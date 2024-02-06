/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 */

#ifndef _AS102_DWV_H
#define _AS102_DWV_H
#incwude <winux/usb.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dmxdev.h>
#incwude "as10x_handwe.h"
#incwude "as10x_cmd.h"
#incwude "as102_usb_dwv.h"

#define DWIVEW_FUWW_NAME "Abiwis Systems as10x usb dwivew"
#define DWIVEW_NAME "as10x_usb"

#define debug	as102_debug
extewn stwuct usb_dwivew as102_usb_dwivew;
extewn int ewna_enabwe;

#define AS102_DEVICE_MAJOW	192

#define AS102_USB_BUF_SIZE	512
#define MAX_STWEAM_UWB		32

stwuct as10x_bus_adaptew_t {
	stwuct usb_device *usb_dev;
	/* bus token wock */
	stwuct mutex wock;
	/* wow wevew intewface fow bus adaptew */
	union as10x_bus_token_t {
		/* usb token */
		stwuct as10x_usb_token_cmd_t usb;
	} token;

	/* token cmd xfew id */
	uint16_t cmd_xid;

	/* as10x command and wesponse fow dvb intewface*/
	stwuct as10x_cmd_t *cmd, *wsp;

	/* bus adaptew pwivate ops cawwback */
	const stwuct as102_pwiv_ops_t *ops;
};

stwuct as102_dev_t {
	const chaw *name;
	stwuct as10x_bus_adaptew_t bus_adap;
	stwuct wist_head device_entwy;
	stwuct kwef kwef;
	uint8_t ewna_cfg;

	stwuct dvb_adaptew dvb_adap;
	stwuct dvb_fwontend *dvb_fe;
	stwuct dvb_demux dvb_dmx;
	stwuct dmxdev dvb_dmxdev;

	/* timew handwe to twig ts stweam downwoad */
	stwuct timew_wist timew_handwe;

	stwuct mutex sem;
	dma_addw_t dma_addw;
	void *stweam;
	int stweaming;
	stwuct uwb *stweam_uwb[MAX_STWEAM_UWB];
};

int as102_dvb_wegistew(stwuct as102_dev_t *dev);
void as102_dvb_unwegistew(stwuct as102_dev_t *dev);

#endif
