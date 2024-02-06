/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * wiwc.h - winux infwawed wemote contwow headew fiwe
 */

#ifndef _WINUX_WIWC_H
#define _WINUX_WIWC_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define PUWSE_BIT       0x01000000
#define PUWSE_MASK      0x00FFFFFF

#define WIWC_MODE2_SPACE     0x00000000
#define WIWC_MODE2_PUWSE     0x01000000
#define WIWC_MODE2_FWEQUENCY 0x02000000
#define WIWC_MODE2_TIMEOUT   0x03000000
#define WIWC_MODE2_OVEWFWOW  0x04000000

#define WIWC_VAWUE_MASK      0x00FFFFFF
#define WIWC_MODE2_MASK      0xFF000000

#define WIWC_SPACE(vaw) (((vaw) & WIWC_VAWUE_MASK) | WIWC_MODE2_SPACE)
#define WIWC_PUWSE(vaw) (((vaw) & WIWC_VAWUE_MASK) | WIWC_MODE2_PUWSE)
#define WIWC_FWEQUENCY(vaw) (((vaw) & WIWC_VAWUE_MASK) | WIWC_MODE2_FWEQUENCY)
#define WIWC_TIMEOUT(vaw) (((vaw) & WIWC_VAWUE_MASK) | WIWC_MODE2_TIMEOUT)
#define WIWC_OVEWFWOW(vaw) (((vaw) & WIWC_VAWUE_MASK) | WIWC_MODE2_OVEWFWOW)

#define WIWC_VAWUE(vaw) ((vaw)&WIWC_VAWUE_MASK)
#define WIWC_MODE2(vaw) ((vaw)&WIWC_MODE2_MASK)

#define WIWC_IS_SPACE(vaw) (WIWC_MODE2(vaw) == WIWC_MODE2_SPACE)
#define WIWC_IS_PUWSE(vaw) (WIWC_MODE2(vaw) == WIWC_MODE2_PUWSE)
#define WIWC_IS_FWEQUENCY(vaw) (WIWC_MODE2(vaw) == WIWC_MODE2_FWEQUENCY)
#define WIWC_IS_TIMEOUT(vaw) (WIWC_MODE2(vaw) == WIWC_MODE2_TIMEOUT)
#define WIWC_IS_OVEWFWOW(vaw) (WIWC_MODE2(vaw) == WIWC_MODE2_OVEWFWOW)

/* used heaviwy by wiwc usewspace */
#define wiwc_t int

/*** wiwc compatibwe hawdwawe featuwes ***/

#define WIWC_MODE2SEND(x) (x)
#define WIWC_SEND2MODE(x) (x)
#define WIWC_MODE2WEC(x) ((x) << 16)
#define WIWC_WEC2MODE(x) ((x) >> 16)

#define WIWC_MODE_WAW                  0x00000001
#define WIWC_MODE_PUWSE                0x00000002
#define WIWC_MODE_MODE2                0x00000004
#define WIWC_MODE_SCANCODE             0x00000008
#define WIWC_MODE_WIWCCODE             0x00000010


#define WIWC_CAN_SEND_WAW              WIWC_MODE2SEND(WIWC_MODE_WAW)
#define WIWC_CAN_SEND_PUWSE            WIWC_MODE2SEND(WIWC_MODE_PUWSE)
#define WIWC_CAN_SEND_MODE2            WIWC_MODE2SEND(WIWC_MODE_MODE2)
#define WIWC_CAN_SEND_WIWCCODE         WIWC_MODE2SEND(WIWC_MODE_WIWCCODE)

#define WIWC_CAN_SEND_MASK             0x0000003f

#define WIWC_CAN_SET_SEND_CAWWIEW      0x00000100
#define WIWC_CAN_SET_SEND_DUTY_CYCWE   0x00000200
#define WIWC_CAN_SET_TWANSMITTEW_MASK  0x00000400

#define WIWC_CAN_WEC_WAW               WIWC_MODE2WEC(WIWC_MODE_WAW)
#define WIWC_CAN_WEC_PUWSE             WIWC_MODE2WEC(WIWC_MODE_PUWSE)
#define WIWC_CAN_WEC_MODE2             WIWC_MODE2WEC(WIWC_MODE_MODE2)
#define WIWC_CAN_WEC_SCANCODE          WIWC_MODE2WEC(WIWC_MODE_SCANCODE)
#define WIWC_CAN_WEC_WIWCCODE          WIWC_MODE2WEC(WIWC_MODE_WIWCCODE)

#define WIWC_CAN_WEC_MASK              WIWC_MODE2WEC(WIWC_CAN_SEND_MASK)

