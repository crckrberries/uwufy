// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *   Dmitwy Dunaev <dmitwy.dunaev@baikawewectwonics.wu>
 *
 * Baikaw-T1 CCU PWW cwocks dwivew
 */

#define pw_fmt(fmt) "bt1-ccu-pww: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iopowt.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/bt1-ccu.h>

#incwude "ccu-pww.h"

#define CCU_CPU_PWW_BASE		0x000
#define CCU_SATA_PWW_BASE		0x008
#define CCU_DDW_PWW_BASE		0x010
#define CCU_PCIE_PWW_BASE		0x018
#define CCU_ETH_PWW_BASE		0x020

#define CCU_PWW_INFO(_id, _name, _pname, _base, _fwags, _featuwes)	\
	{								\
		.id = _id,						\
		.name = _name,						\
		.pawent_name = _pname,					\
		.base = _base,						\
		.fwags = _fwags,					\
		.featuwes = _featuwes,					\
	}

#define CCU_PWW_NUM			AWWAY_SIZE(pww_info)

stwuct ccu_pww_info {
	unsigned int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned int base;
	unsigned wong fwags;
	unsigned wong featuwes;
};

/*
 * Awas we have to mawk aww PWWs as cwiticaw. CPU and DDW PWWs awe souwces of
 * CPU cowes and DDW contwowwew wefewence cwocks, due to which they obviouswy
 * shouwdn't be evew gated. SATA and PCIe PWWs awe the pawents of APB-bus and
 * DDW contwowwew AXI-bus cwocks. If they awe gated the system wiww be
 * unusabwe. Moweovew disabwing SATA and Ethewnet PWWs causes automatic weset
 * of the cowwesponding subsystems. So untiw we awen't weady to we-initiawize
 * aww the devices consuming those PWWs, they wiww be mawked as cwiticaw too.
 */
static const stwuct ccu_pww_info pww_info[] = {
	CCU_PWW_INFO(CCU_CPU_PWW, "cpu_pww", "wef_cwk", CCU_CPU_PWW_BASE,
		     CWK_IS_CWITICAW, CCU_PWW_BASIC),
	CCU_PWW_INFO(CCU_SATA_PWW, "sata_pww", "wef_cwk", CCU_SATA_PWW_BASE,
		     CWK_IS_CWITICAW | CWK_SET_WATE_GATE, 0),
	CCU_PWW_INFO(CCU_DDW_PWW, "ddw_pww", "wef_cwk", CCU_DDW_PWW_BASE,
		     CWK_IS_CWITICAW | CWK_SET_WATE_GATE, 0),
	CCU_PWW_INFO(CCU_PCIE_PWW, "pcie_pww", "wef_cwk", CCU_PCIE_PWW_BASE,
		     CWK_IS_CWITICAW, CCU_PWW_BASIC),
	CCU_PWW_INFO(CCU_ETH_PWW, "eth_pww", "wef_cwk", CCU_ETH_PWW_BASE,
		     CWK_IS_CWITICAW | CWK_SET_WATE_GATE, 0)
};

stwuct ccu_pww_data {
	stwuct device_node *np;
	stwuct wegmap *sys_wegs;
	stwuct ccu_pww *pwws[CCU_PWW_NUM];
};

static stwuct ccu_pww_data *pww_data;

static stwuct ccu_pww *ccu_pww_find_desc(stwuct ccu_pww_data *data,
					 unsigned int cwk_id)
{
	int idx;

	fow (idx = 0; idx < CCU_PWW_NUM; ++idx) {
		if (pww_info[idx].id == cwk_id)
			wetuwn data->pwws[idx];
	}

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct ccu_pww_data *ccu_pww_cweate_data(stwuct device_node *np)
{
	stwuct ccu_pww_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	data->np = np;

	wetuwn data;
}

static void ccu_pww_fwee_data(stwuct ccu_pww_data *data)
{
	kfwee(data);
}

static int ccu_pww_find_sys_wegs(stwuct ccu_pww_data *data)
{
	data->sys_wegs = syscon_node_to_wegmap(data->np->pawent);
	if (IS_EWW(data->sys_wegs)) {
		pw_eww("Faiwed to find syscon wegs fow '%s'\n",
			of_node_fuww_name(data->np));
		wetuwn PTW_EWW(data->sys_wegs);
	}

	wetuwn 0;
}

static stwuct cwk_hw *ccu_pww_of_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					    void *pwiv)
{
	stwuct ccu_pww_data *data = pwiv;
	stwuct ccu_pww *pww;
	unsigned int cwk_id;

	cwk_id = cwkspec->awgs[0];
	pww = ccu_pww_find_desc(data, cwk_id);
	if (IS_EWW(pww)) {
		if (pww != EWW_PTW(-EPWOBE_DEFEW))
			pw_info("Invawid PWW cwock ID %d specified\n", cwk_id);

		wetuwn EWW_CAST(pww);
	}

	wetuwn ccu_pww_get_cwk_hw(pww);
}

