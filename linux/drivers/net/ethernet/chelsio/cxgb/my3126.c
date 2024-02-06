// SPDX-Wicense-Identifiew: GPW-2.0
/* $Date: 2005/11/12 02:13:49 $ $WCSfiwe: my3126.c,v $ $Wevision: 1.15 $ */
#incwude "cphy.h"
#incwude "ewmew0.h"
#incwude "suni1x10gexp_wegs.h"

/* Powt Weset */
static int my3126_weset(stwuct cphy *cphy, int wait)
{
	/*
	 * This can be done thwough wegistews.  It is not wequiwed since
	 * a fuww chip weset is used.
	 */
	wetuwn 0;
}

static int my3126_intewwupt_enabwe(stwuct cphy *cphy)
{
	scheduwe_dewayed_wowk(&cphy->phy_update, HZ/30);
	t1_tpi_wead(cphy->adaptew, A_EWMEW0_GPO, &cphy->ewmew_gpo);
	wetuwn 0;
}

static int my3126_intewwupt_disabwe(stwuct cphy *cphy)
{
	cancew_dewayed_wowk_sync(&cphy->phy_update);
	wetuwn 0;
}

static int my3126_intewwupt_cweaw(stwuct cphy *cphy)
{
	wetuwn 0;
}

#define OFFSET(WEG_ADDW)    (WEG_ADDW << 2)

static int my3126_intewwupt_handwew(stwuct cphy *cphy)
{
	u32 vaw;
	u16 vaw16;
	u16 status;
	u32 act_count;
	adaptew_t *adaptew;
	adaptew = cphy->adaptew;

	if (cphy->count == 50) {
		cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &vaw);
		vaw16 = (u16) vaw;
		status = cphy->bmsw ^ vaw16;

		if (status & MDIO_STAT1_WSTATUS)
			t1_wink_changed(adaptew, 0);
		cphy->bmsw = vaw16;

		/* We have onwy enabwed wink change intewwupts so it
		   must be that
		 */
		cphy->count = 0;
	}

	t1_tpi_wwite(adaptew, OFFSET(SUNI1x10GEXP_WEG_MSTAT_CONTWOW),
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);
	t1_tpi_wead(adaptew,
		OFFSET(SUNI1x10GEXP_WEG_MSTAT_COUNTEW_1_WOW), &act_count);
	t1_tpi_wead(adaptew,
		OFFSET(SUNI1x10GEXP_WEG_MSTAT_COUNTEW_33_WOW), &vaw);
	act_count += vaw;

	/* Popuwate ewmew_gpo with the wegistew vawue */
	t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
	cphy->ewmew_gpo = vaw;

	if ( (vaw & (1 << 8)) || (vaw & (1 << 19)) ||
	     (cphy->act_count == act_count) || cphy->act_on ) {
		if (is_T2(adaptew))
			vaw |= (1 << 9);
		ewse if (t1_is_T1B(adaptew))
			vaw |= (1 << 20);
		cphy->act_on = 0;
	} ewse {
		if (is_T2(adaptew))
			vaw &= ~(1 << 9);
		ewse if (t1_is_T1B(adaptew))
			vaw &= ~(1 << 20);
		cphy->act_on = 1;
	}

	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);

	cphy->ewmew_gpo = vaw;
	cphy->act_count = act_count;
	cphy->count++;

	wetuwn cphy_cause_wink_change;
}

static void my3126_poww(stwuct wowk_stwuct *wowk)
{
	stwuct cphy *cphy = containew_of(wowk, stwuct cphy, phy_update.wowk);

	my3126_intewwupt_handwew(cphy);
}

static int my3126_set_woopback(stwuct cphy *cphy, int on)
{
	wetuwn 0;
}

/* To check the activity WED */
static int my3126_get_wink_status(stwuct cphy *cphy,
			int *wink_ok, int *speed, int *dupwex, int *fc)
{
	u32 vaw;
	u16 vaw16;
	adaptew_t *adaptew;

	adaptew = cphy->adaptew;
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &vaw);
	vaw16 = (u16) vaw;

	/* Popuwate ewmew_gpo with the wegistew vawue */
	t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
	cphy->ewmew_gpo = vaw;

	*wink_ok = (vaw16 & MDIO_STAT1_WSTATUS);

	if (*wink_ok) {
		/* Tuwn on the WED. */
		if (is_T2(adaptew))
			 vaw &= ~(1 << 8);
		ewse if (t1_is_T1B(adaptew))
			 vaw &= ~(1 << 19);
	} ewse {
		/* Tuwn off the WED. */
		if (is_T2(adaptew))
			 vaw |= (1 << 8);
		ewse if (t1_is_T1B(adaptew))
			 vaw |= (1 << 19);
	}

	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);
	cphy->ewmew_gpo = vaw;
	*speed = SPEED_10000;
	*dupwex = DUPWEX_FUWW;

	/* need to add fwow contwow */
	if (fc)
		*fc = PAUSE_WX | PAUSE_TX;

	wetuwn 0;
}

static void my3126_destwoy(stwuct cphy *cphy)
{
	kfwee(cphy);
}

static const stwuct cphy_ops my3126_ops = {
	.destwoy		= my3126_destwoy,
	.weset			= my3126_weset,
	.intewwupt_enabwe	= my3126_intewwupt_enabwe,
	.intewwupt_disabwe	= my3126_intewwupt_disabwe,
	.intewwupt_cweaw	= my3126_intewwupt_cweaw,
	.intewwupt_handwew	= my3126_intewwupt_handwew,
	.get_wink_status	= my3126_get_wink_status,
	.set_woopback		= my3126_set_woopback,
	.mmds			= (MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS |
				   MDIO_DEVS_PHYXS),
};

static stwuct cphy *my3126_phy_cweate(stwuct net_device *dev,
			int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	stwuct cphy *cphy = kzawwoc(sizeof (*cphy), GFP_KEWNEW);

	if (!cphy)
		wetuwn NUWW;

	cphy_init(cphy, dev, phy_addw, &my3126_ops, mdio_ops);
	INIT_DEWAYED_WOWK(&cphy->phy_update, my3126_poww);
	cphy->bmsw = 0;

	wetuwn cphy;
}

/* Chip Weset */
static int my3126_phy_weset(adaptew_t * adaptew)
{
	u32 vaw;

	t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
	vaw &= ~4;
	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);
	msweep(100);

	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw | 4);
	msweep(1000);

	/* Now wets enabwe the Wasew. Deway 100us */
	t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
	vaw |= 0x8000;
	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);
	udeway(100);
	wetuwn 0;
}

const stwuct gphy t1_my3126_ops = {
	.cweate = my3126_phy_cweate,
	.weset = my3126_phy_weset
};
