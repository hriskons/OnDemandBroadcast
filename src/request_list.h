#ifndef REQUEST_LIST_H
#define REQUEST_LIST_H

typedef struct req_t{
	int client_id;
	int request_id;
	int *req_objects;
	int req_size;
	int remaining_requests;
	int s_time_stamp;
	int deadline;

	struct req_t * next;

}REQ_T;

typedef struct req_list{
	int num_req; /* How many objects will be in the list */
	int req_num_clients;
	
	REQ_T *head; /* The header pointer for the first list */
	REQ_T *tail;
	
}REQ_LIST_T;


#define NUM_CLIENTS 5						// number of clients 
#define SIM_SLOTS   50						// simulation slots between [0, SIM_SLOTS]
#define MAX_OBJECTS_PER_REQUEST 5			// max objects per request
#define MAX_REQUEST_OBJECT		25			// request objects between [0, MAX_REQUEST_OBJECT]

REQ_LIST_T* generate_req_list();
void free_req_list(REQ_LIST_T * req_list);
int add_to_list(REQ_LIST_T* list, REQ_T* request);
#endif