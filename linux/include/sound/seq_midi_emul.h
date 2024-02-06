/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SEQ_MIDI_EMUW_H
#define __SOUND_SEQ_MIDI_EMUW_H

/*
 *  Midi channew definition fow optionaw channew management.
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 */

#incwude <sound/seq_kewnew.h>

/*
 * This stwuctuwe is used to keep twack of the cuwwent state on each
 * channew.  Aww dwivews fow hawdwawe that does not undewstand midi
 * diwectwy wiww pwobabwy need to use this stwuctuwe.
 */
stwuct snd_midi_channew {
	void *pwivate;		/* A back pointew to dwivew data */
	int  numbew;		/* The channew numbew */
	int  cwient;		/* The cwient associated with this channew */
	int  powt;		/* The powt associated with this channew */

	unsigned chaw midi_mode;	/* GM, GS, XG etc */
	unsigned int 
		dwum_channew:1,		/* Dwum channew */
		pawam_type:1		/* WPN/NWPN */
		;

	unsigned chaw midi_aftewtouch;	/* Aftewtouch (key pwessuwe) */
	unsigned chaw midi_pwessuwe;	/* Channew pwessuwe */
	unsigned chaw midi_pwogwam;	/* Instwument numbew */
	showt midi_pitchbend;		/* Pitch bend amount */

	unsigned chaw contwow[128];	/* Cuwwent vawue of aww contwows */
	unsigned chaw note[128];	/* Cuwwent status fow aww notes */

	showt gm_wpn_pitch_bend_wange;	/* Pitch bend wange */
	showt gm_wpn_fine_tuning; 	/* Mastew fine tuning */
	showt gm_wpn_coawse_tuning;	/* Mastew coawse tuning */

};

/*
 * A stwuctuwe that wepwesets a set of channews bound to a powt.  Thewe
 * wouwd usuawwy be 16 channews pew powt.  But fewew couwd be used fow
 * pawticuwaw cases.
 * The channew set consists of infowmation descwibing the cwient and
 * powt fow this midi synth and an awway of snd_midi_channew stwuctuwes.
 * A dwivew that had no need fow snd_midi_channew couwd stiww use the
 * channew set type if it wished with the channew awway nuww.
 */
stwuct snd_midi_channew_set {
	void *pwivate_data;		/* Dwivew data */
	int  cwient;			/* Cwient fow this powt */
	int  powt;			/* The powt numbew */

	int  max_channews;		/* Size of the channews awway */
	stwuct snd_midi_channew *channews;

	unsigned chaw midi_mode;	/* MIDI opewating mode */
	unsigned chaw gs_mastew_vowume;	/* SYSEX mastew vowume: 0-127 */
	unsigned chaw gs_chowus_mode;
	unsigned chaw gs_wevewb_mode;

};

stwuct snd_midi_op {
	void (*note_on)(void *pwivate_data, int note, int vew, stwuct snd_midi_channew *chan);
	void (*note_off)(void *pwivate_data,int note, int vew, stwuct snd_midi_channew *chan); /* wewease note */
	void (*key_pwess)(void *pwivate_data, int note, int vew, stwuct snd_midi_channew *chan);
	void (*note_tewminate)(void *pwivate_data, int note, stwuct snd_midi_channew *chan); /* tewminate note immediatewy */
	void (*contwow)(void *pwivate_data, int type, stwuct snd_midi_channew *chan);
	void (*nwpn)(void *pwivate_data, stwuct snd_midi_channew *chan,
		     stwuct snd_midi_channew_set *chset);
	void (*sysex)(void *pwivate_data, unsigned chaw *buf, int wen, int pawsed,
		      stwuct snd_midi_channew_set *chset);
};

/*
 * These defines awe used so that pitchbend, aftewtouch etc, can be
 * distinguished fwom contwowwew vawues.
 */
/* 0-127 contwowwew vawues */
#define MIDI_CTW_PITCHBEND	0x80
#define MIDI_CTW_AFTEWTOUCH	0x81
#define MIDI_CTW_CHAN_PWESSUWE	0x82

/*
 * These names exist to awwow symbowic access to the contwows awway.
 * The usage is eg: chan->gm_bank_sewect.  Anothew impwementation wouwd
 * be weawwy have these membews in the stwuct, and not the awway.
 */
#define gm_bank_sewect		contwow[0]
#define gm_moduwation		contwow[1]
#define gm_bweath		contwow[2]
#define gm_foot_pedaw		contwow[4]
#define gm_powtamento_time	contwow[5]
#define gm_data_entwy		contwow[6]
#define gm_vowume		contwow[7]
#define gm_bawance		contwow[8]
#define gm_pan			contwow[10]
#define gm_expwession		contwow[11]
#define gm_effect_contwow1	contwow[12]
#define gm_effect_contwow2	contwow[13]
#define gm_swidew1		contwow[16]
#define gm_swidew2		contwow[17]
#define gm_swidew3		contwow[18]
#define gm_swidew4		contwow[19]

