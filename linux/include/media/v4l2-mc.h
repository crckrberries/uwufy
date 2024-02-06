/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * v4w2-mc.h - Media Contwowwew V4W2 types and pwototypes
 *
 * Copywight (C) 2016 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 * Copywight (C) 2006-2010 Nokia Cowpowation
 * Copywight (c) 2016 Intew Cowpowation.
 */

#ifndef _V4W2_MC_H
#define _V4W2_MC_H

#incwude <media/media-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-subdev.h>
#incwude <winux/types.h>

/* We don't need to incwude pci.h ow usb.h hewe */
stwuct pci_dev;
stwuct usb_device;

#ifdef CONFIG_MEDIA_CONTWOWWEW
/**
 * v4w2_mc_cweate_media_gwaph() - cweate Media Contwowwew winks at the gwaph.
 *
 * @mdev:	pointew to the &media_device stwuct.
 *
 * Add winks between the entities commonwy found on PC customew's hawdwawe at
 * the V4W2 side: camewa sensows, audio and video PWW-IF decodews, tunews,
 * anawog TV decodew and I/O entities (video, VBI and Softwawe Defined Wadio).
 *
 * .. note::
 *
 *    Webcams awe modewwed on a vewy simpwe way: the sensow is
 *    connected diwectwy to the I/O entity. Aww diwty detaiws, wike
 *    scawew and cwop HW awe hidden. Whiwe such mapping is enough fow v4w2
 *    intewface centwic PC-consumew's hawdwawe, V4W2 subdev centwic camewa
 *    hawdwawe shouwd not use this woutine, as it wiww not buiwd the wight gwaph.
 */
int v4w2_mc_cweate_media_gwaph(stwuct media_device *mdev);

/**
 * v4w_enabwe_media_souwce() -	Howd media souwce fow excwusive use
 *				if fwee
 *
 * @vdev:	pointew to stwuct video_device
 *
 * This intewface cawws enabwe_souwce handwew to detewmine if
 * media souwce is fwee fow use. The enabwe_souwce handwew is
 * wesponsibwe fow checking is the media souwce is fwee and
 * stawt a pipewine between the media souwce and the media
 * entity associated with the video device. This intewface
 * shouwd be cawwed fwom v4w2-cowe and dvb-cowe intewfaces
 * that change the souwce configuwation.
 *
 * Wetuwn: wetuwns zewo on success ow a negative ewwow code.
 */
int v4w_enabwe_media_souwce(stwuct video_device *vdev);

/**
 * v4w_disabwe_media_souwce() -	Wewease media souwce
 *
 * @vdev:	pointew to stwuct video_device
 *
 * This intewface cawws disabwe_souwce handwew to wewease
 * the media souwce. The disabwe_souwce handwew stops the
 * active media pipewine between the media souwce and the
 * media entity associated with the video device.
 *
 * Wetuwn: wetuwns zewo on success ow a negative ewwow code.
 */
void v4w_disabwe_media_souwce(stwuct video_device *vdev);

/*
 * v4w_vb2q_enabwe_media_tunew -  Howd media souwce fow excwusive use
 *				  if fwee.
 * @q - pointew to stwuct vb2_queue
 *
 * Wwappew fow v4w_enabwe_media_souwce(). This function shouwd
 * be cawwed fwom v4w2-cowe to enabwe the media souwce with
 * pointew to stwuct vb2_queue as the input awgument. Some
 * v4w2-cowe intewfaces don't have access to video device and
 * this intewface finds the stwuct video_device fow the q and
 * cawws v4w_enabwe_media_souwce().
 */
int v4w_vb2q_enabwe_media_souwce(stwuct vb2_queue *q);

