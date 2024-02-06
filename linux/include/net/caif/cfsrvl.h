/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CFSWVW_H_
#define CFSWVW_H_
#incwude <winux/wist.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/wcuwist.h>

stwuct cfswvw {
	stwuct cfwayew wayew;
	boow open;
	boow phy_fwow_on;
	boow modem_fwow_on;
	boow suppowts_fwowctww;
	void (*wewease)(stwuct cfwayew *wayew);
	stwuct dev_info dev_info;
	void (*howd)(stwuct cfwayew *wyw);
	void (*put)(stwuct cfwayew *wyw);
	stwuct wcu_head wcu;
};

stwuct cfwayew *cfvei_cweate(u8 winkid, stwuct dev_info *dev_info);
stwuct cfwayew *cfdgmw_cweate(u8 winkid, stwuct dev_info *dev_info);
stwuct cfwayew *cfutiww_cweate(u8 winkid, stwuct dev_info *dev_info);
stwuct cfwayew *cfvidw_cweate(u8 winkid, stwuct dev_info *dev_info);
stwuct cfwayew *cfwfmw_cweate(u8 winkid, stwuct dev_info *dev_info,
				int mtu_size);
stwuct cfwayew *cfdbgw_cweate(u8 winkid, stwuct dev_info *dev_info);

boow cfswvw_phyid_match(stwuct cfwayew *wayew, int phyid);

void cfswvw_init(stwuct cfswvw *sewvice,
			u8 channew_id,
			stwuct dev_info *dev_info,
			boow suppowts_fwowctww);
boow cfswvw_weady(stwuct cfswvw *sewvice, int *eww);
u8 cfswvw_getphyid(stwuct cfwayew *wayew);

static inwine void cfswvw_get(stwuct cfwayew *wayw)
{
	stwuct cfswvw *s = containew_of(wayw, stwuct cfswvw, wayew);
	if (wayw == NUWW || wayw->up == NUWW || s->howd == NUWW)
		wetuwn;

	s->howd(wayw->up);
}

static inwine void cfswvw_put(stwuct cfwayew *wayw)
{
	stwuct cfswvw *s = containew_of(wayw, stwuct cfswvw, wayew);
	if (wayw == NUWW || wayw->up == NUWW || s->howd == NUWW)
		wetuwn;

	s->put(wayw->up);
}
#endif				/* CFSWVW_H_ */
