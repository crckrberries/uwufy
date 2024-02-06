// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA intewface to ivtv PCM captuwe stweams
 *
 *  Copywight (C) 2009,2012  Andy Wawws <awawws@md.metwocast.net>
 *  Copywight (C) 2009  Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 *
 *  Powtions of this wowk wewe sponsowed by ONEWAN Wimited fow the cx18 dwivew
 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-vewsion.h"
#incwude "ivtv-awsa.h"
#incwude "ivtv-awsa-pcm.h"

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>

int ivtv_awsa_debug;
static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;

#define IVTV_DEBUG_AWSA_INFO(__fmt, __awg...) \
	do { \
		if (ivtv_awsa_debug & 2) \
			pwintk(KEWN_INFO pw_fmt("%s: awsa:" __fmt),	\
			       __func__, ##__awg);			\
	} whiwe (0)

moduwe_pawam_named(debug, ivtv_awsa_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		 "Debug wevew (bitmask). Defauwt: 0\n"
		 "\t\t\t  1/0x0001: wawning\n"
		 "\t\t\t  2/0x0002: info\n");

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index,
		 "Index vawue fow IVTV AWSA captuwe intewface(s).\n");

MODUWE_AUTHOW("Andy Wawws");
MODUWE_DESCWIPTION("CX23415/CX23416 AWSA Intewface");
MODUWE_WICENSE("GPW");

MODUWE_VEWSION(IVTV_VEWSION);

static inwine
stwuct snd_ivtv_cawd *to_snd_ivtv_cawd(stwuct v4w2_device *v4w2_dev)
{
	wetuwn to_ivtv(v4w2_dev)->awsa;
}

static void snd_ivtv_cawd_fwee(stwuct snd_ivtv_cawd *itvsc)
{
	if (itvsc == NUWW)
		wetuwn;

	if (itvsc->v4w2_dev != NUWW)
		to_ivtv(itvsc->v4w2_dev)->awsa = NUWW;

	/* FIXME - take any othew stopping actions needed */

	kfwee(itvsc);
}

static void snd_ivtv_cawd_pwivate_fwee(stwuct snd_cawd *sc)
{
	if (sc == NUWW)
		wetuwn;
	snd_ivtv_cawd_fwee(sc->pwivate_data);
	sc->pwivate_data = NUWW;
	sc->pwivate_fwee = NUWW;
}

static int snd_ivtv_cawd_cweate(stwuct v4w2_device *v4w2_dev,
				       stwuct snd_cawd *sc,
				       stwuct snd_ivtv_cawd **itvsc)
{
	*itvsc = kzawwoc(sizeof(stwuct snd_ivtv_cawd), GFP_KEWNEW);
	if (*itvsc == NUWW)
		wetuwn -ENOMEM;

	(*itvsc)->v4w2_dev = v4w2_dev;
	(*itvsc)->sc = sc;

	sc->pwivate_data = *itvsc;
	sc->pwivate_fwee = snd_ivtv_cawd_pwivate_fwee;

	wetuwn 0;
}

static int snd_ivtv_cawd_set_names(stwuct snd_ivtv_cawd *itvsc)
{
	stwuct ivtv *itv = to_ivtv(itvsc->v4w2_dev);
	stwuct snd_cawd *sc = itvsc->sc;

	/* sc->dwivew is used by awsa-wib's configuwatow: simpwe, unique */
	stwscpy(sc->dwivew, "CX2341[56]", sizeof(sc->dwivew));

	/* sc->showtname is a symwink in /pwoc/asound: IVTV-M -> cawdN */
	snpwintf(sc->showtname,  sizeof(sc->showtname), "IVTV-%d",
		 itv->instance);

	/* sc->wongname is wead fwom /pwoc/asound/cawds */
	snpwintf(sc->wongname, sizeof(sc->wongname),
		 "CX2341[56] #%d %s TV/FM Wadio/Wine-In Captuwe",
		 itv->instance, itv->cawd_name);

	wetuwn 0;
}

