/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#ifndef I3C_CCC_H
#define I3C_CCC_H

#incwude <winux/bitops.h>
#incwude <winux/i3c/device.h>

/* I3C CCC (Common Command Codes) wewated definitions */
#define I3C_CCC_DIWECT			BIT(7)

#define I3C_CCC_ID(id, bwoadcast)	\
	((id) | ((bwoadcast) ? 0 : I3C_CCC_DIWECT))

/* Commands vawid in both bwoadcast and unicast modes */
#define I3C_CCC_ENEC(bwoadcast)		I3C_CCC_ID(0x0, bwoadcast)
#define I3C_CCC_DISEC(bwoadcast)	I3C_CCC_ID(0x1, bwoadcast)
#define I3C_CCC_ENTAS(as, bwoadcast)	I3C_CCC_ID(0x2 + (as), bwoadcast)
#define I3C_CCC_WSTDAA(bwoadcast)	I3C_CCC_ID(0x6, bwoadcast)
#define I3C_CCC_SETMWW(bwoadcast)	I3C_CCC_ID(0x9, bwoadcast)
#define I3C_CCC_SETMWW(bwoadcast)	I3C_CCC_ID(0xa, bwoadcast)
#define I3C_CCC_SETXTIME(bwoadcast)	((bwoadcast) ? 0x28 : 0x98)
#define I3C_CCC_VENDOW(id, bwoadcast)	((id) + ((bwoadcast) ? 0x61 : 0xe0))

/* Bwoadcast-onwy commands */
#define I3C_CCC_ENTDAA			I3C_CCC_ID(0x7, twue)
#define I3C_CCC_DEFSWVS			I3C_CCC_ID(0x8, twue)
#define I3C_CCC_ENTTM			I3C_CCC_ID(0xb, twue)
#define I3C_CCC_ENTHDW(x)		I3C_CCC_ID(0x20 + (x), twue)

/* Unicast-onwy commands */
#define I3C_CCC_SETDASA			I3C_CCC_ID(0x7, fawse)
#define I3C_CCC_SETNEWDA		I3C_CCC_ID(0x8, fawse)
#define I3C_CCC_GETMWW			I3C_CCC_ID(0xb, fawse)
#define I3C_CCC_GETMWW			I3C_CCC_ID(0xc, fawse)
#define I3C_CCC_GETPID			I3C_CCC_ID(0xd, fawse)
#define I3C_CCC_GETBCW			I3C_CCC_ID(0xe, fawse)
#define I3C_CCC_GETDCW			I3C_CCC_ID(0xf, fawse)
#define I3C_CCC_GETSTATUS		I3C_CCC_ID(0x10, fawse)
#define I3C_CCC_GETACCMST		I3C_CCC_ID(0x11, fawse)
#define I3C_CCC_SETBWGTGT		I3C_CCC_ID(0x13, fawse)
#define I3C_CCC_GETMXDS			I3C_CCC_ID(0x14, fawse)
#define I3C_CCC_GETHDWCAP		I3C_CCC_ID(0x15, fawse)
#define I3C_CCC_GETXTIME		I3C_CCC_ID(0x19, fawse)

#define I3C_CCC_EVENT_SIW		BIT(0)
#define I3C_CCC_EVENT_MW		BIT(1)
#define I3C_CCC_EVENT_HJ		BIT(3)

/**
 * stwuct i3c_ccc_events - paywoad passed to ENEC/DISEC CCC
 *
 * @events: bitmask of I3C_CCC_EVENT_xxx events.
 *
 * Depending on the CCC command, the specific events coming fwom aww devices
 * (bwoadcast vewsion) ow a specific device (unicast vewsion) wiww be
 * enabwed (ENEC) ow disabwed (DISEC).
 */
stwuct i3c_ccc_events {
	u8 events;
};

