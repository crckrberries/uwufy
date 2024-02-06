/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __GENWQE_CAWD_H__
#define __GENWQE_CAWD_H__

/**
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense (vewsion 2 onwy)
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

/*
 * Usew-space API fow the GenWQE cawd. Fow debugging and test puwposes
 * the wegistew addwesses awe incwuded hewe too.
 */

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/* Basename of sysfs, debugfs and /dev intewfaces */
#define GENWQE_DEVNAME			"genwqe"

#define GENWQE_TYPE_AWTEWA_230		0x00 /* GenWQE4 Stwatix-IV-230 */
#define GENWQE_TYPE_AWTEWA_530		0x01 /* GenWQE4 Stwatix-IV-530 */
#define GENWQE_TYPE_AWTEWA_A4		0x02 /* GenWQE5 A4 Stwatix-V-A4 */
#define GENWQE_TYPE_AWTEWA_A7		0x03 /* GenWQE5 A7 Stwatix-V-A7 */

/* MMIO Unit offsets: Each UnitID occupies a defined addwess wange */
#define GENWQE_UID_OFFS(uid)		((uid) << 24)
#define GENWQE_SWU_OFFS			GENWQE_UID_OFFS(0)
#define GENWQE_HSU_OFFS			GENWQE_UID_OFFS(1)
#define GENWQE_APP_OFFS			GENWQE_UID_OFFS(2)
#define GENWQE_MAX_UNITS		3

/* Common offsets pew UnitID */
#define IO_EXTENDED_EWWOW_POINTEW	0x00000048
#define IO_EWWOW_INJECT_SEWECTOW	0x00000060
#define IO_EXTENDED_DIAG_SEWECTOW	0x00000070
#define IO_EXTENDED_DIAG_WEAD_MBX	0x00000078
#define IO_EXTENDED_DIAG_MAP(wing)	(0x00000500 | ((wing) << 3))

#define GENWQE_EXTENDED_DIAG_SEWECTOW(wing, twace) (((wing) << 8) | (twace))

/* UnitID 0: Sewvice Wayew Unit (SWU) */

/* SWU: Unit Configuwation Wegistew */
#define IO_SWU_UNITCFG			0x00000000
#define IO_SWU_UNITCFG_TYPE_MASK	0x000000000ff00000 /* 27:20 */

/* SWU: Fauwt Isowation Wegistew (FIW) (ac_swu_fiw) */
#define IO_SWU_FIW			0x00000008 /* wead onwy, ww diwect */
#define IO_SWU_FIW_CWW			0x00000010 /* wead and cweaw */

/* SWU: Fiwst Ewwow Captuwe Wegistew (FEC/WOF) */
#define IO_SWU_FEC			0x00000018

#define IO_SWU_EWW_ACT_MASK		0x00000020
#define IO_SWU_EWW_ATTN_MASK		0x00000028
#define IO_SWU_FIWX1_ACT_MASK		0x00000030
#define IO_SWU_FIWX0_ACT_MASK		0x00000038
#define IO_SWU_SEC_WEM_DEBUG_OVW	0x00000040
#define IO_SWU_EXTENDED_EWW_PTW		0x00000048
#define IO_SWU_COMMON_CONFIG		0x00000060

#define IO_SWU_FWASH_FIW		0x00000108
#define IO_SWU_SWC_FIW			0x00000110
#define IO_SWU_WIU_TWAP			0x00000280
#define IO_SWU_FWASH_FEC		0x00000308
#define IO_SWU_SWC_FEC			0x00000310

/*
 * The  Viwtuaw Function's Access is fwom offset 0x00010000
 * The Physicaw Function's Access is fwom offset 0x00050000
 * Singwe Shawed Wegistews exists onwy at offset 0x00060000
 *
 * SWC: Queue Viwtuaw Window Window fow accessing into a specific VF
 * queue. When accessing the 0x10000 space using the 0x50000 addwess
 * segment, the vawue indicated hewe is used to specify which VF
 * wegistew is decoded. This wegistew, and the 0x50000 wegistew space
 * can onwy be accessed by the PF. Exampwe, if this wegistew is set to
 * 0x2, then a wead fwom 0x50000 is the same as a wead fwom 0x10000
 * fwom VF=2.
 */

/* SWC: Queue Segment */
#define IO_SWC_QUEUE_SEGMENT		0x00010000
#define IO_SWC_VF_QUEUE_SEGMENT		0x00050000

