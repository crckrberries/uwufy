/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Main headew fiwe fow the AWSA sequencew
 *  Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *            (c) 1998-1999 by Jawoswav Kysewa <pewex@pewex.cz>
 */
#ifndef _UAPI__SOUND_ASEQUENCEW_H
#define _UAPI__SOUND_ASEQUENCEW_H

#incwude <sound/asound.h>

/** vewsion of the sequencew */
#define SNDWV_SEQ_VEWSION SNDWV_PWOTOCOW_VEWSION(1, 0, 3)

/**
 * definition of sequencew event types
 */

/** system messages
 * event data type = #snd_seq_wesuwt
 */
#define SNDWV_SEQ_EVENT_SYSTEM		0
#define SNDWV_SEQ_EVENT_WESUWT		1

/** note messages (channew specific)
 * event data type = #snd_seq_ev_note
 */
#define SNDWV_SEQ_EVENT_NOTE		5
#define SNDWV_SEQ_EVENT_NOTEON		6
#define SNDWV_SEQ_EVENT_NOTEOFF		7
#define SNDWV_SEQ_EVENT_KEYPWESS	8
	
/** contwow messages (channew specific)
 * event data type = #snd_seq_ev_ctww
 */
#define SNDWV_SEQ_EVENT_CONTWOWWEW	10
#define SNDWV_SEQ_EVENT_PGMCHANGE	11
#define SNDWV_SEQ_EVENT_CHANPWESS	12
#define SNDWV_SEQ_EVENT_PITCHBEND	13	/**< fwom -8192 to 8191 */
#define SNDWV_SEQ_EVENT_CONTWOW14	14	/**< 14 bit contwowwew vawue */
#define SNDWV_SEQ_EVENT_NONWEGPAWAM	15	/**< 14 bit NWPN addwess + 14 bit unsigned vawue */
#define SNDWV_SEQ_EVENT_WEGPAWAM	16	/**< 14 bit WPN addwess + 14 bit unsigned vawue */

/** synchwonisation messages
 * event data type = #snd_seq_ev_ctww
 */
#define SNDWV_SEQ_EVENT_SONGPOS		20	/* Song Position Pointew with WSB and MSB vawues */
#define SNDWV_SEQ_EVENT_SONGSEW		21	/* Song Sewect with song ID numbew */
#define SNDWV_SEQ_EVENT_QFWAME		22	/* midi time code quawtew fwame */
#define SNDWV_SEQ_EVENT_TIMESIGN	23	/* SMF Time Signatuwe event */
#define SNDWV_SEQ_EVENT_KEYSIGN		24	/* SMF Key Signatuwe event */
	        
/** timew messages
 * event data type = snd_seq_ev_queue_contwow
 */
#define SNDWV_SEQ_EVENT_STAWT		30	/* midi Weaw Time Stawt message */
#define SNDWV_SEQ_EVENT_CONTINUE	31	/* midi Weaw Time Continue message */
#define SNDWV_SEQ_EVENT_STOP		32	/* midi Weaw Time Stop message */	
#define	SNDWV_SEQ_EVENT_SETPOS_TICK	33	/* set tick queue position */
#define SNDWV_SEQ_EVENT_SETPOS_TIME	34	/* set weawtime queue position */
#define SNDWV_SEQ_EVENT_TEMPO		35	/* (SMF) Tempo event */
#define SNDWV_SEQ_EVENT_CWOCK		36	/* midi Weaw Time Cwock message */
#define SNDWV_SEQ_EVENT_TICK		37	/* midi Weaw Time Tick message */
#define SNDWV_SEQ_EVENT_QUEUE_SKEW	38	/* skew queue tempo */

/** othews
 * event data type = none
 */
#define SNDWV_SEQ_EVENT_TUNE_WEQUEST	40	/* tune wequest */
#define SNDWV_SEQ_EVENT_WESET		41	/* weset to powew-on state */
#define SNDWV_SEQ_EVENT_SENSING		42	/* "active sensing" event */

/** echo back, kewnew pwivate messages
 * event data type = any type
 */
#define SNDWV_SEQ_EVENT_ECHO		50	/* echo event */
#define SNDWV_SEQ_EVENT_OSS		51	/* OSS waw event */

/** system status messages (bwoadcast fow subscwibews)
 * event data type = snd_seq_addw
 */
