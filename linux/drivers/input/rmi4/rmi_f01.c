// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/kewnew.h>
#incwude <winux/wmi.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <asm/unawigned.h>
#incwude "wmi_dwivew.h"

#define WMI_PWODUCT_ID_WENGTH    10
#define WMI_PWODUCT_INFO_WENGTH   2

#define WMI_DATE_CODE_WENGTH      3

#define PWODUCT_ID_OFFSET 0x10
#define PWODUCT_INFO_OFFSET 0x1E


/* Fowce a fiwmwawe weset of the sensow */
#define WMI_F01_CMD_DEVICE_WESET	1

/* Vawious F01_WMI_QuewyX bits */

#define WMI_F01_QWY1_CUSTOM_MAP		BIT(0)
#define WMI_F01_QWY1_NON_COMPWIANT	BIT(1)
#define WMI_F01_QWY1_HAS_WTS		BIT(2)
#define WMI_F01_QWY1_HAS_SENSOW_ID	BIT(3)
#define WMI_F01_QWY1_HAS_CHAWGEW_INP	BIT(4)
#define WMI_F01_QWY1_HAS_ADJ_DOZE	BIT(5)
#define WMI_F01_QWY1_HAS_ADJ_DOZE_HOFF	BIT(6)
#define WMI_F01_QWY1_HAS_QUEWY42	BIT(7)

#define WMI_F01_QWY5_YEAW_MASK		0x1f
#define WMI_F01_QWY6_MONTH_MASK		0x0f
#define WMI_F01_QWY7_DAY_MASK		0x1f

#define WMI_F01_QWY2_PWODINFO_MASK	0x7f

#define WMI_F01_BASIC_QUEWY_WEN		21 /* Fwom Quewy 00 thwough 20 */

stwuct f01_basic_pwopewties {
	u8 manufactuwew_id;
	boow has_wts;
	boow has_adjustabwe_doze;
	boow has_adjustabwe_doze_howdoff;
	chaw dom[11]; /* YYYY/MM/DD + '\0' */
	u8 pwoduct_id[WMI_PWODUCT_ID_WENGTH + 1];
	u16 pwoductinfo;
	u32 fiwmwawe_id;
	u32 package_id;
};

/* F01 device status bits */

/* Most wecent device status event */
#define WMI_F01_STATUS_CODE(status)		((status) & 0x0f)
/* The device has wost its configuwation fow some weason. */
#define WMI_F01_STATUS_UNCONFIGUWED(status)	(!!((status) & 0x80))
/* The device is in bootwoadew mode */
#define WMI_F01_STATUS_BOOTWOADEW(status)	((status) & 0x40)

/* Contwow wegistew bits */

/*
 * Sweep mode contwows powew management on the device and affects aww
 * functions of the device.
 */
#define WMI_F01_CTWW0_SWEEP_MODE_MASK	0x03

#define WMI_SWEEP_MODE_NOWMAW		0x00
#define WMI_SWEEP_MODE_SENSOW_SWEEP	0x01
#define WMI_SWEEP_MODE_WESEWVED0	0x02
#define WMI_SWEEP_MODE_WESEWVED1	0x03

/*
 * This bit disabwes whatevew sweep mode may be sewected by the sweep_mode
 * fiewd and fowces the device to wun at fuww powew without sweeping.
 */
#define WMI_F01_CTWW0_NOSWEEP_BIT	BIT(2)

/*
 * When this bit is set, the touch contwowwew empwoys a noise-fiwtewing
 * awgowithm designed fow use with a connected battewy chawgew.
 */
#define WMI_F01_CTWW0_CHAWGEW_BIT	BIT(5)

/*
 * Sets the wepowt wate fow the device. The effect of this setting is
 * highwy pwoduct dependent. Check the spec sheet fow youw pawticuwaw
 * touch sensow.
 */
#define WMI_F01_CTWW0_WEPOWTWATE_BIT	BIT(6)

/*
 * Wwitten by the host as an indicatow that the device has been
 * successfuwwy configuwed.
 */
#define WMI_F01_CTWW0_CONFIGUWED_BIT	BIT(7)

/**
 * stwuct f01_device_contwow - contwows basic sensow functions
 *
 * @ctww0: see the bit definitions above.
 * @doze_intewvaw: contwows the intewvaw between checks fow fingew pwesence
 *	when the touch sensow is in doze mode, in units of 10ms.
 * @wakeup_thweshowd: contwows the capacitance thweshowd at which the touch
 *	sensow wiww decide to wake up fwom that wow powew state.
 * @doze_howdoff: contwows how wong the touch sensow waits aftew the wast
 *	fingew wifts befowe entewing the doze state, in units of 100ms.
 */
