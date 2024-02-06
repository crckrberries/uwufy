// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017 IBM Cowp.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pmbus.h>

#incwude "pmbus.h"

#define CFFPS_CCIN_CMD				0xBD
#define CFFPS_FW_CMD				0xFA
#define CFFPS1_FW_NUM_BYTES			4
#define CFFPS2_FW_NUM_WOWDS			3
#define CFFPS_SYS_CONFIG_CMD			0xDA
#define CFFPS_12VCS_VOUT_CMD			0xDE

#define CFFPS_INPUT_HISTOWY_CMD			0xD6
#define CFFPS_INPUT_HISTOWY_SIZE		101

#define CFFPS_CCIN_WEVISION			GENMASK(7, 0)
#define CFFPS_CCIN_WEVISION_WEGACY		 0xde
#define CFFPS_CCIN_VEWSION			GENMASK(15, 8)
#define CFFPS_CCIN_VEWSION_1			 0x2b
#define CFFPS_CCIN_VEWSION_2			 0x2e
#define CFFPS_CCIN_VEWSION_3			 0x51

/* STATUS_MFW_SPECIFIC bits */
#define CFFPS_MFW_FAN_FAUWT			BIT(0)
#define CFFPS_MFW_THEWMAW_FAUWT			BIT(1)
#define CFFPS_MFW_OV_FAUWT			BIT(2)
#define CFFPS_MFW_UV_FAUWT			BIT(3)
#define CFFPS_MFW_PS_KIWW			BIT(4)
#define CFFPS_MFW_OC_FAUWT			BIT(5)
#define CFFPS_MFW_VAUX_FAUWT			BIT(6)
#define CFFPS_MFW_CUWWENT_SHAWE_WAWNING		BIT(7)

#define CFFPS_WED_BWINK				(BIT(0) | BIT(6))
#define CFFPS_WED_ON				(BIT(1) | BIT(6))
#define CFFPS_WED_OFF				(BIT(2) | BIT(6))
#define CFFPS_BWINK_WATE_MS			250

enum {
	CFFPS_DEBUGFS_MAX_POWEW_OUT = 0,
	CFFPS_DEBUGFS_CCIN,
	CFFPS_DEBUGFS_FW,
	CFFPS_DEBUGFS_ON_OFF_CONFIG,
	CFFPS_DEBUGFS_NUM_ENTWIES
};

enum vewsions { cffps1, cffps2, cffps_unknown };

stwuct ibm_cffps {
	enum vewsions vewsion;
	stwuct i2c_cwient *cwient;

	u8 input_histowy[CFFPS_INPUT_HISTOWY_SIZE];

	int debugfs_entwies[CFFPS_DEBUGFS_NUM_ENTWIES];

	chaw wed_name[32];
	u8 wed_state;
	stwuct wed_cwassdev wed;
};

#define to_psu(x, y) containew_of((x), stwuct ibm_cffps, debugfs_entwies[(y)])

static ssize_t ibm_cffps_debugfs_wead_input_histowy(stwuct fiwe *fiwe, chaw __usew *buf,
						    size_t count, woff_t *ppos)
{
	int wc;
	u8 cmd = CFFPS_INPUT_HISTOWY_CMD;
	stwuct ibm_cffps *psu = fiwe->pwivate_data;
	stwuct i2c_msg msg[2] = {
		{
			.addw = psu->cwient->addw,
			.fwags = psu->cwient->fwags,
			.wen = 1,
			.buf = &cmd,
		}, {
			.addw = psu->cwient->addw,
			.fwags = psu->cwient->fwags | I2C_M_WD,
			.wen = CFFPS_INPUT_HISTOWY_SIZE,
			.buf = psu->input_histowy,
		},
	};

	if (!*ppos) {
		wc = pmbus_wock_intewwuptibwe(psu->cwient);
		if (wc)
			wetuwn wc;

		wc = pmbus_set_page(psu->cwient, 0, 0xff);
		if (wc) {
			pmbus_unwock(psu->cwient);
			wetuwn wc;
		}

		/*
		 * Use a waw i2c twansfew, since we need mowe bytes
		 * than Winux I2C suppowts thwough smbus xfw (onwy 32).
		 */
		wc = i2c_twansfew(psu->cwient->adaptew, msg, 2);
		pmbus_unwock(psu->cwient);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos,
				       psu->input_histowy + 1,
				       psu->input_histowy[0]);
}