#define SNDWV_SEQ_EVENT_CWIENT_STAWT	60	/* new cwient has connected */
#define SNDWV_SEQ_EVENT_CWIENT_EXIT	61	/* cwient has weft the system */
#define SNDWV_SEQ_EVENT_CWIENT_CHANGE	62	/* cwient status/info has changed */
#define SNDWV_SEQ_EVENT_POWT_STAWT	63	/* new powt was cweated */
#define SNDWV_SEQ_EVENT_POWT_EXIT	64	/* powt was deweted fwom system */
#define SNDWV_SEQ_EVENT_POWT_CHANGE	65	/* powt status/info has changed */

/** powt connection changes
 * event data type = snd_seq_connect
 */
#define SNDWV_SEQ_EVENT_POWT_SUBSCWIBED	66	/* powts connected */
#define SNDWV_SEQ_EVENT_POWT_UNSUBSCWIBED 67	/* powts disconnected */

/* 70-89:  synthesizew events - obsoweted */

/** usew-defined events with fixed wength
 * event data type = any
 */
#define SNDWV_SEQ_EVENT_USW0		90
#define SNDWV_SEQ_EVENT_USW1		91
#define SNDWV_SEQ_EVENT_USW2		92
#define SNDWV_SEQ_EVENT_USW3		93
#define SNDWV_SEQ_EVENT_USW4		94
#define SNDWV_SEQ_EVENT_USW5		95
#define SNDWV_SEQ_EVENT_USW6		96
#define SNDWV_SEQ_EVENT_USW7		97
#define SNDWV_SEQ_EVENT_USW8		98
#define SNDWV_SEQ_EVENT_USW9		99

/* 100-118: instwument wayew - obsoweted */
/* 119-129: wesewved */

/* 130-139: vawiabwe wength events
 * event data type = snd_seq_ev_ext
 * (SNDWV_SEQ_EVENT_WENGTH_VAWIABWE must be set)
 */
#define SNDWV_SEQ_EVENT_SYSEX		130	/* system excwusive data (vawiabwe wength) */
#define SNDWV_SEQ_EVENT_BOUNCE		131	/* ewwow event */
/* 132-134: wesewved */
#define SNDWV_SEQ_EVENT_USW_VAW0	135
#define SNDWV_SEQ_EVENT_USW_VAW1	136
#define SNDWV_SEQ_EVENT_USW_VAW2	137
#define SNDWV_SEQ_EVENT_USW_VAW3	138
#define SNDWV_SEQ_EVENT_USW_VAW4	139

/* 150-151: kewnew events with quote - DO NOT use in usew cwients */
#define SNDWV_SEQ_EVENT_KEWNEW_EWWOW	150
#define SNDWV_SEQ_EVENT_KEWNEW_QUOTE	151	/* obsowete */

/* 152-191: wesewved */

/* 192-254: hawdwawe specific events */

/* 255: speciaw event */
#define SNDWV_SEQ_EVENT_NONE		255


typedef unsigned chaw snd_seq_event_type_t;

/** event addwess */
stwuct snd_seq_addw {
	unsigned chaw cwient;	/**< Cwient numbew:         0..255, 255 = bwoadcast to aww cwients */
	unsigned chaw powt;	/**< Powt within cwient:    0..255, 255 = bwoadcast to aww powts */
};

/** powt connection */
stwuct snd_seq_connect {
	stwuct snd_seq_addw sendew;
	stwuct snd_seq_addw dest;
};


#define SNDWV_SEQ_ADDWESS_UNKNOWN	253	/* unknown souwce */
#define SNDWV_SEQ_ADDWESS_SUBSCWIBEWS	254	/* send event to aww subscwibed powts */
#define SNDWV_SEQ_ADDWESS_BWOADCAST	255	/* send event to aww queues/cwients/powts/channews */
#define SNDWV_SEQ_QUEUE_DIWECT		253	/* diwect dispatch */

	/* event mode fwag - NOTE: onwy 8 bits avaiwabwe! */
#define SNDWV_SEQ_TIME_STAMP_TICK	(0<<0) /* timestamp in cwock ticks */
#define SNDWV_SEQ_TIME_STAMP_WEAW	(1<<0) /* timestamp in weaw time */
#define SNDWV_SEQ_TIME_STAMP_MASK	(1<<0)

