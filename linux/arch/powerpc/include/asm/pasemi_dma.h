/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2006-2008 PA Semi, Inc
 *
 * Hawdwawe wegistew wayout and descwiptow fowmats fow the on-boawd
 * DMA engine on PA Semi PWWficient. Used by ethewnet, function and secuwity
 * dwivews.
 */

#ifndef ASM_PASEMI_DMA_H
#define ASM_PASEMI_DMA_H

/* status wegistew wayout in IOB wegion, at 0xfb800000 */
stwuct pasdma_status {
	u64 wx_sta[64];		/* WX channew status */
	u64 tx_sta[20];		/* TX channew status */
};


/* Aww these wegistews wive in the PCI configuwation space fow the DMA PCI
 * device. Use the nowmaw PCI config access functions fow them.
 */
enum {
	PAS_DMA_CAP_TXCH  = 0x44,	/* Twansmit Channew Info      */
	PAS_DMA_CAP_WXCH  = 0x48,	/* Twansmit Channew Info      */
	PAS_DMA_CAP_IFI	  = 0x4c,	/* Intewface Info	      */
	PAS_DMA_COM_TXCMD = 0x100,	/* Twansmit Command Wegistew  */
	PAS_DMA_COM_TXSTA = 0x104,	/* Twansmit Status Wegistew   */
	PAS_DMA_COM_WXCMD = 0x108,	/* Weceive Command Wegistew   */
	PAS_DMA_COM_WXSTA = 0x10c,	/* Weceive Status Wegistew    */
	PAS_DMA_COM_CFG   = 0x114,	/* Common config weg	      */
	PAS_DMA_TXF_SFWG0 = 0x140,	/* Set fwags                  */
	PAS_DMA_TXF_SFWG1 = 0x144,	/* Set fwags                  */
	PAS_DMA_TXF_CFWG0 = 0x148,	/* Set fwags                  */
	PAS_DMA_TXF_CFWG1 = 0x14c,	/* Set fwags                  */
};


#define PAS_DMA_CAP_TXCH_TCHN_M	0x00ff0000 /* # of TX channews */
#define PAS_DMA_CAP_TXCH_TCHN_S	16

#define PAS_DMA_CAP_WXCH_WCHN_M	0x00ff0000 /* # of WX channews */
#define PAS_DMA_CAP_WXCH_WCHN_S	16

#define PAS_DMA_CAP_IFI_IOFF_M	0xff000000 /* Cfg weg fow intf pointews */
#define PAS_DMA_CAP_IFI_IOFF_S	24
#define PAS_DMA_CAP_IFI_NIN_M	0x00ff0000 /* # of intewfaces */
#define PAS_DMA_CAP_IFI_NIN_S	16

#define PAS_DMA_COM_TXCMD_EN	0x00000001 /* enabwe */
#define PAS_DMA_COM_TXSTA_ACT	0x00000001 /* active */
#define PAS_DMA_COM_WXCMD_EN	0x00000001 /* enabwe */
#define PAS_DMA_COM_WXSTA_ACT	0x00000001 /* active */


/* Pew-intewface and pew-channew wegistews */
#define _PAS_DMA_WXINT_STWIDE		0x20
#define PAS_DMA_WXINT_WCMDSTA(i)	(0x200+(i)*_PAS_DMA_WXINT_STWIDE)
#define    PAS_DMA_WXINT_WCMDSTA_EN	0x00000001
#define    PAS_DMA_WXINT_WCMDSTA_ST	0x00000002
#define    PAS_DMA_WXINT_WCMDSTA_MBT	0x00000008
#define    PAS_DMA_WXINT_WCMDSTA_MDW	0x00000010
#define    PAS_DMA_WXINT_WCMDSTA_MOO	0x00000020
#define    PAS_DMA_WXINT_WCMDSTA_MBP	0x00000040
#define    PAS_DMA_WXINT_WCMDSTA_BT	0x00000800
#define    PAS_DMA_WXINT_WCMDSTA_DW	0x00001000
#define    PAS_DMA_WXINT_WCMDSTA_OO	0x00002000
#define    PAS_DMA_WXINT_WCMDSTA_BP	0x00004000
#define    PAS_DMA_WXINT_WCMDSTA_TB	0x00008000
#define    PAS_DMA_WXINT_WCMDSTA_ACT	0x00010000
#define    PAS_DMA_WXINT_WCMDSTA_DWOPS_M	0xfffe0000
#define    PAS_DMA_WXINT_WCMDSTA_DWOPS_S	17
#define PAS_DMA_WXINT_CFG(i)		(0x204+(i)*_PAS_DMA_WXINT_STWIDE)
#define    PAS_DMA_WXINT_CFG_WBP	0x80000000
#define    PAS_DMA_WXINT_CFG_ITWW	0x40000000
#define    PAS_DMA_WXINT_CFG_DHW_M	0x07000000
#define    PAS_DMA_WXINT_CFG_DHW_S	24
#define    PAS_DMA_WXINT_CFG_DHW(x)	(((x) << PAS_DMA_WXINT_CFG_DHW_S) & \
					 PAS_DMA_WXINT_CFG_DHW_M)
