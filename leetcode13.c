#include <stdio.h>
#include <stdlib.h>

int romanToInt(char *s)
{
    int result = 0;

    int len;
    for (len = 0; s[len] != '\0'; len++)
        ;

    for (int i = 0; i < len; i++)
    {
        if ((i + 1 < len) && (s[i] == 'I' || s[i] == 'X' || s[i] == 'C'))
        {
            switch (s[i + 1])
            {
            case 'V':
                if (s[i] == 'I')
                {
                    i++;
                    result += 4;
                }
                else
                {
                    goto cornercase;
                }
                break;
            case 'X':
                if (s[i] == 'I')
                {
                    i++;
                    result += 9;
                }
                else
                {
                    goto cornercase;
                }

                break;

            case 'L':
                if (s[i] == 'X')
                {
                    i++;
                    result += 40;
                }
                else
                {
                    goto cornercase;
                }
                break;
            case 'C':
                if (s[i] == 'X')
                {
                    i++;
                    result += 90;
                }
                else
                {
                    goto cornercase;
                }
                break;

            case 'D':
                if (s[i] == 'C')
                {
                    i++;
                    result += 400;
                }
                else
                {
                    goto cornercase;
                }
                break;
            case 'M':
                if (s[i] == 'C')
                {
                    i++;
                    result += 900;
                }
                else
                {
                    goto cornercase;
                }
                break;

            default:
                goto cornercase;
            }
        }
        else
        {
        cornercase:
            switch (s[i])
            {
            case 'I':
                result += 1;
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                result += 10;
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                result += 100;
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;

            default:
                break;
            }
        }
    }

    return result;
}