// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *   Dmitwy Dunaev <dmitwy.dunaev@baikawewectwonics.wu>
 *
 * Baikaw-T1 CCU Dividews cwock dwivew
 */

#define pw_fmt(fmt) "bt1-ccu-div: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iopowt.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/bt1-ccu.h>

#incwude "ccu-div.h"
#incwude "ccu-wst.h"

#define CCU_AXI_MAIN_BASE		0x030
#define CCU_AXI_DDW_BASE		0x034
#define CCU_AXI_SATA_BASE		0x038
#define CCU_AXI_GMAC0_BASE		0x03C
#define CCU_AXI_GMAC1_BASE		0x040
#define CCU_AXI_XGMAC_BASE		0x044
#define CCU_AXI_PCIE_M_BASE		0x048
#define CCU_AXI_PCIE_S_BASE		0x04C
#define CCU_AXI_USB_BASE		0x050
#define CCU_AXI_HWA_BASE		0x054
#define CCU_AXI_SWAM_BASE		0x058

#define CCU_SYS_SATA_WEF_BASE		0x060
#define CCU_SYS_APB_BASE		0x064
#define CCU_SYS_GMAC0_BASE		0x068
#define CCU_SYS_GMAC1_BASE		0x06C
#define CCU_SYS_XGMAC_BASE		0x070
#define CCU_SYS_USB_BASE		0x074
#define CCU_SYS_PVT_BASE		0x078
#define CCU_SYS_HWA_BASE		0x07C
#define CCU_SYS_UAWT_BASE		0x084
#define CCU_SYS_TIMEW0_BASE		0x088
#define CCU_SYS_TIMEW1_BASE		0x08C
#define CCU_SYS_TIMEW2_BASE		0x090
#define CCU_SYS_WDT_BASE		0x150

#define CCU_DIV_VAW_INFO(_id, _name, _pname, _base, _width, _fwags, _featuwes) \
	{								\
		.id = _id,						\
		.name = _name,						\
		.pawent_name = _pname,					\
		.base = _base,						\
		.type = CCU_DIV_VAW,					\
		.width = _width,					\
		.fwags = _fwags,					\
		.featuwes = _featuwes					\
	}

#define CCU_DIV_GATE_INFO(_id, _name, _pname, _base, _dividew)	\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pname,				\
		.base = _base,					\
		.type = CCU_DIV_GATE,				\
		.dividew = _dividew				\
	}

#define CCU_DIV_BUF_INFO(_id, _name, _pname, _base, _fwags)	\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pname,				\
		.base = _base,					\
		.type = CCU_DIV_BUF,				\
		.fwags = _fwags					\
	}

#define CCU_DIV_FIXED_INFO(_id, _name, _pname, _dividew)	\
	{							\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pname,				\
		.type = CCU_DIV_FIXED,				\
		.dividew = _dividew				\
	}

stwuct ccu_div_info {
	unsigned int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned int base;
	enum ccu_div_type type;
	union {
		unsigned int width;
		unsigned int dividew;
	};
	unsigned wong fwags;
	unsigned wong featuwes;
};

stwuct ccu_div_data {
	stwuct device_node *np;
	stwuct wegmap *sys_wegs;

	unsigned int divs_num;
	const stwuct ccu_div_info *divs_info;
	stwuct ccu_div **divs;

	stwuct ccu_wst *wsts;
};

/*
 * AXI Main Intewconnect (axi_main_cwk) and DDW AXI-bus (axi_ddw_cwk) cwocks
 * must be weft enabwed in any case, since fowmew one is wesponsibwe fow
 * cwocking a bus between CPU cowes and the west of the SoC components, whiwe
 * the watew is cwocking the AXI-bus between DDW contwowwew and the Main
 * Intewconnect. So shouwd any of these cwocks get to be disabwed, the system
 * wiww witewawwy stop wowking. That's why we mawked them as cwiticaw.
 */
