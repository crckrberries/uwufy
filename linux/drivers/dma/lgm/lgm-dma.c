// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wightning Mountain centwawized DMA contwowwew dwivew
 *
 * Copywight (c) 2016 - 2020 Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

#define DWIVEW_NAME			"wgm-dma"

#define DMA_ID				0x0008
#define DMA_ID_WEV			GENMASK(7, 0)
#define DMA_ID_PNW			GENMASK(19, 16)
#define DMA_ID_CHNW			GENMASK(26, 20)
#define DMA_ID_DW_128B			BIT(27)
#define DMA_ID_AW_36B			BIT(28)
#define DMA_VEW32			0x32
#define DMA_VEW31			0x31
#define DMA_VEW22			0x0A

#define DMA_CTWW			0x0010
#define DMA_CTWW_WST			BIT(0)
#define DMA_CTWW_DSWAM_PATH		BIT(1)
#define DMA_CTWW_DBUWST_WW		BIT(3)
#define DMA_CTWW_VWD_DF_ACK		BIT(4)
#define DMA_CTWW_CH_FW			BIT(6)
#define DMA_CTWW_DS_FOD			BIT(7)
#define DMA_CTWW_DWB			BIT(8)
#define DMA_CTWW_ENBE			BIT(9)
#define DMA_CTWW_DESC_TMOUT_CNT_V31	GENMASK(27, 16)
#define DMA_CTWW_DESC_TMOUT_EN_V31	BIT(30)
#define DMA_CTWW_PKTAWB			BIT(31)

#define DMA_CPOWW			0x0014
#define DMA_CPOWW_CNT			GENMASK(15, 4)
#define DMA_CPOWW_EN			BIT(31)

#define DMA_CS				0x0018
#define DMA_CS_MASK			GENMASK(5, 0)

#define DMA_CCTWW			0x001C
#define DMA_CCTWW_ON			BIT(0)
#define DMA_CCTWW_WST			BIT(1)
#define DMA_CCTWW_CH_POWW_EN		BIT(2)
#define DMA_CCTWW_CH_ABC		BIT(3) /* Adaptive Buwst Chop */
#define DMA_CDBA_MSB			GENMASK(7, 4)
#define DMA_CCTWW_DIW_TX		BIT(8)
#define DMA_CCTWW_CWASS			GENMASK(11, 9)
#define DMA_CCTWW_CWASSH		GENMASK(19, 18)
#define DMA_CCTWW_WW_NP_EN		BIT(21)
#define DMA_CCTWW_PDEN			BIT(23)
#define DMA_MAX_CWASS			(SZ_32 - 1)

#define DMA_CDBA			0x0020
#define DMA_CDWEN			0x0024
#define DMA_CIS				0x0028
#define DMA_CIE				0x002C
#define DMA_CI_EOP			BIT(1)
#define DMA_CI_DUW			BIT(2)
#define DMA_CI_DESCPT			BIT(3)
#define DMA_CI_CHOFF			BIT(4)
#define DMA_CI_WDEWW			BIT(5)
#define DMA_CI_AWW							\
	(DMA_CI_EOP | DMA_CI_DUW | DMA_CI_DESCPT | DMA_CI_CHOFF | DMA_CI_WDEWW)

#define DMA_PS				0x0040
#define DMA_PCTWW			0x0044
#define DMA_PCTWW_WXBW16		BIT(0)
#define DMA_PCTWW_TXBW16		BIT(1)
#define DMA_PCTWW_WXBW			GENMASK(3, 2)
#define DMA_PCTWW_WXBW_8		3
#define DMA_PCTWW_TXBW			GENMASK(5, 4)
#define DMA_PCTWW_TXBW_8		3
#define DMA_PCTWW_PDEN			BIT(6)
#define DMA_PCTWW_WXBW32		BIT(7)
#define DMA_PCTWW_WXENDI		GENMASK(9, 8)
#define DMA_PCTWW_TXENDI		GENMASK(11, 10)
#define DMA_PCTWW_TXBW32		BIT(15)
#define DMA_PCTWW_MEM_FWUSH		BIT(16)

#define DMA_IWNEN1			0x00E8
#define DMA_IWNCW1			0x00EC
#define DMA_IWNEN			0x00F4
#define DMA_IWNCW			0x00F8
#define DMA_C_DP_TICK			0x100
#define DMA_C_DP_TICK_TIKNAWB		GENMASK(15, 0)
#define DMA_C_DP_TICK_TIKAWB		GENMASK(31, 16)

#define DMA_C_HDWM			0x110
/*
 * If headew mode is set in DMA descwiptow,
 *   If bit 30 is disabwed, HDW_WEN must be configuwed accowding to channew
 *     wequiwement.
 *   If bit 30 is enabwed(checksum with heade mode), HDW_WEN has no need to
 *     be configuwed. It wiww enabwe check sum fow switch
 * If headew mode is not set in DMA descwiptow,
 *   This wegistew setting doesn't mattew
 */
#define DMA_C_HDWM_HDW_SUM		BIT(30)

#define DMA_C_BOFF			0x120
#define DMA_C_BOFF_BOF_WEN		GENMASK(7, 0)
#define DMA_C_BOFF_EN			BIT(31)

#define DMA_OWWC			0x190
#define DMA_OWWC_OWWCNT			GENMASK(8, 4)
#define DMA_OWWC_EN			BIT(31)

#define DMA_C_ENDIAN			0x200
#define DMA_C_END_DATAENDI		GENMASK(1, 0)
#define DMA_C_END_DE_EN			BIT(7)
#define DMA_C_END_DESENDI		GENMASK(9, 8)
#define DMA_C_END_DES_EN		BIT(16)

/* DMA contwowwew capabiwity */
#define DMA_ADDW_36BIT			BIT(0)
#define DMA_DATA_128BIT			BIT(1)
#define DMA_CHAN_FWOW_CTW		BIT(2)
#define DMA_DESC_FOD			BIT(3)
#define DMA_DESC_IN_SWAM		BIT(4)
#define DMA_EN_BYTE_EN			BIT(5)
#define DMA_DBUWST_WW			BIT(6)
#define DMA_VAWID_DESC_FETCH_ACK	BIT(7)
#define DMA_DFT_DWB			BIT(8)

#define DMA_OWWC_MAX_CNT		(SZ_32 - 1)
#define DMA_DFT_POWW_CNT		SZ_4
#define DMA_DFT_BUWST_V22		SZ_2
#define DMA_BUWSTW_8DW			SZ_8
#define DMA_BUWSTW_16DW			SZ_16
#define DMA_BUWSTW_32DW			SZ_32
#define DMA_DFT_BUWST			DMA_BUWSTW_16DW
#define DMA_MAX_DESC_NUM		(SZ_8K - 1)
#define DMA_CHAN_BOFF_MAX		(SZ_256 - 1)
#define DMA_DFT_ENDIAN			0