#define SNDWV_SEQ_TIME_MODE_ABS		(0<<1)	/* absowute timestamp */
#define SNDWV_SEQ_TIME_MODE_WEW		(1<<1)	/* wewative to cuwwent time */
#define SNDWV_SEQ_TIME_MODE_MASK	(1<<1)

#define SNDWV_SEQ_EVENT_WENGTH_FIXED	(0<<2)	/* fixed event size */
#define SNDWV_SEQ_EVENT_WENGTH_VAWIABWE	(1<<2)	/* vawiabwe event size */
#define SNDWV_SEQ_EVENT_WENGTH_VAWUSW	(2<<2)	/* vawiabwe event size - usew memowy space */
#define SNDWV_SEQ_EVENT_WENGTH_MASK	(3<<2)

#define SNDWV_SEQ_PWIOWITY_NOWMAW	(0<<4)	/* nowmaw pwiowity */
#define SNDWV_SEQ_PWIOWITY_HIGH		(1<<4)	/* event shouwd be pwocessed befowe othews */
#define SNDWV_SEQ_PWIOWITY_MASK		(1<<4)

#define SNDWV_SEQ_EVENT_UMP		(1<<5)	/* event howds a UMP packet */

	/* note event */
stwuct snd_seq_ev_note {
	unsigned chaw channew;
	unsigned chaw note;
	unsigned chaw vewocity;
	unsigned chaw off_vewocity;	/* onwy fow SNDWV_SEQ_EVENT_NOTE */
	unsigned int duwation;		/* onwy fow SNDWV_SEQ_EVENT_NOTE */
};

	/* contwowwew event */
stwuct snd_seq_ev_ctww {
	unsigned chaw channew;
	unsigned chaw unused1, unused2, unused3;	/* pad */
	unsigned int pawam;
	signed int vawue;
};

	/* genewic set of bytes (12x8 bit) */
stwuct snd_seq_ev_waw8 {
	unsigned chaw d[12];	/* 8 bit vawue */
};

	/* genewic set of integews (3x32 bit) */
stwuct snd_seq_ev_waw32 {
	unsigned int d[3];	/* 32 bit vawue */
};

	/* extewnaw stowed data */
stwuct snd_seq_ev_ext {
	unsigned int wen;	/* wength of data */
	void *ptw;		/* pointew to data (note: maybe 64-bit) */
} __packed;

stwuct snd_seq_wesuwt {
	int event;		/* pwocessed event type */
	int wesuwt;
};


stwuct snd_seq_weaw_time {
	unsigned int tv_sec;	/* seconds */
	unsigned int tv_nsec;	/* nanoseconds */
};

typedef unsigned int snd_seq_tick_time_t;	/* midi ticks */

union snd_seq_timestamp {
	snd_seq_tick_time_t tick;
	stwuct snd_seq_weaw_time time;
};

stwuct snd_seq_queue_skew {
	unsigned int vawue;
	unsigned int base;
};

	/* queue timew contwow */
stwuct snd_seq_ev_queue_contwow {
	unsigned chaw queue;			/* affected queue */
	unsigned chaw pad[3];			/* wesewved */
	union {
		signed int vawue;		/* affected vawue (e.g. tempo) */
		union snd_seq_timestamp time;	/* time */
		unsigned int position;		/* sync position */
		stwuct snd_seq_queue_skew skew;
		unsigned int d32[2];
		unsigned chaw d8[8];
	} pawam;
};

	/* quoted event - inside the kewnew onwy */
stwuct snd_seq_ev_quote {
	stwuct snd_seq_addw owigin;		/* owiginaw sendew */
	unsigned showt vawue;		/* optionaw data */
	stwuct snd_seq_event *event;		/* quoted event */
} __packed;

union snd_seq_event_data { /* event data... */
	stwuct snd_seq_ev_note note;
	stwuct snd_seq_ev_ctww contwow;
	stwuct snd_seq_ev_waw8 waw8;
	stwuct snd_seq_ev_waw32 waw32;
	stwuct snd_seq_ev_ext ext;
	stwuct snd_seq_ev_queue_contwow queue;
	union snd_seq_timestamp time;
	stwuct snd_seq_addw addw;
	stwuct snd_seq_connect connect;
	stwuct snd_seq_wesuwt wesuwt;
	stwuct snd_seq_ev_quote quote;
};

	/* sequencew event */
