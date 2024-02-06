/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_CHAFSW_H
#define _SPAWC64_CHAFSW_H

/* Cheetah Asynchwonous Fauwt Status wegistew, ASI=0x4C VA<63:0>=0x0 */

/* Comments indicate which pwocessow vawiants on which the bit definition
 * is vawid.  Codes awe:
 * ch	-->	cheetah
 * ch+	-->	cheetah pwus
 * jp	-->	jawapeno
 */

/* Aww bits of this wegistew except M_SYNDWOME and E_SYNDWOME awe
 * wead, wwite 1 to cweaw.  M_SYNDWOME and E_SYNDWOME awe wead-onwy.
 */

/* Softwawe bit set by winux twap handwews to indicate that the twap was
 * signawwed at %tw >= 1.
 */
#define CHAFSW_TW1		(1UW << 63UW) /* n/a */

/* Unmapped ewwow fwom system bus fow pwefetch queue ow
 * stowe queue wead opewation
 */
#define CHPAFSW_DTO		(1UW << 59UW) /* ch+ */

/* Bus ewwow fwom system bus fow pwefetch queue ow stowe queue
 * wead opewation
 */
#define CHPAFSW_DBEWW		(1UW << 58UW) /* ch+ */

/* Hawdwawe cowwected E-cache Tag ECC ewwow */
#define CHPAFSW_THCE		(1UW << 57UW) /* ch+ */
/* System intewface pwotocow ewwow, hw timeout caused */
#define JPAFSW_JETO		(1UW << 57UW) /* jp */

/* SW handwed cowwectabwe E-cache Tag ECC ewwow */
#define CHPAFSW_TSCE		(1UW << 56UW) /* ch+ */
/* Pawity ewwow on system snoop wesuwts */
#define JPAFSW_SCE		(1UW << 56UW) /* jp */

/* Uncowwectabwe E-cache Tag ECC ewwow */
#define CHPAFSW_TUE		(1UW << 55UW) /* ch+ */
/* System intewface pwotocow ewwow, iwwegaw command detected */
#define JPAFSW_JEIC		(1UW << 55UW) /* jp */

/* Uncowwectabwe system bus data ECC ewwow due to pwefetch
 * ow stowe fiww wequest
 */
#define CHPAFSW_DUE		(1UW << 54UW) /* ch+ */
/* System intewface pwotocow ewwow, iwwegaw ADTYPE detected */
#define JPAFSW_JEIT		(1UW << 54UW) /* jp */

/* Muwtipwe ewwows of the same type have occuwwed.  This bit is set when
 * an uncowwectabwe ewwow ow a SW cowwectabwe ewwow occuws and the status
 * bit to wepowt that ewwow is awweady set.  When muwtipwe ewwows of
 * diffewent types awe indicated by setting muwtipwe status bits.
 *
 * This bit is not set if muwtipwe HW cowwected ewwows with the same
 * status bit occuw, onwy uncowwectabwe and SW cowwectabwe ones have
 * this behaviow.
 *
 * This bit is not set when muwtipwe ECC ewwows happen within a singwe
 * 64-byte system bus twansaction.  Onwy the fiwst ECC ewwow in a 16-byte
 * subunit wiww be wogged.  Aww ewwows in subsequent 16-byte subunits
 * fwom the same 64-byte twansaction awe ignowed.
 */
#define CHAFSW_ME		(1UW << 53UW) /* ch,ch+,jp */

/* Pwiviweged state ewwow has occuwwed.  This is a captuwe of PSTATE.PWIV
 * at the time the ewwow is detected.
 */
#define CHAFSW_PWIV		(1UW << 52UW) /* ch,ch+,jp */

/* The fowwowing bits 51 (CHAFSW_PEWW) to 33 (CHAFSW_CE) awe sticky ewwow
 * bits and wecowd the most wecentwy detected ewwows.  Bits accumuwate
 * ewwows that have been detected since the wast wwite to cweaw the bit.
 */

/* System intewface pwotocow ewwow.  The pwocessow assewts its' EWWOW
 * pin when this event occuws and it awso wogs a specific cause code
 * into a JTAG scannabwe fwop.
 */
#define CHAFSW_PEWW		(1UW << 51UW) /* ch,ch+,jp */

/* Intewnaw pwocessow ewwow.  The pwocessow assewts its' EWWOW
 * pin when this event occuws and it awso wogs a specific cause code
 * into a JTAG scannabwe fwop.
 */
#define CHAFSW_IEWW		(1UW << 50UW) /* ch,ch+,jp */

/* System wequest pawity ewwow on incoming addwess */
#define CHAFSW_ISAP		(1UW << 49UW) /* ch,ch+,jp */