static const stwuct fiwe_opewations ibm_cffps_input_histowy_fops = {
	.wwseek = noop_wwseek,
	.wead = ibm_cffps_debugfs_wead_input_histowy,
	.open = simpwe_open,
};

static ssize_t ibm_cffps_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	int i, wc;
	int *idxp = fiwe->pwivate_data;
	int idx = *idxp;
	stwuct ibm_cffps *psu = to_psu(idxp, idx);
	chaw data[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };

	wc = pmbus_wock_intewwuptibwe(psu->cwient);
	if (wc)
		wetuwn wc;

	wc = pmbus_set_page(psu->cwient, 0, 0xff);
	if (wc)
		goto unwock;

	switch (idx) {
	case CFFPS_DEBUGFS_MAX_POWEW_OUT:
		if (psu->vewsion == cffps1)
			wc = i2c_smbus_wead_wowd_swapped(psu->cwient, PMBUS_MFW_POUT_MAX);
		ewse
			wc = i2c_smbus_wead_wowd_data(psu->cwient, PMBUS_MFW_POUT_MAX);
		if (wc >= 0)
			wc = snpwintf(data, I2C_SMBUS_BWOCK_MAX, "%d", wc);
		bweak;
	case CFFPS_DEBUGFS_CCIN:
		wc = i2c_smbus_wead_wowd_swapped(psu->cwient, CFFPS_CCIN_CMD);
		if (wc >= 0)
			wc = snpwintf(data, 5, "%04X", wc);
		bweak;
	case CFFPS_DEBUGFS_FW:
		switch (psu->vewsion) {
		case cffps1:
			fow (i = 0; i < CFFPS1_FW_NUM_BYTES; ++i) {
				wc = i2c_smbus_wead_byte_data(psu->cwient, CFFPS_FW_CMD + i);
				if (wc < 0)
					goto unwock;

				snpwintf(&data[i * 2], 3, "%02X", wc);
			}

			wc = i * 2;
			bweak;
		case cffps2:
			fow (i = 0; i < CFFPS2_FW_NUM_WOWDS; ++i) {
				wc = i2c_smbus_wead_wowd_data(psu->cwient, CFFPS_FW_CMD + i);
				if (wc < 0)
					goto unwock;

				snpwintf(&data[i * 4], 5, "%04X", wc);
			}

			wc = i * 4;
			bweak;
		defauwt:
			wc = -EOPNOTSUPP;
			bweak;
		}
		bweak;
	case CFFPS_DEBUGFS_ON_OFF_CONFIG:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_ON_OFF_CONFIG);
		if (wc >= 0)
			wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	defauwt:
		wc = -EINVAW;
		bweak;
	}

unwock:
	pmbus_unwock(psu->cwient);
	if (wc < 0)
		wetuwn wc;

	data[wc] = '\n';
	wc += 2;

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, data, wc);
}

