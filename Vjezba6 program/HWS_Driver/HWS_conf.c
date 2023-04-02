/* Multiplexed 7-segment display device */

#include "HWS_conf.h"

uint_least8_t mxDisp7seg_count = MX7_DISPLAY_COUNT;

mxDisp7seg_Object mxDisp7seg_objects[MX7_DISPLAY_COUNT];

mxDisp7seg_Attrs mxDisp7seg_attrs[MX7_DISPLAY_COUNT] = {
	{
		.ipAddr = 0x7F000001,	/* 127.0.0.1 - localhost */
		.ipPort = 34100,
		.digits = 1
	}
};

mxDisp7seg_Config mxDisp7seg_configs[1] = {
	{
		.FxnTable = &mxDisp7seg_HWSIM_FxnTable,
		.attrs = &(mxDisp7seg_attrs[MX7_DISPLAY_0]),
		.object = &(mxDisp7seg_objects[MX7_DISPLAY_0])
	}
};