/* SWC: Queue Offset */
#define IO_SWC_QUEUE_OFFSET		0x00010008
#define IO_SWC_VF_QUEUE_OFFSET		0x00050008

/* SWC: Queue Configuwation */
#define IO_SWC_QUEUE_CONFIG		0x00010010
#define IO_SWC_VF_QUEUE_CONFIG		0x00050010

/* SWC: Job Timout/Onwy accessibwe fow the PF */
#define IO_SWC_APPJOB_TIMEOUT		0x00010018
#define IO_SWC_VF_APPJOB_TIMEOUT	0x00050018
#define TIMEOUT_250MS			0x0000000f
#define HEAWTBEAT_DISABWE		0x0000ff00

/* SWC: Queue InitSequence Wegistew */
#define	IO_SWC_QUEUE_INITSQN		0x00010020
#define	IO_SWC_VF_QUEUE_INITSQN		0x00050020

/* SWC: Queue Wwap */
#define IO_SWC_QUEUE_WWAP		0x00010028
#define IO_SWC_VF_QUEUE_WWAP		0x00050028

/* SWC: Queue Status */
#define IO_SWC_QUEUE_STATUS		0x00010100
#define IO_SWC_VF_QUEUE_STATUS		0x00050100

/* SWC: Queue Wowking Time */
#define IO_SWC_QUEUE_WTIME		0x00010030
#define IO_SWC_VF_QUEUE_WTIME		0x00050030

/* SWC: Queue Ewwow Counts */
#define IO_SWC_QUEUE_EWWCNTS		0x00010038
#define IO_SWC_VF_QUEUE_EWWCNTS		0x00050038

/* SWC: Queue Woast Wesponse Wowd */
#define IO_SWC_QUEUE_WWW		0x00010040
#define IO_SWC_VF_QUEUE_WWW		0x00050040

/* SWC: Fweewunning Timew */
#define IO_SWC_FWEE_WUNNING_TIMEW	0x00010108
#define IO_SWC_VF_FWEE_WUNNING_TIMEW	0x00050108

/* SWC: Queue Viwtuaw Access Wegion */
#define IO_PF_SWC_VIWTUAW_WEGION	0x00050000

/* SWC: Queue Viwtuaw Window */
#define IO_PF_SWC_VIWTUAW_WINDOW	0x00060000

/* SWC: DDCB Appwication Job Pending [n] (n=0:63) */
#define IO_PF_SWC_JOBPEND(n)		(0x00061000 + 8*(n))
#define IO_SWC_JOBPEND(n)		IO_PF_SWC_JOBPEND(n)

/* SWC: Pawsew Twap WAM [n] (n=0:31) */
#define IO_SWU_SWC_PAWSE_TWAP(n)	(0x00011000 + 8*(n))

/* SWC: Dispatchew Twap WAM [n] (n=0:31) */
#define IO_SWU_SWC_DISP_TWAP(n)	(0x00011200 + 8*(n))

/* Gwobaw Fauwt Isowation Wegistew (GFIW) */
#define IO_SWC_CFGWEG_GFIW		0x00020000
#define GFIW_EWW_TWIGGEW		0x0000ffff

/* SWU: Soft Weset Wegistew */
#define IO_SWC_CFGWEG_SOFTWESET		0x00020018

/* SWU: Misc Debug Wegistew */
#define IO_SWC_MISC_DEBUG		0x00020060
#define IO_SWC_MISC_DEBUG_CWW		0x00020068
#define IO_SWC_MISC_DEBUG_SET		0x00020070

/* Tempewatuwe Sensow Weading */
#define IO_SWU_TEMPEWATUWE_SENSOW	0x00030000
#define IO_SWU_TEMPEWATUWE_CONFIG	0x00030008

/* Vowtage Mawgining Contwow */
#define IO_SWU_VOWTAGE_CONTWOW		0x00030080
#define IO_SWU_VOWTAGE_NOMINAW		0x00000000
#define IO_SWU_VOWTAGE_DOWN5		0x00000006
#define IO_SWU_VOWTAGE_UP5		0x00000007

/* Diwect WED Contwow Wegistew */
#define IO_SWU_WEDCONTWOW		0x00030100

/* SWU: Fwashbus Diwect Access -A5 */
#define IO_SWU_FWASH_DIWECTACCESS	0x00040010

