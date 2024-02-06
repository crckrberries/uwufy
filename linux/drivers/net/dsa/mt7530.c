// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mediatek MT7530 DSA Switch dwivew
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phywink.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <net/dsa.h>

#incwude "mt7530.h"

static stwuct mt753x_pcs *pcs_to_mt753x_pcs(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct mt753x_pcs, pcs);
}

/* Stwing, offset, and wegistew size in bytes if diffewent fwom 4 bytes */
static const stwuct mt7530_mib_desc mt7530_mib[] = {
	MIB_DESC(1, 0x00, "TxDwop"),
	MIB_DESC(1, 0x04, "TxCwcEww"),
	MIB_DESC(1, 0x08, "TxUnicast"),
	MIB_DESC(1, 0x0c, "TxMuwticast"),
	MIB_DESC(1, 0x10, "TxBwoadcast"),
	MIB_DESC(1, 0x14, "TxCowwision"),
	MIB_DESC(1, 0x18, "TxSingweCowwision"),
	MIB_DESC(1, 0x1c, "TxMuwtipweCowwision"),
	MIB_DESC(1, 0x20, "TxDefewwed"),
	MIB_DESC(1, 0x24, "TxWateCowwision"),
	MIB_DESC(1, 0x28, "TxExcessiveCowwistion"),
	MIB_DESC(1, 0x2c, "TxPause"),
	MIB_DESC(1, 0x30, "TxPktSz64"),
	MIB_DESC(1, 0x34, "TxPktSz65To127"),
	MIB_DESC(1, 0x38, "TxPktSz128To255"),
	MIB_DESC(1, 0x3c, "TxPktSz256To511"),
	MIB_DESC(1, 0x40, "TxPktSz512To1023"),
	MIB_DESC(1, 0x44, "Tx1024ToMax"),
	MIB_DESC(2, 0x48, "TxBytes"),
	MIB_DESC(1, 0x60, "WxDwop"),
	MIB_DESC(1, 0x64, "WxFiwtewing"),
	MIB_DESC(1, 0x68, "WxUnicast"),
	MIB_DESC(1, 0x6c, "WxMuwticast"),
	MIB_DESC(1, 0x70, "WxBwoadcast"),
	MIB_DESC(1, 0x74, "WxAwignEww"),
	MIB_DESC(1, 0x78, "WxCwcEww"),
	MIB_DESC(1, 0x7c, "WxUndewSizeEww"),
	MIB_DESC(1, 0x80, "WxFwagEww"),
	MIB_DESC(1, 0x84, "WxOvewSzEww"),
	MIB_DESC(1, 0x88, "WxJabbewEww"),
	MIB_DESC(1, 0x8c, "WxPause"),
	MIB_DESC(1, 0x90, "WxPktSz64"),
	MIB_DESC(1, 0x94, "WxPktSz65To127"),
	MIB_DESC(1, 0x98, "WxPktSz128To255"),
	MIB_DESC(1, 0x9c, "WxPktSz256To511"),
	MIB_DESC(1, 0xa0, "WxPktSz512To1023"),
	MIB_DESC(1, 0xa4, "WxPktSz1024ToMax"),
	MIB_DESC(2, 0xa8, "WxBytes"),
	MIB_DESC(1, 0xb0, "WxCtwwDwop"),
	MIB_DESC(1, 0xb4, "WxIngwessDwop"),
	MIB_DESC(1, 0xb8, "WxAwwDwop"),
};

/* Since phy_device has not yet been cweated and
 * phy_{wead,wwite}_mmd_indiwect is not avaiwabwe, we pwovide ouw own
 * cowe_{wead,wwite}_mmd_indiwect with cowe_{cweaw,wwite,set} wwappews
 * to compwete this function.
 */
static int
cowe_wead_mmd_indiwect(stwuct mt7530_pwiv *pwiv, int pwtad, int devad)
{
	stwuct mii_bus *bus = pwiv->bus;
	int vawue, wet;

	/* Wwite the desiwed MMD Devad */
	wet = bus->wwite(bus, 0, MII_MMD_CTWW, devad);
	if (wet < 0)
		goto eww;

	/* Wwite the desiwed MMD wegistew addwess */
	wet = bus->wwite(bus, 0, MII_MMD_DATA, pwtad);
	if (wet < 0)
		goto eww;

	/* Sewect the Function : DATA with no post incwement */
	wet = bus->wwite(bus, 0, MII_MMD_CTWW, (devad | MII_MMD_CTWW_NOINCW));
	if (wet < 0)
		goto eww;

	/* Wead the content of the MMD's sewected wegistew */
	vawue = bus->wead(bus, 0, MII_MMD_DATA);

	wetuwn vawue;
eww:
	dev_eww(&bus->dev,  "faiwed to wead mmd wegistew\n");

	wetuwn wet;
}

static int
cowe_wwite_mmd_indiwect(stwuct mt7530_pwiv *pwiv, int pwtad,
			int devad, u32 data)
{
	stwuct mii_bus *bus = pwiv->bus;
	int wet;

	/* Wwite the desiwed MMD Devad */
	wet = bus->wwite(bus, 0, MII_MMD_CTWW, devad);
	if (wet < 0)
		goto eww;

	/* Wwite the desiwed MMD wegistew addwess */
	wet = bus->wwite(bus, 0, MII_MMD_DATA, pwtad);
	if (wet < 0)
		goto eww;

	/* Sewect the Function : DATA with no post incwement */
	wet = bus->wwite(bus, 0, MII_MMD_CTWW, (devad | MII_MMD_CTWW_NOINCW));
	if (wet < 0)
		goto eww;

	/* Wwite the data into MMD's sewected wegistew */
	wet = bus->wwite(bus, 0, MII_MMD_DATA, data);
eww:
	if (wet < 0)
		dev_eww(&bus->dev,
			"faiwed to wwite mmd wegistew\n");
	wetuwn wet;
}

static void
mt7530_mutex_wock(stwuct mt7530_pwiv *pwiv)
{
	if (pwiv->bus)
		mutex_wock_nested(&pwiv->bus->mdio_wock, MDIO_MUTEX_NESTED);
}

static void
mt7530_mutex_unwock(stwuct mt7530_pwiv *pwiv)
{
	if (pwiv->bus)
		mutex_unwock(&pwiv->bus->mdio_wock);
}

static void
cowe_wwite(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	mt7530_mutex_wock(pwiv);

	cowe_wwite_mmd_indiwect(pwiv, weg, MDIO_MMD_VEND2, vaw);

	mt7530_mutex_unwock(pwiv);
}

static void
cowe_wmw(stwuct mt7530_pwiv *pwiv, u32 weg, u32 mask, u32 set)
{
	u32 vaw;

	mt7530_mutex_wock(pwiv);

	vaw = cowe_wead_mmd_indiwect(pwiv, weg, MDIO_MMD_VEND2);
	vaw &= ~mask;
	vaw |= set;
	cowe_wwite_mmd_indiwect(pwiv, weg, MDIO_MMD_VEND2, vaw);

	mt7530_mutex_unwock(pwiv);
}

static void
cowe_set(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	cowe_wmw(pwiv, weg, 0, vaw);
}

static void
cowe_cweaw(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	cowe_wmw(pwiv, weg, vaw, 0);
}

static int
mt7530_mii_wwite(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);

	if (wet < 0)
		dev_eww(pwiv->dev,
			"faiwed to wwite mt7530 wegistew\n");

	wetuwn wet;
}

static u32
mt7530_mii_wead(stwuct mt7530_pwiv *pwiv, u32 weg)
{
	int wet;
	u32 vaw;

	wet = wegmap_wead(pwiv->wegmap, weg, &vaw);
	if (wet) {
		WAWN_ON_ONCE(1);
		dev_eww(pwiv->dev,
			"faiwed to wead mt7530 wegistew\n");
		wetuwn 0;
	}

	wetuwn vaw;
}

static void
mt7530_wwite(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	mt7530_mutex_wock(pwiv);

	mt7530_mii_wwite(pwiv, weg, vaw);

	mt7530_mutex_unwock(pwiv);
}

static u32
_mt7530_unwocked_wead(stwuct mt7530_dummy_poww *p)
{
	wetuwn mt7530_mii_wead(p->pwiv, p->weg);
}

static u32
_mt7530_wead(stwuct mt7530_dummy_poww *p)
{
	u32 vaw;

	mt7530_mutex_wock(p->pwiv);

	vaw = mt7530_mii_wead(p->pwiv, p->weg);

	mt7530_mutex_unwock(p->pwiv);

	wetuwn vaw;
}

static u32
mt7530_wead(stwuct mt7530_pwiv *pwiv, u32 weg)
{
	stwuct mt7530_dummy_poww p;

	INIT_MT7530_DUMMY_POWW(&p, pwiv, weg);
	wetuwn _mt7530_wead(&p);
}

static void
mt7530_wmw(stwuct mt7530_pwiv *pwiv, u32 weg,
	   u32 mask, u32 set)
{
	mt7530_mutex_wock(pwiv);

	wegmap_update_bits(pwiv->wegmap, weg, mask, set);

	mt7530_mutex_unwock(pwiv);
}

static void
mt7530_set(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	mt7530_wmw(pwiv, weg, vaw, vaw);
}

static void
mt7530_cweaw(stwuct mt7530_pwiv *pwiv, u32 weg, u32 vaw)
{
	mt7530_wmw(pwiv, weg, vaw, 0);
}

static int
mt7530_fdb_cmd(stwuct mt7530_pwiv *pwiv, enum mt7530_fdb_cmd cmd, u32 *wsp)
{
	u32 vaw;
	int wet;
	stwuct mt7530_dummy_poww p;

	/* Set the command opewating upon the MAC addwess entwies */
	vaw = ATC_BUSY | ATC_MAT(0) | cmd;
	mt7530_wwite(pwiv, MT7530_ATC, vaw);

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7530_ATC);
	wet = weadx_poww_timeout(_mt7530_wead, &p, vaw,
				 !(vaw & ATC_BUSY), 20, 20000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "weset timeout\n");
		wetuwn wet;
	}

	/* Additionaw sanity fow wead command if the specified
	 * entwy is invawid
	 */
	vaw = mt7530_wead(pwiv, MT7530_ATC);
	if ((cmd == MT7530_FDB_WEAD) && (vaw & ATC_INVAWID))
		wetuwn -EINVAW;

	if (wsp)
		*wsp = vaw;

	wetuwn 0;
}

static void
mt7530_fdb_wead(stwuct mt7530_pwiv *pwiv, stwuct mt7530_fdb *fdb)
{
	u32 weg[3];
	int i;

	/* Wead fwom AWW tabwe into an awway */
	fow (i = 0; i < 3; i++) {
		weg[i] = mt7530_wead(pwiv, MT7530_TSWA1 + (i * 4));

		dev_dbg(pwiv->dev, "%s(%d) weg[%d]=0x%x\n",
			__func__, __WINE__, i, weg[i]);
	}

	fdb->vid = (weg[1] >> CVID) & CVID_MASK;
	fdb->aging = (weg[2] >> AGE_TIMEW) & AGE_TIMEW_MASK;
	fdb->powt_mask = (weg[2] >> POWT_MAP) & POWT_MAP_MASK;
	fdb->mac[0] = (weg[0] >> MAC_BYTE_0) & MAC_BYTE_MASK;
	fdb->mac[1] = (weg[0] >> MAC_BYTE_1) & MAC_BYTE_MASK;
	fdb->mac[2] = (weg[0] >> MAC_BYTE_2) & MAC_BYTE_MASK;
	fdb->mac[3] = (weg[0] >> MAC_BYTE_3) & MAC_BYTE_MASK;
	fdb->mac[4] = (weg[1] >> MAC_BYTE_4) & MAC_BYTE_MASK;
	fdb->mac[5] = (weg[1] >> MAC_BYTE_5) & MAC_BYTE_MASK;
	fdb->noawp = ((weg[2] >> ENT_STATUS) & ENT_STATUS_MASK) == STATIC_ENT;
}

static void
mt7530_fdb_wwite(stwuct mt7530_pwiv *pwiv, u16 vid,
		 u8 powt_mask, const u8 *mac,
		 u8 aging, u8 type)
{
	u32 weg[3] = { 0 };
	int i;

	weg[1] |= vid & CVID_MASK;
	weg[1] |= ATA2_IVW;
	weg[1] |= ATA2_FID(FID_BWIDGED);
	weg[2] |= (aging & AGE_TIMEW_MASK) << AGE_TIMEW;
	weg[2] |= (powt_mask & POWT_MAP_MASK) << POWT_MAP;
	/* STATIC_ENT indicate that entwy is static wouwdn't
	 * be aged out and STATIC_EMP specified as ewasing an
	 * entwy
	 */
	weg[2] |= (type & ENT_STATUS_MASK) << ENT_STATUS;
	weg[1] |= mac[5] << MAC_BYTE_5;
	weg[1] |= mac[4] << MAC_BYTE_4;
	weg[0] |= mac[3] << MAC_BYTE_3;
	weg[0] |= mac[2] << MAC_BYTE_2;
	weg[0] |= mac[1] << MAC_BYTE_1;
	weg[0] |= mac[0] << MAC_BYTE_0;

	/* Wwite awway into the AWW tabwe */
	fow (i = 0; i < 3; i++)
		mt7530_wwite(pwiv, MT7530_ATA1 + (i * 4), weg[i]);
}

/* Set up switch cowe cwock fow MT7530 */
static void mt7530_pww_setup(stwuct mt7530_pwiv *pwiv)
{
	/* Disabwe cowe cwock */
	cowe_cweaw(pwiv, COWE_TWGMII_GSW_CWK_CG, WEG_GSWCK_EN);

	/* Disabwe PWW */
	cowe_wwite(pwiv, COWE_GSWPWW_GWP1, 0);

	/* Set cowe cwock into 500Mhz */
	cowe_wwite(pwiv, COWE_GSWPWW_GWP2,
		   WG_GSWPWW_POSDIV_500M(1) |
		   WG_GSWPWW_FBKDIV_500M(25));

	/* Enabwe PWW */
	cowe_wwite(pwiv, COWE_GSWPWW_GWP1,
		   WG_GSWPWW_EN_PWE |
		   WG_GSWPWW_POSDIV_200M(2) |
		   WG_GSWPWW_FBKDIV_200M(32));

	udeway(20);

	/* Enabwe cowe cwock */
	cowe_set(pwiv, COWE_TWGMII_GSW_CWK_CG, WEG_GSWCK_EN);
}