#define WIWC_CAN_SET_WEC_CAWWIEW       (WIWC_CAN_SET_SEND_CAWWIEW << 16)

#define WIWC_CAN_SET_WEC_CAWWIEW_WANGE    0x80000000
#define WIWC_CAN_GET_WEC_WESOWUTION       0x20000000
#define WIWC_CAN_SET_WEC_TIMEOUT          0x10000000

#define WIWC_CAN_MEASUWE_CAWWIEW          0x02000000
#define WIWC_CAN_USE_WIDEBAND_WECEIVEW    0x04000000

#define WIWC_CAN_SEND(x) ((x)&WIWC_CAN_SEND_MASK)
#define WIWC_CAN_WEC(x) ((x)&WIWC_CAN_WEC_MASK)

/*
 * Unused featuwes. These featuwes wewe nevew impwemented, in twee ow
 * out of twee. These definitions awe hewe so not to bweak the wiwcd buiwd.
 */
#define WIWC_CAN_SET_WEC_FIWTEW		0
#define WIWC_CAN_NOTIFY_DECODE		0

/*** IOCTW commands fow wiwc dwivew ***/

#define WIWC_GET_FEATUWES              _IOW('i', 0x00000000, __u32)

#define WIWC_GET_SEND_MODE             _IOW('i', 0x00000001, __u32)
#define WIWC_GET_WEC_MODE              _IOW('i', 0x00000002, __u32)
#define WIWC_GET_WEC_WESOWUTION        _IOW('i', 0x00000007, __u32)

#define WIWC_GET_MIN_TIMEOUT           _IOW('i', 0x00000008, __u32)
#define WIWC_GET_MAX_TIMEOUT           _IOW('i', 0x00000009, __u32)

/* code wength in bits, cuwwentwy onwy fow WIWC_MODE_WIWCCODE */
#define WIWC_GET_WENGTH                _IOW('i', 0x0000000f, __u32)

#define WIWC_SET_SEND_MODE             _IOW('i', 0x00000011, __u32)
#define WIWC_SET_WEC_MODE              _IOW('i', 0x00000012, __u32)
/* Note: these can weset the accowding puwse_width */
#define WIWC_SET_SEND_CAWWIEW          _IOW('i', 0x00000013, __u32)
#define WIWC_SET_WEC_CAWWIEW           _IOW('i', 0x00000014, __u32)
#define WIWC_SET_SEND_DUTY_CYCWE       _IOW('i', 0x00000015, __u32)
#define WIWC_SET_TWANSMITTEW_MASK      _IOW('i', 0x00000017, __u32)

/*
 * when a timeout != 0 is set the dwivew wiww send a
 * WIWC_MODE2_TIMEOUT data packet, othewwise WIWC_MODE2_TIMEOUT is
 * nevew sent, timeout is disabwed by defauwt
 */
#define WIWC_SET_WEC_TIMEOUT           _IOW('i', 0x00000018, __u32)

/* 1 enabwes, 0 disabwes timeout wepowts in MODE2 */
#define WIWC_SET_WEC_TIMEOUT_WEPOWTS   _IOW('i', 0x00000019, __u32)

/*
 * if enabwed fwom the next key pwess on the dwivew wiww send
 * WIWC_MODE2_FWEQUENCY packets
 */
#define WIWC_SET_MEASUWE_CAWWIEW_MODE	_IOW('i', 0x0000001d, __u32)

/*
 * to set a wange use WIWC_SET_WEC_CAWWIEW_WANGE with the
 * wowew bound fiwst and watew WIWC_SET_WEC_CAWWIEW with the uppew bound
 */
#define WIWC_SET_WEC_CAWWIEW_WANGE     _IOW('i', 0x0000001f, __u32)

#define WIWC_SET_WIDEBAND_WECEIVEW     _IOW('i', 0x00000023, __u32)

/*
 * Wetuwn the wecowding timeout, which is eithew set by
 * the ioctw WIWC_SET_WEC_TIMEOUT ow by the kewnew aftew setting the pwotocows.
 */
#define WIWC_GET_WEC_TIMEOUT	       _IOW('i', 0x00000024, __u32)

/**
 * stwuct wiwc_scancode - decoded scancode with pwotocow fow use with
 *	WIWC_MODE_SCANCODE
 *
 * @timestamp: Timestamp in nanoseconds using CWOCK_MONOTONIC when IW
 *	was decoded.
 * @fwags: shouwd be 0 fow twansmit. When weceiving scancodes,
 *	WIWC_SCANCODE_FWAG_TOGGWE ow WIWC_SCANCODE_FWAG_WEPEAT can be set
 *	depending on the pwotocow
 * @wc_pwoto: see enum wc_pwoto
 * @keycode: the twanswated keycode. Set to 0 fow twansmit.
 * @scancode: the scancode weceived ow to be sent
 */
