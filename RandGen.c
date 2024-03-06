#include <stdio.h> //input-output operations
#include <stdlib.h> // memory allocation

//the main function takes command-line arguments to specify the output file name, the number of bytes to generate, and the probabilities of each byte
//arcg - argument count, the number of arguments passed to the program from cmd
//argv - argument vector, 
//Command-line Arguments:
//argv[0]: ALways the name of the program (the executable .exe generated after compuling the C program).
//argv[1]: Output file name (data.txt).
//argv[2]: Number of bytes to generate.
//argv[3] to argv[argc-1]: Probabilities of each byte.
int main(int argc, char *argv[]) 
{
	FILE *f;								 //f is a file pointer that we'll use to write data to a file. 
	int i, n=argc-3, size;					 //n - number of probabilities read from cmd-line arguments
	float prob[256]={0}; 					 //probabilities for each character/symbol (256 ASCII characters)
	for(i=0;i<n;i++) 						 //reading the probabilities for each character from cmd-line arguments
		sscanf(argv[i+3],"%f",&prob[i]); 	 //reads fortmatted input
	sscanf(argv[2],"%d",&size); 		  	 //readings the desired size of the output file from cmd-line arg
	n=256;
	//for(i=0;i<256;i++)
	//	prob[i]=1.0/256; 					//each character is equally likely to "happen"
	printf("We will output a file %s with %d bytes, with prob:\n",argv[1],size);  //print msg aboyt name&size of the file and prob of chars
	for(i=0;i<n;i++)
		printf("%f ",prob[i]);
	
	 
	unsigned char *data;					//declaring a pointer pointing to memeory locations
											//char data type - single byte (8bits) to hold ASCII characters
											//unsigned char is used to ensure that the range of values is from 0 to 255, which aligns with the possible values of a byte. 					
	data=(unsigned char*)malloc(size*sizeof(unsigned char)); //mwemory allocation
	if (data==NULL)
	{
		printf("Allocation error");
		exit(1);
	}
	int x;									//storing random nimbers 
	srand(0);								//seeding the random number generator
	
	//loop to generate random chaacters
	for(i=0;i<size;i++)
	{
		int k=0;
		x=rand();							//generating a random number x
		while(x>0)
		{
			x=x-prob[k]*RAND_MAX;			//compares it with the cumulative probabilities in prob
			k++;
		}
		data[i]='a'+k-1;					//assigns the corresponding character to data[i]
	}
	f=fopen(argv[1],"w");					//open the output file (argv[1]) in writing 'w' mode
	fwrite(data,1,size,f);					//write the data stored in 'data' to the file
	fclose(f);								//close file
	free(data);								//frees the dynamically allocated memory to prevent memory leaking
	return 0;
}