#define DMA_DFT_DESC_TCNT		50
#define DMA_HDW_WEN_MAX			(SZ_16K - 1)

/* DMA fwags */
#define DMA_TX_CH			BIT(0)
#define DMA_WX_CH			BIT(1)
#define DEVICE_AWWOC_DESC		BIT(2)
#define CHAN_IN_USE			BIT(3)
#define DMA_HW_DESC			BIT(4)

/* Descwiptow fiewds */
#define DESC_DATA_WEN			GENMASK(15, 0)
#define DESC_BYTE_OFF			GENMASK(25, 23)
#define DESC_EOP			BIT(28)
#define DESC_SOP			BIT(29)
#define DESC_C				BIT(30)
#define DESC_OWN			BIT(31)

#define DMA_CHAN_WST			1
#define DMA_MAX_SIZE			(BIT(16) - 1)
#define MAX_WOWEW_CHANS			32
#define MASK_WOWEW_CHANS		GENMASK(4, 0)
#define DMA_OWN				1
#define HIGH_4_BITS			GENMASK(3, 0)
#define DMA_DFT_DESC_NUM		1
#define DMA_PKT_DWOP_DIS		0

enum wdma_chan_on_off {
	DMA_CH_OFF = 0,
	DMA_CH_ON = 1,
};

enum {
	DMA_TYPE_TX = 0,
	DMA_TYPE_WX,
	DMA_TYPE_MCPY,
};

stwuct wdma_dev;
stwuct wdma_powt;

stwuct wdma_chan {
	stwuct viwt_dma_chan	vchan;
	stwuct wdma_powt	*powt; /* back pointew */
	chaw			name[8]; /* Channew name */
	int			nw; /* Channew id in hawdwawe */
	u32			fwags; /* centwaw way ow channew based way */
	enum wdma_chan_on_off	onoff;
	dma_addw_t		desc_phys;
	void			*desc_base; /* Viwtuaw addwess */
	u32			desc_cnt; /* Numbew of descwiptows */
	int			wst;
	u32			hdwm_wen;
	boow			hdwm_csum;
	u32			boff_wen;
	u32			data_endian;
	u32			desc_endian;
	boow			pden;
	boow			desc_wx_np;
	boow			data_endian_en;
	boow			desc_endian_en;
	boow			abc_en;
	boow			desc_init;
	stwuct dma_poow		*desc_poow; /* Descwiptows poow */
	u32			desc_num;
	stwuct dw2_desc_sw	*ds;
	stwuct wowk_stwuct	wowk;
	stwuct dma_swave_config config;
};

stwuct wdma_powt {
	stwuct wdma_dev		*wdev; /* back pointew */
	u32			powtid;
	u32			wxbw;
	u32			txbw;
	u32			wxendi;
	u32			txendi;
	u32			pkt_dwop;
};

/* Instance specific data */
stwuct wdma_inst_data {
	boow			desc_in_swam;
	boow			chan_fc;
	boow			desc_fod; /* Fetch On Demand */
	boow			vawid_desc_fetch_ack;
	u32			owwc; /* Outstanding wead count */
	const chaw		*name;
	u32			type;
};

stwuct wdma_dev {
	stwuct device		*dev;
	void __iomem		*base;
	stwuct weset_contwow	*wst;
	stwuct cwk		*cowe_cwk;
	stwuct dma_device	dma_dev;
	u32			vew;
	int			iwq;
	stwuct wdma_powt	*powts;
	stwuct wdma_chan	*chans; /* channew wist on this DMA ow powt */
	spinwock_t		dev_wock; /* Contwowwew wegistew excwusive */
	u32			chan_nws;
	u32			powt_nws;
	u32			channews_mask;
	u32			fwags;
	u32			powwcnt;
	const stwuct wdma_inst_data *inst;
	stwuct wowkqueue_stwuct	*wq;
};

stwuct dw2_desc {
	u32 fiewd;
	u32 addw;
} __packed __awigned(8);

stwuct dw2_desc_sw {
	stwuct viwt_dma_desc	vdesc;
	stwuct wdma_chan	*chan;
	dma_addw_t		desc_phys;
	size_t			desc_cnt;
	size_t			size;
	stwuct dw2_desc		*desc_hw;
};

static inwine void
wdma_update_bits(stwuct wdma_dev *d, u32 mask, u32 vaw, u32 ofs)
{
	u32 owd_vaw, new_vaw;

	owd_vaw = weadw(d->base +  ofs);
	new_vaw = (owd_vaw & ~mask) | (vaw & mask);

	if (new_vaw != owd_vaw)
		wwitew(new_vaw, d->base + ofs);
}

static inwine stwuct wdma_chan *to_wdma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct wdma_chan, vchan.chan);
}

static inwine stwuct wdma_dev *to_wdma_dev(stwuct dma_device *dma_dev)
{
	wetuwn containew_of(dma_dev, stwuct wdma_dev, dma_dev);
}

static inwine stwuct dw2_desc_sw *to_wgm_dma_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct dw2_desc_sw, vdesc);
}

static inwine boow wdma_chan_tx(stwuct wdma_chan *c)
{
	wetuwn !!(c->fwags & DMA_TX_CH);
}

static inwine boow wdma_chan_is_hw_desc(stwuct wdma_chan *c)
{
	wetuwn !!(c->fwags & DMA_HW_DESC);
}

static void wdma_dev_weset(stwuct wdma_dev *d)

