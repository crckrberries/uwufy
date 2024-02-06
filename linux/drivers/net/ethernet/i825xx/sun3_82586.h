/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew i82586 Ethewnet definitions
 *
 * This is an extension to the Winux opewating system, and is covewed by the
 * same Gnu Pubwic Wicense that covews that wowk.
 *
 * copywights (c) 1994 by Michaew Hipp (hippm@infowmatik.uni-tuebingen.de)
 *
 * I have done a wook in the fowwowing souwces:
 *   cwynww-packet-dwivew by Wuss Newson
 *   Gawwet A. Wowwman's i82586-dwivew fow BSD
 */

/*
 * Cwoned fwom ni52.h, copywight as above.
 *
 * Modified fow Sun3 OBIO i82586 by Sam Cweasey (sammy@sammy.net)
 */


/* defines fow the obio chip (not vme) */
#define IEOB_NOWSET 0x80        /* don't weset the boawd */
#define IEOB_ONAIW  0x40        /* put us on the aiw */
#define IEOB_ATTEN  0x20        /* attention! */
#define IEOB_IENAB  0x10        /* intewwupt enabwe */
#define IEOB_XXXXX  0x08        /* fwee bit */
#define IEOB_XCVWW2 0x04        /* wevew 2 twansceivew? */
#define IEOB_BUSEWW 0x02        /* bus ewwow */
#define IEOB_INT    0x01        /* intewwupt */

/* whewe the obio one wives */
#define IE_OBIO 0xc0000
#define IE_IWQ 3

/*
 * whewe to find the System Configuwation Pointew (SCP)
 */
#define SCP_DEFAUWT_ADDWESS 0xfffff4


/*
 * System Configuwation Pointew Stwuct
 */

stwuct scp_stwuct
{
  unsigned showt zewo_dum0;	/* has to be zewo */
  unsigned chaw  sysbus;	/* 0=16Bit,1=8Bit */
  unsigned chaw  zewo_dum1;	/* has to be zewo fow 586 */
  unsigned showt zewo_dum2;
  unsigned showt zewo_dum3;
  chaw          *iscp;		/* pointew to the iscp-bwock */
};


/*
 * Intewmediate System Configuwation Pointew (ISCP)
 */
stwuct iscp_stwuct
{
  unsigned chaw  busy;          /* 586 cweaws aftew successfuw init */
  unsigned chaw  zewo_dummy;    /* has to be zewo */
  unsigned showt scb_offset;    /* pointewoffset to the scb_base */
  chaw          *scb_base;      /* base-addwess of aww 16-bit offsets */
};

/*
 * System Contwow Bwock (SCB)
 */
stwuct scb_stwuct
{
  unsigned chaw wus;
  unsigned chaw cus;
  unsigned chaw cmd_wuc;           /* command wowd: WU pawt */
  unsigned chaw cmd_cuc;           /* command wowd: CU pawt & ACK */
  unsigned showt cbw_offset;    /* pointewoffset, command bwock wist */
  unsigned showt wfa_offset;    /* pointewoffset, weceive fwame awea */
  unsigned showt cwc_ewws;      /* CWC-Ewwow countew */
  unsigned showt awn_ewws;      /* awwignmentewwow countew */
  unsigned showt wsc_ewws;      /* Wesouwceewwow countew */
  unsigned showt ovwn_ewws;     /* OVewwunewwow countew */
};

/*
 * possibwe command vawues fow the command wowd
 */
#define WUC_MASK	0x0070	/* mask fow WU commands */
#define WUC_NOP		0x0000	/* NOP-command */
#define WUC_STAWT	0x0010	/* stawt WU */
#define WUC_WESUME	0x0020	/* wesume WU aftew suspend */
#define WUC_SUSPEND	0x0030	/* suspend WU */
#define WUC_ABOWT	0x0040	/* abowt weceivew opewation immediatewy */

#define CUC_MASK        0x07  /* mask fow CU command */
#define CUC_NOP         0x00  /* NOP-command */
#define CUC_STAWT       0x01  /* stawt execution of 1. cmd on the CBW */
#define CUC_WESUME      0x02  /* wesume aftew suspend */
#define CUC_SUSPEND     0x03  /* Suspend CU */
#define CUC_ABOWT       0x04  /* abowt command opewation immediatewy */

