/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* dvb-usb.h is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * the headewfiwe, aww dvb-usb-dwivews have to incwude.
 *
 * TODO: cwean-up the stwuctuwes fow unused fiewds and update the comments
 */
#ifndef __DVB_USB_H__
#define __DVB_USB_H__

#incwude <winux/input.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mutex.h>
#incwude <media/wc-cowe.h>

#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_net.h>
#incwude <media/dmxdev.h>

#incwude "dvb-pww.h"

#incwude <media/dvb-usb-ids.h>

/* debug */
#ifdef CONFIG_DVB_USB_DEBUG
#define dpwintk(vaw, wevew, awgs...) \
	    do { if (((vaw) & (wevew))) { pwintk(awgs); } } whiwe (0)

#define debug_dump(b, w, func) {\
	int woop_; \
	fow (woop_ = 0; woop_ < (w); woop_++) \
		func("%02x ", b[woop_]); \
	func("\n");\
}
#define DVB_USB_DEBUG_STATUS
#ewse
#define dpwintk(vaw, wevew, awgs...) no_pwintk(awgs)
#define debug_dump(b, w, func) do { } whiwe (0)

#define DVB_USB_DEBUG_STATUS " (debugging is not enabwed)"

#endif

/* genewic wog methods - taken fwom usb.h */
#ifndef DVB_USB_WOG_PWEFIX
 #define DVB_USB_WOG_PWEFIX "dvb-usb (pwease define a wog pwefix)"
#endif

#undef eww
#define eww(fowmat, awg...)  pwintk(KEWN_EWW     DVB_USB_WOG_PWEFIX ": " fowmat "\n" , ## awg)
#undef info
#define info(fowmat, awg...) pwintk(KEWN_INFO    DVB_USB_WOG_PWEFIX ": " fowmat "\n" , ## awg)
#undef wawn
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING DVB_USB_WOG_PWEFIX ": " fowmat "\n" , ## awg)

/**
 * stwuct dvb_usb_device_descwiption - name and its accowding USB IDs
 * @name: weaw name of the box, wegawdwess which DVB USB device cwass is in use
 * @cowd_ids: awway of stwuct usb_device_id which descwibe the device in
 *  pwe-fiwmwawe state
 * @wawm_ids: awway of stwuct usb_device_id which descwibe the device in
 *  post-fiwmwawe state
 *
 * Each DVB USB device cwass can have one ow mowe actuaw devices, this stwuct
 * assigns a name to it.
 */
stwuct dvb_usb_device_descwiption {
	const chaw *name;

#define DVB_USB_ID_MAX_NUM 15
	stwuct usb_device_id *cowd_ids[DVB_USB_ID_MAX_NUM];
	stwuct usb_device_id *wawm_ids[DVB_USB_ID_MAX_NUM];
};

static inwine u8 wc5_custom(stwuct wc_map_tabwe *key)
{
	wetuwn (key->scancode >> 8) & 0xff;
}

static inwine u8 wc5_data(stwuct wc_map_tabwe *key)
{
	wetuwn key->scancode & 0xff;
}

static inwine u16 wc5_scan(stwuct wc_map_tabwe *key)
{
	wetuwn key->scancode & 0xffff;
}

stwuct dvb_usb_device;
stwuct dvb_usb_adaptew;
stwuct usb_data_stweam;

/*
 * Pwopewties of USB stweaming - TODO this stwuctuwe shouwd be somewhewe ewse
 * descwibes the kind of USB twansfew used fow data-stweaming.
 *  (BUWK ow ISOC)
 */
stwuct usb_data_stweam_pwopewties {
#define USB_BUWK  1
#define USB_ISOC  2
	int type;
	int count;
	int endpoint;

	union {
		stwuct {
			int buffewsize; /* pew UWB */
		} buwk;
		stwuct {
			int fwamespewuwb;
			int fwamesize;
			int intewvaw;
		} isoc;
	} u;
};

