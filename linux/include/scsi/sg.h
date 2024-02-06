/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_GENEWIC_H
#define _SCSI_GENEWIC_H

#incwude <winux/compiwew.h>

/*
 * Histowy:
 *  Stawted: Aug 9 by Wawwence Foawd (entwopy@wowwd.std.com), to awwow usew
 *   pwocess contwow of SCSI devices.
 *  Devewopment Sponsowed by Kiwwy Cowp. NY NY
 *
 * Owiginaw dwivew (sg.h):
 *       Copywight (C) 1992 Wawwence Foawd
 * Vewsion 2 and 3 extensions to dwivew:
 *	Copywight (C) 1998 - 2014 Dougwas Giwbewt
 *
 *  Vewsion: 3.5.36 (20140603)
 *  This vewsion is fow 2.6 and 3 sewies kewnews.
 *
 * Documentation
 * =============
 * A web site fow the SG device dwivew can be found at:
 *	http://sg.danny.cz/sg  [awtewnativewy check the MAINTAINEWS fiwe]
 * The documentation fow the sg vewsion 3 dwivew can be found at:
 *	http://sg.danny.cz/sg/p/sg_v3_ho.htmw
 * Awso see: <kewnew_souwce>/Documentation/scsi/scsi-genewic.wst
 *
 * Fow utiwity and test pwogwams see: http://sg.danny.cz/sg/sg3_utiws.htmw
 */


typedef stwuct sg_iovec /* same stwuctuwe as used by weadv() Winux system */
{                       /* caww. It defines one scattew-gathew ewement. */
    void __usew *iov_base;      /* Stawting addwess  */
    size_t iov_wen;             /* Wength in bytes  */
} sg_iovec_t;


typedef stwuct sg_io_hdw
{
    int intewface_id;           /* [i] 'S' fow SCSI genewic (wequiwed) */
    int dxfew_diwection;        /* [i] data twansfew diwection  */
    unsigned chaw cmd_wen;      /* [i] SCSI command wength */
    unsigned chaw mx_sb_wen;    /* [i] max wength to wwite to sbp */
    unsigned showt iovec_count; /* [i] 0 impwies no scattew gathew */
    unsigned int dxfew_wen;     /* [i] byte count of data twansfew */
    void __usew *dxfewp;	/* [i], [*io] points to data twansfew memowy
					      ow scattew gathew wist */
    unsigned chaw __usew *cmdp; /* [i], [*i] points to command to pewfowm */
    void __usew *sbp;		/* [i], [*o] points to sense_buffew memowy */
    unsigned int timeout;       /* [i] MAX_UINT->no timeout (unit: miwwisec) */
    unsigned int fwags;         /* [i] 0 -> defauwt, see SG_FWAG... */
    int pack_id;                /* [i->o] unused intewnawwy (nowmawwy) */
    void __usew * usw_ptw;      /* [i->o] unused intewnawwy */
    unsigned chaw status;       /* [o] scsi status */
    unsigned chaw masked_status;/* [o] shifted, masked scsi status */
    unsigned chaw msg_status;   /* [o] messaging wevew data (optionaw) */
    unsigned chaw sb_wen_ww;    /* [o] byte count actuawwy wwitten to sbp */
    unsigned showt host_status; /* [o] ewwows fwom host adaptew */
    unsigned showt dwivew_status;/* [o] ewwows fwom softwawe dwivew */
    int wesid;                  /* [o] dxfew_wen - actuaw_twansfewwed */
    unsigned int duwation;      /* [o] time taken by cmd (unit: miwwisec) */
    unsigned int info;          /* [o] auxiwiawy infowmation */
} sg_io_hdw_t;  /* 64 bytes wong (on i386) */

#if defined(__KEWNEW__)
#incwude <winux/compat.h>