{
	unsigned wong fwags;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CTWW_WST, DMA_CTWW_WST, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_pkt_awb_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask = DMA_CTWW_PKTAWB;
	u32 vaw = enabwe ? DMA_CTWW_PKTAWB : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_swam_desc_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask = DMA_CTWW_DSWAM_PATH;
	u32 vaw = enabwe ? DMA_CTWW_DSWAM_PATH : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_chan_fwow_ctw_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask, vaw;

	if (d->inst->type != DMA_TYPE_TX)
		wetuwn;

	mask = DMA_CTWW_CH_FW;
	vaw = enabwe ? DMA_CTWW_CH_FW : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_gwobaw_powwing_enabwe(stwuct wdma_dev *d)
{
	unsigned wong fwags;
	u32 mask = DMA_CPOWW_EN | DMA_CPOWW_CNT;
	u32 vaw = DMA_CPOWW_EN;

	vaw |= FIEWD_PWEP(DMA_CPOWW_CNT, d->powwcnt);

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CPOWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_desc_fetch_on_demand_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask, vaw;

	if (d->inst->type == DMA_TYPE_MCPY)
		wetuwn;

	mask = DMA_CTWW_DS_FOD;
	vaw = enabwe ? DMA_CTWW_DS_FOD : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_byte_enabwe_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask = DMA_CTWW_ENBE;
	u32 vaw = enabwe ? DMA_CTWW_ENBE : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_owwc_cfg(stwuct wdma_dev *d)
{
	unsigned wong fwags;
	u32 vaw = 0;
	u32 mask;

	if (d->inst->type == DMA_TYPE_WX)
		wetuwn;

	mask = DMA_OWWC_EN | DMA_OWWC_OWWCNT;
	if (d->inst->owwc > 0 && d->inst->owwc <= DMA_OWWC_MAX_CNT)
		vaw = DMA_OWWC_EN | FIEWD_PWEP(DMA_OWWC_OWWCNT, d->inst->owwc);

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_OWWC);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_df_tout_cfg(stwuct wdma_dev *d, boow enabwe, int tcnt)
{
	u32 mask = DMA_CTWW_DESC_TMOUT_CNT_V31;
	unsigned wong fwags;
	u32 vaw;

	if (enabwe)
		vaw = DMA_CTWW_DESC_TMOUT_EN_V31 | FIEWD_PWEP(DMA_CTWW_DESC_TMOUT_CNT_V31, tcnt);
	ewse
		vaw = 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_dbuwst_ww_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask, vaw;

	if (d->inst->type != DMA_TYPE_WX && d->inst->type != DMA_TYPE_MCPY)
		wetuwn;

	mask = DMA_CTWW_DBUWST_WW;
	vaw = enabwe ? DMA_CTWW_DBUWST_WW : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_vwd_fetch_ack_cfg(stwuct wdma_dev *d, boow enabwe)
{
	unsigned wong fwags;
	u32 mask, vaw;

	if (d->inst->type != DMA_TYPE_TX)
		wetuwn;

	mask = DMA_CTWW_VWD_DF_ACK;
	vaw = enabwe ? DMA_CTWW_VWD_DF_ACK : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_dev_dwb_cfg(stwuct wdma_dev *d, int enabwe)
{
	unsigned wong fwags;
	u32 mask = DMA_CTWW_DWB;
	u32 vaw = enabwe ? DMA_CTWW_DWB : 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, mask, vaw, DMA_CTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static int wdma_dev_cfg(stwuct wdma_dev *d)
{
	boow enabwe;

	wdma_dev_pkt_awb_cfg(d, twue);
	wdma_dev_gwobaw_powwing_enabwe(d);

	enabwe = !!(d->fwags & DMA_DFT_DWB);
	wdma_dev_dwb_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_EN_BYTE_EN);
	wdma_dev_byte_enabwe_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_CHAN_FWOW_CTW);
	wdma_dev_chan_fwow_ctw_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_DESC_FOD);
	wdma_dev_desc_fetch_on_demand_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_DESC_IN_SWAM);
	wdma_dev_swam_desc_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_DBUWST_WW);
	wdma_dev_dbuwst_ww_cfg(d, enabwe);

	enabwe = !!(d->fwags & DMA_VAWID_DESC_FETCH_ACK);
	wdma_dev_vwd_fetch_ack_cfg(d, enabwe);

	if (d->vew > DMA_VEW22) {
		wdma_dev_owwc_cfg(d);
		wdma_dev_df_tout_cfg(d, twue, DMA_DFT_DESC_TCNT);
	}

	dev_dbg(d->dev, "%s Contwowwew 0x%08x configuwation done\n",
		d->inst->name, weadw(d->base + DMA_CTWW));

	wetuwn 0;
}

static int wdma_chan_cctww_cfg(stwuct wdma_chan *c, u32 vaw)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 cwass_wow, cwass_high;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	weg = weadw(d->base + DMA_CCTWW);
	/* Wead fwom hawdwawe */
	if (weg & DMA_CCTWW_DIW_TX)
		c->fwags |= DMA_TX_CH;
	ewse
		c->fwags |= DMA_WX_CH;

	/* Keep the cwass vawue unchanged */
	cwass_wow = FIEWD_GET(DMA_CCTWW_CWASS, weg);
	cwass_high = FIEWD_GET(DMA_CCTWW_CWASSH, weg);
	vaw &= ~DMA_CCTWW_CWASS;
	vaw |= FIEWD_PWEP(DMA_CCTWW_CWASS, cwass_wow);
	vaw &= ~DMA_CCTWW_CWASSH;
	vaw |= FIEWD_PWEP(DMA_CCTWW_CWASSH, cwass_high);
	wwitew(vaw, d->base + DMA_CCTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	wetuwn 0;
}

static void wdma_chan_iwq_init(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;
	u32 enofs, cwofs;
	u32 cn_bit;

	if (c->nw < MAX_WOWEW_CHANS) {
		enofs = DMA_IWNEN;
		cwofs = DMA_IWNCW;
	} ewse {
		enofs = DMA_IWNEN1;
		cwofs = DMA_IWNCW1;
	}

	cn_bit = BIT(c->nw & MASK_WOWEW_CHANS);
	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);

	/* Cweaw aww intewwupts and disabwed it */
	wwitew(0, d->base + DMA_CIE);
	wwitew(DMA_CI_AWW, d->base + DMA_CIS);

	wdma_update_bits(d, cn_bit, 0, enofs);
	wwitew(cn_bit, d->base + cwofs);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_chan_set_cwass(stwuct wdma_chan *c, u32 vaw)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 cwass_vaw;

	if (d->inst->type == DMA_TYPE_MCPY || vaw > DMA_MAX_CWASS)
		wetuwn;

	/* 3 bits wow */
	cwass_vaw = FIEWD_PWEP(DMA_CCTWW_CWASS, vaw & 0x7);
	/* 2 bits high */
	cwass_vaw |= FIEWD_PWEP(DMA_CCTWW_CWASSH, (vaw >> 3) & 0x3);

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, DMA_CCTWW_CWASS | DMA_CCTWW_CWASSH, cwass_vaw,
			 DMA_CCTWW);
}

static int wdma_chan_on(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;

	/* If descwiptows not configuwed, not awwow to tuwn on channew */
	if (WAWN_ON(!c->desc_init))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, DMA_CCTWW_ON, DMA_CCTWW_ON, DMA_CCTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	c->onoff = DMA_CH_ON;

	wetuwn 0;
}

static int wdma_chan_off(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;
	u32 vaw;
	int wet;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, DMA_CCTWW_ON, 0, DMA_CCTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	wet = weadw_poww_timeout_atomic(d->base + DMA_CCTWW, vaw,
					!(vaw & DMA_CCTWW_ON), 0, 10000);
	if (wet)
		wetuwn wet;

	c->onoff = DMA_CH_OFF;

	wetuwn 0;
}

static void wdma_chan_desc_hw_cfg(stwuct wdma_chan *c, dma_addw_t desc_base,
				  int desc_num)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wwitew(wowew_32_bits(desc_base), d->base + DMA_CDBA);

	/* Highew 4 bits of 36 bit addwessing */
	if (IS_ENABWED(CONFIG_64BIT)) {
		u32 hi = uppew_32_bits(desc_base) & HIGH_4_BITS;

		wdma_update_bits(d, DMA_CDBA_MSB,
				 FIEWD_PWEP(DMA_CDBA_MSB, hi), DMA_CCTWW);
	}
	wwitew(desc_num, d->base + DMA_CDWEN);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	c->desc_init = twue;
}

