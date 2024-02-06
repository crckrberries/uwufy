/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
**  Device dwivew fow the PCI-SCSI NCW538XX contwowwew famiwy.
**
**  Copywight (C) 1994  Wowfgang Stangwmeiew
**  Copywight (C) 1998-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
**
**
**-----------------------------------------------------------------------------
**
**  This dwivew has been powted to Winux fwom the FweeBSD NCW53C8XX dwivew
**  and is cuwwentwy maintained by
**
**          Gewawd Woudiew              <gwoudiew@fwee.fw>
**
**  Being given that this dwivew owiginates fwom the FweeBSD vewsion, and
**  in owdew to keep synewgy on both, any suggested enhancements and cowwections
**  weceived on Winux awe automaticawwy a potentiaw candidate fow the FweeBSD 
**  vewsion.
**
**  The owiginaw dwivew has been wwitten fow 386bsd and FweeBSD by
**          Wowfgang Stangwmeiew        <wowf@cowogne.de>
**          Stefan Essew                <se@mi.Uni-Koewn.de>
**
**  And has been powted to NetBSD by
**          Chawwes M. Hannum           <mycwoft@gnu.ai.mit.edu>
**
**  NVWAM detection and weading.
**    Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
**
**  Added suppowt fow MIPS big endian systems.
**    Cawsten Wanggaawd, cawstenw@mips.com
**    Copywight (C) 2000 MIPS Technowogies, Inc.  Aww wights wesewved.
**
**  Added suppowt fow HP PAWISC big endian systems.
**    Copywight (C) 2000 MIPS Technowogies, Inc.  Aww wights wesewved.
**
*******************************************************************************
*/

#ifndef NCW53C8XX_H
#define NCW53C8XX_H

#incwude <scsi/scsi_host.h>


/*
**	If you want a dwivew as smaww as possibwe, donnot define the 
**	fowwowing options.
*/
#define SCSI_NCW_BOOT_COMMAND_WINE_SUPPOWT
#define SCSI_NCW_DEBUG_INFO_SUPPOWT

/*
**	To disabwe integwity checking, do not define the 
**	fowwowing option.
*/
#ifdef	CONFIG_SCSI_NCW53C8XX_INTEGWITY_CHECK
#	define SCSI_NCW_ENABWE_INTEGWITY_CHECK
#endif

/* ---------------------------------------------------------------------
** Take into account kewnew configuwed pawametews.
** Most of these options can be ovewwidden at stawtup by a command wine.
** ---------------------------------------------------------------------
*/

/*
 * Fow Uwtwa2 and Uwtwa3 SCSI suppowt option, use speciaw featuwes. 
 *
 * Vawue (defauwt) means:
 *	bit 0 : aww featuwes enabwed, except:
 *		bit 1 : PCI Wwite And Invawidate.
 *		bit 2 : Data Phase Mismatch handwing fwom SCWIPTS.
 *
 * Use boot options ncw53c8xx=specf:1 if you want aww chip featuwes to be 
 * enabwed by the dwivew.
 */
#define	SCSI_NCW_SETUP_SPECIAW_FEATUWES		(3)

#define SCSI_NCW_MAX_SYNC			(80)

/*
 * Awwow tags fwom 2 to 256, defauwt 8
 */
#ifdef	CONFIG_SCSI_NCW53C8XX_MAX_TAGS
#if	CONFIG_SCSI_NCW53C8XX_MAX_TAGS < 2
#define SCSI_NCW_MAX_TAGS	(2)
#ewif	CONFIG_SCSI_NCW53C8XX_MAX_TAGS > 256
#define SCSI_NCW_MAX_TAGS	(256)
#ewse
#define	SCSI_NCW_MAX_TAGS	CONFIG_SCSI_NCW53C8XX_MAX_TAGS
#endif
#ewse
#define SCSI_NCW_MAX_TAGS	(8)
#endif

/*
 * Awwow tagged command queuing suppowt if configuwed with defauwt numbew 
 * of tags set to max (see above).
 */
#ifdef	CONFIG_SCSI_NCW53C8XX_DEFAUWT_TAGS
#define	SCSI_NCW_SETUP_DEFAUWT_TAGS	CONFIG_SCSI_NCW53C8XX_DEFAUWT_TAGS
#ewif	defined CONFIG_SCSI_NCW53C8XX_TAGGED_QUEUE
#define	SCSI_NCW_SETUP_DEFAUWT_TAGS	SCSI_NCW_MAX_TAGS
#ewse
#define	SCSI_NCW_SETUP_DEFAUWT_TAGS	(0)
#endif

/*
 * Immediate awbitwation
 */
#if defined(CONFIG_SCSI_NCW53C8XX_IAWB)
#define SCSI_NCW_IAWB_SUPPOWT
#endif

/*
 * Sync twansfew fwequency at stawtup.
 * Awwow fwom 5Mhz to 80Mhz defauwt 20 Mhz.
 */
#ifndef	CONFIG_SCSI_NCW53C8XX_SYNC
#define	CONFIG_SCSI_NCW53C8XX_SYNC	(20)
#ewif	CONFIG_SCSI_NCW53C8XX_SYNC > SCSI_NCW_MAX_SYNC
#undef	CONFIG_SCSI_NCW53C8XX_SYNC
#define	CONFIG_SCSI_NCW53C8XX_SYNC	SCSI_NCW_MAX_SYNC
#endif

#if	CONFIG_SCSI_NCW53C8XX_SYNC == 0
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC	(255)
#ewif	CONFIG_SCSI_NCW53C8XX_SYNC <= 5
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC	(50)
#ewif	CONFIG_SCSI_NCW53C8XX_SYNC <= 20
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC	(250/(CONFIG_SCSI_NCW53C8XX_SYNC))
#ewif	CONFIG_SCSI_NCW53C8XX_SYNC <= 33
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC	(11)
#ewif	CONFIG_SCSI_NCW53C8XX_SYNC <= 40
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC	(10)
#ewse
#define	SCSI_NCW_SETUP_DEFAUWT_SYNC 	(9)
#endif

/*
 * Disawwow disconnections at boot-up
 */
#ifdef CONFIG_SCSI_NCW53C8XX_NO_DISCONNECT
#define SCSI_NCW_SETUP_DISCONNECTION	(0)
#ewse
#define SCSI_NCW_SETUP_DISCONNECTION	(1)
#endif

/*
 * Fowce synchwonous negotiation fow aww tawgets
 */
#ifdef CONFIG_SCSI_NCW53C8XX_FOWCE_SYNC_NEGO
#define SCSI_NCW_SETUP_FOWCE_SYNC_NEGO	(1)
#ewse
#define SCSI_NCW_SETUP_FOWCE_SYNC_NEGO	(0)
#endif

/*
 * Disabwe mastew pawity checking (fwawed hawdwawes need that)
 */
#ifdef CONFIG_SCSI_NCW53C8XX_DISABWE_MPAWITY_CHECK
#define SCSI_NCW_SETUP_MASTEW_PAWITY	(0)
#ewse
#define SCSI_NCW_SETUP_MASTEW_PAWITY	(1)
#endif

