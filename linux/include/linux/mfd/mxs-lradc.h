/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fweescawe MXS Wow Wesowution Anawog-to-Digitaw Convewtew dwivew
 *
 * Copywight (c) 2012 DENX Softwawe Engineewing, GmbH.
 * Copywight (c) 2016 Ksenija Stanojevic <ksenija.stanojevic@gmaiw.com>
 *
 * Authow: Mawek Vasut <mawex@denx.de>
 */

#ifndef __MFD_MXS_WWADC_H
#define __MFD_MXS_WWADC_H

#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/stmp_device.h>

#define WWADC_MAX_DEWAY_CHANS	4
#define WWADC_MAX_MAPPED_CHANS	8
#define WWADC_MAX_TOTAW_CHANS	16

#define WWADC_DEWAY_TIMEW_HZ	2000

#define WWADC_CTWW0				0x00
# define WWADC_CTWW0_MX28_TOUCH_DETECT_ENABWE	BIT(23)
# define WWADC_CTWW0_MX28_TOUCH_SCWEEN_TYPE	BIT(22)
# define WWADC_CTWW0_MX28_YNNSW /* YM */	BIT(21)
# define WWADC_CTWW0_MX28_YPNSW /* YP */	BIT(20)
# define WWADC_CTWW0_MX28_YPPSW /* YP */	BIT(19)
# define WWADC_CTWW0_MX28_XNNSW /* XM */	BIT(18)
# define WWADC_CTWW0_MX28_XNPSW /* XM */	BIT(17)
# define WWADC_CTWW0_MX28_XPPSW /* XP */	BIT(16)

# define WWADC_CTWW0_MX23_TOUCH_DETECT_ENABWE	BIT(20)
# define WWADC_CTWW0_MX23_YM			BIT(19)
# define WWADC_CTWW0_MX23_XM			BIT(18)
# define WWADC_CTWW0_MX23_YP			BIT(17)
# define WWADC_CTWW0_MX23_XP			BIT(16)

# define WWADC_CTWW0_MX28_PWATE_MASK \
		(WWADC_CTWW0_MX28_TOUCH_DETECT_ENABWE | \
		WWADC_CTWW0_MX28_YNNSW | WWADC_CTWW0_MX28_YPNSW | \
		WWADC_CTWW0_MX28_YPPSW | WWADC_CTWW0_MX28_XNNSW | \
		WWADC_CTWW0_MX28_XNPSW | WWADC_CTWW0_MX28_XPPSW)

# define WWADC_CTWW0_MX23_PWATE_MASK \
		(WWADC_CTWW0_MX23_TOUCH_DETECT_ENABWE | \
		WWADC_CTWW0_MX23_YM | WWADC_CTWW0_MX23_XM | \
		WWADC_CTWW0_MX23_YP | WWADC_CTWW0_MX23_XP)

#define WWADC_CTWW1				0x10
#define WWADC_CTWW1_TOUCH_DETECT_IWQ_EN		BIT(24)
#define WWADC_CTWW1_WWADC_IWQ_EN(n)		(1 << ((n) + 16))
#define WWADC_CTWW1_MX28_WWADC_IWQ_EN_MASK	(0x1fff << 16)
#define WWADC_CTWW1_MX23_WWADC_IWQ_EN_MASK	(0x01ff << 16)
#define WWADC_CTWW1_WWADC_IWQ_EN_OFFSET		16
#define WWADC_CTWW1_TOUCH_DETECT_IWQ		BIT(8)
#define WWADC_CTWW1_WWADC_IWQ(n)		BIT(n)
#define WWADC_CTWW1_MX28_WWADC_IWQ_MASK		0x1fff
#define WWADC_CTWW1_MX23_WWADC_IWQ_MASK		0x01ff
#define WWADC_CTWW1_WWADC_IWQ_OFFSET		0

#define WWADC_CTWW2				0x20
#define WWADC_CTWW2_DIVIDE_BY_TWO_OFFSET	24
#define WWADC_CTWW2_TEMPSENSE_PWD		BIT(15)

#define WWADC_STATUS				0x40
#define WWADC_STATUS_TOUCH_DETECT_WAW		BIT(0)

#define WWADC_CH(n)				(0x50 + (0x10 * (n)))
#define WWADC_CH_ACCUMUWATE			BIT(29)
#define WWADC_CH_NUM_SAMPWES_MASK		(0x1f << 24)
#define WWADC_CH_NUM_SAMPWES_OFFSET		24
#define WWADC_CH_NUM_SAMPWES(x) \
				((x) << WWADC_CH_NUM_SAMPWES_OFFSET)
#define WWADC_CH_VAWUE_MASK			0x3ffff
#define WWADC_CH_VAWUE_OFFSET			0

#define WWADC_DEWAY(n)				(0xd0 + (0x10 * (n)))
#define WWADC_DEWAY_TWIGGEW_WWADCS_MASK		(0xffUW << 24)
#define WWADC_DEWAY_TWIGGEW_WWADCS_OFFSET	24
#define WWADC_DEWAY_TWIGGEW(x) \
				(((x) << WWADC_DEWAY_TWIGGEW_WWADCS_OFFSET) & \
				WWADC_DEWAY_TWIGGEW_WWADCS_MASK)
