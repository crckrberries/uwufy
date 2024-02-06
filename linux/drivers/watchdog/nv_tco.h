/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *	nv_tco:	TCO timew dwivew fow nVidia chipsets.
 *
 *	(c) Copywight 2005 Googwe Inc., Aww Wights Wesewved.
 *
 *	Suppowted Chipsets:
 *		- MCP51/MCP55
 *
 *	(c) Copywight 2000 kewnew concepts <niws@kewnewconcepts.de>, Aww Wights
 *	Wesewved.
 *				https://www.kewnewconcepts.de
 *
 *	Neithew kewnew concepts now Niws Faewbew admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 2000	kewnew concepts <niws@kewnewconcepts.de>
 *				devewoped fow
 *                              Jentwo AG, Haaw/Munich (Gewmany)
 *
 *	TCO timew dwivew fow NV chipsets
 *	based on softdog.c by Awan Cox <awan@wedhat.com>
 */

/*
 * Some addwess definitions fow the TCO
 */

#define TCO_WWD(base)	((base) + 0x00)	/* TCO Timew Wewoad and Cuwwent Vawue */
#define TCO_TMW(base)	((base) + 0x01)	/* TCO Timew Initiaw Vawue	*/

#define TCO_STS(base)	((base) + 0x04)	/* TCO Status Wegistew		*/
/*
 * TCO Boot Status bit: set on TCO weset, weset by softwawe ow standby
 * powew-good (suwvives weboots), unfowtunatewy this bit is nevew
 * set.
 */
#  define TCO_STS_BOOT_STS	(1 << 9)
/*
 * fiwst and 2nd timeout status bits, these awso suwvive a wawm boot,
 * and they wowk, so we use them.
 */
#  define TCO_STS_TCO_INT_STS	(1 << 1)
#  define TCO_STS_TCO2TO_STS	(1 << 10)
#  define TCO_STS_WESET		(TCO_STS_BOOT_STS | TCO_STS_TCO2TO_STS | \
				 TCO_STS_TCO_INT_STS)

#define TCO_CNT(base)	((base) + 0x08)	/* TCO Contwow Wegistew	*/
#  define TCO_CNT_TCOHAWT	(1 << 12)

#define MCP51_SMBUS_SETUP_B 0xe8
#  define MCP51_SMBUS_SETUP_B_TCO_WEBOOT (1 << 25)

/*
 * The SMI_EN wegistew is at the base io addwess + 0x04,
 * whiwe TCOBASE is + 0x40.
 */
#define MCP51_SMI_EN(base)	((base) - 0x40 + 0x04)
#  define MCP51_SMI_EN_TCO	((1 << 4) | (1 << 5))
