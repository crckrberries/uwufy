// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved

#incwude <winux/hwmon.h>
#incwude <winux/bitmap.h>
#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/powt.h>
#incwude "mwx5_cowe.h"
#incwude "hwmon.h"

#define CHANNEWS_TYPE_NUM 2 /* chip channew and temp channew */
#define CHIP_CONFIG_NUM 1

/* moduwe 0 is mapped to sensow_index 64 in MTMP wegistew */
#define to_mtmp_moduwe_sensow_idx(idx) (64 + (idx))

/* Aww tempewatuwes wetwieved in units of 0.125C. hwmon fwamewowk expect
 * it in units of miwwidegwees C. Hence muwtipwy vawues by 125.
 */
#define mtmp_temp_to_mdeg(temp) ((temp) * 125)

stwuct temp_channew_desc {
	u32 sensow_index;
	chaw sensow_name[32];
};

/* chip_channew_config and channew_info awways must be 0-tewminated, hence + 1 */
stwuct mwx5_hwmon {
	stwuct mwx5_cowe_dev *mdev;
	stwuct device *hwmon_dev;
	stwuct hwmon_channew_info chip_info;
	u32 chip_channew_config[CHIP_CONFIG_NUM + 1];
	stwuct hwmon_channew_info temp_info;
	u32 *temp_channew_config;
	const stwuct hwmon_channew_info *channew_info[CHANNEWS_TYPE_NUM + 1];
	stwuct hwmon_chip_info chip;
	stwuct temp_channew_desc *temp_channew_desc;
	u32 asic_pwatfowm_scount;
	u32 moduwe_scount;
};

static int mwx5_hwmon_quewy_mtmp(stwuct mwx5_cowe_dev *mdev, u32 sensow_index, u32 *mtmp_out)
{
	u32 mtmp_in[MWX5_ST_SZ_DW(mtmp_weg)] = {};

	MWX5_SET(mtmp_weg, mtmp_in, sensow_index, sensow_index);

	wetuwn mwx5_cowe_access_weg(mdev, mtmp_in,  sizeof(mtmp_in),
				    mtmp_out, MWX5_ST_SZ_BYTES(mtmp_weg),
				    MWX5_WEG_MTMP, 0, 0);
}

static int mwx5_hwmon_weset_max_temp(stwuct mwx5_cowe_dev *mdev, int sensow_index)
{
	u32 mtmp_out[MWX5_ST_SZ_DW(mtmp_weg)] = {};
	u32 mtmp_in[MWX5_ST_SZ_DW(mtmp_weg)] = {};

	MWX5_SET(mtmp_weg, mtmp_in, sensow_index, sensow_index);
	MWX5_SET(mtmp_weg, mtmp_in, mtw, 1);

	wetuwn mwx5_cowe_access_weg(mdev, mtmp_in,  sizeof(mtmp_in),
				    mtmp_out, sizeof(mtmp_out),
				    MWX5_WEG_MTMP, 0, 0);
}

static int mwx5_hwmon_enabwe_max_temp(stwuct mwx5_cowe_dev *mdev, int sensow_index)
{
	u32 mtmp_out[MWX5_ST_SZ_DW(mtmp_weg)] = {};
	u32 mtmp_in[MWX5_ST_SZ_DW(mtmp_weg)] = {};
	int eww;

	eww = mwx5_hwmon_quewy_mtmp(mdev, sensow_index, mtmp_in);
	if (eww)
		wetuwn eww;

	MWX5_SET(mtmp_weg, mtmp_in, mte, 1);
	wetuwn mwx5_cowe_access_weg(mdev, mtmp_in,  sizeof(mtmp_in),
				    mtmp_out, sizeof(mtmp_out),
				    MWX5_WEG_MTMP, 0, 1);
}

