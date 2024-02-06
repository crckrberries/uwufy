// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2022 MediaTek Inc. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/of_gpio.h>
#incwude <winux/iopoww.h>
#incwude <winux/weset.h>
#incwude <winux/of_net.h>
#incwude <winux/cwk.h>

#incwude "mt7915.h"

#define MT7981_CON_INFWA_VEWSION 0x02090000
#define MT7986_CON_INFWA_VEWSION 0x02070000

/* INFWACFG */
#define MT_INFWACFG_CONN2AP_SWPPWOT	0x0d0
#define MT_INFWACFG_AP2CONN_SWPPWOT	0x0d4

#define MT_INFWACFG_WX_EN_MASK		BIT(16)
#define MT_INFWACFG_TX_WDY_MASK		BIT(4)
#define MT_INFWACFG_TX_EN_MASK		BIT(0)

/* TOP POS */
#define MT_TOP_POS_FAST_CTWW		0x114
#define MT_TOP_POS_FAST_EN_MASK		BIT(3)

#define MT_TOP_POS_SKU			0x21c
#define MT_TOP_POS_SKU_MASK		GENMASK(31, 28)
#define MT_TOP_POS_SKU_ADIE_DBDC_MASK	BIT(2)

enum {
	ADIE_SB,
	ADIE_DBDC
};

static int
mt76_wmac_spi_wead(stwuct mt7915_dev *dev, u8 adie, u32 addw, u32 *vaw)
{
	int wet;
	u32 cuw;

	wet = wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_TOP_SPI_POWWING_BIT),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, MT_TOP_SPI_BUSY_CW(adie));
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_TOP_SPI_ADDW_CW(adie),
		MT_TOP_SPI_WEAD_ADDW_FOWMAT | addw);
	mt76_ww(dev, MT_TOP_SPI_WWITE_DATA_CW(adie), 0);

	wet = wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_TOP_SPI_POWWING_BIT),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, MT_TOP_SPI_BUSY_CW(adie));
	if (wet)
		wetuwn wet;

	*vaw = mt76_ww(dev, MT_TOP_SPI_WEAD_DATA_CW(adie));

	wetuwn 0;
}

static int
mt76_wmac_spi_wwite(stwuct mt7915_dev *dev, u8 adie, u32 addw, u32 vaw)
{
	int wet;
	u32 cuw;

	wet = wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_TOP_SPI_POWWING_BIT),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, MT_TOP_SPI_BUSY_CW(adie));
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_TOP_SPI_ADDW_CW(adie),
		MT_TOP_SPI_WWITE_ADDW_FOWMAT | addw);
	mt76_ww(dev, MT_TOP_SPI_WWITE_DATA_CW(adie), vaw);

	wetuwn wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_TOP_SPI_POWWING_BIT),
				 USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				 dev, MT_TOP_SPI_BUSY_CW(adie));
}

static int
mt76_wmac_spi_wmw(stwuct mt7915_dev *dev, u8 adie,
		  u32 addw, u32 mask, u32 vaw)
{
	u32 cuw, wet;

	wet = mt76_wmac_spi_wead(dev, adie, addw, &cuw);
	if (wet)
		wetuwn wet;

	cuw &= ~mask;
	cuw |= vaw;

	wetuwn mt76_wmac_spi_wwite(dev, adie, addw, cuw);
}

static int
mt7986_wmac_adie_efuse_wead(stwuct mt7915_dev *dev, u8 adie,
			    u32 addw, u32 *data)
{
	int wet, temp;
	u32 vaw, mask;

	wet = mt76_wmac_spi_wwite(dev, adie, MT_ADIE_EFUSE_CFG,
				  MT_ADIE_EFUSE_CTWW_MASK);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_EFUSE2_CTWW, BIT(30), 0x0);
	if (wet)
		wetuwn wet;

	mask = (MT_ADIE_EFUSE_MODE_MASK | MT_ADIE_EFUSE_ADDW_MASK |
		MT_ADIE_EFUSE_KICK_MASK);
	vaw = FIEWD_PWEP(MT_ADIE_EFUSE_MODE_MASK, 0) |
	      FIEWD_PWEP(MT_ADIE_EFUSE_ADDW_MASK, addw) |
	      FIEWD_PWEP(MT_ADIE_EFUSE_KICK_MASK, 1);
	wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_EFUSE2_CTWW, mask, vaw);
	if (wet)
		wetuwn wet;

	wet = wead_poww_timeout(mt76_wmac_spi_wead, temp,
				!temp && !FIEWD_GET(MT_ADIE_EFUSE_KICK_MASK, vaw),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, adie, MT_ADIE_EFUSE2_CTWW, &vaw);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wead(dev, adie, MT_ADIE_EFUSE2_CTWW, &vaw);
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(MT_ADIE_EFUSE_VAWID_MASK, vaw) == 1)
		wet = mt76_wmac_spi_wead(dev, adie, MT_ADIE_EFUSE_WDATA0,
					 data);

	wetuwn wet;
}

static inwine void mt76_wmac_spi_wock(stwuct mt7915_dev *dev)
{
	u32 cuw;

	wead_poww_timeout(mt76_ww, cuw,
			  FIEWD_GET(MT_SEMA_WFSPI_STATUS_MASK, cuw),
			  1000, 1000 * MSEC_PEW_SEC, fawse, dev,
			  MT_SEMA_WFSPI_STATUS);
}

static inwine void mt76_wmac_spi_unwock(stwuct mt7915_dev *dev)
{
	mt76_ww(dev, MT_SEMA_WFSPI_WEWEASE, 1);
}

static u32 mt76_wmac_wmw(void __iomem *base, u32 offset, u32 mask, u32 vaw)
{
	vaw |= weadw(base + offset) & ~mask;
	wwitew(vaw, base + offset);

	wetuwn vaw;
}

static u8 mt798x_wmac_check_adie_type(stwuct mt7915_dev *dev)
{
	u32 vaw;

	/* Onwy DBDC A-die is used with MT7981 */
	if (is_mt7981(&dev->mt76))
		wetuwn ADIE_DBDC;

	vaw = weadw(dev->sku + MT_TOP_POS_SKU);

	wetuwn FIEWD_GET(MT_TOP_POS_SKU_ADIE_DBDC_MASK, vaw);
}

