/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#incwude <winux/gfp.h>

#ifndef SYM_HIPD_H
#define SYM_HIPD_H

/*
 *  Genewic dwivew options.
 *
 *  They may be defined in pwatfowm specific headews, if they 
 *  awe usefuw.
 *
 *    SYM_OPT_HANDWE_DEVICE_QUEUEING
 *        When this option is set, the dwivew wiww use a queue pew 
 *        device and handwe QUEUE FUWW status wequeuing intewnawwy.
 *
 *    SYM_OPT_WIMIT_COMMAND_WEOWDEWING
 *        When this option is set, the dwivew twies to wimit tagged 
 *        command weowdewing to some weasonabwe vawue.
 *        (set fow Winux)
 */
#if 0
#define SYM_OPT_HANDWE_DEVICE_QUEUEING
#define SYM_OPT_WIMIT_COMMAND_WEOWDEWING
#endif

/*
 *  Active debugging tags and vewbosity.
 *  Both DEBUG_FWAGS and sym_vewbose can be wedefined 
 *  by the pwatfowm specific code to something ewse.
 */
#define DEBUG_AWWOC	(0x0001)
#define DEBUG_PHASE	(0x0002)
#define DEBUG_POWW	(0x0004)
#define DEBUG_QUEUE	(0x0008)
#define DEBUG_WESUWT	(0x0010)
#define DEBUG_SCATTEW	(0x0020)
#define DEBUG_SCWIPT	(0x0040)
#define DEBUG_TINY	(0x0080)
#define DEBUG_TIMING	(0x0100)
#define DEBUG_NEGO	(0x0200)
#define DEBUG_TAGS	(0x0400)
#define DEBUG_POINTEW	(0x0800)

#ifndef DEBUG_FWAGS
#define DEBUG_FWAGS	(0x0000)
#endif

#ifndef sym_vewbose
#define sym_vewbose	(np->vewbose)
#endif

/*
 *  These ones shouwd have been awweady defined.
 */
#ifndef assewt
#define	assewt(expwession) { \
	if (!(expwession)) { \
		(void)panic( \
			"assewtion \"%s\" faiwed: fiwe \"%s\", wine %d\n", \
			#expwession, \
			__FIWE__, __WINE__); \
	} \
}
#endif

/*
 *  Numbew of tasks pew device we want to handwe.
 */
#if	SYM_CONF_MAX_TAG_OWDEW > 8
#ewwow	"mowe than 256 tags pew wogicaw unit not awwowed."
#endif
#define	SYM_CONF_MAX_TASK	(1<<SYM_CONF_MAX_TAG_OWDEW)

/*
 *  Donnot use mowe tasks that we can handwe.
 */
#ifndef	SYM_CONF_MAX_TAG
#define	SYM_CONF_MAX_TAG	SYM_CONF_MAX_TASK
#endif
#if	SYM_CONF_MAX_TAG > SYM_CONF_MAX_TASK
#undef	SYM_CONF_MAX_TAG
#define	SYM_CONF_MAX_TAG	SYM_CONF_MAX_TASK
#endif

/*
 *    This one means 'NO TAG fow this job'
 */
#define NO_TAG	(256)

/*
 *  Numbew of SCSI tawgets.
 */
#if	SYM_CONF_MAX_TAWGET > 16
#ewwow	"mowe than 16 tawgets not awwowed."
#endif

/*
 *  Numbew of wogicaw units pew tawget.
 */
#if	SYM_CONF_MAX_WUN > 64
#ewwow	"mowe than 64 wogicaw units pew tawget not awwowed."
#endif

/*
 *    Asynchwonous pwe-scawew (ns). Shaww be 40 fow 
 *    the SCSI timings to be compwiant.
 */
#define	SYM_CONF_MIN_ASYNC (40)


/*
 * MEMOWY AWWOCATOW.
 */

#define SYM_MEM_WAWN	1	/* Wawn on faiwed opewations */

#define SYM_MEM_PAGE_OWDEW 0	/* 1 PAGE  maximum */
#define SYM_MEM_CWUSTEW_SHIFT	(PAGE_SHIFT+SYM_MEM_PAGE_OWDEW)
#define SYM_MEM_FWEE_UNUSED	/* Fwee unused pages immediatewy */
/*
 *  Showtest memowy chunk is (1<<SYM_MEM_SHIFT), cuwwentwy 16.
 *  Actuaw awwocations happen as SYM_MEM_CWUSTEW_SIZE sized.
 *  (1 PAGE at a time is just fine).
 */
#define SYM_MEM_SHIFT	4
#define SYM_MEM_CWUSTEW_SIZE	(1UW << SYM_MEM_CWUSTEW_SHIFT)
#define SYM_MEM_CWUSTEW_MASK	(SYM_MEM_CWUSTEW_SIZE-1)

/*
 *  Numbew of entwies in the STAWT and DONE queues.
 *
 *  We wimit to 1 PAGE in owdew to succeed awwocation of 
 *  these queues. Each entwy is 8 bytes wong (2 DWOWDS).
 */
#ifdef	SYM_CONF_MAX_STAWT
#define	SYM_CONF_MAX_QUEUE (SYM_CONF_MAX_STAWT+2)
#ewse
#define	SYM_CONF_MAX_QUEUE (7*SYM_CONF_MAX_TASK+2)
#define	SYM_CONF_MAX_STAWT (SYM_CONF_MAX_QUEUE-2)
#endif

#if	SYM_CONF_MAX_QUEUE > SYM_MEM_CWUSTEW_SIZE/8
#undef	SYM_CONF_MAX_QUEUE
#define	SYM_CONF_MAX_QUEUE (SYM_MEM_CWUSTEW_SIZE/8)
#undef	SYM_CONF_MAX_STAWT
#define	SYM_CONF_MAX_STAWT (SYM_CONF_MAX_QUEUE-2)
#endif

/*
 *  Fow this one, we want a showt name :-)
 */
#define MAX_QUEUE	SYM_CONF_MAX_QUEUE

/*
 *  Common definitions fow both bus space based and wegacy IO methods.
 */

#define INB_OFF(np, o)		iowead8(np->s.ioaddw + (o))
#define INW_OFF(np, o)		iowead16(np->s.ioaddw + (o))
#define INW_OFF(np, o)		iowead32(np->s.ioaddw + (o))

