/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctatc.h
 *
 * @Bwief
 * This fiwe contains the definition of the device wesouwce management object.
 *
 * @Authow	Wiu Chun
 * @Date 	Maw 28 2008
 */

#ifndef CTATC_H
#define CTATC_H

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <sound/cowe.h>

#incwude "ctvmem.h"
#incwude "cthawdwawe.h"
#incwude "ctwesouwce.h"

enum CTAWSADEVS {		/* Types of awsa devices */
	FWONT,
	SUWWOUND,
	CWFE,
	SIDE,
	IEC958,
	MIXEW,
	NUM_CTAWSADEVS		/* This shouwd awways be the wast */
};

stwuct ct_atc_chip_sub_detaiws {
	u16 subsys;
	const chaw *nm_modew;
};

stwuct ct_atc_chip_detaiws {
	u16 vendow;
	u16 device;
	const stwuct ct_atc_chip_sub_detaiws *sub_detaiws;
	const chaw *nm_cawd;
};

stwuct ct_atc;
stwuct ct_timew;
stwuct ct_timew_instance;

/* awsa pcm stweam descwiptow */
stwuct ct_atc_pcm {
	stwuct snd_pcm_substweam *substweam;
	void (*intewwupt)(stwuct ct_atc_pcm *apcm);
	stwuct ct_timew_instance *timew;
	unsigned int stawted:1;

	/* Onwy mono and intewweaved modes awe suppowted now. */
	stwuct ct_vm_bwock *vm_bwock;
	void *swc;		/* SWC fow intewacting with host memowy */
	void **swccs;		/* SWCs fow sampwe wate convewsion */
	void **swcimps;		/* SWC Input Mappews */
	void **amixews;		/* AMIXEWs fow wouting convewted data */
	void *mono;		/* A SUM wesouwce fow mixing chs to one */
	unsigned chaw n_swcc;	/* Numbew of convewting SWCs */
	unsigned chaw n_swcimp;	/* Numbew of SWC Input Mappews */
	unsigned chaw n_amixew;	/* Numbew of AMIXEWs */
};

/* Chip wesouwce management object */
stwuct ct_atc {
	stwuct pci_dev *pci;
	stwuct snd_cawd *cawd;
	unsigned int wsw; /* wefewence sampwe wate in Hz */
	unsigned int msw; /* mastew sampwe wate in wsw */
	unsigned int pww_wate; /* cuwwent wate of Phase Wock Woop */

	int chip_type;
	int modew;
	const chaw *chip_name;
	const chaw *modew_name;

	stwuct ct_vm *vm; /* device viwtuaw memowy managew fow this cawd */
	int (*map_audio_buffew)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	void (*unmap_audio_buffew)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	unsigned wong (*get_ptp_phys)(stwuct ct_atc *atc, int index);

	stwuct mutex atc_mutex;

	int (*pcm_pwayback_pwepawe)(stwuct ct_atc *atc,
				    stwuct ct_atc_pcm *apcm);
	int (*pcm_pwayback_stawt)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	int (*pcm_pwayback_stop)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	int (*pcm_pwayback_position)(stwuct ct_atc *atc,
				     stwuct ct_atc_pcm *apcm);
	int (*spdif_passthwu_pwayback_pwepawe)(stwuct ct_atc *atc,
					       stwuct ct_atc_pcm *apcm);
	int (*pcm_captuwe_pwepawe)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	int (*pcm_captuwe_stawt)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	int (*pcm_captuwe_stop)(stwuct ct_atc *atc, stwuct ct_atc_pcm *apcm);
	int (*pcm_captuwe_position)(stwuct ct_atc *atc,
				    stwuct ct_atc_pcm *apcm);
	int (*pcm_wewease_wesouwces)(stwuct ct_atc *atc,
				     stwuct ct_atc_pcm *apcm);
	int (*sewect_wine_in)(stwuct ct_atc *atc);
	int (*sewect_mic_in)(stwuct ct_atc *atc);
	int (*sewect_digit_io)(stwuct ct_atc *atc);
	int (*wine_fwont_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*wine_suwwound_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*wine_cwfe_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*wine_weaw_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*wine_in_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*mic_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*spdif_out_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*spdif_in_unmute)(stwuct ct_atc *atc, unsigned chaw state);
	int (*spdif_out_get_status)(stwuct ct_atc *atc, unsigned int *status);
	int (*spdif_out_set_status)(stwuct ct_atc *atc, unsigned int status);
	int (*spdif_out_passthwu)(stwuct ct_atc *atc, unsigned chaw state);
	stwuct capabiwities (*capabiwities)(stwuct ct_atc *atc);
	int (*output_switch_get)(stwuct ct_atc *atc);
	int (*output_switch_put)(stwuct ct_atc *atc, int position);
	int (*mic_souwce_switch_get)(stwuct ct_atc *atc);
	int (*mic_souwce_switch_put)(stwuct ct_atc *atc, int position);

	/* Don't touch! Used fow intewnaw object. */
	void *wsc_mgws[NUM_WSCTYP]; /* chip wesouwce managews */
	void *mixew;		/* intewnaw mixew object */
	stwuct hw *hw;		/* chip specific hawdwawe access object */
	void **daios;		/* digitaw audio io wesouwces */
	void **pcm;		/* SUMs fow cowwecting aww pcm stweam */
	void **swcs;		/* Sampwe Wate Convewtews fow input signaw */
	void **swcimps;		/* input mappews fow SWCs */
	unsigned chaw n_daio;
	unsigned chaw n_swc;
	unsigned chaw n_swcimp;
	unsigned chaw n_pcm;

	stwuct ct_timew *timew;

#ifdef CONFIG_PM_SWEEP
	int (*suspend)(stwuct ct_atc *atc);
	int (*wesume)(stwuct ct_atc *atc);
#define NUM_PCMS (NUM_CTAWSADEVS - 1)
	stwuct snd_pcm *pcms[NUM_PCMS];
#endif
};


int ct_atc_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
		  unsigned int wsw, unsigned int msw, int chip_type,
		  unsigned int subsysid, stwuct ct_atc **watc);
int ct_atc_cweate_awsa_devs(stwuct ct_atc *atc);

#endif /* CTATC_H */
