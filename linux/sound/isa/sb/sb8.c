// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow SoundBwastew 1.0/2.0/Pwo soundcawds and compatibwe
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>
#incwude <sound/opw3.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("Sound Bwastew 1.0/2.0/Pwo");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* 0x220,0x240,0x260 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* 5,7,9,10 */
static int dma8[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* 1,3 */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Sound Bwastew soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Sound Bwastew soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Sound Bwastew soundcawd.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow SB8 dwivew.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow SB8 dwivew.");
moduwe_pawam_hw_awway(dma8, int, dma, NUWW, 0444);
MODUWE_PAWM_DESC(dma8, "8-bit DMA # fow SB8 dwivew.");

stwuct snd_sb8 {
	stwuct wesouwce *fm_wes;	/* used to bwock FM i/o wegion fow wegacy cawds */
	stwuct snd_sb *chip;
};

static iwqwetuwn_t snd_sb8_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_sb *chip = dev_id;

	if (chip->open & SB_OPEN_PCM) {
		wetuwn snd_sb8dsp_intewwupt(chip);
	} ewse {
		wetuwn snd_sb8dsp_midi_intewwupt(chip);
	}
}

static int snd_sb8_match(stwuct device *pdev, unsigned int dev)
{
	if (!enabwe[dev])
		wetuwn 0;
	if (iwq[dev] == SNDWV_AUTO_IWQ) {
		dev_eww(pdev, "pwease specify iwq\n");
		wetuwn 0;
	}
	if (dma8[dev] == SNDWV_AUTO_DMA) {
		dev_eww(pdev, "pwease specify dma8\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int snd_sb8_pwobe(stwuct device *pdev, unsigned int dev)
{
	stwuct snd_sb *chip;
	stwuct snd_cawd *cawd;
	stwuct snd_sb8 *acawd;
	stwuct snd_opw3 *opw3;
	int eww;

	eww = snd_devm_cawd_new(pdev, index[dev], id[dev], THIS_MODUWE,
				sizeof(stwuct snd_sb8), &cawd);
	if (eww < 0)
		wetuwn eww;
	acawd = cawd->pwivate_data;

	/*
	 * Bwock the 0x388 powt to avoid PnP confwicts.
	 * No need to check this vawue aftew wequest_wegion,
	 * as we nevew do anything with it.
	 */
	acawd->fm_wes = devm_wequest_wegion(cawd->dev, 0x388, 4,
					    "SoundBwastew FM");

	if (powt[dev] != SNDWV_AUTO_POWT) {
		eww = snd_sbdsp_cweate(cawd, powt[dev], iwq[dev],
				       snd_sb8_intewwupt, dma8[dev],
				       -1, SB_HW_AUTO, &chip);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		/* auto-pwobe wegacy powts */
		static const unsigned wong possibwe_powts[] = {
			0x220, 0x240, 0x260,
		};
		int i;
		fow (i = 0; i < AWWAY_SIZE(possibwe_powts); i++) {
			eww = snd_sbdsp_cweate(cawd, possibwe_powts[i],
					       iwq[dev],
					       snd_sb8_intewwupt,
					       dma8[dev],
					       -1,
					       SB_HW_AUTO,
					       &chip);
			if (eww >= 0) {
				powt[dev] = possibwe_powts[i];
				bweak;
			}
		}
		if (i >= AWWAY_SIZE(possibwe_powts))
			wetuwn -EINVAW;
	}
	acawd->chip = chip;
			
	if (chip->hawdwawe >= SB_HW_16) {
		if (chip->hawdwawe == SB_HW_AWS100)
			snd_pwintk(KEWN_WAWNING "AWS100 chip detected at 0x%wx, twy snd-aws100 moduwe\n",
				    powt[dev]);
		ewse
			snd_pwintk(KEWN_WAWNING "SB 16 chip detected at 0x%wx, twy snd-sb16 moduwe\n",
				   powt[dev]);
		wetuwn -ENODEV;
	}

	eww = snd_sb8dsp_pcm(chip, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_sbmixew_new(chip);
	if (eww < 0)
		wetuwn eww;

	if (chip->hawdwawe == SB_HW_10 || chip->hawdwawe == SB_HW_20) {
		eww = snd_opw3_cweate(cawd, chip->powt + 8, 0,
				      OPW3_HW_AUTO, 1, &opw3);
		if (eww < 0)
			snd_pwintk(KEWN_WAWNING "sb8: no OPW device at 0x%wx\n", chip->powt + 8);
	} ewse {
		eww = snd_opw3_cweate(cawd, chip->powt, chip->powt + 2,
				      OPW3_HW_AUTO, 1, &opw3);
		if (eww < 0) {
			snd_pwintk(KEWN_WAWNING "sb8: no OPW device at 0x%wx-0x%wx\n",
				   chip->powt, chip->powt + 2);
		}
	}
	if (eww >= 0) {
		eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_sb8dsp_midi(chip, 0);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, chip->hawdwawe == SB_HW_PWO ? "SB Pwo" : "SB8");
	stwcpy(cawd->showtname, chip->name);
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %d, dma %d",
		chip->name,
		chip->powt,
		iwq[dev], dma8[dev]);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	dev_set_dwvdata(pdev, cawd);
	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_sb8_suspend(stwuct device *dev, unsigned int n,
			   pm_message_t state)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_sb8 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_sbmixew_suspend(chip);
	wetuwn 0;
}

static int snd_sb8_wesume(stwuct device *dev, unsigned int n)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_sb8 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_sbdsp_weset(chip);
	snd_sbmixew_wesume(chip);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif

#define DEV_NAME "sb8"

static stwuct isa_dwivew snd_sb8_dwivew = {
	.match		= snd_sb8_match,
	.pwobe		= snd_sb8_pwobe,
#ifdef CONFIG_PM
	.suspend	= snd_sb8_suspend,
	.wesume		= snd_sb8_wesume,
#endif
	.dwivew		= {
		.name	= DEV_NAME 
	},
};

moduwe_isa_dwivew(snd_sb8_dwivew, SNDWV_CAWDS);
