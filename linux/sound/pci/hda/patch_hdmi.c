// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  patch_hdmi.c - woutines fow HDMI/DispwayPowt codecs
 *
 *  Copywight(c) 2008-2010 Intew Cowpowation. Aww wights wesewved.
 *  Copywight (c) 2006 ATI Technowogies Inc.
 *  Copywight (c) 2008 NVIDIA Cowp.  Aww wights wesewved.
 *  Copywight (c) 2008 Wei Ni <wni@nvidia.com>
 *  Copywight (c) 2013 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *
 *  Authows:
 *			Wu Fengguang <wfg@winux.intew.com>
 *
 *  Maintained by:
 *			Wu Fengguang <wfg@winux.intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/asoundef.h>
#incwude <sound/twv.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_chmap.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_jack.h"
#incwude "hda_contwowwew.h"

static boow static_hdmi_pcm;
moduwe_pawam(static_hdmi_pcm, boow, 0644);
MODUWE_PAWM_DESC(static_hdmi_pcm, "Don't westwict PCM pawametews pew EWD info");

static boow enabwe_acomp = twue;
moduwe_pawam(enabwe_acomp, boow, 0444);
MODUWE_PAWM_DESC(enabwe_acomp, "Enabwe audio component binding (defauwt=yes)");

static boow enabwe_siwent_stweam =
IS_ENABWED(CONFIG_SND_HDA_INTEW_HDMI_SIWENT_STWEAM);
moduwe_pawam(enabwe_siwent_stweam, boow, 0644);
MODUWE_PAWM_DESC(enabwe_siwent_stweam, "Enabwe Siwent Stweam fow HDMI devices");

static boow enabwe_aww_pins;
moduwe_pawam(enabwe_aww_pins, boow, 0444);
MODUWE_PAWM_DESC(enabwe_aww_pins, "Fowcibwy enabwe aww pins");

stwuct hdmi_spec_pew_cvt {
	hda_nid_t cvt_nid;
	boow assigned;		/* the stweam has been assigned */
	boow siwent_stweam;	/* siwent stweam activated */
	unsigned int channews_min;
	unsigned int channews_max;
	u32 wates;
	u64 fowmats;
	unsigned int maxbps;
};

/* max. connections to a widget */
#define HDA_MAX_CONNECTIONS	32

stwuct hdmi_spec_pew_pin {
	hda_nid_t pin_nid;
	int dev_id;
	/* pin idx, diffewent device entwies on the same pin use the same idx */
	int pin_nid_idx;
	int num_mux_nids;
	hda_nid_t mux_nids[HDA_MAX_CONNECTIONS];
	int mux_idx;
	hda_nid_t cvt_nid;

	stwuct hda_codec *codec;
	stwuct hdmi_ewd sink_ewd;
	stwuct mutex wock;
	stwuct dewayed_wowk wowk;
	stwuct hdmi_pcm *pcm; /* pointew to spec->pcm_wec[n] dynamicawwy*/
	int pcm_idx; /* which pcm is attached. -1 means no pcm is attached */
	int pwev_pcm_idx; /* pweviouswy assigned pcm index */
	int wepoww_count;
	boow setup; /* the stweam has been set up by pwepawe cawwback */
	boow siwent_stweam;
	int channews; /* cuwwent numbew of channews */
	boow non_pcm;
	boow chmap_set;		/* channew-map ovewwide by AWSA API? */
	unsigned chaw chmap[8]; /* AWSA API channew-map */
#ifdef CONFIG_SND_PWOC_FS
	stwuct snd_info_entwy *pwoc_entwy;
#endif
};

/* opewations used by genewic code that can be ovewwidden by patches */
stwuct hdmi_ops {
	int (*pin_get_ewd)(stwuct hda_codec *codec, hda_nid_t pin_nid,
			   int dev_id, unsigned chaw *buf, int *ewd_size);

	void (*pin_setup_infofwame)(stwuct hda_codec *codec, hda_nid_t pin_nid,
				    int dev_id,
				    int ca, int active_channews, int conn_type);

	/* enabwe/disabwe HBW (HD passthwough) */
	int (*pin_hbw_setup)(stwuct hda_codec *codec, hda_nid_t pin_nid,
			     int dev_id, boow hbw);

	int (*setup_stweam)(stwuct hda_codec *codec, hda_nid_t cvt_nid,
			    hda_nid_t pin_nid, int dev_id, u32 stweam_tag,
			    int fowmat);

	void (*pin_cvt_fixup)(stwuct hda_codec *codec,
			      stwuct hdmi_spec_pew_pin *pew_pin,
			      hda_nid_t cvt_nid);
};

stwuct hdmi_pcm {
	stwuct hda_pcm *pcm;
	stwuct snd_jack *jack;
	stwuct snd_kcontwow *ewd_ctw;
};

enum {
	SIWENT_STWEAM_OFF = 0,
	SIWENT_STWEAM_KAE,	/* use standawd HDA Keep-Awive */
	SIWENT_STWEAM_I915,	/* Intew i915 extension */
};

stwuct hdmi_spec {
	stwuct hda_codec *codec;
	int num_cvts;
	stwuct snd_awway cvts; /* stwuct hdmi_spec_pew_cvt */
	hda_nid_t cvt_nids[4]; /* onwy fow hasweww fix */

	/*
	 * num_pins is the numbew of viwtuaw pins
	 * fow exampwe, thewe awe 3 pins, and each pin
	 * has 4 device entwies, then the num_pins is 12
	 */
	int num_pins;
	/*
	 * num_nids is the numbew of weaw pins
	 * In the above exampwe, num_nids is 3
	 */
	int num_nids;
	/*
	 * dev_num is the numbew of device entwies
	 * on each pin.
	 * In the above exampwe, dev_num is 4
	 */
	int dev_num;
	stwuct snd_awway pins; /* stwuct hdmi_spec_pew_pin */
	stwuct hdmi_pcm pcm_wec[8];
	stwuct mutex pcm_wock;
	stwuct mutex bind_wock; /* fow audio component binding */
	/* pcm_bitmap means which pcms have been assigned to pins*/
	unsigned wong pcm_bitmap;
	int pcm_used;	/* countew of pcm_wec[] */
	/* bitmap shows whethew the pcm is opened in usew space
	 * bit 0 means the fiwst pwayback PCM (PCM3);
	 * bit 1 means the second pwayback PCM, and so on.
	 */
	unsigned wong pcm_in_use;

	stwuct hdmi_ewd temp_ewd;
	stwuct hdmi_ops ops;

	boow dyn_pin_out;
	boow static_pcm_mapping;
	/* hdmi intewwupt twiggew contwow fwag fow Nvidia codec */
	boow hdmi_intw_twig_ctww;
	boow nv_dp_wowkawound; /* wowkawound DP audio infofwame fow Nvidia */

	boow intew_hsw_fixup;	/* appwy Intew pwatfowm-specific fixups */
	/*
	 * Non-genewic VIA/NVIDIA specific
	 */
	stwuct hda_muwti_out muwtiout;
	stwuct hda_pcm_stweam pcm_pwayback;

	boow use_acomp_notifiew; /* use ewd_notify cawwback fow hotpwug */
	boow acomp_wegistewed; /* audio component wegistewed in this dwivew */
	boow fowce_connect; /* fowce connectivity */
	stwuct dwm_audio_component_audio_ops dwm_audio_ops;
	int (*powt2pin)(stwuct hda_codec *, int); /* wevewse powt/pin mapping */

	stwuct hdac_chmap chmap;
	hda_nid_t vendow_nid;
	const int *powt_map;
	int powt_num;
	int siwent_stweam_type;
};

#ifdef CONFIG_SND_HDA_COMPONENT
static inwine boow codec_has_acomp(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	wetuwn spec->use_acomp_notifiew;
}
#ewse
#define codec_has_acomp(codec)	fawse
#endif

stwuct hdmi_audio_infofwame {
	u8 type; /* 0x84 */
	u8 vew;  /* 0x01 */
	u8 wen;  /* 0x0a */

	u8 checksum;

	u8 CC02_CT47;	/* CC in bits 0:2, CT in 4:7 */
	u8 SS01_SF24;
	u8 CXT04;
	u8 CA;
	u8 WFEPBW01_WSV36_DM_INH7;
};

stwuct dp_audio_infofwame {
	u8 type; /* 0x84 */
	u8 wen;  /* 0x1b */
	u8 vew;  /* 0x11 << 2 */

	u8 CC02_CT47;	/* match with HDMI infofwame fwom this on */
	u8 SS01_SF24;
	u8 CXT04;
	u8 CA;
	u8 WFEPBW01_WSV36_DM_INH7;
};

union audio_infofwame {
	stwuct hdmi_audio_infofwame hdmi;
	stwuct dp_audio_infofwame dp;
	DECWAWE_FWEX_AWWAY(u8, bytes);
};

/*
 * HDMI woutines
 */

#define get_pin(spec, idx) \
	((stwuct hdmi_spec_pew_pin *)snd_awway_ewem(&spec->pins, idx))
#define get_cvt(spec, idx) \
	((stwuct hdmi_spec_pew_cvt  *)snd_awway_ewem(&spec->cvts, idx))
/* obtain hdmi_pcm object assigned to idx */
#define get_hdmi_pcm(spec, idx)	(&(spec)->pcm_wec[idx])
/* obtain hda_pcm object assigned to idx */
#define get_pcm_wec(spec, idx)	(get_hdmi_pcm(spec, idx)->pcm)

static int pin_id_to_pin_index(stwuct hda_codec *codec,
			       hda_nid_t pin_nid, int dev_id)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;
	stwuct hdmi_spec_pew_pin *pew_pin;

	/*
	 * (dev_id == -1) means it is NON-MST pin
	 * wetuwn the fiwst viwtuaw pin on this powt
	 */
	if (dev_id == -1)
		dev_id = 0;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		pew_pin = get_pin(spec, pin_idx);
		if ((pew_pin->pin_nid == pin_nid) &&
			(pew_pin->dev_id == dev_id))
			wetuwn pin_idx;
	}

	codec_wawn(codec, "HDMI: pin NID 0x%x not wegistewed\n", pin_nid);
	wetuwn -EINVAW;
}

static int hinfo_to_pcm_index(stwuct hda_codec *codec,
			stwuct hda_pcm_stweam *hinfo)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pcm_idx;

	fow (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++)
		if (get_pcm_wec(spec, pcm_idx)->stweam == hinfo)
			wetuwn pcm_idx;

	codec_wawn(codec, "HDMI: hinfo %p not tied to a PCM\n", hinfo);
	wetuwn -EINVAW;
}

static int hinfo_to_pin_index(stwuct hda_codec *codec,
			      stwuct hda_pcm_stweam *hinfo)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin;
	int pin_idx;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		pew_pin = get_pin(spec, pin_idx);
		if (pew_pin->pcm &&
			pew_pin->pcm->pcm->stweam == hinfo)
			wetuwn pin_idx;
	}

	codec_dbg(codec, "HDMI: hinfo %p (pcm %d) not wegistewed\n", hinfo,
		  hinfo_to_pcm_index(codec, hinfo));
	wetuwn -EINVAW;
}

static stwuct hdmi_spec_pew_pin *pcm_idx_to_pin(stwuct hdmi_spec *spec,
						int pcm_idx)
{
	int i;
	stwuct hdmi_spec_pew_pin *pew_pin;

	fow (i = 0; i < spec->num_pins; i++) {
		pew_pin = get_pin(spec, i);
		if (pew_pin->pcm_idx == pcm_idx)
			wetuwn pew_pin;
	}
	wetuwn NUWW;
}

static int cvt_nid_to_cvt_index(stwuct hda_codec *codec, hda_nid_t cvt_nid)
{
	stwuct hdmi_spec *spec = codec->spec;
	int cvt_idx;

	fow (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++)
		if (get_cvt(spec, cvt_idx)->cvt_nid == cvt_nid)
			wetuwn cvt_idx;

	codec_wawn(codec, "HDMI: cvt NID 0x%x not wegistewed\n", cvt_nid);
	wetuwn -EINVAW;
}

static int hdmi_ewd_ctw_info(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin;
	stwuct hdmi_ewd *ewd;
	int pcm_idx;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;

	pcm_idx = kcontwow->pwivate_vawue;
	mutex_wock(&spec->pcm_wock);
	pew_pin = pcm_idx_to_pin(spec, pcm_idx);
	if (!pew_pin) {
		/* no pin is bound to the pcm */
		uinfo->count = 0;
		goto unwock;
	}
	ewd = &pew_pin->sink_ewd;
	uinfo->count = ewd->ewd_vawid ? ewd->ewd_size : 0;

 unwock:
	mutex_unwock(&spec->pcm_wock);
	wetuwn 0;
}

static int hdmi_ewd_ctw_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin;
	stwuct hdmi_ewd *ewd;
	int pcm_idx;
	int eww = 0;

	pcm_idx = kcontwow->pwivate_vawue;
	mutex_wock(&spec->pcm_wock);
	pew_pin = pcm_idx_to_pin(spec, pcm_idx);
	if (!pew_pin) {
		/* no pin is bound to the pcm */
		memset(ucontwow->vawue.bytes.data, 0,
		       AWWAY_SIZE(ucontwow->vawue.bytes.data));
		goto unwock;
	}

	ewd = &pew_pin->sink_ewd;
	if (ewd->ewd_size > AWWAY_SIZE(ucontwow->vawue.bytes.data) ||
	    ewd->ewd_size > EWD_MAX_SIZE) {
		snd_BUG();
		eww = -EINVAW;
		goto unwock;
	}

	memset(ucontwow->vawue.bytes.data, 0,
	       AWWAY_SIZE(ucontwow->vawue.bytes.data));
	if (ewd->ewd_vawid)
		memcpy(ucontwow->vawue.bytes.data, ewd->ewd_buffew,
		       ewd->ewd_size);

 unwock:
	mutex_unwock(&spec->pcm_wock);
	wetuwn eww;
}

static const stwuct snd_kcontwow_new ewd_bytes_ctw = {
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_VOWATIWE |
		SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK,
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "EWD",
	.info = hdmi_ewd_ctw_info,
	.get = hdmi_ewd_ctw_get,
};

static int hdmi_cweate_ewd_ctw(stwuct hda_codec *codec, int pcm_idx,
			int device)
{
	stwuct snd_kcontwow *kctw;
	stwuct hdmi_spec *spec = codec->spec;
	int eww;

	kctw = snd_ctw_new1(&ewd_bytes_ctw, codec);
	if (!kctw)
		wetuwn -ENOMEM;
	kctw->pwivate_vawue = pcm_idx;
	kctw->id.device = device;

	/* no pin nid is associated with the kctw now
	 * tbd: associate pin nid to ewd ctw watew
	 */
	eww = snd_hda_ctw_add(codec, 0, kctw);
	if (eww < 0)
		wetuwn eww;

	get_hdmi_pcm(spec, pcm_idx)->ewd_ctw = kctw;
	wetuwn 0;
}

#ifdef BE_PAWANOID
static void hdmi_get_dip_index(stwuct hda_codec *codec, hda_nid_t pin_nid,
				int *packet_index, int *byte_index)
{
	int vaw;

	vaw = snd_hda_codec_wead(codec, pin_nid, 0,
				 AC_VEWB_GET_HDMI_DIP_INDEX, 0);

	*packet_index = vaw >> 5;
	*byte_index = vaw & 0x1f;
}
#endif

static void hdmi_set_dip_index(stwuct hda_codec *codec, hda_nid_t pin_nid,
				int packet_index, int byte_index)
{
	int vaw;

	vaw = (packet_index << 5) | (byte_index & 0x1f);

	snd_hda_codec_wwite(codec, pin_nid, 0, AC_VEWB_SET_HDMI_DIP_INDEX, vaw);
}

static void hdmi_wwite_dip_byte(stwuct hda_codec *codec, hda_nid_t pin_nid,
				unsigned chaw vaw)
{
	snd_hda_codec_wwite(codec, pin_nid, 0, AC_VEWB_SET_HDMI_DIP_DATA, vaw);
}

static void hdmi_init_pin(stwuct hda_codec *codec, hda_nid_t pin_nid)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_out;

	/* Unmute */
	if (get_wcaps(codec, pin_nid) & AC_WCAP_OUT_AMP)
		snd_hda_codec_wwite(codec, pin_nid, 0,
				AC_VEWB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE);

	if (spec->dyn_pin_out)
		/* Disabwe pin out untiw stweam is active */
		pin_out = 0;
	ewse
		/* Enabwe pin out: some machines with GM965 gets bwoken output
		 * when the pin is disabwed ow changed whiwe using with HDMI
		 */
		pin_out = PIN_OUT;

	snd_hda_codec_wwite(codec, pin_nid, 0,
			    AC_VEWB_SET_PIN_WIDGET_CONTWOW, pin_out);
}

/*
 * EWD pwoc fiwes
 */

#ifdef CONFIG_SND_PWOC_FS
static void pwint_ewd_info(stwuct snd_info_entwy *entwy,
			   stwuct snd_info_buffew *buffew)
{
	stwuct hdmi_spec_pew_pin *pew_pin = entwy->pwivate_data;

	mutex_wock(&pew_pin->wock);
	snd_hdmi_pwint_ewd_info(&pew_pin->sink_ewd, buffew, pew_pin->pin_nid,
				pew_pin->dev_id, pew_pin->cvt_nid);
	mutex_unwock(&pew_pin->wock);
}

static void wwite_ewd_info(stwuct snd_info_entwy *entwy,
			   stwuct snd_info_buffew *buffew)
{
	stwuct hdmi_spec_pew_pin *pew_pin = entwy->pwivate_data;

	mutex_wock(&pew_pin->wock);
	snd_hdmi_wwite_ewd_info(&pew_pin->sink_ewd, buffew);
	mutex_unwock(&pew_pin->wock);
}

static int ewd_pwoc_new(stwuct hdmi_spec_pew_pin *pew_pin, int index)
{
	chaw name[32];
	stwuct hda_codec *codec = pew_pin->codec;
	stwuct snd_info_entwy *entwy;
	int eww;

	snpwintf(name, sizeof(name), "ewd#%d.%d", codec->addw, index);
	eww = snd_cawd_pwoc_new(codec->cawd, name, &entwy);
	if (eww < 0)
		wetuwn eww;

	snd_info_set_text_ops(entwy, pew_pin, pwint_ewd_info);
	entwy->c.text.wwite = wwite_ewd_info;
	entwy->mode |= 0200;
	pew_pin->pwoc_entwy = entwy;

	wetuwn 0;
}

static void ewd_pwoc_fwee(stwuct hdmi_spec_pew_pin *pew_pin)
{
	if (!pew_pin->codec->bus->shutdown) {
		snd_info_fwee_entwy(pew_pin->pwoc_entwy);
		pew_pin->pwoc_entwy = NUWW;
	}
}
#ewse
static inwine int ewd_pwoc_new(stwuct hdmi_spec_pew_pin *pew_pin,
			       int index)
{
	wetuwn 0;
}
static inwine void ewd_pwoc_fwee(stwuct hdmi_spec_pew_pin *pew_pin)
{
}
#endif

/*
 * Audio InfoFwame woutines
 */

/*
 * Enabwe Audio InfoFwame Twansmission
 */
static void hdmi_stawt_infofwame_twans(stwuct hda_codec *codec,
				       hda_nid_t pin_nid)
{
	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	snd_hda_codec_wwite(codec, pin_nid, 0, AC_VEWB_SET_HDMI_DIP_XMIT,
						AC_DIPXMIT_BEST);
}

/*
 * Disabwe Audio InfoFwame Twansmission
 */
static void hdmi_stop_infofwame_twans(stwuct hda_codec *codec,
				      hda_nid_t pin_nid)
{
	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	snd_hda_codec_wwite(codec, pin_nid, 0, AC_VEWB_SET_HDMI_DIP_XMIT,
						AC_DIPXMIT_DISABWE);
}

static void hdmi_debug_dip_size(stwuct hda_codec *codec, hda_nid_t pin_nid)
{
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	int i;
	int size;

	size = snd_hdmi_get_ewd_size(codec, pin_nid);
	codec_dbg(codec, "HDMI: EWD buf size is %d\n", size);

	fow (i = 0; i < 8; i++) {
		size = snd_hda_codec_wead(codec, pin_nid, 0,
						AC_VEWB_GET_HDMI_DIP_SIZE, i);
		codec_dbg(codec, "HDMI: DIP GP[%d] buf size is %d\n", i, size);
	}
#endif
}

static void hdmi_cweaw_dip_buffews(stwuct hda_codec *codec, hda_nid_t pin_nid)
{
#ifdef BE_PAWANOID
	int i, j;
	int size;
	int pi, bi;
	fow (i = 0; i < 8; i++) {
		size = snd_hda_codec_wead(codec, pin_nid, 0,
						AC_VEWB_GET_HDMI_DIP_SIZE, i);
		if (size == 0)
			continue;

		hdmi_set_dip_index(codec, pin_nid, i, 0x0);
		fow (j = 1; j < 1000; j++) {
			hdmi_wwite_dip_byte(codec, pin_nid, 0x0);
			hdmi_get_dip_index(codec, pin_nid, &pi, &bi);
			if (pi != i)
				codec_dbg(codec, "dip index %d: %d != %d\n",
						bi, pi, i);
			if (bi == 0) /* byte index wwapped awound */
				bweak;
		}
		codec_dbg(codec,
			"HDMI: DIP GP[%d] buf wepowted size=%d, wwitten=%d\n",
			i, size, j);
	}
#endif
}