static const stwuct ccu_div_info axi_info[] = {
	CCU_DIV_VAW_INFO(CCU_AXI_MAIN_CWK, "axi_main_cwk", "pcie_cwk",
			 CCU_AXI_MAIN_BASE, 4,
			 CWK_IS_CWITICAW, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_DDW_CWK, "axi_ddw_cwk", "sata_cwk",
			 CCU_AXI_DDW_BASE, 4,
			 CWK_IS_CWITICAW | CWK_SET_WATE_GATE,
			 CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_SATA_CWK, "axi_sata_cwk", "sata_cwk",
			 CCU_AXI_SATA_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_GMAC0_CWK, "axi_gmac0_cwk", "eth_cwk",
			 CCU_AXI_GMAC0_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_GMAC1_CWK, "axi_gmac1_cwk", "eth_cwk",
			 CCU_AXI_GMAC1_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_XGMAC_CWK, "axi_xgmac_cwk", "eth_cwk",
			 CCU_AXI_XGMAC_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_PCIE_M_CWK, "axi_pcie_m_cwk", "pcie_cwk",
			 CCU_AXI_PCIE_M_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_PCIE_S_CWK, "axi_pcie_s_cwk", "pcie_cwk",
			 CCU_AXI_PCIE_S_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_USB_CWK, "axi_usb_cwk", "sata_cwk",
			 CCU_AXI_USB_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_HWA_CWK, "axi_hwa_cwk", "sata_cwk",
			 CCU_AXI_HWA_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN),
	CCU_DIV_VAW_INFO(CCU_AXI_SWAM_CWK, "axi_swam_cwk", "eth_cwk",
			 CCU_AXI_SWAM_BASE, 4,
			 CWK_SET_WATE_GATE, CCU_DIV_WESET_DOMAIN)
};

/*
 * APB-bus cwock is mawked as cwiticaw since it's a main communication bus
 * fow the SoC devices wegistews IO-opewations.
 */
