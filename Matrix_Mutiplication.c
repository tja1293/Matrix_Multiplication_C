#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void main(int argc, char ** argv)
{
  FILE *fp = NULL;
  double matval = 0.0;
  char c;
  FILE * resultFile;

  
  // initialising threads variable
  int threads;
  
  // logic so if a user does not input thread count in default theads is 5.
  if (argc == 2)
  {
  	// allowing the user to input threads count on command line
  	threads = atoi(argv[1]);
  }
  else
  {
  	threads = 5;
  }

  
  fp = fopen("2015861-matrices.txt", "r");
 
  resultFile = fopen("results.txt", "w");
  while(!feof(fp))
  {
  
    // Matrix A
    int Arows, Acols;
    fscanf(fp,"%d,%d",&Arows, &Acols);
    
    //##########################################
    
    // Creating memory to hold A values
    double** A = malloc(sizeof(double*) * Arows);
    for (int i = 0; i < Arows; i++)
    {
    		A[i] = malloc(sizeof(double) * Acols);
    }
    
    //##########################################
    
    
    printf("A Matrix\n");
    for(int row = 0; row < Arows; row++){
      printf("[ ");
      for(int col = 0; col < Acols-1; col++){
        fscanf(fp,"%lf,",&matval);
        A[row][col] = matval;
        printf("%lf\t",matval);
      }
      fscanf(fp,"%lf\n",&matval);
      A[row][Acols-1] = matval;
      printf("%lf ]\n",matval);
    }
    
    // Matrix B
    int Brows, Bcols;
    fscanf(fp,"%d,%d",&Brows, &Bcols);

    
    
    //##########################################
    
    // Creating memory to hold B values
    double** B = malloc(sizeof(double*) * Brows);
    for (int i = 0; i < Brows; i++)
    {
    		B[i] = malloc(sizeof(double) * Bcols);
    }
    
    //##########################################
    
    
    
    printf("B Matrix\n");
    for(int row = 0; row < Brows; row++){
      printf("[ ");
      for(int col = 0; col < Bcols-1; col++){
        fscanf(fp,"%lf,",&matval);
        B[row][col] = matval;
        printf("%lf\t",matval);
      }
      fscanf(fp,"%lf\n",&matval);
      B[row][Bcols-1] = matval;
      printf("%lf ]\n",matval);
    }
    
    int Ccols = Bcols;
    int Crows = Arows;
    
    
    //##########################################
    
    // Creating memory to hold C values
    double** C = malloc(sizeof(double*) * Crows);
    for (int i = 0; i < Crows; i++)
    {
    		C[i] = malloc(sizeof(double) * Ccols);
    }
    
    
    //##########################################
    
    
    // Initiating all C values to 0
    for (int i = 0; i < Crows; i++)
    {
    	for (int j = 0; j < Ccols; j++)
    	{
    		C[i][j] = 0;
    	}
    }
    
	// calculating C matrix values
    if (Acols == Brows){
	    	#pragma omp parallel for collapse(3) num_threads(threads)
	    	for(int i=0; i < Arows; i++){
	    		for(int j=0; j < Bcols; j++){    
		 		for(int k=0; k < Acols; k++){
		 			// printing number of threads to the terminal
		   			printf("threadID: %d\n", omp_get_thread_num());
		   			C[i][j] += A[i][k] * B[k][j];
		   		}
		   	}
		 }
	}
  	else{
  		printf("Error! A and B matricies not compatible\n");
  	}	
  	
  	// print C matrix to terminal (or file)
  	printf("C Matric rows%d, cols%d\n", Crows, Ccols);
  	fprintf(resultFile, "C Matric - Rows %d, Cols %d\n", Crows, Ccols);
  	
  	for (int i=0; i<Crows; i++)
  	{
  		for (int j=0; j<Ccols; j++)
  		{
  			printf("%lf\t", C[i][j]);
  			fprintf(resultFile, "%.4f,",C[i][j]);
  		}
  		printf("\n");
  		fprintf(resultFile,"\n");
 
  	}
  	printf("\n");
  	fprintf(resultFile,"\n");
  	
  	
  	//##########################################
  	
  	
  	//  Freeing memory in rows of A
  	for (int i = 0; i <Arows; i++)
  	{
  		free(A[i]);
  	}
  	// freeing memory in A
  	free(A);
  	
  	
  	//##########################################
  	
  	
  	//  Freeing memory in rows of B
  	for (int i = 0; i <Brows; i++)
  	{
  		free(B[i]);
  	}
  	
  	// freeing memory in B
  	free(B);
  	
  	
  	//##########################################
  	
  	
  	//  Freeing memory in rows of C
  	for (int i = 0; i <Crows; i++)
  	{
  		free(C[i]);
  	}
  	// freeing memory in C
  	free(C);
  	
  	
  	//##########################################
   }
   fclose(fp);
 }
