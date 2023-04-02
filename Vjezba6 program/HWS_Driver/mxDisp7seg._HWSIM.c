#include "mxDisp7seg_HWSIM.h"

void mxDisp7seg_Init_HWSIM(mxDisp7seg_Handle handle);
mxDisp7seg_Handle mxDisp7seg_Open_HWSIM(mxDisp7seg_Handle handle);
void mxDisp7seg_Close_HWSIM(mxDisp7seg_Handle handle);
void mxDisp7seg_SelectDigit_HWSIM(mxDisp7seg_Handle handle, uint8_t digit);
void mxDisp7seg_SetDigit_HWSIM(mxDisp7seg_Handle handle, uint8_t binShape);

#define CMD_NULL 0
#define CMD_MX7_SELECT 1
#define CMD_MX7_SET_DIGIT 2

typedef struct command_struct_ {
    uint16_t command;
    uint8_t data;
} command_struct;

mxDisp7seg_FxnTable mxDisp7seg_HWSIM_FxnTable = {
    .init = mxDisp7seg_Init_HWSIM,
    .open = mxDisp7seg_Open_HWSIM,
    .close = mxDisp7seg_Close_HWSIM,
    .selectDigit = mxDisp7seg_SelectDigit_HWSIM,
    .setDigit = mxDisp7seg_SetDigit_HWSIM
};

void mxDisp7seg_Init_HWSIM(mxDisp7seg_Handle handle)
{
    mxDisp7seg_Object* instanceObject = handle->object;    

    instanceObject->isOpen = false;
}

mxDisp7seg_Handle mxDisp7seg_Open_HWSIM(mxDisp7seg_Handle handle)
{
    mxDisp7seg_Object* instanceObject = handle->object;
    mxDisp7seg_Attrs* instanceAttrs = handle->attrs;

    if (comm_OK == HWSIM_openLink(&(instanceObject->connHandle),
        instanceAttrs->ipPort, instanceAttrs->ipAddr))
    {
        instanceObject->isOpen = true;
        return handle;
    }
    else
    {
        return NULL;
    }
}

void mxDisp7seg_Close_HWSIM(mxDisp7seg_Handle handle)
{
    mxDisp7seg_Object* instanceObject = handle->object;

    if (instanceObject->isOpen)
        HWSIM_closeLink(&(instanceObject->connHandle));

    instanceObject->isOpen = false;
}

void mxDisp7seg_SelectDigit_HWSIM(mxDisp7seg_Handle handle, uint8_t digit)
{
    command_struct dat;
    mxDisp7seg_Object* instanceObject = handle->object;

    dat.command = CMD_MX7_SELECT;
    dat.data = digit;
    HWSIM_sendPacket(&(instanceObject->connHandle), sizeof(command_struct), &dat);
}

void mxDisp7seg_SetDigit_HWSIM(mxDisp7seg_Handle handle, uint8_t binShape)
{
    command_struct dat;
    mxDisp7seg_Object* instanceObject = handle->object;

    dat.command = CMD_MX7_SET_DIGIT;
    dat.data = binShape;
    HWSIM_sendPacket(&(instanceObject->connHandle), sizeof(command_struct), &dat);
}