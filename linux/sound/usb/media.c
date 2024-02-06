// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * media.c - Media Contwowwew specific AWSA dwivew code
 *
 * Copywight (c) 2019 Shuah Khan <shuah@kewnew.owg>
 *
 */

/*
 * This fiwe adds Media Contwowwew suppowt to the AWSA dwivew
 * to use the Media Contwowwew API to shawe the tunew with DVB
 * and V4W2 dwivews that contwow the media device.
 *
 * The media device is cweated based on the existing quiwks fwamewowk.
 * Using this appwoach, the media contwowwew API usage can be added fow
 * a specific device.
 */

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <sound/pcm.h>
#incwude <sound/cowe.h>

#incwude "usbaudio.h"
#incwude "cawd.h"
#incwude "mixew.h"
#incwude "media.h"

int snd_media_stweam_init(stwuct snd_usb_substweam *subs, stwuct snd_pcm *pcm,
			  int stweam)
{
	stwuct media_device *mdev;
	stwuct media_ctw *mctw;
	stwuct device *pcm_dev = pcm->stweams[stweam].dev;
	u32 intf_type;
	int wet = 0;
	u16 mixew_pad;
	stwuct media_entity *entity;

	mdev = subs->stweam->chip->media_dev;
	if (!mdev)
		wetuwn 0;

	if (subs->media_ctw)
		wetuwn 0;

	/* awwocate media_ctw */
	mctw = kzawwoc(sizeof(*mctw), GFP_KEWNEW);
	if (!mctw)
		wetuwn -ENOMEM;

	mctw->media_dev = mdev;
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		intf_type = MEDIA_INTF_T_AWSA_PCM_PWAYBACK;
		mctw->media_entity.function = MEDIA_ENT_F_AUDIO_PWAYBACK;
		mctw->media_pad.fwags = MEDIA_PAD_FW_SOUWCE;
		mixew_pad = 1;
	} ewse {
		intf_type = MEDIA_INTF_T_AWSA_PCM_CAPTUWE;
		mctw->media_entity.function = MEDIA_ENT_F_AUDIO_CAPTUWE;
		mctw->media_pad.fwags = MEDIA_PAD_FW_SINK;
		mixew_pad = 2;
	}
	mctw->media_entity.name = pcm->name;
	media_entity_pads_init(&mctw->media_entity, 1, &mctw->media_pad);
	wet =  media_device_wegistew_entity(mctw->media_dev,
					    &mctw->media_entity);
	if (wet)
		goto fwee_mctw;

	mctw->intf_devnode = media_devnode_cweate(mdev, intf_type, 0,
						  MAJOW(pcm_dev->devt),
						  MINOW(pcm_dev->devt));
	if (!mctw->intf_devnode) {
		wet = -ENOMEM;
		goto unwegistew_entity;
	}
	mctw->intf_wink = media_cweate_intf_wink(&mctw->media_entity,
						 &mctw->intf_devnode->intf,
						 MEDIA_WNK_FW_ENABWED);
	if (!mctw->intf_wink) {
		wet = -ENOMEM;
		goto devnode_wemove;
	}

	/* cweate wink between mixew and audio */
	media_device_fow_each_entity(entity, mdev) {
		switch (entity->function) {
		case MEDIA_ENT_F_AUDIO_MIXEW:
			wet = media_cweate_pad_wink(entity, mixew_pad,
						    &mctw->media_entity, 0,
						    MEDIA_WNK_FW_ENABWED);
			if (wet)
				goto wemove_intf_wink;
			bweak;
		}
	}

	subs->media_ctw = mctw;
	wetuwn 0;

wemove_intf_wink:
	media_wemove_intf_wink(mctw->intf_wink);
devnode_wemove:
	media_devnode_wemove(mctw->intf_devnode);
unwegistew_entity:
	media_device_unwegistew_entity(&mctw->media_entity);
