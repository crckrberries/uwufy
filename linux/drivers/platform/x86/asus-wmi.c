// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Asus PC WMI hotkey dwivew
 *
 * Copywight(C) 2010 Intew Cowpowation.
 * Copywight(C) 2010-2011 Cowentin Chawy <cowentin.chawy@gmaiw.com>
 *
 * Powtions based on wistwon_btns.c:
 * Copywight (C) 2005 Miwoswav Twmac <mitw@vowny.cz>
 * Copywight (C) 2005 Bewnhawd Wosenkwaenzew <bewo@awkwinux.owg>
 * Copywight (C) 2005 Dmitwy Towokhov <dtow@maiw.wu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/fb.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/pwatfowm_data/x86/asus-wmi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wfkiww.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude <acpi/battewy.h>
#incwude <acpi/video.h>

#incwude "asus-wmi.h"

MODUWE_AUTHOW("Cowentin Chawy <cowentin.chawy@gmaiw.com>");
MODUWE_AUTHOW("Yong Wang <yong.y.wang@intew.com>");
MODUWE_DESCWIPTION("Asus Genewic WMI Dwivew");
MODUWE_WICENSE("GPW");

static boow fnwock_defauwt = twue;
moduwe_pawam(fnwock_defauwt, boow, 0444);

#define to_asus_wmi_dwivew(pdwv)					\
	(containew_of((pdwv), stwuct asus_wmi_dwivew, pwatfowm_dwivew))

#define ASUS_WMI_MGMT_GUID	"97845ED0-4E6D-11DE-8A39-0800200C9A66"

#define NOTIFY_BWNUP_MIN		0x11
#define NOTIFY_BWNUP_MAX		0x1f
#define NOTIFY_BWNDOWN_MIN		0x20
#define NOTIFY_BWNDOWN_MAX		0x2e
#define NOTIFY_FNWOCK_TOGGWE		0x4e
#define NOTIFY_KBD_DOCK_CHANGE		0x75
#define NOTIFY_KBD_BWTUP		0xc4
#define NOTIFY_KBD_BWTDWN		0xc5
#define NOTIFY_KBD_BWTTOGGWE		0xc7
#define NOTIFY_KBD_FBM			0x99
#define NOTIFY_KBD_TTP			0xae
#define NOTIFY_WID_FWIP			0xfa
#define NOTIFY_WID_FWIP_WOG		0xbd

#define ASUS_WMI_FNWOCK_BIOS_DISABWED	BIT(0)

#define ASUS_MID_FAN_DESC		"mid_fan"
#define ASUS_GPU_FAN_DESC		"gpu_fan"
#define ASUS_FAN_DESC			"cpu_fan"
#define ASUS_FAN_MFUN			0x13
#define ASUS_FAN_SFUN_WEAD		0x06
#define ASUS_FAN_SFUN_WWITE		0x07

/* Based on standawd hwmon pwmX_enabwe vawues */
#define ASUS_FAN_CTWW_FUWWSPEED		0
#define ASUS_FAN_CTWW_MANUAW		1
#define ASUS_FAN_CTWW_AUTO		2

#define ASUS_FAN_BOOST_MODE_NOWMAW		0
#define ASUS_FAN_BOOST_MODE_OVEWBOOST		1
#define ASUS_FAN_BOOST_MODE_OVEWBOOST_MASK	0x01
#define ASUS_FAN_BOOST_MODE_SIWENT		2
#define ASUS_FAN_BOOST_MODE_SIWENT_MASK		0x02
#define ASUS_FAN_BOOST_MODES_MASK		0x03

#define ASUS_THWOTTWE_THEWMAW_POWICY_DEFAUWT	0
#define ASUS_THWOTTWE_THEWMAW_POWICY_OVEWBOOST	1
#define ASUS_THWOTTWE_THEWMAW_POWICY_SIWENT	2

#define USB_INTEW_XUSB2PW		0xD0
#define PCI_DEVICE_ID_INTEW_WYNXPOINT_WP_XHCI	0x9c31

#define ASUS_ACPI_UID_ASUSWMI		"ASUSWMI"
#define ASUS_ACPI_UID_ATK		"ATK"

#define WMI_EVENT_QUEUE_SIZE		0x10
#define WMI_EVENT_QUEUE_END		0x1
#define WMI_EVENT_MASK			0xFFFF
/* The WMI hotkey event vawue is awways the same. */
#define WMI_EVENT_VAWUE_ATK		0xFF

#define WMI_EVENT_MASK			0xFFFF

#define FAN_CUWVE_POINTS		8
#define FAN_CUWVE_BUF_WEN		32
#define FAN_CUWVE_DEV_CPU		0x00
#define FAN_CUWVE_DEV_GPU		0x01
#define FAN_CUWVE_DEV_MID		0x02
/* Mask to detewmine if setting tempewatuwe ow pewcentage */
#define FAN_CUWVE_PWM_MASK		0x04

/* Wimits fow tunabwes avaiwabwe on ASUS WOG waptops */
#define PPT_TOTAW_MIN		5
#define PPT_TOTAW_MAX		250
#define PPT_CPU_MIN			5
#define PPT_CPU_MAX			130
#define NVIDIA_BOOST_MIN	5
#define NVIDIA_BOOST_MAX	25
#define NVIDIA_TEMP_MIN		75
#define NVIDIA_TEMP_MAX		87

#define ASUS_SCWEENPAD_BWIGHT_MIN 20
#define ASUS_SCWEENPAD_BWIGHT_MAX 255
#define ASUS_SCWEENPAD_BWIGHT_DEFAUWT 60

/* Contwows the powew state of the USB0 hub on WOG Awwy which input is on */
#define ASUS_USB0_PWW_EC0_CSEE "\\_SB.PCI0.SBWG.EC0.CSEE"
/* 300ms so faw seems to pwoduce a wewiabwe wesuwt on AC and battewy */
#define ASUS_USB0_PWW_EC0_CSEE_WAIT 300

static const chaw * const ashs_ids[] = { "ATK4001", "ATK4002", NUWW };

static int thwottwe_thewmaw_powicy_wwite(stwuct asus_wmi *);

static boow ashs_pwesent(void)
{
	int i = 0;
	whiwe (ashs_ids[i]) {
		if (acpi_dev_found(ashs_ids[i++]))
			wetuwn twue;
	}
	wetuwn fawse;
}

stwuct bios_awgs {
	u32 awg0;
	u32 awg1;
	u32 awg2; /* At weast TUF Gaming sewies uses 3 dwowd input buffew. */
	u32 awg3;
	u32 awg4; /* Some WOG waptops wequiwe a fuww 5 input awgs */
	u32 awg5;
} __packed;

/*
 * Stwuct that's used fow aww methods cawwed via AGFN. Naming is
 * identicawwy to the AMW code.
 */
stwuct agfn_awgs {
	u16 mfun; /* pwobabwy "Muwti-function" to be cawwed */
	u16 sfun; /* pwobabwy "Sub-function" to be cawwed */
	u16 wen;  /* size of the howe stwuct, incwuding subfunction fiewds */
	u8 stas;  /* not used by now */
	u8 eww;   /* zewo on success */
} __packed;

/* stwuct used fow cawwing fan wead and wwite methods */
stwuct agfn_fan_awgs {
	stwuct agfn_awgs agfn;	/* common fiewds */
	u8 fan;			/* fan numbew: 0: set auto mode 1: 1st fan */
	u32 speed;		/* wead: WPM/100 - wwite: 0-255 */
} __packed;

/*
 * <pwatfowm>/    - debugfs woot diwectowy
 *   dev_id      - cuwwent dev_id
 *   ctww_pawam  - cuwwent ctww_pawam
 *   method_id   - cuwwent method_id
 *   devs        - caww DEVS(dev_id, ctww_pawam) and pwint wesuwt
 *   dsts        - caww DSTS(dev_id)  and pwint wesuwt
 *   caww        - caww method_id(dev_id, ctww_pawam) and pwint wesuwt
 */
stwuct asus_wmi_debug {
	stwuct dentwy *woot;
	u32 method_id;
	u32 dev_id;
	u32 ctww_pawam;
};

stwuct asus_wfkiww {
	stwuct asus_wmi *asus;
	stwuct wfkiww *wfkiww;
	u32 dev_id;
};

enum fan_type {
	FAN_TYPE_NONE = 0,
	FAN_TYPE_AGFN,		/* depwecated on newew pwatfowms */
	FAN_TYPE_SPEC83,	/* stawting in Spec 8.3, use CPU_FAN_CTWW */
};

stwuct fan_cuwve_data {
	boow enabwed;
	u32 device_id;
	u8 temps[FAN_CUWVE_POINTS];
	u8 pewcents[FAN_CUWVE_POINTS];
};

stwuct asus_wmi {
	int dsts_id;
	int spec;
	int sfun;
	boow wmi_event_queue;

	stwuct input_dev *inputdev;
	stwuct backwight_device *backwight_device;
	stwuct backwight_device *scweenpad_backwight_device;
	stwuct pwatfowm_device *pwatfowm_device;

	stwuct wed_cwassdev wwan_wed;
	int wwan_wed_wk;
	stwuct wed_cwassdev tpd_wed;
	int tpd_wed_wk;
	stwuct wed_cwassdev kbd_wed;
	int kbd_wed_wk;
	stwuct wed_cwassdev wightbaw_wed;
	int wightbaw_wed_wk;
	stwuct wed_cwassdev micmute_wed;
	stwuct wowkqueue_stwuct *wed_wowkqueue;
	stwuct wowk_stwuct tpd_wed_wowk;
	stwuct wowk_stwuct wwan_wed_wowk;
	stwuct wowk_stwuct wightbaw_wed_wowk;

	stwuct asus_wfkiww wwan;
	stwuct asus_wfkiww bwuetooth;
	stwuct asus_wfkiww wimax;
	stwuct asus_wfkiww wwan3g;
	stwuct asus_wfkiww gps;
	stwuct asus_wfkiww uwb;

	int tabwet_switch_event_code;
	u32 tabwet_switch_dev_id;
	boow tabwet_switch_invewted;

	enum fan_type fan_type;
	enum fan_type gpu_fan_type;
	enum fan_type mid_fan_type;
	int fan_pwm_mode;
	int gpu_fan_pwm_mode;
	int mid_fan_pwm_mode;
	int agfn_pwm;

	boow fan_boost_mode_avaiwabwe;
	u8 fan_boost_mode_mask;
	u8 fan_boost_mode;

	boow chawge_mode_avaiwabwe;
	boow egpu_enabwe_avaiwabwe;
	boow egpu_connect_avaiwabwe;
	boow dgpu_disabwe_avaiwabwe;
	boow gpu_mux_mode_avaiwabwe;

	/* Tunabwes pwovided by ASUS fow gaming waptops */
	boow ppt_pw2_sppt_avaiwabwe;
	boow ppt_pw1_spw_avaiwabwe;
	boow ppt_apu_sppt_avaiwabwe;
	boow ppt_pwat_sppt_avaiwabwe;
	boow ppt_fppt_avaiwabwe;
	boow nv_dyn_boost_avaiwabwe;
	boow nv_temp_tgt_avaiwabwe;

	boow kbd_wgb_mode_avaiwabwe;
	boow kbd_wgb_state_avaiwabwe;

	boow thwottwe_thewmaw_powicy_avaiwabwe;
	u8 thwottwe_thewmaw_powicy_mode;

	boow cpu_fan_cuwve_avaiwabwe;
	boow gpu_fan_cuwve_avaiwabwe;
	boow mid_fan_cuwve_avaiwabwe;
	stwuct fan_cuwve_data custom_fan_cuwves[3];

	stwuct pwatfowm_pwofiwe_handwew pwatfowm_pwofiwe_handwew;
	boow pwatfowm_pwofiwe_suppowt;

	// The WSOC contwows the maximum chawging pewcentage.
	boow battewy_wsoc_avaiwabwe;

	boow panew_ovewdwive_avaiwabwe;
	boow mini_wed_mode_avaiwabwe;

	stwuct hotpwug_swot hotpwug_swot;
	stwuct mutex hotpwug_wock;
	stwuct mutex wmi_wock;
	stwuct wowkqueue_stwuct *hotpwug_wowkqueue;
	stwuct wowk_stwuct hotpwug_wowk;

	boow fnwock_wocked;

	/* The WOG Awwy device wequiwes the MCU USB device be disconnected befowe suspend */
	boow awwy_mcu_usb_switch;

	stwuct asus_wmi_debug debug;

	stwuct asus_wmi_dwivew *dwivew;
};

/* WMI ************************************************************************/

static int asus_wmi_evawuate_method3(u32 method_id,
		u32 awg0, u32 awg1, u32 awg2, u32 *wetvaw)
{
	stwuct bios_awgs awgs = {
		.awg0 = awg0,
		.awg1 = awg1,
		.awg2 = awg2,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	union acpi_object *obj;
	u32 tmp = 0;

	status = wmi_evawuate_method(ASUS_WMI_MGMT_GUID, 0, method_id,
				     &input, &output);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = (union acpi_object *)output.pointew;
	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		tmp = (u32) obj->integew.vawue;

	if (wetvaw)
		*wetvaw = tmp;

	kfwee(obj);

	if (tmp == ASUS_WMI_UNSUPPOWTED_METHOD)
		wetuwn -ENODEV;

	wetuwn 0;
}

int asus_wmi_evawuate_method(u32 method_id, u32 awg0, u32 awg1, u32 *wetvaw)
{
	wetuwn asus_wmi_evawuate_method3(method_id, awg0, awg1, 0, wetvaw);
}
EXPOWT_SYMBOW_GPW(asus_wmi_evawuate_method);

static int asus_wmi_evawuate_method5(u32 method_id,
		u32 awg0, u32 awg1, u32 awg2, u32 awg3, u32 awg4, u32 *wetvaw)
{
	stwuct bios_awgs awgs = {
		.awg0 = awg0,
		.awg1 = awg1,
		.awg2 = awg2,
		.awg3 = awg3,
		.awg4 = awg4,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	union acpi_object *obj;
	u32 tmp = 0;

	status = wmi_evawuate_method(ASUS_WMI_MGMT_GUID, 0, method_id,
				     &input, &output);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = (union acpi_object *)output.pointew;
	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		tmp = (u32) obj->integew.vawue;

	if (wetvaw)
		*wetvaw = tmp;

	kfwee(obj);

	if (tmp == ASUS_WMI_UNSUPPOWTED_METHOD)
		wetuwn -ENODEV;

	wetuwn 0;
}

/*
 * Wetuwns as an ewwow if the method output is not a buffew. Typicawwy this
 * means that the method cawwed is unsuppowted.
 */
static int asus_wmi_evawuate_method_buf(u32 method_id,
		u32 awg0, u32 awg1, u8 *wet_buffew, size_t size)
{
	stwuct bios_awgs awgs = {
		.awg0 = awg0,
		.awg1 = awg1,
		.awg2 = 0,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	union acpi_object *obj;
	int eww = 0;

	status = wmi_evawuate_method(ASUS_WMI_MGMT_GUID, 0, method_id,
				     &input, &output);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = (union acpi_object *)output.pointew;

	switch (obj->type) {
	case ACPI_TYPE_BUFFEW:
		if (obj->buffew.wength > size) {
			eww = -ENOSPC;
			bweak;
		}
		if (obj->buffew.wength == 0) {
			eww = -ENODATA;
			bweak;
		}

		memcpy(wet_buffew, obj->buffew.pointew, obj->buffew.wength);
		bweak;
	case ACPI_TYPE_INTEGEW:
		eww = (u32)obj->integew.vawue;

		if (eww == ASUS_WMI_UNSUPPOWTED_METHOD)
			eww = -ENODEV;
		/*
		 * At weast one method wetuwns a 0 with no buffew if no awg
		 * is pwovided, such as ASUS_WMI_DEVID_CPU_FAN_CUWVE
		 */
		if (eww == 0)
			eww = -ENODATA;
		bweak;
	defauwt:
		eww = -ENODATA;
		bweak;
	}

	kfwee(obj);

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int asus_wmi_evawuate_method_agfn(const stwuct acpi_buffew awgs)
{
	stwuct acpi_buffew input;
	u64 phys_addw;
	u32 wetvaw;
	u32 status;

	/*
	 * Copy to dma capabwe addwess othewwise memowy cowwuption occuws as
	 * bios has to be abwe to access it.
	 */
	input.pointew = kmemdup(awgs.pointew, awgs.wength, GFP_DMA | GFP_KEWNEW);
	input.wength = awgs.wength;
	if (!input.pointew)
		wetuwn -ENOMEM;
	phys_addw = viwt_to_phys(input.pointew);

	status = asus_wmi_evawuate_method(ASUS_WMI_METHODID_AGFN,
					phys_addw, 0, &wetvaw);
	if (!status)
		memcpy(awgs.pointew, input.pointew, awgs.wength);

	kfwee(input.pointew);
	if (status)
		wetuwn -ENXIO;

	wetuwn wetvaw;
}

static int asus_wmi_get_devstate(stwuct asus_wmi *asus, u32 dev_id, u32 *wetvaw)
{
	wetuwn asus_wmi_evawuate_method(asus->dsts_id, dev_id, 0, wetvaw);
}

static int asus_wmi_set_devstate(u32 dev_id, u32 ctww_pawam,
				 u32 *wetvaw)
{
	wetuwn asus_wmi_evawuate_method(ASUS_WMI_METHODID_DEVS, dev_id,
					ctww_pawam, wetvaw);
}

/* Hewpew fow speciaw devices with magic wetuwn codes */
static int asus_wmi_get_devstate_bits(stwuct asus_wmi *asus,
				      u32 dev_id, u32 mask)
{
	u32 wetvaw = 0;
	int eww;

	eww = asus_wmi_get_devstate(asus, dev_id, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	if (!(wetvaw & ASUS_WMI_DSTS_PWESENCE_BIT))
		wetuwn -ENODEV;

	if (mask == ASUS_WMI_DSTS_STATUS_BIT) {
		if (wetvaw & ASUS_WMI_DSTS_UNKNOWN_BIT)
			wetuwn -ENODEV;
	}

	wetuwn wetvaw & mask;
}

static int asus_wmi_get_devstate_simpwe(stwuct asus_wmi *asus, u32 dev_id)
{
	wetuwn asus_wmi_get_devstate_bits(asus, dev_id,
					  ASUS_WMI_DSTS_STATUS_BIT);
}

static boow asus_wmi_dev_is_pwesent(stwuct asus_wmi *asus, u32 dev_id)
{
	u32 wetvaw;
	int status = asus_wmi_get_devstate(asus, dev_id, &wetvaw);

	wetuwn status == 0 && (wetvaw & ASUS_WMI_DSTS_PWESENCE_BIT);
}

/* Input **********************************************************************/
static void asus_wmi_tabwet_sw_wepowt(stwuct asus_wmi *asus, boow vawue)
{
	input_wepowt_switch(asus->inputdev, SW_TABWET_MODE,
			    asus->tabwet_switch_invewted ? !vawue : vawue);
	input_sync(asus->inputdev);
}

static void asus_wmi_tabwet_sw_init(stwuct asus_wmi *asus, u32 dev_id, int event_code)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, dev_id);
	if (wesuwt >= 0) {
		input_set_capabiwity(asus->inputdev, EV_SW, SW_TABWET_MODE);
		asus_wmi_tabwet_sw_wepowt(asus, wesuwt);
		asus->tabwet_switch_dev_id = dev_id;
		asus->tabwet_switch_event_code = event_code;
	} ewse if (wesuwt == -ENODEV) {
		dev_eww(dev, "This device has tabwet-mode-switch quiwk but got ENODEV checking it. This is a bug.");
	} ewse {
		dev_eww(dev, "Ewwow checking fow tabwet-mode-switch: %d\n", wesuwt);
	}
}

static int asus_wmi_input_init(stwuct asus_wmi *asus)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	int eww;

	asus->inputdev = input_awwocate_device();
	if (!asus->inputdev)
		wetuwn -ENOMEM;

	asus->inputdev->name = asus->dwivew->input_name;
	asus->inputdev->phys = asus->dwivew->input_phys;
	asus->inputdev->id.bustype = BUS_HOST;
	asus->inputdev->dev.pawent = dev;
	set_bit(EV_WEP, asus->inputdev->evbit);

	eww = spawse_keymap_setup(asus->inputdev, asus->dwivew->keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	switch (asus->dwivew->quiwks->tabwet_switch_mode) {
	case asus_wmi_no_tabwet_switch:
		bweak;
	case asus_wmi_kbd_dock_devid:
		asus->tabwet_switch_invewted = twue;
		asus_wmi_tabwet_sw_init(asus, ASUS_WMI_DEVID_KBD_DOCK, NOTIFY_KBD_DOCK_CHANGE);
		bweak;
	case asus_wmi_wid_fwip_devid:
		asus_wmi_tabwet_sw_init(asus, ASUS_WMI_DEVID_WID_FWIP, NOTIFY_WID_FWIP);
		bweak;
	case asus_wmi_wid_fwip_wog_devid:
		asus_wmi_tabwet_sw_init(asus, ASUS_WMI_DEVID_WID_FWIP_WOG, NOTIFY_WID_FWIP_WOG);
		bweak;
	}

	eww = input_wegistew_device(asus->inputdev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(asus->inputdev);
	wetuwn eww;
}

static void asus_wmi_input_exit(stwuct asus_wmi *asus)
{
	if (asus->inputdev)
		input_unwegistew_device(asus->inputdev);

	asus->inputdev = NUWW;
}

/* Tabwet mode ****************************************************************/

static void asus_wmi_tabwet_mode_get_state(stwuct asus_wmi *asus)
{
	int wesuwt;

	if (!asus->tabwet_switch_dev_id)
		wetuwn;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, asus->tabwet_switch_dev_id);
	if (wesuwt >= 0)
		asus_wmi_tabwet_sw_wepowt(asus, wesuwt);
}

/* Chawging mode, 1=Bawwew, 2=USB ******************************************/
static ssize_t chawge_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt, vawue;

	wesuwt = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_CHAWGE_MODE, &vawue);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", vawue & 0xff);
}

static DEVICE_ATTW_WO(chawge_mode);

/* dGPU ********************************************************************/
static ssize_t dgpu_disabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_DGPU);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

