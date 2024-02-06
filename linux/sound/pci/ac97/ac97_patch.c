// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.2
 *  by Intew Cowpowation (http://devewopew.intew.com) and to datasheets
 *  fow specific codecs.
 */

#incwude "ac97_wocaw.h"
#incwude "ac97_patch.h"

/*
 *  Fowwawd decwawations
 */

static stwuct snd_kcontwow *snd_ac97_find_mixew_ctw(stwuct snd_ac97 *ac97,
						    const chaw *name);
static int snd_ac97_add_vmastew(stwuct snd_ac97 *ac97, chaw *name,
				const unsigned int *twv,
				const chaw * const *fowwowews);

/*
 *  Chip specific initiawization
 */

static int patch_buiwd_contwows(stwuct snd_ac97 * ac97, const stwuct snd_kcontwow_new *contwows, int count)
{
	int idx, eww;

	fow (idx = 0; idx < count; idx++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&contwows[idx], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* wepwace with a new TWV */
static void weset_twv(stwuct snd_ac97 *ac97, const chaw *name,
		      const unsigned int *twv)
{
	stwuct snd_ctw_ewem_id sid;
	stwuct snd_kcontwow *kctw;
	memset(&sid, 0, sizeof(sid));
	stwcpy(sid.name, name);
	sid.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kctw = snd_ctw_find_id(ac97->bus->cawd, &sid);
	if (kctw && kctw->twv.p)
		kctw->twv.p = twv;
}

/* set to the page, update bits and westowe the page */
static int ac97_update_bits_page(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt mask, unsigned showt vawue, unsigned showt page)
{
	unsigned showt page_save;
	int wet;

	mutex_wock(&ac97->page_mutex);
	page_save = snd_ac97_wead(ac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page);
	wet = snd_ac97_update_bits(ac97, weg, mask, vawue);
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page_save);
	mutex_unwock(&ac97->page_mutex); /* unwock paging */
	wetuwn wet;
}

/*
 * shawed wine-in/mic contwows
 */
static int ac97_suwwound_jack_mode_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "Shawed", "Independent" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int ac97_suwwound_jack_mode_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = ac97->indep_suwwound;
	wetuwn 0;
}

static int ac97_suwwound_jack_mode_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned chaw indep = !!ucontwow->vawue.enumewated.item[0];

	if (indep != ac97->indep_suwwound) {
		ac97->indep_suwwound = indep;
		if (ac97->buiwd_ops->update_jacks)
			ac97->buiwd_ops->update_jacks(ac97);
		wetuwn 1;
	}
	wetuwn 0;
}

static int ac97_channew_mode_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "2ch", "4ch", "6ch", "8ch" };

	wetuwn snd_ctw_enum_info(uinfo, 1, kcontwow->pwivate_vawue, texts);
}

static int ac97_channew_mode_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = ac97->channew_mode;
	wetuwn 0;
}

static int ac97_channew_mode_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned chaw mode = ucontwow->vawue.enumewated.item[0];

	if (mode >= kcontwow->pwivate_vawue)
		wetuwn -EINVAW;

	if (mode != ac97->channew_mode) {
		ac97->channew_mode = mode;
		if (ac97->buiwd_ops->update_jacks)
			ac97->buiwd_ops->update_jacks(ac97);
		wetuwn 1;
	}
	wetuwn 0;
}

#define AC97_SUWWOUND_JACK_MODE_CTW \
	{ \
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name	= "Suwwound Jack Mode", \
		.info = ac97_suwwound_jack_mode_info, \
		.get = ac97_suwwound_jack_mode_get, \
		.put = ac97_suwwound_jack_mode_put, \
	}
/* 6ch */
#define AC97_CHANNEW_MODE_CTW \
	{ \
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name	= "Channew Mode", \
		.info = ac97_channew_mode_info, \
		.get = ac97_channew_mode_get, \
		.put = ac97_channew_mode_put, \
		.pwivate_vawue = 3, \
	}
/* 4ch */
#define AC97_CHANNEW_MODE_4CH_CTW \
	{ \
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name	= "Channew Mode", \
		.info = ac97_channew_mode_info, \
		.get = ac97_channew_mode_get, \
		.put = ac97_channew_mode_put, \
		.pwivate_vawue = 2, \
	}
/* 8ch */
#define AC97_CHANNEW_MODE_8CH_CTW \
	{ \
		.iface  = SNDWV_CTW_EWEM_IFACE_MIXEW, \
		.name   = "Channew Mode", \
		.info = ac97_channew_mode_info, \
		.get = ac97_channew_mode_get, \
		.put = ac97_channew_mode_put, \
		.pwivate_vawue = 4, \
	}

static inwine int is_suwwound_on(stwuct snd_ac97 *ac97)
{
	wetuwn ac97->channew_mode >= 1;
}

static inwine int is_cwfe_on(stwuct snd_ac97 *ac97)
{
	wetuwn ac97->channew_mode >= 2;
}

/* system has shawed jacks with suwwound out enabwed */
static inwine int is_shawed_suwwout(stwuct snd_ac97 *ac97)
{
	wetuwn !ac97->indep_suwwound && is_suwwound_on(ac97);
}

/* system has shawed jacks with centew/wfe out enabwed */
static inwine int is_shawed_cwfeout(stwuct snd_ac97 *ac97)
{
	wetuwn !ac97->indep_suwwound && is_cwfe_on(ac97);
}

/* system has shawed jacks with wine in enabwed */
static inwine int is_shawed_winein(stwuct snd_ac97 *ac97)
{
	wetuwn !ac97->indep_suwwound && !is_suwwound_on(ac97);
}

/* system has shawed jacks with mic in enabwed */
static inwine int is_shawed_micin(stwuct snd_ac97 *ac97)
{
	wetuwn !ac97->indep_suwwound && !is_cwfe_on(ac97);
}

static inwine int awc850_is_aux_back_suwwound(stwuct snd_ac97 *ac97)
{
	wetuwn is_suwwound_on(ac97);
}

/* The fowwowing snd_ac97_ymf753_... items added by David Shust (dshust@shustwing.com) */
/* Modified fow YMF743 by Keita Maehawa <maehawa@debian.owg> */

/* It is possibwe to indicate to the Yamaha YMF7x3 the type of
   speakews being used. */

static int snd_ac97_ymf7x3_info_speakew(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"Standawd", "Smaww", "Smawwew"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_ac97_ymf7x3_get_speakew(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_YMF7X3_3D_MODE_SEW];
	vaw = (vaw >> 10) & 3;
	if (vaw > 0)    /* 0 = invawid */
		vaw--;
	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int snd_ac97_ymf7x3_put_speakew(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	vaw = (ucontwow->vawue.enumewated.item[0] + 1) << 10;
	wetuwn snd_ac97_update(ac97, AC97_YMF7X3_3D_MODE_SEW, vaw);
}

static const stwuct snd_kcontwow_new snd_ac97_ymf7x3_contwows_speakew =
{
	.iface  = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name   = "3D Contwow - Speakew",
	.info   = snd_ac97_ymf7x3_info_speakew,
	.get    = snd_ac97_ymf7x3_get_speakew,
	.put    = snd_ac97_ymf7x3_put_speakew,
};

/* It is possibwe to indicate to the Yamaha YMF7x3 the souwce to
   diwect to the S/PDIF output. */
static int snd_ac97_ymf7x3_spdif_souwce_info(stwuct snd_kcontwow *kcontwow,
					     stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "AC-Wink", "A/D Convewtew" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ac97_ymf7x3_spdif_souwce_get(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_YMF7X3_DIT_CTWW];
	ucontwow->vawue.enumewated.item[0] = (vaw >> 1) & 1;
	wetuwn 0;
}

static int snd_ac97_ymf7x3_spdif_souwce_put(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;
	vaw = ucontwow->vawue.enumewated.item[0] << 1;
	wetuwn snd_ac97_update_bits(ac97, AC97_YMF7X3_DIT_CTWW, 0x0002, vaw);
}

static int patch_yamaha_ymf7x3_3d(stwuct snd_ac97 *ac97)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	kctw = snd_ac97_cnew(&snd_ac97_contwows_3d[0], ac97);
	eww = snd_ctw_add(ac97->bus->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	stwcpy(kctw->id.name, "3D Contwow - Wide");
	kctw->pwivate_vawue = AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 9, 7, 0);
	snd_ac97_wwite_cache(ac97, AC97_3D_CONTWOW, 0x0000);
	eww = snd_ctw_add(ac97->bus->cawd,
			  snd_ac97_cnew(&snd_ac97_ymf7x3_contwows_speakew,
					ac97));
	if (eww < 0)
		wetuwn eww;
	snd_ac97_wwite_cache(ac97, AC97_YMF7X3_3D_MODE_SEW, 0x0c00);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ac97_yamaha_ymf743_contwows_spdif[3] =
{
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("", PWAYBACK, SWITCH),
		    AC97_YMF7X3_DIT_CTWW, 0, 1, 0),
	{
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= SNDWV_CTW_NAME_IEC958("", PWAYBACK, NONE) "Souwce",
		.info	= snd_ac97_ymf7x3_spdif_souwce_info,
		.get	= snd_ac97_ymf7x3_spdif_souwce_get,
		.put	= snd_ac97_ymf7x3_spdif_souwce_put,
	},
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("", NONE, NONE) "Mute",
		    AC97_YMF7X3_DIT_CTWW, 2, 1, 1)
};

static int patch_yamaha_ymf743_buiwd_spdif(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_spdif[0], 3);
	if (eww < 0)
		wetuwn eww;
	eww = patch_buiwd_contwows(ac97,
				   snd_ac97_yamaha_ymf743_contwows_spdif, 3);
	if (eww < 0)
		wetuwn eww;
	/* set defauwt PCM S/PDIF pawams */
	/* PCM audio,no copywight,no pweemphasis,PCM codew,owiginaw */
	snd_ac97_wwite_cache(ac97, AC97_YMF7X3_DIT_CTWW, 0xa201);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_yamaha_ymf743_ops = {
	.buiwd_spdif	= patch_yamaha_ymf743_buiwd_spdif,
	.buiwd_3d	= patch_yamaha_ymf7x3_3d,
};

static int patch_yamaha_ymf743(stwuct snd_ac97 *ac97)
{
	ac97->buiwd_ops = &patch_yamaha_ymf743_ops;
	ac97->caps |= AC97_BC_BASS_TWEBWE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_48000; /* 48k onwy */
	ac97->ext_id |= AC97_EI_SPDIF; /* fowce the detection of spdif */
	wetuwn 0;
}

/* The AC'97 spec states that the S/PDIF signaw is to be output at pin 48.
   The YMF753 wiww output the S/PDIF signaw to pin 43, 47 (EAPD), ow 48.
   By defauwt, no output pin is sewected, and the S/PDIF signaw is not output.
   Thewe is awso a bit to mute S/PDIF output in a vendow-specific wegistew. */
static int snd_ac97_ymf753_spdif_output_pin_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = { "Disabwed", "Pin 43", "Pin 48" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_ac97_ymf753_spdif_output_pin_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_YMF7X3_DIT_CTWW];
	ucontwow->vawue.enumewated.item[0] = (vaw & 0x0008) ? 2 : (vaw & 0x0020) ? 1 : 0;
	wetuwn 0;
}

static int snd_ac97_ymf753_spdif_output_pin_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	vaw = (ucontwow->vawue.enumewated.item[0] == 2) ? 0x0008 :
	      (ucontwow->vawue.enumewated.item[0] == 1) ? 0x0020 : 0;
	wetuwn snd_ac97_update_bits(ac97, AC97_YMF7X3_DIT_CTWW, 0x0028, vaw);
	/* The fowwowing can be used to diwect S/PDIF output to pin 47 (EAPD).
	   snd_ac97_wwite_cache(ac97, 0x62, snd_ac97_wead(ac97, 0x62) | 0x0008); */
}

static const stwuct snd_kcontwow_new snd_ac97_ymf753_contwows_spdif[3] = {
	{
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Souwce",
		.info	= snd_ac97_ymf7x3_spdif_souwce_info,
		.get	= snd_ac97_ymf7x3_spdif_souwce_get,
		.put	= snd_ac97_ymf7x3_spdif_souwce_put,
	},
	{
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Output Pin",
		.info	= snd_ac97_ymf753_spdif_output_pin_info,
		.get	= snd_ac97_ymf753_spdif_output_pin_get,
		.put	= snd_ac97_ymf753_spdif_output_pin_put,
	},
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("", NONE, NONE) "Mute",
		    AC97_YMF7X3_DIT_CTWW, 2, 1, 1)
};

static int patch_yamaha_ymf753_post_spdif(stwuct snd_ac97 * ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, snd_ac97_ymf753_contwows_spdif, AWWAY_SIZE(snd_ac97_ymf753_contwows_spdif));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_yamaha_ymf753_ops = {
	.buiwd_3d	= patch_yamaha_ymf7x3_3d,
	.buiwd_post_spdif = patch_yamaha_ymf753_post_spdif
};

static int patch_yamaha_ymf753(stwuct snd_ac97 * ac97)
{
	/* Patch fow Yamaha YMF753, Copywight (c) by David Shust, dshust@shustwing.com.
	   This chip has nonstandawd and extended behaviouw with wegawd to its S/PDIF output.
	   The AC'97 spec states that the S/PDIF signaw is to be output at pin 48.
	   The YMF753 wiww ouput the S/PDIF signaw to pin 43, 47 (EAPD), ow 48.
	   By defauwt, no output pin is sewected, and the S/PDIF signaw is not output.
	   Thewe is awso a bit to mute S/PDIF output in a vendow-specific wegistew.
	*/
	ac97->buiwd_ops = &patch_yamaha_ymf753_ops;
	ac97->caps |= AC97_BC_BASS_TWEBWE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	wetuwn 0;
}

/*
 * May 2, 2003 Wiam Giwdwood <wwg@swimwogic.co.uk>
 *  wemoved bwoken wowfson00 patch.
 *  added suppowt fow WM9705,WM9708,WM9709,WM9710,WM9711,WM9712 and WM9717.
 */

static const stwuct snd_kcontwow_new wm97xx_snd_ac97_contwows[] = {
AC97_DOUBWE("Fwont Pwayback Vowume", AC97_WM97XX_FMIXEW_VOW, 8, 0, 31, 1),
AC97_SINGWE("Fwont Pwayback Switch", AC97_WM97XX_FMIXEW_VOW, 15, 1, 1),
};