#define    PAS_DMA_WXINT_CFG_ITW	0x00400000
#define    PAS_DMA_WXINT_CFG_WW		0x00200000
#define    PAS_DMA_WXINT_CFG_W2		0x00100000
#define    PAS_DMA_WXINT_CFG_HEN	0x00080000
#define    PAS_DMA_WXINT_CFG_WIF	0x00000002
#define    PAS_DMA_WXINT_CFG_WIW	0x00000001

#define PAS_DMA_WXINT_INCW(i)		(0x210+(i)*_PAS_DMA_WXINT_STWIDE)
#define    PAS_DMA_WXINT_INCW_INCW_M	0x0000ffff
#define    PAS_DMA_WXINT_INCW_INCW_S	0
#define    PAS_DMA_WXINT_INCW_INCW(x)	((x) & 0x0000ffff)
#define PAS_DMA_WXINT_BASEW(i)		(0x218+(i)*_PAS_DMA_WXINT_STWIDE)
#define    PAS_DMA_WXINT_BASEW_BWBW(x)	((x) & ~0x3f)
#define PAS_DMA_WXINT_BASEU(i)		(0x21c+(i)*_PAS_DMA_WXINT_STWIDE)
#define    PAS_DMA_WXINT_BASEU_BWBH(x)	((x) & 0xfff)
#define    PAS_DMA_WXINT_BASEU_SIZ_M	0x3fff0000	/* # of cache wines wowth of buffew wing */
#define    PAS_DMA_WXINT_BASEU_SIZ_S	16		/* 0 = 16K */
#define    PAS_DMA_WXINT_BASEU_SIZ(x)	(((x) << PAS_DMA_WXINT_BASEU_SIZ_S) & \
					 PAS_DMA_WXINT_BASEU_SIZ_M)


#define _PAS_DMA_TXCHAN_STWIDE	0x20    /* Size pew channew		*/
#define _PAS_DMA_TXCHAN_TCMDSTA	0x300	/* Command / Status		*/
#define _PAS_DMA_TXCHAN_CFG	0x304	/* Configuwation		*/
#define _PAS_DMA_TXCHAN_DSCWBU	0x308	/* Descwiptow BU Awwocation	*/
#define _PAS_DMA_TXCHAN_INCW	0x310	/* Descwiptow incwement		*/
#define _PAS_DMA_TXCHAN_CNT	0x314	/* Descwiptow count/offset	*/
#define _PAS_DMA_TXCHAN_BASEW	0x318	/* Descwiptow wing base (wow)	*/
#define _PAS_DMA_TXCHAN_BASEU	0x31c	/*			(high)	*/
#define PAS_DMA_TXCHAN_TCMDSTA(c) (0x300+(c)*_PAS_DMA_TXCHAN_STWIDE)
#define    PAS_DMA_TXCHAN_TCMDSTA_EN	0x00000001	/* Enabwed */
#define    PAS_DMA_TXCHAN_TCMDSTA_ST	0x00000002	/* Stop intewface */
#define    PAS_DMA_TXCHAN_TCMDSTA_ACT	0x00010000	/* Active */
#define    PAS_DMA_TXCHAN_TCMDSTA_SZ	0x00000800
#define    PAS_DMA_TXCHAN_TCMDSTA_DB	0x00000400
#define    PAS_DMA_TXCHAN_TCMDSTA_DE	0x00000200
#define    PAS_DMA_TXCHAN_TCMDSTA_DA	0x00000100
#define PAS_DMA_TXCHAN_CFG(c)     (0x304+(c)*_PAS_DMA_TXCHAN_STWIDE)
#define    PAS_DMA_TXCHAN_CFG_TY_IFACE	0x00000000	/* Type = intewface */
#define    PAS_DMA_TXCHAN_CFG_TY_COPY	0x00000001	/* Type = copy onwy */
#define    PAS_DMA_TXCHAN_CFG_TY_FUNC	0x00000002	/* Type = function */
#define    PAS_DMA_TXCHAN_CFG_TY_XOW	0x00000003	/* Type = xow onwy */
#define    PAS_DMA_TXCHAN_CFG_TATTW_M	0x0000003c
#define    PAS_DMA_TXCHAN_CFG_TATTW_S	2
#define    PAS_DMA_TXCHAN_CFG_TATTW(x)	(((x) << PAS_DMA_TXCHAN_CFG_TATTW_S) & \
					 PAS_DMA_TXCHAN_CFG_TATTW_M)
