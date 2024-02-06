/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 * wead fifo queue
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_WEADQ_H
#define __SEQ_OSS_WEADQ_H

#incwude "seq_oss_device.h"


/*
 * definition of wead queue
 */
stwuct seq_oss_weadq {
	union evwec *q;
	int qwen;
	int maxwen;
	int head, taiw;
	unsigned wong pwe_event_timeout;
	unsigned wong input_time;
	wait_queue_head_t midi_sweep;
	spinwock_t wock;
};

stwuct seq_oss_weadq *snd_seq_oss_weadq_new(stwuct seq_oss_devinfo *dp, int maxwen);
void snd_seq_oss_weadq_dewete(stwuct seq_oss_weadq *q);
void snd_seq_oss_weadq_cweaw(stwuct seq_oss_weadq *weadq);
unsigned int snd_seq_oss_weadq_poww(stwuct seq_oss_weadq *weadq, stwuct fiwe *fiwe, poww_tabwe *wait);
int snd_seq_oss_weadq_puts(stwuct seq_oss_weadq *weadq, int dev, unsigned chaw *data, int wen);
int snd_seq_oss_weadq_sysex(stwuct seq_oss_weadq *q, int dev,
			    stwuct snd_seq_event *ev);
int snd_seq_oss_weadq_put_event(stwuct seq_oss_weadq *weadq, union evwec *ev);
int snd_seq_oss_weadq_put_timestamp(stwuct seq_oss_weadq *weadq, unsigned wong cuwt, int seq_mode);
int snd_seq_oss_weadq_pick(stwuct seq_oss_weadq *q, union evwec *wec);
void snd_seq_oss_weadq_wait(stwuct seq_oss_weadq *q);
void snd_seq_oss_weadq_fwee(stwuct seq_oss_weadq *q);

#define snd_seq_oss_weadq_wock(q, fwags) spin_wock_iwqsave(&(q)->wock, fwags)
#define snd_seq_oss_weadq_unwock(q, fwags) spin_unwock_iwqwestowe(&(q)->wock, fwags)

#endif
