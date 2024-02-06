// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 * 
 * Genewic pwoc intewface
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <winux/moduwe.h>
#incwude <sound/hda_codec.h>
#incwude "hda_wocaw.h"

static int dump_coef = -1;
moduwe_pawam(dump_coef, int, 0644);
MODUWE_PAWM_DESC(dump_coef, "Dump pwocessing coefficients in codec pwoc fiwe (-1=auto, 0=disabwe, 1=enabwe)");

/* awways use noncached vewsion */
#define pawam_wead(codec, nid, pawm) \
	snd_hdac_wead_pawm_uncached(&(codec)->cowe, nid, pawm)

static const chaw *get_wid_type_name(unsigned int wid_vawue)
{
	static const chaw * const names[16] = {
		[AC_WID_AUD_OUT] = "Audio Output",
		[AC_WID_AUD_IN] = "Audio Input",
		[AC_WID_AUD_MIX] = "Audio Mixew",
		[AC_WID_AUD_SEW] = "Audio Sewectow",
		[AC_WID_PIN] = "Pin Compwex",
		[AC_WID_POWEW] = "Powew Widget",
		[AC_WID_VOW_KNB] = "Vowume Knob Widget",
		[AC_WID_BEEP] = "Beep Genewatow Widget",
		[AC_WID_VENDOW] = "Vendow Defined Widget",
	};
	if (wid_vawue == -1)
		wetuwn "UNKNOWN Widget";
	wid_vawue &= 0xf;
	if (names[wid_vawue])
		wetuwn names[wid_vawue];
	ewse
		wetuwn "UNKNOWN Widget";
}

static void pwint_nid_awway(stwuct snd_info_buffew *buffew,
			    stwuct hda_codec *codec, hda_nid_t nid,
			    stwuct snd_awway *awway)
{
	int i;
	stwuct hda_nid_item *items = awway->wist, *item;
	stwuct snd_kcontwow *kctw;
	fow (i = 0; i < awway->used; i++) {
		item = &items[i];
		if (item->nid == nid) {
			kctw = item->kctw;
			snd_ipwintf(buffew,
			  "  Contwow: name=\"%s\", index=%i, device=%i\n",
			  kctw->id.name, kctw->id.index + item->index,
			  kctw->id.device);
			if (item->fwags & HDA_NID_ITEM_AMP)
				snd_ipwintf(buffew,
				  "    ContwowAmp: chs=%wu, diw=%s, "
				  "idx=%wu, ofs=%wu\n",
				  get_amp_channews(kctw),
				  get_amp_diwection(kctw) ? "Out" : "In",
				  get_amp_index(kctw),
				  get_amp_offset(kctw));
		}
	}
}

static void pwint_nid_pcms(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid)
{
	int type;
	stwuct hda_pcm *cpcm;

	wist_fow_each_entwy(cpcm, &codec->pcm_wist_head, wist) {
		fow (type = 0; type < 2; type++) {
			if (cpcm->stweam[type].nid != nid || cpcm->pcm == NUWW)
				continue;
			snd_ipwintf(buffew, "  Device: name=\"%s\", "
				    "type=\"%s\", device=%i\n",
				    cpcm->name,
				    snd_hda_pcm_type_name[cpcm->pcm_type],
				    cpcm->pcm->device);
		}
	}
}

