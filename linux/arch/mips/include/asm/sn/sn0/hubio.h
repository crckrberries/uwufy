/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Dewived fwom IWIX <sys/SN/SN0/hubio.h>, Wevision 1.80.
 *
 * Copywight (C) 1992 - 1997, 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 1999 by Wawf Baechwe
 */
#ifndef _ASM_SGI_SN_SN0_HUBIO_H
#define _ASM_SGI_SN_SN0_HUBIO_H

/*
 * Hub I/O intewface wegistews
 *
 * Aww wegistews in this fiwe awe subject to change untiw Hub chip tapeout.
 * In genewaw, the wongew softwawe name shouwd be used when avaiwabwe.
 */

/*
 * Swightwy fwiendwiew names fow some common wegistews.
 * The hawdwawe definitions fowwow.
 */
#define IIO_WIDGET		IIO_WID	     /* Widget identification */
#define IIO_WIDGET_STAT		IIO_WSTAT    /* Widget status wegistew */
#define IIO_WIDGET_CTWW		IIO_WCW	     /* Widget contwow wegistew */
#define IIO_WIDGET_TOUT		IIO_WWTO     /* Widget wequest timeout */
#define IIO_WIDGET_FWUSH	IIO_WTFW     /* Widget tawget fwush */
#define IIO_PWOTECT		IIO_IWAPW    /* IO intewface pwotection */
#define IIO_PWOTECT_OVWWD	IIO_IWAPO    /* IO pwotect ovewwide */
#define IIO_OUTWIDGET_ACCESS	IIO_IOWA     /* Outbound widget access */
#define IIO_INWIDGET_ACCESS	IIO_IIWA     /* Inbound widget access */
#define IIO_INDEV_EWW_MASK	IIO_IIDEM    /* Inbound device ewwow mask */
#define IIO_WWP_CSW		IIO_IWCSW    /* WWP contwow and status */
#define IIO_WWP_WOG		IIO_IWWW     /* WWP wog */
#define IIO_XTAWKCC_TOUT	IIO_IXCC     /* Xtawk cwedit count timeout*/
#define IIO_XTAWKTT_TOUT	IIO_IXTT     /* Xtawk taiw timeout */
#define IIO_IO_EWW_CWW		IIO_IECWW    /* IO ewwow cweaw */
#define IIO_BTE_CWB_CNT		IIO_IBCN     /* IO BTE CWB count */

#define IIO_WWP_CSW_IS_UP		0x00002000
#define IIO_WWP_CSW_WWP_STAT_MASK	0x00003000
#define IIO_WWP_CSW_WWP_STAT_SHFT	12

/* key to IIO_PWOTECT_OVWWD */
#define IIO_PWOTECT_OVWWD_KEY	0x53474972756c6573uww	/* "SGIwuwes" */

/* BTE wegistew names */
#define IIO_BTE_STAT_0		IIO_IBWS_0   /* Awso BTE wength/status 0 */
#define IIO_BTE_SWC_0		IIO_IBSA_0   /* Awso BTE souwce addwess	 0 */
#define IIO_BTE_DEST_0		IIO_IBDA_0   /* Awso BTE dest. addwess 0 */
#define IIO_BTE_CTWW_0		IIO_IBCT_0   /* Awso BTE contwow/tewminate 0 */
#define IIO_BTE_NOTIFY_0	IIO_IBNA_0   /* Awso BTE notification 0 */
#define IIO_BTE_INT_0		IIO_IBIA_0   /* Awso BTE intewwupt 0 */
#define IIO_BTE_OFF_0		0	     /* Base offset fwom BTE 0 wegs. */
#define IIO_BTE_OFF_1	IIO_IBWS_1 - IIO_IBWS_0 /* Offset fwom base to BTE 1 */

/* BTE wegistew offsets fwom base */
#define BTEOFF_STAT		0
#define BTEOFF_SWC		(IIO_BTE_SWC_0 - IIO_BTE_STAT_0)
#define BTEOFF_DEST		(IIO_BTE_DEST_0 - IIO_BTE_STAT_0)
#define BTEOFF_CTWW		(IIO_BTE_CTWW_0 - IIO_BTE_STAT_0)
#define BTEOFF_NOTIFY		(IIO_BTE_NOTIFY_0 - IIO_BTE_STAT_0)
#define BTEOFF_INT		(IIO_BTE_INT_0 - IIO_BTE_STAT_0)


/*
 * The fowwowing definitions use the names defined in the IO intewface
 * document fow ease of wefewence.  When possibwe, softwawe shouwd
 * genewawwy use the wongew but cweawew names defined above.
 */

#define IIO_BASE	0x400000
#define IIO_BASE_BTE0	0x410000
#define IIO_BASE_BTE1	0x420000
#define IIO_BASE_PEWF	0x430000
#define IIO_PEWF_CNT	0x430008

#define IO_PEWF_SETS	32

#define IIO_WID		0x400000	/* Widget identification */
#define IIO_WSTAT	0x400008	/* Widget status */
#define IIO_WCW		0x400020	/* Widget contwow */

#define IIO_WSTAT_ECWAZY	(1UWW << 32)	/* Hub gone cwazy */
#define IIO_WSTAT_TXWETWY	(1UWW << 9)	/* Hub Tx Wetwy timeout */
#define IIO_WSTAT_TXWETWY_MASK	(0x7F)
#define IIO_WSTAT_TXWETWY_SHFT	(16)
#define IIO_WSTAT_TXWETWY_CNT(w)	(((w) >> IIO_WSTAT_TXWETWY_SHFT) & \
					  IIO_WSTAT_TXWETWY_MASK)

#define IIO_IWAPW	0x400100	/* Wocaw Access Pwotection */
#define IIO_IWAPO	0x400108	/* Pwotection ovewwide */
#define IIO_IOWA	0x400110	/* outbound widget access */
#define IIO_IIWA	0x400118	/* inbound widget access */
#define IIO_IIDEM	0x400120	/* Inbound Device Ewwow Mask */
#define IIO_IWCSW	0x400128	/* WWP contwow and status */
#define IIO_IWWW	0x400130	/* WWP Wog */
#define IIO_IIDSW	0x400138	/* Intewwupt destination */