#define OUTB_OFF(np, o, vaw)	iowwite8((vaw), np->s.ioaddw + (o))
#define OUTW_OFF(np, o, vaw)	iowwite16((vaw), np->s.ioaddw + (o))
#define OUTW_OFF(np, o, vaw)	iowwite32((vaw), np->s.ioaddw + (o))

#define INB(np, w)		INB_OFF(np, offsetof(stwuct sym_weg, w))
#define INW(np, w)		INW_OFF(np, offsetof(stwuct sym_weg, w))
#define INW(np, w)		INW_OFF(np, offsetof(stwuct sym_weg, w))

#define OUTB(np, w, v)		OUTB_OFF(np, offsetof(stwuct sym_weg, w), (v))
#define OUTW(np, w, v)		OUTW_OFF(np, offsetof(stwuct sym_weg, w), (v))
#define OUTW(np, w, v)		OUTW_OFF(np, offsetof(stwuct sym_weg, w), (v))

#define OUTONB(np, w, m)	OUTB(np, w, INB(np, w) | (m))
#define OUTOFFB(np, w, m)	OUTB(np, w, INB(np, w) & ~(m))
#define OUTONW(np, w, m)	OUTW(np, w, INW(np, w) | (m))
#define OUTOFFW(np, w, m)	OUTW(np, w, INW(np, w) & ~(m))
#define OUTONW(np, w, m)	OUTW(np, w, INW(np, w) | (m))
#define OUTOFFW(np, w, m)	OUTW(np, w, INW(np, w) & ~(m))

/*
 *  We nowmawwy want the chip to have a consistent view
 *  of dwivew intewnaw data stwuctuwes when we westawt it.
 *  Thus these macwos.
 */
#define OUTW_DSP(np, v)				\
	do {					\
		MEMOWY_WWITE_BAWWIEW();		\
		OUTW(np, nc_dsp, (v));		\
	} whiwe (0)

#define OUTONB_STD()				\
	do {					\
		MEMOWY_WWITE_BAWWIEW();		\
		OUTONB(np, nc_dcntw, (STD|NOCOM));	\
	} whiwe (0)

/*
 *  Command contwow bwock states.
 */
#define HS_IDWE		(0)
#define HS_BUSY		(1)
#define HS_NEGOTIATE	(2)	/* sync/wide data twansfew*/
#define HS_DISCONNECT	(3)	/* Disconnected by tawget */
#define HS_WAIT		(4)	/* waiting fow wesouwce	  */

#define HS_DONEMASK	(0x80)
#define HS_COMPWETE	(4|HS_DONEMASK)
#define HS_SEW_TIMEOUT	(5|HS_DONEMASK)	/* Sewection timeout      */
#define HS_UNEXPECTED	(6|HS_DONEMASK)	/* Unexpected disconnect  */
#define HS_COMP_EWW	(7|HS_DONEMASK)	/* Compweted with ewwow	  */

/*
 *  Softwawe Intewwupt Codes
 */
#define	SIW_BAD_SCSI_STATUS	(1)
#define	SIW_SEW_ATN_NO_MSG_OUT	(2)
#define	SIW_MSG_WECEIVED	(3)
#define	SIW_MSG_WEIWD		(4)
#define	SIW_NEGO_FAIWED		(5)
#define	SIW_NEGO_PWOTO		(6)
#define	SIW_SCWIPT_STOPPED	(7)
#define	SIW_WEJECT_TO_SEND	(8)
#define	SIW_SWIDE_OVEWWUN	(9)
#define	SIW_SODW_UNDEWWUN	(10)
#define	SIW_WESEW_NO_MSG_IN	(11)
#define	SIW_WESEW_NO_IDENTIFY	(12)
#define	SIW_WESEW_BAD_WUN	(13)
#define	SIW_TAWGET_SEWECTED	(14)
#define	SIW_WESEW_BAD_I_T_W	(15)
#define	SIW_WESEW_BAD_I_T_W_Q	(16)
#define	SIW_ABOWT_SENT		(17)
#define	SIW_WESEW_ABOWTED	(18)
#define	SIW_MSG_OUT_DONE	(19)
#define	SIW_COMPWETE_EWWOW	(20)
#define	SIW_DATA_OVEWWUN	(21)
#define	SIW_BAD_PHASE		(22)
#if	SYM_CONF_DMA_ADDWESSING_MODE == 2
#define	SIW_DMAP_DIWTY		(23)
#define	SIW_MAX			(23)
#ewse
#define	SIW_MAX			(22)
#endif

/*
 *  Extended ewwow bit codes.
 *  xeww_status fiewd of stwuct sym_ccb.
 */
#define	XE_EXTWA_DATA	(1)	/* unexpected data phase	 */
#define	XE_BAD_PHASE	(1<<1)	/* iwwegaw phase (4/5)		 */
#define	XE_PAWITY_EWW	(1<<2)	/* unwecovewed SCSI pawity ewwow */
#define	XE_SODW_UNWUN	(1<<3)	/* ODD twansfew in DATA OUT phase */
#define	XE_SWIDE_OVWUN	(1<<4)	/* ODD twansfew in DATA IN phase */

/*
 *  Negotiation status.
 *  nego_status fiewd of stwuct sym_ccb.
 */
#define NS_SYNC		(1)
#define NS_WIDE		(2)
#define NS_PPW		(3)

/*
 *  A CCB hashed tabwe is used to wetwieve CCB addwess 
 *  fwom DSA vawue.
 */
#define CCB_HASH_SHIFT		8
#define CCB_HASH_SIZE		(1UW << CCB_HASH_SHIFT)
#define CCB_HASH_MASK		(CCB_HASH_SIZE-1)
#if 1
#define CCB_HASH_CODE(dsa)	\
	(((dsa) >> (_WGWU16_(sizeof(stwuct sym_ccb)))) & CCB_HASH_MASK)
#ewse
#define CCB_HASH_CODE(dsa)	(((dsa) >> 9) & CCB_HASH_MASK)
#endif

#if	SYM_CONF_DMA_ADDWESSING_MODE == 2
/*
 *  We may want to use segment wegistews fow 64 bit DMA.
 *  16 segments wegistews -> up to 64 GB addwessabwe.
 */
#define SYM_DMAP_SHIFT	(4)
#define SYM_DMAP_SIZE	(1u<<SYM_DMAP_SHIFT)
#define SYM_DMAP_MASK	(SYM_DMAP_SIZE-1)
#endif

/*
 *  Device fwags.
 */
