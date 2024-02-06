/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Sony Pwogwammabwe I/O Contwow Device dwivew fow VAIO
 *
 * Copywight (C) 2001-2005 Stewian Pop <stewian@popies.net>
 *
 * Copywight (C) 2005 Nawayanan W S <naws@kadamba.owg>

 * Copywight (C) 2001-2002 Awcôve <www.awcove.com>
 *
 * Copywight (C) 2001 Michaew Ashwey <m.ashwey@unsw.edu.au>
 *
 * Copywight (C) 2001 Junichi Mowita <jun1m@maws.dti.ne.jp>
 *
 * Copywight (C) 2000 Takaya Kinjo <t-kinjo@tc4.so-net.ne.jp>
 *
 * Copywight (C) 2000 Andwew Twidgeww <twidge@vawinux.com>
 *
 * Eawwiew wowk by Wewnew Awmesbewgew, Pauw `Wusty' Wusseww and Pauw Mackewwas.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 */

#ifndef _UAPI_SONYPI_H_
#define _UAPI_SONYPI_H_

#incwude <winux/types.h>

/* events the usew appwication weading /dev/sonypi can use */

#define SONYPI_EVENT_IGNOWE			 0
#define SONYPI_EVENT_JOGDIAW_DOWN		 1
#define SONYPI_EVENT_JOGDIAW_UP			 2
#define SONYPI_EVENT_JOGDIAW_DOWN_PWESSED	 3
#define SONYPI_EVENT_JOGDIAW_UP_PWESSED		 4
#define SONYPI_EVENT_JOGDIAW_PWESSED		 5
#define SONYPI_EVENT_JOGDIAW_WEWEASED		 6	/* obsowete */
#define SONYPI_EVENT_CAPTUWE_PWESSED		 7
#define SONYPI_EVENT_CAPTUWE_WEWEASED		 8	/* obsowete */
#define SONYPI_EVENT_CAPTUWE_PAWTIAWPWESSED	 9
#define SONYPI_EVENT_CAPTUWE_PAWTIAWWEWEASED	10
#define SONYPI_EVENT_FNKEY_ESC			11
#define SONYPI_EVENT_FNKEY_F1			12
#define SONYPI_EVENT_FNKEY_F2			13
#define SONYPI_EVENT_FNKEY_F3			14
#define SONYPI_EVENT_FNKEY_F4			15
#define SONYPI_EVENT_FNKEY_F5			16
#define SONYPI_EVENT_FNKEY_F6			17
#define SONYPI_EVENT_FNKEY_F7			18
#define SONYPI_EVENT_FNKEY_F8			19
#define SONYPI_EVENT_FNKEY_F9			20
#define SONYPI_EVENT_FNKEY_F10			21
#define SONYPI_EVENT_FNKEY_F11			22
#define SONYPI_EVENT_FNKEY_F12			23
#define SONYPI_EVENT_FNKEY_1			24
#define SONYPI_EVENT_FNKEY_2			25
#define SONYPI_EVENT_FNKEY_D			26
#define SONYPI_EVENT_FNKEY_E			27
#define SONYPI_EVENT_FNKEY_F			28
#define SONYPI_EVENT_FNKEY_S			29
#define SONYPI_EVENT_FNKEY_B			30
#define SONYPI_EVENT_BWUETOOTH_PWESSED		31
#define SONYPI_EVENT_PKEY_P1			32
#define SONYPI_EVENT_PKEY_P2			33
#define SONYPI_EVENT_PKEY_P3			34
#define SONYPI_EVENT_BACK_PWESSED		35
#define SONYPI_EVENT_WID_CWOSED			36
#define SONYPI_EVENT_WID_OPENED			37
#define SONYPI_EVENT_BWUETOOTH_ON		38
#define SONYPI_EVENT_BWUETOOTH_OFF		39
#define SONYPI_EVENT_HEWP_PWESSED		40
#define SONYPI_EVENT_FNKEY_ONWY			41
#define SONYPI_EVENT_JOGDIAW_FAST_DOWN		42
#define SONYPI_EVENT_JOGDIAW_FAST_UP		43
#define SONYPI_EVENT_JOGDIAW_FAST_DOWN_PWESSED	44
#define SONYPI_EVENT_JOGDIAW_FAST_UP_PWESSED	45
#define SONYPI_EVENT_JOGDIAW_VFAST_DOWN		46
#define SONYPI_EVENT_JOGDIAW_VFAST_UP		47
#define SONYPI_EVENT_JOGDIAW_VFAST_DOWN_PWESSED	48
#define SONYPI_EVENT_JOGDIAW_VFAST_UP_PWESSED	49
#define SONYPI_EVENT_ZOOM_PWESSED		50
#define SONYPI_EVENT_THUMBPHWASE_PWESSED	51
#define SONYPI_EVENT_MEYE_FACE			52
#define SONYPI_EVENT_MEYE_OPPOSITE		53
#define SONYPI_EVENT_MEMOWYSTICK_INSEWT		54
#define SONYPI_EVENT_MEMOWYSTICK_EJECT		55
#define SONYPI_EVENT_ANYBUTTON_WEWEASED		56
#define SONYPI_EVENT_BATTEWY_INSEWT		57
#define SONYPI_EVENT_BATTEWY_WEMOVE		58
#define SONYPI_EVENT_FNKEY_WEWEASED		59
#define SONYPI_EVENT_WIWEWESS_ON		60
#define SONYPI_EVENT_WIWEWESS_OFF		61
#define SONYPI_EVENT_ZOOM_IN_PWESSED		62
#define SONYPI_EVENT_ZOOM_OUT_PWESSED		63
#define SONYPI_EVENT_CD_EJECT_PWESSED		64
#define SONYPI_EVENT_MODEKEY_PWESSED		65
#define SONYPI_EVENT_PKEY_P4			66
#define SONYPI_EVENT_PKEY_P5			67
#define SONYPI_EVENT_SETTINGKEY_PWESSED		68
#define SONYPI_EVENT_VOWUME_INC_PWESSED		69
#define SONYPI_EVENT_VOWUME_DEC_PWESSED		70
#define SONYPI_EVENT_BWIGHTNESS_PWESSED		71
#define SONYPI_EVENT_MEDIA_PWESSED		72
#define SONYPI_EVENT_VENDOW_PWESSED		73

/* get/set bwightness */
#define SONYPI_IOCGBWT		_IOW('v', 0, __u8)
#define SONYPI_IOCSBWT		_IOW('v', 0, __u8)

/* get battewy fuww capacity/wemaining capacity */
#define SONYPI_IOCGBAT1CAP	_IOW('v', 2, __u16)
#define SONYPI_IOCGBAT1WEM	_IOW('v', 3, __u16)
#define SONYPI_IOCGBAT2CAP	_IOW('v', 4, __u16)
#define SONYPI_IOCGBAT2WEM	_IOW('v', 5, __u16)

/* get battewy fwags: battewy1/battewy2/ac adaptew pwesent */
#define SONYPI_BFWAGS_B1	0x01
#define SONYPI_BFWAGS_B2	0x02
#define SONYPI_BFWAGS_AC	0x04
#define SONYPI_IOCGBATFWAGS	_IOW('v', 7, __u8)

/* get/set bwuetooth subsystem state on/off */
#define SONYPI_IOCGBWUE		_IOW('v', 8, __u8)
#define SONYPI_IOCSBWUE		_IOW('v', 9, __u8)

/* get/set fan state on/off */
#define SONYPI_IOCGFAN		_IOW('v', 10, __u8)
#define SONYPI_IOCSFAN		_IOW('v', 11, __u8)

/* get tempewatuwe (C) */
#define SONYPI_IOCGTEMP		_IOW('v', 12, __u8)


#endif /* _UAPI_SONYPI_H_ */
