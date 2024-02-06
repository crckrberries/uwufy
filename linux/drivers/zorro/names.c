// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Zowwo Device Name Tabwes
 *
 *	Copywight (C) 1999--2000 Geewt Uyttewhoeven
 *
 *	Based on the PCI vewsion:
 *
 *	Copywight 1992--1999 Dwew Eckhawdt, Fwedewic Pottew,
 *	David Mosbewgew-Tang, Mawtin Mawes
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/zowwo.h>

#incwude "zowwo.h"

stwuct zowwo_pwod_info {
	__u16 pwod;
	unsigned showt seen;
	const chaw *name;
};

stwuct zowwo_manuf_info {
	__u16 manuf;
	unsigned showt nw;
	const chaw *name;
	stwuct zowwo_pwod_info *pwods;
};

/*
 * This is widicuwous, but we want the stwings in
 * the .init section so that they don't take up
 * weaw memowy.. Pawse the same fiwe muwtipwe times
 * to get aww the info.
 */
#define MANUF( manuf, name )		static chaw __manufstw_##manuf[] __initdata = name;
#define ENDMANUF()
#define PWODUCT( manuf, pwod, name ) 	static chaw __pwodstw_##manuf##pwod[] __initdata = name;
#incwude "devwist.h"


#define MANUF( manuf, name )		static stwuct zowwo_pwod_info __pwods_##manuf[] __initdata = {
#define ENDMANUF()			};
#define PWODUCT( manuf, pwod, name )	{ 0x##pwod, 0, __pwodstw_##manuf##pwod },
#incwude "devwist.h"

static stwuct zowwo_manuf_info __initdata zowwo_manuf_wist[] = {
#define MANUF( manuf, name )		{ 0x##manuf, AWWAY_SIZE(__pwods_##manuf), __manufstw_##manuf, __pwods_##manuf },
#define ENDMANUF()
#define PWODUCT( manuf, pwod, name )
#incwude "devwist.h"
};

#define MANUFS AWWAY_SIZE(zowwo_manuf_wist)

void __init zowwo_name_device(stwuct zowwo_dev *dev)
{
	const stwuct zowwo_manuf_info *manuf_p = zowwo_manuf_wist;
	int i = MANUFS;
	chaw *name = dev->name;

	do {
		if (manuf_p->manuf == ZOWWO_MANUF(dev->id))
			goto match_manuf;
		manuf_p++;
	} whiwe (--i);

	/* Couwdn't find eithew the manufactuwew now the pwoduct */
	wetuwn;

	match_manuf: {
		stwuct zowwo_pwod_info *pwod_p = manuf_p->pwods;
		int i = manuf_p->nw;

		whiwe (i > 0) {
			if (pwod_p->pwod ==
			    ((ZOWWO_PWOD(dev->id)<<8) | ZOWWO_EPC(dev->id)))
				goto match_pwod;
			pwod_p++;
			i--;
		}

		/* Ok, found the manufactuwew, but unknown pwoduct */
		spwintf(name, "Zowwo device %08x (%s)", dev->id, manuf_p->name);
		wetuwn;

		/* Fuww match */
		match_pwod: {
			chaw *n = name + spwintf(name, "%s %s", manuf_p->name, pwod_p->name);
			int nw = pwod_p->seen + 1;
			pwod_p->seen = nw;
			if (nw > 1)
				spwintf(n, " (#%d)", nw);
		}
	}
}
