// Problem link: https://noj.tw/problem/350

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUERY_CNT 5
#define NAME_LEN 128
#define DATE_LEN 16
#define MAX_MSG_LEN 1024

int main()
{
    char log_filename[NAME_LEN];
    scanf("%s", log_filename);
    FILE *p_log = fopen(log_filename, "r");
    if (p_log == NULL)
    {
        fprintf(stderr, "Failed to open log file %s\n", log_filename);
        return 1;
    }
    // Read queries
    int query_cnt = 0;
    char query_date[MAX_QUERY_CNT][DATE_LEN] = {};
    FILE *p_outputs[MAX_QUERY_CNT];
    while (scanf("%s", query_date[query_cnt]) != EOF)
    {
        char output_filename[NAME_LEN] = {};
        strcpy(output_filename, log_filename);
        strcat(output_filename, "-");
        strcat(output_filename, query_date[query_cnt]);
        FILE *p_output = fopen(output_filename, "w");
        if (p_output == NULL)
        {
            fprintf(stderr, "Failed to open output file %s\n", output_filename);
            return 2;
        }
        p_outputs[query_cnt] = p_output;
        query_cnt++;
    }
    char current_date[DATE_LEN] = {};
    char msg_len_str[DATE_LEN] = {};
    char msg[MAX_MSG_LEN] = {};
    while (1)
    {
        int date_len = 10;
        if (fread(current_date, 1, date_len + 1, p_log) < date_len + 1)
        {
            break;
        }
        current_date[date_len] = 0;
        int msg_len_len = 0;
        char tmp = 0;
        while ((tmp = fgetc(p_log)) != ' ')
        {
            msg_len_str[msg_len_len++] = tmp;
        }
        msg_len_str[msg_len_len] = 0;
        int msg_len = atoi(msg_len_str);
        fread(msg, 1, msg_len, p_log);
        msg[msg_len] = 0;
        for (size_t i = 0; i < query_cnt; i++)
        {
            if (!strcmp(query_date[i], current_date))
            {
                fprintf(p_outputs[i], "%s\n", msg);
                break;
            }
        }
    }

    for (size_t i = 0; i < query_cnt; i++)
    {
        fclose(p_outputs[i]);
    }
    fseek(p_log, 0, SEEK_SET);
    return 0;
}