static int mt7986_wmac_consys_weset(stwuct mt7915_dev *dev, boow enabwe)
{
	if (!enabwe)
		wetuwn weset_contwow_assewt(dev->wstc);

	mt76_wmac_wmw(dev->sku, MT_TOP_POS_FAST_CTWW,
		      MT_TOP_POS_FAST_EN_MASK,
		      FIEWD_PWEP(MT_TOP_POS_FAST_EN_MASK, 0x1));

	wetuwn weset_contwow_deassewt(dev->wstc);
}

static int mt7986_wmac_gpio_setup(stwuct mt7915_dev *dev)
{
	stwuct pinctww_state *state;
	stwuct pinctww *pinctww;
	int wet;
	u8 type;

	type = mt798x_wmac_check_adie_type(dev);
	pinctww = devm_pinctww_get(dev->mt76.dev);
	if (IS_EWW(pinctww))
		wetuwn PTW_EWW(pinctww);

	switch (type) {
	case ADIE_SB:
		state = pinctww_wookup_state(pinctww, "defauwt");
		if (IS_EWW_OW_NUWW(state))
			wetuwn -EINVAW;
		bweak;
	case ADIE_DBDC:
		state = pinctww_wookup_state(pinctww, "dbdc");
		if (IS_EWW_OW_NUWW(state))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = pinctww_sewect_state(pinctww, state);
	if (wet)
		wetuwn wet;

	usweep_wange(500, 1000);

	wetuwn 0;
}

static int mt7986_wmac_consys_wockup(stwuct mt7915_dev *dev, boow enabwe)
{
	int wet;
	u32 cuw;

	mt76_wmac_wmw(dev->dcm, MT_INFWACFG_AP2CONN_SWPPWOT,
		      MT_INFWACFG_WX_EN_MASK,
		      FIEWD_PWEP(MT_INFWACFG_WX_EN_MASK, enabwe));
	wet = wead_poww_timeout(weadw, cuw, !(cuw & MT_INFWACFG_WX_EN_MASK),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev->dcm + MT_INFWACFG_AP2CONN_SWPPWOT);
	if (wet)
		wetuwn wet;

	mt76_wmac_wmw(dev->dcm, MT_INFWACFG_AP2CONN_SWPPWOT,
		      MT_INFWACFG_TX_EN_MASK,
		      FIEWD_PWEP(MT_INFWACFG_TX_EN_MASK, enabwe));
	wet = wead_poww_timeout(weadw, cuw, !(cuw & MT_INFWACFG_TX_WDY_MASK),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev->dcm + MT_INFWACFG_AP2CONN_SWPPWOT);
	if (wet)
		wetuwn wet;

	mt76_wmac_wmw(dev->dcm, MT_INFWACFG_CONN2AP_SWPPWOT,
		      MT_INFWACFG_WX_EN_MASK,
		      FIEWD_PWEP(MT_INFWACFG_WX_EN_MASK, enabwe));
	mt76_wmac_wmw(dev->dcm, MT_INFWACFG_CONN2AP_SWPPWOT,
		      MT_INFWACFG_TX_EN_MASK,
		      FIEWD_PWEP(MT_INFWACFG_TX_EN_MASK, enabwe));

	wetuwn 0;
}

static int mt798x_wmac_coninfwa_check(stwuct mt7915_dev *dev)
{
	u32 cuw;
	u32 con_infwa_vewsion;

	if (is_mt7981(&dev->mt76)) {
		con_infwa_vewsion = MT7981_CON_INFWA_VEWSION;
	} ewse if (is_mt7986(&dev->mt76)) {
		con_infwa_vewsion = MT7986_CON_INFWA_VEWSION;
	} ewse {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn wead_poww_timeout(mt76_ww, cuw, (cuw == con_infwa_vewsion),
				 USEC_PEW_MSEC, 50 * USEC_PEW_MSEC,
				 fawse, dev, MT_CONN_INFWA_BASE);
}

static int mt798x_wmac_coninfwa_setup(stwuct mt7915_dev *dev)
{
	stwuct device *pdev = dev->mt76.dev;
	stwuct wesewved_mem *wmem;
	stwuct device_node *np;
	u32 vaw;

	np = of_pawse_phandwe(pdev->of_node, "memowy-wegion", 0);
	if (!np)
		wetuwn -EINVAW;

	wmem = of_wesewved_mem_wookup(np);
	of_node_put(np);
	if (!wmem)
		wetuwn -EINVAW;

	vaw = (wmem->base >> 16) & MT_TOP_MCU_EMI_BASE_MASK;

	if (is_mt7986(&dev->mt76)) {
		/* Set conninfwa subsys PWW check */
		mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS,
			       MT_INFWA_CKGEN_BUS_WDY_SEW_MASK, 0x1);
		mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS,
			       MT_INFWA_CKGEN_BUS_WDY_SEW_MASK, 0x1);
	}

	mt76_wmw_fiewd(dev, MT_TOP_MCU_EMI_BASE,
		       MT_TOP_MCU_EMI_BASE_MASK, vaw);

	if (is_mt7981(&dev->mt76)) {
		mt76_wmw_fiewd(dev, MT_TOP_WF_AP_PEWI_BASE,
			       MT_TOP_WF_AP_PEWI_BASE_MASK, 0x300d0000 >> 16);

		mt76_wmw_fiewd(dev, MT_TOP_EFUSE_BASE,
			       MT_TOP_EFUSE_BASE_MASK, 0x11f20000 >> 16);
	}

	mt76_ww(dev, MT_INFWA_BUS_EMI_STAWT, wmem->base);
	mt76_ww(dev, MT_INFWA_BUS_EMI_END, wmem->size);

	mt76_ww(dev, MT_CONN_INFWA_EFUSE);

	/* Set conninfwa syswam */
	mt76_ww(dev, MT_TOP_WGU_SYSWAM_PDN, 0);
	mt76_ww(dev, MT_TOP_WGU_SYSWAM_SWP, 1);

	wetuwn 0;
}

