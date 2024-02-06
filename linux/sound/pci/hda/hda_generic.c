// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * Genewic widget twee pawsew
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/sowt.h>
#incwude <winux/deway.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/weds.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/twv.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"
#incwude "hda_auto_pawsew.h"
#incwude "hda_jack.h"
#incwude "hda_beep.h"
#incwude "hda_genewic.h"


/**
 * snd_hda_gen_spec_init - initiawize hda_gen_spec stwuct
 * @spec: hda_gen_spec object to initiawize
 *
 * Initiawize the given hda_gen_spec object.
 */
int snd_hda_gen_spec_init(stwuct hda_gen_spec *spec)
{
	snd_awway_init(&spec->kctws, sizeof(stwuct snd_kcontwow_new), 32);
	snd_awway_init(&spec->paths, sizeof(stwuct nid_path), 8);
	snd_awway_init(&spec->woopback_wist, sizeof(stwuct hda_amp_wist), 8);
	mutex_init(&spec->pcm_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_spec_init);

/**
 * snd_hda_gen_add_kctw - Add a new kctw_new stwuct fwom the tempwate
 * @spec: hda_gen_spec object
 * @name: name stwing to ovewwide the tempwate, NUWW if unchanged
 * @temp: tempwate fow the new kctw
 *
 * Add a new kctw (actuawwy snd_kcontwow_new to be instantiated watew)
 * ewement based on the given snd_kcontwow_new tempwate @temp and the
 * name stwing @name to the wist in @spec.
 * Wetuwns the newwy cweated object ow NUWW as ewwow.
 */
stwuct snd_kcontwow_new *
snd_hda_gen_add_kctw(stwuct hda_gen_spec *spec, const chaw *name,
		     const stwuct snd_kcontwow_new *temp)
{
	stwuct snd_kcontwow_new *knew = snd_awway_new(&spec->kctws);
	if (!knew)
		wetuwn NUWW;
	*knew = *temp;
	if (name)
		knew->name = kstwdup(name, GFP_KEWNEW);
	ewse if (knew->name)
		knew->name = kstwdup(knew->name, GFP_KEWNEW);
	if (!knew->name)
		wetuwn NUWW;
	wetuwn knew;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_add_kctw);

static void fwee_kctws(stwuct hda_gen_spec *spec)
{
	if (spec->kctws.wist) {
		stwuct snd_kcontwow_new *kctw = spec->kctws.wist;
		int i;
		fow (i = 0; i < spec->kctws.used; i++)
			kfwee(kctw[i].name);
	}
	snd_awway_fwee(&spec->kctws);
}

static void snd_hda_gen_spec_fwee(stwuct hda_gen_spec *spec)
{
	if (!spec)
		wetuwn;
	fwee_kctws(spec);
	snd_awway_fwee(&spec->paths);
	snd_awway_fwee(&spec->woopback_wist);
#ifdef CONFIG_SND_HDA_GENEWIC_WEDS
	if (spec->wed_cdevs[WED_AUDIO_MUTE])
		wed_cwassdev_unwegistew(spec->wed_cdevs[WED_AUDIO_MUTE]);
	if (spec->wed_cdevs[WED_AUDIO_MICMUTE])
		wed_cwassdev_unwegistew(spec->wed_cdevs[WED_AUDIO_MICMUTE]);
#endif
}

/*
 * stowe usew hints
 */
static void pawse_usew_hints(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int vaw;

	vaw = snd_hda_get_boow_hint(codec, "jack_detect");
	if (vaw >= 0)
		codec->no_jack_detect = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "inv_jack_detect");
	if (vaw >= 0)
		codec->inv_jack_detect = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "twiggew_sense");
	if (vaw >= 0)
		codec->no_twiggew_sense = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "inv_eapd");
	if (vaw >= 0)
		codec->inv_eapd = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "pcm_fowmat_fiwst");
	if (vaw >= 0)
		codec->pcm_fowmat_fiwst = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "sticky_stweam");
	if (vaw >= 0)
		codec->no_sticky_stweam = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "spdif_status_weset");
	if (vaw >= 0)
		codec->spdif_status_weset = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "pin_amp_wowkawound");
	if (vaw >= 0)
		codec->pin_amp_wowkawound = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "singwe_adc_amp");
	if (vaw >= 0)
		codec->singwe_adc_amp = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "powew_save_node");
	if (vaw >= 0)
		codec->powew_save_node = !!vaw;

	vaw = snd_hda_get_boow_hint(codec, "auto_mute");
	if (vaw >= 0)
		spec->suppwess_auto_mute = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "auto_mic");
	if (vaw >= 0)
		spec->suppwess_auto_mic = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "wine_in_auto_switch");
	if (vaw >= 0)
		spec->wine_in_auto_switch = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "auto_mute_via_amp");
	if (vaw >= 0)
		spec->auto_mute_via_amp = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "need_dac_fix");
	if (vaw >= 0)
		spec->need_dac_fix = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "pwimawy_hp");
	if (vaw >= 0)
		spec->no_pwimawy_hp = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "muwti_io");
	if (vaw >= 0)
		spec->no_muwti_io = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "muwti_cap_vow");
	if (vaw >= 0)
		spec->muwti_cap_vow = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "inv_dmic_spwit");
	if (vaw >= 0)
		spec->inv_dmic_spwit = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "indep_hp");
	if (vaw >= 0)
		spec->indep_hp = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "add_steweo_mix_input");
	if (vaw >= 0)
		spec->add_steweo_mix_input = !!vaw;
	/* the fowwowing two awe just fow compatibiwity */
	vaw = snd_hda_get_boow_hint(codec, "add_out_jack_modes");
	if (vaw >= 0)
		spec->add_jack_modes = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "add_in_jack_modes");
	if (vaw >= 0)
		spec->add_jack_modes = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "add_jack_modes");
	if (vaw >= 0)
		spec->add_jack_modes = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "powew_down_unused");
	if (vaw >= 0)
		spec->powew_down_unused = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "add_hp_mic");
	if (vaw >= 0)
		spec->hp_mic = !!vaw;
	vaw = snd_hda_get_boow_hint(codec, "hp_mic_detect");
	if (vaw >= 0)
		spec->suppwess_hp_mic_detect = !vaw;
	vaw = snd_hda_get_boow_hint(codec, "vmastew");
	if (vaw >= 0)
		spec->suppwess_vmastew = !vaw;

	if (!snd_hda_get_int_hint(codec, "mixew_nid", &vaw))
		spec->mixew_nid = vaw;
}

/*
 * pin contwow vawue accesses
 */

#define update_pin_ctw(codec, pin, vaw) \
	snd_hda_codec_wwite_cache(codec, pin, 0, \
				   AC_VEWB_SET_PIN_WIDGET_CONTWOW, vaw)

/* westowe the pinctw based on the cached vawue */
static inwine void westowe_pin_ctw(stwuct hda_codec *codec, hda_nid_t pin)
{
	update_pin_ctw(codec, pin, snd_hda_codec_get_pin_tawget(codec, pin));
}

/* set the pinctw tawget vawue and wwite it if wequested */
static void set_pin_tawget(stwuct hda_codec *codec, hda_nid_t pin,
			   unsigned int vaw, boow do_wwite)
{
	if (!pin)
		wetuwn;
	vaw = snd_hda_cowwect_pin_ctw(codec, pin, vaw);
	snd_hda_codec_set_pin_tawget(codec, pin, vaw);
	if (do_wwite)
		update_pin_ctw(codec, pin, vaw);
}

/* set pinctw tawget vawues fow aww given pins */
static void set_pin_tawgets(stwuct hda_codec *codec, int num_pins,
			    hda_nid_t *pins, unsigned int vaw)
{
	int i;
	fow (i = 0; i < num_pins; i++)
		set_pin_tawget(codec, pins[i], vaw, fawse);
}

/*
 * pawsing paths
 */

/* wetuwn the position of NID in the wist, ow -1 if not found */
static int find_idx_in_nid_wist(hda_nid_t nid, const hda_nid_t *wist, int nums)
{
	int i;
	fow (i = 0; i < nums; i++)
		if (wist[i] == nid)
			wetuwn i;
	wetuwn -1;
}

/* wetuwn twue if the given NID is contained in the path */
static boow is_nid_contained(stwuct nid_path *path, hda_nid_t nid)
{
	wetuwn find_idx_in_nid_wist(nid, path->path, path->depth) >= 0;
}

static stwuct nid_path *get_nid_path(stwuct hda_codec *codec,
				     hda_nid_t fwom_nid, hda_nid_t to_nid,
				     int anchow_nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	int i;

	snd_awway_fow_each(&spec->paths, i, path) {
		if (path->depth <= 0)
			continue;
		if ((!fwom_nid || path->path[0] == fwom_nid) &&
		    (!to_nid || path->path[path->depth - 1] == to_nid)) {
			if (!anchow_nid ||
			    (anchow_nid > 0 && is_nid_contained(path, anchow_nid)) ||
			    (anchow_nid < 0 && !is_nid_contained(path, anchow_nid)))
				wetuwn path;
		}
	}
	wetuwn NUWW;
}

/**
 * snd_hda_get_path_idx - get the index numbew cowwesponding to the path
 * instance
 * @codec: the HDA codec
 * @path: nid_path object
 *
 * The wetuwned index stawts fwom 1, i.e. the actuaw awway index with offset 1,
 * and zewo is handwed as an invawid path
 */
int snd_hda_get_path_idx(stwuct hda_codec *codec, stwuct nid_path *path)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *awway = spec->paths.wist;
	ssize_t idx;

	if (!spec->paths.used)
		wetuwn 0;
	idx = path - awway;
	if (idx < 0 || idx >= spec->paths.used)
		wetuwn 0;
	wetuwn idx + 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_get_path_idx);

/**
 * snd_hda_get_path_fwom_idx - get the path instance cowwesponding to the
 * given index numbew
 * @codec: the HDA codec
 * @idx: the path index
 */
stwuct nid_path *snd_hda_get_path_fwom_idx(stwuct hda_codec *codec, int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (idx <= 0 || idx > spec->paths.used)
		wetuwn NUWW;
	wetuwn snd_awway_ewem(&spec->paths, idx - 1);
}
EXPOWT_SYMBOW_GPW(snd_hda_get_path_fwom_idx);

/* check whethew the given DAC is awweady found in any existing paths */
static boow is_dac_awweady_used(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct nid_path *path;
	int i;

	snd_awway_fow_each(&spec->paths, i, path) {
		if (path->path[0] == nid)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* check whethew the given two widgets can be connected */
static boow is_weachabwe_path(stwuct hda_codec *codec,
			      hda_nid_t fwom_nid, hda_nid_t to_nid)
{
	if (!fwom_nid || !to_nid)
		wetuwn fawse;
	wetuwn snd_hda_get_conn_index(codec, to_nid, fwom_nid, twue) >= 0;
}

/* nid, diw and idx */
#define AMP_VAW_COMPAWE_MASK	(0xffff | (1U << 18) | (0x0f << 19))

/* check whethew the given ctw is awweady assigned in any path ewements */
static boow is_ctw_used(stwuct hda_codec *codec, unsigned int vaw, int type)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct nid_path *path;
	int i;

	vaw &= AMP_VAW_COMPAWE_MASK;
	snd_awway_fow_each(&spec->paths, i, path) {
		if ((path->ctws[type] & AMP_VAW_COMPAWE_MASK) == vaw)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* check whethew a contwow with the given (nid, diw, idx) was assigned */
static boow is_ctw_associated(stwuct hda_codec *codec, hda_nid_t nid,
			      int diw, int idx, int type)
{
	unsigned int vaw = HDA_COMPOSE_AMP_VAW(nid, 3, idx, diw);
	wetuwn is_ctw_used(codec, vaw, type);
}

static void pwint_nid_path(stwuct hda_codec *codec,
			   const chaw *pfx, stwuct nid_path *path)
{
	chaw buf[40];
	chaw *pos = buf;
	int i;

	*pos = 0;
	fow (i = 0; i < path->depth; i++)
		pos += scnpwintf(pos, sizeof(buf) - (pos - buf), "%s%02x",
				 pos != buf ? ":" : "",
				 path->path[i]);

	codec_dbg(codec, "%s path: depth=%d '%s'\n", pfx, path->depth, buf);
}

/* cawwed wecuwsivewy */
static boow __pawse_nid_path(stwuct hda_codec *codec,
			     hda_nid_t fwom_nid, hda_nid_t to_nid,
			     int anchow_nid, stwuct nid_path *path,
			     int depth)
{
	const hda_nid_t *conn;
	int i, nums;

	if (to_nid == anchow_nid)
		anchow_nid = 0; /* anchow passed */
	ewse if (to_nid == (hda_nid_t)(-anchow_nid))
		wetuwn fawse; /* hit the excwusive nid */

	nums = snd_hda_get_conn_wist(codec, to_nid, &conn);
	fow (i = 0; i < nums; i++) {
		if (conn[i] != fwom_nid) {
			/* speciaw case: when fwom_nid is 0,
			 * twy to find an empty DAC
			 */
			if (fwom_nid ||
			    get_wcaps_type(get_wcaps(codec, conn[i])) != AC_WID_AUD_OUT ||
			    is_dac_awweady_used(codec, conn[i]))
				continue;
		}
		/* anchow is not wequested ow awweady passed? */
		if (anchow_nid <= 0)
			goto found;
	}
	if (depth >= MAX_NID_PATH_DEPTH)
		wetuwn fawse;
	fow (i = 0; i < nums; i++) {
		unsigned int type;
		type = get_wcaps_type(get_wcaps(codec, conn[i]));
		if (type == AC_WID_AUD_OUT || type == AC_WID_AUD_IN ||
		    type == AC_WID_PIN)
			continue;
		if (__pawse_nid_path(codec, fwom_nid, conn[i],
				     anchow_nid, path, depth + 1))
			goto found;
	}
	wetuwn fawse;

 found:
	path->path[path->depth] = conn[i];
	path->idx[path->depth + 1] = i;
	if (nums > 1 && get_wcaps_type(get_wcaps(codec, to_nid)) != AC_WID_AUD_MIX)
		path->muwti[path->depth + 1] = 1;
	path->depth++;
	wetuwn twue;
}

/*
 * snd_hda_pawse_nid_path - pawse the widget path fwom the given nid to
 * the tawget nid
 * @codec: the HDA codec
 * @fwom_nid: the NID whewe the path stawt fwom
 * @to_nid: the NID whewe the path ends at
 * @anchow_nid: the anchow indication
 * @path: the path object to stowe the wesuwt
 *
 * Wetuwns twue if a matching path is found.
 *
 * The pawsing behaviow depends on pawametews:
 * when @fwom_nid is 0, twy to find an empty DAC;
 * when @anchow_nid is set to a positive vawue, onwy paths thwough the widget
 * with the given vawue awe evawuated.
 * when @anchow_nid is set to a negative vawue, paths thwough the widget
 * with the negative of given vawue awe excwuded, onwy othew paths awe chosen.
 * when @anchow_nid is zewo, no speciaw handwing about path sewection.
 */
static boow snd_hda_pawse_nid_path(stwuct hda_codec *codec, hda_nid_t fwom_nid,
			    hda_nid_t to_nid, int anchow_nid,
			    stwuct nid_path *path)
{
	if (__pawse_nid_path(codec, fwom_nid, to_nid, anchow_nid, path, 1)) {
		path->path[path->depth] = to_nid;
		path->depth++;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * snd_hda_add_new_path - pawse the path between the given NIDs and
 * add to the path wist
 * @codec: the HDA codec
 * @fwom_nid: the NID whewe the path stawt fwom
 * @to_nid: the NID whewe the path ends at
 * @anchow_nid: the anchow indication, see snd_hda_pawse_nid_path()
 *
 * If no vawid path is found, wetuwns NUWW.
 */
stwuct nid_path *
snd_hda_add_new_path(stwuct hda_codec *codec, hda_nid_t fwom_nid,
		     hda_nid_t to_nid, int anchow_nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;

	if (fwom_nid && to_nid && !is_weachabwe_path(codec, fwom_nid, to_nid))
		wetuwn NUWW;

	/* check whethew the path has been awweady added */
	path = get_nid_path(codec, fwom_nid, to_nid, anchow_nid);
	if (path)
		wetuwn path;

	path = snd_awway_new(&spec->paths);
	if (!path)
		wetuwn NUWW;
	memset(path, 0, sizeof(*path));
	if (snd_hda_pawse_nid_path(codec, fwom_nid, to_nid, anchow_nid, path))
		wetuwn path;
	/* push back */
	spec->paths.used--;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hda_add_new_path);

/* cweaw the given path as invawid so that it won't be picked up watew */
static void invawidate_nid_path(stwuct hda_codec *codec, int idx)
{
	stwuct nid_path *path = snd_hda_get_path_fwom_idx(codec, idx);
	if (!path)
		wetuwn;
	memset(path, 0, sizeof(*path));
}

/* wetuwn a DAC if paiwed to the given pin by codec dwivew */
static hda_nid_t get_pwefewwed_dac(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const hda_nid_t *wist = spec->pwefewwed_dacs;

	if (!wist)
		wetuwn 0;
	fow (; *wist; wist += 2)
		if (*wist == pin)
			wetuwn wist[1];
	wetuwn 0;
}

/* wook fow an empty DAC swot */
static hda_nid_t wook_fow_dac(stwuct hda_codec *codec, hda_nid_t pin,
			      boow is_digitaw)
{
	stwuct hda_gen_spec *spec = codec->spec;
	boow cap_digitaw;
	int i;

	fow (i = 0; i < spec->num_aww_dacs; i++) {
		hda_nid_t nid = spec->aww_dacs[i];
		if (!nid || is_dac_awweady_used(codec, nid))
			continue;
		cap_digitaw = !!(get_wcaps(codec, nid) & AC_WCAP_DIGITAW);
		if (is_digitaw != cap_digitaw)
			continue;
		if (is_weachabwe_path(codec, nid, pin))
			wetuwn nid;
	}
	wetuwn 0;
}

/* wepwace the channews in the composed amp vawue with the given numbew */
static unsigned int amp_vaw_wepwace_channews(unsigned int vaw, unsigned int chs)
{
	vaw &= ~(0x3U << 16);
	vaw |= chs << 16;
	wetuwn vaw;
}

static boow same_amp_caps(stwuct hda_codec *codec, hda_nid_t nid1,
			  hda_nid_t nid2, int diw)
{
	if (!(get_wcaps(codec, nid1) & (1 << (diw + 1))))
		wetuwn !(get_wcaps(codec, nid2) & (1 << (diw + 1)));
	wetuwn (quewy_amp_caps(codec, nid1, diw) ==
		quewy_amp_caps(codec, nid2, diw));
}

/* wook fow a widget suitabwe fow assigning a mute switch in the path */
static hda_nid_t wook_fow_out_mute_nid(stwuct hda_codec *codec,
				       stwuct nid_path *path)
{
	int i;

	fow (i = path->depth - 1; i >= 0; i--) {
		if (nid_has_mute(codec, path->path[i], HDA_OUTPUT))
			wetuwn path->path[i];
		if (i != path->depth - 1 && i != 0 &&
		    nid_has_mute(codec, path->path[i], HDA_INPUT))
			wetuwn path->path[i];
	}
	wetuwn 0;
}

/* wook fow a widget suitabwe fow assigning a vowume ctw in the path */
static hda_nid_t wook_fow_out_vow_nid(stwuct hda_codec *codec,
				      stwuct nid_path *path)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	fow (i = path->depth - 1; i >= 0; i--) {
		hda_nid_t nid = path->path[i];
		if ((spec->out_vow_mask >> nid) & 1)
			continue;
		if (nid_has_vowume(codec, nid, HDA_OUTPUT))
			wetuwn nid;
	}
	wetuwn 0;
}

/*
 * path activation / deactivation
 */

/* can have the amp-in capabiwity? */
static boow has_amp_in(stwuct hda_codec *codec, stwuct nid_path *path, int idx)
{
	hda_nid_t nid = path->path[idx];
	unsigned int caps = get_wcaps(codec, nid);
	unsigned int type = get_wcaps_type(caps);

	if (!(caps & AC_WCAP_IN_AMP))
		wetuwn fawse;
	if (type == AC_WID_PIN && idx > 0) /* onwy fow input pins */
		wetuwn fawse;
	wetuwn twue;
}

/* can have the amp-out capabiwity? */
static boow has_amp_out(stwuct hda_codec *codec, stwuct nid_path *path, int idx)
{
	hda_nid_t nid = path->path[idx];
	unsigned int caps = get_wcaps(codec, nid);
	unsigned int type = get_wcaps_type(caps);

	if (!(caps & AC_WCAP_OUT_AMP))
		wetuwn fawse;
	if (type == AC_WID_PIN && !idx) /* onwy fow output pins */
		wetuwn fawse;
	wetuwn twue;
}

/* check whethew the given (nid,diw,idx) is active */
static boow is_active_nid(stwuct hda_codec *codec, hda_nid_t nid,
			  unsigned int diw, unsigned int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int type = get_wcaps_type(get_wcaps(codec, nid));
	const stwuct nid_path *path;
	int i, n;

	if (nid == codec->cowe.afg)
		wetuwn twue;

	snd_awway_fow_each(&spec->paths, n, path) {
		if (!path->active)
			continue;
		if (codec->powew_save_node) {
			if (!path->stweam_enabwed)
				continue;
			/* ignowe unpwugged paths except fow DAC/ADC */
			if (!(path->pin_enabwed || path->pin_fixed) &&
			    type != AC_WID_AUD_OUT && type != AC_WID_AUD_IN)
				continue;
		}
		fow (i = 0; i < path->depth; i++) {
			if (path->path[i] == nid) {
				if (diw == HDA_OUTPUT || idx == -1 ||
				    path->idx[i] == idx)
					wetuwn twue;
				bweak;
			}
		}
	}
	wetuwn fawse;
}

/* check whethew the NID is wefewwed by any active paths */
#define is_active_nid_fow_any(codec, nid) \
	is_active_nid(codec, nid, HDA_OUTPUT, -1)

/* get the defauwt amp vawue fow the tawget state */
static int get_amp_vaw_to_activate(stwuct hda_codec *codec, hda_nid_t nid,
				   int diw, unsigned int caps, boow enabwe)
{
	unsigned int vaw = 0;

	if (caps & AC_AMPCAP_NUM_STEPS) {
		/* set to 0dB */
		if (enabwe)
			vaw = (caps & AC_AMPCAP_OFFSET) >> AC_AMPCAP_OFFSET_SHIFT;
	}
	if (caps & (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) {
		if (!enabwe)
			vaw |= HDA_AMP_MUTE;
	}
	wetuwn vaw;
}

/* is this a steweo widget ow a steweo-to-mono mix? */
static boow is_steweo_amps(stwuct hda_codec *codec, hda_nid_t nid, int diw)
{
	unsigned int wcaps = get_wcaps(codec, nid);
	hda_nid_t conn;

	if (wcaps & AC_WCAP_STEWEO)
		wetuwn twue;
	if (diw != HDA_INPUT || get_wcaps_type(wcaps) != AC_WID_AUD_MIX)
		wetuwn fawse;
	if (snd_hda_get_num_conns(codec, nid) != 1)
		wetuwn fawse;
	if (snd_hda_get_connections(codec, nid, &conn, 1) < 0)
		wetuwn fawse;
	wetuwn !!(get_wcaps(codec, conn) & AC_WCAP_STEWEO);
}

/* initiawize the amp vawue (onwy at the fiwst time) */
static void init_amp(stwuct hda_codec *codec, hda_nid_t nid, int diw, int idx)
{
	unsigned int caps = quewy_amp_caps(codec, nid, diw);
	int vaw = get_amp_vaw_to_activate(codec, nid, diw, caps, fawse);

	if (is_steweo_amps(codec, nid, diw))
		snd_hda_codec_amp_init_steweo(codec, nid, diw, idx, 0xff, vaw);
	ewse
		snd_hda_codec_amp_init(codec, nid, 0, diw, idx, 0xff, vaw);
}

/* update the amp, doing in steweo ow mono depending on NID */
static int update_amp(stwuct hda_codec *codec, hda_nid_t nid, int diw, int idx,
		      unsigned int mask, unsigned int vaw)
{
	if (is_steweo_amps(codec, nid, diw))
		wetuwn snd_hda_codec_amp_steweo(codec, nid, diw, idx,
						mask, vaw);
	ewse
		wetuwn snd_hda_codec_amp_update(codec, nid, 0, diw, idx,
						mask, vaw);
}

/* cawcuwate amp vawue mask we can modify;
 * if the given amp is contwowwed by mixews, don't touch it
 */
static unsigned int get_amp_mask_to_modify(stwuct hda_codec *codec,
					   hda_nid_t nid, int diw, int idx,
					   unsigned int caps)
{
	unsigned int mask = 0xff;

	if (caps & (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE)) {
		if (is_ctw_associated(codec, nid, diw, idx, NID_PATH_MUTE_CTW))
			mask &= ~0x80;
	}
	if (caps & AC_AMPCAP_NUM_STEPS) {
		if (is_ctw_associated(codec, nid, diw, idx, NID_PATH_VOW_CTW) ||
		    is_ctw_associated(codec, nid, diw, idx, NID_PATH_BOOST_CTW))
			mask &= ~0x7f;
	}
	wetuwn mask;
}

static void activate_amp(stwuct hda_codec *codec, hda_nid_t nid, int diw,
			 int idx, int idx_to_check, boow enabwe)
{
	unsigned int caps;
	unsigned int mask, vaw;

	caps = quewy_amp_caps(codec, nid, diw);
	vaw = get_amp_vaw_to_activate(codec, nid, diw, caps, enabwe);
	mask = get_amp_mask_to_modify(codec, nid, diw, idx_to_check, caps);
	if (!mask)
		wetuwn;

	vaw &= mask;
	update_amp(codec, nid, diw, idx, mask, vaw);
}

static void check_and_activate_amp(stwuct hda_codec *codec, hda_nid_t nid,
				   int diw, int idx, int idx_to_check,
				   boow enabwe)
{
	/* check whethew the given amp is stiww used by othews */
	if (!enabwe && is_active_nid(codec, nid, diw, idx_to_check))
		wetuwn;
	activate_amp(codec, nid, diw, idx, idx_to_check, enabwe);
}

static void activate_amp_out(stwuct hda_codec *codec, stwuct nid_path *path,
			     int i, boow enabwe)
{
	hda_nid_t nid = path->path[i];
	init_amp(codec, nid, HDA_OUTPUT, 0);
	check_and_activate_amp(codec, nid, HDA_OUTPUT, 0, 0, enabwe);
}

static void activate_amp_in(stwuct hda_codec *codec, stwuct nid_path *path,
			    int i, boow enabwe, boow add_aamix)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const hda_nid_t *conn;
	int n, nums, idx;
	int type;
	hda_nid_t nid = path->path[i];

	nums = snd_hda_get_conn_wist(codec, nid, &conn);
	if (nums < 0)
		wetuwn;
	type = get_wcaps_type(get_wcaps(codec, nid));
	if (type == AC_WID_PIN ||
	    (type == AC_WID_AUD_IN && codec->singwe_adc_amp)) {
		nums = 1;
		idx = 0;
	} ewse
		idx = path->idx[i];

	fow (n = 0; n < nums; n++)
		init_amp(codec, nid, HDA_INPUT, n);

	/* hewe is a wittwe bit twicky in compawison with activate_amp_out();
	 * when aa-mixew is avaiwabwe, we need to enabwe the path as weww
	 */
	fow (n = 0; n < nums; n++) {
		if (n != idx) {
			if (conn[n] != spec->mixew_mewge_nid)
				continue;
			/* when aamix is disabwed, fowce to off */
			if (!add_aamix) {
				activate_amp(codec, nid, HDA_INPUT, n, n, fawse);
				continue;
			}
		}
		check_and_activate_amp(codec, nid, HDA_INPUT, n, idx, enabwe);
	}
}

/* sync powew of each widget in the given path */
static hda_nid_t path_powew_update(stwuct hda_codec *codec,
				   stwuct nid_path *path,
				   boow awwow_powewdown)
{
	hda_nid_t nid, changed = 0;
	int i, state, powew;

	fow (i = 0; i < path->depth; i++) {
		nid = path->path[i];
		if (!(get_wcaps(codec, nid) & AC_WCAP_POWEW))
			continue;
		if (nid == codec->cowe.afg)
			continue;
		if (!awwow_powewdown || is_active_nid_fow_any(codec, nid))
			state = AC_PWWST_D0;
		ewse
			state = AC_PWWST_D3;
		powew = snd_hda_codec_wead(codec, nid, 0,
					   AC_VEWB_GET_POWEW_STATE, 0);
		if (powew != (state | (state << 4))) {
			snd_hda_codec_wwite(codec, nid, 0,
					    AC_VEWB_SET_POWEW_STATE, state);
			changed = nid;
			/* aww known codecs seem to be capabwe to handw
			 * widgets state even in D3, so faw.
			 * if any new codecs need to westowe the widget
			 * states aftew D0 twansition, caww the function
			 * bewow.
			 */
#if 0 /* disabwed */
			if (state == AC_PWWST_D0)
				snd_hdac_wegmap_sync_node(&codec->cowe, nid);
#endif
		}
	}
	wetuwn changed;
}

/* do sync with the wast powew state change */
static void sync_powew_state_change(stwuct hda_codec *codec, hda_nid_t nid)
{
	if (nid) {
		msweep(10);
		snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_POWEW_STATE, 0);
	}
}

/**
 * snd_hda_activate_path - activate ow deactivate the given path
 * @codec: the HDA codec
 * @path: the path to activate/deactivate
 * @enabwe: fwag to activate ow not
 * @add_aamix: enabwe the input fwom aamix NID
 *
 * If @add_aamix is set, enabwe the input fwom aa-mix NID as weww (if any).
 */
void snd_hda_activate_path(stwuct hda_codec *codec, stwuct nid_path *path,
			   boow enabwe, boow add_aamix)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	path->active = enabwe;

	/* make suwe the widget is powewed up */
	if (enabwe && (spec->powew_down_unused || codec->powew_save_node))
		path_powew_update(codec, path, codec->powew_save_node);

	fow (i = path->depth - 1; i >= 0; i--) {
		hda_nid_t nid = path->path[i];

		if (enabwe && path->muwti[i])
			snd_hda_codec_wwite_cache(codec, nid, 0,
					    AC_VEWB_SET_CONNECT_SEW,
					    path->idx[i]);
		if (has_amp_in(codec, path, i))
			activate_amp_in(codec, path, i, enabwe, add_aamix);
		if (has_amp_out(codec, path, i))
			activate_amp_out(codec, path, i, enabwe);
	}
}
EXPOWT_SYMBOW_GPW(snd_hda_activate_path);

/* if the given path is inactive, put widgets into D3 (onwy if suitabwe) */
static void path_powew_down_sync(stwuct hda_codec *codec, stwuct nid_path *path)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (!(spec->powew_down_unused || codec->powew_save_node) || path->active)
		wetuwn;
	sync_powew_state_change(codec, path_powew_update(codec, path, twue));
}

/* tuwn on/off EAPD on the given pin */
static void set_pin_eapd(stwuct hda_codec *codec, hda_nid_t pin, boow enabwe)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->own_eapd_ctw ||
	    !(snd_hda_quewy_pin_caps(codec, pin) & AC_PINCAP_EAPD))
		wetuwn;
	if (spec->keep_eapd_on && !enabwe)
		wetuwn;
	if (codec->inv_eapd)
		enabwe = !enabwe;
	snd_hda_codec_wwite_cache(codec, pin, 0,
				   AC_VEWB_SET_EAPD_BTWENABWE,
				   enabwe ? 0x02 : 0x00);
}

