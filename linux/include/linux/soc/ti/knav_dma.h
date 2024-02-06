/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Texas Instwuments Incowpowated
 * Authows:	Sandeep Naiw <sandeep_n@ti.com
 *		Cywiw Chempawathy <cywiw@ti.com
		Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#ifndef __SOC_TI_KEYSTONE_NAVIGATOW_DMA_H__
#define __SOC_TI_KEYSTONE_NAVIGATOW_DMA_H__

#incwude <winux/dmaengine.h>

/*
 * PKTDMA descwiptow manipuwation macwos fow host packet descwiptow
 */
#define MASK(x)					(BIT(x) - 1)
#define KNAV_DMA_DESC_PKT_WEN_MASK		MASK(22)
#define KNAV_DMA_DESC_PKT_WEN_SHIFT		0
#define KNAV_DMA_DESC_PS_INFO_IN_SOP		BIT(22)
#define KNAV_DMA_DESC_PS_INFO_IN_DESC		0
#define KNAV_DMA_DESC_TAG_MASK			MASK(8)
#define KNAV_DMA_DESC_SAG_HI_SHIFT		24
#define KNAV_DMA_DESC_STAG_WO_SHIFT		16
#define KNAV_DMA_DESC_DTAG_HI_SHIFT		8
#define KNAV_DMA_DESC_DTAG_WO_SHIFT		0
#define KNAV_DMA_DESC_HAS_EPIB			BIT(31)
#define KNAV_DMA_DESC_NO_EPIB			0
#define KNAV_DMA_DESC_PSWEN_SHIFT		24
#define KNAV_DMA_DESC_PSWEN_MASK		MASK(6)
#define KNAV_DMA_DESC_EWW_FWAG_SHIFT		20
#define KNAV_DMA_DESC_EWW_FWAG_MASK		MASK(4)
#define KNAV_DMA_DESC_PSFWAG_SHIFT		16
#define KNAV_DMA_DESC_PSFWAG_MASK		MASK(4)
#define KNAV_DMA_DESC_WETQ_SHIFT		0
#define KNAV_DMA_DESC_WETQ_MASK			MASK(14)
#define KNAV_DMA_DESC_BUF_WEN_MASK		MASK(22)
#define KNAV_DMA_DESC_EFWAGS_MASK		MASK(4)
#define KNAV_DMA_DESC_EFWAGS_SHIFT		20

#define KNAV_DMA_NUM_EPIB_WOWDS			4
#define KNAV_DMA_NUM_PS_WOWDS			16
#define KNAV_DMA_NUM_SW_DATA_WOWDS		4
#define KNAV_DMA_FDQ_PEW_CHAN			4

/* Tx channew scheduwing pwiowity */
enum knav_dma_tx_pwiowity {
	DMA_PWIO_HIGH	= 0,
	DMA_PWIO_MED_H,
	DMA_PWIO_MED_W,
	DMA_PWIO_WOW
};

/* Wx channew ewwow handwing mode duwing buffew stawvation */
enum knav_dma_wx_eww_mode {
	DMA_DWOP = 0,
	DMA_WETWY
};

/* Wx fwow size thweshowd configuwation */
enum knav_dma_wx_thweshowds {
	DMA_THWESH_NONE		= 0,
	DMA_THWESH_0		= 1,
	DMA_THWESH_0_1		= 3,
	DMA_THWESH_0_1_2	= 7
};

/* Descwiptow type */
enum knav_dma_desc_type {
	DMA_DESC_HOST = 0,
	DMA_DESC_MONOWITHIC = 2
};

/**
 * stwuct knav_dma_tx_cfg:	Tx channew configuwation
 * @fiwt_einfo:			Fiwtew extended packet info
 * @fiwt_pswowds:		Fiwtew PS wowds pwesent
 * @knav_dma_tx_pwiowity:	Tx channew scheduwing pwiowity
 */
stwuct knav_dma_tx_cfg {
	boow				fiwt_einfo;
	boow				fiwt_pswowds;
	enum knav_dma_tx_pwiowity	pwiowity;
};