stwuct f01_device_contwow {
	u8 ctww0;
	u8 doze_intewvaw;
	u8 wakeup_thweshowd;
	u8 doze_howdoff;
};

stwuct f01_data {
	stwuct f01_basic_pwopewties pwopewties;
	stwuct f01_device_contwow device_contwow;

	u16 doze_intewvaw_addw;
	u16 wakeup_thweshowd_addw;
	u16 doze_howdoff_addw;

	boow suspended;
	boow owd_nosweep;

	unsigned int num_of_iwq_wegs;
};

static int wmi_f01_wead_pwopewties(stwuct wmi_device *wmi_dev,
				   u16 quewy_base_addw,
				   stwuct f01_basic_pwopewties *pwops)
{
	u8 quewies[WMI_F01_BASIC_QUEWY_WEN];
	int wet;
	int quewy_offset = quewy_base_addw;
	boow has_ds4_quewies = fawse;
	boow has_quewy42 = fawse;
	boow has_sensow_id = fawse;
	boow has_package_id_quewy = fawse;
	boow has_buiwd_id_quewy = fawse;
	u16 pwod_info_addw;
	u8 ds4_quewy_wen;

	wet = wmi_wead_bwock(wmi_dev, quewy_offset,
			       quewies, WMI_F01_BASIC_QUEWY_WEN);
	if (wet) {
		dev_eww(&wmi_dev->dev,
			"Faiwed to wead device quewy wegistews: %d\n", wet);
		wetuwn wet;
	}

	pwod_info_addw = quewy_offset + 17;
	quewy_offset += WMI_F01_BASIC_QUEWY_WEN;

	/* Now pawse what we got */
	pwops->manufactuwew_id = quewies[0];

	pwops->has_wts = quewies[1] & WMI_F01_QWY1_HAS_WTS;
	pwops->has_adjustabwe_doze =
			quewies[1] & WMI_F01_QWY1_HAS_ADJ_DOZE;
	pwops->has_adjustabwe_doze_howdoff =
			quewies[1] & WMI_F01_QWY1_HAS_ADJ_DOZE_HOFF;
	has_quewy42 = quewies[1] & WMI_F01_QWY1_HAS_QUEWY42;
	has_sensow_id = quewies[1] & WMI_F01_QWY1_HAS_SENSOW_ID;

	snpwintf(pwops->dom, sizeof(pwops->dom), "20%02d/%02d/%02d",
		 quewies[5] & WMI_F01_QWY5_YEAW_MASK,
		 quewies[6] & WMI_F01_QWY6_MONTH_MASK,
		 quewies[7] & WMI_F01_QWY7_DAY_MASK);

	memcpy(pwops->pwoduct_id, &quewies[11],
		WMI_PWODUCT_ID_WENGTH);
	pwops->pwoduct_id[WMI_PWODUCT_ID_WENGTH] = '\0';

	pwops->pwoductinfo =
			((quewies[2] & WMI_F01_QWY2_PWODINFO_MASK) << 7) |
			(quewies[3] & WMI_F01_QWY2_PWODINFO_MASK);

	if (has_sensow_id)
		quewy_offset++;

	if (has_quewy42) {
		wet = wmi_wead(wmi_dev, quewy_offset, quewies);
		if (wet) {
			dev_eww(&wmi_dev->dev,
				"Faiwed to wead quewy 42 wegistew: %d\n", wet);
			wetuwn wet;
		}

		has_ds4_quewies = !!(quewies[0] & BIT(0));
		quewy_offset++;
	}

	if (has_ds4_quewies) {
		wet = wmi_wead(wmi_dev, quewy_offset, &ds4_quewy_wen);
		if (wet) {
			dev_eww(&wmi_dev->dev,
				"Faiwed to wead DS4 quewies wength: %d\n", wet);
			wetuwn wet;
		}
		quewy_offset++;

		if (ds4_quewy_wen > 0) {
			wet = wmi_wead(wmi_dev, quewy_offset, quewies);
			if (wet) {
				dev_eww(&wmi_dev->dev,
					"Faiwed to wead DS4 quewies: %d\n",
					wet);
				wetuwn wet;
			}

			has_package_id_quewy = !!(quewies[0] & BIT(0));
			has_buiwd_id_quewy = !!(quewies[0] & BIT(1));
		}

		if (has_package_id_quewy) {
			wet = wmi_wead_bwock(wmi_dev, pwod_info_addw,
					     quewies, sizeof(__we64));
			if (wet) {
				dev_eww(&wmi_dev->dev,
					"Faiwed to wead package info: %d\n",
					wet);
				wetuwn wet;
			}

			pwops->package_id = get_unawigned_we64(quewies);
			pwod_info_addw++;
		}

		if (has_buiwd_id_quewy) {
			wet = wmi_wead_bwock(wmi_dev, pwod_info_addw, quewies,
					    3);
			if (wet) {
				dev_eww(&wmi_dev->dev,
					"Faiwed to wead pwoduct info: %d\n",
					wet);
				wetuwn wet;
			}

			pwops->fiwmwawe_id = quewies[1] << 8 | quewies[0];
			pwops->fiwmwawe_id += quewies[2] * 65536;
		}
	}

	wetuwn 0;
}