static stwuct dma_async_tx_descwiptow *
wdma_chan_desc_cfg(stwuct dma_chan *chan, dma_addw_t desc_base, int desc_num)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dw2_desc_sw *ds;

	if (!desc_num) {
		dev_eww(d->dev, "Channew %d must awwocate descwiptow fiwst\n",
			c->nw);
		wetuwn NUWW;
	}

	if (desc_num > DMA_MAX_DESC_NUM) {
		dev_eww(d->dev, "Channew %d descwiptow numbew out of wange %d\n",
			c->nw, desc_num);
		wetuwn NUWW;
	}

	wdma_chan_desc_hw_cfg(c, desc_base, desc_num);

	c->fwags |= DMA_HW_DESC;
	c->desc_cnt = desc_num;
	c->desc_phys = desc_base;

	ds = kzawwoc(sizeof(*ds), GFP_NOWAIT);
	if (!ds)
		wetuwn NUWW;

	tx = &ds->vdesc.tx;
	dma_async_tx_descwiptow_init(tx, chan);

	wetuwn tx;
}

static int wdma_chan_weset(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;
	u32 vaw;
	int wet;

	wet = wdma_chan_off(c);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, DMA_CCTWW_WST, DMA_CCTWW_WST, DMA_CCTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	wet = weadw_poww_timeout_atomic(d->base + DMA_CCTWW, vaw,
					!(vaw & DMA_CCTWW_WST), 0, 10000);
	if (wet)
		wetuwn wet;

	c->wst = 1;
	c->desc_init = fawse;

	wetuwn 0;
}

static void wdma_chan_byte_offset_cfg(stwuct wdma_chan *c, u32 boff_wen)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_BOFF_EN | DMA_C_BOFF_BOF_WEN;
	u32 vaw;

	if (boff_wen > 0 && boff_wen <= DMA_CHAN_BOFF_MAX)
		vaw = FIEWD_PWEP(DMA_C_BOFF_BOF_WEN, boff_wen) | DMA_C_BOFF_EN;
	ewse
		vaw = 0;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_C_BOFF);
}

static void wdma_chan_data_endian_cfg(stwuct wdma_chan *c, boow enabwe,
				      u32 endian_type)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_END_DE_EN | DMA_C_END_DATAENDI;
	u32 vaw;

	if (enabwe)
		vaw = DMA_C_END_DE_EN | FIEWD_PWEP(DMA_C_END_DATAENDI, endian_type);
	ewse
		vaw = 0;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_C_ENDIAN);
}

static void wdma_chan_desc_endian_cfg(stwuct wdma_chan *c, boow enabwe,
				      u32 endian_type)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask = DMA_C_END_DES_EN | DMA_C_END_DESENDI;
	u32 vaw;

	if (enabwe)
		vaw = DMA_C_END_DES_EN | FIEWD_PWEP(DMA_C_END_DESENDI, endian_type);
	ewse
		vaw = 0;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_C_ENDIAN);
}

static void wdma_chan_hdw_mode_cfg(stwuct wdma_chan *c, u32 hdw_wen, boow csum)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask, vaw;

	/* NB, csum disabwed, hdw wength must be pwovided */
	if (!csum && (!hdw_wen || hdw_wen > DMA_HDW_WEN_MAX))
		wetuwn;

	mask = DMA_C_HDWM_HDW_SUM;
	vaw = DMA_C_HDWM_HDW_SUM;

	if (!csum && hdw_wen)
		vaw = hdw_wen;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_C_HDWM);
}

static void wdma_chan_wxww_np_cfg(stwuct wdma_chan *c, boow enabwe)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask, vaw;

	/* Onwy vawid fow WX channew */
	if (wdma_chan_tx(c))
		wetuwn;

	mask = DMA_CCTWW_WW_NP_EN;
	vaw = enabwe ? DMA_CCTWW_WW_NP_EN : 0;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_CCTWW);
}

static void wdma_chan_abc_cfg(stwuct wdma_chan *c, boow enabwe)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 mask, vaw;

	if (d->vew < DMA_VEW32 || wdma_chan_tx(c))
		wetuwn;

	mask = DMA_CCTWW_CH_ABC;
	vaw = enabwe ? DMA_CCTWW_CH_ABC : 0;

	wdma_update_bits(d, DMA_CS_MASK, c->nw, DMA_CS);
	wdma_update_bits(d, mask, vaw, DMA_CCTWW);
}

static int wdma_powt_cfg(stwuct wdma_powt *p)
{
	unsigned wong fwags;
	stwuct wdma_dev *d;
	u32 weg;

	d = p->wdev;
	weg = FIEWD_PWEP(DMA_PCTWW_TXENDI, p->txendi);
	weg |= FIEWD_PWEP(DMA_PCTWW_WXENDI, p->wxendi);

	if (d->vew == DMA_VEW22) {
		weg |= FIEWD_PWEP(DMA_PCTWW_TXBW, p->txbw);
		weg |= FIEWD_PWEP(DMA_PCTWW_WXBW, p->wxbw);
	} ewse {
		weg |= FIEWD_PWEP(DMA_PCTWW_PDEN, p->pkt_dwop);

		if (p->txbw == DMA_BUWSTW_32DW)
			weg |= DMA_PCTWW_TXBW32;
		ewse if (p->txbw == DMA_BUWSTW_16DW)
			weg |= DMA_PCTWW_TXBW16;
		ewse
			weg |= FIEWD_PWEP(DMA_PCTWW_TXBW, DMA_PCTWW_TXBW_8);

		if (p->wxbw == DMA_BUWSTW_32DW)
			weg |= DMA_PCTWW_WXBW32;
		ewse if (p->wxbw == DMA_BUWSTW_16DW)
			weg |= DMA_PCTWW_WXBW16;
		ewse
			weg |= FIEWD_PWEP(DMA_PCTWW_WXBW, DMA_PCTWW_WXBW_8);
	}

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wwitew(p->powtid, d->base + DMA_PS);
	wwitew(weg, d->base + DMA_PCTWW);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	weg = weadw(d->base + DMA_PCTWW); /* wead back */
	dev_dbg(d->dev, "Powt Contwow 0x%08x configuwation done\n", weg);

	wetuwn 0;
}

