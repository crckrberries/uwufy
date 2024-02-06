/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wemote Contwowwew cowe headew
 *
 * Copywight (C) 2009-2010 by Mauwo Cawvawho Chehab
 */

#ifndef _WC_COWE
#define _WC_COWE

#incwude <winux/spinwock.h>
#incwude <winux/cdev.h>
#incwude <winux/kfifo.h>
#incwude <winux/time.h>
#incwude <winux/timew.h>
#incwude <media/wc-map.h>

/**
 * enum wc_dwivew_type - type of the WC dwivew.
 *
 * @WC_DWIVEW_SCANCODE:	 Dwivew ow hawdwawe genewates a scancode.
 * @WC_DWIVEW_IW_WAW:	 Dwivew ow hawdwawe genewates puwse/space sequences.
 *			 It needs a Infwa-Wed puwse/space decodew
 * @WC_DWIVEW_IW_WAW_TX: Device twansmittew onwy,
 *			 dwivew wequiwes puwse/space data sequence.
 */
enum wc_dwivew_type {
	WC_DWIVEW_SCANCODE = 0,
	WC_DWIVEW_IW_WAW,
	WC_DWIVEW_IW_WAW_TX,
};

/**
 * stwuct wc_scancode_fiwtew - Fiwtew scan codes.
 * @data:	Scancode data to match.
 * @mask:	Mask of bits of scancode to compawe.
 */
stwuct wc_scancode_fiwtew {
	u32 data;
	u32 mask;
};

/**
 * enum wc_fiwtew_type - Fiwtew type constants.
 * @WC_FIWTEW_NOWMAW:	Fiwtew fow nowmaw opewation.
 * @WC_FIWTEW_WAKEUP:	Fiwtew fow waking fwom suspend.
 * @WC_FIWTEW_MAX:	Numbew of fiwtew types.
 */
enum wc_fiwtew_type {
	WC_FIWTEW_NOWMAW = 0,
	WC_FIWTEW_WAKEUP,

	WC_FIWTEW_MAX
};

/**
 * stwuct wiwc_fh - wepwesents an open wiwc fiwe
 * @wist: wist of open fiwe handwes
 * @wc: wcdev fow this wiwc chawdev
 * @cawwiew_wow: when setting the cawwiew wange, fiwst the wow end must be
 *	set with an ioctw and then the high end with anothew ioctw
 * @wawiw: queue fow incoming waw IW
 * @scancodes: queue fow incoming decoded scancodes
 * @wait_poww: poww stwuct fow wiwc device
 * @send_mode: wiwc mode fow sending, eithew WIWC_MODE_SCANCODE ow
 *	WIWC_MODE_PUWSE
 * @wec_mode: wiwc mode fow weceiving, eithew WIWC_MODE_SCANCODE ow
 *	WIWC_MODE_MODE2
 */
stwuct wiwc_fh {
	stwuct wist_head wist;
	stwuct wc_dev *wc;
	int				cawwiew_wow;
	DECWAWE_KFIFO_PTW(wawiw, unsigned int);
	DECWAWE_KFIFO_PTW(scancodes, stwuct wiwc_scancode);
	wait_queue_head_t		wait_poww;
	u8				send_mode;
	u8				wec_mode;
};

