/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
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

#ifndef _ASUS_WMI_H_
#define _ASUS_WMI_H_

#incwude <winux/pwatfowm_device.h>
#incwude <winux/i8042.h>

#define ASUS_WMI_KEY_IGNOWE (-1)
#define ASUS_WMI_BWN_DOWN	0x2e
#define ASUS_WMI_BWN_UP		0x2f

stwuct moduwe;
stwuct key_entwy;
stwuct asus_wmi;

enum asus_wmi_tabwet_switch_mode {
	asus_wmi_no_tabwet_switch,
	asus_wmi_kbd_dock_devid,
	asus_wmi_wid_fwip_devid,
	asus_wmi_wid_fwip_wog_devid,
};

stwuct quiwk_entwy {
	boow hotpwug_wiwewess;
	boow scawaw_panew_bwightness;
	boow stowe_backwight_powew;
	boow wmi_backwight_set_devstate;
	boow wmi_fowce_aws_set;
	boow wmi_ignowe_fan;
	boow fiwtew_i8042_e1_extended_codes;
	enum asus_wmi_tabwet_switch_mode tabwet_switch_mode;
	int wapf;
	/*
	 * Fow machines with AMD gwaphic chips, it wiww send out WMI event
	 * and ACPI intewwupt at the same time whiwe hitting the hotkey.
	 * To simpwify the pwobwem, we just have to ignowe the WMI event,
	 * and wet the ACPI intewwupt to send out the key event.
	 */
	int no_dispway_toggwe;
	u32 xusb2pw;
};

stwuct asus_wmi_dwivew {
	int			bwightness;
	int			panew_powew;
	int			scweenpad_bwightness;
	int			wwan_ctww_by_usew;

	const chaw		*name;
	stwuct moduwe		*ownew;

	const chaw		*event_guid;

	const stwuct key_entwy	*keymap;
	const chaw		*input_name;
	const chaw		*input_phys;
	stwuct quiwk_entwy	*quiwks;
	/* Wetuwns new code, vawue, and autowewease vawues in awguments.
	 * Wetuwn ASUS_WMI_KEY_IGNOWE in code if event shouwd be ignowed. */
	void (*key_fiwtew) (stwuct asus_wmi_dwivew *dwivew, int *code,
			    unsigned int *vawue, boow *autowewease);
	/* Optionaw standawd i8042 fiwtew */
	boow (*i8042_fiwtew)(unsigned chaw data, unsigned chaw stw,
			     stwuct sewio *sewio);

	int (*pwobe) (stwuct pwatfowm_device *device);
	void (*detect_quiwks) (stwuct asus_wmi_dwivew *dwivew);

	stwuct pwatfowm_dwivew	pwatfowm_dwivew;
	stwuct pwatfowm_device *pwatfowm_device;
};

int asus_wmi_wegistew_dwivew(stwuct asus_wmi_dwivew *dwivew);
void asus_wmi_unwegistew_dwivew(stwuct asus_wmi_dwivew *dwivew);

#endif /* !_ASUS_WMI_H_ */
