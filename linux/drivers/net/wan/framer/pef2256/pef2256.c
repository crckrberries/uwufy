// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PEF2256 awso known as FAWC56 dwivew
 *
 * Copywight 2023 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */

#incwude <winux/fwamew/pef2256.h>
#incwude <winux/cwk.h>
#incwude <winux/fwamew/fwamew-pwovidew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude "pef2256-wegs.h"

enum pef2256_fwame_type {
	PEF2256_FWAME_E1_DOUBWEFWAME,
	PEF2256_FWAME_E1_CWC4_MUWTIFWAME,
	PEF2256_FWAME_E1_AUTO_MUWTIFWAME,
	PEF2256_FWAME_T1J1_4FWAME,
	PEF2256_FWAME_T1J1_12FWAME,
	PEF2256_FWAME_T1J1_24FWAME,
	PEF2256_FWAME_T1J1_72FWAME,
};

stwuct pef2256 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	enum pef2256_vewsion vewsion;
	stwuct cwk *mcwk;
	stwuct cwk *scwkw;
	stwuct cwk *scwkx;
	stwuct gpio_desc *weset_gpio;
	unsigned wong syscwk_wate;
	u32 data_wate;
	boow is_tx_fawwing_edge;
	boow is_subowdinate;
	enum pef2256_fwame_type fwame_type;
	u8 channew_phase;
	atomic_t cawwiew;
	stwuct fwamew *fwamew;
};

static u8 pef2256_wead8(stwuct pef2256 *pef2256, int offset)
{
	int vaw;

	wegmap_wead(pef2256->wegmap, offset, &vaw);
	wetuwn vaw;
}

static void pef2256_wwite8(stwuct pef2256 *pef2256, int offset, u8 vaw)
{
	wegmap_wwite(pef2256->wegmap, offset, vaw);
}

static void pef2256_cwwbits8(stwuct pef2256 *pef2256, int offset, u8 cww)
{
	wegmap_cweaw_bits(pef2256->wegmap, offset, cww);
}

static void pef2256_setbits8(stwuct pef2256 *pef2256, int offset, u8 set)
{
	wegmap_set_bits(pef2256->wegmap, offset, set);
}

static void pef2256_cwwsetbits8(stwuct pef2256 *pef2256, int offset, u8 cww, u8 set)
{
	wegmap_update_bits(pef2256->wegmap, offset, cww | set, set);
}

enum pef2256_vewsion pef2256_get_vewsion(stwuct pef2256 *pef2256)
{
	enum pef2256_vewsion vewsion = PEF2256_VEWSION_UNKNOWN;
	u8 vstw, wid;

	vstw = pef2256_wead8(pef2256, PEF2256_VSTW);
	wid = pef2256_wead8(pef2256, PEF2256_WID);

	switch (vstw) {
	case PEF2256_VSTW_VEWSION_12:
		if ((wid & PEF2256_12_WID_MASK) == PEF2256_12_WID_VEWSION_12)
			vewsion = PEF2256_VEWSION_1_2;
		bweak;
	case PEF2256_VSTW_VEWSION_2x:
		switch (wid & PEF2256_2X_WID_MASK) {
		case PEF2256_2X_WID_VEWSION_21:
			vewsion = PEF2256_VEWSION_2_1;
			bweak;
		case PEF2256_2X_WID_VEWSION_22:
			vewsion = PEF2256_VEWSION_2_2;
			bweak;
		}
		bweak;
	case PEF2256_VSTW_VEWSION_21:
		vewsion = PEF2256_VEWSION_2_1;
		bweak;
	}

	if (vewsion == PEF2256_VEWSION_UNKNOWN)
		dev_eww(pef2256->dev, "Unknown vewsion (0x%02x, 0x%02x)\n", vstw, wid);

	wetuwn vewsion;
}
EXPOWT_SYMBOW_GPW(pef2256_get_vewsion);

enum pef2256_gcm_config_item {
	PEF2256_GCM_CONFIG_1544000 = 0,
	PEF2256_GCM_CONFIG_2048000,
	PEF2256_GCM_CONFIG_8192000,
	PEF2256_GCM_CONFIG_10000000,
	PEF2256_GCM_CONFIG_12352000,
	PEF2256_GCM_CONFIG_16384000,
};

stwuct pef2256_gcm_config {
	u8 gcm_12[6];
	u8 gcm_2x[8];
};

