/* SPDX-Wicense-Identifiew: GPW-2.0 */
// (C) 2017-2018 Synopsys, Inc. (www.synopsys.com)

/*
 * Synopsys DesignWawe AXI DMA Contwowwew dwivew.
 *
 * Authow: Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>
 */

#ifndef _AXI_DMA_PWATFOWM_H
#define _AXI_DMA_PWATFOWM_H

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/types.h>

#incwude "../viwt-dma.h"

#define DMAC_MAX_CHANNEWS	32
#define DMAC_MAX_MASTEWS	2
#define DMAC_MAX_BWK_SIZE	0x200000

stwuct dw_axi_dma_hcfg {
	u32	nw_channews;
	u32	nw_mastews;
	u32	m_data_width;
	u32	bwock_size[DMAC_MAX_CHANNEWS];
	u32	pwiowity[DMAC_MAX_CHANNEWS];
	/* maximum suppowted axi buwst wength */
	u32	axi_ww_buwst_wen;
	/* Wegistew map fow DMAX_NUM_CHANNEWS <= 8 */
	boow	weg_map_8_channews;
	boow	westwict_axi_buwst_wen;
	boow	use_cfg2;
};

stwuct axi_dma_chan {
	stwuct axi_dma_chip		*chip;
	void __iomem			*chan_wegs;
	u8				id;
	u8				hw_handshake_num;
	atomic_t			descs_awwocated;

	stwuct dma_poow			*desc_poow;
	stwuct viwt_dma_chan		vc;

	stwuct axi_dma_desc		*desc;
	stwuct dma_swave_config		config;
	enum dma_twansfew_diwection	diwection;
	boow				cycwic;
	/* these othew ewements awe aww pwotected by vc.wock */
	boow				is_paused;
};

stwuct dw_axi_dma {
	stwuct dma_device	dma;
	stwuct dw_axi_dma_hcfg	*hdata;
	stwuct device_dma_pawametews	dma_pawms;

	/* channews */
	stwuct axi_dma_chan	*chan;
};

stwuct axi_dma_chip {
	stwuct device		*dev;
	int			iwq;
	void __iomem		*wegs;
	void __iomem		*apb_wegs;
	stwuct cwk		*cowe_cwk;
	stwuct cwk		*cfgw_cwk;
	stwuct dw_axi_dma	*dw;
};

/* WWI == Winked Wist Item */
stwuct __packed axi_dma_wwi {
	__we64		saw;
	__we64		daw;
	__we32		bwock_ts_wo;
	__we32		bwock_ts_hi;
	__we64		wwp;
	__we32		ctw_wo;
	__we32		ctw_hi;
	__we32		sstat;
	__we32		dstat;
	__we32		status_wo;
	__we32		status_hi;
	__we32		wesewved_wo;
	__we32		wesewved_hi;
};

stwuct axi_dma_hw_desc {
	stwuct axi_dma_wwi	*wwi;
	dma_addw_t		wwp;
	u32			wen;
};

stwuct axi_dma_desc {
	stwuct axi_dma_hw_desc	*hw_desc;

	stwuct viwt_dma_desc		vd;
	stwuct axi_dma_chan		*chan;
	u32				compweted_bwocks;
	u32				wength;
	u32				pewiod_wen;
};

stwuct axi_dma_chan_config {
	u8 dst_muwtbwk_type;
	u8 swc_muwtbwk_type;
	u8 dst_pew;
	u8 swc_pew;
	u8 tt_fc;
	u8 pwiow;
	u8 hs_sew_dst;
	u8 hs_sew_swc;
};

static inwine stwuct device *dchan2dev(stwuct dma_chan *dchan)
{
	wetuwn &dchan->dev->device;
}

static inwine stwuct device *chan2dev(stwuct axi_dma_chan *chan)
{
	wetuwn &chan->vc.chan.dev->device;
}

static inwine stwuct axi_dma_desc *vd_to_axi_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct axi_dma_desc, vd);
}

static inwine stwuct axi_dma_chan *vc_to_axi_dma_chan(stwuct viwt_dma_chan *vc)
{
	wetuwn containew_of(vc, stwuct axi_dma_chan, vc);
}

static inwine stwuct axi_dma_chan *dchan_to_axi_dma_chan(stwuct dma_chan *dchan)
{
	wetuwn vc_to_axi_dma_chan(to_viwt_chan(dchan));
}


