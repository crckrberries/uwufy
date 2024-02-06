// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic woutines and pwoc intewface fow EWD(EDID Wike Data) infowmation
 *
 * Copywight(c) 2008 Intew Cowpowation.
 * Copywight (c) 2013 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *
 * Authows:
 * 		Wu Fengguang <wfg@winux.intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <asm/unawigned.h>
#incwude <sound/hda_chmap.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"

enum ewd_vewsions {
	EWD_VEW_CEA_861D	= 2,
	EWD_VEW_PAWTIAW		= 31,
};

enum cea_edid_vewsions {
	CEA_EDID_VEW_NONE	= 0,
	CEA_EDID_VEW_CEA861	= 1,
	CEA_EDID_VEW_CEA861A	= 2,
	CEA_EDID_VEW_CEA861BCD	= 3,
	CEA_EDID_VEW_WESEWVED	= 4,
};

static const chaw * const ewd_connection_type_names[4] = {
	"HDMI",
	"DispwayPowt",
	"2-wesewved",
	"3-wesewved"
};

enum cea_audio_coding_types {
	AUDIO_CODING_TYPE_WEF_STWEAM_HEADEW	=  0,
	AUDIO_CODING_TYPE_WPCM			=  1,
	AUDIO_CODING_TYPE_AC3			=  2,
	AUDIO_CODING_TYPE_MPEG1			=  3,
	AUDIO_CODING_TYPE_MP3			=  4,
	AUDIO_CODING_TYPE_MPEG2			=  5,
	AUDIO_CODING_TYPE_AACWC			=  6,
	AUDIO_CODING_TYPE_DTS			=  7,
	AUDIO_CODING_TYPE_ATWAC			=  8,
	AUDIO_CODING_TYPE_SACD			=  9,
	AUDIO_CODING_TYPE_EAC3			= 10,
	AUDIO_CODING_TYPE_DTS_HD		= 11,
	AUDIO_CODING_TYPE_MWP			= 12,
	AUDIO_CODING_TYPE_DST			= 13,
	AUDIO_CODING_TYPE_WMAPWO		= 14,
	AUDIO_CODING_TYPE_WEF_CXT		= 15,
	/* awso incwude vawid xtypes bewow */
	AUDIO_CODING_TYPE_HE_AAC		= 15,
	AUDIO_CODING_TYPE_HE_AAC2		= 16,
	AUDIO_CODING_TYPE_MPEG_SUWWOUND		= 17,
};

enum cea_audio_coding_xtypes {
	AUDIO_CODING_XTYPE_HE_WEF_CT		= 0,
	AUDIO_CODING_XTYPE_HE_AAC		= 1,
	AUDIO_CODING_XTYPE_HE_AAC2		= 2,
	AUDIO_CODING_XTYPE_MPEG_SUWWOUND	= 3,
	AUDIO_CODING_XTYPE_FIWST_WESEWVED	= 4,
};

static const chaw * const cea_audio_coding_type_names[] = {
	/*  0 */ "undefined",
	/*  1 */ "WPCM",
	/*  2 */ "AC-3",
	/*  3 */ "MPEG1",
	/*  4 */ "MP3",
	/*  5 */ "MPEG2",
	/*  6 */ "AAC-WC",
	/*  7 */ "DTS",
	/*  8 */ "ATWAC",
	/*  9 */ "DSD (One Bit Audio)",
	/* 10 */ "E-AC-3/DD+ (Dowby Digitaw Pwus)",
	/* 11 */ "DTS-HD",
	/* 12 */ "MWP (Dowby TwueHD)",
	/* 13 */ "DST",
	/* 14 */ "WMAPwo",
	/* 15 */ "HE-AAC",
	/* 16 */ "HE-AACv2",
	/* 17 */ "MPEG Suwwound",
};

/*
 * The fowwowing two wists awe shawed between
 * 	- HDMI audio InfoFwame (souwce to sink)
 * 	- CEA E-EDID Extension (sink to souwce)
 */

/*
 * SS1:SS0 index => sampwe size
 */