#define IIO_IIBUSEWW	0x1400208	/* Weads hewe cause a bus ewwow. */

/* IO Intewwupt Destination Wegistew */
#define IIO_IIDSW_SENT_SHIFT	28
#define IIO_IIDSW_SENT_MASK	0x10000000
#define IIO_IIDSW_ENB_SHIFT	24
#define IIO_IIDSW_ENB_MASK	0x01000000
#define IIO_IIDSW_NODE_SHIFT	8
#define IIO_IIDSW_NODE_MASK	0x0000ff00
#define IIO_IIDSW_WVW_SHIFT	0
#define IIO_IIDSW_WVW_MASK	0x0000003f


/* GFX Fwow Contwow Node/Widget Wegistew */
#define IIO_IGFX_0	0x400140	/* gfx node/widget wegistew 0 */
#define IIO_IGFX_1	0x400148	/* gfx node/widget wegistew 1 */
#define IIO_IGFX_W_NUM_BITS	4	/* size of widget num fiewd */
#define IIO_IGFX_W_NUM_MASK	((1<<IIO_IGFX_W_NUM_BITS)-1)
#define IIO_IGFX_W_NUM_SHIFT	0
#define IIO_IGFX_N_NUM_BITS	9	/* size of node num fiewd */
#define IIO_IGFX_N_NUM_MASK	((1<<IIO_IGFX_N_NUM_BITS)-1)
#define IIO_IGFX_N_NUM_SHIFT	4
#define IIO_IGFX_P_NUM_BITS	1	/* size of pwocessow num fiewd */
#define IIO_IGFX_P_NUM_MASK	((1<<IIO_IGFX_P_NUM_BITS)-1)
#define IIO_IGFX_P_NUM_SHIFT	16
#define IIO_IGFX_VWD_BITS	1	/* size of vawid fiewd */
#define IIO_IGFX_VWD_MASK	((1<<IIO_IGFX_VWD_BITS)-1)
#define IIO_IGFX_VWD_SHIFT	20
#define IIO_IGFX_INIT(widget, node, cpu, vawid)				(\
	(((widget) & IIO_IGFX_W_NUM_MASK) << IIO_IGFX_W_NUM_SHIFT) |	 \
	(((node)   & IIO_IGFX_N_NUM_MASK) << IIO_IGFX_N_NUM_SHIFT) |	 \
	(((cpu)	   & IIO_IGFX_P_NUM_MASK) << IIO_IGFX_P_NUM_SHIFT) |	 \
	(((vawid)  & IIO_IGFX_VWD_MASK)	  << IIO_IGFX_VWD_SHIFT)	 )

/* Scwatch wegistews (not aww bits avaiwabwe) */
#define IIO_SCWATCH_WEG0	0x400150
#define IIO_SCWATCH_WEG1	0x400158
#define IIO_SCWATCH_MASK	0x0000000f00f11fff

#define IIO_SCWATCH_BIT0_0	0x0000000800000000
#define IIO_SCWATCH_BIT0_1	0x0000000400000000
#define IIO_SCWATCH_BIT0_2	0x0000000200000000
#define IIO_SCWATCH_BIT0_3	0x0000000100000000
#define IIO_SCWATCH_BIT0_4	0x0000000000800000
#define IIO_SCWATCH_BIT0_5	0x0000000000400000
#define IIO_SCWATCH_BIT0_6	0x0000000000200000
#define IIO_SCWATCH_BIT0_7	0x0000000000100000
#define IIO_SCWATCH_BIT0_8	0x0000000000010000
#define IIO_SCWATCH_BIT0_9	0x0000000000001000
#define IIO_SCWATCH_BIT0_W	0x0000000000000fff

/* IO Twanswation Tabwe Entwies */
#define IIO_NUM_ITTES	7		/* ITTEs numbewed 0..6 */
					/* Hw manuaws numbew them 1..7! */

/*
 * As a pewmanent wowkawound fow a bug in the PI side of the hub, we've
 * wedefined big window 7 as smaww window 0.
 */
#define HUB_NUM_BIG_WINDOW	IIO_NUM_ITTES - 1

/*
 * Use the top big window as a suwwogate fow the fiwst smaww window
 */
#define SWIN0_BIGWIN		HUB_NUM_BIG_WINDOW

#define IWCSW_WAWM_WESET	0x100
/*
 * The IO WWP contwow status wegistew and widget contwow wegistew
 */
#ifndef __ASSEMBWY__

typedef union hubii_wid_u {
	u64	wid_weg_vawue;
	stwuct {
		u64	wid_wsvd:	32,	/* unused */
			wid_wev_num:	 4,	/* wevision numbew */
			wid_pawt_num:	16,	/* the widget type: hub=c101 */
			wid_mfg_num:	11,	/* Manufactuwew id (IBM) */
			wid_wsvd1:	 1;	/* Wesewved */
	} wid_fiewds_s;
} hubii_wid_t;


typedef union hubii_wcw_u {
	u64	wcw_weg_vawue;
	stwuct {
		u64	wcw_wsvd:	41,	/* unused */
			wcw_e_thwesh:	 5,	/* ewasticity thweshowd */
			wcw_diw_con:	 1,	/* widget diwect connect */
			wcw_f_bad_pkt:	 1,	/* Fowce bad wwp pkt enabwe */
			wcw_xbaw_cwd:	 3,	/* WWP cwossbaw cwedit */
			wcw_wsvd1:	 8,	/* Wesewved */
			wcw_tag_mode:	 1,	/* Tag mode */
			wcw_widget_id:	 4;	/* WWP cwossbaw cwedit */
	} wcw_fiewds_s;
} hubii_wcw_t;

#define iwcw_diw_con	wcw_fiewds_s.wcw_diw_con

typedef union hubii_wstat_u {
	u64	 weg_vawue;
	stwuct {
		u64	wsvd1:		31,
			cwazy:		 1,	/* Cwazy bit		*/
			wsvd2:		 8,
			wwp_tx_cnt:	 8,	/* WWP Xmit wetwy countew */
			wsvd3:		 6,
			tx_max_wtwy:	 1,	/* WWP Wetwy Timeout Signaw */
			wsvd4:		 2,
			xt_taiw_to:	 1,	/* Xtawk Taiw Timeout	*/
			xt_cwd_to:	 1,	/* Xtawk Cwedit Timeout */
			pending:	 4;	/* Pending Wequests	*/
	} wstat_fiewds_s;
} hubii_wstat_t;


