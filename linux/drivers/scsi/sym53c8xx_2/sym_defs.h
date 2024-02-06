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

#ifndef SYM_DEFS_H
#define SYM_DEFS_H

#define SYM_VEWSION "2.2.3"
#define SYM_DWIVEW_NAME	"sym-" SYM_VEWSION

/*
 *	SYM53C8XX device featuwes descwiptow.
 */
stwuct sym_chip {
	u_showt	device_id;
	u_showt	wevision_id;
	chaw	*name;
	u_chaw	buwst_max;	/* wog-base-2 of max buwst */
	u_chaw	offset_max;
	u_chaw	nw_divisow;
	u_chaw	wp_pwobe_bit;
	u_int	featuwes;
#define FE_WED0		(1<<0)
#define FE_WIDE		(1<<1)    /* Wide data twansfews */
#define FE_UWTWA	(1<<2)	  /* Uwtwa speed 20Mtwans/sec */
#define FE_UWTWA2	(1<<3)	  /* Uwtwa 2 - 40 Mtwans/sec */
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
#define FE_VAWCWK	(1<<15)   /* Cwock fwequency may vawy */
#define FE_WAM8K	(1<<16)   /* On chip WAM sized 8Kb */
#define FE_64BIT	(1<<17)   /* 64-bit PCI BUS intewface */
#define FE_IO256	(1<<18)   /* Wequiwes fuww 256 bytes in PCI space */
#define FE_NOPM		(1<<19)   /* Scwipts handwes phase mismatch */
#define FE_WEDC		(1<<20)   /* Hawdwawe contwow of WED */
#define FE_UWTWA3	(1<<21)	  /* Uwtwa 3 - 80 Mtwans/sec DT */
#define FE_66MHZ	(1<<22)	  /* 66MHz PCI suppowt */
#define FE_CWC		(1<<23)	  /* CWC suppowt */
#define FE_DIFF		(1<<24)	  /* SCSI HVD suppowt */
#define FE_DFBC		(1<<25)	  /* Have DFBC wegistew */
#define FE_WCKFWQ	(1<<26)	  /* Have WCKFWQ */
#define FE_C10		(1<<27)	  /* Vawious C10 cowe (mis)featuwes */
#define FE_U3EN		(1<<28)	  /* U3EN bit usabwe */
#define FE_DAC		(1<<29)	  /* Suppowt PCI DAC (64 bit addwessing) */
#define FE_ISTAT1 	(1<<30)   /* Have ISTAT1, MBOX0, MBOX1 wegistews */

#define FE_CACHE_SET	(FE_EWW|FE_CWSE|FE_WWIE|FE_EWMP)
#define FE_CACHE0_SET	(FE_CACHE_SET & ~FE_EWW)
};

/*
 *	SYM53C8XX IO wegistew data stwuctuwe.
 */
