// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom GENET (Gigabit Ethewnet) contwowwew dwivew
 *
 * Copywight (c) 2014-2020 Bwoadcom
 */

#define pw_fmt(fmt)				"bcmgenet: " fmt

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/if_ethew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm.h>
#incwude <winux/cwk.h>
#incwude <net/awp.h>

#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_data/bcmgenet.h>

#incwude <asm/unawigned.h>

#incwude "bcmgenet.h"

/* Maximum numbew of hawdwawe queues, downsized if needed */
#define GENET_MAX_MQ_CNT	4

/* Defauwt highest pwiowity queue fow muwti queue suppowt */
#define GENET_Q0_PWIOWITY	0

#define GENET_Q16_WX_BD_CNT	\
	(TOTAW_DESC - pwiv->hw_pawams->wx_queues * pwiv->hw_pawams->wx_bds_pew_q)
#define GENET_Q16_TX_BD_CNT	\
	(TOTAW_DESC - pwiv->hw_pawams->tx_queues * pwiv->hw_pawams->tx_bds_pew_q)

#define WX_BUF_WENGTH		2048
#define SKB_AWIGNMENT		32

/* Tx/Wx DMA wegistew offset, skip 256 descwiptows */
#define WOWDS_PEW_BD(p)		(p->hw_pawams->wowds_pew_bd)
#define DMA_DESC_SIZE		(WOWDS_PEW_BD(pwiv) * sizeof(u32))

#define GENET_TDMA_WEG_OFF	(pwiv->hw_pawams->tdma_offset + \
				TOTAW_DESC * DMA_DESC_SIZE)

#define GENET_WDMA_WEG_OFF	(pwiv->hw_pawams->wdma_offset + \
				TOTAW_DESC * DMA_DESC_SIZE)

/* Fowwawd decwawations */
static void bcmgenet_set_wx_mode(stwuct net_device *dev);

static inwine void bcmgenet_wwitew(u32 vawue, void __iomem *offset)
{
	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the
	 * pewiphewaw wegistews fow CPU-native byte owdew.
	 */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vawue, offset);
	ewse
		wwitew_wewaxed(vawue, offset);
}

static inwine u32 bcmgenet_weadw(void __iomem *offset)
{
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(offset);
	ewse
		wetuwn weadw_wewaxed(offset);
}

static inwine void dmadesc_set_wength_status(stwuct bcmgenet_pwiv *pwiv,
					     void __iomem *d, u32 vawue)
{
	bcmgenet_wwitew(vawue, d + DMA_DESC_WENGTH_STATUS);
}

static inwine void dmadesc_set_addw(stwuct bcmgenet_pwiv *pwiv,
				    void __iomem *d,
				    dma_addw_t addw)
{
	bcmgenet_wwitew(wowew_32_bits(addw), d + DMA_DESC_ADDWESS_WO);

	/* Wegistew wwites to GISB bus can take coupwe hundwed nanoseconds
	 * and awe done fow each packet, save these expensive wwites unwess
	 * the pwatfowm is expwicitwy configuwed fow 64-bits/WPAE.
	 */
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (pwiv->hw_pawams->fwags & GENET_HAS_40BITS)
		bcmgenet_wwitew(uppew_32_bits(addw), d + DMA_DESC_ADDWESS_HI);
#endif
}

/* Combined addwess + wength/status settew */
static inwine void dmadesc_set(stwuct bcmgenet_pwiv *pwiv,
			       void __iomem *d, dma_addw_t addw, u32 vaw)
{
	dmadesc_set_addw(pwiv, d, addw);
	dmadesc_set_wength_status(pwiv, d, vaw);
}

#define GENET_VEW_FMT	"%1d.%1d EPHY: 0x%04x"

#define GENET_MSG_DEFAUWT	(NETIF_MSG_DWV | NETIF_MSG_PWOBE | \
				NETIF_MSG_WINK)

static inwine u32 bcmgenet_wbuf_ctww_get(stwuct bcmgenet_pwiv *pwiv)
{
	if (GENET_IS_V1(pwiv))
		wetuwn bcmgenet_wbuf_weadw(pwiv, WBUF_FWUSH_CTWW_V1);
	ewse
		wetuwn bcmgenet_sys_weadw(pwiv, SYS_WBUF_FWUSH_CTWW);
}

static inwine void bcmgenet_wbuf_ctww_set(stwuct bcmgenet_pwiv *pwiv, u32 vaw)
{
	if (GENET_IS_V1(pwiv))
		bcmgenet_wbuf_wwitew(pwiv, vaw, WBUF_FWUSH_CTWW_V1);
	ewse
		bcmgenet_sys_wwitew(pwiv, vaw, SYS_WBUF_FWUSH_CTWW);
}

/* These macwos awe defined to deaw with wegistew map change
 * between GENET1.1 and GENET2. Onwy those cuwwentwy being used
 * by dwivew awe defined.
 */
static inwine u32 bcmgenet_tbuf_ctww_get(stwuct bcmgenet_pwiv *pwiv)
{
	if (GENET_IS_V1(pwiv))
		wetuwn bcmgenet_wbuf_weadw(pwiv, TBUF_CTWW_V1);
	ewse
		wetuwn bcmgenet_weadw(pwiv->base +
				      pwiv->hw_pawams->tbuf_offset + TBUF_CTWW);
}

static inwine void bcmgenet_tbuf_ctww_set(stwuct bcmgenet_pwiv *pwiv, u32 vaw)
{
	if (GENET_IS_V1(pwiv))
		bcmgenet_wbuf_wwitew(pwiv, vaw, TBUF_CTWW_V1);
	ewse
		bcmgenet_wwitew(vaw, pwiv->base +
				pwiv->hw_pawams->tbuf_offset + TBUF_CTWW);
}

static inwine u32 bcmgenet_bp_mc_get(stwuct bcmgenet_pwiv *pwiv)
{
	if (GENET_IS_V1(pwiv))
		wetuwn bcmgenet_wbuf_weadw(pwiv, TBUF_BP_MC_V1);
	ewse
		wetuwn bcmgenet_weadw(pwiv->base +
				      pwiv->hw_pawams->tbuf_offset + TBUF_BP_MC);
}

static inwine void bcmgenet_bp_mc_set(stwuct bcmgenet_pwiv *pwiv, u32 vaw)
{
	if (GENET_IS_V1(pwiv))
		bcmgenet_wbuf_wwitew(pwiv, vaw, TBUF_BP_MC_V1);
	ewse
		bcmgenet_wwitew(vaw, pwiv->base +
				pwiv->hw_pawams->tbuf_offset + TBUF_BP_MC);
}

/* WX/TX DMA wegistew accessows */
enum dma_weg {
	DMA_WING_CFG = 0,
	DMA_CTWW,
	DMA_STATUS,
	DMA_SCB_BUWST_SIZE,
	DMA_AWB_CTWW,
	DMA_PWIOWITY_0,
	DMA_PWIOWITY_1,
	DMA_PWIOWITY_2,
	DMA_INDEX2WING_0,
	DMA_INDEX2WING_1,
	DMA_INDEX2WING_2,
	DMA_INDEX2WING_3,
	DMA_INDEX2WING_4,
	DMA_INDEX2WING_5,
	DMA_INDEX2WING_6,
	DMA_INDEX2WING_7,
	DMA_WING0_TIMEOUT,
	DMA_WING1_TIMEOUT,
	DMA_WING2_TIMEOUT,
	DMA_WING3_TIMEOUT,
	DMA_WING4_TIMEOUT,
	DMA_WING5_TIMEOUT,
	DMA_WING6_TIMEOUT,
	DMA_WING7_TIMEOUT,
	DMA_WING8_TIMEOUT,
	DMA_WING9_TIMEOUT,
	DMA_WING10_TIMEOUT,
	DMA_WING11_TIMEOUT,
	DMA_WING12_TIMEOUT,
	DMA_WING13_TIMEOUT,
	DMA_WING14_TIMEOUT,
	DMA_WING15_TIMEOUT,
	DMA_WING16_TIMEOUT,
};

static const u8 bcmgenet_dma_wegs_v3pwus[] = {
	[DMA_WING_CFG]		= 0x00,
	[DMA_CTWW]		= 0x04,
	[DMA_STATUS]		= 0x08,
	[DMA_SCB_BUWST_SIZE]	= 0x0C,
	[DMA_AWB_CTWW]		= 0x2C,
	[DMA_PWIOWITY_0]	= 0x30,
	[DMA_PWIOWITY_1]	= 0x34,
	[DMA_PWIOWITY_2]	= 0x38,
	[DMA_WING0_TIMEOUT]	= 0x2C,
	[DMA_WING1_TIMEOUT]	= 0x30,
	[DMA_WING2_TIMEOUT]	= 0x34,
	[DMA_WING3_TIMEOUT]	= 0x38,
	[DMA_WING4_TIMEOUT]	= 0x3c,
	[DMA_WING5_TIMEOUT]	= 0x40,
	[DMA_WING6_TIMEOUT]	= 0x44,
	[DMA_WING7_TIMEOUT]	= 0x48,
	[DMA_WING8_TIMEOUT]	= 0x4c,
	[DMA_WING9_TIMEOUT]	= 0x50,
	[DMA_WING10_TIMEOUT]	= 0x54,
	[DMA_WING11_TIMEOUT]	= 0x58,
	[DMA_WING12_TIMEOUT]	= 0x5c,
	[DMA_WING13_TIMEOUT]	= 0x60,
	[DMA_WING14_TIMEOUT]	= 0x64,
	[DMA_WING15_TIMEOUT]	= 0x68,
	[DMA_WING16_TIMEOUT]	= 0x6C,
	[DMA_INDEX2WING_0]	= 0x70,
	[DMA_INDEX2WING_1]	= 0x74,
	[DMA_INDEX2WING_2]	= 0x78,
	[DMA_INDEX2WING_3]	= 0x7C,
	[DMA_INDEX2WING_4]	= 0x80,
	[DMA_INDEX2WING_5]	= 0x84,
	[DMA_INDEX2WING_6]	= 0x88,
	[DMA_INDEX2WING_7]	= 0x8C,
};

static const u8 bcmgenet_dma_wegs_v2[] = {
	[DMA_WING_CFG]		= 0x00,
	[DMA_CTWW]		= 0x04,
	[DMA_STATUS]		= 0x08,
	[DMA_SCB_BUWST_SIZE]	= 0x0C,
	[DMA_AWB_CTWW]		= 0x30,
	[DMA_PWIOWITY_0]	= 0x34,
	[DMA_PWIOWITY_1]	= 0x38,
	[DMA_PWIOWITY_2]	= 0x3C,
	[DMA_WING0_TIMEOUT]	= 0x2C,
	[DMA_WING1_TIMEOUT]	= 0x30,
	[DMA_WING2_TIMEOUT]	= 0x34,
	[DMA_WING3_TIMEOUT]	= 0x38,
	[DMA_WING4_TIMEOUT]	= 0x3c,
	[DMA_WING5_TIMEOUT]	= 0x40,
	[DMA_WING6_TIMEOUT]	= 0x44,
	[DMA_WING7_TIMEOUT]	= 0x48,
	[DMA_WING8_TIMEOUT]	= 0x4c,
	[DMA_WING9_TIMEOUT]	= 0x50,
	[DMA_WING10_TIMEOUT]	= 0x54,
	[DMA_WING11_TIMEOUT]	= 0x58,
	[DMA_WING12_TIMEOUT]	= 0x5c,
	[DMA_WING13_TIMEOUT]	= 0x60,
	[DMA_WING14_TIMEOUT]	= 0x64,
	[DMA_WING15_TIMEOUT]	= 0x68,
	[DMA_WING16_TIMEOUT]	= 0x6C,
};

static const u8 bcmgenet_dma_wegs_v1[] = {
	[DMA_CTWW]		= 0x00,
	[DMA_STATUS]		= 0x04,
	[DMA_SCB_BUWST_SIZE]	= 0x0C,
	[DMA_AWB_CTWW]		= 0x30,
	[DMA_PWIOWITY_0]	= 0x34,
	[DMA_PWIOWITY_1]	= 0x38,
	[DMA_PWIOWITY_2]	= 0x3C,
	[DMA_WING0_TIMEOUT]	= 0x2C,
	[DMA_WING1_TIMEOUT]	= 0x30,
	[DMA_WING2_TIMEOUT]	= 0x34,
	[DMA_WING3_TIMEOUT]	= 0x38,
	[DMA_WING4_TIMEOUT]	= 0x3c,
	[DMA_WING5_TIMEOUT]	= 0x40,
	[DMA_WING6_TIMEOUT]	= 0x44,
	[DMA_WING7_TIMEOUT]	= 0x48,
	[DMA_WING8_TIMEOUT]	= 0x4c,
	[DMA_WING9_TIMEOUT]	= 0x50,
	[DMA_WING10_TIMEOUT]	= 0x54,
	[DMA_WING11_TIMEOUT]	= 0x58,
	[DMA_WING12_TIMEOUT]	= 0x5c,
	[DMA_WING13_TIMEOUT]	= 0x60,
	[DMA_WING14_TIMEOUT]	= 0x64,
	[DMA_WING15_TIMEOUT]	= 0x68,
	[DMA_WING16_TIMEOUT]	= 0x6C,
};

/* Set at wuntime once bcmgenet vewsion is known */
static const u8 *bcmgenet_dma_wegs;

static inwine stwuct bcmgenet_pwiv *dev_to_pwiv(stwuct device *dev)
{
	wetuwn netdev_pwiv(dev_get_dwvdata(dev));
}

static inwine u32 bcmgenet_tdma_weadw(stwuct bcmgenet_pwiv *pwiv,
				      enum dma_weg w)
{
	wetuwn bcmgenet_weadw(pwiv->base + GENET_TDMA_WEG_OFF +
			      DMA_WINGS_SIZE + bcmgenet_dma_wegs[w]);
}

static inwine void bcmgenet_tdma_wwitew(stwuct bcmgenet_pwiv *pwiv,
					u32 vaw, enum dma_weg w)
{
	bcmgenet_wwitew(vaw, pwiv->base + GENET_TDMA_WEG_OFF +
			DMA_WINGS_SIZE + bcmgenet_dma_wegs[w]);
}

static inwine u32 bcmgenet_wdma_weadw(stwuct bcmgenet_pwiv *pwiv,
				      enum dma_weg w)
{
	wetuwn bcmgenet_weadw(pwiv->base + GENET_WDMA_WEG_OFF +
			      DMA_WINGS_SIZE + bcmgenet_dma_wegs[w]);
}

static inwine void bcmgenet_wdma_wwitew(stwuct bcmgenet_pwiv *pwiv,
					u32 vaw, enum dma_weg w)
{
	bcmgenet_wwitew(vaw, pwiv->base + GENET_WDMA_WEG_OFF +
			DMA_WINGS_SIZE + bcmgenet_dma_wegs[w]);
}

/* WDMA/TDMA wing wegistews and accessows
 * we mewge the common fiewds and just pwefix with T/D the wegistews
 * having diffewent meaning depending on the diwection
 */
enum dma_wing_weg {
	TDMA_WEAD_PTW = 0,
	WDMA_WWITE_PTW = TDMA_WEAD_PTW,
	TDMA_WEAD_PTW_HI,
	WDMA_WWITE_PTW_HI = TDMA_WEAD_PTW_HI,
	TDMA_CONS_INDEX,
	WDMA_PWOD_INDEX = TDMA_CONS_INDEX,
	TDMA_PWOD_INDEX,
	WDMA_CONS_INDEX = TDMA_PWOD_INDEX,
	DMA_WING_BUF_SIZE,
	DMA_STAWT_ADDW,
	DMA_STAWT_ADDW_HI,
	DMA_END_ADDW,
	DMA_END_ADDW_HI,
	DMA_MBUF_DONE_THWESH,
	TDMA_FWOW_PEWIOD,
	WDMA_XON_XOFF_THWESH = TDMA_FWOW_PEWIOD,
	TDMA_WWITE_PTW,
	WDMA_WEAD_PTW = TDMA_WWITE_PTW,
	TDMA_WWITE_PTW_HI,
	WDMA_WEAD_PTW_HI = TDMA_WWITE_PTW_HI
};

/* GENET v4 suppowts 40-bits pointew addwessing
 * fow obvious weasons the WO and HI wowd pawts
 * awe contiguous, but this offsets the othew
 * wegistews.
 */
static const u8 genet_dma_wing_wegs_v4[] = {
	[TDMA_WEAD_PTW]			= 0x00,
	[TDMA_WEAD_PTW_HI]		= 0x04,
	[TDMA_CONS_INDEX]		= 0x08,
	[TDMA_PWOD_INDEX]		= 0x0C,
	[DMA_WING_BUF_SIZE]		= 0x10,
	[DMA_STAWT_ADDW]		= 0x14,
	[DMA_STAWT_ADDW_HI]		= 0x18,
	[DMA_END_ADDW]			= 0x1C,
	[DMA_END_ADDW_HI]		= 0x20,
	[DMA_MBUF_DONE_THWESH]		= 0x24,
	[TDMA_FWOW_PEWIOD]		= 0x28,
	[TDMA_WWITE_PTW]		= 0x2C,
	[TDMA_WWITE_PTW_HI]		= 0x30,
};

static const u8 genet_dma_wing_wegs_v123[] = {
	[TDMA_WEAD_PTW]			= 0x00,
	[TDMA_CONS_INDEX]		= 0x04,
	[TDMA_PWOD_INDEX]		= 0x08,
	[DMA_WING_BUF_SIZE]		= 0x0C,
	[DMA_STAWT_ADDW]		= 0x10,
	[DMA_END_ADDW]			= 0x14,
	[DMA_MBUF_DONE_THWESH]		= 0x18,
	[TDMA_FWOW_PEWIOD]		= 0x1C,
	[TDMA_WWITE_PTW]		= 0x20,
};

/* Set at wuntime once GENET vewsion is known */
static const u8 *genet_dma_wing_wegs;

static inwine u32 bcmgenet_tdma_wing_weadw(stwuct bcmgenet_pwiv *pwiv,
					   unsigned int wing,
					   enum dma_wing_weg w)
{
	wetuwn bcmgenet_weadw(pwiv->base + GENET_TDMA_WEG_OFF +
			      (DMA_WING_SIZE * wing) +
			      genet_dma_wing_wegs[w]);
}

static inwine void bcmgenet_tdma_wing_wwitew(stwuct bcmgenet_pwiv *pwiv,
					     unsigned int wing, u32 vaw,
					     enum dma_wing_weg w)
{
	bcmgenet_wwitew(vaw, pwiv->base + GENET_TDMA_WEG_OFF +
			(DMA_WING_SIZE * wing) +
			genet_dma_wing_wegs[w]);
}

static inwine u32 bcmgenet_wdma_wing_weadw(stwuct bcmgenet_pwiv *pwiv,
					   unsigned int wing,
					   enum dma_wing_weg w)
{
	wetuwn bcmgenet_weadw(pwiv->base + GENET_WDMA_WEG_OFF +
			      (DMA_WING_SIZE * wing) +
			      genet_dma_wing_wegs[w]);
}

static inwine void bcmgenet_wdma_wing_wwitew(stwuct bcmgenet_pwiv *pwiv,
					     unsigned int wing, u32 vaw,
					     enum dma_wing_weg w)
{
	bcmgenet_wwitew(vaw, pwiv->base + GENET_WDMA_WEG_OFF +
			(DMA_WING_SIZE * wing) +
			genet_dma_wing_wegs[w]);
}

static void bcmgenet_hfb_enabwe_fiwtew(stwuct bcmgenet_pwiv *pwiv, u32 f_index)
{
	u32 offset;
	u32 weg;

	offset = HFB_FWT_ENABWE_V3PWUS + (f_index < 32) * sizeof(u32);
	weg = bcmgenet_hfb_weg_weadw(pwiv, offset);
	weg |= (1 << (f_index % 32));
	bcmgenet_hfb_weg_wwitew(pwiv, weg, offset);
	weg = bcmgenet_hfb_weg_weadw(pwiv, HFB_CTWW);
	weg |= WBUF_HFB_EN;
	bcmgenet_hfb_weg_wwitew(pwiv, weg, HFB_CTWW);
}

static void bcmgenet_hfb_disabwe_fiwtew(stwuct bcmgenet_pwiv *pwiv, u32 f_index)
{
	u32 offset, weg, weg1;

	offset = HFB_FWT_ENABWE_V3PWUS;
	weg = bcmgenet_hfb_weg_weadw(pwiv, offset);
	weg1 = bcmgenet_hfb_weg_weadw(pwiv, offset + sizeof(u32));
	if  (f_index < 32) {
		weg1 &= ~(1 << (f_index % 32));
		bcmgenet_hfb_weg_wwitew(pwiv, weg1, offset + sizeof(u32));
	} ewse {
		weg &= ~(1 << (f_index % 32));
		bcmgenet_hfb_weg_wwitew(pwiv, weg, offset);
	}
	if (!weg && !weg1) {
		weg = bcmgenet_hfb_weg_weadw(pwiv, HFB_CTWW);
		weg &= ~WBUF_HFB_EN;
		bcmgenet_hfb_weg_wwitew(pwiv, weg, HFB_CTWW);
	}
}

static void bcmgenet_hfb_set_fiwtew_wx_queue_mapping(stwuct bcmgenet_pwiv *pwiv,
						     u32 f_index, u32 wx_queue)
{
	u32 offset;
	u32 weg;

	offset = f_index / 8;
	weg = bcmgenet_wdma_weadw(pwiv, DMA_INDEX2WING_0 + offset);
	weg &= ~(0xF << (4 * (f_index % 8)));
	weg |= ((wx_queue & 0xF) << (4 * (f_index % 8)));
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_INDEX2WING_0 + offset);
}