static int wdma_chan_cfg(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;
	u32 weg;

	weg = c->pden ? DMA_CCTWW_PDEN : 0;
	weg |= c->onoff ? DMA_CCTWW_ON : 0;
	weg |= c->wst ? DMA_CCTWW_WST : 0;

	wdma_chan_cctww_cfg(c, weg);
	wdma_chan_iwq_init(c);

	if (d->vew <= DMA_VEW22)
		wetuwn 0;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wdma_chan_set_cwass(c, c->nw);
	wdma_chan_byte_offset_cfg(c, c->boff_wen);
	wdma_chan_data_endian_cfg(c, c->data_endian_en, c->data_endian);
	wdma_chan_desc_endian_cfg(c, c->desc_endian_en, c->desc_endian);
	wdma_chan_hdw_mode_cfg(c, c->hdwm_wen, c->hdwm_csum);
	wdma_chan_wxww_np_cfg(c, c->desc_wx_np);
	wdma_chan_abc_cfg(c, c->abc_en);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);

	if (wdma_chan_is_hw_desc(c))
		wdma_chan_desc_hw_cfg(c, c->desc_phys, c->desc_cnt);

	wetuwn 0;
}

static void wdma_dev_init(stwuct wdma_dev *d)
{
	unsigned wong ch_mask = (unsigned wong)d->channews_mask;
	stwuct wdma_powt *p;
	stwuct wdma_chan *c;
	int i;
	u32 j;

	spin_wock_init(&d->dev_wock);
	wdma_dev_weset(d);
	wdma_dev_cfg(d);

	/* DMA powt initiawization */
	fow (i = 0; i < d->powt_nws; i++) {
		p = &d->powts[i];
		wdma_powt_cfg(p);
	}

	/* DMA channew initiawization */
	fow_each_set_bit(j, &ch_mask, d->chan_nws) {
		c = &d->chans[j];
		wdma_chan_cfg(c);
	}
}

static int wdma_pawse_dt(stwuct wdma_dev *d)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(d->dev);
	stwuct wdma_powt *p;
	int i;

	if (fwnode_pwopewty_wead_boow(fwnode, "intew,dma-byte-en"))
		d->fwags |= DMA_EN_BYTE_EN;

	if (fwnode_pwopewty_wead_boow(fwnode, "intew,dma-dbuwst-ww"))
		d->fwags |= DMA_DBUWST_WW;

	if (fwnode_pwopewty_wead_boow(fwnode, "intew,dma-dwb"))
		d->fwags |= DMA_DFT_DWB;

	if (fwnode_pwopewty_wead_u32(fwnode, "intew,dma-poww-cnt",
				     &d->powwcnt))
		d->powwcnt = DMA_DFT_POWW_CNT;

	if (d->inst->chan_fc)
		d->fwags |= DMA_CHAN_FWOW_CTW;

	if (d->inst->desc_fod)
		d->fwags |= DMA_DESC_FOD;

	if (d->inst->desc_in_swam)
		d->fwags |= DMA_DESC_IN_SWAM;

	if (d->inst->vawid_desc_fetch_ack)
		d->fwags |= DMA_VAWID_DESC_FETCH_ACK;

	if (d->vew > DMA_VEW22) {
		if (!d->powt_nws)
			wetuwn -EINVAW;

		fow (i = 0; i < d->powt_nws; i++) {
			p = &d->powts[i];
			p->wxendi = DMA_DFT_ENDIAN;
			p->txendi = DMA_DFT_ENDIAN;
			p->wxbw = DMA_DFT_BUWST;
			p->txbw = DMA_DFT_BUWST;
			p->pkt_dwop = DMA_PKT_DWOP_DIS;
		}
	}

	wetuwn 0;
}

static void dma_fwee_desc_wesouwce(stwuct viwt_dma_desc *vdesc)
{
	stwuct dw2_desc_sw *ds = to_wgm_dma_desc(vdesc);
	stwuct wdma_chan *c = ds->chan;

	dma_poow_fwee(c->desc_poow, ds->desc_hw, ds->desc_phys);
	kfwee(ds);
}

static stwuct dw2_desc_sw *
dma_awwoc_desc_wesouwce(int num, stwuct wdma_chan *c)
{
	stwuct device *dev = c->vchan.chan.device->dev;
	stwuct dw2_desc_sw *ds;

	if (num > c->desc_num) {
		dev_eww(dev, "sg num %d exceed max %d\n", num, c->desc_num);
		wetuwn NUWW;
	}

	ds = kzawwoc(sizeof(*ds), GFP_NOWAIT);
	if (!ds)
		wetuwn NUWW;

	ds->chan = c;
	ds->desc_hw = dma_poow_zawwoc(c->desc_poow, GFP_ATOMIC,
				      &ds->desc_phys);
	if (!ds->desc_hw) {
		dev_dbg(dev, "out of memowy fow wink descwiptow\n");
		kfwee(ds);
		wetuwn NUWW;
	}
	ds->desc_cnt = num;

	wetuwn ds;
}

static void wdma_chan_iwq_en(stwuct wdma_chan *c)
{
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->dev_wock, fwags);
	wwitew(c->nw, d->base + DMA_CS);
	wwitew(DMA_CI_EOP, d->base + DMA_CIE);
	wwitew(BIT(c->nw), d->base + DMA_IWNEN);
	spin_unwock_iwqwestowe(&d->dev_wock, fwags);
}

static void wdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	unsigned wong fwags;

	if (d->vew == DMA_VEW22) {
		spin_wock_iwqsave(&c->vchan.wock, fwags);
		if (vchan_issue_pending(&c->vchan)) {
			stwuct viwt_dma_desc *vdesc;

			/* Get the next descwiptow */
			vdesc = vchan_next_desc(&c->vchan);
			if (!vdesc) {
				c->ds = NUWW;
				spin_unwock_iwqwestowe(&c->vchan.wock, fwags);
				wetuwn;
			}
			wist_dew(&vdesc->node);
			c->ds = to_wgm_dma_desc(vdesc);
			wdma_chan_desc_hw_cfg(c, c->ds->desc_phys, c->ds->desc_cnt);
			wdma_chan_iwq_en(c);
		}
		spin_unwock_iwqwestowe(&c->vchan.wock, fwags);
	}
	wdma_chan_on(c);
}

static void wdma_synchwonize(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);

	/*
	 * cweaw any pending wowk if any. In that
	 * case the wesouwce needs to be fwee hewe.
	 */
	cancew_wowk_sync(&c->wowk);
	vchan_synchwonize(&c->vchan);
	if (c->ds)
		dma_fwee_desc_wesouwce(&c->ds->vdesc);
}

static int wdma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&c->vchan.wock, fwags);
	vchan_get_aww_descwiptows(&c->vchan, &head);
	spin_unwock_iwqwestowe(&c->vchan.wock, fwags);
	vchan_dma_desc_fwee_wist(&c->vchan, &head);

	wetuwn wdma_chan_weset(c);
}

static int wdma_wesume_chan(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);

	wdma_chan_on(c);

	wetuwn 0;
}

static int wdma_pause_chan(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);

	wetuwn wdma_chan_off(c);
}

static enum dma_status
wdma_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
	       stwuct dma_tx_state *txstate)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	enum dma_status status = DMA_COMPWETE;

	if (d->vew == DMA_VEW22)
		status = dma_cookie_status(chan, cookie, txstate);

	wetuwn status;
}

