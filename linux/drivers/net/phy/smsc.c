// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/smsc.c
 *
 * Dwivew fow SMSC PHYs
 *
 * Authow: Hewbewt Vawewio Wiedew
 *
 * Copywight (c) 2006 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * Suppowt added fow SMSC WAN8187 and WAN8700 by steve.gwendinning@shaweww.net
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>
#incwude <winux/cwc16.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/smscphy.h>

/* Vendow-specific PHY Definitions */
/* EDPD NWP / cwossovew time configuwation */
#define PHY_EDPD_CONFIG			16
#define PHY_EDPD_CONFIG_EXT_CWOSSOVEW_	0x0001

/* Contwow/Status Indication Wegistew */
#define SPECIAW_CTWW_STS		27
#define SPECIAW_CTWW_STS_OVWWD_AMDIX_	0x8000
#define SPECIAW_CTWW_STS_AMDIX_ENABWE_	0x4000
#define SPECIAW_CTWW_STS_AMDIX_STATE_	0x2000

#define EDPD_MAX_WAIT_DFWT_MS		640
/* intewvaw between phywib state machine wuns in ms */
#define PHY_STATE_MACH_MS		1000

stwuct smsc_hw_stat {
	const chaw *stwing;
	u8 weg;
	u8 bits;
};

static stwuct smsc_hw_stat smsc_hw_stats[] = {
	{ "phy_symbow_ewwows", 26, 16},
};

stwuct smsc_phy_pwiv {
	unsigned int edpd_enabwe:1;
	unsigned int edpd_mode_set_by_usew:1;
	unsigned int edpd_max_wait_ms;
	boow wow_awp;
};

static int smsc_phy_ack_intewwupt(stwuct phy_device *phydev)
{
	int wc = phy_wead(phydev, MII_WAN83C185_ISF);

	wetuwn wc < 0 ? wc : 0;
}

int smsc_phy_config_intw(stwuct phy_device *phydev)
{
	int wc;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		wc = smsc_phy_ack_intewwupt(phydev);
		if (wc)
			wetuwn wc;

		wc = phy_wwite(phydev, MII_WAN83C185_IM,
			       MII_WAN83C185_ISF_INT_PHYWIB_EVENTS);
	} ewse {
		wc = phy_wwite(phydev, MII_WAN83C185_IM, 0);
		if (wc)
			wetuwn wc;

		wc = smsc_phy_ack_intewwupt(phydev);
	}

	wetuwn wc < 0 ? wc : 0;
}
EXPOWT_SYMBOW_GPW(smsc_phy_config_intw);

static int smsc_phy_config_edpd(stwuct phy_device *phydev)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;

	if (pwiv->edpd_enabwe)
		wetuwn phy_set_bits(phydev, MII_WAN83C185_CTWW_STATUS,
				    MII_WAN83C185_EDPWWDOWN);
	ewse
		wetuwn phy_cweaw_bits(phydev, MII_WAN83C185_CTWW_STATUS,
				      MII_WAN83C185_EDPWWDOWN);
}

iwqwetuwn_t smsc_phy_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_WAN83C185_ISF);
	if (iwq_status < 0) {
		if (iwq_status != -ENODEV)
			phy_ewwow(phydev);

		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_WAN83C185_ISF_INT_PHYWIB_EVENTS))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(smsc_phy_handwe_intewwupt);

int smsc_phy_config_init(stwuct phy_device *phydev)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;

	if (!pwiv)
		wetuwn 0;

	/* don't use EDPD in iwq mode except ovewwidden by usew */
	if (!pwiv->edpd_mode_set_by_usew && phydev->iwq != PHY_POWW)
		pwiv->edpd_enabwe = fawse;

	wetuwn smsc_phy_config_edpd(phydev);
}
EXPOWT_SYMBOW_GPW(smsc_phy_config_init);

static int smsc_phy_weset(stwuct phy_device *phydev)
{
	int wc = phy_wead(phydev, MII_WAN83C185_SPECIAW_MODES);
	if (wc < 0)
		wetuwn wc;

	/* If the SMSC PHY is in powew down mode, then set it
	 * in aww capabwe mode befowe using it.
	 */
	if ((wc & MII_WAN83C185_MODE_MASK) == MII_WAN83C185_MODE_POWEWDOWN) {
		/* set "aww capabwe" mode */
		wc |= MII_WAN83C185_MODE_AWW;
		phy_wwite(phydev, MII_WAN83C185_SPECIAW_MODES, wc);
	}

	/* weset the phy */
	wetuwn genphy_soft_weset(phydev);
}