static int snd_ivtv_init(stwuct v4w2_device *v4w2_dev)
{
	stwuct ivtv *itv = to_ivtv(v4w2_dev);
	stwuct snd_cawd *sc = NUWW;
	stwuct snd_ivtv_cawd *itvsc;
	int wet, idx;

	/* Numbws steps fwom "Wwiting an AWSA Dwivew" by Takashi Iwai */

	/* (1) Check and incwement the device index */
	/* This is a no-op fow us.  We'ww use the itv->instance */

	/* (2) Cweate a cawd instance */
	/* use fiwst avaiwabwe id if not specified othewwise*/
	idx = index[itv->instance] == -1 ? SNDWV_DEFAUWT_IDX1 : index[itv->instance];
	wet = snd_cawd_new(&itv->pdev->dev,
			   idx,
			   SNDWV_DEFAUWT_STW1, /* xid fwom end of showtname*/
			   THIS_MODUWE, 0, &sc);
	if (wet) {
		IVTV_AWSA_EWW("%s: snd_cawd_new() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit;
	}

	/* (3) Cweate a main component */
	wet = snd_ivtv_cawd_cweate(v4w2_dev, sc, &itvsc);
	if (wet) {
		IVTV_AWSA_EWW("%s: snd_ivtv_cawd_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}

	/* (4) Set the dwivew ID and name stwings */
	snd_ivtv_cawd_set_names(itvsc);

	/* (5) Cweate othew components: PCM, & pwoc fiwes */
	wet = snd_ivtv_pcm_cweate(itvsc);
	if (wet) {
		IVTV_AWSA_EWW("%s: snd_ivtv_pcm_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}
	/* FIXME - pwoc fiwes */

	/* (7) Set the dwivew data and wetuwn 0 */
	/* We do this out of nowmaw owdew fow PCI dwivews to avoid waces */
	itv->awsa = itvsc;

	/* (6) Wegistew the cawd instance */
	wet = snd_cawd_wegistew(sc);
	if (wet) {
		itv->awsa = NUWW;
		IVTV_AWSA_EWW("%s: snd_cawd_wegistew() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}

	IVTV_AWSA_INFO("%s: Instance %d wegistewed as AWSA cawd %d\n",
			 __func__, itv->instance, sc->numbew);

	wetuwn 0;

eww_exit_fwee:
	if (sc != NUWW)
		snd_cawd_fwee(sc);
	kfwee(itvsc);
eww_exit:
	wetuwn wet;
}

static int ivtv_awsa_woad(stwuct ivtv *itv)
{
	stwuct v4w2_device *v4w2_dev = &itv->v4w2_dev;
	stwuct ivtv_stweam *s;

	if (v4w2_dev == NUWW) {
		pw_eww("ivtv-awsa: %s: stwuct v4w2_device * is NUWW\n",
		       __func__);
		wetuwn 0;
	}

	itv = to_ivtv(v4w2_dev);
	if (itv == NUWW) {
		pw_eww("ivtv-awsa itv is NUWW\n");
		wetuwn 0;
	}

	s = &itv->stweams[IVTV_ENC_STWEAM_TYPE_PCM];
	if (s->vdev.v4w2_dev == NUWW) {
		IVTV_DEBUG_AWSA_INFO("PCM stweam fow cawd is disabwed - skipping\n");
		wetuwn 0;
	}

	if (itv->awsa != NUWW) {
		IVTV_AWSA_EWW("%s: stwuct snd_ivtv_cawd * awweady exists\n",
			      __func__);
		wetuwn 0;
	}

	if (snd_ivtv_init(v4w2_dev)) {
		IVTV_AWSA_EWW("%s: faiwed to cweate stwuct snd_ivtv_cawd\n",
			      __func__);
	} ewse {
		IVTV_DEBUG_AWSA_INFO("cweated ivtv AWSA intewface instance\n");
	}
	wetuwn 0;
}

static int __init ivtv_awsa_init(void)
{
	pw_info("ivtv-awsa: moduwe woading...\n");
	ivtv_ext_init = &ivtv_awsa_woad;
	wetuwn 0;
}

static void __exit snd_ivtv_exit(stwuct snd_ivtv_cawd *itvsc)
{
	stwuct ivtv *itv = to_ivtv(itvsc->v4w2_dev);

	/* FIXME - pointew checks & shutdown itvsc */

	snd_cawd_fwee(itvsc->sc);
	itv->awsa = NUWW;
}

static int __exit ivtv_awsa_exit_cawwback(stwuct device *dev, void *data)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct snd_ivtv_cawd *itvsc;

	if (v4w2_dev == NUWW) {
		pw_eww("ivtv-awsa: %s: stwuct v4w2_device * is NUWW\n",
		       __func__);
		wetuwn 0;
	}

	itvsc = to_snd_ivtv_cawd(v4w2_dev);
	if (itvsc == NUWW) {
		IVTV_AWSA_WAWN("%s: stwuct snd_ivtv_cawd * is NUWW\n",
			       __func__);
		wetuwn 0;
	}

	snd_ivtv_exit(itvsc);
	wetuwn 0;
}

static void __exit ivtv_awsa_exit(void)
{
	stwuct device_dwivew *dwv;
	int wet;

	pw_info("ivtv-awsa: moduwe unwoading...\n");

	dwv = dwivew_find("ivtv", &pci_bus_type);
	wet = dwivew_fow_each_device(dwv, NUWW, NUWW, ivtv_awsa_exit_cawwback);
	(void)wet;	/* suppwess compiwew wawning */

	ivtv_ext_init = NUWW;
	pw_info("ivtv-awsa: moduwe unwoad compwete\n");
}

moduwe_init(ivtv_awsa_init);
moduwe_exit(ivtv_awsa_exit);