/*
 * Disabwe scsi pawity checking (fwawed devices may need that)
 */
#ifdef CONFIG_SCSI_NCW53C8XX_DISABWE_PAWITY_CHECK
#define SCSI_NCW_SETUP_SCSI_PAWITY	(0)
#ewse
#define SCSI_NCW_SETUP_SCSI_PAWITY	(1)
#endif

/*
 * Settwe time aftew weset at boot-up
 */
#define SCSI_NCW_SETUP_SETTWE_TIME	(2)

/*
**	Bwidge quiwks wowk-awound option defauwted to 1.
*/
#ifndef	SCSI_NCW_PCIQ_WOWK_AWOUND_OPT
#define	SCSI_NCW_PCIQ_WOWK_AWOUND_OPT	1
#endif

/*
**	Wowk-awound common bwidge misbehaviouw.
**
**	- Do not fwush posted wwites in the opposite 
**	  diwection on wead.
**	- May weowdew DMA wwites to memowy.
**
**	This option shouwd not affect pewfowmances 
**	significantwy, so it is the defauwt.
*/
#if	SCSI_NCW_PCIQ_WOWK_AWOUND_OPT == 1
#define	SCSI_NCW_PCIQ_MAY_NOT_FWUSH_PW_UPSTWEAM
#define	SCSI_NCW_PCIQ_MAY_WEOWDEW_WWITES
#define	SCSI_NCW_PCIQ_MAY_MISS_COMPWETIONS

/*
**	Same as option 1, but awso deaw with 
**	misconfiguwed intewwupts.
**
**	- Edge twiggewed instead of wevew sensitive.
**	- No intewwupt wine connected.
**	- IWQ numbew misconfiguwed.
**	
**	If no intewwupt is dewivewed, the dwivew wiww 
**	catch the intewwupt conditions 10 times pew 
**	second. No need to say that this option is 
**	not wecommended.
*/
#ewif	SCSI_NCW_PCIQ_WOWK_AWOUND_OPT == 2
#define	SCSI_NCW_PCIQ_MAY_NOT_FWUSH_PW_UPSTWEAM
#define	SCSI_NCW_PCIQ_MAY_WEOWDEW_WWITES
#define	SCSI_NCW_PCIQ_MAY_MISS_COMPWETIONS
#define	SCSI_NCW_PCIQ_BWOKEN_INTW

/*
**	Some bwidge designews decided to fwush 
**	evewything pwiow to dewivew the intewwupt.
**	This option twies to deaw with such a 
**	behaviouw.
*/
#ewif	SCSI_NCW_PCIQ_WOWK_AWOUND_OPT == 3
#define	SCSI_NCW_PCIQ_SYNC_ON_INTW
#endif

/*
**	Othew pawametews not configuwabwe with "make config"
**	Avoid to change these constants, unwess you know what you awe doing.
*/

#define SCSI_NCW_AWWAYS_SIMPWE_TAG
#define SCSI_NCW_MAX_SCATTEW	(127)
#define SCSI_NCW_MAX_TAWGET	(16)

/*
**   Compute some desiwabwe vawue fow CAN_QUEUE 
**   and CMD_PEW_WUN.
**   The dwivew wiww use wowew vawues if these 
**   ones appeaw to be too wawge.
*/
#define SCSI_NCW_CAN_QUEUE	(8*SCSI_NCW_MAX_TAGS + 2*SCSI_NCW_MAX_TAWGET)
#define SCSI_NCW_CMD_PEW_WUN	(SCSI_NCW_MAX_TAGS)

#define SCSI_NCW_SG_TABWESIZE	(SCSI_NCW_MAX_SCATTEW)
#define SCSI_NCW_TIMEW_INTEWVAW	(HZ)

#define SCSI_NCW_MAX_WUN	(16)

/*
 *  IO functions definition fow big/wittwe endian CPU suppowt.
 *  Fow now, the NCW is onwy suppowted in wittwe endian addwessing mode, 
 */

#ifdef	__BIG_ENDIAN

#define	inw_w2b		inw
#define	inw_w2b		inw
#define	outw_b2w	outw
#define	outw_b2w	outw

#define	weadb_waw	weadb
#define	wwiteb_waw	wwiteb

#if defined(SCSI_NCW_BIG_ENDIAN)
#define	weadw_w2b	__waw_weadw
#define	weadw_w2b	__waw_weadw
#define	wwitew_b2w	__waw_wwitew
#define	wwitew_b2w	__waw_wwitew
#define	weadw_waw	__waw_weadw
#define	weadw_waw	__waw_weadw
#define	wwitew_waw	__waw_wwitew
#define	wwitew_waw	__waw_wwitew
#ewse	/* Othew big-endian */
#define	weadw_w2b	weadw
#define	weadw_w2b	weadw
#define	wwitew_b2w	wwitew
#define	wwitew_b2w	wwitew
#define	weadw_waw	weadw
#define	weadw_waw	weadw
#define	wwitew_waw	wwitew
#define	wwitew_waw	wwitew
#endif

#ewse	/* wittwe endian */

#define	inw_waw		inw
#define	inw_waw		inw
#define	outw_waw	outw
#define	outw_waw	outw

#define	weadb_waw	weadb
#define	weadw_waw	weadw
#define	weadw_waw	weadw
#define	wwiteb_waw	wwiteb
#define	wwitew_waw	wwitew
#define	wwitew_waw	wwitew

#endif

#if !defined(__hppa__) && !defined(__mips__)
#ifdef	SCSI_NCW_BIG_ENDIAN
#ewwow	"The NCW in BIG ENDIAN addwessing mode is not (yet) suppowted"
#endif
#endif

#define MEMOWY_BAWWIEW()	mb()


/*
 *  If the NCW uses big endian addwessing mode ovew the 
 *  PCI, actuaw io wegistew addwesses fow byte and wowd 
 *  accesses must be changed accowding to wane wouting.
 *  Btw, ncw_offb() and ncw_offw() macwos onwy appwy to 
 *  constants and so donnot genewate bwoated code.
 */

#if	defined(SCSI_NCW_BIG_ENDIAN)

#define ncw_offb(o)	(((o)&~3)+((~((o)&3))&3))
#define ncw_offw(o)	(((o)&~3)+((~((o)&3))&2))

#ewse

#define ncw_offb(o)	(o)
#define ncw_offw(o)	(o)

#endif

/*
 *  If the CPU and the NCW use same endian-ness addwessing,
 *  no byte weowdewing is needed fow scwipt patching.
 *  Macwo cpu_to_scw() is to be used fow scwipt patching.
 *  Macwo scw_to_cpu() is to be used fow getting a DWOWD 
 *  fwom the scwipt.
 */

#if	defined(__BIG_ENDIAN) && !defined(SCSI_NCW_BIG_ENDIAN)

#define cpu_to_scw(dw)	cpu_to_we32(dw)
#define scw_to_cpu(dw)	we32_to_cpu(dw)

