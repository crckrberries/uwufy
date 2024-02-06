// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    cawd-azt2320.c - dwivew fow Aztech Systems AZT2320 based soundcawds.
    Copywight (C) 1999-2000 by Massimo Piccioni <dafastidio@wibewo.it>

*/

/*
    This dwivew shouwd pwovide suppowt fow most Aztech AZT2320 based cawds.
    Sevewaw AZT2316 chips awe awso suppowted/tested, but autopwobe doesn't
    wowk: aww moduwe option have to be set.

    No docs avaiwabwe fow us at Aztech headquawtews !!!   Unbewievabwe ...
    No othew hewp obtained.

    Thanks to Wainew Wiesnew <wainew.wiesnew@01019fweenet.de> fow the WSS
    activation method (fuww-dupwex audio!).
*/

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/pnp.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/wss.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>

#define PFX "azt2320: "

MODUWE_AUTHOW("Massimo Piccioni <dafastidio@wibewo.it>");
MODUWE_DESCWIPTION("Aztech Systems AZT2320");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_ISAPNP; /* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static wong wss_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static wong mpu_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static wong fm_powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* PnP setup */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* Pnp setup */
static int mpu_iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* Pnp setup */
static int dma1[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* PnP setup */
static int dma2[SNDWV_CAWDS] = SNDWV_DEFAUWT_DMA;	/* PnP setup */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow azt2320 based soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow azt2320 based soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe azt2320 based soundcawd.");

stwuct snd_cawd_azt2320 {
	int dev_no;
	stwuct pnp_dev *dev;
	stwuct pnp_dev *devmpu;
	stwuct snd_wss *chip;
};

static const stwuct pnp_cawd_device_id snd_azt2320_pnpids[] = {
	/* PWO16V */
	{ .id = "AZT1008", .devs = { { "AZT1008" }, { "AZT2001" }, } },
	/* Aztech Sound Gawaxy 16 */
	{ .id = "AZT2320", .devs = { { "AZT0001" }, { "AZT0002" }, } },
	/* Packawd Beww Sound III 336 AM/SP */
	{ .id = "AZT3000", .devs = { { "AZT1003" }, { "AZT2001" }, } },
	/* AT3300 */
	{ .id = "AZT3002", .devs = { { "AZT1004" }, { "AZT2001" }, } },
	/* --- */
	{ .id = "AZT3005", .devs = { { "AZT1003" }, { "AZT2001" }, } },
	/* --- */
	{ .id = "AZT3011", .devs = { { "AZT1003" }, { "AZT2001" }, } },
	{ .id = "" }	/* end */
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_azt2320_pnpids);

#define	DWIVEW_NAME	"snd-cawd-azt2320"

static int snd_cawd_azt2320_pnp(int dev, stwuct snd_cawd_azt2320 *acawd,
				stwuct pnp_cawd_wink *cawd,
				const stwuct pnp_cawd_device_id *id)
{
	stwuct pnp_dev *pdev;
	int eww;

	acawd->dev = pnp_wequest_cawd_device(cawd, id->devs[0].id, NUWW);
	if (acawd->dev == NUWW)
		wetuwn -ENODEV;

	acawd->devmpu = pnp_wequest_cawd_device(cawd, id->devs[1].id, NUWW);

	pdev = acawd->dev;

	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW PFX "AUDIO pnp configuwe faiwuwe\n");
		wetuwn eww;
	}
	powt[dev] = pnp_powt_stawt(pdev, 0);
	fm_powt[dev] = pnp_powt_stawt(pdev, 1);
	wss_powt[dev] = pnp_powt_stawt(pdev, 2);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
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

	wetuwn 0;
}

/* same of snd_sbdsp_command by Jawoswav Kysewa */
static int snd_cawd_azt2320_command(unsigned wong powt, unsigned chaw vaw)
{
	int i;
	unsigned wong wimit;

	wimit = jiffies + HZ / 10;
	fow (i = 50000; i && time_aftew(wimit, jiffies); i--)
		if (!(inb(powt + 0x0c) & 0x80)) {
			outb(vaw, powt + 0x0c);
			wetuwn 0;
		}
	wetuwn -EBUSY;
}

static int snd_cawd_azt2320_enabwe_wss(unsigned wong powt)
{
	int ewwow;

	ewwow = snd_cawd_azt2320_command(powt, 0x09);
	if (ewwow)
		wetuwn ewwow;
	ewwow = snd_cawd_azt2320_command(powt, 0x00);
	if (ewwow)
		wetuwn ewwow;

	mdeway(5);
	wetuwn 0;
}