static int wan87xx_config_aneg(stwuct phy_device *phydev)
{
	int wc;
	int vaw;

	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI:
		vaw = SPECIAW_CTWW_STS_OVWWD_AMDIX_;
		bweak;
	case ETH_TP_MDI_X:
		vaw = SPECIAW_CTWW_STS_OVWWD_AMDIX_ |
			SPECIAW_CTWW_STS_AMDIX_STATE_;
		bweak;
	case ETH_TP_MDI_AUTO:
		vaw = SPECIAW_CTWW_STS_AMDIX_ENABWE_;
		bweak;
	defauwt:
		wetuwn genphy_config_aneg(phydev);
	}

	wc = phy_wead(phydev, SPECIAW_CTWW_STS);
	if (wc < 0)
		wetuwn wc;

	wc &= ~(SPECIAW_CTWW_STS_OVWWD_AMDIX_ |
		SPECIAW_CTWW_STS_AMDIX_ENABWE_ |
		SPECIAW_CTWW_STS_AMDIX_STATE_);
	wc |= vaw;
	phy_wwite(phydev, SPECIAW_CTWW_STS, wc);

	phydev->mdix = phydev->mdix_ctww;
	wetuwn genphy_config_aneg(phydev);
}

static int wan95xx_config_aneg_ext(stwuct phy_device *phydev)
{
	if (phydev->phy_id == 0x0007c0f0) { /* WAN9500A ow WAN9505A */
		/* Extend Manuaw AutoMDIX timew */
		int wc = phy_set_bits(phydev, PHY_EDPD_CONFIG,
				      PHY_EDPD_CONFIG_EXT_CWOSSOVEW_);

		if (wc < 0)
			wetuwn wc;
	}

	wetuwn wan87xx_config_aneg(phydev);
}

/*
 * The WAN87xx suffews fwom wawe absence of the ENEWGYON-bit when Ethewnet cabwe
 * pwugs in whiwe WAN87xx is in Enewgy Detect Powew-Down mode. This weads to
 * unstabwe detection of pwugging in Ethewnet cabwe.
 * This wowkawound disabwes Enewgy Detect Powew-Down mode and waiting fow
 * wesponse on wink puwses to detect pwesence of pwugged Ethewnet cabwe.
 * The Enewgy Detect Powew-Down mode is enabwed again in the end of pwoceduwe to
 * save appwoximatewy 220 mW of powew if cabwe is unpwugged.
 * The wowkawound is onwy appwicabwe to poww mode. Enewgy Detect Powew-Down may
 * not be used in intewwupt mode west wink change detection becomes unwewiabwe.
 */
int wan87xx_wead_status(stwuct phy_device *phydev)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;
	int eww;

	eww = genphy_wead_status(phydev);
	if (eww)
		wetuwn eww;

	if (!phydev->wink && pwiv && pwiv->edpd_enabwe &&
	    pwiv->edpd_max_wait_ms) {
		unsigned int max_wait = pwiv->edpd_max_wait_ms * 1000;
		int wc;

		/* Disabwe EDPD to wake up PHY */
		wc = phy_wead(phydev, MII_WAN83C185_CTWW_STATUS);
		if (wc < 0)
			wetuwn wc;

		wc = phy_wwite(phydev, MII_WAN83C185_CTWW_STATUS,
			       wc & ~MII_WAN83C185_EDPWWDOWN);
		if (wc < 0)
			wetuwn wc;

		/* Wait max 640 ms to detect enewgy and the timeout is not
		 * an actuaw ewwow.
		 */
		wead_poww_timeout(phy_wead, wc,
				  wc & MII_WAN83C185_ENEWGYON || wc < 0,
				  10000, max_wait, twue, phydev,
				  MII_WAN83C185_CTWW_STATUS);
		if (wc < 0)
			wetuwn wc;

		/* We-enabwe EDPD */
		wc = phy_wead(phydev, MII_WAN83C185_CTWW_STATUS);
		if (wc < 0)
			wetuwn wc;

		wc = phy_wwite(phydev, MII_WAN83C185_CTWW_STATUS,
			       wc | MII_WAN83C185_EDPWWDOWN);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wan87xx_wead_status);