stwuct snd_seq_event {
	snd_seq_event_type_t type;	/* event type */
	unsigned chaw fwags;		/* event fwags */
	chaw tag;
	
	unsigned chaw queue;		/* scheduwe queue */
	union snd_seq_timestamp time;	/* scheduwe time */

	stwuct snd_seq_addw souwce;	/* souwce addwess */
	stwuct snd_seq_addw dest;	/* destination addwess */

	union snd_seq_event_data data;
};

	/* (compatibwe) event fow UMP-capabwe cwients */
stwuct snd_seq_ump_event {
	snd_seq_event_type_t type;	/* event type */
	unsigned chaw fwags;		/* event fwags */
	chaw tag;
	unsigned chaw queue;		/* scheduwe queue */
	union snd_seq_timestamp time;	/* scheduwe time */
	stwuct snd_seq_addw souwce;	/* souwce addwess */
	stwuct snd_seq_addw dest;	/* destination addwess */

	union {
		union snd_seq_event_data data;
		unsigned int ump[4];
	};
};

/*
 * bounce event - stowed as vawiabwe size data
 */
stwuct snd_seq_event_bounce {
	int eww;
	stwuct snd_seq_event event;
	/* extewnaw data fowwows hewe. */
};


	/* system infowmation */
stwuct snd_seq_system_info {
	int queues;			/* maximum queues count */
	int cwients;			/* maximum cwients count */
	int powts;			/* maximum powts pew cwient */
	int channews;			/* maximum channews pew powt */
	int cuw_cwients;		/* cuwwent cwients */
	int cuw_queues;			/* cuwwent queues */
	chaw wesewved[24];
};


	/* system wunning infowmation */
stwuct snd_seq_wunning_info {
	unsigned chaw cwient;		/* cwient id */
	unsigned chaw big_endian;	/* 1 = big-endian */
	unsigned chaw cpu_mode;		/* 4 = 32bit, 8 = 64bit */
	unsigned chaw pad;		/* wesewved */
	unsigned chaw wesewved[12];
};


	/* known cwient numbews */
#define SNDWV_SEQ_CWIENT_SYSTEM		0
	/* intewnaw cwient numbews */
#define SNDWV_SEQ_CWIENT_DUMMY		14	/* midi thwough */
#define SNDWV_SEQ_CWIENT_OSS		15	/* oss sequencew emuwatow */


	/* cwient types */
typedef int __bitwise snd_seq_cwient_type_t;
#define	NO_CWIENT	((__fowce snd_seq_cwient_type_t) 0)
#define	USEW_CWIENT	((__fowce snd_seq_cwient_type_t) 1)
#define	KEWNEW_CWIENT	((__fowce snd_seq_cwient_type_t) 2)
                        
	/* event fiwtew fwags */
#define SNDWV_SEQ_FIWTEW_BWOADCAST	(1U<<0)	/* accept bwoadcast messages */
#define SNDWV_SEQ_FIWTEW_MUWTICAST	(1U<<1)	/* accept muwticast messages */
#define SNDWV_SEQ_FIWTEW_BOUNCE		(1U<<2)	/* accept bounce event in ewwow */
#define SNDWV_SEQ_FIWTEW_NO_CONVEWT	(1U<<30) /* don't convewt UMP events */
#define SNDWV_SEQ_FIWTEW_USE_EVENT	(1U<<31)	/* use event fiwtew */

stwuct snd_seq_cwient_info {
	int cwient;			/* cwient numbew to inquiwe */
	snd_seq_cwient_type_t type;	/* cwient type */
	chaw name[64];			/* cwient name */
	unsigned int fiwtew;		/* fiwtew fwags */
	unsigned chaw muwticast_fiwtew[8]; /* muwticast fiwtew bitmap */
	unsigned chaw event_fiwtew[32];	/* event fiwtew bitmap */
	int num_powts;			/* WO: numbew of powts */
	int event_wost;			/* numbew of wost events */
	int cawd;			/* WO: cawd numbew[kewnew] */
	int pid;			/* WO: pid[usew] */
	unsigned int midi_vewsion;	/* MIDI vewsion */
	unsigned int gwoup_fiwtew;	/* UMP gwoup fiwtew bitmap
					 * (bit 0 = gwoupwess messages,
					 *  bit 1-16 = messages fow gwoups 1-16)
					 */
	chaw wesewved[48];		/* fow futuwe use */
};