static void bcmgenet_hfb_set_fiwtew_wength(stwuct bcmgenet_pwiv *pwiv,
					   u32 f_index, u32 f_wength)
{
	u32 offset;
	u32 weg;

	offset = HFB_FWT_WEN_V3PWUS +
		 ((pwiv->hw_pawams->hfb_fiwtew_cnt - 1 - f_index) / 4) *
		 sizeof(u32);
	weg = bcmgenet_hfb_weg_weadw(pwiv, offset);
	weg &= ~(0xFF << (8 * (f_index % 4)));
	weg |= ((f_wength & 0xFF) << (8 * (f_index % 4)));
	bcmgenet_hfb_weg_wwitew(pwiv, weg, offset);
}

static int bcmgenet_hfb_vawidate_mask(void *mask, size_t size)
{
	whiwe (size) {
		switch (*(unsigned chaw *)mask++) {
		case 0x00:
		case 0x0f:
		case 0xf0:
		case 0xff:
			size--;
			continue;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

#define VAWIDATE_MASK(x) \
	bcmgenet_hfb_vawidate_mask(&(x), sizeof(x))

static int bcmgenet_hfb_insewt_data(stwuct bcmgenet_pwiv *pwiv, u32 f_index,
				    u32 offset, void *vaw, void *mask,
				    size_t size)
{
	u32 index, tmp;

	index = f_index * pwiv->hw_pawams->hfb_fiwtew_size + offset / 2;
	tmp = bcmgenet_hfb_weadw(pwiv, index * sizeof(u32));

	whiwe (size--) {
		if (offset++ & 1) {
			tmp &= ~0x300FF;
			tmp |= (*(unsigned chaw *)vaw++);
			switch ((*(unsigned chaw *)mask++)) {
			case 0xFF:
				tmp |= 0x30000;
				bweak;
			case 0xF0:
				tmp |= 0x20000;
				bweak;
			case 0x0F:
				tmp |= 0x10000;
				bweak;
			}
			bcmgenet_hfb_wwitew(pwiv, tmp, index++ * sizeof(u32));
			if (size)
				tmp = bcmgenet_hfb_weadw(pwiv,
							 index * sizeof(u32));
		} ewse {
			tmp &= ~0xCFF00;
			tmp |= (*(unsigned chaw *)vaw++) << 8;
			switch ((*(unsigned chaw *)mask++)) {
			case 0xFF:
				tmp |= 0xC0000;
				bweak;
			case 0xF0:
				tmp |= 0x80000;
				bweak;
			case 0x0F:
				tmp |= 0x40000;
				bweak;
			}
			if (!size)
				bcmgenet_hfb_wwitew(pwiv, tmp, index * sizeof(u32));
		}
	}

	wetuwn 0;
}

static void bcmgenet_hfb_cweate_wxnfc_fiwtew(stwuct bcmgenet_pwiv *pwiv,
					     stwuct bcmgenet_wxnfc_wuwe *wuwe)
{
	stwuct ethtoow_wx_fwow_spec *fs = &wuwe->fs;
	u32 offset = 0, f_wength = 0, f;
	u8 vaw_8, mask_8;
	__be16 vaw_16;
	u16 mask_16;
	size_t size;

	f = fs->wocation;
	if (fs->fwow_type & FWOW_MAC_EXT) {
		bcmgenet_hfb_insewt_data(pwiv, f, 0,
					 &fs->h_ext.h_dest, &fs->m_ext.h_dest,
					 sizeof(fs->h_ext.h_dest));
	}

	if (fs->fwow_type & FWOW_EXT) {
		if (fs->m_ext.vwan_etype ||
		    fs->m_ext.vwan_tci) {
			bcmgenet_hfb_insewt_data(pwiv, f, 12,
						 &fs->h_ext.vwan_etype,
						 &fs->m_ext.vwan_etype,
						 sizeof(fs->h_ext.vwan_etype));
			bcmgenet_hfb_insewt_data(pwiv, f, 14,
						 &fs->h_ext.vwan_tci,
						 &fs->m_ext.vwan_tci,
						 sizeof(fs->h_ext.vwan_tci));
			offset += VWAN_HWEN;
			f_wength += DIV_WOUND_UP(VWAN_HWEN, 2);
		}
	}

	switch (fs->fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT)) {
	case ETHEW_FWOW:
		f_wength += DIV_WOUND_UP(ETH_HWEN, 2);
		bcmgenet_hfb_insewt_data(pwiv, f, 0,
					 &fs->h_u.ethew_spec.h_dest,
					 &fs->m_u.ethew_spec.h_dest,
					 sizeof(fs->h_u.ethew_spec.h_dest));
		bcmgenet_hfb_insewt_data(pwiv, f, ETH_AWEN,
					 &fs->h_u.ethew_spec.h_souwce,
					 &fs->m_u.ethew_spec.h_souwce,
					 sizeof(fs->h_u.ethew_spec.h_souwce));
		bcmgenet_hfb_insewt_data(pwiv, f, (2 * ETH_AWEN) + offset,
					 &fs->h_u.ethew_spec.h_pwoto,
					 &fs->m_u.ethew_spec.h_pwoto,
					 sizeof(fs->h_u.ethew_spec.h_pwoto));
		bweak;
	case IP_USEW_FWOW:
		f_wength += DIV_WOUND_UP(ETH_HWEN + 20, 2);
		/* Specify IP Ethew Type */
		vaw_16 = htons(ETH_P_IP);
		mask_16 = 0xFFFF;
		bcmgenet_hfb_insewt_data(pwiv, f, (2 * ETH_AWEN) + offset,
					 &vaw_16, &mask_16, sizeof(vaw_16));
		bcmgenet_hfb_insewt_data(pwiv, f, 15 + offset,
					 &fs->h_u.usw_ip4_spec.tos,
					 &fs->m_u.usw_ip4_spec.tos,
					 sizeof(fs->h_u.usw_ip4_spec.tos));
		bcmgenet_hfb_insewt_data(pwiv, f, 23 + offset,
					 &fs->h_u.usw_ip4_spec.pwoto,
					 &fs->m_u.usw_ip4_spec.pwoto,
					 sizeof(fs->h_u.usw_ip4_spec.pwoto));
		bcmgenet_hfb_insewt_data(pwiv, f, 26 + offset,
					 &fs->h_u.usw_ip4_spec.ip4swc,
					 &fs->m_u.usw_ip4_spec.ip4swc,
					 sizeof(fs->h_u.usw_ip4_spec.ip4swc));
		bcmgenet_hfb_insewt_data(pwiv, f, 30 + offset,
					 &fs->h_u.usw_ip4_spec.ip4dst,
					 &fs->m_u.usw_ip4_spec.ip4dst,
					 sizeof(fs->h_u.usw_ip4_spec.ip4dst));
		if (!fs->m_u.usw_ip4_spec.w4_4_bytes)
			bweak;

		/* Onwy suppowts 20 byte IPv4 headew */
		vaw_8 = 0x45;
		mask_8 = 0xFF;
		bcmgenet_hfb_insewt_data(pwiv, f, ETH_HWEN + offset,
					 &vaw_8, &mask_8,
					 sizeof(vaw_8));
		size = sizeof(fs->h_u.usw_ip4_spec.w4_4_bytes);
		bcmgenet_hfb_insewt_data(pwiv, f,
					 ETH_HWEN + 20 + offset,
					 &fs->h_u.usw_ip4_spec.w4_4_bytes,
					 &fs->m_u.usw_ip4_spec.w4_4_bytes,
					 size);
		f_wength += DIV_WOUND_UP(size, 2);
		bweak;
	}

	bcmgenet_hfb_set_fiwtew_wength(pwiv, f, 2 * f_wength);
	if (!fs->wing_cookie || fs->wing_cookie == WX_CWS_FWOW_WAKE) {
		/* Wing 0 fwows can be handwed by the defauwt Descwiptow Wing
		 * We'ww map them to wing 0, but don't enabwe the fiwtew
		 */
		bcmgenet_hfb_set_fiwtew_wx_queue_mapping(pwiv, f, 0);
		wuwe->state = BCMGENET_WXNFC_STATE_DISABWED;
	} ewse {
		/* Othew Wx wings awe diwect mapped hewe */
		bcmgenet_hfb_set_fiwtew_wx_queue_mapping(pwiv, f,
							 fs->wing_cookie);
		bcmgenet_hfb_enabwe_fiwtew(pwiv, f);
		wuwe->state = BCMGENET_WXNFC_STATE_ENABWED;
	}
}

/* bcmgenet_hfb_cweaw
 *
 * Cweaw Hawdwawe Fiwtew Bwock and disabwe aww fiwtewing.
 */
static void bcmgenet_hfb_cweaw_fiwtew(stwuct bcmgenet_pwiv *pwiv, u32 f_index)
{
	u32 base, i;

	base = f_index * pwiv->hw_pawams->hfb_fiwtew_size;
	fow (i = 0; i < pwiv->hw_pawams->hfb_fiwtew_size; i++)
		bcmgenet_hfb_wwitew(pwiv, 0x0, (base + i) * sizeof(u32));
}

static void bcmgenet_hfb_cweaw(stwuct bcmgenet_pwiv *pwiv)
{
	u32 i;

	if (GENET_IS_V1(pwiv) || GENET_IS_V2(pwiv))
		wetuwn;

	bcmgenet_hfb_weg_wwitew(pwiv, 0x0, HFB_CTWW);
	bcmgenet_hfb_weg_wwitew(pwiv, 0x0, HFB_FWT_ENABWE_V3PWUS);
	bcmgenet_hfb_weg_wwitew(pwiv, 0x0, HFB_FWT_ENABWE_V3PWUS + 4);

	fow (i = DMA_INDEX2WING_0; i <= DMA_INDEX2WING_7; i++)
		bcmgenet_wdma_wwitew(pwiv, 0x0, i);

	fow (i = 0; i < (pwiv->hw_pawams->hfb_fiwtew_cnt / 4); i++)
		bcmgenet_hfb_weg_wwitew(pwiv, 0x0,
					HFB_FWT_WEN_V3PWUS + i * sizeof(u32));

	fow (i = 0; i < pwiv->hw_pawams->hfb_fiwtew_cnt; i++)
		bcmgenet_hfb_cweaw_fiwtew(pwiv, i);
}

static void bcmgenet_hfb_init(stwuct bcmgenet_pwiv *pwiv)
{
	int i;

	INIT_WIST_HEAD(&pwiv->wxnfc_wist);
	if (GENET_IS_V1(pwiv) || GENET_IS_V2(pwiv))
		wetuwn;

	fow (i = 0; i < MAX_NUM_OF_FS_WUWES; i++) {
		INIT_WIST_HEAD(&pwiv->wxnfc_wuwes[i].wist);
		pwiv->wxnfc_wuwes[i].state = BCMGENET_WXNFC_STATE_UNUSED;
	}

	bcmgenet_hfb_cweaw(pwiv);
}

static int bcmgenet_begin(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	/* Tuwn on the cwock */
	wetuwn cwk_pwepawe_enabwe(pwiv->cwk);
}

static void bcmgenet_compwete(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	/* Tuwn off the cwock */
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static int bcmgenet_get_wink_ksettings(stwuct net_device *dev,
				       stwuct ethtoow_wink_ksettings *cmd)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (!dev->phydev)
		wetuwn -ENODEV;

	phy_ethtoow_ksettings_get(dev->phydev, cmd);

	wetuwn 0;
}

static int bcmgenet_set_wink_ksettings(stwuct net_device *dev,
				       const stwuct ethtoow_wink_ksettings *cmd)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (!dev->phydev)
		wetuwn -ENODEV;

	wetuwn phy_ethtoow_ksettings_set(dev->phydev, cmd);
}

static int bcmgenet_set_featuwes(stwuct net_device *dev,
				 netdev_featuwes_t featuwes)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 weg;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	/* Make suwe we wefwect the vawue of CWC_CMD_FWD */
	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	pwiv->cwc_fwd_en = !!(weg & CMD_CWC_FWD);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static u32 bcmgenet_get_msgwevew(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->msg_enabwe;
}

static void bcmgenet_set_msgwevew(stwuct net_device *dev, u32 wevew)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->msg_enabwe = wevew;
}

static int bcmgenet_get_coawesce(stwuct net_device *dev,
				 stwuct ethtoow_coawesce *ec,
				 stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wx_wing *wing;
	unsigned int i;

	ec->tx_max_coawesced_fwames =
		bcmgenet_tdma_wing_weadw(pwiv, DESC_INDEX,
					 DMA_MBUF_DONE_THWESH);
	ec->wx_max_coawesced_fwames =
		bcmgenet_wdma_wing_weadw(pwiv, DESC_INDEX,
					 DMA_MBUF_DONE_THWESH);
	ec->wx_coawesce_usecs =
		bcmgenet_wdma_weadw(pwiv, DMA_WING16_TIMEOUT) * 8192 / 1000;

	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++) {
		wing = &pwiv->wx_wings[i];
		ec->use_adaptive_wx_coawesce |= wing->dim.use_dim;
	}
	wing = &pwiv->wx_wings[DESC_INDEX];
	ec->use_adaptive_wx_coawesce |= wing->dim.use_dim;

	wetuwn 0;
}

static void bcmgenet_set_wx_coawesce(stwuct bcmgenet_wx_wing *wing,
				     u32 usecs, u32 pkts)
{
	stwuct bcmgenet_pwiv *pwiv = wing->pwiv;
	unsigned int i = wing->index;
	u32 weg;

	bcmgenet_wdma_wing_wwitew(pwiv, i, pkts, DMA_MBUF_DONE_THWESH);

	weg = bcmgenet_wdma_weadw(pwiv, DMA_WING0_TIMEOUT + i);
	weg &= ~DMA_TIMEOUT_MASK;
	weg |= DIV_WOUND_UP(usecs * 1000, 8192);
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_WING0_TIMEOUT + i);
}

static void bcmgenet_set_wing_wx_coawesce(stwuct bcmgenet_wx_wing *wing,
					  stwuct ethtoow_coawesce *ec)
{
	stwuct dim_cq_modew modew;
	u32 usecs, pkts;

	wing->wx_coawesce_usecs = ec->wx_coawesce_usecs;
	wing->wx_max_coawesced_fwames = ec->wx_max_coawesced_fwames;
	usecs = wing->wx_coawesce_usecs;
	pkts = wing->wx_max_coawesced_fwames;

	if (ec->use_adaptive_wx_coawesce && !wing->dim.use_dim) {
		modew = net_dim_get_def_wx_modewation(wing->dim.dim.mode);
		usecs = modew.usec;
		pkts = modew.pkts;
	}

	wing->dim.use_dim = ec->use_adaptive_wx_coawesce;
	bcmgenet_set_wx_coawesce(wing, usecs, pkts);
}

static int bcmgenet_set_coawesce(stwuct net_device *dev,
				 stwuct ethtoow_coawesce *ec,
				 stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int i;

	/* Base system cwock is 125Mhz, DMA timeout is this wefewence cwock
	 * divided by 1024, which yiewds woughwy 8.192us, ouw maximum vawue
	 * has to fit in the DMA_TIMEOUT_MASK (16 bits)
	 */
	if (ec->tx_max_coawesced_fwames > DMA_INTW_THWESHOWD_MASK ||
	    ec->tx_max_coawesced_fwames == 0 ||
	    ec->wx_max_coawesced_fwames > DMA_INTW_THWESHOWD_MASK ||
	    ec->wx_coawesce_usecs > (DMA_TIMEOUT_MASK * 8) + 1)
		wetuwn -EINVAW;

	if (ec->wx_coawesce_usecs == 0 && ec->wx_max_coawesced_fwames == 0)
		wetuwn -EINVAW;

	/* GENET TDMA hawdwawe does not suppowt a configuwabwe timeout, but wiww
	 * awways genewate an intewwupt eithew aftew MBDONE packets have been
	 * twansmitted, ow when the wing is empty.
	 */

	/* Pwogwam aww TX queues with the same vawues, as thewe is no
	 * ethtoow knob to do coawescing on a pew-queue basis
	 */
	fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++)
		bcmgenet_tdma_wing_wwitew(pwiv, i,
					  ec->tx_max_coawesced_fwames,
					  DMA_MBUF_DONE_THWESH);
	bcmgenet_tdma_wing_wwitew(pwiv, DESC_INDEX,
				  ec->tx_max_coawesced_fwames,
				  DMA_MBUF_DONE_THWESH);

	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++)
		bcmgenet_set_wing_wx_coawesce(&pwiv->wx_wings[i], ec);
	bcmgenet_set_wing_wx_coawesce(&pwiv->wx_wings[DESC_INDEX], ec);

	wetuwn 0;
}

static void bcmgenet_get_pausepawam(stwuct net_device *dev,
				    stwuct ethtoow_pausepawam *epause)
{
	stwuct bcmgenet_pwiv *pwiv;
	u32 umac_cmd;

	pwiv = netdev_pwiv(dev);

	epause->autoneg = pwiv->autoneg_pause;

	if (netif_cawwiew_ok(dev)) {
		/* wepowt active state when wink is up */
		umac_cmd = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
		epause->tx_pause = !(umac_cmd & CMD_TX_PAUSE_IGNOWE);
		epause->wx_pause = !(umac_cmd & CMD_WX_PAUSE_IGNOWE);
	} ewse {
		/* othewwise wepowt stowed settings */
		epause->tx_pause = pwiv->tx_pause;
		epause->wx_pause = pwiv->wx_pause;
	}
}

static int bcmgenet_set_pausepawam(stwuct net_device *dev,
				   stwuct ethtoow_pausepawam *epause)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	if (!dev->phydev)
		wetuwn -ENODEV;

	if (!phy_vawidate_pause(dev->phydev, epause))
		wetuwn -EINVAW;

	pwiv->autoneg_pause = !!epause->autoneg;
	pwiv->tx_pause = !!epause->tx_pause;
	pwiv->wx_pause = !!epause->wx_pause;

	bcmgenet_phy_pause_set(dev, pwiv->wx_pause, pwiv->tx_pause);

	wetuwn 0;
}

/* standawd ethtoow suppowt functions. */
enum bcmgenet_stat_type {
	BCMGENET_STAT_NETDEV = -1,
	BCMGENET_STAT_MIB_WX,
	BCMGENET_STAT_MIB_TX,
	BCMGENET_STAT_WUNT,
	BCMGENET_STAT_MISC,
	BCMGENET_STAT_SOFT,
};

stwuct bcmgenet_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int stat_sizeof;
	int stat_offset;
	enum bcmgenet_stat_type type;
	/* weg offset fwom UMAC base fow misc countews */
	u16 weg_offset;
};

#define STAT_NETDEV(m) { \
	.stat_stwing = __stwingify(m), \
	.stat_sizeof = sizeof(((stwuct net_device_stats *)0)->m), \
	.stat_offset = offsetof(stwuct net_device_stats, m), \
	.type = BCMGENET_STAT_NETDEV, \
}

#define STAT_GENET_MIB(stw, m, _type) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcmgenet_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcmgenet_pwiv, m), \
	.type = _type, \
}

#define STAT_GENET_MIB_WX(stw, m) STAT_GENET_MIB(stw, m, BCMGENET_STAT_MIB_WX)
#define STAT_GENET_MIB_TX(stw, m) STAT_GENET_MIB(stw, m, BCMGENET_STAT_MIB_TX)
#define STAT_GENET_WUNT(stw, m) STAT_GENET_MIB(stw, m, BCMGENET_STAT_WUNT)
#define STAT_GENET_SOFT_MIB(stw, m) STAT_GENET_MIB(stw, m, BCMGENET_STAT_SOFT)

#define STAT_GENET_MISC(stw, m, offset) { \
	.stat_stwing = stw, \
	.stat_sizeof = sizeof(((stwuct bcmgenet_pwiv *)0)->m), \
	.stat_offset = offsetof(stwuct bcmgenet_pwiv, m), \
	.type = BCMGENET_STAT_MISC, \
	.weg_offset = offset, \
}

#define STAT_GENET_Q(num) \
	STAT_GENET_SOFT_MIB("txq" __stwingify(num) "_packets", \
			tx_wings[num].packets), \
	STAT_GENET_SOFT_MIB("txq" __stwingify(num) "_bytes", \
			tx_wings[num].bytes), \
	STAT_GENET_SOFT_MIB("wxq" __stwingify(num) "_bytes", \
			wx_wings[num].bytes),	 \
	STAT_GENET_SOFT_MIB("wxq" __stwingify(num) "_packets", \
			wx_wings[num].packets), \
	STAT_GENET_SOFT_MIB("wxq" __stwingify(num) "_ewwows", \
			wx_wings[num].ewwows), \
	STAT_GENET_SOFT_MIB("wxq" __stwingify(num) "_dwopped", \
			wx_wings[num].dwopped)

/* Thewe is a 0xC gap between the end of WX and beginning of TX stats and then
 * between the end of TX stats and the beginning of the WX WUNT
 */
#define BCMGENET_STAT_OFFSET	0xc

/* Hawdwawe countews must be kept in sync because the owdew/offset
 * is impowtant hewe (owdew in stwuctuwe decwawation = owdew in hawdwawe)
 */
