#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<regex.h>
#define PRINT() print(__LINE__,__FUNCTION__)
  int debug_level = 0;

int print(int line,const char *function){
time_t tm;
    char* curDateTime;
    time(&tm);
curDateTime = ctime(&tm);
   printf("%s",curDateTime);
    printf("line No.|%d| function |%s|",line,function);
    return 0;
    }
int check_File(char *arg,char *filename){
int fd = access(filename, F_OK); 
int fd1 = access(filename, R_OK); 

if(fd==-1){

fprintf(stdout,"error file does not exist\n");
}

else if(fd1==-1){

fprintf(stdout,"does not have read permission\n");


}
else {

fprintf(stdout,"files exist and have read permission\n");
}

return 0;
}
void usage(char *err){

fprintf(stdout,"%s\n",err);
fprintf(stdout,"Usage :\n");
 fprintf(stdout,"  c_sort_tutorial -f <in_file_name> -D <debug level>\n");
fprintf(stdout,"   -f  : Should be given with the file name .\n");
 fprintf(stdout ,"   -D  : Optional parameter to enable debug log by specifying debug level. 0 mean debug off. 1 and 2 are debug level for debug on.\n");
   exit(-1);

}


typedef struct {
    char name[50];
    char number[50];
} Student;

int comparator(const void *a, const void *b) {
    const Student *studentA = (const Student*) a;
    const Student *studentB = (const Student*) b;

    return strcmp(studentA->name, studentB->name);
   
}

int count_records(char *arg1,char *arg,char *filename){

    FILE *fp;
    char buffer[500];
    regex_t regex;
    int reti, read, records = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"Error: file is not present\n");
        return 1;
    }

    FILE *out = fopen("student.csv.sorted", "w");
    if (out == NULL) {
        fprintf(stderr, "Error: cannot create output file\n");
        fclose(fp);
        return 1;
    }

    Student students[100];

    reti = regcomp(&regex, "^[a-zA-Z]+,[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Error: could not compile regex\n");
        return 1;
    }    
          
if(*arg=='0'){

    return 0;
}



    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = 0; 
        reti = regexec(&regex, buffer, 0, NULL, 0);
        if (!reti) {
            read = sscanf(buffer, "%49[^,],%s", students[records].name, students[records].number);
            if (read == 2) {
                records++;
            } else {
                printf("Error: invalid record format: %s\n", buffer);
            }
        } else {
            printf("Error: invalid record format: %s\n", buffer);
        
    }
    }
    fclose(fp);
if(*arg=='1'){
    
   int run= printf("%d valid records read\n", records);
   return run;
}


printf("%d valid records read\n", records);
    printf("\nBEFORE sorting:\n\n");
    for (int i = 0; i < records; i++) {
        printf("%s,%s\n", students[i].name, students[i].number);
    }

    qsort(students, records, sizeof(Student), comparator);

    printf("\nAFTER sorting:\n\n");
  
    for (int i = 0; i < records; i++) {
        snprintf(buffer, 500, "%s,%s\n", students[i].name, students[i].number);
        printf("%s", buffer);
       
        fprintf(out, "%s", buffer);

    }
    

    
    fclose(out);
    regfree(&regex);

    return 0;
}
int check_argument(int argc, char **argv) {
    int opt;
    int count = 0;
  


    while ((opt = getopt(argc, argv, "f:D:")) != -1) {

        switch (opt) {
            case 'f':
          
                if (count > 0)
                    usage("Error: -f option is specified more than once.");
                count++;
             
                break;
                case 'D':
                
                debug_level=0;
     		if (strcmp(optarg, "0") == 0) {
                    debug_level = 0;
                } else if (strcmp(optarg, "1") == 0) {
                    debug_level = 1;
                } else if (strcmp(optarg, "2") == 0) {
                    debug_level = 2;
                } else {
                    usage("Error: Invalid debugging level.");
                }
                break;
                
                
        
                
            default:
                usage("Error: Invalid arguments.");
                break;
        
    }
    }

    if (count == 0) {
        fprintf(stderr, "Error: -f option is mandatory.\n");
        
    }

    switch (debug_level) {
        case 0:
        freopen("debug.log", "w", stdout);
            PRINT();
            printf("Debugging level 0: no debugging messages will be printed.\n");
            break;
        case 1:
            freopen("debug.log", "w", stdout);
            PRINT();
            printf("Debugging level 1: some debugging messages will be printed.\n");
            break;
        case 2:
            freopen("debug.log", "w", stdout);
            PRINT();
            printf("Debugging level 2: all debugging messages and errors will be printed.\n");
            break;
        default:
            break;
    }

    return 0;
}

int main (int argc, char *argv[]){ 

check_File(argv[4],argv[2]);
check_argument(argc, argv);
count_records(argv[3],argv[4],argv[2]);


return 0; 
}