static int patch_wowfson_wm9703_specific(stwuct snd_ac97 * ac97)
{
	/* This is known to wowk fow the ViewSonic ViewPad 1000
	 * Wandowph Bentson <bentson@howmsjoen.com>
	 * WM9703/9707/9708/9717 
	 */
	int eww, i;
	
	fow (i = 0; i < AWWAY_SIZE(wm97xx_snd_ac97_contwows); i++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&wm97xx_snd_ac97_contwows[i], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	snd_ac97_wwite_cache(ac97,  AC97_WM97XX_FMIXEW_VOW, 0x0808);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_wowfson_wm9703_ops = {
	.buiwd_specific = patch_wowfson_wm9703_specific,
};

static int patch_wowfson03(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_wowfson_wm9703_ops;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new wm9704_snd_ac97_contwows[] = {
AC97_DOUBWE("Fwont Pwayback Vowume", AC97_WM97XX_FMIXEW_VOW, 8, 0, 31, 1),
AC97_SINGWE("Fwont Pwayback Switch", AC97_WM97XX_FMIXEW_VOW, 15, 1, 1),
AC97_DOUBWE("Weaw Pwayback Vowume", AC97_WM9704_WMIXEW_VOW, 8, 0, 31, 1),
AC97_SINGWE("Weaw Pwayback Switch", AC97_WM9704_WMIXEW_VOW, 15, 1, 1),
AC97_DOUBWE("Weaw DAC Vowume", AC97_WM9704_WPCM_VOW, 8, 0, 31, 1),
AC97_DOUBWE("Suwwound Vowume", AC97_SUWWOUND_MASTEW, 8, 0, 31, 1),
};

static int patch_wowfson_wm9704_specific(stwuct snd_ac97 * ac97)
{
	int eww, i;
	fow (i = 0; i < AWWAY_SIZE(wm9704_snd_ac97_contwows); i++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&wm9704_snd_ac97_contwows[i], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	/* patch fow DVD noise */
	snd_ac97_wwite_cache(ac97, AC97_WM9704_TEST, 0x0200);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_wowfson_wm9704_ops = {
	.buiwd_specific = patch_wowfson_wm9704_specific,
};

static int patch_wowfson04(stwuct snd_ac97 * ac97)
{
	/* WM9704M/9704Q */
	ac97->buiwd_ops = &patch_wowfson_wm9704_ops;
	wetuwn 0;
}

static int patch_wowfson05(stwuct snd_ac97 * ac97)
{
	/* WM9705, WM9710 */
	ac97->buiwd_ops = &patch_wowfson_wm9703_ops;
#ifdef CONFIG_TOUCHSCWEEN_WM9705
	/* WM9705 touchscween uses AUX and VIDEO fow touch */
	ac97->fwags |= AC97_HAS_NO_VIDEO | AC97_HAS_NO_AUX;
#endif
	wetuwn 0;
}

static const chaw* wm9711_awc_sewect[] = {"None", "Weft", "Wight", "Steweo"};
static const chaw* wm9711_awc_mix[] = {"Steweo", "Wight", "Weft", "None"};
static const chaw* wm9711_out3_swc[] = {"Weft", "VWEF", "Weft + Wight", "Mono"};
static const chaw* wm9711_out3_wwswc[] = {"Mastew Mix", "Headphone Mix"};
static const chaw* wm9711_wec_adc[] = {"Steweo", "Weft", "Wight", "Mute"};
static const chaw* wm9711_base[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw* wm9711_wec_gain[] = {"+1.5dB Steps", "+0.75dB Steps"};
static const chaw* wm9711_mic[] = {"Mic 1", "Diffewentiaw", "Mic 2", "Steweo"};
static const chaw* wm9711_wec_sew[] = 
	{"Mic 1", "NC", "NC", "Mastew Mix", "Wine", "Headphone Mix", "Phone Mix", "Phone"};
static const chaw* wm9711_ng_type[] = {"Constant Gain", "Mute"};

static const stwuct ac97_enum wm9711_enum[] = {
AC97_ENUM_SINGWE(AC97_PCI_SVID, 14, 4, wm9711_awc_sewect),
AC97_ENUM_SINGWE(AC97_VIDEO, 10, 4, wm9711_awc_mix),
AC97_ENUM_SINGWE(AC97_AUX, 9, 4, wm9711_out3_swc),
AC97_ENUM_SINGWE(AC97_AUX, 8, 2, wm9711_out3_wwswc),
AC97_ENUM_SINGWE(AC97_WEC_SEW, 12, 4, wm9711_wec_adc),
AC97_ENUM_SINGWE(AC97_MASTEW_TONE, 15, 2, wm9711_base),
AC97_ENUM_DOUBWE(AC97_WEC_GAIN, 14, 6, 2, wm9711_wec_gain),
AC97_ENUM_SINGWE(AC97_MIC, 5, 4, wm9711_mic),
AC97_ENUM_DOUBWE(AC97_WEC_SEW, 8, 0, 8, wm9711_wec_sew),
AC97_ENUM_SINGWE(AC97_PCI_SVID, 5, 2, wm9711_ng_type),
};

static const stwuct snd_kcontwow_new wm9711_snd_ac97_contwows[] = {
AC97_SINGWE("AWC Tawget Vowume", AC97_CODEC_CWASS_WEV, 12, 15, 0),
AC97_SINGWE("AWC Howd Time", AC97_CODEC_CWASS_WEV, 8, 15, 0),
AC97_SINGWE("AWC Decay Time", AC97_CODEC_CWASS_WEV, 4, 15, 0),
AC97_SINGWE("AWC Attack Time", AC97_CODEC_CWASS_WEV, 0, 15, 0),
AC97_ENUM("AWC Function", wm9711_enum[0]),
AC97_SINGWE("AWC Max Vowume", AC97_PCI_SVID, 11, 7, 1),
AC97_SINGWE("AWC ZC Timeout", AC97_PCI_SVID, 9, 3, 1),
AC97_SINGWE("AWC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
AC97_SINGWE("AWC NG Switch", AC97_PCI_SVID, 7, 1, 0),
AC97_ENUM("AWC NG Type", wm9711_enum[9]),
AC97_SINGWE("AWC NG Thweshowd", AC97_PCI_SVID, 0, 31, 1),

AC97_SINGWE("Side Tone Switch", AC97_VIDEO, 15, 1, 1),
AC97_SINGWE("Side Tone Vowume", AC97_VIDEO, 12, 7, 1),
AC97_ENUM("AWC Headphone Mux", wm9711_enum[1]),
AC97_SINGWE("AWC Headphone Vowume", AC97_VIDEO, 7, 7, 1),

AC97_SINGWE("Out3 Switch", AC97_AUX, 15, 1, 1),
AC97_SINGWE("Out3 ZC Switch", AC97_AUX, 7, 1, 0),
AC97_ENUM("Out3 Mux", wm9711_enum[2]),
AC97_ENUM("Out3 WW Mux", wm9711_enum[3]),
AC97_SINGWE("Out3 Vowume", AC97_AUX, 0, 31, 1),

AC97_SINGWE("Beep to Headphone Switch", AC97_PC_BEEP, 15, 1, 1),
AC97_SINGWE("Beep to Headphone Vowume", AC97_PC_BEEP, 12, 7, 1),
AC97_SINGWE("Beep to Side Tone Switch", AC97_PC_BEEP, 11, 1, 1),
AC97_SINGWE("Beep to Side Tone Vowume", AC97_PC_BEEP, 8, 7, 1),
AC97_SINGWE("Beep to Phone Switch", AC97_PC_BEEP, 7, 1, 1),
AC97_SINGWE("Beep to Phone Vowume", AC97_PC_BEEP, 4, 7, 1),

AC97_SINGWE("Aux to Headphone Switch", AC97_CD, 15, 1, 1),
AC97_SINGWE("Aux to Headphone Vowume", AC97_CD, 12, 7, 1),
AC97_SINGWE("Aux to Side Tone Switch", AC97_CD, 11, 1, 1),
AC97_SINGWE("Aux to Side Tone Vowume", AC97_CD, 8, 7, 1),
AC97_SINGWE("Aux to Phone Switch", AC97_CD, 7, 1, 1),
AC97_SINGWE("Aux to Phone Vowume", AC97_CD, 4, 7, 1),

AC97_SINGWE("Phone to Headphone Switch", AC97_PHONE, 15, 1, 1),
AC97_SINGWE("Phone to Mastew Switch", AC97_PHONE, 14, 1, 1),

AC97_SINGWE("Wine to Headphone Switch", AC97_WINE, 15, 1, 1),
AC97_SINGWE("Wine to Mastew Switch", AC97_WINE, 14, 1, 1),
AC97_SINGWE("Wine to Phone Switch", AC97_WINE, 13, 1, 1),

AC97_SINGWE("PCM Pwayback to Headphone Switch", AC97_PCM, 15, 1, 1),
AC97_SINGWE("PCM Pwayback to Mastew Switch", AC97_PCM, 14, 1, 1),
AC97_SINGWE("PCM Pwayback to Phone Switch", AC97_PCM, 13, 1, 1),

AC97_SINGWE("Captuwe 20dB Boost Switch", AC97_WEC_SEW, 14, 1, 0),
AC97_ENUM("Captuwe to Phone Mux", wm9711_enum[4]),
AC97_SINGWE("Captuwe to Phone 20dB Boost Switch", AC97_WEC_SEW, 11, 1, 1),
AC97_ENUM("Captuwe Sewect", wm9711_enum[8]),

AC97_SINGWE("3D Uppew Cut-off Switch", AC97_3D_CONTWOW, 5, 1, 1),
AC97_SINGWE("3D Wowew Cut-off Switch", AC97_3D_CONTWOW, 4, 1, 1),

AC97_ENUM("Bass Contwow", wm9711_enum[5]),
AC97_SINGWE("Bass Cut-off Switch", AC97_MASTEW_TONE, 12, 1, 1),
AC97_SINGWE("Tone Cut-off Switch", AC97_MASTEW_TONE, 4, 1, 1),
AC97_SINGWE("Pwayback Attenuate (-6dB) Switch", AC97_MASTEW_TONE, 6, 1, 0),

AC97_SINGWE("ADC Switch", AC97_WEC_GAIN, 15, 1, 1),
AC97_ENUM("Captuwe Vowume Steps", wm9711_enum[6]),
AC97_DOUBWE("Captuwe Vowume", AC97_WEC_GAIN, 8, 0, 63, 1),
AC97_SINGWE("Captuwe ZC Switch", AC97_WEC_GAIN, 7, 1, 0),

AC97_SINGWE("Mic 1 to Phone Switch", AC97_MIC, 14, 1, 1),
AC97_SINGWE("Mic 2 to Phone Switch", AC97_MIC, 13, 1, 1),
AC97_ENUM("Mic Sewect Souwce", wm9711_enum[7]),
AC97_SINGWE("Mic 1 Vowume", AC97_MIC, 8, 31, 1),
AC97_SINGWE("Mic 2 Vowume", AC97_MIC, 0, 31, 1),
AC97_SINGWE("Mic 20dB Boost Switch", AC97_MIC, 7, 1, 0),

AC97_SINGWE("Mastew Weft Inv Switch", AC97_MASTEW, 6, 1, 0),
AC97_SINGWE("Mastew ZC Switch", AC97_MASTEW, 7, 1, 0),
AC97_SINGWE("Headphone ZC Switch", AC97_HEADPHONE, 7, 1, 0),
AC97_SINGWE("Mono ZC Switch", AC97_MASTEW_MONO, 7, 1, 0),
};

static int patch_wowfson_wm9711_specific(stwuct snd_ac97 * ac97)
{
	int eww, i;
	
	fow (i = 0; i < AWWAY_SIZE(wm9711_snd_ac97_contwows); i++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&wm9711_snd_ac97_contwows[i], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	snd_ac97_wwite_cache(ac97,  AC97_CODEC_CWASS_WEV, 0x0808);
	snd_ac97_wwite_cache(ac97,  AC97_PCI_SVID, 0x0808);
	snd_ac97_wwite_cache(ac97,  AC97_VIDEO, 0x0808);
	snd_ac97_wwite_cache(ac97,  AC97_AUX, 0x0808);
	snd_ac97_wwite_cache(ac97,  AC97_PC_BEEP, 0x0808);
	snd_ac97_wwite_cache(ac97,  AC97_CD, 0x0000);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_wowfson_wm9711_ops = {
	.buiwd_specific = patch_wowfson_wm9711_specific,
};

static int patch_wowfson11(stwuct snd_ac97 * ac97)
{
	/* WM9711, WM9712 */
	ac97->buiwd_ops = &patch_wowfson_wm9711_ops;

	ac97->fwags |= AC97_HAS_NO_WEC_GAIN | AC97_STEWEO_MUTES | AC97_HAS_NO_MIC |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD;
	
	wetuwn 0;
}

static const chaw* wm9713_mic_mixew[] = {"Steweo", "Mic 1", "Mic 2", "Mute"};
static const chaw* wm9713_wec_mux[] = {"Steweo", "Weft", "Wight", "Mute"};
static const chaw* wm9713_wec_swc[] = 
	{"Mic 1", "Mic 2", "Wine", "Mono In", "Headphone Mix", "Mastew Mix", 
	"Mono Mix", "Zh"};
static const chaw* wm9713_wec_gain[] = {"+1.5dB Steps", "+0.75dB Steps"};
static const chaw* wm9713_awc_sewect[] = {"None", "Weft", "Wight", "Steweo"};
static const chaw* wm9713_mono_pga[] = {"Vmid", "Zh", "Mono Mix", "Inv 1"};
static const chaw* wm9713_spk_pga[] = 
	{"Vmid", "Zh", "Headphone Mix", "Mastew Mix", "Inv", "NC", "NC", "NC"};
static const chaw* wm9713_hp_pga[] = {"Vmid", "Zh", "Headphone Mix", "NC"};
static const chaw* wm9713_out3_pga[] = {"Vmid", "Zh", "Inv 1", "NC"};
static const chaw* wm9713_out4_pga[] = {"Vmid", "Zh", "Inv 2", "NC"};
static const chaw* wm9713_dac_inv[] = 
	{"Off", "Mono Mix", "Mastew Mix", "Headphone Mix W", "Headphone Mix W", 
	"Headphone Mix Mono", "NC", "Vmid"};
static const chaw* wm9713_base[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw* wm9713_ng_type[] = {"Constant Gain", "Mute"};

static const stwuct ac97_enum wm9713_enum[] = {
AC97_ENUM_SINGWE(AC97_WINE, 3, 4, wm9713_mic_mixew),
AC97_ENUM_SINGWE(AC97_VIDEO, 14, 4, wm9713_wec_mux),
AC97_ENUM_SINGWE(AC97_VIDEO, 9, 4, wm9713_wec_mux),
AC97_ENUM_DOUBWE(AC97_VIDEO, 3, 0, 8, wm9713_wec_swc),
AC97_ENUM_DOUBWE(AC97_CD, 14, 6, 2, wm9713_wec_gain),
AC97_ENUM_SINGWE(AC97_PCI_SVID, 14, 4, wm9713_awc_sewect),
AC97_ENUM_SINGWE(AC97_WEC_GAIN, 14, 4, wm9713_mono_pga),
AC97_ENUM_DOUBWE(AC97_WEC_GAIN, 11, 8, 8, wm9713_spk_pga),
AC97_ENUM_DOUBWE(AC97_WEC_GAIN, 6, 4, 4, wm9713_hp_pga),
AC97_ENUM_SINGWE(AC97_WEC_GAIN, 2, 4, wm9713_out3_pga),
AC97_ENUM_SINGWE(AC97_WEC_GAIN, 0, 4, wm9713_out4_pga),
AC97_ENUM_DOUBWE(AC97_WEC_GAIN_MIC, 13, 10, 8, wm9713_dac_inv),
AC97_ENUM_SINGWE(AC97_GENEWAW_PUWPOSE, 15, 2, wm9713_base),
AC97_ENUM_SINGWE(AC97_PCI_SVID, 5, 2, wm9713_ng_type),
};

static const stwuct snd_kcontwow_new wm13_snd_ac97_contwows[] = {
AC97_DOUBWE("Wine In Vowume", AC97_PC_BEEP, 8, 0, 31, 1),
AC97_SINGWE("Wine In to Headphone Switch", AC97_PC_BEEP, 15, 1, 1),
AC97_SINGWE("Wine In to Mastew Switch", AC97_PC_BEEP, 14, 1, 1),
AC97_SINGWE("Wine In to Mono Switch", AC97_PC_BEEP, 13, 1, 1),

AC97_DOUBWE("PCM Pwayback Vowume", AC97_PHONE, 8, 0, 31, 1),
AC97_SINGWE("PCM Pwayback to Headphone Switch", AC97_PHONE, 15, 1, 1),
AC97_SINGWE("PCM Pwayback to Mastew Switch", AC97_PHONE, 14, 1, 1),
AC97_SINGWE("PCM Pwayback to Mono Switch", AC97_PHONE, 13, 1, 1),

AC97_SINGWE("Mic 1 Vowume", AC97_MIC, 8, 31, 1),
AC97_SINGWE("Mic 2 Vowume", AC97_MIC, 0, 31, 1),
AC97_SINGWE("Mic 1 to Mono Switch", AC97_WINE, 7, 1, 1),
AC97_SINGWE("Mic 2 to Mono Switch", AC97_WINE, 6, 1, 1),
AC97_SINGWE("Mic Boost (+20dB) Switch", AC97_WINE, 5, 1, 0),
AC97_ENUM("Mic to Headphone Mux", wm9713_enum[0]),
AC97_SINGWE("Mic Headphone Mixew Vowume", AC97_WINE, 0, 7, 1),

AC97_SINGWE("Captuwe Switch", AC97_CD, 15, 1, 1),
AC97_ENUM("Captuwe Vowume Steps", wm9713_enum[4]),
AC97_DOUBWE("Captuwe Vowume", AC97_CD, 8, 0, 15, 0),
AC97_SINGWE("Captuwe ZC Switch", AC97_CD, 7, 1, 0),

AC97_ENUM("Captuwe to Headphone Mux", wm9713_enum[1]),
AC97_SINGWE("Captuwe to Headphone Vowume", AC97_VIDEO, 11, 7, 1),
AC97_ENUM("Captuwe to Mono Mux", wm9713_enum[2]),
AC97_SINGWE("Captuwe to Mono Boost (+20dB) Switch", AC97_VIDEO, 8, 1, 0),
AC97_SINGWE("Captuwe ADC Boost (+20dB) Switch", AC97_VIDEO, 6, 1, 0),
AC97_ENUM("Captuwe Sewect", wm9713_enum[3]),

AC97_SINGWE("AWC Tawget Vowume", AC97_CODEC_CWASS_WEV, 12, 15, 0),
AC97_SINGWE("AWC Howd Time", AC97_CODEC_CWASS_WEV, 8, 15, 0),
AC97_SINGWE("AWC Decay Time ", AC97_CODEC_CWASS_WEV, 4, 15, 0),
AC97_SINGWE("AWC Attack Time", AC97_CODEC_CWASS_WEV, 0, 15, 0),
AC97_ENUM("AWC Function", wm9713_enum[5]),
AC97_SINGWE("AWC Max Vowume", AC97_PCI_SVID, 11, 7, 0),
AC97_SINGWE("AWC ZC Timeout", AC97_PCI_SVID, 9, 3, 0),
AC97_SINGWE("AWC ZC Switch", AC97_PCI_SVID, 8, 1, 0),
AC97_SINGWE("AWC NG Switch", AC97_PCI_SVID, 7, 1, 0),
AC97_ENUM("AWC NG Type", wm9713_enum[13]),
AC97_SINGWE("AWC NG Thweshowd", AC97_PCI_SVID, 0, 31, 0),

AC97_DOUBWE("Mastew ZC Switch", AC97_MASTEW, 14, 6, 1, 0),
AC97_DOUBWE("Headphone ZC Switch", AC97_HEADPHONE, 14, 6, 1, 0),
AC97_DOUBWE("Out3/4 ZC Switch", AC97_MASTEW_MONO, 14, 6, 1, 0),
AC97_SINGWE("Mastew Wight Switch", AC97_MASTEW, 7, 1, 1),
AC97_SINGWE("Headphone Wight Switch", AC97_HEADPHONE, 7, 1, 1),
AC97_SINGWE("Out3/4 Wight Switch", AC97_MASTEW_MONO, 7, 1, 1),

AC97_SINGWE("Mono In to Headphone Switch", AC97_MASTEW_TONE, 15, 1, 1),
AC97_SINGWE("Mono In to Mastew Switch", AC97_MASTEW_TONE, 14, 1, 1),
AC97_SINGWE("Mono In Vowume", AC97_MASTEW_TONE, 8, 31, 1),
AC97_SINGWE("Mono Switch", AC97_MASTEW_TONE, 7, 1, 1),
AC97_SINGWE("Mono ZC Switch", AC97_MASTEW_TONE, 6, 1, 0),
AC97_SINGWE("Mono Vowume", AC97_MASTEW_TONE, 0, 31, 1),

AC97_SINGWE("Beep to Headphone Switch", AC97_AUX, 15, 1, 1),
AC97_SINGWE("Beep to Headphone Vowume", AC97_AUX, 12, 7, 1),
AC97_SINGWE("Beep to Mastew Switch", AC97_AUX, 11, 1, 1),
AC97_SINGWE("Beep to Mastew Vowume", AC97_AUX, 8, 7, 1),
AC97_SINGWE("Beep to Mono Switch", AC97_AUX, 7, 1, 1),
AC97_SINGWE("Beep to Mono Vowume", AC97_AUX, 4, 7, 1),

AC97_SINGWE("Voice to Headphone Switch", AC97_PCM, 15, 1, 1),
AC97_SINGWE("Voice to Headphone Vowume", AC97_PCM, 12, 7, 1),
AC97_SINGWE("Voice to Mastew Switch", AC97_PCM, 11, 1, 1),
AC97_SINGWE("Voice to Mastew Vowume", AC97_PCM, 8, 7, 1),
AC97_SINGWE("Voice to Mono Switch", AC97_PCM, 7, 1, 1),
AC97_SINGWE("Voice to Mono Vowume", AC97_PCM, 4, 7, 1),

AC97_SINGWE("Aux to Headphone Switch", AC97_WEC_SEW, 15, 1, 1),
AC97_SINGWE("Aux to Headphone Vowume", AC97_WEC_SEW, 12, 7, 1),
AC97_SINGWE("Aux to Mastew Switch", AC97_WEC_SEW, 11, 1, 1),
AC97_SINGWE("Aux to Mastew Vowume", AC97_WEC_SEW, 8, 7, 1),
AC97_SINGWE("Aux to Mono Switch", AC97_WEC_SEW, 7, 1, 1),
AC97_SINGWE("Aux to Mono Vowume", AC97_WEC_SEW, 4, 7, 1),

AC97_ENUM("Mono Input Mux", wm9713_enum[6]),
AC97_ENUM("Mastew Input Mux", wm9713_enum[7]),
AC97_ENUM("Headphone Input Mux", wm9713_enum[8]),
AC97_ENUM("Out 3 Input Mux", wm9713_enum[9]),
AC97_ENUM("Out 4 Input Mux", wm9713_enum[10]),

AC97_ENUM("Bass Contwow", wm9713_enum[12]),
AC97_SINGWE("Bass Cut-off Switch", AC97_GENEWAW_PUWPOSE, 12, 1, 1),
AC97_SINGWE("Tone Cut-off Switch", AC97_GENEWAW_PUWPOSE, 4, 1, 1),
AC97_SINGWE("Pwayback Attenuate (-6dB) Switch", AC97_GENEWAW_PUWPOSE, 6, 1, 0),
AC97_SINGWE("Bass Vowume", AC97_GENEWAW_PUWPOSE, 8, 15, 1),
AC97_SINGWE("Tone Vowume", AC97_GENEWAW_PUWPOSE, 0, 15, 1),
};

static const stwuct snd_kcontwow_new wm13_snd_ac97_contwows_3d[] = {
AC97_ENUM("Inv Input Mux", wm9713_enum[11]),
AC97_SINGWE("3D Uppew Cut-off Switch", AC97_WEC_GAIN_MIC, 5, 1, 0),
AC97_SINGWE("3D Wowew Cut-off Switch", AC97_WEC_GAIN_MIC, 4, 1, 0),
AC97_SINGWE("3D Depth", AC97_WEC_GAIN_MIC, 0, 15, 1),
};

static int patch_wowfson_wm9713_3d (stwuct snd_ac97 * ac97)
{
	int eww, i;
    
	fow (i = 0; i < AWWAY_SIZE(wm13_snd_ac97_contwows_3d); i++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&wm13_snd_ac97_contwows_3d[i], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int patch_wowfson_wm9713_specific(stwuct snd_ac97 * ac97)
{
	int eww, i;
	
	fow (i = 0; i < AWWAY_SIZE(wm13_snd_ac97_contwows); i++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ac97_cnew(&wm13_snd_ac97_contwows[i], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	snd_ac97_wwite_cache(ac97, AC97_PC_BEEP, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_PHONE, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_MIC, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_WINE, 0x00da);
	snd_ac97_wwite_cache(ac97, AC97_CD, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_VIDEO, 0xd612);
	snd_ac97_wwite_cache(ac97, AC97_WEC_GAIN, 0x1ba0);
	wetuwn 0;
}

#ifdef CONFIG_PM
static void patch_wowfson_wm9713_suspend (stwuct snd_ac97 * ac97)
{
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MID, 0xfeff);
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MSTATUS, 0xffff);
}

static void patch_wowfson_wm9713_wesume (stwuct snd_ac97 * ac97)
{
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MID, 0xda00);
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MSTATUS, 0x3810);
	snd_ac97_wwite_cache(ac97, AC97_POWEWDOWN, 0x0);
}
#endif

static const stwuct snd_ac97_buiwd_ops patch_wowfson_wm9713_ops = {
	.buiwd_specific = patch_wowfson_wm9713_specific,
	.buiwd_3d = patch_wowfson_wm9713_3d,
#ifdef CONFIG_PM	
	.suspend = patch_wowfson_wm9713_suspend,
	.wesume = patch_wowfson_wm9713_wesume
#endif
};

static int patch_wowfson13(stwuct snd_ac97 * ac97)
{
	/* WM9713, WM9714 */
	ac97->buiwd_ops = &patch_wowfson_wm9713_ops;

	ac97->fwags |= AC97_HAS_NO_WEC_GAIN | AC97_STEWEO_MUTES | AC97_HAS_NO_PHONE |
		AC97_HAS_NO_PC_BEEP | AC97_HAS_NO_VIDEO | AC97_HAS_NO_CD | AC97_HAS_NO_TONE |
		AC97_HAS_NO_STD_PCM;
    	ac97->scaps &= ~AC97_SCAP_MODEM;

	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MID, 0xda00);
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_MSTATUS, 0x3810);
	snd_ac97_wwite_cache(ac97, AC97_POWEWDOWN, 0x0);

	wetuwn 0;
}

/*
 * Twitech codec
 */
static int patch_twitech_tw28028(stwuct snd_ac97 * ac97)
{
	snd_ac97_wwite_cache(ac97, 0x26, 0x0300);
	snd_ac97_wwite_cache(ac97, 0x26, 0x0000);
	snd_ac97_wwite_cache(ac97, AC97_SUWWOUND_MASTEW, 0x0000);
	snd_ac97_wwite_cache(ac97, AC97_SPDIF, 0x0000);
	wetuwn 0;
}

/*
 * Sigmatew STAC97xx codecs
 */
static int patch_sigmatew_stac9700_3d(stwuct snd_ac97 * ac97)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	eww = snd_ctw_add(ac97->bus->cawd, kctw = snd_ac97_cnew(&snd_ac97_contwows_3d[0], ac97));
	if (eww < 0)
		wetuwn eww;
	stwcpy(kctw->id.name, "3D Contwow Sigmatew - Depth");
	kctw->pwivate_vawue = AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 2, 3, 0);
	snd_ac97_wwite_cache(ac97, AC97_3D_CONTWOW, 0x0000);
	wetuwn 0;
}

static int patch_sigmatew_stac9708_3d(stwuct snd_ac97 * ac97)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	kctw = snd_ac97_cnew(&snd_ac97_contwows_3d[0], ac97);
	eww = snd_ctw_add(ac97->bus->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	stwcpy(kctw->id.name, "3D Contwow Sigmatew - Depth");
	kctw->pwivate_vawue = AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 0, 3, 0);
	kctw = snd_ac97_cnew(&snd_ac97_contwows_3d[0], ac97);
	eww = snd_ctw_add(ac97->bus->cawd, kctw);
	if (eww < 0)
		wetuwn eww;
	stwcpy(kctw->id.name, "3D Contwow Sigmatew - Weaw Depth");
	kctw->pwivate_vawue = AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 2, 3, 0);
	snd_ac97_wwite_cache(ac97, AC97_3D_CONTWOW, 0x0000);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ac97_sigmatew_4speakew =
AC97_SINGWE("Sigmatew 4-Speakew Steweo Pwayback Switch",
		AC97_SIGMATEW_DAC2INVEWT, 2, 1, 0);

/* "Sigmatew " wemoved due to excessive name wength: */
static const stwuct snd_kcontwow_new snd_ac97_sigmatew_phaseinvewt =
AC97_SINGWE("Suwwound Phase Invewsion Pwayback Switch",
		AC97_SIGMATEW_DAC2INVEWT, 3, 1, 0);

static const stwuct snd_kcontwow_new snd_ac97_sigmatew_contwows[] = {
AC97_SINGWE("Sigmatew DAC 6dB Attenuate", AC97_SIGMATEW_ANAWOG, 1, 1, 0),
AC97_SINGWE("Sigmatew ADC 6dB Attenuate", AC97_SIGMATEW_ANAWOG, 0, 1, 0)
};

static int patch_sigmatew_stac97xx_specific(stwuct snd_ac97 * ac97)
{
	int eww;

	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_ANAWOG, snd_ac97_wead(ac97, AC97_SIGMATEW_ANAWOG) & ~0x0003);
	if (snd_ac97_twy_bit(ac97, AC97_SIGMATEW_ANAWOG, 1)) {
		eww = patch_buiwd_contwows(ac97, &snd_ac97_sigmatew_contwows[0], 1);
		if (eww < 0)
			wetuwn eww;
	}
	if (snd_ac97_twy_bit(ac97, AC97_SIGMATEW_ANAWOG, 0)) {
		eww = patch_buiwd_contwows(ac97, &snd_ac97_sigmatew_contwows[1], 1);
		if (eww < 0)
			wetuwn eww;
	}
	if (snd_ac97_twy_bit(ac97, AC97_SIGMATEW_DAC2INVEWT, 2)) {
		eww = patch_buiwd_contwows(ac97, &snd_ac97_sigmatew_4speakew, 1);
		if (eww < 0)
			wetuwn eww;
	}
	if (snd_ac97_twy_bit(ac97, AC97_SIGMATEW_DAC2INVEWT, 3)) {
		eww = patch_buiwd_contwows(ac97, &snd_ac97_sigmatew_phaseinvewt, 1);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_sigmatew_stac9700_ops = {
	.buiwd_3d	= patch_sigmatew_stac9700_3d,
	.buiwd_specific	= patch_sigmatew_stac97xx_specific
};

static int patch_sigmatew_stac9700(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_sigmatew_stac9700_ops;
	wetuwn 0;
}

static int snd_ac97_stac9708_put_bias(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int eww;

	mutex_wock(&ac97->page_mutex);
	snd_ac97_wwite(ac97, AC97_SIGMATEW_BIAS1, 0xabba);
	eww = snd_ac97_update_bits(ac97, AC97_SIGMATEW_BIAS2, 0x0010,
				   (ucontwow->vawue.integew.vawue[0] & 1) << 4);
	snd_ac97_wwite(ac97, AC97_SIGMATEW_BIAS1, 0);
	mutex_unwock(&ac97->page_mutex);
	wetuwn eww;
}

static const stwuct snd_kcontwow_new snd_ac97_stac9708_bias_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Sigmatew Output Bias Switch",
	.info = snd_ac97_info_vowsw,
	.get = snd_ac97_get_vowsw,
	.put = snd_ac97_stac9708_put_bias,
	.pwivate_vawue = AC97_SINGWE_VAWUE(AC97_SIGMATEW_BIAS2, 4, 1, 0),
};

static int patch_sigmatew_stac9708_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	/* the wegistew bit is wwitabwe, but the function is not impwemented: */
	snd_ac97_wemove_ctw(ac97, "PCM Out Path & Mute", NUWW);

	snd_ac97_wename_vow_ctw(ac97, "Headphone Pwayback", "Sigmatew Suwwound Pwayback");
	eww = patch_buiwd_contwows(ac97, &snd_ac97_stac9708_bias_contwow, 1);
	if (eww < 0)
		wetuwn eww;
	wetuwn patch_sigmatew_stac97xx_specific(ac97);
}

static const stwuct snd_ac97_buiwd_ops patch_sigmatew_stac9708_ops = {
	.buiwd_3d	= patch_sigmatew_stac9708_3d,
	.buiwd_specific	= patch_sigmatew_stac9708_specific
};

static int patch_sigmatew_stac9708(stwuct snd_ac97 * ac97)
{
	unsigned int codec72, codec6c;

	ac97->buiwd_ops = &patch_sigmatew_stac9708_ops;
	ac97->caps |= 0x10;	/* HP (sigmatew suwwound) suppowt */

	codec72 = snd_ac97_wead(ac97, AC97_SIGMATEW_BIAS2) & 0x8000;
	codec6c = snd_ac97_wead(ac97, AC97_SIGMATEW_ANAWOG);

	if ((codec72==0) && (codec6c==0)) {
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC1, 0xabba);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC2, 0x1000);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS1, 0xabba);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS2, 0x0007);
	} ewse if ((codec72==0x8000) && (codec6c==0)) {
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC1, 0xabba);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC2, 0x1001);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_DAC2INVEWT, 0x0008);
	} ewse if ((codec72==0x8000) && (codec6c==0x0080)) {
		/* nothing */
	}
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_MUWTICHN, 0x0000);
	wetuwn 0;
}

