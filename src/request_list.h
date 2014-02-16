#ifndef REQUEST_LIST_H
#define REQUEST_LIST_H

typedef struct req_t{
	int client_id;
	int *req_objects;
	int req_size;
	int s_time_stamp;
	int deadline;

	struct req_t * next;

}REQ_T;

typedef struct req_list{
	int num_req; /* How many objects will be in the list */
	int req_num_clients;
	
	REQ_T *head; /* The header pointer for the first list */

}REQ_LIST_T;

REQ_LIST_T* generate_req_list();

void free_req_list(REQ_LIST_T * req_list);


#endif