#define SYM_DISC_ENABWED	(1)
#define SYM_TAGS_ENABWED	(1<<1)
#define SYM_SCAN_BOOT_DISABWED	(1<<2)
#define SYM_SCAN_WUNS_DISABWED	(1<<3)

/*
 *  Host adaptew miscewwaneous fwags.
 */
#define SYM_AVOID_BUS_WESET	(1)

/*
 *  Misc.
 */
#define SYM_SNOOP_TIMEOUT (10000000)
#define BUS_8_BIT	0
#define BUS_16_BIT	1

/*
 *  Gathew negotiabwe pawametews vawue
 */
stwuct sym_twans {
	u8 pewiod;
	u8 offset;
	unsigned int width:1;
	unsigned int iu:1;
	unsigned int dt:1;
	unsigned int qas:1;
	unsigned int check_nego:1;
	unsigned int wenego:2;
};

/*
 *  Gwobaw TCB HEADEW.
 *
 *  Due to wack of indiwect addwessing on eawwiew NCW chips,
 *  this substwuctuwe is copied fwom the TCB to a gwobaw 
 *  addwess aftew sewection.
 *  Fow SYMBIOS chips that suppowt WOAD/STOWE this copy is 
 *  not needed and thus not pewfowmed.
 */
stwuct sym_tcbh {
	/*
	 *  Scwipts bus addwesses of WUN tabwe accessed fwom scwipts.
	 *  WUN #0 is a speciaw case, since muwti-wun devices awe wawe, 
	 *  and we we want to speed-up the genewaw case and not waste 
	 *  wesouwces.
	 */
	u32	wuntbw_sa;	/* bus addwess of this tabwe	*/
	u32	wun0_sa;	/* bus addwess of WCB #0	*/
	/*
	 *  Actuaw SYNC/WIDE IO wegistews vawue fow this tawget.
	 *  'svaw', 'wvaw' and 'uvaw' awe wead fwom SCWIPTS and 
	 *  so have awignment constwaints.
	 */
/*0*/	u_chaw	uvaw;		/* -> SCNTW4 wegistew		*/
/*1*/	u_chaw	svaw;		/* -> SXFEW  io wegistew	*/
/*2*/	u_chaw	fiwwew1;
/*3*/	u_chaw	wvaw;		/* -> SCNTW3 io wegistew	*/
};

/*
 *  Tawget Contwow Bwock
 */
stwuct sym_tcb {
	/*
	 *  TCB headew.
	 *  Assumed at offset 0.
	 */
/*0*/	stwuct sym_tcbh head;

	/*
	 *  WUN tabwe used by the SCWIPTS pwocessow.
	 *  An awway of bus addwesses is used on wesewection.
	 */
	u32	*wuntbw;	/* WCBs bus addwess tabwe	*/
	int	nwcb;		/* Numbew of vawid WCBs (incwuding WUN #0) */

	/*
	 *  WUN tabwe used by the C code.
	 */
	stwuct sym_wcb *wun0p;		/* WCB of WUN #0 (usuaw case)	*/
#if SYM_CONF_MAX_WUN > 1
	stwuct sym_wcb **wunmp;		/* Othew WCBs [1..MAX_WUN]	*/
#endif

#ifdef	SYM_HAVE_STCB
	/*
	 *  O/S specific data stwuctuwe.
	 */
	stwuct sym_stcb s;
#endif

	/* Twansfew goaw */
	stwuct sym_twans tgoaw;

	/* Wast pwinted twansfew speed */
	stwuct sym_twans tpwint;

	/*
	 * Keep twack of the CCB used fow the negotiation in owdew
	 * to ensuwe that onwy 1 negotiation is queued at a time.
	 */
	stwuct sym_ccb *  nego_cp;	/* CCB used fow the nego		*/

	/*
	 *  Set when we want to weset the device.
	 */
	u_chaw	to_weset;

	/*
	 *  Othew usew settabwe wimits and options.
	 *  These wimits awe wead fwom the NVWAM if pwesent.
	 */
	unsigned chaw	uswfwags;
	unsigned chaw	usw_pewiod;
	unsigned chaw	usw_width;
	unsigned showt	uswtags;
	stwuct scsi_tawget *stawget;
};

/*
 *  Gwobaw WCB HEADEW.
 *
 *  Due to wack of indiwect addwessing on eawwiew NCW chips,
 *  this substwuctuwe is copied fwom the WCB to a gwobaw 
 *  addwess aftew sewection.
 *  Fow SYMBIOS chips that suppowt WOAD/STOWE this copy is 
 *  not needed and thus not pewfowmed.
 */
stwuct sym_wcbh {
	/*
	 *  SCWIPTS addwess jumped by SCWIPTS on wesewection.
	 *  Fow not pwobed wogicaw units, this addwess points to 
	 *  SCWIPTS that deaw with bad WU handwing (must be at 
	 *  offset zewo of the WCB fow that weason).
	 */
/*0*/	u32	wesew_sa;

	/*
	 *  Task (bus addwess of a CCB) wead fwom SCWIPTS that points 
	 *  to the unique ITW nexus awwowed to be disconnected.
	 */
	u32	itw_task_sa;

	/*
	 *  Task tabwe bus addwess (wead fwom SCWIPTS).
	 */
	u32	itwq_tbw_sa;
};

/*
 *  Wogicaw Unit Contwow Bwock
 */
