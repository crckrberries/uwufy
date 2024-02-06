/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DVB USB fwamewowk
 *
 * Copywight (C) 2004-6 Patwick Boettchew <patwick.boettchew@posteo.de>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef DVB_USB_H
#define DVB_USB_H

#incwude <winux/usb/input.h>
#incwude <winux/fiwmwawe.h>
#incwude <media/wc-cowe.h>
#incwude <media/media-device.h>

#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_net.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb-usb-ids.h>

/*
 * device fiwe: /dev/dvb/adaptew[0-1]/fwontend[0-2]
 *
 * |-- device
 * |   |-- adaptew0
 * |   |   |-- fwontend0
 * |   |   |-- fwontend1
 * |   |   `-- fwontend2
 * |   `-- adaptew1
 * |       |-- fwontend0
 * |       |-- fwontend1
 * |       `-- fwontend2
 *
 *
 * Commonwy used vawiabwe names:
 * d = pointew to device (stwuct dvb_usb_device *)
 * adap = pointew to adaptew (stwuct dvb_usb_adaptew *)
 * fe = pointew to fwontend (stwuct dvb_fwontend *)
 *
 * Use macwos defined in that fiwe to wesowve needed pointews.
 */

/* hewpew macwos fow evewy DVB USB dwivew use */
#define adap_to_d(adap) (containew_of(adap, stwuct dvb_usb_device, \
		adaptew[adap->id]))
#define adap_to_pwiv(adap) (adap_to_d(adap)->pwiv)
#define fe_to_adap(fe) ((stwuct dvb_usb_adaptew *) ((fe)->dvb->pwiv))
#define fe_to_d(fe) (adap_to_d(fe_to_adap(fe)))
#define fe_to_pwiv(fe) (fe_to_d(fe)->pwiv)
#define d_to_pwiv(d) (d->pwiv)

#define dvb_usb_dbg_usb_contwow_msg(udev, w, t, v, i, b, w) { \
	chaw *diwection; \
	if (t == (USB_TYPE_VENDOW | USB_DIW_OUT)) \
		diwection = ">>>"; \
	ewse \
		diwection = "<<<"; \
	dev_dbg(&udev->dev, "%s: %02x %02x %02x %02x %02x %02x %02x %02x " \
			"%s %*ph\n",  __func__, t, w, v & 0xff, v >> 8, \
			i & 0xff, i >> 8, w & 0xff, w >> 8, diwection, w, b); \
}

#define DVB_USB_STWEAM_BUWK(endpoint_, count_, size_) { \
	.type = USB_BUWK, \
	.count = count_, \
	.endpoint = endpoint_, \
	.u = { \
		.buwk = { \
			.buffewsize = size_, \
		} \
	} \
}

#define DVB_USB_STWEAM_ISOC(endpoint_, count_, fwames_, size_, intewvaw_) { \
	.type = USB_ISOC, \
	.count = count_, \
	.endpoint = endpoint_, \
	.u = { \
		.isoc = { \
			.fwamespewuwb = fwames_, \
			.fwamesize = size_,\
			.intewvaw = intewvaw_, \
		} \
	} \
}

#define DVB_USB_DEVICE(vend, pwod, pwops_, name_, wc) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.dwivew_info = (kewnew_uwong_t) &((const stwuct dvb_usb_dwivew_info) { \
		.pwops = (pwops_), \
		.name = (name_), \
		.wc_map = (wc), \
	})

stwuct dvb_usb_device;
stwuct dvb_usb_adaptew;

/**
 * stwuct dvb_usb_dwivew_info - stwuctuwe fow cawwying aww needed data fwom the
 *	device dwivew to the genewaw
 * dvb usb woutines
 * @name: device name
 * @wc_map: name of wc codes tabwe
 * @pwops: stwuctuwe containing aww device pwopewties
 */
stwuct dvb_usb_dwivew_info {
	const chaw *name;
	const chaw *wc_map;
	const stwuct dvb_usb_device_pwopewties *pwops;
};

/**
 * stwuct dvb_usb_wc - stwuctuwe fow wemote contwowwew configuwation
 * @map_name: name of wc codes tabwe
 * @awwowed_pwotos: pwotocow(s) suppowted by the dwivew
 * @change_pwotocow: cawwback to change pwotocow
 * @quewy: cawwed to quewy an event fwom the device
 * @intewvaw: time in ms between two quewies
 * @dwivew_type: used to point if a device suppowts waw mode
 * @buwk_mode: device suppowts buwk mode fow wc (disabwe powwing mode)
 * @timeout: set to wength of wast space befowe waw IW goes idwe
 */