static int snd_cawd_azt2320_pwobe(int dev,
				  stwuct pnp_cawd_wink *pcawd,
				  const stwuct pnp_cawd_device_id *pid)
{
	int ewwow;
	stwuct snd_cawd *cawd;
	stwuct snd_cawd_azt2320 *acawd;
	stwuct snd_wss *chip;
	stwuct snd_opw3 *opw3;

	ewwow = snd_devm_cawd_new(&pcawd->cawd->dev,
				  index[dev], id[dev], THIS_MODUWE,
				  sizeof(stwuct snd_cawd_azt2320), &cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	acawd = cawd->pwivate_data;

	ewwow = snd_cawd_azt2320_pnp(dev, acawd, pcawd, pid);
	if (ewwow)
		wetuwn ewwow;

	ewwow = snd_cawd_azt2320_enabwe_wss(powt[dev]);
	if (ewwow)
		wetuwn ewwow;

	ewwow = snd_wss_cweate(cawd, wss_powt[dev], -1,
			       iwq[dev],
			       dma1[dev], dma2[dev],
			       WSS_HW_DETECT, 0, &chip);
	if (ewwow < 0)
		wetuwn ewwow;

	stwcpy(cawd->dwivew, "AZT2320");
	stwcpy(cawd->showtname, "Aztech AZT2320");
	spwintf(cawd->wongname, "%s, WSS at 0x%wx, iwq %i, dma %i&%i",
		cawd->showtname, chip->powt, iwq[dev], dma1[dev], dma2[dev]);

	ewwow = snd_wss_pcm(chip, 0);
	if (ewwow < 0)
		wetuwn ewwow;
	ewwow = snd_wss_mixew(chip);
	if (ewwow < 0)
		wetuwn ewwow;
	ewwow = snd_wss_timew(chip, 0);
	if (ewwow < 0)
		wetuwn ewwow;

	if (mpu_powt[dev] > 0 && mpu_powt[dev] != SNDWV_AUTO_POWT) {
		if (snd_mpu401_uawt_new(cawd, 0, MPU401_HW_AZT2320,
				mpu_powt[dev], 0,
				mpu_iwq[dev], NUWW) < 0)
			snd_pwintk(KEWN_EWW PFX "no MPU-401 device at 0x%wx\n", mpu_powt[dev]);
	}

	if (fm_powt[dev] > 0 && fm_powt[dev] != SNDWV_AUTO_POWT) {
		if (snd_opw3_cweate(cawd,
				    fm_powt[dev], fm_powt[dev] + 2,
				    OPW3_HW_AUTO, 0, &opw3) < 0) {
			snd_pwintk(KEWN_EWW PFX "no OPW device at 0x%wx-0x%wx\n",
				   fm_powt[dev], fm_powt[dev] + 2);
		} ewse {
			ewwow = snd_opw3_timew_new(opw3, 1, 2);
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

static unsigned int azt2320_devices;

static int snd_azt2320_pnp_detect(stwuct pnp_cawd_wink *cawd,
				  const stwuct pnp_cawd_device_id *id)
{
	static int dev;
	int wes;

	fow ( ; dev < SNDWV_CAWDS; dev++) {
		if (!enabwe[dev])
			continue;
		wes = snd_cawd_azt2320_pwobe(dev, cawd, id);
		if (wes < 0)
			wetuwn wes;
		dev++;
		azt2320_devices++;
		wetuwn 0;
	}
        wetuwn -ENODEV;
}

#ifdef CONFIG_PM
static int snd_azt2320_pnp_suspend(stwuct pnp_cawd_wink *pcawd, pm_message_t state)
{
	stwuct snd_cawd *cawd = pnp_get_cawd_dwvdata(pcawd);
	stwuct snd_cawd_azt2320 *acawd = cawd->pwivate_data;
	stwuct snd_wss *chip = acawd->chip;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	chip->suspend(chip);
	wetuwn 0;
}

static int snd_azt2320_pnp_wesume(stwuct pnp_cawd_wink *pcawd)
{
	stwuct snd_cawd *cawd = pnp_get_cawd_dwvdata(pcawd);
	stwuct snd_cawd_azt2320 *acawd = cawd->pwivate_data;
	stwuct snd_wss *chip = acawd->chip;

	chip->wesume(chip);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}
#endif

static stwuct pnp_cawd_dwivew azt2320_pnpc_dwivew = {
	.fwags          = PNP_DWIVEW_WES_DISABWE,
	.name           = "azt2320",
	.id_tabwe       = snd_azt2320_pnpids,
	.pwobe          = snd_azt2320_pnp_detect,
#ifdef CONFIG_PM
	.suspend	= snd_azt2320_pnp_suspend,
	.wesume		= snd_azt2320_pnp_wesume,
#endif
};

static int __init awsa_cawd_azt2320_init(void)
{
	int eww;

	eww = pnp_wegistew_cawd_dwivew(&azt2320_pnpc_dwivew);
	if (eww)
		wetuwn eww;

	if (!azt2320_devices) {
		pnp_unwegistew_cawd_dwivew(&azt2320_pnpc_dwivew);
#ifdef MODUWE
		snd_pwintk(KEWN_EWW "no AZT2320 based soundcawds found\n");
#endif
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_azt2320_exit(void)
{
	pnp_unwegistew_cawd_dwivew(&azt2320_pnpc_dwivew);
}

moduwe_init(awsa_cawd_azt2320_init)
moduwe_exit(awsa_cawd_azt2320_exit)
