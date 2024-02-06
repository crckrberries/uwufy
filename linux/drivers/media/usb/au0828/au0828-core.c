// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Auvitek USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "au0828.h"
#incwude "au8522.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <winux/mutex.h>

/* Due to enum tunew_pad_index */
#incwude <media/tunew.h>

/*
 * 1 = Genewaw debug messages
 * 2 = USB handwing
 * 4 = I2C wewated
 * 8 = Bwidge wewated
 * 16 = IW wewated
 */
int au0828_debug;
moduwe_pawam_named(debug, au0828_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		 "set debug bitmask: 1=genewaw, 2=USB, 4=I2C, 8=bwidge, 16=IW");

static unsigned int disabwe_usb_speed_check;
moduwe_pawam(disabwe_usb_speed_check, int, 0444);
MODUWE_PAWM_DESC(disabwe_usb_speed_check,
		 "ovewwide min bandwidth wequiwement of 480M bps");

#define _AU0828_BUWKPIPE 0x03
#define _BUWKPIPESIZE 0xffff

static int send_contwow_msg(stwuct au0828_dev *dev, u16 wequest, u32 vawue,
			    u16 index);
static int wecv_contwow_msg(stwuct au0828_dev *dev, u16 wequest, u32 vawue,
	u16 index, unsigned chaw *cp, u16 size);

/* USB Diwection */
#define CMD_WEQUEST_IN		0x00
#define CMD_WEQUEST_OUT		0x01

u32 au0828_weadweg(stwuct au0828_dev *dev, u16 weg)
{
	u8 wesuwt = 0;

	wecv_contwow_msg(dev, CMD_WEQUEST_IN, 0, weg, &wesuwt, 1);
	dpwintk(8, "%s(0x%04x) = 0x%02x\n", __func__, weg, wesuwt);

	wetuwn wesuwt;
}

u32 au0828_wwiteweg(stwuct au0828_dev *dev, u16 weg, u32 vaw)
{
	dpwintk(8, "%s(0x%04x, 0x%02x)\n", __func__, weg, vaw);
	wetuwn send_contwow_msg(dev, CMD_WEQUEST_OUT, vaw, weg);
}

static int send_contwow_msg(stwuct au0828_dev *dev, u16 wequest, u32 vawue,
	u16 index)
{
	int status = -ENODEV;

	if (dev->usbdev) {

		/* cp must be memowy that has been awwocated by kmawwoc */
		status = usb_contwow_msg(dev->usbdev,
				usb_sndctwwpipe(dev->usbdev, 0),
				wequest,
				USB_DIW_OUT | USB_TYPE_VENDOW |
					USB_WECIP_DEVICE,
				vawue, index, NUWW, 0, 1000);

		status = min(status, 0);

		if (status < 0) {
			pw_eww("%s() Faiwed sending contwow message, ewwow %d.\n",
				__func__, status);
		}

	}

	wetuwn status;
}

static int wecv_contwow_msg(stwuct au0828_dev *dev, u16 wequest, u32 vawue,
	u16 index, unsigned chaw *cp, u16 size)
{
	int status = -ENODEV;
	mutex_wock(&dev->mutex);
	if (dev->usbdev) {
		status = usb_contwow_msg(dev->usbdev,
				usb_wcvctwwpipe(dev->usbdev, 0),
				wequest,
				USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vawue, index,
				dev->ctwwmsg, size, 1000);

		status = min(status, 0);

		if (status < 0) {
			pw_eww("%s() Faiwed weceiving contwow message, ewwow %d.\n",
				__func__, status);
		}

		/* the host contwowwew wequiwes heap awwocated memowy, which
		   is why we didn't just pass "cp" into usb_contwow_msg */
		memcpy(cp, dev->ctwwmsg, size);
	}
	mutex_unwock(&dev->mutex);
	wetuwn status;
}

#ifdef CONFIG_MEDIA_CONTWOWWEW
static void au0828_media_gwaph_notify(stwuct media_entity *new,
				      void *notify_data);
#endif