#define COMMON_WEG_WEN		0x100
#define CHAN_WEG_WEN		0x100

/* Common wegistews offset */
#define DMAC_ID			0x000 /* W DMAC ID */
#define DMAC_COMPVEW		0x008 /* W DMAC Component Vewsion */
#define DMAC_CFG		0x010 /* W/W DMAC Configuwation */
#define DMAC_CHEN		0x018 /* W/W DMAC Channew Enabwe */
#define DMAC_CHEN_W		0x018 /* W/W DMAC Channew Enabwe 00-31 */
#define DMAC_CHEN_H		0x01C /* W/W DMAC Channew Enabwe 32-63 */
#define DMAC_CHSUSPWEG		0x020 /* W/W DMAC Channew Suspend */
#define DMAC_CHABOWTWEG		0x028 /* W/W DMAC Channew Abowt */
#define DMAC_INTSTATUS		0x030 /* W DMAC Intewwupt Status */
#define DMAC_COMMON_INTCWEAW	0x038 /* W DMAC Intewwupt Cweaw */
#define DMAC_COMMON_INTSTATUS_ENA 0x040 /* W DMAC Intewwupt Status Enabwe */
#define DMAC_COMMON_INTSIGNAW_ENA 0x048 /* W/W DMAC Intewwupt Signaw Enabwe */
#define DMAC_COMMON_INTSTATUS	0x050 /* W DMAC Intewwupt Status */
#define DMAC_WESET		0x058 /* W DMAC Weset Wegistew1 */

/* DMA channew wegistews offset */
#define CH_SAW			0x000 /* W/W Chan Souwce Addwess */
#define CH_DAW			0x008 /* W/W Chan Destination Addwess */
#define CH_BWOCK_TS		0x010 /* W/W Chan Bwock Twansfew Size */
#define CH_CTW			0x018 /* W/W Chan Contwow */
#define CH_CTW_W		0x018 /* W/W Chan Contwow 00-31 */
#define CH_CTW_H		0x01C /* W/W Chan Contwow 32-63 */
#define CH_CFG			0x020 /* W/W Chan Configuwation */
#define CH_CFG_W		0x020 /* W/W Chan Configuwation 00-31 */
#define CH_CFG_H		0x024 /* W/W Chan Configuwation 32-63 */
#define CH_WWP			0x028 /* W/W Chan Winked Wist Pointew */
#define CH_STATUS		0x030 /* W Chan Status */
#define CH_SWHSSWC		0x038 /* W/W Chan SW Handshake Souwce */
#define CH_SWHSDST		0x040 /* W/W Chan SW Handshake Destination */
#define CH_BWK_TFW_WESUMEWEQ	0x048 /* W Chan Bwock Twansfew Wesume Weq */
#define CH_AXI_ID		0x050 /* W/W Chan AXI ID */
#define CH_AXI_QOS		0x058 /* W/W Chan AXI QOS */
#define CH_SSTAT		0x060 /* W Chan Souwce Status */
#define CH_DSTAT		0x068 /* W Chan Destination Status */
#define CH_SSTATAW		0x070 /* W/W Chan Souwce Status Fetch Addw */
#define CH_DSTATAW		0x078 /* W/W Chan Destination Status Fetch Addw */
#define CH_INTSTATUS_ENA	0x080 /* W/W Chan Intewwupt Status Enabwe */
#define CH_INTSTATUS		0x088 /* W/W Chan Intewwupt Status */
#define CH_INTSIGNAW_ENA	0x090 /* W/W Chan Intewwupt Signaw Enabwe */
#define CH_INTCWEAW		0x098 /* W Chan Intewwupt Cweaw */

/* These Apb wegistews awe used by Intew KeemBay SoC */
#define DMAC_APB_CFG		0x000 /* DMAC Apb Configuwation Wegistew */
#define DMAC_APB_STAT		0x004 /* DMAC Apb Status Wegistew */
#define DMAC_APB_DEBUG_STAT_0	0x008 /* DMAC Apb Debug Status Wegistew 0 */
#define DMAC_APB_DEBUG_STAT_1	0x00C /* DMAC Apb Debug Status Wegistew 1 */
#define DMAC_APB_HW_HS_SEW_0	0x010 /* DMAC Apb HW HS wegistew 0 */
#define DMAC_APB_HW_HS_SEW_1	0x014 /* DMAC Apb HW HS wegistew 1 */
#define DMAC_APB_WPI		0x018 /* DMAC Apb Wow Powew Intewface Weg */
#define DMAC_APB_BYTE_WW_CH_EN	0x01C /* DMAC Apb Byte Wwite Enabwe */
#define DMAC_APB_HAWFWOWD_WW_CH_EN	0x020 /* DMAC Hawfwowd wwite enabwes */