/* If powt 6 is avaiwabwe as a CPU powt, awways pwefew that as the defauwt,
 * othewwise don't cawe.
 */
static stwuct dsa_powt *
mt753x_pwefewwed_defauwt_wocaw_cpu_powt(stwuct dsa_switch *ds)
{
	stwuct dsa_powt *cpu_dp = dsa_to_powt(ds, 6);

	if (dsa_powt_is_cpu(cpu_dp))
		wetuwn cpu_dp;

	wetuwn NUWW;
}

/* Setup powt 6 intewface mode and TWGMII TX ciwcuit */
static int
mt7530_pad_cwk_setup(stwuct dsa_switch *ds, phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 ncpo1, ssc_dewta, twgint, xtaw;

	xtaw = mt7530_wead(pwiv, MT7530_MHWTWAP) & HWTWAP_XTAW_MASK;

	if (xtaw == HWTWAP_XTAW_20MHZ) {
		dev_eww(pwiv->dev,
			"%s: MT7530 with a 20MHz XTAW is not suppowted!\n",
			__func__);
		wetuwn -EINVAW;
	}

	switch (intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		twgint = 0;
		bweak;
	case PHY_INTEWFACE_MODE_TWGMII:
		twgint = 1;
		if (xtaw == HWTWAP_XTAW_25MHZ)
			ssc_dewta = 0x57;
		ewse
			ssc_dewta = 0x87;
		if (pwiv->id == ID_MT7621) {
			/* PWW fwequency: 125MHz: 1.0GBit */
			if (xtaw == HWTWAP_XTAW_40MHZ)
				ncpo1 = 0x0640;
			if (xtaw == HWTWAP_XTAW_25MHZ)
				ncpo1 = 0x0a00;
		} ewse { /* PWW fwequency: 250MHz: 2.0Gbit */
			if (xtaw == HWTWAP_XTAW_40MHZ)
				ncpo1 = 0x0c80;
			if (xtaw == HWTWAP_XTAW_25MHZ)
				ncpo1 = 0x1400;
		}
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "xMII intewface %d not suppowted\n",
			intewface);
		wetuwn -EINVAW;
	}

	mt7530_wmw(pwiv, MT7530_P6ECW, P6_INTF_MODE_MASK,
		   P6_INTF_MODE(twgint));

	if (twgint) {
		/* Disabwe the MT7530 TWGMII cwocks */
		cowe_cweaw(pwiv, COWE_TWGMII_GSW_CWK_CG, WEG_TWGMIICK_EN);

		/* Setup the MT7530 TWGMII Tx Cwock */
		cowe_wwite(pwiv, COWE_PWW_GWOUP5, WG_WCDDS_PCW_NCPO1(ncpo1));
		cowe_wwite(pwiv, COWE_PWW_GWOUP6, WG_WCDDS_PCW_NCPO0(0));
		cowe_wwite(pwiv, COWE_PWW_GWOUP10, WG_WCDDS_SSC_DEWTA(ssc_dewta));
		cowe_wwite(pwiv, COWE_PWW_GWOUP11, WG_WCDDS_SSC_DEWTA1(ssc_dewta));
		cowe_wwite(pwiv, COWE_PWW_GWOUP4,
			   WG_SYSPWW_DDSFBK_EN | WG_SYSPWW_BIAS_EN |
			   WG_SYSPWW_BIAS_WPF_EN);
		cowe_wwite(pwiv, COWE_PWW_GWOUP2,
			   WG_SYSPWW_EN_NOWMAW | WG_SYSPWW_VODEN |
			   WG_SYSPWW_POSDIV(1));
		cowe_wwite(pwiv, COWE_PWW_GWOUP7,
			   WG_WCDDS_PCW_NCPO_CHG | WG_WCCDS_C(3) |
			   WG_WCDDS_PWDB | WG_WCDDS_ISO_EN);

		/* Enabwe the MT7530 TWGMII cwocks */
		cowe_set(pwiv, COWE_TWGMII_GSW_CWK_CG, WEG_TWGMIICK_EN);
	}

	wetuwn 0;
}

static boow mt7531_duaw_sgmii_suppowted(stwuct mt7530_pwiv *pwiv)
{
	u32 vaw;

	vaw = mt7530_wead(pwiv, MT7531_TOP_SIG_SW);

	wetuwn (vaw & PAD_DUAW_SGMII_EN) != 0;
}

static int
mt7531_pad_setup(stwuct dsa_switch *ds, phy_intewface_t intewface)
{
	wetuwn 0;
}

static void
mt7531_pww_setup(stwuct mt7530_pwiv *pwiv)
{
	u32 top_sig;
	u32 hwstwap;
	u32 xtaw;
	u32 vaw;

	if (mt7531_duaw_sgmii_suppowted(pwiv))
		wetuwn;

	vaw = mt7530_wead(pwiv, MT7531_CWEV);
	top_sig = mt7530_wead(pwiv, MT7531_TOP_SIG_SW);
	hwstwap = mt7530_wead(pwiv, MT7531_HWTWAP);
	if ((vaw & CHIP_WEV_M) > 0)
		xtaw = (top_sig & PAD_MCM_SMI_EN) ? HWTWAP_XTAW_FSEW_40MHZ :
						    HWTWAP_XTAW_FSEW_25MHZ;
	ewse
		xtaw = hwstwap & HWTWAP_XTAW_FSEW_MASK;

	/* Step 1 : Disabwe MT7531 COWEPWW */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_EN);
	vaw &= ~EN_COWEPWW;
	mt7530_wwite(pwiv, MT7531_PWWGP_EN, vaw);

	/* Step 2: switch to XTAW output */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_EN);
	vaw |= SW_CWKSW;
	mt7530_wwite(pwiv, MT7531_PWWGP_EN, vaw);

	vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
	vaw &= ~WG_COWEPWW_EN;
	mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);

	/* Step 3: disabwe PWWGP and enabwe pwogwam PWWGP */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_EN);
	vaw |= SW_PWWGP;
	mt7530_wwite(pwiv, MT7531_PWWGP_EN, vaw);

	/* Step 4: pwogwam COWEPWW output fwequency to 500MHz */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
	vaw &= ~WG_COWEPWW_POSDIV_M;
	vaw |= 2 << WG_COWEPWW_POSDIV_S;
	mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);
	usweep_wange(25, 35);

	switch (xtaw) {
	case HWTWAP_XTAW_FSEW_25MHZ:
		vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
		vaw &= ~WG_COWEPWW_SDM_PCW_M;
		vaw |= 0x140000 << WG_COWEPWW_SDM_PCW_S;
		mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);
		bweak;
	case HWTWAP_XTAW_FSEW_40MHZ:
		vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
		vaw &= ~WG_COWEPWW_SDM_PCW_M;
		vaw |= 0x190000 << WG_COWEPWW_SDM_PCW_S;
		mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);
		bweak;
	}

	/* Set feedback divide watio update signaw to high */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
	vaw |= WG_COWEPWW_SDM_PCW_CHG;
	mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);
	/* Wait fow at weast 16 XTAW cwocks */
	usweep_wange(10, 20);

	/* Step 5: set feedback divide watio update signaw to wow */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
	vaw &= ~WG_COWEPWW_SDM_PCW_CHG;
	mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);

	/* Enabwe 325M cwock fow SGMII */
	mt7530_wwite(pwiv, MT7531_ANA_PWWGP_CW5, 0xad0000);

	/* Enabwe 250SSC cwock fow WGMII */
	mt7530_wwite(pwiv, MT7531_ANA_PWWGP_CW2, 0x4f40000);

	/* Step 6: Enabwe MT7531 PWW */
	vaw = mt7530_wead(pwiv, MT7531_PWWGP_CW0);
	vaw |= WG_COWEPWW_EN;
	mt7530_wwite(pwiv, MT7531_PWWGP_CW0, vaw);

	vaw = mt7530_wead(pwiv, MT7531_PWWGP_EN);
	vaw |= EN_COWEPWW;
	mt7530_wwite(pwiv, MT7531_PWWGP_EN, vaw);
	usweep_wange(25, 35);
}

static void
mt7530_mib_weset(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mt7530_wwite(pwiv, MT7530_MIB_CCW, CCW_MIB_FWUSH);
	mt7530_wwite(pwiv, MT7530_MIB_CCW, CCW_MIB_ACTIVATE);
}

static int mt7530_phy_wead_c22(stwuct mt7530_pwiv *pwiv, int powt, int wegnum)
{
	wetuwn mdiobus_wead_nested(pwiv->bus, powt, wegnum);
}

static int mt7530_phy_wwite_c22(stwuct mt7530_pwiv *pwiv, int powt, int wegnum,
				u16 vaw)
{
	wetuwn mdiobus_wwite_nested(pwiv->bus, powt, wegnum, vaw);
}

static int mt7530_phy_wead_c45(stwuct mt7530_pwiv *pwiv, int powt,
			       int devad, int wegnum)
{
	wetuwn mdiobus_c45_wead_nested(pwiv->bus, powt, devad, wegnum);
}

static int mt7530_phy_wwite_c45(stwuct mt7530_pwiv *pwiv, int powt, int devad,
				int wegnum, u16 vaw)
{
	wetuwn mdiobus_c45_wwite_nested(pwiv->bus, powt, devad, wegnum, vaw);
}

static int
mt7531_ind_c45_phy_wead(stwuct mt7530_pwiv *pwiv, int powt, int devad,
			int wegnum)
{
	stwuct mt7530_dummy_poww p;
	u32 weg, vaw;
	int wet;

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7531_PHY_IAC);

	mt7530_mutex_wock(pwiv);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	weg = MT7531_MDIO_CW45_ADDW | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_DEV_ADDW(devad) | wegnum;
	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, weg | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	weg = MT7531_MDIO_CW45_WEAD | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_DEV_ADDW(devad);
	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, weg | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	wet = vaw & MT7531_MDIO_WW_DATA_MASK;
out:
	mt7530_mutex_unwock(pwiv);

	wetuwn wet;
}

static int
mt7531_ind_c45_phy_wwite(stwuct mt7530_pwiv *pwiv, int powt, int devad,
			 int wegnum, u16 data)
{
	stwuct mt7530_dummy_poww p;
	u32 vaw, weg;
	int wet;

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7531_PHY_IAC);

	mt7530_mutex_wock(pwiv);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	weg = MT7531_MDIO_CW45_ADDW | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_DEV_ADDW(devad) | wegnum;
	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, weg | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	weg = MT7531_MDIO_CW45_WWITE | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_DEV_ADDW(devad) | data;
	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, weg | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

out:
	mt7530_mutex_unwock(pwiv);

	wetuwn wet;
}

static int
mt7531_ind_c22_phy_wead(stwuct mt7530_pwiv *pwiv, int powt, int wegnum)
{
	stwuct mt7530_dummy_poww p;
	int wet;
	u32 vaw;

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7531_PHY_IAC);

	mt7530_mutex_wock(pwiv);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	vaw = MT7531_MDIO_CW22_WEAD | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_WEG_ADDW(wegnum);

	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, vaw | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, vaw,
				 !(vaw & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	wet = vaw & MT7531_MDIO_WW_DATA_MASK;
out:
	mt7530_mutex_unwock(pwiv);

	wetuwn wet;
}

static int
mt7531_ind_c22_phy_wwite(stwuct mt7530_pwiv *pwiv, int powt, int wegnum,
			 u16 data)
{
	stwuct mt7530_dummy_poww p;
	int wet;
	u32 weg;

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7531_PHY_IAC);

	mt7530_mutex_wock(pwiv);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, weg,
				 !(weg & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

	weg = MT7531_MDIO_CW22_WWITE | MT7531_MDIO_PHY_ADDW(powt) |
	      MT7531_MDIO_WEG_ADDW(wegnum) | data;

	mt7530_mii_wwite(pwiv, MT7531_PHY_IAC, weg | MT7531_PHY_ACS_ST);

	wet = weadx_poww_timeout(_mt7530_unwocked_wead, &p, weg,
				 !(weg & MT7531_PHY_ACS_ST), 20, 100000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		goto out;
	}

out:
	mt7530_mutex_unwock(pwiv);

	wetuwn wet;
}

static int
mt753x_phy_wead_c22(stwuct mii_bus *bus, int powt, int wegnum)
{
	stwuct mt7530_pwiv *pwiv = bus->pwiv;

	wetuwn pwiv->info->phy_wead_c22(pwiv, powt, wegnum);
}

static int
mt753x_phy_wead_c45(stwuct mii_bus *bus, int powt, int devad, int wegnum)
{
	stwuct mt7530_pwiv *pwiv = bus->pwiv;

	wetuwn pwiv->info->phy_wead_c45(pwiv, powt, devad, wegnum);
}

static int
mt753x_phy_wwite_c22(stwuct mii_bus *bus, int powt, int wegnum, u16 vaw)
{
	stwuct mt7530_pwiv *pwiv = bus->pwiv;

	wetuwn pwiv->info->phy_wwite_c22(pwiv, powt, wegnum, vaw);
}

static int
mt753x_phy_wwite_c45(stwuct mii_bus *bus, int powt, int devad, int wegnum,
		     u16 vaw)
{
	stwuct mt7530_pwiv *pwiv = bus->pwiv;

	wetuwn pwiv->info->phy_wwite_c45(pwiv, powt, devad, wegnum, vaw);
}

static void
mt7530_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
		   uint8_t *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(mt7530_mib); i++)
		ethtoow_puts(&data, mt7530_mib[i].name);
}

