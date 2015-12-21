#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{

  
  if(argc!=4)                 /*check if correct number of arguments are passed*/
  {
            printf("******Incorrect number of arguments*******\n");
           // abort();
            return -1;
  }

 
 FILE *fp1,*fp2,*fp3;/*fp1 is filepointer to huffman table file ,fp2 is filepointer to input text file,fp3 is filepointer to output binary file*/
 
 char codeword[32];
 char array[256][32];

 int entry;
 int i=0,j,k;
 int addzero;
 unsigned char a=0x0;
 int bufferlength;
 char inputchar,buffer[32];  /* each code is maximum 32 bits long*/
 char *buffersequence=malloc(40000);  

 
 /* open the files in desired mode */
  fp1=fopen(argv[1],"r");
  printf("argv[1] %s\n", argv[1]);
  fp2=fopen(argv[2],"r");
  printf("argv[2] %s\n", argv[2]);
  fp3=fopen(argv[3],"wb+");
  printf("argv[3] %s\n", argv[3]);

 if(fp1  == NULL)  /* Open huffman file in read mode */
  {
    printf("Error opening %s for reading. Program terminated.", argv[1]);
    abort();
  }
  
  if(fp2  == NULL) 
  {
    printf("Error opening %s for reading. Program terminated.", argv[2]);
    abort();
  }
  if(fp3  == NULL) 
  {
    printf("Error opening %s for writing. Program terminated.", argv[3]);
    abort();
  }

  
  for(i=0; i<256; i++){
    for(j=0; j<32; j++){
      array[i][j] = 0;
    }
  }

/* read the huffman file line by line and convert it into an array */  
while (!feof(fp1)) {   /* open huffman file and read each line of huffman file to store into an array*/
    fscanf(fp1, " %d %s", &entry, codeword);
    strcpy(array[entry], codeword);
}


/* read the input file and check for the symbols in huffman file*/
   while((inputchar = fgetc(fp2)) != EOF){
   printf("%c",inputchar); 
      if(0 == array[inputchar]){
        return -1;
      }

      strcat(buffersequence,array[inputchar]); 
   }


/* work on the buffersequence u got */
bufferlength=(strlen(buffersequence))%8; /*start working with final string you got and check if you need to pad zeroes */

if(bufferlength!=0)  /*if your buffersequencelength is not a byte i.e 8 bits long */
{
           
   addzero=8-bufferlength;
   for(j=0;j<addzero;j++)
   {
     strcat(buffersequence,"0");
   }
     
}

printf(" The sequence that will be written in binary to output file: %s\n", buffersequence);
   
/*write out your sequence to the third file */


k = 0;
i = 0;
while(k<strlen(buffersequence)){
    if (buffersequence[k] == '0') {
          a = a << 1; 
          i++;
                    
    }else {             
          a = a<< 1;
          a++;
          i++;
                    
    }

    if((i%8)==0){
          fwrite(&a, 1, sizeof(a), fp3);
          a = 0x0;
          i = 0;
    }
    k++;
}

if(i<8 && i>0){

  while(i<8){
    a = a<<1;
    i++;
  }
  
  fwrite(&a, 1, sizeof(a), fp3);
  a = 0x0;

}



fclose(fp1);
fclose(fp2);
fclose(fp3);
}