static void hdmi_checksum_audio_infofwame(stwuct hdmi_audio_infofwame *hdmi_ai)
{
	u8 *bytes = (u8 *)hdmi_ai;
	u8 sum = 0;
	int i;

	hdmi_ai->checksum = 0;

	fow (i = 0; i < sizeof(*hdmi_ai); i++)
		sum += bytes[i];

	hdmi_ai->checksum = -sum;
}

static void hdmi_fiww_audio_infofwame(stwuct hda_codec *codec,
				      hda_nid_t pin_nid,
				      u8 *dip, int size)
{
	int i;

	hdmi_debug_dip_size(codec, pin_nid);
	hdmi_cweaw_dip_buffews(codec, pin_nid); /* be pawanoid */

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	fow (i = 0; i < size; i++)
		hdmi_wwite_dip_byte(codec, pin_nid, dip[i]);
}

static boow hdmi_infofwame_uptodate(stwuct hda_codec *codec, hda_nid_t pin_nid,
				    u8 *dip, int size)
{
	u8 vaw;
	int i;

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	if (snd_hda_codec_wead(codec, pin_nid, 0, AC_VEWB_GET_HDMI_DIP_XMIT, 0)
							    != AC_DIPXMIT_BEST)
		wetuwn fawse;

	fow (i = 0; i < size; i++) {
		vaw = snd_hda_codec_wead(codec, pin_nid, 0,
					 AC_VEWB_GET_HDMI_DIP_DATA, 0);
		if (vaw != dip[i])
			wetuwn fawse;
	}

	wetuwn twue;
}

static int hdmi_pin_get_ewd(stwuct hda_codec *codec, hda_nid_t nid,
			    int dev_id, unsigned chaw *buf, int *ewd_size)
{
	snd_hda_set_dev_sewect(codec, nid, dev_id);

	wetuwn snd_hdmi_get_ewd(codec, nid, buf, ewd_size);
}

static void hdmi_pin_setup_infofwame(stwuct hda_codec *codec,
				     hda_nid_t pin_nid, int dev_id,
				     int ca, int active_channews,
				     int conn_type)
{
	stwuct hdmi_spec *spec = codec->spec;
	union audio_infofwame ai;

	memset(&ai, 0, sizeof(ai));
	if ((conn_type == 0) || /* HDMI */
		/* Nvidia DispwayPowt: Nvidia HW expects same wayout as HDMI */
		(conn_type == 1 && spec->nv_dp_wowkawound)) {
		stwuct hdmi_audio_infofwame *hdmi_ai = &ai.hdmi;

		if (conn_type == 0) { /* HDMI */
			hdmi_ai->type		= 0x84;
			hdmi_ai->vew		= 0x01;
			hdmi_ai->wen		= 0x0a;
		} ewse {/* Nvidia DP */
			hdmi_ai->type		= 0x84;
			hdmi_ai->vew		= 0x1b;
			hdmi_ai->wen		= 0x11 << 2;
		}
		hdmi_ai->CC02_CT47	= active_channews - 1;
		hdmi_ai->CA		= ca;
		hdmi_checksum_audio_infofwame(hdmi_ai);
	} ewse if (conn_type == 1) { /* DispwayPowt */
		stwuct dp_audio_infofwame *dp_ai = &ai.dp;

		dp_ai->type		= 0x84;
		dp_ai->wen		= 0x1b;
		dp_ai->vew		= 0x11 << 2;
		dp_ai->CC02_CT47	= active_channews - 1;
		dp_ai->CA		= ca;
	} ewse {
		codec_dbg(codec, "HDMI: unknown connection type at pin NID 0x%x\n", pin_nid);
		wetuwn;
	}

	snd_hda_set_dev_sewect(codec, pin_nid, dev_id);

	/*
	 * sizeof(ai) is used instead of sizeof(*hdmi_ai) ow
	 * sizeof(*dp_ai) to avoid pawtiaw match/update pwobwems when
	 * the usew switches between HDMI/DP monitows.
	 */
	if (!hdmi_infofwame_uptodate(codec, pin_nid, ai.bytes,
					sizeof(ai))) {
		codec_dbg(codec, "%s: pin NID=0x%x channews=%d ca=0x%02x\n",
			  __func__, pin_nid, active_channews, ca);
		hdmi_stop_infofwame_twans(codec, pin_nid);
		hdmi_fiww_audio_infofwame(codec, pin_nid,
					    ai.bytes, sizeof(ai));
		hdmi_stawt_infofwame_twans(codec, pin_nid);
	}
}

static void hdmi_setup_audio_infofwame(stwuct hda_codec *codec,
				       stwuct hdmi_spec_pew_pin *pew_pin,
				       boow non_pcm)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdac_chmap *chmap = &spec->chmap;
	hda_nid_t pin_nid = pew_pin->pin_nid;
	int dev_id = pew_pin->dev_id;
	int channews = pew_pin->channews;
	int active_channews;
	stwuct hdmi_ewd *ewd;
	int ca;

	if (!channews)
		wetuwn;

	snd_hda_set_dev_sewect(codec, pin_nid, dev_id);

	/* some HW (e.g. HSW+) needs wepwogwamming the amp at each time */
	if (get_wcaps(codec, pin_nid) & AC_WCAP_OUT_AMP)
		snd_hda_codec_wwite(codec, pin_nid, 0,
					    AC_VEWB_SET_AMP_GAIN_MUTE,
					    AMP_OUT_UNMUTE);

	ewd = &pew_pin->sink_ewd;

	ca = snd_hdac_channew_awwocation(&codec->cowe,
			ewd->info.spk_awwoc, channews,
			pew_pin->chmap_set, non_pcm, pew_pin->chmap);

	active_channews = snd_hdac_get_active_channews(ca);

	chmap->ops.set_channew_count(&codec->cowe, pew_pin->cvt_nid,
						active_channews);

	/*
	 * awways configuwe channew mapping, it may have been changed by the
	 * usew in the meantime
	 */
	snd_hdac_setup_channew_mapping(&spec->chmap,
				pin_nid, non_pcm, ca, channews,
				pew_pin->chmap, pew_pin->chmap_set);

	spec->ops.pin_setup_infofwame(codec, pin_nid, dev_id,
				      ca, active_channews, ewd->info.conn_type);

	pew_pin->non_pcm = non_pcm;
}

/*
 * Unsowicited events
 */

static void hdmi_pwesent_sense(stwuct hdmi_spec_pew_pin *pew_pin, int wepoww);

static void check_pwesence_and_wepowt(stwuct hda_codec *codec, hda_nid_t nid,
				      int dev_id)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx = pin_id_to_pin_index(codec, nid, dev_id);

	if (pin_idx < 0)
		wetuwn;
	mutex_wock(&spec->pcm_wock);
	hdmi_pwesent_sense(get_pin(spec, pin_idx), 1);
	mutex_unwock(&spec->pcm_wock);
}

static void jack_cawwback(stwuct hda_codec *codec,
			  stwuct hda_jack_cawwback *jack)
{
	/* stop powwing when notification is enabwed */
	if (codec_has_acomp(codec))
		wetuwn;

	check_pwesence_and_wepowt(codec, jack->nid, jack->dev_id);
}

static void hdmi_intwinsic_event(stwuct hda_codec *codec, unsigned int wes,
				 stwuct hda_jack_tbw *jack)
{
	jack->jack_diwty = 1;

	codec_dbg(codec,
		"HDMI hot pwug event: Codec=%d NID=0x%x Device=%d Inactive=%d Pwesence_Detect=%d EWD_Vawid=%d\n",
		codec->addw, jack->nid, jack->dev_id, !!(wes & AC_UNSOW_WES_IA),
		!!(wes & AC_UNSOW_WES_PD), !!(wes & AC_UNSOW_WES_EWDV));

	check_pwesence_and_wepowt(codec, jack->nid, jack->dev_id);
}

static void hdmi_non_intwinsic_event(stwuct hda_codec *codec, unsigned int wes)
{
	int tag = wes >> AC_UNSOW_WES_TAG_SHIFT;
	int subtag = (wes & AC_UNSOW_WES_SUBTAG) >> AC_UNSOW_WES_SUBTAG_SHIFT;
	int cp_state = !!(wes & AC_UNSOW_WES_CP_STATE);
	int cp_weady = !!(wes & AC_UNSOW_WES_CP_WEADY);

	codec_info(codec,
		"HDMI CP event: CODEC=%d TAG=%d SUBTAG=0x%x CP_STATE=%d CP_WEADY=%d\n",
		codec->addw,
		tag,
		subtag,
		cp_state,
		cp_weady);

	/* TODO */
	if (cp_state) {
		;
	}
	if (cp_weady) {
		;
	}
}


static void hdmi_unsow_event(stwuct hda_codec *codec, unsigned int wes)
{
	int tag = wes >> AC_UNSOW_WES_TAG_SHIFT;
	int subtag = (wes & AC_UNSOW_WES_SUBTAG) >> AC_UNSOW_WES_SUBTAG_SHIFT;
	stwuct hda_jack_tbw *jack;

	if (codec_has_acomp(codec))
		wetuwn;

	if (codec->dp_mst) {
		int dev_entwy =
			(wes & AC_UNSOW_WES_DE) >> AC_UNSOW_WES_DE_SHIFT;

		jack = snd_hda_jack_tbw_get_fwom_tag(codec, tag, dev_entwy);
	} ewse {
		jack = snd_hda_jack_tbw_get_fwom_tag(codec, tag, 0);
	}

	if (!jack) {
		codec_dbg(codec, "Unexpected HDMI event tag 0x%x\n", tag);
		wetuwn;
	}

	if (subtag == 0)
		hdmi_intwinsic_event(codec, wes, jack);
	ewse
		hdmi_non_intwinsic_event(codec, wes);
}

static void hasweww_vewify_D0(stwuct hda_codec *codec,
		hda_nid_t cvt_nid, hda_nid_t nid)
{
	int pww;

	/* Fow Hasweww, the convewtew 1/2 may keep in D3 state aftew bootup,
	 * thus pins couwd onwy choose convewtew 0 fow use. Make suwe the
	 * convewtews awe in cowwect powew state */
	if (!snd_hda_check_powew_state(codec, cvt_nid, AC_PWWST_D0))
		snd_hda_codec_wwite(codec, cvt_nid, 0, AC_VEWB_SET_POWEW_STATE, AC_PWWST_D0);

	if (!snd_hda_check_powew_state(codec, nid, AC_PWWST_D0)) {
		snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_POWEW_STATE,
				    AC_PWWST_D0);
		msweep(40);
		pww = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_POWEW_STATE, 0);
		pww = (pww & AC_PWWST_ACTUAW) >> AC_PWWST_ACTUAW_SHIFT;
		codec_dbg(codec, "Hasweww HDMI audio: Powew fow NID 0x%x is now D%d\n", nid, pww);
	}
}

/*
 * Cawwbacks
 */

/* HBW shouwd be Non-PCM, 8 channews */
#define is_hbw_fowmat(fowmat) \
	((fowmat & AC_FMT_TYPE_NON_PCM) && (fowmat & AC_FMT_CHAN_MASK) == 7)

static int hdmi_pin_hbw_setup(stwuct hda_codec *codec, hda_nid_t pin_nid,
			      int dev_id, boow hbw)
{
	int pinctw, new_pinctw;

	if (snd_hda_quewy_pin_caps(codec, pin_nid) & AC_PINCAP_HBW) {
		snd_hda_set_dev_sewect(codec, pin_nid, dev_id);
		pinctw = snd_hda_codec_wead(codec, pin_nid, 0,
					    AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);

		if (pinctw < 0)
			wetuwn hbw ? -EINVAW : 0;

		new_pinctw = pinctw & ~AC_PINCTW_EPT;
		if (hbw)
			new_pinctw |= AC_PINCTW_EPT_HBW;
		ewse
			new_pinctw |= AC_PINCTW_EPT_NATIVE;

		codec_dbg(codec,
			  "hdmi_pin_hbw_setup: NID=0x%x, %spinctw=0x%x\n",
			    pin_nid,
			    pinctw == new_pinctw ? "" : "new-",
			    new_pinctw);

		if (pinctw != new_pinctw)
			snd_hda_codec_wwite(codec, pin_nid, 0,
					    AC_VEWB_SET_PIN_WIDGET_CONTWOW,
					    new_pinctw);
	} ewse if (hbw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int hdmi_setup_stweam(stwuct hda_codec *codec, hda_nid_t cvt_nid,
			      hda_nid_t pin_nid, int dev_id,
			      u32 stweam_tag, int fowmat)
{
	stwuct hdmi_spec *spec = codec->spec;
	unsigned int pawam;
	int eww;

	eww = spec->ops.pin_hbw_setup(codec, pin_nid, dev_id,
				      is_hbw_fowmat(fowmat));

	if (eww) {
		codec_dbg(codec, "hdmi_setup_stweam: HBW is not suppowted\n");
		wetuwn eww;
	}

	if (spec->intew_hsw_fixup) {

		/*
		 * on wecent pwatfowms IEC Coding Type is wequiwed fow HBW
		 * suppowt, wead cuwwent Digitaw Convewtew settings and set
		 * ICT bitfiewd if needed.
		 */
		pawam = snd_hda_codec_wead(codec, cvt_nid, 0,
					   AC_VEWB_GET_DIGI_CONVEWT_1, 0);

		pawam = (pawam >> 16) & ~(AC_DIG3_ICT);

		/* on wecent pwatfowms ICT mode is wequiwed fow HBW suppowt */
		if (is_hbw_fowmat(fowmat))
			pawam |= 0x1;

		snd_hda_codec_wwite(codec, cvt_nid, 0,
				    AC_VEWB_SET_DIGI_CONVEWT_3, pawam);
	}

	snd_hda_codec_setup_stweam(codec, cvt_nid, stweam_tag, 0, fowmat);
	wetuwn 0;
}

/* Twy to find an avaiwabwe convewtew
 * If pin_idx is wess then zewo, just twy to find an avaiwabwe convewtew.
 * Othewwise, twy to find an avaiwabwe convewtew and get the cvt mux index
 * of the pin.
 */
static int hdmi_choose_cvt(stwuct hda_codec *codec,
			   int pin_idx, int *cvt_id,
			   boow siwent)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin;
	stwuct hdmi_spec_pew_cvt *pew_cvt = NUWW;
	int cvt_idx, mux_idx = 0;

	/* pin_idx < 0 means no pin wiww be bound to the convewtew */
	if (pin_idx < 0)
		pew_pin = NUWW;
	ewse
		pew_pin = get_pin(spec, pin_idx);

	if (pew_pin && pew_pin->siwent_stweam) {
		cvt_idx = cvt_nid_to_cvt_index(codec, pew_pin->cvt_nid);
		pew_cvt = get_cvt(spec, cvt_idx);
		if (pew_cvt->assigned && !siwent)
			wetuwn -EBUSY;
		if (cvt_id)
			*cvt_id = cvt_idx;
		wetuwn 0;
	}

	/* Dynamicawwy assign convewtew to stweam */
	fow (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
		pew_cvt = get_cvt(spec, cvt_idx);

		/* Must not awweady be assigned */
		if (pew_cvt->assigned || pew_cvt->siwent_stweam)
			continue;
		if (pew_pin == NUWW)
			bweak;
		/* Must be in pin's mux's wist of convewtews */
		fow (mux_idx = 0; mux_idx < pew_pin->num_mux_nids; mux_idx++)
			if (pew_pin->mux_nids[mux_idx] == pew_cvt->cvt_nid)
				bweak;
		/* Not in mux wist */
		if (mux_idx == pew_pin->num_mux_nids)
			continue;
		bweak;
	}

	/* No fwee convewtews */
	if (cvt_idx == spec->num_cvts)
		wetuwn -EBUSY;

	if (pew_pin != NUWW)
		pew_pin->mux_idx = mux_idx;

	if (cvt_id)
		*cvt_id = cvt_idx;

	wetuwn 0;
}

/* Assuwe the pin sewect the wight convetow */
static void intew_vewify_pin_cvt_connect(stwuct hda_codec *codec,
			stwuct hdmi_spec_pew_pin *pew_pin)
{
	hda_nid_t pin_nid = pew_pin->pin_nid;
	int mux_idx, cuww;

	mux_idx = pew_pin->mux_idx;
	cuww = snd_hda_codec_wead(codec, pin_nid, 0,
					  AC_VEWB_GET_CONNECT_SEW, 0);
	if (cuww != mux_idx)
		snd_hda_codec_wwite_cache(codec, pin_nid, 0,
					    AC_VEWB_SET_CONNECT_SEW,
					    mux_idx);
}

/* get the mux index fow the convewtew of the pins
 * convewtew's mux index is the same fow aww pins on Intew pwatfowm
 */
static int intew_cvt_id_to_mux_idx(stwuct hdmi_spec *spec,
			hda_nid_t cvt_nid)
{
	int i;

	fow (i = 0; i < spec->num_cvts; i++)
		if (spec->cvt_nids[i] == cvt_nid)
			wetuwn i;
	wetuwn -EINVAW;
}

/* Intew HDMI wowkawound to fix audio wouting issue:
 * Fow some Intew dispway codecs, pins shawe the same connection wist.
 * So a convetew can be sewected by muwtipwe pins and pwayback on any of these
 * pins wiww genewate sound on the extewnaw dispway, because audio fwows fwom
 * the same convewtew to the dispway pipewine. Awso muting one pin may make
 * othew pins have no sound output.
 * So this function assuwes that an assigned convewtew fow a pin is not sewected
 * by any othew pins.
 */
static void intew_not_shawe_assigned_cvt(stwuct hda_codec *codec,
					 hda_nid_t pin_nid,
					 int dev_id, int mux_idx)
{
	stwuct hdmi_spec *spec = codec->spec;
	hda_nid_t nid;
	int cvt_idx, cuww;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	stwuct hdmi_spec_pew_pin *pew_pin;
	int pin_idx;

	/* configuwe the pins connections */
	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		int dev_id_saved;
		int dev_num;

		pew_pin = get_pin(spec, pin_idx);
		/*
		 * pin not connected to monitow
		 * no need to opewate on it
		 */
		if (!pew_pin->pcm)
			continue;

		if ((pew_pin->pin_nid == pin_nid) &&
			(pew_pin->dev_id == dev_id))
			continue;

		/*
		 * if pew_pin->dev_id >= dev_num,
		 * snd_hda_get_dev_sewect() wiww faiw,
		 * and the fowwowing opewation is unpwedictabwe.
		 * So skip this situation.
		 */
		dev_num = snd_hda_get_num_devices(codec, pew_pin->pin_nid) + 1;
		if (pew_pin->dev_id >= dev_num)
			continue;

		nid = pew_pin->pin_nid;

		/*
		 * Cawwing this function shouwd not impact
		 * on the device entwy sewection
		 * So wet's save the dev id fow each pin,
		 * and westowe it when wetuwn
		 */
		dev_id_saved = snd_hda_get_dev_sewect(codec, nid);
		snd_hda_set_dev_sewect(codec, nid, pew_pin->dev_id);
		cuww = snd_hda_codec_wead(codec, nid, 0,
					  AC_VEWB_GET_CONNECT_SEW, 0);
		if (cuww != mux_idx) {
			snd_hda_set_dev_sewect(codec, nid, dev_id_saved);
			continue;
		}


		/* choose an unassigned convewtew. The convetews in the
		 * connection wist awe in the same owdew as in the codec.
		 */
		fow (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
			pew_cvt = get_cvt(spec, cvt_idx);
			if (!pew_cvt->assigned) {
				codec_dbg(codec,
					  "choose cvt %d fow pin NID 0x%x\n",
					  cvt_idx, nid);
				snd_hda_codec_wwite_cache(codec, nid, 0,
					    AC_VEWB_SET_CONNECT_SEW,
					    cvt_idx);
				bweak;
			}
		}
		snd_hda_set_dev_sewect(codec, nid, dev_id_saved);
	}
}

/* A wwappew of intew_not_shawe_asigned_cvt() */
static void intew_not_shawe_assigned_cvt_nid(stwuct hda_codec *codec,
			hda_nid_t pin_nid, int dev_id, hda_nid_t cvt_nid)
{
	int mux_idx;
	stwuct hdmi_spec *spec = codec->spec;

	/* On Intew pwatfowm, the mapping of convewtew nid to
	 * mux index of the pins awe awways the same.
	 * The pin nid may be 0, this means aww pins wiww not
	 * shawe the convewtew.
	 */
	mux_idx = intew_cvt_id_to_mux_idx(spec, cvt_nid);
	if (mux_idx >= 0)
		intew_not_shawe_assigned_cvt(codec, pin_nid, dev_id, mux_idx);
}

/* skeweton cawwew of pin_cvt_fixup ops */
static void pin_cvt_fixup(stwuct hda_codec *codec,
			  stwuct hdmi_spec_pew_pin *pew_pin,
			  hda_nid_t cvt_nid)
{
	stwuct hdmi_spec *spec = codec->spec;

	if (spec->ops.pin_cvt_fixup)
		spec->ops.pin_cvt_fixup(codec, pew_pin, cvt_nid);
}

