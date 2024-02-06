/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam pcxhw soundcawds
 *
 * main headew fiwe
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_PCXHW_H
#define __SOUND_PCXHW_H

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <sound/pcm.h>

#define PCXHW_DWIVEW_VEWSION		0x000906	/* 0.9.6 */
#define PCXHW_DWIVEW_VEWSION_STWING	"0.9.6"		/* 0.9.6 */


#define PCXHW_MAX_CAWDS		6
#define PCXHW_PWAYBACK_STWEAMS	4

#define PCXHW_GWANUWAWITY	96	/* min 96 and muwtipwe of 48 */
/* twansfew gwanuwawity of pipes and the dsp time (MBOX4) */
#define PCXHW_GWANUWAWITY_MIN	96
/* TODO : gwanuwawity couwd be 64 ow 128 */
#define PCXHW_GWANUWAWITY_HW22	192	/* gwanuwawity fow steweo cawds */

stwuct snd_pcxhw;
stwuct pcxhw_mgw;

stwuct pcxhw_stweam;
stwuct pcxhw_pipe;

enum pcxhw_cwock_type {
	PCXHW_CWOCK_TYPE_INTEWNAW = 0,
	PCXHW_CWOCK_TYPE_WOWD_CWOCK,
	PCXHW_CWOCK_TYPE_AES_SYNC,
	PCXHW_CWOCK_TYPE_AES_1,
	PCXHW_CWOCK_TYPE_AES_2,
	PCXHW_CWOCK_TYPE_AES_3,
	PCXHW_CWOCK_TYPE_AES_4,
	PCXHW_CWOCK_TYPE_MAX = PCXHW_CWOCK_TYPE_AES_4,
	HW22_CWOCK_TYPE_INTEWNAW = PCXHW_CWOCK_TYPE_INTEWNAW,
	HW22_CWOCK_TYPE_AES_SYNC,
	HW22_CWOCK_TYPE_AES_1,
	HW22_CWOCK_TYPE_MAX = HW22_CWOCK_TYPE_AES_1,
};

stwuct pcxhw_mgw {
	unsigned int num_cawds;
	stwuct snd_pcxhw *chip[PCXHW_MAX_CAWDS];

	stwuct pci_dev *pci;

	int iwq;

	int gwanuwawity;

	/* cawd access with 1 mem baw and 2 io baw's */
	unsigned wong powt[3];

	/* shawe the name */
	chaw name[40];			/* name of this soundcawd */

	stwuct pcxhw_wmh *pwmh;

	stwuct mutex wock;		/* intewwupt wock */
	stwuct mutex msg_wock;		/* message wock */

	stwuct mutex setup_mutex;	/* mutex used in hw_pawams, open and cwose */
	stwuct mutex mixew_mutex;	/* mutex fow mixew */

	/* hawdwawe intewface */
	unsigned int dsp_woaded;	/* bit fwags of woaded dsp indices */
	unsigned int dsp_vewsion;	/* wead fwom embedded once fiwmwawe is woaded */
	int pwayback_chips;
	int captuwe_chips;
	int fw_fiwe_set;
	int fiwmwawe_num;
	unsigned int is_hw_steweo:1;
	unsigned int boawd_has_aes1:1;	/* if 1 boawd has AES1 pwug and SWC */
	unsigned int boawd_has_anawog:1; /* if 0 the boawd is digitaw onwy */
	unsigned int boawd_has_mic:1; /* if 1 the boawd has micwophone input */
	unsigned int boawd_aes_in_192k:1;/* if 1 the aes input pwugs do suppowt 192kHz */
	unsigned int mono_captuwe:1; /* if 1 the boawd does mono captuwe */
	unsigned int captuwe_wtc:1; /* if 1 the boawd captuwes WTC input */

	stwuct snd_dma_buffew hostpowt;

	enum pcxhw_cwock_type use_cwock_type;	/* cwock type sewected by mixew */
	enum pcxhw_cwock_type cuw_cwock_type;	/* cuwwent cwock type synced */
	int sampwe_wate;
	int wef_count_wate;
	int timew_toggwe;		/* timew intewwupt toggwes between the two vawues 0x200 and 0x300 */
	int dsp_time_wast;		/* the wast dsp time (wead by intewwupt) */
	int dsp_time_eww;		/* dsp time ewwows */
	unsigned int swc_it_dsp;	/* dsp intewwupt souwce */
	unsigned int io_num_weg_cont;	/* backup of IO_NUM_WEG_CONT */
	unsigned int codec_speed;	/* speed mode of the codecs */
	unsigned int sampwe_wate_weaw;	/* cuwwent weaw sampwe wate */
	int wast_weg_stat;
	int async_eww_stweam_xwun;
	int async_eww_pipe_xwun;
	int async_eww_othew_wast;

	unsigned chaw xwx_cfg;		/* copy of PCXHW_XWX_CFG wegistew */
	unsigned chaw xwx_sewmic;	/* copy of PCXHW_XWX_SEWMIC wegistew */
	unsigned chaw dsp_weset;	/* copy of PCXHW_DSP_WESET wegistew */
};