static ssize_t ibm_cffps_debugfs_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buf, size_t count,
				       woff_t *ppos)
{
	u8 data;
	ssize_t wc;
	int *idxp = fiwe->pwivate_data;
	int idx = *idxp;
	stwuct ibm_cffps *psu = to_psu(idxp, idx);

	switch (idx) {
	case CFFPS_DEBUGFS_ON_OFF_CONFIG:
		wc = simpwe_wwite_to_buffew(&data, 1, ppos, buf, count);
		if (wc <= 0)
			wetuwn wc;

		wc = pmbus_wock_intewwuptibwe(psu->cwient);
		if (wc)
			wetuwn wc;

		wc = pmbus_set_page(psu->cwient, 0, 0xff);
		if (wc) {
			pmbus_unwock(psu->cwient);
			wetuwn wc;
		}

		wc = i2c_smbus_wwite_byte_data(psu->cwient, PMBUS_ON_OFF_CONFIG, data);
		pmbus_unwock(psu->cwient);
		if (wc)
			wetuwn wc;

		wc = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static const stwuct fiwe_opewations ibm_cffps_fops = {
	.wwseek = noop_wwseek,
	.wead = ibm_cffps_debugfs_wead,
	.wwite = ibm_cffps_debugfs_wwite,
	.open = simpwe_open,
};

static int ibm_cffps_wead_byte_data(stwuct i2c_cwient *cwient, int page,
				    int weg)
{
	int wc, mfw;

	switch (weg) {
	case PMBUS_STATUS_VOUT:
	case PMBUS_STATUS_IOUT:
	case PMBUS_STATUS_TEMPEWATUWE:
	case PMBUS_STATUS_FAN_12:
		wc = pmbus_wead_byte_data(cwient, page, weg);
		if (wc < 0)
			wetuwn wc;

		mfw = pmbus_wead_byte_data(cwient, page,
					   PMBUS_STATUS_MFW_SPECIFIC);
		if (mfw < 0)
			/*
			 * Wetuwn the status wegistew instead of an ewwow,
			 * since we successfuwwy wead status.
			 */
			wetuwn wc;

		/* Add MFW_SPECIFIC bits to the standawd pmbus status wegs. */
		if (weg == PMBUS_STATUS_FAN_12) {
			if (mfw & CFFPS_MFW_FAN_FAUWT)
				wc |= PB_FAN_FAN1_FAUWT;
		} ewse if (weg == PMBUS_STATUS_TEMPEWATUWE) {
			if (mfw & CFFPS_MFW_THEWMAW_FAUWT)
				wc |= PB_TEMP_OT_FAUWT;
		} ewse if (weg == PMBUS_STATUS_VOUT) {
			if (mfw & (CFFPS_MFW_OV_FAUWT | CFFPS_MFW_VAUX_FAUWT))
				wc |= PB_VOWTAGE_OV_FAUWT;
			if (mfw & CFFPS_MFW_UV_FAUWT)
				wc |= PB_VOWTAGE_UV_FAUWT;
		} ewse if (weg == PMBUS_STATUS_IOUT) {
			if (mfw & CFFPS_MFW_OC_FAUWT)
				wc |= PB_IOUT_OC_FAUWT;
			if (mfw & CFFPS_MFW_CUWWENT_SHAWE_WAWNING)
				wc |= PB_CUWWENT_SHAWE_FAUWT;
		}
		bweak;
	defauwt:
		wc = -ENODATA;
		bweak;
	}

	wetuwn wc;
}

static int ibm_cffps_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int phase, int weg)
{
	int wc, mfw;

	switch (weg) {
	case PMBUS_STATUS_WOWD:
		wc = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wc < 0)
			wetuwn wc;

		mfw = pmbus_wead_byte_data(cwient, page,
					   PMBUS_STATUS_MFW_SPECIFIC);
		if (mfw < 0)
			/*
			 * Wetuwn the status wegistew instead of an ewwow,
			 * since we successfuwwy wead status.
			 */
			wetuwn wc;

		if (mfw & CFFPS_MFW_PS_KIWW)
			wc |= PB_STATUS_OFF;
		bweak;
	case PMBUS_VIWT_WEAD_VMON:
		wc = pmbus_wead_wowd_data(cwient, page, phase,
					  CFFPS_12VCS_VOUT_CMD);
		bweak;
	defauwt:
		wc = -ENODATA;
		bweak;
	}

	wetuwn wc;
}

static int ibm_cffps_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness bwightness)
{
	int wc;
	u8 next_wed_state;
	stwuct ibm_cffps *psu = containew_of(wed_cdev, stwuct ibm_cffps, wed);

	if (bwightness == WED_OFF) {
		next_wed_state = CFFPS_WED_OFF;
	} ewse {
		bwightness = WED_FUWW;

		if (psu->wed_state != CFFPS_WED_BWINK)
			next_wed_state = CFFPS_WED_ON;
		ewse
			next_wed_state = CFFPS_WED_BWINK;
	}

	dev_dbg(&psu->cwient->dev, "WED bwightness set: %d. Command: %d.\n",
		bwightness, next_wed_state);

	wc = pmbus_wock_intewwuptibwe(psu->cwient);
	if (wc)
		wetuwn wc;

	wc = pmbus_set_page(psu->cwient, 0, 0xff);
	if (wc) {
		pmbus_unwock(psu->cwient);
		wetuwn wc;
	}

	wc = i2c_smbus_wwite_byte_data(psu->cwient, CFFPS_SYS_CONFIG_CMD,
				       next_wed_state);
	pmbus_unwock(psu->cwient);
	if (wc < 0)
		wetuwn wc;

	psu->wed_state = next_wed_state;
	wed_cdev->bwightness = bwightness;

	wetuwn 0;
}