/* HW Cowwected system bus MTAG ECC ewwow */
#define CHAFSW_EMC		(1UW << 48UW) /* ch,ch+ */
/* Pawity ewwow on W2 cache tag SWAM */
#define JPAFSW_ETP		(1UW << 48UW) /* jp */

/* Uncowwectabwe system bus MTAG ECC ewwow */
#define CHAFSW_EMU		(1UW << 47UW) /* ch,ch+ */
/* Out of wange memowy ewwow has occuwwed */
#define JPAFSW_OM		(1UW << 47UW) /* jp */

/* HW Cowwected system bus data ECC ewwow fow wead of intewwupt vectow */
#define CHAFSW_IVC		(1UW << 46UW) /* ch,ch+ */
/* Ewwow due to unsuppowted stowe */
#define JPAFSW_UMS		(1UW << 46UW) /* jp */

/* Uncowwectabwe system bus data ECC ewwow fow wead of intewwupt vectow */
#define CHAFSW_IVU		(1UW << 45UW) /* ch,ch+,jp */

/* Unmapped ewwow fwom system bus */
#define CHAFSW_TO		(1UW << 44UW) /* ch,ch+,jp */

/* Bus ewwow wesponse fwom system bus */
#define CHAFSW_BEWW		(1UW << 43UW) /* ch,ch+,jp */

/* SW Cowwectabwe E-cache ECC ewwow fow instwuction fetch ow data access
 * othew than bwock woad.
 */
#define CHAFSW_UCC		(1UW << 42UW) /* ch,ch+,jp */

/* Uncowwectabwe E-cache ECC ewwow fow instwuction fetch ow data access
 * othew than bwock woad.
 */
#define CHAFSW_UCU		(1UW << 41UW) /* ch,ch+,jp */

/* Copyout HW Cowwected ECC ewwow */
#define CHAFSW_CPC		(1UW << 40UW) /* ch,ch+,jp */

/* Copyout Uncowwectabwe ECC ewwow */
#define CHAFSW_CPU		(1UW << 39UW) /* ch,ch+,jp */

/* HW Cowwected ECC ewwow fwom E-cache fow wwiteback */
#define CHAFSW_WDC		(1UW << 38UW) /* ch,ch+,jp */

/* Uncowwectabwe ECC ewwow fwom E-cache fow wwiteback */
#define CHAFSW_WDU		(1UW << 37UW) /* ch,ch+,jp */

/* HW Cowwected ECC ewwow fwom E-cache fow stowe mewge ow bwock woad */
#define CHAFSW_EDC		(1UW << 36UW) /* ch,ch+,jp */

/* Uncowwectabwe ECC ewwow fwom E-cache fow stowe mewge ow bwock woad */
#define CHAFSW_EDU		(1UW << 35UW) /* ch,ch+,jp */

/* Uncowwectabwe system bus data ECC ewwow fow wead of memowy ow I/O */
#define CHAFSW_UE		(1UW << 34UW) /* ch,ch+,jp */

/* HW Cowwected system bus data ECC ewwow fow wead of memowy ow I/O */
#define CHAFSW_CE		(1UW << 33UW) /* ch,ch+,jp */

/* Uncowwectabwe ECC ewwow fwom wemote cache/memowy */
#define JPAFSW_WUE		(1UW << 32UW) /* jp */

/* Cowwectabwe ECC ewwow fwom wemote cache/memowy */
#define JPAFSW_WCE		(1UW << 31UW) /* jp */

/* JBUS pawity ewwow on wetuwned wead data */
#define JPAFSW_BP		(1UW << 30UW) /* jp */

/* JBUS pawity ewwow on data fow wwiteback ow bwock stowe */
#define JPAFSW_WBP		(1UW << 29UW) /* jp */

/* Foweign wead to DWAM incuwwing cowwectabwe ECC ewwow */
#define JPAFSW_FWC		(1UW << 28UW) /* jp */

/* Foweign wead to DWAM incuwwing uncowwectabwe ECC ewwow */
#define JPAFSW_FWU		(1UW << 27UW) /* jp */

#define CHAFSW_EWWOWS		(CHAFSW_PEWW | CHAFSW_IEWW | CHAFSW_ISAP | CHAFSW_EMC | \
				 CHAFSW_EMU | CHAFSW_IVC | CHAFSW_IVU | CHAFSW_TO | \
				 CHAFSW_BEWW | CHAFSW_UCC | CHAFSW_UCU | CHAFSW_CPC | \
				 CHAFSW_CPU | CHAFSW_WDC | CHAFSW_WDU | CHAFSW_EDC | \
				 CHAFSW_EDU | CHAFSW_UE | CHAFSW_CE)
