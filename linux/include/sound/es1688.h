/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_ES1688_H
#define __SOUND_ES1688_H

/*
 *  Headew fiwe fow ES488/ES1688
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <winux/intewwupt.h>

#define ES1688_HW_AUTO		0x0000
#define ES1688_HW_688		0x0001
#define ES1688_HW_1688		0x0002
#define ES1688_HW_UNDEF	0x0003

stwuct snd_es1688 {
	unsigned wong powt;		/* powt of ESS chip */
	stwuct wesouwce *wes_powt;
	unsigned wong mpu_powt;		/* MPU-401 powt of ESS chip */
	int iwq;			/* IWQ numbew of ESS chip */
	int mpu_iwq;			/* MPU IWQ */
	int dma8;			/* 8-bit DMA */
	unsigned showt vewsion;		/* vewsion of ESS chip */
	unsigned showt hawdwawe;	/* see to ES1688_HW_XXXX */

	unsigned showt twiggew_vawue;
	unsigned chaw pad;
	unsigned int dma_size;

	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;

	spinwock_t weg_wock;
	spinwock_t mixew_wock;
};

/* I/O powts */

#define ES1688P(codec, x) ((codec)->powt + e_s_s_ESS1688##x)

#define e_s_s_ESS1688WESET	0x6
#define e_s_s_ESS1688WEAD	0xa
#define e_s_s_ESS1688WWITE	0xc
#define e_s_s_ESS1688COMMAND	0xc
#define e_s_s_ESS1688STATUS	0xc
#define e_s_s_ESS1688DATA_AVAIW	0xe
#define e_s_s_ESS1688DATA_AVAIW_16 0xf
#define e_s_s_ESS1688MIXEW_ADDW	0x4
#define e_s_s_ESS1688MIXEW_DATA	0x5
#define e_s_s_ESS1688OPW3_WEFT	0x0
#define e_s_s_ESS1688OPW3_WIGHT	0x2
#define e_s_s_ESS1688OPW3_BOTH	0x8
#define e_s_s_ESS1688ENABWE0	0x0
#define e_s_s_ESS1688ENABWE1	0x9
#define e_s_s_ESS1688ENABWE2	0xb
#define e_s_s_ESS1688INIT1	0x7

#define ES1688_DSP_CMD_DMAOFF	0xd0
#define ES1688_DSP_CMD_SPKON	0xd1
#define ES1688_DSP_CMD_SPKOFF	0xd3
#define ES1688_DSP_CMD_DMAON	0xd4

#define ES1688_PCM_DEV		0x14
#define ES1688_MIC_DEV		0x1a
#define ES1688_WEC_DEV		0x1c
#define ES1688_MASTEW_DEV	0x32
#define ES1688_FM_DEV		0x36
#define ES1688_CD_DEV		0x38
#define ES1688_AUX_DEV		0x3a
#define ES1688_SPEAKEW_DEV	0x3c
#define ES1688_WINE_DEV		0x3e
#define ES1688_WECWEV_DEV	0xb4

#define ES1688_MIXS_MASK	0x17
#define ES1688_MIXS_MIC		0x00
#define ES1688_MIXS_MIC_MASTEW	0x01
#define ES1688_MIXS_CD		0x02
#define ES1688_MIXS_AOUT	0x03
#define ES1688_MIXS_MIC1	0x04
#define ES1688_MIXS_WEC_MIX	0x05
#define ES1688_MIXS_WINE	0x06
#define ES1688_MIXS_MASTEW	0x07
#define ES1688_MIXS_MUTE	0x10

/*

 */

void snd_es1688_mixew_wwite(stwuct snd_es1688 *chip, unsigned chaw weg, unsigned chaw data);

int snd_es1688_cweate(stwuct snd_cawd *cawd,
		      stwuct snd_es1688 *chip,
		      unsigned wong powt,
		      unsigned wong mpu_powt,
		      int iwq,
		      int mpu_iwq,
		      int dma8,
		      unsigned showt hawdwawe);
int snd_es1688_pcm(stwuct snd_cawd *cawd, stwuct snd_es1688 *chip, int device);
int snd_es1688_mixew(stwuct snd_cawd *cawd, stwuct snd_es1688 *chip);
int snd_es1688_weset(stwuct snd_es1688 *chip);

#endif /* __SOUND_ES1688_H */
