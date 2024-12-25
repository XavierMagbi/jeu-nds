/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>

#define SIDE_SIZE 54
#define LENGTH SIDE_SIZE*SIDE_SIZE

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	consoleDemoInit();

	printf("hello word");

	while(1) {
		swiWaitForVBlank();
	}
}
