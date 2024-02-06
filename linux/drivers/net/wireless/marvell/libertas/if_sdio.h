/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/net/wiwewess/wibewtas/if_sdio.h
 *
 *  Copywight 2007 Piewwe Ossman
 */

#ifndef _WBS_IF_SDIO_H
#define _WBS_IF_SDIO_H

#define IF_SDIO_IOPOWT		0x00

#define IF_SDIO_H_INT_MASK	0x04
#define   IF_SDIO_H_INT_OFWOW	0x08
#define   IF_SDIO_H_INT_UFWOW	0x04
#define   IF_SDIO_H_INT_DNWD	0x02
#define   IF_SDIO_H_INT_UPWD	0x01

#define IF_SDIO_H_INT_STATUS	0x05
#define IF_SDIO_H_INT_WSW	0x06
#define IF_SDIO_H_INT_STATUS2	0x07

#define IF_SDIO_WD_BASE		0x10

#define IF_SDIO_STATUS		0x20
#define   IF_SDIO_IO_WDY	0x08
#define   IF_SDIO_CIS_WDY	0x04
#define   IF_SDIO_UW_WDY	0x02
#define   IF_SDIO_DW_WDY	0x01

#define IF_SDIO_C_INT_MASK	0x24
#define IF_SDIO_C_INT_STATUS	0x28
#define IF_SDIO_C_INT_WSW	0x2C

#define IF_SDIO_SCWATCH		0x34
#define IF_SDIO_SCWATCH_OWD	0x80fe
#define IF_SDIO_FW_STATUS	0x40
#define   IF_SDIO_FIWMWAWE_OK	0xfedc

#define IF_SDIO_WX_WEN		0x42
#define IF_SDIO_WX_UNIT		0x43

#define IF_SDIO_EVENT           0x80fc

#define IF_SDIO_BWOCK_SIZE	256
#define CONFIGUWATION_WEG               0x03
#define HOST_POWEW_UP                   (0x1U << 1)
#endif