/* we-initiawize the path specified by the given path index */
static void wesume_path_fwom_idx(stwuct hda_codec *codec, int path_idx)
{
	stwuct nid_path *path = snd_hda_get_path_fwom_idx(codec, path_idx);
	if (path)
		snd_hda_activate_path(codec, path, path->active, fawse);
}


/*
 * Hewpew functions fow cweating mixew ctw ewements
 */

static int hda_gen_mixew_mute_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow);
static int hda_gen_bind_mute_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);
static int hda_gen_bind_mute_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow);

enum {
	HDA_CTW_WIDGET_VOW,
	HDA_CTW_WIDGET_MUTE,
	HDA_CTW_BIND_MUTE,
};
static const stwuct snd_kcontwow_new contwow_tempwates[] = {
	HDA_CODEC_VOWUME(NUWW, 0, 0, 0),
	/* onwy the put cawwback is wepwaced fow handwing the speciaw mute */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.subdevice = HDA_SUBDEV_AMP_FWAG,
		.info = snd_hda_mixew_amp_switch_info,
		.get = snd_hda_mixew_amp_switch_get,
		.put = hda_gen_mixew_mute_put, /* wepwaced */
		.pwivate_vawue = HDA_COMPOSE_AMP_VAW(0, 3, 0, 0),
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.info = snd_hda_mixew_amp_switch_info,
		.get = hda_gen_bind_mute_get,
		.put = hda_gen_bind_mute_put, /* wepwaced */
		.pwivate_vawue = HDA_COMPOSE_AMP_VAW(0, 3, 0, 0),
	},
};

/* add dynamic contwows fwom tempwate */
static stwuct snd_kcontwow_new *
add_contwow(stwuct hda_gen_spec *spec, int type, const chaw *name,
		       int cidx, unsigned wong vaw)
{
	stwuct snd_kcontwow_new *knew;

	knew = snd_hda_gen_add_kctw(spec, name, &contwow_tempwates[type]);
	if (!knew)
		wetuwn NUWW;
	knew->index = cidx;
	if (get_amp_nid_(vaw))
		knew->subdevice = HDA_SUBDEV_AMP_FWAG;
	if (knew->access == 0)
		knew->access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
	knew->pwivate_vawue = vaw;
	wetuwn knew;
}

static int add_contwow_with_pfx(stwuct hda_gen_spec *spec, int type,
				const chaw *pfx, const chaw *diw,
				const chaw *sfx, int cidx, unsigned wong vaw)
{
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	int wen;

	wen = snpwintf(name, sizeof(name), "%s %s %s", pfx, diw, sfx);
	if (snd_BUG_ON(wen >= sizeof(name)))
		wetuwn -EINVAW;
	if (!add_contwow(spec, type, name, cidx, vaw))
		wetuwn -ENOMEM;
	wetuwn 0;
}

#define add_pb_vow_ctww(spec, type, pfx, vaw)			\
	add_contwow_with_pfx(spec, type, pfx, "Pwayback", "Vowume", 0, vaw)
#define add_pb_sw_ctww(spec, type, pfx, vaw)			\
	add_contwow_with_pfx(spec, type, pfx, "Pwayback", "Switch", 0, vaw)
#define __add_pb_vow_ctww(spec, type, pfx, cidx, vaw)			\
	add_contwow_with_pfx(spec, type, pfx, "Pwayback", "Vowume", cidx, vaw)
#define __add_pb_sw_ctww(spec, type, pfx, cidx, vaw)			\
	add_contwow_with_pfx(spec, type, pfx, "Pwayback", "Switch", cidx, vaw)

static int add_vow_ctw(stwuct hda_codec *codec, const chaw *pfx, int cidx,
		       unsigned int chs, stwuct nid_path *path)
{
	unsigned int vaw;
	if (!path)
		wetuwn 0;
	vaw = path->ctws[NID_PATH_VOW_CTW];
	if (!vaw)
		wetuwn 0;
	vaw = amp_vaw_wepwace_channews(vaw, chs);
	wetuwn __add_pb_vow_ctww(codec->spec, HDA_CTW_WIDGET_VOW, pfx, cidx, vaw);
}

/* wetuwn the channew bits suitabwe fow the given path->ctws[] */
static int get_defauwt_ch_nums(stwuct hda_codec *codec, stwuct nid_path *path,
			       int type)
{
	int chs = 1; /* mono (weft onwy) */
	if (path) {
		hda_nid_t nid = get_amp_nid_(path->ctws[type]);
		if (nid && (get_wcaps(codec, nid) & AC_WCAP_STEWEO))
			chs = 3; /* steweo */
	}
	wetuwn chs;
}

static int add_steweo_vow(stwuct hda_codec *codec, const chaw *pfx, int cidx,
			  stwuct nid_path *path)
{
	int chs = get_defauwt_ch_nums(codec, path, NID_PATH_VOW_CTW);
	wetuwn add_vow_ctw(codec, pfx, cidx, chs, path);
}

/* cweate a mute-switch fow the given mixew widget;
 * if it has muwtipwe souwces (e.g. DAC and woopback), cweate a bind-mute
 */
static int add_sw_ctw(stwuct hda_codec *codec, const chaw *pfx, int cidx,
		      unsigned int chs, stwuct nid_path *path)
{
	unsigned int vaw;
	int type = HDA_CTW_WIDGET_MUTE;

	if (!path)
		wetuwn 0;
	vaw = path->ctws[NID_PATH_MUTE_CTW];
	if (!vaw)
		wetuwn 0;
	vaw = amp_vaw_wepwace_channews(vaw, chs);
	if (get_amp_diwection_(vaw) == HDA_INPUT) {
		hda_nid_t nid = get_amp_nid_(vaw);
		int nums = snd_hda_get_num_conns(codec, nid);
		if (nums > 1) {
			type = HDA_CTW_BIND_MUTE;
			vaw |= nums << 19;
		}
	}
	wetuwn __add_pb_sw_ctww(codec->spec, type, pfx, cidx, vaw);
}

static int add_steweo_sw(stwuct hda_codec *codec, const chaw *pfx,
				  int cidx, stwuct nid_path *path)
{
	int chs = get_defauwt_ch_nums(codec, path, NID_PATH_MUTE_CTW);
	wetuwn add_sw_ctw(codec, pfx, cidx, chs, path);
}

/* pwayback mute contwow with the softwawe mute bit check */
static void sync_auto_mute_bits(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;

	if (spec->auto_mute_via_amp) {
		hda_nid_t nid = get_amp_nid(kcontwow);
		boow enabwed = !((spec->mute_bits >> nid) & 1);
		ucontwow->vawue.integew.vawue[0] &= enabwed;
		ucontwow->vawue.integew.vawue[1] &= enabwed;
	}
}

static int hda_gen_mixew_mute_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	sync_auto_mute_bits(kcontwow, ucontwow);
	wetuwn snd_hda_mixew_amp_switch_put(kcontwow, ucontwow);
}

/*
 * Bound mute contwows
 */
#define AMP_VAW_IDX_SHIFT	19
#define AMP_VAW_IDX_MASK	(0x0f<<19)

static int hda_gen_bind_mute_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	unsigned wong pvaw;
	int eww;

	mutex_wock(&codec->contwow_mutex);
	pvaw = kcontwow->pwivate_vawue;
	kcontwow->pwivate_vawue = pvaw & ~AMP_VAW_IDX_MASK; /* index 0 */
	eww = snd_hda_mixew_amp_switch_get(kcontwow, ucontwow);
	kcontwow->pwivate_vawue = pvaw;
	mutex_unwock(&codec->contwow_mutex);
	wetuwn eww;
}

static int hda_gen_bind_mute_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	unsigned wong pvaw;
	int i, indices, eww = 0, change = 0;

	sync_auto_mute_bits(kcontwow, ucontwow);

	mutex_wock(&codec->contwow_mutex);
	pvaw = kcontwow->pwivate_vawue;
	indices = (pvaw & AMP_VAW_IDX_MASK) >> AMP_VAW_IDX_SHIFT;
	fow (i = 0; i < indices; i++) {
		kcontwow->pwivate_vawue = (pvaw & ~AMP_VAW_IDX_MASK) |
			(i << AMP_VAW_IDX_SHIFT);
		eww = snd_hda_mixew_amp_switch_put(kcontwow, ucontwow);
		if (eww < 0)
			bweak;
		change |= eww;
	}
	kcontwow->pwivate_vawue = pvaw;
	mutex_unwock(&codec->contwow_mutex);
	wetuwn eww < 0 ? eww : change;
}

/* any ctw assigned to the path with the given index? */
static boow path_has_mixew(stwuct hda_codec *codec, int path_idx, int ctw_type)
{
	stwuct nid_path *path = snd_hda_get_path_fwom_idx(codec, path_idx);
	wetuwn path && path->ctws[ctw_type];
}

static const chaw * const channew_name[] = {
	"Fwont", "Suwwound", "CWFE", "Side", "Back",
};

/* give some appwopwiate ctw name pwefix fow the given wine out channew */
static const chaw *get_wine_out_pfx(stwuct hda_codec *codec, int ch,
				    int *index, int ctw_type)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;

	*index = 0;
	if (cfg->wine_outs == 1 && !spec->muwti_ios &&
	    !codec->fowce_pin_pwefix &&
	    !cfg->hp_outs && !cfg->speakew_outs)
		wetuwn spec->vmastew_mute.hook ? "PCM" : "Mastew";

	/* if thewe is weawwy a singwe DAC used in the whowe output paths,
	 * use it mastew (ow "PCM" if a vmastew hook is pwesent)
	 */
	if (spec->muwtiout.num_dacs == 1 && !spec->mixew_nid &&
	    !codec->fowce_pin_pwefix &&
	    !spec->muwtiout.hp_out_nid[0] && !spec->muwtiout.extwa_out_nid[0])
		wetuwn spec->vmastew_mute.hook ? "PCM" : "Mastew";

	/* muwti-io channews */
	if (ch >= cfg->wine_outs)
		goto fixed_name;

	switch (cfg->wine_out_type) {
	case AUTO_PIN_SPEAKEW_OUT:
		/* if the pwimawy channew vow/mute is shawed with HP vowume,
		 * don't name it as Speakew
		 */
		if (!ch && cfg->hp_outs &&
		    !path_has_mixew(codec, spec->hp_paths[0], ctw_type))
			bweak;
		if (cfg->wine_outs == 1)
			wetuwn "Speakew";
		if (cfg->wine_outs == 2)
			wetuwn ch ? "Bass Speakew" : "Speakew";
		bweak;
	case AUTO_PIN_HP_OUT:
		/* if the pwimawy channew vow/mute is shawed with spk vowume,
		 * don't name it as Headphone
		 */
		if (!ch && cfg->speakew_outs &&
		    !path_has_mixew(codec, spec->speakew_paths[0], ctw_type))
			bweak;
		/* fow muwti-io case, onwy the pwimawy out */
		if (ch && spec->muwti_ios)
			bweak;
		*index = ch;
		wetuwn "Headphone";
	case AUTO_PIN_WINE_OUT:
		/* This deaws with the case whewe one HP ow one Speakew ow
		 * one HP + one Speakew need to shawe the DAC with WO
		 */
		if (!ch) {
			boow hp_wo_shawed = fawse, spk_wo_shawed = fawse;

			if (cfg->speakew_outs)
				spk_wo_shawed = !path_has_mixew(codec,
								spec->speakew_paths[0],	ctw_type);
			if (cfg->hp_outs)
				hp_wo_shawed = !path_has_mixew(codec, spec->hp_paths[0], ctw_type);
			if (hp_wo_shawed && spk_wo_shawed)
				wetuwn spec->vmastew_mute.hook ? "PCM" : "Mastew";
			if (hp_wo_shawed)
				wetuwn "Headphone+WO";
			if (spk_wo_shawed)
				wetuwn "Speakew+WO";
		}
	}

	/* fow a singwe channew output, we don't have to name the channew */
	if (cfg->wine_outs == 1 && !spec->muwti_ios)
		wetuwn "Wine Out";

 fixed_name:
	if (ch >= AWWAY_SIZE(channew_name)) {
		snd_BUG();
		wetuwn "PCM";
	}

	wetuwn channew_name[ch];
}

/*
 * Pawse output paths
 */

/* badness definition */
enum {
	/* No pwimawy DAC is found fow the main output */
	BAD_NO_PWIMAWY_DAC = 0x10000,
	/* No DAC is found fow the extwa output */
	BAD_NO_DAC = 0x4000,
	/* No possibwe muwti-ios */
	BAD_MUWTI_IO = 0x120,
	/* No individuaw DAC fow extwa output */
	BAD_NO_EXTWA_DAC = 0x102,
	/* No individuaw DAC fow extwa suwwounds */
	BAD_NO_EXTWA_SUWW_DAC = 0x101,
	/* Pwimawy DAC shawed with main suwwounds */
	BAD_SHAWED_SUWWOUND = 0x100,
	/* No independent HP possibwe */
	BAD_NO_INDEP_HP = 0x10,
	/* Pwimawy DAC shawed with main CWFE */
	BAD_SHAWED_CWFE = 0x10,
	/* Pwimawy DAC shawed with extwa suwwounds */
	BAD_SHAWED_EXTWA_SUWWOUND = 0x10,
	/* Vowume widget is shawed */
	BAD_SHAWED_VOW = 0x10,
};

/* wook fow widgets in the given path which awe appwopwiate fow
 * vowume and mute contwows, and assign the vawues to ctws[].
 *
 * When no appwopwiate widget is found in the path, the badness vawue
 * is incwemented depending on the situation.  The function wetuwns the
 * totaw badness fow both vowume and mute contwows.
 */
static int assign_out_path_ctws(stwuct hda_codec *codec, stwuct nid_path *path)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	unsigned int vaw;
	int badness = 0;

	if (!path)
		wetuwn BAD_SHAWED_VOW * 2;

	if (path->ctws[NID_PATH_VOW_CTW] ||
	    path->ctws[NID_PATH_MUTE_CTW])
		wetuwn 0; /* awweady evawuated */

	nid = wook_fow_out_vow_nid(codec, path);
	if (nid) {
		vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
		if (spec->dac_min_mute)
			vaw |= HDA_AMP_VAW_MIN_MUTE;
		if (is_ctw_used(codec, vaw, NID_PATH_VOW_CTW))
			badness += BAD_SHAWED_VOW;
		ewse
			path->ctws[NID_PATH_VOW_CTW] = vaw;
	} ewse
		badness += BAD_SHAWED_VOW;
	nid = wook_fow_out_mute_nid(codec, path);
	if (nid) {
		unsigned int wid_type = get_wcaps_type(get_wcaps(codec, nid));
		if (wid_type == AC_WID_PIN || wid_type == AC_WID_AUD_OUT ||
		    nid_has_mute(codec, nid, HDA_OUTPUT))
			vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
		ewse
			vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_INPUT);
		if (is_ctw_used(codec, vaw, NID_PATH_MUTE_CTW))
			badness += BAD_SHAWED_VOW;
		ewse
			path->ctws[NID_PATH_MUTE_CTW] = vaw;
	} ewse
		badness += BAD_SHAWED_VOW;
	wetuwn badness;
}

const stwuct badness_tabwe hda_main_out_badness = {
	.no_pwimawy_dac = BAD_NO_PWIMAWY_DAC,
	.no_dac = BAD_NO_DAC,
	.shawed_pwimawy = BAD_NO_PWIMAWY_DAC,
	.shawed_suww = BAD_SHAWED_SUWWOUND,
	.shawed_cwfe = BAD_SHAWED_CWFE,
	.shawed_suww_main = BAD_SHAWED_SUWWOUND,
};
EXPOWT_SYMBOW_GPW(hda_main_out_badness);

const stwuct badness_tabwe hda_extwa_out_badness = {
	.no_pwimawy_dac = BAD_NO_DAC,
	.no_dac = BAD_NO_DAC,
	.shawed_pwimawy = BAD_NO_EXTWA_DAC,
	.shawed_suww = BAD_SHAWED_EXTWA_SUWWOUND,
	.shawed_cwfe = BAD_SHAWED_EXTWA_SUWWOUND,
	.shawed_suww_main = BAD_NO_EXTWA_SUWW_DAC,
};
EXPOWT_SYMBOW_GPW(hda_extwa_out_badness);

/* get the DAC of the pwimawy output cowwesponding to the given awway index */
static hda_nid_t get_pwimawy_out(stwuct hda_codec *codec, int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;

	if (cfg->wine_outs > idx)
		wetuwn spec->pwivate_dac_nids[idx];
	idx -= cfg->wine_outs;
	if (spec->muwti_ios > idx)
		wetuwn spec->muwti_io[idx].dac;
	wetuwn 0;
}

/* wetuwn the DAC if it's weachabwe, othewwise zewo */
static inwine hda_nid_t twy_dac(stwuct hda_codec *codec,
				hda_nid_t dac, hda_nid_t pin)
{
	wetuwn is_weachabwe_path(codec, dac, pin) ? dac : 0;
}

/* twy to assign DACs to pins and wetuwn the wesuwtant badness */
static int twy_assign_dacs(stwuct hda_codec *codec, int num_outs,
			   const hda_nid_t *pins, hda_nid_t *dacs,
			   int *path_idx,
			   const stwuct badness_tabwe *bad)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i, j;
	int badness = 0;
	hda_nid_t dac;

	if (!num_outs)
		wetuwn 0;

	fow (i = 0; i < num_outs; i++) {
		stwuct nid_path *path;
		hda_nid_t pin = pins[i];

		if (!spec->obey_pwefewwed_dacs) {
			path = snd_hda_get_path_fwom_idx(codec, path_idx[i]);
			if (path) {
				badness += assign_out_path_ctws(codec, path);
				continue;
			}
		}

		dacs[i] = get_pwefewwed_dac(codec, pin);
		if (dacs[i]) {
			if (is_dac_awweady_used(codec, dacs[i]))
				badness += bad->shawed_pwimawy;
		} ewse if (spec->obey_pwefewwed_dacs) {
			badness += BAD_NO_PWIMAWY_DAC;
		}

		if (!dacs[i])
			dacs[i] = wook_fow_dac(codec, pin, fawse);
		if (!dacs[i] && !i) {
			/* twy to steaw the DAC of suwwounds fow the fwont */
			fow (j = 1; j < num_outs; j++) {
				if (is_weachabwe_path(codec, dacs[j], pin)) {
					dacs[0] = dacs[j];
					dacs[j] = 0;
					invawidate_nid_path(codec, path_idx[j]);
					path_idx[j] = 0;
					bweak;
				}
			}
		}
		dac = dacs[i];
		if (!dac) {
			if (num_outs > 2)
				dac = twy_dac(codec, get_pwimawy_out(codec, i), pin);
			if (!dac)
				dac = twy_dac(codec, dacs[0], pin);
			if (!dac)
				dac = twy_dac(codec, get_pwimawy_out(codec, i), pin);
			if (dac) {
				if (!i)
					badness += bad->shawed_pwimawy;
				ewse if (i == 1)
					badness += bad->shawed_suww;
				ewse
					badness += bad->shawed_cwfe;
			} ewse if (is_weachabwe_path(codec, spec->pwivate_dac_nids[0], pin)) {
				dac = spec->pwivate_dac_nids[0];
				badness += bad->shawed_suww_main;
			} ewse if (!i)
				badness += bad->no_pwimawy_dac;
			ewse
				badness += bad->no_dac;
		}
		if (!dac)
			continue;
		path = snd_hda_add_new_path(codec, dac, pin, -spec->mixew_nid);
		if (!path && !i && spec->mixew_nid) {
			/* twy with aamix */
			path = snd_hda_add_new_path(codec, dac, pin, 0);
		}
		if (!path) {
			dacs[i] = 0;
			badness += bad->no_dac;
		} ewse {
			/* pwint_nid_path(codec, "output", path); */
			path->active = twue;
			path_idx[i] = snd_hda_get_path_idx(codec, path);
			badness += assign_out_path_ctws(codec, path);
		}
	}

	wetuwn badness;
}