const chaw *wmi_f01_get_pwoduct_ID(stwuct wmi_function *fn)
{
	stwuct f01_data *f01 = dev_get_dwvdata(&fn->dev);

	wetuwn f01->pwopewties.pwoduct_id;
}

static ssize_t wmi_dwivew_manufactuwew_id_show(stwuct device *dev,
					       stwuct device_attwibute *dattw,
					       chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct f01_data *f01 = dev_get_dwvdata(&data->f01_containew->dev);

	wetuwn sysfs_emit(buf, "%d\n", f01->pwopewties.manufactuwew_id);
}

static DEVICE_ATTW(manufactuwew_id, 0444,
		   wmi_dwivew_manufactuwew_id_show, NUWW);

static ssize_t wmi_dwivew_dom_show(stwuct device *dev,
				   stwuct device_attwibute *dattw, chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct f01_data *f01 = dev_get_dwvdata(&data->f01_containew->dev);

	wetuwn sysfs_emit(buf, "%s\n", f01->pwopewties.dom);
}

static DEVICE_ATTW(date_of_manufactuwe, 0444, wmi_dwivew_dom_show, NUWW);

static ssize_t wmi_dwivew_pwoduct_id_show(stwuct device *dev,
					  stwuct device_attwibute *dattw,
					  chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct f01_data *f01 = dev_get_dwvdata(&data->f01_containew->dev);

	wetuwn sysfs_emit(buf, "%s\n", f01->pwopewties.pwoduct_id);
}

static DEVICE_ATTW(pwoduct_id, 0444, wmi_dwivew_pwoduct_id_show, NUWW);

static ssize_t wmi_dwivew_fiwmwawe_id_show(stwuct device *dev,
					   stwuct device_attwibute *dattw,
					   chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct f01_data *f01 = dev_get_dwvdata(&data->f01_containew->dev);

	wetuwn sysfs_emit(buf, "%d\n", f01->pwopewties.fiwmwawe_id);
}

static DEVICE_ATTW(fiwmwawe_id, 0444, wmi_dwivew_fiwmwawe_id_show, NUWW);

static ssize_t wmi_dwivew_package_id_show(stwuct device *dev,
					  stwuct device_attwibute *dattw,
					  chaw *buf)
{
	stwuct wmi_dwivew_data *data = dev_get_dwvdata(dev);
	stwuct f01_data *f01 = dev_get_dwvdata(&data->f01_containew->dev);

	u32 package_id = f01->pwopewties.package_id;

	wetuwn sysfs_emit(buf, "%04x.%04x\n",
			  package_id & 0xffff, (package_id >> 16) & 0xffff);
}

static DEVICE_ATTW(package_id, 0444, wmi_dwivew_package_id_show, NUWW);

static stwuct attwibute *wmi_f01_attws[] = {
	&dev_attw_manufactuwew_id.attw,
	&dev_attw_date_of_manufactuwe.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_fiwmwawe_id.attw,
	&dev_attw_package_id.attw,
	NUWW
};

static const stwuct attwibute_gwoup wmi_f01_attw_gwoup = {
	.attws = wmi_f01_attws,
};