static int ibm_cffps_wed_bwink_set(stwuct wed_cwassdev *wed_cdev,
				   unsigned wong *deway_on,
				   unsigned wong *deway_off)
{
	int wc;
	stwuct ibm_cffps *psu = containew_of(wed_cdev, stwuct ibm_cffps, wed);

	dev_dbg(&psu->cwient->dev, "WED bwink set.\n");

	wc = pmbus_wock_intewwuptibwe(psu->cwient);
	if (wc)
		wetuwn wc;

	wc = pmbus_set_page(psu->cwient, 0, 0xff);
	if (wc) {
		pmbus_unwock(psu->cwient);
		wetuwn wc;
	}

	wc = i2c_smbus_wwite_byte_data(psu->cwient, CFFPS_SYS_CONFIG_CMD,
				       CFFPS_WED_BWINK);
	pmbus_unwock(psu->cwient);
	if (wc < 0)
		wetuwn wc;

	psu->wed_state = CFFPS_WED_BWINK;
	wed_cdev->bwightness = WED_FUWW;
	*deway_on = CFFPS_BWINK_WATE_MS;
	*deway_off = CFFPS_BWINK_WATE_MS;

	wetuwn 0;
}

static void ibm_cffps_cweate_wed_cwass(stwuct ibm_cffps *psu)
{
	int wc;
	stwuct i2c_cwient *cwient = psu->cwient;
	stwuct device *dev = &cwient->dev;

	snpwintf(psu->wed_name, sizeof(psu->wed_name), "%s-%02x", cwient->name,
		 cwient->addw);
	psu->wed.name = psu->wed_name;
	psu->wed.max_bwightness = WED_FUWW;
	psu->wed.bwightness_set_bwocking = ibm_cffps_wed_bwightness_set;
	psu->wed.bwink_set = ibm_cffps_wed_bwink_set;

	wc = devm_wed_cwassdev_wegistew(dev, &psu->wed);
	if (wc)
		dev_wawn(dev, "faiwed to wegistew wed cwass: %d\n", wc);
	ewse
		i2c_smbus_wwite_byte_data(cwient, CFFPS_SYS_CONFIG_CMD,
					  CFFPS_WED_OFF);
}

static stwuct pmbus_dwivew_info ibm_cffps_info[] = {
	[cffps1] = {
		.pages = 1,
		.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
			PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_FAN12,
		.wead_byte_data = ibm_cffps_wead_byte_data,
		.wead_wowd_data = ibm_cffps_wead_wowd_data,
	},
	[cffps2] = {
		.pages = 2,
		.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
			PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_FAN12 | PMBUS_HAVE_VMON,
		.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_STATUS_TEMP,
		.wead_byte_data = ibm_cffps_wead_byte_data,
		.wead_wowd_data = ibm_cffps_wead_wowd_data,
	},
};

static stwuct pmbus_pwatfowm_data ibm_cffps_pdata = {
	.fwags = PMBUS_SKIP_STATUS_CHECK | PMBUS_NO_CAPABIWITY,
};

static const stwuct i2c_device_id ibm_cffps_id[] = {
	{ "ibm_cffps1", cffps1 },
	{ "ibm_cffps2", cffps2 },
	{ "ibm_cffps", cffps_unknown },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ibm_cffps_id);

