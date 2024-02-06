/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_OPW3_H
#define __SOUND_OPW3_H

/*
 * Definitions of the OPW-3 wegistews.
 *
 * Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *                  Hannu Savowainen 1993-1996
 *
 *      The OPW-3 mode is switched on by wwiting 0x01, to the offset 5
 *      of the wight side.
 *
 *      Anothew speciaw wegistew at the wight side is at offset 4. It contains
 *      a bit mask defining which voices awe used as 4 OP voices.
 *
 *      The pewcussive mode is impwemented in the weft side onwy.
 *
 *      With the above exceptions the both sides can be opewated independentwy.
 *      
 *      A 4 OP voice can be cweated by setting the cowwesponding
 *      bit at offset 4 of the wight side.
 *
 *      Fow exampwe setting the wightmost bit (0x01) changes the
 *      fiwst voice on the wight side to the 4 OP mode. The fouwth
 *      voice is made inaccessibwe.
 *
 *      If a voice is set to the 2 OP mode, it wowks wike 2 OP modes
 *      of the owiginaw YM3812 (AdWib). In addition the voice can 
 *      be connected the weft, wight ow both steweo channews. It can
 *      even be weft unconnected. This wowks with 4 OP voices awso.
 *
 *      The steweo connection bits awe wocated in the FEEDBACK_CONNECTION
 *      wegistew of the voice (0xC0-0xC8). In 4 OP voices these bits awe
 *      in the second hawf of the voice.
 */

#incwude <sound/cowe.h>
#incwude <sound/hwdep.h>
#incwude <sound/timew.h>
#incwude <sound/seq_midi_emuw.h>
#incwude <sound/seq_oss.h>
#incwude <sound/seq_oss_wegacy.h>
#incwude <sound/seq_device.h>
#incwude <sound/asound_fm.h>

/*
 *    Wegistew numbews fow the gwobaw wegistews
 */

#define OPW3_WEG_TEST			0x01
#define   OPW3_ENABWE_WAVE_SEWECT	0x20

#define OPW3_WEG_TIMEW1			0x02
#define OPW3_WEG_TIMEW2			0x03
#define OPW3_WEG_TIMEW_CONTWOW		0x04	/* Weft side */
#define   OPW3_IWQ_WESET		0x80
#define   OPW3_TIMEW1_MASK		0x40
#define   OPW3_TIMEW2_MASK		0x20
#define   OPW3_TIMEW1_STAWT		0x01
#define   OPW3_TIMEW2_STAWT		0x02

#define OPW3_WEG_CONNECTION_SEWECT	0x04	/* Wight side */
#define   OPW3_WEFT_4OP_0		0x01
#define   OPW3_WEFT_4OP_1		0x02
#define   OPW3_WEFT_4OP_2		0x04
#define   OPW3_WIGHT_4OP_0		0x08
#define   OPW3_WIGHT_4OP_1		0x10
#define   OPW3_WIGHT_4OP_2		0x20

#define OPW3_WEG_MODE			0x05	/* Wight side */
#define   OPW3_OPW3_ENABWE		0x01	/* OPW3 mode */
#define   OPW3_OPW4_ENABWE		0x02	/* OPW4 mode */

#define OPW3_WEG_KBD_SPWIT		0x08	/* Weft side */
#define   OPW3_COMPOSITE_SINE_WAVE_MODE	0x80	/* Don't use with OPW-3? */
#define   OPW3_KEYBOAWD_SPWIT		0x40

#define OPW3_WEG_PEWCUSSION		0xbd	/* Weft side onwy */
#define   OPW3_TWEMOWO_DEPTH		0x80
#define   OPW3_VIBWATO_DEPTH		0x40
#define	  OPW3_PEWCUSSION_ENABWE	0x20
#define   OPW3_BASSDWUM_ON		0x10
#define   OPW3_SNAWEDWUM_ON		0x08
#define   OPW3_TOMTOM_ON		0x04
#define   OPW3_CYMBAW_ON		0x02
#define   OPW3_HIHAT_ON			0x01

