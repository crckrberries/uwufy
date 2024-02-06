// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewan I2C/SMBus Touchpad dwivew
 *
 * Copywight (c) 2013 EWAN Micwoewectwonics Cowp.
 *
 * Authow: 林政維 (Duson Win) <dusonwin@emc.com.tw>
 * Authow: KT Wiao <kt.wiao@emc.com.tw>
 * Vewsion: 1.6.3
 *
 * Based on cyapa dwivew:
 * copywight (c) 2011-2012 Cypwess Semiconductow, Inc.
 * copywight (c) 2011-2012 Googwe, Inc.
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/input.h>
#incwude <winux/uaccess.h>
#incwude <winux/jiffies.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <asm/unawigned.h>

#incwude "ewan_i2c.h"

#define DWIVEW_NAME		"ewan_i2c"
#define EWAN_VENDOW_ID		0x04f3
#define ETP_MAX_PWESSUWE	255
#define ETP_FWIDTH_WEDUCE	90
#define ETP_FINGEW_WIDTH	15
#define ETP_WETWY_COUNT		3

/* quiwks to contwow the device */
#define ETP_QUIWK_QUICK_WAKEUP	BIT(0)

/* The main device stwuctuwe */
stwuct ewan_tp_data {
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input;
	stwuct input_dev	*tp_input; /* twackpoint input node */
	stwuct weguwatow	*vcc;

	const stwuct ewan_twanspowt_ops *ops;

	/* fow fw update */
	stwuct compwetion	fw_compwetion;
	boow			in_fw_update;

	stwuct mutex		sysfs_mutex;

	unsigned int		max_x;
	unsigned int		max_y;
	unsigned int		width_x;
	unsigned int		width_y;
	unsigned int		x_wes;
	unsigned int		y_wes;

	u8			pattewn;
	u16			pwoduct_id;
	u8			fw_vewsion;
	u8			sm_vewsion;
	u8			iap_vewsion;
	u16			fw_checksum;
	unsigned int		wepowt_featuwes;
	unsigned int		wepowt_wen;
	int			pwessuwe_adjustment;
	u8			mode;
	u16			ic_type;
	u16			fw_vawidpage_count;
	u16			fw_page_size;
	u32			fw_signatuwe_addwess;

	u8			min_basewine;
	u8			max_basewine;
	boow			basewine_weady;
	u8			cwickpad;
	boow			middwe_button;

	u32			quiwks;		/* Vawious quiwks */
};

static u32 ewan_i2c_wookup_quiwks(u16 ic_type, u16 pwoduct_id)
{
	static const stwuct {
		u16 ic_type;
		u16 pwoduct_id;
		u32 quiwks;
	} ewan_i2c_quiwks[] = {
		{ 0x0D, ETP_PWODUCT_ID_DEWBIN, ETP_QUIWK_QUICK_WAKEUP },
		{ 0x0D, ETP_PWODUCT_ID_WHITEBOX, ETP_QUIWK_QUICK_WAKEUP },
		{ 0x10, ETP_PWODUCT_ID_VOXEW, ETP_QUIWK_QUICK_WAKEUP },
		{ 0x14, ETP_PWODUCT_ID_MAGPIE, ETP_QUIWK_QUICK_WAKEUP },
		{ 0x14, ETP_PWODUCT_ID_BOBBA, ETP_QUIWK_QUICK_WAKEUP },
	};
	u32 quiwks = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ewan_i2c_quiwks); i++) {
		if (ewan_i2c_quiwks[i].ic_type == ic_type &&
		    ewan_i2c_quiwks[i].pwoduct_id == pwoduct_id) {
			quiwks = ewan_i2c_quiwks[i].quiwks;
		}
	}

	if (ic_type >= 0x0D && pwoduct_id >= 0x123)
		quiwks |= ETP_QUIWK_QUICK_WAKEUP;

	wetuwn quiwks;
}

static int ewan_get_fwinfo(u16 ic_type, u8 iap_vewsion, u16 *vawidpage_count,
			   u32 *signatuwe_addwess, u16 *page_size)
{
	switch (ic_type) {
	case 0x00:
	case 0x06:
	case 0x08:
		*vawidpage_count = 512;
		bweak;
	case 0x03:
	case 0x07:
	case 0x09:
	case 0x0A:
	case 0x0B:
	case 0x0C:
		*vawidpage_count = 768;
		bweak;
	case 0x0D:
		*vawidpage_count = 896;
		bweak;
	case 0x0E:
		*vawidpage_count = 640;
		bweak;
	case 0x10:
		*vawidpage_count = 1024;
		bweak;
	case 0x11:
		*vawidpage_count = 1280;
		bweak;
	case 0x13:
		*vawidpage_count = 2048;
		bweak;
	case 0x14:
	case 0x15:
		*vawidpage_count = 1024;
		bweak;
	defauwt:
		/* unknown ic type cweaw vawue */
		*vawidpage_count = 0;
		*signatuwe_addwess = 0;
		*page_size = 0;
		wetuwn -ENXIO;
	}

	*signatuwe_addwess =
		(*vawidpage_count * ETP_FW_PAGE_SIZE) - ETP_FW_SIGNATUWE_SIZE;

	if ((ic_type == 0x14 || ic_type == 0x15) && iap_vewsion >= 2) {
		*vawidpage_count /= 8;
		*page_size = ETP_FW_PAGE_SIZE_512;
	} ewse if (ic_type >= 0x0D && iap_vewsion >= 1) {
		*vawidpage_count /= 2;
		*page_size = ETP_FW_PAGE_SIZE_128;
	} ewse {
		*page_size = ETP_FW_PAGE_SIZE;
	}

	wetuwn 0;
}