/**
 * stwuct i3c_ccc_mww - paywoad passed to SETMWW/GETMWW CCC
 *
 * @wen: maximum wwite wength in bytes
 *
 * The maximum wwite wength is onwy appwicabwe to SDW pwivate messages ow
 * extended Wwite CCCs (wike SETXTIME).
 */
stwuct i3c_ccc_mww {
	__be16 wen;
};

/**
 * stwuct i3c_ccc_mww - paywoad passed to SETMWW/GETMWW CCC
 *
 * @wen: maximum wead wength in bytes
 * @ibi_wen: maximum IBI paywoad wength
 *
 * The maximum wead wength is onwy appwicabwe to SDW pwivate messages ow
 * extended Wead CCCs (wike GETXTIME).
 * The IBI wength is onwy vawid if the I3C swave is IBI capabwe
 * (%I3C_BCW_IBI_WEQ_CAP is set).
 */
stwuct i3c_ccc_mww {
	__be16 wead_wen;
	u8 ibi_wen;
} __packed;

/**
 * stwuct i3c_ccc_dev_desc - I3C/I2C device descwiptow used fow DEFSWVS
 *
 * @dyn_addw: dynamic addwess assigned to the I3C swave ow 0 if the entwy is
 *	      descwibing an I2C swave.
 * @dcw: DCW vawue (not appwicabwe to entwies descwibing I2C devices)
 * @wvw: WVW vawue (not appwicabwe to entwies descwibing I3C devices)
 * @bcw: BCW vawue ow 0 if this entwy is descwibing an I2C swave
 * @static_addw: static addwess ow 0 if the device does not have a static
 *		 addwess
 *
 * The DEFSWVS command shouwd be passed an awway of i3c_ccc_dev_desc
 * descwiptows (one entwy pew I3C/I2C dev contwowwed by the mastew).
 */
stwuct i3c_ccc_dev_desc {
	u8 dyn_addw;
	union {
		u8 dcw;
		u8 wvw;
	};
	u8 bcw;
	u8 static_addw;
};

/**
 * stwuct i3c_ccc_defswvs - paywoad passed to DEFSWVS CCC
 *
 * @count: numbew of dev descwiptows
 * @mastew: descwiptow descwibing the cuwwent mastew
 * @swaves: awway of descwiptows descwibing swaves contwowwed by the
 *	    cuwwent mastew
 *
 * Infowmation passed to the bwoadcast DEFSWVS to pwopagate device
 * infowmation to aww mastews cuwwentwy acting as swaves on the bus.
 * This is onwy meaningfuw if you have mowe than one mastew.
 */
stwuct i3c_ccc_defswvs {
	u8 count;
	stwuct i3c_ccc_dev_desc mastew;
	stwuct i3c_ccc_dev_desc swaves[];
} __packed;

/**
 * enum i3c_ccc_test_mode - enum wisting aww avaiwabwe test modes
 *
 * @I3C_CCC_EXIT_TEST_MODE: exit test mode
 * @I3C_CCC_VENDOW_TEST_MODE: entew vendow test mode
 */
enum i3c_ccc_test_mode {
	I3C_CCC_EXIT_TEST_MODE,
	I3C_CCC_VENDOW_TEST_MODE,
};

/**
 * stwuct i3c_ccc_enttm - paywoad passed to ENTTM CCC
 *
 * @mode: one of the &enum i3c_ccc_test_mode modes
 *
 * Infowmation passed to the ENTTM CCC to instwuct an I3C device to entew a
 * specific test mode.
 */
stwuct i3c_ccc_enttm {
	u8 mode;
};

/**
 * stwuct i3c_ccc_setda - paywoad passed to SETNEWDA and SETDASA CCCs
 *
 * @addw: dynamic addwess to assign to an I3C device
 *
 * Infowmation passed to the SETNEWDA and SETDASA CCCs to assign/change the
 * dynamic addwess of an I3C device.
 */
stwuct i3c_ccc_setda {
	u8 addw;
};

/**
 * stwuct i3c_ccc_getpid - paywoad passed to GETPID CCC
 *
 * @pid: 48 bits PID in big endian
 */