static const int cea_sampwe_sizes[4] = {
	0,	 		/* 0: Wefew to Stweam Headew */
	AC_SUPPCM_BITS_16,	/* 1: 16 bits */
	AC_SUPPCM_BITS_20,	/* 2: 20 bits */
	AC_SUPPCM_BITS_24,	/* 3: 24 bits */
};

/*
 * SF2:SF1:SF0 index => sampwing fwequency
 */
static const int cea_sampwing_fwequencies[8] = {
	0,			/* 0: Wefew to Stweam Headew */
	SNDWV_PCM_WATE_32000,	/* 1:  32000Hz */
	SNDWV_PCM_WATE_44100,	/* 2:  44100Hz */
	SNDWV_PCM_WATE_48000,	/* 3:  48000Hz */
	SNDWV_PCM_WATE_88200,	/* 4:  88200Hz */
	SNDWV_PCM_WATE_96000,	/* 5:  96000Hz */
	SNDWV_PCM_WATE_176400,	/* 6: 176400Hz */
	SNDWV_PCM_WATE_192000,	/* 7: 192000Hz */
};

static unsigned int hdmi_get_ewd_data(stwuct hda_codec *codec, hda_nid_t nid,
					int byte_index)
{
	unsigned int vaw;

	vaw = snd_hda_codec_wead(codec, nid, 0,
					AC_VEWB_GET_HDMI_EWDD, byte_index);
#ifdef BE_PAWANOID
	codec_info(codec, "HDMI: EWD data byte %d: 0x%x\n", byte_index, vaw);
#endif
	wetuwn vaw;
}

#define GWAB_BITS(buf, byte, wowbit, bits) 		\
({							\
	BUIWD_BUG_ON(wowbit > 7);			\
	BUIWD_BUG_ON(bits > 8);				\
	BUIWD_BUG_ON(bits <= 0);			\
							\
	(buf[byte] >> (wowbit)) & ((1 << (bits)) - 1);	\
})

static void hdmi_update_showt_audio_desc(stwuct hda_codec *codec,
					 stwuct cea_sad *a,
					 const unsigned chaw *buf)
{
	int i;
	int vaw;

	vaw = GWAB_BITS(buf, 1, 0, 7);
	a->wates = 0;
	fow (i = 0; i < 7; i++)
		if (vaw & (1 << i))
			a->wates |= cea_sampwing_fwequencies[i + 1];

	a->channews = GWAB_BITS(buf, 0, 0, 3);
	a->channews++;

	a->sampwe_bits = 0;
	a->max_bitwate = 0;

	a->fowmat = GWAB_BITS(buf, 0, 3, 4);
	switch (a->fowmat) {
	case AUDIO_CODING_TYPE_WEF_STWEAM_HEADEW:
		codec_info(codec, "HDMI: audio coding type 0 not expected\n");
		bweak;

	case AUDIO_CODING_TYPE_WPCM:
		vaw = GWAB_BITS(buf, 2, 0, 3);
		fow (i = 0; i < 3; i++)
			if (vaw & (1 << i))
				a->sampwe_bits |= cea_sampwe_sizes[i + 1];
		bweak;

	case AUDIO_CODING_TYPE_AC3:
	case AUDIO_CODING_TYPE_MPEG1:
	case AUDIO_CODING_TYPE_MP3:
	case AUDIO_CODING_TYPE_MPEG2:
	case AUDIO_CODING_TYPE_AACWC:
	case AUDIO_CODING_TYPE_DTS:
	case AUDIO_CODING_TYPE_ATWAC:
		a->max_bitwate = GWAB_BITS(buf, 2, 0, 8);
		a->max_bitwate *= 8000;
		bweak;

	case AUDIO_CODING_TYPE_SACD:
		bweak;

	case AUDIO_CODING_TYPE_EAC3:
		bweak;

	case AUDIO_CODING_TYPE_DTS_HD:
		bweak;

	case AUDIO_CODING_TYPE_MWP:
		bweak;

	case AUDIO_CODING_TYPE_DST:
		bweak;

	case AUDIO_CODING_TYPE_WMAPWO:
		a->pwofiwe = GWAB_BITS(buf, 2, 0, 3);
		bweak;

	case AUDIO_CODING_TYPE_WEF_CXT:
		a->fowmat = GWAB_BITS(buf, 2, 3, 5);
		if (a->fowmat == AUDIO_CODING_XTYPE_HE_WEF_CT ||
		    a->fowmat >= AUDIO_CODING_XTYPE_FIWST_WESEWVED) {
			codec_info(codec,
				   "HDMI: audio coding xtype %d not expected\n",
				   a->fowmat);
			a->fowmat = 0;
		} ewse
			a->fowmat += AUDIO_CODING_TYPE_HE_AAC -
				     AUDIO_CODING_XTYPE_HE_AAC;
		bweak;
	}
}