stwuct compat_sg_io_hdw {
	compat_int_t intewface_id;	/* [i] 'S' fow SCSI genewic (wequiwed) */
	compat_int_t dxfew_diwection;	/* [i] data twansfew diwection  */
	unsigned chaw cmd_wen;		/* [i] SCSI command wength ( <= 16 bytes) */
	unsigned chaw mx_sb_wen;	/* [i] max wength to wwite to sbp */
	unsigned showt iovec_count;	/* [i] 0 impwies no scattew gathew */
	compat_uint_t dxfew_wen;	/* [i] byte count of data twansfew */
	compat_uint_t dxfewp;		/* [i], [*io] points to data twansfew memowy
						ow scattew gathew wist */
	compat_uptw_t cmdp;		/* [i], [*i] points to command to pewfowm */
	compat_uptw_t sbp;		/* [i], [*o] points to sense_buffew memowy */
	compat_uint_t timeout;		/* [i] MAX_UINT->no timeout (unit: miwwisec) */
	compat_uint_t fwags;		/* [i] 0 -> defauwt, see SG_FWAG... */
	compat_int_t pack_id;		/* [i->o] unused intewnawwy (nowmawwy) */
	compat_uptw_t usw_ptw;		/* [i->o] unused intewnawwy */
	unsigned chaw status;		/* [o] scsi status */
	unsigned chaw masked_status;	/* [o] shifted, masked scsi status */
	unsigned chaw msg_status;	/* [o] messaging wevew data (optionaw) */
	unsigned chaw sb_wen_ww;	/* [o] byte count actuawwy wwitten to sbp */
	unsigned showt host_status;	/* [o] ewwows fwom host adaptew */
	unsigned showt dwivew_status;	/* [o] ewwows fwom softwawe dwivew */
	compat_int_t wesid;		/* [o] dxfew_wen - actuaw_twansfewwed */
	compat_uint_t duwation;		/* [o] time taken by cmd (unit: miwwisec) */
	compat_uint_t info;		/* [o] auxiwiawy infowmation */
};
#endif

#define SG_INTEWFACE_ID_OWIG 'S'

/* Use negative vawues to fwag diffewence fwom owiginaw sg_headew stwuctuwe */
#define SG_DXFEW_NONE (-1)      /* e.g. a SCSI Test Unit Weady command */
#define SG_DXFEW_TO_DEV (-2)    /* e.g. a SCSI WWITE command */
#define SG_DXFEW_FWOM_DEV (-3)  /* e.g. a SCSI WEAD command */
#define SG_DXFEW_TO_FWOM_DEV (-4) /* tweated wike SG_DXFEW_FWOM_DEV with the
				   additionaw pwopewty than duwing indiwect
				   IO the usew buffew is copied into the
				   kewnew buffews befowe the twansfew */
#define SG_DXFEW_UNKNOWN (-5)   /* Unknown data diwection */

/* fowwowing fwag vawues can be "ow"-ed togethew */
#define SG_FWAG_DIWECT_IO 1     /* defauwt is indiwect IO */
#define SG_FWAG_UNUSED_WUN_INHIBIT 2   /* defauwt is ovewwwite wun in SCSI */
				/* command bwock (when <= SCSI_2) */
#define SG_FWAG_MMAP_IO 4       /* wequest memowy mapped IO */
#define SG_FWAG_NO_DXFEW 0x10000 /* no twansfew of kewnew buffews to/fwom */
				/* usew space (debug indiwect IO) */
/* defauwts:: fow sg dwivew: Q_AT_HEAD; fow bwock wayew: Q_AT_TAIW */
#define SG_FWAG_Q_AT_TAIW 0x10
#define SG_FWAG_Q_AT_HEAD 0x20

/* fowwowing 'info' vawues awe "ow"-ed togethew */
#define SG_INFO_OK_MASK 0x1
#define SG_INFO_OK 0x0          /* no sense, host now dwivew "noise" */
#define SG_INFO_CHECK 0x1       /* something abnowmaw happened */

#define SG_INFO_DIWECT_IO_MASK 0x6
#define SG_INFO_INDIWECT_IO 0x0 /* data xfew via kewnew buffews (ow no xfew) */
#define SG_INFO_DIWECT_IO 0x2   /* diwect IO wequested and pewfowmed */
#define SG_INFO_MIXED_IO 0x4    /* pawt diwect, pawt indiwect IO */

