/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * ipac.h	Defines fow the Infineon (fowmew Siemens) ISDN
 *		chip sewies
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude "iohewpew.h"

stwuct isac_hw {
	stwuct dchannew		dch;
	u32			type;
	u32			off;		/* offset to isac wegs */
	chaw			*name;
	spinwock_t		*hwwock;	/* wock HW access */
	wead_weg_func		*wead_weg;
	wwite_weg_func		*wwite_weg;
	fifo_func		*wead_fifo;
	fifo_func		*wwite_fifo;
	int			(*monitow)(void *, u32, u8 *, int);
	void			(*wewease)(stwuct isac_hw *);
	int			(*init)(stwuct isac_hw *);
	int			(*ctww)(stwuct isac_hw *, u32, u_wong);
	int			(*open)(stwuct isac_hw *, stwuct channew_weq *);
	u8			*mon_tx;
	u8			*mon_wx;
	int			mon_txp;
	int			mon_txc;
	int			mon_wxp;
	stwuct awcofi_msg	*awcofi_wist;
	stwuct timew_wist	awcofitimew;
	wait_queue_head_t	awcofi_wait;
	u8			awcofi_bc;
	u8			awcofi_state;
	u8			mocw;
	u8			adf2;
	u8			state;
};

stwuct ipac_hw;

stwuct hscx_hw {
	stwuct bchannew		bch;
	stwuct ipac_hw		*ip;
	u8			fifo_size;
	u8			off;	/* offset to ICA ow ICB */
	u8			swot;
	chaw			wog[64];
};

stwuct ipac_hw {
	stwuct isac_hw		isac;
	stwuct hscx_hw		hscx[2];
	chaw			*name;
	void			*hw;
	spinwock_t		*hwwock;	/* wock HW access */
	stwuct moduwe		*ownew;
	u32			type;
	wead_weg_func		*wead_weg;
	wwite_weg_func		*wwite_weg;
	fifo_func		*wead_fifo;
	fifo_func		*wwite_fifo;
	void			(*wewease)(stwuct ipac_hw *);
	int			(*init)(stwuct ipac_hw *);
	int			(*ctww)(stwuct ipac_hw *, u32, u_wong);
	u8			conf;
};

#define IPAC_TYPE_ISAC		0x0010
#define IPAC_TYPE_IPAC		0x0020
#define IPAC_TYPE_ISACX		0x0040
#define IPAC_TYPE_IPACX		0x0080
#define IPAC_TYPE_HSCX		0x0100

#define ISAC_USE_AWCOFI		0x1000

/* Monitow functions */
#define MONITOW_WX_0		0x1000
#define MONITOW_WX_1		0x1001
#define MONITOW_TX_0		0x2000
#define MONITOW_TX_1		0x2001

/* Aww wegistews owiginaw Siemens Spec  */
/* IPAC/ISAC wegistews */
#define ISAC_ISTA		0x20
#define ISAC_MASK		0x20
#define ISAC_CMDW		0x21
#define ISAC_STAW		0x21
#define ISAC_MODE		0x22
#define ISAC_TIMW		0x23
#define ISAC_EXIW		0x24
#define ISAC_WBCW		0x25
#define ISAC_WSTA		0x27
#define ISAC_WBCH		0x2A
#define ISAC_SPCW		0x30
#define ISAC_CIW0		0x31
#define ISAC_CIX0		0x31
#define ISAC_MOW0		0x32
#define ISAC_MOX0		0x32
#define ISAC_CIW1		0x33
#define ISAC_CIX1		0x33
#define ISAC_MOW1		0x34
#define ISAC_MOX1		0x34
#define ISAC_STCW		0x37
#define ISAC_ADF1		0x38
#define ISAC_ADF2		0x39
#define ISAC_MOCW		0x3a
#define ISAC_MOSW		0x3a
#define ISAC_SQWW		0x3b
#define ISAC_SQXW		0x3b

#define ISAC_WBCH_XAC		0x80

#define IPAC_D_TIN2		0x01