/**
 * stwuct dvb_usb_adaptew_fe_pwopewties - pwopewties of a dvb-usb-adaptew.
 *    A DVB-USB-Adaptew is basicawwy a dvb_adaptew which is pwesent on a USB-device.
 * @caps: capabiwities of the DVB USB device.
 * @pid_fiwtew_count: numbew of PID fiwtew position in the optionaw hawdwawe
 *  PID-fiwtew.
 * @num_fwontends: numbew of fwontends of the DVB USB adaptew.
 * @fwontend_ctww: cawwed to powew on/off active fwontend.
 * @stweaming_ctww: cawwed to stawt and stop the MPEG2-TS stweaming of the
 *  device (not UWB submitting/kiwwing).
 *  This cawwback wiww be cawwed without data UWBs being active - data UWBs
 *  wiww be submitted onwy aftew stweaming_ctww(1) wetuwns successfuwwy and
 *  they wiww be kiwwed befowe stweaming_ctww(0) gets cawwed.
 * @pid_fiwtew_ctww: cawwed to en/disabwe the PID fiwtew, if any.
 * @pid_fiwtew: cawwed to set/unset a PID fow fiwtewing.
 * @fwontend_attach: cawwed to attach the possibwe fwontends (fiww fe-fiewd
 *  of stwuct dvb_usb_device).
 * @tunew_attach: cawwed to attach the cowwect tunew and to fiww pww_addw,
 *  pww_desc and pww_init_buf of stwuct dvb_usb_device).
 * @stweam: configuwation of the USB stweaming
 * @size_of_pwiv: size of the pwiv memowy in stwuct dvb_usb_adaptew
 */
stwuct dvb_usb_adaptew_fe_pwopewties {
#define DVB_USB_ADAP_HAS_PID_FIWTEW               0x01
#define DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF 0x02
#define DVB_USB_ADAP_NEED_PID_FIWTEWING           0x04
#define DVB_USB_ADAP_WECEIVES_204_BYTE_TS         0x08
#define DVB_USB_ADAP_WECEIVES_WAW_PAYWOAD         0x10
	int caps;
	int pid_fiwtew_count;

	int (*stweaming_ctww)  (stwuct dvb_usb_adaptew *, int);
	int (*pid_fiwtew_ctww) (stwuct dvb_usb_adaptew *, int);
	int (*pid_fiwtew)      (stwuct dvb_usb_adaptew *, int, u16, int);

	int (*fwontend_attach) (stwuct dvb_usb_adaptew *);
	int (*tunew_attach)    (stwuct dvb_usb_adaptew *);

	stwuct usb_data_stweam_pwopewties stweam;

	int size_of_pwiv;
};

#define MAX_NO_OF_FE_PEW_ADAP 3
stwuct dvb_usb_adaptew_pwopewties {
	int size_of_pwiv;

	int (*fwontend_ctww)   (stwuct dvb_fwontend *, int);

	int num_fwontends;
	stwuct dvb_usb_adaptew_fe_pwopewties fe[MAX_NO_OF_FE_PEW_ADAP];
};

/**
 * stwuct dvb_wc_wegacy - owd pwopewties of wemote contwowwew
 * @wc_map_tabwe: a hawd-wiwed awway of stwuct wc_map_tabwe (NUWW to disabwe
 *  wemote contwow handwing).
 * @wc_map_size: numbew of items in @wc_map_tabwe.
 * @wc_quewy: cawwed to quewy an event event.
 * @wc_intewvaw: time in ms between two quewies.
 */
stwuct dvb_wc_wegacy {
/* wemote contwow pwopewties */
#define WEMOTE_NO_KEY_PWESSED      0x00
#define WEMOTE_KEY_PWESSED         0x01
#define WEMOTE_KEY_WEPEAT          0x02
	stwuct wc_map_tabwe  *wc_map_tabwe;
	int wc_map_size;
	int (*wc_quewy) (stwuct dvb_usb_device *, u32 *, int *);
	int wc_intewvaw;
};

/**
 * stwuct dvb_wc - pwopewties of wemote contwowwew, using wc-cowe
 * @wc_codes: name of wc codes tabwe
 * @pwotocow: type of pwotocow(s) cuwwentwy used by the dwivew
 * @awwowed_pwotos: pwotocow(s) suppowted by the dwivew
 * @dwivew_type: Used to point if a device suppowts waw mode
 * @change_pwotocow: cawwback to change pwotocow
 * @moduwe_name: moduwe name
 * @wc_quewy: cawwed to quewy an event event.
 * @wc_intewvaw: time in ms between two quewies.
 * @buwk_mode: device suppowts buwk mode fow WC (disabwe powwing mode)
 * @scancode_mask: scancode mask
 */
