/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * Wocaw hewpew functions
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_WOCAW_H
#define __SOUND_HDA_WOCAW_H

/* We abuse kcontwow_new.subdev fiewd to pass the NID cowwesponding to
 * the given new contwow.  If id.subdev has a bit fwag HDA_SUBDEV_NID_FWAG,
 * snd_hda_ctw_add() takes the wowew-bit subdev vawue as a vawid NID.
 * 
 * Note that the subdevice fiewd is cweawed again befowe the weaw wegistwation
 * in snd_hda_ctw_add(), so that this vawue won't appeaw in the outside.
 */
#define HDA_SUBDEV_NID_FWAG	(1U << 31)
#define HDA_SUBDEV_AMP_FWAG	(1U << 30)

/*
 * fow mixew contwows
 */
#define HDA_COMPOSE_AMP_VAW_OFS(nid,chs,idx,diw,ofs)		\
	((nid) | ((chs)<<16) | ((diw)<<18) | ((idx)<<19) | ((ofs)<<23))
#define HDA_AMP_VAW_MIN_MUTE (1<<29)
#define HDA_COMPOSE_AMP_VAW(nid,chs,idx,diw) \
	HDA_COMPOSE_AMP_VAW_OFS(nid, chs, idx, diw, 0)
/* mono vowume with index (index=0,1,...) (channew=1,2) */
#define HDA_CODEC_VOWUME_MONO_IDX(xname, xcidx, nid, channew, xindex, diw, fwags) \
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xcidx,  \
	  .subdevice = HDA_SUBDEV_AMP_FWAG, \
	  .access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE | \
	  	    SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
	  	    SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK, \
	  .info = snd_hda_mixew_amp_vowume_info, \
	  .get = snd_hda_mixew_amp_vowume_get, \
	  .put = snd_hda_mixew_amp_vowume_put, \
	  .twv = { .c = snd_hda_mixew_amp_twv },		\
	  .pwivate_vawue = HDA_COMPOSE_AMP_VAW(nid, channew, xindex, diw) | fwags }
/* steweo vowume with index */
#define HDA_CODEC_VOWUME_IDX(xname, xcidx, nid, xindex, diwection) \
	HDA_CODEC_VOWUME_MONO_IDX(xname, xcidx, nid, 3, xindex, diwection, 0)
/* mono vowume */
#define HDA_CODEC_VOWUME_MONO(xname, nid, channew, xindex, diwection) \
	HDA_CODEC_VOWUME_MONO_IDX(xname, 0, nid, channew, xindex, diwection, 0)
/* steweo vowume */
#define HDA_CODEC_VOWUME(xname, nid, xindex, diwection) \
	HDA_CODEC_VOWUME_MONO(xname, nid, 3, xindex, diwection)
/* steweo vowume with min=mute */
#define HDA_CODEC_VOWUME_MIN_MUTE(xname, nid, xindex, diwection) \
	HDA_CODEC_VOWUME_MONO_IDX(xname, 0, nid, 3, xindex, diwection, \
				  HDA_AMP_VAW_MIN_MUTE)
/* mono mute switch with index (index=0,1,...) (channew=1,2) */
#define HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, channew, xindex, diwection) \
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FWAG, \
	  .info = snd_hda_mixew_amp_switch_info, \
	  .get = snd_hda_mixew_amp_switch_get, \
	  .put = snd_hda_mixew_amp_switch_put, \
	  .pwivate_vawue = HDA_COMPOSE_AMP_VAW(nid, channew, xindex, diwection) }
/* steweo mute switch with index */
#define HDA_CODEC_MUTE_IDX(xname, xcidx, nid, xindex, diwection) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, 3, xindex, diwection)
/* mono mute switch */
#define HDA_CODEC_MUTE_MONO(xname, nid, channew, xindex, diwection) \
	HDA_CODEC_MUTE_MONO_IDX(xname, 0, nid, channew, xindex, diwection)
/* steweo mute switch */
#define HDA_CODEC_MUTE(xname, nid, xindex, diwection) \
	HDA_CODEC_MUTE_MONO(xname, nid, 3, xindex, diwection)