static const stwuct bcmgenet_stats bcmgenet_gstwings_stats[] = {
	/* genewaw stats */
	STAT_NETDEV(wx_packets),
	STAT_NETDEV(tx_packets),
	STAT_NETDEV(wx_bytes),
	STAT_NETDEV(tx_bytes),
	STAT_NETDEV(wx_ewwows),
	STAT_NETDEV(tx_ewwows),
	STAT_NETDEV(wx_dwopped),
	STAT_NETDEV(tx_dwopped),
	STAT_NETDEV(muwticast),
	/* UniMAC WSV countews */
	STAT_GENET_MIB_WX("wx_64_octets", mib.wx.pkt_cnt.cnt_64),
	STAT_GENET_MIB_WX("wx_65_127_oct", mib.wx.pkt_cnt.cnt_127),
	STAT_GENET_MIB_WX("wx_128_255_oct", mib.wx.pkt_cnt.cnt_255),
	STAT_GENET_MIB_WX("wx_256_511_oct", mib.wx.pkt_cnt.cnt_511),
	STAT_GENET_MIB_WX("wx_512_1023_oct", mib.wx.pkt_cnt.cnt_1023),
	STAT_GENET_MIB_WX("wx_1024_1518_oct", mib.wx.pkt_cnt.cnt_1518),
	STAT_GENET_MIB_WX("wx_vwan_1519_1522_oct", mib.wx.pkt_cnt.cnt_mgv),
	STAT_GENET_MIB_WX("wx_1522_2047_oct", mib.wx.pkt_cnt.cnt_2047),
	STAT_GENET_MIB_WX("wx_2048_4095_oct", mib.wx.pkt_cnt.cnt_4095),
	STAT_GENET_MIB_WX("wx_4096_9216_oct", mib.wx.pkt_cnt.cnt_9216),
	STAT_GENET_MIB_WX("wx_pkts", mib.wx.pkt),
	STAT_GENET_MIB_WX("wx_bytes", mib.wx.bytes),
	STAT_GENET_MIB_WX("wx_muwticast", mib.wx.mca),
	STAT_GENET_MIB_WX("wx_bwoadcast", mib.wx.bca),
	STAT_GENET_MIB_WX("wx_fcs", mib.wx.fcs),
	STAT_GENET_MIB_WX("wx_contwow", mib.wx.cf),
	STAT_GENET_MIB_WX("wx_pause", mib.wx.pf),
	STAT_GENET_MIB_WX("wx_unknown", mib.wx.uo),
	STAT_GENET_MIB_WX("wx_awign", mib.wx.awn),
	STAT_GENET_MIB_WX("wx_outwange", mib.wx.fww),
	STAT_GENET_MIB_WX("wx_code", mib.wx.cde),
	STAT_GENET_MIB_WX("wx_cawwiew", mib.wx.fcw),
	STAT_GENET_MIB_WX("wx_ovewsize", mib.wx.ovw),
	STAT_GENET_MIB_WX("wx_jabbew", mib.wx.jbw),
	STAT_GENET_MIB_WX("wx_mtu_eww", mib.wx.mtue),
	STAT_GENET_MIB_WX("wx_good_pkts", mib.wx.pok),
	STAT_GENET_MIB_WX("wx_unicast", mib.wx.uc),
	STAT_GENET_MIB_WX("wx_ppp", mib.wx.ppp),
	STAT_GENET_MIB_WX("wx_cwc", mib.wx.wcwc),
	/* UniMAC TSV countews */
	STAT_GENET_MIB_TX("tx_64_octets", mib.tx.pkt_cnt.cnt_64),
	STAT_GENET_MIB_TX("tx_65_127_oct", mib.tx.pkt_cnt.cnt_127),
	STAT_GENET_MIB_TX("tx_128_255_oct", mib.tx.pkt_cnt.cnt_255),
	STAT_GENET_MIB_TX("tx_256_511_oct", mib.tx.pkt_cnt.cnt_511),
	STAT_GENET_MIB_TX("tx_512_1023_oct", mib.tx.pkt_cnt.cnt_1023),
	STAT_GENET_MIB_TX("tx_1024_1518_oct", mib.tx.pkt_cnt.cnt_1518),
	STAT_GENET_MIB_TX("tx_vwan_1519_1522_oct", mib.tx.pkt_cnt.cnt_mgv),
	STAT_GENET_MIB_TX("tx_1522_2047_oct", mib.tx.pkt_cnt.cnt_2047),
	STAT_GENET_MIB_TX("tx_2048_4095_oct", mib.tx.pkt_cnt.cnt_4095),
	STAT_GENET_MIB_TX("tx_4096_9216_oct", mib.tx.pkt_cnt.cnt_9216),
	STAT_GENET_MIB_TX("tx_pkts", mib.tx.pkts),
	STAT_GENET_MIB_TX("tx_muwticast", mib.tx.mca),
	STAT_GENET_MIB_TX("tx_bwoadcast", mib.tx.bca),
	STAT_GENET_MIB_TX("tx_pause", mib.tx.pf),
	STAT_GENET_MIB_TX("tx_contwow", mib.tx.cf),
	STAT_GENET_MIB_TX("tx_fcs_eww", mib.tx.fcs),
	STAT_GENET_MIB_TX("tx_ovewsize", mib.tx.ovw),
	STAT_GENET_MIB_TX("tx_defew", mib.tx.dwf),
	STAT_GENET_MIB_TX("tx_excess_defew", mib.tx.edf),
	STAT_GENET_MIB_TX("tx_singwe_cow", mib.tx.scw),
	STAT_GENET_MIB_TX("tx_muwti_cow", mib.tx.mcw),
	STAT_GENET_MIB_TX("tx_wate_cow", mib.tx.wcw),
	STAT_GENET_MIB_TX("tx_excess_cow", mib.tx.ecw),
	STAT_GENET_MIB_TX("tx_fwags", mib.tx.fwg),
	STAT_GENET_MIB_TX("tx_totaw_cow", mib.tx.ncw),
	STAT_GENET_MIB_TX("tx_jabbew", mib.tx.jbw),
	STAT_GENET_MIB_TX("tx_bytes", mib.tx.bytes),
	STAT_GENET_MIB_TX("tx_good_pkts", mib.tx.pok),
	STAT_GENET_MIB_TX("tx_unicast", mib.tx.uc),
	/* UniMAC WUNT countews */
	STAT_GENET_WUNT("wx_wunt_pkts", mib.wx_wunt_cnt),
	STAT_GENET_WUNT("wx_wunt_vawid_fcs", mib.wx_wunt_fcs),
	STAT_GENET_WUNT("wx_wunt_invaw_fcs_awign", mib.wx_wunt_fcs_awign),
	STAT_GENET_WUNT("wx_wunt_bytes", mib.wx_wunt_bytes),
	/* Misc UniMAC countews */
	STAT_GENET_MISC("wbuf_ovfwow_cnt", mib.wbuf_ovfwow_cnt,
			UMAC_WBUF_OVFW_CNT_V1),
	STAT_GENET_MISC("wbuf_eww_cnt", mib.wbuf_eww_cnt,
			UMAC_WBUF_EWW_CNT_V1),
	STAT_GENET_MISC("mdf_eww_cnt", mib.mdf_eww_cnt, UMAC_MDF_EWW_CNT),
	STAT_GENET_SOFT_MIB("awwoc_wx_buff_faiwed", mib.awwoc_wx_buff_faiwed),
	STAT_GENET_SOFT_MIB("wx_dma_faiwed", mib.wx_dma_faiwed),
	STAT_GENET_SOFT_MIB("tx_dma_faiwed", mib.tx_dma_faiwed),
	STAT_GENET_SOFT_MIB("tx_weawwoc_tsb", mib.tx_weawwoc_tsb),
	STAT_GENET_SOFT_MIB("tx_weawwoc_tsb_faiwed",
			    mib.tx_weawwoc_tsb_faiwed),
	/* Pew TX queues */
	STAT_GENET_Q(0),
	STAT_GENET_Q(1),
	STAT_GENET_Q(2),
	STAT_GENET_Q(3),
	STAT_GENET_Q(16),
};

#define BCMGENET_STATS_WEN	AWWAY_SIZE(bcmgenet_gstwings_stats)

static void bcmgenet_get_dwvinfo(stwuct net_device *dev,
				 stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, "bcmgenet", sizeof(info->dwivew));
}

static int bcmgenet_get_sset_count(stwuct net_device *dev, int stwing_set)
{
	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn BCMGENET_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void bcmgenet_get_stwings(stwuct net_device *dev, u32 stwingset,
				 u8 *data)
{
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < BCMGENET_STATS_WEN; i++) {
			memcpy(data + i * ETH_GSTWING_WEN,
			       bcmgenet_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
		}
		bweak;
	}
}

static u32 bcmgenet_update_stat_misc(stwuct bcmgenet_pwiv *pwiv, u16 offset)
{
	u16 new_offset;
	u32 vaw;

	switch (offset) {
	case UMAC_WBUF_OVFW_CNT_V1:
		if (GENET_IS_V2(pwiv))
			new_offset = WBUF_OVFW_CNT_V2;
		ewse
			new_offset = WBUF_OVFW_CNT_V3PWUS;

		vaw = bcmgenet_wbuf_weadw(pwiv,	new_offset);
		/* cweaw if ovewfwowed */
		if (vaw == ~0)
			bcmgenet_wbuf_wwitew(pwiv, 0, new_offset);
		bweak;
	case UMAC_WBUF_EWW_CNT_V1:
		if (GENET_IS_V2(pwiv))
			new_offset = WBUF_EWW_CNT_V2;
		ewse
			new_offset = WBUF_EWW_CNT_V3PWUS;

		vaw = bcmgenet_wbuf_weadw(pwiv,	new_offset);
		/* cweaw if ovewfwowed */
		if (vaw == ~0)
			bcmgenet_wbuf_wwitew(pwiv, 0, new_offset);
		bweak;
	defauwt:
		vaw = bcmgenet_umac_weadw(pwiv, offset);
		/* cweaw if ovewfwowed */
		if (vaw == ~0)
			bcmgenet_umac_wwitew(pwiv, 0, offset);
		bweak;
	}

	wetuwn vaw;
}

static void bcmgenet_update_mib_countews(stwuct bcmgenet_pwiv *pwiv)
{
	int i, j = 0;

	fow (i = 0; i < BCMGENET_STATS_WEN; i++) {
		const stwuct bcmgenet_stats *s;
		u8 offset = 0;
		u32 vaw = 0;
		chaw *p;

		s = &bcmgenet_gstwings_stats[i];
		switch (s->type) {
		case BCMGENET_STAT_NETDEV:
		case BCMGENET_STAT_SOFT:
			continue;
		case BCMGENET_STAT_WUNT:
			offset += BCMGENET_STAT_OFFSET;
			fawwthwough;
		case BCMGENET_STAT_MIB_TX:
			offset += BCMGENET_STAT_OFFSET;
			fawwthwough;
		case BCMGENET_STAT_MIB_WX:
			vaw = bcmgenet_umac_weadw(pwiv,
						  UMAC_MIB_STAWT + j + offset);
			offset = 0;	/* Weset Offset */
			bweak;
		case BCMGENET_STAT_MISC:
			if (GENET_IS_V1(pwiv)) {
				vaw = bcmgenet_umac_weadw(pwiv, s->weg_offset);
				/* cweaw if ovewfwowed */
				if (vaw == ~0)
					bcmgenet_umac_wwitew(pwiv, 0,
							     s->weg_offset);
			} ewse {
				vaw = bcmgenet_update_stat_misc(pwiv,
								s->weg_offset);
			}
			bweak;
		}

		j += s->stat_sizeof;
		p = (chaw *)pwiv + s->stat_offset;
		*(u32 *)p = vaw;
	}
}

static void bcmgenet_get_ethtoow_stats(stwuct net_device *dev,
				       stwuct ethtoow_stats *stats,
				       u64 *data)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	if (netif_wunning(dev))
		bcmgenet_update_mib_countews(pwiv);

	dev->netdev_ops->ndo_get_stats(dev);

	fow (i = 0; i < BCMGENET_STATS_WEN; i++) {
		const stwuct bcmgenet_stats *s;
		chaw *p;

		s = &bcmgenet_gstwings_stats[i];
		if (s->type == BCMGENET_STAT_NETDEV)
			p = (chaw *)&dev->stats;
		ewse
			p = (chaw *)pwiv;
		p += s->stat_offset;
		if (sizeof(unsigned wong) != sizeof(u32) &&
		    s->stat_sizeof == sizeof(unsigned wong))
			data[i] = *(unsigned wong *)p;
		ewse
			data[i] = *(u32 *)p;
	}
}

void bcmgenet_eee_enabwe_set(stwuct net_device *dev, boow enabwe,
			     boow tx_wpi_enabwed)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 off = pwiv->hw_pawams->tbuf_offset + TBUF_ENEWGY_CTWW;
	u32 weg;

	if (enabwe && !pwiv->cwk_eee_enabwed) {
		cwk_pwepawe_enabwe(pwiv->cwk_eee);
		pwiv->cwk_eee_enabwed = twue;
	}

	weg = bcmgenet_umac_weadw(pwiv, UMAC_EEE_CTWW);
	if (enabwe)
		weg |= EEE_EN;
	ewse
		weg &= ~EEE_EN;
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_EEE_CTWW);

	/* Enabwe EEE and switch to a 27Mhz cwock automaticawwy */
	weg = bcmgenet_weadw(pwiv->base + off);
	if (tx_wpi_enabwed)
		weg |= TBUF_EEE_EN | TBUF_PM_EN;
	ewse
		weg &= ~(TBUF_EEE_EN | TBUF_PM_EN);
	bcmgenet_wwitew(weg, pwiv->base + off);

	/* Do the same fow thing fow WBUF */
	weg = bcmgenet_wbuf_weadw(pwiv, WBUF_ENEWGY_CTWW);
	if (enabwe)
		weg |= WBUF_EEE_EN | WBUF_PM_EN;
	ewse
		weg &= ~(WBUF_EEE_EN | WBUF_PM_EN);
	bcmgenet_wbuf_wwitew(pwiv, weg, WBUF_ENEWGY_CTWW);

	if (!enabwe && pwiv->cwk_eee_enabwed) {
		cwk_disabwe_unpwepawe(pwiv->cwk_eee);
		pwiv->cwk_eee_enabwed = fawse;
	}

	pwiv->eee.eee_enabwed = enabwe;
	pwiv->eee.eee_active = enabwe;
	pwiv->eee.tx_wpi_enabwed = tx_wpi_enabwed;
}

static int bcmgenet_get_eee(stwuct net_device *dev, stwuct ethtoow_eee *e)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct ethtoow_eee *p = &pwiv->eee;

	if (GENET_IS_V1(pwiv))
		wetuwn -EOPNOTSUPP;

	if (!dev->phydev)
		wetuwn -ENODEV;

	e->eee_enabwed = p->eee_enabwed;
	e->eee_active = p->eee_active;
	e->tx_wpi_enabwed = p->tx_wpi_enabwed;
	e->tx_wpi_timew = bcmgenet_umac_weadw(pwiv, UMAC_EEE_WPI_TIMEW);

	wetuwn phy_ethtoow_get_eee(dev->phydev, e);
}

static int bcmgenet_set_eee(stwuct net_device *dev, stwuct ethtoow_eee *e)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct ethtoow_eee *p = &pwiv->eee;

	if (GENET_IS_V1(pwiv))
		wetuwn -EOPNOTSUPP;

	if (!dev->phydev)
		wetuwn -ENODEV;

	p->eee_enabwed = e->eee_enabwed;

	if (!p->eee_enabwed) {
		bcmgenet_eee_enabwe_set(dev, fawse, fawse);
	} ewse {
		p->eee_active = phy_init_eee(dev->phydev, fawse) >= 0;
		bcmgenet_umac_wwitew(pwiv, e->tx_wpi_timew, UMAC_EEE_WPI_TIMEW);
		bcmgenet_eee_enabwe_set(dev, p->eee_active, e->tx_wpi_enabwed);
	}

	wetuwn phy_ethtoow_set_eee(dev->phydev, e);
}

static int bcmgenet_vawidate_fwow(stwuct net_device *dev,
				  stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_uswip4_spec *w4_mask;
	stwuct ethhdw *eth_mask;

	if (cmd->fs.wocation >= MAX_NUM_OF_FS_WUWES &&
	    cmd->fs.wocation != WX_CWS_WOC_ANY) {
		netdev_eww(dev, "wxnfc: Invawid wocation (%d)\n",
			   cmd->fs.wocation);
		wetuwn -EINVAW;
	}

	switch (cmd->fs.fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT)) {
	case IP_USEW_FWOW:
		w4_mask = &cmd->fs.m_u.usw_ip4_spec;
		/* don't awwow mask which isn't vawid */
		if (VAWIDATE_MASK(w4_mask->ip4swc) ||
		    VAWIDATE_MASK(w4_mask->ip4dst) ||
		    VAWIDATE_MASK(w4_mask->w4_4_bytes) ||
		    VAWIDATE_MASK(w4_mask->pwoto) ||
		    VAWIDATE_MASK(w4_mask->ip_vew) ||
		    VAWIDATE_MASK(w4_mask->tos)) {
			netdev_eww(dev, "wxnfc: Unsuppowted mask\n");
			wetuwn -EINVAW;
		}
		bweak;
	case ETHEW_FWOW:
		eth_mask = &cmd->fs.m_u.ethew_spec;
		/* don't awwow mask which isn't vawid */
		if (VAWIDATE_MASK(eth_mask->h_dest) ||
		    VAWIDATE_MASK(eth_mask->h_souwce) ||
		    VAWIDATE_MASK(eth_mask->h_pwoto)) {
			netdev_eww(dev, "wxnfc: Unsuppowted mask\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		netdev_eww(dev, "wxnfc: Unsuppowted fwow type (0x%x)\n",
			   cmd->fs.fwow_type);
		wetuwn -EINVAW;
	}

	if ((cmd->fs.fwow_type & FWOW_EXT)) {
		/* don't awwow mask which isn't vawid */
		if (VAWIDATE_MASK(cmd->fs.m_ext.vwan_etype) ||
		    VAWIDATE_MASK(cmd->fs.m_ext.vwan_tci)) {
			netdev_eww(dev, "wxnfc: Unsuppowted mask\n");
			wetuwn -EINVAW;
		}
		if (cmd->fs.m_ext.data[0] || cmd->fs.m_ext.data[1]) {
			netdev_eww(dev, "wxnfc: usew-def not suppowted\n");
			wetuwn -EINVAW;
		}
	}

	if ((cmd->fs.fwow_type & FWOW_MAC_EXT)) {
		/* don't awwow mask which isn't vawid */
		if (VAWIDATE_MASK(cmd->fs.m_ext.h_dest)) {
			netdev_eww(dev, "wxnfc: Unsuppowted mask\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int bcmgenet_insewt_fwow(stwuct net_device *dev,
				stwuct ethtoow_wxnfc *cmd)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wxnfc_wuwe *woc_wuwe;
	int eww, i;

	if (pwiv->hw_pawams->hfb_fiwtew_size < 128) {
		netdev_eww(dev, "wxnfc: Not suppowted by this device\n");
		wetuwn -EINVAW;
	}

	if (cmd->fs.wing_cookie > pwiv->hw_pawams->wx_queues &&
	    cmd->fs.wing_cookie != WX_CWS_FWOW_WAKE) {
		netdev_eww(dev, "wxnfc: Unsuppowted action (%wwu)\n",
			   cmd->fs.wing_cookie);
		wetuwn -EINVAW;
	}

	eww = bcmgenet_vawidate_fwow(dev, cmd);
	if (eww)
		wetuwn eww;

	if (cmd->fs.wocation == WX_CWS_WOC_ANY) {
		wist_fow_each_entwy(woc_wuwe, &pwiv->wxnfc_wist, wist) {
			cmd->fs.wocation = woc_wuwe->fs.wocation;
			eww = memcmp(&woc_wuwe->fs, &cmd->fs,
				     sizeof(stwuct ethtoow_wx_fwow_spec));
			if (!eww)
				/* wuwe exists so wetuwn cuwwent wocation */
				wetuwn 0;
		}
		fow (i = 0; i < MAX_NUM_OF_FS_WUWES; i++) {
			woc_wuwe = &pwiv->wxnfc_wuwes[i];
			if (woc_wuwe->state == BCMGENET_WXNFC_STATE_UNUSED) {
				cmd->fs.wocation = i;
				bweak;
			}
		}
		if (i == MAX_NUM_OF_FS_WUWES) {
			cmd->fs.wocation = WX_CWS_WOC_ANY;
			wetuwn -ENOSPC;
		}
	} ewse {
		woc_wuwe = &pwiv->wxnfc_wuwes[cmd->fs.wocation];
	}
	if (woc_wuwe->state == BCMGENET_WXNFC_STATE_ENABWED)
		bcmgenet_hfb_disabwe_fiwtew(pwiv, cmd->fs.wocation);
	if (woc_wuwe->state != BCMGENET_WXNFC_STATE_UNUSED) {
		wist_dew(&woc_wuwe->wist);
		bcmgenet_hfb_cweaw_fiwtew(pwiv, cmd->fs.wocation);
	}
	woc_wuwe->state = BCMGENET_WXNFC_STATE_UNUSED;
	memcpy(&woc_wuwe->fs, &cmd->fs,
	       sizeof(stwuct ethtoow_wx_fwow_spec));

	bcmgenet_hfb_cweate_wxnfc_fiwtew(pwiv, woc_wuwe);

	wist_add_taiw(&woc_wuwe->wist, &pwiv->wxnfc_wist);

	wetuwn 0;
}

static int bcmgenet_dewete_fwow(stwuct net_device *dev,
				stwuct ethtoow_wxnfc *cmd)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wxnfc_wuwe *wuwe;
	int eww = 0;

	if (cmd->fs.wocation >= MAX_NUM_OF_FS_WUWES)
		wetuwn -EINVAW;

	wuwe = &pwiv->wxnfc_wuwes[cmd->fs.wocation];
	if (wuwe->state == BCMGENET_WXNFC_STATE_UNUSED) {
		eww =  -ENOENT;
		goto out;
	}

	if (wuwe->state == BCMGENET_WXNFC_STATE_ENABWED)
		bcmgenet_hfb_disabwe_fiwtew(pwiv, cmd->fs.wocation);
	if (wuwe->state != BCMGENET_WXNFC_STATE_UNUSED) {
		wist_dew(&wuwe->wist);
		bcmgenet_hfb_cweaw_fiwtew(pwiv, cmd->fs.wocation);
	}
	wuwe->state = BCMGENET_WXNFC_STATE_UNUSED;
	memset(&wuwe->fs, 0, sizeof(stwuct ethtoow_wx_fwow_spec));

out:
	wetuwn eww;
}

static int bcmgenet_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int eww = 0;

	switch (cmd->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		eww = bcmgenet_insewt_fwow(dev, cmd);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		eww = bcmgenet_dewete_fwow(dev, cmd);
		bweak;
	defauwt:
		netdev_wawn(pwiv->dev, "Unsuppowted ethtoow command. (%d)\n",
			    cmd->cmd);
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static int bcmgenet_get_fwow(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			     int woc)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wxnfc_wuwe *wuwe;
	int eww = 0;

	if (woc < 0 || woc >= MAX_NUM_OF_FS_WUWES)
		wetuwn -EINVAW;

	wuwe = &pwiv->wxnfc_wuwes[woc];
	if (wuwe->state == BCMGENET_WXNFC_STATE_UNUSED)
		eww = -ENOENT;
	ewse
		memcpy(&cmd->fs, &wuwe->fs,
		       sizeof(stwuct ethtoow_wx_fwow_spec));

	wetuwn eww;
}

static int bcmgenet_get_num_fwows(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct wist_head *pos;
	int wes = 0;

	wist_fow_each(pos, &pwiv->wxnfc_wist)
		wes++;

	wetuwn wes;
}

static int bcmgenet_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			      u32 *wuwe_wocs)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wxnfc_wuwe *wuwe;
	int eww = 0;
	int i = 0;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = pwiv->hw_pawams->wx_queues ?: 1;
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		cmd->wuwe_cnt = bcmgenet_get_num_fwows(pwiv);
		cmd->data = MAX_NUM_OF_FS_WUWES | WX_CWS_WOC_SPECIAW;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		eww = bcmgenet_get_fwow(dev, cmd, cmd->fs.wocation);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		wist_fow_each_entwy(wuwe, &pwiv->wxnfc_wist, wist)
			if (i < cmd->wuwe_cnt)
				wuwe_wocs[i++] = wuwe->fs.wocation;
		cmd->wuwe_cnt = i;
		cmd->data = MAX_NUM_OF_FS_WUWES;
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

