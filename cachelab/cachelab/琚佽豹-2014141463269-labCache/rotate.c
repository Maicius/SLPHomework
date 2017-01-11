#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "cache.h"


/* Here is an our naive implementation */
char rotate_descr[] = "Naive Row-wise Traversal of src";
void rotate(int dim, pixel *src, pixel *dst) {
	int i, j;

	for(i=0; i < dim; i++) {
		for(j=0; j < dim; j++) {
			COPY(&dst[PIXEL(dim-1-j,i,dim)], &src[PIXEL(i,j,dim)]);
		}
	}

	return;
}
char my_rotate_descr[] = "my wise Traversal of src";
void my_rotate(int dim, pixel *src, pixel *dst) 
{
   int i, j,c,r;
   int rstripe = dim,cstripe = dim;
   rstripe = cstripe = 4;
   
   for (c = 0; c < dim / rstripe; c++) {
	   for (r = 0; r < dim / cstripe; r++) {
		   for (i = c*rstripe; i < (c+1)*rstripe; i++) {
			   for (j = r*cstripe; j < (r+1)*cstripe; j++) {
				   COPY(&dst[PIXEL(dim-1-j,i,dim)], &src[PIXEL(i,j,dim)]);
			   }
		   }
	   } 
   }
	return;
}
/* Add additional functions to test here */
void register_rotate_functions() {
	add_rotate_function(&rotate, rotate_descr);
	add_rotate_function(&my_rotate, my_rotate_descr);
}