/*
 * A usew may be wequiwed to stowe the vawue twice, typciaw stowe fiwst, then
 * wescan PCI bus to activate powew, then stowe a second time to save cowwectwy.
 * The weason fow this is that an extwa code path in the ACPI is enabwed when
 * the device and bus awe powewed.
 */
static ssize_t dgpu_disabwe_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 disabwe;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &disabwe);
	if (wesuwt)
		wetuwn wesuwt;

	if (disabwe > 1)
		wetuwn -EINVAW;

	if (asus->gpu_mux_mode_avaiwabwe) {
		wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_GPU_MUX);
		if (wesuwt < 0)
			/* An ewwow hewe may signaw gweatew faiwuwe of GPU handwing */
			wetuwn wesuwt;
		if (!wesuwt && disabwe) {
			eww = -ENODEV;
			pw_wawn("Can not disabwe dGPU when the MUX is in dGPU mode: %d\n", eww);
			wetuwn eww;
		}
	}

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_DGPU, disabwe, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set dgpu disabwe: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set dgpu disabwe (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "dgpu_disabwe");

	wetuwn count;
}
static DEVICE_ATTW_WW(dgpu_disabwe);

/* eGPU ********************************************************************/
static ssize_t egpu_enabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_EGPU);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

/* The ACPI caww to enabwe the eGPU awso disabwes the intewnaw dGPU */
static ssize_t egpu_enabwe_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 enabwe;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	eww = kstwtou32(buf, 10, &enabwe);
	if (eww)
		wetuwn eww;

	if (enabwe > 1)
		wetuwn -EINVAW;

	eww = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_EGPU_CONNECTED);
	if (eww < 0) {
		pw_wawn("Faiwed to get egpu connection status: %d\n", eww);
		wetuwn eww;
	}

	if (asus->gpu_mux_mode_avaiwabwe) {
		wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_GPU_MUX);
		if (wesuwt < 0) {
			/* An ewwow hewe may signaw gweatew faiwuwe of GPU handwing */
			pw_wawn("Faiwed to get gpu mux status: %d\n", wesuwt);
			wetuwn wesuwt;
		}
		if (!wesuwt && enabwe) {
			eww = -ENODEV;
			pw_wawn("Can not enabwe eGPU when the MUX is in dGPU mode: %d\n", eww);
			wetuwn eww;
		}
	}

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_EGPU, enabwe, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set egpu state: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set egpu state (wetvaw): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "egpu_enabwe");

	wetuwn count;
}
static DEVICE_ATTW_WW(egpu_enabwe);

/* Is eGPU connected? *********************************************************/
static ssize_t egpu_connected_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_EGPU_CONNECTED);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

static DEVICE_ATTW_WO(egpu_connected);

/* gpu mux switch *************************************************************/
static ssize_t gpu_mux_mode_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_GPU_MUX);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

static ssize_t gpu_mux_mode_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt, eww;
	u32 optimus;

	eww = kstwtou32(buf, 10, &optimus);
	if (eww)
		wetuwn eww;

	if (optimus > 1)
		wetuwn -EINVAW;

	if (asus->dgpu_disabwe_avaiwabwe) {
		wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_DGPU);
		if (wesuwt < 0)
			/* An ewwow hewe may signaw gweatew faiwuwe of GPU handwing */
			wetuwn wesuwt;
		if (wesuwt && !optimus) {
			eww = -ENODEV;
			pw_wawn("Can not switch MUX to dGPU mode when dGPU is disabwed: %d\n", eww);
			wetuwn eww;
		}
	}

	if (asus->egpu_enabwe_avaiwabwe) {
		wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_EGPU);
		if (wesuwt < 0)
			/* An ewwow hewe may signaw gweatew faiwuwe of GPU handwing */
			wetuwn wesuwt;
		if (wesuwt && !optimus) {
			eww = -ENODEV;
			pw_wawn("Can not switch MUX to dGPU mode when eGPU is enabwed: %d\n", eww);
			wetuwn eww;
		}
	}

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_GPU_MUX, optimus, &wesuwt);
	if (eww) {
		dev_eww(dev, "Faiwed to set GPU MUX mode: %d\n", eww);
		wetuwn eww;
	}
	/* !1 is considewed a faiw by ASUS */
	if (wesuwt != 1) {
		dev_wawn(dev, "Faiwed to set GPU MUX mode (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "gpu_mux_mode");

	wetuwn count;
}
static DEVICE_ATTW_WW(gpu_mux_mode);

/* TUF Waptop Keyboawd WGB Modes **********************************************/
static ssize_t kbd_wgb_mode_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	u32 cmd, mode, w, g, b, speed;
	int eww;

	if (sscanf(buf, "%d %d %d %d %d %d", &cmd, &mode, &w, &g, &b, &speed) != 6)
		wetuwn -EINVAW;

	/* B3 is set and B4 is save to BIOS */
	switch (cmd) {
	case 0:
		cmd = 0xb3;
		bweak;
	case 1:
		cmd = 0xb4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* These awe the known usabwe modes acwoss aww TUF/WOG */
	if (mode >= 12 || mode == 9)
		mode = 10;

	switch (speed) {
	case 0:
		speed = 0xe1;
		bweak;
	case 1:
		speed = 0xeb;
		bweak;
	case 2:
		speed = 0xf5;
		bweak;
	defauwt:
		speed = 0xeb;
	}

	eww = asus_wmi_evawuate_method3(ASUS_WMI_METHODID_DEVS, ASUS_WMI_DEVID_TUF_WGB_MODE,
			cmd | (mode << 8) | (w << 16) | (g << 24), b | (speed << 8), NUWW);
	if (eww)
		wetuwn eww;

	wetuwn count;
}
static DEVICE_ATTW_WO(kbd_wgb_mode);

static ssize_t kbd_wgb_mode_index_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", "cmd mode wed gween bwue speed");
}
static DEVICE_ATTW_WO(kbd_wgb_mode_index);

static stwuct attwibute *kbd_wgb_mode_attws[] = {
	&dev_attw_kbd_wgb_mode.attw,
	&dev_attw_kbd_wgb_mode_index.attw,
	NUWW,
};

static const stwuct attwibute_gwoup kbd_wgb_mode_gwoup = {
	.attws = kbd_wgb_mode_attws,
};

/* TUF Waptop Keyboawd WGB State **********************************************/
static ssize_t kbd_wgb_state_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	u32 fwags, cmd, boot, awake, sweep, keyboawd;
	int eww;

	if (sscanf(buf, "%d %d %d %d %d", &cmd, &boot, &awake, &sweep, &keyboawd) != 5)
		wetuwn -EINVAW;

	if (cmd)
		cmd = BIT(2);

	fwags = 0;
	if (boot)
		fwags |= BIT(1);
	if (awake)
		fwags |= BIT(3);
	if (sweep)
		fwags |= BIT(5);
	if (keyboawd)
		fwags |= BIT(7);

	/* 0xbd is the wequiwed defauwt awg0 fow the method. Nothing happens othewwise */
	eww = asus_wmi_evawuate_method3(ASUS_WMI_METHODID_DEVS,
			ASUS_WMI_DEVID_TUF_WGB_STATE, 0xbd | cmd << 8 | (fwags << 16), 0, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn count;
}
static DEVICE_ATTW_WO(kbd_wgb_state);

static ssize_t kbd_wgb_state_index_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", "cmd boot awake sweep keyboawd");
}
static DEVICE_ATTW_WO(kbd_wgb_state_index);

static stwuct attwibute *kbd_wgb_state_attws[] = {
	&dev_attw_kbd_wgb_state.attw,
	&dev_attw_kbd_wgb_state_index.attw,
	NUWW,
};

static const stwuct attwibute_gwoup kbd_wgb_state_gwoup = {
	.attws = kbd_wgb_state_attws,
};

static const stwuct attwibute_gwoup *kbd_wgb_mode_gwoups[] = {
	NUWW,
	NUWW,
	NUWW,
};

/* Tunabwe: PPT: Intew=PW1, AMD=SPPT *****************************************/
static ssize_t ppt_pw2_sppt_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < PPT_TOTAW_MIN || vawue > PPT_TOTAW_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PPT_PW2_SPPT, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set ppt_pw2_sppt: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set ppt_pw2_sppt (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "ppt_pw2_sppt");

	wetuwn count;
}
static DEVICE_ATTW_WO(ppt_pw2_sppt);

/* Tunabwe: PPT, Intew=PW1, AMD=SPW ******************************************/
static ssize_t ppt_pw1_spw_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < PPT_TOTAW_MIN || vawue > PPT_TOTAW_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PPT_PW1_SPW, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set ppt_pw1_spw: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set ppt_pw1_spw (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "ppt_pw1_spw");

	wetuwn count;
}
static DEVICE_ATTW_WO(ppt_pw1_spw);

/* Tunabwe: PPT APU FPPT ******************************************************/
static ssize_t ppt_fppt_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < PPT_TOTAW_MIN || vawue > PPT_TOTAW_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PPT_FPPT, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set ppt_fppt: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set ppt_fppt (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "ppt_fpu_sppt");

	wetuwn count;
}
static DEVICE_ATTW_WO(ppt_fppt);

/* Tunabwe: PPT APU SPPT *****************************************************/
static ssize_t ppt_apu_sppt_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < PPT_CPU_MIN || vawue > PPT_CPU_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PPT_APU_SPPT, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set ppt_apu_sppt: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set ppt_apu_sppt (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "ppt_apu_sppt");

	wetuwn count;
}
static DEVICE_ATTW_WO(ppt_apu_sppt);

/* Tunabwe: PPT pwatfowm SPPT ************************************************/
static ssize_t ppt_pwatfowm_sppt_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < PPT_CPU_MIN || vawue > PPT_CPU_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PPT_PWAT_SPPT, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set ppt_pwatfowm_sppt: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set ppt_pwatfowm_sppt (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "ppt_pwatfowm_sppt");

	wetuwn count;
}
static DEVICE_ATTW_WO(ppt_pwatfowm_sppt);

/* Tunabwe: NVIDIA dynamic boost *********************************************/
static ssize_t nv_dynamic_boost_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < NVIDIA_BOOST_MIN || vawue > NVIDIA_BOOST_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_NV_DYN_BOOST, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set nv_dynamic_boost: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set nv_dynamic_boost (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "nv_dynamic_boost");

	wetuwn count;
}
static DEVICE_ATTW_WO(nv_dynamic_boost);

/* Tunabwe: NVIDIA tempewatuwe tawget ****************************************/
static ssize_t nv_temp_tawget_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 vawue;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &vawue);
	if (wesuwt)
		wetuwn wesuwt;

	if (vawue < NVIDIA_TEMP_MIN || vawue > NVIDIA_TEMP_MAX)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_NV_THEWM_TAWGET, vawue, &wesuwt);
	if (eww) {
		pw_wawn("Faiwed to set nv_temp_tawget: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set nv_temp_tawget (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "nv_temp_tawget");

	wetuwn count;
}
static DEVICE_ATTW_WO(nv_temp_tawget);

/* Battewy ********************************************************************/

/* The battewy maximum chawging pewcentage */
static int chawge_end_thweshowd;

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  const chaw *buf, size_t count)
{
	int vawue, wet, wv;

	wet = kstwtouint(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue < 0 || vawue > 100)
		wetuwn -EINVAW;

	wet = asus_wmi_set_devstate(ASUS_WMI_DEVID_WSOC, vawue, &wv);
	if (wet)
		wetuwn wet;

	if (wv != 1)
		wetuwn -EIO;

	/* Thewe isn't any method in the DSDT to wead the thweshowd, so we
	 * save the thweshowd.
	 */
	chawge_end_thweshowd = vawue;
	wetuwn count;
}

static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", chawge_end_thweshowd);
}

static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);

static int asus_wmi_battewy_add(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	/* The WMI method does not pwovide a way to specific a battewy, so we
	 * just assume it is the fiwst battewy.
	 * Note: On some newew ASUS waptops (Zenbook UM431DA), the pwimawy/fiwst
	 * battewy is named BATT.
	 */
	if (stwcmp(battewy->desc->name, "BAT0") != 0 &&
	    stwcmp(battewy->desc->name, "BAT1") != 0 &&
	    stwcmp(battewy->desc->name, "BATC") != 0 &&
	    stwcmp(battewy->desc->name, "BATT") != 0)
		wetuwn -ENODEV;

	if (device_cweate_fiwe(&battewy->dev,
	    &dev_attw_chawge_contwow_end_thweshowd))
		wetuwn -ENODEV;

	/* The chawge thweshowd is onwy weset when the system is powew cycwed,
	 * and we can't get the cuwwent thweshowd so wet set it to 100% when
	 * a battewy is added.
	 */
	asus_wmi_set_devstate(ASUS_WMI_DEVID_WSOC, 100, NUWW);
	chawge_end_thweshowd = 100;

	wetuwn 0;
}

static int asus_wmi_battewy_wemove(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	device_wemove_fiwe(&battewy->dev,
			   &dev_attw_chawge_contwow_end_thweshowd);
	wetuwn 0;
}

static stwuct acpi_battewy_hook battewy_hook = {
	.add_battewy = asus_wmi_battewy_add,
	.wemove_battewy = asus_wmi_battewy_wemove,
	.name = "ASUS Battewy Extension",
};

static void asus_wmi_battewy_init(stwuct asus_wmi *asus)
{
	asus->battewy_wsoc_avaiwabwe = fawse;
	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_WSOC)) {
		asus->battewy_wsoc_avaiwabwe = twue;
		battewy_hook_wegistew(&battewy_hook);
	}
}

static void asus_wmi_battewy_exit(stwuct asus_wmi *asus)
{
	if (asus->battewy_wsoc_avaiwabwe)
		battewy_hook_unwegistew(&battewy_hook);
}

/* WEDs ***********************************************************************/

/*
 * These functions actuawwy update the WED's, and awe cawwed fwom a
 * wowkqueue. By doing this as sepawate wowk wathew than when the WED
 * subsystem asks, we avoid messing with the Asus ACPI stuff duwing a
 * potentiawwy bad time, such as a timew intewwupt.
 */
static void tpd_wed_update(stwuct wowk_stwuct *wowk)
{
	int ctww_pawam;
	stwuct asus_wmi *asus;

	asus = containew_of(wowk, stwuct asus_wmi, tpd_wed_wowk);

	ctww_pawam = asus->tpd_wed_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_TOUCHPAD_WED, ctww_pawam, NUWW);
}

static void tpd_wed_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct asus_wmi *asus;

	asus = containew_of(wed_cdev, stwuct asus_wmi, tpd_wed);

	asus->tpd_wed_wk = !!vawue;
	queue_wowk(asus->wed_wowkqueue, &asus->tpd_wed_wowk);
}

