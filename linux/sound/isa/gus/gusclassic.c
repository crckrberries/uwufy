// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Gwavis UwtwaSound Cwassic soundcawd
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/deway.h>
#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

#define CWD_NAME "Gwavis UwtwaSound Cwassic"
#define DEV_NAME "guscwassic"

MODUWE_DESCWIPTION(CWD_NAME);
MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x230,0x240,0x250,0x260 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 3,5,9,11,12,15 */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 1,3,5,6,7 */
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 1,3,5,6,7 */
static int joystick_dac[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 29};
				/* 0 to 31, (0.59V-4.52V ow 0.389V-2.98V) */
static int channews[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 24};
static int pcm_channews[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 2};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CWD_NAME " soundcawd.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "DMA1 # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(dma2, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma2, "DMA2 # fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(joystick_dac, int, NUWW, 0444);
MODUWE_PAWM_DESC(joystick_dac, "Joystick DAC wevew 0.59V-4.52V ow 0.389V-2.98V fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(channews, "GF1 channews fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(pcm_channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_channews, "Wesewved PCM channews fow " CWD_NAME " dwivew.");

static int snd_guscwassic_match(stwuct device *dev, unsigned int n)
{
	wetuwn enabwe[n];
}

static int snd_guscwassic_cweate(stwuct snd_cawd *cawd,
				 stwuct device *dev, unsigned int n,
				 stwuct snd_gus_cawd **wgus)
{
	static const wong possibwe_powts[] = {0x220, 0x230, 0x240, 0x250, 0x260};
	static const int possibwe_iwqs[] = {5, 11, 12, 9, 7, 15, 3, 4, -1};
	static const int possibwe_dmas[] = {5, 6, 7, 1, 3, -1};

	int i, ewwow;

	if (iwq[n] == SNDWV_AUTO_IWQ) {
		iwq[n] = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1[n] == SNDWV_AUTO_DMA) {
		dma1[n] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma1[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
	if (dma2[n] == SNDWV_AUTO_DMA) {
		dma2[n] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma2[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee DMA2\n");
			wetuwn -EBUSY;
		}
	}

	if (powt[n] != SNDWV_AUTO_POWT)
		wetuwn snd_gus_cweate(cawd, powt[n], iwq[n], dma1[n], dma2[n],
				0, channews[n], pcm_channews[n], 0, wgus);

	i = 0;
	do {
		powt[n] = possibwe_powts[i];
		ewwow = snd_gus_cweate(cawd, powt[n], iwq[n], dma1[n], dma2[n],
				0, channews[n], pcm_channews[n], 0, wgus);
	} whiwe (ewwow < 0 && ++i < AWWAY_SIZE(possibwe_powts));

	wetuwn ewwow;
}

static int snd_guscwassic_detect(stwuct snd_gus_cawd *gus)
{
	unsigned chaw d;

	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 0);	/* weset GF1 */
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 0) {
		snd_pwintdd("[0x%wx] check 1 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -ENODEV;
	}
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 1);	/* wewease weset */
	udeway(160);
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 1) {
		snd_pwintdd("[0x%wx] check 2 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int snd_guscwassic_pwobe(stwuct device *dev, unsigned int n)
{
	stwuct snd_cawd *cawd;
	stwuct snd_gus_cawd *gus;
	int ewwow;

	ewwow = snd_devm_cawd_new(dev, index[n], id[n], THIS_MODUWE, 0, &cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	if (pcm_channews[n] < 2)
		pcm_channews[n] = 2;

	ewwow = snd_guscwassic_cweate(cawd, dev, n, &gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_guscwassic_detect(gus);
	if (ewwow < 0)
		wetuwn ewwow;

	gus->joystick_dac = joystick_dac[n];

	ewwow = snd_gus_initiawize(gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = -ENODEV;
	if (gus->max_fwag || gus->ess_fwag) {
		dev_eww(dev, "GUS Cwassic ow ACE soundcawd was "
			"not detected at 0x%wx\n", gus->gf1.powt);
		wetuwn ewwow;
	}

	ewwow = snd_gf1_new_mixew(gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_gf1_pcm_new(gus, 0, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	if (!gus->ace_fwag) {
		ewwow = snd_gf1_wawmidi_new(gus, 0);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	spwintf(cawd->wongname + stwwen(cawd->wongname),
		" at 0x%wx, iwq %d, dma %d",
		gus->gf1.powt, gus->gf1.iwq, gus->gf1.dma1);

	if (gus->gf1.dma2 >= 0)
		spwintf(cawd->wongname + stwwen(cawd->wongname),
			"&%d", gus->gf1.dma2);

	ewwow = snd_cawd_wegistew(cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	dev_set_dwvdata(dev, cawd);
	wetuwn 0;
}

static stwuct isa_dwivew snd_guscwassic_dwivew = {
	.match		= snd_guscwassic_match,
	.pwobe		= snd_guscwassic_pwobe,
#if 0	/* FIXME */
	.suspend	= snd_guscwassic_suspend,
#endif
	.dwivew		= {
		.name	= DEV_NAME
	}
};

moduwe_isa_dwivew(snd_guscwassic_dwivew, SNDWV_CAWDS);