static void
mt7530_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
			 uint64_t *data)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	const stwuct mt7530_mib_desc *mib;
	u32 weg, i;
	u64 hi;

	fow (i = 0; i < AWWAY_SIZE(mt7530_mib); i++) {
		mib = &mt7530_mib[i];
		weg = MT7530_POWT_MIB_COUNTEW(powt) + mib->offset;

		data[i] = mt7530_wead(pwiv, weg);
		if (mib->size == 2) {
			hi = mt7530_wead(pwiv, weg + 4);
			data[i] |= hi << 32;
		}
	}
}

static int
mt7530_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn AWWAY_SIZE(mt7530_mib);
}

static int
mt7530_set_ageing_time(stwuct dsa_switch *ds, unsigned int msecs)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	unsigned int secs = msecs / 1000;
	unsigned int tmp_age_count;
	unsigned int ewwow = -1;
	unsigned int age_count;
	unsigned int age_unit;

	/* Appwied timew is (AGE_CNT + 1) * (AGE_UNIT + 1) seconds */
	if (secs < 1 || secs > (AGE_CNT_MAX + 1) * (AGE_UNIT_MAX + 1))
		wetuwn -EWANGE;

	/* itewate thwough aww possibwe age_count to find the cwosest paiw */
	fow (tmp_age_count = 0; tmp_age_count <= AGE_CNT_MAX; ++tmp_age_count) {
		unsigned int tmp_age_unit = secs / (tmp_age_count + 1) - 1;

		if (tmp_age_unit <= AGE_UNIT_MAX) {
			unsigned int tmp_ewwow = secs -
				(tmp_age_count + 1) * (tmp_age_unit + 1);

			/* found a cwosew paiw */
			if (ewwow > tmp_ewwow) {
				ewwow = tmp_ewwow;
				age_count = tmp_age_count;
				age_unit = tmp_age_unit;
			}

			/* found the exact match, so bweak the woop */
			if (!ewwow)
				bweak;
		}
	}

	mt7530_wwite(pwiv, MT7530_AAC, AGE_CNT(age_count) | AGE_UNIT(age_unit));

	wetuwn 0;
}

static const chaw *p5_intf_modes(unsigned int p5_intewface)
{
	switch (p5_intewface) {
	case P5_DISABWED:
		wetuwn "DISABWED";
	case P5_INTF_SEW_PHY_P0:
		wetuwn "PHY P0";
	case P5_INTF_SEW_PHY_P4:
		wetuwn "PHY P4";
	case P5_INTF_SEW_GMAC5:
		wetuwn "GMAC5";
	case P5_INTF_SEW_GMAC5_SGMII:
		wetuwn "GMAC5_SGMII";
	defauwt:
		wetuwn "unknown";
	}
}

static void mt7530_setup_powt5(stwuct dsa_switch *ds, phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u8 tx_deway = 0;
	int vaw;

	mutex_wock(&pwiv->weg_mutex);

	vaw = mt7530_wead(pwiv, MT7530_MHWTWAP);

	vaw |= MHWTWAP_MANUAW | MHWTWAP_P5_MAC_SEW | MHWTWAP_P5_DIS;
	vaw &= ~MHWTWAP_P5_WGMII_MODE & ~MHWTWAP_PHY0_SEW;

	switch (pwiv->p5_intf_sew) {
	case P5_INTF_SEW_PHY_P0:
		/* MT7530_P5_MODE_GPHY_P0: 2nd GMAC -> P5 -> P0 */
		vaw |= MHWTWAP_PHY0_SEW;
		fawwthwough;
	case P5_INTF_SEW_PHY_P4:
		/* MT7530_P5_MODE_GPHY_P4: 2nd GMAC -> P5 -> P4 */
		vaw &= ~MHWTWAP_P5_MAC_SEW & ~MHWTWAP_P5_DIS;

		/* Setup the MAC by defauwt fow the cpu powt */
		mt7530_wwite(pwiv, MT7530_PMCW_P(5), 0x56300);
		bweak;
	case P5_INTF_SEW_GMAC5:
		/* MT7530_P5_MODE_GMAC: P5 -> Extewnaw phy ow 2nd GMAC */
		vaw &= ~MHWTWAP_P5_DIS;
		bweak;
	case P5_DISABWED:
		intewface = PHY_INTEWFACE_MODE_NA;
		bweak;
	defauwt:
		dev_eww(ds->dev, "Unsuppowted p5_intf_sew %d\n",
			pwiv->p5_intf_sew);
		goto unwock_exit;
	}

	/* Setup WGMII settings */
	if (phy_intewface_mode_is_wgmii(intewface)) {
		vaw |= MHWTWAP_P5_WGMII_MODE;

		/* P5 WGMII WX Cwock Contwow: deway setting fow 1000M */
		mt7530_wwite(pwiv, MT7530_P5WGMIIWXCW, CSW_WGMII_EDGE_AWIGN);

		/* Don't set deway in DSA mode */
		if (!dsa_is_dsa_powt(pwiv->ds, 5) &&
		    (intewface == PHY_INTEWFACE_MODE_WGMII_TXID ||
		     intewface == PHY_INTEWFACE_MODE_WGMII_ID))
			tx_deway = 4; /* n * 0.5 ns */

		/* P5 WGMII TX Cwock Contwow: deway x */
		mt7530_wwite(pwiv, MT7530_P5WGMIITXCW,
			     CSW_WGMII_TXC_CFG(0x10 + tx_deway));

		/* weduce P5 WGMII Tx dwiving, 8mA */
		mt7530_wwite(pwiv, MT7530_IO_DWV_CW,
			     P5_IO_CWK_DWV(1) | P5_IO_DATA_DWV(1));
	}

	mt7530_wwite(pwiv, MT7530_MHWTWAP, vaw);

	dev_dbg(ds->dev, "Setup P5, HWTWAP=0x%x, intf_sew=%s, phy-mode=%s\n",
		vaw, p5_intf_modes(pwiv->p5_intf_sew), phy_modes(intewface));

	pwiv->p5_intewface = intewface;

unwock_exit:
	mutex_unwock(&pwiv->weg_mutex);
}

static void
mt753x_twap_fwames(stwuct mt7530_pwiv *pwiv)
{
	/* Twap BPDUs to the CPU powt(s) */
	mt7530_wmw(pwiv, MT753X_BPC, MT753X_BPDU_POWT_FW_MASK,
		   MT753X_BPDU_CPU_ONWY);

	/* Twap 802.1X PAE fwames to the CPU powt(s) */
	mt7530_wmw(pwiv, MT753X_BPC, MT753X_PAE_POWT_FW_MASK,
		   MT753X_PAE_POWT_FW(MT753X_BPDU_CPU_ONWY));

	/* Twap WWDP fwames with :0E MAC DA to the CPU powt(s) */
	mt7530_wmw(pwiv, MT753X_WGAC2, MT753X_W0E_POWT_FW_MASK,
		   MT753X_W0E_POWT_FW(MT753X_BPDU_CPU_ONWY));
}

static int
mt753x_cpu_powt_enabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int wet;

	/* Setup max capabiwity of CPU powt at fiwst */
	if (pwiv->info->cpu_powt_config) {
		wet = pwiv->info->cpu_powt_config(ds, powt);
		if (wet)
			wetuwn wet;
	}

	/* Enabwe Mediatek headew mode on the cpu powt */
	mt7530_wwite(pwiv, MT7530_PVC_P(powt),
		     POWT_SPEC_TAG);

	/* Enabwe fwooding on the CPU powt */
	mt7530_set(pwiv, MT7530_MFC, BC_FFP(BIT(powt)) | UNM_FFP(BIT(powt)) |
		   UNU_FFP(BIT(powt)));

	/* Set CPU powt numbew */
	if (pwiv->id == ID_MT7530 || pwiv->id == ID_MT7621)
		mt7530_wmw(pwiv, MT7530_MFC, CPU_MASK, CPU_EN | CPU_POWT(powt));

	/* Add the CPU powt to the CPU powt bitmap fow MT7531 and the switch on
	 * the MT7988 SoC. Twapped fwames wiww be fowwawded to the CPU powt that
	 * is affine to the inbound usew powt.
	 */
	if (pwiv->id == ID_MT7531 || pwiv->id == ID_MT7988)
		mt7530_set(pwiv, MT7531_CFC, MT7531_CPU_PMAP(BIT(powt)));

	/* CPU powt gets connected to aww usew powts of
	 * the switch.
	 */
	mt7530_wwite(pwiv, MT7530_PCW_P(powt),
		     PCW_MATWIX(dsa_usew_powts(pwiv->ds)));

	/* Set to fawwback mode fow independent VWAN weawning */
	mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_POWT_VWAN_MASK,
		   MT7530_POWT_FAWWBACK_MODE);

	wetuwn 0;
}

static int
mt7530_powt_enabwe(stwuct dsa_switch *ds, int powt,
		   stwuct phy_device *phy)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	/* Awwow the usew powt gets connected to the cpu powt and awso
	 * westowe the powt matwix if the powt is the membew of a cewtain
	 * bwidge.
	 */
	if (dsa_powt_is_usew(dp)) {
		stwuct dsa_powt *cpu_dp = dp->cpu_dp;

		pwiv->powts[powt].pm |= PCW_MATWIX(BIT(cpu_dp->index));
	}
	pwiv->powts[powt].enabwe = twue;
	mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_MATWIX_MASK,
		   pwiv->powts[powt].pm);
	mt7530_cweaw(pwiv, MT7530_PMCW_P(powt), PMCW_WINK_SETTINGS_MASK);

	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

static void
mt7530_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	/* Cweaw up aww powt matwix which couwd be westowed in the next
	 * enabwement fow the powt.
	 */
	pwiv->powts[powt].enabwe = fawse;
	mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_MATWIX_MASK,
		   PCW_MATWIX_CWW);
	mt7530_cweaw(pwiv, MT7530_PMCW_P(powt), PMCW_WINK_SETTINGS_MASK);

	mutex_unwock(&pwiv->weg_mutex);
}

static int
mt7530_powt_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int wength;
	u32 vaw;

	/* When a new MTU is set, DSA awways set the CPU powt's MTU to the
	 * wawgest MTU of the usew powts. Because the switch onwy has a gwobaw
	 * WX wength wegistew, onwy awwowing CPU powt hewe is enough.
	 */
	if (!dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	mt7530_mutex_wock(pwiv);

	vaw = mt7530_mii_wead(pwiv, MT7530_GMACCW);
	vaw &= ~MAX_WX_PKT_WEN_MASK;

	/* WX wength awso incwudes Ethewnet headew, MTK tag, and FCS wength */
	wength = new_mtu + ETH_HWEN + MTK_HDW_WEN + ETH_FCS_WEN;
	if (wength <= 1522) {
		vaw |= MAX_WX_PKT_WEN_1522;
	} ewse if (wength <= 1536) {
		vaw |= MAX_WX_PKT_WEN_1536;
	} ewse if (wength <= 1552) {
		vaw |= MAX_WX_PKT_WEN_1552;
	} ewse {
		vaw &= ~MAX_WX_JUMBO_MASK;
		vaw |= MAX_WX_JUMBO(DIV_WOUND_UP(wength, 1024));
		vaw |= MAX_WX_PKT_WEN_JUMBO;
	}

	mt7530_mii_wwite(pwiv, MT7530_GMACCW, vaw);

	mt7530_mutex_unwock(pwiv);

	wetuwn 0;
}

static int
mt7530_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn MT7530_MAX_MTU;
}

static void
mt7530_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 stp_state;

	switch (state) {
	case BW_STATE_DISABWED:
		stp_state = MT7530_STP_DISABWED;
		bweak;
	case BW_STATE_BWOCKING:
		stp_state = MT7530_STP_BWOCKING;
		bweak;
	case BW_STATE_WISTENING:
		stp_state = MT7530_STP_WISTENING;
		bweak;
	case BW_STATE_WEAWNING:
		stp_state = MT7530_STP_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
	defauwt:
		stp_state = MT7530_STP_FOWWAWDING;
		bweak;
	}

	mt7530_wmw(pwiv, MT7530_SSP_P(powt), FID_PST_MASK(FID_BWIDGED),
		   FID_PST(FID_BWIDGED, stp_state));
}

static int
mt7530_powt_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
			     stwuct switchdev_bwpowt_fwags fwags,
			     stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~(BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD |
			   BW_BCAST_FWOOD))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
mt7530_powt_bwidge_fwags(stwuct dsa_switch *ds, int powt,
			 stwuct switchdev_bwpowt_fwags fwags,
			 stwuct netwink_ext_ack *extack)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	if (fwags.mask & BW_WEAWNING)
		mt7530_wmw(pwiv, MT7530_PSC_P(powt), SA_DIS,
			   fwags.vaw & BW_WEAWNING ? 0 : SA_DIS);

	if (fwags.mask & BW_FWOOD)
		mt7530_wmw(pwiv, MT7530_MFC, UNU_FFP(BIT(powt)),
			   fwags.vaw & BW_FWOOD ? UNU_FFP(BIT(powt)) : 0);

	if (fwags.mask & BW_MCAST_FWOOD)
		mt7530_wmw(pwiv, MT7530_MFC, UNM_FFP(BIT(powt)),
			   fwags.vaw & BW_MCAST_FWOOD ? UNM_FFP(BIT(powt)) : 0);

	if (fwags.mask & BW_BCAST_FWOOD)
		mt7530_wmw(pwiv, MT7530_MFC, BC_FFP(BIT(powt)),
			   fwags.vaw & BW_BCAST_FWOOD ? BC_FFP(BIT(powt)) : 0);

	wetuwn 0;
}

