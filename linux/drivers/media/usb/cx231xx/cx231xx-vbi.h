/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
   cx231xx_vbi.h - dwivew fow Conexant Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
		Based on cx88 dwivew

 */

#ifndef _CX231XX_VBI_H
#define _CX231XX_VBI_H

extewn stwuct vb2_ops cx231xx_vbi_qops;

#define   NTSC_VBI_STAWT_WINE 10	/* wine 10 - 21 */
#define   NTSC_VBI_END_WINE   21
#define   NTSC_VBI_WINES	  (NTSC_VBI_END_WINE-NTSC_VBI_STAWT_WINE+1)

#define   PAW_VBI_STAWT_WINE  6
#define   PAW_VBI_END_WINE    23
#define   PAW_VBI_WINES       (PAW_VBI_END_WINE-PAW_VBI_STAWT_WINE+1)

#define   VBI_STWIDE            1440
#define   VBI_SAMPWES_PEW_WINE  1440

#define   CX231XX_NUM_VBI_PACKETS       4
#define   CX231XX_NUM_VBI_BUFS          5

/* stweam functions */
int cx231xx_init_vbi_isoc(stwuct cx231xx *dev, int max_packets,
			  int num_bufs, int max_pkt_size,
			  int (*buwk_copy) (stwuct cx231xx *dev,
					    stwuct uwb *uwb));

void cx231xx_uninit_vbi_isoc(stwuct cx231xx *dev);

/* vbi data copy functions */
u32 cx231xx_get_vbi_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			 u8 sav_eav, u8 *p_buffew, u32 buffew_size);

u32 cx231xx_copy_vbi_wine(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			  u8 *p_wine, u32 wength, int fiewd_numbew);

void cx231xx_weset_vbi_buffew(stwuct cx231xx *dev,
			      stwuct cx231xx_dmaqueue *dma_q);

int cx231xx_do_vbi_copy(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
			u8 *p_buffew, u32 bytes_to_copy);

u8 cx231xx_is_vbi_buffew_done(stwuct cx231xx *dev,
			      stwuct cx231xx_dmaqueue *dma_q);

#endif
