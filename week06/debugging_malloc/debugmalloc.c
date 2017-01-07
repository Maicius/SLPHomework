#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "dmhelper.h"
#include <stdio.h>


struct Footer{
	int Fence[1];
};
/**********************
*双向链表，用于确定分配的内存块的地址，以便检查是否没有释放
*********************/
struct Node{
	struct Header* header;
	int sequence;
	void* ptr;
	size_t size;
	char AllocFilename[1000];
	int  AllocLinenumber;
	struct Node* prev;
	struct Node* next;
};
struct Header{
	int Checksum;
	int sequence;
	size_t size;
	char Filename[1000];
	int Linenumber;
	int Fence[1];
};

struct Node* used = NULL;
struct Node* unUsed = NULL;
size_t allocated = 0;
/* Wrappers for malloc and free */

void *MyMalloc(size_t size, char *filename, int linenumber) {
	struct Node* pTemp = unUsed;
	struct Node* node;
	struct Header* blockHeader;
	void* ptr;
	struct Footer* blockFooter;
	int found = 0;

	/* find available block in unUsed list */
	if (NULL != unUsed)
	{
		do 
		{
			if (pTemp->size >= size)
			{
			found = 1;
				break;
			}

			if (NULL == pTemp->prev)
				break;
			pTemp = pTemp->prev;
		} while (1);
	}
	/*if find one suitable block*/
	if (found)
	{
		node = pTemp;
		//分配Block的信息，including fence, checksum, node
		blockHeader = pTemp->header; 
		ptr = (void*) (((char*)blockHeader) + sizeof(struct Header));
		blockFooter = (struct Footer*) (((char*)ptr) + size);
		blockHeader->Fence[0] = 0xCCDEADCC;
		blockFooter->Fence[0] = 0xCCDEADCC;
		blockHeader->size = size;
		blockHeader->Checksum = size | linenumber;
		blockHeader->Linenumber = linenumber;
		strcpy(blockHeader->Filename, filename);
		//设置节点信息
		node->header = blockHeader;
		node->ptr = ptr;
		strcpy(node->AllocFilename, filename);
		node->AllocLinenumber = linenumber;
		node->sequence = allocated;
		//modify unUsed list,
		if (NULL == pTemp->prev && NULL == pTemp->next)
			unUsed = NULL;
		else if (NULL == pTemp->prev)
		{
			pTemp->next->prev = NULL;
		}
		else if (NULL == pTemp->next)
		{
			pTemp->prev->next = NULL;
		}
		else
			pTemp->prev->next = pTemp->next->prev;
	}
	/* */
	else
	{
		node = (struct Node*) malloc(sizeof(struct Node));

		blockHeader = (struct Header*) malloc(sizeof(struct Header) 
			+ size + sizeof(struct Footer));
		ptr = (void*) (((char*)blockHeader) + sizeof(struct Header));
		blockFooter = (struct Footer*) (((char*)ptr) + size);
		blockHeader->Fence[0] = 0xCCDEADCC;
		blockFooter->Fence[0] = 0xCCDEADCC;
		blockHeader->size = size;
		blockHeader->Checksum = size | linenumber;
		blockHeader->Linenumber = linenumber;
		strcpy(blockHeader->Filename, filename);
		
		node->header = blockHeader;
		node->ptr = ptr;
		node->size = size;
		strcpy(node->AllocFilename, filename);
		node->AllocLinenumber = linenumber;
		node->sequence = allocated;
	}
	if (NULL == used)
	{
		used = node;
		used->prev = NULL;
		used->next = NULL;
	}
	else
	{
		used->next = node;
		node->prev = used;
		node->next = NULL;
		used = node;	
	}
	
	allocated += size;
	return (ptr);
}

void MyFree(void *ptr, char *filename, int linenumber) {
	struct Node* pTemp = used;
	void* pData;

	if (NULL == used)
		error(4, filename, linenumber); 

	do 
	{
		pData = (void*) (((char*)pTemp->header) + sizeof(struct Header));
		if (ptr == pData || NULL == pTemp)
			break;
		pTemp = pTemp->prev;
	} while (1);
	

	if (ptr == pData)
	{
		struct Footer* footerTemp = (struct Footer*)((char*)pTemp->header + sizeof(struct Header) 
				+ pTemp->header->size);
		if (0xCCDEADCC != footerTemp->Fence[0])
		{
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Ending edge of the payload has been overwritten."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			printf("\tand freed at %s, line %d\n", filename, linenumber);
		}
		
		if (0xCCDEADCC != pTemp->header->Fence[0] 
			|| ((pTemp->header->size | pTemp->header->Linenumber) != pTemp->header->Checksum))
		{
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Header has been corrupted."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			printf("\tand freed at %s, line %d\n", filename, linenumber);
			printf("or\n");
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Starting edge of the payload has been overwritten."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			printf("\tand freed at %s, line %d\n", filename, linenumber);
		}

		if (NULL == pTemp->prev && NULL == pTemp->next)
			used = NULL;
		else if (NULL == pTemp->prev)
		{
			pTemp->next->prev = NULL;
		}
		else if (NULL == pTemp->next)
		{
			pTemp->prev->next = NULL;
		}
		else
			pTemp->prev->next = pTemp->next->prev;

		if (NULL == unUsed)
		{
			unUsed = pTemp;
			unUsed->prev = NULL;
			unUsed->next = NULL;
		}
		else
		{
			unUsed->next = pTemp;
			unUsed = pTemp;
			pTemp->next = NULL;
		}

		allocated -= pTemp->header->size;
	}
	else
	{
		error(4, filename, linenumber); 
	}
}

/* returns number of bytes allocated using MyMalloc/MyFree:
	used as a debugging tool to test for memory leaks */
int AllocatedSize() {
	return allocated;
}



/* Optional functions */

/* Prints a list of all allocated blocks with the
	filename/line number when they were MALLOC'd */
void PrintAllocatedBlocks() {
	struct Node* pTemp = used;
	
	if (NULL == pTemp)
		return;

	printf("Currently allocated blocks:\n");
	do 
	{
		printf("%d bytes, created at driver.c, line%d\n"
			, pTemp->size, pTemp->AllocLinenumber);
		if (NULL == pTemp->prev)
			break;
		
		pTemp = pTemp->prev;

	} while (1);

	return;
}

/* Goes through the currently allocated blocks and checks
	to see if they are all valid.
	Returns -1 if it receives an error, 0 if all blocks are
	okay.
*/
int HeapCheck() {
	struct Node* pTemp = used;
	int ok = 1;

	if (NULL == pTemp)
		return 0;

	do 
	{
		struct Footer* footerTemp = (struct Footer*)((char*)pTemp->header + sizeof(struct Header) 
			+ pTemp->header->size);
		if (0xCCDEADCC != footerTemp->Fence[0])
		{
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Ending edge of the payload has been overwritten."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			ok = 0;
		}
		
		if (0xCCDEADCC != pTemp->header->Fence[0] 
			|| ((pTemp->header->size | pTemp->header->Linenumber) != pTemp->header->Checksum))
		{
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Header has been corrupted."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			printf("or\n");
			printf("Error: %s\n\tin block allocated at %s, line %d\n", "Starting edge of the payload has been overwritten."
				, pTemp->AllocFilename, pTemp->AllocLinenumber);
			ok = 0;
		}
		if (NULL == pTemp->prev)
			break;
	
		pTemp = pTemp->prev;
	} while (1);

	if(ok)
		return 0;
	else
		return -1;
}