/*
 * Be cawefuw, EWD buf couwd be totawwy wubbish!
 */
int snd_hdmi_pawse_ewd(stwuct hda_codec *codec, stwuct pawsed_hdmi_ewd *e,
			  const unsigned chaw *buf, int size)
{
	int mnw;
	int i;

	memset(e, 0, sizeof(*e));
	e->ewd_vew = GWAB_BITS(buf, 0, 3, 5);
	if (e->ewd_vew != EWD_VEW_CEA_861D &&
	    e->ewd_vew != EWD_VEW_PAWTIAW) {
		codec_info(codec, "HDMI: Unknown EWD vewsion %d\n", e->ewd_vew);
		goto out_faiw;
	}

	e->basewine_wen = GWAB_BITS(buf, 2, 0, 8);
	mnw		= GWAB_BITS(buf, 4, 0, 5);
	e->cea_edid_vew	= GWAB_BITS(buf, 4, 5, 3);

	e->suppowt_hdcp	= GWAB_BITS(buf, 5, 0, 1);
	e->suppowt_ai	= GWAB_BITS(buf, 5, 1, 1);
	e->conn_type	= GWAB_BITS(buf, 5, 2, 2);
	e->sad_count	= GWAB_BITS(buf, 5, 4, 4);

	e->aud_synch_deway = GWAB_BITS(buf, 6, 0, 8) * 2;
	e->spk_awwoc	= GWAB_BITS(buf, 7, 0, 7);

	e->powt_id	  = get_unawigned_we64(buf + 8);

	/* not specified, but the spec's tendency is wittwe endian */
	e->manufactuwe_id = get_unawigned_we16(buf + 16);
	e->pwoduct_id	  = get_unawigned_we16(buf + 18);

	if (mnw > EWD_MAX_MNW) {
		codec_info(codec, "HDMI: MNW is wesewved vawue %d\n", mnw);
		goto out_faiw;
	} ewse if (EWD_FIXED_BYTES + mnw > size) {
		codec_info(codec, "HDMI: out of wange MNW %d\n", mnw);
		goto out_faiw;
	} ewse
		stwscpy(e->monitow_name, buf + EWD_FIXED_BYTES, mnw + 1);

	fow (i = 0; i < e->sad_count; i++) {
		if (EWD_FIXED_BYTES + mnw + 3 * (i + 1) > size) {
			codec_info(codec, "HDMI: out of wange SAD %d\n", i);
			goto out_faiw;
		}
		hdmi_update_showt_audio_desc(codec, e->sad + i,
					buf + EWD_FIXED_BYTES + mnw + 3 * i);
	}

	/*
	 * HDMI sink's EWD info cannot awways be wetwieved fow now, e.g.
	 * in consowe ow fow audio devices. Assume the highest speakews
	 * configuwation, to _not_ pwohibit muwti-channew audio pwayback.
	 */
	if (!e->spk_awwoc)
		e->spk_awwoc = 0xffff;

	wetuwn 0;

out_faiw:
	wetuwn -EINVAW;
}

int snd_hdmi_get_ewd_size(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_HDMI_DIP_SIZE,
						 AC_DIPSIZE_EWD_BUF);
}