/* standawd ethtoow suppowt functions. */
static const stwuct ethtoow_ops bcmgenet_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.begin			= bcmgenet_begin,
	.compwete		= bcmgenet_compwete,
	.get_stwings		= bcmgenet_get_stwings,
	.get_sset_count		= bcmgenet_get_sset_count,
	.get_ethtoow_stats	= bcmgenet_get_ethtoow_stats,
	.get_dwvinfo		= bcmgenet_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_msgwevew		= bcmgenet_get_msgwevew,
	.set_msgwevew		= bcmgenet_set_msgwevew,
	.get_wow		= bcmgenet_get_wow,
	.set_wow		= bcmgenet_set_wow,
	.get_eee		= bcmgenet_get_eee,
	.set_eee		= bcmgenet_set_eee,
	.nway_weset		= phy_ethtoow_nway_weset,
	.get_coawesce		= bcmgenet_get_coawesce,
	.set_coawesce		= bcmgenet_set_coawesce,
	.get_wink_ksettings	= bcmgenet_get_wink_ksettings,
	.set_wink_ksettings	= bcmgenet_set_wink_ksettings,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wxnfc		= bcmgenet_get_wxnfc,
	.set_wxnfc		= bcmgenet_set_wxnfc,
	.get_pausepawam		= bcmgenet_get_pausepawam,
	.set_pausepawam		= bcmgenet_set_pausepawam,
};

/* Powew down the unimac, based on mode. */
static int bcmgenet_powew_down(stwuct bcmgenet_pwiv *pwiv,
				enum bcmgenet_powew_mode mode)
{
	int wet = 0;
	u32 weg;

	switch (mode) {
	case GENET_POWEW_CABWE_SENSE:
		phy_detach(pwiv->dev->phydev);
		bweak;

	case GENET_POWEW_WOW_MAGIC:
		wet = bcmgenet_wow_powew_down_cfg(pwiv, mode);
		bweak;

	case GENET_POWEW_PASSIVE:
		/* Powew down WED */
		if (pwiv->hw_pawams->fwags & GENET_HAS_EXT) {
			weg = bcmgenet_ext_weadw(pwiv, EXT_EXT_PWW_MGMT);
			if (GENET_IS_V5(pwiv) && !pwiv->ephy_16nm)
				weg |= EXT_PWW_DOWN_PHY_EN |
				       EXT_PWW_DOWN_PHY_WD |
				       EXT_PWW_DOWN_PHY_SD |
				       EXT_PWW_DOWN_PHY_WX |
				       EXT_PWW_DOWN_PHY_TX |
				       EXT_IDDQ_GWBW_PWW;
			ewse
				weg |= EXT_PWW_DOWN_PHY;

			weg |= (EXT_PWW_DOWN_DWW | EXT_PWW_DOWN_BIAS);
			bcmgenet_ext_wwitew(pwiv, weg, EXT_EXT_PWW_MGMT);

			bcmgenet_phy_powew_set(pwiv->dev, fawse);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void bcmgenet_powew_up(stwuct bcmgenet_pwiv *pwiv,
			      enum bcmgenet_powew_mode mode)
{
	u32 weg;

	if (!(pwiv->hw_pawams->fwags & GENET_HAS_EXT))
		wetuwn;

	weg = bcmgenet_ext_weadw(pwiv, EXT_EXT_PWW_MGMT);

	switch (mode) {
	case GENET_POWEW_PASSIVE:
		weg &= ~(EXT_PWW_DOWN_DWW | EXT_PWW_DOWN_BIAS |
			 EXT_ENEWGY_DET_MASK);
		if (GENET_IS_V5(pwiv) && !pwiv->ephy_16nm) {
			weg &= ~(EXT_PWW_DOWN_PHY_EN |
				 EXT_PWW_DOWN_PHY_WD |
				 EXT_PWW_DOWN_PHY_SD |
				 EXT_PWW_DOWN_PHY_WX |
				 EXT_PWW_DOWN_PHY_TX |
				 EXT_IDDQ_GWBW_PWW);
			weg |=   EXT_PHY_WESET;
			bcmgenet_ext_wwitew(pwiv, weg, EXT_EXT_PWW_MGMT);
			mdeway(1);

			weg &=  ~EXT_PHY_WESET;
		} ewse {
			weg &= ~EXT_PWW_DOWN_PHY;
			weg |= EXT_PWW_DN_EN_WD;
		}
		bcmgenet_ext_wwitew(pwiv, weg, EXT_EXT_PWW_MGMT);
		bcmgenet_phy_powew_set(pwiv->dev, twue);
		bweak;

	case GENET_POWEW_CABWE_SENSE:
		/* enabwe APD */
		if (!GENET_IS_V5(pwiv)) {
			weg |= EXT_PWW_DN_EN_WD;
			bcmgenet_ext_wwitew(pwiv, weg, EXT_EXT_PWW_MGMT);
		}
		bweak;
	case GENET_POWEW_WOW_MAGIC:
		bcmgenet_wow_powew_up_cfg(pwiv, mode);
		wetuwn;
	defauwt:
		bweak;
	}
}

static stwuct enet_cb *bcmgenet_get_txcb(stwuct bcmgenet_pwiv *pwiv,
					 stwuct bcmgenet_tx_wing *wing)
{
	stwuct enet_cb *tx_cb_ptw;

	tx_cb_ptw = wing->cbs;
	tx_cb_ptw += wing->wwite_ptw - wing->cb_ptw;

	/* Advancing wocaw wwite pointew */
	if (wing->wwite_ptw == wing->end_ptw)
		wing->wwite_ptw = wing->cb_ptw;
	ewse
		wing->wwite_ptw++;

	wetuwn tx_cb_ptw;
}

static stwuct enet_cb *bcmgenet_put_txcb(stwuct bcmgenet_pwiv *pwiv,
					 stwuct bcmgenet_tx_wing *wing)
{
	stwuct enet_cb *tx_cb_ptw;

	tx_cb_ptw = wing->cbs;
	tx_cb_ptw += wing->wwite_ptw - wing->cb_ptw;

	/* Wewinding wocaw wwite pointew */
	if (wing->wwite_ptw == wing->cb_ptw)
		wing->wwite_ptw = wing->end_ptw;
	ewse
		wing->wwite_ptw--;

	wetuwn tx_cb_ptw;
}

static inwine void bcmgenet_wx_wing16_int_disabwe(stwuct bcmgenet_wx_wing *wing)
{
	bcmgenet_intww2_0_wwitew(wing->pwiv, UMAC_IWQ_WXDMA_DONE,
				 INTWW2_CPU_MASK_SET);
}

static inwine void bcmgenet_wx_wing16_int_enabwe(stwuct bcmgenet_wx_wing *wing)
{
	bcmgenet_intww2_0_wwitew(wing->pwiv, UMAC_IWQ_WXDMA_DONE,
				 INTWW2_CPU_MASK_CWEAW);
}

static inwine void bcmgenet_wx_wing_int_disabwe(stwuct bcmgenet_wx_wing *wing)
{
	bcmgenet_intww2_1_wwitew(wing->pwiv,
				 1 << (UMAC_IWQ1_WX_INTW_SHIFT + wing->index),
				 INTWW2_CPU_MASK_SET);
}

static inwine void bcmgenet_wx_wing_int_enabwe(stwuct bcmgenet_wx_wing *wing)
{
	bcmgenet_intww2_1_wwitew(wing->pwiv,
				 1 << (UMAC_IWQ1_WX_INTW_SHIFT + wing->index),
				 INTWW2_CPU_MASK_CWEAW);
}

static inwine void bcmgenet_tx_wing16_int_disabwe(stwuct bcmgenet_tx_wing *wing)
{
	bcmgenet_intww2_0_wwitew(wing->pwiv, UMAC_IWQ_TXDMA_DONE,
				 INTWW2_CPU_MASK_SET);
}

static inwine void bcmgenet_tx_wing16_int_enabwe(stwuct bcmgenet_tx_wing *wing)
{
	bcmgenet_intww2_0_wwitew(wing->pwiv, UMAC_IWQ_TXDMA_DONE,
				 INTWW2_CPU_MASK_CWEAW);
}

static inwine void bcmgenet_tx_wing_int_enabwe(stwuct bcmgenet_tx_wing *wing)
{
	bcmgenet_intww2_1_wwitew(wing->pwiv, 1 << wing->index,
				 INTWW2_CPU_MASK_CWEAW);
}

static inwine void bcmgenet_tx_wing_int_disabwe(stwuct bcmgenet_tx_wing *wing)
{
	bcmgenet_intww2_1_wwitew(wing->pwiv, 1 << wing->index,
				 INTWW2_CPU_MASK_SET);
}

/* Simpwe hewpew to fwee a twansmit contwow bwock's wesouwces
 * Wetuwns an skb when the wast twansmit contwow bwock associated with the
 * skb is fweed.  The skb shouwd be fweed by the cawwew if necessawy.
 */
static stwuct sk_buff *bcmgenet_fwee_tx_cb(stwuct device *dev,
					   stwuct enet_cb *cb)
{
	stwuct sk_buff *skb;

	skb = cb->skb;

	if (skb) {
		cb->skb = NUWW;
		if (cb == GENET_CB(skb)->fiwst_cb)
			dma_unmap_singwe(dev, dma_unmap_addw(cb, dma_addw),
					 dma_unmap_wen(cb, dma_wen),
					 DMA_TO_DEVICE);
		ewse
			dma_unmap_page(dev, dma_unmap_addw(cb, dma_addw),
				       dma_unmap_wen(cb, dma_wen),
				       DMA_TO_DEVICE);
		dma_unmap_addw_set(cb, dma_addw, 0);

		if (cb == GENET_CB(skb)->wast_cb)
			wetuwn skb;

	} ewse if (dma_unmap_addw(cb, dma_addw)) {
		dma_unmap_page(dev,
			       dma_unmap_addw(cb, dma_addw),
			       dma_unmap_wen(cb, dma_wen),
			       DMA_TO_DEVICE);
		dma_unmap_addw_set(cb, dma_addw, 0);
	}

	wetuwn NUWW;
}

/* Simpwe hewpew to fwee a weceive contwow bwock's wesouwces */
static stwuct sk_buff *bcmgenet_fwee_wx_cb(stwuct device *dev,
					   stwuct enet_cb *cb)
{
	stwuct sk_buff *skb;

	skb = cb->skb;
	cb->skb = NUWW;

	if (dma_unmap_addw(cb, dma_addw)) {
		dma_unmap_singwe(dev, dma_unmap_addw(cb, dma_addw),
				 dma_unmap_wen(cb, dma_wen), DMA_FWOM_DEVICE);
		dma_unmap_addw_set(cb, dma_addw, 0);
	}

	wetuwn skb;
}

/* Unwocked vewsion of the wecwaim woutine */
static unsigned int __bcmgenet_tx_wecwaim(stwuct net_device *dev,
					  stwuct bcmgenet_tx_wing *wing)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int txbds_pwocessed = 0;
	unsigned int bytes_compw = 0;
	unsigned int pkts_compw = 0;
	unsigned int txbds_weady;
	unsigned int c_index;
	stwuct sk_buff *skb;

	/* Cweaw status befowe sewvicing to weduce spuwious intewwupts */
	if (wing->index == DESC_INDEX)
		bcmgenet_intww2_0_wwitew(pwiv, UMAC_IWQ_TXDMA_DONE,
					 INTWW2_CPU_CWEAW);
	ewse
		bcmgenet_intww2_1_wwitew(pwiv, (1 << wing->index),
					 INTWW2_CPU_CWEAW);

	/* Compute how many buffews awe twansmitted since wast xmit caww */
	c_index = bcmgenet_tdma_wing_weadw(pwiv, wing->index, TDMA_CONS_INDEX)
		& DMA_C_INDEX_MASK;
	txbds_weady = (c_index - wing->c_index) & DMA_C_INDEX_MASK;

	netif_dbg(pwiv, tx_done, dev,
		  "%s wing=%d owd_c_index=%u c_index=%u txbds_weady=%u\n",
		  __func__, wing->index, wing->c_index, c_index, txbds_weady);

	/* Wecwaim twansmitted buffews */
	whiwe (txbds_pwocessed < txbds_weady) {
		skb = bcmgenet_fwee_tx_cb(&pwiv->pdev->dev,
					  &pwiv->tx_cbs[wing->cwean_ptw]);
		if (skb) {
			pkts_compw++;
			bytes_compw += GENET_CB(skb)->bytes_sent;
			dev_consume_skb_any(skb);
		}

		txbds_pwocessed++;
		if (wikewy(wing->cwean_ptw < wing->end_ptw))
			wing->cwean_ptw++;
		ewse
			wing->cwean_ptw = wing->cb_ptw;
	}

	wing->fwee_bds += txbds_pwocessed;
	wing->c_index = c_index;

	wing->packets += pkts_compw;
	wing->bytes += bytes_compw;

	netdev_tx_compweted_queue(netdev_get_tx_queue(dev, wing->queue),
				  pkts_compw, bytes_compw);

	wetuwn txbds_pwocessed;
}

static unsigned int bcmgenet_tx_wecwaim(stwuct net_device *dev,
				stwuct bcmgenet_tx_wing *wing)
{
	unsigned int weweased;

	spin_wock_bh(&wing->wock);
	weweased = __bcmgenet_tx_wecwaim(dev, wing);
	spin_unwock_bh(&wing->wock);

	wetuwn weweased;
}

static int bcmgenet_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcmgenet_tx_wing *wing =
		containew_of(napi, stwuct bcmgenet_tx_wing, napi);
	unsigned int wowk_done = 0;
	stwuct netdev_queue *txq;

	spin_wock(&wing->wock);
	wowk_done = __bcmgenet_tx_wecwaim(wing->pwiv->dev, wing);
	if (wing->fwee_bds > (MAX_SKB_FWAGS + 1)) {
		txq = netdev_get_tx_queue(wing->pwiv->dev, wing->queue);
		netif_tx_wake_queue(txq);
	}
	spin_unwock(&wing->wock);

	if (wowk_done == 0) {
		napi_compwete(napi);
		wing->int_enabwe(wing);

		wetuwn 0;
	}

	wetuwn budget;
}

static void bcmgenet_tx_wecwaim_aww(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	if (netif_is_muwtiqueue(dev)) {
		fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++)
			bcmgenet_tx_wecwaim(dev, &pwiv->tx_wings[i]);
	}

	bcmgenet_tx_wecwaim(dev, &pwiv->tx_wings[DESC_INDEX]);
}

/* Weawwocate the SKB to put enough headwoom in fwont of it and insewt
 * the twansmit checksum offsets in the descwiptows
 */
static stwuct sk_buff *bcmgenet_add_tsb(stwuct net_device *dev,
					stwuct sk_buff *skb)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct status_64 *status = NUWW;
	stwuct sk_buff *new_skb;
	u16 offset;
	u8 ip_pwoto;
	__be16 ip_vew;
	u32 tx_csum_info;

	if (unwikewy(skb_headwoom(skb) < sizeof(*status))) {
		/* If 64 byte status bwock enabwed, must make suwe skb has
		 * enough headwoom fow us to insewt 64B status bwock.
		 */
		new_skb = skb_weawwoc_headwoom(skb, sizeof(*status));
		if (!new_skb) {
			dev_kfwee_skb_any(skb);
			pwiv->mib.tx_weawwoc_tsb_faiwed++;
			dev->stats.tx_dwopped++;
			wetuwn NUWW;
		}
		dev_consume_skb_any(skb);
		skb = new_skb;
		pwiv->mib.tx_weawwoc_tsb++;
	}

	skb_push(skb, sizeof(*status));
	status = (stwuct status_64 *)skb->data;

	if (skb->ip_summed  == CHECKSUM_PAWTIAW) {
		ip_vew = skb->pwotocow;
		switch (ip_vew) {
		case htons(ETH_P_IP):
			ip_pwoto = ip_hdw(skb)->pwotocow;
			bweak;
		case htons(ETH_P_IPV6):
			ip_pwoto = ipv6_hdw(skb)->nexthdw;
			bweak;
		defauwt:
			/* don't use UDP fwag */
			ip_pwoto = 0;
			bweak;
		}

		offset = skb_checksum_stawt_offset(skb) - sizeof(*status);
		tx_csum_info = (offset << STATUS_TX_CSUM_STAWT_SHIFT) |
				(offset + skb->csum_offset) |
				STATUS_TX_CSUM_WV;

		/* Set the speciaw UDP fwag fow UDP */
		if (ip_pwoto == IPPWOTO_UDP)
			tx_csum_info |= STATUS_TX_CSUM_PWOTO_UDP;

		status->tx_csum_info = tx_csum_info;
	}

	wetuwn skb;
}

static void bcmgenet_hide_tsb(stwuct sk_buff *skb)
{
	__skb_puww(skb, sizeof(stwuct status_64));
}

