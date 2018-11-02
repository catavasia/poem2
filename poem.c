//created by Dana 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
const int NOTLETTER = -2;
char* ReadFile();
long long StringClean();
char** CreateMassivPtr();
void Swap();
int FindLetter(char s);
int CompareStr();
int main() 
{
	char* text = ReadFile();
	//printf("Text done");
	long long lines = StringClean(text);
	printf("%lld\n", lines);
	int i = 0;
	while(text[i] != '\n')
	{
		printf("%c", text[i]);
		i++;
	}
	printf("All done\n");
	char** nol = CreateMassivPtr(text, lines);
	printf("ptr ok\n");
	Swap(nol[1], nol[2]);
	for (int i = 0; i < lines ; i++)
	{
		printf("%s\n", *(nol+i));
	}
	qsort(nol, lines, sizeof(char*), CompareStr);
	printf( " qsort is OK\n");
	for (int i = 0; i < lines ; i++) // печать отсортированного текста
	{
		printf("%s\n", *(nol+i));
	}
	free(text);
	free(nol);
	return 0;
}

char* ReadFile()
{
	FILE *f = fopen("poem.txt", "rb");
	struct stat st = {};
	if(f == NULL) 
	{
		printf("Cannot open poem \n");
		return NULL;
	}
	stat("poem.txt", &st);
	long long a = st.st_size;
	printf("Size of the poem is: %lld\n", a);
	char *W = (char*) calloc(a, sizeof(char));
	if(fread(W, sizeof(char), a, f)!= a)
       {
        if(feof(f))
            printf(" End of file");
        else
            printf("File read error");
       }
    /*for ( int i = 0; i < a; i++)
    {
        printf("%c\n", W[i]);
    }*/
	fclose(f);
	return W;
}

long long StringClean(char* text)
{
	long long lines = 0;
	int i = 0;
	while( text[i] != '\0' )
	{
		if ((text[i] == '\n') && (text[i+1] != '\n'))
		{
				text[i] = '\0';
				lines++;
		}
				i++;
		
	}
	text[i+1] = '\n';
	return lines;
}

char** CreateMassivPtr( char* text, long long lines)
{
	char** nol = (char* *)calloc(lines, sizeof(char*));
	//printf("ok 1\n");
	nol[0] = &text[0];
	//printf("ok 2\n");
	int i = 1;
	int k = 1;
	while( (*(text+i) != '\n') && k < lines)
	{
			if ( text[i] == '\0' && (text[i+1] != '\0' || text[i+1] != '\n' ))
			{
				nol[k] = &text[i+1];
				//printf(" ptr is \n");
				k++;
				i++;
			}
			else
				i++;
	}
	//printf("massiv was created");
	return nol;
}

void Swap( char** s1, char** s2)
{
	char *temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

int FindLetter(char s)
{
	char Alph[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for ( int i = 0; i < 52; )
	{
		if ( s == Alph[i] )
			return i;
		i++;
	}
	return NOTLETTER;
}
	/*if( 65 <= s && s< = 90 || 97<= s && s <= 122)
		return 1;
	else
		return 0;*/
	
int CompareStr( const void* p1, const void* p2)
{
	const char *s1 = (char*)p1;
	const char *s2 = (char*)p2;
	while( *s1 != '\0' || *s2 != '\0')
	{
		while (FindLetter(*s1) == NOTLETTER)
		{
			s1++;
		}
			char c1 = FindLetter(*s1);
		while(FindLetter(*s2) == NOTLETTER)
		{
			s2++;
		}
			char c2 = FindLetter(*s2);
		if( c1 < c2 )
			return -1;
		if( c1 > c2)
			return 2;
		s1++;
		s2++;
	}
	/*if ( *s1 == '\0' && *s2 != '\0')
		return -1;
	if (*s2 == '\0' && *s1 != '\0')
		return 2;*/
		return 0;
}


			
			