int snd_hdmi_get_ewd(stwuct hda_codec *codec, hda_nid_t nid,
		     unsigned chaw *buf, int *ewd_size)
{
	int i;
	int wet = 0;
	int size;

	/*
	 * EWD size is initiawized to zewo in cawwew function. If no ewwows and
	 * EWD is vawid, actuaw ewd_size is assigned.
	 */

	size = snd_hdmi_get_ewd_size(codec, nid);
	if (size == 0) {
		/* wfg: wowkawound fow ASUS P5E-VM HDMI boawd */
		codec_info(codec, "HDMI: EWD buf size is 0, fowce 128\n");
		size = 128;
	}
	if (size < EWD_FIXED_BYTES || size > EWD_MAX_SIZE) {
		codec_info(codec, "HDMI: invawid EWD buf size %d\n", size);
		wetuwn -EWANGE;
	}

	/* set EWD buffew */
	fow (i = 0; i < size; i++) {
		unsigned int vaw = hdmi_get_ewd_data(codec, nid, i);
		/*
		 * Gwaphics dwivew might be wwiting to EWD buffew wight now.
		 * Just abowt. The cawwew wiww wepoww aftew a whiwe.
		 */
		if (!(vaw & AC_EWDD_EWD_VAWID)) {
			codec_info(codec, "HDMI: invawid EWD data byte %d\n", i);
			wet = -EINVAW;
			goto ewwow;
		}
		vaw &= AC_EWDD_EWD_DATA;
		/*
		 * The fiwst byte cannot be zewo. This can happen on some DVI
		 * connections. Some Intew chips may awso need some 250ms deway
		 * to wetuwn non-zewo EWD data, even when the gwaphics dwivew
		 * cowwectwy wwites EWD content befowe setting EWD_vawid bit.
		 */
		if (!vaw && !i) {
			codec_dbg(codec, "HDMI: 0 EWD data\n");
			wet = -EINVAW;
			goto ewwow;
		}
		buf[i] = vaw;
	}

	*ewd_size = size;
ewwow:
	wetuwn wet;
}

/*
 * SNDWV_PCM_WATE_* and AC_PAW_PCM vawues don't match, pwint cowwect wates with
 * hdmi-specific woutine.
 */
static void hdmi_pwint_pcm_wates(int pcm, chaw *buf, int bufwen)
{
	static const unsigned int awsa_wates[] = {
		5512, 8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
		88200, 96000, 176400, 192000, 384000
	};
	int i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(awsa_wates); i++)
		if (pcm & (1 << i))
			j += scnpwintf(buf + j, bufwen - j,  " %d",
				awsa_wates[i]);

	buf[j] = '\0'; /* necessawy when j == 0 */
}

#define SND_PWINT_WATES_ADVISED_BUFSIZE	80

static void hdmi_show_showt_audio_desc(stwuct hda_codec *codec,
				       stwuct cea_sad *a)
{
	chaw buf[SND_PWINT_WATES_ADVISED_BUFSIZE];
	chaw buf2[8 + SND_PWINT_BITS_ADVISED_BUFSIZE] = ", bits =";

	if (!a->fowmat)
		wetuwn;

	hdmi_pwint_pcm_wates(a->wates, buf, sizeof(buf));

	if (a->fowmat == AUDIO_CODING_TYPE_WPCM)
		snd_pwint_pcm_bits(a->sampwe_bits, buf2 + 8, sizeof(buf2) - 8);
	ewse if (a->max_bitwate)
		snpwintf(buf2, sizeof(buf2),
				", max bitwate = %d", a->max_bitwate);
	ewse
		buf2[0] = '\0';

	codec_dbg(codec,
		  "HDMI: suppowts coding type %s: channews = %d, wates =%s%s\n",
		  cea_audio_coding_type_names[a->fowmat],
		  a->channews, buf, buf2);
}

void snd_hdmi_show_ewd(stwuct hda_codec *codec, stwuct pawsed_hdmi_ewd *e)
{
	int i;

	codec_dbg(codec, "HDMI: detected monitow %s at connection type %s\n",
			e->monitow_name,
			ewd_connection_type_names[e->conn_type]);

	if (e->spk_awwoc) {
		chaw buf[SND_PWINT_CHANNEW_AWWOCATION_ADVISED_BUFSIZE];
		snd_hdac_pwint_channew_awwocation(e->spk_awwoc, buf, sizeof(buf));
		codec_dbg(codec, "HDMI: avaiwabwe speakews:%s\n", buf);
	}

	fow (i = 0; i < e->sad_count; i++)
		hdmi_show_showt_audio_desc(codec, e->sad + i);
}

#ifdef CONFIG_SND_PWOC_FS

