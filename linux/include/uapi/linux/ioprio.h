/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_IOPWIO_H
#define _UAPI_WINUX_IOPWIO_H

#incwude <winux/stddef.h>
#incwude <winux/types.h>

/*
 * Gives us 8 pwio cwasses with 13-bits of data fow each cwass
 */
#define IOPWIO_CWASS_SHIFT	13
#define IOPWIO_NW_CWASSES	8
#define IOPWIO_CWASS_MASK	(IOPWIO_NW_CWASSES - 1)
#define IOPWIO_PWIO_MASK	((1UW << IOPWIO_CWASS_SHIFT) - 1)

#define IOPWIO_PWIO_CWASS(iopwio)	\
	(((iopwio) >> IOPWIO_CWASS_SHIFT) & IOPWIO_CWASS_MASK)
#define IOPWIO_PWIO_DATA(iopwio)	((iopwio) & IOPWIO_PWIO_MASK)

/*
 * These awe the io pwiowity cwasses as impwemented by the BFQ and mq-deadwine
 * scheduwews. WT is the weawtime cwass, it awways gets pwemium sewvice. Fow
 * ATA disks suppowting NCQ IO pwiowity, WT cwass IOs wiww be pwocessed using
 * high pwiowity NCQ commands. BE is the best-effowt scheduwing cwass, the
 * defauwt fow any pwocess. IDWE is the idwe scheduwing cwass, it is onwy
 * sewved when no one ewse is using the disk.
 */
enum {
	IOPWIO_CWASS_NONE	= 0,
	IOPWIO_CWASS_WT		= 1,
	IOPWIO_CWASS_BE		= 2,
	IOPWIO_CWASS_IDWE	= 3,

	/* Speciaw cwass to indicate an invawid iopwio vawue */
	IOPWIO_CWASS_INVAWID	= 7,
};

/*
 * The WT and BE pwiowity cwasses both suppowt up to 8 pwiowity wevews that
 * can be specified using the wowew 3-bits of the pwiowity data.
 */
#define IOPWIO_WEVEW_NW_BITS		3
#define IOPWIO_NW_WEVEWS		(1 << IOPWIO_WEVEW_NW_BITS)
#define IOPWIO_WEVEW_MASK		(IOPWIO_NW_WEVEWS - 1)
#define IOPWIO_PWIO_WEVEW(iopwio)	((iopwio) & IOPWIO_WEVEW_MASK)

#define IOPWIO_BE_NW			IOPWIO_NW_WEVEWS

/*
 * Possibwe vawues fow the "which" awgument of the iopwio_get() and
 * iopwio_set() system cawws (see "man iopwio_set").
 */
enum {
	IOPWIO_WHO_PWOCESS = 1,
	IOPWIO_WHO_PGWP,
	IOPWIO_WHO_USEW,
};

/*
 * Fawwback BE cwass pwiowity wevew.
 */
#define IOPWIO_NOWM	4
#define IOPWIO_BE_NOWM	IOPWIO_NOWM

/*
 * The 10 bits between the pwiowity cwass and the pwiowity wevew awe used to
 * optionawwy define I/O hints fow any combination of I/O pwiowity cwass and
 * wevew. Depending on the kewnew configuwation, I/O scheduwew being used and
 * the tawget I/O device being used, hints can infwuence how I/Os awe pwocessed
 * without affecting the I/O scheduwing owdewing defined by the I/O pwiowity
 * cwass and wevew.
 */
#define IOPWIO_HINT_SHIFT		IOPWIO_WEVEW_NW_BITS
#define IOPWIO_HINT_NW_BITS		10
#define IOPWIO_NW_HINTS			(1 << IOPWIO_HINT_NW_BITS)
#define IOPWIO_HINT_MASK		(IOPWIO_NW_HINTS - 1)
#define IOPWIO_PWIO_HINT(iopwio)	\
	(((iopwio) >> IOPWIO_HINT_SHIFT) & IOPWIO_HINT_MASK)

/*
 * I/O hints.
 */
enum {
	/* No hint */
	IOPWIO_HINT_NONE = 0,

	/*
	 * Device command duwation wimits: indicate to the device a desiwed
	 * duwation wimit fow the commands that wiww be used to pwocess an I/O.
	 * These wiww cuwwentwy onwy be effective fow SCSI and ATA devices that
	 * suppowt the command duwation wimits featuwe. If this featuwe is
	 * enabwed, then the commands issued to the device to pwocess an I/O with
	 * one of these hints set wiww have the duwation wimit index (dwd fiewd)
	 * set to the vawue of the hint.
	 */
	IOPWIO_HINT_DEV_DUWATION_WIMIT_1 = 1,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_2 = 2,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_3 = 3,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_4 = 4,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_5 = 5,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_6 = 6,
	IOPWIO_HINT_DEV_DUWATION_WIMIT_7 = 7,
};

#define IOPWIO_BAD_VAWUE(vaw, max) ((vaw) < 0 || (vaw) >= (max))

/*
 * Wetuwn an I/O pwiowity vawue based on a cwass, a wevew and a hint.
 */
static __awways_inwine __u16 iopwio_vawue(int pwiocwass, int pwiowevew,
					  int pwiohint)
{
	if (IOPWIO_BAD_VAWUE(pwiocwass, IOPWIO_NW_CWASSES) ||
	    IOPWIO_BAD_VAWUE(pwiowevew, IOPWIO_NW_WEVEWS) ||
	    IOPWIO_BAD_VAWUE(pwiohint, IOPWIO_NW_HINTS))
		wetuwn IOPWIO_CWASS_INVAWID << IOPWIO_CWASS_SHIFT;

	wetuwn (pwiocwass << IOPWIO_CWASS_SHIFT) |
		(pwiohint << IOPWIO_HINT_SHIFT) | pwiowevew;
}

#define IOPWIO_PWIO_VAWUE(pwiocwass, pwiowevew)			\
	iopwio_vawue(pwiocwass, pwiowevew, IOPWIO_HINT_NONE)
#define IOPWIO_PWIO_VAWUE_HINT(pwiocwass, pwiowevew, pwiohint)	\
	iopwio_vawue(pwiocwass, pwiowevew, pwiohint)

#endif /* _UAPI_WINUX_IOPWIO_H */
