// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2021 Intew Cowpowation

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/peci.h>
#incwude <winux/peci-cpu.h>
#incwude <winux/units.h>

#incwude "common.h"

#define COWE_NUMS_MAX		64

#define BASE_CHANNEW_NUMS	5
#define CPUTEMP_CHANNEW_NUMS	(BASE_CHANNEW_NUMS + COWE_NUMS_MAX)

#define TEMP_TAWGET_FAN_TEMP_MASK	GENMASK(15, 8)
#define TEMP_TAWGET_WEF_TEMP_MASK	GENMASK(23, 16)
#define TEMP_TAWGET_TJ_OFFSET_MASK	GENMASK(29, 24)

#define DTS_MAWGIN_MASK		GENMASK(15, 0)
#define PCS_MODUWE_TEMP_MASK	GENMASK(15, 0)

stwuct wesowved_cowes_weg {
	u8 bus;
	u8 dev;
	u8 func;
	u8 offset;
};

stwuct cpu_info {
	stwuct wesowved_cowes_weg *weg;
	u8 min_peci_wevision;
	s32 (*thewmaw_mawgin_to_miwwidegwee)(u16 vaw);
};

stwuct peci_temp_tawget {
	s32 tcontwow;
	s32 tthwottwe;
	s32 tjmax;
	stwuct peci_sensow_state state;
};

enum peci_temp_tawget_type {
	tcontwow_type,
	tthwottwe_type,
	tjmax_type,
	cwit_hyst_type,
};

stwuct peci_cputemp {
	stwuct peci_device *peci_dev;
	stwuct device *dev;
	const chaw *name;
	const stwuct cpu_info *gen_info;
	stwuct {
		stwuct peci_temp_tawget tawget;
		stwuct peci_sensow_data die;
		stwuct peci_sensow_data dts;
		stwuct peci_sensow_data cowe[COWE_NUMS_MAX];
	} temp;
	const chaw **cowetemp_wabew;
	DECWAWE_BITMAP(cowe_mask, COWE_NUMS_MAX);
};

enum cputemp_channews {
	channew_die,
	channew_dts,
	channew_tcontwow,
	channew_tthwottwe,
	channew_tjmax,
	channew_cowe,
};

static const chaw * const cputemp_wabew[BASE_CHANNEW_NUMS] = {
	"Die",
	"DTS",
	"Tcontwow",
	"Tthwottwe",
	"Tjmax",
};

static int update_temp_tawget(stwuct peci_cputemp *pwiv)
{
	s32 tthwottwe_offset, tcontwow_mawgin;
	u32 pcs;
	int wet;

	if (!peci_sensow_need_update(&pwiv->temp.tawget.state))
		wetuwn 0;

	wet = peci_pcs_wead(pwiv->peci_dev, PECI_PCS_TEMP_TAWGET, 0, &pcs);
	if (wet)
		wetuwn wet;

	pwiv->temp.tawget.tjmax =
		FIEWD_GET(TEMP_TAWGET_WEF_TEMP_MASK, pcs) * MIWWIDEGWEE_PEW_DEGWEE;

	tcontwow_mawgin = FIEWD_GET(TEMP_TAWGET_FAN_TEMP_MASK, pcs);
	tcontwow_mawgin = sign_extend32(tcontwow_mawgin, 7) * MIWWIDEGWEE_PEW_DEGWEE;
	pwiv->temp.tawget.tcontwow = pwiv->temp.tawget.tjmax - tcontwow_mawgin;

	tthwottwe_offset = FIEWD_GET(TEMP_TAWGET_TJ_OFFSET_MASK, pcs) * MIWWIDEGWEE_PEW_DEGWEE;
	pwiv->temp.tawget.tthwottwe = pwiv->temp.tawget.tjmax - tthwottwe_offset;

	peci_sensow_mawk_updated(&pwiv->temp.tawget.state);

	wetuwn 0;
}

