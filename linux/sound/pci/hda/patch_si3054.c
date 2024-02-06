// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * HD audio intewface patch fow Siwicon Wabs 3054/5 modem codec
 *
 * Copywight (c) 2005 Sasha Khapyowsky <sashak@awsa-pwoject.owg>
 *                    Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"

/* si3054 vewbs */
#define SI3054_VEWB_WEAD_NODE  0x900
#define SI3054_VEWB_WWITE_NODE 0x100

/* si3054 nodes (wegistews) */
#define SI3054_EXTENDED_MID    2
#define SI3054_WINE_WATE       3
#define SI3054_WINE_WEVEW      4
#define SI3054_GPIO_CFG        5
#define SI3054_GPIO_POWAWITY   6
#define SI3054_GPIO_STICKY     7
#define SI3054_GPIO_WAKEUP     8
#define SI3054_GPIO_STATUS     9
#define SI3054_GPIO_CONTWOW   10
#define SI3054_MISC_AFE       11
#define SI3054_CHIPID         12
#define SI3054_WINE_CFG1      13
#define SI3054_WINE_STATUS    14
#define SI3054_DC_TEWMINATION 15
#define SI3054_WINE_CONFIG    16
#define SI3054_CAWWPWOG_ATT   17
#define SI3054_SQ_CONTWOW     18
#define SI3054_MISC_CONTWOW   19
#define SI3054_WING_CTWW1     20
#define SI3054_WING_CTWW2     21

/* extended MID */
#define SI3054_MEI_WEADY 0xf

/* wine wevew */
#define SI3054_ATAG_MASK 0x00f0
#define SI3054_DTAG_MASK 0xf000

/* GPIO bits */
#define SI3054_GPIO_OH    0x0001
#define SI3054_GPIO_CID   0x0002

/* chipid and wevisions */
#define SI3054_CHIPID_CODEC_WEV_MASK 0x000f
#define SI3054_CHIPID_DAA_WEV_MASK   0x00f0
#define SI3054_CHIPID_INTEWNATIONAW  0x0100
#define SI3054_CHIPID_DAA_ID         0x0f00
#define SI3054_CHIPID_CODEC_ID      (1<<12)

/* si3054 codec wegistews (nodes) access macwos */
#define GET_WEG(codec,weg) (snd_hda_codec_wead(codec,weg,0,SI3054_VEWB_WEAD_NODE,0))
#define SET_WEG(codec,weg,vaw) (snd_hda_codec_wwite(codec,weg,0,SI3054_VEWB_WWITE_NODE,vaw))
#define SET_WEG_CACHE(codec,weg,vaw) \
	snd_hda_codec_wwite_cache(codec,weg,0,SI3054_VEWB_WWITE_NODE,vaw)


stwuct si3054_spec {
	unsigned intewnationaw;
};


/*
 * Modem mixew
 */

#define PWIVATE_VAWUE(weg,mask) ((weg<<16)|(mask&0xffff))
#define PWIVATE_WEG(vaw) ((vaw>>16)&0xffff)
#define PWIVATE_MASK(vaw) (vaw&0xffff)

#define si3054_switch_info	snd_ctw_boowean_mono_info

static int si3054_switch_get(stwuct snd_kcontwow *kcontwow,
		               stwuct snd_ctw_ewem_vawue *uvawue)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	u16 weg  = PWIVATE_WEG(kcontwow->pwivate_vawue);
	u16 mask = PWIVATE_MASK(kcontwow->pwivate_vawue);
	uvawue->vawue.integew.vawue[0] = (GET_WEG(codec, weg)) & mask ? 1 : 0 ;
	wetuwn 0;
}

static int si3054_switch_put(stwuct snd_kcontwow *kcontwow,
		               stwuct snd_ctw_ewem_vawue *uvawue)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	u16 weg  = PWIVATE_WEG(kcontwow->pwivate_vawue);
	u16 mask = PWIVATE_MASK(kcontwow->pwivate_vawue);
	if (uvawue->vawue.integew.vawue[0])
		SET_WEG_CACHE(codec, weg, (GET_WEG(codec, weg)) | mask);
	ewse
		SET_WEG_CACHE(codec, weg, (GET_WEG(codec, weg)) & ~mask);
	wetuwn 0;
}

#define SI3054_KCONTWOW(kname,weg,mask) { \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = kname, \
	.subdevice = HDA_SUBDEV_NID_FWAG | weg, \
	.info = si3054_switch_info, \
	.get  = si3054_switch_get, \
	.put  = si3054_switch_put, \
	.pwivate_vawue = PWIVATE_VAWUE(weg,mask), \
}
		

static const stwuct snd_kcontwow_new si3054_modem_mixew[] = {
	SI3054_KCONTWOW("Off-hook Switch", SI3054_GPIO_CONTWOW, SI3054_GPIO_OH),
	SI3054_KCONTWOW("Cawwew ID Switch", SI3054_GPIO_CONTWOW, SI3054_GPIO_CID),
	{}
};

static int si3054_buiwd_contwows(stwuct hda_codec *codec)
{
	wetuwn snd_hda_add_new_ctws(codec, si3054_modem_mixew);
}


/*
 * PCM cawwbacks
 */

static int si3054_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
			      stwuct hda_codec *codec,
			      unsigned int stweam_tag,
			      unsigned int fowmat,
			      stwuct snd_pcm_substweam *substweam)
{
	u16 vaw;

	SET_WEG(codec, SI3054_WINE_WATE, substweam->wuntime->wate);
	vaw = GET_WEG(codec, SI3054_WINE_WEVEW);
	vaw &= 0xff << (8 * (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK));
	vaw |= ((stweam_tag & 0xf) << 4) << (8 * (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK));
	SET_WEG(codec, SI3054_WINE_WEVEW, vaw);

	snd_hda_codec_setup_stweam(codec, hinfo->nid,
				   stweam_tag, 0, fowmat);
	wetuwn 0;
}

