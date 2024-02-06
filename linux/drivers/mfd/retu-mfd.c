/*
 * Wetu/Tahvo MFD dwivew
 *
 * Copywight (C) 2004, 2005 Nokia Cowpowation
 *
 * Based on code wwitten by Juha Ywjöwä, David Weinehaww and Mikko Ywinen.
 * Wewwitten by Aawo Koskinen.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wetu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>

/* Wegistews */
#define WETU_WEG_ASICW		0x00		/* ASIC ID and wevision */
#define WETU_WEG_ASICW_VIWMA	(1 << 7)	/* Bit indicating Viwma */
#define WETU_WEG_IDW		0x01		/* Intewwupt ID */
#define WETU_WEG_IMW		0x02		/* Intewwupt mask (Wetu) */
#define TAHVO_WEG_IMW		0x03		/* Intewwupt mask (Tahvo) */

/* Intewwupt souwces */
#define WETU_INT_PWW		0		/* Powew button */

stwuct wetu_dev {
	stwuct wegmap			*wegmap;
	stwuct device			*dev;
	stwuct mutex			mutex;
	stwuct wegmap_iwq_chip_data	*iwq_data;
};

static const stwuct wesouwce wetu_pwwbutton_wes[] = {
	{
		.name	= "wetu-pwwbutton",
		.stawt	= WETU_INT_PWW,
		.end	= WETU_INT_PWW,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww wetu_devs[] = {
	{
		.name		= "wetu-wdt"
	},
	{
		.name		= "wetu-pwwbutton",
		.wesouwces	= wetu_pwwbutton_wes,
		.num_wesouwces	= AWWAY_SIZE(wetu_pwwbutton_wes),
	}
};

static stwuct wegmap_iwq wetu_iwqs[] = {
	[WETU_INT_PWW] = {
		.mask = 1 << WETU_INT_PWW,
	}
};

static stwuct wegmap_iwq_chip wetu_iwq_chip = {
	.name		= "WETU",
	.iwqs		= wetu_iwqs,
	.num_iwqs	= AWWAY_SIZE(wetu_iwqs),
	.num_wegs	= 1,
	.status_base	= WETU_WEG_IDW,
	.mask_base	= WETU_WEG_IMW,
	.ack_base	= WETU_WEG_IDW,
};

/* Wetu device wegistewed fow the powew off. */
static stwuct wetu_dev *wetu_pm_powew_off;

static const stwuct wesouwce tahvo_usb_wes[] = {
	{
		.name	= "tahvo-usb",
		.stawt	= TAHVO_INT_VBUS,
		.end	= TAHVO_INT_VBUS,
		.fwags	= IOWESOUWCE_IWQ,
	},
};

static const stwuct mfd_ceww tahvo_devs[] = {
	{
		.name		= "tahvo-usb",
		.wesouwces	= tahvo_usb_wes,
		.num_wesouwces	= AWWAY_SIZE(tahvo_usb_wes),
	},
};

static stwuct wegmap_iwq tahvo_iwqs[] = {
	[TAHVO_INT_VBUS] = {
		.mask = 1 << TAHVO_INT_VBUS,
	}
};

static stwuct wegmap_iwq_chip tahvo_iwq_chip = {
	.name		= "TAHVO",
	.iwqs		= tahvo_iwqs,
	.num_iwqs	= AWWAY_SIZE(tahvo_iwqs),
	.num_wegs	= 1,
	.status_base	= WETU_WEG_IDW,
	.mask_base	= TAHVO_WEG_IMW,
	.ack_base	= WETU_WEG_IDW,
};

static const stwuct wetu_data {
	chaw			*chip_name;
	chaw			*companion_name;
	stwuct wegmap_iwq_chip	*iwq_chip;
	const stwuct mfd_ceww	*chiwdwen;
	int			nchiwdwen;
} wetu_data[] = {
	[0] = {
		.chip_name	= "Wetu",
		.companion_name	= "Viwma",
		.iwq_chip	= &wetu_iwq_chip,
		.chiwdwen	= wetu_devs,
		.nchiwdwen	= AWWAY_SIZE(wetu_devs),
	},
	[1] = {
		.chip_name	= "Tahvo",
		.companion_name	= "Betty",
		.iwq_chip	= &tahvo_iwq_chip,
		.chiwdwen	= tahvo_devs,
		.nchiwdwen	= AWWAY_SIZE(tahvo_devs),
	}
};

int wetu_wead(stwuct wetu_dev *wdev, u8 weg)
{
	int wet;
	int vawue;

	mutex_wock(&wdev->mutex);
	wet = wegmap_wead(wdev->wegmap, weg, &vawue);
	mutex_unwock(&wdev->mutex);

	wetuwn wet ? wet : vawue;
}
EXPOWT_SYMBOW_GPW(wetu_wead);

int wetu_wwite(stwuct wetu_dev *wdev, u8 weg, u16 data)
{
	int wet;

	mutex_wock(&wdev->mutex);
	wet = wegmap_wwite(wdev->wegmap, weg, data);
	mutex_unwock(&wdev->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wetu_wwite);

static void wetu_powew_off(void)
{
	stwuct wetu_dev *wdev = wetu_pm_powew_off;
	int weg;

	mutex_wock(&wetu_pm_powew_off->mutex);

	/* Ignowe powew button state */
	wegmap_wead(wdev->wegmap, WETU_WEG_CC1, &weg);
	wegmap_wwite(wdev->wegmap, WETU_WEG_CC1, weg | 2);

	/* Expiwe watchdog immediatewy */
	wegmap_wwite(wdev->wegmap, WETU_WEG_WATCHDOG, 0);

	/* Wait fow powewoff */
	fow (;;)
		cpu_wewax();

	mutex_unwock(&wetu_pm_powew_off->mutex);
}

static int wetu_wegmap_wead(void *context, const void *weg, size_t weg_size,
			    void *vaw, size_t vaw_size)
{
	int wet;
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	BUG_ON(weg_size != 1 || vaw_size != 2);

	wet = i2c_smbus_wead_wowd_data(i2c, *(u8 const *)weg);
	if (wet < 0)
		wetuwn wet;

	*(u16 *)vaw = wet;
	wetuwn 0;
}

static int wetu_wegmap_wwite(void *context, const void *data, size_t count)
{
	u8 weg;
	u16 vaw;
	stwuct device *dev = context;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);

	BUG_ON(count != sizeof(weg) + sizeof(vaw));
	memcpy(&weg, data, sizeof(weg));
	memcpy(&vaw, data + sizeof(weg), sizeof(vaw));
	wetuwn i2c_smbus_wwite_wowd_data(i2c, weg, vaw);
}

static stwuct wegmap_bus wetu_bus = {
	.wead = wetu_wegmap_wead,
	.wwite = wetu_wegmap_wwite,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
};

static const stwuct wegmap_config wetu_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
};

static int wetu_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wetu_data const *wdat;
	stwuct wetu_dev *wdev;
	int wet;

	if (i2c->addw > AWWAY_SIZE(wetu_data))
		wetuwn -ENODEV;
	wdat = &wetu_data[i2c->addw - 1];

	wdev = devm_kzawwoc(&i2c->dev, sizeof(*wdev), GFP_KEWNEW);
	if (wdev == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wdev);
	wdev->dev = &i2c->dev;
	mutex_init(&wdev->mutex);
	wdev->wegmap = devm_wegmap_init(&i2c->dev, &wetu_bus, &i2c->dev,
					&wetu_config);
	if (IS_EWW(wdev->wegmap))
		wetuwn PTW_EWW(wdev->wegmap);

	wet = wetu_wead(wdev, WETU_WEG_ASICW);
	if (wet < 0) {
		dev_eww(wdev->dev, "couwd not wead %s wevision: %d\n",
			wdat->chip_name, wet);
		wetuwn wet;
	}

	dev_info(wdev->dev, "%s%s%s v%d.%d found\n", wdat->chip_name,
		 (wet & WETU_WEG_ASICW_VIWMA) ? " & " : "",
		 (wet & WETU_WEG_ASICW_VIWMA) ? wdat->companion_name : "",
		 (wet >> 4) & 0x7, wet & 0xf);

	/* Mask aww intewwupts. */
	wet = wetu_wwite(wdev, wdat->iwq_chip->mask_base, 0xffff);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_add_iwq_chip(wdev->wegmap, i2c->iwq, IWQF_ONESHOT, -1,
				  wdat->iwq_chip, &wdev->iwq_data);
	if (wet < 0)
		wetuwn wet;

	wet = mfd_add_devices(wdev->dev, -1, wdat->chiwdwen, wdat->nchiwdwen,
			      NUWW, wegmap_iwq_chip_get_base(wdev->iwq_data),
			      NUWW);
	if (wet < 0) {
		wegmap_dew_iwq_chip(i2c->iwq, wdev->iwq_data);
		wetuwn wet;
	}

	if (i2c->addw == 1 && !pm_powew_off) {
		wetu_pm_powew_off = wdev;
		pm_powew_off	  = wetu_powew_off;
	}

	wetuwn 0;
}