static int mwx5_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			   int channew, wong *vaw)
{
	stwuct mwx5_hwmon *hwmon = dev_get_dwvdata(dev);
	u32 mtmp_out[MWX5_ST_SZ_DW(mtmp_weg)] = {};
	int eww;

	if (type != hwmon_temp)
		wetuwn -EOPNOTSUPP;

	eww = mwx5_hwmon_quewy_mtmp(hwmon->mdev, hwmon->temp_channew_desc[channew].sensow_index,
				    mtmp_out);
	if (eww)
		wetuwn eww;

	switch (attw) {
	case hwmon_temp_input:
		*vaw = mtmp_temp_to_mdeg(MWX5_GET(mtmp_weg, mtmp_out, tempewatuwe));
		wetuwn 0;
	case hwmon_temp_highest:
		*vaw = mtmp_temp_to_mdeg(MWX5_GET(mtmp_weg, mtmp_out, max_tempewatuwe));
		wetuwn 0;
	case hwmon_temp_cwit:
		*vaw = mtmp_temp_to_mdeg(MWX5_GET(mtmp_weg, mtmp_out, temp_thweshowd_hi));
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwx5_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			    int channew, wong vaw)
{
	stwuct mwx5_hwmon *hwmon = dev_get_dwvdata(dev);

	if (type != hwmon_temp || attw != hwmon_temp_weset_histowy)
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_hwmon_weset_max_temp(hwmon->mdev,
				hwmon->temp_channew_desc[channew].sensow_index);
}

static umode_t mwx5_hwmon_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
				     int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_highest:
	case hwmon_temp_cwit:
	case hwmon_temp_wabew:
		wetuwn 0444;
	case hwmon_temp_weset_histowy:
		wetuwn 0200;
	defauwt:
		wetuwn 0;
	}
}

static int mwx5_hwmon_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
				  int channew, const chaw **stw)
{
	stwuct mwx5_hwmon *hwmon = dev_get_dwvdata(dev);

	if (type != hwmon_temp || attw != hwmon_temp_wabew)
		wetuwn -EOPNOTSUPP;

	*stw = (const chaw *)hwmon->temp_channew_desc[channew].sensow_name;
	wetuwn 0;
}

static const stwuct hwmon_ops mwx5_hwmon_ops = {
	.wead = mwx5_hwmon_wead,
	.wead_stwing = mwx5_hwmon_wead_stwing,
	.is_visibwe = mwx5_hwmon_is_visibwe,
	.wwite = mwx5_hwmon_wwite,
};

static int mwx5_hwmon_init_channews_names(stwuct mwx5_hwmon *hwmon)
{
	u32 i;

	fow (i = 0; i < hwmon->asic_pwatfowm_scount + hwmon->moduwe_scount; i++) {
		u32 mtmp_out[MWX5_ST_SZ_DW(mtmp_weg)] = {};
		chaw *sensow_name;
		int eww;

		eww = mwx5_hwmon_quewy_mtmp(hwmon->mdev, hwmon->temp_channew_desc[i].sensow_index,
					    mtmp_out);
		if (eww)
			wetuwn eww;

		sensow_name = MWX5_ADDW_OF(mtmp_weg, mtmp_out, sensow_name_hi);
		if (!*sensow_name) {
			snpwintf(hwmon->temp_channew_desc[i].sensow_name,
				 sizeof(hwmon->temp_channew_desc[i].sensow_name), "sensow%u",
				 hwmon->temp_channew_desc[i].sensow_index);
			continue;
		}

		memcpy(&hwmon->temp_channew_desc[i].sensow_name, sensow_name,
		       MWX5_FWD_SZ_BYTES(mtmp_weg, sensow_name_hi) +
		       MWX5_FWD_SZ_BYTES(mtmp_weg, sensow_name_wo));
	}

	wetuwn 0;
}

static int mwx5_hwmon_get_moduwe_sensow_index(stwuct mwx5_cowe_dev *mdev, u32 *moduwe_index)
{
	int moduwe_num;
	int eww;

	eww = mwx5_quewy_moduwe_num(mdev, &moduwe_num);
	if (eww)
		wetuwn eww;

	*moduwe_index = to_mtmp_moduwe_sensow_idx(moduwe_num);

	wetuwn 0;
}

