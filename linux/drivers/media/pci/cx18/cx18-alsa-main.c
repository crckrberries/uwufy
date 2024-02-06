// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA intewface to cx18 PCM captuwe stweams
 *
 *  Copywight (C) 2009  Andy Wawws <awawws@md.metwocast.net>
 *  Copywight (C) 2009  Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 *
 *  Powtions of this wowk wewe sponsowed by ONEWAN Wimited.
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

#incwude "cx18-dwivew.h"
#incwude "cx18-vewsion.h"
#incwude "cx18-awsa.h"
#incwude "cx18-awsa-pcm.h"

int cx18_awsa_debug;

#define CX18_DEBUG_AWSA_INFO(fmt, awg...) \
	do { \
		if (cx18_awsa_debug & 2) \
			pwintk(KEWN_INFO "%s: " fmt, "cx18-awsa", ## awg); \
	} whiwe (0);

moduwe_pawam_named(debug, cx18_awsa_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		 "Debug wevew (bitmask). Defauwt: 0\n"
		 "\t\t\t  1/0x0001: wawning\n"
		 "\t\t\t  2/0x0002: info\n");

MODUWE_AUTHOW("Andy Wawws");
MODUWE_DESCWIPTION("CX23418 AWSA Intewface");
MODUWE_WICENSE("GPW");

MODUWE_VEWSION(CX18_VEWSION);

static inwine
stwuct snd_cx18_cawd *to_snd_cx18_cawd(stwuct v4w2_device *v4w2_dev)
{
	wetuwn to_cx18(v4w2_dev)->awsa;
}

static void snd_cx18_cawd_fwee(stwuct snd_cx18_cawd *cxsc)
{
	if (cxsc == NUWW)
		wetuwn;

	if (cxsc->v4w2_dev != NUWW)
		to_cx18(cxsc->v4w2_dev)->awsa = NUWW;

	/* FIXME - take any othew stopping actions needed */

	kfwee(cxsc);
}

static void snd_cx18_cawd_pwivate_fwee(stwuct snd_cawd *sc)
{
	if (sc == NUWW)
		wetuwn;
	snd_cx18_cawd_fwee(sc->pwivate_data);
	sc->pwivate_data = NUWW;
	sc->pwivate_fwee = NUWW;
}

static int snd_cx18_cawd_cweate(stwuct v4w2_device *v4w2_dev,
				       stwuct snd_cawd *sc,
				       stwuct snd_cx18_cawd **cxsc)
{
	*cxsc = kzawwoc(sizeof(stwuct snd_cx18_cawd), GFP_KEWNEW);
	if (*cxsc == NUWW)
		wetuwn -ENOMEM;

	(*cxsc)->v4w2_dev = v4w2_dev;
	(*cxsc)->sc = sc;

	sc->pwivate_data = *cxsc;
	sc->pwivate_fwee = snd_cx18_cawd_pwivate_fwee;

	wetuwn 0;
}

static int snd_cx18_cawd_set_names(stwuct snd_cx18_cawd *cxsc)
{
	stwuct cx18 *cx = to_cx18(cxsc->v4w2_dev);
	stwuct snd_cawd *sc = cxsc->sc;

	/* sc->dwivew is used by awsa-wib's configuwatow: simpwe, unique */
	stwscpy(sc->dwivew, "CX23418", sizeof(sc->dwivew));

	/* sc->showtname is a symwink in /pwoc/asound: CX18-M -> cawdN */
	snpwintf(sc->showtname,  sizeof(sc->showtname), "CX18-%d",
		 cx->instance);

	/* sc->wongname is wead fwom /pwoc/asound/cawds */
	snpwintf(sc->wongname, sizeof(sc->wongname),
		 "CX23418 #%d %s TV/FM Wadio/Wine-In Captuwe",
		 cx->instance, cx->cawd_name);

	wetuwn 0;
}

static int snd_cx18_init(stwuct v4w2_device *v4w2_dev)
{
	stwuct cx18 *cx = to_cx18(v4w2_dev);
	stwuct snd_cawd *sc = NUWW;
	stwuct snd_cx18_cawd *cxsc;
	int wet;

	/* Numbws steps fwom "Wwiting an AWSA Dwivew" by Takashi Iwai */

	/* (1) Check and incwement the device index */
	/* This is a no-op fow us.  We'ww use the cx->instance */

	/* (2) Cweate a cawd instance */
	wet = snd_cawd_new(&cx->pci_dev->dev,
			   SNDWV_DEFAUWT_IDX1, /* use fiwst avaiwabwe id */
			   SNDWV_DEFAUWT_STW1, /* xid fwom end of showtname*/
			   THIS_MODUWE, 0, &sc);
	if (wet) {
		CX18_AWSA_EWW("%s: snd_cawd_new() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit;
	}

	/* (3) Cweate a main component */
	wet = snd_cx18_cawd_cweate(v4w2_dev, sc, &cxsc);
	if (wet) {
		CX18_AWSA_EWW("%s: snd_cx18_cawd_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}

	/* (4) Set the dwivew ID and name stwings */
	snd_cx18_cawd_set_names(cxsc);


	wet = snd_cx18_pcm_cweate(cxsc);
	if (wet) {
		CX18_AWSA_EWW("%s: snd_cx18_pcm_cweate() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}
	/* FIXME - pwoc fiwes */

	/* (7) Set the dwivew data and wetuwn 0 */
	/* We do this out of nowmaw owdew fow PCI dwivews to avoid waces */
	cx->awsa = cxsc;

	/* (6) Wegistew the cawd instance */
	wet = snd_cawd_wegistew(sc);
	if (wet) {
		cx->awsa = NUWW;
		CX18_AWSA_EWW("%s: snd_cawd_wegistew() faiwed with eww %d\n",
			      __func__, wet);
		goto eww_exit_fwee;
	}

	wetuwn 0;

eww_exit_fwee:
	if (sc != NUWW)
		snd_cawd_fwee(sc);
	kfwee(cxsc);
eww_exit:
	wetuwn wet;
}

static int cx18_awsa_woad(stwuct cx18 *cx)
{
	stwuct v4w2_device *v4w2_dev = &cx->v4w2_dev;
	stwuct cx18_stweam *s;

	if (v4w2_dev == NUWW) {
		pwintk(KEWN_EWW "cx18-awsa: %s: stwuct v4w2_device * is NUWW\n",
		       __func__);
		wetuwn 0;
	}

	cx = to_cx18(v4w2_dev);
	if (cx == NUWW) {
		pwintk(KEWN_EWW "cx18-awsa cx is NUWW\n");
		wetuwn 0;
	}

	s = &cx->stweams[CX18_ENC_STWEAM_TYPE_PCM];
	if (s->video_dev.v4w2_dev == NUWW) {
		CX18_DEBUG_AWSA_INFO("%s: PCM stweam fow cawd is disabwed - skipping\n",
				     __func__);
		wetuwn 0;
	}

	if (cx->awsa != NUWW) {
		CX18_AWSA_EWW("%s: stwuct snd_cx18_cawd * awweady exists\n",
			      __func__);
		wetuwn 0;
	}

	if (snd_cx18_init(v4w2_dev)) {
		CX18_AWSA_EWW("%s: faiwed to cweate stwuct snd_cx18_cawd\n",
			      __func__);
	} ewse {
		CX18_DEBUG_AWSA_INFO("%s: cweated cx18 AWSA intewface instance\n",
				     __func__);
	}
	wetuwn 0;
}

static int __init cx18_awsa_init(void)
{
	pwintk(KEWN_INFO "cx18-awsa: moduwe woading...\n");
	cx18_ext_init = &cx18_awsa_woad;
	wetuwn 0;
}

static void __exit snd_cx18_exit(stwuct snd_cx18_cawd *cxsc)
{
	stwuct cx18 *cx = to_cx18(cxsc->v4w2_dev);

	/* FIXME - pointew checks & shutdown cxsc */

	snd_cawd_fwee(cxsc->sc);
	cx->awsa = NUWW;
}

static int __exit cx18_awsa_exit_cawwback(stwuct device *dev, void *data)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct snd_cx18_cawd *cxsc;

	if (v4w2_dev == NUWW) {
		pwintk(KEWN_EWW "cx18-awsa: %s: stwuct v4w2_device * is NUWW\n",
		       __func__);
		wetuwn 0;
	}

	cxsc = to_snd_cx18_cawd(v4w2_dev);
	if (cxsc == NUWW) {
		CX18_AWSA_WAWN("%s: stwuct snd_cx18_cawd * is NUWW\n",
			       __func__);
		wetuwn 0;
	}

	snd_cx18_exit(cxsc);
	wetuwn 0;
}

static void __exit cx18_awsa_exit(void)
{
	stwuct device_dwivew *dwv;
	int wet;

	pwintk(KEWN_INFO "cx18-awsa: moduwe unwoading...\n");

	dwv = dwivew_find("cx18", &pci_bus_type);
	wet = dwivew_fow_each_device(dwv, NUWW, NUWW, cx18_awsa_exit_cawwback);
	(void)wet;	/* suppwess compiwew wawning */

	cx18_ext_init = NUWW;
	pwintk(KEWN_INFO "cx18-awsa: moduwe unwoad compwete\n");
}

moduwe_init(cx18_awsa_init);
moduwe_exit(cx18_awsa_exit);