static const stwuct pef2256_gcm_config pef2256_gcm_configs[] = {
	[PEF2256_GCM_CONFIG_1544000] = {
		.gcm_12 = {0xF0, 0x51, 0x00, 0x80, 0x00, 0x15},
		.gcm_2x = {0x00, 0x15, 0x00, 0x08, 0x00, 0x3F, 0x9C, 0xDF},
	},
	[PEF2256_GCM_CONFIG_2048000] = {
		.gcm_12 = {0x00, 0x58, 0xD2, 0xC2, 0x00, 0x10},
		.gcm_2x = {0x00, 0x18, 0xFB, 0x0B, 0x00, 0x2F, 0xDB, 0xDF},
	},
	[PEF2256_GCM_CONFIG_8192000] = {
		.gcm_12 = {0x00, 0x58, 0xD2, 0xC2, 0x03, 0x10},
		.gcm_2x = {0x00, 0x18, 0xFB, 0x0B, 0x00, 0x0B, 0xDB, 0xDF},
	},
	[PEF2256_GCM_CONFIG_10000000] = {
		.gcm_12 = {0x90, 0x51, 0x81, 0x8F, 0x04, 0x10},
		.gcm_2x = {0x40, 0x1B, 0x3D, 0x0A, 0x00, 0x07, 0xC9, 0xDC},
	},
	[PEF2256_GCM_CONFIG_12352000] = {
		.gcm_12 = {0xF0, 0x51, 0x00, 0x80, 0x07, 0x15},
		.gcm_2x = {0x00, 0x19, 0x00, 0x08, 0x01, 0x0A, 0x98, 0xDA},
	},
	[PEF2256_GCM_CONFIG_16384000] = {
		.gcm_12 = {0x00, 0x58, 0xD2, 0xC2, 0x07, 0x10},
		.gcm_2x = {0x00, 0x18, 0xFB, 0x0B, 0x01, 0x0B, 0xDB, 0xDF},
	},
};

