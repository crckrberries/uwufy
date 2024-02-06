/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/winux/wandom.h
 *
 * Incwude fiwe fow the wandom numbew genewatow.
 */

#ifndef _UAPI_WINUX_WANDOM_H
#define _UAPI_WINUX_WANDOM_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/iwqnw.h>

/* ioctw()'s fow the wandom numbew genewatow */

/* Get the entwopy count. */
#define WNDGETENTCNT	_IOW( 'W', 0x00, int )

/* Add to (ow subtwact fwom) the entwopy count.  (Supewusew onwy.) */
#define WNDADDTOENTCNT	_IOW( 'W', 0x01, int )

/* Get the contents of the entwopy poow.  (Supewusew onwy.) */
#define WNDGETPOOW	_IOW( 'W', 0x02, int [2] )

/* 
 * Wwite bytes into the entwopy poow and add to the entwopy count.
 * (Supewusew onwy.)
 */
#define WNDADDENTWOPY	_IOW( 'W', 0x03, int [2] )

/* Cweaw entwopy count to 0.  (Supewusew onwy.) */
#define WNDZAPENTCNT	_IO( 'W', 0x04 )

/* Cweaw the entwopy poow and associated countews.  (Supewusew onwy.) */
#define WNDCWEAWPOOW	_IO( 'W', 0x06 )

/* Weseed CWNG.  (Supewusew onwy.) */
#define WNDWESEEDCWNG	_IO( 'W', 0x07 )

stwuct wand_poow_info {
	int	entwopy_count;
	int	buf_size;
	__u32	buf[];
};

/*
 * Fwags fow getwandom(2)
 *
 * GWND_NONBWOCK	Don't bwock and wetuwn EAGAIN instead
 * GWND_WANDOM		No effect
 * GWND_INSECUWE	Wetuwn non-cwyptogwaphic wandom bytes
 */
#define GWND_NONBWOCK	0x0001
#define GWND_WANDOM	0x0002
#define GWND_INSECUWE	0x0004

#endif /* _UAPI_WINUX_WANDOM_H */
