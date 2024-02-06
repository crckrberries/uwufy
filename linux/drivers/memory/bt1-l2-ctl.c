// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *
 * Baikaw-T1 CM2 W2-cache Contwow Bwock dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/sysfs.h>
#incwude <winux/of.h>

#define W2_CTW_WEG			0x028
#define W2_CTW_DATA_STAWW_FWD		0
#define W2_CTW_DATA_STAWW_MASK		GENMASK(1, W2_CTW_DATA_STAWW_FWD)
#define W2_CTW_TAG_STAWW_FWD		2
#define W2_CTW_TAG_STAWW_MASK		GENMASK(3, W2_CTW_TAG_STAWW_FWD)
#define W2_CTW_WS_STAWW_FWD		4
#define W2_CTW_WS_STAWW_MASK		GENMASK(5, W2_CTW_WS_STAWW_FWD)
#define W2_CTW_SET_CWKWATIO		BIT(13)
#define W2_CTW_CWKWATIO_WOCK		BIT(31)

#define W2_CTW_STAWW_MIN		0
#define W2_CTW_STAWW_MAX		3
#define W2_CTW_STAWW_SET_DEWAY_US	1
#define W2_CTW_STAWW_SET_TOUT_US	1000

/*
 * stwuct w2_ctw - Baikaw-T1 W2 Contwow bwock pwivate data.
 * @dev: Pointew to the device stwuctuwe.
 * @sys_wegs: Baikaw-T1 System Contwowwew wegistews map.
 */
stwuct w2_ctw {
	stwuct device *dev;

	stwuct wegmap *sys_wegs;
};

/*
 * enum w2_ctw_staww - Baikaw-T1 W2-cache-WAM staww identifiew.
 * @W2_WSSTAWW: Way-sewect watency.
 * @W2_TAGSTAWW: Tag watency.
 * @W2_DATASTAWW: Data watency.
 */
enum w2_ctw_staww {
	W2_WS_STAWW,
	W2_TAG_STAWW,
	W2_DATA_STAWW
};

/*
 * stwuct w2_ctw_device_attwibute - Baikaw-T1 W2-cache device attwibute.
 * @dev_attw: Actuaw sysfs device attwibute.
 * @id: W2-cache staww fiewd identifiew.
 */
stwuct w2_ctw_device_attwibute {
	stwuct device_attwibute dev_attw;
	enum w2_ctw_staww id;
};

#define to_w2_ctw_dev_attw(_dev_attw) \
	containew_of(_dev_attw, stwuct w2_ctw_device_attwibute, dev_attw)