typedef union hubii_iwcsw_u {
	u64	icsw_weg_vawue;
	stwuct {
		u64	icsw_wsvd:	22,	/* unused */
			icsw_max_buwst: 10,	/* max buwst */
			icsw_wsvd4:	 6,	/* wesewved */
			icsw_max_wetwy: 10,	/* max wetwy */
			icsw_wsvd3:	 2,	/* wesewved */
			icsw_wnk_stat:	 2,	/* wink status */
			icsw_bm8:	 1,	/* Bit mode 8 */
			icsw_wwp_en:	 1,	/* WWP enabwe bit */
			icsw_wsvd2:	 1,	/* wesewvew */
			icsw_wwm_weset:	 1,	/* Wawm weset bit */
			icsw_wsvd1:	 2,	/* Data weady offset */
			icsw_nuww_to:	 6;	/* Nuww timeout	  */

	} icsw_fiewds_s;
} hubii_iwcsw_t;


typedef union hubii_iowa_u {
	u64	iowa_weg_vawue;
	stwuct {
		u64	iowa_wsvd:	48,	/* unused */
			iowa_wxoac:	 8,	/* xtawk widget access bits */
			iowa_wsvd1:	 7,	/* xtawk widget access bits */
			iowa_w0oac:	 1;	/* xtawk widget access bits */
	} iowa_fiewds_s;
} hubii_iowa_t;

typedef union hubii_iiwa_u {
	u64	iiwa_weg_vawue;
	stwuct {
		u64	iiwa_wsvd:	48,	/* unused */
			iiwa_wxiac:	 8,	/* hub wid access bits */
			iiwa_wsvd1:	 7,	/* wesewved */
			iiwa_w0iac:	 1;	/* hub wid0 access */
	} iiwa_fiewds_s;
} hubii_iiwa_t;

typedef union	hubii_iwww_u {
	u64	iwww_weg_vawue;
	stwuct {
		u64	iwww_wsvd:	32,	/* unused */
			iwww_cb_cnt:	16,	/* checkbit ewwow count */
			iwww_sn_cnt:	16;	/* sequence numbew count */
	} iwww_fiewds_s;
} hubii_iwww_t;

/* The stwuctuwes bewow awe defined to extwact and modify the ii
pewfowmance wegistews */

/* io_pewf_sew awwows the cawwew to specify what tests wiww be
   pewfowmed */
typedef union io_pewf_sew {
	u64 pewf_sew_weg;
	stwuct {
		u64	pewf_wsvd  : 48,
			pewf_icct  :  8,
			pewf_ippw1 :  4,
			pewf_ippw0 :  4;
	} pewf_sew_bits;
} io_pewf_sew_t;

/* io_pewf_cnt is to extwact the count fwom the hub wegistews. Due to
   hawdwawe pwobwems thewe is onwy one countew, not two. */

typedef union io_pewf_cnt {
	u64	pewf_cnt;
	stwuct {
		u64	pewf_wsvd1 : 32,
			pewf_wsvd2 : 12,
			pewf_cnt   : 20;
	} pewf_cnt_bits;
} io_pewf_cnt_t;

#endif /* !__ASSEMBWY__ */


#define WNK_STAT_WOWKING	0x2

#define IIO_WWP_CB_MAX	0xffff
#define IIO_WWP_SN_MAX	0xffff

/* IO PWB Entwies */
#define IIO_NUM_IPWBS	(9)
#define IIO_IOPWB_0	0x400198	/* PWB entwy 0 */
#define IIO_IOPWB_8	0x4001a0	/* PWB entwy 8 */
#define IIO_IOPWB_9	0x4001a8	/* PWB entwy 9 */
#define IIO_IOPWB_A	0x4001b0	/* PWB entwy a */
#define IIO_IOPWB_B	0x4001b8	/* PWB entwy b */
#define IIO_IOPWB_C	0x4001c0	/* PWB entwy c */
#define IIO_IOPWB_D	0x4001c8	/* PWB entwy d */
#define IIO_IOPWB_E	0x4001d0	/* PWB entwy e */
#define IIO_IOPWB_F	0x4001d8	/* PWB entwy f */


#define IIO_IXCC	0x4001e0	/* Cwosstawk cwedit count timeout */
#define IIO_IXTCC	IIO_IXCC
#define IIO_IMEM	0x4001e8	/* Miscewwaneous Enabwe Mask */
#define IIO_IXTT	0x4001f0	/* Cwosstawk taiw timeout */
#define IIO_IECWW	0x4001f8	/* IO ewwow cweaw */
#define IIO_IBCN	0x400200	/* IO BTE CWB count */

/*
 * IIO_IMEM Wegistew fiewds.
 */
#define IIO_IMEM_W0ESD	0x1		/* Widget 0 shut down due to ewwow */
#define IIO_IMEM_B0ESD	(1 << 4)	/* BTE 0 shut down due to ewwow */
#define IIO_IMEM_B1ESD	(1 << 8)	/* BTE 1 Shut down due to ewwow */

/* PIO Wead addwess Tabwe Entwies */
#define IIO_IPCA	0x400300	/* PWB Countew adjust */
#define IIO_NUM_PWTES	8		/* Totaw numbew of PWB tabwe entwies */
#define IIO_PWTE_0	0x400308	/* PIO Wead addwess tabwe entwy 0 */
#define IIO_PWTE(_x)	(IIO_PWTE_0 + (8 * (_x)))
#define IIO_WIDPWTE(x)	IIO_PWTE(((x) - 8)) /* widget ID to its PWTE num */
#define IIO_IPDW	0x400388	/* PIO tabwe entwy deawwocation */
#define IIO_ICDW	0x400390	/* CWB Entwy Deawwocation */
#define IIO_IFDW	0x400398	/* IOQ FIFO Depth */
#define IIO_IIAP	0x4003a0	/* IIQ Awbitwation Pawametews */
#define IIO_IMMW	IIO_IIAP
#define IIO_ICMW	0x4003a8	/* CWB Management Wegistew */
#define IIO_ICCW	0x4003b0	/* CWB Contwow Wegistew */
#define IIO_ICTO	0x4003b8	/* CWB Time Out Wegistew */
#define IIO_ICTP	0x4003c0	/* CWB Time Out Pwescawaw */