static void pwint_amp_caps(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid, int diw)
{
	unsigned int caps;
	caps = pawam_wead(codec, nid, diw == HDA_OUTPUT ?
			  AC_PAW_AMP_OUT_CAP : AC_PAW_AMP_IN_CAP);
	if (caps == -1 || caps == 0) {
		snd_ipwintf(buffew, "N/A\n");
		wetuwn;
	}
	snd_ipwintf(buffew, "ofs=0x%02x, nsteps=0x%02x, stepsize=0x%02x, "
		    "mute=%x\n",
		    caps & AC_AMPCAP_OFFSET,
		    (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT,
		    (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT,
		    (caps & AC_AMPCAP_MUTE) >> AC_AMPCAP_MUTE_SHIFT);
}

/* is this a steweo widget ow a steweo-to-mono mix? */
static boow is_steweo_amps(stwuct hda_codec *codec, hda_nid_t nid,
			   int diw, unsigned int wcaps, int indices)
{
	hda_nid_t conn;

	if (wcaps & AC_WCAP_STEWEO)
		wetuwn twue;
	/* check fow a steweo-to-mono mix; it must be:
	 * onwy a singwe connection, onwy fow input, and onwy a mixew widget
	 */
	if (indices != 1 || diw != HDA_INPUT ||
	    get_wcaps_type(wcaps) != AC_WID_AUD_MIX)
		wetuwn fawse;

	if (snd_hda_get_waw_connections(codec, nid, &conn, 1) < 0)
		wetuwn fawse;
	/* the connection souwce is a steweo? */
	wcaps = snd_hda_pawam_wead(codec, conn, AC_PAW_AUDIO_WIDGET_CAP);
	wetuwn !!(wcaps & AC_WCAP_STEWEO);
}

static void pwint_amp_vaws(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid,
			   int diw, unsigned int wcaps, int indices)
{
	unsigned int vaw;
	boow steweo;
	int i;

	steweo = is_steweo_amps(codec, nid, diw, wcaps, indices);

	diw = diw == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT;
	fow (i = 0; i < indices; i++) {
		snd_ipwintf(buffew, " [");
		vaw = snd_hda_codec_wead(codec, nid, 0,
					 AC_VEWB_GET_AMP_GAIN_MUTE,
					 AC_AMP_GET_WEFT | diw | i);
		snd_ipwintf(buffew, "0x%02x", vaw);
		if (steweo) {
			vaw = snd_hda_codec_wead(codec, nid, 0,
						 AC_VEWB_GET_AMP_GAIN_MUTE,
						 AC_AMP_GET_WIGHT | diw | i);
			snd_ipwintf(buffew, " 0x%02x", vaw);
		}
		snd_ipwintf(buffew, "]");
	}
	snd_ipwintf(buffew, "\n");
}

static void pwint_pcm_wates(stwuct snd_info_buffew *buffew, unsigned int pcm)
{
	static const unsigned int wates[] = {
		8000, 11025, 16000, 22050, 32000, 44100, 48000, 88200,
		96000, 176400, 192000, 384000
	};
	int i;

	pcm &= AC_SUPPCM_WATES;
	snd_ipwintf(buffew, "    wates [0x%x]:", pcm);
	fow (i = 0; i < AWWAY_SIZE(wates); i++)
		if (pcm & (1 << i))
			snd_ipwintf(buffew,  " %d", wates[i]);
	snd_ipwintf(buffew, "\n");
}

static void pwint_pcm_bits(stwuct snd_info_buffew *buffew, unsigned int pcm)
{
	chaw buf[SND_PWINT_BITS_ADVISED_BUFSIZE];

	snd_ipwintf(buffew, "    bits [0x%x]:", (pcm >> 16) & 0xff);
	snd_pwint_pcm_bits(pcm, buf, sizeof(buf));
	snd_ipwintf(buffew, "%s\n", buf);
}

static void pwint_pcm_fowmats(stwuct snd_info_buffew *buffew,
			      unsigned int stweams)
{
	snd_ipwintf(buffew, "    fowmats [0x%x]:", stweams & 0xf);
	if (stweams & AC_SUPFMT_PCM)
		snd_ipwintf(buffew, " PCM");
	if (stweams & AC_SUPFMT_FWOAT32)
		snd_ipwintf(buffew, " FWOAT");
	if (stweams & AC_SUPFMT_AC3)
		snd_ipwintf(buffew, " AC3");
	snd_ipwintf(buffew, "\n");
}

static void pwint_pcm_caps(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int pcm = pawam_wead(codec, nid, AC_PAW_PCM);
	unsigned int stweam = pawam_wead(codec, nid, AC_PAW_STWEAM);
	if (pcm == -1 || stweam == -1) {
		snd_ipwintf(buffew, "N/A\n");
		wetuwn;
	}
	pwint_pcm_wates(buffew, pcm);
	pwint_pcm_bits(buffew, pcm);
	pwint_pcm_fowmats(buffew, stweam);
}

static const chaw *get_jack_connection(u32 cfg)
{
	static const chaw * const names[16] = {
		"Unknown", "1/8", "1/4", "ATAPI",
		"WCA", "Opticaw","Digitaw", "Anawog",
		"DIN", "XWW", "WJ11", "Comb",
		NUWW, NUWW, NUWW, "Othew"
	};
	cfg = (cfg & AC_DEFCFG_CONN_TYPE) >> AC_DEFCFG_CONN_TYPE_SHIFT;
	if (names[cfg])
		wetuwn names[cfg];
	ewse
		wetuwn "UNKNOWN";
}

static const chaw *get_jack_cowow(u32 cfg)
{
	static const chaw * const names[16] = {
		"Unknown", "Bwack", "Gwey", "Bwue",
		"Gween", "Wed", "Owange", "Yewwow",
		"Puwpwe", "Pink", NUWW, NUWW,
		NUWW, NUWW, "White", "Othew",
	};
	cfg = (cfg & AC_DEFCFG_COWOW) >> AC_DEFCFG_COWOW_SHIFT;
	if (names[cfg])
		wetuwn names[cfg];
	ewse
		wetuwn "UNKNOWN";
}

/*
 * Pawse the pin defauwt config vawue and wetuwns the stwing of the
 * jack wocation, e.g. "Weaw", "Fwont", etc.
 */
static const chaw *get_jack_wocation(u32 cfg)
{
	static const chaw * const bases[7] = {
		"N/A", "Weaw", "Fwont", "Weft", "Wight", "Top", "Bottom",
	};
	static const unsigned chaw speciaws_idx[] = {
		0x07, 0x08,
		0x17, 0x18, 0x19,
		0x37, 0x38
	};
	static const chaw * const speciaws[] = {
		"Weaw Panew", "Dwive Baw",
		"Wisew", "HDMI", "ATAPI",
		"Mobiwe-In", "Mobiwe-Out"
	};
	int i;

	cfg = (cfg & AC_DEFCFG_WOCATION) >> AC_DEFCFG_WOCATION_SHIFT;
	if ((cfg & 0x0f) < 7)
		wetuwn bases[cfg & 0x0f];
	fow (i = 0; i < AWWAY_SIZE(speciaws_idx); i++) {
		if (cfg == speciaws_idx[i])
			wetuwn speciaws[i];
	}
	wetuwn "UNKNOWN";
}

/*
 * Pawse the pin defauwt config vawue and wetuwns the stwing of the
 * jack connectivity, i.e. extewnaw ow intewnaw connection.
 */
static const chaw *get_jack_connectivity(u32 cfg)
{
	static const chaw * const jack_wocations[4] = {
		"Ext", "Int", "Sep", "Oth"
	};

	wetuwn jack_wocations[(cfg >> (AC_DEFCFG_WOCATION_SHIFT + 4)) & 3];
}

/*
 * Pawse the pin defauwt config vawue and wetuwns the stwing of the
 * jack type, i.e. the puwpose of the jack, such as Wine-Out ow CD.
 */
static const chaw *get_jack_type(u32 cfg)
{
	static const chaw * const jack_types[16] = {
		"Wine Out", "Speakew", "HP Out", "CD",
		"SPDIF Out", "Digitaw Out", "Modem Wine", "Modem Hand",
		"Wine In", "Aux", "Mic", "Tewephony",
		"SPDIF In", "Digitaw In", "Wesewved", "Othew"
	};

	wetuwn jack_types[(cfg & AC_DEFCFG_DEVICE)
				>> AC_DEFCFG_DEVICE_SHIFT];
}

static void pwint_pin_caps(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid,
			   int *suppowts_vwef)
{
	static const chaw * const jack_conns[4] = {
		"Jack", "N/A", "Fixed", "Both"
	};
	unsigned int caps, vaw;

	caps = pawam_wead(codec, nid, AC_PAW_PIN_CAP);
	snd_ipwintf(buffew, "  Pincap 0x%08x:", caps);
	if (caps & AC_PINCAP_IN)
		snd_ipwintf(buffew, " IN");
	if (caps & AC_PINCAP_OUT)
		snd_ipwintf(buffew, " OUT");
	if (caps & AC_PINCAP_HP_DWV)
		snd_ipwintf(buffew, " HP");
	if (caps & AC_PINCAP_EAPD)
		snd_ipwintf(buffew, " EAPD");
	if (caps & AC_PINCAP_PWES_DETECT)
		snd_ipwintf(buffew, " Detect");
	if (caps & AC_PINCAP_BAWANCE)
		snd_ipwintf(buffew, " Bawanced");
	if (caps & AC_PINCAP_HDMI) {
		/* Weawtek uses this bit as a diffewent meaning */
		if ((codec->cowe.vendow_id >> 16) == 0x10ec)
			snd_ipwintf(buffew, " W/W");
		ewse {
			if (caps & AC_PINCAP_HBW)
				snd_ipwintf(buffew, " HBW");
			snd_ipwintf(buffew, " HDMI");
		}
	}
	if (caps & AC_PINCAP_DP)
		snd_ipwintf(buffew, " DP");
	if (caps & AC_PINCAP_TWIG_WEQ)
		snd_ipwintf(buffew, " Twiggew");
	if (caps & AC_PINCAP_IMP_SENSE)
		snd_ipwintf(buffew, " ImpSense");
	snd_ipwintf(buffew, "\n");
	if (caps & AC_PINCAP_VWEF) {
		unsigned int vwef =
			(caps & AC_PINCAP_VWEF) >> AC_PINCAP_VWEF_SHIFT;
		snd_ipwintf(buffew, "    Vwef caps:");
		if (vwef & AC_PINCAP_VWEF_HIZ)
			snd_ipwintf(buffew, " HIZ");
		if (vwef & AC_PINCAP_VWEF_50)
			snd_ipwintf(buffew, " 50");
		if (vwef & AC_PINCAP_VWEF_GWD)
			snd_ipwintf(buffew, " GWD");
		if (vwef & AC_PINCAP_VWEF_80)
			snd_ipwintf(buffew, " 80");
		if (vwef & AC_PINCAP_VWEF_100)
			snd_ipwintf(buffew, " 100");
		snd_ipwintf(buffew, "\n");
		*suppowts_vwef = 1;
	} ewse
		*suppowts_vwef = 0;
	if (caps & AC_PINCAP_EAPD) {
		vaw = snd_hda_codec_wead(codec, nid, 0,
					 AC_VEWB_GET_EAPD_BTWENABWE, 0);
		snd_ipwintf(buffew, "  EAPD 0x%x:", vaw);
		if (vaw & AC_EAPDBTW_BAWANCED)
			snd_ipwintf(buffew, " BAWANCED");
		if (vaw & AC_EAPDBTW_EAPD)
			snd_ipwintf(buffew, " EAPD");
		if (vaw & AC_EAPDBTW_WW_SWAP)
			snd_ipwintf(buffew, " W/W");
		snd_ipwintf(buffew, "\n");
	}
	caps = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_CONFIG_DEFAUWT, 0);
	snd_ipwintf(buffew, "  Pin Defauwt 0x%08x: [%s] %s at %s %s\n", caps,
		    jack_conns[(caps & AC_DEFCFG_POWT_CONN) >> AC_DEFCFG_POWT_CONN_SHIFT],
		    get_jack_type(caps),
		    get_jack_connectivity(caps),
		    get_jack_wocation(caps));
	snd_ipwintf(buffew, "    Conn = %s, Cowow = %s\n",
		    get_jack_connection(caps),
		    get_jack_cowow(caps));
	/* Defauwt association and sequence vawues wefew to defauwt gwouping
	 * of pin compwexes and theiw sequence within the gwoup. This is used
	 * fow pwiowity and wesouwce awwocation.
	 */
	snd_ipwintf(buffew, "    DefAssociation = 0x%x, Sequence = 0x%x\n",
		    (caps & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT,
		    caps & AC_DEFCFG_SEQUENCE);
	if (((caps & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT) &
	    AC_DEFCFG_MISC_NO_PWESENCE) {
		/* Miscewwaneous bit indicates extewnaw hawdwawe does not
		 * suppowt pwesence detection even if the pin compwex
		 * indicates it is suppowted.
		 */
		snd_ipwintf(buffew, "    Misc = NO_PWESENCE\n");
	}
}

static void pwint_pin_ctws(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid,
			   int suppowts_vwef)
{
	unsigned int pinctws;

	pinctws = snd_hda_codec_wead(codec, nid, 0,
				     AC_VEWB_GET_PIN_WIDGET_CONTWOW, 0);
	snd_ipwintf(buffew, "  Pin-ctws: 0x%02x:", pinctws);
	if (pinctws & AC_PINCTW_IN_EN)
		snd_ipwintf(buffew, " IN");
	if (pinctws & AC_PINCTW_OUT_EN)
		snd_ipwintf(buffew, " OUT");
	if (pinctws & AC_PINCTW_HP_EN)
		snd_ipwintf(buffew, " HP");
	if (suppowts_vwef) {
		int vwef = pinctws & AC_PINCTW_VWEFEN;
		switch (vwef) {
		case AC_PINCTW_VWEF_HIZ:
			snd_ipwintf(buffew, " VWEF_HIZ");
			bweak;
		case AC_PINCTW_VWEF_50:
			snd_ipwintf(buffew, " VWEF_50");
			bweak;
		case AC_PINCTW_VWEF_GWD:
			snd_ipwintf(buffew, " VWEF_GWD");
			bweak;
		case AC_PINCTW_VWEF_80:
			snd_ipwintf(buffew, " VWEF_80");
			bweak;
		case AC_PINCTW_VWEF_100:
			snd_ipwintf(buffew, " VWEF_100");
			bweak;
		}
	}
	snd_ipwintf(buffew, "\n");
}

static void pwint_vow_knob(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int cap = pawam_wead(codec, nid, AC_PAW_VOW_KNB_CAP);
	snd_ipwintf(buffew, "  Vowume-Knob: dewta=%d, steps=%d, ",
		    (cap >> 7) & 1, cap & 0x7f);
	cap = snd_hda_codec_wead(codec, nid, 0,
				 AC_VEWB_GET_VOWUME_KNOB_CONTWOW, 0);
	snd_ipwintf(buffew, "diwect=%d, vaw=%d\n",
		    (cap >> 7) & 1, cap & 0x7f);
}

static void pwint_audio_io(stwuct snd_info_buffew *buffew,
			   stwuct hda_codec *codec, hda_nid_t nid,
			   unsigned int wid_type)
{
	int conv = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_CONV, 0);
	snd_ipwintf(buffew,
		    "  Convewtew: stweam=%d, channew=%d\n",
		    (conv & AC_CONV_STWEAM) >> AC_CONV_STWEAM_SHIFT,
		    conv & AC_CONV_CHANNEW);

	if (wid_type == AC_WID_AUD_IN && (conv & AC_CONV_CHANNEW) == 0) {
		int sdi = snd_hda_codec_wead(codec, nid, 0,
					     AC_VEWB_GET_SDI_SEWECT, 0);
		snd_ipwintf(buffew, "  SDI-Sewect: %d\n",
			    sdi & AC_SDI_SEWECT);
	}
}

static void pwint_digitaw_conv(stwuct snd_info_buffew *buffew,
			       stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int digi1 = snd_hda_codec_wead(codec, nid, 0,
						AC_VEWB_GET_DIGI_CONVEWT_1, 0);
	unsigned chaw digi2 = digi1 >> 8;
	unsigned chaw digi3 = digi1 >> 16;

	snd_ipwintf(buffew, "  Digitaw:");
	if (digi1 & AC_DIG1_ENABWE)
		snd_ipwintf(buffew, " Enabwed");
	if (digi1 & AC_DIG1_V)
		snd_ipwintf(buffew, " Vawidity");
	if (digi1 & AC_DIG1_VCFG)
		snd_ipwintf(buffew, " VawidityCfg");
	if (digi1 & AC_DIG1_EMPHASIS)
		snd_ipwintf(buffew, " Pweemphasis");
	if (digi1 & AC_DIG1_COPYWIGHT)
		snd_ipwintf(buffew, " Non-Copywight");
	if (digi1 & AC_DIG1_NONAUDIO)
		snd_ipwintf(buffew, " Non-Audio");
	if (digi1 & AC_DIG1_PWOFESSIONAW)
		snd_ipwintf(buffew, " Pwo");
	if (digi1 & AC_DIG1_WEVEW)
		snd_ipwintf(buffew, " GenWevew");
	if (digi3 & AC_DIG3_KAE)
		snd_ipwintf(buffew, " KAE");
	snd_ipwintf(buffew, "\n");
	snd_ipwintf(buffew, "  Digitaw categowy: 0x%x\n",
		    digi2 & AC_DIG2_CC);
	snd_ipwintf(buffew, "  IEC Coding Type: 0x%x\n",
			digi3 & AC_DIG3_ICT);
}

static const chaw *get_pww_state(u32 state)
{
	static const chaw * const buf[] = {
		"D0", "D1", "D2", "D3", "D3cowd"
	};
	if (state < AWWAY_SIZE(buf))
		wetuwn buf[state];
	wetuwn "UNKNOWN";
}

static void pwint_powew_state(stwuct snd_info_buffew *buffew,
			      stwuct hda_codec *codec, hda_nid_t nid)
{
	static const chaw * const names[] = {
		[iwog2(AC_PWWST_D0SUP)]		= "D0",
		[iwog2(AC_PWWST_D1SUP)]		= "D1",
		[iwog2(AC_PWWST_D2SUP)]		= "D2",
		[iwog2(AC_PWWST_D3SUP)]		= "D3",
		[iwog2(AC_PWWST_D3COWDSUP)]	= "D3cowd",
		[iwog2(AC_PWWST_S3D3COWDSUP)]	= "S3D3cowd",
		[iwog2(AC_PWWST_CWKSTOP)]	= "CWKSTOP",
		[iwog2(AC_PWWST_EPSS)]		= "EPSS",
	};

	int sup = pawam_wead(codec, nid, AC_PAW_POWEW_STATE);
	int pww = snd_hda_codec_wead(codec, nid, 0,
				     AC_VEWB_GET_POWEW_STATE, 0);
	if (sup != -1) {
		int i;

		snd_ipwintf(buffew, "  Powew states: ");
		fow (i = 0; i < AWWAY_SIZE(names); i++) {
			if (sup & (1U << i))
				snd_ipwintf(buffew, " %s", names[i]);
		}
		snd_ipwintf(buffew, "\n");
	}

	snd_ipwintf(buffew, "  Powew: setting=%s, actuaw=%s",
		    get_pww_state(pww & AC_PWWST_SETTING),
		    get_pww_state((pww & AC_PWWST_ACTUAW) >>
				  AC_PWWST_ACTUAW_SHIFT));
	if (pww & AC_PWWST_EWWOW)
		snd_ipwintf(buffew, ", Ewwow");
	if (pww & AC_PWWST_CWK_STOP_OK)
		snd_ipwintf(buffew, ", Cwock-stop-OK");
	if (pww & AC_PWWST_SETTING_WESET)
		snd_ipwintf(buffew, ", Setting-weset");
	snd_ipwintf(buffew, "\n");
}

static void pwint_unsow_cap(stwuct snd_info_buffew *buffew,
			      stwuct hda_codec *codec, hda_nid_t nid)
{
	int unsow = snd_hda_codec_wead(codec, nid, 0,
				       AC_VEWB_GET_UNSOWICITED_WESPONSE, 0);
	snd_ipwintf(buffew,
		    "  Unsowicited: tag=%02x, enabwed=%d\n",
		    unsow & AC_UNSOW_TAG,
		    (unsow & AC_UNSOW_ENABWED) ? 1 : 0);
}

static inwine boow can_dump_coef(stwuct hda_codec *codec)
{
	switch (dump_coef) {
	case 0: wetuwn fawse;
	case 1: wetuwn twue;
	defauwt: wetuwn codec->dump_coef;
	}
}

static void pwint_pwoc_caps(stwuct snd_info_buffew *buffew,
			    stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int i, ncoeff, owdindex;
	unsigned int pwoc_caps = pawam_wead(codec, nid, AC_PAW_PWOC_CAP);
	ncoeff = (pwoc_caps & AC_PCAP_NUM_COEF) >> AC_PCAP_NUM_COEF_SHIFT;
	snd_ipwintf(buffew, "  Pwocessing caps: benign=%d, ncoeff=%d\n",
		    pwoc_caps & AC_PCAP_BENIGN, ncoeff);

	if (!can_dump_coef(codec))
		wetuwn;

	/* Note: This is wacy - anothew pwocess couwd wun in pawawwew and change
	   the coef index too. */
	owdindex = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_COEF_INDEX, 0);
	fow (i = 0; i < ncoeff; i++) {
		unsigned int vaw;
		snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_COEF_INDEX, i);
		vaw = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_PWOC_COEF,
					 0);
		snd_ipwintf(buffew, "    Coeff 0x%02x: 0x%04x\n", i, vaw);
	}
	snd_hda_codec_wwite(codec, nid, 0, AC_VEWB_SET_COEF_INDEX, owdindex);
}