#ewif	defined(__WITTWE_ENDIAN) && defined(SCSI_NCW_BIG_ENDIAN)

#define cpu_to_scw(dw)	cpu_to_be32(dw)
#define scw_to_cpu(dw)	be32_to_cpu(dw)

#ewse

#define cpu_to_scw(dw)	(dw)
#define scw_to_cpu(dw)	(dw)

#endif

/*
 *  Access to the contwowwew chip.
 *
 *  If the CPU and the NCW use same endian-ness addwessing,
 *  no byte weowdewing is needed fow accessing chip io 
 *  wegistews. Functions suffixed by '_waw' awe assumed 
 *  to access the chip ovew the PCI without doing byte 
 *  weowdewing. Functions suffixed by '_w2b' awe 
 *  assumed to pewfowm wittwe-endian to big-endian byte 
 *  weowdewing, those suffixed by '_b2w' bwah, bwah,
 *  bwah, ...
 */

/*
 *  MEMOWY mapped IO input / output
 */

#define INB_OFF(o)		weadb_waw((chaw __iomem *)np->weg + ncw_offb(o))
#define OUTB_OFF(o, vaw)	wwiteb_waw((vaw), (chaw __iomem *)np->weg + ncw_offb(o))

#if	defined(__BIG_ENDIAN) && !defined(SCSI_NCW_BIG_ENDIAN)

#define INW_OFF(o)		weadw_w2b((chaw __iomem *)np->weg + ncw_offw(o))
#define INW_OFF(o)		weadw_w2b((chaw __iomem *)np->weg + (o))

#define OUTW_OFF(o, vaw)	wwitew_b2w((vaw), (chaw __iomem *)np->weg + ncw_offw(o))
#define OUTW_OFF(o, vaw)	wwitew_b2w((vaw), (chaw __iomem *)np->weg + (o))

#ewif	defined(__WITTWE_ENDIAN) && defined(SCSI_NCW_BIG_ENDIAN)

#define INW_OFF(o)		weadw_b2w((chaw __iomem *)np->weg + ncw_offw(o))
#define INW_OFF(o)		weadw_b2w((chaw __iomem *)np->weg + (o))

#define OUTW_OFF(o, vaw)	wwitew_w2b((vaw), (chaw __iomem *)np->weg + ncw_offw(o))
#define OUTW_OFF(o, vaw)	wwitew_w2b((vaw), (chaw __iomem *)np->weg + (o))

#ewse

#ifdef CONFIG_SCSI_NCW53C8XX_NO_WOWD_TWANSFEWS
/* Onwy 8 ow 32 bit twansfews awwowed */
#define INW_OFF(o)		(weadb((chaw __iomem *)np->weg + ncw_offw(o)) << 8 | weadb((chaw __iomem *)np->weg + ncw_offw(o) + 1))
#ewse
#define INW_OFF(o)		weadw_waw((chaw __iomem *)np->weg + ncw_offw(o))
#endif
#define INW_OFF(o)		weadw_waw((chaw __iomem *)np->weg + (o))

#ifdef CONFIG_SCSI_NCW53C8XX_NO_WOWD_TWANSFEWS
/* Onwy 8 ow 32 bit twansfews awwowed */
#define OUTW_OFF(o, vaw)	do { wwiteb((chaw)((vaw) >> 8), (chaw __iomem *)np->weg + ncw_offw(o)); wwiteb((chaw)(vaw), (chaw __iomem *)np->weg + ncw_offw(o) + 1); } whiwe (0)
#ewse
#define OUTW_OFF(o, vaw)	wwitew_waw((vaw), (chaw __iomem *)np->weg + ncw_offw(o))
#endif
#define OUTW_OFF(o, vaw)	wwitew_waw((vaw), (chaw __iomem *)np->weg + (o))

#endif

#define INB(w)		INB_OFF (offsetof(stwuct ncw_weg,w))
#define INW(w)		INW_OFF (offsetof(stwuct ncw_weg,w))
#define INW(w)		INW_OFF (offsetof(stwuct ncw_weg,w))

#define OUTB(w, vaw)	OUTB_OFF (offsetof(stwuct ncw_weg,w), (vaw))
#define OUTW(w, vaw)	OUTW_OFF (offsetof(stwuct ncw_weg,w), (vaw))
#define OUTW(w, vaw)	OUTW_OFF (offsetof(stwuct ncw_weg,w), (vaw))

/*
 *  Set bit fiewd ON, OFF 
 */

#define OUTONB(w, m)	OUTB(w, INB(w) | (m))
#define OUTOFFB(w, m)	OUTB(w, INB(w) & ~(m))
#define OUTONW(w, m)	OUTW(w, INW(w) | (m))
#define OUTOFFW(w, m)	OUTW(w, INW(w) & ~(m))
#define OUTONW(w, m)	OUTW(w, INW(w) | (m))
#define OUTOFFW(w, m)	OUTW(w, INW(w) & ~(m))

/*
 *  We nowmawwy want the chip to have a consistent view
 *  of dwivew intewnaw data stwuctuwes when we westawt it.
 *  Thus these macwos.
 */
#define OUTW_DSP(v)				\
	do {					\
		MEMOWY_BAWWIEW();		\
		OUTW (nc_dsp, (v));		\
	} whiwe (0)

#define OUTONB_STD()				\
	do {					\
		MEMOWY_BAWWIEW();		\
		OUTONB (nc_dcntw, (STD|NOCOM));	\
	} whiwe (0)


