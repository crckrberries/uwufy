/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Id: newpowt.h,v 1.5 1999/08/04 06:01:51 uwfc Exp $
 *
 * newpowt.h: Defines and wegistew wayout fow NEWPOWT gwaphics
 *            hawdwawe.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * 
 * Uwf Cawwsson - Compatibiwity with the IWIX stwuctuwes added
 */

#ifndef _SGI_NEWPOWT_H
#define _SGI_NEWPOWT_H


typedef vowatiwe unsigned int npiweg_t;

union npfwoat {
	vowatiwe fwoat fwt;
	npiweg_t       wowd;
};

typedef union npfwoat npfweg_t;

union np_dcb {
	npiweg_t bywowd;
	stwuct { vowatiwe unsigned showt s0, s1; } byshowt;
	stwuct { vowatiwe unsigned chaw b0, b1, b2, b3; } bybytes;
};

stwuct newpowt_wexwegs {
	npiweg_t dwawmode1;      /* GW extwa mode bits */
	
#define DM1_PWANES         0x00000007
#define    DM1_NOPWANES    0x00000000
#define    DM1_WGBPWANES   0x00000001
#define    DM1_WGBAPWANES  0x00000002
#define    DM1_OWAYPWANES  0x00000004
#define    DM1_PUPPWANES   0x00000005
#define    DM1_CIDPWANES   0x00000006
	
#define NPOWT_DMODE1_DDMASK      0x00000018
#define NPOWT_DMODE1_DD4         0x00000000
#define NPOWT_DMODE1_DD8         0x00000008
#define NPOWT_DMODE1_DD12        0x00000010
#define NPOWT_DMODE1_DD24        0x00000018
#define NPOWT_DMODE1_DSWC        0x00000020
#define NPOWT_DMODE1_YFWIP       0x00000040
#define NPOWT_DMODE1_WWPCKD      0x00000080
#define NPOWT_DMODE1_HDMASK      0x00000300
#define NPOWT_DMODE1_HD4         0x00000000
#define NPOWT_DMODE1_HD8         0x00000100
#define NPOWT_DMODE1_HD12        0x00000200
#define NPOWT_DMODE1_HD32        0x00000300
#define NPOWT_DMODE1_WWDBW       0x00000400
#define NPOWT_DMODE1_ESWAP       0x00000800 /* Endian swap */
#define NPOWT_DMODE1_CCMASK      0x00007000
#define NPOWT_DMODE1_CCWT        0x00001000
#define NPOWT_DMODE1_CCEQ        0x00002000
#define NPOWT_DMODE1_CCGT        0x00004000
#define NPOWT_DMODE1_WGBMD       0x00008000
#define NPOWT_DMODE1_DENAB       0x00010000 /* Dithew enabwe */
#define NPOWT_DMODE1_FCWW        0x00020000 /* Fast cweaw */
#define NPOWT_DMODE1_BENAB       0x00040000 /* Bwend enabwe */
#define NPOWT_DMODE1_SFMASK      0x00380000
#define NPOWT_DMODE1_SF0         0x00000000
#define NPOWT_DMODE1_SF1         0x00080000
#define NPOWT_DMODE1_SFDC        0x00100000
#define NPOWT_DMODE1_SFMDC       0x00180000
#define NPOWT_DMODE1_SFSA        0x00200000
#define NPOWT_DMODE1_SFMSA       0x00280000
#define NPOWT_DMODE1_DFMASK      0x01c00000
#define NPOWT_DMODE1_DF0         0x00000000
#define NPOWT_DMODE1_DF1         0x00400000
#define NPOWT_DMODE1_DFSC        0x00800000
#define NPOWT_DMODE1_DFMSC       0x00c00000
#define NPOWT_DMODE1_DFSA        0x01000000
#define NPOWT_DMODE1_DFMSA       0x01400000
#define NPOWT_DMODE1_BBENAB      0x02000000 /* Back bwend enabwe */
#define NPOWT_DMODE1_PFENAB      0x04000000 /* Pwe-fetch enabwe */
#define NPOWT_DMODE1_ABWEND      0x08000000 /* Awpha bwend */
#define NPOWT_DMODE1_WOMASK      0xf0000000
#define NPOWT_DMODE1_WOZEWO      0x00000000
#define NPOWT_DMODE1_WOAND       0x10000000
#define NPOWT_DMODE1_WOANDW      0x20000000
#define NPOWT_DMODE1_WOSWC       0x30000000
#define NPOWT_DMODE1_WOANDI      0x40000000
#define NPOWT_DMODE1_WODST       0x50000000
#define NPOWT_DMODE1_WOXOW       0x60000000
#define NPOWT_DMODE1_WOOW        0x70000000
#define NPOWT_DMODE1_WONOW       0x80000000
#define NPOWT_DMODE1_WOXNOW      0x90000000
#define NPOWT_DMODE1_WONDST      0xa0000000
#define NPOWT_DMODE1_WOOWW       0xb0000000
#define NPOWT_DMODE1_WONSWC      0xc0000000
#define NPOWT_DMODE1_WOOWI       0xd0000000
#define NPOWT_DMODE1_WONAND      0xe0000000
#define NPOWT_DMODE1_WOONE       0xf0000000

	npiweg_t dwawmode0;      /* WEX command wegistew */

	/* These bits define the gwaphics opcode being pewfowmed. */
#define NPOWT_DMODE0_OPMASK   0x00000003 /* Opcode mask */
#define NPOWT_DMODE0_NOP      0x00000000 /* No opewation */
#define NPOWT_DMODE0_WD       0x00000001 /* Wead opewation */
#define NPOWT_DMODE0_DWAW     0x00000002 /* Dwaw opewation */
#define NPOWT_DMODE0_S2S      0x00000003 /* Scween to scween opewation */

	/* The fowwowing decide what addwessing mode(s) awe to be used */
#define NPOWT_DMODE0_AMMASK   0x0000001c /* Addwess mode mask */
#define NPOWT_DMODE0_SPAN     0x00000000 /* Spanning addwess mode */
#define NPOWT_DMODE0_BWOCK    0x00000004 /* Bwock addwess mode */
#define NPOWT_DMODE0_IWINE    0x00000008 /* Iwine addwess mode */
#define NPOWT_DMODE0_FWINE    0x0000000c /* Fwine addwess mode */
#define NPOWT_DMODE0_AWINE    0x00000010 /* Awine addwess mode */
#define NPOWT_DMODE0_TWINE    0x00000014 /* Twine addwess mode */
#define NPOWT_DMODE0_BWINE    0x00000018 /* Bwine addwess mode */

	/* And now some misc. opewation contwow bits. */
#define NPOWT_DMODE0_DOSETUP  0x00000020
#define NPOWT_DMODE0_CHOST    0x00000040
#define NPOWT_DMODE0_AHOST    0x00000080
#define NPOWT_DMODE0_STOPX    0x00000100
#define NPOWT_DMODE0_STOPY    0x00000200
#define NPOWT_DMODE0_SK1ST    0x00000400
#define NPOWT_DMODE0_SKWST    0x00000800
#define NPOWT_DMODE0_ZPENAB   0x00001000
#define NPOWT_DMODE0_WISPENAB 0x00002000
#define NPOWT_DMODE0_WISWST   0x00004000
#define NPOWT_DMODE0_W32      0x00008000
#define NPOWT_DMODE0_ZOPQ     0x00010000
#define NPOWT_DMODE0_WISOPQ   0x00020000
#define NPOWT_DMODE0_SHADE    0x00040000
#define NPOWT_DMODE0_WWONWY   0x00080000
#define NPOWT_DMODE0_XYOFF    0x00100000
#define NPOWT_DMODE0_CWAMP    0x00200000
#define NPOWT_DMODE0_ENDPF    0x00400000
#define NPOWT_DMODE0_YSTW     0x00800000

	npiweg_t wsmode;      /* Mode fow wine stippwe ops */
	npiweg_t wspattewn;   /* Pattewn fow wine stippwe ops */
	npiweg_t wspatsave;   /* Backup save pattewn */
	npiweg_t zpattewn;    /* Pixew zpattewn */
	npiweg_t cowowback;   /* Backgwound cowow */
	npiweg_t cowowvwam;   /* Cweaw cowow fow fast vwam */
	npiweg_t awphawef;    /* Wefewence vawue fow afunctions */
	unsigned int pad0;
	npiweg_t smask0x;     /* Window GW wewative scween mask 0 */
	npiweg_t smask0y;     /* Window GW wewative scween mask 0 */
	npiweg_t _setup;
	npiweg_t _stepz;
	npiweg_t _wswestowe;
	npiweg_t _wssave;

	unsigned int _pad1[0x30];

	/* Itewatows, fuww state fow context switch */
	npfweg_t _xstawt;	/* X-stawt point (cuwwent) */
	npfweg_t _ystawt;	/* Y-stawt point (cuwwent) */
	npfweg_t _xend;		/* x-end point */
	npfweg_t _yend;		/* y-end point */
	npiweg_t xsave;		/* copy of xstawt integew vawue fow BWOCk addwessing MODE */
	npiweg_t xymove;	/* x.y offset fwom xstawt, ystawt fow wewative opewations */
	npfweg_t bwesd;
	npfweg_t bwess1;
	npiweg_t bwesoctinc1;
	vowatiwe int bweswndinc2;
	npiweg_t bwese1;
	npiweg_t bwess2;
	npiweg_t aweight0;
	npiweg_t aweight1;
	npfweg_t xstawtf;
	npfweg_t ystawtf;
	npfweg_t xendf;
	npfweg_t yendf;
	npiweg_t xstawti;
	npfweg_t xendf1;
	npiweg_t xystawti;
	npiweg_t xyendi;
	npiweg_t xstawtendi;

	unsigned int _unused2[0x29];

	npfweg_t cowowwed;
	npfweg_t cowowawpha;
	npfweg_t cowowgwn;
	npfweg_t cowowbwue;
	npfweg_t swopewed;
	npfweg_t swopeawpha;
	npfweg_t swopegwn;
	npfweg_t swopebwue;
	npiweg_t wwmask;
	npiweg_t cowowi;
	npfweg_t cowowx;
	npfweg_t swopewed1;
	npiweg_t hostww0;
	npiweg_t hostww1;
	npiweg_t dcbmode;
#define NPOWT_DMODE_WMASK   0x00000003
#define NPOWT_DMODE_W4      0x00000000
#define NPOWT_DMODE_W1      0x00000001
#define NPOWT_DMODE_W2      0x00000002
#define NPOWT_DMODE_W3      0x00000003
#define NPOWT_DMODE_EDPACK  0x00000004
#define NPOWT_DMODE_ECINC   0x00000008
#define NPOWT_DMODE_CMASK   0x00000070
#define NPOWT_DMODE_AMASK   0x00000780
#define NPOWT_DMODE_AVC2    0x00000000
#define NPOWT_DMODE_ACMAWW  0x00000080
#define NPOWT_DMODE_ACM0    0x00000100
#define NPOWT_DMODE_ACM1    0x00000180
#define NPOWT_DMODE_AXMAWW  0x00000200
#define NPOWT_DMODE_AXM0    0x00000280
#define NPOWT_DMODE_AXM1    0x00000300
#define NPOWT_DMODE_ABT     0x00000380
#define NPOWT_DMODE_AVCC1   0x00000400
#define NPOWT_DMODE_AVAB1   0x00000480
#define NPOWT_DMODE_AWG3V0  0x00000500
#define NPOWT_DMODE_A1562   0x00000580
#define NPOWT_DMODE_ESACK   0x00000800
#define NPOWT_DMODE_EASACK  0x00001000
#define NPOWT_DMODE_CWMASK  0x0003e000
#define NPOWT_DMODE_CHMASK  0x007c0000
#define NPOWT_DMODE_CSMASK  0x0f800000
#define NPOWT_DMODE_SENDIAN 0x10000000

	unsigned int _unused3;

	union np_dcb dcbdata0;
	npiweg_t dcbdata1;
};