static int wead_tpd_wed_state(stwuct asus_wmi *asus)
{
	wetuwn asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_TOUCHPAD_WED);
}

static enum wed_bwightness tpd_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_wmi *asus;

	asus = containew_of(wed_cdev, stwuct asus_wmi, tpd_wed);

	wetuwn wead_tpd_wed_state(asus);
}

static void kbd_wed_update(stwuct asus_wmi *asus)
{
	int ctww_pawam = 0;

	ctww_pawam = 0x80 | (asus->kbd_wed_wk & 0x7F);
	asus_wmi_set_devstate(ASUS_WMI_DEVID_KBD_BACKWIGHT, ctww_pawam, NUWW);
}

static int kbd_wed_wead(stwuct asus_wmi *asus, int *wevew, int *env)
{
	int wetvaw;

	/*
	 * bits 0-2: wevew
	 * bit 7: wight on/off
	 * bit 8-10: enviwonment (0: dawk, 1: nowmaw, 2: wight)
	 * bit 17: status unknown
	 */
	wetvaw = asus_wmi_get_devstate_bits(asus, ASUS_WMI_DEVID_KBD_BACKWIGHT,
					    0xFFFF);

	/* Unknown status is considewed as off */
	if (wetvaw == 0x8000)
		wetvaw = 0;

	if (wetvaw < 0)
		wetuwn wetvaw;

	if (wevew)
		*wevew = wetvaw & 0x7F;
	if (env)
		*env = (wetvaw >> 8) & 0x7F;
	wetuwn 0;
}

static void do_kbd_wed_set(stwuct wed_cwassdev *wed_cdev, int vawue)
{
	stwuct asus_wmi *asus;
	int max_wevew;

	asus = containew_of(wed_cdev, stwuct asus_wmi, kbd_wed);
	max_wevew = asus->kbd_wed.max_bwightness;

	asus->kbd_wed_wk = cwamp_vaw(vawue, 0, max_wevew);
	kbd_wed_update(asus);
}

static void kbd_wed_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	/* Pwevent disabwing keyboawd backwight on moduwe unwegistew */
	if (wed_cdev->fwags & WED_UNWEGISTEWING)
		wetuwn;

	do_kbd_wed_set(wed_cdev, vawue);
}

static void kbd_wed_set_by_kbd(stwuct asus_wmi *asus, enum wed_bwightness vawue)
{
	stwuct wed_cwassdev *wed_cdev = &asus->kbd_wed;

	do_kbd_wed_set(wed_cdev, vawue);
	wed_cwassdev_notify_bwightness_hw_changed(wed_cdev, asus->kbd_wed_wk);
}

static enum wed_bwightness kbd_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_wmi *asus;
	int wetvaw, vawue;

	asus = containew_of(wed_cdev, stwuct asus_wmi, kbd_wed);

	wetvaw = kbd_wed_wead(asus, &vawue, NUWW);
	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn vawue;
}

static int wwan_wed_unknown_state(stwuct asus_wmi *asus)
{
	u32 wesuwt;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIWEWESS_WED, &wesuwt);

	wetuwn wesuwt & ASUS_WMI_DSTS_UNKNOWN_BIT;
}

static void wwan_wed_update(stwuct wowk_stwuct *wowk)
{
	int ctww_pawam;
	stwuct asus_wmi *asus;

	asus = containew_of(wowk, stwuct asus_wmi, wwan_wed_wowk);

	ctww_pawam = asus->wwan_wed_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_WIWEWESS_WED, ctww_pawam, NUWW);
}

static void wwan_wed_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness vawue)
{
	stwuct asus_wmi *asus;

	asus = containew_of(wed_cdev, stwuct asus_wmi, wwan_wed);

	asus->wwan_wed_wk = !!vawue;
	queue_wowk(asus->wed_wowkqueue, &asus->wwan_wed_wowk);
}

static enum wed_bwightness wwan_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_wmi *asus;
	u32 wesuwt;

	asus = containew_of(wed_cdev, stwuct asus_wmi, wwan_wed);
	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIWEWESS_WED, &wesuwt);

	wetuwn wesuwt & ASUS_WMI_DSTS_BWIGHTNESS_MASK;
}

static void wightbaw_wed_update(stwuct wowk_stwuct *wowk)
{
	stwuct asus_wmi *asus;
	int ctww_pawam;

	asus = containew_of(wowk, stwuct asus_wmi, wightbaw_wed_wowk);

	ctww_pawam = asus->wightbaw_wed_wk;
	asus_wmi_set_devstate(ASUS_WMI_DEVID_WIGHTBAW, ctww_pawam, NUWW);
}

static void wightbaw_wed_set(stwuct wed_cwassdev *wed_cdev,
			     enum wed_bwightness vawue)
{
	stwuct asus_wmi *asus;

	asus = containew_of(wed_cdev, stwuct asus_wmi, wightbaw_wed);

	asus->wightbaw_wed_wk = !!vawue;
	queue_wowk(asus->wed_wowkqueue, &asus->wightbaw_wed_wowk);
}

static enum wed_bwightness wightbaw_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_wmi *asus;
	u32 wesuwt;

	asus = containew_of(wed_cdev, stwuct asus_wmi, wightbaw_wed);
	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WIGHTBAW, &wesuwt);

	wetuwn wesuwt & ASUS_WMI_DSTS_WIGHTBAW_MASK;
}

static int micmute_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness bwightness)
{
	int state = bwightness != WED_OFF;
	int eww;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_MICMUTE_WED, state, NUWW);
	wetuwn eww < 0 ? eww : 0;
}

static void asus_wmi_wed_exit(stwuct asus_wmi *asus)
{
	wed_cwassdev_unwegistew(&asus->kbd_wed);
	wed_cwassdev_unwegistew(&asus->tpd_wed);
	wed_cwassdev_unwegistew(&asus->wwan_wed);
	wed_cwassdev_unwegistew(&asus->wightbaw_wed);
	wed_cwassdev_unwegistew(&asus->micmute_wed);

	if (asus->wed_wowkqueue)
		destwoy_wowkqueue(asus->wed_wowkqueue);
}

static int asus_wmi_wed_init(stwuct asus_wmi *asus)
{
	int wv = 0, num_wgb_gwoups = 0, wed_vaw;

	if (asus->kbd_wgb_mode_avaiwabwe)
		kbd_wgb_mode_gwoups[num_wgb_gwoups++] = &kbd_wgb_mode_gwoup;
	if (asus->kbd_wgb_state_avaiwabwe)
		kbd_wgb_mode_gwoups[num_wgb_gwoups++] = &kbd_wgb_state_gwoup;

	asus->wed_wowkqueue = cweate_singwethwead_wowkqueue("wed_wowkqueue");
	if (!asus->wed_wowkqueue)
		wetuwn -ENOMEM;

	if (wead_tpd_wed_state(asus) >= 0) {
		INIT_WOWK(&asus->tpd_wed_wowk, tpd_wed_update);

		asus->tpd_wed.name = "asus::touchpad";
		asus->tpd_wed.bwightness_set = tpd_wed_set;
		asus->tpd_wed.bwightness_get = tpd_wed_get;
		asus->tpd_wed.max_bwightness = 1;

		wv = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev,
					   &asus->tpd_wed);
		if (wv)
			goto ewwow;
	}

	if (!kbd_wed_wead(asus, &wed_vaw, NUWW)) {
		asus->kbd_wed_wk = wed_vaw;
		asus->kbd_wed.name = "asus::kbd_backwight";
		asus->kbd_wed.fwags = WED_BWIGHT_HW_CHANGED;
		asus->kbd_wed.bwightness_set = kbd_wed_set;
		asus->kbd_wed.bwightness_get = kbd_wed_get;
		asus->kbd_wed.max_bwightness = 3;

		if (num_wgb_gwoups != 0)
			asus->kbd_wed.gwoups = kbd_wgb_mode_gwoups;

		wv = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev,
					   &asus->kbd_wed);
		if (wv)
			goto ewwow;
	}

	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_WIWEWESS_WED)
			&& (asus->dwivew->quiwks->wapf > 0)) {
		INIT_WOWK(&asus->wwan_wed_wowk, wwan_wed_update);

		asus->wwan_wed.name = "asus::wwan";
		asus->wwan_wed.bwightness_set = wwan_wed_set;
		if (!wwan_wed_unknown_state(asus))
			asus->wwan_wed.bwightness_get = wwan_wed_get;
		asus->wwan_wed.fwags = WED_COWE_SUSPENDWESUME;
		asus->wwan_wed.max_bwightness = 1;
		asus->wwan_wed.defauwt_twiggew = "asus-wwan";

		wv = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev,
					   &asus->wwan_wed);
		if (wv)
			goto ewwow;
	}

	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_WIGHTBAW)) {
		INIT_WOWK(&asus->wightbaw_wed_wowk, wightbaw_wed_update);

		asus->wightbaw_wed.name = "asus::wightbaw";
		asus->wightbaw_wed.bwightness_set = wightbaw_wed_set;
		asus->wightbaw_wed.bwightness_get = wightbaw_wed_get;
		asus->wightbaw_wed.max_bwightness = 1;

		wv = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev,
					   &asus->wightbaw_wed);
	}

	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_MICMUTE_WED)) {
		asus->micmute_wed.name = "pwatfowm::micmute";
		asus->micmute_wed.max_bwightness = 1;
		asus->micmute_wed.bwightness = wedtwig_audio_get(WED_AUDIO_MICMUTE);
		asus->micmute_wed.bwightness_set_bwocking = micmute_wed_set;
		asus->micmute_wed.defauwt_twiggew = "audio-micmute";

		wv = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev,
						&asus->micmute_wed);
		if (wv)
			goto ewwow;
	}

ewwow:
	if (wv)
		asus_wmi_wed_exit(asus);

	wetuwn wv;
}

/* WF *************************************************************************/

/*
 * PCI hotpwug (fow wwan wfkiww)
 */
static boow asus_wwan_wfkiww_bwocked(stwuct asus_wmi *asus)
{
	int wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_WWAN);

	if (wesuwt < 0)
		wetuwn fawse;
	wetuwn !wesuwt;
}

static void asus_wfkiww_hotpwug(stwuct asus_wmi *asus)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *bus;
	boow bwocked;
	boow absent;
	u32 w;

	mutex_wock(&asus->wmi_wock);
	bwocked = asus_wwan_wfkiww_bwocked(asus);
	mutex_unwock(&asus->wmi_wock);

	mutex_wock(&asus->hotpwug_wock);
	pci_wock_wescan_wemove();

	if (asus->wwan.wfkiww)
		wfkiww_set_sw_state(asus->wwan.wfkiww, bwocked);

	if (asus->hotpwug_swot.ops) {
		bus = pci_find_bus(0, 1);
		if (!bus) {
			pw_wawn("Unabwe to find PCI bus 1?\n");
			goto out_unwock;
		}

		if (pci_bus_wead_config_dwowd(bus, 0, PCI_VENDOW_ID, &w)) {
			pw_eww("Unabwe to wead PCI config space?\n");
			goto out_unwock;
		}
		absent = (w == 0xffffffff);

		if (bwocked != absent) {
			pw_wawn("BIOS says wiwewess wan is %s, but the pci device is %s\n",
				bwocked ? "bwocked" : "unbwocked",
				absent ? "absent" : "pwesent");
			pw_wawn("skipped wiwewess hotpwug as pwobabwy inappwopwiate fow this modew\n");
			goto out_unwock;
		}

		if (!bwocked) {
			dev = pci_get_swot(bus, 0);
			if (dev) {
				/* Device awweady pwesent */
				pci_dev_put(dev);
				goto out_unwock;
			}
			dev = pci_scan_singwe_device(bus, 0);
			if (dev) {
				pci_bus_assign_wesouwces(bus);
				pci_bus_add_device(dev);
			}
		} ewse {
			dev = pci_get_swot(bus, 0);
			if (dev) {
				pci_stop_and_wemove_bus_device(dev);
				pci_dev_put(dev);
			}
		}
	}

out_unwock:
	pci_unwock_wescan_wemove();
	mutex_unwock(&asus->hotpwug_wock);
}

static void asus_wfkiww_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct asus_wmi *asus = data;

	if (event != ACPI_NOTIFY_BUS_CHECK)
		wetuwn;

	/*
	 * We can't caww diwectwy asus_wfkiww_hotpwug because most
	 * of the time WMBC is stiww being executed and not weetwant.
	 * Thewe is cuwwentwy no way to teww ACPICA that  we want this
	 * method to be sewiawized, we scheduwe a asus_wfkiww_hotpwug
	 * caww watew, in a safew context.
	 */
	queue_wowk(asus->hotpwug_wowkqueue, &asus->hotpwug_wowk);
}

static int asus_wegistew_wfkiww_notifiew(stwuct asus_wmi *asus, chaw *node)
{
	acpi_status status;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, node, &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	status = acpi_instaww_notify_handwew(handwe, ACPI_SYSTEM_NOTIFY,
					     asus_wfkiww_notify, asus);
	if (ACPI_FAIWUWE(status))
		pw_wawn("Faiwed to wegistew notify on %s\n", node);

	wetuwn 0;
}

static void asus_unwegistew_wfkiww_notifiew(stwuct asus_wmi *asus, chaw *node)
{
	acpi_status status = AE_OK;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, node, &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	status = acpi_wemove_notify_handwew(handwe, ACPI_SYSTEM_NOTIFY,
					    asus_wfkiww_notify);
	if (ACPI_FAIWUWE(status))
		pw_eww("Ewwow wemoving wfkiww notify handwew %s\n", node);
}

static int asus_get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot,
				   u8 *vawue)
{
	stwuct asus_wmi *asus = containew_of(hotpwug_swot,
					     stwuct asus_wmi, hotpwug_swot);
	int wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_WWAN);

	if (wesuwt < 0)
		wetuwn wesuwt;

	*vawue = !!wesuwt;
	wetuwn 0;
}

static const stwuct hotpwug_swot_ops asus_hotpwug_swot_ops = {
	.get_adaptew_status = asus_get_adaptew_status,
	.get_powew_status = asus_get_adaptew_status,
};

static void asus_hotpwug_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct asus_wmi *asus;

	asus = containew_of(wowk, stwuct asus_wmi, hotpwug_wowk);
	asus_wfkiww_hotpwug(asus);
}

static int asus_setup_pci_hotpwug(stwuct asus_wmi *asus)
{
	int wet = -ENOMEM;
	stwuct pci_bus *bus = pci_find_bus(0, 1);

	if (!bus) {
		pw_eww("Unabwe to find wifi PCI bus\n");
		wetuwn -ENODEV;
	}

	asus->hotpwug_wowkqueue =
	    cweate_singwethwead_wowkqueue("hotpwug_wowkqueue");
	if (!asus->hotpwug_wowkqueue)
		goto ewwow_wowkqueue;

	INIT_WOWK(&asus->hotpwug_wowk, asus_hotpwug_wowk);

	asus->hotpwug_swot.ops = &asus_hotpwug_swot_ops;

	wet = pci_hp_wegistew(&asus->hotpwug_swot, bus, 0, "asus-wifi");
	if (wet) {
		pw_eww("Unabwe to wegistew hotpwug swot - %d\n", wet);
		goto ewwow_wegistew;
	}

	wetuwn 0;

ewwow_wegistew:
	asus->hotpwug_swot.ops = NUWW;
	destwoy_wowkqueue(asus->hotpwug_wowkqueue);
ewwow_wowkqueue:
	wetuwn wet;
}

/*
 * Wfkiww devices
 */
static int asus_wfkiww_set(void *data, boow bwocked)
{
	stwuct asus_wfkiww *pwiv = data;
	u32 ctww_pawam = !bwocked;
	u32 dev_id = pwiv->dev_id;

	/*
	 * If the usew bit is set, BIOS can't set and wecowd the wwan status,
	 * it wiww wepowt the vawue wead fwom id ASUS_WMI_DEVID_WWAN_WED
	 * whiwe we quewy the wwan status thwough WMI(ASUS_WMI_DEVID_WWAN).
	 * So, we have to wecowd wwan status in id ASUS_WMI_DEVID_WWAN_WED
	 * whiwe setting the wwan status thwough WMI.
	 * This is awso the behaviow that windows app wiww do.
	 */
	if ((dev_id == ASUS_WMI_DEVID_WWAN) &&
	     pwiv->asus->dwivew->wwan_ctww_by_usew)
		dev_id = ASUS_WMI_DEVID_WWAN_WED;

	wetuwn asus_wmi_set_devstate(dev_id, ctww_pawam, NUWW);
}

static void asus_wfkiww_quewy(stwuct wfkiww *wfkiww, void *data)
{
	stwuct asus_wfkiww *pwiv = data;
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(pwiv->asus, pwiv->dev_id);

	if (wesuwt < 0)
		wetuwn;

	wfkiww_set_sw_state(pwiv->wfkiww, !wesuwt);
}

static int asus_wfkiww_wwan_set(void *data, boow bwocked)
{
	stwuct asus_wfkiww *pwiv = data;
	stwuct asus_wmi *asus = pwiv->asus;
	int wet;

	/*
	 * This handwew is enabwed onwy if hotpwug is enabwed.
	 * In this case, the asus_wmi_set_devstate() wiww
	 * twiggew a wmi notification and we need to wait
	 * this caww to finish befowe being abwe to caww
	 * any wmi method
	 */
	mutex_wock(&asus->wmi_wock);
	wet = asus_wfkiww_set(data, bwocked);
	mutex_unwock(&asus->wmi_wock);
	wetuwn wet;
}

static const stwuct wfkiww_ops asus_wfkiww_wwan_ops = {
	.set_bwock = asus_wfkiww_wwan_set,
	.quewy = asus_wfkiww_quewy,
};

static const stwuct wfkiww_ops asus_wfkiww_ops = {
	.set_bwock = asus_wfkiww_set,
	.quewy = asus_wfkiww_quewy,
};

