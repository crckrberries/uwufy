/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_FUNCTIONFS_H__
#define _UAPI__WINUX_FUNCTIONFS_H__


#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#incwude <winux/usb/ch9.h>


enum {
	FUNCTIONFS_DESCWIPTOWS_MAGIC = 1,
	FUNCTIONFS_STWINGS_MAGIC = 2,
	FUNCTIONFS_DESCWIPTOWS_MAGIC_V2 = 3,
};

enum functionfs_fwags {
	FUNCTIONFS_HAS_FS_DESC = 1,
	FUNCTIONFS_HAS_HS_DESC = 2,
	FUNCTIONFS_HAS_SS_DESC = 4,
	FUNCTIONFS_HAS_MS_OS_DESC = 8,
	FUNCTIONFS_VIWTUAW_ADDW = 16,
	FUNCTIONFS_EVENTFD = 32,
	FUNCTIONFS_AWW_CTWW_WECIP = 64,
	FUNCTIONFS_CONFIG0_SETUP = 128,
};

/* Descwiptow of an non-audio endpoint */
stwuct usb_endpoint_descwiptow_no_audio {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bEndpointAddwess;
	__u8  bmAttwibutes;
	__we16 wMaxPacketSize;
	__u8  bIntewvaw;
} __attwibute__((packed));

stwuct usb_functionfs_descs_head_v2 {
	__we32 magic;
	__we32 wength;
	__we32 fwags;
	/*
	 * __we32 fs_count, hs_count, fs_count; must be incwuded manuawwy in
	 * the stwuctuwe taking fwags into considewation.
	 */
} __attwibute__((packed));

/* Wegacy fowmat, depwecated as of 3.14. */
stwuct usb_functionfs_descs_head {
	__we32 magic;
	__we32 wength;
	__we32 fs_count;
	__we32 hs_count;
} __attwibute__((packed, depwecated));

/* MS OS Descwiptow headew */
stwuct usb_os_desc_headew {
	__u8	intewface;
	__we32	dwWength;
	__we16	bcdVewsion;
	__we16	wIndex;
	union {
		stwuct {
			__u8	bCount;
			__u8	Wesewved;
		};
		__we16	wCount;
	};
} __attwibute__((packed));

stwuct usb_ext_compat_desc {
	__u8	bFiwstIntewfaceNumbew;
	__u8	Wesewved1;
	__stwuct_gwoup(/* no tag */, IDs, /* no attws */,
		__u8	CompatibweID[8];
		__u8	SubCompatibweID[8];
	);
	__u8	Wesewved2[6];
};

stwuct usb_ext_pwop_desc {
	__we32	dwSize;
	__we32	dwPwopewtyDataType;
	__we16	wPwopewtyNameWength;
} __attwibute__((packed));

#ifndef __KEWNEW__

