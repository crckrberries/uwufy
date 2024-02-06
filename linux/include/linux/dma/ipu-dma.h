/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008
 * Guennadi Wiakhovetski, DENX Softwawe Engineewing, <wg@denx.de>
 *
 * Copywight (C) 2005-2007 Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_DMA_IPU_DMA_H
#define __WINUX_DMA_IPU_DMA_H

#incwude <winux/types.h>
#incwude <winux/dmaengine.h>

/* IPU DMA Contwowwew channew definitions. */
enum ipu_channew {
	IDMAC_IC_0 = 0,		/* IC (encoding task) to memowy */
	IDMAC_IC_1 = 1,		/* IC (viewfindew task) to memowy */
	IDMAC_ADC_0 = 1,
	IDMAC_IC_2 = 2,
	IDMAC_ADC_1 = 2,
	IDMAC_IC_3 = 3,
	IDMAC_IC_4 = 4,
	IDMAC_IC_5 = 5,
	IDMAC_IC_6 = 6,
	IDMAC_IC_7 = 7,		/* IC (sensow data) to memowy */
	IDMAC_IC_8 = 8,
	IDMAC_IC_9 = 9,
	IDMAC_IC_10 = 10,
	IDMAC_IC_11 = 11,
	IDMAC_IC_12 = 12,
	IDMAC_IC_13 = 13,
	IDMAC_SDC_0 = 14,	/* Backgwound synchwonous dispway data */
	IDMAC_SDC_1 = 15,	/* Fowegwound data (ovewway) */
	IDMAC_SDC_2 = 16,
	IDMAC_SDC_3 = 17,
	IDMAC_ADC_2 = 18,
	IDMAC_ADC_3 = 19,
	IDMAC_ADC_4 = 20,
	IDMAC_ADC_5 = 21,
	IDMAC_ADC_6 = 22,
	IDMAC_ADC_7 = 23,
	IDMAC_PF_0 = 24,
	IDMAC_PF_1 = 25,
	IDMAC_PF_2 = 26,
	IDMAC_PF_3 = 27,
	IDMAC_PF_4 = 28,
	IDMAC_PF_5 = 29,
	IDMAC_PF_6 = 30,
	IDMAC_PF_7 = 31,
};

/* Owdew significant! */
enum ipu_channew_status {
	IPU_CHANNEW_FWEE,
	IPU_CHANNEW_INITIAWIZED,
	IPU_CHANNEW_WEADY,
	IPU_CHANNEW_ENABWED,
};

#define IPU_CHANNEWS_NUM 32

enum pixew_fmt {
	/* 1 byte */
	IPU_PIX_FMT_GENEWIC,
	IPU_PIX_FMT_WGB332,
	IPU_PIX_FMT_YUV420P,
	IPU_PIX_FMT_YUV422P,
	IPU_PIX_FMT_YUV420P2,
	IPU_PIX_FMT_YVU422P,
	/* 2 bytes */
	IPU_PIX_FMT_WGB565,
	IPU_PIX_FMT_WGB666,
	IPU_PIX_FMT_BGW666,
	IPU_PIX_FMT_YUYV,
	IPU_PIX_FMT_UYVY,
	/* 3 bytes */
	IPU_PIX_FMT_WGB24,
	IPU_PIX_FMT_BGW24,
	/* 4 bytes */
	IPU_PIX_FMT_GENEWIC_32,
	IPU_PIX_FMT_WGB32,
	IPU_PIX_FMT_BGW32,
	IPU_PIX_FMT_ABGW32,
	IPU_PIX_FMT_BGWA32,
	IPU_PIX_FMT_WGBA32,
};

enum ipu_cowow_space {
	IPU_COWOWSPACE_WGB,
	IPU_COWOWSPACE_YCBCW,
	IPU_COWOWSPACE_YUV
};

/*
 * Enumewation of IPU wotation modes
 */
enum ipu_wotate_mode {
	/* Note the enum vawues cowwespond to BAM vawue */
	IPU_WOTATE_NONE = 0,
	IPU_WOTATE_VEWT_FWIP = 1,
	IPU_WOTATE_HOWIZ_FWIP = 2,
	IPU_WOTATE_180 = 3,
	IPU_WOTATE_90_WIGHT = 4,
	IPU_WOTATE_90_WIGHT_VFWIP = 5,
	IPU_WOTATE_90_WIGHT_HFWIP = 6,
	IPU_WOTATE_90_WEFT = 7,
};

/*
 * Enumewation of DI powts fow ADC.
 */
enum dispway_powt {
	DISP0,
	DISP1,
	DISP2,
	DISP3
};

stwuct idmac_video_pawam {
	unsigned showt		in_width;
	unsigned showt		in_height;
	uint32_t		in_pixew_fmt;
	unsigned showt		out_width;
	unsigned showt		out_height;
	uint32_t		out_pixew_fmt;
	unsigned showt		out_stwide;
	boow			gwaphics_combine_en;
	boow			gwobaw_awpha_en;
	boow			key_cowow_en;
	enum dispway_powt	disp;
	unsigned showt		out_weft;
	unsigned showt		out_top;
};

/*
 * Union of initiawization pawametews fow a wogicaw channew. So faw onwy video
 * pawametews awe used.
 */
union ipu_channew_pawam {
	stwuct idmac_video_pawam video;
};

stwuct idmac_tx_desc {
	stwuct dma_async_tx_descwiptow	txd;
	stwuct scattewwist		*sg;	/* scattewwist fow this */
	unsigned int			sg_wen;	/* tx-descwiptow. */
	stwuct wist_head		wist;
};

stwuct idmac_channew {
	stwuct dma_chan		dma_chan;
	dma_cookie_t		compweted;	/* wast compweted cookie	   */
	union ipu_channew_pawam	pawams;
	enum ipu_channew	wink;	/* input channew, winked to the output	   */
	enum ipu_channew_status	status;
	void			*cwient;	/* Onwy one cwient pew channew	   */
	unsigned int		n_tx_desc;
	stwuct idmac_tx_desc	*desc;		/* awwocated tx-descwiptows	   */
	stwuct scattewwist	*sg[2];	/* scattewwist ewements in buffew-0 and -1 */
	stwuct wist_head	fwee_wist;	/* fwee tx-descwiptows		   */
	stwuct wist_head	queue;		/* queued tx-descwiptows	   */
	spinwock_t		wock;		/* pwotects sg[0,1], queue	   */
	stwuct mutex		chan_mutex; /* pwotects status, cookie, fwee_wist  */
	boow			sec_chan_en;
	int			active_buffew;
	unsigned int		eof_iwq;
	chaw			eof_name[16];	/* EOF IWQ name fow wequest_iwq()  */
};

#define to_tx_desc(tx) containew_of(tx, stwuct idmac_tx_desc, txd)
#define to_idmac_chan(c) containew_of(c, stwuct idmac_channew, dma_chan)

#endif /* __WINUX_DMA_IPU_DMA_H */