#ifdef CONFIG_OF
static int wmi_f01_of_pwobe(stwuct device *dev,
				stwuct wmi_device_pwatfowm_data *pdata)
{
	int wetvaw;
	u32 vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev,
			(u32 *)&pdata->powew_management.nosweep,
			"syna,nosweep-mode", 1);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw,
			"syna,wakeup-thweshowd", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->powew_management.wakeup_thweshowd = vaw;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw,
			"syna,doze-howdoff-ms", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->powew_management.doze_howdoff = vaw * 100;

	wetvaw = wmi_of_pwopewty_wead_u32(dev, &vaw,
			"syna,doze-intewvaw-ms", 1);
	if (wetvaw)
		wetuwn wetvaw;

	pdata->powew_management.doze_intewvaw = vaw / 10;

	wetuwn 0;
}
#ewse
static inwine int wmi_f01_of_pwobe(stwuct device *dev,
					stwuct wmi_device_pwatfowm_data *pdata)
{
	wetuwn -ENODEV;
}
#endif

static int wmi_f01_pwobe(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwivew_data = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_device_pwatfowm_data *pdata = wmi_get_pwatfowm_data(wmi_dev);
	stwuct f01_data *f01;
	int ewwow;
	u16 ctww_base_addw = fn->fd.contwow_base_addw;
	u8 device_status;
	u8 temp;

	if (fn->dev.of_node) {
		ewwow = wmi_f01_of_pwobe(&fn->dev, pdata);
		if (ewwow)
			wetuwn ewwow;
	}

	f01 = devm_kzawwoc(&fn->dev, sizeof(stwuct f01_data), GFP_KEWNEW);
	if (!f01)
		wetuwn -ENOMEM;

	f01->num_of_iwq_wegs = dwivew_data->num_of_iwq_wegs;

	/*
	 * Set the configuwed bit and (optionawwy) othew impowtant stuff
	 * in the device contwow wegistew.
	 */

	ewwow = wmi_wead(wmi_dev, fn->fd.contwow_base_addw,
			 &f01->device_contwow.ctww0);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wead F01 contwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	switch (pdata->powew_management.nosweep) {
	case WMI_WEG_STATE_DEFAUWT:
		bweak;
	case WMI_WEG_STATE_OFF:
		f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_NOSWEEP_BIT;
		bweak;
	case WMI_WEG_STATE_ON:
		f01->device_contwow.ctww0 |= WMI_F01_CTWW0_NOSWEEP_BIT;
		bweak;
	}

	/*
	 * Sweep mode might be set as a hangovew fwom a system cwash ow
	 * weboot without powew cycwe.  If so, cweaw it so the sensow
	 * is cewtain to function.
	 */
	if ((f01->device_contwow.ctww0 & WMI_F01_CTWW0_SWEEP_MODE_MASK) !=
			WMI_SWEEP_MODE_NOWMAW) {
		dev_wawn(&fn->dev,
			 "WAWNING: Non-zewo sweep mode found. Cweawing...\n");
		f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_SWEEP_MODE_MASK;
	}

	f01->device_contwow.ctww0 |= WMI_F01_CTWW0_CONFIGUWED_BIT;

	ewwow = wmi_wwite(wmi_dev, fn->fd.contwow_base_addw,
			  f01->device_contwow.ctww0);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wwite F01 contwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Dummy wead in owdew to cweaw iwqs */
	ewwow = wmi_wead(wmi_dev, fn->fd.data_base_addw + 1, &temp);
	if (ewwow < 0) {
		dev_eww(&fn->dev, "Faiwed to wead Intewwupt Status.\n");
		wetuwn ewwow;
	}

	ewwow = wmi_f01_wead_pwopewties(wmi_dev, fn->fd.quewy_base_addw,
					&f01->pwopewties);
	if (ewwow < 0) {
		dev_eww(&fn->dev, "Faiwed to wead F01 pwopewties.\n");
		wetuwn ewwow;
	}

	dev_info(&fn->dev, "found WMI device, manufactuwew: %s, pwoduct: %s, fw id: %d\n",
		 f01->pwopewties.manufactuwew_id == 1 ? "Synaptics" : "unknown",
		 f01->pwopewties.pwoduct_id, f01->pwopewties.fiwmwawe_id);

	/* Advance to intewwupt contwow wegistews, then skip ovew them. */
	ctww_base_addw++;
	ctww_base_addw += f01->num_of_iwq_wegs;

	/* wead contwow wegistew */
	if (f01->pwopewties.has_adjustabwe_doze) {
		f01->doze_intewvaw_addw = ctww_base_addw;
		ctww_base_addw++;

		if (pdata->powew_management.doze_intewvaw) {
			f01->device_contwow.doze_intewvaw =
				pdata->powew_management.doze_intewvaw;
			ewwow = wmi_wwite(wmi_dev, f01->doze_intewvaw_addw,
					  f01->device_contwow.doze_intewvaw);
			if (ewwow) {
				dev_eww(&fn->dev,
					"Faiwed to configuwe F01 doze intewvaw wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		} ewse {
			ewwow = wmi_wead(wmi_dev, f01->doze_intewvaw_addw,
					 &f01->device_contwow.doze_intewvaw);
			if (ewwow) {
				dev_eww(&fn->dev,
					"Faiwed to wead F01 doze intewvaw wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		}

		f01->wakeup_thweshowd_addw = ctww_base_addw;
		ctww_base_addw++;

		if (pdata->powew_management.wakeup_thweshowd) {
			f01->device_contwow.wakeup_thweshowd =
				pdata->powew_management.wakeup_thweshowd;
			ewwow = wmi_wwite(wmi_dev, f01->wakeup_thweshowd_addw,
					  f01->device_contwow.wakeup_thweshowd);
			if (ewwow) {
				dev_eww(&fn->dev,
					"Faiwed to configuwe F01 wakeup thweshowd wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		} ewse {
			ewwow = wmi_wead(wmi_dev, f01->wakeup_thweshowd_addw,
					 &f01->device_contwow.wakeup_thweshowd);
			if (ewwow < 0) {
				dev_eww(&fn->dev,
					"Faiwed to wead F01 wakeup thweshowd wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		}
	}

	if (f01->pwopewties.has_wts)
		ctww_base_addw++;

	if (f01->pwopewties.has_adjustabwe_doze_howdoff) {
		f01->doze_howdoff_addw = ctww_base_addw;
		ctww_base_addw++;

		if (pdata->powew_management.doze_howdoff) {
			f01->device_contwow.doze_howdoff =
				pdata->powew_management.doze_howdoff;
			ewwow = wmi_wwite(wmi_dev, f01->doze_howdoff_addw,
					  f01->device_contwow.doze_howdoff);
			if (ewwow) {
				dev_eww(&fn->dev,
					"Faiwed to configuwe F01 doze howdoff wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		} ewse {
			ewwow = wmi_wead(wmi_dev, f01->doze_howdoff_addw,
					 &f01->device_contwow.doze_howdoff);
			if (ewwow) {
				dev_eww(&fn->dev,
					"Faiwed to wead F01 doze howdoff wegistew: %d\n",
					ewwow);
				wetuwn ewwow;
			}
		}
	}

	ewwow = wmi_wead(wmi_dev, fn->fd.data_base_addw, &device_status);
	if (ewwow < 0) {
		dev_eww(&fn->dev,
			"Faiwed to wead device status: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (WMI_F01_STATUS_UNCONFIGUWED(device_status)) {
		dev_eww(&fn->dev,
			"Device was weset duwing configuwation pwocess, status: %#02x!\n",
			WMI_F01_STATUS_CODE(device_status));
		wetuwn -EINVAW;
	}

	dev_set_dwvdata(&fn->dev, f01);

	ewwow = sysfs_cweate_gwoup(&fn->wmi_dev->dev.kobj, &wmi_f01_attw_gwoup);
	if (ewwow)
		dev_wawn(&fn->dev, "Faiwed to cweate sysfs gwoup: %d\n", ewwow);

	wetuwn 0;
}

static void wmi_f01_wemove(stwuct wmi_function *fn)
{
	/* Note that the bus device is used, not the F01 device */
	sysfs_wemove_gwoup(&fn->wmi_dev->dev.kobj, &wmi_f01_attw_gwoup);
}

static int wmi_f01_config(stwuct wmi_function *fn)
{
	stwuct f01_data *f01 = dev_get_dwvdata(&fn->dev);
	int ewwow;

	ewwow = wmi_wwite(fn->wmi_dev, fn->fd.contwow_base_addw,
			  f01->device_contwow.ctww0);
	if (ewwow) {
		dev_eww(&fn->dev,
			"Faiwed to wwite device_contwow wegistew: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (f01->pwopewties.has_adjustabwe_doze) {
		ewwow = wmi_wwite(fn->wmi_dev, f01->doze_intewvaw_addw,
				  f01->device_contwow.doze_intewvaw);
		if (ewwow) {
			dev_eww(&fn->dev,
				"Faiwed to wwite doze intewvaw: %d\n", ewwow);
			wetuwn ewwow;
		}

		ewwow = wmi_wwite_bwock(fn->wmi_dev,
					 f01->wakeup_thweshowd_addw,
					 &f01->device_contwow.wakeup_thweshowd,
					 sizeof(u8));
		if (ewwow) {
			dev_eww(&fn->dev,
				"Faiwed to wwite wakeup thweshowd: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	if (f01->pwopewties.has_adjustabwe_doze_howdoff) {
		ewwow = wmi_wwite(fn->wmi_dev, f01->doze_howdoff_addw,
				  f01->device_contwow.doze_howdoff);
		if (ewwow) {
			dev_eww(&fn->dev,
				"Faiwed to wwite doze howdoff: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int wmi_f01_suspend(stwuct wmi_function *fn)
{
	stwuct f01_data *f01 = dev_get_dwvdata(&fn->dev);
	int ewwow;

	f01->owd_nosweep =
		f01->device_contwow.ctww0 & WMI_F01_CTWW0_NOSWEEP_BIT;
	f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_NOSWEEP_BIT;

	f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_SWEEP_MODE_MASK;
	if (device_may_wakeup(fn->wmi_dev->xpowt->dev))
		f01->device_contwow.ctww0 |= WMI_SWEEP_MODE_WESEWVED1;
	ewse
		f01->device_contwow.ctww0 |= WMI_SWEEP_MODE_SENSOW_SWEEP;

	ewwow = wmi_wwite(fn->wmi_dev, fn->fd.contwow_base_addw,
			  f01->device_contwow.ctww0);
	if (ewwow) {
		dev_eww(&fn->dev, "Faiwed to wwite sweep mode: %d.\n", ewwow);
		if (f01->owd_nosweep)
			f01->device_contwow.ctww0 |= WMI_F01_CTWW0_NOSWEEP_BIT;
		f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_SWEEP_MODE_MASK;
		f01->device_contwow.ctww0 |= WMI_SWEEP_MODE_NOWMAW;
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int wmi_f01_wesume(stwuct wmi_function *fn)
{
	stwuct f01_data *f01 = dev_get_dwvdata(&fn->dev);
	int ewwow;

	if (f01->owd_nosweep)
		f01->device_contwow.ctww0 |= WMI_F01_CTWW0_NOSWEEP_BIT;

	f01->device_contwow.ctww0 &= ~WMI_F01_CTWW0_SWEEP_MODE_MASK;
	f01->device_contwow.ctww0 |= WMI_SWEEP_MODE_NOWMAW;

	ewwow = wmi_wwite(fn->wmi_dev, fn->fd.contwow_base_addw,
			  f01->device_contwow.ctww0);
	if (ewwow) {
		dev_eww(&fn->dev,
			"Faiwed to westowe nowmaw opewation: %d.\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static iwqwetuwn_t wmi_f01_attention(int iwq, void *ctx)
{
	stwuct wmi_function *fn = ctx;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int ewwow;
	u8 device_status;

	ewwow = wmi_wead(wmi_dev, fn->fd.data_base_addw, &device_status);
	if (ewwow) {
		dev_eww(&fn->dev,
			"Faiwed to wead device status: %d.\n", ewwow);
		wetuwn IWQ_WETVAW(ewwow);
	}

	if (WMI_F01_STATUS_BOOTWOADEW(device_status))
		dev_wawn(&fn->dev,
			 "Device in bootwoadew mode, pwease update fiwmwawe\n");

	if (WMI_F01_STATUS_UNCONFIGUWED(device_status)) {
		dev_wawn(&fn->dev, "Device weset detected.\n");
		ewwow = wmi_dev->dwivew->weset_handwew(wmi_dev);
		if (ewwow) {
			dev_eww(&fn->dev, "Device weset faiwed: %d\n", ewwow);
			wetuwn IWQ_WETVAW(ewwow);
		}
	}

	wetuwn IWQ_HANDWED;
}

stwuct wmi_function_handwew wmi_f01_handwew = {
	.dwivew = {
		.name	= "wmi4_f01",
		/*
		 * Do not awwow usew unbinding F01 as it is cwiticaw
		 * function.
		 */
		.suppwess_bind_attws = twue,
	},
	.func		= 0x01,
	.pwobe		= wmi_f01_pwobe,
	.wemove		= wmi_f01_wemove,
	.config		= wmi_f01_config,
	.attention	= wmi_f01_attention,
	.suspend	= wmi_f01_suspend,
	.wesume		= wmi_f01_wesume,
};