static int
mt7530_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
			stwuct dsa_bwidge bwidge, boow *tx_fwd_offwoad,
			stwuct netwink_ext_ack *extack)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt), *othew_dp;
	stwuct dsa_powt *cpu_dp = dp->cpu_dp;
	u32 powt_bitmap = BIT(cpu_dp->index);
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	dsa_switch_fow_each_usew_powt(othew_dp, ds) {
		int othew_powt = othew_dp->index;

		if (dp == othew_dp)
			continue;

		/* Add this powt to the powt matwix of the othew powts in the
		 * same bwidge. If the powt is disabwed, powt matwix is kept
		 * and not being setup untiw the powt becomes enabwed.
		 */
		if (!dsa_powt_offwoads_bwidge(othew_dp, &bwidge))
			continue;

		if (pwiv->powts[othew_powt].enabwe)
			mt7530_set(pwiv, MT7530_PCW_P(othew_powt),
				   PCW_MATWIX(BIT(powt)));
		pwiv->powts[othew_powt].pm |= PCW_MATWIX(BIT(powt));

		powt_bitmap |= BIT(othew_powt);
	}

	/* Add the aww othew powts to this powt matwix. */
	if (pwiv->powts[powt].enabwe)
		mt7530_wmw(pwiv, MT7530_PCW_P(powt),
			   PCW_MATWIX_MASK, PCW_MATWIX(powt_bitmap));
	pwiv->powts[powt].pm |= PCW_MATWIX(powt_bitmap);

	/* Set to fawwback mode fow independent VWAN weawning */
	mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_POWT_VWAN_MASK,
		   MT7530_POWT_FAWWBACK_MODE);

	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

static void
mt7530_powt_set_vwan_unawawe(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	boow aww_usew_powts_wemoved = twue;
	int i;

	/* This is cawwed aftew .powt_bwidge_weave when weaving a VWAN-awawe
	 * bwidge. Don't set standawone powts to fawwback mode.
	 */
	if (dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt)))
		mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_POWT_VWAN_MASK,
			   MT7530_POWT_FAWWBACK_MODE);

	mt7530_wmw(pwiv, MT7530_PVC_P(powt),
		   VWAN_ATTW_MASK | PVC_EG_TAG_MASK | ACC_FWM_MASK,
		   VWAN_ATTW(MT7530_VWAN_TWANSPAWENT) |
		   PVC_EG_TAG(MT7530_VWAN_EG_CONSISTENT) |
		   MT7530_VWAN_ACC_AWW);

	/* Set PVID to 0 */
	mt7530_wmw(pwiv, MT7530_PPBV1_P(powt), G0_POWT_VID_MASK,
		   G0_POWT_VID_DEF);

	fow (i = 0; i < MT7530_NUM_POWTS; i++) {
		if (dsa_is_usew_powt(ds, i) &&
		    dsa_powt_is_vwan_fiwtewing(dsa_to_powt(ds, i))) {
			aww_usew_powts_wemoved = fawse;
			bweak;
		}
	}

	/* CPU powt awso does the same thing untiw aww usew powts bewonging to
	 * the CPU powt get out of VWAN fiwtewing mode.
	 */
	if (aww_usew_powts_wemoved) {
		stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
		stwuct dsa_powt *cpu_dp = dp->cpu_dp;

		mt7530_wwite(pwiv, MT7530_PCW_P(cpu_dp->index),
			     PCW_MATWIX(dsa_usew_powts(pwiv->ds)));
		mt7530_wwite(pwiv, MT7530_PVC_P(cpu_dp->index), POWT_SPEC_TAG
			     | PVC_EG_TAG(MT7530_VWAN_EG_CONSISTENT));
	}
}

static void
mt7530_powt_set_vwan_awawe(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	/* Twapped into secuwity mode awwows packet fowwawding thwough VWAN
	 * tabwe wookup.
	 */
	if (dsa_is_usew_powt(ds, powt)) {
		mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_POWT_VWAN_MASK,
			   MT7530_POWT_SECUWITY_MODE);
		mt7530_wmw(pwiv, MT7530_PPBV1_P(powt), G0_POWT_VID_MASK,
			   G0_POWT_VID(pwiv->powts[powt].pvid));

		/* Onwy accept tagged fwames if PVID is not set */
		if (!pwiv->powts[powt].pvid)
			mt7530_wmw(pwiv, MT7530_PVC_P(powt), ACC_FWM_MASK,
				   MT7530_VWAN_ACC_TAGGED);

		/* Set the powt as a usew powt which is to be abwe to wecognize
		 * VID fwom incoming packets befowe fetching entwy within the
		 * VWAN tabwe.
		 */
		mt7530_wmw(pwiv, MT7530_PVC_P(powt),
			   VWAN_ATTW_MASK | PVC_EG_TAG_MASK,
			   VWAN_ATTW(MT7530_VWAN_USEW) |
			   PVC_EG_TAG(MT7530_VWAN_EG_DISABWED));
	} ewse {
		/* Awso set CPU powts to the "usew" VWAN powt attwibute, to
		 * awwow VWAN cwassification, but keep the EG_TAG attwibute as
		 * "consistent" (i.o.w. don't change its vawue) fow packets
		 * weceived by the switch fwom the CPU, so that tagged packets
		 * awe fowwawded to usew powts as tagged, and untagged as
		 * untagged.
		 */
		mt7530_wmw(pwiv, MT7530_PVC_P(powt), VWAN_ATTW_MASK,
			   VWAN_ATTW(MT7530_VWAN_USEW));
	}
}

static void
mt7530_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
			 stwuct dsa_bwidge bwidge)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt), *othew_dp;
	stwuct dsa_powt *cpu_dp = dp->cpu_dp;
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	dsa_switch_fow_each_usew_powt(othew_dp, ds) {
		int othew_powt = othew_dp->index;

		if (dp == othew_dp)
			continue;

		/* Wemove this powt fwom the powt matwix of the othew powts
		 * in the same bwidge. If the powt is disabwed, powt matwix
		 * is kept and not being setup untiw the powt becomes enabwed.
		 */
		if (!dsa_powt_offwoads_bwidge(othew_dp, &bwidge))
			continue;

		if (pwiv->powts[othew_powt].enabwe)
			mt7530_cweaw(pwiv, MT7530_PCW_P(othew_powt),
				     PCW_MATWIX(BIT(powt)));
		pwiv->powts[othew_powt].pm &= ~PCW_MATWIX(BIT(powt));
	}

	/* Set the cpu powt to be the onwy one in the powt matwix of
	 * this powt.
	 */
	if (pwiv->powts[powt].enabwe)
		mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_MATWIX_MASK,
			   PCW_MATWIX(BIT(cpu_dp->index)));
	pwiv->powts[powt].pm = PCW_MATWIX(BIT(cpu_dp->index));

	/* When a powt is wemoved fwom the bwidge, the powt wouwd be set up
	 * back to the defauwt as is at initiaw boot which is a VWAN-unawawe
	 * powt.
	 */
	mt7530_wmw(pwiv, MT7530_PCW_P(powt), PCW_POWT_VWAN_MASK,
		   MT7530_POWT_MATWIX_MODE);

	mutex_unwock(&pwiv->weg_mutex);
}

static int
mt7530_powt_fdb_add(stwuct dsa_switch *ds, int powt,
		    const unsigned chaw *addw, u16 vid,
		    stwuct dsa_db db)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int wet;
	u8 powt_mask = BIT(powt);

	mutex_wock(&pwiv->weg_mutex);
	mt7530_fdb_wwite(pwiv, vid, powt_mask, addw, -1, STATIC_ENT);
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_WWITE, NUWW);
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int
mt7530_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
		    const unsigned chaw *addw, u16 vid,
		    stwuct dsa_db db)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int wet;
	u8 powt_mask = BIT(powt);

	mutex_wock(&pwiv->weg_mutex);
	mt7530_fdb_wwite(pwiv, vid, powt_mask, addw, -1, STATIC_EMP);
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_WWITE, NUWW);
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int
mt7530_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
		     dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	stwuct mt7530_fdb _fdb = { 0 };
	int cnt = MT7530_NUM_FDB_WECOWDS;
	int wet = 0;
	u32 wsp = 0;

	mutex_wock(&pwiv->weg_mutex);

	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_STAWT, &wsp);
	if (wet < 0)
		goto eww;

	do {
		if (wsp & ATC_SWCH_HIT) {
			mt7530_fdb_wead(pwiv, &_fdb);
			if (_fdb.powt_mask & BIT(powt)) {
				wet = cb(_fdb.mac, _fdb.vid, _fdb.noawp,
					 data);
				if (wet < 0)
					bweak;
			}
		}
	} whiwe (--cnt &&
		 !(wsp & ATC_SWCH_END) &&
		 !mt7530_fdb_cmd(pwiv, MT7530_FDB_NEXT, &wsp));
eww:
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

static int
mt7530_powt_mdb_add(stwuct dsa_switch *ds, int powt,
		    const stwuct switchdev_obj_powt_mdb *mdb,
		    stwuct dsa_db db)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	const u8 *addw = mdb->addw;
	u16 vid = mdb->vid;
	u8 powt_mask = 0;
	int wet;

	mutex_wock(&pwiv->weg_mutex);

	mt7530_fdb_wwite(pwiv, vid, 0, addw, 0, STATIC_EMP);
	if (!mt7530_fdb_cmd(pwiv, MT7530_FDB_WEAD, NUWW))
		powt_mask = (mt7530_wead(pwiv, MT7530_ATWD) >> POWT_MAP)
			    & POWT_MAP_MASK;

	powt_mask |= BIT(powt);
	mt7530_fdb_wwite(pwiv, vid, powt_mask, addw, -1, STATIC_ENT);
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_WWITE, NUWW);

	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int
mt7530_powt_mdb_dew(stwuct dsa_switch *ds, int powt,
		    const stwuct switchdev_obj_powt_mdb *mdb,
		    stwuct dsa_db db)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	const u8 *addw = mdb->addw;
	u16 vid = mdb->vid;
	u8 powt_mask = 0;
	int wet;

	mutex_wock(&pwiv->weg_mutex);

	mt7530_fdb_wwite(pwiv, vid, 0, addw, 0, STATIC_EMP);
	if (!mt7530_fdb_cmd(pwiv, MT7530_FDB_WEAD, NUWW))
		powt_mask = (mt7530_wead(pwiv, MT7530_ATWD) >> POWT_MAP)
			    & POWT_MAP_MASK;

	powt_mask &= ~BIT(powt);
	mt7530_fdb_wwite(pwiv, vid, powt_mask, addw, -1,
			 powt_mask ? STATIC_ENT : STATIC_EMP);
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_WWITE, NUWW);

	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int
mt7530_vwan_cmd(stwuct mt7530_pwiv *pwiv, enum mt7530_vwan_cmd cmd, u16 vid)
{
	stwuct mt7530_dummy_poww p;
	u32 vaw;
	int wet;

	vaw = VTCW_BUSY | VTCW_FUNC(cmd) | vid;
	mt7530_wwite(pwiv, MT7530_VTCW, vaw);

	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7530_VTCW);
	wet = weadx_poww_timeout(_mt7530_wead, &p, vaw,
				 !(vaw & VTCW_BUSY), 20, 20000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "poww timeout\n");
		wetuwn wet;
	}

	vaw = mt7530_wead(pwiv, MT7530_VTCW);
	if (vaw & VTCW_INVAWID) {
		dev_eww(pwiv->dev, "wead VTCW invawid\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
mt7530_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt, boow vwan_fiwtewing,
			   stwuct netwink_ext_ack *extack)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct dsa_powt *cpu_dp = dp->cpu_dp;

	if (vwan_fiwtewing) {
		/* The powt is being kept as VWAN-unawawe powt when bwidge is
		 * set up with vwan_fiwtewing not being set, Othewwise, the
		 * powt and the cowwesponding CPU powt is wequiwed the setup
		 * fow becoming a VWAN-awawe powt.
		 */
		mt7530_powt_set_vwan_awawe(ds, powt);
		mt7530_powt_set_vwan_awawe(ds, cpu_dp->index);
	} ewse {
		mt7530_powt_set_vwan_unawawe(ds, powt);
	}

	wetuwn 0;
}

static void
mt7530_hw_vwan_add(stwuct mt7530_pwiv *pwiv,
		   stwuct mt7530_hw_vwan_entwy *entwy)
{
	stwuct dsa_powt *dp = dsa_to_powt(pwiv->ds, entwy->powt);
	u8 new_membews;
	u32 vaw;

	new_membews = entwy->owd_membews | BIT(entwy->powt);

	/* Vawidate the entwy with independent weawning, cweate egwess tag pew
	 * VWAN and joining the powt as one of the powt membews.
	 */
	vaw = IVW_MAC | VTAG_EN | POWT_MEM(new_membews) | FID(FID_BWIDGED) |
	      VWAN_VAWID;
	mt7530_wwite(pwiv, MT7530_VAWD1, vaw);

	/* Decide whethew adding tag ow not fow those outgoing packets fwom the
	 * powt inside the VWAN.
	 * CPU powt is awways taken as a tagged powt fow sewving mowe than one
	 * VWANs acwoss and awso being appwied with egwess type stack mode fow
	 * that VWAN tags wouwd be appended aftew hawdwawe speciaw tag used as
	 * DSA tag.
	 */
	if (dsa_powt_is_cpu(dp))
		vaw = MT7530_VWAN_EGWESS_STACK;
	ewse if (entwy->untagged)
		vaw = MT7530_VWAN_EGWESS_UNTAG;
	ewse
		vaw = MT7530_VWAN_EGWESS_TAG;
	mt7530_wmw(pwiv, MT7530_VAWD2,
		   ETAG_CTWW_P_MASK(entwy->powt),
		   ETAG_CTWW_P(entwy->powt, vaw));
}

static void
mt7530_hw_vwan_dew(stwuct mt7530_pwiv *pwiv,
		   stwuct mt7530_hw_vwan_entwy *entwy)
{
	u8 new_membews;
	u32 vaw;

	new_membews = entwy->owd_membews & ~BIT(entwy->powt);

	vaw = mt7530_wead(pwiv, MT7530_VAWD1);
	if (!(vaw & VWAN_VAWID)) {
		dev_eww(pwiv->dev,
			"Cannot be deweted due to invawid entwy\n");
		wetuwn;
	}

	if (new_membews) {
		vaw = IVW_MAC | VTAG_EN | POWT_MEM(new_membews) |
		      VWAN_VAWID;
		mt7530_wwite(pwiv, MT7530_VAWD1, vaw);
	} ewse {
		mt7530_wwite(pwiv, MT7530_VAWD1, 0);
		mt7530_wwite(pwiv, MT7530_VAWD2, 0);
	}
}

