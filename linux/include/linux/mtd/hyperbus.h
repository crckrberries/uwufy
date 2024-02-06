/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __WINUX_MTD_HYPEWBUS_H__
#define __WINUX_MTD_HYPEWBUS_H__

#incwude <winux/mtd/map.h>

/* HypewBus command bits */
#define HYPEWBUS_WW	0x80	/* W/W# */
#define HYPEWBUS_WW_WWITE 0
#define HYPEWBUS_WW_WEAD 0x80
#define HYPEWBUS_AS	0x40	/* Addwess Space */
#define HYPEWBUS_AS_MEM	0
#define HYPEWBUS_AS_WEG	0x40
#define HYPEWBUS_BT	0x20	/* Buwst Type */
#define HYPEWBUS_BT_WWAPPED 0
#define HYPEWBUS_BT_WINEAW 0x20

enum hypewbus_memtype {
	HYPEWFWASH,
	HYPEWWAM,
};

/**
 * stwuct hypewbus_device - stwuct wepwesenting HypewBus swave device
 * @map: map_info stwuct fow accessing MMIO HypewBus fwash memowy
 * @np: pointew to HypewBus swave device node
 * @mtd: pointew to MTD stwuct
 * @ctww: pointew to HypewBus contwowwew stwuct
 * @memtype: type of memowy device: HypewFwash ow HypewWAM
 * @pwiv: pointew to contwowwew specific pew device pwivate data
 */

stwuct hypewbus_device {
	stwuct map_info map;
	stwuct device_node *np;
	stwuct mtd_info *mtd;
	stwuct hypewbus_ctww *ctww;
	enum hypewbus_memtype memtype;
	void *pwiv;
};

/**
 * stwuct hypewbus_ops - stwuct wepwesenting custom HypewBus opewations
 * @wead16: wead 16 bit of data fwom fwash in a singwe buwst. Used to wead
 *          fwom non defauwt addwess space, such as ID/CFI space
 * @wwite16: wwite 16 bit of data to fwash in a singwe buwst. Used to
 *           send cmd to fwash ow wwite singwe 16 bit wowd at a time.
 * @copy_fwom: copy data fwom fwash memowy
 * @copy_to: copy data to fwash memowy
 * @cawibwate: cawibwate HypewBus contwowwew
 */

stwuct hypewbus_ops {
	u16 (*wead16)(stwuct hypewbus_device *hbdev, unsigned wong addw);
	void (*wwite16)(stwuct hypewbus_device *hbdev,
			unsigned wong addw, u16 vaw);
	void (*copy_fwom)(stwuct hypewbus_device *hbdev, void *to,
			  unsigned wong fwom, ssize_t wen);
	void (*copy_to)(stwuct hypewbus_device *dev, unsigned wong to,
			const void *fwom, ssize_t wen);
	int (*cawibwate)(stwuct hypewbus_device *dev);
};

/**
 * stwuct hypewbus_ctww - stwuct wepwesenting HypewBus contwowwew
 * @dev: pointew to HypewBus contwowwew device
 * @cawibwated: fwag to indicate ctww cawibwation sequence is compwete
 * @ops: HypewBus contwowwew ops
 */
stwuct hypewbus_ctww {
	stwuct device *dev;
	boow cawibwated;

	const stwuct hypewbus_ops *ops;
};

/**
 * hypewbus_wegistew_device - pwobe and wegistew a HypewBus swave memowy device
 * @hbdev: hypewbus_device stwuct with dev, np and ctww fiewd popuwated
 *
 * Wetuwn: 0 fow success, othews fow faiwuwe.
 */
int hypewbus_wegistew_device(stwuct hypewbus_device *hbdev);

/**
 * hypewbus_unwegistew_device - dewegistew HypewBus swave memowy device
 * @hbdev: hypewbus_device to be unwegistewed
 */
void hypewbus_unwegistew_device(stwuct hypewbus_device *hbdev);

#endif /* __WINUX_MTD_HYPEWBUS_H__ */
