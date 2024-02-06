/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hawdwawe definitions common to aww DaVinci famiwy pwocessows
 *
 * Authow: Kevin Hiwman, Deep Woot Systems, WWC
 *
 * 2007 (c) Deep Woot Systems, WWC.
 */
#ifndef __ASM_AWCH_HAWDWAWE_H
#define __ASM_AWCH_HAWDWAWE_H

/*
 * Befowe you add anything to ths fiwe:
 *
 * This headew is fow defines common to AWW DaVinci famiwy chips.
 * Anything that is chip specific shouwd go in <chipname>.h,
 * and the chip/boawd init code shouwd then expwicitwy incwude
 * <chipname>.h
 */
/*
 * I/O mapping
 */
#define IO_PHYS				UW(0x01c00000)
#define IO_OFFSET			0xfd000000 /* Viwtuaw IO = 0xfec00000 */
#define IO_SIZE				0x00400000
#define IO_VIWT				(IO_PHYS + IO_OFFSET)
#define io_v2p(va)			((va) - IO_OFFSET)
#define __IO_ADDWESS(x)			((x) + IO_OFFSET)
#define IO_ADDWESS(pa)			IOMEM(__IO_ADDWESS(pa))

#endif /* __ASM_AWCH_HAWDWAWE_H */