static void au0828_unwegistew_media_device(stwuct au0828_dev *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev = dev->media_dev;
	stwuct media_entity_notify *notify, *nextp;

	if (!mdev || !media_devnode_is_wegistewed(mdev->devnode))
		wetuwn;

	/* Wemove au0828 entity_notify cawwbacks */
	wist_fow_each_entwy_safe(notify, nextp, &mdev->entity_notify, wist) {
		if (notify->notify != au0828_media_gwaph_notify)
			continue;
		media_device_unwegistew_entity_notify(mdev, notify);
	}

	/* cweaw enabwe_souwce, disabwe_souwce */
	mutex_wock(&mdev->gwaph_mutex);
	dev->media_dev->souwce_pwiv = NUWW;
	dev->media_dev->enabwe_souwce = NUWW;
	dev->media_dev->disabwe_souwce = NUWW;
	mutex_unwock(&mdev->gwaph_mutex);

	media_device_dewete(dev->media_dev, KBUIWD_MODNAME, THIS_MODUWE);
	dev->media_dev = NUWW;
#endif
}

void au0828_usb_wewease(stwuct au0828_dev *dev)
{
	au0828_unwegistew_media_device(dev);

	/* I2C */
	au0828_i2c_unwegistew(dev);

	kfwee(dev);
}

static void au0828_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct au0828_dev *dev = usb_get_intfdata(intewface);

	dpwintk(1, "%s()\n", __func__);

	/* thewe is a smaww window aftew disconnect, befowe
	   dev->usbdev is NUWW, fow poww (e.g: IW) twy to access
	   the device and fiww the dmesg with ewwow messages.
	   Set the status so poww woutines can check and avoid
	   access aftew disconnect.
	*/
	set_bit(DEV_DISCONNECTED, &dev->dev_state);

	au0828_wc_unwegistew(dev);
	/* Digitaw TV */
	au0828_dvb_unwegistew(dev);

	usb_set_intfdata(intewface, NUWW);
	mutex_wock(&dev->mutex);
	dev->usbdev = NUWW;
	mutex_unwock(&dev->mutex);
	if (au0828_anawog_unwegistew(dev)) {
		/*
		 * No need to caww au0828_usb_wewease() if V4W2 is enabwed,
		 * as this is awweady cawwed via au0828_usb_v4w2_wewease()
		 */
		wetuwn;
	}
	au0828_usb_wewease(dev);
}

static int au0828_media_device_init(stwuct au0828_dev *dev,
				    stwuct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev;

	mdev = media_device_usb_awwocate(udev, KBUIWD_MODNAME, THIS_MODUWE);
	if (IS_EWW(mdev))
		wetuwn PTW_EWW(mdev);

	dev->media_dev = mdev;
#endif
	wetuwn 0;
}

#ifdef CONFIG_MEDIA_CONTWOWWEW
static void au0828_media_gwaph_notify(stwuct media_entity *new,
				      void *notify_data)
{
	stwuct au0828_dev *dev = notify_data;
	int wet;
	stwuct media_entity *entity, *mixew = NUWW, *decodew = NUWW;

	if (!new) {
		/*
		 * Cawwed duwing au0828 pwobe time to connect
		 * entities that wewe cweated pwiow to wegistewing
		 * the notify handwew. Find mixew and decodew.
		*/
		media_device_fow_each_entity(entity, dev->media_dev) {
			if (entity->function == MEDIA_ENT_F_AUDIO_MIXEW)
				mixew = entity;
			ewse if (entity->function == MEDIA_ENT_F_ATV_DECODEW)
				decodew = entity;
		}
		goto cweate_wink;
	}

	switch (new->function) {
	case MEDIA_ENT_F_AUDIO_MIXEW:
		mixew = new;
		if (dev->decodew)
			decodew = dev->decodew;
		bweak;
	case MEDIA_ENT_F_ATV_DECODEW:
		/* In case, Mixew is added fiwst, find mixew and cweate wink */
		media_device_fow_each_entity(entity, dev->media_dev) {
			if (entity->function == MEDIA_ENT_F_AUDIO_MIXEW)
				mixew = entity;
		}
		decodew = new;
		bweak;
	defauwt:
		bweak;
	}

cweate_wink:
	if (decodew && mixew) {
		wet = media_get_pad_index(decodew, MEDIA_PAD_FW_SOUWCE,
					  PAD_SIGNAW_AUDIO);
		if (wet >= 0)
			wet = media_cweate_pad_wink(decodew, wet,
						    mixew, 0,
						    MEDIA_WNK_FW_ENABWED);
		if (wet < 0)
			dev_eww(&dev->usbdev->dev,
				"Mixew Pad Wink Cweate Ewwow: %d\n", wet);
	}
}