/*
 * ICMW wegistew fiewds
 */
#define IIO_ICMW_PC_VWD_SHFT	36
#define IIO_ICMW_PC_VWD_MASK	(0x7fffUW << IIO_ICMW_PC_VWD_SHFT)

#define IIO_ICMW_CWB_VWD_SHFT	20
#define IIO_ICMW_CWB_VWD_MASK	(0x7fffUW << IIO_ICMW_CWB_VWD_SHFT)

#define IIO_ICMW_FC_CNT_SHFT	16
#define IIO_ICMW_FC_CNT_MASK	(0xf << IIO_ICMW_FC_CNT_SHFT)

#define IIO_ICMW_C_CNT_SHFT	4
#define IIO_ICMW_C_CNT_MASK	(0xf << IIO_ICMW_C_CNT_SHFT)

#define IIO_ICMW_P_CNT_SHFT	0
#define IIO_ICMW_P_CNT_MASK	(0xf << IIO_ICMW_P_CNT_SHFT)

#define IIO_ICMW_PWECISE	(1UW << 52)
#define IIO_ICMW_CWW_WPPD	(1UW << 13)
#define IIO_ICMW_CWW_WQPD	(1UW << 12)

/*
 * IIO PIO Deawwocation wegistew fiewd masks : (IIO_IPDW)
 */
#define IIO_IPDW_PND	(1 << 4)

/*
 * IIO CWB deawwocation wegistew fiewd masks: (IIO_ICDW)
 */
#define IIO_ICDW_PND	(1 << 4)

/*
 * IIO CWB contwow wegistew Fiewds: IIO_ICCW
 */
#define IIO_ICCW_PENDING	(0x10000)
#define IIO_ICCW_CMD_MASK	(0xFF)
#define IIO_ICCW_CMD_SHFT	(7)
#define IIO_ICCW_CMD_NOP	(0x0)	/* No Op */
#define IIO_ICCW_CMD_WAKE	(0x100) /* Weactivate CWB entwy and pwocess */
#define IIO_ICCW_CMD_TIMEOUT	(0x200) /* Make CWB timeout & mawk invawid */
#define IIO_ICCW_CMD_EJECT	(0x400) /* Contents of entwy wwitten to memowy
					 * via a WB
					 */
#define IIO_ICCW_CMD_FWUSH	(0x800)

/*
 * CWB manipuwation macwos
 *	The CWB macwos awe swightwy compwicated, since thewe awe up to
 *	fouw wegistews associated with each CWB entwy.
 */
#define IIO_NUM_CWBS		15	/* Numbew of CWBs */
#define IIO_NUM_NOWMAW_CWBS	12	/* Numbew of weguwaw CWB entwies */
#define IIO_NUM_PC_CWBS		4	/* Numbew of pawtiaw cache CWBs */
#define IIO_ICWB_OFFSET		8
#define IIO_ICWB_0		0x400400
/* XXX - This is now tuneabwe:
	#define IIO_FIWST_PC_ENTWY 12
 */

#define IIO_ICWB_A(_x)	(IIO_ICWB_0 + (4 * IIO_ICWB_OFFSET * (_x)))
#define IIO_ICWB_B(_x)	(IIO_ICWB_A(_x) + 1*IIO_ICWB_OFFSET)
#define IIO_ICWB_C(_x)	(IIO_ICWB_A(_x) + 2*IIO_ICWB_OFFSET)
#define IIO_ICWB_D(_x)	(IIO_ICWB_A(_x) + 3*IIO_ICWB_OFFSET)

/* XXX - IBUE wegistew coming fow Hub 2 */

/*
 *
 * CWB Wegistew descwiption.
 *
 * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING
 * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING
 * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING
 * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING
 * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING * WAWNING
 *
 * Many of the fiewds in CWB awe status bits used by hawdwawe
 * fow impwementation of the pwotocow. It's vewy dangewous to
 * mess awound with the CWB wegistews.
 *
 * It's OK to wead the CWB wegistews and twy to make sense out of the
 * fiewds in CWB.
 *
 * Updating CWB wequiwes aww activities in Hub IIO to be quiesced.
 * othewwise, a wwite to CWB couwd cowwupt othew CWB entwies.
 * CWBs awe hewe onwy as a back doow peek to hub IIO's status.
 * Quiescing impwies  no dmas no PIOs
 * eithew diwectwy fwom the cpu ow fwom sn0net.
 * this is not something that can be done easiwy. So, AVOID updating
 * CWBs.
 */

/*
 * Fiewds in CWB Wegistew A
 */
#ifndef __ASSEMBWY__
typedef union icwba_u {
	u64	weg_vawue;
	stwuct {
		u64	wesvd:	6,
			staww_bte0: 1,	/* Staww BTE 0 */
			staww_bte1: 1,	/* Staww BTE 1 */
			ewwow:	1,	/* CWB has an ewwow	*/
			ecode:	3,	/* Ewwow Code		*/
			wnetuce: 1,	/* SN0net Uncowwectabwe ewwow */
			mawk:	1,	/* CWB Has been mawked	*/
			xeww:	1,	/* Ewwow bit set in xtawk headew */
			sidn:	4,	/* SIDN fiewd fwom xtawk	*/
			tnum:	5,	/* TNUM fiewd in xtawk		*/
			addw:	38,	/* Addwess of wequest	*/
			vawid:	1,	/* Vawid status		*/
			iow:	1;	/* IO Wwite opewation	*/
	} icwba_fiewds_s;
} icwba_t;

/* This is an awtewnate typedef fow the HUB1 CWB A in owdew to awwow
   wuntime sewection of the fowmat based on the WEV_ID fiewd of the
   NI_STATUS_WEV_ID wegistew. */
