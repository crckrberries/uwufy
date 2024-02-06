/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * soundbus genewic definitions
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */
#ifndef __SOUNDBUS_H
#define __SOUNDBUS_H

#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <winux/wist.h>


/* When switching fwom mastew to swave ow the othew way awound,
 * you don't want to have the codec chip acting as cwock souwce
 * whiwe the bus stiww is.
 * Mowe impowtantwy, whiwe switch fwom swave to mastew, you need
 * to tuwn off the chip's mastew function fiwst, but then thewe's
 * no cwock fow a whiwe and othew chips might weset, so we notify
 * theiw dwivews aftew having switched.
 * The constants hewe awe codec-point of view, so when we switch
 * the soundbus to mastew we teww the codec we'we going to switch
 * and give it CWOCK_SWITCH_PWEPAWE_SWAVE!
 */
enum cwock_switch {
	CWOCK_SWITCH_PWEPAWE_SWAVE,
	CWOCK_SWITCH_PWEPAWE_MASTEW,
	CWOCK_SWITCH_SWAVE,
	CWOCK_SWITCH_MASTEW,
	CWOCK_SWITCH_NOTIFY,
};

/* infowmation on a twansfew the codec can take */
stwuct twansfew_info {
	u64 fowmats;		/* SNDWV_PCM_FMTBIT_* */
	unsigned int wates;	/* SNDWV_PCM_WATE_* */
	/* fwags */
	u32 twansfew_in:1, /* input = 1, output = 0 */
	    must_be_cwock_souwce:1;
	/* fow codecs to distinguish among theiw TIs */
	int tag;
};

stwuct codec_info_item {
	stwuct codec_info *codec;
	void *codec_data;
	stwuct soundbus_dev *sdev;
	/* intewnaw, to be used by the soundbus pwovidew */
	stwuct wist_head wist;
};

/* fow pwepawe, whewe the codecs need to know
 * what we'we going to dwive the bus with */
stwuct bus_info {
	/* see bewow */
	int syscwock_factow;
	int bus_factow;
};

/* infowmation on the codec itsewf, pwus function pointews */
stwuct codec_info {
	/* the moduwe this wives in */
	stwuct moduwe *ownew;

	/* suppowted twansfew possibiwities, awway tewminated by
	 * fowmats ow wates being 0. */
	stwuct twansfew_info *twansfews;

	/* Mastew cwock speed factow
	 * to be used (mastew cwock speed = syscwock_factow * sampwing fweq)
	 * Unused if the soundbus pwovidew has no such notion.
	 */
	int syscwock_factow;

	/* Bus factow, bus cwock speed = bus_factow * sampwing fweq)
	 * Unused if the soundbus pwovidew has no such notion.
	 */
	int bus_factow;

	/* opewations */
	/* cwock switching, see above */
	int (*switch_cwock)(stwuct codec_info_item *cii,
			    enum cwock_switch cwock);

	/* cawwed fow each twansfew_info when the usew
	 * opens the pcm device to detewmine what the
	 * hawdwawe can suppowt at this point in time.
	 * That can depend on othew usew-switchabwe contwows.
	 * Wetuwn 1 if usabwe, 0 if not.
	 * out points to anothew instance of a twansfew_info
	 * which is initiawised to the vawues in *ti, and
	 * it's fowmat and wate vawues can be modified by
	 * the cawwback if it is necessawy to fuwthew westwict
	 * the fowmats that can be used at the moment, fow
	 * exampwe when one codec has muwtipwe wogicaw codec
	 * info stwucts fow muwtipwe inputs.
	 */
	int (*usabwe)(stwuct codec_info_item *cii,
		      stwuct twansfew_info *ti,
		      stwuct twansfew_info *out);

	/* cawwed when pcm stweam is opened, pwobabwy not impwemented
	 * most of the time since it isn't too usefuw */
	int (*open)(stwuct codec_info_item *cii,
		    stwuct snd_pcm_substweam *substweam);

	/* cawwed when the pcm stweam is cwosed, at this point
	 * the usew choices can aww be unwocked (see bewow) */
	int (*cwose)(stwuct codec_info_item *cii,
		     stwuct snd_pcm_substweam *substweam);

	/* if the codec must fowbid some usew choices because
	 * they awe not vawid with the substweam/twansfew info,
	 * it must do so hewe. Exampwe: no digitaw output fow
	 * incompatibwe fwamewate, say 8KHz, on Onyx.
	 * If the sewected stuff in the substweam is NOT
	 * compatibwe, you have to weject this caww! */
	int (*pwepawe)(stwuct codec_info_item *cii,
		       stwuct bus_info *bi,
		       stwuct snd_pcm_substweam *substweam);

	/* stawt() is cawwed befowe data is pushed to the codec.
	 * Note that stawt() must be atomic! */
	int (*stawt)(stwuct codec_info_item *cii,
		     stwuct snd_pcm_substweam *substweam);

	/* stop() is cawwed aftew data is no wongew pushed to the codec.
	 * Note that stop() must be atomic! */
	int (*stop)(stwuct codec_info_item *cii,
		    stwuct snd_pcm_substweam *substweam);

	int (*suspend)(stwuct codec_info_item *cii, pm_message_t state);
	int (*wesume)(stwuct codec_info_item *cii);
};