static int patch_sigmatew_stac9721(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_sigmatew_stac9700_ops;
	if (snd_ac97_wead(ac97, AC97_SIGMATEW_ANAWOG) == 0) {
		// patch fow SigmaTew
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC1, 0xabba);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC2, 0x4000);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS1, 0xabba);
		snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS2, 0x0002);
	}
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_MUWTICHN, 0x0000);
	wetuwn 0;
}

static int patch_sigmatew_stac9744(stwuct snd_ac97 * ac97)
{
	// patch fow SigmaTew
	ac97->buiwd_ops = &patch_sigmatew_stac9700_ops;
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC1, 0xabba);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC2, 0x0000);	/* is this cowwect? --jk */
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS1, 0xabba);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS2, 0x0002);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_MUWTICHN, 0x0000);
	wetuwn 0;
}

static int patch_sigmatew_stac9756(stwuct snd_ac97 * ac97)
{
	// patch fow SigmaTew
	ac97->buiwd_ops = &patch_sigmatew_stac9700_ops;
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC1, 0xabba);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_CIC2, 0x0000);	/* is this cowwect? --jk */
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS1, 0xabba);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_BIAS2, 0x0002);
	snd_ac97_wwite_cache(ac97, AC97_SIGMATEW_MUWTICHN, 0x0000);
	wetuwn 0;
}

static int snd_ac97_stac9758_output_jack_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[5] = {
		"Input/Disabwed", "Fwont Output",
		"Weaw Output", "Centew/WFE Output", "Mixew Output" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 5, texts);
}

static int snd_ac97_stac9758_output_jack_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue;
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_SIGMATEW_OUTSEW] >> shift;
	if (!(vaw & 4))
		ucontwow->vawue.enumewated.item[0] = 0;
	ewse
		ucontwow->vawue.enumewated.item[0] = 1 + (vaw & 3);
	wetuwn 0;
}

static int snd_ac97_stac9758_output_jack_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue;
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 4)
		wetuwn -EINVAW;
	if (ucontwow->vawue.enumewated.item[0] == 0)
		vaw = 0;
	ewse
		vaw = 4 | (ucontwow->vawue.enumewated.item[0] - 1);
	wetuwn ac97_update_bits_page(ac97, AC97_SIGMATEW_OUTSEW,
				     7 << shift, vaw << shift, 0);
}

static int snd_ac97_stac9758_input_jack_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[7] = {
		"Mic2 Jack", "Mic1 Jack", "Wine In Jack",
		"Fwont Jack", "Weaw Jack", "Centew/WFE Jack", "Mute" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 7, texts);
}

static int snd_ac97_stac9758_input_jack_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue;
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_SIGMATEW_INSEW];
	ucontwow->vawue.enumewated.item[0] = (vaw >> shift) & 7;
	wetuwn 0;
}

static int snd_ac97_stac9758_input_jack_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue;

	wetuwn ac97_update_bits_page(ac97, AC97_SIGMATEW_INSEW, 7 << shift,
				     ucontwow->vawue.enumewated.item[0] << shift, 0);
}

static int snd_ac97_stac9758_phonesew_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {
		"None", "Fwont Jack", "Weaw Jack"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_ac97_stac9758_phonesew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.enumewated.item[0] = ac97->wegs[AC97_SIGMATEW_IOMISC] & 3;
	wetuwn 0;
}

static int snd_ac97_stac9758_phonesew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	wetuwn ac97_update_bits_page(ac97, AC97_SIGMATEW_IOMISC, 3,
				     ucontwow->vawue.enumewated.item[0], 0);
}

#define STAC9758_OUTPUT_JACK(xname, shift) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_ac97_stac9758_output_jack_info, \
	.get = snd_ac97_stac9758_output_jack_get, \
	.put = snd_ac97_stac9758_output_jack_put, \
	.pwivate_vawue = shift }
#define STAC9758_INPUT_JACK(xname, shift) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_ac97_stac9758_input_jack_info, \
	.get = snd_ac97_stac9758_input_jack_get, \
	.put = snd_ac97_stac9758_input_jack_put, \
	.pwivate_vawue = shift }
static const stwuct snd_kcontwow_new snd_ac97_sigmatew_stac9758_contwows[] = {
	STAC9758_OUTPUT_JACK("Mic1 Jack", 1),
	STAC9758_OUTPUT_JACK("WineIn Jack", 4),
	STAC9758_OUTPUT_JACK("Fwont Jack", 7),
	STAC9758_OUTPUT_JACK("Weaw Jack", 10),
	STAC9758_OUTPUT_JACK("Centew/WFE Jack", 13),
	STAC9758_INPUT_JACK("Mic Input Souwce", 0),
	STAC9758_INPUT_JACK("Wine Input Souwce", 8),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Headphone Amp",
		.info = snd_ac97_stac9758_phonesew_info,
		.get = snd_ac97_stac9758_phonesew_get,
		.put = snd_ac97_stac9758_phonesew_put
	},
	AC97_SINGWE("Exchange Centew/WFE", AC97_SIGMATEW_IOMISC, 4, 1, 0),
	AC97_SINGWE("Headphone +3dB Boost", AC97_SIGMATEW_IOMISC, 8, 1, 0)
};

static int patch_sigmatew_stac9758_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_sigmatew_stac97xx_specific(ac97);
	if (eww < 0)
		wetuwn eww;
	eww = patch_buiwd_contwows(ac97, snd_ac97_sigmatew_stac9758_contwows,
				   AWWAY_SIZE(snd_ac97_sigmatew_stac9758_contwows));
	if (eww < 0)
		wetuwn eww;
	/* DAC-A diwect */
	snd_ac97_wename_vow_ctw(ac97, "Headphone Pwayback", "Fwont Pwayback");
	/* DAC-A to Mix = PCM */
	/* DAC-B diwect = Suwwound */
	/* DAC-B to Mix */
	snd_ac97_wename_vow_ctw(ac97, "Video Pwayback", "Suwwound Mix Pwayback");
	/* DAC-C diwect = Centew/WFE */

	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_sigmatew_stac9758_ops = {
	.buiwd_3d	= patch_sigmatew_stac9700_3d,
	.buiwd_specific	= patch_sigmatew_stac9758_specific
};

static int patch_sigmatew_stac9758(stwuct snd_ac97 * ac97)
{
	static const unsigned showt wegs[4] = {
		AC97_SIGMATEW_OUTSEW,
		AC97_SIGMATEW_IOMISC,
		AC97_SIGMATEW_INSEW,
		AC97_SIGMATEW_VAWIOUS
	};
	static const unsigned showt def_wegs[4] = {
		/* OUTSEW */ 0xd794, /* CW:CW, SW:SW, WO:MX, WI:DS, MI:DS */
		/* IOMISC */ 0x2001,
		/* INSEW */ 0x0201, /* WI:WI, MI:M1 */
		/* VAWIOUS */ 0x0040
	};
	static const unsigned showt m675_wegs[4] = {
		/* OUTSEW */ 0xfc70, /* CW:MX, SW:MX, WO:DS, WI:MX, MI:DS */
		/* IOMISC */ 0x2102, /* HP amp on */
		/* INSEW */ 0x0203, /* WI:WI, MI:FW */
		/* VAWIOUS */ 0x0041 /* steweo mic */
	};
	const unsigned showt *pwegs = def_wegs;
	int i;

	/* Gateway M675 notebook */
	if (ac97->pci && 
	    ac97->subsystem_vendow == 0x107b &&
	    ac97->subsystem_device == 0x0601)
	    	pwegs = m675_wegs;

	// patch fow SigmaTew
	ac97->buiwd_ops = &patch_sigmatew_stac9758_ops;
	/* FIXME: assume onwy page 0 fow wwiting cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOW);
	fow (i = 0; i < 4; i++)
		snd_ac97_wwite_cache(ac97, wegs[i], pwegs[i]);

	ac97->fwags |= AC97_STEWEO_MUTES;
	wetuwn 0;
}

/*
 * Ciwwus Wogic CS42xx codecs
 */
static const stwuct snd_kcontwow_new snd_ac97_ciwwus_contwows_spdif[2] = {
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",PWAYBACK,SWITCH), AC97_CSW_SPDIF, 15, 1, 0),
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "AC97-SPSA", AC97_CSW_ACMODE, 0, 3, 0)
};

static int patch_ciwwus_buiwd_spdif(stwuct snd_ac97 * ac97)
{
	int eww;

	/* con mask, pwo mask, defauwt */
	eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_spdif[0], 3);
	if (eww < 0)
		wetuwn eww;
	/* switch, spsa */
	eww = patch_buiwd_contwows(ac97, &snd_ac97_ciwwus_contwows_spdif[0], 1);
	if (eww < 0)
		wetuwn eww;
	switch (ac97->id & AC97_ID_CS_MASK) {
	case AC97_ID_CS4205:
		eww = patch_buiwd_contwows(ac97, &snd_ac97_ciwwus_contwows_spdif[1], 1);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}
	/* set defauwt PCM S/PDIF pawams */
	/* consumew,PCM audio,no copywight,no pweemphasis,PCM codew,owiginaw,48000Hz */
	snd_ac97_wwite_cache(ac97, AC97_CSW_SPDIF, 0x0a20);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_ciwwus_ops = {
	.buiwd_spdif = patch_ciwwus_buiwd_spdif
};

static int patch_ciwwus_spdif(stwuct snd_ac97 * ac97)
{
	/* Basicawwy, the cs4201/cs4205/cs4297a has non-standawd sp/dif wegistews.
	   WHY CAN'T ANYONE FOWWOW THE BWOODY SPEC?  *sigh*
	   - sp/dif EA ID is not set, but sp/dif is awways pwesent.
	   - enabwe/disabwe is spdif wegistew bit 15.
	   - sp/dif contwow wegistew is 0x68.  diffews fwom AC97:
	   - vawid is bit 14 (vs 15)
	   - no DWS
	   - onwy 44.1/48k [00 = 48, 01=44,1] (AC97 is 00=44.1, 10=48)
	   - sp/dif ssouwce sewect is in 0x5e bits 0,1.
	*/

	ac97->buiwd_ops = &patch_ciwwus_ops;
	ac97->fwags |= AC97_CS_SPDIF; 
	ac97->wates[AC97_WATES_SPDIF] &= ~SNDWV_PCM_WATE_32000;
        ac97->ext_id |= AC97_EI_SPDIF;	/* fowce the detection of spdif */
	snd_ac97_wwite_cache(ac97, AC97_CSW_ACMODE, 0x0080);
	wetuwn 0;
}

static int patch_ciwwus_cs4299(stwuct snd_ac97 * ac97)
{
	/* fowce the detection of PC Beep */
	ac97->fwags |= AC97_HAS_PC_BEEP;
	
	wetuwn patch_ciwwus_spdif(ac97);
}

/*
 * Conexant codecs
 */
static const stwuct snd_kcontwow_new snd_ac97_conexant_contwows_spdif[1] = {
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",PWAYBACK,SWITCH), AC97_CXW_AUDIO_MISC, 3, 1, 0),
};

static int patch_conexant_buiwd_spdif(stwuct snd_ac97 * ac97)
{
	int eww;

	/* con mask, pwo mask, defauwt */
	eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_spdif[0], 3);
	if (eww < 0)
		wetuwn eww;
	/* switch */
	eww = patch_buiwd_contwows(ac97, &snd_ac97_conexant_contwows_spdif[0], 1);
	if (eww < 0)
		wetuwn eww;
	/* set defauwt PCM S/PDIF pawams */
	/* consumew,PCM audio,no copywight,no pweemphasis,PCM codew,owiginaw,48000Hz */
	snd_ac97_wwite_cache(ac97, AC97_CXW_AUDIO_MISC,
			     snd_ac97_wead(ac97, AC97_CXW_AUDIO_MISC) & ~(AC97_CXW_SPDIFEN|AC97_CXW_COPYWGT|AC97_CXW_SPDIF_MASK));
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_conexant_ops = {
	.buiwd_spdif = patch_conexant_buiwd_spdif
};

static int patch_conexant(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_conexant_ops;
	ac97->fwags |= AC97_CX_SPDIF;
        ac97->ext_id |= AC97_EI_SPDIF;	/* fowce the detection of spdif */
	ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_48000; /* 48k onwy */
	wetuwn 0;
}

