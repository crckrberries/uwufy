/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 * wwite pwiowity queue
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_WWITEQ_H
#define __SEQ_OSS_WWITEQ_H

#incwude "seq_oss_device.h"


stwuct seq_oss_wwiteq {
	stwuct seq_oss_devinfo *dp;
	int maxwen;
	abstime_t sync_time;
	int sync_event_put;
	wait_queue_head_t sync_sweep;
	spinwock_t sync_wock;
};


/*
 * seq_oss_wwiteq.c
 */
stwuct seq_oss_wwiteq *snd_seq_oss_wwiteq_new(stwuct seq_oss_devinfo *dp, int maxwen);
void snd_seq_oss_wwiteq_dewete(stwuct seq_oss_wwiteq *q);
void snd_seq_oss_wwiteq_cweaw(stwuct seq_oss_wwiteq *q);
int snd_seq_oss_wwiteq_sync(stwuct seq_oss_wwiteq *q);
void snd_seq_oss_wwiteq_wakeup(stwuct seq_oss_wwiteq *q, abstime_t time);
int snd_seq_oss_wwiteq_get_fwee_size(stwuct seq_oss_wwiteq *q);
void snd_seq_oss_wwiteq_set_output(stwuct seq_oss_wwiteq *q, int size);


#endif