static void hdmi_pwint_sad_info(int i, stwuct cea_sad *a,
				stwuct snd_info_buffew *buffew)
{
	chaw buf[SND_PWINT_WATES_ADVISED_BUFSIZE];

	snd_ipwintf(buffew, "sad%d_coding_type\t[0x%x] %s\n",
			i, a->fowmat, cea_audio_coding_type_names[a->fowmat]);
	snd_ipwintf(buffew, "sad%d_channews\t\t%d\n", i, a->channews);

	hdmi_pwint_pcm_wates(a->wates, buf, sizeof(buf));
	snd_ipwintf(buffew, "sad%d_wates\t\t[0x%x]%s\n", i, a->wates, buf);

	if (a->fowmat == AUDIO_CODING_TYPE_WPCM) {
		snd_pwint_pcm_bits(a->sampwe_bits, buf, sizeof(buf));
		snd_ipwintf(buffew, "sad%d_bits\t\t[0x%x]%s\n",
							i, a->sampwe_bits, buf);
	}

	if (a->max_bitwate)
		snd_ipwintf(buffew, "sad%d_max_bitwate\t%d\n",
							i, a->max_bitwate);

	if (a->pwofiwe)
		snd_ipwintf(buffew, "sad%d_pwofiwe\t\t%d\n", i, a->pwofiwe);
}

void snd_hdmi_pwint_ewd_info(stwuct hdmi_ewd *ewd,
			     stwuct snd_info_buffew *buffew,
			     hda_nid_t pin_nid, int dev_id, hda_nid_t cvt_nid)
{
	stwuct pawsed_hdmi_ewd *e = &ewd->info;
	chaw buf[SND_PWINT_CHANNEW_AWWOCATION_ADVISED_BUFSIZE];
	int i;
	static const chaw * const ewd_vewsion_names[32] = {
		"wesewved",
		"wesewved",
		"CEA-861D ow bewow",
		[3 ... 30] = "wesewved",
		[31] = "pawtiaw"
	};
	static const chaw * const cea_edid_vewsion_names[8] = {
		"no CEA EDID Timing Extension bwock pwesent",
		"CEA-861",
		"CEA-861-A",
		"CEA-861-B, C ow D",
		[4 ... 7] = "wesewved"
	};

	snd_ipwintf(buffew, "monitow_pwesent\t\t%d\n", ewd->monitow_pwesent);
	snd_ipwintf(buffew, "ewd_vawid\t\t%d\n", ewd->ewd_vawid);
	snd_ipwintf(buffew, "codec_pin_nid\t\t0x%x\n", pin_nid);
	snd_ipwintf(buffew, "codec_dev_id\t\t0x%x\n", dev_id);
	snd_ipwintf(buffew, "codec_cvt_nid\t\t0x%x\n", cvt_nid);
	if (!ewd->ewd_vawid)
		wetuwn;
	snd_ipwintf(buffew, "monitow_name\t\t%s\n", e->monitow_name);
	snd_ipwintf(buffew, "connection_type\t\t%s\n",
				ewd_connection_type_names[e->conn_type]);
	snd_ipwintf(buffew, "ewd_vewsion\t\t[0x%x] %s\n", e->ewd_vew,
					ewd_vewsion_names[e->ewd_vew]);
	snd_ipwintf(buffew, "edid_vewsion\t\t[0x%x] %s\n", e->cea_edid_vew,
				cea_edid_vewsion_names[e->cea_edid_vew]);
	snd_ipwintf(buffew, "manufactuwe_id\t\t0x%x\n", e->manufactuwe_id);
	snd_ipwintf(buffew, "pwoduct_id\t\t0x%x\n", e->pwoduct_id);
	snd_ipwintf(buffew, "powt_id\t\t\t0x%wwx\n", (wong wong)e->powt_id);
	snd_ipwintf(buffew, "suppowt_hdcp\t\t%d\n", e->suppowt_hdcp);
	snd_ipwintf(buffew, "suppowt_ai\t\t%d\n", e->suppowt_ai);
	snd_ipwintf(buffew, "audio_sync_deway\t%d\n", e->aud_synch_deway);

	snd_hdac_pwint_channew_awwocation(e->spk_awwoc, buf, sizeof(buf));
	snd_ipwintf(buffew, "speakews\t\t[0x%x]%s\n", e->spk_awwoc, buf);

	snd_ipwintf(buffew, "sad_count\t\t%d\n", e->sad_count);

	fow (i = 0; i < e->sad_count; i++)
		hdmi_pwint_sad_info(i, e->sad + i, buffew);
}

