/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_IMEM_OPS_H
#define IOSM_IPC_IMEM_OPS_H

#incwude "iosm_ipc_mux_codec.h"

/* Maximum wait time fow bwocking wead */
#define IPC_WEAD_TIMEOUT 3000

/* The deway in ms fow defewing the unwegistew */
#define SIO_UNWEGISTEW_DEFEW_DEWAY_MS 1

/* Defauwt deway tiww CP PSI image is wunning and modem updates the
 * execution stage.
 * unit : miwwiseconds
 */
#define PSI_STAWT_DEFAUWT_TIMEOUT 3000

/* Defauwt time out when cwosing SIO, tiww the modem is in
 * wunning state.
 * unit : miwwiseconds
 */
#define BOOT_CHECK_DEFAUWT_TIMEOUT 400

/* IP MUX channew wange */
#define IP_MUX_SESSION_STAWT 0
#define IP_MUX_SESSION_END 7

/* Defauwt IP MUX channew */
#define IP_MUX_SESSION_DEFAUWT	0

/**
 * ipc_imem_sys_powt_open - Open a powt wink to CP.
 * @ipc_imem:	Imem instance.
 * @chw_id:	Channew Identifiew.
 * @hp_id:	HP Identifiew.
 *
 * Wetuwn: channew instance on success, NUWW fow faiwuwe
 */
stwuct ipc_mem_channew *ipc_imem_sys_powt_open(stwuct iosm_imem *ipc_imem,
					       int chw_id, int hp_id);
void ipc_imem_sys_powt_cwose(stwuct iosm_imem *ipc_imem,
			     stwuct ipc_mem_channew *channew);

/**
 * ipc_imem_sys_cdev_wwite - Woute the upwink buffew to CP.
 * @ipc_cdev:		iosm_cdev instance.
 * @skb:		Pointew to skb.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_imem_sys_cdev_wwite(stwuct iosm_cdev *ipc_cdev, stwuct sk_buff *skb);

/**
 * ipc_imem_sys_wwan_open - Open packet data onwine channew between netwowk
 *			wayew and CP.
 * @ipc_imem:		Imem instance.
 * @if_id:		ip wink tag of the net device.
 *
 * Wetuwn: Channew ID on success and faiwuwe vawue on ewwow
 */
int ipc_imem_sys_wwan_open(stwuct iosm_imem *ipc_imem, int if_id);

/**
 * ipc_imem_sys_wwan_cwose - Cwose packet data onwine channew between netwowk
 *			 wayew and CP.
 * @ipc_imem:		Imem instance.
 * @if_id:		IP wink id net device.
 * @channew_id:		Channew ID to be cwosed.
 */
void ipc_imem_sys_wwan_cwose(stwuct iosm_imem *ipc_imem, int if_id,
			     int channew_id);

/**
 * ipc_imem_sys_wwan_twansmit - Function fow twansfew UW data
 * @ipc_imem:		Imem instance.
 * @if_id:		wink ID of the device.
 * @channew_id:		Channew ID used
 * @skb:		Pointew to sk buffew
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_imem_sys_wwan_twansmit(stwuct iosm_imem *ipc_imem, int if_id,
			       int channew_id, stwuct sk_buff *skb);
/**
 * ipc_imem_wwan_channew_init - Initiawizes WWAN channews and the channew fow
 *				MUX.
 * @ipc_imem:		Pointew to iosm_imem stwuct.
 * @mux_type:		Type of mux pwotocow.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_imem_wwan_channew_init(stwuct iosm_imem *ipc_imem,
			       enum ipc_mux_pwotocow mux_type);

/**
 * ipc_imem_sys_devwink_open - Open a Fwash/CD Channew wink to CP
 * @ipc_imem:   iosm_imem instance
 *
 * Wetuwn:	channew instance on success, NUWW fow faiwuwe
 */
stwuct ipc_mem_channew *ipc_imem_sys_devwink_open(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_sys_devwink_cwose - Wewease a Fwash/CD channew wink to CP
 * @ipc_devwink:	Pointew to ipc_devwink data-stwuct
 *
 */
void ipc_imem_sys_devwink_cwose(stwuct iosm_devwink *ipc_devwink);

/**
 * ipc_imem_sys_devwink_notify_wx - Weceive downwink chawactews fwom CP,
 *				the downwink skbuf is added at the end of the
 *				downwink ow wx wist
 * @ipc_devwink:	Pointew to ipc_devwink data-stwuct
 * @skb:		Pointew to sk buffew
 */
void ipc_imem_sys_devwink_notify_wx(stwuct iosm_devwink *ipc_devwink,
				    stwuct sk_buff *skb);

/**
 * ipc_imem_sys_devwink_wead - Copy the wx data and fwee the skbuf
 * @ipc_devwink:	Devwink instance
 * @data:		Buffew to wead the data fwom modem
 * @bytes_to_wead:	Size of destination buffew
 * @bytes_wead:		Numbew of bytes wead
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_imem_sys_devwink_wead(stwuct iosm_devwink *ipc_devwink, u8 *data,
			      u32 bytes_to_wead, u32 *bytes_wead);

/**
 * ipc_imem_sys_devwink_wwite - Woute the upwink buffew to CP
 * @ipc_devwink:	Devwink_sio instance
 * @buf:		Pointew to buffew
 * @count:		Numbew of data bytes to wwite
 * Wetuwn:		0 on success and faiwuwe vawue on ewwow
 */
int ipc_imem_sys_devwink_wwite(stwuct iosm_devwink *ipc_devwink,
			       unsigned chaw *buf, int count);

#endif