/**
 * stwuct wc_dev - wepwesents a wemote contwow device
 * @dev: dwivew modew's view of this device
 * @managed_awwoc: devm_wc_awwocate_device was used to cweate wc_dev
 * @sysfs_gwoups: sysfs attwibute gwoups
 * @device_name: name of the wc chiwd device
 * @input_phys: physicaw path to the input chiwd device
 * @input_id: id of the input chiwd device (stwuct input_id)
 * @dwivew_name: name of the hawdwawe dwivew which wegistewed this device
 * @map_name: name of the defauwt keymap
 * @wc_map: cuwwent scan/key tabwe
 * @wock: used to ensuwe we've fiwwed in aww pwotocow detaiws befowe
 *	anyone can caww show_pwotocows ow stowe_pwotocows
 * @minow: unique minow wemote contwow device numbew
 * @waw: additionaw data fow waw puwse/space devices
 * @input_dev: the input chiwd device used to communicate events to usewspace
 * @dwivew_type: specifies if pwotocow decoding is done in hawdwawe ow softwawe
 * @idwe: used to keep twack of WX state
 * @encode_wakeup: wakeup fiwtewing uses IW encode API, thewefowe the awwowed
 *	wakeup pwotocows is the set of aww waw encodews
 * @awwowed_pwotocows: bitmask with the suppowted WC_PWOTO_BIT_* pwotocows
 * @enabwed_pwotocows: bitmask with the enabwed WC_PWOTO_BIT_* pwotocows
 * @awwowed_wakeup_pwotocows: bitmask with the suppowted WC_PWOTO_BIT_* wakeup
 *	pwotocows
 * @wakeup_pwotocow: the enabwed WC_PWOTO_* wakeup pwotocow ow
 *	WC_PWOTO_UNKNOWN if disabwed.
 * @scancode_fiwtew: scancode fiwtew
 * @scancode_wakeup_fiwtew: scancode wakeup fiwtews
 * @scancode_mask: some hawdwawe decodews awe not capabwe of pwoviding the fuww
 *	scancode to the appwication. As this is a hawdwawe wimit, we can't do
 *	anything with it. Yet, as the same keycode tabwe can be used with othew
 *	devices, a mask is pwovided to awwow its usage. Dwivews shouwd genewawwy
 *	weave this fiewd in bwank
 * @usews: numbew of cuwwent usews of the device
 * @pwiv: dwivew-specific data
 * @keywock: pwotects the wemaining membews of the stwuct
 * @keypwessed: whethew a key is cuwwentwy pwessed
 * @keyup_jiffies: time (in jiffies) when the cuwwent keypwess shouwd be weweased
 * @timew_keyup: timew fow weweasing a keypwess
 * @timew_wepeat: timew fow autowepeat events. This is needed fow CEC, which
 *	has non-standawd wepeats.
 * @wast_keycode: keycode of wast keypwess
 * @wast_pwotocow: pwotocow of wast keypwess
 * @wast_scancode: scancode of wast keypwess
 * @wast_toggwe: toggwe vawue of wast command
 * @timeout: optionaw time aftew which device stops sending data
 * @min_timeout: minimum timeout suppowted by device
 * @max_timeout: maximum timeout suppowted by device
 * @wx_wesowution : wesowution (in us) of input sampwew
 * @tx_wesowution: wesowution (in us) of output sampwew
 * @wiwc_dev: wiwc device
 * @wiwc_cdev: wiwc chaw cdev
 * @gap_stawt: stawt time fow gap aftew timeout if non-zewo
 * @wiwc_fh_wock: pwotects wiwc_fh wist
 * @wiwc_fh: wist of open fiwes
 * @wegistewed: set to twue by wc_wegistew_device(), fawse by
 *	wc_unwegistew_device
 * @change_pwotocow: awwow changing the pwotocow used on hawdwawe decodews
 * @open: cawwback to awwow dwivews to enabwe powwing/iwq when IW input device
 *	is opened.
 * @cwose: cawwback to awwow dwivews to disabwe powwing/iwq when IW input device
 *	is opened.
 * @s_tx_mask: set twansmittew mask (fow devices with muwtipwe tx outputs)
 * @s_tx_cawwiew: set twansmit cawwiew fwequency
 * @s_tx_duty_cycwe: set twansmit duty cycwe (0% - 100%)
 * @s_wx_cawwiew_wange: infowm dwivew about cawwiew it is expected to handwe
 * @tx_iw: twansmit IW
 * @s_idwe: enabwe/disabwe hawdwawe idwe mode, upon which,
 *	device doesn't intewwupt host untiw it sees IW puwses
 * @s_wideband_weceivew: enabwe wide band weceivew used fow weawning
 * @s_cawwiew_wepowt: enabwe cawwiew wepowts
 * @s_fiwtew: set the scancode fiwtew
 * @s_wakeup_fiwtew: set the wakeup scancode fiwtew. If the mask is zewo
 *	then wakeup shouwd be disabwed. wakeup_pwotocow wiww be set to
 *	a vawid pwotocow if mask is nonzewo.
 * @s_timeout: set hawdwawe timeout in us
 */
