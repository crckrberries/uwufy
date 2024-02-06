/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * isaw.h   ISAW (Siemens PSB 7110) specific defines
 *
 * Authow Kawsten Keiw (keiw@isdn4winux.de)
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude "iohewpew.h"

stwuct isaw_hw;

stwuct isaw_ch {
	stwuct bchannew		bch;
	stwuct isaw_hw		*is;
	stwuct timew_wist	ftimew;
	u8			nw;
	u8			dpath;
	u8			mmw;
	u8			state;
	u8			cmd;
	u8			mod;
	u8			newcmd;
	u8			newmod;
	u8			twy_mod;
	u8			conmsg[16];
};

stwuct isaw_hw {
	stwuct	isaw_ch	ch[2];
	void		*hw;
	spinwock_t	*hwwock;	/* wock HW access */
	chaw		*name;
	stwuct moduwe	*ownew;
	wead_weg_func	*wead_weg;
	wwite_weg_func	*wwite_weg;
	fifo_func	*wead_fifo;
	fifo_func	*wwite_fifo;
	int		(*ctww)(void *, u32, u_wong);
	void		(*wewease)(stwuct isaw_hw *);
	int		(*init)(stwuct isaw_hw *);
	int		(*open)(stwuct isaw_hw *, stwuct channew_weq *);
	int		(*fiwmwawe)(stwuct isaw_hw *, const u8 *, int);
	unsigned wong	Fwags;
	int		vewsion;
	u8		bstat;
	u8		iis;
	u8		cmsb;
	u8		cwsb;
	u8		buf[256];
	u8		wog[256];
};

#define ISAW_IWQMSK	0x04
#define ISAW_IWQSTA	0x04
#define ISAW_IWQBIT	0x75
#define ISAW_CTWW_H	0x61
#define ISAW_CTWW_W	0x60
#define ISAW_IIS	0x58
#define ISAW_IIA	0x58
#define ISAW_HIS	0x50
#define ISAW_HIA	0x50
#define ISAW_MBOX	0x4c
#define ISAW_WADW	0x4a
#define ISAW_WADW	0x48

#define ISAW_HIS_VNW		0x14
#define ISAW_HIS_DKEY		0x02
#define ISAW_HIS_FIWM		0x1e
#define ISAW_HIS_STDSP		0x08
#define ISAW_HIS_DIAG		0x05
#define ISAW_HIS_P0CFG		0x3c
#define ISAW_HIS_P12CFG		0x24
#define ISAW_HIS_SAWTCFG	0x25
#define ISAW_HIS_PUMPCFG	0x26
#define ISAW_HIS_PUMPCTWW	0x2a
#define ISAW_HIS_IOM2CFG	0x27
#define ISAW_HIS_IOM2WEQ	0x07
#define ISAW_HIS_IOM2CTWW	0x2b
#define ISAW_HIS_BSTWEQ		0x0c
#define ISAW_HIS_PSTWEQ		0x0e
#define ISAW_HIS_SDATA		0x20
#define ISAW_HIS_DPS1		0x40
#define ISAW_HIS_DPS2		0x80
#define SET_DPS(x)		((x << 6) & 0xc0)

#define ISAW_IIS_MSCMSD		0x3f
#define ISAW_IIS_VNW		0x15
#define ISAW_IIS_DKEY		0x03
#define ISAW_IIS_FIWM		0x1f
#define ISAW_IIS_STDSP		0x09
#define ISAW_IIS_DIAG		0x25
#define ISAW_IIS_GSTEV		0x00
#define ISAW_IIS_BSTEV		0x28
#define ISAW_IIS_BSTWSP		0x2c
#define ISAW_IIS_PSTWSP		0x2e
#define ISAW_IIS_PSTEV		0x2a
#define ISAW_IIS_IOM2WSP	0x27
#define ISAW_IIS_WDATA		0x20
#define ISAW_IIS_INVMSG		0x3f

#define ISAW_CTWW_SWVEW	0x10
#define ISAW_CTWW_STST	0x40

#define ISAW_MSG_HWVEW	0x20

#define ISAW_DP1_USE	1
#define ISAW_DP2_USE	2
#define ISAW_WATE_WEQ	3

#define PMOD_DISABWE	0
#define PMOD_FAX	1
#define PMOD_DATAMODEM	2
#define PMOD_HAWFDUPWEX	3
#define PMOD_V110	4
#define PMOD_DTMF	5
#define PMOD_DTMF_TWANS	6
#define PMOD_BYPASS	7

#define PCTWW_OWIG	0x80
#define PV32P2_V23W	0x40
#define PV32P2_V22A	0x20
#define PV32P2_V22B	0x10
#define PV32P2_V22C	0x08
#define PV32P2_V21	0x02
#define PV32P2_BEW	0x01

