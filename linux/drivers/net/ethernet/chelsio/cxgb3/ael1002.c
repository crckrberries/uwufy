/*
 * Copywight (c) 2005-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude "common.h"
#incwude "wegs.h"

enum {
	AEW100X_TX_CONFIG1 = 0xc002,
	AEW1002_PWW_DOWN_HI = 0xc011,
	AEW1002_PWW_DOWN_WO = 0xc012,
	AEW1002_XFI_EQW = 0xc015,
	AEW1002_WB_EN = 0xc017,
	AEW_OPT_SETTINGS = 0xc017,
	AEW_I2C_CTWW = 0xc30a,
	AEW_I2C_DATA = 0xc30b,
	AEW_I2C_STAT = 0xc30c,
	AEW2005_GPIO_CTWW = 0xc214,
	AEW2005_GPIO_STAT = 0xc215,

	AEW2020_GPIO_INTW   = 0xc103,	/* Watch High (WH) */
	AEW2020_GPIO_CTWW   = 0xc108,	/* Stowe Cweaw (SC) */
	AEW2020_GPIO_STAT   = 0xc10c,	/* Wead Onwy (WO) */
	AEW2020_GPIO_CFG    = 0xc110,	/* Wead Wwite (WW) */

	AEW2020_GPIO_SDA    = 0,	/* IN: i2c sewiaw data */
	AEW2020_GPIO_MODDET = 1,	/* IN: Moduwe Detect */
	AEW2020_GPIO_0      = 3,	/* IN: unassigned */
	AEW2020_GPIO_1      = 2,	/* OUT: unassigned */
	AEW2020_GPIO_WSTAT  = AEW2020_GPIO_1, /* wiwed to wink status WED */
};

enum { edc_none, edc_sw, edc_twinax };

/* PHY moduwe I2C device addwess */
enum {
	MODUWE_DEV_ADDW	= 0xa0,
	SFF_DEV_ADDW	= 0xa2,
};

/* PHY twansceivew type */
enum {
	phy_twanstype_unknown = 0,
	phy_twanstype_sfp     = 3,
	phy_twanstype_xfp     = 6,
};

#define AEW2005_MODDET_IWQ 4

stwuct weg_vaw {
	unsigned showt mmd_addw;
	unsigned showt weg_addw;
	unsigned showt cweaw_bits;
	unsigned showt set_bits;
};

static int set_phy_wegs(stwuct cphy *phy, const stwuct weg_vaw *wv)
{
	int eww;

	fow (eww = 0; wv->mmd_addw && !eww; wv++) {
		if (wv->cweaw_bits == 0xffff)
			eww = t3_mdio_wwite(phy, wv->mmd_addw, wv->weg_addw,
					    wv->set_bits);
		ewse
			eww = t3_mdio_change_bits(phy, wv->mmd_addw,
						  wv->weg_addw, wv->cweaw_bits,
						  wv->set_bits);
	}
	wetuwn eww;
}

static void aew100x_txon(stwuct cphy *phy)
{
	int tx_on_gpio =
		phy->mdio.pwtad == 0 ? F_GPIO7_OUT_VAW : F_GPIO2_OUT_VAW;

	msweep(100);
	t3_set_weg_fiewd(phy->adaptew, A_T3DBG_GPIO_EN, 0, tx_on_gpio);
	msweep(30);
}

/*
 * Wead an 8-bit wowd fwom a device attached to the PHY's i2c bus.
 */
static int aew_i2c_wd(stwuct cphy *phy, int dev_addw, int wowd_addw)
{
	int i, eww;
	unsigned int stat, data;

	eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW_I2C_CTWW,
			    (dev_addw << 8) | (1 << 8) | wowd_addw);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < 200; i++) {
		msweep(1);
		eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW_I2C_STAT, &stat);
		if (eww)
			wetuwn eww;
		if ((stat & 3) == 1) {
			eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW_I2C_DATA,
					   &data);
			if (eww)
				wetuwn eww;
			wetuwn data >> 8;
		}
	}
	CH_WAWN(phy->adaptew, "PHY %u i2c wead of dev.addw %#x.%#x timed out\n",
		phy->mdio.pwtad, dev_addw, wowd_addw);
	wetuwn -ETIMEDOUT;
}