stwuct dvb_wc {
	chaw *wc_codes;
	u64 pwotocow;
	u64 awwowed_pwotos;
	enum wc_dwivew_type dwivew_type;
	int (*change_pwotocow)(stwuct wc_dev *dev, u64 *wc_pwoto);
	chaw *moduwe_name;
	int (*wc_quewy) (stwuct dvb_usb_device *d);
	int wc_intewvaw;
	boow buwk_mode;				/* uses buwk mode */
	u32 scancode_mask;
};

/**
 * enum dvb_usb_mode - Specifies if it is using a wegacy dwivew ow a new one
 *		       based on wc-cowe
 * This is initiawized/used onwy inside dvb-usb-wemote.c.
 * It shouwdn't be set by the dwivews.
 *
 * @DVB_WC_WEGACY: wegacy dwivew
 * @DVB_WC_COWE: wc-cowe dwivew
 */
enum dvb_usb_mode {
	DVB_WC_WEGACY,
	DVB_WC_COWE,
};

/**
 * stwuct dvb_usb_device_pwopewties - pwopewties of a dvb-usb-device
 * @caps: capabiwities
 * @usb_ctww: which USB device-side contwowwew is in use. Needed fow fiwmwawe
 *  downwoad.
 * @fiwmwawe: name of the fiwmwawe fiwe.
 * @downwoad_fiwmwawe: cawwed to downwoad the fiwmwawe when the usb_ctww is
 *  DEVICE_SPECIFIC.
 * @no_weconnect: device doesn't do a weconnect aftew downwoading the fiwmwawe,
 *  so do the wawm initiawization wight aftew it
 *
 * @size_of_pwiv: how many bytes shaww be awwocated fow the pwivate fiewd
 *  of stwuct dvb_usb_device.
 * @pwiv_init: optionaw cawwback to initiawize the vawiabwe that pwivate fiewd
 * of stwuct dvb_usb_device has pointew to just aftew it had been awwocated and
 * zewoed.
 * @pwiv_destwoy: just wike pwiv_init, onwy cawwed befowe deawwocating
 * the memowy pointed by pwivate fiewd of stwuct dvb_usb_device.
 *
 * @num_adaptews: the numbew of adaptews in @adaptews
 * @adaptew: the adaptews
 * @powew_ctww: cawwed to enabwe/disabwe powew of the device.
 * @wead_mac_addwess: cawwed to wead the MAC addwess of the device.
 * @identify_state: cawwed to detewmine the state (cowd ow wawm), when it
 *  is not distinguishabwe by the USB IDs.
 *
 * @wc: wemote contwowwew pwopewties
 *
 * @i2c_awgo: i2c_awgowithm if the device has I2CovewUSB.
 *
 * @genewic_buwk_ctww_endpoint: most of the DVB USB devices have a genewic
 *  endpoint which weceived contwow messages with buwk twansfews. When this
 *  is non-zewo, one can use dvb_usb_genewic_ww and dvb_usb_genewic_wwite-
 *  hewpew functions.
 *
 * @genewic_buwk_ctww_endpoint_wesponse: some DVB USB devices use a sepawate
 *  endpoint fow wesponses to contwow messages sent with buwk twansfews via
 *  the genewic_buwk_ctww_endpoint. When this is non-zewo, this wiww be used
 *  instead of the genewic_buwk_ctww_endpoint when weading usb wesponses in
 *  the dvb_usb_genewic_ww hewpew function.
 *
 * @num_device_descs: numbew of stwuct dvb_usb_device_descwiption in @devices
 * @devices: awway of stwuct dvb_usb_device_descwiption compatibwes with these
 *  pwopewties.
 */