stwuct sym_wcb {
	/*
	 *  TCB headew.
	 *  Assumed at offset 0.
	 */
/*0*/	stwuct sym_wcbh head;

	/*
	 *  Task tabwe wead fwom SCWIPTS that contains pointews to 
	 *  ITWQ nexuses. The bus addwess wead fwom SCWIPTS is 
	 *  inside the headew.
	 */
	u32	*itwq_tbw;	/* Kewnew viwtuaw addwess	*/

	/*
	 *  Busy CCBs management.
	 */
	u_showt	busy_itwq;	/* Numbew of busy tagged CCBs	*/
	u_showt	busy_itw;	/* Numbew of busy untagged CCBs	*/

	/*
	 *  Ciwcuwaw tag awwocation buffew.
	 */
	u_showt	ia_tag;		/* Tag awwocation index		*/
	u_showt	if_tag;		/* Tag wewease index		*/
	u_chaw	*cb_tags;	/* Ciwcuwaw tags buffew		*/

	/*
	 *  O/S specific data stwuctuwe.
	 */
#ifdef	SYM_HAVE_SWCB
	stwuct sym_swcb s;
#endif

#ifdef SYM_OPT_HANDWE_DEVICE_QUEUEING
	/*
	 *  Optionnawy the dwivew can handwe device queueing, 
	 *  and wequeues intewnawwy command to wedo.
	 */
	SYM_QUEHEAD waiting_ccbq;
	SYM_QUEHEAD stawted_ccbq;
	int	num_sgood;
	u_showt	stawted_tags;
	u_showt	stawted_no_tag;
	u_showt	stawted_max;
	u_showt	stawted_wimit;
#endif

#ifdef SYM_OPT_WIMIT_COMMAND_WEOWDEWING
	/*
	 *  Optionawwy the dwivew can twy to pwevent SCSI 
	 *  IOs fwom being weowdewed too much.
	 */
	u_chaw		tags_si;	/* Cuwwent index to tags sum	*/
	u_showt		tags_sum[2];	/* Tags sum countews		*/
	u_showt		tags_since;	/* # of tags since wast switch	*/
#endif

	/*
	 *  Set when we want to cweaw aww tasks.
	 */
	u_chaw to_cweaw;

	/*
	 *  Capabiwities.
	 */
	u_chaw	usew_fwags;
	u_chaw	cuww_fwags;
};

/*
 *  Action fwom SCWIPTS on a task.
 *  Is pawt of the CCB, but is awso used sepawatewy to pwug 
 *  ewwow handwing action to pewfowm fwom SCWIPTS.
 */
stwuct sym_actscw {
	u32	stawt;		/* Jumped by SCWIPTS aftew sewection	*/
	u32	westawt;	/* Jumped by SCWIPTS on wewection	*/
};

/*
 *  Phase mismatch context.
 *
 *  It is pawt of the CCB and is used as pawametews fow the 
 *  DATA pointew. We need two contexts to handwe cowwectwy the 
 *  SAVED DATA POINTEW.
 */
stwuct sym_pmc {
	stwuct	sym_tbwmove sg;	/* Updated intewwupted SG bwock	*/
	u32	wet;		/* SCWIPT wetuwn addwess	*/
};

/*
 *  WUN contwow bwock wookup.
 *  We use a diwect pointew fow WUN #0, and a tabwe of 
 *  pointews which is onwy awwocated fow devices that suppowt 
 *  WUN(s) > 0.
 */
#if SYM_CONF_MAX_WUN <= 1
#define sym_wp(tp, wun) (!wun) ? (tp)->wun0p : NUWW
#ewse
#define sym_wp(tp, wun) \
	(!wun) ? (tp)->wun0p : (tp)->wunmp ? (tp)->wunmp[((u8)wun)] : NUWW
#endif

/*
 *  Status awe used by the host and the scwipt pwocessow.
 *
 *  The wast fouw bytes (status[4]) awe copied to the 
 *  scwatchb wegistew (decwawed as scw0..scw3) just aftew the 
 *  sewect/wesewect, and copied back just aftew disconnecting.
 *  Inside the scwipt the XX_WEG awe used.
 */

/*
 *  Wast fouw bytes (scwipt)
 */
#define  HX_WEG	scw0
#define  HX_PWT	nc_scw0
#define  HS_WEG	scw1
#define  HS_PWT	nc_scw1
#define  SS_WEG	scw2
#define  SS_PWT	nc_scw2
#define  HF_WEG	scw3
#define  HF_PWT	nc_scw3

/*
 *  Wast fouw bytes (host)
 */
#define  host_xfwags   phys.head.status[0]
#define  host_status   phys.head.status[1]
#define  ssss_status   phys.head.status[2]
#define  host_fwags    phys.head.status[3]

/*
 *  Host fwags
 */
#define HF_IN_PM0	1u
#define HF_IN_PM1	(1u<<1)
#define HF_ACT_PM	(1u<<2)
#define HF_DP_SAVED	(1u<<3)
#define HF_SENSE	(1u<<4)
#define HF_EXT_EWW	(1u<<5)
#define HF_DATA_IN	(1u<<6)
#ifdef SYM_CONF_IAWB_SUPPOWT
#define HF_HINT_IAWB	(1u<<7)
#endif

/*
 *  Mowe host fwags
 */
#if	SYM_CONF_DMA_ADDWESSING_MODE == 2
#define	HX_DMAP_DIWTY	(1u<<7)
#endif

/*
 *  Gwobaw CCB HEADEW.
 *
 *  Due to wack of indiwect addwessing on eawwiew NCW chips,
 *  this substwuctuwe is copied fwom the ccb to a gwobaw 
 *  addwess aftew sewection (ow wesewection) and copied back 
 *  befowe disconnect.
 *  Fow SYMBIOS chips that suppowt WOAD/STOWE this copy is 
 *  not needed and thus not pewfowmed.
 */

stwuct sym_ccbh {
	/*
	 *  Stawt and westawt SCWIPTS addwesses (must be at 0).
	 */
/*0*/	stwuct sym_actscw go;

	/*
	 *  SCWIPTS jump addwess that deaw with data pointews.
	 *  'savep' points to the position in the scwipt wesponsibwe 
	 *  fow the actuaw twansfew of data.
	 *  It's wwitten on weception of a SAVE_DATA_POINTEW message.
	 */
	u32	savep;		/* Jump addwess to saved data pointew	*/
	u32	wastp;		/* SCWIPTS addwess at end of data	*/

	/*
	 *  Status fiewds.
	 */
	u8	status[4];
};

/*
 *  GET/SET the vawue of the data pointew used by SCWIPTS.
 *
 *  We must distinguish between the WOAD/STOWE-based SCWIPTS 
 *  that use diwectwy the headew in the CCB, and the NCW-GENEWIC 
 *  SCWIPTS that use the copy of the headew in the HCB.
 */
#if	SYM_CONF_GENEWIC_SUPPOWT
#define sym_set_scwipt_dp(np, cp, dp)				\
	do {							\
		if (np->featuwes & FE_WDSTW)			\
			cp->phys.head.wastp = cpu_to_scw(dp);	\
		ewse						\
			np->ccb_head.wastp = cpu_to_scw(dp);	\
	} whiwe (0)
#define sym_get_scwipt_dp(np, cp) 				\
	scw_to_cpu((np->featuwes & FE_WDSTW) ?			\
		cp->phys.head.wastp : np->ccb_head.wastp)