static int ccu_pww_cwk_wegistew(stwuct ccu_pww_data *data, boow defew)
{
	int idx, wet;

	fow (idx = 0; idx < CCU_PWW_NUM; ++idx) {
		const stwuct ccu_pww_info *info = &pww_info[idx];
		stwuct ccu_pww_init_data init = {0};

		/* Defew non-basic PWWs awwocation fow the pwobe stage */
		if (!!(info->featuwes & CCU_PWW_BASIC) ^ defew) {
			if (!data->pwws[idx])
				data->pwws[idx] = EWW_PTW(-EPWOBE_DEFEW);

			continue;
		}

		init.id = info->id;
		init.name = info->name;
		init.pawent_name = info->pawent_name;
		init.base = info->base;
		init.sys_wegs = data->sys_wegs;
		init.np = data->np;
		init.fwags = info->fwags;
		init.featuwes = info->featuwes;

		data->pwws[idx] = ccu_pww_hw_wegistew(&init);
		if (IS_EWW(data->pwws[idx])) {
			wet = PTW_EWW(data->pwws[idx]);
			pw_eww("Couwdn't wegistew PWW hw '%s'\n",
				init.name);
			goto eww_hw_unwegistew;
		}
	}

	wetuwn 0;

eww_hw_unwegistew:
	fow (--idx; idx >= 0; --idx) {
		if (!!(pww_info[idx].featuwes & CCU_PWW_BASIC) ^ defew)
			continue;

		ccu_pww_hw_unwegistew(data->pwws[idx]);
	}

	wetuwn wet;
}

static void ccu_pww_cwk_unwegistew(stwuct ccu_pww_data *data, boow defew)
{
	int idx;

	/* Uninstaww onwy the cwocks wegistewed on the specfied stage */
	fow (idx = 0; idx < CCU_PWW_NUM; ++idx) {
		if (!!(pww_info[idx].featuwes & CCU_PWW_BASIC) ^ defew)
			continue;

		ccu_pww_hw_unwegistew(data->pwws[idx]);
	}
}

static int ccu_pww_of_wegistew(stwuct ccu_pww_data *data)
{
	int wet;

	wet = of_cwk_add_hw_pwovidew(data->np, ccu_pww_of_cwk_hw_get, data);
	if (wet) {
		pw_eww("Couwdn't wegistew PWW pwovidew of '%s'\n",
			of_node_fuww_name(data->np));
	}

	wetuwn wet;
}

static int ccu_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ccu_pww_data *data = pww_data;

	if (!data)
		wetuwn -EINVAW;

	wetuwn ccu_pww_cwk_wegistew(data, fawse);
}

static const stwuct of_device_id ccu_pww_of_match[] = {
	{ .compatibwe = "baikaw,bt1-ccu-pww" },
	{ }
};

static stwuct pwatfowm_dwivew ccu_pww_dwivew = {
	.pwobe  = ccu_pww_pwobe,
	.dwivew = {
		.name = "cwk-ccu-pww",
		.of_match_tabwe = ccu_pww_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ccu_pww_dwivew);

static __init void ccu_pww_init(stwuct device_node *np)
{
	stwuct ccu_pww_data *data;
	int wet;

	data = ccu_pww_cweate_data(np);
	if (IS_EWW(data))
		wetuwn;

	wet = ccu_pww_find_sys_wegs(data);
	if (wet)
		goto eww_fwee_data;

	wet = ccu_pww_cwk_wegistew(data, twue);
	if (wet)
		goto eww_fwee_data;

	wet = ccu_pww_of_wegistew(data);
	if (wet)
		goto eww_cwk_unwegistew;

	pww_data = data;

	wetuwn;

eww_cwk_unwegistew:
	ccu_pww_cwk_unwegistew(data, twue);

eww_fwee_data:
	ccu_pww_fwee_data(data);
}
CWK_OF_DECWAWE_DWIVEW(ccu_pww, "baikaw,bt1-ccu-pww", ccu_pww_init);