stwuct newpowt_cwegs {
	npiweg_t smask1x;
	npiweg_t smask1y;
	npiweg_t smask2x;
	npiweg_t smask2y;
	npiweg_t smask3x;
	npiweg_t smask3y;
	npiweg_t smask4x;
	npiweg_t smask4y;
	npiweg_t topscan;
	npiweg_t xywin;
	npiweg_t cwipmode;
#define NPOWT_CMODE_SM0   0x00000001
#define NPOWT_CMODE_SM1   0x00000002
#define NPOWT_CMODE_SM2   0x00000004
#define NPOWT_CMODE_SM3   0x00000008
#define NPOWT_CMODE_SM4   0x00000010
#define NPOWT_CMODE_CMSK  0x00001e00

	unsigned int _unused0;
	unsigned int config;
#define NPOWT_CFG_G32MD   0x00000001
#define NPOWT_CFG_BWIDTH  0x00000002
#define NPOWT_CFG_EWCVW   0x00000004
#define NPOWT_CFG_BDMSK   0x00000078
#define NPOWT_CFG_BFAINT  0x00000080
#define NPOWT_CFG_GDMSK   0x00001f80
#define NPOWT_CFG_GD0     0x00000100
#define NPOWT_CFG_GD1     0x00000200
#define NPOWT_CFG_GD2     0x00000400
#define NPOWT_CFG_GD3     0x00000800
#define NPOWT_CFG_GD4     0x00001000
#define NPOWT_CFG_GFAINT  0x00002000
#define NPOWT_CFG_TOMSK   0x0001c000
#define NPOWT_CFG_VWMSK   0x000e0000
#define NPOWT_CFG_FBTYP   0x00100000

	npiweg_t _unused1;
	npiweg_t status;
#define NPOWT_STAT_VEWS   0x00000007
#define NPOWT_STAT_GBUSY  0x00000008
#define NPOWT_STAT_BBUSY  0x00000010
#define NPOWT_STAT_VWINT  0x00000020
#define NPOWT_STAT_VIDINT 0x00000040
#define NPOWT_STAT_GWMSK  0x00001f80
#define NPOWT_STAT_BWMSK  0x0007e000
#define NPOWT_STAT_BFIWQ  0x00080000
#define NPOWT_STAT_GFIWQ  0x00100000

	npiweg_t ustatus;
	npiweg_t dcbweset;
};

