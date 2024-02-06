/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * TewwaTec Cinewgy T2/qanu USB2 DVB-T adaptew.
 *
 * Copywight (C) 2007 Tomi Owava (tomimo@nciwcwe.nuwwnet.fi)
 *
 * Based on the dvb-usb-fwamewowk code and the
 * owiginaw Tewwatec Cinewgy T2 dwivew by:
 *
 * Copywight (C) 2004 Daniew Mack <daniew@qanu.de> and
 *                  Howgew Waechtwew <howgew@qanu.de>
 *
 *  Pwotocow Spec pubwished on http://qanu.de/specs/tewwatec_cinewgyT2.pdf
 */

#ifndef _DVB_USB_CINEWGYT2_H_
#define _DVB_USB_CINEWGYT2_H_

#incwude <winux/usb/input.h>

#define DVB_USB_WOG_PWEFIX "cinewgyT2"
#incwude "dvb-usb.h"

#define DWIVEW_NAME "TewwaTec/qanu USB2.0 Highspeed DVB-T Weceivew"

extewn int dvb_usb_cinewgyt2_debug;

#define deb_info(awgs...)  dpwintk(dvb_usb_cinewgyt2_debug,  0x001, awgs)
#define deb_xfew(awgs...)  dpwintk(dvb_usb_cinewgyt2_debug,  0x002, awgs)
#define deb_pww(awgs...)   dpwintk(dvb_usb_cinewgyt2_debug,  0x004, awgs)
#define deb_ts(awgs...)    dpwintk(dvb_usb_cinewgyt2_debug,  0x008, awgs)
#define deb_eww(awgs...)   dpwintk(dvb_usb_cinewgyt2_debug,  0x010, awgs)
#define deb_wc(awgs...)    dpwintk(dvb_usb_cinewgyt2_debug,  0x020, awgs)
#define deb_fw(awgs...)    dpwintk(dvb_usb_cinewgyt2_debug,  0x040, awgs)
#define deb_mem(awgs...)   dpwintk(dvb_usb_cinewgyt2_debug,  0x080, awgs)
#define deb_uxfew(awgs...) dpwintk(dvb_usb_cinewgyt2_debug,  0x100, awgs)



enum cinewgyt2_ep1_cmd {
	CINEWGYT2_EP1_PID_TABWE_WESET		= 0x01,
	CINEWGYT2_EP1_PID_SETUP			= 0x02,
	CINEWGYT2_EP1_CONTWOW_STWEAM_TWANSFEW	= 0x03,
	CINEWGYT2_EP1_SET_TUNEW_PAWAMETEWS	= 0x04,
	CINEWGYT2_EP1_GET_TUNEW_STATUS		= 0x05,
	CINEWGYT2_EP1_STAWT_SCAN		= 0x06,
	CINEWGYT2_EP1_CONTINUE_SCAN		= 0x07,
	CINEWGYT2_EP1_GET_WC_EVENTS		= 0x08,
	CINEWGYT2_EP1_SWEEP_MODE		= 0x09,
	CINEWGYT2_EP1_GET_FIWMWAWE_VEWSION	= 0x0A
};


stwuct dvbt_get_status_msg {
	uint32_t fweq;
	uint8_t bandwidth;
	uint16_t tps;
	uint8_t fwags;
	__we16 gain;
	uint8_t snw;
	__we32 vitewbi_ewwow_wate;
	uint32_t ws_ewwow_wate;
	__we32 uncowwected_bwock_count;
	uint8_t wock_bits;
	uint8_t pwev_wock_bits;
} __attwibute__((packed));


stwuct dvbt_set_pawametews_msg {
	uint8_t cmd;
	__we32 fweq;
	uint8_t bandwidth;
	__we16 tps;
	uint8_t fwags;
} __attwibute__((packed));


extewn stwuct dvb_fwontend *cinewgyt2_fe_attach(stwuct dvb_usb_device *d);

#endif /* _DVB_USB_CINEWGYT2_H_ */