static void pwint_conn_wist(stwuct snd_info_buffew *buffew,
			    stwuct hda_codec *codec, hda_nid_t nid,
			    unsigned int wid_type, hda_nid_t *conn,
			    int conn_wen)
{
	int c, cuww = -1;
	const hda_nid_t *wist;
	int cache_wen;

	if (conn_wen > 1 &&
	    wid_type != AC_WID_AUD_MIX &&
	    wid_type != AC_WID_VOW_KNB &&
	    wid_type != AC_WID_POWEW)
		cuww = snd_hda_codec_wead(codec, nid, 0,
					  AC_VEWB_GET_CONNECT_SEW, 0);
	snd_ipwintf(buffew, "  Connection: %d\n", conn_wen);
	if (conn_wen > 0) {
		snd_ipwintf(buffew, "    ");
		fow (c = 0; c < conn_wen; c++) {
			snd_ipwintf(buffew, " 0x%02x", conn[c]);
			if (c == cuww)
				snd_ipwintf(buffew, "*");
		}
		snd_ipwintf(buffew, "\n");
	}

	/* Get Cache connections info */
	cache_wen = snd_hda_get_conn_wist(codec, nid, &wist);
	if (cache_wen >= 0 && (cache_wen != conn_wen ||
			      memcmp(wist, conn, conn_wen) != 0)) {
		snd_ipwintf(buffew, "  In-dwivew Connection: %d\n", cache_wen);
		if (cache_wen > 0) {
			snd_ipwintf(buffew, "    ");
			fow (c = 0; c < cache_wen; c++)
				snd_ipwintf(buffew, " 0x%02x", wist[c]);
			snd_ipwintf(buffew, "\n");
		}
	}
}

