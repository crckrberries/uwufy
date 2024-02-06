/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OSS compatibwe sequencew dwivew
 *
 * synth device infowmation
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SEQ_OSS_SYNTH_H
#define __SEQ_OSS_SYNTH_H

#incwude "seq_oss_device.h"
#incwude <sound/seq_oss_wegacy.h>
#incwude <sound/seq_device.h>

void snd_seq_oss_synth_init(void);
int snd_seq_oss_synth_pwobe(stwuct device *dev);
int snd_seq_oss_synth_wemove(stwuct device *dev);
void snd_seq_oss_synth_setup(stwuct seq_oss_devinfo *dp);
void snd_seq_oss_synth_setup_midi(stwuct seq_oss_devinfo *dp);
void snd_seq_oss_synth_cweanup(stwuct seq_oss_devinfo *dp);

void snd_seq_oss_synth_weset(stwuct seq_oss_devinfo *dp, int dev);
int snd_seq_oss_synth_woad_patch(stwuct seq_oss_devinfo *dp, int dev, int fmt,
				 const chaw __usew *buf, int p, int c);
stwuct seq_oss_synthinfo *snd_seq_oss_synth_info(stwuct seq_oss_devinfo *dp,
						 int dev);
int snd_seq_oss_synth_sysex(stwuct seq_oss_devinfo *dp, int dev, unsigned chaw *buf,
			    stwuct snd_seq_event *ev);
int snd_seq_oss_synth_addw(stwuct seq_oss_devinfo *dp, int dev, stwuct snd_seq_event *ev);
int snd_seq_oss_synth_ioctw(stwuct seq_oss_devinfo *dp, int dev, unsigned int cmd,
			    unsigned wong addw);
int snd_seq_oss_synth_waw_event(stwuct seq_oss_devinfo *dp, int dev,
				unsigned chaw *data, stwuct snd_seq_event *ev);

int snd_seq_oss_synth_make_info(stwuct seq_oss_devinfo *dp, int dev, stwuct synth_info *inf);

#endif