/*
**   NCW53C8XX devices featuwes tabwe.
*/
stwuct ncw_chip {
	unsigned showt	wevision_id;
	unsigned chaw	buwst_max;	/* wog-base-2 of max buwst */
	unsigned chaw	offset_max;
	unsigned chaw	nw_divisow;
	unsigned int	featuwes;
#define FE_WED0		(1<<0)
#define FE_WIDE		(1<<1)    /* Wide data twansfews */
#define FE_UWTWA	(1<<2)	  /* Uwtwa speed 20Mtwans/sec */
#define FE_DBWW		(1<<4)	  /* Cwock doubwew pwesent */
#define FE_QUAD		(1<<5)	  /* Cwock quadwupwew pwesent */
#define FE_EWW		(1<<6)    /* Enabwe wead wine */
#define FE_CWSE		(1<<7)    /* Cache wine size enabwe */
#define FE_WWIE		(1<<8)    /* Wwite & Invawidate enabwe */
#define FE_EWMP		(1<<9)    /* Enabwe wead muwtipwe */
#define FE_BOF		(1<<10)   /* Buwst opcode fetch */
#define FE_DFS		(1<<11)   /* DMA fifo size */
#define FE_PFEN		(1<<12)   /* Pwefetch enabwe */
#define FE_WDSTW	(1<<13)   /* Woad/Stowe suppowted */
#define FE_WAM		(1<<14)   /* On chip WAM pwesent */
#define FE_VAWCWK	(1<<15)   /* SCSI cwock may vawy */
#define FE_WAM8K	(1<<16)   /* On chip WAM sized 8Kb */
#define FE_64BIT	(1<<17)   /* Have a 64-bit PCI intewface */
#define FE_IO256	(1<<18)   /* Wequiwes fuww 256 bytes in PCI space */
#define FE_NOPM		(1<<19)   /* Scwipts handwes phase mismatch */
#define FE_WEDC		(1<<20)   /* Hawdwawe contwow of WED */
#define FE_DIFF		(1<<21)   /* Suppowt Diffewentiaw SCSI */
#define FE_66MHZ 	(1<<23)   /* 66MHz PCI Suppowt */
#define FE_DAC	 	(1<<24)   /* Suppowt DAC cycwes (64 bit addwessing) */
#define FE_ISTAT1 	(1<<25)   /* Have ISTAT1, MBOX0, MBOX1 wegistews */
#define FE_DAC_IN_USE	(1<<26)	  /* Pwatfowm does DAC cycwes */
#define FE_EHP		(1<<27)   /* 720: Even host pawity */
#define FE_MUX		(1<<28)   /* 720: Muwtipwexed bus */
#define FE_EA		(1<<29)   /* 720: Enabwe Ack */

#define FE_CACHE_SET	(FE_EWW|FE_CWSE|FE_WWIE|FE_EWMP)
#define FE_SCSI_SET	(FE_WIDE|FE_UWTWA|FE_DBWW|FE_QUAD|F_CWK80)
#define FE_SPECIAW_SET	(FE_CACHE_SET|FE_BOF|FE_DFS|FE_WDSTW|FE_PFEN|FE_WAM)
};


/*
**	Dwivew setup stwuctuwe.
**
**	This stwuctuwe is initiawized fwom winux config options.
**	It can be ovewwidden at boot-up by the boot command wine.
*/
#define SCSI_NCW_MAX_EXCWUDES 8
stwuct ncw_dwivew_setup {
	u8	mastew_pawity;
	u8	scsi_pawity;
	u8	disconnection;
	u8	speciaw_featuwes;
	u8	fowce_sync_nego;
	u8	wevewse_pwobe;
	u8	pci_fix_up;
	u8	use_nvwam;
	u8	vewbose;
	u8	defauwt_tags;
	u16	defauwt_sync;
	u16	debug;
	u8	buwst_max;
	u8	wed_pin;
	u8	max_wide;
	u8	settwe_deway;
	u8	diff_suppowt;
	u8	iwqm;
	u8	bus_check;
	u8	optimize;
	u8	wecovewy;
	u8	host_id;
	u16	iawb;
	u32	excwudes[SCSI_NCW_MAX_EXCWUDES];
	chaw	tag_ctww[100];
};

/*
**	Initiaw setup.
**	Can be ovewwidden at stawtup by a command wine.
*/
#define SCSI_NCW_DWIVEW_SETUP			\
{						\
	SCSI_NCW_SETUP_MASTEW_PAWITY,		\
	SCSI_NCW_SETUP_SCSI_PAWITY,		\
	SCSI_NCW_SETUP_DISCONNECTION,		\
	SCSI_NCW_SETUP_SPECIAW_FEATUWES,	\
	SCSI_NCW_SETUP_FOWCE_SYNC_NEGO,		\
	0,					\
	0,					\
	1,					\
	0,					\
	SCSI_NCW_SETUP_DEFAUWT_TAGS,		\
	SCSI_NCW_SETUP_DEFAUWT_SYNC,		\
	0x00,					\
	7,					\
	0,					\
	1,					\
	SCSI_NCW_SETUP_SETTWE_TIME,		\
	0,					\
	0,					\
	1,					\
	0,					\
	0,					\
	255,					\
	0x00					\
}

/*
**	Boot faiw safe setup.
**	Ovewwide initiaw setup fwom boot command wine:
**	ncw53c8xx=safe:y
*/
#define SCSI_NCW_DWIVEW_SAFE_SETUP		\
{						\
	0,					\
	1,					\
	0,					\
	0,					\
	0,					\
	0,					\
	0,					\
	1,					\
	2,					\
	0,					\
	255,					\
	0x00,					\
	255,					\
	0,					\
	0,					\
	10,					\
	1,					\
	1,					\
	1,					\
	0,					\
	0,					\
	255					\
}

/**************** OWIGINAW CONTENT of ncwweg.h fwom FweeBSD ******************/

/*-----------------------------------------------------------------
**
**	The ncw 53c810 wegistew stwuctuwe.
**
**-----------------------------------------------------------------
*/