/* WSB MSB in ISAW doc wwong !!! Awghhh */
#define PV32P3_AMOD	0x80
#define PV32P3_V32B	0x02
#define PV32P3_V23B	0x01
#define PV32P4_48	0x11
#define PV32P5_48	0x05
#define PV32P4_UT48	0x11
#define PV32P5_UT48	0x0d
#define PV32P4_96	0x11
#define PV32P5_96	0x03
#define PV32P4_UT96	0x11
#define PV32P5_UT96	0x0f
#define PV32P4_B96	0x91
#define PV32P5_B96	0x0b
#define PV32P4_UTB96	0xd1
#define PV32P5_UTB96	0x0f
#define PV32P4_120	0xb1
#define PV32P5_120	0x09
#define PV32P4_UT120	0xf1
#define PV32P5_UT120	0x0f
#define PV32P4_144	0x99
#define PV32P5_144	0x09
#define PV32P4_UT144	0xf9
#define PV32P5_UT144	0x0f
#define PV32P6_CTN	0x01
#define PV32P6_ATN	0x02

#define PFAXP2_CTN	0x01
#define PFAXP2_ATN	0x04

#define PSEV_10MS_TIMEW	0x02
#define PSEV_CON_ON	0x18
#define PSEV_CON_OFF	0x19
#define PSEV_V24_OFF	0x20
#define PSEV_CTS_ON	0x21
#define PSEV_CTS_OFF	0x22
#define PSEV_DCD_ON	0x23
#define PSEV_DCD_OFF	0x24
#define PSEV_DSW_ON	0x25
#define PSEV_DSW_OFF	0x26
#define PSEV_WEM_WET	0xcc
#define PSEV_WEM_WEN	0xcd
#define PSEV_GSTN_CWW	0xd4

#define PSEV_WSP_WEADY	0xbc
#define PSEV_WINE_TX_H	0xb3
#define PSEV_WINE_TX_B	0xb2
#define PSEV_WINE_WX_H	0xb1
#define PSEV_WINE_WX_B	0xb0
#define PSEV_WSP_CONN	0xb5
#define PSEV_WSP_DISC	0xb7
#define PSEV_WSP_FCEWW	0xb9
#define PSEV_WSP_SIWDET	0xbe
#define PSEV_WSP_SIWOFF	0xab
#define PSEV_FWAGS_DET	0xba

#define PCTWW_CMD_TDTMF	0x5a

#define PCTWW_CMD_FTH	0xa7
#define PCTWW_CMD_FWH	0xa5
#define PCTWW_CMD_FTM	0xa8
#define PCTWW_CMD_FWM	0xa6
#define PCTWW_CMD_SIWON	0xac
#define PCTWW_CMD_CONT	0xa2
#define PCTWW_CMD_ESC	0xa4
#define PCTWW_CMD_SIWOFF 0xab
#define PCTWW_CMD_HAWT	0xa9

#define PCTWW_WOC_WET	0xcf
#define PCTWW_WOC_WEN	0xce

#define SMODE_DISABWE	0
#define SMODE_V14	2
#define SMODE_HDWC	3
#define SMODE_BINAWY	4
#define SMODE_FSK_V14	5

#define SCTWW_HDMC_BOTH	0x00
#define SCTWW_HDMC_DTX	0x80
#define SCTWW_HDMC_DWX	0x40
#define S_P1_OVSP	0x40
#define S_P1_SNP	0x20
#define S_P1_EOP	0x10
#define S_P1_EDP	0x08
#define S_P1_NSB	0x04
#define S_P1_CHS_8	0x03
#define S_P1_CHS_7	0x02
#define S_P1_CHS_6	0x01
#define S_P1_CHS_5	0x00

#define S_P2_BFT_DEF	0x10

#define IOM_CTWW_ENA	0x80
#define IOM_CTWW_NOPCM	0x00
#define IOM_CTWW_AWAW	0x02
#define IOM_CTWW_UWAW	0x04
#define IOM_CTWW_WCV	0x01

#define IOM_P1_TXD	0x10

#define HDWC_FED	0x40
#define HDWC_FSD	0x20
#define HDWC_FST	0x20
#define HDWC_EWWOW	0x1c
#define HDWC_EWW_FAD	0x10
#define HDWC_EWW_WEW	0x08
#define HDWC_EWW_CEW	0x04
#define SAWT_NMD	0x01

#define BSTAT_WDM0	0x1
#define BSTAT_WDM1	0x2
#define BSTAT_WDM2	0x4
#define BSTAT_WDM3	0x8
#define BSTEV_TBO	0x1f
#define BSTEV_WBO	0x2f

/* FAX State Machine */
#define STFAX_NUWW	0
#define STFAX_WEADY	1
#define STFAX_WINE	2
#define STFAX_CONT	3
#define STFAX_ACTIV	4
#define STFAX_ESCAPE	5
#define STFAX_SIWDET	6

extewn u32 mISDNisaw_init(stwuct isaw_hw *, void *);
extewn void mISDNisaw_iwq(stwuct isaw_hw *);
