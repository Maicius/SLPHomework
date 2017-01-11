#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "cache.h"




/* Here is an our naive implementation */
char smooth_descr[] = "SMOOTH: Naive Row-wise Traversal of src";
void smooth(int dim, pixel *src, pixel *dst) {
	int i, j;
	for(i=0; i<dim;i++) {
		COPY(&dst[PIXEL(i,0,dim)], &src[PIXEL(i,0,dim)]);
		COPY(&dst[PIXEL(i,dim-1,dim)], &src[PIXEL(i,dim-1,dim)]);
	}
	for(j=1; j<dim-1;j++) {
		COPY(&dst[PIXEL(0,j,dim)], &src[PIXEL(0,j,dim)]);
		COPY(&dst[PIXEL(dim-1,j,dim)], &src[PIXEL(dim-1,j,dim)]);
	}
	for(i=1; i<dim-1; i++) {
		for(j=1; j<dim-1; j++) {
			SMOOTH(&dst[PIXEL(j,i,dim)],
					&src[PIXEL(j,i,dim)],
					&src[PIXEL(j-1,i,dim)],
					&src[PIXEL(j+1,i,dim)],
					&src[PIXEL(j,i+1,dim)],
					&src[PIXEL(j,i-1,dim)],
					&src[PIXEL(j-1,i-1,dim)],
					&src[PIXEL(j+1,i+1,dim)],
					&src[PIXEL(j-1,i+1,dim)],
					&src[PIXEL(j+1,i-1,dim)]);
		}
	}
	return;
}
char my_smooth_descr[] = "YuanHao's wise Traversal of src";   
void my_smooth(int dim, pixel *src, pixel *dst) {   
    int i, j;   
	
    for(i=0; i < dim; i++) {   
        for(j=0; j < dim; j++) {   
            if (i != 0 && j != 0 && i != (dim - 1) && j != (dim - 1)) {   
                SMOOTH(&dst[PIXEL(i,j,dim)],   
                    &src[PIXEL(i,j,dim)],   
                    &src[PIXEL(i-1,j,dim)],   
                    &src[PIXEL(i+1,j,dim)],   
                    &src[PIXEL(i,j+1,dim)],   
                    &src[PIXEL(i,j-1,dim)],   
                    &src[PIXEL(i-1,j-1,dim)],   
                    &src[PIXEL(i+1,j+1,dim)],   
                    &src[PIXEL(i-1,j+1,dim)],   
                    &src[PIXEL(i+1,j-1,dim)]);   
            }   
            else {   
                COPY(&dst[PIXEL(i,j,dim)], &src[PIXEL(i,j,dim)]);   
            }   
        }   
    }   
	
    return;   
}   



/* Add additional functions to test here */
void register_smooth_functions() {
	add_smooth_function(&smooth, smooth_descr);
	add_smooth_function(&my_smooth, my_smooth_descr);   
}