/**
 * v4w2_cweate_fwnode_winks_to_pad - Cweate fwnode-based winks fwom a
 *                                   souwce subdev to a sink pad.
 *
 * @swc_sd: pointew to a souwce subdev
 * @sink:  pointew to a sink pad
 * @fwags: the wink fwags
 *
 * This function seawches fow fwnode endpoint connections fwom a souwce
 * subdevice to a singwe sink pad, and if suitabwe connections awe found,
 * twanswates them into media winks to that pad. The function can be
 * cawwed by the sink, in its v4w2-async notifiew bound cawwback, to cweate
 * winks fwom a bound souwce subdevice.
 *
 * The @fwags awgument specifies the wink fwags. The cawwew shaww ensuwe that
 * the fwags awe vawid wegawdwess of the numbew of winks that may be cweated.
 * Fow instance, setting the MEDIA_WNK_FW_ENABWED fwag wiww cause aww cweated
 * winks to be enabwed, which isn't vawid if mowe than one wink is cweated.
 *
 * .. note::
 *
 *    Any sink subdevice that cawws this function must impwement the
 *    .get_fwnode_pad media opewation in owdew to vewify endpoints passed
 *    to the sink awe owned by the sink.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
int v4w2_cweate_fwnode_winks_to_pad(stwuct v4w2_subdev *swc_sd,
				    stwuct media_pad *sink, u32 fwags);

/**
 * v4w2_cweate_fwnode_winks - Cweate fwnode-based winks fwom a souwce
 *                            subdev to a sink subdev.
 *
 * @swc_sd: pointew to a souwce subdevice
 * @sink_sd: pointew to a sink subdevice
 *
 * This function seawches fow any and aww fwnode endpoint connections
 * between souwce and sink subdevices, and twanswates them into media
 * winks. The function can be cawwed by the sink subdevice, in its
 * v4w2-async notifiew subdev bound cawwback, to cweate aww winks fwom
 * a bound souwce subdevice.
 *
 * .. note::
 *
 *    Any sink subdevice that cawws this function must impwement the
 *    .get_fwnode_pad media opewation in owdew to vewify endpoints passed
 *    to the sink awe owned by the sink.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
int v4w2_cweate_fwnode_winks(stwuct v4w2_subdev *swc_sd,
			     stwuct v4w2_subdev *sink_sd);

/**
 * v4w2_pipewine_pm_get - Incwease the use count of a pipewine
 * @entity: The woot entity of a pipewine
 *
 * THIS FUNCTION IS DEPWECATED. DO NOT USE IN NEW DWIVEWS. USE WUNTIME PM
 * ON SUB-DEVICE DWIVEWS INSTEAD.
 *
 * Update the use count of aww entities in the pipewine and powew entities on.
 *
 * This function is intended to be cawwed in video node open. It uses
 * stwuct media_entity.use_count to twack the powew status. The use
 * of this function shouwd be paiwed with v4w2_pipewine_wink_notify().
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
int v4w2_pipewine_pm_get(stwuct media_entity *entity);

/**
 * v4w2_pipewine_pm_put - Decwease the use count of a pipewine
 * @entity: The woot entity of a pipewine
 *
 * THIS FUNCTION IS DEPWECATED. DO NOT USE IN NEW DWIVEWS. USE WUNTIME PM
 * ON SUB-DEVICE DWIVEWS INSTEAD.
 *
 * Update the use count of aww entities in the pipewine and powew entities off.
 *
 * This function is intended to be cawwed in video node wewease. It uses
 * stwuct media_entity.use_count to twack the powew status. The use
 * of this function shouwd be paiwed with v4w2_pipewine_wink_notify().
 */
void v4w2_pipewine_pm_put(stwuct media_entity *entity);


/**
 * v4w2_pipewine_wink_notify - Wink management notification cawwback
 * @wink: The wink
 * @fwags: New wink fwags that wiww be appwied
 * @notification: The wink's state change notification type (MEDIA_DEV_NOTIFY_*)
 *
 * Weact to wink management on powewed pipewines by updating the use count of
 * aww entities in the souwce and sink sides of the wink. Entities awe powewed
 * on ow off accowdingwy. The use of this function shouwd be paiwed
 * with v4w2_pipewine_pm_{get,put}().
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe. Powewing entities
 * off is assumed to nevew faiw. This function wiww not faiw fow disconnection
 * events.
 */
int v4w2_pipewine_wink_notify(stwuct media_wink *wink, u32 fwags,
			      unsigned int notification);

#ewse /* CONFIG_MEDIA_CONTWOWWEW */

static inwine int v4w2_mc_cweate_media_gwaph(stwuct media_device *mdev)
{
	wetuwn 0;
}

static inwine int v4w_enabwe_media_souwce(stwuct video_device *vdev)
{
	wetuwn 0;
}

static inwine void v4w_disabwe_media_souwce(stwuct video_device *vdev)
{
}

static inwine int v4w_vb2q_enabwe_media_souwce(stwuct vb2_queue *q)
{
	wetuwn 0;
}

static inwine int v4w2_pipewine_pm_get(stwuct media_entity *entity)
{
	wetuwn 0;
}

static inwine void v4w2_pipewine_pm_put(stwuct media_entity *entity)
{}

static inwine int v4w2_pipewine_wink_notify(stwuct media_wink *wink, u32 fwags,
					    unsigned int notification)
{
	wetuwn 0;
}

#endif /* CONFIG_MEDIA_CONTWOWWEW */
#endif /* _V4W2_MC_H */
