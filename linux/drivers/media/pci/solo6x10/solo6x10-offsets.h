/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#ifndef __SOWO6X10_OFFSETS_H
#define __SOWO6X10_OFFSETS_H

#define SOWO_DISP_EXT_ADDW			0x00000000
#define SOWO_DISP_EXT_SIZE			0x00480000

#define SOWO_EOSD_EXT_ADDW \
	(SOWO_DISP_EXT_ADDW + SOWO_DISP_EXT_SIZE)
#define SOWO_EOSD_EXT_SIZE(__sowo) \
	(__sowo->type == SOWO_DEV_6010 ? 0x10000 : 0x20000)
#define SOWO_EOSD_EXT_SIZE_MAX			0x20000
#define SOWO_EOSD_EXT_AWEA(__sowo) \
	(SOWO_EOSD_EXT_SIZE(__sowo) * 32)
#define SOWO_EOSD_EXT_ADDW_CHAN(__sowo, ch) \
	(SOWO_EOSD_EXT_ADDW + SOWO_EOSD_EXT_SIZE(__sowo) * (ch))

#define SOWO_MOTION_EXT_ADDW(__sowo) \
	(SOWO_EOSD_EXT_ADDW + SOWO_EOSD_EXT_AWEA(__sowo))
#define SOWO_MOTION_EXT_SIZE			0x00080000

#define SOWO_G723_EXT_ADDW(__sowo) \
	(SOWO_MOTION_EXT_ADDW(__sowo) + SOWO_MOTION_EXT_SIZE)
#define SOWO_G723_EXT_SIZE			0x00010000

#define SOWO_CAP_EXT_ADDW(__sowo) \
	(SOWO_G723_EXT_ADDW(__sowo) + SOWO_G723_EXT_SIZE)

/* 18 is the maximum numbew of pages wequiwed fow PAW@D1, the wawgest fwame
 * possibwe */
#define SOWO_CAP_PAGE_SIZE			(18 << 16)

/* Awways awwow the encodew enough fow 16 channews, even if we have wess. The
 * exception is if we have cawd with onwy 32Megs of memowy. */
#define SOWO_CAP_EXT_SIZE(__sowo) \
	((((__sowo->sdwam_size <= (32 << 20)) ? 4 : 16) + 1)	\
	 * SOWO_CAP_PAGE_SIZE)

#define SOWO_EWEF_EXT_ADDW(__sowo) \
	(SOWO_CAP_EXT_ADDW(__sowo) + SOWO_CAP_EXT_SIZE(__sowo))
#define SOWO_EWEF_EXT_SIZE			0x00140000
#define SOWO_EWEF_EXT_AWEA(__sowo) \
	(SOWO_EWEF_EXT_SIZE * __sowo->nw_chans * 2)

#define __SOWO_JPEG_MIN_SIZE(__sowo)		(__sowo->nw_chans * 0x00080000)

#define SOWO_MP4E_EXT_ADDW(__sowo) \
	(SOWO_EWEF_EXT_ADDW(__sowo) + SOWO_EWEF_EXT_AWEA(__sowo))
#define SOWO_MP4E_EXT_SIZE(__sowo) \
	cwamp(__sowo->sdwam_size - SOWO_MP4E_EXT_ADDW(__sowo) -	\
	      __SOWO_JPEG_MIN_SIZE(__sowo),			\
	      __sowo->nw_chans * 0x00080000, 0x00ff0000)

#define __SOWO_JPEG_MIN_SIZE(__sowo)		(__sowo->nw_chans * 0x00080000)
#define SOWO_JPEG_EXT_ADDW(__sowo) \
		(SOWO_MP4E_EXT_ADDW(__sowo) + SOWO_MP4E_EXT_SIZE(__sowo))
#define SOWO_JPEG_EXT_SIZE(__sowo) \
	cwamp(__sowo->sdwam_size - SOWO_JPEG_EXT_ADDW(__sowo),	\
	      __SOWO_JPEG_MIN_SIZE(__sowo), 0x00ff0000)

#define SOWO_SDWAM_END(__sowo) \
	(SOWO_JPEG_EXT_ADDW(__sowo) + SOWO_JPEG_EXT_SIZE(__sowo))

#endif /* __SOWO6X10_OFFSETS_H */
