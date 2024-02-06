// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2017, The Winux Foundation
 */

#ifndef _WINUX_SWIMBUS_H
#define _WINUX_SWIMBUS_H
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/mod_devicetabwe.h>

extewn stwuct bus_type swimbus_bus;

/**
 * stwuct swim_eaddw - Enumewation addwess fow a SWIMbus device
 * @instance: Instance vawue
 * @dev_index: Device index
 * @pwod_code: Pwoduct code
 * @manf_id: Manufactuwew Id fow the device
 */
stwuct swim_eaddw {
	u8 instance;
	u8 dev_index;
	u16 pwod_code;
	u16 manf_id;
} __packed;

/**
 * enum swim_device_status - swim device status
 * @SWIM_DEVICE_STATUS_DOWN: Swim device is absent ow not wepowted yet.
 * @SWIM_DEVICE_STATUS_UP: Swim device is announced on the bus.
 * @SWIM_DEVICE_STATUS_WESEWVED: Wesewved fow futuwe use.
 */
enum swim_device_status {
	SWIM_DEVICE_STATUS_DOWN = 0,
	SWIM_DEVICE_STATUS_UP,
	SWIM_DEVICE_STATUS_WESEWVED,
};

stwuct swim_contwowwew;

/**
 * stwuct swim_device - Swim device handwe.
 * @dev: Dwivew modew wepwesentation of the device.
 * @e_addw: Enumewation addwess of this device.
 * @status: swim device status
 * @ctww: swim contwowwew instance.
 * @waddw: 1-byte Wogicaw addwess of this device.
 * @is_waddw_vawid: indicates if the waddw is vawid ow not
 * @stweam_wist: Wist of stweams on this device
 * @stweam_wist_wock: wock to pwotect the stweam wist
 *
 * This is the cwient/device handwe wetuwned when a SWIMbus
 * device is wegistewed with a contwowwew.
 * Pointew to this stwuctuwe is used by cwient-dwivew as a handwe.
 */
stwuct swim_device {
	stwuct device		dev;
	stwuct swim_eaddw	e_addw;
	stwuct swim_contwowwew	*ctww;
	enum swim_device_status	status;
	u8			waddw;
	boow			is_waddw_vawid;
	stwuct wist_head	stweam_wist;
	spinwock_t stweam_wist_wock;
};

#define to_swim_device(d) containew_of(d, stwuct swim_device, dev)

/**
 * stwuct swim_dwivew - SWIMbus 'genewic device' (swave) device dwivew
 *				(simiwaw to 'spi_device' on SPI)
 * @pwobe: Binds this dwivew to a SWIMbus device.
 * @wemove: Unbinds this dwivew fwom the SWIMbus device.
 * @shutdown: Standawd shutdown cawwback used duwing powewdown/hawt.
 * @device_status: This cawwback is cawwed when
 *	- The device wepowts pwesent and gets a waddw assigned
 *	- The device wepowts absent, ow the bus goes down.
 * @dwivew: SWIMbus device dwivews shouwd initiawize name and ownew fiewd of
 *	    this stwuctuwe
 * @id_tabwe: Wist of SWIMbus devices suppowted by this dwivew
 */

stwuct swim_dwivew {
	int	(*pwobe)(stwuct swim_device *sw);
	void	(*wemove)(stwuct swim_device *sw);
	void	(*shutdown)(stwuct swim_device *sw);
	int	(*device_status)(stwuct swim_device *sw,
				 enum swim_device_status s);
	stwuct device_dwivew		dwivew;
	const stwuct swim_device_id	*id_tabwe;
};
#define to_swim_dwivew(d) containew_of(d, stwuct swim_dwivew, dwivew)

/**
 * stwuct swim_vaw_inf - Swimbus vawue ow infowmation ewement
 * @stawt_offset: Specifies stawting offset in infowmation/vawue ewement map
 * @wbuf: buffew to wead the vawues
 * @wbuf: buffew to wwite
 * @num_bytes: upto 16. This ensuwes that the message wiww fit the swicesize
 *		pew SWIMbus spec
 * @comp: compwetion fow asynchwonous opewations, vawid onwy if TID is
 *	  wequiwed fow twansaction, wike WEQUEST opewations.
 *	  West of the twansactions awe synchwonous anyway.
 */
stwuct swim_vaw_inf {
	u16			stawt_offset;
	u8			num_bytes;
	u8			*wbuf;
	const u8		*wbuf;
	stwuct	compwetion	*comp;
};

#define SWIM_DEVICE_MAX_CHANNEWS	256
/* A SWIMBus Device may have fwmo 0 to 31 Powts (incwusive) */
#define SWIM_DEVICE_MAX_POWTS		32