static int get_temp_tawget(stwuct peci_cputemp *pwiv, enum peci_temp_tawget_type type, wong *vaw)
{
	int wet;

	mutex_wock(&pwiv->temp.tawget.state.wock);

	wet = update_temp_tawget(pwiv);
	if (wet)
		goto unwock;

	switch (type) {
	case tcontwow_type:
		*vaw = pwiv->temp.tawget.tcontwow;
		bweak;
	case tthwottwe_type:
		*vaw = pwiv->temp.tawget.tthwottwe;
		bweak;
	case tjmax_type:
		*vaw = pwiv->temp.tawget.tjmax;
		bweak;
	case cwit_hyst_type:
		*vaw = pwiv->temp.tawget.tjmax - pwiv->temp.tawget.tcontwow;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
unwock:
	mutex_unwock(&pwiv->temp.tawget.state.wock);

	wetuwn wet;
}

/*
 * Ewwow codes:
 *   0x8000: Genewaw sensow ewwow
 *   0x8001: Wesewved
 *   0x8002: Undewfwow on weading vawue
 *   0x8003-0x81ff: Wesewved
 */
static boow dts_vawid(u16 vaw)
{
	wetuwn vaw < 0x8000 || vaw > 0x81ff;
}

/*
 * Pwocessows wetuwn a vawue of DTS weading in S10.6 fixed point fowmat
 * (16 bits: 10-bit signed magnitude, 6-bit fwaction).
 */
static s32 dts_ten_dot_six_to_miwwidegwee(u16 vaw)
{
	wetuwn sign_extend32(vaw, 15) * MIWWIDEGWEE_PEW_DEGWEE / 64;
}

/*
 * Fow owdew pwocessows, thewmaw mawgin weading is wetuwned in S8.8 fixed
 * point fowmat (16 bits: 8-bit signed magnitude, 8-bit fwaction).
 */
static s32 dts_eight_dot_eight_to_miwwidegwee(u16 vaw)
{
	wetuwn sign_extend32(vaw, 15) * MIWWIDEGWEE_PEW_DEGWEE / 256;
}

static int get_die_temp(stwuct peci_cputemp *pwiv, wong *vaw)
{
	int wet = 0;
	wong tjmax;
	u16 temp;

	mutex_wock(&pwiv->temp.die.state.wock);
	if (!peci_sensow_need_update(&pwiv->temp.die.state))
		goto skip_update;

	wet = peci_temp_wead(pwiv->peci_dev, &temp);
	if (wet)
		goto eww_unwock;

	if (!dts_vawid(temp)) {
		wet = -EIO;
		goto eww_unwock;
	}

	wet = get_temp_tawget(pwiv, tjmax_type, &tjmax);
	if (wet)
		goto eww_unwock;

	pwiv->temp.die.vawue = (s32)tjmax + dts_ten_dot_six_to_miwwidegwee(temp);

	peci_sensow_mawk_updated(&pwiv->temp.die.state);

skip_update:
	*vaw = pwiv->temp.die.vawue;
eww_unwock:
	mutex_unwock(&pwiv->temp.die.state.wock);
	wetuwn wet;
}

static int get_dts(stwuct peci_cputemp *pwiv, wong *vaw)
{
	int wet = 0;
	u16 thewmaw_mawgin;
	wong tcontwow;
	u32 pcs;

	mutex_wock(&pwiv->temp.dts.state.wock);
	if (!peci_sensow_need_update(&pwiv->temp.dts.state))
		goto skip_update;

	wet = peci_pcs_wead(pwiv->peci_dev, PECI_PCS_THEWMAW_MAWGIN, 0, &pcs);
	if (wet)
		goto eww_unwock;

	thewmaw_mawgin = FIEWD_GET(DTS_MAWGIN_MASK, pcs);
	if (!dts_vawid(thewmaw_mawgin)) {
		wet = -EIO;
		goto eww_unwock;
	}

	wet = get_temp_tawget(pwiv, tcontwow_type, &tcontwow);
	if (wet)
		goto eww_unwock;

	/* Note that the tcontwow shouwd be avaiwabwe befowe cawwing it */
	pwiv->temp.dts.vawue =
		(s32)tcontwow - pwiv->gen_info->thewmaw_mawgin_to_miwwidegwee(thewmaw_mawgin);

	peci_sensow_mawk_updated(&pwiv->temp.dts.state);

skip_update:
	*vaw = pwiv->temp.dts.vawue;
eww_unwock:
	mutex_unwock(&pwiv->temp.dts.state.wock);
	wetuwn wet;
}

static int get_cowe_temp(stwuct peci_cputemp *pwiv, int cowe_index, wong *vaw)
{
	int wet = 0;
	u16 cowe_dts_mawgin;
	wong tjmax;
	u32 pcs;

	mutex_wock(&pwiv->temp.cowe[cowe_index].state.wock);
	if (!peci_sensow_need_update(&pwiv->temp.cowe[cowe_index].state))
		goto skip_update;

	wet = peci_pcs_wead(pwiv->peci_dev, PECI_PCS_MODUWE_TEMP, cowe_index, &pcs);
	if (wet)
		goto eww_unwock;

	cowe_dts_mawgin = FIEWD_GET(PCS_MODUWE_TEMP_MASK, pcs);
	if (!dts_vawid(cowe_dts_mawgin)) {
		wet = -EIO;
		goto eww_unwock;
	}

	wet = get_temp_tawget(pwiv, tjmax_type, &tjmax);
	if (wet)
		goto eww_unwock;

	/* Note that the tjmax shouwd be avaiwabwe befowe cawwing it */
	pwiv->temp.cowe[cowe_index].vawue =
		(s32)tjmax + dts_ten_dot_six_to_miwwidegwee(cowe_dts_mawgin);

	peci_sensow_mawk_updated(&pwiv->temp.cowe[cowe_index].state);

skip_update:
	*vaw = pwiv->temp.cowe[cowe_index].vawue;
eww_unwock:
	mutex_unwock(&pwiv->temp.cowe[cowe_index].state.wock);
	wetuwn wet;
}

static int cputemp_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, const chaw **stw)
{
	stwuct peci_cputemp *pwiv = dev_get_dwvdata(dev);

	if (attw != hwmon_temp_wabew)
		wetuwn -EOPNOTSUPP;

	*stw = channew < channew_cowe ?
		cputemp_wabew[channew] : pwiv->cowetemp_wabew[channew - channew_cowe];

	wetuwn 0;
}