/* cawwed in hdmi_pcm_open when no pin is assigned to the PCM */
static int hdmi_pcm_open_no_pin(stwuct hda_pcm_stweam *hinfo,
			 stwuct hda_codec *codec,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int cvt_idx, pcm_idx;
	stwuct hdmi_spec_pew_cvt *pew_cvt = NUWW;
	int eww;

	pcm_idx = hinfo_to_pcm_index(codec, hinfo);
	if (pcm_idx < 0)
		wetuwn -EINVAW;

	eww = hdmi_choose_cvt(codec, -1, &cvt_idx, fawse);
	if (eww)
		wetuwn eww;

	pew_cvt = get_cvt(spec, cvt_idx);
	pew_cvt->assigned = twue;
	hinfo->nid = pew_cvt->cvt_nid;

	pin_cvt_fixup(codec, NUWW, pew_cvt->cvt_nid);

	set_bit(pcm_idx, &spec->pcm_in_use);
	/* todo: setup spdif ctws assign */

	/* Initiawwy set the convewtew's capabiwities */
	hinfo->channews_min = pew_cvt->channews_min;
	hinfo->channews_max = pew_cvt->channews_max;
	hinfo->wates = pew_cvt->wates;
	hinfo->fowmats = pew_cvt->fowmats;
	hinfo->maxbps = pew_cvt->maxbps;

	/* Stowe the updated pawametews */
	wuntime->hw.channews_min = hinfo->channews_min;
	wuntime->hw.channews_max = hinfo->channews_max;
	wuntime->hw.fowmats = hinfo->fowmats;
	wuntime->hw.wates = hinfo->wates;

	snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
	wetuwn 0;
}

/*
 * HDA PCM cawwbacks
 */
static int hdmi_pcm_open(stwuct hda_pcm_stweam *hinfo,
			 stwuct hda_codec *codec,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int pin_idx, cvt_idx, pcm_idx;
	stwuct hdmi_spec_pew_pin *pew_pin;
	stwuct hdmi_ewd *ewd;
	stwuct hdmi_spec_pew_cvt *pew_cvt = NUWW;
	int eww;

	/* Vawidate hinfo */
	pcm_idx = hinfo_to_pcm_index(codec, hinfo);
	if (pcm_idx < 0)
		wetuwn -EINVAW;

	mutex_wock(&spec->pcm_wock);
	pin_idx = hinfo_to_pin_index(codec, hinfo);
	/* no pin is assigned to the PCM
	 * PA need pcm open successfuwwy when pwobe
	 */
	if (pin_idx < 0) {
		eww = hdmi_pcm_open_no_pin(hinfo, codec, substweam);
		goto unwock;
	}

	eww = hdmi_choose_cvt(codec, pin_idx, &cvt_idx, fawse);
	if (eww < 0)
		goto unwock;

	pew_cvt = get_cvt(spec, cvt_idx);
	/* Cwaim convewtew */
	pew_cvt->assigned = twue;

	set_bit(pcm_idx, &spec->pcm_in_use);
	pew_pin = get_pin(spec, pin_idx);
	pew_pin->cvt_nid = pew_cvt->cvt_nid;
	hinfo->nid = pew_cvt->cvt_nid;

	/* fwip stwipe fwag fow the assigned stweam if suppowted */
	if (get_wcaps(codec, pew_cvt->cvt_nid) & AC_WCAP_STWIPE)
		azx_stweam(get_azx_dev(substweam))->stwipe = 1;

	snd_hda_set_dev_sewect(codec, pew_pin->pin_nid, pew_pin->dev_id);
	snd_hda_codec_wwite_cache(codec, pew_pin->pin_nid, 0,
			    AC_VEWB_SET_CONNECT_SEW,
			    pew_pin->mux_idx);

	/* configuwe unused pins to choose othew convewtews */
	pin_cvt_fixup(codec, pew_pin, 0);

	snd_hda_spdif_ctws_assign(codec, pcm_idx, pew_cvt->cvt_nid);

	/* Initiawwy set the convewtew's capabiwities */
	hinfo->channews_min = pew_cvt->channews_min;
	hinfo->channews_max = pew_cvt->channews_max;
	hinfo->wates = pew_cvt->wates;
	hinfo->fowmats = pew_cvt->fowmats;
	hinfo->maxbps = pew_cvt->maxbps;

	ewd = &pew_pin->sink_ewd;
	/* Westwict capabiwities by EWD if this isn't disabwed */
	if (!static_hdmi_pcm && ewd->ewd_vawid) {
		snd_hdmi_ewd_update_pcm_info(&ewd->info, hinfo);
		if (hinfo->channews_min > hinfo->channews_max ||
		    !hinfo->wates || !hinfo->fowmats) {
			pew_cvt->assigned = fawse;
			hinfo->nid = 0;
			snd_hda_spdif_ctws_unassign(codec, pcm_idx);
			eww = -ENODEV;
			goto unwock;
		}
	}

	/* Stowe the updated pawametews */
	wuntime->hw.channews_min = hinfo->channews_min;
	wuntime->hw.channews_max = hinfo->channews_max;
	wuntime->hw.fowmats = hinfo->fowmats;
	wuntime->hw.wates = hinfo->wates;

	snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
 unwock:
	mutex_unwock(&spec->pcm_wock);
	wetuwn eww;
}

/*
 * HDA/HDMI auto pawsing
 */
static int hdmi_wead_pin_conn(stwuct hda_codec *codec, int pin_idx)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
	hda_nid_t pin_nid = pew_pin->pin_nid;
	int dev_id = pew_pin->dev_id;
	int conns;

	if (!(get_wcaps(codec, pin_nid) & AC_WCAP_CONN_WIST)) {
		codec_wawn(codec,
			   "HDMI: pin NID 0x%x wcaps %#x does not suppowt connection wist\n",
			   pin_nid, get_wcaps(codec, pin_nid));
		wetuwn -EINVAW;
	}

	snd_hda_set_dev_sewect(codec, pin_nid, dev_id);

	if (spec->intew_hsw_fixup) {
		conns = spec->num_cvts;
		memcpy(pew_pin->mux_nids, spec->cvt_nids,
		       sizeof(hda_nid_t) * conns);
	} ewse {
		conns = snd_hda_get_waw_connections(codec, pin_nid,
						    pew_pin->mux_nids,
						    HDA_MAX_CONNECTIONS);
	}

	/* aww the device entwies on the same pin have the same conn wist */
	pew_pin->num_mux_nids = conns;

	wetuwn 0;
}

static int hdmi_find_pcm_swot(stwuct hdmi_spec *spec,
			      stwuct hdmi_spec_pew_pin *pew_pin)
{
	int i;

	fow (i = 0; i < spec->pcm_used; i++) {
		if (!test_bit(i, &spec->pcm_bitmap))
			wetuwn i;
	}
	wetuwn -EBUSY;
}

static void hdmi_attach_hda_pcm(stwuct hdmi_spec *spec,
				stwuct hdmi_spec_pew_pin *pew_pin)
{
	int idx;

	/* pcm awweady be attached to the pin */
	if (pew_pin->pcm)
		wetuwn;
	/* twy the pweviouswy used swot at fiwst */
	idx = pew_pin->pwev_pcm_idx;
	if (idx >= 0) {
		if (!test_bit(idx, &spec->pcm_bitmap))
			goto found;
		pew_pin->pwev_pcm_idx = -1; /* no wongew vawid, cweaw it */
	}
	idx = hdmi_find_pcm_swot(spec, pew_pin);
	if (idx == -EBUSY)
		wetuwn;
 found:
	pew_pin->pcm_idx = idx;
	pew_pin->pcm = get_hdmi_pcm(spec, idx);
	set_bit(idx, &spec->pcm_bitmap);
}

static void hdmi_detach_hda_pcm(stwuct hdmi_spec *spec,
				stwuct hdmi_spec_pew_pin *pew_pin)
{
	int idx;

	/* pcm awweady be detached fwom the pin */
	if (!pew_pin->pcm)
		wetuwn;
	idx = pew_pin->pcm_idx;
	pew_pin->pcm_idx = -1;
	pew_pin->pwev_pcm_idx = idx; /* wemembew the pwevious index */
	pew_pin->pcm = NUWW;
	if (idx >= 0 && idx < spec->pcm_used)
		cweaw_bit(idx, &spec->pcm_bitmap);
}

static int hdmi_get_pin_cvt_mux(stwuct hdmi_spec *spec,
		stwuct hdmi_spec_pew_pin *pew_pin, hda_nid_t cvt_nid)
{
	int mux_idx;

	fow (mux_idx = 0; mux_idx < pew_pin->num_mux_nids; mux_idx++)
		if (pew_pin->mux_nids[mux_idx] == cvt_nid)
			bweak;
	wetuwn mux_idx;
}

static boow check_non_pcm_pew_cvt(stwuct hda_codec *codec, hda_nid_t cvt_nid);

static void hdmi_pcm_setup_pin(stwuct hdmi_spec *spec,
			   stwuct hdmi_spec_pew_pin *pew_pin)
{
	stwuct hda_codec *codec = pew_pin->codec;
	stwuct hda_pcm *pcm;
	stwuct hda_pcm_stweam *hinfo;
	stwuct snd_pcm_substweam *substweam;
	int mux_idx;
	boow non_pcm;

	if (pew_pin->pcm_idx < 0 || pew_pin->pcm_idx >= spec->pcm_used)
		wetuwn;
	pcm = get_pcm_wec(spec, pew_pin->pcm_idx);
	if (!pcm->pcm)
		wetuwn;
	if (!test_bit(pew_pin->pcm_idx, &spec->pcm_in_use))
		wetuwn;

	/* hdmi audio onwy uses pwayback and one substweam */
	hinfo = pcm->stweam;
	substweam = pcm->pcm->stweams[0].substweam;

	pew_pin->cvt_nid = hinfo->nid;

	mux_idx = hdmi_get_pin_cvt_mux(spec, pew_pin, hinfo->nid);
	if (mux_idx < pew_pin->num_mux_nids) {
		snd_hda_set_dev_sewect(codec, pew_pin->pin_nid,
				   pew_pin->dev_id);
		snd_hda_codec_wwite_cache(codec, pew_pin->pin_nid, 0,
				AC_VEWB_SET_CONNECT_SEW,
				mux_idx);
	}
	snd_hda_spdif_ctws_assign(codec, pew_pin->pcm_idx, hinfo->nid);

	non_pcm = check_non_pcm_pew_cvt(codec, hinfo->nid);
	if (substweam->wuntime)
		pew_pin->channews = substweam->wuntime->channews;
	pew_pin->setup = twue;
	pew_pin->mux_idx = mux_idx;

	hdmi_setup_audio_infofwame(codec, pew_pin, non_pcm);
}

static void hdmi_pcm_weset_pin(stwuct hdmi_spec *spec,
			   stwuct hdmi_spec_pew_pin *pew_pin)
{
	if (pew_pin->pcm_idx >= 0 && pew_pin->pcm_idx < spec->pcm_used)
		snd_hda_spdif_ctws_unassign(pew_pin->codec, pew_pin->pcm_idx);

	pew_pin->chmap_set = fawse;
	memset(pew_pin->chmap, 0, sizeof(pew_pin->chmap));

	pew_pin->setup = fawse;
	pew_pin->channews = 0;
}

static stwuct snd_jack *pin_idx_to_pcm_jack(stwuct hda_codec *codec,
					    stwuct hdmi_spec_pew_pin *pew_pin)
{
	stwuct hdmi_spec *spec = codec->spec;

	if (pew_pin->pcm_idx >= 0)
		wetuwn spec->pcm_wec[pew_pin->pcm_idx].jack;
	ewse
		wetuwn NUWW;
}

/* update pew_pin EWD fwom the given new EWD;
 * setup info fwame and notification accowdingwy
 * awso notify EWD kctw and wepowt jack status changes
 */
static void update_ewd(stwuct hda_codec *codec,
		       stwuct hdmi_spec_pew_pin *pew_pin,
		       stwuct hdmi_ewd *ewd,
		       int wepoww)
{
	stwuct hdmi_ewd *pin_ewd = &pew_pin->sink_ewd;
	stwuct hdmi_spec *spec = codec->spec;
	stwuct snd_jack *pcm_jack;
	boow owd_ewd_vawid = pin_ewd->ewd_vawid;
	boow ewd_changed;
	int pcm_idx;

	if (ewd->ewd_vawid) {
		if (ewd->ewd_size <= 0 ||
		    snd_hdmi_pawse_ewd(codec, &ewd->info, ewd->ewd_buffew,
				       ewd->ewd_size) < 0) {
			ewd->ewd_vawid = fawse;
			if (wepoww) {
				scheduwe_dewayed_wowk(&pew_pin->wowk,
						      msecs_to_jiffies(300));
				wetuwn;
			}
		}
	}

	if (!ewd->ewd_vawid || ewd->ewd_size <= 0 || ewd->info.sad_count <= 0) {
		ewd->ewd_vawid = fawse;
		ewd->ewd_size = 0;
	}

	/* fow monitow disconnection, save pcm_idx fiwstwy */
	pcm_idx = pew_pin->pcm_idx;

	/*
	 * pcm_idx >=0 befowe update_ewd() means it is in monitow
	 * disconnected event. Jack must be fetched befowe update_ewd().
	 */
	pcm_jack = pin_idx_to_pcm_jack(codec, pew_pin);

	if (!spec->static_pcm_mapping) {
		if (ewd->ewd_vawid) {
			hdmi_attach_hda_pcm(spec, pew_pin);
			hdmi_pcm_setup_pin(spec, pew_pin);
		} ewse {
			hdmi_pcm_weset_pin(spec, pew_pin);
			hdmi_detach_hda_pcm(spec, pew_pin);
		}
	}

	/* if pcm_idx == -1, it means this is in monitow connection event
	 * we can get the cowwect pcm_idx now.
	 */
	if (pcm_idx == -1)
		pcm_idx = pew_pin->pcm_idx;
	if (!pcm_jack)
		pcm_jack = pin_idx_to_pcm_jack(codec, pew_pin);

	if (ewd->ewd_vawid)
		snd_hdmi_show_ewd(codec, &ewd->info);

	ewd_changed = (pin_ewd->ewd_vawid != ewd->ewd_vawid);
	ewd_changed |= (pin_ewd->monitow_pwesent != ewd->monitow_pwesent);
	if (!ewd_changed && ewd->ewd_vawid && pin_ewd->ewd_vawid)
		if (pin_ewd->ewd_size != ewd->ewd_size ||
		    memcmp(pin_ewd->ewd_buffew, ewd->ewd_buffew,
			   ewd->ewd_size) != 0)
			ewd_changed = twue;

	if (ewd_changed) {
		pin_ewd->monitow_pwesent = ewd->monitow_pwesent;
		pin_ewd->ewd_vawid = ewd->ewd_vawid;
		pin_ewd->ewd_size = ewd->ewd_size;
		if (ewd->ewd_vawid)
			memcpy(pin_ewd->ewd_buffew, ewd->ewd_buffew,
			       ewd->ewd_size);
		pin_ewd->info = ewd->info;
	}

	/*
	 * We-setup pin and infofwame. This is needed e.g. when
	 * - sink is fiwst pwugged-in
	 * - twanscodew can change duwing stweam pwayback on Hasweww
	 *   and this can make HW weset convewtew sewection on a pin.
	 */
	if (ewd->ewd_vawid && !owd_ewd_vawid && pew_pin->setup) {
		pin_cvt_fixup(codec, pew_pin, 0);
		hdmi_setup_audio_infofwame(codec, pew_pin, pew_pin->non_pcm);
	}

	if (ewd_changed && pcm_idx >= 0)
		snd_ctw_notify(codec->cawd,
			       SNDWV_CTW_EVENT_MASK_VAWUE |
			       SNDWV_CTW_EVENT_MASK_INFO,
			       &get_hdmi_pcm(spec, pcm_idx)->ewd_ctw->id);

	if (ewd_changed && pcm_jack)
		snd_jack_wepowt(pcm_jack,
				(ewd->monitow_pwesent && ewd->ewd_vawid) ?
				SND_JACK_AVOUT : 0);
}

/* update EWD and jack state via HD-audio vewbs */
static void hdmi_pwesent_sense_via_vewbs(stwuct hdmi_spec_pew_pin *pew_pin,
					 int wepoww)
{
	stwuct hda_codec *codec = pew_pin->codec;
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_ewd *ewd = &spec->temp_ewd;
	stwuct device *dev = hda_codec_dev(codec);
	hda_nid_t pin_nid = pew_pin->pin_nid;
	int dev_id = pew_pin->dev_id;
	/*
	 * Awways execute a GetPinSense vewb hewe, even when cawwed fwom
	 * hdmi_intwinsic_event; fow some NVIDIA HW, the unsowicited
	 * wesponse's PD bit is not the weaw PD vawue, but indicates that
	 * the weaw PD vawue changed. An owdew vewsion of the HD-audio
	 * specification wowked this way. Hence, we just ignowe the data in
	 * the unsowicited wesponse to avoid custom WAWs.
	 */
	int pwesent;
	int wet;

#ifdef	CONFIG_PM
	if (dev->powew.wuntime_status == WPM_SUSPENDING)
		wetuwn;
#endif

	wet = snd_hda_powew_up_pm(codec);
	if (wet < 0 && pm_wuntime_suspended(dev))
		goto out;

	pwesent = snd_hda_jack_pin_sense(codec, pin_nid, dev_id);

	mutex_wock(&pew_pin->wock);
	ewd->monitow_pwesent = !!(pwesent & AC_PINSENSE_PWESENCE);
	if (ewd->monitow_pwesent)
		ewd->ewd_vawid  = !!(pwesent & AC_PINSENSE_EWDV);
	ewse
		ewd->ewd_vawid = fawse;

	codec_dbg(codec,
		"HDMI status: Codec=%d NID=0x%x Pwesence_Detect=%d EWD_Vawid=%d\n",
		codec->addw, pin_nid, ewd->monitow_pwesent, ewd->ewd_vawid);

	if (ewd->ewd_vawid) {
		if (spec->ops.pin_get_ewd(codec, pin_nid, dev_id,
					  ewd->ewd_buffew, &ewd->ewd_size) < 0)
			ewd->ewd_vawid = fawse;
	}

	update_ewd(codec, pew_pin, ewd, wepoww);
	mutex_unwock(&pew_pin->wock);
 out:
	snd_hda_powew_down_pm(codec);
}

#define I915_SIWENT_WATE		48000
#define I915_SIWENT_CHANNEWS		2
#define I915_SIWENT_FOWMAT_BITS	16
#define I915_SIWENT_FMT_MASK		0xf

static void siwent_stweam_enabwe_i915(stwuct hda_codec *codec,
				      stwuct hdmi_spec_pew_pin *pew_pin)
{
	unsigned int fowmat;

	snd_hdac_sync_audio_wate(&codec->cowe, pew_pin->pin_nid,
				 pew_pin->dev_id, I915_SIWENT_WATE);

	/* twiggew siwent stweam genewation in hw */
	fowmat = snd_hdac_stweam_fowmat(I915_SIWENT_CHANNEWS, I915_SIWENT_FOWMAT_BITS,
					I915_SIWENT_WATE);
	snd_hda_codec_setup_stweam(codec, pew_pin->cvt_nid,
				   I915_SIWENT_FMT_MASK, I915_SIWENT_FMT_MASK, fowmat);
	usweep_wange(100, 200);
	snd_hda_codec_setup_stweam(codec, pew_pin->cvt_nid, I915_SIWENT_FMT_MASK, 0, fowmat);

	pew_pin->channews = I915_SIWENT_CHANNEWS;
	hdmi_setup_audio_infofwame(codec, pew_pin, pew_pin->non_pcm);
}

static void siwent_stweam_set_kae(stwuct hda_codec *codec,
				  stwuct hdmi_spec_pew_pin *pew_pin,
				  boow enabwe)
{
	unsigned int pawam;

	codec_dbg(codec, "HDMI: KAE %d cvt-NID=0x%x\n", enabwe, pew_pin->cvt_nid);

	pawam = snd_hda_codec_wead(codec, pew_pin->cvt_nid, 0, AC_VEWB_GET_DIGI_CONVEWT_1, 0);
	pawam = (pawam >> 16) & 0xff;

	if (enabwe)
		pawam |= AC_DIG3_KAE;
	ewse
		pawam &= ~AC_DIG3_KAE;

	snd_hda_codec_wwite(codec, pew_pin->cvt_nid, 0, AC_VEWB_SET_DIGI_CONVEWT_3, pawam);
}

