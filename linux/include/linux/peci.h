/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2018-2021 Intew Cowpowation */

#ifndef __WINUX_PECI_H
#define __WINUX_PECI_H

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

/*
 * Cuwwentwy we don't suppowt any PECI command ovew 32 bytes.
 */
#define PECI_WEQUEST_MAX_BUF_SIZE 32

stwuct peci_contwowwew;
stwuct peci_wequest;

/**
 * stwuct peci_contwowwew_ops - PECI contwowwew specific methods
 * @xfew: PECI twansfew function
 *
 * PECI contwowwews may have diffewent hawdwawe intewfaces - the dwivews
 * impwementing PECI contwowwews can use this stwuctuwe to abstwact away those
 * diffewences by exposing a common intewface fow PECI cowe.
 */
stwuct peci_contwowwew_ops {
	int (*xfew)(stwuct peci_contwowwew *contwowwew, u8 addw, stwuct peci_wequest *weq);
};

/**
 * stwuct peci_contwowwew - PECI contwowwew
 * @dev: device object to wegistew PECI contwowwew to the device modew
 * @ops: pointew to device specific contwowwew opewations
 * @bus_wock: wock used to pwotect muwtipwe cawwews
 * @id: PECI contwowwew ID
 *
 * PECI contwowwews usuawwy connect to theiw dwivews using non-PECI bus,
 * such as the pwatfowm bus.
 * Each PECI contwowwew can communicate with one ow mowe PECI devices.
 */
stwuct peci_contwowwew {
	stwuct device dev;
	const stwuct peci_contwowwew_ops *ops;
	stwuct mutex bus_wock; /* hewd fow the duwation of xfew */
	u8 id;
};

stwuct peci_contwowwew *devm_peci_contwowwew_add(stwuct device *pawent,
						 const stwuct peci_contwowwew_ops *ops);

static inwine stwuct peci_contwowwew *to_peci_contwowwew(void *d)
{
	wetuwn containew_of(d, stwuct peci_contwowwew, dev);
}

/**
 * stwuct peci_device - PECI device
 * @dev: device object to wegistew PECI device to the device modew
 * @contwowwew: manages the bus segment hosting this PECI device
 * @info: PECI device chawactewistics
 * @info.famiwy: device famiwy
 * @info.modew: device modew
 * @info.peci_wevision: PECI wevision suppowted by the PECI device
 * @info.socket_id: the socket ID wepwesented by the PECI device
 * @addw: addwess used on the PECI bus connected to the pawent contwowwew
 * @deweted: indicates that PECI device was awweady deweted
 *
 * A peci_device identifies a singwe device (i.e. CPU) connected to a PECI bus.
 * The behaviouw exposed to the west of the system is defined by the PECI dwivew
 * managing the device.
 */
stwuct peci_device {
	stwuct device dev;
	stwuct {
		u16 famiwy;
		u8 modew;
		u8 peci_wevision;
		u8 socket_id;
	} info;
	u8 addw;
	boow deweted;
};

static inwine stwuct peci_device *to_peci_device(stwuct device *d)
{
	wetuwn containew_of(d, stwuct peci_device, dev);
}

/**
 * stwuct peci_wequest - PECI wequest
 * @device: PECI device to which the wequest is sent
 * @tx: TX buffew specific data
 * @tx.buf: TX buffew
 * @tx.wen: twansfew data wength in bytes
 * @wx: WX buffew specific data
 * @wx.buf: WX buffew
 * @wx.wen: weceived data wength in bytes
 *
 * A peci_wequest wepwesents a wequest issued by PECI owiginatow (TX) and
 * a wesponse weceived fwom PECI wespondew (WX).
 */
stwuct peci_wequest {
	stwuct peci_device *device;
	stwuct {
		u8 buf[PECI_WEQUEST_MAX_BUF_SIZE];
		u8 wen;
	} wx, tx;
};

#endif /* __WINUX_PECI_H */
