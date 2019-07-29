#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <dlfcn.h>
#include "lib/complex_saz.h"

void Add_num(struct complex *num)
{
    printf("Real: ");
    scanf("%d", &num->real);
    printf("\nImaginary  ");
    scanf("%d", &num->imaginary);
    printf("\n");
}

void Print_complex(struct complex *num)
{
    printf("%d + %di\n", num->real, num->imaginary);
}

int main(int argc, char *argv[])
{
    ENTRY hash_tab, *found;
    int chose = 0, cycle = 1, i = 0, j = 0;
    struct complex num_1;
    struct complex num_2;
    hcreate(30);                                     //hash table for function
    char **ptr_str = calloc(argc-1, sizeof(char*));  //function names
    int **ptr_func = calloc((argc-1), sizeof(int*)); //function pointers
    void (*ptr)(struct complex *, struct complex *);

    for (i = 1; i < argc; i++)
    {
        char name[20];
        hash_tab.key = argv[i];
        hash_tab.data = argv[i];
        found = hsearch(hash_tab, FIND);
	if(found == NULL)
        {
            if(hsearch(hash_tab, ENTER) == NULL)
	    {
                fprintf(stderr, "error in hash table\n");
                exit(1);
            }
	    sprintf(name, "%s%s%s", "./lib/lib", argv[i], "_saz.so");
            ptr_func[j] = dlopen(name, RTLD_NOW);
            if (!ptr_func[j])
            {
                fprintf (stderr, "%s\n", dlerror());
                exit(1);
            }
            ptr_str[j] = calloc(4, sizeof(char));
            strcpy(ptr_str[j], argv[i]);
            j++;
        }
    }

    while(cycle)
    {
        printf("Chose command:\n");
        printf("------------\n");
        for(i = 0; i < j; i++)
        {
            printf("%d - %s\n", i, ptr_str[i]);
        }
        printf("%d - Exit\n------------\n", i);

        scanf("%d", &chose);
        if(chose < i)
        {
            printf("Input first number:\n");
            Add_num(&num_1);
            printf("Input second number:\n");
            Add_num(&num_2);
            ptr = dlsym(ptr_func[chose], ptr_str[chose]);
            if (dlerror() != NULL)
            {
                fprintf (stderr, "%s\n", dlerror());
                exit(1);
            }
            ptr(&num_1, &num_2);
            Print_complex(&num_1);
        }else{
            if(chose == i)
            {
                cycle = 0;
                break;
            }else{
                printf("\nERROR\n");
                cycle = 0;
            }
        }
        chose = i + 1;                  //error handling if no number is entered
    }
    for(i = 0; i < j; i++)
    {
        free(ptr_str[i]);
        dlclose(ptr_func[i]);
    }
    free(ptr_str);
    free(ptr_func);
    return 0;
}
