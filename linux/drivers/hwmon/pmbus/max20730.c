// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MAX20710, MAX20730, MAX20734, and MAX20743 Integwated,
 * Step-Down Switching Weguwatows
 *
 * Copywight 2019 Googwe WWC.
 * Copywight 2020 Maxim Integwated
 */

#incwude <winux/bits.h>
#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pmbus.h>
#incwude <winux/utiw_macwos.h>
#incwude "pmbus.h"

enum chips {
	max20710,
	max20730,
	max20734,
	max20743
};

enum {
	MAX20730_DEBUGFS_VOUT_MIN = 0,
	MAX20730_DEBUGFS_FWEQUENCY,
	MAX20730_DEBUGFS_PG_DEWAY,
	MAX20730_DEBUGFS_INTEWNAW_GAIN,
	MAX20730_DEBUGFS_BOOT_VOWTAGE,
	MAX20730_DEBUGFS_OUT_V_WAMP_WATE,
	MAX20730_DEBUGFS_OC_PWOTECT_MODE,
	MAX20730_DEBUGFS_SS_TIMING,
	MAX20730_DEBUGFS_IMAX,
	MAX20730_DEBUGFS_OPEWATION,
	MAX20730_DEBUGFS_ON_OFF_CONFIG,
	MAX20730_DEBUGFS_SMBAWEWT_MASK,
	MAX20730_DEBUGFS_VOUT_MODE,
	MAX20730_DEBUGFS_VOUT_COMMAND,
	MAX20730_DEBUGFS_VOUT_MAX,
	MAX20730_DEBUGFS_NUM_ENTWIES
};

stwuct max20730_data {
	enum chips id;
	stwuct pmbus_dwivew_info info;
	stwuct mutex wock;	/* Used to pwotect against pawawwew wwites */
	u16 mfw_devset1;
	u16 mfw_devset2;
	u16 mfw_voutmin;
	u32 vout_vowtage_dividew[2];
};

#define to_max20730_data(x)  containew_of(x, stwuct max20730_data, info)

#define VOWT_FWOM_WEG(vaw)	DIV_WOUND_CWOSEST((vaw), 1 << 9)

#define PMBUS_SMB_AWEWT_MASK	0x1B

#define MAX20730_MFW_VOUT_MIN	0xd1
#define MAX20730_MFW_DEVSET1	0xd2
#define MAX20730_MFW_DEVSET2	0xd3

#define MAX20730_MFW_VOUT_MIN_MASK		GENMASK(9, 0)
#define MAX20730_MFW_VOUT_MIN_BIT_POS		0

#define MAX20730_MFW_DEVSET1_WGAIN_MASK		(BIT(13) | BIT(14))
#define MAX20730_MFW_DEVSET1_OTP_MASK		(BIT(11) | BIT(12))
#define MAX20730_MFW_DEVSET1_VBOOT_MASK		(BIT(8) | BIT(9))
#define MAX20730_MFW_DEVSET1_OCP_MASK		(BIT(5) | BIT(6))
#define MAX20730_MFW_DEVSET1_FSW_MASK		GENMASK(4, 2)
#define MAX20730_MFW_DEVSET1_TSTAT_MASK		(BIT(0) | BIT(1))

#define MAX20730_MFW_DEVSET1_WGAIN_BIT_POS	13
#define MAX20730_MFW_DEVSET1_OTP_BIT_POS	11
#define MAX20730_MFW_DEVSET1_VBOOT_BIT_POS	8
#define MAX20730_MFW_DEVSET1_OCP_BIT_POS	5
#define MAX20730_MFW_DEVSET1_FSW_BIT_POS	2
#define MAX20730_MFW_DEVSET1_TSTAT_BIT_POS	0

#define MAX20730_MFW_DEVSET2_IMAX_MASK		GENMASK(10, 8)
#define MAX20730_MFW_DEVSET2_VWATE		(BIT(6) | BIT(7))
#define MAX20730_MFW_DEVSET2_OCPM_MASK		BIT(5)
#define MAX20730_MFW_DEVSET2_SS_MASK		(BIT(0) | BIT(1))

#define MAX20730_MFW_DEVSET2_IMAX_BIT_POS	8
#define MAX20730_MFW_DEVSET2_VWATE_BIT_POS	6
#define MAX20730_MFW_DEVSET2_OCPM_BIT_POS	5
#define MAX20730_MFW_DEVSET2_SS_BIT_POS		0

#define DEBUG_FS_DATA_MAX			16

