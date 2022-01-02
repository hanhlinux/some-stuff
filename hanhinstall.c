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
	
/*Function for checking path*/
int check_path(char a[], char b[], int c) {
	char bruh[2048];
	int if_found;
	struct stat buf;
	strcpy(bruh, a);
	if (b[0] == '\0') {
		strcat(bruh, " is empty!");
		err(bruh);
		return c;
		}
		
	if_found=stat(b, &buf);
	if (if_found == -1){
		strcat(bruh, " not found!");
		err(bruh);
		return c; 
		}
		return 0;
	}
		
int INSTALL(char a[]) {
	printf("%s", a);
	char *token = strtok(a, " ");
	while ( token != NULL) {
		char template[2048] = "/tmp/pachanh/tmp.XXXXXX";
		char header[2048] = "";
		strcpy(token, header);
		strcat(header, " pre-install");
		mkdtemp(template);
		untar(template, header);
		
		untar(template, token);
		token = strtok(NULL, " ");
		}
		return 0;
	}  
	
	
int main(int argc, char **argv)
{
	/* Export some important variables */
	int opt;
	int install = 0; 
	int remove = 0 ;
	int sync = 0; 
	int Snapshot = 0; 
	int find = 0; 
	int nodeps=0;
	int exitcode=0;
	char packages[2000];
	char ROOT[2048]= "";
	char download[2048] ="";
	char mirror[2048]="";
	char type[2048]="";
	
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
			install=1;
			break;
			
			case 'r': 
			remove=1;
			break;
			
			case 's': 
			sync=1;
			break;
			
			case 'S':
			Snapshot=1;
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
	if(packages[0] == '\0'){
		err("Packages are empty!");
		exitcode=1;
		}
		
	exitcode=check_path("Root", ROOT,1);
	exitcode=check_path("Mirror directory", mirror, 1);
	if (download[0] == '\0') {
		err("Download command is empty!");
		exitcode=1;
		}
	
	if (exitcode == 1) {
		die("Exit due to previous error!", exitcode);
		}
		
		INSTALL(packages);
}