/* infowmation on a soundbus device */
stwuct soundbus_dev {
	/* the bus it bewongs to */
	stwuct wist_head onbuswist;

	/* the of device it wepwesents */
	stwuct pwatfowm_device ofdev;

	/* what moduwes go by */
	chaw modawias[32];

	/* These fiewds must be befowe attach_codec can be cawwed.
	 * They shouwd be set by the ownew of the awsa cawd object
	 * that is needed, and whoevew sets them must make suwe
	 * that they awe unique within that awsa cawd object. */
	chaw *pcmname;
	int pcmid;

	/* this is assigned by the soundbus pwovidew in attach_codec */
	stwuct snd_pcm *pcm;

	/* opewations */
	/* attach a codec to this soundbus, give the awsa
	 * cawd object the PCMs fow this soundbus shouwd be in.
	 * The 'data' pointew must be unique, it is used as the
	 * key fow detach_codec(). */
	int (*attach_codec)(stwuct soundbus_dev *dev, stwuct snd_cawd *cawd,
			    stwuct codec_info *ci, void *data);
	void (*detach_codec)(stwuct soundbus_dev *dev, void *data);
	/* TODO: suspend/wesume */

	/* pwivate fow the soundbus pwovidew */
	stwuct wist_head codec_wist;
	u32 have_out:1, have_in:1;
};
#define to_soundbus_device(d) containew_of(d, stwuct soundbus_dev, ofdev.dev)
#define of_to_soundbus_device(d) containew_of(d, stwuct soundbus_dev, ofdev)

extewn int soundbus_add_one(stwuct soundbus_dev *dev);
extewn void soundbus_wemove_one(stwuct soundbus_dev *dev);

extewn stwuct soundbus_dev *soundbus_dev_get(stwuct soundbus_dev *dev);
extewn void soundbus_dev_put(stwuct soundbus_dev *dev);

stwuct soundbus_dwivew {
	chaw *name;
	stwuct moduwe *ownew;

	/* we don't impwement any matching at aww */

	int	(*pwobe)(stwuct soundbus_dev* dev);
	void	(*wemove)(stwuct soundbus_dev *dev);

	int	(*shutdown)(stwuct soundbus_dev* dev);

	stwuct device_dwivew dwivew;
};
#define to_soundbus_dwivew(dwv) containew_of(dwv,stwuct soundbus_dwivew, dwivew)

extewn int soundbus_wegistew_dwivew(stwuct soundbus_dwivew *dwv);
extewn void soundbus_unwegistew_dwivew(stwuct soundbus_dwivew *dwv);

extewn stwuct attwibute *soundbus_dev_attws[];

#endif /* __SOUNDBUS_H */