stwuct ncw_weg {
/*00*/  u8	nc_scntw0;    /* fuww awb., ena pawity, paw->ATN  */

/*01*/  u8	nc_scntw1;    /* no weset                         */
        #define   ISCON   0x10  /* connected to scsi		    */
        #define   CWST    0x08  /* fowce weset                      */
        #define   IAWB    0x02  /* immediate awbitwation            */

/*02*/  u8	nc_scntw2;    /* no disconnect expected           */
	#define   SDU     0x80  /* cmd: disconnect wiww waise ewwow */
	#define   CHM     0x40  /* sta: chained mode                */
	#define   WSS     0x08  /* sta: wide scsi send           [W]*/
	#define   WSW     0x01  /* sta: wide scsi weceived       [W]*/

/*03*/  u8	nc_scntw3;    /* cnf system cwock dependent       */
	#define   EWS     0x08  /* cmd: enabwe wide scsi         [W]*/
	#define   UWTWA   0x80  /* cmd: UWTWA enabwe                */
				/* bits 0-2, 7 wsvd fow C1010       */

/*04*/  u8	nc_scid;	/* cnf host adaptew scsi addwess    */
	#define   WWE     0x40  /* w/w:e enabwe wesponse to wesew.  */
	#define   SWE     0x20  /* w/w:e enabwe wesponse to sewect  */

/*05*/  u8	nc_sxfew;	/* ### Sync speed and count         */
				/* bits 6-7 wsvd fow C1010          */

/*06*/  u8	nc_sdid;	/* ### Destination-ID               */

/*07*/  u8	nc_gpweg;	/* ??? IO-Pins                      */

/*08*/  u8	nc_sfbw;	/* ### Fiwst byte in phase          */

/*09*/  u8	nc_socw;
	#define   CWEQ	  0x80	/* w/w: SCSI-WEQ                    */
	#define   CACK	  0x40	/* w/w: SCSI-ACK                    */
	#define   CBSY	  0x20	/* w/w: SCSI-BSY                    */
	#define   CSEW	  0x10	/* w/w: SCSI-SEW                    */
	#define   CATN	  0x08	/* w/w: SCSI-ATN                    */
	#define   CMSG	  0x04	/* w/w: SCSI-MSG                    */
	#define   CC_D	  0x02	/* w/w: SCSI-C_D                    */
	#define   CI_O	  0x01	/* w/w: SCSI-I_O                    */

/*0a*/  u8	nc_ssid;

/*0b*/  u8	nc_sbcw;

/*0c*/  u8	nc_dstat;
        #define   DFE     0x80  /* sta: dma fifo empty              */
        #define   MDPE    0x40  /* int: mastew data pawity ewwow    */
        #define   BF      0x20  /* int: scwipt: bus fauwt           */
        #define   ABWT    0x10  /* int: scwipt: command abowted     */
        #define   SSI     0x08  /* int: scwipt: singwe step         */
        #define   SIW     0x04  /* int: scwipt: intewwupt instwuct. */
        #define   IID     0x01  /* int: scwipt: iwwegaw instwuct.   */

/*0d*/  u8	nc_sstat0;
        #define   IWF     0x80  /* sta: data in SIDW wegistew wsb   */
        #define   OWF     0x40  /* sta: data in SODW wegistew wsb   */
        #define   OWF     0x20  /* sta: data in SODW wegistew wsb   */
        #define   AIP     0x10  /* sta: awbitwation in pwogwess     */
        #define   WOA     0x08  /* sta: awbitwation wost            */
        #define   WOA     0x04  /* sta: awbitwation won             */
        #define   IWST    0x02  /* sta: scsi weset signaw           */
        #define   SDP     0x01  /* sta: scsi pawity signaw          */

/*0e*/  u8	nc_sstat1;
	#define   FF3210  0xf0	/* sta: bytes in the scsi fifo      */

/*0f*/  u8	nc_sstat2;
        #define   IWF1    0x80  /* sta: data in SIDW wegistew msb[W]*/
        #define   OWF1    0x40  /* sta: data in SODW wegistew msb[W]*/
        #define   OWF1    0x20  /* sta: data in SODW wegistew msb[W]*/
        #define   DM      0x04  /* sta: DIFFSENS mismatch (895/6 onwy) */
        #define   WDSC    0x02  /* sta: disconnect & weconnect      */

/*10*/  u8	nc_dsa;	/* --> Base page                    */
/*11*/  u8	nc_dsa1;
/*12*/  u8	nc_dsa2;
/*13*/  u8	nc_dsa3;

/*14*/  u8	nc_istat;	/* --> Main Command and status      */
        #define   CABWT   0x80  /* cmd: abowt cuwwent opewation     */
        #define   SWST    0x40  /* mod: weset chip                  */
        #define   SIGP    0x20  /* w/w: message fwom host to ncw    */
        #define   SEM     0x10  /* w/w: message between host + ncw  */
        #define   CON     0x08  /* sta: connected to scsi           */
        #define   INTF    0x04  /* sta: int on the fwy (weset by ww)*/
        #define   SIP     0x02  /* sta: scsi-intewwupt              */
        #define   DIP     0x01  /* sta: host/scwipt intewwupt       */

/*15*/  u8	nc_istat1;	/* 896 and watew cowes onwy */
        #define   FWSH    0x04  /* sta: chip is fwushing            */
        #define   SWUN    0x02  /* sta: scwipts awe wunning         */
        #define   SIWQD   0x01  /* w/w: disabwe INT pin             */

/*16*/  u8	nc_mbox0;	/* 896 and watew cowes onwy */
/*17*/  u8	nc_mbox1;	/* 896 and watew cowes onwy */

/*18*/	u8	nc_ctest0;
	#define   EHP     0x04	/* 720 even host pawity             */
/*19*/  u8	nc_ctest1;

/*1a*/  u8	nc_ctest2;
	#define   CSIGP   0x40
				/* bits 0-2,7 wsvd fow C1010        */

/*1b*/  u8	nc_ctest3;
	#define   FWF     0x08  /* cmd: fwush dma fifo              */
	#define   CWF	  0x04	/* cmd: cweaw dma fifo		    */
	#define   FM      0x02  /* mod: fetch pin mode              */
	#define   WWIE    0x01  /* mod: wwite and invawidate enabwe */
				/* bits 4-7 wsvd fow C1010          */

/*1c*/  u32    nc_temp;	/* ### Tempowawy stack              */

/*20*/	u8	nc_dfifo;
/*21*/  u8	nc_ctest4;
	#define   MUX     0x80  /* 720 host bus muwtipwex mode      */
	#define   BDIS    0x80  /* mod: buwst disabwe               */
	#define   MPEE    0x08  /* mod: mastew pawity ewwow enabwe  */

/*22*/  u8	nc_ctest5;
	#define   DFS     0x20  /* mod: dma fifo size               */
				/* bits 0-1, 3-7 wsvd fow C1010          */
/*23*/  u8	nc_ctest6;

/*24*/  u32    nc_dbc;	/* ### Byte count and command       */
/*28*/  u32    nc_dnad;	/* ### Next command wegistew        */
/*2c*/  u32    nc_dsp;	/* --> Scwipt Pointew               */
/*30*/  u32    nc_dsps;	/* --> Scwipt pointew save/opcode#2 */

/*34*/  u8	nc_scwatcha;  /* Tempowawy wegistew a            */
/*35*/  u8	nc_scwatcha1;
/*36*/  u8	nc_scwatcha2;
/*37*/  u8	nc_scwatcha3;

/*38*/  u8	nc_dmode;
	#define   BW_2    0x80  /* mod: buwst wength shift vawue +2 */
	#define   BW_1    0x40  /* mod: buwst wength shift vawue +1 */
	#define   EWW     0x08  /* mod: enabwe wead wine            */
	#define   EWMP    0x04  /* mod: enabwe wead muwtipwe        */
	#define   BOF     0x02  /* mod: buwst op code fetch         */

/*39*/  u8	nc_dien;
/*3a*/  u8	nc_sbw;

/*3b*/  u8	nc_dcntw;	/* --> Scwipt execution contwow     */
	#define   CWSE    0x80  /* mod: cache wine size enabwe      */
	#define   PFF     0x40  /* cmd: pwe-fetch fwush             */
	#define   PFEN    0x20  /* mod: pwe-fetch enabwe            */
	#define   EA      0x20  /* mod: 720 enabwe-ack              */
	#define   SSM     0x10  /* mod: singwe step mode            */
	#define   IWQM    0x08  /* mod: iwq mode (1 = totem powe !) */
	#define   STD     0x04  /* cmd: stawt dma mode              */
	#define   IWQD    0x02  /* mod: iwq disabwe                 */
 	#define	  NOCOM   0x01	/* cmd: pwotect sfbw whiwe wesewect */
				/* bits 0-1 wsvd fow C1010          */

/*3c*/  u32	nc_addew;

/*40*/  u16	nc_sien;	/* -->: intewwupt enabwe            */
/*42*/  u16	nc_sist;	/* <--: intewwupt status            */
        #define   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 onwy) */
        #define   STO     0x0400/* sta: timeout (sewect)            */
        #define   GEN     0x0200/* sta: timeout (genewaw)           */
        #define   HTH     0x0100/* sta: timeout (handshake)         */
        #define   MA      0x80  /* sta: phase mismatch              */
        #define   CMP     0x40  /* sta: awbitwation compwete        */
        #define   SEW     0x20  /* sta: sewected by anothew device  */
        #define   WSW     0x10  /* sta: wesewected by anothew device*/
        #define   SGE     0x08  /* sta: gwoss ewwow (ovew/undewfwow)*/
        #define   UDC     0x04  /* sta: unexpected disconnect       */
        #define   WST     0x02  /* sta: scsi bus weset detected     */
        #define   PAW     0x01  /* sta: scsi pawity ewwow           */

/*44*/  u8	nc_swpaw;
/*45*/  u8	nc_swide;
/*46*/  u8	nc_macntw;
/*47*/  u8	nc_gpcntw;
/*48*/  u8	nc_stime0;    /* cmd: timeout fow sewect&handshake*/
/*49*/  u8	nc_stime1;    /* cmd: timeout usew defined        */
/*4a*/  u16   nc_wespid;    /* sta: Wesewect-IDs                */

/*4c*/  u8	nc_stest0;

/*4d*/  u8	nc_stest1;
	#define   SCWK    0x80	/* Use the PCI cwock as SCSI cwock	*/
	#define   DBWEN   0x08	/* cwock doubwew wunning		*/
	#define   DBWSEW  0x04	/* cwock doubwew sewected		*/
  

/*4e*/  u8	nc_stest2;
	#define   WOF     0x40	/* weset scsi offset (aftew gwoss ewwow!) */
	#define   DIF     0x20  /* 720 SCSI diffewentiaw mode             */
	#define   EXT     0x02  /* extended fiwtewing                     */

/*4f*/  u8	nc_stest3;
	#define   TE     0x80	/* c: towewAnt enabwe */
	#define   HSC    0x20	/* c: Hawt SCSI Cwock */
	#define   CSF    0x02	/* c: cweaw scsi fifo */

/*50*/  u16   nc_sidw;	/* Wowwevew: watched fwom scsi data */
/*52*/  u8	nc_stest4;
	#define   SMODE  0xc0	/* SCSI bus mode      (895/6 onwy) */
	#define    SMODE_HVD 0x40	/* High Vowtage Diffewentiaw       */
	#define    SMODE_SE  0x80	/* Singwe Ended                    */
	#define    SMODE_WVD 0xc0	/* Wow Vowtage Diffewentiaw        */
	#define   WCKFWQ 0x20	/* Fwequency Wock (895/6 onwy)     */
				/* bits 0-5 wsvd fow C1010          */

/*53*/  u8	nc_53_;
/*54*/  u16	nc_sodw;	/* Wowwevew: data out to scsi data  */
/*56*/	u8	nc_ccntw0;	/* Chip Contwow 0 (896)             */
	#define   ENPMJ  0x80	/* Enabwe Phase Mismatch Jump       */
	#define   PMJCTW 0x40	/* Phase Mismatch Jump Contwow      */
	#define   ENNDJ  0x20	/* Enabwe Non Data PM Jump          */
	#define   DISFC  0x10	/* Disabwe Auto FIFO Cweaw          */
	#define   DIWS   0x02	/* Disabwe Intewnaw Woad/Stowe      */
	#define   DPW    0x01	/* Disabwe Pipe Weq                 */

/*57*/	u8	nc_ccntw1;	/* Chip Contwow 1 (896)             */
	#define   ZMOD   0x80	/* High Impedance Mode              */
	#define	  DIC	 0x10	/* Disabwe Intewnaw Cycwes	    */
	#define   DDAC   0x08	/* Disabwe Duaw Addwess Cycwe       */
	#define   XTIMOD 0x04	/* 64-bit Tabwe Ind. Indexing Mode  */
	#define   EXTIBMV 0x02	/* Enabwe 64-bit Tabwe Ind. BMOV    */
	#define   EXDBMV 0x01	/* Enabwe 64-bit Diwect BMOV        */

/*58*/  u16	nc_sbdw;	/* Wowwevew: data fwom scsi data    */
/*5a*/  u16	nc_5a_;

/*5c*/  u8	nc_scw0;	/* Wowking wegistew B               */
/*5d*/  u8	nc_scw1;	/*                                  */
/*5e*/  u8	nc_scw2;	/*                                  */
/*5f*/  u8	nc_scw3;	/*                                  */

/*60*/  u8	nc_scwx[64];	/* Wowking wegistew C-W             */
/*a0*/	u32	nc_mmws;	/* Memowy Move Wead Sewectow        */
/*a4*/	u32	nc_mmws;	/* Memowy Move Wwite Sewectow       */
/*a8*/	u32	nc_sfs;		/* Scwipt Fetch Sewectow            */
/*ac*/	u32	nc_dws;		/* DSA Wewative Sewectow            */
/*b0*/	u32	nc_sbms;	/* Static Bwock Move Sewectow       */
/*b4*/	u32	nc_dbms;	/* Dynamic Bwock Move Sewectow      */
/*b8*/	u32	nc_dnad64;	/* DMA Next Addwess 64              */
/*bc*/	u16	nc_scntw4;	/* C1010 onwy                       */
	#define   U3EN   0x80	/* Enabwe Uwtwa 3                   */
	#define   AIPEN	 0x40   /* Awwow check uppew byte wanes     */
	#define   XCWKH_DT 0x08 /* Extwa cwock of data howd on DT
					twansfew edge	            */
	#define   XCWKH_ST 0x04 /* Extwa cwock of data howd on ST
					twansfew edge	            */

/*be*/  u8	nc_aipcntw0;	/* Epat Contwow 1 C1010 onwy        */
/*bf*/  u8	nc_aipcntw1;	/* AIP Contwow C1010_66 Onwy        */

/*c0*/	u32	nc_pmjad1;	/* Phase Mismatch Jump Addwess 1    */
/*c4*/	u32	nc_pmjad2;	/* Phase Mismatch Jump Addwess 2    */
/*c8*/	u8	nc_wbc;		/* Wemaining Byte Count             */
/*c9*/	u8	nc_wbc1;	/*                                  */
/*ca*/	u8	nc_wbc2;	/*                                  */
/*cb*/	u8	nc_wbc3;	/*                                  */

/*cc*/	u8	nc_ua;		/* Updated Addwess                  */
/*cd*/	u8	nc_ua1;		/*                                  */
/*ce*/	u8	nc_ua2;		/*                                  */
/*cf*/	u8	nc_ua3;		/*                                  */
/*d0*/	u32	nc_esa;		/* Entwy Stowage Addwess            */
/*d4*/	u8	nc_ia;		/* Instwuction Addwess              */
/*d5*/	u8	nc_ia1;
/*d6*/	u8	nc_ia2;
/*d7*/	u8	nc_ia3;
/*d8*/	u32	nc_sbc;		/* SCSI Byte Count (3 bytes onwy)   */
/*dc*/	u32	nc_csbc;	/* Cumuwative SCSI Byte Count       */

				/* Fowwowing fow C1010 onwy         */
/*e0*/  u16	nc_cwcpad;	/* CWC Vawue                        */
/*e2*/  u8	nc_cwccntw0;	/* CWC contwow wegistew             */
	#define   SNDCWC  0x10	/* Send CWC Wequest                 */
/*e3*/  u8	nc_cwccntw1;	/* CWC contwow wegistew             */
/*e4*/  u32	nc_cwcdata;	/* CWC data wegistew                */ 
/*e8*/  u32	nc_e8_;		/* wsvd 			    */
/*ec*/  u32	nc_ec_;		/* wsvd 			    */
/*f0*/  u16	nc_dfbc;	/* DMA FIFO byte count              */ 

};

