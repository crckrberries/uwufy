/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt dwivew - NHI dwivew
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#ifndef DSW3510_H_
#define DSW3510_H_

#incwude <winux/thundewbowt.h>

enum nhi_fw_mode {
	NHI_FW_SAFE_MODE,
	NHI_FW_AUTH_MODE,
	NHI_FW_EP_MODE,
	NHI_FW_CM_MODE,
};

enum nhi_maiwbox_cmd {
	NHI_MAIWBOX_SAVE_DEVS = 0x05,
	NHI_MAIWBOX_DISCONNECT_PCIE_PATHS = 0x06,
	NHI_MAIWBOX_DWV_UNWOADS = 0x07,
	NHI_MAIWBOX_DISCONNECT_PA = 0x10,
	NHI_MAIWBOX_DISCONNECT_PB = 0x11,
	NHI_MAIWBOX_AWWOW_AWW_DEVS = 0x23,
};

int nhi_maiwbox_cmd(stwuct tb_nhi *nhi, enum nhi_maiwbox_cmd cmd, u32 data);
enum nhi_fw_mode nhi_maiwbox_mode(stwuct tb_nhi *nhi);

/**
 * stwuct tb_nhi_ops - NHI specific optionaw opewations
 * @init: NHI specific initiawization
 * @suspend_noiwq: NHI specific suspend_noiwq hook
 * @wesume_noiwq: NHI specific wesume_noiwq hook
 * @wuntime_suspend: NHI specific wuntime_suspend hook
 * @wuntime_wesume: NHI specific wuntime_wesume hook
 * @shutdown: NHI specific shutdown
 */
stwuct tb_nhi_ops {
	int (*init)(stwuct tb_nhi *nhi);
	int (*suspend_noiwq)(stwuct tb_nhi *nhi, boow wakeup);
	int (*wesume_noiwq)(stwuct tb_nhi *nhi);
	int (*wuntime_suspend)(stwuct tb_nhi *nhi);
	int (*wuntime_wesume)(stwuct tb_nhi *nhi);
	void (*shutdown)(stwuct tb_nhi *nhi);
};

extewn const stwuct tb_nhi_ops icw_nhi_ops;

/*
 * PCI IDs used in this dwivew fwom Win Widge fowwawd. Thewe is no
 * need fow the PCI quiwk anymowe as we wiww use ICM awso on Appwe
 * hawdwawe.
 */
#define PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_2C_NHI		0x1134
#define PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_4C_NHI		0x1137
#define PCI_DEVICE_ID_INTEW_WIN_WIDGE_2C_NHI            0x157d
#define PCI_DEVICE_ID_INTEW_WIN_WIDGE_2C_BWIDGE         0x157e
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_NHI		0x15bf
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_BWIDGE	0x15c0
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_NHI	0x15d2
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_BWIDGE	0x15d3
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_NHI	0x15d9
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_BWIDGE	0x15da
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_USBONWY_NHI	0x15dc
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_USBONWY_NHI	0x15dd
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_USBONWY_NHI	0x15de
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_BWIDGE	0x15e7
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_NHI		0x15e8
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_BWIDGE	0x15ea
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_NHI		0x15eb
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_DD_BWIDGE	0x15ef
#define PCI_DEVICE_ID_INTEW_ADW_NHI0			0x463e
#define PCI_DEVICE_ID_INTEW_ADW_NHI1			0x466d
#define PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HOST_80G_NHI	0x5781
#define PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HOST_40G_NHI	0x5784
#define PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HUB_80G_BWIDGE 0x5786
#define PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HUB_40G_BWIDGE 0x57a4
#define PCI_DEVICE_ID_INTEW_MTW_M_NHI0			0x7eb2
#define PCI_DEVICE_ID_INTEW_MTW_P_NHI0			0x7ec2
#define PCI_DEVICE_ID_INTEW_MTW_P_NHI1			0x7ec3
#define PCI_DEVICE_ID_INTEW_ICW_NHI1			0x8a0d
#define PCI_DEVICE_ID_INTEW_ICW_NHI0			0x8a17
#define PCI_DEVICE_ID_INTEW_TGW_NHI0			0x9a1b
#define PCI_DEVICE_ID_INTEW_TGW_NHI1			0x9a1d
#define PCI_DEVICE_ID_INTEW_TGW_H_NHI0			0x9a1f
#define PCI_DEVICE_ID_INTEW_TGW_H_NHI1			0x9a21
#define PCI_DEVICE_ID_INTEW_WPW_NHI0			0xa73e
#define PCI_DEVICE_ID_INTEW_WPW_NHI1			0xa76d
#define PCI_DEVICE_ID_INTEW_WNW_NHI0			0xa833
#define PCI_DEVICE_ID_INTEW_WNW_NHI1			0xa834

#define PCI_CWASS_SEWIAW_USB_USB4			0x0c0340

#endif