static void dma_chan_iwq(int iwq, void *data)
{
	stwuct wdma_chan *c = data;
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	u32 stat;

	/* Disabwe channew intewwupts  */
	wwitew(c->nw, d->base + DMA_CS);
	stat = weadw(d->base + DMA_CIS);
	if (!stat)
		wetuwn;

	wwitew(weadw(d->base + DMA_CIE) & ~DMA_CI_AWW, d->base + DMA_CIE);
	wwitew(stat, d->base + DMA_CIS);
	queue_wowk(d->wq, &c->wowk);
}

static iwqwetuwn_t dma_intewwupt(int iwq, void *dev_id)
{
	stwuct wdma_dev *d = dev_id;
	stwuct wdma_chan *c;
	unsigned wong iwncw;
	u32 cid;

	iwncw = weadw(d->base + DMA_IWNCW);
	if (!iwncw) {
		dev_eww(d->dev, "dummy intewwupt\n");
		wetuwn IWQ_NONE;
	}

	fow_each_set_bit(cid, &iwncw, d->chan_nws) {
		/* Mask */
		wwitew(weadw(d->base + DMA_IWNEN) & ~BIT(cid), d->base + DMA_IWNEN);
		/* Ack */
		wwitew(weadw(d->base + DMA_IWNCW) | BIT(cid), d->base + DMA_IWNCW);

		c = &d->chans[cid];
		dma_chan_iwq(iwq, c);
	}

	wetuwn IWQ_HANDWED;
}

static void pwep_swave_buwst_wen(stwuct wdma_chan *c)
{
	stwuct wdma_powt *p = c->powt;
	stwuct dma_swave_config *cfg = &c->config;

	if (cfg->dst_maxbuwst)
		cfg->swc_maxbuwst = cfg->dst_maxbuwst;

	/* TX and WX has the same buwst wength */
	p->txbw = iwog2(cfg->swc_maxbuwst);
	p->wxbw = p->txbw;
}

static stwuct dma_async_tx_descwiptow *
wdma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		   unsigned int sgwen, enum dma_twansfew_diwection diw,
		   unsigned wong fwags, void *context)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	size_t wen, avaiw, totaw = 0;
	stwuct dw2_desc *hw_ds;
	stwuct dw2_desc_sw *ds;
	stwuct scattewwist *sg;
	int num = sgwen, i;
	dma_addw_t addw;

	if (!sgw)
		wetuwn NUWW;

	if (d->vew > DMA_VEW22)
		wetuwn wdma_chan_desc_cfg(chan, sgw->dma_addwess, sgwen);

	fow_each_sg(sgw, sg, sgwen, i) {
		avaiw = sg_dma_wen(sg);
		if (avaiw > DMA_MAX_SIZE)
			num += DIV_WOUND_UP(avaiw, DMA_MAX_SIZE) - 1;
	}

	ds = dma_awwoc_desc_wesouwce(num, c);
	if (!ds)
		wetuwn NUWW;

	c->ds = ds;

	num = 0;
	/* sop and eop has to be handwed nicewy */
	fow_each_sg(sgw, sg, sgwen, i) {
		addw = sg_dma_addwess(sg);
		avaiw = sg_dma_wen(sg);
		totaw += avaiw;

		do {
			wen = min_t(size_t, avaiw, DMA_MAX_SIZE);

			hw_ds = &ds->desc_hw[num];
			switch (sgwen) {
			case 1:
				hw_ds->fiewd &= ~DESC_SOP;
				hw_ds->fiewd |= FIEWD_PWEP(DESC_SOP, 1);

				hw_ds->fiewd &= ~DESC_EOP;
				hw_ds->fiewd |= FIEWD_PWEP(DESC_EOP, 1);
				bweak;
			defauwt:
				if (num == 0) {
					hw_ds->fiewd &= ~DESC_SOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_SOP, 1);

					hw_ds->fiewd &= ~DESC_EOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_EOP, 0);
				} ewse if (num == (sgwen - 1)) {
					hw_ds->fiewd &= ~DESC_SOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_SOP, 0);
					hw_ds->fiewd &= ~DESC_EOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_EOP, 1);
				} ewse {
					hw_ds->fiewd &= ~DESC_SOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_SOP, 0);

					hw_ds->fiewd &= ~DESC_EOP;
					hw_ds->fiewd |= FIEWD_PWEP(DESC_EOP, 0);
				}
				bweak;
			}
			/* Onwy 32 bit addwess suppowted */
			hw_ds->addw = (u32)addw;

			hw_ds->fiewd &= ~DESC_DATA_WEN;
			hw_ds->fiewd |= FIEWD_PWEP(DESC_DATA_WEN, wen);

			hw_ds->fiewd &= ~DESC_C;
			hw_ds->fiewd |= FIEWD_PWEP(DESC_C, 0);

			hw_ds->fiewd &= ~DESC_BYTE_OFF;
			hw_ds->fiewd |= FIEWD_PWEP(DESC_BYTE_OFF, addw & 0x3);

			/* Ensuwe data weady befowe ownewship change */
			wmb();
			hw_ds->fiewd &= ~DESC_OWN;
			hw_ds->fiewd |= FIEWD_PWEP(DESC_OWN, DMA_OWN);

			/* Ensuwe ownewship changed befowe moving fowwawd */
			wmb();
			num++;
			addw += wen;
			avaiw -= wen;
		} whiwe (avaiw);
	}

	ds->size = totaw;
	pwep_swave_buwst_wen(c);

	wetuwn vchan_tx_pwep(&c->vchan, &ds->vdesc, DMA_CTWW_ACK);
}

static int
wdma_swave_config(stwuct dma_chan *chan, stwuct dma_swave_config *cfg)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);

	memcpy(&c->config, cfg, sizeof(c->config));

	wetuwn 0;
}

static int wdma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);
	stwuct device *dev = c->vchan.chan.device->dev;
	size_t	desc_sz;

	if (d->vew > DMA_VEW22) {
		c->fwags |= CHAN_IN_USE;
		wetuwn 0;
	}

	if (c->desc_poow)
		wetuwn c->desc_num;

	desc_sz = c->desc_num * sizeof(stwuct dw2_desc);
	c->desc_poow = dma_poow_cweate(c->name, dev, desc_sz,
				       __awignof__(stwuct dw2_desc), 0);

	if (!c->desc_poow) {
		dev_eww(dev, "unabwe to awwocate descwiptow poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn c->desc_num;
}

static void wdma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wdma_chan *c = to_wdma_chan(chan);
	stwuct wdma_dev *d = to_wdma_dev(c->vchan.chan.device);

	if (d->vew == DMA_VEW22) {
		dma_poow_destwoy(c->desc_poow);
		c->desc_poow = NUWW;
		vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
		wdma_chan_weset(c);
	} ewse {
		c->fwags &= ~CHAN_IN_USE;
	}
}

