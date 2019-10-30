/*****************************************************************************
 *
 *  Copyright (c) 2015  Broadcom Corporation
 *  All Rights Reserved
 *
 * <:label-BRCM:2015:DUAL/GPL:standard
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
:>
 *
 ****************************************************************************/

#ifndef BCM_IMGIF_H
#define BCM_IMGIF_H

/* ---- Include Files ----------------------------------------------------- */

#include "cms_image.h"


/* ---- Constants and Types ----------------------------------------------- */

typedef void *IMGIF_HANDLE;

/*
 * Image information. The source may be one of the following:
 * - Built-in attribute included in the image.
 * - Derived/calculated from the image.
 * - Obtained externally.
 */
typedef struct
{
#define IMG_INFO_BITMASK_SIZE 0x1
#define IMG_INFO_BITMASK_CRC  0x2
    UINT32 bitmask;
    UINT32 size;
    UINT32 crc;
} imgif_img_info_t;

typedef struct
{
    UINT32 flashType;
    UINT32 flashSize;
    UINT32 eraseSize;
} imgif_flash_info_t;

typedef CmsImageFormat (*IMG_FORMAT_PARSER_CB)(UINT8 *bufP,
  UINT32 bufLen);
typedef void (*CAL_CRC32_CB)(UINT32 stage, UINT32 *crcInP, UINT8 *bufP,
  UINT32 bufLen);


/* ---- Variable Externs -------------------------------------------------- */


/* ---- Function Prototypes ----------------------------------------------- */

IMGIF_HANDLE imgif_open(IMG_FORMAT_PARSER_CB fmtParserCb,
  CAL_CRC32_CB calCrc32Cb);
int imgif_write(IMGIF_HANDLE h, UINT8 *dataP, int len);
int imgif_close(IMGIF_HANDLE h, UBOOL8 abortFlag);
int imgif_set_image_info(IMGIF_HANDLE h, imgif_img_info_t *imgInfoP);
int imgif_get_flash_info(IMGIF_HANDLE h, imgif_flash_info_t *flashInfoP);
UBOOL8 imgif_get_enable_mode(void);


#endif /* CMS_IMGIF_H */