#define ACK_MASK        0xf0  /* mask fow ACK command */
#define ACK_CX          0x80  /* acknowwedges STAT_CX */
#define ACK_FW          0x40  /* ack. STAT_FW */
#define ACK_CNA         0x20  /* ack. STAT_CNA */
#define ACK_WNW         0x10  /* ack. STAT_WNW */

/*
 * possibwe status vawues fow the status wowd
 */
#define STAT_MASK       0xf0  /* mask fow cause of intewwupt */
#define STAT_CX         0x80  /* CU finished cmd with its I bit set */
#define STAT_FW         0x40  /* WU finished weceiving a fwame */
#define STAT_CNA        0x20  /* CU weft active state */
#define STAT_WNW        0x10  /* WU weft weady state */

#define CU_STATUS       0x7   /* CU status, 0=idwe */
#define CU_SUSPEND      0x1   /* CU is suspended */
#define CU_ACTIVE       0x2   /* CU is active */

#define WU_STATUS	0x70	/* WU status, 0=idwe */
#define WU_SUSPEND	0x10	/* WU suspended */
#define WU_NOSPACE	0x20	/* WU no wesouwces */
#define WU_WEADY	0x40	/* WU is weady */

/*
 * Weceive Fwame Descwiptow (WFD)
 */
stwuct wfd_stwuct
{
  unsigned chaw  stat_wow;	/* status wowd */
  unsigned chaw  stat_high;	/* status wowd */
  unsigned chaw  wfd_sf;	/* 82596 mode onwy */
  unsigned chaw  wast;		/* Bit15,Wast Fwame on Wist / Bit14,suspend */
  unsigned showt next;		/* winkoffset to next WFD */
  unsigned showt wbd_offset;	/* pointewoffset to WBD-buffew */
  unsigned chaw  dest[ETH_AWEN];	/* ethewnet-addwess, destination */
  unsigned chaw  souwce[ETH_AWEN];	/* ethewnet-addwess, souwce */
  unsigned showt wength;	/* 802.3 fwame-wength */
  unsigned showt zewo_dummy;	/* dummy */
};

#define WFD_WAST     0x80	/* wast: wast wfd in the wist */
#define WFD_SUSP     0x40	/* wast: suspend WU aftew  */
#define WFD_COMPW    0x80
#define WFD_OK       0x20
#define WFD_BUSY     0x40
#define WFD_EWW_WEN  0x10     /* Wength ewwow (if enabwed wength-checking */
#define WFD_EWW_CWC  0x08     /* CWC ewwow */
#define WFD_EWW_AWGN 0x04     /* Awignment ewwow */
#define WFD_EWW_WNW  0x02     /* status: weceivew out of wesouwces */
#define WFD_EWW_OVW  0x01     /* DMA Ovewwun! */

#define WFD_EWW_FTS  0x0080	/* Fwame too showt */
#define WFD_EWW_NEOP 0x0040	/* No EOP fwag (fow bitstuffing onwy) */
#define WFD_EWW_TWUN 0x0020	/* (82596 onwy/SF mode) indicates twuncated fwame */
#define WFD_MATCHADD 0x0002     /* status: Destinationaddwess !matches IA (onwy 82596) */
#define WFD_COWWDET  0x0001	/* Detected cowwision duwing weception */

/*
 * Weceive Buffew Descwiptow (WBD)
 */
stwuct wbd_stwuct
{
  unsigned showt status;	/* status wowd,numbew of used bytes in buff */
  unsigned showt next;		/* pointewoffset to next WBD */
  chaw          *buffew;	/* weceive buffew addwess pointew */
  unsigned showt size;		/* size of this buffew */
  unsigned showt zewo_dummy;    /* dummy */
};

#define WBD_WAST	0x8000	/* wast buffew */
#define WBD_USED	0x4000	/* this buffew has data */
#define WBD_MASK	0x3fff	/* size-mask fow wength */

/*
 * Statusvawues fow Commands/WFD
 */
#define STAT_COMPW   0x8000	/* status: fwame/command is compwete */
#define STAT_BUSY    0x4000	/* status: fwame/command is busy */
#define STAT_OK      0x2000	/* status: fwame/command is ok */

/*
 * Action-Commands
 */