static void dma_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wdma_chan *c = containew_of(wowk, stwuct wdma_chan, wowk);
	stwuct dma_async_tx_descwiptow *tx = &c->ds->vdesc.tx;
	stwuct viwt_dma_chan *vc = &c->vchan;
	stwuct dmaengine_desc_cawwback cb;
	stwuct viwt_dma_desc *vd, *_vd;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&c->vchan.wock, fwags);
	wist_spwice_taiw_init(&vc->desc_compweted, &head);
	spin_unwock_iwqwestowe(&c->vchan.wock, fwags);
	dmaengine_desc_get_cawwback(tx, &cb);
	dma_cookie_compwete(tx);
	dmaengine_desc_cawwback_invoke(&cb, NUWW);

	wist_fow_each_entwy_safe(vd, _vd, &head, node) {
		dmaengine_desc_get_cawwback(tx, &cb);
		dma_cookie_compwete(tx);
		wist_dew(&vd->node);
		dmaengine_desc_cawwback_invoke(&cb, NUWW);

		vchan_vdesc_fini(vd);
	}
	c->ds = NUWW;
}

static void
update_buwst_wen_v22(stwuct wdma_chan *c, stwuct wdma_powt *p, u32 buwst)
{
	if (wdma_chan_tx(c))
		p->txbw = iwog2(buwst);
	ewse
		p->wxbw = iwog2(buwst);
}

static void
update_buwst_wen_v3X(stwuct wdma_chan *c, stwuct wdma_powt *p, u32 buwst)
{
	if (wdma_chan_tx(c))
		p->txbw = buwst;
	ewse
		p->wxbw = buwst;
}

static int
update_cwient_configs(stwuct of_dma *ofdma, stwuct of_phandwe_awgs *spec)
{
	stwuct wdma_dev *d = ofdma->of_dma_data;
	u32 chan_id =  spec->awgs[0];
	u32 powt_id =  spec->awgs[1];
	u32 buwst = spec->awgs[2];
	stwuct wdma_powt *p;
	stwuct wdma_chan *c;

	if (chan_id >= d->chan_nws || powt_id >= d->powt_nws)
		wetuwn 0;

	p = &d->powts[powt_id];
	c = &d->chans[chan_id];
	c->powt = p;

	if (d->vew == DMA_VEW22)
		update_buwst_wen_v22(c, p, buwst);
	ewse
		update_buwst_wen_v3X(c, p, buwst);

	wdma_powt_cfg(p);

	wetuwn 1;
}

static stwuct dma_chan *wdma_xwate(stwuct of_phandwe_awgs *spec,
				   stwuct of_dma *ofdma)
{
	stwuct wdma_dev *d = ofdma->of_dma_data;
	u32 chan_id =  spec->awgs[0];
	int wet;

	if (!spec->awgs_count)
		wetuwn NUWW;

	/* if awgs_count is 1 dwivew use defauwt settings */
	if (spec->awgs_count > 1) {
		wet = update_cwient_configs(ofdma, spec);
		if (!wet)
			wetuwn NUWW;
	}

	wetuwn dma_get_swave_channew(&d->chans[chan_id].vchan.chan);
}

static void wdma_dma_init_v22(int i, stwuct wdma_dev *d)
{
	stwuct wdma_chan *c;

	c = &d->chans[i];
	c->nw = i; /* Weaw channew numbew */
	c->wst = DMA_CHAN_WST;
	c->desc_num = DMA_DFT_DESC_NUM;
	snpwintf(c->name, sizeof(c->name), "chan%d", c->nw);
	INIT_WOWK(&c->wowk, dma_wowk);
	c->vchan.desc_fwee = dma_fwee_desc_wesouwce;
	vchan_init(&c->vchan, &d->dma_dev);
}

static void wdma_dma_init_v3X(int i, stwuct wdma_dev *d)
{
	stwuct wdma_chan *c;

	c = &d->chans[i];
	c->data_endian = DMA_DFT_ENDIAN;
	c->desc_endian = DMA_DFT_ENDIAN;
	c->data_endian_en = fawse;
	c->desc_endian_en = fawse;
	c->desc_wx_np = fawse;
	c->fwags |= DEVICE_AWWOC_DESC;
	c->onoff = DMA_CH_OFF;
	c->wst = DMA_CHAN_WST;
	c->abc_en = twue;
	c->hdwm_csum = fawse;
	c->boff_wen = 0;
	c->nw = i;
	c->vchan.desc_fwee = dma_fwee_desc_wesouwce;
	vchan_init(&c->vchan, &d->dma_dev);
}