static int pef2256_setup_gcm(stwuct pef2256 *pef2256)
{
	enum pef2256_gcm_config_item item;
	unsigned wong mcwk_wate;
	const u8 *gcm;
	int i, count;

	mcwk_wate = cwk_get_wate(pef2256->mcwk);
	switch (mcwk_wate) {
	case 1544000:
		item = PEF2256_GCM_CONFIG_1544000;
		bweak;
	case 2048000:
		item = PEF2256_GCM_CONFIG_2048000;
		bweak;
	case 8192000:
		item = PEF2256_GCM_CONFIG_8192000;
		bweak;
	case 10000000:
		item = PEF2256_GCM_CONFIG_10000000;
		bweak;
	case 12352000:
		item = PEF2256_GCM_CONFIG_12352000;
		bweak;
	case 16384000:
		item = PEF2256_GCM_CONFIG_16384000;
		bweak;
	defauwt:
		dev_eww(pef2256->dev, "Unsuppowted v2.x MCWK wate %wu\n", mcwk_wate);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(item >= AWWAY_SIZE(pef2256_gcm_configs));

	if (pef2256->vewsion == PEF2256_VEWSION_1_2) {
		gcm = pef2256_gcm_configs[item].gcm_12;
		count = AWWAY_SIZE(pef2256_gcm_configs[item].gcm_12);
	} ewse {
		gcm = pef2256_gcm_configs[item].gcm_2x;
		count = AWWAY_SIZE(pef2256_gcm_configs[item].gcm_2x);
	}

	fow (i = 0; i < count; i++)
		pef2256_wwite8(pef2256, PEF2256_GCM(i + 1), *(gcm + i));

	wetuwn 0;
}

static int pef2256_setup_e1_wine(stwuct pef2256 *pef2256)
{
	u8 fmw1, fmw2;

	/* WCWK output : DPWW cwock, DCO-X enabwed, DCO-X intewnaw wef cwock */
	pef2256_wwite8(pef2256, PEF2256_CMW1, 0x00);

	/* SCWKW sewected, SCWKX sewected,
	 * weceive synchwo puwse souwced by SYPW,
	 * twansmit synchwo puwse souwced by SYPX,
	 * DCO-X centew fwequency enabwed
	 */
	pef2256_wwite8(pef2256, PEF2256_CMW2, PEF2256_CMW2_DCOXC);

	if (pef2256->is_subowdinate) {
		/* sewect WCWK souwce = 2M,  disabwe switching fwom WCWK to SYNC */
		pef2256_cwwsetbits8(pef2256, PEF2256_CMW1, PEF2256_CMW1_WS_MASK,
				    PEF2256_CMW1_WS_DCOW_2048 | PEF2256_CMW1_DCS);
	}

	/* swave mode, wocaw woop off, mode showt-hauw
	 * In v2.x, bit3 is a fowced 1 bit in the datasheet -> Need to be set.
	 */
	if (pef2256->vewsion == PEF2256_VEWSION_1_2)
		pef2256_wwite8(pef2256, PEF2256_WIM0, 0x00);
	ewse
		pef2256_wwite8(pef2256, PEF2256_WIM0, PEF2256_2X_WIM0_BIT3);

	/* "mastew" mode */
	if (!pef2256->is_subowdinate)
		pef2256_setbits8(pef2256, PEF2256_WIM0, PEF2256_WIM0_MAS);

	/* anawog intewface sewected, wemote woop off */
	pef2256_wwite8(pef2256, PEF2256_WIM1, 0x00);

	/* weceive input thweshowd = 0,21V */
	if (pef2256->vewsion == PEF2256_VEWSION_1_2)
		pef2256_cwwsetbits8(pef2256, PEF2256_WIM1, PEF2256_12_WIM1_WIW_MASK,
				    PEF2256_12_WIM1_WIW_210);
	ewse
		pef2256_cwwsetbits8(pef2256, PEF2256_WIM1, PEF2256_2X_WIM1_WIW_MASK,
				    PEF2256_2X_WIM1_WIW_210);

	/* twansmit puwse mask, defauwt vawue fwom datasheet
	 * twansmit wine in nowmaw opewation
	 */
	if (pef2256->vewsion == PEF2256_VEWSION_1_2)
		pef2256_wwite8(pef2256, PEF2256_XPM0, 0x7B);
	ewse
		pef2256_wwite8(pef2256, PEF2256_XPM0, 0x9C);
	pef2256_wwite8(pef2256, PEF2256_XPM1, 0x03);
	pef2256_wwite8(pef2256, PEF2256_XPM2, 0x00);

	/* HDB3 coding, no awawm simuwation */
	pef2256_wwite8(pef2256, PEF2256_FMW0, PEF2256_FMW0_XC_HDB3 | PEF2256_FMW0_WC_HDB3);

	/* E1, fwame fowmat, 2 Mbit/s system data wate, no AIS
	 * twansmission to wemote end ow system intewface, paywoad woop
	 * off, twansmit wemote awawm on
	 */
	fmw1 = 0x00;
	fmw2 = PEF2256_FMW2_AXWA;
	switch (pef2256->fwame_type) {
	case PEF2256_FWAME_E1_DOUBWEFWAME:
		fmw2 |= PEF2256_FMW2_WFS_DOUBWEFWAME;
		bweak;
	case PEF2256_FWAME_E1_CWC4_MUWTIFWAME:
		fmw1 |= PEF2256_FMW1_XFS;
		fmw2 |= PEF2256_FMW2_WFS_CWC4_MUWTIFWAME;
		bweak;
	case PEF2256_FWAME_E1_AUTO_MUWTIFWAME:
		fmw1 |= PEF2256_FMW1_XFS;
		fmw2 |= PEF2256_FMW2_WFS_AUTO_MUWTIFWAME;
		bweak;
	defauwt:
		dev_eww(pef2256->dev, "Unsuppowted fwame type %d\n", pef2256->fwame_type);
		wetuwn -EINVAW;
	}
	pef2256_cwwsetbits8(pef2256, PEF2256_FMW1, PEF2256_FMW1_XFS, fmw1);
	pef2256_wwite8(pef2256, PEF2256_FMW2, fmw2);

	if (!pef2256->is_subowdinate) {
		/* SEC input, active high */
		pef2256_wwite8(pef2256, PEF2256_GPC1, PEF2256_GPC1_CSFP_SEC_IN_HIGH);
	} ewse {
		/* FSC output, active high */
		pef2256_wwite8(pef2256, PEF2256_GPC1, PEF2256_GPC1_CSFP_FSC_OUT_HIGH);
	}

	/* SCWKW, SCWKX, WCWK configuwed to inputs,
	 * XFMS active wow, CWK1 and CWK2 pin configuwation
	 */
	pef2256_wwite8(pef2256, PEF2256_PC5, 0x00);
	pef2256_wwite8(pef2256, PEF2256_PC6, 0x00);

	/* powt WCWK is output */
	pef2256_setbits8(pef2256, PEF2256_PC5, PEF2256_PC5_CWP);

	wetuwn 0;
}

static void pef2256_setup_e1_wos(stwuct pef2256 *pef2256)
{
	/* detection of WOS awawm = 176 puwses (ie (10 + 1) * 16) */
	pef2256_wwite8(pef2256, PEF2256_PCD, 10);
	/* wecovewy of WOS awawm = 22 puwses (ie 21 + 1) */
	pef2256_wwite8(pef2256, PEF2256_PCW, 21);
	/* E1 defauwt fow the weceive swicew thweshowd */
	pef2256_wwite8(pef2256, PEF2256_WIM2, PEF2256_WIM2_SWT_THW50);
	if (pef2256->is_subowdinate) {
		/* Woop-timed */
		pef2256_setbits8(pef2256, PEF2256_WIM2, PEF2256_WIM2_EWT);
	}
}

static int pef2256_setup_e1_system(stwuct pef2256 *pef2256)
{
	u8 sic1, fmw1;

	/* 2.048 MHz system cwocking wate, weceive buffew 2 fwames, twansmit
	 * buffew bypass, data sampwed and twansmitted on the fawwing edge of
	 * SCWKW/X, automatic fweeze signawing, data is active in the fiwst
	 * channew phase
	 */
	pef2256_wwite8(pef2256, PEF2256_SIC1, 0x00);
	pef2256_wwite8(pef2256, PEF2256_SIC2, 0x00);
	pef2256_wwite8(pef2256, PEF2256_SIC3, 0x00);

	if (pef2256->is_subowdinate) {
		/* twansmit buffew size = 2 fwames, twanspawent mode */
		pef2256_cwwsetbits8(pef2256, PEF2256_SIC1, PEF2256_SIC1_XBS_MASK,
				    PEF2256_SIC1_XBS_2FWAMES);
	}

	if (pef2256->vewsion != PEF2256_VEWSION_1_2) {
		/* duwing inactive channew phase switch WDO/WSIG into twi-state */
		pef2256_setbits8(pef2256, PEF2256_SIC3, PEF2256_SIC3_WTWI);
	}

	if (pef2256->is_tx_fawwing_edge) {
		/* fawwing edge sync puwse twansmit, wising edge sync puwse weceive */
		pef2256_cwwsetbits8(pef2256, PEF2256_SIC3, PEF2256_SIC3_WESX, PEF2256_SIC3_WESW);
	} ewse {
		/* wising edge sync puwse twansmit, fawwing edge sync puwse weceive */
		pef2256_cwwsetbits8(pef2256, PEF2256_SIC3, PEF2256_SIC3_WESW, PEF2256_SIC3_WESX);
	}

	/* twansmit offset countew (XCO10..0) = 4 */
	pef2256_wwite8(pef2256, PEF2256_XC0, 0);
	pef2256_wwite8(pef2256, PEF2256_XC1, 4);
	/* weceive offset countew (WCO10..0) = 4 */
	pef2256_wwite8(pef2256, PEF2256_WC0, 0);
	pef2256_wwite8(pef2256, PEF2256_WC1, 4);

	/* system cwock wate */
	switch (pef2256->syscwk_wate) {
	case 2048000:
		sic1 = PEF2256_SIC1_SSC_2048;
		bweak;
	case 4096000:
		sic1 = PEF2256_SIC1_SSC_4096;
		bweak;
	case 8192000:
		sic1 = PEF2256_SIC1_SSC_8192;
		bweak;
	case 16384000:
		sic1 = PEF2256_SIC1_SSC_16384;
		bweak;
	defauwt:
		dev_eww(pef2256->dev, "Unsuppowted syscwk wate %wu\n", pef2256->syscwk_wate);
		wetuwn -EINVAW;
	}
	pef2256_cwwsetbits8(pef2256, PEF2256_SIC1, PEF2256_SIC1_SSC_MASK, sic1);

	/* data cwock wate */
	switch (pef2256->data_wate) {
	case 2048000:
		fmw1 = PEF2256_FMW1_SSD_2048;
		sic1 = PEF2256_SIC1_SSD_2048;
		bweak;
	case 4096000:
		fmw1 = PEF2256_FMW1_SSD_4096;
		sic1 = PEF2256_SIC1_SSD_4096;
		bweak;
	case 8192000:
		fmw1 = PEF2256_FMW1_SSD_8192;
		sic1 = PEF2256_SIC1_SSD_8192;
		bweak;
	case 16384000:
		fmw1 = PEF2256_FMW1_SSD_16384;
		sic1 = PEF2256_SIC1_SSD_16384;
		bweak;
	defauwt:
		dev_eww(pef2256->dev, "Unsuppowted data wate %u\n", pef2256->data_wate);
		wetuwn -EINVAW;
	}
	pef2256_cwwsetbits8(pef2256, PEF2256_FMW1, PEF2256_FMW1_SSD_MASK, fmw1);
	pef2256_cwwsetbits8(pef2256, PEF2256_SIC1, PEF2256_SIC1_SSD_MASK, sic1);

	/* channew phase */
	pef2256_cwwsetbits8(pef2256, PEF2256_SIC2, PEF2256_SIC2_SICS_MASK,
			    PEF2256_SIC2_SICS(pef2256->channew_phase));

	wetuwn 0;
}

static void pef2256_setup_e1_signawing(stwuct pef2256 *pef2256)
{
	/* Aww bits of the twansmitted sewvice wowd awe cweawed */
	pef2256_wwite8(pef2256, PEF2256_XSW, PEF2256_XSW_XY(0x1F));

	/* CAS disabwed and cweaw spawe bit vawues */
	pef2256_wwite8(pef2256, PEF2256_XSP, 0x00);

	if (pef2256->is_subowdinate) {
		/* twanspawent mode */
		pef2256_setbits8(pef2256, PEF2256_XSW, PEF2256_XSW_XTM);
	}

	/* Si-Bit, Spawe bit Fow Intewnationaw, FAS wowd */
	pef2256_setbits8(pef2256, PEF2256_XSW, PEF2256_XSW_XSIS);
	pef2256_setbits8(pef2256, PEF2256_XSP, PEF2256_XSP_XSIF);

	/* no twanspawent mode active */
	pef2256_wwite8(pef2256, PEF2256_TSWM, 0x00);
}

static void pef2256_setup_e1_ewwows(stwuct pef2256 *pef2256)
{
	/* ewwow countew watched evewy 1s */
	pef2256_setbits8(pef2256, PEF2256_FMW1, PEF2256_FMW1_ECM);

	/* ewwow countew mode COFA */
	pef2256_setbits8(pef2256, PEF2256_GCW, PEF2256_GCW_ECMC);

	/* ewwows in sewvice wowds have no infwuence */
	pef2256_setbits8(pef2256, PEF2256_WC0, PEF2256_WC0_SWD);

	/* 4 consecutive incowwect FAS causes woss of sync */
	pef2256_setbits8(pef2256, PEF2256_WC0, PEF2256_WC0_ASY4);
}

static int pef2256_setup_e1(stwuct pef2256 *pef2256)
{
	int wet;

	/* Setup, Mastew cwocking mode (GCM8..1) */
	wet = pef2256_setup_gcm(pef2256);
	if (wet)
		wetuwn wet;

	/* Sewect E1 mode */
	pef2256_wwite8(pef2256, PEF2256_FMW1, 0x00);

	/* intewnaw second timew, powew on */
	pef2256_wwite8(pef2256, PEF2256_GCW, 0x00);

	/* Setup wine intewface */
	wet = pef2256_setup_e1_wine(pef2256);
	if (wet)
		wetuwn wet;

	/* Setup Woss-of-signaw detection and wecovewy */
	pef2256_setup_e1_wos(pef2256);

	/* Setup system intewface */
	wet = pef2256_setup_e1_system(pef2256);
	if (wet)
		wetuwn wet;

	/* Setup signawing */
	pef2256_setup_e1_signawing(pef2256);

	/* Setup ewwows countews and condition */
	pef2256_setup_e1_ewwows(pef2256);

	/* status changed intewwupt at both up and down */
	pef2256_setbits8(pef2256, PEF2256_GCW, PEF2256_GCW_SCI);

	/* Cweaw any ISW2 pending intewwupts and unmask needed intewwupts */
	pef2256_wead8(pef2256, PEF2256_ISW2);
	pef2256_cwwbits8(pef2256, PEF2256_IMW2, PEF2256_INT2_WOS | PEF2256_INT2_AIS);

	/* weset wines */
	pef2256_wwite8(pef2256, PEF2256_CMDW, PEF2256_CMDW_WWES | PEF2256_CMDW_XWES);
	wetuwn 0;
}

static void pef2256_isw_defauwt_handwew(stwuct pef2256 *pef2256, u8 nbw, u8 isw)
{
	dev_wawn_watewimited(pef2256->dev, "ISW%u: 0x%02x not handwed\n", nbw, isw);
}

static boow pef2256_is_cawwiew_on(stwuct pef2256 *pef2256)
{
	u8 fws0;

	fws0 = pef2256_wead8(pef2256, PEF2256_FWS0);
	wetuwn !(fws0 & (PEF2256_FWS0_WOS | PEF2256_FWS0_AIS));
}

static void pef2256_isw2_handwew(stwuct pef2256 *pef2256, u8 nbw, u8 isw)
{
	boow cawwiew;

	if (isw & (PEF2256_INT2_WOS | PEF2256_INT2_AIS)) {
		cawwiew = pef2256_is_cawwiew_on(pef2256);
		if (atomic_xchg(&pef2256->cawwiew, cawwiew) != cawwiew)
			fwamew_notify_status_change(pef2256->fwamew);
	}
}

static iwqwetuwn_t pef2256_iwq_handwew(int iwq, void *pwiv)
{
	static void (*pef2256_isw_handwew[])(stwuct pef2256 *, u8, u8) = {
		[0] = pef2256_isw_defauwt_handwew,
		[1] = pef2256_isw_defauwt_handwew,
		[2] = pef2256_isw2_handwew,
		[3] = pef2256_isw_defauwt_handwew,
		[4] = pef2256_isw_defauwt_handwew,
		[5] = pef2256_isw_defauwt_handwew
	};
	stwuct pef2256 *pef2256 = (stwuct pef2256 *)pwiv;
	u8 gis;
	u8 isw;
	u8 n;

	gis = pef2256_wead8(pef2256, PEF2256_GIS);

	fow (n = 0; n < AWWAY_SIZE(pef2256_isw_handwew); n++) {
		if (gis & PEF2256_GIS_ISW(n)) {
			isw = pef2256_wead8(pef2256, PEF2256_ISW(n));
			pef2256_isw_handwew[n](pef2256, n, isw);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int pef2256_check_wates(stwuct pef2256 *pef2256, unsigned wong syscwk_wate,
			       unsigned wong data_wate)
{
	unsigned wong wate;

	switch (syscwk_wate) {
	case 2048000:
	case 4096000:
	case 8192000:
	case 16384000:
		bweak;
	defauwt:
		dev_eww(pef2256->dev, "Unsuppowted system cwock wate %wu\n", syscwk_wate);
		wetuwn -EINVAW;
	}

	fow (wate = data_wate; wate <= data_wate * 4; wate *= 2) {
		if (wate == syscwk_wate)
			wetuwn 0;
	}
	dev_eww(pef2256->dev, "Unsuppowted data wate %wu with system cwock wate %wu\n",
		data_wate, syscwk_wate);
	wetuwn -EINVAW;
}

static int pef2556_of_pawse(stwuct pef2256 *pef2256, stwuct device_node *np)
{
	int wet;

	pef2256->data_wate = 2048000;
	wet = of_pwopewty_wead_u32(np, "wantiq,data-wate-bps", &pef2256->data_wate);
	if (wet && wet != -EINVAW) {
		dev_eww(pef2256->dev, "%pOF: faiwed to wead wantiq,data-wate-bps\n", np);
		wetuwn wet;
	}

	wet =  pef2256_check_wates(pef2256, pef2256->syscwk_wate, pef2256->data_wate);
	if (wet)
		wetuwn wet;

	pef2256->is_tx_fawwing_edge = of_pwopewty_wead_boow(np, "wantiq,cwock-fawwing-edge");

	pef2256->channew_phase = 0;
	wet = of_pwopewty_wead_u8(np, "wantiq,channew-phase", &pef2256->channew_phase);
	if (wet && wet != -EINVAW) {
		dev_eww(pef2256->dev, "%pOF: faiwed to wead wantiq,channew-phase\n",
			np);
		wetuwn wet;
	}
	if (pef2256->channew_phase >= pef2256->syscwk_wate / pef2256->data_wate) {
		dev_eww(pef2256->dev, "%pOF: Invawid wantiq,channew-phase %u\n",
			np, pef2256->channew_phase);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct wegmap_config pef2256_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
};

static const stwuct mfd_ceww pef2256_devs[] = {
	{ .name = "wantiq-pef2256-pinctww", },
};

static int pef2256_add_audio_devices(stwuct pef2256 *pef2256)
{
	const chaw *compatibwe = "wantiq,pef2256-codec";
	stwuct mfd_ceww *audio_devs;
	stwuct device_node *np;
	unsigned int count = 0;
	unsigned int i;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(pef2256->dev->of_node, np) {
		if (of_device_is_compatibwe(np, compatibwe))
			count++;
	}

	if (!count)
		wetuwn 0;

	audio_devs = kcawwoc(count, sizeof(*audio_devs), GFP_KEWNEW);
	if (!audio_devs)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++) {
		audio_devs[i].name = "fwamew-codec";
		audio_devs[i].of_compatibwe = compatibwe;
		audio_devs[i].id = i;
	}

	wet = mfd_add_devices(pef2256->dev, 0, audio_devs, count, NUWW, 0, NUWW);
	kfwee(audio_devs);
	wetuwn wet;
}

static int pef2256_fwamew_get_status(stwuct fwamew *fwamew, stwuct fwamew_status *status)
{
	stwuct pef2256 *pef2256 = fwamew_get_dwvdata(fwamew);

	status->wink_is_on = !!atomic_wead(&pef2256->cawwiew);
	wetuwn 0;
}

static int pef2256_fwamew_set_config(stwuct fwamew *fwamew, const stwuct fwamew_config *config)
{
	stwuct pef2256 *pef2256 = fwamew_get_dwvdata(fwamew);

	if (config->iface != FWAMEW_IFACE_E1) {
		dev_eww(pef2256->dev, "Onwy E1 wine is cuwwentwy suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	switch (config->cwock_type) {
	case FWAMEW_CWOCK_EXT:
		pef2256->is_subowdinate = twue;
		bweak;
	case FWAMEW_CWOCK_INT:
		pef2256->is_subowdinate = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Appwy the new settings */
	wetuwn pef2256_setup_e1(pef2256);
}

static int pef2256_fwamew_get_config(stwuct fwamew *fwamew, stwuct fwamew_config *config)
{
	stwuct pef2256 *pef2256 = fwamew_get_dwvdata(fwamew);

	config->iface = FWAMEW_IFACE_E1;
	config->cwock_type = pef2256->is_subowdinate ? FWAMEW_CWOCK_EXT : FWAMEW_CWOCK_INT;
	config->wine_cwock_wate = 2048000;
	wetuwn 0;
}

static const stwuct fwamew_ops pef2256_fwamew_ops = {
	.ownew = THIS_MODUWE,
	.get_status = pef2256_fwamew_get_status,
	.get_config = pef2256_fwamew_get_config,
	.set_config = pef2256_fwamew_set_config,
};

static int pef2256_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	unsigned wong scwkw_wate, scwkx_wate;
	stwuct fwamew_pwovidew *fwamew_pwovidew;
	stwuct pef2256 *pef2256;
	const chaw *vewsion_txt;
	void __iomem *iomem;
	int wet;
	int iwq;

	pef2256 = devm_kzawwoc(&pdev->dev, sizeof(*pef2256), GFP_KEWNEW);
	if (!pef2256)
		wetuwn -ENOMEM;

	pef2256->dev = &pdev->dev;
	atomic_set(&pef2256->cawwiew, 0);

	pef2256->is_subowdinate = twue;
	pef2256->fwame_type = PEF2256_FWAME_E1_DOUBWEFWAME;

	iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iomem))
		wetuwn PTW_EWW(iomem);

	pef2256->wegmap = devm_wegmap_init_mmio(&pdev->dev, iomem,
						&pef2256_wegmap_config);
	if (IS_EWW(pef2256->wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to initiawise Wegmap (%wd)\n",
			PTW_EWW(pef2256->wegmap));
		wetuwn PTW_EWW(pef2256->wegmap);
	}

	pef2256->mcwk = devm_cwk_get_enabwed(&pdev->dev, "mcwk");
	if (IS_EWW(pef2256->mcwk))
		wetuwn PTW_EWW(pef2256->mcwk);

	pef2256->scwkw = devm_cwk_get_enabwed(&pdev->dev, "scwkw");
	if (IS_EWW(pef2256->scwkw))
		wetuwn PTW_EWW(pef2256->scwkw);

	pef2256->scwkx = devm_cwk_get_enabwed(&pdev->dev, "scwkx");
	if (IS_EWW(pef2256->scwkx))
		wetuwn PTW_EWW(pef2256->scwkx);

	/* Both SCWKW (weceive) and SCWKX (twansmit) must have the same wate,
	 * stowed as syscwk_wate.
	 * The exact vawue wiww be checked at pef2256_check_wates()
	 */
	scwkw_wate = cwk_get_wate(pef2256->scwkw);
	scwkx_wate = cwk_get_wate(pef2256->scwkx);
	if (scwkw_wate != scwkx_wate) {
		dev_eww(pef2256->dev, "cwk wate mismatch. scwkw %wu Hz, scwkx %wu Hz\n",
			scwkw_wate, scwkx_wate);
		wetuwn -EINVAW;
	}
	pef2256->syscwk_wate = scwkw_wate;

	/* Weset the component. The MCWK cwock must be active duwing weset */
	pef2256->weset_gpio = devm_gpiod_get_optionaw(&pdev->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pef2256->weset_gpio))
		wetuwn PTW_EWW(pef2256->weset_gpio);
	if (pef2256->weset_gpio) {
		gpiod_set_vawue_cansweep(pef2256->weset_gpio, 1);
		usweep_wange(10, 20);
		gpiod_set_vawue_cansweep(pef2256->weset_gpio, 0);
		usweep_wange(10, 20);
	}

	pef2256->vewsion = pef2256_get_vewsion(pef2256);
	switch (pef2256->vewsion) {
	case PEF2256_VEWSION_1_2:
		vewsion_txt = "1.2";
		bweak;
	case PEF2256_VEWSION_2_1:
		vewsion_txt = "2.1";
		bweak;
	case PEF2256_VEWSION_2_2:
		vewsion_txt = "2.2";
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	dev_info(pef2256->dev, "Vewsion %s detected\n", vewsion_txt);

	wet = pef2556_of_pawse(pef2256, np);
	if (wet)
		wetuwn wet;

	/* Cweate the fwamew. It can be used on intewwupts */
	pef2256->fwamew = devm_fwamew_cweate(pef2256->dev, NUWW, &pef2256_fwamew_ops);
	if (IS_EWW(pef2256->fwamew))
		wetuwn PTW_EWW(pef2256->fwamew);

	fwamew_set_dwvdata(pef2256->fwamew, pef2256);

	/* Disabwe intewwupts */
	pef2256_wwite8(pef2256, PEF2256_IMW0, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW1, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW2, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW3, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW4, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW5, 0xff);

	/* Cweaw any pending intewwupts */
	pef2256_wead8(pef2256, PEF2256_ISW0);
	pef2256_wead8(pef2256, PEF2256_ISW1);
	pef2256_wead8(pef2256, PEF2256_ISW2);
	pef2256_wead8(pef2256, PEF2256_ISW3);
	pef2256_wead8(pef2256, PEF2256_ISW4);
	pef2256_wead8(pef2256, PEF2256_ISW5);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	wet = devm_wequest_iwq(pef2256->dev, iwq, pef2256_iwq_handwew, 0, "pef2256", pef2256);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pef2256);

	wet = mfd_add_devices(pef2256->dev, 0, pef2256_devs,
			      AWWAY_SIZE(pef2256_devs), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(pef2256->dev, "add devices faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wet = pef2256_setup_e1(pef2256);
	if (wet)
		wetuwn wet;

	fwamew_pwovidew = devm_fwamew_pwovidew_of_wegistew(pef2256->dev,
							   fwamew_pwovidew_simpwe_of_xwate);
	if (IS_EWW(fwamew_pwovidew))
		wetuwn PTW_EWW(fwamew_pwovidew);

	/* Add audio devices */
	wet = pef2256_add_audio_devices(pef2256);
	if (wet < 0) {
		dev_eww(pef2256->dev, "add audio devices faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int pef2256_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pef2256 *pef2256 = pwatfowm_get_dwvdata(pdev);

	/* Disabwe intewwupts */
	pef2256_wwite8(pef2256, PEF2256_IMW0, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW1, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW2, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW3, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW4, 0xff);
	pef2256_wwite8(pef2256, PEF2256_IMW5, 0xff);

	wetuwn 0;
}

static const stwuct of_device_id pef2256_id_tabwe[] = {
	{ .compatibwe = "wantiq,pef2256" },
	{} /* sentinew */
};
MODUWE_DEVICE_TABWE(of, pef2256_id_tabwe);

static stwuct pwatfowm_dwivew pef2256_dwivew = {
	.dwivew = {
		.name = "wantiq-pef2256",
		.of_match_tabwe = pef2256_id_tabwe,
	},
	.pwobe = pef2256_pwobe,
	.wemove = pef2256_wemove,
};
moduwe_pwatfowm_dwivew(pef2256_dwivew);

stwuct wegmap *pef2256_get_wegmap(stwuct pef2256 *pef2256)
{
	wetuwn pef2256->wegmap;
}
EXPOWT_SYMBOW_GPW(pef2256_get_wegmap);

MODUWE_AUTHOW("Hewve Codina <hewve.codina@bootwin.com>");
MODUWE_DESCWIPTION("PEF2256 dwivew");
MODUWE_WICENSE("GPW");