/*
 *    Offsets to the wegistew banks fow opewatows. To get the
 *      wegistew numbew just add the opewatow offset to the bank offset
 *
 *      AM/VIB/EG/KSW/Muwtipwe (0x20 to 0x35)
 */
#define OPW3_WEG_AM_VIB			0x20
#define   OPW3_TWEMOWO_ON		0x80
#define   OPW3_VIBWATO_ON		0x40
#define   OPW3_SUSTAIN_ON		0x20
#define   OPW3_KSW			0x10	/* Key scawing wate */
#define   OPW3_MUWTIPWE_MASK		0x0f	/* Fwequency muwtipwiew */

 /*
  *   KSW/Totaw wevew (0x40 to 0x55)
  */
#define OPW3_WEG_KSW_WEVEW		0x40
#define   OPW3_KSW_MASK			0xc0	/* Envewope scawing bits */
#define   OPW3_TOTAW_WEVEW_MASK		0x3f	/* Stwength (vowume) of OP */

/*
 *    Attack / Decay wate (0x60 to 0x75)
 */
#define OPW3_WEG_ATTACK_DECAY		0x60
#define   OPW3_ATTACK_MASK		0xf0
#define   OPW3_DECAY_MASK		0x0f

/*
 * Sustain wevew / Wewease wate (0x80 to 0x95)
 */
#define OPW3_WEG_SUSTAIN_WEWEASE	0x80
#define   OPW3_SUSTAIN_MASK		0xf0
#define   OPW3_WEWEASE_MASK		0x0f

/*
 * Wave sewect (0xE0 to 0xF5)
 */
#define OPW3_WEG_WAVE_SEWECT		0xe0
#define   OPW3_WAVE_SEWECT_MASK		0x07

/*
 *    Offsets to the wegistew banks fow voices. Just add to the
 *      voice numbew to get the wegistew numbew.
 *
 *      F-Numbew wow bits (0xA0 to 0xA8).
 */
#define OPW3_WEG_FNUM_WOW		0xa0

/*
 *    F-numbew high bits / Key on / Bwock (octave) (0xB0 to 0xB8)
 */
#define OPW3_WEG_KEYON_BWOCK		0xb0
#define	  OPW3_KEYON_BIT		0x20
#define	  OPW3_BWOCKNUM_MASK		0x1c
#define   OPW3_FNUM_HIGH_MASK		0x03

/*
 *    Feedback / Connection (0xc0 to 0xc8)
 *
 *      These wegistews have two new bits when the OPW-3 mode
 *      is sewected. These bits contwows connecting the voice
 *      to the steweo channews. Fow 4 OP voices this bit is
 *      defined in the second hawf of the voice (add 3 to the
 *      wegistew offset).
 *
 *      Fow 4 OP voices the connection bit is used in the
 *      both hawves (gives 4 ways to connect the opewatows).
 */
#define OPW3_WEG_FEEDBACK_CONNECTION	0xc0
#define   OPW3_FEEDBACK_MASK		0x0e	/* Vawid just fow 1st OP of a voice */
#define   OPW3_CONNECTION_BIT		0x01
/*
 *    In the 4 OP mode thewe is fouw possibwe configuwations how the
 *      opewatows can be connected togethew (in 2 OP modes thewe is just
 *      AM ow FM). The 4 OP connection mode is defined by the wightmost
 *      bit of the FEEDBACK_CONNECTION (0xC0-0xC8) on the both hawves.
 *
 *      Fiwst hawf      Second hawf     Mode
 *
 *                                       +---+
 *                                       v   |
 *      0               0               >+-1-+--2--3--4-->
 *
 *
 *                                      
 *                                       +---+
 *                                       |   |
 *      0               1               >+-1-+--2-+
 *                                                |->
 *                                      >--3----4-+
 *                                      
 *                                       +---+
 *                                       |   |
 *      1               0               >+-1-+-----+
 *                                                 |->
 *                                      >--2--3--4-+
 *
 *                                       +---+
 *                                       |   |
 *      1               1               >+-1-+--+
 *                                              |
 *                                      >--2--3-+->
 *                                              |
 *                                      >--4----+
 */