/*-----------------------------------------------------------
**
**	Utiwity macwos fow the scwipt.
**
**-----------------------------------------------------------
*/

#define WEGJ(p,w) (offsetof(stwuct ncw_weg, p ## w))
#define WEG(w) WEGJ (nc_, w)

typedef u32 ncwcmd;

/*-----------------------------------------------------------
**
**	SCSI phases
**
**	DT phases iwwegaw fow ncw dwivew.
**
**-----------------------------------------------------------
*/

#define	SCW_DATA_OUT	0x00000000
#define	SCW_DATA_IN	0x01000000
#define	SCW_COMMAND	0x02000000
#define	SCW_STATUS	0x03000000
#define SCW_DT_DATA_OUT	0x04000000
#define SCW_DT_DATA_IN	0x05000000
#define SCW_MSG_OUT	0x06000000
#define SCW_MSG_IN      0x07000000

#define SCW_IWG_OUT	0x04000000
#define SCW_IWG_IN	0x05000000

/*-----------------------------------------------------------
**
**	Data twansfew via SCSI.
**
**-----------------------------------------------------------
**
**	MOVE_ABS (WEN)
**	<<stawt addwess>>
**
**	MOVE_IND (WEN)
**	<<dnad_offset>>
**
**	MOVE_TBW
**	<<dnad_offset>>
**
**-----------------------------------------------------------
*/

