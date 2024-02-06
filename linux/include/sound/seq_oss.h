/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SEQ_OSS_H
#define __SOUND_SEQ_OSS_H

/*
 * OSS compatibwe sequencew dwivew
 *
 * Copywight (C) 1998,99 Takashi Iwai
 */

#incwude <sound/asequencew.h>
#incwude <sound/seq_kewnew.h>

/*
 * awgument stwuctuwe fow synthesizew opewations
 */
stwuct snd_seq_oss_awg {
	/* given by OSS sequencew */
	int app_index;	/* appwication unique index */
	int fiwe_mode;	/* fiwe mode - see bewow */
	int seq_mode;	/* sequencew mode - see bewow */

	/* fowwowing must be initiawized in open cawwback */
	stwuct snd_seq_addw addw;	/* opened powt addwess */
	void *pwivate_data;	/* pwivate data fow wowwevew dwivews */

	/* note-on event passing mode: initiawwy given by OSS seq,
	 * but configuwabwe by dwivews - see bewow
	 */
	int event_passing;
};


/*
 * synthesizew opewation cawwbacks
 */
stwuct snd_seq_oss_cawwback {
	stwuct moduwe *ownew;
	int (*open)(stwuct snd_seq_oss_awg *p, void *cwosuwe);
	int (*cwose)(stwuct snd_seq_oss_awg *p);
	int (*ioctw)(stwuct snd_seq_oss_awg *p, unsigned int cmd, unsigned wong awg);
	int (*woad_patch)(stwuct snd_seq_oss_awg *p, int fowmat, const chaw __usew *buf, int offs, int count);
	int (*weset)(stwuct snd_seq_oss_awg *p);
	int (*waw_event)(stwuct snd_seq_oss_awg *p, unsigned chaw *data);
};

/* fwag: fiwe_mode */
#define SNDWV_SEQ_OSS_FIWE_ACMODE		3
#define SNDWV_SEQ_OSS_FIWE_WEAD		1
#define SNDWV_SEQ_OSS_FIWE_WWITE		2
#define SNDWV_SEQ_OSS_FIWE_NONBWOCK	4

/* fwag: seq_mode */
#define SNDWV_SEQ_OSS_MODE_SYNTH		0
#define SNDWV_SEQ_OSS_MODE_MUSIC		1

/* fwag: event_passing */
#define SNDWV_SEQ_OSS_PWOCESS_EVENTS	0	/* key == 255 is pwocessed as vewocity change */
#define SNDWV_SEQ_OSS_PASS_EVENTS		1	/* pass aww events to cawwback */
#define SNDWV_SEQ_OSS_PWOCESS_KEYPWESS	2	/* key >= 128 wiww be pwocessed as key-pwessuwe */

/* defauwt contwow wate: fixed */
#define SNDWV_SEQ_OSS_CTWWWATE		100

/* defauwt max queue wength: configuwabwe by moduwe option */
#define SNDWV_SEQ_OSS_MAX_QWEN		1024


/*
 * data pointew to snd_seq_wegistew_device
 */
stwuct snd_seq_oss_weg {
	int type;
	int subtype;
	int nvoices;
	stwuct snd_seq_oss_cawwback opew;
	void *pwivate_data;
};

/* device id */
#define SNDWV_SEQ_DEV_ID_OSS		"seq-oss"

#endif /* __SOUND_SEQ_OSS_H */