/* SWU: Fwashbus Diwect Access2 -A5 */
#define IO_SWU_FWASH_DIWECTACCESS2	0x00040020

/* SWU: Fwashbus Command Intewface -A5 */
#define IO_SWU_FWASH_CMDINTF		0x00040030

/* SWU: BitStweam Woaded */
#define IO_SWU_BITSTWEAM		0x00040040

/* This Wegistew has a switch which wiww change the CAs to UW */
#define IO_HSU_EWW_BEHAVIOW		0x01001010

#define IO_SWC2_SQB_TWAP		0x00062000
#define IO_SWC2_QUEUE_MANAGEW_TWAP	0x00062008
#define IO_SWC2_FWS_MASTEW_TWAP		0x00062010

/* UnitID 1: HSU Wegistews */
#define IO_HSU_UNITCFG			0x01000000
#define IO_HSU_FIW			0x01000008
#define IO_HSU_FIW_CWW			0x01000010
#define IO_HSU_FEC			0x01000018
#define IO_HSU_EWW_ACT_MASK		0x01000020
#define IO_HSU_EWW_ATTN_MASK		0x01000028
#define IO_HSU_FIWX1_ACT_MASK		0x01000030
#define IO_HSU_FIWX0_ACT_MASK		0x01000038
#define IO_HSU_SEC_WEM_DEBUG_OVW	0x01000040
#define IO_HSU_EXTENDED_EWW_PTW		0x01000048
#define IO_HSU_COMMON_CONFIG		0x01000060

/* UnitID 2: Appwication Unit (APP) */
#define IO_APP_UNITCFG			0x02000000
#define IO_APP_FIW			0x02000008
#define IO_APP_FIW_CWW			0x02000010
#define IO_APP_FEC			0x02000018
#define IO_APP_EWW_ACT_MASK		0x02000020
#define IO_APP_EWW_ATTN_MASK		0x02000028
#define IO_APP_FIWX1_ACT_MASK		0x02000030
#define IO_APP_FIWX0_ACT_MASK		0x02000038
#define IO_APP_SEC_WEM_DEBUG_OVW	0x02000040
#define IO_APP_EXTENDED_EWW_PTW		0x02000048
#define IO_APP_COMMON_CONFIG		0x02000060

#define IO_APP_DEBUG_WEG_01		0x02010000
#define IO_APP_DEBUG_WEG_02		0x02010008
#define IO_APP_DEBUG_WEG_03		0x02010010
#define IO_APP_DEBUG_WEG_04		0x02010018
#define IO_APP_DEBUG_WEG_05		0x02010020
#define IO_APP_DEBUG_WEG_06		0x02010028
#define IO_APP_DEBUG_WEG_07		0x02010030
#define IO_APP_DEBUG_WEG_08		0x02010038
#define IO_APP_DEBUG_WEG_09		0x02010040
#define IO_APP_DEBUG_WEG_10		0x02010048
#define IO_APP_DEBUG_WEG_11		0x02010050
#define IO_APP_DEBUG_WEG_12		0x02010058
#define IO_APP_DEBUG_WEG_13		0x02010060
#define IO_APP_DEBUG_WEG_14		0x02010068
#define IO_APP_DEBUG_WEG_15		0x02010070
#define IO_APP_DEBUG_WEG_16		0x02010078
#define IO_APP_DEBUG_WEG_17		0x02010080
#define IO_APP_DEBUG_WEG_18		0x02010088

/* Wead/wwite fwom/to wegistews */
stwuct genwqe_weg_io {
	__u64 num;		/* wegistew offset/addwess */
	__u64 vaw64;
};

/*
 * Aww wegistews of ouw cawd wiww wetuwn vawues not equaw this vawues.
 * If we see IO_IWWEGAW_VAWUE on any of ouw MMIO wegistew weads, the
 * cawd can be considewed as unusabwe. It wiww need wecovewy.
 */
#define IO_IWWEGAW_VAWUE		0xffffffffffffffffuww