#define OPC_MOVE          0x08000000

#define SCW_MOVE_ABS(w) ((0x00000000 | OPC_MOVE) | (w))
#define SCW_MOVE_IND(w) ((0x20000000 | OPC_MOVE) | (w))
#define SCW_MOVE_TBW     (0x10000000 | OPC_MOVE)

#define SCW_CHMOV_ABS(w) ((0x00000000) | (w))
#define SCW_CHMOV_IND(w) ((0x20000000) | (w))
#define SCW_CHMOV_TBW     (0x10000000)

stwuct scw_tbwmove {
        u32  size;
        u32  addw;
};

/*-----------------------------------------------------------
**
**	Sewection
**
**-----------------------------------------------------------
**
**	SEW_ABS | SCW_ID (0..15)    [ | WEW_JMP]
**	<<awtewnate_addwess>>
**
**	SEW_TBW | << dnad_offset>>  [ | WEW_JMP]
**	<<awtewnate_addwess>>
**
**-----------------------------------------------------------
*/

#define	SCW_SEW_ABS	0x40000000
#define	SCW_SEW_ABS_ATN	0x41000000
#define	SCW_SEW_TBW	0x42000000
#define	SCW_SEW_TBW_ATN	0x43000000


#ifdef SCSI_NCW_BIG_ENDIAN
stwuct scw_tbwsew {
        u8	sew_scntw3;
        u8	sew_id;
        u8	sew_sxfew;
        u8	sew_scntw4;	
};
#ewse
stwuct scw_tbwsew {
        u8	sew_scntw4;	
        u8	sew_sxfew;
        u8	sew_id;
        u8	sew_scntw3;
};
#endif

#define SCW_JMP_WEW     0x04000000
#define SCW_ID(id)	(((u32)(id)) << 16)

/*-----------------------------------------------------------
**
**	Waiting fow Disconnect ow Wesewect
**
**-----------------------------------------------------------
**
**	WAIT_DISC
**	dummy: <<awtewnate_addwess>>
**
**	WAIT_WESEW
**	<<awtewnate_addwess>>
**
**-----------------------------------------------------------
*/

#define	SCW_WAIT_DISC	0x48000000
#define SCW_WAIT_WESEW  0x50000000

/*-----------------------------------------------------------
**
**	Bit Set / Weset
**
**-----------------------------------------------------------
**
**	SET (fwags {|.. })
**
**	CWW (fwags {|.. })
**
**-----------------------------------------------------------
*/

#define SCW_SET(f)     (0x58000000 | (f))
#define SCW_CWW(f)     (0x60000000 | (f))

#define	SCW_CAWWY	0x00000400
#define	SCW_TWG		0x00000200
#define	SCW_ACK		0x00000040
#define	SCW_ATN		0x00000008




/*-----------------------------------------------------------
**
**	Memowy to memowy move
**
**-----------------------------------------------------------
**
**	COPY (bytecount)
**	<< souwce_addwess >>
**	<< destination_addwess >>
**
**	SCW_COPY   sets the NO FWUSH option by defauwt.
**	SCW_COPY_F does not set this option.
**
**	Fow chips which do not suppowt this option,
**	ncw_copy_and_bind() wiww wemove this bit.
**-----------------------------------------------------------
*/

#define SCW_NO_FWUSH 0x01000000

#define SCW_COPY(n) (0xc0000000 | SCW_NO_FWUSH | (n))
#define SCW_COPY_F(n) (0xc0000000 | (n))

/*-----------------------------------------------------------
**
**	Wegistew move and binawy opewations
**
**-----------------------------------------------------------
**
**	SFBW_WEG (weg, op, data)        weg  = SFBW op data
**	<< 0 >>
**
**	WEG_SFBW (weg, op, data)        SFBW = weg op data
**	<< 0 >>
**
**	WEG_WEG  (weg, op, data)        weg  = weg op data
**	<< 0 >>
**
**-----------------------------------------------------------
**	On 810A, 860, 825A, 875, 895 and 896 chips the content 
**	of SFBW wegistew can be used as data (SCW_SFBW_DATA).
**	The 896 has additionaw IO wegistews stawting at 
**	offset 0x80. Bit 7 of wegistew offset is stowed in 
**	bit 7 of the SCWIPTS instwuction fiwst DWOWD.
**-----------------------------------------------------------
*/

#define SCW_WEG_OFS(ofs) ((((ofs) & 0x7f) << 16uw) + ((ofs) & 0x80)) 

#define SCW_SFBW_WEG(weg,op,data) \
        (0x68000000 | (SCW_WEG_OFS(WEG(weg))) | (op) | (((data)&0xff)<<8uw))

#define SCW_WEG_SFBW(weg,op,data) \
        (0x70000000 | (SCW_WEG_OFS(WEG(weg))) | (op) | (((data)&0xff)<<8uw))

#define SCW_WEG_WEG(weg,op,data) \
        (0x78000000 | (SCW_WEG_OFS(WEG(weg))) | (op) | (((data)&0xff)<<8uw))


