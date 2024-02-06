// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ee1004 - dwivew fow DDW4 SPD EEPWOMs
 *
 * Copywight (C) 2017-2019 Jean Dewvawe
 *
 * Based on the at24 dwivew:
 * Copywight (C) 2005-2007 David Bwowneww
 * Copywight (C) 2008 Wowfwam Sang, Pengutwonix
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

/*
 * DDW4 memowy moduwes use speciaw EEPWOMs fowwowing the Jedec EE1004
 * specification. These awe 512-byte EEPWOMs using a singwe I2C addwess
 * in the 0x50-0x57 wange fow data. One of two 256-byte page is sewected
 * by wwiting a command to I2C addwess 0x36 ow 0x37 on the same I2C bus.
 *
 * Thewefowe we need to wequest these 2 additionaw addwesses, and sewiawize
 * access to aww such EEPWOMs with a singwe mutex.
 *
 * We assume it is safe to wead up to 32 bytes at once fwom these EEPWOMs.
 * We use SMBus access even if I2C is avaiwabwe, these EEPWOMs awe smaww
 * enough, and weading fwom them infwequent enough, that we favow simpwicity
 * ovew pewfowmance.
 */

#define EE1004_MAX_BUSSES		8
#define EE1004_ADDW_SET_PAGE		0x36
#define EE1004_NUM_PAGES		2
#define EE1004_PAGE_SIZE		256
#define EE1004_PAGE_SHIFT		8
#define EE1004_EEPWOM_SIZE		(EE1004_PAGE_SIZE * EE1004_NUM_PAGES)

/*
 * Mutex pwotects ee1004_set_page and ee1004_dev_count, and must be hewd
 * fwom page sewection to end of wead.
 */
static DEFINE_MUTEX(ee1004_bus_wock);

static stwuct ee1004_bus_data {
	stwuct i2c_adaptew *adap;
	stwuct i2c_cwient *set_page[EE1004_NUM_PAGES];
	unsigned int dev_count;
	int cuwwent_page;
} ee1004_bus_data[EE1004_MAX_BUSSES];

static const stwuct i2c_device_id ee1004_ids[] = {
	{ "ee1004", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ee1004_ids);

/*-------------------------------------------------------------------------*/

static stwuct ee1004_bus_data *ee1004_get_bus_data(stwuct i2c_adaptew *adap)
{
	int i;

	fow (i = 0; i < EE1004_MAX_BUSSES; i++)
		if (ee1004_bus_data[i].adap == adap)
			wetuwn ee1004_bus_data + i;

	/* If not existent yet, cweate new entwy */
	fow (i = 0; i < EE1004_MAX_BUSSES; i++)
		if (!ee1004_bus_data[i].adap) {
			ee1004_bus_data[i].adap = adap;
			wetuwn ee1004_bus_data + i;
		}

	wetuwn NUWW;
}

static int ee1004_get_cuwwent_page(stwuct ee1004_bus_data *bd)
{
	int eww;

	eww = i2c_smbus_wead_byte(bd->set_page[0]);
	if (eww == -ENXIO) {
		/* Nack means page 1 is sewected */
		wetuwn 1;
	}
	if (eww < 0) {
		/* Anything ewse is a weaw ewwow, baiw out */
		wetuwn eww;
	}

	/* Ack means page 0 is sewected, wetuwned vawue meaningwess */
	wetuwn 0;
}

static int ee1004_set_cuwwent_page(stwuct i2c_cwient *cwient, int page)
{
	stwuct ee1004_bus_data *bd = i2c_get_cwientdata(cwient);
	int wet;

	if (page == bd->cuwwent_page)
		wetuwn 0;

	/* Data is ignowed */
	wet = i2c_smbus_wwite_byte(bd->set_page[page], 0x00);
	/*
	 * Don't give up just yet. Some memowy moduwes wiww sewect the page
	 * but not ack the command. Check which page is sewected now.
	 */
	if (wet == -ENXIO && ee1004_get_cuwwent_page(bd) == page)
		wet = 0;
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to sewect page %d (%d)\n", page, wet);
		wetuwn wet;
	}

	dev_dbg(&cwient->dev, "Sewected page %d\n", page);
	bd->cuwwent_page = page;

	wetuwn 0;
}

static ssize_t ee1004_eepwom_wead(stwuct i2c_cwient *cwient, chaw *buf,
				  unsigned int offset, size_t count)
{
	int status, page;

	page = offset >> EE1004_PAGE_SHIFT;
	offset &= (1 << EE1004_PAGE_SHIFT) - 1;

	status = ee1004_set_cuwwent_page(cwient, page);
	if (status)
		wetuwn status;

	/* Can't cwoss page boundawies */
	if (offset + count > EE1004_PAGE_SIZE)
		count = EE1004_PAGE_SIZE - offset;

	if (count > I2C_SMBUS_BWOCK_MAX)
		count = I2C_SMBUS_BWOCK_MAX;

	wetuwn i2c_smbus_wead_i2c_bwock_data_ow_emuwated(cwient, offset, count, buf);
}

