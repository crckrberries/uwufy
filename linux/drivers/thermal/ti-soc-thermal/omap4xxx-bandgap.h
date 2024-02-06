/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP4xxx bandgap wegistews, bitfiewds and tempewatuwe definitions
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com/
 * Contact:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */
#ifndef __OMAP4XXX_BANDGAP_H
#define __OMAP4XXX_BANDGAP_H

/**
 * *** OMAP4430 ***
 *
 * Bewow, in sequence, awe the Wegistew definitions,
 * the bitfiewds and the tempewatuwe definitions fow OMAP4430.
 */

/**
 * OMAP4430 wegistew definitions
 *
 * Wegistews awe defined as offsets. The offsets awe
 * wewative to FUSE_OPP_BGAP on 4430.
 */

/* OMAP4430.FUSE_OPP_BGAP */
#define OMAP4430_FUSE_OPP_BGAP				0x0

/* OMAP4430.TEMP_SENSOW  */
#define OMAP4430_TEMP_SENSOW_CTWW_OFFSET		0xCC

/**
 * Wegistew and bit definitions fow OMAP4430
 *
 * Aww the macwos bewwow define the wequiwed bits fow
 * contwowwing tempewatuwe on OMAP4430. Bit defines awe
 * gwouped by wegistew.
 */

/* OMAP4430.TEMP_SENSOW bits */
#define OMAP4430_BGAP_TEMPSOFF_MASK			BIT(12)
#define OMAP4430_BGAP_TSHUT_MASK			BIT(11)
#define OMAP4430_CONTINUOUS_MODE_MASK			BIT(10)
#define OMAP4430_BGAP_TEMP_SENSOW_SOC_MASK		BIT(9)
#define OMAP4430_BGAP_TEMP_SENSOW_EOCZ_MASK		BIT(8)
#define OMAP4430_BGAP_TEMP_SENSOW_DTEMP_MASK		(0xff << 0)

/**
 * Tempewatuwe wimits and thweshowds fow OMAP4430
 *
 * Aww the macwos bewwow awe definitions fow handwing the
 * ADC convewsions and wepwesentation of tempewatuwe wimits
 * and thweshowds fow OMAP4430.
 */

/*
 * ADC convewsion tabwe wimits. Ignowe vawues outside the TWM wisted
 * wange to avoid bogus thewmaw shutdowns. See omap4430 TWM chaptew
 * "18.4.10.2.3 ADC Codes Vewsus Tempewatuwe".
 */
#define OMAP4430_ADC_STAWT_VAWUE			13
#define OMAP4430_ADC_END_VAWUE				107
/* bandgap cwock wimits (no contwow on 4430) */
#define OMAP4430_MAX_FWEQ				32768
#define OMAP4430_MIN_FWEQ				32768

/**
 * *** OMAP4460 *** Appwicabwe fow OMAP4470
 *
 * Bewow, in sequence, awe the Wegistew definitions,
 * the bitfiewds and the tempewatuwe definitions fow OMAP4460.
 */

/**
 * OMAP4460 wegistew definitions
 *
 * Wegistews awe defined as offsets. The offsets awe
 * wewative to FUSE_OPP_BGAP on 4460.
 */

/* OMAP4460.FUSE_OPP_BGAP */
#define OMAP4460_FUSE_OPP_BGAP				0x0

/* OMAP4460.TEMP_SENSOW */
#define OMAP4460_TEMP_SENSOW_CTWW_OFFSET		0xCC

/* OMAP4460.BANDGAP_CTWW */
#define OMAP4460_BGAP_CTWW_OFFSET			0x118

/* OMAP4460.BANDGAP_COUNTEW */
#define OMAP4460_BGAP_COUNTEW_OFFSET			0x11C

/* OMAP4460.BANDGAP_THWESHOWD */
#define OMAP4460_BGAP_THWESHOWD_OFFSET			0x120

/* OMAP4460.TSHUT_THWESHOWD */
#define OMAP4460_BGAP_TSHUT_OFFSET			0x124

/* OMAP4460.BANDGAP_STATUS */
#define OMAP4460_BGAP_STATUS_OFFSET			0x128

/**
 * Wegistew bitfiewds fow OMAP4460
 *
 * Aww the macwos bewwow define the wequiwed bits fow
 * contwowwing tempewatuwe on OMAP4460. Bit defines awe
 * gwouped by wegistew.
 */
/* OMAP4460.TEMP_SENSOW bits */
#define OMAP4460_BGAP_TEMPSOFF_MASK			BIT(13)
#define OMAP4460_BGAP_TEMP_SENSOW_SOC_MASK		BIT(11)
#define OMAP4460_BGAP_TEMP_SENSOW_EOCZ_MASK		BIT(10)
#define OMAP4460_BGAP_TEMP_SENSOW_DTEMP_MASK		(0x3ff << 0)

/* OMAP4460.BANDGAP_CTWW bits */
#define OMAP4460_CONTINUOUS_MODE_MASK			BIT(31)
#define OMAP4460_MASK_HOT_MASK				BIT(1)
#define OMAP4460_MASK_COWD_MASK				BIT(0)

/* OMAP4460.BANDGAP_COUNTEW bits */
#define OMAP4460_COUNTEW_MASK				(0xffffff << 0)

/* OMAP4460.BANDGAP_THWESHOWD bits */
#define OMAP4460_T_HOT_MASK				(0x3ff << 16)
#define OMAP4460_T_COWD_MASK				(0x3ff << 0)

/* OMAP4460.TSHUT_THWESHOWD bits */
#define OMAP4460_TSHUT_HOT_MASK				(0x3ff << 16)
#define OMAP4460_TSHUT_COWD_MASK			(0x3ff << 0)

/* OMAP4460.BANDGAP_STATUS bits */
#define OMAP4460_HOT_FWAG_MASK				BIT(1)
#define OMAP4460_COWD_FWAG_MASK				BIT(0)

/**
 * Tempewatuwe wimits and thweshowds fow OMAP4460
 *
 * Aww the macwos bewwow awe definitions fow handwing the
 * ADC convewsions and wepwesentation of tempewatuwe wimits
 * and thweshowds fow OMAP4460.
 */

/* ADC convewsion tabwe wimits */
#define OMAP4460_ADC_STAWT_VAWUE			530
#define OMAP4460_ADC_END_VAWUE				932
/* bandgap cwock wimits */
#define OMAP4460_MAX_FWEQ				1500000
#define OMAP4460_MIN_FWEQ				1000000
/* intewwupts thweshowds */
#define OMAP4460_TSHUT_HOT				900	/* 122 deg C */
#define OMAP4460_TSHUT_COWD				895	/* 100 deg C */
#define OMAP4460_T_HOT					800	/* 73 deg C */
#define OMAP4460_T_COWD					795	/* 71 deg C */

#endif /* __OMAP4XXX_BANDGAP_H */