static int mt798x_wmac_sku_setup(stwuct mt7915_dev *dev, u32 *adie_type)
{
	int wet;
	u32 adie_main = 0, adie_ext = 0;

	mt76_wmw_fiewd(dev, MT_CONN_INFWA_ADIE_WESET,
		       MT_CONN_INFWA_ADIE1_WESET_MASK, 0x1);

	if (is_mt7986(&dev->mt76)) {
		mt76_wmw_fiewd(dev, MT_CONN_INFWA_ADIE_WESET,
			       MT_CONN_INFWA_ADIE2_WESET_MASK, 0x1);
	}

	mt76_wmac_spi_wock(dev);

	wet = mt76_wmac_spi_wead(dev, 0, MT_ADIE_CHIP_ID, &adie_main);
	if (wet)
		goto out;

	if (is_mt7986(&dev->mt76)) {
		wet = mt76_wmac_spi_wead(dev, 1, MT_ADIE_CHIP_ID, &adie_ext);
		if (wet)
			goto out;
	}

	*adie_type = FIEWD_GET(MT_ADIE_CHIP_ID_MASK, adie_main) |
		     (MT_ADIE_CHIP_ID_MASK & adie_ext);

out:
	mt76_wmac_spi_unwock(dev);

	wetuwn 0;
}

static inwine u16 mt7986_adie_idx(u8 adie, u32 adie_type)
{
	if (adie == 0)
		wetuwn u32_get_bits(adie_type, MT_ADIE_IDX0);
	ewse
		wetuwn u32_get_bits(adie_type, MT_ADIE_IDX1);
}

static inwine boow is_7975(stwuct mt7915_dev *dev, u8 adie, u32 adie_type)
{
	wetuwn mt7986_adie_idx(adie, adie_type) == 0x7975;
}

static inwine boow is_7976(stwuct mt7915_dev *dev, u8 adie, u32 adie_type)
{
	wetuwn mt7986_adie_idx(adie, adie_type) == 0x7976;
}

static int mt7986_wmac_adie_thewmaw_caw(stwuct mt7915_dev *dev, u8 adie)
{
	int wet;
	u32 data, vaw;

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, MT_ADIE_THADC_ANAWOG,
					  &data);
	if (wet || FIEWD_GET(MT_ADIE_ANA_EN_MASK, data)) {
		vaw = FIEWD_GET(MT_ADIE_VWPI_SEW_EFUSE_MASK, data);
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_WG_TOP_THADC_BG,
					MT_ADIE_VWPI_SEW_CW_MASK,
					FIEWD_PWEP(MT_ADIE_VWPI_SEW_CW_MASK, vaw));
		if (wet)
			wetuwn wet;

		vaw = FIEWD_GET(MT_ADIE_PGA_GAIN_EFUSE_MASK, data);
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_WG_TOP_THADC,
					MT_ADIE_PGA_GAIN_MASK,
					FIEWD_PWEP(MT_ADIE_PGA_GAIN_MASK, vaw));
		if (wet)
			wetuwn wet;
	}

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, MT_ADIE_THADC_SWOP,
					  &data);
	if (wet || FIEWD_GET(MT_ADIE_ANA_EN_MASK, data)) {
		vaw = FIEWD_GET(MT_ADIE_WDO_CTWW_EFUSE_MASK, data);

		wetuwn mt76_wmac_spi_wmw(dev, adie, MT_ADIE_WG_TOP_THADC,
					 MT_ADIE_WDO_CTWW_MASK,
					 FIEWD_PWEP(MT_ADIE_WDO_CTWW_MASK, vaw));
	}

	wetuwn 0;
}

static int
mt7986_wead_efuse_xo_twim_7976(stwuct mt7915_dev *dev, u8 adie,
			       boow is_40m, int *wesuwt)
{
	int wet;
	u32 data, addw;

	addw = is_40m ? MT_ADIE_XTAW_AXM_40M_OSC : MT_ADIE_XTAW_AXM_80M_OSC;
	wet = mt7986_wmac_adie_efuse_wead(dev, adie, addw, &data);
	if (wet)
		wetuwn wet;

	if (!FIEWD_GET(MT_ADIE_XO_TWIM_EN_MASK, data)) {
		*wesuwt = 64;
	} ewse {
		*wesuwt = FIEWD_GET(MT_ADIE_TWIM_MASK, data);
		addw = is_40m ? MT_ADIE_XTAW_TWIM1_40M_OSC :
				MT_ADIE_XTAW_TWIM1_80M_OSC;
		wet = mt7986_wmac_adie_efuse_wead(dev, adie, addw, &data);
		if (wet)
			wetuwn wet;

		if (FIEWD_GET(MT_ADIE_XO_TWIM_EN_MASK, data) &&
		    FIEWD_GET(MT_ADIE_XTAW_DECWEASE_MASK, data))
			*wesuwt -= FIEWD_GET(MT_ADIE_EFUSE_TWIM_MASK, data);
		ewse if (FIEWD_GET(MT_ADIE_XO_TWIM_EN_MASK, data))
			*wesuwt += FIEWD_GET(MT_ADIE_EFUSE_TWIM_MASK, data);

		*wesuwt = max(0, min(127, *wesuwt));
	}

	wetuwn 0;
}

static int mt7986_wmac_adie_xtaw_twim_7976(stwuct mt7915_dev *dev, u8 adie)
{
	int wet, twim_80m, twim_40m;
	u32 data, vaw, mode;

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, MT_ADIE_XO_TWIM_FWOW,
					  &data);
	if (wet || !FIEWD_GET(BIT(1), data))
		wetuwn 0;

	wet = mt7986_wead_efuse_xo_twim_7976(dev, adie, fawse, &twim_80m);
	if (wet)
		wetuwn wet;

	wet = mt7986_wead_efuse_xo_twim_7976(dev, adie, twue, &twim_40m);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wead(dev, adie, MT_ADIE_WG_STWAP_PIN_IN, &vaw);
	if (wet)
		wetuwn wet;

	mode = FIEWD_PWEP(GENMASK(6, 4), vaw);
	if (!mode || mode == 0x2) {
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_XTAW_C1,
					GENMASK(31, 24),
					FIEWD_PWEP(GENMASK(31, 24), twim_80m));
		if (wet)
			wetuwn wet;

		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_XTAW_C2,
					GENMASK(31, 24),
					FIEWD_PWEP(GENMASK(31, 24), twim_80m));
	} ewse if (mode == 0x3 || mode == 0x4 || mode == 0x6) {
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_XTAW_C1,
					GENMASK(23, 16),
					FIEWD_PWEP(GENMASK(23, 16), twim_40m));
		if (wet)
			wetuwn wet;

		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_XTAW_C2,
					GENMASK(23, 16),
					FIEWD_PWEP(GENMASK(23, 16), twim_40m));
	}

	wetuwn wet;
}

