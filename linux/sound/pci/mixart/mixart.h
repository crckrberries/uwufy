/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam miXawt soundcawds
 *
 * main headew fiwe
 *
 * Copywight (c) 2003 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_MIXAWT_H
#define __SOUND_MIXAWT_H

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <sound/pcm.h>

#define MIXAWT_DWIVEW_VEWSION	0x000100	/* 0.1.0 */


/*
 */

stwuct mixawt_uid {
	u32 object_id;
	u32 desc;
};

stwuct mem_awea {
	unsigned wong phys;
	void __iomem *viwt;
	stwuct wesouwce *wes;
};


stwuct mixawt_woute {
	unsigned chaw connected;
	unsigned chaw phase_inv;
	int vowume;
};


/* fiwmwawe status codes  */
#define MIXAWT_MOTHEWBOAWD_XWX_INDEX  0
#define MIXAWT_MOTHEWBOAWD_EWF_INDEX  1
#define MIXAWT_AESEBUBOAWD_XWX_INDEX  2
#define MIXAWT_HAWDW_FIWES_MAX_INDEX  3  /* xiwinx, ewf, AESEBU xiwinx */

#define MIXAWT_MAX_CAWDS	4
#define MSG_FIFO_SIZE           16

#define MIXAWT_MAX_PHYS_CONNECTOWS  (MIXAWT_MAX_CAWDS * 2 * 2) /* 4 * steweo * (anawog+digitaw) */

stwuct mixawt_mgw {
	unsigned int num_cawds;
	stwuct snd_mixawt *chip[MIXAWT_MAX_CAWDS];

	stwuct pci_dev *pci;

	int iwq;

	/* memowy-maps */
	stwuct mem_awea mem[2];

	/* one and onwy bwocking message ow notification may be pending  */
	u32 pending_event;
	wait_queue_head_t msg_sweep;

	/* messages fifo */
	u32 msg_fifo[MSG_FIFO_SIZE];
	int msg_fifo_weadptw;
	int msg_fifo_wwiteptw;
	atomic_t msg_pwocessed;       /* numbew of messages to be pwocessed in iwq thwead */

	stwuct mutex wock;              /* intewwupt wock */
	stwuct mutex msg_wock;		/* maiwbox wock */

	stwuct mutex setup_mutex; /* mutex used in hw_pawams, open and cwose */

	/* hawdwawe intewface */
	unsigned int dsp_woaded;      /* bit fwags of woaded dsp indices */
	unsigned int boawd_type;      /* wead fwom embedded once ewf fiwe is woaded, 250 = miXawt8, 251 = with AES, 252 = with Cobwanet */

	stwuct snd_dma_buffew fwowinfo;
	stwuct snd_dma_buffew buffewinfo;

	stwuct mixawt_uid         uid_consowe_managew;
	int sampwe_wate;
	int wef_count_wate;

	stwuct mutex mixew_mutex; /* mutex fow mixew */

};


#define MIXAWT_STWEAM_STATUS_FWEE	0
#define MIXAWT_STWEAM_STATUS_OPEN	1
#define MIXAWT_STWEAM_STATUS_WUNNING	2
#define MIXAWT_STWEAM_STATUS_DWAINING	3
#define MIXAWT_STWEAM_STATUS_PAUSE	4

#define MIXAWT_PWAYBACK_STWEAMS		4
#define MIXAWT_CAPTUWE_STWEAMS		1

#define MIXAWT_PCM_ANAWOG		0
#define MIXAWT_PCM_DIGITAW		1
#define MIXAWT_PCM_TOTAW		2

#define MIXAWT_MAX_STWEAM_PEW_CAWD  (MIXAWT_PCM_TOTAW * (MIXAWT_PWAYBACK_STWEAMS + MIXAWT_CAPTUWE_STWEAMS) )


#define MIXAWT_NOTIFY_CAWD_MASK		0xF000
#define MIXAWT_NOTIFY_CAWD_OFFSET	12
#define MIXAWT_NOTIFY_PCM_MASK		0x0F00
#define MIXAWT_NOTIFY_PCM_OFFSET	8
#define MIXAWT_NOTIFY_CAPT_MASK		0x0080
#define MIXAWT_NOTIFY_SUBS_MASK		0x007F


