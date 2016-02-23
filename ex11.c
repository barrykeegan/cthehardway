#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int teststr = 0;

    char name[4]  = { 'a' };
    int numbers[4] = {530};

    //sizeof int
    //printf("Size of int: %d\n", sizeof(teststr));

    //first, print them out raw
    printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], 
       numbers[3]);
   
    printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

    printf("name: %s\n", name);

    //print teststr hidden in an int
    //printf("teststr: %s\n", &teststr);
    
    //set up numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    //set up name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    memcpy(&teststr, name, 4);

    // then print them out initialised
    printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2], 
       numbers[3]);
    
    printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);


    printf("name: %s\n", name);
    
    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
       another[0], another[1], another[2], another[3]);

    //pointer test
    printf("teststr: %d\n", teststr);
    printf("&teststr: %ld\n", &teststr);
    return 0;
}