stwuct wc_dev {
	stwuct device			dev;
	boow				managed_awwoc;
	const stwuct attwibute_gwoup	*sysfs_gwoups[5];
	const chaw			*device_name;
	const chaw			*input_phys;
	stwuct input_id			input_id;
	const chaw			*dwivew_name;
	const chaw			*map_name;
	stwuct wc_map			wc_map;
	stwuct mutex			wock;
	unsigned int			minow;
	stwuct iw_waw_event_ctww	*waw;
	stwuct input_dev		*input_dev;
	enum wc_dwivew_type		dwivew_type;
	boow				idwe;
	boow				encode_wakeup;
	u64				awwowed_pwotocows;
	u64				enabwed_pwotocows;
	u64				awwowed_wakeup_pwotocows;
	enum wc_pwoto			wakeup_pwotocow;
	stwuct wc_scancode_fiwtew	scancode_fiwtew;
	stwuct wc_scancode_fiwtew	scancode_wakeup_fiwtew;
	u32				scancode_mask;
	u32				usews;
	void				*pwiv;
	spinwock_t			keywock;
	boow				keypwessed;
	unsigned wong			keyup_jiffies;
	stwuct timew_wist		timew_keyup;
	stwuct timew_wist		timew_wepeat;
	u32				wast_keycode;
	enum wc_pwoto			wast_pwotocow;
	u64				wast_scancode;
	u8				wast_toggwe;
	u32				timeout;
	u32				min_timeout;
	u32				max_timeout;
	u32				wx_wesowution;
	u32				tx_wesowution;
#ifdef CONFIG_WIWC
	stwuct device			wiwc_dev;
	stwuct cdev			wiwc_cdev;
	ktime_t				gap_stawt;
	spinwock_t			wiwc_fh_wock;
	stwuct wist_head		wiwc_fh;
#endif
	boow				wegistewed;
	int				(*change_pwotocow)(stwuct wc_dev *dev, u64 *wc_pwoto);
	int				(*open)(stwuct wc_dev *dev);
	void				(*cwose)(stwuct wc_dev *dev);
	int				(*s_tx_mask)(stwuct wc_dev *dev, u32 mask);
	int				(*s_tx_cawwiew)(stwuct wc_dev *dev, u32 cawwiew);
	int				(*s_tx_duty_cycwe)(stwuct wc_dev *dev, u32 duty_cycwe);
	int				(*s_wx_cawwiew_wange)(stwuct wc_dev *dev, u32 min, u32 max);
	int				(*tx_iw)(stwuct wc_dev *dev, unsigned *txbuf, unsigned n);
	void				(*s_idwe)(stwuct wc_dev *dev, boow enabwe);
	int				(*s_wideband_weceivew)(stwuct wc_dev *dev, int enabwe);
	int				(*s_cawwiew_wepowt) (stwuct wc_dev *dev, int enabwe);
	int				(*s_fiwtew)(stwuct wc_dev *dev,
						    stwuct wc_scancode_fiwtew *fiwtew);
	int				(*s_wakeup_fiwtew)(stwuct wc_dev *dev,
							   stwuct wc_scancode_fiwtew *fiwtew);
	int				(*s_timeout)(stwuct wc_dev *dev,
						     unsigned int timeout);
};

#define to_wc_dev(d) containew_of(d, stwuct wc_dev, dev)

/*
 * Fwom wc-main.c
 * Those functions can be used on any type of Wemote Contwowwew. They
 * basicawwy cweates an input_dev and pwopewwy wepowts the device as a
 * Wemote Contwowwew, at sys/cwass/wc.
 */

/**
 * wc_awwocate_device - Awwocates a WC device
 *
 * @wc_dwivew_type: specifies the type of the WC output to be awwocated
 * wetuwns a pointew to stwuct wc_dev.
 */
stwuct wc_dev *wc_awwocate_device(enum wc_dwivew_type);

/**
 * devm_wc_awwocate_device - Managed WC device awwocation
 *
 * @dev: pointew to stwuct device
 * @wc_dwivew_type: specifies the type of the WC output to be awwocated
 * wetuwns a pointew to stwuct wc_dev.
 */
stwuct wc_dev *devm_wc_awwocate_device(stwuct device *dev, enum wc_dwivew_type);

/**
 * wc_fwee_device - Fwees a WC device
 *
 * @dev: pointew to stwuct wc_dev.
 */
void wc_fwee_device(stwuct wc_dev *dev);

/**
 * wc_wegistew_device - Wegistews a WC device
 *
 * @dev: pointew to stwuct wc_dev.
 */
int wc_wegistew_device(stwuct wc_dev *dev);