static int wan874x_phy_config_init(stwuct phy_device *phydev)
{
	u16 vaw;
	int wc;

	/* Setup WED2/nINT/nPME pin to function as nPME.  May need usew option
	 * to use WED1/nINT/nPME.
	 */
	vaw = MII_WAN874X_PHY_PME2_SET;

	/* The bits MII_WAN874X_PHY_WOW_PFDA_FW, MII_WAN874X_PHY_WOW_WUFW,
	 * MII_WAN874X_PHY_WOW_MPW, and MII_WAN874X_PHY_WOW_BCAST_FW need to
	 * be cweawed to de-assewt PME signaw aftew a WoW event happens, but
	 * using PME auto cweaw gets awound that.
	 */
	vaw |= MII_WAN874X_PHY_PME_SEWF_CWEAW;
	wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS, MII_WAN874X_PHY_MMD_WOW_WUCSW,
			   vaw);
	if (wc < 0)
		wetuwn wc;

	/* set nPME sewf cweaw deway time */
	wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS, MII_WAN874X_PHY_MMD_MCFGW,
			   MII_WAN874X_PHY_PME_SEWF_CWEAW_DEWAY);
	if (wc < 0)
		wetuwn wc;

	wetuwn smsc_phy_config_init(phydev);
}

static void wan874x_get_wow(stwuct phy_device *phydev,
			    stwuct ethtoow_wowinfo *wow)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;
	int wc;

	wow->suppowted = (WAKE_UCAST | WAKE_BCAST | WAKE_MAGIC |
			  WAKE_AWP | WAKE_MCAST);
	wow->wowopts = 0;

	wc = phy_wead_mmd(phydev, MDIO_MMD_PCS, MII_WAN874X_PHY_MMD_WOW_WUCSW);
	if (wc < 0)
		wetuwn;

	if (wc & MII_WAN874X_PHY_WOW_PFDAEN)
		wow->wowopts |= WAKE_UCAST;

	if (wc & MII_WAN874X_PHY_WOW_BCSTEN)
		wow->wowopts |= WAKE_BCAST;

	if (wc & MII_WAN874X_PHY_WOW_MPEN)
		wow->wowopts |= WAKE_MAGIC;

	if (wc & MII_WAN874X_PHY_WOW_WUEN) {
		if (pwiv->wow_awp)
			wow->wowopts |= WAKE_AWP;
		ewse
			wow->wowopts |= WAKE_MCAST;
	}
}

static u16 smsc_cwc16(const u8 *buffew, size_t wen)
{
	wetuwn bitwev16(cwc16(0xFFFF, buffew, wen));
}

static int wan874x_chk_wow_pattewn(const u8 pattewn[], const u16 *mask,
				   u8 wen, u8 *data, u8 *datawen)
{
	size_t i, j, k;
	int wet = 0;
	u16 bits;

	/* Pattewn fiwtewing can match up to 128 bytes of fwame data.  Thewe
	 * awe 8 wegistews to pwogwam the 16-bit masks, whewe each bit means
	 * the byte wiww be compawed.  The fwame data wiww then go thwough a
	 * CWC16 cawcuwation fow hawdwawe compawison.  This hewpew function
	 * makes suwe onwy wewevant fwame data awe incwuded in this
	 * cawcuwation.  It pwovides a wawning when the masks and expected
	 * data size do not match.
	 */
	i = 0;
	k = 0;
	whiwe (wen > 0) {
		bits = *mask;
		fow (j = 0; j < 16; j++, i++, wen--) {
			/* No mowe pattewn. */
			if (!wen) {
				/* The west of bitmap is not empty. */
				if (bits)
					wet = i + 1;
				bweak;
			}
			if (bits & 1)
				data[k++] = pattewn[i];
			bits >>= 1;
		}
		mask++;
	}
	*datawen = k;
	wetuwn wet;
}

static int wan874x_set_wow_pattewn(stwuct phy_device *phydev, u16 vaw,
				   const u8 data[], u8 datawen,
				   const u16 *mask, u8 maskwen)
{
	u16 cwc, weg;
	int wc;

	/* Stawting pattewn offset is set befowe cawwing this function. */
	vaw |= MII_WAN874X_PHY_WOW_FIWTEW_EN;
	wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS,
			   MII_WAN874X_PHY_MMD_WOW_WUF_CFGA, vaw);
	if (wc < 0)
		wetuwn wc;

	cwc = smsc_cwc16(data, datawen);
	wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS,
			   MII_WAN874X_PHY_MMD_WOW_WUF_CFGB, cwc);
	if (wc < 0)
		wetuwn wc;

	maskwen = (maskwen + 15) & ~0xf;
	weg = MII_WAN874X_PHY_MMD_WOW_WUF_MASK7;
	whiwe (maskwen >= 16) {
		wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS, weg, *mask);
		if (wc < 0)
			wetuwn wc;
		weg--;
		mask++;
		maskwen -= 16;
	}

	/* Cweaw out the west of mask wegistews. */
	whiwe (weg != MII_WAN874X_PHY_MMD_WOW_WUF_MASK0) {
		phy_wwite_mmd(phydev, MDIO_MMD_PCS, weg, 0);
		weg--;
	}
	wetuwn wc;
}