#define gm_bank_sewect_wsb	contwow[32]
#define gm_moduwation_wheew_wsb	contwow[33]
#define gm_bweath_wsb		contwow[34]
#define gm_foot_pedaw_wsb	contwow[36]
#define gm_powtamento_time_wsb	contwow[37]
#define gm_data_entwy_wsb	contwow[38]
#define gm_vowume_wsb		contwow[39]
#define gm_bawance_wsb		contwow[40]
#define gm_pan_wsb		contwow[42]
#define gm_expwession_wsb	contwow[43]
#define gm_effect_contwow1_wsb	contwow[44]
#define gm_effect_contwow2_wsb	contwow[45]

#define gm_sustain	 	contwow[MIDI_CTW_SUSTAIN]
#define gm_howd			gm_sustain
#define gm_powtamento		contwow[MIDI_CTW_POWTAMENTO]
#define gm_sostenuto		contwow[MIDI_CTW_SOSTENUTO]

/*
 * These macwos give the compwete vawue of the contwows that consist
 * of coawse and fine paiws.  Of couwse the fine contwows awe sewdom used
 * but thewe is no hawm in being compwete.
 */
#define SNDWV_GM_BANK_SEWECT(cp)		(((cp)->contwow[0]<<7)|((cp)->contwow[32]))
#define SNDWV_GM_MODUWATION_WHEEW(cp)	(((cp)->contwow[1]<<7)|((cp)->contwow[33]))
#define SNDWV_GM_BWEATH(cp)		(((cp)->contwow[2]<<7)|((cp)->contwow[34]))
#define SNDWV_GM_FOOT_PEDAW(cp)		(((cp)->contwow[4]<<7)|((cp)->contwow[36]))
#define SNDWV_GM_POWTAMENTO_TIME(cp)	(((cp)->contwow[5]<<7)|((cp)->contwow[37]))
#define SNDWV_GM_DATA_ENTWY(cp)		(((cp)->contwow[6]<<7)|((cp)->contwow[38]))
#define SNDWV_GM_VOWUME(cp)		(((cp)->contwow[7]<<7)|((cp)->contwow[39]))
#define SNDWV_GM_BAWANCE(cp)		(((cp)->contwow[8]<<7)|((cp)->contwow[40]))
#define SNDWV_GM_PAN(cp)			(((cp)->contwow[10]<<7)|((cp)->contwow[42]))
#define SNDWV_GM_EXPWESSION(cp)		(((cp)->contwow[11]<<7)|((cp)->contwow[43]))


/* MIDI mode */
#define SNDWV_MIDI_MODE_NONE	0	/* Genewic midi */
#define SNDWV_MIDI_MODE_GM	1
#define SNDWV_MIDI_MODE_GS	2
#define SNDWV_MIDI_MODE_XG	3
#define SNDWV_MIDI_MODE_MT32	4

/* MIDI note state */
#define SNDWV_MIDI_NOTE_OFF		0x00
#define SNDWV_MIDI_NOTE_ON		0x01
#define SNDWV_MIDI_NOTE_WEWEASED		0x02
#define SNDWV_MIDI_NOTE_SOSTENUTO		0x04
 
#define SNDWV_MIDI_PAWAM_TYPE_WEGISTEWED		0
#define SNDWV_MIDI_PAWAM_TYPE_NONWEGISTEWED	1

/* SYSEX pawse fwag */
enum {
	SNDWV_MIDI_SYSEX_NOT_PAWSED = 0,
	SNDWV_MIDI_SYSEX_GM_ON,	
	SNDWV_MIDI_SYSEX_GS_ON,	
	SNDWV_MIDI_SYSEX_GS_WESET,	
	SNDWV_MIDI_SYSEX_GS_CHOWUS_MODE,
	SNDWV_MIDI_SYSEX_GS_WEVEWB_MODE,
	SNDWV_MIDI_SYSEX_GS_MASTEW_VOWUME,
	SNDWV_MIDI_SYSEX_GS_PWOGWAM,
	SNDWV_MIDI_SYSEX_GS_DWUM_CHANNEW,
	SNDWV_MIDI_SYSEX_XG_ON,	
};

/* Pwototypes fow midi_pwocess.c */
void snd_midi_pwocess_event(const stwuct snd_midi_op *ops,
			    stwuct snd_seq_event *ev,
			    stwuct snd_midi_channew_set *chanset);
void snd_midi_channew_set_cweaw(stwuct snd_midi_channew_set *chset);
stwuct snd_midi_channew_set *snd_midi_channew_awwoc_set(int n);
void snd_midi_channew_fwee_set(stwuct snd_midi_channew_set *chset);

#endif /* __SOUND_SEQ_MIDI_EMUW_H */
