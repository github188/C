// led_manager.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "led_manager.h"

#define ENTER_FUN() printf("+ %s\n", __func__)
#define EXIT_FUN()  printf("- %s\n", __func__)

#define MAX_BUF_LEN 256
#define MAX_CHASSIS_NUM 5
#define MAX_DISK_NUM_PER_CHASSIS 48

static char arr_expander[MAX_CHASSIS_NUM][MAX_BUF_LEN] = {0};
static int disk_index[MAX_CHASSIS_NUM][MAX_DISK_NUM_PER_CHASSIS] = {0};

/*
 * This function need to call to update expander info when jbod status change?
 */
static void get_expander()
{
	int i=0;
	FILE *fp = NULL;
	char line[MAX_BUF_LEN] = {0};

	memset(arr_expander, 0, sizeof(arr_expander));

	if ((fp=popen("sg_map |awk '{if($2==\"\"){print $1}}'", "r")) == NULL)
		return;

	while (fgets(line, sizeof(line), fp))
	{
		if (i < MAX_CHASSIS_NUM)
		{
			int len = strlen(line);
			line[len-1] = '\0';
			strcpy(arr_expander[i++], line);
		}
	}
	
	pclose(fp);
}

/*
 * 
 */
static void get_maping_slot_index(int expander_index)
{
	FILE *fp = NULL;
	int i = 0, j = 0;
	char **tokens = NULL;
	char line[MAX_BUF_LEN] = {0};
	char cmd[MAX_BUF_LEN] = {0};

	snprintf(cmd, sizeof(cmd), "sg_ses -p 0xa %s |grep -E 'slot|Element' |sed 'N;s/\\n//' |awk '{print $15,$3}' |sort -n",
			arr_expander[expander_index]);

	// clean data
	for (i=0; i<MAX_CHASSIS_NUM; i++)
	{
		for (j=0; j<MAX_DISK_NUM_PER_CHASSIS; j++)
		{
			disk_index[i][j] = -1;
		}
	}

	if ((fp=popen(cmd, "r")) == NULL)
		return;

	i = 0;
	char *token;
	while (fgets(line, sizeof(line), fp))
	{
		token = strtok(line, " ");
		if (token)
		{
			token = strtok(NULL, " ");
			if (token && i < MAX_DISK_NUM_PER_CHASSIS)
				disk_index[expander_index][i++] = atoi(token);
		}
	}
	free(tokens);

	pclose(fp);
}

static void led_debug_print()
{
	int i=0, j=0;

	for (i=0; i<MAX_CHASSIS_NUM; i++) 
	{
		if (strlen(arr_expander[i]) > 0 )
		{
			printf("%s\n", arr_expander[i]);
		}
		else
		{
			break;
		}
	}

	for (i=0; i<MAX_CHASSIS_NUM; i++) 
	{
		for (j=0; j<MAX_DISK_NUM_PER_CHASSIS; j++) 
		{
			if (disk_index[i][j] != -1)
			{
				printf("%d -- %d\n", j, disk_index[i][j]);
			}
			else
			{
				break;
			}
		}
	}
}

void led_init()
{
	int i=0;

	get_expander();

	for (i=0; i<MAX_CHASSIS_NUM; i++) 
	{
		if (strlen(arr_expander[i]) > 0)
			get_maping_slot_index(i);
	}

	//led_debug_print();
}

void led_set_status(int chassis_index, int slot_index, char *type, int status)
{
	char cmd[MAX_BUF_LEN] = {0};

	snprintf(cmd, sizeof(cmd), "sg_ses --index=%d --%s=%s %s >/dev/null 2>&1", 
		disk_index[chassis_index][slot_index], status==0?"clear":"set", type, 
		arr_expander[chassis_index]);
	
	//printf("%s\n", cmd);

	// run cmd here
	system(cmd);
}