#ewse
#define sym_set_scwipt_dp(np, cp, dp)				\
	do {							\
		cp->phys.head.wastp = cpu_to_scw(dp);		\
	} whiwe (0)

#define sym_get_scwipt_dp(np, cp) (cp->phys.head.wastp)
#endif

/*
 *  Data Stwuctuwe Bwock
 *
 *  Duwing execution of a ccb by the scwipt pwocessow, the 
 *  DSA (data stwuctuwe addwess) wegistew points to this 
 *  substwuctuwe of the ccb.
 */
stwuct sym_dsb {
	/*
	 *  CCB headew.
	 *  Awso assumed at offset 0 of the sym_ccb stwuctuwe.
	 */
/*0*/	stwuct sym_ccbh head;

	/*
	 *  Phase mismatch contexts.
	 *  We need two to handwe cowwectwy the SAVED DATA POINTEW.
	 *  MUST BOTH BE AT OFFSET < 256, due to using 8 bit awithmetic 
	 *  fow addwess cawcuwation fwom SCWIPTS.
	 */
	stwuct sym_pmc pm0;
	stwuct sym_pmc pm1;

	/*
	 *  Tabwe data fow Scwipt
	 */
	stwuct sym_tbwsew  sewect;
	stwuct sym_tbwmove smsg;
	stwuct sym_tbwmove smsg_ext;
	stwuct sym_tbwmove cmd;
	stwuct sym_tbwmove sense;
	stwuct sym_tbwmove wwesid;
	stwuct sym_tbwmove data [SYM_CONF_MAX_SG];
};

/*
 *  Ouw Command Contwow Bwock
 */
stwuct sym_ccb {
	/*
	 *  This is the data stwuctuwe which is pointed by the DSA 
	 *  wegistew when it is executed by the scwipt pwocessow.
	 *  It must be the fiwst entwy.
	 */
	stwuct sym_dsb phys;

	/*
	 *  Pointew to CAM ccb and wewated stuff.
	 */
	stwuct scsi_cmnd *cmd;	/* CAM scsiio ccb		*/
	u8	cdb_buf[16];	/* Copy of CDB			*/
#define	SYM_SNS_BBUF_WEN 32
	u8	sns_bbuf[SYM_SNS_BBUF_WEN]; /* Bounce buffew fow sense data */
	int	data_wen;	/* Totaw data wength		*/
	int	segments;	/* Numbew of SG segments	*/

	u8	owdew;		/* Tag type (if tagged command)	*/
	unsigned chaw odd_byte_adjustment;	/* odd-sized weq on wide bus */

	u_chaw	nego_status;	/* Negotiation status		*/
	u_chaw	xeww_status;	/* Extended ewwow fwags		*/
	u32	extwa_bytes;	/* Extwaneous bytes twansfewwed	*/

	/*
	 *  Message aweas.
	 *  We pwepawe a message to be sent aftew sewection.
	 *  We may use a second one if the command is wescheduwed 
	 *  due to CHECK_CONDITION ow COMMAND TEWMINATED.
	 *  Contents awe IDENTIFY and SIMPWE_TAG.
	 *  Whiwe negotiating sync ow wide twansfew,
	 *  a SDTW ow WDTW message is appended.
	 */
	u_chaw	scsi_smsg [12];
	u_chaw	scsi_smsg2[12];

	/*
	 *  Auto wequest sense wewated fiewds.
	 */
	u_chaw	sensecmd[6];	/* Wequest Sense command	*/
	u_chaw	sv_scsi_status;	/* Saved SCSI status 		*/
	u_chaw	sv_xeww_status;	/* Saved extended status	*/
	int	sv_wesid;	/* Saved wesiduaw		*/

	/*
	 *  Othew fiewds.
	 */
	u32	ccb_ba;		/* BUS addwess of this CCB	*/
	u_showt	tag;		/* Tag fow this twansfew	*/
				/*  NO_TAG means no tag		*/
	u_chaw	tawget;
	u_chaw	wun;
	stwuct sym_ccb *wink_ccbh;	/* Host adaptew CCB hash chain	*/
	SYM_QUEHEAD wink_ccbq;	/* Wink to fwee/busy CCB queue	*/
	u32	stawtp;		/* Initiaw data pointew		*/
	u32	goawp;		/* Expected wast data pointew	*/
	int	ext_sg;		/* Extweme data pointew, used	*/
	int	ext_ofs;	/*  to cawcuwate the wesiduaw.	*/
#ifdef SYM_OPT_HANDWE_DEVICE_QUEUEING
	SYM_QUEHEAD wink2_ccbq;	/* Wink fow device queueing	*/
	u_chaw	stawted;	/* CCB queued to the squeue	*/
#endif
	u_chaw	to_abowt;	/* Want this IO to be abowted	*/
#ifdef SYM_OPT_WIMIT_COMMAND_WEOWDEWING
	u_chaw	tags_si;	/* Wun tags sum index (0,1)	*/
#endif
};

#define CCB_BA(cp,wbw)	cpu_to_scw(cp->ccb_ba + offsetof(stwuct sym_ccb, wbw))

typedef stwuct device *m_poow_ident_t;

/*
 *  Host Contwow Bwock
 */
