#ifndef _HWS_CONFIG_H
#define _HWS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mxDisp7seg_HWSIM.h"

typedef enum {
	MX7_DISPLAY_0 = 0,
	MX7_DISPLAY_COUNT
} mxDisp7seg_device_names;

extern uint_least8_t mxDisp7seg_count;

extern mxDisp7seg_Object mxDisp7seg_objects[MX7_DISPLAY_COUNT];

extern mxDisp7seg_Attrs mxDisp7seg_attrs[MX7_DISPLAY_COUNT];

extern mxDisp7seg_Config mxDisp7seg_configs[MX7_DISPLAY_COUNT];

#ifdef __cplusplus
}
#endif

#endif