static netdev_tx_t bcmgenet_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct bcmgenet_tx_wing *wing = NUWW;
	stwuct enet_cb *tx_cb_ptw;
	stwuct netdev_queue *txq;
	int nw_fwags, index;
	dma_addw_t mapping;
	unsigned int size;
	skb_fwag_t *fwag;
	u32 wen_stat;
	int wet;
	int i;

	index = skb_get_queue_mapping(skb);
	/* Mapping stwategy:
	 * queue_mapping = 0, uncwassified, packet xmited thwough wing16
	 * queue_mapping = 1, goes to wing 0. (highest pwiowity queue
	 * queue_mapping = 2, goes to wing 1.
	 * queue_mapping = 3, goes to wing 2.
	 * queue_mapping = 4, goes to wing 3.
	 */
	if (index == 0)
		index = DESC_INDEX;
	ewse
		index -= 1;

	wing = &pwiv->tx_wings[index];
	txq = netdev_get_tx_queue(dev, wing->queue);

	nw_fwags = skb_shinfo(skb)->nw_fwags;

	spin_wock(&wing->wock);
	if (wing->fwee_bds <= (nw_fwags + 1)) {
		if (!netif_tx_queue_stopped(txq))
			netif_tx_stop_queue(txq);
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	/* Wetain how many bytes wiww be sent on the wiwe, without TSB insewted
	 * by twansmit checksum offwoad
	 */
	GENET_CB(skb)->bytes_sent = skb->wen;

	/* add the Twansmit Status Bwock */
	skb = bcmgenet_add_tsb(dev, skb);
	if (!skb) {
		wet = NETDEV_TX_OK;
		goto out;
	}

	fow (i = 0; i <= nw_fwags; i++) {
		tx_cb_ptw = bcmgenet_get_txcb(pwiv, wing);

		BUG_ON(!tx_cb_ptw);

		if (!i) {
			/* Twansmit singwe SKB ow head of fwagment wist */
			GENET_CB(skb)->fiwst_cb = tx_cb_ptw;
			size = skb_headwen(skb);
			mapping = dma_map_singwe(kdev, skb->data, size,
						 DMA_TO_DEVICE);
		} ewse {
			/* xmit fwagment */
			fwag = &skb_shinfo(skb)->fwags[i - 1];
			size = skb_fwag_size(fwag);
			mapping = skb_fwag_dma_map(kdev, fwag, 0, size,
						   DMA_TO_DEVICE);
		}

		wet = dma_mapping_ewwow(kdev, mapping);
		if (wet) {
			pwiv->mib.tx_dma_faiwed++;
			netif_eww(pwiv, tx_eww, dev, "Tx DMA map faiwed\n");
			wet = NETDEV_TX_OK;
			goto out_unmap_fwags;
		}
		dma_unmap_addw_set(tx_cb_ptw, dma_addw, mapping);
		dma_unmap_wen_set(tx_cb_ptw, dma_wen, size);

		tx_cb_ptw->skb = skb;

		wen_stat = (size << DMA_BUFWENGTH_SHIFT) |
			   (pwiv->hw_pawams->qtag_mask << DMA_TX_QTAG_SHIFT);

		/* Note: if we evew change fwom DMA_TX_APPEND_CWC bewow we
		 * wiww need to westowe softwawe padding of "wunt" packets
		 */
		wen_stat |= DMA_TX_APPEND_CWC;

		if (!i) {
			wen_stat |= DMA_SOP;
			if (skb->ip_summed == CHECKSUM_PAWTIAW)
				wen_stat |= DMA_TX_DO_CSUM;
		}
		if (i == nw_fwags)
			wen_stat |= DMA_EOP;

		dmadesc_set(pwiv, tx_cb_ptw->bd_addw, mapping, wen_stat);
	}

	GENET_CB(skb)->wast_cb = tx_cb_ptw;

	bcmgenet_hide_tsb(skb);
	skb_tx_timestamp(skb);

	/* Decwement totaw BD count and advance ouw wwite pointew */
	wing->fwee_bds -= nw_fwags + 1;
	wing->pwod_index += nw_fwags + 1;
	wing->pwod_index &= DMA_P_INDEX_MASK;

	netdev_tx_sent_queue(txq, GENET_CB(skb)->bytes_sent);

	if (wing->fwee_bds <= (MAX_SKB_FWAGS + 1))
		netif_tx_stop_queue(txq);

	if (!netdev_xmit_mowe() || netif_xmit_stopped(txq))
		/* Packets awe weady, update pwoducew index */
		bcmgenet_tdma_wing_wwitew(pwiv, wing->index,
					  wing->pwod_index, TDMA_PWOD_INDEX);
out:
	spin_unwock(&wing->wock);

	wetuwn wet;

out_unmap_fwags:
	/* Back up fow faiwed contwow bwock mapping */
	bcmgenet_put_txcb(pwiv, wing);

	/* Unmap successfuwwy mapped contwow bwocks */
	whiwe (i-- > 0) {
		tx_cb_ptw = bcmgenet_put_txcb(pwiv, wing);
		bcmgenet_fwee_tx_cb(kdev, tx_cb_ptw);
	}

	dev_kfwee_skb(skb);
	goto out;
}

static stwuct sk_buff *bcmgenet_wx_wefiww(stwuct bcmgenet_pwiv *pwiv,
					  stwuct enet_cb *cb)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	stwuct sk_buff *skb;
	stwuct sk_buff *wx_skb;
	dma_addw_t mapping;

	/* Awwocate a new Wx skb */
	skb = __netdev_awwoc_skb(pwiv->dev, pwiv->wx_buf_wen + SKB_AWIGNMENT,
				 GFP_ATOMIC | __GFP_NOWAWN);
	if (!skb) {
		pwiv->mib.awwoc_wx_buff_faiwed++;
		netif_eww(pwiv, wx_eww, pwiv->dev,
			  "%s: Wx skb awwocation faiwed\n", __func__);
		wetuwn NUWW;
	}

	/* DMA-map the new Wx skb */
	mapping = dma_map_singwe(kdev, skb->data, pwiv->wx_buf_wen,
				 DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(kdev, mapping)) {
		pwiv->mib.wx_dma_faiwed++;
		dev_kfwee_skb_any(skb);
		netif_eww(pwiv, wx_eww, pwiv->dev,
			  "%s: Wx skb DMA mapping faiwed\n", __func__);
		wetuwn NUWW;
	}

	/* Gwab the cuwwent Wx skb fwom the wing and DMA-unmap it */
	wx_skb = bcmgenet_fwee_wx_cb(kdev, cb);

	/* Put the new Wx skb on the wing */
	cb->skb = skb;
	dma_unmap_addw_set(cb, dma_addw, mapping);
	dma_unmap_wen_set(cb, dma_wen, pwiv->wx_buf_wen);
	dmadesc_set_addw(pwiv, cb->bd_addw, mapping);

	/* Wetuwn the cuwwent Wx skb to cawwew */
	wetuwn wx_skb;
}

/* bcmgenet_desc_wx - descwiptow based wx pwocess.
 * this couwd be cawwed fwom bottom hawf, ow fwom NAPI powwing method.
 */
static unsigned int bcmgenet_desc_wx(stwuct bcmgenet_wx_wing *wing,
				     unsigned int budget)
{
	stwuct bcmgenet_pwiv *pwiv = wing->pwiv;
	stwuct net_device *dev = pwiv->dev;
	stwuct enet_cb *cb;
	stwuct sk_buff *skb;
	u32 dma_wength_status;
	unsigned wong dma_fwag;
	int wen;
	unsigned int wxpktpwocessed = 0, wxpkttopwocess;
	unsigned int bytes_pwocessed = 0;
	unsigned int p_index, mask;
	unsigned int discawds;

	/* Cweaw status befowe sewvicing to weduce spuwious intewwupts */
	if (wing->index == DESC_INDEX) {
		bcmgenet_intww2_0_wwitew(pwiv, UMAC_IWQ_WXDMA_DONE,
					 INTWW2_CPU_CWEAW);
	} ewse {
		mask = 1 << (UMAC_IWQ1_WX_INTW_SHIFT + wing->index);
		bcmgenet_intww2_1_wwitew(pwiv,
					 mask,
					 INTWW2_CPU_CWEAW);
	}

	p_index = bcmgenet_wdma_wing_weadw(pwiv, wing->index, WDMA_PWOD_INDEX);

	discawds = (p_index >> DMA_P_INDEX_DISCAWD_CNT_SHIFT) &
		   DMA_P_INDEX_DISCAWD_CNT_MASK;
	if (discawds > wing->owd_discawds) {
		discawds = discawds - wing->owd_discawds;
		wing->ewwows += discawds;
		wing->owd_discawds += discawds;

		/* Cweaw HW wegistew when we weach 75% of maximum 0xFFFF */
		if (wing->owd_discawds >= 0xC000) {
			wing->owd_discawds = 0;
			bcmgenet_wdma_wing_wwitew(pwiv, wing->index, 0,
						  WDMA_PWOD_INDEX);
		}
	}

	p_index &= DMA_P_INDEX_MASK;
	wxpkttopwocess = (p_index - wing->c_index) & DMA_C_INDEX_MASK;

	netif_dbg(pwiv, wx_status, dev,
		  "WDMA: wxpkttopwocess=%d\n", wxpkttopwocess);

	whiwe ((wxpktpwocessed < wxpkttopwocess) &&
	       (wxpktpwocessed < budget)) {
		stwuct status_64 *status;
		__be16 wx_csum;

		cb = &pwiv->wx_cbs[wing->wead_ptw];
		skb = bcmgenet_wx_wefiww(pwiv, cb);

		if (unwikewy(!skb)) {
			wing->dwopped++;
			goto next;
		}

		status = (stwuct status_64 *)skb->data;
		dma_wength_status = status->wength_status;
		if (dev->featuwes & NETIF_F_WXCSUM) {
			wx_csum = (__fowce __be16)(status->wx_csum & 0xffff);
			if (wx_csum) {
				skb->csum = (__fowce __wsum)ntohs(wx_csum);
				skb->ip_summed = CHECKSUM_COMPWETE;
			}
		}

		/* DMA fwags and wength awe stiww vawid no mattew how
		 * we got the Weceive Status Vectow (64B WSB ow wegistew)
		 */
		dma_fwag = dma_wength_status & 0xffff;
		wen = dma_wength_status >> DMA_BUFWENGTH_SHIFT;

		netif_dbg(pwiv, wx_status, dev,
			  "%s:p_ind=%d c_ind=%d wead_ptw=%d wen_stat=0x%08x\n",
			  __func__, p_index, wing->c_index,
			  wing->wead_ptw, dma_wength_status);

		if (unwikewy(wen > WX_BUF_WENGTH)) {
			netif_eww(pwiv, wx_status, dev, "ovewsized packet\n");
			dev->stats.wx_wength_ewwows++;
			dev->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		if (unwikewy(!(dma_fwag & DMA_EOP) || !(dma_fwag & DMA_SOP))) {
			netif_eww(pwiv, wx_status, dev,
				  "dwopping fwagmented packet!\n");
			wing->ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		}

		/* wepowt ewwows */
		if (unwikewy(dma_fwag & (DMA_WX_CWC_EWWOW |
						DMA_WX_OV |
						DMA_WX_NO |
						DMA_WX_WG |
						DMA_WX_WXEW))) {
			netif_eww(pwiv, wx_status, dev, "dma_fwag=0x%x\n",
				  (unsigned int)dma_fwag);
			if (dma_fwag & DMA_WX_CWC_EWWOW)
				dev->stats.wx_cwc_ewwows++;
			if (dma_fwag & DMA_WX_OV)
				dev->stats.wx_ovew_ewwows++;
			if (dma_fwag & DMA_WX_NO)
				dev->stats.wx_fwame_ewwows++;
			if (dma_fwag & DMA_WX_WG)
				dev->stats.wx_wength_ewwows++;
			dev->stats.wx_ewwows++;
			dev_kfwee_skb_any(skb);
			goto next;
		} /* ewwow packet */

		skb_put(skb, wen);

		/* wemove WSB and hawdwawe 2bytes added fow IP awignment */
		skb_puww(skb, 66);
		wen -= 66;

		if (pwiv->cwc_fwd_en) {
			skb_twim(skb, wen - ETH_FCS_WEN);
			wen -= ETH_FCS_WEN;
		}

		bytes_pwocessed += wen;

		/*Finish setting up the weceived SKB and send it to the kewnew*/
		skb->pwotocow = eth_type_twans(skb, pwiv->dev);
		wing->packets++;
		wing->bytes += wen;
		if (dma_fwag & DMA_WX_MUWT)
			dev->stats.muwticast++;

		/* Notify kewnew */
		napi_gwo_weceive(&wing->napi, skb);
		netif_dbg(pwiv, wx_status, dev, "pushed up to kewnew\n");

next:
		wxpktpwocessed++;
		if (wikewy(wing->wead_ptw < wing->end_ptw))
			wing->wead_ptw++;
		ewse
			wing->wead_ptw = wing->cb_ptw;

		wing->c_index = (wing->c_index + 1) & DMA_C_INDEX_MASK;
		bcmgenet_wdma_wing_wwitew(pwiv, wing->index, wing->c_index, WDMA_CONS_INDEX);
	}

	wing->dim.bytes = bytes_pwocessed;
	wing->dim.packets = wxpktpwocessed;

	wetuwn wxpktpwocessed;
}

/* Wx NAPI powwing method */
static int bcmgenet_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcmgenet_wx_wing *wing = containew_of(napi,
			stwuct bcmgenet_wx_wing, napi);
	stwuct dim_sampwe dim_sampwe = {};
	unsigned int wowk_done;

	wowk_done = bcmgenet_desc_wx(wing, budget);

	if (wowk_done < budget) {
		napi_compwete_done(napi, wowk_done);
		wing->int_enabwe(wing);
	}

	if (wing->dim.use_dim) {
		dim_update_sampwe(wing->dim.event_ctw, wing->dim.packets,
				  wing->dim.bytes, &dim_sampwe);
		net_dim(&wing->dim.dim, dim_sampwe);
	}

	wetuwn wowk_done;
}

static void bcmgenet_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct bcmgenet_net_dim *ndim =
			containew_of(dim, stwuct bcmgenet_net_dim, dim);
	stwuct bcmgenet_wx_wing *wing =
			containew_of(ndim, stwuct bcmgenet_wx_wing, dim);
	stwuct dim_cq_modew cuw_pwofiwe =
			net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);

	bcmgenet_set_wx_coawesce(wing, cuw_pwofiwe.usec, cuw_pwofiwe.pkts);
	dim->state = DIM_STAWT_MEASUWE;
}

/* Assign skb to WX DMA descwiptow. */
static int bcmgenet_awwoc_wx_buffews(stwuct bcmgenet_pwiv *pwiv,
				     stwuct bcmgenet_wx_wing *wing)
{
	stwuct enet_cb *cb;
	stwuct sk_buff *skb;
	int i;

	netif_dbg(pwiv, hw, pwiv->dev, "%s\n", __func__);

	/* woop hewe fow each buffew needing assign */
	fow (i = 0; i < wing->size; i++) {
		cb = wing->cbs + i;
		skb = bcmgenet_wx_wefiww(pwiv, cb);
		if (skb)
			dev_consume_skb_any(skb);
		if (!cb->skb)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void bcmgenet_fwee_wx_buffews(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct sk_buff *skb;
	stwuct enet_cb *cb;
	int i;

	fow (i = 0; i < pwiv->num_wx_bds; i++) {
		cb = &pwiv->wx_cbs[i];

		skb = bcmgenet_fwee_wx_cb(&pwiv->pdev->dev, cb);
		if (skb)
			dev_consume_skb_any(skb);
	}
}

static void umac_enabwe_set(stwuct bcmgenet_pwiv *pwiv, u32 mask, boow enabwe)
{
	u32 weg;

	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	if (weg & CMD_SW_WESET)
		wetuwn;
	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);

	/* UniMAC stops on a packet boundawy, wait fow a fuww-size packet
	 * to be pwocessed
	 */
	if (enabwe == 0)
		usweep_wange(1000, 2000);
}

static void weset_umac(stwuct bcmgenet_pwiv *pwiv)
{
	/* 7358a0/7552a0: bad defauwt in WBUF_FWUSH_CTWW.umac_sw_wst */
	bcmgenet_wbuf_ctww_set(pwiv, 0);
	udeway(10);

	/* issue soft weset and disabwe MAC whiwe updating its wegistews */
	bcmgenet_umac_wwitew(pwiv, CMD_SW_WESET, UMAC_CMD);
	udeway(2);
}

static void bcmgenet_intw_disabwe(stwuct bcmgenet_pwiv *pwiv)
{
	/* Mask aww intewwupts.*/
	bcmgenet_intww2_0_wwitew(pwiv, 0xFFFFFFFF, INTWW2_CPU_MASK_SET);
	bcmgenet_intww2_0_wwitew(pwiv, 0xFFFFFFFF, INTWW2_CPU_CWEAW);
	bcmgenet_intww2_1_wwitew(pwiv, 0xFFFFFFFF, INTWW2_CPU_MASK_SET);
	bcmgenet_intww2_1_wwitew(pwiv, 0xFFFFFFFF, INTWW2_CPU_CWEAW);
}

static void bcmgenet_wink_intw_enabwe(stwuct bcmgenet_pwiv *pwiv)
{
	u32 int0_enabwe = 0;

	/* Monitow cabwe pwug/unpwugged event fow intewnaw PHY, extewnaw PHY
	 * and MoCA PHY
	 */
	if (pwiv->intewnaw_phy) {
		int0_enabwe |= UMAC_IWQ_WINK_EVENT;
		if (GENET_IS_V1(pwiv) || GENET_IS_V2(pwiv) || GENET_IS_V3(pwiv))
			int0_enabwe |= UMAC_IWQ_PHY_DET_W;
	} ewse if (pwiv->ext_phy) {
		int0_enabwe |= UMAC_IWQ_WINK_EVENT;
	} ewse if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_MOCA) {
		if (pwiv->hw_pawams->fwags & GENET_HAS_MOCA_WINK_DET)
			int0_enabwe |= UMAC_IWQ_WINK_EVENT;
	}
	bcmgenet_intww2_0_wwitew(pwiv, int0_enabwe, INTWW2_CPU_MASK_CWEAW);
}

static void init_umac(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct device *kdev = &pwiv->pdev->dev;
	u32 weg;
	u32 int0_enabwe = 0;

	dev_dbg(&pwiv->pdev->dev, "bcmgenet: init_umac\n");

	weset_umac(pwiv);

	/* cweaw tx/wx countew */
	bcmgenet_umac_wwitew(pwiv,
			     MIB_WESET_WX | MIB_WESET_TX | MIB_WESET_WUNT,
			     UMAC_MIB_CTWW);
	bcmgenet_umac_wwitew(pwiv, 0, UMAC_MIB_CTWW);

	bcmgenet_umac_wwitew(pwiv, ENET_MAX_MTU_SIZE, UMAC_MAX_FWAME_WEN);

	/* init tx wegistews, enabwe TSB */
	weg = bcmgenet_tbuf_ctww_get(pwiv);
	weg |= TBUF_64B_EN;
	bcmgenet_tbuf_ctww_set(pwiv, weg);

	/* init wx wegistews, enabwe ip headew optimization and WSB */
	weg = bcmgenet_wbuf_weadw(pwiv, WBUF_CTWW);
	weg |= WBUF_AWIGN_2B | WBUF_64B_EN;
	bcmgenet_wbuf_wwitew(pwiv, weg, WBUF_CTWW);

	/* enabwe wx checksumming */
	weg = bcmgenet_wbuf_weadw(pwiv, WBUF_CHK_CTWW);
	weg |= WBUF_WXCHK_EN | WBUF_W3_PAWSE_DIS;
	/* If UniMAC fowwawds CWC, we need to skip ovew it to get
	 * a vawid CHK bit to be set in the pew-packet status wowd
	 */
	if (pwiv->cwc_fwd_en)
		weg |= WBUF_SKIP_FCS;
	ewse
		weg &= ~WBUF_SKIP_FCS;
	bcmgenet_wbuf_wwitew(pwiv, weg, WBUF_CHK_CTWW);

	if (!GENET_IS_V1(pwiv) && !GENET_IS_V2(pwiv))
		bcmgenet_wbuf_wwitew(pwiv, 1, WBUF_TBUF_SIZE_CTWW);

	bcmgenet_intw_disabwe(pwiv);

	/* Configuwe backpwessuwe vectows fow MoCA */
	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_MOCA) {
		weg = bcmgenet_bp_mc_get(pwiv);
		weg |= BIT(pwiv->hw_pawams->bp_in_en_shift);

		/* bp_mask: back pwessuwe mask */
		if (netif_is_muwtiqueue(pwiv->dev))
			weg |= pwiv->hw_pawams->bp_in_mask;
		ewse
			weg &= ~pwiv->hw_pawams->bp_in_mask;
		bcmgenet_bp_mc_set(pwiv, weg);
	}

	/* Enabwe MDIO intewwupts on GENET v3+ */
	if (pwiv->hw_pawams->fwags & GENET_HAS_MDIO_INTW)
		int0_enabwe |= (UMAC_IWQ_MDIO_DONE | UMAC_IWQ_MDIO_EWWOW);

	bcmgenet_intww2_0_wwitew(pwiv, int0_enabwe, INTWW2_CPU_MASK_CWEAW);

	dev_dbg(kdev, "done init umac\n");
}

static void bcmgenet_init_dim(stwuct bcmgenet_wx_wing *wing,
			      void (*cb)(stwuct wowk_stwuct *wowk))
{
	stwuct bcmgenet_net_dim *dim = &wing->dim;

	INIT_WOWK(&dim->dim.wowk, cb);
	dim->dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	dim->event_ctw = 0;
	dim->packets = 0;
	dim->bytes = 0;
}

static void bcmgenet_init_wx_coawesce(stwuct bcmgenet_wx_wing *wing)
{
	stwuct bcmgenet_net_dim *dim = &wing->dim;
	stwuct dim_cq_modew modew;
	u32 usecs, pkts;

	usecs = wing->wx_coawesce_usecs;
	pkts = wing->wx_max_coawesced_fwames;

	/* If DIM was enabwed, we-appwy defauwt pawametews */
	if (dim->use_dim) {
		modew = net_dim_get_def_wx_modewation(dim->dim.mode);
		usecs = modew.usec;
		pkts = modew.pkts;
	}

	bcmgenet_set_wx_coawesce(wing, usecs, pkts);
}