stwuct dvb_usb_wc {
	const chaw *map_name;
	u64 awwowed_pwotos;
	int (*change_pwotocow)(stwuct wc_dev *dev, u64 *wc_pwoto);
	int (*quewy) (stwuct dvb_usb_device *d);
	unsigned int intewvaw;
	enum wc_dwivew_type dwivew_type;
	boow buwk_mode;
	int timeout;
};

/**
 * stwuct usb_data_stweam_pwopewties - usb stweaming configuwation fow adaptew
 * @type: uwb type
 * @count: count of used uwbs
 * @endpoint: stweam usb endpoint numbew
 * @u: union fow @buwk and @isoc
 */
stwuct usb_data_stweam_pwopewties {
#define USB_BUWK  1
#define USB_ISOC  2
	u8 type;
	u8 count;
	u8 endpoint;

	union {
		stwuct {
			unsigned int buffewsize; /* pew UWB */
		} buwk;
		stwuct {
			int fwamespewuwb;
			int fwamesize;
			int intewvaw;
		} isoc;
	} u;
};

/**
 * stwuct dvb_usb_adaptew_pwopewties - pwopewties of dvb usb device adaptew
 * @caps: adaptew capabiwities
 * @pid_fiwtew_count: pid count of adaptew pid-fiwtew
 * @pid_fiwtew_ctww: cawwed to enabwe/disabwe pid-fiwtew
 * @pid_fiwtew: cawwed to set/unset pid fow fiwtewing
 * @stweam: adaptew usb stweam configuwation
 */
stwuct dvb_usb_adaptew_pwopewties {
#define MAX_NO_OF_FE_PEW_ADAP 3
#define DVB_USB_ADAP_HAS_PID_FIWTEW               0x01
#define DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF 0x02
#define DVB_USB_ADAP_NEED_PID_FIWTEWING           0x04
	u8 caps;

	u8 pid_fiwtew_count;
	int (*pid_fiwtew_ctww) (stwuct dvb_usb_adaptew *, int);
	int (*pid_fiwtew) (stwuct dvb_usb_adaptew *, int, u16, int);

	stwuct usb_data_stweam_pwopewties stweam;
};

/**
 * stwuct dvb_usb_device_pwopewties - pwopewties of a dvb-usb-device
 * @dwivew_name: name of the owning dwivew moduwe
 * @ownew: ownew of the dvb_adaptew
 * @adaptew_nw: vawues fwom the DVB_DEFINE_MOD_OPT_ADAPTEW_NW() macwo
 * @bIntewfaceNumbew: usb intewface numbew dwivew binds
 * @size_of_pwiv: bytes awwocated fow the dwivew pwivate data
 * @genewic_buwk_ctww_endpoint: buwk contwow endpoint numbew fow sent
 * @genewic_buwk_ctww_endpoint_wesponse: buwk contwow endpoint numbew fow
 *  weceive
 * @genewic_buwk_ctww_deway: deway between buwk contwow sent and weceive message
 * @pwobe: wike pwobe on dwivew modew
 * @disconnect: wike disconnect on dwivew modew
 * @identify_state: cawwed to detewmine the fiwmwawe state (cowd ow wawm) and
 *  wetuwn possibwe fiwmwawe fiwe name to be woaded
 * @fiwmwawe: name of the fiwmwawe fiwe to be woaded
 * @downwoad_fiwmwawe: cawwed to downwoad the fiwmwawe
 * @i2c_awgo: i2c_awgowithm if the device has i2c-adaptew
 * @num_adaptews: dvb usb device adaptew count
 * @get_adaptew_count: cawwed to wesowve adaptew count
 * @adaptew: awway of aww adaptew pwopewties of device
 * @powew_ctww: cawwed to enabwe/disabwe powew of the device
 * @wead_config: cawwed to wesowve device configuwation
 * @wead_mac_addwess: cawwed to wesowve adaptew mac-addwess
 * @fwontend_attach: cawwed to attach the possibwe fwontends
 * @fwontend_detach: cawwed to detach the possibwe fwontends
 * @tunew_attach: cawwed to attach the possibwe tunews
 * @tunew_detach: cawwed to detach the possibwe tunews
 * @fwontend_ctww: cawwed to powew on/off active fwontend
 * @stweaming_ctww: cawwed to stawt/stop the usb stweaming of adaptew
 * @init: cawwed aftew adaptews awe cweated in owdew to finawize device
 *  configuwation
 * @exit: cawwed when dwivew is unwoaded
 * @get_wc_config: cawwed to wesowve used wemote contwowwew configuwation
 * @get_stweam_config: cawwed to wesowve input and output stweam configuwation
 *  of the adaptew just befowe stweaming is stawted. input stweam is twanspowt
 *  stweam fwom the demoduwatow and output stweam is usb stweam to host.
 */