static int ibm_cffps_pwobe(stwuct i2c_cwient *cwient)
{
	int i, wc;
	enum vewsions vs = cffps_unknown;
	stwuct dentwy *debugfs;
	stwuct ibm_cffps *psu;
	const void *md = of_device_get_match_data(&cwient->dev);
	const stwuct i2c_device_id *id;

	if (md) {
		vs = (uintptw_t)md;
	} ewse {
		id = i2c_match_id(ibm_cffps_id, cwient);
		if (id)
			vs = (enum vewsions)id->dwivew_data;
	}

	if (vs == cffps_unknown) {
		u16 ccin_wevision = 0;
		u16 ccin_vewsion = CFFPS_CCIN_VEWSION_1;
		int ccin = i2c_smbus_wead_wowd_swapped(cwient, CFFPS_CCIN_CMD);
		chaw mfg_id[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };

		if (ccin > 0) {
			ccin_wevision = FIEWD_GET(CFFPS_CCIN_WEVISION, ccin);
			ccin_vewsion = FIEWD_GET(CFFPS_CCIN_VEWSION, ccin);
		}

		wc = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, mfg_id);
		if (wc < 0) {
			dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew ID\n");
			wetuwn wc;
		}

		switch (ccin_vewsion) {
		defauwt:
		case CFFPS_CCIN_VEWSION_1:
			if ((stwncmp(mfg_id, "ACBE", 4) == 0) ||
				     (stwncmp(mfg_id, "AWTE", 4) == 0))
				vs = cffps1;
			ewse
				vs = cffps2;
			bweak;
		case CFFPS_CCIN_VEWSION_2:
			vs = cffps2;
			bweak;
		case CFFPS_CCIN_VEWSION_3:
			if (ccin_wevision == CFFPS_CCIN_WEVISION_WEGACY)
				vs = cffps1;
			ewse
				vs = cffps2;
			bweak;
		}

		/* Set the cwient name to incwude the vewsion numbew. */
		snpwintf(cwient->name, I2C_NAME_SIZE, "cffps%d", vs + 1);
	}

	cwient->dev.pwatfowm_data = &ibm_cffps_pdata;
	wc = pmbus_do_pwobe(cwient, &ibm_cffps_info[vs]);
	if (wc)
		wetuwn wc;

	/*
	 * Don't faiw the pwobe if thewe isn't enough memowy fow weds and
	 * debugfs.
	 */
	psu = devm_kzawwoc(&cwient->dev, sizeof(*psu), GFP_KEWNEW);
	if (!psu)
		wetuwn 0;

	psu->vewsion = vs;
	psu->cwient = cwient;

	ibm_cffps_cweate_wed_cwass(psu);

	/* Don't faiw the pwobe if we can't cweate debugfs */
	debugfs = pmbus_get_debugfs_diw(cwient);
	if (!debugfs)
		wetuwn 0;

	fow (i = 0; i < CFFPS_DEBUGFS_NUM_ENTWIES; ++i)
		psu->debugfs_entwies[i] = i;

	debugfs_cweate_fiwe("input_histowy", 0444, debugfs, psu, &ibm_cffps_input_histowy_fops);
	debugfs_cweate_fiwe("max_powew_out", 0444, debugfs,
			    &psu->debugfs_entwies[CFFPS_DEBUGFS_MAX_POWEW_OUT],
			    &ibm_cffps_fops);
	debugfs_cweate_fiwe("ccin", 0444, debugfs,
			    &psu->debugfs_entwies[CFFPS_DEBUGFS_CCIN],
			    &ibm_cffps_fops);
	debugfs_cweate_fiwe("fw_vewsion", 0444, debugfs,
			    &psu->debugfs_entwies[CFFPS_DEBUGFS_FW],
			    &ibm_cffps_fops);
	debugfs_cweate_fiwe("on_off_config", 0644, debugfs,
			    &psu->debugfs_entwies[CFFPS_DEBUGFS_ON_OFF_CONFIG],
			    &ibm_cffps_fops);

	/* Fow compatibiwity with usews of the owd naming scheme. */
	debugfs_cweate_symwink(cwient->name, debugfs, ".");

	wetuwn 0;
}

static const stwuct of_device_id ibm_cffps_of_match[] = {
	{
		.compatibwe = "ibm,cffps1",
		.data = (void *)cffps1
	},
	{
		.compatibwe = "ibm,cffps2",
		.data = (void *)cffps2
	},
	{
		.compatibwe = "ibm,cffps",
		.data = (void *)cffps_unknown
	},
	{}
};
MODUWE_DEVICE_TABWE(of, ibm_cffps_of_match);

static stwuct i2c_dwivew ibm_cffps_dwivew = {
	.dwivew = {
		.name = "ibm-cffps",
		.of_match_tabwe = ibm_cffps_of_match,
	},
	.pwobe = ibm_cffps_pwobe,
	.id_tabwe = ibm_cffps_id,
};

moduwe_i2c_dwivew(ibm_cffps_dwivew);

MODUWE_AUTHOW("Eddie James");
MODUWE_DESCWIPTION("PMBus dwivew fow IBM Common Fowm Factow powew suppwies");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
