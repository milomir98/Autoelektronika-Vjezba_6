/* Driver includes */
#include "HWS_Driver/HWS_conf.h"
static const char character[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x06D, 0x7D, 0x07, 0x7F, 0x6F };



#define task_prioritet		( tskIDLE_PRIORITY + 2 )

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "I_Vezba.h"

static mxDisp7seg_Handle myDisp;
static SemaphoreHandle_t binSem1;

static TaskHandle_t tA, tB;


#define mainVALUE_SENT_FROM_TASK			( 100UL )
#define mainVALUE_SENT_FROM_TIMER			( 200UL )

static QueueHandle_t myQueue = NULL;

TimerHandle_t tH;

//local function declaration
static void TimerCallback(TimerHandle_t tmH);
static void QueueSend_tsk(void* pvParams);
static void QueueReceive_tsk(void* pvParameters);





static void TimerCallback(TimerHandle_t tmH)
{
	 uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER;
	xQueueSend(myQueue, &ulValueToSend, 0U);// salje podatak iz tajmera
}



static void QueueSend_tsk(void* pvParams)
{
		 uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
		xTimerStart(tH, 0);// pokrecemo tajmer
 for (;; ) // beskonacna petlja
	{
		vTaskDelay(pdMS_TO_TICKS(400UL)); // task je blokiran 400 ms
		xQueueSend(myQueue, &ulValueToSend, 0U);// salje podatak iz taska u red myQueue
		}
	
}
static void QueueReceive_tsk(void* pvParameters)
{
	uint32_t ulReceivedValue;
	uint16_t a_num = 0;
	uint16_t b_num = 0;
		for (;; )
	{
		xQueueReceive(myQueue, &ulReceivedValue, portMAX_DELAY); // task ceka u blokiranom stanju dok ne dobije podatak iz Queue
		
		if (ulReceivedValue == mainVALUE_SENT_FROM_TASK) //ako smo dobili podatak iz taksa inkrementira vrednost na zadnje dve cifre displeja
		{
			mxDisp7seg_SelectDigit(myDisp, 4);
			mxDisp7seg_SetDigit(myDisp, character[a_num % 10]);
			mxDisp7seg_SelectDigit(myDisp, 3);
			mxDisp7seg_SetDigit(myDisp, character[a_num / 10]);
			a_num++;
		}
		else if (ulReceivedValue == mainVALUE_SENT_FROM_TIMER)  //ako smo dobili podatak iz tajmera inkrementira vrednost na prve dve cifre displeja
		{
			mxDisp7seg_SelectDigit(myDisp, 1);
			mxDisp7seg_SetDigit(myDisp, character[b_num % 10]);
			mxDisp7seg_SelectDigit(myDisp, 0);
			mxDisp7seg_SetDigit(myDisp, character[b_num / 10]);
			b_num++;
		}
		else
		{
			printf("Unexpected message\r\n");
		}
	}
}


void V_vezba_1(void)
{
	/* Inicijalizacija drajvera za displej*/
	mxDisp7seg_Init();
	myDisp = mxDisp7seg_Open(MX7_DISPLAY_0);
	// ubacujemo crticu u srednju cifru
	mxDisp7seg_SelectDigit(myDisp, 2);
	mxDisp7seg_SetDigit(myDisp, 0x40);//vrednost za crticu na cifri
	

	

	// -------------- CREATE TASKS AND OTHER OBJECTS HERE --------

	tH = xTimerCreate(NULL, pdMS_TO_TICKS(1100), pdTRUE, NULL, TimerCallback);
	if (tH == NULL)
		while (1);
	//xTimerStart(tH, 0);
	
	

	if (xTaskCreate(QueueReceive_tsk, "Rx", configMINIMAL_STACK_SIZE, NULL, 2, &tA) != pdPASS)
		while (1);// task za primanje podataka iz reda
	if (xTaskCreate(QueueSend_tsk, "TX", configMINIMAL_STACK_SIZE, NULL, 2, &tB) != pdPASS)
		while (1);// task za upis podataka u red

	myQueue = xQueueCreate(1, sizeof(uint32_t));// kreiramo Queue duzine dva uint32_t
// -----------------------------------------------------------

	vTaskStartScheduler();
	while (1);
}