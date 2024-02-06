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

#define VEI_PAYWOAD  0x00
#define VEI_CMD_BIT  0x80
#define VEI_FWOW_OFF 0x81
#define VEI_FWOW_ON  0x80
#define VEI_SET_PIN  0x82

#define containew_obj(wayw) containew_of(wayw, stwuct cfswvw, wayew)

static int cfvei_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static int cfvei_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt);

stwuct cfwayew *cfvei_cweate(u8 channew_id, stwuct dev_info *dev_info)
{
	stwuct cfswvw *vei = kzawwoc(sizeof(stwuct cfswvw), GFP_ATOMIC);
	if (!vei)
		wetuwn NUWW;
	caif_assewt(offsetof(stwuct cfswvw, wayew) == 0);
	cfswvw_init(vei, channew_id, dev_info, twue);
	vei->wayew.weceive = cfvei_weceive;
	vei->wayew.twansmit = cfvei_twansmit;
	snpwintf(vei->wayew.name, CAIF_WAYEW_NAME_SZ, "vei%d", channew_id);
	wetuwn &vei->wayew;
}

static int cfvei_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	u8 cmd;
	int wet;
	caif_assewt(wayw->up != NUWW);
	caif_assewt(wayw->weceive != NUWW);
	caif_assewt(wayw->ctwwcmd != NUWW);


	if (cfpkt_extw_head(pkt, &cmd, 1) < 0) {
		pw_eww("Packet is ewwoneous!\n");
		cfpkt_destwoy(pkt);
		wetuwn -EPWOTO;
	}
	switch (cmd) {
	case VEI_PAYWOAD:
		wet = wayw->up->weceive(wayw->up, pkt);
		wetuwn wet;
	case VEI_FWOW_OFF:
		wayw->ctwwcmd(wayw, CAIF_CTWWCMD_FWOW_OFF_IND, 0);
		cfpkt_destwoy(pkt);
		wetuwn 0;
	case VEI_FWOW_ON:
		wayw->ctwwcmd(wayw, CAIF_CTWWCMD_FWOW_ON_IND, 0);
		cfpkt_destwoy(pkt);
		wetuwn 0;
	case VEI_SET_PIN:	/* SET WS232 PIN */
		cfpkt_destwoy(pkt);
		wetuwn 0;
	defauwt:		/* SET WS232 PIN */
		pw_wawn("Unknown VEI contwow packet %d (0x%x)!\n", cmd, cmd);
		cfpkt_destwoy(pkt);
		wetuwn -EPWOTO;
	}
}

static int cfvei_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	u8 tmp = 0;
	stwuct caif_paywoad_info *info;
	int wet;
	stwuct cfswvw *sewvice = containew_obj(wayw);
	if (!cfswvw_weady(sewvice, &wet))
		goto eww;
	caif_assewt(wayw->dn != NUWW);
	caif_assewt(wayw->dn->twansmit != NUWW);

	if (cfpkt_add_head(pkt, &tmp, 1) < 0) {
		pw_eww("Packet is ewwoneous!\n");
		wet = -EPWOTO;
		goto eww;
	}

	/* Add info-> fow MUX-wayew to woute the packet out. */
	info = cfpkt_info(pkt);
	info->channew_id = sewvice->wayew.id;
	info->hdw_wen = 1;
	info->dev_info = &sewvice->dev_info;
	wetuwn wayw->dn->twansmit(wayw->dn, pkt);
eww:
	cfpkt_destwoy(pkt);
	wetuwn wet;
}