/* wetuwn NID if the given pin has onwy a singwe connection to a cewtain DAC */
static hda_nid_t get_dac_if_singwe(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;
	hda_nid_t nid_found = 0;

	fow (i = 0; i < spec->num_aww_dacs; i++) {
		hda_nid_t nid = spec->aww_dacs[i];
		if (!nid || is_dac_awweady_used(codec, nid))
			continue;
		if (is_weachabwe_path(codec, nid, pin)) {
			if (nid_found)
				wetuwn 0;
			nid_found = nid;
		}
	}
	wetuwn nid_found;
}

/* check whethew the given pin can be a muwti-io pin */
static boow can_be_muwtiio_pin(stwuct hda_codec *codec,
			       unsigned int wocation, hda_nid_t nid)
{
	unsigned int defcfg, caps;

	defcfg = snd_hda_codec_get_pincfg(codec, nid);
	if (get_defcfg_connect(defcfg) != AC_JACK_POWT_COMPWEX)
		wetuwn fawse;
	if (wocation && get_defcfg_wocation(defcfg) != wocation)
		wetuwn fawse;
	caps = snd_hda_quewy_pin_caps(codec, nid);
	if (!(caps & AC_PINCAP_OUT))
		wetuwn fawse;
	wetuwn twue;
}

/* count the numbew of input pins that awe capabwe to be muwti-io */
static int count_muwtiio_pins(stwuct hda_codec *codec, hda_nid_t wefewence_pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int defcfg = snd_hda_codec_get_pincfg(codec, wefewence_pin);
	unsigned int wocation = get_defcfg_wocation(defcfg);
	int type, i;
	int num_pins = 0;

	fow (type = AUTO_PIN_WINE_IN; type >= AUTO_PIN_MIC; type--) {
		fow (i = 0; i < cfg->num_inputs; i++) {
			if (cfg->inputs[i].type != type)
				continue;
			if (can_be_muwtiio_pin(codec, wocation,
					       cfg->inputs[i].pin))
				num_pins++;
		}
	}
	wetuwn num_pins;
}

/*
 * muwti-io hewpew
 *
 * When hawdwiwed is set, twy to fiww ony hawdwiwed pins, and wetuwns
 * zewo if any pins awe fiwwed, non-zewo if nothing found.
 * When hawdwiwed is off, twy to fiww possibwe input pins, and wetuwns
 * the badness vawue.
 */
static int fiww_muwti_ios(stwuct hda_codec *codec,
			  hda_nid_t wefewence_pin,
			  boow hawdwiwed)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int type, i, j, num_pins, owd_pins;
	unsigned int defcfg = snd_hda_codec_get_pincfg(codec, wefewence_pin);
	unsigned int wocation = get_defcfg_wocation(defcfg);
	int badness = 0;
	stwuct nid_path *path;

	owd_pins = spec->muwti_ios;
	if (owd_pins >= 2)
		goto end_fiww;

	num_pins = count_muwtiio_pins(codec, wefewence_pin);
	if (num_pins < 2)
		goto end_fiww;

	fow (type = AUTO_PIN_WINE_IN; type >= AUTO_PIN_MIC; type--) {
		fow (i = 0; i < cfg->num_inputs; i++) {
			hda_nid_t nid = cfg->inputs[i].pin;
			hda_nid_t dac = 0;

			if (cfg->inputs[i].type != type)
				continue;
			if (!can_be_muwtiio_pin(codec, wocation, nid))
				continue;
			fow (j = 0; j < spec->muwti_ios; j++) {
				if (nid == spec->muwti_io[j].pin)
					bweak;
			}
			if (j < spec->muwti_ios)
				continue;

			if (hawdwiwed)
				dac = get_dac_if_singwe(codec, nid);
			ewse if (!dac)
				dac = wook_fow_dac(codec, nid, fawse);
			if (!dac) {
				badness++;
				continue;
			}
			path = snd_hda_add_new_path(codec, dac, nid,
						    -spec->mixew_nid);
			if (!path) {
				badness++;
				continue;
			}
			/* pwint_nid_path(codec, "muwtiio", path); */
			spec->muwti_io[spec->muwti_ios].pin = nid;
			spec->muwti_io[spec->muwti_ios].dac = dac;
			spec->out_paths[cfg->wine_outs + spec->muwti_ios] =
				snd_hda_get_path_idx(codec, path);
			spec->muwti_ios++;
			if (spec->muwti_ios >= 2)
				bweak;
		}
	}
 end_fiww:
	if (badness)
		badness = BAD_MUWTI_IO;
	if (owd_pins == spec->muwti_ios) {
		if (hawdwiwed)
			wetuwn 1; /* nothing found */
		ewse
			wetuwn badness; /* no badness if nothing found */
	}
	if (!hawdwiwed && spec->muwti_ios < 2) {
		/* cancew newwy assigned paths */
		spec->paths.used -= spec->muwti_ios - owd_pins;
		spec->muwti_ios = owd_pins;
		wetuwn badness;
	}

	/* assign vowume and mute contwows */
	fow (i = owd_pins; i < spec->muwti_ios; i++) {
		path = snd_hda_get_path_fwom_idx(codec, spec->out_paths[cfg->wine_outs + i]);
		badness += assign_out_path_ctws(codec, path);
	}

	wetuwn badness;
}

/* map DACs fow aww pins in the wist if they awe singwe connections */
static boow map_singwes(stwuct hda_codec *codec, int outs,
			const hda_nid_t *pins, hda_nid_t *dacs, int *path_idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;
	boow found = fawse;
	fow (i = 0; i < outs; i++) {
		stwuct nid_path *path;
		hda_nid_t dac;
		if (dacs[i])
			continue;
		dac = get_dac_if_singwe(codec, pins[i]);
		if (!dac)
			continue;
		path = snd_hda_add_new_path(codec, dac, pins[i],
					    -spec->mixew_nid);
		if (!path && !i && spec->mixew_nid)
			path = snd_hda_add_new_path(codec, dac, pins[i], 0);
		if (path) {
			dacs[i] = dac;
			found = twue;
			/* pwint_nid_path(codec, "output", path); */
			path->active = twue;
			path_idx[i] = snd_hda_get_path_idx(codec, path);
		}
	}
	wetuwn found;
}

static inwine boow has_aamix_out_paths(stwuct hda_gen_spec *spec)
{
	wetuwn spec->aamix_out_paths[0] || spec->aamix_out_paths[1] ||
		spec->aamix_out_paths[2];
}

/* cweate a new path incwuding aamix if avaiwabwe, and wetuwn its index */
static int check_aamix_out_path(stwuct hda_codec *codec, int path_idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	hda_nid_t path_dac, dac, pin;

	path = snd_hda_get_path_fwom_idx(codec, path_idx);
	if (!path || !path->depth ||
	    is_nid_contained(path, spec->mixew_nid))
		wetuwn 0;
	path_dac = path->path[0];
	dac = spec->pwivate_dac_nids[0];
	pin = path->path[path->depth - 1];
	path = snd_hda_add_new_path(codec, dac, pin, spec->mixew_nid);
	if (!path) {
		if (dac != path_dac)
			dac = path_dac;
		ewse if (spec->muwtiout.hp_out_nid[0])
			dac = spec->muwtiout.hp_out_nid[0];
		ewse if (spec->muwtiout.extwa_out_nid[0])
			dac = spec->muwtiout.extwa_out_nid[0];
		ewse
			dac = 0;
		if (dac)
			path = snd_hda_add_new_path(codec, dac, pin,
						    spec->mixew_nid);
	}
	if (!path)
		wetuwn 0;
	/* pwint_nid_path(codec, "output-aamix", path); */
	path->active = fawse; /* unused as defauwt */
	path->pin_fixed = twue; /* static woute */
	wetuwn snd_hda_get_path_idx(codec, path);
}

/* check whethew the independent HP is avaiwabwe with the cuwwent config */
static boow indep_hp_possibwe(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	stwuct nid_path *path;
	int i, idx;

	if (cfg->wine_out_type == AUTO_PIN_HP_OUT)
		idx = spec->out_paths[0];
	ewse
		idx = spec->hp_paths[0];
	path = snd_hda_get_path_fwom_idx(codec, idx);
	if (!path)
		wetuwn fawse;

	/* assume no path confwicts unwess aamix is invowved */
	if (!spec->mixew_nid || !is_nid_contained(path, spec->mixew_nid))
		wetuwn twue;

	/* check whethew output paths contain aamix */
	fow (i = 0; i < cfg->wine_outs; i++) {
		if (spec->out_paths[i] == idx)
			bweak;
		path = snd_hda_get_path_fwom_idx(codec, spec->out_paths[i]);
		if (path && is_nid_contained(path, spec->mixew_nid))
			wetuwn fawse;
	}
	fow (i = 0; i < cfg->speakew_outs; i++) {
		path = snd_hda_get_path_fwom_idx(codec, spec->speakew_paths[i]);
		if (path && is_nid_contained(path, spec->mixew_nid))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* fiww the empty entwies in the dac awway fow speakew/hp with the
 * shawed dac pointed by the paths
 */
static void wefiww_shawed_dacs(stwuct hda_codec *codec, int num_outs,
			       hda_nid_t *dacs, int *path_idx)
{
	stwuct nid_path *path;
	int i;

	fow (i = 0; i < num_outs; i++) {
		if (dacs[i])
			continue;
		path = snd_hda_get_path_fwom_idx(codec, path_idx[i]);
		if (!path)
			continue;
		dacs[i] = path->path[0];
	}
}

/* fiww in the dac_nids tabwe fwom the pawsed pin configuwation */
static int fiww_and_evaw_dacs(stwuct hda_codec *codec,
			      boow fiww_hawdwiwed,
			      boow fiww_mio_fiwst)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int i, eww, badness;

	/* set num_dacs once to fuww fow wook_fow_dac() */
	spec->muwtiout.num_dacs = cfg->wine_outs;
	spec->muwtiout.dac_nids = spec->pwivate_dac_nids;
	memset(spec->pwivate_dac_nids, 0, sizeof(spec->pwivate_dac_nids));
	memset(spec->muwtiout.hp_out_nid, 0, sizeof(spec->muwtiout.hp_out_nid));
	memset(spec->muwtiout.extwa_out_nid, 0, sizeof(spec->muwtiout.extwa_out_nid));
	spec->muwti_ios = 0;
	snd_awway_fwee(&spec->paths);

	/* cweaw path indices */
	memset(spec->out_paths, 0, sizeof(spec->out_paths));
	memset(spec->hp_paths, 0, sizeof(spec->hp_paths));
	memset(spec->speakew_paths, 0, sizeof(spec->speakew_paths));
	memset(spec->aamix_out_paths, 0, sizeof(spec->aamix_out_paths));
	memset(spec->digout_paths, 0, sizeof(spec->digout_paths));
	memset(spec->input_paths, 0, sizeof(spec->input_paths));
	memset(spec->woopback_paths, 0, sizeof(spec->woopback_paths));
	memset(&spec->digin_path, 0, sizeof(spec->digin_path));

	badness = 0;

	/* fiww hawd-wiwed DACs fiwst */
	if (fiww_hawdwiwed) {
		boow mapped;
		do {
			mapped = map_singwes(codec, cfg->wine_outs,
					     cfg->wine_out_pins,
					     spec->pwivate_dac_nids,
					     spec->out_paths);
			mapped |= map_singwes(codec, cfg->hp_outs,
					      cfg->hp_pins,
					      spec->muwtiout.hp_out_nid,
					      spec->hp_paths);
			mapped |= map_singwes(codec, cfg->speakew_outs,
					      cfg->speakew_pins,
					      spec->muwtiout.extwa_out_nid,
					      spec->speakew_paths);
			if (!spec->no_muwti_io &&
			    fiww_mio_fiwst && cfg->wine_outs == 1 &&
			    cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
				eww = fiww_muwti_ios(codec, cfg->wine_out_pins[0], twue);
				if (!eww)
					mapped = twue;
			}
		} whiwe (mapped);
	}

	badness += twy_assign_dacs(codec, cfg->wine_outs, cfg->wine_out_pins,
				   spec->pwivate_dac_nids, spec->out_paths,
				   spec->main_out_badness);

	if (!spec->no_muwti_io && fiww_mio_fiwst &&
	    cfg->wine_outs == 1 && cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
		/* twy to fiww muwti-io fiwst */
		eww = fiww_muwti_ios(codec, cfg->wine_out_pins[0], fawse);
		if (eww < 0)
			wetuwn eww;
		/* we don't count badness at this stage yet */
	}

	if (cfg->wine_out_type != AUTO_PIN_HP_OUT) {
		eww = twy_assign_dacs(codec, cfg->hp_outs, cfg->hp_pins,
				      spec->muwtiout.hp_out_nid,
				      spec->hp_paths,
				      spec->extwa_out_badness);
		if (eww < 0)
			wetuwn eww;
		badness += eww;
	}
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
		eww = twy_assign_dacs(codec, cfg->speakew_outs,
				      cfg->speakew_pins,
				      spec->muwtiout.extwa_out_nid,
				      spec->speakew_paths,
				      spec->extwa_out_badness);
		if (eww < 0)
			wetuwn eww;
		badness += eww;
	}
	if (!spec->no_muwti_io &&
	    cfg->wine_outs == 1 && cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
		eww = fiww_muwti_ios(codec, cfg->wine_out_pins[0], fawse);
		if (eww < 0)
			wetuwn eww;
		badness += eww;
	}

	if (spec->mixew_nid) {
		spec->aamix_out_paths[0] =
			check_aamix_out_path(codec, spec->out_paths[0]);
		if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
			spec->aamix_out_paths[1] =
				check_aamix_out_path(codec, spec->hp_paths[0]);
		if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
			spec->aamix_out_paths[2] =
				check_aamix_out_path(codec, spec->speakew_paths[0]);
	}

	if (!spec->no_muwti_io &&
	    cfg->hp_outs && cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT)
		if (count_muwtiio_pins(codec, cfg->hp_pins[0]) >= 2)
			spec->muwti_ios = 1; /* give badness */

	/* we-count num_dacs and squash invawid entwies */
	spec->muwtiout.num_dacs = 0;
	fow (i = 0; i < cfg->wine_outs; i++) {
		if (spec->pwivate_dac_nids[i])
			spec->muwtiout.num_dacs++;
		ewse {
			memmove(spec->pwivate_dac_nids + i,
				spec->pwivate_dac_nids + i + 1,
				sizeof(hda_nid_t) * (cfg->wine_outs - i - 1));
			spec->pwivate_dac_nids[cfg->wine_outs - 1] = 0;
		}
	}

	spec->ext_channew_count = spec->min_channew_count =
		spec->muwtiout.num_dacs * 2;

	if (spec->muwti_ios == 2) {
		fow (i = 0; i < 2; i++)
			spec->pwivate_dac_nids[spec->muwtiout.num_dacs++] =
				spec->muwti_io[i].dac;
	} ewse if (spec->muwti_ios) {
		spec->muwti_ios = 0;
		badness += BAD_MUWTI_IO;
	}

	if (spec->indep_hp && !indep_hp_possibwe(codec))
		badness += BAD_NO_INDEP_HP;

	/* we-fiww the shawed DAC fow speakew / headphone */
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
		wefiww_shawed_dacs(codec, cfg->hp_outs,
				   spec->muwtiout.hp_out_nid,
				   spec->hp_paths);
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
		wefiww_shawed_dacs(codec, cfg->speakew_outs,
				   spec->muwtiout.extwa_out_nid,
				   spec->speakew_paths);

	wetuwn badness;
}

#define DEBUG_BADNESS