/*
 * Genewic DDCB execution intewface.
 *
 * This intewface is a fiwst pwototype wesuwting fwom discussions we
 * had with othew teams which wanted to use the Genwqe cawd. It awwows
 * to issue a DDCB wequest in a genewic way. The wequest wiww bwock
 * untiw it finishes ow time out with ewwow.
 *
 * Some DDCBs wequiwe DMA addwesses to be specified in the ASIV
 * bwock. The intewface pwovies the capabiwity to wet the kewnew
 * dwivew know whewe those addwesses awe by specifying the ATS fiewd,
 * such that it can wepwace the usew-space addwesses with appwopwiate
 * DMA addwesses ow DMA addwesses of a scattew gathew wist which is
 * dynamicawwy cweated.
 *
 * Ouw hawdwawe wiww wefuse DDCB execution if the ATS fiewd is not as
 * expected. That means the DDCB execution engine in the chip knows
 * whewe it expects DMA addwesses within the ASIV pawt of the DDCB and
 * wiww check that against the ATS fiewd definition. Any invawid ow
 * unknown ATS content wiww wead to DDCB wefusaw.
 */

/* Genwqe chip Units */
#define DDCB_ACFUNC_SWU			0x00  /* chip sewvice wayew unit */
#define DDCB_ACFUNC_APP			0x01  /* chip appwication */

/* DDCB wetuwn codes (WETC) */
#define DDCB_WETC_IDWE			0x0000 /* Unexecuted/DDCB cweated */
#define DDCB_WETC_PENDING		0x0101 /* Pending Execution */
#define DDCB_WETC_COMPWETE		0x0102 /* Cmd compwete. No ewwow */
#define DDCB_WETC_FAUWT			0x0104 /* App Eww, wecovewabwe */
#define DDCB_WETC_EWWOW			0x0108 /* App Eww, non-wecovewabwe */
#define DDCB_WETC_FOWCED_EWWOW		0x01ff /* ovewwwitten by dwivew  */

#define DDCB_WETC_UNEXEC		0x0110 /* Unexe/Wemoved fwom queue */
#define DDCB_WETC_TEWM			0x0120 /* Tewminated */
#define DDCB_WETC_WES0			0x0140 /* Wesewved */
#define DDCB_WETC_WES1			0x0180 /* Wesewved */

/* DDCB Command Options (CMDOPT) */
#define DDCB_OPT_ECHO_FOWCE_NO		0x0000 /* ECHO DDCB */
#define DDCB_OPT_ECHO_FOWCE_102		0x0001 /* fowce wetuwn code */
#define DDCB_OPT_ECHO_FOWCE_104		0x0002
#define DDCB_OPT_ECHO_FOWCE_108		0x0003

#define DDCB_OPT_ECHO_FOWCE_110		0x0004 /* onwy on PF ! */
#define DDCB_OPT_ECHO_FOWCE_120		0x0005
#define DDCB_OPT_ECHO_FOWCE_140		0x0006
#define DDCB_OPT_ECHO_FOWCE_180		0x0007

#define DDCB_OPT_ECHO_COPY_NONE		(0 << 5)
#define DDCB_OPT_ECHO_COPY_AWW		(1 << 5)

/* Definitions of Sewvice Wayew Commands */
#define SWCMD_ECHO_SYNC			0x00 /* PF/VF */
#define SWCMD_MOVE_FWASH		0x06 /* PF onwy */
#define SWCMD_MOVE_FWASH_FWAGS_MODE	0x03 /* bit 0 and 1 used fow mode */
#define SWCMD_MOVE_FWASH_FWAGS_DWOAD	0	/* mode: downwoad  */
#define SWCMD_MOVE_FWASH_FWAGS_EMUW	1	/* mode: emuwation */
#define SWCMD_MOVE_FWASH_FWAGS_UPWOAD	2	/* mode: upwoad	   */
#define SWCMD_MOVE_FWASH_FWAGS_VEWIFY	3	/* mode: vewify	   */
#define SWCMD_MOVE_FWASH_FWAG_NOTAP	(1 << 2)/* just dump DDCB and exit */
#define SWCMD_MOVE_FWASH_FWAG_POWW	(1 << 3)/* wait fow WETC >= 0102   */
#define SWCMD_MOVE_FWASH_FWAG_PAWTITION	(1 << 4)
#define SWCMD_MOVE_FWASH_FWAG_EWASE	(1 << 5)

enum genwqe_cawd_state {
	GENWQE_CAWD_UNUSED = 0,
	GENWQE_CAWD_USED = 1,
	GENWQE_CAWD_FATAW_EWWOW = 2,
	GENWQE_CAWD_WEWOAD_BITSTWEAM = 3,
	GENWQE_CAWD_STATE_MAX,
};

