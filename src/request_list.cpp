#include <stdio.h>
#include <stdlib.h>

#include "request_list.h"

static int generate_random();

REQ_LIST_T* generate_req_list(){

	int curr_slot;
	int client_id; 
	int p = 2;
	int pp = 4;
	int counter = 0;
	REQ_LIST_T* list = NULL;

	list = (REQ_LIST_T*) malloc(sizeof(REQ_LIST_T));
	if(!list)
		return NULL;

	list->num_req = 0;
	list->req_num_clients = NUM_CLIENTS;
	list->head = NULL;
	list->tail = NULL;


	for( curr_slot = 0; curr_slot < SIM_SLOTS ; curr_slot++){
		
		if( generate_random() % 11 <= pp )
		for (client_id = 0; client_id < NUM_CLIENTS; client_id++){
			int make_request = generate_random() % ( 10 + 1);
			if( make_request <= p ){
				// this client will make a request
				int k;
				REQ_T* new_request = NULL;
				int how_many_ojects = generate_random() %  ( MAX_OBJECTS_PER_REQUEST + 1 );
				if( how_many_ojects > 0 ){
					new_request = (REQ_T*) malloc(sizeof(REQ_T));
					// fill the request
					new_request->client_id = client_id;

					new_request->req_size = how_many_ojects;
					new_request->remaining_requests = how_many_ojects; 
					new_request->req_objects = (int*) malloc(sizeof(int) * how_many_ojects);
					if(!new_request)
						continue;


					for( k = 0 ; k < how_many_ojects ; k++)
						new_request->req_objects[k] = -1;

					// fill request objects
					int i;
					for( i = 0; i < how_many_ojects; i++){
						int found = 0;
						do {
							
							found = 0;
							int temp = generate_random() % ( MAX_REQUEST_OBJECT + 1 );
						
							for(k = 0 ; k < how_many_ojects; k++){
								if( new_request->req_objects[k] == temp){
									found = 1;
									break; // for loop
								}
							}
							if(!found){
								new_request->req_objects[i] = temp;
								break; // do-while loop
							}
						}while(found);
					}
					new_request->s_time_stamp = curr_slot;
					new_request->deadline = generate_random() % 11 + curr_slot + 2 ;
					counter++;
					add_to_list(list, new_request);
				}
			}

		}
	}
	printf("TOTAL REQUESTS:%d\n",counter);
	return list;
}

static int generate_random(){

	return (int)rand();

}

int add_to_list(REQ_LIST_T* list, REQ_T* request){

	
	request->next = NULL;
	request->request_id = list->num_req;

	if( list->num_req == 0 ){
		list->head = request;
		list->tail = request;
		list->num_req = list->num_req + 1;

	}
	else{

		// add to the end of the list
		list->tail->next = request;
		list->tail = request;

		list->num_req = list->num_req + 1; 
	}

	return 1;
}

void free_req_list(REQ_LIST_T * req_list){

	REQ_T* temp;


	while(req_list->head){
		temp = req_list->head->next;
		free(req_list->head->req_objects);
		free(req_list->head);

		req_list->head = temp;
	}

	free(req_list);
}