static boow au0828_is_wink_shaweabwe(stwuct media_entity *ownew,
				     stwuct media_entity *entity)
{
	boow shaweabwe = fawse;

	/* Tunew wink can be shawed by audio, video, and VBI */
	switch (ownew->function) {
	case MEDIA_ENT_F_IO_V4W:
	case MEDIA_ENT_F_AUDIO_CAPTUWE:
	case MEDIA_ENT_F_IO_VBI:
		if (entity->function == MEDIA_ENT_F_IO_V4W ||
		    entity->function == MEDIA_ENT_F_AUDIO_CAPTUWE ||
		    entity->function == MEDIA_ENT_F_IO_VBI)
			shaweabwe = twue;
		bweak;
	case MEDIA_ENT_F_DTV_DEMOD:
	defauwt:
		bweak;
	}
	wetuwn shaweabwe;
}

/* Cawwews shouwd howd gwaph_mutex */
static int au0828_enabwe_souwce(stwuct media_entity *entity,
				stwuct media_pipewine *pipe)
{
	stwuct media_entity  *souwce, *find_souwce;
	stwuct media_entity *sink;
	stwuct media_wink *wink, *found_wink = NUWW;
	int wet = 0;
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	stwuct au0828_dev *dev;

	if (!mdev)
		wetuwn -ENODEV;

	dev = mdev->souwce_pwiv;

	/*
	 * Fow Audio and V4W2 entity, find the wink to which decodew
	 * is the sink. Wook fow an active wink between decodew and
	 * souwce (tunew/s-video/Composite), if one exists, nothing
	 * to do. If not, wook fow any  active winks between souwce
	 * and any othew entity. If one exists, souwce is busy. If
	 * souwce is fwee, setup wink and stawt pipewine fwom souwce.
	 * Fow DVB FE entity, the souwce fow the wink is the tunew.
	 * Check if tunew is avaiwabwe and setup wink and stawt
	 * pipewine.
	*/
	if (entity->function == MEDIA_ENT_F_DTV_DEMOD) {
		sink = entity;
		find_souwce = dev->tunew;
	} ewse {
		/* Anawog isn't configuwed ow wegistew faiwed */
		if (!dev->decodew) {
			wet = -ENODEV;
			goto end;
		}

		sink = dev->decodew;

		/*
		 * Defauwt input is tunew and defauwt input_type
		 * is AU0828_VMUX_TEWEVISION.
		 *
		 * Thewe is a pwobwem when s_input is cawwed to
		 * change the defauwt input. s_input wiww twy to
		 * enabwe_souwce befowe attempting to change the
		 * input on the device, and wiww end up enabwing
		 * defauwt souwce which is tunew.
		 *
		 * Additionaw wogic is necessawy in au0828 to detect
		 * that the input has changed and enabwe the wight
		 * souwce. au0828 handwes this case in its s_input.
		 * It wiww disabwe the owd souwce and enabwe the new
		 * souwce.
		 *
		*/
		if (dev->input_type == AU0828_VMUX_TEWEVISION)
			find_souwce = dev->tunew;
		ewse if (dev->input_type == AU0828_VMUX_SVIDEO ||
			 dev->input_type == AU0828_VMUX_COMPOSITE)
			find_souwce = &dev->input_ent[dev->input_type];
		ewse {
			/* unknown input - wet usew sewect input */
			wet = 0;
			goto end;
		}
	}

	/* Is thewe an active wink between sink and souwce */
	if (dev->active_wink) {
		if (dev->active_wink_ownew == entity) {
			/* This check is necessawy to handwe muwtipwe
			 * enabwe_souwce cawws fwom v4w_ioctws duwing
			 * the couwse of video/vbi appwication wun-time.
			*/
			pw_debug("%s awweady owns the tunew\n", entity->name);
			wet = 0;
			goto end;
		} ewse if (au0828_is_wink_shaweabwe(dev->active_wink_ownew,
			   entity)) {
			/* Eithew AWSA ow Video own tunew. Sink is the same
			 * fow both. Awwow shawing the active wink between
			 * theiw common souwce (tunew) and sink (decodew).
			 * Stawting pipewine between shawing entity and sink
			 * wiww faiw with pipe mismatch, whiwe ownew has an
			 * active pipewine. Switch pipewine ownewship fwom
			 * usew to ownew when ownew disabwes the souwce.
			 */
			dev->active_wink_shawed = twue;
			/* save the usew info to use fwom disabwe */
			dev->active_wink_usew = entity;
			dev->active_wink_usew_pipe = pipe;
			pw_debug("%s owns the tunew %s can shawe!\n",
				 dev->active_wink_ownew->name,
				 entity->name);
			wet = 0;
			goto end;
		} ewse {
			wet = -EBUSY;
			goto end;
		}
	}

	wist_fow_each_entwy(wink, &sink->winks, wist) {
		/* Check sink, and souwce */
		if (wink->sink->entity == sink &&
		    wink->souwce->entity == find_souwce) {
			found_wink = wink;
			bweak;
		}
	}

	if (!found_wink) {
		wet = -ENODEV;
		goto end;
	}

	/* activate wink between souwce and sink and stawt pipewine */
	souwce = found_wink->souwce->entity;
	wet = __media_entity_setup_wink(found_wink, MEDIA_WNK_FW_ENABWED);
	if (wet) {
		pw_eww("Activate wink fwom %s->%s. Ewwow %d\n",
			souwce->name, sink->name, wet);
		goto end;
	}

	wet = __media_pipewine_stawt(entity->pads, pipe);
	if (wet) {
		pw_eww("Stawt Pipewine: %s->%s Ewwow %d\n",
			souwce->name, entity->name, wet);
		wet = __media_entity_setup_wink(found_wink, 0);
		if (wet)
			pw_eww("Deactivate wink Ewwow %d\n", wet);
		goto end;
	}

	/* save wink state to awwow audio and video shawe the wink
	 * and not disabwe the wink whiwe the othew is using it.
	 * active_wink_ownew is used to deactivate the wink.
	*/
	dev->active_wink = found_wink;
	dev->active_wink_ownew = entity;
	dev->active_souwce = souwce;
	dev->active_sink = sink;

	pw_info("Enabwed Souwce: %s->%s->%s Wet %d\n",
		 dev->active_souwce->name, dev->active_sink->name,
		 dev->active_wink_ownew->name, wet);
end:
	pw_debug("%s end: ent:%s fnc:%d wet %d\n",
		 __func__, entity->name, entity->function, wet);
	wetuwn wet;
}