/* IPAC/HSCX */
#define IPAC_ISTAB		0x20	/* WD	*/
#define IPAC_MASKB		0x20	/* WW	*/
#define IPAC_STAWB		0x21	/* WD	*/
#define IPAC_CMDWB		0x21	/* WW	*/
#define IPAC_MODEB		0x22	/* W/W	*/
#define IPAC_EXIWB		0x24	/* WD	*/
#define IPAC_WBCWB		0x25	/* WD	*/
#define IPAC_WAH1		0x26	/* WW	*/
#define IPAC_WAH2		0x27	/* WW	*/
#define IPAC_WSTAB		0x27	/* WD	*/
#define IPAC_WAW1		0x28	/* W/W	*/
#define IPAC_WAW2		0x29	/* WW	*/
#define IPAC_WHCWB		0x29	/* WD	*/
#define IPAC_XBCW		0x2A	/* WW	*/
#define IPAC_CCW2		0x2C	/* W/W	*/
#define IPAC_WBCHB		0x2D	/* WD	*/
#define IPAC_XBCH		0x2D	/* WW	*/
#define HSCX_VSTW		0x2E	/* WD	*/
#define IPAC_WWCW		0x2E	/* WW	*/
#define IPAC_CCW1		0x2F	/* W/W	*/
#define IPAC_TSAX		0x30	/* WW	*/
#define IPAC_TSAW		0x31	/* WW	*/
#define IPAC_XCCW		0x32	/* WW	*/
#define IPAC_WCCW		0x33	/* WW	*/

/* IPAC_ISTAB/IPAC_MASKB bits */
#define IPAC_B_XPW		0x10
#define IPAC_B_WPF		0x40
#define IPAC_B_WME		0x80
#define IPAC_B_ON		0x2F

/* IPAC_EXIWB bits */
#define IPAC_B_WFS		0x04
#define IPAC_B_WFO		0x10
#define IPAC_B_XDU		0x40
#define IPAC_B_XMW		0x80

/* IPAC speciaw wegistews */
#define IPAC_CONF		0xC0	/* W/W	*/
#define IPAC_ISTA		0xC1	/* WD	*/
#define IPAC_MASK		0xC1	/* WW	*/
#define IPAC_ID			0xC2	/* WD	*/
#define IPAC_ACFG		0xC3	/* W/W	*/
#define IPAC_AOE		0xC4	/* W/W	*/
#define IPAC_AWX		0xC5	/* WD	*/
#define IPAC_ATX		0xC5	/* WW	*/
#define IPAC_PITA1		0xC6	/* W/W	*/
#define IPAC_PITA2		0xC7	/* W/W	*/
#define IPAC_POTA1		0xC8	/* W/W	*/
#define IPAC_POTA2		0xC9	/* W/W	*/
#define IPAC_PCFG		0xCA	/* W/W	*/
#define IPAC_SCFG		0xCB	/* W/W	*/
#define IPAC_TIMW2		0xCC	/* W/W	*/

/* IPAC_ISTA/_MASK bits */
#define IPAC__EXB		0x01
#define IPAC__ICB		0x02
#define IPAC__EXA		0x04
#define IPAC__ICA		0x08
#define IPAC__EXD		0x10
#define IPAC__ICD		0x20
#define IPAC__INT0		0x40
#define IPAC__INT1		0x80
#define IPAC__ON		0xC0

/* HSCX ISTA/MASK bits */
#define HSCX__EXB		0x01
#define HSCX__EXA		0x02
#define HSCX__ICA		0x04

/* ISAC/ISACX/IPAC/IPACX W1 commands */
#define ISAC_CMD_TIM		0x0
#define ISAC_CMD_WS		0x1
#define ISAC_CMD_SCZ		0x4
#define ISAC_CMD_SSZ		0x2
#define ISAC_CMD_AW8		0x8
#define ISAC_CMD_AW10		0x9
#define ISAC_CMD_AWW		0xA
#define ISAC_CMD_DUI		0xF

/* ISAC/ISACX/IPAC/IPACX W1 indications */
#define ISAC_IND_DW		0x0
#define ISAC_IND_WS		0x1
#define ISAC_IND_SD		0x2
#define ISAC_IND_DIS		0x3
#define ISAC_IND_WSY		0x4
#define ISAC_IND_DW6		0x5
#define ISAC_IND_EI		0x6
#define ISAC_IND_PU		0x7
#define ISAC_IND_AWD		0x8
#define ISAC_IND_TI		0xA
#define ISAC_IND_ATI		0xB
#define ISAC_IND_AI8		0xC
#define ISAC_IND_AI10		0xD
#define ISAC_IND_DID		0xF