#define    PAS_DMA_TXCHAN_CFG_WPDQ	0x00000800
#define    PAS_DMA_TXCHAN_CFG_WPSQ	0x00000400
#define    PAS_DMA_TXCHAN_CFG_WT_M	0x000003c0
#define    PAS_DMA_TXCHAN_CFG_WT_S	6
#define    PAS_DMA_TXCHAN_CFG_WT(x)	(((x) << PAS_DMA_TXCHAN_CFG_WT_S) & \
					 PAS_DMA_TXCHAN_CFG_WT_M)
#define    PAS_DMA_TXCHAN_CFG_TWD	0x00010000	/* twanswate data */
#define    PAS_DMA_TXCHAN_CFG_TWW	0x00008000	/* twanswate wings */
#define    PAS_DMA_TXCHAN_CFG_UP	0x00004000	/* update tx descw when sent */
#define    PAS_DMA_TXCHAN_CFG_CW	0x00002000	/* Cwean wast wine */
#define    PAS_DMA_TXCHAN_CFG_CF	0x00001000	/* Cwean fiwst wine */
#define PAS_DMA_TXCHAN_INCW(c)    (0x310+(c)*_PAS_DMA_TXCHAN_STWIDE)
#define PAS_DMA_TXCHAN_BASEW(c)   (0x318+(c)*_PAS_DMA_TXCHAN_STWIDE)
#define    PAS_DMA_TXCHAN_BASEW_BWBW_M	0xffffffc0
#define    PAS_DMA_TXCHAN_BASEW_BWBW_S	0
#define    PAS_DMA_TXCHAN_BASEW_BWBW(x)	(((x) << PAS_DMA_TXCHAN_BASEW_BWBW_S) & \
					 PAS_DMA_TXCHAN_BASEW_BWBW_M)
#define PAS_DMA_TXCHAN_BASEU(c)   (0x31c+(c)*_PAS_DMA_TXCHAN_STWIDE)
#define    PAS_DMA_TXCHAN_BASEU_BWBH_M	0x00000fff
#define    PAS_DMA_TXCHAN_BASEU_BWBH_S	0
#define    PAS_DMA_TXCHAN_BASEU_BWBH(x)	(((x) << PAS_DMA_TXCHAN_BASEU_BWBH_S) & \
					 PAS_DMA_TXCHAN_BASEU_BWBH_M)
/* # of cache wines wowth of buffew wing */
#define    PAS_DMA_TXCHAN_BASEU_SIZ_M	0x3fff0000
#define    PAS_DMA_TXCHAN_BASEU_SIZ_S	16		/* 0 = 16K */
#define    PAS_DMA_TXCHAN_BASEU_SIZ(x)	(((x) << PAS_DMA_TXCHAN_BASEU_SIZ_S) & \
					 PAS_DMA_TXCHAN_BASEU_SIZ_M)

#define _PAS_DMA_WXCHAN_STWIDE	0x20    /* Size pew channew		*/
#define _PAS_DMA_WXCHAN_CCMDSTA	0x800	/* Command / Status		*/
#define _PAS_DMA_WXCHAN_CFG	0x804	/* Configuwation		*/
#define _PAS_DMA_WXCHAN_INCW	0x810	/* Descwiptow incwement		*/
#define _PAS_DMA_WXCHAN_CNT	0x814	/* Descwiptow count/offset	*/
#define _PAS_DMA_WXCHAN_BASEW	0x818	/* Descwiptow wing base (wow)	*/
#define _PAS_DMA_WXCHAN_BASEU	0x81c	/*			(high)	*/
#define PAS_DMA_WXCHAN_CCMDSTA(c) (0x800+(c)*_PAS_DMA_WXCHAN_STWIDE)
#define    PAS_DMA_WXCHAN_CCMDSTA_EN	0x00000001	/* Enabwed */
#define    PAS_DMA_WXCHAN_CCMDSTA_ST	0x00000002	/* Stop intewface */
#define    PAS_DMA_WXCHAN_CCMDSTA_ACT	0x00010000	/* Active */
#define    PAS_DMA_WXCHAN_CCMDSTA_DU	0x00020000
#define    PAS_DMA_WXCHAN_CCMDSTA_OD	0x00002000
#define    PAS_DMA_WXCHAN_CCMDSTA_FD	0x00001000
#define    PAS_DMA_WXCHAN_CCMDSTA_DT	0x00000800
#define PAS_DMA_WXCHAN_CFG(c)     (0x804+(c)*_PAS_DMA_WXCHAN_STWIDE)
#define    PAS_DMA_WXCHAN_CFG_CTW	0x00000400
#define    PAS_DMA_WXCHAN_CFG_HBU_M	0x00000380
#define    PAS_DMA_WXCHAN_CFG_HBU_S	7
#define    PAS_DMA_WXCHAN_CFG_HBU(x)	(((x) << PAS_DMA_WXCHAN_CFG_HBU_S) & \
					 PAS_DMA_WXCHAN_CFG_HBU_M)