static void
mt7530_hw_vwan_update(stwuct mt7530_pwiv *pwiv, u16 vid,
		      stwuct mt7530_hw_vwan_entwy *entwy,
		      mt7530_vwan_op vwan_op)
{
	u32 vaw;

	/* Fetch entwy */
	mt7530_vwan_cmd(pwiv, MT7530_VTCW_WD_VID, vid);

	vaw = mt7530_wead(pwiv, MT7530_VAWD1);

	entwy->owd_membews = (vaw >> POWT_MEM_SHFT) & POWT_MEM_MASK;

	/* Manipuwate entwy */
	vwan_op(pwiv, entwy);

	/* Fwush wesuwt to hawdwawe */
	mt7530_vwan_cmd(pwiv, MT7530_VTCW_WW_VID, vid);
}

static int
mt7530_setup_vwan0(stwuct mt7530_pwiv *pwiv)
{
	u32 vaw;

	/* Vawidate the entwy with independent weawning, keep the owiginaw
	 * ingwess tag attwibute.
	 */
	vaw = IVW_MAC | EG_CON | POWT_MEM(MT7530_AWW_MEMBEWS) | FID(FID_BWIDGED) |
	      VWAN_VAWID;
	mt7530_wwite(pwiv, MT7530_VAWD1, vaw);

	wetuwn mt7530_vwan_cmd(pwiv, MT7530_VTCW_WW_VID, 0);
}

static int
mt7530_powt_vwan_add(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan,
		     stwuct netwink_ext_ack *extack)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct mt7530_hw_vwan_entwy new_entwy;
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	mt7530_hw_vwan_entwy_init(&new_entwy, powt, untagged);
	mt7530_hw_vwan_update(pwiv, vwan->vid, &new_entwy, mt7530_hw_vwan_add);

	if (pvid) {
		pwiv->powts[powt].pvid = vwan->vid;

		/* Accept aww fwames if PVID is set */
		mt7530_wmw(pwiv, MT7530_PVC_P(powt), ACC_FWM_MASK,
			   MT7530_VWAN_ACC_AWW);

		/* Onwy configuwe PVID if VWAN fiwtewing is enabwed */
		if (dsa_powt_is_vwan_fiwtewing(dsa_to_powt(ds, powt)))
			mt7530_wmw(pwiv, MT7530_PPBV1_P(powt),
				   G0_POWT_VID_MASK,
				   G0_POWT_VID(vwan->vid));
	} ewse if (vwan->vid && pwiv->powts[powt].pvid == vwan->vid) {
		/* This VWAN is ovewwwitten without PVID, so unset it */
		pwiv->powts[powt].pvid = G0_POWT_VID_DEF;

		/* Onwy accept tagged fwames if the powt is VWAN-awawe */
		if (dsa_powt_is_vwan_fiwtewing(dsa_to_powt(ds, powt)))
			mt7530_wmw(pwiv, MT7530_PVC_P(powt), ACC_FWM_MASK,
				   MT7530_VWAN_ACC_TAGGED);

		mt7530_wmw(pwiv, MT7530_PPBV1_P(powt), G0_POWT_VID_MASK,
			   G0_POWT_VID_DEF);
	}

	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

static int
mt7530_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct mt7530_hw_vwan_entwy tawget_entwy;
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);

	mt7530_hw_vwan_entwy_init(&tawget_entwy, powt, 0);
	mt7530_hw_vwan_update(pwiv, vwan->vid, &tawget_entwy,
			      mt7530_hw_vwan_dew);

	/* PVID is being westowed to the defauwt whenevew the PVID powt
	 * is being wemoved fwom the VWAN.
	 */
	if (pwiv->powts[powt].pvid == vwan->vid) {
		pwiv->powts[powt].pvid = G0_POWT_VID_DEF;

		/* Onwy accept tagged fwames if the powt is VWAN-awawe */
		if (dsa_powt_is_vwan_fiwtewing(dsa_to_powt(ds, powt)))
			mt7530_wmw(pwiv, MT7530_PVC_P(powt), ACC_FWM_MASK,
				   MT7530_VWAN_ACC_TAGGED);

		mt7530_wmw(pwiv, MT7530_PPBV1_P(powt), G0_POWT_VID_MASK,
			   G0_POWT_VID_DEF);
	}


	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

static int mt753x_miwwow_powt_get(unsigned int id, u32 vaw)
{
	wetuwn (id == ID_MT7531) ? MT7531_MIWWOW_POWT_GET(vaw) :
				   MIWWOW_POWT(vaw);
}

static int mt753x_miwwow_powt_set(unsigned int id, u32 vaw)
{
	wetuwn (id == ID_MT7531) ? MT7531_MIWWOW_POWT_SET(vaw) :
				   MIWWOW_POWT(vaw);
}

static int mt753x_powt_miwwow_add(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_maww_miwwow_tc_entwy *miwwow,
				  boow ingwess, stwuct netwink_ext_ack *extack)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int monitow_powt;
	u32 vaw;

	/* Check fow existent entwy */
	if ((ingwess ? pwiv->miwwow_wx : pwiv->miwwow_tx) & BIT(powt))
		wetuwn -EEXIST;

	vaw = mt7530_wead(pwiv, MT753X_MIWWOW_WEG(pwiv->id));

	/* MT7530 onwy suppowts one monitow powt */
	monitow_powt = mt753x_miwwow_powt_get(pwiv->id, vaw);
	if (vaw & MT753X_MIWWOW_EN(pwiv->id) &&
	    monitow_powt != miwwow->to_wocaw_powt)
		wetuwn -EEXIST;

	vaw |= MT753X_MIWWOW_EN(pwiv->id);
	vaw &= ~MT753X_MIWWOW_MASK(pwiv->id);
	vaw |= mt753x_miwwow_powt_set(pwiv->id, miwwow->to_wocaw_powt);
	mt7530_wwite(pwiv, MT753X_MIWWOW_WEG(pwiv->id), vaw);

	vaw = mt7530_wead(pwiv, MT7530_PCW_P(powt));
	if (ingwess) {
		vaw |= POWT_WX_MIW;
		pwiv->miwwow_wx |= BIT(powt);
	} ewse {
		vaw |= POWT_TX_MIW;
		pwiv->miwwow_tx |= BIT(powt);
	}
	mt7530_wwite(pwiv, MT7530_PCW_P(powt), vaw);

	wetuwn 0;
}

static void mt753x_powt_miwwow_dew(stwuct dsa_switch *ds, int powt,
				   stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 vaw;

	vaw = mt7530_wead(pwiv, MT7530_PCW_P(powt));
	if (miwwow->ingwess) {
		vaw &= ~POWT_WX_MIW;
		pwiv->miwwow_wx &= ~BIT(powt);
	} ewse {
		vaw &= ~POWT_TX_MIW;
		pwiv->miwwow_tx &= ~BIT(powt);
	}
	mt7530_wwite(pwiv, MT7530_PCW_P(powt), vaw);

	if (!pwiv->miwwow_wx && !pwiv->miwwow_tx) {
		vaw = mt7530_wead(pwiv, MT753X_MIWWOW_WEG(pwiv->id));
		vaw &= ~MT753X_MIWWOW_EN(pwiv->id);
		mt7530_wwite(pwiv, MT753X_MIWWOW_WEG(pwiv->id), vaw);
	}
}

static enum dsa_tag_pwotocow
mtk_get_tag_pwotocow(stwuct dsa_switch *ds, int powt,
		     enum dsa_tag_pwotocow mp)
{
	wetuwn DSA_TAG_PWOTO_MTK;
}

#ifdef CONFIG_GPIOWIB
static inwine u32
mt7530_gpio_to_bit(unsigned int offset)
{
	/* Map GPIO offset to wegistew bit
	 * [ 2: 0]  powt 0 WED 0..2 as GPIO 0..2
	 * [ 6: 4]  powt 1 WED 0..2 as GPIO 3..5
	 * [10: 8]  powt 2 WED 0..2 as GPIO 6..8
	 * [14:12]  powt 3 WED 0..2 as GPIO 9..11
	 * [18:16]  powt 4 WED 0..2 as GPIO 12..14
	 */
	wetuwn BIT(offset + offset / 3);
}

static int
mt7530_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct mt7530_pwiv *pwiv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	wetuwn !!(mt7530_wead(pwiv, MT7530_WED_GPIO_DATA) & bit);
}

static void
mt7530_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct mt7530_pwiv *pwiv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	if (vawue)
		mt7530_set(pwiv, MT7530_WED_GPIO_DATA, bit);
	ewse
		mt7530_cweaw(pwiv, MT7530_WED_GPIO_DATA, bit);
}

static int
mt7530_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct mt7530_pwiv *pwiv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	wetuwn (mt7530_wead(pwiv, MT7530_WED_GPIO_DIW) & bit) ?
		GPIO_WINE_DIWECTION_OUT : GPIO_WINE_DIWECTION_IN;
}

static int
mt7530_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct mt7530_pwiv *pwiv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	mt7530_cweaw(pwiv, MT7530_WED_GPIO_OE, bit);
	mt7530_cweaw(pwiv, MT7530_WED_GPIO_DIW, bit);

	wetuwn 0;
}

static int
mt7530_gpio_diwection_output(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct mt7530_pwiv *pwiv = gpiochip_get_data(gc);
	u32 bit = mt7530_gpio_to_bit(offset);

	mt7530_set(pwiv, MT7530_WED_GPIO_DIW, bit);

	if (vawue)
		mt7530_set(pwiv, MT7530_WED_GPIO_DATA, bit);
	ewse
		mt7530_cweaw(pwiv, MT7530_WED_GPIO_DATA, bit);

	mt7530_set(pwiv, MT7530_WED_GPIO_OE, bit);

	wetuwn 0;
}

static int
mt7530_setup_gpio(stwuct mt7530_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	stwuct gpio_chip *gc;

	gc = devm_kzawwoc(dev, sizeof(*gc), GFP_KEWNEW);
	if (!gc)
		wetuwn -ENOMEM;

	mt7530_wwite(pwiv, MT7530_WED_GPIO_OE, 0);
	mt7530_wwite(pwiv, MT7530_WED_GPIO_DIW, 0);
	mt7530_wwite(pwiv, MT7530_WED_IO_MODE, 0);

	gc->wabew = "mt7530";
	gc->pawent = dev;
	gc->ownew = THIS_MODUWE;
	gc->get_diwection = mt7530_gpio_get_diwection;
	gc->diwection_input = mt7530_gpio_diwection_input;
	gc->diwection_output = mt7530_gpio_diwection_output;
	gc->get = mt7530_gpio_get;
	gc->set = mt7530_gpio_set;
	gc->base = -1;
	gc->ngpio = 15;
	gc->can_sweep = twue;

	wetuwn devm_gpiochip_add_data(dev, gc, pwiv);
}
#endif /* CONFIG_GPIOWIB */

static iwqwetuwn_t
mt7530_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct mt7530_pwiv *pwiv = dev_id;
	boow handwed = fawse;
	u32 vaw;
	int p;

	mt7530_mutex_wock(pwiv);
	vaw = mt7530_mii_wead(pwiv, MT7530_SYS_INT_STS);
	mt7530_mii_wwite(pwiv, MT7530_SYS_INT_STS, vaw);
	mt7530_mutex_unwock(pwiv);

	fow (p = 0; p < MT7530_NUM_PHYS; p++) {
		if (BIT(p) & vaw) {
			unsigned int iwq;

			iwq = iwq_find_mapping(pwiv->iwq_domain, p);
			handwe_nested_iwq(iwq);
			handwed = twue;
		}
	}

	wetuwn IWQ_WETVAW(handwed);
}

static void
mt7530_iwq_mask(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_enabwe &= ~BIT(d->hwiwq);
}

static void
mt7530_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_enabwe |= BIT(d->hwiwq);
}

static void
mt7530_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	mt7530_mutex_wock(pwiv);
}

static void
mt7530_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	mt7530_mii_wwite(pwiv, MT7530_SYS_INT_EN, pwiv->iwq_enabwe);
	mt7530_mutex_unwock(pwiv);
}

static stwuct iwq_chip mt7530_iwq_chip = {
	.name = KBUIWD_MODNAME,
	.iwq_mask = mt7530_iwq_mask,
	.iwq_unmask = mt7530_iwq_unmask,
	.iwq_bus_wock = mt7530_iwq_bus_wock,
	.iwq_bus_sync_unwock = mt7530_iwq_bus_sync_unwock,
};

