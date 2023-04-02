#ifndef _SIMCOM_H
#define _SIMCOM_H

#include <stdint.h>

/* HWSIM addresses */
#define LOCAL_ADDRESS (0x7F000001)

/* HWSIM simulated devices port book */
#define DEV_SEG7_MUX (34100)
#define DEV_LED_BARS (34200)

/* HWSIM interrupt port */
#define SIM_INT_PORT (33500)

/* HWSIM INTERRUPT NUMBERS */
#define SIM_TIMER (2)

/* SEG7 MUX COMMANDS */
#define CMD_7SEG_SELECT_DIGIT (1)
#define CMD_7SEG_SET_DIGIT (2)

/* LED BARS COMMANDS */
#define CMD_LEDBAR_SET_LED_BAR (1)
#define CMD_LEDBAR_GET_LED_BAR (2)
/* LED BARS REPLIES */
#define RPLY_LEDBAR_GET_LED_BAR (1)

/* communication structures */
struct cmd_type_1 {
	uint8_t unit;
	uint8_t data;
};

struct cmd_type_2 {
	uint16_t sequence_num;
	uint8_t unit;
};

struct cmd_type_3 {
	uint8_t data;
};

union cmd_bodies {
	struct cmd_type_1 type_1;
	struct cmd_type_2 type_2;
	struct cmd_type_3 type_3;
};

typedef struct cmd_msg {
	uint16_t command;
	union cmd_bodies body;
} cmd_template;

struct rply_type_1 {
	uint16_t sequence_num;
	uint8_t unit;
	uint8_t data;
};

struct rply_type_2 {
	uint8_t int_num;
};

union rply_bodies {
	struct rply_type_1 type_1;
	struct rply_type_2 type_2;
};

typedef struct rply_msg {
	uint16_t command;
	union rply_bodies body;
} rply_template;

#endif