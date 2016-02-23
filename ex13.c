#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    //print each character in the two dimensional array  argv individually
    for (i = 0; i < 20; i++)
    {
        printf("%c\n", argv[0][i]);
    }

    //let's make our own array of strings
    char *states[] = { "California", "Oregon", "Washington", "Texas"};

    argv[1] = states[2];
    states[3] = argv[0];
    
    
    //go through each string in argv
    //why am I skipping argv[0]?
    for (i = 1; i < argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
    }
    int num_states = 4;

    for (i = 0; i < num_states; i++)
    {
        printf("state %d: %s\n", i, states[i]);
    }

    

    //print each character in the two dimensional array states individually
    for (i = 0; i < 20; i++)
    {
        printf("%c\n", states[0][i]);
    }
    //print each character in the two dimensional array argv individually
    for (i = 0; i < 20; i++)
    {
        printf("%c\n", argv[0][i]);
    }
    
    char test[] = "this a test";
    char testtoo[] = { 't', 'e', 's', 't','t', 'o', 'o', '\0' };
    char *test3 = "test three";
    printf("test: %s\n", test);
    printf("testtoo: %s\n", testtoo);
    printf("test3: %s\n", test3);

    return 0;
}