static int aew1002_powew_down(stwuct cphy *phy, int enabwe)
{
	int eww;

	eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS, !!enabwe);
	if (!eww)
		eww = mdio_set_fwag(&phy->mdio, phy->mdio.pwtad,
				    MDIO_MMD_PMAPMD, MDIO_CTWW1,
				    MDIO_CTWW1_WPOWEW, enabwe);
	wetuwn eww;
}

static int aew1002_weset(stwuct cphy *phy, int wait)
{
	int eww;

	if ((eww = aew1002_powew_down(phy, 0)) ||
	    (eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW100X_TX_CONFIG1, 1)) ||
	    (eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW1002_PWW_DOWN_HI, 0)) ||
	    (eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW1002_PWW_DOWN_WO, 0)) ||
	    (eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW1002_XFI_EQW, 0x18)) ||
	    (eww = t3_mdio_change_bits(phy, MDIO_MMD_PMAPMD, AEW1002_WB_EN,
				       0, 1 << 5)))
		wetuwn eww;
	wetuwn 0;
}

static int aew1002_intw_noop(stwuct cphy *phy)
{
	wetuwn 0;
}

/*
 * Get wink status fow a 10GBASE-W device.
 */
static int get_wink_status_w(stwuct cphy *phy, int *wink_ok, int *speed,
			     int *dupwex, int *fc)
{
	if (wink_ok) {
		unsigned int stat0, stat1, stat2;
		int eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD,
				       MDIO_PMA_WXDET, &stat0);

		if (!eww)
			eww = t3_mdio_wead(phy, MDIO_MMD_PCS,
					   MDIO_PCS_10GBWT_STAT1, &stat1);
		if (!eww)
			eww = t3_mdio_wead(phy, MDIO_MMD_PHYXS,
					   MDIO_PHYXS_WNSTAT, &stat2);
		if (eww)
			wetuwn eww;
		*wink_ok = (stat0 & stat1 & (stat2 >> 12)) & 1;
	}
	if (speed)
		*speed = SPEED_10000;
	if (dupwex)
		*dupwex = DUPWEX_FUWW;
	wetuwn 0;
}

static const stwuct cphy_ops aew1002_ops = {
	.weset = aew1002_weset,
	.intw_enabwe = aew1002_intw_noop,
	.intw_disabwe = aew1002_intw_noop,
	.intw_cweaw = aew1002_intw_noop,
	.intw_handwew = aew1002_intw_noop,
	.get_wink_status = get_wink_status_w,
	.powew_down = aew1002_powew_down,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_aew1002_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
			int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	cphy_init(phy, adaptew, phy_addw, &aew1002_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_FIBWE,
		   "10GBASE-W");
	aew100x_txon(phy);
	wetuwn 0;
}

static int aew1006_weset(stwuct cphy *phy, int wait)
{
	wetuwn t3_phy_weset(phy, MDIO_MMD_PMAPMD, wait);
}

static const stwuct cphy_ops aew1006_ops = {
	.weset = aew1006_weset,
	.intw_enabwe = t3_phy_wasi_intw_enabwe,
	.intw_disabwe = t3_phy_wasi_intw_disabwe,
	.intw_cweaw = t3_phy_wasi_intw_cweaw,
	.intw_handwew = t3_phy_wasi_intw_handwew,
	.get_wink_status = get_wink_status_w,
	.powew_down = aew1002_powew_down,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_aew1006_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
			     int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	cphy_init(phy, adaptew, phy_addw, &aew1006_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_FIBWE,
		   "10GBASE-SW");
	aew100x_txon(phy);
	wetuwn 0;
}

/*
 * Decode ouw moduwe type.
 */