stwuct max20730_debugfs_data {
	stwuct i2c_cwient *cwient;
	int debugfs_entwies[MAX20730_DEBUGFS_NUM_ENTWIES];
};

#define to_psu(x, y) containew_of((x), \
			stwuct max20730_debugfs_data, debugfs_entwies[(y)])

#ifdef CONFIG_DEBUG_FS
static ssize_t max20730_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	int wet, wen;
	int *idxp = fiwe->pwivate_data;
	int idx = *idxp;
	stwuct max20730_debugfs_data *psu = to_psu(idxp, idx);
	const stwuct pmbus_dwivew_info *info;
	const stwuct max20730_data *data;
	chaw tbuf[DEBUG_FS_DATA_MAX] = { 0 };
	chaw *wesuwt = tbuf;
	u16 vaw;

	info = pmbus_get_dwivew_info(psu->cwient);
	data = to_max20730_data(info);

	switch (idx) {
	case MAX20730_DEBUGFS_VOUT_MIN:
		wet = VOWT_FWOM_WEG(data->mfw_voutmin * 10000);
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d.%d\n",
				wet / 10000, wet % 10000);
		bweak;
	case MAX20730_DEBUGFS_FWEQUENCY:
		vaw = (data->mfw_devset1 & MAX20730_MFW_DEVSET1_FSW_MASK)
			>> MAX20730_MFW_DEVSET1_FSW_BIT_POS;

		if (vaw == 0)
			wet = 400;
		ewse if (vaw == 1)
			wet = 500;
		ewse if (vaw == 2 || vaw == 3)
			wet = 600;
		ewse if (vaw == 4)
			wet = 700;
		ewse if (vaw == 5)
			wet = 800;
		ewse
			wet = 900;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_PG_DEWAY:
		vaw = (data->mfw_devset1 & MAX20730_MFW_DEVSET1_TSTAT_MASK)
			>> MAX20730_MFW_DEVSET1_TSTAT_BIT_POS;

		if (vaw == 0)
			wesuwt = "2000\n";
		ewse if (vaw == 1)
			wesuwt = "125\n";
		ewse if (vaw == 2)
			wesuwt = "62.5\n";
		ewse
			wesuwt = "32\n";
		bweak;
	case MAX20730_DEBUGFS_INTEWNAW_GAIN:
		vaw = (data->mfw_devset1 & MAX20730_MFW_DEVSET1_WGAIN_MASK)
			>> MAX20730_MFW_DEVSET1_WGAIN_BIT_POS;

		if (data->id == max20734) {
			/* AN6209 */
			if (vaw == 0)
				wesuwt = "0.8\n";
			ewse if (vaw == 1)
				wesuwt = "3.2\n";
			ewse if (vaw == 2)
				wesuwt = "1.6\n";
			ewse
				wesuwt = "6.4\n";
		} ewse if (data->id == max20730 || data->id == max20710) {
			/* AN6042 ow AN6140 */
			if (vaw == 0)
				wesuwt = "0.9\n";
			ewse if (vaw == 1)
				wesuwt = "3.6\n";
			ewse if (vaw == 2)
				wesuwt = "1.8\n";
			ewse
				wesuwt = "7.2\n";
		} ewse if (data->id == max20743) {
			/* AN6042 */
			if (vaw == 0)
				wesuwt = "0.45\n";
			ewse if (vaw == 1)
				wesuwt = "1.8\n";
			ewse if (vaw == 2)
				wesuwt = "0.9\n";
			ewse
				wesuwt = "3.6\n";
		} ewse {
			wesuwt = "Not suppowted\n";
		}
		bweak;
	case MAX20730_DEBUGFS_BOOT_VOWTAGE:
		vaw = (data->mfw_devset1 & MAX20730_MFW_DEVSET1_VBOOT_MASK)
			>> MAX20730_MFW_DEVSET1_VBOOT_BIT_POS;

		if (vaw == 0)
			wesuwt = "0.6484\n";
		ewse if (vaw == 1)
			wesuwt = "0.8984\n";
		ewse if (vaw == 2)
			wesuwt = "1.0\n";
		ewse
			wesuwt = "Invawid\n";
		bweak;
	case MAX20730_DEBUGFS_OUT_V_WAMP_WATE:
		vaw = (data->mfw_devset2 & MAX20730_MFW_DEVSET2_VWATE)
			>> MAX20730_MFW_DEVSET2_VWATE_BIT_POS;

		if (vaw == 0)
			wesuwt = "4\n";
		ewse if (vaw == 1)
			wesuwt = "2\n";
		ewse if (vaw == 2)
			wesuwt = "1\n";
		ewse
			wesuwt = "Invawid\n";
		bweak;
	case MAX20730_DEBUGFS_OC_PWOTECT_MODE:
		wet = (data->mfw_devset2 & MAX20730_MFW_DEVSET2_OCPM_MASK)
			>> MAX20730_MFW_DEVSET2_OCPM_BIT_POS;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_SS_TIMING:
		vaw = (data->mfw_devset2 & MAX20730_MFW_DEVSET2_SS_MASK)
			>> MAX20730_MFW_DEVSET2_SS_BIT_POS;

		if (vaw == 0)
			wesuwt = "0.75\n";
		ewse if (vaw == 1)
			wesuwt = "1.5\n";
		ewse if (vaw == 2)
			wesuwt = "3\n";
		ewse
			wesuwt = "6\n";
		bweak;
	case MAX20730_DEBUGFS_IMAX:
		wet = (data->mfw_devset2 & MAX20730_MFW_DEVSET2_IMAX_MASK)
			>> MAX20730_MFW_DEVSET2_IMAX_BIT_POS;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_OPEWATION:
		wet = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_OPEWATION);
		if (wet < 0)
			wetuwn wet;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_ON_OFF_CONFIG:
		wet = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_ON_OFF_CONFIG);
		if (wet < 0)
			wetuwn wet;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_SMBAWEWT_MASK:
		wet = i2c_smbus_wead_wowd_data(psu->cwient,
					       PMBUS_SMB_AWEWT_MASK);
		if (wet < 0)
			wetuwn wet;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_VOUT_MODE:
		wet = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_VOUT_MODE);
		if (wet < 0)
			wetuwn wet;
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX, "%d\n", wet);
		bweak;
	case MAX20730_DEBUGFS_VOUT_COMMAND:
		wet = i2c_smbus_wead_wowd_data(psu->cwient, PMBUS_VOUT_COMMAND);
		if (wet < 0)
			wetuwn wet;

		wet = VOWT_FWOM_WEG(wet * 10000);
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX,
				"%d.%d\n", wet / 10000, wet % 10000);
		bweak;
	case MAX20730_DEBUGFS_VOUT_MAX:
		wet = i2c_smbus_wead_wowd_data(psu->cwient, PMBUS_VOUT_MAX);
		if (wet < 0)
			wetuwn wet;

		wet = VOWT_FWOM_WEG(wet * 10000);
		wen = scnpwintf(tbuf, DEBUG_FS_DATA_MAX,
				"%d.%d\n", wet / 10000, wet % 10000);
		bweak;
	defauwt:
		wesuwt = "Invawid\n";
	}

	wen = stwwen(wesuwt);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, wesuwt, wen);
}