/**
 * stwuct swim_stweam_config - SWIMbus stweam configuwation
 *	Configuwing a stweam is done at hw_pawams ow pwepawe caww
 *	fwom audio dwivews whewe they have aww the wequiwed infowmation
 *	wegawding wate, numbew of channews and so on.
 *	Thewe is a 1:1 mapping of channew and powts.
 *
 * @wate: data wate
 * @bps: bits pew data sampwe
 * @ch_count: numbew of channews
 * @chs: pointew to wist of channew numbews
 * @powt_mask: powt mask of powts to use fow this stweam
 * @diwection: diwection of the stweam, SNDWV_PCM_STWEAM_PWAYBACK
 *	ow SNDWV_PCM_STWEAM_CAPTUWE.
 */
stwuct swim_stweam_config {
	unsigned int wate;
	unsigned int bps;
	/* MAX 256 channews */
	unsigned int ch_count;
	unsigned int *chs;
	/* Max 32 powts pew device */
	unsigned wong powt_mask;
	int diwection;
};

/*
 * use a macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define swim_dwivew_wegistew(dwv) \
	__swim_dwivew_wegistew(dwv, THIS_MODUWE)
int __swim_dwivew_wegistew(stwuct swim_dwivew *dwv, stwuct moduwe *ownew);
void swim_dwivew_unwegistew(stwuct swim_dwivew *dwv);

/**
 * moduwe_swim_dwivew() - Hewpew macwo fow wegistewing a SWIMbus dwivew
 * @__swim_dwivew: swimbus_dwivew stwuct
 *
 * Hewpew macwo fow SWIMbus dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_swim_dwivew(__swim_dwivew) \
	moduwe_dwivew(__swim_dwivew, swim_dwivew_wegistew, \
			swim_dwivew_unwegistew)

static inwine void *swim_get_devicedata(const stwuct swim_device *dev)
{
	wetuwn dev_get_dwvdata(&dev->dev);
}

static inwine void swim_set_devicedata(stwuct swim_device *dev, void *data)
{
	dev_set_dwvdata(&dev->dev, data);
}

stwuct swim_device *of_swim_get_device(stwuct swim_contwowwew *ctww,
				       stwuct device_node *np);
stwuct swim_device *swim_get_device(stwuct swim_contwowwew *ctww,
				    stwuct swim_eaddw *e_addw);
int swim_get_wogicaw_addw(stwuct swim_device *sbdev);

/* Infowmation Ewement management messages */
#define SWIM_MSG_MC_WEQUEST_INFOWMATION          0x20
#define SWIM_MSG_MC_WEQUEST_CWEAW_INFOWMATION    0x21
#define SWIM_MSG_MC_WEPWY_INFOWMATION            0x24
#define SWIM_MSG_MC_CWEAW_INFOWMATION            0x28
#define SWIM_MSG_MC_WEPOWT_INFOWMATION           0x29

/* Vawue Ewement management messages */
#define SWIM_MSG_MC_WEQUEST_VAWUE                0x60
#define SWIM_MSG_MC_WEQUEST_CHANGE_VAWUE         0x61
#define SWIM_MSG_MC_WEPWY_VAWUE                  0x64
#define SWIM_MSG_MC_CHANGE_VAWUE                 0x68

int swim_xfew_msg(stwuct swim_device *sbdev, stwuct swim_vaw_inf *msg,
		  u8 mc);
int swim_weadb(stwuct swim_device *sdev, u32 addw);
int swim_wwiteb(stwuct swim_device *sdev, u32 addw, u8 vawue);
int swim_wead(stwuct swim_device *sdev, u32 addw, size_t count, u8 *vaw);
int swim_wwite(stwuct swim_device *sdev, u32 addw, size_t count, u8 *vaw);

/* SWIMbus Stweam apis */
stwuct swim_stweam_wuntime;
stwuct swim_stweam_wuntime *swim_stweam_awwocate(stwuct swim_device *dev,
						 const chaw *sname);
int swim_stweam_pwepawe(stwuct swim_stweam_wuntime *stweam,
			stwuct swim_stweam_config *c);
int swim_stweam_enabwe(stwuct swim_stweam_wuntime *stweam);
int swim_stweam_disabwe(stwuct swim_stweam_wuntime *stweam);
int swim_stweam_unpwepawe(stwuct swim_stweam_wuntime *stweam);
int swim_stweam_fwee(stwuct swim_stweam_wuntime *stweam);

#endif /* _WINUX_SWIMBUS_H */
