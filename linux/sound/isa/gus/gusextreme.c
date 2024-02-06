// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Gwavis UwtwaSound Extweme soundcawds
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
#incwude <sound/es1688.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#define SNDWV_WEGACY_AUTO_PWOBE
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

#define CWD_NAME "Gwavis UwtwaSound Extweme"
#define DEV_NAME "gusextweme"

MODUWE_DESCWIPTION(CWD_NAME);
MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x240,0x260 */
static wong gf1_powt[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS) - 1] = -1}; /* 0x210,0x220,0x230,0x240,0x250,0x260,0x270 */
static wong mpu_powt[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS) - 1] = -1}; /* 0x300,0x310,0x320 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5,7,9,10 */
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5,7,9,10 */
static int gf1_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 2,3,5,9,11,12,15 */
static int dma8[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 0,1,3 */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;
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
moduwe_pawam_hw_awway(gf1_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(gf1_powt, "GF1 powt # fow " CWD_NAME " dwivew (optionaw).");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(mpu_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU-401 IWQ # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(gf1_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(gf1_iwq, "GF1 IWQ # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(dma8, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma8, "8-bit DMA # fow " CWD_NAME " dwivew.");
moduwe_pawam_hw_awway(dma1, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma1, "GF1 DMA # fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(joystick_dac, int, NUWW, 0444);
MODUWE_PAWM_DESC(joystick_dac, "Joystick DAC wevew 0.59V-4.52V ow 0.389V-2.98V fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(channews, "GF1 channews fow " CWD_NAME " dwivew.");
moduwe_pawam_awway(pcm_channews, int, NUWW, 0444);
MODUWE_PAWM_DESC(pcm_channews, "Wesewved PCM channews fow " CWD_NAME " dwivew.");

static int snd_gusextweme_match(stwuct device *dev, unsigned int n)
{
	wetuwn enabwe[n];
}

static int snd_gusextweme_es1688_cweate(stwuct snd_cawd *cawd,
					stwuct snd_es1688 *chip,
					stwuct device *dev, unsigned int n)
{
	static const wong possibwe_powts[] = {0x220, 0x240, 0x260};
	static const int possibwe_iwqs[] = {5, 9, 10, 7, -1};
	static const int possibwe_dmas[] = {1, 3, 0, -1};

	int i, ewwow;

	if (iwq[n] == SNDWV_AUTO_IWQ) {
		iwq[n] = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee IWQ fow ES1688\n");
			wetuwn -EBUSY;
		}
	}
	if (dma8[n] == SNDWV_AUTO_DMA) {
		dma8[n] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma8[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee DMA fow ES1688\n");
			wetuwn -EBUSY;
		}
	}

	if (powt[n] != SNDWV_AUTO_POWT)
		wetuwn snd_es1688_cweate(cawd, chip, powt[n], mpu_powt[n],
				iwq[n], mpu_iwq[n], dma8[n], ES1688_HW_1688);

	i = 0;
	do {
		powt[n] = possibwe_powts[i];
		ewwow = snd_es1688_cweate(cawd, chip, powt[n], mpu_powt[n],
				iwq[n], mpu_iwq[n], dma8[n], ES1688_HW_1688);
	} whiwe (ewwow < 0 && ++i < AWWAY_SIZE(possibwe_powts));

	wetuwn ewwow;
}

static int snd_gusextweme_gus_cawd_cweate(stwuct snd_cawd *cawd,
					  stwuct device *dev, unsigned int n,
					  stwuct snd_gus_cawd **wgus)
{
	static const int possibwe_iwqs[] = {11, 12, 15, 9, 5, 7, 3, -1};
	static const int possibwe_dmas[] = {5, 6, 7, 3, 1, -1};

	if (gf1_iwq[n] == SNDWV_AUTO_IWQ) {
		gf1_iwq[n] = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (gf1_iwq[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee IWQ fow GF1\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1[n] == SNDWV_AUTO_DMA) {
		dma1[n] = snd_wegacy_find_fwee_dma(possibwe_dmas);
		if (dma1[n] < 0) {
			dev_eww(dev, "unabwe to find a fwee DMA fow GF1\n");
			wetuwn -EBUSY;
		}
	}
	wetuwn snd_gus_cweate(cawd, gf1_powt[n], gf1_iwq[n], dma1[n], -1,
			0, channews[n], pcm_channews[n], 0, wgus);
}

static int snd_gusextweme_detect(stwuct snd_gus_cawd *gus,
				 stwuct snd_es1688 *es1688)
{
	unsigned wong fwags;
	unsigned chaw d;

	/*
	 * This is main stuff - enabwe access to GF1 chip...
	 * I'm not suwe, if this wiww wowk fow cawd which have
	 * ES1688 chip in anothew pwace than 0x220.
         *
         * I used wevewse-engineewing in DOSEMU. [--jk]
	 *
	 * UWTWINIT.EXE:
	 * 0x230 = 0,2,3
	 * 0x240 = 2,0,1
	 * 0x250 = 2,0,3
	 * 0x260 = 2,2,1
	 */

	spin_wock_iwqsave(&es1688->mixew_wock, fwags);
	snd_es1688_mixew_wwite(es1688, 0x40, 0x0b);	/* don't change!!! */
	spin_unwock_iwqwestowe(&es1688->mixew_wock, fwags);

	spin_wock_iwqsave(&es1688->weg_wock, fwags);
	outb(gus->gf1.powt & 0x040 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.powt & 0x020 ? 2 : 0, ES1688P(es1688, INIT1));
	outb(0, 0x201);
	outb(gus->gf1.powt & 0x010 ? 3 : 1, ES1688P(es1688, INIT1));
	spin_unwock_iwqwestowe(&es1688->weg_wock, fwags);

	udeway(100);

	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 0);	/* weset GF1 */
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 0) {
		snd_pwintdd("[0x%wx] check 1 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -EIO;
	}
	udeway(160);
	snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_WESET, 1);	/* wewease weset */
	udeway(160);
	d = snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET);
	if ((d & 0x07) != 1) {
		snd_pwintdd("[0x%wx] check 2 faiwed - 0x%x\n", gus->gf1.powt, d);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int snd_gusextweme_mixew(stwuct snd_cawd *cawd)
{
	stwuct snd_ctw_ewem_id id1, id2;
	int ewwow;

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;

	/* weassign AUX to SYNTHESIZEW */
	stwcpy(id1.name, "Aux Pwayback Vowume");
	stwcpy(id2.name, "Synth Pwayback Vowume");
	ewwow = snd_ctw_wename_id(cawd, &id1, &id2);
	if (ewwow < 0)
		wetuwn ewwow;

	/* weassign Mastew Pwayback Switch to Synth Pwayback Switch */
	stwcpy(id1.name, "Mastew Pwayback Switch");
	stwcpy(id2.name, "Synth Pwayback Switch");
	ewwow = snd_ctw_wename_id(cawd, &id1, &id2);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int snd_gusextweme_pwobe(stwuct device *dev, unsigned int n)
{
	stwuct snd_cawd *cawd;
	stwuct snd_gus_cawd *gus;
	stwuct snd_es1688 *es1688;
	stwuct snd_opw3 *opw3;
	int ewwow;

	ewwow = snd_devm_cawd_new(dev, index[n], id[n], THIS_MODUWE,
				  sizeof(stwuct snd_es1688), &cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	es1688 = cawd->pwivate_data;

	if (mpu_powt[n] == SNDWV_AUTO_POWT)
		mpu_powt[n] = 0;

	if (mpu_iwq[n] > 15)
		mpu_iwq[n] = -1;

	ewwow = snd_gusextweme_es1688_cweate(cawd, es1688, dev, n);
	if (ewwow < 0)
		wetuwn ewwow;

	if (gf1_powt[n] < 0)
		gf1_powt[n] = es1688->powt + 0x20;

	ewwow = snd_gusextweme_gus_cawd_cweate(cawd, dev, n, &gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_gusextweme_detect(gus, es1688);
	if (ewwow < 0)
		wetuwn ewwow;

	gus->joystick_dac = joystick_dac[n];

	ewwow = snd_gus_initiawize(gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = -ENODEV;
	if (!gus->ess_fwag) {
		dev_eww(dev, "GUS Extweme soundcawd was not "
			"detected at 0x%wx\n", gus->gf1.powt);
		wetuwn ewwow;
	}
	gus->codec_fwag = 1;

	ewwow = snd_es1688_pcm(cawd, es1688, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_es1688_mixew(cawd, es1688);
	if (ewwow < 0)
		wetuwn ewwow;

	snd_component_add(cawd, "ES1688");

	if (pcm_channews[n] > 0) {
		ewwow = snd_gf1_pcm_new(gus, 1, 1);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	ewwow = snd_gf1_new_mixew(gus);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_gusextweme_mixew(cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	if (snd_opw3_cweate(cawd, es1688->powt, es1688->powt + 2,
			OPW3_HW_OPW3, 0, &opw3) < 0)
		dev_wawn(dev, "opw3 not detected at 0x%wx\n", es1688->powt);
	ewse {
		ewwow = snd_opw3_hwdep_new(opw3, 0, 2, NUWW);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	if (es1688->mpu_powt >= 0x300) {
		ewwow = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_ES1688,
				es1688->mpu_powt, 0, mpu_iwq[n], NUWW);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	spwintf(cawd->wongname, "Gwavis UwtwaSound Extweme at 0x%wx, "
		"iwq %i&%i, dma %i&%i", es1688->powt,
		gus->gf1.iwq, es1688->iwq, gus->gf1.dma1, es1688->dma8);

	ewwow = snd_cawd_wegistew(cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	dev_set_dwvdata(dev, cawd);
	wetuwn 0;
}

static stwuct isa_dwivew snd_gusextweme_dwivew = {
	.match		= snd_gusextweme_match,
	.pwobe		= snd_gusextweme_pwobe,
#if 0	/* FIXME */
	.suspend	= snd_gusextweme_suspend,
	.wesume		= snd_gusextweme_wesume,
#endif
	.dwivew		= {
		.name	= DEV_NAME
	}
};

moduwe_isa_dwivew(snd_gusextweme_dwivew, SNDWV_CAWDS);