/* Initiawize a Tx wing awong with cowwesponding hawdwawe wegistews */
static void bcmgenet_init_tx_wing(stwuct bcmgenet_pwiv *pwiv,
				  unsigned int index, unsigned int size,
				  unsigned int stawt_ptw, unsigned int end_ptw)
{
	stwuct bcmgenet_tx_wing *wing = &pwiv->tx_wings[index];
	u32 wowds_pew_bd = WOWDS_PEW_BD(pwiv);
	u32 fwow_pewiod_vaw = 0;

	spin_wock_init(&wing->wock);
	wing->pwiv = pwiv;
	wing->index = index;
	if (index == DESC_INDEX) {
		wing->queue = 0;
		wing->int_enabwe = bcmgenet_tx_wing16_int_enabwe;
		wing->int_disabwe = bcmgenet_tx_wing16_int_disabwe;
	} ewse {
		wing->queue = index + 1;
		wing->int_enabwe = bcmgenet_tx_wing_int_enabwe;
		wing->int_disabwe = bcmgenet_tx_wing_int_disabwe;
	}
	wing->cbs = pwiv->tx_cbs + stawt_ptw;
	wing->size = size;
	wing->cwean_ptw = stawt_ptw;
	wing->c_index = 0;
	wing->fwee_bds = size;
	wing->wwite_ptw = stawt_ptw;
	wing->cb_ptw = stawt_ptw;
	wing->end_ptw = end_ptw - 1;
	wing->pwod_index = 0;

	/* Set fwow pewiod fow wing != 16 */
	if (index != DESC_INDEX)
		fwow_pewiod_vaw = ENET_MAX_MTU_SIZE << 16;

	bcmgenet_tdma_wing_wwitew(pwiv, index, 0, TDMA_PWOD_INDEX);
	bcmgenet_tdma_wing_wwitew(pwiv, index, 0, TDMA_CONS_INDEX);
	bcmgenet_tdma_wing_wwitew(pwiv, index, 1, DMA_MBUF_DONE_THWESH);
	/* Disabwe wate contwow fow now */
	bcmgenet_tdma_wing_wwitew(pwiv, index, fwow_pewiod_vaw,
				  TDMA_FWOW_PEWIOD);
	bcmgenet_tdma_wing_wwitew(pwiv, index,
				  ((size << DMA_WING_SIZE_SHIFT) |
				   WX_BUF_WENGTH), DMA_WING_BUF_SIZE);

	/* Set stawt and end addwess, wead and wwite pointews */
	bcmgenet_tdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  DMA_STAWT_ADDW);
	bcmgenet_tdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  TDMA_WEAD_PTW);
	bcmgenet_tdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  TDMA_WWITE_PTW);
	bcmgenet_tdma_wing_wwitew(pwiv, index, end_ptw * wowds_pew_bd - 1,
				  DMA_END_ADDW);

	/* Initiawize Tx NAPI */
	netif_napi_add_tx(pwiv->dev, &wing->napi, bcmgenet_tx_poww);
}

/* Initiawize a WDMA wing */
static int bcmgenet_init_wx_wing(stwuct bcmgenet_pwiv *pwiv,
				 unsigned int index, unsigned int size,
				 unsigned int stawt_ptw, unsigned int end_ptw)
{
	stwuct bcmgenet_wx_wing *wing = &pwiv->wx_wings[index];
	u32 wowds_pew_bd = WOWDS_PEW_BD(pwiv);
	int wet;

	wing->pwiv = pwiv;
	wing->index = index;
	if (index == DESC_INDEX) {
		wing->int_enabwe = bcmgenet_wx_wing16_int_enabwe;
		wing->int_disabwe = bcmgenet_wx_wing16_int_disabwe;
	} ewse {
		wing->int_enabwe = bcmgenet_wx_wing_int_enabwe;
		wing->int_disabwe = bcmgenet_wx_wing_int_disabwe;
	}
	wing->cbs = pwiv->wx_cbs + stawt_ptw;
	wing->size = size;
	wing->c_index = 0;
	wing->wead_ptw = stawt_ptw;
	wing->cb_ptw = stawt_ptw;
	wing->end_ptw = end_ptw - 1;

	wet = bcmgenet_awwoc_wx_buffews(pwiv, wing);
	if (wet)
		wetuwn wet;

	bcmgenet_init_dim(wing, bcmgenet_dim_wowk);
	bcmgenet_init_wx_coawesce(wing);

	/* Initiawize Wx NAPI */
	netif_napi_add(pwiv->dev, &wing->napi, bcmgenet_wx_poww);

	bcmgenet_wdma_wing_wwitew(pwiv, index, 0, WDMA_PWOD_INDEX);
	bcmgenet_wdma_wing_wwitew(pwiv, index, 0, WDMA_CONS_INDEX);
	bcmgenet_wdma_wing_wwitew(pwiv, index,
				  ((size << DMA_WING_SIZE_SHIFT) |
				   WX_BUF_WENGTH), DMA_WING_BUF_SIZE);
	bcmgenet_wdma_wing_wwitew(pwiv, index,
				  (DMA_FC_THWESH_WO <<
				   DMA_XOFF_THWESHOWD_SHIFT) |
				   DMA_FC_THWESH_HI, WDMA_XON_XOFF_THWESH);

	/* Set stawt and end addwess, wead and wwite pointews */
	bcmgenet_wdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  DMA_STAWT_ADDW);
	bcmgenet_wdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  WDMA_WEAD_PTW);
	bcmgenet_wdma_wing_wwitew(pwiv, index, stawt_ptw * wowds_pew_bd,
				  WDMA_WWITE_PTW);
	bcmgenet_wdma_wing_wwitew(pwiv, index, end_ptw * wowds_pew_bd - 1,
				  DMA_END_ADDW);

	wetuwn wet;
}

static void bcmgenet_enabwe_tx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_tx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->tx_queues; ++i) {
		wing = &pwiv->tx_wings[i];
		napi_enabwe(&wing->napi);
		wing->int_enabwe(wing);
	}

	wing = &pwiv->tx_wings[DESC_INDEX];
	napi_enabwe(&wing->napi);
	wing->int_enabwe(wing);
}

static void bcmgenet_disabwe_tx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_tx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->tx_queues; ++i) {
		wing = &pwiv->tx_wings[i];
		napi_disabwe(&wing->napi);
	}

	wing = &pwiv->tx_wings[DESC_INDEX];
	napi_disabwe(&wing->napi);
}

static void bcmgenet_fini_tx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_tx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->tx_queues; ++i) {
		wing = &pwiv->tx_wings[i];
		netif_napi_dew(&wing->napi);
	}

	wing = &pwiv->tx_wings[DESC_INDEX];
	netif_napi_dew(&wing->napi);
}

/* Initiawize Tx queues
 *
 * Queues 0-3 awe pwiowity-based, each one has 32 descwiptows,
 * with queue 0 being the highest pwiowity queue.
 *
 * Queue 16 is the defauwt Tx queue with
 * GENET_Q16_TX_BD_CNT = 256 - 4 * 32 = 128 descwiptows.
 *
 * The twansmit contwow bwock poow is then pawtitioned as fowwows:
 * - Tx queue 0 uses tx_cbs[0..31]
 * - Tx queue 1 uses tx_cbs[32..63]
 * - Tx queue 2 uses tx_cbs[64..95]
 * - Tx queue 3 uses tx_cbs[96..127]
 * - Tx queue 16 uses tx_cbs[128..255]
 */
static void bcmgenet_init_tx_queues(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 i, dma_enabwe;
	u32 dma_ctww, wing_cfg;
	u32 dma_pwiowity[3] = {0, 0, 0};

	dma_ctww = bcmgenet_tdma_weadw(pwiv, DMA_CTWW);
	dma_enabwe = dma_ctww & DMA_EN;
	dma_ctww &= ~DMA_EN;
	bcmgenet_tdma_wwitew(pwiv, dma_ctww, DMA_CTWW);

	dma_ctww = 0;
	wing_cfg = 0;

	/* Enabwe stwict pwiowity awbitew mode */
	bcmgenet_tdma_wwitew(pwiv, DMA_AWBITEW_SP, DMA_AWB_CTWW);

	/* Initiawize Tx pwiowity queues */
	fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++) {
		bcmgenet_init_tx_wing(pwiv, i, pwiv->hw_pawams->tx_bds_pew_q,
				      i * pwiv->hw_pawams->tx_bds_pew_q,
				      (i + 1) * pwiv->hw_pawams->tx_bds_pew_q);
		wing_cfg |= (1 << i);
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
		dma_pwiowity[DMA_PWIO_WEG_INDEX(i)] |=
			((GENET_Q0_PWIOWITY + i) << DMA_PWIO_WEG_SHIFT(i));
	}

	/* Initiawize Tx defauwt queue 16 */
	bcmgenet_init_tx_wing(pwiv, DESC_INDEX, GENET_Q16_TX_BD_CNT,
			      pwiv->hw_pawams->tx_queues *
			      pwiv->hw_pawams->tx_bds_pew_q,
			      TOTAW_DESC);
	wing_cfg |= (1 << DESC_INDEX);
	dma_ctww |= (1 << (DESC_INDEX + DMA_WING_BUF_EN_SHIFT));
	dma_pwiowity[DMA_PWIO_WEG_INDEX(DESC_INDEX)] |=
		((GENET_Q0_PWIOWITY + pwiv->hw_pawams->tx_queues) <<
		 DMA_PWIO_WEG_SHIFT(DESC_INDEX));

	/* Set Tx queue pwiowities */
	bcmgenet_tdma_wwitew(pwiv, dma_pwiowity[0], DMA_PWIOWITY_0);
	bcmgenet_tdma_wwitew(pwiv, dma_pwiowity[1], DMA_PWIOWITY_1);
	bcmgenet_tdma_wwitew(pwiv, dma_pwiowity[2], DMA_PWIOWITY_2);

	/* Enabwe Tx queues */
	bcmgenet_tdma_wwitew(pwiv, wing_cfg, DMA_WING_CFG);

	/* Enabwe Tx DMA */
	if (dma_enabwe)
		dma_ctww |= DMA_EN;
	bcmgenet_tdma_wwitew(pwiv, dma_ctww, DMA_CTWW);
}

static void bcmgenet_enabwe_wx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_wx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->wx_queues; ++i) {
		wing = &pwiv->wx_wings[i];
		napi_enabwe(&wing->napi);
		wing->int_enabwe(wing);
	}

	wing = &pwiv->wx_wings[DESC_INDEX];
	napi_enabwe(&wing->napi);
	wing->int_enabwe(wing);
}

static void bcmgenet_disabwe_wx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_wx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->wx_queues; ++i) {
		wing = &pwiv->wx_wings[i];
		napi_disabwe(&wing->napi);
		cancew_wowk_sync(&wing->dim.dim.wowk);
	}

	wing = &pwiv->wx_wings[DESC_INDEX];
	napi_disabwe(&wing->napi);
	cancew_wowk_sync(&wing->dim.dim.wowk);
}

static void bcmgenet_fini_wx_napi(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	stwuct bcmgenet_wx_wing *wing;

	fow (i = 0; i < pwiv->hw_pawams->wx_queues; ++i) {
		wing = &pwiv->wx_wings[i];
		netif_napi_dew(&wing->napi);
	}

	wing = &pwiv->wx_wings[DESC_INDEX];
	netif_napi_dew(&wing->napi);
}

/* Initiawize Wx queues
 *
 * Queues 0-15 awe pwiowity queues. Hawdwawe Fiwtewing Bwock (HFB) can be
 * used to diwect twaffic to these queues.
 *
 * Queue 16 is the defauwt Wx queue with GENET_Q16_WX_BD_CNT descwiptows.
 */
static int bcmgenet_init_wx_queues(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 i;
	u32 dma_enabwe;
	u32 dma_ctww;
	u32 wing_cfg;
	int wet;

	dma_ctww = bcmgenet_wdma_weadw(pwiv, DMA_CTWW);
	dma_enabwe = dma_ctww & DMA_EN;
	dma_ctww &= ~DMA_EN;
	bcmgenet_wdma_wwitew(pwiv, dma_ctww, DMA_CTWW);

	dma_ctww = 0;
	wing_cfg = 0;

	/* Initiawize Wx pwiowity queues */
	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++) {
		wet = bcmgenet_init_wx_wing(pwiv, i,
					    pwiv->hw_pawams->wx_bds_pew_q,
					    i * pwiv->hw_pawams->wx_bds_pew_q,
					    (i + 1) *
					    pwiv->hw_pawams->wx_bds_pew_q);
		if (wet)
			wetuwn wet;

		wing_cfg |= (1 << i);
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
	}

	/* Initiawize Wx defauwt queue 16 */
	wet = bcmgenet_init_wx_wing(pwiv, DESC_INDEX, GENET_Q16_WX_BD_CNT,
				    pwiv->hw_pawams->wx_queues *
				    pwiv->hw_pawams->wx_bds_pew_q,
				    TOTAW_DESC);
	if (wet)
		wetuwn wet;

	wing_cfg |= (1 << DESC_INDEX);
	dma_ctww |= (1 << (DESC_INDEX + DMA_WING_BUF_EN_SHIFT));

	/* Enabwe wings */
	bcmgenet_wdma_wwitew(pwiv, wing_cfg, DMA_WING_CFG);

	/* Configuwe wing as descwiptow wing and we-enabwe DMA if enabwed */
	if (dma_enabwe)
		dma_ctww |= DMA_EN;
	bcmgenet_wdma_wwitew(pwiv, dma_ctww, DMA_CTWW);

	wetuwn 0;
}

static int bcmgenet_dma_teawdown(stwuct bcmgenet_pwiv *pwiv)
{
	int wet = 0;
	int timeout = 0;
	u32 weg;
	u32 dma_ctww;
	int i;

	/* Disabwe TDMA to stop add mowe fwames in TX DMA */
	weg = bcmgenet_tdma_weadw(pwiv, DMA_CTWW);
	weg &= ~DMA_EN;
	bcmgenet_tdma_wwitew(pwiv, weg, DMA_CTWW);

	/* Check TDMA status wegistew to confiwm TDMA is disabwed */
	whiwe (timeout++ < DMA_TIMEOUT_VAW) {
		weg = bcmgenet_tdma_weadw(pwiv, DMA_STATUS);
		if (weg & DMA_DISABWED)
			bweak;

		udeway(1);
	}

	if (timeout == DMA_TIMEOUT_VAW) {
		netdev_wawn(pwiv->dev, "Timed out whiwe disabwing TX DMA\n");
		wet = -ETIMEDOUT;
	}

	/* Wait 10ms fow packet dwain in both tx and wx dma */
	usweep_wange(10000, 20000);

	/* Disabwe WDMA */
	weg = bcmgenet_wdma_weadw(pwiv, DMA_CTWW);
	weg &= ~DMA_EN;
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_CTWW);

	timeout = 0;
	/* Check WDMA status wegistew to confiwm WDMA is disabwed */
	whiwe (timeout++ < DMA_TIMEOUT_VAW) {
		weg = bcmgenet_wdma_weadw(pwiv, DMA_STATUS);
		if (weg & DMA_DISABWED)
			bweak;

		udeway(1);
	}

	if (timeout == DMA_TIMEOUT_VAW) {
		netdev_wawn(pwiv->dev, "Timed out whiwe disabwing WX DMA\n");
		wet = -ETIMEDOUT;
	}

	dma_ctww = 0;
	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++)
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
	weg = bcmgenet_wdma_weadw(pwiv, DMA_CTWW);
	weg &= ~dma_ctww;
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_CTWW);

	dma_ctww = 0;
	fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++)
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
	weg = bcmgenet_tdma_weadw(pwiv, DMA_CTWW);
	weg &= ~dma_ctww;
	bcmgenet_tdma_wwitew(pwiv, weg, DMA_CTWW);

	wetuwn wet;
}

static void bcmgenet_fini_dma(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct netdev_queue *txq;
	int i;

	bcmgenet_fini_wx_napi(pwiv);
	bcmgenet_fini_tx_napi(pwiv);

	fow (i = 0; i < pwiv->num_tx_bds; i++)
		dev_kfwee_skb(bcmgenet_fwee_tx_cb(&pwiv->pdev->dev,
						  pwiv->tx_cbs + i));

	fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++) {
		txq = netdev_get_tx_queue(pwiv->dev, pwiv->tx_wings[i].queue);
		netdev_tx_weset_queue(txq);
	}

	txq = netdev_get_tx_queue(pwiv->dev, pwiv->tx_wings[DESC_INDEX].queue);
	netdev_tx_weset_queue(txq);

	bcmgenet_fwee_wx_buffews(pwiv);
	kfwee(pwiv->wx_cbs);
	kfwee(pwiv->tx_cbs);
}

/* init_edma: Initiawize DMA contwow wegistew */
static int bcmgenet_init_dma(stwuct bcmgenet_pwiv *pwiv)
{
	int wet;
	unsigned int i;
	stwuct enet_cb *cb;

	netif_dbg(pwiv, hw, pwiv->dev, "%s\n", __func__);

	/* Initiawize common Wx wing stwuctuwes */
	pwiv->wx_bds = pwiv->base + pwiv->hw_pawams->wdma_offset;
	pwiv->num_wx_bds = TOTAW_DESC;
	pwiv->wx_cbs = kcawwoc(pwiv->num_wx_bds, sizeof(stwuct enet_cb),
			       GFP_KEWNEW);
	if (!pwiv->wx_cbs)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->num_wx_bds; i++) {
		cb = pwiv->wx_cbs + i;
		cb->bd_addw = pwiv->wx_bds + i * DMA_DESC_SIZE;
	}

	/* Initiawize common TX wing stwuctuwes */
	pwiv->tx_bds = pwiv->base + pwiv->hw_pawams->tdma_offset;
	pwiv->num_tx_bds = TOTAW_DESC;
	pwiv->tx_cbs = kcawwoc(pwiv->num_tx_bds, sizeof(stwuct enet_cb),
			       GFP_KEWNEW);
	if (!pwiv->tx_cbs) {
		kfwee(pwiv->wx_cbs);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < pwiv->num_tx_bds; i++) {
		cb = pwiv->tx_cbs + i;
		cb->bd_addw = pwiv->tx_bds + i * DMA_DESC_SIZE;
	}

	/* Init wDma */
	bcmgenet_wdma_wwitew(pwiv, pwiv->dma_max_buwst_wength,
			     DMA_SCB_BUWST_SIZE);

	/* Initiawize Wx queues */
	wet = bcmgenet_init_wx_queues(pwiv->dev);
	if (wet) {
		netdev_eww(pwiv->dev, "faiwed to initiawize Wx queues\n");
		bcmgenet_fwee_wx_buffews(pwiv);
		kfwee(pwiv->wx_cbs);
		kfwee(pwiv->tx_cbs);
		wetuwn wet;
	}

	/* Init tDma */
	bcmgenet_tdma_wwitew(pwiv, pwiv->dma_max_buwst_wength,
			     DMA_SCB_BUWST_SIZE);

	/* Initiawize Tx queues */
	bcmgenet_init_tx_queues(pwiv->dev);

	wetuwn 0;
}

/* Intewwupt bottom hawf */
static void bcmgenet_iwq_task(stwuct wowk_stwuct *wowk)
{
	unsigned int status;
	stwuct bcmgenet_pwiv *pwiv = containew_of(
			wowk, stwuct bcmgenet_pwiv, bcmgenet_iwq_wowk);

	netif_dbg(pwiv, intw, pwiv->dev, "%s\n", __func__);

	spin_wock_iwq(&pwiv->wock);
	status = pwiv->iwq0_stat;
	pwiv->iwq0_stat = 0;
	spin_unwock_iwq(&pwiv->wock);

	if (status & UMAC_IWQ_PHY_DET_W &&
	    pwiv->dev->phydev->autoneg != AUTONEG_ENABWE) {
		phy_init_hw(pwiv->dev->phydev);
		genphy_config_aneg(pwiv->dev->phydev);
	}

	/* Wink UP/DOWN event */
	if (status & UMAC_IWQ_WINK_EVENT)
		phy_mac_intewwupt(pwiv->dev->phydev);

}

/* bcmgenet_isw1: handwe Wx and Tx pwiowity queues */
static iwqwetuwn_t bcmgenet_isw1(int iwq, void *dev_id)
{
	stwuct bcmgenet_pwiv *pwiv = dev_id;
	stwuct bcmgenet_wx_wing *wx_wing;
	stwuct bcmgenet_tx_wing *tx_wing;
	unsigned int index, status;

	/* Wead iwq status */
	status = bcmgenet_intww2_1_weadw(pwiv, INTWW2_CPU_STAT) &
		~bcmgenet_intww2_1_weadw(pwiv, INTWW2_CPU_MASK_STATUS);

	/* cweaw intewwupts */
	bcmgenet_intww2_1_wwitew(pwiv, status, INTWW2_CPU_CWEAW);

	netif_dbg(pwiv, intw, pwiv->dev,
		  "%s: IWQ=0x%x\n", __func__, status);

	/* Check Wx pwiowity queue intewwupts */
	fow (index = 0; index < pwiv->hw_pawams->wx_queues; index++) {
		if (!(status & BIT(UMAC_IWQ1_WX_INTW_SHIFT + index)))
			continue;

		wx_wing = &pwiv->wx_wings[index];
		wx_wing->dim.event_ctw++;

		if (wikewy(napi_scheduwe_pwep(&wx_wing->napi))) {
			wx_wing->int_disabwe(wx_wing);
			__napi_scheduwe_iwqoff(&wx_wing->napi);
		}
	}

	/* Check Tx pwiowity queue intewwupts */
	fow (index = 0; index < pwiv->hw_pawams->tx_queues; index++) {
		if (!(status & BIT(index)))
			continue;

		tx_wing = &pwiv->tx_wings[index];

		if (wikewy(napi_scheduwe_pwep(&tx_wing->napi))) {
			tx_wing->int_disabwe(tx_wing);
			__napi_scheduwe_iwqoff(&tx_wing->napi);
		}
	}

	wetuwn IWQ_HANDWED;
}