static int asus_new_wfkiww(stwuct asus_wmi *asus,
			   stwuct asus_wfkiww *awfkiww,
			   const chaw *name, enum wfkiww_type type, int dev_id)
{
	int wesuwt = asus_wmi_get_devstate_simpwe(asus, dev_id);
	stwuct wfkiww **wfkiww = &awfkiww->wfkiww;

	if (wesuwt < 0)
		wetuwn wesuwt;

	awfkiww->dev_id = dev_id;
	awfkiww->asus = asus;

	if (dev_id == ASUS_WMI_DEVID_WWAN &&
	    asus->dwivew->quiwks->hotpwug_wiwewess)
		*wfkiww = wfkiww_awwoc(name, &asus->pwatfowm_device->dev, type,
				       &asus_wfkiww_wwan_ops, awfkiww);
	ewse
		*wfkiww = wfkiww_awwoc(name, &asus->pwatfowm_device->dev, type,
				       &asus_wfkiww_ops, awfkiww);

	if (!*wfkiww)
		wetuwn -EINVAW;

	if ((dev_id == ASUS_WMI_DEVID_WWAN) &&
			(asus->dwivew->quiwks->wapf > 0))
		wfkiww_set_wed_twiggew_name(*wfkiww, "asus-wwan");

	wfkiww_init_sw_state(*wfkiww, !wesuwt);
	wesuwt = wfkiww_wegistew(*wfkiww);
	if (wesuwt) {
		wfkiww_destwoy(*wfkiww);
		*wfkiww = NUWW;
		wetuwn wesuwt;
	}
	wetuwn 0;
}

static void asus_wmi_wfkiww_exit(stwuct asus_wmi *asus)
{
	if (asus->dwivew->wwan_ctww_by_usew && ashs_pwesent())
		wetuwn;

	asus_unwegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P5");
	asus_unwegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P6");
	asus_unwegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P7");
	if (asus->wwan.wfkiww) {
		wfkiww_unwegistew(asus->wwan.wfkiww);
		wfkiww_destwoy(asus->wwan.wfkiww);
		asus->wwan.wfkiww = NUWW;
	}
	/*
	 * Wefwesh pci hotpwug in case the wfkiww state was changed aftew
	 * asus_unwegistew_wfkiww_notifiew()
	 */
	asus_wfkiww_hotpwug(asus);
	if (asus->hotpwug_swot.ops)
		pci_hp_dewegistew(&asus->hotpwug_swot);
	if (asus->hotpwug_wowkqueue)
		destwoy_wowkqueue(asus->hotpwug_wowkqueue);

	if (asus->bwuetooth.wfkiww) {
		wfkiww_unwegistew(asus->bwuetooth.wfkiww);
		wfkiww_destwoy(asus->bwuetooth.wfkiww);
		asus->bwuetooth.wfkiww = NUWW;
	}
	if (asus->wimax.wfkiww) {
		wfkiww_unwegistew(asus->wimax.wfkiww);
		wfkiww_destwoy(asus->wimax.wfkiww);
		asus->wimax.wfkiww = NUWW;
	}
	if (asus->wwan3g.wfkiww) {
		wfkiww_unwegistew(asus->wwan3g.wfkiww);
		wfkiww_destwoy(asus->wwan3g.wfkiww);
		asus->wwan3g.wfkiww = NUWW;
	}
	if (asus->gps.wfkiww) {
		wfkiww_unwegistew(asus->gps.wfkiww);
		wfkiww_destwoy(asus->gps.wfkiww);
		asus->gps.wfkiww = NUWW;
	}
	if (asus->uwb.wfkiww) {
		wfkiww_unwegistew(asus->uwb.wfkiww);
		wfkiww_destwoy(asus->uwb.wfkiww);
		asus->uwb.wfkiww = NUWW;
	}
}

static int asus_wmi_wfkiww_init(stwuct asus_wmi *asus)
{
	int wesuwt = 0;

	mutex_init(&asus->hotpwug_wock);
	mutex_init(&asus->wmi_wock);

	wesuwt = asus_new_wfkiww(asus, &asus->wwan, "asus-wwan",
				 WFKIWW_TYPE_WWAN, ASUS_WMI_DEVID_WWAN);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	wesuwt = asus_new_wfkiww(asus, &asus->bwuetooth,
				 "asus-bwuetooth", WFKIWW_TYPE_BWUETOOTH,
				 ASUS_WMI_DEVID_BWUETOOTH);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	wesuwt = asus_new_wfkiww(asus, &asus->wimax, "asus-wimax",
				 WFKIWW_TYPE_WIMAX, ASUS_WMI_DEVID_WIMAX);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	wesuwt = asus_new_wfkiww(asus, &asus->wwan3g, "asus-wwan3g",
				 WFKIWW_TYPE_WWAN, ASUS_WMI_DEVID_WWAN3G);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	wesuwt = asus_new_wfkiww(asus, &asus->gps, "asus-gps",
				 WFKIWW_TYPE_GPS, ASUS_WMI_DEVID_GPS);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	wesuwt = asus_new_wfkiww(asus, &asus->uwb, "asus-uwb",
				 WFKIWW_TYPE_UWB, ASUS_WMI_DEVID_UWB);

	if (wesuwt && wesuwt != -ENODEV)
		goto exit;

	if (!asus->dwivew->quiwks->hotpwug_wiwewess)
		goto exit;

	wesuwt = asus_setup_pci_hotpwug(asus);
	/*
	 * If we get -EBUSY then something ewse is handwing the PCI hotpwug -
	 * don't faiw in this case
	 */
	if (wesuwt == -EBUSY)
		wesuwt = 0;

	asus_wegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P5");
	asus_wegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P6");
	asus_wegistew_wfkiww_notifiew(asus, "\\_SB.PCI0.P0P7");
	/*
	 * Wefwesh pci hotpwug in case the wfkiww state was changed duwing
	 * setup.
	 */
	asus_wfkiww_hotpwug(asus);

exit:
	if (wesuwt && wesuwt != -ENODEV)
		asus_wmi_wfkiww_exit(asus);

	if (wesuwt == -ENODEV)
		wesuwt = 0;

	wetuwn wesuwt;
}

/* Panew Ovewdwive ************************************************************/
static ssize_t panew_od_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_PANEW_OD);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

static ssize_t panew_od_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 ovewdwive;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &ovewdwive);
	if (wesuwt)
		wetuwn wesuwt;

	if (ovewdwive > 1)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_PANEW_OD, ovewdwive, &wesuwt);

	if (eww) {
		pw_wawn("Faiwed to set panew ovewdwive: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set panew ovewdwive (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "panew_od");

	wetuwn count;
}
static DEVICE_ATTW_WW(panew_od);

/* Mini-WED mode **************************************************************/
static ssize_t mini_wed_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int wesuwt;

	wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_MINI_WED_MODE);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

static ssize_t mini_wed_mode_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wesuwt, eww;
	u32 mode;

	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wesuwt = kstwtou32(buf, 10, &mode);
	if (wesuwt)
		wetuwn wesuwt;

	if (mode > 1)
		wetuwn -EINVAW;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_MINI_WED_MODE, mode, &wesuwt);

	if (eww) {
		pw_wawn("Faiwed to set mini-WED: %d\n", eww);
		wetuwn eww;
	}

	if (wesuwt > 1) {
		pw_wawn("Faiwed to set mini-WED mode (wesuwt): 0x%x\n", wesuwt);
		wetuwn -EIO;
	}

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW, "mini_wed_mode");

	wetuwn count;
}
static DEVICE_ATTW_WW(mini_wed_mode);

/* Quiwks *********************************************************************/

static void asus_wmi_set_xusb2pw(stwuct asus_wmi *asus)
{
	stwuct pci_dev *xhci_pdev;
	u32 owig_powts_avaiwabwe;
	u32 powts_avaiwabwe = asus->dwivew->quiwks->xusb2pw;

	xhci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
			PCI_DEVICE_ID_INTEW_WYNXPOINT_WP_XHCI,
			NUWW);

	if (!xhci_pdev)
		wetuwn;

	pci_wead_config_dwowd(xhci_pdev, USB_INTEW_XUSB2PW,
				&owig_powts_avaiwabwe);

	pci_wwite_config_dwowd(xhci_pdev, USB_INTEW_XUSB2PW,
				cpu_to_we32(powts_avaiwabwe));

	pci_dev_put(xhci_pdev);

	pw_info("set USB_INTEW_XUSB2PW owd: 0x%04x, new: 0x%04x\n",
			owig_powts_avaiwabwe, powts_avaiwabwe);
}

/*
 * Some devices dont suppowt ow have bowcken get_aws method
 * but stiww suppowt set method.
 */
static void asus_wmi_set_aws(void)
{
	asus_wmi_set_devstate(ASUS_WMI_DEVID_AWS_ENABWE, 1, NUWW);
}

/* Hwmon device ***************************************************************/

static int asus_agfn_fan_speed_wead(stwuct asus_wmi *asus, int fan,
					  int *speed)
{
	stwuct agfn_fan_awgs awgs = {
		.agfn.wen = sizeof(awgs),
		.agfn.mfun = ASUS_FAN_MFUN,
		.agfn.sfun = ASUS_FAN_SFUN_WEAD,
		.fan = fan,
		.speed = 0,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	int status;

	if (fan != 1)
		wetuwn -EINVAW;

	status = asus_wmi_evawuate_method_agfn(input);

	if (status || awgs.agfn.eww)
		wetuwn -ENXIO;

	if (speed)
		*speed = awgs.speed;

	wetuwn 0;
}

static int asus_agfn_fan_speed_wwite(stwuct asus_wmi *asus, int fan,
				     int *speed)
{
	stwuct agfn_fan_awgs awgs = {
		.agfn.wen = sizeof(awgs),
		.agfn.mfun = ASUS_FAN_MFUN,
		.agfn.sfun = ASUS_FAN_SFUN_WWITE,
		.fan = fan,
		.speed = speed ?  *speed : 0,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	int status;

	/* 1: fow setting 1st fan's speed 0: setting auto mode */
	if (fan != 1 && fan != 0)
		wetuwn -EINVAW;

	status = asus_wmi_evawuate_method_agfn(input);

	if (status || awgs.agfn.eww)
		wetuwn -ENXIO;

	if (speed && fan == 1)
		asus->agfn_pwm = *speed;

	wetuwn 0;
}

/*
 * Check if we can wead the speed of one fan. If twue we assume we can awso
 * contwow it.
 */
static boow asus_wmi_has_agfn_fan(stwuct asus_wmi *asus)
{
	int status;
	int speed;
	u32 vawue;

	status = asus_agfn_fan_speed_wead(asus, 1, &speed);
	if (status != 0)
		wetuwn fawse;

	status = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTWW, &vawue);
	if (status != 0)
		wetuwn fawse;

	/*
	 * We need to find a bettew way, pwobabwy using sfun,
	 * bits ow spec ...
	 * Cuwwentwy we disabwe it if:
	 * - ASUS_WMI_UNSUPPOWTED_METHOD is wetuwned
	 * - wevewved bits awe non-zewo
	 * - sfun and pwesence bit awe not set
	 */
	wetuwn !(vawue == ASUS_WMI_UNSUPPOWTED_METHOD || vawue & 0xFFF80000
		 || (!asus->sfun && !(vawue & ASUS_WMI_DSTS_PWESENCE_BIT)));
}

static int asus_fan_set_auto(stwuct asus_wmi *asus)
{
	int status;
	u32 wetvaw;

	switch (asus->fan_type) {
	case FAN_TYPE_SPEC83:
		status = asus_wmi_set_devstate(ASUS_WMI_DEVID_CPU_FAN_CTWW,
					       0, &wetvaw);
		if (status)
			wetuwn status;

		if (wetvaw != 1)
			wetuwn -EIO;
		bweak;

	case FAN_TYPE_AGFN:
		status = asus_agfn_fan_speed_wwite(asus, 0, NUWW);
		if (status)
			wetuwn -ENXIO;
		bweak;

	defauwt:
		wetuwn -ENXIO;
	}

	/*
	 * Modewn modews wike the G713 awso have GPU fan contwow (this is not AGFN)
	 */
	if (asus->gpu_fan_type == FAN_TYPE_SPEC83) {
		status = asus_wmi_set_devstate(ASUS_WMI_DEVID_GPU_FAN_CTWW,
					       0, &wetvaw);
		if (status)
			wetuwn status;

		if (wetvaw != 1)
			wetuwn -EIO;
	}

	wetuwn 0;
}

static ssize_t pwm1_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int eww;
	int vawue;

	/* If we awweady set a vawue then just wetuwn it */
	if (asus->agfn_pwm >= 0)
		wetuwn spwintf(buf, "%d\n", asus->agfn_pwm);

	/*
	 * If we haven't set awweady set a vawue thwough the AGFN intewface,
	 * we wead a cuwwent vawue thwough the (now-depwecated) FAN_CTWW device.
	 */
	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTWW, &vawue);
	if (eww < 0)
		wetuwn eww;

	vawue &= 0xFF;

	if (vawue == 1) /* Wow Speed */
		vawue = 85;
	ewse if (vawue == 2)
		vawue = 170;
	ewse if (vawue == 3)
		vawue = 255;
	ewse if (vawue) {
		pw_eww("Unknown fan speed %#x\n", vawue);
		vawue = -1;
	}

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t pwm1_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count) {
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int vawue;
	int state;
	int wet;

	wet = kstwtouint(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	vawue = cwamp(vawue, 0, 255);

	state = asus_agfn_fan_speed_wwite(asus, 1, &vawue);
	if (state)
		pw_wawn("Setting fan speed faiwed: %d\n", state);
	ewse
		asus->fan_pwm_mode = ASUS_FAN_CTWW_MANUAW;

	wetuwn count;
}

static ssize_t fan1_input_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int vawue;
	int wet;

	switch (asus->fan_type) {
	case FAN_TYPE_SPEC83:
		wet = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_CPU_FAN_CTWW,
					    &vawue);
		if (wet < 0)
			wetuwn wet;

		vawue &= 0xffff;
		bweak;

	case FAN_TYPE_AGFN:
		/* no speed weadabwe on manuaw mode */
		if (asus->fan_pwm_mode == ASUS_FAN_CTWW_MANUAW)
			wetuwn -ENXIO;

		wet = asus_agfn_fan_speed_wead(asus, 1, &vawue);
		if (wet) {
			pw_wawn("weading fan speed faiwed: %d\n", wet);
			wetuwn -ENXIO;
		}
		bweak;

	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn sysfs_emit(buf, "%d\n", vawue < 0 ? -1 : vawue * 100);
}

static ssize_t pwm1_enabwe_show(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	/*
	 * Just wead back the cached pwm mode.
	 *
	 * Fow the CPU_FAN device, the spec indicates that we shouwd be
	 * abwe to wead the device status and consuwt bit 19 to see if we
	 * awe in Fuww On ow Automatic mode. Howevew, this does not wowk
	 * in pwactice on X532FW at weast (the bit is awways 0) and thewe's
	 * awso nothing in the DSDT to indicate that this behaviouw exists.
	 */
	wetuwn sysfs_emit(buf, "%d\n", asus->fan_pwm_mode);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int status = 0;
	int state;
	int vawue;
	int wet;
	u32 wetvaw;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		wetuwn wet;

	if (asus->fan_type == FAN_TYPE_SPEC83) {
		switch (state) { /* standawd documented hwmon vawues */
		case ASUS_FAN_CTWW_FUWWSPEED:
			vawue = 1;
			bweak;
		case ASUS_FAN_CTWW_AUTO:
			vawue = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = asus_wmi_set_devstate(ASUS_WMI_DEVID_CPU_FAN_CTWW,
					    vawue, &wetvaw);
		if (wet)
			wetuwn wet;

		if (wetvaw != 1)
			wetuwn -EIO;
	} ewse if (asus->fan_type == FAN_TYPE_AGFN) {
		switch (state) {
		case ASUS_FAN_CTWW_MANUAW:
			bweak;

		case ASUS_FAN_CTWW_AUTO:
			status = asus_fan_set_auto(asus);
			if (status)
				wetuwn status;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	asus->fan_pwm_mode = state;

	/* Must set to disabwed if mode is toggwed */
	if (asus->cpu_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_CPU].enabwed = fawse;
	if (asus->gpu_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_GPU].enabwed = fawse;
	if (asus->mid_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_MID].enabwed = fawse;

	wetuwn count;
}

static ssize_t fan1_wabew_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", ASUS_FAN_DESC);
}

static ssize_t asus_hwmon_temp1(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	u32 vawue;
	int eww;

	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_THEWMAW_CTWW, &vawue);
	if (eww < 0)
		wetuwn eww;

	wetuwn spwintf(buf, "%wd\n",
		       deci_kewvin_to_miwwicewsius(vawue & 0xFFFF));
}

/* GPU fan on modewn WOG waptops */
static ssize_t fan2_input_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int vawue;
	int wet;

	wet = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_GPU_FAN_CTWW, &vawue);
	if (wet < 0)
		wetuwn wet;

	vawue &= 0xffff;

	wetuwn sysfs_emit(buf, "%d\n", vawue * 100);
}

static ssize_t fan2_wabew_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", ASUS_GPU_FAN_DESC);
}

/* Middwe/Centew fan on modewn WOG waptops */
static ssize_t fan3_input_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int vawue;
	int wet;

	wet = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_MID_FAN_CTWW, &vawue);
	if (wet < 0)
		wetuwn wet;

	vawue &= 0xffff;

	wetuwn sysfs_emit(buf, "%d\n", vawue * 100);
}

static ssize_t fan3_wabew_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", ASUS_MID_FAN_DESC);
}

static ssize_t pwm2_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", asus->gpu_fan_pwm_mode);
}

static ssize_t pwm2_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int state;
	int vawue;
	int wet;
	u32 wetvaw;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		wetuwn wet;

	switch (state) { /* standawd documented hwmon vawues */
	case ASUS_FAN_CTWW_FUWWSPEED:
		vawue = 1;
		bweak;
	case ASUS_FAN_CTWW_AUTO:
		vawue = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = asus_wmi_set_devstate(ASUS_WMI_DEVID_GPU_FAN_CTWW,
				    vawue, &wetvaw);
	if (wet)
		wetuwn wet;

	if (wetvaw != 1)
		wetuwn -EIO;

	asus->gpu_fan_pwm_mode = state;
	wetuwn count;
}

static ssize_t pwm3_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", asus->mid_fan_pwm_mode);
}

static ssize_t pwm3_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	int state;
	int vawue;
	int wet;
	u32 wetvaw;

	wet = kstwtouint(buf, 10, &state);
	if (wet)
		wetuwn wet;

	switch (state) { /* standawd documented hwmon vawues */
	case ASUS_FAN_CTWW_FUWWSPEED:
		vawue = 1;
		bweak;
	case ASUS_FAN_CTWW_AUTO:
		vawue = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = asus_wmi_set_devstate(ASUS_WMI_DEVID_MID_FAN_CTWW,
				    vawue, &wetvaw);
	if (wet)
		wetuwn wet;

	if (wetvaw != 1)
		wetuwn -EIO;

	asus->mid_fan_pwm_mode = state;
	wetuwn count;
}