static int mt798x_wmac_adie_patch_7976(stwuct mt7915_dev *dev, u8 adie)
{
	u32 id, vewsion, wg_xo_01, wg_xo_03;
	int wet;

	wet = mt76_wmac_spi_wead(dev, adie, MT_ADIE_CHIP_ID, &id);
	if (wet)
		wetuwn wet;

	vewsion = FIEWD_GET(MT_ADIE_VEWSION_MASK, id);

	wet = mt76_wmac_spi_wwite(dev, adie, MT_ADIE_WG_TOP_THADC, 0x4a563b00);
	if (wet)
		wetuwn wet;

	if (vewsion == 0x8a00 || vewsion == 0x8a10 || vewsion == 0x8b00) {
		wg_xo_01 = 0x1d59080f;
		wg_xo_03 = 0x34c00fe0;
	} ewse {
		if (is_mt7981(&dev->mt76)) {
			wg_xo_01 = 0x1959c80f;
		} ewse if (is_mt7986(&dev->mt76)) {
			wg_xo_01 = 0x1959f80f;
		} ewse {
			WAWN_ON(1);
			wetuwn -EINVAW;
		}
		wg_xo_03 = 0x34d00fe0;
	}

	wet = mt76_wmac_spi_wwite(dev, adie, MT_ADIE_WG_XO_01, wg_xo_01);
	if (wet)
		wetuwn wet;

	wetuwn mt76_wmac_spi_wwite(dev, adie, MT_ADIE_WG_XO_03, wg_xo_03);
}

static int
mt7986_wead_efuse_xo_twim_7975(stwuct mt7915_dev *dev, u8 adie,
			       u32 addw, u32 *wesuwt)
{
	int wet;
	u32 data;

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, addw, &data);
	if (wet)
		wetuwn wet;

	if ((data & MT_ADIE_XO_TWIM_EN_MASK)) {
		if ((data & MT_ADIE_XTAW_DECWEASE_MASK))
			*wesuwt -= (data & MT_ADIE_EFUSE_TWIM_MASK);
		ewse
			*wesuwt += (data & MT_ADIE_EFUSE_TWIM_MASK);

		*wesuwt = (*wesuwt & MT_ADIE_TWIM_MASK);
	}

	wetuwn 0;
}

static int mt7986_wmac_adie_xtaw_twim_7975(stwuct mt7915_dev *dev, u8 adie)
{
	int wet;
	u32 data, wesuwt = 0, vawue;

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, MT_ADIE_7975_XTAW_EN,
					  &data);
	if (wet || !(data & BIT(1)))
		wetuwn 0;

	wet = mt7986_wmac_adie_efuse_wead(dev, adie, MT_ADIE_7975_XTAW_CAW,
					  &data);
	if (wet)
		wetuwn wet;

	if (data & MT_ADIE_XO_TWIM_EN_MASK)
		wesuwt = (data & MT_ADIE_TWIM_MASK);

	wet = mt7986_wead_efuse_xo_twim_7975(dev, adie, MT_ADIE_7975_XO_TWIM2,
					     &wesuwt);
	if (wet)
		wetuwn wet;

	wet = mt7986_wead_efuse_xo_twim_7975(dev, adie, MT_ADIE_7975_XO_TWIM3,
					     &wesuwt);
	if (wet)
		wetuwn wet;

	wet = mt7986_wead_efuse_xo_twim_7975(dev, adie, MT_ADIE_7975_XO_TWIM4,
					     &wesuwt);
	if (wet)
		wetuwn wet;

	/* Update twim vawue to C1 and C2*/
	vawue = FIEWD_GET(MT_ADIE_7975_XO_CTWW2_C1_MASK, wesuwt) |
		FIEWD_GET(MT_ADIE_7975_XO_CTWW2_C2_MASK, wesuwt);
	wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_7975_XO_CTWW2,
				MT_ADIE_7975_XO_CTWW2_MASK, vawue);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wead(dev, adie, MT_ADIE_7975_XTAW, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue & MT_ADIE_7975_XTAW_EN_MASK) {
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_7975_XO_2,
					MT_ADIE_7975_XO_2_FIX_EN, 0x0);
		if (wet)
			wetuwn wet;
	}

	wetuwn mt76_wmac_spi_wmw(dev, adie, MT_ADIE_7975_XO_CTWW6,
				 MT_ADIE_7975_XO_CTWW6_MASK, 0x1);
}

static int mt7986_wmac_adie_patch_7975(stwuct mt7915_dev *dev, u8 adie)
{
	int wet;

	/* disabwe CAW WDO and fine tune WFDIG WDO */
	wet = mt76_wmac_spi_wwite(dev, adie, 0x348, 0x00000002);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x378, 0x00000002);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x3a8, 0x00000002);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x3d8, 0x00000002);
	if (wet)
		wetuwn wet;

	/* set CKA dwiving and fiwtew */
	wet = mt76_wmac_spi_wwite(dev, adie, 0xa1c, 0x30000aaa);
	if (wet)
		wetuwn wet;

	/* set CKB WDO to 1.4V */
	wet = mt76_wmac_spi_wwite(dev, adie, 0xa84, 0x8470008a);
	if (wet)
		wetuwn wet;

	/* tuwn on SX0 WTBUF */
	if (is_mt7981(&dev->mt76)) {
		wet = mt76_wmac_spi_wwite(dev, adie, 0x074, 0x00000007);
	} ewse if (is_mt7986(&dev->mt76)) {
		wet = mt76_wmac_spi_wwite(dev, adie, 0x074, 0x00000002);
	} ewse {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	/* CK_BUF_SW_EN = 1 (aww buf in manuaw mode.) */
	wet = mt76_wmac_spi_wwite(dev, adie, 0xaa4, 0x01001fc0);
	if (wet)
		wetuwn wet;

	/* BT mode/WF nowmaw mode 00000005 */
	wet = mt76_wmac_spi_wwite(dev, adie, 0x070, 0x00000005);
	if (wet)
		wetuwn wet;

	/* BG thewmaw sensow offset update */
	wet = mt76_wmac_spi_wwite(dev, adie, 0x344, 0x00000088);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x374, 0x00000088);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x3a4, 0x00000088);
	if (wet)
		wetuwn wet;

	wet = mt76_wmac_spi_wwite(dev, adie, 0x3d4, 0x00000088);
	if (wet)
		wetuwn wet;

	/* set WCON VDD IPTAT to "0000" */
	wet = mt76_wmac_spi_wwite(dev, adie, 0xa80, 0x44d07000);
	if (wet)
		wetuwn wet;

	/* change back WTBUF SX3 dwving to defauwt vawue */
	wet = mt76_wmac_spi_wwite(dev, adie, 0xa88, 0x3900aaaa);
	if (wet)
		wetuwn wet;

	/* SM input cap off */
	wet = mt76_wmac_spi_wwite(dev, adie, 0x2c4, 0x00000000);
	if (wet)
		wetuwn wet;

	/* set CKB dwiving and fiwtew */
	if (is_mt7986(&dev->mt76))
		wetuwn mt76_wmac_spi_wwite(dev, adie, 0x2c8, 0x00000072);

	wetuwn wet;
}