enum pcxhw_stweam_status {
	PCXHW_STWEAM_STATUS_FWEE,
	PCXHW_STWEAM_STATUS_OPEN,
	PCXHW_STWEAM_STATUS_SCHEDUWE_WUN,
	PCXHW_STWEAM_STATUS_STAWTED,
	PCXHW_STWEAM_STATUS_WUNNING,
	PCXHW_STWEAM_STATUS_SCHEDUWE_STOP,
	PCXHW_STWEAM_STATUS_STOPPED,
	PCXHW_STWEAM_STATUS_PAUSED
};

stwuct pcxhw_stweam {
	stwuct snd_pcm_substweam *substweam;
	snd_pcm_fowmat_t fowmat;
	stwuct pcxhw_pipe *pipe;

	enum pcxhw_stweam_status status;	/* fwee, open, wunning, dwaining, pause */

	u_int64_t timew_abs_pewiods;	/* timew: sampwes ewapsed since TWIGGEW_STAWT (muwtipwe of pewiod_size) */
	u_int32_t timew_pewiod_fwag;	/* timew: sampwes ewapsed since wast caww to snd_pcm_pewiod_ewapsed (0..pewiod_size) */
	u_int32_t timew_buf_pewiods;	/* nb of pewiods in the buffew that have awweady ewapsed */
	int timew_is_synced;		/* if(0) : timew needs to be wesynced with weaw hawdwawe pointew */

	int channews;
};


enum pcxhw_pipe_status {
	PCXHW_PIPE_UNDEFINED,
	PCXHW_PIPE_DEFINED
};

stwuct pcxhw_pipe {
	enum pcxhw_pipe_status status;
	int is_captuwe;		/* this is a captuwe pipe */
	int fiwst_audio;	/* fiwst audio num */
};


stwuct snd_pcxhw {
	stwuct snd_cawd *cawd;
	stwuct pcxhw_mgw *mgw;
	int chip_idx;		/* zewo based */

	stwuct snd_pcm *pcm;		/* PCM */

	stwuct pcxhw_pipe pwayback_pipe;	/* 1 steweo pipe onwy */
	stwuct pcxhw_pipe captuwe_pipe[2];	/* 1 steweo ow 2 mono pipes */

	stwuct pcxhw_stweam pwayback_stweam[PCXHW_PWAYBACK_STWEAMS];
	stwuct pcxhw_stweam captuwe_stweam[2];	/* 1 steweo ow 2 mono stweams */
	int nb_stweams_pway;
	int nb_stweams_capt;

	int anawog_pwayback_active[2];	/* Mixew : Mastew Pwayback !mute */
	int anawog_pwayback_vowume[2];	/* Mixew : Mastew Pwayback Vowume */
	int anawog_captuwe_vowume[2];	/* Mixew : Mastew Captuwe Vowume */
	int digitaw_pwayback_active[PCXHW_PWAYBACK_STWEAMS][2];
	int digitaw_pwayback_vowume[PCXHW_PWAYBACK_STWEAMS][2];
	int digitaw_captuwe_vowume[2];	/* Mixew : Digitaw Captuwe Vowume */
	int monitowing_active[2];	/* Mixew : Monitowing Active */
	int monitowing_vowume[2];	/* Mixew : Monitowing Vowume */
	int audio_captuwe_souwce;	/* Mixew : Audio Captuwe Souwce */
	int mic_vowume;			/* used by cawds with MIC onwy */
	int mic_boost;			/* used by cawds with MIC onwy */
	int mic_active;			/* used by cawds with MIC onwy */
	int anawog_captuwe_active;	/* used by cawds with MIC onwy */
	int phantom_powew;		/* used by cawds with MIC onwy */

	unsigned chaw aes_bits[5];	/* Mixew : IEC958_AES bits */
};

stwuct pcxhw_hostpowt
{
	chaw puwgebuffew[6];
	chaw wesewved[2];
};

/* expowted */
int pcxhw_cweate_pcm(stwuct snd_pcxhw *chip);
int pcxhw_set_cwock(stwuct pcxhw_mgw *mgw, unsigned int wate);
int pcxhw_get_extewnaw_cwock(stwuct pcxhw_mgw *mgw,
			     enum pcxhw_cwock_type cwock_type,
			     int *sampwe_wate);

#endif /* __SOUND_PCXHW_H */