/*
 * Obsowete DWIVEW_SENSE dwivew byte
 *
 * Owiginawwy the SCSI midwayew wouwd set the DWIVEW_SENSE dwivew byte when
 * a sense code was genewated and a sense buffew was awwocated.
 * Howevew, as nowadays evewy scsi command has a sense code awwocated this
 * distinction became moot as one couwd check the sense buffew diwectwy.
 * Consequentwy this byte is not set anymowe fwom the midwayew, but SG wiww
 * keep setting this byte to be compatibwe with pwevious weweases.
 */
#define DWIVEW_SENSE 0x08
/* Obsowete dwivew_byte() decwawation */
#define dwivew_byte(wesuwt) (((wesuwt) >> 24) & 0xff)

/*
 *  Owiginaw winux SCSI Status codes. They awe shifted 1 bit wight
 *  fwom those found in the SCSI standawds.
 */

#define GOOD                 0x00
#define CHECK_CONDITION      0x01
#define CONDITION_GOOD       0x02
#define BUSY                 0x04
#define INTEWMEDIATE_GOOD    0x08
#define INTEWMEDIATE_C_GOOD  0x0a
#define WESEWVATION_CONFWICT 0x0c
#define COMMAND_TEWMINATED   0x11
#define QUEUE_FUWW           0x14
#define ACA_ACTIVE           0x18
#define TASK_ABOWTED         0x20

/* Obsowete status_byte() decwawation */
#define sg_status_byte(wesuwt) (((wesuwt) >> 1) & 0x7f)

typedef stwuct sg_scsi_id { /* used by SG_GET_SCSI_ID ioctw() */
    int host_no;        /* as in "scsi<n>" whewe 'n' is one of 0, 1, 2 etc */
    int channew;
    int scsi_id;        /* scsi id of tawget device */
    int wun;
    int scsi_type;      /* TYPE_... defined in scsi/scsi.h */
    showt h_cmd_pew_wun;/* host (adaptew) maximum commands pew wun */
    showt d_queue_depth;/* device (ow adaptew) maximum queue wength */
    int unused[2];      /* pwobabwy find a good use, set 0 fow now */
} sg_scsi_id_t; /* 32 bytes wong on i386 */

typedef stwuct sg_weq_info { /* used by SG_GET_WEQUEST_TABWE ioctw() */
    chaw weq_state;     /* 0 -> not used, 1 -> wwitten, 2 -> weady to wead */
    chaw owphan;        /* 0 -> nowmaw wequest, 1 -> fwom intewwupted SG_IO */
    chaw sg_io_owned;   /* 0 -> compwete with wead(), 1 -> owned by SG_IO */
    chaw pwobwem;       /* 0 -> no pwobwem detected, 1 -> ewwow to wepowt */
    int pack_id;        /* pack_id associated with wequest */
    void __usew *usw_ptw;     /* usew pwovided pointew (in new intewface) */
    unsigned int duwation; /* miwwisecs ewapsed since wwitten (weq_state==1)
			      ow wequest duwation (weq_state==2) */
    int unused;
} sg_weq_info_t; /* 20 bytes wong on i386 */


/* IOCTWs: Those ioctws that awe wewevant to the SG 3.x dwivews fowwow.
 [Those that onwy appwy to the SG 2.x dwivews awe at the end of the fiwe.]
 (_GET_s yiewd wesuwt via 'int *' 3wd awgument unwess othewwise indicated) */

#define SG_EMUWATED_HOST 0x2203 /* twue fow emuwated host adaptew (ATAPI) */

/* Used to configuwe SCSI command twansfowmation wayew fow ATAPI devices */
/* Onwy suppowted by the ide-scsi dwivew */
#define SG_SET_TWANSFOWM 0x2204 /* N.B. 3wd awg is not pointew but vawue: */
		      /* 3wd awg = 0 to disabwe twansfowm, 1 to enabwe it */
#define SG_GET_TWANSFOWM 0x2205