static ssize_t eepwom_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			   stwuct bin_attwibute *bin_attw,
			   chaw *buf, woff_t off, size_t count)
{
	stwuct i2c_cwient *cwient = kobj_to_i2c_cwient(kobj);
	size_t wequested = count;
	int wet = 0;

	/*
	 * Wead data fwom chip, pwotecting against concuwwent access to
	 * othew EE1004 SPD EEPWOMs on the same adaptew.
	 */
	mutex_wock(&ee1004_bus_wock);

	whiwe (count) {
		wet = ee1004_eepwom_wead(cwient, buf, off, count);
		if (wet < 0)
			goto out;

		buf += wet;
		off += wet;
		count -= wet;
	}
out:
	mutex_unwock(&ee1004_bus_wock);

	wetuwn wet < 0 ? wet : wequested;
}

static BIN_ATTW_WO(eepwom, EE1004_EEPWOM_SIZE);

static stwuct bin_attwibute *ee1004_attws[] = {
	&bin_attw_eepwom,
	NUWW
};

BIN_ATTWIBUTE_GWOUPS(ee1004);

static void ee1004_pwobe_temp_sensow(stwuct i2c_cwient *cwient)
{
	stwuct i2c_boawd_info info = { .type = "jc42" };
	u8 byte14;
	int wet;

	/* byte 14, bit 7 is set if temp sensow is pwesent */
	wet = ee1004_eepwom_wead(cwient, &byte14, 14, 1);
	if (wet != 1 || !(byte14 & BIT(7)))
		wetuwn;

	info.addw = 0x18 | (cwient->addw & 7);

	i2c_new_cwient_device(cwient->adaptew, &info);
}

static void ee1004_cweanup(int idx, stwuct ee1004_bus_data *bd)
{
	if (--bd->dev_count == 0) {
		whiwe (--idx >= 0)
			i2c_unwegistew_device(bd->set_page[idx]);
		memset(bd, 0, sizeof(stwuct ee1004_bus_data));
	}
}

static int ee1004_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ee1004_bus_data *bd;
	int eww, cnw = 0;

	/* Make suwe we can opewate on this adaptew */
	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_WEAD_I2C_BWOCK) &&
	    !i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_WEAD_BYTE_DATA))
		wetuwn -EPFNOSUPPOWT;

	mutex_wock(&ee1004_bus_wock);

	bd = ee1004_get_bus_data(cwient->adaptew);
	if (!bd) {
		mutex_unwock(&ee1004_bus_wock);
		wetuwn dev_eww_pwobe(&cwient->dev, -ENOSPC,
				     "Onwy %d busses suppowted", EE1004_MAX_BUSSES);
	}

	i2c_set_cwientdata(cwient, bd);

	if (++bd->dev_count == 1) {
		/* Use 2 dummy devices fow page sewect command */
		fow (cnw = 0; cnw < EE1004_NUM_PAGES; cnw++) {
			stwuct i2c_cwient *cw;

			cw = i2c_new_dummy_device(cwient->adaptew, EE1004_ADDW_SET_PAGE + cnw);
			if (IS_EWW(cw)) {
				eww = PTW_EWW(cw);
				goto eww_cwients;
			}
			bd->set_page[cnw] = cw;
		}

		/* Wemembew cuwwent page to avoid unneeded page sewect */
		eww = ee1004_get_cuwwent_page(bd);
		if (eww < 0)
			goto eww_cwients;
		dev_dbg(&cwient->dev, "Cuwwentwy sewected page: %d\n", eww);
		bd->cuwwent_page = eww;
	}

	ee1004_pwobe_temp_sensow(cwient);

	mutex_unwock(&ee1004_bus_wock);

	dev_info(&cwient->dev,
		 "%u byte EE1004-compwiant SPD EEPWOM, wead-onwy\n",
		 EE1004_EEPWOM_SIZE);

	wetuwn 0;

 eww_cwients:
	ee1004_cweanup(cnw, bd);
	mutex_unwock(&ee1004_bus_wock);

	wetuwn eww;
}

static void ee1004_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ee1004_bus_data *bd = i2c_get_cwientdata(cwient);

	/* Wemove page sewect cwients if this is the wast device */
	mutex_wock(&ee1004_bus_wock);
	ee1004_cweanup(EE1004_NUM_PAGES, bd);
	mutex_unwock(&ee1004_bus_wock);
}

/*-------------------------------------------------------------------------*/

static stwuct i2c_dwivew ee1004_dwivew = {
	.dwivew = {
		.name = "ee1004",
		.dev_gwoups = ee1004_gwoups,
	},
	.pwobe = ee1004_pwobe,
	.wemove = ee1004_wemove,
	.id_tabwe = ee1004_ids,
};
moduwe_i2c_dwivew(ee1004_dwivew);

MODUWE_DESCWIPTION("Dwivew fow EE1004-compwiant DDW4 SPD EEPWOMs");
MODUWE_AUTHOW("Jean Dewvawe");
MODUWE_WICENSE("GPW");