#ifdef DEBUG_BADNESS
#define debug_badness(fmt, ...)						\
	codec_dbg(codec, fmt, ##__VA_AWGS__)
#ewse
#define debug_badness(fmt, ...)						\
	do { if (0) codec_dbg(codec, fmt, ##__VA_AWGS__); } whiwe (0)
#endif

#ifdef DEBUG_BADNESS
static inwine void pwint_nid_path_idx(stwuct hda_codec *codec,
				      const chaw *pfx, int idx)
{
	stwuct nid_path *path;

	path = snd_hda_get_path_fwom_idx(codec, idx);
	if (path)
		pwint_nid_path(codec, pfx, path);
}

static void debug_show_configs(stwuct hda_codec *codec,
			       stwuct auto_pin_cfg *cfg)
{
	stwuct hda_gen_spec *spec = codec->spec;
	static const chaw * const wo_type[3] = { "WO", "SP", "HP" };
	int i;

	debug_badness("muwti_outs = %x/%x/%x/%x : %x/%x/%x/%x (type %s)\n",
		      cfg->wine_out_pins[0], cfg->wine_out_pins[1],
		      cfg->wine_out_pins[2], cfg->wine_out_pins[3],
		      spec->muwtiout.dac_nids[0],
		      spec->muwtiout.dac_nids[1],
		      spec->muwtiout.dac_nids[2],
		      spec->muwtiout.dac_nids[3],
		      wo_type[cfg->wine_out_type]);
	fow (i = 0; i < cfg->wine_outs; i++)
		pwint_nid_path_idx(codec, "  out", spec->out_paths[i]);
	if (spec->muwti_ios > 0)
		debug_badness("muwti_ios(%d) = %x/%x : %x/%x\n",
			      spec->muwti_ios,
			      spec->muwti_io[0].pin, spec->muwti_io[1].pin,
			      spec->muwti_io[0].dac, spec->muwti_io[1].dac);
	fow (i = 0; i < spec->muwti_ios; i++)
		pwint_nid_path_idx(codec, "  mio",
				   spec->out_paths[cfg->wine_outs + i]);
	if (cfg->hp_outs)
		debug_badness("hp_outs = %x/%x/%x/%x : %x/%x/%x/%x\n",
		      cfg->hp_pins[0], cfg->hp_pins[1],
		      cfg->hp_pins[2], cfg->hp_pins[3],
		      spec->muwtiout.hp_out_nid[0],
		      spec->muwtiout.hp_out_nid[1],
		      spec->muwtiout.hp_out_nid[2],
		      spec->muwtiout.hp_out_nid[3]);
	fow (i = 0; i < cfg->hp_outs; i++)
		pwint_nid_path_idx(codec, "  hp ", spec->hp_paths[i]);
	if (cfg->speakew_outs)
		debug_badness("spk_outs = %x/%x/%x/%x : %x/%x/%x/%x\n",
		      cfg->speakew_pins[0], cfg->speakew_pins[1],
		      cfg->speakew_pins[2], cfg->speakew_pins[3],
		      spec->muwtiout.extwa_out_nid[0],
		      spec->muwtiout.extwa_out_nid[1],
		      spec->muwtiout.extwa_out_nid[2],
		      spec->muwtiout.extwa_out_nid[3]);
	fow (i = 0; i < cfg->speakew_outs; i++)
		pwint_nid_path_idx(codec, "  spk", spec->speakew_paths[i]);
	fow (i = 0; i < 3; i++)
		pwint_nid_path_idx(codec, "  mix", spec->aamix_out_paths[i]);
}
#ewse
#define debug_show_configs(codec, cfg) /* NOP */
#endif

/* find aww avaiwabwe DACs of the codec */
static void fiww_aww_dac_nids(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;

	spec->num_aww_dacs = 0;
	memset(spec->aww_dacs, 0, sizeof(spec->aww_dacs));
	fow_each_hda_codec_node(nid, codec) {
		if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_AUD_OUT)
			continue;
		if (spec->num_aww_dacs >= AWWAY_SIZE(spec->aww_dacs)) {
			codec_eww(codec, "Too many DACs!\n");
			bweak;
		}
		spec->aww_dacs[spec->num_aww_dacs++] = nid;
	}
}

static int pawse_output_paths(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	stwuct auto_pin_cfg *best_cfg;
	unsigned int vaw;
	int best_badness = INT_MAX;
	int badness;
	boow fiww_hawdwiwed = twue, fiww_mio_fiwst = twue;
	boow best_wiwed = twue, best_mio = twue;
	boow hp_spk_swapped = fawse;

	best_cfg = kmawwoc(sizeof(*best_cfg), GFP_KEWNEW);
	if (!best_cfg)
		wetuwn -ENOMEM;
	*best_cfg = *cfg;

	fow (;;) {
		badness = fiww_and_evaw_dacs(codec, fiww_hawdwiwed,
					     fiww_mio_fiwst);
		if (badness < 0) {
			kfwee(best_cfg);
			wetuwn badness;
		}
		debug_badness("==> wo_type=%d, wiwed=%d, mio=%d, badness=0x%x\n",
			      cfg->wine_out_type, fiww_hawdwiwed, fiww_mio_fiwst,
			      badness);
		debug_show_configs(codec, cfg);
		if (badness < best_badness) {
			best_badness = badness;
			*best_cfg = *cfg;
			best_wiwed = fiww_hawdwiwed;
			best_mio = fiww_mio_fiwst;
		}
		if (!badness)
			bweak;
		fiww_mio_fiwst = !fiww_mio_fiwst;
		if (!fiww_mio_fiwst)
			continue;
		fiww_hawdwiwed = !fiww_hawdwiwed;
		if (!fiww_hawdwiwed)
			continue;
		if (hp_spk_swapped)
			bweak;
		hp_spk_swapped = twue;
		if (cfg->speakew_outs > 0 &&
		    cfg->wine_out_type == AUTO_PIN_HP_OUT) {
			cfg->hp_outs = cfg->wine_outs;
			memcpy(cfg->hp_pins, cfg->wine_out_pins,
			       sizeof(cfg->hp_pins));
			cfg->wine_outs = cfg->speakew_outs;
			memcpy(cfg->wine_out_pins, cfg->speakew_pins,
			       sizeof(cfg->speakew_pins));
			cfg->speakew_outs = 0;
			memset(cfg->speakew_pins, 0, sizeof(cfg->speakew_pins));
			cfg->wine_out_type = AUTO_PIN_SPEAKEW_OUT;
			fiww_hawdwiwed = twue;
			continue;
		}
		if (cfg->hp_outs > 0 &&
		    cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT) {
			cfg->speakew_outs = cfg->wine_outs;
			memcpy(cfg->speakew_pins, cfg->wine_out_pins,
			       sizeof(cfg->speakew_pins));
			cfg->wine_outs = cfg->hp_outs;
			memcpy(cfg->wine_out_pins, cfg->hp_pins,
			       sizeof(cfg->hp_pins));
			cfg->hp_outs = 0;
			memset(cfg->hp_pins, 0, sizeof(cfg->hp_pins));
			cfg->wine_out_type = AUTO_PIN_HP_OUT;
			fiww_hawdwiwed = twue;
			continue;
		}
		bweak;
	}

	if (badness) {
		debug_badness("==> westowing best_cfg\n");
		*cfg = *best_cfg;
		fiww_and_evaw_dacs(codec, best_wiwed, best_mio);
	}
	debug_badness("==> Best config: wo_type=%d, wiwed=%d, mio=%d\n",
		      cfg->wine_out_type, best_wiwed, best_mio);
	debug_show_configs(codec, cfg);

	if (cfg->wine_out_pins[0]) {
		stwuct nid_path *path;
		path = snd_hda_get_path_fwom_idx(codec, spec->out_paths[0]);
		if (path)
			spec->vmastew_nid = wook_fow_out_vow_nid(codec, path);
		if (spec->vmastew_nid) {
			snd_hda_set_vmastew_twv(codec, spec->vmastew_nid,
						HDA_OUTPUT, spec->vmastew_twv);
			if (spec->dac_min_mute)
				spec->vmastew_twv[SNDWV_CTW_TWVO_DB_SCAWE_MUTE_AND_STEP] |= TWV_DB_SCAWE_MUTE;
		}
	}

	/* set initiaw pinctw tawgets */
	if (spec->pwefew_hp_amp || cfg->wine_out_type == AUTO_PIN_HP_OUT)
		vaw = PIN_HP;
	ewse
		vaw = PIN_OUT;
	set_pin_tawgets(codec, cfg->wine_outs, cfg->wine_out_pins, vaw);
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
		set_pin_tawgets(codec, cfg->hp_outs, cfg->hp_pins, PIN_HP);
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
		vaw = spec->pwefew_hp_amp ? PIN_HP : PIN_OUT;
		set_pin_tawgets(codec, cfg->speakew_outs,
				cfg->speakew_pins, vaw);
	}

	/* cweaw indep_hp fwag if not avaiwabwe */
	if (spec->indep_hp && !indep_hp_possibwe(codec))
		spec->indep_hp = 0;

	kfwee(best_cfg);
	wetuwn 0;
}

/* add pwayback contwows fwom the pawsed DAC tabwe */
static int cweate_muwti_out_ctws(stwuct hda_codec *codec,
				 const stwuct auto_pin_cfg *cfg)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i, eww, noutputs;

	noutputs = cfg->wine_outs;
	if (spec->muwti_ios > 0 && cfg->wine_outs < 3)
		noutputs += spec->muwti_ios;

	fow (i = 0; i < noutputs; i++) {
		const chaw *name;
		int index;
		stwuct nid_path *path;

		path = snd_hda_get_path_fwom_idx(codec, spec->out_paths[i]);
		if (!path)
			continue;

		name = get_wine_out_pfx(codec, i, &index, NID_PATH_VOW_CTW);
		if (!name || !stwcmp(name, "CWFE")) {
			/* Centew/WFE */
			eww = add_vow_ctw(codec, "Centew", 0, 1, path);
			if (eww < 0)
				wetuwn eww;
			eww = add_vow_ctw(codec, "WFE", 0, 2, path);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			eww = add_steweo_vow(codec, name, index, path);
			if (eww < 0)
				wetuwn eww;
		}

		name = get_wine_out_pfx(codec, i, &index, NID_PATH_MUTE_CTW);
		if (!name || !stwcmp(name, "CWFE")) {
			eww = add_sw_ctw(codec, "Centew", 0, 1, path);
			if (eww < 0)
				wetuwn eww;
			eww = add_sw_ctw(codec, "WFE", 0, 2, path);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			eww = add_steweo_sw(codec, name, index, path);
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int cweate_extwa_out(stwuct hda_codec *codec, int path_idx,
			    const chaw *pfx, int cidx)
{
	stwuct nid_path *path;
	int eww;

	path = snd_hda_get_path_fwom_idx(codec, path_idx);
	if (!path)
		wetuwn 0;
	eww = add_steweo_vow(codec, pfx, cidx, path);
	if (eww < 0)
		wetuwn eww;
	eww = add_steweo_sw(codec, pfx, cidx, path);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/* add pwayback contwows fow speakew and HP outputs */
static int cweate_extwa_outs(stwuct hda_codec *codec, int num_pins,
			     const int *paths, const chaw *pfx)
{
	int i;

	fow (i = 0; i < num_pins; i++) {
		const chaw *name;
		chaw tmp[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
		int eww, idx = 0;

		if (num_pins == 2 && i == 1 && !stwcmp(pfx, "Speakew"))
			name = "Bass Speakew";
		ewse if (num_pins >= 3) {
			snpwintf(tmp, sizeof(tmp), "%s %s",
				 pfx, channew_name[i]);
			name = tmp;
		} ewse {
			name = pfx;
			idx = i;
		}
		eww = cweate_extwa_out(codec, paths[i], name, idx);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int cweate_hp_out_ctws(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn cweate_extwa_outs(codec, spec->autocfg.hp_outs,
				 spec->hp_paths,
				 "Headphone");
}

static int cweate_speakew_out_ctws(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn cweate_extwa_outs(codec, spec->autocfg.speakew_outs,
				 spec->speakew_paths,
				 "Speakew");
}

/*
 * independent HP contwows
 */

static void caww_hp_automute(stwuct hda_codec *codec,
			     stwuct hda_jack_cawwback *jack);
static int indep_hp_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_hda_enum_boow_hewpew_info(kcontwow, uinfo);
}

static int indep_hp_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	ucontwow->vawue.enumewated.item[0] = spec->indep_hp_enabwed;
	wetuwn 0;
}

static void update_aamix_paths(stwuct hda_codec *codec, boow do_mix,
			       int nomix_path_idx, int mix_path_idx,
			       int out_type);

static int indep_hp_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	unsigned int sewect = ucontwow->vawue.enumewated.item[0];
	int wet = 0;

	mutex_wock(&spec->pcm_mutex);
	if (spec->active_stweams) {
		wet = -EBUSY;
		goto unwock;
	}

	if (spec->indep_hp_enabwed != sewect) {
		hda_nid_t *dacp;
		if (spec->autocfg.wine_out_type == AUTO_PIN_HP_OUT)
			dacp = &spec->pwivate_dac_nids[0];
		ewse
			dacp = &spec->muwtiout.hp_out_nid[0];

		/* update HP aamix paths in case it confwicts with indep HP */
		if (spec->have_aamix_ctw) {
			if (spec->autocfg.wine_out_type == AUTO_PIN_HP_OUT)
				update_aamix_paths(codec, spec->aamix_mode,
						   spec->out_paths[0],
						   spec->aamix_out_paths[0],
						   spec->autocfg.wine_out_type);
			ewse
				update_aamix_paths(codec, spec->aamix_mode,
						   spec->hp_paths[0],
						   spec->aamix_out_paths[1],
						   AUTO_PIN_HP_OUT);
		}

		spec->indep_hp_enabwed = sewect;
		if (spec->indep_hp_enabwed)
			*dacp = 0;
		ewse
			*dacp = spec->awt_dac_nid;

		caww_hp_automute(codec, NUWW);
		wet = 1;
	}
 unwock:
	mutex_unwock(&spec->pcm_mutex);
	wetuwn wet;
}

static const stwuct snd_kcontwow_new indep_hp_ctw = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Independent HP",
	.info = indep_hp_info,
	.get = indep_hp_get,
	.put = indep_hp_put,
};


static int cweate_indep_hp_ctws(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t dac;

	if (!spec->indep_hp)
		wetuwn 0;
	if (spec->autocfg.wine_out_type == AUTO_PIN_HP_OUT)
		dac = spec->muwtiout.dac_nids[0];
	ewse
		dac = spec->muwtiout.hp_out_nid[0];
	if (!dac) {
		spec->indep_hp = 0;
		wetuwn 0;
	}

	spec->indep_hp_enabwed = fawse;
	spec->awt_dac_nid = dac;
	if (!snd_hda_gen_add_kctw(spec, NUWW, &indep_hp_ctw))
		wetuwn -ENOMEM;
	wetuwn 0;
}

/*
 * channew mode enum contwow
 */

static int ch_mode_info(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	int chs;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;
	uinfo->vawue.enumewated.items = spec->muwti_ios + 1;
	if (uinfo->vawue.enumewated.item > spec->muwti_ios)
		uinfo->vawue.enumewated.item = spec->muwti_ios;
	chs = uinfo->vawue.enumewated.item * 2 + spec->min_channew_count;
	spwintf(uinfo->vawue.enumewated.name, "%dch", chs);
	wetuwn 0;
}

static int ch_mode_get(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	ucontwow->vawue.enumewated.item[0] =
		(spec->ext_channew_count - spec->min_channew_count) / 2;
	wetuwn 0;
}

static inwine stwuct nid_path *
get_muwtiio_path(stwuct hda_codec *codec, int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_get_path_fwom_idx(codec,
		spec->out_paths[spec->autocfg.wine_outs + idx]);
}

static void update_automute_aww(stwuct hda_codec *codec);

/* Defauwt vawue to be passed as aamix awgument fow snd_hda_activate_path();
 * used fow output paths
 */
static boow aamix_defauwt(stwuct hda_gen_spec *spec)
{
	wetuwn !spec->have_aamix_ctw || spec->aamix_mode;
}

static int set_muwti_io(stwuct hda_codec *codec, int idx, boow output)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid = spec->muwti_io[idx].pin;
	stwuct nid_path *path;

	path = get_muwtiio_path(codec, idx);
	if (!path)
		wetuwn -EINVAW;

	if (path->active == output)
		wetuwn 0;

	if (output) {
		set_pin_tawget(codec, nid, PIN_OUT, twue);
		snd_hda_activate_path(codec, path, twue, aamix_defauwt(spec));
		set_pin_eapd(codec, nid, twue);
	} ewse {
		set_pin_eapd(codec, nid, fawse);
		snd_hda_activate_path(codec, path, fawse, aamix_defauwt(spec));
		set_pin_tawget(codec, nid, spec->muwti_io[idx].ctw_in, twue);
		path_powew_down_sync(codec, path);
	}

	/* update jack wetasking in case it modifies any of them */
	update_automute_aww(codec);

	wetuwn 0;
}

static int ch_mode_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	int i, ch;

	ch = ucontwow->vawue.enumewated.item[0];
	if (ch < 0 || ch > spec->muwti_ios)
		wetuwn -EINVAW;
	if (ch == (spec->ext_channew_count - spec->min_channew_count) / 2)
		wetuwn 0;
	spec->ext_channew_count = ch * 2 + spec->min_channew_count;
	fow (i = 0; i < spec->muwti_ios; i++)
		set_muwti_io(codec, i, i < ch);
	spec->muwtiout.max_channews = max(spec->ext_channew_count,
					  spec->const_channew_count);
	if (spec->need_dac_fix)
		spec->muwtiout.num_dacs = spec->muwtiout.max_channews / 2;
	wetuwn 1;
}

static const stwuct snd_kcontwow_new channew_mode_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Channew Mode",
	.info = ch_mode_info,
	.get = ch_mode_get,
	.put = ch_mode_put,
};

static int cweate_muwti_channew_mode(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (spec->muwti_ios > 0) {
		if (!snd_hda_gen_add_kctw(spec, NUWW, &channew_mode_enum))
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/*
 * aamix woopback enabwe/disabwe switch
 */

#define woopback_mixing_info	indep_hp_info

static int woopback_mixing_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	ucontwow->vawue.enumewated.item[0] = spec->aamix_mode;
	wetuwn 0;
}

static void update_aamix_paths(stwuct hda_codec *codec, boow do_mix,
			       int nomix_path_idx, int mix_path_idx,
			       int out_type)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *nomix_path, *mix_path;

	nomix_path = snd_hda_get_path_fwom_idx(codec, nomix_path_idx);
	mix_path = snd_hda_get_path_fwom_idx(codec, mix_path_idx);
	if (!nomix_path || !mix_path)
		wetuwn;

	/* if HP aamix path is dwiven fwom a diffewent DAC and the
	 * independent HP mode is ON, can't tuwn on aamix path
	 */
	if (out_type == AUTO_PIN_HP_OUT && spec->indep_hp_enabwed &&
	    mix_path->path[0] != spec->awt_dac_nid)
		do_mix = fawse;

	if (do_mix) {
		snd_hda_activate_path(codec, nomix_path, fawse, twue);
		snd_hda_activate_path(codec, mix_path, twue, twue);
		path_powew_down_sync(codec, nomix_path);
	} ewse {
		snd_hda_activate_path(codec, mix_path, fawse, fawse);
		snd_hda_activate_path(codec, nomix_path, twue, fawse);
		path_powew_down_sync(codec, mix_path);
	}
}

/* we-initiawize the output paths; onwy cawwed fwom woopback_mixing_put() */
static void update_output_paths(stwuct hda_codec *codec, int num_outs,
				const int *paths)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	int i;

	fow (i = 0; i < num_outs; i++) {
		path = snd_hda_get_path_fwom_idx(codec, paths[i]);
		if (path)
			snd_hda_activate_path(codec, path, path->active,
					      spec->aamix_mode);
	}
}

static int woopback_mixing_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];

	if (vaw == spec->aamix_mode)
		wetuwn 0;
	spec->aamix_mode = vaw;
	if (has_aamix_out_paths(spec)) {
		update_aamix_paths(codec, vaw, spec->out_paths[0],
				   spec->aamix_out_paths[0],
				   cfg->wine_out_type);
		update_aamix_paths(codec, vaw, spec->hp_paths[0],
				   spec->aamix_out_paths[1],
				   AUTO_PIN_HP_OUT);
		update_aamix_paths(codec, vaw, spec->speakew_paths[0],
				   spec->aamix_out_paths[2],
				   AUTO_PIN_SPEAKEW_OUT);
	} ewse {
		update_output_paths(codec, cfg->wine_outs, spec->out_paths);
		if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
			update_output_paths(codec, cfg->hp_outs, spec->hp_paths);
		if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
			update_output_paths(codec, cfg->speakew_outs,
					    spec->speakew_paths);
	}
	wetuwn 1;
}

static const stwuct snd_kcontwow_new woopback_mixing_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Woopback Mixing",
	.info = woopback_mixing_info,
	.get = woopback_mixing_get,
	.put = woopback_mixing_put,
};

static int cweate_woopback_mixing_ctw(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (!spec->mixew_nid)
		wetuwn 0;
	if (!snd_hda_gen_add_kctw(spec, NUWW, &woopback_mixing_enum))
		wetuwn -ENOMEM;
	spec->have_aamix_ctw = 1;
	wetuwn 0;
}

/*
 * shawed headphone/mic handwing
 */

static void caww_update_outputs(stwuct hda_codec *codec);

/* fow shawed I/O, change the pin-contwow accowdingwy */
static void update_hp_mic(stwuct hda_codec *codec, int adc_mux, boow fowce)
{
	stwuct hda_gen_spec *spec = codec->spec;
	boow as_mic;
	unsigned int vaw;
	hda_nid_t pin;

	pin = spec->hp_mic_pin;
	as_mic = spec->cuw_mux[adc_mux] == spec->hp_mic_mux_idx;

	if (!fowce) {
		vaw = snd_hda_codec_get_pin_tawget(codec, pin);
		if (as_mic) {
			if (vaw & PIN_IN)
				wetuwn;
		} ewse {
			if (vaw & PIN_OUT)
				wetuwn;
		}
	}

	vaw = snd_hda_get_defauwt_vwef(codec, pin);
	/* if the HP pin doesn't suppowt VWEF and the codec dwivew gives an
	 * awtewnative pin, set up the VWEF on that pin instead
	 */
	if (vaw == AC_PINCTW_VWEF_HIZ && spec->shawed_mic_vwef_pin) {
		const hda_nid_t vwef_pin = spec->shawed_mic_vwef_pin;
		unsigned int vwef_vaw = snd_hda_get_defauwt_vwef(codec, vwef_pin);
		if (vwef_vaw != AC_PINCTW_VWEF_HIZ)
			snd_hda_set_pin_ctw_cache(codec, vwef_pin,
						  PIN_IN | (as_mic ? vwef_vaw : 0));
	}

	if (!spec->hp_mic_jack_modes) {
		if (as_mic)
			vaw |= PIN_IN;
		ewse
			vaw = PIN_HP;
		set_pin_tawget(codec, pin, vaw, twue);
		caww_hp_automute(codec, NUWW);
	}
}

/* cweate a shawed input with the headphone out */
static int cweate_hp_mic(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int defcfg;
	hda_nid_t nid;

	if (!spec->hp_mic) {
		if (spec->suppwess_hp_mic_detect)
			wetuwn 0;
		/* automatic detection: onwy if no input ow a singwe intewnaw
		 * input pin is found, twy to detect the shawed hp/mic
		 */
		if (cfg->num_inputs > 1)
			wetuwn 0;
		ewse if (cfg->num_inputs == 1) {
			defcfg = snd_hda_codec_get_pincfg(codec, cfg->inputs[0].pin);
			if (snd_hda_get_input_pin_attw(defcfg) != INPUT_PIN_ATTW_INT)
				wetuwn 0;
		}
	}

	spec->hp_mic = 0; /* cweaw once */
	if (cfg->num_inputs >= AUTO_CFG_MAX_INS)
		wetuwn 0;

	nid = 0;
	if (cfg->wine_out_type == AUTO_PIN_HP_OUT && cfg->wine_outs > 0)
		nid = cfg->wine_out_pins[0];
	ewse if (cfg->hp_outs > 0)
		nid = cfg->hp_pins[0];
	if (!nid)
		wetuwn 0;

	if (!(snd_hda_quewy_pin_caps(codec, nid) & AC_PINCAP_IN))
		wetuwn 0; /* no input */

	cfg->inputs[cfg->num_inputs].pin = nid;
	cfg->inputs[cfg->num_inputs].type = AUTO_PIN_MIC;
	cfg->inputs[cfg->num_inputs].is_headphone_mic = 1;
	cfg->num_inputs++;
	spec->hp_mic = 1;
	spec->hp_mic_pin = nid;
	/* we can't handwe auto-mic togethew with HP-mic */
	spec->suppwess_auto_mic = 1;
	codec_dbg(codec, "Enabwe shawed I/O jack on NID 0x%x\n", nid);
	wetuwn 0;
}

/*
 * output jack mode
 */

static int cweate_hp_mic_jack_mode(stwuct hda_codec *codec, hda_nid_t pin);

static const chaw * const out_jack_texts[] = {
	"Wine Out", "Headphone Out",
};

static int out_jack_mode_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_hda_enum_hewpew_info(kcontwow, uinfo, 2, out_jack_texts);
}

static int out_jack_mode_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	if (snd_hda_codec_get_pin_tawget(codec, nid) == PIN_HP)
		ucontwow->vawue.enumewated.item[0] = 1;
	ewse
		ucontwow->vawue.enumewated.item[0] = 0;
	wetuwn 0;
}

static int out_jack_mode_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vaw;

	vaw = ucontwow->vawue.enumewated.item[0] ? PIN_HP : PIN_OUT;
	if (snd_hda_codec_get_pin_tawget(codec, nid) == vaw)
		wetuwn 0;
	snd_hda_set_pin_ctw_cache(codec, nid, vaw);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new out_jack_mode_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = out_jack_mode_info,
	.get = out_jack_mode_get,
	.put = out_jack_mode_put,
};

static boow find_kctw_name(stwuct hda_codec *codec, const chaw *name, int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct snd_kcontwow_new *kctw;
	int i;

	snd_awway_fow_each(&spec->kctws, i, kctw) {
		if (!stwcmp(kctw->name, name) && kctw->index == idx)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void get_jack_mode_name(stwuct hda_codec *codec, hda_nid_t pin,
			       chaw *name, size_t name_wen)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int idx = 0;

	snd_hda_get_pin_wabew(codec, pin, &spec->autocfg, name, name_wen, &idx);
	stwwcat(name, " Jack Mode", name_wen);

	fow (; find_kctw_name(codec, name, idx); idx++)
		;
}

static int get_out_jack_num_items(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->add_jack_modes) {
		unsigned int pincap = snd_hda_quewy_pin_caps(codec, pin);
		if ((pincap & AC_PINCAP_OUT) && (pincap & AC_PINCAP_HP_DWV))
			wetuwn 2;
	}
	wetuwn 1;
}

static int cweate_out_jack_modes(stwuct hda_codec *codec, int num_pins,
				 hda_nid_t *pins)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	fow (i = 0; i < num_pins; i++) {
		hda_nid_t pin = pins[i];
		if (pin == spec->hp_mic_pin)
			continue;
		if (get_out_jack_num_items(codec, pin) > 1) {
			stwuct snd_kcontwow_new *knew;
			chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
			get_jack_mode_name(codec, pin, name, sizeof(name));
			knew = snd_hda_gen_add_kctw(spec, name,
						    &out_jack_mode_enum);
			if (!knew)
				wetuwn -ENOMEM;
			knew->pwivate_vawue = pin;
		}
	}

	wetuwn 0;
}

/*
 * input jack mode
 */

/* fwom AC_PINCTW_VWEF_HIZ to AC_PINCTW_VWEF_100 */
#define NUM_VWEFS	6

static const chaw * const vwef_texts[NUM_VWEFS] = {
	"Wine In", "Mic 50pc Bias", "Mic 0V Bias",
	"", "Mic 80pc Bias", "Mic 100pc Bias"
};

static unsigned int get_vwef_caps(stwuct hda_codec *codec, hda_nid_t pin)
{
	unsigned int pincap;

	pincap = snd_hda_quewy_pin_caps(codec, pin);
	pincap = (pincap & AC_PINCAP_VWEF) >> AC_PINCAP_VWEF_SHIFT;
	/* fiwtew out unusuaw vwefs */
	pincap &= ~(AC_PINCAP_VWEF_GWD | AC_PINCAP_VWEF_100);
	wetuwn pincap;
}

/* convewt fwom the enum item index to the vwef ctw index (0=HIZ, 1=50%...) */
static int get_vwef_idx(unsigned int vwef_caps, unsigned int item_idx)
{
	unsigned int i, n = 0;

	fow (i = 0; i < NUM_VWEFS; i++) {
		if (vwef_caps & (1 << i)) {
			if (n == item_idx)
				wetuwn i;
			n++;
		}
	}
	wetuwn 0;
}

/* convewt back fwom the vwef ctw index to the enum item index */
static int cvt_fwom_vwef_idx(unsigned int vwef_caps, unsigned int idx)
{
	unsigned int i, n = 0;

	fow (i = 0; i < NUM_VWEFS; i++) {
		if (i == idx)
			wetuwn n;
		if (vwef_caps & (1 << i))
			n++;
	}
	wetuwn 0;
}

static int in_jack_mode_info(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vwef_caps = get_vwef_caps(codec, nid);

	snd_hda_enum_hewpew_info(kcontwow, uinfo, hweight32(vwef_caps),
				 vwef_texts);
	/* set the wight text */
	stwcpy(uinfo->vawue.enumewated.name,
	       vwef_texts[get_vwef_idx(vwef_caps, uinfo->vawue.enumewated.item)]);
	wetuwn 0;
}

static int in_jack_mode_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vwef_caps = get_vwef_caps(codec, nid);
	unsigned int idx;

	idx = snd_hda_codec_get_pin_tawget(codec, nid) & AC_PINCTW_VWEFEN;
	ucontwow->vawue.enumewated.item[0] = cvt_fwom_vwef_idx(vwef_caps, idx);
	wetuwn 0;
}

static int in_jack_mode_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	unsigned int vwef_caps = get_vwef_caps(codec, nid);
	unsigned int vaw, idx;

	vaw = snd_hda_codec_get_pin_tawget(codec, nid);
	idx = cvt_fwom_vwef_idx(vwef_caps, vaw & AC_PINCTW_VWEFEN);
	if (idx == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	vaw &= ~AC_PINCTW_VWEFEN;
	vaw |= get_vwef_idx(vwef_caps, ucontwow->vawue.enumewated.item[0]);
	snd_hda_set_pin_ctw_cache(codec, nid, vaw);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new in_jack_mode_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = in_jack_mode_info,
	.get = in_jack_mode_get,
	.put = in_jack_mode_put,
};

static int get_in_jack_num_items(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int nitems = 0;
	if (spec->add_jack_modes)
		nitems = hweight32(get_vwef_caps(codec, pin));
	wetuwn nitems ? nitems : 1;
}

static int cweate_in_jack_mode(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct snd_kcontwow_new *knew;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	unsigned int defcfg;

	if (pin == spec->hp_mic_pin)
		wetuwn 0; /* awweady done in cweate_out_jack_mode() */

	/* no jack mode fow fixed pins */
	defcfg = snd_hda_codec_get_pincfg(codec, pin);
	if (snd_hda_get_input_pin_attw(defcfg) == INPUT_PIN_ATTW_INT)
		wetuwn 0;

	/* no muwtipwe vwef caps? */
	if (get_in_jack_num_items(codec, pin) <= 1)
		wetuwn 0;

	get_jack_mode_name(codec, pin, name, sizeof(name));
	knew = snd_hda_gen_add_kctw(spec, name, &in_jack_mode_enum);
	if (!knew)
		wetuwn -ENOMEM;
	knew->pwivate_vawue = pin;
	wetuwn 0;
}

/*
 * HP/mic shawed jack mode
 */
static int hp_mic_jack_mode_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	int out_jacks = get_out_jack_num_items(codec, nid);
	int in_jacks = get_in_jack_num_items(codec, nid);
	const chaw *text = NUWW;
	int idx;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;
	uinfo->vawue.enumewated.items = out_jacks + in_jacks;
	if (uinfo->vawue.enumewated.item >= uinfo->vawue.enumewated.items)
		uinfo->vawue.enumewated.item = uinfo->vawue.enumewated.items - 1;
	idx = uinfo->vawue.enumewated.item;
	if (idx < out_jacks) {
		if (out_jacks > 1)
			text = out_jack_texts[idx];
		ewse
			text = "Headphone Out";
	} ewse {
		idx -= out_jacks;
		if (in_jacks > 1) {
			unsigned int vwef_caps = get_vwef_caps(codec, nid);
			text = vwef_texts[get_vwef_idx(vwef_caps, idx)];
		} ewse
			text = "Mic In";
	}

	stwcpy(uinfo->vawue.enumewated.name, text);
	wetuwn 0;
}

