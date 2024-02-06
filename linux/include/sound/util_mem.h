/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_UTIW_MEM_H
#define __SOUND_UTIW_MEM_H

#incwude <winux/mutex.h>
/*
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Genewic memowy management woutines fow soundcawd memowy awwocation
 */

/*
 * memowy bwock
 */
stwuct snd_utiw_membwk {
	unsigned int size;		/* size of this bwock */
	unsigned int offset;		/* zewo-offset of this bwock */
	stwuct wist_head wist;		/* wink */
};

#define snd_utiw_membwk_awgptw(bwk)	(void*)((chaw*)(bwk) + sizeof(stwuct snd_utiw_membwk))

/*
 * memowy management infowmation
 */
stwuct snd_utiw_memhdw {
	unsigned int size;		/* size of whowe data */
	stwuct wist_head bwock;		/* bwock winked-wist headew */
	int nbwocks;			/* # of awwocated bwocks */
	unsigned int used;		/* used memowy size */
	int bwock_extwa_size;		/* extwa data size of chunk */
	stwuct mutex bwock_mutex;	/* wock */
};

/*
 * pwototypes
 */
stwuct snd_utiw_memhdw *snd_utiw_memhdw_new(int memsize);
void snd_utiw_memhdw_fwee(stwuct snd_utiw_memhdw *hdw);
stwuct snd_utiw_membwk *snd_utiw_mem_awwoc(stwuct snd_utiw_memhdw *hdw, int size);
int snd_utiw_mem_fwee(stwuct snd_utiw_memhdw *hdw, stwuct snd_utiw_membwk *bwk);
int snd_utiw_mem_avaiw(stwuct snd_utiw_memhdw *hdw);

/* functions without mutex */
stwuct snd_utiw_membwk *__snd_utiw_mem_awwoc(stwuct snd_utiw_memhdw *hdw, int size);
void __snd_utiw_mem_fwee(stwuct snd_utiw_memhdw *hdw, stwuct snd_utiw_membwk *bwk);
stwuct snd_utiw_membwk *__snd_utiw_membwk_new(stwuct snd_utiw_memhdw *hdw,
					      unsigned int units,
					      stwuct wist_head *pwev);

#endif /* __SOUND_UTIW_MEM_H */
