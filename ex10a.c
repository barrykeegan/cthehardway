#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("ERROR: You need at least one argument.\n");
        //this is how you abort a program
        return 1;
    }

    int i = 0, j = 0;
    char letter = '\0';
    for (j = 1; j < argc; j++)
    {
        printf("Argument %d:\n", j);
        for (letter = '\0', i = 0; argv[1][i] != '\0'; i++)
        {
            letter = argv[j][i];
            if (letter >= 'A' && letter <= 'Z')
            {
                letter += ('a'-'A');
            }

            switch (letter)
            {
              case 'a':
                printf("%d: 'a'\n", i);
                break;
              case 'e':
                printf("%d: 'e'\n", i);
                break;
              case 'i':
                printf("%d: 'i'\n", i);
                break;
              case 'o':
                printf("%d: 'o'\n", i);
                break;
              case 'u':
                printf("%d: 'u'\n", i);
                break;
              case 'y':
                if (i > 2)
                {
                    //it's only sometimes Y
                    printf("%d: 'y'\n", i);
                    break;
                }
                else
                {
                    printf("%d: %c is not a vowel\n", i, letter);
                    break;
                }
                //break;
              default:
                printf("%d: %c is not a vowel\n", i, letter);

            }
        }
        printf("\n");
    }
    return 0;
}

