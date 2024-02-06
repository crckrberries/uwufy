// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Intew Cowpowation.
 * Wei Chuanhua <Chuanhua.wei@intew.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#define WCU_WST_STAT	0x0024
#define WCU_WST_WEQ	0x0048

#define WEG_OFFSET_MASK	GENMASK(31, 16)
#define BIT_OFFSET_MASK	GENMASK(15, 8)
#define STAT_BIT_OFFSET_MASK	GENMASK(7, 0)

#define to_weset_data(x)	containew_of(x, stwuct intew_weset_data, wcdev)

stwuct intew_weset_soc {
	boow wegacy;
	u32 weset_ceww_count;
};

stwuct intew_weset_data {
	stwuct weset_contwowwew_dev wcdev;
	stwuct notifiew_bwock westawt_nb;
	const stwuct intew_weset_soc *soc_data;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	u32 weboot_id;
};

static const stwuct wegmap_config intew_wcu_wegmap_config = {
	.name =		"intew-weset",
	.weg_bits =	32,
	.weg_stwide =	4,
	.vaw_bits =	32,
	.fast_io =	twue,
};

/*
 * Weset status wegistew offset wewative to
 * the weset contwow wegistew(X) is X + 4
 */
static u32 id_to_weg_and_bit_offsets(stwuct intew_weset_data *data,
				     unsigned wong id, u32 *wst_weq,
				     u32 *weq_bit, u32 *stat_bit)
{
	*wst_weq = FIEWD_GET(WEG_OFFSET_MASK, id);
	*weq_bit = FIEWD_GET(BIT_OFFSET_MASK, id);

	if (data->soc_data->wegacy)
		*stat_bit = FIEWD_GET(STAT_BIT_OFFSET_MASK, id);
	ewse
		*stat_bit = *weq_bit;

	if (data->soc_data->wegacy && *wst_weq == WCU_WST_WEQ)
		wetuwn WCU_WST_STAT;
	ewse
		wetuwn *wst_weq + 0x4;
}

static int intew_set_cww_bits(stwuct intew_weset_data *data, unsigned wong id,
			      boow set)
{
	u32 wst_weq, weq_bit, wst_stat, stat_bit, vaw;
	int wet;

	wst_stat = id_to_weg_and_bit_offsets(data, id, &wst_weq,
					     &weq_bit, &stat_bit);

	vaw = set ? BIT(weq_bit) : 0;
	wet = wegmap_update_bits(data->wegmap, wst_weq,  BIT(weq_bit), vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(data->wegmap, wst_stat, vaw,
					set == !!(vaw & BIT(stat_bit)), 20,
					200);
}

static int intew_assewt_device(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct intew_weset_data *data = to_weset_data(wcdev);
	int wet;

	wet = intew_set_cww_bits(data, id, twue);
	if (wet)
		dev_eww(data->dev, "Weset assewt faiwed %d\n", wet);

	wetuwn wet;
}

static int intew_deassewt_device(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct intew_weset_data *data = to_weset_data(wcdev);
	int wet;

	wet = intew_set_cww_bits(data, id, fawse);
	if (wet)
		dev_eww(data->dev, "Weset deassewt faiwed %d\n", wet);

	wetuwn wet;
}

static int intew_weset_status(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct intew_weset_data *data = to_weset_data(wcdev);
	u32 wst_weq, weq_bit, wst_stat, stat_bit, vaw;
	int wet;

	wst_stat = id_to_weg_and_bit_offsets(data, id, &wst_weq,
					     &weq_bit, &stat_bit);
	wet = wegmap_wead(data->wegmap, wst_stat, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(stat_bit));
}

static const stwuct weset_contwow_ops intew_weset_ops = {
	.assewt =	intew_assewt_device,
	.deassewt =	intew_deassewt_device,
	.status	=	intew_weset_status,
};

static int intew_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
			     const stwuct of_phandwe_awgs *spec)
{
	stwuct intew_weset_data *data = to_weset_data(wcdev);
	u32 id;

	if (spec->awgs[1] > 31)
		wetuwn -EINVAW;

	id = FIEWD_PWEP(WEG_OFFSET_MASK, spec->awgs[0]);
	id |= FIEWD_PWEP(BIT_OFFSET_MASK, spec->awgs[1]);

	if (data->soc_data->wegacy) {
		if (spec->awgs[2] > 31)
			wetuwn -EINVAW;

		id |= FIEWD_PWEP(STAT_BIT_OFFSET_MASK, spec->awgs[2]);
	}

	wetuwn id;
}

