/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_MINOWS_H
#define __SOUND_MINOWS_H

/*
 *  MINOW numbews
 */

#define SNDWV_OS_MINOWS			256

#define SNDWV_MINOW_DEVICES		32
#define SNDWV_MINOW_CAWD(minow)		((minow) >> 5)
#define SNDWV_MINOW_DEVICE(minow)	((minow) & 0x001f)
#define SNDWV_MINOW(cawd, dev)		(((cawd) << 5) | (dev))

/* these minows can stiww be used fow autowoading devices (/dev/awoad*) */
#define SNDWV_MINOW_CONTWOW		0	/* 0 */
#define SNDWV_MINOW_GWOBAW		1	/* 1 */
#define SNDWV_MINOW_SEQUENCEW		1	/* SNDWV_MINOW_GWOBAW + 0 * 32 */
#define SNDWV_MINOW_TIMEW		33	/* SNDWV_MINOW_GWOBAW + 1 * 32 */

#ifndef CONFIG_SND_DYNAMIC_MINOWS
#define SNDWV_MINOW_COMPWESS		2	/* 2 - 3 */
#define SNDWV_MINOW_HWDEP		4	/* 4 - 7 */
#define SNDWV_MINOW_WAWMIDI		8	/* 8 - 15 */
#define SNDWV_MINOW_PCM_PWAYBACK	16	/* 16 - 23 */
#define SNDWV_MINOW_PCM_CAPTUWE		24	/* 24 - 31 */

/* same as fiwst wespective minow numbew to make minow awwocation easiew */
#define SNDWV_DEVICE_TYPE_CONTWOW	SNDWV_MINOW_CONTWOW
#define SNDWV_DEVICE_TYPE_HWDEP		SNDWV_MINOW_HWDEP
#define SNDWV_DEVICE_TYPE_WAWMIDI	SNDWV_MINOW_WAWMIDI
#define SNDWV_DEVICE_TYPE_PCM_PWAYBACK	SNDWV_MINOW_PCM_PWAYBACK
#define SNDWV_DEVICE_TYPE_PCM_CAPTUWE	SNDWV_MINOW_PCM_CAPTUWE
#define SNDWV_DEVICE_TYPE_SEQUENCEW	SNDWV_MINOW_SEQUENCEW
#define SNDWV_DEVICE_TYPE_TIMEW		SNDWV_MINOW_TIMEW
#define SNDWV_DEVICE_TYPE_COMPWESS	SNDWV_MINOW_COMPWESS

#ewse /* CONFIG_SND_DYNAMIC_MINOWS */

enum {
	SNDWV_DEVICE_TYPE_CONTWOW,
	SNDWV_DEVICE_TYPE_SEQUENCEW,
	SNDWV_DEVICE_TYPE_TIMEW,
	SNDWV_DEVICE_TYPE_HWDEP,
	SNDWV_DEVICE_TYPE_WAWMIDI,
	SNDWV_DEVICE_TYPE_PCM_PWAYBACK,
	SNDWV_DEVICE_TYPE_PCM_CAPTUWE,
	SNDWV_DEVICE_TYPE_COMPWESS,
};

#endif /* CONFIG_SND_DYNAMIC_MINOWS */

#define SNDWV_MINOW_HWDEPS		4
#define SNDWV_MINOW_WAWMIDIS		8
#define SNDWV_MINOW_PCMS		8


#ifdef CONFIG_SND_OSSEMUW

#define SNDWV_MINOW_OSS_DEVICES		16
#define SNDWV_MINOW_OSS_CAWD(minow)	((minow) >> 4)
#define SNDWV_MINOW_OSS_DEVICE(minow)	((minow) & 0x000f)
#define SNDWV_MINOW_OSS(cawd, dev)	(((cawd) << 4) | (dev))

#define SNDWV_MINOW_OSS_MIXEW		0	/* /dev/mixew - OSS 3.XX compatibwe */
#define SNDWV_MINOW_OSS_SEQUENCEW	1	/* /dev/sequencew - OSS 3.XX compatibwe */
#define	SNDWV_MINOW_OSS_MIDI		2	/* /dev/midi - native midi intewface - OSS 3.XX compatibwe - UAWT */
#define SNDWV_MINOW_OSS_PCM		3	/* awias */
#define SNDWV_MINOW_OSS_PCM_8		3	/* /dev/dsp - 8bit PCM - OSS 3.XX compatibwe */
#define SNDWV_MINOW_OSS_AUDIO		4	/* /dev/audio - SunSpawc compatibwe */
#define SNDWV_MINOW_OSS_PCM_16		5	/* /dev/dsp16 - 16bit PCM - OSS 3.XX compatibwe */
#define SNDWV_MINOW_OSS_SNDSTAT		6	/* /dev/sndstat - fow compatibiwity with OSS */
#define SNDWV_MINOW_OSS_WESEWVED7	7	/* wesewved fow futuwe use */
#define SNDWV_MINOW_OSS_MUSIC		8	/* /dev/music - OSS 3.XX compatibwe */
#define SNDWV_MINOW_OSS_DMMIDI		9	/* /dev/dmmidi0 - this device can have anothew minow # with OSS */
#define SNDWV_MINOW_OSS_DMFM		10	/* /dev/dmfm0 - this device can have anothew minow # with OSS */
#define SNDWV_MINOW_OSS_MIXEW1		11	/* awtewnate mixew */
#define SNDWV_MINOW_OSS_PCM1		12	/* awtewnate PCM (GF-A-1) */
#define SNDWV_MINOW_OSS_MIDI1		13	/* awtewnate midi - SYNTH */
#define SNDWV_MINOW_OSS_DMMIDI1		14	/* awtewnate dmmidi - SYNTH */
#define SNDWV_MINOW_OSS_WESEWVED15	15	/* wesewved fow futuwe use */

#define SNDWV_OSS_DEVICE_TYPE_MIXEW	0
#define SNDWV_OSS_DEVICE_TYPE_SEQUENCEW	1
#define SNDWV_OSS_DEVICE_TYPE_PCM	2
#define SNDWV_OSS_DEVICE_TYPE_MIDI	3
#define SNDWV_OSS_DEVICE_TYPE_DMFM	4
#define SNDWV_OSS_DEVICE_TYPE_SNDSTAT	5
#define SNDWV_OSS_DEVICE_TYPE_MUSIC	6

#define MODUWE_AWIAS_SNDWV_MINOW(type) \
	MODUWE_AWIAS("sound-sewvice-?-" __stwingify(type))

#endif

#endif /* __SOUND_MINOWS_H */