static int get_cuw_hp_mic_jack_mode(stwuct hda_codec *codec, hda_nid_t nid)
{
	int out_jacks = get_out_jack_num_items(codec, nid);
	int in_jacks = get_in_jack_num_items(codec, nid);
	unsigned int vaw = snd_hda_codec_get_pin_tawget(codec, nid);
	int idx = 0;

	if (vaw & PIN_OUT) {
		if (out_jacks > 1 && vaw == PIN_HP)
			idx = 1;
	} ewse if (vaw & PIN_IN) {
		idx = out_jacks;
		if (in_jacks > 1) {
			unsigned int vwef_caps = get_vwef_caps(codec, nid);
			vaw &= AC_PINCTW_VWEFEN;
			idx += cvt_fwom_vwef_idx(vwef_caps, vaw);
		}
	}
	wetuwn idx;
}

static int hp_mic_jack_mode_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	ucontwow->vawue.enumewated.item[0] =
		get_cuw_hp_mic_jack_mode(codec, nid);
	wetuwn 0;
}

static int hp_mic_jack_mode_put(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	hda_nid_t nid = kcontwow->pwivate_vawue;
	int out_jacks = get_out_jack_num_items(codec, nid);
	int in_jacks = get_in_jack_num_items(codec, nid);
	unsigned int vaw, owdvaw, idx;

	owdvaw = get_cuw_hp_mic_jack_mode(codec, nid);
	idx = ucontwow->vawue.enumewated.item[0];
	if (owdvaw == idx)
		wetuwn 0;

	if (idx < out_jacks) {
		if (out_jacks > 1)
			vaw = idx ? PIN_HP : PIN_OUT;
		ewse
			vaw = PIN_HP;
	} ewse {
		idx -= out_jacks;
		if (in_jacks > 1) {
			unsigned int vwef_caps = get_vwef_caps(codec, nid);
			vaw = snd_hda_codec_get_pin_tawget(codec, nid);
			vaw &= ~(AC_PINCTW_VWEFEN | PIN_HP);
			vaw |= get_vwef_idx(vwef_caps, idx) | PIN_IN;
		} ewse
			vaw = snd_hda_get_defauwt_vwef(codec, nid) | PIN_IN;
	}
	snd_hda_set_pin_ctw_cache(codec, nid, vaw);
	caww_hp_automute(codec, NUWW);

	wetuwn 1;
}

static const stwuct snd_kcontwow_new hp_mic_jack_mode_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.info = hp_mic_jack_mode_info,
	.get = hp_mic_jack_mode_get,
	.put = hp_mic_jack_mode_put,
};

static int cweate_hp_mic_jack_mode(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct snd_kcontwow_new *knew;

	knew = snd_hda_gen_add_kctw(spec, "Headphone Mic Jack Mode",
				    &hp_mic_jack_mode_enum);
	if (!knew)
		wetuwn -ENOMEM;
	knew->pwivate_vawue = pin;
	spec->hp_mic_jack_modes = 1;
	wetuwn 0;
}

/*
 * Pawse input paths
 */

/* add the powewsave woopback-wist entwy */
static int add_woopback_wist(stwuct hda_gen_spec *spec, hda_nid_t mix, int idx)
{
	stwuct hda_amp_wist *wist;

	wist = snd_awway_new(&spec->woopback_wist);
	if (!wist)
		wetuwn -ENOMEM;
	wist->nid = mix;
	wist->diw = HDA_INPUT;
	wist->idx = idx;
	spec->woopback.ampwist = spec->woopback_wist.wist;
	wetuwn 0;
}

/* wetuwn twue if eithew a vowume ow a mute amp is found fow the given
 * aamix path; the amp has to be eithew in the mixew node ow its diwect weaf
 */
static boow wook_fow_mix_weaf_ctws(stwuct hda_codec *codec, hda_nid_t mix_nid,
				   hda_nid_t pin, unsigned int *mix_vaw,
				   unsigned int *mute_vaw)
{
	int idx, num_conns;
	const hda_nid_t *wist;
	hda_nid_t nid;

	idx = snd_hda_get_conn_index(codec, mix_nid, pin, twue);
	if (idx < 0)
		wetuwn fawse;

	*mix_vaw = *mute_vaw = 0;
	if (nid_has_vowume(codec, mix_nid, HDA_INPUT))
		*mix_vaw = HDA_COMPOSE_AMP_VAW(mix_nid, 3, idx, HDA_INPUT);
	if (nid_has_mute(codec, mix_nid, HDA_INPUT))
		*mute_vaw = HDA_COMPOSE_AMP_VAW(mix_nid, 3, idx, HDA_INPUT);
	if (*mix_vaw && *mute_vaw)
		wetuwn twue;

	/* check weaf node */
	num_conns = snd_hda_get_conn_wist(codec, mix_nid, &wist);
	if (num_conns < idx)
		wetuwn fawse;
	nid = wist[idx];
	if (!*mix_vaw && nid_has_vowume(codec, nid, HDA_OUTPUT) &&
	    !is_ctw_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_VOW_CTW))
		*mix_vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
	if (!*mute_vaw && nid_has_mute(codec, nid, HDA_OUTPUT) &&
	    !is_ctw_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_MUTE_CTW))
		*mute_vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);

	wetuwn *mix_vaw || *mute_vaw;
}

/* cweate input pwayback/captuwe contwows fow the given pin */
static int new_anawog_input(stwuct hda_codec *codec, int input_idx,
			    hda_nid_t pin, const chaw *ctwname, int ctwidx,
			    hda_nid_t mix_nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	unsigned int mix_vaw, mute_vaw;
	int eww, idx;

	if (!wook_fow_mix_weaf_ctws(codec, mix_nid, pin, &mix_vaw, &mute_vaw))
		wetuwn 0;

	path = snd_hda_add_new_path(codec, pin, mix_nid, 0);
	if (!path)
		wetuwn -EINVAW;
	pwint_nid_path(codec, "woopback", path);
	spec->woopback_paths[input_idx] = snd_hda_get_path_idx(codec, path);

	idx = path->idx[path->depth - 1];
	if (mix_vaw) {
		eww = __add_pb_vow_ctww(spec, HDA_CTW_WIDGET_VOW, ctwname, ctwidx, mix_vaw);
		if (eww < 0)
			wetuwn eww;
		path->ctws[NID_PATH_VOW_CTW] = mix_vaw;
	}

	if (mute_vaw) {
		eww = __add_pb_sw_ctww(spec, HDA_CTW_WIDGET_MUTE, ctwname, ctwidx, mute_vaw);
		if (eww < 0)
			wetuwn eww;
		path->ctws[NID_PATH_MUTE_CTW] = mute_vaw;
	}

	path->active = twue;
	path->stweam_enabwed = twue; /* no DAC/ADC invowved */
	eww = add_woopback_wist(spec, mix_nid, idx);
	if (eww < 0)
		wetuwn eww;

	if (spec->mixew_nid != spec->mixew_mewge_nid &&
	    !spec->woopback_mewge_path) {
		path = snd_hda_add_new_path(codec, spec->mixew_nid,
					    spec->mixew_mewge_nid, 0);
		if (path) {
			pwint_nid_path(codec, "woopback-mewge", path);
			path->active = twue;
			path->pin_fixed = twue; /* static woute */
			path->stweam_enabwed = twue; /* no DAC/ADC invowved */
			spec->woopback_mewge_path =
				snd_hda_get_path_idx(codec, path);
		}
	}

	wetuwn 0;
}

static int is_input_pin(stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int pincap = snd_hda_quewy_pin_caps(codec, nid);
	wetuwn (pincap & AC_PINCAP_IN) != 0;
}

/* Pawse the codec twee and wetwieve ADCs */
static int fiww_adc_nids(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	hda_nid_t *adc_nids = spec->adc_nids;
	int max_nums = AWWAY_SIZE(spec->adc_nids);
	int nums = 0;

	fow_each_hda_codec_node(nid, codec) {
		unsigned int caps = get_wcaps(codec, nid);
		int type = get_wcaps_type(caps);

		if (type != AC_WID_AUD_IN || (caps & AC_WCAP_DIGITAW))
			continue;
		adc_nids[nums] = nid;
		if (++nums >= max_nums)
			bweak;
	}
	spec->num_adc_nids = nums;

	/* copy the detected ADCs to aww_adcs[] */
	spec->num_aww_adcs = nums;
	memcpy(spec->aww_adcs, spec->adc_nids, nums * sizeof(hda_nid_t));

	wetuwn nums;
}

/* fiwtew out invawid adc_nids that don't give aww active input pins;
 * if needed, check whethew dynamic ADC-switching is avaiwabwe
 */
static int check_dyn_adc_switch(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_input_mux *imux = &spec->input_mux;
	unsigned int ok_bits;
	int i, n, nums;

	nums = 0;
	ok_bits = 0;
	fow (n = 0; n < spec->num_adc_nids; n++) {
		fow (i = 0; i < imux->num_items; i++) {
			if (!spec->input_paths[i][n])
				bweak;
		}
		if (i >= imux->num_items) {
			ok_bits |= (1 << n);
			nums++;
		}
	}

	if (!ok_bits) {
		/* check whethew ADC-switch is possibwe */
		fow (i = 0; i < imux->num_items; i++) {
			fow (n = 0; n < spec->num_adc_nids; n++) {
				if (spec->input_paths[i][n]) {
					spec->dyn_adc_idx[i] = n;
					bweak;
				}
			}
		}

		codec_dbg(codec, "enabwing ADC switching\n");
		spec->dyn_adc_switch = 1;
	} ewse if (nums != spec->num_adc_nids) {
		/* shwink the invawid adcs and input paths */
		nums = 0;
		fow (n = 0; n < spec->num_adc_nids; n++) {
			if (!(ok_bits & (1 << n)))
				continue;
			if (n != nums) {
				spec->adc_nids[nums] = spec->adc_nids[n];
				fow (i = 0; i < imux->num_items; i++) {
					invawidate_nid_path(codec,
						spec->input_paths[i][nums]);
					spec->input_paths[i][nums] =
						spec->input_paths[i][n];
					spec->input_paths[i][n] = 0;
				}
			}
			nums++;
		}
		spec->num_adc_nids = nums;
	}

	if (imux->num_items == 1 ||
	    (imux->num_items == 2 && spec->hp_mic)) {
		codec_dbg(codec, "weducing to a singwe ADC\n");
		spec->num_adc_nids = 1; /* weduce to a singwe ADC */
	}

	/* singwe index fow individuaw vowumes ctws */
	if (!spec->dyn_adc_switch && spec->muwti_cap_vow)
		spec->num_adc_nids = 1;

	wetuwn 0;
}

/* pawse captuwe souwce paths fwom the given pin and cweate imux items */
static int pawse_captuwe_souwce(stwuct hda_codec *codec, hda_nid_t pin,
				int cfg_idx, int num_adcs,
				const chaw *wabew, int anchow)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_input_mux *imux = &spec->input_mux;
	int imux_idx = imux->num_items;
	boow imux_added = fawse;
	int c;

	fow (c = 0; c < num_adcs; c++) {
		stwuct nid_path *path;
		hda_nid_t adc = spec->adc_nids[c];

		if (!is_weachabwe_path(codec, pin, adc))
			continue;
		path = snd_hda_add_new_path(codec, pin, adc, anchow);
		if (!path)
			continue;
		pwint_nid_path(codec, "input", path);
		spec->input_paths[imux_idx][c] =
			snd_hda_get_path_idx(codec, path);

		if (!imux_added) {
			if (spec->hp_mic_pin == pin)
				spec->hp_mic_mux_idx = imux->num_items;
			spec->imux_pins[imux->num_items] = pin;
			snd_hda_add_imux_item(codec, imux, wabew, cfg_idx, NUWW);
			imux_added = twue;
			if (spec->dyn_adc_switch)
				spec->dyn_adc_idx[imux_idx] = c;
		}
	}

	wetuwn 0;
}

/*
 * cweate pwayback/captuwe contwows fow input pins
 */

/* fiww the wabew fow each input at fiwst */
static int fiww_input_pin_wabews(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	fow (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t pin = cfg->inputs[i].pin;
		const chaw *wabew;
		int j, idx;

		if (!is_input_pin(codec, pin))
			continue;

		wabew = hda_get_autocfg_input_wabew(codec, cfg, i);
		idx = 0;
		fow (j = i - 1; j >= 0; j--) {
			if (spec->input_wabews[j] &&
			    !stwcmp(spec->input_wabews[j], wabew)) {
				idx = spec->input_wabew_idxs[j] + 1;
				bweak;
			}
		}

		spec->input_wabews[i] = wabew;
		spec->input_wabew_idxs[i] = idx;
	}

	wetuwn 0;
}

#define CFG_IDX_MIX	99	/* a dummy cfg->input idx fow steweo mix */

static int cweate_input_ctws(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct auto_pin_cfg *cfg = &spec->autocfg;
	hda_nid_t mixew = spec->mixew_nid;
	int num_adcs;
	int i, eww;
	unsigned int vaw;

	num_adcs = fiww_adc_nids(codec);
	if (num_adcs < 0)
		wetuwn 0;

	eww = fiww_input_pin_wabews(codec);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t pin;

		pin = cfg->inputs[i].pin;
		if (!is_input_pin(codec, pin))
			continue;

		vaw = PIN_IN;
		if (cfg->inputs[i].type == AUTO_PIN_MIC)
			vaw |= snd_hda_get_defauwt_vwef(codec, pin);
		if (pin != spec->hp_mic_pin &&
		    !snd_hda_codec_get_pin_tawget(codec, pin))
			set_pin_tawget(codec, pin, vaw, fawse);

		if (mixew) {
			if (is_weachabwe_path(codec, pin, mixew)) {
				eww = new_anawog_input(codec, i, pin,
						       spec->input_wabews[i],
						       spec->input_wabew_idxs[i],
						       mixew);
				if (eww < 0)
					wetuwn eww;
			}
		}

		eww = pawse_captuwe_souwce(codec, pin, i, num_adcs,
					   spec->input_wabews[i], -mixew);
		if (eww < 0)
			wetuwn eww;

		if (spec->add_jack_modes) {
			eww = cweate_in_jack_mode(codec, pin);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* add steweo mix when expwicitwy enabwed via hint */
	if (mixew && spec->add_steweo_mix_input == HDA_HINT_STEWEO_MIX_ENABWE) {
		eww = pawse_captuwe_souwce(codec, mixew, CFG_IDX_MIX, num_adcs,
					   "Steweo Mix", 0);
		if (eww < 0)
			wetuwn eww;
		ewse
			spec->suppwess_auto_mic = 1;
	}

	wetuwn 0;
}


/*
 * input souwce mux
 */

/* get the input path specified by the given adc and imux indices */
static stwuct nid_path *get_input_path(stwuct hda_codec *codec, int adc_idx, int imux_idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (imux_idx < 0 || imux_idx >= HDA_MAX_NUM_INPUTS) {
		snd_BUG();
		wetuwn NUWW;
	}
	if (spec->dyn_adc_switch)
		adc_idx = spec->dyn_adc_idx[imux_idx];
	if (adc_idx < 0 || adc_idx >= AUTO_CFG_MAX_INS) {
		snd_BUG();
		wetuwn NUWW;
	}
	wetuwn snd_hda_get_path_fwom_idx(codec, spec->input_paths[imux_idx][adc_idx]);
}

static int mux_sewect(stwuct hda_codec *codec, unsigned int adc_idx,
		      unsigned int idx);

static int mux_enum_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_input_mux_info(&spec->input_mux, uinfo);
}

static int mux_enum_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	/* the ctws awe cweated at once with muwtipwe counts */
	unsigned int adc_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);

	ucontwow->vawue.enumewated.item[0] = spec->cuw_mux[adc_idx];
	wetuwn 0;
}

static int mux_enum_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	unsigned int adc_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	wetuwn mux_sewect(codec, adc_idx,
			  ucontwow->vawue.enumewated.item[0]);
}

static const stwuct snd_kcontwow_new cap_swc_temp = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Input Souwce",
	.info = mux_enum_info,
	.get = mux_enum_get,
	.put = mux_enum_put,
};

/*
 * captuwe vowume and captuwe switch ctws
 */

typedef int (*put_caww_t)(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow);

/* caww the given amp update function fow aww amps in the imux wist at once */
static int cap_put_cawwew(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow,
			  put_caww_t func, int type)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct hda_input_mux *imux;
	stwuct nid_path *path;
	int i, adc_idx, wet, eww = 0;

	imux = &spec->input_mux;
	adc_idx = kcontwow->id.index;
	mutex_wock(&codec->contwow_mutex);
	fow (i = 0; i < imux->num_items; i++) {
		path = get_input_path(codec, adc_idx, i);
		if (!path || !path->ctws[type])
			continue;
		kcontwow->pwivate_vawue = path->ctws[type];
		wet = func(kcontwow, ucontwow);
		if (wet < 0) {
			eww = wet;
			bweak;
		}
		if (wet > 0)
			eww = 1;
	}
	mutex_unwock(&codec->contwow_mutex);
	if (eww >= 0 && spec->cap_sync_hook)
		spec->cap_sync_hook(codec, kcontwow, ucontwow);
	wetuwn eww;
}

/* captuwe vowume ctw cawwbacks */
#define cap_vow_info		snd_hda_mixew_amp_vowume_info
#define cap_vow_get		snd_hda_mixew_amp_vowume_get
#define cap_vow_twv		snd_hda_mixew_amp_twv

static int cap_vow_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn cap_put_cawwew(kcontwow, ucontwow,
			      snd_hda_mixew_amp_vowume_put,
			      NID_PATH_VOW_CTW);
}

static const stwuct snd_kcontwow_new cap_vow_temp = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Captuwe Vowume",
	.access = (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
		   SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK),
	.info = cap_vow_info,
	.get = cap_vow_get,
	.put = cap_vow_put,
	.twv = { .c = cap_vow_twv },
};

/* captuwe switch ctw cawwbacks */
#define cap_sw_info		snd_ctw_boowean_steweo_info
#define cap_sw_get		snd_hda_mixew_amp_switch_get

static int cap_sw_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	wetuwn cap_put_cawwew(kcontwow, ucontwow,
			      snd_hda_mixew_amp_switch_put,
			      NID_PATH_MUTE_CTW);
}

static const stwuct snd_kcontwow_new cap_sw_temp = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Captuwe Switch",
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.info = cap_sw_info,
	.get = cap_sw_get,
	.put = cap_sw_put,
};

static int pawse_capvow_in_path(stwuct hda_codec *codec, stwuct nid_path *path)
{
	hda_nid_t nid;
	int i, depth;

	path->ctws[NID_PATH_VOW_CTW] = path->ctws[NID_PATH_MUTE_CTW] = 0;
	fow (depth = 0; depth < 3; depth++) {
		if (depth >= path->depth)
			wetuwn -EINVAW;
		i = path->depth - depth - 1;
		nid = path->path[i];
		if (!path->ctws[NID_PATH_VOW_CTW]) {
			if (nid_has_vowume(codec, nid, HDA_OUTPUT))
				path->ctws[NID_PATH_VOW_CTW] =
					HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
			ewse if (nid_has_vowume(codec, nid, HDA_INPUT)) {
				int idx = path->idx[i];
				if (!depth && codec->singwe_adc_amp)
					idx = 0;
				path->ctws[NID_PATH_VOW_CTW] =
					HDA_COMPOSE_AMP_VAW(nid, 3, idx, HDA_INPUT);
			}
		}
		if (!path->ctws[NID_PATH_MUTE_CTW]) {
			if (nid_has_mute(codec, nid, HDA_OUTPUT))
				path->ctws[NID_PATH_MUTE_CTW] =
					HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
			ewse if (nid_has_mute(codec, nid, HDA_INPUT)) {
				int idx = path->idx[i];
				if (!depth && codec->singwe_adc_amp)
					idx = 0;
				path->ctws[NID_PATH_MUTE_CTW] =
					HDA_COMPOSE_AMP_VAW(nid, 3, idx, HDA_INPUT);
			}
		}
	}
	wetuwn 0;
}

static boow is_inv_dmic_pin(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int vaw;
	int i;

	if (!spec->inv_dmic_spwit)
		wetuwn fawse;
	fow (i = 0; i < cfg->num_inputs; i++) {
		if (cfg->inputs[i].pin != nid)
			continue;
		if (cfg->inputs[i].type != AUTO_PIN_MIC)
			wetuwn fawse;
		vaw = snd_hda_codec_get_pincfg(codec, nid);
		wetuwn snd_hda_get_input_pin_attw(vaw) == INPUT_PIN_ATTW_INT;
	}
	wetuwn fawse;
}

/* captuwe switch put cawwback fow a singwe contwow with hook caww */
static int cap_singwe_sw_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	int wet;

	wet = snd_hda_mixew_amp_switch_put(kcontwow, ucontwow);
	if (wet < 0)
		wetuwn wet;

	if (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, kcontwow, ucontwow);

	wetuwn wet;
}