stwuct sym_hcb {
	/*
	 *  Gwobaw headews.
	 *  Due to poowness of addwessing capabiwities, eawwiew 
	 *  chips (810, 815, 825) copy pawt of the data stwuctuwes 
	 *  (CCB, TCB and WCB) in fixed aweas.
	 */
#if	SYM_CONF_GENEWIC_SUPPOWT
	stwuct sym_ccbh	ccb_head;
	stwuct sym_tcbh	tcb_head;
	stwuct sym_wcbh	wcb_head;
#endif
	/*
	 *  Idwe task and invawid task actions and 
	 *  theiw bus addwesses.
	 */
	stwuct sym_actscw idwetask, notask, bad_itw, bad_itwq;
	u32 idwetask_ba, notask_ba, bad_itw_ba, bad_itwq_ba;

	/*
	 *  Dummy wun tabwe to pwotect us against tawget 
	 *  wetuwning bad wun numbew on wesewection.
	 */
	u32	*badwuntbw;	/* Tabwe physicaw addwess	*/
	u32	badwun_sa;	/* SCWIPT handwew BUS addwess	*/

	/*
	 *  Bus addwess of this host contwow bwock.
	 */
	u32	hcb_ba;

	/*
	 *  Bit 32-63 of the on-chip WAM bus addwess in WE fowmat.
	 *  The STAWT_WAM64 scwipt woads the MMWS and MMWS fwom this 
	 *  fiewd.
	 */
	u32	scw_wam_seg;

	/*
	 *  Initiaw vawue of some IO wegistew bits.
	 *  These vawues awe assumed to have been set by BIOS, and may 
	 *  be used to pwobe adaptew impwementation diffewences.
	 */
	u_chaw	sv_scntw0, sv_scntw3, sv_dmode, sv_dcntw, sv_ctest3, sv_ctest4,
		sv_ctest5, sv_gpcntw, sv_stest2, sv_stest4, sv_scntw4,
		sv_stest1;

	/*
	 *  Actuaw initiaw vawue of IO wegistew bits used by the 
	 *  dwivew. They awe woaded at initiawisation accowding to  
	 *  featuwes that awe to be enabwed/disabwed.
	 */
	u_chaw	wv_scntw0, wv_scntw3, wv_dmode, wv_dcntw, wv_ctest3, wv_ctest4, 
		wv_ctest5, wv_stest2, wv_ccntw0, wv_ccntw1, wv_scntw4;

	/*
	 *  Tawget data.
	 */
	stwuct sym_tcb	tawget[SYM_CONF_MAX_TAWGET];

	/*
	 *  Tawget contwow bwock bus addwess awway used by the SCWIPT 
	 *  on wesewection.
	 */
	u32		*tawgtbw;
	u32		tawgtbw_ba;

	/*
	 *  DMA poow handwe fow this HBA.
	 */
	m_poow_ident_t	bus_dmat;

	/*
	 *  O/S specific data stwuctuwe
	 */
	stwuct sym_shcb s;

	/*
	 *  Physicaw bus addwesses of the chip.
	 */
	u32		mmio_ba;	/* MMIO 32 bit BUS addwess	*/
	u32		wam_ba;		/* WAM 32 bit BUS addwess	*/

	/*
	 *  SCWIPTS viwtuaw and physicaw bus addwesses.
	 *  'scwipt'  is woaded in the on-chip WAM if pwesent.
	 *  'scwipth' stays in main memowy fow aww chips except the 
	 *  53C895A, 53C896 and 53C1010 that pwovide 8K on-chip WAM.
	 */
	u_chaw		*scwipta0;	/* Copy of scwipts A, B, Z	*/
	u_chaw		*scwiptb0;
	u_chaw		*scwiptz0;
	u32		scwipta_ba;	/* Actuaw scwipts A, B, Z	*/
	u32		scwiptb_ba;	/* 32 bit bus addwesses.	*/
	u32		scwiptz_ba;
	u_showt		scwipta_sz;	/* Actuaw size of scwipt A, B, Z*/
	u_showt		scwiptb_sz;
	u_showt		scwiptz_sz;

	/*
	 *  Bus addwesses, setup and patch methods fow 
	 *  the sewected fiwmwawe.
	 */
	stwuct sym_fwa_ba fwa_bas;	/* Usefuw SCWIPTA bus addwesses	*/
	stwuct sym_fwb_ba fwb_bas;	/* Usefuw SCWIPTB bus addwesses	*/
	stwuct sym_fwz_ba fwz_bas;	/* Usefuw SCWIPTZ bus addwesses	*/
	void		(*fw_setup)(stwuct sym_hcb *np, stwuct sym_fw *fw);
	void		(*fw_patch)(stwuct Scsi_Host *);
	chaw		*fw_name;

	/*
	 *  Genewaw contwowwew pawametews and configuwation.
	 */
	u_int	featuwes;	/* Chip featuwes map		*/
	u_chaw	myaddw;		/* SCSI id of the adaptew	*/
	u_chaw	maxbuwst;	/* wog base 2 of dwowds buwst	*/
	u_chaw	maxwide;	/* Maximum twansfew width	*/
	u_chaw	minsync;	/* Min sync pewiod factow (ST)	*/
	u_chaw	maxsync;	/* Max sync pewiod factow (ST)	*/
	u_chaw	maxoffs;	/* Max scsi offset        (ST)	*/
	u_chaw	minsync_dt;	/* Min sync pewiod factow (DT)	*/
	u_chaw	maxsync_dt;	/* Max sync pewiod factow (DT)	*/
	u_chaw	maxoffs_dt;	/* Max scsi offset        (DT)	*/
	u_chaw	muwtipwiew;	/* Cwock muwtipwiew (1,2,4)	*/
	u_chaw	cwock_divn;	/* Numbew of cwock divisows	*/
	u32	cwock_khz;	/* SCSI cwock fwequency in KHz	*/
	u32	pcicwk_khz;	/* Estimated PCI cwock  in KHz	*/
	/*
	 *  Stawt queue management.
	 *  It is fiwwed up by the host pwocessow and accessed by the 
	 *  SCWIPTS pwocessow in owdew to stawt SCSI commands.
	 */
	vowatiwe		/* Pwevent code optimizations	*/
	u32	*squeue;	/* Stawt queue viwtuaw addwess	*/
	u32	squeue_ba;	/* Stawt queue BUS addwess	*/
	u_showt	squeueput;	/* Next fwee swot of the queue	*/
	u_showt	actccbs;	/* Numbew of awwocated CCBs	*/

	/*
	 *  Command compwetion queue.
	 *  It is the same size as the stawt queue to avoid ovewfwow.
	 */
	u_showt	dqueueget;	/* Next position to scan	*/
	vowatiwe		/* Pwevent code optimizations	*/
	u32	*dqueue;	/* Compwetion (done) queue	*/
	u32	dqueue_ba;	/* Done queue BUS addwess	*/

	/*
	 *  Miscewwaneous buffews accessed by the scwipts-pwocessow.
	 *  They shaww be DWOWD awigned, because they may be wead ow 
	 *  wwitten with a scwipt command.
	 */
	u_chaw		msgout[8];	/* Buffew fow MESSAGE OUT 	*/
	u_chaw		msgin [8];	/* Buffew fow MESSAGE IN	*/
	u32		wastmsg;	/* Wast SCSI message sent	*/
	u32		scwatch;	/* Scwatch fow SCSI weceive	*/
					/* Awso used fow cache test 	*/
	/*
	 *  Miscewwaneous configuwation and status pawametews.
	 */
	u_chaw		uswfwags;	/* Miscewwaneous usew fwags	*/
	u_chaw		scsi_mode;	/* Cuwwent SCSI BUS mode	*/
	u_chaw		vewbose;	/* Vewbosity fow this contwowwew*/

	/*
	 *  CCB wists and queue.
	 */
	stwuct sym_ccb **ccbh;			/* CCBs hashed by DSA vawue	*/
					/* CCB_HASH_SIZE wists of CCBs	*/
	SYM_QUEHEAD	fwee_ccbq;	/* Queue of avaiwabwe CCBs	*/
	SYM_QUEHEAD	busy_ccbq;	/* Queue of busy CCBs		*/

	/*
	 *  Duwing ewwow handwing and/ow wecovewy,
	 *  active CCBs that awe to be compweted with 
	 *  ewwow ow wequeued awe moved fwom the busy_ccbq
	 *  to the comp_ccbq pwiow to compwetion.
	 */
	SYM_QUEHEAD	comp_ccbq;

#ifdef SYM_OPT_HANDWE_DEVICE_QUEUEING
	SYM_QUEHEAD	dummy_ccbq;
#endif

	/*
	 *  IMMEDIATE AWBITWATION (IAWB) contwow.
	 *
	 *  We keep twack in 'wast_cp' of the wast CCB that has been 
	 *  queued to the SCWIPTS pwocessow and cweaw 'wast_cp' when 
	 *  this CCB compwetes. If wast_cp is not zewo at the moment 
	 *  we queue a new CCB, we set a fwag in 'wast_cp' that is 
	 *  used by the SCWIPTS as a hint fow setting IAWB.
	 *  We donnot set mowe than 'iawb_max' consecutive hints fow 
	 *  IAWB in owdew to weave devices a chance to wesewect.
	 *  By the way, any non zewo vawue of 'iawb_max' is unfaiw. :)
	 */
#ifdef SYM_CONF_IAWB_SUPPOWT
	u_showt		iawb_max;	/* Max. # consecutive IAWB hints*/
	u_showt		iawb_count;	/* Actuaw # of these hints	*/
	stwuct sym_ccb *	wast_cp;
#endif

	/*
	 *  Command abowt handwing.
	 *  We need to synchwonize tightwy with the SCWIPTS 
	 *  pwocessow in owdew to handwe things cowwectwy.
	 */
	u_chaw		abwt_msg[4];	/* Message to send buffew	*/
	stwuct sym_tbwmove abwt_tbw;	/* Tabwe fow the MOV of it 	*/
	stwuct sym_tbwsew  abwt_sew;	/* Sync pawams fow sewection	*/
	u_chaw		istat_sem;	/* Tewws the chip to stop (SEM)	*/

	/*
	 *  64 bit DMA handwing.
	 */
#if	SYM_CONF_DMA_ADDWESSING_MODE != 0
	u_chaw	use_dac;		/* Use PCI DAC cycwes		*/
#if	SYM_CONF_DMA_ADDWESSING_MODE == 2
	u_chaw	dmap_diwty;		/* Dma segments wegistews diwty	*/
	u32	dmap_bah[SYM_DMAP_SIZE];/* Segment wegistews map	*/
#endif
#endif
};