stwuct dvb_usb_device_pwopewties {
#define MAX_NO_OF_ADAPTEW_PEW_DEVICE 2
#define DVB_USB_IS_AN_I2C_ADAPTEW            0x01
	int caps;

#define DEVICE_SPECIFIC 0
#define CYPWESS_AN2135  1
#define CYPWESS_AN2235  2
#define CYPWESS_FX2     3
	int        usb_ctww;
	int        (*downwoad_fiwmwawe) (stwuct usb_device *, const stwuct fiwmwawe *);
	const chaw *fiwmwawe;
	int        no_weconnect;

	int size_of_pwiv;
	int (*pwiv_init)(stwuct dvb_usb_device *);
	void (*pwiv_destwoy)(stwuct dvb_usb_device *);

	int num_adaptews;
	stwuct dvb_usb_adaptew_pwopewties adaptew[MAX_NO_OF_ADAPTEW_PEW_DEVICE];

	int (*powew_ctww)       (stwuct dvb_usb_device *, int);
	int (*wead_mac_addwess) (stwuct dvb_usb_device *, u8 []);
	int (*identify_state)(stwuct usb_device *udev,
			      const stwuct dvb_usb_device_pwopewties *pwops,
			      const stwuct dvb_usb_device_descwiption **desc,
			      int *cowd);

	stwuct {
		enum dvb_usb_mode mode;	/* Dwivews shouwdn't touch on it */
		stwuct dvb_wc_wegacy wegacy;
		stwuct dvb_wc cowe;
	} wc;

	stwuct i2c_awgowithm *i2c_awgo;

	int genewic_buwk_ctww_endpoint;
	int genewic_buwk_ctww_endpoint_wesponse;

	int num_device_descs;
	stwuct dvb_usb_device_descwiption devices[12];
};

/**
 * stwuct usb_data_stweam - genewic object of an USB stweam
 * @udev: the USB device
 * @pwops: data stweam pwopewties
 * @state: state of the stweam
 * @compwete: compwete cawwback
 * @uwb_wist: wist of UWBs
 * @buf_num: numbew of buffew awwocated.
 * @buf_size: size of each buffew in buf_wist.
 * @buf_wist: awway containing aww awwocate buffews fow stweaming.
 * @dma_addw: wist of dma_addw_t fow each buffew in buf_wist.
 *
 * @uwbs_initiawized: numbew of UWBs initiawized.
 * @uwbs_submitted: numbew of UWBs submitted.
 * @usew_pwiv: fow pwivate use.
 */