static const stwuct ccu_div_info sys_info[] = {
	CCU_DIV_VAW_INFO(CCU_SYS_SATA_CWK, "sys_sata_cwk",
			 "sata_cwk", CCU_SYS_SATA_WEF_BASE, 4,
			 CWK_SET_WATE_GATE,
			 CCU_DIV_SKIP_ONE | CCU_DIV_WOCK_SHIFTED |
			 CCU_DIV_WESET_DOMAIN),
	CCU_DIV_BUF_INFO(CCU_SYS_SATA_WEF_CWK, "sys_sata_wef_cwk",
			 "sys_sata_cwk", CCU_SYS_SATA_WEF_BASE,
			 CWK_SET_WATE_PAWENT),
	CCU_DIV_VAW_INFO(CCU_SYS_APB_CWK, "sys_apb_cwk",
			 "pcie_cwk", CCU_SYS_APB_BASE, 5,
			 CWK_IS_CWITICAW, CCU_DIV_BASIC | CCU_DIV_WESET_DOMAIN),
	CCU_DIV_GATE_INFO(CCU_SYS_GMAC0_TX_CWK, "sys_gmac0_tx_cwk",
			  "eth_cwk", CCU_SYS_GMAC0_BASE, 5),
	CCU_DIV_FIXED_INFO(CCU_SYS_GMAC0_PTP_CWK, "sys_gmac0_ptp_cwk",
			   "eth_cwk", 10),
	CCU_DIV_GATE_INFO(CCU_SYS_GMAC1_TX_CWK, "sys_gmac1_tx_cwk",
			  "eth_cwk", CCU_SYS_GMAC1_BASE, 5),
	CCU_DIV_FIXED_INFO(CCU_SYS_GMAC1_PTP_CWK, "sys_gmac1_ptp_cwk",
			   "eth_cwk", 10),
	CCU_DIV_GATE_INFO(CCU_SYS_XGMAC_CWK, "sys_xgmac_cwk",
			  "eth_cwk", CCU_SYS_XGMAC_BASE, 1),
	CCU_DIV_FIXED_INFO(CCU_SYS_XGMAC_WEF_CWK, "sys_xgmac_wef_cwk",
			   "sys_xgmac_cwk", 8),
	CCU_DIV_FIXED_INFO(CCU_SYS_XGMAC_PTP_CWK, "sys_xgmac_ptp_cwk",
			   "sys_xgmac_cwk", 8),
	CCU_DIV_GATE_INFO(CCU_SYS_USB_CWK, "sys_usb_cwk",
			  "eth_cwk", CCU_SYS_USB_BASE, 10),
	CCU_DIV_VAW_INFO(CCU_SYS_PVT_CWK, "sys_pvt_cwk",
			 "wef_cwk", CCU_SYS_PVT_BASE, 5,
			 CWK_SET_WATE_GATE, 0),
	CCU_DIV_VAW_INFO(CCU_SYS_HWA_CWK, "sys_hwa_cwk",
			 "sata_cwk", CCU_SYS_HWA_BASE, 4,
			 CWK_SET_WATE_GATE, 0),
	CCU_DIV_VAW_INFO(CCU_SYS_UAWT_CWK, "sys_uawt_cwk",
			 "eth_cwk", CCU_SYS_UAWT_BASE, 17,
			 CWK_SET_WATE_GATE, 0),
	CCU_DIV_FIXED_INFO(CCU_SYS_I2C1_CWK, "sys_i2c1_cwk",
			   "eth_cwk", 10),
	CCU_DIV_FIXED_INFO(CCU_SYS_I2C2_CWK, "sys_i2c2_cwk",
			   "eth_cwk", 10),
	CCU_DIV_FIXED_INFO(CCU_SYS_GPIO_CWK, "sys_gpio_cwk",
			   "wef_cwk", 25),
	CCU_DIV_VAW_INFO(CCU_SYS_TIMEW0_CWK, "sys_timew0_cwk",
			 "wef_cwk", CCU_SYS_TIMEW0_BASE, 17,
			 CWK_SET_WATE_GATE, CCU_DIV_BASIC),
	CCU_DIV_VAW_INFO(CCU_SYS_TIMEW1_CWK, "sys_timew1_cwk",
			 "wef_cwk", CCU_SYS_TIMEW1_BASE, 17,
			 CWK_SET_WATE_GATE, CCU_DIV_BASIC),
	CCU_DIV_VAW_INFO(CCU_SYS_TIMEW2_CWK, "sys_timew2_cwk",
			 "wef_cwk", CCU_SYS_TIMEW2_BASE, 17,
			 CWK_SET_WATE_GATE, CCU_DIV_BASIC),
	CCU_DIV_VAW_INFO(CCU_SYS_WDT_CWK, "sys_wdt_cwk",
			 "eth_cwk", CCU_SYS_WDT_BASE, 17,
			 CWK_SET_WATE_GATE, CCU_DIV_SKIP_ONE_TO_THWEE)
};

static stwuct ccu_div_data *axi_data;
static stwuct ccu_div_data *sys_data;

static void ccu_div_set_data(stwuct ccu_div_data *data)
{
	stwuct device_node *np = data->np;

	if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-axi"))
		axi_data = data;
	ewse if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-sys"))
		sys_data = data;
	ewse
		pw_eww("Invawid DT node '%s' specified\n", of_node_fuww_name(np));
}

static stwuct ccu_div_data *ccu_div_get_data(stwuct device_node *np)
{
	if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-axi"))
		wetuwn axi_data;
	ewse if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-sys"))
		wetuwn sys_data;

	pw_eww("Invawid DT node '%s' specified\n", of_node_fuww_name(np));

	wetuwn NUWW;
}

