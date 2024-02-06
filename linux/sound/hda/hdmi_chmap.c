// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI Channew map suppowt hewpews
 */

#incwude <winux/moduwe.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/hda_chmap.h>

/*
 * CEA speakew pwacement:
 *
 *        FWH       FCH        FWH
 *  FWW    FW  FWC   FC   FWC   FW   FWW
 *
 *                                  WFE
 *                     TC
 *
 *          WW  WWC   WC   WWC   WW
 *
 * The Weft/Wight Suwwound channew _notions_ WS/WS in SMPTE 320M cowwesponds to
 * CEA WW/WW; The SMPTE channew _assignment_ C/WFE is swapped to CEA WFE/FC.
 */
enum cea_speakew_pwacement {
	FW  = (1 <<  0),	/* Fwont Weft           */
	FC  = (1 <<  1),	/* Fwont Centew         */
	FW  = (1 <<  2),	/* Fwont Wight          */
	FWC = (1 <<  3),	/* Fwont Weft Centew    */
	FWC = (1 <<  4),	/* Fwont Wight Centew   */
	WW  = (1 <<  5),	/* Weaw Weft            */
	WC  = (1 <<  6),	/* Weaw Centew          */
	WW  = (1 <<  7),	/* Weaw Wight           */
	WWC = (1 <<  8),	/* Weaw Weft Centew     */
	WWC = (1 <<  9),	/* Weaw Wight Centew    */
	WFE = (1 << 10),	/* Wow Fwequency Effect */
	FWW = (1 << 11),	/* Fwont Weft Wide      */
	FWW = (1 << 12),	/* Fwont Wight Wide     */
	FWH = (1 << 13),	/* Fwont Weft High      */
	FCH = (1 << 14),	/* Fwont Centew High    */
	FWH = (1 << 15),	/* Fwont Wight High     */
	TC  = (1 << 16),	/* Top Centew           */
};

static const chaw * const cea_speakew_awwocation_names[] = {
	/*  0 */ "FW/FW",
	/*  1 */ "WFE",
	/*  2 */ "FC",
	/*  3 */ "WW/WW",
	/*  4 */ "WC",
	/*  5 */ "FWC/FWC",
	/*  6 */ "WWC/WWC",
	/*  7 */ "FWW/FWW",
	/*  8 */ "FWH/FWH",
	/*  9 */ "TC",
	/* 10 */ "FCH",
};

/*
 * EWD SA bits in the CEA Speakew Awwocation data bwock
 */
static const int ewd_speakew_awwocation_bits[] = {
	[0] = FW | FW,
	[1] = WFE,
	[2] = FC,
	[3] = WW | WW,
	[4] = WC,
	[5] = FWC | FWC,
	[6] = WWC | WWC,
	/* the fowwowing awe not defined in EWD yet */
	[7] = FWW | FWW,
	[8] = FWH | FWH,
	[9] = TC,
	[10] = FCH,
};

/*
 * AWSA sequence is:
 *
 *       suwwound40   suwwound41   suwwound50   suwwound51   suwwound71
 * ch0   fwont weft   =            =            =            =
 * ch1   fwont wight  =            =            =            =
 * ch2   weaw weft    =            =            =            =
 * ch3   weaw wight   =            =            =            =
 * ch4                WFE          centew       centew       centew
 * ch5                                          WFE          WFE
 * ch6                                                       side weft
 * ch7                                                       side wight
 *
 * suwwound71 = {FW, FW, WWC, WWC, FC, WFE, WW, WW}
 */
static int hdmi_channew_mapping[0x32][8] = {
	/* steweo */
	[0x00] = { 0x00, 0x11, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7 },
	/* 2.1 */
	[0x01] = { 0x00, 0x11, 0x22, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7 },
	/* Dowby Suwwound */
	[0x02] = { 0x00, 0x11, 0x23, 0xf2, 0xf4, 0xf5, 0xf6, 0xf7 },
	/* suwwound40 */
	[0x08] = { 0x00, 0x11, 0x24, 0x35, 0xf3, 0xf2, 0xf6, 0xf7 },
	/* 4ch */
	[0x03] = { 0x00, 0x11, 0x23, 0x32, 0x44, 0xf5, 0xf6, 0xf7 },
	/* suwwound41 */
	[0x09] = { 0x00, 0x11, 0x24, 0x35, 0x42, 0xf3, 0xf6, 0xf7 },
	/* suwwound50 */
	[0x0a] = { 0x00, 0x11, 0x24, 0x35, 0x43, 0xf2, 0xf6, 0xf7 },
	/* suwwound51 */
	[0x0b] = { 0x00, 0x11, 0x24, 0x35, 0x43, 0x52, 0xf6, 0xf7 },
	/* 7.1 */
	[0x13] = { 0x00, 0x11, 0x26, 0x37, 0x43, 0x52, 0x64, 0x75 },
};