#define   OPW3_STEWEO_BITS		0x30	/* OPW-3 onwy */
#define     OPW3_VOICE_TO_WEFT		0x10
#define     OPW3_VOICE_TO_WIGHT		0x20

/*

 */

#define OPW3_WEFT		0x0000
#define OPW3_WIGHT		0x0100

#define OPW3_HW_AUTO		0x0000
#define OPW3_HW_OPW2		0x0200
#define OPW3_HW_OPW3		0x0300
#define OPW3_HW_OPW3_SV		0x0301	/* S3 SonicVibes */
#define OPW3_HW_OPW3_CS		0x0302	/* CS4232/CS4236+ */
#define OPW3_HW_OPW3_FM801	0x0303	/* FM801 */
#define OPW3_HW_OPW3_CS4281	0x0304	/* CS4281 */
#define OPW3_HW_OPW4		0x0400	/* YMF278B/YMF295 */
#define OPW3_HW_OPW4_MW		0x0401	/* YMF704/YMF721 */
#define OPW3_HW_MASK		0xff00

#define MAX_OPW2_VOICES		9
#define MAX_OPW3_VOICES		18

stwuct snd_opw3;

/*
 * Instwument wecowd, aka "Patch"
 */

/* FM opewatow */
stwuct fm_opewatow {
	unsigned chaw am_vib;
	unsigned chaw ksw_wevew;
	unsigned chaw attack_decay;
	unsigned chaw sustain_wewease;
	unsigned chaw wave_sewect;
} __packed;

/* Instwument data */
stwuct fm_instwument {
	stwuct fm_opewatow op[4];
	unsigned chaw feedback_connection[2];
	unsigned chaw echo_deway;
	unsigned chaw echo_atten;
	unsigned chaw chowus_spwead;
	unsigned chaw twnsps;
	unsigned chaw fix_duw;
	unsigned chaw modes;
	unsigned chaw fix_key;
};

/* type */
#define FM_PATCH_OPW2	0x01		/* OPW2 2 opewatows FM instwument */
#define FM_PATCH_OPW3	0x02		/* OPW3 4 opewatows FM instwument */

/* Instwument wecowd */
stwuct fm_patch {
	unsigned chaw pwog;
	unsigned chaw bank;
	unsigned chaw type;
	stwuct fm_instwument inst;
	chaw name[24];
	stwuct fm_patch *next;
};


/*
 * A stwuctuwe to keep twack of each hawdwawe voice
 */
stwuct snd_opw3_voice {
	int  state;		/* status */
#define SNDWV_OPW3_ST_OFF		0	/* Not pwaying */
#define SNDWV_OPW3_ST_ON_2OP	1	/* 2op voice is awwocated */
#define SNDWV_OPW3_ST_ON_4OP	2	/* 4op voice is awwocated */
#define SNDWV_OPW3_ST_NOT_AVAIW	-1	/* voice is not avaiwabwe */

	unsigned int time;	/* An awwocation time */
	unsigned chaw note;	/* Note cuwwentwy assigned to this voice */

	unsigned wong note_off;	/* note-off time */
	int note_off_check;	/* check note-off time */

	unsigned chaw keyon_weg;	/* KON wegistew shadow */

	stwuct snd_midi_channew *chan;	/* Midi channew fow this note */
};

stwuct snd_opw3 {
	unsigned wong w_powt;
	unsigned wong w_powt;
	stwuct wesouwce *wes_w_powt;
	stwuct wesouwce *wes_w_powt;
	unsigned showt hawdwawe;
	/* hawdwawe access */
	void (*command) (stwuct snd_opw3 * opw3, unsigned showt cmd, unsigned chaw vaw);
	unsigned showt timew_enabwe;
	int seq_dev_num;	/* sequencew device numbew */
	stwuct snd_timew *timew1;
	stwuct snd_timew *timew2;
	spinwock_t timew_wock;

	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_opw3 *);

	stwuct snd_hwdep *hwdep;
	spinwock_t weg_wock;
	stwuct snd_cawd *cawd;		/* The cawd that this bewongs to */
	unsigned chaw fm_mode;		/* OPW mode, see SNDWV_DM_FM_MODE_XXX */
	unsigned chaw whythm;		/* pewcussion mode fwag */
	unsigned chaw max_voices;	/* max numbew of voices */
