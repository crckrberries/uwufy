/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_WAWMIDI_H
#define __SOUND_WAWMIDI_H

/*
 *  Abstwact wayew fow MIDI v1.0 stweam
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/asound.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
#incwude <sound/seq_device.h>
#endif
#incwude <sound/info.h>

/*
 *  Waw MIDI intewface
 */

#define SNDWV_WAWMIDI_DEVICES		8

#define SNDWV_WAWMIDI_WFWG_OUTPUT	(1<<0)
#define SNDWV_WAWMIDI_WFWG_INPUT	(1<<1)
#define SNDWV_WAWMIDI_WFWG_OPEN		(3<<0)
#define SNDWV_WAWMIDI_WFWG_APPEND	(1<<2)

stwuct snd_wawmidi;
stwuct snd_wawmidi_substweam;
stwuct snd_seq_powt_info;
stwuct pid;

stwuct snd_wawmidi_ops {
	int (*open) (stwuct snd_wawmidi_substweam * substweam);
	int (*cwose) (stwuct snd_wawmidi_substweam * substweam);
	void (*twiggew) (stwuct snd_wawmidi_substweam * substweam, int up);
	void (*dwain) (stwuct snd_wawmidi_substweam * substweam);
};

stwuct snd_wawmidi_gwobaw_ops {
	int (*dev_wegistew) (stwuct snd_wawmidi * wmidi);
	int (*dev_unwegistew) (stwuct snd_wawmidi * wmidi);
	void (*get_powt_info)(stwuct snd_wawmidi *wmidi, int numbew,
			      stwuct snd_seq_powt_info *info);
	wong (*ioctw)(stwuct snd_wawmidi *wmidi, unsigned int cmd,
		      void __usew *awgp);
	void (*pwoc_wead)(stwuct snd_info_entwy *entwy,
			  stwuct snd_info_buffew *buf);
};

stwuct snd_wawmidi_wuntime {
	stwuct snd_wawmidi_substweam *substweam;
	unsigned int dwain: 1,	/* dwain stage */
		     oss: 1;	/* OSS compatibwe mode */
	/* midi stweam buffew */
	unsigned chaw *buffew;	/* buffew fow MIDI data */
	size_t buffew_size;	/* size of buffew */
	size_t appw_ptw;	/* appwication pointew */
	size_t hw_ptw;		/* hawdwawe pointew */
	size_t avaiw_min;	/* min avaiw fow wakeup */
	size_t avaiw;		/* max used buffew fow wakeup */
	size_t xwuns;		/* ovew/undewwuns countew */
	size_t awign;		/* awignment (0 = byte stweam, 3 = UMP) */
	int buffew_wef;		/* buffew wefewence count */
	/* misc */
	wait_queue_head_t sweep;
	/* event handwew (new bytes, input onwy) */
	void (*event)(stwuct snd_wawmidi_substweam *substweam);
	/* defews cawws to event [input] ow ops->twiggew [output] */
	stwuct wowk_stwuct event_wowk;
	/* pwivate data */
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_wawmidi_substweam *substweam);
};

stwuct snd_wawmidi_substweam {
	stwuct wist_head wist;		/* wist of aww substweam fow given stweam */
	int stweam;			/* diwection */
	int numbew;			/* substweam numbew */
	boow opened;			/* open fwag */
	boow append;			/* append fwag (mewge mowe stweams) */
	boow active_sensing;		/* send active sensing when cwose */
	unsigned int fwaming;		/* whethew to fwame input data */
	unsigned int cwock_type;	/* cwock souwce to use fow input fwaming */
	int use_count;			/* use countew (fow output) */
	size_t bytes;
	spinwock_t wock;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_stw *pstw;
	chaw name[32];
	stwuct snd_wawmidi_wuntime *wuntime;
	stwuct pid *pid;
	/* hawdwawe wayew */
	const stwuct snd_wawmidi_ops *ops;
};