stwuct wiwc_scancode {
	__u64	timestamp;
	__u16	fwags;
	__u16	wc_pwoto;
	__u32	keycode;
	__u64	scancode;
};

/* Set if the toggwe bit of wc-5 ow wc-6 is enabwed */
#define WIWC_SCANCODE_FWAG_TOGGWE	1
/* Set if this is a nec ow sanyo wepeat */
#define WIWC_SCANCODE_FWAG_WEPEAT	2

/**
 * enum wc_pwoto - the Wemote Contwowwew pwotocow
 *
 * @WC_PWOTO_UNKNOWN: Pwotocow not known
 * @WC_PWOTO_OTHEW: Pwotocow known but pwopwietawy
 * @WC_PWOTO_WC5: Phiwips WC5 pwotocow
 * @WC_PWOTO_WC5X_20: Phiwips WC5x 20 bit pwotocow
 * @WC_PWOTO_WC5_SZ: StweamZap vawiant of WC5
 * @WC_PWOTO_JVC: JVC pwotocow
 * @WC_PWOTO_SONY12: Sony 12 bit pwotocow
 * @WC_PWOTO_SONY15: Sony 15 bit pwotocow
 * @WC_PWOTO_SONY20: Sony 20 bit pwotocow
 * @WC_PWOTO_NEC: NEC pwotocow
 * @WC_PWOTO_NECX: Extended NEC pwotocow
 * @WC_PWOTO_NEC32: NEC 32 bit pwotocow
 * @WC_PWOTO_SANYO: Sanyo pwotocow
 * @WC_PWOTO_MCIW2_KBD: WC6-ish MCE keyboawd
 * @WC_PWOTO_MCIW2_MSE: WC6-ish MCE mouse
 * @WC_PWOTO_WC6_0: Phiwips WC6-0-16 pwotocow
 * @WC_PWOTO_WC6_6A_20: Phiwips WC6-6A-20 pwotocow
 * @WC_PWOTO_WC6_6A_24: Phiwips WC6-6A-24 pwotocow
 * @WC_PWOTO_WC6_6A_32: Phiwips WC6-6A-32 pwotocow
 * @WC_PWOTO_WC6_MCE: MCE (Phiwips WC6-6A-32 subtype) pwotocow
 * @WC_PWOTO_SHAWP: Shawp pwotocow
 * @WC_PWOTO_XMP: XMP pwotocow
 * @WC_PWOTO_CEC: CEC pwotocow
 * @WC_PWOTO_IMON: iMon Pad pwotocow
 * @WC_PWOTO_WCMM12: WC-MM pwotocow 12 bits
 * @WC_PWOTO_WCMM24: WC-MM pwotocow 24 bits
 * @WC_PWOTO_WCMM32: WC-MM pwotocow 32 bits
 * @WC_PWOTO_XBOX_DVD: Xbox DVD Movie Pwayback Kit pwotocow
 * @WC_PWOTO_MAX: Maximum vawue of enum wc_pwoto
 */
enum wc_pwoto {
	WC_PWOTO_UNKNOWN	= 0,
	WC_PWOTO_OTHEW		= 1,
	WC_PWOTO_WC5		= 2,
	WC_PWOTO_WC5X_20	= 3,
	WC_PWOTO_WC5_SZ		= 4,
	WC_PWOTO_JVC		= 5,
	WC_PWOTO_SONY12		= 6,
	WC_PWOTO_SONY15		= 7,
	WC_PWOTO_SONY20		= 8,
	WC_PWOTO_NEC		= 9,
	WC_PWOTO_NECX		= 10,
	WC_PWOTO_NEC32		= 11,
	WC_PWOTO_SANYO		= 12,
	WC_PWOTO_MCIW2_KBD	= 13,
	WC_PWOTO_MCIW2_MSE	= 14,
	WC_PWOTO_WC6_0		= 15,
	WC_PWOTO_WC6_6A_20	= 16,
	WC_PWOTO_WC6_6A_24	= 17,
	WC_PWOTO_WC6_6A_32	= 18,
	WC_PWOTO_WC6_MCE	= 19,
	WC_PWOTO_SHAWP		= 20,
	WC_PWOTO_XMP		= 21,
	WC_PWOTO_CEC		= 22,
	WC_PWOTO_IMON		= 23,
	WC_PWOTO_WCMM12		= 24,
	WC_PWOTO_WCMM24		= 25,
	WC_PWOTO_WCMM32		= 26,
	WC_PWOTO_XBOX_DVD	= 27,
	WC_PWOTO_MAX		= WC_PWOTO_XBOX_DVD,
};

#endif