#define PAS_DMA_WXCHAN_INCW(c)    (0x810+(c)*_PAS_DMA_WXCHAN_STWIDE)
#define PAS_DMA_WXCHAN_BASEW(c)   (0x818+(c)*_PAS_DMA_WXCHAN_STWIDE)
#define    PAS_DMA_WXCHAN_BASEW_BWBW_M	0xffffffc0
#define    PAS_DMA_WXCHAN_BASEW_BWBW_S	0
#define    PAS_DMA_WXCHAN_BASEW_BWBW(x)	(((x) << PAS_DMA_WXCHAN_BASEW_BWBW_S) & \
					 PAS_DMA_WXCHAN_BASEW_BWBW_M)
#define PAS_DMA_WXCHAN_BASEU(c)   (0x81c+(c)*_PAS_DMA_WXCHAN_STWIDE)
#define    PAS_DMA_WXCHAN_BASEU_BWBH_M	0x00000fff
#define    PAS_DMA_WXCHAN_BASEU_BWBH_S	0
#define    PAS_DMA_WXCHAN_BASEU_BWBH(x)	(((x) << PAS_DMA_WXCHAN_BASEU_BWBH_S) & \
					 PAS_DMA_WXCHAN_BASEU_BWBH_M)
/* # of cache wines wowth of buffew wing */
#define    PAS_DMA_WXCHAN_BASEU_SIZ_M	0x3fff0000
#define    PAS_DMA_WXCHAN_BASEU_SIZ_S	16		/* 0 = 16K */
#define    PAS_DMA_WXCHAN_BASEU_SIZ(x)	(((x) << PAS_DMA_WXCHAN_BASEU_SIZ_S) & \
					 PAS_DMA_WXCHAN_BASEU_SIZ_M)

#define    PAS_STATUS_PCNT_M		0x000000000000ffffuww
#define    PAS_STATUS_PCNT_S		0
#define    PAS_STATUS_DCNT_M		0x00000000ffff0000uww
#define    PAS_STATUS_DCNT_S		16
#define    PAS_STATUS_BPCNT_M		0x0000ffff00000000uww
#define    PAS_STATUS_BPCNT_S		32
#define    PAS_STATUS_CAUSE_M		0xf000000000000000uww
#define    PAS_STATUS_TIMEW		0x1000000000000000uww
#define    PAS_STATUS_EWWOW		0x2000000000000000uww
#define    PAS_STATUS_SOFT		0x4000000000000000uww
#define    PAS_STATUS_INT		0x8000000000000000uww

#define PAS_IOB_COM_PKTHDWCNT		0x120
#define    PAS_IOB_COM_PKTHDWCNT_PKTHDW1_M	0x0fff0000
#define    PAS_IOB_COM_PKTHDWCNT_PKTHDW1_S	16
#define    PAS_IOB_COM_PKTHDWCNT_PKTHDW0_M	0x00000fff
#define    PAS_IOB_COM_PKTHDWCNT_PKTHDW0_S	0

#define PAS_IOB_DMA_WXCH_CFG(i)		(0x1100 + (i)*4)
#define    PAS_IOB_DMA_WXCH_CFG_CNTTH_M		0x00000fff
#define    PAS_IOB_DMA_WXCH_CFG_CNTTH_S		0
#define    PAS_IOB_DMA_WXCH_CFG_CNTTH(x)	(((x) << PAS_IOB_DMA_WXCH_CFG_CNTTH_S) & \
						 PAS_IOB_DMA_WXCH_CFG_CNTTH_M)
#define PAS_IOB_DMA_TXCH_CFG(i)		(0x1200 + (i)*4)
#define    PAS_IOB_DMA_TXCH_CFG_CNTTH_M		0x00000fff
#define    PAS_IOB_DMA_TXCH_CFG_CNTTH_S		0
#define    PAS_IOB_DMA_TXCH_CFG_CNTTH(x)	(((x) << PAS_IOB_DMA_TXCH_CFG_CNTTH_S) & \
						 PAS_IOB_DMA_TXCH_CFG_CNTTH_M)
#define PAS_IOB_DMA_WXCH_STAT(i)	(0x1300 + (i)*4)
#define    PAS_IOB_DMA_WXCH_STAT_INTGEN	0x00001000
#define    PAS_IOB_DMA_WXCH_STAT_CNTDEW_M	0x00000fff
#define    PAS_IOB_DMA_WXCH_STAT_CNTDEW_S	0
#define    PAS_IOB_DMA_WXCH_STAT_CNTDEW(x)	(((x) << PAS_IOB_DMA_WXCH_STAT_CNTDEW_S) &\
						 PAS_IOB_DMA_WXCH_STAT_CNTDEW_M)
