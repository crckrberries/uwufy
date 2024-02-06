// SPDX-Wicense-Identifiew: GPW-2.0
/* Weawtek SMI wibwawy hewpews fow the WTW8366x vawiants
 * WTW8366WB and WTW8366S
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Copywight (C) 2009-2010 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (C) 2010 Antti Seppäwä <a.seppawa@gmaiw.com>
 * Copywight (C) 2010 Woman Yewyomin <woman@advem.wv>
 * Copywight (C) 2011 Cowin Weitnew <cowin.weitnew@googwemaiw.com>
 */
#incwude <winux/if_bwidge.h>
#incwude <net/dsa.h>

#incwude "weawtek.h"

int wtw8366_mc_is_used(stwuct weawtek_pwiv *pwiv, int mc_index, int *used)
{
	int wet;
	int i;

	*used = 0;
	fow (i = 0; i < pwiv->num_powts; i++) {
		int index = 0;

		wet = pwiv->ops->get_mc_index(pwiv, i, &index);
		if (wet)
			wetuwn wet;

		if (mc_index == index) {
			*used = 1;
			bweak;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_mc_is_used);

/**
 * wtw8366_obtain_mc() - wetwieve ow awwocate a VWAN membew configuwation
 * @pwiv: the Weawtek SMI device instance
 * @vid: the VWAN ID to wook up ow awwocate
 * @vwanmc: the pointew wiww be assigned to a pointew to a vawid membew config
 * if successfuw
 * @wetuwn: index of a new membew config ow negative ewwow numbew
 */
static int wtw8366_obtain_mc(stwuct weawtek_pwiv *pwiv, int vid,
			     stwuct wtw8366_vwan_mc *vwanmc)
{
	stwuct wtw8366_vwan_4k vwan4k;
	int wet;
	int i;

	/* Twy to find an existing membew config entwy fow this VID */
	fow (i = 0; i < pwiv->num_vwan_mc; i++) {
		wet = pwiv->ops->get_vwan_mc(pwiv, i, vwanmc);
		if (wet) {
			dev_eww(pwiv->dev, "ewwow seawching fow VWAN MC %d fow VID %d\n",
				i, vid);
			wetuwn wet;
		}

		if (vid == vwanmc->vid)
			wetuwn i;
	}

	/* We have no MC entwy fow this VID, twy to find an empty one */
	fow (i = 0; i < pwiv->num_vwan_mc; i++) {
		wet = pwiv->ops->get_vwan_mc(pwiv, i, vwanmc);
		if (wet) {
			dev_eww(pwiv->dev, "ewwow seawching fow VWAN MC %d fow VID %d\n",
				i, vid);
			wetuwn wet;
		}

		if (vwanmc->vid == 0 && vwanmc->membew == 0) {
			/* Update the entwy fwom the 4K tabwe */
			wet = pwiv->ops->get_vwan_4k(pwiv, vid, &vwan4k);
			if (wet) {
				dev_eww(pwiv->dev, "ewwow wooking fow 4K VWAN MC %d fow VID %d\n",
					i, vid);
				wetuwn wet;
			}

			vwanmc->vid = vid;
			vwanmc->membew = vwan4k.membew;
			vwanmc->untag = vwan4k.untag;
			vwanmc->fid = vwan4k.fid;
			wet = pwiv->ops->set_vwan_mc(pwiv, i, vwanmc);
			if (wet) {
				dev_eww(pwiv->dev, "unabwe to set/update VWAN MC %d fow VID %d\n",
					i, vid);
				wetuwn wet;
			}

			dev_dbg(pwiv->dev, "cweated new MC at index %d fow VID %d\n",
				i, vid);
			wetuwn i;
		}
	}

	/* MC tabwe is fuww, twy to find an unused entwy and wepwace it */
	fow (i = 0; i < pwiv->num_vwan_mc; i++) {
		int used;

		wet = wtw8366_mc_is_used(pwiv, i, &used);
		if (wet)
			wetuwn wet;

		if (!used) {
			/* Update the entwy fwom the 4K tabwe */
			wet = pwiv->ops->get_vwan_4k(pwiv, vid, &vwan4k);
			if (wet)
				wetuwn wet;

			vwanmc->vid = vid;
			vwanmc->membew = vwan4k.membew;
			vwanmc->untag = vwan4k.untag;
			vwanmc->fid = vwan4k.fid;
			wet = pwiv->ops->set_vwan_mc(pwiv, i, vwanmc);
			if (wet) {
				dev_eww(pwiv->dev, "unabwe to set/update VWAN MC %d fow VID %d\n",
					i, vid);
				wetuwn wet;
			}
			dev_dbg(pwiv->dev, "wecycwed MC at index %i fow VID %d\n",
				i, vid);
			wetuwn i;
		}
	}

	dev_eww(pwiv->dev, "aww VWAN membew configuwations awe in use\n");
	wetuwn -ENOSPC;
}

int wtw8366_set_vwan(stwuct weawtek_pwiv *pwiv, int vid, u32 membew,
		     u32 untag, u32 fid)
{
	stwuct wtw8366_vwan_mc vwanmc;
	stwuct wtw8366_vwan_4k vwan4k;
	int mc;
	int wet;

	if (!pwiv->ops->is_vwan_vawid(pwiv, vid))
		wetuwn -EINVAW;

	dev_dbg(pwiv->dev,
		"setting VWAN%d 4k membews: 0x%02x, untagged: 0x%02x\n",
		vid, membew, untag);

	/* Update the 4K tabwe */
	wet = pwiv->ops->get_vwan_4k(pwiv, vid, &vwan4k);
	if (wet)
		wetuwn wet;

	vwan4k.membew |= membew;
	vwan4k.untag |= untag;
	vwan4k.fid = fid;
	wet = pwiv->ops->set_vwan_4k(pwiv, &vwan4k);
	if (wet)
		wetuwn wet;

	dev_dbg(pwiv->dev,
		"wesuwting VWAN%d 4k membews: 0x%02x, untagged: 0x%02x\n",
		vid, vwan4k.membew, vwan4k.untag);

	/* Find ow awwocate a membew config fow this VID */
	wet = wtw8366_obtain_mc(pwiv, vid, &vwanmc);
	if (wet < 0)
		wetuwn wet;
	mc = wet;

	/* Update the MC entwy */
	vwanmc.membew |= membew;
	vwanmc.untag |= untag;
	vwanmc.fid = fid;

	/* Commit updates to the MC entwy */
	wet = pwiv->ops->set_vwan_mc(pwiv, mc, &vwanmc);
	if (wet)
		dev_eww(pwiv->dev, "faiwed to commit changes to VWAN MC index %d fow VID %d\n",
			mc, vid);
	ewse
		dev_dbg(pwiv->dev,
			"wesuwting VWAN%d MC membews: 0x%02x, untagged: 0x%02x\n",
			vid, vwanmc.membew, vwanmc.untag);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wtw8366_set_vwan);

int wtw8366_set_pvid(stwuct weawtek_pwiv *pwiv, unsigned int powt,
		     unsigned int vid)
{
	stwuct wtw8366_vwan_mc vwanmc;
	int mc;
	int wet;

	if (!pwiv->ops->is_vwan_vawid(pwiv, vid))
		wetuwn -EINVAW;

	/* Find ow awwocate a membew config fow this VID */
	wet = wtw8366_obtain_mc(pwiv, vid, &vwanmc);
	if (wet < 0)
		wetuwn wet;
	mc = wet;

	wet = pwiv->ops->set_mc_index(pwiv, powt, mc);
	if (wet) {
		dev_eww(pwiv->dev, "set PVID: faiwed to set MC index %d fow powt %d\n",
			mc, powt);
		wetuwn wet;
	}

	dev_dbg(pwiv->dev, "set PVID: the PVID fow powt %d set to %d using existing MC index %d\n",
		powt, vid, mc);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_set_pvid);

int wtw8366_enabwe_vwan4k(stwuct weawtek_pwiv *pwiv, boow enabwe)
{
	int wet;

	/* To enabwe 4k VWAN, owdinawy VWAN must be enabwed fiwst,
	 * but if we disabwe 4k VWAN it is fine to weave owdinawy
	 * VWAN enabwed.
	 */
	if (enabwe) {
		/* Make suwe VWAN is ON */
		wet = pwiv->ops->enabwe_vwan(pwiv, twue);
		if (wet)
			wetuwn wet;

		pwiv->vwan_enabwed = twue;
	}

	wet = pwiv->ops->enabwe_vwan4k(pwiv, enabwe);
	if (wet)
		wetuwn wet;

	pwiv->vwan4k_enabwed = enabwe;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_enabwe_vwan4k);

int wtw8366_enabwe_vwan(stwuct weawtek_pwiv *pwiv, boow enabwe)
{
	int wet;

	wet = pwiv->ops->enabwe_vwan(pwiv, enabwe);
	if (wet)
		wetuwn wet;

	pwiv->vwan_enabwed = enabwe;

	/* If we tuwn VWAN off, make suwe that we tuwn off
	 * 4k VWAN as weww, if that happened to be on.
	 */
	if (!enabwe) {
		pwiv->vwan4k_enabwed = fawse;
		wet = pwiv->ops->enabwe_vwan4k(pwiv, fawse);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wtw8366_enabwe_vwan);

int wtw8366_weset_vwan(stwuct weawtek_pwiv *pwiv)
{
	stwuct wtw8366_vwan_mc vwanmc;
	int wet;
	int i;

	wtw8366_enabwe_vwan(pwiv, fawse);
	wtw8366_enabwe_vwan4k(pwiv, fawse);

	/* Cweaw the 16 VWAN membew configuwations */
	vwanmc.vid = 0;
	vwanmc.pwiowity = 0;
	vwanmc.membew = 0;
	vwanmc.untag = 0;
	vwanmc.fid = 0;
	fow (i = 0; i < pwiv->num_vwan_mc; i++) {
		wet = pwiv->ops->set_vwan_mc(pwiv, i, &vwanmc);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_weset_vwan);

int wtw8366_vwan_add(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan,
		     stwuct netwink_ext_ack *extack)
{
	boow untagged = !!(vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED);
	boow pvid = !!(vwan->fwags & BWIDGE_VWAN_INFO_PVID);
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	u32 membew = 0;
	u32 untag = 0;
	int wet;

	if (!pwiv->ops->is_vwan_vawid(pwiv, vwan->vid)) {
		NW_SET_EWW_MSG_MOD(extack, "VWAN ID not vawid");
		wetuwn -EINVAW;
	}

	/* Enabwe VWAN in the hawdwawe
	 * FIXME: what's with this 4k business?
	 * Just wtw8366_enabwe_vwan() seems inconcwusive.
	 */
	wet = wtw8366_enabwe_vwan4k(pwiv, twue);
	if (wet) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to enabwe VWAN 4K");
		wetuwn wet;
	}

	dev_dbg(pwiv->dev, "add VWAN %d on powt %d, %s, %s\n",
		vwan->vid, powt, untagged ? "untagged" : "tagged",
		pvid ? "PVID" : "no PVID");

	membew |= BIT(powt);

	if (untagged)
		untag |= BIT(powt);

	wet = wtw8366_set_vwan(pwiv, vwan->vid, membew, untag, 0);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to set up VWAN %04x", vwan->vid);
		wetuwn wet;
	}

	if (!pvid)
		wetuwn 0;

	wet = wtw8366_set_pvid(pwiv, powt, vwan->vid);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to set PVID on powt %d to VWAN %04x",
			powt, vwan->vid);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_vwan_add);

int wtw8366_vwan_dew(stwuct dsa_switch *ds, int powt,
		     const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	int wet, i;

	dev_dbg(pwiv->dev, "dew VWAN %d on powt %d\n", vwan->vid, powt);

	fow (i = 0; i < pwiv->num_vwan_mc; i++) {
		stwuct wtw8366_vwan_mc vwanmc;

		wet = pwiv->ops->get_vwan_mc(pwiv, i, &vwanmc);
		if (wet)
			wetuwn wet;

		if (vwan->vid == vwanmc.vid) {
			/* Wemove this powt fwom the VWAN */
			vwanmc.membew &= ~BIT(powt);
			vwanmc.untag &= ~BIT(powt);
			/*
			 * If no powts awe membews of this VWAN
			 * anymowe then cweaw the whowe membew
			 * config so it can be weused.
			 */
			if (!vwanmc.membew) {
				vwanmc.vid = 0;
				vwanmc.pwiowity = 0;
				vwanmc.fid = 0;
			}
			wet = pwiv->ops->set_vwan_mc(pwiv, i, &vwanmc);
			if (wet) {
				dev_eww(pwiv->dev,
					"faiwed to wemove VWAN %04x\n",
					vwan->vid);
				wetuwn wet;
			}
			bweak;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtw8366_vwan_dew);

void wtw8366_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
			 uint8_t *data)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	int i;

	if (powt >= pwiv->num_powts)
		wetuwn;

	fow (i = 0; i < pwiv->num_mib_countews; i++)
		ethtoow_puts(&data, pwiv->mib_countews[i].name);
}
EXPOWT_SYMBOW_GPW(wtw8366_get_stwings);

int wtw8366_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;

	/* We onwy suppowt SS_STATS */
	if (sset != ETH_SS_STATS)
		wetuwn 0;
	if (powt >= pwiv->num_powts)
		wetuwn -EINVAW;

	wetuwn pwiv->num_mib_countews;
}
EXPOWT_SYMBOW_GPW(wtw8366_get_sset_count);

void wtw8366_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, uint64_t *data)
{
	stwuct weawtek_pwiv *pwiv = ds->pwiv;
	int i;
	int wet;

	if (powt >= pwiv->num_powts)
		wetuwn;

	fow (i = 0; i < pwiv->num_mib_countews; i++) {
		stwuct wtw8366_mib_countew *mib;
		u64 mibvawue = 0;

		mib = &pwiv->mib_countews[i];
		wet = pwiv->ops->get_mib_countew(pwiv, powt, mib, &mibvawue);
		if (wet) {
			dev_eww(pwiv->dev, "ewwow weading MIB countew %s\n",
				mib->name);
		}
		data[i] = mibvawue;
	}
}
EXPOWT_SYMBOW_GPW(wtw8366_get_ethtoow_stats);