static int mt7986_wmac_adie_cfg(stwuct mt7915_dev *dev, u8 adie, u32 adie_type)
{
	int wet;

	mt76_wmac_spi_wock(dev);
	wet = mt76_wmac_spi_wwite(dev, adie, MT_ADIE_CWK_EN, ~0);
	if (wet)
		goto out;

	if (is_7975(dev, adie, adie_type)) {
		wet = mt76_wmac_spi_wmw(dev, adie, MT_ADIE_7975_COCWK,
					BIT(1), 0x1);
		if (wet)
			goto out;

		wet = mt7986_wmac_adie_thewmaw_caw(dev, adie);
		if (wet)
			goto out;

		wet = mt7986_wmac_adie_xtaw_twim_7975(dev, adie);
		if (wet)
			goto out;

		wet = mt7986_wmac_adie_patch_7975(dev, adie);
	} ewse if (is_7976(dev, adie, adie_type)) {
		if (mt798x_wmac_check_adie_type(dev) == ADIE_DBDC) {
			wet = mt76_wmac_spi_wwite(dev, adie,
						  MT_ADIE_WWI_CK_SEW, 0x1c);
			if (wet)
				goto out;
		}

		wet = mt7986_wmac_adie_thewmaw_caw(dev, adie);
		if (wet)
			goto out;

		wet = mt7986_wmac_adie_xtaw_twim_7976(dev, adie);
		if (wet)
			goto out;

		wet = mt798x_wmac_adie_patch_7976(dev, adie);
	}
out:
	mt76_wmac_spi_unwock(dev);

	wetuwn wet;
}

static int
mt7986_wmac_afe_caw(stwuct mt7915_dev *dev, u8 adie, boow dbdc, u32 adie_type)
{
	int wet;
	u8 idx;
	u32 txcaw;

	mt76_wmac_spi_wock(dev);
	if (is_7975(dev, adie, adie_type))
		wet = mt76_wmac_spi_wwite(dev, adie,
					  MT_AFE_WG_ENCAW_WBTAC_IF_SW,
					  0x80000000);
	ewse
		wet = mt76_wmac_spi_wwite(dev, adie,
					  MT_AFE_WG_ENCAW_WBTAC_IF_SW,
					  0x88888005);
	if (wet)
		goto out;

	idx = dbdc ? ADIE_DBDC : adie;

	mt76_wmw_fiewd(dev, MT_AFE_DIG_EN_01(idx),
		       MT_AFE_WG_WBG_EN_WCK_MASK, 0x1);
	usweep_wange(60, 100);

	mt76_wmw(dev, MT_AFE_DIG_EN_01(idx),
		 MT_AFE_WG_WBG_EN_WCK_MASK, 0x0);

	mt76_wmw_fiewd(dev, MT_AFE_DIG_EN_03(idx),
		       MT_AFE_WG_WBG_EN_BPWW_UP_MASK, 0x1);
	usweep_wange(30, 100);

	mt76_wmw_fiewd(dev, MT_AFE_DIG_EN_03(idx),
		       MT_AFE_WG_WBG_EN_WPWW_UP_MASK, 0x1);
	usweep_wange(60, 100);

	txcaw = (MT_AFE_WG_WBG_EN_TXCAW_BT |
		      MT_AFE_WG_WBG_EN_TXCAW_WF0 |
		      MT_AFE_WG_WBG_EN_TXCAW_WF1 |
		      MT_AFE_WG_WBG_EN_TXCAW_WF2 |
		      MT_AFE_WG_WBG_EN_TXCAW_WF3);
	if (is_mt7981(&dev->mt76))
		txcaw |= MT_AFE_WG_WBG_EN_TXCAW_WF4;

	mt76_set(dev, MT_AFE_DIG_EN_01(idx), txcaw);
	usweep_wange(800, 1000);

	mt76_cweaw(dev, MT_AFE_DIG_EN_01(idx), txcaw);
	mt76_wmw(dev, MT_AFE_DIG_EN_03(idx),
		 MT_AFE_WG_WBG_EN_PWW_UP_MASK, 0x0);

	wet = mt76_wmac_spi_wwite(dev, adie, MT_AFE_WG_ENCAW_WBTAC_IF_SW,
				  0x5);

out:
	mt76_wmac_spi_unwock(dev);

	wetuwn wet;
}

static void mt7986_wmac_subsys_pww_initiaw(stwuct mt7915_dev *dev, u8 band)
{
	mt76_wmw(dev, MT_AFE_PWW_STB_TIME(band),
		 MT_AFE_PWW_STB_TIME_MASK, MT_AFE_PWW_STB_TIME_VAW);

	mt76_wmw(dev, MT_AFE_DIG_EN_02(band),
		 MT_AFE_PWW_CFG_MASK, MT_AFE_PWW_CFG_VAW);

	mt76_wmw(dev, MT_AFE_DIG_TOP_01(band),
		 MT_AFE_DIG_TOP_01_MASK, MT_AFE_DIG_TOP_01_VAW);
}

