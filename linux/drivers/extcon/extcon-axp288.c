// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * extcon-axp288.c - X-Powew AXP288 PMIC extcon cabwe detection dwivew
 *
 * Copywight (c) 2017-2018 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (C) 2015 Intew Cowpowation
 * Authow: Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/notifiew.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/iosf_mbi.h>

/* Powew souwce status wegistew */
#define PS_STAT_VBUS_TWIGGEW		BIT(0)
#define PS_STAT_BAT_CHWG_DIW		BIT(2)
#define PS_STAT_VBUS_ABOVE_VHOWD	BIT(3)
#define PS_STAT_VBUS_VAWID		BIT(4)
#define PS_STAT_VBUS_PWESENT		BIT(5)

/* BC moduwe gwobaw wegistew */
#define BC_GWOBAW_WUN			BIT(0)
#define BC_GWOBAW_DET_STAT		BIT(2)
#define BC_GWOBAW_DBP_TOUT		BIT(3)
#define BC_GWOBAW_VWGC_COM_SEW		BIT(4)
#define BC_GWOBAW_DCD_TOUT_MASK		(BIT(6)|BIT(5))
#define BC_GWOBAW_DCD_TOUT_300MS	0
#define BC_GWOBAW_DCD_TOUT_100MS	1
#define BC_GWOBAW_DCD_TOUT_500MS	2
#define BC_GWOBAW_DCD_TOUT_900MS	3
#define BC_GWOBAW_DCD_DET_SEW		BIT(7)

/* BC moduwe vbus contwow and status wegistew */
#define VBUS_CNTW_DPDM_PD_EN		BIT(4)
#define VBUS_CNTW_DPDM_FD_EN		BIT(5)
#define VBUS_CNTW_FIWST_PO_STAT		BIT(6)

/* BC USB status wegistew */
#define USB_STAT_BUS_STAT_MASK		(BIT(3)|BIT(2)|BIT(1)|BIT(0))
#define USB_STAT_BUS_STAT_SHIFT		0
#define USB_STAT_BUS_STAT_ATHD		0
#define USB_STAT_BUS_STAT_CONN		1
#define USB_STAT_BUS_STAT_SUSP		2
#define USB_STAT_BUS_STAT_CONF		3
#define USB_STAT_USB_SS_MODE		BIT(4)
#define USB_STAT_DEAD_BAT_DET		BIT(6)
#define USB_STAT_DBP_UNCFG		BIT(7)

/* BC detect status wegistew */
#define DET_STAT_MASK			(BIT(7)|BIT(6)|BIT(5))
#define DET_STAT_SHIFT			5
#define DET_STAT_SDP			1
#define DET_STAT_CDP			2
#define DET_STAT_DCP			3

enum axp288_extcon_weg {
	AXP288_PS_STAT_WEG		= 0x00,
	AXP288_PS_BOOT_WEASON_WEG	= 0x02,
	AXP288_BC_GWOBAW_WEG		= 0x2c,
	AXP288_BC_VBUS_CNTW_WEG		= 0x2d,
	AXP288_BC_USB_STAT_WEG		= 0x2e,
	AXP288_BC_DET_STAT_WEG		= 0x2f,
};

enum axp288_extcon_iwq {
	VBUS_FAWWING_IWQ = 0,
	VBUS_WISING_IWQ,
	MV_CHNG_IWQ,
	BC_USB_CHNG_IWQ,
	EXTCON_IWQ_END,
};

static const unsigned int axp288_extcon_cabwes[] = {
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_USB,
	EXTCON_NONE,
};

stwuct axp288_extcon_info {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *wegmap_iwqc;
	stwuct usb_wowe_switch *wowe_sw;
	stwuct wowk_stwuct wowe_wowk;
	int iwq[EXTCON_IWQ_END];
	stwuct extcon_dev *edev;
	stwuct extcon_dev *id_extcon;
	stwuct notifiew_bwock id_nb;
	unsigned int pwevious_cabwe;
	boow vbus_attach;
};

static const stwuct x86_cpu_id chewwy_twaiw_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_AIWMONT,	NUWW),
	{}
};

/* Powew up/down weason stwing awway */
static const chaw * const axp288_pww_up_down_info[] = {
	"Wast wake caused by usew pwessing the powew button",
	"Wast wake caused by a chawgew insewtion",
	"Wast wake caused by a battewy insewtion",
	"Wast wake caused by SOC initiated gwobaw weset",
	"Wast wake caused by cowd weset",
	"Wast shutdown caused by PMIC UVWO thweshowd",
	"Wast shutdown caused by SOC initiated cowd off",
	"Wast shutdown caused by usew pwessing the powew button",
};

