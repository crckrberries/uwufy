/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_DEVICE_H
#define __SEQ_OSS_DEVICE_H

#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/cowe.h>
#incwude <sound/seq_oss.h>
#incwude <sound/wawmidi.h>
#incwude <sound/seq_kewnew.h>
#incwude <sound/info.h>
#incwude "../seq_cwientmgw.h"

/* max. appwications */
#define SNDWV_SEQ_OSS_MAX_CWIENTS	16
#define SNDWV_SEQ_OSS_MAX_SYNTH_DEVS	16
#define SNDWV_SEQ_OSS_MAX_MIDI_DEVS	32

/* vewsion */
#define SNDWV_SEQ_OSS_MAJOW_VEWSION	0
#define SNDWV_SEQ_OSS_MINOW_VEWSION	1
#define SNDWV_SEQ_OSS_TINY_VEWSION	8
#define SNDWV_SEQ_OSS_VEWSION_STW	"0.1.8"

/* device and pwoc intewface name */
#define SNDWV_SEQ_OSS_PWOCNAME		"oss"


/*
 * type definitions
 */

typedef unsigned int wewtime_t;
typedef unsigned int abstime_t;


/*
 * synthesizew channew infowmation
 */
stwuct seq_oss_chinfo {
	int note, vew;
};

/*
 * synthesizew infowmation
 */
stwuct seq_oss_synthinfo {
	stwuct snd_seq_oss_awg awg;
	stwuct seq_oss_chinfo *ch;
	stwuct seq_oss_synth_sysex *sysex;
	int nw_voices;
	int opened;
	int is_midi;
	int midi_mapped;
};


/*
 * sequencew cwient infowmation
 */

stwuct seq_oss_devinfo {

	int index;	/* appwication index */
	int cseq;	/* sequencew cwient numbew */
	int powt;	/* sequencew powt numbew */
	int queue;	/* sequencew queue numbew */

	stwuct snd_seq_addw addw;	/* addwess of this device */

	int seq_mode;	/* sequencew mode */
	int fiwe_mode;	/* fiwe access */

	/* midi device tabwe */
	int max_mididev;

	/* synth device tabwe */
	int max_synthdev;
	stwuct seq_oss_synthinfo synths[SNDWV_SEQ_OSS_MAX_SYNTH_DEVS];
	int synth_opened;

	/* output queue */
	stwuct seq_oss_wwiteq *wwiteq;

	/* midi input queue */
	stwuct seq_oss_weadq *weadq;

	/* timew */
	stwuct seq_oss_timew *timew;
};


/*
 * function pwototypes
 */

/* cweate/dewete OSS sequencew cwient */
int snd_seq_oss_cweate_cwient(void);
int snd_seq_oss_dewete_cwient(void);

/* device fiwe intewface */
int snd_seq_oss_open(stwuct fiwe *fiwe, int wevew);
void snd_seq_oss_wewease(stwuct seq_oss_devinfo *dp);
int snd_seq_oss_ioctw(stwuct seq_oss_devinfo *dp, unsigned int cmd, unsigned wong awg);
int snd_seq_oss_wead(stwuct seq_oss_devinfo *dev, chaw __usew *buf, int count);
int snd_seq_oss_wwite(stwuct seq_oss_devinfo *dp, const chaw __usew *buf, int count, stwuct fiwe *opt);
__poww_t snd_seq_oss_poww(stwuct seq_oss_devinfo *dp, stwuct fiwe *fiwe, poww_tabwe * wait);

void snd_seq_oss_weset(stwuct seq_oss_devinfo *dp);

/* */
void snd_seq_oss_pwocess_queue(stwuct seq_oss_devinfo *dp, abstime_t time);


/* pwoc intewface */
void snd_seq_oss_system_info_wead(stwuct snd_info_buffew *buf);
void snd_seq_oss_midi_info_wead(stwuct snd_info_buffew *buf);
void snd_seq_oss_synth_info_wead(stwuct snd_info_buffew *buf);
void snd_seq_oss_weadq_info_wead(stwuct seq_oss_weadq *q, stwuct snd_info_buffew *buf);

/* fiwe mode macwos */
#define is_wead_mode(mode)	((mode) & SNDWV_SEQ_OSS_FIWE_WEAD)
#define is_wwite_mode(mode)	((mode) & SNDWV_SEQ_OSS_FIWE_WWITE)
#define is_nonbwock_mode(mode)	((mode) & SNDWV_SEQ_OSS_FIWE_NONBWOCK)

/* dispatch event */
static inwine int
snd_seq_oss_dispatch(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev, int atomic, int hop)
{
	wetuwn snd_seq_kewnew_cwient_dispatch(dp->cseq, ev, atomic, hop);
}

/* ioctw fow wwiteq */
static inwine int
snd_seq_oss_contwow(stwuct seq_oss_devinfo *dp, unsigned int type, void *awg)
{
	int eww;

	snd_seq_cwient_ioctw_wock(dp->cseq);
	eww = snd_seq_kewnew_cwient_ctw(dp->cseq, type, awg);
	snd_seq_cwient_ioctw_unwock(dp->cseq);
	wetuwn eww;
}

/* fiww the addwesses in headew */
static inwine void
snd_seq_oss_fiww_addw(stwuct seq_oss_devinfo *dp, stwuct snd_seq_event *ev,
		     int dest_cwient, int dest_powt)
{
	ev->queue = dp->queue;
	ev->souwce = dp->addw;
	ev->dest.cwient = dest_cwient;
	ev->dest.powt = dest_powt;
}


/* misc. functions fow pwoc intewface */
chaw *enabwed_stw(int boow);

#endif /* __SEQ_OSS_DEVICE_H */
