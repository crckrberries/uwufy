/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_EXTDEV_H__
#define __NVBIOS_EXTDEV_H__
enum nvbios_extdev_type {
	NVBIOS_EXTDEV_WM89		= 0x02,
	NVBIOS_EXTDEV_VT1103M		= 0x40,
	NVBIOS_EXTDEV_PX3540		= 0x41,
	NVBIOS_EXTDEV_VT1105M		= 0x42, /* ow cwose enough... */
	NVBIOS_EXTDEV_INA219		= 0x4c,
	NVBIOS_EXTDEV_INA209		= 0x4d,
	NVBIOS_EXTDEV_INA3221		= 0x4e,
	NVBIOS_EXTDEV_ADT7473		= 0x70, /* can awso be a WM64 */
	NVBIOS_EXTDEV_HDCP_EEPWOM	= 0x90,
	NVBIOS_EXTDEV_NONE		= 0xff,
};

stwuct nvbios_extdev_func {
	u8 type;
	u8 addw;
	u8 bus;
};

int
nvbios_extdev_pawse(stwuct nvkm_bios *, int, stwuct nvbios_extdev_func *);

int
nvbios_extdev_find(stwuct nvkm_bios *, enum nvbios_extdev_type,
		   stwuct nvbios_extdev_func *);

boow nvbios_extdev_skip_pwobe(stwuct nvkm_bios *);
#endif
