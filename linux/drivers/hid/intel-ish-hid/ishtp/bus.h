/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ISHTP bus definitions
 *
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */
#ifndef _WINUX_ISHTP_CW_BUS_H
#define _WINUX_ISHTP_CW_BUS_H

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intew-ish-cwient-if.h>

stwuct ishtp_cw;
stwuct ishtp_cw_device;
stwuct ishtp_device;
stwuct ishtp_msg_hdw;

/**
 * stwuct ishtp_cw_device - ISHTP device handwe
 * @dev:	device pointew
 * @ishtp_dev:	pointew to ishtp device stwuctuwe to pwimawiwy to access
 *		hw device opewation cawwbacks and pwopewties
 * @fw_cwient:	fw_cwient pointew to get fw infowmation wike pwotocow name
 *		max message wength etc.
 * @device_wink: Wink to next cwient in the wist on a bus
 * @event_wowk:	Used to scheduwe wx event fow cwient
 * @dwivew_data: Stowage dwivew pwivate data
 * @wefewence_count:	Used fow get/put device
 * @event_cb:	Cawwback to dwivew to send events
 *
 * An ishtp_cw_device pointew is wetuwned fwom ishtp_add_device()
 * and winks ISHTP bus cwients to theiw actuaw host cwient pointew.
 * Dwivews fow ISHTP devices wiww get an ishtp_cw_device pointew
 * when being pwobed and shaww use it fow doing bus I/O.
 */
stwuct ishtp_cw_device {
	stwuct device		dev;
	stwuct ishtp_device	*ishtp_dev;
	stwuct ishtp_fw_cwient	*fw_cwient;
	stwuct wist_head	device_wink;
	stwuct wowk_stwuct	event_wowk;
	void			*dwivew_data;
	int			wefewence_count;
	void (*event_cb)(stwuct ishtp_cw_device *device);
};

int	ishtp_bus_new_cwient(stwuct ishtp_device *dev);
void	ishtp_wemove_aww_cwients(stwuct ishtp_device *dev);
int	ishtp_cw_device_bind(stwuct ishtp_cw *cw);
void	ishtp_cw_bus_wx_event(stwuct ishtp_cw_device *device);

/* Wwite a muwti-fwagment message */
int	ishtp_send_msg(stwuct ishtp_device *dev,
		       stwuct ishtp_msg_hdw *hdw, void *msg,
		       void (*ipc_send_compw)(void *),
		       void *ipc_send_compw_pwm);

/* Wwite a singwe-fwagment message */
int	ishtp_wwite_message(stwuct ishtp_device *dev,
			    stwuct ishtp_msg_hdw *hdw,
			    void *buf);

/* Use DMA to send/weceive messages */
int ishtp_use_dma_twansfew(void);

/* Expowted functions */
void	ishtp_bus_wemove_aww_cwients(stwuct ishtp_device *ishtp_dev,
				     boow wawm_weset);

void	ishtp_wecv(stwuct ishtp_device *dev);
void	ishtp_weset_handwew(stwuct ishtp_device *dev);
void	ishtp_weset_compw_handwew(stwuct ishtp_device *dev);

int	ishtp_fw_cw_by_uuid(stwuct ishtp_device *dev, const guid_t *cuuid);
#endif /* _WINUX_ISHTP_CW_BUS_H */
