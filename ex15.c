#include <stdio.h>

int main(int argc, char *argv[])
{
    //create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    printf("sizeof(ages): %ld, sizeof(int): %ld\n", sizeof(ages), sizeof(int));
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //printf("sizeof(ages): %d. sizeof(names): %d. sizeof(&ages): %d \n", sizeof(ages), sizeof(names),sizeof(&ages));

    // first way using indexing
    for (i = 0; i < count; i++)
    {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    // set up the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    /*printf("My little tests on cur_age:\n");
    printf("&ages = %ld\n", &ages);
    printf("cur_age = %ld\n", cur_age);
    printf("cur_age + 1 = %ld\n", cur_age + 1);
    printf("---\n");
    printf("My little tests on cur_name:\n");
    printf("&names = %ld\n", &names);
    printf("cur_name = %ld\n", cur_name);
    printf("cur_name + 1 = %ld\n", cur_name + 1);
    printf("---\n");
    printf("My little test on cur_name one char at a time:\n");
    for (i = 0; i < 10; i++)
    {
        printf("cur_name[0][%d] = %c; cur_name  = %ld\n",
           i, cur_name[0][i], ((long)cur_name)+i);
    }
    printf("---\n");
    printf("My further testing of pointer addresses:\n");
    printf("%%p of names: %p. &names of names: %ld\n", names, &names);
    printf("%%p of names[0]: %p. &names[0] of names: %ld\n", 
       names[0], &names[0]);
    printf("%%p of names[1]: %p. &names[1] of names: %ld\n", 
       names[1], &names[1]);
    printf("---\n");*/
    // second way using pointers
    for (i = 0; i < count; i++)
    {
        printf("%s is %d years old.\n", 
           *(cur_name + i), *(cur_age + i) );
    }

    printf("---\n");

    //third way, pointers are just arrays
    for (i = 0; i < count; i++)
    {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");


    //Before we change the pointers lets have a look at the pointer addresses
    /*for (i = 0; i < count; i++)
    {
        printf("%%p of names[%5$d]: %p, %%p of cur_name[%5$d]: %p, %%p of ages[%5$d]: %p, %%p of cur_age[%5$d]: %p\n",
            names[i], cur_name[i], &ages[i], &cur_age[i], i);
    }

    printf("---\n");*/

    //fourth way with pointer in a stupid complex way
    for ( cur_name = names, cur_age = ages;
            (cur_age - ages) < count; cur_name++, cur_age++)
    { 
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    return 0;
}