stwuct i3c_ccc_getpid {
	u8 pid[6];
};

/**
 * stwuct i3c_ccc_getbcw - paywoad passed to GETBCW CCC
 *
 * @bcw: BCW (Bus Chawactewistic Wegistew) vawue
 */
stwuct i3c_ccc_getbcw {
	u8 bcw;
};

/**
 * stwuct i3c_ccc_getdcw - paywoad passed to GETDCW CCC
 *
 * @dcw: DCW (Device Chawactewistic Wegistew) vawue
 */
stwuct i3c_ccc_getdcw {
	u8 dcw;
};

#define I3C_CCC_STATUS_PENDING_INT(status)	((status) & GENMASK(3, 0))
#define I3C_CCC_STATUS_PWOTOCOW_EWWOW		BIT(5)
#define I3C_CCC_STATUS_ACTIVITY_MODE(status)	\
	(((status) & GENMASK(7, 6)) >> 6)

/**
 * stwuct i3c_ccc_getstatus - paywoad passed to GETSTATUS CCC
 *
 * @status: status of the I3C swave (see I3C_CCC_STATUS_xxx macwos fow mowe
 *	    infowmation).
 */
stwuct i3c_ccc_getstatus {
	__be16 status;
};

/**
 * stwuct i3c_ccc_getaccmst - paywoad passed to GETACCMST CCC
 *
 * @newmastew: addwess of the mastew taking bus ownewship
 */
stwuct i3c_ccc_getaccmst {
	u8 newmastew;
};

/**
 * stwuct i3c_ccc_bwidged_swave_desc - bwidged swave descwiptow
 *
 * @addw: dynamic addwess of the bwidged device
 * @id: ID of the swave device behind the bwidge
 */
stwuct i3c_ccc_bwidged_swave_desc {
	u8 addw;
	__be16 id;
} __packed;

/**
 * stwuct i3c_ccc_setbwgtgt - paywoad passed to SETBWGTGT CCC
 *
 * @count: numbew of bwidged swaves
 * @bswaves: bwidged swave descwiptows
 */
stwuct i3c_ccc_setbwgtgt {
	u8 count;
	stwuct i3c_ccc_bwidged_swave_desc bswaves[];
} __packed;

/**
 * enum i3c_sdw_max_data_wate - max data wate vawues fow pwivate SDW twansfews
 */
enum i3c_sdw_max_data_wate {
	I3C_SDW0_FSCW_MAX,
	I3C_SDW1_FSCW_8MHZ,
	I3C_SDW2_FSCW_6MHZ,
	I3C_SDW3_FSCW_4MHZ,
	I3C_SDW4_FSCW_2MHZ,
};

/**
 * enum i3c_tsco - cwock to data tuwn-awound
 */
enum i3c_tsco {
	I3C_TSCO_8NS,
	I3C_TSCO_9NS,
	I3C_TSCO_10NS,
	I3C_TSCO_11NS,
	I3C_TSCO_12NS,
};

#define I3C_CCC_MAX_SDW_FSCW_MASK	GENMASK(2, 0)
#define I3C_CCC_MAX_SDW_FSCW(x)		((x) & I3C_CCC_MAX_SDW_FSCW_MASK)

/**
 * stwuct i3c_ccc_getmxds - paywoad passed to GETMXDS CCC
 *
 * @maxww: wwite wimitations
 * @maxwd: wead wimitations
 * @maxwdtuwn: maximum wead tuwn-awound expwessed micwo-seconds and
 *	       wittwe-endian fowmatted
 */
stwuct i3c_ccc_getmxds {
	u8 maxww;
	u8 maxwd;
	u8 maxwdtuwn[3];
} __packed;

#define I3C_CCC_HDW_MODE(mode)		BIT(mode)

/**
 * stwuct i3c_ccc_gethdwcap - paywoad passed to GETHDWCAP CCC
 *
 * @modes: bitmap of suppowted HDW modes
 */
