#include<regex.h>     
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"node.h"
#include"regexfile.h"
#include"wrapper.h"
#include"recurse.h"


int has_char(char* str,char ch)
{
	while(*str !='\0')
	{
		if (*str == ch) return 1;
		str++; 
	}
	return 0;
}

char* extarct_word(char* str,char ch)
{
	printf("\tHFILE %s\n",str);
	char* start;
	char* end;
	
	int count=0;
	while(*str !='\0')
	{
		if (*str == ch && count== 0 ) start=str;
		if (ch=='<') 
		{
			if(*str=='>')
			{
				 end=str;
				 break;
			}
		}
		if (ch=='"')
		{
			if(*str=='"' && count==0) count++;
			else if (*str=='"' && count==1) end=str;
		}
		str++;
	}
	//printf("%c",*start);	
	//printf("%c",*end);
	char* ret = (char*)malloc(sizeof(char)*(end-start));
	strncpy(ret,start+1,end-start-1);
	ret[end-start-1]='\0';
	//printf("Return value %s\n",ret);	
	return ret;	
}

int regexfile(node* node_obj,char* filename)
{   
	regex_t regex;
	int reti;
	char msgbuf[100];
	/* Compile regular expression For #include Directive*/ 
   
        reti = regcomp(&regex, "^ *#include", 0);
        if( reti ){ fprintf(stderr, "Could not compile regex\n"); exit(1); }

	char str[200];
	FILE *fp;
	fp = fopen(filename,"r");
	if(!fp) return 1; // bail out if file not found
   	while(fgets(str,sizeof(str),fp) != NULL)
  	{
		// strip trailing '\n' if it exists
        	int len = strlen(str)-1;
        	if(str[len] == '\n') 
      	     		str[len] = 0;
		/* Execute regular expression */
        	reti = regexec(&regex, str, 0, NULL, 0);
	        if( !reti ){
       		     printf("%s\n", str);
		     if (has_char(str,'<'))
		     {		printf("Contains Include File\n");
			        char* header_file = extarct_word(str, '<');
				printf("Adding Header_File :- %s\n",header_file);
				node_ops.add_element(node_obj,header_file);		
		     }
		     else if (has_char(str,'"'))
		     {
				char* cwd=gnu_getcwd();
			        strcat(cwd,"/");	
				printf("Contains Local File\n");
			        char* header_file = extarct_word(str, '"');
				printf("Adding Header_File :- %s\n",header_file);
				node_ops.add_element(node_obj,strcat(cwd,header_file));	
		     }
		     
	        }
	        else if( reti == REG_NOMATCH ){
        	      //  puts("No match");
	        }
        	else{
                	regerror(reti, &regex, msgbuf, sizeof(msgbuf));
	                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        	        exit(1);
	        }
       }
       node_ops.display_element(node_obj);
       fclose(fp);

/* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);

}