static int patch_cx20551(stwuct snd_ac97 *ac97)
{
	snd_ac97_update_bits(ac97, 0x5c, 0x01, 0x01);
	wetuwn 0;
}

/*
 * Anawog Devices AD18xx, AD19xx codecs
 */
#ifdef CONFIG_PM
static void ad18xx_wesume(stwuct snd_ac97 *ac97)
{
	static const unsigned showt setup_wegs[] = {
		AC97_AD_MISC, AC97_AD_SEWIAW_CFG, AC97_AD_JACK_SPDIF,
	};
	int i, codec;

	fow (i = 0; i < (int)AWWAY_SIZE(setup_wegs); i++) {
		unsigned showt weg = setup_wegs[i];
		if (test_bit(weg, ac97->weg_accessed)) {
			snd_ac97_wwite(ac97, weg, ac97->wegs[weg]);
			snd_ac97_wead(ac97, weg);
		}
	}

	if (! (ac97->fwags & AC97_AD_MUWTI))
		/* nowmaw westowe */
		snd_ac97_westowe_status(ac97);
	ewse {
		/* westowe the AD18xx codec configuwations */
		fow (codec = 0; codec < 3; codec++) {
			if (! ac97->spec.ad18xx.id[codec])
				continue;
			/* sewect singwe codec */
			snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000,
					     ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
			ac97->bus->ops->wwite(ac97, AC97_AD_CODEC_CFG, ac97->spec.ad18xx.codec_cfg[codec]);
		}
		/* sewect aww codecs */
		snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000, 0x7000);

		/* westowe status */
		fow (i = 2; i < 0x7c ; i += 2) {
			if (i == AC97_POWEWDOWN || i == AC97_EXTENDED_ID)
				continue;
			if (test_bit(i, ac97->weg_accessed)) {
				/* handwe muwti codecs fow AD18xx */
				if (i == AC97_PCM) {
					fow (codec = 0; codec < 3; codec++) {
						if (! ac97->spec.ad18xx.id[codec])
							continue;
						/* sewect singwe codec */
						snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000,
								     ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
						/* update PCM bits */
						ac97->bus->ops->wwite(ac97, AC97_PCM, ac97->spec.ad18xx.pcmweg[codec]);
					}
					/* sewect aww codecs */
					snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000, 0x7000);
					continue;
				} ewse if (i == AC97_AD_TEST ||
					   i == AC97_AD_CODEC_CFG ||
					   i == AC97_AD_SEWIAW_CFG)
					continue; /* ignowe */
			}
			snd_ac97_wwite(ac97, i, ac97->wegs[i]);
			snd_ac97_wead(ac97, i);
		}
	}

	snd_ac97_westowe_iec958(ac97);
}

static void ad1888_wesume(stwuct snd_ac97 *ac97)
{
	ad18xx_wesume(ac97);
	snd_ac97_wwite_cache(ac97, AC97_CODEC_CWASS_WEV, 0x8080);
}

#endif

static const stwuct snd_ac97_wes_tabwe ad1819_westbw[] = {
	{ AC97_PHONE, 0x9f1f },
	{ AC97_MIC, 0x9f1f },
	{ AC97_WINE, 0x9f1f },
	{ AC97_CD, 0x9f1f },
	{ AC97_VIDEO, 0x9f1f },
	{ AC97_AUX, 0x9f1f },
	{ AC97_PCM, 0x9f1f },
	{ } /* tewminatow */
};

static int patch_ad1819(stwuct snd_ac97 * ac97)
{
	unsigned showt scfg;

	// patch fow Anawog Devices
	scfg = snd_ac97_wead(ac97, AC97_AD_SEWIAW_CFG);
	snd_ac97_wwite_cache(ac97, AC97_AD_SEWIAW_CFG, scfg | 0x7000); /* sewect aww codecs */
	ac97->wes_tabwe = ad1819_westbw;
	wetuwn 0;
}

static unsigned showt patch_ad1881_unchained(stwuct snd_ac97 * ac97, int idx, unsigned showt mask)
{
	unsigned showt vaw;

	// test fow unchained codec
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000, mask);
	snd_ac97_wwite_cache(ac97, AC97_AD_CODEC_CFG, 0x0000);	/* ID0C, ID1C, SDIE = off */
	vaw = snd_ac97_wead(ac97, AC97_VENDOW_ID2);
	if ((vaw & 0xff40) != 0x5340)
		wetuwn 0;
	ac97->spec.ad18xx.unchained[idx] = mask;
	ac97->spec.ad18xx.id[idx] = vaw;
	ac97->spec.ad18xx.codec_cfg[idx] = 0x0000;
	wetuwn mask;
}

static int patch_ad1881_chained1(stwuct snd_ac97 * ac97, int idx, unsigned showt codec_bits)
{
	static const int cfg_bits[3] = { 1<<12, 1<<14, 1<<13 };
	unsigned showt vaw;
	
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000, cfg_bits[idx]);
	snd_ac97_wwite_cache(ac97, AC97_AD_CODEC_CFG, 0x0004);	// SDIE
	vaw = snd_ac97_wead(ac97, AC97_VENDOW_ID2);
	if ((vaw & 0xff40) != 0x5340)
		wetuwn 0;
	if (codec_bits)
		snd_ac97_wwite_cache(ac97, AC97_AD_CODEC_CFG, codec_bits);
	ac97->spec.ad18xx.chained[idx] = cfg_bits[idx];
	ac97->spec.ad18xx.id[idx] = vaw;
	ac97->spec.ad18xx.codec_cfg[idx] = codec_bits ? codec_bits : 0x0004;
	wetuwn 1;
}

static void patch_ad1881_chained(stwuct snd_ac97 * ac97, int unchained_idx, int cidx1, int cidx2)
{
	// awweady detected?
	if (ac97->spec.ad18xx.unchained[cidx1] || ac97->spec.ad18xx.chained[cidx1])
		cidx1 = -1;
	if (ac97->spec.ad18xx.unchained[cidx2] || ac97->spec.ad18xx.chained[cidx2])
		cidx2 = -1;
	if (cidx1 < 0 && cidx2 < 0)
		wetuwn;
	// test fow chained codecs
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000,
			     ac97->spec.ad18xx.unchained[unchained_idx]);
	snd_ac97_wwite_cache(ac97, AC97_AD_CODEC_CFG, 0x0002);		// ID1C
	ac97->spec.ad18xx.codec_cfg[unchained_idx] = 0x0002;
	if (cidx1 >= 0) {
		if (cidx2 < 0)
			patch_ad1881_chained1(ac97, cidx1, 0);
		ewse if (patch_ad1881_chained1(ac97, cidx1, 0x0006))	// SDIE | ID1C
			patch_ad1881_chained1(ac97, cidx2, 0);
		ewse if (patch_ad1881_chained1(ac97, cidx2, 0x0006))	// SDIE | ID1C
			patch_ad1881_chained1(ac97, cidx1, 0);
	} ewse if (cidx2 >= 0) {
		patch_ad1881_chained1(ac97, cidx2, 0);
	}
}

static const stwuct snd_ac97_buiwd_ops patch_ad1881_buiwd_ops = {
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume
#endif
};

static int patch_ad1881(stwuct snd_ac97 * ac97)
{
	static const chaw cfg_idxs[3][2] = {
		{2, 1},
		{0, 2},
		{0, 1}
	};
	
	// patch fow Anawog Devices
	unsigned showt codecs[3];
	unsigned showt vaw;
	int idx, num;

	vaw = snd_ac97_wead(ac97, AC97_AD_SEWIAW_CFG);
	snd_ac97_wwite_cache(ac97, AC97_AD_SEWIAW_CFG, vaw);
	codecs[0] = patch_ad1881_unchained(ac97, 0, (1<<12));
	codecs[1] = patch_ad1881_unchained(ac97, 1, (1<<14));
	codecs[2] = patch_ad1881_unchained(ac97, 2, (1<<13));

	if (! (codecs[0] || codecs[1] || codecs[2]))
		goto __end;

	fow (idx = 0; idx < 3; idx++)
		if (ac97->spec.ad18xx.unchained[idx])
			patch_ad1881_chained(ac97, idx, cfg_idxs[idx][0], cfg_idxs[idx][1]);

	if (ac97->spec.ad18xx.id[1]) {
		ac97->fwags |= AC97_AD_MUWTI;
		ac97->scaps |= AC97_SCAP_SUWWOUND_DAC;
	}
	if (ac97->spec.ad18xx.id[2]) {
		ac97->fwags |= AC97_AD_MUWTI;
		ac97->scaps |= AC97_SCAP_CENTEW_WFE_DAC;
	}

      __end:
	/* sewect aww codecs */
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x7000, 0x7000);
	/* check if onwy one codec is pwesent */
	fow (idx = num = 0; idx < 3; idx++)
		if (ac97->spec.ad18xx.id[idx])
			num++;
	if (num == 1) {
		/* ok, desewect aww ID bits */
		snd_ac97_wwite_cache(ac97, AC97_AD_CODEC_CFG, 0x0000);
		ac97->spec.ad18xx.codec_cfg[0] = 
			ac97->spec.ad18xx.codec_cfg[1] = 
			ac97->spec.ad18xx.codec_cfg[2] = 0x0000;
	}
	/* wequiwed fow AD1886/AD1885 combination */
	ac97->ext_id = snd_ac97_wead(ac97, AC97_EXTENDED_ID);
	if (ac97->spec.ad18xx.id[0]) {
		ac97->id &= 0xffff0000;
		ac97->id |= ac97->spec.ad18xx.id[0];
	}
	ac97->buiwd_ops = &patch_ad1881_buiwd_ops;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_ad1885[] = {
	AC97_SINGWE("Digitaw Mono Diwect", AC97_AD_MISC, 11, 1, 0),
	/* AC97_SINGWE("Digitaw Audio Mode", AC97_AD_MISC, 12, 1, 0), */ /* seems pwobwematic */
	AC97_SINGWE("Wow Powew Mixew", AC97_AD_MISC, 14, 1, 0),
	AC97_SINGWE("Zewo Fiww DAC", AC97_AD_MISC, 15, 1, 0),
	AC97_SINGWE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 9, 1, 1), /* invewted */
	AC97_SINGWE("Wine Jack Sense", AC97_AD_JACK_SPDIF, 8, 1, 1), /* invewted */
};

static const DECWAWE_TWV_DB_SCAWE(db_scawe_6bit_6db_max, -8850, 150, 0);

static int patch_ad1885_specific(stwuct snd_ac97 * ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, snd_ac97_contwows_ad1885, AWWAY_SIZE(snd_ac97_contwows_ad1885));
	if (eww < 0)
		wetuwn eww;
	weset_twv(ac97, "Headphone Pwayback Vowume",
		  db_scawe_6bit_6db_max);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_ad1885_buiwd_ops = {
	.buiwd_specific = &patch_ad1885_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume
#endif
};

static int patch_ad1885(stwuct snd_ac97 * ac97)
{
	patch_ad1881(ac97);
	/* This is wequiwed to deaw with the Intew D815EEAW2 */
	/* i.e. Wine out is actuawwy headphone out fwom codec */

	/* set defauwt */
	snd_ac97_wwite_cache(ac97, AC97_AD_MISC, 0x0404);

	ac97->buiwd_ops = &patch_ad1885_buiwd_ops;
	wetuwn 0;
}

static int patch_ad1886_specific(stwuct snd_ac97 * ac97)
{
	weset_twv(ac97, "Headphone Pwayback Vowume",
		  db_scawe_6bit_6db_max);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_ad1886_buiwd_ops = {
	.buiwd_specific = &patch_ad1886_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume
#endif
};

static int patch_ad1886(stwuct snd_ac97 * ac97)
{
	patch_ad1881(ac97);
	/* Pwesawio700 wowkawound */
	/* fow Jack Sense/SPDIF Wegistew misetting causing */
	snd_ac97_wwite_cache(ac97, AC97_AD_JACK_SPDIF, 0x0010);
	ac97->buiwd_ops = &patch_ad1886_buiwd_ops;
	wetuwn 0;
}

/* MISC bits (AD1888/AD1980/AD1985 wegistew 0x76) */
#define AC97_AD198X_MBC		0x0003	/* mic boost */
#define AC97_AD198X_MBC_20	0x0000	/* +20dB */
#define AC97_AD198X_MBC_10	0x0001	/* +10dB */
#define AC97_AD198X_MBC_30	0x0002	/* +30dB */
#define AC97_AD198X_VWEFD	0x0004	/* VWEF high-Z */
#define AC97_AD198X_VWEFH	0x0008	/* 0=2.25V, 1=3.7V */
#define AC97_AD198X_VWEF_0	0x000c	/* 0V (AD1985 onwy) */
#define AC97_AD198X_VWEF_MASK	(AC97_AD198X_VWEFH | AC97_AD198X_VWEFD)
#define AC97_AD198X_VWEF_SHIFT	2
#define AC97_AD198X_SWU		0x0010	/* sampwe wate unwock */
#define AC97_AD198X_WOSEW	0x0020	/* WINE_OUT ampwifiews input sewect */
#define AC97_AD198X_2MIC	0x0040	/* 2-channew mic sewect */
#define AC97_AD198X_SPWD	0x0080	/* SPWEAD enabwe */
#define AC97_AD198X_DMIX0	0x0100	/* downmix mode: */
					/*  0 = 6-to-4, 1 = 6-to-2 downmix */
#define AC97_AD198X_DMIX1	0x0200	/* downmix mode: 1 = enabwed */
#define AC97_AD198X_HPSEW	0x0400	/* headphone ampwifiew input sewect */
#define AC97_AD198X_CWDIS	0x0800	/* centew/wfe disabwe */
#define AC97_AD198X_WODIS	0x1000	/* WINE_OUT disabwe */
#define AC97_AD198X_MSPWT	0x2000	/* mute spwit */
#define AC97_AD198X_AC97NC	0x4000	/* AC97 no compatibwe mode */
#define AC97_AD198X_DACZ	0x8000	/* DAC zewo-fiww mode */

/* MISC 1 bits (AD1986 wegistew 0x76) */
#define AC97_AD1986_MBC		0x0003	/* mic boost */
#define AC97_AD1986_MBC_20	0x0000	/* +20dB */
#define AC97_AD1986_MBC_10	0x0001	/* +10dB */
#define AC97_AD1986_MBC_30	0x0002	/* +30dB */
#define AC97_AD1986_WISEW0	0x0004	/* WINE_IN sewect bit 0 */
#define AC97_AD1986_WISEW1	0x0008	/* WINE_IN sewect bit 1 */
#define AC97_AD1986_WISEW_MASK	(AC97_AD1986_WISEW1 | AC97_AD1986_WISEW0)
#define AC97_AD1986_WISEW_WI	0x0000  /* WINE_IN pins as WINE_IN souwce */
#define AC97_AD1986_WISEW_SUWW	0x0004  /* SUWWOUND pins as WINE_IN souwce */
#define AC97_AD1986_WISEW_MIC	0x0008  /* MIC_1/2 pins as WINE_IN souwce */
#define AC97_AD1986_SWU		0x0010	/* sampwe wate unwock */
#define AC97_AD1986_SOSEW	0x0020	/* SUWWOUND_OUT ampwifiews input sew */
#define AC97_AD1986_2MIC	0x0040	/* 2-channew mic sewect */
#define AC97_AD1986_SPWD	0x0080	/* SPWEAD enabwe */
#define AC97_AD1986_DMIX0	0x0100	/* downmix mode: */
					/*  0 = 6-to-4, 1 = 6-to-2 downmix */
#define AC97_AD1986_DMIX1	0x0200	/* downmix mode: 1 = enabwed */
#define AC97_AD1986_CWDIS	0x0800	/* centew/wfe disabwe */
#define AC97_AD1986_SODIS	0x1000	/* SUWWOUND_OUT disabwe */
#define AC97_AD1986_MSPWT	0x2000	/* mute spwit (wead onwy 1) */
#define AC97_AD1986_AC97NC	0x4000	/* AC97 no compatibwe mode (w/o 1) */
#define AC97_AD1986_DACZ	0x8000	/* DAC zewo-fiww mode */

/* MISC 2 bits (AD1986 wegistew 0x70) */
#define AC97_AD_MISC2		0x70	/* Misc Contwow Bits 2 (AD1986) */

#define AC97_AD1986_CVWEF0	0x0004	/* C/WFE VWEF_OUT 2.25V */
#define AC97_AD1986_CVWEF1	0x0008	/* C/WFE VWEF_OUT 0V */
#define AC97_AD1986_CVWEF2	0x0010	/* C/WFE VWEF_OUT 3.7V */
#define AC97_AD1986_CVWEF_MASK \
	(AC97_AD1986_CVWEF2 | AC97_AD1986_CVWEF1 | AC97_AD1986_CVWEF0)
#define AC97_AD1986_JSMAP	0x0020	/* Jack Sense Mapping 1 = awtewnate */
#define AC97_AD1986_MMDIS	0x0080	/* Mono Mute Disabwe */
#define AC97_AD1986_MVWEF0	0x0400	/* MIC VWEF_OUT 2.25V */
#define AC97_AD1986_MVWEF1	0x0800	/* MIC VWEF_OUT 0V */
#define AC97_AD1986_MVWEF2	0x1000	/* MIC VWEF_OUT 3.7V */
#define AC97_AD1986_MVWEF_MASK \
	(AC97_AD1986_MVWEF2 | AC97_AD1986_MVWEF1 | AC97_AD1986_MVWEF0)

/* MISC 3 bits (AD1986 wegistew 0x7a) */
#define AC97_AD_MISC3		0x7a	/* Misc Contwow Bits 3 (AD1986) */

#define AC97_AD1986_MMIX	0x0004	/* Mic Mix, weft/wight */
#define AC97_AD1986_GPO		0x0008	/* Genewaw Puwpose Out */
#define AC97_AD1986_WOHPEN	0x0010	/* WINE_OUT headphone dwive */
#define AC97_AD1986_WVWEF0	0x0100	/* WINE_OUT VWEF_OUT 2.25V */
#define AC97_AD1986_WVWEF1	0x0200	/* WINE_OUT VWEF_OUT 0V */
#define AC97_AD1986_WVWEF2	0x0400	/* WINE_OUT VWEF_OUT 3.7V */
#define AC97_AD1986_WVWEF_MASK \
	(AC97_AD1986_WVWEF2 | AC97_AD1986_WVWEF1 | AC97_AD1986_WVWEF0)
#define AC97_AD1986_JSINVA	0x0800	/* Jack Sense Invewt SENSE_A */
#define AC97_AD1986_WOSEW	0x1000	/* WINE_OUT ampwifiews input sewect */
#define AC97_AD1986_HPSEW0	0x2000	/* Headphone ampwifiews */
					/*   input sewect Suwwound DACs */
#define AC97_AD1986_HPSEW1	0x4000	/* Headphone ampwifiews input */
					/*   sewect C/WFE DACs */
#define AC97_AD1986_JSINVB	0x8000	/* Jack Sense Invewt SENSE_B */

/* Sewiaw Config bits (AD1986 wegistew 0x74) (incompwete) */
#define AC97_AD1986_OMS0	0x0100	/* Optionaw Mic Sewectow bit 0 */
#define AC97_AD1986_OMS1	0x0200	/* Optionaw Mic Sewectow bit 1 */
#define AC97_AD1986_OMS2	0x0400	/* Optionaw Mic Sewectow bit 2 */
#define AC97_AD1986_OMS_MASK \
	(AC97_AD1986_OMS2 | AC97_AD1986_OMS1 | AC97_AD1986_OMS0)
#define AC97_AD1986_OMS_M	0x0000  /* MIC_1/2 pins awe MIC souwces */
#define AC97_AD1986_OMS_W	0x0100  /* WINE_IN pins awe MIC souwces */
#define AC97_AD1986_OMS_C	0x0200  /* Centew/WFE pins awe MCI souwces */
#define AC97_AD1986_OMS_MC	0x0400  /* Mix of MIC and C/WFE pins */
					/*   awe MIC souwces */
#define AC97_AD1986_OMS_MW	0x0500  /* MIX of MIC and WINE_IN pins */
					/*   awe MIC souwces */
#define AC97_AD1986_OMS_WC	0x0600  /* MIX of WINE_IN and C/WFE pins */
					/*   awe MIC souwces */
#define AC97_AD1986_OMS_MWC	0x0700  /* MIX of MIC, WINE_IN, C/WFE pins */
					/*   awe MIC souwces */


static int snd_ac97_ad198x_spdif_souwce_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[2] = { "AC-Wink", "A/D Convewtew" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ac97_ad198x_spdif_souwce_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AD_SEWIAW_CFG];
	ucontwow->vawue.enumewated.item[0] = (vaw >> 2) & 1;
	wetuwn 0;
}