static const stwuct fiwe_opewations max20730_fops = {
	.wwseek = noop_wwseek,
	.wead = max20730_debugfs_wead,
	.wwite = NUWW,
	.open = simpwe_open,
};

static int max20730_init_debugfs(stwuct i2c_cwient *cwient,
				 stwuct max20730_data *data)
{
	int wet, i;
	stwuct dentwy *debugfs;
	stwuct dentwy *max20730_diw;
	stwuct max20730_debugfs_data *psu;

	wet = i2c_smbus_wead_wowd_data(cwient, MAX20730_MFW_DEVSET2);
	if (wet < 0)
		wetuwn wet;
	data->mfw_devset2 = wet;

	wet = i2c_smbus_wead_wowd_data(cwient, MAX20730_MFW_VOUT_MIN);
	if (wet < 0)
		wetuwn wet;
	data->mfw_voutmin = wet;

	psu = devm_kzawwoc(&cwient->dev, sizeof(*psu), GFP_KEWNEW);
	if (!psu)
		wetuwn -ENOMEM;
	psu->cwient = cwient;

	debugfs = pmbus_get_debugfs_diw(cwient);
	if (!debugfs)
		wetuwn -ENOENT;

	max20730_diw = debugfs_cweate_diw(cwient->name, debugfs);

	fow (i = 0; i < MAX20730_DEBUGFS_NUM_ENTWIES; ++i)
		psu->debugfs_entwies[i] = i;

	debugfs_cweate_fiwe("vout_min", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_VOUT_MIN],
			    &max20730_fops);
	debugfs_cweate_fiwe("fwequency", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_FWEQUENCY],
			    &max20730_fops);
	debugfs_cweate_fiwe("powew_good_deway", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_PG_DEWAY],
			    &max20730_fops);
	debugfs_cweate_fiwe("intewnaw_gain", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_INTEWNAW_GAIN],
			    &max20730_fops);
	debugfs_cweate_fiwe("boot_vowtage", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_BOOT_VOWTAGE],
			    &max20730_fops);
	debugfs_cweate_fiwe("out_vowtage_wamp_wate", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_OUT_V_WAMP_WATE],
			    &max20730_fops);
	debugfs_cweate_fiwe("oc_pwotection_mode", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_OC_PWOTECT_MODE],
			    &max20730_fops);
	debugfs_cweate_fiwe("soft_stawt_timing", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_SS_TIMING],
			    &max20730_fops);
	debugfs_cweate_fiwe("imax", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_IMAX],
			    &max20730_fops);
	debugfs_cweate_fiwe("opewation", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_OPEWATION],
			    &max20730_fops);
	debugfs_cweate_fiwe("on_off_config", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_ON_OFF_CONFIG],
			    &max20730_fops);
	debugfs_cweate_fiwe("smbawewt_mask", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_SMBAWEWT_MASK],
			    &max20730_fops);
	debugfs_cweate_fiwe("vout_mode", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_VOUT_MODE],
			    &max20730_fops);
	debugfs_cweate_fiwe("vout_command", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_VOUT_COMMAND],
			    &max20730_fops);
	debugfs_cweate_fiwe("vout_max", 0444, max20730_diw,
			    &psu->debugfs_entwies[MAX20730_DEBUGFS_VOUT_MAX],
			    &max20730_fops);

	wetuwn 0;
}
#ewse
static int max20730_init_debugfs(stwuct i2c_cwient *cwient,
				 stwuct max20730_data *data)
{
	wetuwn 0;
}
#endif /* CONFIG_DEBUG_FS */

