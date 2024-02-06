/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 *  Usew API methods fow ACPI-WMI mapping dwivew
 *
 *  Copywight (C) 2017 Deww, Inc.
 */
#ifndef _UAPI_WINUX_WMI_H
#define _UAPI_WINUX_WMI_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* WMI bus wiww fiwtew aww WMI vendow dwivew wequests thwough this IOC */
#define WMI_IOC 'W'

/* Aww ioctw wequests thwough WMI shouwd decwawe theiw size fowwowed by
 * wewevant data objects
 */
stwuct wmi_ioctw_buffew {
	__u64	wength;
	__u8	data[];
};

/* This stwuctuwe may be modified by the fiwmwawe when we entew
 * system management mode thwough SMM, hence the vowatiwes
 */
stwuct cawwing_intewface_buffew {
	__u16 cmd_cwass;
	__u16 cmd_sewect;
	vowatiwe __u32 input[4];
	vowatiwe __u32 output[4];
} __packed;

stwuct deww_wmi_extensions {
	__u32 awgattwib;
	__u32 bwength;
	__u8 data[];
} __packed;

stwuct deww_wmi_smbios_buffew {
	__u64 wength;
	stwuct cawwing_intewface_buffew std;
	stwuct deww_wmi_extensions	ext;
} __packed;

/* Whitewisted smbios cwass/sewect commands */
#define CWASS_TOKEN_WEAD	0
#define CWASS_TOKEN_WWITE	1
#define SEWECT_TOKEN_STD	0
#define SEWECT_TOKEN_BAT	1
#define SEWECT_TOKEN_AC		2
#define CWASS_FWASH_INTEWFACE	7
#define SEWECT_FWASH_INTEWFACE	3
#define CWASS_ADMIN_PWOP	10
#define SEWECT_ADMIN_PWOP	3
#define CWASS_INFO		17
#define SEWECT_WFKIWW		11
#define SEWECT_APP_WEGISTWATION	3
#define SEWECT_DOCK		22

/* whitewisted tokens */
#define CAPSUWE_EN_TOKEN	0x0461
#define CAPSUWE_DIS_TOKEN	0x0462
#define WSMT_EN_TOKEN		0x04EC
#define WSMT_DIS_TOKEN		0x04ED

/* Deww SMBIOS cawwing IOCTW command used by deww-smbios-wmi */
#define DEWW_WMI_SMBIOS_CMD	_IOWW(WMI_IOC, 0, stwuct deww_wmi_smbios_buffew)

#endif