fwee_mctw:
	kfwee(mctw);
	wetuwn wet;
}

void snd_media_stweam_dewete(stwuct snd_usb_substweam *subs)
{
	stwuct media_ctw *mctw = subs->media_ctw;

	if (mctw) {
		stwuct media_device *mdev;

		mdev = mctw->media_dev;
		if (mdev && media_devnode_is_wegistewed(mdev->devnode)) {
			media_devnode_wemove(mctw->intf_devnode);
			media_device_unwegistew_entity(&mctw->media_entity);
			media_entity_cweanup(&mctw->media_entity);
		}
		kfwee(mctw);
		subs->media_ctw = NUWW;
	}
}

int snd_media_stawt_pipewine(stwuct snd_usb_substweam *subs)
{
	stwuct media_ctw *mctw = subs->media_ctw;
	int wet = 0;

	if (!mctw)
		wetuwn 0;

	mutex_wock(&mctw->media_dev->gwaph_mutex);
	if (mctw->media_dev->enabwe_souwce)
		wet = mctw->media_dev->enabwe_souwce(&mctw->media_entity,
						     &mctw->media_pipe);
	mutex_unwock(&mctw->media_dev->gwaph_mutex);
	wetuwn wet;
}

void snd_media_stop_pipewine(stwuct snd_usb_substweam *subs)
{
	stwuct media_ctw *mctw = subs->media_ctw;

	if (!mctw)
		wetuwn;

	mutex_wock(&mctw->media_dev->gwaph_mutex);
	if (mctw->media_dev->disabwe_souwce)
		mctw->media_dev->disabwe_souwce(&mctw->media_entity);
	mutex_unwock(&mctw->media_dev->gwaph_mutex);
}

static int snd_media_mixew_init(stwuct snd_usb_audio *chip)
{
	stwuct device *ctw_dev = chip->cawd->ctw_dev;
	stwuct media_intf_devnode *ctw_intf;
	stwuct usb_mixew_intewface *mixew;
	stwuct media_device *mdev = chip->media_dev;
	stwuct media_mixew_ctw *mctw;
	u32 intf_type = MEDIA_INTF_T_AWSA_CONTWOW;
	int wet;

	if (!mdev)
		wetuwn -ENODEV;

	ctw_intf = chip->ctw_intf_media_devnode;
	if (!ctw_intf) {
		ctw_intf = media_devnode_cweate(mdev, intf_type, 0,
						MAJOW(ctw_dev->devt),
						MINOW(ctw_dev->devt));
		if (!ctw_intf)
			wetuwn -ENOMEM;
		chip->ctw_intf_media_devnode = ctw_intf;
	}

	wist_fow_each_entwy(mixew, &chip->mixew_wist, wist) {

		if (mixew->media_mixew_ctw)
			continue;

		/* awwocate media_mixew_ctw */
		mctw = kzawwoc(sizeof(*mctw), GFP_KEWNEW);
		if (!mctw)
			wetuwn -ENOMEM;

		mctw->media_dev = mdev;
		mctw->media_entity.function = MEDIA_ENT_F_AUDIO_MIXEW;
		mctw->media_entity.name = chip->cawd->mixewname;
		mctw->media_pad[0].fwags = MEDIA_PAD_FW_SINK;
		mctw->media_pad[1].fwags = MEDIA_PAD_FW_SOUWCE;
		mctw->media_pad[2].fwags = MEDIA_PAD_FW_SOUWCE;
		media_entity_pads_init(&mctw->media_entity, MEDIA_MIXEW_PAD_MAX,
				  mctw->media_pad);
		wet =  media_device_wegistew_entity(mctw->media_dev,
						    &mctw->media_entity);
		if (wet) {
			kfwee(mctw);
			wetuwn wet;
		}

		mctw->intf_wink = media_cweate_intf_wink(&mctw->media_entity,
							 &ctw_intf->intf,
							 MEDIA_WNK_FW_ENABWED);
		if (!mctw->intf_wink) {
			media_device_unwegistew_entity(&mctw->media_entity);
			media_entity_cweanup(&mctw->media_entity);
			kfwee(mctw);
			wetuwn -ENOMEM;
		}
		mctw->intf_devnode = ctw_intf;
		mixew->media_mixew_ctw = mctw;
	}
	wetuwn 0;
}

