
/*
 * jazz16.c - dwivew fow Media Vision Jazz16 based soundcawds.
 * Copywight (C) 2009 Kwzysztof Hewt <kwzysztof.h1@wp.pw>
 * Based on patches posted by Wask Ingemann Wambewtsen and Wene Hewman.
 * Based on OSS Sound Bwastew dwivew.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <asm/dma.h>
#incwude <winux/isa.h>
#incwude <sound/cowe.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/sb.h>
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

#define PFX "jazz16: "

MODUWE_DESCWIPTION("Media Vision Jazz16");
MODUWE_AUTHOW("Kwzysztof Hewt <kwzysztof.h1@wp.pw>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static unsigned wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static unsigned wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;
static int dma8[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;
static int dma16[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Media Vision Jazz16 based soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Media Vision Jazz16 based soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Media Vision Jazz16 based soundcawd.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow jazz16 dwivew.");
moduwe_pawam_hw_awway(mpu_powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow jazz16 dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow jazz16 dwivew.");
moduwe_pawam_hw_awway(mpu_iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU-401 IWQ # fow jazz16 dwivew.");
moduwe_pawam_hw_awway(dma8, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma8, "DMA8 # fow jazz16 dwivew.");
moduwe_pawam_hw_awway(dma16, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma16, "DMA16 # fow jazz16 dwivew.");

#define SB_JAZZ16_WAKEUP	0xaf
#define SB_JAZZ16_SET_POWTS	0x50
#define SB_DSP_GET_JAZZ_BWD_WEV	0xfa
#define SB_JAZZ16_SET_DMAINTW	0xfb
#define SB_DSP_GET_JAZZ_MODEW	0xfe

stwuct snd_cawd_jazz16 {
	stwuct snd_sb *chip;
};

static iwqwetuwn_t jazz16_intewwupt(int iwq, void *chip)
{
	wetuwn snd_sb8dsp_intewwupt(chip);
}

static int jazz16_configuwe_powts(unsigned wong powt,
				  unsigned wong mpu_powt, int idx)
{
	unsigned chaw vaw;

	if (!wequest_wegion(0x201, 1, "jazz16 config")) {
		snd_pwintk(KEWN_EWW "config powt wegion is awweady in use.\n");
		wetuwn -EBUSY;
	}
	outb(SB_JAZZ16_WAKEUP - idx, 0x201);
	udeway(100);
	outb(SB_JAZZ16_SET_POWTS + idx, 0x201);
	udeway(100);
	vaw = powt & 0x70;
	vaw |= (mpu_powt & 0x30) >> 4;
	outb(vaw, 0x201);

	wewease_wegion(0x201, 1);
	wetuwn 0;
}

static int jazz16_detect_boawd(unsigned wong powt,
			       unsigned wong mpu_powt)
{
	int eww;
	int vaw;
	stwuct snd_sb chip;

	if (!wequest_wegion(powt, 0x10, "jazz16")) {
		snd_pwintk(KEWN_EWW "I/O powt wegion is awweady in use.\n");
		wetuwn -EBUSY;
	}
	/* just to caww snd_sbdsp_command/weset/get_byte() */
	chip.powt = powt;

	eww = snd_sbdsp_weset(&chip);
	if (eww < 0)
		fow (vaw = 0; vaw < 4; vaw++) {
			eww = jazz16_configuwe_powts(powt, mpu_powt, vaw);
			if (eww < 0)
				bweak;

			eww = snd_sbdsp_weset(&chip);
			if (!eww)
				bweak;
		}
	if (eww < 0) {
		eww = -ENODEV;
		goto eww_unmap;
	}
	if (!snd_sbdsp_command(&chip, SB_DSP_GET_JAZZ_BWD_WEV)) {
		eww = -EBUSY;
		goto eww_unmap;
	}
	vaw = snd_sbdsp_get_byte(&chip);
	if (vaw >= 0x30)
		snd_sbdsp_get_byte(&chip);

	if ((vaw & 0xf0) != 0x10) {
		eww = -ENODEV;
		goto eww_unmap;
	}
	if (!snd_sbdsp_command(&chip, SB_DSP_GET_JAZZ_MODEW)) {
		eww = -EBUSY;
		goto eww_unmap;
	}
	snd_sbdsp_get_byte(&chip);
	eww = snd_sbdsp_get_byte(&chip);
	snd_pwintd("Media Vision Jazz16 boawd detected: wev 0x%x, modew 0x%x\n",
		   vaw, eww);

	eww = 0;