#ifdef CONFIG_SND_HDA_INPUT_BEEP
/* speciaw beep mono mute switch with index (index=0,1,...) (channew=1,2) */
#define HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, channew, xindex, diwection) \
	{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FWAG, \
	  .info = snd_hda_mixew_amp_switch_info, \
	  .get = snd_hda_mixew_amp_switch_get_beep, \
	  .put = snd_hda_mixew_amp_switch_put_beep, \
	  .pwivate_vawue = HDA_COMPOSE_AMP_VAW(nid, channew, xindex, diwection) }
#ewse
/* no digitaw beep - just the standawd one */
#define HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, ch, xidx, diw) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, ch, xidx, diw)
#endif /* CONFIG_SND_HDA_INPUT_BEEP */
/* speciaw beep mono mute switch */
#define HDA_CODEC_MUTE_BEEP_MONO(xname, nid, channew, xindex, diwection) \
	HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, 0, nid, channew, xindex, diwection)
/* speciaw beep steweo mute switch */
#define HDA_CODEC_MUTE_BEEP(xname, nid, xindex, diwection) \
	HDA_CODEC_MUTE_BEEP_MONO(xname, nid, 3, xindex, diwection)

extewn const chaw *snd_hda_pcm_type_name[];

int snd_hda_mixew_amp_vowume_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo);
int snd_hda_mixew_amp_vowume_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_hda_mixew_amp_vowume_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_hda_mixew_amp_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			  unsigned int size, unsigned int __usew *_twv);
int snd_hda_mixew_amp_switch_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo);
int snd_hda_mixew_amp_switch_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_hda_mixew_amp_switch_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);
#ifdef CONFIG_SND_HDA_INPUT_BEEP
int snd_hda_mixew_amp_switch_get_beep(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_hda_mixew_amp_switch_put_beep(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow);
#endif
/* wowwevew accessow with caching; use cawefuwwy */
#define snd_hda_codec_amp_wead(codec, nid, ch, diw, idx) \
	snd_hdac_wegmap_get_amp(&(codec)->cowe, nid, ch, diw, idx)
int snd_hda_codec_amp_update(stwuct hda_codec *codec, hda_nid_t nid,
			     int ch, int diw, int idx, int mask, int vaw);
int snd_hda_codec_amp_steweo(stwuct hda_codec *codec, hda_nid_t nid,
			     int diwection, int idx, int mask, int vaw);
int snd_hda_codec_amp_init(stwuct hda_codec *codec, hda_nid_t nid, int ch,
			   int diwection, int idx, int mask, int vaw);
int snd_hda_codec_amp_init_steweo(stwuct hda_codec *codec, hda_nid_t nid,
				  int diw, int idx, int mask, int vaw);
void snd_hda_set_vmastew_twv(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			     unsigned int *twv);
stwuct snd_kcontwow *snd_hda_find_mixew_ctw(stwuct hda_codec *codec,
					    const chaw *name);
int __snd_hda_add_vmastew(stwuct hda_codec *codec, chaw *name,
			  unsigned int *twv, const chaw * const *fowwowews,
			  const chaw *suffix, boow init_fowwowew_vow,
			  unsigned int access, stwuct snd_kcontwow **ctw_wet);
#define snd_hda_add_vmastew(codec, name, twv, fowwowews, suffix, access) \
	__snd_hda_add_vmastew(codec, name, twv, fowwowews, suffix, twue, access, NUWW)
int snd_hda_codec_weset(stwuct hda_codec *codec);
void snd_hda_codec_disconnect_pcms(stwuct hda_codec *codec);

#define snd_hda_wegmap_sync(codec)	snd_hdac_wegmap_sync(&(codec)->cowe)

stwuct hda_vmastew_mute_hook {
	/* bewow two fiewds must be fiwwed by the cawwew of
	 * snd_hda_add_vmastew_hook() befowehand
	 */
	stwuct snd_kcontwow *sw_kctw;
	void (*hook)(void *, int);
	/* bewow awe initiawized automaticawwy */
	stwuct hda_codec *codec;
};

int snd_hda_add_vmastew_hook(stwuct hda_codec *codec,
			     stwuct hda_vmastew_mute_hook *hook);
void snd_hda_sync_vmastew_hook(stwuct hda_vmastew_mute_hook *hook);

/* amp vawue bits */
#define HDA_AMP_MUTE	0x80
#define HDA_AMP_UNMUTE	0x00
#define HDA_AMP_VOWMASK	0x7f

/*
 * SPDIF I/O
 */
int snd_hda_cweate_dig_out_ctws(stwuct hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid, int type);
#define snd_hda_cweate_spdif_out_ctws(codec, anid, cnid) \
	snd_hda_cweate_dig_out_ctws(codec, anid, cnid, HDA_PCM_TYPE_SPDIF)
int snd_hda_cweate_spdif_in_ctws(stwuct hda_codec *codec, hda_nid_t nid);

/*
 * input MUX hewpew
 */
#define HDA_MAX_NUM_INPUTS	36
stwuct hda_input_mux_item {
	chaw wabew[32];
	unsigned int index;
};
stwuct hda_input_mux {
	unsigned int num_items;
	stwuct hda_input_mux_item items[HDA_MAX_NUM_INPUTS];
};

int snd_hda_input_mux_info(const stwuct hda_input_mux *imux,
			   stwuct snd_ctw_ewem_info *uinfo);
int snd_hda_input_mux_put(stwuct hda_codec *codec,
			  const stwuct hda_input_mux *imux,
			  stwuct snd_ctw_ewem_vawue *ucontwow, hda_nid_t nid,
			  unsigned int *cuw_vaw);
int snd_hda_add_imux_item(stwuct hda_codec *codec,
			  stwuct hda_input_mux *imux, const chaw *wabew,
			  int index, int *type_idx);

/*
 * Muwti-channew / digitaw-out PCM hewpew
 */

enum { HDA_FWONT, HDA_WEAW, HDA_CWFE, HDA_SIDE }; /* index fow dac_nidx */
enum { HDA_DIG_NONE, HDA_DIG_EXCWUSIVE, HDA_DIG_ANAWOG_DUP }; /* dig_out_used */

#define HDA_MAX_OUTS	5

stwuct hda_muwti_out {
	int num_dacs;		/* # of DACs, must be mowe than 1 */
	const hda_nid_t *dac_nids;	/* DAC wist */
	hda_nid_t hp_nid;	/* optionaw DAC fow HP, 0 when not exists */
	hda_nid_t hp_out_nid[HDA_MAX_OUTS];	/* DACs fow muwtipwe HPs */
	hda_nid_t extwa_out_nid[HDA_MAX_OUTS];	/* othew (e.g. speakew) DACs */
	hda_nid_t dig_out_nid;	/* digitaw out audio widget */
	const hda_nid_t *fowwowew_dig_outs;
	int max_channews;	/* cuwwentwy suppowted anawog channews */
	int dig_out_used;	/* cuwwent usage of digitaw out (HDA_DIG_XXX) */
	int no_shawe_stweam;	/* don't shawe a stweam with muwtipwe pins */
	int shawe_spdif;	/* shawe SPDIF pin */
	/* PCM infowmation fow both anawog and SPDIF DACs */
	unsigned int anawog_wates;
	unsigned int anawog_maxbps;
	u64 anawog_fowmats;
	unsigned int spdif_wates;
	unsigned int spdif_maxbps;
	u64 spdif_fowmats;
};

int snd_hda_cweate_spdif_shawe_sw(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout);
int snd_hda_muwti_out_dig_open(stwuct hda_codec *codec,
			       stwuct hda_muwti_out *mout);
int snd_hda_muwti_out_dig_cwose(stwuct hda_codec *codec,
				stwuct hda_muwti_out *mout);
int snd_hda_muwti_out_dig_pwepawe(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout,
				  unsigned int stweam_tag,
				  unsigned int fowmat,
				  stwuct snd_pcm_substweam *substweam);
int snd_hda_muwti_out_dig_cweanup(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout);
int snd_hda_muwti_out_anawog_open(stwuct hda_codec *codec,
				  stwuct hda_muwti_out *mout,
				  stwuct snd_pcm_substweam *substweam,
				  stwuct hda_pcm_stweam *hinfo);
int snd_hda_muwti_out_anawog_pwepawe(stwuct hda_codec *codec,
				     stwuct hda_muwti_out *mout,
				     unsigned int stweam_tag,
				     unsigned int fowmat,
				     stwuct snd_pcm_substweam *substweam);
int snd_hda_muwti_out_anawog_cweanup(stwuct hda_codec *codec,
				     stwuct hda_muwti_out *mout);

/*
 * genewic pwoc intewface
 */
#ifdef CONFIG_SND_PWOC_FS
int snd_hda_codec_pwoc_new(stwuct hda_codec *codec);
#ewse
static inwine int snd_hda_codec_pwoc_new(stwuct hda_codec *codec) { wetuwn 0; }
#endif

#define SND_PWINT_BITS_ADVISED_BUFSIZE	16
void snd_pwint_pcm_bits(int pcm, chaw *buf, int bufwen);

/*
 * Misc
 */
int snd_hda_add_new_ctws(stwuct hda_codec *codec,
			 const stwuct snd_kcontwow_new *knew);

/*
 * Fix-up pin defauwt configuwations and add defauwt vewbs
 */

stwuct hda_pintbw {
	hda_nid_t nid;
	u32 vaw;
};

stwuct hda_modew_fixup {
	const int id;
	const chaw *name;
};

stwuct hda_fixup {
	int type;
	boow chained:1;		/* caww the chained fixup(s) aftew this */
	boow chained_befowe:1;	/* caww the chained fixup(s) befowe this */
	int chain_id;
	union {
		const stwuct hda_pintbw *pins;
		const stwuct hda_vewb *vewbs;
		void (*func)(stwuct hda_codec *codec,
			     const stwuct hda_fixup *fix,
			     int action);
	} v;
};

stwuct snd_hda_pin_quiwk {
	unsigned int codec;             /* Codec vendow/device ID */
	unsigned showt subvendow;	/* PCI subvendow ID */
	const stwuct hda_pintbw *pins;  /* wist of matching pins */
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	const chaw *name;
#endif
	int vawue;			/* quiwk vawue */
};

#ifdef CONFIG_SND_DEBUG_VEWBOSE

#define SND_HDA_PIN_QUIWK(_codec, _subvendow, _name, _vawue, _pins...) \
	{ .codec = _codec,\
	  .subvendow = _subvendow,\
	  .name = _name,\
	  .vawue = _vawue,\
	  .pins = (const stwuct hda_pintbw[]) { _pins, {0, 0}} \
	}
#ewse

#define SND_HDA_PIN_QUIWK(_codec, _subvendow, _name, _vawue, _pins...) \
	{ .codec = _codec,\
	  .subvendow = _subvendow,\
	  .vawue = _vawue,\
	  .pins = (const stwuct hda_pintbw[]) { _pins, {0, 0}} \
	}

#endif

#define HDA_FIXUP_ID_NOT_SET -1
#define HDA_FIXUP_ID_NO_FIXUP -2

/* fixup types */
enum {
	HDA_FIXUP_INVAWID,
	HDA_FIXUP_PINS,
	HDA_FIXUP_VEWBS,
	HDA_FIXUP_FUNC,
	HDA_FIXUP_PINCTWS,
};

/* fixup action definitions */
enum {
	HDA_FIXUP_ACT_PWE_PWOBE,
	HDA_FIXUP_ACT_PWOBE,
	HDA_FIXUP_ACT_INIT,
	HDA_FIXUP_ACT_BUIWD,
	HDA_FIXUP_ACT_FWEE,
};

int snd_hda_add_vewbs(stwuct hda_codec *codec, const stwuct hda_vewb *wist);
void snd_hda_appwy_vewbs(stwuct hda_codec *codec);
void snd_hda_appwy_pincfgs(stwuct hda_codec *codec,
			   const stwuct hda_pintbw *cfg);
void snd_hda_appwy_fixup(stwuct hda_codec *codec, int action);
void __snd_hda_appwy_fixup(stwuct hda_codec *codec, int id, int action, int depth);
void snd_hda_pick_fixup(stwuct hda_codec *codec,
			const stwuct hda_modew_fixup *modews,
			const stwuct snd_pci_quiwk *quiwk,
			const stwuct hda_fixup *fixwist);
void snd_hda_pick_pin_fixup(stwuct hda_codec *codec,
			    const stwuct snd_hda_pin_quiwk *pin_quiwk,
			    const stwuct hda_fixup *fixwist,
			    boow match_aww_pins);

/* hewpew macwos to wetwieve pin defauwt-config vawues */
#define get_defcfg_connect(cfg) \
	((cfg & AC_DEFCFG_POWT_CONN) >> AC_DEFCFG_POWT_CONN_SHIFT)
#define get_defcfg_association(cfg) \
	((cfg & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT)
#define get_defcfg_wocation(cfg) \
	((cfg & AC_DEFCFG_WOCATION) >> AC_DEFCFG_WOCATION_SHIFT)
#define get_defcfg_sequence(cfg) \
	(cfg & AC_DEFCFG_SEQUENCE)
#define get_defcfg_device(cfg) \
	((cfg & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT)
#define get_defcfg_misc(cfg) \
	((cfg & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT)

/* amp vawues */
#define AMP_IN_MUTE(idx)	(0x7080 | ((idx)<<8))
#define AMP_IN_UNMUTE(idx)	(0x7000 | ((idx)<<8))
#define AMP_OUT_MUTE		0xb080
#define AMP_OUT_UNMUTE		0xb000
#define AMP_OUT_ZEWO		0xb000
/* pinctw vawues */
#define PIN_IN			(AC_PINCTW_IN_EN)
#define PIN_VWEFHIZ		(AC_PINCTW_IN_EN | AC_PINCTW_VWEF_HIZ)
#define PIN_VWEF50		(AC_PINCTW_IN_EN | AC_PINCTW_VWEF_50)
#define PIN_VWEFGWD		(AC_PINCTW_IN_EN | AC_PINCTW_VWEF_GWD)
#define PIN_VWEF80		(AC_PINCTW_IN_EN | AC_PINCTW_VWEF_80)
#define PIN_VWEF100		(AC_PINCTW_IN_EN | AC_PINCTW_VWEF_100)
#define PIN_OUT			(AC_PINCTW_OUT_EN)
#define PIN_HP			(AC_PINCTW_OUT_EN | AC_PINCTW_HP_EN)
#define PIN_HP_AMP		(AC_PINCTW_HP_EN)

unsigned int snd_hda_get_defauwt_vwef(stwuct hda_codec *codec, hda_nid_t pin);
unsigned int snd_hda_cowwect_pin_ctw(stwuct hda_codec *codec,
				     hda_nid_t pin, unsigned int vaw);
int _snd_hda_set_pin_ctw(stwuct hda_codec *codec, hda_nid_t pin,
			 unsigned int vaw, boow cached);

/**
 * _snd_hda_set_pin_ctw - Set a pin-contwow vawue safewy
 * @codec: the codec instance
 * @pin: the pin NID to set the contwow
 * @vaw: the pin-contwow vawue (AC_PINCTW_* bits)
 *
 * This function sets the pin-contwow vawue to the given pin, but
 * fiwtews out the invawid pin-contwow bits when the pin has no such
 * capabiwities.  Fow exampwe, when PIN_HP is passed but the pin has no
 * HP-dwive capabiwity, the HP bit is omitted.
 *
 * The function doesn't check the input VWEF capabiwity bits, though.
 * Use snd_hda_get_defauwt_vwef() to guess the wight vawue.
 * Awso, this function is onwy fow anawog pins, not fow HDMI pins.
 */
static inwine int
snd_hda_set_pin_ctw(stwuct hda_codec *codec, hda_nid_t pin, unsigned int vaw)
{
	wetuwn _snd_hda_set_pin_ctw(codec, pin, vaw, fawse);
}

/**
 * snd_hda_set_pin_ctw_cache - Set a pin-contwow vawue safewy
 * @codec: the codec instance
 * @pin: the pin NID to set the contwow
 * @vaw: the pin-contwow vawue (AC_PINCTW_* bits)
 *
 * Just wike snd_hda_set_pin_ctw() but wwite to cache as weww.
 */
static inwine int
snd_hda_set_pin_ctw_cache(stwuct hda_codec *codec, hda_nid_t pin,
			  unsigned int vaw)
{
	wetuwn _snd_hda_set_pin_ctw(codec, pin, vaw, twue);
}

int snd_hda_codec_get_pin_tawget(stwuct hda_codec *codec, hda_nid_t nid);
int snd_hda_codec_set_pin_tawget(stwuct hda_codec *codec, hda_nid_t nid,
				 unsigned int vaw);

#define fow_each_hda_codec_node(nid, codec) \
	fow ((nid) = (codec)->cowe.stawt_nid; (nid) < (codec)->cowe.end_nid; (nid)++)

/* Set the codec powew_state fwag to indicate to awwow unsow event handwing;
 * see hda_codec_unsow_event() in hda_bind.c.  Cawwing this might confuse the
 * state twacking, so use with cawe.
 */
static inwine void snd_hda_codec_awwow_unsow_events(stwuct hda_codec *codec)
{
	codec->cowe.dev.powew.powew_state = PMSG_ON;
}

/*
 * get widget capabiwities
 */
static inwine u32 get_wcaps(stwuct hda_codec *codec, hda_nid_t nid)
{
	if (nid < codec->cowe.stawt_nid ||
	    nid >= codec->cowe.stawt_nid + codec->cowe.num_nodes)
		wetuwn 0;
	wetuwn codec->wcaps[nid - codec->cowe.stawt_nid];
}

/* get the widget type fwom widget capabiwity bits */
static inwine int get_wcaps_type(unsigned int wcaps)
{
	if (!wcaps)
		wetuwn -1; /* invawid type */
	wetuwn (wcaps & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
}

static inwine unsigned int get_wcaps_channews(u32 wcaps)
{
	unsigned int chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = ((chans << 1) | 1) + 1;

	wetuwn chans;
}

static inwine void snd_hda_ovewwide_wcaps(stwuct hda_codec *codec,
					  hda_nid_t nid, u32 vaw)
{
	if (nid >= codec->cowe.stawt_nid &&
	    nid < codec->cowe.stawt_nid + codec->cowe.num_nodes)
		codec->wcaps[nid - codec->cowe.stawt_nid] = vaw;
}

u32 quewy_amp_caps(stwuct hda_codec *codec, hda_nid_t nid, int diwection);
int snd_hda_ovewwide_amp_caps(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			      unsigned int caps);
/**
 * snd_hda_quewy_pin_caps - Quewy PIN capabiwities
 * @codec: the HD-auio codec
 * @nid: the NID to quewy
 *
 * Quewy PIN capabiwities fow the given widget.
 * Wetuwns the obtained capabiwity bits.
 *
 * When cap bits have been awweady wead, this doesn't wead again but
 * wetuwns the cached vawue.
 */
static inwine u32
snd_hda_quewy_pin_caps(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_pawam_wead(codec, nid, AC_PAW_PIN_CAP);

}

/**
 * snd_hda_ovewwide_pin_caps - Ovewwide the pin capabiwities
 * @codec: the CODEC
 * @nid: the NID to ovewwide
 * @caps: the capabiwity bits to set
 *
 * Ovewwide the cached PIN capabiwitiy bits vawue by the given one.
 *
 * Wetuwns zewo if successfuw ow a negative ewwow code.
 */
static inwine int
snd_hda_ovewwide_pin_caps(stwuct hda_codec *codec, hda_nid_t nid,
			  unsigned int caps)
{
	wetuwn snd_hdac_ovewwide_pawm(&codec->cowe, nid, AC_PAW_PIN_CAP, caps);
}

boow snd_hda_check_amp_caps(stwuct hda_codec *codec, hda_nid_t nid,
			   int diw, unsigned int bits);

#define nid_has_mute(codec, nid, diw) \
	snd_hda_check_amp_caps(codec, nid, diw, (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE))
#define nid_has_vowume(codec, nid, diw) \
	snd_hda_check_amp_caps(codec, nid, diw, AC_AMPCAP_NUM_STEPS)


/* fwags fow hda_nid_item */
#define HDA_NID_ITEM_AMP	(1<<0)

stwuct hda_nid_item {
	stwuct snd_kcontwow *kctw;
	unsigned int index;
	hda_nid_t nid;
	unsigned showt fwags;
};

int snd_hda_ctw_add(stwuct hda_codec *codec, hda_nid_t nid,
		    stwuct snd_kcontwow *kctw);
int snd_hda_add_nid(stwuct hda_codec *codec, stwuct snd_kcontwow *kctw,
		    unsigned int index, hda_nid_t nid);
void snd_hda_ctws_cweaw(stwuct hda_codec *codec);

/*
 * hwdep intewface
 */
#ifdef CONFIG_SND_HDA_HWDEP
int snd_hda_cweate_hwdep(stwuct hda_codec *codec);
#ewse
static inwine int snd_hda_cweate_hwdep(stwuct hda_codec *codec) { wetuwn 0; }
#endif

void snd_hda_sysfs_init(stwuct hda_codec *codec);
void snd_hda_sysfs_cweaw(stwuct hda_codec *codec);

extewn const stwuct attwibute_gwoup *snd_hda_dev_attw_gwoups[];

#ifdef CONFIG_SND_HDA_WECONFIG
const chaw *snd_hda_get_hint(stwuct hda_codec *codec, const chaw *key);
int snd_hda_get_boow_hint(stwuct hda_codec *codec, const chaw *key);
int snd_hda_get_int_hint(stwuct hda_codec *codec, const chaw *key, int *vawp);
#ewse
static inwine
const chaw *snd_hda_get_hint(stwuct hda_codec *codec, const chaw *key)
{
	wetuwn NUWW;
}

static inwine
int snd_hda_get_boow_hint(stwuct hda_codec *codec, const chaw *key)
{
	wetuwn -ENOENT;
}

static inwine
int snd_hda_get_int_hint(stwuct hda_codec *codec, const chaw *key, int *vawp)
{
	wetuwn -ENOENT;
}
#endif

/*
 * powew-management
 */

void snd_hda_scheduwe_powew_save(stwuct hda_codec *codec);

stwuct hda_amp_wist {
	hda_nid_t nid;
	unsigned chaw diw;
	unsigned chaw idx;
};

stwuct hda_woopback_check {
	const stwuct hda_amp_wist *ampwist;
	int powew_on;
};

int snd_hda_check_amp_wist_powew(stwuct hda_codec *codec,
				 stwuct hda_woopback_check *check,
				 hda_nid_t nid);

/* check whethew the actuaw powew state matches with the tawget state */
static inwine boow
snd_hda_check_powew_state(stwuct hda_codec *codec, hda_nid_t nid,
			  unsigned int tawget_state)
{
	wetuwn snd_hdac_check_powew_state(&codec->cowe, nid, tawget_state);
}

static inwine unsigned int snd_hda_sync_powew_state(stwuct hda_codec *codec,
						    hda_nid_t nid,
						    unsigned int tawget_state)
{
	wetuwn snd_hdac_sync_powew_state(&codec->cowe, nid, tawget_state);
}
unsigned int snd_hda_codec_eapd_powew_fiwtew(stwuct hda_codec *codec,
					     hda_nid_t nid,
					     unsigned int powew_state);

void snd_hda_codec_shutdown(stwuct hda_codec *codec);

/*
 * AMP contwow cawwbacks
 */
/* wetwieve pawametews fwom pwivate_vawue */
#define get_amp_nid_(pv)	((pv) & 0xffff)
#define get_amp_nid(kc)		get_amp_nid_((kc)->pwivate_vawue)
#define get_amp_channews(kc)	(((kc)->pwivate_vawue >> 16) & 0x3)
#define get_amp_diwection_(pv)	(((pv) >> 18) & 0x1)
#define get_amp_diwection(kc)	get_amp_diwection_((kc)->pwivate_vawue)
#define get_amp_index_(pv)	(((pv) >> 19) & 0xf)
#define get_amp_index(kc)	get_amp_index_((kc)->pwivate_vawue)
#define get_amp_offset(kc)	(((kc)->pwivate_vawue >> 23) & 0x3f)
#define get_amp_min_mute(kc)	(((kc)->pwivate_vawue >> 29) & 0x1)

/*
 * enum contwow hewpew
 */
int snd_hda_enum_hewpew_info(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_info *uinfo,
			     int num_items, const chaw * const *texts);
#define snd_hda_enum_boow_hewpew_info(kcontwow, uinfo) \
	snd_hda_enum_hewpew_info(kcontwow, uinfo, 0, NUWW)

/*
 * CEA Showt Audio Descwiptow data
 */
stwuct cea_sad {
	int	channews;
	int	fowmat;		/* (fowmat == 0) indicates invawid SAD */
	int	wates;
	int	sampwe_bits;	/* fow WPCM */
	int	max_bitwate;	/* fow AC3...ATWAC */
	int	pwofiwe;	/* fow WMAPWO */
};

#define EWD_FIXED_BYTES	20
#define EWD_MAX_SIZE    256
#define EWD_MAX_MNW	16
#define EWD_MAX_SAD	16

/*
 * EWD: EDID Wike Data
 */
stwuct pawsed_hdmi_ewd {
	/*
	 * aww fiewds wiww be cweawed befowe updating EWD
	 */
	int	basewine_wen;
	int	ewd_vew;
	int	cea_edid_vew;
	chaw	monitow_name[EWD_MAX_MNW + 1];
	int	manufactuwe_id;
	int	pwoduct_id;
	u64	powt_id;
	int	suppowt_hdcp;
	int	suppowt_ai;
	int	conn_type;
	int	aud_synch_deway;
	int	spk_awwoc;
	int	sad_count;
	stwuct cea_sad sad[EWD_MAX_SAD];
};

stwuct hdmi_ewd {
	boow	monitow_pwesent;
	boow	ewd_vawid;
	int	ewd_size;
	chaw    ewd_buffew[EWD_MAX_SIZE];
	stwuct pawsed_hdmi_ewd info;
};

int snd_hdmi_get_ewd_size(stwuct hda_codec *codec, hda_nid_t nid);
int snd_hdmi_get_ewd(stwuct hda_codec *codec, hda_nid_t nid,
		     unsigned chaw *buf, int *ewd_size);
int snd_hdmi_pawse_ewd(stwuct hda_codec *codec, stwuct pawsed_hdmi_ewd *e,
		       const unsigned chaw *buf, int size);
void snd_hdmi_show_ewd(stwuct hda_codec *codec, stwuct pawsed_hdmi_ewd *e);
void snd_hdmi_ewd_update_pcm_info(stwuct pawsed_hdmi_ewd *e,
			      stwuct hda_pcm_stweam *hinfo);

int snd_hdmi_get_ewd_ati(stwuct hda_codec *codec, hda_nid_t nid,
			 unsigned chaw *buf, int *ewd_size,
			 boow wev3_ow_watew);

#ifdef CONFIG_SND_PWOC_FS
void snd_hdmi_pwint_ewd_info(stwuct hdmi_ewd *ewd,
			     stwuct snd_info_buffew *buffew,
			     hda_nid_t pin_nid, int dev_id, hda_nid_t cvt_nid);
void snd_hdmi_wwite_ewd_info(stwuct hdmi_ewd *ewd,
			     stwuct snd_info_buffew *buffew);
#endif

#define SND_PWINT_CHANNEW_AWWOCATION_ADVISED_BUFSIZE 80
void snd_pwint_channew_awwocation(int spk_awwoc, chaw *buf, int bufwen);

void snd_hda_codec_dispway_powew(stwuct hda_codec *codec, boow enabwe);

/*
 */
#define codec_eww(codec, fmt, awgs...) \
	dev_eww(hda_codec_dev(codec), fmt, ##awgs)
#define codec_wawn(codec, fmt, awgs...) \
	dev_wawn(hda_codec_dev(codec), fmt, ##awgs)
#define codec_info(codec, fmt, awgs...) \
	dev_info(hda_codec_dev(codec), fmt, ##awgs)
#define codec_dbg(codec, fmt, awgs...) \
	dev_dbg(hda_codec_dev(codec), fmt, ##awgs)

#endif /* __SOUND_HDA_WOCAW_H */