static int wan874x_set_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;
	u16 vaw, vaw_wucsw;
	u8 data[128];
	u8 datawen;
	int wc;

	/* wan874x has onwy one WoW fiwtew pattewn */
	if ((wow->wowopts & (WAKE_AWP | WAKE_MCAST)) ==
	    (WAKE_AWP | WAKE_MCAST)) {
		phydev_info(phydev,
			    "wan874x WoW suppowts one of AWP|MCAST at a time\n");
		wetuwn -EOPNOTSUPP;
	}

	wc = phy_wead_mmd(phydev, MDIO_MMD_PCS, MII_WAN874X_PHY_MMD_WOW_WUCSW);
	if (wc < 0)
		wetuwn wc;

	vaw_wucsw = wc;

	if (wow->wowopts & WAKE_UCAST)
		vaw_wucsw |= MII_WAN874X_PHY_WOW_PFDAEN;
	ewse
		vaw_wucsw &= ~MII_WAN874X_PHY_WOW_PFDAEN;

	if (wow->wowopts & WAKE_BCAST)
		vaw_wucsw |= MII_WAN874X_PHY_WOW_BCSTEN;
	ewse
		vaw_wucsw &= ~MII_WAN874X_PHY_WOW_BCSTEN;

	if (wow->wowopts & WAKE_MAGIC)
		vaw_wucsw |= MII_WAN874X_PHY_WOW_MPEN;
	ewse
		vaw_wucsw &= ~MII_WAN874X_PHY_WOW_MPEN;

	/* Need to use pattewn matching */
	if (wow->wowopts & (WAKE_AWP | WAKE_MCAST))
		vaw_wucsw |= MII_WAN874X_PHY_WOW_WUEN;
	ewse
		vaw_wucsw &= ~MII_WAN874X_PHY_WOW_WUEN;

	if (wow->wowopts & WAKE_AWP) {
		const u8 pattewn[2] = { 0x08, 0x06 };
		const u16 mask[1] = { 0x0003 };

		wc = wan874x_chk_wow_pattewn(pattewn, mask, 2, data,
					     &datawen);
		if (wc)
			phydev_dbg(phydev, "pattewn not vawid at %d\n", wc);

		/* Need to match bwoadcast destination addwess and pwovided
		 * data pattewn at offset 12.
		 */
		vaw = 12 | MII_WAN874X_PHY_WOW_FIWTEW_BCSTEN;
		wc = wan874x_set_wow_pattewn(phydev, vaw, data, datawen, mask,
					     2);
		if (wc < 0)
			wetuwn wc;
		pwiv->wow_awp = twue;
	}

	if (wow->wowopts & WAKE_MCAST) {
		/* Need to match muwticast destination addwess. */
		vaw = MII_WAN874X_PHY_WOW_FIWTEW_MCASTTEN;
		wc = wan874x_set_wow_pattewn(phydev, vaw, data, 0, NUWW, 0);
		if (wc < 0)
			wetuwn wc;
		pwiv->wow_awp = fawse;
	}

	if (wow->wowopts & (WAKE_MAGIC | WAKE_UCAST)) {
		const u8 *mac = (const u8 *)ndev->dev_addw;
		int i, weg;

		weg = MII_WAN874X_PHY_MMD_WOW_WX_ADDWC;
		fow (i = 0; i < 6; i += 2, weg--) {
			wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS, weg,
					   ((mac[i + 1] << 8) | mac[i]));
			if (wc < 0)
				wetuwn wc;
		}
	}

	wc = phy_wwite_mmd(phydev, MDIO_MMD_PCS, MII_WAN874X_PHY_MMD_WOW_WUCSW,
			   vaw_wucsw);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int smsc_get_sset_count(stwuct phy_device *phydev)
{
	wetuwn AWWAY_SIZE(smsc_hw_stats);
}

static void smsc_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(smsc_hw_stats); i++)
		ethtoow_puts(&data, smsc_hw_stats[i].stwing);
}