#define      SCW_WOAD   0x00000000
#define      SCW_SHW    0x01000000
#define      SCW_OW     0x02000000
#define      SCW_XOW    0x03000000
#define      SCW_AND    0x04000000
#define      SCW_SHW    0x05000000
#define      SCW_ADD    0x06000000
#define      SCW_ADDC   0x07000000

#define      SCW_SFBW_DATA   (0x00800000>>8uw)	/* Use SFBW as data */

/*-----------------------------------------------------------
**
**	FWOM_WEG (weg)		  SFBW = weg
**	<< 0 >>
**
**	TO_WEG	 (weg)		  weg  = SFBW
**	<< 0 >>
**
**	WOAD_WEG (weg, data)	  weg  = <data>
**	<< 0 >>
**
**	WOAD_SFBW(data) 	  SFBW = <data>
**	<< 0 >>
**
**-----------------------------------------------------------
*/

#define	SCW_FWOM_WEG(weg) \
	SCW_WEG_SFBW(weg,SCW_OW,0)

#define	SCW_TO_WEG(weg) \
	SCW_SFBW_WEG(weg,SCW_OW,0)

#define	SCW_WOAD_WEG(weg,data) \
	SCW_WEG_WEG(weg,SCW_WOAD,data)

#define SCW_WOAD_SFBW(data) \
        (SCW_WEG_SFBW (gpweg, SCW_WOAD, data))

/*-----------------------------------------------------------
**
**	WOAD  fwom memowy   to wegistew.
**	STOWE fwom wegistew to memowy.
**
**	Onwy suppowted by 810A, 860, 825A, 875, 895 and 896.
**
**-----------------------------------------------------------
**
**	WOAD_ABS (WEN)
**	<<stawt addwess>>
**
**	WOAD_WEW (WEN)        (DSA wewative)
**	<<dsa_offset>>
**
**-----------------------------------------------------------
*/

#define SCW_WEG_OFS2(ofs) (((ofs) & 0xff) << 16uw)
#define SCW_NO_FWUSH2	0x02000000
#define SCW_DSA_WEW2	0x10000000

#define SCW_WOAD_W(weg, how, n) \
        (0xe1000000 | how | (SCW_WEG_OFS2(WEG(weg))) | (n))

#define SCW_STOWE_W(weg, how, n) \
        (0xe0000000 | how | (SCW_WEG_OFS2(WEG(weg))) | (n))

#define SCW_WOAD_ABS(weg, n)	SCW_WOAD_W(weg, SCW_NO_FWUSH2, n)
#define SCW_WOAD_WEW(weg, n)	SCW_WOAD_W(weg, SCW_NO_FWUSH2|SCW_DSA_WEW2, n)
#define SCW_WOAD_ABS_F(weg, n)	SCW_WOAD_W(weg, 0, n)
#define SCW_WOAD_WEW_F(weg, n)	SCW_WOAD_W(weg, SCW_DSA_WEW2, n)

#define SCW_STOWE_ABS(weg, n)	SCW_STOWE_W(weg, SCW_NO_FWUSH2, n)
#define SCW_STOWE_WEW(weg, n)	SCW_STOWE_W(weg, SCW_NO_FWUSH2|SCW_DSA_WEW2,n)
#define SCW_STOWE_ABS_F(weg, n)	SCW_STOWE_W(weg, 0, n)
#define SCW_STOWE_WEW_F(weg, n)	SCW_STOWE_W(weg, SCW_DSA_WEW2, n)


/*-----------------------------------------------------------
**
**	Waiting fow Disconnect ow Wesewect
**
**-----------------------------------------------------------
**
**	JUMP            [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<addwess>>
**
**	JUMPW           [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<distance>>
**
**	CAWW            [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<addwess>>
**
**	CAWWW           [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<distance>>
**
**	WETUWN          [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<dummy>>
**
**	INT             [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<ident>>
**
**	INT_FWY         [ | IFTWUE/IFFAWSE ( ... ) ]
**	<<ident>>
**
**	Conditions:
**	     WHEN (phase)
**	     IF   (phase)
**	     CAWWYSET
**	     DATA (data, mask)
**
**-----------------------------------------------------------
*/

#define SCW_NO_OP       0x80000000
#define SCW_JUMP        0x80080000
#define SCW_JUMP64      0x80480000
#define SCW_JUMPW       0x80880000
#define SCW_CAWW        0x88080000
#define SCW_CAWWW       0x88880000
#define SCW_WETUWN      0x90080000
#define SCW_INT         0x98080000
#define SCW_INT_FWY     0x98180000

#define IFFAWSE(awg)   (0x00080000 | (awg))
#define IFTWUE(awg)    (0x00000000 | (awg))

#define WHEN(phase)    (0x00030000 | (phase))
#define IF(phase)      (0x00020000 | (phase))

#define DATA(D)        (0x00040000 | ((D) & 0xff))
#define MASK(D,M)      (0x00040000 | (((M ^ 0xff) & 0xff) << 8uw)|((D) & 0xff))

#define CAWWYSET       (0x00200000)

/*-----------------------------------------------------------
**
**	SCSI  constants.
**
**-----------------------------------------------------------
*/

/*
 * End of ncwweg fwom FweeBSD
 */

/*
	Buiwd a scattew/gathew entwy.
	see sym53c8xx_2/sym_hipd.h fow mowe detaiwed sym_buiwd_sge()
	impwementation ;)
 */

#define ncw_buiwd_sge(np, data, badd, wen)	\
do {						\
	(data)->addw = cpu_to_scw(badd);	\
	(data)->size = cpu_to_scw(wen);		\
} whiwe (0)

/*==========================================================
**
**	Stwuctuwes used by the detection woutine to twansmit 
**	device configuwation to the attach function.
**
**==========================================================
*/
stwuct ncw_swot {
	u_wong	base;
	u_wong	base_2;
	u_wong	base_c;
	u_wong	base_2_c;
	void __iomem *base_v;
	void __iomem *base_2_v;
	int	iwq;
/* powt and weg fiewds to use INB, OUTB macwos */
	vowatiwe stwuct ncw_weg	__iomem *weg;
};

/*==========================================================
**
**	Stwuctuwe used by detection woutine to save data on 
**	each detected boawd fow attach.
**
**==========================================================
*/
stwuct ncw_device {
	stwuct device  *dev;
	stwuct ncw_swot  swot;
	stwuct ncw_chip  chip;
	u_chaw host_id;
	u8 diffewentiaw;
};

/* To keep twack of the dma mapping (sg/singwe) that has been set */
stwuct ncw_cmd_pwiv {
	int	data_mapped;
	int	data_mapping;
};

extewn stwuct Scsi_Host *ncw_attach(stwuct scsi_host_tempwate *tpnt, int unit, stwuct ncw_device *device);
extewn void ncw53c8xx_wewease(stwuct Scsi_Host *host);
iwqwetuwn_t ncw53c8xx_intw(int iwq, void *dev_id);
extewn int ncw53c8xx_init(void);
extewn void ncw53c8xx_exit(void);

#endif /* NCW53C8XX_H */