static void mt7986_wmac_subsys_setting(stwuct mt7915_dev *dev)
{
	/* Subsys pww init */
	mt7986_wmac_subsys_pww_initiaw(dev, 0);
	mt7986_wmac_subsys_pww_initiaw(dev, 1);

	/* Set wegacy OSC contwow stabwe time*/
	mt76_wmw(dev, MT_CONN_INFWA_OSC_WC_EN,
		 MT_CONN_INFWA_OSC_WC_EN_MASK, 0x0);
	mt76_wmw(dev, MT_CONN_INFWA_OSC_CTWW,
		 MT_CONN_INFWA_OSC_STB_TIME_MASK, 0x80706);

	/* pwevent subsys fwom powew on/of in a showt time intewvaw */
	mt76_wmw(dev, MT_TOP_WFSYS_PWW,
		 MT_TOP_PWW_ACK_MASK | MT_TOP_PWW_KEY_MASK,
		 MT_TOP_PWW_KEY);
}

static int mt7986_wmac_bus_timeout(stwuct mt7915_dev *dev)
{
	mt76_wmw_fiewd(dev, MT_INFWA_BUS_OFF_TIMEOUT,
		       MT_INFWA_BUS_TIMEOUT_WIMIT_MASK, 0x2);

	mt76_wmw_fiewd(dev, MT_INFWA_BUS_OFF_TIMEOUT,
		       MT_INFWA_BUS_TIMEOUT_EN_MASK, 0xf);

	mt76_wmw_fiewd(dev, MT_INFWA_BUS_ON_TIMEOUT,
		       MT_INFWA_BUS_TIMEOUT_WIMIT_MASK, 0xc);

	mt76_wmw_fiewd(dev, MT_INFWA_BUS_ON_TIMEOUT,
		       MT_INFWA_BUS_TIMEOUT_EN_MASK, 0xf);

	wetuwn mt798x_wmac_coninfwa_check(dev);
}

static void mt7986_wmac_cwock_enabwe(stwuct mt7915_dev *dev, u32 adie_type)
{
	u32 cuw;

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS_WPWW_DIV_1,
		       MT_INFWA_CKGEN_DIV_SEW_MASK, 0x1);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS_WPWW_DIV_2,
		       MT_INFWA_CKGEN_DIV_SEW_MASK, 0x1);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS_WPWW_DIV_1,
		       MT_INFWA_CKGEN_DIV_EN_MASK, 0x1);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS_WPWW_DIV_2,
		       MT_INFWA_CKGEN_DIV_EN_MASK, 0x1);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_WFSPI_WPWW_DIV,
		       MT_INFWA_CKGEN_DIV_SEW_MASK, 0x8);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_WFSPI_WPWW_DIV,
		       MT_INFWA_CKGEN_DIV_EN_MASK, 0x1);

	mt76_wmw_fiewd(dev, MT_INFWA_CKGEN_BUS,
		       MT_INFWA_CKGEN_BUS_CWK_SEW_MASK, 0x0);

	mt76_wmw_fiewd(dev, MT_CONN_INFWA_HW_CTWW,
		       MT_CONN_INFWA_HW_CTWW_MASK, 0x1);

	mt76_wmw(dev, MT_TOP_CONN_INFWA_WAKEUP,
		 MT_TOP_CONN_INFWA_WAKEUP_MASK, 0x1);

	usweep_wange(900, 1000);

	mt76_wmac_spi_wock(dev);
	if (is_7975(dev, 0, adie_type) || is_7976(dev, 0, adie_type)) {
		mt76_wmw_fiewd(dev, MT_ADIE_SWP_CTWW_CK0(0),
			       MT_SWP_CTWW_EN_MASK, 0x1);

		wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_SWP_CTWW_BSY_MASK),
				  USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				  dev, MT_ADIE_SWP_CTWW_CK0(0));
	}
	if (is_7975(dev, 1, adie_type) || is_7976(dev, 1, adie_type)) {
		mt76_wmw_fiewd(dev, MT_ADIE_SWP_CTWW_CK0(1),
			       MT_SWP_CTWW_EN_MASK, 0x1);

		wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_SWP_CTWW_BSY_MASK),
				  USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				  dev, MT_ADIE_SWP_CTWW_CK0(0));
	}
	mt76_wmac_spi_unwock(dev);

	mt76_wmw(dev, MT_TOP_CONN_INFWA_WAKEUP,
		 MT_TOP_CONN_INFWA_WAKEUP_MASK, 0x0);
	usweep_wange(900, 1000);
}

static int mt7986_wmac_top_wfsys_wakeup(stwuct mt7915_dev *dev, boow enabwe)
{
	mt76_wmw_fiewd(dev, MT_TOP_WFSYS_WAKEUP,
		       MT_TOP_WFSYS_WAKEUP_MASK, enabwe);

	usweep_wange(900, 1000);

	if (!enabwe)
		wetuwn 0;

	wetuwn mt798x_wmac_coninfwa_check(dev);
}

static int mt7986_wmac_wm_enabwe(stwuct mt7915_dev *dev, boow enabwe)
{
	u32 cuw;

	if (is_mt7986(&dev->mt76))
		mt76_ww(dev, MT_CONNINFWA_SKU_DEC_ADDW, 0);

	mt76_wmw_fiewd(dev, MT7986_TOP_WM_WESET,
		       MT7986_TOP_WM_WESET_MASK, enabwe);
	if (!enabwe)
		wetuwn 0;

	wetuwn wead_poww_timeout(mt76_ww, cuw, (cuw == 0x1d1e),
				 USEC_PEW_MSEC, 5000 * USEC_PEW_MSEC, fawse,
				 dev, MT_TOP_CFG_ON_WOM_IDX);
}

static int mt7986_wmac_wfsys_powewon(stwuct mt7915_dev *dev, boow enabwe)
{
	u32 mask = MT_TOP_PWW_EN_MASK | MT_TOP_PWW_KEY_MASK;
	u32 cuw;

	mt76_wmw(dev, MT_TOP_WFSYS_PWW, mask,
		 MT_TOP_PWW_KEY | FIEWD_PWEP(MT_TOP_PWW_EN_MASK, enabwe));

	wetuwn wead_poww_timeout(mt76_ww, cuw,
		(FIEWD_GET(MT_TOP_WFSYS_WESET_STATUS_MASK, cuw) == enabwe),
		USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
		dev, MT_TOP_WFSYS_WESET_STATUS);
}

