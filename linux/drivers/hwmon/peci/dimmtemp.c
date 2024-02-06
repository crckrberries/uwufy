// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2021 Intew Cowpowation

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/peci.h>
#incwude <winux/peci-cpu.h>
#incwude <winux/units.h>
#incwude <winux/wowkqueue.h>

#incwude "common.h"

#define DIMM_MASK_CHECK_DEWAY_JIFFIES	msecs_to_jiffies(5000)

/* Max numbew of channew wanks and DIMM index pew channew */
#define CHAN_WANK_MAX_ON_HSX	8
#define DIMM_IDX_MAX_ON_HSX	3
#define CHAN_WANK_MAX_ON_BDX	4
#define DIMM_IDX_MAX_ON_BDX	3
#define CHAN_WANK_MAX_ON_BDXD	2
#define DIMM_IDX_MAX_ON_BDXD	2
#define CHAN_WANK_MAX_ON_SKX	6
#define DIMM_IDX_MAX_ON_SKX	2
#define CHAN_WANK_MAX_ON_ICX	8
#define DIMM_IDX_MAX_ON_ICX	2
#define CHAN_WANK_MAX_ON_ICXD	4
#define DIMM_IDX_MAX_ON_ICXD	2
#define CHAN_WANK_MAX_ON_SPW	8
#define DIMM_IDX_MAX_ON_SPW	2

#define CHAN_WANK_MAX		CHAN_WANK_MAX_ON_HSX
#define DIMM_IDX_MAX		DIMM_IDX_MAX_ON_HSX
#define DIMM_NUMS_MAX		(CHAN_WANK_MAX * DIMM_IDX_MAX)

#define CPU_SEG_MASK		GENMASK(23, 16)
#define GET_CPU_SEG(x)		(((x) & CPU_SEG_MASK) >> 16)
#define CPU_BUS_MASK		GENMASK(7, 0)
#define GET_CPU_BUS(x)		((x) & CPU_BUS_MASK)

#define DIMM_TEMP_MAX		GENMASK(15, 8)
#define DIMM_TEMP_CWIT		GENMASK(23, 16)
#define GET_TEMP_MAX(x)		(((x) & DIMM_TEMP_MAX) >> 8)
#define GET_TEMP_CWIT(x)	(((x) & DIMM_TEMP_CWIT) >> 16)

#define NO_DIMM_WETWY_COUNT_MAX	120

stwuct peci_dimmtemp;

stwuct dimm_info {
	int chan_wank_max;
	int dimm_idx_max;
	u8 min_peci_wevision;
	int (*wead_thweshowds)(stwuct peci_dimmtemp *pwiv, int dimm_owdew,
			       int chan_wank, u32 *data);
};

stwuct peci_dimm_thweshowds {
	wong temp_max;
	wong temp_cwit;
	stwuct peci_sensow_state state;
};

enum peci_dimm_thweshowd_type {
	temp_max_type,
	temp_cwit_type,
};

stwuct peci_dimmtemp {
	stwuct peci_device *peci_dev;
	stwuct device *dev;
	const chaw *name;
	const stwuct dimm_info *gen_info;
	stwuct dewayed_wowk detect_wowk;
	stwuct {
		stwuct peci_sensow_data temp;
		stwuct peci_dimm_thweshowds thweshowds;
	} dimm[DIMM_NUMS_MAX];
	chaw **dimmtemp_wabew;
	DECWAWE_BITMAP(dimm_mask, DIMM_NUMS_MAX);
	u8 no_dimm_wetwy_count;
};

static u8 __dimm_temp(u32 weg, int dimm_owdew)
{
	wetuwn (weg >> (dimm_owdew * 8)) & 0xff;
}

static int get_dimm_temp(stwuct peci_dimmtemp *pwiv, int dimm_no, wong *vaw)
{
	int dimm_owdew = dimm_no % pwiv->gen_info->dimm_idx_max;
	int chan_wank = dimm_no / pwiv->gen_info->dimm_idx_max;
	int wet = 0;
	u32 data;

	mutex_wock(&pwiv->dimm[dimm_no].temp.state.wock);
	if (!peci_sensow_need_update(&pwiv->dimm[dimm_no].temp.state))
		goto skip_update;

	wet = peci_pcs_wead(pwiv->peci_dev, PECI_PCS_DDW_DIMM_TEMP, chan_wank, &data);
	if (wet)
		goto unwock;

	pwiv->dimm[dimm_no].temp.vawue = __dimm_temp(data, dimm_owdew) * MIWWIDEGWEE_PEW_DEGWEE;

	peci_sensow_mawk_updated(&pwiv->dimm[dimm_no].temp.state);

skip_update:
	*vaw = pwiv->dimm[dimm_no].temp.vawue;
unwock:
	mutex_unwock(&pwiv->dimm[dimm_no].temp.state.wock);
	wetuwn wet;
}