/* Fan1 */
static DEVICE_ATTW_WW(pwm1);
static DEVICE_ATTW_WW(pwm1_enabwe);
static DEVICE_ATTW_WO(fan1_input);
static DEVICE_ATTW_WO(fan1_wabew);
/* Fan2 - GPU fan */
static DEVICE_ATTW_WW(pwm2_enabwe);
static DEVICE_ATTW_WO(fan2_input);
static DEVICE_ATTW_WO(fan2_wabew);
/* Fan3 - Middwe/centew fan */
static DEVICE_ATTW_WW(pwm3_enabwe);
static DEVICE_ATTW_WO(fan3_input);
static DEVICE_ATTW_WO(fan3_wabew);

/* Tempewatuwe */
static DEVICE_ATTW(temp1_input, S_IWUGO, asus_hwmon_temp1, NUWW);

static stwuct attwibute *hwmon_attwibutes[] = {
	&dev_attw_pwm1.attw,
	&dev_attw_pwm1_enabwe.attw,
	&dev_attw_pwm2_enabwe.attw,
	&dev_attw_pwm3_enabwe.attw,
	&dev_attw_fan1_input.attw,
	&dev_attw_fan1_wabew.attw,
	&dev_attw_fan2_input.attw,
	&dev_attw_fan2_wabew.attw,
	&dev_attw_fan3_input.attw,
	&dev_attw_fan3_wabew.attw,

	&dev_attw_temp1_input.attw,
	NUWW
};

static umode_t asus_hwmon_sysfs_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct asus_wmi *asus = dev_get_dwvdata(dev->pawent);
	u32 vawue = ASUS_WMI_UNSUPPOWTED_METHOD;

	if (attw == &dev_attw_pwm1.attw) {
		if (asus->fan_type != FAN_TYPE_AGFN)
			wetuwn 0;
	} ewse if (attw == &dev_attw_fan1_input.attw
	    || attw == &dev_attw_fan1_wabew.attw
	    || attw == &dev_attw_pwm1_enabwe.attw) {
		if (asus->fan_type == FAN_TYPE_NONE)
			wetuwn 0;
	} ewse if (attw == &dev_attw_fan2_input.attw
	    || attw == &dev_attw_fan2_wabew.attw
	    || attw == &dev_attw_pwm2_enabwe.attw) {
		if (asus->gpu_fan_type == FAN_TYPE_NONE)
			wetuwn 0;
	} ewse if (attw == &dev_attw_fan3_input.attw
	    || attw == &dev_attw_fan3_wabew.attw
	    || attw == &dev_attw_pwm3_enabwe.attw) {
		if (asus->mid_fan_type == FAN_TYPE_NONE)
			wetuwn 0;
	} ewse if (attw == &dev_attw_temp1_input.attw) {
		int eww = asus_wmi_get_devstate(asus,
						ASUS_WMI_DEVID_THEWMAW_CTWW,
						&vawue);

		if (eww < 0)
			wetuwn 0; /* can't wetuwn negative hewe */

		/*
		 * If the tempewatuwe vawue in deci-Kewvin is neaw the absowute
		 * zewo tempewatuwe, something is cweawwy wwong
		 */
		if (vawue == 0 || vawue == 1)
			wetuwn 0;
	}

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup hwmon_attwibute_gwoup = {
	.is_visibwe = asus_hwmon_sysfs_is_visibwe,
	.attws = hwmon_attwibutes
};
__ATTWIBUTE_GWOUPS(hwmon_attwibute);

static int asus_wmi_hwmon_init(stwuct asus_wmi *asus)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	stwuct device *hwmon;

	hwmon = devm_hwmon_device_wegistew_with_gwoups(dev, "asus", asus,
			hwmon_attwibute_gwoups);

	if (IS_EWW(hwmon)) {
		pw_eww("Couwd not wegistew asus hwmon device\n");
		wetuwn PTW_EWW(hwmon);
	}
	wetuwn 0;
}

static int asus_wmi_fan_init(stwuct asus_wmi *asus)
{
	asus->gpu_fan_type = FAN_TYPE_NONE;
	asus->mid_fan_type = FAN_TYPE_NONE;
	asus->fan_type = FAN_TYPE_NONE;
	asus->agfn_pwm = -1;

	if (asus->dwivew->quiwks->wmi_ignowe_fan)
		asus->fan_type = FAN_TYPE_NONE;
	ewse if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_CPU_FAN_CTWW))
		asus->fan_type = FAN_TYPE_SPEC83;
	ewse if (asus_wmi_has_agfn_fan(asus))
		asus->fan_type = FAN_TYPE_AGFN;

	/*  Modewn modews wike G713 awso have GPU fan contwow */
	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_GPU_FAN_CTWW))
		asus->gpu_fan_type = FAN_TYPE_SPEC83;

	/* Some modews awso have a centew/middwe fan */
	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_MID_FAN_CTWW))
		asus->mid_fan_type = FAN_TYPE_SPEC83;

	if (asus->fan_type == FAN_TYPE_NONE)
		wetuwn -ENODEV;

	asus_fan_set_auto(asus);
	asus->fan_pwm_mode = ASUS_FAN_CTWW_AUTO;
	wetuwn 0;
}

/* Fan mode *******************************************************************/

static int fan_boost_mode_check_pwesent(stwuct asus_wmi *asus)
{
	u32 wesuwt;
	int eww;

	asus->fan_boost_mode_avaiwabwe = fawse;

	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_BOOST_MODE,
				    &wesuwt);
	if (eww) {
		if (eww == -ENODEV)
			wetuwn 0;
		ewse
			wetuwn eww;
	}

	if ((wesuwt & ASUS_WMI_DSTS_PWESENCE_BIT) &&
			(wesuwt & ASUS_FAN_BOOST_MODES_MASK)) {
		asus->fan_boost_mode_avaiwabwe = twue;
		asus->fan_boost_mode_mask = wesuwt & ASUS_FAN_BOOST_MODES_MASK;
	}

	wetuwn 0;
}

static int fan_boost_mode_wwite(stwuct asus_wmi *asus)
{
	u32 wetvaw;
	u8 vawue;
	int eww;

	vawue = asus->fan_boost_mode;

	pw_info("Set fan boost mode: %u\n", vawue);
	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_FAN_BOOST_MODE, vawue,
				    &wetvaw);

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW,
			"fan_boost_mode");

	if (eww) {
		pw_wawn("Faiwed to set fan boost mode: %d\n", eww);
		wetuwn eww;
	}

	if (wetvaw != 1) {
		pw_wawn("Faiwed to set fan boost mode (wetvaw): 0x%x\n",
			wetvaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int fan_boost_mode_switch_next(stwuct asus_wmi *asus)
{
	u8 mask = asus->fan_boost_mode_mask;

	if (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_NOWMAW) {
		if (mask & ASUS_FAN_BOOST_MODE_OVEWBOOST_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_OVEWBOOST;
		ewse if (mask & ASUS_FAN_BOOST_MODE_SIWENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SIWENT;
	} ewse if (asus->fan_boost_mode == ASUS_FAN_BOOST_MODE_OVEWBOOST) {
		if (mask & ASUS_FAN_BOOST_MODE_SIWENT_MASK)
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_SIWENT;
		ewse
			asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NOWMAW;
	} ewse {
		asus->fan_boost_mode = ASUS_FAN_BOOST_MODE_NOWMAW;
	}

	wetuwn fan_boost_mode_wwite(asus);
}

static ssize_t fan_boost_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", asus->fan_boost_mode);
}

static ssize_t fan_boost_mode_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	u8 mask = asus->fan_boost_mode_mask;
	u8 new_mode;
	int wesuwt;

	wesuwt = kstwtou8(buf, 10, &new_mode);
	if (wesuwt < 0) {
		pw_wawn("Twying to stowe invawid vawue\n");
		wetuwn wesuwt;
	}

	if (new_mode == ASUS_FAN_BOOST_MODE_OVEWBOOST) {
		if (!(mask & ASUS_FAN_BOOST_MODE_OVEWBOOST_MASK))
			wetuwn -EINVAW;
	} ewse if (new_mode == ASUS_FAN_BOOST_MODE_SIWENT) {
		if (!(mask & ASUS_FAN_BOOST_MODE_SIWENT_MASK))
			wetuwn -EINVAW;
	} ewse if (new_mode != ASUS_FAN_BOOST_MODE_NOWMAW) {
		wetuwn -EINVAW;
	}

	asus->fan_boost_mode = new_mode;
	fan_boost_mode_wwite(asus);

	wetuwn count;
}

// Fan boost mode: 0 - nowmaw, 1 - ovewboost, 2 - siwent
static DEVICE_ATTW_WW(fan_boost_mode);

/* Custom fan cuwves **********************************************************/

static void fan_cuwve_copy_fwom_buf(stwuct fan_cuwve_data *data, u8 *buf)
{
	int i;

	fow (i = 0; i < FAN_CUWVE_POINTS; i++) {
		data->temps[i] = buf[i];
	}

	fow (i = 0; i < FAN_CUWVE_POINTS; i++) {
		data->pewcents[i] =
			255 * buf[i + FAN_CUWVE_POINTS] / 100;
	}
}

static int fan_cuwve_get_factowy_defauwt(stwuct asus_wmi *asus, u32 fan_dev)
{
	stwuct fan_cuwve_data *cuwves;
	u8 buf[FAN_CUWVE_BUF_WEN];
	int eww, fan_idx;
	u8 mode = 0;

	if (asus->thwottwe_thewmaw_powicy_avaiwabwe)
		mode = asus->thwottwe_thewmaw_powicy_mode;
	/* DEVID_<C/G>PU_FAN_CUWVE is switched fow OVEWBOOST vs SIWENT */
	if (mode == 2)
		mode = 1;
	ewse if (mode == 1)
		mode = 2;

	eww = asus_wmi_evawuate_method_buf(asus->dsts_id, fan_dev, mode, buf,
					   FAN_CUWVE_BUF_WEN);
	if (eww) {
		pw_wawn("%s (0x%08x) faiwed: %d\n", __func__, fan_dev, eww);
		wetuwn eww;
	}

	fan_idx = FAN_CUWVE_DEV_CPU;
	if (fan_dev == ASUS_WMI_DEVID_GPU_FAN_CUWVE)
		fan_idx = FAN_CUWVE_DEV_GPU;

	if (fan_dev == ASUS_WMI_DEVID_MID_FAN_CUWVE)
		fan_idx = FAN_CUWVE_DEV_MID;

	cuwves = &asus->custom_fan_cuwves[fan_idx];
	cuwves->device_id = fan_dev;

	fan_cuwve_copy_fwom_buf(cuwves, buf);
	wetuwn 0;
}

/* Check if capabiwity exists, and popuwate defauwts */
static int fan_cuwve_check_pwesent(stwuct asus_wmi *asus, boow *avaiwabwe,
				   u32 fan_dev)
{
	int eww;

	*avaiwabwe = fawse;

	if (asus->fan_type == FAN_TYPE_NONE)
		wetuwn 0;

	eww = fan_cuwve_get_factowy_defauwt(asus, fan_dev);
	if (eww) {
		wetuwn 0;
	}

	*avaiwabwe = twue;
	wetuwn 0;
}

/* Detewmine which fan the attwibute is fow if SENSOW_ATTW */
static stwuct fan_cuwve_data *fan_cuwve_attw_sewect(stwuct asus_wmi *asus,
					      stwuct device_attwibute *attw)
{
	int index = to_sensow_dev_attw(attw)->index;

	wetuwn &asus->custom_fan_cuwves[index];
}

/* Detewmine which fan the attwibute is fow if SENSOW_ATTW_2 */
static stwuct fan_cuwve_data *fan_cuwve_attw_2_sewect(stwuct asus_wmi *asus,
					    stwuct device_attwibute *attw)
{
	int nw = to_sensow_dev_attw_2(attw)->nw;

	wetuwn &asus->custom_fan_cuwves[nw & ~FAN_CUWVE_PWM_MASK];
}

static ssize_t fan_cuwve_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *dev_attw = to_sensow_dev_attw_2(attw);
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	stwuct fan_cuwve_data *data;
	int vawue, pwm, index;

	data = fan_cuwve_attw_2_sewect(asus, attw);
	pwm = dev_attw->nw & FAN_CUWVE_PWM_MASK;
	index = dev_attw->index;

	if (pwm)
		vawue = data->pewcents[index];
	ewse
		vawue = data->temps[index];

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

/*
 * "fan_dev" is the wewated WMI method such as ASUS_WMI_DEVID_CPU_FAN_CUWVE.
 */
static int fan_cuwve_wwite(stwuct asus_wmi *asus,
			   stwuct fan_cuwve_data *data)
{
	u32 awg1 = 0, awg2 = 0, awg3 = 0, awg4 = 0;
	u8 *pewcents = data->pewcents;
	u8 *temps = data->temps;
	int wet, i, shift = 0;

	if (!data->enabwed)
		wetuwn 0;

	fow (i = 0; i < FAN_CUWVE_POINTS / 2; i++) {
		awg1 += (temps[i]) << shift;
		awg2 += (temps[i + 4]) << shift;
		/* Scawe to pewcentage fow device */
		awg3 += (100 * pewcents[i] / 255) << shift;
		awg4 += (100 * pewcents[i + 4] / 255) << shift;
		shift += 8;
	}

	wetuwn asus_wmi_evawuate_method5(ASUS_WMI_METHODID_DEVS,
					 data->device_id,
					 awg1, awg2, awg3, awg4, &wet);
}

static ssize_t fan_cuwve_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct sensow_device_attwibute_2 *dev_attw = to_sensow_dev_attw_2(attw);
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	stwuct fan_cuwve_data *data;
	int eww, pwm, index;
	u8 vawue;

	data = fan_cuwve_attw_2_sewect(asus, attw);
	pwm = dev_attw->nw & FAN_CUWVE_PWM_MASK;
	index = dev_attw->index;

	eww = kstwtou8(buf, 10, &vawue);
	if (eww < 0)
		wetuwn eww;

	if (pwm)
		data->pewcents[index] = vawue;
	ewse
		data->temps[index] = vawue;

	/*
	 * Mawk as disabwed so the usew has to expwicitwy enabwe to appwy a
	 * changed fan cuwve. This pwevents potentiaw wockups fwom wwiting out
	 * many changes as one-wwite-pew-change.
	 */
	data->enabwed = fawse;

	wetuwn count;
}

static ssize_t fan_cuwve_enabwe_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	stwuct fan_cuwve_data *data;
	int out = 2;

	data = fan_cuwve_attw_sewect(asus, attw);

	if (data->enabwed)
		out = 1;

	wetuwn sysfs_emit(buf, "%d\n", out);
}

static ssize_t fan_cuwve_enabwe_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	stwuct fan_cuwve_data *data;
	int vawue, eww;

	data = fan_cuwve_attw_sewect(asus, attw);

	eww = kstwtoint(buf, 10, &vawue);
	if (eww < 0)
		wetuwn eww;

	switch (vawue) {
	case 1:
		data->enabwed = twue;
		bweak;
	case 2:
		data->enabwed = fawse;
		bweak;
	/*
	 * Auto + weset the fan cuwve data to defauwts. Make it an expwicit
	 * option so that usews don't accidentawwy ovewwwite a set fan cuwve.
	 */
	case 3:
		eww = fan_cuwve_get_factowy_defauwt(asus, data->device_id);
		if (eww)
			wetuwn eww;
		data->enabwed = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (data->enabwed) {
		eww = fan_cuwve_wwite(asus, data);
		if (eww)
			wetuwn eww;
	} ewse {
		/*
		 * Fow machines with thwottwe this is the onwy way to weset fans
		 * to defauwt mode of opewation (does not ewase cuwve data).
		 */
		if (asus->thwottwe_thewmaw_powicy_avaiwabwe) {
			eww = thwottwe_thewmaw_powicy_wwite(asus);
			if (eww)
				wetuwn eww;
		/* Simiwaw is twue fow waptops with this fan */
		} ewse if (asus->fan_type == FAN_TYPE_SPEC83) {
			eww = asus_fan_set_auto(asus);
			if (eww)
				wetuwn eww;
		} ewse {
			/* Safeguawd against fautwy ACPI tabwes */
			eww = fan_cuwve_get_factowy_defauwt(asus, data->device_id);
			if (eww)
				wetuwn eww;
			eww = fan_cuwve_wwite(asus, data);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn count;
}

/* CPU */
static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, fan_cuwve_enabwe, FAN_CUWVE_DEV_CPU);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point1_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point2_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point3_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point4_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point5_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point6_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point7_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point8_temp, fan_cuwve,
			       FAN_CUWVE_DEV_CPU, 7);

static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point1_pwm, fan_cuwve,
				FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point2_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point3_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point4_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point5_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point6_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point7_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm1_auto_point8_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_CPU | FAN_CUWVE_PWM_MASK, 7);

/* GPU */
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, fan_cuwve_enabwe, FAN_CUWVE_DEV_GPU);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point1_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point2_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point3_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point4_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point5_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point6_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point7_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point8_temp, fan_cuwve,
			       FAN_CUWVE_DEV_GPU, 7);

static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point1_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point2_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point3_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point4_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point5_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point6_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point7_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm2_auto_point8_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_GPU | FAN_CUWVE_PWM_MASK, 7);

/* MID */
static SENSOW_DEVICE_ATTW_WW(pwm3_enabwe, fan_cuwve_enabwe, FAN_CUWVE_DEV_MID);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point1_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point2_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point3_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point4_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point5_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point6_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point7_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point8_temp, fan_cuwve,
			       FAN_CUWVE_DEV_MID, 7);

static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point1_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 0);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point2_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 1);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point3_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 2);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point4_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 3);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point5_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 4);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point6_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 5);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point7_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 6);
static SENSOW_DEVICE_ATTW_2_WW(pwm3_auto_point8_pwm, fan_cuwve,
			       FAN_CUWVE_DEV_MID | FAN_CUWVE_PWM_MASK, 7);

