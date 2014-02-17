#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "request_list.h"
#include "rows_algorithm.h"

REQUEST* construct_request_list(REQ_LIST_T* requests_list,REQUEST* unserved_list_head,int time_slot);
REQUEST* get_max_rows(REQUEST* unserved_list_head, int time_curr);
void update_row(REQUEST* unserved_list_head);
int update_list(REQUEST* unserved_list_head, REQUEST* req_served,int time_curr);
void printList(REQUEST* unserved_list_head);

REQUEST* unserved_list_head = NULL;

int main (int argc, char *argv[])
{
	int time_slot = 0;
	int succeed = 0;
	srand((int) time(NULL));

	REQ_LIST_T* requests_list = generate_req_list();
	REQUEST* req_served;

	printf("\n\n\n\n\n\n\n");
	for(time_slot = 0; time_slot < SIM_SLOTS; time_slot++)
	{
		unserved_list_head = construct_request_list(requests_list,unserved_list_head,time_slot);
		req_served = get_max_rows(unserved_list_head,time_slot);
		if(req_served != NULL){
			printf("request to be served:%d\n",req_served->request_id);
			succeed++;
		}
		if(req_served == NULL)
			continue;
		succeed += update_list(unserved_list_head,req_served,time_slot);
	}
	printf("Requests succeeded:%d\n",succeed);

	return 0;

}

int update_list(REQUEST* unserved_list_head, REQUEST* req_served, int time_curr)
{
	REQUEST* curr = unserved_list_head;
	REQUEST* prev = NULL;
	int succeed = 0;
	int i,j;
	
	for(prev = NULL; curr != NULL; prev = curr)
	{
		for(i = 0; i < req_served->size_D; i++)
		{
			for(j = 0; j < curr->size_D; j++)
			{
				if(req_served->req_objects[i] == curr->req_objects[j] && req_served->req_objects[i] != -1)
				{
					curr->req_objects[j] = -1;
					curr->unserved_obj--;
				}
			}
		}
		if(curr->unserved_obj == 0){
			if(curr->deadline_L - time_curr >= 0)
				succeed++;
			
			if(prev != NULL)
			{
				prev->next_req = curr->next_req;
				//free(curr);
				curr = prev->next_req;
			}else{
				unserved_list_head = curr->next_req;
				//free(curr);
				curr = unserved_list_head;
			}
		}
		if(curr != NULL)
			curr = curr->next_req;
		else
			break;
	}
	update_row(unserved_list_head);
	printList(unserved_list_head);
	return succeed;
}
REQUEST* get_max_rows(REQUEST* unserved_list_head, int time_curr)
{
	REQUEST* curr,*next;
	double max_rows = rows_calc(unserved_list_head,time_curr);
	double temp_rows;
	int max_id;
	next = unserved_list_head;
	
	if(unserved_list_head == NULL)
		return NULL;
	max_id = unserved_list_head->request_id;
	for( ; next != NULL; next = next->next_req)
	{
		temp_rows = rows_calc(next,time_curr);
		//printf("Rows:%lf next: %lf\n",max_rows,temp_rows);
		if(temp_rows >= max_rows)
		{
			max_id = next->request_id;
			max_rows = temp_rows; 
		}
	}
	printf("\n");
	for(curr = NULL, next = unserved_list_head; next != NULL; curr = next, next = next->next_req)
	{
		if(next->request_id == max_id && max_rows > 0){
			if(curr == NULL){
				unserved_list_head = next->next_req;
				return next;
			}else
			{
				curr->next_req = next->next_req;
				return next;
			}
		}
	}

	return NULL;	
}
void printList(REQUEST* unserved_list_head)
{
	REQUEST* curr = unserved_list_head;

	printf("---------------------------------------------------------------\n");


	for(curr = unserved_list_head; curr != NULL; curr = curr->next_req)
	{
		printf("request id: %d\n",curr->request_id);
		printf("deadline: %d\n",curr->deadline_L);
		printf("no of requests: %d\n",curr->size_D);
		printf("no of remaining requests: %d\n",curr->unserved_obj);
		printf("Requests left:  ");
		for(int i = 0; i < curr->size_D; i++)
			if(curr->req_objects[i] != -1)
				printf("%d  ",curr->req_objects[i]);
		printf("\n");
		printf("Row: %d\n",curr->row_value);
		printf("---------------------------------------------------------------\n");
	}
}

REQUEST* construct_request_list(REQ_LIST_T* requests_list,REQUEST* unserved_list_head,int time_slot)
{
	REQ_T *curr;
	REQUEST* new_node;
	
	

	for( curr = requests_list->head; curr != NULL && curr->s_time_stamp == time_slot ; curr = curr->next)
	{

		new_node = (REQUEST *)malloc(sizeof(REQUEST));
		new_node->next_req = unserved_list_head;
		unserved_list_head = new_node;

		new_node->request_id = curr->request_id;
		new_node->deadline_L = curr->deadline;
		new_node->size_D = curr->req_size;
		new_node->unserved_obj = curr->remaining_requests;
		new_node->req_objects = curr->req_objects;

		requests_list->head = curr->next;

	}
	update_row(unserved_list_head);
	
	//printList(unserved_list_head);

	return unserved_list_head;
}

void update_row(REQUEST* unserved_list_head)
{
	for( REQUEST* curr_req = unserved_list_head; curr_req != NULL; curr_req = curr_req->next_req)
	{
		curr_req->row_value = row_calc(unserved_list_head,curr_req);
	}
}

