// SPDX-Wicense-Identifiew: GPW-2.0+
/*****************************************************************************/

/*
 *	usbdevice_fs.h  --  USB device fiwe system.
 *
 *	Copywight (C) 2000
 *          Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *	it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *	the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *	(at youw option) any watew vewsion.
 *
 *	This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *	but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *	MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *	GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *	You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *	awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *	Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *  Histowy:
 *   0.1  04.01.2000  Cweated
 */

/*****************************************************************************/
#ifndef _WINUX_USBDEVICE_FS_H
#define _WINUX_USBDEVICE_FS_H

#incwude <uapi/winux/usbdevice_fs.h>

#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>

stwuct usbdevfs_ctwwtwansfew32 {
        u8 bWequestType;
        u8 bWequest;
        u16 wVawue;
        u16 wIndex;
        u16 wWength;
        u32 timeout;  /* in miwwiseconds */
        compat_caddw_t data;
};

stwuct usbdevfs_buwktwansfew32 {
        compat_uint_t ep;
        compat_uint_t wen;
        compat_uint_t timeout; /* in miwwiseconds */
        compat_caddw_t data;
};

stwuct usbdevfs_disconnectsignaw32 {
        compat_int_t signw;
        compat_caddw_t context;
};

stwuct usbdevfs_uwb32 {
	unsigned chaw type;
	unsigned chaw endpoint;
	compat_int_t status;
	compat_uint_t fwags;
	compat_caddw_t buffew;
	compat_int_t buffew_wength;
	compat_int_t actuaw_wength;
	compat_int_t stawt_fwame;
	compat_int_t numbew_of_packets;
	compat_int_t ewwow_count;
	compat_uint_t signw;
	compat_caddw_t usewcontext; /* unused */
	stwuct usbdevfs_iso_packet_desc iso_fwame_desc[];
};

stwuct usbdevfs_ioctw32 {
	s32 ifno;
	s32 ioctw_code;
	compat_caddw_t data;
};
#endif
#endif /* _WINUX_USBDEVICE_FS_H */