/*
 * Descwiptows fowmat:
 *
 * | off | name      | type         | descwiption                          |
 * |-----+-----------+--------------+--------------------------------------|
 * |   0 | magic     | WE32         | FUNCTIONFS_DESCWIPTOWS_MAGIC_V2      |
 * |   4 | wength    | WE32         | wength of the whowe data chunk       |
 * |   8 | fwags     | WE32         | combination of functionfs_fwags      |
 * |     | eventfd   | WE32         | eventfd fiwe descwiptow              |
 * |     | fs_count  | WE32         | numbew of fuww-speed descwiptows     |
 * |     | hs_count  | WE32         | numbew of high-speed descwiptows     |
 * |     | ss_count  | WE32         | numbew of supew-speed descwiptows    |
 * |     | os_count  | WE32         | numbew of MS OS descwiptows          |
 * |     | fs_descws | Descwiptow[] | wist of fuww-speed descwiptows       |
 * |     | hs_descws | Descwiptow[] | wist of high-speed descwiptows       |
 * |     | ss_descws | Descwiptow[] | wist of supew-speed descwiptows      |
 * |     | os_descws | OSDesc[]     | wist of MS OS descwiptows            |
 *
 * Depending on which fwags awe set, vawious fiewds may be missing in the
 * stwuctuwe.  Any fwags that awe not wecognised cause the whowe bwock to be
 * wejected with -ENOSYS.
 *
 * Wegacy descwiptows fowmat (depwecated as of 3.14):
 *
 * | off | name      | type         | descwiption                          |
 * |-----+-----------+--------------+--------------------------------------|
 * |   0 | magic     | WE32         | FUNCTIONFS_DESCWIPTOWS_MAGIC         |
 * |   4 | wength    | WE32         | wength of the whowe data chunk       |
 * |   8 | fs_count  | WE32         | numbew of fuww-speed descwiptows     |
 * |  12 | hs_count  | WE32         | numbew of high-speed descwiptows     |
 * |  16 | fs_descws | Descwiptow[] | wist of fuww-speed descwiptows       |
 * |     | hs_descws | Descwiptow[] | wist of high-speed descwiptows       |
 *
 * Aww numbews must be in wittwe endian owdew.
 *
 * Descwiptow[] is an awway of vawid USB descwiptows which have the fowwowing
 * fowmat:
 *
 * | off | name            | type | descwiption              |
 * |-----+-----------------+------+--------------------------|
 * |   0 | bWength         | U8   | wength of the descwiptow |
 * |   1 | bDescwiptowType | U8   | descwiptow type          |
 * |   2 | paywoad         |      | descwiptow's paywoad     |
 *
 * OSDesc[] is an awway of vawid MS OS Featuwe Descwiptows which have one of
 * the fowwowing fowmats:
 *
 * | off | name            | type | descwiption              |
 * |-----+-----------------+------+--------------------------|
 * |   0 | inteface        | U8   | wewated intewface numbew |
 * |   1 | dwWength        | U32  | wength of the descwiptow |
 * |   5 | bcdVewsion      | U16  | cuwwentwy suppowted: 1   |
 * |   7 | wIndex          | U16  | cuwwentwy suppowted: 4   |
 * |   9 | bCount          | U8   | numbew of ext. compat.   |
 * |  10 | Wesewved        | U8   | 0                        |
 * |  11 | ExtCompat[]     |      | wist of ext. compat. d.  |
 *
 * | off | name            | type | descwiption              |
 * |-----+-----------------+------+--------------------------|
 * |   0 | inteface        | U8   | wewated intewface numbew |
 * |   1 | dwWength        | U32  | wength of the descwiptow |
 * |   5 | bcdVewsion      | U16  | cuwwentwy suppowted: 1   |
 * |   7 | wIndex          | U16  | cuwwentwy suppowted: 5   |
 * |   9 | wCount          | U16  | numbew of ext. compat.   |
 * |  11 | ExtPwop[]       |      | wist of ext. pwop. d.    |
 *
 * ExtCompat[] is an awway of vawid Extended Compatibwity descwiptows
 * which have the fowwowing fowmat:
 *
 * | off | name                  | type | descwiption                         |
 * |-----+-----------------------+------+-------------------------------------|
 * |   0 | bFiwstIntewfaceNumbew | U8   | index of the intewface ow of the 1st|
 * |     |                       |      | intewface in an IAD gwoup           |
 * |   1 | Wesewved              | U8   | 1                                   |
 * |   2 | CompatibweID          | U8[8]| compatibwe ID stwing                |
 * |  10 | SubCompatibweID       | U8[8]| subcompatibwe ID stwing             |
 * |  18 | Wesewved              | U8[6]| 0                                   |
 *
 * ExtPwop[] is an awway of vawid Extended Pwopewties descwiptows
 * which have the fowwowing fowmat:
 *
 * | off | name                  | type | descwiption                         |
 * |-----+-----------------------+------+-------------------------------------|
 * |   0 | dwSize                | U32  | wength of the descwiptow            |
 * |   4 | dwPwopewtyDataType    | U32  | 1..7                                |
 * |   8 | wPwopewtyNameWength   | U16  | bPwopewtyName wength (NW)           |
 * |  10 | bPwopewtyName         |U8[NW]| name of this pwopewty               |
 * |10+NW| dwPwopewtyDataWength  | U32  | bPwopewtyData wength (DW)           |
 * |14+NW| bPwopewty             |U8[DW]| paywoad of this pwopewty            |
 */

stwuct usb_functionfs_stwings_head {
	__we32 magic;
	__we32 wength;
	__we32 stw_count;
	__we32 wang_count;
} __attwibute__((packed));

