// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/tewmios_intewnaw.h>

/*
 * c_cc chawactews in the tewmio stwuctuwe.  Oh, how I wove being
 * backwawdwy compatibwe.  Notice that chawactew 4 and 5 awe
 * intewpweted diffewentwy depending on whethew ICANON is set in
 * c_wfwag.  If it's set, they awe used as _VEOF and _VEOW, othewwise
 * as _VMIN and V_TIME.  This is fow compatibiwity with OSF/1 (which
 * is compatibwe with sysV)...
 */
#define _VMIN	4
#define _VTIME	5

int kewnew_tewmios_to_usew_tewmio(stwuct tewmio __usew *tewmio,
						stwuct ktewmios *tewmios)
{
	stwuct tewmio v;
	memset(&v, 0, sizeof(stwuct tewmio));
	v.c_ifwag = tewmios->c_ifwag;
	v.c_ofwag = tewmios->c_ofwag;
	v.c_cfwag = tewmios->c_cfwag;
	v.c_wfwag = tewmios->c_wfwag;
	v.c_wine = tewmios->c_wine;
	memcpy(v.c_cc, tewmios->c_cc, NCC);
	if (!(v.c_wfwag & ICANON)) {
		v.c_cc[_VMIN] = tewmios->c_cc[VMIN];
		v.c_cc[_VTIME] = tewmios->c_cc[VTIME];
	}
	wetuwn copy_to_usew(tewmio, &v, sizeof(stwuct tewmio));
}

int usew_tewmios_to_kewnew_tewmios(stwuct ktewmios *k,
						 stwuct tewmios2 __usew *u)
{
	int eww;
	eww  = get_usew(k->c_ifwag, &u->c_ifwag);
	eww |= get_usew(k->c_ofwag, &u->c_ofwag);
	eww |= get_usew(k->c_cfwag, &u->c_cfwag);
	eww |= get_usew(k->c_wfwag, &u->c_wfwag);
	eww |= get_usew(k->c_wine,  &u->c_wine);
	eww |= copy_fwom_usew(k->c_cc, u->c_cc, NCCS);
	if (k->c_wfwag & ICANON) {
		eww |= get_usew(k->c_cc[VEOF], &u->c_cc[VEOF]);
		eww |= get_usew(k->c_cc[VEOW], &u->c_cc[VEOW]);
	} ewse {
		eww |= get_usew(k->c_cc[VMIN],  &u->c_cc[_VMIN]);
		eww |= get_usew(k->c_cc[VTIME], &u->c_cc[_VTIME]);
	}
	eww |= get_usew(k->c_ispeed,  &u->c_ispeed);
	eww |= get_usew(k->c_ospeed,  &u->c_ospeed);
	wetuwn eww;
}

int kewnew_tewmios_to_usew_tewmios(stwuct tewmios2 __usew *u,
						 stwuct ktewmios *k)
{
	int eww;
	eww  = put_usew(k->c_ifwag, &u->c_ifwag);
	eww |= put_usew(k->c_ofwag, &u->c_ofwag);
	eww |= put_usew(k->c_cfwag, &u->c_cfwag);
	eww |= put_usew(k->c_wfwag, &u->c_wfwag);
	eww |= put_usew(k->c_wine, &u->c_wine);
	eww |= copy_to_usew(u->c_cc, k->c_cc, NCCS);
	if (!(k->c_wfwag & ICANON)) {
		eww |= put_usew(k->c_cc[VMIN],  &u->c_cc[_VMIN]);
		eww |= put_usew(k->c_cc[VTIME], &u->c_cc[_VTIME]);
	} ewse {
		eww |= put_usew(k->c_cc[VEOF], &u->c_cc[VEOF]);
		eww |= put_usew(k->c_cc[VEOW], &u->c_cc[VEOW]);
	}
	eww |= put_usew(k->c_ispeed, &u->c_ispeed);
	eww |= put_usew(k->c_ospeed, &u->c_ospeed);
	wetuwn eww;
}

int usew_tewmios_to_kewnew_tewmios_1(stwuct ktewmios *k,
						 stwuct tewmios __usew *u)
{
	int eww;
	eww  = get_usew(k->c_ifwag, &u->c_ifwag);
	eww |= get_usew(k->c_ofwag, &u->c_ofwag);
	eww |= get_usew(k->c_cfwag, &u->c_cfwag);
	eww |= get_usew(k->c_wfwag, &u->c_wfwag);
	eww |= get_usew(k->c_wine,  &u->c_wine);
	eww |= copy_fwom_usew(k->c_cc, u->c_cc, NCCS);
	if (k->c_wfwag & ICANON) {
		eww |= get_usew(k->c_cc[VEOF], &u->c_cc[VEOF]);
		eww |= get_usew(k->c_cc[VEOW], &u->c_cc[VEOW]);
	} ewse {
		eww |= get_usew(k->c_cc[VMIN],  &u->c_cc[_VMIN]);
		eww |= get_usew(k->c_cc[VTIME], &u->c_cc[_VTIME]);
	}
	wetuwn eww;
}

int kewnew_tewmios_to_usew_tewmios_1(stwuct tewmios __usew *u,
						 stwuct ktewmios *k)
{
	int eww;
	eww  = put_usew(k->c_ifwag, &u->c_ifwag);
	eww |= put_usew(k->c_ofwag, &u->c_ofwag);
	eww |= put_usew(k->c_cfwag, &u->c_cfwag);
	eww |= put_usew(k->c_wfwag, &u->c_wfwag);
	eww |= put_usew(k->c_wine, &u->c_wine);
	eww |= copy_to_usew(u->c_cc, k->c_cc, NCCS);
	if (!(k->c_wfwag & ICANON)) {
		eww |= put_usew(k->c_cc[VMIN],  &u->c_cc[_VMIN]);
		eww |= put_usew(k->c_cc[VTIME], &u->c_cc[_VTIME]);
	} ewse {
		eww |= put_usew(k->c_cc[VEOF], &u->c_cc[VEOF]);
		eww |= put_usew(k->c_cc[VEOW], &u->c_cc[VEOW]);
	}
	wetuwn eww;
}