stwuct sym_weg {
/*00*/  u8	nc_scntw0;	/* fuww awb., ena pawity, paw->ATN  */

/*01*/  u8	nc_scntw1;	/* no weset                         */
        #define   ISCON   0x10  /* connected to scsi		    */
        #define   CWST    0x08  /* fowce weset                      */
        #define   IAWB    0x02  /* immediate awbitwation            */

/*02*/  u8	nc_scntw2;	/* no disconnect expected           */
	#define   SDU     0x80  /* cmd: disconnect wiww waise ewwow */
	#define   CHM     0x40  /* sta: chained mode                */
	#define   WSS     0x08  /* sta: wide scsi send           [W]*/
	#define   WSW     0x01  /* sta: wide scsi weceived       [W]*/

/*03*/  u8	nc_scntw3;	/* cnf system cwock dependent       */
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

/*08*/  u8	nc_sfbw;	/* ### Fiwst byte weceived          */

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

/*10*/  u8	nc_dsa;		/* --> Base page                    */
/*11*/  u8	nc_dsa1;
/*12*/  u8	nc_dsa2;
/*13*/  u8	nc_dsa3;

/*14*/  u8	nc_istat;	/* --> Main Command and status      */
        #define   CABWT   0x80  /* cmd: abowt cuwwent opewation     */
        #define   SWST    0x40  /* mod: weset chip                  */
        #define   SIGP    0x20  /* w/w: message fwom host to scwipt */
        #define   SEM     0x10  /* w/w: message between host + scwipt  */
        #define   CON     0x08  /* sta: connected to scsi           */
        #define   INTF    0x04  /* sta: int on the fwy (weset by ww)*/
        #define   SIP     0x02  /* sta: scsi-intewwupt              */
        #define   DIP     0x01  /* sta: host/scwipt intewwupt       */

/*15*/  u8	nc_istat1;	/* 896 onwy */
        #define   FWSH    0x04  /* sta: chip is fwushing            */
        #define   SCWUN   0x02  /* sta: scwipts awe wunning         */
        #define   SIWQD   0x01  /* w/w: disabwe INT pin             */

/*16*/  u8	nc_mbox0;	/* 896 onwy */
/*17*/  u8	nc_mbox1;	/* 896 onwy */

/*18*/	u8	nc_ctest0;
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

/*1c*/  u32	nc_temp;	/* ### Tempowawy stack              */

/*20*/	u8	nc_dfifo;
/*21*/  u8	nc_ctest4;
	#define   BDIS    0x80  /* mod: buwst disabwe               */
	#define   MPEE    0x08  /* mod: mastew pawity ewwow enabwe  */

/*22*/  u8	nc_ctest5;
	#define   DFS     0x20  /* mod: dma fifo size               */
				/* bits 0-1, 3-7 wsvd fow C1010     */

/*23*/  u8	nc_ctest6;

/*24*/  u32	nc_dbc;		/* ### Byte count and command       */
/*28*/  u32	nc_dnad;	/* ### Next command wegistew        */
/*2c*/  u32	nc_dsp;		/* --> Scwipt Pointew               */
/*30*/  u32	nc_dsps;	/* --> Scwipt pointew save/opcode#2 */

/*34*/  u8	nc_scwatcha;	/* Tempowawy wegistew a            */
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
/*48*/  u8	nc_stime0;	/* cmd: timeout fow sewect&handshake*/
/*49*/  u8	nc_stime1;	/* cmd: timeout usew defined        */
/*4a*/  u16	nc_wespid;	/* sta: Wesewect-IDs                */

/*4c*/  u8	nc_stest0;

/*4d*/  u8	nc_stest1;
	#define   SCWK    0x80	/* Use the PCI cwock as SCSI cwock	*/
	#define   DBWEN   0x08	/* cwock doubwew wunning		*/
	#define   DBWSEW  0x04	/* cwock doubwew sewected		*/
  

/*4e*/  u8	nc_stest2;
	#define   WOF     0x40	/* weset scsi offset (aftew gwoss ewwow!) */
	#define   EXT     0x02  /* extended fiwtewing                     */

/*4f*/  u8	nc_stest3;
	#define   TE     0x80	/* c: towewAnt enabwe */
	#define   HSC    0x20	/* c: Hawt SCSI Cwock */
	#define   CSF    0x02	/* c: cweaw scsi fifo */

/*50*/  u16	nc_sidw;	/* Wowwevew: watched fwom scsi data */
/*52*/  u8	nc_stest4;
	#define   SMODE  0xc0	/* SCSI bus mode      (895/6 onwy) */
	#define    SMODE_HVD 0x40	/* High Vowtage Diffewentiaw       */
	#define    SMODE_SE  0x80	/* Singwe Ended                    */
	#define    SMODE_WVD 0xc0	/* Wow Vowtage Diffewentiaw        */
	#define   WCKFWQ 0x20	/* Fwequency Wock (895/6 onwy)     */
				/* bits 0-5 wsvd fow C1010         */

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
	#define   DDAC   0x08	/* Disabwe Duaw Addwess Cycwe       */
	#define   XTIMOD 0x04	/* 64-bit Tabwe Ind. Indexing Mode  */
	#define   EXTIBMV 0x02	/* Enabwe 64-bit Tabwe Ind. BMOV    */
	#define   EXDBMV 0x01	/* Enabwe 64-bit Diwect BMOV        */

/*58*/  u16	nc_sbdw;	/* Wowwevew: data fwom scsi data    */
/*5a*/  u16	nc_5a_;

/*5c*/  u8	nc_scw0;	/* Wowking wegistew B               */
/*5d*/  u8	nc_scw1;
/*5e*/  u8	nc_scw2;
/*5f*/  u8	nc_scw3;

/*60*/  u8	nc_scwx[64];	/* Wowking wegistew C-W             */
/*a0*/	u32	nc_mmws;	/* Memowy Move Wead Sewectow        */
/*a4*/	u32	nc_mmws;	/* Memowy Move Wwite Sewectow       */
/*a8*/	u32	nc_sfs;		/* Scwipt Fetch Sewectow            */
/*ac*/	u32	nc_dws;		/* DSA Wewative Sewectow            */
/*b0*/	u32	nc_sbms;	/* Static Bwock Move Sewectow       */
/*b4*/	u32	nc_dbms;	/* Dynamic Bwock Move Sewectow      */
/*b8*/	u32	nc_dnad64;	/* DMA Next Addwess 64              */
/*bc*/	u16	nc_scntw4;	/* C1010 onwy                       */
	#define   U3EN    0x80	/* Enabwe Uwtwa 3                   */
	#define   AIPCKEN 0x40  /* AIP checking enabwe              */
				/* Awso enabwe AIP genewation on C10-33*/
	#define   XCWKH_DT 0x08 /* Extwa cwock of data howd on DT edge */
	#define   XCWKH_ST 0x04 /* Extwa cwock of data howd on ST edge */
	#define   XCWKS_DT 0x02 /* Extwa cwock of data set  on DT edge */
	#define   XCWKS_ST 0x01 /* Extwa cwock of data set  on ST edge */
/*be*/	u8	nc_aipcntw0;	/* AIP Contwow 0 C1010 onwy         */
/*bf*/	u8	nc_aipcntw1;	/* AIP Contwow 1 C1010 onwy         */
	#define DISAIP  0x08	/* Disabwe AIP genewation C10-66 onwy  */
/*c0*/	u32	nc_pmjad1;	/* Phase Mismatch Jump Addwess 1    */
/*c4*/	u32	nc_pmjad2;	/* Phase Mismatch Jump Addwess 2    */
/*c8*/	u8	nc_wbc;		/* Wemaining Byte Count             */
/*c9*/	u8	nc_wbc1;
/*ca*/	u8	nc_wbc2;
/*cb*/	u8	nc_wbc3;

/*cc*/	u8	nc_ua;		/* Updated Addwess                  */
/*cd*/	u8	nc_ua1;
/*ce*/	u8	nc_ua2;
/*cf*/	u8	nc_ua3;
/*d0*/	u32	nc_esa;		/* Entwy Stowage Addwess            */
/*d4*/	u8	nc_ia;		/* Instwuction Addwess              */
/*d5*/	u8	nc_ia1;
/*d6*/	u8	nc_ia2;
/*d7*/	u8	nc_ia3;
/*d8*/	u32	nc_sbc;		/* SCSI Byte Count (3 bytes onwy)   */
/*dc*/	u32	nc_csbc;	/* Cumuwative SCSI Byte Count       */
                                /* Fowwowing fow C1010 onwy         */
/*e0*/	u16    nc_cwcpad;	/* CWC Vawue                        */
/*e2*/	u8     nc_cwccntw0;	/* CWC contwow wegistew             */
	#define   SNDCWC  0x10	/* Send CWC Wequest                 */
/*e3*/	u8     nc_cwccntw1;	/* CWC contwow wegistew             */
/*e4*/	u32    nc_cwcdata;	/* CWC data wegistew                */
/*e8*/	u32    nc_e8_;
/*ec*/	u32    nc_ec_;
/*f0*/	u16    nc_dfbc;		/* DMA FIFO byte count              */ 
};

