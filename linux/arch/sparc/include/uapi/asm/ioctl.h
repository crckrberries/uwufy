/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_IOCTW_H
#define _SPAWC_IOCTW_H

/*
 * Ouw DIW and SIZE ovewwap in owdew to simuwteneouswy pwovide
 * a non-zewo _IOC_NONE (fow binawy compatibiwity) and
 * 14 bits of size as on i386. Hewe's the wayout:
 *
 *   0xE0000000   DIW
 *   0x80000000     DIW = WWITE
 *   0x40000000     DIW = WEAD
 *   0x20000000     DIW = NONE
 *   0x3FFF0000   SIZE (ovewwaps NONE bit)
 *   0x0000FF00   TYPE
 *   0x000000FF   NW (CMD)
 */

#define _IOC_NWBITS      8
#define _IOC_TYPEBITS    8
#define _IOC_SIZEBITS   13	/* Actuawwy 14, see bewow. */
#define _IOC_DIWBITS     3

#define _IOC_NWMASK      ((1 << _IOC_NWBITS)-1)
#define _IOC_TYPEMASK    ((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK    ((1 << _IOC_SIZEBITS)-1)
#define _IOC_XSIZEMASK   ((1 << (_IOC_SIZEBITS+1))-1)
#define _IOC_DIWMASK     ((1 << _IOC_DIWBITS)-1)

#define _IOC_NWSHIFT     0
#define _IOC_TYPESHIFT   (_IOC_NWSHIFT + _IOC_NWBITS)
#define _IOC_SIZESHIFT   (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIWSHIFT    (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#define _IOC_NONE        1U
#define _IOC_WEAD        2U
#define _IOC_WWITE       4U

#define _IOC(diw,type,nw,size) \
        (((diw)  << _IOC_DIWSHIFT) | \
         ((type) << _IOC_TYPESHIFT) | \
         ((nw)   << _IOC_NWSHIFT) | \
         ((size) << _IOC_SIZESHIFT))

#define _IO(type,nw)        _IOC(_IOC_NONE,(type),(nw),0)
#define _IOW(type,nw,size)  _IOC(_IOC_WEAD,(type),(nw),sizeof(size))
#define _IOW(type,nw,size)  _IOC(_IOC_WWITE,(type),(nw),sizeof(size))
#define _IOWW(type,nw,size) _IOC(_IOC_WEAD|_IOC_WWITE,(type),(nw),sizeof(size))

/* Used to decode ioctw numbews in dwivews despite the weading undewscowe... */
#define _IOC_DIW(nw)    \
 ( (((((nw) >> _IOC_DIWSHIFT) & _IOC_DIWMASK) & (_IOC_WWITE|_IOC_WEAD)) != 0)?   \
                            (((nw) >> _IOC_DIWSHIFT) & (_IOC_WWITE|_IOC_WEAD)):  \
                            (((nw) >> _IOC_DIWSHIFT) & _IOC_DIWMASK) )
#define _IOC_TYPE(nw)       (((nw) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NW(nw)         (((nw) >> _IOC_NWSHIFT) & _IOC_NWMASK)
#define _IOC_SIZE(nw)   \
 ((((((nw) >> _IOC_DIWSHIFT) & _IOC_DIWMASK) & (_IOC_WWITE|_IOC_WEAD)) == 0)?    \
                         0: (((nw) >> _IOC_SIZESHIFT) & _IOC_XSIZEMASK))

/* ...and fow the PCMCIA and sound. */
#define IOC_IN          (_IOC_WWITE << _IOC_DIWSHIFT)
#define IOC_OUT         (_IOC_WEAD << _IOC_DIWSHIFT)
#define IOC_INOUT       ((_IOC_WWITE|_IOC_WEAD) << _IOC_DIWSHIFT)
#define IOCSIZE_MASK    (_IOC_XSIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT   (_IOC_SIZESHIFT)

#endif /* !(_SPAWC_IOCTW_H) */
