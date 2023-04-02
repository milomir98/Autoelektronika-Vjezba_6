#ifndef _HWINT_H
#define _HWINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uintptr_t hwInt_disable(void);

void hwInt_restore(uintptr_t key);

#ifdef __cplusplus
}
#endif

#endif