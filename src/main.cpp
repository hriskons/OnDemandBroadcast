#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "request_list.h"


int main (int argc, char *argv[])
{
	srand((int) time(NULL));

	generate_req_list();
	return 0;

}