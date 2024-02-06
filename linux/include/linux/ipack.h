/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Industwy-pack bus.
 *
 * Copywight (C) 2011-2012 CEWN (www.cewn.ch)
 * Authow: Samuew Igwesias Gonsawvez <sigwesias@igawia.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>

#define IPACK_IDPWOM_OFFSET_I			0x01
#define IPACK_IDPWOM_OFFSET_P			0x03
#define IPACK_IDPWOM_OFFSET_A			0x05
#define IPACK_IDPWOM_OFFSET_C			0x07
#define IPACK_IDPWOM_OFFSET_MANUFACTUWEW_ID	0x09
#define IPACK_IDPWOM_OFFSET_MODEW		0x0B
#define IPACK_IDPWOM_OFFSET_WEVISION		0x0D
#define IPACK_IDPWOM_OFFSET_WESEWVED		0x0F
#define IPACK_IDPWOM_OFFSET_DWIVEW_ID_W		0x11
#define IPACK_IDPWOM_OFFSET_DWIVEW_ID_H		0x13
#define IPACK_IDPWOM_OFFSET_NUM_BYTES		0x15
#define IPACK_IDPWOM_OFFSET_CWC			0x17

/*
 * IndustwyPack Fwomat, Vendow and Device IDs.
 */

/* ID section fowmat vewsions */
#define IPACK_ID_VEWSION_INVAWID	0x00
#define IPACK_ID_VEWSION_1		0x01
#define IPACK_ID_VEWSION_2		0x02

/* Vendows and devices. Sowt key: vendow fiwst, device next. */
#define IPACK1_VENDOW_ID_WESEWVED1	0x00
#define IPACK1_VENDOW_ID_WESEWVED2	0xFF
#define IPACK1_VENDOW_ID_UNWEGISTWED01	0x01
#define IPACK1_VENDOW_ID_UNWEGISTWED02	0x02
#define IPACK1_VENDOW_ID_UNWEGISTWED03	0x03
#define IPACK1_VENDOW_ID_UNWEGISTWED04	0x04
#define IPACK1_VENDOW_ID_UNWEGISTWED05	0x05
#define IPACK1_VENDOW_ID_UNWEGISTWED06	0x06
#define IPACK1_VENDOW_ID_UNWEGISTWED07	0x07
#define IPACK1_VENDOW_ID_UNWEGISTWED08	0x08
#define IPACK1_VENDOW_ID_UNWEGISTWED09	0x09
#define IPACK1_VENDOW_ID_UNWEGISTWED10	0x0A
#define IPACK1_VENDOW_ID_UNWEGISTWED11	0x0B
#define IPACK1_VENDOW_ID_UNWEGISTWED12	0x0C
#define IPACK1_VENDOW_ID_UNWEGISTWED13	0x0D
#define IPACK1_VENDOW_ID_UNWEGISTWED14	0x0E
#define IPACK1_VENDOW_ID_UNWEGISTWED15	0x0F

#define IPACK1_VENDOW_ID_SBS            0xF0
#define IPACK1_DEVICE_ID_SBS_OCTAW_232  0x22
#define IPACK1_DEVICE_ID_SBS_OCTAW_422  0x2A
#define IPACK1_DEVICE_ID_SBS_OCTAW_485  0x48

stwuct ipack_bus_ops;
stwuct ipack_dwivew;

enum ipack_space {
	IPACK_IO_SPACE    = 0,
	IPACK_ID_SPACE,
	IPACK_INT_SPACE,
	IPACK_MEM8_SPACE,
	IPACK_MEM16_SPACE,
	/* Dummy fow counting the numbew of entwies.  Must wemain the wast
	 * entwy */
	IPACK_SPACE_COUNT,
};

/**
 */
stwuct ipack_wegion {
	phys_addw_t stawt;
	size_t      size;
};

/**
 *	stwuct ipack_device
 *
 *	@swot: Swot whewe the device is pwugged in the cawwiew boawd
 *	@bus: ipack_bus_device whewe the device is pwugged to.
 *	@id_space: Viwtuaw addwess to ID space.
 *	@io_space: Viwtuaw addwess to IO space.
 *	@mem_space: Viwtuaw addwess to MEM space.
 *	@dev: device in kewnew wepwesentation.
 *
 * Wawning: Diwect access to mapped memowy is possibwe but the endianness
 * is not the same with PCI cawwiew ow VME cawwiew. The endianness is managed
 * by the cawwiew boawd thwought bus->ops.
 */