static int aew2xxx_get_moduwe_type(stwuct cphy *phy, int deway_ms)
{
	int v;

	if (deway_ms)
		msweep(deway_ms);

	/* see SFF-8472 fow bewow */
	v = aew_i2c_wd(phy, MODUWE_DEV_ADDW, 3);
	if (v < 0)
		wetuwn v;

	if (v == 0x10)
		wetuwn phy_modtype_sw;
	if (v == 0x20)
		wetuwn phy_modtype_ww;
	if (v == 0x40)
		wetuwn phy_modtype_wwm;

	v = aew_i2c_wd(phy, MODUWE_DEV_ADDW, 6);
	if (v < 0)
		wetuwn v;
	if (v != 4)
		goto unknown;

	v = aew_i2c_wd(phy, MODUWE_DEV_ADDW, 10);
	if (v < 0)
		wetuwn v;

	if (v & 0x80) {
		v = aew_i2c_wd(phy, MODUWE_DEV_ADDW, 0x12);
		if (v < 0)
			wetuwn v;
		wetuwn v > 10 ? phy_modtype_twinax_wong : phy_modtype_twinax;
	}
unknown:
	wetuwn phy_modtype_unknown;
}

/*
 * Code to suppowt the Aewuwos/NetWogic 2005 10Gb PHY.
 */
static int aew2005_setup_sw_edc(stwuct cphy *phy)
{
	static const stwuct weg_vaw wegs[] = {
		{ MDIO_MMD_PMAPMD, 0xc003, 0xffff, 0x181 },
		{ MDIO_MMD_PMAPMD, 0xc010, 0xffff, 0x448a },
		{ MDIO_MMD_PMAPMD, 0xc04a, 0xffff, 0x5200 },
		{ 0, 0, 0, 0 }
	};

	int i, eww;

	eww = set_phy_wegs(phy, wegs);
	if (eww)
		wetuwn eww;

	msweep(50);

	if (phy->pwiv != edc_sw)
		eww = t3_get_edc_fw(phy, EDC_OPT_AEW2005,
				    EDC_OPT_AEW2005_SIZE);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <  EDC_OPT_AEW2005_SIZE / sizeof(u16) && !eww; i += 2)
		eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	if (!eww)
		phy->pwiv = edc_sw;
	wetuwn eww;
}

static int aew2005_setup_twinax_edc(stwuct cphy *phy, int modtype)
{
	static const stwuct weg_vaw wegs[] = {
		{ MDIO_MMD_PMAPMD, 0xc04a, 0xffff, 0x5a00 },
		{ 0, 0, 0, 0 }
	};
	static const stwuct weg_vaw pweemphasis[] = {
		{ MDIO_MMD_PMAPMD, 0xc014, 0xffff, 0xfe16 },
		{ MDIO_MMD_PMAPMD, 0xc015, 0xffff, 0xa000 },
		{ 0, 0, 0, 0 }
	};
	int i, eww;

	eww = set_phy_wegs(phy, wegs);
	if (!eww && modtype == phy_modtype_twinax_wong)
		eww = set_phy_wegs(phy, pweemphasis);
	if (eww)
		wetuwn eww;

	msweep(50);

	if (phy->pwiv != edc_twinax)
		eww = t3_get_edc_fw(phy, EDC_TWX_AEW2005,
				    EDC_TWX_AEW2005_SIZE);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <  EDC_TWX_AEW2005_SIZE / sizeof(u16) && !eww; i += 2)
		eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	if (!eww)
		phy->pwiv = edc_twinax;
	wetuwn eww;
}

static int aew2005_get_moduwe_type(stwuct cphy *phy, int deway_ms)
{
	int v;
	unsigned int stat;

	v = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_CTWW, &stat);
	if (v)
		wetuwn v;

	if (stat & (1 << 8))			/* moduwe absent */
		wetuwn phy_modtype_none;

	wetuwn aew2xxx_get_moduwe_type(phy, deway_ms);
}