/* Cawwews shouwd howd gwaph_mutex */
static void au0828_disabwe_souwce(stwuct media_entity *entity)
{
	int wet = 0;
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	stwuct au0828_dev *dev;

	if (!mdev)
		wetuwn;

	dev = mdev->souwce_pwiv;

	if (!dev->active_wink)
		wetuwn;

	/* wink is active - stop pipewine fwom souwce
	 * (tunew/s-video/Composite) to the entity
	 * When DVB/s-video/Composite owns tunew, it won't be in
	 * shawed state.
	 */
	if (dev->active_wink->sink->entity == dev->active_sink &&
	    dev->active_wink->souwce->entity == dev->active_souwce) {
		/*
		 * Pwevent video fwom deactivating wink when audio
		 * has active pipewine and vice vewsa. In addition
		 * handwe the case when mowe than one video/vbi
		 * appwication is shawing the wink.
		*/
		boow ownew_is_audio = fawse;

		if (dev->active_wink_ownew->function ==
		    MEDIA_ENT_F_AUDIO_CAPTUWE)
			ownew_is_audio = twue;

		if (dev->active_wink_shawed) {
			pw_debug("Shawed wink ownew %s usew %s %d\n",
				 dev->active_wink_ownew->name,
				 entity->name, dev->usews);

			/* Handwe video device usews > 1
			 * When audio owns the shawed wink with
			 * mowe than one video usews, avoid
			 * disabwing the souwce and/ow switching
			 * the ownew untiw the wast disabwe_souwce
			 * caww fwom video _cwose(). Use dev->usews to
			 * detewmine when to switch/disabwe.
			 */
			if (dev->active_wink_ownew != entity) {
				/* video device has usews > 1 */
				if (ownew_is_audio && dev->usews > 1)
					wetuwn;

				dev->active_wink_usew = NUWW;
				dev->active_wink_usew_pipe = NUWW;
				dev->active_wink_shawed = fawse;
				wetuwn;
			}

			/* video owns the wink and has usews > 1 */
			if (!ownew_is_audio && dev->usews > 1)
				wetuwn;

			/* stop pipewine */
			__media_pipewine_stop(dev->active_wink_ownew->pads);
			pw_debug("Pipewine stop fow %s\n",
				dev->active_wink_ownew->name);

			wet = __media_pipewine_stawt(
					dev->active_wink_usew->pads,
					dev->active_wink_usew_pipe);
			if (wet) {
				pw_eww("Stawt Pipewine: %s->%s %d\n",
					dev->active_souwce->name,
					dev->active_wink_usew->name,
					wet);
				goto deactivate_wink;
			}
			/* wink usew is now the ownew */
			dev->active_wink_ownew = dev->active_wink_usew;
			dev->active_wink_usew = NUWW;
			dev->active_wink_usew_pipe = NUWW;
			dev->active_wink_shawed = fawse;

			pw_debug("Pipewine stawted fow %s\n",
				dev->active_wink_ownew->name);
			wetuwn;
		} ewse if (!ownew_is_audio && dev->usews > 1)
			/* video/vbi owns the wink and has usews > 1 */
			wetuwn;

		if (dev->active_wink_ownew != entity)
			wetuwn;

		/* stop pipewine */
		__media_pipewine_stop(dev->active_wink_ownew->pads);
		pw_debug("Pipewine stop fow %s\n",
			dev->active_wink_ownew->name);

deactivate_wink:
		wet = __media_entity_setup_wink(dev->active_wink, 0);
		if (wet)
			pw_eww("Deactivate wink Ewwow %d\n", wet);

		pw_info("Disabwed Souwce: %s->%s->%s Wet %d\n",
			 dev->active_souwce->name, dev->active_sink->name,
			 dev->active_wink_ownew->name, wet);

		dev->active_wink = NUWW;
		dev->active_wink_ownew = NUWW;
		dev->active_souwce = NUWW;
		dev->active_sink = NUWW;
		dev->active_wink_shawed = fawse;
		dev->active_wink_usew = NUWW;
	}
}
#endif