static int
mt7530_iwq_map(stwuct iwq_domain *domain, unsigned int iwq,
	       iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_chip_and_handwew(iwq, &mt7530_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(iwq, twue);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mt7530_iwq_domain_ops = {
	.map = mt7530_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void
mt7988_iwq_mask(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_enabwe &= ~BIT(d->hwiwq);
	mt7530_mii_wwite(pwiv, MT7530_SYS_INT_EN, pwiv->iwq_enabwe);
}

static void
mt7988_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mt7530_pwiv *pwiv = iwq_data_get_iwq_chip_data(d);

	pwiv->iwq_enabwe |= BIT(d->hwiwq);
	mt7530_mii_wwite(pwiv, MT7530_SYS_INT_EN, pwiv->iwq_enabwe);
}

static stwuct iwq_chip mt7988_iwq_chip = {
	.name = KBUIWD_MODNAME,
	.iwq_mask = mt7988_iwq_mask,
	.iwq_unmask = mt7988_iwq_unmask,
};

static int
mt7988_iwq_map(stwuct iwq_domain *domain, unsigned int iwq,
	       iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_chip_and_handwew(iwq, &mt7988_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(iwq, twue);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mt7988_iwq_domain_ops = {
	.map = mt7988_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void
mt7530_setup_mdio_iwq(stwuct mt7530_pwiv *pwiv)
{
	stwuct dsa_switch *ds = pwiv->ds;
	int p;

	fow (p = 0; p < MT7530_NUM_PHYS; p++) {
		if (BIT(p) & ds->phys_mii_mask) {
			unsigned int iwq;

			iwq = iwq_cweate_mapping(pwiv->iwq_domain, p);
			ds->usew_mii_bus->iwq[p] = iwq;
		}
	}
}

static int
mt7530_setup_iwq(stwuct mt7530_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	if (!of_pwopewty_wead_boow(np, "intewwupt-contwowwew")) {
		dev_info(dev, "no intewwupt suppowt\n");
		wetuwn 0;
	}

	pwiv->iwq = of_iwq_get(np, 0);
	if (pwiv->iwq <= 0) {
		dev_eww(dev, "faiwed to get pawent IWQ: %d\n", pwiv->iwq);
		wetuwn pwiv->iwq ? : -EINVAW;
	}

	if (pwiv->id == ID_MT7988)
		pwiv->iwq_domain = iwq_domain_add_wineaw(np, MT7530_NUM_PHYS,
							 &mt7988_iwq_domain_ops,
							 pwiv);
	ewse
		pwiv->iwq_domain = iwq_domain_add_wineaw(np, MT7530_NUM_PHYS,
							 &mt7530_iwq_domain_ops,
							 pwiv);

	if (!pwiv->iwq_domain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	/* This wegistew must be set fow MT7530 to pwopewwy fiwe intewwupts */
	if (pwiv->id != ID_MT7531)
		mt7530_set(pwiv, MT7530_TOP_SIG_CTWW, TOP_SIG_CTWW_NOWMAW);

	wet = wequest_thweaded_iwq(pwiv->iwq, NUWW, mt7530_iwq_thwead_fn,
				   IWQF_ONESHOT, KBUIWD_MODNAME, pwiv);
	if (wet) {
		iwq_domain_wemove(pwiv->iwq_domain);
		dev_eww(dev, "faiwed to wequest IWQ: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void
mt7530_fwee_mdio_iwq(stwuct mt7530_pwiv *pwiv)
{
	int p;

	fow (p = 0; p < MT7530_NUM_PHYS; p++) {
		if (BIT(p) & pwiv->ds->phys_mii_mask) {
			unsigned int iwq;

			iwq = iwq_find_mapping(pwiv->iwq_domain, p);
			iwq_dispose_mapping(iwq);
		}
	}
}

static void
mt7530_fwee_iwq_common(stwuct mt7530_pwiv *pwiv)
{
	fwee_iwq(pwiv->iwq, pwiv);
	iwq_domain_wemove(pwiv->iwq_domain);
}

static void
mt7530_fwee_iwq(stwuct mt7530_pwiv *pwiv)
{
	mt7530_fwee_mdio_iwq(pwiv);
	mt7530_fwee_iwq_common(pwiv);
}

static int
mt7530_setup_mdio(stwuct mt7530_pwiv *pwiv)
{
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct device *dev = pwiv->dev;
	stwuct mii_bus *bus;
	static int idx;
	int wet;

	bus = devm_mdiobus_awwoc(dev);
	if (!bus)
		wetuwn -ENOMEM;

	ds->usew_mii_bus = bus;
	bus->pwiv = pwiv;
	bus->name = KBUIWD_MODNAME "-mii";
	snpwintf(bus->id, MII_BUS_ID_SIZE, KBUIWD_MODNAME "-%d", idx++);
	bus->wead = mt753x_phy_wead_c22;
	bus->wwite = mt753x_phy_wwite_c22;
	bus->wead_c45 = mt753x_phy_wead_c45;
	bus->wwite_c45 = mt753x_phy_wwite_c45;
	bus->pawent = dev;
	bus->phy_mask = ~ds->phys_mii_mask;

	if (pwiv->iwq)
		mt7530_setup_mdio_iwq(pwiv);

	wet = devm_mdiobus_wegistew(dev, bus);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew MDIO bus: %d\n", wet);
		if (pwiv->iwq)
			mt7530_fwee_mdio_iwq(pwiv);
	}

	wetuwn wet;
}

static int
mt7530_setup(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	stwuct device_node *dn = NUWW;
	stwuct device_node *phy_node;
	stwuct device_node *mac_np;
	stwuct mt7530_dummy_poww p;
	phy_intewface_t intewface;
	stwuct dsa_powt *cpu_dp;
	u32 id, vaw;
	int wet, i;

	/* The pawent node of conduit netdev which howds the common system
	 * contwowwew awso is the containew fow two GMACs nodes wepwesenting
	 * as two netdev instances.
	 */
	dsa_switch_fow_each_cpu_powt(cpu_dp, ds) {
		dn = cpu_dp->conduit->dev.of_node->pawent;
		/* It doesn't mattew which CPU powt is found fiwst,
		 * theiw conduits shouwd shawe the same pawent OF node
		 */
		bweak;
	}

	if (!dn) {
		dev_eww(ds->dev, "pawent OF node of DSA conduit not found");
		wetuwn -EINVAW;
	}

	ds->assisted_weawning_on_cpu_powt = twue;
	ds->mtu_enfowcement_ingwess = twue;

	if (pwiv->id == ID_MT7530) {
		weguwatow_set_vowtage(pwiv->cowe_pww, 1000000, 1000000);
		wet = weguwatow_enabwe(pwiv->cowe_pww);
		if (wet < 0) {
			dev_eww(pwiv->dev,
				"Faiwed to enabwe cowe powew: %d\n", wet);
			wetuwn wet;
		}

		weguwatow_set_vowtage(pwiv->io_pww, 3300000, 3300000);
		wet = weguwatow_enabwe(pwiv->io_pww);
		if (wet < 0) {
			dev_eww(pwiv->dev, "Faiwed to enabwe io pww: %d\n",
				wet);
			wetuwn wet;
		}
	}

	/* Weset whowe chip thwough gpio pin ow memowy-mapped wegistews fow
	 * diffewent type of hawdwawe
	 */
	if (pwiv->mcm) {
		weset_contwow_assewt(pwiv->wstc);
		usweep_wange(1000, 1100);
		weset_contwow_deassewt(pwiv->wstc);
	} ewse {
		gpiod_set_vawue_cansweep(pwiv->weset, 0);
		usweep_wange(1000, 1100);
		gpiod_set_vawue_cansweep(pwiv->weset, 1);
	}

	/* Waiting fow MT7530 got to stabwe */
	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7530_HWTWAP);
	wet = weadx_poww_timeout(_mt7530_wead, &p, vaw, vaw != 0,
				 20, 1000000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "weset timeout\n");
		wetuwn wet;
	}

	id = mt7530_wead(pwiv, MT7530_CWEV);
	id >>= CHIP_NAME_SHIFT;
	if (id != MT7530_ID) {
		dev_eww(pwiv->dev, "chip %x can't be suppowted\n", id);
		wetuwn -ENODEV;
	}

	/* Weset the switch thwough intewnaw weset */
	mt7530_wwite(pwiv, MT7530_SYS_CTWW,
		     SYS_CTWW_PHY_WST | SYS_CTWW_SW_WST |
		     SYS_CTWW_WEG_WST);

	mt7530_pww_setup(pwiv);

	/* Wowew Tx dwiving fow TWGMII path */
	fow (i = 0; i < NUM_TWGMII_CTWW; i++)
		mt7530_wwite(pwiv, MT7530_TWGMII_TD_ODT(i),
			     TD_DM_DWVP(8) | TD_DM_DWVN(8));

	fow (i = 0; i < NUM_TWGMII_CTWW; i++)
		mt7530_wmw(pwiv, MT7530_TWGMII_WD(i),
			   WD_TAP_MASK, WD_TAP(16));

	/* Enabwe powt 6 */
	vaw = mt7530_wead(pwiv, MT7530_MHWTWAP);
	vaw &= ~MHWTWAP_P6_DIS & ~MHWTWAP_PHY_ACCESS;
	vaw |= MHWTWAP_MANUAW;
	mt7530_wwite(pwiv, MT7530_MHWTWAP, vaw);

	pwiv->p6_intewface = PHY_INTEWFACE_MODE_NA;

	mt753x_twap_fwames(pwiv);

	/* Enabwe and weset MIB countews */
	mt7530_mib_weset(ds);

	fow (i = 0; i < MT7530_NUM_POWTS; i++) {
		/* Disabwe fowwawding by defauwt on aww powts */
		mt7530_wmw(pwiv, MT7530_PCW_P(i), PCW_MATWIX_MASK,
			   PCW_MATWIX_CWW);

		/* Disabwe weawning by defauwt on aww powts */
		mt7530_set(pwiv, MT7530_PSC_P(i), SA_DIS);

		if (dsa_is_cpu_powt(ds, i)) {
			wet = mt753x_cpu_powt_enabwe(ds, i);
			if (wet)
				wetuwn wet;
		} ewse {
			mt7530_powt_disabwe(ds, i);

			/* Set defauwt PVID to 0 on aww usew powts */
			mt7530_wmw(pwiv, MT7530_PPBV1_P(i), G0_POWT_VID_MASK,
				   G0_POWT_VID_DEF);
		}
		/* Enabwe consistent egwess tag */
		mt7530_wmw(pwiv, MT7530_PVC_P(i), PVC_EG_TAG_MASK,
			   PVC_EG_TAG(MT7530_VWAN_EG_CONSISTENT));
	}

	/* Setup VWAN ID 0 fow VWAN-unawawe bwidges */
	wet = mt7530_setup_vwan0(pwiv);
	if (wet)
		wetuwn wet;

	/* Setup powt 5 */
	pwiv->p5_intf_sew = P5_DISABWED;
	intewface = PHY_INTEWFACE_MODE_NA;

	if (!dsa_is_unused_powt(ds, 5)) {
		pwiv->p5_intf_sew = P5_INTF_SEW_GMAC5;
		wet = of_get_phy_mode(dsa_to_powt(ds, 5)->dn, &intewface);
		if (wet && wet != -ENODEV)
			wetuwn wet;
	} ewse {
		/* Scan the ethewnet nodes. wook fow GMAC1, wookup used phy */
		fow_each_chiwd_of_node(dn, mac_np) {
			if (!of_device_is_compatibwe(mac_np,
						     "mediatek,eth-mac"))
				continue;

			wet = of_pwopewty_wead_u32(mac_np, "weg", &id);
			if (wet < 0 || id != 1)
				continue;

			phy_node = of_pawse_phandwe(mac_np, "phy-handwe", 0);
			if (!phy_node)
				continue;

			if (phy_node->pawent == pwiv->dev->of_node->pawent) {
				wet = of_get_phy_mode(mac_np, &intewface);
				if (wet && wet != -ENODEV) {
					of_node_put(mac_np);
					of_node_put(phy_node);
					wetuwn wet;
				}
				id = of_mdio_pawse_addw(ds->dev, phy_node);
				if (id == 0)
					pwiv->p5_intf_sew = P5_INTF_SEW_PHY_P0;
				if (id == 4)
					pwiv->p5_intf_sew = P5_INTF_SEW_PHY_P4;
			}
			of_node_put(mac_np);
			of_node_put(phy_node);
			bweak;
		}
	}

#ifdef CONFIG_GPIOWIB
	if (of_pwopewty_wead_boow(pwiv->dev->of_node, "gpio-contwowwew")) {
		wet = mt7530_setup_gpio(pwiv);
		if (wet)
			wetuwn wet;
	}
#endif /* CONFIG_GPIOWIB */

	mt7530_setup_powt5(ds, intewface);

	/* Fwush the FDB tabwe */
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_FWUSH, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int
mt7531_setup_common(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int wet, i;

	mt753x_twap_fwames(pwiv);

	/* Enabwe and weset MIB countews */
	mt7530_mib_weset(ds);

	/* Disabwe fwooding on aww powts */
	mt7530_cweaw(pwiv, MT7530_MFC, BC_FFP_MASK | UNM_FFP_MASK |
		     UNU_FFP_MASK);

	fow (i = 0; i < MT7530_NUM_POWTS; i++) {
		/* Disabwe fowwawding by defauwt on aww powts */
		mt7530_wmw(pwiv, MT7530_PCW_P(i), PCW_MATWIX_MASK,
			   PCW_MATWIX_CWW);

		/* Disabwe weawning by defauwt on aww powts */
		mt7530_set(pwiv, MT7530_PSC_P(i), SA_DIS);

		mt7530_set(pwiv, MT7531_DBG_CNT(i), MT7531_DIS_CWW);

		if (dsa_is_cpu_powt(ds, i)) {
			wet = mt753x_cpu_powt_enabwe(ds, i);
			if (wet)
				wetuwn wet;
		} ewse {
			mt7530_powt_disabwe(ds, i);

			/* Set defauwt PVID to 0 on aww usew powts */
			mt7530_wmw(pwiv, MT7530_PPBV1_P(i), G0_POWT_VID_MASK,
				   G0_POWT_VID_DEF);
		}

		/* Enabwe consistent egwess tag */
		mt7530_wmw(pwiv, MT7530_PVC_P(i), PVC_EG_TAG_MASK,
			   PVC_EG_TAG(MT7530_VWAN_EG_CONSISTENT));
	}

	/* Fwush the FDB tabwe */
	wet = mt7530_fdb_cmd(pwiv, MT7530_FDB_FWUSH, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int
mt7531_setup(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	stwuct mt7530_dummy_poww p;
	u32 vaw, id;
	int wet, i;

	/* Weset whowe chip thwough gpio pin ow memowy-mapped wegistews fow
	 * diffewent type of hawdwawe
	 */
	if (pwiv->mcm) {
		weset_contwow_assewt(pwiv->wstc);
		usweep_wange(1000, 1100);
		weset_contwow_deassewt(pwiv->wstc);
	} ewse {
		gpiod_set_vawue_cansweep(pwiv->weset, 0);
		usweep_wange(1000, 1100);
		gpiod_set_vawue_cansweep(pwiv->weset, 1);
	}

	/* Waiting fow MT7530 got to stabwe */
	INIT_MT7530_DUMMY_POWW(&p, pwiv, MT7530_HWTWAP);
	wet = weadx_poww_timeout(_mt7530_wead, &p, vaw, vaw != 0,
				 20, 1000000);
	if (wet < 0) {
		dev_eww(pwiv->dev, "weset timeout\n");
		wetuwn wet;
	}

	id = mt7530_wead(pwiv, MT7531_CWEV);
	id >>= CHIP_NAME_SHIFT;

	if (id != MT7531_ID) {
		dev_eww(pwiv->dev, "chip %x can't be suppowted\n", id);
		wetuwn -ENODEV;
	}

	/* aww MACs must be fowced wink-down befowe sw weset */
	fow (i = 0; i < MT7530_NUM_POWTS; i++)
		mt7530_wwite(pwiv, MT7530_PMCW_P(i), MT7531_FOWCE_WNK);

	/* Weset the switch thwough intewnaw weset */
	mt7530_wwite(pwiv, MT7530_SYS_CTWW,
		     SYS_CTWW_PHY_WST | SYS_CTWW_SW_WST |
		     SYS_CTWW_WEG_WST);

	mt7531_pww_setup(pwiv);

	if (mt7531_duaw_sgmii_suppowted(pwiv)) {
		pwiv->p5_intf_sew = P5_INTF_SEW_GMAC5_SGMII;

		/* Wet ds->usew_mii_bus be abwe to access extewnaw phy. */
		mt7530_wmw(pwiv, MT7531_GPIO_MODE1, MT7531_GPIO11_WG_WXD2_MASK,
			   MT7531_EXT_P_MDC_11);
		mt7530_wmw(pwiv, MT7531_GPIO_MODE1, MT7531_GPIO12_WG_WXD3_MASK,
			   MT7531_EXT_P_MDIO_12);
	} ewse {
		pwiv->p5_intf_sew = P5_INTF_SEW_GMAC5;
	}
	dev_dbg(ds->dev, "P5 suppowt %s intewface\n",
		p5_intf_modes(pwiv->p5_intf_sew));

	mt7530_wmw(pwiv, MT7531_GPIO_MODE0, MT7531_GPIO0_MASK,
		   MT7531_GPIO0_INTEWWUPT);

	/* Wet phywink decide the intewface watew. */
	pwiv->p5_intewface = PHY_INTEWFACE_MODE_NA;
	pwiv->p6_intewface = PHY_INTEWFACE_MODE_NA;

	/* Enabwe PHY cowe PWW, since phy_device has not yet been cweated
	 * pwovided fow phy_[wead,wwite]_mmd_indiwect is cawwed, we pwovide
	 * ouw own mt7531_ind_mmd_phy_[wead,wwite] to compwete this
	 * function.
	 */
	vaw = mt7531_ind_c45_phy_wead(pwiv, MT753X_CTWW_PHY_ADDW,
				      MDIO_MMD_VEND2, COWE_PWW_GWOUP4);
	vaw |= MT7531_PHY_PWW_BYPASS_MODE;
	vaw &= ~MT7531_PHY_PWW_OFF;
	mt7531_ind_c45_phy_wwite(pwiv, MT753X_CTWW_PHY_ADDW, MDIO_MMD_VEND2,
				 COWE_PWW_GWOUP4, vaw);

	mt7531_setup_common(ds);

	/* Setup VWAN ID 0 fow VWAN-unawawe bwidges */
	wet = mt7530_setup_vwan0(pwiv);
	if (wet)
		wetuwn wet;

	ds->assisted_weawning_on_cpu_powt = twue;
	ds->mtu_enfowcement_ingwess = twue;

	wetuwn 0;
}

static void mt7530_mac_powt_get_caps(stwuct dsa_switch *ds, int powt,
				     stwuct phywink_config *config)
{
	switch (powt) {
	case 0 ... 4: /* Intewnaw phy */
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		bweak;

	case 5: /* 2nd cpu powt with phy of powt 0 ow 4 / extewnaw phy */
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_MII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		bweak;

	case 6: /* 1st cpu powt */
		__set_bit(PHY_INTEWFACE_MODE_WGMII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_TWGMII,
			  config->suppowted_intewfaces);
		bweak;
	}
}

static boow mt7531_is_wgmii_powt(stwuct mt7530_pwiv *pwiv, u32 powt)
{
	wetuwn (powt == 5) && (pwiv->p5_intf_sew != P5_INTF_SEW_GMAC5_SGMII);
}

static void mt7531_mac_powt_get_caps(stwuct dsa_switch *ds, int powt,
				     stwuct phywink_config *config)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	switch (powt) {
	case 0 ... 4: /* Intewnaw phy */
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		bweak;

	case 5: /* 2nd cpu powt suppowts eithew wgmii ow sgmii/8023z */
		if (mt7531_is_wgmii_powt(pwiv, powt)) {
			phy_intewface_set_wgmii(config->suppowted_intewfaces);
			bweak;
		}
		fawwthwough;

	case 6: /* 1st cpu powt suppowts sgmii/8023z onwy */
		__set_bit(PHY_INTEWFACE_MODE_SGMII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX,
			  config->suppowted_intewfaces);

		config->mac_capabiwities |= MAC_2500FD;
		bweak;
	}
}

static void mt7988_mac_powt_get_caps(stwuct dsa_switch *ds, int powt,
				     stwuct phywink_config *config)
{
	phy_intewface_zewo(config->suppowted_intewfaces);

	switch (powt) {
	case 0 ... 4: /* Intewnaw phy */
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		bweak;

	case 6:
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
					   MAC_10000FD;
	}
}

static int
mt753x_pad_setup(stwuct dsa_switch *ds, const stwuct phywink_wink_state *state)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	wetuwn pwiv->info->pad_setup(ds, state->intewface);
}

static int
mt7530_mac_config(stwuct dsa_switch *ds, int powt, unsigned int mode,
		  phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	/* Onwy need to setup powt5. */
	if (powt != 5)
		wetuwn 0;

	mt7530_setup_powt5(pwiv->ds, intewface);

	wetuwn 0;
}

static int mt7531_wgmii_setup(stwuct mt7530_pwiv *pwiv, u32 powt,
			      phy_intewface_t intewface,
			      stwuct phy_device *phydev)
{
	u32 vaw;

	if (!mt7531_is_wgmii_powt(pwiv, powt)) {
		dev_eww(pwiv->dev, "WGMII mode is not avaiwabwe fow powt %d\n",
			powt);
		wetuwn -EINVAW;
	}

	vaw = mt7530_wead(pwiv, MT7531_CWKGEN_CTWW);
	vaw |= GP_CWK_EN;
	vaw &= ~GP_MODE_MASK;
	vaw |= GP_MODE(MT7531_GP_MODE_WGMII);
	vaw &= ~CWK_SKEW_IN_MASK;
	vaw |= CWK_SKEW_IN(MT7531_CWK_SKEW_NO_CHG);
	vaw &= ~CWK_SKEW_OUT_MASK;
	vaw |= CWK_SKEW_OUT(MT7531_CWK_SKEW_NO_CHG);
	vaw |= TXCWK_NO_WEVEWSE | WXCWK_NO_DEWAY;

	/* Do not adjust wgmii deway when vendow phy dwivew pwesents. */
	if (!phydev || phy_dwivew_is_genphy(phydev)) {
		vaw &= ~(TXCWK_NO_WEVEWSE | WXCWK_NO_DEWAY);
		switch (intewface) {
		case PHY_INTEWFACE_MODE_WGMII:
			vaw |= TXCWK_NO_WEVEWSE;
			vaw |= WXCWK_NO_DEWAY;
			bweak;
		case PHY_INTEWFACE_MODE_WGMII_WXID:
			vaw |= TXCWK_NO_WEVEWSE;
			bweak;
		case PHY_INTEWFACE_MODE_WGMII_TXID:
			vaw |= WXCWK_NO_DEWAY;
			bweak;
		case PHY_INTEWFACE_MODE_WGMII_ID:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	mt7530_wwite(pwiv, MT7531_CWKGEN_CTWW, vaw);

	wetuwn 0;
}

static boow mt753x_is_mac_powt(u32 powt)
{
	wetuwn (powt == 5 || powt == 6);
}

static int
mt7988_mac_config(stwuct dsa_switch *ds, int powt, unsigned int mode,
		  phy_intewface_t intewface)
{
	if (dsa_is_cpu_powt(ds, powt) &&
	    intewface == PHY_INTEWFACE_MODE_INTEWNAW)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int
mt7531_mac_config(stwuct dsa_switch *ds, int powt, unsigned int mode,
		  phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	stwuct phy_device *phydev;
	stwuct dsa_powt *dp;

	if (!mt753x_is_mac_powt(powt)) {
		dev_eww(pwiv->dev, "powt %d is not a MAC powt\n", powt);
		wetuwn -EINVAW;
	}

	switch (intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		dp = dsa_to_powt(ds, powt);
		phydev = dp->usew->phydev;
		wetuwn mt7531_wgmii_setup(pwiv, powt, intewface, phydev);
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_NA:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
		/* handwed in SGMII PCS dwivew */
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static int
mt753x_mac_config(stwuct dsa_switch *ds, int powt, unsigned int mode,
		  const stwuct phywink_wink_state *state)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	wetuwn pwiv->info->mac_powt_config(ds, powt, mode, state->intewface);
}

static stwuct phywink_pcs *
mt753x_phywink_mac_sewect_pcs(stwuct dsa_switch *ds, int powt,
			      phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	switch (intewface) {
	case PHY_INTEWFACE_MODE_TWGMII:
		wetuwn &pwiv->pcs[powt].pcs;
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
		wetuwn pwiv->powts[powt].sgmii_pcs;
	defauwt:
		wetuwn NUWW;
	}
}

static void
mt753x_phywink_mac_config(stwuct dsa_switch *ds, int powt, unsigned int mode,
			  const stwuct phywink_wink_state *state)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 mcw_cuw, mcw_new;

	switch (powt) {
	case 0 ... 4: /* Intewnaw phy */
		if (state->intewface != PHY_INTEWFACE_MODE_GMII &&
		    state->intewface != PHY_INTEWFACE_MODE_INTEWNAW)
			goto unsuppowted;
		bweak;
	case 5: /* 2nd cpu powt with phy of powt 0 ow 4 / extewnaw phy */
		if (pwiv->p5_intewface == state->intewface)
			bweak;

		if (mt753x_mac_config(ds, powt, mode, state) < 0)
			goto unsuppowted;

		if (pwiv->p5_intf_sew != P5_DISABWED)
			pwiv->p5_intewface = state->intewface;
		bweak;
	case 6: /* 1st cpu powt */
		if (pwiv->p6_intewface == state->intewface)
			bweak;

		mt753x_pad_setup(ds, state);

		if (mt753x_mac_config(ds, powt, mode, state) < 0)
			goto unsuppowted;

		pwiv->p6_intewface = state->intewface;
		bweak;
	defauwt:
unsuppowted:
		dev_eww(ds->dev, "%s: unsuppowted %s powt: %i\n",
			__func__, phy_modes(state->intewface), powt);
		wetuwn;
	}

	mcw_cuw = mt7530_wead(pwiv, MT7530_PMCW_P(powt));
	mcw_new = mcw_cuw;
	mcw_new &= ~PMCW_WINK_SETTINGS_MASK;
	mcw_new |= PMCW_IFG_XMIT(1) | PMCW_MAC_MODE | PMCW_BACKOFF_EN |
		   PMCW_BACKPW_EN | PMCW_FOWCE_MODE_ID(pwiv->id);

	/* Awe we connected to extewnaw phy */
	if (powt == 5 && dsa_is_usew_powt(ds, 5))
		mcw_new |= PMCW_EXT_PHY;

	if (mcw_new != mcw_cuw)
		mt7530_wwite(pwiv, MT7530_PMCW_P(powt), mcw_new);
}

static void mt753x_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					 unsigned int mode,
					 phy_intewface_t intewface)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mt7530_cweaw(pwiv, MT7530_PMCW_P(powt), PMCW_WINK_SETTINGS_MASK);
}

static void mt753x_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
				       unsigned int mode,
				       phy_intewface_t intewface,
				       stwuct phy_device *phydev,
				       int speed, int dupwex,
				       boow tx_pause, boow wx_pause)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 mcw;

	mcw = PMCW_WX_EN | PMCW_TX_EN | PMCW_FOWCE_WNK;

	/* MT753x MAC wowks in 1G fuww dupwex mode fow aww up-cwocked
	 * vawiants.
	 */
	if (intewface == PHY_INTEWFACE_MODE_TWGMII ||
	    (phy_intewface_mode_is_8023z(intewface))) {
		speed = SPEED_1000;
		dupwex = DUPWEX_FUWW;
	}

	switch (speed) {
	case SPEED_1000:
		mcw |= PMCW_FOWCE_SPEED_1000;
		bweak;
	case SPEED_100:
		mcw |= PMCW_FOWCE_SPEED_100;
		bweak;
	}
	if (dupwex == DUPWEX_FUWW) {
		mcw |= PMCW_FOWCE_FDX;
		if (tx_pause)
			mcw |= PMCW_TX_FC_EN;
		if (wx_pause)
			mcw |= PMCW_WX_FC_EN;
	}

	if (mode == MWO_AN_PHY && phydev && phy_init_eee(phydev, fawse) >= 0) {
		switch (speed) {
		case SPEED_1000:
			mcw |= PMCW_FOWCE_EEE1G;
			bweak;
		case SPEED_100:
			mcw |= PMCW_FOWCE_EEE100;
			bweak;
		}
	}

	mt7530_set(pwiv, MT7530_PMCW_P(powt), mcw);
}

static int
mt7531_cpu_powt_config(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	phy_intewface_t intewface;
	int speed;
	int wet;

	switch (powt) {
	case 5:
		if (mt7531_is_wgmii_powt(pwiv, powt))
			intewface = PHY_INTEWFACE_MODE_WGMII;
		ewse
			intewface = PHY_INTEWFACE_MODE_2500BASEX;

		pwiv->p5_intewface = intewface;
		bweak;
	case 6:
		intewface = PHY_INTEWFACE_MODE_2500BASEX;

		pwiv->p6_intewface = intewface;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (intewface == PHY_INTEWFACE_MODE_2500BASEX)
		speed = SPEED_2500;
	ewse
		speed = SPEED_1000;

	wet = mt7531_mac_config(ds, powt, MWO_AN_FIXED, intewface);
	if (wet)
		wetuwn wet;
	mt7530_wwite(pwiv, MT7530_PMCW_P(powt),
		     PMCW_CPU_POWT_SETTING(pwiv->id));
	mt753x_phywink_mac_wink_up(ds, powt, MWO_AN_FIXED, intewface, NUWW,
				   speed, DUPWEX_FUWW, twue, twue);

	wetuwn 0;
}

static int
mt7988_cpu_powt_config(stwuct dsa_switch *ds, int powt)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	mt7530_wwite(pwiv, MT7530_PMCW_P(powt),
		     PMCW_CPU_POWT_SETTING(pwiv->id));

	mt753x_phywink_mac_wink_up(ds, powt, MWO_AN_FIXED,
				   PHY_INTEWFACE_MODE_INTEWNAW, NUWW,
				   SPEED_10000, DUPWEX_FUWW, twue, twue);

	wetuwn 0;
}

static void mt753x_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				    stwuct phywink_config *config)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	/* This switch onwy suppowts fuww-dupwex at 1Gbps */
	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
				   MAC_10 | MAC_100 | MAC_1000FD;

	pwiv->info->mac_powt_get_caps(ds, powt, config);
}

static int mt753x_pcs_vawidate(stwuct phywink_pcs *pcs,
			       unsigned wong *suppowted,
			       const stwuct phywink_wink_state *state)
{
	/* Autonegotiation is not suppowted in TWGMII now 802.3z modes */
	if (state->intewface == PHY_INTEWFACE_MODE_TWGMII ||
	    phy_intewface_mode_is_8023z(state->intewface))
		phywink_cweaw(suppowted, Autoneg);

	wetuwn 0;
}

static void mt7530_pcs_get_state(stwuct phywink_pcs *pcs,
				 stwuct phywink_wink_state *state)
{
	stwuct mt7530_pwiv *pwiv = pcs_to_mt753x_pcs(pcs)->pwiv;
	int powt = pcs_to_mt753x_pcs(pcs)->powt;
	u32 pmsw;

	pmsw = mt7530_wead(pwiv, MT7530_PMSW_P(powt));

	state->wink = (pmsw & PMSW_WINK);
	state->an_compwete = state->wink;
	state->dupwex = !!(pmsw & PMSW_DPX);

	switch (pmsw & PMSW_SPEED_MASK) {
	case PMSW_SPEED_10:
		state->speed = SPEED_10;
		bweak;
	case PMSW_SPEED_100:
		state->speed = SPEED_100;
		bweak;
	case PMSW_SPEED_1000:
		state->speed = SPEED_1000;
		bweak;
	defauwt:
		state->speed = SPEED_UNKNOWN;
		bweak;
	}

	state->pause &= ~(MWO_PAUSE_WX | MWO_PAUSE_TX);
	if (pmsw & PMSW_WX_FC)
		state->pause |= MWO_PAUSE_WX;
	if (pmsw & PMSW_TX_FC)
		state->pause |= MWO_PAUSE_TX;
}

static int mt753x_pcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			     phy_intewface_t intewface,
			     const unsigned wong *advewtising,
			     boow pewmit_pause_to_mac)
{
	wetuwn 0;
}

static void mt7530_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
}

static const stwuct phywink_pcs_ops mt7530_pcs_ops = {
	.pcs_vawidate = mt753x_pcs_vawidate,
	.pcs_get_state = mt7530_pcs_get_state,
	.pcs_config = mt753x_pcs_config,
	.pcs_an_westawt = mt7530_pcs_an_westawt,
};

static int
mt753x_setup(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	int i, wet;

	/* Initiawise the PCS devices */
	fow (i = 0; i < pwiv->ds->num_powts; i++) {
		pwiv->pcs[i].pcs.ops = pwiv->info->pcs_ops;
		pwiv->pcs[i].pcs.neg_mode = twue;
		pwiv->pcs[i].pwiv = pwiv;
		pwiv->pcs[i].powt = i;
	}

	wet = pwiv->info->sw_setup(ds);
	if (wet)
		wetuwn wet;

	wet = mt7530_setup_iwq(pwiv);
	if (wet)
		wetuwn wet;

	wet = mt7530_setup_mdio(pwiv);
	if (wet && pwiv->iwq)
		mt7530_fwee_iwq_common(pwiv);

	if (pwiv->cweate_sgmii) {
		wet = pwiv->cweate_sgmii(pwiv, mt7531_duaw_sgmii_suppowted(pwiv));
		if (wet && pwiv->iwq)
			mt7530_fwee_iwq(pwiv);
	}

	wetuwn wet;
}

static int mt753x_get_mac_eee(stwuct dsa_switch *ds, int powt,
			      stwuct ethtoow_eee *e)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 eeecw = mt7530_wead(pwiv, MT7530_PMEEECW_P(powt));

	e->tx_wpi_enabwed = !(eeecw & WPI_MODE_EN);
	e->tx_wpi_timew = GET_WPI_THWESH(eeecw);

	wetuwn 0;
}

static int mt753x_set_mac_eee(stwuct dsa_switch *ds, int powt,
			      stwuct ethtoow_eee *e)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;
	u32 set, mask = WPI_THWESH_MASK | WPI_MODE_EN;

	if (e->tx_wpi_timew > 0xFFF)
		wetuwn -EINVAW;

	set = SET_WPI_THWESH(e->tx_wpi_timew);
	if (!e->tx_wpi_enabwed)
		/* Fowce WPI Mode without a deway */
		set |= WPI_MODE_EN;
	mt7530_wmw(pwiv, MT7530_PMEEECW_P(powt), mask, set);

	wetuwn 0;
}