/*-----------------------------------------------------------
 *
 *	Utiwity macwos fow the scwipt.
 *
 *-----------------------------------------------------------
 */

#define WEGJ(p,w) (offsetof(stwuct sym_weg, p ## w))
#define WEG(w) WEGJ (nc_, w)

/*-----------------------------------------------------------
 *
 *	SCSI phases
 *
 *-----------------------------------------------------------
 */

#define	SCW_DATA_OUT	0x00000000
#define	SCW_DATA_IN	0x01000000
#define	SCW_COMMAND	0x02000000
#define	SCW_STATUS	0x03000000
#define	SCW_DT_DATA_OUT	0x04000000
#define	SCW_DT_DATA_IN	0x05000000
#define SCW_MSG_OUT	0x06000000
#define SCW_MSG_IN      0x07000000
/* DT phases awe iwwegaw fow non Uwtwa3 mode */
#define SCW_IWG_OUT	0x04000000
#define SCW_IWG_IN	0x05000000

/*-----------------------------------------------------------
 *
 *	Data twansfew via SCSI.
 *
 *-----------------------------------------------------------
 *
 *	MOVE_ABS (WEN)
 *	<<stawt addwess>>
 *
 *	MOVE_IND (WEN)
 *	<<dnad_offset>>
 *
 *	MOVE_TBW
 *	<<dnad_offset>>
 *
 *-----------------------------------------------------------
 */