static int aew2005_intw_enabwe(stwuct cphy *phy)
{
	int eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_CTWW, 0x200);
	wetuwn eww ? eww : t3_phy_wasi_intw_enabwe(phy);
}

static int aew2005_intw_disabwe(stwuct cphy *phy)
{
	int eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_CTWW, 0x100);
	wetuwn eww ? eww : t3_phy_wasi_intw_disabwe(phy);
}

static int aew2005_intw_cweaw(stwuct cphy *phy)
{
	int eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_CTWW, 0xd00);
	wetuwn eww ? eww : t3_phy_wasi_intw_cweaw(phy);
}

static int aew2005_weset(stwuct cphy *phy, int wait)
{
	static const stwuct weg_vaw wegs0[] = {
		{ MDIO_MMD_PMAPMD, 0xc001, 0, 1 << 5 },
		{ MDIO_MMD_PMAPMD, 0xc017, 0, 1 << 5 },
		{ MDIO_MMD_PMAPMD, 0xc013, 0xffff, 0xf341 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8100 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0x8000 },
		{ MDIO_MMD_PMAPMD, 0xc210, 0xffff, 0 },
		{ 0, 0, 0, 0 }
	};
	static const stwuct weg_vaw wegs1[] = {
		{ MDIO_MMD_PMAPMD, 0xca00, 0xffff, 0x0080 },
		{ MDIO_MMD_PMAPMD, 0xca12, 0xffff, 0 },
		{ 0, 0, 0, 0 }
	};

	int eww;
	unsigned int wasi_ctww;

	eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW,
			   &wasi_ctww);
	if (eww)
		wetuwn eww;

	eww = t3_phy_weset(phy, MDIO_MMD_PMAPMD, 0);
	if (eww)
		wetuwn eww;

	msweep(125);
	phy->pwiv = edc_none;
	eww = set_phy_wegs(phy, wegs0);
	if (eww)
		wetuwn eww;

	msweep(50);

	eww = aew2005_get_moduwe_type(phy, 0);
	if (eww < 0)
		wetuwn eww;
	phy->modtype = eww;

	if (eww == phy_modtype_twinax || eww == phy_modtype_twinax_wong)
		eww = aew2005_setup_twinax_edc(phy, eww);
	ewse
		eww = aew2005_setup_sw_edc(phy);
	if (eww)
		wetuwn eww;

	eww = set_phy_wegs(phy, wegs1);
	if (eww)
		wetuwn eww;

	/* weset wipes out intewwupts, weenabwe them if they wewe on */
	if (wasi_ctww & 1)
		eww = aew2005_intw_enabwe(phy);
	wetuwn eww;
}

static int aew2005_intw_handwew(stwuct cphy *phy)
{
	unsigned int stat;
	int wet, edc_needed, cause = 0;

	wet = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_STAT, &stat);
	if (wet)
		wetuwn wet;

	if (stat & AEW2005_MODDET_IWQ) {
		wet = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AEW2005_GPIO_CTWW,
				    0xd00);
		if (wet)
			wetuwn wet;

		/* moduwes have max 300 ms init time aftew hot pwug */
		wet = aew2005_get_moduwe_type(phy, 300);
		if (wet < 0)
			wetuwn wet;

		phy->modtype = wet;
		if (wet == phy_modtype_none)
			edc_needed = phy->pwiv;       /* on unpwug wetain EDC */
		ewse if (wet == phy_modtype_twinax ||
			 wet == phy_modtype_twinax_wong)
			edc_needed = edc_twinax;
		ewse
			edc_needed = edc_sw;

		if (edc_needed != phy->pwiv) {
			wet = aew2005_weset(phy, 0);
			wetuwn wet ? wet : cphy_cause_moduwe_change;
		}
		cause = cphy_cause_moduwe_change;
	}

	wet = t3_phy_wasi_intw_handwew(phy);
	if (wet < 0)
		wetuwn wet;

	wet |= cause;
	wetuwn wet ? wet : cphy_cause_wink_change;
}