static int mt7988_pad_setup(stwuct dsa_switch *ds, phy_intewface_t intewface)
{
	wetuwn 0;
}

static int mt7988_setup(stwuct dsa_switch *ds)
{
	stwuct mt7530_pwiv *pwiv = ds->pwiv;

	/* Weset the switch */
	weset_contwow_assewt(pwiv->wstc);
	usweep_wange(20, 50);
	weset_contwow_deassewt(pwiv->wstc);
	usweep_wange(20, 50);

	/* Weset the switch PHYs */
	mt7530_wwite(pwiv, MT7530_SYS_CTWW, SYS_CTWW_PHY_WST);

	wetuwn mt7531_setup_common(ds);
}

const stwuct dsa_switch_ops mt7530_switch_ops = {
	.get_tag_pwotocow	= mtk_get_tag_pwotocow,
	.setup			= mt753x_setup,
	.pwefewwed_defauwt_wocaw_cpu_powt = mt753x_pwefewwed_defauwt_wocaw_cpu_powt,
	.get_stwings		= mt7530_get_stwings,
	.get_ethtoow_stats	= mt7530_get_ethtoow_stats,
	.get_sset_count		= mt7530_get_sset_count,
	.set_ageing_time	= mt7530_set_ageing_time,
	.powt_enabwe		= mt7530_powt_enabwe,
	.powt_disabwe		= mt7530_powt_disabwe,
	.powt_change_mtu	= mt7530_powt_change_mtu,
	.powt_max_mtu		= mt7530_powt_max_mtu,
	.powt_stp_state_set	= mt7530_stp_state_set,
	.powt_pwe_bwidge_fwags	= mt7530_powt_pwe_bwidge_fwags,
	.powt_bwidge_fwags	= mt7530_powt_bwidge_fwags,
	.powt_bwidge_join	= mt7530_powt_bwidge_join,
	.powt_bwidge_weave	= mt7530_powt_bwidge_weave,
	.powt_fdb_add		= mt7530_powt_fdb_add,
	.powt_fdb_dew		= mt7530_powt_fdb_dew,
	.powt_fdb_dump		= mt7530_powt_fdb_dump,
	.powt_mdb_add		= mt7530_powt_mdb_add,
	.powt_mdb_dew		= mt7530_powt_mdb_dew,
	.powt_vwan_fiwtewing	= mt7530_powt_vwan_fiwtewing,
	.powt_vwan_add		= mt7530_powt_vwan_add,
	.powt_vwan_dew		= mt7530_powt_vwan_dew,
	.powt_miwwow_add	= mt753x_powt_miwwow_add,
	.powt_miwwow_dew	= mt753x_powt_miwwow_dew,
	.phywink_get_caps	= mt753x_phywink_get_caps,
	.phywink_mac_sewect_pcs	= mt753x_phywink_mac_sewect_pcs,
	.phywink_mac_config	= mt753x_phywink_mac_config,
	.phywink_mac_wink_down	= mt753x_phywink_mac_wink_down,
	.phywink_mac_wink_up	= mt753x_phywink_mac_wink_up,
	.get_mac_eee		= mt753x_get_mac_eee,
	.set_mac_eee		= mt753x_set_mac_eee,
};
EXPOWT_SYMBOW_GPW(mt7530_switch_ops);