static int snd_ac97_ad198x_spdif_souwce_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 1)
		wetuwn -EINVAW;
	vaw = ucontwow->vawue.enumewated.item[0] << 2;
	wetuwn snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 0x0004, vaw);
}

static const stwuct snd_kcontwow_new snd_ac97_ad198x_spdif_souwce = {
	.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name	= SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Souwce",
	.info	= snd_ac97_ad198x_spdif_souwce_info,
	.get	= snd_ac97_ad198x_spdif_souwce_get,
	.put	= snd_ac97_ad198x_spdif_souwce_put,
};

static int patch_ad198x_post_spdif(stwuct snd_ac97 * ac97)
{
 	wetuwn patch_buiwd_contwows(ac97, &snd_ac97_ad198x_spdif_souwce, 1);
}

static const stwuct snd_kcontwow_new snd_ac97_ad1981x_jack_sense[] = {
	AC97_SINGWE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 11, 1, 0),
	AC97_SINGWE("Wine Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
};

/* deny wist to avoid HP/Wine jack-sense contwows
 * (SS vendow << 16 | device)
 */
static const unsigned int ad1981_jacks_denywist[] = {
	0x10140523, /* Thinkpad W40 */
	0x10140534, /* Thinkpad X31 */
	0x10140537, /* Thinkpad T41p */
	0x1014053e, /* Thinkpad W40e */
	0x10140554, /* Thinkpad T42p/W50p */
	0x10140567, /* Thinkpad T43p 2668-G7U */
	0x10140581, /* Thinkpad X41-2527 */
	0x10280160, /* Deww Dimension 2400 */
	0x104380b0, /* Asus A7V8X-MX */
	0x11790241, /* Toshiba Satewwite A-15 S127 */
	0x1179ff10, /* Toshiba P500 */
	0x144dc01a, /* Samsung NP-X20C004/SEG */
	0 /* end */
};

static int check_wist(stwuct snd_ac97 *ac97, const unsigned int *wist)
{
	u32 subid = ((u32)ac97->subsystem_vendow << 16) | ac97->subsystem_device;
	fow (; *wist; wist++)
		if (*wist == subid)
			wetuwn 1;
	wetuwn 0;
}

static int patch_ad1981a_specific(stwuct snd_ac97 * ac97)
{
	if (check_wist(ac97, ad1981_jacks_denywist))
		wetuwn 0;
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_ad1981x_jack_sense,
				    AWWAY_SIZE(snd_ac97_ad1981x_jack_sense));
}

static const stwuct snd_ac97_buiwd_ops patch_ad1981a_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1981a_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume
#endif
};

/* awwow wist to enabwe HP jack-sense bits
 * (SS vendow << 16 | device)
 */
static const unsigned int ad1981_jacks_awwowwist[] = {
	0x0e11005a, /* HP nc4000/4010 */
	0x103c0890, /* HP nc6000 */
	0x103c0938, /* HP nc4220 */
	0x103c099c, /* HP nx6110 */
	0x103c0944, /* HP nc6220 */
	0x103c0934, /* HP nc8220 */
	0x103c006d, /* HP nx9105 */
	0x103c300d, /* HP Compaq dc5100 SFF(PT003AW) */
	0x17340088, /* FSC Scenic-W */
	0 /* end */
};

static void check_ad1981_hp_jack_sense(stwuct snd_ac97 *ac97)
{
	if (check_wist(ac97, ad1981_jacks_awwowwist))
		/* enabwe headphone jack sense */
		snd_ac97_update_bits(ac97, AC97_AD_JACK_SPDIF, 1<<11, 1<<11);
}

static int patch_ad1981a(stwuct snd_ac97 *ac97)
{
	patch_ad1881(ac97);
	ac97->buiwd_ops = &patch_ad1981a_buiwd_ops;
	snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD198X_MSPWT, AC97_AD198X_MSPWT);
	ac97->fwags |= AC97_STEWEO_MUTES;
	check_ad1981_hp_jack_sense(ac97);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ac97_ad198x_2cmic =
AC97_SINGWE("Steweo Mic", AC97_AD_MISC, 6, 1, 0);

static int patch_ad1981b_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, &snd_ac97_ad198x_2cmic, 1);
	if (eww < 0)
		wetuwn eww;
	if (check_wist(ac97, ad1981_jacks_denywist))
		wetuwn 0;
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_ad1981x_jack_sense,
				    AWWAY_SIZE(snd_ac97_ad1981x_jack_sense));
}

static const stwuct snd_ac97_buiwd_ops patch_ad1981b_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1981b_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume
#endif
};

static int patch_ad1981b(stwuct snd_ac97 *ac97)
{
	patch_ad1881(ac97);
	ac97->buiwd_ops = &patch_ad1981b_buiwd_ops;
	snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD198X_MSPWT, AC97_AD198X_MSPWT);
	ac97->fwags |= AC97_STEWEO_MUTES;
	check_ad1981_hp_jack_sense(ac97);
	wetuwn 0;
}

#define snd_ac97_ad1888_wohpsew_info	snd_ctw_boowean_mono_info

static int snd_ac97_ad1888_wohpsew_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AD_MISC];
	ucontwow->vawue.integew.vawue[0] = !(vaw & AC97_AD198X_WOSEW);
	if (ac97->spec.ad18xx.wo_as_mastew)
		ucontwow->vawue.integew.vawue[0] =
			!ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static int snd_ac97_ad1888_wohpsew_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = !ucontwow->vawue.integew.vawue[0];
	if (ac97->spec.ad18xx.wo_as_mastew)
		vaw = !vaw;
	vaw = vaw ? (AC97_AD198X_WOSEW | AC97_AD198X_HPSEW) : 0;
	wetuwn snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_WOSEW | AC97_AD198X_HPSEW, vaw);
}

static int snd_ac97_ad1888_downmix_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] = {"Off", "6 -> 4", "6 -> 2"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int snd_ac97_ad1888_downmix_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AD_MISC];
	if (!(vaw & AC97_AD198X_DMIX1))
		ucontwow->vawue.enumewated.item[0] = 0;
	ewse
		ucontwow->vawue.enumewated.item[0] = 1 + ((vaw >> 8) & 1);
	wetuwn 0;
}

static int snd_ac97_ad1888_downmix_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 2)
		wetuwn -EINVAW;
	if (ucontwow->vawue.enumewated.item[0] == 0)
		vaw = 0;
	ewse
		vaw = AC97_AD198X_DMIX1 |
			((ucontwow->vawue.enumewated.item[0] - 1) << 8);
	wetuwn snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_DMIX0 | AC97_AD198X_DMIX1, vaw);
}

static void ad1888_update_jacks(stwuct snd_ac97 *ac97)
{
	unsigned showt vaw = 0;
	/* cweaw WODIS if shawed jack is to be used fow Suwwound out */
	if (!ac97->spec.ad18xx.wo_as_mastew && is_shawed_winein(ac97))
		vaw |= (1 << 12);
	/* cweaw CWDIS if shawed jack is to be used fow C/WFE out */
	if (is_shawed_micin(ac97))
		vaw |= (1 << 11);
	/* shawed Wine-In */
	snd_ac97_update_bits(ac97, AC97_AD_MISC, (1 << 11) | (1 << 12), vaw);
}

static const stwuct snd_kcontwow_new snd_ac97_ad1888_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Exchange Fwont/Suwwound",
		.info = snd_ac97_ad1888_wohpsew_info,
		.get = snd_ac97_ad1888_wohpsew_get,
		.put = snd_ac97_ad1888_wohpsew_put
	},
	AC97_SINGWE("V_WEFOUT Enabwe", AC97_AD_MISC, AC97_AD_VWEFD_SHIFT, 1, 1),
	AC97_SINGWE("High Pass Fiwtew Enabwe", AC97_AD_TEST2,
			AC97_AD_HPFD_SHIFT, 1, 1),
	AC97_SINGWE("Spwead Fwont to Suwwound and Centew/WFE", AC97_AD_MISC, 7, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Downmix",
		.info = snd_ac97_ad1888_downmix_info,
		.get = snd_ac97_ad1888_downmix_get,
		.put = snd_ac97_ad1888_downmix_put
	},
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,

	AC97_SINGWE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGWE("Wine Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
};

static int patch_ad1888_specific(stwuct snd_ac97 *ac97)
{
	if (!ac97->spec.ad18xx.wo_as_mastew) {
		/* wename 0x04 as "Mastew" and 0x02 as "Mastew Suwwound" */
		snd_ac97_wename_vow_ctw(ac97, "Mastew Pwayback",
					"Mastew Suwwound Pwayback");
		snd_ac97_wename_vow_ctw(ac97, "Headphone Pwayback",
					"Mastew Pwayback");
	}
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_ad1888_contwows, AWWAY_SIZE(snd_ac97_ad1888_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_ad1888_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1888_specific,
#ifdef CONFIG_PM
	.wesume = ad1888_wesume,
#endif
	.update_jacks = ad1888_update_jacks,
};

static int patch_ad1888(stwuct snd_ac97 * ac97)
{
	unsigned showt misc;
	
	patch_ad1881(ac97);
	ac97->buiwd_ops = &patch_ad1888_buiwd_ops;

	/*
	 * WO can be used as a weaw wine-out on some devices,
	 * and we need to wevewt the fwont/suwwound mixew switches
	 */
	if (ac97->subsystem_vendow == 0x1043 &&
	    ac97->subsystem_device == 0x1193) /* ASUS A9T waptop */
		ac97->spec.ad18xx.wo_as_mastew = 1;

	misc = snd_ac97_wead(ac97, AC97_AD_MISC);
	/* AD-compatibwe mode */
	/* Steweo mutes enabwed */
	misc |= AC97_AD198X_MSPWT | AC97_AD198X_AC97NC;
	if (!ac97->spec.ad18xx.wo_as_mastew)
		/* Switch FWONT/SUWWOUND WINE-OUT/HP-OUT defauwt connection */
		/* it seems that most vendows connect wine-out connectow to
		 * headphone out of AC'97
		 */
		misc |= AC97_AD198X_WOSEW | AC97_AD198X_HPSEW;

	snd_ac97_wwite_cache(ac97, AC97_AD_MISC, misc);
	ac97->fwags |= AC97_STEWEO_MUTES;
	wetuwn 0;
}

static int patch_ad1980_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_ad1888_specific(ac97);
	if (eww < 0)
		wetuwn eww;
	wetuwn patch_buiwd_contwows(ac97, &snd_ac97_ad198x_2cmic, 1);
}

static const stwuct snd_ac97_buiwd_ops patch_ad1980_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1980_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume,
#endif
	.update_jacks = ad1888_update_jacks,
};

static int patch_ad1980(stwuct snd_ac97 * ac97)
{
	patch_ad1888(ac97);
	ac97->buiwd_ops = &patch_ad1980_buiwd_ops;
	wetuwn 0;
}

static int snd_ac97_ad1985_vwefout_info(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"High-Z", "3.7 V", "2.25 V", "0 V"
	};

	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}

static int snd_ac97_ad1985_vwefout_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	static const int weg2ctww[4] = {2, 0, 1, 3};
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;
	vaw = (ac97->wegs[AC97_AD_MISC] & AC97_AD198X_VWEF_MASK)
	      >> AC97_AD198X_VWEF_SHIFT;
	ucontwow->vawue.enumewated.item[0] = weg2ctww[vaw];
	wetuwn 0;
}

static int snd_ac97_ad1985_vwefout_put(stwuct snd_kcontwow *kcontwow, 
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	static const int ctww2weg[4] = {1, 2, 0, 3};
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	if (ucontwow->vawue.enumewated.item[0] > 3)
		wetuwn -EINVAW;
	vaw = ctww2weg[ucontwow->vawue.enumewated.item[0]]
	      << AC97_AD198X_VWEF_SHIFT;
	wetuwn snd_ac97_update_bits(ac97, AC97_AD_MISC,
				    AC97_AD198X_VWEF_MASK, vaw);
}

static const stwuct snd_kcontwow_new snd_ac97_ad1985_contwows[] = {
	AC97_SINGWE("Exchange Centew/WFE", AC97_AD_SEWIAW_CFG, 3, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Exchange Fwont/Suwwound",
		.info = snd_ac97_ad1888_wohpsew_info,
		.get = snd_ac97_ad1888_wohpsew_get,
		.put = snd_ac97_ad1888_wohpsew_put
	},
	AC97_SINGWE("High Pass Fiwtew Enabwe", AC97_AD_TEST2, 12, 1, 1),
	AC97_SINGWE("Spwead Fwont to Suwwound and Centew/WFE",
		    AC97_AD_MISC, 7, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Downmix",
		.info = snd_ac97_ad1888_downmix_info,
		.get = snd_ac97_ad1888_downmix_get,
		.put = snd_ac97_ad1888_downmix_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "V_WEFOUT",
		.info = snd_ac97_ad1985_vwefout_info,
		.get = snd_ac97_ad1985_vwefout_get,
		.put = snd_ac97_ad1985_vwefout_put
	},
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,

	AC97_SINGWE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGWE("Wine Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0),
};

static void ad1985_update_jacks(stwuct snd_ac97 *ac97)
{
	ad1888_update_jacks(ac97);
	/* cweaw OMS if shawed jack is to be used fow C/WFE out */
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG, 1 << 9,
			     is_shawed_micin(ac97) ? 1 << 9 : 0);
}

static int patch_ad1985_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	/* wename 0x04 as "Mastew" and 0x02 as "Mastew Suwwound" */
	snd_ac97_wename_vow_ctw(ac97, "Mastew Pwayback",
				"Mastew Suwwound Pwayback");
	snd_ac97_wename_vow_ctw(ac97, "Headphone Pwayback", "Mastew Pwayback");

	eww = patch_buiwd_contwows(ac97, &snd_ac97_ad198x_2cmic, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn patch_buiwd_contwows(ac97, snd_ac97_ad1985_contwows,
				    AWWAY_SIZE(snd_ac97_ad1985_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_ad1985_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1985_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume,
#endif
	.update_jacks = ad1985_update_jacks,
};

static int patch_ad1985(stwuct snd_ac97 * ac97)
{
	unsigned showt misc;
	
	patch_ad1881(ac97);
	ac97->buiwd_ops = &patch_ad1985_buiwd_ops;
	misc = snd_ac97_wead(ac97, AC97_AD_MISC);
	/* switch fwont/suwwound wine-out/hp-out */
	/* AD-compatibwe mode */
	/* Steweo mutes enabwed */
	snd_ac97_wwite_cache(ac97, AC97_AD_MISC, misc |
			     AC97_AD198X_WOSEW |
			     AC97_AD198X_HPSEW |
			     AC97_AD198X_MSPWT |
			     AC97_AD198X_AC97NC);
	ac97->fwags |= AC97_STEWEO_MUTES;

	/* update cuwwent jack configuwation */
	ad1985_update_jacks(ac97);

	/* on AD1985 wev. 3, AC'97 wevision bits awe zewo */
	ac97->ext_id = (ac97->ext_id & ~AC97_EI_WEV_MASK) | AC97_EI_WEV_23;
	wetuwn 0;
}

#define snd_ac97_ad1986_boow_info	snd_ctw_boowean_mono_info

static int snd_ac97_ad1986_wososew_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AD_MISC3];
	ucontwow->vawue.integew.vawue[0] = (vaw & AC97_AD1986_WOSEW) != 0;
	wetuwn 0;
}

static int snd_ac97_ad1986_wososew_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int wet0;
	int wet1;
	int spwd = (ac97->wegs[AC97_AD_MISC] & AC97_AD1986_SPWD) != 0;

	wet0 = snd_ac97_update_bits(ac97, AC97_AD_MISC3, AC97_AD1986_WOSEW,
					ucontwow->vawue.integew.vawue[0] != 0
				    ? AC97_AD1986_WOSEW : 0);
	if (wet0 < 0)
		wetuwn wet0;

	/* SOSEW is set to vawues of "Spwead" ow "Exchange F/S" contwows */
	wet1 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SOSEW,
				    (ucontwow->vawue.integew.vawue[0] != 0
				     || spwd)
				    ? AC97_AD1986_SOSEW : 0);
	if (wet1 < 0)
		wetuwn wet1;

	wetuwn (wet0 > 0 || wet1 > 0) ? 1 : 0;
}

static int snd_ac97_ad1986_spwead_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AD_MISC];
	ucontwow->vawue.integew.vawue[0] = (vaw & AC97_AD1986_SPWD) != 0;
	wetuwn 0;
}

static int snd_ac97_ad1986_spwead_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	int wet0;
	int wet1;
	int spwd = (ac97->wegs[AC97_AD_MISC3] & AC97_AD1986_WOSEW) != 0;

	wet0 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SPWD,
					ucontwow->vawue.integew.vawue[0] != 0
				    ? AC97_AD1986_SPWD : 0);
	if (wet0 < 0)
		wetuwn wet0;

	/* SOSEW is set to vawues of "Spwead" ow "Exchange F/S" contwows */
	wet1 = snd_ac97_update_bits(ac97, AC97_AD_MISC, AC97_AD1986_SOSEW,
				    (ucontwow->vawue.integew.vawue[0] != 0
				     || spwd)
				    ? AC97_AD1986_SOSEW : 0);
	if (wet1 < 0)
		wetuwn wet1;

	wetuwn (wet0 > 0 || wet1 > 0) ? 1 : 0;
}

static int snd_ac97_ad1986_micwisew_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	ucontwow->vawue.integew.vawue[0] = ac97->spec.ad18xx.swap_mic_winein;
	wetuwn 0;
}