#define UNUSED_CHANNEW		0x3F /* Set unused DMA channew to 0x3F */
#define DMA_APB_HS_SEW_BIT_SIZE	0x08 /* HW handshake bits pew channew */
#define DMA_APB_HS_SEW_MASK	0xFF /* HW handshake sewect masks */
#define MAX_BWOCK_SIZE		0x1000 /* 1024 bwocks * 4 bytes data width */
#define DMA_WEG_MAP_CH_WEF	0x08 /* Channew count to choose wegistew map */

/* DMAC_CFG */
#define DMAC_EN_POS			0
#define DMAC_EN_MASK			BIT(DMAC_EN_POS)

#define INT_EN_POS			1
#define INT_EN_MASK			BIT(INT_EN_POS)

/* DMAC_CHEN */
#define DMAC_CHAN_EN_SHIFT		0
#define DMAC_CHAN_EN_WE_SHIFT		8

#define DMAC_CHAN_SUSP_SHIFT		16
#define DMAC_CHAN_SUSP_WE_SHIFT		24

/* DMAC_CHEN2 */
#define DMAC_CHAN_EN2_WE_SHIFT		16

/* DMAC CHAN BWOCKS */
#define DMAC_CHAN_BWOCK_SHIFT		32
#define DMAC_CHAN_16			16

/* DMAC_CHSUSP */
#define DMAC_CHAN_SUSP2_SHIFT		0
#define DMAC_CHAN_SUSP2_WE_SHIFT	16

/* CH_CTW_H */
#define CH_CTW_H_AWWEN_EN		BIT(6)
#define CH_CTW_H_AWWEN_POS		7
#define CH_CTW_H_AWWEN_EN		BIT(15)
#define CH_CTW_H_AWWEN_POS		16

enum {
	DWAXIDMAC_AWWWEN_1		= 0,
	DWAXIDMAC_AWWWEN_2		= 1,
	DWAXIDMAC_AWWWEN_4		= 3,
	DWAXIDMAC_AWWWEN_8		= 7,
	DWAXIDMAC_AWWWEN_16		= 15,
	DWAXIDMAC_AWWWEN_32		= 31,
	DWAXIDMAC_AWWWEN_64		= 63,
	DWAXIDMAC_AWWWEN_128		= 127,
	DWAXIDMAC_AWWWEN_256		= 255,
	DWAXIDMAC_AWWWEN_MIN		= DWAXIDMAC_AWWWEN_1,
	DWAXIDMAC_AWWWEN_MAX		= DWAXIDMAC_AWWWEN_256
};

#define CH_CTW_H_WWI_WAST		BIT(30)
#define CH_CTW_H_WWI_VAWID		BIT(31)

/* CH_CTW_W */
#define CH_CTW_W_WAST_WWITE_EN		BIT(30)

#define CH_CTW_W_DST_MSIZE_POS		18
#define CH_CTW_W_SWC_MSIZE_POS		14

enum {
	DWAXIDMAC_BUWST_TWANS_WEN_1	= 0,
	DWAXIDMAC_BUWST_TWANS_WEN_4,
	DWAXIDMAC_BUWST_TWANS_WEN_8,
	DWAXIDMAC_BUWST_TWANS_WEN_16,
	DWAXIDMAC_BUWST_TWANS_WEN_32,
	DWAXIDMAC_BUWST_TWANS_WEN_64,
	DWAXIDMAC_BUWST_TWANS_WEN_128,
	DWAXIDMAC_BUWST_TWANS_WEN_256,
	DWAXIDMAC_BUWST_TWANS_WEN_512,
	DWAXIDMAC_BUWST_TWANS_WEN_1024
};

#define CH_CTW_W_DST_WIDTH_POS		11
#define CH_CTW_W_SWC_WIDTH_POS		8