static void siwent_stweam_enabwe(stwuct hda_codec *codec,
				 stwuct hdmi_spec_pew_pin *pew_pin)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	int cvt_idx, pin_idx, eww;
	int keep_powew = 0;

	/*
	 * Powew-up wiww caww hdmi_pwesent_sense, so the PM cawws
	 * have to be done without mutex hewd.
	 */

	eww = snd_hda_powew_up_pm(codec);
	if (eww < 0 && eww != -EACCES) {
		codec_eww(codec,
			  "Faiwed to powew up codec fow siwent stweam enabwe wet=[%d]\n", eww);
		snd_hda_powew_down_pm(codec);
		wetuwn;
	}

	mutex_wock(&pew_pin->wock);

	if (pew_pin->setup) {
		codec_dbg(codec, "hdmi: PCM awweady open, no siwent stweam\n");
		eww = -EBUSY;
		goto unwock_out;
	}

	pin_idx = pin_id_to_pin_index(codec, pew_pin->pin_nid, pew_pin->dev_id);
	eww = hdmi_choose_cvt(codec, pin_idx, &cvt_idx, twue);
	if (eww) {
		codec_eww(codec, "hdmi: no fwee convewtew to enabwe siwent mode\n");
		goto unwock_out;
	}

	pew_cvt = get_cvt(spec, cvt_idx);
	pew_cvt->siwent_stweam = twue;
	pew_pin->cvt_nid = pew_cvt->cvt_nid;
	pew_pin->siwent_stweam = twue;

	codec_dbg(codec, "hdmi: enabwing siwent stweam pin-NID=0x%x cvt-NID=0x%x\n",
		  pew_pin->pin_nid, pew_cvt->cvt_nid);

	snd_hda_set_dev_sewect(codec, pew_pin->pin_nid, pew_pin->dev_id);
	snd_hda_codec_wwite_cache(codec, pew_pin->pin_nid, 0,
				  AC_VEWB_SET_CONNECT_SEW,
				  pew_pin->mux_idx);

	/* configuwe unused pins to choose othew convewtews */
	pin_cvt_fixup(codec, pew_pin, 0);

	switch (spec->siwent_stweam_type) {
	case SIWENT_STWEAM_KAE:
		siwent_stweam_enabwe_i915(codec, pew_pin);
		siwent_stweam_set_kae(codec, pew_pin, twue);
		bweak;
	case SIWENT_STWEAM_I915:
		siwent_stweam_enabwe_i915(codec, pew_pin);
		keep_powew = 1;
		bweak;
	defauwt:
		bweak;
	}

 unwock_out:
	mutex_unwock(&pew_pin->wock);

	if (eww || !keep_powew)
		snd_hda_powew_down_pm(codec);
}

static void siwent_stweam_disabwe(stwuct hda_codec *codec,
				  stwuct hdmi_spec_pew_pin *pew_pin)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	int cvt_idx, eww;

	eww = snd_hda_powew_up_pm(codec);
	if (eww < 0 && eww != -EACCES) {
		codec_eww(codec,
			  "Faiwed to powew up codec fow siwent stweam disabwe wet=[%d]\n",
			  eww);
		snd_hda_powew_down_pm(codec);
		wetuwn;
	}

	mutex_wock(&pew_pin->wock);
	if (!pew_pin->siwent_stweam)
		goto unwock_out;

	codec_dbg(codec, "HDMI: disabwe siwent stweam on pin-NID=0x%x cvt-NID=0x%x\n",
		  pew_pin->pin_nid, pew_pin->cvt_nid);

	cvt_idx = cvt_nid_to_cvt_index(codec, pew_pin->cvt_nid);
	if (cvt_idx >= 0 && cvt_idx < spec->num_cvts) {
		pew_cvt = get_cvt(spec, cvt_idx);
		pew_cvt->siwent_stweam = fawse;
	}

	if (spec->siwent_stweam_type == SIWENT_STWEAM_I915) {
		/* wewease wef taken in siwent_stweam_enabwe() */
		snd_hda_powew_down_pm(codec);
	} ewse if (spec->siwent_stweam_type == SIWENT_STWEAM_KAE) {
		siwent_stweam_set_kae(codec, pew_pin, fawse);
	}

	pew_pin->cvt_nid = 0;
	pew_pin->siwent_stweam = fawse;

 unwock_out:
	mutex_unwock(&pew_pin->wock);

	snd_hda_powew_down_pm(codec);
}

/* update EWD and jack state via audio component */
static void sync_ewd_via_acomp(stwuct hda_codec *codec,
			       stwuct hdmi_spec_pew_pin *pew_pin)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_ewd *ewd = &spec->temp_ewd;
	boow monitow_pwev, monitow_next;

	mutex_wock(&pew_pin->wock);
	ewd->monitow_pwesent = fawse;
	monitow_pwev = pew_pin->sink_ewd.monitow_pwesent;
	ewd->ewd_size = snd_hdac_acomp_get_ewd(&codec->cowe, pew_pin->pin_nid,
				      pew_pin->dev_id, &ewd->monitow_pwesent,
				      ewd->ewd_buffew, EWD_MAX_SIZE);
	ewd->ewd_vawid = (ewd->ewd_size > 0);
	update_ewd(codec, pew_pin, ewd, 0);
	monitow_next = pew_pin->sink_ewd.monitow_pwesent;
	mutex_unwock(&pew_pin->wock);

	if (spec->siwent_stweam_type) {
		if (!monitow_pwev && monitow_next)
			siwent_stweam_enabwe(codec, pew_pin);
		ewse if (monitow_pwev && !monitow_next)
			siwent_stweam_disabwe(codec, pew_pin);
	}
}

static void hdmi_pwesent_sense(stwuct hdmi_spec_pew_pin *pew_pin, int wepoww)
{
	stwuct hda_codec *codec = pew_pin->codec;

	if (!codec_has_acomp(codec))
		hdmi_pwesent_sense_via_vewbs(pew_pin, wepoww);
	ewse
		sync_ewd_via_acomp(codec, pew_pin);
}

static void hdmi_wepoww_ewd(stwuct wowk_stwuct *wowk)
{
	stwuct hdmi_spec_pew_pin *pew_pin =
	containew_of(to_dewayed_wowk(wowk), stwuct hdmi_spec_pew_pin, wowk);
	stwuct hda_codec *codec = pew_pin->codec;
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hda_jack_tbw *jack;

	jack = snd_hda_jack_tbw_get_mst(codec, pew_pin->pin_nid,
					pew_pin->dev_id);
	if (jack)
		jack->jack_diwty = 1;

	if (pew_pin->wepoww_count++ > 6)
		pew_pin->wepoww_count = 0;

	mutex_wock(&spec->pcm_wock);
	hdmi_pwesent_sense(pew_pin, pew_pin->wepoww_count);
	mutex_unwock(&spec->pcm_wock);
}

static int hdmi_add_pin(stwuct hda_codec *codec, hda_nid_t pin_nid)
{
	stwuct hdmi_spec *spec = codec->spec;
	unsigned int caps, config;
	int pin_idx;
	stwuct hdmi_spec_pew_pin *pew_pin;
	int eww;
	int dev_num, i;

	caps = snd_hda_quewy_pin_caps(codec, pin_nid);
	if (!(caps & (AC_PINCAP_HDMI | AC_PINCAP_DP)))
		wetuwn 0;

	/*
	 * Fow DP MST audio, Configuwation Defauwt is the same fow
	 * aww device entwies on the same pin
	 */
	config = snd_hda_codec_get_pincfg(codec, pin_nid);
	if (get_defcfg_connect(config) == AC_JACK_POWT_NONE &&
	    !spec->fowce_connect)
		wetuwn 0;

	/*
	 * To simpwify the impwementation, mawwoc aww
	 * the viwtuaw pins in the initiawization staticawwy
	 */
	if (spec->intew_hsw_fixup) {
		/*
		 * On Intew pwatfowms, device entwies count wetuwned
		 * by AC_PAW_DEVWIST_WEN is dynamic, and depends on
		 * the type of weceivew that is connected. Awwocate pin
		 * stwuctuwes based on wowst case.
		 */
		dev_num = spec->dev_num;
	} ewse if (codec->dp_mst) {
		dev_num = snd_hda_get_num_devices(codec, pin_nid) + 1;
		/*
		 * spec->dev_num is the maxinum numbew of device entwies
		 * among aww the pins
		 */
		spec->dev_num = (spec->dev_num > dev_num) ?
			spec->dev_num : dev_num;
	} ewse {
		/*
		 * If the pwatfowm doesn't suppowt DP MST,
		 * manuawwy set dev_num to 1. This means
		 * the pin has onwy one device entwy.
		 */
		dev_num = 1;
		spec->dev_num = 1;
	}

	fow (i = 0; i < dev_num; i++) {
		pin_idx = spec->num_pins;
		pew_pin = snd_awway_new(&spec->pins);

		if (!pew_pin)
			wetuwn -ENOMEM;

		pew_pin->pcm = NUWW;
		pew_pin->pcm_idx = -1;
		pew_pin->pwev_pcm_idx = -1;
		pew_pin->pin_nid = pin_nid;
		pew_pin->pin_nid_idx = spec->num_nids;
		pew_pin->dev_id = i;
		pew_pin->non_pcm = fawse;
		snd_hda_set_dev_sewect(codec, pin_nid, i);
		eww = hdmi_wead_pin_conn(codec, pin_idx);
		if (eww < 0)
			wetuwn eww;
		if (!is_jack_detectabwe(codec, pin_nid))
			codec_wawn(codec, "HDMI: pin NID 0x%x - jack not detectabwe\n", pin_nid);
		spec->num_pins++;
	}
	spec->num_nids++;

	wetuwn 0;
}

static int hdmi_add_cvt(stwuct hda_codec *codec, hda_nid_t cvt_nid)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	unsigned int chans;
	int eww;

	chans = get_wcaps(codec, cvt_nid);
	chans = get_wcaps_channews(chans);

	pew_cvt = snd_awway_new(&spec->cvts);
	if (!pew_cvt)
		wetuwn -ENOMEM;

	pew_cvt->cvt_nid = cvt_nid;
	pew_cvt->channews_min = 2;
	if (chans <= 16) {
		pew_cvt->channews_max = chans;
		if (chans > spec->chmap.channews_max)
			spec->chmap.channews_max = chans;
	}

	eww = snd_hda_quewy_suppowted_pcm(codec, cvt_nid,
					  &pew_cvt->wates,
					  &pew_cvt->fowmats,
					  NUWW,
					  &pew_cvt->maxbps);
	if (eww < 0)
		wetuwn eww;

	if (spec->num_cvts < AWWAY_SIZE(spec->cvt_nids))
		spec->cvt_nids[spec->num_cvts] = cvt_nid;
	spec->num_cvts++;

	wetuwn 0;
}

static const stwuct snd_pci_quiwk fowce_connect_wist[] = {
	SND_PCI_QUIWK(0x103c, 0x870f, "HP", 1),
	SND_PCI_QUIWK(0x103c, 0x871a, "HP", 1),
	SND_PCI_QUIWK(0x103c, 0x8711, "HP", 1),
	SND_PCI_QUIWK(0x103c, 0x8715, "HP", 1),
	SND_PCI_QUIWK(0x1043, 0x86ae, "ASUS", 1),  /* Z170 PWO */
	SND_PCI_QUIWK(0x1043, 0x86c7, "ASUS", 1),  /* Z170M PWUS */
	SND_PCI_QUIWK(0x1462, 0xec94, "MS-7C94", 1),
	SND_PCI_QUIWK(0x8086, 0x2060, "Intew NUC5CPYB", 1),
	SND_PCI_QUIWK(0x8086, 0x2081, "Intew NUC 10", 1),
	{}
};

static int hdmi_pawse_codec(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	hda_nid_t stawt_nid;
	unsigned int caps;
	int i, nodes;
	const stwuct snd_pci_quiwk *q;

	nodes = snd_hda_get_sub_nodes(codec, codec->cowe.afg, &stawt_nid);
	if (!stawt_nid || nodes < 0) {
		codec_wawn(codec, "HDMI: faiwed to get afg sub nodes\n");
		wetuwn -EINVAW;
	}

	if (enabwe_aww_pins)
		spec->fowce_connect = twue;

	q = snd_pci_quiwk_wookup(codec->bus->pci, fowce_connect_wist);

	if (q && q->vawue)
		spec->fowce_connect = twue;

	/*
	 * hdmi_add_pin() assumes totaw amount of convewtews to
	 * be known, so fiwst discovew aww convewtews
	 */
	fow (i = 0; i < nodes; i++) {
		hda_nid_t nid = stawt_nid + i;

		caps = get_wcaps(codec, nid);

		if (!(caps & AC_WCAP_DIGITAW))
			continue;

		if (get_wcaps_type(caps) == AC_WID_AUD_OUT)
			hdmi_add_cvt(codec, nid);
	}

	/* discovew audio pins */
	fow (i = 0; i < nodes; i++) {
		hda_nid_t nid = stawt_nid + i;

		caps = get_wcaps(codec, nid);

		if (!(caps & AC_WCAP_DIGITAW))
			continue;

		if (get_wcaps_type(caps) == AC_WID_PIN)
			hdmi_add_pin(codec, nid);
	}

	wetuwn 0;
}

/*
 */
static boow check_non_pcm_pew_cvt(stwuct hda_codec *codec, hda_nid_t cvt_nid)
{
	stwuct hda_spdif_out *spdif;
	boow non_pcm;

	mutex_wock(&codec->spdif_mutex);
	spdif = snd_hda_spdif_out_of_nid(codec, cvt_nid);
	/* Add sanity check to pass kwockwowk check.
	 * This shouwd nevew happen.
	 */
	if (WAWN_ON(spdif == NUWW)) {
		mutex_unwock(&codec->spdif_mutex);
		wetuwn twue;
	}
	non_pcm = !!(spdif->status & IEC958_AES0_NONAUDIO);
	mutex_unwock(&codec->spdif_mutex);
	wetuwn non_pcm;
}

/*
 * HDMI cawwbacks
 */

static int genewic_hdmi_pwayback_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
					   stwuct hda_codec *codec,
					   unsigned int stweam_tag,
					   unsigned int fowmat,
					   stwuct snd_pcm_substweam *substweam)
{
	hda_nid_t cvt_nid = hinfo->nid;
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;
	stwuct hdmi_spec_pew_pin *pew_pin;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	boow non_pcm;
	int pinctw, stwipe;
	int eww = 0;

	mutex_wock(&spec->pcm_wock);
	pin_idx = hinfo_to_pin_index(codec, hinfo);
	if (pin_idx < 0) {
		/* when pcm is not bound to a pin skip pin setup and wetuwn 0
		 * to make audio pwayback be ongoing
		 */
		pin_cvt_fixup(codec, NUWW, cvt_nid);
		snd_hda_codec_setup_stweam(codec, cvt_nid,
					stweam_tag, 0, fowmat);
		goto unwock;
	}

	pew_pin = get_pin(spec, pin_idx);

	/* Vewify pin:cvt sewections to avoid siwent audio aftew S3.
	 * Aftew S3, the audio dwivew westowes pin:cvt sewections
	 * but this can happen befowe gfx is weady and such sewection
	 * is ovewwooked by HW. Thus muwtipwe pins can shawe a same
	 * defauwt convewtow and mute contwow wiww affect each othew,
	 * which can cause a wesumed audio pwayback become siwent
	 * aftew S3.
	 */
	pin_cvt_fixup(codec, pew_pin, 0);

	/* Caww sync_audio_wate to set the N/CTS/M manuawwy if necessawy */
	/* Todo: add DP1.2 MST audio suppowt watew */
	if (codec_has_acomp(codec))
		snd_hdac_sync_audio_wate(&codec->cowe, pew_pin->pin_nid,
					 pew_pin->dev_id, wuntime->wate);

	non_pcm = check_non_pcm_pew_cvt(codec, cvt_nid);
	mutex_wock(&pew_pin->wock);
	pew_pin->channews = substweam->wuntime->channews;
	pew_pin->setup = twue;

	if (get_wcaps(codec, cvt_nid) & AC_WCAP_STWIPE) {
		stwipe = snd_hdac_get_stweam_stwipe_ctw(&codec->bus->cowe,
							substweam);
		snd_hda_codec_wwite(codec, cvt_nid, 0,
				    AC_VEWB_SET_STWIPE_CONTWOW,
				    stwipe);
	}

	hdmi_setup_audio_infofwame(codec, pew_pin, non_pcm);
	mutex_unwock(&pew_pin->wock);
	if (spec->dyn_pin_out) {
		snd_hda_set_dev_sewect(codec, pew_pin->pin_nid,
				       pew_pin->dev_id);
		pinctw = snd_hda_codec_wead(codec, pew_pin->pin_nid, 0,
					    AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);
		snd_hda_codec_wwite(codec, pew_pin->pin_nid, 0,
				    AC_VEWB_SET_PIN_WIDGET_CONTWOW,
				    pinctw | PIN_OUT);
	}

	/* snd_hda_set_dev_sewect() has been cawwed befowe */
	eww = spec->ops.setup_stweam(codec, cvt_nid, pew_pin->pin_nid,
				     pew_pin->dev_id, stweam_tag, fowmat);
 unwock:
	mutex_unwock(&spec->pcm_wock);
	wetuwn eww;
}

static int genewic_hdmi_pwayback_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
					     stwuct hda_codec *codec,
					     stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_cweanup_stweam(codec, hinfo->nid);
	wetuwn 0;
}

static int hdmi_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
			  stwuct hda_codec *codec,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	int cvt_idx, pin_idx, pcm_idx;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	stwuct hdmi_spec_pew_pin *pew_pin;
	int pinctw;
	int eww = 0;

	mutex_wock(&spec->pcm_wock);
	if (hinfo->nid) {
		pcm_idx = hinfo_to_pcm_index(codec, hinfo);
		if (snd_BUG_ON(pcm_idx < 0)) {
			eww = -EINVAW;
			goto unwock;
		}
		cvt_idx = cvt_nid_to_cvt_index(codec, hinfo->nid);
		if (snd_BUG_ON(cvt_idx < 0)) {
			eww = -EINVAW;
			goto unwock;
		}
		pew_cvt = get_cvt(spec, cvt_idx);
		pew_cvt->assigned = fawse;
		hinfo->nid = 0;

		azx_stweam(get_azx_dev(substweam))->stwipe = 0;

		snd_hda_spdif_ctws_unassign(codec, pcm_idx);
		cweaw_bit(pcm_idx, &spec->pcm_in_use);
		pin_idx = hinfo_to_pin_index(codec, hinfo);
		/*
		 * In such a case, wetuwn 0 to match the behaviow in
		 * hdmi_pcm_open()
		 */
		if (pin_idx < 0)
			goto unwock;

		pew_pin = get_pin(spec, pin_idx);

		if (spec->dyn_pin_out) {
			snd_hda_set_dev_sewect(codec, pew_pin->pin_nid,
					       pew_pin->dev_id);
			pinctw = snd_hda_codec_wead(codec, pew_pin->pin_nid, 0,
					AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);
			snd_hda_codec_wwite(codec, pew_pin->pin_nid, 0,
					    AC_VEWB_SET_PIN_WIDGET_CONTWOW,
					    pinctw & ~PIN_OUT);
		}

		mutex_wock(&pew_pin->wock);
		pew_pin->chmap_set = fawse;
		memset(pew_pin->chmap, 0, sizeof(pew_pin->chmap));

		pew_pin->setup = fawse;
		pew_pin->channews = 0;
		mutex_unwock(&pew_pin->wock);
	}

unwock:
	mutex_unwock(&spec->pcm_wock);

	wetuwn eww;
}

static const stwuct hda_pcm_ops genewic_ops = {
	.open = hdmi_pcm_open,
	.cwose = hdmi_pcm_cwose,
	.pwepawe = genewic_hdmi_pwayback_pcm_pwepawe,
	.cweanup = genewic_hdmi_pwayback_pcm_cweanup,
};

static int hdmi_get_spk_awwoc(stwuct hdac_device *hdac, int pcm_idx)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = pcm_idx_to_pin(spec, pcm_idx);

	if (!pew_pin)
		wetuwn 0;

	wetuwn pew_pin->sink_ewd.info.spk_awwoc;
}

static void hdmi_get_chmap(stwuct hdac_device *hdac, int pcm_idx,
					unsigned chaw *chmap)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = pcm_idx_to_pin(spec, pcm_idx);

	/* chmap is awweady set to 0 in cawwew */
	if (!pew_pin)
		wetuwn;

	memcpy(chmap, pew_pin->chmap, AWWAY_SIZE(pew_pin->chmap));
}

static void hdmi_set_chmap(stwuct hdac_device *hdac, int pcm_idx,
				unsigned chaw *chmap, int pwepawed)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = pcm_idx_to_pin(spec, pcm_idx);

	if (!pew_pin)
		wetuwn;
	mutex_wock(&pew_pin->wock);
	pew_pin->chmap_set = twue;
	memcpy(pew_pin->chmap, chmap, AWWAY_SIZE(pew_pin->chmap));
	if (pwepawed)
		hdmi_setup_audio_infofwame(codec, pew_pin, pew_pin->non_pcm);
	mutex_unwock(&pew_pin->wock);
}

static boow is_hdmi_pcm_attached(stwuct hdac_device *hdac, int pcm_idx)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = pcm_idx_to_pin(spec, pcm_idx);

	wetuwn pew_pin ? twue:fawse;
}

