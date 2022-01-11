#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void help() {
	printf("hanhinstall - Hanh Linux package manager\n");
	printf("Usage: hanhinstall [Action] [Options]\n");	
	printf("Action\n"); 
	printf("-s                        Sync database from remote \n");
	printf("-i                        Install packages <file>\n");
	printf("-r                        Remove packages\n");
	printf("-f                        Search for installed packages\n"); 
	printf("-g <path>                 Generate the packages build files\n");
	printf("-S                        Build a snapshot\n");
	printf("Options \n");
	printf("-h                        Print this message\n");
	printf("-v                        Print version\n");
	printf("-R <path>                 Change root directory\n");
	printf("-d <command>              Use another download command\n");
	printf("-m <path>                 Use specified mirror directory\n");
	printf("-t [info,filelist,header] Specify file(s) to search\n");
	printf("-D                        Disable dependencies check\n");
	printf("For any questions, please consider asking on GitHub: https://github.com/hanh-linux/pachanh\n");
	exit(0);
	}
	
void printver(){
	char version[] = "1.3.2";
	printf("%s\n", version);
	exit(0);
	}

/*ERROR message*/
void err(char x[]){
	printf("ERROR: %s\n", x);
	}

void die (char x[], int y) {
	err(x);
	exit(y);
	}

/*Check exitcode*/
void check_code(int a) {
	if (a != 0) {
		die("Exit program due to previous error", 1);
		}
	}
/*Check if a string is empty*/	
int check_empty(char a[], char b[]) {
	char bruh[2048];
	strcpy(bruh, b);
	if (a[0] == '\0') {
		strcat(bruh, " is empty!\n");
		printf("%s", bruh); 
		return 1;
		}
	return 0;
	}
	
/*Function for checking path*/
int check_path(char a[], char b[], int c) {
	char bruh[2048];
	int if_found;
	struct stat buf;
	strcpy(bruh, a);
	if (b[0] == '\0') {
		strcat(bruh, " is empty!\n");
		err(bruh);
		return c;
		}
		
	if_found=stat(b, &buf);
	if (if_found == -1){
		strcat(bruh, " not found!\n");
		err(bruh);
		return c; 
		}
		return 0;
	}

/*Function for unpacking packages*/
int untar(char a[], char b[]) {
	char command[2048] = "";
	strcat(command, "tar -C ");
	strcat(command, a);
	strcat(command, " -xf ");
	strcat(command, b);
	int c = system(command);
	return c;
	}
			
int INSTALL(char a[], char b[], int c) {
	char *token = strtok(a, " ");
	while ( token != NULL) {
		// Prepare to unpack
		int code = 0; 
		char template[2048] = "/tmp/tmp.XXXXXX";
		char header[2048] = "";
		strcpy(header, token);
		strcat(header, " pre-install");
		
		// Create temporary directory so we can get the header
		mkdtemp(template);
		code = untar(template, header);
		check_code(code);
		if (c == 0) {
			
			}
		code = untar(b, token);
		check_code(code);
		token = strtok(NULL, " ");
		}
		return 0;
	}  
	
	
int main(int argc, char **argv)
{	
	/*Actions: 
	 * -i 		install 			= 1
	 * -r 		remove 		= 2
	 * -s 		sync 				= 3 
	 * -S 		Snapshot 	= 4  
	 * -f 		find				=	5
	 * Multiple actions will result in an override*/
	int action = 0;
	int nodeps=0; // enable checking dependencies by default
	
	// General variables will be used from command-line 
	char packages[2000]="";
	char ROOT[2048]= "";
	char download[2048] ="";
	char mirror[2048]="";
	char type[2048]="";
		
	// Misc
	int exitcode=0;
	int opt;
	
	/* Working with command-line argument. Here we use POSIX getopt() function. */
	while ((opt = getopt(argc, argv, "irsSfhvR:d:m:t:D")) != -1){
		switch (opt) {
			
			case 'h': 
			help();
			break;
			
			case 'v':
			printver();
			break;
			
			case 'i':
			action=1;
			break;
			
			case 'r': 
			action=2;
			break;
			
			case 's': 
			action=3;
			break;
			
			case 'S':
			action=4;
			break;
			
			case 'f': 
			action=5;
			break;
			
			case 'D': 
			nodeps=1;
			break;
						
			case 'R': 
			strcpy(ROOT, optarg);
			break;
			
			 case 'd': 
			 strcpy(download, optarg);
			 break;
			
			case 'm': 
			strcpy(mirror, optarg);
			break;
			
			case 't':
			strcpy(type, optarg);
			break;
			
			case '?':
			printf("Please use \"hanhinstall -h\" for more information\n");
			return 1;
			}
	}


	for (; optind < argc; optind++){
		strcat(packages, argv[optind]);
		strcat(packages, " ");
		}
		
	/*Check for command line error*/	
	exitcode = check_empty(packages, "Packages");
	check_code(exitcode);
	exitcode= check_empty(download, "Download command");
	check_code(exitcode);
	exitcode=check_path("Root", ROOT, 1);
	check_code(exitcode);
	exitcode=check_path("Mirror directory", mirror, 1);
	check_code(exitcode);
	
	switch(action) {
		
		case 0: 
		die("No action is specified! Please specify one", 1);
		break;
		
		case 1:
		INSTALL(packages, ROOT, nodeps);
		break;
		
		case 2: 
		break;
		
		case 3:
		break;
		
		case 4:
		break;
		
		case 5:
		break;
		
				}		
}