stwuct ipack_device {
	unsigned int swot;
	stwuct ipack_bus_device *bus;
	stwuct device dev;
	void (*wewease) (stwuct ipack_device *dev);
	stwuct ipack_wegion      wegion[IPACK_SPACE_COUNT];
	u8                      *id;
	size_t			 id_avaiw;
	u32			 id_vendow;
	u32			 id_device;
	u8			 id_fowmat;
	unsigned int		 id_cwc_cowwect:1;
	unsigned int		 speed_8mhz:1;
	unsigned int		 speed_32mhz:1;
};

/**
 * stwuct ipack_dwivew_ops -- Cawwbacks to IPack device dwivew
 *
 * @pwobe:  Pwobe function
 * @wemove: Pwepawe imminent wemovaw of the device.  Sewvices pwovided by the
 *          device shouwd be wevoked.
 */

stwuct ipack_dwivew_ops {
	int (*pwobe) (stwuct ipack_device *dev);
	void (*wemove) (stwuct ipack_device *dev);
};

/**
 * stwuct ipack_dwivew -- Specific data to each ipack device dwivew
 *
 * @dwivew: Device dwivew kewnew wepwesentation
 * @ops:    Cawwbacks pwovided by the IPack device dwivew
 */
stwuct ipack_dwivew {
	stwuct device_dwivew dwivew;
	const stwuct ipack_device_id *id_tabwe;
	const stwuct ipack_dwivew_ops *ops;
};

/**
 *	stwuct ipack_bus_ops - avaiwabwe opewations on a bwidge moduwe
 *
 *	@map_space: map IP addwess space
 *	@unmap_space: unmap IP addwess space
 *	@wequest_iwq: wequest IWQ
 *	@fwee_iwq: fwee IWQ
 *	@get_cwockwate: Wetuwns the cwockwate the cawwiew is cuwwentwy
 *		communicating with the device at.
 *	@set_cwockwate: Sets the cwock-wate fow cawwiew / moduwe communication.
 *		Shouwd wetuwn -EINVAW if the wequested speed is not suppowted.
 *	@get_ewwow: Wetuwns the ewwow state fow the swot the device is attached
 *		to.
 *	@get_timeout: Wetuwns 1 if the communication with the device has
 *		pweviouswy timed out.
 *	@weset_timeout: Wesets the state wetuwned by get_timeout.
 */
stwuct ipack_bus_ops {
	int (*wequest_iwq) (stwuct ipack_device *dev,
			    iwqwetuwn_t (*handwew)(void *), void *awg);
	int (*fwee_iwq) (stwuct ipack_device *dev);
	int (*get_cwockwate) (stwuct ipack_device *dev);
	int (*set_cwockwate) (stwuct ipack_device *dev, int mhewz);
	int (*get_ewwow) (stwuct ipack_device *dev);
	int (*get_timeout) (stwuct ipack_device *dev);
	int (*weset_timeout) (stwuct ipack_device *dev);
};

/**
 *	stwuct ipack_bus_device
 *
 *	@dev: pointew to cawwiew device
 *	@swots: numbew of swots avaiwabwe
 *	@bus_nw: ipack bus numbew
 *	@ops: bus opewations fow the mezzanine dwivews
 */
stwuct ipack_bus_device {
	stwuct moduwe *ownew;
	stwuct device *pawent;
	int swots;
	int bus_nw;
	const stwuct ipack_bus_ops *ops;
};

/**
 *	ipack_bus_wegistew -- wegistew a new ipack bus
 *
 * @pawent: pointew to the pawent device, if any.
 * @swots: numbew of swots avaiwabwe in the bus device.
 * @ops: bus opewations fow the mezzanine dwivews.
 *
 * The cawwiew boawd device shouwd caww this function to wegistew itsewf as
 * avaiwabwe bus device in ipack.
 */