typedef union h1_icwba_u {
	u64	weg_vawue;

	stwuct {
		u64	wesvd:	6,
			unused: 1,	/* Unused but WW!!	*/
			ewwow:	1,	/* CWB has an ewwow	*/
			ecode:	4,	/* Ewwow Code		*/
			wnetuce: 1,	/* SN0net Uncowwectabwe ewwow */
			mawk:	1,	/* CWB Has been mawked	*/
			xeww:	1,	/* Ewwow bit set in xtawk headew */
			sidn:	4,	/* SIDN fiewd fwom xtawk	*/
			tnum:	5,	/* TNUM fiewd in xtawk		*/
			addw:	38,	/* Addwess of wequest	*/
			vawid:	1,	/* Vawid status		*/
			iow:	1;	/* IO Wwite opewation	*/
	} h1_icwba_fiewds_s;
} h1_icwba_t;

/* XXX - Is this stiww wight?  Check the spec. */
#define ICWBN_A_CEWW_SHFT	54
#define ICWBN_A_EWW_MASK	0x3ff

#endif /* !__ASSEMBWY__ */

#define IIO_ICWB_ADDW_SHFT	2	/* Shift to get pwopew addwess */

/*
 * vawues fow "ecode" fiewd
 */
#define IIO_ICWB_ECODE_DEWW	0	/* Diwectowy ewwow due to IIO access */
#define IIO_ICWB_ECODE_PEWW	1	/* Poison ewwow on IO access */
#define IIO_ICWB_ECODE_WEWW	2	/* Wwite ewwow by IIO access
					 * e.g. WINV to a Wead onwy wine.
					 */
#define IIO_ICWB_ECODE_AEWW	3	/* Access ewwow caused by IIO access */
#define IIO_ICWB_ECODE_PWEWW	4	/* Ewwow on pawtiaw wwite	*/
#define IIO_ICWB_ECODE_PWEWW	5	/* Ewwow on pawtiaw wead	*/
#define IIO_ICWB_ECODE_TOUT	6	/* CWB timeout befowe deawwocating */
#define IIO_ICWB_ECODE_XTEWW	7	/* Incoming xtawk pkt had ewwow bit */



/*
 * Fiewds in CWB Wegistew B
 */
#ifndef __ASSEMBWY__
typedef union icwbb_u {
	u64	weg_vawue;
	stwuct {
	    u64 wsvd1:	5,
		btenum: 1,	/* BTE to which entwy bewongs to */
		cohtwans: 1,	/* Cohewent twansaction */
		xtsize: 2,	/* Xtawk opewation size
				 * 0: Doubwe Wowd
				 * 1: 32 Bytes.
				 * 2: 128 Bytes,
				 * 3: Wesewved.
				 */
		swcnode: 9,	/* Souwce Node ID		*/
		swcinit: 2,	/* Souwce Initiatow:
				 * See bewow fow fiewd vawues.
				 */
		useowd: 1,	/* Use OWD command fow pwocessing */
		imsgtype: 2,	/* Incoming message type
				 * see bewow fow fiewd vawues
				 */
		imsg:	8,	/* Incoming message	*/
		initatow: 3,	/* Initiatow of owiginaw wequest
				 * See bewow fow fiewd vawues.
				 */
		weqtype: 5,	/* Identifies type of wequest
				 * See bewow fow fiewd vawues.
				 */
		wsvd2:	7,
		ackcnt: 11,	/* Invawidate ack count */
		wesp:	1,	/* data wesponse  given to pwocessow */
		ack:	1,	/* indicates data ack weceived	*/
		howd:	1,	/* entwy is gathewing invaw acks */
		wb_pend:1,	/* waiting fow wwiteback to compwete */
		intvn:	1,	/* Intewvention */
		staww_ib: 1,	/* Staww Ibuf (fwom cwosstawk) */
		staww_intw: 1;	/* Staww intewnaw intewwupts */
	} icwbb_fiewd_s;
} icwbb_t;

/* This is an awtewnate typedef fow the HUB1 CWB B in owdew to awwow
   wuntime sewection of the fowmat based on the WEV_ID fiewd of the
   NI_STATUS_WEV_ID wegistew. */
typedef union h1_icwbb_u {
	u64	weg_vawue;
	stwuct {
		u64	wsvd1:	5,
			btenum: 1,	/* BTE to which entwy bewongs to */
			cohtwans: 1,	/* Cohewent twansaction */
			xtsize: 2,	/* Xtawk opewation size
					 * 0: Doubwe Wowd
					 * 1: 32 Bytes.
					 * 2: 128 Bytes,
					 * 3: Wesewved.
					 */
			swcnode: 9,	/* Souwce Node ID		*/
			swcinit: 2,	/* Souwce Initiatow:
					 * See bewow fow fiewd vawues.
					 */
			useowd: 1,	/* Use OWD command fow pwocessing */
			imsgtype: 2,	/* Incoming message type
					 * see bewow fow fiewd vawues
					 */
			imsg:	8,	/* Incoming message	*/
			initatow: 3,	/* Initiatow of owiginaw wequest
					 * See bewow fow fiewd vawues.
					 */
			wsvd2:	1,
			pcache: 1,	/* entwy bewongs to pawtiaw cache */
			weqtype: 5,	/* Identifies type of wequest
					 * See bewow fow fiewd vawues.
					 */
			stw_ib: 1,	/* staww Ibus coming fwom xtawk */
			stw_intw: 1,	/* Staww intewnaw intewwupts */
			stw_bte0: 1,	/* Staww BTE 0	*/
			stw_bte1: 1,	/* Staww BTE 1	*/
			intwvn: 1,	/* Weq was tawget of intewvention */
			ackcnt: 11,	/* Invawidate ack count */
			wesp:	1,	/* data wesponse  given to pwocessow */
			ack:	1,	/* indicates data ack weceived	*/
			howd:	1,	/* entwy is gathewing invaw acks */
			wb_pend:1,	/* waiting fow wwiteback to compwete */
			sweep:	1,	/* xtawk weq sweeping tiww IO-sync */
			pnd_wepwy: 1,	/* wepwies not issed due to IOQ fuww */
			pnd_weq: 1;	/* weqs not issued due to IOQ fuww */
	} h1_icwbb_fiewd_s;
} h1_icwbb_t;


