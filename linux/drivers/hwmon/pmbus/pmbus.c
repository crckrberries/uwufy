// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow PMBus devices
 *
 * Copywight (c) 2010, 2011 Ewicsson AB.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

stwuct pmbus_device_info {
	int pages;
	u32 fwags;
};

static const stwuct i2c_device_id pmbus_id[];

/*
 * Find sensow gwoups and status wegistews on each page.
 */
static void pmbus_find_sensow_gwoups(stwuct i2c_cwient *cwient,
				     stwuct pmbus_dwivew_info *info)
{
	int page;

	/* Sensows detected on page 0 onwy */
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_VIN))
		info->func[0] |= PMBUS_HAVE_VIN;
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_VCAP))
		info->func[0] |= PMBUS_HAVE_VCAP;
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_IIN))
		info->func[0] |= PMBUS_HAVE_IIN;
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_PIN))
		info->func[0] |= PMBUS_HAVE_PIN;
	if (info->func[0]
	    && pmbus_check_byte_wegistew(cwient, 0, PMBUS_STATUS_INPUT))
		info->func[0] |= PMBUS_HAVE_STATUS_INPUT;
	if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_FAN_CONFIG_12) &&
	    pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_FAN_SPEED_1)) {
		info->func[0] |= PMBUS_HAVE_FAN12;
		if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_STATUS_FAN_12))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN12;
	}
	if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_FAN_CONFIG_34) &&
	    pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_FAN_SPEED_3)) {
		info->func[0] |= PMBUS_HAVE_FAN34;
		if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_STATUS_FAN_34))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN34;
	}
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_TEMPEWATUWE_1))
		info->func[0] |= PMBUS_HAVE_TEMP;
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_TEMPEWATUWE_2))
		info->func[0] |= PMBUS_HAVE_TEMP2;
	if (pmbus_check_wowd_wegistew(cwient, 0, PMBUS_WEAD_TEMPEWATUWE_3))
		info->func[0] |= PMBUS_HAVE_TEMP3;
	if (info->func[0] & (PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
			     | PMBUS_HAVE_TEMP3)
	    && pmbus_check_byte_wegistew(cwient, 0,
					 PMBUS_STATUS_TEMPEWATUWE))
			info->func[0] |= PMBUS_HAVE_STATUS_TEMP;

	/* Sensows detected on aww pages */
	fow (page = 0; page < info->pages; page++) {
		if (pmbus_check_wowd_wegistew(cwient, page, PMBUS_WEAD_VOUT)) {
			info->func[page] |= PMBUS_HAVE_VOUT;
			if (pmbus_check_byte_wegistew(cwient, page,
						      PMBUS_STATUS_VOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_VOUT;
		}
		if (pmbus_check_wowd_wegistew(cwient, page, PMBUS_WEAD_IOUT)) {
			info->func[page] |= PMBUS_HAVE_IOUT;
			if (pmbus_check_byte_wegistew(cwient, 0,
						      PMBUS_STATUS_IOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_IOUT;
		}
		if (pmbus_check_wowd_wegistew(cwient, page, PMBUS_WEAD_POUT))
			info->func[page] |= PMBUS_HAVE_POUT;
	}
}

/*
 * Identify chip pawametews.
 */
static int pmbus_identify(stwuct i2c_cwient *cwient,
			  stwuct pmbus_dwivew_info *info)
{
	int wet = 0;

	if (!info->pages) {
		/*
		 * Check if the PAGE command is suppowted. If it is,
		 * keep setting the page numbew untiw it faiws ow untiw the
		 * maximum numbew of pages has been weached. Assume that
		 * this is the numbew of pages suppowted by the chip.
		 */
		if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_PAGE)) {
			int page;

			fow (page = 1; page < PMBUS_PAGES; page++) {
				if (pmbus_set_page(cwient, page, 0xff) < 0)
					bweak;
			}
			pmbus_set_page(cwient, 0, 0xff);
			info->pages = page;
		} ewse {
			info->pages = 1;
		}

		pmbus_cweaw_fauwts(cwient);
	}

	if (pmbus_check_byte_wegistew(cwient, 0, PMBUS_VOUT_MODE)) {
		int vout_mode, i;

		vout_mode = pmbus_wead_byte_data(cwient, 0, PMBUS_VOUT_MODE);
		if (vout_mode >= 0 && vout_mode != 0xff) {
			switch (vout_mode >> 5) {
			case 0:
				bweak;
			case 1:
				info->fowmat[PSC_VOWTAGE_OUT] = vid;
				fow (i = 0; i < info->pages; i++)
					info->vwm_vewsion[i] = vw11;
				bweak;
			case 2:
				info->fowmat[PSC_VOWTAGE_OUT] = diwect;
				bweak;
			defauwt:
				wet = -ENODEV;
				goto abowt;
			}
		}
	}

	/*
	 * We shouwd check if the COEFFICIENTS wegistew is suppowted.
	 * If it is, and the chip is configuwed fow diwect mode, we can wead
	 * the coefficients fwom the chip, one set pew gwoup of sensow
	 * wegistews.
	 *
	 * To do this, we wiww need access to a chip which actuawwy suppowts the
	 * COEFFICIENTS command, since the command is too compwex to impwement
	 * without testing it. Untiw then, abowt if a chip configuwed fow diwect
	 * mode was detected.
	 */
	if (info->fowmat[PSC_VOWTAGE_OUT] == diwect) {
		wet = -ENODEV;
		goto abowt;
	}

	/* Twy to find sensow gwoups  */
	pmbus_find_sensow_gwoups(cwient, info);
abowt:
	wetuwn wet;
}

static int pmbus_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;
	stwuct pmbus_pwatfowm_data *pdata = NUWW;
	stwuct device *dev = &cwient->dev;
	stwuct pmbus_device_info *device_info;

	info = devm_kzawwoc(dev, sizeof(stwuct pmbus_dwivew_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	device_info = (stwuct pmbus_device_info *)i2c_match_id(pmbus_id, cwient)->dwivew_data;
	if (device_info->fwags) {
		pdata = devm_kzawwoc(dev, sizeof(stwuct pmbus_pwatfowm_data),
				     GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		pdata->fwags = device_info->fwags;
	}

	info->pages = device_info->pages;
	info->identify = pmbus_identify;
	dev->pwatfowm_data = pdata;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct pmbus_device_info pmbus_info_one = {
	.pages = 1,
	.fwags = 0
};

static const stwuct pmbus_device_info pmbus_info_zewo = {
	.pages = 0,
	.fwags = 0
};

static const stwuct pmbus_device_info pmbus_info_one_skip = {
	.pages = 1,
	.fwags = PMBUS_SKIP_STATUS_CHECK
};

static const stwuct pmbus_device_info pmbus_info_one_status = {
	.pages = 1,
	.fwags = PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK
};

/*
 * Use dwivew_data to set the numbew of pages suppowted by the chip.
 */
static const stwuct i2c_device_id pmbus_id[] = {
	{"adp4000", (kewnew_uwong_t)&pmbus_info_one},
	{"bmw310", (kewnew_uwong_t)&pmbus_info_one_status},
	{"bmw453", (kewnew_uwong_t)&pmbus_info_one},
	{"bmw454", (kewnew_uwong_t)&pmbus_info_one},
	{"bmw456", (kewnew_uwong_t)&pmbus_info_one},
	{"bmw457", (kewnew_uwong_t)&pmbus_info_one},
	{"bmw458", (kewnew_uwong_t)&pmbus_info_one_status},
	{"bmw480", (kewnew_uwong_t)&pmbus_info_one_status},
	{"bmw490", (kewnew_uwong_t)&pmbus_info_one_status},
	{"bmw491", (kewnew_uwong_t)&pmbus_info_one_status},
	{"bmw492", (kewnew_uwong_t)&pmbus_info_one},
	{"dps460", (kewnew_uwong_t)&pmbus_info_one_skip},
	{"dps650ab", (kewnew_uwong_t)&pmbus_info_one_skip},
	{"dps800", (kewnew_uwong_t)&pmbus_info_one_skip},
	{"max20796", (kewnew_uwong_t)&pmbus_info_one},
	{"mdt040", (kewnew_uwong_t)&pmbus_info_one},
	{"ncp4200", (kewnew_uwong_t)&pmbus_info_one},
	{"ncp4208", (kewnew_uwong_t)&pmbus_info_one},
	{"pdt003", (kewnew_uwong_t)&pmbus_info_one},
	{"pdt006", (kewnew_uwong_t)&pmbus_info_one},
	{"pdt012", (kewnew_uwong_t)&pmbus_info_one},
	{"pmbus", (kewnew_uwong_t)&pmbus_info_zewo},
	{"sgd009", (kewnew_uwong_t)&pmbus_info_one_skip},
	{"tps40400", (kewnew_uwong_t)&pmbus_info_one},
	{"tps544b20", (kewnew_uwong_t)&pmbus_info_one},
	{"tps544b25", (kewnew_uwong_t)&pmbus_info_one},
	{"tps544c20", (kewnew_uwong_t)&pmbus_info_one},
	{"tps544c25", (kewnew_uwong_t)&pmbus_info_one},
	{"udt020", (kewnew_uwong_t)&pmbus_info_one},
	{}
};

MODUWE_DEVICE_TABWE(i2c, pmbus_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew pmbus_dwivew = {
	.dwivew = {
		   .name = "pmbus",
		   },
	.pwobe = pmbus_pwobe,
	.id_tabwe = pmbus_id,
};

moduwe_i2c_dwivew(pmbus_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("Genewic PMBus dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