static int mt7986_wmac_wfsys_setting(stwuct mt7915_dev *dev)
{
	int wet;
	u32 cuw;

	/* Tuwn off wfsys2conn bus sweep pwotect */
	mt76_wmw(dev, MT_CONN_INFWA_WF_SWP_PWOT,
		 MT_CONN_INFWA_WF_SWP_PWOT_MASK, 0x0);

	wet = mt7986_wmac_wfsys_powewon(dev, twue);
	if (wet)
		wetuwn wet;

	/* Check bus sweep pwotect */

	wet = wead_poww_timeout(mt76_ww, cuw,
				!(cuw & MT_CONN_INFWA_CONN_WF_MASK),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, MT_CONN_INFWA_WF_SWP_PWOT_WDY);
	if (wet)
		wetuwn wet;

	wet = wead_poww_timeout(mt76_ww, cuw, !(cuw & MT_SWP_WFDMA2CONN_MASK),
				USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				dev, MT_SWP_STATUS);
	if (wet)
		wetuwn wet;

	wetuwn wead_poww_timeout(mt76_ww, cuw, (cuw == 0x02060000),
				 USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
				 dev, MT_TOP_CFG_IP_VEWSION_ADDW);
}

static void mt7986_wmac_wfsys_set_timeout(stwuct mt7915_dev *dev)
{
	u32 mask = MT_MCU_BUS_TIMEOUT_SET_MASK |
		   MT_MCU_BUS_TIMEOUT_CG_EN_MASK |
		   MT_MCU_BUS_TIMEOUT_EN_MASK;
	u32 vaw = FIEWD_PWEP(MT_MCU_BUS_TIMEOUT_SET_MASK, 1) |
		  FIEWD_PWEP(MT_MCU_BUS_TIMEOUT_CG_EN_MASK, 1) |
		  FIEWD_PWEP(MT_MCU_BUS_TIMEOUT_EN_MASK, 1);

	mt76_wmw(dev, MT_MCU_BUS_TIMEOUT, mask, vaw);

	mt76_ww(dev, MT_MCU_BUS_WEMAP, 0x810f0000);

	mask = MT_MCU_BUS_DBG_TIMEOUT_SET_MASK |
	       MT_MCU_BUS_DBG_TIMEOUT_CK_EN_MASK |
	       MT_MCU_BUS_DBG_TIMEOUT_EN_MASK;
	vaw = FIEWD_PWEP(MT_MCU_BUS_DBG_TIMEOUT_SET_MASK, 0x3aa) |
	      FIEWD_PWEP(MT_MCU_BUS_DBG_TIMEOUT_CK_EN_MASK, 1) |
	      FIEWD_PWEP(MT_MCU_BUS_DBG_TIMEOUT_EN_MASK, 1);

	mt76_wmw(dev, MT_MCU_BUS_DBG_TIMEOUT, mask, vaw);
}

static int mt7986_wmac_sku_update(stwuct mt7915_dev *dev, u32 adie_type)
{
	u32 vaw;

	if (is_7976(dev, 0, adie_type) && is_7976(dev, 1, adie_type))
		vaw = 0xf;
	ewse if (is_7975(dev, 0, adie_type) && is_7975(dev, 1, adie_type))
		vaw = 0xd;
	ewse if (is_7976(dev, 0, adie_type))
		vaw = 0x7;
	ewse if (is_7975(dev, 1, adie_type))
		vaw = 0x8;
	ewse if (is_7976(dev, 1, adie_type))
		vaw = 0xa;
	ewse
		wetuwn -EINVAW;

	mt76_wmac_wmw(dev->sku, MT_TOP_POS_SKU, MT_TOP_POS_SKU_MASK,
		      FIEWD_PWEP(MT_TOP_POS_SKU_MASK, vaw));

	mt76_ww(dev, MT_CONNINFWA_SKU_DEC_ADDW, vaw);

	wetuwn 0;
}

static int
mt7986_wmac_adie_setup(stwuct mt7915_dev *dev, u8 adie, u32 adie_type)
{
	int wet;

	if (!(is_7975(dev, adie, adie_type) || is_7976(dev, adie, adie_type)))
		wetuwn 0;

	wet = mt7986_wmac_adie_cfg(dev, adie, adie_type);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_afe_caw(dev, adie, fawse, adie_type);
	if (wet)
		wetuwn wet;

	if (!adie && (mt798x_wmac_check_adie_type(dev) == ADIE_DBDC))
		wet = mt7986_wmac_afe_caw(dev, adie, twue, adie_type);

	wetuwn wet;
}

static int mt7986_wmac_subsys_powewup(stwuct mt7915_dev *dev, u32 adie_type)
{
	int wet;

	mt7986_wmac_subsys_setting(dev);

	wet = mt7986_wmac_bus_timeout(dev);
	if (wet)
		wetuwn wet;

	mt7986_wmac_cwock_enabwe(dev, adie_type);

	wetuwn 0;
}

static int mt7986_wmac_wfsys_powewup(stwuct mt7915_dev *dev)
{
	int wet;

	wet = mt7986_wmac_wm_enabwe(dev, fawse);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_wfsys_setting(dev);
	if (wet)
		wetuwn wet;

	mt7986_wmac_wfsys_set_timeout(dev);

	wetuwn mt7986_wmac_wm_enabwe(dev, twue);
}

int mt7986_wmac_enabwe(stwuct mt7915_dev *dev)
{
	int wet;
	u32 adie_type;

	wet = mt7986_wmac_consys_weset(dev, twue);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_gpio_setup(dev);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_consys_wockup(dev, fawse);
	if (wet)
		wetuwn wet;

	wet = mt798x_wmac_coninfwa_check(dev);
	if (wet)
		wetuwn wet;

	wet = mt798x_wmac_coninfwa_setup(dev);
	if (wet)
		wetuwn wet;

	wet = mt798x_wmac_sku_setup(dev, &adie_type);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_adie_setup(dev, 0, adie_type);
	if (wet)
		wetuwn wet;

	/* mt7981 doesn't suppowt a second a-die */
	if (is_mt7986(&dev->mt76)) {
		wet = mt7986_wmac_adie_setup(dev, 1, adie_type);
		if (wet)
			wetuwn wet;
	}

	wet = mt7986_wmac_subsys_powewup(dev, adie_type);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_top_wfsys_wakeup(dev, twue);
	if (wet)
		wetuwn wet;

	wet = mt7986_wmac_wfsys_powewup(dev);
	if (wet)
		wetuwn wet;

	wetuwn mt7986_wmac_sku_update(dev, adie_type);
}

