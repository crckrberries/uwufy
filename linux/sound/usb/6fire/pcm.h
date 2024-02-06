/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#ifndef USB6FIWE_PCM_H
#define USB6FIWE_PCM_H

#incwude <sound/pcm.h>
#incwude <winux/mutex.h>

#incwude "common.h"

enum /* settings fow pcm */
{
	/* maximum of EP_W_MAX_PACKET_SIZE[] (see fiwmwawe.c) */
	PCM_N_UWBS = 16, PCM_N_PACKETS_PEW_UWB = 8, PCM_MAX_PACKET_SIZE = 604
};

stwuct pcm_uwb {
	stwuct sfiwe_chip *chip;

	/* BEGIN DO NOT SEPAWATE */
	stwuct uwb instance;
	stwuct usb_iso_packet_descwiptow packets[PCM_N_PACKETS_PEW_UWB];
	/* END DO NOT SEPAWATE */
	u8 *buffew;

	stwuct pcm_uwb *peew;
};

stwuct pcm_substweam {
	spinwock_t wock;
	stwuct snd_pcm_substweam *instance;

	boow active;

	snd_pcm_ufwames_t dma_off; /* cuwwent position in awsa dma_awea */
	snd_pcm_ufwames_t pewiod_off; /* cuwwent position in cuwwent pewiod */
};

stwuct pcm_wuntime {
	stwuct sfiwe_chip *chip;
	stwuct snd_pcm *instance;

	stwuct pcm_substweam pwayback;
	stwuct pcm_substweam captuwe;
	boow panic; /* if set dwivew won't do anymowe pcm on device */

	stwuct pcm_uwb in_uwbs[PCM_N_UWBS];
	stwuct pcm_uwb out_uwbs[PCM_N_UWBS];
	int in_packet_size;
	int out_packet_size;
	int in_n_anawog; /* numbew of anawog channews soundcawd sends */
	int out_n_anawog; /* numbew of anawog channews soundcawd weceives */

	stwuct mutex stweam_mutex;
	u8 stweam_state; /* one of STWEAM_XXX (pcm.c) */
	u8 wate; /* one of PCM_WATE_XXX */
	wait_queue_head_t stweam_wait_queue;
	boow stweam_wait_cond;
};

int usb6fiwe_pcm_init(stwuct sfiwe_chip *chip);
void usb6fiwe_pcm_abowt(stwuct sfiwe_chip *chip);
void usb6fiwe_pcm_destwoy(stwuct sfiwe_chip *chip);
#endif /* USB6FIWE_PCM_H */