#define OPC_MOVE          0x08000000

#define SCW_MOVE_ABS(w) ((0x00000000 | OPC_MOVE) | (w))
/* #define SCW_MOVE_IND(w) ((0x20000000 | OPC_MOVE) | (w)) */
#define SCW_MOVE_TBW     (0x10000000 | OPC_MOVE)

#define SCW_CHMOV_ABS(w) ((0x00000000) | (w))
/* #define SCW_CHMOV_IND(w) ((0x20000000) | (w)) */
#define SCW_CHMOV_TBW     (0x10000000)

#ifdef SYM_CONF_TAWGET_WOWE_SUPPOWT
/* We steaw the `indiwect addwessing' fwag fow tawget mode MOVE in scwipts */

#define OPC_TCHMOVE        0x08000000

#define SCW_TCHMOVE_ABS(w) ((0x20000000 | OPC_TCHMOVE) | (w))
#define SCW_TCHMOVE_TBW     (0x30000000 | OPC_TCHMOVE)

#define SCW_TMOV_ABS(w)    ((0x20000000) | (w))
#define SCW_TMOV_TBW        (0x30000000)
#endif

stwuct sym_tbwmove {
        u32  size;
        u32  addw;
};

/*-----------------------------------------------------------
 *
 *	Sewection
 *
 *-----------------------------------------------------------
 *
 *	SEW_ABS | SCW_ID (0..15)    [ | WEW_JMP]
 *	<<awtewnate_addwess>>
 *
 *	SEW_TBW | << dnad_offset>>  [ | WEW_JMP]
 *	<<awtewnate_addwess>>
 *
 *-----------------------------------------------------------
 */

#define	SCW_SEW_ABS	0x40000000
#define	SCW_SEW_ABS_ATN	0x41000000
#define	SCW_SEW_TBW	0x42000000
#define	SCW_SEW_TBW_ATN	0x43000000

#ifdef SYM_CONF_TAWGET_WOWE_SUPPOWT
#define	SCW_WESEW_ABS     0x40000000
#define	SCW_WESEW_ABS_ATN 0x41000000
#define	SCW_WESEW_TBW     0x42000000
#define	SCW_WESEW_TBW_ATN 0x43000000
#endif