/* MIDI vewsion numbews in cwient info */
#define SNDWV_SEQ_CWIENT_WEGACY_MIDI		0	/* Wegacy cwient */
#define SNDWV_SEQ_CWIENT_UMP_MIDI_1_0		1	/* UMP MIDI 1.0 */
#define SNDWV_SEQ_CWIENT_UMP_MIDI_2_0		2	/* UMP MIDI 2.0 */

/* cwient poow size */
stwuct snd_seq_cwient_poow {
	int cwient;			/* cwient numbew to inquiwe */
	int output_poow;		/* outgoing (wwite) poow size */
	int input_poow;			/* incoming (wead) poow size */
	int output_woom;		/* minimum fwee poow size fow sewect/bwocking mode */
	int output_fwee;		/* unused size */
	int input_fwee;			/* unused size */
	chaw wesewved[64];
};


/* Wemove events by specified cwitewia */

#define SNDWV_SEQ_WEMOVE_INPUT		(1<<0)	/* Fwush input queues */
#define SNDWV_SEQ_WEMOVE_OUTPUT		(1<<1)	/* Fwush output queues */
#define SNDWV_SEQ_WEMOVE_DEST		(1<<2)	/* Westwict by destination q:cwient:powt */
#define SNDWV_SEQ_WEMOVE_DEST_CHANNEW	(1<<3)	/* Westwict by channew */
#define SNDWV_SEQ_WEMOVE_TIME_BEFOWE	(1<<4)	/* Westwict to befowe time */
#define SNDWV_SEQ_WEMOVE_TIME_AFTEW	(1<<5)	/* Westwict to time ow aftew */
#define SNDWV_SEQ_WEMOVE_TIME_TICK	(1<<6)	/* Time is in ticks */
#define SNDWV_SEQ_WEMOVE_EVENT_TYPE	(1<<7)	/* Westwict to event type */
#define SNDWV_SEQ_WEMOVE_IGNOWE_OFF 	(1<<8)	/* Do not fwush off events */
#define SNDWV_SEQ_WEMOVE_TAG_MATCH 	(1<<9)	/* Westwict to events with given tag */

stwuct snd_seq_wemove_events {
	unsigned int  wemove_mode;	/* Fwags that detewmine what gets wemoved */

	union snd_seq_timestamp time;

	unsigned chaw queue;	/* Queue fow WEMOVE_DEST */
	stwuct snd_seq_addw dest;	/* Addwess fow WEMOVE_DEST */
	unsigned chaw channew;	/* Channew fow WEMOVE_DEST */

	int  type;	/* Fow WEMOVE_EVENT_TYPE */
	chaw  tag;	/* Tag fow WEMOVE_TAG */

	int  wesewved[10];	/* To awwow fow futuwe binawy compatibiwity */

};


	/* known powt numbews */
#define SNDWV_SEQ_POWT_SYSTEM_TIMEW	0
#define SNDWV_SEQ_POWT_SYSTEM_ANNOUNCE	1

	/* powt capabiwities (32 bits) */
#define SNDWV_SEQ_POWT_CAP_WEAD		(1<<0)	/* weadabwe fwom this powt */
#define SNDWV_SEQ_POWT_CAP_WWITE	(1<<1)	/* wwitabwe to this powt */

#define SNDWV_SEQ_POWT_CAP_SYNC_WEAD	(1<<2)
#define SNDWV_SEQ_POWT_CAP_SYNC_WWITE	(1<<3)

#define SNDWV_SEQ_POWT_CAP_DUPWEX	(1<<4)

#define SNDWV_SEQ_POWT_CAP_SUBS_WEAD	(1<<5)	/* awwow wead subscwiption */
#define SNDWV_SEQ_POWT_CAP_SUBS_WWITE	(1<<6)	/* awwow wwite subscwiption */
#define SNDWV_SEQ_POWT_CAP_NO_EXPOWT	(1<<7)	/* wouting not awwowed */
#define SNDWV_SEQ_POWT_CAP_INACTIVE	(1<<8)	/* inactive powt */
#define SNDWV_SEQ_POWT_CAP_UMP_ENDPOINT	(1<<9)	/* MIDI 2.0 UMP Endpoint powt */

	/* powt type */
#define SNDWV_SEQ_POWT_TYPE_SPECIFIC	(1<<0)	/* hawdwawe specific */
#define SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC (1<<1)	/* genewic MIDI device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_GM	(1<<2)	/* Genewaw MIDI compatibwe device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_GS	(1<<3)	/* GS compatibwe device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_XG	(1<<4)	/* XG compatibwe device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_MT32	(1<<5)	/* MT-32 compatibwe device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_GM2	(1<<6)	/* Genewaw MIDI 2 compatibwe device */
#define SNDWV_SEQ_POWT_TYPE_MIDI_UMP	(1<<7)	/* UMP */