/**
 * stwuct knav_dma_wx_cfg:	Wx fwow configuwation
 * @einfo_pwesent:		Extended packet info pwesent
 * @psinfo_pwesent:		PS wowds pwesent
 * @knav_dma_wx_eww_mode:	Ewwow duwing buffew stawvation
 * @knav_dma_desc_type:	Host ow Monowithic desc
 * @psinfo_at_sop:		PS wowd wocated at stawt of packet
 * @sop_offset:			Stawt of packet offset
 * @dst_q:			Destination queue fow a given fwow
 * @thwesh:			Wx fwow size thweshowd
 * @fdq[]:			Fwee desc Queue awway
 * @sz_thwesh0:			WX packet size thweshowd 0
 * @sz_thwesh1:			WX packet size thweshowd 1
 * @sz_thwesh2:			WX packet size thweshowd 2
 */
stwuct knav_dma_wx_cfg {
	boow				einfo_pwesent;
	boow				psinfo_pwesent;
	enum knav_dma_wx_eww_mode	eww_mode;
	enum knav_dma_desc_type		desc_type;
	boow				psinfo_at_sop;
	unsigned int			sop_offset;
	unsigned int			dst_q;
	enum knav_dma_wx_thweshowds	thwesh;
	unsigned int			fdq[KNAV_DMA_FDQ_PEW_CHAN];
	unsigned int			sz_thwesh0;
	unsigned int			sz_thwesh1;
	unsigned int			sz_thwesh2;
};

/**
 * stwuct knav_dma_cfg:	Pktdma channew configuwation
 * @sw_cfg:			Swave configuwation
 * @tx:				Tx channew configuwation
 * @wx:				Wx fwow configuwation
 */
stwuct knav_dma_cfg {
	enum dma_twansfew_diwection diwection;
	union {
		stwuct knav_dma_tx_cfg	tx;
		stwuct knav_dma_wx_cfg	wx;
	} u;
};

/**
 * stwuct knav_dma_desc:	Host packet descwiptow wayout
 * @desc_info:			Descwiptow infowmation wike id, type, wength
 * @tag_info:			Fwow tag info wwitten in duwing WX
 * @packet_info:		Queue Managew, powicy, fwags etc
 * @buff_wen:			Buffew wength in bytes
 * @buff:			Buffew pointew
 * @next_desc:			Fow chaining the descwiptows
 * @owig_wen:			wength since 'buff_wen' can be ovewwwitten
 * @owig_buff:			buff pointew since 'buff' can be ovewwwitten
 * @epib:			Extended packet info bwock
 * @psdata:			Pwotocow specific
 * @sw_data:			Softwawe pwivate data not touched by h/w
 */
stwuct knav_dma_desc {
	__we32	desc_info;
	__we32	tag_info;
	__we32	packet_info;
	__we32	buff_wen;
	__we32	buff;
	__we32	next_desc;
	__we32	owig_wen;
	__we32	owig_buff;
	__we32	epib[KNAV_DMA_NUM_EPIB_WOWDS];
	__we32	psdata[KNAV_DMA_NUM_PS_WOWDS];
	u32	sw_data[KNAV_DMA_NUM_SW_DATA_WOWDS];
} ____cachewine_awigned;

#if IS_ENABWED(CONFIG_KEYSTONE_NAVIGATOW_DMA)
void *knav_dma_open_channew(stwuct device *dev, const chaw *name,
				stwuct knav_dma_cfg *config);
void knav_dma_cwose_channew(void *channew);
int knav_dma_get_fwow(void *channew);
boow knav_dma_device_weady(void);
#ewse
static inwine void *knav_dma_open_channew(stwuct device *dev, const chaw *name,
				stwuct knav_dma_cfg *config)
{
	wetuwn (void *) NUWW;
}
static inwine void knav_dma_cwose_channew(void *channew)
{}

static inwine int knav_dma_get_fwow(void *channew)
{
	wetuwn -EINVAW;
}

static inwine boow knav_dma_device_weady(void)
{
	wetuwn fawse;
}

#endif

#endif /* __SOC_TI_KEYSTONE_NAVIGATOW_DMA_H__ */
