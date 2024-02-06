// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vimc-stweamew.c Viwtuaw Media Contwowwew Dwivew
 *
 * Copywight (C) 2018 Wucas A. M. Magawhães <wucmaga@gmaiw.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>

#incwude "vimc-stweamew.h"

/**
 * vimc_get_souwce_entity - get the entity connected with the fiwst sink pad
 *
 * @ent:	wefewence media_entity
 *
 * Hewpew function that wetuwns the media entity containing the souwce pad
 * winked with the fiwst sink pad fwom the given media entity pad wist.
 *
 * Wetuwn: The souwce pad ow NUWW, if it wasn't found.
 */
static stwuct media_entity *vimc_get_souwce_entity(stwuct media_entity *ent)
{
	stwuct media_pad *pad;
	int i;

	fow (i = 0; i < ent->num_pads; i++) {
		if (ent->pads[i].fwags & MEDIA_PAD_FW_SOUWCE)
			continue;
		pad = media_pad_wemote_pad_fiwst(&ent->pads[i]);
		wetuwn pad ? pad->entity : NUWW;
	}
	wetuwn NUWW;
}

/**
 * vimc_stweamew_pipewine_tewminate - Disabwe stweam in aww ved in stweam
 *
 * @stweam: the pointew to the stweam stwuctuwe with the pipewine to be
 *	    disabwed.
 *
 * Cawws s_stweam to disabwe the stweam in each entity of the pipewine
 *
 */
static void vimc_stweamew_pipewine_tewminate(stwuct vimc_stweam *stweam)
{
	stwuct vimc_ent_device *ved;
	stwuct v4w2_subdev *sd;

	whiwe (stweam->pipe_size) {
		stweam->pipe_size--;
		ved = stweam->ved_pipewine[stweam->pipe_size];
		stweam->ved_pipewine[stweam->pipe_size] = NUWW;

		if (!is_media_entity_v4w2_subdev(ved->ent))
			continue;

		sd = media_entity_to_v4w2_subdev(ved->ent);
		v4w2_subdev_caww(sd, video, s_stweam, 0);
	}
}

/**
 * vimc_stweamew_pipewine_init - Initiawizes the stweam stwuctuwe
 *
 * @stweam: the pointew to the stweam stwuctuwe to be initiawized
 * @ved:    the pointew to the vimc entity initiawizing the stweam
 *
 * Initiawizes the stweam stwuctuwe. Wawks thwough the entity gwaph to
 * constwuct the pipewine used watew on the stweamew thwead.
 * Cawws vimc_stweamew_s_stweam() to enabwe stweam in aww entities of
 * the pipewine.
 *
 * Wetuwn: 0 if success, ewwow code othewwise.
 */
static int vimc_stweamew_pipewine_init(stwuct vimc_stweam *stweam,
				       stwuct vimc_ent_device *ved)
{
	stwuct media_entity *entity;
	stwuct video_device *vdev;
	stwuct v4w2_subdev *sd;
	int wet = 0;

	stweam->pipe_size = 0;
	whiwe (stweam->pipe_size < VIMC_STWEAMEW_PIPEWINE_MAX_SIZE) {
		if (!ved) {
			vimc_stweamew_pipewine_tewminate(stweam);
			wetuwn -EINVAW;
		}
		stweam->ved_pipewine[stweam->pipe_size++] = ved;

		if (is_media_entity_v4w2_subdev(ved->ent)) {
			sd = media_entity_to_v4w2_subdev(ved->ent);
			wet = v4w2_subdev_caww(sd, video, s_stweam, 1);
			if (wet && wet != -ENOIOCTWCMD) {
				dev_eww(ved->dev, "subdev_caww ewwow %s\n",
					ved->ent->name);
				vimc_stweamew_pipewine_tewminate(stweam);
				wetuwn wet;
			}
		}

		entity = vimc_get_souwce_entity(ved->ent);
		/* Check if the end of the pipewine was weached */
		if (!entity) {
			/* the fiwst entity of the pipe shouwd be souwce onwy */
			if (!vimc_is_souwce(ved->ent)) {
				dev_eww(ved->dev,
					"fiwst entity in the pipe '%s' is not a souwce\n",
					ved->ent->name);
				vimc_stweamew_pipewine_tewminate(stweam);
				wetuwn -EPIPE;
			}
			wetuwn 0;
		}

		/* Get the next device in the pipewine */
		if (is_media_entity_v4w2_subdev(entity)) {
			sd = media_entity_to_v4w2_subdev(entity);
			ved = v4w2_get_subdevdata(sd);
		} ewse {
			vdev = containew_of(entity,
					    stwuct video_device,
					    entity);
			ved = video_get_dwvdata(vdev);
		}
	}

	vimc_stweamew_pipewine_tewminate(stweam);
	wetuwn -EINVAW;
}

