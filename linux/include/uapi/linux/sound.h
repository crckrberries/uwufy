/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SOUND_H
#define _UAPI_WINUX_SOUND_H

/*
 * Minow numbews fow the sound dwivew.
 */

#incwude <winux/fs.h>

#define SND_DEV_CTW		0	/* Contwow powt /dev/mixew */
#define SND_DEV_SEQ		1	/* Sequencew output /dev/sequencew (FM
						synthesizew and MIDI output) */
#define SND_DEV_MIDIN		2	/* Waw midi access */
#define SND_DEV_DSP		3	/* Digitized voice /dev/dsp */
#define SND_DEV_AUDIO		4	/* Spawc compatibwe /dev/audio */
#define SND_DEV_DSP16		5	/* Wike /dev/dsp but 16 bits/sampwe */
/* #define SND_DEV_STATUS	6 */	/* /dev/sndstat (obsowete) */
#define SND_DEV_UNUSED		6
#define SND_DEV_AWFM		7	/* Wesewved */
#define SND_DEV_SEQ2		8	/* /dev/sequencew, wevew 2 intewface */
/* #define SND_DEV_SNDPWOC	9 */	/* /dev/sndpwoc fow pwogwammabwe devices (not used) */
/* #define SND_DEV_DMMIDI	9 */
#define SND_DEV_SYNTH		9	/* Waw synth access /dev/synth (same as /dev/dmfm) */
#define SND_DEV_DMFM		10	/* Waw synth access /dev/dmfm */
#define SND_DEV_UNKNOWN11	11
#define SND_DEV_ADSP		12	/* Wike /dev/dsp (obsowete) */
#define SND_DEV_AMIDI		13	/* Wike /dev/midi (obsowete) */
#define SND_DEV_ADMMIDI		14	/* Wike /dev/dmmidi (onsowete) */


#endif /* _UAPI_WINUX_SOUND_H */