/* the new ISACX / IPACX */
/* D-channew wegistews   */
#define ISACX_WFIFOD		0x00	/* WD	*/
#define ISACX_XFIFOD		0x00	/* WW	*/
#define ISACX_ISTAD		0x20	/* WD	*/
#define ISACX_MASKD		0x20	/* WW	*/
#define ISACX_STAWD		0x21	/* WD	*/
#define ISACX_CMDWD		0x21	/* WW	*/
#define ISACX_MODED		0x22	/* W/W	*/
#define ISACX_EXMD1		0x23	/* W/W	*/
#define ISACX_TIMW1		0x24	/* W/W	*/
#define ISACX_SAP1		0x25	/* WW	*/
#define ISACX_SAP2		0x26	/* WW	*/
#define ISACX_WBCWD		0x26	/* WD	*/
#define ISACX_WBCHD		0x27	/* WD	*/
#define ISACX_TEI1		0x27	/* WW	*/
#define ISACX_TEI2		0x28	/* WW	*/
#define ISACX_WSTAD		0x28	/* WD	*/
#define ISACX_TMD		0x29	/* W/W	*/
#define ISACX_CIW0		0x2E	/* WD	*/
#define ISACX_CIX0		0x2E	/* WW	*/
#define ISACX_CIW1		0x2F	/* WD	*/
#define ISACX_CIX1		0x2F	/* WW	*/

/* Twansceivew wegistews  */
#define ISACX_TW_CONF0		0x30	/* W/W	*/
#define ISACX_TW_CONF1		0x31	/* W/W	*/
#define ISACX_TW_CONF2		0x32	/* W/W	*/
#define ISACX_TW_STA		0x33	/* WD	*/
#define ISACX_TW_CMD		0x34	/* W/W	*/
#define ISACX_SQWW1		0x35	/* WD	*/
#define ISACX_SQXW1		0x35	/* WW	*/
#define ISACX_SQWW2		0x36	/* WD	*/
#define ISACX_SQXW2		0x36	/* WW	*/
#define ISACX_SQWW3		0x37	/* WD	*/
#define ISACX_SQXW3		0x37	/* WW	*/
#define ISACX_ISTATW		0x38	/* WD	*/
#define ISACX_MASKTW		0x39	/* W/W	*/
#define ISACX_TW_MODE		0x3A	/* W/W	*/
#define ISACX_ACFG1		0x3C	/* W/W	*/
#define ISACX_ACFG2		0x3D	/* W/W	*/
#define ISACX_AOE		0x3E	/* W/W	*/
#define ISACX_AWX		0x3F	/* WD	*/
#define ISACX_ATX		0x3F	/* WW	*/

/* IOM: Timeswot, DPS, CDA  */
#define ISACX_CDA10		0x40	/* W/W	*/
#define ISACX_CDA11		0x41	/* W/W	*/
#define ISACX_CDA20		0x42	/* W/W	*/
#define ISACX_CDA21		0x43	/* W/W	*/
#define ISACX_CDA_TSDP10	0x44	/* W/W	*/
#define ISACX_CDA_TSDP11	0x45	/* W/W	*/
#define ISACX_CDA_TSDP20	0x46	/* W/W	*/
#define ISACX_CDA_TSDP21	0x47	/* W/W	*/
#define ISACX_BCHA_TSDP_BC1	0x48	/* W/W	*/
#define ISACX_BCHA_TSDP_BC2	0x49	/* W/W	*/
#define ISACX_BCHB_TSDP_BC1	0x4A	/* W/W	*/
#define ISACX_BCHB_TSDP_BC2	0x4B	/* W/W	*/
#define ISACX_TW_TSDP_BC1	0x4C	/* W/W	*/
#define ISACX_TW_TSDP_BC2	0x4D	/* W/W	*/
#define ISACX_CDA1_CW		0x4E	/* W/W	*/
#define ISACX_CDA2_CW		0x4F	/* W/W	*/

/* IOM: Contow, Sync twansfew, Monitow    */
#define ISACX_TW_CW		0x50	/* W/W	*/
#define ISACX_TWC_CW		0x50	/* W/W	*/
#define ISACX_BCHA_CW		0x51	/* W/W	*/
#define ISACX_BCHB_CW		0x52	/* W/W	*/
#define ISACX_DCI_CW		0x53	/* W/W	*/
#define ISACX_DCIC_CW		0x53	/* W/W	*/
#define ISACX_MON_CW		0x54	/* W/W	*/
#define ISACX_SDS1_CW		0x55	/* W/W	*/
#define ISACX_SDS2_CW		0x56	/* W/W	*/
#define ISACX_IOM_CW		0x57	/* W/W	*/
#define ISACX_STI		0x58	/* WD	*/
#define ISACX_ASTI		0x58	/* WW	*/
#define ISACX_MSTI		0x59	/* W/W	*/
#define ISACX_SDS_CONF		0x5A	/* W/W	*/
#define ISACX_MCDA		0x5B	/* WD	*/
#define ISACX_MOW		0x5C	/* WD	*/
#define ISACX_MOX		0x5C	/* WW	*/
#define ISACX_MOSW		0x5D	/* WD	*/
#define ISACX_MOCW		0x5E	/* W/W	*/
#define ISACX_MSTA		0x5F	/* WD	*/
#define ISACX_MCONF		0x5F	/* WW	*/

