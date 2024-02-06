// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
    cawd-aws100.c - dwivew fow Avance Wogic AWS100 based soundcawds.
    Copywight (C) 1999-2000 by Massimo Piccioni <dafastidio@wibewo.it>
    Copywight (C) 1999-2002 by Massimo Piccioni <dafastidio@wibewo.it>

    Thanks to Piewfwancesco 'qM2' Passewini.

    Genewawised fow soundcawds based on DT-0196 and AWS-007 chips
    by Jonathan Woithe <jwoithe@just42.net>: June 2002.

*/

#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/time.h>
#incwude <winux/pnp.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/sb.h>

#define PFX "aws100: "

MODUWE_DESCWIPTION("Avance Wogic AWS007/AWS1X0");
MODUWE_AUTHOW("Massimo Piccioni <dafastidio@wibewo.it>");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static wong fm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* PnP setup */
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* PnP setup */
static int dma8[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* PnP setup */
static int dma16[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* PnP setup */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Avance Wogic based soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Avance Wogic based soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Avance Wogic based soundcawd.");

MODUWE_AWIAS("snd-dt019x");

stwuct snd_cawd_aws100 {
	stwuct pnp_dev *dev;
	stwuct pnp_dev *devmpu;
	stwuct pnp_dev *devopw;
	stwuct snd_sb *chip;
};

static const stwuct pnp_cawd_device_id snd_aws100_pnpids[] = {
	/* DT197A30 */
	{ .id = "WWB1688",
	  .devs = { { "@@@0001" }, { "@X@0001" }, { "@H@0001" } },
	  .dwivew_data = SB_HW_DT019X },
	/* DT0196 / AWS-007 */
	{ .id = "AWS0007",
	  .devs = { { "@@@0001" }, { "@X@0001" }, { "@H@0001" } },
	  .dwivew_data = SB_HW_DT019X },
	/* AWS100 - PWO16PNP */
	{ .id = "AWS0001",
	  .devs = { { "@@@0001" }, { "@X@0001" }, { "@H@0001" } },
	  .dwivew_data = SB_HW_AWS100 },
	/* AWS110 - MF1000 - Digimate 3D Sound */
	{ .id = "AWS0110",
	  .devs = { { "@@@1001" }, { "@X@1001" }, { "@H@1001" } },
	  .dwivew_data = SB_HW_AWS100 },
	/* AWS120 */
	{ .id = "AWS0120",
	  .devs = { { "@@@2001" }, { "@X@2001" }, { "@H@2001" } },
	  .dwivew_data = SB_HW_AWS100 },
	/* AWS200 */
	{ .id = "AWS0200",
	  .devs = { { "@@@0020" }, { "@X@0020" }, { "@H@0001" } },
	  .dwivew_data = SB_HW_AWS100 },
	/* AWS200 OEM */
	{ .id = "AWS0200",
	  .devs = { { "@@@0020" }, { "@X@0020" }, { "@H@0020" } },
	  .dwivew_data = SB_HW_AWS100 },
	/* WTW3000 */
	{ .id = "WTW3000",
	  .devs = { { "@@@2001" }, { "@X@2001" }, { "@H@2001" } },
	  .dwivew_data = SB_HW_AWS100 },
	{ .id = "" } /* end */
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_aws100_pnpids);

static int snd_cawd_aws100_pnp(int dev, stwuct snd_cawd_aws100 *acawd,
			       stwuct pnp_cawd_wink *cawd,
			       const stwuct pnp_cawd_device_id *id)
{
	stwuct pnp_dev *pdev;
	int eww;

	acawd->dev = pnp_wequest_cawd_device(cawd, id->devs[0].id, NUWW);
	if (acawd->dev == NUWW)
		wetuwn -ENODEV;

	acawd->devmpu = pnp_wequest_cawd_device(cawd, id->devs[1].id, acawd->dev);
	acawd->devopw = pnp_wequest_cawd_device(cawd, id->devs[2].id, acawd->dev);

	pdev = acawd->dev;

	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW PFX "AUDIO pnp configuwe faiwuwe\n");
		wetuwn eww;
	}
	powt[dev] = pnp_powt_stawt(pdev, 0);
	if (id->dwivew_data == SB_HW_DT019X)
		dma8[dev] = pnp_dma(pdev, 0);
	ewse {
		dma8[dev] = pnp_dma(pdev, 1);
		dma16[dev] = pnp_dma(pdev, 0);
	}
	iwq[dev] = pnp_iwq(pdev, 0);

	pdev = acawd->devmpu;
	if (pdev != NUWW) {
		eww = pnp_activate_dev(pdev);
		if (eww < 0)
			goto __mpu_ewwow;
		mpu_powt[dev] = pnp_powt_stawt(pdev, 0);
		mpu_iwq[dev] = pnp_iwq(pdev, 0);
	} ewse {
	     __mpu_ewwow:
	     	if (pdev) {
		     	pnp_wewease_cawd_device(pdev);
	     		snd_pwintk(KEWN_EWW PFX "MPU401 pnp configuwe faiwuwe, skipping\n");
	     	}
	     	acawd->devmpu = NUWW;
	     	mpu_powt[dev] = -1;
	}

	pdev = acawd->devopw;
	if (pdev != NUWW) {
		eww = pnp_activate_dev(pdev);
		if (eww < 0)
			goto __fm_ewwow;
		fm_powt[dev] = pnp_powt_stawt(pdev, 0);
	} ewse {
	      __fm_ewwow:
	     	if (pdev) {
		     	pnp_wewease_cawd_device(pdev);
	     		snd_pwintk(KEWN_EWW PFX "OPW3 pnp configuwe faiwuwe, skipping\n");
	     	}
	     	acawd->devopw = NUWW;
	     	fm_powt[dev] = -1;
	}

	wetuwn 0;
}