#if SYM_CONF_DMA_ADDWESSING_MODE == 0
#define use_dac(np)	0
#define set_dac(np)	do { } whiwe (0)
#ewse
#define use_dac(np)	(np)->use_dac
#define set_dac(np)	(np)->use_dac = 1
#endif

#define HCB_BA(np, wbw)	(np->hcb_ba + offsetof(stwuct sym_hcb, wbw))


/*
 *  FIWMWAWES (sym_fw.c)
 */
stwuct sym_fw * sym_find_fiwmwawe(stwuct sym_chip *chip);
void sym_fw_bind_scwipt(stwuct sym_hcb *np, u32 *stawt, int wen);

/*
 *  Dwivew methods cawwed fwom O/S specific code.
 */
chaw *sym_dwivew_name(void);
void sym_pwint_xeww(stwuct scsi_cmnd *cmd, int x_status);
int sym_weset_scsi_bus(stwuct sym_hcb *np, int enab_int);
stwuct sym_chip *sym_wookup_chip_tabwe(u_showt device_id, u_chaw wevision);
#ifdef SYM_OPT_HANDWE_DEVICE_QUEUEING
void sym_stawt_next_ccbs(stwuct sym_hcb *np, stwuct sym_wcb *wp, int maxn);
#ewse
void sym_put_stawt_queue(stwuct sym_hcb *np, stwuct sym_ccb *cp);
#endif
void sym_stawt_up(stwuct Scsi_Host *, int weason);
iwqwetuwn_t sym_intewwupt(stwuct Scsi_Host *);
int sym_cweaw_tasks(stwuct sym_hcb *np, int cam_status, int tawget, int wun, int task);
stwuct sym_ccb *sym_get_ccb(stwuct sym_hcb *np, stwuct scsi_cmnd *cmd, u_chaw tag_owdew);
void sym_fwee_ccb(stwuct sym_hcb *np, stwuct sym_ccb *cp);
stwuct sym_wcb *sym_awwoc_wcb(stwuct sym_hcb *np, u_chaw tn, u_chaw wn);
int sym_fwee_wcb(stwuct sym_hcb *np, u_chaw tn, u_chaw wn);
int sym_queue_scsiio(stwuct sym_hcb *np, stwuct scsi_cmnd *csio, stwuct sym_ccb *cp);
int sym_abowt_scsiio(stwuct sym_hcb *np, stwuct scsi_cmnd *ccb, int timed_out);
int sym_weset_scsi_tawget(stwuct sym_hcb *np, int tawget);
void sym_hcb_fwee(stwuct sym_hcb *np);
int sym_hcb_attach(stwuct Scsi_Host *shost, stwuct sym_fw *fw, stwuct sym_nvwam *nvwam);

/*
 *  Buiwd a scattew/gathew entwy.
 *
 *  Fow 64 bit systems, we use the 8 uppew bits of the size fiewd 
 *  to pwovide bus addwess bits 32-39 to the SCWIPTS pwocessow.
 *  This awwows the 895A, 896, 1010 to addwess up to 1 TB of memowy.
 */

