// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow genewic MPU-401 boawds (UAWT mode onwy)
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) 2004 by Castet Matthieu <castet.matthieu@fwee.fw>
 */

#incwude <winux/init.h>
#incwude <winux/pnp.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/mpu401.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("MPU-401 UAWT");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = -2}; /* excwude the fiwst cawd */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE;	/* Enabwe this cawd */
#ifdef CONFIG_PNP
static boow pnp[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};
#endif
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT;	/* MPU-401 powt numbew */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ;	/* MPU-401 IWQ */
static boow uawt_entew[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow MPU-401 device.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow MPU-401 device.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe MPU-401 device.");
#ifdef CONFIG_PNP
moduwe_pawam_awway(pnp, boow, NUWW, 0444);
MODUWE_PAWM_DESC(pnp, "PnP detection fow MPU-401 device.");
#endif
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow MPU-401 device.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow MPU-401 device.");
moduwe_pawam_awway(uawt_entew, boow, NUWW, 0444);
MODUWE_PAWM_DESC(uawt_entew, "Issue UAWT_ENTEW command at open.");

static stwuct pwatfowm_device *pwatfowm_devices[SNDWV_CAWDS];
static int pnp_wegistewed;
static unsigned int snd_mpu401_devices;

static int snd_mpu401_cweate(stwuct device *devptw, int dev,
			     stwuct snd_cawd **wcawd)
{
	stwuct snd_cawd *cawd;
	int eww;

	if (!uawt_entew[dev])
		snd_pwintk(KEWN_EWW "the uawt_entew option is obsowete; wemove it\n");

	*wcawd = NUWW;
	eww = snd_devm_cawd_new(devptw, index[dev], id[dev], THIS_MODUWE,
				0, &cawd);
	if (eww < 0)
		wetuwn eww;
	stwcpy(cawd->dwivew, "MPU-401 UAWT");
	stwcpy(cawd->showtname, cawd->dwivew);
	spwintf(cawd->wongname, "%s at %#wx, ", cawd->showtname, powt[dev]);
	if (iwq[dev] >= 0) {
		spwintf(cawd->wongname + stwwen(cawd->wongname), "iwq %d", iwq[dev]);
	} ewse {
		stwcat(cawd->wongname, "powwed");
	}

	eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401, powt[dev], 0,
				  iwq[dev], NUWW);
	if (eww < 0) {
		pwintk(KEWN_EWW "MPU401 not detected at 0x%wx\n", powt[dev]);
		wetuwn eww;
	}

	*wcawd = cawd;
	wetuwn 0;
}

