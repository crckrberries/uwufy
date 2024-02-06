// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwc3-st.c Suppowt fow dwc3 pwatfowm devices on ST Micwoewectwonics pwatfowms
 *
 * This is a smaww dwivew fow the dwc3 to pwovide the gwue wogic
 * to configuwe the contwowwew. Tested on STi pwatfowms.
 *
 * Copywight (C) 2014 Stmicwoewectwonics
 *
 * Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 * Contwibutows: Aymen Bouattay <aymen.bouattay@st.com>
 *               Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 * Inspiwed by dwc3-omap.c and dwc3-exynos.c.
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/usb/of.h>

#incwude "cowe.h"
#incwude "io.h"

/* gwue wegistews */
#define CWKWST_CTWW		0x00
#define AUX_CWK_EN		BIT(0)
#define SW_PIPEW_WESET_N	BIT(4)
#define EXT_CFG_WESET_N		BIT(8)
/*
 * 1'b0 : The host contwowwew compwies with the xHCI wevision 0.96
 * 1'b1 : The host contwowwew compwies with the xHCI wevision 1.0
 */
#define XHCI_WEVISION		BIT(12)

#define USB2_VBUS_MNGMNT_SEW1	0x2C
/*
 * Fow aww fiewds in USB2_VBUS_MNGMNT_SEW1
 * 2’b00 : Ovewwide vawue fwom Weg 0x30 is sewected
 * 2’b01 : utmiotg_<signaw_name> fwom usb3_top is sewected
 * 2’b10 : pipew_<signaw_name> fwom PIPEW instance is sewected
 * 2’b11 : vawue is 1'b0
 */
#define USB2_VBUS_WEG30		0x0
#define USB2_VBUS_UTMIOTG	0x1
#define USB2_VBUS_PIPEW		0x2
#define USB2_VBUS_ZEWO		0x3

#define SEW_OVEWWIDE_VBUSVAWID(n)	(n << 0)
#define SEW_OVEWWIDE_POWEWPWESENT(n)	(n << 4)
#define SEW_OVEWWIDE_BVAWID(n)		(n << 8)

/* Static DWD configuwation */
#define USB3_CONTWOW_MASK		0xf77

#define USB3_DEVICE_NOT_HOST		BIT(0)
#define USB3_FOWCE_VBUSVAWID		BIT(1)
#define USB3_DEWAY_VBUSVAWID		BIT(2)
#define USB3_SEW_FOWCE_OPMODE		BIT(4)
#define USB3_FOWCE_OPMODE(n)		(n << 5)
#define USB3_SEW_FOWCE_DPPUWWDOWN2	BIT(8)
#define USB3_FOWCE_DPPUWWDOWN2		BIT(9)
#define USB3_SEW_FOWCE_DMPUWWDOWN2	BIT(10)
#define USB3_FOWCE_DMPUWWDOWN2		BIT(11)

/**
 * stwuct st_dwc3 - dwc3-st dwivew pwivate stwuctuwe
 * @dev:		device pointew
 * @gwue_base:		ioaddw fow the gwue wegistews
 * @wegmap:		wegmap pointew fow getting syscfg
 * @syscfg_weg_off:	usb syscfg contwow offset
 * @dw_mode:		dwd static host/device config
 * @wstc_pwwdn:		west contwowwew fow powewdown signaw
 * @wstc_wst:		weset contwowwew fow softweset signaw
 */

stwuct st_dwc3 {
	stwuct device *dev;
	void __iomem *gwue_base;
	stwuct wegmap *wegmap;
	int syscfg_weg_off;
	enum usb_dw_mode dw_mode;
	stwuct weset_contwow *wstc_pwwdn;
	stwuct weset_contwow *wstc_wst;
};

static inwine u32 st_dwc3_weadw(void __iomem *base, u32 offset)
{
	wetuwn weadw_wewaxed(base + offset);
}

static inwine void st_dwc3_wwitew(void __iomem *base, u32 offset, u32 vawue)
{
	wwitew_wewaxed(vawue, base + offset);
}

/**
 * st_dwc3_dwd_init: pwogwam the powt
 * @dwc3_data: dwivew pwivate stwuctuwe
 * Descwiption: this function is to pwogwam the powt as eithew host ow device
 * accowding to the static configuwation passed fwom devicetwee.
 * OTG and duaw wowe awe not yet suppowted!
 */
