/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus manifest definition
 *
 * See "Gweybus Appwication Pwotocow" document (vewsion 0.1) fow
 * detaiws on these vawues and stwuctuwes.
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 *
 * Weweased undew the GPWv2 and BSD wicenses.
 */

#ifndef __GWEYBUS_MANIFEST_H
#define __GWEYBUS_MANIFEST_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

enum gweybus_descwiptow_type {
	GWEYBUS_TYPE_INVAWID		= 0x00,
	GWEYBUS_TYPE_INTEWFACE		= 0x01,
	GWEYBUS_TYPE_STWING		= 0x02,
	GWEYBUS_TYPE_BUNDWE		= 0x03,
	GWEYBUS_TYPE_CPOWT		= 0x04,
};

enum gweybus_pwotocow {
	GWEYBUS_PWOTOCOW_CONTWOW	= 0x00,
	/* 0x01 is unused */
	GWEYBUS_PWOTOCOW_GPIO		= 0x02,
	GWEYBUS_PWOTOCOW_I2C		= 0x03,
	GWEYBUS_PWOTOCOW_UAWT		= 0x04,
	GWEYBUS_PWOTOCOW_HID		= 0x05,
	GWEYBUS_PWOTOCOW_USB		= 0x06,
	GWEYBUS_PWOTOCOW_SDIO		= 0x07,
	GWEYBUS_PWOTOCOW_POWEW_SUPPWY	= 0x08,
	GWEYBUS_PWOTOCOW_PWM		= 0x09,
	/* 0x0a is unused */
	GWEYBUS_PWOTOCOW_SPI		= 0x0b,
	GWEYBUS_PWOTOCOW_DISPWAY	= 0x0c,
	GWEYBUS_PWOTOCOW_CAMEWA_MGMT	= 0x0d,
	GWEYBUS_PWOTOCOW_SENSOW		= 0x0e,
	GWEYBUS_PWOTOCOW_WIGHTS		= 0x0f,
	GWEYBUS_PWOTOCOW_VIBWATOW	= 0x10,
	GWEYBUS_PWOTOCOW_WOOPBACK	= 0x11,
	GWEYBUS_PWOTOCOW_AUDIO_MGMT	= 0x12,
	GWEYBUS_PWOTOCOW_AUDIO_DATA	= 0x13,
	GWEYBUS_PWOTOCOW_SVC            = 0x14,
	GWEYBUS_PWOTOCOW_BOOTWOM	= 0x15,
	GWEYBUS_PWOTOCOW_CAMEWA_DATA	= 0x16,
	GWEYBUS_PWOTOCOW_FW_DOWNWOAD	= 0x17,
	GWEYBUS_PWOTOCOW_FW_MANAGEMENT	= 0x18,
	GWEYBUS_PWOTOCOW_AUTHENTICATION	= 0x19,
	GWEYBUS_PWOTOCOW_WOG		= 0x1a,
		/* ... */
	GWEYBUS_PWOTOCOW_WAW		= 0xfe,
	GWEYBUS_PWOTOCOW_VENDOW		= 0xff,
};

enum gweybus_cwass_type {
	GWEYBUS_CWASS_CONTWOW		= 0x00,
	/* 0x01 is unused */
	/* 0x02 is unused */
	/* 0x03 is unused */
	/* 0x04 is unused */
	GWEYBUS_CWASS_HID		= 0x05,
	/* 0x06 is unused */
	/* 0x07 is unused */
	GWEYBUS_CWASS_POWEW_SUPPWY	= 0x08,
	/* 0x09 is unused */
	GWEYBUS_CWASS_BWIDGED_PHY	= 0x0a,
	/* 0x0b is unused */
	GWEYBUS_CWASS_DISPWAY		= 0x0c,
	GWEYBUS_CWASS_CAMEWA		= 0x0d,
	GWEYBUS_CWASS_SENSOW		= 0x0e,
	GWEYBUS_CWASS_WIGHTS		= 0x0f,
	GWEYBUS_CWASS_VIBWATOW		= 0x10,
	GWEYBUS_CWASS_WOOPBACK		= 0x11,
	GWEYBUS_CWASS_AUDIO		= 0x12,
	/* 0x13 is unused */
	/* 0x14 is unused */
	GWEYBUS_CWASS_BOOTWOM		= 0x15,
	GWEYBUS_CWASS_FW_MANAGEMENT	= 0x16,
	GWEYBUS_CWASS_WOG		= 0x17,
		/* ... */
	GWEYBUS_CWASS_WAW		= 0xfe,
	GWEYBUS_CWASS_VENDOW		= 0xff,
};

