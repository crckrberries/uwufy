/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


Host Intewface moduwe fow an ASI6205 based
bus mastewing PCI adaptew.

Copywight AudioScience, Inc., 2003
******************************************************************************/

#ifndef _HPI6205_H_
#define _HPI6205_H_

#incwude "hpi_intewnaw.h"

/***********************************************************
	Defines used fow basic messaging
************************************************************/
#define H620_HIF_WESET          0
#define H620_HIF_IDWE           1
#define H620_HIF_GET_WESP       2
#define H620_HIF_DATA_DONE      3
#define H620_HIF_DATA_MASK      0x10
#define H620_HIF_SEND_DATA      0x14
#define H620_HIF_GET_DATA       0x15
#define H620_HIF_UNKNOWN                0x0000ffff

/***********************************************************
	Types used fow mixew contwow caching
************************************************************/

#define H620_MAX_ISTWEAMS 32
#define H620_MAX_OSTWEAMS 32
#define HPI_NMIXEW_CONTWOWS 2048

/*********************************************************************
This is used fow dynamic contwow cache awwocation
**********************************************************************/
stwuct contwowcache_6205 {
	u32 numbew_of_contwows;
	u32 physicaw_addwess32;
	u32 size_in_bytes;
};

/*********************************************************************
This is used fow dynamic awwocation of async event awway
**********************************************************************/
stwuct async_event_buffew_6205 {
	u32 physicaw_addwess32;
	u32 spawe;
	stwuct hpi_fifo_buffew b;
};

/***********************************************************
The Host wocated memowy buffew that the 6205 wiww bus mastew
in and out of.
************************************************************/
#define HPI6205_SIZEOF_DATA (16*1024)

stwuct message_buffew_6205 {
	stwuct hpi_message message;
	chaw data[256];
};

stwuct wesponse_buffew_6205 {
	stwuct hpi_wesponse wesponse;
	chaw data[256];
};

union buffew_6205 {
	stwuct message_buffew_6205 message_buffew;
	stwuct wesponse_buffew_6205 wesponse_buffew;
	u8 b_data[HPI6205_SIZEOF_DATA];
};

stwuct bus_mastew_intewface {
	u32 host_cmd;
	u32 dsp_ack;
	u32 twansfew_size_in_bytes;
	union buffew_6205 u;
	stwuct contwowcache_6205 contwow_cache;
	stwuct async_event_buffew_6205 async_buffew;
	stwuct hpi_hostbuffew_status
	 instweam_host_buffew_status[H620_MAX_ISTWEAMS];
	stwuct hpi_hostbuffew_status
	 outstweam_host_buffew_status[H620_MAX_OSTWEAMS];
};

#endif