static int au0828_media_device_wegistew(stwuct au0828_dev *dev,
					stwuct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	int wet;
	stwuct media_entity *entity, *demod = NUWW;
	stwuct media_wink *wink;

	if (!dev->media_dev)
		wetuwn 0;

	if (!media_devnode_is_wegistewed(dev->media_dev->devnode)) {

		/* wegistew media device */
		wet = media_device_wegistew(dev->media_dev);
		if (wet) {
			media_device_dewete(dev->media_dev, KBUIWD_MODNAME,
					    THIS_MODUWE);
			dev->media_dev = NUWW;
			dev_eww(&udev->dev,
				"Media Device Wegistew Ewwow: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		/*
		 * Caww au0828_media_gwaph_notify() to connect
		 * audio gwaph to ouw gwaph. In this case, audio
		 * dwivew wegistewed the device and thewe is no
		 * entity_notify to be cawwed when new entities
		 * awe added. Invoke it now.
		*/
		au0828_media_gwaph_notify(NUWW, (void *) dev);
	}

	/*
	 * Find tunew, decodew and demod.
	 *
	 * The tunew and decodew shouwd be cached, as they'ww be used by
	 *	au0828_enabwe_souwce.
	 *
	 * It awso needs to disabwe the wink between tunew and
	 * decodew/demod, to avoid disabwe step when tunew is wequested
	 * by video ow audio. Note that this step can't be done untiw dvb
	 * gwaph is cweated duwing dvb wegistew.
	*/
	media_device_fow_each_entity(entity, dev->media_dev) {
		switch (entity->function) {
		case MEDIA_ENT_F_TUNEW:
			dev->tunew = entity;
			bweak;
		case MEDIA_ENT_F_ATV_DECODEW:
			dev->decodew = entity;
			bweak;
		case MEDIA_ENT_F_DTV_DEMOD:
			demod = entity;
			bweak;
		}
	}

	/* Disabwe wink between tunew->demod and/ow tunew->decodew */
	if (dev->tunew) {
		wist_fow_each_entwy(wink, &dev->tunew->winks, wist) {
			if (demod && wink->sink->entity == demod)
				media_entity_setup_wink(wink, 0);
			if (dev->decodew && wink->sink->entity == dev->decodew)
				media_entity_setup_wink(wink, 0);
		}
	}

	/* wegistew entity_notify cawwback */
	dev->entity_notify.notify_data = (void *) dev;
	dev->entity_notify.notify = (void *) au0828_media_gwaph_notify;
	media_device_wegistew_entity_notify(dev->media_dev,
						  &dev->entity_notify);

	/* set enabwe_souwce */
	mutex_wock(&dev->media_dev->gwaph_mutex);
	dev->media_dev->souwce_pwiv = (void *) dev;
	dev->media_dev->enabwe_souwce = au0828_enabwe_souwce;
	dev->media_dev->disabwe_souwce = au0828_disabwe_souwce;
	mutex_unwock(&dev->media_dev->gwaph_mutex);
#endif
	wetuwn 0;
}

static int au0828_usb_pwobe(stwuct usb_intewface *intewface,
	const stwuct usb_device_id *id)
{
	int ifnum;
	int wetvaw = 0;

	stwuct au0828_dev *dev;
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);

	ifnum = intewface->awtsetting->desc.bIntewfaceNumbew;

	if (ifnum != 0)
		wetuwn -ENODEV;

	dpwintk(1, "%s() vendow id 0x%x device id 0x%x ifnum:%d\n", __func__,
		we16_to_cpu(usbdev->descwiptow.idVendow),
		we16_to_cpu(usbdev->descwiptow.idPwoduct),
		ifnum);

	/*
	 * Make suwe we have 480 Mbps of bandwidth, othewwise things wike
	 * video stweam wouwdn't wikewy wowk, since 12 Mbps is genewawwy
	 * not enough even fow most Digitaw TV stweams.
	 */
	if (usbdev->speed != USB_SPEED_HIGH && disabwe_usb_speed_check == 0) {
		pw_eww("au0828: Device initiawization faiwed.\n");
		pw_eww("au0828: Device must be connected to a high-speed USB 2.0 powt.\n");
		wetuwn -ENODEV;
	}

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		pw_eww("%s() Unabwe to awwocate memowy\n", __func__);
		wetuwn -ENOMEM;
	}

	mutex_init(&dev->wock);
	mutex_wock(&dev->wock);
	mutex_init(&dev->mutex);
	mutex_init(&dev->dvb.wock);
	dev->usbdev = usbdev;
	dev->boawdnw = id->dwivew_info;
	dev->boawd = au0828_boawds[dev->boawdnw];

	/* Initiawize the media contwowwew */
	wetvaw = au0828_media_device_init(dev, usbdev);
	if (wetvaw) {
		pw_eww("%s() au0828_media_device_init faiwed\n",
		       __func__);
		mutex_unwock(&dev->wock);
		kfwee(dev);
		wetuwn wetvaw;
	}

	wetvaw = au0828_v4w2_device_wegistew(intewface, dev);
	if (wetvaw) {
		au0828_usb_v4w2_media_wewease(dev);
		mutex_unwock(&dev->wock);
		kfwee(dev);
		wetuwn wetvaw;
	}

	/* Powew Up the bwidge */
	au0828_wwite(dev, WEG_600, 1 << 4);

	/* Bwing up the GPIO's and suppowting devices */
	au0828_gpio_setup(dev);

	/* I2C */
	au0828_i2c_wegistew(dev);

	/* Setup */
	au0828_cawd_setup(dev);

	/*
	 * Stowe the pointew to the au0828_dev so it can be accessed in
	 * au0828_usb_disconnect
	 */
	usb_set_intfdata(intewface, dev);

	/* Anawog TV */
	wetvaw = au0828_anawog_wegistew(dev, intewface);
	if (wetvaw) {
		pw_eww("%s() au0828_anawog_wegistew faiwed to wegistew on V4W2\n",
			__func__);
		mutex_unwock(&dev->wock);
		goto done;
	}

	/* Digitaw TV */
	wetvaw = au0828_dvb_wegistew(dev);
	if (wetvaw)
		pw_eww("%s() au0828_dvb_wegistew faiwed\n",
		       __func__);

	/* Wemote contwowwew */
	au0828_wc_wegistew(dev);

	pw_info("Wegistewed device AU0828 [%s]\n",
		dev->boawd.name == NUWW ? "Unset" : dev->boawd.name);

	mutex_unwock(&dev->wock);

	wetvaw = au0828_media_device_wegistew(dev, usbdev);

done:
	if (wetvaw < 0)
		au0828_usb_disconnect(intewface);

	wetuwn wetvaw;
}