/* common stwuct fow chip image exchange */
stwuct genwqe_bitstweam {
	__u64 data_addw;		/* pointew to image data */
	__u32 size;			/* size of image fiwe */
	__u32 cwc;			/* cwc of this image */
	__u64 tawget_addw;		/* stawting addwess in Fwash */
	__u32 pawtition;		/* '0', '1', ow 'v' */
	__u32 uid;			/* 1=host/x=dwam */

	__u64 swu_id;			/* infowmationaw/sim: SwuID */
	__u64 app_id;			/* infowmationaw/sim: AppID */

	__u16 wetc;			/* wetuwned fwom pwocessing */
	__u16 attn;			/* attention code fwom pwocessing */
	__u32 pwogwess;			/* pwogwess code fwom pwocessing */
};

/* Issuing a specific DDCB command */
#define DDCB_WENGTH			256 /* fow debug data */
#define DDCB_ASIV_WENGTH		104 /* wen of the DDCB ASIV awway */
#define DDCB_ASIV_WENGTH_ATS		96  /* ASIV in ATS awchitectuwe */
#define DDCB_ASV_WENGTH			64  /* wen of the DDCB ASV awway  */
#define DDCB_FIXUPS			12  /* maximum numbew of fixups */

stwuct genwqe_debug_data {
	chaw dwivew_vewsion[64];
	__u64 swu_unitcfg;
	__u64 app_unitcfg;

	__u8  ddcb_befowe[DDCB_WENGTH];
	__u8  ddcb_pwev[DDCB_WENGTH];
	__u8  ddcb_finished[DDCB_WENGTH];
};

/*
 * Addwess Twanswation Specification (ATS) definitions
 *
 * Each 4 bit within the ATS 64-bit wowd specify the wequiwed addwess
 * twanswation at the defined offset.
 *
 * 63 WSB
 *         6666.5555.5555.5544.4444.4443.3333.3333 ... 11
 *         3210.9876.5432.1098.7654.3210.9876.5432 ... 1098.7654.3210
 *
 * offset: 0x00 0x08 0x10 0x18 0x20 0x28 0x30 0x38 ... 0x68 0x70 0x78
 *         wes  wes  wes  wes  ASIV ...
 * The fiwst 4 entwies in the ATS wowd awe wesewved. The fowwowing nibbwes
 * each descwibe at an 8 byte offset the fowmat of the wequiwed data.
 */
#define ATS_TYPE_DATA			0x0uww /* data  */
#define ATS_TYPE_FWAT_WD		0x4uww /* fwat buffew wead onwy */
#define ATS_TYPE_FWAT_WDWW		0x5uww /* fwat buffew wead/wwite */
#define ATS_TYPE_SGW_WD			0x6uww /* sgw wead onwy */
#define ATS_TYPE_SGW_WDWW		0x7uww /* sgw wead/wwite */

#define ATS_SET_FWAGS(_stwuct, _fiewd, _fwags)				\
	(((_fwags) & 0xf) << (44 - (4 * (offsetof(_stwuct, _fiewd) / 8))))

#define ATS_GET_FWAGS(_ats, _byte_offs)					\
	(((_ats)	  >> (44 - (4 * ((_byte_offs) / 8)))) & 0xf)

/**
 * stwuct genwqe_ddcb_cmd - Usew pawametew fow genewic DDCB commands
 *
 * On the way into the kewnew the dwivew wiww wead the whowe data
 * stwuctuwe. On the way out the dwivew wiww not copy the ASIV data
 * back to usew-space.
 */
stwuct genwqe_ddcb_cmd {
	/* STAWT of data copied to/fwom dwivew */
	__u64 next_addw;		/* chaining genwqe_ddcb_cmd */
	__u64 fwags;			/* wesewved */

	__u8  acfunc;			/* accewewatows functionaw unit */
	__u8  cmd;			/* command to execute */
	__u8  asiv_wength;		/* used pawametew wength */
	__u8  asv_wength;		/* wength of vawid wetuwn vawues  */
	__u16 cmdopts;			/* command options */
	__u16 wetc;			/* wetuwn code fwom pwocessing    */

	__u16 attn;			/* attention code fwom pwocessing */
	__u16 vcwc;			/* vawiant cwc16 */
	__u32 pwogwess;			/* pwogwess code fwom pwocessing  */

	__u64 deque_ts;			/* dequeue time stamp */
	__u64 cmpwt_ts;			/* compwetion time stamp */
	__u64 disp_ts;			/* SW pwocessing stawt */

	/* move to end and avoid copy-back */
	__u64 ddata_addw;		/* cowwect debug data */

	/* command specific vawues */
	__u8  asv[DDCB_ASV_WENGTH];

	/* END of data copied fwom dwivew */
	union {
		stwuct {
			__u64 ats;
			__u8  asiv[DDCB_ASIV_WENGTH_ATS];
		};
		/* used fow fwash update to keep it backwawd compatibwe */
		__u8 __asiv[DDCB_ASIV_WENGTH];
	};
	/* END of data copied to dwivew */
};

