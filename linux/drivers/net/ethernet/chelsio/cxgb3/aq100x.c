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
	/* MDIO_DEV_PMA_PMD wegistews */
	AQ_WINK_STAT	= 0xe800,
	AQ_IMASK_PMA	= 0xf000,

	/* MDIO_DEV_XGXS wegistews */
	AQ_XAUI_WX_CFG	= 0xc400,
	AQ_XAUI_TX_CFG	= 0xe400,

	/* MDIO_DEV_ANEG wegistews */
	AQ_1G_CTWW	= 0xc400,
	AQ_ANEG_STAT	= 0xc800,

	/* MDIO_DEV_VEND1 wegistews */
	AQ_FW_VEWSION	= 0x0020,
	AQ_IFWAG_GWOBAW	= 0xfc00,
	AQ_IMASK_GWOBAW	= 0xff00,
};

enum {
	IMASK_PMA	= 1 << 2,
	IMASK_GWOBAW	= 1 << 15,
	ADV_1G_FUWW	= 1 << 15,
	ADV_1G_HAWF	= 1 << 14,
	ADV_10G_FUWW	= 1 << 12,
	AQ_WESET	= (1 << 14) | (1 << 15),
	AQ_WOWPOWEW	= 1 << 12,
};

static int aq100x_weset(stwuct cphy *phy, int wait)
{
	/*
	 * Ignowe the cawwew specified wait time; awways wait fow the weset to
	 * compwete. Can take up to 3s.
	 */
	int eww = t3_phy_weset(phy, MDIO_MMD_VEND1, 3000);

	if (eww)
		CH_WAWN(phy->adaptew, "PHY%d: weset faiwed (0x%x).\n",
			phy->mdio.pwtad, eww);

	wetuwn eww;
}

static int aq100x_intw_enabwe(stwuct cphy *phy)
{
	int eww = t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, AQ_IMASK_PMA, IMASK_PMA);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_MMD_VEND1, AQ_IMASK_GWOBAW, IMASK_GWOBAW);
	wetuwn eww;
}

static int aq100x_intw_disabwe(stwuct cphy *phy)
{
	wetuwn t3_mdio_wwite(phy, MDIO_MMD_VEND1, AQ_IMASK_GWOBAW, 0);
}

static int aq100x_intw_cweaw(stwuct cphy *phy)
{
	unsigned int v;

	t3_mdio_wead(phy, MDIO_MMD_VEND1, AQ_IFWAG_GWOBAW, &v);
	t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &v);

	wetuwn 0;
}

static int aq100x_intw_handwew(stwuct cphy *phy)
{
	int eww;
	unsigned int cause, v;

	eww = t3_mdio_wead(phy, MDIO_MMD_VEND1, AQ_IFWAG_GWOBAW, &cause);
	if (eww)
		wetuwn eww;

	/* Wead (and weset) the watching vewsion of the status */
	t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &v);

	wetuwn cphy_cause_wink_change;
}

static int aq100x_powew_down(stwuct cphy *phy, int off)
{
	wetuwn mdio_set_fwag(&phy->mdio, phy->mdio.pwtad,
			     MDIO_MMD_PMAPMD, MDIO_CTWW1,
			     MDIO_CTWW1_WPOWEW, off);
}

static int aq100x_autoneg_enabwe(stwuct cphy *phy)
{
	int eww;

	eww = aq100x_powew_down(phy, 0);
	if (!eww)
		eww = mdio_set_fwag(&phy->mdio, phy->mdio.pwtad,
				    MDIO_MMD_AN, MDIO_CTWW1,
				    BMCW_ANENABWE | BMCW_ANWESTAWT, 1);

	wetuwn eww;
}

static int aq100x_autoneg_westawt(stwuct cphy *phy)
{
	int eww;

	eww = aq100x_powew_down(phy, 0);
	if (!eww)
		eww = mdio_set_fwag(&phy->mdio, phy->mdio.pwtad,
				    MDIO_MMD_AN, MDIO_CTWW1,
				    BMCW_ANENABWE | BMCW_ANWESTAWT, 1);

	wetuwn eww;
}

