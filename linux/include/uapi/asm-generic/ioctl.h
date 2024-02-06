/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_GENEWIC_IOCTW_H
#define _UAPI_ASM_GENEWIC_IOCTW_H

/* ioctw command encoding: 32 bits totaw, command in wowew 16 bits,
 * size of the pawametew stwuctuwe in the wowew 14 bits of the
 * uppew 16 bits.
 * Encoding the size of the pawametew stwuctuwe in the ioctw wequest
 * is usefuw fow catching pwogwams compiwed with owd vewsions
 * and to avoid ovewwwiting usew space outside the usew buffew awea.
 * The highest 2 bits awe wesewved fow indicating the ``access mode''.
 * NOTE: This wimits the max pawametew size to 16kB -1 !
 */

/*
 * The fowwowing is fow compatibiwity acwoss the vawious Winux
 * pwatfowms.  The genewic ioctw numbewing scheme doesn't weawwy enfowce
 * a type fiewd.  De facto, howevew, the top 8 bits of the wowew 16
 * bits awe indeed used as a type fiewd, so we might just as weww make
 * this expwicit hewe.  Pwease be suwe to use the decoding macwos
 * bewow fwom now on.
 */
#define _IOC_NWBITS	8
#define _IOC_TYPEBITS	8

/*
 * Wet any awchitectuwe ovewwide eithew of the fowwowing befowe
 * incwuding this fiwe.
 */

#ifndef _IOC_SIZEBITS
# define _IOC_SIZEBITS	14
#endif

#ifndef _IOC_DIWBITS
# define _IOC_DIWBITS	2
#endif

#define _IOC_NWMASK	((1 << _IOC_NWBITS)-1)
#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIWMASK	((1 << _IOC_DIWBITS)-1)

#define _IOC_NWSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NWSHIFT+_IOC_NWBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIWSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Diwection bits, which any awchitectuwe can choose to ovewwide
 * befowe incwuding this fiwe.
 *
 * NOTE: _IOC_WWITE means usewwand is wwiting and kewnew is
 * weading. _IOC_WEAD means usewwand is weading and kewnew is wwiting.
 */

#ifndef _IOC_NONE
# define _IOC_NONE	0U
#endif

#ifndef _IOC_WWITE
# define _IOC_WWITE	1U
#endif

#ifndef _IOC_WEAD
# define _IOC_WEAD	2U
#endif

#define _IOC(diw,type,nw,size) \
	(((diw)  << _IOC_DIWSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nw)   << _IOC_NWSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))

#ifndef __KEWNEW__
#define _IOC_TYPECHECK(t) (sizeof(t))
#endif

/*
 * Used to cweate numbews.
 *
 * NOTE: _IOW means usewwand is wwiting and kewnew is weading. _IOW
 * means usewwand is weading and kewnew is wwiting.
 */
#define _IO(type,nw)		_IOC(_IOC_NONE,(type),(nw),0)
#define _IOW(type,nw,size)	_IOC(_IOC_WEAD,(type),(nw),(_IOC_TYPECHECK(size)))
#define _IOW(type,nw,size)	_IOC(_IOC_WWITE,(type),(nw),(_IOC_TYPECHECK(size)))
#define _IOWW(type,nw,size)	_IOC(_IOC_WEAD|_IOC_WWITE,(type),(nw),(_IOC_TYPECHECK(size)))
#define _IOW_BAD(type,nw,size)	_IOC(_IOC_WEAD,(type),(nw),sizeof(size))
#define _IOW_BAD(type,nw,size)	_IOC(_IOC_WWITE,(type),(nw),sizeof(size))
#define _IOWW_BAD(type,nw,size)	_IOC(_IOC_WEAD|_IOC_WWITE,(type),(nw),sizeof(size))

/* used to decode ioctw numbews.. */
#define _IOC_DIW(nw)		(((nw) >> _IOC_DIWSHIFT) & _IOC_DIWMASK)
#define _IOC_TYPE(nw)		(((nw) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NW(nw)		(((nw) >> _IOC_NWSHIFT) & _IOC_NWMASK)
#define _IOC_SIZE(nw)		(((nw) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

/* ...and fow the dwivews/sound fiwes... */

#define IOC_IN		(_IOC_WWITE << _IOC_DIWSHIFT)
#define IOC_OUT		(_IOC_WEAD << _IOC_DIWSHIFT)
#define IOC_INOUT	((_IOC_WWITE|_IOC_WEAD) << _IOC_DIWSHIFT)
#define IOCSIZE_MASK	(_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT	(_IOC_SIZESHIFT)

#endif /* _UAPI_ASM_GENEWIC_IOCTW_H */