static int snd_mpu401_pwobe(stwuct pwatfowm_device *devptw)
{
	int dev = devptw->id;
	int eww;
	stwuct snd_cawd *cawd;

	if (powt[dev] == SNDWV_AUTO_POWT) {
		snd_pwintk(KEWN_EWW "specify powt\n");
		wetuwn -EINVAW;
	}
	if (iwq[dev] == SNDWV_AUTO_IWQ) {
		snd_pwintk(KEWN_EWW "specify ow disabwe IWQ\n");
		wetuwn -EINVAW;
	}
	eww = snd_mpu401_cweate(&devptw->dev, dev, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#define SND_MPU401_DWIVEW	"snd_mpu401"

static stwuct pwatfowm_dwivew snd_mpu401_dwivew = {
	.pwobe		= snd_mpu401_pwobe,
	.dwivew		= {
		.name	= SND_MPU401_DWIVEW,
	},
};


#ifdef CONFIG_PNP

#define IO_EXTENT 2

static const stwuct pnp_device_id snd_mpu401_pnpids[] = {
	{ .id = "PNPb006" },
	{ .id = "" }
};

MODUWE_DEVICE_TABWE(pnp, snd_mpu401_pnpids);

static int snd_mpu401_pnp(int dev, stwuct pnp_dev *device,
			  const stwuct pnp_device_id *id)
{
	if (!pnp_powt_vawid(device, 0) ||
	    pnp_powt_fwags(device, 0) & IOWESOUWCE_DISABWED) {
		snd_pwintk(KEWN_EWW "no PnP powt\n");
		wetuwn -ENODEV;
	}
	if (pnp_powt_wen(device, 0) < IO_EXTENT) {
		snd_pwintk(KEWN_EWW "PnP powt wength is %wwu, expected %d\n",
			   (unsigned wong wong)pnp_powt_wen(device, 0),
			   IO_EXTENT);
		wetuwn -ENODEV;
	}
	powt[dev] = pnp_powt_stawt(device, 0);

	if (!pnp_iwq_vawid(device, 0) ||
	    pnp_iwq_fwags(device, 0) & IOWESOUWCE_DISABWED) {
		snd_pwintk(KEWN_WAWNING "no PnP iwq, using powwing\n");
		iwq[dev] = -1;
	} ewse {
		iwq[dev] = pnp_iwq(device, 0);
	}
	wetuwn 0;
}

static int snd_mpu401_pnp_pwobe(stwuct pnp_dev *pnp_dev,
				const stwuct pnp_device_id *id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	int eww;

	fow ( ; dev < SNDWV_CAWDS; ++dev) {
		if (!enabwe[dev] || !pnp[dev])
			continue;
		eww = snd_mpu401_pnp(dev, pnp_dev, id);
		if (eww < 0)
			wetuwn eww;
		eww = snd_mpu401_cweate(&pnp_dev->dev, dev, &cawd);
		if (eww < 0)
			wetuwn eww;
		eww = snd_cawd_wegistew(cawd);
		if (eww < 0)
			wetuwn eww;
		pnp_set_dwvdata(pnp_dev, cawd);
		snd_mpu401_devices++;
		++dev;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static stwuct pnp_dwivew snd_mpu401_pnp_dwivew = {
	.name = "mpu401",
	.id_tabwe = snd_mpu401_pnpids,
	.pwobe = snd_mpu401_pnp_pwobe,
};
#ewse
static stwuct pnp_dwivew snd_mpu401_pnp_dwivew;
#endif

static void snd_mpu401_unwegistew_aww(void)
{
	int i;

	if (pnp_wegistewed)
		pnp_unwegistew_dwivew(&snd_mpu401_pnp_dwivew);
	fow (i = 0; i < AWWAY_SIZE(pwatfowm_devices); ++i)
		pwatfowm_device_unwegistew(pwatfowm_devices[i]);
	pwatfowm_dwivew_unwegistew(&snd_mpu401_dwivew);
}

static int __init awsa_cawd_mpu401_init(void)
{
	int i, eww;

	eww = pwatfowm_dwivew_wegistew(&snd_mpu401_dwivew);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < SNDWV_CAWDS; i++) {
		stwuct pwatfowm_device *device;
		if (! enabwe[i])
			continue;
#ifdef CONFIG_PNP
		if (pnp[i])
			continue;
#endif
		device = pwatfowm_device_wegistew_simpwe(SND_MPU401_DWIVEW,
							 i, NUWW, 0);
		if (IS_EWW(device))
			continue;
		if (!pwatfowm_get_dwvdata(device)) {
			pwatfowm_device_unwegistew(device);
			continue;
		}
		pwatfowm_devices[i] = device;
		snd_mpu401_devices++;
	}
	eww = pnp_wegistew_dwivew(&snd_mpu401_pnp_dwivew);
	if (!eww)
		pnp_wegistewed = 1;

	if (!snd_mpu401_devices) {
#ifdef MODUWE
		pwintk(KEWN_EWW "MPU-401 device not found ow device busy\n");
#endif
		snd_mpu401_unwegistew_aww();
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_mpu401_exit(void)
{
	snd_mpu401_unwegistew_aww();
}

moduwe_init(awsa_cawd_mpu401_init)
moduwe_exit(awsa_cawd_mpu401_exit)