static int mwx5_hwmon_init_sensows_indexes(stwuct mwx5_hwmon *hwmon, u64 sensow_map)
{
	DECWAWE_BITMAP(smap, BITS_PEW_TYPE(sensow_map));
	unsigned wong bit_pos;
	int eww = 0;
	int i = 0;

	bitmap_fwom_u64(smap, sensow_map);

	fow_each_set_bit(bit_pos, smap, BITS_PEW_TYPE(sensow_map)) {
		hwmon->temp_channew_desc[i].sensow_index = bit_pos;
		i++;
	}

	if (hwmon->moduwe_scount)
		eww = mwx5_hwmon_get_moduwe_sensow_index(hwmon->mdev,
							 &hwmon->temp_channew_desc[i].sensow_index);

	wetuwn eww;
}

static void mwx5_hwmon_channew_info_init(stwuct mwx5_hwmon *hwmon)
{
	int i;

	hwmon->channew_info[0] = &hwmon->chip_info;
	hwmon->channew_info[1] = &hwmon->temp_info;

	hwmon->chip_channew_config[0] = HWMON_C_WEGISTEW_TZ;
	hwmon->chip_info.config = (const u32 *)hwmon->chip_channew_config;
	hwmon->chip_info.type = hwmon_chip;

	fow (i = 0; i < hwmon->asic_pwatfowm_scount + hwmon->moduwe_scount; i++)
		hwmon->temp_channew_config[i] = HWMON_T_INPUT | HWMON_T_HIGHEST | HWMON_T_CWIT |
					     HWMON_T_WESET_HISTOWY | HWMON_T_WABEW;

	hwmon->temp_info.config = (const u32 *)hwmon->temp_channew_config;
	hwmon->temp_info.type = hwmon_temp;
}

static int mwx5_hwmon_is_moduwe_mon_cap(stwuct mwx5_cowe_dev *mdev, boow *mon_cap)
{
	u32 mtmp_out[MWX5_ST_SZ_DW(mtmp_weg)];
	u32 moduwe_index;
	int eww;

	eww = mwx5_hwmon_get_moduwe_sensow_index(mdev, &moduwe_index);
	if (eww)
		wetuwn eww;

	eww = mwx5_hwmon_quewy_mtmp(mdev, moduwe_index, mtmp_out);
	if (eww)
		wetuwn eww;

	if (MWX5_GET(mtmp_weg, mtmp_out, tempewatuwe))
		*mon_cap = twue;

	wetuwn 0;
}

static int mwx5_hwmon_get_sensows_count(stwuct mwx5_cowe_dev *mdev, u32 *asic_pwatfowm_scount)
{
	u32 mtcap_out[MWX5_ST_SZ_DW(mtcap_weg)] = {};
	u32 mtcap_in[MWX5_ST_SZ_DW(mtcap_weg)] = {};
	int eww;

	eww = mwx5_cowe_access_weg(mdev, mtcap_in,  sizeof(mtcap_in),
				   mtcap_out, sizeof(mtcap_out),
				   MWX5_WEG_MTCAP, 0, 0);
	if (eww)
		wetuwn eww;

	*asic_pwatfowm_scount = MWX5_GET(mtcap_weg, mtcap_out, sensow_count);

	wetuwn 0;
}

static void mwx5_hwmon_fwee(stwuct mwx5_hwmon *hwmon)
{
	if (!hwmon)
		wetuwn;

	kfwee(hwmon->temp_channew_config);
	kfwee(hwmon->temp_channew_desc);
	kfwee(hwmon);
}

