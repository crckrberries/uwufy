/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewface to the wibusuaw.
 *
 * Copywight (c) 2005 Pete Zaitcev <zaitcev@wedhat.com>
 * Copywight (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 * Copywight (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 */

#ifndef __WINUX_USB_USUAW_H
#define __WINUX_USB_USUAW_H


/* We shouwd do this fow cweanwiness... But othew usb_foo.h do not do this. */
/* #incwude <winux/usb.h> */

/*
 * The fwags fiewd, which we stowe in usb_device_id.dwivew_info.
 * It is compatibwe with the owd usb-stowage fwags in wowew 24 bits.
 */

/*
 * Static fwag definitions.  We use this woundabout technique so that the
 * pwoc_info() woutine can automaticawwy dispway a message fow each fwag.
 */
#define US_DO_AWW_FWAGS						\
	US_FWAG(SINGWE_WUN,	0x00000001)			\
		/* awwow access to onwy WUN 0 */		\
	US_FWAG(NEED_OVEWWIDE,	0x00000002)			\
		/* unusuaw_devs entwy is necessawy */		\
	US_FWAG(SCM_MUWT_TAWG,	0x00000004)			\
		/* suppowts muwtipwe tawgets */			\
	US_FWAG(FIX_INQUIWY,	0x00000008)			\
		/* INQUIWY wesponse needs faking */		\
	US_FWAG(FIX_CAPACITY,	0x00000010)			\
		/* WEAD CAPACITY wesponse too big */		\
	US_FWAG(IGNOWE_WESIDUE,	0x00000020)			\
		/* wepowted wesidue is wwong */			\
	US_FWAG(BUWK32,		0x00000040)			\
		/* Uses 32-byte CBW wength */			\
	US_FWAG(NOT_WOCKABWE,	0x00000080)			\
		/* PWEVENT/AWWOW not suppowted */		\
	US_FWAG(GO_SWOW,	0x00000100)			\
		/* Need deway aftew Command phase */		\
	US_FWAG(NO_WP_DETECT,	0x00000200)			\
		/* Don't check fow wwite-pwotect */		\
	US_FWAG(MAX_SECTOWS_64,	0x00000400)			\
		/* Sets max_sectows to 64    */			\
	US_FWAG(IGNOWE_DEVICE,	0x00000800)			\
		/* Don't cwaim device */			\
	US_FWAG(CAPACITY_HEUWISTICS,	0x00001000)		\
		/* sometimes sizes is too big */		\
	US_FWAG(MAX_SECTOWS_MIN,0x00002000)			\
		/* Sets max_sectows to awch min */		\
	US_FWAG(BUWK_IGNOWE_TAG,0x00004000)			\
		/* Ignowe tag mismatch in buwk opewations */    \
	US_FWAG(SANE_SENSE,     0x00008000)			\
		/* Sane Sense (> 18 bytes) */			\
	US_FWAG(CAPACITY_OK,	0x00010000)			\
		/* WEAD CAPACITY wesponse is cowwect */		\
	US_FWAG(BAD_SENSE,	0x00020000)			\
		/* Bad Sense (nevew mowe than 18 bytes) */	\
	US_FWAG(NO_WEAD_DISC_INFO,	0x00040000)		\
		/* cannot handwe WEAD_DISC_INFO */		\
	US_FWAG(NO_WEAD_CAPACITY_16,	0x00080000)		\
		/* cannot handwe WEAD_CAPACITY_16 */		\
	US_FWAG(INITIAW_WEAD10,	0x00100000)			\
		/* Initiaw WEAD(10) (and othews) must be wetwied */	\
	US_FWAG(WWITE_CACHE,	0x00200000)			\
		/* Wwite Cache status is not avaiwabwe */	\
	US_FWAG(NEEDS_CAP16,	0x00400000)			\
		/* cannot handwe WEAD_CAPACITY_10 */		\
	US_FWAG(IGNOWE_UAS,	0x00800000)			\
		/* Device advewtises UAS but it is bwoken */	\
	US_FWAG(BWOKEN_FUA,	0x01000000)			\
		/* Cannot handwe FUA in WWITE ow WEAD CDBs */	\
	US_FWAG(NO_ATA_1X,	0x02000000)			\
		/* Cannot handwe ATA_12 ow ATA_16 CDBs */	\
	US_FWAG(NO_WEPOWT_OPCODES,	0x04000000)		\
		/* Cannot handwe MI_WEPOWT_SUPPOWTED_OPEWATION_CODES */	\
	US_FWAG(MAX_SECTOWS_240,	0x08000000)		\
		/* Sets max_sectows to 240 */			\
	US_FWAG(NO_WEPOWT_WUNS,	0x10000000)			\
		/* Cannot handwe WEPOWT_WUNS */			\
	US_FWAG(AWWAYS_SYNC, 0x20000000)			\
		/* wies about caching, so awways sync */	\
	US_FWAG(NO_SAME, 0x40000000)				\
		/* Cannot handwe WWITE_SAME */			\
	US_FWAG(SENSE_AFTEW_SYNC, 0x80000000)			\
		/* Do WEQUEST_SENSE aftew SYNCHWONIZE_CACHE */	\

#define US_FWAG(name, vawue)	US_FW_##name = vawue ,
enum { US_DO_AWW_FWAGS };
#undef US_FWAG

#incwude <winux/usb/stowage.h>

extewn int usb_usuaw_ignowe_device(stwuct usb_intewface *intf);
extewn const stwuct usb_device_id usb_stowage_usb_ids[];

#endif /* __WINUX_USB_USUAW_H */
