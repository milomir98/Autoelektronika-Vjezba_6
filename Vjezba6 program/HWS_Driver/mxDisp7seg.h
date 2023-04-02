#ifndef _MX_DISP_7_SEG_H
#define _MX_DISP_7_SEG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct mxDisp7seg_Config_* mxDisp7seg_Handle;


void mxDisp7seg_Init(void);

typedef void (*mxDisp7seg_InitFxn)(mxDisp7seg_Handle handle);


mxDisp7seg_Handle mxDisp7seg_Open(uint_least8_t index);

typedef mxDisp7seg_Handle(*mxDisp7seg_OpenFxn)(mxDisp7seg_Handle handle);


void mxDisp7seg_Close(mxDisp7seg_Handle handle);

typedef void (*mxDisp7seg_CloseFxn)(mxDisp7seg_Handle handle);


void mxDisp7seg_SelectDigit(mxDisp7seg_Handle handle, uint8_t digit);

typedef void (*mxDisp7seg_SelectDigitFxn)(mxDisp7seg_Handle handle, uint8_t digit);


void mxDisp7seg_SetDigit(mxDisp7seg_Handle handle, uint8_t binShape);

typedef void (*mxDisp7seg_SetDigitFxn)(mxDisp7seg_Handle handle, uint8_t binShape);


typedef struct mxDisp7seg_FxnTable_ {
    mxDisp7seg_InitFxn init;
    mxDisp7seg_OpenFxn open;
    mxDisp7seg_CloseFxn close;
    mxDisp7seg_SelectDigitFxn selectDigit;
    mxDisp7seg_SetDigitFxn setDigit;
} mxDisp7seg_FxnTable;


typedef struct mxDisp7seg_Config_ {
    mxDisp7seg_FxnTable* FxnTable;
    void* attrs;
    void* object;
} mxDisp7seg_Config;

#ifdef __cplusplus
}
#endif

#endif