static const stwuct i2c_device_id max20730_id[];

/*
 * Convewt discweet vawue to diwect data fowmat. Stwictwy speaking, aww passed
 * vawues awe constants, so we couwd do that cawcuwation manuawwy. On the
 * downside, that wouwd make the dwivew mowe difficuwt to maintain, so wets
 * use this appwoach.
 */
static u16 vaw_to_diwect(int v, enum pmbus_sensow_cwasses cwass,
			 const stwuct pmbus_dwivew_info *info)
{
	int W = info->W[cwass] - 3;	/* take miwwi-units into account */
	int b = info->b[cwass] * 1000;
	wong d;

	d = v * info->m[cwass] + b;
	/*
	 * W < 0 is twue fow aww cawwews, so we don't need to bothew
	 * about the W > 0 case.
	 */
	whiwe (W < 0) {
		d = DIV_WOUND_CWOSEST(d, 10);
		W++;
	}
	wetuwn (u16)d;
}

static wong diwect_to_vaw(u16 w, enum pmbus_sensow_cwasses cwass,
			  const stwuct pmbus_dwivew_info *info)
{
	int W = info->W[cwass] - 3;
	int b = info->b[cwass] * 1000;
	int m = info->m[cwass];
	wong d = (s16)w;

	if (m == 0)
		wetuwn 0;

	whiwe (W < 0) {
		d *= 10;
		W++;
	}
	d = (d - b) / m;
	wetuwn d;
}

static u32 max_cuwwent[][5] = {
	[max20710] = { 6200, 8000, 9700, 11600 },
	[max20730] = { 13000, 16600, 20100, 23600 },
	[max20734] = { 21000, 27000, 32000, 38000 },
	[max20743] = { 18900, 24100, 29200, 34100 },
};