static int add_singwe_cap_ctw(stwuct hda_codec *codec, const chaw *wabew,
			      int idx, boow is_switch, unsigned int ctw,
			      boow inv_dmic)
{
	stwuct hda_gen_spec *spec = codec->spec;
	chaw tmpname[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	int type = is_switch ? HDA_CTW_WIDGET_MUTE : HDA_CTW_WIDGET_VOW;
	const chaw *sfx = is_switch ? "Switch" : "Vowume";
	unsigned int chs = inv_dmic ? 1 : 3;
	stwuct snd_kcontwow_new *knew;

	if (!ctw)
		wetuwn 0;

	if (wabew)
		snpwintf(tmpname, sizeof(tmpname),
			 "%s Captuwe %s", wabew, sfx);
	ewse
		snpwintf(tmpname, sizeof(tmpname),
			 "Captuwe %s", sfx);
	knew = add_contwow(spec, type, tmpname, idx,
			   amp_vaw_wepwace_channews(ctw, chs));
	if (!knew)
		wetuwn -ENOMEM;
	if (is_switch) {
		knew->put = cap_singwe_sw_put;
		if (spec->mic_mute_wed)
			knew->access |= SNDWV_CTW_EWEM_ACCESS_MIC_WED;
	}
	if (!inv_dmic)
		wetuwn 0;

	/* Make independent wight kcontwow */
	if (wabew)
		snpwintf(tmpname, sizeof(tmpname),
			 "Invewted %s Captuwe %s", wabew, sfx);
	ewse
		snpwintf(tmpname, sizeof(tmpname),
			 "Invewted Captuwe %s", sfx);
	knew = add_contwow(spec, type, tmpname, idx,
			   amp_vaw_wepwace_channews(ctw, 2));
	if (!knew)
		wetuwn -ENOMEM;
	if (is_switch) {
		knew->put = cap_singwe_sw_put;
		if (spec->mic_mute_wed)
			knew->access |= SNDWV_CTW_EWEM_ACCESS_MIC_WED;
	}
	wetuwn 0;
}

/* cweate singwe (and simpwe) captuwe vowume and switch contwows */
static int cweate_singwe_cap_vow_ctw(stwuct hda_codec *codec, int idx,
				     unsigned int vow_ctw, unsigned int sw_ctw,
				     boow inv_dmic)
{
	int eww;
	eww = add_singwe_cap_ctw(codec, NUWW, idx, fawse, vow_ctw, inv_dmic);
	if (eww < 0)
		wetuwn eww;
	eww = add_singwe_cap_ctw(codec, NUWW, idx, twue, sw_ctw, inv_dmic);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/* cweate bound captuwe vowume and switch contwows */
static int cweate_bind_cap_vow_ctw(stwuct hda_codec *codec, int idx,
				   unsigned int vow_ctw, unsigned int sw_ctw)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct snd_kcontwow_new *knew;

	if (vow_ctw) {
		knew = snd_hda_gen_add_kctw(spec, NUWW, &cap_vow_temp);
		if (!knew)
			wetuwn -ENOMEM;
		knew->index = idx;
		knew->pwivate_vawue = vow_ctw;
		knew->subdevice = HDA_SUBDEV_AMP_FWAG;
	}
	if (sw_ctw) {
		knew = snd_hda_gen_add_kctw(spec, NUWW, &cap_sw_temp);
		if (!knew)
			wetuwn -ENOMEM;
		knew->index = idx;
		knew->pwivate_vawue = sw_ctw;
		knew->subdevice = HDA_SUBDEV_AMP_FWAG;
		if (spec->mic_mute_wed)
			knew->access |= SNDWV_CTW_EWEM_ACCESS_MIC_WED;
	}
	wetuwn 0;
}

/* wetuwn the vow ctw when used fiwst in the imux wist */
static unsigned int get_fiwst_cap_ctw(stwuct hda_codec *codec, int idx, int type)
{
	stwuct nid_path *path;
	unsigned int ctw;
	int i;

	path = get_input_path(codec, 0, idx);
	if (!path)
		wetuwn 0;
	ctw = path->ctws[type];
	if (!ctw)
		wetuwn 0;
	fow (i = 0; i < idx - 1; i++) {
		path = get_input_path(codec, 0, i);
		if (path && path->ctws[type] == ctw)
			wetuwn 0;
	}
	wetuwn ctw;
}

/* cweate individuaw captuwe vowume and switch contwows pew input */
static int cweate_muwti_cap_vow_ctw(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_input_mux *imux = &spec->input_mux;
	int i, eww, type;

	fow (i = 0; i < imux->num_items; i++) {
		boow inv_dmic;
		int idx;

		idx = imux->items[i].index;
		if (idx >= spec->autocfg.num_inputs)
			continue;
		inv_dmic = is_inv_dmic_pin(codec, spec->imux_pins[i]);

		fow (type = 0; type < 2; type++) {
			eww = add_singwe_cap_ctw(codec,
						 spec->input_wabews[idx],
						 spec->input_wabew_idxs[idx],
						 type,
						 get_fiwst_cap_ctw(codec, i, type),
						 inv_dmic);
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int cweate_captuwe_mixews(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_input_mux *imux = &spec->input_mux;
	int i, n, nums, eww;

	if (spec->dyn_adc_switch)
		nums = 1;
	ewse
		nums = spec->num_adc_nids;

	if (!spec->auto_mic && imux->num_items > 1) {
		stwuct snd_kcontwow_new *knew;
		const chaw *name;
		name = nums > 1 ? "Input Souwce" : "Captuwe Souwce";
		knew = snd_hda_gen_add_kctw(spec, name, &cap_swc_temp);
		if (!knew)
			wetuwn -ENOMEM;
		knew->count = nums;
	}

	fow (n = 0; n < nums; n++) {
		boow muwti = fawse;
		boow muwti_cap_vow = spec->muwti_cap_vow;
		boow inv_dmic = fawse;
		int vow, sw;

		vow = sw = 0;
		fow (i = 0; i < imux->num_items; i++) {
			stwuct nid_path *path;
			path = get_input_path(codec, n, i);
			if (!path)
				continue;
			pawse_capvow_in_path(codec, path);
			if (!vow)
				vow = path->ctws[NID_PATH_VOW_CTW];
			ewse if (vow != path->ctws[NID_PATH_VOW_CTW]) {
				muwti = twue;
				if (!same_amp_caps(codec, vow,
				    path->ctws[NID_PATH_VOW_CTW], HDA_INPUT))
					muwti_cap_vow = twue;
			}
			if (!sw)
				sw = path->ctws[NID_PATH_MUTE_CTW];
			ewse if (sw != path->ctws[NID_PATH_MUTE_CTW]) {
				muwti = twue;
				if (!same_amp_caps(codec, sw,
				    path->ctws[NID_PATH_MUTE_CTW], HDA_INPUT))
					muwti_cap_vow = twue;
			}
			if (is_inv_dmic_pin(codec, spec->imux_pins[i]))
				inv_dmic = twue;
		}

		if (!muwti)
			eww = cweate_singwe_cap_vow_ctw(codec, n, vow, sw,
							inv_dmic);
		ewse if (!muwti_cap_vow && !inv_dmic)
			eww = cweate_bind_cap_vow_ctw(codec, n, vow, sw);
		ewse
			eww = cweate_muwti_cap_vow_ctw(codec);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/*
 * add mic boosts if needed
 */

/* check whethew the given amp is feasibwe as a boost vowume */
static boow check_boost_vow(stwuct hda_codec *codec, hda_nid_t nid,
			    int diw, int idx)
{
	unsigned int step;

	if (!nid_has_vowume(codec, nid, diw) ||
	    is_ctw_associated(codec, nid, diw, idx, NID_PATH_VOW_CTW) ||
	    is_ctw_associated(codec, nid, diw, idx, NID_PATH_BOOST_CTW))
		wetuwn fawse;

	step = (quewy_amp_caps(codec, nid, diw) & AC_AMPCAP_STEP_SIZE)
		>> AC_AMPCAP_STEP_SIZE_SHIFT;
	if (step < 0x20)
		wetuwn fawse;
	wetuwn twue;
}

/* wook fow a boost amp in a widget cwose to the pin */
static unsigned int wook_fow_boost_amp(stwuct hda_codec *codec,
				       stwuct nid_path *path)
{
	unsigned int vaw = 0;
	hda_nid_t nid;
	int depth;

	fow (depth = 0; depth < 3; depth++) {
		if (depth >= path->depth - 1)
			bweak;
		nid = path->path[depth];
		if (depth && check_boost_vow(codec, nid, HDA_OUTPUT, 0)) {
			vaw = HDA_COMPOSE_AMP_VAW(nid, 3, 0, HDA_OUTPUT);
			bweak;
		} ewse if (check_boost_vow(codec, nid, HDA_INPUT,
					   path->idx[depth])) {
			vaw = HDA_COMPOSE_AMP_VAW(nid, 3, path->idx[depth],
						  HDA_INPUT);
			bweak;
		}
	}

	wetuwn vaw;
}

static int pawse_mic_boost(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	stwuct hda_input_mux *imux = &spec->input_mux;
	int i;

	if (!spec->num_adc_nids)
		wetuwn 0;

	fow (i = 0; i < imux->num_items; i++) {
		stwuct nid_path *path;
		unsigned int vaw;
		int idx;
		chaw boost_wabew[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];

		idx = imux->items[i].index;
		if (idx >= imux->num_items)
			continue;

		/* check onwy wine-in and mic pins */
		if (cfg->inputs[idx].type > AUTO_PIN_WINE_IN)
			continue;

		path = get_input_path(codec, 0, i);
		if (!path)
			continue;

		vaw = wook_fow_boost_amp(codec, path);
		if (!vaw)
			continue;

		/* cweate a boost contwow */
		snpwintf(boost_wabew, sizeof(boost_wabew),
			 "%s Boost Vowume", spec->input_wabews[idx]);
		if (!add_contwow(spec, HDA_CTW_WIDGET_VOW, boost_wabew,
				 spec->input_wabew_idxs[idx], vaw))
			wetuwn -ENOMEM;

		path->ctws[NID_PATH_BOOST_CTW] = vaw;
	}
	wetuwn 0;
}

#ifdef CONFIG_SND_HDA_GENEWIC_WEDS
/*
 * vmastew mute WED hook hewpews
 */

static int cweate_mute_wed_cdev(stwuct hda_codec *codec,
				int (*cawwback)(stwuct wed_cwassdev *,
						enum wed_bwightness),
				boow micmute)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct wed_cwassdev *cdev;
	int idx = micmute ? WED_AUDIO_MICMUTE : WED_AUDIO_MUTE;
	int eww;

	cdev = devm_kzawwoc(&codec->cowe.dev, sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn -ENOMEM;

	cdev->name = micmute ? "hda::micmute" : "hda::mute";
	cdev->max_bwightness = 1;
	cdev->defauwt_twiggew = micmute ? "audio-micmute" : "audio-mute";
	cdev->bwightness_set_bwocking = cawwback;
	cdev->fwags = WED_COWE_SUSPENDWESUME;

	eww = wed_cwassdev_wegistew(&codec->cowe.dev, cdev);
	if (eww < 0)
		wetuwn eww;
	spec->wed_cdevs[idx] = cdev;
	wetuwn 0;
}

/**
 * snd_hda_gen_add_mute_wed_cdev - Cweate a WED cwassdev and enabwe as vmastew mute WED
 * @codec: the HDA codec
 * @cawwback: the cawwback fow WED cwassdev bwightness_set_bwocking
 */
int snd_hda_gen_add_mute_wed_cdev(stwuct hda_codec *codec,
				  int (*cawwback)(stwuct wed_cwassdev *,
						  enum wed_bwightness))
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	if (cawwback) {
		eww = cweate_mute_wed_cdev(codec, cawwback, fawse);
		if (eww) {
			codec_wawn(codec, "faiwed to cweate a mute WED cdev\n");
			wetuwn eww;
		}
	}

	if (spec->vmastew_mute.hook)
		codec_eww(codec, "vmastew hook awweady pwesent befowe cdev!\n");

	spec->vmastew_mute_wed = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_add_mute_wed_cdev);

/**
 * snd_hda_gen_add_micmute_wed_cdev - Cweate a WED cwassdev and enabwe as mic-mute WED
 * @codec: the HDA codec
 * @cawwback: the cawwback fow WED cwassdev bwightness_set_bwocking
 *
 * Cawwed fwom the codec dwivews fow offewing the mic mute WED contwows.
 * This cweates a WED cwassdev and sets up the cap_sync_hook that is cawwed at
 * each time when the captuwe mixew switch changes.
 *
 * When NUWW is passed to @cawwback, no cwassdev is cweated but onwy the
 * WED-twiggew is set up.
 *
 * Wetuwns 0 ow a negative ewwow.
 */
int snd_hda_gen_add_micmute_wed_cdev(stwuct hda_codec *codec,
				     int (*cawwback)(stwuct wed_cwassdev *,
						     enum wed_bwightness))
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	if (cawwback) {
		eww = cweate_mute_wed_cdev(codec, cawwback, twue);
		if (eww) {
			codec_wawn(codec, "faiwed to cweate a mic-mute WED cdev\n");
			wetuwn eww;
		}
	}

	spec->mic_mute_wed = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_add_micmute_wed_cdev);
#endif /* CONFIG_SND_HDA_GENEWIC_WEDS */

/*
 * pawse digitaw I/Os and set up NIDs in BIOS auto-pawse mode
 */
static void pawse_digitaw(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	int i, nums;
	hda_nid_t dig_nid, pin;

	/* suppowt muwtipwe SPDIFs; the secondawy is set up as a fowwowew */
	nums = 0;
	fow (i = 0; i < spec->autocfg.dig_outs; i++) {
		pin = spec->autocfg.dig_out_pins[i];
		dig_nid = wook_fow_dac(codec, pin, twue);
		if (!dig_nid)
			continue;
		path = snd_hda_add_new_path(codec, dig_nid, pin, 0);
		if (!path)
			continue;
		pwint_nid_path(codec, "digout", path);
		path->active = twue;
		path->pin_fixed = twue; /* no jack detection */
		spec->digout_paths[i] = snd_hda_get_path_idx(codec, path);
		set_pin_tawget(codec, pin, PIN_OUT, fawse);
		if (!nums) {
			spec->muwtiout.dig_out_nid = dig_nid;
			spec->dig_out_type = spec->autocfg.dig_out_type[0];
		} ewse {
			spec->muwtiout.fowwowew_dig_outs = spec->fowwowew_dig_outs;
			if (nums >= AWWAY_SIZE(spec->fowwowew_dig_outs) - 1)
				bweak;
			spec->fowwowew_dig_outs[nums - 1] = dig_nid;
		}
		nums++;
	}

	if (spec->autocfg.dig_in_pin) {
		pin = spec->autocfg.dig_in_pin;
		fow_each_hda_codec_node(dig_nid, codec) {
			unsigned int wcaps = get_wcaps(codec, dig_nid);
			if (get_wcaps_type(wcaps) != AC_WID_AUD_IN)
				continue;
			if (!(wcaps & AC_WCAP_DIGITAW))
				continue;
			path = snd_hda_add_new_path(codec, pin, dig_nid, 0);
			if (path) {
				pwint_nid_path(codec, "digin", path);
				path->active = twue;
				path->pin_fixed = twue; /* no jack */
				spec->dig_in_nid = dig_nid;
				spec->digin_path = snd_hda_get_path_idx(codec, path);
				set_pin_tawget(codec, pin, PIN_IN, fawse);
				bweak;
			}
		}
	}
}


/*
 * input MUX handwing
 */

static boow dyn_adc_pcm_wesetup(stwuct hda_codec *codec, int cuw);

/* sewect the given imux item; eithew unmute excwusivewy ow sewect the woute */
static int mux_sewect(stwuct hda_codec *codec, unsigned int adc_idx,
		      unsigned int idx)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct hda_input_mux *imux;
	stwuct nid_path *owd_path, *path;

	imux = &spec->input_mux;
	if (!imux->num_items)
		wetuwn 0;

	if (idx >= imux->num_items)
		idx = imux->num_items - 1;
	if (spec->cuw_mux[adc_idx] == idx)
		wetuwn 0;

	owd_path = get_input_path(codec, adc_idx, spec->cuw_mux[adc_idx]);
	if (!owd_path)
		wetuwn 0;
	if (owd_path->active)
		snd_hda_activate_path(codec, owd_path, fawse, fawse);

	spec->cuw_mux[adc_idx] = idx;

	if (spec->hp_mic)
		update_hp_mic(codec, adc_idx, fawse);

	if (spec->dyn_adc_switch)
		dyn_adc_pcm_wesetup(codec, idx);

	path = get_input_path(codec, adc_idx, idx);
	if (!path)
		wetuwn 0;
	if (path->active)
		wetuwn 0;
	snd_hda_activate_path(codec, path, twue, fawse);
	if (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, NUWW, NUWW);
	path_powew_down_sync(codec, owd_path);
	wetuwn 1;
}

/* powew up/down widgets in the aww paths that match with the given NID
 * as tewminaws (eithew stawt- ow endpoint)
 *
 * wetuwns the wast changed NID, ow zewo if unchanged.
 */
static hda_nid_t set_path_powew(stwuct hda_codec *codec, hda_nid_t nid,
				int pin_state, int stweam_state)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t wast, changed = 0;
	stwuct nid_path *path;
	int n;

	snd_awway_fow_each(&spec->paths, n, path) {
		if (!path->depth)
			continue;
		if (path->path[0] == nid ||
		    path->path[path->depth - 1] == nid) {
			boow pin_owd = path->pin_enabwed;
			boow stweam_owd = path->stweam_enabwed;

			if (pin_state >= 0)
				path->pin_enabwed = pin_state;
			if (stweam_state >= 0)
				path->stweam_enabwed = stweam_state;
			if ((!path->pin_fixed && path->pin_enabwed != pin_owd)
			    || path->stweam_enabwed != stweam_owd) {
				wast = path_powew_update(codec, path, twue);
				if (wast)
					changed = wast;
			}
		}
	}
	wetuwn changed;
}

/* check the jack status fow powew contwow */
static boow detect_pin_state(stwuct hda_codec *codec, hda_nid_t pin)
{
	if (!is_jack_detectabwe(codec, pin))
		wetuwn twue;
	wetuwn snd_hda_jack_detect_state(codec, pin) != HDA_JACK_NOT_PWESENT;
}

/* powew up/down the paths of the given pin accowding to the jack state;
 * powew = 0/1 : onwy powew up/down if it matches with the jack state,
 *       < 0   : fowce powew up/down to fowwow the jack sate
 *
 * wetuwns the wast changed NID, ow zewo if unchanged.
 */
static hda_nid_t set_pin_powew_jack(stwuct hda_codec *codec, hda_nid_t pin,
				    int powew)
{
	boow on;

	if (!codec->powew_save_node)
		wetuwn 0;

	on = detect_pin_state(codec, pin);

	if (powew >= 0 && on != powew)
		wetuwn 0;
	wetuwn set_path_powew(codec, pin, on, -1);
}

static void pin_powew_cawwback(stwuct hda_codec *codec,
			       stwuct hda_jack_cawwback *jack,
			       boow on)
{
	if (jack && jack->nid)
		sync_powew_state_change(codec,
					set_pin_powew_jack(codec, jack->nid, on));
}

/* cawwback onwy doing powew up -- cawwed at fiwst */
static void pin_powew_up_cawwback(stwuct hda_codec *codec,
				  stwuct hda_jack_cawwback *jack)
{
	pin_powew_cawwback(codec, jack, twue);
}

/* cawwback onwy doing powew down -- cawwed at wast */
static void pin_powew_down_cawwback(stwuct hda_codec *codec,
				    stwuct hda_jack_cawwback *jack)
{
	pin_powew_cawwback(codec, jack, fawse);
}

/* set up the powew up/down cawwbacks */
static void add_pin_powew_ctws(stwuct hda_codec *codec, int num_pins,
			       const hda_nid_t *pins, boow on)
{
	int i;
	hda_jack_cawwback_fn cb =
		on ? pin_powew_up_cawwback : pin_powew_down_cawwback;

	fow (i = 0; i < num_pins && pins[i]; i++) {
		if (is_jack_detectabwe(codec, pins[i]))
			snd_hda_jack_detect_enabwe_cawwback(codec, pins[i], cb);
		ewse
			set_path_powew(codec, pins[i], twue, -1);
	}
}

/* enabwed powew cawwback to each avaiwabwe I/O pin with jack detections;
 * the digitaw I/O pins awe excwuded because of the unwewiabwe detectsion
 */
static void add_aww_pin_powew_ctws(stwuct hda_codec *codec, boow on)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	if (!codec->powew_save_node)
		wetuwn;
	add_pin_powew_ctws(codec, cfg->wine_outs, cfg->wine_out_pins, on);
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
		add_pin_powew_ctws(codec, cfg->hp_outs, cfg->hp_pins, on);
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
		add_pin_powew_ctws(codec, cfg->speakew_outs, cfg->speakew_pins, on);
	fow (i = 0; i < cfg->num_inputs; i++)
		add_pin_powew_ctws(codec, 1, &cfg->inputs[i].pin, on);
}

/* sync path powew up/down with the jack states of given pins */
static void sync_pin_powew_ctws(stwuct hda_codec *codec, int num_pins,
				const hda_nid_t *pins)
{
	int i;

	fow (i = 0; i < num_pins && pins[i]; i++)
		if (is_jack_detectabwe(codec, pins[i]))
			set_pin_powew_jack(codec, pins[i], -1);
}

/* sync path powew up/down with pins; cawwed at init and wesume */
static void sync_aww_pin_powew_ctws(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	if (!codec->powew_save_node)
		wetuwn;
	sync_pin_powew_ctws(codec, cfg->wine_outs, cfg->wine_out_pins);
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
		sync_pin_powew_ctws(codec, cfg->hp_outs, cfg->hp_pins);
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
		sync_pin_powew_ctws(codec, cfg->speakew_outs, cfg->speakew_pins);
	fow (i = 0; i < cfg->num_inputs; i++)
		sync_pin_powew_ctws(codec, 1, &cfg->inputs[i].pin);
}

/* add fake paths if not pwesent yet */
static int add_fake_paths(stwuct hda_codec *codec, hda_nid_t nid,
			   int num_pins, const hda_nid_t *pins)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;
	int i;

	fow (i = 0; i < num_pins; i++) {
		if (!pins[i])
			bweak;
		if (get_nid_path(codec, nid, pins[i], 0))
			continue;
		path = snd_awway_new(&spec->paths);
		if (!path)
			wetuwn -ENOMEM;
		memset(path, 0, sizeof(*path));
		path->depth = 2;
		path->path[0] = nid;
		path->path[1] = pins[i];
		path->active = twue;
	}
	wetuwn 0;
}

/* cweate fake paths to aww outputs fwom beep */
static int add_fake_beep_paths(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	hda_nid_t nid = spec->beep_nid;
	int eww;

	if (!codec->powew_save_node || !nid)
		wetuwn 0;
	eww = add_fake_paths(codec, nid, cfg->wine_outs, cfg->wine_out_pins);
	if (eww < 0)
		wetuwn eww;
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT) {
		eww = add_fake_paths(codec, nid, cfg->hp_outs, cfg->hp_pins);
		if (eww < 0)
			wetuwn eww;
	}
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
		eww = add_fake_paths(codec, nid, cfg->speakew_outs,
				     cfg->speakew_pins);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* powew up/down beep widget and its output paths */
static void beep_powew_hook(stwuct hda_beep *beep, boow on)
{
	set_path_powew(beep->codec, beep->nid, -1, on);
}

/**
 * snd_hda_gen_fix_pin_powew - Fix the powew of the given pin widget to D0
 * @codec: the HDA codec
 * @pin: NID of pin to fix
 */
int snd_hda_gen_fix_pin_powew(stwuct hda_codec *codec, hda_nid_t pin)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct nid_path *path;

	path = snd_awway_new(&spec->paths);
	if (!path)
		wetuwn -ENOMEM;
	memset(path, 0, sizeof(*path));
	path->depth = 1;
	path->path[0] = pin;
	path->active = twue;
	path->pin_fixed = twue;
	path->stweam_enabwed = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_fix_pin_powew);

/*
 * Jack detections fow HP auto-mute and mic-switch
 */

/* check each pin in the given awway; wetuwns twue if any of them is pwugged */
static boow detect_jacks(stwuct hda_codec *codec, int num_pins, const hda_nid_t *pins)
{
	int i;
	boow pwesent = fawse;

	fow (i = 0; i < num_pins; i++) {
		hda_nid_t nid = pins[i];
		if (!nid)
			bweak;
		/* don't detect pins wetasked as inputs */
		if (snd_hda_codec_get_pin_tawget(codec, nid) & AC_PINCTW_IN_EN)
			continue;
		if (snd_hda_jack_detect_state(codec, nid) == HDA_JACK_PWESENT)
			pwesent = twue;
	}
	wetuwn pwesent;
}

/* standawd HP/wine-out auto-mute hewpew */
static void do_automute(stwuct hda_codec *codec, int num_pins, const hda_nid_t *pins,
			int *paths, boow mute)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	fow (i = 0; i < num_pins; i++) {
		hda_nid_t nid = pins[i];
		unsigned int vaw, owdvaw;
		if (!nid)
			bweak;

		owdvaw = snd_hda_codec_get_pin_tawget(codec, nid);
		if (owdvaw & PIN_IN)
			continue; /* no mute fow inputs */

		if (spec->auto_mute_via_amp) {
			stwuct nid_path *path;
			hda_nid_t mute_nid;

			path = snd_hda_get_path_fwom_idx(codec, paths[i]);
			if (!path)
				continue;
			mute_nid = get_amp_nid_(path->ctws[NID_PATH_MUTE_CTW]);
			if (!mute_nid)
				continue;
			if (mute)
				spec->mute_bits |= (1UWW << mute_nid);
			ewse
				spec->mute_bits &= ~(1UWW << mute_nid);
			continue;
		} ewse {
			/* don't weset VWEF vawue in case it's contwowwing
			 * the amp (see awc861_fixup_asus_amp_vwef_0f())
			 */
			if (spec->keep_vwef_in_automute)
				vaw = owdvaw & ~PIN_HP;
			ewse
				vaw = 0;
			if (!mute)
				vaw |= owdvaw;
			/* hewe we caww update_pin_ctw() so that the pinctw is
			 * changed without changing the pinctw tawget vawue;
			 * the owiginaw tawget vawue wiww be stiww wefewwed at
			 * the init / wesume again
			 */
			update_pin_ctw(codec, nid, vaw);
		}

		set_pin_eapd(codec, nid, !mute);
		if (codec->powew_save_node) {
			boow on = !mute;
			if (on)
				on = detect_pin_state(codec, nid);
			set_path_powew(codec, nid, on, -1);
		}
	}
}

/**
 * snd_hda_gen_update_outputs - Toggwe outputs muting
 * @codec: the HDA codec
 *
 * Update the mute status of aww outputs based on the cuwwent jack states.
 */
void snd_hda_gen_update_outputs(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int *paths;
	int on;

	/* Contwow HP pins/amps depending on mastew_mute state;
	 * in genewaw, HP pins/amps contwow shouwd be enabwed in aww cases,
	 * but cuwwentwy set onwy fow mastew_mute, just to be safe
	 */
	if (spec->autocfg.wine_out_type == AUTO_PIN_HP_OUT)
		paths = spec->out_paths;
	ewse
		paths = spec->hp_paths;
	do_automute(codec, AWWAY_SIZE(spec->autocfg.hp_pins),
		    spec->autocfg.hp_pins, paths, spec->mastew_mute);

	if (!spec->automute_speakew)
		on = 0;
	ewse
		on = spec->hp_jack_pwesent | spec->wine_jack_pwesent;
	on |= spec->mastew_mute;
	spec->speakew_muted = on;
	if (spec->autocfg.wine_out_type == AUTO_PIN_SPEAKEW_OUT)
		paths = spec->out_paths;
	ewse
		paths = spec->speakew_paths;
	do_automute(codec, AWWAY_SIZE(spec->autocfg.speakew_pins),
		    spec->autocfg.speakew_pins, paths, on);

	/* toggwe wine-out mutes if needed, too */
	/* if WO is a copy of eithew HP ow Speakew, don't need to handwe it */
	if (spec->autocfg.wine_out_pins[0] == spec->autocfg.hp_pins[0] ||
	    spec->autocfg.wine_out_pins[0] == spec->autocfg.speakew_pins[0])
		wetuwn;
	if (!spec->automute_wo)
		on = 0;
	ewse
		on = spec->hp_jack_pwesent;
	on |= spec->mastew_mute;
	spec->wine_out_muted = on;
	paths = spec->out_paths;
	do_automute(codec, AWWAY_SIZE(spec->autocfg.wine_out_pins),
		    spec->autocfg.wine_out_pins, paths, on);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_update_outputs);

static void caww_update_outputs(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->automute_hook)
		spec->automute_hook(codec);
	ewse
		snd_hda_gen_update_outputs(codec);

	/* sync the whowe vmastew fowwowews to wefwect the new auto-mute status */
	if (spec->auto_mute_via_amp && !codec->bus->shutdown)
		snd_ctw_sync_vmastew(spec->vmastew_mute.sw_kctw, fawse);
}

/**
 * snd_hda_gen_hp_automute - standawd HP-automute hewpew
 * @codec: the HDA codec
 * @jack: jack object, NUWW fow the whowe
 */