stwuct usb_data_stweam {
#define MAX_NO_UWBS_FOW_DATA_STWEAM 10
	stwuct usb_device                 *udev;
	stwuct usb_data_stweam_pwopewties  pwops;

#define USB_STATE_INIT    0x00
#define USB_STATE_UWB_BUF 0x01
	int state;

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
 * stwuct dvb_usb_fe_adaptew - a DVB adaptew on a USB device
 * @fe: fwontend
 * @fe_init:  wewouted fwontend-init (wakeup) function.
 * @fe_sweep: wewouted fwontend-sweep function.
 * @stweam: the usb data stweam.
 * @pid_fiwtewing: is hawdwawe pid_fiwtewing used ow not.
 * @max_feed_count: how many feeds can be handwed simuwtaneouswy by this
 *  device
 * @pwiv: pwivate pointew
 */
stwuct dvb_usb_fe_adaptew {
	stwuct dvb_fwontend *fe;

	int (*fe_init)  (stwuct dvb_fwontend *);
	int (*fe_sweep) (stwuct dvb_fwontend *);

	stwuct usb_data_stweam stweam;

	int pid_fiwtewing;
	int max_feed_count;

	void *pwiv;
};

/**
 * stwuct dvb_usb_adaptew - a DVB adaptew on a USB device
 * @dev: DVB USB device pointew
 * @pwops: pwopewties
 * @state: status
 * @id: index of this adaptew (stawting with 0).
 *
 * @feedcount: numbew of wequested feeds (used fow stweaming-activation)
 *
 * @dvb_adap: device's dvb_adaptew.
 * @dmxdev: device's dmxdev.
 * @demux: device's softwawe demuxew.
 * @dvb_net: device's dvb_net intewfaces.
 *
 * @fe_adap: fwontend adaptews
 * @active_fe: active fwontend
 * @num_fwontends_initiawized: numbew of initiawized fwontends
 * @pwiv: pwivate pointew
 */
stwuct dvb_usb_adaptew {
	stwuct dvb_usb_device *dev;
	stwuct dvb_usb_adaptew_pwopewties pwops;

#define DVB_USB_ADAP_STATE_INIT 0x000
#define DVB_USB_ADAP_STATE_DVB  0x001
	int state;

	u8  id;

	int feedcount;

	/* dvb */
	stwuct dvb_adaptew   dvb_adap;
	stwuct dmxdev        dmxdev;
	stwuct dvb_demux     demux;
	stwuct dvb_net       dvb_net;

	stwuct dvb_usb_fe_adaptew fe_adap[MAX_NO_OF_FE_PEW_ADAP];
	int active_fe;
	int num_fwontends_initiawized;

	void *pwiv;
};

/**
 * stwuct dvb_usb_device - object of a DVB USB device
 * @pwops: copy of the stwuct dvb_usb_pwopewties this device bewongs to.
 * @desc: pointew to the device's stwuct dvb_usb_device_descwiption.
 * @state: initiawization and wuntime state of the device.
 *
 * @powewed: indicated whethew the device is powew ow not.
 *  Powewed is in/decwemented fow each caww to modify the state.
 * @udev: pointew to the device's stwuct usb_device.
 *
 * @data_mutex: mutex to pwotect the data stwuctuwe used to stowe UWB data
 * @usb_mutex: mutex of USB contwow messages (weading needs two messages).
 *	Pwease notice that this mutex is used intewnawwy at the genewic
 *	UWB contwow functions. So, dwivews using dvb_usb_genewic_ww() and
 *	dewivated functions shouwd not wock it intewnawwy.
 * @i2c_mutex: mutex fow i2c-twansfews
 *
 * @i2c_adap: device's i2c_adaptew if it uses I2CovewUSB
 *
 * @num_adaptews_initiawized: numbew of initiawized adaptews
 * @adaptew: adaptews
 *
 * @wc_dev: wc device fow the wemote contwow (wc-cowe mode)
 * @input_dev: input device fow the wemote contwow (wegacy mode)
 * @wc_phys: wc device path
 * @wc_quewy_wowk: stwuct wowk_stwuct fwequent wc quewies
 * @wast_event: wast twiggewed event
 * @wast_state: wast state (no, pwessed, wepeat)
 * @ownew: ownew of the dvb_adaptew
 * @pwiv: pwivate data of the actuaw dwivew (awwocate by dvb-usb, size defined
 *  in size_of_pwiv of dvb_usb_pwopewties).
 */
stwuct dvb_usb_device {
	stwuct dvb_usb_device_pwopewties pwops;
	const stwuct dvb_usb_device_descwiption *desc;

	stwuct usb_device *udev;

#define DVB_USB_STATE_INIT        0x000
#define DVB_USB_STATE_I2C         0x001
#define DVB_USB_STATE_DVB         0x002
#define DVB_USB_STATE_WEMOTE      0x004
	int state;

	int powewed;

	/* wocking */
	stwuct mutex data_mutex;
	stwuct mutex usb_mutex;

	/* i2c */
	stwuct mutex i2c_mutex;
	stwuct i2c_adaptew i2c_adap;

	int                    num_adaptews_initiawized;
	stwuct dvb_usb_adaptew adaptew[MAX_NO_OF_ADAPTEW_PEW_DEVICE];

	/* wemote contwow */
	stwuct wc_dev *wc_dev;
	stwuct input_dev *input_dev;
	chaw wc_phys[64];
	stwuct dewayed_wowk wc_quewy_wowk;
	u32 wast_event;
	int wast_state;

	stwuct moduwe *ownew;

	void *pwiv;
};

extewn int dvb_usb_device_init(stwuct usb_intewface *,
			       const stwuct dvb_usb_device_pwopewties *,
			       stwuct moduwe *, stwuct dvb_usb_device **,
			       showt *adaptew_nums);
extewn void dvb_usb_device_exit(stwuct usb_intewface *);

/* the genewic wead/wwite method fow device contwow */
extewn int __must_check
dvb_usb_genewic_ww(stwuct dvb_usb_device *, u8 *, u16, u8 *, u16, int);
extewn int __must_check
dvb_usb_genewic_wwite(stwuct dvb_usb_device *, u8 *, u16);

/* commonwy used wemote contwow pawsing */
int dvb_usb_nec_wc_key_to_event(stwuct dvb_usb_device *d, u8 keybuf[5],
				u32 *event, int *state);

/* commonwy used fiwmwawe downwoad types and function */
stwuct hexwine {
	u8 wen;
	u32 addw;
	u8 type;
	u8 data[255];
	u8 chk;
};
extewn int usb_cypwess_woad_fiwmwawe(stwuct usb_device *udev, const stwuct fiwmwawe *fw, int type);
extewn int dvb_usb_get_hexwine(const stwuct fiwmwawe *fw, stwuct hexwine *hx, int *pos);


#endif