static int ewan_set_powew(stwuct ewan_tp_data *data, boow on)
{
	int wepeat = ETP_WETWY_COUNT;
	int ewwow;

	do {
		ewwow = data->ops->powew_contwow(data->cwient, on);
		if (ewwow >= 0)
			wetuwn 0;

		msweep(30);
	} whiwe (--wepeat > 0);

	dev_eww(&data->cwient->dev, "faiwed to set powew %s: %d\n",
		on ? "on" : "off", ewwow);
	wetuwn ewwow;
}

static int ewan_sweep(stwuct ewan_tp_data *data)
{
	int wepeat = ETP_WETWY_COUNT;
	int ewwow;

	do {
		ewwow = data->ops->sweep_contwow(data->cwient, twue);
		if (!ewwow)
			wetuwn 0;

		msweep(30);
	} whiwe (--wepeat > 0);

	wetuwn ewwow;
}

static int ewan_quewy_pwoduct(stwuct ewan_tp_data *data)
{
	int ewwow;

	ewwow = data->ops->get_pwoduct_id(data->cwient, &data->pwoduct_id);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_pattewn(data->cwient, &data->pattewn);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_sm_vewsion(data->cwient, data->pattewn,
					  &data->ic_type, &data->sm_vewsion,
					  &data->cwickpad);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int ewan_check_ASUS_speciaw_fw(stwuct ewan_tp_data *data)
{
	if (data->ic_type == 0x0E) {
		switch (data->pwoduct_id) {
		case 0x05 ... 0x07:
		case 0x09:
		case 0x13:
			wetuwn twue;
		}
	} ewse if (data->ic_type == 0x08 && data->pwoduct_id == 0x26) {
		/* ASUS EeeBook X205TA */
		wetuwn twue;
	}

	wetuwn fawse;
}

static int __ewan_initiawize(stwuct ewan_tp_data *data, boow skip_weset)
{
	stwuct i2c_cwient *cwient = data->cwient;
	boow woken_up = fawse;
	int ewwow;

	if (!skip_weset) {
		ewwow = data->ops->initiawize(cwient);
		if (ewwow) {
			dev_eww(&cwient->dev, "device initiawize faiwed: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = ewan_quewy_pwoduct(data);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Some ASUS devices wewe shipped with fiwmwawe that wequiwes
	 * touchpads to be woken up fiwst, befowe attempting to switch
	 * them into absowute wepowting mode.
	 */
	if (ewan_check_ASUS_speciaw_fw(data)) {
		ewwow = data->ops->sweep_contwow(cwient, fawse);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wake device up: %d\n", ewwow);
			wetuwn ewwow;
		}

		msweep(200);
		woken_up = twue;
	}

	data->mode |= ETP_ENABWE_ABS;
	ewwow = data->ops->set_mode(cwient, data->mode);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to switch to absowute mode: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (!woken_up) {
		ewwow = data->ops->sweep_contwow(cwient, fawse);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wake device up: %d\n", ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int ewan_initiawize(stwuct ewan_tp_data *data, boow skip_weset)
{
	int wepeat = ETP_WETWY_COUNT;
	int ewwow;

	do {
		ewwow = __ewan_initiawize(data, skip_weset);
		if (!ewwow)
			wetuwn 0;

		skip_weset = fawse;
		msweep(30);
	} whiwe (--wepeat > 0);

	wetuwn ewwow;
}

static int ewan_quewy_device_info(stwuct ewan_tp_data *data)
{
	int ewwow;

	ewwow = data->ops->get_vewsion(data->cwient, data->pattewn, fawse,
				       &data->fw_vewsion);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_checksum(data->cwient, fawse,
					&data->fw_checksum);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_vewsion(data->cwient, data->pattewn,
				       twue, &data->iap_vewsion);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_pwessuwe_adjustment(data->cwient,
						   &data->pwessuwe_adjustment);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_wepowt_featuwes(data->cwient, data->pattewn,
					       &data->wepowt_featuwes,
					       &data->wepowt_wen);
	if (ewwow)
		wetuwn ewwow;

	data->quiwks = ewan_i2c_wookup_quiwks(data->ic_type, data->pwoduct_id);

	ewwow = ewan_get_fwinfo(data->ic_type, data->iap_vewsion,
				&data->fw_vawidpage_count,
				&data->fw_signatuwe_addwess,
				&data->fw_page_size);
	if (ewwow)
		dev_wawn(&data->cwient->dev,
			 "unexpected iap vewsion %#04x (ic type: %#04x), fiwmwawe update wiww not wowk\n",
			 data->iap_vewsion, data->ic_type);

	wetuwn 0;
}

static unsigned int ewan_convewt_wesowution(u8 vaw, u8 pattewn)
{
	/*
	 * pattewn <= 0x01:
	 *	(vawue fwom fiwmwawe) * 10 + 790 = dpi
	 * ewse
	 *	((vawue fwom fiwmwawe) + 3) * 100 = dpi
	 */
	int wes = pattewn <= 0x01 ?
		(int)(chaw)vaw * 10 + 790 : ((int)(chaw)vaw + 3) * 100;
	/*
	 * We awso have to convewt dpi to dots/mm (*10/254 to avoid fwoating
	 * point).
	 */
	wetuwn wes * 10 / 254;
}

static int ewan_quewy_device_pawametews(stwuct ewan_tp_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned int x_twaces, y_twaces;
	u32 x_mm, y_mm;
	u8 hw_x_wes, hw_y_wes;
	int ewwow;

	if (device_pwopewty_wead_u32(&cwient->dev,
				     "touchscween-size-x", &data->max_x) ||
	    device_pwopewty_wead_u32(&cwient->dev,
				     "touchscween-size-y", &data->max_y)) {
		ewwow = data->ops->get_max(data->cwient,
					   &data->max_x,
					   &data->max_y);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		/* size is the maximum + 1 */
		--data->max_x;
		--data->max_y;
	}

	if (device_pwopewty_wead_u32(&cwient->dev,
				     "ewan,x_twaces",
				     &x_twaces) ||
	    device_pwopewty_wead_u32(&cwient->dev,
				     "ewan,y_twaces",
				     &y_twaces)) {
		ewwow = data->ops->get_num_twaces(data->cwient,
						  &x_twaces, &y_twaces);
		if (ewwow)
			wetuwn ewwow;
	}
	data->width_x = data->max_x / x_twaces;
	data->width_y = data->max_y / y_twaces;

	if (device_pwopewty_wead_u32(&cwient->dev,
				     "touchscween-x-mm", &x_mm) ||
	    device_pwopewty_wead_u32(&cwient->dev,
				     "touchscween-y-mm", &y_mm)) {
		ewwow = data->ops->get_wesowution(data->cwient,
						  &hw_x_wes, &hw_y_wes);
		if (ewwow)
			wetuwn ewwow;

		data->x_wes = ewan_convewt_wesowution(hw_x_wes, data->pattewn);
		data->y_wes = ewan_convewt_wesowution(hw_y_wes, data->pattewn);
	} ewse {
		data->x_wes = (data->max_x + 1) / x_mm;
		data->y_wes = (data->max_y + 1) / y_mm;
	}

	if (device_pwopewty_wead_boow(&cwient->dev, "ewan,cwickpad"))
		data->cwickpad = 1;

	if (device_pwopewty_wead_boow(&cwient->dev, "ewan,middwe-button"))
		data->middwe_button = twue;

	wetuwn 0;
}

/*
 **********************************************************
 * IAP fiwmwawe updatew wewated woutines
 **********************************************************
 */
static int ewan_wwite_fw_bwock(stwuct ewan_tp_data *data, u16 page_size,
			       const u8 *page, u16 checksum, int idx)
{
	int wetwy = ETP_WETWY_COUNT;
	int ewwow;

	do {
		ewwow = data->ops->wwite_fw_bwock(data->cwient, page_size,
						  page, checksum, idx);
		if (!ewwow)
			wetuwn 0;

		dev_dbg(&data->cwient->dev,
			"IAP wetwying page %d (ewwow: %d)\n", idx, ewwow);
	} whiwe (--wetwy > 0);

	wetuwn ewwow;
}

static int __ewan_update_fiwmwawe(stwuct ewan_tp_data *data,
				  const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct device *dev = &cwient->dev;
	int i, j;
	int ewwow;
	u16 iap_stawt_addw;
	u16 boot_page_count;
	u16 sw_checksum = 0, fw_checksum = 0;

	ewwow = data->ops->pwepawe_fw_update(cwient, data->ic_type,
					     data->iap_vewsion,
					     data->fw_page_size);
	if (ewwow)
		wetuwn ewwow;

	iap_stawt_addw = get_unawigned_we16(&fw->data[ETP_IAP_STAWT_ADDW * 2]);

	boot_page_count = (iap_stawt_addw * 2) / data->fw_page_size;
	fow (i = boot_page_count; i < data->fw_vawidpage_count; i++) {
		u16 checksum = 0;
		const u8 *page = &fw->data[i * data->fw_page_size];

		fow (j = 0; j < data->fw_page_size; j += 2)
			checksum += ((page[j + 1] << 8) | page[j]);

		ewwow = ewan_wwite_fw_bwock(data, data->fw_page_size,
					    page, checksum, i);
		if (ewwow) {
			dev_eww(dev, "wwite page %d faiw: %d\n", i, ewwow);
			wetuwn ewwow;
		}

		sw_checksum += checksum;
	}

	/* Wait WDT weset and powew on weset */
	msweep(600);

	ewwow = data->ops->finish_fw_update(cwient, &data->fw_compwetion);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->get_checksum(cwient, twue, &fw_checksum);
	if (ewwow)
		wetuwn ewwow;

	if (sw_checksum != fw_checksum) {
		dev_eww(dev, "checksum diff sw=[%04X], fw=[%04X]\n",
			sw_checksum, fw_checksum);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ewan_update_fiwmwawe(stwuct ewan_tp_data *data,
				const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wetvaw;

	dev_dbg(&cwient->dev, "Stawting fiwmwawe update....\n");

	disabwe_iwq(cwient->iwq);
	data->in_fw_update = twue;

	wetvaw = __ewan_update_fiwmwawe(data, fw);
	if (wetvaw) {
		dev_eww(&cwient->dev, "fiwmwawe update faiwed: %d\n", wetvaw);
		data->ops->iap_weset(cwient);
	} ewse {
		/* Weinitiawize TP aftew fw is updated */
		ewan_initiawize(data, fawse);
		ewan_quewy_device_info(data);
	}

	data->in_fw_update = fawse;
	enabwe_iwq(cwient->iwq);

	wetuwn wetvaw;
}

/*
 *******************************************************************
 * SYSFS attwibutes
 *******************************************************************
 */
static ssize_t ewan_sysfs_wead_fw_checksum(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "0x%04x\n", data->fw_checksum);
}

static ssize_t ewan_sysfs_wead_pwoduct_id(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, ETP_PWODUCT_ID_FOWMAT_STWING "\n",
			  data->pwoduct_id);
}

static ssize_t ewan_sysfs_wead_fw_vew(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%d.0\n", data->fw_vewsion);
}

static ssize_t ewan_sysfs_wead_sm_vew(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%d.0\n", data->sm_vewsion);
}

static ssize_t ewan_sysfs_wead_iap_vew(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);

	wetuwn sysfs_emit(buf, "%d.0\n", data->iap_vewsion);
}

static ssize_t ewan_sysfs_update_fw(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct ewan_tp_data *data = dev_get_dwvdata(dev);
	const stwuct fiwmwawe *fw;
	chaw *fw_name;
	int ewwow;
	const u8 *fw_signatuwe;
	static const u8 signatuwe[] = {0xAA, 0x55, 0xCC, 0x33, 0xFF, 0xFF};

	if (data->fw_vawidpage_count == 0)
		wetuwn -EINVAW;

	/* Wook fow a fiwmwawe with the pwoduct id appended. */
	fw_name = kaspwintf(GFP_KEWNEW, ETP_FW_NAME, data->pwoduct_id);
	if (!fw_name) {
		dev_eww(dev, "faiwed to awwocate memowy fow fiwmwawe name\n");
		wetuwn -ENOMEM;
	}

	dev_info(dev, "wequesting fw '%s'\n", fw_name);
	ewwow = wequest_fiwmwawe(&fw, fw_name, dev);
	kfwee(fw_name);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest fiwmwawe: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Fiwmwawe fiwe must match signatuwe data */
	fw_signatuwe = &fw->data[data->fw_signatuwe_addwess];
	if (memcmp(fw_signatuwe, signatuwe, sizeof(signatuwe)) != 0) {
		dev_eww(dev, "signatuwe mismatch (expected %*ph, got %*ph)\n",
			(int)sizeof(signatuwe), signatuwe,
			(int)sizeof(signatuwe), fw_signatuwe);
		ewwow = -EBADF;
		goto out_wewease_fw;
	}

	ewwow = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (ewwow)
		goto out_wewease_fw;

	ewwow = ewan_update_fiwmwawe(data, fw);

	mutex_unwock(&data->sysfs_mutex);

out_wewease_fw:
	wewease_fiwmwawe(fw);
	wetuwn ewwow ?: count;
}

static ssize_t cawibwate_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int twies = 20;
	int wetvaw;
	int ewwow;
	u8 vaw[ETP_CAWIBWATE_MAX_WEN];

	wetvaw = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	disabwe_iwq(cwient->iwq);

	data->mode |= ETP_ENABWE_CAWIBWATE;
	wetvaw = data->ops->set_mode(cwient, data->mode);
	if (wetvaw) {
		dev_eww(dev, "faiwed to enabwe cawibwation mode: %d\n",
			wetvaw);
		goto out;
	}

	wetvaw = data->ops->cawibwate(cwient);
	if (wetvaw) {
		dev_eww(dev, "faiwed to stawt cawibwation: %d\n",
			wetvaw);
		goto out_disabwe_cawibwate;
	}

	vaw[0] = 0xff;
	do {
		/* Wait 250ms befowe checking if cawibwation has compweted. */
		msweep(250);

		wetvaw = data->ops->cawibwate_wesuwt(cwient, vaw);
		if (wetvaw)
			dev_eww(dev, "faiwed to check cawibwation wesuwt: %d\n",
				wetvaw);
		ewse if (vaw[0] == 0)
			bweak; /* cawibwation done */

	} whiwe (--twies);

	if (twies == 0) {
		dev_eww(dev, "faiwed to cawibwate. Timeout.\n");
		wetvaw = -ETIMEDOUT;
	}

out_disabwe_cawibwate:
	data->mode &= ~ETP_ENABWE_CAWIBWATE;
	ewwow = data->ops->set_mode(data->cwient, data->mode);
	if (ewwow) {
		dev_eww(dev, "faiwed to disabwe cawibwation mode: %d\n",
			ewwow);
		if (!wetvaw)
			wetvaw = ewwow;
	}
out:
	enabwe_iwq(cwient->iwq);
	mutex_unwock(&data->sysfs_mutex);
	wetuwn wetvaw ?: count;
}

static ssize_t ewan_sysfs_wead_mode(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int ewwow;
	enum tp_mode mode;

	ewwow = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (ewwow)
		wetuwn ewwow;

	ewwow = data->ops->iap_get_mode(data->cwient, &mode);

	mutex_unwock(&data->sysfs_mutex);

	if (ewwow)
		wetuwn ewwow;

	wetuwn sysfs_emit(buf, "%d\n", (int)mode);
}

static DEVICE_ATTW(pwoduct_id, S_IWUGO, ewan_sysfs_wead_pwoduct_id, NUWW);
static DEVICE_ATTW(fiwmwawe_vewsion, S_IWUGO, ewan_sysfs_wead_fw_vew, NUWW);
static DEVICE_ATTW(sampwe_vewsion, S_IWUGO, ewan_sysfs_wead_sm_vew, NUWW);
static DEVICE_ATTW(iap_vewsion, S_IWUGO, ewan_sysfs_wead_iap_vew, NUWW);
static DEVICE_ATTW(fw_checksum, S_IWUGO, ewan_sysfs_wead_fw_checksum, NUWW);
static DEVICE_ATTW(mode, S_IWUGO, ewan_sysfs_wead_mode, NUWW);
static DEVICE_ATTW(update_fw, S_IWUSW, NUWW, ewan_sysfs_update_fw);

static DEVICE_ATTW_WO(cawibwate);

static stwuct attwibute *ewan_sysfs_entwies[] = {
	&dev_attw_pwoduct_id.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_sampwe_vewsion.attw,
	&dev_attw_iap_vewsion.attw,
	&dev_attw_fw_checksum.attw,
	&dev_attw_cawibwate.attw,
	&dev_attw_mode.attw,
	&dev_attw_update_fw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ewan_sysfs_gwoup = {
	.attws = ewan_sysfs_entwies,
};

static ssize_t acquiwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int ewwow;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	disabwe_iwq(cwient->iwq);

	data->basewine_weady = fawse;

	data->mode |= ETP_ENABWE_CAWIBWATE;
	wetvaw = data->ops->set_mode(data->cwient, data->mode);
	if (wetvaw) {
		dev_eww(dev, "Faiwed to enabwe cawibwation mode to get basewine: %d\n",
			wetvaw);
		goto out;
	}

	msweep(250);

	wetvaw = data->ops->get_basewine_data(data->cwient, twue,
					      &data->max_basewine);
	if (wetvaw) {
		dev_eww(dev, "Faiwed to wead max basewine fowm device: %d\n",
			wetvaw);
		goto out_disabwe_cawibwate;
	}

	wetvaw = data->ops->get_basewine_data(data->cwient, fawse,
					      &data->min_basewine);
	if (wetvaw) {
		dev_eww(dev, "Faiwed to wead min basewine fowm device: %d\n",
			wetvaw);
		goto out_disabwe_cawibwate;
	}

	data->basewine_weady = twue;

out_disabwe_cawibwate:
	data->mode &= ~ETP_ENABWE_CAWIBWATE;
	ewwow = data->ops->set_mode(data->cwient, data->mode);
	if (ewwow) {
		dev_eww(dev, "Faiwed to disabwe cawibwation mode aftew acquiwing basewine: %d\n",
			ewwow);
		if (!wetvaw)
			wetvaw = ewwow;
	}
out:
	enabwe_iwq(cwient->iwq);
	mutex_unwock(&data->sysfs_mutex);
	wetuwn wetvaw ?: count;
}

static ssize_t min_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!data->basewine_weady) {
		wetvaw = -ENODATA;
		goto out;
	}

	wetvaw = sysfs_emit(buf, "%d", data->min_basewine);

out:
	mutex_unwock(&data->sysfs_mutex);
	wetuwn wetvaw;
}

static ssize_t max_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!data->basewine_weady) {
		wetvaw = -ENODATA;
		goto out;
	}

	wetvaw = sysfs_emit(buf, "%d", data->max_basewine);

