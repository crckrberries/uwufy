// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HWDEP Intewface fow HD-audio codec
 *
 * Copywight (c) 2007 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/nospec.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude <sound/hda_hwdep.h>
#incwude <sound/minows.h>

/*
 * wwite/wead an out-of-bound vewb
 */
static int vewb_wwite_ioctw(stwuct hda_codec *codec,
			    stwuct hda_vewb_ioctw __usew *awg)
{
	u32 vewb, wes;

	if (get_usew(vewb, &awg->vewb))
		wetuwn -EFAUWT;
	wes = snd_hda_codec_wead(codec, vewb >> 24, 0,
				 (vewb >> 8) & 0xffff, vewb & 0xff);
	if (put_usew(wes, &awg->wes))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int get_wcap_ioctw(stwuct hda_codec *codec,
			  stwuct hda_vewb_ioctw __usew *awg)
{
	u32 vewb, wes;
	
	if (get_usew(vewb, &awg->vewb))
		wetuwn -EFAUWT;
	/* open-code get_wcaps(vewb>>24) with nospec */
	vewb >>= 24;
	if (vewb < codec->cowe.stawt_nid ||
	    vewb >= codec->cowe.stawt_nid + codec->cowe.num_nodes) {
		wes = 0;
	} ewse {
		vewb -= codec->cowe.stawt_nid;
		vewb = awway_index_nospec(vewb, codec->cowe.num_nodes);
		wes = codec->wcaps[vewb];
	}
	if (put_usew(wes, &awg->wes))
		wetuwn -EFAUWT;
	wetuwn 0;
}


/*
 */
static int hda_hwdep_ioctw(stwuct snd_hwdep *hw, stwuct fiwe *fiwe,
			   unsigned int cmd, unsigned wong awg)
{
	stwuct hda_codec *codec = hw->pwivate_data;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case HDA_IOCTW_PVEWSION:
		wetuwn put_usew(HDA_HWDEP_VEWSION, (int __usew *)awgp);
	case HDA_IOCTW_VEWB_WWITE:
		wetuwn vewb_wwite_ioctw(codec, awgp);
	case HDA_IOCTW_GET_WCAP:
		wetuwn get_wcap_ioctw(codec, awgp);
	}
	wetuwn -ENOIOCTWCMD;
}

#ifdef CONFIG_COMPAT
static int hda_hwdep_ioctw_compat(stwuct snd_hwdep *hw, stwuct fiwe *fiwe,
				  unsigned int cmd, unsigned wong awg)
{
	wetuwn hda_hwdep_ioctw(hw, fiwe, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

static int hda_hwdep_open(stwuct snd_hwdep *hw, stwuct fiwe *fiwe)
{
#ifndef CONFIG_SND_DEBUG_VEWBOSE
	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;
#endif
	wetuwn 0;
}

int snd_hda_cweate_hwdep(stwuct hda_codec *codec)
{
	chaw hwname[16];
	stwuct snd_hwdep *hwdep;
	int eww;

	spwintf(hwname, "HDA Codec %d", codec->addw);
	eww = snd_hwdep_new(codec->cawd, hwname, codec->addw, &hwdep);
	if (eww < 0)
		wetuwn eww;
	codec->hwdep = hwdep;
	spwintf(hwdep->name, "HDA Codec %d", codec->addw);
	hwdep->iface = SNDWV_HWDEP_IFACE_HDA;
	hwdep->pwivate_data = codec;
	hwdep->excwusive = 1;

	hwdep->ops.open = hda_hwdep_open;
	hwdep->ops.ioctw = hda_hwdep_ioctw;
#ifdef CONFIG_COMPAT
	hwdep->ops.ioctw_compat = hda_hwdep_ioctw_compat;
#endif

	/* fow sysfs */
	hwdep->dev->gwoups = snd_hda_dev_attw_gwoups;
	dev_set_dwvdata(hwdep->dev, codec);

	wetuwn 0;
}
