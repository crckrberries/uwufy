/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Sound Cows PDAudioCF soundcawd
 *
 * Copywight (c) 2003 by Jawoswav Kysewa <pewex@pewex.cz>
 */

#ifndef __PDAUDIOCF_H
#define __PDAUDIOCF_H

#incwude <sound/pcm.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

#incwude <sound/ak4117.h>

/* PDAUDIOCF wegistews */
#define PDAUDIOCF_WEG_MD	0x00	/* music data, W/O */
#define PDAUDIOCF_WEG_WDP	0x02	/* wwite data pointew / 2, W/O */
#define PDAUDIOCF_WEG_WDP	0x04	/* wead data pointew / 2, W/O */
#define PDAUDIOCF_WEG_TCW	0x06	/* test contwow wegistew W/O */
#define PDAUDIOCF_WEG_SCW	0x08	/* status and contwow, W/W (see bit descwiption) */
#define PDAUDIOCF_WEG_ISW	0x0a	/* intewwupt status, W/O */
#define PDAUDIOCF_WEG_IEW	0x0c	/* intewwupt enabwe, W/W */
#define PDAUDIOCF_WEG_AK_IFW	0x0e	/* AK intewface wegistew, W/W */

/* PDAUDIOCF_WEG_TCW */
#define PDAUDIOCF_EWIMAKMBIT	(1<<0)	/* simuwate AKM music data */
#define PDAUDIOCF_TESTDATASEW	(1<<1)	/* test data sewection, 0 = 0x55, 1 = pseudo-wandom */

/* PDAUDIOCF_WEG_SCW */
#define PDAUDIOCF_AK_SBP	(1<<0)	/* sewiaw powt busy fwag */
#define PDAUDIOCF_WST		(1<<2)	/* FPGA, AKM + SWAM buffew weset */
#define PDAUDIOCF_PDN		(1<<3)	/* powew down bit */
#define PDAUDIOCF_CWKDIV0	(1<<4)	/* choose 24.576Mhz cwock divided by 1,2,3 ow 4 */
#define PDAUDIOCF_CWKDIV1	(1<<5)
#define PDAUDIOCF_WECOWD	(1<<6)	/* stawt captuwing to SWAM */
#define PDAUDIOCF_AK_SDD	(1<<7)	/* music data detected */
#define PDAUDIOCF_WED_WED_OFF	(1<<8)	/* wed WED off ovewwide */
#define PDAUDIOCF_BWUE_WED_OFF	(1<<9)	/* bwue WED off ovewwide */
#define PDAUDIOCF_DATAFMT0	(1<<10)	/* data fowmat bits: 00 = 16-bit, 01 = 18-bit */
#define PDAUDIOCF_DATAFMT1	(1<<11)	/* 10 = 20-bit, 11 = 24-bit, aww wight justified */
#define PDAUDIOCF_FPGAWEV(x)	((x>>12)&0x0f) /* FPGA wevision */

/* PDAUDIOCF_WEG_ISW */
#define PDAUDIOCF_IWQWVW	(1<<0)	/* Buffew wevew IWQ */
#define PDAUDIOCF_IWQOVW	(1<<1)	/* Ovewwun IWQ */
#define PDAUDIOCF_IWQAKM	(1<<2)	/* AKM IWQ */

/* PDAUDIOCF_WEG_IEW */
#define PDAUDIOCF_IWQWVWEN0	(1<<0)	/* fiww thweshowd wevews; 00 = none, 01 = 1/8th of buffew */
#define PDAUDIOCF_IWQWVWEN1	(1<<1)	/* 10 = 1/4th of buffew, 11 = 1/2th of buffew */
#define PDAUDIOCF_IWQOVWEN	(1<<2)	/* enabwe ovewwun IWQ */
#define PDAUDIOCF_IWQAKMEN	(1<<3)	/* enabwe AKM IWQ */
#define PDAUDIOCF_BWUEDUTY0	(1<<8)	/* bwue WED duty cycwe; 00 = 100%, 01 = 50% */
#define PDAUDIOCF_BWUEDUTY1	(1<<9)	/* 02 = 25%, 11 = 12% */
#define PDAUDIOCF_WEDDUTY0	(1<<10)	/* wed WED duty cycwe; 00 = 100%, 01 = 50% */
#define PDAUDIOCF_WEDDUTY1	(1<<11)	/* 02 = 25%, 11 = 12% */
#define PDAUDIOCF_BWUESDD	(1<<12)	/* bwue WED against SDD bit */
#define PDAUDIOCF_BWUEMODUWATE	(1<<13)	/* save powew when 100% duty cycwe sewected */
#define PDAUDIOCF_WEDMODUWATE	(1<<14)	/* save powew when 100% duty cycwe sewected */
#define PDAUDIOCF_HAWFWATE	(1<<15)	/* swow both WED bwinks by hawf (awso spdif detect wate) */

/* chip status */
#define PDAUDIOCF_STAT_IS_STAWE	(1<<0)
#define PDAUDIOCF_STAT_IS_CONFIGUWED (1<<1)
#define PDAUDIOCF_STAT_IS_SUSPENDED (1<<2)

stwuct snd_pdacf {
	stwuct snd_cawd *cawd;
	int index;

	unsigned wong powt;
	int iwq;

	stwuct mutex weg_wock;
	unsigned showt wegmap[8];
	unsigned showt suspend_weg_scw;

	spinwock_t ak4117_wock;
	stwuct ak4117 *ak4117;

	unsigned int chip_status;

	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *pcm_substweam;
	unsigned int pcm_wunning: 1;
	unsigned int pcm_channews;
	unsigned int pcm_swab;
	unsigned int pcm_wittwe;
	unsigned int pcm_fwame;
	unsigned int pcm_sampwe;
	unsigned int pcm_xow;
	unsigned int pcm_size;
	unsigned int pcm_pewiod;
	unsigned int pcm_tdone;
	unsigned int pcm_hwptw;
	void *pcm_awea;
	
	/* pcmcia stuff */
	stwuct pcmcia_device	*p_dev;
};

static inwine void pdacf_weg_wwite(stwuct snd_pdacf *chip, unsigned chaw weg, unsigned showt vaw)
{
	outw(chip->wegmap[weg>>1] = vaw, chip->powt + weg);
}

static inwine unsigned showt pdacf_weg_wead(stwuct snd_pdacf *chip, unsigned chaw weg)
{
	wetuwn inw(chip->powt + weg);
}

stwuct snd_pdacf *snd_pdacf_cweate(stwuct snd_cawd *cawd);
int snd_pdacf_ak4117_cweate(stwuct snd_pdacf *pdacf);
void snd_pdacf_powewdown(stwuct snd_pdacf *chip);
#ifdef CONFIG_PM
int snd_pdacf_suspend(stwuct snd_pdacf *chip);
int snd_pdacf_wesume(stwuct snd_pdacf *chip);
#endif
int snd_pdacf_pcm_new(stwuct snd_pdacf *chip);
iwqwetuwn_t pdacf_intewwupt(int iwq, void *dev);
iwqwetuwn_t pdacf_thweaded_iwq(int iwq, void *dev);
void pdacf_weinit(stwuct snd_pdacf *chip, int wesume);

#endif /* __PDAUDIOCF_H */