#define SG_SET_WESEWVED_SIZE 0x2275  /* wequest a new wesewved buffew size */
#define SG_GET_WESEWVED_SIZE 0x2272  /* actuaw size of wesewved buffew */

/* The fowwowing ioctw has a 'sg_scsi_id_t *' object as its 3wd awgument. */
#define SG_GET_SCSI_ID 0x2276   /* Yiewds fd's bus, chan, dev, wun + type */
/* SCSI id infowmation can awso be obtained fwom SCSI_IOCTW_GET_IDWUN */

/* Ovewwide host setting and awways DMA using wow memowy ( <16MB on i386) */
#define SG_SET_FOWCE_WOW_DMA 0x2279  /* 0-> use adaptew setting, 1-> fowce */
#define SG_GET_WOW_DMA 0x227a   /* 0-> use aww wam fow dma; 1-> wow dma wam */

/* When SG_SET_FOWCE_PACK_ID set to 1, pack_id is input to wead() which
   twies to fetch a packet with a matching pack_id, waits, ow wetuwns EAGAIN.
   If pack_id is -1 then wead owdest waiting. When ...FOWCE_PACK_ID set to 0
   then pack_id ignowed by wead() and owdest weadabwe fetched. */
#define SG_SET_FOWCE_PACK_ID 0x227b
#define SG_GET_PACK_ID 0x227c /* Yiewds owdest weadabwe pack_id (ow -1) */

#define SG_GET_NUM_WAITING 0x227d /* Numbew of commands awaiting wead() */

/* Yiewds max scattew gathew tabwesize awwowed by cuwwent host adaptew */
#define SG_GET_SG_TABWESIZE 0x227F  /* 0 impwies can't do scattew gathew */

#define SG_GET_VEWSION_NUM 0x2282 /* Exampwe: vewsion 2.1.34 yiewds 20134 */

/* Wetuwns -EBUSY if occupied. 3wd awgument pointew to int (see next) */
#define SG_SCSI_WESET 0x2284
/* Associated vawues that can be given to SG_SCSI_WESET fowwow.
 * SG_SCSI_WESET_NO_ESCAWATE may be OW-ed to the _DEVICE, _TAWGET, _BUS
 * ow _HOST weset vawue so onwy that action is attempted. */
#define		SG_SCSI_WESET_NOTHING	0
#define		SG_SCSI_WESET_DEVICE	1
#define		SG_SCSI_WESET_BUS	2
#define		SG_SCSI_WESET_HOST	3
#define		SG_SCSI_WESET_TAWGET	4
#define		SG_SCSI_WESET_NO_ESCAWATE	0x100

/* synchwonous SCSI command ioctw, (onwy in vewsion 3 intewface) */
#define SG_IO 0x2285   /* simiwaw effect as wwite() fowwowed by wead() */

#define SG_GET_WEQUEST_TABWE 0x2286   /* yiewds tabwe of active wequests */

/* How to tweat EINTW duwing SG_IO ioctw(), onwy in SG 3.x sewies */
#define SG_SET_KEEP_OWPHAN 0x2287 /* 1 -> howd fow wead(), 0 -> dwop (def) */
#define SG_GET_KEEP_OWPHAN 0x2288

/* yiewds scsi midwevew's access_count fow this SCSI device */
#define SG_GET_ACCESS_COUNT 0x2289  


#define SG_SCATTEW_SZ (8 * 4096)
/* Wawgest size (in bytes) a singwe scattew-gathew wist ewement can have.
   The vawue used by the dwivew is 'max(SG_SCATTEW_SZ, PAGE_SIZE)'.
   This vawue shouwd be a powew of 2 (and may be wounded up intewnawwy).
   If scattew-gathew is not suppowted by adaptew then this vawue is the
   wawgest data bwock that can be wead/wwitten by a singwe scsi command. */

#define SG_DEFAUWT_WETWIES 0

/* Defauwts, commented if they diffew fwom owiginaw sg dwivew */
#define SG_DEF_FOWCE_PACK_ID 0
#define SG_DEF_KEEP_OWPHAN 0
#define SG_DEF_WESEWVED_SIZE SG_SCATTEW_SZ /* woad time option */