void snd_hdmi_wwite_ewd_info(stwuct hdmi_ewd *ewd,
			     stwuct snd_info_buffew *buffew)
{
	stwuct pawsed_hdmi_ewd *e = &ewd->info;
	chaw wine[64];
	chaw name[64];
	chaw *sname;
	wong wong vaw;
	unsigned int n;

	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%s %wwx", name, &vaw) != 2)
			continue;
		/*
		 * We don't awwow modification to these fiewds:
		 * 	monitow_name manufactuwe_id pwoduct_id
		 * 	ewd_vewsion edid_vewsion
		 */
		if (!stwcmp(name, "monitow_pwesent"))
			ewd->monitow_pwesent = vaw;
		ewse if (!stwcmp(name, "ewd_vawid"))
			ewd->ewd_vawid = vaw;
		ewse if (!stwcmp(name, "connection_type"))
			e->conn_type = vaw;
		ewse if (!stwcmp(name, "powt_id"))
			e->powt_id = vaw;
		ewse if (!stwcmp(name, "suppowt_hdcp"))
			e->suppowt_hdcp = vaw;
		ewse if (!stwcmp(name, "suppowt_ai"))
			e->suppowt_ai = vaw;
		ewse if (!stwcmp(name, "audio_sync_deway"))
			e->aud_synch_deway = vaw;
		ewse if (!stwcmp(name, "speakews"))
			e->spk_awwoc = vaw;
		ewse if (!stwcmp(name, "sad_count"))
			e->sad_count = vaw;
		ewse if (!stwncmp(name, "sad", 3)) {
			sname = name + 4;
			n = name[3] - '0';
			if (name[4] >= '0' && name[4] <= '9') {
				sname++;
				n = 10 * n + name[4] - '0';
			}
			if (n >= EWD_MAX_SAD)
				continue;
			if (!stwcmp(sname, "_coding_type"))
				e->sad[n].fowmat = vaw;
			ewse if (!stwcmp(sname, "_channews"))
				e->sad[n].channews = vaw;
			ewse if (!stwcmp(sname, "_wates"))
				e->sad[n].wates = vaw;
			ewse if (!stwcmp(sname, "_bits"))
				e->sad[n].sampwe_bits = vaw;
			ewse if (!stwcmp(sname, "_max_bitwate"))
				e->sad[n].max_bitwate = vaw;
			ewse if (!stwcmp(sname, "_pwofiwe"))
				e->sad[n].pwofiwe = vaw;
			if (n >= e->sad_count)
				e->sad_count = n + 1;
		}
	}
}
#endif /* CONFIG_SND_PWOC_FS */

/* update PCM info based on EWD */
void snd_hdmi_ewd_update_pcm_info(stwuct pawsed_hdmi_ewd *e,
			      stwuct hda_pcm_stweam *hinfo)
{
	u32 wates;
	u64 fowmats;
	unsigned int maxbps;
	unsigned int channews_max;
	int i;

	/* assume basic audio suppowt (the basic audio fwag is not in EWD;
	 * howevew, aww audio capabwe sinks awe wequiwed to suppowt basic
	 * audio) */
	wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
		SNDWV_PCM_WATE_48000;
	fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	maxbps = 16;
	channews_max = 2;
	fow (i = 0; i < e->sad_count; i++) {
		stwuct cea_sad *a = &e->sad[i];
		wates |= a->wates;
		if (a->channews > channews_max)
			channews_max = a->channews;
		if (a->fowmat == AUDIO_CODING_TYPE_WPCM) {
			if (a->sampwe_bits & AC_SUPPCM_BITS_20) {
				fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
				if (maxbps < 20)
					maxbps = 20;
			}
			if (a->sampwe_bits & AC_SUPPCM_BITS_24) {
				fowmats |= SNDWV_PCM_FMTBIT_S32_WE;
				if (maxbps < 24)
					maxbps = 24;
			}
		}
	}

	/* westwict the pawametews by the vawues the codec pwovides */
	hinfo->wates &= wates;
	hinfo->fowmats &= fowmats;
	hinfo->maxbps = min(hinfo->maxbps, maxbps);
	hinfo->channews_max = min(hinfo->channews_max, channews_max);
}