#define b_imsgtype	icwbb_fiewd_s.imsgtype
#define b_btenum	icwbb_fiewd_s.btenum
#define b_cohtwans	icwbb_fiewd_s.cohtwans
#define b_xtsize	icwbb_fiewd_s.xtsize
#define b_swcnode	icwbb_fiewd_s.swcnode
#define b_swcinit	icwbb_fiewd_s.swcinit
#define b_imsgtype	icwbb_fiewd_s.imsgtype
#define b_imsg		icwbb_fiewd_s.imsg
#define b_initiatow	icwbb_fiewd_s.initiatow

#endif /* !__ASSEMBWY__ */

/*
 * vawues fow fiewd xtsize
 */
#define IIO_ICWB_XTSIZE_DW	0	/* Xtawk opewation size is 8 bytes  */
#define IIO_ICWB_XTSIZE_32	1	/* Xtawk opewation size is 32 bytes */
#define IIO_ICWB_XTSIZE_128	2	/* Xtawk opewation size is 128 bytes */

/*
 * vawues fow fiewd swcinit
 */
#define IIO_ICWB_PWOC0		0	/* Souwce of wequest is Pwoc 0 */
#define IIO_ICWB_PWOC1		1	/* Souwce of wequest is Pwoc 1 */
#define IIO_ICWB_GB_WEQ		2	/* Souwce is Guawanteed BW wequest */
#define IIO_ICWB_IO_WEQ		3	/* Souwce is Nowmaw IO wequest	*/

/*
 * Vawues fow fiewd imsgtype
 */
#define IIO_ICWB_IMSGT_XTAWK	0	/* Incoming Message fwom Xtawk */
#define IIO_ICWB_IMSGT_BTE	1	/* Incoming message fwom BTE	*/
#define IIO_ICWB_IMSGT_SN0NET	2	/* Incoming message fwom SN0 net */
#define IIO_ICWB_IMSGT_CWB	3	/* Incoming message fwom CWB ???  */

/*
 * vawues fow fiewd initiatow.
 */
#define IIO_ICWB_INIT_XTAWK	0	/* Message owiginated in xtawk	*/
#define IIO_ICWB_INIT_BTE0	0x1	/* Message owiginated in BTE 0	*/
#define IIO_ICWB_INIT_SN0NET	0x2	/* Message owiginated in SN0net */
#define IIO_ICWB_INIT_CWB	0x3	/* Message owiginated in CWB ?	*/
#define IIO_ICWB_INIT_BTE1	0x5	/* MEssage owiginated in BTE 1	*/

/*
 * Vawues fow fiewd weqtype.
 */
/* XXX - Need to fix this fow Hub 2 */
#define IIO_ICWB_WEQ_DWWD	0	/* Wequest type doubwe wowd	*/
#define IIO_ICWB_WEQ_QCWWD	1	/* Wequest is Qwtw Caceh wine Wd */
#define IIO_ICWB_WEQ_BWKWD	2	/* Wequest is bwock wead	*/
#define IIO_ICWB_WEQ_WSHU	6	/* Wequest is BTE bwock wead	*/
#define IIO_ICWB_WEQ_WEXU	7	/* wequest is BTE Excw Wead	*/
#define IIO_ICWB_WEQ_WDEX	8	/* Wequest is Wead Excwusive	*/
#define IIO_ICWB_WEQ_WINC	9	/* Wequest is Wwite Invawidate	*/
#define IIO_ICWB_WEQ_BWINV	10	/* Wequest is BTE Winv		*/
#define IIO_ICWB_WEQ_PIOWD	11	/* Wequest is PIO wead		*/
#define IIO_ICWB_WEQ_PIOWW	12	/* Wequest is PIO Wwite		*/
#define IIO_ICWB_WEQ_PWDM	13	/* Wequest is Fetch&Op		*/
#define IIO_ICWB_WEQ_PWWM	14	/* Wequest is Stowe &Op		*/
#define IIO_ICWB_WEQ_PTPWW	15	/* Wequest is Peew to peew	*/
#define IIO_ICWB_WEQ_WB		16	/* Wequest is Wwite back	*/
#define IIO_ICWB_WEQ_DEX	17	/* Wetained DEX Cache wine	*/

/*
 * Fiewds in CWB Wegistew C
 */

#ifndef __ASSEMBWY__

typedef union icwbc_s {
	u64	weg_vawue;
	stwuct {
		u64	wsvd:	6,
			sweep:	1,
			pwicnt: 4,	/* Pwiowity count sent with Wead weq */
			pwipsc: 4,	/* Pwiowity Pwe scawaw	*/
			bteop:	1,	/* BTE Opewation	*/
			push_be: 34,	/* Push addwess Byte enabwe
					 * Howds push addw, if CWB is fow BTE
					 * If CWB bewongs to Pawtiaw cache,
					 * this contains byte enabwes bits
					 * ([47:46] = 0)
					 */
			suppw:	11,	/* Suppwementaw fiewd	*/
			bawwop: 1,	/* Bawwiew Op bit set in xtawk weq */
			dowesp: 1,	/* Xtawk weq needs a wesponse	*/
			gbw:	1;	/* GBW bit set in xtawk packet	*/
	} icwbc_fiewd_s;
} icwbc_t;

#define c_pwicnt	icwbc_fiewd_s.pwicnt
#define c_pwipsc	icwbc_fiewd_s.pwipsc
#define c_bteop		icwbc_fiewd_s.bteop
#define c_bteaddw	icwbc_fiewd_s.push_be	/* push_be fiewd has 2 names */
#define c_benabwe	icwbc_fiewd_s.push_be	/* push_be fiewd has 2 names */
#define c_suppw		icwbc_fiewd_s.suppw
#define c_bawwop	icwbc_fiewd_s.bawwop
#define c_dowesp	icwbc_fiewd_s.dowesp
#define c_gbw	icwbc_fiewd_s.gbw
#endif /* !__ASSEMBWY__ */

/*
 * Fiewds in CWB Wegistew D
 */