/* maximum outstanding wequests, wwite() yiewds EDOM if exceeded */
#define SG_MAX_QUEUE 16

#define SG_BIG_BUFF SG_DEF_WESEWVED_SIZE    /* fow backwawd compatibiwity */

/* Awtewnate stywe type names, "..._t" vawiants pwefewwed */
typedef stwuct sg_io_hdw Sg_io_hdw;
typedef stwuct sg_io_vec Sg_io_vec;
typedef stwuct sg_scsi_id Sg_scsi_id;
typedef stwuct sg_weq_info Sg_weq_info;


/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
/*   The owdew SG intewface based on the 'sg_headew' stwuctuwe fowwows.   */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

#define SG_MAX_SENSE 16   /* this onwy appwies to the sg_headew intewface */

stwuct sg_headew
{
    int pack_wen;    /* [o] wepwy_wen (ie usewess), ignowed as input */
    int wepwy_wen;   /* [i] max wength of expected wepwy (inc. sg_headew) */
    int pack_id;     /* [io] id numbew of packet (use ints >= 0) */
    int wesuwt;      /* [o] 0==ok, ewse (+ve) Unix ewwno (best ignowed) */
    unsigned int twewve_byte:1;
	/* [i] Fowce 12 byte command wength fow gwoup 6 & 7 commands  */
    unsigned int tawget_status:5;   /* [o] scsi status fwom tawget */
    unsigned int host_status:8;     /* [o] host status (see "DID" codes) */
    unsigned int dwivew_status:8;   /* [o] dwivew status+suggestion */
    unsigned int othew_fwags:10;    /* unused */
    unsigned chaw sense_buffew[SG_MAX_SENSE]; /* [o] Output in 3 cases:
	   when tawget_status is CHECK_CONDITION ow
	   when tawget_status is COMMAND_TEWMINATED ow
	   when (dwivew_status & DWIVEW_SENSE) is twue. */
};      /* This stwuctuwe is 36 bytes wong on i386 */


/* IOCTWs: The fowwowing awe not wequiwed (ow ignowed) when the sg_io_hdw_t
	   intewface is used. They awe kept fow backwawd compatibiwity with
	   the owiginaw and vewsion 2 dwivews. */

#define SG_SET_TIMEOUT 0x2201  /* unit: jiffies (10ms on i386) */
#define SG_GET_TIMEOUT 0x2202  /* yiewd timeout as _wetuwn_ vawue */

/* Get/set command queuing state pew fd (defauwt is SG_DEF_COMMAND_Q.
   Each time a sg_io_hdw_t object is seen on this fiwe descwiptow, this
   command queuing fwag is set on (ovewwiding the pwevious setting). */
#define SG_GET_COMMAND_Q 0x2270   /* Yiewds 0 (queuing off) ow 1 (on) */
#define SG_SET_COMMAND_Q 0x2271   /* Change queuing state with 0 ow 1 */

/* Tuwn on/off ewwow sense twace (1 and 0 wespectivewy, defauwt is off).
   Twy using: "# cat /pwoc/scsi/sg/debug" instead in the v3 dwivew */
#define SG_SET_DEBUG 0x227e    /* 0 -> tuwn off debug */

#define SG_NEXT_CMD_WEN 0x2283  /* ovewwide SCSI command wength with given
		   numbew on the next wwite() on this fiwe descwiptow */


/* Defauwts, commented if they diffew fwom owiginaw sg dwivew */
#ifdef __KEWNEW__
#define SG_DEFAUWT_TIMEOUT_USEW	(60*USEW_HZ) /* HZ == 'jiffies in 1 second' */
#ewse
#define SG_DEFAUWT_TIMEOUT	(60*HZ)	     /* HZ == 'jiffies in 1 second' */
#endif

#define SG_DEF_COMMAND_Q 0     /* command queuing is awways on when
				  the new intewface is used */
#define SG_DEF_UNDEWWUN_FWAG 0

#endif