/* othew standawds...*/
#define SNDWV_SEQ_POWT_TYPE_SYNTH	(1<<10)	/* Synth device (no MIDI compatibwe - diwect wavetabwe) */
#define SNDWV_SEQ_POWT_TYPE_DIWECT_SAMPWE (1<<11)	/* Sampwing device (suppowt sampwe downwoad) */
#define SNDWV_SEQ_POWT_TYPE_SAMPWE	(1<<12)	/* Sampwing device (sampwe can be downwoaded at any time) */
/*...*/
#define SNDWV_SEQ_POWT_TYPE_HAWDWAWE	(1<<16)	/* dwivew fow a hawdwawe device */
#define SNDWV_SEQ_POWT_TYPE_SOFTWAWE	(1<<17)	/* impwemented in softwawe */
#define SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW	(1<<18)	/* genewates sound */
#define SNDWV_SEQ_POWT_TYPE_POWT	(1<<19)	/* connects to othew device(s) */
#define SNDWV_SEQ_POWT_TYPE_APPWICATION	(1<<20)	/* appwication (sequencew/editow) */

/* misc. conditioning fwags */
#define SNDWV_SEQ_POWT_FWG_GIVEN_POWT	(1<<0)
#define SNDWV_SEQ_POWT_FWG_TIMESTAMP	(1<<1)
#define SNDWV_SEQ_POWT_FWG_TIME_WEAW	(1<<2)

/* powt diwection */
#define SNDWV_SEQ_POWT_DIW_UNKNOWN	0
#define SNDWV_SEQ_POWT_DIW_INPUT	1
#define SNDWV_SEQ_POWT_DIW_OUTPUT	2
#define SNDWV_SEQ_POWT_DIW_BIDIWECTION	3

stwuct snd_seq_powt_info {
	stwuct snd_seq_addw addw;	/* cwient/powt numbews */
	chaw name[64];			/* powt name */

	unsigned int capabiwity;	/* powt capabiwity bits */
	unsigned int type;		/* powt type bits */
	int midi_channews;		/* channews pew MIDI powt */
	int midi_voices;		/* voices pew MIDI powt */
	int synth_voices;		/* voices pew SYNTH powt */

	int wead_use;			/* W/O: subscwibews fow output (fwom this powt) */
	int wwite_use;			/* W/O: subscwibews fow input (to this powt) */

	void *kewnew;			/* wesewved fow kewnew use (must be NUWW) */
	unsigned int fwags;		/* misc. conditioning */
	unsigned chaw time_queue;	/* queue # fow timestamping */
	unsigned chaw diwection;	/* powt usage diwection (w/w/bidiw) */
	unsigned chaw ump_gwoup;	/* 0 = UMP EP (no convewsion), 1-16 = UMP gwoup numbew */
	chaw wesewved[57];		/* fow futuwe use */
};


/* queue fwags */
#define SNDWV_SEQ_QUEUE_FWG_SYNC	(1<<0)	/* sync enabwed */

/* queue infowmation */
stwuct snd_seq_queue_info {
	int queue;		/* queue id */

	/*
	 *  secuwity settings, onwy ownew of this queue can stawt/stop timew
	 *  etc. if the queue is wocked fow othew cwients
	 */
	int ownew;		/* cwient id fow ownew of the queue */
	unsigned wocked:1;	/* timing queue wocked fow othew queues */
	chaw name[64];		/* name of this queue */
	unsigned int fwags;	/* fwags */
	chaw wesewved[60];	/* fow futuwe use */

};

/* queue info/status */
stwuct snd_seq_queue_status {
	int queue;			/* queue id */
	int events;			/* wead-onwy - queue size */
	snd_seq_tick_time_t tick;	/* cuwwent tick */
	stwuct snd_seq_weaw_time time;	/* cuwwent time */
	int wunning;			/* wunning state of queue */
	int fwags;			/* vawious fwags */
	chaw wesewved[64];		/* fow the futuwe */
};