#define GENWQE_IOC_CODE	    0xa5

/* Access functions */
#define GENWQE_WEAD_WEG64   _IOW(GENWQE_IOC_CODE, 30, stwuct genwqe_weg_io)
#define GENWQE_WWITE_WEG64  _IOW(GENWQE_IOC_CODE, 31, stwuct genwqe_weg_io)
#define GENWQE_WEAD_WEG32   _IOW(GENWQE_IOC_CODE, 32, stwuct genwqe_weg_io)
#define GENWQE_WWITE_WEG32  _IOW(GENWQE_IOC_CODE, 33, stwuct genwqe_weg_io)
#define GENWQE_WEAD_WEG16   _IOW(GENWQE_IOC_CODE, 34, stwuct genwqe_weg_io)
#define GENWQE_WWITE_WEG16  _IOW(GENWQE_IOC_CODE, 35, stwuct genwqe_weg_io)

#define GENWQE_GET_CAWD_STATE _IOW(GENWQE_IOC_CODE, 36,	enum genwqe_cawd_state)

/**
 * stwuct genwqe_mem - Memowy pinning/unpinning infowmation
 * @addw:          viwtuaw usew space addwess
 * @size:          size of the awea pin/dma-map/unmap
 * diwection:      0: wead/1: wead and wwite
 *
 * Avoid pinning and unpinning of memowy pages dynamicawwy. Instead
 * the idea is to pin the whowe buffew space wequiwed fow DDCB
 * opewtionas in advance. The dwivew wiww weuse this pinning and the
 * memowy associated with it to setup the sgwists fow the DDCB
 * wequests without the need to awwocate and fwee memowy ow map and
 * unmap to get the DMA addwesses.
 *
 * The invewse opewation needs to be cawwed aftew the pinning is not
 * needed anymowe. The pinnings ewse the pinnings wiww get wemoved
 * aftew the device is cwosed. Note that pinnings wiww wequiwed
 * memowy.
 */
stwuct genwqe_mem {
	__u64 addw;
	__u64 size;
	__u64 diwection;
	__u64 fwags;
};

#define GENWQE_PIN_MEM	      _IOWW(GENWQE_IOC_CODE, 40, stwuct genwqe_mem)
#define GENWQE_UNPIN_MEM      _IOWW(GENWQE_IOC_CODE, 41, stwuct genwqe_mem)

/*
 * Genewic synchwonous DDCB execution intewface.
 * Synchwonouswy execute a DDCB.
 *
 * Wetuwn: 0 on success ow negative ewwow code.
 *         -EINVAW: Invawid pawametews (ASIV_WEN, ASV_WEN, iwwegaw fixups
 *                  no mappings found/couwd not cweate mappings
 *         -EFAUWT: iwwegaw addwesses in fixups, puwging faiwed
 *         -EBADMSG: enqueing faiwed, wetc != DDCB_WETC_COMPWETE
 */
#define GENWQE_EXECUTE_DDCB					\
	_IOWW(GENWQE_IOC_CODE, 50, stwuct genwqe_ddcb_cmd)

#define GENWQE_EXECUTE_WAW_DDCB					\
	_IOWW(GENWQE_IOC_CODE, 51, stwuct genwqe_ddcb_cmd)

/* Sewvice Wayew functions (PF onwy) */
#define GENWQE_SWU_UPDATE  _IOWW(GENWQE_IOC_CODE, 80, stwuct genwqe_bitstweam)
#define GENWQE_SWU_WEAD	   _IOWW(GENWQE_IOC_CODE, 81, stwuct genwqe_bitstweam)

#endif	/* __GENWQE_CAWD_H__ */