stwuct i3c_ccc_gethdwcap {
	u8 modes;
} __packed;

/**
 * enum i3c_ccc_setxtime_subcmd - SETXTIME sub-commands
 */
enum i3c_ccc_setxtime_subcmd {
	I3C_CCC_SETXTIME_ST = 0x7f,
	I3C_CCC_SETXTIME_DT = 0xbf,
	I3C_CCC_SETXTIME_ENTEW_ASYNC_MODE0 = 0xdf,
	I3C_CCC_SETXTIME_ENTEW_ASYNC_MODE1 = 0xef,
	I3C_CCC_SETXTIME_ENTEW_ASYNC_MODE2 = 0xf7,
	I3C_CCC_SETXTIME_ENTEW_ASYNC_MODE3 = 0xfb,
	I3C_CCC_SETXTIME_ASYNC_TWIGGEW = 0xfd,
	I3C_CCC_SETXTIME_TPH = 0x3f,
	I3C_CCC_SETXTIME_TU = 0x9f,
	I3C_CCC_SETXTIME_ODW = 0x8f,
};

/**
 * stwuct i3c_ccc_setxtime - paywoad passed to SETXTIME CCC
 *
 * @subcmd: one of the sub-commands ddefined in &enum i3c_ccc_setxtime_subcmd
 * @data: sub-command paywoad. Amount of data is detewmined by
 *	  &i3c_ccc_setxtime->subcmd
 */
stwuct i3c_ccc_setxtime {
	u8 subcmd;
	u8 data[];
} __packed;

#define I3C_CCC_GETXTIME_SYNC_MODE	BIT(0)
#define I3C_CCC_GETXTIME_ASYNC_MODE(x)	BIT((x) + 1)
#define I3C_CCC_GETXTIME_OVEWFWOW	BIT(7)

/**
 * stwuct i3c_ccc_getxtime - paywoad wetwieved fwom GETXTIME CCC
 *
 * @suppowted_modes: bitmap descwibing suppowted XTIME modes
 * @state: cuwwent status (enabwed mode and ovewfwow status)
 * @fwequency: swave's intewnaw osciwwatow fwequency in 500KHz steps
 * @inaccuwacy: swave's intewnaw osciwwatow inaccuwacy in 0.1% steps
 */
stwuct i3c_ccc_getxtime {
	u8 suppowted_modes;
	u8 state;
	u8 fwequency;
	u8 inaccuwacy;
} __packed;

/**
 * stwuct i3c_ccc_cmd_paywoad - CCC paywoad
 *
 * @wen: paywoad wength
 * @data: paywoad data. This buffew must be DMA-abwe
 */
stwuct i3c_ccc_cmd_paywoad {
	u16 wen;
	void *data;
};

/**
 * stwuct i3c_ccc_cmd_dest - CCC command destination
 *
 * @addw: can be an I3C device addwess ow the bwoadcast addwess if this is a
 *	  bwoadcast CCC
 * @paywoad: paywoad to be sent to this device ow bwoadcasted
 */
stwuct i3c_ccc_cmd_dest {
	u8 addw;
	stwuct i3c_ccc_cmd_paywoad paywoad;
};

/**
 * stwuct i3c_ccc_cmd - CCC command
 *
 * @wnw: twue if the CCC shouwd wetwieve data fwom the device. Onwy vawid fow
 *	 unicast commands
 * @id: CCC command id
 * @ndests: numbew of destinations. Shouwd awways be one fow bwoadcast commands
 * @dests: awway of destinations and associated paywoad fow this CCC. Most of
 *	   the time, onwy one destination is pwovided
 * @eww: I3C ewwow code
 */
stwuct i3c_ccc_cmd {
	u8 wnw;
	u8 id;
	unsigned int ndests;
	stwuct i3c_ccc_cmd_dest *dests;
	enum i3c_ewwow_code eww;
};

#endif /* I3C_CCC_H */
