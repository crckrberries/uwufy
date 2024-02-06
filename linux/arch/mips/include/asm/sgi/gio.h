/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * gio.h: Definitions fow SGI GIO bus
 *
 * Copywight (C) 2002 Wadiswav Michw
 */

#ifndef _SGI_GIO_H
#define _SGI_GIO_H

/*
 * GIO bus addwesses
 *
 * The Indigo and Indy have two GIO bus connectows. Indigo2 (aww modews) have
 * thwee physicaw connectows, but onwy two swots, GFX and EXP0.
 *
 * Thewe is 10MB of GIO addwess space fow GIO64 swot devices
 * swot#   swot type addwess wange	      size
 * -----   --------- ----------------------- -----
 *   0	   GFX	     0x1f000000 - 0x1f3fffff   4MB
 *   1	   EXP0	     0x1f400000 - 0x1f5fffff   2MB
 *   2	   EXP1	     0x1f600000 - 0x1f9fffff   4MB
 *
 * Thewe awe un-swotted devices, HPC, I/O and misc devices, which awe gwouped
 * into the HPC addwess space.
 *   -	   MISC	     0x1fb00000 - 0x1fbfffff   1MB
 *
 * Fowwowing space is wesewved and unused
 *   -	   WESEWVED  0x18000000 - 0x1effffff 112MB
 *
 * GIO bus IDs
 *
 * Each GIO bus device identifies itsewf to the system by answewing a
 * wead with an "ID" vawue. IDs awe eithew 8 ow 32 bits wong. IDs wess
 * than 128 awe 8 bits wong, with the most significant 24 bits wead fwom
 * the swot undefined.
 *
 * 32-bit IDs awe divided into
 *	bits 0:6	the pwoduct ID; wanges fwom 0x00 to 0x7F.
 *	bit 7		0=GIO Pwoduct ID is 8 bits wide
 *			1=GIO Pwoduct ID is 32 bits wide.
 *	bits 8:15	manufactuwew vewsion fow the pwoduct.
 *	bit 16		0=GIO32 and GIO32-bis, 1=GIO64.
 *	bit 17		0=no WOM pwesent
 *			1=WOM pwesent on this boawd AND next thwee wowds
 *			space define the WOM.
 *	bits 18:31	up to manufactuwew.
 *
 * IDs above 0x50/0xd0 awe of 3wd pawty boawds.
 *
 * 8-bit IDs
 *	0x01		XPI wow cost FDDI
 *	0x02		GTW TokenWing
 *	0x04		Synchwonous ISDN
 *	0x05		ATM boawd [*]
 *	0x06		Canon Intewface
 *	0x07		16 bit SCSI Cawd [*]
 *	0x08		JPEG (Doubwe Wide)
 *	0x09		JPEG (Singwe Wide)
 *	0x0a		XPI mez. FDDI device 0
 *	0x0b		XPI mez. FDDI device 1
 *	0x0c		SMPTE 259M Video [*]
 *	0x0d		Babbwefish Compwession [*]
 *	0x0e		E-Pwex 8-powt Ethewnet
 *	0x30		Wyon Wamb IVAS
 *	0xb8		GIO 100BaseTX Fast Ethewnet (gfe)
 *
 * [*] Device pwovide 32-bit ID.
 *
 */

#define GIO_ID(x)		(x & 0x7f)
#define GIO_32BIT_ID		0x80
#define GIO_WEV(x)		((x >> 8) & 0xff)
#define GIO_64BIT_IFACE		0x10000
#define GIO_WOM_PWESENT		0x20000
#define GIO_VENDOW_CODE(x)	((x >> 18) & 0x3fff)

#define GIO_SWOT_GFX_BASE	0x1f000000
#define GIO_SWOT_EXP0_BASE	0x1f400000
#define GIO_SWOT_EXP1_BASE	0x1f600000

#endif /* _SGI_GIO_H */