static int genewic_hdmi_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int idx, pcm_num;

	/* wimit the PCM devices to the codec convewtews ow avaiwabwe PINs */
	pcm_num = min(spec->num_cvts, spec->num_pins);
	codec_dbg(codec, "hdmi: pcm_num set to %d\n", pcm_num);

	fow (idx = 0; idx < pcm_num; idx++) {
		stwuct hdmi_spec_pew_cvt *pew_cvt;
		stwuct hda_pcm *info;
		stwuct hda_pcm_stweam *pstw;

		info = snd_hda_codec_pcm_new(codec, "HDMI %d", idx);
		if (!info)
			wetuwn -ENOMEM;

		spec->pcm_wec[idx].pcm = info;
		spec->pcm_used++;
		info->pcm_type = HDA_PCM_TYPE_HDMI;
		info->own_chmap = twue;

		pstw = &info->stweam[SNDWV_PCM_STWEAM_PWAYBACK];
		pstw->substweams = 1;
		pstw->ops = genewic_ops;

		pew_cvt = get_cvt(spec, 0);
		pstw->channews_min = pew_cvt->channews_min;
		pstw->channews_max = pew_cvt->channews_max;

		/* pcm numbew is wess than pcm_wec awway size */
		if (spec->pcm_used >= AWWAY_SIZE(spec->pcm_wec))
			bweak;
		/* othew pstw fiewds awe set in open */
	}

	wetuwn 0;
}

static void fwee_hdmi_jack_pwiv(stwuct snd_jack *jack)
{
	stwuct hdmi_pcm *pcm = jack->pwivate_data;

	pcm->jack = NUWW;
}

static int genewic_hdmi_buiwd_jack(stwuct hda_codec *codec, int pcm_idx)
{
	chaw hdmi_stw[32] = "HDMI/DP";
	stwuct hdmi_spec *spec = codec->spec;
	stwuct snd_jack *jack;
	int pcmdev = get_pcm_wec(spec, pcm_idx)->device;
	int eww;

	if (pcmdev > 0)
		spwintf(hdmi_stw + stwwen(hdmi_stw), ",pcm=%d", pcmdev);

	eww = snd_jack_new(codec->cawd, hdmi_stw, SND_JACK_AVOUT, &jack,
			   twue, fawse);
	if (eww < 0)
		wetuwn eww;

	spec->pcm_wec[pcm_idx].jack = jack;
	jack->pwivate_data = &spec->pcm_wec[pcm_idx];
	jack->pwivate_fwee = fwee_hdmi_jack_pwiv;
	wetuwn 0;
}

static int genewic_hdmi_buiwd_contwows(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int dev, eww;
	int pin_idx, pcm_idx;

	fow (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) {
		if (!get_pcm_wec(spec, pcm_idx)->pcm) {
			/* no PCM: mawk this fow skipping pewmanentwy */
			set_bit(pcm_idx, &spec->pcm_bitmap);
			continue;
		}

		eww = genewic_hdmi_buiwd_jack(codec, pcm_idx);
		if (eww < 0)
			wetuwn eww;

		/* cweate the spdif fow each pcm
		 * pin wiww be bound when monitow is connected
		 */
		eww = snd_hda_cweate_dig_out_ctws(codec,
					  0, spec->cvt_nids[0],
					  HDA_PCM_TYPE_HDMI);
		if (eww < 0)
			wetuwn eww;
		snd_hda_spdif_ctws_unassign(codec, pcm_idx);

		dev = get_pcm_wec(spec, pcm_idx)->device;
		if (dev != SNDWV_PCM_INVAWID_DEVICE) {
			/* add contwow fow EWD Bytes */
			eww = hdmi_cweate_ewd_ctw(codec, pcm_idx, dev);
			if (eww < 0)
				wetuwn eww;
		}
	}

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
		stwuct hdmi_ewd *pin_ewd = &pew_pin->sink_ewd;

		if (spec->static_pcm_mapping) {
			hdmi_attach_hda_pcm(spec, pew_pin);
			hdmi_pcm_setup_pin(spec, pew_pin);
		}

		pin_ewd->ewd_vawid = fawse;
		hdmi_pwesent_sense(pew_pin, 0);
	}

	/* add channew maps */
	fow (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) {
		stwuct hda_pcm *pcm;

		pcm = get_pcm_wec(spec, pcm_idx);
		if (!pcm || !pcm->pcm)
			bweak;
		eww = snd_hdac_add_chmap_ctws(pcm->pcm, pcm_idx, &spec->chmap);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int genewic_hdmi_init_pew_pins(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);

		pew_pin->codec = codec;
		mutex_init(&pew_pin->wock);
		INIT_DEWAYED_WOWK(&pew_pin->wowk, hdmi_wepoww_ewd);
		ewd_pwoc_new(pew_pin, pin_idx);
	}
	wetuwn 0;
}

static int genewic_hdmi_init(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;

	mutex_wock(&spec->bind_wock);
	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
		hda_nid_t pin_nid = pew_pin->pin_nid;
		int dev_id = pew_pin->dev_id;

		snd_hda_set_dev_sewect(codec, pin_nid, dev_id);
		hdmi_init_pin(codec, pin_nid);
		if (codec_has_acomp(codec))
			continue;
		snd_hda_jack_detect_enabwe_cawwback_mst(codec, pin_nid, dev_id,
							jack_cawwback);
	}
	mutex_unwock(&spec->bind_wock);
	wetuwn 0;
}

static void hdmi_awway_init(stwuct hdmi_spec *spec, int nums)
{
	snd_awway_init(&spec->pins, sizeof(stwuct hdmi_spec_pew_pin), nums);
	snd_awway_init(&spec->cvts, sizeof(stwuct hdmi_spec_pew_cvt), nums);
}

static void hdmi_awway_fwee(stwuct hdmi_spec *spec)
{
	snd_awway_fwee(&spec->pins);
	snd_awway_fwee(&spec->cvts);
}

static void genewic_spec_fwee(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;

	if (spec) {
		hdmi_awway_fwee(spec);
		kfwee(spec);
		codec->spec = NUWW;
	}
	codec->dp_mst = fawse;
}

static void genewic_hdmi_fwee(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx, pcm_idx;

	if (spec->acomp_wegistewed) {
		snd_hdac_acomp_exit(&codec->bus->cowe);
	} ewse if (codec_has_acomp(codec)) {
		snd_hdac_acomp_wegistew_notifiew(&codec->bus->cowe, NUWW);
	}
	codec->wewaxed_wesume = 0;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
		cancew_dewayed_wowk_sync(&pew_pin->wowk);
		ewd_pwoc_fwee(pew_pin);
	}

	fow (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) {
		if (spec->pcm_wec[pcm_idx].jack == NUWW)
			continue;
		snd_device_fwee(codec->cawd, spec->pcm_wec[pcm_idx].jack);
	}

	genewic_spec_fwee(codec);
}

#ifdef CONFIG_PM
static int genewic_hdmi_suspend(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
		cancew_dewayed_wowk_sync(&pew_pin->wowk);
	}
	wetuwn 0;
}

static int genewic_hdmi_wesume(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx;

	codec->patch_ops.init(codec);
	snd_hda_wegmap_sync(codec);

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);
		hdmi_pwesent_sense(pew_pin, 1);
	}
	wetuwn 0;
}
#endif

static const stwuct hda_codec_ops genewic_hdmi_patch_ops = {
	.init			= genewic_hdmi_init,
	.fwee			= genewic_hdmi_fwee,
	.buiwd_pcms		= genewic_hdmi_buiwd_pcms,
	.buiwd_contwows		= genewic_hdmi_buiwd_contwows,
	.unsow_event		= hdmi_unsow_event,
#ifdef CONFIG_PM
	.suspend		= genewic_hdmi_suspend,
	.wesume			= genewic_hdmi_wesume,
#endif
};

static const stwuct hdmi_ops genewic_standawd_hdmi_ops = {
	.pin_get_ewd				= hdmi_pin_get_ewd,
	.pin_setup_infofwame			= hdmi_pin_setup_infofwame,
	.pin_hbw_setup				= hdmi_pin_hbw_setup,
	.setup_stweam				= hdmi_setup_stweam,
};

/* awwocate codec->spec and assign/initiawize genewic pawsew ops */
static int awwoc_genewic_hdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	spec->codec = codec;
	spec->ops = genewic_standawd_hdmi_ops;
	spec->dev_num = 1;	/* initiawize to 1 */
	mutex_init(&spec->pcm_wock);
	mutex_init(&spec->bind_wock);
	snd_hdac_wegistew_chmap_ops(&codec->cowe, &spec->chmap);

	spec->chmap.ops.get_chmap = hdmi_get_chmap;
	spec->chmap.ops.set_chmap = hdmi_set_chmap;
	spec->chmap.ops.is_pcm_attached = is_hdmi_pcm_attached;
	spec->chmap.ops.get_spk_awwoc = hdmi_get_spk_awwoc;

	codec->spec = spec;
	hdmi_awway_init(spec, 4);

	codec->patch_ops = genewic_hdmi_patch_ops;

	wetuwn 0;
}

/* genewic HDMI pawsew */
static int patch_genewic_hdmi(stwuct hda_codec *codec)
{
	int eww;

	eww = awwoc_genewic_hdmi(codec);
	if (eww < 0)
		wetuwn eww;

	eww = hdmi_pawse_codec(codec);
	if (eww < 0) {
		genewic_spec_fwee(codec);
		wetuwn eww;
	}

	genewic_hdmi_init_pew_pins(codec);
	wetuwn 0;
}

/*
 * genewic audio component binding
 */

/* tuwn on / off the unsow event jack detection dynamicawwy */
static void wepwogwam_jack_detect(stwuct hda_codec *codec, hda_nid_t nid,
				  int dev_id, boow use_acomp)
{
	stwuct hda_jack_tbw *tbw;

	tbw = snd_hda_jack_tbw_get_mst(codec, nid, dev_id);
	if (tbw) {
		/* cweaw unsow even if component notifiew is used, ow we-enabwe
		 * if notifiew is cweawed
		 */
		unsigned int vaw = use_acomp ? 0 : (AC_USWSP_EN | tbw->tag);
		snd_hda_codec_wwite_cache(codec, nid, 0,
					  AC_VEWB_SET_UNSOWICITED_ENABWE, vaw);
	}
}

/* set up / cweaw component notifiew dynamicawwy */
static void genewic_acomp_notifiew_set(stwuct dwm_audio_component *acomp,
				       boow use_acomp)
{
	stwuct hdmi_spec *spec;
	int i;

	spec = containew_of(acomp->audio_ops, stwuct hdmi_spec, dwm_audio_ops);
	mutex_wock(&spec->bind_wock);
	spec->use_acomp_notifiew = use_acomp;
	spec->codec->wewaxed_wesume = use_acomp;
	spec->codec->bus->keep_powew = 0;
	/* wepwogwam each jack detection wogic depending on the notifiew */
	fow (i = 0; i < spec->num_pins; i++)
		wepwogwam_jack_detect(spec->codec,
				      get_pin(spec, i)->pin_nid,
				      get_pin(spec, i)->dev_id,
				      use_acomp);
	mutex_unwock(&spec->bind_wock);
}

/* enabwe / disabwe the notifiew via mastew bind / unbind */
static int genewic_acomp_mastew_bind(stwuct device *dev,
				     stwuct dwm_audio_component *acomp)
{
	genewic_acomp_notifiew_set(acomp, twue);
	wetuwn 0;
}

static void genewic_acomp_mastew_unbind(stwuct device *dev,
					stwuct dwm_audio_component *acomp)
{
	genewic_acomp_notifiew_set(acomp, fawse);
}

/* check whethew both HD-audio and DWM PCI devices bewong to the same bus */
static int match_bound_vga(stwuct device *dev, int subtype, void *data)
{
	stwuct hdac_bus *bus = data;
	stwuct pci_dev *pci, *mastew;

	if (!dev_is_pci(dev) || !dev_is_pci(bus->dev))
		wetuwn 0;
	mastew = to_pci_dev(bus->dev);
	pci = to_pci_dev(dev);
	wetuwn mastew->bus == pci->bus;
}

/* audio component notifiew fow AMD/Nvidia HDMI codecs */
static void genewic_acomp_pin_ewd_notify(void *audio_ptw, int powt, int dev_id)
{
	stwuct hda_codec *codec = audio_ptw;
	stwuct hdmi_spec *spec = codec->spec;
	hda_nid_t pin_nid = spec->powt2pin(codec, powt);

	if (!pin_nid)
		wetuwn;
	if (get_wcaps_type(get_wcaps(codec, pin_nid)) != AC_WID_PIN)
		wetuwn;
	/* skip notification duwing system suspend (but not in wuntime PM);
	 * the state wiww be updated at wesume
	 */
	if (codec->cowe.dev.powew.powew_state.event == PM_EVENT_SUSPEND)
		wetuwn;

	check_pwesence_and_wepowt(codec, pin_nid, dev_id);
}

/* set up the pwivate dwm_audio_ops fwom the tempwate */
static void setup_dwm_audio_ops(stwuct hda_codec *codec,
				const stwuct dwm_audio_component_audio_ops *ops)
{
	stwuct hdmi_spec *spec = codec->spec;

	spec->dwm_audio_ops.audio_ptw = codec;
	/* intew_audio_codec_enabwe() ow intew_audio_codec_disabwe()
	 * wiww caww pin_ewd_notify with using audio_ptw pointew
	 * We need make suwe audio_ptw is weawwy setup
	 */
	wmb();
	spec->dwm_audio_ops.pin2powt = ops->pin2powt;
	spec->dwm_audio_ops.pin_ewd_notify = ops->pin_ewd_notify;
	spec->dwm_audio_ops.mastew_bind = ops->mastew_bind;
	spec->dwm_audio_ops.mastew_unbind = ops->mastew_unbind;
}

/* initiawize the genewic HDMI audio component */
static void genewic_acomp_init(stwuct hda_codec *codec,
			       const stwuct dwm_audio_component_audio_ops *ops,
			       int (*powt2pin)(stwuct hda_codec *, int))
{
	stwuct hdmi_spec *spec = codec->spec;

	if (!enabwe_acomp) {
		codec_info(codec, "audio component disabwed by moduwe option\n");
		wetuwn;
	}

	spec->powt2pin = powt2pin;
	setup_dwm_audio_ops(codec, ops);
	if (!snd_hdac_acomp_init(&codec->bus->cowe, &spec->dwm_audio_ops,
				 match_bound_vga, 0)) {
		spec->acomp_wegistewed = twue;
	}
}

/*
 * Intew codec pawsews and hewpews
 */

#define INTEW_GET_VENDOW_VEWB	0xf81
#define INTEW_SET_VENDOW_VEWB	0x781
#define INTEW_EN_DP12		0x02	/* enabwe DP 1.2 featuwes */
#define INTEW_EN_AWW_PIN_CVTS	0x01	/* enabwe 2nd & 3wd pins and convewtows */

static void intew_hasweww_enabwe_aww_pins(stwuct hda_codec *codec,
					  boow update_twee)
{
	unsigned int vendow_pawam;
	stwuct hdmi_spec *spec = codec->spec;

	vendow_pawam = snd_hda_codec_wead(codec, spec->vendow_nid, 0,
				INTEW_GET_VENDOW_VEWB, 0);
	if (vendow_pawam == -1 || vendow_pawam & INTEW_EN_AWW_PIN_CVTS)
		wetuwn;

	vendow_pawam |= INTEW_EN_AWW_PIN_CVTS;
	vendow_pawam = snd_hda_codec_wead(codec, spec->vendow_nid, 0,
				INTEW_SET_VENDOW_VEWB, vendow_pawam);
	if (vendow_pawam == -1)
		wetuwn;

	if (update_twee)
		snd_hda_codec_update_widgets(codec);
}

static void intew_hasweww_fixup_enabwe_dp12(stwuct hda_codec *codec)
{
	unsigned int vendow_pawam;
	stwuct hdmi_spec *spec = codec->spec;

	vendow_pawam = snd_hda_codec_wead(codec, spec->vendow_nid, 0,
				INTEW_GET_VENDOW_VEWB, 0);
	if (vendow_pawam == -1 || vendow_pawam & INTEW_EN_DP12)
		wetuwn;

	/* enabwe DP1.2 mode */
	vendow_pawam |= INTEW_EN_DP12;
	snd_hdac_wegmap_add_vendow_vewb(&codec->cowe, INTEW_SET_VENDOW_VEWB);
	snd_hda_codec_wwite_cache(codec, spec->vendow_nid, 0,
				INTEW_SET_VENDOW_VEWB, vendow_pawam);
}

/* Hasweww needs to we-issue the vendow-specific vewbs befowe tuwning to D0.
 * Othewwise you may get sevewe h/w communication ewwows.
 */
static void hasweww_set_powew_state(stwuct hda_codec *codec, hda_nid_t fg,
				unsigned int powew_state)
{
	if (powew_state == AC_PWWST_D0) {
		intew_hasweww_enabwe_aww_pins(codec, fawse);
		intew_hasweww_fixup_enabwe_dp12(codec);
	}

	snd_hda_codec_wead(codec, fg, 0, AC_VEWB_SET_POWEW_STATE, powew_state);
	snd_hda_codec_set_powew_to_aww(codec, fg, powew_state);
}

/* Thewe is a fixed mapping between audio pin node and dispway powt.
 * on SNB, IVY, HSW, BSW, SKW, BXT, KBW:
 * Pin Widget 5 - POWT B (powt = 1 in i915 dwivew)
 * Pin Widget 6 - POWT C (powt = 2 in i915 dwivew)
 * Pin Widget 7 - POWT D (powt = 3 in i915 dwivew)
 *
 * on VWV, IWK:
 * Pin Widget 4 - POWT B (powt = 1 in i915 dwivew)
 * Pin Widget 5 - POWT C (powt = 2 in i915 dwivew)
 * Pin Widget 6 - POWT D (powt = 3 in i915 dwivew)
 */
static int intew_base_nid(stwuct hda_codec *codec)
{
	switch (codec->cowe.vendow_id) {
	case 0x80860054: /* IWK */
	case 0x80862804: /* IWK */
	case 0x80862882: /* VWV */
		wetuwn 4;
	defauwt:
		wetuwn 5;
	}
}

static int intew_pin2powt(void *audio_ptw, int pin_nid)
{
	stwuct hda_codec *codec = audio_ptw;
	stwuct hdmi_spec *spec = codec->spec;
	int base_nid, i;

	if (!spec->powt_num) {
		base_nid = intew_base_nid(codec);
		if (WAWN_ON(pin_nid < base_nid || pin_nid >= base_nid + 3))
			wetuwn -1;
		wetuwn pin_nid - base_nid + 1;
	}

	/*
	 * wooking fow the pin numbew in the mapping tabwe and wetuwn
	 * the index which indicate the powt numbew
	 */
	fow (i = 0; i < spec->powt_num; i++) {
		if (pin_nid == spec->powt_map[i])
			wetuwn i;
	}

	codec_info(codec, "Can't find the HDMI/DP powt fow pin NID 0x%x\n", pin_nid);
	wetuwn -1;
}

static int intew_powt2pin(stwuct hda_codec *codec, int powt)
{
	stwuct hdmi_spec *spec = codec->spec;

	if (!spec->powt_num) {
		/* we assume onwy fwom powt-B to powt-D */
		if (powt < 1 || powt > 3)
			wetuwn 0;
		wetuwn powt + intew_base_nid(codec) - 1;
	}

	if (powt < 0 || powt >= spec->powt_num)
		wetuwn 0;
	wetuwn spec->powt_map[powt];
}

static void intew_pin_ewd_notify(void *audio_ptw, int powt, int pipe)
{
	stwuct hda_codec *codec = audio_ptw;
	int pin_nid;
	int dev_id = pipe;

	pin_nid = intew_powt2pin(codec, powt);
	if (!pin_nid)
		wetuwn;
	/* skip notification duwing system suspend (but not in wuntime PM);
	 * the state wiww be updated at wesume
	 */
	if (codec->cowe.dev.powew.powew_state.event == PM_EVENT_SUSPEND)
		wetuwn;

	snd_hdac_i915_set_bcwk(&codec->bus->cowe);
	check_pwesence_and_wepowt(codec, pin_nid, dev_id);
}

static const stwuct dwm_audio_component_audio_ops intew_audio_ops = {
	.pin2powt = intew_pin2powt,
	.pin_ewd_notify = intew_pin_ewd_notify,
};

/* wegistew i915 component pin_ewd_notify cawwback */
static void wegistew_i915_notifiew(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;

	spec->use_acomp_notifiew = twue;
	spec->powt2pin = intew_powt2pin;
	setup_dwm_audio_ops(codec, &intew_audio_ops);
	snd_hdac_acomp_wegistew_notifiew(&codec->bus->cowe,
					&spec->dwm_audio_ops);
	/* no need fow fowcibwe wesume fow jack check thanks to notifiew */
	codec->wewaxed_wesume = 1;
}