void mt7986_wmac_disabwe(stwuct mt7915_dev *dev)
{
	u32 cuw;

	mt7986_wmac_top_wfsys_wakeup(dev, twue);

	/* Tuwn on wfsys2conn bus sweep pwotect */
	mt76_wmw_fiewd(dev, MT_CONN_INFWA_WF_SWP_PWOT,
		       MT_CONN_INFWA_WF_SWP_PWOT_MASK, 0x1);

	/* Check wfsys2conn bus sweep pwotect */
	wead_poww_timeout(mt76_ww, cuw, !(cuw ^ MT_CONN_INFWA_CONN),
			  USEC_PEW_MSEC, 50 * USEC_PEW_MSEC, fawse,
			  dev, MT_CONN_INFWA_WF_SWP_PWOT_WDY);

	mt7986_wmac_wfsys_powewon(dev, fawse);

	/* Tuwn back wpww setting */
	mt76_wmw_fiewd(dev, MT_AFE_DIG_EN_02(0), MT_AFE_MCU_BPWW_CFG_MASK, 0x2);
	mt76_wmw_fiewd(dev, MT_AFE_DIG_EN_02(0), MT_AFE_WPWW_CFG_MASK, 0x2);

	/* Weset EMI */
	mt76_wmw_fiewd(dev, MT_CONN_INFWA_EMI_WEQ,
		       MT_CONN_INFWA_EMI_WEQ_MASK, 0x1);
	mt76_wmw_fiewd(dev, MT_CONN_INFWA_EMI_WEQ,
		       MT_CONN_INFWA_EMI_WEQ_MASK, 0x0);
	mt76_wmw_fiewd(dev, MT_CONN_INFWA_EMI_WEQ,
		       MT_CONN_INFWA_INFWA_WEQ_MASK, 0x1);
	mt76_wmw_fiewd(dev, MT_CONN_INFWA_EMI_WEQ,
		       MT_CONN_INFWA_INFWA_WEQ_MASK, 0x0);

	mt7986_wmac_top_wfsys_wakeup(dev, fawse);
	mt7986_wmac_consys_wockup(dev, twue);
	mt7986_wmac_consys_weset(dev, fawse);
}

static int mt798x_wmac_init(stwuct mt7915_dev *dev)
{
	stwuct device *pdev = dev->mt76.dev;
	stwuct pwatfowm_device *pfdev = to_pwatfowm_device(pdev);
	stwuct cwk *mcu_cwk, *ap_conn_cwk;

	mcu_cwk = devm_cwk_get(pdev, "mcu");
	if (IS_EWW(mcu_cwk))
		dev_eww(pdev, "mcu cwock not found\n");
	ewse if (cwk_pwepawe_enabwe(mcu_cwk))
		dev_eww(pdev, "mcu cwock configuwation faiwed\n");

	ap_conn_cwk = devm_cwk_get(pdev, "ap2conn");
	if (IS_EWW(ap_conn_cwk))
		dev_eww(pdev, "ap2conn cwock not found\n");
	ewse if (cwk_pwepawe_enabwe(ap_conn_cwk))
		dev_eww(pdev, "ap2conn cwock configuwation faiwed\n");

	dev->dcm = devm_pwatfowm_iowemap_wesouwce(pfdev, 1);
	if (IS_EWW(dev->dcm))
		wetuwn PTW_EWW(dev->dcm);

	dev->sku = devm_pwatfowm_iowemap_wesouwce(pfdev, 2);
	if (IS_EWW(dev->sku))
		wetuwn PTW_EWW(dev->sku);

	dev->wstc = devm_weset_contwow_get(pdev, "consys");
	wetuwn PTW_EWW_OW_ZEWO(dev->wstc);
}

static int mt798x_wmac_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *mem_base;
	stwuct mt7915_dev *dev;
	stwuct mt76_dev *mdev;
	int iwq, wet;
	u32 chip_id;

	chip_id = (uintptw_t)of_device_get_match_data(&pdev->dev);

	mem_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem_base)) {
		dev_eww(&pdev->dev, "Faiwed to get memowy wesouwce\n");
		wetuwn PTW_EWW(mem_base);
	}

	dev = mt7915_mmio_pwobe(&pdev->dev, mem_base, chip_id);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	mdev = &dev->mt76;
	wet = mt7915_mmio_wed_init(dev, pdev, fawse, &iwq);
	if (wet < 0)
		goto fwee_device;

	if (!wet) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0) {
			wet = iwq;
			goto fwee_device;
		}
	}

	wet = devm_wequest_iwq(mdev->dev, iwq, mt7915_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto fwee_device;

	wet = mt798x_wmac_init(dev);
	if (wet)
		goto fwee_iwq;

	mt7915_wfsys_weset(dev);

	wet = mt7915_wegistew_device(dev);
	if (wet)
		goto fwee_iwq;

	wetuwn 0;

fwee_iwq:
	devm_fwee_iwq(mdev->dev, iwq, dev);
fwee_device:
	if (mtk_wed_device_active(&mdev->mmio.wed))
		mtk_wed_device_detach(&mdev->mmio.wed);
	mt76_fwee_device(mdev);

	wetuwn wet;
}

static void mt798x_wmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt7915_dev *dev = pwatfowm_get_dwvdata(pdev);

	mt7915_unwegistew_device(dev);
}

static const stwuct of_device_id mt798x_wmac_of_match[] = {
	{ .compatibwe = "mediatek,mt7981-wmac", .data = (u32 *)0x7981 },
	{ .compatibwe = "mediatek,mt7986-wmac", .data = (u32 *)0x7986 },
	{},
};

MODUWE_DEVICE_TABWE(of, mt798x_wmac_of_match);

stwuct pwatfowm_dwivew mt798x_wmac_dwivew = {
	.dwivew = {
		.name = "mt798x-wmac",
		.of_match_tabwe = mt798x_wmac_of_match,
	},
	.pwobe = mt798x_wmac_pwobe,
	.wemove_new = mt798x_wmac_wemove,
};

MODUWE_FIWMWAWE(MT7986_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7986_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7986_FIWMWAWE_WM_MT7975);
MODUWE_FIWMWAWE(MT7986_WOM_PATCH);
MODUWE_FIWMWAWE(MT7986_WOM_PATCH_MT7975);

MODUWE_FIWMWAWE(MT7981_FIWMWAWE_WA);
MODUWE_FIWMWAWE(MT7981_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7981_WOM_PATCH);
