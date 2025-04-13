#include <stdlib.h>
#include <string.h>
#include "../stack/stack.h"
#include "stdio.h"
double math_parse(char *math_string[], double mem[], size_t math_str_len)
{
    OBJ *math_stack = NULL;
    for (size_t i = 0; i < math_str_len; i++)
    {
        double res;
        if (math_stack != NULL)
        {
            char subs[2] = {math_string[i][0], 0};
            char* isnum = strstr("0123456789", subs);
            if (isnum)
            {
                res = strtod(math_string[i], NULL);
            }
            else
            {
                double a = math_stack->data;
                math_stack = pop(math_stack);
                

                if (!strcmp(math_string[i], "!"))
                {   
                    
                    res = !a;
                }
                else if (!strcmp(math_string[i], "СЧИТАТЬ"))
                {
                    res = mem[(int)a];
                }
                else
                {
                    double b;
                    if (math_stack == NULL)
                    {
                        printf("математическая ошибка");
                        exit(1);
                    }
                    else
                    {
                        b = math_stack->data;
                        math_stack = pop(math_stack);
                    }

                    if (!strcmp(math_string[i], "+"))
                    {
                        res = b + a;
                    }

                    else if (!strcmp(math_string[i], "-"))
                    {
                        res = b - a;
                    }

                    else if (!strcmp(math_string[i], "*"))
                    {
                        res = b * a;
                    }

                    else if (!strcmp(math_string[i], "/"))
                    {
                        res = b / a;
                    }

                    else if (!strcmp(math_string[i], "%"))
                    {
                        res = (int)b % (int)a;
                    }

                    else if (!strcmp(math_string[i], "//"))
                    {
                        res = (int)b / (int)a;
                    }

                    else if (!strcmp(math_string[i], "="))
                    {
                        res = (b == a);
                    }

                    else if (!strcmp(math_string[i], "!="))
                    {
                        res = (b != a);
                    }

                    else if (!strcmp(math_string[i], ">"))
                    {
                        res = (b > a);
                    }

                    else if (!strcmp(math_string[i], "<"))
                    {
                        res = (b < a);
                    }

                    else if (!strcmp(math_string[i], ">="))
                    {
                        res = (b >= a);
                    }

                    else if (!strcmp(math_string[i], "<="))
                    {
                        res = (b <= a);
                    }

                    else if (!strcmp(math_string[i], "ИЛИ"))
                    {
                        res = (b || a);
                    }
                    else if (!strcmp(math_string[i], "И"))
                    {
                        res = (b && a);
                    }
                }
            }
        }
        else
        {
            res = strtod(math_string[i], NULL);
        }
        math_stack = push(math_stack, res);
    }
    double stack_top = math_stack->data;
    free_stack(math_stack);
    return stack_top;
}