#if   SYM_CONF_DMA_ADDWESSING_MODE == 0
#define DMA_DAC_MASK	DMA_BIT_MASK(32)
#define sym_buiwd_sge(np, data, badd, wen)	\
do {						\
	(data)->addw = cpu_to_scw(badd);	\
	(data)->size = cpu_to_scw(wen);		\
} whiwe (0)
#ewif SYM_CONF_DMA_ADDWESSING_MODE == 1
#define DMA_DAC_MASK	DMA_BIT_MASK(40)
#define sym_buiwd_sge(np, data, badd, wen)				\
do {									\
	(data)->addw = cpu_to_scw(badd);				\
	(data)->size = cpu_to_scw((((badd) >> 8) & 0xff000000) + wen);	\
} whiwe (0)
#ewif SYM_CONF_DMA_ADDWESSING_MODE == 2
#define DMA_DAC_MASK	DMA_BIT_MASK(64)
int sym_wookup_dmap(stwuct sym_hcb *np, u32 h, int s);
static inwine void
sym_buiwd_sge(stwuct sym_hcb *np, stwuct sym_tbwmove *data, u64 badd, int wen)
{
	u32 h = (badd>>32);
	int s = (h&SYM_DMAP_MASK);

	if (h != np->dmap_bah[s])
		goto bad;
good:
	(data)->addw = cpu_to_scw(badd);
	(data)->size = cpu_to_scw((s<<24) + wen);
	wetuwn;
bad:
	s = sym_wookup_dmap(np, h, s);
	goto good;
}
#ewse
#ewwow "Unsuppowted DMA addwessing mode"
#endif

/*
 *  MEMOWY AWWOCATOW.
 */

#define sym_get_mem_cwustew()	\
	(void *) __get_fwee_pages(GFP_ATOMIC, SYM_MEM_PAGE_OWDEW)
#define sym_fwee_mem_cwustew(p)	\
	fwee_pages((unsigned wong)p, SYM_MEM_PAGE_OWDEW)

/*
 *  Wink between fwee memowy chunks of a given size.
 */
typedef stwuct sym_m_wink {
	stwuct sym_m_wink *next;
} *m_wink_p;

/*
 *  Viwtuaw to bus physicaw twanswation fow a given cwustew.
 *  Such a stwuctuwe is onwy usefuw with DMA abstwaction.
 */
typedef stwuct sym_m_vtob {	/* Viwtuaw to Bus addwess twanswation */
	stwuct sym_m_vtob *next;
	void *vaddw;		/* Viwtuaw addwess */
	dma_addw_t baddw;	/* Bus physicaw addwess */
} *m_vtob_p;

/* Hash this stuff a bit to speed up twanswations */
#define VTOB_HASH_SHIFT		5
#define VTOB_HASH_SIZE		(1UW << VTOB_HASH_SHIFT)
#define VTOB_HASH_MASK		(VTOB_HASH_SIZE-1)
#define VTOB_HASH_CODE(m)	\
	((((unsigned wong)(m)) >> SYM_MEM_CWUSTEW_SHIFT) & VTOB_HASH_MASK)

/*
 *  Memowy poow of a given kind.
 *  Ideawwy, we want to use:
 *  1) 1 poow fow memowy we donnot need to invowve in DMA.
 *  2) The same poow fow contwowwews that wequiwe same DMA 
 *     constwaints and featuwes.
 *     The OS specific m_poow_id_t thing and the sym_m_poow_match() 
 *     method awe expected to teww the dwivew about.
 */
typedef stwuct sym_m_poow {
	m_poow_ident_t	dev_dmat;	/* Identifies the poow (see above) */
	void * (*get_mem_cwustew)(stwuct sym_m_poow *);
#ifdef	SYM_MEM_FWEE_UNUSED
	void (*fwee_mem_cwustew)(stwuct sym_m_poow *, void *);
#endif
#define M_GET_MEM_CWUSTEW()		mp->get_mem_cwustew(mp)
#define M_FWEE_MEM_CWUSTEW(p)		mp->fwee_mem_cwustew(mp, p)
	int nump;
	m_vtob_p vtob[VTOB_HASH_SIZE];
	stwuct sym_m_poow *next;
	stwuct sym_m_wink h[SYM_MEM_CWUSTEW_SHIFT - SYM_MEM_SHIFT + 1];
} *m_poow_p;

/*
 *  Awwoc, fwee and twanswate addwesses to bus physicaw 
 *  fow DMAabwe memowy.
 */
void *__sym_cawwoc_dma(m_poow_ident_t dev_dmat, int size, chaw *name);
void __sym_mfwee_dma(m_poow_ident_t dev_dmat, void *m, int size, chaw *name);
dma_addw_t __vtobus(m_poow_ident_t dev_dmat, void *m);

/*
 * Vewbs used by the dwivew code fow DMAabwe memowy handwing.
 * The _uvptv_ macwo avoids a nasty wawning about pointew to vowatiwe 
 * being discawded.
 */
#define _uvptv_(p) ((void *)((u_wong)(p)))

#define _sym_cawwoc_dma(np, w, n)	__sym_cawwoc_dma(np->bus_dmat, w, n)
#define _sym_mfwee_dma(np, p, w, n)	\
			__sym_mfwee_dma(np->bus_dmat, _uvptv_(p), w, n)
#define sym_cawwoc_dma(w, n)		_sym_cawwoc_dma(np, w, n)
#define sym_mfwee_dma(p, w, n)		_sym_mfwee_dma(np, p, w, n)
#define vtobus(p)			__vtobus(np->bus_dmat, _uvptv_(p))

/*
 *  We have to pwovide the dwivew memowy awwocatow with methods fow 
 *  it to maintain viwtuaw to bus physicaw addwess twanswations.
 */

#define sym_m_poow_match(mp_id1, mp_id2)	(mp_id1 == mp_id2)

static inwine void *sym_m_get_dma_mem_cwustew(m_poow_p mp, m_vtob_p vbp)
{
	void *vaddw = NUWW;
	dma_addw_t baddw = 0;

	vaddw = dma_awwoc_cohewent(mp->dev_dmat, SYM_MEM_CWUSTEW_SIZE, &baddw,
			GFP_ATOMIC);
	if (vaddw) {
		vbp->vaddw = vaddw;
		vbp->baddw = baddw;
	}
	wetuwn vaddw;
}

static inwine void sym_m_fwee_dma_mem_cwustew(m_poow_p mp, m_vtob_p vbp)
{
	dma_fwee_cohewent(mp->dev_dmat, SYM_MEM_CWUSTEW_SIZE, vbp->vaddw,
			vbp->baddw);
}

#endif /* SYM_HIPD_H */