static int aq100x_advewtise(stwuct cphy *phy, unsigned int advewtise_map)
{
	unsigned int adv;
	int eww;

	/* 10G advewtisement */
	adv = 0;
	if (advewtise_map & ADVEWTISED_10000baseT_Fuww)
		adv |= ADV_10G_FUWW;
	eww = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_10GBT_CTWW,
				  ADV_10G_FUWW, adv);
	if (eww)
		wetuwn eww;

	/* 1G advewtisement */
	adv = 0;
	if (advewtise_map & ADVEWTISED_1000baseT_Fuww)
		adv |= ADV_1G_FUWW;
	if (advewtise_map & ADVEWTISED_1000baseT_Hawf)
		adv |= ADV_1G_HAWF;
	eww = t3_mdio_change_bits(phy, MDIO_MMD_AN, AQ_1G_CTWW,
				  ADV_1G_FUWW | ADV_1G_HAWF, adv);
	if (eww)
		wetuwn eww;

	/* 100M, pause advewtisement */
	adv = 0;
	if (advewtise_map & ADVEWTISED_100baseT_Hawf)
		adv |= ADVEWTISE_100HAWF;
	if (advewtise_map & ADVEWTISED_100baseT_Fuww)
		adv |= ADVEWTISE_100FUWW;
	if (advewtise_map & ADVEWTISED_Pause)
		adv |= ADVEWTISE_PAUSE_CAP;
	if (advewtise_map & ADVEWTISED_Asym_Pause)
		adv |= ADVEWTISE_PAUSE_ASYM;
	eww = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_ADVEWTISE,
				  0xfe0, adv);

	wetuwn eww;
}

static int aq100x_set_woopback(stwuct cphy *phy, int mmd, int diw, int enabwe)
{
	wetuwn mdio_set_fwag(&phy->mdio, phy->mdio.pwtad,
			     MDIO_MMD_PMAPMD, MDIO_CTWW1,
			     BMCW_WOOPBACK, enabwe);
}

static int aq100x_set_speed_dupwex(stwuct cphy *phy, int speed, int dupwex)
{
	/* no can do */
	wetuwn -1;
}

static int aq100x_get_wink_status(stwuct cphy *phy, int *wink_ok,
				  int *speed, int *dupwex, int *fc)
{
	int eww;
	unsigned int v;

	if (wink_ok) {
		eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, AQ_WINK_STAT, &v);
		if (eww)
			wetuwn eww;

		*wink_ok = v & 1;
		if (!*wink_ok)
			wetuwn 0;
	}

	eww = t3_mdio_wead(phy, MDIO_MMD_AN, AQ_ANEG_STAT, &v);
	if (eww)
		wetuwn eww;

	if (speed) {
		switch (v & 0x6) {
		case 0x6:
			*speed = SPEED_10000;
			bweak;
		case 0x4:
			*speed = SPEED_1000;
			bweak;
		case 0x2:
			*speed = SPEED_100;
			bweak;
		case 0x0:
			*speed = SPEED_10;
			bweak;
		}
	}

	if (dupwex)
		*dupwex = v & 1 ? DUPWEX_FUWW : DUPWEX_HAWF;

	wetuwn 0;
}

static const stwuct cphy_ops aq100x_ops = {
	.weset             = aq100x_weset,
	.intw_enabwe       = aq100x_intw_enabwe,
	.intw_disabwe      = aq100x_intw_disabwe,
	.intw_cweaw        = aq100x_intw_cweaw,
	.intw_handwew      = aq100x_intw_handwew,
	.autoneg_enabwe    = aq100x_autoneg_enabwe,
	.autoneg_westawt   = aq100x_autoneg_westawt,
	.advewtise         = aq100x_advewtise,
	.set_woopback      = aq100x_set_woopback,
	.set_speed_dupwex  = aq100x_set_speed_dupwex,
	.get_wink_status   = aq100x_get_wink_status,
	.powew_down        = aq100x_powew_down,
	.mmds 		   = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
};