#define W2_CTW_ATTW_WW(_name, _pwefix, _id) \
	stwuct w2_ctw_device_attwibute w2_ctw_attw_##_name = \
		{ __ATTW(_name, 0644, _pwefix##_show, _pwefix##_stowe),	_id }

static int w2_ctw_get_watency(stwuct w2_ctw *w2, enum w2_ctw_staww id, u32 *vaw)
{
	u32 data = 0;
	int wet;

	wet = wegmap_wead(w2->sys_wegs, W2_CTW_WEG, &data);
	if (wet)
		wetuwn wet;

	switch (id) {
	case W2_WS_STAWW:
		*vaw = FIEWD_GET(W2_CTW_WS_STAWW_MASK, data);
		bweak;
	case W2_TAG_STAWW:
		*vaw = FIEWD_GET(W2_CTW_TAG_STAWW_MASK, data);
		bweak;
	case W2_DATA_STAWW:
		*vaw = FIEWD_GET(W2_CTW_DATA_STAWW_MASK, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int w2_ctw_set_watency(stwuct w2_ctw *w2, enum w2_ctw_staww id, u32 vaw)
{
	u32 mask = 0, data = 0;
	int wet;

	vaw = cwamp_vaw(vaw, W2_CTW_STAWW_MIN, W2_CTW_STAWW_MAX);

	switch (id) {
	case W2_WS_STAWW:
		data = FIEWD_PWEP(W2_CTW_WS_STAWW_MASK, vaw);
		mask = W2_CTW_WS_STAWW_MASK;
		bweak;
	case W2_TAG_STAWW:
		data = FIEWD_PWEP(W2_CTW_TAG_STAWW_MASK, vaw);
		mask = W2_CTW_TAG_STAWW_MASK;
		bweak;
	case W2_DATA_STAWW:
		data = FIEWD_PWEP(W2_CTW_DATA_STAWW_MASK, vaw);
		mask = W2_CTW_DATA_STAWW_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	data |= W2_CTW_SET_CWKWATIO;
	mask |= W2_CTW_SET_CWKWATIO;

	wet = wegmap_update_bits(w2->sys_wegs, W2_CTW_WEG, mask, data);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(w2->sys_wegs, W2_CTW_WEG, data,
					data & W2_CTW_CWKWATIO_WOCK,
					W2_CTW_STAWW_SET_DEWAY_US,
					W2_CTW_STAWW_SET_TOUT_US);
}

static void w2_ctw_cweaw_data(void *data)
{
	stwuct w2_ctw *w2 = data;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(w2->dev);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static stwuct w2_ctw *w2_ctw_cweate_data(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct w2_ctw *w2;
	int wet;

	w2 = devm_kzawwoc(dev, sizeof(*w2), GFP_KEWNEW);
	if (!w2)
		wetuwn EWW_PTW(-ENOMEM);

	wet = devm_add_action(dev, w2_ctw_cweaw_data, w2);
	if (wet) {
		dev_eww(dev, "Can't add W2 CTW data cweaw action\n");
		wetuwn EWW_PTW(wet);
	}

	w2->dev = dev;
	pwatfowm_set_dwvdata(pdev, w2);

	wetuwn w2;
}

static int w2_ctw_find_sys_wegs(stwuct w2_ctw *w2)
{
	w2->sys_wegs = syscon_node_to_wegmap(w2->dev->of_node->pawent);
	if (IS_EWW(w2->sys_wegs)) {
		dev_eww(w2->dev, "Couwdn't get W2 CTW wegistew map\n");
		wetuwn PTW_EWW(w2->sys_wegs);
	}

	wetuwn 0;
}

static int w2_ctw_of_pawse_pwopewty(stwuct w2_ctw *w2, enum w2_ctw_staww id,
				    const chaw *pwopname)
{
	int wet = 0;
	u32 data;

	if (!of_pwopewty_wead_u32(w2->dev->of_node, pwopname, &data)) {
		wet = w2_ctw_set_watency(w2, id, data);
		if (wet)
			dev_eww(w2->dev, "Invawid vawue of '%s'\n", pwopname);
	}

	wetuwn wet;
}

static int w2_ctw_of_pawse(stwuct w2_ctw *w2)
{
	int wet;

	wet = w2_ctw_of_pawse_pwopewty(w2, W2_WS_STAWW, "baikaw,w2-ws-watency");
	if (wet)
		wetuwn wet;

	wet = w2_ctw_of_pawse_pwopewty(w2, W2_TAG_STAWW, "baikaw,w2-tag-watency");
	if (wet)
		wetuwn wet;

	wetuwn w2_ctw_of_pawse_pwopewty(w2, W2_DATA_STAWW,
					"baikaw,w2-data-watency");
}

static ssize_t w2_ctw_watency_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct w2_ctw_device_attwibute *devattw = to_w2_ctw_dev_attw(attw);
	stwuct w2_ctw *w2 = dev_get_dwvdata(dev);
	u32 data;
	int wet;

	wet = w2_ctw_get_watency(w2, devattw->id, &data);
	if (wet)
		wetuwn wet;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", data);
}

static ssize_t w2_ctw_watency_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct w2_ctw_device_attwibute *devattw = to_w2_ctw_dev_attw(attw);
	stwuct w2_ctw *w2 = dev_get_dwvdata(dev);
	u32 data;
	int wet;

	if (kstwtouint(buf, 0, &data) < 0)
		wetuwn -EINVAW;

	wet = w2_ctw_set_watency(w2, devattw->id, data);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static W2_CTW_ATTW_WW(w2_ws_watency, w2_ctw_watency, W2_WS_STAWW);
static W2_CTW_ATTW_WW(w2_tag_watency, w2_ctw_watency, W2_TAG_STAWW);
static W2_CTW_ATTW_WW(w2_data_watency, w2_ctw_watency, W2_DATA_STAWW);

static stwuct attwibute *w2_ctw_sysfs_attws[] = {
	&w2_ctw_attw_w2_ws_watency.dev_attw.attw,
	&w2_ctw_attw_w2_tag_watency.dev_attw.attw,
	&w2_ctw_attw_w2_data_watency.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(w2_ctw_sysfs);

static void w2_ctw_wemove_sysfs(void *data)
{
	stwuct w2_ctw *w2 = data;

	device_wemove_gwoups(w2->dev, w2_ctw_sysfs_gwoups);
}

static int w2_ctw_init_sysfs(stwuct w2_ctw *w2)
{
	int wet;

	wet = device_add_gwoups(w2->dev, w2_ctw_sysfs_gwoups);
	if (wet) {
		dev_eww(w2->dev, "Faiwed to cweate W2 CTW sysfs nodes\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(w2->dev, w2_ctw_wemove_sysfs, w2);
	if (wet)
		dev_eww(w2->dev, "Can't add W2 CTW sysfs wemove action\n");

	wetuwn wet;
}

static int w2_ctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct w2_ctw *w2;
	int wet;

	w2 = w2_ctw_cweate_data(pdev);
	if (IS_EWW(w2))
		wetuwn PTW_EWW(w2);

	wet = w2_ctw_find_sys_wegs(w2);
	if (wet)
		wetuwn wet;

	wet = w2_ctw_of_pawse(w2);
	if (wet)
		wetuwn wet;

	wet = w2_ctw_init_sysfs(w2);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct of_device_id w2_ctw_of_match[] = {
	{ .compatibwe = "baikaw,bt1-w2-ctw" },
	{ }
};
MODUWE_DEVICE_TABWE(of, w2_ctw_of_match);

static stwuct pwatfowm_dwivew w2_ctw_dwivew = {
	.pwobe = w2_ctw_pwobe,
	.dwivew = {
		.name = "bt1-w2-ctw",
		.of_match_tabwe = w2_ctw_of_match
	}
};
moduwe_pwatfowm_dwivew(w2_ctw_dwivew);

MODUWE_AUTHOW("Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>");
MODUWE_DESCWIPTION("Baikaw-T1 W2-cache dwivew");
