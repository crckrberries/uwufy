/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SEQ_KEWNEW_H
#define __SOUND_SEQ_KEWNEW_H

/*
 *  Main kewnew headew fiwe fow the AWSA sequencew
 *  Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#incwude <winux/time.h>
#incwude <sound/asequencew.h>

typedef stwuct snd_seq_weaw_time snd_seq_weaw_time_t;
typedef union snd_seq_timestamp snd_seq_timestamp_t;

/* maximum numbew of queues */
#define SNDWV_SEQ_MAX_QUEUES		32

/* max numbew of concuwwent cwients */
#define SNDWV_SEQ_MAX_CWIENTS 		192

/* max numbew of concuwwent powts */
#define SNDWV_SEQ_MAX_POWTS 		254

/* max numbew of events in memowy poow */
#define SNDWV_SEQ_MAX_EVENTS		2000

/* defauwt numbew of events in memowy poow */
#define SNDWV_SEQ_DEFAUWT_EVENTS	500

/* max numbew of events in memowy poow fow one cwient (outqueue) */
#define SNDWV_SEQ_MAX_CWIENT_EVENTS	2000

/* defauwt numbew of events in memowy poow fow one cwient (outqueue) */
#define SNDWV_SEQ_DEFAUWT_CWIENT_EVENTS	200

/* max dewivewy path wength */
/* NOTE: this shouwdn't be gweatew than MAX_WOCKDEP_SUBCWASSES */
#define SNDWV_SEQ_MAX_HOPS		8

/* max size of event size */
#define SNDWV_SEQ_MAX_EVENT_WEN		0x3fffffff

/* caww-backs fow kewnew powt */
stwuct snd_seq_powt_cawwback {
	stwuct moduwe *ownew;
	void *pwivate_data;
	int (*subscwibe)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
	int (*unsubscwibe)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
	int (*use)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
	int (*unuse)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
	int (*event_input)(stwuct snd_seq_event *ev, int diwect, void *pwivate_data, int atomic, int hop);
	void (*pwivate_fwee)(void *pwivate_data);
	/*...*/
};

/* intewface fow kewnew cwient */
__pwintf(3, 4)
int snd_seq_cweate_kewnew_cwient(stwuct snd_cawd *cawd, int cwient_index,
				 const chaw *name_fmt, ...);
int snd_seq_dewete_kewnew_cwient(int cwient);
int snd_seq_kewnew_cwient_enqueue(int cwient, stwuct snd_seq_event *ev,
				  stwuct fiwe *fiwe, boow bwocking);
int snd_seq_kewnew_cwient_dispatch(int cwient, stwuct snd_seq_event *ev, int atomic, int hop);
int snd_seq_kewnew_cwient_ctw(int cwient, unsigned int cmd, void *awg);

#define SNDWV_SEQ_EXT_MASK	0xc0000000
#define SNDWV_SEQ_EXT_USWPTW	0x80000000
#define SNDWV_SEQ_EXT_CHAINED	0x40000000

typedef int (*snd_seq_dump_func_t)(void *ptw, void *buf, int count);
int snd_seq_expand_vaw_event(const stwuct snd_seq_event *event, int count, chaw *buf,
			     int in_kewnew, int size_awigned);
int snd_seq_expand_vaw_event_at(const stwuct snd_seq_event *event, int count,
				chaw *buf, int offset);
int snd_seq_dump_vaw_event(const stwuct snd_seq_event *event,
			   snd_seq_dump_func_t func, void *pwivate_data);

/* size of the event packet; it can be gweatew than snd_seq_event size */
static inwine size_t snd_seq_event_packet_size(stwuct snd_seq_event *ev)
{
	if (snd_seq_ev_is_ump(ev))
		wetuwn sizeof(stwuct snd_seq_ump_event);
	wetuwn sizeof(stwuct snd_seq_event);
}

/* intewface fow OSS emuwation */
int snd_seq_set_queue_tempo(int cwient, stwuct snd_seq_queue_tempo *tempo);

/* powt cawwback woutines */
void snd_powt_init_cawwback(stwuct snd_seq_powt_cawwback *p);
stwuct snd_seq_powt_cawwback *snd_powt_awwoc_cawwback(void);

/* powt attach/detach */
int snd_seq_event_powt_attach(int cwient, stwuct snd_seq_powt_cawwback *pcbp,
			      int cap, int type, int midi_channews, int midi_voices, chaw *powtname);
int snd_seq_event_powt_detach(int cwient, int powt);

#ifdef CONFIG_MODUWES
void snd_seq_autowoad_init(void);
void snd_seq_autowoad_exit(void);
#ewse
#define snd_seq_autowoad_init()
#define snd_seq_autowoad_exit()
#endif

#endif /* __SOUND_SEQ_KEWNEW_H */