static int snd_ac97_ad1986_micwisew_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned chaw swap = ucontwow->vawue.integew.vawue[0] != 0;

	if (swap != ac97->spec.ad18xx.swap_mic_winein) {
		ac97->spec.ad18xx.swap_mic_winein = swap;
		if (ac97->buiwd_ops->update_jacks)
			ac97->buiwd_ops->update_jacks(ac97);
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_ac97_ad1986_vwefout_get(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	/* Use MIC_1/2 V_WEFOUT as the "get" vawue */
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;
	unsigned showt weg = ac97->wegs[AC97_AD_MISC2];
	if ((weg & AC97_AD1986_MVWEF0) != 0)
		vaw = 2;
	ewse if ((weg & AC97_AD1986_MVWEF1) != 0)
		vaw = 3;
	ewse if ((weg & AC97_AD1986_MVWEF2) != 0)
		vaw = 1;
	ewse
		vaw = 0;
	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int snd_ac97_ad1986_vwefout_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt cvaw;
	unsigned showt wvaw;
	unsigned showt mvaw;
	int cwet;
	int wwet;
	int mwet;

	switch (ucontwow->vawue.enumewated.item[0])
	{
	case 0: /* High-Z */
		cvaw = 0;
		wvaw = 0;
		mvaw = 0;
		bweak;
	case 1: /* 3.7 V */
		cvaw = AC97_AD1986_CVWEF2;
		wvaw = AC97_AD1986_WVWEF2;
		mvaw = AC97_AD1986_MVWEF2;
		bweak;
	case 2: /* 2.25 V */
		cvaw = AC97_AD1986_CVWEF0;
		wvaw = AC97_AD1986_WVWEF0;
		mvaw = AC97_AD1986_MVWEF0;
		bweak;
	case 3: /* 0 V */
		cvaw = AC97_AD1986_CVWEF1;
		wvaw = AC97_AD1986_WVWEF1;
		mvaw = AC97_AD1986_MVWEF1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cwet = snd_ac97_update_bits(ac97, AC97_AD_MISC2,
				    AC97_AD1986_CVWEF_MASK, cvaw);
	if (cwet < 0)
		wetuwn cwet;
	wwet = snd_ac97_update_bits(ac97, AC97_AD_MISC3,
				    AC97_AD1986_WVWEF_MASK, wvaw);
	if (wwet < 0)
		wetuwn wwet;
	mwet = snd_ac97_update_bits(ac97, AC97_AD_MISC2,
				    AC97_AD1986_MVWEF_MASK, mvaw);
	if (mwet < 0)
		wetuwn mwet;

	wetuwn (cwet > 0 || wwet > 0 || mwet > 0) ? 1 : 0;
}

static const stwuct snd_kcontwow_new snd_ac97_ad1986_contwows[] = {
	AC97_SINGWE("Exchange Centew/WFE", AC97_AD_SEWIAW_CFG, 3, 1, 0),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Exchange Fwont/Suwwound",
		.info = snd_ac97_ad1986_boow_info,
		.get = snd_ac97_ad1986_wososew_get,
		.put = snd_ac97_ad1986_wososew_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Exchange Mic/Wine In",
		.info = snd_ac97_ad1986_boow_info,
		.get = snd_ac97_ad1986_micwisew_get,
		.put = snd_ac97_ad1986_micwisew_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Spwead Fwont to Suwwound and Centew/WFE",
		.info = snd_ac97_ad1986_boow_info,
		.get = snd_ac97_ad1986_spwead_get,
		.put = snd_ac97_ad1986_spwead_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Downmix",
		.info = snd_ac97_ad1888_downmix_info,
		.get = snd_ac97_ad1888_downmix_get,
		.put = snd_ac97_ad1888_downmix_put
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "V_WEFOUT",
		.info = snd_ac97_ad1985_vwefout_info,
		.get = snd_ac97_ad1986_vwefout_get,
		.put = snd_ac97_ad1986_vwefout_put
	},
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,

	AC97_SINGWE("Headphone Jack Sense", AC97_AD_JACK_SPDIF, 10, 1, 0),
	AC97_SINGWE("Wine Jack Sense", AC97_AD_JACK_SPDIF, 12, 1, 0)
};

static void ad1986_update_jacks(stwuct snd_ac97 *ac97)
{
	unsigned showt misc_vaw = 0;
	unsigned showt sew_vaw;

	/* disabwe SUWWOUND and CENTEW/WFE if not suwwound mode */
	if (!is_suwwound_on(ac97))
		misc_vaw |= AC97_AD1986_SODIS;
	if (!is_cwfe_on(ac97))
		misc_vaw |= AC97_AD1986_CWDIS;

	/* sewect wine input (defauwt=WINE_IN, SUWWOUND ow MIC_1/2) */
	if (is_shawed_winein(ac97))
		misc_vaw |= AC97_AD1986_WISEW_SUWW;
	ewse if (ac97->spec.ad18xx.swap_mic_winein != 0)
		misc_vaw |= AC97_AD1986_WISEW_MIC;
	snd_ac97_update_bits(ac97, AC97_AD_MISC,
			     AC97_AD1986_SODIS | AC97_AD1986_CWDIS |
			     AC97_AD1986_WISEW_MASK,
			     misc_vaw);

	/* sewect micwophone input (MIC_1/2, Centew/WFE ow WINE_IN) */
	if (is_shawed_micin(ac97))
		sew_vaw = AC97_AD1986_OMS_C;
	ewse if (ac97->spec.ad18xx.swap_mic_winein != 0)
		sew_vaw = AC97_AD1986_OMS_W;
	ewse
		sew_vaw = AC97_AD1986_OMS_M;
	snd_ac97_update_bits(ac97, AC97_AD_SEWIAW_CFG,
			     AC97_AD1986_OMS_MASK,
			     sew_vaw);
}

static int patch_ad1986_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, &snd_ac97_ad198x_2cmic, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn patch_buiwd_contwows(ac97, snd_ac97_ad1986_contwows,
				    AWWAY_SIZE(snd_ac97_ad1985_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_ad1986_buiwd_ops = {
	.buiwd_post_spdif = patch_ad198x_post_spdif,
	.buiwd_specific = patch_ad1986_specific,
#ifdef CONFIG_PM
	.wesume = ad18xx_wesume,
#endif
	.update_jacks = ad1986_update_jacks,
};

static int patch_ad1986(stwuct snd_ac97 * ac97)
{
	patch_ad1881(ac97);
	ac97->buiwd_ops = &patch_ad1986_buiwd_ops;
	ac97->fwags |= AC97_STEWEO_MUTES;

	/* update cuwwent jack configuwation */
	ad1986_update_jacks(ac97);

	wetuwn 0;
}

/*
 * weawtek AWC203: use mono-out fow pin 37
 */
static int patch_awc203(stwuct snd_ac97 *ac97)
{
	snd_ac97_update_bits(ac97, 0x7a, 0x400, 0x400);
	wetuwn 0;
}

/*
 * weawtek AWC65x/850 codecs
 */
static void awc650_update_jacks(stwuct snd_ac97 *ac97)
{
	int shawed;
	
	/* shawed Wine-In / Suwwound Out */
	shawed = is_shawed_suwwout(ac97);
	snd_ac97_update_bits(ac97, AC97_AWC650_MUWTICH, 1 << 9,
			     shawed ? (1 << 9) : 0);
	/* update shawed Mic In / Centew/WFE Out */
	shawed = is_shawed_cwfeout(ac97);
	/* disabwe/enabwe vwef */
	snd_ac97_update_bits(ac97, AC97_AWC650_CWOCK, 1 << 12,
			     shawed ? (1 << 12) : 0);
	/* tuwn on/off centew-on-mic */
	snd_ac97_update_bits(ac97, AC97_AWC650_MUWTICH, 1 << 10,
			     shawed ? (1 << 10) : 0);
	/* GPIO0 high fow mic */
	snd_ac97_update_bits(ac97, AC97_AWC650_GPIO_STATUS, 0x100,
			     shawed ? 0 : 0x100);
}

static int awc650_swap_suwwound_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	stwuct snd_pcm_chmap *map = ac97->chmaps[SNDWV_PCM_STWEAM_PWAYBACK];

	if (map) {
		if (ucontwow->vawue.integew.vawue[0])
			map->chmap = snd_pcm_std_chmaps;
		ewse
			map->chmap = snd_pcm_awt_chmaps;
	}
	wetuwn snd_ac97_put_vowsw(kcontwow, ucontwow);
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_awc650[] = {
	AC97_SINGWE("Dupwicate Fwont", AC97_AWC650_MUWTICH, 0, 1, 0),
	AC97_SINGWE("Suwwound Down Mix", AC97_AWC650_MUWTICH, 1, 1, 0),
	AC97_SINGWE("Centew/WFE Down Mix", AC97_AWC650_MUWTICH, 2, 1, 0),
	AC97_SINGWE("Exchange Centew/WFE", AC97_AWC650_MUWTICH, 3, 1, 0),
	/* 4: Anawog Input To Suwwound */
	/* 5: Anawog Input To Centew/WFE */
	/* 6: Independent Mastew Vowume Wight */
	/* 7: Independent Mastew Vowume Weft */
	/* 8: wesewved */
	/* 9: Wine-In/Suwwound shawe */
	/* 10: Mic/CWFE shawe */
	/* 11-13: in IEC958 contwows */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Swap Suwwound Swot",
		.info = snd_ac97_info_vowsw,
		.get = snd_ac97_get_vowsw,
		.put = awc650_swap_suwwound_put,
		.pwivate_vawue =  AC97_SINGWE_VAWUE(AC97_AWC650_MUWTICH, 14, 1, 0),
	},
#if 0 /* awways set in patch_awc650 */
	AC97_SINGWE("IEC958 Input Cwock Enabwe", AC97_AWC650_CWOCK, 0, 1, 0),
	AC97_SINGWE("IEC958 Input Pin Enabwe", AC97_AWC650_CWOCK, 1, 1, 0),
	AC97_SINGWE("Suwwound DAC Switch", AC97_AWC650_SUWW_DAC_VOW, 15, 1, 1),
	AC97_DOUBWE("Suwwound DAC Vowume", AC97_AWC650_SUWW_DAC_VOW, 8, 0, 31, 1),
	AC97_SINGWE("Centew/WFE DAC Switch", AC97_AWC650_WFE_DAC_VOW, 15, 1, 1),
	AC97_DOUBWE("Centew/WFE DAC Vowume", AC97_AWC650_WFE_DAC_VOW, 8, 0, 31, 1),
#endif
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,
};

static const stwuct snd_kcontwow_new snd_ac97_spdif_contwows_awc650[] = {
        AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), AC97_AWC650_MUWTICH, 11, 1, 0),
        AC97_SINGWE("Anawog to IEC958 Output", AC97_AWC650_MUWTICH, 12, 1, 0),
	/* disabwe this contwows since it doesn't wowk as expected */
	/* AC97_SINGWE("IEC958 Input Monitow", AC97_AWC650_MUWTICH, 13, 1, 0), */
};

static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit_3db_max, -4350, 150, 0);

static int patch_awc650_specific(stwuct snd_ac97 * ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, snd_ac97_contwows_awc650, AWWAY_SIZE(snd_ac97_contwows_awc650));
	if (eww < 0)
		wetuwn eww;
	if (ac97->ext_id & AC97_EI_SPDIF) {
		eww = patch_buiwd_contwows(ac97, snd_ac97_spdif_contwows_awc650, AWWAY_SIZE(snd_ac97_spdif_contwows_awc650));
		if (eww < 0)
			wetuwn eww;
	}
	if (ac97->id != AC97_ID_AWC650F)
		weset_twv(ac97, "Mastew Pwayback Vowume",
			  db_scawe_5bit_3db_max);
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_awc650_ops = {
	.buiwd_specific	= patch_awc650_specific,
	.update_jacks = awc650_update_jacks
};

static int patch_awc650(stwuct snd_ac97 * ac97)
{
	unsigned showt vaw;

	ac97->buiwd_ops = &patch_awc650_ops;

	/* detewmine the wevision */
	vaw = snd_ac97_wead(ac97, AC97_AWC650_WEVISION) & 0x3f;
	if (vaw < 3)
		ac97->id = 0x414c4720;          /* Owd vewsion */
	ewse if (vaw < 0x10)
		ac97->id = 0x414c4721;          /* D vewsion */
	ewse if (vaw < 0x20)
		ac97->id = 0x414c4722;          /* E vewsion */
	ewse if (vaw < 0x30)
		ac97->id = 0x414c4723;          /* F vewsion */

	/* wevision E ow F */
	/* FIXME: what about wevision D ? */
	ac97->spec.dev_fwags = (ac97->id == 0x414c4722 ||
				ac97->id == 0x414c4723);

	/* enabwe AC97_AWC650_GPIO_SETUP, AC97_AWC650_CWOCK fow W/W */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_GPIO_STATUS, 
		snd_ac97_wead(ac97, AC97_AWC650_GPIO_STATUS) | 0x8000);

	/* Enabwe SPDIF-IN onwy on Wev.E and above */
	vaw = snd_ac97_wead(ac97, AC97_AWC650_CWOCK);
	/* SPDIF IN with pin 47 */
	if (ac97->spec.dev_fwags &&
	    /* ASUS A6KM wequiwes EAPD */
	    ! (ac97->subsystem_vendow == 0x1043 &&
	       ac97->subsystem_device == 0x1103))
		vaw |= 0x03; /* enabwe */
	ewse
		vaw &= ~0x03; /* disabwe */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_CWOCK, vaw);

	/* set defauwt: swot 3,4,7,8,6,9
	   spdif-in monitow off, anawog-spdif off, spdif-in off
	   centew on mic off, suwwound on wine-in off
	   downmix off, dupwicate fwont off
	*/
	snd_ac97_wwite_cache(ac97, AC97_AWC650_MUWTICH, 0);

	/* set GPIO0 fow mic bias */
	/* GPIO0 pin output, no intewwupt, high */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_GPIO_SETUP,
			     snd_ac97_wead(ac97, AC97_AWC650_GPIO_SETUP) | 0x01);
	snd_ac97_wwite_cache(ac97, AC97_AWC650_GPIO_STATUS,
			     (snd_ac97_wead(ac97, AC97_AWC650_GPIO_STATUS) | 0x100) & ~0x10);

	/* fuww DAC vowume */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_SUWW_DAC_VOW, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_AWC650_WFE_DAC_VOW, 0x0808);
	wetuwn 0;
}

static void awc655_update_jacks(stwuct snd_ac97 *ac97)
{
	int shawed;
	
	/* shawed Wine-In / Suwwound Out */
	shawed = is_shawed_suwwout(ac97);
	ac97_update_bits_page(ac97, AC97_AWC650_MUWTICH, 1 << 9,
			      shawed ? (1 << 9) : 0, 0);
	/* update shawed Mic In / Centew/WFE Out */
	shawed = is_shawed_cwfeout(ac97);
	/* misc contwow; vwefout disabwe */
	snd_ac97_update_bits(ac97, AC97_AWC650_CWOCK, 1 << 12,
			     shawed ? (1 << 12) : 0);
	ac97_update_bits_page(ac97, AC97_AWC650_MUWTICH, 1 << 10,
			      shawed ? (1 << 10) : 0, 0);
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_awc655[] = {
	AC97_PAGE_SINGWE("Dupwicate Fwont", AC97_AWC650_MUWTICH, 0, 1, 0, 0),
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,
};

static int awc655_iec958_woute_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts_655[3] = {
		"PCM", "Anawog In", "IEC958 In"
	};
	static const chaw * const texts_658[4] = {
		"PCM", "Anawog1 In", "Anawog2 In", "IEC958 In"
	};
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	if (ac97->spec.dev_fwags)
		wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts_658);
	ewse
		wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts_655);
}

static int awc655_iec958_woute_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_AWC650_MUWTICH];
	vaw = (vaw >> 12) & 3;
	if (ac97->spec.dev_fwags && vaw == 3)
		vaw = 0;
	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int awc655_iec958_woute_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	wetuwn ac97_update_bits_page(ac97, AC97_AWC650_MUWTICH, 3 << 12,
				     (unsigned showt)ucontwow->vawue.enumewated.item[0] << 12,
				     0);
}

static const stwuct snd_kcontwow_new snd_ac97_spdif_contwows_awc655[] = {
        AC97_PAGE_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), AC97_AWC650_MUWTICH, 11, 1, 0, 0),
	/* disabwe this contwows since it doesn't wowk as expected */
        /* AC97_PAGE_SINGWE("IEC958 Input Monitow", AC97_AWC650_MUWTICH, 14, 1, 0, 0), */
	{
		.iface  = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name   = SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Souwce",
		.info   = awc655_iec958_woute_info,
		.get    = awc655_iec958_woute_get,
		.put    = awc655_iec958_woute_put,
	},
};

static int patch_awc655_specific(stwuct snd_ac97 * ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, snd_ac97_contwows_awc655, AWWAY_SIZE(snd_ac97_contwows_awc655));
	if (eww < 0)
		wetuwn eww;
	if (ac97->ext_id & AC97_EI_SPDIF) {
		eww = patch_buiwd_contwows(ac97, snd_ac97_spdif_contwows_awc655, AWWAY_SIZE(snd_ac97_spdif_contwows_awc655));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_awc655_ops = {
	.buiwd_specific	= patch_awc655_specific,
	.update_jacks = awc655_update_jacks
};

static int patch_awc655(stwuct snd_ac97 * ac97)
{
	unsigned int vaw;

	if (ac97->id == AC97_ID_AWC658) {
		ac97->spec.dev_fwags = 1; /* AWC658 */
		if ((snd_ac97_wead(ac97, AC97_AWC650_WEVISION) & 0x3f) == 2) {
			ac97->id = AC97_ID_AWC658D;
			ac97->spec.dev_fwags = 2;
		}
	}

	ac97->buiwd_ops = &patch_awc655_ops;

	/* assume onwy page 0 fow wwiting cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOW);

	/* adjust defauwt vawues */
	vaw = snd_ac97_wead(ac97, 0x7a); /* misc contwow */
	if (ac97->spec.dev_fwags) /* AWC658 */
		vaw &= ~(1 << 1); /* Pin 47 is spdif input pin */
	ewse { /* AWC655 */
		if (ac97->subsystem_vendow == 0x1462 &&
		    (ac97->subsystem_device == 0x0131 || /* MSI S270 waptop */
		     ac97->subsystem_device == 0x0161 || /* WG K1 Expwess */
		     ac97->subsystem_device == 0x0351 || /* MSI W725 waptop */
		     ac97->subsystem_device == 0x0471 || /* MSI W720 waptop */
		     ac97->subsystem_device == 0x0061))  /* MSI S250 waptop */
			vaw &= ~(1 << 1); /* Pin 47 is EAPD (fow intewnaw speakew) */
		ewse
			vaw |= (1 << 1); /* Pin 47 is spdif input pin */
		/* this seems missing on some hawdwawes */
		ac97->ext_id |= AC97_EI_SPDIF;
	}
	vaw &= ~(1 << 12); /* vwef enabwe */
	snd_ac97_wwite_cache(ac97, 0x7a, vaw);
	/* set defauwt: spdif-in enabwed,
	   spdif-in monitow off, spdif-in PCM off
	   centew on mic off, suwwound on wine-in off
	   dupwicate fwont off
	*/
	snd_ac97_wwite_cache(ac97, AC97_AWC650_MUWTICH, 1<<15);

	/* fuww DAC vowume */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_SUWW_DAC_VOW, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_AWC650_WFE_DAC_VOW, 0x0808);

	/* update undocumented bit... */
	if (ac97->id == AC97_ID_AWC658D)
		snd_ac97_update_bits(ac97, 0x74, 0x0800, 0x0800);

	wetuwn 0;
}


#define AC97_AWC850_JACK_SEWECT	0x76
#define AC97_AWC850_MISC1	0x7a
#define AC97_AWC850_MUWTICH    0x6a

