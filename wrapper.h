
//A wrapper is collection of filepath in linkedlist form

struct Filelist
{
  struct Filelist* next;
  char* path; 	
};
typedef struct Filelist Filelist;

struct Wrapper
{
	Filelist* filelist1;
	int initialized;
};
typedef struct Wrapper Wrapper;

//Add a file path to wrapper char* is file path
void wrapper_addfile(Wrapper* ,char*);

//When we add files to a wrapper it in form of a stack i.e LIFO,
//So the wrapper needed to be reverse in order to work properly		
void wrapper_reverse(Wrapper*);

//Display contents of wrapper
void wrapper_display(Wrapper*);

/*
usage
Wrapper* wrapper1=(Wrapper*)malloc(sizeof(Wrapper));
wrapper_addfile(wrapper1,"File1");
wrapper_addfile(wrapper1,"File2");
wrapper_display(wrapper1);
wrapper_reverse(wrapper1);
wrapper_display(wrapper1);
*/	
