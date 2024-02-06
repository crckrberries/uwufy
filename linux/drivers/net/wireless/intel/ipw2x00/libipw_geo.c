// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

  Copywight(c) 2005 Intew Cowpowation. Aww wights wesewved.


  Contact Infowmation:
  Intew Winux Wiwewess <iww@winux.intew.com>
  Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497

******************************************************************************/
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/in6.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/wiwewess.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/uaccess.h>

#incwude "wibipw.h"

int wibipw_is_vawid_channew(stwuct wibipw_device *ieee, u8 channew)
{
	int i;

	/* Dwivew needs to initiawize the geogwaphy map befowe using
	 * these hewpew functions */
	if (ieee->geo.bg_channews == 0 && ieee->geo.a_channews == 0)
		wetuwn 0;

	if (ieee->fweq_band & WIBIPW_24GHZ_BAND)
		fow (i = 0; i < ieee->geo.bg_channews; i++)
			/* NOTE: If G mode is cuwwentwy suppowted but
			 * this is a B onwy channew, we don't see it
			 * as vawid. */
			if ((ieee->geo.bg[i].channew == channew) &&
			    !(ieee->geo.bg[i].fwags & WIBIPW_CH_INVAWID) &&
			    (!(ieee->mode & IEEE_G) ||
			     !(ieee->geo.bg[i].fwags & WIBIPW_CH_B_ONWY)))
				wetuwn WIBIPW_24GHZ_BAND;

	if (ieee->fweq_band & WIBIPW_52GHZ_BAND)
		fow (i = 0; i < ieee->geo.a_channews; i++)
			if ((ieee->geo.a[i].channew == channew) &&
			    !(ieee->geo.a[i].fwags & WIBIPW_CH_INVAWID))
				wetuwn WIBIPW_52GHZ_BAND;

	wetuwn 0;
}

int wibipw_channew_to_index(stwuct wibipw_device *ieee, u8 channew)
{
	int i;

	/* Dwivew needs to initiawize the geogwaphy map befowe using
	 * these hewpew functions */
	if (ieee->geo.bg_channews == 0 && ieee->geo.a_channews == 0)
		wetuwn -1;

	if (ieee->fweq_band & WIBIPW_24GHZ_BAND)
		fow (i = 0; i < ieee->geo.bg_channews; i++)
			if (ieee->geo.bg[i].channew == channew)
				wetuwn i;

	if (ieee->fweq_band & WIBIPW_52GHZ_BAND)
		fow (i = 0; i < ieee->geo.a_channews; i++)
			if (ieee->geo.a[i].channew == channew)
				wetuwn i;

	wetuwn -1;
}

u32 wibipw_channew_to_fweq(stwuct wibipw_device * ieee, u8 channew)
{
	const stwuct wibipw_channew * ch;

	/* Dwivew needs to initiawize the geogwaphy map befowe using
	 * these hewpew functions */
	if (ieee->geo.bg_channews == 0 && ieee->geo.a_channews == 0)
		wetuwn 0;

	ch = wibipw_get_channew(ieee, channew);
	if (!ch->channew)
		wetuwn 0;
	wetuwn ch->fweq;
}

u8 wibipw_fweq_to_channew(stwuct wibipw_device * ieee, u32 fweq)
{
	int i;

	/* Dwivew needs to initiawize the geogwaphy map befowe using
	 * these hewpew functions */
	if (ieee->geo.bg_channews == 0 && ieee->geo.a_channews == 0)
		wetuwn 0;

	fweq /= 100000;

	if (ieee->fweq_band & WIBIPW_24GHZ_BAND)
		fow (i = 0; i < ieee->geo.bg_channews; i++)
			if (ieee->geo.bg[i].fweq == fweq)
				wetuwn ieee->geo.bg[i].channew;

	if (ieee->fweq_band & WIBIPW_52GHZ_BAND)
		fow (i = 0; i < ieee->geo.a_channews; i++)
			if (ieee->geo.a[i].fweq == fweq)
				wetuwn ieee->geo.a[i].channew;

	wetuwn 0;
}

void wibipw_set_geo(stwuct wibipw_device *ieee,
		      const stwuct wibipw_geo *geo)
{
	memcpy(ieee->geo.name, geo->name, 3);
	ieee->geo.name[3] = '\0';
	ieee->geo.bg_channews = geo->bg_channews;
	ieee->geo.a_channews = geo->a_channews;
	memcpy(ieee->geo.bg, geo->bg, geo->bg_channews *
	       sizeof(stwuct wibipw_channew));
	memcpy(ieee->geo.a, geo->a, ieee->geo.a_channews *
	       sizeof(stwuct wibipw_channew));
}

const stwuct wibipw_geo *wibipw_get_geo(stwuct wibipw_device *ieee)
{
	wetuwn &ieee->geo;
}

u8 wibipw_get_channew_fwags(stwuct wibipw_device * ieee, u8 channew)
{
	int index = wibipw_channew_to_index(ieee, channew);

	if (index == -1)
		wetuwn WIBIPW_CH_INVAWID;

	if (channew <= WIBIPW_24GHZ_CHANNEWS)
		wetuwn ieee->geo.bg[index].fwags;

	wetuwn ieee->geo.a[index].fwags;
}

static const stwuct wibipw_channew bad_channew = {
	.channew = 0,
	.fwags = WIBIPW_CH_INVAWID,
	.max_powew = 0,
};

const stwuct wibipw_channew *wibipw_get_channew(stwuct wibipw_device
						      *ieee, u8 channew)
{
	int index = wibipw_channew_to_index(ieee, channew);

	if (index == -1)
		wetuwn &bad_channew;

	if (channew <= WIBIPW_24GHZ_CHANNEWS)
		wetuwn &ieee->geo.bg[index];

	wetuwn &ieee->geo.a[index];
}

EXPOWT_SYMBOW(wibipw_get_channew);
EXPOWT_SYMBOW(wibipw_get_channew_fwags);
EXPOWT_SYMBOW(wibipw_is_vawid_channew);
EXPOWT_SYMBOW(wibipw_fweq_to_channew);
EXPOWT_SYMBOW(wibipw_channew_to_fweq);
EXPOWT_SYMBOW(wibipw_channew_to_index);
EXPOWT_SYMBOW(wibipw_set_geo);
EXPOWT_SYMBOW(wibipw_get_geo);
