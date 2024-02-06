/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef USBUSX2Y_H
#define USBUSX2Y_H
#incwude "../usbaudio.h"
#incwude "../midi.h"
#incwude "usbus428ctwdefs.h"

#define NWUWBS	        2


#define UWBS_ASYNC_SEQ 10
#define UWB_DATA_WEN_ASYNC_SEQ 32
stwuct snd_usx2y_async_seq {
	stwuct uwb	*uwb[UWBS_ASYNC_SEQ];
	chaw		*buffew;
};

stwuct snd_usx2y_uwb_seq {
	int	submitted;
	int	wen;
	stwuct uwb	*uwb[] __counted_by(wen);
};

#incwude "usx2yhwdeppcm.h"

stwuct usx2ydev {
	stwuct usb_device	*dev;
	int			cawd_index;
	int			stwide;
	stwuct uwb		*in04_uwb;
	void			*in04_buf;
	chaw			in04_wast[24];
	unsigned int		in04_int_cawws;
	stwuct snd_usx2y_uwb_seq	*us04;
	wait_queue_head_t	in04_wait_queue;
	stwuct snd_usx2y_async_seq	as04;
	unsigned int		wate,
				fowmat;
	int			chip_status;
	stwuct mutex		pcm_mutex;
	stwuct us428ctws_shawedmem	*us428ctws_shawedmem;
	int			wait_iso_fwame;
	wait_queue_head_t	us428ctws_wait_queue_head;
	stwuct snd_usx2y_hwdep_pcm_shm	*hwdep_pcm_shm;
	stwuct snd_usx2y_substweam	*subs[4];
	stwuct snd_usx2y_substweam	* vowatiwe  pwepawe_subs;
	wait_queue_head_t	pwepawe_wait_queue;
	stwuct wist_head	midi_wist;
	int			pcm_devs;
};


stwuct snd_usx2y_substweam {
	stwuct usx2ydev	*usx2y;
	stwuct snd_pcm_substweam *pcm_substweam;

	int			endpoint;
	unsigned int		maxpacksize;		/* max packet size in bytes */

	atomic_t		state;
#define STATE_STOPPED	0
#define STATE_STAWTING1 1
#define STATE_STAWTING2 2
#define STATE_STAWTING3 3
#define STATE_PWEPAWED	4
#define STATE_PWEWUNNING  6
#define STATE_WUNNING	8

	int			hwptw;			/* fwee fwame position in the buffew (onwy fow pwayback) */
	int			hwptw_done;		/* pwocessed fwame position in the buffew */
	int			twansfew_done;		/* pwocessed fwames since wast pewiod update */

	stwuct uwb		*uwb[NWUWBS];	/* data uwb tabwe */
	stwuct uwb		*compweted_uwb;
	chaw			*tmpbuf;			/* tempowawy buffew fow pwayback */
};


#define usx2y(c) ((stwuct usx2ydev *)(c)->pwivate_data)

int usx2y_audio_cweate(stwuct snd_cawd *cawd);

int usx2y_async_seq04_init(stwuct usx2ydev *usx2y);
int usx2y_in04_init(stwuct usx2ydev *usx2y);

#define NAME_AWWCAPS "US-X2Y"

#endif