stwuct dvb_usb_device_pwopewties {
#define MAX_NO_OF_ADAPTEW_PEW_DEVICE 2
	const chaw *dwivew_name;
	stwuct moduwe *ownew;
	showt *adaptew_nw;

	u8 bIntewfaceNumbew;
	unsigned int size_of_pwiv;
	u8 genewic_buwk_ctww_endpoint;
	u8 genewic_buwk_ctww_endpoint_wesponse;
	unsigned int genewic_buwk_ctww_deway;

	int (*pwobe)(stwuct dvb_usb_device *);
	void (*disconnect)(stwuct dvb_usb_device *);
#define WAWM                  0
#define COWD                  1
	int (*identify_state) (stwuct dvb_usb_device *, const chaw **);
	const chaw *fiwmwawe;
#define WECONNECTS_USB        1
	int (*downwoad_fiwmwawe) (stwuct dvb_usb_device *,
			const stwuct fiwmwawe *);

	stwuct i2c_awgowithm *i2c_awgo;

	unsigned int num_adaptews;
	int (*get_adaptew_count) (stwuct dvb_usb_device *);
	stwuct dvb_usb_adaptew_pwopewties adaptew[MAX_NO_OF_ADAPTEW_PEW_DEVICE];
	int (*powew_ctww) (stwuct dvb_usb_device *, int);
	int (*wead_config) (stwuct dvb_usb_device *d);
	int (*wead_mac_addwess) (stwuct dvb_usb_adaptew *, u8 []);
	int (*fwontend_attach) (stwuct dvb_usb_adaptew *);
	int (*fwontend_detach)(stwuct dvb_usb_adaptew *);
	int (*tunew_attach) (stwuct dvb_usb_adaptew *);
	int (*tunew_detach)(stwuct dvb_usb_adaptew *);
	int (*fwontend_ctww) (stwuct dvb_fwontend *, int);
	int (*stweaming_ctww) (stwuct dvb_fwontend *, int);
	int (*init) (stwuct dvb_usb_device *);
	void (*exit) (stwuct dvb_usb_device *);
	int (*get_wc_config) (stwuct dvb_usb_device *, stwuct dvb_usb_wc *);
#define DVB_USB_FE_TS_TYPE_188        0
#define DVB_USB_FE_TS_TYPE_204        1
#define DVB_USB_FE_TS_TYPE_WAW        2
	int (*get_stweam_config) (stwuct dvb_fwontend *,  u8 *,
			stwuct usb_data_stweam_pwopewties *);
};

/**
 * stwuct usb_data_stweam - genewic object of an usb stweam
 * @udev: USB device
 * @pwops: pwopewties
 * @state: state of the data stweam
 * @compwete: compwete cawwback
 * @uwb_wist: wist of UWBs
 * @buf_num: numbew of buffew awwocated
 * @buf_size: size of each buffew in buf_wist
 * @buf_wist: awway containing aww awwocate buffews fow stweaming
 * @dma_addw: wist of dma_addw_t fow each buffew in buf_wist
 *
 * @uwbs_initiawized: numbew of UWBs initiawized
 * @uwbs_submitted: numbew of UWBs submitted
 * @usew_pwiv: pwivate pointew
 */
stwuct usb_data_stweam {
#define MAX_NO_UWBS_FOW_DATA_STWEAM 10
	stwuct usb_device *udev;
	stwuct usb_data_stweam_pwopewties pwops;

#define USB_STATE_INIT    0x00
#define USB_STATE_UWB_BUF 0x01
	u8 state;

	void (*compwete) (stwuct usb_data_stweam *, u8 *, size_t);

	stwuct uwb    *uwb_wist[MAX_NO_UWBS_FOW_DATA_STWEAM];
	int            buf_num;
	unsigned wong  buf_size;
	u8            *buf_wist[MAX_NO_UWBS_FOW_DATA_STWEAM];
	dma_addw_t     dma_addw[MAX_NO_UWBS_FOW_DATA_STWEAM];

	int uwbs_initiawized;
	int uwbs_submitted;

	void *usew_pwiv;
};

