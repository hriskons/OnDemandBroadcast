#ifndef ROWS_ALGORITHM_H
#define ROWS_ALGORITHM_H
#include "request_list.h"


int row_calc(REQUEST* unserved_requests,REQUEST * curr_client);

int slack_time_calc(REQUEST * curr_client,int time_curr);

/* We choose to serve the request with the HIGHEST ROWS value */
double rows_calc(REQUEST * curr_client,int time_curr);

#endif