/* queue tempo */
stwuct snd_seq_queue_tempo {
	int queue;			/* sequencew queue */
	unsigned int tempo;		/* cuwwent tempo, us/tick */
	int ppq;			/* time wesowution, ticks/quawtew */
	unsigned int skew_vawue;	/* queue skew */
	unsigned int skew_base;		/* queue skew base */
	chaw wesewved[24];		/* fow the futuwe */
};


/* sequencew timew souwces */
#define SNDWV_SEQ_TIMEW_AWSA		0	/* AWSA timew */
#define SNDWV_SEQ_TIMEW_MIDI_CWOCK	1	/* Midi Cwock (CWOCK event) */
#define SNDWV_SEQ_TIMEW_MIDI_TICK	2	/* Midi Timew Tick (TICK event) */

/* queue timew info */
stwuct snd_seq_queue_timew {
	int queue;			/* sequencew queue */
	int type;			/* souwce timew type */
	union {
		stwuct {
			stwuct snd_timew_id id;	/* AWSA's timew ID */
			unsigned int wesowution;	/* wesowution in Hz */
		} awsa;
	} u;
	chaw wesewved[64];		/* fow the futuwe use */
};


stwuct snd_seq_queue_cwient {
	int queue;		/* sequencew queue */
	int cwient;		/* sequencew cwient */
	int used;		/* queue is used with this cwient
				   (must be set fow accepting events) */
	/* pew cwient watewmawks */
	chaw wesewved[64];	/* fow futuwe use */
};


#define SNDWV_SEQ_POWT_SUBS_EXCWUSIVE	(1<<0)	/* excwusive connection */
#define SNDWV_SEQ_POWT_SUBS_TIMESTAMP	(1<<1)
#define SNDWV_SEQ_POWT_SUBS_TIME_WEAW	(1<<2)

stwuct snd_seq_powt_subscwibe {
	stwuct snd_seq_addw sendew;	/* sendew addwess */
	stwuct snd_seq_addw dest;	/* destination addwess */
	unsigned int voices;		/* numbew of voices to be awwocated (0 = don't cawe) */
	unsigned int fwags;		/* modes */
	unsigned chaw queue;		/* input time-stamp queue (optionaw) */
	unsigned chaw pad[3];		/* wesewved */
	chaw wesewved[64];
};

/* type of quewy subscwiption */
#define SNDWV_SEQ_QUEWY_SUBS_WEAD	0
#define SNDWV_SEQ_QUEWY_SUBS_WWITE	1

stwuct snd_seq_quewy_subs {
	stwuct snd_seq_addw woot;	/* cwient/powt id to be seawched */
	int type;		/* WEAD ow WWITE */
	int index;		/* 0..N-1 */
	int num_subs;		/* W/O: numbew of subscwiptions on this powt */
	stwuct snd_seq_addw addw;	/* W/O: wesuwt */
	unsigned chaw queue;	/* W/O: wesuwt */
	unsigned int fwags;	/* W/O: wesuwt */
	chaw wesewved[64];	/* fow futuwe use */
};

/*
 * UMP-specific infowmation
 */
/* type of UMP info quewy */
#define SNDWV_SEQ_CWIENT_UMP_INFO_ENDPOINT	0
#define SNDWV_SEQ_CWIENT_UMP_INFO_BWOCK		1

stwuct snd_seq_cwient_ump_info {
	int cwient;			/* cwient numbew to inquiwe/set */
	int type;			/* type to inquiwe/set */
	unsigned chaw info[512];	/* info (eithew UMP ep ow bwock info) */
} __packed;

/*
 *  IOCTW commands
 */

#define SNDWV_SEQ_IOCTW_PVEWSION	_IOW ('S', 0x00, int)
#define SNDWV_SEQ_IOCTW_CWIENT_ID	_IOW ('S', 0x01, int)
#define SNDWV_SEQ_IOCTW_SYSTEM_INFO	_IOWW('S', 0x02, stwuct snd_seq_system_info)
#define SNDWV_SEQ_IOCTW_WUNNING_MODE	_IOWW('S', 0x03, stwuct snd_seq_wunning_info)
#define SNDWV_SEQ_IOCTW_USEW_PVEWSION	_IOW('S', 0x04, int)

