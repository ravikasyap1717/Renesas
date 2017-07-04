/*
 * zelib-files.h
 *
 * Created on: July 26, 2016
 *     Author: Mike McDonald @ KISStek.com
 */

#ifndef _ZELIB_FILES_H_
#define _ZELIB_FILES_H_

#include "bsp_api.h"
#include "fx_api.h"

ssp_err_t ze_InitFiles(void *first_unused_memory);
UINT ze_OpenFile(FX_FILE *file_handle, char *filename, UINT flags);
unsigned int ze_LoadFile(char *filename, unsigned char *buffer, unsigned int buf_len);

#endif /* _ZELIB_FILES_H_ */