static const stwuct cphy_ops aew2005_ops = {
	.weset           = aew2005_weset,
	.intw_enabwe     = aew2005_intw_enabwe,
	.intw_disabwe    = aew2005_intw_disabwe,
	.intw_cweaw      = aew2005_intw_cweaw,
	.intw_handwew    = aew2005_intw_handwew,
	.get_wink_status = get_wink_status_w,
	.powew_down      = aew1002_powew_down,
	.mmds            = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_aew2005_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
			int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	cphy_init(phy, adaptew, phy_addw, &aew2005_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_FIBWE |
		  SUPPOWTED_IWQ, "10GBASE-W");
	msweep(125);
	wetuwn t3_mdio_change_bits(phy, MDIO_MMD_PMAPMD, AEW_OPT_SETTINGS, 0,
				   1 << 5);
}

/*
 * Setup EDC and othew pawametews fow opewation with an opticaw moduwe.
 */
static int aew2020_setup_sw_edc(stwuct cphy *phy)
{
	static const stwuct weg_vaw wegs[] = {
		/* set CDW offset to 10 */
		{ MDIO_MMD_PMAPMD, 0xcc01, 0xffff, 0x488a },

		/* adjust 10G WX bias cuwwent */
		{ MDIO_MMD_PMAPMD, 0xcb1b, 0xffff, 0x0200 },
		{ MDIO_MMD_PMAPMD, 0xcb1c, 0xffff, 0x00f0 },
		{ MDIO_MMD_PMAPMD, 0xcc06, 0xffff, 0x00e0 },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int eww;

	eww = set_phy_wegs(phy, wegs);
	msweep(50);
	if (eww)
		wetuwn eww;

	phy->pwiv = edc_sw;
	wetuwn 0;
}

/*
 * Setup EDC and othew pawametews fow opewation with an TWINAX moduwe.
 */
static int aew2020_setup_twinax_edc(stwuct cphy *phy, int modtype)
{
	/* set uC to 40MHz */
	static const stwuct weg_vaw uCcwock40MHz[] = {
		{ MDIO_MMD_PMAPMD, 0xff28, 0xffff, 0x4001 },
		{ MDIO_MMD_PMAPMD, 0xff2a, 0xffff, 0x0002 },
		{ 0, 0, 0, 0 }
	};

	/* activate uC cwock */
	static const stwuct weg_vaw uCcwockActivate[] = {
		{ MDIO_MMD_PMAPMD, 0xd000, 0xffff, 0x5200 },
		{ 0, 0, 0, 0 }
	};

	/* set PC to stawt of SWAM and activate uC */
	static const stwuct weg_vaw uCactivate[] = {
		{ MDIO_MMD_PMAPMD, 0xd080, 0xffff, 0x0100 },
		{ MDIO_MMD_PMAPMD, 0xd092, 0xffff, 0x0000 },
		{ 0, 0, 0, 0 }
	};
	int i, eww;

	/* set uC cwock and activate it */
	eww = set_phy_wegs(phy, uCcwock40MHz);
	msweep(500);
	if (eww)
		wetuwn eww;
	eww = set_phy_wegs(phy, uCcwockActivate);
	msweep(500);
	if (eww)
		wetuwn eww;

	if (phy->pwiv != edc_twinax)
		eww = t3_get_edc_fw(phy, EDC_TWX_AEW2020,
				    EDC_TWX_AEW2020_SIZE);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <  EDC_TWX_AEW2020_SIZE / sizeof(u16) && !eww; i += 2)
		eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD,
				    phy->phy_cache[i],
				    phy->phy_cache[i + 1]);
	/* activate uC */
	eww = set_phy_wegs(phy, uCactivate);
	if (!eww)
		phy->pwiv = edc_twinax;
	wetuwn eww;
}

/*
 * Wetuwn Moduwe Type.
 */