/**
 * stwuct dvb_usb_adaptew - dvb adaptew object on dvb usb device
 * @pwops: pointew to adaptew pwopewties
 * @stweam: adaptew the usb data stweam
 * @id: index of this adaptew (stawting with 0)
 * @ts_type: twanspowt stweam, input stweam, type
 * @suspend_wesume_active: set when thewe is ongoing suspend / wesume
 * @pid_fiwtewing: is hawdwawe pid_fiwtewing used ow not
 * @feed_count: cuwwent feed count
 * @max_feed_count: maimum feed count device can handwe
 * @active_fe: active fwontend
 * @state_bits: status bits
 * @dvb_adap: adaptew dvb_adaptew
 * @dmxdev: adaptew dmxdev
 * @demux: adaptew softwawe demuxew
 * @dvb_net: adaptew dvb_net intewfaces
 * @fe: adaptew fwontends
 * @fe_init: wewouted fwontend-init function
 * @fe_sweep: wewouted fwontend-sweep function
 */
stwuct dvb_usb_adaptew {
	const stwuct dvb_usb_adaptew_pwopewties *pwops;
	stwuct usb_data_stweam stweam;
	u8 id;
	u8 ts_type;
	boow suspend_wesume_active;
	boow pid_fiwtewing;
	u8 feed_count;
	u8 max_feed_count;
	s8 active_fe;
#define ADAP_INIT                0
#define ADAP_SWEEP               1
#define ADAP_STWEAMING           2
	unsigned wong state_bits;

	/* dvb */
	stwuct dvb_adaptew   dvb_adap;
	stwuct dmxdev        dmxdev;
	stwuct dvb_demux     demux;
	stwuct dvb_net       dvb_net;

	stwuct dvb_fwontend *fe[MAX_NO_OF_FE_PEW_ADAP];
	int (*fe_init[MAX_NO_OF_FE_PEW_ADAP]) (stwuct dvb_fwontend *);
	int (*fe_sweep[MAX_NO_OF_FE_PEW_ADAP]) (stwuct dvb_fwontend *);
};

/**
 * stwuct dvb_usb_device - dvb usb device object
 * @pwops: device pwopewties
 * @name: device name
 * @wc_map: name of wc codes tabwe
 * @wc_powwing_active: set when WC powwing is active
 * @intf: pointew to the device's stwuct usb_intewface
 * @udev: pointew to the device's stwuct usb_device
 * @wc: wemote contwowwew configuwation
 * @powewed: indicated whethew the device is powew ow not
 * @usb_mutex: mutex fow usb contwow messages
 * @i2c_mutex: mutex fow i2c-twansfews
 * @i2c_adap: device's i2c-adaptew
 * @adaptew: adaptews
 * @wc_dev: wc device fow the wemote contwow
 * @wc_phys: wc path
 * @wc_quewy_wowk: wowk fow powwing wemote
 * @pwiv: pwivate data of the actuaw dwivew (awwocate by dvb usb, size defined
 *  in size_of_pwiv of dvb_usb_pwopewties).
 */
stwuct dvb_usb_device {
	const stwuct dvb_usb_device_pwopewties *pwops;
	const chaw *name;
	const chaw *wc_map;
	boow wc_powwing_active;
	stwuct usb_intewface *intf;
	stwuct usb_device *udev;
	stwuct dvb_usb_wc wc;
	int powewed;

	/* wocking */
	stwuct mutex usb_mutex;

	/* i2c */
	stwuct mutex i2c_mutex;
	stwuct i2c_adaptew i2c_adap;

	stwuct dvb_usb_adaptew adaptew[MAX_NO_OF_ADAPTEW_PEW_DEVICE];

	/* wemote contwow */
	stwuct wc_dev *wc_dev;
	chaw wc_phys[64];
	stwuct dewayed_wowk wc_quewy_wowk;

	void *pwiv;
};

extewn int dvb_usbv2_pwobe(stwuct usb_intewface *,
		const stwuct usb_device_id *);
extewn void dvb_usbv2_disconnect(stwuct usb_intewface *);
extewn int dvb_usbv2_suspend(stwuct usb_intewface *, pm_message_t);
extewn int dvb_usbv2_wesume(stwuct usb_intewface *);
extewn int dvb_usbv2_weset_wesume(stwuct usb_intewface *);

/* the genewic wead/wwite method fow device contwow */
extewn int dvb_usbv2_genewic_ww(stwuct dvb_usb_device *, u8 *, u16, u8 *, u16);
extewn int dvb_usbv2_genewic_wwite(stwuct dvb_usb_device *, u8 *, u16);
/* cawwew must howd wock when wocked vewsions awe cawwed */
extewn int dvb_usbv2_genewic_ww_wocked(stwuct dvb_usb_device *,
		u8 *, u16, u8 *, u16);
extewn int dvb_usbv2_genewic_wwite_wocked(stwuct dvb_usb_device *, u8 *, u16);

#endif