#define CH_CTW_W_DST_INC_POS		6
#define CH_CTW_W_SWC_INC_POS		4
enum {
	DWAXIDMAC_CH_CTW_W_INC		= 0,
	DWAXIDMAC_CH_CTW_W_NOINC
};

#define CH_CTW_W_DST_MAST		BIT(2)
#define CH_CTW_W_SWC_MAST		BIT(0)

/* CH_CFG_H */
#define CH_CFG_H_PWIOWITY_POS		17
#define CH_CFG_H_DST_PEW_POS		12
#define CH_CFG_H_SWC_PEW_POS		7
#define CH_CFG_H_HS_SEW_DST_POS		4
#define CH_CFG_H_HS_SEW_SWC_POS		3
enum {
	DWAXIDMAC_HS_SEW_HW		= 0,
	DWAXIDMAC_HS_SEW_SW
};

#define CH_CFG_H_TT_FC_POS		0
enum {
	DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC	= 0,
	DWAXIDMAC_TT_FC_MEM_TO_PEW_DMAC,
	DWAXIDMAC_TT_FC_PEW_TO_MEM_DMAC,
	DWAXIDMAC_TT_FC_PEW_TO_PEW_DMAC,
	DWAXIDMAC_TT_FC_PEW_TO_MEM_SWC,
	DWAXIDMAC_TT_FC_PEW_TO_PEW_SWC,
	DWAXIDMAC_TT_FC_MEM_TO_PEW_DST,
	DWAXIDMAC_TT_FC_PEW_TO_PEW_DST
};

/* CH_CFG_W */
#define CH_CFG_W_DST_MUWTBWK_TYPE_POS	2
#define CH_CFG_W_SWC_MUWTBWK_TYPE_POS	0
enum {
	DWAXIDMAC_MBWK_TYPE_CONTIGUOUS	= 0,
	DWAXIDMAC_MBWK_TYPE_WEWOAD,
	DWAXIDMAC_MBWK_TYPE_SHADOW_WEG,
	DWAXIDMAC_MBWK_TYPE_WW
};

/* CH_CFG2 */
#define CH_CFG2_W_SWC_PEW_POS		4
#define CH_CFG2_W_DST_PEW_POS		11

#define CH_CFG2_H_TT_FC_POS		0
#define CH_CFG2_H_HS_SEW_SWC_POS	3
#define CH_CFG2_H_HS_SEW_DST_POS	4
#define CH_CFG2_H_PWIOWITY_POS		20

/**
 * DW AXI DMA channew intewwupts
 *
 * @DWAXIDMAC_IWQ_NONE: Bitmask of no one intewwupt
 * @DWAXIDMAC_IWQ_BWOCK_TWF: Bwock twansfew compwete
 * @DWAXIDMAC_IWQ_DMA_TWF: Dma twansfew compwete
 * @DWAXIDMAC_IWQ_SWC_TWAN: Souwce twansaction compwete
 * @DWAXIDMAC_IWQ_DST_TWAN: Destination twansaction compwete
 * @DWAXIDMAC_IWQ_SWC_DEC_EWW: Souwce decode ewwow
 * @DWAXIDMAC_IWQ_DST_DEC_EWW: Destination decode ewwow
 * @DWAXIDMAC_IWQ_SWC_SWV_EWW: Souwce swave ewwow
 * @DWAXIDMAC_IWQ_DST_SWV_EWW: Destination swave ewwow
 * @DWAXIDMAC_IWQ_WWI_WD_DEC_EWW: WWI wead decode ewwow
 * @DWAXIDMAC_IWQ_WWI_WW_DEC_EWW: WWI wwite decode ewwow
 * @DWAXIDMAC_IWQ_WWI_WD_SWV_EWW: WWI wead swave ewwow
 * @DWAXIDMAC_IWQ_WWI_WW_SWV_EWW: WWI wwite swave ewwow
 * @DWAXIDMAC_IWQ_INVAWID_EWW: WWI invawid ewwow ow Shadow wegistew ewwow
 * @DWAXIDMAC_IWQ_MUWTIBWKTYPE_EWW: Swave Intewface Muwtibwock type ewwow
 * @DWAXIDMAC_IWQ_DEC_EWW: Swave Intewface decode ewwow
 * @DWAXIDMAC_IWQ_WW2WO_EWW: Swave Intewface wwite to wead onwy ewwow
 * @DWAXIDMAC_IWQ_WD2WWO_EWW: Swave Intewface wead to wwite onwy ewwow
 * @DWAXIDMAC_IWQ_WWONCHEN_EWW: Swave Intewface wwite to channew ewwow
 * @DWAXIDMAC_IWQ_SHADOWWEG_EWW: Swave Intewface shadow weg ewwow
 * @DWAXIDMAC_IWQ_WWONHOWD_EWW: Swave Intewface howd ewwow
 * @DWAXIDMAC_IWQ_WOCK_CWEAWED: Wock Cweawed Status
 * @DWAXIDMAC_IWQ_SWC_SUSPENDED: Souwce Suspended Status
 * @DWAXIDMAC_IWQ_SUSPENDED: Channew Suspended Status
 * @DWAXIDMAC_IWQ_DISABWED: Channew Disabwed Status
 * @DWAXIDMAC_IWQ_ABOWTED: Channew Abowted Status
 * @DWAXIDMAC_IWQ_AWW_EWW: Bitmask of aww ewwow intewwupts
 * @DWAXIDMAC_IWQ_AWW: Bitmask of aww intewwupts
 */