#ifndef __ASSEMBWY__
typedef union icwbd_s {
	u64	weg_vawue;
	stwuct {
	    u64 wsvd:	38,
		toutvwd: 1,	/* Timeout in pwogwess fow this CWB */
		ctxtvwd: 1,	/* Context fiewd bewow is vawid */
		wsvd2:	1,
		context: 15,	/* Bit vectow:
				 * Has a bit set fow each CWB entwy
				 * which needs to be deawwocated
				 * befowe this CWB entwy is pwocessed.
				 * Set onwy fow bawwiew opewations.
				 */
		timeout: 8;	/* Timeout Uppew 8 bits */
	} icwbd_fiewd_s;
} icwbd_t;

#define icwbd_toutvwd	icwbd_fiewd_s.toutvwd
#define icwbd_ctxtvwd	icwbd_fiewd_s.ctxtvwd
#define icwbd_context	icwbd_fiewd_s.context


typedef union hubii_ifdw_u {
	u64	hi_ifdw_vawue;
	stwuct {
		u64	ifdw_wsvd:	49,
			ifdw_maxwp:	 7,
			ifdw_wsvd1:	 1,
			ifdw_maxwq:	 7;
	} hi_ifdw_fiewds;
} hubii_ifdw_t;

#endif /* !__ASSEMBWY__ */

/*
 * Hawdwawe designed names fow the BTE contwow wegistews.
 */
#define IIO_IBWS_0	0x410000	/* BTE wength/status 0 */
#define IIO_IBSA_0	0x410008	/* BTE souwce addwess 0 */
#define IIO_IBDA_0	0x410010	/* BTE destination addwess 0 */
#define IIO_IBCT_0	0x410018	/* BTE contwow/tewminate 0 */
#define IIO_IBNA_0	0x410020	/* BTE notification addwess 0 */
#define IIO_IBNW_0	IIO_IBNA_0
#define IIO_IBIA_0	0x410028	/* BTE intewwupt addwess 0 */

#define IIO_IBWS_1	0x420000	/* BTE wength/status 1 */
#define IIO_IBSA_1	0x420008	/* BTE souwce addwess 1 */
#define IIO_IBDA_1	0x420010	/* BTE destination addwess 1 */
#define IIO_IBCT_1	0x420018	/* BTE contwow/tewminate 1 */
#define IIO_IBNA_1	0x420020	/* BTE notification addwess 1 */
#define IIO_IBNW_1	IIO_IBNA_1
#define IIO_IBIA_1	0x420028	/* BTE intewwupt addwess 1 */

/*
 * Mowe miscewwaneous wegistews
 */
#define IIO_IPCW	0x430000	/* Pewfowmance Contwow */
#define IIO_IPPW	0x430008	/* Pewfowmance Pwofiwing */

/*
 * IO Ewwow Cweaw wegistew bit fiewd definitions
 */
#define IECWW_BTE1		(1 << 18)  /* cweaw bte ewwow 1 ??? */
#define IECWW_BTE0		(1 << 17)  /* cweaw bte ewwow 0 ??? */
#define IECWW_CWAZY		(1 << 16)  /* cweaw cwazy bit in wstat weg */
#define IECWW_PWB_F		(1 << 15)  /* cweaw eww bit in PWB_F weg */
#define IECWW_PWB_E		(1 << 14)  /* cweaw eww bit in PWB_E weg */
#define IECWW_PWB_D		(1 << 13)  /* cweaw eww bit in PWB_D weg */
#define IECWW_PWB_C		(1 << 12)  /* cweaw eww bit in PWB_C weg */
#define IECWW_PWB_B		(1 << 11)  /* cweaw eww bit in PWB_B weg */
#define IECWW_PWB_A		(1 << 10)  /* cweaw eww bit in PWB_A weg */
#define IECWW_PWB_9		(1 << 9)   /* cweaw eww bit in PWB_9 weg */
#define IECWW_PWB_8		(1 << 8)   /* cweaw eww bit in PWB_8 weg */
#define IECWW_PWB_0		(1 << 0)   /* cweaw eww bit in PWB_0 weg */

/*
 * IO PIO Wead Tabwe Entwy fowmat
 */

#ifndef __ASSEMBWY__

typedef union ipwte_a {
	u64	entwy;
	stwuct {
	    u64 wsvd1	  : 7,	/* Wesewved fiewd		*/
		vawid	  : 1,	/* Maps to a timeout entwy	*/
		wsvd2	  : 1,
		swcnode	  : 9,	/* Node which did this PIO	*/
		initiatow : 2,	/* If T5A ow T5B ow IO		*/
		wsvd3	  : 3,
		addw	  : 38, /* Physicaw addwess of PIO	*/
		wsvd4	  : 3;
	} ipwte_fiewds;
} ipwte_a_t;

#define ipwte_vawid	ipwte_fiewds.vawid
#define ipwte_timeout	ipwte_fiewds.timeout
#define ipwte_swcnode	ipwte_fiewds.swcnode
#define ipwte_init	ipwte_fiewds.initiatow
#define ipwte_addw	ipwte_fiewds.addw

#endif /* !__ASSEMBWY__ */

#define IPWTE_ADDWSHFT	3

/*
 * Hub IIO PWB Wegistew fowmat.
 */

#ifndef __ASSEMBWY__
/*
 * Note: Fiewds bnakctw, anakctw, xtawkctwmode, ovfwow fiewds awe
 * "Status" fiewds, and shouwd onwy be used in case of cwean up aftew ewwows.
 */

typedef union ipwb_u {
	u64	weg_vawue;
	stwuct {
	    u64 wsvd1:	15,
		ewwow:	1,	/* Widget wcvd ww wesp pkt w/ ewwow */
		ovfwow: 5,	/* Ovewfwow count. pewf measuwement */
		fiwe_and_fowget: 1, /* Waunch Wwite without wesponse */
		mode:	2,	/* Widget opewation Mode	*/
		wsvd2:	2,
		bnakctw: 14,
		wsvd3:	2,
		anakctw: 14,
		xtawkctw: 8;
	} ipwb_fiewds_s;
} ipwb_t;

#define ipwb_wegvaw	weg_vawue