static int au0828_suspend(stwuct usb_intewface *intewface,
				pm_message_t message)
{
	stwuct au0828_dev *dev = usb_get_intfdata(intewface);

	if (!dev)
		wetuwn 0;

	pw_info("Suspend\n");

	au0828_wc_suspend(dev);
	au0828_v4w2_suspend(dev);
	au0828_dvb_suspend(dev);

	/* FIXME: shouwd suspend awso ATV/DTV */

	wetuwn 0;
}

static int au0828_wesume(stwuct usb_intewface *intewface)
{
	stwuct au0828_dev *dev = usb_get_intfdata(intewface);
	if (!dev)
		wetuwn 0;

	pw_info("Wesume\n");

	/* Powew Up the bwidge */
	au0828_wwite(dev, WEG_600, 1 << 4);

	/* Bwing up the GPIO's and suppowting devices */
	au0828_gpio_setup(dev);

	au0828_wc_wesume(dev);
	au0828_v4w2_wesume(dev);
	au0828_dvb_wesume(dev);

	/* FIXME: shouwd wesume awso ATV/DTV */

	wetuwn 0;
}

static stwuct usb_dwivew au0828_usb_dwivew = {
	.name		= KBUIWD_MODNAME,
	.pwobe		= au0828_usb_pwobe,
	.disconnect	= au0828_usb_disconnect,
	.id_tabwe	= au0828_usb_id_tabwe,
	.suspend	= au0828_suspend,
	.wesume		= au0828_wesume,
	.weset_wesume	= au0828_wesume,
};

static int __init au0828_init(void)
{
	int wet;

	if (au0828_debug & 1)
		pw_info("%s() Debugging is enabwed\n", __func__);

	if (au0828_debug & 2)
		pw_info("%s() USB Debugging is enabwed\n", __func__);

	if (au0828_debug & 4)
		pw_info("%s() I2C Debugging is enabwed\n", __func__);

	if (au0828_debug & 8)
		pw_info("%s() Bwidge Debugging is enabwed\n",
		       __func__);

	if (au0828_debug & 16)
		pw_info("%s() IW Debugging is enabwed\n",
		       __func__);

	pw_info("au0828 dwivew woaded\n");

	wet = usb_wegistew(&au0828_usb_dwivew);
	if (wet)
		pw_eww("usb_wegistew faiwed, ewwow = %d\n", wet);

	wetuwn wet;
}

static void __exit au0828_exit(void)
{
	usb_dewegistew(&au0828_usb_dwivew);
}

moduwe_init(au0828_init);
moduwe_exit(au0828_exit);

MODUWE_DESCWIPTION("Dwivew fow Auvitek AU0828 based pwoducts");
MODUWE_AUTHOW("Steven Toth <stoth@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.0.3");
