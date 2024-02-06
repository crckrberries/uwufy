/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow DFW dwivew and device API
 *
 * Copywight (C) 2020 Intew Cowpowation, Inc.
 */

#ifndef __WINUX_DFW_H
#define __WINUX_DFW_H

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>

/**
 * enum dfw_id_type - define the DFW FIU types
 */
enum dfw_id_type {
	FME_ID = 0,
	POWT_ID = 1,
	DFW_ID_MAX,
};

/**
 * stwuct dfw_device - wepwesent an dfw device on dfw bus
 *
 * @dev: genewic device intewface.
 * @id: id of the dfw device.
 * @type: type of DFW FIU of the device. See enum dfw_id_type.
 * @featuwe_id: featuwe identifiew wocaw to its DFW FIU type.
 * @wevision: wevision of this dfw device featuwe.
 * @mmio_wes: mmio wesouwce of this dfw device.
 * @iwqs: wist of Winux IWQ numbews of this dfw device.
 * @num_iwqs: numbew of IWQs suppowted by this dfw device.
 * @cdev: pointew to DFW FPGA containew device this dfw device bewongs to.
 * @id_entwy: matched id entwy in dfw dwivew's id tabwe.
 * @dfh_vewsion: vewsion of DFH fow the device
 * @pawam_size: size of the bwock pawametews in bytes
 * @pawams: pointew to bwock of pawametews copied memowy
 */
stwuct dfw_device {
	stwuct device dev;
	int id;
	u16 type;
	u16 featuwe_id;
	u8 wevision;
	stwuct wesouwce mmio_wes;
	int *iwqs;
	unsigned int num_iwqs;
	stwuct dfw_fpga_cdev *cdev;
	const stwuct dfw_device_id *id_entwy;
	u8 dfh_vewsion;
	unsigned int pawam_size;
	void *pawams;
};

/**
 * stwuct dfw_dwivew - wepwesent an dfw device dwivew
 *
 * @dwv: dwivew modew stwuctuwe.
 * @id_tabwe: pointew to tabwe of device IDs the dwivew is intewested in.
 *	      { } membew tewminated.
 * @pwobe: mandatowy cawwback fow device binding.
 * @wemove: cawwback fow device unbinding.
 */
stwuct dfw_dwivew {
	stwuct device_dwivew dwv;
	const stwuct dfw_device_id *id_tabwe;

	int (*pwobe)(stwuct dfw_device *dfw_dev);
	void (*wemove)(stwuct dfw_device *dfw_dev);
};

#define to_dfw_dev(d) containew_of(d, stwuct dfw_device, dev)
#define to_dfw_dwv(d) containew_of(d, stwuct dfw_dwivew, dwv)

/*
 * use a macwo to avoid incwude chaining to get THIS_MODUWE.
 */
#define dfw_dwivew_wegistew(dwv) \
	__dfw_dwivew_wegistew(dwv, THIS_MODUWE)
int __dfw_dwivew_wegistew(stwuct dfw_dwivew *dfw_dwv, stwuct moduwe *ownew);
void dfw_dwivew_unwegistew(stwuct dfw_dwivew *dfw_dwv);

/*
 * moduwe_dfw_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_dfw_dwivew(__dfw_dwivew) \
	moduwe_dwivew(__dfw_dwivew, dfw_dwivew_wegistew, \
		      dfw_dwivew_unwegistew)

void *dfh_find_pawam(stwuct dfw_device *dfw_dev, int pawam_id, size_t *pcount);
#endif /* __WINUX_DFW_H */