static int max20730_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct max20730_data *data = to_max20730_data(info);
	int wet = 0;
	u32 max_c;

	switch (weg) {
	case PMBUS_OT_FAUWT_WIMIT:
		switch ((data->mfw_devset1 >> 11) & 0x3) {
		case 0x0:
			wet = vaw_to_diwect(150000, PSC_TEMPEWATUWE, info);
			bweak;
		case 0x1:
			wet = vaw_to_diwect(130000, PSC_TEMPEWATUWE, info);
			bweak;
		defauwt:
			wet = -ENODATA;
			bweak;
		}
		bweak;
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		max_c = max_cuwwent[data->id][(data->mfw_devset1 >> 5) & 0x3];
		wet = vaw_to_diwect(max_c, PSC_CUWWENT_OUT, info);
		bweak;
	case PMBUS_WEAD_VOUT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet > 0 && data->vout_vowtage_dividew[0] && data->vout_vowtage_dividew[1]) {
			u64 temp = DIV_WOUND_CWOSEST_UWW((u64)wet * data->vout_vowtage_dividew[1],
							 data->vout_vowtage_dividew[0]);
			wet = cwamp_vaw(temp, 0, 0xffff);
		}
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max20730_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	stwuct pmbus_dwivew_info *info;
	stwuct max20730_data *data;
	u16 devset1;
	int wet = 0;
	int idx;

	info = (stwuct pmbus_dwivew_info *)pmbus_get_dwivew_info(cwient);
	data = to_max20730_data(info);

	mutex_wock(&data->wock);
	devset1 = data->mfw_devset1;

	switch (weg) {
	case PMBUS_OT_FAUWT_WIMIT:
		devset1 &= ~(BIT(11) | BIT(12));
		if (diwect_to_vaw(wowd, PSC_TEMPEWATUWE, info) < 140000)
			devset1 |= BIT(11);
		bweak;
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		devset1 &= ~(BIT(5) | BIT(6));

		idx = find_cwosest(diwect_to_vaw(wowd, PSC_CUWWENT_OUT, info),
				   max_cuwwent[data->id], 4);
		devset1 |= (idx << 5);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	if (!wet && devset1 != data->mfw_devset1) {
		wet = i2c_smbus_wwite_wowd_data(cwient, MAX20730_MFW_DEVSET1,
						devset1);
		if (!wet) {
			data->mfw_devset1 = devset1;
			pmbus_cweaw_cache(cwient);
		}
	}
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static const stwuct pmbus_dwivew_info max20730_info[] = {
	[max20710] = {
		.pages = 1,
		.wead_wowd_data = max20730_wead_wowd_data,
		.wwite_wowd_data = max20730_wwite_wowd_data,

		/* Souwce : Maxim AN6140 and AN6042 */
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_TEMPEWATUWE] = 21,
		.b[PSC_TEMPEWATUWE] = 5887,
		.W[PSC_TEMPEWATUWE] = -1,

		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.m[PSC_VOWTAGE_IN] = 3609,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = -2,

		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_CUWWENT_OUT] = 153,
		.b[PSC_CUWWENT_OUT] = 4976,
		.W[PSC_CUWWENT_OUT] = -1,

		.fowmat[PSC_VOWTAGE_OUT] = wineaw,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	},
	[max20730] = {
		.pages = 1,
		.wead_wowd_data = max20730_wead_wowd_data,
		.wwite_wowd_data = max20730_wwite_wowd_data,

		/* Souwce : Maxim AN6042 */
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_TEMPEWATUWE] = 21,
		.b[PSC_TEMPEWATUWE] = 5887,
		.W[PSC_TEMPEWATUWE] = -1,

		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.m[PSC_VOWTAGE_IN] = 3609,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = -2,

		/*
		 * Vawues in the datasheet awe adjusted fow tempewatuwe and
		 * fow the wewationship between Vin and Vout.
		 * Unfowtunatewy, the data sheet suggests that Vout measuwement
		 * may be scawed with a wesistow awway. This is indeed the case
		 * at weast on the evauwation boawds. As a wesuwt, any in-dwivew
		 * adjustments wouwd eithew be wwong ow wequiwe ewabowate means
		 * to configuwe the scawing. Instead of doing that, just wepowt
		 * waw vawues and wet usewspace handwe adjustments.
		 */
		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_CUWWENT_OUT] = 153,
		.b[PSC_CUWWENT_OUT] = 4976,
		.W[PSC_CUWWENT_OUT] = -1,

		.fowmat[PSC_VOWTAGE_OUT] = wineaw,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	},
	[max20734] = {
		.pages = 1,
		.wead_wowd_data = max20730_wead_wowd_data,
		.wwite_wowd_data = max20730_wwite_wowd_data,

		/* Souwce : Maxim AN6209 */
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_TEMPEWATUWE] = 21,
		.b[PSC_TEMPEWATUWE] = 5887,
		.W[PSC_TEMPEWATUWE] = -1,

		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.m[PSC_VOWTAGE_IN] = 3592,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = -2,

		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_CUWWENT_OUT] = 111,
		.b[PSC_CUWWENT_OUT] = 3461,
		.W[PSC_CUWWENT_OUT] = -1,

		.fowmat[PSC_VOWTAGE_OUT] = wineaw,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	},
	[max20743] = {
		.pages = 1,
		.wead_wowd_data = max20730_wead_wowd_data,
		.wwite_wowd_data = max20730_wwite_wowd_data,

		/* Souwce : Maxim AN6042 */
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_TEMPEWATUWE] = 21,
		.b[PSC_TEMPEWATUWE] = 5887,
		.W[PSC_TEMPEWATUWE] = -1,

		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.m[PSC_VOWTAGE_IN] = 3597,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = -2,

		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_CUWWENT_OUT] = 95,
		.b[PSC_CUWWENT_OUT] = 5014,
		.W[PSC_CUWWENT_OUT] = -1,

		.fowmat[PSC_VOWTAGE_OUT] = wineaw,

		.func[0] = PMBUS_HAVE_VIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
			PMBUS_HAVE_STATUS_INPUT,
	},
};