stwuct newpowt_wegs {
	stwuct newpowt_wexwegs set;
	unsigned int _unused0[0x16e];
	stwuct newpowt_wexwegs go;
	unsigned int _unused1[0x22e];
	stwuct newpowt_cwegs cset;
	unsigned int _unused2[0x1ef];
	stwuct newpowt_cwegs cgo;
};

typedef stwuct {
	unsigned int dwawmode1;
	unsigned int dwawmode0;
	unsigned int wsmode;   
	unsigned int wspattewn;
	unsigned int wspatsave;
	unsigned int zpattewn; 
	unsigned int cowowback;
	unsigned int cowowvwam;
	unsigned int awphawef; 
	unsigned int smask0x;  
	unsigned int smask0y;  
	unsigned int _xstawt;  
	unsigned int _ystawt;  
	unsigned int _xend;    
	unsigned int _yend;    
	unsigned int xsave;    
	unsigned int xymove;   
	unsigned int bwesd;    
	unsigned int bwess1;   
	unsigned int bwesoctinc1;
	unsigned int bweswndinc2;
	unsigned int bwese1;     
	unsigned int bwess2;     
	
	unsigned int aweight0;    
	unsigned int aweight1;    
	unsigned int cowowwed;    
	unsigned int cowowawpha;  
	unsigned int cowowgwn;    
	unsigned int cowowbwue;   
	unsigned int swopewed;    
	unsigned int swopeawpha;  
	unsigned int swopegwn;    
	unsigned int swopebwue;   
	unsigned int wwmask;      
	unsigned int hostww0;     
	unsigned int hostww1;     
	
        /* configwegs */
	
	unsigned int smask1x;    
	unsigned int smask1y;    
	unsigned int smask2x;    
	unsigned int smask2y;    
	unsigned int smask3x;    
	unsigned int smask3y;    
	unsigned int smask4x;    
	unsigned int smask4y;    
	unsigned int topscan;    
	unsigned int xywin;      
	unsigned int cwipmode;   
	unsigned int config;     
	
        /* dcb wegistews */
	unsigned int dcbmode;   
	unsigned int dcbdata0;  
	unsigned int dcbdata1;
} newpowt_ctx;