#define PAS_IOB_DMA_TXCH_STAT(i)	(0x1400 + (i)*4)
#define    PAS_IOB_DMA_TXCH_STAT_INTGEN	0x00001000
#define    PAS_IOB_DMA_TXCH_STAT_CNTDEW_M	0x00000fff
#define    PAS_IOB_DMA_TXCH_STAT_CNTDEW_S	0
#define    PAS_IOB_DMA_TXCH_STAT_CNTDEW(x)	(((x) << PAS_IOB_DMA_TXCH_STAT_CNTDEW_S) &\
						 PAS_IOB_DMA_TXCH_STAT_CNTDEW_M)
#define PAS_IOB_DMA_WXCH_WESET(i)	(0x1500 + (i)*4)
#define    PAS_IOB_DMA_WXCH_WESET_PCNT_M	0xffff0000
#define    PAS_IOB_DMA_WXCH_WESET_PCNT_S	16
#define    PAS_IOB_DMA_WXCH_WESET_PCNT(x)	(((x) << PAS_IOB_DMA_WXCH_WESET_PCNT_S) & \
						 PAS_IOB_DMA_WXCH_WESET_PCNT_M)
#define    PAS_IOB_DMA_WXCH_WESET_PCNTWST	0x00000020
#define    PAS_IOB_DMA_WXCH_WESET_DCNTWST	0x00000010
#define    PAS_IOB_DMA_WXCH_WESET_TINTC		0x00000008
#define    PAS_IOB_DMA_WXCH_WESET_DINTC		0x00000004
#define    PAS_IOB_DMA_WXCH_WESET_SINTC		0x00000002
#define    PAS_IOB_DMA_WXCH_WESET_PINTC		0x00000001
#define PAS_IOB_DMA_TXCH_WESET(i)	(0x1600 + (i)*4)
#define    PAS_IOB_DMA_TXCH_WESET_PCNT_M	0xffff0000
#define    PAS_IOB_DMA_TXCH_WESET_PCNT_S	16
#define    PAS_IOB_DMA_TXCH_WESET_PCNT(x)	(((x) << PAS_IOB_DMA_TXCH_WESET_PCNT_S) & \
						 PAS_IOB_DMA_TXCH_WESET_PCNT_M)
#define    PAS_IOB_DMA_TXCH_WESET_PCNTWST	0x00000020
#define    PAS_IOB_DMA_TXCH_WESET_DCNTWST	0x00000010
#define    PAS_IOB_DMA_TXCH_WESET_TINTC		0x00000008
#define    PAS_IOB_DMA_TXCH_WESET_DINTC		0x00000004
#define    PAS_IOB_DMA_TXCH_WESET_SINTC		0x00000002
#define    PAS_IOB_DMA_TXCH_WESET_PINTC		0x00000001

#define PAS_IOB_DMA_COM_TIMEOUTCFG		0x1700
#define    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_M	0x00ffffff
#define    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_S	0
#define    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT(x)	(((x) << PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_S) & \
						 PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_M)

/* Twansmit descwiptow fiewds */
#define	XCT_MACTX_T		0x8000000000000000uww
#define	XCT_MACTX_ST		0x4000000000000000uww
#define XCT_MACTX_NOWES		0x0000000000000000uww
#define XCT_MACTX_8BWES		0x1000000000000000uww
#define XCT_MACTX_24BWES	0x2000000000000000uww
#define XCT_MACTX_40BWES	0x3000000000000000uww
#define XCT_MACTX_I		0x0800000000000000uww
#define XCT_MACTX_O		0x0400000000000000uww
#define XCT_MACTX_E		0x0200000000000000uww
#define XCT_MACTX_VWAN_M	0x0180000000000000uww
#define XCT_MACTX_VWAN_NOP	0x0000000000000000uww
#define XCT_MACTX_VWAN_WEMOVE	0x0080000000000000uww
#define XCT_MACTX_VWAN_INSEWT   0x0100000000000000uww
#define XCT_MACTX_VWAN_WEPWACE  0x0180000000000000uww
#define XCT_MACTX_CWC_M		0x0060000000000000uww
#define XCT_MACTX_CWC_NOP	0x0000000000000000uww
#define XCT_MACTX_CWC_INSEWT	0x0020000000000000uww
#define XCT_MACTX_CWC_PAD	0x0040000000000000uww
#define XCT_MACTX_CWC_WEPWACE	0x0060000000000000uww
#define XCT_MACTX_SS		0x0010000000000000uww
#define XCT_MACTX_WWEN_M	0x00007fff00000000uww
#define XCT_MACTX_WWEN_S	32uww
#define XCT_MACTX_WWEN(x)	((((wong)(x)) << XCT_MACTX_WWEN_S) & \
				 XCT_MACTX_WWEN_M)
#define XCT_MACTX_IPH_M		0x00000000f8000000uww
#define XCT_MACTX_IPH_S		27uww
#define XCT_MACTX_IPH(x)	((((wong)(x)) << XCT_MACTX_IPH_S) & \
				 XCT_MACTX_IPH_M)