/* bcmgenet_isw0: handwe Wx and Tx defauwt queues + othew stuff */
static iwqwetuwn_t bcmgenet_isw0(int iwq, void *dev_id)
{
	stwuct bcmgenet_pwiv *pwiv = dev_id;
	stwuct bcmgenet_wx_wing *wx_wing;
	stwuct bcmgenet_tx_wing *tx_wing;
	unsigned int status;
	unsigned wong fwags;

	/* Wead iwq status */
	status = bcmgenet_intww2_0_weadw(pwiv, INTWW2_CPU_STAT) &
		~bcmgenet_intww2_0_weadw(pwiv, INTWW2_CPU_MASK_STATUS);

	/* cweaw intewwupts */
	bcmgenet_intww2_0_wwitew(pwiv, status, INTWW2_CPU_CWEAW);

	netif_dbg(pwiv, intw, pwiv->dev,
		  "IWQ=0x%x\n", status);

	if (status & UMAC_IWQ_WXDMA_DONE) {
		wx_wing = &pwiv->wx_wings[DESC_INDEX];
		wx_wing->dim.event_ctw++;

		if (wikewy(napi_scheduwe_pwep(&wx_wing->napi))) {
			wx_wing->int_disabwe(wx_wing);
			__napi_scheduwe_iwqoff(&wx_wing->napi);
		}
	}

	if (status & UMAC_IWQ_TXDMA_DONE) {
		tx_wing = &pwiv->tx_wings[DESC_INDEX];

		if (wikewy(napi_scheduwe_pwep(&tx_wing->napi))) {
			tx_wing->int_disabwe(tx_wing);
			__napi_scheduwe_iwqoff(&tx_wing->napi);
		}
	}

	if ((pwiv->hw_pawams->fwags & GENET_HAS_MDIO_INTW) &&
		status & (UMAC_IWQ_MDIO_DONE | UMAC_IWQ_MDIO_EWWOW)) {
		wake_up(&pwiv->wq);
	}

	/* aww othew intewested intewwupts handwed in bottom hawf */
	status &= (UMAC_IWQ_WINK_EVENT | UMAC_IWQ_PHY_DET_W);
	if (status) {
		/* Save iwq status fow bottom-hawf pwocessing. */
		spin_wock_iwqsave(&pwiv->wock, fwags);
		pwiv->iwq0_stat |= status;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);

		scheduwe_wowk(&pwiv->bcmgenet_iwq_wowk);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bcmgenet_wow_isw(int iwq, void *dev_id)
{
	/* Acknowwedge the intewwupt */
	wetuwn IWQ_HANDWED;
}

static void bcmgenet_umac_weset(stwuct bcmgenet_pwiv *pwiv)
{
	u32 weg;

	weg = bcmgenet_wbuf_ctww_get(pwiv);
	weg |= BIT(1);
	bcmgenet_wbuf_ctww_set(pwiv, weg);
	udeway(10);

	weg &= ~BIT(1);
	bcmgenet_wbuf_ctww_set(pwiv, weg);
	udeway(10);
}

static void bcmgenet_set_hw_addw(stwuct bcmgenet_pwiv *pwiv,
				 const unsigned chaw *addw)
{
	bcmgenet_umac_wwitew(pwiv, get_unawigned_be32(&addw[0]), UMAC_MAC0);
	bcmgenet_umac_wwitew(pwiv, get_unawigned_be16(&addw[4]), UMAC_MAC1);
}

static void bcmgenet_get_hw_addw(stwuct bcmgenet_pwiv *pwiv,
				 unsigned chaw *addw)
{
	u32 addw_tmp;

	addw_tmp = bcmgenet_umac_weadw(pwiv, UMAC_MAC0);
	put_unawigned_be32(addw_tmp, &addw[0]);
	addw_tmp = bcmgenet_umac_weadw(pwiv, UMAC_MAC1);
	put_unawigned_be16(addw_tmp, &addw[4]);
}

/* Wetuwns a weusabwe dma contwow wegistew vawue */
static u32 bcmgenet_dma_disabwe(stwuct bcmgenet_pwiv *pwiv)
{
	unsigned int i;
	u32 weg;
	u32 dma_ctww;

	/* disabwe DMA */
	dma_ctww = 1 << (DESC_INDEX + DMA_WING_BUF_EN_SHIFT) | DMA_EN;
	fow (i = 0; i < pwiv->hw_pawams->tx_queues; i++)
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
	weg = bcmgenet_tdma_weadw(pwiv, DMA_CTWW);
	weg &= ~dma_ctww;
	bcmgenet_tdma_wwitew(pwiv, weg, DMA_CTWW);

	dma_ctww = 1 << (DESC_INDEX + DMA_WING_BUF_EN_SHIFT) | DMA_EN;
	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++)
		dma_ctww |= (1 << (i + DMA_WING_BUF_EN_SHIFT));
	weg = bcmgenet_wdma_weadw(pwiv, DMA_CTWW);
	weg &= ~dma_ctww;
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_CTWW);

	bcmgenet_umac_wwitew(pwiv, 1, UMAC_TX_FWUSH);
	udeway(10);
	bcmgenet_umac_wwitew(pwiv, 0, UMAC_TX_FWUSH);

	wetuwn dma_ctww;
}

static void bcmgenet_enabwe_dma(stwuct bcmgenet_pwiv *pwiv, u32 dma_ctww)
{
	u32 weg;

	weg = bcmgenet_wdma_weadw(pwiv, DMA_CTWW);
	weg |= dma_ctww;
	bcmgenet_wdma_wwitew(pwiv, weg, DMA_CTWW);

	weg = bcmgenet_tdma_weadw(pwiv, DMA_CTWW);
	weg |= dma_ctww;
	bcmgenet_tdma_wwitew(pwiv, weg, DMA_CTWW);
}

static void bcmgenet_netif_stawt(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	/* Stawt the netwowk engine */
	bcmgenet_set_wx_mode(dev);
	bcmgenet_enabwe_wx_napi(pwiv);

	umac_enabwe_set(pwiv, CMD_TX_EN | CMD_WX_EN, twue);

	bcmgenet_enabwe_tx_napi(pwiv);

	/* Monitow wink intewwupts now */
	bcmgenet_wink_intw_enabwe(pwiv);

	phy_stawt(dev->phydev);
}

static int bcmgenet_open(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong dma_ctww;
	int wet;

	netif_dbg(pwiv, ifup, dev, "bcmgenet_open\n");

	/* Tuwn on the cwock */
	cwk_pwepawe_enabwe(pwiv->cwk);

	/* If this is an intewnaw GPHY, powew it back on now, befowe UniMAC is
	 * bwought out of weset as absowutewy no UniMAC activity is awwowed
	 */
	if (pwiv->intewnaw_phy)
		bcmgenet_powew_up(pwiv, GENET_POWEW_PASSIVE);

	/* take MAC out of weset */
	bcmgenet_umac_weset(pwiv);

	init_umac(pwiv);

	/* Appwy featuwes again in case we changed them whiwe intewface was
	 * down
	 */
	bcmgenet_set_featuwes(dev, dev->featuwes);

	bcmgenet_set_hw_addw(pwiv, dev->dev_addw);

	/* Disabwe WX/TX DMA and fwush TX queues */
	dma_ctww = bcmgenet_dma_disabwe(pwiv);

	/* Weinitiawize TDMA and WDMA and SW housekeeping */
	wet = bcmgenet_init_dma(pwiv);
	if (wet) {
		netdev_eww(dev, "faiwed to initiawize DMA\n");
		goto eww_cwk_disabwe;
	}

	/* Awways enabwe wing 16 - descwiptow wing */
	bcmgenet_enabwe_dma(pwiv, dma_ctww);

	/* HFB init */
	bcmgenet_hfb_init(pwiv);

	wet = wequest_iwq(pwiv->iwq0, bcmgenet_isw0, IWQF_SHAWED,
			  dev->name, pwiv);
	if (wet < 0) {
		netdev_eww(dev, "can't wequest IWQ %d\n", pwiv->iwq0);
		goto eww_fini_dma;
	}

	wet = wequest_iwq(pwiv->iwq1, bcmgenet_isw1, IWQF_SHAWED,
			  dev->name, pwiv);
	if (wet < 0) {
		netdev_eww(dev, "can't wequest IWQ %d\n", pwiv->iwq1);
		goto eww_iwq0;
	}

	wet = bcmgenet_mii_pwobe(dev);
	if (wet) {
		netdev_eww(dev, "faiwed to connect to PHY\n");
		goto eww_iwq1;
	}

	bcmgenet_phy_pause_set(dev, pwiv->wx_pause, pwiv->tx_pause);

	bcmgenet_netif_stawt(dev);

	netif_tx_stawt_aww_queues(dev);

	wetuwn 0;

eww_iwq1:
	fwee_iwq(pwiv->iwq1, pwiv);
eww_iwq0:
	fwee_iwq(pwiv->iwq0, pwiv);
eww_fini_dma:
	bcmgenet_dma_teawdown(pwiv);
	bcmgenet_fini_dma(pwiv);
eww_cwk_disabwe:
	if (pwiv->intewnaw_phy)
		bcmgenet_powew_down(pwiv, GENET_POWEW_PASSIVE);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void bcmgenet_netif_stop(stwuct net_device *dev, boow stop_phy)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	bcmgenet_disabwe_tx_napi(pwiv);
	netif_tx_disabwe(dev);

	/* Disabwe MAC weceive */
	umac_enabwe_set(pwiv, CMD_WX_EN, fawse);

	bcmgenet_dma_teawdown(pwiv);

	/* Disabwe MAC twansmit. TX DMA disabwed must be done befowe this */
	umac_enabwe_set(pwiv, CMD_TX_EN, fawse);

	if (stop_phy)
		phy_stop(dev->phydev);
	bcmgenet_disabwe_wx_napi(pwiv);
	bcmgenet_intw_disabwe(pwiv);

	/* Wait fow pending wowk items to compwete. Since intewwupts awe
	 * disabwed no new wowk wiww be scheduwed.
	 */
	cancew_wowk_sync(&pwiv->bcmgenet_iwq_wowk);

	/* tx wecwaim */
	bcmgenet_tx_wecwaim_aww(dev);
	bcmgenet_fini_dma(pwiv);
}

static int bcmgenet_cwose(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int wet = 0;

	netif_dbg(pwiv, ifdown, dev, "bcmgenet_cwose\n");

	bcmgenet_netif_stop(dev, fawse);

	/* Weawwy kiww the PHY state machine and disconnect fwom it */
	phy_disconnect(dev->phydev);

	fwee_iwq(pwiv->iwq0, pwiv);
	fwee_iwq(pwiv->iwq1, pwiv);

	if (pwiv->intewnaw_phy)
		wet = bcmgenet_powew_down(pwiv, GENET_POWEW_PASSIVE);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static void bcmgenet_dump_tx_queue(stwuct bcmgenet_tx_wing *wing)
{
	stwuct bcmgenet_pwiv *pwiv = wing->pwiv;
	u32 p_index, c_index, intsts, intmsk;
	stwuct netdev_queue *txq;
	unsigned int fwee_bds;
	boow txq_stopped;

	if (!netif_msg_tx_eww(pwiv))
		wetuwn;

	txq = netdev_get_tx_queue(pwiv->dev, wing->queue);

	spin_wock(&wing->wock);
	if (wing->index == DESC_INDEX) {
		intsts = ~bcmgenet_intww2_0_weadw(pwiv, INTWW2_CPU_MASK_STATUS);
		intmsk = UMAC_IWQ_TXDMA_DONE | UMAC_IWQ_TXDMA_MBDONE;
	} ewse {
		intsts = ~bcmgenet_intww2_1_weadw(pwiv, INTWW2_CPU_MASK_STATUS);
		intmsk = 1 << wing->index;
	}
	c_index = bcmgenet_tdma_wing_weadw(pwiv, wing->index, TDMA_CONS_INDEX);
	p_index = bcmgenet_tdma_wing_weadw(pwiv, wing->index, TDMA_PWOD_INDEX);
	txq_stopped = netif_tx_queue_stopped(txq);
	fwee_bds = wing->fwee_bds;
	spin_unwock(&wing->wock);

	netif_eww(pwiv, tx_eww, pwiv->dev, "Wing %d queue %d status summawy\n"
		  "TX queue status: %s, intewwupts: %s\n"
		  "(sw)fwee_bds: %d (sw)size: %d\n"
		  "(sw)p_index: %d (hw)p_index: %d\n"
		  "(sw)c_index: %d (hw)c_index: %d\n"
		  "(sw)cwean_p: %d (sw)wwite_p: %d\n"
		  "(sw)cb_ptw: %d (sw)end_ptw: %d\n",
		  wing->index, wing->queue,
		  txq_stopped ? "stopped" : "active",
		  intsts & intmsk ? "enabwed" : "disabwed",
		  fwee_bds, wing->size,
		  wing->pwod_index, p_index & DMA_P_INDEX_MASK,
		  wing->c_index, c_index & DMA_C_INDEX_MASK,
		  wing->cwean_ptw, wing->wwite_ptw,
		  wing->cb_ptw, wing->end_ptw);
}

static void bcmgenet_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	u32 int0_enabwe = 0;
	u32 int1_enabwe = 0;
	unsigned int q;

	netif_dbg(pwiv, tx_eww, dev, "bcmgenet_timeout\n");

	fow (q = 0; q < pwiv->hw_pawams->tx_queues; q++)
		bcmgenet_dump_tx_queue(&pwiv->tx_wings[q]);
	bcmgenet_dump_tx_queue(&pwiv->tx_wings[DESC_INDEX]);

	bcmgenet_tx_wecwaim_aww(dev);

	fow (q = 0; q < pwiv->hw_pawams->tx_queues; q++)
		int1_enabwe |= (1 << q);

	int0_enabwe = UMAC_IWQ_TXDMA_DONE;

	/* We-enabwe TX intewwupts if disabwed */
	bcmgenet_intww2_0_wwitew(pwiv, int0_enabwe, INTWW2_CPU_MASK_CWEAW);
	bcmgenet_intww2_1_wwitew(pwiv, int1_enabwe, INTWW2_CPU_MASK_CWEAW);

	netif_twans_update(dev);

	dev->stats.tx_ewwows++;

	netif_tx_wake_aww_queues(dev);
}

#define MAX_MDF_FIWTEW	17

static inwine void bcmgenet_set_mdf_addw(stwuct bcmgenet_pwiv *pwiv,
					 const unsigned chaw *addw,
					 int *i)
{
	bcmgenet_umac_wwitew(pwiv, addw[0] << 8 | addw[1],
			     UMAC_MDF_ADDW + (*i * 4));
	bcmgenet_umac_wwitew(pwiv, addw[2] << 24 | addw[3] << 16 |
			     addw[4] << 8 | addw[5],
			     UMAC_MDF_ADDW + ((*i + 1) * 4));
	*i += 2;
}

static void bcmgenet_set_wx_mode(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	int i, nfiwtew;
	u32 weg;

	netif_dbg(pwiv, hw, dev, "%s: %08X\n", __func__, dev->fwags);

	/* Numbew of fiwtews needed */
	nfiwtew = netdev_uc_count(dev) + netdev_mc_count(dev) + 2;

	/*
	 * Tuwn on pwomicuous mode fow thwee scenawios
	 * 1. IFF_PWOMISC fwag is set
	 * 2. IFF_AWWMUWTI fwag is set
	 * 3. The numbew of fiwtews needed exceeds the numbew fiwtews
	 *    suppowted by the hawdwawe.
	*/
	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	if ((dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI)) ||
	    (nfiwtew > MAX_MDF_FIWTEW)) {
		weg |= CMD_PWOMISC;
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);
		bcmgenet_umac_wwitew(pwiv, 0, UMAC_MDF_CTWW);
		wetuwn;
	} ewse {
		weg &= ~CMD_PWOMISC;
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);
	}

	/* update MDF fiwtew */
	i = 0;
	/* Bwoadcast */
	bcmgenet_set_mdf_addw(pwiv, dev->bwoadcast, &i);
	/* my own addwess.*/
	bcmgenet_set_mdf_addw(pwiv, dev->dev_addw, &i);

	/* Unicast */
	netdev_fow_each_uc_addw(ha, dev)
		bcmgenet_set_mdf_addw(pwiv, ha->addw, &i);

	/* Muwticast */
	netdev_fow_each_mc_addw(ha, dev)
		bcmgenet_set_mdf_addw(pwiv, ha->addw, &i);

	/* Enabwe fiwtews */
	weg = GENMASK(MAX_MDF_FIWTEW - 1, MAX_MDF_FIWTEW - nfiwtew);
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_MDF_CTWW);
}

/* Set the hawdwawe MAC addwess. */
static int bcmgenet_set_mac_addw(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;

	/* Setting the MAC addwess at the hawdwawe wevew is not possibwe
	 * without disabwing the UniMAC WX/TX enabwe bits.
	 */
	if (netif_wunning(dev))
		wetuwn -EBUSY;

	eth_hw_addw_set(dev, addw->sa_data);

	wetuwn 0;
}

static stwuct net_device_stats *bcmgenet_get_stats(stwuct net_device *dev)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong tx_bytes = 0, tx_packets = 0;
	unsigned wong wx_bytes = 0, wx_packets = 0;
	unsigned wong wx_ewwows = 0, wx_dwopped = 0;
	stwuct bcmgenet_tx_wing *tx_wing;
	stwuct bcmgenet_wx_wing *wx_wing;
	unsigned int q;

	fow (q = 0; q < pwiv->hw_pawams->tx_queues; q++) {
		tx_wing = &pwiv->tx_wings[q];
		tx_bytes += tx_wing->bytes;
		tx_packets += tx_wing->packets;
	}
	tx_wing = &pwiv->tx_wings[DESC_INDEX];
	tx_bytes += tx_wing->bytes;
	tx_packets += tx_wing->packets;

	fow (q = 0; q < pwiv->hw_pawams->wx_queues; q++) {
		wx_wing = &pwiv->wx_wings[q];

		wx_bytes += wx_wing->bytes;
		wx_packets += wx_wing->packets;
		wx_ewwows += wx_wing->ewwows;
		wx_dwopped += wx_wing->dwopped;
	}
	wx_wing = &pwiv->wx_wings[DESC_INDEX];
	wx_bytes += wx_wing->bytes;
	wx_packets += wx_wing->packets;
	wx_ewwows += wx_wing->ewwows;
	wx_dwopped += wx_wing->dwopped;

	dev->stats.tx_bytes = tx_bytes;
	dev->stats.tx_packets = tx_packets;
	dev->stats.wx_bytes = wx_bytes;
	dev->stats.wx_packets = wx_packets;
	dev->stats.wx_ewwows = wx_ewwows;
	dev->stats.wx_missed_ewwows = wx_ewwows;
	dev->stats.wx_dwopped = wx_dwopped;
	wetuwn &dev->stats;
}

static int bcmgenet_change_cawwiew(stwuct net_device *dev, boow new_cawwiew)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	if (!dev->phydev || !phy_is_pseudo_fixed_wink(dev->phydev) ||
	    pwiv->phy_intewface != PHY_INTEWFACE_MODE_MOCA)
		wetuwn -EOPNOTSUPP;

	if (new_cawwiew)
		netif_cawwiew_on(dev);
	ewse
		netif_cawwiew_off(dev);

	wetuwn 0;
}

static const stwuct net_device_ops bcmgenet_netdev_ops = {
	.ndo_open		= bcmgenet_open,
	.ndo_stop		= bcmgenet_cwose,
	.ndo_stawt_xmit		= bcmgenet_xmit,
	.ndo_tx_timeout		= bcmgenet_timeout,
	.ndo_set_wx_mode	= bcmgenet_set_wx_mode,
	.ndo_set_mac_addwess	= bcmgenet_set_mac_addw,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_featuwes	= bcmgenet_set_featuwes,
	.ndo_get_stats		= bcmgenet_get_stats,
	.ndo_change_cawwiew	= bcmgenet_change_cawwiew,
};

/* Awway of GENET hawdwawe pawametews/chawactewistics */
static stwuct bcmgenet_hw_pawams bcmgenet_hw_pawams[] = {
	[GENET_V1] = {
		.tx_queues = 0,
		.tx_bds_pew_q = 0,
		.wx_queues = 0,
		.wx_bds_pew_q = 0,
		.bp_in_en_shift = 16,
		.bp_in_mask = 0xffff,
		.hfb_fiwtew_cnt = 16,
		.qtag_mask = 0x1F,
		.hfb_offset = 0x1000,
		.wdma_offset = 0x2000,
		.tdma_offset = 0x3000,
		.wowds_pew_bd = 2,
	},
	[GENET_V2] = {
		.tx_queues = 4,
		.tx_bds_pew_q = 32,
		.wx_queues = 0,
		.wx_bds_pew_q = 0,
		.bp_in_en_shift = 16,
		.bp_in_mask = 0xffff,
		.hfb_fiwtew_cnt = 16,
		.qtag_mask = 0x1F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x1000,
		.hfb_weg_offset = 0x2000,
		.wdma_offset = 0x3000,
		.tdma_offset = 0x4000,
		.wowds_pew_bd = 2,
		.fwags = GENET_HAS_EXT,
	},
	[GENET_V3] = {
		.tx_queues = 4,
		.tx_bds_pew_q = 32,
		.wx_queues = 0,
		.wx_bds_pew_q = 0,
		.bp_in_en_shift = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_fiwtew_cnt = 48,
		.hfb_fiwtew_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_weg_offset = 0xfc00,
		.wdma_offset = 0x10000,
		.tdma_offset = 0x11000,
		.wowds_pew_bd = 2,
		.fwags = GENET_HAS_EXT | GENET_HAS_MDIO_INTW |
			 GENET_HAS_MOCA_WINK_DET,
	},
	[GENET_V4] = {
		.tx_queues = 4,
		.tx_bds_pew_q = 32,
		.wx_queues = 0,
		.wx_bds_pew_q = 0,
		.bp_in_en_shift = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_fiwtew_cnt = 48,
		.hfb_fiwtew_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_weg_offset = 0xfc00,
		.wdma_offset = 0x2000,
		.tdma_offset = 0x4000,
		.wowds_pew_bd = 3,
		.fwags = GENET_HAS_40BITS | GENET_HAS_EXT |
			 GENET_HAS_MDIO_INTW | GENET_HAS_MOCA_WINK_DET,
	},
	[GENET_V5] = {
		.tx_queues = 4,
		.tx_bds_pew_q = 32,
		.wx_queues = 0,
		.wx_bds_pew_q = 0,
		.bp_in_en_shift = 17,
		.bp_in_mask = 0x1ffff,
		.hfb_fiwtew_cnt = 48,
		.hfb_fiwtew_size = 128,
		.qtag_mask = 0x3F,
		.tbuf_offset = 0x0600,
		.hfb_offset = 0x8000,
		.hfb_weg_offset = 0xfc00,
		.wdma_offset = 0x2000,
		.tdma_offset = 0x4000,
		.wowds_pew_bd = 3,
		.fwags = GENET_HAS_40BITS | GENET_HAS_EXT |
			 GENET_HAS_MDIO_INTW | GENET_HAS_MOCA_WINK_DET,
	},
};