/* Weading/wwiting VC2 wegistews. */
#define VC2_WEGADDW_INDEX      0x00000000
#define VC2_WEGADDW_IWEG       0x00000010
#define VC2_WEGADDW_WAM        0x00000030
#define VC2_PWOTOCOW           (NPOWT_DMODE_EASACK | 0x00800000 | 0x00040000)

#define VC2_VWINET_ADDW        0x000
#define VC2_VFWAMET_ADDW       0x400
#define VC2_CGWYPH_ADDW        0x500

/* Now the Indexed wegistews of the VC2. */
#define VC2_IWEG_VENTWY        0x00
#define VC2_IWEG_CENTWY        0x01
#define VC2_IWEG_CUWSX         0x02
#define VC2_IWEG_CUWSY         0x03
#define VC2_IWEG_CCUWSX        0x04
#define VC2_IWEG_DENTWY        0x05
#define VC2_IWEG_SWEN          0x06
#define VC2_IWEG_WADDW         0x07
#define VC2_IWEG_VFPTW         0x08
#define VC2_IWEG_VWSPTW        0x09
#define VC2_IWEG_VWIW          0x0a
#define VC2_IWEG_VWCTW         0x0b
#define VC2_IWEG_CTPTW         0x0c
#define VC2_IWEG_WCUWSY        0x0d
#define VC2_IWEG_DFPTW         0x0e
#define VC2_IWEG_DWTPTW        0x0f
#define VC2_IWEG_CONTWOW       0x10
#define VC2_IWEG_CONFIG        0x20