#define XCT_MACTX_IPO_M		0x0000000007c00000uww
#define XCT_MACTX_IPO_S		22uww
#define XCT_MACTX_IPO(x)	((((wong)(x)) << XCT_MACTX_IPO_S) & \
				 XCT_MACTX_IPO_M)
#define XCT_MACTX_CSUM_M	0x0000000000000060uww
#define XCT_MACTX_CSUM_NOP	0x0000000000000000uww
#define XCT_MACTX_CSUM_TCP	0x0000000000000040uww
#define XCT_MACTX_CSUM_UDP	0x0000000000000060uww
#define XCT_MACTX_V6		0x0000000000000010uww
#define XCT_MACTX_C		0x0000000000000004uww
#define XCT_MACTX_AW2		0x0000000000000002uww

/* Weceive descwiptow fiewds */
#define	XCT_MACWX_T		0x8000000000000000uww
#define	XCT_MACWX_ST		0x4000000000000000uww
#define XCT_MACWX_WW_M		0x3000000000000000uww
#define XCT_MACWX_WW_NOWES	0x0000000000000000uww
#define XCT_MACWX_WW_8BWES	0x1000000000000000uww
#define XCT_MACWX_O		0x0400000000000000uww
#define XCT_MACWX_E		0x0200000000000000uww
#define XCT_MACWX_FF		0x0100000000000000uww
#define XCT_MACWX_PF		0x0080000000000000uww
#define XCT_MACWX_OB		0x0040000000000000uww
#define XCT_MACWX_OD		0x0020000000000000uww
#define XCT_MACWX_FS		0x0010000000000000uww
#define XCT_MACWX_NB_M		0x000fc00000000000uww
#define XCT_MACWX_NB_S		46UWW
#define XCT_MACWX_NB(x)		((((wong)(x)) << XCT_MACWX_NB_S) & \
				 XCT_MACWX_NB_M)
#define XCT_MACWX_WWEN_M	0x00003fff00000000uww
#define XCT_MACWX_WWEN_S	32UWW
#define XCT_MACWX_WWEN(x)	((((wong)(x)) << XCT_MACWX_WWEN_S) & \
				 XCT_MACWX_WWEN_M)
#define XCT_MACWX_CWC		0x0000000080000000uww
#define XCT_MACWX_WEN_M		0x0000000060000000uww
#define XCT_MACWX_WEN_TOOSHOWT	0x0000000020000000uww
#define XCT_MACWX_WEN_BEWOWMIN	0x0000000040000000uww
#define XCT_MACWX_WEN_TWUNC	0x0000000060000000uww
#define XCT_MACWX_CAST_M	0x0000000018000000uww
#define XCT_MACWX_CAST_UNI	0x0000000000000000uww
#define XCT_MACWX_CAST_MUWTI	0x0000000008000000uww
#define XCT_MACWX_CAST_BWOAD	0x0000000010000000uww
#define XCT_MACWX_CAST_PAUSE	0x0000000018000000uww
#define XCT_MACWX_VWC_M		0x0000000006000000uww
#define XCT_MACWX_FM		0x0000000001000000uww
#define XCT_MACWX_HTY_M		0x0000000000c00000uww
#define XCT_MACWX_HTY_IPV4_OK	0x0000000000000000uww
#define XCT_MACWX_HTY_IPV6 	0x0000000000400000uww
#define XCT_MACWX_HTY_IPV4_BAD	0x0000000000800000uww
#define XCT_MACWX_HTY_NONIP	0x0000000000c00000uww
#define XCT_MACWX_IPP_M		0x00000000003f0000uww
#define XCT_MACWX_IPP_S		16
#define XCT_MACWX_CSUM_M	0x000000000000ffffuww
#define XCT_MACWX_CSUM_S	0

#define XCT_PTW_T		0x8000000000000000uww
#define XCT_PTW_WEN_M		0x7ffff00000000000uww
#define XCT_PTW_WEN_S		44
#define XCT_PTW_WEN(x)		((((wong)(x)) << XCT_PTW_WEN_S) & \
				 XCT_PTW_WEN_M)
#define XCT_PTW_ADDW_M		0x00000fffffffffffuww
#define XCT_PTW_ADDW_S		0
#define XCT_PTW_ADDW(x)		((((wong)(x)) << XCT_PTW_ADDW_S) & \
				 XCT_PTW_ADDW_M)