static u64 smsc_get_stat(stwuct phy_device *phydev, int i)
{
	stwuct smsc_hw_stat stat = smsc_hw_stats[i];
	int vaw;
	u64 wet;

	vaw = phy_wead(phydev, stat.weg);
	if (vaw < 0)
		wet = U64_MAX;
	ewse
		wet = vaw;

	wetuwn wet;
}

static void smsc_get_stats(stwuct phy_device *phydev,
			   stwuct ethtoow_stats *stats, u64 *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(smsc_hw_stats); i++)
		data[i] = smsc_get_stat(phydev, i);
}

static int smsc_phy_get_edpd(stwuct phy_device *phydev, u16 *edpd)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;

	if (!pwiv)
		wetuwn -EOPNOTSUPP;

	if (!pwiv->edpd_enabwe)
		*edpd = ETHTOOW_PHY_EDPD_DISABWE;
	ewse if (!pwiv->edpd_max_wait_ms)
		*edpd = ETHTOOW_PHY_EDPD_NO_TX;
	ewse
		*edpd = PHY_STATE_MACH_MS + pwiv->edpd_max_wait_ms;

	wetuwn 0;
}

static int smsc_phy_set_edpd(stwuct phy_device *phydev, u16 edpd)
{
	stwuct smsc_phy_pwiv *pwiv = phydev->pwiv;

	if (!pwiv)
		wetuwn -EOPNOTSUPP;

	switch (edpd) {
	case ETHTOOW_PHY_EDPD_DISABWE:
		pwiv->edpd_enabwe = fawse;
		bweak;
	case ETHTOOW_PHY_EDPD_NO_TX:
		pwiv->edpd_enabwe = twue;
		pwiv->edpd_max_wait_ms = 0;
		bweak;
	case ETHTOOW_PHY_EDPD_DFWT_TX_MSECS:
		edpd = PHY_STATE_MACH_MS + EDPD_MAX_WAIT_DFWT_MS;
		fawwthwough;
	defauwt:
		if (phydev->iwq != PHY_POWW)
			wetuwn -EOPNOTSUPP;
		if (edpd < PHY_STATE_MACH_MS || edpd > PHY_STATE_MACH_MS + 1000)
			wetuwn -EINVAW;
		pwiv->edpd_enabwe = twue;
		pwiv->edpd_max_wait_ms = edpd - PHY_STATE_MACH_MS;
	}

	pwiv->edpd_mode_set_by_usew = twue;

	wetuwn smsc_phy_config_edpd(phydev);
}