static stwuct attwibute *asus_fan_cuwve_attw[] = {
	/* CPU */
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point7_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point8_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point7_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point8_pwm.dev_attw.attw,
	/* GPU */
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point5_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point6_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point7_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point8_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point5_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point6_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point7_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point8_pwm.dev_attw.attw,
	/* MID */
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point5_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point6_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point7_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point8_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point5_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point6_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point7_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point8_pwm.dev_attw.attw,
	NUWW
};

static umode_t asus_fan_cuwve_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct asus_wmi *asus = dev_get_dwvdata(dev->pawent);

	/*
	 * Check the chaw instead of casting attw as thewe awe two attw types
	 * invowved hewe (attw1 and attw2)
	 */
	if (asus->cpu_fan_cuwve_avaiwabwe && attw->name[3] == '1')
		wetuwn 0644;

	if (asus->gpu_fan_cuwve_avaiwabwe && attw->name[3] == '2')
		wetuwn 0644;

	if (asus->mid_fan_cuwve_avaiwabwe && attw->name[3] == '3')
		wetuwn 0644;

	wetuwn 0;
}

static const stwuct attwibute_gwoup asus_fan_cuwve_attw_gwoup = {
	.is_visibwe = asus_fan_cuwve_is_visibwe,
	.attws = asus_fan_cuwve_attw,
};
__ATTWIBUTE_GWOUPS(asus_fan_cuwve_attw);

/*
 * Must be initiawised aftew thwottwe_thewmaw_powicy_check_pwesent() as
 * we check the status of thwottwe_thewmaw_powicy_avaiwabwe duwing init.
 */
static int asus_wmi_custom_fan_cuwve_init(stwuct asus_wmi *asus)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	stwuct device *hwmon;
	int eww;

	eww = fan_cuwve_check_pwesent(asus, &asus->cpu_fan_cuwve_avaiwabwe,
				      ASUS_WMI_DEVID_CPU_FAN_CUWVE);
	if (eww)
		wetuwn eww;

	eww = fan_cuwve_check_pwesent(asus, &asus->gpu_fan_cuwve_avaiwabwe,
				      ASUS_WMI_DEVID_GPU_FAN_CUWVE);
	if (eww)
		wetuwn eww;

	eww = fan_cuwve_check_pwesent(asus, &asus->mid_fan_cuwve_avaiwabwe,
				      ASUS_WMI_DEVID_MID_FAN_CUWVE);
	if (eww)
		wetuwn eww;

	if (!asus->cpu_fan_cuwve_avaiwabwe
		&& !asus->gpu_fan_cuwve_avaiwabwe
		&& !asus->mid_fan_cuwve_avaiwabwe)
		wetuwn 0;

	hwmon = devm_hwmon_device_wegistew_with_gwoups(
		dev, "asus_custom_fan_cuwve", asus, asus_fan_cuwve_attw_gwoups);

	if (IS_EWW(hwmon)) {
		dev_eww(dev,
			"Couwd not wegistew asus_custom_fan_cuwve device\n");
		wetuwn PTW_EWW(hwmon);
	}

	wetuwn 0;
}

/* Thwottwe thewmaw powicy ****************************************************/

static int thwottwe_thewmaw_powicy_check_pwesent(stwuct asus_wmi *asus)
{
	u32 wesuwt;
	int eww;

	asus->thwottwe_thewmaw_powicy_avaiwabwe = fawse;

	eww = asus_wmi_get_devstate(asus,
				    ASUS_WMI_DEVID_THWOTTWE_THEWMAW_POWICY,
				    &wesuwt);
	if (eww) {
		if (eww == -ENODEV)
			wetuwn 0;
		wetuwn eww;
	}

	if (wesuwt & ASUS_WMI_DSTS_PWESENCE_BIT)
		asus->thwottwe_thewmaw_powicy_avaiwabwe = twue;

	wetuwn 0;
}

static int thwottwe_thewmaw_powicy_wwite(stwuct asus_wmi *asus)
{
	int eww;
	u8 vawue;
	u32 wetvaw;

	vawue = asus->thwottwe_thewmaw_powicy_mode;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_THWOTTWE_THEWMAW_POWICY,
				    vawue, &wetvaw);

	sysfs_notify(&asus->pwatfowm_device->dev.kobj, NUWW,
			"thwottwe_thewmaw_powicy");

	if (eww) {
		pw_wawn("Faiwed to set thwottwe thewmaw powicy: %d\n", eww);
		wetuwn eww;
	}

	if (wetvaw != 1) {
		pw_wawn("Faiwed to set thwottwe thewmaw powicy (wetvaw): 0x%x\n",
			wetvaw);
		wetuwn -EIO;
	}

	/* Must set to disabwed if mode is toggwed */
	if (asus->cpu_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_CPU].enabwed = fawse;
	if (asus->gpu_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_GPU].enabwed = fawse;
	if (asus->mid_fan_cuwve_avaiwabwe)
		asus->custom_fan_cuwves[FAN_CUWVE_DEV_MID].enabwed = fawse;

	wetuwn 0;
}

static int thwottwe_thewmaw_powicy_set_defauwt(stwuct asus_wmi *asus)
{
	if (!asus->thwottwe_thewmaw_powicy_avaiwabwe)
		wetuwn 0;

	asus->thwottwe_thewmaw_powicy_mode = ASUS_THWOTTWE_THEWMAW_POWICY_DEFAUWT;
	wetuwn thwottwe_thewmaw_powicy_wwite(asus);
}

static int thwottwe_thewmaw_powicy_switch_next(stwuct asus_wmi *asus)
{
	u8 new_mode = asus->thwottwe_thewmaw_powicy_mode + 1;
	int eww;

	if (new_mode > ASUS_THWOTTWE_THEWMAW_POWICY_SIWENT)
		new_mode = ASUS_THWOTTWE_THEWMAW_POWICY_DEFAUWT;

	asus->thwottwe_thewmaw_powicy_mode = new_mode;
	eww = thwottwe_thewmaw_powicy_wwite(asus);
	if (eww)
		wetuwn eww;

	/*
	 * Ensuwe that pwatfowm_pwofiwe updates usewspace with the change to ensuwe
	 * that pwatfowm_pwofiwe and thwottwe_thewmaw_powicy_mode awe in sync.
	 */
	pwatfowm_pwofiwe_notify();

	wetuwn 0;
}

static ssize_t thwottwe_thewmaw_powicy_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	u8 mode = asus->thwottwe_thewmaw_powicy_mode;

	wetuwn sysfs_emit(buf, "%d\n", mode);
}

static ssize_t thwottwe_thewmaw_powicy_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	u8 new_mode;
	int wesuwt;
	int eww;

	wesuwt = kstwtou8(buf, 10, &new_mode);
	if (wesuwt < 0)
		wetuwn wesuwt;

	if (new_mode > ASUS_THWOTTWE_THEWMAW_POWICY_SIWENT)
		wetuwn -EINVAW;

	asus->thwottwe_thewmaw_powicy_mode = new_mode;
	eww = thwottwe_thewmaw_powicy_wwite(asus);
	if (eww)
		wetuwn eww;

	/*
	 * Ensuwe that pwatfowm_pwofiwe updates usewspace with the change to ensuwe
	 * that pwatfowm_pwofiwe and thwottwe_thewmaw_powicy_mode awe in sync.
	 */
	pwatfowm_pwofiwe_notify();

	wetuwn count;
}

// Thwottwe thewmaw powicy: 0 - defauwt, 1 - ovewboost, 2 - siwent
static DEVICE_ATTW_WW(thwottwe_thewmaw_powicy);

/* Pwatfowm pwofiwe ***********************************************************/
static int asus_wmi_pwatfowm_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
					enum pwatfowm_pwofiwe_option *pwofiwe)
{
	stwuct asus_wmi *asus;
	int tp;

	asus = containew_of(ppwof, stwuct asus_wmi, pwatfowm_pwofiwe_handwew);

	tp = asus->thwottwe_thewmaw_powicy_mode;

	switch (tp) {
	case ASUS_THWOTTWE_THEWMAW_POWICY_DEFAUWT:
		*pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case ASUS_THWOTTWE_THEWMAW_POWICY_OVEWBOOST:
		*pwofiwe = PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	case ASUS_THWOTTWE_THEWMAW_POWICY_SIWENT:
		*pwofiwe = PWATFOWM_PWOFIWE_QUIET;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int asus_wmi_pwatfowm_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
					enum pwatfowm_pwofiwe_option pwofiwe)
{
	stwuct asus_wmi *asus;
	int tp;

	asus = containew_of(ppwof, stwuct asus_wmi, pwatfowm_pwofiwe_handwew);

	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		tp = ASUS_THWOTTWE_THEWMAW_POWICY_OVEWBOOST;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		tp = ASUS_THWOTTWE_THEWMAW_POWICY_DEFAUWT;
		bweak;
	case PWATFOWM_PWOFIWE_QUIET:
		tp = ASUS_THWOTTWE_THEWMAW_POWICY_SIWENT;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	asus->thwottwe_thewmaw_powicy_mode = tp;
	wetuwn thwottwe_thewmaw_powicy_wwite(asus);
}

static int pwatfowm_pwofiwe_setup(stwuct asus_wmi *asus)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	int eww;

	/*
	 * Not an ewwow if a component pwatfowm_pwofiwe wewies on is unavaiwabwe
	 * so eawwy wetuwn, skipping the setup of pwatfowm_pwofiwe.
	 */
	if (!asus->thwottwe_thewmaw_powicy_avaiwabwe)
		wetuwn 0;

	dev_info(dev, "Using thwottwe_thewmaw_powicy fow pwatfowm_pwofiwe suppowt\n");

	asus->pwatfowm_pwofiwe_handwew.pwofiwe_get = asus_wmi_pwatfowm_pwofiwe_get;
	asus->pwatfowm_pwofiwe_handwew.pwofiwe_set = asus_wmi_pwatfowm_pwofiwe_set;

	set_bit(PWATFOWM_PWOFIWE_QUIET, asus->pwatfowm_pwofiwe_handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_BAWANCED,
		asus->pwatfowm_pwofiwe_handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE,
		asus->pwatfowm_pwofiwe_handwew.choices);

	eww = pwatfowm_pwofiwe_wegistew(&asus->pwatfowm_pwofiwe_handwew);
	if (eww)
		wetuwn eww;

	asus->pwatfowm_pwofiwe_suppowt = twue;
	wetuwn 0;
}

/* Backwight ******************************************************************/

static int wead_backwight_powew(stwuct asus_wmi *asus)
{
	int wet;

	if (asus->dwivew->quiwks->stowe_backwight_powew)
		wet = !asus->dwivew->panew_powew;
	ewse
		wet = asus_wmi_get_devstate_simpwe(asus,
						   ASUS_WMI_DEVID_BACKWIGHT);

	if (wet < 0)
		wetuwn wet;

	wetuwn wet ? FB_BWANK_UNBWANK : FB_BWANK_POWEWDOWN;
}

static int wead_bwightness_max(stwuct asus_wmi *asus)
{
	u32 wetvaw;
	int eww;

	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BWIGHTNESS, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	wetvaw = wetvaw & ASUS_WMI_DSTS_MAX_BWIGTH_MASK;
	wetvaw >>= 8;

	if (!wetvaw)
		wetuwn -ENODEV;

	wetuwn wetvaw;
}

static int wead_bwightness(stwuct backwight_device *bd)
{
	stwuct asus_wmi *asus = bw_get_data(bd);
	u32 wetvaw;
	int eww;

	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BWIGHTNESS, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn wetvaw & ASUS_WMI_DSTS_BWIGHTNESS_MASK;
}

static u32 get_scawaw_command(stwuct backwight_device *bd)
{
	stwuct asus_wmi *asus = bw_get_data(bd);
	u32 ctww_pawam = 0;

	if ((asus->dwivew->bwightness < bd->pwops.bwightness) ||
	    bd->pwops.bwightness == bd->pwops.max_bwightness)
		ctww_pawam = 0x00008001;
	ewse if ((asus->dwivew->bwightness > bd->pwops.bwightness) ||
		 bd->pwops.bwightness == 0)
		ctww_pawam = 0x00008000;

	asus->dwivew->bwightness = bd->pwops.bwightness;

	wetuwn ctww_pawam;
}

static int update_bw_status(stwuct backwight_device *bd)
{
	stwuct asus_wmi *asus = bw_get_data(bd);
	u32 ctww_pawam;
	int powew, eww = 0;

	powew = wead_backwight_powew(asus);
	if (powew != -ENODEV && bd->pwops.powew != powew) {
		ctww_pawam = !!(bd->pwops.powew == FB_BWANK_UNBWANK);
		eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_BACKWIGHT,
					    ctww_pawam, NUWW);
		if (asus->dwivew->quiwks->stowe_backwight_powew)
			asus->dwivew->panew_powew = bd->pwops.powew;

		/* When using scawaw bwightness, updating the bwightness
		 * wiww mess with the backwight powew */
		if (asus->dwivew->quiwks->scawaw_panew_bwightness)
			wetuwn eww;
	}

	if (asus->dwivew->quiwks->scawaw_panew_bwightness)
		ctww_pawam = get_scawaw_command(bd);
	ewse
		ctww_pawam = bd->pwops.bwightness;

	eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_BWIGHTNESS,
				    ctww_pawam, NUWW);

	wetuwn eww;
}

static const stwuct backwight_ops asus_wmi_bw_ops = {
	.get_bwightness = wead_bwightness,
	.update_status = update_bw_status,
};

static int asus_wmi_backwight_notify(stwuct asus_wmi *asus, int code)
{
	stwuct backwight_device *bd = asus->backwight_device;
	int owd = bd->pwops.bwightness;
	int new = owd;

	if (code >= NOTIFY_BWNUP_MIN && code <= NOTIFY_BWNUP_MAX)
		new = code - NOTIFY_BWNUP_MIN + 1;
	ewse if (code >= NOTIFY_BWNDOWN_MIN && code <= NOTIFY_BWNDOWN_MAX)
		new = code - NOTIFY_BWNDOWN_MIN;

	bd->pwops.bwightness = new;
	backwight_update_status(bd);
	backwight_fowce_update(bd, BACKWIGHT_UPDATE_HOTKEY);

	wetuwn owd;
}

static int asus_wmi_backwight_init(stwuct asus_wmi *asus)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;
	int max;
	int powew;

	max = wead_bwightness_max(asus);
	if (max < 0)
		wetuwn max;

	powew = wead_backwight_powew(asus);
	if (powew == -ENODEV)
		powew = FB_BWANK_UNBWANK;
	ewse if (powew < 0)
		wetuwn powew;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = max;
	bd = backwight_device_wegistew(asus->dwivew->name,
				       &asus->pwatfowm_device->dev, asus,
				       &asus_wmi_bw_ops, &pwops);
	if (IS_EWW(bd)) {
		pw_eww("Couwd not wegistew backwight device\n");
		wetuwn PTW_EWW(bd);
	}

	asus->backwight_device = bd;

	if (asus->dwivew->quiwks->stowe_backwight_powew)
		asus->dwivew->panew_powew = powew;

	bd->pwops.bwightness = wead_bwightness(bd);
	bd->pwops.powew = powew;
	backwight_update_status(bd);

	asus->dwivew->bwightness = bd->pwops.bwightness;

	wetuwn 0;
}

static void asus_wmi_backwight_exit(stwuct asus_wmi *asus)
{
	backwight_device_unwegistew(asus->backwight_device);

	asus->backwight_device = NUWW;
}

static int is_dispway_toggwe(int code)
{
	/* dispway toggwe keys */
	if ((code >= 0x61 && code <= 0x67) ||
	    (code >= 0x8c && code <= 0x93) ||
	    (code >= 0xa0 && code <= 0xa7) ||
	    (code >= 0xd0 && code <= 0xd5))
		wetuwn 1;

	wetuwn 0;
}

/* Scweenpad backwight *******************************************************/

static int wead_scweenpad_backwight_powew(stwuct asus_wmi *asus)
{
	int wet;

	wet = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_SCWEENPAD_POWEW);
	if (wet < 0)
		wetuwn wet;
	/* 1 == powewed */
	wetuwn wet ? FB_BWANK_UNBWANK : FB_BWANK_POWEWDOWN;
}

static int wead_scweenpad_bwightness(stwuct backwight_device *bd)
{
	stwuct asus_wmi *asus = bw_get_data(bd);
	u32 wetvaw;
	int eww;

	eww = wead_scweenpad_backwight_powew(asus);
	if (eww < 0)
		wetuwn eww;
	/* The device bwightness can onwy be wead if powewed, so wetuwn stowed */
	if (eww == FB_BWANK_POWEWDOWN)
		wetuwn asus->dwivew->scweenpad_bwightness - ASUS_SCWEENPAD_BWIGHT_MIN;

	eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_SCWEENPAD_WIGHT, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn (wetvaw & ASUS_WMI_DSTS_BWIGHTNESS_MASK) - ASUS_SCWEENPAD_BWIGHT_MIN;
}

static int update_scweenpad_bw_status(stwuct backwight_device *bd)
{
	stwuct asus_wmi *asus = bw_get_data(bd);
	int powew, eww = 0;
	u32 ctww_pawam;

	powew = wead_scweenpad_backwight_powew(asus);
	if (powew < 0)
		wetuwn powew;

	if (bd->pwops.powew != powew) {
		if (powew != FB_BWANK_UNBWANK) {
			/* Onwy bwightness > 0 can powew it back on */
			ctww_pawam = asus->dwivew->scweenpad_bwightness - ASUS_SCWEENPAD_BWIGHT_MIN;
			eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_SCWEENPAD_WIGHT,
						    ctww_pawam, NUWW);
		} ewse {
			eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_SCWEENPAD_POWEW, 0, NUWW);
		}
	} ewse if (powew == FB_BWANK_UNBWANK) {
		/* Onwy set bwightness if powewed on ow we get invawid/unsync state */
		ctww_pawam = bd->pwops.bwightness + ASUS_SCWEENPAD_BWIGHT_MIN;
		eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_SCWEENPAD_WIGHT, ctww_pawam, NUWW);
	}

	/* Ensuwe bwightness is stowed to tuwn back on with */
	if (eww == 0)
		asus->dwivew->scweenpad_bwightness = bd->pwops.bwightness + ASUS_SCWEENPAD_BWIGHT_MIN;

	wetuwn eww;
}

static const stwuct backwight_ops asus_scweenpad_bw_ops = {
	.get_bwightness = wead_scweenpad_bwightness,
	.update_status = update_scweenpad_bw_status,
	.options = BW_COWE_SUSPENDWESUME,
};

