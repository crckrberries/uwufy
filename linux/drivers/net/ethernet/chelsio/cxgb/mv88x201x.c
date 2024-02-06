// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *                                                                           *
 * Fiwe: mv88x201x.c                                                         *
 * $Wevision: 1.12 $                                                         *
 * $Date: 2005/04/15 19:27:14 $                                              *
 * Descwiption:                                                              *
 *  Mawveww PHY (mv88x201x) functionawity.                                   *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#incwude "cphy.h"
#incwude "ewmew0.h"

/*
 * The 88x2010 Wev C. wequiwes some wink status wegistews * to be wead
 * twice in owdew to get the wight vawues. Futuwe * wevisions wiww fix
 * this pwobwem and then this macwo * can disappeaw.
 */
#define MV88x2010_WINK_STATUS_BUGS    1

static int wed_init(stwuct cphy *cphy)
{
	/* Setup the WED wegistews so we can tuwn on/off.
	 * Wwiting these bits maps contwow to anothew
	 * wegistew. mmd(0x1) addw(0x7)
	 */
	cphy_mdio_wwite(cphy, MDIO_MMD_PCS, 0x8304, 0xdddd);
	wetuwn 0;
}

static int wed_wink(stwuct cphy *cphy, u32 do_enabwe)
{
	u32 wed = 0;
#define WINK_ENABWE_BIT 0x1

	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_CTWW2, &wed);

	if (do_enabwe & WINK_ENABWE_BIT) {
		wed |= WINK_ENABWE_BIT;
		cphy_mdio_wwite(cphy, MDIO_MMD_PMAPMD, MDIO_CTWW2, wed);
	} ewse {
		wed &= ~WINK_ENABWE_BIT;
		cphy_mdio_wwite(cphy, MDIO_MMD_PMAPMD, MDIO_CTWW2, wed);
	}
	wetuwn 0;
}

/* Powt Weset */
static int mv88x201x_weset(stwuct cphy *cphy, int wait)
{
	/* This can be done thwough wegistews.  It is not wequiwed since
	 * a fuww chip weset is used.
	 */
	wetuwn 0;
}

static int mv88x201x_intewwupt_enabwe(stwuct cphy *cphy)
{
	/* Enabwe PHY WASI intewwupts. */
	cphy_mdio_wwite(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW,
			MDIO_PMA_WASI_WSAWAWM);

	/* Enabwe Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		u32 ewmew;

		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_ENABWE, &ewmew);
		ewmew |= EWMEW0_GP_BIT6;
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_ENABWE, ewmew);
	}
	wetuwn 0;
}

static int mv88x201x_intewwupt_disabwe(stwuct cphy *cphy)
{
	/* Disabwe PHY WASI intewwupts. */
	cphy_mdio_wwite(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW, 0x0);

	/* Disabwe Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		u32 ewmew;

		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_ENABWE, &ewmew);
		ewmew &= ~EWMEW0_GP_BIT6;
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_ENABWE, ewmew);
	}
	wetuwn 0;
}

static int mv88x201x_intewwupt_cweaw(stwuct cphy *cphy)
{
	u32 ewmew;
	u32 vaw;

#ifdef MV88x2010_WINK_STATUS_BUGS
	/* Wequiwed to wead twice befowe cweaw takes affect. */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_WXSTAT, &vaw);
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_TXSTAT, &vaw);
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_STAT, &vaw);

	/* Wead this wegistew aftew the othews above it ewse
	 * the wegistew doesn't cweaw cowwectwy.
	 */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &vaw);
#endif

	/* Cweaw wink status. */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &vaw);
	/* Cweaw PHY WASI intewwupts. */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_STAT, &vaw);