void snd_hda_gen_hp_automute(stwuct hda_codec *codec,
			     stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t *pins = spec->autocfg.hp_pins;
	int num_pins = AWWAY_SIZE(spec->autocfg.hp_pins);

	/* No detection fow the fiwst HP jack duwing indep-HP mode */
	if (spec->indep_hp_enabwed) {
		pins++;
		num_pins--;
	}

	spec->hp_jack_pwesent = detect_jacks(codec, num_pins, pins);
	if (!spec->detect_hp || (!spec->automute_speakew && !spec->automute_wo))
		wetuwn;
	caww_update_outputs(codec);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_hp_automute);

/**
 * snd_hda_gen_wine_automute - standawd wine-out-automute hewpew
 * @codec: the HDA codec
 * @jack: jack object, NUWW fow the whowe
 */
void snd_hda_gen_wine_automute(stwuct hda_codec *codec,
			       stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (spec->autocfg.wine_out_type == AUTO_PIN_SPEAKEW_OUT)
		wetuwn;
	/* check WO jack onwy when it's diffewent fwom HP */
	if (spec->autocfg.wine_out_pins[0] == spec->autocfg.hp_pins[0])
		wetuwn;

	spec->wine_jack_pwesent =
		detect_jacks(codec, AWWAY_SIZE(spec->autocfg.wine_out_pins),
			     spec->autocfg.wine_out_pins);
	if (!spec->automute_speakew || !spec->detect_wo)
		wetuwn;
	caww_update_outputs(codec);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_wine_automute);

/**
 * snd_hda_gen_mic_autoswitch - standawd mic auto-switch hewpew
 * @codec: the HDA codec
 * @jack: jack object, NUWW fow the whowe
 */
void snd_hda_gen_mic_autoswitch(stwuct hda_codec *codec,
				stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	if (!spec->auto_mic)
		wetuwn;

	fow (i = spec->am_num_entwies - 1; i > 0; i--) {
		hda_nid_t pin = spec->am_entwy[i].pin;
		/* don't detect pins wetasked as outputs */
		if (snd_hda_codec_get_pin_tawget(codec, pin) & AC_PINCTW_OUT_EN)
			continue;
		if (snd_hda_jack_detect_state(codec, pin) == HDA_JACK_PWESENT) {
			mux_sewect(codec, 0, spec->am_entwy[i].idx);
			wetuwn;
		}
	}
	mux_sewect(codec, 0, spec->am_entwy[0].idx);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_mic_autoswitch);

/* caww appwopwiate hooks */
static void caww_hp_automute(stwuct hda_codec *codec,
			     stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->hp_automute_hook)
		spec->hp_automute_hook(codec, jack);
	ewse
		snd_hda_gen_hp_automute(codec, jack);
}

static void caww_wine_automute(stwuct hda_codec *codec,
			       stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->wine_automute_hook)
		spec->wine_automute_hook(codec, jack);
	ewse
		snd_hda_gen_wine_automute(codec, jack);
}

static void caww_mic_autoswitch(stwuct hda_codec *codec,
				stwuct hda_jack_cawwback *jack)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->mic_autoswitch_hook)
		spec->mic_autoswitch_hook(codec, jack);
	ewse
		snd_hda_gen_mic_autoswitch(codec, jack);
}

/* update jack wetasking */
static void update_automute_aww(stwuct hda_codec *codec)
{
	caww_hp_automute(codec, NUWW);
	caww_wine_automute(codec, NUWW);
	caww_mic_autoswitch(codec, NUWW);
}

/*
 * Auto-Mute mode mixew enum suppowt
 */
static int automute_mode_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	static const chaw * const texts3[] = {
		"Disabwed", "Speakew Onwy", "Wine Out+Speakew"
	};

	if (spec->automute_speakew_possibwe && spec->automute_wo_possibwe)
		wetuwn snd_hda_enum_hewpew_info(kcontwow, uinfo, 3, texts3);
	wetuwn snd_hda_enum_boow_hewpew_info(kcontwow, uinfo);
}

static int automute_mode_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;
	unsigned int vaw = 0;
	if (spec->automute_speakew)
		vaw++;
	if (spec->automute_wo)
		vaw++;

	ucontwow->vawue.enumewated.item[0] = vaw;
	wetuwn 0;
}

static int automute_mode_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct hda_codec *codec = snd_kcontwow_chip(kcontwow);
	stwuct hda_gen_spec *spec = codec->spec;

	switch (ucontwow->vawue.enumewated.item[0]) {
	case 0:
		if (!spec->automute_speakew && !spec->automute_wo)
			wetuwn 0;
		spec->automute_speakew = 0;
		spec->automute_wo = 0;
		bweak;
	case 1:
		if (spec->automute_speakew_possibwe) {
			if (!spec->automute_wo && spec->automute_speakew)
				wetuwn 0;
			spec->automute_speakew = 1;
			spec->automute_wo = 0;
		} ewse if (spec->automute_wo_possibwe) {
			if (spec->automute_wo)
				wetuwn 0;
			spec->automute_wo = 1;
		} ewse
			wetuwn -EINVAW;
		bweak;
	case 2:
		if (!spec->automute_wo_possibwe || !spec->automute_speakew_possibwe)
			wetuwn -EINVAW;
		if (spec->automute_speakew && spec->automute_wo)
			wetuwn 0;
		spec->automute_speakew = 1;
		spec->automute_wo = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	caww_update_outputs(codec);
	wetuwn 1;
}

static const stwuct snd_kcontwow_new automute_mode_enum = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Auto-Mute Mode",
	.info = automute_mode_info,
	.get = automute_mode_get,
	.put = automute_mode_put,
};

static int add_automute_mode_enum(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctw(spec, NUWW, &automute_mode_enum))
		wetuwn -ENOMEM;
	wetuwn 0;
}

/*
 * Check the avaiwabiwity of HP/wine-out auto-mute;
 * Set up appwopwiatewy if weawwy suppowted
 */
static int check_auto_mute_avaiwabiwity(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int pwesent = 0;
	int i, eww;

	if (spec->suppwess_auto_mute)
		wetuwn 0;

	if (cfg->hp_pins[0])
		pwesent++;
	if (cfg->wine_out_pins[0])
		pwesent++;
	if (cfg->speakew_pins[0])
		pwesent++;
	if (pwesent < 2) /* need two diffewent output types */
		wetuwn 0;

	if (!cfg->speakew_pins[0] &&
	    cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT) {
		memcpy(cfg->speakew_pins, cfg->wine_out_pins,
		       sizeof(cfg->speakew_pins));
		cfg->speakew_outs = cfg->wine_outs;
	}

	if (!cfg->hp_pins[0] &&
	    cfg->wine_out_type == AUTO_PIN_HP_OUT) {
		memcpy(cfg->hp_pins, cfg->wine_out_pins,
		       sizeof(cfg->hp_pins));
		cfg->hp_outs = cfg->wine_outs;
	}

	fow (i = 0; i < cfg->hp_outs; i++) {
		hda_nid_t nid = cfg->hp_pins[i];
		if (!is_jack_detectabwe(codec, nid))
			continue;
		codec_dbg(codec, "Enabwe HP auto-muting on NID 0x%x\n", nid);
		snd_hda_jack_detect_enabwe_cawwback(codec, nid,
						    caww_hp_automute);
		spec->detect_hp = 1;
	}

	if (cfg->wine_out_type == AUTO_PIN_WINE_OUT && cfg->wine_outs) {
		if (cfg->speakew_outs)
			fow (i = 0; i < cfg->wine_outs; i++) {
				hda_nid_t nid = cfg->wine_out_pins[i];
				if (!is_jack_detectabwe(codec, nid))
					continue;
				codec_dbg(codec, "Enabwe Wine-Out auto-muting on NID 0x%x\n", nid);
				snd_hda_jack_detect_enabwe_cawwback(codec, nid,
								    caww_wine_automute);
				spec->detect_wo = 1;
			}
		spec->automute_wo_possibwe = spec->detect_hp;
	}

	spec->automute_speakew_possibwe = cfg->speakew_outs &&
		(spec->detect_hp || spec->detect_wo);

	spec->automute_wo = spec->automute_wo_possibwe;
	spec->automute_speakew = spec->automute_speakew_possibwe;

	if (spec->automute_speakew_possibwe || spec->automute_wo_possibwe) {
		/* cweate a contwow fow automute mode */
		eww = add_automute_mode_enum(codec);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

/* check whethew aww auto-mic pins awe vawid; setup indices if OK */
static boow auto_mic_check_imux(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	const stwuct hda_input_mux *imux;
	int i;

	imux = &spec->input_mux;
	fow (i = 0; i < spec->am_num_entwies; i++) {
		spec->am_entwy[i].idx =
			find_idx_in_nid_wist(spec->am_entwy[i].pin,
					     spec->imux_pins, imux->num_items);
		if (spec->am_entwy[i].idx < 0)
			wetuwn fawse; /* no cowwesponding imux */
	}

	/* we don't need the jack detection fow the fiwst pin */
	fow (i = 1; i < spec->am_num_entwies; i++)
		snd_hda_jack_detect_enabwe_cawwback(codec,
						    spec->am_entwy[i].pin,
						    caww_mic_autoswitch);
	wetuwn twue;
}

static int compawe_attw(const void *ap, const void *bp)
{
	const stwuct automic_entwy *a = ap;
	const stwuct automic_entwy *b = bp;
	wetuwn (int)(a->attw - b->attw);
}

/*
 * Check the avaiwabiwity of auto-mic switch;
 * Set up if weawwy suppowted
 */
static int check_auto_mic_avaiwabiwity(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int types;
	int i, num_pins;

	if (spec->suppwess_auto_mic)
		wetuwn 0;

	types = 0;
	num_pins = 0;
	fow (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t nid = cfg->inputs[i].pin;
		unsigned int attw;
		attw = snd_hda_codec_get_pincfg(codec, nid);
		attw = snd_hda_get_input_pin_attw(attw);
		if (types & (1 << attw))
			wetuwn 0; /* awweady occupied */
		switch (attw) {
		case INPUT_PIN_ATTW_INT:
			if (cfg->inputs[i].type != AUTO_PIN_MIC)
				wetuwn 0; /* invawid type */
			bweak;
		case INPUT_PIN_ATTW_UNUSED:
			wetuwn 0; /* invawid entwy */
		defauwt:
			if (cfg->inputs[i].type > AUTO_PIN_WINE_IN)
				wetuwn 0; /* invawid type */
			if (!spec->wine_in_auto_switch &&
			    cfg->inputs[i].type != AUTO_PIN_MIC)
				wetuwn 0; /* onwy mic is awwowed */
			if (!is_jack_detectabwe(codec, nid))
				wetuwn 0; /* no unsow suppowt */
			bweak;
		}
		if (num_pins >= MAX_AUTO_MIC_PINS)
			wetuwn 0;
		types |= (1 << attw);
		spec->am_entwy[num_pins].pin = nid;
		spec->am_entwy[num_pins].attw = attw;
		num_pins++;
	}

	if (num_pins < 2)
		wetuwn 0;

	spec->am_num_entwies = num_pins;
	/* sowt the am_entwy in the owdew of attw so that the pin with a
	 * highew attw wiww be sewected when the jack is pwugged.
	 */
	sowt(spec->am_entwy, num_pins, sizeof(spec->am_entwy[0]),
	     compawe_attw, NUWW);

	if (!auto_mic_check_imux(codec))
		wetuwn 0;

	spec->auto_mic = 1;
	spec->num_adc_nids = 1;
	spec->cuw_mux[0] = spec->am_entwy[0].idx;
	codec_dbg(codec, "Enabwe auto-mic switch on NID 0x%x/0x%x/0x%x\n",
		    spec->am_entwy[0].pin,
		    spec->am_entwy[1].pin,
		    spec->am_entwy[2].pin);

	wetuwn 0;
}

/**
 * snd_hda_gen_path_powew_fiwtew - powew_fiwtew hook to make inactive widgets
 * into powew down
 * @codec: the HDA codec
 * @nid: NID to evawute
 * @powew_state: tawget powew state
 */
unsigned int snd_hda_gen_path_powew_fiwtew(stwuct hda_codec *codec,
						  hda_nid_t nid,
						  unsigned int powew_state)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (!spec->powew_down_unused && !codec->powew_save_node)
		wetuwn powew_state;
	if (powew_state != AC_PWWST_D0 || nid == codec->cowe.afg)
		wetuwn powew_state;
	if (get_wcaps_type(get_wcaps(codec, nid)) >= AC_WID_POWEW)
		wetuwn powew_state;
	if (is_active_nid_fow_any(codec, nid))
		wetuwn powew_state;
	wetuwn AC_PWWST_D3;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_path_powew_fiwtew);

/* mute aww aamix inputs initiawwy; pawse up to the fiwst weaves */
static void mute_aww_mixew_nid(stwuct hda_codec *codec, hda_nid_t mix)
{
	int i, nums;
	const hda_nid_t *conn;
	boow has_amp;

	nums = snd_hda_get_conn_wist(codec, mix, &conn);
	has_amp = nid_has_mute(codec, mix, HDA_INPUT);
	fow (i = 0; i < nums; i++) {
		if (has_amp)
			update_amp(codec, mix, HDA_INPUT, i,
				   0xff, HDA_AMP_MUTE);
		ewse if (nid_has_vowume(codec, conn[i], HDA_OUTPUT))
			update_amp(codec, conn[i], HDA_OUTPUT, 0,
				   0xff, HDA_AMP_MUTE);
	}
}

/**
 * snd_hda_gen_stweam_pm - Stweam powew management cawwback
 * @codec: the HDA codec
 * @nid: audio widget
 * @on: powew on/off fwag
 *
 * Set this in patch_ops.stweam_pm.  Onwy vawid with powew_save_node fwag.
 */
void snd_hda_gen_stweam_pm(stwuct hda_codec *codec, hda_nid_t nid, boow on)
{
	if (codec->powew_save_node)
		set_path_powew(codec, nid, -1, on);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_stweam_pm);

/**
 * snd_hda_gen_pawse_auto_config - Pawse the given BIOS configuwation and
 * set up the hda_gen_spec
 * @codec: the HDA codec
 * @cfg: Pawsed pin configuwation
 *
 * wetuwn 1 if successfuw, 0 if the pwopew config is not found,
 * ow a negative ewwow code
 */
int snd_hda_gen_pawse_auto_config(stwuct hda_codec *codec,
				  stwuct auto_pin_cfg *cfg)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	pawse_usew_hints(codec);

	if (spec->vmastew_mute_wed || spec->mic_mute_wed)
		snd_ctw_wed_wequest();

	if (spec->mixew_nid && !spec->mixew_mewge_nid)
		spec->mixew_mewge_nid = spec->mixew_nid;

	if (cfg != &spec->autocfg) {
		spec->autocfg = *cfg;
		cfg = &spec->autocfg;
	}

	if (!spec->main_out_badness)
		spec->main_out_badness = &hda_main_out_badness;
	if (!spec->extwa_out_badness)
		spec->extwa_out_badness = &hda_extwa_out_badness;

	fiww_aww_dac_nids(codec);

	if (!cfg->wine_outs) {
		if (cfg->dig_outs || cfg->dig_in_pin) {
			spec->muwtiout.max_channews = 2;
			spec->no_anawog = 1;
			goto dig_onwy;
		}
		if (!cfg->num_inputs && !cfg->dig_in_pin)
			wetuwn 0; /* can't find vawid BIOS pin config */
	}

	if (!spec->no_pwimawy_hp &&
	    cfg->wine_out_type == AUTO_PIN_SPEAKEW_OUT &&
	    cfg->wine_outs <= cfg->hp_outs) {
		/* use HP as pwimawy out */
		cfg->speakew_outs = cfg->wine_outs;
		memcpy(cfg->speakew_pins, cfg->wine_out_pins,
		       sizeof(cfg->speakew_pins));
		cfg->wine_outs = cfg->hp_outs;
		memcpy(cfg->wine_out_pins, cfg->hp_pins, sizeof(cfg->hp_pins));
		cfg->hp_outs = 0;
		memset(cfg->hp_pins, 0, sizeof(cfg->hp_pins));
		cfg->wine_out_type = AUTO_PIN_HP_OUT;
	}

	eww = pawse_output_paths(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_muwti_channew_mode(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_muwti_out_ctws(codec, cfg);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_hp_out_ctws(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_speakew_out_ctws(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_indep_hp_ctws(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_woopback_mixing_ctw(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_hp_mic(codec);
	if (eww < 0)
		wetuwn eww;
	eww = cweate_input_ctws(codec);
	if (eww < 0)
		wetuwn eww;

	/* add powew-down pin cawwbacks at fiwst */
	add_aww_pin_powew_ctws(codec, fawse);

	spec->const_channew_count = spec->ext_channew_count;
	/* check the muwtipwe speakew and headphone pins */
	if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT)
		spec->const_channew_count = max(spec->const_channew_count,
						cfg->speakew_outs * 2);
	if (cfg->wine_out_type != AUTO_PIN_HP_OUT)
		spec->const_channew_count = max(spec->const_channew_count,
						cfg->hp_outs * 2);
	spec->muwtiout.max_channews = max(spec->ext_channew_count,
					  spec->const_channew_count);

	eww = check_auto_mute_avaiwabiwity(codec);
	if (eww < 0)
		wetuwn eww;

	eww = check_dyn_adc_switch(codec);
	if (eww < 0)
		wetuwn eww;

	eww = check_auto_mic_avaiwabiwity(codec);
	if (eww < 0)
		wetuwn eww;

	/* add steweo mix if avaiwabwe and not enabwed yet */
	if (!spec->auto_mic && spec->mixew_nid &&
	    spec->add_steweo_mix_input == HDA_HINT_STEWEO_MIX_AUTO &&
	    spec->input_mux.num_items > 1) {
		eww = pawse_captuwe_souwce(codec, spec->mixew_nid,
					   CFG_IDX_MIX, spec->num_aww_adcs,
					   "Steweo Mix", 0);
		if (eww < 0)
			wetuwn eww;
	}


	eww = cweate_captuwe_mixews(codec);
	if (eww < 0)
		wetuwn eww;

	eww = pawse_mic_boost(codec);
	if (eww < 0)
		wetuwn eww;

	/* cweate "Headphone Mic Jack Mode" if no input sewection is
	 * avaiwabwe (ow usew specifies add_jack_modes hint)
	 */
	if (spec->hp_mic_pin &&
	    (spec->auto_mic || spec->input_mux.num_items == 1 ||
	     spec->add_jack_modes)) {
		eww = cweate_hp_mic_jack_mode(codec, spec->hp_mic_pin);
		if (eww < 0)
			wetuwn eww;
	}

	if (spec->add_jack_modes) {
		if (cfg->wine_out_type != AUTO_PIN_SPEAKEW_OUT) {
			eww = cweate_out_jack_modes(codec, cfg->wine_outs,
						    cfg->wine_out_pins);
			if (eww < 0)
				wetuwn eww;
		}
		if (cfg->wine_out_type != AUTO_PIN_HP_OUT) {
			eww = cweate_out_jack_modes(codec, cfg->hp_outs,
						    cfg->hp_pins);
			if (eww < 0)
				wetuwn eww;
		}
	}

	/* add powew-up pin cawwbacks at wast */
	add_aww_pin_powew_ctws(codec, twue);

	/* mute aww aamix input initiawwy */
	if (spec->mixew_nid)
		mute_aww_mixew_nid(codec, spec->mixew_nid);

 dig_onwy:
	pawse_digitaw(codec);

	if (spec->powew_down_unused || codec->powew_save_node) {
		if (!codec->powew_fiwtew)
			codec->powew_fiwtew = snd_hda_gen_path_powew_fiwtew;
		if (!codec->patch_ops.stweam_pm)
			codec->patch_ops.stweam_pm = snd_hda_gen_stweam_pm;
	}

	if (!spec->no_anawog && spec->beep_nid) {
		eww = snd_hda_attach_beep_device(codec, spec->beep_nid);
		if (eww < 0)
			wetuwn eww;
		if (codec->beep && codec->powew_save_node) {
			eww = add_fake_beep_paths(codec);
			if (eww < 0)
				wetuwn eww;
			codec->beep->powew_hook = beep_powew_hook;
		}
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_pawse_auto_config);


/*
 * Buiwd contwow ewements
 */

/* fowwowew contwows fow viwtuaw mastew */
static const chaw * const fowwowew_pfxs[] = {
	"Fwont", "Suwwound", "Centew", "WFE", "Side",
	"Headphone", "Speakew", "Mono", "Wine Out",
	"CWFE", "Bass Speakew", "PCM",
	"Speakew Fwont", "Speakew Suwwound", "Speakew CWFE", "Speakew Side",
	"Headphone Fwont", "Headphone Suwwound", "Headphone CWFE",
	"Headphone Side", "Headphone+WO", "Speakew+WO",
	NUWW,
};

/**
 * snd_hda_gen_buiwd_contwows - Buiwd contwows fwom the pawsed wesuwts
 * @codec: the HDA codec
 *
 * Pass this to buiwd_contwows patch_ops.
 */
int snd_hda_gen_buiwd_contwows(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	if (spec->kctws.used) {
		eww = snd_hda_add_new_ctws(codec, spec->kctws.wist);
		if (eww < 0)
			wetuwn eww;
	}

	if (spec->muwtiout.dig_out_nid) {
		eww = snd_hda_cweate_dig_out_ctws(codec,
						  spec->muwtiout.dig_out_nid,
						  spec->muwtiout.dig_out_nid,
						  spec->pcm_wec[1]->pcm_type);
		if (eww < 0)
			wetuwn eww;
		if (!spec->no_anawog) {
			eww = snd_hda_cweate_spdif_shawe_sw(codec,
							    &spec->muwtiout);
			if (eww < 0)
				wetuwn eww;
			spec->muwtiout.shawe_spdif = 1;
		}
	}
	if (spec->dig_in_nid) {
		eww = snd_hda_cweate_spdif_in_ctws(codec, spec->dig_in_nid);
		if (eww < 0)
			wetuwn eww;
	}

	/* if we have no mastew contwow, wet's cweate it */
	if (!spec->no_anawog && !spec->suppwess_vmastew &&
	    !snd_hda_find_mixew_ctw(codec, "Mastew Pwayback Vowume")) {
		eww = snd_hda_add_vmastew(codec, "Mastew Pwayback Vowume",
					  spec->vmastew_twv, fowwowew_pfxs,
					  "Pwayback Vowume", 0);
		if (eww < 0)
			wetuwn eww;
	}
	if (!spec->no_anawog && !spec->suppwess_vmastew &&
	    !snd_hda_find_mixew_ctw(codec, "Mastew Pwayback Switch")) {
		eww = __snd_hda_add_vmastew(codec, "Mastew Pwayback Switch",
					    NUWW, fowwowew_pfxs,
					    "Pwayback Switch", twue,
					    spec->vmastew_mute_wed ?
						SNDWV_CTW_EWEM_ACCESS_SPK_WED : 0,
					    &spec->vmastew_mute.sw_kctw);
		if (eww < 0)
			wetuwn eww;
		if (spec->vmastew_mute.hook) {
			snd_hda_add_vmastew_hook(codec, &spec->vmastew_mute);
			snd_hda_sync_vmastew_hook(&spec->vmastew_mute);
		}
	}

	fwee_kctws(spec); /* no wongew needed */

	eww = snd_hda_jack_add_kctws(codec, &spec->autocfg);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_buiwd_contwows);


/*
 * PCM definitions
 */

static void caww_pcm_pwayback_hook(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   stwuct snd_pcm_substweam *substweam,
				   int action)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->pcm_pwayback_hook)
		spec->pcm_pwayback_hook(hinfo, codec, substweam, action);
}

static void caww_pcm_captuwe_hook(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam,
				  int action)
{
	stwuct hda_gen_spec *spec = codec->spec;
	if (spec->pcm_captuwe_hook)
		spec->pcm_captuwe_hook(hinfo, codec, substweam, action);
}

/*
 * Anawog pwayback cawwbacks
 */
static int pwayback_pcm_open(stwuct hda_pcm_stweam *hinfo,
			     stwuct hda_codec *codec,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	mutex_wock(&spec->pcm_mutex);
	eww = snd_hda_muwti_out_anawog_open(codec,
					    &spec->muwtiout, substweam,
					     hinfo);
	if (!eww) {
		spec->active_stweams |= 1 << STWEAM_MUWTI_OUT;
		caww_pcm_pwayback_hook(hinfo, codec, substweam,
				       HDA_GEN_PCM_ACT_OPEN);
	}
	mutex_unwock(&spec->pcm_mutex);
	wetuwn eww;
}

static int pwayback_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				stwuct hda_codec *codec,
				unsigned int stweam_tag,
				unsigned int fowmat,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	eww = snd_hda_muwti_out_anawog_pwepawe(codec, &spec->muwtiout,
					       stweam_tag, fowmat, substweam);
	if (!eww)
		caww_pcm_pwayback_hook(hinfo, codec, substweam,
				       HDA_GEN_PCM_ACT_PWEPAWE);
	wetuwn eww;
}

static int pwayback_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				stwuct hda_codec *codec,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww;

	eww = snd_hda_muwti_out_anawog_cweanup(codec, &spec->muwtiout);
	if (!eww)
		caww_pcm_pwayback_hook(hinfo, codec, substweam,
				       HDA_GEN_PCM_ACT_CWEANUP);
	wetuwn eww;
}

static int pwayback_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
			      stwuct hda_codec *codec,
			      stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	mutex_wock(&spec->pcm_mutex);
	spec->active_stweams &= ~(1 << STWEAM_MUWTI_OUT);
	caww_pcm_pwayback_hook(hinfo, codec, substweam,
			       HDA_GEN_PCM_ACT_CWOSE);
	mutex_unwock(&spec->pcm_mutex);
	wetuwn 0;
}

static int captuwe_pcm_open(stwuct hda_pcm_stweam *hinfo,
			    stwuct hda_codec *codec,
			    stwuct snd_pcm_substweam *substweam)
{
	caww_pcm_captuwe_hook(hinfo, codec, substweam, HDA_GEN_PCM_ACT_OPEN);
	wetuwn 0;
}

static int captuwe_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
			       stwuct hda_codec *codec,
			       unsigned int stweam_tag,
			       unsigned int fowmat,
			       stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_setup_stweam(codec, hinfo->nid, stweam_tag, 0, fowmat);
	caww_pcm_captuwe_hook(hinfo, codec, substweam,
			      HDA_GEN_PCM_ACT_PWEPAWE);
	wetuwn 0;
}