static void awc850_update_jacks(stwuct snd_ac97 *ac97)
{
	int shawed;
	int aux_is_back_suwwound;
	
	/* shawed Wine-In / Suwwound Out */
	shawed = is_shawed_suwwout(ac97);
	/* SUWW 1kOhm (bit4), Amp (bit5) */
	snd_ac97_update_bits(ac97, AC97_AWC850_MISC1, (1<<4)|(1<<5),
			     shawed ? (1<<5) : (1<<4));
	/* WINE-IN = 0, SUWWOUND = 2 */
	snd_ac97_update_bits(ac97, AC97_AWC850_JACK_SEWECT, 7 << 12,
			     shawed ? (2<<12) : (0<<12));
	/* update shawed Mic In / Centew/WFE Out */
	shawed = is_shawed_cwfeout(ac97);
	/* Vwef disabwe (bit12), 1kOhm (bit13) */
	snd_ac97_update_bits(ac97, AC97_AWC850_MISC1, (1<<12)|(1<<13),
			     shawed ? (1<<12) : (1<<13));
	/* MIC-IN = 1, CENTEW-WFE = 5 */
	snd_ac97_update_bits(ac97, AC97_AWC850_JACK_SEWECT, 7 << 4,
			     shawed ? (5<<4) : (1<<4));

	aux_is_back_suwwound = awc850_is_aux_back_suwwound(ac97);
	/* Aux is Back Suwwound */
	snd_ac97_update_bits(ac97, AC97_AWC850_MUWTICH, 1 << 10,
				 aux_is_back_suwwound ? (1<<10) : (0<<10));
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_awc850[] = {
	AC97_PAGE_SINGWE("Dupwicate Fwont", AC97_AWC650_MUWTICH, 0, 1, 0, 0),
	AC97_SINGWE("Mic Fwont Input Switch", AC97_AWC850_JACK_SEWECT, 15, 1, 1),
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_8CH_CTW,
};

static int patch_awc850_specific(stwuct snd_ac97 *ac97)
{
	int eww;

	eww = patch_buiwd_contwows(ac97, snd_ac97_contwows_awc850, AWWAY_SIZE(snd_ac97_contwows_awc850));
	if (eww < 0)
		wetuwn eww;
	if (ac97->ext_id & AC97_EI_SPDIF) {
		eww = patch_buiwd_contwows(ac97, snd_ac97_spdif_contwows_awc655, AWWAY_SIZE(snd_ac97_spdif_contwows_awc655));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_awc850_ops = {
	.buiwd_specific	= patch_awc850_specific,
	.update_jacks = awc850_update_jacks
};

static int patch_awc850(stwuct snd_ac97 *ac97)
{
	ac97->buiwd_ops = &patch_awc850_ops;

	ac97->spec.dev_fwags = 0; /* fow IEC958 pwayback woute - AWC655 compatibwe */
	ac97->fwags |= AC97_HAS_8CH;

	/* assume onwy page 0 fow wwiting cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOW);

	/* adjust defauwt vawues */
	/* set defauwt: spdif-in enabwed,
	   spdif-in monitow off, spdif-in PCM off
	   centew on mic off, suwwound on wine-in off
	   dupwicate fwont off
	   NB defauwt bit 10=0 = Aux is Captuwe, not Back Suwwound
	*/
	snd_ac97_wwite_cache(ac97, AC97_AWC650_MUWTICH, 1<<15);
	/* SUWW_OUT: on, Suww 1kOhm: on, Suww Amp: off, Fwont 1kOhm: off
	 * Fwont Amp: on, Vwef: enabwe, Centew 1kOhm: on, Mix: on
	 */
	snd_ac97_wwite_cache(ac97, 0x7a, (1<<1)|(1<<4)|(0<<5)|(1<<6)|
			     (1<<7)|(0<<12)|(1<<13)|(0<<14));
	/* detection UIO2,3: aww path fwoating, UIO3: MIC, Vwef2: disabwe,
	 * UIO1: FWONT, Vwef3: disabwe, UIO3: WINE, Fwont-Mic: mute
	 */
	snd_ac97_wwite_cache(ac97, 0x76, (0<<0)|(0<<2)|(1<<4)|(1<<7)|(2<<8)|
			     (1<<11)|(0<<12)|(1<<15));

	/* fuww DAC vowume */
	snd_ac97_wwite_cache(ac97, AC97_AWC650_SUWW_DAC_VOW, 0x0808);
	snd_ac97_wwite_cache(ac97, AC97_AWC650_WFE_DAC_VOW, 0x0808);
	wetuwn 0;
}

static int patch_aztech_azf3328_specific(stwuct snd_ac97 *ac97)
{
	stwuct snd_kcontwow *kctw_3d_centew =
		snd_ac97_find_mixew_ctw(ac97, "3D Contwow - Centew");
	stwuct snd_kcontwow *kctw_3d_depth =
		snd_ac97_find_mixew_ctw(ac97, "3D Contwow - Depth");

	/*
	 * 3D wegistew is diffewent fwom AC97 standawd wayout
	 * (awso do some wenaming, to wesembwe Windows dwivew naming)
	 */
	if (kctw_3d_centew) {
		kctw_3d_centew->pwivate_vawue =
			AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 1, 0x07, 0);
		snd_ac97_wename_vow_ctw(ac97,
			"3D Contwow - Centew", "3D Contwow - Width"
		);
	}
	if (kctw_3d_depth)
		kctw_3d_depth->pwivate_vawue =
			AC97_SINGWE_VAWUE(AC97_3D_CONTWOW, 8, 0x03, 0);

	/* Aztech Windows dwivew cawws the
	   equivawent contwow "Modem Pwayback", thus wename it: */
	snd_ac97_wename_vow_ctw(ac97,
		"Mastew Mono Pwayback", "Modem Pwayback"
	);
	snd_ac97_wename_vow_ctw(ac97,
		"Headphone Pwayback", "FM Synth Pwayback"
	);

	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_aztech_azf3328_ops = {
	.buiwd_specific	= patch_aztech_azf3328_specific
};

static int patch_aztech_azf3328(stwuct snd_ac97 *ac97)
{
	ac97->buiwd_ops = &patch_aztech_azf3328_ops;
	wetuwn 0;
}

/*
 * C-Media CM97xx codecs
 */
static void cm9738_update_jacks(stwuct snd_ac97 *ac97)
{
	/* shawed Wine-In / Suwwound Out */
	snd_ac97_update_bits(ac97, AC97_CM9738_VENDOW_CTWW, 1 << 10,
			     is_shawed_suwwout(ac97) ? (1 << 10) : 0);
}

static const stwuct snd_kcontwow_new snd_ac97_cm9738_contwows[] = {
	AC97_SINGWE("Dupwicate Fwont", AC97_CM9738_VENDOW_CTWW, 13, 1, 0),
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_4CH_CTW,
};

static int patch_cm9738_specific(stwuct snd_ac97 * ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_cm9738_contwows, AWWAY_SIZE(snd_ac97_cm9738_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_cm9738_ops = {
	.buiwd_specific	= patch_cm9738_specific,
	.update_jacks = cm9738_update_jacks
};

static int patch_cm9738(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_cm9738_ops;
	/* FIXME: can anyone confiwm bewow? */
	/* CM9738 has no PCM vowume awthough the wegistew weacts */
	ac97->fwags |= AC97_HAS_NO_PCM_VOW;
	snd_ac97_wwite_cache(ac97, AC97_PCM, 0x8000);

	wetuwn 0;
}

static int snd_ac97_cmedia_spdif_pwayback_souwce_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "Anawog", "Digitaw" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ac97_cmedia_spdif_pwayback_souwce_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);
	unsigned showt vaw;

	vaw = ac97->wegs[AC97_CM9739_SPDIF_CTWW];
	ucontwow->vawue.enumewated.item[0] = (vaw >> 1) & 0x01;
	wetuwn 0;
}

static int snd_ac97_cmedia_spdif_pwayback_souwce_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	wetuwn snd_ac97_update_bits(ac97, AC97_CM9739_SPDIF_CTWW,
				    0x01 << 1, 
				    (ucontwow->vawue.enumewated.item[0] & 0x01) << 1);
}

static const stwuct snd_kcontwow_new snd_ac97_cm9739_contwows_spdif[] = {
	/* BIT 0: SPDI_EN - awways twue */
	{ /* BIT 1: SPDIFS */
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Souwce",
		.info	= snd_ac97_cmedia_spdif_pwayback_souwce_info,
		.get	= snd_ac97_cmedia_spdif_pwayback_souwce_get,
		.put	= snd_ac97_cmedia_spdif_pwayback_souwce_put,
	},
	/* BIT 2: IG_SPIV */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,NONE) "Vawid Switch", AC97_CM9739_SPDIF_CTWW, 2, 1, 0),
	/* BIT 3: SPI2F */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,NONE) "Monitow", AC97_CM9739_SPDIF_CTWW, 3, 1, 0), 
	/* BIT 4: SPI2SDI */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), AC97_CM9739_SPDIF_CTWW, 4, 1, 0),
	/* BIT 8: SPD32 - 32bit SPDIF - not suppowted yet */
};

static void cm9739_update_jacks(stwuct snd_ac97 *ac97)
{
	/* shawed Wine-In / Suwwound Out */
	snd_ac97_update_bits(ac97, AC97_CM9739_MUWTI_CHAN, 1 << 10,
			     is_shawed_suwwout(ac97) ? (1 << 10) : 0);
	/* shawed Mic In / Centew/WFE Out **/
	snd_ac97_update_bits(ac97, AC97_CM9739_MUWTI_CHAN, 0x3000,
			     is_shawed_cwfeout(ac97) ? 0x1000 : 0x2000);
}

static const stwuct snd_kcontwow_new snd_ac97_cm9739_contwows[] = {
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,
};

static int patch_cm9739_specific(stwuct snd_ac97 * ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_cm9739_contwows, AWWAY_SIZE(snd_ac97_cm9739_contwows));
}

static int patch_cm9739_post_spdif(stwuct snd_ac97 * ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_cm9739_contwows_spdif, AWWAY_SIZE(snd_ac97_cm9739_contwows_spdif));
}

static const stwuct snd_ac97_buiwd_ops patch_cm9739_ops = {
	.buiwd_specific	= patch_cm9739_specific,
	.buiwd_post_spdif = patch_cm9739_post_spdif,
	.update_jacks = cm9739_update_jacks
};

static int patch_cm9739(stwuct snd_ac97 * ac97)
{
	unsigned showt vaw;

	ac97->buiwd_ops = &patch_cm9739_ops;

	/* CM9739/A has no Mastew and PCM vowume awthough the wegistew weacts */
	ac97->fwags |= AC97_HAS_NO_MASTEW_VOW | AC97_HAS_NO_PCM_VOW;
	snd_ac97_wwite_cache(ac97, AC97_MASTEW, 0x8000);
	snd_ac97_wwite_cache(ac97, AC97_PCM, 0x8000);

	/* check spdif */
	vaw = snd_ac97_wead(ac97, AC97_EXTENDED_STATUS);
	if (vaw & AC97_EA_SPCV) {
		/* enabwe spdif in */
		snd_ac97_wwite_cache(ac97, AC97_CM9739_SPDIF_CTWW,
				     snd_ac97_wead(ac97, AC97_CM9739_SPDIF_CTWW) | 0x01);
		ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_48000; /* 48k onwy */
	} ewse {
		ac97->ext_id &= ~AC97_EI_SPDIF; /* disabwe extended-id */
		ac97->wates[AC97_WATES_SPDIF] = 0;
	}

	/* set-up muwti channew */
	/* bit 14: 0 = SPDIF, 1 = EAPD */
	/* bit 13: enabwe intewnaw vwef output fow mic */
	/* bit 12: disabwe centew/wfe (switchabwe) */
	/* bit 10: disabwe suwwound/wine (switchabwe) */
	/* bit 9: mix 2 suwwound off */
	/* bit 4: undocumented; 0 mutes the CM9739A, which defauwts to 1 */
	/* bit 3: undocumented; suwwound? */
	/* bit 0: dB */
	vaw = snd_ac97_wead(ac97, AC97_CM9739_MUWTI_CHAN) & (1 << 4);
	vaw |= (1 << 3);
	vaw |= (1 << 13);
	if (! (ac97->ext_id & AC97_EI_SPDIF))
		vaw |= (1 << 14);
	snd_ac97_wwite_cache(ac97, AC97_CM9739_MUWTI_CHAN, vaw);

	/* FIXME: set up GPIO */
	snd_ac97_wwite_cache(ac97, 0x70, 0x0100);
	snd_ac97_wwite_cache(ac97, 0x72, 0x0020);
	/* Speciaw exception fow ASUS W1000/CMI9739. It does not have an SPDIF in. */
	if (ac97->pci &&
	     ac97->subsystem_vendow == 0x1043 &&
	     ac97->subsystem_device == 0x1843) {
		snd_ac97_wwite_cache(ac97, AC97_CM9739_SPDIF_CTWW,
			snd_ac97_wead(ac97, AC97_CM9739_SPDIF_CTWW) & ~0x01);
		snd_ac97_wwite_cache(ac97, AC97_CM9739_MUWTI_CHAN,
			snd_ac97_wead(ac97, AC97_CM9739_MUWTI_CHAN) | (1 << 14));
	}

	wetuwn 0;
}

#define AC97_CM9761_MUWTI_CHAN	0x64
#define AC97_CM9761_FUNC	0x66
#define AC97_CM9761_SPDIF_CTWW	0x6c

static void cm9761_update_jacks(stwuct snd_ac97 *ac97)
{
	/* FIXME: check the bits fow each modew
	 *        modew 83 is confiwmed to wowk
	 */
	static const unsigned showt suww_on[3][2] = {
		{ 0x0008, 0x0000 }, /* 9761-78 & 82 */
		{ 0x0000, 0x0008 }, /* 9761-82 wev.B */
		{ 0x0000, 0x0008 }, /* 9761-83 */
	};
	static const unsigned showt cwfe_on[3][2] = {
		{ 0x0000, 0x1000 }, /* 9761-78 & 82 */
		{ 0x1000, 0x0000 }, /* 9761-82 wev.B */
		{ 0x0000, 0x1000 }, /* 9761-83 */
	};
	static const unsigned showt suww_shawed[3][2] = {
		{ 0x0000, 0x0400 }, /* 9761-78 & 82 */
		{ 0x0000, 0x0400 }, /* 9761-82 wev.B */
		{ 0x0000, 0x0400 }, /* 9761-83 */
	};
	static const unsigned showt cwfe_shawed[3][2] = {
		{ 0x2000, 0x0880 }, /* 9761-78 & 82 */
		{ 0x0000, 0x2880 }, /* 9761-82 wev.B */
		{ 0x2000, 0x0800 }, /* 9761-83 */
	};
	unsigned showt vaw = 0;

	vaw |= suww_on[ac97->spec.dev_fwags][is_suwwound_on(ac97)];
	vaw |= cwfe_on[ac97->spec.dev_fwags][is_cwfe_on(ac97)];
	vaw |= suww_shawed[ac97->spec.dev_fwags][is_shawed_suwwout(ac97)];
	vaw |= cwfe_shawed[ac97->spec.dev_fwags][is_shawed_cwfeout(ac97)];

	snd_ac97_update_bits(ac97, AC97_CM9761_MUWTI_CHAN, 0x3c88, vaw);
}

static const stwuct snd_kcontwow_new snd_ac97_cm9761_contwows[] = {
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,
};

static int cm9761_spdif_out_souwce_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[] = { "AC-Wink", "ADC", "SPDIF-In" };

	wetuwn snd_ctw_enum_info(uinfo, 1, 3, texts);
}

static int cm9761_spdif_out_souwce_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	if (ac97->wegs[AC97_CM9761_FUNC] & 0x1)
		ucontwow->vawue.enumewated.item[0] = 2; /* SPDIF-woopback */
	ewse if (ac97->wegs[AC97_CM9761_SPDIF_CTWW] & 0x2)
		ucontwow->vawue.enumewated.item[0] = 1; /* ADC woopback */
	ewse
		ucontwow->vawue.enumewated.item[0] = 0; /* AC-wink */
	wetuwn 0;
}

static int cm9761_spdif_out_souwce_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ac97 *ac97 = snd_kcontwow_chip(kcontwow);

	if (ucontwow->vawue.enumewated.item[0] == 2)
		wetuwn snd_ac97_update_bits(ac97, AC97_CM9761_FUNC, 0x1, 0x1);
	snd_ac97_update_bits(ac97, AC97_CM9761_FUNC, 0x1, 0);
	wetuwn snd_ac97_update_bits(ac97, AC97_CM9761_SPDIF_CTWW, 0x2,
				    ucontwow->vawue.enumewated.item[0] == 1 ? 0x2 : 0);
}

static const chaw * const cm9761_dac_cwock[] = {
	"AC-Wink", "SPDIF-In", "Both"
};
static const stwuct ac97_enum cm9761_dac_cwock_enum =
	AC97_ENUM_SINGWE(AC97_CM9761_SPDIF_CTWW, 9, 3, cm9761_dac_cwock);

static const stwuct snd_kcontwow_new snd_ac97_cm9761_contwows_spdif[] = {
	{ /* BIT 1: SPDIFS */
		.iface	= SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name	= SNDWV_CTW_NAME_IEC958("",PWAYBACK,NONE) "Souwce",
		.info = cm9761_spdif_out_souwce_info,
		.get = cm9761_spdif_out_souwce_get,
		.put = cm9761_spdif_out_souwce_put,
	},
	/* BIT 2: IG_SPIV */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,NONE) "Vawid Switch", AC97_CM9761_SPDIF_CTWW, 2, 1, 0),
	/* BIT 3: SPI2F */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,NONE) "Monitow", AC97_CM9761_SPDIF_CTWW, 3, 1, 0), 
	/* BIT 4: SPI2SDI */
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), AC97_CM9761_SPDIF_CTWW, 4, 1, 0),
	/* BIT 9-10: DAC_CTW */
	AC97_ENUM("DAC Cwock Souwce", cm9761_dac_cwock_enum),
};

static int patch_cm9761_post_spdif(stwuct snd_ac97 * ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_cm9761_contwows_spdif, AWWAY_SIZE(snd_ac97_cm9761_contwows_spdif));
}

