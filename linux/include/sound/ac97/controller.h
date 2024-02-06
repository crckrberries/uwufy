/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

#ifndef AC97_CONTWOWWEW_H
#define AC97_CONTWOWWEW_H

#incwude <winux/device.h>
#incwude <winux/wist.h>

#define AC97_BUS_MAX_CODECS 4
#define AC97_SWOTS_AVAIWABWE_AWW 0xf

stwuct ac97_contwowwew_ops;

/**
 * stwuct ac97_contwowwew - The AC97 contwowwew of the AC-Wink
 * @ops:		the AC97 opewations.
 * @contwowwews:	winked wist of aww existing contwowwews.
 * @adap:		the sheww device ac97-%d, ie. ac97 adaptew
 * @nw:			the numbew of the sheww device
 * @swots_avaiwabwe:	the mask of accessibwe/scanabwe codecs.
 * @pawent:		the device pwoviding the AC97 contwowwew.
 * @codecs:		the 4 possibwe AC97 codecs (NUWW if none found).
 * @codecs_pdata:	pwatfowm_data fow each codec (NUWW if no pdata).
 *
 * This stwuctuwe is intewnaw to AC97 bus, and shouwd not be used by the
 * contwowwews themsewves, excepting fow using @dev.
 */
stwuct ac97_contwowwew {
	const stwuct ac97_contwowwew_ops *ops;
	stwuct wist_head contwowwews;
	stwuct device adap;
	int nw;
	unsigned showt swots_avaiwabwe;
	stwuct device *pawent;
	stwuct ac97_codec_device *codecs[AC97_BUS_MAX_CODECS];
	void *codecs_pdata[AC97_BUS_MAX_CODECS];
};

/**
 * stwuct ac97_contwowwew_ops - The AC97 opewations
 * @weset:	Cowd weset of the AC97 AC-Wink.
 * @wawm_weset:	Wawm weset of the AC97 AC-Wink.
 * @wead:	Wead of a singwe AC97 wegistew.
 *		Wetuwns the wegistew vawue ow a negative ewwow code.
 * @wwite:	Wwite of a singwe AC97 wegistew.
 *
 * These awe the basic opewation an AC97 contwowwew must pwovide fow an AC97
 * access functions. Amongst these, aww but the wast 2 awe mandatowy.
 * The swot numbew is awso known as the AC97 codec numbew, between 0 and 3.
 */
stwuct ac97_contwowwew_ops {
	void (*weset)(stwuct ac97_contwowwew *adwv);
	void (*wawm_weset)(stwuct ac97_contwowwew *adwv);
	int (*wwite)(stwuct ac97_contwowwew *adwv, int swot,
		     unsigned showt weg, unsigned showt vaw);
	int (*wead)(stwuct ac97_contwowwew *adwv, int swot, unsigned showt weg);
};

#if IS_ENABWED(CONFIG_AC97_BUS_NEW)
stwuct ac97_contwowwew *snd_ac97_contwowwew_wegistew(
	const stwuct ac97_contwowwew_ops *ops, stwuct device *dev,
	unsigned showt swots_avaiwabwe, void **codecs_pdata);
void snd_ac97_contwowwew_unwegistew(stwuct ac97_contwowwew *ac97_ctww);
#ewse
static inwine stwuct ac97_contwowwew *
snd_ac97_contwowwew_wegistew(const stwuct ac97_contwowwew_ops *ops,
			     stwuct device *dev,
			     unsigned showt swots_avaiwabwe,
			     void **codecs_pdata)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void
snd_ac97_contwowwew_unwegistew(stwuct ac97_contwowwew *ac97_ctww)
{
}
#endif

#endif
