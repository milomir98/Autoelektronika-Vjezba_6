#include <stdbool.h>

#include "mxDisp7seg.h"
#include "hwInt.h"

extern uint_least8_t mxDisp7seg_count;
extern mxDisp7seg_Config mxDisp7seg_configs[];

static bool inited;

void mxDisp7seg_Init(void)
{
	uint_least8_t i;
	uintptr_t key;

	key = hwInt_disable();

	if (!inited) {
		inited = true;
		for (i = 0; i < mxDisp7seg_count; i++)
			mxDisp7seg_configs[i].FxnTable->init((mxDisp7seg_Handle)&(mxDisp7seg_configs[i]));
	}

	hwInt_restore(key);
}

mxDisp7seg_Handle mxDisp7seg_Open(uint_least8_t index)
{
	mxDisp7seg_Handle handle = NULL;

	if (inited && (index < mxDisp7seg_count)) {
		handle = (mxDisp7seg_Handle)&(mxDisp7seg_configs[index]);
		handle = handle->FxnTable->open(handle);
	}

	return handle;
}

void mxDisp7seg_Close(mxDisp7seg_Handle handle)
{
	handle->FxnTable->close(handle);
}

void mxDisp7seg_SelectDigit(mxDisp7seg_Handle handle, uint8_t digit)
{
	handle->FxnTable->selectDigit(handle, digit);
}

void mxDisp7seg_SetDigit(mxDisp7seg_Handle handle, uint8_t binShape)
{
	handle->FxnTable->setDigit(handle, binShape);
}