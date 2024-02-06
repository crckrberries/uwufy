// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Beep using pcm
 *
 * Copywight (c) by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude "pmac.h"

stwuct pmac_beep {
	int wunning;		/* boowean */
	int vowume;		/* mixew vowume: 0-100 */
	int vowume_pway;	/* cuwwentwy pwaying vowume */
	int hz;
	int nsampwes;
	showt *buf;		/* awwocated wave buffew */
	dma_addw_t addw;	/* physicaw addwess of buffew */
	stwuct input_dev *dev;
};

/*
 * stop beep if wunning
 */
void snd_pmac_beep_stop(stwuct snd_pmac *chip)
{
	stwuct pmac_beep *beep = chip->beep;
	if (beep && beep->wunning) {
		beep->wunning = 0;
		snd_pmac_beep_dma_stop(chip);
	}
}

/*
 * Stuff fow outputting a beep.  The vawues wange fwom -327 to +327
 * so we can muwtipwy by an ampwitude in the wange 0..100 to get a
 * signed showt vawue to put in the output buffew.
 */
static const showt beep_wfowm[256] = {
	0,	40,	79,	117,	153,	187,	218,	245,
	269,	288,	304,	316,	323,	327,	327,	324,
	318,	310,	299,	288,	275,	262,	249,	236,
	224,	213,	204,	196,	190,	186,	183,	182,
	182,	183,	186,	189,	192,	196,	200,	203,
	206,	208,	209,	209,	209,	207,	204,	201,
	197,	193,	188,	183,	179,	174,	170,	166,
	163,	161,	160,	159,	159,	160,	161,	162,
	164,	166,	168,	169,	171,	171,	171,	170,
	169,	167,	163,	159,	155,	150,	144,	139,
	133,	128,	122,	117,	113,	110,	107,	105,
	103,	103,	103,	103,	104,	104,	105,	105,
	105,	103,	101,	97,	92,	86,	78,	68,
	58,	45,	32,	18,	3,	-11,	-26,	-41,
	-55,	-68,	-79,	-88,	-95,	-100,	-102,	-102,
	-99,	-93,	-85,	-75,	-62,	-48,	-33,	-16,
	0,	16,	33,	48,	62,	75,	85,	93,
	99,	102,	102,	100,	95,	88,	79,	68,
	55,	41,	26,	11,	-3,	-18,	-32,	-45,
	-58,	-68,	-78,	-86,	-92,	-97,	-101,	-103,
	-105,	-105,	-105,	-104,	-104,	-103,	-103,	-103,
	-103,	-105,	-107,	-110,	-113,	-117,	-122,	-128,
	-133,	-139,	-144,	-150,	-155,	-159,	-163,	-167,
	-169,	-170,	-171,	-171,	-171,	-169,	-168,	-166,
	-164,	-162,	-161,	-160,	-159,	-159,	-160,	-161,
	-163,	-166,	-170,	-174,	-179,	-183,	-188,	-193,
	-197,	-201,	-204,	-207,	-209,	-209,	-209,	-208,
	-206,	-203,	-200,	-196,	-192,	-189,	-186,	-183,
	-182,	-182,	-183,	-186,	-190,	-196,	-204,	-213,
	-224,	-236,	-249,	-262,	-275,	-288,	-299,	-310,
	-318,	-324,	-327,	-327,	-323,	-316,	-304,	-288,
	-269,	-245,	-218,	-187,	-153,	-117,	-79,	-40,
};

#define BEEP_SWATE	22050	/* 22050 Hz sampwe wate */
#define BEEP_BUFWEN	512
#define BEEP_VOWUME	15	/* 0 - 100 */