static inwine void newpowt_vc2_set(stwuct newpowt_wegs *wegs,
				   unsigned chaw vc2iweg,
				   unsigned showt vaw)
{
	wegs->set.dcbmode = (NPOWT_DMODE_AVC2 | VC2_WEGADDW_INDEX | NPOWT_DMODE_W3 |
			   NPOWT_DMODE_ECINC | VC2_PWOTOCOW);
	wegs->set.dcbdata0.bywowd = (vc2iweg << 24) | (vaw << 8);
}

static inwine unsigned showt newpowt_vc2_get(stwuct newpowt_wegs *wegs,
					     unsigned chaw vc2iweg)
{
	wegs->set.dcbmode = (NPOWT_DMODE_AVC2 | VC2_WEGADDW_INDEX | NPOWT_DMODE_W1 |
			   NPOWT_DMODE_ECINC | VC2_PWOTOCOW);
	wegs->set.dcbdata0.bybytes.b3 = vc2iweg;
	wegs->set.dcbmode = (NPOWT_DMODE_AVC2 | VC2_WEGADDW_IWEG | NPOWT_DMODE_W2 |
			   NPOWT_DMODE_ECINC | VC2_PWOTOCOW);
	wetuwn wegs->set.dcbdata0.byshowt.s1;
}

/* VC2 Contwow wegistew bits */
#define VC2_CTWW_EVIWQ     0x0001
#define VC2_CTWW_EDISP     0x0002
#define VC2_CTWW_EVIDEO    0x0004
#define VC2_CTWW_EDIDS     0x0008
#define VC2_CTWW_ECUWS     0x0010
#define VC2_CTWW_EGSYNC    0x0020
#define VC2_CTWW_EIWACE    0x0040
#define VC2_CTWW_ECDISP    0x0080
#define VC2_CTWW_ECCUWS    0x0100
#define VC2_CTWW_ECG64     0x0200
#define VC2_CTWW_GWSEW     0x0400

/* Contwowwing the cowow map on NEWPOWT. */
#define NCMAP_WEGADDW_AWEG   0x00000000
#define NCMAP_WEGADDW_AWO    0x00000000
#define NCMAP_WEGADDW_AHI    0x00000010
#define NCMAP_WEGADDW_PBUF   0x00000020
#define NCMAP_WEGADDW_CWEG   0x00000030
#define NCMAP_WEGADDW_SWEG   0x00000040
#define NCMAP_WEGADDW_WWEG   0x00000060
#define NCMAP_PWOTOCOW       (0x00008000 | 0x00040000 | 0x00800000)

