// Dingbang Chen//
// Assignment 4//
// CS211 //
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>




char* tobinary(char *hex){
	//char bin[48];
	int hexlength= strlen(hex)-2;
//	printf("%d\n",hexlength );
	int binarylength=hexlength*4;
//	printf("%d\n", binarylength );
	char out[binarylength+1];

	out[0]='\0';
	
	char *mycode;
	int i=2;
//	printf("%s\n", hex);
	while(hex[i]){
		//printf("1\n");
		switch (hex[i])
        {
        case '0':
            mycode="0000"; break;
        case '1':
            mycode="0001"; break;
        case '2':
            mycode="0010"; break;
        case '3':
            mycode="0011"; break;
        case '4':
            mycode="0100"; break;
        case '5':
            mycode="0101"; break;
        case '6':
            mycode="0110"; break;
        case '7':
            mycode="0111"; break;
        case '8':
            mycode="1000"; break;
        case '9':
            mycode="1001"; break;
        case 'A':
            mycode="1010"; break;
        case 'B':
            mycode="1011"; break;
        case 'C':
            mycode="1100"; break;
        case 'D':
            mycode="1101"; break;
        case 'E':
            mycode="1110"; break;
        case 'F':
            mycode="1111"; break;
        case 'a':
            mycode="1010"; break;
        case 'b':
            mycode="1011"; break;
        case 'c':
            mycode="1100"; break;
        case 'd':
            mycode="1101"; break;
        case 'e':
            mycode="1110"; break;
        case 'f':
            mycode="1111"; break;
        default:
            printf("\n Invalid hexa digit %c ", hex[i]);
            return 0;
        }
        strcat(out, mycode);
        i++;
    }
    //printf("%s\n", out);
 // printf("%c %c %c %c\n",out[binarylength-3] ,out[binarylength-2],out[binarylength-1],out[binarylength]);
   char * tmp = out;
   tmp[binarylength] = '\0';
    return tmp;
}
int binarytodecimal(int* binary, int setindex){
	int result = 0 ;
//		int t;
//			for(t=0;t<setindex;t++){
//				printf("%c",binary[t] );
//		}
//			printf("\n");
	int y;
	//printf("%d\n", setindex);
	for(y=0 ; y< setindex;y++){
	//	printf("%d\n",binary[y] );
		result= result*2 + (binary[y]-48);
	}
//	printf("%d\n", result);
	return result;

}
	
//void implementtypeA (char* a, int setindex, int numberoftag){
	

		
			//int inttag;
		//	sscanf(tag, "%d", &inttag);
		//	printf("%d\n",inttag );
			//printf("%d\n", decimalindex);
		//		int t;
	//		for (t=0; t<numberoftag;t++){
	//			printf("%c", tag[t]);
	//		}
	//		printf("\n");
				// create a 2D-array//
	//	int column= intass;
	//	int row= numberofset2;
	//	int arr[row][column];

		//start to check//






