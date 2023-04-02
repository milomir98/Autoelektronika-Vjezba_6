#ifndef _MX_DISP_7_SEG_HWSIM_H
#define _MX_DISP_7_SEG_HWSIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mxDisp7seg.h"
#include "common_HWSIM.h"

#include <stdbool.h>

extern mxDisp7seg_FxnTable mxDisp7seg_HWSIM_FxnTable;

typedef struct mxDisp7seg_Attrs_ {
	uint32_t ipAddr;
	uint16_t ipPort;
	uint_least8_t digits;
} mxDisp7seg_Attrs;

typedef struct mxDisp7seg_Object_ {
	bool isOpen;
	commData connHandle;
} mxDisp7seg_Object;

#ifdef __cplusplus
}
#endif

#endif