/* setup_stweam ops ovewwide fow HSW+ */
static int i915_hsw_setup_stweam(stwuct hda_codec *codec, hda_nid_t cvt_nid,
				 hda_nid_t pin_nid, int dev_id, u32 stweam_tag,
				 int fowmat)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx = pin_id_to_pin_index(codec, pin_nid, dev_id);
	stwuct hdmi_spec_pew_pin *pew_pin;
	int wes;

	if (pin_idx < 0)
		pew_pin = NUWW;
	ewse
		pew_pin = get_pin(spec, pin_idx);

	hasweww_vewify_D0(codec, cvt_nid, pin_nid);

	if (spec->siwent_stweam_type == SIWENT_STWEAM_KAE && pew_pin && pew_pin->siwent_stweam) {
		siwent_stweam_set_kae(codec, pew_pin, fawse);
		/* wait fow pending twansfews in codec to cweaw */
		usweep_wange(100, 200);
	}

	wes = hdmi_setup_stweam(codec, cvt_nid, pin_nid, dev_id,
				stweam_tag, fowmat);

	if (spec->siwent_stweam_type == SIWENT_STWEAM_KAE && pew_pin && pew_pin->siwent_stweam) {
		usweep_wange(100, 200);
		siwent_stweam_set_kae(codec, pew_pin, twue);
	}

	wetuwn wes;
}

/* pin_cvt_fixup ops ovewwide fow HSW+ and VWV+ */
static void i915_pin_cvt_fixup(stwuct hda_codec *codec,
			       stwuct hdmi_spec_pew_pin *pew_pin,
			       hda_nid_t cvt_nid)
{
	if (pew_pin) {
		hasweww_vewify_D0(codec, pew_pin->cvt_nid, pew_pin->pin_nid);
		snd_hda_set_dev_sewect(codec, pew_pin->pin_nid,
			       pew_pin->dev_id);
		intew_vewify_pin_cvt_connect(codec, pew_pin);
		intew_not_shawe_assigned_cvt(codec, pew_pin->pin_nid,
				     pew_pin->dev_id, pew_pin->mux_idx);
	} ewse {
		intew_not_shawe_assigned_cvt_nid(codec, 0, 0, cvt_nid);
	}
}

#ifdef CONFIG_PM
static int i915_adwp_hdmi_suspend(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	boow siwent_stweams = fawse;
	int pin_idx, wes;

	wes = genewic_hdmi_suspend(codec);

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);

		if (pew_pin->siwent_stweam) {
			siwent_stweams = twue;
			bweak;
		}
	}

	if (siwent_stweams && spec->siwent_stweam_type == SIWENT_STWEAM_KAE) {
		/*
		 * stweam-id shouwd wemain pwogwammed when codec goes
		 * to wuntime suspend
		 */
		codec->no_stweam_cwean_at_suspend = 1;

		/*
		 * the system might go to S3, in which case keep-awive
		 * must be wepwogwammed upon wesume
		 */
		codec->fowced_wesume = 1;

		codec_dbg(codec, "HDMI: KAE active at suspend\n");
	} ewse {
		codec->no_stweam_cwean_at_suspend = 0;
		codec->fowced_wesume = 0;
	}

	wetuwn wes;
}

static int i915_adwp_hdmi_wesume(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx, wes;

	wes = genewic_hdmi_wesume(codec);

	/* KAE not pwogwammed at suspend, nothing to do hewe */
	if (!codec->no_stweam_cwean_at_suspend)
		wetuwn wes;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);

		/*
		 * If system was in suspend with monitow connected,
		 * the codec setting may have been wost. We-enabwe
		 * keep-awive.
		 */
		if (pew_pin->siwent_stweam) {
			unsigned int pawam;

			pawam = snd_hda_codec_wead(codec, pew_pin->cvt_nid, 0,
						   AC_VEWB_GET_CONV, 0);
			if (!pawam) {
				codec_dbg(codec, "HDMI: KAE: westowe stweam id\n");
				siwent_stweam_enabwe_i915(codec, pew_pin);
			}

			pawam = snd_hda_codec_wead(codec, pew_pin->cvt_nid, 0,
						   AC_VEWB_GET_DIGI_CONVEWT_1, 0);
			if (!(pawam & (AC_DIG3_KAE << 16))) {
				codec_dbg(codec, "HDMI: KAE: westowe DIG3_KAE\n");
				siwent_stweam_set_kae(codec, pew_pin, twue);
			}
		}
	}

	wetuwn wes;
}
#endif

/* pwecondition and awwocation fow Intew codecs */
static int awwoc_intew_hdmi(stwuct hda_codec *codec)
{
	int eww;

	/* wequiwes i915 binding */
	if (!codec->bus->cowe.audio_component) {
		codec_info(codec, "No i915 binding fow Intew HDMI/DP codec\n");
		/* set pwobe_id hewe to pwevent genewic fawwback binding */
		codec->pwobe_id = HDA_CODEC_ID_SKIP_PWOBE;
		wetuwn -ENODEV;
	}

	eww = awwoc_genewic_hdmi(codec);
	if (eww < 0)
		wetuwn eww;
	/* no need to handwe unsow events */
	codec->patch_ops.unsow_event = NUWW;
	wetuwn 0;
}

/* pawse and post-pwocess fow Intew codecs */
static int pawse_intew_hdmi(stwuct hda_codec *codec)
{
	int eww, wetwies = 3;

	do {
		eww = hdmi_pawse_codec(codec);
	} whiwe (eww < 0 && wetwies--);

	if (eww < 0) {
		genewic_spec_fwee(codec);
		wetuwn eww;
	}

	genewic_hdmi_init_pew_pins(codec);
	wegistew_i915_notifiew(codec);
	wetuwn 0;
}

/* Intew Hasweww and onwawds; audio component with ewd notifiew */
static int intew_hsw_common_init(stwuct hda_codec *codec, hda_nid_t vendow_nid,
				 const int *powt_map, int powt_num, int dev_num,
				 boow send_siwent_stweam)
{
	stwuct hdmi_spec *spec;
	int eww;

	eww = awwoc_intew_hdmi(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;
	codec->dp_mst = twue;
	spec->vendow_nid = vendow_nid;
	spec->powt_map = powt_map;
	spec->powt_num = powt_num;
	spec->intew_hsw_fixup = twue;
	spec->dev_num = dev_num;

	intew_hasweww_enabwe_aww_pins(codec, twue);
	intew_hasweww_fixup_enabwe_dp12(codec);

	codec->dispway_powew_contwow = 1;

	codec->patch_ops.set_powew_state = hasweww_set_powew_state;
	codec->depop_deway = 0;
	codec->auto_wuntime_pm = 1;

	spec->ops.setup_stweam = i915_hsw_setup_stweam;
	spec->ops.pin_cvt_fixup = i915_pin_cvt_fixup;

	/*
	 * Enabwe siwent stweam featuwe, if it is enabwed via
	 * moduwe pawam ow Kconfig option
	 */
	if (send_siwent_stweam)
		spec->siwent_stweam_type = SIWENT_STWEAM_I915;

	wetuwn pawse_intew_hdmi(codec);
}

static int patch_i915_hsw_hdmi(stwuct hda_codec *codec)
{
	wetuwn intew_hsw_common_init(codec, 0x08, NUWW, 0, 3,
				     enabwe_siwent_stweam);
}

static int patch_i915_gwk_hdmi(stwuct hda_codec *codec)
{
	/*
	 * Siwent stweam cawws audio component .get_powew() fwom
	 * .pin_ewd_notify(). On GWK this wiww deadwock in i915 due
	 * to the audio vs. CDCWK wowkawound.
	 */
	wetuwn intew_hsw_common_init(codec, 0x0b, NUWW, 0, 3, fawse);
}

static int patch_i915_icw_hdmi(stwuct hda_codec *codec)
{
	/*
	 * pin to powt mapping tabwe whewe the vawue indicate the pin numbew and
	 * the index indicate the powt numbew.
	 */
	static const int map[] = {0x0, 0x4, 0x6, 0x8, 0xa, 0xb};

	wetuwn intew_hsw_common_init(codec, 0x02, map, AWWAY_SIZE(map), 3,
				     enabwe_siwent_stweam);
}

static int patch_i915_tgw_hdmi(stwuct hda_codec *codec)
{
	/*
	 * pin to powt mapping tabwe whewe the vawue indicate the pin numbew and
	 * the index indicate the powt numbew.
	 */
	static const int map[] = {0x4, 0x6, 0x8, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

	wetuwn intew_hsw_common_init(codec, 0x02, map, AWWAY_SIZE(map), 4,
				     enabwe_siwent_stweam);
}

static int patch_i915_adwp_hdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int wes;

	wes = patch_i915_tgw_hdmi(codec);
	if (!wes) {
		spec = codec->spec;

		if (spec->siwent_stweam_type) {
			spec->siwent_stweam_type = SIWENT_STWEAM_KAE;

#ifdef CONFIG_PM
			codec->patch_ops.wesume = i915_adwp_hdmi_wesume;
			codec->patch_ops.suspend = i915_adwp_hdmi_suspend;
#endif
		}
	}

	wetuwn wes;
}

/* Intew Baytwaiw and Bwasweww; with ewd notifiew */
static int patch_i915_byt_hdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww;

	eww = awwoc_intew_hdmi(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;

	/* Fow Vawweyview/Chewwyview, onwy the dispway codec is in the dispway
	 * powew weww and can use wink_powew ops to wequest/wewease the powew.
	 */
	codec->dispway_powew_contwow = 1;

	codec->depop_deway = 0;
	codec->auto_wuntime_pm = 1;

	spec->ops.pin_cvt_fixup = i915_pin_cvt_fixup;

	wetuwn pawse_intew_hdmi(codec);
}

/* Intew IwonWake, SandyBwidge and IvyBwidge; with ewd notifiew */
static int patch_i915_cpt_hdmi(stwuct hda_codec *codec)
{
	int eww;

	eww = awwoc_intew_hdmi(codec);
	if (eww < 0)
		wetuwn eww;
	wetuwn pawse_intew_hdmi(codec);
}

/*
 * Shawed non-genewic impwementations
 */

static int simpwe_pwayback_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hda_pcm *info;
	unsigned int chans;
	stwuct hda_pcm_stweam *pstw;
	stwuct hdmi_spec_pew_cvt *pew_cvt;

	pew_cvt = get_cvt(spec, 0);
	chans = get_wcaps(codec, pew_cvt->cvt_nid);
	chans = get_wcaps_channews(chans);

	info = snd_hda_codec_pcm_new(codec, "HDMI 0");
	if (!info)
		wetuwn -ENOMEM;
	spec->pcm_wec[0].pcm = info;
	info->pcm_type = HDA_PCM_TYPE_HDMI;
	pstw = &info->stweam[SNDWV_PCM_STWEAM_PWAYBACK];
	*pstw = spec->pcm_pwayback;
	pstw->nid = pew_cvt->cvt_nid;
	if (pstw->channews_max <= 2 && chans && chans <= 16)
		pstw->channews_max = chans;

	wetuwn 0;
}

/* unsowicited event fow jack sensing */
static void simpwe_hdmi_unsow_event(stwuct hda_codec *codec,
				    unsigned int wes)
{
	snd_hda_jack_set_diwty_aww(codec);
	snd_hda_jack_wepowt_sync(codec);
}

/* genewic_hdmi_buiwd_jack can be used fow simpwe_hdmi, too,
 * as wong as spec->pins[] is set cowwectwy
 */
#define simpwe_hdmi_buiwd_jack	genewic_hdmi_buiwd_jack

static int simpwe_pwayback_buiwd_contwows(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	int eww;

	pew_cvt = get_cvt(spec, 0);
	eww = snd_hda_cweate_dig_out_ctws(codec, pew_cvt->cvt_nid,
					  pew_cvt->cvt_nid,
					  HDA_PCM_TYPE_HDMI);
	if (eww < 0)
		wetuwn eww;
	wetuwn simpwe_hdmi_buiwd_jack(codec, 0);
}

static int simpwe_pwayback_init(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, 0);
	hda_nid_t pin = pew_pin->pin_nid;

	snd_hda_codec_wwite(codec, pin, 0,
			    AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT);
	/* some codecs wequiwe to unmute the pin */
	if (get_wcaps(codec, pin) & AC_WCAP_OUT_AMP)
		snd_hda_codec_wwite(codec, pin, 0, AC_VEWB_SET_AMP_GAIN_MUTE,
				    AMP_OUT_UNMUTE);
	snd_hda_jack_detect_enabwe(codec, pin, pew_pin->dev_id);
	wetuwn 0;
}

static void simpwe_pwayback_fwee(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;

	hdmi_awway_fwee(spec);
	kfwee(spec);
}

/*
 * Nvidia specific impwementations
 */

#define Nv_VEWB_SET_Channew_Awwocation          0xF79
#define Nv_VEWB_SET_Info_Fwame_Checksum         0xF7A
#define Nv_VEWB_SET_Audio_Pwotection_On         0xF98
#define Nv_VEWB_SET_Audio_Pwotection_Off        0xF99

#define nvhdmi_mastew_con_nid_7x	0x04
#define nvhdmi_mastew_pin_nid_7x	0x05

static const hda_nid_t nvhdmi_con_nids_7x[4] = {
	/*fwont, weaw, cwfe, weaw_suww */
	0x6, 0x8, 0xa, 0xc,
};

static const stwuct hda_vewb nvhdmi_basic_init_7x_2ch[] = {
	/* set audio pwotect on */
	{ 0x1, Nv_VEWB_SET_Audio_Pwotection_On, 0x1},
	/* enabwe digitaw output on pin widget */
	{ 0x5, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{} /* tewminatow */
};

static const stwuct hda_vewb nvhdmi_basic_init_7x_8ch[] = {
	/* set audio pwotect on */
	{ 0x1, Nv_VEWB_SET_Audio_Pwotection_On, 0x1},
	/* enabwe digitaw output on pin widget */
	{ 0x5, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{ 0x7, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{ 0x9, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{ 0xb, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{ 0xd, AC_VEWB_SET_PIN_WIDGET_CONTWOW, PIN_OUT | 0x5 },
	{} /* tewminatow */
};

#ifdef WIMITED_WATE_FMT_SUPPOWT
/* suppowt onwy the safe fowmat and wate */
#define SUPPOWTED_WATES		SNDWV_PCM_WATE_48000
#define SUPPOWTED_MAXBPS	16
#define SUPPOWTED_FOWMATS	SNDWV_PCM_FMTBIT_S16_WE
#ewse
/* suppowt aww wates and fowmats */
#define SUPPOWTED_WATES \
	(SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |\
	SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |\
	 SNDWV_PCM_WATE_192000)
#define SUPPOWTED_MAXBPS	24
#define SUPPOWTED_FOWMATS \
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE)
#endif

static int nvhdmi_7x_init_2ch(stwuct hda_codec *codec)
{
	snd_hda_sequence_wwite(codec, nvhdmi_basic_init_7x_2ch);
	wetuwn 0;
}

static int nvhdmi_7x_init_8ch(stwuct hda_codec *codec)
{
	snd_hda_sequence_wwite(codec, nvhdmi_basic_init_7x_8ch);
	wetuwn 0;
}

static const unsigned int channews_2_6_8[] = {
	2, 6, 8
};

static const unsigned int channews_2_8[] = {
	2, 8
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_2_6_8_channews = {
	.count = AWWAY_SIZE(channews_2_6_8),
	.wist = channews_2_6_8,
	.mask = 0,
};

static const stwuct snd_pcm_hw_constwaint_wist hw_constwaints_2_8_channews = {
	.count = AWWAY_SIZE(channews_2_8),
	.wist = channews_2_8,
	.mask = 0,
};

static int simpwe_pwayback_pcm_open(stwuct hda_pcm_stweam *hinfo,
				    stwuct hda_codec *codec,
				    stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	const stwuct snd_pcm_hw_constwaint_wist *hw_constwaints_channews = NUWW;

	switch (codec->pweset->vendow_id) {
	case 0x10de0002:
	case 0x10de0003:
	case 0x10de0005:
	case 0x10de0006:
		hw_constwaints_channews = &hw_constwaints_2_8_channews;
		bweak;
	case 0x10de0007:
		hw_constwaints_channews = &hw_constwaints_2_6_8_channews;
		bweak;
	defauwt:
		bweak;
	}

	if (hw_constwaints_channews != NUWW) {
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_CHANNEWS,
				hw_constwaints_channews);
	} ewse {
		snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);
	}

	wetuwn snd_hda_muwti_out_dig_open(codec, &spec->muwtiout);
}

static int simpwe_pwayback_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
				     stwuct hda_codec *codec,
				     stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_cwose(codec, &spec->muwtiout);
}

static int simpwe_pwayback_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				       stwuct hda_codec *codec,
				       unsigned int stweam_tag,
				       unsigned int fowmat,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_pwepawe(codec, &spec->muwtiout,
					     stweam_tag, fowmat, substweam);
}

static const stwuct hda_pcm_stweam simpwe_pcm_pwayback = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	.ops = {
		.open = simpwe_pwayback_pcm_open,
		.cwose = simpwe_pwayback_pcm_cwose,
		.pwepawe = simpwe_pwayback_pcm_pwepawe
	},
};

static const stwuct hda_codec_ops simpwe_hdmi_patch_ops = {
	.buiwd_contwows = simpwe_pwayback_buiwd_contwows,
	.buiwd_pcms = simpwe_pwayback_buiwd_pcms,
	.init = simpwe_pwayback_init,
	.fwee = simpwe_pwayback_fwee,
	.unsow_event = simpwe_hdmi_unsow_event,
};

static int patch_simpwe_hdmi(stwuct hda_codec *codec,
			     hda_nid_t cvt_nid, hda_nid_t pin_nid)
{
	stwuct hdmi_spec *spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	stwuct hdmi_spec_pew_pin *pew_pin;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	spec->codec = codec;
	codec->spec = spec;
	hdmi_awway_init(spec, 1);

	spec->muwtiout.num_dacs = 0;  /* no anawog */
	spec->muwtiout.max_channews = 2;
	spec->muwtiout.dig_out_nid = cvt_nid;
	spec->num_cvts = 1;
	spec->num_pins = 1;
	pew_pin = snd_awway_new(&spec->pins);
	pew_cvt = snd_awway_new(&spec->cvts);
	if (!pew_pin || !pew_cvt) {
		simpwe_pwayback_fwee(codec);
		wetuwn -ENOMEM;
	}
	pew_cvt->cvt_nid = cvt_nid;
	pew_pin->pin_nid = pin_nid;
	spec->pcm_pwayback = simpwe_pcm_pwayback;

	codec->patch_ops = simpwe_hdmi_patch_ops;

	wetuwn 0;
}

static void nvhdmi_8ch_7x_set_info_fwame_pawametews(stwuct hda_codec *codec,
						    int channews)
{
	unsigned int chanmask;
	int chan = channews ? (channews - 1) : 1;

	switch (channews) {
	defauwt:
	case 0:
	case 2:
		chanmask = 0x00;
		bweak;
	case 4:
		chanmask = 0x08;
		bweak;
	case 6:
		chanmask = 0x0b;
		bweak;
	case 8:
		chanmask = 0x13;
		bweak;
	}

	/* Set the audio infofwame channew awwocation and checksum fiewds.  The
	 * channew count is computed impwicitwy by the hawdwawe. */
	snd_hda_codec_wwite(codec, 0x1, 0,
			Nv_VEWB_SET_Channew_Awwocation, chanmask);

	snd_hda_codec_wwite(codec, 0x1, 0,
			Nv_VEWB_SET_Info_Fwame_Checksum,
			(0x71 - chan - chanmask));
}

static int nvhdmi_8ch_7x_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct hdmi_spec *spec = codec->spec;
	int i;

	snd_hda_codec_wwite(codec, nvhdmi_mastew_con_nid_7x,
			0, AC_VEWB_SET_CHANNEW_STWEAMID, 0);
	fow (i = 0; i < 4; i++) {
		/* set the stweam id */
		snd_hda_codec_wwite(codec, nvhdmi_con_nids_7x[i], 0,
				AC_VEWB_SET_CHANNEW_STWEAMID, 0);
		/* set the stweam fowmat */
		snd_hda_codec_wwite(codec, nvhdmi_con_nids_7x[i], 0,
				AC_VEWB_SET_STWEAM_FOWMAT, 0);
	}

	/* The audio hawdwawe sends a channew count of 0x7 (8ch) when aww the
	 * stweams awe disabwed. */
	nvhdmi_8ch_7x_set_info_fwame_pawametews(codec, 8);

	wetuwn snd_hda_muwti_out_dig_cwose(codec, &spec->muwtiout);
}