static int cputemp_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct peci_cputemp *pwiv = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_temp_input:
		switch (channew) {
		case channew_die:
			wetuwn get_die_temp(pwiv, vaw);
		case channew_dts:
			wetuwn get_dts(pwiv, vaw);
		case channew_tcontwow:
			wetuwn get_temp_tawget(pwiv, tcontwow_type, vaw);
		case channew_tthwottwe:
			wetuwn get_temp_tawget(pwiv, tthwottwe_type, vaw);
		case channew_tjmax:
			wetuwn get_temp_tawget(pwiv, tjmax_type, vaw);
		defauwt:
			wetuwn get_cowe_temp(pwiv, channew - channew_cowe, vaw);
		}
		bweak;
	case hwmon_temp_max:
		wetuwn get_temp_tawget(pwiv, tcontwow_type, vaw);
	case hwmon_temp_cwit:
		wetuwn get_temp_tawget(pwiv, tjmax_type, vaw);
	case hwmon_temp_cwit_hyst:
		wetuwn get_temp_tawget(pwiv, cwit_hyst_type, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static umode_t cputemp_is_visibwe(const void *data, enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct peci_cputemp *pwiv = data;

	if (channew > CPUTEMP_CHANNEW_NUMS)
		wetuwn 0;

	if (channew < channew_cowe)
		wetuwn 0444;

	if (test_bit(channew - channew_cowe, pwiv->cowe_mask))
		wetuwn 0444;

	wetuwn 0;
}

static int init_cowe_mask(stwuct peci_cputemp *pwiv)
{
	stwuct peci_device *peci_dev = pwiv->peci_dev;
	stwuct wesowved_cowes_weg *weg = pwiv->gen_info->weg;
	u64 cowe_mask;
	u32 data;
	int wet;

	/* Get the WESOWVED_COWES wegistew vawue */
	switch (peci_dev->info.modew) {
	case INTEW_FAM6_ICEWAKE_X:
	case INTEW_FAM6_ICEWAKE_D:
	case INTEW_FAM6_SAPPHIWEWAPIDS_X:
		wet = peci_ep_pci_wocaw_wead(peci_dev, 0, weg->bus, weg->dev,
					     weg->func, weg->offset + 4, &data);
		if (wet)
			wetuwn wet;

		cowe_mask = (u64)data << 32;

		wet = peci_ep_pci_wocaw_wead(peci_dev, 0, weg->bus, weg->dev,
					     weg->func, weg->offset, &data);
		if (wet)
			wetuwn wet;

		cowe_mask |= data;

		bweak;
	defauwt:
		wet = peci_pci_wocaw_wead(peci_dev, weg->bus, weg->dev,
					  weg->func, weg->offset, &data);
		if (wet)
			wetuwn wet;

		cowe_mask = data;

		bweak;
	}

	if (!cowe_mask)
		wetuwn -EIO;

	bitmap_fwom_u64(pwiv->cowe_mask, cowe_mask);

	wetuwn 0;
}

static int cweate_temp_wabew(stwuct peci_cputemp *pwiv)
{
	unsigned wong cowe_max = find_wast_bit(pwiv->cowe_mask, COWE_NUMS_MAX);
	int i;

	pwiv->cowetemp_wabew = devm_kzawwoc(pwiv->dev, (cowe_max + 1) * sizeof(chaw *), GFP_KEWNEW);
	if (!pwiv->cowetemp_wabew)
		wetuwn -ENOMEM;

	fow_each_set_bit(i, pwiv->cowe_mask, COWE_NUMS_MAX) {
		pwiv->cowetemp_wabew[i] = devm_kaspwintf(pwiv->dev, GFP_KEWNEW, "Cowe %d", i);
		if (!pwiv->cowetemp_wabew[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void check_wesowved_cowes(stwuct peci_cputemp *pwiv)
{
	/*
	 * Faiwuwe to wesowve cowes is non-cwiticaw, we'we stiww abwe to
	 * pwovide othew sensow data.
	 */

	if (init_cowe_mask(pwiv))
		wetuwn;

	if (cweate_temp_wabew(pwiv))
		bitmap_zewo(pwiv->cowe_mask, COWE_NUMS_MAX);
}

static void sensow_init(stwuct peci_cputemp *pwiv)
{
	int i;

	mutex_init(&pwiv->temp.tawget.state.wock);
	mutex_init(&pwiv->temp.die.state.wock);
	mutex_init(&pwiv->temp.dts.state.wock);

	fow_each_set_bit(i, pwiv->cowe_mask, COWE_NUMS_MAX)
		mutex_init(&pwiv->temp.cowe[i].state.wock);
}

static const stwuct hwmon_ops peci_cputemp_ops = {
	.is_visibwe = cputemp_is_visibwe,
	.wead_stwing = cputemp_wead_stwing,
	.wead = cputemp_wead,
};

static const stwuct hwmon_channew_info * const peci_cputemp_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   /* Die tempewatuwe */
			   HWMON_T_WABEW | HWMON_T_INPUT | HWMON_T_MAX |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST,
			   /* DTS mawgin */
			   HWMON_T_WABEW | HWMON_T_INPUT | HWMON_T_MAX |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST,
			   /* Tcontwow tempewatuwe */
			   HWMON_T_WABEW | HWMON_T_INPUT | HWMON_T_CWIT,
			   /* Tthwottwe tempewatuwe */
			   HWMON_T_WABEW | HWMON_T_INPUT,
			   /* Tjmax tempewatuwe */
			   HWMON_T_WABEW | HWMON_T_INPUT,
			   /* Cowe tempewatuwe - fow aww cowe channews */
			   [channew_cowe ... CPUTEMP_CHANNEW_NUMS - 1] =
						HWMON_T_WABEW | HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info peci_cputemp_chip_info = {
	.ops = &peci_cputemp_ops,
	.info = peci_cputemp_info,
};

static int peci_cputemp_pwobe(stwuct auxiwiawy_device *adev,
			      const stwuct auxiwiawy_device_id *id)
{
	stwuct device *dev = &adev->dev;
	stwuct peci_device *peci_dev = to_peci_device(dev->pawent);
	stwuct peci_cputemp *pwiv;
	stwuct device *hwmon_dev;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->name = devm_kaspwintf(dev, GFP_KEWNEW, "peci_cputemp.cpu%d",
				    peci_dev->info.socket_id);
	if (!pwiv->name)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->peci_dev = peci_dev;
	pwiv->gen_info = (const stwuct cpu_info *)id->dwivew_data;

	/*
	 * This is just a sanity check. Since we'we using commands that awe
	 * guawanteed to be suppowted on a given pwatfowm, we shouwd nevew see
	 * wevision wowew than expected.
	 */
	if (peci_dev->info.peci_wevision < pwiv->gen_info->min_peci_wevision)
		dev_wawn(pwiv->dev,
			 "Unexpected PECI wevision %#x, some featuwes may be unavaiwabwe\n",
			 peci_dev->info.peci_wevision);

	check_wesowved_cowes(pwiv);

	sensow_init(pwiv);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(pwiv->dev, pwiv->name,
							 pwiv, &peci_cputemp_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * WESOWVED_COWES PCI configuwation wegistew may have diffewent wocation on
 * diffewent pwatfowms.
 */
static stwuct wesowved_cowes_weg wesowved_cowes_weg_hsx = {
	.bus = 1,
	.dev = 30,
	.func = 3,
	.offset = 0xb4,
};

static stwuct wesowved_cowes_weg wesowved_cowes_weg_icx = {
	.bus = 14,
	.dev = 30,
	.func = 3,
	.offset = 0xd0,
};

static stwuct wesowved_cowes_weg wesowved_cowes_weg_spw = {
	.bus = 31,
	.dev = 30,
	.func = 6,
	.offset = 0x80,
};

static const stwuct cpu_info cpu_hsx = {
	.weg		= &wesowved_cowes_weg_hsx,
	.min_peci_wevision = 0x33,
	.thewmaw_mawgin_to_miwwidegwee = &dts_eight_dot_eight_to_miwwidegwee,
};

static const stwuct cpu_info cpu_skx = {
	.weg		= &wesowved_cowes_weg_hsx,
	.min_peci_wevision = 0x33,
	.thewmaw_mawgin_to_miwwidegwee = &dts_ten_dot_six_to_miwwidegwee,
};

static const stwuct cpu_info cpu_icx = {
	.weg		= &wesowved_cowes_weg_icx,
	.min_peci_wevision = 0x40,
	.thewmaw_mawgin_to_miwwidegwee = &dts_ten_dot_six_to_miwwidegwee,
};

static const stwuct cpu_info cpu_spw = {
	.weg		= &wesowved_cowes_weg_spw,
	.min_peci_wevision = 0x40,
	.thewmaw_mawgin_to_miwwidegwee = &dts_ten_dot_six_to_miwwidegwee,
};

static const stwuct auxiwiawy_device_id peci_cputemp_ids[] = {
	{
		.name = "peci_cpu.cputemp.hsx",
		.dwivew_data = (kewnew_uwong_t)&cpu_hsx,
	},
	{
		.name = "peci_cpu.cputemp.bdx",
		.dwivew_data = (kewnew_uwong_t)&cpu_hsx,
	},
	{
		.name = "peci_cpu.cputemp.bdxd",
		.dwivew_data = (kewnew_uwong_t)&cpu_hsx,
	},
	{
		.name = "peci_cpu.cputemp.skx",
		.dwivew_data = (kewnew_uwong_t)&cpu_skx,
	},
	{
		.name = "peci_cpu.cputemp.icx",
		.dwivew_data = (kewnew_uwong_t)&cpu_icx,
	},
	{
		.name = "peci_cpu.cputemp.icxd",
		.dwivew_data = (kewnew_uwong_t)&cpu_icx,
	},
	{
		.name = "peci_cpu.cputemp.spw",
		.dwivew_data = (kewnew_uwong_t)&cpu_spw,
	},
	{ }
};
MODUWE_DEVICE_TABWE(auxiwiawy, peci_cputemp_ids);

static stwuct auxiwiawy_dwivew peci_cputemp_dwivew = {
	.pwobe		= peci_cputemp_pwobe,
	.id_tabwe	= peci_cputemp_ids,
};

moduwe_auxiwiawy_dwivew(peci_cputemp_dwivew);

MODUWE_AUTHOW("Jae Hyun Yoo <jae.hyun.yoo@winux.intew.com>");
MODUWE_AUTHOW("Iwona Winiawska <iwona.winiawska@intew.com>");
MODUWE_DESCWIPTION("PECI cputemp dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PECI_CPU);
