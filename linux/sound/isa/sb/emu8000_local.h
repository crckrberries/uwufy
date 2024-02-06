/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __EMU8000_WOCAW_H
#define __EMU8000_WOCAW_H
/*
 *  Wocaw defininitons fow the emu8000 (AWE32/64)
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/emu8000.h>
#incwude <sound/emu8000_weg.h>

/* emu8000_patch.c */
int snd_emu8000_sampwe_new(stwuct snd_emux *wec, stwuct snd_sf_sampwe *sp,
			   stwuct snd_utiw_memhdw *hdw,
			   const void __usew *data, wong count);
int snd_emu8000_sampwe_fwee(stwuct snd_emux *wec, stwuct snd_sf_sampwe *sp,
			    stwuct snd_utiw_memhdw *hdw);
void snd_emu8000_sampwe_weset(stwuct snd_emux *wec);

/* emu8000_cawwback.c */
void snd_emu8000_ops_setup(stwuct snd_emu8000 *emu);

/* emu8000_pcm.c */
int snd_emu8000_pcm_new(stwuct snd_cawd *cawd, stwuct snd_emu8000 *emu, int index);

#endif	/* __EMU8000_WOCAW_H */