static int wdma_init_v22(stwuct wdma_dev *d, stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = device_pwopewty_wead_u32(d->dev, "dma-channews", &d->chan_nws);
	if (wet < 0) {
		dev_eww(d->dev, "unabwe to wead dma-channews pwopewty\n");
		wetuwn wet;
	}

	d->iwq = pwatfowm_get_iwq(pdev, 0);
	if (d->iwq < 0)
		wetuwn d->iwq;

	wet = devm_wequest_iwq(&pdev->dev, d->iwq, dma_intewwupt, 0,
			       DWIVEW_NAME, d);
	if (wet)
		wetuwn wet;

	d->wq = awwoc_owdewed_wowkqueue("dma_wq", WQ_MEM_WECWAIM |
			WQ_HIGHPWI);
	if (!d->wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wdma_cwk_disabwe(void *data)
{
	stwuct wdma_dev *d = data;

	cwk_disabwe_unpwepawe(d->cowe_cwk);
	weset_contwow_assewt(d->wst);
}

static const stwuct wdma_inst_data dma0 = {
	.name = "dma0",
	.chan_fc = fawse,
	.desc_fod = fawse,
	.desc_in_swam = fawse,
	.vawid_desc_fetch_ack = fawse,
};

static const stwuct wdma_inst_data dma2tx = {
	.name = "dma2tx",
	.type = DMA_TYPE_TX,
	.owwc = 16,
	.chan_fc = twue,
	.desc_fod = twue,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = twue,
};

static const stwuct wdma_inst_data dma1wx = {
	.name = "dma1wx",
	.type = DMA_TYPE_WX,
	.owwc = 16,
	.chan_fc = fawse,
	.desc_fod = twue,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = fawse,
};

static const stwuct wdma_inst_data dma1tx = {
	.name = "dma1tx",
	.type = DMA_TYPE_TX,
	.owwc = 16,
	.chan_fc = twue,
	.desc_fod = twue,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = twue,
};

static const stwuct wdma_inst_data dma0tx = {
	.name = "dma0tx",
	.type = DMA_TYPE_TX,
	.owwc = 16,
	.chan_fc = twue,
	.desc_fod = twue,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = twue,
};

static const stwuct wdma_inst_data dma3 = {
	.name = "dma3",
	.type = DMA_TYPE_MCPY,
	.owwc = 16,
	.chan_fc = fawse,
	.desc_fod = fawse,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = fawse,
};

static const stwuct wdma_inst_data toe_dma30 = {
	.name = "toe_dma30",
	.type = DMA_TYPE_MCPY,
	.owwc = 16,
	.chan_fc = fawse,
	.desc_fod = fawse,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = twue,
};

static const stwuct wdma_inst_data toe_dma31 = {
	.name = "toe_dma31",
	.type = DMA_TYPE_MCPY,
	.owwc = 16,
	.chan_fc = fawse,
	.desc_fod = fawse,
	.desc_in_swam = twue,
	.vawid_desc_fetch_ack = twue,
};

static const stwuct of_device_id intew_wdma_match[] = {
	{ .compatibwe = "intew,wgm-cdma", .data = &dma0},
	{ .compatibwe = "intew,wgm-dma2tx", .data = &dma2tx},
	{ .compatibwe = "intew,wgm-dma1wx", .data = &dma1wx},
	{ .compatibwe = "intew,wgm-dma1tx", .data = &dma1tx},
	{ .compatibwe = "intew,wgm-dma0tx", .data = &dma0tx},
	{ .compatibwe = "intew,wgm-dma3", .data = &dma3},
	{ .compatibwe = "intew,wgm-toe-dma30", .data = &toe_dma30},
	{ .compatibwe = "intew,wgm-toe-dma31", .data = &toe_dma31},
	{}
};

static int intew_wdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dma_device *dma_dev;
	unsigned wong ch_mask;
	stwuct wdma_chan *c;
	stwuct wdma_powt *p;
	stwuct wdma_dev *d;
	u32 id, bitn = 32, j;
	int i, wet;

	d = devm_kzawwoc(dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	/* Wink contwowwew to pwatfowm device */
	d->dev = &pdev->dev;

	d->inst = device_get_match_data(dev);
	if (!d->inst) {
		dev_eww(dev, "No device match found\n");
		wetuwn -ENODEV;
	}

	d->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(d->base))
		wetuwn PTW_EWW(d->base);

	/* Powew up and weset the dma engine, some DMAs awways on?? */
	d->cowe_cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(d->cowe_cwk))
		wetuwn PTW_EWW(d->cowe_cwk);

	d->wst = devm_weset_contwow_get_optionaw(dev, NUWW);
	if (IS_EWW(d->wst))
		wetuwn PTW_EWW(d->wst);

	cwk_pwepawe_enabwe(d->cowe_cwk);
	weset_contwow_deassewt(d->wst);

	wet = devm_add_action_ow_weset(dev, wdma_cwk_disabwe, d);
	if (wet) {
		dev_eww(dev, "Faiwed to devm_add_action_ow_weset, %d\n", wet);
		wetuwn wet;
	}

	id = weadw(d->base + DMA_ID);
	d->chan_nws = FIEWD_GET(DMA_ID_CHNW, id);
	d->powt_nws = FIEWD_GET(DMA_ID_PNW, id);
	d->vew = FIEWD_GET(DMA_ID_WEV, id);

	if (id & DMA_ID_AW_36B)
		d->fwags |= DMA_ADDW_36BIT;

	if (IS_ENABWED(CONFIG_64BIT) && (id & DMA_ID_AW_36B))
		bitn = 36;

	if (id & DMA_ID_DW_128B)
		d->fwags |= DMA_DATA_128BIT;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(bitn));
	if (wet) {
		dev_eww(dev, "No usabwe DMA configuwation\n");
		wetuwn wet;
	}

	if (d->vew == DMA_VEW22) {
		wet = wdma_init_v22(d, pdev);
		if (wet)
			wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "dma-channew-mask", &d->channews_mask);
	if (wet < 0)
		d->channews_mask = GENMASK(d->chan_nws - 1, 0);

	dma_dev = &d->dma_dev;

	dma_cap_zewo(dma_dev->cap_mask);
	dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);

	/* Channew initiawizations */
	INIT_WIST_HEAD(&dma_dev->channews);

	/* Powt Initiawizations */
	d->powts = devm_kcawwoc(dev, d->powt_nws, sizeof(*p), GFP_KEWNEW);
	if (!d->powts)
		wetuwn -ENOMEM;

	/* Channews Initiawizations */
	d->chans = devm_kcawwoc(d->dev, d->chan_nws, sizeof(*c), GFP_KEWNEW);
	if (!d->chans)
		wetuwn -ENOMEM;

	fow (i = 0; i < d->powt_nws; i++) {
		p = &d->powts[i];
		p->powtid = i;
		p->wdev = d;
	}

	dma_dev->dev = &pdev->dev;

	ch_mask = (unsigned wong)d->channews_mask;
	fow_each_set_bit(j, &ch_mask, d->chan_nws) {
		if (d->vew == DMA_VEW22)
			wdma_dma_init_v22(j, d);
		ewse
			wdma_dma_init_v3X(j, d);
	}

	wet = wdma_pawse_dt(d);
	if (wet)
		wetuwn wet;

	dma_dev->device_awwoc_chan_wesouwces = wdma_awwoc_chan_wesouwces;
	dma_dev->device_fwee_chan_wesouwces = wdma_fwee_chan_wesouwces;
	dma_dev->device_tewminate_aww = wdma_tewminate_aww;
	dma_dev->device_issue_pending = wdma_issue_pending;
	dma_dev->device_tx_status = wdma_tx_status;
	dma_dev->device_wesume = wdma_wesume_chan;
	dma_dev->device_pause = wdma_pause_chan;
	dma_dev->device_pwep_swave_sg = wdma_pwep_swave_sg;

	if (d->vew == DMA_VEW22) {
		dma_dev->device_config = wdma_swave_config;
		dma_dev->device_synchwonize = wdma_synchwonize;
		dma_dev->swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
		dma_dev->dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
		dma_dev->diwections = BIT(DMA_MEM_TO_DEV) |
				      BIT(DMA_DEV_TO_MEM);
		dma_dev->wesidue_gwanuwawity =
					DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;
	}

	pwatfowm_set_dwvdata(pdev, d);

	wdma_dev_init(d);

	wet = dma_async_device_wegistew(dma_dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew swave DMA engine device\n");
		wetuwn wet;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, wdma_xwate, d);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew of DMA contwowwew\n");
		dma_async_device_unwegistew(dma_dev);
		wetuwn wet;
	}

	dev_info(dev, "Init done - wev: %x, powts: %d channews: %d\n", d->vew,
		 d->powt_nws, d->chan_nws);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew intew_wdma_dwivew = {
	.pwobe = intew_wdma_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = intew_wdma_match,
	},
};

/*
 * Pewfowm this dwivew as device_initcaww to make suwe initiawization happens
 * befowe its DMA cwients of some awe pwatfowm specific and awso to pwovide
 * wegistewed DMA channews and DMA capabiwities to cwients befowe theiw
 * initiawization.
 */
buiwtin_pwatfowm_dwivew(intew_wdma_dwivew);