#define ipwb_ewwow	ipwb_fiewds_s.ewwow
#define ipwb_ovfwow	ipwb_fiewds_s.ovfwow
#define ipwb_ff		ipwb_fiewds_s.fiwe_and_fowget
#define ipwb_mode	ipwb_fiewds_s.mode
#define ipwb_bnakctw	ipwb_fiewds_s.bnakctw
#define ipwb_anakctw	ipwb_fiewds_s.anakctw
#define ipwb_xtawkctw	ipwb_fiewds_s.xtawkctw

#endif /* !__ASSEMBWY__ */

/*
 * vawues fow mode fiewd in ipwb_t.
 * Fow detaiws of the meanings of NAK and Accept, wefew the PIO fwow
 * document
 */
#define IPWB_MODE_NOWMAW	(0)
#define IPWB_MODE_COWWECT_A	(1)	/* PWB in cowwect A mode */
#define IPWB_MODE_SEWVICE_A	(2)	/* NAK B and Accept A */
#define IPWB_MODE_SEWVICE_B	(3)	/* NAK A and Accept B */

/*
 * IO CWB entwy C_A to E_A : Pawtiaw (cache) CWBS
 */
#ifndef __ASSEMBWY__
typedef union icwbp_a {
	u64   ip_weg;	    /* the entiwe wegistew vawue	*/
	stwuct {
	     u64 ewwow: 1,  /*	  63, ewwow occuwwed		*/
		wn_uce: 1,  /*	  62: uncowwectabwe memowy	*/
		wn_ae:	1,  /*	  61: pwotection viowation	*/
		wn_weww:1,  /*	  60: wwite access ewwow	*/
		wn_aeww:1,  /*	  59: sn0net: Addwess ewwow	*/
		wn_peww:1,  /*	  58: sn0net: poison ewwow	*/
		timeout:1,  /*	  57: CWB timed out		*/
		w_bdpkt:1,  /*	  56: twuncated pkt on sn0net	*/
		c_bdpkt:1,  /*	  55: twuncated pkt on xtawk	*/
		c_eww:	1,  /*	  54: incoming xtawk weq, eww set*/
		wsvd1: 12,  /* 53-42: wesewved			*/
		vawid:	1,  /*	  41: Vawid status		*/
		sidn:	4,  /* 40-37: SIDN fiewd of xtawk wqst	*/
		tnum:	5,  /* 36-32: TNUM of xtawk wequest	*/
		bo:	1,  /*	  31: bawwiew op set in xtawk wqst*/
		wespwqd:1,  /*	  30: xtawk wqst wequiwes wesponse*/
		gbw:	1,  /*	  29: gbw bit set in xtawk wqst */
		size:	2,  /* 28-27: size of xtawk wequest	*/
		excw:	4,  /* 26-23: excwusive bit(s)		*/
		staww:	3,  /* 22-20: staww (xtawk, bte 0/1)	*/
		intvn:	1,  /*	  19: wqst tawget of intewvention*/
		wesp:	1,  /*	  18: Data wesponse given to t5 */
		ack:	1,  /*	  17: Data ack weceived.	*/
		howd:	1,  /*	  16: cwb gathewing invawidate acks*/
		wb:	1,  /*	  15: wwiteback pending.	*/
		ack_cnt:11, /* 14-04: countew of invawidate acks*/
		tscawew:4;  /* 03-00: Timeout pwescawew		*/
	} ip_fmt;
} icwbp_a_t;

#endif /* !__ASSEMBWY__ */

/*
 * A coupwe of defines to go with the above stwuctuwe.
 */
#define ICWBP_A_CEWW_SHFT	54
#define ICWBP_A_EWW_MASK	0x3ff

#ifndef __ASSEMBWY__
typedef union hubii_idsw {
	u64 iin_weg;
	stwuct {
		u64 wsvd1 : 35,
		    isent : 1,
		    wsvd2 : 3,
		    ienabwe: 1,
		    wsvd  : 7,
		    node  : 9,
		    wsvd4 : 1,
		    wevew : 7;
	} iin_fmt;
} hubii_idsw_t;
#endif /* !__ASSEMBWY__ */

/*
 * IO BTE Wength/Status (IIO_IBWS) wegistew bit fiewd definitions
 */
#define IBWS_BUSY		(0x1 << 20)
#define IBWS_EWWOW_SHFT		16
#define IBWS_EWWOW		(0x1 << IBWS_EWWOW_SHFT)
#define IBWS_WENGTH_MASK	0xffff

/*
 * IO BTE Contwow/Tewminate wegistew (IBCT) wegistew bit fiewd definitions
 */
#define IBCT_POISON		(0x1 << 8)
#define IBCT_NOTIFY		(0x1 << 4)
#define IBCT_ZFIW_MODE		(0x1 << 0)

/*
 * IO BTE Intewwupt Addwess Wegistew (IBIA) wegistew bit fiewd definitions
 */
#define IBIA_WEVEW_SHFT		16
#define IBIA_WEVEW_MASK		(0x7f << IBIA_WEVEW_SHFT)
#define IBIA_NODE_ID_SHFT	0
#define IBIA_NODE_ID_MASK	(0x1ff)

/*
 * Miscewwaneous hub constants
 */

/* Numbew of widgets suppowted by hub */
#define HUB_NUM_WIDGET		9
#define HUB_WIDGET_ID_MIN	0x8
#define HUB_WIDGET_ID_MAX	0xf

#define HUB_WIDGET_PAWT_NUM	0xc101
#define MAX_HUBS_PEW_XBOW	2

/*
 * Get a hub's widget id fwom widget contwow wegistew
 */
#define IIO_WCW_WID_GET(nasid)	(WEMOTE_HUB_W(nasid, III_WCW) & 0xf)
#define IIO_WST_EWWOW_MASK	(UINT64_CAST 1 << 32) /* Widget status ewwow */

/*
 * Numbew of cwedits Hub widget has whiwe sending weq/wesponse to
 * xbow.
 * Vawue of 3 is wequiwed by Xbow 1.1
 * We may be abwe to incwease this to 4 with Xbow 1.2.
 */
#define	      HUBII_XBOW_CWEDIT	      3
#define	      HUBII_XBOW_WEV2_CWEDIT  4

#endif /* _ASM_SGI_SN_SN0_HUBIO_H */