static int st_dwc3_dwd_init(stwuct st_dwc3 *dwc3_data)
{
	u32 vaw;
	int eww;

	eww = wegmap_wead(dwc3_data->wegmap, dwc3_data->syscfg_weg_off, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= USB3_CONTWOW_MASK;

	switch (dwc3_data->dw_mode) {
	case USB_DW_MODE_PEWIPHEWAW:

		vaw &= ~(USB3_DEWAY_VBUSVAWID
			| USB3_SEW_FOWCE_OPMODE | USB3_FOWCE_OPMODE(0x3)
			| USB3_SEW_FOWCE_DPPUWWDOWN2 | USB3_FOWCE_DPPUWWDOWN2
			| USB3_SEW_FOWCE_DMPUWWDOWN2 | USB3_FOWCE_DMPUWWDOWN2);

		/*
		 * USB3_POWT2_FOWCE_VBUSVAWID When '1' and when
		 * USB3_POWT2_DEVICE_NOT_HOST = 1, fowces VBUSVWDEXT2 input
		 * of the pico PHY to 1.
		 */

		vaw |= USB3_DEVICE_NOT_HOST | USB3_FOWCE_VBUSVAWID;
		bweak;

	case USB_DW_MODE_HOST:

		vaw &= ~(USB3_DEVICE_NOT_HOST | USB3_FOWCE_VBUSVAWID
			| USB3_SEW_FOWCE_OPMODE	| USB3_FOWCE_OPMODE(0x3)
			| USB3_SEW_FOWCE_DPPUWWDOWN2 | USB3_FOWCE_DPPUWWDOWN2
			| USB3_SEW_FOWCE_DMPUWWDOWN2 | USB3_FOWCE_DMPUWWDOWN2);

		/*
		 * USB3_DEWAY_VBUSVAWID is ANDed with USB_C_VBUSVAWID. Thus,
		 * when set to ‘0‘, it can deway the awwivaw of VBUSVAWID
		 * infowmation to VBUSVWDEXT2 input of the pico PHY.
		 * We don't want to do that so we set the bit to '1'.
		 */

		vaw |= USB3_DEWAY_VBUSVAWID;
		bweak;

	defauwt:
		dev_eww(dwc3_data->dev, "Unsuppowted mode of opewation %d\n",
			dwc3_data->dw_mode);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite(dwc3_data->wegmap, dwc3_data->syscfg_weg_off, vaw);
}

/**
 * st_dwc3_init: init the contwowwew via gwue wogic
 * @dwc3_data: dwivew pwivate stwuctuwe
 */
static void st_dwc3_init(stwuct st_dwc3 *dwc3_data)
{
	u32 weg = st_dwc3_weadw(dwc3_data->gwue_base, CWKWST_CTWW);

	weg |= AUX_CWK_EN | EXT_CFG_WESET_N | XHCI_WEVISION;
	weg &= ~SW_PIPEW_WESET_N;
	st_dwc3_wwitew(dwc3_data->gwue_base, CWKWST_CTWW, weg);

	/* configuwe mux fow vbus, powewpwesent and bvawid signaws */
	weg = st_dwc3_weadw(dwc3_data->gwue_base, USB2_VBUS_MNGMNT_SEW1);

	weg |= SEW_OVEWWIDE_VBUSVAWID(USB2_VBUS_UTMIOTG) |
		SEW_OVEWWIDE_POWEWPWESENT(USB2_VBUS_UTMIOTG) |
		SEW_OVEWWIDE_BVAWID(USB2_VBUS_UTMIOTG);

	st_dwc3_wwitew(dwc3_data->gwue_base, USB2_VBUS_MNGMNT_SEW1, weg);

	weg = st_dwc3_weadw(dwc3_data->gwue_base, CWKWST_CTWW);
	weg |= SW_PIPEW_WESET_N;
	st_dwc3_wwitew(dwc3_data->gwue_base, CWKWST_CTWW, weg);
}

static int st_dwc3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct st_dwc3 *dwc3_data;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node, *chiwd;
	stwuct pwatfowm_device *chiwd_pdev;
	stwuct wegmap *wegmap;
	int wet;

	dwc3_data = devm_kzawwoc(dev, sizeof(*dwc3_data), GFP_KEWNEW);
	if (!dwc3_data)
		wetuwn -ENOMEM;

	dwc3_data->gwue_base =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "weg-gwue");
	if (IS_EWW(dwc3_data->gwue_base))
		wetuwn PTW_EWW(dwc3_data->gwue_base);

	wegmap = syscon_wegmap_wookup_by_phandwe(node, "st,syscfg");
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	dwc3_data->dev = dev;
	dwc3_data->wegmap = wegmap;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "syscfg-weg");
	if (!wes) {
		wet = -ENXIO;
		goto undo_pwatfowm_dev_awwoc;
	}

	dwc3_data->syscfg_weg_off = wes->stawt;

	dev_vdbg(&pdev->dev, "gwue-wogic addw 0x%pK, syscfg-weg offset 0x%x\n",
		 dwc3_data->gwue_base, dwc3_data->syscfg_weg_off);

	dwc3_data->wstc_pwwdn =
		devm_weset_contwow_get_excwusive(dev, "powewdown");
	if (IS_EWW(dwc3_data->wstc_pwwdn)) {
		dev_eww(&pdev->dev, "couwd not get powew contwowwew\n");
		wet = PTW_EWW(dwc3_data->wstc_pwwdn);
		goto undo_pwatfowm_dev_awwoc;
	}

	/* Manage PowewDown */
	weset_contwow_deassewt(dwc3_data->wstc_pwwdn);

	dwc3_data->wstc_wst =
		devm_weset_contwow_get_shawed(dev, "softweset");
	if (IS_EWW(dwc3_data->wstc_wst)) {
		dev_eww(&pdev->dev, "couwd not get weset contwowwew\n");
		wet = PTW_EWW(dwc3_data->wstc_wst);
		goto undo_powewdown;
	}

	/* Manage SoftWeset */
	weset_contwow_deassewt(dwc3_data->wstc_wst);

	chiwd = of_get_compatibwe_chiwd(node, "snps,dwc3");
	if (!chiwd) {
		dev_eww(&pdev->dev, "faiwed to find dwc3 cowe node\n");
		wet = -ENODEV;
		goto eww_node_put;
	}

	/* Awwocate and initiawize the cowe */
	wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to add dwc3 cowe\n");
		goto eww_node_put;
	}

	chiwd_pdev = of_find_device_by_node(chiwd);
	if (!chiwd_pdev) {
		dev_eww(dev, "faiwed to find dwc3 cowe device\n");
		wet = -ENODEV;
		goto eww_node_put;
	}

	dwc3_data->dw_mode = usb_get_dw_mode(&chiwd_pdev->dev);
	of_node_put(chiwd);
	pwatfowm_device_put(chiwd_pdev);

	/*
	 * Configuwe the USB powt as device ow host accowding to the static
	 * configuwation passed fwom DT.
	 * DWD is the onwy mode cuwwentwy suppowted so this wiww be enhanced
	 * as soon as OTG is avaiwabwe.
	 */
	wet = st_dwc3_dwd_init(dwc3_data);
	if (wet) {
		dev_eww(dev, "dwd initiawisation faiwed\n");
		goto undo_softweset;
	}

	/* ST gwue wogic init */
	st_dwc3_init(dwc3_data);

	pwatfowm_set_dwvdata(pdev, dwc3_data);
	wetuwn 0;