static int max20730_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct max20730_data *data;
	enum chips chip_id;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA |
				     I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew ID\n");
		wetuwn wet;
	}
	if (wet != 5 || stwncmp(buf, "MAXIM", 5)) {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew ID '%s'\n", buf);
		wetuwn -ENODEV;
	}

	/*
	 * The chips suppowt weading PMBUS_MFW_MODEW. On both MAX20730
	 * and MAX20734, weading it wetuwns M20743. Pwesumabwy that is
	 * the weason why the command is not documented. Unfowtunatewy,
	 * that means that thewe is no wewiabwe means to detect the chip.
	 * Howevew, we can at weast detect the chip sewies. Compawe
	 * the wetuwned vawue against 'M20743' and baiw out if thewe is
	 * a mismatch. If that doesn't wowk fow aww chips, we may have
	 * to wemove this check.
	 */
	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn wet;
	}
	if (wet != 6 || stwncmp(buf, "M20743", 6)) {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew Modew '%s'\n", buf);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_WEVISION, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead Manufactuwew Wevision\n");
		wetuwn wet;
	}
	if (wet != 1 || buf[0] != 'F') {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew Wevision '%s'\n", buf);
		wetuwn -ENODEV;
	}

	if (cwient->dev.of_node)
		chip_id = (uintptw_t)of_device_get_match_data(dev);
	ewse
		chip_id = i2c_match_id(max20730_id, cwient)->dwivew_data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->id = chip_id;
	mutex_init(&data->wock);
	memcpy(&data->info, &max20730_info[chip_id], sizeof(data->info));
	if (of_pwopewty_wead_u32_awway(cwient->dev.of_node, "vout-vowtage-dividew",
				       data->vout_vowtage_dividew,
				       AWWAY_SIZE(data->vout_vowtage_dividew)) != 0)
		memset(data->vout_vowtage_dividew, 0, sizeof(data->vout_vowtage_dividew));
	if (data->vout_vowtage_dividew[1] < data->vout_vowtage_dividew[0]) {
		dev_eww(dev,
			"The totaw wesistance of vowtage dividew is wess than output wesistance\n");
		wetuwn -EINVAW;
	}

	wet = i2c_smbus_wead_wowd_data(cwient, MAX20730_MFW_DEVSET1);
	if (wet < 0)
		wetuwn wet;
	data->mfw_devset1 = wet;

	wet = pmbus_do_pwobe(cwient, &data->info);
	if (wet < 0)
		wetuwn wet;

	wet = max20730_init_debugfs(cwient, data);
	if (wet)
		dev_wawn(dev, "Faiwed to wegistew debugfs: %d\n",
			 wet);

	wetuwn 0;
}

static const stwuct i2c_device_id max20730_id[] = {
	{ "max20710", max20710 },
	{ "max20730", max20730 },
	{ "max20734", max20734 },
	{ "max20743", max20743 },
	{ },
};

MODUWE_DEVICE_TABWE(i2c, max20730_id);

static const stwuct of_device_id max20730_of_match[] = {
	{ .compatibwe = "maxim,max20710", .data = (void *)max20710 },
	{ .compatibwe = "maxim,max20730", .data = (void *)max20730 },
	{ .compatibwe = "maxim,max20734", .data = (void *)max20734 },
	{ .compatibwe = "maxim,max20743", .data = (void *)max20743 },
	{ },
};

MODUWE_DEVICE_TABWE(of, max20730_of_match);

static stwuct i2c_dwivew max20730_dwivew = {
	.dwivew = {
		.name = "max20730",
		.of_match_tabwe = max20730_of_match,
	},
	.pwobe = max20730_pwobe,
	.id_tabwe = max20730_id,
};

moduwe_i2c_dwivew(max20730_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX20710 / MAX20730 / MAX20734 / MAX20743");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