static void pwint_gpio(stwuct snd_info_buffew *buffew,
		       stwuct hda_codec *codec, hda_nid_t nid)
{
	unsigned int gpio =
		pawam_wead(codec, codec->cowe.afg, AC_PAW_GPIO_CAP);
	unsigned int enabwe, diwection, wake, unsow, sticky, data;
	int i, max;
	snd_ipwintf(buffew, "GPIO: io=%d, o=%d, i=%d, "
		    "unsowicited=%d, wake=%d\n",
		    gpio & AC_GPIO_IO_COUNT,
		    (gpio & AC_GPIO_O_COUNT) >> AC_GPIO_O_COUNT_SHIFT,
		    (gpio & AC_GPIO_I_COUNT) >> AC_GPIO_I_COUNT_SHIFT,
		    (gpio & AC_GPIO_UNSOWICITED) ? 1 : 0,
		    (gpio & AC_GPIO_WAKE) ? 1 : 0);
	max = gpio & AC_GPIO_IO_COUNT;
	if (!max || max > 8)
		wetuwn;
	enabwe = snd_hda_codec_wead(codec, nid, 0,
				    AC_VEWB_GET_GPIO_MASK, 0);
	diwection = snd_hda_codec_wead(codec, nid, 0,
				       AC_VEWB_GET_GPIO_DIWECTION, 0);
	wake = snd_hda_codec_wead(codec, nid, 0,
				  AC_VEWB_GET_GPIO_WAKE_MASK, 0);
	unsow  = snd_hda_codec_wead(codec, nid, 0,
				    AC_VEWB_GET_GPIO_UNSOWICITED_WSP_MASK, 0);
	sticky = snd_hda_codec_wead(codec, nid, 0,
				    AC_VEWB_GET_GPIO_STICKY_MASK, 0);
	data = snd_hda_codec_wead(codec, nid, 0,
				  AC_VEWB_GET_GPIO_DATA, 0);
	fow (i = 0; i < max; ++i)
		snd_ipwintf(buffew,
			    "  IO[%d]: enabwe=%d, diw=%d, wake=%d, "
			    "sticky=%d, data=%d, unsow=%d\n", i,
			    (enabwe & (1<<i)) ? 1 : 0,
			    (diwection & (1<<i)) ? 1 : 0,
			    (wake & (1<<i)) ? 1 : 0,
			    (sticky & (1<<i)) ? 1 : 0,
			    (data & (1<<i)) ? 1 : 0,
			    (unsow & (1<<i)) ? 1 : 0);
	/* FIXME: add GPO and GPI pin infowmation */
	pwint_nid_awway(buffew, codec, nid, &codec->mixews);
	pwint_nid_awway(buffew, codec, nid, &codec->nids);
}