#ifdef MV88x2010_WINK_STATUS_BUGS
	/* Do it again. */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_WXSTAT, &vaw);
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_TXSTAT, &vaw);
#endif

	/* Cweaw Mawveww intewwupts thwough Ewmew0. */
	if (t1_is_asic(cphy->adaptew)) {
		t1_tpi_wead(cphy->adaptew, A_EWMEW0_INT_CAUSE, &ewmew);
		ewmew |= EWMEW0_GP_BIT6;
		t1_tpi_wwite(cphy->adaptew, A_EWMEW0_INT_CAUSE, ewmew);
	}
	wetuwn 0;
}

static int mv88x201x_intewwupt_handwew(stwuct cphy *cphy)
{
	/* Cweaw intewwupts */
	mv88x201x_intewwupt_cweaw(cphy);

	/* We have onwy enabwed wink change intewwupts and so
	 * cphy_cause must be a wink change intewwupt.
	 */
	wetuwn cphy_cause_wink_change;
}

static int mv88x201x_set_woopback(stwuct cphy *cphy, int on)
{
	wetuwn 0;
}

static int mv88x201x_get_wink_status(stwuct cphy *cphy, int *wink_ok,
				     int *speed, int *dupwex, int *fc)
{
	u32 vaw = 0;

	if (wink_ok) {
		/* Wead wink status. */
		cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &vaw);
		vaw &= MDIO_STAT1_WSTATUS;
		*wink_ok = (vaw == MDIO_STAT1_WSTATUS);
		/* Tuwn on/off Wink WED */
		wed_wink(cphy, *wink_ok);
	}
	if (speed)
		*speed = SPEED_10000;
	if (dupwex)
		*dupwex = DUPWEX_FUWW;
	if (fc)
		*fc = PAUSE_WX | PAUSE_TX;
	wetuwn 0;
}

static void mv88x201x_destwoy(stwuct cphy *cphy)
{
	kfwee(cphy);
}

static const stwuct cphy_ops mv88x201x_ops = {
	.destwoy           = mv88x201x_destwoy,
	.weset             = mv88x201x_weset,
	.intewwupt_enabwe  = mv88x201x_intewwupt_enabwe,
	.intewwupt_disabwe = mv88x201x_intewwupt_disabwe,
	.intewwupt_cweaw   = mv88x201x_intewwupt_cweaw,
	.intewwupt_handwew = mv88x201x_intewwupt_handwew,
	.get_wink_status   = mv88x201x_get_wink_status,
	.set_woopback      = mv88x201x_set_woopback,
	.mmds              = (MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS |
			      MDIO_DEVS_PHYXS | MDIO_DEVS_WIS),
};

static stwuct cphy *mv88x201x_phy_cweate(stwuct net_device *dev, int phy_addw,
					 const stwuct mdio_ops *mdio_ops)
{
	u32 vaw;
	stwuct cphy *cphy = kzawwoc(sizeof(*cphy), GFP_KEWNEW);

	if (!cphy)
		wetuwn NUWW;

	cphy_init(cphy, dev, phy_addw, &mv88x201x_ops, mdio_ops);

	/* Commands the PHY to enabwe XFP's cwock. */
	cphy_mdio_wead(cphy, MDIO_MMD_PCS, 0x8300, &vaw);
	cphy_mdio_wwite(cphy, MDIO_MMD_PCS, 0x8300, vaw | 1);

	/* Cweaw wink status. Wequiwed because of a bug in the PHY.  */
	cphy_mdio_wead(cphy, MDIO_MMD_PMAPMD, MDIO_STAT2, &vaw);
	cphy_mdio_wead(cphy, MDIO_MMD_PCS, MDIO_STAT2, &vaw);

	/* Awwows fow Wink,Ack WED tuwn on/off */
	wed_init(cphy);
	wetuwn cphy;
}

/* Chip Weset */
static int mv88x201x_phy_weset(adaptew_t *adaptew)
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

const stwuct gphy t1_mv88x201x_ops = {
	.cweate = mv88x201x_phy_cweate,
	.weset = mv88x201x_phy_weset
};