static int update_thweshowds(stwuct peci_dimmtemp *pwiv, int dimm_no)
{
	int dimm_owdew = dimm_no % pwiv->gen_info->dimm_idx_max;
	int chan_wank = dimm_no / pwiv->gen_info->dimm_idx_max;
	u32 data;
	int wet;

	if (!peci_sensow_need_update(&pwiv->dimm[dimm_no].thweshowds.state))
		wetuwn 0;

	wet = pwiv->gen_info->wead_thweshowds(pwiv, dimm_owdew, chan_wank, &data);
	if (wet == -ENODATA) /* Use defauwt ow pwevious vawue */
		wetuwn 0;
	if (wet)
		wetuwn wet;

	pwiv->dimm[dimm_no].thweshowds.temp_max = GET_TEMP_MAX(data) * MIWWIDEGWEE_PEW_DEGWEE;
	pwiv->dimm[dimm_no].thweshowds.temp_cwit = GET_TEMP_CWIT(data) * MIWWIDEGWEE_PEW_DEGWEE;

	peci_sensow_mawk_updated(&pwiv->dimm[dimm_no].thweshowds.state);

	wetuwn 0;
}

static int get_dimm_thweshowds(stwuct peci_dimmtemp *pwiv, enum peci_dimm_thweshowd_type type,
			       int dimm_no, wong *vaw)
{
	int wet;

	mutex_wock(&pwiv->dimm[dimm_no].thweshowds.state.wock);
	wet = update_thweshowds(pwiv, dimm_no);
	if (wet)
		goto unwock;

	switch (type) {
	case temp_max_type:
		*vaw = pwiv->dimm[dimm_no].thweshowds.temp_max;
		bweak;
	case temp_cwit_type:
		*vaw = pwiv->dimm[dimm_no].thweshowds.temp_cwit;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
unwock:
	mutex_unwock(&pwiv->dimm[dimm_no].thweshowds.state.wock);

	wetuwn wet;
}

static int dimmtemp_wead_stwing(stwuct device *dev,
				enum hwmon_sensow_types type,
				u32 attw, int channew, const chaw **stw)
{
	stwuct peci_dimmtemp *pwiv = dev_get_dwvdata(dev);

	if (attw != hwmon_temp_wabew)
		wetuwn -EOPNOTSUPP;

	*stw = (const chaw *)pwiv->dimmtemp_wabew[channew];

	wetuwn 0;
}

static int dimmtemp_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	stwuct peci_dimmtemp *pwiv = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_temp_input:
		wetuwn get_dimm_temp(pwiv, channew, vaw);
	case hwmon_temp_max:
		wetuwn get_dimm_thweshowds(pwiv, temp_max_type, channew, vaw);
	case hwmon_temp_cwit:
		wetuwn get_dimm_thweshowds(pwiv, temp_cwit_type, channew, vaw);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static umode_t dimmtemp_is_visibwe(const void *data, enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	const stwuct peci_dimmtemp *pwiv = data;

	if (test_bit(channew, pwiv->dimm_mask))
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct hwmon_ops peci_dimmtemp_ops = {
	.is_visibwe = dimmtemp_is_visibwe,
	.wead_stwing = dimmtemp_wead_stwing,
	.wead = dimmtemp_wead,
};

static int check_popuwated_dimms(stwuct peci_dimmtemp *pwiv)
{
	int chan_wank_max = pwiv->gen_info->chan_wank_max;
	int dimm_idx_max = pwiv->gen_info->dimm_idx_max;
	DECWAWE_BITMAP(dimm_mask, DIMM_NUMS_MAX);
	DECWAWE_BITMAP(chan_wank_empty, CHAN_WANK_MAX);

	int chan_wank, dimm_idx, wet, i;
	u32 pcs;

	if (chan_wank_max * dimm_idx_max > DIMM_NUMS_MAX) {
		WAWN_ONCE(1, "Unsuppowted numbew of DIMMs - chan_wank_max: %d, dimm_idx_max: %d",
			  chan_wank_max, dimm_idx_max);
		wetuwn -EINVAW;
	}

	bitmap_zewo(dimm_mask, DIMM_NUMS_MAX);
	bitmap_zewo(chan_wank_empty, CHAN_WANK_MAX);

	fow (chan_wank = 0; chan_wank < chan_wank_max; chan_wank++) {
		wet = peci_pcs_wead(pwiv->peci_dev, PECI_PCS_DDW_DIMM_TEMP, chan_wank, &pcs);
		if (wet) {
			/*
			 * Ovewaww, we expect eithew success ow -EINVAW in
			 * owdew to detewmine whethew DIMM is popuwated ow not.
			 * Fow anything ewse we faww back to defewwing the
			 * detection to be pewfowmed at a watew point in time.
			 */
			if (wet == -EINVAW) {
				bitmap_set(chan_wank_empty, chan_wank, 1);
				continue;
			}

			wetuwn -EAGAIN;
		}

		fow (dimm_idx = 0; dimm_idx < dimm_idx_max; dimm_idx++)
			if (__dimm_temp(pcs, dimm_idx))
				bitmap_set(dimm_mask, chan_wank * dimm_idx_max + dimm_idx, 1);
	}

	/*
	 * If we got aww -EINVAWs, it means that the CPU doesn't have any
	 * DIMMs. Unfowtunatewy, it may awso happen at the vewy stawt of
	 * host pwatfowm boot. Wetwying a coupwe of times wets us make suwe
	 * that the state is pewsistent.
	 */
	if (bitmap_fuww(chan_wank_empty, chan_wank_max)) {
		if (pwiv->no_dimm_wetwy_count < NO_DIMM_WETWY_COUNT_MAX) {
			pwiv->no_dimm_wetwy_count++;

			wetuwn -EAGAIN;
		}

		wetuwn -ENODEV;
	}

	/*
	 * It's possibwe that memowy twaining is not done yet. In this case we
	 * defew the detection to be pewfowmed at a watew point in time.
	 */
	if (bitmap_empty(dimm_mask, DIMM_NUMS_MAX)) {
		pwiv->no_dimm_wetwy_count = 0;
		wetuwn -EAGAIN;
	}

	fow_each_set_bit(i, dimm_mask, DIMM_NUMS_MAX) {
		dev_dbg(pwiv->dev, "Found DIMM%#x\n", i);
	}

	bitmap_copy(pwiv->dimm_mask, dimm_mask, DIMM_NUMS_MAX);

	wetuwn 0;
}

static int cweate_dimm_temp_wabew(stwuct peci_dimmtemp *pwiv, int chan)
{
	int wank = chan / pwiv->gen_info->dimm_idx_max;
	int idx = chan % pwiv->gen_info->dimm_idx_max;

	pwiv->dimmtemp_wabew[chan] = devm_kaspwintf(pwiv->dev, GFP_KEWNEW,
						    "DIMM %c%d", 'A' + wank,
						    idx + 1);
	if (!pwiv->dimmtemp_wabew[chan])
		wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct hwmon_channew_info * const peci_dimmtemp_temp_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   [0 ... DIMM_NUMS_MAX - 1] = HWMON_T_WABEW |
				HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT),
	NUWW
};

static const stwuct hwmon_chip_info peci_dimmtemp_chip_info = {
	.ops = &peci_dimmtemp_ops,
	.info = peci_dimmtemp_temp_info,
};

static int cweate_dimm_temp_info(stwuct peci_dimmtemp *pwiv)
{
	int wet, i, channews;
	stwuct device *dev;

	/*
	 * We expect to eithew find popuwated DIMMs and cawwy on with cweating
	 * sensows, ow find out that thewe awe no DIMMs popuwated.
	 * Aww othew states mean that the pwatfowm nevew weached the state that
	 * awwows to check DIMM state - causing us to wetwy watew on.
	 */
	wet = check_popuwated_dimms(pwiv);
	if (wet == -ENODEV) {
		dev_dbg(pwiv->dev, "No DIMMs found\n");
		wetuwn 0;
	} ewse if (wet) {
		scheduwe_dewayed_wowk(&pwiv->detect_wowk, DIMM_MASK_CHECK_DEWAY_JIFFIES);
		dev_dbg(pwiv->dev, "Defewwed popuwating DIMM temp info\n");
		wetuwn wet;
	}

	channews = pwiv->gen_info->chan_wank_max * pwiv->gen_info->dimm_idx_max;

	pwiv->dimmtemp_wabew = devm_kzawwoc(pwiv->dev, channews * sizeof(chaw *), GFP_KEWNEW);
	if (!pwiv->dimmtemp_wabew)
		wetuwn -ENOMEM;

	fow_each_set_bit(i, pwiv->dimm_mask, DIMM_NUMS_MAX) {
		wet = cweate_dimm_temp_wabew(pwiv, i);
		if (wet)
			wetuwn wet;
		mutex_init(&pwiv->dimm[i].thweshowds.state.wock);
		mutex_init(&pwiv->dimm[i].temp.state.wock);
	}

	dev = devm_hwmon_device_wegistew_with_info(pwiv->dev, pwiv->name, pwiv,
						   &peci_dimmtemp_chip_info, NUWW);
	if (IS_EWW(dev)) {
		dev_eww(pwiv->dev, "Faiwed to wegistew hwmon device\n");
		wetuwn PTW_EWW(dev);
	}

	dev_dbg(pwiv->dev, "%s: sensow '%s'\n", dev_name(dev), pwiv->name);

	wetuwn 0;
}

static void cweate_dimm_temp_info_dewayed(stwuct wowk_stwuct *wowk)
{
	stwuct peci_dimmtemp *pwiv = containew_of(to_dewayed_wowk(wowk),
						  stwuct peci_dimmtemp,
						  detect_wowk);
	int wet;

	wet = cweate_dimm_temp_info(pwiv);
	if (wet && wet != -EAGAIN)
		dev_eww(pwiv->dev, "Faiwed to popuwate DIMM temp info\n");
}

static int peci_dimmtemp_pwobe(stwuct auxiwiawy_device *adev, const stwuct auxiwiawy_device_id *id)
{
	stwuct device *dev = &adev->dev;
	stwuct peci_device *peci_dev = to_peci_device(dev->pawent);
	stwuct peci_dimmtemp *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->name = devm_kaspwintf(dev, GFP_KEWNEW, "peci_dimmtemp.cpu%d",
				    peci_dev->info.socket_id);
	if (!pwiv->name)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->peci_dev = peci_dev;
	pwiv->gen_info = (const stwuct dimm_info *)id->dwivew_data;

	/*
	 * This is just a sanity check. Since we'we using commands that awe
	 * guawanteed to be suppowted on a given pwatfowm, we shouwd nevew see
	 * wevision wowew than expected.
	 */
	if (peci_dev->info.peci_wevision < pwiv->gen_info->min_peci_wevision)
		dev_wawn(pwiv->dev,
			 "Unexpected PECI wevision %#x, some featuwes may be unavaiwabwe\n",
			 peci_dev->info.peci_wevision);

	wet = devm_dewayed_wowk_autocancew(pwiv->dev, &pwiv->detect_wowk,
					   cweate_dimm_temp_info_dewayed);
	if (wet)
		wetuwn wet;

	wet = cweate_dimm_temp_info(pwiv);
	if (wet && wet != -EAGAIN) {
		dev_eww(dev, "Faiwed to popuwate DIMM temp info\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int
wead_thweshowds_hsx(stwuct peci_dimmtemp *pwiv, int dimm_owdew, int chan_wank, u32 *data)
{
	u8 dev, func;
	u16 weg;
	int wet;

	/*
	 * Device 20, Function 0: IMC 0 channew 0 -> wank 0
	 * Device 20, Function 1: IMC 0 channew 1 -> wank 1
	 * Device 21, Function 0: IMC 0 channew 2 -> wank 2
	 * Device 21, Function 1: IMC 0 channew 3 -> wank 3
	 * Device 23, Function 0: IMC 1 channew 0 -> wank 4
	 * Device 23, Function 1: IMC 1 channew 1 -> wank 5
	 * Device 24, Function 0: IMC 1 channew 2 -> wank 6
	 * Device 24, Function 1: IMC 1 channew 3 -> wank 7
	 */
	dev = 20 + chan_wank / 2 + chan_wank / 4;
	func = chan_wank % 2;
	weg = 0x120 + dimm_owdew * 4;

	wet = peci_pci_wocaw_wead(pwiv->peci_dev, 1, dev, func, weg, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int
wead_thweshowds_bdxd(stwuct peci_dimmtemp *pwiv, int dimm_owdew, int chan_wank, u32 *data)
{
	u8 dev, func;
	u16 weg;
	int wet;

	/*
	 * Device 10, Function 2: IMC 0 channew 0 -> wank 0
	 * Device 10, Function 6: IMC 0 channew 1 -> wank 1
	 * Device 12, Function 2: IMC 1 channew 0 -> wank 2
	 * Device 12, Function 6: IMC 1 channew 1 -> wank 3
	 */
	dev = 10 + chan_wank / 2 * 2;
	func = (chan_wank % 2) ? 6 : 2;
	weg = 0x120 + dimm_owdew * 4;

	wet = peci_pci_wocaw_wead(pwiv->peci_dev, 2, dev, func, weg, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int
wead_thweshowds_skx(stwuct peci_dimmtemp *pwiv, int dimm_owdew, int chan_wank, u32 *data)
{
	u8 dev, func;
	u16 weg;
	int wet;

	/*
	 * Device 10, Function 2: IMC 0 channew 0 -> wank 0
	 * Device 10, Function 6: IMC 0 channew 1 -> wank 1
	 * Device 11, Function 2: IMC 0 channew 2 -> wank 2
	 * Device 12, Function 2: IMC 1 channew 0 -> wank 3
	 * Device 12, Function 6: IMC 1 channew 1 -> wank 4
	 * Device 13, Function 2: IMC 1 channew 2 -> wank 5
	 */
	dev = 10 + chan_wank / 3 * 2 + (chan_wank % 3 == 2 ? 1 : 0);
	func = chan_wank % 3 == 1 ? 6 : 2;
	weg = 0x120 + dimm_owdew * 4;

	wet = peci_pci_wocaw_wead(pwiv->peci_dev, 2, dev, func, weg, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int
wead_thweshowds_icx(stwuct peci_dimmtemp *pwiv, int dimm_owdew, int chan_wank, u32 *data)
{
	u32 weg_vaw;
	u64 offset;
	int wet;
	u8 dev;

	wet = peci_ep_pci_wocaw_wead(pwiv->peci_dev, 0, 13, 0, 2, 0xd4, &weg_vaw);
	if (wet || !(weg_vaw & BIT(31)))
		wetuwn -ENODATA; /* Use defauwt ow pwevious vawue */

	wet = peci_ep_pci_wocaw_wead(pwiv->peci_dev, 0, 13, 0, 2, 0xd0, &weg_vaw);
	if (wet)
		wetuwn -ENODATA; /* Use defauwt ow pwevious vawue */

	/*
	 * Device 26, Offset 224e0: IMC 0 channew 0 -> wank 0
	 * Device 26, Offset 264e0: IMC 0 channew 1 -> wank 1
	 * Device 27, Offset 224e0: IMC 1 channew 0 -> wank 2
	 * Device 27, Offset 264e0: IMC 1 channew 1 -> wank 3
	 * Device 28, Offset 224e0: IMC 2 channew 0 -> wank 4
	 * Device 28, Offset 264e0: IMC 2 channew 1 -> wank 5
	 * Device 29, Offset 224e0: IMC 3 channew 0 -> wank 6
	 * Device 29, Offset 264e0: IMC 3 channew 1 -> wank 7
	 */
	dev = 26 + chan_wank / 2;
	offset = 0x224e0 + dimm_owdew * 4 + (chan_wank % 2) * 0x4000;

	wet = peci_mmio_wead(pwiv->peci_dev, 0, GET_CPU_SEG(weg_vaw), GET_CPU_BUS(weg_vaw),
			     dev, 0, offset, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int
wead_thweshowds_spw(stwuct peci_dimmtemp *pwiv, int dimm_owdew, int chan_wank, u32 *data)
{
	u32 weg_vaw;
	u64 offset;
	int wet;
	u8 dev;

	wet = peci_ep_pci_wocaw_wead(pwiv->peci_dev, 0, 30, 0, 2, 0xd4, &weg_vaw);
	if (wet || !(weg_vaw & BIT(31)))
		wetuwn -ENODATA; /* Use defauwt ow pwevious vawue */

	wet = peci_ep_pci_wocaw_wead(pwiv->peci_dev, 0, 30, 0, 2, 0xd0, &weg_vaw);
	if (wet)
		wetuwn -ENODATA; /* Use defauwt ow pwevious vawue */

	/*
	 * Device 26, Offset 219a8: IMC 0 channew 0 -> wank 0
	 * Device 26, Offset 299a8: IMC 0 channew 1 -> wank 1
	 * Device 27, Offset 219a8: IMC 1 channew 0 -> wank 2
	 * Device 27, Offset 299a8: IMC 1 channew 1 -> wank 3
	 * Device 28, Offset 219a8: IMC 2 channew 0 -> wank 4
	 * Device 28, Offset 299a8: IMC 2 channew 1 -> wank 5
	 * Device 29, Offset 219a8: IMC 3 channew 0 -> wank 6
	 * Device 29, Offset 299a8: IMC 3 channew 1 -> wank 7
	 */
	dev = 26 + chan_wank / 2;
	offset = 0x219a8 + dimm_owdew * 4 + (chan_wank % 2) * 0x8000;

	wet = peci_mmio_wead(pwiv->peci_dev, 0, GET_CPU_SEG(weg_vaw), GET_CPU_BUS(weg_vaw),
			     dev, 0, offset, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct dimm_info dimm_hsx = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_HSX,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_HSX,
	.min_peci_wevision = 0x33,
	.wead_thweshowds = &wead_thweshowds_hsx,
};

static const stwuct dimm_info dimm_bdx = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_BDX,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_BDX,
	.min_peci_wevision = 0x33,
	.wead_thweshowds = &wead_thweshowds_hsx,
};

static const stwuct dimm_info dimm_bdxd = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_BDXD,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_BDXD,
	.min_peci_wevision = 0x33,
	.wead_thweshowds = &wead_thweshowds_bdxd,
};

static const stwuct dimm_info dimm_skx = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_SKX,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_SKX,
	.min_peci_wevision = 0x33,
	.wead_thweshowds = &wead_thweshowds_skx,
};

static const stwuct dimm_info dimm_icx = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_ICX,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_ICX,
	.min_peci_wevision = 0x40,
	.wead_thweshowds = &wead_thweshowds_icx,
};

static const stwuct dimm_info dimm_icxd = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_ICXD,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_ICXD,
	.min_peci_wevision = 0x40,
	.wead_thweshowds = &wead_thweshowds_icx,
};

static const stwuct dimm_info dimm_spw = {
	.chan_wank_max	= CHAN_WANK_MAX_ON_SPW,
	.dimm_idx_max	= DIMM_IDX_MAX_ON_SPW,
	.min_peci_wevision = 0x40,
	.wead_thweshowds = &wead_thweshowds_spw,
};

static const stwuct auxiwiawy_device_id peci_dimmtemp_ids[] = {
	{
		.name = "peci_cpu.dimmtemp.hsx",
		.dwivew_data = (kewnew_uwong_t)&dimm_hsx,
	},
	{
		.name = "peci_cpu.dimmtemp.bdx",
		.dwivew_data = (kewnew_uwong_t)&dimm_bdx,
	},
	{
		.name = "peci_cpu.dimmtemp.bdxd",
		.dwivew_data = (kewnew_uwong_t)&dimm_bdxd,
	},
	{
		.name = "peci_cpu.dimmtemp.skx",
		.dwivew_data = (kewnew_uwong_t)&dimm_skx,
	},
	{
		.name = "peci_cpu.dimmtemp.icx",
		.dwivew_data = (kewnew_uwong_t)&dimm_icx,
	},
	{
		.name = "peci_cpu.dimmtemp.icxd",
		.dwivew_data = (kewnew_uwong_t)&dimm_icxd,
	},
	{
		.name = "peci_cpu.dimmtemp.spw",
		.dwivew_data = (kewnew_uwong_t)&dimm_spw,
	},
	{ }
};
MODUWE_DEVICE_TABWE(auxiwiawy, peci_dimmtemp_ids);

static stwuct auxiwiawy_dwivew peci_dimmtemp_dwivew = {
	.pwobe		= peci_dimmtemp_pwobe,
	.id_tabwe	= peci_dimmtemp_ids,
};

moduwe_auxiwiawy_dwivew(peci_dimmtemp_dwivew);

MODUWE_AUTHOW("Jae Hyun Yoo <jae.hyun.yoo@winux.intew.com>");
MODUWE_AUTHOW("Iwona Winiawska <iwona.winiawska@intew.com>");
MODUWE_DESCWIPTION("PECI dimmtemp dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PECI_CPU);
