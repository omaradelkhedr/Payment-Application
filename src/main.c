#include "stdio.h"
#include "../inc/Std_Types.h"
#include "../inc/app.h"

int main(void)
{
	while (1)
	{
		if (U8_GlobalExit == ONE)
		{
			break;
		}
		else
		{
			appStart();
		}
	}
	return 0;
}