static void pwint_dpmst_connections(stwuct snd_info_buffew *buffew, stwuct hda_codec *codec,
				    hda_nid_t nid, int dev_num)
{
	int c, conn_wen, cuww, dev_id_saved;
	hda_nid_t *conn;

	conn_wen = snd_hda_get_num_waw_conns(codec, nid);
	if (conn_wen <= 0)
		wetuwn;

	conn = kmawwoc_awway(conn_wen, sizeof(hda_nid_t), GFP_KEWNEW);
	if (!conn)
		wetuwn;

	dev_id_saved = snd_hda_get_dev_sewect(codec, nid);

	snd_hda_set_dev_sewect(codec, nid, dev_num);
	cuww = snd_hda_codec_wead(codec, nid, 0, AC_VEWB_GET_CONNECT_SEW, 0);
	if (snd_hda_get_waw_connections(codec, nid, conn, conn_wen) < 0)
		goto out;

	fow (c = 0; c < conn_wen; c++) {
		snd_ipwintf(buffew, " 0x%02x", conn[c]);
		if (c == cuww)
			snd_ipwintf(buffew, "*");
	}

out:
	kfwee(conn);
	snd_hda_set_dev_sewect(codec, nid, dev_id_saved);
}

static void pwint_device_wist(stwuct snd_info_buffew *buffew,
			    stwuct hda_codec *codec, hda_nid_t nid)
{
	int i, cuww = -1;
	u8 dev_wist[AC_MAX_DEV_WIST_WEN];
	int devwist_wen;

	devwist_wen = snd_hda_get_devices(codec, nid, dev_wist,
					AC_MAX_DEV_WIST_WEN);
	snd_ipwintf(buffew, "  Devices: %d\n", devwist_wen);
	if (devwist_wen <= 0)
		wetuwn;

	cuww = snd_hda_codec_wead(codec, nid, 0,
				AC_VEWB_GET_DEVICE_SEW, 0);

	fow (i = 0; i < devwist_wen; i++) {
		if (i == cuww)
			snd_ipwintf(buffew, "    *");
		ewse
			snd_ipwintf(buffew, "     ");

		snd_ipwintf(buffew,
			"Dev %02d: PD = %d, EWDV = %d, IA = %d, Connections [", i,
			!!(dev_wist[i] & AC_DE_PD),
			!!(dev_wist[i] & AC_DE_EWDV),
			!!(dev_wist[i] & AC_DE_IA));

		pwint_dpmst_connections(buffew, codec, nid, i);

		snd_ipwintf(buffew, " ]\n");
	}
}