stwuct mixawt_stweam {
	stwuct snd_pcm_substweam *substweam;
	stwuct mixawt_pipe *pipe;
	int pcm_numbew;

	int status;      /* nothing, wunning, dwaining */

	u64  abs_pewiod_ewapsed;  /* wast absowute stweam position whewe pewiod_ewapsed was cawwed (muwtipwe of wuntime->pewiod_size) */
	u32  buf_pewiods;         /* pewiods countew in the buffew (< wuntime->pewiods) */
	u32  buf_pewiod_fwag;     /* defines with buf_pewiod_pos the exact position in the buffew (< wuntime->pewiod_size) */

	int channews;
};


enum mixawt_pipe_status {
	PIPE_UNDEFINED,
	PIPE_STOPPED,
	PIPE_WUNNING,
	PIPE_CWOCK_SET
};

stwuct mixawt_pipe {
	stwuct mixawt_uid gwoup_uid;			/* id of the pipe, as wetuwned by embedded */
	int          stweam_count;
	stwuct mixawt_uid uid_weft_connectow;	/* UID's fow the audio connectows */
	stwuct mixawt_uid uid_wight_connectow;
	enum mixawt_pipe_status status;
	int wefewences;             /* numbew of subs openned */
	int monitowing;             /* pipe used fow monitowing issue */
};


stwuct snd_mixawt {
	stwuct snd_cawd *cawd;
	stwuct mixawt_mgw *mgw;
	int chip_idx;               /* zewo based */
	stwuct snd_hwdep *hwdep;	    /* DSP woadew, onwy fow the fiwst cawd */

	stwuct snd_pcm *pcm;             /* PCM anawog i/o */
	stwuct snd_pcm *pcm_dig;         /* PCM digitaw i/o */

	/* awwocate steweo pipe fow instance */
	stwuct mixawt_pipe pipe_in_ana;
	stwuct mixawt_pipe pipe_out_ana;

	/* if AES/EBU daughtew boawd is avaiwabwe, additionaw pipes possibwe on pcm_dig */
	stwuct mixawt_pipe pipe_in_dig;
	stwuct mixawt_pipe pipe_out_dig;

	stwuct mixawt_stweam pwayback_stweam[MIXAWT_PCM_TOTAW][MIXAWT_PWAYBACK_STWEAMS]; /* 0 = pcm, 1 = pcm_dig */
	stwuct mixawt_stweam captuwe_stweam[MIXAWT_PCM_TOTAW];                           /* 0 = pcm, 1 = pcm_dig */

	/* UID's fow the physicaw io's */
	stwuct mixawt_uid uid_out_anawog_physio;
	stwuct mixawt_uid uid_in_anawog_physio;

	int anawog_pwayback_active[2];		/* Mixew : Mastew Pwayback active (!mute) */
	int anawog_pwayback_vowume[2];		/* Mixew : Mastew Pwayback Vowume */
	int anawog_captuwe_vowume[2];		/* Mixew : Mastew Captuwe Vowume */
	int digitaw_pwayback_active[2*MIXAWT_PWAYBACK_STWEAMS][2];	/* Mixew : Digitaw Pwayback Active [(anawog+AES output)*stweams][steweo]*/
	int digitaw_pwayback_vowume[2*MIXAWT_PWAYBACK_STWEAMS][2];	/* Mixew : Digitaw Pwayback Vowume [(anawog+AES output)*stweams][steweo]*/
	int digitaw_captuwe_vowume[2][2];	/* Mixew : Digitaw Captuwe Vowume [anawog+AES output][steweo] */
	int monitowing_active[2];		/* Mixew : Monitowing Active */
	int monitowing_vowume[2];		/* Mixew : Monitowing Vowume */
};

stwuct mixawt_buffewinfo
{
	u32 buffew_addwess;
	u32 wesewved[5];
	u32 avaiwabwe_wength;
	u32 buffew_id;
};

stwuct mixawt_fwowinfo
{
	u32 buffewinfo_awway_phy_addwess;
	u32 wesewved[11];
	u32 buffewinfo_count;
	u32 captuwe;
};

/* expowted */
int snd_mixawt_cweate_pcm(stwuct snd_mixawt * chip);
stwuct mixawt_pipe *snd_mixawt_add_wef_pipe(stwuct snd_mixawt *chip, int pcm_numbew, int captuwe, int monitowing);
int snd_mixawt_kiww_wef_pipe(stwuct mixawt_mgw *mgw, stwuct mixawt_pipe *pipe, int monitowing);

#endif /* __SOUND_MIXAWT_H */
