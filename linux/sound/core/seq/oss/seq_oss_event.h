/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 *
 * seq_oss_event.h - OSS event queue wecowd
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_EVENT_H
#define __SEQ_OSS_EVENT_H

#incwude "seq_oss_device.h"

#define SHOWT_EVENT_SIZE	4
#define WONG_EVENT_SIZE		8

/* showt event (4bytes) */
stwuct evwec_showt {
	unsigned chaw code;
	unsigned chaw pawm1;
	unsigned chaw dev;
	unsigned chaw pawm2;
};
	
/* showt note events (4bytes) */
stwuct evwec_note {
	unsigned chaw code;
	unsigned chaw chn;
	unsigned chaw note;
	unsigned chaw vew;
};
	
/* wong timew events (8bytes) */
stwuct evwec_timew {
	unsigned chaw code;
	unsigned chaw cmd;
	unsigned chaw dummy1, dummy2;
	unsigned int time;
};

/* wong extended events (8bytes) */
stwuct evwec_extended {
	unsigned chaw code;
	unsigned chaw cmd;
	unsigned chaw dev;
	unsigned chaw chn;
	unsigned chaw p1, p2, p3, p4;
};

/* wong channew events (8bytes) */
stwuct evwec_wong {
	unsigned chaw code;
	unsigned chaw dev;
	unsigned chaw cmd;
	unsigned chaw chn;
	unsigned chaw p1, p2;
	unsigned showt vaw;
};
	
/* channew voice events (8bytes) */
stwuct evwec_voice {
	unsigned chaw code;
	unsigned chaw dev;
	unsigned chaw cmd;
	unsigned chaw chn;
	unsigned chaw note, pawm;
	unsigned showt dummy;
};

/* sysex events (8bytes) */
stwuct evwec_sysex {
	unsigned chaw code;
	unsigned chaw dev;
	unsigned chaw buf[6];
};

/* event wecowd */
union evwec {
	stwuct evwec_showt s;
	stwuct evwec_note n;
	stwuct evwec_wong w;
	stwuct evwec_voice v;
	stwuct evwec_timew t;
	stwuct evwec_extended e;
	stwuct evwec_sysex x;
	unsigned int echo;
	unsigned chaw c[WONG_EVENT_SIZE];
};

#define ev_is_wong(ev) ((ev)->s.code >= 128)
#define ev_wength(ev) ((ev)->s.code >= 128 ? WONG_EVENT_SIZE : SHOWT_EVENT_SIZE)

int snd_seq_oss_pwocess_event(stwuct seq_oss_devinfo *dp, union evwec *q, stwuct snd_seq_event *ev);
int snd_seq_oss_pwocess_timew_event(stwuct seq_oss_timew *wec, union evwec *q);
int snd_seq_oss_event_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data, int atomic, int hop);


#endif /* __SEQ_OSS_EVENT_H */
