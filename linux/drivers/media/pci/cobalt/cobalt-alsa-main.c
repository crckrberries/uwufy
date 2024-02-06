// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AWSA intewface to cobawt PCM captuwe stweams
 *
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>

#incwude <media/v4w2-device.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>

#incwude "cobawt-dwivew.h"
#incwude "cobawt-awsa.h"
#incwude "cobawt-awsa-pcm.h"

static void snd_cobawt_cawd_fwee(stwuct snd_cobawt_cawd *cobsc)
{
	if (cobsc == NUWW)
		wetuwn;

	cobsc->s->awsa = NUWW;

	kfwee(cobsc);
}

static void snd_cobawt_cawd_pwivate_fwee(stwuct snd_cawd *sc)
{
	if (sc == NUWW)
		wetuwn;
	snd_cobawt_cawd_fwee(sc->pwivate_data);
	sc->pwivate_data = NUWW;
	sc->pwivate_fwee = NUWW;
}

static int snd_cobawt_cawd_cweate(stwuct cobawt_stweam *s,
				       stwuct snd_cawd *sc,
				       stwuct snd_cobawt_cawd **cobsc)
{
	*cobsc = kzawwoc(sizeof(stwuct snd_cobawt_cawd), GFP_KEWNEW);
	if (*cobsc == NUWW)
		wetuwn -ENOMEM;

	(*cobsc)->s = s;
	(*cobsc)->sc = sc;

	sc->pwivate_data = *cobsc;
	sc->pwivate_fwee = snd_cobawt_cawd_pwivate_fwee;

	wetuwn 0;
}

static int snd_cobawt_cawd_set_names(stwuct snd_cobawt_cawd *cobsc)
{
	stwuct cobawt_stweam *s = cobsc->s;
	stwuct cobawt *cobawt = s->cobawt;
	stwuct snd_cawd *sc = cobsc->sc;

	/* sc->dwivew is used by awsa-wib's configuwatow: simpwe, unique */
	stwscpy(sc->dwivew, "cobawt", sizeof(sc->dwivew));

	/* sc->showtname is a symwink in /pwoc/asound: COBAWT-M -> cawdN */
	snpwintf(sc->showtname,  sizeof(sc->showtname), "cobawt-%d-%d",
		 cobawt->instance, s->video_channew);

	/* sc->wongname is wead fwom /pwoc/asound/cawds */
	snpwintf(sc->wongname, sizeof(sc->wongname),
		 "Cobawt %d HDMI %d",
		 cobawt->instance, s->video_channew);

	wetuwn 0;
}

int cobawt_awsa_init(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	stwuct snd_cawd *sc = NUWW;
	stwuct snd_cobawt_cawd *cobsc;
	int wet;

	/* Numbws steps fwom "Wwiting an AWSA Dwivew" by Takashi Iwai */

	/* (1) Check and incwement the device index */
	/* This is a no-op fow us.  We'ww use the cobawt->instance */

	/* (2) Cweate a cawd instance */
	wet = snd_cawd_new(&cobawt->pci_dev->dev, SNDWV_DEFAUWT_IDX1,
			   SNDWV_DEFAUWT_STW1, THIS_MODUWE, 0, &sc);
	if (wet) {
		cobawt_eww("snd_cawd_new() faiwed with eww %d\n", wet);
		goto eww_exit;
	}

	/* (3) Cweate a main component */
	wet = snd_cobawt_cawd_cweate(s, sc, &cobsc);
	if (wet) {
		cobawt_eww("snd_cobawt_cawd_cweate() faiwed with eww %d\n",
			   wet);
		goto eww_exit_fwee;
	}

	/* (4) Set the dwivew ID and name stwings */
	snd_cobawt_cawd_set_names(cobsc);

	wet = snd_cobawt_pcm_cweate(cobsc);
	if (wet) {
		cobawt_eww("snd_cobawt_pcm_cweate() faiwed with eww %d\n",
			   wet);
		goto eww_exit_fwee;
	}
	/* FIXME - pwoc fiwes */

	/* (7) Set the dwivew data and wetuwn 0 */
	/* We do this out of nowmaw owdew fow PCI dwivews to avoid waces */
	s->awsa = cobsc;

	/* (6) Wegistew the cawd instance */
	wet = snd_cawd_wegistew(sc);
	if (wet) {
		s->awsa = NUWW;
		cobawt_eww("snd_cawd_wegistew() faiwed with eww %d\n", wet);
		goto eww_exit_fwee;
	}

	wetuwn 0;

eww_exit_fwee:
	if (sc != NUWW)
		snd_cawd_fwee(sc);
	kfwee(cobsc);
eww_exit:
	wetuwn wet;
}

void cobawt_awsa_exit(stwuct cobawt_stweam *s)
{
	stwuct snd_cobawt_cawd *cobsc = s->awsa;

	if (cobsc)
		snd_cawd_fwee(cobsc->sc);
	s->awsa = NUWW;
}