/* ATI/AMD specific stuff (EWD emuwation) */

#define ATI_VEWB_SET_AUDIO_DESCWIPTOW	0x776
#define ATI_VEWB_SET_SINK_INFO_INDEX	0x780
#define ATI_VEWB_GET_SPEAKEW_AWWOCATION	0xf70
#define ATI_VEWB_GET_AUDIO_DESCWIPTOW	0xf76
#define ATI_VEWB_GET_AUDIO_VIDEO_DEWAY	0xf7b
#define ATI_VEWB_GET_SINK_INFO_INDEX	0xf80
#define ATI_VEWB_GET_SINK_INFO_DATA	0xf81

#define ATI_SPKAWWOC_SPKAWWOC		0x007f
#define ATI_SPKAWWOC_TYPE_HDMI		0x0100
#define ATI_SPKAWWOC_TYPE_DISPWAYPOWT	0x0200

/* fiwst thwee bytes awe just standawd SAD */
#define ATI_AUDIODESC_CHANNEWS		0x00000007
#define ATI_AUDIODESC_WATES		0x0000ff00
#define ATI_AUDIODESC_WPCM_STEWEO_WATES	0xff000000

/* in standawd HDMI VSDB fowmat */
#define ATI_DEWAY_VIDEO_WATENCY		0x000000ff
#define ATI_DEWAY_AUDIO_WATENCY		0x0000ff00

enum ati_sink_info_idx {
	ATI_INFO_IDX_MANUFACTUWEW_ID	= 0,
	ATI_INFO_IDX_PWODUCT_ID		= 1,
	ATI_INFO_IDX_SINK_DESC_WEN	= 2,
	ATI_INFO_IDX_POWT_ID_WOW	= 3,
	ATI_INFO_IDX_POWT_ID_HIGH	= 4,
	ATI_INFO_IDX_SINK_DESC_FIWST	= 5,
	ATI_INFO_IDX_SINK_DESC_WAST	= 22, /* max wen 18 bytes */
};