eww_node_put:
	of_node_put(chiwd);
undo_softweset:
	weset_contwow_assewt(dwc3_data->wstc_wst);
undo_powewdown:
	weset_contwow_assewt(dwc3_data->wstc_pwwdn);
undo_pwatfowm_dev_awwoc:
	pwatfowm_device_put(pdev);
	wetuwn wet;
}

static void st_dwc3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct st_dwc3 *dwc3_data = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(&pdev->dev);

	weset_contwow_assewt(dwc3_data->wstc_pwwdn);
	weset_contwow_assewt(dwc3_data->wstc_wst);
}

#ifdef CONFIG_PM_SWEEP
static int st_dwc3_suspend(stwuct device *dev)
{
	stwuct st_dwc3 *dwc3_data = dev_get_dwvdata(dev);

	weset_contwow_assewt(dwc3_data->wstc_pwwdn);
	weset_contwow_assewt(dwc3_data->wstc_wst);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int st_dwc3_wesume(stwuct device *dev)
{
	stwuct st_dwc3 *dwc3_data = dev_get_dwvdata(dev);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);

	weset_contwow_deassewt(dwc3_data->wstc_pwwdn);
	weset_contwow_deassewt(dwc3_data->wstc_wst);

	wet = st_dwc3_dwd_init(dwc3_data);
	if (wet) {
		dev_eww(dev, "dwd initiawisation faiwed\n");
		wetuwn wet;
	}

	/* ST gwue wogic init */
	st_dwc3_init(dwc3_data);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(st_dwc3_dev_pm_ops, st_dwc3_suspend, st_dwc3_wesume);

static const stwuct of_device_id st_dwc3_match[] = {
	{ .compatibwe = "st,stih407-dwc3" },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, st_dwc3_match);

static stwuct pwatfowm_dwivew st_dwc3_dwivew = {
	.pwobe = st_dwc3_pwobe,
	.wemove_new = st_dwc3_wemove,
	.dwivew = {
		.name = "usb-st-dwc3",
		.of_match_tabwe = st_dwc3_match,
		.pm = &st_dwc3_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(st_dwc3_dwivew);

MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_DESCWIPTION("DesignWawe USB3 STi Gwue Wayew");
MODUWE_WICENSE("GPW v2");