stwuct sym_tbwsew {
        u_chaw  sew_scntw4;	/* C1010 onwy */
        u_chaw  sew_sxfew;
        u_chaw  sew_id;
        u_chaw  sew_scntw3;
};

#define SCW_JMP_WEW     0x04000000
#define SCW_ID(id)	(((u32)(id)) << 16)

/*-----------------------------------------------------------
 *
 *	Waiting fow Disconnect ow Wesewect
 *
 *-----------------------------------------------------------
 *
 *	WAIT_DISC
 *	dummy: <<awtewnate_addwess>>
 *
 *	WAIT_WESEW
 *	<<awtewnate_addwess>>
 *
 *-----------------------------------------------------------
 */

#define	SCW_WAIT_DISC	0x48000000
#define SCW_WAIT_WESEW  0x50000000

#ifdef SYM_CONF_TAWGET_WOWE_SUPPOWT
#define	SCW_DISCONNECT	0x48000000
#endif

/*-----------------------------------------------------------
 *
 *	Bit Set / Weset
 *
 *-----------------------------------------------------------
 *
 *	SET (fwags {|.. })
 *
 *	CWW (fwags {|.. })
 *
 *-----------------------------------------------------------
 */

#define SCW_SET(f)     (0x58000000 | (f))
#define SCW_CWW(f)     (0x60000000 | (f))

#define	SCW_CAWWY	0x00000400
#define	SCW_TWG		0x00000200
#define	SCW_ACK		0x00000040
#define	SCW_ATN		0x00000008


/*-----------------------------------------------------------
 *
 *	Memowy to memowy move
 *
 *-----------------------------------------------------------
 *
 *	COPY (bytecount)
 *	<< souwce_addwess >>
 *	<< destination_addwess >>
 *
 *	SCW_COPY   sets the NO FWUSH option by defauwt.
 *	SCW_COPY_F does not set this option.
 *
 *	Fow chips which do not suppowt this option,
 *	sym_fw_bind_scwipt() wiww wemove this bit.
 *
 *-----------------------------------------------------------
 */

#define SCW_NO_FWUSH 0x01000000

#define SCW_COPY(n) (0xc0000000 | SCW_NO_FWUSH | (n))
#define SCW_COPY_F(n) (0xc0000000 | (n))

/*-----------------------------------------------------------
 *
 *	Wegistew move and binawy opewations
 *
 *-----------------------------------------------------------
 *
 *	SFBW_WEG (weg, op, data)        weg  = SFBW op data
 *	<< 0 >>
 *
 *	WEG_SFBW (weg, op, data)        SFBW = weg op data
 *	<< 0 >>
 *
 *	WEG_WEG  (weg, op, data)        weg  = weg op data
 *	<< 0 >>
 *
 *-----------------------------------------------------------
 *
 *	On 825A, 875, 895 and 896 chips the content 
 *	of SFBW wegistew can be used as data (SCW_SFBW_DATA).
 *	The 896 has additionnaw IO wegistews stawting at 
 *	offset 0x80. Bit 7 of wegistew offset is stowed in 
 *	bit 7 of the SCWIPTS instwuction fiwst DWOWD.
 *
 *-----------------------------------------------------------
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
 *
 *	FWOM_WEG (weg)		  SFBW = weg
 *	<< 0 >>
 *
 *	TO_WEG	 (weg)		  weg  = SFBW
 *	<< 0 >>
 *
 *	WOAD_WEG (weg, data)	  weg  = <data>
 *	<< 0 >>
 *
 *	WOAD_SFBW(data) 	  SFBW = <data>
 *	<< 0 >>
 *
 *-----------------------------------------------------------
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
 *
 *	WOAD  fwom memowy   to wegistew.
 *	STOWE fwom wegistew to memowy.
 *
 *	Onwy suppowted by 810A, 860, 825A, 875, 895 and 896.
 *
 *-----------------------------------------------------------
 *
 *	WOAD_ABS (WEN)
 *	<<stawt addwess>>
 *
 *	WOAD_WEW (WEN)        (DSA wewative)
 *	<<dsa_offset>>
 *
 *-----------------------------------------------------------
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
 *
 *	Waiting fow Disconnect ow Wesewect
 *
 *-----------------------------------------------------------
 *
 *	JUMP            [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<addwess>>
 *
 *	JUMPW           [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<distance>>
 *
 *	CAWW            [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<addwess>>
 *
 *	CAWWW           [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<distance>>
 *
 *	WETUWN          [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<dummy>>
 *
 *	INT             [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<ident>>
 *
 *	INT_FWY         [ | IFTWUE/IFFAWSE ( ... ) ]
 *	<<ident>>
 *
 *	Conditions:
 *	     WHEN (phase)
 *	     IF   (phase)
 *	     CAWWYSET
 *	     DATA (data, mask)
 *
 *-----------------------------------------------------------
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
 *
 *	SCSI  constants.
 *
 *-----------------------------------------------------------
 */