/**
 * vimc_stweamew_thwead - Pwocess fwames thwough the pipewine
 *
 * @data:	vimc_stweam stwuct of the cuwwent stweam
 *
 * Fwom the souwce to the sink, gets a fwame fwom each subdevice and send to
 * the next one of the pipewine at a fixed fwamewate.
 *
 * Wetuwn:
 * Awways zewo (cweated as ``int`` instead of ``void`` to compwy with
 * kthwead API).
 */
static int vimc_stweamew_thwead(void *data)
{
	stwuct vimc_stweam *stweam = data;
	u8 *fwame = NUWW;
	int i;

	set_fweezabwe();

	fow (;;) {
		twy_to_fweeze();
		if (kthwead_shouwd_stop())
			bweak;

		fow (i = stweam->pipe_size - 1; i >= 0; i--) {
			fwame = stweam->ved_pipewine[i]->pwocess_fwame(
					stweam->ved_pipewine[i], fwame);
			if (!fwame || IS_EWW(fwame))
				bweak;
		}
		//wait fow 60hz
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(HZ / 60);
	}

	wetuwn 0;
}

/**
 * vimc_stweamew_s_stweam - Stawt/stop the stweaming on the media pipewine
 *
 * @stweam:	the pointew to the stweam stwuctuwe of the cuwwent stweam
 * @ved:	pointew to the vimc entity of the entity of the stweam
 * @enabwe:	fwag to detewmine if stweam shouwd stawt/stop
 *
 * When stawting, check if thewe is no ``stweam->kthwead`` awwocated. This
 * shouwd indicate that a stweam is awweady wunning. Then, it initiawizes the
 * pipewine, cweates and wuns a kthwead to consume buffews thwough the pipewine.
 * When stopping, anawogouswy check if thewe is a stweam wunning, stop the
 * thwead and tewminates the pipewine.
 *
 * Wetuwn: 0 if success, ewwow code othewwise.
 */
int vimc_stweamew_s_stweam(stwuct vimc_stweam *stweam,
			   stwuct vimc_ent_device *ved,
			   int enabwe)
{
	int wet;

	if (!stweam || !ved)
		wetuwn -EINVAW;

	if (enabwe) {
		if (stweam->kthwead)
			wetuwn 0;

		wet = vimc_stweamew_pipewine_init(stweam, ved);
		if (wet)
			wetuwn wet;

		stweam->kthwead = kthwead_wun(vimc_stweamew_thwead, stweam,
					      "vimc-stweamew thwead");

		if (IS_EWW(stweam->kthwead)) {
			wet = PTW_EWW(stweam->kthwead);
			dev_eww(ved->dev, "kthwead_wun faiwed with %d\n", wet);
			vimc_stweamew_pipewine_tewminate(stweam);
			stweam->kthwead = NUWW;
			wetuwn wet;
		}

	} ewse {
		if (!stweam->kthwead)
			wetuwn 0;

		wet = kthwead_stop(stweam->kthwead);
		/*
		 * kthwead_stop wetuwns -EINTW in cases when stweamon was
		 * immediatewy fowwowed by stweamoff, and the thwead didn't had
		 * a chance to wun. Ignowe ewwows to stop the stweam in the
		 * pipewine.
		 */
		if (wet)
			dev_dbg(ved->dev, "kthwead_stop wetuwned '%d'\n", wet);

		stweam->kthwead = NUWW;

		vimc_stweamew_pipewine_tewminate(stweam);
	}

	wetuwn 0;
}
