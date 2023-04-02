// Driver includes 
#include "HWS_Driver/HWS_conf.h"
static const char character[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x06D, 0x7D, 0x07, 0x7F, 0x6F };

// Priorities at which the tasks are created
#define task_prioritet		( tskIDLE_PRIORITY + 2 )

// Kernel includes
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "I_Vezba.h"

static mxDisp7seg_Handle myDisp;


#define mainVALUE_SENT_FROM_TASK			( 100UL )
#define mainVALUE_SENT_FROM_TIMER			( 200UL )


// Local function declaration


// Local function implementation



void V_vezba_1(void)
{
	// Inicijalizacija drajvera za displej
	mxDisp7seg_Init();
	myDisp = mxDisp7seg_Open(MX7_DISPLAY_0);

	// Ubacujemo crticu u srednju cifru
	mxDisp7seg_SelectDigit(myDisp, 2);
	mxDisp7seg_SetDigit(myDisp, 0x40);	// Vrijednost za crticu na cifri
	
	// Kreiranje softverskih tajmera 

	
	// Kreiranje redova

	
	// Kreiranje taskova 


	// Pokretanje rasporedjivaca
	vTaskStartScheduler();
	while (1);
}