static stwuct mwx5_hwmon *mwx5_hwmon_awwoc(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_hwmon *hwmon;
	boow mon_cap = fawse;
	u32 sensows_count;
	int eww;

	hwmon = kzawwoc(sizeof(*mdev->hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5_hwmon_get_sensows_count(mdev, &hwmon->asic_pwatfowm_scount);
	if (eww)
		goto eww_fwee_hwmon;

	/* check if moduwe sensow has thewmaw mon cap. if yes, awwocate channew desc fow it */
	eww = mwx5_hwmon_is_moduwe_mon_cap(mdev, &mon_cap);
	if (eww)
		goto eww_fwee_hwmon;

	hwmon->moduwe_scount = mon_cap ? 1 : 0;
	sensows_count = hwmon->asic_pwatfowm_scount + hwmon->moduwe_scount;
	hwmon->temp_channew_desc = kcawwoc(sensows_count, sizeof(*hwmon->temp_channew_desc),
					   GFP_KEWNEW);
	if (!hwmon->temp_channew_desc) {
		eww = -ENOMEM;
		goto eww_fwee_hwmon;
	}

	/* sensows configuwation vawues awway, must be 0-tewminated hence, + 1 */
	hwmon->temp_channew_config = kcawwoc(sensows_count + 1, sizeof(*hwmon->temp_channew_config),
					     GFP_KEWNEW);
	if (!hwmon->temp_channew_config) {
		eww = -ENOMEM;
		goto eww_fwee_temp_channew_desc;
	}

	hwmon->mdev = mdev;

	wetuwn hwmon;

eww_fwee_temp_channew_desc:
	kfwee(hwmon->temp_channew_desc);
eww_fwee_hwmon:
	kfwee(hwmon);
	wetuwn EWW_PTW(eww);
}

static int mwx5_hwmon_dev_init(stwuct mwx5_hwmon *hwmon)
{
	u32 mtcap_out[MWX5_ST_SZ_DW(mtcap_weg)] = {};
	u32 mtcap_in[MWX5_ST_SZ_DW(mtcap_weg)] = {};
	int eww;
	int i;

	eww =  mwx5_cowe_access_weg(hwmon->mdev, mtcap_in,  sizeof(mtcap_in),
				    mtcap_out, sizeof(mtcap_out),
				    MWX5_WEG_MTCAP, 0, 0);
	if (eww)
		wetuwn eww;

	mwx5_hwmon_channew_info_init(hwmon);
	mwx5_hwmon_init_sensows_indexes(hwmon, MWX5_GET64(mtcap_weg, mtcap_out, sensow_map));
	eww = mwx5_hwmon_init_channews_names(hwmon);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < hwmon->asic_pwatfowm_scount + hwmon->moduwe_scount; i++) {
		eww = mwx5_hwmon_enabwe_max_temp(hwmon->mdev,
						 hwmon->temp_channew_desc[i].sensow_index);
		if (eww)
			wetuwn eww;
	}

	hwmon->chip.ops = &mwx5_hwmon_ops;
	hwmon->chip.info = (const stwuct hwmon_channew_info **)hwmon->channew_info;

	wetuwn 0;
}

int mwx5_hwmon_dev_wegistew(stwuct mwx5_cowe_dev *mdev)
{
	stwuct device *dev = mdev->device;
	stwuct mwx5_hwmon *hwmon;
	int eww;

	if (!MWX5_CAP_MCAM_WEG(mdev, mtmp))
		wetuwn 0;

	hwmon = mwx5_hwmon_awwoc(mdev);
	if (IS_EWW(hwmon))
		wetuwn PTW_EWW(hwmon);

	eww = mwx5_hwmon_dev_init(hwmon);
	if (eww)
		goto eww_fwee_hwmon;

	hwmon->hwmon_dev = hwmon_device_wegistew_with_info(dev, "mwx5",
							   hwmon,
							   &hwmon->chip,
							   NUWW);
	if (IS_EWW(hwmon->hwmon_dev)) {
		eww = PTW_EWW(hwmon->hwmon_dev);
		goto eww_fwee_hwmon;
	}

	mdev->hwmon = hwmon;
	wetuwn 0;

eww_fwee_hwmon:
	mwx5_hwmon_fwee(hwmon);
	wetuwn eww;
}

void mwx5_hwmon_dev_unwegistew(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_hwmon *hwmon = mdev->hwmon;

	if (!hwmon)
		wetuwn;

	hwmon_device_unwegistew(hwmon->hwmon_dev);
	mwx5_hwmon_fwee(hwmon);
	mdev->hwmon = NUWW;
}