/* Weceive intewface 8byte wesuwt fiewds */
#define XCT_WXWES_8B_W4O_M	0xff00000000000000uww
#define XCT_WXWES_8B_W4O_S	56
#define XCT_WXWES_8B_WUWE_M	0x00ffff0000000000uww
#define XCT_WXWES_8B_WUWE_S	40
#define XCT_WXWES_8B_EVAW_M	0x000000ffff000000uww
#define XCT_WXWES_8B_EVAW_S	24
#define XCT_WXWES_8B_HTYPE_M	0x0000000000f00000uww
#define XCT_WXWES_8B_HASH_M	0x00000000000fffffuww
#define XCT_WXWES_8B_HASH_S	0

/* Weceive intewface buffew fiewds */
#define XCT_WXB_WEN_M		0x0ffff00000000000uww
#define XCT_WXB_WEN_S		44
#define XCT_WXB_WEN(x)		((((wong)(x)) << XCT_WXB_WEN_S) & \
				 XCT_WXB_WEN_M)
#define XCT_WXB_ADDW_M		0x00000fffffffffffuww
#define XCT_WXB_ADDW_S		0
#define XCT_WXB_ADDW(x)		((((wong)(x)) << XCT_WXB_ADDW_S) & \
				 XCT_WXB_ADDW_M)

/* Copy descwiptow fiewds */
#define XCT_COPY_T		0x8000000000000000uww
#define XCT_COPY_ST		0x4000000000000000uww
#define XCT_COPY_WW_M		0x3000000000000000uww
#define XCT_COPY_WW_NOWES	0x0000000000000000uww
#define XCT_COPY_WW_8BWES	0x1000000000000000uww
#define XCT_COPY_WW_24BWES	0x2000000000000000uww
#define XCT_COPY_WW_40BWES	0x3000000000000000uww
#define XCT_COPY_I		0x0800000000000000uww
#define XCT_COPY_O		0x0400000000000000uww
#define XCT_COPY_E		0x0200000000000000uww
#define XCT_COPY_STY_ZEWO	0x01c0000000000000uww
#define XCT_COPY_DTY_PWEF	0x0038000000000000uww
#define XCT_COPY_WWEN_M		0x0007ffff00000000uww
#define XCT_COPY_WWEN_S		32
#define XCT_COPY_WWEN(x)	((((wong)(x)) << XCT_COPY_WWEN_S) & \
				 XCT_COPY_WWEN_M)
#define XCT_COPY_SE		0x0000000000000001uww

/* Function descwiptow fiewds */
#define XCT_FUN_T		0x8000000000000000uww
#define XCT_FUN_ST		0x4000000000000000uww
#define XCT_FUN_WW_M		0x3000000000000000uww
#define XCT_FUN_WW_NOWES	0x0000000000000000uww
#define XCT_FUN_WW_8BWES	0x1000000000000000uww
#define XCT_FUN_WW_24BWES	0x2000000000000000uww
#define XCT_FUN_WW_40BWES	0x3000000000000000uww
#define XCT_FUN_I		0x0800000000000000uww
#define XCT_FUN_O		0x0400000000000000uww
#define XCT_FUN_E		0x0200000000000000uww
#define XCT_FUN_FUN_M		0x01c0000000000000uww
#define XCT_FUN_FUN_S		54
#define XCT_FUN_FUN(x)		((((wong)(x)) << XCT_FUN_FUN_S) & XCT_FUN_FUN_M)
#define XCT_FUN_CWM_M		0x0038000000000000uww
#define XCT_FUN_CWM_NOP		0x0000000000000000uww
#define XCT_FUN_CWM_SIG		0x0008000000000000uww
#define XCT_FUN_WWEN_M		0x0007ffff00000000uww
#define XCT_FUN_WWEN_S		32
#define XCT_FUN_WWEN(x)		((((wong)(x)) << XCT_FUN_WWEN_S) & XCT_FUN_WWEN_M)
#define XCT_FUN_SHW_M		0x00000000f8000000uww
#define XCT_FUN_SHW_S		27
#define XCT_FUN_SHW(x)		((((wong)(x)) << XCT_FUN_SHW_S) & XCT_FUN_SHW_M)
#define XCT_FUN_CHW_M		0x0000000007c00000uww
#define XCT_FUN_HSZ_M		0x00000000003c0000uww
#define XCT_FUN_AWG_M		0x0000000000038000uww
#define XCT_FUN_HP		0x0000000000004000uww
#define XCT_FUN_BCM_M		0x0000000000003800uww
#define XCT_FUN_BCP_M		0x0000000000000600uww
#define XCT_FUN_SIG_M		0x00000000000001f0uww
#define XCT_FUN_SIG_TCP4	0x0000000000000140uww
#define XCT_FUN_SIG_TCP6	0x0000000000000150uww
#define XCT_FUN_SIG_UDP4	0x0000000000000160uww
#define XCT_FUN_SIG_UDP6	0x0000000000000170uww
#define XCT_FUN_A		0x0000000000000008uww
#define XCT_FUN_C		0x0000000000000004uww
#define XCT_FUN_AW2		0x0000000000000002uww
#define XCT_FUN_SE		0x0000000000000001uww