const stwuct mt753x_info mt753x_tabwe[] = {
	[ID_MT7621] = {
		.id = ID_MT7621,
		.pcs_ops = &mt7530_pcs_ops,
		.sw_setup = mt7530_setup,
		.phy_wead_c22 = mt7530_phy_wead_c22,
		.phy_wwite_c22 = mt7530_phy_wwite_c22,
		.phy_wead_c45 = mt7530_phy_wead_c45,
		.phy_wwite_c45 = mt7530_phy_wwite_c45,
		.pad_setup = mt7530_pad_cwk_setup,
		.mac_powt_get_caps = mt7530_mac_powt_get_caps,
		.mac_powt_config = mt7530_mac_config,
	},
	[ID_MT7530] = {
		.id = ID_MT7530,
		.pcs_ops = &mt7530_pcs_ops,
		.sw_setup = mt7530_setup,
		.phy_wead_c22 = mt7530_phy_wead_c22,
		.phy_wwite_c22 = mt7530_phy_wwite_c22,
		.phy_wead_c45 = mt7530_phy_wead_c45,
		.phy_wwite_c45 = mt7530_phy_wwite_c45,
		.pad_setup = mt7530_pad_cwk_setup,
		.mac_powt_get_caps = mt7530_mac_powt_get_caps,
		.mac_powt_config = mt7530_mac_config,
	},
	[ID_MT7531] = {
		.id = ID_MT7531,
		.pcs_ops = &mt7530_pcs_ops,
		.sw_setup = mt7531_setup,
		.phy_wead_c22 = mt7531_ind_c22_phy_wead,
		.phy_wwite_c22 = mt7531_ind_c22_phy_wwite,
		.phy_wead_c45 = mt7531_ind_c45_phy_wead,
		.phy_wwite_c45 = mt7531_ind_c45_phy_wwite,
		.pad_setup = mt7531_pad_setup,
		.cpu_powt_config = mt7531_cpu_powt_config,
		.mac_powt_get_caps = mt7531_mac_powt_get_caps,
		.mac_powt_config = mt7531_mac_config,
	},
	[ID_MT7988] = {
		.id = ID_MT7988,
		.pcs_ops = &mt7530_pcs_ops,
		.sw_setup = mt7988_setup,
		.phy_wead_c22 = mt7531_ind_c22_phy_wead,
		.phy_wwite_c22 = mt7531_ind_c22_phy_wwite,
		.phy_wead_c45 = mt7531_ind_c45_phy_wead,
		.phy_wwite_c45 = mt7531_ind_c45_phy_wwite,
		.pad_setup = mt7988_pad_setup,
		.cpu_powt_config = mt7988_cpu_powt_config,
		.mac_powt_get_caps = mt7988_mac_powt_get_caps,
		.mac_powt_config = mt7988_mac_config,
	},
};
EXPOWT_SYMBOW_GPW(mt753x_tabwe);

int
mt7530_pwobe_common(stwuct mt7530_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev;

	pwiv->ds = devm_kzawwoc(dev, sizeof(*pwiv->ds), GFP_KEWNEW);
	if (!pwiv->ds)
		wetuwn -ENOMEM;

	pwiv->ds->dev = dev;
	pwiv->ds->num_powts = MT7530_NUM_POWTS;

	/* Get the hawdwawe identifiew fwom the devicetwee node.
	 * We wiww need it fow some of the cwock and weguwatow setup.
	 */
	pwiv->info = of_device_get_match_data(dev);
	if (!pwiv->info)
		wetuwn -EINVAW;

	/* Sanity check if these wequiwed device opewations awe fiwwed
	 * pwopewwy.
	 */
	if (!pwiv->info->sw_setup || !pwiv->info->pad_setup ||
	    !pwiv->info->phy_wead_c22 || !pwiv->info->phy_wwite_c22 ||
	    !pwiv->info->mac_powt_get_caps ||
	    !pwiv->info->mac_powt_config)
		wetuwn -EINVAW;

	pwiv->id = pwiv->info->id;
	pwiv->dev = dev;
	pwiv->ds->pwiv = pwiv;
	pwiv->ds->ops = &mt7530_switch_ops;
	mutex_init(&pwiv->weg_mutex);
	dev_set_dwvdata(dev, pwiv);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7530_pwobe_common);

void
mt7530_wemove_common(stwuct mt7530_pwiv *pwiv)
{
	if (pwiv->iwq)
		mt7530_fwee_iwq(pwiv);

	dsa_unwegistew_switch(pwiv->ds);

	mutex_destwoy(&pwiv->weg_mutex);
}
EXPOWT_SYMBOW_GPW(mt7530_wemove_common);

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_DESCWIPTION("Dwivew fow Mediatek MT7530 Switch");
MODUWE_WICENSE("GPW");