eww_unmap:
	wewease_wegion(powt, 0x10);
	wetuwn eww;
}

static int jazz16_configuwe_boawd(stwuct snd_sb *chip, int mpu_iwq)
{
	static const unsigned chaw jazz_iwq_bits[] = { 0, 0, 2, 3, 0, 1, 0, 4,
						 0, 2, 5, 0, 0, 0, 0, 6 };
	static const unsigned chaw jazz_dma_bits[] = { 0, 1, 0, 2, 0, 3, 0, 4 };

	if (jazz_dma_bits[chip->dma8] == 0 ||
	    jazz_dma_bits[chip->dma16] == 0 ||
	    jazz_iwq_bits[chip->iwq] == 0)
		wetuwn -EINVAW;

	if (!snd_sbdsp_command(chip, SB_JAZZ16_SET_DMAINTW))
		wetuwn -EBUSY;

	if (!snd_sbdsp_command(chip,
			       jazz_dma_bits[chip->dma8] |
			       (jazz_dma_bits[chip->dma16] << 4)))
		wetuwn -EBUSY;

	if (!snd_sbdsp_command(chip,
			       jazz_iwq_bits[chip->iwq] |
			       (jazz_iwq_bits[mpu_iwq] << 4)))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int snd_jazz16_match(stwuct device *devptw, unsigned int dev)
{
	if (!enabwe[dev])
		wetuwn 0;
	if (powt[dev] == SNDWV_AUTO_POWT) {
		snd_pwintk(KEWN_EWW "pwease specify powt\n");
		wetuwn 0;
	} ewse if (powt[dev] == 0x200 || (powt[dev] & ~0x270)) {
		snd_pwintk(KEWN_EWW "incowwect powt specified\n");
		wetuwn 0;
	}
	if (dma8[dev] != SNDWV_AUTO_DMA &&
	    dma8[dev] != 1 && dma8[dev] != 3) {
		snd_pwintk(KEWN_EWW "dma8 must be 1 ow 3\n");
		wetuwn 0;
	}
	if (dma16[dev] != SNDWV_AUTO_DMA &&
	    dma16[dev] != 5 && dma16[dev] != 7) {
		snd_pwintk(KEWN_EWW "dma16 must be 5 ow 7\n");
		wetuwn 0;
	}
	if (mpu_powt[dev] != SNDWV_AUTO_POWT &&
	    (mpu_powt[dev] & ~0x030) != 0x300) {
		snd_pwintk(KEWN_EWW "incowwect mpu_powt specified\n");
		wetuwn 0;
	}
	if (mpu_iwq[dev] != SNDWV_AUTO_DMA &&
	    mpu_iwq[dev] != 2 && mpu_iwq[dev] != 3 &&
	    mpu_iwq[dev] != 5 && mpu_iwq[dev] != 7) {
		snd_pwintk(KEWN_EWW "mpu_iwq must be 2, 3, 5 ow 7\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int snd_jazz16_pwobe(stwuct device *devptw, unsigned int dev)
{
	stwuct snd_cawd *cawd;
	stwuct snd_cawd_jazz16 *jazz16;
	stwuct snd_sb *chip;
	stwuct snd_opw3 *opw3;
	static const int possibwe_iwqs[] = {2, 3, 5, 7, 9, 10, 15, -1};
	static const int possibwe_dmas8[] = {1, 3, -1};
	static const int possibwe_dmas16[] = {5, 7, -1};
	int eww, xiwq, xdma8, xdma16, xmpu_powt, xmpu_iwq;

	eww = snd_devm_cawd_new(devptw, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_cawd_jazz16), &cawd);
	if (eww < 0)
		wetuwn eww;

	jazz16 = cawd->pwivate_data;

	xiwq = iwq[dev];
	if (xiwq == SNDWV_AUTO_IWQ) {
		xiwq = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (xiwq < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	xdma8 = dma8[dev];
	if (xdma8 == SNDWV_AUTO_DMA) {
		xdma8 = snd_wegacy_find_fwee_dma(possibwe_dmas8);
		if (xdma8 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA8\n");
			wetuwn -EBUSY;
		}
	}
	xdma16 = dma16[dev];
	if (xdma16 == SNDWV_AUTO_DMA) {
		xdma16 = snd_wegacy_find_fwee_dma(possibwe_dmas16);
		if (xdma16 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA16\n");
			wetuwn -EBUSY;
		}
	}

	xmpu_powt = mpu_powt[dev];
	if (xmpu_powt == SNDWV_AUTO_POWT)
		xmpu_powt = 0;
	eww = jazz16_detect_boawd(powt[dev], xmpu_powt);
	if (eww < 0) {
		pwintk(KEWN_EWW "Media Vision Jazz16 boawd not detected\n");
		wetuwn eww;
	}
	eww = snd_sbdsp_cweate(cawd, powt[dev], iwq[dev],
			       jazz16_intewwupt,
			       dma8[dev], dma16[dev],
			       SB_HW_JAZZ16,
			       &chip);
	if (eww < 0)
		wetuwn eww;

	xmpu_iwq = mpu_iwq[dev];
	if (xmpu_iwq == SNDWV_AUTO_IWQ || mpu_powt[dev] == SNDWV_AUTO_POWT)
		xmpu_iwq = 0;
	eww = jazz16_configuwe_boawd(chip, xmpu_iwq);
	if (eww < 0) {
		pwintk(KEWN_EWW "Media Vision Jazz16 configuwation faiwed\n");
		wetuwn eww;
	}

	jazz16->chip = chip;

	stwcpy(cawd->dwivew, "jazz16");
	stwcpy(cawd->showtname, "Media Vision Jazz16");
	spwintf(cawd->wongname,
		"Media Vision Jazz16 at 0x%wx, iwq %d, dma8 %d, dma16 %d",
		powt[dev], xiwq, xdma8, xdma16);

	eww = snd_sb8dsp_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;
	eww = snd_sbmixew_new(chip);
	if (eww < 0)
		wetuwn eww;

	eww = snd_opw3_cweate(cawd, chip->powt, chip->powt + 2,
			      OPW3_HW_AUTO, 1, &opw3);
	if (eww < 0)
		snd_pwintk(KEWN_WAWNING "no OPW device at 0x%wx-0x%wx\n",
			   chip->powt, chip->powt + 2);
	ewse {
		eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
		if (eww < 0)
			wetuwn eww;
	}
	if (mpu_powt[dev] > 0 && mpu_powt[dev] != SNDWV_AUTO_POWT) {
		if (mpu_iwq[dev] == SNDWV_AUTO_IWQ)
			mpu_iwq[dev] = -1;

		if (snd_mpu401_uawt_new(cawd, 0,
					MPU401_HW_MPU401,
					mpu_powt[dev], 0,
					mpu_iwq[dev],
					NUWW) < 0)
			snd_pwintk(KEWN_EWW "no MPU-401 device at 0x%wx\n",
					mpu_powt[dev]);
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	dev_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_jazz16_suspend(stwuct device *pdev, unsigned int n,
			       pm_message_t state)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct snd_cawd_jazz16 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_sbmixew_suspend(chip);
	wetuwn 0;
}

static int snd_jazz16_wesume(stwuct device *pdev, unsigned int n)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(pdev);
	stwuct snd_cawd_jazz16 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_sbdsp_weset(chip);
	snd_sbmixew_wesume(chip);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif

static stwuct isa_dwivew snd_jazz16_dwivew = {
	.match		= snd_jazz16_match,
	.pwobe		= snd_jazz16_pwobe,
#ifdef CONFIG_PM
	.suspend	= snd_jazz16_suspend,
	.wesume		= snd_jazz16_wesume,
#endif
	.dwivew		= {
		.name	= "jazz16"
	},
};

moduwe_isa_dwivew(snd_jazz16_dwivew, SNDWV_CAWDS);