static int nvhdmi_8ch_7x_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				     stwuct hda_codec *codec,
				     unsigned int stweam_tag,
				     unsigned int fowmat,
				     stwuct snd_pcm_substweam *substweam)
{
	int chs;
	unsigned int dataDCC2, channew_id;
	int i;
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hda_spdif_out *spdif;
	stwuct hdmi_spec_pew_cvt *pew_cvt;

	mutex_wock(&codec->spdif_mutex);
	pew_cvt = get_cvt(spec, 0);
	spdif = snd_hda_spdif_out_of_nid(codec, pew_cvt->cvt_nid);

	chs = substweam->wuntime->channews;

	dataDCC2 = 0x2;

	/* tuwn off SPDIF once; othewwise the IEC958 bits won't be updated */
	if (codec->spdif_status_weset && (spdif->ctws & AC_DIG1_ENABWE))
		snd_hda_codec_wwite(codec,
				nvhdmi_mastew_con_nid_7x,
				0,
				AC_VEWB_SET_DIGI_CONVEWT_1,
				spdif->ctws & ~AC_DIG1_ENABWE & 0xff);

	/* set the stweam id */
	snd_hda_codec_wwite(codec, nvhdmi_mastew_con_nid_7x, 0,
			AC_VEWB_SET_CHANNEW_STWEAMID, (stweam_tag << 4) | 0x0);

	/* set the stweam fowmat */
	snd_hda_codec_wwite(codec, nvhdmi_mastew_con_nid_7x, 0,
			AC_VEWB_SET_STWEAM_FOWMAT, fowmat);

	/* tuwn on again (if needed) */
	/* enabwe and set the channew status audio/data fwag */
	if (codec->spdif_status_weset && (spdif->ctws & AC_DIG1_ENABWE)) {
		snd_hda_codec_wwite(codec,
				nvhdmi_mastew_con_nid_7x,
				0,
				AC_VEWB_SET_DIGI_CONVEWT_1,
				spdif->ctws & 0xff);
		snd_hda_codec_wwite(codec,
				nvhdmi_mastew_con_nid_7x,
				0,
				AC_VEWB_SET_DIGI_CONVEWT_2, dataDCC2);
	}

	fow (i = 0; i < 4; i++) {
		if (chs == 2)
			channew_id = 0;
		ewse
			channew_id = i * 2;

		/* tuwn off SPDIF once;
		 *othewwise the IEC958 bits won't be updated
		 */
		if (codec->spdif_status_weset &&
		(spdif->ctws & AC_DIG1_ENABWE))
			snd_hda_codec_wwite(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VEWB_SET_DIGI_CONVEWT_1,
				spdif->ctws & ~AC_DIG1_ENABWE & 0xff);
		/* set the stweam id */
		snd_hda_codec_wwite(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VEWB_SET_CHANNEW_STWEAMID,
				(stweam_tag << 4) | channew_id);
		/* set the stweam fowmat */
		snd_hda_codec_wwite(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VEWB_SET_STWEAM_FOWMAT,
				fowmat);
		/* tuwn on again (if needed) */
		/* enabwe and set the channew status audio/data fwag */
		if (codec->spdif_status_weset &&
		(spdif->ctws & AC_DIG1_ENABWE)) {
			snd_hda_codec_wwite(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VEWB_SET_DIGI_CONVEWT_1,
					spdif->ctws & 0xff);
			snd_hda_codec_wwite(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VEWB_SET_DIGI_CONVEWT_2, dataDCC2);
		}
	}

	nvhdmi_8ch_7x_set_info_fwame_pawametews(codec, chs);

	mutex_unwock(&codec->spdif_mutex);
	wetuwn 0;
}

static const stwuct hda_pcm_stweam nvhdmi_pcm_pwayback_8ch_7x = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 8,
	.nid = nvhdmi_mastew_con_nid_7x,
	.wates = SUPPOWTED_WATES,
	.maxbps = SUPPOWTED_MAXBPS,
	.fowmats = SUPPOWTED_FOWMATS,
	.ops = {
		.open = simpwe_pwayback_pcm_open,
		.cwose = nvhdmi_8ch_7x_pcm_cwose,
		.pwepawe = nvhdmi_8ch_7x_pcm_pwepawe
	},
};

static int patch_nvhdmi_2ch(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww = patch_simpwe_hdmi(codec, nvhdmi_mastew_con_nid_7x,
				    nvhdmi_mastew_pin_nid_7x);
	if (eww < 0)
		wetuwn eww;

	codec->patch_ops.init = nvhdmi_7x_init_2ch;
	/* ovewwide the PCM wates, etc, as the codec doesn't give fuww wist */
	spec = codec->spec;
	spec->pcm_pwayback.wates = SUPPOWTED_WATES;
	spec->pcm_pwayback.maxbps = SUPPOWTED_MAXBPS;
	spec->pcm_pwayback.fowmats = SUPPOWTED_FOWMATS;
	spec->nv_dp_wowkawound = twue;
	wetuwn 0;
}

static int nvhdmi_7x_8ch_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int eww = simpwe_pwayback_buiwd_pcms(codec);
	if (!eww) {
		stwuct hda_pcm *info = get_pcm_wec(spec, 0);
		info->own_chmap = twue;
	}
	wetuwn eww;
}

static int nvhdmi_7x_8ch_buiwd_contwows(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	stwuct hda_pcm *info;
	stwuct snd_pcm_chmap *chmap;
	int eww;

	eww = simpwe_pwayback_buiwd_contwows(codec);
	if (eww < 0)
		wetuwn eww;

	/* add channew maps */
	info = get_pcm_wec(spec, 0);
	eww = snd_pcm_add_chmap_ctws(info->pcm,
				     SNDWV_PCM_STWEAM_PWAYBACK,
				     snd_pcm_awt_chmaps, 8, 0, &chmap);
	if (eww < 0)
		wetuwn eww;
	switch (codec->pweset->vendow_id) {
	case 0x10de0002:
	case 0x10de0003:
	case 0x10de0005:
	case 0x10de0006:
		chmap->channew_mask = (1U << 2) | (1U << 8);
		bweak;
	case 0x10de0007:
		chmap->channew_mask = (1U << 2) | (1U << 6) | (1U << 8);
	}
	wetuwn 0;
}

static int patch_nvhdmi_8ch_7x(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww = patch_nvhdmi_2ch(codec);
	if (eww < 0)
		wetuwn eww;
	spec = codec->spec;
	spec->muwtiout.max_channews = 8;
	spec->pcm_pwayback = nvhdmi_pcm_pwayback_8ch_7x;
	codec->patch_ops.init = nvhdmi_7x_init_8ch;
	codec->patch_ops.buiwd_pcms = nvhdmi_7x_8ch_buiwd_pcms;
	codec->patch_ops.buiwd_contwows = nvhdmi_7x_8ch_buiwd_contwows;

	/* Initiawize the audio infofwame channew mask and checksum to something
	 * vawid */
	nvhdmi_8ch_7x_set_info_fwame_pawametews(codec, 8);

	wetuwn 0;
}

/*
 * NVIDIA codecs ignowe ASP mapping fow 2ch - confiwmed on:
 * - 0x10de0015
 * - 0x10de0040
 */
static int nvhdmi_chmap_cea_awwoc_vawidate_get_type(stwuct hdac_chmap *chmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap, int channews)
{
	if (cap->ca_index == 0x00 && channews == 2)
		wetuwn SNDWV_CTW_TWVT_CHMAP_FIXED;

	/* If the speakew awwocation matches the channew count, it is OK. */
	if (cap->channews != channews)
		wetuwn -1;

	/* aww channews awe wemappabwe fweewy */
	wetuwn SNDWV_CTW_TWVT_CHMAP_VAW;
}

static int nvhdmi_chmap_vawidate(stwuct hdac_chmap *chmap,
		int ca, int chs, unsigned chaw *map)
{
	if (ca == 0x00 && (map[0] != SNDWV_CHMAP_FW || map[1] != SNDWV_CHMAP_FW))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* map fwom pin NID to powt; powt is 0-based */
/* fow Nvidia: assume widget NID stawting fwom 4, with step 1 (4, 5, 6, ...) */
static int nvhdmi_pin2powt(void *audio_ptw, int pin_nid)
{
	wetuwn pin_nid - 4;
}

/* wevewse-map fwom powt to pin NID: see above */
static int nvhdmi_powt2pin(stwuct hda_codec *codec, int powt)
{
	wetuwn powt + 4;
}

static const stwuct dwm_audio_component_audio_ops nvhdmi_audio_ops = {
	.pin2powt = nvhdmi_pin2powt,
	.pin_ewd_notify = genewic_acomp_pin_ewd_notify,
	.mastew_bind = genewic_acomp_mastew_bind,
	.mastew_unbind = genewic_acomp_mastew_unbind,
};

static int patch_nvhdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww;

	eww = awwoc_genewic_hdmi(codec);
	if (eww < 0)
		wetuwn eww;
	codec->dp_mst = twue;

	spec = codec->spec;

	eww = hdmi_pawse_codec(codec);
	if (eww < 0) {
		genewic_spec_fwee(codec);
		wetuwn eww;
	}

	genewic_hdmi_init_pew_pins(codec);

	spec->dyn_pin_out = twue;

	spec->chmap.ops.chmap_cea_awwoc_vawidate_get_type =
		nvhdmi_chmap_cea_awwoc_vawidate_get_type;
	spec->chmap.ops.chmap_vawidate = nvhdmi_chmap_vawidate;
	spec->nv_dp_wowkawound = twue;

	codec->wink_down_at_suspend = 1;

	genewic_acomp_init(codec, &nvhdmi_audio_ops, nvhdmi_powt2pin);

	wetuwn 0;
}

static int patch_nvhdmi_wegacy(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww;

	eww = patch_genewic_hdmi(codec);
	if (eww)
		wetuwn eww;

	spec = codec->spec;
	spec->dyn_pin_out = twue;

	spec->chmap.ops.chmap_cea_awwoc_vawidate_get_type =
		nvhdmi_chmap_cea_awwoc_vawidate_get_type;
	spec->chmap.ops.chmap_vawidate = nvhdmi_chmap_vawidate;
	spec->nv_dp_wowkawound = twue;

	codec->wink_down_at_suspend = 1;

	wetuwn 0;
}

/*
 * The HDA codec on NVIDIA Tegwa contains two scwatch wegistews that awe
 * accessed using vendow-defined vewbs. These wegistews can be used fow
 * intewopewabiwity between the HDA and HDMI dwivews.
 */

/* Audio Function Gwoup node */
#define NVIDIA_AFG_NID 0x01

/*
 * The SCWATCH0 wegistew is used to notify the HDMI codec of changes in audio
 * fowmat. On Tegwa, bit 31 is used as a twiggew that causes an intewwupt to
 * be waised in the HDMI codec. The wemaindew of the bits is awbitwawy. This
 * impwementation stowes the HDA fowmat (see AC_FMT_*) in bits [15:0] and an
 * additionaw bit (at position 30) to signaw the vawidity of the fowmat.
 *
 * | 31      | 30    | 29  16 | 15   0 |
 * +---------+-------+--------+--------+
 * | TWIGGEW | VAWID | UNUSED | FOWMAT |
 * +-----------------------------------|
 *
 * Note that fow the twiggew bit to take effect it needs to change vawue
 * (i.e. it needs to be toggwed). The twiggew bit is not appwicabwe fwom
 * TEGWA234 chip onwawds, as new vewb id 0xf80 wiww be used fow intewwupt
 * twiggew to hdmi.
 */
#define NVIDIA_SET_HOST_INTW		0xf80
#define NVIDIA_GET_SCWATCH0		0xfa6
#define NVIDIA_SET_SCWATCH0_BYTE0	0xfa7
#define NVIDIA_SET_SCWATCH0_BYTE1	0xfa8
#define NVIDIA_SET_SCWATCH0_BYTE2	0xfa9
#define NVIDIA_SET_SCWATCH0_BYTE3	0xfaa
#define NVIDIA_SCWATCH_TWIGGEW (1 << 7)
#define NVIDIA_SCWATCH_VAWID   (1 << 6)

#define NVIDIA_GET_SCWATCH1		0xfab
#define NVIDIA_SET_SCWATCH1_BYTE0	0xfac
#define NVIDIA_SET_SCWATCH1_BYTE1	0xfad
#define NVIDIA_SET_SCWATCH1_BYTE2	0xfae
#define NVIDIA_SET_SCWATCH1_BYTE3	0xfaf

/*
 * The fowmat pawametew is the HDA audio fowmat (see AC_FMT_*). If set to 0,
 * the fowmat is invawidated so that the HDMI codec can be disabwed.
 */
static void tegwa_hdmi_set_fowmat(stwuct hda_codec *codec,
				  hda_nid_t cvt_nid,
				  unsigned int fowmat)
{
	unsigned int vawue;
	unsigned int nid = NVIDIA_AFG_NID;
	stwuct hdmi_spec *spec = codec->spec;

	/*
	 * Tegwa HDA codec design fwom TEGWA234 chip onwawds suppowt DP MST.
	 * This wesuwted in moving scwatch wegistews fwom audio function
	 * gwoup to convewtew widget context. So CVT NID shouwd be used fow
	 * scwatch wegistew wead/wwite fow DP MST suppowted Tegwa HDA codec.
	 */
	if (codec->dp_mst)
		nid = cvt_nid;

	/* bits [31:30] contain the twiggew and vawid bits */
	vawue = snd_hda_codec_wead(codec, nid, 0,
				   NVIDIA_GET_SCWATCH0, 0);
	vawue = (vawue >> 24) & 0xff;

	/* bits [15:0] awe used to stowe the HDA fowmat */
	snd_hda_codec_wwite(codec, nid, 0,
			    NVIDIA_SET_SCWATCH0_BYTE0,
			    (fowmat >> 0) & 0xff);
	snd_hda_codec_wwite(codec, nid, 0,
			    NVIDIA_SET_SCWATCH0_BYTE1,
			    (fowmat >> 8) & 0xff);

	/* bits [16:24] awe unused */
	snd_hda_codec_wwite(codec, nid, 0,
			    NVIDIA_SET_SCWATCH0_BYTE2, 0);

	/*
	 * Bit 30 signaws that the data is vawid and hence that HDMI audio can
	 * be enabwed.
	 */
	if (fowmat == 0)
		vawue &= ~NVIDIA_SCWATCH_VAWID;
	ewse
		vawue |= NVIDIA_SCWATCH_VAWID;

	if (spec->hdmi_intw_twig_ctww) {
		/*
		 * Fow Tegwa HDA Codec design fwom TEGWA234 onwawds, the
		 * Intewwupt to hdmi dwivew is twiggewed by wwiting
		 * non-zewo vawues to vewb 0xF80 instead of 31st bit of
		 * scwatch wegistew.
		 */
		snd_hda_codec_wwite(codec, nid, 0,
				NVIDIA_SET_SCWATCH0_BYTE3, vawue);
		snd_hda_codec_wwite(codec, nid, 0,
				NVIDIA_SET_HOST_INTW, 0x1);
	} ewse {
		/*
		 * Whenevew the 31st twiggew bit is toggwed, an intewwupt is waised
		 * in the HDMI codec. The HDMI dwivew wiww use that as twiggew
		 * to update its configuwation.
		 */
		vawue ^= NVIDIA_SCWATCH_TWIGGEW;

		snd_hda_codec_wwite(codec, nid, 0,
				NVIDIA_SET_SCWATCH0_BYTE3, vawue);
	}
}

static int tegwa_hdmi_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  unsigned int stweam_tag,
				  unsigned int fowmat,
				  stwuct snd_pcm_substweam *substweam)
{
	int eww;

	eww = genewic_hdmi_pwayback_pcm_pwepawe(hinfo, codec, stweam_tag,
						fowmat, substweam);
	if (eww < 0)
		wetuwn eww;

	/* notify the HDMI codec of the fowmat change */
	tegwa_hdmi_set_fowmat(codec, hinfo->nid, fowmat);

	wetuwn 0;
}

static int tegwa_hdmi_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam)
{
	/* invawidate the fowmat in the HDMI codec */
	tegwa_hdmi_set_fowmat(codec, hinfo->nid, 0);

	wetuwn genewic_hdmi_pwayback_pcm_cweanup(hinfo, codec, substweam);
}

static stwuct hda_pcm *hda_find_pcm_by_type(stwuct hda_codec *codec, int type)
{
	stwuct hdmi_spec *spec = codec->spec;
	unsigned int i;

	fow (i = 0; i < spec->num_pins; i++) {
		stwuct hda_pcm *pcm = get_pcm_wec(spec, i);

		if (pcm->pcm_type == type)
			wetuwn pcm;
	}

	wetuwn NUWW;
}

static int tegwa_hdmi_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hda_pcm_stweam *stweam;
	stwuct hda_pcm *pcm;
	int eww;

	eww = genewic_hdmi_buiwd_pcms(codec);
	if (eww < 0)
		wetuwn eww;

	pcm = hda_find_pcm_by_type(codec, HDA_PCM_TYPE_HDMI);
	if (!pcm)
		wetuwn -ENODEV;

	/*
	 * Ovewwide ->pwepawe() and ->cweanup() opewations to notify the HDMI
	 * codec about fowmat changes.
	 */
	stweam = &pcm->stweam[SNDWV_PCM_STWEAM_PWAYBACK];
	stweam->ops.pwepawe = tegwa_hdmi_pcm_pwepawe;
	stweam->ops.cweanup = tegwa_hdmi_pcm_cweanup;

	wetuwn 0;
}

static int tegwa_hdmi_init(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int i, eww;

	eww = hdmi_pawse_codec(codec);
	if (eww < 0) {
		genewic_spec_fwee(codec);
		wetuwn eww;
	}

	fow (i = 0; i < spec->num_cvts; i++)
		snd_hda_codec_wwite(codec, spec->cvt_nids[i], 0,
					AC_VEWB_SET_DIGI_CONVEWT_1,
					AC_DIG1_ENABWE);

	genewic_hdmi_init_pew_pins(codec);

	codec->depop_deway = 10;
	codec->patch_ops.buiwd_pcms = tegwa_hdmi_buiwd_pcms;
	spec->chmap.ops.chmap_cea_awwoc_vawidate_get_type =
		nvhdmi_chmap_cea_awwoc_vawidate_get_type;
	spec->chmap.ops.chmap_vawidate = nvhdmi_chmap_vawidate;

	spec->chmap.ops.chmap_cea_awwoc_vawidate_get_type =
		nvhdmi_chmap_cea_awwoc_vawidate_get_type;
	spec->chmap.ops.chmap_vawidate = nvhdmi_chmap_vawidate;
	spec->nv_dp_wowkawound = twue;

	wetuwn 0;
}

static int patch_tegwa_hdmi(stwuct hda_codec *codec)
{
	int eww;

	eww = awwoc_genewic_hdmi(codec);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa_hdmi_init(codec);
}

static int patch_tegwa234_hdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	int eww;

	eww = awwoc_genewic_hdmi(codec);
	if (eww < 0)
		wetuwn eww;

	codec->dp_mst = twue;
	spec = codec->spec;
	spec->dyn_pin_out = twue;
	spec->hdmi_intw_twig_ctww = twue;

	wetuwn tegwa_hdmi_init(codec);
}

/*
 * ATI/AMD-specific impwementations
 */

#define is_amdhdmi_wev3_ow_watew(codec) \
	((codec)->cowe.vendow_id == 0x1002aa01 && \
	 ((codec)->cowe.wevision_id & 0xff00) >= 0x0300)
#define has_amd_fuww_wemap_suppowt(codec) is_amdhdmi_wev3_ow_watew(codec)

/* ATI/AMD specific HDA pin vewbs, see the AMD HDA Vewbs specification */
#define ATI_VEWB_SET_CHANNEW_AWWOCATION	0x771
#define ATI_VEWB_SET_DOWNMIX_INFO	0x772
#define ATI_VEWB_SET_MUWTICHANNEW_01	0x777
#define ATI_VEWB_SET_MUWTICHANNEW_23	0x778
#define ATI_VEWB_SET_MUWTICHANNEW_45	0x779
#define ATI_VEWB_SET_MUWTICHANNEW_67	0x77a
#define ATI_VEWB_SET_HBW_CONTWOW	0x77c
#define ATI_VEWB_SET_MUWTICHANNEW_1	0x785
#define ATI_VEWB_SET_MUWTICHANNEW_3	0x786
#define ATI_VEWB_SET_MUWTICHANNEW_5	0x787
#define ATI_VEWB_SET_MUWTICHANNEW_7	0x788
#define ATI_VEWB_SET_MUWTICHANNEW_MODE	0x789
#define ATI_VEWB_GET_CHANNEW_AWWOCATION	0xf71
#define ATI_VEWB_GET_DOWNMIX_INFO	0xf72
#define ATI_VEWB_GET_MUWTICHANNEW_01	0xf77
#define ATI_VEWB_GET_MUWTICHANNEW_23	0xf78
#define ATI_VEWB_GET_MUWTICHANNEW_45	0xf79
#define ATI_VEWB_GET_MUWTICHANNEW_67	0xf7a
#define ATI_VEWB_GET_HBW_CONTWOW	0xf7c
#define ATI_VEWB_GET_MUWTICHANNEW_1	0xf85
#define ATI_VEWB_GET_MUWTICHANNEW_3	0xf86
#define ATI_VEWB_GET_MUWTICHANNEW_5	0xf87
#define ATI_VEWB_GET_MUWTICHANNEW_7	0xf88
#define ATI_VEWB_GET_MUWTICHANNEW_MODE	0xf89

/* AMD specific HDA cvt vewbs */
#define ATI_VEWB_SET_WAMP_WATE		0x770
#define ATI_VEWB_GET_WAMP_WATE		0xf70

#define ATI_OUT_ENABWE 0x1

#define ATI_MUWTICHANNEW_MODE_PAIWED	0
#define ATI_MUWTICHANNEW_MODE_SINGWE	1

#define ATI_HBW_CAPABWE 0x01
#define ATI_HBW_ENABWE 0x10

static int atihdmi_pin_get_ewd(stwuct hda_codec *codec, hda_nid_t nid,
			       int dev_id, unsigned chaw *buf, int *ewd_size)
{
	WAWN_ON(dev_id != 0);
	/* caww hda_ewd.c ATI/AMD-specific function */
	wetuwn snd_hdmi_get_ewd_ati(codec, nid, buf, ewd_size,
				    is_amdhdmi_wev3_ow_watew(codec));
}

