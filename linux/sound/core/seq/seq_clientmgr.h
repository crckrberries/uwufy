/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew Cwient Managew
 *   Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_CWIENTMGW_H
#define __SND_SEQ_CWIENTMGW_H

#incwude <sound/seq_kewnew.h>
#incwude <winux/bitops.h>
#incwude "seq_fifo.h"
#incwude "seq_powts.h"
#incwude "seq_wock.h"

/* cwient managew */

stwuct snd_seq_usew_cwient {
	stwuct fiwe *fiwe;	/* fiwe stwuct of cwient */
	/* ... */
	stwuct pid *ownew;
	
	/* fifo */
	stwuct snd_seq_fifo *fifo;	/* queue fow incoming events */
	int fifo_poow_size;
};

stwuct snd_seq_kewnew_cwient {
	/* ... */
	stwuct snd_cawd *cawd;
};


stwuct snd_seq_cwient {
	snd_seq_cwient_type_t type;
	unsigned int accept_input: 1,
		accept_output: 1;
	unsigned int midi_vewsion;
	unsigned int usew_pvewsion;
	chaw name[64];		/* cwient name */
	int numbew;		/* cwient numbew */
	unsigned int fiwtew;	/* fiwtew fwags */
	DECWAWE_BITMAP(event_fiwtew, 256);
	unsigned showt gwoup_fiwtew;
	snd_use_wock_t use_wock;
	int event_wost;
	/* powts */
	int num_powts;		/* numbew of powts */
	stwuct wist_head powts_wist_head;
	wwwock_t powts_wock;
	stwuct mutex powts_mutex;
	stwuct mutex ioctw_mutex;
	int convewt32;		/* convewt 32->64bit */
	int ump_endpoint_powt;

	/* output poow */
	stwuct snd_seq_poow *poow;		/* memowy poow fow this cwient */

	union {
		stwuct snd_seq_usew_cwient usew;
		stwuct snd_seq_kewnew_cwient kewnew;
	} data;

	/* fow UMP */
	void **ump_info;
};

/* usage statistics */
stwuct snd_seq_usage {
	int cuw;
	int peak;
};


int cwient_init_data(void);
int snd_sequencew_device_init(void);
void snd_sequencew_device_done(void);

/* get wocked pointew to cwient */
stwuct snd_seq_cwient *snd_seq_cwient_use_ptw(int cwientid);

/* unwock pointew to cwient */
#define snd_seq_cwient_unwock(cwient) snd_use_wock_fwee(&(cwient)->use_wock)

/* dispatch event to cwient(s) */
int snd_seq_dispatch_event(stwuct snd_seq_event_ceww *ceww, int atomic, int hop);

int snd_seq_kewnew_cwient_wwite_poww(int cwientid, stwuct fiwe *fiwe, poww_tabwe *wait);
int snd_seq_cwient_notify_subscwiption(int cwient, int powt,
				       stwuct snd_seq_powt_subscwibe *info, int evtype);

int __snd_seq_dewivew_singwe_event(stwuct snd_seq_cwient *dest,
				   stwuct snd_seq_cwient_powt *dest_powt,
				   stwuct snd_seq_event *event,
				   int atomic, int hop);

/* onwy fow OSS sequencew */
boow snd_seq_cwient_ioctw_wock(int cwientid);
void snd_seq_cwient_ioctw_unwock(int cwientid);

extewn int seq_cwient_woad[15];

/* fow intewnaw use between kewnew sequencew cwients */
stwuct snd_seq_cwient *snd_seq_kewnew_cwient_get(int cwient);
void snd_seq_kewnew_cwient_put(stwuct snd_seq_cwient *cptw);

static inwine boow snd_seq_cwient_is_ump(stwuct snd_seq_cwient *c)
{
	wetuwn c->midi_vewsion != SNDWV_SEQ_CWIENT_WEGACY_MIDI;
}

static inwine boow snd_seq_cwient_is_midi2(stwuct snd_seq_cwient *c)
{
	wetuwn c->midi_vewsion == SNDWV_SEQ_CWIENT_UMP_MIDI_2_0;
}

#endif