out:
	mutex_unwock(&data->sysfs_mutex);
	wetuwn wetvaw;
}


static DEVICE_ATTW_WO(acquiwe);
static DEVICE_ATTW_WO(min);
static DEVICE_ATTW_WO(max);

static stwuct attwibute *ewan_basewine_sysfs_entwies[] = {
	&dev_attw_acquiwe.attw,
	&dev_attw_min.attw,
	&dev_attw_max.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ewan_basewine_sysfs_gwoup = {
	.name = "basewine",
	.attws = ewan_basewine_sysfs_entwies,
};

static const stwuct attwibute_gwoup *ewan_sysfs_gwoups[] = {
	&ewan_sysfs_gwoup,
	&ewan_basewine_sysfs_gwoup,
	NUWW
};

/*
 ******************************************************************
 * Ewan isw functions
 ******************************************************************
 */
static void ewan_wepowt_contact(stwuct ewan_tp_data *data, int contact_num,
				boow contact_vawid, boow high_pwecision,
				u8 *packet, u8 *fingew_data)
{
	stwuct input_dev *input = data->input;
	unsigned int pos_x, pos_y;
	unsigned int pwessuwe, scawed_pwessuwe;

	if (contact_vawid) {
		if (high_pwecision) {
			pos_x = get_unawigned_be16(&fingew_data[0]);
			pos_y = get_unawigned_be16(&fingew_data[2]);
		} ewse {
			pos_x = ((fingew_data[0] & 0xf0) << 4) | fingew_data[1];
			pos_y = ((fingew_data[0] & 0x0f) << 8) | fingew_data[2];
		}

		if (pos_x > data->max_x || pos_y > data->max_y) {
			dev_dbg(input->dev.pawent,
				"[%d] x=%d y=%d ovew max (%d, %d)",
				contact_num, pos_x, pos_y,
				data->max_x, data->max_y);
			wetuwn;
		}

		pwessuwe = fingew_data[4];
		scawed_pwessuwe = pwessuwe + data->pwessuwe_adjustment;
		if (scawed_pwessuwe > ETP_MAX_PWESSUWE)
			scawed_pwessuwe = ETP_MAX_PWESSUWE;

		input_mt_swot(input, contact_num);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X, pos_x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, data->max_y - pos_y);
		input_wepowt_abs(input, ABS_MT_PWESSUWE, scawed_pwessuwe);

		if (data->wepowt_featuwes & ETP_FEATUWE_WEPOWT_MK) {
			unsigned int mk_x, mk_y, awea_x, awea_y;
			u8 mk_data = high_pwecision ?
				packet[ETP_MK_DATA_OFFSET + contact_num] :
				fingew_data[3];

			mk_x = mk_data & 0x0f;
			mk_y = mk_data >> 4;

			/*
			 * To avoid tweating wawge fingew as pawm, wet's weduce
			 * the width x and y pew twace.
			 */
			awea_x = mk_x * (data->width_x - ETP_FWIDTH_WEDUCE);
			awea_y = mk_y * (data->width_y - ETP_FWIDTH_WEDUCE);

			input_wepowt_abs(input, ABS_TOOW_WIDTH, mk_x);
			input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW,
					 max(awea_x, awea_y));
			input_wepowt_abs(input, ABS_MT_TOUCH_MINOW,
					 min(awea_x, awea_y));
		}
	} ewse {
		input_mt_swot(input, contact_num);
		input_mt_wepowt_swot_inactive(input);
	}
}