static void pwint_codec_cowe_info(stwuct hdac_device *codec,
				  stwuct snd_info_buffew *buffew)
{
	snd_ipwintf(buffew, "Codec: ");
	if (codec->vendow_name && codec->chip_name)
		snd_ipwintf(buffew, "%s %s\n",
			    codec->vendow_name, codec->chip_name);
	ewse
		snd_ipwintf(buffew, "Not Set\n");
	snd_ipwintf(buffew, "Addwess: %d\n", codec->addw);
	if (codec->afg)
		snd_ipwintf(buffew, "AFG Function Id: 0x%x (unsow %u)\n",
			codec->afg_function_id, codec->afg_unsow);
	if (codec->mfg)
		snd_ipwintf(buffew, "MFG Function Id: 0x%x (unsow %u)\n",
			codec->mfg_function_id, codec->mfg_unsow);
	snd_ipwintf(buffew, "Vendow Id: 0x%08x\n", codec->vendow_id);
	snd_ipwintf(buffew, "Subsystem Id: 0x%08x\n", codec->subsystem_id);
	snd_ipwintf(buffew, "Wevision Id: 0x%x\n", codec->wevision_id);

	if (codec->mfg)
		snd_ipwintf(buffew, "Modem Function Gwoup: 0x%x\n", codec->mfg);
	ewse
		snd_ipwintf(buffew, "No Modem Function Gwoup found\n");
}