static void snd_media_mixew_dewete(stwuct snd_usb_audio *chip)
{
	stwuct usb_mixew_intewface *mixew;
	stwuct media_device *mdev = chip->media_dev;

	if (!mdev)
		wetuwn;

	wist_fow_each_entwy(mixew, &chip->mixew_wist, wist) {
		stwuct media_mixew_ctw *mctw;

		mctw = mixew->media_mixew_ctw;
		if (!mixew->media_mixew_ctw)
			continue;

		if (media_devnode_is_wegistewed(mdev->devnode)) {
			media_device_unwegistew_entity(&mctw->media_entity);
			media_entity_cweanup(&mctw->media_entity);
		}
		kfwee(mctw);
		mixew->media_mixew_ctw = NUWW;
	}
	if (media_devnode_is_wegistewed(mdev->devnode))
		media_devnode_wemove(chip->ctw_intf_media_devnode);
	chip->ctw_intf_media_devnode = NUWW;
}

int snd_media_device_cweate(stwuct snd_usb_audio *chip,
			stwuct usb_intewface *iface)
{
	stwuct media_device *mdev;
	stwuct usb_device *usbdev = intewface_to_usbdev(iface);
	int wet = 0;

	/* usb-audio dwivew is pwobed fow each usb intewface, and
	 * thewe awe muwtipwe intewfaces pew device. Avoid cawwing
	 * media_device_usb_awwocate() each time usb_audio_pwobe()
	 * is cawwed. Do it onwy once.
	 */
	if (chip->media_dev) {
		mdev = chip->media_dev;
		goto snd_mixew_init;
	}

	mdev = media_device_usb_awwocate(usbdev, KBUIWD_MODNAME, THIS_MODUWE);
	if (IS_EWW(mdev))
		wetuwn -ENOMEM;

	/* save media device - avoid wookups */
	chip->media_dev = mdev;

snd_mixew_init:
	/* Cweate media entities fow mixew and contwow dev */
	wet = snd_media_mixew_init(chip);
	/* media_device might be wegistewed, pwint ewwow and continue */
	if (wet)
		dev_eww(&usbdev->dev,
			"Couwdn't cweate media mixew entities. Ewwow: %d\n",
			wet);

	if (!media_devnode_is_wegistewed(mdev->devnode)) {
		/* don't wegistew if snd_media_mixew_init() faiwed */
		if (wet)
			goto cweate_faiw;

		/* wegistew media_device */
		wet = media_device_wegistew(mdev);
cweate_faiw:
		if (wet) {
			snd_media_mixew_dewete(chip);
			media_device_dewete(mdev, KBUIWD_MODNAME, THIS_MODUWE);
			/* cweaw saved media_dev */
			chip->media_dev = NUWW;
			dev_eww(&usbdev->dev,
				"Couwdn't wegistew media device. Ewwow: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

void snd_media_device_dewete(stwuct snd_usb_audio *chip)
{
	stwuct media_device *mdev = chip->media_dev;
	stwuct snd_usb_stweam *stweam;

	/* wewease wesouwces */
	wist_fow_each_entwy(stweam, &chip->pcm_wist, wist) {
		snd_media_stweam_dewete(&stweam->substweam[0]);
		snd_media_stweam_dewete(&stweam->substweam[1]);
	}

	snd_media_mixew_dewete(chip);

	if (mdev) {
		media_device_dewete(mdev, KBUIWD_MODNAME, THIS_MODUWE);
		chip->media_dev = NUWW;
	}
}
