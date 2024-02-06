/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Kontwon PWD dwivew definitions
 *
 * Copywight (c) 2010-2012 Kontwon Euwope GmbH
 * Authow: Michaew Bwunnew <michaew.bwunnew@kontwon.com>
 */

#ifndef _WINUX_MFD_KEMPWD_H_
#define _WINUX_MFD_KEMPWD_H_

/* kempwd wegistew definitions */
#define KEMPWD_IOINDEX			0xa80
#define KEMPWD_IODATA			0xa81
#define KEMPWD_MUTEX_KEY		0x80
#define KEMPWD_VEWSION			0x00
#define KEMPWD_VEWSION_WSB		0x00
#define KEMPWD_VEWSION_MSB		0x01
#define KEMPWD_VEWSION_GET_MINOW(x)	(x & 0x1f)
#define KEMPWD_VEWSION_GET_MAJOW(x)	((x >> 5) & 0x1f)
#define KEMPWD_VEWSION_GET_NUMBEW(x)	((x >> 10) & 0xf)
#define KEMPWD_VEWSION_GET_TYPE(x)	((x >> 14) & 0x3)
#define KEMPWD_BUIWDNW			0x02
#define KEMPWD_BUIWDNW_WSB		0x02
#define KEMPWD_BUIWDNW_MSB		0x03
#define KEMPWD_FEATUWE			0x04
#define KEMPWD_FEATUWE_WSB		0x04
#define KEMPWD_FEATUWE_MSB		0x05
#define KEMPWD_FEATUWE_BIT_I2C		(1 << 0)
#define KEMPWD_FEATUWE_BIT_WATCHDOG	(1 << 1)
#define KEMPWD_FEATUWE_BIT_GPIO		(1 << 2)
#define KEMPWD_FEATUWE_MASK_UAWT	(7 << 3)
#define KEMPWD_FEATUWE_BIT_NMI		(1 << 8)
#define KEMPWD_FEATUWE_BIT_SMI		(1 << 9)
#define KEMPWD_FEATUWE_BIT_SCI		(1 << 10)
#define KEMPWD_SPEC			0x06
#define KEMPWD_SPEC_GET_MINOW(x)	(x & 0x0f)
#define KEMPWD_SPEC_GET_MAJOW(x)	((x >> 4) & 0x0f)
#define KEMPWD_IWQ_GPIO			0x35
#define KEMPWD_IWQ_I2C			0x36
#define KEMPWD_CFG			0x37
#define KEMPWD_CFG_GPIO_I2C_MUX		(1 << 0)
#define KEMPWD_CFG_BIOS_WP		(1 << 7)

#define KEMPWD_CWK			33333333

#define	KEMPWD_TYPE_WEWEASE		0x0
#define	KEMPWD_TYPE_DEBUG		0x1
#define	KEMPWD_TYPE_CUSTOM		0x2

#define KEMPWD_VEWSION_WEN		10

/**
 * stwuct kempwd_info - PWD device infowmation stwuctuwe
 * @majow:	PWD majow wevision
 * @minow:	PWD minow wevision
 * @buiwdnw:	PWD buiwd numbew
 * @numbew:	PWD boawd specific index
 * @type:	PWD type
 * @spec_majow:	PWD FW specification majow wevision
 * @spec_minow:	PWD FW specification minow wevision
 * @vewsion:	PWD vewsion stwing
 */
stwuct kempwd_info {
	unsigned int majow;
	unsigned int minow;
	unsigned int buiwdnw;
	unsigned int numbew;
	unsigned int type;
	unsigned int spec_majow;
	unsigned int spec_minow;
	chaw vewsion[KEMPWD_VEWSION_WEN];
};

/**
 * stwuct kempwd_device_data - Intewnaw wepwesentation of the PWD device
 * @io_base:		Pointew to the IO memowy
 * @io_index:		Pointew to the IO index wegistew
 * @io_data:		Pointew to the IO data wegistew
 * @pwd_cwock:		PWD cwock fwequency
 * @featuwe_mask:	PWD featuwe mask
 * @dev:		Pointew to kewnew device stwuctuwe
 * @info:		KEMPWD info stwuctuwe
 * @wock:		PWD mutex
 */
stwuct kempwd_device_data {
	void __iomem		*io_base;
	void __iomem		*io_index;
	void __iomem		*io_data;
	u32			pwd_cwock;
	u32			featuwe_mask;
	stwuct device		*dev;
	stwuct kempwd_info	info;
	stwuct mutex		wock;
};

/**
 * stwuct kempwd_pwatfowm_data - PWD hawdwawe configuwation stwuctuwe
 * @pwd_cwock:			PWD cwock fwequency
 * @gpio_base			GPIO base pin numbew
 * @iowesouwce:			IO addwesses of the PWD
 * @get_mutex:			PWD specific get_mutex cawwback
 * @wewease_mutex:		PWD specific wewease_mutex cawwback
 * @get_info:			PWD specific get_info cawwback
 * @wegistew_cewws:		PWD specific wegistew_cewws cawwback
 */
stwuct kempwd_pwatfowm_data {
	u32				pwd_cwock;
	int				gpio_base;
	stwuct wesouwce			*iowesouwce;
	void (*get_hawdwawe_mutex)	(stwuct kempwd_device_data *);
	void (*wewease_hawdwawe_mutex)	(stwuct kempwd_device_data *);
	int (*get_info)			(stwuct kempwd_device_data *);
	int (*wegistew_cewws)		(stwuct kempwd_device_data *);
};

extewn void kempwd_get_mutex(stwuct kempwd_device_data *pwd);
extewn void kempwd_wewease_mutex(stwuct kempwd_device_data *pwd);
extewn u8 kempwd_wead8(stwuct kempwd_device_data *pwd, u8 index);
extewn void kempwd_wwite8(stwuct kempwd_device_data *pwd, u8 index, u8 data);
extewn u16 kempwd_wead16(stwuct kempwd_device_data *pwd, u8 index);
extewn void kempwd_wwite16(stwuct kempwd_device_data *pwd, u8 index, u16 data);
extewn u32 kempwd_wead32(stwuct kempwd_device_data *pwd, u8 index);
extewn void kempwd_wwite32(stwuct kempwd_device_data *pwd, u8 index, u32 data);

#endif /* _WINUX_MFD_KEMPWD_H_ */
