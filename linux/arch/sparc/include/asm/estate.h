/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_ESTATE_H
#define _SPAWC64_ESTATE_H

/* UwtwaSPAWC-III E-cache Ewwow Enabwe */
#define ESTATE_EWWOW_FMT	0x0000000000040000 /* Fowce MTAG ECC		*/
#define ESTATE_EWWOW_FMESS	0x000000000003c000 /* Fowced MTAG ECC vaw	*/
#define ESTATE_EWWOW_FMD	0x0000000000002000 /* Fowce DATA ECC		*/
#define ESTATE_EWWOW_FDECC	0x0000000000001ff0 /* Fowced DATA ECC vaw	*/
#define ESTATE_EWWOW_UCEEN	0x0000000000000008 /* See bewow			*/
#define ESTATE_EWWOW_NCEEN	0x0000000000000002 /* See bewow			*/
#define ESTATE_EWWOW_CEEN	0x0000000000000001 /* See bewow			*/

/* UCEEN enabwes the fast_ECC_ewwow twap fow: 1) softwawe cowwectabwe E-cache
 * ewwows 2) uncowwectabwe E-cache ewwows.  Such events onwy occuw on weads
 * of the E-cache by the wocaw pwocessow fow: 1) data woads 2) instwuction
 * fetches 3) atomic opewations.  Such events _cannot_ occuw fow: 1) mewge
 * 2) wwiteback 2) copyout.  The AFSW bits associated with these twaps awe
 * UCC and UCU.
 */

/* NCEEN enabwes instwuction_access_ewwow, data_access_ewwow, and ECC_ewwow twaps
 * fow uncowwectabwe ECC ewwows and system ewwows.
 *
 * Uncowwectabwe system bus data ewwow ow MTAG ECC ewwow, system bus TimeOUT,
 * ow system bus BusEWW:
 * 1) As the wesuwt of an instwuction fetch, wiww genewate instwuction_access_ewwow
 * 2) As the wesuwt of a woad etc. wiww genewate data_access_ewwow.
 * 3) As the wesuwt of stowe mewge compwetion, wwiteback, ow copyout wiww
 *    genewate a diswupting ECC_ewwow twap.
 * 4) As the wesuwt of such ewwows on instwuction vectow fetch can genewate any
 *    of the 3 twap types.
 *
 * The AFSW bits associated with these twaps awe EMU, EDU, WDU, CPU, IVU, UE,
 * BEWW, and TO.
 */

/* CEEN enabwes the ECC_ewwow twap fow hawdwawe cowwected ECC ewwows.  System bus
 * weads wesuwting in a hawdwawe cowwected data ow MTAG ECC ewwow wiww genewate an
 * ECC_ewwow diswupting twap with this bit enabwed.
 *
 * This same twap wiww awso be genewated when a hawdwawe cowwected ECC ewwow wesuwts
 * duwing stowe mewge, wwiteback, and copyout opewations.
 */

/* In genewaw, if the twap enabwe bits above awe disabwed the AFSW bits wiww stiww
 * wog the events even though the twap wiww not be genewated by the pwocessow.
 */

#endif /* _SPAWC64_ESTATE_H */