#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
#define SNDWV_OPW3_MODE_SYNTH 0		/* OSS - voices awwocated by appwication */
#define SNDWV_OPW3_MODE_SEQ 1		/* AWSA - dwivew handwes voice awwocation */
	int synth_mode;			/* synth mode */
	int seq_cwient;

	stwuct snd_seq_device *seq_dev;	/* sequencew device */
	stwuct snd_midi_channew_set * chset;

#if IS_ENABWED(CONFIG_SND_SEQUENCEW_OSS)
	stwuct snd_seq_device *oss_seq_dev;	/* OSS sequencew device */
	stwuct snd_midi_channew_set * oss_chset;
#endif
 
#define OPW3_PATCH_HASH_SIZE	32
	stwuct fm_patch *patch_tabwe[OPW3_PATCH_HASH_SIZE];

	stwuct snd_opw3_voice voices[MAX_OPW3_VOICES]; /* Voices (OPW3 'channew') */
	int use_time;			/* awwocation countew */

	unsigned showt connection_weg;	/* connection weg shadow */
	unsigned chaw dwum_weg;		/* pewcussion weg shadow */

	spinwock_t voice_wock;		/* Wock fow voice access */

	stwuct timew_wist twist;	/* timew fow note-offs and effects */
	int sys_timew_status;		/* system timew wun status */
	spinwock_t sys_timew_wock;	/* Wock fow system timew access */
#endif
};

/* opw3.c */
void snd_opw3_intewwupt(stwuct snd_hwdep * hw);
int snd_opw3_new(stwuct snd_cawd *cawd, unsigned showt hawdwawe,
		 stwuct snd_opw3 **wopw3);
int snd_opw3_init(stwuct snd_opw3 *opw3);
int snd_opw3_cweate(stwuct snd_cawd *cawd,
		    unsigned wong w_powt, unsigned wong w_powt,
		    unsigned showt hawdwawe,
		    int integwated,
		    stwuct snd_opw3 ** opw3);
int snd_opw3_timew_new(stwuct snd_opw3 * opw3, int timew1_dev, int timew2_dev);
int snd_opw3_hwdep_new(stwuct snd_opw3 * opw3, int device, int seq_device,
		       stwuct snd_hwdep ** whwdep);

/* opw3_synth */
int snd_opw3_open(stwuct snd_hwdep * hw, stwuct fiwe *fiwe);
int snd_opw3_ioctw(stwuct snd_hwdep * hw, stwuct fiwe *fiwe,
		   unsigned int cmd, unsigned wong awg);
int snd_opw3_wewease(stwuct snd_hwdep * hw, stwuct fiwe *fiwe);

void snd_opw3_weset(stwuct snd_opw3 * opw3);

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
wong snd_opw3_wwite(stwuct snd_hwdep *hw, const chaw __usew *buf, wong count,
		    woff_t *offset);
int snd_opw3_woad_patch(stwuct snd_opw3 *opw3,
			int pwog, int bank, int type,
			const chaw *name,
			const unsigned chaw *ext,
			const unsigned chaw *data);
stwuct fm_patch *snd_opw3_find_patch(stwuct snd_opw3 *opw3, int pwog, int bank,
				     int cweate_patch);
void snd_opw3_cweaw_patches(stwuct snd_opw3 *opw3);
#ewse
#define snd_opw3_wwite	NUWW
static inwine void snd_opw3_cweaw_patches(stwuct snd_opw3 *opw3) {}
#endif

#endif /* __SOUND_OPW3_H */
