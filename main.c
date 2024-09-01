/**
    @author Leviathenn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <git2.h>
#include <unistd.h>

void mainMenu();

char* concat(const char* str1, const char* str2) {
    // Calculate the total length of the concatenated string
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int totalLen = len1 + len2;

    // Allocate memory for the concatenated string (+1 for the null terminator)
    char* result = (char*)malloc((totalLen + 1) * sizeof(char));

    // Check if memory allocation was successful
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the first string into the result
    strcpy(result, str1);

    // Concatenate the second string onto the end
    strcat(result, str2);

    return result;
}


void anyKeyMenu(char *text){
    printMiddle(text);
    printf("Press \"1\" to exit.\n");
    
    int c;
    scanf("%d",&c);
    printf("%d\n",c);
    if(c != 1){
        scanf("%d",c);
    }else{
        mainMenu();
    }
}

void anyKeyExit(char *text){
    printMiddle(text);
    printf("Press \"1\" to exit.\n");
    
    int c;
    scanf("%d",&c);
    printf("%d\n",c);
    if(c != 1){
        scanf("%d",c);
    }else{
        clear_screen();
        exit(0);
    }
}

void createProject(){
    char* projectName = malloc(sizeof(char*));
    printf("Enter the project name: ");
    scanf("%s",projectName);
    mkdir(concat("/",concat(projectName,".git")),0700);
    git_repository *repo = NULL;
    git_remote *remote = NULL;
    git_libgit2_init();
    git_repository_init(&repo, concat("/",concat(projectName,".git")), 1);
    git_remote_create(&remote, repo, "origin", concat("/",concat(projectName,".git")));
    system(concat("setfacl -m u:newrepo:rwx ",concat("/",concat(projectName,".git"))));
    system(concat("setfacl -R -m u:git:rwx ",concat("/",concat(projectName,".git"))));
    anyKeyMenu("Repository Successfully Created!");
};
void clear_screen(){
    printf("\e[1;1H\e[2J");
}
void clear_area(int height){
    for (size_t i = 0; i < height; i++)
    {
        printf("\n");
    }
};

void printMiddle(char* text){
    //  printf( "\e[2J" );
    clear_screen();
    struct winsize sz;
    ioctl( 0, TIOCGWINSZ, &sz );
    int width = (sz.ws_col + sz.ws_row ) / 2 - strlen(text) - 2;

    int height = (sz.ws_row / 2);
    clear_area(height);
    for (int i = 0; i < width; i++)
    {
        printf(" ");
    }
    printf("%s",text);
    clear_area(height);
}

void removeProject(){
    char* projectName = malloc(sizeof(char*));
    printf("Enter Project Name: ");
    scanf("%s",projectName);
    system(concat("setfacl -m u:newrepo:rwx ",concat("/",concat(projectName,".git"))));
    system(concat("mv /",concat(concat(projectName,".git "),concat("/tmp/",concat(projectName,".git.old")))));
    anyKeyMenu("Repository Successfully Removed!");
}

void about(){
    anyKeyMenu("Made By Leviathenn");
}


void mainMenu(){
    clear_screen();
    printf("Please choose one.\n");
    printf("1: Create a repo.\n");
    printf("2: Delete a repo.\n");
    printf("3: About. \n");
    printf("4 : Exit.\n");
    int option;
    scanf("%d",&option);
    switch (option)
    {
        case 1:
            createProject();  
        break;
        case 2:
            removeProject();
            break;
        case 3:
            about();
            break;
        case 4:
            anyKeyExit("Thank you for using the Repo Portal!");
            break;
        default:
            printf("Invalid Option.\n");
            mainMenu();
        break;
    }
}




int main(){
    mainMenu();
    return 0;
}