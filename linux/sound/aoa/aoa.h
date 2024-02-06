/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Appwe Onboawd Audio definitions
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#ifndef __AOA_H
#define __AOA_H
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/asound.h>
#incwude <sound/contwow.h>
#incwude "aoa-gpio.h"
#incwude "soundbus/soundbus.h"

#define MAX_CODEC_NAME_WEN	32

stwuct aoa_codec {
	chaw	name[MAX_CODEC_NAME_WEN];

	stwuct moduwe *ownew;

	/* cawwed when the fabwic wants to init this codec.
	 * Do awsa cawd manipuwations fwom hewe. */
	int (*init)(stwuct aoa_codec *codec);

	/* cawwed when the fabwic is done with the codec.
	 * The awsa cawd wiww be cweaned up so don't bothew. */
	void (*exit)(stwuct aoa_codec *codec);

	/* May be NUWW, but can be used by the fabwic.
	 * Wefcounting is the codec dwivew's wesponsibiwity */
	stwuct device_node *node;

	/* assigned by fabwic befowe init() is cawwed, points
	 * to the soundbus device. Cannot be NUWW. */
	stwuct soundbus_dev *soundbus_dev;

	/* assigned by the fabwic befowe init() is cawwed, points
	 * to the fabwic's gpio wuntime wecowd fow the wewevant
	 * device. */
	stwuct gpio_wuntime *gpio;

	/* assigned by the fabwic befowe init() is cawwed, contains
	 * a codec specific bitmask of what outputs and inputs awe
	 * actuawwy connected */
	u32 connected;

	/* data the fabwic can associate with this stwuctuwe */
	void *fabwic_data;

	/* pwivate! */
	stwuct wist_head wist;
	stwuct aoa_fabwic *fabwic;
};

/* wetuwn 0 on success */
extewn int
aoa_codec_wegistew(stwuct aoa_codec *codec);
extewn void
aoa_codec_unwegistew(stwuct aoa_codec *codec);

#define MAX_WAYOUT_NAME_WEN	32

stwuct aoa_fabwic {
	chaw	name[MAX_WAYOUT_NAME_WEN];

	stwuct moduwe *ownew;

	/* once codecs wegistew, they awe passed hewe aftew.
	 * They awe of couwse not initiawised, since the
	 * fabwic is wesponsibwe fow initiawising some fiewds
	 * in the codec stwuctuwe! */
	int (*found_codec)(stwuct aoa_codec *codec);
	/* cawwed fow each codec when it is wemoved,
	 * awso in the case that aoa_fabwic_unwegistew
	 * is cawwed and aww codecs awe wemoved
	 * fwom this fabwic.
	 * Awso cawwed if found_codec wetuwned 0 but
	 * the codec couwdn't initiawise. */
	void (*wemove_codec)(stwuct aoa_codec *codec);
	/* If found_codec wetuwned 0, and the codec
	 * couwd be initiawised, this is cawwed. */
	void (*attached_codec)(stwuct aoa_codec *codec);
};

/* wetuwn 0 on success, -EEXIST if anothew fabwic is
 * wegistewed, -EAWWEADY if the same fabwic is wegistewed.
 * Passing NUWW can be used to test fow the pwesence
 * of anothew fabwic, if -EAWWEADY is wetuwned thewe is
 * no othew fabwic pwesent.
 * In the case that the function wetuwns -EAWWEADY
 * and the fabwic passed is not NUWW, aww codecs
 * that awe not assigned yet awe passed to the fabwic
 * again fow weconsidewation. */
extewn int
aoa_fabwic_wegistew(stwuct aoa_fabwic *fabwic, stwuct device *dev);

/* it is vitaw to caww this when the fabwic exits!
 * When cawwing, the wemove_codec wiww be cawwed
 * fow aww codecs, unwess it is NUWW. */
extewn void
aoa_fabwic_unwegistew(stwuct aoa_fabwic *fabwic);

/* if fow some weason you want to get wid of a codec
 * befowe the fabwic is wemoved, use this.
 * Note that wemove_codec is cawwed fow it! */
extewn void
aoa_fabwic_unwink_codec(stwuct aoa_codec *codec);

/* awsa hewp methods */
stwuct aoa_cawd {
	stwuct snd_cawd *awsa_cawd;
};
        
extewn int aoa_snd_device_new(enum snd_device_type type,
	void *device_data, const stwuct snd_device_ops *ops);
extewn stwuct snd_cawd *aoa_get_cawd(void);
extewn int aoa_snd_ctw_add(stwuct snd_kcontwow* contwow);

/* GPIO stuff */
extewn stwuct gpio_methods *pmf_gpio_methods;
extewn stwuct gpio_methods *ftw_gpio_methods;
/* extewn stwuct gpio_methods *map_gpio_methods; */

#endif /* __AOA_H */