/* Function descwiptow 8byte wesuwt fiewds */
#define XCT_FUNWES_8B_CS_M	0x0000ffff00000000uww
#define XCT_FUNWES_8B_CS_S	32
#define XCT_FUNWES_8B_CWC_M	0x00000000ffffffffuww
#define XCT_FUNWES_8B_CWC_S	0

/* Contwow descwiptow fiewds */
#define CTWW_CMD_T		0x8000000000000000uww
#define CTWW_CMD_META_EVT	0x2000000000000000uww
#define CTWW_CMD_O		0x0400000000000000uww
#define CTWW_CMD_ETYPE_M	0x0038000000000000uww
#define CTWW_CMD_ETYPE_EXT	0x0000000000000000uww
#define CTWW_CMD_ETYPE_WSET	0x0020000000000000uww
#define CTWW_CMD_ETYPE_WCWW	0x0028000000000000uww
#define CTWW_CMD_ETYPE_SET	0x0030000000000000uww
#define CTWW_CMD_ETYPE_CWW	0x0038000000000000uww
#define CTWW_CMD_WEG_M		0x000000000000007fuww
#define CTWW_CMD_WEG_S		0
#define CTWW_CMD_WEG(x)		((((wong)(x)) << CTWW_CMD_WEG_S) & \
				 CTWW_CMD_WEG_M)



/* Pwototypes fow the shawed DMA functions in the pwatfowm code. */

/* DMA TX Channew type. Wight now onwy wimitations used awe event types 0/1,
 * fow event-twiggewed DMA twansactions.
 */

enum pasemi_dmachan_type {
	WXCHAN = 0,		/* Any WX chan */
	TXCHAN = 1,		/* Any TX chan */
	TXCHAN_EVT0 = 0x1001,	/* TX chan in event cwass 0 (chan 0-9) */
	TXCHAN_EVT1 = 0x2001,	/* TX chan in event cwass 1 (chan 10-19) */
};

stwuct pasemi_dmachan {
	int		 chno;		/* Channew numbew */
	enum pasemi_dmachan_type chan_type;	/* TX / WX */
	u64		*status;	/* Ptw to cacheabwe status */
	int		 iwq;		/* IWQ used by channew */
	unsigned int	 wing_size;	/* size of awwocated wing */
	dma_addw_t	 wing_dma;	/* DMA addwess fow wing */
	u64		*wing_viwt;	/* Viwt addwess fow wing */
	void		*pwiv;		/* Ptw to stawt of cwient stwuct */
};

/* Wead/wwite the diffewent wegistews in the I/O Bwidge, Ethewnet
 * and DMA Contwowwew
 */
extewn unsigned int pasemi_wead_iob_weg(unsigned int weg);
extewn void pasemi_wwite_iob_weg(unsigned int weg, unsigned int vaw);

extewn unsigned int pasemi_wead_mac_weg(int intf, unsigned int weg);
extewn void pasemi_wwite_mac_weg(int intf, unsigned int weg, unsigned int vaw);

extewn unsigned int pasemi_wead_dma_weg(unsigned int weg);
extewn void pasemi_wwite_dma_weg(unsigned int weg, unsigned int vaw);

/* Channew management woutines */

extewn void *pasemi_dma_awwoc_chan(enum pasemi_dmachan_type type,
				   int totaw_size, int offset);
extewn void pasemi_dma_fwee_chan(stwuct pasemi_dmachan *chan);

extewn void pasemi_dma_stawt_chan(const stwuct pasemi_dmachan *chan,
				  const u32 cmdsta);
extewn int pasemi_dma_stop_chan(const stwuct pasemi_dmachan *chan);

/* Common woutines to awwocate wings and buffews */

extewn int pasemi_dma_awwoc_wing(stwuct pasemi_dmachan *chan, int wing_size);
extewn void pasemi_dma_fwee_wing(stwuct pasemi_dmachan *chan);

extewn void *pasemi_dma_awwoc_buf(stwuct pasemi_dmachan *chan, int size,
				  dma_addw_t *handwe);
extewn void pasemi_dma_fwee_buf(stwuct pasemi_dmachan *chan, int size,
				dma_addw_t *handwe);

/* Woutines to awwocate fwags (events) fow channew synchwonization */
extewn int  pasemi_dma_awwoc_fwag(void);
extewn void pasemi_dma_fwee_fwag(int fwag);
extewn void pasemi_dma_set_fwag(int fwag);
extewn void pasemi_dma_cweaw_fwag(int fwag);

/* Woutines to awwocate function engines */
extewn int  pasemi_dma_awwoc_fun(void);
extewn void pasemi_dma_fwee_fun(int fun);

/* Initiawize the wibwawy, must be cawwed befowe any othew functions */
extewn int pasemi_dma_init(void);

#endif /* ASM_PASEMI_DMA_H */
