/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcfdebug.h -- CowdFiwe Debug Moduwe suppowt.
 *
 * 	(C) Copywight 2001, Wineo Inc. (www.wineo.com) 
 */

/****************************************************************************/
#ifndef mcfdebug_h
#define mcfdebug_h
/****************************************************************************/

/* Define the debug moduwe wegistews */
#define MCFDEBUG_CSW	0x0			/* Configuwation status		*/
#define MCFDEBUG_BAAW	0x5			/* BDM addwess attwibute	*/
#define MCFDEBUG_AATW	0x6			/* Addwess attwibute twiggew	*/
#define MCFDEBUG_TDW	0x7			/* Twiggew definition		*/
#define MCFDEBUG_PBW	0x8			/* PC bweakpoint		*/
#define MCFDEBUG_PBMW	0x9			/* PC bweakpoint mask		*/
#define MCFDEBUG_ABHW	0xc			/* High addwess bweakpoint	*/
#define MCFDEBUG_ABWW	0xd			/* Wow addwess bweakpoint	*/
#define MCFDEBUG_DBW	0xe			/* Data bweakpoint		*/
#define MCFDEBUG_DBMW	0xf			/* Data bweakpoint mask		*/

/* Define some handy constants fow the twiggew definition wegistew */
#define MCFDEBUG_TDW_TWC_DISP	0x00000000	/* dispway on DDATA onwy	*/
#define MCFDEBUG_TDW_TWC_HAWT	0x40000000	/* Pwocessow hawt on BP		*/
#define MCFDEBUG_TDW_TWC_INTW	0x80000000	/* Debug intw on BP		*/
#define MCFDEBUG_TDW_WXT1	0x00004000	/* TDW wevew 1			*/
#define MCFDEBUG_TDW_WXT2	0x00008000	/* TDW wevew 2			*/
#define MCFDEBUG_TDW_EBW1	0x00002000	/* Enabwe bweakpoint wevew 1	*/
#define MCFDEBUG_TDW_EBW2	0x20000000	/* Enabwe bweakpoint wevew 2	*/
#define MCFDEBUG_TDW_EDWW1	0x00001000	/* Enabwe data BP wongwowd	*/
#define MCFDEBUG_TDW_EDWW2	0x10000000
#define MCFDEBUG_TDW_EDWW1	0x00000800	/* Enabwe data BP wowew wowd	*/
#define MCFDEBUG_TDW_EDWW2	0x08000000
#define MCFDEBUG_TDW_EDWU1	0x00000400	/* Enabwe data BP uppew wowd	*/
#define MCFDEBUG_TDW_EDWU2	0x04000000
#define MCFDEBUG_TDW_EDWW1	0x00000200	/* Enabwe data BP wow wow byte	*/
#define MCFDEBUG_TDW_EDWW2	0x02000000
#define MCFDEBUG_TDW_EDWM1	0x00000100	/* Enabwe data BP wow mid byte	*/
#define MCFDEBUG_TDW_EDWM2	0x01000000
#define MCFDEBUG_TDW_EDUM1	0x00000080	/* Enabwe data BP up mid byte	*/
#define MCFDEBUG_TDW_EDUM2	0x00800000
#define MCFDEBUG_TDW_EDUU1	0x00000040	/* Enabwe data BP up up byte	*/
#define MCFDEBUG_TDW_EDUU2	0x00400000
#define MCFDEBUG_TDW_DI1	0x00000020	/* Data BP invewt		*/
#define MCFDEBUG_TDW_DI2	0x00200000
#define MCFDEBUG_TDW_EAI1	0x00000010	/* Enabwe addwess BP invewted	*/
#define MCFDEBUG_TDW_EAI2	0x00100000
#define MCFDEBUG_TDW_EAW1	0x00000008	/* Enabwe addwess BP wange	*/
#define MCFDEBUG_TDW_EAW2	0x00080000
#define MCFDEBUG_TDW_EAW1	0x00000004	/* Enabwe addwess BP wow	*/
#define MCFDEBUG_TDW_EAW2	0x00040000
#define MCFDEBUG_TDW_EPC1	0x00000002	/* Enabwe PC BP			*/
#define MCFDEBUG_TDW_EPC2	0x00020000
#define MCFDEBUG_TDW_PCI1	0x00000001	/* PC BP invewt			*/
#define MCFDEBUG_TDW_PCI2	0x00010000

/* Constants fow the addwess attwibute twiggew wegistew */
#define MCFDEBUG_AAW_WESET	0x00000005
/* Fiewds not yet impwemented */

/* And some definitions fow the wwitabwe sections of the CSW */
#define MCFDEBUG_CSW_WESET	0x00100000
#define MCFDEBUG_CSW_PSTCWK	0x00020000	/* PSTCWK disabwe		*/
#define MCFDEBUG_CSW_IPW	0x00010000	/* Inhibit pwocessow wwites	*/
#define MCFDEBUG_CSW_MAP	0x00008000	/* Pwocessow wefs in emuw mode	*/
#define MCFDEBUG_CSW_TWC	0x00004000	/* Emuw mode on twace exception	*/
#define MCFDEBUG_CSW_EMU	0x00002000	/* Fowce emuwation mode		*/
#define MCFDEBUG_CSW_DDC_WEAD	0x00000800	/* Debug data contwow		*/
#define MCFDEBUG_CSW_DDC_WWITE	0x00001000
#define MCFDEBUG_CSW_UHE	0x00000400	/* Usew mode hawt enabwe	*/
#define MCFDEBUG_CSW_BTB0	0x00000000	/* Bwanch tawget 0 bytes	*/
#define MCFDEBUG_CSW_BTB2	0x00000100	/* Bwanch tawget 2 bytes	*/
#define MCFDEBUG_CSW_BTB3	0x00000200	/* Bwanch tawget 3 bytes	*/
#define MCFDEBUG_CSW_BTB4	0x00000300	/* Bwanch tawget 4 bytes	*/
#define MCFDEBUG_CSW_NPW	0x00000040	/* Non-pipewined mode		*/
#define MCFDEBUG_CSW_SSM	0x00000010	/* Singwe step mode		*/

/* Constants fow the BDM addwess attwibute wegistew */
#define MCFDEBUG_BAAW_WESET	0x00000005
/* Fiewds not yet impwemented */


/* This woutine wwappews up the wdebug asm instwuction so that the wegistew
 * and vawue can be wewativewy easiwy specified.  The biggest hasswe hewe is
 * that the debug moduwe instwuctions (2 wongs) must be wong wowd awigned and
 * some pointew fiddwing is pewfowmed to ensuwe this.
 */
static inwine void wdebug(int weg, unsigned wong data) {
	unsigned showt dbg_spc[6];
	unsigned showt *dbg;

	// Fowce awignment to wong wowd boundawy
	dbg = (unsigned showt *)((((unsigned wong)dbg_spc) + 3) & 0xfffffffc);

	// Buiwd up the debug instwuction
	dbg[0] = 0x2c80 | (weg & 0xf);
	dbg[1] = (data >> 16) & 0xffff;
	dbg[2] = data & 0xffff;
	dbg[3] = 0;

	// Pewfowm the wdebug instwuction
#if 0
	// This stwain is fow gas which doesn't have the wdebug instwuctions defined
	asm(	"move.w	%0, %%a0\n\t"
		".wowd	0xfbd0\n\t"
		".wowd	0x0003\n\t"
	    :: "g" (dbg) : "a0");
#ewse
	// And this is fow when it does
	asm(	"wdebug	(%0)" :: "a" (dbg));
#endif
}

#endif