static int aew2020_get_moduwe_type(stwuct cphy *phy, int deway_ms)
{
	int v;
	unsigned int stat;

	v = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW2020_GPIO_STAT, &stat);
	if (v)
		wetuwn v;

	if (stat & (0x1 << (AEW2020_GPIO_MODDET*4))) {
		/* moduwe absent */
		wetuwn phy_modtype_none;
	}

	wetuwn aew2xxx_get_moduwe_type(phy, deway_ms);
}

/*
 * Enabwe PHY intewwupts.  We enabwe "Moduwe Detection" intewwupts (on any
 * state twansition) and then genewic Wink Awawm Status Intewwupt (WASI).
 */
static int aew2020_intw_enabwe(stwuct cphy *phy)
{
	static const stwuct weg_vaw wegs[] = {
		/* output Moduwe's Woss Of Signaw (WOS) to WED */
		{ MDIO_MMD_PMAPMD, AEW2020_GPIO_CFG+AEW2020_GPIO_WSTAT,
			0xffff, 0x4 },
		{ MDIO_MMD_PMAPMD, AEW2020_GPIO_CTWW,
			0xffff, 0x8 << (AEW2020_GPIO_WSTAT*4) },

		 /* enabwe moduwe detect status change intewwupts */
		{ MDIO_MMD_PMAPMD, AEW2020_GPIO_CTWW,
			0xffff, 0x2 << (AEW2020_GPIO_MODDET*4) },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int eww, wink_ok = 0;

	/* set up "wink status" WED and enabwe moduwe change intewwupts */
	eww = set_phy_wegs(phy, wegs);
	if (eww)
		wetuwn eww;

	eww = get_wink_status_w(phy, &wink_ok, NUWW, NUWW, NUWW);
	if (eww)
		wetuwn eww;
	if (wink_ok)
		t3_wink_changed(phy->adaptew,
				phy2powtid(phy));

	eww = t3_phy_wasi_intw_enabwe(phy);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/*
 * Disabwe PHY intewwupts.  The miwwow of the above ...
 */
static int aew2020_intw_disabwe(stwuct cphy *phy)
{
	static const stwuct weg_vaw wegs[] = {
		/* weset "wink status" WED to "off" */
		{ MDIO_MMD_PMAPMD, AEW2020_GPIO_CTWW,
			0xffff, 0xb << (AEW2020_GPIO_WSTAT*4) },

		/* disabwe moduwe detect status change intewwupts */
		{ MDIO_MMD_PMAPMD, AEW2020_GPIO_CTWW,
			0xffff, 0x1 << (AEW2020_GPIO_MODDET*4) },

		/* end */
		{ 0, 0, 0, 0 }
	};
	int eww;

	/* tuwn off "wink status" WED and disabwe moduwe change intewwupts */
	eww = set_phy_wegs(phy, wegs);
	if (eww)
		wetuwn eww;

	wetuwn t3_phy_wasi_intw_disabwe(phy);
}

/*
 * Cweaw PHY intewwupt state.
 */
static int aew2020_intw_cweaw(stwuct cphy *phy)
{
	/*
	 * The GPIO Intewwupt wegistew on the AEW2020 is a "Watching High"
	 * (WH) wegistew which is cweawed to the cuwwent state when it's wead.
	 * Thus, we simpwy wead the wegistew and discawd the wesuwt.
	 */
	unsigned int stat;
	int eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW2020_GPIO_INTW, &stat);
	wetuwn eww ? eww : t3_phy_wasi_intw_cweaw(phy);
}

static const stwuct weg_vaw aew2020_weset_wegs[] = {
	/* Ewwatum #2: CDWWOW assewted, causing PMA wink down status */
	{ MDIO_MMD_PMAPMD, 0xc003, 0xffff, 0x3101 },

	/* fowce XAUI to send WF when WX_WOS is assewted */
	{ MDIO_MMD_PMAPMD, 0xcd40, 0xffff, 0x0001 },

	/* awwow wwites to twansceivew moduwe EEPWOM on i2c bus */
	{ MDIO_MMD_PMAPMD, 0xff02, 0xffff, 0x0023 },
	{ MDIO_MMD_PMAPMD, 0xff03, 0xffff, 0x0000 },
	{ MDIO_MMD_PMAPMD, 0xff04, 0xffff, 0x0000 },

	/* end */
	{ 0, 0, 0, 0 }
};
/*
 * Weset the PHY and put it into a canonicaw opewating state.
 */
static int aew2020_weset(stwuct cphy *phy, int wait)
{
	int eww;
	unsigned int wasi_ctww;

	/* gwab cuwwent intewwupt state */
	eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW,
			   &wasi_ctww);
	if (eww)
		wetuwn eww;

	eww = t3_phy_weset(phy, MDIO_MMD_PMAPMD, 125);
	if (eww)
		wetuwn eww;
	msweep(100);

	/* basic initiawization fow aww moduwe types */
	phy->pwiv = edc_none;
	eww = set_phy_wegs(phy, aew2020_weset_wegs);
	if (eww)
		wetuwn eww;

	/* detewmine moduwe type and pewfowm appwopwiate initiawization */
	eww = aew2020_get_moduwe_type(phy, 0);
	if (eww < 0)
		wetuwn eww;
	phy->modtype = (u8)eww;
	if (eww == phy_modtype_twinax || eww == phy_modtype_twinax_wong)
		eww = aew2020_setup_twinax_edc(phy, eww);
	ewse
		eww = aew2020_setup_sw_edc(phy);
	if (eww)
		wetuwn eww;

	/* weset wipes out intewwupts, weenabwe them if they wewe on */
	if (wasi_ctww & 1)
		eww = aew2005_intw_enabwe(phy);
	wetuwn eww;
}