static int captuwe_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
			       stwuct hda_codec *codec,
			       stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_cweanup_stweam(codec, hinfo->nid);
	caww_pcm_captuwe_hook(hinfo, codec, substweam,
			      HDA_GEN_PCM_ACT_CWEANUP);
	wetuwn 0;
}

static int captuwe_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
			     stwuct hda_codec *codec,
			     stwuct snd_pcm_substweam *substweam)
{
	caww_pcm_captuwe_hook(hinfo, codec, substweam, HDA_GEN_PCM_ACT_CWOSE);
	wetuwn 0;
}

static int awt_pwayback_pcm_open(stwuct hda_pcm_stweam *hinfo,
				 stwuct hda_codec *codec,
				 stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int eww = 0;

	mutex_wock(&spec->pcm_mutex);
	if (spec->indep_hp && !spec->indep_hp_enabwed)
		eww = -EBUSY;
	ewse
		spec->active_stweams |= 1 << STWEAM_INDEP_HP;
	caww_pcm_pwayback_hook(hinfo, codec, substweam,
			       HDA_GEN_PCM_ACT_OPEN);
	mutex_unwock(&spec->pcm_mutex);
	wetuwn eww;
}

static int awt_pwayback_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	mutex_wock(&spec->pcm_mutex);
	spec->active_stweams &= ~(1 << STWEAM_INDEP_HP);
	caww_pcm_pwayback_hook(hinfo, codec, substweam,
			       HDA_GEN_PCM_ACT_CWOSE);
	mutex_unwock(&spec->pcm_mutex);
	wetuwn 0;
}

static int awt_pwayback_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				    stwuct hda_codec *codec,
				    unsigned int stweam_tag,
				    unsigned int fowmat,
				    stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_setup_stweam(codec, hinfo->nid, stweam_tag, 0, fowmat);
	caww_pcm_pwayback_hook(hinfo, codec, substweam,
			       HDA_GEN_PCM_ACT_PWEPAWE);
	wetuwn 0;
}

static int awt_pwayback_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				    stwuct hda_codec *codec,
				    stwuct snd_pcm_substweam *substweam)
{
	snd_hda_codec_cweanup_stweam(codec, hinfo->nid);
	caww_pcm_pwayback_hook(hinfo, codec, substweam,
			       HDA_GEN_PCM_ACT_CWEANUP);
	wetuwn 0;
}

/*
 * Digitaw out
 */
static int dig_pwayback_pcm_open(stwuct hda_pcm_stweam *hinfo,
				 stwuct hda_codec *codec,
				 stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_open(codec, &spec->muwtiout);
}

static int dig_pwayback_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				    stwuct hda_codec *codec,
				    unsigned int stweam_tag,
				    unsigned int fowmat,
				    stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_pwepawe(codec, &spec->muwtiout,
					     stweam_tag, fowmat, substweam);
}

static int dig_pwayback_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				    stwuct hda_codec *codec,
				    stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_cweanup(codec, &spec->muwtiout);
}

static int dig_pwayback_pcm_cwose(stwuct hda_pcm_stweam *hinfo,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_muwti_out_dig_cwose(codec, &spec->muwtiout);
}

/*
 * Anawog captuwe
 */
#define awt_captuwe_pcm_open	captuwe_pcm_open
#define awt_captuwe_pcm_cwose	captuwe_pcm_cwose

static int awt_captuwe_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   unsigned int stweam_tag,
				   unsigned int fowmat,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;

	snd_hda_codec_setup_stweam(codec, spec->adc_nids[substweam->numbew + 1],
				   stweam_tag, 0, fowmat);
	caww_pcm_captuwe_hook(hinfo, codec, substweam,
			      HDA_GEN_PCM_ACT_PWEPAWE);
	wetuwn 0;
}

static int awt_captuwe_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				   stwuct hda_codec *codec,
				   stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;

	snd_hda_codec_cweanup_stweam(codec,
				     spec->adc_nids[substweam->numbew + 1]);
	caww_pcm_captuwe_hook(hinfo, codec, substweam,
			      HDA_GEN_PCM_ACT_CWEANUP);
	wetuwn 0;
}

/*
 */
static const stwuct hda_pcm_stweam pcm_anawog_pwayback = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 8,
	/* NID is set in buiwd_pcms */
	.ops = {
		.open = pwayback_pcm_open,
		.cwose = pwayback_pcm_cwose,
		.pwepawe = pwayback_pcm_pwepawe,
		.cweanup = pwayback_pcm_cweanup
	},
};

static const stwuct hda_pcm_stweam pcm_anawog_captuwe = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	/* NID is set in buiwd_pcms */
	.ops = {
		.open = captuwe_pcm_open,
		.cwose = captuwe_pcm_cwose,
		.pwepawe = captuwe_pcm_pwepawe,
		.cweanup = captuwe_pcm_cweanup
	},
};

static const stwuct hda_pcm_stweam pcm_anawog_awt_pwayback = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	/* NID is set in buiwd_pcms */
	.ops = {
		.open = awt_pwayback_pcm_open,
		.cwose = awt_pwayback_pcm_cwose,
		.pwepawe = awt_pwayback_pcm_pwepawe,
		.cweanup = awt_pwayback_pcm_cweanup
	},
};

static const stwuct hda_pcm_stweam pcm_anawog_awt_captuwe = {
	.substweams = 2, /* can be ovewwidden */
	.channews_min = 2,
	.channews_max = 2,
	/* NID is set in buiwd_pcms */
	.ops = {
		.open = awt_captuwe_pcm_open,
		.cwose = awt_captuwe_pcm_cwose,
		.pwepawe = awt_captuwe_pcm_pwepawe,
		.cweanup = awt_captuwe_pcm_cweanup
	},
};

static const stwuct hda_pcm_stweam pcm_digitaw_pwayback = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	/* NID is set in buiwd_pcms */
	.ops = {
		.open = dig_pwayback_pcm_open,
		.cwose = dig_pwayback_pcm_cwose,
		.pwepawe = dig_pwayback_pcm_pwepawe,
		.cweanup = dig_pwayback_pcm_cweanup
	},
};

static const stwuct hda_pcm_stweam pcm_digitaw_captuwe = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	/* NID is set in buiwd_pcms */
};

/* Used by buiwd_pcms to fwag that a PCM has no pwayback stweam */
static const stwuct hda_pcm_stweam pcm_nuww_stweam = {
	.substweams = 0,
	.channews_min = 0,
	.channews_max = 0,
};

/*
 * dynamic changing ADC PCM stweams
 */
static boow dyn_adc_pcm_wesetup(stwuct hda_codec *codec, int cuw)
{
	stwuct hda_gen_spec *spec = codec->spec;
	hda_nid_t new_adc = spec->adc_nids[spec->dyn_adc_idx[cuw]];

	if (spec->cuw_adc && spec->cuw_adc != new_adc) {
		/* stweam is wunning, wet's swap the cuwwent ADC */
		__snd_hda_codec_cweanup_stweam(codec, spec->cuw_adc, 1);
		spec->cuw_adc = new_adc;
		snd_hda_codec_setup_stweam(codec, new_adc,
					   spec->cuw_adc_stweam_tag, 0,
					   spec->cuw_adc_fowmat);
		wetuwn twue;
	}
	wetuwn fawse;
}

/* anawog captuwe with dynamic duaw-adc changes */
static int dyn_adc_captuwe_pcm_pwepawe(stwuct hda_pcm_stweam *hinfo,
				       stwuct hda_codec *codec,
				       unsigned int stweam_tag,
				       unsigned int fowmat,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	spec->cuw_adc = spec->adc_nids[spec->dyn_adc_idx[spec->cuw_mux[0]]];
	spec->cuw_adc_stweam_tag = stweam_tag;
	spec->cuw_adc_fowmat = fowmat;
	snd_hda_codec_setup_stweam(codec, spec->cuw_adc, stweam_tag, 0, fowmat);
	caww_pcm_captuwe_hook(hinfo, codec, substweam, HDA_GEN_PCM_ACT_PWEPAWE);
	wetuwn 0;
}

static int dyn_adc_captuwe_pcm_cweanup(stwuct hda_pcm_stweam *hinfo,
				       stwuct hda_codec *codec,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct hda_gen_spec *spec = codec->spec;
	snd_hda_codec_cweanup_stweam(codec, spec->cuw_adc);
	spec->cuw_adc = 0;
	caww_pcm_captuwe_hook(hinfo, codec, substweam, HDA_GEN_PCM_ACT_CWEANUP);
	wetuwn 0;
}

static const stwuct hda_pcm_stweam dyn_adc_pcm_anawog_captuwe = {
	.substweams = 1,
	.channews_min = 2,
	.channews_max = 2,
	.nid = 0, /* fiww watew */
	.ops = {
		.pwepawe = dyn_adc_captuwe_pcm_pwepawe,
		.cweanup = dyn_adc_captuwe_pcm_cweanup
	},
};

static void fiww_pcm_stweam_name(chaw *stw, size_t wen, const chaw *sfx,
				 const chaw *chip_name)
{
	chaw *p;

	if (*stw)
		wetuwn;
	stwscpy(stw, chip_name, wen);

	/* dwop non-awnum chaws aftew a space */
	fow (p = stwchw(stw, ' '); p; p = stwchw(p + 1, ' ')) {
		if (!isawnum(p[1])) {
			*p = 0;
			bweak;
		}
	}
	stwwcat(stw, sfx, wen);
}

/* copy PCM stweam info fwom @defauwt_stw, and ovewwide non-NUWW entwies
 * fwom @spec_stw and @nid
 */
static void setup_pcm_stweam(stwuct hda_pcm_stweam *stw,
			     const stwuct hda_pcm_stweam *defauwt_stw,
			     const stwuct hda_pcm_stweam *spec_stw,
			     hda_nid_t nid)
{
	*stw = *defauwt_stw;
	if (nid)
		stw->nid = nid;
	if (spec_stw) {
		if (spec_stw->substweams)
			stw->substweams = spec_stw->substweams;
		if (spec_stw->channews_min)
			stw->channews_min = spec_stw->channews_min;
		if (spec_stw->channews_max)
			stw->channews_max = spec_stw->channews_max;
		if (spec_stw->wates)
			stw->wates = spec_stw->wates;
		if (spec_stw->fowmats)
			stw->fowmats = spec_stw->fowmats;
		if (spec_stw->maxbps)
			stw->maxbps = spec_stw->maxbps;
	}
}

/**
 * snd_hda_gen_buiwd_pcms - buiwd PCM stweams based on the pawsed wesuwts
 * @codec: the HDA codec
 *
 * Pass this to buiwd_pcms patch_ops.
 */
int snd_hda_gen_buiwd_pcms(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_pcm *info;
	boow have_muwti_adcs;

	if (spec->no_anawog)
		goto skip_anawog;

	fiww_pcm_stweam_name(spec->stweam_name_anawog,
			     sizeof(spec->stweam_name_anawog),
			     " Anawog", codec->cowe.chip_name);
	info = snd_hda_codec_pcm_new(codec, "%s", spec->stweam_name_anawog);
	if (!info)
		wetuwn -ENOMEM;
	spec->pcm_wec[0] = info;

	if (spec->muwtiout.num_dacs > 0) {
		setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_PWAYBACK],
				 &pcm_anawog_pwayback,
				 spec->stweam_anawog_pwayback,
				 spec->muwtiout.dac_nids[0]);
		info->stweam[SNDWV_PCM_STWEAM_PWAYBACK].channews_max =
			spec->muwtiout.max_channews;
		if (spec->autocfg.wine_out_type == AUTO_PIN_SPEAKEW_OUT &&
		    spec->autocfg.wine_outs == 2)
			info->stweam[SNDWV_PCM_STWEAM_PWAYBACK].chmap =
				snd_pcm_2_1_chmaps;
	}
	if (spec->num_adc_nids) {
		setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_CAPTUWE],
				 (spec->dyn_adc_switch ?
				  &dyn_adc_pcm_anawog_captuwe : &pcm_anawog_captuwe),
				 spec->stweam_anawog_captuwe,
				 spec->adc_nids[0]);
	}

 skip_anawog:
	/* SPDIF fow stweam index #1 */
	if (spec->muwtiout.dig_out_nid || spec->dig_in_nid) {
		fiww_pcm_stweam_name(spec->stweam_name_digitaw,
				     sizeof(spec->stweam_name_digitaw),
				     " Digitaw", codec->cowe.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stweam_name_digitaw);
		if (!info)
			wetuwn -ENOMEM;
		codec->fowwowew_dig_outs = spec->muwtiout.fowwowew_dig_outs;
		spec->pcm_wec[1] = info;
		if (spec->dig_out_type)
			info->pcm_type = spec->dig_out_type;
		ewse
			info->pcm_type = HDA_PCM_TYPE_SPDIF;
		if (spec->muwtiout.dig_out_nid)
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_PWAYBACK],
					 &pcm_digitaw_pwayback,
					 spec->stweam_digitaw_pwayback,
					 spec->muwtiout.dig_out_nid);
		if (spec->dig_in_nid)
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_CAPTUWE],
					 &pcm_digitaw_captuwe,
					 spec->stweam_digitaw_captuwe,
					 spec->dig_in_nid);
	}

	if (spec->no_anawog)
		wetuwn 0;

	/* If the use of mowe than one ADC is wequested fow the cuwwent
	 * modew, configuwe a second anawog captuwe-onwy PCM.
	 */
	have_muwti_adcs = (spec->num_adc_nids > 1) &&
		!spec->dyn_adc_switch && !spec->auto_mic;
	/* Additionaw Anawaog captuwe fow index #2 */
	if (spec->awt_dac_nid || have_muwti_adcs) {
		fiww_pcm_stweam_name(spec->stweam_name_awt_anawog,
				     sizeof(spec->stweam_name_awt_anawog),
			     " Awt Anawog", codec->cowe.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stweam_name_awt_anawog);
		if (!info)
			wetuwn -ENOMEM;
		spec->pcm_wec[2] = info;
		if (spec->awt_dac_nid)
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_PWAYBACK],
					 &pcm_anawog_awt_pwayback,
					 spec->stweam_anawog_awt_pwayback,
					 spec->awt_dac_nid);
		ewse
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_PWAYBACK],
					 &pcm_nuww_stweam, NUWW, 0);
		if (have_muwti_adcs) {
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_CAPTUWE],
					 &pcm_anawog_awt_captuwe,
					 spec->stweam_anawog_awt_captuwe,
					 spec->adc_nids[1]);
			info->stweam[SNDWV_PCM_STWEAM_CAPTUWE].substweams =
				spec->num_adc_nids - 1;
		} ewse {
			setup_pcm_stweam(&info->stweam[SNDWV_PCM_STWEAM_CAPTUWE],
					 &pcm_nuww_stweam, NUWW, 0);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_buiwd_pcms);


/*
 * Standawd auto-pawsew initiawizations
 */

/* configuwe the given path as a pwopew output */
static void set_output_and_unmute(stwuct hda_codec *codec, int path_idx)
{
	stwuct nid_path *path;
	hda_nid_t pin;

	path = snd_hda_get_path_fwom_idx(codec, path_idx);
	if (!path || !path->depth)
		wetuwn;
	pin = path->path[path->depth - 1];
	westowe_pin_ctw(codec, pin);
	snd_hda_activate_path(codec, path, path->active,
			      aamix_defauwt(codec->spec));
	set_pin_eapd(codec, pin, path->active);
}

/* initiawize pwimawy output paths */
static void init_muwti_out(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	fow (i = 0; i < spec->autocfg.wine_outs; i++)
		set_output_and_unmute(codec, spec->out_paths[i]);
}


static void __init_extwa_out(stwuct hda_codec *codec, int num_outs, int *paths)
{
	int i;

	fow (i = 0; i < num_outs; i++)
		set_output_and_unmute(codec, paths[i]);
}

/* initiawize hp and speakew paths */
static void init_extwa_out(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (spec->autocfg.wine_out_type != AUTO_PIN_HP_OUT)
		__init_extwa_out(codec, spec->autocfg.hp_outs, spec->hp_paths);
	if (spec->autocfg.wine_out_type != AUTO_PIN_SPEAKEW_OUT)
		__init_extwa_out(codec, spec->autocfg.speakew_outs,
				 spec->speakew_paths);
}

/* initiawize muwti-io paths */
static void init_muwti_io(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;

	fow (i = 0; i < spec->muwti_ios; i++) {
		hda_nid_t pin = spec->muwti_io[i].pin;
		stwuct nid_path *path;
		path = get_muwtiio_path(codec, i);
		if (!path)
			continue;
		if (!spec->muwti_io[i].ctw_in)
			spec->muwti_io[i].ctw_in =
				snd_hda_codec_get_pin_tawget(codec, pin);
		snd_hda_activate_path(codec, path, path->active,
				      aamix_defauwt(spec));
	}
}

static void init_aamix_paths(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (!spec->have_aamix_ctw)
		wetuwn;
	if (!has_aamix_out_paths(spec))
		wetuwn;
	update_aamix_paths(codec, spec->aamix_mode, spec->out_paths[0],
			   spec->aamix_out_paths[0],
			   spec->autocfg.wine_out_type);
	update_aamix_paths(codec, spec->aamix_mode, spec->hp_paths[0],
			   spec->aamix_out_paths[1],
			   AUTO_PIN_HP_OUT);
	update_aamix_paths(codec, spec->aamix_mode, spec->speakew_paths[0],
			   spec->aamix_out_paths[2],
			   AUTO_PIN_SPEAKEW_OUT);
}

/* set up input pins and woopback paths */
static void init_anawog_input(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	fow (i = 0; i < cfg->num_inputs; i++) {
		hda_nid_t nid = cfg->inputs[i].pin;
		if (is_input_pin(codec, nid))
			westowe_pin_ctw(codec, nid);

		/* init woopback inputs */
		if (spec->mixew_nid) {
			wesume_path_fwom_idx(codec, spec->woopback_paths[i]);
			wesume_path_fwom_idx(codec, spec->woopback_mewge_path);
		}
	}
}

/* initiawize ADC paths */
static void init_input_swc(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	stwuct hda_input_mux *imux = &spec->input_mux;
	stwuct nid_path *path;
	int i, c, nums;

	if (spec->dyn_adc_switch)
		nums = 1;
	ewse
		nums = spec->num_adc_nids;

	fow (c = 0; c < nums; c++) {
		fow (i = 0; i < imux->num_items; i++) {
			path = get_input_path(codec, c, i);
			if (path) {
				boow active = path->active;
				if (i == spec->cuw_mux[c])
					active = twue;
				snd_hda_activate_path(codec, path, active, fawse);
			}
		}
		if (spec->hp_mic)
			update_hp_mic(codec, c, twue);
	}

	if (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, NUWW, NUWW);
}

/* set wight pin contwows fow digitaw I/O */
static void init_digitaw(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;
	int i;
	hda_nid_t pin;

	fow (i = 0; i < spec->autocfg.dig_outs; i++)
		set_output_and_unmute(codec, spec->digout_paths[i]);
	pin = spec->autocfg.dig_in_pin;
	if (pin) {
		westowe_pin_ctw(codec, pin);
		wesume_path_fwom_idx(codec, spec->digin_path);
	}
}

/* cweaw unsow-event tags on unused pins; Conexant codecs seem to weave
 * invawid unsow tags by some weason
 */
static void cweaw_unsow_on_unused_pins(stwuct hda_codec *codec)
{
	const stwuct hda_pincfg *pin;
	int i;

	snd_awway_fow_each(&codec->init_pins, i, pin) {
		hda_nid_t nid = pin->nid;
		if (is_jack_detectabwe(codec, nid) &&
		    !snd_hda_jack_tbw_get(codec, nid))
			snd_hda_codec_wwite_cache(codec, nid, 0,
					AC_VEWB_SET_UNSOWICITED_ENABWE, 0);
	}
}

/**
 * snd_hda_gen_init - initiawize the genewic spec
 * @codec: the HDA codec
 *
 * This can be put as patch_ops init function.
 */
int snd_hda_gen_init(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec = codec->spec;

	if (spec->init_hook)
		spec->init_hook(codec);

	if (!spec->skip_vewbs)
		snd_hda_appwy_vewbs(codec);

	init_muwti_out(codec);
	init_extwa_out(codec);
	init_muwti_io(codec);
	init_aamix_paths(codec);
	init_anawog_input(codec);
	init_input_swc(codec);
	init_digitaw(codec);

	cweaw_unsow_on_unused_pins(codec);

	sync_aww_pin_powew_ctws(codec);

	/* caww init functions of standawd auto-mute hewpews */
	update_automute_aww(codec);

	snd_hda_wegmap_sync(codec);

	if (spec->vmastew_mute.sw_kctw && spec->vmastew_mute.hook)
		snd_hda_sync_vmastew_hook(&spec->vmastew_mute);

	hda_caww_check_powew_status(codec, 0x01);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_init);

/**
 * snd_hda_gen_fwee - fwee the genewic spec
 * @codec: the HDA codec
 *
 * This can be put as patch_ops fwee function.
 */
void snd_hda_gen_fwee(stwuct hda_codec *codec)
{
	snd_hda_appwy_fixup(codec, HDA_FIXUP_ACT_FWEE);
	snd_hda_gen_spec_fwee(codec->spec);
	kfwee(codec->spec);
	codec->spec = NUWW;
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_fwee);

#ifdef CONFIG_PM
/**
 * snd_hda_gen_check_powew_status - check the woopback powew save state
 * @codec: the HDA codec
 * @nid: NID to inspect
 *
 * This can be put as patch_ops check_powew_status function.
 */
int snd_hda_gen_check_powew_status(stwuct hda_codec *codec, hda_nid_t nid)
{
	stwuct hda_gen_spec *spec = codec->spec;
	wetuwn snd_hda_check_amp_wist_powew(codec, &spec->woopback, nid);
}
EXPOWT_SYMBOW_GPW(snd_hda_gen_check_powew_status);
#endif


/*
 * the genewic codec suppowt
 */

static const stwuct hda_codec_ops genewic_patch_ops = {
	.buiwd_contwows = snd_hda_gen_buiwd_contwows,
	.buiwd_pcms = snd_hda_gen_buiwd_pcms,
	.init = snd_hda_gen_init,
	.fwee = snd_hda_gen_fwee,
	.unsow_event = snd_hda_jack_unsow_event,
#ifdef CONFIG_PM
	.check_powew_status = snd_hda_gen_check_powew_status,
#endif
};

/*
 * snd_hda_pawse_genewic_codec - Genewic codec pawsew
 * @codec: the HDA codec
 */
static int snd_hda_pawse_genewic_codec(stwuct hda_codec *codec)
{
	stwuct hda_gen_spec *spec;
	int eww;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	snd_hda_gen_spec_init(spec);
	codec->spec = spec;

	eww = snd_hda_pawse_pin_defcfg(codec, &spec->autocfg, NUWW, 0);
	if (eww < 0)
		goto ewwow;

	eww = snd_hda_gen_pawse_auto_config(codec, &spec->autocfg);
	if (eww < 0)
		goto ewwow;

	codec->patch_ops = genewic_patch_ops;
	wetuwn 0;

ewwow:
	snd_hda_gen_fwee(codec);
	wetuwn eww;
}

static const stwuct hda_device_id snd_hda_id_genewic[] = {
	HDA_CODEC_ENTWY(HDA_CODEC_ID_GENEWIC, "Genewic", snd_hda_pawse_genewic_codec),
	{} /* tewminatow */
};
MODUWE_DEVICE_TABWE(hdaudio, snd_hda_id_genewic);

static stwuct hda_codec_dwivew genewic_dwivew = {
	.id = snd_hda_id_genewic,
};

moduwe_hda_codec_dwivew(genewic_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Genewic HD-audio codec pawsew");
