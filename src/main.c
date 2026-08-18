#include <stdio.h>

int main(void)
{
    char input[1024];

    while (1)
    {
        printf("solaymane-shell > ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        printf("You typed: %s", input);
    }

    return (0);
}