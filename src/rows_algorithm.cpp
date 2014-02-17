#include "rows_algorithm.h"
#include "request_list.h"
#include <stdio.h>

int row_calc(REQUEST* unserved_requests,REQUEST * curr_client)
{
	REQUEST* curr;
	int row = 0;
	int i,j;

	curr = unserved_requests;
	//printf("%p\n",curr);
	for(; curr ; curr = curr->next_req)
	{
		//printf("id_list: %d id_curr: %d\n ",curr->request_id,curr_client->request_id);
		if(curr->request_id != curr_client->request_id)
		{
			for(i = 0; i < curr->size_D; i++)
			{
				for(j = 0; j < curr_client->size_D; j++)
				{
					//printf("Compare: %d %d\n",curr->req_objects[i],curr_client->req_objects[j]);
					if(curr->req_objects[i] != -1 && curr->req_objects[i] == curr_client->req_objects[j])
						row++;
				}
			} 
		}
	}
	//printf("\n\n\n");
	return row;
}

int slack_time_calc(REQUEST * curr_client,int time_curr)
{
	/* Note it says that we have to subtract the current time from the absolute deadline */
	return curr_client->deadline_L - time_curr;
}

/* We choose to serve the request with the HIGHEST ROWS value */
double rows_calc(REQUEST * curr_client,int time_curr)
{
	if(curr_client != NULL)
	{
		int slack = slack_time_calc(curr_client,time_curr);
		if(slack == 0)
			return -1.0;
		else
			return curr_client->row_value / slack;
	}else{
		return -1.0; 
	}
}