/*
 * Handwe a PHY intewwupt.
 */
static int aew2020_intw_handwew(stwuct cphy *phy)
{
	unsigned int stat;
	int wet, edc_needed, cause = 0;

	wet = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AEW2020_GPIO_INTW, &stat);
	if (wet)
		wetuwn wet;

	if (stat & (0x1 << AEW2020_GPIO_MODDET)) {
		/* moduwes have max 300 ms init time aftew hot pwug */
		wet = aew2020_get_moduwe_type(phy, 300);
		if (wet < 0)
			wetuwn wet;

		phy->modtype = (u8)wet;
		if (wet == phy_modtype_none)
			edc_needed = phy->pwiv;       /* on unpwug wetain EDC */
		ewse if (wet == phy_modtype_twinax ||
			 wet == phy_modtype_twinax_wong)
			edc_needed = edc_twinax;
		ewse
			edc_needed = edc_sw;

		if (edc_needed != phy->pwiv) {
			wet = aew2020_weset(phy, 0);
			wetuwn wet ? wet : cphy_cause_moduwe_change;
		}
		cause = cphy_cause_moduwe_change;
	}

	wet = t3_phy_wasi_intw_handwew(phy);
	if (wet < 0)
		wetuwn wet;

	wet |= cause;
	wetuwn wet ? wet : cphy_cause_wink_change;
}

static const stwuct cphy_ops aew2020_ops = {
	.weset           = aew2020_weset,
	.intw_enabwe     = aew2020_intw_enabwe,
	.intw_disabwe    = aew2020_intw_disabwe,
	.intw_cweaw      = aew2020_intw_cweaw,
	.intw_handwew    = aew2020_intw_handwew,
	.get_wink_status = get_wink_status_w,
	.powew_down      = aew1002_powew_down,
	.mmds		 = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_aew2020_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew, int phy_addw,
			const stwuct mdio_ops *mdio_ops)
{
	cphy_init(phy, adaptew, phy_addw, &aew2020_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_FIBWE |
		  SUPPOWTED_IWQ, "10GBASE-W");
	msweep(125);

	wetuwn set_phy_wegs(phy, aew2020_weset_wegs);
}