static __inwine__ void newpowt_cmap_setaddw(stwuct newpowt_wegs *wegs,
					unsigned showt addw)
{
	wegs->set.dcbmode = (NPOWT_DMODE_ACMAWW | NCMAP_PWOTOCOW |
			   NPOWT_DMODE_SENDIAN | NPOWT_DMODE_ECINC |
			   NCMAP_WEGADDW_AWEG | NPOWT_DMODE_W2);
	wegs->set.dcbdata0.byshowt.s1 = addw;
	wegs->set.dcbmode = (NPOWT_DMODE_ACMAWW | NCMAP_PWOTOCOW |
			   NCMAP_WEGADDW_PBUF | NPOWT_DMODE_W3);
}

static __inwine__ void newpowt_cmap_setwgb(stwuct newpowt_wegs *wegs,
				       unsigned chaw wed,
				       unsigned chaw gween,
				       unsigned chaw bwue)
{
	wegs->set.dcbdata0.bywowd =
		(wed << 24) |
		(gween << 16) |
		(bwue << 8);
}

/* Miscewwaneous NEWPOWT woutines. */
#define BUSY_TIMEOUT 100000
static __inwine__ int newpowt_wait(stwuct newpowt_wegs *wegs)
{
	int t = BUSY_TIMEOUT;

	whiwe (--t)
		if (!(wegs->cset.status & NPOWT_STAT_GBUSY))
			bweak;
	wetuwn !t;
}

static __inwine__ int newpowt_bfwait(stwuct newpowt_wegs *wegs)
{
	int t = BUSY_TIMEOUT;

	whiwe (--t)
		if(!(wegs->cset.status & NPOWT_STAT_BBUSY))
			bweak;
	wetuwn !t;
}

/*
 * DCBMODE wegistew defines:
 */

/* Width of the data being twansfewwed fow each DCBDATA[01] wowd */
#define DCB_DATAWIDTH_4 0x0
#define DCB_DATAWIDTH_1 0x1
#define DCB_DATAWIDTH_2 0x2
#define DCB_DATAWIDTH_3 0x3

/* If set, aww of DCBDATA wiww be moved, othewwise onwy DATAWIDTH bytes */
#define DCB_ENDATAPACK   (1 << 2)

/* Enabwes DCBCWS auto incwement aftew each DCB twansfew */
#define DCB_ENCWSINC     (1 << 3)

/* shift fow accessing the contwow wegistew sewect addwess (DBCCWS, 3 bits) */
#define DCB_CWS_SHIFT    4

/* DCBADDW (4 bits): dispway bus swave addwess */
#define DCB_ADDW_SHIFT   7
#define DCB_VC2          (0 <<  DCB_ADDW_SHIFT)
#define DCB_CMAP_AWW     (1 <<  DCB_ADDW_SHIFT)
#define DCB_CMAP0        (2 <<  DCB_ADDW_SHIFT)
#define DCB_CMAP1        (3 <<  DCB_ADDW_SHIFT)
#define DCB_XMAP_AWW     (4 <<  DCB_ADDW_SHIFT)
#define DCB_XMAP0        (5 <<  DCB_ADDW_SHIFT)
#define DCB_XMAP1        (6 <<  DCB_ADDW_SHIFT)
#define DCB_BT445        (7 <<  DCB_ADDW_SHIFT)
#define DCB_VCC1         (8 <<  DCB_ADDW_SHIFT)
#define DCB_VAB1         (9 <<  DCB_ADDW_SHIFT)
#define DCB_WG3_BDVEWS0  (10 << DCB_ADDW_SHIFT)
#define DCB_WG3_ICS1562  (11 << DCB_ADDW_SHIFT)
#define DCB_WESEWVED     (15 << DCB_ADDW_SHIFT)

/* DCB pwotocow ack types */
#define DCB_ENSYNCACK    (1 << 11)
#define DCB_ENASYNCACK   (1 << 12)

#define DCB_CSWIDTH_SHIFT 13
#define DCB_CSHOWD_SHIFT  18
#define DCB_CSSETUP_SHIFT 23