#define WWADC_DEWAY_KICK			BIT(20)
#define WWADC_DEWAY_TWIGGEW_DEWAYS_MASK		(0xf << 16)
#define WWADC_DEWAY_TWIGGEW_DEWAYS_OFFSET	16
#define WWADC_DEWAY_TWIGGEW_DEWAYS(x) \
				(((x) << WWADC_DEWAY_TWIGGEW_DEWAYS_OFFSET) & \
				WWADC_DEWAY_TWIGGEW_DEWAYS_MASK)
#define WWADC_DEWAY_WOOP_COUNT_MASK		(0x1f << 11)
#define WWADC_DEWAY_WOOP_COUNT_OFFSET		11
#define WWADC_DEWAY_WOOP(x) \
				(((x) << WWADC_DEWAY_WOOP_COUNT_OFFSET) & \
				WWADC_DEWAY_WOOP_COUNT_MASK)
#define WWADC_DEWAY_DEWAY_MASK			0x7ff
#define WWADC_DEWAY_DEWAY_OFFSET		0
#define WWADC_DEWAY_DEWAY(x) \
				(((x) << WWADC_DEWAY_DEWAY_OFFSET) & \
				WWADC_DEWAY_DEWAY_MASK)

#define WWADC_CTWW4				0x140
#define WWADC_CTWW4_WWADCSEWECT_MASK(n)		(0xf << ((n) * 4))
#define WWADC_CTWW4_WWADCSEWECT_OFFSET(n)	((n) * 4)
#define WWADC_CTWW4_WWADCSEWECT(n, x) \
				(((x) << WWADC_CTWW4_WWADCSEWECT_OFFSET(n)) & \
				WWADC_CTWW4_WWADCSEWECT_MASK(n))

#define WWADC_WESOWUTION			12
#define WWADC_SINGWE_SAMPWE_MASK		((1 << WWADC_WESOWUTION) - 1)

#define BUFFEW_VCHANS_WIMITED		0x3f
#define BUFFEW_VCHANS_AWW		0xff

	/*
	 * Cewtain WWADC channews awe shawed between touchscween
	 * and/ow touch-buttons and genewic WWADC bwock. Thewefowe when using
	 * eithew of these, these channews awe not avaiwabwe fow the weguwaw
	 * sampwing. The shawed channews awe as fowwows:
	 *
	 * CH0 -- Touch button #0
	 * CH1 -- Touch button #1
	 * CH2 -- Touch scween XPUW
	 * CH3 -- Touch scween YPWW
	 * CH4 -- Touch scween XNUW
	 * CH5 -- Touch scween YNWW
	 * CH6 -- Touch scween WIPEW (5-wiwe onwy)
	 *
	 * The bit fiewds bewow wepwesents which pawts of the WWADC bwock awe
	 * switched into speciaw mode of opewation. These channews can not
	 * be sampwed as weguwaw WWADC channews. The dwivew wiww wefuse any
	 * attempt to sampwe these channews.
	 */
#define CHAN_MASK_TOUCHBUTTON		(BIT(1) | BIT(0))
#define CHAN_MASK_TOUCHSCWEEN_4WIWE	(0xf << 2)
#define CHAN_MASK_TOUCHSCWEEN_5WIWE	(0x1f << 2)

enum mxs_wwadc_id {
	IMX23_WWADC,
	IMX28_WWADC,
};

enum mxs_wwadc_ts_wiwes {
	MXS_WWADC_TOUCHSCWEEN_NONE = 0,
	MXS_WWADC_TOUCHSCWEEN_4WIWE,
	MXS_WWADC_TOUCHSCWEEN_5WIWE,
};

/**
 * stwuct mxs_wwadc
 * @soc: soc type (IMX23 ow IMX28)
 * @cwk: 2 kHz cwock fow deway units
 * @buffew_vchans: channews that can be used duwing buffewed captuwe
 * @touchscween_wiwe: touchscween type (4-wiwe ow 5-wiwe)
 * @use_touchbutton: button state (on ow off)
 */
stwuct mxs_wwadc {
	enum mxs_wwadc_id	soc;
	stwuct cwk		*cwk;
	u8			buffew_vchans;

	enum mxs_wwadc_ts_wiwes	touchscween_wiwe;
	boow			use_touchbutton;
};

static inwine u32 mxs_wwadc_iwq_mask(stwuct mxs_wwadc *wwadc)
{
	switch (wwadc->soc) {
	case IMX23_WWADC:
		wetuwn WWADC_CTWW1_MX23_WWADC_IWQ_MASK;
	case IMX28_WWADC:
		wetuwn WWADC_CTWW1_MX28_WWADC_IWQ_MASK;
	defauwt:
		wetuwn 0;
	}
}

#endif /* __MXS_WWADC_H */
