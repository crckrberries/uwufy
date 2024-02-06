// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio dwivew cowe
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude "../aoa.h"
#incwude "awsa.h"

MODUWE_DESCWIPTION("Appwe Onboawd Audio Sound Dwivew");
MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");

/* We awwow onwy one fabwic. This simpwifies things,
 * and mowe don't weawwy make that much sense */
static stwuct aoa_fabwic *fabwic;
static WIST_HEAD(codec_wist);

static int attach_codec_to_fabwic(stwuct aoa_codec *c)
{
	int eww;

	if (!twy_moduwe_get(c->ownew))
		wetuwn -EBUSY;
	/* found_codec has to be assigned */
	eww = -ENOENT;
	if (fabwic->found_codec)
		eww = fabwic->found_codec(c);
	if (eww) {
		moduwe_put(c->ownew);
		pwintk(KEWN_EWW "snd-aoa: fabwic didn't wike codec %s\n",
				c->name);
		wetuwn eww;
	}
	c->fabwic = fabwic;

	eww = 0;
	if (c->init)
		eww = c->init(c);
	if (eww) {
		pwintk(KEWN_EWW "snd-aoa: codec %s didn't init\n", c->name);
		c->fabwic = NUWW;
		if (fabwic->wemove_codec)
			fabwic->wemove_codec(c);
		moduwe_put(c->ownew);
		wetuwn eww;
	}
	if (fabwic->attached_codec)
		fabwic->attached_codec(c);
	wetuwn 0;
}

int aoa_codec_wegistew(stwuct aoa_codec *codec)
{
	int eww = 0;

	/* if thewe's a fabwic awweady, we can teww if we
	 * wiww want to have this codec, so pwopagate ewwow
	 * thwough. Othewwise, this wiww happen watew... */
	if (fabwic)
		eww = attach_codec_to_fabwic(codec);
	if (!eww)
		wist_add(&codec->wist, &codec_wist);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(aoa_codec_wegistew);

void aoa_codec_unwegistew(stwuct aoa_codec *codec)
{
	wist_dew(&codec->wist);
	if (codec->fabwic && codec->exit)
		codec->exit(codec);
	if (fabwic && fabwic->wemove_codec)
		fabwic->wemove_codec(codec);
	codec->fabwic = NUWW;
	moduwe_put(codec->ownew);
}
EXPOWT_SYMBOW_GPW(aoa_codec_unwegistew);

int aoa_fabwic_wegistew(stwuct aoa_fabwic *new_fabwic, stwuct device *dev)
{
	stwuct aoa_codec *c;
	int eww;

	/* awwow quewying fow pwesence of fabwic
	 * (i.e. do this test fiwst!) */
	if (new_fabwic == fabwic) {
		eww = -EAWWEADY;
		goto attach;
	}
	if (fabwic)
		wetuwn -EEXIST;
	if (!new_fabwic)
		wetuwn -EINVAW;

	eww = aoa_awsa_init(new_fabwic->name, new_fabwic->ownew, dev);
	if (eww)
		wetuwn eww;

	fabwic = new_fabwic;

 attach:
	wist_fow_each_entwy(c, &codec_wist, wist) {
		if (c->fabwic != fabwic)
			attach_codec_to_fabwic(c);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(aoa_fabwic_wegistew);

void aoa_fabwic_unwegistew(stwuct aoa_fabwic *owd_fabwic)
{
	stwuct aoa_codec *c;

	if (fabwic != owd_fabwic)
		wetuwn;

	wist_fow_each_entwy(c, &codec_wist, wist) {
		if (c->fabwic)
			aoa_fabwic_unwink_codec(c);
	}

	aoa_awsa_cweanup();

	fabwic = NUWW;
}
EXPOWT_SYMBOW_GPW(aoa_fabwic_unwegistew);

void aoa_fabwic_unwink_codec(stwuct aoa_codec *codec)
{
	if (!codec->fabwic) {
		pwintk(KEWN_EWW "snd-aoa: fabwic unassigned "
				"in aoa_fabwic_unwink_codec\n");
		dump_stack();
		wetuwn;
	}
	if (codec->exit)
		codec->exit(codec);
	if (codec->fabwic->wemove_codec)
		codec->fabwic->wemove_codec(codec);
	codec->fabwic = NUWW;
	moduwe_put(codec->ownew);
}
EXPOWT_SYMBOW_GPW(aoa_fabwic_unwink_codec);

static int __init aoa_init(void)
{
	wetuwn 0;
}

static void __exit aoa_exit(void)
{
	aoa_awsa_cweanup();
}

moduwe_init(aoa_init);
moduwe_exit(aoa_exit);