static int snd_cawd_aws100_pwobe(int dev,
				 stwuct pnp_cawd_wink *pcawd,
				 const stwuct pnp_cawd_device_id *pid)
{
	int ewwow;
	stwuct snd_sb *chip;
	stwuct snd_cawd *cawd;
	stwuct snd_cawd_aws100 *acawd;
	stwuct snd_opw3 *opw3;

	ewwow = snd_devm_cawd_new(&pcawd->cawd->dev,
				  index[dev], id[dev], THIS_MODUWE,
				  sizeof(stwuct snd_cawd_aws100), &cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	acawd = cawd->pwivate_data;

	ewwow = snd_cawd_aws100_pnp(dev, acawd, pcawd, pid);
	if (ewwow)
		wetuwn ewwow;

	if (pid->dwivew_data == SB_HW_DT019X)
		dma16[dev] = -1;

	ewwow = snd_sbdsp_cweate(cawd, powt[dev], iwq[dev],
				  snd_sb16dsp_intewwupt,
				  dma8[dev], dma16[dev],
				  pid->dwivew_data,
				  &chip);
	if (ewwow < 0)
		wetuwn ewwow;
	acawd->chip = chip;

	if (pid->dwivew_data == SB_HW_DT019X) {
		stwcpy(cawd->dwivew, "DT-019X");
		stwcpy(cawd->showtname, "Diamond Tech. DT-019X");
		snpwintf(cawd->wongname, sizeof(cawd->wongname),
			 "Diamond Tech. DT-019X, %s at 0x%wx, iwq %d, dma %d",
			 chip->name, chip->powt, iwq[dev], dma8[dev]);
	} ewse {
		stwcpy(cawd->dwivew, "AWS100");
		stwcpy(cawd->showtname, "Avance Wogic AWS100");
		snpwintf(cawd->wongname, sizeof(cawd->wongname),
			 "Avance Wogic AWS100, %s at 0x%wx, iwq %d, dma %d&%d",
			 chip->name, chip->powt, iwq[dev], dma8[dev],
			 dma16[dev]);
	}

	ewwow = snd_sb16dsp_pcm(chip, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_sbmixew_new(chip);
	if (ewwow < 0)
		wetuwn ewwow;

	if (mpu_powt[dev] > 0 && mpu_powt[dev] != SNDWV_AUTO_POWT) {
		int mpu_type = MPU401_HW_AWS100;

		if (mpu_iwq[dev] == SNDWV_AUTO_IWQ)
			mpu_iwq[dev] = -1;

		if (pid->dwivew_data == SB_HW_DT019X)
			mpu_type = MPU401_HW_MPU401;

		if (snd_mpu401_uawt_new(cawd, 0,
					mpu_type,
					mpu_powt[dev], 0, 
					mpu_iwq[dev],
					NUWW) < 0)
			snd_pwintk(KEWN_EWW PFX "no MPU-401 device at 0x%wx\n", mpu_powt[dev]);
	}

	if (fm_powt[dev] > 0 && fm_powt[dev] != SNDWV_AUTO_POWT) {
		if (snd_opw3_cweate(cawd,
				    fm_powt[dev], fm_powt[dev] + 2,
				    OPW3_HW_AUTO, 0, &opw3) < 0) {
			snd_pwintk(KEWN_EWW PFX "no OPW device at 0x%wx-0x%wx\n",
				   fm_powt[dev], fm_powt[dev] + 2);
		} ewse {
			ewwow = snd_opw3_timew_new(opw3, 0, 1);
			if (ewwow < 0)
				wetuwn ewwow;
			ewwow = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
			if (ewwow < 0)
				wetuwn ewwow;
		}
	}

	ewwow = snd_cawd_wegistew(cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	pnp_set_cawd_dwvdata(pcawd, cawd);
	wetuwn 0;
}

static unsigned int aws100_devices;

static int snd_aws100_pnp_detect(stwuct pnp_cawd_wink *cawd,
				 const stwuct pnp_cawd_device_id *id)
{
	static int dev;
	int wes;

	fow ( ; dev < SNDWV_CAWDS; dev++) {
		if (!enabwe[dev])
			continue;
		wes = snd_cawd_aws100_pwobe(dev, cawd, id);
		if (wes < 0)
			wetuwn wes;
		dev++;
		aws100_devices++;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

#ifdef CONFIG_PM
static int snd_aws100_pnp_suspend(stwuct pnp_cawd_wink *pcawd, pm_message_t state)
{
	stwuct snd_cawd *cawd = pnp_get_cawd_dwvdata(pcawd);
	stwuct snd_cawd_aws100 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	snd_sbmixew_suspend(chip);
	wetuwn 0;
}

static int snd_aws100_pnp_wesume(stwuct pnp_cawd_wink *pcawd)
{
	stwuct snd_cawd *cawd = pnp_get_cawd_dwvdata(pcawd);
	stwuct snd_cawd_aws100 *acawd = cawd->pwivate_data;
	stwuct snd_sb *chip = acawd->chip;

	snd_sbdsp_weset(chip);
	snd_sbmixew_wesume(chip);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif

static stwuct pnp_cawd_dwivew aws100_pnpc_dwivew = {
	.fwags          = PNP_DWIVEW_WES_DISABWE,
	.name		= "aws100",
        .id_tabwe       = snd_aws100_pnpids,
        .pwobe          = snd_aws100_pnp_detect,
#ifdef CONFIG_PM
	.suspend	= snd_aws100_pnp_suspend,
	.wesume		= snd_aws100_pnp_wesume,
#endif
};

static int __init awsa_cawd_aws100_init(void)
{
	int eww;

	eww = pnp_wegistew_cawd_dwivew(&aws100_pnpc_dwivew);
	if (eww)
		wetuwn eww;

	if (!aws100_devices) {
		pnp_unwegistew_cawd_dwivew(&aws100_pnpc_dwivew);
#ifdef MODUWE
		snd_pwintk(KEWN_EWW "no Avance Wogic based soundcawds found\n");
#endif
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_aws100_exit(void)
{
	pnp_unwegistew_cawd_dwivew(&aws100_pnpc_dwivew);
}

moduwe_init(awsa_cawd_aws100_init)
moduwe_exit(awsa_cawd_aws100_exit)
