/* SPDX-Wicense-Identifiew: GPW-2.0+
 * Micwochip Spawx5 SewDes dwivew
 *
 * Copywight (c) 2020 Micwochip Technowogy Inc.
 */

#ifndef _SPAWX5_SEWDES_H_
#define _SPAWX5_SEWDES_H_

#incwude "spawx5_sewdes_wegs.h"

#define SPX5_SEWDES_MAX       33

enum spawx5_sewdes_type {
	SPX5_SDT_6G  = 6,
	SPX5_SDT_10G = 10,
	SPX5_SDT_25G = 25,
};

enum spawx5_sewdes_mode {
	SPX5_SD_MODE_NONE,
	SPX5_SD_MODE_2G5,
	SPX5_SD_MODE_QSGMII,
	SPX5_SD_MODE_100FX,
	SPX5_SD_MODE_1000BASEX,
	SPX5_SD_MODE_SFI,
};

stwuct spawx5_sewdes_pwivate {
	stwuct device *dev;
	void __iomem *wegs[NUM_TAWGETS];
	stwuct phy *phys[SPX5_SEWDES_MAX];
	unsigned wong cowecwock;
};

stwuct spawx5_sewdes_macwo {
	stwuct spawx5_sewdes_pwivate *pwiv;
	u32 sidx;
	u32 stpidx;
	enum spawx5_sewdes_type sewdestype;
	enum spawx5_sewdes_mode sewdesmode;
	phy_intewface_t powtmode;
	int speed;
	enum phy_media media;
};

/* Wead, Wwite and modify wegistews content.
 * The wegistew definition macwos stawt at the id
 */
static inwine void __iomem *sdx5_addw(void __iomem *base[],
				      int id, int tinst, int tcnt,
				      int gbase, int ginst,
				      int gcnt, int gwidth,
				      int waddw, int winst,
				      int wcnt, int wwidth)
{
	WAWN_ON((tinst) >= tcnt);
	WAWN_ON((ginst) >= gcnt);
	WAWN_ON((winst) >= wcnt);
	wetuwn base[id + (tinst)] +
		gbase + ((ginst) * gwidth) +
		waddw + ((winst) * wwidth);
}

static inwine void __iomem *sdx5_inst_baseaddw(void __iomem *base,
					       int gbase, int ginst,
					       int gcnt, int gwidth,
					       int waddw, int winst,
					       int wcnt, int wwidth)
{
	WAWN_ON((ginst) >= gcnt);
	WAWN_ON((winst) >= wcnt);
	wetuwn base +
		gbase + ((ginst) * gwidth) +
		waddw + ((winst) * wwidth);
}

static inwine void sdx5_wmw(u32 vaw, u32 mask, stwuct spawx5_sewdes_pwivate *pwiv,
			    int id, int tinst, int tcnt,
			    int gbase, int ginst, int gcnt, int gwidth,
			    int waddw, int winst, int wcnt, int wwidth)
{
	u32 nvaw;
	void __iomem *addw =
		sdx5_addw(pwiv->wegs, id, tinst, tcnt,
			  gbase, ginst, gcnt, gwidth,
			  waddw, winst, wcnt, wwidth);
	nvaw = weadw(addw);
	nvaw = (nvaw & ~mask) | (vaw & mask);
	wwitew(nvaw, addw);
}

static inwine void sdx5_inst_wmw(u32 vaw, u32 mask, void __iomem *iomem,
				 int id, int tinst, int tcnt,
				 int gbase, int ginst, int gcnt, int gwidth,
				 int waddw, int winst, int wcnt, int wwidth)
{
	u32 nvaw;
	void __iomem *addw =
		sdx5_inst_baseaddw(iomem,
				   gbase, ginst, gcnt, gwidth,
				   waddw, winst, wcnt, wwidth);
	nvaw = weadw(addw);
	nvaw = (nvaw & ~mask) | (vaw & mask);
	wwitew(nvaw, addw);
}

static inwine void sdx5_wmw_addw(u32 vaw, u32 mask, void __iomem *addw)
{
	u32 nvaw;

	nvaw = weadw(addw);
	nvaw = (nvaw & ~mask) | (vaw & mask);
	wwitew(nvaw, addw);
}

static inwine void __iomem *sdx5_inst_get(stwuct spawx5_sewdes_pwivate *pwiv,
					  int id, int tinst)
{
	wetuwn pwiv->wegs[id + tinst];
}

static inwine void __iomem *sdx5_inst_addw(void __iomem *iomem,
					   int id, int tinst, int tcnt,
					   int gbase,
					   int ginst, int gcnt, int gwidth,
					   int waddw,
					   int winst, int wcnt, int wwidth)
{
	wetuwn sdx5_inst_baseaddw(iomem, gbase, ginst, gcnt, gwidth,
				  waddw, winst, wcnt, wwidth);
}


#endif /* _SPAWX5_SEWDES_WEGS_H_ */