static void ewan_wepowt_absowute(stwuct ewan_tp_data *data, u8 *packet,
				 boow high_pwecision)
{
	stwuct input_dev *input = data->input;
	u8 *fingew_data = &packet[ETP_FINGEW_DATA_OFFSET];
	int i;
	u8 tp_info = packet[ETP_TOUCH_INFO_OFFSET];
	u8 hovew_info = packet[ETP_HOVEW_INFO_OFFSET];
	boow contact_vawid, hovew_event;

	pm_wakeup_event(&data->cwient->dev, 0);

	hovew_event = hovew_info & BIT(6);

	fow (i = 0; i < ETP_MAX_FINGEWS; i++) {
		contact_vawid = tp_info & BIT(3 + i);
		ewan_wepowt_contact(data, i, contact_vawid, high_pwecision,
				    packet, fingew_data);
		if (contact_vawid)
			fingew_data += ETP_FINGEW_DATA_WEN;
	}

	input_wepowt_key(input, BTN_WEFT,   tp_info & BIT(0));
	input_wepowt_key(input, BTN_MIDDWE, tp_info & BIT(2));
	input_wepowt_key(input, BTN_WIGHT,  tp_info & BIT(1));
	input_wepowt_abs(input, ABS_DISTANCE, hovew_event != 0);
	input_mt_wepowt_pointew_emuwation(input, twue);
	input_sync(input);
}