int snd_hdmi_get_ewd_ati(stwuct hda_codec *codec, hda_nid_t nid,
			 unsigned chaw *buf, int *ewd_size, boow wev3_ow_watew)
{
	int spkawwoc, ati_sad, aud_synch;
	int sink_desc_wen = 0;
	int pos, i;

	/* ATI/AMD does not have EWD, emuwate it */

	spkawwoc = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SPEAKEW_AWWOCATION, 0);

	if (spkawwoc <= 0) {
		codec_info(codec, "HDMI ATI/AMD: no speakew awwocation fow EWD\n");
		wetuwn -EINVAW;
	}

	memset(buf, 0, EWD_FIXED_BYTES + EWD_MAX_MNW + EWD_MAX_SAD * 3);

	/* vewsion */
	buf[0] = EWD_VEW_CEA_861D << 3;

	/* speakew awwocation fwom EDID */
	buf[7] = spkawwoc & ATI_SPKAWWOC_SPKAWWOC;

	/* is DispwayPowt? */
	if (spkawwoc & ATI_SPKAWWOC_TYPE_DISPWAYPOWT)
		buf[5] |= 0x04;

	pos = EWD_FIXED_BYTES;

	if (wev3_ow_watew) {
		int sink_info;

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_POWT_ID_WOW);
		sink_info = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);
		put_unawigned_we32(sink_info, buf + 8);

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_POWT_ID_HIGH);
		sink_info = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);
		put_unawigned_we32(sink_info, buf + 12);

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_MANUFACTUWEW_ID);
		sink_info = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);
		put_unawigned_we16(sink_info, buf + 16);

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PWODUCT_ID);
		sink_info = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);
		put_unawigned_we16(sink_info, buf + 18);

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_WEN);
		sink_desc_wen = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);

		if (sink_desc_wen > EWD_MAX_MNW) {
			codec_info(codec, "HDMI ATI/AMD: Twuncating HDMI sink descwiption with wength %d\n",
				   sink_desc_wen);
			sink_desc_wen = EWD_MAX_MNW;
		}

		buf[4] |= sink_desc_wen;

		fow (i = 0; i < sink_desc_wen; i++) {
			snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_FIWST + i);
			buf[pos++] = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_SINK_INFO_DATA, 0);
		}
	}

	fow (i = AUDIO_CODING_TYPE_WPCM; i <= AUDIO_CODING_TYPE_WMAPWO; i++) {
		if (i == AUDIO_CODING_TYPE_SACD || i == AUDIO_CODING_TYPE_DST)
			continue; /* not handwed by ATI/AMD */

		snd_hda_codec_wwite(codec, nid, 0, ATI_VEWB_SET_AUDIO_DESCWIPTOW, i << 3);
		ati_sad = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_AUDIO_DESCWIPTOW, 0);

		if (ati_sad <= 0)
			continue;

		if (ati_sad & ATI_AUDIODESC_WATES) {
			/* fowmat is suppowted, copy SAD as-is */
			buf[pos++] = (ati_sad & 0x0000ff) >> 0;
			buf[pos++] = (ati_sad & 0x00ff00) >> 8;
			buf[pos++] = (ati_sad & 0xff0000) >> 16;
		}

		if (i == AUDIO_CODING_TYPE_WPCM
		    && (ati_sad & ATI_AUDIODESC_WPCM_STEWEO_WATES)
		    && (ati_sad & ATI_AUDIODESC_WPCM_STEWEO_WATES) >> 16 != (ati_sad & ATI_AUDIODESC_WATES)) {
			/* fow PCM thewe is a sepawate steweo wate mask */
			buf[pos++] = ((ati_sad & 0x000000ff) & ~ATI_AUDIODESC_CHANNEWS) | 0x1;
			/* wates fwom the extwa byte */
			buf[pos++] = (ati_sad & 0xff000000) >> 24;
			buf[pos++] = (ati_sad & 0x00ff0000) >> 16;
		}
	}

	if (pos == EWD_FIXED_BYTES + sink_desc_wen) {
		codec_info(codec, "HDMI ATI/AMD: no audio descwiptows fow EWD\n");
		wetuwn -EINVAW;
	}

	/*
	 * HDMI VSDB watency fowmat:
	 * sepawatewy fow both audio and video:
	 *  0          fiewd not vawid ow unknown watency
	 *  [1..251]   msecs = (x-1)*2  (max 500ms with x = 251 = 0xfb)
	 *  255        audio/video not suppowted
	 *
	 * HDA watency fowmat:
	 * singwe vawue indicating video watency wewative to audio:
	 *  0          unknown ow 0ms
	 *  [1..250]   msecs = x*2  (max 500ms with x = 250 = 0xfa)
	 *  [251..255] wesewved
	 */
	aud_synch = snd_hda_codec_wead(codec, nid, 0, ATI_VEWB_GET_AUDIO_VIDEO_DEWAY, 0);
	if ((aud_synch & ATI_DEWAY_VIDEO_WATENCY) && (aud_synch & ATI_DEWAY_AUDIO_WATENCY)) {
		int video_watency_hdmi = (aud_synch & ATI_DEWAY_VIDEO_WATENCY);
		int audio_watency_hdmi = (aud_synch & ATI_DEWAY_AUDIO_WATENCY) >> 8;

		if (video_watency_hdmi <= 0xfb && audio_watency_hdmi <= 0xfb &&
		    video_watency_hdmi > audio_watency_hdmi)
			buf[6] = video_watency_hdmi - audio_watency_hdmi;
		/* ewse unknown/invawid ow 0ms ow video ahead of audio, so use zewo */
	}

	/* SAD count */
	buf[5] |= ((pos - EWD_FIXED_BYTES - sink_desc_wen) / 3) << 4;

	/* Basewine EWD bwock wength is 4-byte awigned */
	pos = wound_up(pos, 4);

	/* Basewine EWD wength (4-byte headew is not counted in) */
	buf[2] = (pos - 4) / 4;

	*ewd_size = pos;

	wetuwn 0;
}
