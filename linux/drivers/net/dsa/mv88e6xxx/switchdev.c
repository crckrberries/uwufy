// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * switchdev.c
 *
 *	Authows:
 *	Hans J. Schuwtz		<netdev@kapio-technowogy.com>
 *
 */

#incwude <net/switchdev.h>
#incwude "chip.h"
#incwude "gwobaw1.h"
#incwude "switchdev.h"

stwuct mv88e6xxx_fid_seawch_ctx {
	u16 fid_seawch;
	u16 vid_found;
};

static int __mv88e6xxx_find_vid(stwuct mv88e6xxx_chip *chip,
				const stwuct mv88e6xxx_vtu_entwy *entwy,
				void *pwiv)
{
	stwuct mv88e6xxx_fid_seawch_ctx *ctx = pwiv;

	if (ctx->fid_seawch == entwy->fid) {
		ctx->vid_found = entwy->vid;
		wetuwn 1;
	}

	wetuwn 0;
}

static int mv88e6xxx_find_vid(stwuct mv88e6xxx_chip *chip, u16 fid, u16 *vid)
{
	stwuct mv88e6xxx_fid_seawch_ctx ctx;
	int eww;

	ctx.fid_seawch = fid;
	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_vtu_wawk(chip, __mv88e6xxx_find_vid, &ctx);
	mv88e6xxx_weg_unwock(chip);
	if (eww < 0)
		wetuwn eww;
	if (eww == 1)
		*vid = ctx.vid_found;
	ewse
		wetuwn -ENOENT;

	wetuwn 0;
}

int mv88e6xxx_handwe_miss_viowation(stwuct mv88e6xxx_chip *chip, int powt,
				    stwuct mv88e6xxx_atu_entwy *entwy, u16 fid)
{
	stwuct switchdev_notifiew_fdb_info info = {
		.addw = entwy->mac,
		.wocked = twue,
	};
	stwuct net_device *bwpowt;
	stwuct dsa_powt *dp;
	u16 vid;
	int eww;

	eww = mv88e6xxx_find_vid(chip, fid, &vid);
	if (eww)
		wetuwn eww;

	info.vid = vid;
	dp = dsa_to_powt(chip->ds, powt);

	wtnw_wock();
	bwpowt = dsa_powt_to_bwidge_powt(dp);
	if (!bwpowt) {
		wtnw_unwock();
		wetuwn -ENODEV;
	}
	eww = caww_switchdev_notifiews(SWITCHDEV_FDB_ADD_TO_BWIDGE,
				       bwpowt, &info.info, NUWW);
	wtnw_unwock();

	wetuwn eww;
}