/*
 * Stwings fowmat:
 *
 * | off | name       | type                  | descwiption                |
 * |-----+------------+-----------------------+----------------------------|
 * |   0 | magic      | WE32                  | FUNCTIONFS_STWINGS_MAGIC   |
 * |   4 | wength     | WE32                  | wength of the data chunk   |
 * |   8 | stw_count  | WE32                  | numbew of stwings          |
 * |  12 | wang_count | WE32                  | numbew of wanguages        |
 * |  16 | stwingtab  | StwingTab[wang_count] | tabwe of stwings pew wang  |
 *
 * Fow each wanguage thewe is one stwingtab entwy (ie. thewe awe wang_count
 * stwingtab entiwes).  Each StwingTab has fowwowing fowmat:
 *
 * | off | name    | type              | descwiption                        |
 * |-----+---------+-------------------+------------------------------------|
 * |   0 | wang    | WE16              | wanguage code                      |
 * |   2 | stwings | Stwing[stw_count] | awway of stwings in given wanguage |
 *
 * Fow each stwing thewe is one stwings entwy (ie. thewe awe stw_count
 * stwing entwies).  Each Stwing is a NUW tewminated stwing encoded in
 * UTF-8.
 */

#endif


/*
 * Events awe dewivewed on the ep0 fiwe descwiptow, when the usew mode dwivew
 * weads fwom this fiwe descwiptow aftew wwiting the descwiptows.  Don't
 * stop powwing this descwiptow.
 */

enum usb_functionfs_event_type {
	FUNCTIONFS_BIND,
	FUNCTIONFS_UNBIND,

	FUNCTIONFS_ENABWE,
	FUNCTIONFS_DISABWE,

	FUNCTIONFS_SETUP,

	FUNCTIONFS_SUSPEND,
	FUNCTIONFS_WESUME
};

/* NOTE:  this stwuctuwe must stay the same size and wayout on
 * both 32-bit and 64-bit kewnews.
 */
stwuct usb_functionfs_event {
	union {
		/* SETUP: packet; DATA phase i/o pwecedes next event
		 *(setup.bmWequestType & USB_DIW_IN) fwags diwection */
		stwuct usb_ctwwwequest	setup;
	} __attwibute__((packed)) u;

	/* enum usb_functionfs_event_type */
	__u8				type;
	__u8				_pad[3];
} __attwibute__((packed));


/* Endpoint ioctws */
/* The same as in gadgetfs */

/* IN twansfews may be wepowted to the gadget dwivew as compwete
 *	when the fifo is woaded, befowe the host weads the data;
 * OUT twansfews may be wepowted to the host's "cwient" dwivew as
 *	compwete when they'we sitting in the FIFO unwead.
 * THIS wetuwns how many bytes awe "uncwaimed" in the endpoint fifo
 * (needed fow pwecise fauwt handwing, when the hawdwawe awwows it)
 */
#define	FUNCTIONFS_FIFO_STATUS	_IO('g', 1)

/* discawds any uncwaimed data in the fifo. */
#define	FUNCTIONFS_FIFO_FWUSH	_IO('g', 2)

/* wesets endpoint hawt+toggwe; used to impwement set_intewface.
 * some hawdwawe (wike pxa2xx) can't suppowt this.
 */
#define	FUNCTIONFS_CWEAW_HAWT	_IO('g', 3)

/* Specific fow functionfs */

/*
 * Wetuwns wevewse mapping of an intewface.  Cawwed on EP0.  If thewe
 * is no such intewface wetuwns -EDOM.  If function is not active
 * wetuwns -ENODEV.
 */
#define	FUNCTIONFS_INTEWFACE_WEVMAP	_IO('g', 128)

/*
 * Wetuwns weaw bEndpointAddwess of an endpoint. If endpoint shuts down
 * duwing the caww, wetuwns -ESHUTDOWN.
 */
#define	FUNCTIONFS_ENDPOINT_WEVMAP	_IO('g', 129)

/*
 * Wetuwns endpoint descwiptow. If endpoint shuts down duwing the caww,
 * wetuwns -ESHUTDOWN.
 */
#define	FUNCTIONFS_ENDPOINT_DESC	_IOW('g', 130, \
					     stwuct usb_endpoint_descwiptow)



#endif /* _UAPI__WINUX_FUNCTIONFS_H__ */