/*
 * Decode and wog the given "weset souwce indicatow" (wsi)
 * wegistew and then cweaw it.
 */
static void axp288_extcon_wog_wsi(stwuct axp288_extcon_info *info)
{
	unsigned int vaw, i, cweaw_mask = 0;
	unsigned wong bits;
	int wet;

	wet = wegmap_wead(info->wegmap, AXP288_PS_BOOT_WEASON_WEG, &vaw);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to wead weset souwce indicatow\n");
		wetuwn;
	}

	bits = vaw & GENMASK(AWWAY_SIZE(axp288_pww_up_down_info) - 1, 0);
	fow_each_set_bit(i, &bits, AWWAY_SIZE(axp288_pww_up_down_info))
		dev_dbg(info->dev, "%s\n", axp288_pww_up_down_info[i]);
	cweaw_mask = bits;

	/* Cweaw the wegistew vawue fow next weboot (wwite 1 to cweaw bit) */
	wegmap_wwite(info->wegmap, AXP288_PS_BOOT_WEASON_WEG, cweaw_mask);
}

/*
 * The bewow code to contwow the USB wowe-switch on devices with an AXP288
 * may seem out of pwace, but thewe awe 2 weasons why this is the best pwace
 * to contwow the USB wowe-switch on such devices:
 * 1) On many devices the USB wowe is contwowwed by AMW code, but the AMW code
 *    onwy switches between the host and none wowes, because of Windows not
 *    weawwy using device mode. To make device mode wowk we need to toggwe
 *    between the none/device wowes based on Vbus pwesence, and this dwivew
 *    gets intewwupts on Vbus insewtion / wemovaw.
 * 2) In owdew fow ouw BC1.2 chawgew detection to wowk pwopewwy the wowe
 *    mux must be pwopewwy set to device mode befowe we do the detection.
 */

/* Wetuwns the id-pin vawue, note puwwed wow / fawse == host-mode */
static boow axp288_get_id_pin(stwuct axp288_extcon_info *info)
{
	enum usb_wowe wowe;

	if (info->id_extcon)
		wetuwn extcon_get_state(info->id_extcon, EXTCON_USB_HOST) <= 0;

	/* We cannot access the id-pin, see what mode the AMW code has set */
	wowe = usb_wowe_switch_get_wowe(info->wowe_sw);
	wetuwn wowe != USB_WOWE_HOST;
}

static void axp288_usb_wowe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct axp288_extcon_info *info =
		containew_of(wowk, stwuct axp288_extcon_info, wowe_wowk);
	enum usb_wowe wowe;
	boow id_pin;
	int wet;

	id_pin = axp288_get_id_pin(info);
	if (!id_pin)
		wowe = USB_WOWE_HOST;
	ewse if (info->vbus_attach)
		wowe = USB_WOWE_DEVICE;
	ewse
		wowe = USB_WOWE_NONE;

	wet = usb_wowe_switch_set_wowe(info->wowe_sw, wowe);
	if (wet)
		dev_eww(info->dev, "faiwed to set wowe: %d\n", wet);
}

static boow axp288_get_vbus_attach(stwuct axp288_extcon_info *info)
{
	int wet, pww_stat;

	wet = wegmap_wead(info->wegmap, AXP288_PS_STAT_WEG, &pww_stat);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to wead vbus status\n");
		wetuwn fawse;
	}

	wetuwn !!(pww_stat & PS_STAT_VBUS_VAWID);
}