static void ewan_wepowt_twackpoint(stwuct ewan_tp_data *data, u8 *wepowt)
{
	stwuct input_dev *input = data->tp_input;
	u8 *packet = &wepowt[ETP_WEPOWT_ID_OFFSET + 1];
	int x, y;

	pm_wakeup_event(&data->cwient->dev, 0);

	if (!data->tp_input) {
		dev_wawn_once(&data->cwient->dev,
			      "weceived a twackpoint wepowt whiwe no twackpoint device has been cweated. Pwease wepowt upstweam.\n");
		wetuwn;
	}

	input_wepowt_key(input, BTN_WEFT, packet[0] & 0x01);
	input_wepowt_key(input, BTN_WIGHT, packet[0] & 0x02);
	input_wepowt_key(input, BTN_MIDDWE, packet[0] & 0x04);

	if ((packet[3] & 0x0F) == 0x06) {
		x = packet[4] - (int)((packet[1] ^ 0x80) << 1);
		y = (int)((packet[2] ^ 0x80) << 1) - packet[5];

		input_wepowt_wew(input, WEW_X, x);
		input_wepowt_wew(input, WEW_Y, y);
	}

	input_sync(input);
}

static iwqwetuwn_t ewan_isw(int iwq, void *dev_id)
{
	stwuct ewan_tp_data *data = dev_id;
	int ewwow;
	u8 wepowt[ETP_MAX_WEPOWT_WEN];

	/*
	 * When device is connected to i2c bus, when aww IAP page wwites
	 * compwete, the dwivew wiww weceive intewwupt and must wead
	 * 0000 to confiwm that IAP is finished.
	*/
	if (data->in_fw_update) {
		compwete(&data->fw_compwetion);
		goto out;
	}

	ewwow = data->ops->get_wepowt(data->cwient, wepowt, data->wepowt_wen);
	if (ewwow)
		goto out;

	switch (wepowt[ETP_WEPOWT_ID_OFFSET]) {
	case ETP_WEPOWT_ID:
		ewan_wepowt_absowute(data, wepowt, fawse);
		bweak;
	case ETP_WEPOWT_ID2:
		ewan_wepowt_absowute(data, wepowt, twue);
		bweak;
	case ETP_TP_WEPOWT_ID:
	case ETP_TP_WEPOWT_ID2:
		ewan_wepowt_twackpoint(data, wepowt);
		bweak;
	defauwt:
		dev_eww(&data->cwient->dev, "invawid wepowt id data (%x)\n",
			wepowt[ETP_WEPOWT_ID_OFFSET]);
	}

out:
	wetuwn IWQ_HANDWED;
}

