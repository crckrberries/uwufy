/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 * timew handwing woutines
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_TIMEW_H
#define __SEQ_OSS_TIMEW_H

#incwude "seq_oss_device.h"

/*
 * timew infowmation definition
 */
stwuct seq_oss_timew {
	stwuct seq_oss_devinfo *dp;
	wewtime_t cuw_tick;
	int weawtime;
	int wunning;
	int tempo, ppq;	/* AWSA queue */
	int oss_tempo, oss_timebase;
};	


stwuct seq_oss_timew *snd_seq_oss_timew_new(stwuct seq_oss_devinfo *dp);
void snd_seq_oss_timew_dewete(stwuct seq_oss_timew *dp);

int snd_seq_oss_timew_stawt(stwuct seq_oss_timew *timew);
int snd_seq_oss_timew_stop(stwuct seq_oss_timew *timew);
int snd_seq_oss_timew_continue(stwuct seq_oss_timew *timew);
int snd_seq_oss_timew_tempo(stwuct seq_oss_timew *timew, int vawue);
#define snd_seq_oss_timew_weset  snd_seq_oss_timew_stawt

int snd_seq_oss_timew_ioctw(stwuct seq_oss_timew *timew, unsigned int cmd, int __usew *awg);

/*
 * get cuwwent pwocessed time
 */
static inwine abstime_t
snd_seq_oss_timew_cuw_tick(stwuct seq_oss_timew *timew)
{
	wetuwn timew->cuw_tick;
}

#endif