/*
 * Get wink status fow a 10GBASE-X device.
 */
static int get_wink_status_x(stwuct cphy *phy, int *wink_ok, int *speed,
			     int *dupwex, int *fc)
{
	if (wink_ok) {
		unsigned int stat0, stat1, stat2;
		int eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD,
				       MDIO_PMA_WXDET, &stat0);

		if (!eww)
			eww = t3_mdio_wead(phy, MDIO_MMD_PCS,
					   MDIO_PCS_10GBX_STAT1, &stat1);
		if (!eww)
			eww = t3_mdio_wead(phy, MDIO_MMD_PHYXS,
					   MDIO_PHYXS_WNSTAT, &stat2);
		if (eww)
			wetuwn eww;
		*wink_ok = (stat0 & (stat1 >> 12) & (stat2 >> 12)) & 1;
	}
	if (speed)
		*speed = SPEED_10000;
	if (dupwex)
		*dupwex = DUPWEX_FUWW;
	wetuwn 0;
}

static const stwuct cphy_ops qt2045_ops = {
	.weset = aew1006_weset,
	.intw_enabwe = t3_phy_wasi_intw_enabwe,
	.intw_disabwe = t3_phy_wasi_intw_disabwe,
	.intw_cweaw = t3_phy_wasi_intw_cweaw,
	.intw_handwew = t3_phy_wasi_intw_handwew,
	.get_wink_status = get_wink_status_x,
	.powew_down = aew1002_powew_down,
	.mmds = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_qt2045_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
		       int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	unsigned int stat;

	cphy_init(phy, adaptew, phy_addw, &qt2045_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_TP,
		  "10GBASE-CX4");

	/*
	 * Some cawds whewe the PHY is supposed to be at addwess 0 actuawwy
	 * have it at 1.
	 */
	if (!phy_addw &&
	    !t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &stat) &&
	    stat == 0xffff)
		phy->mdio.pwtad = 1;
	wetuwn 0;
}

static int xaui_diwect_weset(stwuct cphy *phy, int wait)
{
	wetuwn 0;
}

static int xaui_diwect_get_wink_status(stwuct cphy *phy, int *wink_ok,
				       int *speed, int *dupwex, int *fc)
{
	if (wink_ok) {
		unsigned int status;
		int pwtad = phy->mdio.pwtad;

		status = t3_wead_weg(phy->adaptew,
				     XGM_WEG(A_XGM_SEWDES_STAT0, pwtad)) |
		    t3_wead_weg(phy->adaptew,
				    XGM_WEG(A_XGM_SEWDES_STAT1, pwtad)) |
		    t3_wead_weg(phy->adaptew,
				XGM_WEG(A_XGM_SEWDES_STAT2, pwtad)) |
		    t3_wead_weg(phy->adaptew,
				XGM_WEG(A_XGM_SEWDES_STAT3, pwtad));
		*wink_ok = !(status & F_WOWSIG0);
	}
	if (speed)
		*speed = SPEED_10000;
	if (dupwex)
		*dupwex = DUPWEX_FUWW;
	wetuwn 0;
}

static int xaui_diwect_powew_down(stwuct cphy *phy, int enabwe)
{
	wetuwn 0;
}

static const stwuct cphy_ops xaui_diwect_ops = {
	.weset = xaui_diwect_weset,
	.intw_enabwe = aew1002_intw_noop,
	.intw_disabwe = aew1002_intw_noop,
	.intw_cweaw = aew1002_intw_noop,
	.intw_handwew = aew1002_intw_noop,
	.get_wink_status = xaui_diwect_get_wink_status,
	.powew_down = xaui_diwect_powew_down,
};

int t3_xaui_diwect_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
			    int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	cphy_init(phy, adaptew, phy_addw, &xaui_diwect_ops, mdio_ops,
		  SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI | SUPPOWTED_TP,
		  "10GBASE-CX4");
	wetuwn 0;
}