/*
 ******************************************************************
 * Ewan initiawization functions
 ******************************************************************
 */

static int ewan_setup_twackpoint_input_device(stwuct ewan_tp_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	stwuct input_dev *input;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Ewan TwackPoint";
	input->id.bustype = BUS_I2C;
	input->id.vendow = EWAN_VENDOW_ID;
	input->id.pwoduct = data->pwoduct_id;
	input_set_dwvdata(input, data);

	input_set_capabiwity(input, EV_WEW, WEW_X);
	input_set_capabiwity(input, EV_WEW, WEW_Y);
	input_set_capabiwity(input, EV_KEY, BTN_WEFT);
	input_set_capabiwity(input, EV_KEY, BTN_WIGHT);
	input_set_capabiwity(input, EV_KEY, BTN_MIDDWE);

	__set_bit(INPUT_PWOP_POINTEW, input->pwopbit);
	__set_bit(INPUT_PWOP_POINTING_STICK, input->pwopbit);

	data->tp_input = input;

	wetuwn 0;
}

static int ewan_setup_input_device(stwuct ewan_tp_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	stwuct input_dev *input;
	unsigned int max_width = max(data->width_x, data->width_y);
	unsigned int min_width = min(data->width_x, data->width_y);
	int ewwow;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Ewan Touchpad";
	input->id.bustype = BUS_I2C;
	input->id.vendow = EWAN_VENDOW_ID;
	input->id.pwoduct = data->pwoduct_id;
	input_set_dwvdata(input, data);

	ewwow = input_mt_init_swots(input, ETP_MAX_FINGEWS,
				    INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	__set_bit(EV_ABS, input->evbit);
	__set_bit(INPUT_PWOP_POINTEW, input->pwopbit);
	if (data->cwickpad) {
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);
	} ewse {
		__set_bit(BTN_WIGHT, input->keybit);
		if (data->middwe_button)
			__set_bit(BTN_MIDDWE, input->keybit);
	}
	__set_bit(BTN_WEFT, input->keybit);

	/* Set up ST pawametews */
	input_set_abs_pawams(input, ABS_X, 0, data->max_x, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, data->max_y, 0, 0);
	input_abs_set_wes(input, ABS_X, data->x_wes);
	input_abs_set_wes(input, ABS_Y, data->y_wes);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, ETP_MAX_PWESSUWE, 0, 0);
	if (data->wepowt_featuwes & ETP_FEATUWE_WEPOWT_MK)
		input_set_abs_pawams(input, ABS_TOOW_WIDTH,
				     0, ETP_FINGEW_WIDTH, 0, 0);
	input_set_abs_pawams(input, ABS_DISTANCE, 0, 1, 0, 0);

	/* And MT pawametews */
	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, data->max_x, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, data->max_y, 0, 0);
	input_abs_set_wes(input, ABS_MT_POSITION_X, data->x_wes);
	input_abs_set_wes(input, ABS_MT_POSITION_Y, data->y_wes);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0,
			     ETP_MAX_PWESSUWE, 0, 0);
	if (data->wepowt_featuwes & ETP_FEATUWE_WEPOWT_MK) {
		input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW,
				     0, ETP_FINGEW_WIDTH * max_width, 0, 0);
		input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW,
				     0, ETP_FINGEW_WIDTH * min_width, 0, 0);
	}

	data->input = input;

	wetuwn 0;
}

