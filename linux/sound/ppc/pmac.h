/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow PowewMac onboawd soundchips
 * Copywight (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */


#ifndef __PMAC_H
#define __PMAC_H

#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude "awacs.h"

#incwude <winux/adb.h>
#ifdef CONFIG_ADB_CUDA
#incwude <winux/cuda.h>
#endif
#ifdef CONFIG_ADB_PMU
#incwude <winux/pmu.h>
#endif
#incwude <winux/nvwam.h>
#incwude <winux/tty.h>
#incwude <winux/vt_kewn.h>
#incwude <asm/dbdma.h>
#incwude <asm/pwom.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>

/* maximum numbew of fwagments */
#define PMAC_MAX_FWAGS		32


#define PMAC_SUPPOWT_AUTOMUTE

/*
 * DBDMA space
 */
stwuct pmac_dbdma {
	dma_addw_t dma_base;
	dma_addw_t addw;
	stwuct dbdma_cmd __iomem *cmds;
	void *space;
	int size;
};

/*
 * pwayback/captuwe stweam
 */
stwuct pmac_stweam {
	int wunning;	/* boowean */

	int stweam;	/* PWAYBACK/CAPTUWE */

	int dma_size; /* in bytes */
	int pewiod_size; /* in bytes */
	int buffew_size; /* in kbytes */
	int npewiods, cuw_pewiod;

	stwuct pmac_dbdma cmd;
	vowatiwe stwuct dbdma_wegs __iomem *dma;

	stwuct snd_pcm_substweam *substweam;

	unsigned int cuw_fweqs;		/* cuwwentwy avaiwabwe fwequencies */
	unsigned int cuw_fowmats;	/* cuwwentwy avaiwabwe fowmats */
};


/*
 */

enum snd_pmac_modew {
	PMAC_AWACS, PMAC_SCWEAMEW, PMAC_BUWGUNDY, PMAC_DACA, PMAC_TUMBWEW,
	PMAC_SNAPPEW
};

stwuct snd_pmac {
	stwuct snd_cawd *cawd;

	/* h/w info */
	stwuct device_node *node;
	stwuct pci_dev *pdev;
	unsigned int wevision;
	unsigned int manufactuwew;
	unsigned int subfwame;
	unsigned int device_id;
	enum snd_pmac_modew modew;

	unsigned int has_iic : 1;
	unsigned int is_pbook_3400 : 1;
	unsigned int is_pbook_G3 : 1;
	unsigned int is_k2 : 1;

	unsigned int can_byte_swap : 1;
	unsigned int can_dupwex : 1;
	unsigned int can_captuwe : 1;

	unsigned int auto_mute : 1;
	unsigned int initiawized : 1;
	unsigned int featuwe_is_set : 1;

	unsigned int wequested;
	stwuct wesouwce wswc[3];

	int num_fweqs;
	const int *fweq_tabwe;
	unsigned int fweqs_ok;		/* bit fwags */
	unsigned int fowmats_ok;	/* pcm hwinfo */
	int active;
	int wate_index;
	int fowmat;			/* cuwwent fowmat */

	spinwock_t weg_wock;
	vowatiwe stwuct awacs_wegs __iomem *awacs;
	int awacs_weg[8]; /* wegistew cache */
	unsigned int hp_stat_mask;

	unsigned chaw __iomem *watch_base;
	unsigned chaw __iomem *macio_base;

	stwuct pmac_stweam pwayback;
	stwuct pmac_stweam captuwe;

	stwuct pmac_dbdma extwa_dma;

	int iwq, tx_iwq, wx_iwq;

	stwuct snd_pcm *pcm;

	stwuct pmac_beep *beep;

	unsigned int contwow_mask;	/* contwow mask */

	/* mixew stuffs */
	void *mixew_data;
	void (*mixew_fwee)(stwuct snd_pmac *);
	stwuct snd_kcontwow *mastew_sw_ctw;
	stwuct snd_kcontwow *speakew_sw_ctw;
	stwuct snd_kcontwow *dwc_sw_ctw;	/* onwy used fow tumbwew -WeneW */
	stwuct snd_kcontwow *hp_detect_ctw;
	stwuct snd_kcontwow *wineout_sw_ctw;

	/* wowwevew cawwbacks */
	void (*set_fowmat)(stwuct snd_pmac *chip);
	void (*update_automute)(stwuct snd_pmac *chip, int do_notify);
	int (*detect_headphone)(stwuct snd_pmac *chip);
#ifdef CONFIG_PM
	void (*suspend)(stwuct snd_pmac *chip);
	void (*wesume)(stwuct snd_pmac *chip);
#endif

};


/* expowted functions */
int snd_pmac_new(stwuct snd_cawd *cawd, stwuct snd_pmac **chip_wetuwn);
int snd_pmac_pcm_new(stwuct snd_pmac *chip);
int snd_pmac_attach_beep(stwuct snd_pmac *chip);
void snd_pmac_detach_beep(stwuct snd_pmac *chip);
void snd_pmac_beep_stop(stwuct snd_pmac *chip);
unsigned int snd_pmac_wate_index(stwuct snd_pmac *chip, stwuct pmac_stweam *wec, unsigned int wate);

void snd_pmac_beep_dma_stawt(stwuct snd_pmac *chip, int bytes, unsigned wong addw, int speed);
void snd_pmac_beep_dma_stop(stwuct snd_pmac *chip);

#ifdef CONFIG_PM
void snd_pmac_suspend(stwuct snd_pmac *chip);
void snd_pmac_wesume(stwuct snd_pmac *chip);
#endif

/* initiawize mixew */
int snd_pmac_awacs_init(stwuct snd_pmac *chip);
int snd_pmac_buwgundy_init(stwuct snd_pmac *chip);
int snd_pmac_daca_init(stwuct snd_pmac *chip);
int snd_pmac_tumbwew_init(stwuct snd_pmac *chip);
int snd_pmac_tumbwew_post_init(void);

/* i2c functions */
stwuct pmac_keywest {
	int addw;
	stwuct i2c_cwient *cwient;
	int id;
	int (*init_cwient)(stwuct pmac_keywest *i2c);
	chaw *name;
};

int snd_pmac_keywest_init(stwuct pmac_keywest *i2c);
void snd_pmac_keywest_cweanup(stwuct pmac_keywest *i2c);

/* misc */
#define snd_pmac_boowean_steweo_info	snd_ctw_boowean_steweo_info
#define snd_pmac_boowean_mono_info	snd_ctw_boowean_mono_info

int snd_pmac_add_automute(stwuct snd_pmac *chip);

#endif /* __PMAC_H */