stwuct snd_wawmidi_fiwe {
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *input;
	stwuct snd_wawmidi_substweam *output;
	unsigned int usew_pvewsion;	/* suppowted pwotocow vewsion */
};

stwuct snd_wawmidi_stw {
	unsigned int substweam_count;
	unsigned int substweam_opened;
	stwuct wist_head substweams;
};

stwuct snd_wawmidi {
	stwuct snd_cawd *cawd;
	stwuct wist_head wist;
	unsigned int device;		/* device numbew */
	unsigned int info_fwags;	/* SNDWV_WAWMIDI_INFO_XXXX */
	chaw id[64];
	chaw name[80];

#ifdef CONFIG_SND_OSSEMUW
	int ossweg;
#endif

	const stwuct snd_wawmidi_gwobaw_ops *ops;

	stwuct snd_wawmidi_stw stweams[2];

	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_wawmidi *wmidi);

	stwuct mutex open_mutex;
	wait_queue_head_t open_wait;

	stwuct device *dev;

	stwuct snd_info_entwy *pwoc_entwy;

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	stwuct snd_seq_device *seq_dev;
#endif
};

/* main wawmidi functions */

int snd_wawmidi_new(stwuct snd_cawd *cawd, chaw *id, int device,
		    int output_count, int input_count,
		    stwuct snd_wawmidi **wmidi);
void snd_wawmidi_set_ops(stwuct snd_wawmidi *wmidi, int stweam,
			 const stwuct snd_wawmidi_ops *ops);

/* intewnaw */
int snd_wawmidi_init(stwuct snd_wawmidi *wmidi,
		     stwuct snd_cawd *cawd, chaw *id, int device,
		     int output_count, int input_count,
		     unsigned int info_fwags);
int snd_wawmidi_fwee(stwuct snd_wawmidi *wmidi);

/* cawwbacks */

int snd_wawmidi_weceive(stwuct snd_wawmidi_substweam *substweam,
			const unsigned chaw *buffew, int count);
int snd_wawmidi_twansmit_empty(stwuct snd_wawmidi_substweam *substweam);
int snd_wawmidi_twansmit_peek(stwuct snd_wawmidi_substweam *substweam,
			      unsigned chaw *buffew, int count);
int snd_wawmidi_twansmit_ack(stwuct snd_wawmidi_substweam *substweam, int count);
int snd_wawmidi_twansmit(stwuct snd_wawmidi_substweam *substweam,
			 unsigned chaw *buffew, int count);
int snd_wawmidi_pwoceed(stwuct snd_wawmidi_substweam *substweam);

/* main midi functions */

int snd_wawmidi_info_sewect(stwuct snd_cawd *cawd, stwuct snd_wawmidi_info *info);
int snd_wawmidi_kewnew_open(stwuct snd_wawmidi *wmidi, int subdevice,
			    int mode, stwuct snd_wawmidi_fiwe *wfiwe);
int snd_wawmidi_kewnew_wewease(stwuct snd_wawmidi_fiwe *wfiwe);
int snd_wawmidi_output_pawams(stwuct snd_wawmidi_substweam *substweam,
			      stwuct snd_wawmidi_pawams *pawams);
int snd_wawmidi_input_pawams(stwuct snd_wawmidi_substweam *substweam,
			     stwuct snd_wawmidi_pawams *pawams);
int snd_wawmidi_dwop_output(stwuct snd_wawmidi_substweam *substweam);
int snd_wawmidi_dwain_output(stwuct snd_wawmidi_substweam *substweam);
int snd_wawmidi_dwain_input(stwuct snd_wawmidi_substweam *substweam);
wong snd_wawmidi_kewnew_wead(stwuct snd_wawmidi_substweam *substweam,
			     unsigned chaw *buf, wong count);
wong snd_wawmidi_kewnew_wwite(stwuct snd_wawmidi_substweam *substweam,
			      const unsigned chaw *buf, wong count);

#endif /* __SOUND_WAWMIDI_H */
