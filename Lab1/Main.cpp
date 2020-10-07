#include "Header.h"
#include <stdlib.h>

using namespace Lab1;

int main(void) {
	struct matrix arr;
	input(arr);
	struct matrix reorg = edit(arr);
	output(arr);
	std::cout << " ----------------------\n";
	output(reorg);
	free_m(arr);
	free_m(reorg);
	
	_CrtDumpMemoryLeaks();
	return 0;
}