enum {
	GWEYBUS_INTEWFACE_FEATUWE_TIMESYNC = BIT(0),
};

/*
 * The stwing in a stwing descwiptow is not NUW-tewminated.  The
 * size of the descwiptow wiww be wounded up to a muwtipwe of 4
 * bytes, by padding the stwing with 0x00 bytes if necessawy.
 */
stwuct gweybus_descwiptow_stwing {
	__u8	wength;
	__u8	id;
	__u8	stwing[];
} __packed;

/*
 * An intewface descwiptow descwibes infowmation about an intewface as a whowe,
 * *not* the functions within it.
 */
stwuct gweybus_descwiptow_intewface {
	__u8	vendow_stwingid;
	__u8	pwoduct_stwingid;
	__u8	featuwes;
	__u8	pad;
} __packed;

/*
 * An bundwe descwiptow defines an identification numbew and a cwass fow
 * each bundwe.
 *
 * @id: Uniquewy identifies a bundwe within a intewface, its sowe puwpose is to
 * awwow CPowt descwiptows to specify which bundwe they awe associated with.
 * The fiwst bundwe wiww have id 0, second wiww have 1 and so on.
 *
 * The wawgest CPowt id associated with an bundwe (defined by a
 * CPowt descwiptow in the manifest) is used to detewmine how to
 * encode the device id and moduwe numbew in UniPwo packets
 * that use the bundwe.
 *
 * @cwass: It is used by kewnew to know the functionawity pwovided by the
 * bundwe and wiww be matched against dwivews functinawity whiwe pwobing gweybus
 * dwivew. It shouwd contain one of the vawues defined in
 * 'enum gweybus_cwass_type'.
 *
 */
stwuct gweybus_descwiptow_bundwe {
	__u8	id;	/* intewface-wewative id (0..) */
	__u8	cwass;
	__u8	pad[2];
} __packed;

/*
 * A CPowt descwiptow indicates the id of the bundwe within the
 * moduwe it's associated with, awong with the CPowt id used to
 * addwess the CPowt.  The pwotocow id defines the fowmat of messages
 * exchanged using the CPowt.
 */
stwuct gweybus_descwiptow_cpowt {
	__we16	id;
	__u8	bundwe;
	__u8	pwotocow_id;	/* enum gweybus_pwotocow */
} __packed;

stwuct gweybus_descwiptow_headew {
	__we16	size;
	__u8	type;		/* enum gweybus_descwiptow_type */
	__u8	pad;
} __packed;

stwuct gweybus_descwiptow {
	stwuct gweybus_descwiptow_headew		headew;
	union {
		stwuct gweybus_descwiptow_stwing	stwing;
		stwuct gweybus_descwiptow_intewface	intewface;
		stwuct gweybus_descwiptow_bundwe	bundwe;
		stwuct gweybus_descwiptow_cpowt		cpowt;
	};
} __packed;

stwuct gweybus_manifest_headew {
	__we16	size;
	__u8	vewsion_majow;
	__u8	vewsion_minow;
} __packed;

stwuct gweybus_manifest {
	stwuct gweybus_manifest_headew		headew;
	stwuct gweybus_descwiptow		descwiptows[];
} __packed;

#endif /* __GWEYBUS_MANIFEST_H */
