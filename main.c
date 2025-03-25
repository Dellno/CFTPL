#define _CRT_SECURE_NO_WARNINGS
#define true 1
#define false 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "math_parser/math_parser.h"

typedef struct key_value
{
    int value;
    char *key;
    struct key_value *next_key;
} KEY_VALUE;

int get_value(KEY_VALUE *top, char *key)
{
    int flag = 0;
    int res;
    while (top != NULL)
    {
        if (!strcmp(top->key, key))
        {
            res = top->value;
            flag = 1;
            break;
        }
        top = top->next_key;
    }
    if (!flag)
    {
        printf("Ошибка! Точка перехода программы <%s> отсутствует", key);
        exit(1);
    }
    return res;
}
KEY_VALUE *add_key(KEY_VALUE *top, char *key, int value)
{
    KEY_VALUE *ptr = malloc(sizeof(KEY_VALUE));
    ptr->key = key;
    ptr->value = value;
    ptr->next_key = top;
    return ptr;
}

KEY_VALUE *point_dict = NULL;

const int buffersize = 4092;

double memory[512];
int memory_cursor = 0;
int attachments_count = 0;
int main(int argc, char *argv[]) 
{
    setlocale(LC_CTYPE, "ru_RU.UTF-8");
    if (argc == 1)
    {
        printf("Ошибка! Файл не был указан!");
        return 1;
    }
    if (argc == 3)
    {   
        if (!strcmp(argv[3], "--memory"))
        {
        double* memory = malloc(sizeof(double)* atoi(argv[4]));
        }
    }
    else
    {
        double memory[512];
    }
    FILE *file = fopen(argv[1], "r");
    char buf[8192];
    if (file == NULL)
    {
        perror("Ошибка! Файл не найден!");
        return 1;
    }
    char c;
    int string_count = 1;
    char **pre_program;
    pre_program = (char **)malloc(1 * sizeof(char *));
    // построчное чтение из файла
    while ((fgets(buf, 8192, file)) != NULL)
    {
        pre_program = (char **)realloc(pre_program, string_count * sizeof(char *));
        int i = 0;
        do
        {
            i += 1;
        } while (buf[i] != '\n');
        buf[i] = '\0';
        buf[i + 1] = (char)0;
        int length = strlen(buf);
        pre_program[string_count - 1] = (char *)malloc(length + 1);
        strcpy(pre_program[string_count - 1], buf);
        string_count += 1;
    }
    fclose(file);

    // парсинг строк на отдельные инструкции
    char ***program;
    program = (char ***)malloc((string_count - 1) * sizeof(char **));
    for (int i = 0; i < string_count - 1; i++)
    {
        char buf[128];
        int j = 0;
        int arg_len = 0;
        int arg_count = 0;
        char **commad;
        commad = (char **)malloc(1 * sizeof(char *));
        int ignore_space = 0;
        int new_point = 0;
        while (true)
        {
            if ((pre_program[i][j] == ' ' && !ignore_space) || pre_program[i][j] == '\0')
            {
                commad = (char **)realloc(commad, (arg_count + 1) * sizeof(char *));
                buf[arg_len] = '\0';
                int length = strlen(buf);
                
                commad[arg_count] = (char *)malloc(length + 1);
                strcpy(commad[arg_count], buf);
                // для инструкций с строчными аргументами
                if (!strcmp(commad[arg_count], "СТРОКА"))
                {
                    ignore_space = 1;
                }
                if (new_point)
                {
                    point_dict = add_key(point_dict, commad[arg_count], i);
                }
                if (!strcmp(commad[arg_count], "ТОЧКА"))
                {
                    new_point = 1;
                }

                arg_count += 1;
                arg_len = 0;
                if (pre_program[i][j] == '\0')
                {
                    commad = (char **)realloc(commad, (arg_count + 1) * sizeof(char *));
                    int length = strlen("КЦ");
                    commad[arg_count] = (char *)malloc(length + 1);
                    strcpy(commad[arg_count], "КЦ");
                    break;
                }
            }
            else
            {

                buf[arg_len] = pre_program[i][j];
                arg_len++;
            }
            j++;
        }
        program[i] = commad;
    }
    
    // собственно сама интерпретация.
    for (int program_cursor = 0; program_cursor < string_count - 1; program_cursor++)
    {
        if (program[program_cursor][0][0] == '_')
        {
            if (attachments_count < strlen(program[program_cursor][0]))
            {
                continue;
            }
            else if (attachments_count > strlen(program[program_cursor][0]))
            {
                attachments_count = strlen(program[program_cursor][0]);
            }
        }
        else if (attachments_count > 0)
        {
            attachments_count = 0;
        }

        // КУРСОР
        if ((!strcmp(program[program_cursor][0], "КУРСОР")) || (!strcmp(program[program_cursor][1], "КУРСОР")))
        {
            int d = !strcmp(program[program_cursor][1], "КУРСОР");
            int ln = 0;
            while (strcmp(program[program_cursor][1+ln+d], "КЦ"))
            {
                ln++;
            }
            char **funargs;
            funargs = (char**)malloc(ln*sizeof(char*));
            for (int i = 0; i < ln; i++)
            {
                int length = strlen(program[program_cursor][1+i+d]);
                funargs[i] = (char*)malloc(length + 1);
                strcpy(funargs[i], program[program_cursor][1+i+d]);
            }
            double arg = math_parse(funargs, memory, ln);
            memory_cursor = (int)arg;
            for (int i = 0; i < ln; i++)
            {
                free(funargs[i]);
            }
            free(funargs);
        }
        // СЧЁТ 
        else if ((!strcmp(program[program_cursor][0], "СЧЁТ")) || (!strcmp(program[program_cursor][1], "СЧЁТ")))
        {
            int d = !strcmp(program[program_cursor][1], "СЧЁТ");
            int ln = 0;
            while (strcmp(program[program_cursor][1+ln+d], "КЦ"))
            {
                ln++;
            }
            char **funargs;
            funargs = (char**)malloc(ln*sizeof(char*));
            for (int i = 0; i < ln; i++)
            {
                int length = strlen(program[program_cursor][1+i+d]);
                funargs[i] = (char*)malloc(length + 1);
                strcpy(funargs[i], program[program_cursor][1+i+d]);
            }
            double arg = math_parse(funargs, memory, ln);
            memory[memory_cursor] = arg;
            for (int i = 0; i < ln; i++)
            {
                free(funargs[i]);
            }
            free(funargs);
        }
        // ЕСЛИ
        else if ((!strcmp(program[program_cursor][0], "ЕСЛИ")) || (!strcmp(program[program_cursor][1], "ЕСЛИ")))
        {
            int d = !strcmp(program[program_cursor][1], "ЕСЛИ");
            int ln = 0;
            while (strcmp(program[program_cursor][1+ln+d], "КЦ"))
            {
                ln++;
            }
            char **funargs;
            funargs = (char**)malloc(ln*sizeof(char*));
            for (int i = 0; i < ln; i++)
            {
                int length = strlen(program[program_cursor][1+i+d]);
                funargs[i] = (char*)malloc(length + 1);
                strcpy(funargs[i], program[program_cursor][1+i+d]);
            }
            double arg = math_parse(funargs, memory, ln);
            
            if (arg)
            {
                attachments_count++;
            }

            for (int i = 0; i < ln; i++)
            {
                free(funargs[i]);
            }
            free(funargs);
        }
        // ВВОД
        else if ((!strcmp(program[program_cursor][0], "ВВОД")) || (!strcmp(program[program_cursor][1], "ВВОД")))
        {
            double arg;
            scanf("%lf", &arg);
            memory[memory_cursor] = arg;
        }
        // ПЕРЕЙТИК
        else if ((!strcmp(program[program_cursor][0], "ПЕРЕЙТИК")) || (!strcmp(program[program_cursor][1], "ПЕРЕЙТИК")))
        {
            int d = !strcmp(program[program_cursor][1], "ПЕРЕЙТИК");
            program_cursor = get_value(point_dict, program[program_cursor][1+d]);
        }
        // ВЫВОД
        else if ((!strcmp(program[program_cursor][0], "ВЫВОД")) || (!strcmp(program[program_cursor][1], "ВЫВОД")))
        {
            int d = !strcmp(program[program_cursor][1], "ВЫВОД");
            if (!strcmp(program[program_cursor][1+d], "СИМВОЛЫ"))
            {
                int str_len = 0;
                while ((char)memory[memory_cursor + str_len] != '\0')
                {
                    str_len++;
                }
                char* buf = (char*)malloc(str_len);
                for (int i = 0; i < str_len; i++)
                {
                    buf[i] = memory[memory_cursor+i];
                }
                printf("%s", buf);    
            }
            else if (!strcmp(program[program_cursor][1+d], "ЦЕЛ"))
            {
                double arg = memory[memory_cursor];
                printf("%d\n", (int)arg); 
            }

            else 
            {
            double arg = memory[memory_cursor];
            printf("%lf\n", arg); 
            }
        }
        // ЦЕЛ (отбросить дробную часть)
        else if ((!strcmp(program[program_cursor][0], "ЦЕЛ")) || (!strcmp(program[program_cursor][1], "ЦЕЛ")))
        {
            memory[memory_cursor] = (int)memory[memory_cursor];
        }
        // СТРОКА
        else if ((!strcmp(program[program_cursor][0], "СТРОКА")) || (!strcmp(program[program_cursor][1], "СТРОКА")))
        {
            int d = !strcmp(program[program_cursor][1], "СТРОКА");
            int cpcursor = memory_cursor;
            while (program[program_cursor][1+d][cpcursor-memory_cursor] != '\0')
            {
                memory[cpcursor] = program[program_cursor][1+d][cpcursor-memory_cursor];
                cpcursor += 1;
            }
            memory[cpcursor] = program[program_cursor][1+d][cpcursor-memory_cursor];
        }
        else if ((!strcmp(program[program_cursor][0], "СТРОКА")) || (!strcmp(program[program_cursor][1], "СТРОКА")))
        {
            exit(0);
        }

        else if ((!strcmp(program[program_cursor][0], "ВВОДСТРОКИ")) || (!strcmp(program[program_cursor][1], "ВВОДСТРОКИ")))
        {
            int d = !strcmp(program[program_cursor][1], "ВВОДСТРОКИ");
            int cpcursor = memory_cursor;
            int input_buf_len = 128;
            if (strcmp(program[program_cursor][1+d], "КЦ"))
            {
                input_buf_len = atoi(program[program_cursor][1+d]);
            }
            char* input_buf = (char*)malloc(sizeof(char) * input_buf_len);
            fgets(input_buf, input_buf_len, stdin);
            while (input_buf[cpcursor-memory_cursor] != '\0')
            {
                memory[cpcursor] = input_buf[cpcursor-memory_cursor];
                cpcursor += 1;
            }
            memory[cpcursor] = input_buf[cpcursor-memory_cursor];
        }
    }

    return 0;
}