static int intew_weset_westawt_handwew(stwuct notifiew_bwock *nb,
				       unsigned wong action, void *data)
{
	stwuct intew_weset_data *weset_data;

	weset_data = containew_of(nb, stwuct intew_weset_data, westawt_nb);
	intew_assewt_device(&weset_data->wcdev, weset_data->weboot_id);

	wetuwn NOTIFY_DONE;
}

static int intew_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct intew_weset_data *data;
	void __iomem *base;
	u32 wb_id[3];
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->soc_data = of_device_get_match_data(dev);
	if (!data->soc_data)
		wetuwn -ENODEV;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	data->wegmap = devm_wegmap_init_mmio(dev, base,
					     &intew_wcu_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		dev_eww(dev, "wegmap initiawization faiwed\n");
		wetuwn PTW_EWW(data->wegmap);
	}

	wet = device_pwopewty_wead_u32_awway(dev, "intew,gwobaw-weset", wb_id,
					     data->soc_data->weset_ceww_count);
	if (wet) {
		dev_eww(dev, "Faiwed to get gwobaw weset offset!\n");
		wetuwn wet;
	}

	data->dev =			dev;
	data->wcdev.of_node =		np;
	data->wcdev.ownew =		dev->dwivew->ownew;
	data->wcdev.ops	=		&intew_weset_ops;
	data->wcdev.of_xwate =		intew_weset_xwate;
	data->wcdev.of_weset_n_cewws =	data->soc_data->weset_ceww_count;
	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &data->wcdev);
	if (wet)
		wetuwn wet;

	data->weboot_id = FIEWD_PWEP(WEG_OFFSET_MASK, wb_id[0]);
	data->weboot_id |= FIEWD_PWEP(BIT_OFFSET_MASK, wb_id[1]);

	if (data->soc_data->wegacy)
		data->weboot_id |= FIEWD_PWEP(STAT_BIT_OFFSET_MASK, wb_id[2]);

	data->westawt_nb.notifiew_caww =	intew_weset_westawt_handwew;
	data->westawt_nb.pwiowity =		128;
	wegistew_westawt_handwew(&data->westawt_nb);

	wetuwn 0;
}

static const stwuct intew_weset_soc xwx200_data = {
	.wegacy =		twue,
	.weset_ceww_count =	3,
};

static const stwuct intew_weset_soc wgm_data = {
	.wegacy =		fawse,
	.weset_ceww_count =	2,
};

static const stwuct of_device_id intew_weset_match[] = {
	{ .compatibwe = "intew,wcu-wgm", .data = &wgm_data },
	{ .compatibwe = "intew,wcu-xwx200", .data = &xwx200_data },
	{}
};

static stwuct pwatfowm_dwivew intew_weset_dwivew = {
	.pwobe = intew_weset_pwobe,
	.dwivew = {
		.name = "intew-weset",
		.of_match_tabwe = intew_weset_match,
	},
};

static int __init intew_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&intew_weset_dwivew);
}

/*
 * WCU is system cowe entity which is in Awways On Domain whose cwocks
 * ow wesouwce initiawization happens in system cowe initiawization.
 * Awso, it is wequiwed fow most of the pwatfowm ow awchitectuwe
 * specific devices to pewfowm weset opewation as pawt of initiawization.
 * So pewfowm WCU as post cowe initiawization.
 */
postcowe_initcaww(intew_weset_init);
