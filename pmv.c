#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 int MinLength,MaxLength;
void RandomSendRec (){


} 

int Random1 (int Min,int Max){

    int x=Max-Min;
return (int) (((double)(x+1)/RAND_MAX)*rand()+Min);
}
int main(int argc,char *argv[])
	
{
	MPI_Status stu;
	int count;
	int numtasks;
	int rank;
	int ran1;
	int ran2;
	int j;
	int ran;
	int i;
	int k;
	int min,max;
	int *outmsg1;
	int* outmsg2;
	int *inmsg1;
	int* inmsg2;
	int *inmsg;
	int flag=0;
	int tag;
        int DesRan1,DesRan2,DesRan;
        int sum=0;	
	int se,se2,rc,rc2;
	MPI_Request reque1[100];
	MPI_Request reque[100];
	MPI_Request req[4];
	MPI_Request request1[2];
	MPI_Request reques2[100];
	MPI_Status stats[4],st[20];
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0){
	printf("enter the minimum Length of the array \n ");
	fflush(stdout);
	scanf("%d",&MinLength);
	min=MinLength;
	
	printf("enter the maximum Length of the array \n ");
        fflush(stdout);
	scanf("%d",&MaxLength);
	max=MaxLength;      
	printf("\n oKaY ... \n");
	}
	
	 MPI_Bcast(&min,1,MPI_INT,0,MPI_COMM_WORLD);	
	 MPI_Bcast(&max,1,MPI_INT,0,MPI_COMM_WORLD);
		srand(rank); 
       ran1= rand() % (max-min+1) +min;
	//srand(time(NULL)+rank); 
	ran2=rand() % (max-min+1) +min;


	
	outmsg1= (int*) malloc(ran1 * sizeof(int));
	printf("\n process ( %d ) created array1[ %d ] = ",rank,ran1);
	for (i=0;i<ran1;i++){
           outmsg1[i]=Random1(i,i+150);
		   printf("%d  ",outmsg1[i]);
		}
	
	 
	 outmsg2= (int*) malloc(ran2 * sizeof(int));
	 printf("\n process ( %d ) created array2[ %d ] = ",rank,ran2);
	 for (i=0;i<ran2;i++){
           outmsg2[i]=Random1(i,i+150);
		   printf("%d  ",outmsg2[i]);
		}
	
	 
	srand(time(NULL)+rank);
	DesRan1 = rand() % (numtasks) ;
	
	dr1=DesRan1;	
	srand(rank);
	DesRan2 = rand() % (numtasks) ;


	MPI_Barrier(MPI_COMM_WORLD);

	printf("\n creation finished .... \n");


	for (i=0;i<numtasks;i++){
		 MPI_Isend(&DesRan1, 1, MPI_INT,i, 5000, MPI_COMM_WORLD,&req[i]);
		 
	} 
	for (i=0;i<numtasks;i++){
	    MPI_Isend(&DesRan2, 1, MPI_INT,i, 5001, MPI_COMM_WORLD,&req[i]);
		
	}
		printf("\n process %d  send to the destenation process1 = %d",rank,DesRan1);
    	printf("\n                        destenation process2 = %d",DesRan2);
	 printf("\n  \n");

	MPI_Barrier(MPI_COMM_WORLD);
	for (i=0;i<numtasks;i++){
		 MPI_Irecv(&DesRan, 1, MPI_INT,MPI_ANY_SOURCE, 5000, MPI_COMM_WORLD, &req[i]);
		
	//	 printf("\n process %d recieve DesRan1 = %d \n",rank,DesRan1);
		  if (rank==DesRan ){
		   sum =sum+1;
		  }
	}
	for (i=0;i<numtasks;i++){
	    MPI_Irecv(&DesRan, 1, MPI_INT, MPI_ANY_SOURCE, 5001, MPI_COMM_WORLD, &req[i]);
		MPI_Barrier(MPI_COMM_WORLD);
		// printf("\n process %d recieve DesRan2 = %d \n",rank,DesRan2);
		 if (rank == DesRan){
		   sum =sum+1;
		  }
		 
	}

	 printf("\n  process %d will receive  = %d  messege \n",rank,sum);
	 printf("\n _______________________________________ \n");
	fflush(stdout);

	

	 MPI_Barrier(MPI_COMM_WORLD);
	MPI_Isend(outmsg1, ran1, MPI_INT,DesRan1, 150, MPI_COMM_WORLD,&reque[0]); 
	// MPI_Barrier(MPI_COMM_WORLD);
	 MPI_Isend(outmsg2, ran2, MPI_INT,DesRan2, 150, MPI_COMM_WORLD,&reque[1]);



	  MPI_Barrier(MPI_COMM_WORLD);

	// sta= (MPI_Status*) malloc(sum * sizeof(MPI_Status));
	 //for (i=0;i<sum;i++){
	


	 k=0;
	 while (1){
    		//printf("\n \n im process %d my sum is %d \n \n",rank,sum);
		    MPI_Iprobe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &stu);   
			if (flag){
			      MPI_Get_count(&stu,MPI_INT,&count);
			     inmsg= (int*) malloc(count * sizeof(int));
				 k++;
			    MPI_Recv(inmsg,count , MPI_INT, stu.MPI_SOURCE, stu.MPI_TAG,
				MPI_COMM_WORLD, &stu);	
			
			printf("\n \n process %d received from source %d for the %d  times >>> \n array[%d] = "
				,rank,stu.MPI_SOURCE,i,count);
			for (j=0;j<count;j++){
		          printf("%d ",inmsg[j]); 
	           }
		
		
		}
		if (k == sum)
			break;
	 }
	
//printf("\n process %d done now ....",rank) ;
//	 MPI_Wait(&request)
 MPI_Finalize();

}

