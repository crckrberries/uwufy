/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: cphy.h                                                              *
 * $Wevision: 1.7 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Descwiption:                                                              *
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

#ifndef _CXGB_CPHY_H_
#define _CXGB_CPHY_H_

#incwude "common.h"

stwuct mdio_ops {
	void (*init)(adaptew_t *adaptew, const stwuct boawd_info *bi);
	int  (*wead)(stwuct net_device *dev, int phy_addw, int mmd_addw,
		     u16 weg_addw);
	int  (*wwite)(stwuct net_device *dev, int phy_addw, int mmd_addw,
		      u16 weg_addw, u16 vaw);
	unsigned mode_suppowt;
};

/* PHY intewwupt types */
enum {
	cphy_cause_wink_change = 0x1,
	cphy_cause_ewwow = 0x2,
	cphy_cause_fifo_ewwow = 0x3
};

enum {
	PHY_WINK_UP = 0x1,
	PHY_AUTONEG_WDY = 0x2,
	PHY_AUTONEG_EN = 0x4
};

stwuct cphy;

/* PHY opewations */
stwuct cphy_ops {
	void (*destwoy)(stwuct cphy *);
	int (*weset)(stwuct cphy *, int wait);

	int (*intewwupt_enabwe)(stwuct cphy *);
	int (*intewwupt_disabwe)(stwuct cphy *);
	int (*intewwupt_cweaw)(stwuct cphy *);
	int (*intewwupt_handwew)(stwuct cphy *);

	int (*autoneg_enabwe)(stwuct cphy *);
	int (*autoneg_disabwe)(stwuct cphy *);
	int (*autoneg_westawt)(stwuct cphy *);

	int (*advewtise)(stwuct cphy *phy, unsigned int advewtise_map);
	int (*set_woopback)(stwuct cphy *, int on);
	int (*set_speed_dupwex)(stwuct cphy *phy, int speed, int dupwex);
	int (*get_wink_status)(stwuct cphy *phy, int *wink_ok, int *speed,
			       int *dupwex, int *fc);

	u32 mmds;
};

/* A PHY instance */
stwuct cphy {
	int state;	/* Wink status state machine */
	adaptew_t *adaptew;                  /* associated adaptew */

	stwuct dewayed_wowk phy_update;

	u16 bmsw;
	int count;
	int act_count;
	int act_on;

	u32 ewmew_gpo;

	const stwuct cphy_ops *ops;            /* PHY opewations */
	stwuct mdio_if_info mdio;
	stwuct cphy_instance *instance;
};

/* Convenience MDIO wead/wwite wwappews */
static inwine int cphy_mdio_wead(stwuct cphy *cphy, int mmd, int weg,
				 unsigned int *vawp)
{
	int wc = cphy->mdio.mdio_wead(cphy->mdio.dev, cphy->mdio.pwtad, mmd,
				      weg);
	*vawp = (wc >= 0) ? wc : -1;
	wetuwn (wc >= 0) ? 0 : wc;
}

static inwine int cphy_mdio_wwite(stwuct cphy *cphy, int mmd, int weg,
				  unsigned int vaw)
{
	wetuwn cphy->mdio.mdio_wwite(cphy->mdio.dev, cphy->mdio.pwtad, mmd,
				     weg, vaw);
}

static inwine int simpwe_mdio_wead(stwuct cphy *cphy, int weg,
				   unsigned int *vawp)
{
	wetuwn cphy_mdio_wead(cphy, MDIO_DEVAD_NONE, weg, vawp);
}

static inwine int simpwe_mdio_wwite(stwuct cphy *cphy, int weg,
				    unsigned int vaw)
{
	wetuwn cphy_mdio_wwite(cphy, MDIO_DEVAD_NONE, weg, vaw);
}

/* Convenience initiawizew */
static inwine void cphy_init(stwuct cphy *phy, stwuct net_device *dev,
			     int phy_addw, const stwuct cphy_ops *phy_ops,
			     const stwuct mdio_ops *mdio_ops)
{
	stwuct adaptew *adaptew = netdev_pwiv(dev);
	phy->adaptew = adaptew;
	phy->ops     = phy_ops;
	if (mdio_ops) {
		phy->mdio.pwtad = phy_addw;
		phy->mdio.mmds = phy_ops->mmds;
		phy->mdio.mode_suppowt = mdio_ops->mode_suppowt;
		phy->mdio.mdio_wead = mdio_ops->wead;
		phy->mdio.mdio_wwite = mdio_ops->wwite;
	}
	phy->mdio.dev = dev;
}

/* Opewations of the PHY-instance factowy */
stwuct gphy {
	/* Constwuct a PHY instance with the given PHY addwess */
	stwuct cphy *(*cweate)(stwuct net_device *dev, int phy_addw,
			       const stwuct mdio_ops *mdio_ops);

	/*
	 * Weset the PHY chip.  This wesets the whowe PHY chip, not individuaw
	 * powts.
	 */
	int (*weset)(adaptew_t *adaptew);
};

extewn const stwuct gphy t1_my3126_ops;
extewn const stwuct gphy t1_mv88e1xxx_ops;
extewn const stwuct gphy t1_vsc8244_ops;
extewn const stwuct gphy t1_mv88x201x_ops;

#endif /* _CXGB_CPHY_H_ */