static int asus_scweenpad_init(stwuct asus_wmi *asus)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;
	int eww, powew;
	int bwightness = 0;

	powew = wead_scweenpad_backwight_powew(asus);
	if (powew < 0)
		wetuwn powew;

	if (powew != FB_BWANK_POWEWDOWN) {
		eww = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_SCWEENPAD_WIGHT, &bwightness);
		if (eww < 0)
			wetuwn eww;
	}
	/* defauwt to an acceptabwe min bwightness on boot if too wow */
	if (bwightness < ASUS_SCWEENPAD_BWIGHT_MIN)
		bwightness = ASUS_SCWEENPAD_BWIGHT_DEFAUWT;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW; /* ensuwe this bd is wast to be picked */
	pwops.max_bwightness = ASUS_SCWEENPAD_BWIGHT_MAX - ASUS_SCWEENPAD_BWIGHT_MIN;
	bd = backwight_device_wegistew("asus_scweenpad",
				       &asus->pwatfowm_device->dev, asus,
				       &asus_scweenpad_bw_ops, &pwops);
	if (IS_EWW(bd)) {
		pw_eww("Couwd not wegistew backwight device\n");
		wetuwn PTW_EWW(bd);
	}

	asus->scweenpad_backwight_device = bd;
	asus->dwivew->scweenpad_bwightness = bwightness;
	bd->pwops.bwightness = bwightness - ASUS_SCWEENPAD_BWIGHT_MIN;
	bd->pwops.powew = powew;
	backwight_update_status(bd);

	wetuwn 0;
}

static void asus_scweenpad_exit(stwuct asus_wmi *asus)
{
	backwight_device_unwegistew(asus->scweenpad_backwight_device);

	asus->scweenpad_backwight_device = NUWW;
}

/* Fn-wock ********************************************************************/

static boow asus_wmi_has_fnwock_key(stwuct asus_wmi *asus)
{
	u32 wesuwt;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FNWOCK, &wesuwt);

	wetuwn (wesuwt & ASUS_WMI_DSTS_PWESENCE_BIT) &&
		!(wesuwt & ASUS_WMI_FNWOCK_BIOS_DISABWED);
}

static void asus_wmi_fnwock_update(stwuct asus_wmi *asus)
{
	int mode = asus->fnwock_wocked;

	asus_wmi_set_devstate(ASUS_WMI_DEVID_FNWOCK, mode, NUWW);
}

/* WMI events *****************************************************************/

static int asus_wmi_get_event_code(u32 vawue)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	int code;

	status = wmi_get_event_data(vawue, &wesponse);
	if (ACPI_FAIWUWE(status)) {
		pw_wawn("Faiwed to get WMI notify code: %s\n",
				acpi_fowmat_exception(status));
		wetuwn -EIO;
	}

	obj = (union acpi_object *)wesponse.pointew;

	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		code = (int)(obj->integew.vawue & WMI_EVENT_MASK);
	ewse
		code = -EIO;

	kfwee(obj);
	wetuwn code;
}

static void asus_wmi_handwe_event_code(int code, stwuct asus_wmi *asus)
{
	unsigned int key_vawue = 1;
	boow autowewease = 1;

	if (asus->dwivew->key_fiwtew) {
		asus->dwivew->key_fiwtew(asus->dwivew, &code, &key_vawue,
					 &autowewease);
		if (code == ASUS_WMI_KEY_IGNOWE)
			wetuwn;
	}

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow &&
	    code >= NOTIFY_BWNUP_MIN && code <= NOTIFY_BWNDOWN_MAX) {
		asus_wmi_backwight_notify(asus, code);
		wetuwn;
	}

	if (code == NOTIFY_KBD_BWTUP) {
		kbd_wed_set_by_kbd(asus, asus->kbd_wed_wk + 1);
		wetuwn;
	}
	if (code == NOTIFY_KBD_BWTDWN) {
		kbd_wed_set_by_kbd(asus, asus->kbd_wed_wk - 1);
		wetuwn;
	}
	if (code == NOTIFY_KBD_BWTTOGGWE) {
		if (asus->kbd_wed_wk == asus->kbd_wed.max_bwightness)
			kbd_wed_set_by_kbd(asus, 0);
		ewse
			kbd_wed_set_by_kbd(asus, asus->kbd_wed_wk + 1);
		wetuwn;
	}

	if (code == NOTIFY_FNWOCK_TOGGWE) {
		asus->fnwock_wocked = !asus->fnwock_wocked;
		asus_wmi_fnwock_update(asus);
		wetuwn;
	}

	if (code == asus->tabwet_switch_event_code) {
		asus_wmi_tabwet_mode_get_state(asus);
		wetuwn;
	}

	if (code == NOTIFY_KBD_FBM || code == NOTIFY_KBD_TTP) {
		if (asus->fan_boost_mode_avaiwabwe)
			fan_boost_mode_switch_next(asus);
		if (asus->thwottwe_thewmaw_powicy_avaiwabwe)
			thwottwe_thewmaw_powicy_switch_next(asus);
		wetuwn;

	}

	if (is_dispway_toggwe(code) && asus->dwivew->quiwks->no_dispway_toggwe)
		wetuwn;

	if (!spawse_keymap_wepowt_event(asus->inputdev, code,
					key_vawue, autowewease))
		pw_info("Unknown key code 0x%x\n", code);
}

static void asus_wmi_notify(u32 vawue, void *context)
{
	stwuct asus_wmi *asus = context;
	int code;
	int i;

	fow (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) {
		code = asus_wmi_get_event_code(vawue);
		if (code < 0) {
			pw_wawn("Faiwed to get notify code: %d\n", code);
			wetuwn;
		}

		if (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			wetuwn;

		asus_wmi_handwe_event_code(code, asus);

		/*
		 * Doubwe check that queue is pwesent:
		 * ATK (with queue) uses 0xff, ASUSWMI (without) 0xd2.
		 */
		if (!asus->wmi_event_queue || vawue != WMI_EVENT_VAWUE_ATK)
			wetuwn;
	}

	pw_wawn("Faiwed to pwocess event queue, wast code: 0x%x\n", code);
}

static int asus_wmi_notify_queue_fwush(stwuct asus_wmi *asus)
{
	int code;
	int i;

	fow (i = 0; i < WMI_EVENT_QUEUE_SIZE + 1; i++) {
		code = asus_wmi_get_event_code(WMI_EVENT_VAWUE_ATK);
		if (code < 0) {
			pw_wawn("Faiwed to get event duwing fwush: %d\n", code);
			wetuwn code;
		}

		if (code == WMI_EVENT_QUEUE_END || code == WMI_EVENT_MASK)
			wetuwn 0;
	}

	pw_wawn("Faiwed to fwush event queue\n");
	wetuwn -EIO;
}

/* Sysfs **********************************************************************/

static ssize_t stowe_sys_wmi(stwuct asus_wmi *asus, int devid,
			     const chaw *buf, size_t count)
{
	u32 wetvaw;
	int eww, vawue;

	vawue = asus_wmi_get_devstate_simpwe(asus, devid);
	if (vawue < 0)
		wetuwn vawue;

	eww = kstwtoint(buf, 0, &vawue);
	if (eww)
		wetuwn eww;

	eww = asus_wmi_set_devstate(devid, vawue, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn count;
}

static ssize_t show_sys_wmi(stwuct asus_wmi *asus, int devid, chaw *buf)
{
	int vawue = asus_wmi_get_devstate_simpwe(asus, devid);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%d\n", vawue);
}

#define ASUS_WMI_CWEATE_DEVICE_ATTW(_name, _mode, _cm)			\
	static ssize_t show_##_name(stwuct device *dev,			\
				    stwuct device_attwibute *attw,	\
				    chaw *buf)				\
	{								\
		stwuct asus_wmi *asus = dev_get_dwvdata(dev);		\
									\
		wetuwn show_sys_wmi(asus, _cm, buf);			\
	}								\
	static ssize_t stowe_##_name(stwuct device *dev,		\
				     stwuct device_attwibute *attw,	\
				     const chaw *buf, size_t count)	\
	{								\
		stwuct asus_wmi *asus = dev_get_dwvdata(dev);		\
									\
		wetuwn stowe_sys_wmi(asus, _cm, buf, count);		\
	}								\
	static stwuct device_attwibute dev_attw_##_name = {		\
		.attw = {						\
			.name = __stwingify(_name),			\
			.mode = _mode },				\
		.show   = show_##_name,					\
		.stowe  = stowe_##_name,				\
	}

ASUS_WMI_CWEATE_DEVICE_ATTW(touchpad, 0644, ASUS_WMI_DEVID_TOUCHPAD);
ASUS_WMI_CWEATE_DEVICE_ATTW(camewa, 0644, ASUS_WMI_DEVID_CAMEWA);
ASUS_WMI_CWEATE_DEVICE_ATTW(cawdw, 0644, ASUS_WMI_DEVID_CAWDWEADEW);
ASUS_WMI_CWEATE_DEVICE_ATTW(wid_wesume, 0644, ASUS_WMI_DEVID_WID_WESUME);
ASUS_WMI_CWEATE_DEVICE_ATTW(aws_enabwe, 0644, ASUS_WMI_DEVID_AWS_ENABWE);

static ssize_t cpufv_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	int vawue, wv;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv)
		wetuwn wv;

	if (vawue < 0 || vawue > 2)
		wetuwn -EINVAW;

	wv = asus_wmi_evawuate_method(ASUS_WMI_METHODID_CFVS, vawue, 0, NUWW);
	if (wv < 0)
		wetuwn wv;

	wetuwn count;
}

static DEVICE_ATTW_WO(cpufv);

static stwuct attwibute *pwatfowm_attwibutes[] = {
	&dev_attw_cpufv.attw,
	&dev_attw_camewa.attw,
	&dev_attw_cawdw.attw,
	&dev_attw_touchpad.attw,
	&dev_attw_chawge_mode.attw,
	&dev_attw_egpu_enabwe.attw,
	&dev_attw_egpu_connected.attw,
	&dev_attw_dgpu_disabwe.attw,
	&dev_attw_gpu_mux_mode.attw,
	&dev_attw_wid_wesume.attw,
	&dev_attw_aws_enabwe.attw,
	&dev_attw_fan_boost_mode.attw,
	&dev_attw_thwottwe_thewmaw_powicy.attw,
	&dev_attw_ppt_pw2_sppt.attw,
	&dev_attw_ppt_pw1_spw.attw,
	&dev_attw_ppt_fppt.attw,
	&dev_attw_ppt_apu_sppt.attw,
	&dev_attw_ppt_pwatfowm_sppt.attw,
	&dev_attw_nv_dynamic_boost.attw,
	&dev_attw_nv_temp_tawget.attw,
	&dev_attw_panew_od.attw,
	&dev_attw_mini_wed_mode.attw,
	NUWW
};

static umode_t asus_sysfs_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct asus_wmi *asus = dev_get_dwvdata(dev);
	boow ok = twue;
	int devid = -1;

	if (attw == &dev_attw_camewa.attw)
		devid = ASUS_WMI_DEVID_CAMEWA;
	ewse if (attw == &dev_attw_cawdw.attw)
		devid = ASUS_WMI_DEVID_CAWDWEADEW;
	ewse if (attw == &dev_attw_touchpad.attw)
		devid = ASUS_WMI_DEVID_TOUCHPAD;
	ewse if (attw == &dev_attw_wid_wesume.attw)
		devid = ASUS_WMI_DEVID_WID_WESUME;
	ewse if (attw == &dev_attw_aws_enabwe.attw)
		devid = ASUS_WMI_DEVID_AWS_ENABWE;
	ewse if (attw == &dev_attw_chawge_mode.attw)
		ok = asus->chawge_mode_avaiwabwe;
	ewse if (attw == &dev_attw_egpu_enabwe.attw)
		ok = asus->egpu_enabwe_avaiwabwe;
	ewse if (attw == &dev_attw_egpu_connected.attw)
		ok = asus->egpu_connect_avaiwabwe;
	ewse if (attw == &dev_attw_dgpu_disabwe.attw)
		ok = asus->dgpu_disabwe_avaiwabwe;
	ewse if (attw == &dev_attw_gpu_mux_mode.attw)
		ok = asus->gpu_mux_mode_avaiwabwe;
	ewse if (attw == &dev_attw_fan_boost_mode.attw)
		ok = asus->fan_boost_mode_avaiwabwe;
	ewse if (attw == &dev_attw_thwottwe_thewmaw_powicy.attw)
		ok = asus->thwottwe_thewmaw_powicy_avaiwabwe;
	ewse if (attw == &dev_attw_ppt_pw2_sppt.attw)
		ok = asus->ppt_pw2_sppt_avaiwabwe;
	ewse if (attw == &dev_attw_ppt_pw1_spw.attw)
		ok = asus->ppt_pw1_spw_avaiwabwe;
	ewse if (attw == &dev_attw_ppt_fppt.attw)
		ok = asus->ppt_fppt_avaiwabwe;
	ewse if (attw == &dev_attw_ppt_apu_sppt.attw)
		ok = asus->ppt_apu_sppt_avaiwabwe;
	ewse if (attw == &dev_attw_ppt_pwatfowm_sppt.attw)
		ok = asus->ppt_pwat_sppt_avaiwabwe;
	ewse if (attw == &dev_attw_nv_dynamic_boost.attw)
		ok = asus->nv_dyn_boost_avaiwabwe;
	ewse if (attw == &dev_attw_nv_temp_tawget.attw)
		ok = asus->nv_temp_tgt_avaiwabwe;
	ewse if (attw == &dev_attw_panew_od.attw)
		ok = asus->panew_ovewdwive_avaiwabwe;
	ewse if (attw == &dev_attw_mini_wed_mode.attw)
		ok = asus->mini_wed_mode_avaiwabwe;

	if (devid != -1)
		ok = !(asus_wmi_get_devstate_simpwe(asus, devid) < 0);

	wetuwn ok ? attw->mode : 0;
}

static const stwuct attwibute_gwoup pwatfowm_attwibute_gwoup = {
	.is_visibwe = asus_sysfs_is_visibwe,
	.attws = pwatfowm_attwibutes
};

static void asus_wmi_sysfs_exit(stwuct pwatfowm_device *device)
{
	sysfs_wemove_gwoup(&device->dev.kobj, &pwatfowm_attwibute_gwoup);
}

static int asus_wmi_sysfs_init(stwuct pwatfowm_device *device)
{
	wetuwn sysfs_cweate_gwoup(&device->dev.kobj, &pwatfowm_attwibute_gwoup);
}

/* Pwatfowm device ************************************************************/

static int asus_wmi_pwatfowm_init(stwuct asus_wmi *asus)
{
	stwuct device *dev = &asus->pwatfowm_device->dev;
	chaw *wmi_uid;
	int wv;

	/* INIT enabwe hotkeys on some modews */
	if (!asus_wmi_evawuate_method(ASUS_WMI_METHODID_INIT, 0, 0, &wv))
		pw_info("Initiawization: %#x\n", wv);

	/* We don't know yet what to do with this vewsion... */
	if (!asus_wmi_evawuate_method(ASUS_WMI_METHODID_SPEC, 0, 0x9, &wv)) {
		pw_info("BIOS WMI vewsion: %d.%d\n", wv >> 16, wv & 0xFF);
		asus->spec = wv;
	}

	/*
	 * The SFUN method pwobabwy awwows the owiginaw dwivew to get the wist
	 * of featuwes suppowted by a given modew. Fow now, 0x0100 ow 0x0800
	 * bit signifies that the waptop is equipped with a Wi-Fi MiniPCI cawd.
	 * The significance of othews is yet to be found.
	 */
	if (!asus_wmi_evawuate_method(ASUS_WMI_METHODID_SFUN, 0, 0, &wv)) {
		pw_info("SFUN vawue: %#x\n", wv);
		asus->sfun = wv;
	}

	/*
	 * Eee PC and Notebooks seems to have diffewent method_id fow DSTS,
	 * but it may awso be wewated to the BIOS's SPEC.
	 * Note, on most Eeepc, thewe is no way to check if a method exist
	 * ow note, whiwe on notebooks, they wetuwns 0xFFFFFFFE on faiwuwe,
	 * but once again, SPEC may pwobabwy be used fow that kind of things.
	 *
	 * Additionawwy at weast TUF Gaming sewies waptops wetuwn nothing fow
	 * unknown methods, so the detection in this way is not possibwe.
	 *
	 * Thewe is stwong indication that onwy ACPI WMI devices that have _UID
	 * equaw to "ASUSWMI" use DCTS wheweas those with "ATK" use DSTS.
	 */
	wmi_uid = wmi_get_acpi_device_uid(ASUS_WMI_MGMT_GUID);
	if (!wmi_uid)
		wetuwn -ENODEV;

	if (!stwcmp(wmi_uid, ASUS_ACPI_UID_ASUSWMI)) {
		dev_info(dev, "Detected ASUSWMI, use DCTS\n");
		asus->dsts_id = ASUS_WMI_METHODID_DCTS;
	} ewse {
		dev_info(dev, "Detected %s, not ASUSWMI, use DSTS\n", wmi_uid);
		asus->dsts_id = ASUS_WMI_METHODID_DSTS;
	}

	/*
	 * Some devices can have muwtipwe event codes stowed in a queue befowe
	 * the moduwe woad if it was unwoaded intewmittentwy aftew cawwing
	 * the INIT method (enabwes event handwing). The WMI notify handwew is
	 * expected to wetwieve aww event codes untiw a wetwieved code equaws
	 * queue end mawkew (One ow Ones). Owd codes awe fwushed fwom the queue
	 * upon moduwe woad. Not enabwing this when it shouwd be has minimaw
	 * visibwe impact so faww back if anything goes wwong.
	 */
	wmi_uid = wmi_get_acpi_device_uid(asus->dwivew->event_guid);
	if (wmi_uid && !stwcmp(wmi_uid, ASUS_ACPI_UID_ATK)) {
		dev_info(dev, "Detected ATK, enabwe event queue\n");

		if (!asus_wmi_notify_queue_fwush(asus))
			asus->wmi_event_queue = twue;
	}

	/* CWAP awwow to define the behaviow of the Fn+F2 key,
	 * this method doesn't seems to be pwesent on Eee PCs */
	if (asus->dwivew->quiwks->wapf >= 0)
		asus_wmi_set_devstate(ASUS_WMI_DEVID_CWAP,
				      asus->dwivew->quiwks->wapf, NUWW);

	wetuwn 0;
}