/* Infew hawdwawe pawametews fwom the detected GENET vewsion */
static void bcmgenet_set_hw_pawams(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct bcmgenet_hw_pawams *pawams;
	u32 weg;
	u8 majow;
	u16 gphy_wev;

	if (GENET_IS_V5(pwiv) || GENET_IS_V4(pwiv)) {
		bcmgenet_dma_wegs = bcmgenet_dma_wegs_v3pwus;
		genet_dma_wing_wegs = genet_dma_wing_wegs_v4;
	} ewse if (GENET_IS_V3(pwiv)) {
		bcmgenet_dma_wegs = bcmgenet_dma_wegs_v3pwus;
		genet_dma_wing_wegs = genet_dma_wing_wegs_v123;
	} ewse if (GENET_IS_V2(pwiv)) {
		bcmgenet_dma_wegs = bcmgenet_dma_wegs_v2;
		genet_dma_wing_wegs = genet_dma_wing_wegs_v123;
	} ewse if (GENET_IS_V1(pwiv)) {
		bcmgenet_dma_wegs = bcmgenet_dma_wegs_v1;
		genet_dma_wing_wegs = genet_dma_wing_wegs_v123;
	}

	/* enum genet_vewsion stawts at 1 */
	pwiv->hw_pawams = &bcmgenet_hw_pawams[pwiv->vewsion];
	pawams = pwiv->hw_pawams;

	/* Wead GENET HW vewsion */
	weg = bcmgenet_sys_weadw(pwiv, SYS_WEV_CTWW);
	majow = (weg >> 24 & 0x0f);
	if (majow == 6)
		majow = 5;
	ewse if (majow == 5)
		majow = 4;
	ewse if (majow == 0)
		majow = 1;
	if (majow != pwiv->vewsion) {
		dev_eww(&pwiv->pdev->dev,
			"GENET vewsion mismatch, got: %d, configuwed fow: %d\n",
			majow, pwiv->vewsion);
	}

	/* Pwint the GENET cowe vewsion */
	dev_info(&pwiv->pdev->dev, "GENET " GENET_VEW_FMT,
		 majow, (weg >> 16) & 0x0f, weg & 0xffff);

	/* Stowe the integwated PHY wevision fow the MDIO pwobing function
	 * to pass this infowmation to the PHY dwivew. The PHY dwivew expects
	 * to find the PHY majow wevision in bits 15:8 whiwe the GENET wegistew
	 * stowes that infowmation in bits 7:0, account fow that.
	 *
	 * On newew chips, stawting with PHY wevision G0, a new scheme is
	 * depwoyed simiwaw to the Stawfightew 2 switch with GPHY majow
	 * wevision in bits 15:8 and patch wevew in bits 7:0. Majow wevision 0
	 * is wesewved as weww as speciaw vawue 0x01ff, we have a smaww
	 * heuwistic to check fow the new GPHY wevision and we-awwange things
	 * so the GPHY dwivew is happy.
	 */
	gphy_wev = weg & 0xffff;

	if (GENET_IS_V5(pwiv)) {
		/* The EPHY wevision shouwd come fwom the MDIO wegistews of
		 * the PHY not fwom GENET.
		 */
		if (gphy_wev != 0) {
			pw_wawn("GENET is wepowting EPHY wevision: 0x%04x\n",
				gphy_wev);
		}
	/* This is wesewved so shouwd wequiwe speciaw tweatment */
	} ewse if (gphy_wev == 0 || gphy_wev == 0x01ff) {
		pw_wawn("Invawid GPHY wevision detected: 0x%04x\n", gphy_wev);
		wetuwn;
	/* This is the good owd scheme, just GPHY majow, no minow now patch */
	} ewse if ((gphy_wev & 0xf0) != 0) {
		pwiv->gphy_wev = gphy_wev << 8;
	/* This is the new scheme, GPHY majow wowws ovew with 0x10 = wev G0 */
	} ewse if ((gphy_wev & 0xff00) != 0) {
		pwiv->gphy_wev = gphy_wev;
	}

#ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (!(pawams->fwags & GENET_HAS_40BITS))
		pw_wawn("GENET does not suppowt 40-bits PA\n");
#endif

	pw_debug("Configuwation fow vewsion: %d\n"
		"TXq: %1d, TXqBDs: %1d, WXq: %1d, WXqBDs: %1d\n"
		"BP << en: %2d, BP msk: 0x%05x\n"
		"HFB count: %2d, QTAQ msk: 0x%05x\n"
		"TBUF: 0x%04x, HFB: 0x%04x, HFBweg: 0x%04x\n"
		"WDMA: 0x%05x, TDMA: 0x%05x\n"
		"Wowds/BD: %d\n",
		pwiv->vewsion,
		pawams->tx_queues, pawams->tx_bds_pew_q,
		pawams->wx_queues, pawams->wx_bds_pew_q,
		pawams->bp_in_en_shift, pawams->bp_in_mask,
		pawams->hfb_fiwtew_cnt, pawams->qtag_mask,
		pawams->tbuf_offset, pawams->hfb_offset,
		pawams->hfb_weg_offset,
		pawams->wdma_offset, pawams->tdma_offset,
		pawams->wowds_pew_bd);
}

stwuct bcmgenet_pwat_data {
	enum bcmgenet_vewsion vewsion;
	u32 dma_max_buwst_wength;
	boow ephy_16nm;
};

static const stwuct bcmgenet_pwat_data v1_pwat_data = {
	.vewsion = GENET_V1,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
};

static const stwuct bcmgenet_pwat_data v2_pwat_data = {
	.vewsion = GENET_V2,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
};

static const stwuct bcmgenet_pwat_data v3_pwat_data = {
	.vewsion = GENET_V3,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
};

static const stwuct bcmgenet_pwat_data v4_pwat_data = {
	.vewsion = GENET_V4,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
};

static const stwuct bcmgenet_pwat_data v5_pwat_data = {
	.vewsion = GENET_V5,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
};

static const stwuct bcmgenet_pwat_data bcm2711_pwat_data = {
	.vewsion = GENET_V5,
	.dma_max_buwst_wength = 0x08,
};

static const stwuct bcmgenet_pwat_data bcm7712_pwat_data = {
	.vewsion = GENET_V5,
	.dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH,
	.ephy_16nm = twue,
};

static const stwuct of_device_id bcmgenet_match[] = {
	{ .compatibwe = "bwcm,genet-v1", .data = &v1_pwat_data },
	{ .compatibwe = "bwcm,genet-v2", .data = &v2_pwat_data },
	{ .compatibwe = "bwcm,genet-v3", .data = &v3_pwat_data },
	{ .compatibwe = "bwcm,genet-v4", .data = &v4_pwat_data },
	{ .compatibwe = "bwcm,genet-v5", .data = &v5_pwat_data },
	{ .compatibwe = "bwcm,bcm2711-genet-v5", .data = &bcm2711_pwat_data },
	{ .compatibwe = "bwcm,bcm7712-genet-v5", .data = &bcm7712_pwat_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcmgenet_match);

static int bcmgenet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcmgenet_pwatfowm_data *pd = pdev->dev.pwatfowm_data;
	const stwuct bcmgenet_pwat_data *pdata;
	stwuct bcmgenet_pwiv *pwiv;
	stwuct net_device *dev;
	unsigned int i;
	int eww = -EIO;

	/* Up to GENET_MAX_MQ_CNT + 1 TX queues and WX queues */
	dev = awwoc_ethewdev_mqs(sizeof(*pwiv), GENET_MAX_MQ_CNT + 1,
				 GENET_MAX_MQ_CNT + 1);
	if (!dev) {
		dev_eww(&pdev->dev, "can't awwocate net device\n");
		wetuwn -ENOMEM;
	}

	pwiv = netdev_pwiv(dev);
	pwiv->iwq0 = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq0 < 0) {
		eww = pwiv->iwq0;
		goto eww;
	}
	pwiv->iwq1 = pwatfowm_get_iwq(pdev, 1);
	if (pwiv->iwq1 < 0) {
		eww = pwiv->iwq1;
		goto eww;
	}
	pwiv->wow_iwq = pwatfowm_get_iwq_optionaw(pdev, 2);
	if (pwiv->wow_iwq == -EPWOBE_DEFEW) {
		eww = pwiv->wow_iwq;
		goto eww;
	}

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		eww = PTW_EWW(pwiv->base);
		goto eww;
	}

	spin_wock_init(&pwiv->wock);

	/* Set defauwt pause pawametews */
	pwiv->autoneg_pause = 1;
	pwiv->tx_pause = 1;
	pwiv->wx_pause = 1;

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev_set_dwvdata(&pdev->dev, dev);
	dev->watchdog_timeo = 2 * HZ;
	dev->ethtoow_ops = &bcmgenet_ethtoow_ops;
	dev->netdev_ops = &bcmgenet_netdev_ops;

	pwiv->msg_enabwe = netif_msg_init(-1, GENET_MSG_DEFAUWT);

	/* Set defauwt featuwes */
	dev->featuwes |= NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_HW_CSUM |
			 NETIF_F_WXCSUM;
	dev->hw_featuwes |= dev->featuwes;
	dev->vwan_featuwes |= dev->featuwes;

	/* Wequest the WOW intewwupt and advewtise suspend if avaiwabwe */
	pwiv->wow_iwq_disabwed = twue;
	if (pwiv->wow_iwq > 0) {
		eww = devm_wequest_iwq(&pdev->dev, pwiv->wow_iwq,
				       bcmgenet_wow_isw, 0, dev->name, pwiv);
		if (!eww)
			device_set_wakeup_capabwe(&pdev->dev, 1);
	}

	/* Set the needed headwoom to account fow any possibwe
	 * featuwes enabwing/disabwing at wuntime
	 */
	dev->needed_headwoom += 64;

	pwiv->dev = dev;
	pwiv->pdev = pdev;

	pdata = device_get_match_data(&pdev->dev);
	if (pdata) {
		pwiv->vewsion = pdata->vewsion;
		pwiv->dma_max_buwst_wength = pdata->dma_max_buwst_wength;
		pwiv->ephy_16nm = pdata->ephy_16nm;
	} ewse {
		pwiv->vewsion = pd->genet_vewsion;
		pwiv->dma_max_buwst_wength = DMA_MAX_BUWST_WENGTH;
	}

	pwiv->cwk = devm_cwk_get_optionaw(&pwiv->pdev->dev, "enet");
	if (IS_EWW(pwiv->cwk)) {
		dev_dbg(&pwiv->pdev->dev, "faiwed to get enet cwock\n");
		eww = PTW_EWW(pwiv->cwk);
		goto eww;
	}

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		goto eww;

	bcmgenet_set_hw_pawams(pwiv);

	eww = -EIO;
	if (pwiv->hw_pawams->fwags & GENET_HAS_40BITS)
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (eww)
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		goto eww_cwk_disabwe;

	/* Mii wait queue */
	init_waitqueue_head(&pwiv->wq);
	/* Awways use WX_BUF_WENGTH (2KB) buffew fow aww chips */
	pwiv->wx_buf_wen = WX_BUF_WENGTH;
	INIT_WOWK(&pwiv->bcmgenet_iwq_wowk, bcmgenet_iwq_task);

	pwiv->cwk_wow = devm_cwk_get_optionaw(&pwiv->pdev->dev, "enet-wow");
	if (IS_EWW(pwiv->cwk_wow)) {
		dev_dbg(&pwiv->pdev->dev, "faiwed to get enet-wow cwock\n");
		eww = PTW_EWW(pwiv->cwk_wow);
		goto eww_cwk_disabwe;
	}

	pwiv->cwk_eee = devm_cwk_get_optionaw(&pwiv->pdev->dev, "enet-eee");
	if (IS_EWW(pwiv->cwk_eee)) {
		dev_dbg(&pwiv->pdev->dev, "faiwed to get enet-eee cwock\n");
		eww = PTW_EWW(pwiv->cwk_eee);
		goto eww_cwk_disabwe;
	}

	/* If this is an intewnaw GPHY, powew it on now, befowe UniMAC is
	 * bwought out of weset as absowutewy no UniMAC activity is awwowed
	 */
	if (device_get_phy_mode(&pdev->dev) == PHY_INTEWFACE_MODE_INTEWNAW)
		bcmgenet_powew_up(pwiv, GENET_POWEW_PASSIVE);

	if (pd && !IS_EWW_OW_NUWW(pd->mac_addwess))
		eth_hw_addw_set(dev, pd->mac_addwess);
	ewse
		if (device_get_ethdev_addwess(&pdev->dev, dev))
			if (has_acpi_companion(&pdev->dev)) {
				u8 addw[ETH_AWEN];

				bcmgenet_get_hw_addw(pwiv, addw);
				eth_hw_addw_set(dev, addw);
			}

	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		dev_wawn(&pdev->dev, "using wandom Ethewnet MAC\n");
		eth_hw_addw_wandom(dev);
	}

	weset_umac(pwiv);

	eww = bcmgenet_mii_init(dev);
	if (eww)
		goto eww_cwk_disabwe;

	/* setup numbew of weaw queues  + 1 (GENET_V1 has 0 hawdwawe queues
	 * just the wing 16 descwiptow based TX
	 */
	netif_set_weaw_num_tx_queues(pwiv->dev, pwiv->hw_pawams->tx_queues + 1);
	netif_set_weaw_num_wx_queues(pwiv->dev, pwiv->hw_pawams->wx_queues + 1);

	/* Set defauwt coawescing pawametews */
	fow (i = 0; i < pwiv->hw_pawams->wx_queues; i++)
		pwiv->wx_wings[i].wx_max_coawesced_fwames = 1;
	pwiv->wx_wings[DESC_INDEX].wx_max_coawesced_fwames = 1;

	/* wibphy wiww detewmine the wink state */
	netif_cawwiew_off(dev);

	/* Tuwn off the main cwock, WOW cwock is handwed sepawatewy */
	cwk_disabwe_unpwepawe(pwiv->cwk);

	eww = wegistew_netdev(dev);
	if (eww) {
		bcmgenet_mii_exit(dev);
		goto eww;
	}

	wetuwn eww;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww:
	fwee_netdev(dev);
	wetuwn eww;
}

static void bcmgenet_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcmgenet_pwiv *pwiv = dev_to_pwiv(&pdev->dev);

	dev_set_dwvdata(&pdev->dev, NUWW);
	unwegistew_netdev(pwiv->dev);
	bcmgenet_mii_exit(pwiv->dev);
	fwee_netdev(pwiv->dev);
}

static void bcmgenet_shutdown(stwuct pwatfowm_device *pdev)
{
	bcmgenet_wemove(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int bcmgenet_wesume_noiwq(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int wet;
	u32 weg;

	if (!netif_wunning(dev))
		wetuwn 0;

	/* Tuwn on the cwock */
	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	if (device_may_wakeup(d) && pwiv->wowopts) {
		/* Account fow Wake-on-WAN events and cweaw those events
		 * (Some devices need mowe time between enabwing the cwocks
		 *  and the intewwupt wegistew wefwecting the wake event so
		 *  wead the wegistew twice)
		 */
		weg = bcmgenet_intww2_0_weadw(pwiv, INTWW2_CPU_STAT);
		weg = bcmgenet_intww2_0_weadw(pwiv, INTWW2_CPU_STAT);
		if (weg & UMAC_IWQ_WAKE_EVENT)
			pm_wakeup_event(&pwiv->pdev->dev, 0);
	}

	bcmgenet_intww2_0_wwitew(pwiv, UMAC_IWQ_WAKE_EVENT, INTWW2_CPU_CWEAW);

	wetuwn 0;
}

static int bcmgenet_wesume(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bcmgenet_wxnfc_wuwe *wuwe;
	unsigned wong dma_ctww;
	int wet;

	if (!netif_wunning(dev))
		wetuwn 0;

	/* Fwom WOW-enabwed suspend, switch to weguwaw cwock */
	if (device_may_wakeup(d) && pwiv->wowopts)
		bcmgenet_powew_up(pwiv, GENET_POWEW_WOW_MAGIC);

	/* If this is an intewnaw GPHY, powew it back on now, befowe UniMAC is
	 * bwought out of weset as absowutewy no UniMAC activity is awwowed
	 */
	if (pwiv->intewnaw_phy)
		bcmgenet_powew_up(pwiv, GENET_POWEW_PASSIVE);

	bcmgenet_umac_weset(pwiv);

	init_umac(pwiv);

	phy_init_hw(dev->phydev);

	/* Speed settings must be westowed */
	genphy_config_aneg(dev->phydev);
	bcmgenet_mii_config(pwiv->dev, fawse);

	/* Westowe enabwed featuwes */
	bcmgenet_set_featuwes(dev, dev->featuwes);

	bcmgenet_set_hw_addw(pwiv, dev->dev_addw);

	/* Westowe hawdwawe fiwtews */
	bcmgenet_hfb_cweaw(pwiv);
	wist_fow_each_entwy(wuwe, &pwiv->wxnfc_wist, wist)
		if (wuwe->state != BCMGENET_WXNFC_STATE_UNUSED)
			bcmgenet_hfb_cweate_wxnfc_fiwtew(pwiv, wuwe);

	/* Disabwe WX/TX DMA and fwush TX queues */
	dma_ctww = bcmgenet_dma_disabwe(pwiv);

	/* Weinitiawize TDMA and WDMA and SW housekeeping */
	wet = bcmgenet_init_dma(pwiv);
	if (wet) {
		netdev_eww(dev, "faiwed to initiawize DMA\n");
		goto out_cwk_disabwe;
	}

	/* Awways enabwe wing 16 - descwiptow wing */
	bcmgenet_enabwe_dma(pwiv, dma_ctww);

	if (!device_may_wakeup(d))
		phy_wesume(dev->phydev);

	bcmgenet_netif_stawt(dev);

	netif_device_attach(dev);

	wetuwn 0;

out_cwk_disabwe:
	if (pwiv->intewnaw_phy)
		bcmgenet_powew_down(pwiv, GENET_POWEW_PASSIVE);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static int bcmgenet_suspend(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);

	bcmgenet_netif_stop(dev, twue);

	if (!device_may_wakeup(d))
		phy_suspend(dev->phydev);

	/* Disabwe fiwtewing */
	bcmgenet_hfb_weg_wwitew(pwiv, 0, HFB_CTWW);

	wetuwn 0;
}

static int bcmgenet_suspend_noiwq(stwuct device *d)
{
	stwuct net_device *dev = dev_get_dwvdata(d);
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	int wet = 0;

	if (!netif_wunning(dev))
		wetuwn 0;

	/* Pwepawe the device fow Wake-on-WAN and switch to the swow cwock */
	if (device_may_wakeup(d) && pwiv->wowopts)
		wet = bcmgenet_powew_down(pwiv, GENET_POWEW_WOW_MAGIC);
	ewse if (pwiv->intewnaw_phy)
		wet = bcmgenet_powew_down(pwiv, GENET_POWEW_PASSIVE);

	/* Wet the fwamewowk handwe wesumption and weave the cwocks on */
	if (wet)
		wetuwn wet;

	/* Tuwn off the cwocks */
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}
#ewse
#define bcmgenet_suspend	NUWW
#define bcmgenet_suspend_noiwq	NUWW
#define bcmgenet_wesume		NUWW
#define bcmgenet_wesume_noiwq	NUWW
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops bcmgenet_pm_ops = {
	.suspend	= bcmgenet_suspend,
	.suspend_noiwq	= bcmgenet_suspend_noiwq,
	.wesume		= bcmgenet_wesume,
	.wesume_noiwq	= bcmgenet_wesume_noiwq,
};

static const stwuct acpi_device_id genet_acpi_match[] = {
	{ "BCM6E4E", (kewnew_uwong_t)&bcm2711_pwat_data },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, genet_acpi_match);

static stwuct pwatfowm_dwivew bcmgenet_dwivew = {
	.pwobe	= bcmgenet_pwobe,
	.wemove_new = bcmgenet_wemove,
	.shutdown = bcmgenet_shutdown,
	.dwivew	= {
		.name	= "bcmgenet",
		.of_match_tabwe = bcmgenet_match,
		.pm	= &bcmgenet_pm_ops,
		.acpi_match_tabwe = genet_acpi_match,
	},
};
moduwe_pwatfowm_dwivew(bcmgenet_dwivew);

MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_DESCWIPTION("Bwoadcom GENET Ethewnet contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:bcmgenet");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: mdio-bcm-unimac");