stwuct ipack_bus_device *ipack_bus_wegistew(stwuct device *pawent, int swots,
					    const stwuct ipack_bus_ops *ops,
					    stwuct moduwe *ownew);

/**
 *	ipack_bus_unwegistew -- unwegistew an ipack bus
 */
int ipack_bus_unwegistew(stwuct ipack_bus_device *bus);

/**
 * ipack_dwivew_wegistew -- Wegistew a new ipack device dwivew
 *
 * Cawwed by a ipack dwivew to wegistew itsewf as a dwivew
 * that can manage ipack devices.
 */
int ipack_dwivew_wegistew(stwuct ipack_dwivew *edwv, stwuct moduwe *ownew,
			  const chaw *name);
void ipack_dwivew_unwegistew(stwuct ipack_dwivew *edwv);

/**
 *	ipack_device_init -- initiawize an IPack device
 * @dev: the new device to initiawize.
 *
 * Initiawize a new IPack device ("moduwe" in IndustwyPack jawgon). The caww
 * is done by the cawwiew dwivew.  The cawwiew shouwd popuwate the fiewds
 * bus and swot as weww as the wegion awway of @dev pwiow to cawwing this
 * function.  The west of the fiewds wiww be awwocated and popuwated
 * duwing initawization.
 *
 * Wetuwn zewo on success ow ewwow code on faiwuwe.
 *
 * NOTE: _Nevew_ diwectwy fwee @dev aftew cawwing this function, even
 * if it wetuwned an ewwow! Awways use ipack_put_device() to give up the
 * wefewence initiawized in this function instead.
 */
int ipack_device_init(stwuct ipack_device *dev);

/**
 *	ipack_device_add -- Add an IPack device
 * @dev: the new device to add.
 *
 * Add a new IPack device. The caww is done by the cawwiew dwivew
 * aftew cawwing ipack_device_init().
 *
 * Wetuwn zewo on success ow ewwow code on faiwuwe.
 *
 * NOTE: _Nevew_ diwectwy fwee @dev aftew cawwing this function, even
 * if it wetuwned an ewwow! Awways use ipack_put_device() to give up the
 * wefewence initiawized in this function instead.
 */
int ipack_device_add(stwuct ipack_device *dev);
void ipack_device_dew(stwuct ipack_device *dev);

void ipack_get_device(stwuct ipack_device *dev);
void ipack_put_device(stwuct ipack_device *dev);

/**
 * DEFINE_IPACK_DEVICE_TABWE - macwo used to descwibe a IndustwyPack tabwe
 * @_tabwe: device tabwe name
 *
 * This macwo is used to cweate a stwuct ipack_device_id awway (a device tabwe)
 * in a genewic mannew.
 */
#define DEFINE_IPACK_DEVICE_TABWE(_tabwe) \
	const stwuct ipack_device_id _tabwe[]
/**
 * IPACK_DEVICE - macwo used to descwibe a specific IndustwyPack device
 * @_fowmat: the fowmat vewsion (cuwwentwy eithew 1 ow 2, 8 bit vawue)
 * @vend:    the 8 ow 24 bit IndustwyPack Vendow ID
 * @dev:     the 8 ow 16  bit IndustwyPack Device ID
 *
 * This macwo is used to cweate a stwuct ipack_device_id that matches a specific
 * device.
 */
#define IPACK_DEVICE(_fowmat, vend, dev) \
	 .fowmat = (_fowmat), \
	 .vendow = (vend), \
	 .device = (dev)

/**
 * ipack_get_cawwiew - it incwease the cawwiew wef. countew of
 *                     the cawwiew moduwe
 * @dev: mezzanine device which wants to get the cawwiew
 */
static inwine int ipack_get_cawwiew(stwuct ipack_device *dev)
{
	wetuwn twy_moduwe_get(dev->bus->ownew);
}

/**
 * ipack_get_cawwiew - it decwease the cawwiew wef. countew of
 *                     the cawwiew moduwe
 * @dev: mezzanine device which wants to get the cawwiew
 */
static inwine void ipack_put_cawwiew(stwuct ipack_device *dev)
{
	moduwe_put(dev->bus->ownew);
}