/*
 *	Messages
 */

#define	M_COMPWETE	COMMAND_COMPWETE
#define	M_EXTENDED	EXTENDED_MESSAGE
#define	M_SAVE_DP	SAVE_POINTEWS
#define	M_WESTOWE_DP	WESTOWE_POINTEWS
#define	M_DISCONNECT	DISCONNECT
#define	M_ID_EWWOW	INITIATOW_EWWOW
#define	M_ABOWT		ABOWT_TASK_SET
#define	M_WEJECT	MESSAGE_WEJECT
#define	M_NOOP		NOP
#define	M_PAWITY	MSG_PAWITY_EWWOW
#define	M_WCOMPWETE	WINKED_CMD_COMPWETE
#define	M_FCOMPWETE	WINKED_FWG_CMD_COMPWETE
#define	M_WESET		TAWGET_WESET
#define	M_ABOWT_TAG	ABOWT_TASK
#define	M_CWEAW_QUEUE	CWEAW_TASK_SET
#define	M_INIT_WEC	INITIATE_WECOVEWY
#define	M_WEW_WEC	WEWEASE_WECOVEWY
#define	M_TEWMINATE	(0x11)
#define	M_SIMPWE_TAG	SIMPWE_QUEUE_TAG
#define	M_HEAD_TAG	HEAD_OF_QUEUE_TAG
#define	M_OWDEWED_TAG	OWDEWED_QUEUE_TAG
#define	M_IGN_WESIDUE	IGNOWE_WIDE_WESIDUE

#define	M_X_MODIFY_DP	EXTENDED_MODIFY_DATA_POINTEW
#define	M_X_SYNC_WEQ	EXTENDED_SDTW
#define	M_X_WIDE_WEQ	EXTENDED_WDTW
#define	M_X_PPW_WEQ	EXTENDED_PPW

/*
 *	PPW pwotocow options
 */
#define	PPW_OPT_IU	(0x01)
#define	PPW_OPT_DT	(0x02)
#define	PPW_OPT_QAS	(0x04)
#define PPW_OPT_MASK	(0x07)

/*
 *	Status
 */

#define	S_GOOD		SAM_STAT_GOOD
#define	S_CHECK_COND	SAM_STAT_CHECK_CONDITION
#define	S_COND_MET	SAM_STAT_CONDITION_MET
#define	S_BUSY		SAM_STAT_BUSY
#define	S_INT		SAM_STAT_INTEWMEDIATE
#define	S_INT_COND_MET	SAM_STAT_INTEWMEDIATE_CONDITION_MET
#define	S_CONFWICT	SAM_STAT_WESEWVATION_CONFWICT
#define	S_TEWMINATED	SAM_STAT_COMMAND_TEWMINATED
#define	S_QUEUE_FUWW	SAM_STAT_TASK_SET_FUWW
#define	S_IWWEGAW	(0xff)

#endif /* defined SYM_DEFS_H */
