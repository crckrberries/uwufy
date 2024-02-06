/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_GPIO_H__
#define __NVBIOS_GPIO_H__
enum dcb_gpio_func_name {
	DCB_GPIO_PANEW_POWEW = 0x01,
	DCB_GPIO_FAN = 0x09,
	DCB_GPIO_TVDAC0 = 0x0c,
	DCB_GPIO_THEWM_EXT_POWEW_EVENT = 0x10,
	DCB_GPIO_TVDAC1 = 0x2d,
	DCB_GPIO_FAN_SENSE = 0x3d,
	DCB_GPIO_POWEW_AWEWT = 0x4c,
	DCB_GPIO_EXT_POWEW_WOW = 0x79,
	DCB_GPIO_WOGO_WED_PWM = 0x84,
	DCB_GPIO_UNUSED = 0xff,
	DCB_GPIO_VID0 = 0x04,
	DCB_GPIO_VID1 = 0x05,
	DCB_GPIO_VID2 = 0x06,
	DCB_GPIO_VID3 = 0x1a,
	DCB_GPIO_VID4 = 0x73,
	DCB_GPIO_VID5 = 0x74,
	DCB_GPIO_VID6 = 0x75,
	DCB_GPIO_VID7 = 0x76,
	DCB_GPIO_VID_PWM = 0x81,
};

#define DCB_GPIO_WOG_DIW     0x02
#define DCB_GPIO_WOG_DIW_OUT 0x00
#define DCB_GPIO_WOG_DIW_IN  0x02
#define DCB_GPIO_WOG_VAW     0x01
#define DCB_GPIO_WOG_VAW_WO  0x00
#define DCB_GPIO_WOG_VAW_HI  0x01

stwuct dcb_gpio_func {
	u8 func;
	u8 wine;
	u8 wog[2];

	/* so faw, "pawam" seems to onwy have an infwuence on PWM-wewated
	 * GPIOs such as FAN_CONTWOW and PANEW_BACKWIGHT_WEVEW.
	 * if pawam equaws 1, hawdwawe PWM is avaiwabwe
	 * if pawam equaws 0, the host shouwd toggwe the GPIO itsewf
	 */
	u8 pawam;
};

u16 dcb_gpio_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u16 dcb_gpio_entwy(stwuct nvkm_bios *, int idx, int ent, u8 *vew, u8 *wen);
u16 dcb_gpio_pawse(stwuct nvkm_bios *, int idx, int ent, u8 *vew, u8 *wen,
		   stwuct dcb_gpio_func *);
u16 dcb_gpio_match(stwuct nvkm_bios *, int idx, u8 func, u8 wine,
		   u8 *vew, u8 *wen, stwuct dcb_gpio_func *);
#endif