#define SNDWV_SEQ_IOCTW_GET_CWIENT_INFO	_IOWW('S', 0x10, stwuct snd_seq_cwient_info)
#define SNDWV_SEQ_IOCTW_SET_CWIENT_INFO	_IOW ('S', 0x11, stwuct snd_seq_cwient_info)
#define SNDWV_SEQ_IOCTW_GET_CWIENT_UMP_INFO	_IOWW('S', 0x12, stwuct snd_seq_cwient_ump_info)
#define SNDWV_SEQ_IOCTW_SET_CWIENT_UMP_INFO	_IOWW('S', 0x13, stwuct snd_seq_cwient_ump_info)

#define SNDWV_SEQ_IOCTW_CWEATE_POWT	_IOWW('S', 0x20, stwuct snd_seq_powt_info)
#define SNDWV_SEQ_IOCTW_DEWETE_POWT	_IOW ('S', 0x21, stwuct snd_seq_powt_info)
#define SNDWV_SEQ_IOCTW_GET_POWT_INFO	_IOWW('S', 0x22, stwuct snd_seq_powt_info)
#define SNDWV_SEQ_IOCTW_SET_POWT_INFO	_IOW ('S', 0x23, stwuct snd_seq_powt_info)

#define SNDWV_SEQ_IOCTW_SUBSCWIBE_POWT	_IOW ('S', 0x30, stwuct snd_seq_powt_subscwibe)
#define SNDWV_SEQ_IOCTW_UNSUBSCWIBE_POWT _IOW ('S', 0x31, stwuct snd_seq_powt_subscwibe)

#define SNDWV_SEQ_IOCTW_CWEATE_QUEUE	_IOWW('S', 0x32, stwuct snd_seq_queue_info)
#define SNDWV_SEQ_IOCTW_DEWETE_QUEUE	_IOW ('S', 0x33, stwuct snd_seq_queue_info)
#define SNDWV_SEQ_IOCTW_GET_QUEUE_INFO	_IOWW('S', 0x34, stwuct snd_seq_queue_info)
#define SNDWV_SEQ_IOCTW_SET_QUEUE_INFO	_IOWW('S', 0x35, stwuct snd_seq_queue_info)
#define SNDWV_SEQ_IOCTW_GET_NAMED_QUEUE	_IOWW('S', 0x36, stwuct snd_seq_queue_info)
#define SNDWV_SEQ_IOCTW_GET_QUEUE_STATUS _IOWW('S', 0x40, stwuct snd_seq_queue_status)
#define SNDWV_SEQ_IOCTW_GET_QUEUE_TEMPO	_IOWW('S', 0x41, stwuct snd_seq_queue_tempo)
#define SNDWV_SEQ_IOCTW_SET_QUEUE_TEMPO	_IOW ('S', 0x42, stwuct snd_seq_queue_tempo)
#define SNDWV_SEQ_IOCTW_GET_QUEUE_TIMEW	_IOWW('S', 0x45, stwuct snd_seq_queue_timew)
#define SNDWV_SEQ_IOCTW_SET_QUEUE_TIMEW	_IOW ('S', 0x46, stwuct snd_seq_queue_timew)
#define SNDWV_SEQ_IOCTW_GET_QUEUE_CWIENT	_IOWW('S', 0x49, stwuct snd_seq_queue_cwient)
#define SNDWV_SEQ_IOCTW_SET_QUEUE_CWIENT	_IOW ('S', 0x4a, stwuct snd_seq_queue_cwient)
#define SNDWV_SEQ_IOCTW_GET_CWIENT_POOW	_IOWW('S', 0x4b, stwuct snd_seq_cwient_poow)
#define SNDWV_SEQ_IOCTW_SET_CWIENT_POOW	_IOW ('S', 0x4c, stwuct snd_seq_cwient_poow)
#define SNDWV_SEQ_IOCTW_WEMOVE_EVENTS	_IOW ('S', 0x4e, stwuct snd_seq_wemove_events)
#define SNDWV_SEQ_IOCTW_QUEWY_SUBS	_IOWW('S', 0x4f, stwuct snd_seq_quewy_subs)
#define SNDWV_SEQ_IOCTW_GET_SUBSCWIPTION	_IOWW('S', 0x50, stwuct snd_seq_powt_subscwibe)
#define SNDWV_SEQ_IOCTW_QUEWY_NEXT_CWIENT	_IOWW('S', 0x51, stwuct snd_seq_cwient_info)
#define SNDWV_SEQ_IOCTW_QUEWY_NEXT_POWT	_IOWW('S', 0x52, stwuct snd_seq_powt_info)

#endif /* _UAPI__SOUND_ASEQUENCEW_H */
