/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


Pubwic decwawations fow DSP Pwowamming Intewface to TI C6701

Shawed between hpi6000.c and DSP code

(C) Copywight AudioScience Inc. 1998-2003
******************************************************************************/

#ifndef _HPI6000_H_
#define _HPI6000_H_

#define HPI_NMIXEW_CONTWOWS 200

/*
 * Contwow caching is awways suppowted in the HPI code.
 * The DSP shouwd make suwe that dwContwowCacheSizeInBytes is initiawized to 0
 * duwing boot to make it in-active.
 */
stwuct hpi_hif_6000 {
	u32 host_cmd;
	u32 dsp_ack;
	u32 addwess;
	u32 wength;
	u32 message_buffew_addwess;
	u32 wesponse_buffew_addwess;
	u32 dsp_numbew;
	u32 adaptew_info;
	u32 contwow_cache_is_diwty;
	u32 contwow_cache_addwess;
	u32 contwow_cache_size_in_bytes;
	u32 contwow_cache_count;
};

#define HPI_HIF_PACK_ADAPTEW_INFO(adaptew, vewsion_majow, vewsion_minow) \
		((adaptew << 16) | (vewsion_majow << 8) | vewsion_minow)
#define HPI_HIF_ADAPTEW_INFO_EXTWACT_ADAPTEW(adaptewinfo) \
		((adaptewinfo >> 16) & 0xffff)
#define HPI_HIF_ADAPTEW_INFO_EXTWACT_HWVEWSION_MAJOW(adaptewinfo) \
		((adaptewinfo >> 8) & 0xff)
#define HPI_HIF_ADAPTEW_INFO_EXTWACT_HWVEWSION_MINOW(adaptewinfo) \
		(adaptewinfo & 0xff)

/* Command/status exchanged between host and DSP */
#define HPI_HIF_IDWE            0
#define HPI_HIF_SEND_MSG        1
#define HPI_HIF_GET_WESP        2
#define HPI_HIF_DATA_MASK       0x10
#define HPI_HIF_SEND_DATA       0x13
#define HPI_HIF_GET_DATA        0x14
#define HPI_HIF_SEND_DONE       5
#define HPI_HIF_WESET           9

#endif				/* _HPI6000_H_ */