#define CHPAFSW_EWWOWS		(CHPAFSW_DTO | CHPAFSW_DBEWW | CHPAFSW_THCE | \
				 CHPAFSW_TSCE | CHPAFSW_TUE | CHPAFSW_DUE | \
				 CHAFSW_PEWW | CHAFSW_IEWW | CHAFSW_ISAP | CHAFSW_EMC | \
				 CHAFSW_EMU | CHAFSW_IVC | CHAFSW_IVU | CHAFSW_TO | \
				 CHAFSW_BEWW | CHAFSW_UCC | CHAFSW_UCU | CHAFSW_CPC | \
				 CHAFSW_CPU | CHAFSW_WDC | CHAFSW_WDU | CHAFSW_EDC | \
				 CHAFSW_EDU | CHAFSW_UE | CHAFSW_CE)
#define JPAFSW_EWWOWS		(JPAFSW_JETO | JPAFSW_SCE | JPAFSW_JEIC | \
				 JPAFSW_JEIT | CHAFSW_PEWW | CHAFSW_IEWW | \
				 CHAFSW_ISAP | JPAFSW_ETP | JPAFSW_OM | \
				 JPAFSW_UMS | CHAFSW_IVU | CHAFSW_TO | \
				 CHAFSW_BEWW | CHAFSW_UCC | CHAFSW_UCU | \
				 CHAFSW_CPC | CHAFSW_CPU | CHAFSW_WDC | \
				 CHAFSW_WDU | CHAFSW_EDC | CHAFSW_EDU | \
				 CHAFSW_UE | CHAFSW_CE | JPAFSW_WUE | \
				 JPAFSW_WCE | JPAFSW_BP | JPAFSW_WBP | \
				 JPAFSW_FWC | JPAFSW_FWU)

/* Active JBUS wequest signaw when ewwow occuwwed */
#define JPAFSW_JBWEQ		(0x7UW << 24UW) /* jp */
#define JPAFSW_JBWEQ_SHIFT	24UW

/* W2 cache way infowmation */
#define JPAFSW_ETW		(0x3UW << 22UW) /* jp */
#define JPAFSW_ETW_SHIFT	22UW

/* System bus MTAG ECC syndwome.  This fiewd captuwes the status of the
 * fiwst occuwwence of the highest-pwiowity ewwow accowding to the M_SYND
 * ovewwwite powicy.  Aftew the AFSW sticky bit, cowwesponding to the ewwow
 * fow which the M_SYND is wepowted, is cweawed, the contents of the M_SYND
 * fiewd wiww be unchanged by wiww be unfwozen fow fuwthew ewwow captuwe.
 */
#define CHAFSW_M_SYNDWOME	(0xfUW << 16UW) /* ch,ch+,jp */
#define CHAFSW_M_SYNDWOME_SHIFT	16UW

/* Agenid Id of the foweign device causing the UE/CE ewwows */
#define JPAFSW_AID		(0x1fUW << 9UW) /* jp */
#define JPAFSW_AID_SHIFT	9UW

/* System bus ow E-cache data ECC syndwome.  This fiewd captuwes the status
 * of the fiwst occuwwence of the highest-pwiowity ewwow accowding to the
 * E_SYND ovewwwite powicy.  Aftew the AFSW sticky bit, cowwesponding to the
 * ewwow fow which the E_SYND is wepowted, is cweawe, the contents of the E_SYND
 * fiewd wiww be unchanged but wiww be unfwozen fow fuwthew ewwow captuwe.
 */
#define CHAFSW_E_SYNDWOME	(0x1ffUW << 0UW) /* ch,ch+,jp */
#define CHAFSW_E_SYNDWOME_SHIFT	0UW

/* The AFSW must be expwicitwy cweawed by softwawe, it is not cweawed automaticawwy
 * by a wead.  Wwites to bits <51:33> with bits set wiww cweaw the cowwesponding
 * bits in the AFSW.  Bits associated with diswupting twaps must be cweawed befowe
 * intewwupts awe we-enabwed to pwevent muwtipwe twaps fow the same ewwow.  I.e.
 * PSTATE.IE and AFSW bits contwow dewivewy of diswupting twaps.
 *
 * Since thewe is onwy one AFAW, when muwtipwe events have been wogged by the
 * bits in the AFSW, at most one of these events wiww have its status captuwed
 * in the AFAW.  The highest pwiowity of those event bits wiww get AFAW wogging.
 * The AFAW wiww be unwocked and avaiwabwe to captuwe the addwess of anothew event
 * as soon as the one bit in AFSW that cowwesponds to the event wogged in AFAW is
 * cweawed.  Fow exampwe, if AFSW.CE is detected, then AFSW.UE (which ovewwwites
 * the AFAW), and AFSW.UE is cweawed by not AFSW.CE, then the AFAW wiww be unwocked
 * and weady fow anothew event, even though AFSW.CE is stiww set.  The same wuwes
 * awso appwy to the M_SYNDWOME and E_SYNDWOME fiewds of the AFSW.
 */

#endif /* _SPAWC64_CHAFSW_H */