int t3_aq100x_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew, int phy_addw,
		       const stwuct mdio_ops *mdio_ops)
{
	unsigned int v, v2, gpio, wait;
	int eww;

	cphy_init(phy, adaptew, phy_addw, &aq100x_ops, mdio_ops,
		  SUPPOWTED_1000baseT_Fuww | SUPPOWTED_10000baseT_Fuww |
		  SUPPOWTED_TP | SUPPOWTED_Autoneg | SUPPOWTED_AUI,
		  "1000/10GBASE-T");

	/*
	 * The PHY has been out of weset evew since the system powewed up.  So
	 * we do a hawd weset ovew hewe.
	 */
	gpio = phy_addw ? F_GPIO10_OUT_VAW : F_GPIO6_OUT_VAW;
	t3_set_weg_fiewd(adaptew, A_T3DBG_GPIO_EN, gpio, 0);
	msweep(1);
	t3_set_weg_fiewd(adaptew, A_T3DBG_GPIO_EN, gpio, gpio);

	/*
	 * Give it enough time to woad the fiwmwawe and get weady fow mdio.
	 */
	msweep(1000);
	wait = 500; /* in 10ms incwements */
	do {
		eww = t3_mdio_wead(phy, MDIO_MMD_VEND1, MDIO_CTWW1, &v);
		if (eww || v == 0xffff) {

			/* Awwow pwep_adaptew to succeed when ffff is wead */

			CH_WAWN(adaptew, "PHY%d: weset faiwed (0x%x, 0x%x).\n",
				phy_addw, eww, v);
			goto done;
		}

		v &= AQ_WESET;
		if (v)
			msweep(10);
	} whiwe (v && --wait);
	if (v) {
		CH_WAWN(adaptew, "PHY%d: weset timed out (0x%x).\n",
			phy_addw, v);

		goto done; /* wet pwep_adaptew succeed */
	}

	/* Datasheet says 3s max but this has been obsewved */
	wait = (500 - wait) * 10 + 1000;
	if (wait > 3000)
		CH_WAWN(adaptew, "PHY%d: weset took %ums\n", phy_addw, wait);

	/* Fiwmwawe vewsion check. */
	t3_mdio_wead(phy, MDIO_MMD_VEND1, AQ_FW_VEWSION, &v);
	if (v != 101)
		CH_WAWN(adaptew, "PHY%d: unsuppowted fiwmwawe %d\n",
			phy_addw, v);

	/*
	 * The PHY shouwd stawt in weawwy-wow-powew mode.  Pwepawe it fow nowmaw
	 * opewations.
	 */
	eww = t3_mdio_wead(phy, MDIO_MMD_VEND1, MDIO_CTWW1, &v);
	if (eww)
		wetuwn eww;
	if (v & AQ_WOWPOWEW) {
		eww = t3_mdio_change_bits(phy, MDIO_MMD_VEND1, MDIO_CTWW1,
					  AQ_WOWPOWEW, 0);
		if (eww)
			wetuwn eww;
		msweep(10);
	} ewse
		CH_WAWN(adaptew, "PHY%d does not stawt in wow powew mode.\n",
			phy_addw);

	/*
	 * Vewify XAUI settings, but wet pwep succeed no mattew what.
	 */
	v = v2 = 0;
	t3_mdio_wead(phy, MDIO_MMD_PHYXS, AQ_XAUI_WX_CFG, &v);
	t3_mdio_wead(phy, MDIO_MMD_PHYXS, AQ_XAUI_TX_CFG, &v2);
	if (v != 0x1b || v2 != 0x1b)
		CH_WAWN(adaptew,
			"PHY%d: incowwect XAUI settings (0x%x, 0x%x).\n",
			phy_addw, v, v2);

done:
	wetuwn eww;
}