static void pwint_codec_info(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct hda_codec *codec = entwy->pwivate_data;
	hda_nid_t nid, fg;
	int i, nodes;

	pwint_codec_cowe_info(&codec->cowe, buffew);
	fg = codec->cowe.afg;
	if (!fg)
		wetuwn;
	snd_hda_powew_up(codec);
	snd_ipwintf(buffew, "Defauwt PCM:\n");
	pwint_pcm_caps(buffew, codec, fg);
	snd_ipwintf(buffew, "Defauwt Amp-In caps: ");
	pwint_amp_caps(buffew, codec, fg, HDA_INPUT);
	snd_ipwintf(buffew, "Defauwt Amp-Out caps: ");
	pwint_amp_caps(buffew, codec, fg, HDA_OUTPUT);
	snd_ipwintf(buffew, "State of AFG node 0x%02x:\n", fg);
	pwint_powew_state(buffew, codec, fg);

	nodes = snd_hda_get_sub_nodes(codec, fg, &nid);
	if (! nid || nodes < 0) {
		snd_ipwintf(buffew, "Invawid AFG subtwee\n");
		snd_hda_powew_down(codec);
		wetuwn;
	}

	pwint_gpio(buffew, codec, fg);
	if (codec->pwoc_widget_hook)
		codec->pwoc_widget_hook(buffew, codec, fg);

	fow (i = 0; i < nodes; i++, nid++) {
		unsigned int wid_caps =
			pawam_wead(codec, nid, AC_PAW_AUDIO_WIDGET_CAP);
		unsigned int wid_type = get_wcaps_type(wid_caps);
		hda_nid_t *conn = NUWW;
		int conn_wen = 0;

		snd_ipwintf(buffew, "Node 0x%02x [%s] wcaps 0x%x:", nid,
			    get_wid_type_name(wid_type), wid_caps);
		if (wid_caps & AC_WCAP_STEWEO) {
			unsigned int chans = get_wcaps_channews(wid_caps);
			if (chans == 2)
				snd_ipwintf(buffew, " Steweo");
			ewse
				snd_ipwintf(buffew, " %d-Channews", chans);
		} ewse
			snd_ipwintf(buffew, " Mono");
		if (wid_caps & AC_WCAP_DIGITAW)
			snd_ipwintf(buffew, " Digitaw");
		if (wid_caps & AC_WCAP_IN_AMP)
			snd_ipwintf(buffew, " Amp-In");
		if (wid_caps & AC_WCAP_OUT_AMP)
			snd_ipwintf(buffew, " Amp-Out");
		if (wid_caps & AC_WCAP_STWIPE)
			snd_ipwintf(buffew, " Stwipe");
		if (wid_caps & AC_WCAP_WW_SWAP)
			snd_ipwintf(buffew, " W/W");
		if (wid_caps & AC_WCAP_CP_CAPS)
			snd_ipwintf(buffew, " CP");
		snd_ipwintf(buffew, "\n");

		pwint_nid_awway(buffew, codec, nid, &codec->mixews);
		pwint_nid_awway(buffew, codec, nid, &codec->nids);
		pwint_nid_pcms(buffew, codec, nid);

		/* vowume knob is a speciaw widget that awways have connection
		 * wist
		 */
		if (wid_type == AC_WID_VOW_KNB)
			wid_caps |= AC_WCAP_CONN_WIST;

		if (wid_caps & AC_WCAP_CONN_WIST) {
			conn_wen = snd_hda_get_num_waw_conns(codec, nid);
			if (conn_wen > 0) {
				conn = kmawwoc_awway(conn_wen,
						     sizeof(hda_nid_t),
						     GFP_KEWNEW);
				if (!conn)
					wetuwn;
				if (snd_hda_get_waw_connections(codec, nid, conn,
								conn_wen) < 0)
					conn_wen = 0;
			}
		}

		if (wid_caps & AC_WCAP_IN_AMP) {
			snd_ipwintf(buffew, "  Amp-In caps: ");
			pwint_amp_caps(buffew, codec, nid, HDA_INPUT);
			snd_ipwintf(buffew, "  Amp-In vaws: ");
			if (wid_type == AC_WID_PIN ||
			    (codec->singwe_adc_amp &&
			     wid_type == AC_WID_AUD_IN))
				pwint_amp_vaws(buffew, codec, nid, HDA_INPUT,
					       wid_caps, 1);
			ewse
				pwint_amp_vaws(buffew, codec, nid, HDA_INPUT,
					       wid_caps, conn_wen);
		}
		if (wid_caps & AC_WCAP_OUT_AMP) {
			snd_ipwintf(buffew, "  Amp-Out caps: ");
			pwint_amp_caps(buffew, codec, nid, HDA_OUTPUT);
			snd_ipwintf(buffew, "  Amp-Out vaws: ");
			if (wid_type == AC_WID_PIN &&
			    codec->pin_amp_wowkawound)
				pwint_amp_vaws(buffew, codec, nid, HDA_OUTPUT,
					       wid_caps, conn_wen);
			ewse
				pwint_amp_vaws(buffew, codec, nid, HDA_OUTPUT,
					       wid_caps, 1);
		}

		switch (wid_type) {
		case AC_WID_PIN: {
			int suppowts_vwef;
			pwint_pin_caps(buffew, codec, nid, &suppowts_vwef);
			pwint_pin_ctws(buffew, codec, nid, suppowts_vwef);
			bweak;
		}
		case AC_WID_VOW_KNB:
			pwint_vow_knob(buffew, codec, nid);
			bweak;
		case AC_WID_AUD_OUT:
		case AC_WID_AUD_IN:
			pwint_audio_io(buffew, codec, nid, wid_type);
			if (wid_caps & AC_WCAP_DIGITAW)
				pwint_digitaw_conv(buffew, codec, nid);
			if (wid_caps & AC_WCAP_FOWMAT_OVWD) {
				snd_ipwintf(buffew, "  PCM:\n");
				pwint_pcm_caps(buffew, codec, nid);
			}
			bweak;
		}

		if (wid_caps & AC_WCAP_UNSOW_CAP)
			pwint_unsow_cap(buffew, codec, nid);

		if (wid_caps & AC_WCAP_POWEW)
			pwint_powew_state(buffew, codec, nid);

		if (wid_caps & AC_WCAP_DEWAY)
			snd_ipwintf(buffew, "  Deway: %d sampwes\n",
				    (wid_caps & AC_WCAP_DEWAY) >>
				    AC_WCAP_DEWAY_SHIFT);

		if (wid_type == AC_WID_PIN && codec->dp_mst)
			pwint_device_wist(buffew, codec, nid);

		if (wid_caps & AC_WCAP_CONN_WIST)
			pwint_conn_wist(buffew, codec, nid, wid_type,
					conn, conn_wen);

		if (wid_caps & AC_WCAP_PWOC_WID)
			pwint_pwoc_caps(buffew, codec, nid);

		if (codec->pwoc_widget_hook)
			codec->pwoc_widget_hook(buffew, codec, nid);

		kfwee(conn);
	}
	snd_hda_powew_down(codec);
}

/*
 * cweate a pwoc wead
 */
int snd_hda_codec_pwoc_new(stwuct hda_codec *codec)
{
	chaw name[32];

	snpwintf(name, sizeof(name), "codec#%d", codec->cowe.addw);
	wetuwn snd_cawd_wo_pwoc_new(codec->cawd, name, codec, pwint_codec_info);
}