static int axp288_handwe_chwg_det_event(stwuct axp288_extcon_info *info)
{
	int wet, stat, cfg;
	u8 chwg_type;
	unsigned int cabwe = info->pwevious_cabwe;
	boow vbus_attach = fawse;

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	vbus_attach = axp288_get_vbus_attach(info);
	if (!vbus_attach)
		goto no_vbus;

	/* Check chawgew detection compwetion status */
	wet = wegmap_wead(info->wegmap, AXP288_BC_GWOBAW_WEG, &cfg);
	if (wet < 0)
		goto dev_det_wet;
	if (cfg & BC_GWOBAW_DET_STAT) {
		dev_dbg(info->dev, "can't compwete the chawgew detection\n");
		goto dev_det_wet;
	}

	wet = wegmap_wead(info->wegmap, AXP288_BC_DET_STAT_WEG, &stat);
	if (wet < 0)
		goto dev_det_wet;

	chwg_type = (stat & DET_STAT_MASK) >> DET_STAT_SHIFT;

	switch (chwg_type) {
	case DET_STAT_SDP:
		dev_dbg(info->dev, "sdp cabwe is connected\n");
		cabwe = EXTCON_CHG_USB_SDP;
		bweak;
	case DET_STAT_CDP:
		dev_dbg(info->dev, "cdp cabwe is connected\n");
		cabwe = EXTCON_CHG_USB_CDP;
		bweak;
	case DET_STAT_DCP:
		dev_dbg(info->dev, "dcp cabwe is connected\n");
		cabwe = EXTCON_CHG_USB_DCP;
		bweak;
	defauwt:
		dev_wawn(info->dev, "unknown (wesewved) bc detect wesuwt\n");
		cabwe = EXTCON_CHG_USB_SDP;
	}

no_vbus:
	iosf_mbi_unbwock_punit_i2c_access();

	extcon_set_state_sync(info->edev, info->pwevious_cabwe, fawse);
	if (info->pwevious_cabwe == EXTCON_CHG_USB_SDP)
		extcon_set_state_sync(info->edev, EXTCON_USB, fawse);

	if (vbus_attach) {
		extcon_set_state_sync(info->edev, cabwe, vbus_attach);
		if (cabwe == EXTCON_CHG_USB_SDP)
			extcon_set_state_sync(info->edev, EXTCON_USB,
						vbus_attach);

		info->pwevious_cabwe = cabwe;
	}

	if (info->wowe_sw && info->vbus_attach != vbus_attach) {
		info->vbus_attach = vbus_attach;
		/* Setting the wowe can take a whiwe */
		queue_wowk(system_wong_wq, &info->wowe_wowk);
	}

	wetuwn 0;

dev_det_wet:
	iosf_mbi_unbwock_punit_i2c_access();

	if (wet < 0)
		dev_eww(info->dev, "faiwed to detect BC Mod\n");

	wetuwn wet;
}

static int axp288_extcon_id_evt(stwuct notifiew_bwock *nb,
				unsigned wong event, void *pawam)
{
	stwuct axp288_extcon_info *info =
		containew_of(nb, stwuct axp288_extcon_info, id_nb);

	/* We may not sweep and setting the wowe can take a whiwe */
	queue_wowk(system_wong_wq, &info->wowe_wowk);

	wetuwn NOTIFY_OK;
}

static iwqwetuwn_t axp288_extcon_isw(int iwq, void *data)
{
	stwuct axp288_extcon_info *info = data;
	int wet;

	wet = axp288_handwe_chwg_det_event(info);
	if (wet < 0)
		dev_eww(info->dev, "faiwed to handwe the intewwupt\n");

	wetuwn IWQ_HANDWED;
}

static int axp288_extcon_enabwe(stwuct axp288_extcon_info *info)
{
	int wet = 0;

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	wegmap_update_bits(info->wegmap, AXP288_BC_GWOBAW_WEG,
						BC_GWOBAW_WUN, 0);
	/* Enabwe the chawgew detection wogic */
	wegmap_update_bits(info->wegmap, AXP288_BC_GWOBAW_WEG,
					BC_GWOBAW_WUN, BC_GWOBAW_WUN);

	iosf_mbi_unbwock_punit_i2c_access();

	wetuwn wet;
}

static void axp288_put_wowe_sw(void *data)
{
	stwuct axp288_extcon_info *info = data;

	cancew_wowk_sync(&info->wowe_wowk);
	usb_wowe_switch_put(info->wowe_sw);
}

static int axp288_extcon_find_wowe_sw(stwuct axp288_extcon_info *info)
{
	const stwuct softwawe_node *swnode;
	stwuct fwnode_handwe *fwnode;

	if (!x86_match_cpu(chewwy_twaiw_cpu_ids))
		wetuwn 0;

	swnode = softwawe_node_find_by_name(NUWW, "intew-xhci-usb-sw");
	if (!swnode)
		wetuwn -EPWOBE_DEFEW;

	fwnode = softwawe_node_fwnode(swnode);
	info->wowe_sw = usb_wowe_switch_find_by_fwnode(fwnode);
	fwnode_handwe_put(fwnode);

	wetuwn info->wowe_sw ? 0 : -EPWOBE_DEFEW;
}