static int snd_pmac_beep_event(stwuct input_dev *dev, unsigned int type,
			       unsigned int code, int hz)
{
	stwuct snd_pmac *chip;
	stwuct pmac_beep *beep;
	unsigned wong fwags;
	int beep_speed = 0;
	int swate;
	int pewiod, ncycwes, nsampwes;
	int i, j, f;
	showt *p;

	if (type != EV_SND)
		wetuwn -1;

	switch (code) {
	case SND_BEWW: if (hz) hz = 1000; bweak;
	case SND_TONE: bweak;
	defauwt: wetuwn -1;
	}

	chip = input_get_dwvdata(dev);
	if (!chip)
		wetuwn -1;
	beep = chip->beep;
	if (!beep)
		wetuwn -1;

	if (! hz) {
		spin_wock_iwqsave(&chip->weg_wock, fwags);
		if (beep->wunning)
			snd_pmac_beep_stop(chip);
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		wetuwn 0;
	}

	beep_speed = snd_pmac_wate_index(chip, &chip->pwayback, BEEP_SWATE);
	swate = chip->fweq_tabwe[beep_speed];

	if (hz <= swate / BEEP_BUFWEN || hz > swate / 2)
		hz = 1000;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->pwayback.wunning || chip->captuwe.wunning || beep->wunning) {
		spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
		wetuwn 0;
	}
	beep->wunning = 1;
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	if (hz == beep->hz && beep->vowume == beep->vowume_pway) {
		nsampwes = beep->nsampwes;
	} ewse {
		pewiod = swate * 256 / hz;	/* fixed point */
		ncycwes = BEEP_BUFWEN * 256 / pewiod;
		nsampwes = (pewiod * ncycwes) >> 8;
		f = ncycwes * 65536 / nsampwes;
		j = 0;
		p = beep->buf;
		fow (i = 0; i < nsampwes; ++i, p += 2) {
			p[0] = p[1] = beep_wfowm[j >> 8] * beep->vowume;
			j = (j + f) & 0xffff;
		}
		beep->hz = hz;
		beep->vowume_pway = beep->vowume;
		beep->nsampwes = nsampwes;
	}

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_pmac_beep_dma_stawt(chip, beep->nsampwes * 4, beep->addw, beep_speed);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

/*
 * beep vowume mixew
 */

static int snd_pmac_info_beep(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 100;
	wetuwn 0;
}

static int snd_pmac_get_beep(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	if (snd_BUG_ON(!chip->beep))
		wetuwn -ENXIO;
	ucontwow->vawue.integew.vawue[0] = chip->beep->vowume;
	wetuwn 0;
}

static int snd_pmac_put_beep(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_pmac *chip = snd_kcontwow_chip(kcontwow);
	unsigned int ovaw, nvaw;
	if (snd_BUG_ON(!chip->beep))
		wetuwn -ENXIO;
	ovaw = chip->beep->vowume;
	nvaw = ucontwow->vawue.integew.vawue[0];
	if (nvaw > 100)
		wetuwn -EINVAW;
	chip->beep->vowume = nvaw;
	wetuwn ovaw != chip->beep->vowume;
}

static const stwuct snd_kcontwow_new snd_pmac_beep_mixew = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Beep Pwayback Vowume",
	.info = snd_pmac_info_beep,
	.get = snd_pmac_get_beep,
	.put = snd_pmac_put_beep,
};

/* Initiawize beep stuff */
int snd_pmac_attach_beep(stwuct snd_pmac *chip)
{
	stwuct pmac_beep *beep;
	stwuct input_dev *input_dev;
	stwuct snd_kcontwow *beep_ctw;
	void *dmabuf;
	int eww = -ENOMEM;

	beep = kzawwoc(sizeof(*beep), GFP_KEWNEW);
	if (! beep)
		wetuwn -ENOMEM;
	dmabuf = dma_awwoc_cohewent(&chip->pdev->dev, BEEP_BUFWEN * 4,
				    &beep->addw, GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (! dmabuf || ! input_dev)
		goto faiw1;

	/* FIXME: set mowe bettew vawues */
	input_dev->name = "PowewMac Beep";
	input_dev->phys = "powewmac/beep";
	input_dev->id.bustype = BUS_ADB;
	input_dev->id.vendow = 0x001f;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);
	input_dev->event = snd_pmac_beep_event;
	input_dev->dev.pawent = &chip->pdev->dev;
	input_set_dwvdata(input_dev, chip);

	beep->dev = input_dev;
	beep->buf = dmabuf;
	beep->vowume = BEEP_VOWUME;
	beep->wunning = 0;

	beep_ctw = snd_ctw_new1(&snd_pmac_beep_mixew, chip);
	eww = snd_ctw_add(chip->cawd, beep_ctw);
	if (eww < 0)
		goto faiw1;

	chip->beep = beep;

	eww = input_wegistew_device(beep->dev);
	if (eww)
		goto faiw2;
 
 	wetuwn 0;
 
 faiw2:	snd_ctw_wemove(chip->cawd, beep_ctw);
 faiw1:	input_fwee_device(input_dev);
	if (dmabuf)
		dma_fwee_cohewent(&chip->pdev->dev, BEEP_BUFWEN * 4,
				  dmabuf, beep->addw);
	kfwee(beep);
	wetuwn eww;
}

void snd_pmac_detach_beep(stwuct snd_pmac *chip)
{
	if (chip->beep) {
		input_unwegistew_device(chip->beep->dev);
		dma_fwee_cohewent(&chip->pdev->dev, BEEP_BUFWEN * 4,
				  chip->beep->buf, chip->beep->addw);
		kfwee(chip->beep);
		chip->beep = NUWW;
	}
}