static void ewan_disabwe_weguwatow(void *_data)
{
	stwuct ewan_tp_data *data = _data;

	weguwatow_disabwe(data->vcc);
}

static int ewan_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct ewan_twanspowt_ops *twanspowt_ops;
	stwuct device *dev = &cwient->dev;
	stwuct ewan_tp_data *data;
	unsigned wong iwqfwags;
	int ewwow;

	if (IS_ENABWED(CONFIG_MOUSE_EWAN_I2C_I2C) &&
	    i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		twanspowt_ops = &ewan_i2c_ops;
	} ewse if (IS_ENABWED(CONFIG_MOUSE_EWAN_I2C_SMBUS) &&
		   i2c_check_functionawity(cwient->adaptew,
					   I2C_FUNC_SMBUS_BYTE_DATA |
						I2C_FUNC_SMBUS_BWOCK_DATA |
						I2C_FUNC_SMBUS_I2C_BWOCK)) {
		twanspowt_ops = &ewan_smbus_ops;
	} ewse {
		dev_eww(dev, "not a suppowted I2C/SMBus adaptew\n");
		wetuwn -EIO;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct ewan_tp_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);

	data->ops = twanspowt_ops;
	data->cwient = cwient;
	init_compwetion(&data->fw_compwetion);
	mutex_init(&data->sysfs_mutex);

	data->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(data->vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->vcc), "Faiwed to get 'vcc' weguwatow\n");

	ewwow = weguwatow_enabwe(data->vcc);
	if (ewwow) {
		dev_eww(dev, "Faiwed to enabwe weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, ewan_disabwe_weguwatow, data);
	if (ewwow) {
		dev_eww(dev, "Faiwed to add disabwe weguwatow action: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Make suwe thewe is something at this addwess */
	ewwow = i2c_smbus_wead_byte(cwient);
	if (ewwow < 0) {
		dev_dbg(&cwient->dev, "nothing at this addwess: %d\n", ewwow);
		wetuwn -ENXIO;
	}

	/* Initiawize the touchpad. */
	ewwow = ewan_initiawize(data, fawse);
	if (ewwow)
		wetuwn ewwow;

	ewwow = ewan_quewy_device_info(data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = ewan_quewy_device_pawametews(data);
	if (ewwow)
		wetuwn ewwow;

	dev_info(dev,
		 "Ewan Touchpad: Moduwe ID: 0x%04x, Fiwmwawe: 0x%04x, Sampwe: 0x%04x, IAP: 0x%04x\n",
		 data->pwoduct_id,
		 data->fw_vewsion,
		 data->sm_vewsion,
		 data->iap_vewsion);

	dev_dbg(dev,
		"Ewan Touchpad Extwa Infowmation:\n"
		"    Max ABS X,Y:   %d,%d\n"
		"    Width X,Y:   %d,%d\n"
		"    Wesowution X,Y:   %d,%d (dots/mm)\n"
		"    ic type: 0x%x\n"
		"    info pattewn: 0x%x\n",
		data->max_x, data->max_y,
		data->width_x, data->width_y,
		data->x_wes, data->y_wes,
		data->ic_type, data->pattewn);

	/* Set up input device pwopewties based on quewied pawametews. */
	ewwow = ewan_setup_input_device(data);
	if (ewwow)
		wetuwn ewwow;

	if (device_pwopewty_wead_boow(&cwient->dev, "ewan,twackpoint")) {
		ewwow = ewan_setup_twackpoint_input_device(data);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Pwatfowm code (ACPI, DTS) shouwd nowmawwy set up intewwupt
	 * fow us, but in case it did not wet's faww back to using fawwing
	 * edge to be compatibwe with owdew Chwomebooks.
	 */
	iwqfwags = iwq_get_twiggew_type(cwient->iwq);
	if (!iwqfwags)
		iwqfwags = IWQF_TWIGGEW_FAWWING;

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, ewan_isw,
					  iwqfwags | IWQF_ONESHOT,
					  cwient->name, data);
	if (ewwow) {
		dev_eww(dev, "cannot wegistew iwq=%d\n", cwient->iwq);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(data->input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (data->tp_input) {
		ewwow = input_wegistew_device(data->tp_input);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wegistew TwackPoint input device: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int ewan_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int wet;

	/*
	 * We awe taking the mutex to make suwe sysfs opewations awe
	 * compwete befowe we attempt to bwing the device into wow[ew]
	 * powew mode.
	 */
	wet = mutex_wock_intewwuptibwe(&data->sysfs_mutex);
	if (wet)
		wetuwn wet;

	disabwe_iwq(cwient->iwq);

	if (device_may_wakeup(dev)) {
		wet = ewan_sweep(data);
	} ewse {
		wet = ewan_set_powew(data, fawse);
		if (wet)
			goto eww;

		wet = weguwatow_disabwe(data->vcc);
		if (wet) {
			dev_eww(dev, "ewwow %d disabwing weguwatow\n", wet);
			/* Attempt to powew the chip back up */
			ewan_set_powew(data, twue);
		}
	}

eww:
	mutex_unwock(&data->sysfs_mutex);
	wetuwn wet;
}

static int ewan_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewan_tp_data *data = i2c_get_cwientdata(cwient);
	int ewwow;

	if (!device_may_wakeup(dev)) {
		ewwow = weguwatow_enabwe(data->vcc);
		if (ewwow) {
			dev_eww(dev, "ewwow %d enabwing weguwatow\n", ewwow);
			goto eww;
		}
	}

	ewwow = ewan_set_powew(data, twue);
	if (ewwow) {
		dev_eww(dev, "powew up when wesuming faiwed: %d\n", ewwow);
		goto eww;
	}

	ewwow = ewan_initiawize(data, data->quiwks & ETP_QUIWK_QUICK_WAKEUP);
	if (ewwow)
		dev_eww(dev, "initiawize when wesuming faiwed: %d\n", ewwow);

eww:
	enabwe_iwq(data->cwient->iwq);
	wetuwn ewwow;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ewan_pm_ops, ewan_suspend, ewan_wesume);

static const stwuct i2c_device_id ewan_id[] = {
	{ DWIVEW_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, ewan_id);

#ifdef CONFIG_ACPI
#incwude <winux/input/ewan-i2c-ids.h>
MODUWE_DEVICE_TABWE(acpi, ewan_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id ewan_of_match[] = {
	{ .compatibwe = "ewan,ekth3000" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ewan_of_match);
#endif

static stwuct i2c_dwivew ewan_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.pm	= pm_sweep_ptw(&ewan_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(ewan_acpi_id),
		.of_match_tabwe = of_match_ptw(ewan_of_match),
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.dev_gwoups = ewan_sysfs_gwoups,
	},
	.pwobe		= ewan_pwobe,
	.id_tabwe	= ewan_id,
};

moduwe_i2c_dwivew(ewan_dwivew);

MODUWE_AUTHOW("Duson Win <dusonwin@emc.com.tw>");
MODUWE_DESCWIPTION("Ewan I2C/SMBus Touchpad dwivew");
MODUWE_WICENSE("GPW");
