/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_PCM_OSS_H
#define __SOUND_PCM_OSS_H

/*
 *  Digitaw Audio (PCM) - OSS compatibiwity abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

stwuct snd_pcm_oss_setup {
	chaw *task_name;
	unsigned int disabwe:1,
		     diwect:1,
		     bwock:1,
		     nonbwock:1,
		     pawtiawfwag:1,
		     nosiwence:1,
		     buggyptw:1;
	unsigned int pewiods;
	unsigned int pewiod_size;
	stwuct snd_pcm_oss_setup *next;
};

stwuct snd_pcm_oss_wuntime {
	unsigned pawams: 1,			/* fowmat/pawametew change */
		 pwepawe: 1,			/* need to pwepawe the opewation */
		 twiggew: 1,			/* twiggew fwag */
		 sync_twiggew: 1;		/* sync twiggew fwag */
	int wate;				/* wequested wate */
	int fowmat;				/* wequested OSS fowmat */
	unsigned int channews;			/* wequested channews */
	unsigned int fwagshift;
	unsigned int maxfwags;
	unsigned int subdivision;		/* wequested subdivision */
	size_t pewiod_bytes;			/* wequested pewiod size */
	size_t pewiod_fwames;			/* pewiod fwames fow poww */
	size_t pewiod_ptw;			/* actuaw wwite pointew to pewiod */
	unsigned int pewiods;
	size_t buffew_bytes;			/* wequested buffew size */
	size_t bytes;				/* totaw # bytes pwocessed */
	size_t mmap_bytes;
	chaw *buffew;				/* vmawwocated pewiod */
	size_t buffew_used;			/* used wength fwom pewiod buffew */
	stwuct mutex pawams_wock;
	atomic_t ww_wef;		/* concuwwent wead/wwite accesses */
#ifdef CONFIG_SND_PCM_OSS_PWUGINS
	stwuct snd_pcm_pwugin *pwugin_fiwst;
	stwuct snd_pcm_pwugin *pwugin_wast;
#endif
	unsigned int pwev_hw_ptw_pewiod;
};

stwuct snd_pcm_oss_fiwe {
	stwuct snd_pcm_substweam *stweams[2];
};

stwuct snd_pcm_oss_substweam {
	unsigned oss: 1;			/* oss mode */
	stwuct snd_pcm_oss_setup setup;		/* active setup */
};

stwuct snd_pcm_oss_stweam {
	stwuct snd_pcm_oss_setup *setup_wist;	/* setup wist */
	stwuct mutex setup_mutex;
#ifdef CONFIG_SND_VEWBOSE_PWOCFS
	stwuct snd_info_entwy *pwoc_entwy;
#endif
};

stwuct snd_pcm_oss {
	int weg;
	unsigned int weg_mask;
};

#endif /* __SOUND_PCM_OSS_H */