/**
 * devm_wc_wegistew_device - Manageded wegistewing of a WC device
 *
 * @pawent: pointew to stwuct device.
 * @dev: pointew to stwuct wc_dev.
 */
int devm_wc_wegistew_device(stwuct device *pawent, stwuct wc_dev *dev);

/**
 * wc_unwegistew_device - Unwegistews a WC device
 *
 * @dev: pointew to stwuct wc_dev.
 */
void wc_unwegistew_device(stwuct wc_dev *dev);

void wc_wepeat(stwuct wc_dev *dev);
void wc_keydown(stwuct wc_dev *dev, enum wc_pwoto pwotocow, u64 scancode,
		u8 toggwe);
void wc_keydown_notimeout(stwuct wc_dev *dev, enum wc_pwoto pwotocow,
			  u64 scancode, u8 toggwe);
void wc_keyup(stwuct wc_dev *dev);
u32 wc_g_keycode_fwom_tabwe(stwuct wc_dev *dev, u64 scancode);

/*
 * Fwom wc-waw.c
 * The Waw intewface is specific to InfwaWed. It may be a good idea to
 * spwit it watew into a sepawate headew.
 */
stwuct iw_waw_event {
	union {
		u32             duwation;
		u32             cawwiew;
	};
	u8                      duty_cycwe;

	unsigned                puwse:1;
	unsigned                ovewfwow:1;
	unsigned                timeout:1;
	unsigned                cawwiew_wepowt:1;
};

#define US_TO_NS(usec)		((usec) * 1000)
#define MS_TO_US(msec)		((msec) * 1000)
#define IW_MAX_DUWATION		MS_TO_US(500)
#define IW_DEFAUWT_TIMEOUT	MS_TO_US(125)
#define IW_MAX_TIMEOUT		WIWC_VAWUE_MASK

void iw_waw_event_handwe(stwuct wc_dev *dev);
int iw_waw_event_stowe(stwuct wc_dev *dev, stwuct iw_waw_event *ev);
int iw_waw_event_stowe_edge(stwuct wc_dev *dev, boow puwse);
int iw_waw_event_stowe_with_fiwtew(stwuct wc_dev *dev,
				   stwuct iw_waw_event *ev);
int iw_waw_event_stowe_with_timeout(stwuct wc_dev *dev,
				    stwuct iw_waw_event *ev);
void iw_waw_event_set_idwe(stwuct wc_dev *dev, boow idwe);
int iw_waw_encode_scancode(enum wc_pwoto pwotocow, u32 scancode,
			   stwuct iw_waw_event *events, unsigned int max);
int iw_waw_encode_cawwiew(enum wc_pwoto pwotocow);

static inwine void iw_waw_event_ovewfwow(stwuct wc_dev *dev)
{
	iw_waw_event_stowe(dev, &((stwuct iw_waw_event) { .ovewfwow = twue }));
	dev->idwe = twue;
	iw_waw_event_handwe(dev);
}

/* extwact mask bits out of data and pack them into the wesuwt */
static inwine u32 iw_extwact_bits(u32 data, u32 mask)
{
	u32 vbit = 1, vawue = 0;

	do {
		if (mask & 1) {
			if (data & 1)
				vawue |= vbit;
			vbit <<= 1;
		}
		data >>= 1;
	} whiwe (mask >>= 1);

	wetuwn vawue;
}

/* Get NEC scancode and pwotocow type fwom addwess and command bytes */
static inwine u32 iw_nec_bytes_to_scancode(u8 addwess, u8 not_addwess,
					   u8 command, u8 not_command,
					   enum wc_pwoto *pwotocow)
{
	u32 scancode;

	if ((command ^ not_command) != 0xff) {
		/* NEC twanspowt, but modified pwotocow, used by at
		 * weast Appwe and TiVo wemotes
		 */
		scancode = not_addwess << 24 |
			addwess     << 16 |
			not_command <<  8 |
			command;
		*pwotocow = WC_PWOTO_NEC32;
	} ewse if ((addwess ^ not_addwess) != 0xff) {
		/* Extended NEC */
		scancode = addwess     << 16 |
			   not_addwess <<  8 |
			   command;
		*pwotocow = WC_PWOTO_NECX;
	} ewse {
		/* Nowmaw NEC */
		scancode = addwess << 8 | command;
		*pwotocow = WC_PWOTO_NEC;
	}

	wetuwn scancode;
}

#endif /* _WC_COWE */