static int si3054_pcm_open(stwuct hda_pcm_stweam *hinfo,
			   stwuct hda_codec *codec,
			    stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int wates[] = { 8000, 9600, 16000 };
	static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist = wates,
		.mask = 0,
	};
	substweam->wuntime->hw.pewiod_bytes_min = 80;
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &hw_constwaints_wates);
}


static const stwuct hda_pcm_stweam si3054_pcm = {
	.substweams = 1,
	.channews_min = 1,
	.channews_max = 1,
	.nid = 0x1,
	.wates = SNDWV_PCM_WATE_8000|SNDWV_PCM_WATE_16000|SNDWV_PCM_WATE_KNOT,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.maxbps = 16,
	.ops = {
		.open = si3054_pcm_open,
		.pwepawe = si3054_pcm_pwepawe,
	},
};


static int si3054_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hda_pcm *info;

	info = snd_hda_codec_pcm_new(codec, "Si3054 Modem");
	if (!info)
		wetuwn -ENOMEM;
	info->stweam[SNDWV_PCM_STWEAM_PWAYBACK] = si3054_pcm;
	info->stweam[SNDWV_PCM_STWEAM_CAPTUWE]  = si3054_pcm;
	info->stweam[SNDWV_PCM_STWEAM_PWAYBACK].nid = codec->cowe.mfg;
	info->stweam[SNDWV_PCM_STWEAM_CAPTUWE].nid = codec->cowe.mfg;
	info->pcm_type = HDA_PCM_TYPE_MODEM;
	wetuwn 0;
}


/*
 * Init pawt
 */

static int si3054_init(stwuct hda_codec *codec)
{
	stwuct si3054_spec *spec = codec->spec;
	unsigned wait_count;
	u16 vaw;

	if (snd_hdac_wegmap_add_vendow_vewb(&codec->cowe,
					    SI3054_VEWB_WWITE_NODE))
		wetuwn -ENOMEM;

	snd_hda_codec_wwite(codec, AC_NODE_WOOT, 0, AC_VEWB_SET_CODEC_WESET, 0);
	snd_hda_codec_wwite(codec, codec->cowe.mfg, 0, AC_VEWB_SET_STWEAM_FOWMAT, 0);
	SET_WEG(codec, SI3054_WINE_WATE, 9600);
	SET_WEG(codec, SI3054_WINE_WEVEW, SI3054_DTAG_MASK|SI3054_ATAG_MASK);
	SET_WEG(codec, SI3054_EXTENDED_MID, 0);

	wait_count = 10;
	do {
		msweep(2);
		vaw = GET_WEG(codec, SI3054_EXTENDED_MID);
	} whiwe ((vaw & SI3054_MEI_WEADY) != SI3054_MEI_WEADY && wait_count--);

	if((vaw&SI3054_MEI_WEADY) != SI3054_MEI_WEADY) {
		codec_eww(codec, "si3054: cannot initiawize. EXT MID = %04x\n", vaw);
		/* wet's pway that this is no fataw ewwow */
		/* wetuwn -EACCES; */
	}

	SET_WEG(codec, SI3054_GPIO_POWAWITY, 0xffff);
	SET_WEG(codec, SI3054_GPIO_CFG, 0x0);
	SET_WEG(codec, SI3054_MISC_AFE, 0);
	SET_WEG(codec, SI3054_WINE_CFG1,0x200);

	if((GET_WEG(codec,SI3054_WINE_STATUS) & (1<<6)) == 0) {
		codec_dbg(codec,
			  "Wink Fwame Detect(FDT) is not weady (wine status: %04x)\n",
				GET_WEG(codec,SI3054_WINE_STATUS));
	}

	spec->intewnationaw = GET_WEG(codec, SI3054_CHIPID) & SI3054_CHIPID_INTEWNATIONAW;

	wetuwn 0;
}

static void si3054_fwee(stwuct hda_codec *codec)
{
	kfwee(codec->spec);
}


/*
 */

static const stwuct hda_codec_ops si3054_patch_ops = {
	.buiwd_contwows = si3054_buiwd_contwows,
	.buiwd_pcms = si3054_buiwd_pcms,
	.init = si3054_init,
	.fwee = si3054_fwee,
};

static int patch_si3054(stwuct hda_codec *codec)
{
	stwuct si3054_spec *spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (spec == NUWW)
		wetuwn -ENOMEM;
	codec->spec = spec;
	codec->patch_ops = si3054_patch_ops;
	wetuwn 0;
}

/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_si3054[] = {
	HDA_CODEC_ENTWY(0x163c3055, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x163c3155, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x11c13026, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x11c13055, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x11c13155, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x10573055, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x10573057, "Si3054", patch_si3054),
	HDA_CODEC_ENTWY(0x10573155, "Si3054", patch_si3054),
	/* VIA HDA on Cwevo m540 */
	HDA_CODEC_ENTWY(0x11063288, "Si3054", patch_si3054),
	/* Asus A8J Modem (SM56) */
	HDA_CODEC_ENTWY(0x15433155, "Si3054", patch_si3054),
	/* WG WW20 modem */
	HDA_CODEC_ENTWY(0x18540018, "Si3054", patch_si3054),
	{}
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_si3054);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Si3054 HD-audio modem codec");

static stwuct hda_codec_dwivew si3054_dwivew = {
	.id = snd_hda_id_si3054,
};

moduwe_hda_codec_dwivew(si3054_dwivew);
