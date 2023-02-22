#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

int marioHp = 20;
int bowserHp = 20;

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("\x1b[16;20HHello Player!");
	printf("\x1b[30;16HPress A to begin...");

	while(true)
	{
		hidScanInput(); // scans for input
		u32 kDown = hidKeysDown(); // kDown = the keys that have been pressed down
		if (kDown & KEY_A) break; // breaks if a is pressed 		
	}
	
	consoleClear();
	
	while (true) // automatically is true so the battle will begin
	{

		std::cout << "\x1b[1;1HMario HP  :  " << marioHp << std::endl;  //text
		std::cout << "\x1b[3;1HBowser HP :  " << bowserHp << std::endl; //text
		printf("\x1b[16;20HPress A to Attack!"); //text
		
		if (bowserHp <= 0 || marioHp <= 0) break; // if any of the characters hp is 0 or under break the loop

		hidScanInput(); // scans for input
		u32 kDown = hidKeysDown(); // kDown = the keys that have been pressed down
		
		if (kDown & KEY_A) // if a is pressed
		{	
			consoleClear();
			int marioAtck = rand() % 10; // random between 0 and 10
			int bowserAtck = rand() % 10; // random between 0 and 10
		
			bowserHp -= marioAtck; // subtracts health - damage
			marioHp -= bowserAtck; // subtracts health - damage
	
			std::cout << "\x1b[27;16HMario lost " << bowserAtck << " HP"; //text shows how much hp mario lost
			std::cout << "\x1b[29;16HBowser lost " << marioAtck << " HP"; //text shows how much hp bowser lost
		}		
	}	
	
	consoleClear();
	std::cout << "\x1b[1;1HMario HP  :  " << marioHp << std::endl;  //text
	std::cout << "\x1b[3;1HBowser HP :  " << bowserHp << std::endl; //text
	
	if (marioHp <= 0) std::cout <<"\x1b[16;20HBowser Won!" <<"\x1b[30;16HPress Start to exit"; //text
	if (bowserHp <= 0) std::cout <<"\x1b[16;20HMario Won!" <<"\x1b[30;16HPress Start to exit"; //text
	printf("\x1b[30;16HPress Start to exit"); //text



	
	
	while (aptMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) break; 
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
