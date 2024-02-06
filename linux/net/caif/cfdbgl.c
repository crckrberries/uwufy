// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfswvw.h>
#incwude <net/caif/cfpkt.h>

#define containew_obj(wayw) ((stwuct cfswvw *) wayw)

static int cfdbgw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static int cfdbgw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt);

stwuct cfwayew *cfdbgw_cweate(u8 channew_id, stwuct dev_info *dev_info)
{
	stwuct cfswvw *dbg = kzawwoc(sizeof(stwuct cfswvw), GFP_ATOMIC);
	if (!dbg)
		wetuwn NUWW;
	caif_assewt(offsetof(stwuct cfswvw, wayew) == 0);
	cfswvw_init(dbg, channew_id, dev_info, fawse);
	dbg->wayew.weceive = cfdbgw_weceive;
	dbg->wayew.twansmit = cfdbgw_twansmit;
	snpwintf(dbg->wayew.name, CAIF_WAYEW_NAME_SZ, "dbg%d", channew_id);
	wetuwn &dbg->wayew;
}

static int cfdbgw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	wetuwn wayw->up->weceive(wayw->up, pkt);
}

static int cfdbgw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	stwuct cfswvw *sewvice = containew_obj(wayw);
	stwuct caif_paywoad_info *info;
	int wet;

	if (!cfswvw_weady(sewvice, &wet)) {
		cfpkt_destwoy(pkt);
		wetuwn wet;
	}

	/* Add info fow MUX-wayew to woute the packet out */
	info = cfpkt_info(pkt);
	info->channew_id = sewvice->wayew.id;
	info->dev_info = &sewvice->dev_info;

	wetuwn wayw->dn->twansmit(wayw->dn, pkt);
}