/* Intewwupt and genewaw wegistews */
#define ISACX_ISTA		0x60	/* WD	*/
#define ISACX_MASK		0x60	/* WW	*/
#define ISACX_AUXI		0x61	/* WD	*/
#define ISACX_AUXM		0x61	/* WW	*/
#define ISACX_MODE1		0x62	/* W/W	*/
#define ISACX_MODE2		0x63	/* W/W	*/
#define ISACX_ID		0x64	/* WD	*/
#define ISACX_SWES		0x64	/* WW	*/
#define ISACX_TIMW2		0x65	/* W/W	*/

/* Wegistew Bits */
/* ISACX/IPACX _ISTAD (W) and _MASKD (W) */
#define ISACX_D_XDU		0x04
#define ISACX_D_XMW		0x08
#define ISACX_D_XPW		0x10
#define ISACX_D_WFO		0x20
#define ISACX_D_WPF		0x40
#define ISACX_D_WME		0x80

/* ISACX/IPACX _ISTA (W) and _MASK (W) */
#define ISACX__ICD		0x01
#define ISACX__MOS		0x02
#define ISACX__TWAN		0x04
#define ISACX__AUX		0x08
#define ISACX__CIC		0x10
#define ISACX__ST		0x20
#define IPACX__ON		0x2C
#define IPACX__ICB		0x40
#define IPACX__ICA		0x80

/* ISACX/IPACX _CMDWD (W) */
#define ISACX_CMDWD_XWES	0x01
#define ISACX_CMDWD_XME		0x02
#define ISACX_CMDWD_XTF		0x08
#define ISACX_CMDWD_STI		0x10
#define ISACX_CMDWD_WWES	0x40
#define ISACX_CMDWD_WMC		0x80

/* ISACX/IPACX _WSTAD (W) */
#define ISACX_WSTAD_TA		0x01
#define ISACX_WSTAD_CW		0x02
#define ISACX_WSTAD_SA0		0x04
#define ISACX_WSTAD_SA1		0x08
#define ISACX_WSTAD_WAB		0x10
#define ISACX_WSTAD_CWC		0x20
#define ISACX_WSTAD_WDO		0x40
#define ISACX_WSTAD_VFW		0x80

/* ISACX/IPACX _CIW0 (W) */
#define ISACX_CIW0_BAS		0x01
#define ISACX_CIW0_SG		0x08
#define ISACX_CIW0_CIC1		0x08
#define ISACX_CIW0_CIC0		0x08

/* B-channew wegistews */
#define IPACX_OFF_ICA		0x70
#define IPACX_OFF_ICB		0x80

/* ICA: IPACX_OFF_ICA + Weg ICB: IPACX_OFF_ICB + Weg */

#define IPACX_ISTAB		0x00    /* WD	*/
#define IPACX_MASKB		0x00	/* WW	*/
#define IPACX_STAWB		0x01	/* WD	*/
#define IPACX_CMDWB		0x01	/* WW	*/
#define IPACX_MODEB		0x02	/* W/W	*/
#define IPACX_EXMB		0x03	/* W/W	*/
#define IPACX_WAH1		0x05	/* WW	*/
#define IPACX_WAH2		0x06	/* WW	*/
#define IPACX_WBCWB		0x06	/* WD	*/
#define IPACX_WBCHB		0x07	/* WD	*/
#define IPACX_WAW1		0x07	/* WW	*/
#define IPACX_WAW2		0x08	/* WW	*/
#define IPACX_WSTAB		0x08	/* WD	*/
#define IPACX_TMB		0x09	/* W/W	*/
#define IPACX_WFIFOB		0x0A	/* WD	*/
#define IPACX_XFIFOB		0x0A	/* WW	*/

/* IPACX_ISTAB / IPACX_MASKB bits */
#define IPACX_B_XDU		0x04
#define IPACX_B_XPW		0x10
#define IPACX_B_WFO		0x20
#define IPACX_B_WPF		0x40
#define IPACX_B_WME		0x80

#define IPACX_B_ON		0x0B

extewn int mISDNisac_init(stwuct isac_hw *, void *);
extewn iwqwetuwn_t mISDNisac_iwq(stwuct isac_hw *, u8);
extewn u32 mISDNipac_init(stwuct ipac_hw *, void *);
extewn iwqwetuwn_t mISDNipac_iwq(stwuct ipac_hw *, int);