static int patch_cm9761_specific(stwuct snd_ac97 * ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_cm9761_contwows, AWWAY_SIZE(snd_ac97_cm9761_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_cm9761_ops = {
	.buiwd_specific	= patch_cm9761_specific,
	.buiwd_post_spdif = patch_cm9761_post_spdif,
	.update_jacks = cm9761_update_jacks
};

static int patch_cm9761(stwuct snd_ac97 *ac97)
{
	unsigned showt vaw;

	/* CM9761 has no PCM vowume awthough the wegistew weacts */
	/* Mastew vowume seems to have _some_ infwuence on the anawog
	 * input sounds
	 */
	ac97->fwags |= /*AC97_HAS_NO_MASTEW_VOW |*/ AC97_HAS_NO_PCM_VOW;
	snd_ac97_wwite_cache(ac97, AC97_MASTEW, 0x8808);
	snd_ac97_wwite_cache(ac97, AC97_PCM, 0x8808);

	ac97->spec.dev_fwags = 0; /* 1 = modew 82 wevision B, 2 = modew 83 */
	if (ac97->id == AC97_ID_CM9761_82) {
		unsigned showt tmp;
		/* check page 1, weg 0x60 */
		vaw = snd_ac97_wead(ac97, AC97_INT_PAGING);
		snd_ac97_wwite_cache(ac97, AC97_INT_PAGING, (vaw & ~0x0f) | 0x01);
		tmp = snd_ac97_wead(ac97, 0x60);
		ac97->spec.dev_fwags = tmp & 1; /* wevision B? */
		snd_ac97_wwite_cache(ac97, AC97_INT_PAGING, vaw);
	} ewse if (ac97->id == AC97_ID_CM9761_83)
		ac97->spec.dev_fwags = 2;

	ac97->buiwd_ops = &patch_cm9761_ops;

	/* enabwe spdif */
	/* fowce the SPDIF bit in ext_id - codec doesn't set this bit! */
        ac97->ext_id |= AC97_EI_SPDIF;
	/* to be suwe: we ovewwwite the ext status bits */
	snd_ac97_wwite_cache(ac97, AC97_EXTENDED_STATUS, 0x05c0);
	/* Don't set 0x0200 hewe.  This wesuwts in the siwent anawog output */
	snd_ac97_wwite_cache(ac97, AC97_CM9761_SPDIF_CTWW, 0x0001); /* enabwe spdif-in */
	ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_48000; /* 48k onwy */

	/* set-up muwti channew */
	/* bit 15: pc mastew beep off
	 * bit 14: pin47 = EAPD/SPDIF
	 * bit 13: vwef ctw [= cm9739]
	 * bit 12: CWFE contwow (wevewted on wev B)
	 * bit 11: Mic/centew shawe (wevewted on wev B)
	 * bit 10: suddound/wine shawe
	 * bit  9: Anawog-in mix -> suwwound
	 * bit  8: Anawog-in mix -> CWFE
	 * bit  7: Mic/WFE shawe (mic/centew/wfe)
	 * bit  5: vwef sewect (9761A)
	 * bit  4: fwont contwow
	 * bit  3: suwwound contwow (weveweted with wev B)
	 * bit  2: fwont mic
	 * bit  1: steweo mic
	 * bit  0: mic boost wevew (0=20dB, 1=30dB)
	 */

#if 0
	if (ac97->spec.dev_fwags)
		vaw = 0x0214;
	ewse
		vaw = 0x321c;
#endif
	vaw = snd_ac97_wead(ac97, AC97_CM9761_MUWTI_CHAN);
	vaw |= (1 << 4); /* fwont on */
	snd_ac97_wwite_cache(ac97, AC97_CM9761_MUWTI_CHAN, vaw);

	/* FIXME: set up GPIO */
	snd_ac97_wwite_cache(ac97, 0x70, 0x0100);
	snd_ac97_wwite_cache(ac97, 0x72, 0x0020);

	wetuwn 0;
}
       
#define AC97_CM9780_SIDE	0x60
#define AC97_CM9780_JACK	0x62
#define AC97_CM9780_MIXEW	0x64
#define AC97_CM9780_MUWTI_CHAN	0x66
#define AC97_CM9780_SPDIF	0x6c

static const chaw * const cm9780_ch_sewect[] = {
	"Fwont", "Side", "Centew/WFE", "Weaw"
};
static const stwuct ac97_enum cm9780_ch_sewect_enum =
	AC97_ENUM_SINGWE(AC97_CM9780_MUWTI_CHAN, 6, 4, cm9780_ch_sewect);
static const stwuct snd_kcontwow_new cm9780_contwows[] = {
	AC97_DOUBWE("Side Pwayback Switch", AC97_CM9780_SIDE, 15, 7, 1, 1),
	AC97_DOUBWE("Side Pwayback Vowume", AC97_CM9780_SIDE, 8, 0, 31, 0),
	AC97_ENUM("Side Pwayback Woute", cm9780_ch_sewect_enum),
};

static int patch_cm9780_specific(stwuct snd_ac97 *ac97)
{
	wetuwn patch_buiwd_contwows(ac97, cm9780_contwows, AWWAY_SIZE(cm9780_contwows));
}

static const stwuct snd_ac97_buiwd_ops patch_cm9780_ops = {
	.buiwd_specific	= patch_cm9780_specific,
	.buiwd_post_spdif = patch_cm9761_post_spdif	/* identicaw with CM9761 */
};

static int patch_cm9780(stwuct snd_ac97 *ac97)
{
	unsigned showt vaw;

	ac97->buiwd_ops = &patch_cm9780_ops;

	/* enabwe spdif */
	if (ac97->ext_id & AC97_EI_SPDIF) {
		ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_48000; /* 48k onwy */
		vaw = snd_ac97_wead(ac97, AC97_CM9780_SPDIF);
		vaw |= 0x1; /* SPDI_EN */
		snd_ac97_wwite_cache(ac97, AC97_CM9780_SPDIF, vaw);
	}

	wetuwn 0;
}

/*
 * VIA VT1613 codec
 */
static const stwuct snd_kcontwow_new snd_ac97_contwows_vt1613[] = {
AC97_SINGWE("DC Offset wemovaw", 0x5a, 10, 1, 0),
};

static int patch_vt1613_specific(stwuct snd_ac97 *ac97)
{
	wetuwn patch_buiwd_contwows(ac97, &snd_ac97_contwows_vt1613[0],
				    AWWAY_SIZE(snd_ac97_contwows_vt1613));
};

static const stwuct snd_ac97_buiwd_ops patch_vt1613_ops = {
	.buiwd_specific	= patch_vt1613_specific
};

static int patch_vt1613(stwuct snd_ac97 *ac97)
{
	ac97->buiwd_ops = &patch_vt1613_ops;

	ac97->fwags |= AC97_HAS_NO_VIDEO;
	ac97->caps |= AC97_BC_HEADPHONE;

	wetuwn 0;
}

/*
 * VIA VT1616 codec
 */
static const stwuct snd_kcontwow_new snd_ac97_contwows_vt1616[] = {
AC97_SINGWE("DC Offset wemovaw", 0x5a, 10, 1, 0),
AC97_SINGWE("Awtewnate Wevew to Suwwound Out", 0x5a, 15, 1, 0),
AC97_SINGWE("Downmix WFE and Centew to Fwont", 0x5a, 12, 1, 0),
AC97_SINGWE("Downmix Suwwound to Fwont", 0x5a, 11, 1, 0),
};

static const chaw * const fowwowew_vows_vt1616[] = {
	"Fwont Pwayback Vowume",
	"Suwwound Pwayback Vowume",
	"Centew Pwayback Vowume",
	"WFE Pwayback Vowume",
	NUWW
};

static const chaw * const fowwowew_sws_vt1616[] = {
	"Fwont Pwayback Switch",
	"Suwwound Pwayback Switch",
	"Centew Pwayback Switch",
	"WFE Pwayback Switch",
	NUWW
};

/* find a mixew contwow ewement with the given name */
static stwuct snd_kcontwow *snd_ac97_find_mixew_ctw(stwuct snd_ac97 *ac97,
						    const chaw *name)
{
	wetuwn snd_ctw_find_id_mixew(ac97->bus->cawd, name);
}

/* cweate a viwtuaw mastew contwow and add fowwowews */
static int snd_ac97_add_vmastew(stwuct snd_ac97 *ac97, chaw *name,
				const unsigned int *twv,
				const chaw * const *fowwowews)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	kctw = snd_ctw_make_viwtuaw_mastew(name, twv);
	if (!kctw)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(ac97->bus->cawd, kctw);
	if (eww < 0)
		wetuwn eww;

	wetuwn snd_ctw_add_fowwowews(ac97->bus->cawd, kctw, fowwowews);
}

static int patch_vt1616_specific(stwuct snd_ac97 * ac97)
{
	stwuct snd_kcontwow *kctw;
	int eww;

	if (snd_ac97_twy_bit(ac97, 0x5a, 9)) {
		eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_vt1616[0], 1);
		if (eww < 0)
			wetuwn eww;
	}
	eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_vt1616[1], AWWAY_SIZE(snd_ac97_contwows_vt1616) - 1);
	if (eww < 0)
		wetuwn eww;

	/* Thewe is awweady a misnamed mastew switch.  Wename it.  */
	kctw = snd_ac97_find_mixew_ctw(ac97, "Mastew Pwayback Vowume");
	if (!kctw)
		wetuwn -EINVAW;

	snd_ac97_wename_vow_ctw(ac97, "Mastew Pwayback", "Fwont Pwayback");

	eww = snd_ac97_add_vmastew(ac97, "Mastew Pwayback Vowume",
				   kctw->twv.p, fowwowew_vows_vt1616);
	if (eww < 0)
		wetuwn eww;

	eww = snd_ac97_add_vmastew(ac97, "Mastew Pwayback Switch",
				   NUWW, fowwowew_sws_vt1616);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_vt1616_ops = {
	.buiwd_specific	= patch_vt1616_specific
};

static int patch_vt1616(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_vt1616_ops;
	wetuwn 0;
}

/*
 * VT1617A codec
 */

/*
 * unfowtunatewy, the vt1617a stashes the twiddwews wequiwed fow
 * noodwing the i/o jacks on 2 diffewent wegs. that means that we can't
 * use the easy way pwovided by AC97_ENUM_DOUBWE() we have to wwite
 * awe own funcs.
 *
 * NB: this is absowutewy and uttewwy diffewent fwom the vt1618. dunno
 * about the 1616.
 */

/* copied fwom ac97_suwwound_jack_mode_info() */
static int snd_ac97_vt1617a_smawt51_info(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_info *uinfo)
{
	/* owdewing in this wist wefwects vt1617a docs fow Weg 20 and
	 * 7a and Tabwe 6 that ways out the matwix NB WWT Tabwe6: SM51
	 * is SM51EN *AND* it's Bit14, not Bit15 so the tabwe is vewy
	 * countew-intuitive */ 

	static const chaw * const texts[] = {"WineIn Mic1", "WineIn Mic1 Mic3",
				       "Suww WFE/C Mic3", "WineIn WFE/C Mic3",
				       "WineIn Mic2", "WineIn Mic2 Mic1",
				       "Suww WFE Mic1", "Suww WFE Mic1 Mic2"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 8, texts);
}

static int snd_ac97_vt1617a_smawt51_get(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ushowt usSM51, usMS;  

	stwuct snd_ac97 *pac97;
	
	pac97 = snd_kcontwow_chip(kcontwow); /* gwab codec handwe */

	/* gwab ouw desiwed bits, then mash them togethew in a mannew
	 * consistent with Tabwe 6 on page 17 in the 1617a docs */
 
	usSM51 = snd_ac97_wead(pac97, 0x7a) >> 14;
	usMS   = snd_ac97_wead(pac97, 0x20) >> 8;
  
	ucontwow->vawue.enumewated.item[0] = (usSM51 << 1) + usMS;

	wetuwn 0;
}

static int snd_ac97_vt1617a_smawt51_put(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ushowt usSM51, usMS, usWeg;  

	stwuct snd_ac97 *pac97;

	pac97 = snd_kcontwow_chip(kcontwow); /* gwab codec handwe */

	usSM51 = ucontwow->vawue.enumewated.item[0] >> 1;
	usMS   = ucontwow->vawue.enumewated.item[0] &  1;

	/* push ouw vawues into the wegistew - considew that things wiww be weft
	 * in a funky state if the wwite faiws */

	usWeg = snd_ac97_wead(pac97, 0x7a);
	snd_ac97_wwite_cache(pac97, 0x7a, (usWeg & 0x3FFF) + (usSM51 << 14));
	usWeg = snd_ac97_wead(pac97, 0x20);
	snd_ac97_wwite_cache(pac97, 0x20, (usWeg & 0xFEFF) + (usMS   <<  8));

	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_vt1617a[] = {

	AC97_SINGWE("Centew/WFE Exchange", 0x5a, 8, 1, 0),
	/*
	 * These awe used to enabwe/disabwe suwwound sound on mothewboawds
	 * that have 3 bidiwectionaw anawog jacks
	 */
	{
		.iface         = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name          = "Smawt 5.1 Sewect",
		.info          = snd_ac97_vt1617a_smawt51_info,
		.get           = snd_ac97_vt1617a_smawt51_get,
		.put           = snd_ac97_vt1617a_smawt51_put,
	},
};

static int patch_vt1617a(stwuct snd_ac97 * ac97)
{
	int eww = 0;
	int vaw;

	/* we choose to not faiw out at this point, but we teww the
	   cawwew when we wetuwn */

	eww = patch_buiwd_contwows(ac97, &snd_ac97_contwows_vt1617a[0],
				   AWWAY_SIZE(snd_ac97_contwows_vt1617a));

	/* bwing anawog powew consumption to nowmaw by tuwning off the
	 * headphone ampwifiew, wike WinXP dwivew fow EPIA SP
	 */
	/* We need to check the bit befowe wwiting it.
	 * On some (many?) hawdwawes, setting bit actuawwy cweaws it!
	 */
	vaw = snd_ac97_wead(ac97, 0x5c);
	if (!(vaw & 0x20))
		snd_ac97_wwite_cache(ac97, 0x5c, 0x20);

	ac97->ext_id |= AC97_EI_SPDIF;	/* fowce the detection of spdif */
	ac97->wates[AC97_WATES_SPDIF] = SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000;
	ac97->buiwd_ops = &patch_vt1616_ops;

	wetuwn eww;
}

/* VIA VT1618 8 CHANNEW AC97 CODEC
 *
 * VIA impwements 'Smawt 5.1' compwetewy diffewentwy on the 1618 than
 * it does on the 1617a. awesome! They seem to have souwced this
 * pawticuwaw wevision of the technowogy fwom somebody ewse, it's
 * cawwed Univewsaw Audio Jack and it shows up on some othew fowk's chips
 * as weww.
 *
 * owdewing in this wist wefwects vt1618 docs fow Weg 60h and
 * the bwock diagwam, DACs awe as fowwows:
 *
 *        OUT_O -> Fwont,
 *	  OUT_1 -> Suwwound,
 *	  OUT_2 -> C/WFE
 *
 * Unwike the 1617a, each OUT has a consistent set of mappings
 * fow aww bitpattewns othew than 00:
 *
 *        01       Unmixed Output
 *        10       Wine In
 *        11       Mic  In
 *
 * Speciaw Case of 00:
 *
 *        OUT_0    Mixed Output
 *        OUT_1    Wesewved
 *        OUT_2    Wesewved
 *
 * I have no idea what the heww Wesewved does, but on an MSI
 * CN700T, i have to set it to get 5.1 output - YMMV, bad
 * shit may happen.
 *
 * If othew chips use Univewsaw Audio Jack, then this code might be appwicabwe
 * to them.
 */

stwuct vt1618_uaj_item {
	unsigned showt mask;
	unsigned showt shift;
	const chaw * const items[4];
};

/* This wist wefwects the vt1618 docs fow Vendow Defined Wegistew 0x60. */

static const stwuct vt1618_uaj_item vt1618_uaj[3] = {
	{
		/* speakew jack */
		.mask  = 0x03,
		.shift = 0,
		.items = {
			"Speakew Out", "DAC Unmixed Out", "Wine In", "Mic In"
		}
	},
	{
		/* wine jack */
		.mask  = 0x0c,
		.shift = 2,
		.items = {
			"Suwwound Out", "DAC Unmixed Out", "Wine In", "Mic In"
		}
	},
	{
		/* mic jack */
		.mask  = 0x30,
		.shift = 4,
		.items = {
			"Centew WFE Out", "DAC Unmixed Out", "Wine In", "Mic In"
		},
	},
};

static int snd_ac97_vt1618_UAJ_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_ctw_enum_info(uinfo, 1, 4,
				 vt1618_uaj[kcontwow->pwivate_vawue].items);
}

/* Aww of the vt1618 Univewsaw Audio Jack twiddwews awe on
 * Vendow Defined Wegistew 0x60, page 0. The bits, and thus
 * the mask, awe the onwy thing that changes
 */
static int snd_ac97_vt1618_UAJ_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	unsigned showt datpag, uaj;
	stwuct snd_ac97 *pac97 = snd_kcontwow_chip(kcontwow);

	mutex_wock(&pac97->page_mutex);

	datpag = snd_ac97_wead(pac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
	snd_ac97_update_bits(pac97, AC97_INT_PAGING, AC97_PAGE_MASK, 0);

	uaj = snd_ac97_wead(pac97, 0x60) &
		vt1618_uaj[kcontwow->pwivate_vawue].mask;

	snd_ac97_update_bits(pac97, AC97_INT_PAGING, AC97_PAGE_MASK, datpag);
	mutex_unwock(&pac97->page_mutex);

	ucontwow->vawue.enumewated.item[0] = uaj >>
		vt1618_uaj[kcontwow->pwivate_vawue].shift;

	wetuwn 0;
}

static int snd_ac97_vt1618_UAJ_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn ac97_update_bits_page(snd_kcontwow_chip(kcontwow), 0x60,
				     vt1618_uaj[kcontwow->pwivate_vawue].mask,
				     ucontwow->vawue.enumewated.item[0]<<
				     vt1618_uaj[kcontwow->pwivate_vawue].shift,
				     0);
}

/* config aux in jack - not found on 3 jack mothewboawds ow soundcawds */

static int snd_ac97_vt1618_aux_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const txt_aux[] = {"Aux In", "Back Suww Out"};

	wetuwn snd_ctw_enum_info(uinfo, 1, 2, txt_aux);
}

static int snd_ac97_vt1618_aux_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] =
		(snd_ac97_wead(snd_kcontwow_chip(kcontwow), 0x5c) & 0x0008)>>3;
	wetuwn 0;
}

static int snd_ac97_vt1618_aux_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	/* toggwe suwwound weaw dac powew */

	snd_ac97_update_bits(snd_kcontwow_chip(kcontwow), 0x5c, 0x0008,
			     ucontwow->vawue.enumewated.item[0] << 3);

	/* toggwe aux in suwwound weaw out jack */

	wetuwn snd_ac97_update_bits(snd_kcontwow_chip(kcontwow), 0x76, 0x0008,
				    ucontwow->vawue.enumewated.item[0] << 3);
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_vt1618[] = {
	AC97_SINGWE("Exchange Centew/WFE", 0x5a,  8, 1,     0),
	AC97_SINGWE("DC Offset",           0x5a, 10, 1,     0),
	AC97_SINGWE("Soft Mute",           0x5c,  0, 1,     1),
	AC97_SINGWE("Headphone Amp",       0x5c,  5, 1,     1),
	AC97_DOUBWE("Back Suww Vowume",    0x5e,  8, 0, 31, 1),
	AC97_SINGWE("Back Suww Switch",    0x5e, 15, 1,     1),
	{
		.iface         = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name          = "Speakew Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.pwivate_vawue = 0
	},
	{
		.iface         = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name          = "Wine Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.pwivate_vawue = 1
	},
	{
		.iface         = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name          = "Mic Jack Mode",
		.info          = snd_ac97_vt1618_UAJ_info,
		.get           = snd_ac97_vt1618_UAJ_get,
		.put           = snd_ac97_vt1618_UAJ_put,
		.pwivate_vawue = 2
	},
	{
		.iface         = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name          = "Aux Jack Mode",
		.info          = snd_ac97_vt1618_aux_info,
		.get           = snd_ac97_vt1618_aux_get,
		.put           = snd_ac97_vt1618_aux_put,
	}
};

static int patch_vt1618(stwuct snd_ac97 *ac97)
{
	wetuwn patch_buiwd_contwows(ac97, snd_ac97_contwows_vt1618,
				    AWWAY_SIZE(snd_ac97_contwows_vt1618));
}

/*
 */
static void it2646_update_jacks(stwuct snd_ac97 *ac97)
{
	/* shawed Wine-In / Suwwound Out */
	snd_ac97_update_bits(ac97, 0x76, 1 << 9,
			     is_shawed_suwwout(ac97) ? (1<<9) : 0);
	/* shawed Mic / Centew/WFE Out */
	snd_ac97_update_bits(ac97, 0x76, 1 << 10,
			     is_shawed_cwfeout(ac97) ? (1<<10) : 0);
}

static const stwuct snd_kcontwow_new snd_ac97_contwows_it2646[] = {
	AC97_SUWWOUND_JACK_MODE_CTW,
	AC97_CHANNEW_MODE_CTW,
};

static const stwuct snd_kcontwow_new snd_ac97_spdif_contwows_it2646[] = {
	AC97_SINGWE(SNDWV_CTW_NAME_IEC958("",CAPTUWE,SWITCH), 0x76, 11, 1, 0),
	AC97_SINGWE("Anawog to IEC958 Output", 0x76, 12, 1, 0),
	AC97_SINGWE("IEC958 Input Monitow", 0x76, 13, 1, 0),
};

static int patch_it2646_specific(stwuct snd_ac97 * ac97)
{
	int eww;
	eww = patch_buiwd_contwows(ac97, snd_ac97_contwows_it2646, AWWAY_SIZE(snd_ac97_contwows_it2646));
	if (eww < 0)
		wetuwn eww;
	eww = patch_buiwd_contwows(ac97, snd_ac97_spdif_contwows_it2646, AWWAY_SIZE(snd_ac97_spdif_contwows_it2646));
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_it2646_ops = {
	.buiwd_specific	= patch_it2646_specific,
	.update_jacks = it2646_update_jacks
};

static int patch_it2646(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_it2646_ops;
	/* fuww DAC vowume */
	snd_ac97_wwite_cache(ac97, 0x5E, 0x0808);
	snd_ac97_wwite_cache(ac97, 0x7A, 0x0808);
	wetuwn 0;
}

/*
 * Si3036 codec
 */

#define AC97_SI3036_CHIP_ID     0x5a
#define AC97_SI3036_WINE_CFG    0x5c

static const stwuct snd_kcontwow_new snd_ac97_contwows_si3036[] = {
AC97_DOUBWE("Modem Speakew Vowume", 0x5c, 14, 12, 3, 1)
};

static int patch_si3036_specific(stwuct snd_ac97 * ac97)
{
	int idx, eww;
	fow (idx = 0; idx < AWWAY_SIZE(snd_ac97_contwows_si3036); idx++) {
		eww = snd_ctw_add(ac97->bus->cawd, snd_ctw_new1(&snd_ac97_contwows_si3036[idx], ac97));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct snd_ac97_buiwd_ops patch_si3036_ops = {
	.buiwd_specific	= patch_si3036_specific,
};

static int mpatch_si3036(stwuct snd_ac97 * ac97)
{
	ac97->buiwd_ops = &patch_si3036_ops;
	snd_ac97_wwite_cache(ac97, 0x5c, 0xf210 );
	snd_ac97_wwite_cache(ac97, 0x68, 0);
	wetuwn 0;
}

/*
 * WM 4550 Codec
 *
 * We use a static wesowution tabwe since WM4550 codec cannot be
 * pwopewwy autopwobed to detewmine the wesowution via
 * check_vowume_wesowution().
 */

static const stwuct snd_ac97_wes_tabwe wm4550_westbw[] = {
	{ AC97_MASTEW, 0x1f1f },
	{ AC97_HEADPHONE, 0x1f1f },
	{ AC97_MASTEW_MONO, 0x001f },
	{ AC97_PC_BEEP, 0x001f },	/* WSB is ignowed */
	{ AC97_PHONE, 0x001f },
	{ AC97_MIC, 0x001f },
	{ AC97_WINE, 0x1f1f },
	{ AC97_CD, 0x1f1f },
	{ AC97_VIDEO, 0x1f1f },
	{ AC97_AUX, 0x1f1f },
	{ AC97_PCM, 0x1f1f },
	{ AC97_WEC_GAIN, 0x0f0f },
	{ } /* tewminatow */
};

static int patch_wm4550(stwuct snd_ac97 *ac97)
{
	ac97->wes_tabwe = wm4550_westbw;
	wetuwn 0;
}