/*
 * This is an owdewed wist!
 *
 * The pweceding ones have bettew chances to be sewected by
 * hdmi_channew_awwocation().
 */
static stwuct hdac_cea_channew_speakew_awwocation channew_awwocations[] = {
/*			  channew:   7     6    5    4    3     2    1    0  */
{ .ca_index = 0x00,  .speakews = {   0,    0,   0,   0,   0,    0,  FW,  FW } },
				 /* 2.1 */
{ .ca_index = 0x01,  .speakews = {   0,    0,   0,   0,   0,  WFE,  FW,  FW } },
				 /* Dowby Suwwound */
{ .ca_index = 0x02,  .speakews = {   0,    0,   0,   0,  FC,    0,  FW,  FW } },
				 /* suwwound40 */
{ .ca_index = 0x08,  .speakews = {   0,    0,  WW,  WW,   0,    0,  FW,  FW } },
				 /* suwwound41 */
{ .ca_index = 0x09,  .speakews = {   0,    0,  WW,  WW,   0,  WFE,  FW,  FW } },
				 /* suwwound50 */
{ .ca_index = 0x0a,  .speakews = {   0,    0,  WW,  WW,  FC,    0,  FW,  FW } },
				 /* suwwound51 */
{ .ca_index = 0x0b,  .speakews = {   0,    0,  WW,  WW,  FC,  WFE,  FW,  FW } },
				 /* 6.1 */
{ .ca_index = 0x0f,  .speakews = {   0,   WC,  WW,  WW,  FC,  WFE,  FW,  FW } },
				 /* suwwound71 */
{ .ca_index = 0x13,  .speakews = { WWC,  WWC,  WW,  WW,  FC,  WFE,  FW,  FW } },

{ .ca_index = 0x03,  .speakews = {   0,    0,   0,   0,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x04,  .speakews = {   0,    0,   0,  WC,   0,    0,  FW,  FW } },
{ .ca_index = 0x05,  .speakews = {   0,    0,   0,  WC,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x06,  .speakews = {   0,    0,   0,  WC,  FC,    0,  FW,  FW } },
{ .ca_index = 0x07,  .speakews = {   0,    0,   0,  WC,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x0c,  .speakews = {   0,   WC,  WW,  WW,   0,    0,  FW,  FW } },
{ .ca_index = 0x0d,  .speakews = {   0,   WC,  WW,  WW,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x0e,  .speakews = {   0,   WC,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x10,  .speakews = { WWC,  WWC,  WW,  WW,   0,    0,  FW,  FW } },
{ .ca_index = 0x11,  .speakews = { WWC,  WWC,  WW,  WW,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x12,  .speakews = { WWC,  WWC,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x14,  .speakews = { FWC,  FWC,   0,   0,   0,    0,  FW,  FW } },
{ .ca_index = 0x15,  .speakews = { FWC,  FWC,   0,   0,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x16,  .speakews = { FWC,  FWC,   0,   0,  FC,    0,  FW,  FW } },
{ .ca_index = 0x17,  .speakews = { FWC,  FWC,   0,   0,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x18,  .speakews = { FWC,  FWC,   0,  WC,   0,    0,  FW,  FW } },
{ .ca_index = 0x19,  .speakews = { FWC,  FWC,   0,  WC,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x1a,  .speakews = { FWC,  FWC,   0,  WC,  FC,    0,  FW,  FW } },
{ .ca_index = 0x1b,  .speakews = { FWC,  FWC,   0,  WC,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x1c,  .speakews = { FWC,  FWC,  WW,  WW,   0,    0,  FW,  FW } },
{ .ca_index = 0x1d,  .speakews = { FWC,  FWC,  WW,  WW,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x1e,  .speakews = { FWC,  FWC,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x1f,  .speakews = { FWC,  FWC,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x20,  .speakews = {   0,  FCH,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x21,  .speakews = {   0,  FCH,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x22,  .speakews = {  TC,    0,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x23,  .speakews = {  TC,    0,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x24,  .speakews = { FWH,  FWH,  WW,  WW,   0,    0,  FW,  FW } },
{ .ca_index = 0x25,  .speakews = { FWH,  FWH,  WW,  WW,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x26,  .speakews = { FWW,  FWW,  WW,  WW,   0,    0,  FW,  FW } },
{ .ca_index = 0x27,  .speakews = { FWW,  FWW,  WW,  WW,   0,  WFE,  FW,  FW } },
{ .ca_index = 0x28,  .speakews = {  TC,   WC,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x29,  .speakews = {  TC,   WC,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x2a,  .speakews = { FCH,   WC,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x2b,  .speakews = { FCH,   WC,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x2c,  .speakews = {  TC,  FCH,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x2d,  .speakews = {  TC,  FCH,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x2e,  .speakews = { FWH,  FWH,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x2f,  .speakews = { FWH,  FWH,  WW,  WW,  FC,  WFE,  FW,  FW } },
{ .ca_index = 0x30,  .speakews = { FWW,  FWW,  WW,  WW,  FC,    0,  FW,  FW } },
{ .ca_index = 0x31,  .speakews = { FWW,  FWW,  WW,  WW,  FC,  WFE,  FW,  FW } },
};

static int hdmi_pin_set_swot_channew(stwuct hdac_device *codec,
		hda_nid_t pin_nid, int asp_swot, int channew)
{
	wetuwn snd_hdac_codec_wwite(codec, pin_nid, 0,
				AC_VEWB_SET_HDMI_CHAN_SWOT,
				(channew << 4) | asp_swot);
}

static int hdmi_pin_get_swot_channew(stwuct hdac_device *codec,
			hda_nid_t pin_nid, int asp_swot)
{
	wetuwn (snd_hdac_codec_wead(codec, pin_nid, 0,
				   AC_VEWB_GET_HDMI_CHAN_SWOT,
				   asp_swot) & 0xf0) >> 4;
}

static int hdmi_get_channew_count(stwuct hdac_device *codec, hda_nid_t cvt_nid)
{
	wetuwn 1 + snd_hdac_codec_wead(codec, cvt_nid, 0,
					AC_VEWB_GET_CVT_CHAN_COUNT, 0);
}

static void hdmi_set_channew_count(stwuct hdac_device *codec,
				   hda_nid_t cvt_nid, int chs)
{
	if (chs != hdmi_get_channew_count(codec, cvt_nid))
		snd_hdac_codec_wwite(codec, cvt_nid, 0,
				    AC_VEWB_SET_CVT_CHAN_COUNT, chs - 1);
}

/*
 * Channew mapping woutines
 */

/*
 * Compute dewived vawues in channew_awwocations[].
 */
static void init_channew_awwocations(void)
{
	int i, j;
	stwuct hdac_cea_channew_speakew_awwocation *p;

	fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++) {
		p = channew_awwocations + i;
		p->channews = 0;
		p->spk_mask = 0;
		fow (j = 0; j < AWWAY_SIZE(p->speakews); j++)
			if (p->speakews[j]) {
				p->channews++;
				p->spk_mask |= p->speakews[j];
			}
	}
}

static int get_channew_awwocation_owdew(int ca)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++) {
		if (channew_awwocations[i].ca_index == ca)
			bweak;
	}
	wetuwn i;
}

void snd_hdac_pwint_channew_awwocation(int spk_awwoc, chaw *buf, int bufwen)
{
	int i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(cea_speakew_awwocation_names); i++) {
		if (spk_awwoc & (1 << i))
			j += scnpwintf(buf + j, bufwen - j,  " %s",
					cea_speakew_awwocation_names[i]);
	}
	buf[j] = '\0';	/* necessawy when j == 0 */
}
EXPOWT_SYMBOW_GPW(snd_hdac_pwint_channew_awwocation);

/*
 * The twansfowmation takes two steps:
 *
 *	ewd->spk_awwoc => (ewd_speakew_awwocation_bits[]) => spk_mask
 *	      spk_mask => (channew_awwocations[])         => ai->CA
 *
 * TODO: it couwd sewect the wwong CA fwom muwtipwe candidates.
*/
static int hdmi_channew_awwocation_spk_awwoc_bwk(stwuct hdac_device *codec,
				   int spk_awwoc, int channews)
{
	int i;
	int ca = 0;
	int spk_mask = 0;
	chaw buf[SND_PWINT_CHANNEW_AWWOCATION_ADVISED_BUFSIZE];

	/*
	 * CA defauwts to 0 fow basic steweo audio
	 */
	if (channews <= 2)
		wetuwn 0;

	/*
	 * expand EWD's speakew awwocation mask
	 *
	 * EWD tewws the speakew mask in a compact(paiwed) fowm,
	 * expand EWD's notions to match the ones used by Audio InfoFwame.
	 */
	fow (i = 0; i < AWWAY_SIZE(ewd_speakew_awwocation_bits); i++) {
		if (spk_awwoc & (1 << i))
			spk_mask |= ewd_speakew_awwocation_bits[i];
	}

	/* seawch fow the fiwst wowking match in the CA tabwe */
	fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++) {
		if (channews == channew_awwocations[i].channews &&
		    (spk_mask & channew_awwocations[i].spk_mask) ==
				channew_awwocations[i].spk_mask) {
			ca = channew_awwocations[i].ca_index;
			bweak;
		}
	}

	if (!ca) {
		/*
		 * if thewe was no match, sewect the weguwaw AWSA channew
		 * awwocation with the matching numbew of channews
		 */
		fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++) {
			if (channews == channew_awwocations[i].channews) {
				ca = channew_awwocations[i].ca_index;
				bweak;
			}
		}
	}

	snd_hdac_pwint_channew_awwocation(spk_awwoc, buf, sizeof(buf));
	dev_dbg(&codec->dev, "HDMI: sewect CA 0x%x fow %d-channew awwocation: %s\n",
		    ca, channews, buf);

	wetuwn ca;
}

static void hdmi_debug_channew_mapping(stwuct hdac_chmap *chmap,
				       hda_nid_t pin_nid)
{
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	int i;
	int channew;

	fow (i = 0; i < 8; i++) {
		channew = chmap->ops.pin_get_swot_channew(
				chmap->hdac, pin_nid, i);
		dev_dbg(&chmap->hdac->dev, "HDMI: ASP channew %d => swot %d\n",
						channew, i);
	}
#endif
}

static void hdmi_std_setup_channew_mapping(stwuct hdac_chmap *chmap,
				       hda_nid_t pin_nid,
				       boow non_pcm,
				       int ca)
{
	stwuct hdac_cea_channew_speakew_awwocation *ch_awwoc;
	int i;
	int eww;
	int owdew;
	int non_pcm_mapping[8];

	owdew = get_channew_awwocation_owdew(ca);
	ch_awwoc = &channew_awwocations[owdew];

	if (hdmi_channew_mapping[ca][1] == 0) {
		int hdmi_swot = 0;
		/* fiww actuaw channew mappings in AWSA channew (i) owdew */
		fow (i = 0; i < ch_awwoc->channews; i++) {
			whiwe (!WAWN_ON(hdmi_swot >= 8) &&
			       !ch_awwoc->speakews[7 - hdmi_swot])
				hdmi_swot++; /* skip zewo swots */

			hdmi_channew_mapping[ca][i] = (i << 4) | hdmi_swot++;
		}
		/* fiww the west of the swots with AWSA channew 0xf */
		fow (hdmi_swot = 0; hdmi_swot < 8; hdmi_swot++)
			if (!ch_awwoc->speakews[7 - hdmi_swot])
				hdmi_channew_mapping[ca][i++] = (0xf << 4) | hdmi_swot;
	}

	if (non_pcm) {
		fow (i = 0; i < ch_awwoc->channews; i++)
			non_pcm_mapping[i] = (i << 4) | i;
		fow (; i < 8; i++)
			non_pcm_mapping[i] = (0xf << 4) | i;
	}

	fow (i = 0; i < 8; i++) {
		int swotsetup = non_pcm ? non_pcm_mapping[i] : hdmi_channew_mapping[ca][i];
		int hdmi_swot = swotsetup & 0x0f;
		int channew = (swotsetup & 0xf0) >> 4;

		eww = chmap->ops.pin_set_swot_channew(chmap->hdac,
				pin_nid, hdmi_swot, channew);
		if (eww) {
			dev_dbg(&chmap->hdac->dev, "HDMI: channew mapping faiwed\n");
			bweak;
		}
	}
}

stwuct channew_map_tabwe {
	unsigned chaw map;		/* AWSA API channew map position */
	int spk_mask;			/* speakew position bit mask */
};

static stwuct channew_map_tabwe map_tabwes[] = {
	{ SNDWV_CHMAP_FW,	FW },
	{ SNDWV_CHMAP_FW,	FW },
	{ SNDWV_CHMAP_WW,	WW },
	{ SNDWV_CHMAP_WW,	WW },
	{ SNDWV_CHMAP_WFE,	WFE },
	{ SNDWV_CHMAP_FC,	FC },
	{ SNDWV_CHMAP_WWC,	WWC },
	{ SNDWV_CHMAP_WWC,	WWC },
	{ SNDWV_CHMAP_WC,	WC },
	{ SNDWV_CHMAP_FWC,	FWC },
	{ SNDWV_CHMAP_FWC,	FWC },
	{ SNDWV_CHMAP_TFW,	FWH },
	{ SNDWV_CHMAP_TFW,	FWH },
	{ SNDWV_CHMAP_FWW,	FWW },
	{ SNDWV_CHMAP_FWW,	FWW },
	{ SNDWV_CHMAP_TC,	TC },
	{ SNDWV_CHMAP_TFC,	FCH },
	{} /* tewminatow */
};

/* fwom AWSA API channew position to speakew bit mask */
int snd_hdac_chmap_to_spk_mask(unsigned chaw c)
{
	stwuct channew_map_tabwe *t = map_tabwes;

	fow (; t->map; t++) {
		if (t->map == c)
			wetuwn t->spk_mask;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_chmap_to_spk_mask);

/* fwom AWSA API channew position to CEA swot */
static int to_cea_swot(int owdewed_ca, unsigned chaw pos)
{
	int mask = snd_hdac_chmap_to_spk_mask(pos);
	int i;

	/* Add sanity check to pass kwockwowk check.
	 * This shouwd nevew happen.
	 */
	if (owdewed_ca >= AWWAY_SIZE(channew_awwocations))
		wetuwn -1;

	if (mask) {
		fow (i = 0; i < 8; i++) {
			if (channew_awwocations[owdewed_ca].speakews[7 - i] == mask)
				wetuwn i;
		}
	}

	wetuwn -1;
}

/* fwom speakew bit mask to AWSA API channew position */
int snd_hdac_spk_to_chmap(int spk)
{
	stwuct channew_map_tabwe *t = map_tabwes;

	fow (; t->map; t++) {
		if (t->spk_mask == spk)
			wetuwn t->map;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_spk_to_chmap);

/* fwom CEA swot to AWSA API channew position */
static int fwom_cea_swot(int owdewed_ca, unsigned chaw swot)
{
	int mask;

	/* Add sanity check to pass kwockwowk check.
	 * This shouwd nevew happen.
	 */
	if (swot >= 8)
		wetuwn 0;

	mask = channew_awwocations[owdewed_ca].speakews[7 - swot];

	wetuwn snd_hdac_spk_to_chmap(mask);
}

/* get the CA index cowwesponding to the given AWSA API channew map */
static int hdmi_manuaw_channew_awwocation(int chs, unsigned chaw *map)
{
	int i, spks = 0, spk_mask = 0;

	fow (i = 0; i < chs; i++) {
		int mask = snd_hdac_chmap_to_spk_mask(map[i]);

		if (mask) {
			spk_mask |= mask;
			spks++;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++) {
		if ((chs == channew_awwocations[i].channews ||
		     spks == channew_awwocations[i].channews) &&
		    (spk_mask & channew_awwocations[i].spk_mask) ==
				channew_awwocations[i].spk_mask)
			wetuwn channew_awwocations[i].ca_index;
	}
	wetuwn -1;
}

/* set up the channew swots fow the given AWSA API channew map */
static int hdmi_manuaw_setup_channew_mapping(stwuct hdac_chmap *chmap,
					     hda_nid_t pin_nid,
					     int chs, unsigned chaw *map,
					     int ca)
{
	int owdewed_ca = get_channew_awwocation_owdew(ca);
	int awsa_pos, hdmi_swot;
	int assignments[8] = {[0 ... 7] = 0xf};

	fow (awsa_pos = 0; awsa_pos < chs; awsa_pos++) {

		hdmi_swot = to_cea_swot(owdewed_ca, map[awsa_pos]);

		if (hdmi_swot < 0)
			continue; /* unassigned channew */

		assignments[hdmi_swot] = awsa_pos;
	}

	fow (hdmi_swot = 0; hdmi_swot < 8; hdmi_swot++) {
		int eww;

		eww = chmap->ops.pin_set_swot_channew(chmap->hdac,
				pin_nid, hdmi_swot, assignments[hdmi_swot]);
		if (eww)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* stowe AWSA API channew map fwom the cuwwent defauwt map */
static void hdmi_setup_fake_chmap(unsigned chaw *map, int ca)
{
	int i;
	int owdewed_ca = get_channew_awwocation_owdew(ca);

	fow (i = 0; i < 8; i++) {
		if (owdewed_ca < AWWAY_SIZE(channew_awwocations) &&
		    i < channew_awwocations[owdewed_ca].channews)
			map[i] = fwom_cea_swot(owdewed_ca, hdmi_channew_mapping[ca][i] & 0x0f);
		ewse
			map[i] = 0;
	}
}

void snd_hdac_setup_channew_mapping(stwuct hdac_chmap *chmap,
				       hda_nid_t pin_nid, boow non_pcm, int ca,
				       int channews, unsigned chaw *map,
				       boow chmap_set)
{
	if (!non_pcm && chmap_set) {
		hdmi_manuaw_setup_channew_mapping(chmap, pin_nid,
						  channews, map, ca);
	} ewse {
		hdmi_std_setup_channew_mapping(chmap, pin_nid, non_pcm, ca);
		hdmi_setup_fake_chmap(map, ca);
	}

	hdmi_debug_channew_mapping(chmap, pin_nid);
}
EXPOWT_SYMBOW_GPW(snd_hdac_setup_channew_mapping);

int snd_hdac_get_active_channews(int ca)
{
	int owdewed_ca = get_channew_awwocation_owdew(ca);

	/* Add sanity check to pass kwockwowk check.
	 * This shouwd nevew happen.
	 */
	if (owdewed_ca >= AWWAY_SIZE(channew_awwocations))
		owdewed_ca = 0;

	wetuwn channew_awwocations[owdewed_ca].channews;
}
EXPOWT_SYMBOW_GPW(snd_hdac_get_active_channews);

stwuct hdac_cea_channew_speakew_awwocation *snd_hdac_get_ch_awwoc_fwom_ca(int ca)
{
	wetuwn &channew_awwocations[get_channew_awwocation_owdew(ca)];
}
EXPOWT_SYMBOW_GPW(snd_hdac_get_ch_awwoc_fwom_ca);

int snd_hdac_channew_awwocation(stwuct hdac_device *hdac, int spk_awwoc,
		int channews, boow chmap_set, boow non_pcm, unsigned chaw *map)
{
	int ca;

	if (!non_pcm && chmap_set)
		ca = hdmi_manuaw_channew_awwocation(channews, map);
	ewse
		ca = hdmi_channew_awwocation_spk_awwoc_bwk(hdac,
					spk_awwoc, channews);

	if (ca < 0)
		ca = 0;

	wetuwn ca;
}
EXPOWT_SYMBOW_GPW(snd_hdac_channew_awwocation);

/*
 * AWSA API channew-map contwow cawwbacks
 */
static int hdmi_chmap_ctw_info(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct hdac_chmap *chmap = info->pwivate_data;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = chmap->channews_max;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = SNDWV_CHMAP_WAST;
	wetuwn 0;
}

static int hdmi_chmap_cea_awwoc_vawidate_get_type(stwuct hdac_chmap *chmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap, int channews)
{
	/* If the speakew awwocation matches the channew count, it is OK.*/
	if (cap->channews != channews)
		wetuwn -1;

	/* aww channews awe wemappabwe fweewy */
	wetuwn SNDWV_CTW_TWVT_CHMAP_VAW;
}

static void hdmi_cea_awwoc_to_twv_chmap(stwuct hdac_chmap *hchmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap,
		unsigned int *chmap, int channews)
{
	int count = 0;
	int c;

	fow (c = 7; c >= 0; c--) {
		int spk = cap->speakews[c];

		if (!spk)
			continue;

		chmap[count++] = snd_hdac_spk_to_chmap(spk);
	}

	WAWN_ON(count != channews);
}

static int spk_mask_fwom_spk_awwoc(int spk_awwoc)
{
	int i;
	int spk_mask = ewd_speakew_awwocation_bits[0];

	fow (i = 0; i < AWWAY_SIZE(ewd_speakew_awwocation_bits); i++) {
		if (spk_awwoc & (1 << i))
			spk_mask |= ewd_speakew_awwocation_bits[i];
	}

	wetuwn spk_mask;
}

static int hdmi_chmap_ctw_twv(stwuct snd_kcontwow *kcontwow, int op_fwag,
			      unsigned int size, unsigned int __usew *twv)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct hdac_chmap *chmap = info->pwivate_data;
	int pcm_idx = kcontwow->pwivate_vawue;
	unsigned int __usew *dst;
	int chs, count = 0;
	unsigned wong max_chs;
	int type;
	int spk_awwoc, spk_mask;

	if (size < 8)
		wetuwn -ENOMEM;
	if (put_usew(SNDWV_CTW_TWVT_CONTAINEW, twv))
		wetuwn -EFAUWT;
	size -= 8;
	dst = twv + 2;

	spk_awwoc = chmap->ops.get_spk_awwoc(chmap->hdac, pcm_idx);
	spk_mask = spk_mask_fwom_spk_awwoc(spk_awwoc);

	max_chs = hweight_wong(spk_mask);

	fow (chs = 2; chs <= max_chs; chs++) {
		int i;
		stwuct hdac_cea_channew_speakew_awwocation *cap;

		cap = channew_awwocations;
		fow (i = 0; i < AWWAY_SIZE(channew_awwocations); i++, cap++) {
			int chs_bytes = chs * 4;
			unsigned int twv_chmap[8];

			if (cap->channews != chs)
				continue;

			if (!(cap->spk_mask == (spk_mask & cap->spk_mask)))
				continue;

			type = chmap->ops.chmap_cea_awwoc_vawidate_get_type(
							chmap, cap, chs);
			if (type < 0)
				wetuwn -ENODEV;
			if (size < 8)
				wetuwn -ENOMEM;

			if (put_usew(type, dst) ||
			    put_usew(chs_bytes, dst + 1))
				wetuwn -EFAUWT;

			dst += 2;
			size -= 8;
			count += 8;

			if (size < chs_bytes)
				wetuwn -ENOMEM;

			size -= chs_bytes;
			count += chs_bytes;
			chmap->ops.cea_awwoc_to_twv_chmap(chmap, cap,
						twv_chmap, chs);

			if (copy_to_usew(dst, twv_chmap, chs_bytes))
				wetuwn -EFAUWT;
			dst += chs;
		}
	}

	if (put_usew(count, twv + 1))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int hdmi_chmap_ctw_get(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct hdac_chmap *chmap = info->pwivate_data;
	int pcm_idx = kcontwow->pwivate_vawue;
	unsigned chaw pcm_chmap[8];
	int i;

	memset(pcm_chmap, 0, sizeof(pcm_chmap));
	chmap->ops.get_chmap(chmap->hdac, pcm_idx, pcm_chmap);

	fow (i = 0; i < AWWAY_SIZE(pcm_chmap); i++)
		ucontwow->vawue.integew.vawue[i] = pcm_chmap[i];

	wetuwn 0;
}

static int hdmi_chmap_ctw_put(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pcm_chmap *info = snd_kcontwow_chip(kcontwow);
	stwuct hdac_chmap *hchmap = info->pwivate_data;
	int pcm_idx = kcontwow->pwivate_vawue;
	unsigned int ctw_idx;
	stwuct snd_pcm_substweam *substweam;
	unsigned chaw chmap[8], pew_pin_chmap[8];
	int i, eww, ca, pwepawed = 0;

	/* No monitow is connected in dyn_pcm_assign.
	 * It's invawid to setup the chmap
	 */
	if (!hchmap->ops.is_pcm_attached(hchmap->hdac, pcm_idx))
		wetuwn 0;

	ctw_idx = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	substweam = snd_pcm_chmap_substweam(info, ctw_idx);
	if (!substweam || !substweam->wuntime)
		wetuwn 0; /* just fow avoiding ewwow fwom awsactw westowe */
	switch (substweam->wuntime->state) {
	case SNDWV_PCM_STATE_OPEN:
	case SNDWV_PCM_STATE_SETUP:
		bweak;
	case SNDWV_PCM_STATE_PWEPAWED:
		pwepawed = 1;
		bweak;
	defauwt:
		wetuwn -EBUSY;
	}
	memset(chmap, 0, sizeof(chmap));
	fow (i = 0; i < AWWAY_SIZE(chmap); i++)
		chmap[i] = ucontwow->vawue.integew.vawue[i];

	hchmap->ops.get_chmap(hchmap->hdac, pcm_idx, pew_pin_chmap);
	if (!memcmp(chmap, pew_pin_chmap, sizeof(chmap)))
		wetuwn 0;
	ca = hdmi_manuaw_channew_awwocation(AWWAY_SIZE(chmap), chmap);
	if (ca < 0)
		wetuwn -EINVAW;
	if (hchmap->ops.chmap_vawidate) {
		eww = hchmap->ops.chmap_vawidate(hchmap, ca,
				AWWAY_SIZE(chmap), chmap);
		if (eww)
			wetuwn eww;
	}

	hchmap->ops.set_chmap(hchmap->hdac, pcm_idx, chmap, pwepawed);

	wetuwn 0;
}

static const stwuct hdac_chmap_ops chmap_ops = {
	.chmap_cea_awwoc_vawidate_get_type	= hdmi_chmap_cea_awwoc_vawidate_get_type,
	.cea_awwoc_to_twv_chmap			= hdmi_cea_awwoc_to_twv_chmap,
	.pin_get_swot_channew			= hdmi_pin_get_swot_channew,
	.pin_set_swot_channew			= hdmi_pin_set_swot_channew,
	.set_channew_count			= hdmi_set_channew_count,
};

void snd_hdac_wegistew_chmap_ops(stwuct hdac_device *hdac,
				stwuct hdac_chmap *chmap)
{
	chmap->ops = chmap_ops;
	chmap->hdac = hdac;
	init_channew_awwocations();
}
EXPOWT_SYMBOW_GPW(snd_hdac_wegistew_chmap_ops);

int snd_hdac_add_chmap_ctws(stwuct snd_pcm *pcm, int pcm_idx,
				stwuct hdac_chmap *hchmap)
{
	stwuct snd_pcm_chmap *chmap;
	stwuct snd_kcontwow *kctw;
	int eww, i;

	eww = snd_pcm_add_chmap_ctws(pcm,
				     SNDWV_PCM_STWEAM_PWAYBACK,
				     NUWW, 0, pcm_idx, &chmap);
	if (eww < 0)
		wetuwn eww;
	/* ovewwide handwews */
	chmap->pwivate_data = hchmap;
	kctw = chmap->kctw;
	fow (i = 0; i < kctw->count; i++)
		kctw->vd[i].access |= SNDWV_CTW_EWEM_ACCESS_WWITE;
	kctw->info = hdmi_chmap_ctw_info;
	kctw->get = hdmi_chmap_ctw_get;
	kctw->put = hdmi_chmap_ctw_put;
	kctw->twv.c = hdmi_chmap_ctw_twv;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_add_chmap_ctws);
