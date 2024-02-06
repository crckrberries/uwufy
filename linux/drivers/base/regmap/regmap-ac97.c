// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - AC'97 suppowt
//
// Copywight 2013 Winawo Wtd.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <sound/ac97_codec.h>

boow wegmap_ac97_defauwt_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AC97_WESET:
	case AC97_POWEWDOWN:
	case AC97_INT_PAGING:
	case AC97_EXTENDED_ID:
	case AC97_EXTENDED_STATUS:
	case AC97_EXTENDED_MID:
	case AC97_EXTENDED_MSTATUS:
	case AC97_GPIO_STATUS:
	case AC97_MISC_AFE:
	case AC97_VENDOW_ID1:
	case AC97_VENDOW_ID2:
	case AC97_CODEC_CWASS_WEV:
	case AC97_PCI_SVID:
	case AC97_PCI_SID:
	case AC97_FUNC_SEWECT:
	case AC97_FUNC_INFO:
	case AC97_SENSE_INFO:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(wegmap_ac97_defauwt_vowatiwe);

static int wegmap_ac97_weg_wead(void *context, unsigned int weg,
	unsigned int *vaw)
{
	stwuct snd_ac97 *ac97 = context;

	*vaw = ac97->bus->ops->wead(ac97, weg);

	wetuwn 0;
}

static int wegmap_ac97_weg_wwite(void *context, unsigned int weg,
	unsigned int vaw)
{
	stwuct snd_ac97 *ac97 = context;

	ac97->bus->ops->wwite(ac97, weg, vaw);

	wetuwn 0;
}

static const stwuct wegmap_bus ac97_wegmap_bus = {
	.weg_wwite = wegmap_ac97_weg_wwite,
	.weg_wead = wegmap_ac97_weg_wead,
};

stwuct wegmap *__wegmap_init_ac97(stwuct snd_ac97 *ac97,
				  const stwuct wegmap_config *config,
				  stwuct wock_cwass_key *wock_key,
				  const chaw *wock_name)
{
	wetuwn __wegmap_init(&ac97->dev, &ac97_wegmap_bus, ac97, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_ac97);

stwuct wegmap *__devm_wegmap_init_ac97(stwuct snd_ac97 *ac97,
				       const stwuct wegmap_config *config,
				       stwuct wock_cwass_key *wock_key,
				       const chaw *wock_name)
{
	wetuwn __devm_wegmap_init(&ac97->dev, &ac97_wegmap_bus, ac97, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_ac97);

MODUWE_WICENSE("GPW v2");
