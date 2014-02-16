#include <stdlib.h>

#include "request_list.h"

static int generate_random();

REQ_LIST_T* generate_req_list(){

	int curr_slot;
	int client_id; 
	int p = 3;
	int slot_num_requests;


	REQ_LIST_T* list = NULL;

	list = (REQ_LIST_T*) malloc(sizeof(REQ_LIST_T));
	if(!list)
		return NULL;

	list->num_req = 0;
	list->req_num_clients = NUM_CLIENTS;
	list->head = NULL;

	for( curr_slot = 0; curr_slot < SIM_SLOTS ; curr_slot++){
		for (client_id = 0; client_id < NUM_CLIENTS; client_id++){
			int make_request = generate_random() % 10;
			if( make_request > p ){
				// this client will make a request

				REQ_T* new_request = NULL;
				int how_many_ojects = generate_random() % MAX_OBJECTS_PER_REQUEST;
				
				// fill the request
				new_request->client_id = client_id;

				new_request->req_size = how_many_ojects;
				new_request->req_objects = (int*) malloc(sizeof(int) * how_many_ojects);
				if(!new_request)
					continue;

				// fill request objects
				int i;
				for( i = 0; i < how_many_ojects; i++){
					new_request->req_objects[i] = generate_random() % MAX_REQUEST_OBJECT;	
				}

				new_request->s_time_stamp = curr_slot;
				new_request->deadline = generate_random() % 10 + curr_slot ;

				add_to_list(list->new_request);
			}

		}
	}
	return list;
}

static int generate_random(){

	return (int)rand();

}

int add_to_list(REQ_LIST_T* list, REQ_T* request){

	request->next = NULL;
	REQ_T* curr;

	if( list->num_req == 0 ){
		list->head = request;
		list->num_req = list->num_req + 1;
	}
	else{

		request->next = list->head;
		list->head    = request;
		list->num_req = list->num_req + 1; 
	}

	return 1;
}