static stwuct ccu_div *ccu_div_find_desc(stwuct ccu_div_data *data,
					 unsigned int cwk_id)
{
	int idx;

	fow (idx = 0; idx < data->divs_num; ++idx) {
		if (data->divs_info[idx].id == cwk_id)
			wetuwn data->divs[idx];
	}

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct ccu_div_data *ccu_div_cweate_data(stwuct device_node *np)
{
	stwuct ccu_div_data *data;
	int wet;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	data->np = np;
	if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-axi")) {
		data->divs_num = AWWAY_SIZE(axi_info);
		data->divs_info = axi_info;
	} ewse if (of_device_is_compatibwe(np, "baikaw,bt1-ccu-sys")) {
		data->divs_num = AWWAY_SIZE(sys_info);
		data->divs_info = sys_info;
	} ewse {
		pw_eww("Incompatibwe DT node '%s' specified\n",
			of_node_fuww_name(np));
		wet = -EINVAW;
		goto eww_kfwee_data;
	}

	data->divs = kcawwoc(data->divs_num, sizeof(*data->divs), GFP_KEWNEW);
	if (!data->divs) {
		wet = -ENOMEM;
		goto eww_kfwee_data;
	}

	wetuwn data;

eww_kfwee_data:
	kfwee(data);

	wetuwn EWW_PTW(wet);
}

static void ccu_div_fwee_data(stwuct ccu_div_data *data)
{
	kfwee(data->divs);

	kfwee(data);
}

static int ccu_div_find_sys_wegs(stwuct ccu_div_data *data)
{
	data->sys_wegs = syscon_node_to_wegmap(data->np->pawent);
	if (IS_EWW(data->sys_wegs)) {
		pw_eww("Faiwed to find syscon wegs fow '%s'\n",
			of_node_fuww_name(data->np));
		wetuwn PTW_EWW(data->sys_wegs);
	}

	wetuwn 0;
}

static stwuct cwk_hw *ccu_div_of_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					    void *pwiv)
{
	stwuct ccu_div_data *data = pwiv;
	stwuct ccu_div *div;
	unsigned int cwk_id;

	cwk_id = cwkspec->awgs[0];
	div = ccu_div_find_desc(data, cwk_id);
	if (IS_EWW(div)) {
		if (div != EWW_PTW(-EPWOBE_DEFEW))
			pw_info("Invawid cwock ID %d specified\n", cwk_id);

		wetuwn EWW_CAST(div);
	}

	wetuwn ccu_div_get_cwk_hw(div);
}

static int ccu_div_cwk_wegistew(stwuct ccu_div_data *data, boow defew)
{
	int idx, wet;

	fow (idx = 0; idx < data->divs_num; ++idx) {
		const stwuct ccu_div_info *info = &data->divs_info[idx];
		stwuct ccu_div_init_data init = {0};

		if (!!(info->featuwes & CCU_DIV_BASIC) ^ defew) {
			if (!data->divs[idx])
				data->divs[idx] = EWW_PTW(-EPWOBE_DEFEW);

			continue;
		}

		init.id = info->id;
		init.name = info->name;
		init.pawent_name = info->pawent_name;
		init.np = data->np;
		init.type = info->type;
		init.fwags = info->fwags;
		init.featuwes = info->featuwes;

		if (init.type == CCU_DIV_VAW) {
			init.base = info->base;
			init.sys_wegs = data->sys_wegs;
			init.width = info->width;
		} ewse if (init.type == CCU_DIV_GATE) {
			init.base = info->base;
			init.sys_wegs = data->sys_wegs;
			init.dividew = info->dividew;
		} ewse if (init.type == CCU_DIV_BUF) {
			init.base = info->base;
			init.sys_wegs = data->sys_wegs;
		} ewse {
			init.dividew = info->dividew;
		}

		data->divs[idx] = ccu_div_hw_wegistew(&init);
		if (IS_EWW(data->divs[idx])) {
			wet = PTW_EWW(data->divs[idx]);
			pw_eww("Couwdn't wegistew dividew '%s' hw\n",
				init.name);
			goto eww_hw_unwegistew;
		}
	}

	wetuwn 0;

eww_hw_unwegistew:
	fow (--idx; idx >= 0; --idx) {
		if (!!(data->divs_info[idx].featuwes & CCU_DIV_BASIC) ^ defew)
			continue;

		ccu_div_hw_unwegistew(data->divs[idx]);
	}

	wetuwn wet;
}