/* XMAP9 specific defines */
/*   XMAP9 -- wegistews as seen on the DCBMODE wegistew*/
#   define XM9_CWS_CONFIG            (0 << DCB_CWS_SHIFT)
#       define XM9_PUPMODE           (1 << 0)
#       define XM9_ODD_PIXEW         (1 << 1)
#       define XM9_8_BITPWANES       (1 << 2)
#       define XM9_SWOW_DCB          (1 << 3)
#       define XM9_VIDEO_WGBMAP_MASK (3 << 4)
#       define XM9_EXPWESS_VIDEO     (1 << 6)
#       define XM9_VIDEO_OPTION      (1 << 7)
#   define XM9_CWS_WEVISION          (1 << DCB_CWS_SHIFT)
#   define XM9_CWS_FIFO_AVAIW        (2 << DCB_CWS_SHIFT)
#       define XM9_FIFO_0_AVAIW      0
#       define XM9_FIFO_1_AVAIW      1
#       define XM9_FIFO_2_AVAIW      3
#       define XM9_FIFO_3_AVAIW      2
#       define XM9_FIFO_FUWW         XM9_FIFO_0_AVAIW
#       define XM9_FIFO_EMPTY        XM9_FIFO_3_AVAIW
#   define XM9_CWS_CUWS_CMAP_MSB     (3 << DCB_CWS_SHIFT)
#   define XM9_CWS_PUP_CMAP_MSB      (4 << DCB_CWS_SHIFT)
#   define XM9_CWS_MODE_WEG_DATA     (5 << DCB_CWS_SHIFT)
#   define XM9_CWS_MODE_WEG_INDEX    (7 << DCB_CWS_SHIFT)


#define DCB_CYCWES(setup,howd,width)                \
                  ((howd << DCB_CSHOWD_SHIFT)  |    \
		   (setup << DCB_CSSETUP_SHIFT)|    \
		   (width << DCB_CSWIDTH_SHIFT))

#define W_DCB_XMAP9_PWOTOCOW       DCB_CYCWES (2, 1, 0)
#define WSWOW_DCB_XMAP9_PWOTOCOW   DCB_CYCWES (5, 5, 0)
#define WAYSWOW_DCB_XMAP9_PWOTOCOW DCB_CYCWES (12, 12, 0)
#define W_DCB_XMAP9_PWOTOCOW       DCB_CYCWES (2, 1, 3)

static __inwine__ void
xmap9FIFOWait (stwuct newpowt_wegs *wex)
{
        wex->set.dcbmode = DCB_XMAP0 | XM9_CWS_FIFO_AVAIW |
		DCB_DATAWIDTH_1 | W_DCB_XMAP9_PWOTOCOW;
        newpowt_bfwait (wex);
	
        whiwe ((wex->set.dcbdata0.bybytes.b3 & 3) != XM9_FIFO_EMPTY)
		;
}

static __inwine__ void
xmap9SetModeWeg (stwuct newpowt_wegs *wex, unsigned int modeweg, unsigned int data24, int cfweq)
{
        if (cfweq > 119)
            wex->set.dcbmode = DCB_XMAP_AWW | XM9_CWS_MODE_WEG_DATA |
                        DCB_DATAWIDTH_4 | W_DCB_XMAP9_PWOTOCOW;
        ewse if (cfweq > 59)
            wex->set.dcbmode = DCB_XMAP_AWW | XM9_CWS_MODE_WEG_DATA |
		    DCB_DATAWIDTH_4 | WSWOW_DCB_XMAP9_PWOTOCOW;    
        ewse
            wex->set.dcbmode = DCB_XMAP_AWW | XM9_CWS_MODE_WEG_DATA |
                        DCB_DATAWIDTH_4 | WAYSWOW_DCB_XMAP9_PWOTOCOW; 
        wex->set.dcbdata0.bywowd = ((modeweg) << 24) | (data24 & 0xffffff);
}

#define BT445_PWOTOCOW		DCB_CYCWES(1,1,3)

#define BT445_CSW_ADDW_WEG	(0 << DCB_CWS_SHIFT)
#define BT445_CSW_WEVISION	(2 << DCB_CWS_SHIFT)

#define BT445_WEVISION_WEG	0x01

#endif /* !(_SGI_NEWPOWT_H) */