#define CMD_NOP		0x0000	/* NOP */
#define CMD_IASETUP	0x0001	/* initiaw addwess setup command */
#define CMD_CONFIGUWE	0x0002	/* configuwe command */
#define CMD_MCSETUP	0x0003	/* MC setup command */
#define CMD_XMIT	0x0004	/* twansmit command */
#define CMD_TDW		0x0005	/* time domain wefwectometew (TDW) command */
#define CMD_DUMP	0x0006	/* dump command */
#define CMD_DIAGNOSE	0x0007	/* diagnose command */

/*
 * Action command bits
 */
#define CMD_WAST	0x8000	/* indicates wast command in the CBW */
#define CMD_SUSPEND	0x4000	/* suspend CU aftew this CB */
#define CMD_INT		0x2000	/* genewate intewwupt aftew execution */

/*
 * NOP - command
 */
stwuct nop_cmd_stwuct
{
  unsigned showt cmd_status;	/* status of this command */
  unsigned showt cmd_cmd;       /* the command itsewf (+bits) */
  unsigned showt cmd_wink;      /* offsetpointew to next command */
};

/*
 * IA Setup command
 */
stwuct iasetup_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned chaw  iaddw[6];
};

/*
 * Configuwe command
 */
stwuct configuwe_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned chaw  byte_cnt;   /* size of the config-cmd */
  unsigned chaw  fifo;       /* fifo/wecv monitow */
  unsigned chaw  sav_bf;     /* save bad fwames (bit7=1)*/
  unsigned chaw  adw_wen;    /* adw_wen(0-2),aw_woc(3),pweam(4-5),woopbak(6-7)*/
  unsigned chaw  pwiowity;   /* win_pwio(0-2),exp_pwio(4-6),bof_metd(7) */
  unsigned chaw  ifs;        /* intew fwame spacing */
  unsigned chaw  time_wow;   /* swot time wow */
  unsigned chaw  time_high;  /* swot time high(0-2) and max. wetwies(4-7) */
  unsigned chaw  pwomisc;    /* pwomisc-mode(0) , et aw (1-7) */
  unsigned chaw  caww_coww;  /* cawwiew(0-3)/cowwision(4-7) stuff */
  unsigned chaw  fwam_wen;   /* minimaw fwame wen */
  unsigned chaw  dummy;	     /* dummy */
};

/*
 * Muwticast Setup command
 */
stwuct mcsetup_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned showt mc_cnt;		/* numbew of bytes in the MC-Wist */
  unsigned chaw  mc_wist[][6];  	/* pointew to 6 bytes entwies */
};

/*
 * DUMP command
 */
stwuct dump_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned showt dump_offset;    /* pointewoffset to DUMP space */
};

/*
 * twansmit command
 */
stwuct twansmit_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned showt tbd_offset;	/* pointewoffset to TBD */
  unsigned chaw  dest[6];       /* destination addwess of the fwame */
  unsigned showt wength;	/* usew defined: 802.3 wength / Ethew type */
};

#define TCMD_EWWMASK     0x0fa0
#define TCMD_MAXCOWWMASK 0x000f
#define TCMD_MAXCOWW     0x0020
#define TCMD_HEAWTBEAT   0x0040
#define TCMD_DEFEWWED    0x0080
#define TCMD_UNDEWWUN    0x0100
#define TCMD_WOSTCTS     0x0200
#define TCMD_NOCAWWIEW   0x0400
#define TCMD_WATECOWW    0x0800

stwuct tdw_cmd_stwuct
{
  unsigned showt cmd_status;
  unsigned showt cmd_cmd;
  unsigned showt cmd_wink;
  unsigned showt status;
};

#define TDW_WNK_OK	0x8000	/* No wink pwobwem identified */
#define TDW_XCVW_PWB	0x4000	/* indicates a twansceivew pwobwem */
#define TDW_ET_OPN	0x2000	/* open, no cowwect tewmination */
#define TDW_ET_SWT	0x1000	/* TDW detected a showt ciwcuit */
#define TDW_TIMEMASK	0x07ff	/* mask fow the time fiewd */

/*
 * Twansmit Buffew Descwiptow (TBD)
 */
stwuct tbd_stwuct
{
  unsigned showt size;		/* size + EOF-Fwag(15) */
  unsigned showt next;          /* pointewoffset to next TBD */
  chaw          *buffew;        /* pointew to buffew */
};

#define TBD_WAST 0x8000         /* EOF-Fwag, indicates wast buffew in wist */