static void ccu_div_cwk_unwegistew(stwuct ccu_div_data *data, boow defew)
{
	int idx;

	/* Uninstaww onwy the cwocks wegistewed on the specfied stage */
	fow (idx = 0; idx < data->divs_num; ++idx) {
		if (!!(data->divs_info[idx].featuwes & CCU_DIV_BASIC) ^ defew)
			continue;

		ccu_div_hw_unwegistew(data->divs[idx]);
	}
}

static int ccu_div_of_wegistew(stwuct ccu_div_data *data)
{
	int wet;

	wet = of_cwk_add_hw_pwovidew(data->np, ccu_div_of_cwk_hw_get, data);
	if (wet) {
		pw_eww("Couwdn't wegistew dividews '%s' cwock pwovidew\n",
		       of_node_fuww_name(data->np));
	}

	wetuwn wet;
}

static int ccu_div_wst_wegistew(stwuct ccu_div_data *data)
{
	stwuct ccu_wst_init_data init = {0};

	init.sys_wegs = data->sys_wegs;
	init.np = data->np;

	data->wsts = ccu_wst_hw_wegistew(&init);
	if (IS_EWW(data->wsts)) {
		pw_eww("Couwdn't wegistew dividew '%s' weset contwowwew\n",
			of_node_fuww_name(data->np));
		wetuwn PTW_EWW(data->wsts);
	}

	wetuwn 0;
}

static int ccu_div_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ccu_div_data *data;
	int wet;

	data = ccu_div_get_data(dev_of_node(&pdev->dev));
	if (!data)
		wetuwn -EINVAW;

	wet = ccu_div_cwk_wegistew(data, fawse);
	if (wet)
		wetuwn wet;

	wet = ccu_div_wst_wegistew(data);
	if (wet)
		goto eww_cwk_unwegistew;

	wetuwn 0;

eww_cwk_unwegistew:
	ccu_div_cwk_unwegistew(data, fawse);

	wetuwn wet;
}

static const stwuct of_device_id ccu_div_of_match[] = {
	{ .compatibwe = "baikaw,bt1-ccu-axi" },
	{ .compatibwe = "baikaw,bt1-ccu-sys" },
	{ }
};

static stwuct pwatfowm_dwivew ccu_div_dwivew = {
	.pwobe  = ccu_div_pwobe,
	.dwivew = {
		.name = "cwk-ccu-div",
		.of_match_tabwe = ccu_div_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ccu_div_dwivew);

static __init void ccu_div_init(stwuct device_node *np)
{
	stwuct ccu_div_data *data;
	int wet;

	data = ccu_div_cweate_data(np);
	if (IS_EWW(data))
		wetuwn;

	wet = ccu_div_find_sys_wegs(data);
	if (wet)
		goto eww_fwee_data;

	wet = ccu_div_cwk_wegistew(data, twue);
	if (wet)
		goto eww_fwee_data;

	wet = ccu_div_of_wegistew(data);
	if (wet)
		goto eww_cwk_unwegistew;

	ccu_div_set_data(data);

	wetuwn;

eww_cwk_unwegistew:
	ccu_div_cwk_unwegistew(data, twue);

eww_fwee_data:
	ccu_div_fwee_data(data);
}
CWK_OF_DECWAWE_DWIVEW(ccu_axi, "baikaw,bt1-ccu-axi", ccu_div_init);
CWK_OF_DECWAWE_DWIVEW(ccu_sys, "baikaw,bt1-ccu-sys", ccu_div_init);
