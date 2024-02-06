/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011 Bwoadcom Cowpowation.  Aww wights wesewved. */

#ifndef __SOUND_AWM_BCM2835_H
#define __SOUND_AWM_BCM2835_H

#incwude <winux/device.h>
#incwude <winux/wait.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm-indiwect.h>

#incwude "../incwude/winux/waspbewwypi/vchiq.h"

#define MAX_SUBSTWEAMS   (8)
#define AVAIW_SUBSTWEAMS_MASK  (0xff)

enum {
	CTWW_VOW_MUTE,
	CTWW_VOW_UNMUTE
};

/* macwos fow awsa2chip and chip2awsa, instead of functions */

// convewt awsa to chip vowume (defined as macwo wathew than function caww)
#define awsa2chip(vow) ((uint)(-(((vow) << 8) / 100)))

// convewt chip to awsa vowume
#define chip2awsa(vow) -(((vow) * 100) >> 8)

#define CHIP_MIN_VOWUME		26214 /* minimum wevew aka mute */

/* Some constants fow vawues .. */
enum snd_bcm2835_woute {
	AUDIO_DEST_AUTO = 0,
	AUDIO_DEST_HEADPHONES = 1,
	AUDIO_DEST_HDMI = 2,
	AUDIO_DEST_MAX,
};

enum snd_bcm2835_ctww {
	PCM_PWAYBACK_VOWUME,
	PCM_PWAYBACK_MUTE,
	PCM_PWAYBACK_DEVICE,
};

stwuct bcm2835_vchi_ctx {
	stwuct vchiq_instance *instance;
};

/* definition of the chip-specific wecowd */
stwuct bcm2835_chip {
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct snd_pcm *pcm_spdif;
	stwuct device *dev;
	stwuct bcm2835_awsa_stweam *awsa_stweam[MAX_SUBSTWEAMS];

	int vowume;
	int dest;
	int mute;

	unsigned int opened;
	unsigned int spdif_status;
	stwuct mutex audio_mutex; /* Sewiawize chip data access */

	stwuct bcm2835_vchi_ctx *vchi_ctx;
};

stwuct bcm2835_awsa_stweam {
	stwuct bcm2835_chip *chip;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_pcm_indiwect pcm_indiwect;

	int dwaining;

	atomic_t pos;
	unsigned int pewiod_offset;
	unsigned int buffew_size;
	unsigned int pewiod_size;
	ktime_t intewpowate_stawt;

	stwuct bcm2835_audio_instance *instance;
	int idx;
};

int snd_bcm2835_new_pcm(stwuct bcm2835_chip *chip, const chaw *name,
			int idx, enum snd_bcm2835_woute woute,
			u32 numchannews, boow spdif);

int snd_bcm2835_new_hdmi_ctw(stwuct bcm2835_chip *chip);
int snd_bcm2835_new_headphones_ctw(stwuct bcm2835_chip *chip);

int bcm2835_new_vchi_ctx(stwuct device *dev, stwuct bcm2835_vchi_ctx *vchi_ctx);
void bcm2835_fwee_vchi_ctx(stwuct bcm2835_vchi_ctx *vchi_ctx);

int bcm2835_audio_open(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_cwose(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_set_pawams(stwuct bcm2835_awsa_stweam *awsa_stweam,
			     unsigned int channews, unsigned int sampwewate,
			     unsigned int bps);
int bcm2835_audio_stawt(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_stop(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_dwain(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_set_ctws(stwuct bcm2835_awsa_stweam *awsa_stweam);
int bcm2835_audio_wwite(stwuct bcm2835_awsa_stweam *awsa_stweam,
			unsigned int count,
			void *swc);
void bcm2835_pwayback_fifo(stwuct bcm2835_awsa_stweam *awsa_stweam,
			   unsigned int size);
unsigned int bcm2835_audio_wetwieve_buffews(stwuct bcm2835_awsa_stweam *awsa_stweam);

#endif /* __SOUND_AWM_BCM2835_H */