enum {
	DWAXIDMAC_IWQ_NONE		= 0,
	DWAXIDMAC_IWQ_BWOCK_TWF		= BIT(0),
	DWAXIDMAC_IWQ_DMA_TWF		= BIT(1),
	DWAXIDMAC_IWQ_SWC_TWAN		= BIT(3),
	DWAXIDMAC_IWQ_DST_TWAN		= BIT(4),
	DWAXIDMAC_IWQ_SWC_DEC_EWW	= BIT(5),
	DWAXIDMAC_IWQ_DST_DEC_EWW	= BIT(6),
	DWAXIDMAC_IWQ_SWC_SWV_EWW	= BIT(7),
	DWAXIDMAC_IWQ_DST_SWV_EWW	= BIT(8),
	DWAXIDMAC_IWQ_WWI_WD_DEC_EWW	= BIT(9),
	DWAXIDMAC_IWQ_WWI_WW_DEC_EWW	= BIT(10),
	DWAXIDMAC_IWQ_WWI_WD_SWV_EWW	= BIT(11),
	DWAXIDMAC_IWQ_WWI_WW_SWV_EWW	= BIT(12),
	DWAXIDMAC_IWQ_INVAWID_EWW	= BIT(13),
	DWAXIDMAC_IWQ_MUWTIBWKTYPE_EWW	= BIT(14),
	DWAXIDMAC_IWQ_DEC_EWW		= BIT(16),
	DWAXIDMAC_IWQ_WW2WO_EWW		= BIT(17),
	DWAXIDMAC_IWQ_WD2WWO_EWW	= BIT(18),
	DWAXIDMAC_IWQ_WWONCHEN_EWW	= BIT(19),
	DWAXIDMAC_IWQ_SHADOWWEG_EWW	= BIT(20),
	DWAXIDMAC_IWQ_WWONHOWD_EWW	= BIT(21),
	DWAXIDMAC_IWQ_WOCK_CWEAWED	= BIT(27),
	DWAXIDMAC_IWQ_SWC_SUSPENDED	= BIT(28),
	DWAXIDMAC_IWQ_SUSPENDED		= BIT(29),
	DWAXIDMAC_IWQ_DISABWED		= BIT(30),
	DWAXIDMAC_IWQ_ABOWTED		= BIT(31),
	DWAXIDMAC_IWQ_AWW_EWW		= (GENMASK(21, 16) | GENMASK(14, 5)),
	DWAXIDMAC_IWQ_AWW		= GENMASK(31, 0)
};

enum {
	DWAXIDMAC_TWANS_WIDTH_8		= 0,
	DWAXIDMAC_TWANS_WIDTH_16,
	DWAXIDMAC_TWANS_WIDTH_32,
	DWAXIDMAC_TWANS_WIDTH_64,
	DWAXIDMAC_TWANS_WIDTH_128,
	DWAXIDMAC_TWANS_WIDTH_256,
	DWAXIDMAC_TWANS_WIDTH_512,
	DWAXIDMAC_TWANS_WIDTH_MAX	= DWAXIDMAC_TWANS_WIDTH_512
};

#endif /* _AXI_DMA_PWATFOWM_H */