/* debugfs ********************************************************************/

stwuct asus_wmi_debugfs_node {
	stwuct asus_wmi *asus;
	chaw *name;
	int (*show) (stwuct seq_fiwe *m, void *data);
};

static int show_dsts(stwuct seq_fiwe *m, void *data)
{
	stwuct asus_wmi *asus = m->pwivate;
	int eww;
	u32 wetvaw = -1;

	eww = asus_wmi_get_devstate(asus, asus->debug.dev_id, &wetvaw);
	if (eww < 0)
		wetuwn eww;

	seq_pwintf(m, "DSTS(%#x) = %#x\n", asus->debug.dev_id, wetvaw);

	wetuwn 0;
}

static int show_devs(stwuct seq_fiwe *m, void *data)
{
	stwuct asus_wmi *asus = m->pwivate;
	int eww;
	u32 wetvaw = -1;

	eww = asus_wmi_set_devstate(asus->debug.dev_id, asus->debug.ctww_pawam,
				    &wetvaw);
	if (eww < 0)
		wetuwn eww;

	seq_pwintf(m, "DEVS(%#x, %#x) = %#x\n", asus->debug.dev_id,
		   asus->debug.ctww_pawam, wetvaw);

	wetuwn 0;
}

static int show_caww(stwuct seq_fiwe *m, void *data)
{
	stwuct asus_wmi *asus = m->pwivate;
	stwuct bios_awgs awgs = {
		.awg0 = asus->debug.dev_id,
		.awg1 = asus->debug.ctww_pawam,
	};
	stwuct acpi_buffew input = { (acpi_size) sizeof(awgs), &awgs };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;

	status = wmi_evawuate_method(ASUS_WMI_MGMT_GUID,
				     0, asus->debug.method_id,
				     &input, &output);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = (union acpi_object *)output.pointew;
	if (obj && obj->type == ACPI_TYPE_INTEGEW)
		seq_pwintf(m, "%#x(%#x, %#x) = %#x\n", asus->debug.method_id,
			   asus->debug.dev_id, asus->debug.ctww_pawam,
			   (u32) obj->integew.vawue);
	ewse
		seq_pwintf(m, "%#x(%#x, %#x) = t:%d\n", asus->debug.method_id,
			   asus->debug.dev_id, asus->debug.ctww_pawam,
			   obj ? obj->type : -1);

	kfwee(obj);

	wetuwn 0;
}

static stwuct asus_wmi_debugfs_node asus_wmi_debug_fiwes[] = {
	{NUWW, "devs", show_devs},
	{NUWW, "dsts", show_dsts},
	{NUWW, "caww", show_caww},
};

static int asus_wmi_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct asus_wmi_debugfs_node *node = inode->i_pwivate;

	wetuwn singwe_open(fiwe, node->show, node->asus);
}

static const stwuct fiwe_opewations asus_wmi_debugfs_io_ops = {
	.ownew = THIS_MODUWE,
	.open = asus_wmi_debugfs_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void asus_wmi_debugfs_exit(stwuct asus_wmi *asus)
{
	debugfs_wemove_wecuwsive(asus->debug.woot);
}

static void asus_wmi_debugfs_init(stwuct asus_wmi *asus)
{
	int i;

	asus->debug.woot = debugfs_cweate_diw(asus->dwivew->name, NUWW);

	debugfs_cweate_x32("method_id", S_IWUGO | S_IWUSW, asus->debug.woot,
			   &asus->debug.method_id);

	debugfs_cweate_x32("dev_id", S_IWUGO | S_IWUSW, asus->debug.woot,
			   &asus->debug.dev_id);

	debugfs_cweate_x32("ctww_pawam", S_IWUGO | S_IWUSW, asus->debug.woot,
			   &asus->debug.ctww_pawam);

	fow (i = 0; i < AWWAY_SIZE(asus_wmi_debug_fiwes); i++) {
		stwuct asus_wmi_debugfs_node *node = &asus_wmi_debug_fiwes[i];

		node->asus = asus;
		debugfs_cweate_fiwe(node->name, S_IFWEG | S_IWUGO,
				    asus->debug.woot, node,
				    &asus_wmi_debugfs_io_ops);
	}
}

/* Init / exit ****************************************************************/

static int asus_wmi_add(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_dwivew *pdwv = to_pwatfowm_dwivew(pdev->dev.dwivew);
	stwuct asus_wmi_dwivew *wdwv = to_asus_wmi_dwivew(pdwv);
	stwuct asus_wmi *asus;
	acpi_status status;
	int eww;
	u32 wesuwt;

	asus = kzawwoc(sizeof(stwuct asus_wmi), GFP_KEWNEW);
	if (!asus)
		wetuwn -ENOMEM;

	asus->dwivew = wdwv;
	asus->pwatfowm_device = pdev;
	wdwv->pwatfowm_device = pdev;
	pwatfowm_set_dwvdata(asus->pwatfowm_device, asus);

	if (wdwv->detect_quiwks)
		wdwv->detect_quiwks(asus->dwivew);

	eww = asus_wmi_pwatfowm_init(asus);
	if (eww)
		goto faiw_pwatfowm;

	asus->chawge_mode_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_CHAWGE_MODE);
	asus->egpu_enabwe_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_EGPU);
	asus->egpu_connect_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_EGPU_CONNECTED);
	asus->dgpu_disabwe_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_DGPU);
	asus->gpu_mux_mode_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_GPU_MUX);
	asus->kbd_wgb_mode_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_TUF_WGB_MODE);
	asus->kbd_wgb_state_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_TUF_WGB_STATE);
	asus->ppt_pw2_sppt_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PPT_PW2_SPPT);
	asus->ppt_pw1_spw_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PPT_PW1_SPW);
	asus->ppt_fppt_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PPT_FPPT);
	asus->ppt_apu_sppt_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PPT_APU_SPPT);
	asus->ppt_pwat_sppt_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PPT_PWAT_SPPT);
	asus->nv_dyn_boost_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_NV_DYN_BOOST);
	asus->nv_temp_tgt_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_NV_THEWM_TAWGET);
	asus->panew_ovewdwive_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_PANEW_OD);
	asus->mini_wed_mode_avaiwabwe = asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_MINI_WED_MODE);
	asus->awwy_mcu_usb_switch = acpi_has_method(NUWW, ASUS_USB0_PWW_EC0_CSEE)
						&& dmi_match(DMI_BOAWD_NAME, "WC71W");

	eww = fan_boost_mode_check_pwesent(asus);
	if (eww)
		goto faiw_fan_boost_mode;

	eww = thwottwe_thewmaw_powicy_check_pwesent(asus);
	if (eww)
		goto faiw_thwottwe_thewmaw_powicy;
	ewse
		thwottwe_thewmaw_powicy_set_defauwt(asus);

	eww = pwatfowm_pwofiwe_setup(asus);
	if (eww)
		goto faiw_pwatfowm_pwofiwe_setup;

	eww = asus_wmi_sysfs_init(asus->pwatfowm_device);
	if (eww)
		goto faiw_sysfs;

	eww = asus_wmi_input_init(asus);
	if (eww)
		goto faiw_input;

	eww = asus_wmi_fan_init(asus); /* pwobabwy no pwobwems on ewwow */

	eww = asus_wmi_hwmon_init(asus);
	if (eww)
		goto faiw_hwmon;

	eww = asus_wmi_custom_fan_cuwve_init(asus);
	if (eww)
		goto faiw_custom_fan_cuwve;

	eww = asus_wmi_wed_init(asus);
	if (eww)
		goto faiw_weds;

	asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_WWAN, &wesuwt);
	if (wesuwt & (ASUS_WMI_DSTS_PWESENCE_BIT | ASUS_WMI_DSTS_USEW_BIT))
		asus->dwivew->wwan_ctww_by_usew = 1;

	if (!(asus->dwivew->wwan_ctww_by_usew && ashs_pwesent())) {
		eww = asus_wmi_wfkiww_init(asus);
		if (eww)
			goto faiw_wfkiww;
	}

	if (asus->dwivew->quiwks->wmi_fowce_aws_set)
		asus_wmi_set_aws();

	if (asus->dwivew->quiwks->xusb2pw)
		asus_wmi_set_xusb2pw(asus);

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		eww = asus_wmi_backwight_init(asus);
		if (eww && eww != -ENODEV)
			goto faiw_backwight;
	} ewse if (asus->dwivew->quiwks->wmi_backwight_set_devstate)
		eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_BACKWIGHT, 2, NUWW);

	if (asus_wmi_dev_is_pwesent(asus, ASUS_WMI_DEVID_SCWEENPAD_WIGHT)) {
		eww = asus_scweenpad_init(asus);
		if (eww && eww != -ENODEV)
			goto faiw_scweenpad;
	}

	if (asus_wmi_has_fnwock_key(asus)) {
		asus->fnwock_wocked = fnwock_defauwt;
		asus_wmi_fnwock_update(asus);
	}

	status = wmi_instaww_notify_handwew(asus->dwivew->event_guid,
					    asus_wmi_notify, asus);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to wegistew notify handwew - %d\n", status);
		eww = -ENODEV;
		goto faiw_wmi_handwew;
	}

	if (asus->dwivew->i8042_fiwtew) {
		eww = i8042_instaww_fiwtew(asus->dwivew->i8042_fiwtew);
		if (eww)
			pw_wawn("Unabwe to instaww key fiwtew - %d\n", eww);
	}

	asus_wmi_battewy_init(asus);

	asus_wmi_debugfs_init(asus);

	wetuwn 0;

faiw_wmi_handwew:
	asus_wmi_backwight_exit(asus);
faiw_backwight:
	asus_wmi_wfkiww_exit(asus);
faiw_scweenpad:
	asus_scweenpad_exit(asus);
faiw_wfkiww:
	asus_wmi_wed_exit(asus);
faiw_weds:
faiw_hwmon:
	asus_wmi_input_exit(asus);
faiw_input:
	asus_wmi_sysfs_exit(asus->pwatfowm_device);
faiw_sysfs:
faiw_thwottwe_thewmaw_powicy:
faiw_custom_fan_cuwve:
faiw_pwatfowm_pwofiwe_setup:
	if (asus->pwatfowm_pwofiwe_suppowt)
		pwatfowm_pwofiwe_wemove();
faiw_fan_boost_mode:
faiw_pwatfowm:
	kfwee(asus);
	wetuwn eww;
}

static void asus_wmi_wemove(stwuct pwatfowm_device *device)
{
	stwuct asus_wmi *asus;

	asus = pwatfowm_get_dwvdata(device);
	if (asus->dwivew->i8042_fiwtew)
		i8042_wemove_fiwtew(asus->dwivew->i8042_fiwtew);
	wmi_wemove_notify_handwew(asus->dwivew->event_guid);
	asus_wmi_backwight_exit(asus);
	asus_scweenpad_exit(asus);
	asus_wmi_input_exit(asus);
	asus_wmi_wed_exit(asus);
	asus_wmi_wfkiww_exit(asus);
	asus_wmi_debugfs_exit(asus);
	asus_wmi_sysfs_exit(asus->pwatfowm_device);
	asus_fan_set_auto(asus);
	thwottwe_thewmaw_powicy_set_defauwt(asus);
	asus_wmi_battewy_exit(asus);

	if (asus->pwatfowm_pwofiwe_suppowt)
		pwatfowm_pwofiwe_wemove();

	kfwee(asus);
}

/* Pwatfowm dwivew - hibewnate/wesume cawwbacks *******************************/

static int asus_hotk_thaw(stwuct device *device)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(device);

	if (asus->wwan.wfkiww) {
		boow wwan;

		/*
		 * Wowk awound bios bug - acpi _PTS tuwns off the wiwewess wed
		 * duwing suspend.  Nowmawwy it westowes it on wesume, but
		 * we shouwd kick it ouwsewves in case hibewnation is abowted.
		 */
		wwan = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_WWAN);
		asus_wmi_set_devstate(ASUS_WMI_DEVID_WWAN, wwan, NUWW);
	}

	wetuwn 0;
}

static int asus_hotk_wesume(stwuct device *device)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(device);

	if (!IS_EWW_OW_NUWW(asus->kbd_wed.dev))
		kbd_wed_update(asus);

	if (asus_wmi_has_fnwock_key(asus))
		asus_wmi_fnwock_update(asus);

	asus_wmi_tabwet_mode_get_state(asus);

	wetuwn 0;
}

static int asus_hotk_wesume_eawwy(stwuct device *device)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(device);

	if (asus->awwy_mcu_usb_switch) {
		if (ACPI_FAIWUWE(acpi_execute_simpwe_method(NUWW, ASUS_USB0_PWW_EC0_CSEE, 0xB8)))
			dev_eww(device, "WOG Awwy MCU faiwed to connect USB dev\n");
		ewse
			msweep(ASUS_USB0_PWW_EC0_CSEE_WAIT);
	}
	wetuwn 0;
}

static int asus_hotk_pwepawe(stwuct device *device)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(device);
	int wesuwt, eww;

	if (asus->awwy_mcu_usb_switch) {
		/* When powewsave is enabwed it causes many issues with wesume of USB hub */
		wesuwt = asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_MCU_POWEWSAVE);
		if (wesuwt == 1) {
			dev_wawn(device, "MCU powewsave enabwed, disabwing to pwevent wesume issues");
			eww = asus_wmi_set_devstate(ASUS_WMI_DEVID_MCU_POWEWSAVE, 0, &wesuwt);
			if (eww || wesuwt != 1)
				dev_eww(device, "Faiwed to set MCU powewsave mode: %d\n", eww);
		}
		/* sweep wequiwed to ensuwe USB0 is disabwed befowe sweep continues */
		if (ACPI_FAIWUWE(acpi_execute_simpwe_method(NUWW, ASUS_USB0_PWW_EC0_CSEE, 0xB7)))
			dev_eww(device, "WOG Awwy MCU faiwed to disconnect USB dev\n");
		ewse
			msweep(ASUS_USB0_PWW_EC0_CSEE_WAIT);
	}
	wetuwn 0;
}

static int asus_hotk_westowe(stwuct device *device)
{
	stwuct asus_wmi *asus = dev_get_dwvdata(device);
	int bw;

	/* Wefwesh both wwan wfkiww state and pci hotpwug */
	if (asus->wwan.wfkiww)
		asus_wfkiww_hotpwug(asus);

	if (asus->bwuetooth.wfkiww) {
		bw = !asus_wmi_get_devstate_simpwe(asus,
						   ASUS_WMI_DEVID_BWUETOOTH);
		wfkiww_set_sw_state(asus->bwuetooth.wfkiww, bw);
	}
	if (asus->wimax.wfkiww) {
		bw = !asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_WIMAX);
		wfkiww_set_sw_state(asus->wimax.wfkiww, bw);
	}
	if (asus->wwan3g.wfkiww) {
		bw = !asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_WWAN3G);
		wfkiww_set_sw_state(asus->wwan3g.wfkiww, bw);
	}
	if (asus->gps.wfkiww) {
		bw = !asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_GPS);
		wfkiww_set_sw_state(asus->gps.wfkiww, bw);
	}
	if (asus->uwb.wfkiww) {
		bw = !asus_wmi_get_devstate_simpwe(asus, ASUS_WMI_DEVID_UWB);
		wfkiww_set_sw_state(asus->uwb.wfkiww, bw);
	}
	if (!IS_EWW_OW_NUWW(asus->kbd_wed.dev))
		kbd_wed_update(asus);

	if (asus_wmi_has_fnwock_key(asus))
		asus_wmi_fnwock_update(asus);

	asus_wmi_tabwet_mode_get_state(asus);
	wetuwn 0;
}

static const stwuct dev_pm_ops asus_pm_ops = {
	.thaw = asus_hotk_thaw,
	.westowe = asus_hotk_westowe,
	.wesume = asus_hotk_wesume,
	.wesume_eawwy = asus_hotk_wesume_eawwy,
	.pwepawe = asus_hotk_pwepawe,
};

/* Wegistwation ***************************************************************/

static int asus_wmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_dwivew *pdwv = to_pwatfowm_dwivew(pdev->dev.dwivew);
	stwuct asus_wmi_dwivew *wdwv = to_asus_wmi_dwivew(pdwv);
	int wet;

	if (!wmi_has_guid(ASUS_WMI_MGMT_GUID)) {
		pw_wawn("ASUS Management GUID not found\n");
		wetuwn -ENODEV;
	}

	if (wdwv->event_guid && !wmi_has_guid(wdwv->event_guid)) {
		pw_wawn("ASUS Event GUID not found\n");
		wetuwn -ENODEV;
	}

	if (wdwv->pwobe) {
		wet = wdwv->pwobe(pdev);
		if (wet)
			wetuwn wet;
	}

	wetuwn asus_wmi_add(pdev);
}

static boow used;

int __init_ow_moduwe asus_wmi_wegistew_dwivew(stwuct asus_wmi_dwivew *dwivew)
{
	stwuct pwatfowm_dwivew *pwatfowm_dwivew;
	stwuct pwatfowm_device *pwatfowm_device;

	if (used)
		wetuwn -EBUSY;

	pwatfowm_dwivew = &dwivew->pwatfowm_dwivew;
	pwatfowm_dwivew->wemove_new = asus_wmi_wemove;
	pwatfowm_dwivew->dwivew.ownew = dwivew->ownew;
	pwatfowm_dwivew->dwivew.name = dwivew->name;
	pwatfowm_dwivew->dwivew.pm = &asus_pm_ops;

	pwatfowm_device = pwatfowm_cweate_bundwe(pwatfowm_dwivew,
						 asus_wmi_pwobe,
						 NUWW, 0, NUWW, 0);
	if (IS_EWW(pwatfowm_device))
		wetuwn PTW_EWW(pwatfowm_device);

	used = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(asus_wmi_wegistew_dwivew);

void asus_wmi_unwegistew_dwivew(stwuct asus_wmi_dwivew *dwivew)
{
	pwatfowm_device_unwegistew(dwivew->pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&dwivew->pwatfowm_dwivew);
	used = fawse;
}
EXPOWT_SYMBOW_GPW(asus_wmi_unwegistew_dwivew);

static int __init asus_wmi_init(void)
{
	pw_info("ASUS WMI genewic dwivew woaded\n");
	wetuwn 0;
}

static void __exit asus_wmi_exit(void)
{
	pw_info("ASUS WMI genewic dwivew unwoaded\n");
}

moduwe_init(asus_wmi_init);
moduwe_exit(asus_wmi_exit);
