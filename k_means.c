#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//code@raajtilaksarma

float EucDist(int x1,int x2,int y1,int y2);
/*taking no of clusters = 3
any no of clusters can be taken
and changes can be made accordingly*/

int main()
{
	FILE *file;
	FILE *final;	
	file = fopen("data.csv","r");
	final = fopen("x-y-cluster.csv","w+");
	int *x_coor;
	int *y_coor;
	int NumberOfPoints=-1;
	int i=0,j=0;
	int count;
	float min,fromR,fromS,fromT;
	int mean_x[3],mean_y[3];
	int sum_x[3],sum_y[3];
	int prev_x[3],prev_y[3];
	//sum to keep track of mean for each cluster
	//current mean coordinates of that cluster
	char c;
	//keeping count for each cluster
	int c1=1,c2=1,c3=1;
	if(file==NULL)
		printf("\nFile DNE");
	else
	{
		for (c=getc(file); c!=EOF; c=getc(file))
        	if (c=='\n')
            		NumberOfPoints++;
		printf("\nno of points = %d\n",NumberOfPoints);
		x_coor = malloc(sizeof(int)*NumberOfPoints);
		y_coor = malloc(sizeof(int)*NumberOfPoints);
		fseek(file,0,SEEK_SET);
		while(fscanf(file,"%d,%d",&x_coor[i],&y_coor[i])!=EOF)
		{
			i++;
		}				
	}
	char Cluster[NumberOfPoints];
	//array to tell me which cluster the point belongs
	for(i=0; i<NumberOfPoints; i++)
		printf("Point no %d : (x,y) = %d, %d\n",i,x_coor[i],y_coor[i]); 
	printf("No of clusters=3\n");
	//taking first three points as means of three clusters
	for(i=0;i<3;i++)
	{
		mean_x[i]=x_coor[i];
		mean_y[i]=y_coor[i];
	}
	Cluster[0]='R';
	Cluster[1]='T';
	Cluster[2]='S';
	printf("The clusters are named R,T and S\n");
	printf("Initial means:\n");	
	for(i=0;i<3;i++)
		printf("Cluster=%c x=%d,y=%d\n",Cluster[i],mean_x[i],mean_y[i]);
	for(i=0; i<3; i++)
	{
		sum_x[i]=mean_x[i];
		sum_y[i]=mean_y[i];
	}
	//below loop can break in two ways
	//either no of iterations end or mean remains constant as to previous iterations
	for(j=0; j<100; j++)
	{	
		count = 0;		
		for(i=0;i<3;i++)
		{
			prev_x[i]=mean_x[i];
			prev_y[i]=mean_y[i];
		}
		for(i=0; i<NumberOfPoints; i++)
		{
			fromS=EucDist(x_coor[i],mean_x[2],y_coor[i],mean_y[2]);
			fromT=EucDist(x_coor[i],mean_x[1],y_coor[i],mean_y[1]);
			fromR=EucDist(x_coor[i],mean_x[0],y_coor[i],mean_y[0]);	
			min = fminf(fromR,fminf(fromT,fromS));
			if(min==fromR)
			{
				Cluster[i]='R';
				c1++;
				sum_x[0] = sum_x[0] + x_coor[i];
				sum_y[0] = sum_y[0] + y_coor[i];
			}
			else if(min==fromT)
			{
				Cluster[i]='T';
				c2++;
				sum_x[1] = sum_x[1] + x_coor[i];
				sum_y[1] = sum_y[1] + y_coor[i];
			}
			else if(min==fromS)
			{
				Cluster[i]='S';
				c3++;
				sum_x[2] = sum_x[2] + x_coor[i];
				sum_y[2] = sum_y[2] + y_coor[i];
			}
			//more else if statements depending on no of clusters
		}
		mean_x[0] = sum_x[0]/c1;
		mean_y[0] = sum_y[0]/c1;
		mean_x[1] = sum_x[1]/c2;
		mean_y[1] = sum_y[1]/c2;
		mean_x[2] = sum_x[2]/c3;
		mean_y[2] = sum_y[2]/c3;
		for(i=0;i<3;i++)
		{
			if(mean_x[i]==prev_x[i]&&mean_y[i]==prev_y[i])
				count++;
		}
		if(count==3)
			printf("\nStopped at iteration %d",j+1);
		if(count==3)
			break;	
	}

	//for(i=0;i<3;i++)
	//	printf("\nNew means:Cluster=%c x=%d,y=%d",Cluster[i],mean_x[i],mean_y[i]);
	for(i=0; i<NumberOfPoints;i++)
		printf("\npoint no %d: x = %d, y= %d, Cluster = %c",i,x_coor[i],y_coor[i],Cluster[i]);
	for(i=0; i<NumberOfPoints;i++)
		fprintf(final,"%d,%d,%c\n",x_coor[i],y_coor[i],Cluster[i]);
	fclose(file);
	fclose(final);
	system("python plot.py");
	return 0;
}

float EucDist(int x1,int x2,int y1,int y2)
{
	int diffx,diffy;
	diffx=x2-x1;
	diffy=y2-y1;
	return sqrt(pow(diffx,2)+pow(diffy,2));
}