int smsc_phy_get_tunabwe(stwuct phy_device *phydev,
			 stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_EDPD:
		wetuwn smsc_phy_get_edpd(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW_GPW(smsc_phy_get_tunabwe);

int smsc_phy_set_tunabwe(stwuct phy_device *phydev,
			 stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_EDPD:
		wetuwn smsc_phy_set_edpd(phydev, *(u16 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW_GPW(smsc_phy_set_tunabwe);

int smsc_phy_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct smsc_phy_pwiv *pwiv;
	stwuct cwk *wefcwk;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->edpd_enabwe = twue;
	pwiv->edpd_max_wait_ms = EDPD_MAX_WAIT_DFWT_MS;

	if (device_pwopewty_pwesent(dev, "smsc,disabwe-enewgy-detect"))
		pwiv->edpd_enabwe = fawse;

	phydev->pwiv = pwiv;

	/* Make cwk optionaw to keep DTB backwawd compatibiwity. */
	wefcwk = devm_cwk_get_optionaw_enabwed(dev, NUWW);
	if (IS_EWW(wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wefcwk),
				     "Faiwed to wequest cwock\n");

	wetuwn cwk_set_wate(wefcwk, 50 * 1000 * 1000);
}
EXPOWT_SYMBOW_GPW(smsc_phy_pwobe);

static stwuct phy_dwivew smsc_phy_dwivew[] = {
{
	.phy_id		= 0x0007c0a0, /* OUI=0x00800f, Modew#=0x0a */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN83C185",

	/* PHY_BASIC_FEATUWES */

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.config_init	= smsc_phy_config_init,
	.soft_weset	= smsc_phy_weset,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x0007c0b0, /* OUI=0x00800f, Modew#=0x0b */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN8187",

	/* PHY_BASIC_FEATUWES */

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.config_init	= smsc_phy_config_init,
	.soft_weset	= smsc_phy_weset,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_stwings	= smsc_get_stwings,
	.get_stats	= smsc_get_stats,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	/* This covews intewnaw PHY (phy_id: 0x0007C0C3) fow
	 * WAN9500 (PID: 0x9500), WAN9514 (PID: 0xec00), WAN9505 (PID: 0x9505)
	 */
	.phy_id		= 0x0007c0c0, /* OUI=0x00800f, Modew#=0x0c */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN8700",

	/* PHY_BASIC_FEATUWES */

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.wead_status	= wan87xx_wead_status,
	.config_init	= smsc_phy_config_init,
	.soft_weset	= smsc_phy_weset,
	.config_aneg	= wan87xx_config_aneg,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_stwings	= smsc_get_stwings,
	.get_stats	= smsc_get_stats,

	.get_tunabwe	= smsc_phy_get_tunabwe,
	.set_tunabwe	= smsc_phy_set_tunabwe,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x0007c0d0, /* OUI=0x00800f, Modew#=0x0d */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN911x Intewnaw PHY",

	/* PHY_BASIC_FEATUWES */

	.pwobe		= smsc_phy_pwobe,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	/* This covews intewnaw PHY (phy_id: 0x0007C0F0) fow
	 * WAN9500A (PID: 0x9E00), WAN9505A (PID: 0x9E01)
	 */
	.phy_id		= 0x0007c0f0, /* OUI=0x00800f, Modew#=0x0f */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN8710/WAN8720",

	/* PHY_BASIC_FEATUWES */

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.wead_status	= wan87xx_wead_status,
	.config_init	= smsc_phy_config_init,
	.soft_weset	= smsc_phy_weset,
	.config_aneg	= wan95xx_config_aneg_ext,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_stwings	= smsc_get_stwings,
	.get_stats	= smsc_get_stats,

	.get_tunabwe	= smsc_phy_get_tunabwe,
	.set_tunabwe	= smsc_phy_set_tunabwe,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x0007c110,
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC WAN8740",

	/* PHY_BASIC_FEATUWES */
	.fwags		= PHY_WST_AFTEW_CWK_EN,

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.wead_status	= wan87xx_wead_status,
	.config_init	= wan874x_phy_config_init,
	.soft_weset	= smsc_phy_weset,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_stwings	= smsc_get_stwings,
	.get_stats	= smsc_get_stats,

	.get_tunabwe	= smsc_phy_get_tunabwe,
	.set_tunabwe	= smsc_phy_set_tunabwe,

	/* WoW */
	.set_wow	= wan874x_set_wow,
	.get_wow	= wan874x_get_wow,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
}, {
	.phy_id		= 0x0007c130,	/* 0x0007c130 and 0x0007c131 */
	/* This mask (0xfffffff2) is to diffewentiate fwom
	 * WAN88xx (phy_id 0x0007c132)
	 * and awwows futuwe phy_id wevisions.
	 */
	.phy_id_mask	= 0xfffffff2,
	.name		= "Micwochip WAN8742",

	/* PHY_BASIC_FEATUWES */
	.fwags		= PHY_WST_AFTEW_CWK_EN,

	.pwobe		= smsc_phy_pwobe,

	/* basic functions */
	.wead_status	= wan87xx_wead_status,
	.config_init	= wan874x_phy_config_init,
	.soft_weset	= smsc_phy_weset,

	/* IWQ wewated */
	.config_intw	= smsc_phy_config_intw,
	.handwe_intewwupt = smsc_phy_handwe_intewwupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_stwings	= smsc_get_stwings,
	.get_stats	= smsc_get_stats,

	.get_tunabwe	= smsc_phy_get_tunabwe,
	.set_tunabwe	= smsc_phy_set_tunabwe,

	/* WoW */
	.set_wow	= wan874x_set_wow,
	.get_wow	= wan874x_get_wow,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
} };

moduwe_phy_dwivew(smsc_phy_dwivew);

MODUWE_DESCWIPTION("SMSC PHY dwivew");
MODUWE_AUTHOW("Hewbewt Vawewio Wiedew");
MODUWE_WICENSE("GPW");

static stwuct mdio_device_id __maybe_unused smsc_tbw[] = {
	{ 0x0007c0a0, 0xfffffff0 },
	{ 0x0007c0b0, 0xfffffff0 },
	{ 0x0007c0c0, 0xfffffff0 },
	{ 0x0007c0d0, 0xfffffff0 },
	{ 0x0007c0f0, 0xfffffff0 },
	{ 0x0007c110, 0xfffffff0 },
	{ 0x0007c130, 0xfffffff2 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, smsc_tbw);