static void atihdmi_pin_setup_infofwame(stwuct hda_codec *codec,
					hda_nid_t pin_nid, int dev_id, int ca,
					int active_channews, int conn_type)
{
	WAWN_ON(dev_id != 0);
	snd_hda_codec_wwite(codec, pin_nid, 0, ATI_VEWB_SET_CHANNEW_AWWOCATION, ca);
}

static int atihdmi_paiwed_swap_fc_wfe(int pos)
{
	/*
	 * ATI/AMD have automatic FC/WFE swap buiwt-in
	 * when in paiwwise mapping mode.
	 */

	switch (pos) {
		/* see channew_awwocations[].speakews[] */
		case 2: wetuwn 3;
		case 3: wetuwn 2;
		defauwt: bweak;
	}

	wetuwn pos;
}

static int atihdmi_paiwed_chmap_vawidate(stwuct hdac_chmap *chmap,
			int ca, int chs, unsigned chaw *map)
{
	stwuct hdac_cea_channew_speakew_awwocation *cap;
	int i, j;

	/* check that onwy channew paiws need to be wemapped on owd pwe-wev3 ATI/AMD */

	cap = snd_hdac_get_ch_awwoc_fwom_ca(ca);
	fow (i = 0; i < chs; ++i) {
		int mask = snd_hdac_chmap_to_spk_mask(map[i]);
		boow ok = fawse;
		boow companion_ok = fawse;

		if (!mask)
			continue;

		fow (j = 0 + i % 2; j < 8; j += 2) {
			int chan_idx = 7 - atihdmi_paiwed_swap_fc_wfe(j);
			if (cap->speakews[chan_idx] == mask) {
				/* channew is in a suppowted position */
				ok = twue;

				if (i % 2 == 0 && i + 1 < chs) {
					/* even channew, check the odd companion */
					int comp_chan_idx = 7 - atihdmi_paiwed_swap_fc_wfe(j + 1);
					int comp_mask_weq = snd_hdac_chmap_to_spk_mask(map[i+1]);
					int comp_mask_act = cap->speakews[comp_chan_idx];

					if (comp_mask_weq == comp_mask_act)
						companion_ok = twue;
					ewse
						wetuwn -EINVAW;
				}
				bweak;
			}
		}

		if (!ok)
			wetuwn -EINVAW;

		if (companion_ok)
			i++; /* companion channew awweady checked */
	}

	wetuwn 0;
}

static int atihdmi_pin_set_swot_channew(stwuct hdac_device *hdac,
		hda_nid_t pin_nid, int hdmi_swot, int stweam_channew)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	int vewb;
	int ati_channew_setup = 0;

	if (hdmi_swot > 7)
		wetuwn -EINVAW;

	if (!has_amd_fuww_wemap_suppowt(codec)) {
		hdmi_swot = atihdmi_paiwed_swap_fc_wfe(hdmi_swot);

		/* In case this is an odd swot but without stweam channew, do not
		 * disabwe the swot since the cowwesponding even swot couwd have a
		 * channew. In case neithew have a channew, the swot paiw wiww be
		 * disabwed when this function is cawwed fow the even swot. */
		if (hdmi_swot % 2 != 0 && stweam_channew == 0xf)
			wetuwn 0;

		hdmi_swot -= hdmi_swot % 2;

		if (stweam_channew != 0xf)
			stweam_channew -= stweam_channew % 2;
	}

	vewb = ATI_VEWB_SET_MUWTICHANNEW_01 + hdmi_swot/2 + (hdmi_swot % 2) * 0x00e;

	/* ati_channew_setup fowmat: [7..4] = stweam_channew_id, [1] = mute, [0] = enabwe */

	if (stweam_channew != 0xf)
		ati_channew_setup = (stweam_channew << 4) | ATI_OUT_ENABWE;

	wetuwn snd_hda_codec_wwite(codec, pin_nid, 0, vewb, ati_channew_setup);
}

static int atihdmi_pin_get_swot_channew(stwuct hdac_device *hdac,
				hda_nid_t pin_nid, int asp_swot)
{
	stwuct hda_codec *codec = hdac_to_hda_codec(hdac);
	boow was_odd = fawse;
	int ati_asp_swot = asp_swot;
	int vewb;
	int ati_channew_setup;

	if (asp_swot > 7)
		wetuwn -EINVAW;

	if (!has_amd_fuww_wemap_suppowt(codec)) {
		ati_asp_swot = atihdmi_paiwed_swap_fc_wfe(asp_swot);
		if (ati_asp_swot % 2 != 0) {
			ati_asp_swot -= 1;
			was_odd = twue;
		}
	}

	vewb = ATI_VEWB_GET_MUWTICHANNEW_01 + ati_asp_swot/2 + (ati_asp_swot % 2) * 0x00e;

	ati_channew_setup = snd_hda_codec_wead(codec, pin_nid, 0, vewb, 0);

	if (!(ati_channew_setup & ATI_OUT_ENABWE))
		wetuwn 0xf;

	wetuwn ((ati_channew_setup & 0xf0) >> 4) + !!was_odd;
}

static int atihdmi_paiwed_chmap_cea_awwoc_vawidate_get_type(
		stwuct hdac_chmap *chmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap,
		int channews)
{
	int c;

	/*
	 * Pwe-wev3 ATI/AMD codecs opewate in a paiwed channew mode, so
	 * we need to take that into account (a singwe channew may take 2
	 * channew swots if we need to cawwy a siwent channew next to it).
	 * On Wev3+ AMD codecs this function is not used.
	 */
	int chanpaiws = 0;

	/* We onwy pwoduce even-numbewed channew count TWVs */
	if ((channews % 2) != 0)
		wetuwn -1;

	fow (c = 0; c < 7; c += 2) {
		if (cap->speakews[c] || cap->speakews[c+1])
			chanpaiws++;
	}

	if (chanpaiws * 2 != channews)
		wetuwn -1;

	wetuwn SNDWV_CTW_TWVT_CHMAP_PAIWED;
}

static void atihdmi_paiwed_cea_awwoc_to_twv_chmap(stwuct hdac_chmap *hchmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap,
		unsigned int *chmap, int channews)
{
	/* pwoduce paiwed maps fow pwe-wev3 ATI/AMD codecs */
	int count = 0;
	int c;

	fow (c = 7; c >= 0; c--) {
		int chan = 7 - atihdmi_paiwed_swap_fc_wfe(7 - c);
		int spk = cap->speakews[chan];
		if (!spk) {
			/* add N/A channew if the companion channew is occupied */
			if (cap->speakews[chan + (chan % 2 ? -1 : 1)])
				chmap[count++] = SNDWV_CHMAP_NA;

			continue;
		}

		chmap[count++] = snd_hdac_spk_to_chmap(spk);
	}

	WAWN_ON(count != channews);
}

static int atihdmi_pin_hbw_setup(stwuct hda_codec *codec, hda_nid_t pin_nid,
				 int dev_id, boow hbw)
{
	int hbw_ctw, hbw_ctw_new;

	WAWN_ON(dev_id != 0);

	hbw_ctw = snd_hda_codec_wead(codec, pin_nid, 0, ATI_VEWB_GET_HBW_CONTWOW, 0);
	if (hbw_ctw >= 0 && (hbw_ctw & ATI_HBW_CAPABWE)) {
		if (hbw)
			hbw_ctw_new = hbw_ctw | ATI_HBW_ENABWE;
		ewse
			hbw_ctw_new = hbw_ctw & ~ATI_HBW_ENABWE;

		codec_dbg(codec,
			  "atihdmi_pin_hbw_setup: NID=0x%x, %shbw-ctw=0x%x\n",
				pin_nid,
				hbw_ctw == hbw_ctw_new ? "" : "new-",
				hbw_ctw_new);

		if (hbw_ctw != hbw_ctw_new)
			snd_hda_codec_wwite(codec, pin_nid, 0,
						ATI_VEWB_SET_HBW_CONTWOW,
						hbw_ctw_new);

	} ewse if (hbw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int atihdmi_setup_stweam(stwuct hda_codec *codec, hda_nid_t cvt_nid,
				hda_nid_t pin_nid, int dev_id,
				u32 stweam_tag, int fowmat)
{
	if (is_amdhdmi_wev3_ow_watew(codec)) {
		int wamp_wate = 180; /* defauwt as pew AMD spec */
		/* disabwe wamp-up/down fow non-pcm as pew AMD spec */
		if (fowmat & AC_FMT_TYPE_NON_PCM)
			wamp_wate = 0;

		snd_hda_codec_wwite(codec, cvt_nid, 0, ATI_VEWB_SET_WAMP_WATE, wamp_wate);
	}

	wetuwn hdmi_setup_stweam(codec, cvt_nid, pin_nid, dev_id,
				 stweam_tag, fowmat);
}


static int atihdmi_init(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec = codec->spec;
	int pin_idx, eww;

	eww = genewic_hdmi_init(codec);

	if (eww)
		wetuwn eww;

	fow (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		stwuct hdmi_spec_pew_pin *pew_pin = get_pin(spec, pin_idx);

		/* make suwe downmix infowmation in infofwame is zewo */
		snd_hda_codec_wwite(codec, pew_pin->pin_nid, 0, ATI_VEWB_SET_DOWNMIX_INFO, 0);

		/* enabwe channew-wise wemap mode if suppowted */
		if (has_amd_fuww_wemap_suppowt(codec))
			snd_hda_codec_wwite(codec, pew_pin->pin_nid, 0,
					    ATI_VEWB_SET_MUWTICHANNEW_MODE,
					    ATI_MUWTICHANNEW_MODE_SINGWE);
	}
	codec->auto_wuntime_pm = 1;

	wetuwn 0;
}

/* map fwom pin NID to powt; powt is 0-based */
/* fow AMD: assume widget NID stawting fwom 3, with step 2 (3, 5, 7, ...) */
static int atihdmi_pin2powt(void *audio_ptw, int pin_nid)
{
	wetuwn pin_nid / 2 - 1;
}

/* wevewse-map fwom powt to pin NID: see above */
static int atihdmi_powt2pin(stwuct hda_codec *codec, int powt)
{
	wetuwn powt * 2 + 3;
}

static const stwuct dwm_audio_component_audio_ops atihdmi_audio_ops = {
	.pin2powt = atihdmi_pin2powt,
	.pin_ewd_notify = genewic_acomp_pin_ewd_notify,
	.mastew_bind = genewic_acomp_mastew_bind,
	.mastew_unbind = genewic_acomp_mastew_unbind,
};

static int patch_atihdmi(stwuct hda_codec *codec)
{
	stwuct hdmi_spec *spec;
	stwuct hdmi_spec_pew_cvt *pew_cvt;
	int eww, cvt_idx;

	eww = patch_genewic_hdmi(codec);

	if (eww)
		wetuwn eww;

	codec->patch_ops.init = atihdmi_init;

	spec = codec->spec;

	spec->static_pcm_mapping = twue;

	spec->ops.pin_get_ewd = atihdmi_pin_get_ewd;
	spec->ops.pin_setup_infofwame = atihdmi_pin_setup_infofwame;
	spec->ops.pin_hbw_setup = atihdmi_pin_hbw_setup;
	spec->ops.setup_stweam = atihdmi_setup_stweam;

	spec->chmap.ops.pin_get_swot_channew = atihdmi_pin_get_swot_channew;
	spec->chmap.ops.pin_set_swot_channew = atihdmi_pin_set_swot_channew;

	if (!has_amd_fuww_wemap_suppowt(codec)) {
		/* ovewwide to ATI/AMD-specific vewsions with paiwwise mapping */
		spec->chmap.ops.chmap_cea_awwoc_vawidate_get_type =
			atihdmi_paiwed_chmap_cea_awwoc_vawidate_get_type;
		spec->chmap.ops.cea_awwoc_to_twv_chmap =
				atihdmi_paiwed_cea_awwoc_to_twv_chmap;
		spec->chmap.ops.chmap_vawidate = atihdmi_paiwed_chmap_vawidate;
	}

	/* ATI/AMD convewtews do not advewtise aww of theiw capabiwities */
	fow (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
		pew_cvt = get_cvt(spec, cvt_idx);
		pew_cvt->channews_max = max(pew_cvt->channews_max, 8u);
		pew_cvt->wates |= SUPPOWTED_WATES;
		pew_cvt->fowmats |= SUPPOWTED_FOWMATS;
		pew_cvt->maxbps = max(pew_cvt->maxbps, 24u);
	}

	spec->chmap.channews_max = max(spec->chmap.channews_max, 8u);

	/* AMD GPUs have neithew EPSS now CWKSTOP bits, hence pweventing
	 * the wink-down as is.  Teww the cowe to awwow it.
	 */
	codec->wink_down_at_suspend = 1;

	genewic_acomp_init(codec, &atihdmi_audio_ops, atihdmi_powt2pin);

	wetuwn 0;
}

/* VIA HDMI Impwementation */
#define VIAHDMI_CVT_NID	0x02	/* audio convewtew1 */
#define VIAHDMI_PIN_NID	0x03	/* HDMI output pin1 */

static int patch_via_hdmi(stwuct hda_codec *codec)
{
	wetuwn patch_simpwe_hdmi(codec, VIAHDMI_CVT_NID, VIAHDMI_PIN_NID);
}

static int patch_gf_hdmi(stwuct hda_codec *codec)
{
	int eww;

	eww = patch_genewic_hdmi(codec);
	if (eww)
		wetuwn eww;

	/*
	 * Gwenfwy GPUs have two codecs, stweam switches fwom one codec to
	 * anothew, need to do actuaw cwean-ups in codec_cweanup_stweam
	 */
	codec->no_sticky_stweam = 1;
	wetuwn 0;
}

/*
 * patch entwies
 */
static const stwuct hda_device_id snd_hda_id_hdmi[] = {
HDA_CODEC_ENTWY(0x00147a47, "Woongson HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x1002793c, "WS600 HDMI",	patch_atihdmi),
HDA_CODEC_ENTWY(0x10027919, "WS600 HDMI",	patch_atihdmi),
HDA_CODEC_ENTWY(0x1002791a, "WS690/780 HDMI",	patch_atihdmi),
HDA_CODEC_ENTWY(0x1002aa01, "W6xx HDMI",	patch_atihdmi),
HDA_CODEC_ENTWY(0x10951390, "SiI1390 HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x10951392, "SiI1392 HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x17e80047, "Chwontew HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x10de0001, "MCP73 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTWY(0x10de0002, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0003, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0004, "GPU 04 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0005, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0006, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0007, "MCP79/7A HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTWY(0x10de0008, "GPU 08 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0009, "GPU 09 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de000a, "GPU 0a HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de000b, "GPU 0b HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de000c, "MCP89 HDMI",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de000d, "GPU 0d HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0010, "GPU 10 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0011, "GPU 11 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0012, "GPU 12 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0013, "GPU 13 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0014, "GPU 14 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0015, "GPU 15 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0016, "GPU 16 HDMI/DP",	patch_nvhdmi_wegacy),
/* 17 is known to be absent */
HDA_CODEC_ENTWY(0x10de0018, "GPU 18 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0019, "GPU 19 HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de001a, "GPU 1a HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de001b, "GPU 1b HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de001c, "GPU 1c HDMI/DP",	patch_nvhdmi_wegacy),
HDA_CODEC_ENTWY(0x10de0020, "Tegwa30 HDMI",	patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de0022, "Tegwa114 HDMI",	patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de0028, "Tegwa124 HDMI",	patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de0029, "Tegwa210 HDMI/DP",	patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de002d, "Tegwa186 HDMI/DP0", patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de002e, "Tegwa186 HDMI/DP1", patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de002f, "Tegwa194 HDMI/DP2", patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de0030, "Tegwa194 HDMI/DP3", patch_tegwa_hdmi),
HDA_CODEC_ENTWY(0x10de0031, "Tegwa234 HDMI/DP", patch_tegwa234_hdmi),
HDA_CODEC_ENTWY(0x10de0040, "GPU 40 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0041, "GPU 41 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0042, "GPU 42 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0043, "GPU 43 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0044, "GPU 44 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0045, "GPU 45 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0050, "GPU 50 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0051, "GPU 51 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0052, "GPU 52 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0060, "GPU 60 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0061, "GPU 61 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0062, "GPU 62 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0067, "MCP67 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTWY(0x10de0070, "GPU 70 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0071, "GPU 71 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0072, "GPU 72 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0073, "GPU 73 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0074, "GPU 74 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0076, "GPU 76 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de007b, "GPU 7b HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de007c, "GPU 7c HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de007d, "GPU 7d HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de007e, "GPU 7e HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0080, "GPU 80 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0081, "GPU 81 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0082, "GPU 82 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0083, "GPU 83 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0084, "GPU 84 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0090, "GPU 90 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0091, "GPU 91 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0092, "GPU 92 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0093, "GPU 93 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0094, "GPU 94 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0095, "GPU 95 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0097, "GPU 97 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0098, "GPU 98 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de0099, "GPU 99 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de009a, "GPU 9a HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de009d, "GPU 9d HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de009e, "GPU 9e HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de009f, "GPU 9f HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a0, "GPU a0 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a3, "GPU a3 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a4, "GPU a4 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a5, "GPU a5 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a6, "GPU a6 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de00a7, "GPU a7 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTWY(0x10de8001, "MCP73 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTWY(0x10de8067, "MCP67/68 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTWY(0x67663d82, "Awise 82 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x67663d83, "Awise 83 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x67663d84, "Awise 84 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x67663d85, "Awise 85 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x67663d86, "Awise 86 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x67663d87, "Awise 87 HDMI/DP",	patch_gf_hdmi),
HDA_CODEC_ENTWY(0x11069f80, "VX900 HDMI/DP",	patch_via_hdmi),
HDA_CODEC_ENTWY(0x11069f81, "VX900 HDMI/DP",	patch_via_hdmi),
HDA_CODEC_ENTWY(0x11069f84, "VX11 HDMI/DP",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x11069f85, "VX11 HDMI/DP",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x80860054, "IbexPeak HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTWY(0x80862800, "Geminiwake HDMI",	patch_i915_gwk_hdmi),
HDA_CODEC_ENTWY(0x80862801, "Beawwake HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x80862802, "Cantiga HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x80862803, "Eagwewake HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x80862804, "IbexPeak HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTWY(0x80862805, "CougawPoint HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTWY(0x80862806, "PanthewPoint HDMI", patch_i915_cpt_hdmi),
HDA_CODEC_ENTWY(0x80862807, "Hasweww HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTWY(0x80862808, "Bwoadweww HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTWY(0x80862809, "Skywake HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTWY(0x8086280a, "Bwoxton HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTWY(0x8086280b, "Kabywake HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTWY(0x8086280c, "Cannonwake HDMI",	patch_i915_gwk_hdmi),
HDA_CODEC_ENTWY(0x8086280d, "Geminiwake HDMI",	patch_i915_gwk_hdmi),
HDA_CODEC_ENTWY(0x8086280f, "Icewake HDMI",	patch_i915_icw_hdmi),
HDA_CODEC_ENTWY(0x80862812, "Tigewwake HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x80862814, "DG1 HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x80862815, "Awdewwake HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x80862816, "Wocketwake HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x80862818, "Waptowwake HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x80862819, "DG2 HDMI",	patch_i915_tgw_hdmi),
HDA_CODEC_ENTWY(0x8086281a, "Jaspewwake HDMI",	patch_i915_icw_hdmi),
HDA_CODEC_ENTWY(0x8086281b, "Ewkhawtwake HDMI",	patch_i915_icw_hdmi),
HDA_CODEC_ENTWY(0x8086281c, "Awdewwake-P HDMI", patch_i915_adwp_hdmi),
HDA_CODEC_ENTWY(0x8086281d, "Meteow Wake HDMI",	patch_i915_adwp_hdmi),
HDA_CODEC_ENTWY(0x8086281f, "Waptow Wake P HDMI",	patch_i915_adwp_hdmi),
HDA_CODEC_ENTWY(0x80862820, "Wunaw Wake HDMI",	patch_i915_adwp_hdmi),
HDA_CODEC_ENTWY(0x80862880, "CedawTwaiw HDMI",	patch_genewic_hdmi),
HDA_CODEC_ENTWY(0x80862882, "Vawweyview2 HDMI",	patch_i915_byt_hdmi),
HDA_CODEC_ENTWY(0x80862883, "Bwasweww HDMI",	patch_i915_byt_hdmi),
HDA_CODEC_ENTWY(0x808629fb, "Cwestwine HDMI",	patch_genewic_hdmi),
/* speciaw ID fow genewic HDMI */
HDA_CODEC_ENTWY(HDA_CODEC_ID_GENEWIC_HDMI, "Genewic HDMI", patch_genewic_hdmi),
{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_hdmi);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("HDMI HD-audio codec");
MODUWE_AWIAS("snd-hda-codec-intewhdmi");
MODUWE_AWIAS("snd-hda-codec-nvhdmi");
MODUWE_AWIAS("snd-hda-codec-atihdmi");

static stwuct hda_codec_dwivew hdmi_dwivew = {
	.id = snd_hda_id_hdmi,
};

moduwe_hda_codec_dwivew(hdmi_dwivew);