//}
int main(int argc, char**argv)
{
	if(argc<5){
		printf("Invalid Command!\n");
		exit(0);
	}

	char* cachesize= argv[1];
	char* asso= argv[2];
	char* blocksize= argv[3];
	//char* tracefile= argv[4];

	int cache_size;
	sscanf(cachesize,"%d",&cache_size);

	int block_size;
	sscanf(blocksize,"%d",&block_size);

	//Get assoc//
	int intass;

	if(strcmp(asso,"direct")==0){
		intass=1;
	}else if (strcmp(asso,"assoc")==0){
		intass=cache_size/block_size;
	}else{
	char charass=asso[6];
	intass= charass-'0';
	
}
	int Amemoryread=0;
	int Amemorywrite=0;
	int Acachehit=0;
	int Acachemiss=0;
	int Bmemoryread=0;
	int Bmemorywrite=0;
	int Bcachehit=0;
	int Bcachemiss=0;

	//calculate tag//
	int numberofset1= cache_size/intass;
	int numberofset2= numberofset1/block_size;
	int setindex = log(numberofset2)/log(2);
	int blockoffset= log(block_size)/log(2);
	int numberoftag= 48-setindex-blockoffset;

	// Set up the Cache//
	 int column= intass;
		int row= numberofset2;
		char *arr[row+1][column+1];
			int r;
			int co;
	for( r=0;r<=row;r++){
		for(co=0;co<=column;co++){
			arr[r][co]=malloc(46);
			arr[r][co][0] = '\0';
		}
	}
// Set up Cache B//
		int columnB = intass;
		int rowB= numberofset2;
		char* arrB [ rowB+1][columnB+1];
		for(r=0; r <= rowB; r++){
			for(co = 0; co<= columnB;co++){
				arrB[r][co]=malloc(46);
				arrB[r][co][0]= '\0';
			}
		}



	//Read the File//
	FILE* fp;
	char readorwrite;
	char address[30];
	char useless[30];
//	int num = 1;
	
	fp=fopen(argv[4],"r");
	if(fp==NULL){
		printf("error\n");
		return 1;
	}
	if(fp!=NULL){
		while(fscanf(fp,"%s %c %s", useless,&readorwrite,address)!=EOF){
			if(strcmp(useless,"#eof")==0){
				break;
			}
			char* a= tobinary(address);
			
			// Type A//
			// Get everything in array 0//
			int i;
			char fortyeight [48];
			for(i=0;i<48;i++){
				fortyeight[i]='0';
			}
			//Get a full address 48bits//
			int length=strlen(a)-1;
			int j= 47;
			for (; j>0;j-- ){
				if (length==-1){
					break;
				}
				fortyeight[j]=a[length];
				length--;
			}
			// Get set index//
			int setindexarr [setindex];
			int start= numberoftag;
			int q;
			int w=0;
			for(q=start;q<start+setindex;q++){
				setindexarr[w]=fortyeight[q];
				w++;
			}
			//Get tag//
			
			char tag [numberoftag+1];
			int e =0;
			int r;
			for(r=0; r <numberoftag; r++){
				tag[e]=fortyeight[r];
				e++;
			}
			tag[numberoftag] = '\0';
//			int t ;
//			for(t=0; t<numberoftag; t++){
//			printf("%c", tag[t]);
//		}
//				printf("\n");

			char* tagA= tag;
	//		printf("%s\n",tagA );

		//	char * tagg= tag;
			//printf("%s\n", tagg);
			// Gey set index in decimal//
			int decimalindex;
			decimalindex=binarytodecimal(setindexarr, setindex);
		//	printf("%d\n",decimalindex );
			

			//compare //
			int g;
			int h;
			int count =0;
			int add= 0;
			int compare=0;
			//int more =0;
	//		printf("%d\n",decimalindex );
			for (g =0; g<intass; g++){
				if(arr[decimalindex][g]!=NULL){
					char* get = arr[decimalindex][g];
					get[numberoftag] = '\0';
					compare=0;
				//	printf("%d\n", num);
				//	printf("length of get: %lu\nlength of tagA: %lu\n", strlen(arr[decimalindex][g]), strlen(tagA));
					for(h=0; h <numberoftag;h++){
						if (get[h]!=tagA[h]){
							//printf("tagA: %s\n", tagA);
							//printf("%d\n", num);

							compare=1;
						}
					}
				  	if(compare==0){
				  	//	printf("hit\n");

						count=1;
				//	printf("sdsa\n");
						Acachehit++;
						if(readorwrite=='W'){
							Amemorywrite++;
						}
						break;
					}
				}
			}
				if(count==0){
				    Acachemiss++;	
					for(g=0; g<intass;g++){
						if(arr[decimalindex][g][0] == '\0'){
							memcpy(arr[decimalindex][g], &tagA[0], numberoftag);
							arr[decimalindex][g][numberoftag]= '\0';
							add=1;
							break;
						}

					}
						if(add==0){
							for(h=0;h<intass; h++){
								if(h+1!=intass){
									memcpy(arr[decimalindex][h], &arr[decimalindex][h+1][0], numberoftag);
									arr[decimalindex][h][numberoftag]= '\0';
					//				printf("arr %s\n", arr[decimalindex][g]);

							}else if (h+1==intass){
	//							arr[decimalindex][g]=tagA;
								memcpy(arr[decimalindex][h], &tagA[0], numberoftag);
								arr[decimalindex][h][numberoftag]= '\0';
								break;
								}

							
						}
						//printf("arr:%s length: %lu\n", arr[decimalindex][g], strlen(arr[decimalindex][g]));

					}
					if(readorwrite=='R'){
						Amemoryread++;
						}
					if(readorwrite=='W'){
						Amemoryread++;
						Amemorywrite++;
					}

				}

		


				// Type B//

	// GET SET INDEX//
		int Bsetindexarr[setindex];
		int u;
		int l=0;
		for (u=0 ; u<setindex;u++){
			Bsetindexarr[u]= fortyeight[l];
			l++;
		}
  
		int Bdecimalsetindex;
		Bdecimalsetindex=binarytodecimal(Bsetindexarr, setindex);
	//	printf("%d\n",Bdecimalsetindex );
		
//		int t ;
//	for(t=0; t<48; t++){
//		printf("%c", tybeBaddress[t]);
//	}
//	printf("\n");
		//Get tag//
		char tagB[numberoftag+1];
		
		int f=0;
		int v;
		for( v= setindex; v<setindex+numberoftag;v++){
			tagB[f]= fortyeight[v];
			f++;
		}
		tagB[numberoftag]= '\0';
		char* tagBB = tagB;
//		printf("%s\n",tagBB );
	
		

	//	num++;
		//compare//
		int gg;
		int hh;
		int countcount=0;
		int addadd=0;
		int comparecompare=0;
		for(gg=0; gg<intass;gg++){
			if (arrB[Bdecimalsetindex][gg]!=NULL){
			//	printf("%s\n", arrB[Bdecimalsetindex][gg]);
				char* getB = arrB[Bdecimalsetindex][gg];
			//	printf("%s\n", getB);
				getB[numberoftag]= '\0';
				comparecompare=0;
			//		printf("length of get: %lu\nlength of tagA: %lu\n", strlen(getB), strlen(tagBB));
				for(hh=0; hh< numberoftag; hh++){
					if(getB[hh]!= tagBB[hh]){

						comparecompare=1;
					}
				}
				if(comparecompare==0){
					countcount=1;
					Bcachehit++;
					if(readorwrite=='W'){
						Bmemorywrite++;
					}
					break;
				}


			}
		}
		if(countcount==0){
			Bcachemiss++;
			for(gg=0; gg<intass;gg++){
				if(arrB[Bdecimalsetindex][gg][0]=='\0'){
					memcpy(arrB[Bdecimalsetindex][gg], &tagBB[0],numberoftag);
					//printf("%s\n",tagBB);
					//printf("%s\n",arrB[Bdecimalsetindex][gg] );
			//		printf("!!!!!!!\n");

					arrB[Bdecimalsetindex][gg][numberoftag]='\0';
		//			printf("%s\n",arrB[Bdecimalsetindex][gg] );
					addadd=1;
		//			printf("%d\n",addadd );
					break;
				}
			}
			if(addadd==0){
		//		printf("afdasfasdf\n");
				for(hh=0; hh<intass; hh++){
					if(hh+1!=intass){
						memcpy(arrB[Bdecimalsetindex][hh],&arrB[Bdecimalsetindex][hh+1][0],numberoftag);
						
						arrB[Bdecimalsetindex][hh][numberoftag]='\0';
				//		printf("2222\n");
					}else if (hh+1==intass){
						memcpy(arrB[Bdecimalsetindex][hh],&tagBB[0],numberoftag);
						arrB[Bdecimalsetindex][hh][numberoftag]='\0';
				//		printf("1111\n");
						break;

					}


				}



			}

			if(readorwrite=='R'){
				Bmemoryread++;
			}
			if(readorwrite=='W'){
				Bmemoryread++;
				Bmemorywrite++;
			}


		}



		}

	}
	

	printf("cache A\n");
	printf("Memory reads: %d\n", Amemoryread);
	printf("Memory writes: %d\n", Amemorywrite);
	printf("Cache hits: %d\n", Acachehit);
	printf("Cache misses: %d\n", Acachemiss);
	printf("cache B\n");
	printf("Memory reads: %d\n", Bmemoryread);
	printf("Memory writes: %d\n", Bmemorywrite);
	printf("Cache hits: %d\n", Bcachehit);
	printf("Cache misses: %d\n", Bcachemiss);
	
	
	fclose(fp);
	return 0;
}