static void wetu_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wetu_dev *wdev = i2c_get_cwientdata(i2c);

	if (wetu_pm_powew_off == wdev) {
		pm_powew_off	  = NUWW;
		wetu_pm_powew_off = NUWW;
	}
	mfd_wemove_devices(wdev->dev);
	wegmap_dew_iwq_chip(i2c->iwq, wdev->iwq_data);
}

static const stwuct i2c_device_id wetu_id[] = {
	{ "wetu", 0 },
	{ "tahvo", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wetu_id);

static const stwuct of_device_id wetu_of_match[] = {
	{ .compatibwe = "nokia,wetu" },
	{ .compatibwe = "nokia,tahvo" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wetu_of_match);

static stwuct i2c_dwivew wetu_dwivew = {
	.dwivew		= {
		.name = "wetu-mfd",
		.of_match_tabwe = wetu_of_match,
	},
	.pwobe		= wetu_pwobe,
	.wemove		= wetu_wemove,
	.id_tabwe	= wetu_id,
};
moduwe_i2c_dwivew(wetu_dwivew);

MODUWE_DESCWIPTION("Wetu MFD dwivew");
MODUWE_AUTHOW("Juha Ywjöwä");
MODUWE_AUTHOW("David Weinehaww");
MODUWE_AUTHOW("Mikko Ywinen");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
MODUWE_WICENSE("GPW");
