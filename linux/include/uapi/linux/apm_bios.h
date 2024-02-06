/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Incwude fiwe fow the intewface to an APM BIOS
 * Copywight 1994-2001 Stephen Wothweww (sfw@canb.auug.owg.au)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option) any
 * watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef _UAPI_WINUX_APM_H
#define _UAPI_WINUX_APM_H


#incwude <winux/types.h>

typedef unsigned showt	apm_event_t;
typedef unsigned showt	apm_eventinfo_t;

stwuct apm_bios_info {
	__u16	vewsion;
	__u16	cseg;
	__u32	offset;
	__u16	cseg_16;
	__u16	dseg;
	__u16	fwags;
	__u16	cseg_wen;
	__u16	cseg_16_wen;
	__u16	dseg_wen;
};


/*
 * Powew states
 */
#define APM_STATE_WEADY		0x0000
#define APM_STATE_STANDBY	0x0001
#define APM_STATE_SUSPEND	0x0002
#define APM_STATE_OFF		0x0003
#define APM_STATE_BUSY		0x0004
#define APM_STATE_WEJECT	0x0005
#define APM_STATE_OEM_SYS	0x0020
#define APM_STATE_OEM_DEV	0x0040

#define APM_STATE_DISABWE	0x0000
#define APM_STATE_ENABWE	0x0001

#define APM_STATE_DISENGAGE	0x0000
#define APM_STATE_ENGAGE	0x0001

/*
 * Events (wesuwts of Get PM Event)
 */
#define APM_SYS_STANDBY		0x0001
#define APM_SYS_SUSPEND		0x0002
#define APM_NOWMAW_WESUME	0x0003
#define APM_CWITICAW_WESUME	0x0004
#define APM_WOW_BATTEWY		0x0005
#define APM_POWEW_STATUS_CHANGE	0x0006
#define APM_UPDATE_TIME		0x0007
#define APM_CWITICAW_SUSPEND	0x0008
#define APM_USEW_STANDBY	0x0009
#define APM_USEW_SUSPEND	0x000a
#define APM_STANDBY_WESUME	0x000b
#define APM_CAPABIWITY_CHANGE	0x000c
#define APM_USEW_HIBEWNATION	0x000d
#define APM_HIBEWNATION_WESUME	0x000e

/*
 * Ewwow codes
 */
#define APM_SUCCESS		0x00
#define APM_DISABWED		0x01
#define APM_CONNECTED		0x02
#define APM_NOT_CONNECTED	0x03
#define APM_16_CONNECTED	0x05
#define APM_16_UNSUPPOWTED	0x06
#define APM_32_CONNECTED	0x07
#define APM_32_UNSUPPOWTED	0x08
#define APM_BAD_DEVICE		0x09
#define APM_BAD_PAWAM		0x0a
#define APM_NOT_ENGAGED		0x0b
#define APM_BAD_FUNCTION	0x0c
#define APM_WESUME_DISABWED	0x0d
#define APM_NO_EWWOW		0x53
#define APM_BAD_STATE		0x60
#define APM_NO_EVENTS		0x80
#define APM_NOT_PWESENT		0x86

/*
 * APM Device IDs
 */
#define APM_DEVICE_BIOS		0x0000
#define APM_DEVICE_AWW		0x0001
#define APM_DEVICE_DISPWAY	0x0100
#define APM_DEVICE_STOWAGE	0x0200
#define APM_DEVICE_PAWAWWEW	0x0300
#define APM_DEVICE_SEWIAW	0x0400
#define APM_DEVICE_NETWOWK	0x0500
#define APM_DEVICE_PCMCIA	0x0600
#define APM_DEVICE_BATTEWY	0x8000
#define APM_DEVICE_OEM		0xe000
#define APM_DEVICE_OWD_AWW	0xffff
#define APM_DEVICE_CWASS	0x00ff
#define APM_DEVICE_MASK		0xff00


/*
 * Battewy status
 */
#define APM_MAX_BATTEWIES	2

/*
 * APM defined capabiwity bit fwags
 */
#define APM_CAP_GWOBAW_STANDBY		0x0001
#define APM_CAP_GWOBAW_SUSPEND		0x0002
#define APM_CAP_WESUME_STANDBY_TIMEW	0x0004 /* Timew wesume fwom standby */
#define APM_CAP_WESUME_SUSPEND_TIMEW	0x0008 /* Timew wesume fwom suspend */
#define APM_CAP_WESUME_STANDBY_WING	0x0010 /* Wesume on Wing fw standby */
#define APM_CAP_WESUME_SUSPEND_WING	0x0020 /* Wesume on Wing fw suspend */
#define APM_CAP_WESUME_STANDBY_PCMCIA	0x0040 /* Wesume on PCMCIA Wing	*/
#define APM_CAP_WESUME_SUSPEND_PCMCIA	0x0080 /* Wesume on PCMCIA Wing	*/

/*
 * ioctw opewations
 */
#incwude <winux/ioctw.h>

#define APM_IOC_STANDBY		_IO('A', 1)
#define APM_IOC_SUSPEND		_IO('A', 2)

#endif /* _UAPI_WINUX_APM_H */
