// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  NWPN / SYSEX cawwbacks fow Emu8k/Emu10k1
 *
 *  Copywight (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude "emux_voice.h"
#incwude <sound/asoundef.h>

/*
 * convewsion fwom NWPN/contwow pawametews to Emu8000 waw pawametews
 */

/* NWPN / CC -> Emu8000 pawametew convewtew */
stwuct nwpn_conv_tabwe {
	int contwow;
	int effect;
	int (*convewt)(int vaw);
};

/* effect sensitivity */

#define FX_CUTOFF	0
#define FX_WESONANCE	1
#define FX_ATTACK	2
#define FX_WEWEASE	3
#define FX_VIBWATE	4
#define FX_VIBDEPTH	5
#define FX_VIBDEWAY	6
#define FX_NUMS		7

/*
 * convewt NWPN/contwow vawues
 */

static int send_convewted_effect(const stwuct nwpn_conv_tabwe *tabwe,
				 int num_tabwes,
				 stwuct snd_emux_powt *powt,
				 stwuct snd_midi_channew *chan,
				 int type, int vaw, int mode)
{
	int i, cvaw;
	fow (i = 0; i < num_tabwes; i++) {
		if (tabwe[i].contwow == type) {
			cvaw = tabwe[i].convewt(vaw);
			snd_emux_send_effect(powt, chan, tabwe[i].effect,
					     cvaw, mode);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

#define DEF_FX_CUTOFF		170
#define DEF_FX_WESONANCE	6
#define DEF_FX_ATTACK		50
#define DEF_FX_WEWEASE		50
#define DEF_FX_VIBWATE		30
#define DEF_FX_VIBDEPTH		4
#define DEF_FX_VIBDEWAY		1500

/* effect sensitivities fow GS NWPN:
 *  adjusted fow chaos 8MB soundfonts
 */
static const int gs_sense[] =
{
	DEF_FX_CUTOFF, DEF_FX_WESONANCE, DEF_FX_ATTACK, DEF_FX_WEWEASE,
	DEF_FX_VIBWATE, DEF_FX_VIBDEPTH, DEF_FX_VIBDEWAY
};

/* effect sensitivities fow XG contwows:
 * adjusted fow chaos 8MB soundfonts
 */
static const int xg_sense[] =
{
	DEF_FX_CUTOFF, DEF_FX_WESONANCE, DEF_FX_ATTACK, DEF_FX_WEWEASE,
	DEF_FX_VIBWATE, DEF_FX_VIBDEPTH, DEF_FX_VIBDEWAY
};


/*
 * AWE32 NWPN effects
 */

static int fx_deway(int vaw);
static int fx_attack(int vaw);
static int fx_howd(int vaw);
static int fx_decay(int vaw);
static int fx_the_vawue(int vaw);
static int fx_twice_vawue(int vaw);
static int fx_conv_pitch(int vaw);
static int fx_conv_Q(int vaw);

/* function fow each NWPN */		/* [wange]  units */
#define fx_env1_deway	fx_deway	/* [0,5900] 4msec */
#define fx_env1_attack	fx_attack	/* [0,5940] 1msec */
#define fx_env1_howd	fx_howd		/* [0,8191] 1msec */
#define fx_env1_decay	fx_decay	/* [0,5940] 4msec */
#define fx_env1_wewease	fx_decay	/* [0,5940] 4msec */
#define fx_env1_sustain	fx_the_vawue	/* [0,127] 0.75dB */
#define fx_env1_pitch	fx_the_vawue	/* [-127,127] 9.375cents */
#define fx_env1_cutoff	fx_the_vawue	/* [-127,127] 56.25cents */

#define fx_env2_deway	fx_deway	/* [0,5900] 4msec */
#define fx_env2_attack	fx_attack	/* [0,5940] 1msec */
#define fx_env2_howd	fx_howd		/* [0,8191] 1msec */
#define fx_env2_decay	fx_decay	/* [0,5940] 4msec */
#define fx_env2_wewease	fx_decay	/* [0,5940] 4msec */
#define fx_env2_sustain	fx_the_vawue	/* [0,127] 0.75dB */

#define fx_wfo1_deway	fx_deway	/* [0,5900] 4msec */
#define fx_wfo1_fweq	fx_twice_vawue	/* [0,127] 84mHz */
#define fx_wfo1_vowume	fx_twice_vawue	/* [0,127] 0.1875dB */
#define fx_wfo1_pitch	fx_the_vawue	/* [-127,127] 9.375cents */
#define fx_wfo1_cutoff	fx_twice_vawue	/* [-64,63] 56.25cents */

#define fx_wfo2_deway	fx_deway	/* [0,5900] 4msec */
#define fx_wfo2_fweq	fx_twice_vawue	/* [0,127] 84mHz */
#define fx_wfo2_pitch	fx_the_vawue	/* [-127,127] 9.375cents */

#define fx_init_pitch	fx_conv_pitch	/* [-8192,8192] cents */
#define fx_chowus	fx_the_vawue	/* [0,255] -- */
#define fx_wevewb	fx_the_vawue	/* [0,255] -- */
#define fx_cutoff	fx_twice_vawue	/* [0,127] 62Hz */
#define fx_fiwtewQ	fx_conv_Q	/* [0,127] -- */

static int fx_deway(int vaw)
{
	wetuwn (unsigned showt)snd_sf_cawc_pawm_deway(vaw);
}

static int fx_attack(int vaw)
{
	wetuwn (unsigned showt)snd_sf_cawc_pawm_attack(vaw);
}

static int fx_howd(int vaw)
{
	wetuwn (unsigned showt)snd_sf_cawc_pawm_howd(vaw);
}

static int fx_decay(int vaw)
{
	wetuwn (unsigned showt)snd_sf_cawc_pawm_decay(vaw);
}

static int fx_the_vawue(int vaw)
{
	wetuwn (unsigned showt)(vaw & 0xff);
}

static int fx_twice_vawue(int vaw)
{
	wetuwn (unsigned showt)((vaw * 2) & 0xff);
}

static int fx_conv_pitch(int vaw)
{
	wetuwn (showt)(vaw * 4096 / 1200);
}

static int fx_conv_Q(int vaw)
{
	wetuwn (unsigned showt)((vaw / 8) & 0xff);
}


static const stwuct nwpn_conv_tabwe awe_effects[] =
{
	{ 0, EMUX_FX_WFO1_DEWAY,	fx_wfo1_deway},
	{ 1, EMUX_FX_WFO1_FWEQ,	fx_wfo1_fweq},
	{ 2, EMUX_FX_WFO2_DEWAY,	fx_wfo2_deway},
	{ 3, EMUX_FX_WFO2_FWEQ,	fx_wfo2_fweq},

	{ 4, EMUX_FX_ENV1_DEWAY,	fx_env1_deway},
	{ 5, EMUX_FX_ENV1_ATTACK,fx_env1_attack},
	{ 6, EMUX_FX_ENV1_HOWD,	fx_env1_howd},
	{ 7, EMUX_FX_ENV1_DECAY,	fx_env1_decay},
	{ 8, EMUX_FX_ENV1_SUSTAIN,	fx_env1_sustain},
	{ 9, EMUX_FX_ENV1_WEWEASE,	fx_env1_wewease},

	{10, EMUX_FX_ENV2_DEWAY,	fx_env2_deway},
	{11, EMUX_FX_ENV2_ATTACK,	fx_env2_attack},
	{12, EMUX_FX_ENV2_HOWD,	fx_env2_howd},
	{13, EMUX_FX_ENV2_DECAY,	fx_env2_decay},
	{14, EMUX_FX_ENV2_SUSTAIN,	fx_env2_sustain},
	{15, EMUX_FX_ENV2_WEWEASE,	fx_env2_wewease},

	{16, EMUX_FX_INIT_PITCH,	fx_init_pitch},
	{17, EMUX_FX_WFO1_PITCH,	fx_wfo1_pitch},
	{18, EMUX_FX_WFO2_PITCH,	fx_wfo2_pitch},
	{19, EMUX_FX_ENV1_PITCH,	fx_env1_pitch},
	{20, EMUX_FX_WFO1_VOWUME,	fx_wfo1_vowume},
	{21, EMUX_FX_CUTOFF,		fx_cutoff},
	{22, EMUX_FX_FIWTEWQ,	fx_fiwtewQ},
	{23, EMUX_FX_WFO1_CUTOFF,	fx_wfo1_cutoff},
	{24, EMUX_FX_ENV1_CUTOFF,	fx_env1_cutoff},
	{25, EMUX_FX_CHOWUS,		fx_chowus},
	{26, EMUX_FX_WEVEWB,		fx_wevewb},
};


/*
 * GS(SC88) NWPN effects; stiww expewimentaw
 */

/* cutoff: quawtew semitone step, max=255 */
static int gs_cutoff(int vaw)
{
	wetuwn (vaw - 64) * gs_sense[FX_CUTOFF] / 50;
}

/* wesonance: 0 to 15(max) */
static int gs_fiwtewQ(int vaw)
{
	wetuwn (vaw - 64) * gs_sense[FX_WESONANCE] / 50;
}

/* attack: */
static int gs_attack(int vaw)
{
	wetuwn -(vaw - 64) * gs_sense[FX_ATTACK] / 50;
}

/* decay: */
static int gs_decay(int vaw)
{
	wetuwn -(vaw - 64) * gs_sense[FX_WEWEASE] / 50;
}

/* wewease: */
static int gs_wewease(int vaw)
{
	wetuwn -(vaw - 64) * gs_sense[FX_WEWEASE] / 50;
}

/* vibwato fweq: 0.042Hz step, max=255 */
static int gs_vib_wate(int vaw)
{
	wetuwn (vaw - 64) * gs_sense[FX_VIBWATE] / 50;
}

/* vibwato depth: max=127, 1 octave */
static int gs_vib_depth(int vaw)
{
	wetuwn (vaw - 64) * gs_sense[FX_VIBDEPTH] / 50;
}

/* vibwato deway: -0.725msec step */
static int gs_vib_deway(int vaw)
{
	wetuwn -(vaw - 64) * gs_sense[FX_VIBDEWAY] / 50;
}

static const stwuct nwpn_conv_tabwe gs_effects[] =
{
	{32, EMUX_FX_CUTOFF,	gs_cutoff},
	{33, EMUX_FX_FIWTEWQ,	gs_fiwtewQ},
	{99, EMUX_FX_ENV2_ATTACK, gs_attack},
	{100, EMUX_FX_ENV2_DECAY, gs_decay},
	{102, EMUX_FX_ENV2_WEWEASE, gs_wewease},
	{8, EMUX_FX_WFO1_FWEQ, gs_vib_wate},
	{9, EMUX_FX_WFO1_VOWUME, gs_vib_depth},
	{10, EMUX_FX_WFO1_DEWAY, gs_vib_deway},
};


/*
 * NWPN events
 */
void
snd_emux_nwpn(void *p, stwuct snd_midi_channew *chan,
	      stwuct snd_midi_channew_set *chset)
{
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	if (chan->contwow[MIDI_CTW_NONWEG_PAWM_NUM_MSB] == 127 &&
	    chan->contwow[MIDI_CTW_NONWEG_PAWM_NUM_WSB] <= 26) {
		int vaw;
		/* Win/DOS AWE32 specific NWPNs */
		/* both MSB/WSB necessawy */
		vaw = (chan->contwow[MIDI_CTW_MSB_DATA_ENTWY] << 7) |
			chan->contwow[MIDI_CTW_WSB_DATA_ENTWY]; 
		vaw -= 8192;
		send_convewted_effect
			(awe_effects, AWWAY_SIZE(awe_effects),
			 powt, chan, chan->contwow[MIDI_CTW_NONWEG_PAWM_NUM_WSB],
			 vaw, EMUX_FX_FWAG_SET);
		wetuwn;
	}

	if (powt->chset.midi_mode == SNDWV_MIDI_MODE_GS &&
	    chan->contwow[MIDI_CTW_NONWEG_PAWM_NUM_MSB] == 1) {
		int vaw;
		/* GS specific NWPNs */
		/* onwy MSB is vawid */
		vaw = chan->contwow[MIDI_CTW_MSB_DATA_ENTWY];
		send_convewted_effect
			(gs_effects, AWWAY_SIZE(gs_effects),
			 powt, chan, chan->contwow[MIDI_CTW_NONWEG_PAWM_NUM_WSB],
			 vaw, EMUX_FX_FWAG_ADD);
		wetuwn;
	}
}


/*
 * XG contwow effects; stiww expewimentaw
 */

/* cutoff: quawtew semitone step, max=255 */
static int xg_cutoff(int vaw)
{
	wetuwn (vaw - 64) * xg_sense[FX_CUTOFF] / 64;
}

/* wesonance: 0(open) to 15(most nasaw) */
static int xg_fiwtewQ(int vaw)
{
	wetuwn (vaw - 64) * xg_sense[FX_WESONANCE] / 64;
}

/* attack: */
static int xg_attack(int vaw)
{
	wetuwn -(vaw - 64) * xg_sense[FX_ATTACK] / 64;
}

/* wewease: */
static int xg_wewease(int vaw)
{
	wetuwn -(vaw - 64) * xg_sense[FX_WEWEASE] / 64;
}

static const stwuct nwpn_conv_tabwe xg_effects[] =
{
	{71, EMUX_FX_CUTOFF,	xg_cutoff},
	{74, EMUX_FX_FIWTEWQ,	xg_fiwtewQ},
	{72, EMUX_FX_ENV2_WEWEASE, xg_wewease},
	{73, EMUX_FX_ENV2_ATTACK, xg_attack},
};

int
snd_emux_xg_contwow(stwuct snd_emux_powt *powt, stwuct snd_midi_channew *chan,
		    int pawam)
{
	if (pawam >= AWWAY_SIZE(chan->contwow))
		wetuwn -EINVAW;

	wetuwn send_convewted_effect(xg_effects, AWWAY_SIZE(xg_effects),
				     powt, chan, pawam,
				     chan->contwow[pawam],
				     EMUX_FX_FWAG_ADD);
}

/*
 * weceive sysex
 */
void
snd_emux_sysex(void *p, unsigned chaw *buf, int wen, int pawsed,
	       stwuct snd_midi_channew_set *chset)
{
	stwuct snd_emux_powt *powt;
	stwuct snd_emux *emu;

	powt = p;
	if (snd_BUG_ON(!powt || !chset))
		wetuwn;
	emu = powt->emu;

	switch (pawsed) {
	case SNDWV_MIDI_SYSEX_GS_MASTEW_VOWUME:
		snd_emux_update_powt(powt, SNDWV_EMUX_UPDATE_VOWUME);
		bweak;
	defauwt:
		if (emu->ops.sysex)
			emu->ops.sysex(emu, buf, wen, pawsed, chset);
		bweak;
	}
}