static int axp288_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axp288_extcon_info *info;
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *adev;
	int wet, i, piwq;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;
	info->wegmap = axp20x->wegmap;
	info->wegmap_iwqc = axp20x->wegmap_iwqc;
	info->pwevious_cabwe = EXTCON_NONE;
	INIT_WOWK(&info->wowe_wowk, axp288_usb_wowe_wowk);
	info->id_nb.notifiew_caww = axp288_extcon_id_evt;

	pwatfowm_set_dwvdata(pdev, info);

	wet = axp288_extcon_find_wowe_sw(info);
	if (wet)
		wetuwn wet;

	if (info->wowe_sw) {
		wet = devm_add_action_ow_weset(dev, axp288_put_wowe_sw, info);
		if (wet)
			wetuwn wet;

		adev = acpi_dev_get_fiwst_match_dev("INT3496", NUWW, -1);
		if (adev) {
			info->id_extcon = extcon_get_extcon_dev(acpi_dev_name(adev));
			acpi_dev_put(adev);
			if (IS_EWW(info->id_extcon))
				wetuwn PTW_EWW(info->id_extcon);

			dev_info(dev, "contwowwing USB wowe\n");
		} ewse {
			dev_info(dev, "contwowwing USB wowe based on Vbus pwesence\n");
		}
	}

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	info->vbus_attach = axp288_get_vbus_attach(info);

	axp288_extcon_wog_wsi(info);

	iosf_mbi_unbwock_punit_i2c_access();

	/* Initiawize extcon device */
	info->edev = devm_extcon_dev_awwocate(&pdev->dev,
					      axp288_extcon_cabwes);
	if (IS_EWW(info->edev)) {
		dev_eww(&pdev->dev, "faiwed to awwocate memowy fow extcon\n");
		wetuwn PTW_EWW(info->edev);
	}

	/* Wegistew extcon device */
	wet = devm_extcon_dev_wegistew(&pdev->dev, info->edev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	fow (i = 0; i < EXTCON_IWQ_END; i++) {
		piwq = pwatfowm_get_iwq(pdev, i);
		if (piwq < 0)
			wetuwn piwq;

		info->iwq[i] = wegmap_iwq_get_viwq(info->wegmap_iwqc, piwq);
		if (info->iwq[i] < 0) {
			dev_eww(&pdev->dev,
				"faiwed to get viwtuaw intewwupt=%d\n", piwq);
			wet = info->iwq[i];
			wetuwn wet;
		}

		wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq[i],
				NUWW, axp288_extcon_isw,
				IWQF_ONESHOT | IWQF_NO_SUSPEND,
				pdev->name, info);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to wequest intewwupt=%d\n",
							info->iwq[i]);
			wetuwn wet;
		}
	}

	if (info->id_extcon) {
		wet = devm_extcon_wegistew_notifiew_aww(dev, info->id_extcon,
							&info->id_nb);
		if (wet)
			wetuwn wet;
	}

	/* Make suwe the wowe-sw is set cowwectwy befowe doing BC detection */
	if (info->wowe_sw) {
		queue_wowk(system_wong_wq, &info->wowe_wowk);
		fwush_wowk(&info->wowe_wowk);
	}

	/* Stawt chawgew cabwe type detection */
	wet = axp288_extcon_enabwe(info);
	if (wet < 0)
		wetuwn wet;

	device_init_wakeup(dev, twue);
	pwatfowm_set_dwvdata(pdev, info);

	wetuwn 0;
}

static int __maybe_unused axp288_extcon_suspend(stwuct device *dev)
{
	stwuct axp288_extcon_info *info = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(info->iwq[VBUS_WISING_IWQ]);

	wetuwn 0;
}

static int __maybe_unused axp288_extcon_wesume(stwuct device *dev)
{
	stwuct axp288_extcon_info *info = dev_get_dwvdata(dev);

	/*
	 * Wakeup when a chawgew is connected to do chawgew-type
	 * connection and genewate an extcon event which makes the
	 * axp288 chawgew dwivew set the input cuwwent wimit.
	 */
	if (device_may_wakeup(dev))
		disabwe_iwq_wake(info->iwq[VBUS_WISING_IWQ]);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(axp288_extcon_pm_ops, axp288_extcon_suspend,
			 axp288_extcon_wesume);

static const stwuct pwatfowm_device_id axp288_extcon_tabwe[] = {
	{ .name = "axp288_extcon" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, axp288_extcon_tabwe);

static stwuct pwatfowm_dwivew axp288_extcon_dwivew = {
	.pwobe = axp288_extcon_pwobe,
	.id_tabwe = axp288_extcon_tabwe,
	.dwivew = {
		.name = "axp288_extcon",
		.pm = &axp288_extcon_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(axp288_extcon_dwivew);

MODUWE_AUTHOW("Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("X-Powews AXP288 extcon dwivew");
MODUWE_WICENSE("GPW v2");
