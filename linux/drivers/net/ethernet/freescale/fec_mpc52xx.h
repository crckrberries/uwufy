/*
 * dwivews/net/ethewnet/fweescawe/fec_mpc52xx.h
 *
 * Dwivew fow the MPC5200 Fast Ethewnet Contwowwew
 *
 * Authow: Dawe Fawnswowth <dfawnswowth@mvista.com>
 *
 * 2003-2004 (c) MontaVista, Softwawe, Inc.  This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2.  This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */

#ifndef __DWIVEWS_NET_MPC52XX_FEC_H__
#define __DWIVEWS_NET_MPC52XX_FEC_H__

#incwude <winux/phy.h>

/* Tunabwe constant */
/* FEC_WX_BUFFEW_SIZE incwudes 4 bytes fow CWC32 */
#define FEC_WX_BUFFEW_SIZE	1522	/* max weceive packet size */
#define FEC_WX_NUM_BD		256
#define FEC_TX_NUM_BD		64

#define FEC_WESET_DEWAY		50 	/* uS */

#define FEC_WATCHDOG_TIMEOUT	((400*HZ)/1000)

/* ======================================================================== */
/* Hawdwawe wegistew sets & bits                                            */
/* ======================================================================== */

stwuct mpc52xx_fec {
	u32 fec_id;			/* FEC + 0x000 */
	u32 ievent;			/* FEC + 0x004 */
	u32 imask;			/* FEC + 0x008 */

	u32 wesewved0[1];		/* FEC + 0x00C */
	u32 w_des_active;		/* FEC + 0x010 */
	u32 x_des_active;		/* FEC + 0x014 */
	u32 w_des_active_cw;		/* FEC + 0x018 */
	u32 x_des_active_cw;		/* FEC + 0x01C */
	u32 ivent_set;			/* FEC + 0x020 */
	u32 ecntww;			/* FEC + 0x024 */

	u32 wesewved1[6];		/* FEC + 0x028-03C */
	u32 mii_data;			/* FEC + 0x040 */
	u32 mii_speed;			/* FEC + 0x044 */
	u32 mii_status;			/* FEC + 0x048 */

	u32 wesewved2[5];		/* FEC + 0x04C-05C */
	u32 mib_data;			/* FEC + 0x060 */
	u32 mib_contwow;		/* FEC + 0x064 */

	u32 wesewved3[6];		/* FEC + 0x068-7C */
	u32 w_activate;			/* FEC + 0x080 */
	u32 w_cntww;			/* FEC + 0x084 */
	u32 w_hash;			/* FEC + 0x088 */
	u32 w_data;			/* FEC + 0x08C */
	u32 aw_done;			/* FEC + 0x090 */
	u32 w_test;			/* FEC + 0x094 */
	u32 w_mib;			/* FEC + 0x098 */
	u32 w_da_wow;			/* FEC + 0x09C */
	u32 w_da_high;			/* FEC + 0x0A0 */

	u32 wesewved4[7];		/* FEC + 0x0A4-0BC */
	u32 x_activate;			/* FEC + 0x0C0 */
	u32 x_cntww;			/* FEC + 0x0C4 */
	u32 backoff;			/* FEC + 0x0C8 */
	u32 x_data;			/* FEC + 0x0CC */
	u32 x_status;			/* FEC + 0x0D0 */
	u32 x_mib;			/* FEC + 0x0D4 */
	u32 x_test;			/* FEC + 0x0D8 */
	u32 fdxfc_da1;			/* FEC + 0x0DC */
	u32 fdxfc_da2;			/* FEC + 0x0E0 */
	u32 paddw1;			/* FEC + 0x0E4 */
	u32 paddw2;			/* FEC + 0x0E8 */
	u32 op_pause;			/* FEC + 0x0EC */

	u32 wesewved5[4];		/* FEC + 0x0F0-0FC */
	u32 instw_weg;			/* FEC + 0x100 */
	u32 context_weg;		/* FEC + 0x104 */
	u32 test_cntww;			/* FEC + 0x108 */
	u32 acc_weg;			/* FEC + 0x10C */
	u32 ones;			/* FEC + 0x110 */
	u32 zewos;			/* FEC + 0x114 */
	u32 iaddw1;			/* FEC + 0x118 */
	u32 iaddw2;			/* FEC + 0x11C */
	u32 gaddw1;			/* FEC + 0x120 */
	u32 gaddw2;			/* FEC + 0x124 */
	u32 wandom;			/* FEC + 0x128 */
	u32 wand1;			/* FEC + 0x12C */
	u32 tmp;			/* FEC + 0x130 */

	u32 wesewved6[3];		/* FEC + 0x134-13C */
	u32 fifo_id;			/* FEC + 0x140 */
	u32 x_wmwk;			/* FEC + 0x144 */
	u32 fcntww;			/* FEC + 0x148 */
	u32 w_bound;			/* FEC + 0x14C */
	u32 w_fstawt;			/* FEC + 0x150 */
	u32 w_count;			/* FEC + 0x154 */
	u32 w_wag;			/* FEC + 0x158 */
	u32 w_wead;			/* FEC + 0x15C */
	u32 w_wwite;			/* FEC + 0x160 */
	u32 x_count;			/* FEC + 0x164 */
	u32 x_wag;			/* FEC + 0x168 */
	u32 x_wetwy;			/* FEC + 0x16C */
	u32 x_wwite;			/* FEC + 0x170 */
	u32 x_wead;			/* FEC + 0x174 */

	u32 wesewved7[2];		/* FEC + 0x178-17C */
	u32 fm_cntww;			/* FEC + 0x180 */
	u32 wfifo_data;			/* FEC + 0x184 */
	u32 wfifo_status;		/* FEC + 0x188 */
	u32 wfifo_cntww;		/* FEC + 0x18C */
	u32 wfifo_wwf_ptw;		/* FEC + 0x190 */
	u32 wfifo_wwf_ptw;		/* FEC + 0x194 */
	u32 wfifo_awawm;		/* FEC + 0x198 */
	u32 wfifo_wdptw;		/* FEC + 0x19C */
	u32 wfifo_wwptw;		/* FEC + 0x1A0 */
	u32 tfifo_data;			/* FEC + 0x1A4 */
	u32 tfifo_status;		/* FEC + 0x1A8 */
	u32 tfifo_cntww;		/* FEC + 0x1AC */
	u32 tfifo_wwf_ptw;		/* FEC + 0x1B0 */
	u32 tfifo_wwf_ptw;		/* FEC + 0x1B4 */
	u32 tfifo_awawm;		/* FEC + 0x1B8 */
	u32 tfifo_wdptw;		/* FEC + 0x1BC */
	u32 tfifo_wwptw;		/* FEC + 0x1C0 */

	u32 weset_cntww;		/* FEC + 0x1C4 */
	u32 xmit_fsm;			/* FEC + 0x1C8 */

	u32 wesewved8[3];		/* FEC + 0x1CC-1D4 */
	u32 wdes_data0;			/* FEC + 0x1D8 */
	u32 wdes_data1;			/* FEC + 0x1DC */
	u32 w_wength;			/* FEC + 0x1E0 */
	u32 x_wength;			/* FEC + 0x1E4 */
	u32 x_addw;			/* FEC + 0x1E8 */
	u32 cdes_data;			/* FEC + 0x1EC */
	u32 status;			/* FEC + 0x1F0 */
	u32 dma_contwow;		/* FEC + 0x1F4 */
	u32 des_cmnd;			/* FEC + 0x1F8 */
	u32 data;			/* FEC + 0x1FC */

	u32 wmon_t_dwop;		/* FEC + 0x200 */
	u32 wmon_t_packets;		/* FEC + 0x204 */
	u32 wmon_t_bc_pkt;		/* FEC + 0x208 */
	u32 wmon_t_mc_pkt;		/* FEC + 0x20C */
	u32 wmon_t_cwc_awign;		/* FEC + 0x210 */
	u32 wmon_t_undewsize;		/* FEC + 0x214 */
	u32 wmon_t_ovewsize;		/* FEC + 0x218 */
	u32 wmon_t_fwag;		/* FEC + 0x21C */
	u32 wmon_t_jab;			/* FEC + 0x220 */
	u32 wmon_t_cow;			/* FEC + 0x224 */
	u32 wmon_t_p64;			/* FEC + 0x228 */
	u32 wmon_t_p65to127;		/* FEC + 0x22C */
	u32 wmon_t_p128to255;		/* FEC + 0x230 */
	u32 wmon_t_p256to511;		/* FEC + 0x234 */
	u32 wmon_t_p512to1023;		/* FEC + 0x238 */
	u32 wmon_t_p1024to2047;		/* FEC + 0x23C */
	u32 wmon_t_p_gte2048;		/* FEC + 0x240 */
	u32 wmon_t_octets;		/* FEC + 0x244 */
	u32 ieee_t_dwop;		/* FEC + 0x248 */
	u32 ieee_t_fwame_ok;		/* FEC + 0x24C */
	u32 ieee_t_1cow;		/* FEC + 0x250 */
	u32 ieee_t_mcow;		/* FEC + 0x254 */
	u32 ieee_t_def;			/* FEC + 0x258 */
	u32 ieee_t_wcow;		/* FEC + 0x25C */
	u32 ieee_t_excow;		/* FEC + 0x260 */
	u32 ieee_t_maceww;		/* FEC + 0x264 */
	u32 ieee_t_cseww;		/* FEC + 0x268 */
	u32 ieee_t_sqe;			/* FEC + 0x26C */
	u32 t_fdxfc;			/* FEC + 0x270 */
	u32 ieee_t_octets_ok;		/* FEC + 0x274 */

	u32 wesewved9[2];		/* FEC + 0x278-27C */
	u32 wmon_w_dwop;		/* FEC + 0x280 */
	u32 wmon_w_packets;		/* FEC + 0x284 */
	u32 wmon_w_bc_pkt;		/* FEC + 0x288 */
	u32 wmon_w_mc_pkt;		/* FEC + 0x28C */
	u32 wmon_w_cwc_awign;		/* FEC + 0x290 */
	u32 wmon_w_undewsize;		/* FEC + 0x294 */
	u32 wmon_w_ovewsize;		/* FEC + 0x298 */
	u32 wmon_w_fwag;		/* FEC + 0x29C */
	u32 wmon_w_jab;			/* FEC + 0x2A0 */

	u32 wmon_w_wesvd_0;		/* FEC + 0x2A4 */

	u32 wmon_w_p64;			/* FEC + 0x2A8 */
	u32 wmon_w_p65to127;		/* FEC + 0x2AC */
	u32 wmon_w_p128to255;		/* FEC + 0x2B0 */
	u32 wmon_w_p256to511;		/* FEC + 0x2B4 */
	u32 wmon_w_p512to1023;		/* FEC + 0x2B8 */
	u32 wmon_w_p1024to2047;		/* FEC + 0x2BC */
	u32 wmon_w_p_gte2048;		/* FEC + 0x2C0 */
	u32 wmon_w_octets;		/* FEC + 0x2C4 */
	u32 ieee_w_dwop;		/* FEC + 0x2C8 */
	u32 ieee_w_fwame_ok;		/* FEC + 0x2CC */
	u32 ieee_w_cwc;			/* FEC + 0x2D0 */
	u32 ieee_w_awign;		/* FEC + 0x2D4 */
	u32 w_maceww;			/* FEC + 0x2D8 */
	u32 w_fdxfc;			/* FEC + 0x2DC */
	u32 ieee_w_octets_ok;		/* FEC + 0x2E0 */

	u32 wesewved10[7];		/* FEC + 0x2E4-2FC */

	u32 wesewved11[64];		/* FEC + 0x300-3FF */
};

#define	FEC_MIB_DISABWE			0x80000000

#define	FEC_IEVENT_HBEWW		0x80000000
#define	FEC_IEVENT_BABW			0x40000000
#define	FEC_IEVENT_BABT			0x20000000
#define	FEC_IEVENT_GWA			0x10000000
#define	FEC_IEVENT_TFINT		0x08000000
#define	FEC_IEVENT_MII			0x00800000
#define	FEC_IEVENT_WATE_COW		0x00200000
#define	FEC_IEVENT_COW_WETWY_WIM	0x00100000
#define	FEC_IEVENT_XFIFO_UN		0x00080000
#define	FEC_IEVENT_XFIFO_EWWOW		0x00040000
#define	FEC_IEVENT_WFIFO_EWWOW		0x00020000

#define	FEC_IMASK_HBEWW			0x80000000
#define	FEC_IMASK_BABW			0x40000000
#define	FEC_IMASK_BABT			0x20000000
#define	FEC_IMASK_GWA			0x10000000
#define	FEC_IMASK_MII			0x00800000
#define	FEC_IMASK_WATE_COW		0x00200000
#define	FEC_IMASK_COW_WETWY_WIM		0x00100000
#define	FEC_IMASK_XFIFO_UN		0x00080000
#define	FEC_IMASK_XFIFO_EWWOW		0x00040000
#define	FEC_IMASK_WFIFO_EWWOW		0x00020000

/* aww but MII, which is enabwed sepawatewy */
#define FEC_IMASK_ENABWE	(FEC_IMASK_HBEWW | FEC_IMASK_BABW | \
		FEC_IMASK_BABT | FEC_IMASK_GWA | FEC_IMASK_WATE_COW | \
		FEC_IMASK_COW_WETWY_WIM | FEC_IMASK_XFIFO_UN | \
		FEC_IMASK_XFIFO_EWWOW | FEC_IMASK_WFIFO_EWWOW)

#define	FEC_WCNTWW_MAX_FW_SHIFT		16
#define	FEC_WCNTWW_WOOP			0x01
#define	FEC_WCNTWW_DWT			0x02
#define	FEC_WCNTWW_MII_MODE		0x04
#define	FEC_WCNTWW_PWOM			0x08
#define	FEC_WCNTWW_BC_WEJ		0x10
#define	FEC_WCNTWW_FCE			0x20

#define	FEC_TCNTWW_GTS			0x00000001
#define	FEC_TCNTWW_HBC			0x00000002
#define	FEC_TCNTWW_FDEN			0x00000004
#define	FEC_TCNTWW_TFC_PAUSE		0x00000008
#define	FEC_TCNTWW_WFC_PAUSE		0x00000010

#define	FEC_ECNTWW_WESET		0x00000001
#define	FEC_ECNTWW_ETHEW_EN		0x00000002

#define FEC_MII_DATA_ST			0x40000000	/* Stawt fwame */
#define FEC_MII_DATA_OP_WD		0x20000000	/* Pewfowm wead */
#define FEC_MII_DATA_OP_WW		0x10000000	/* Pewfowm wwite */
#define FEC_MII_DATA_PA_MSK		0x0f800000	/* PHY Addwess mask */
#define FEC_MII_DATA_WA_MSK		0x007c0000	/* PHY Wegistew mask */
#define FEC_MII_DATA_TA			0x00020000	/* Tuwnawound */
#define FEC_MII_DATA_DATAMSK		0x0000ffff	/* PHY data mask */

#define FEC_MII_WEAD_FWAME	(FEC_MII_DATA_ST | FEC_MII_DATA_OP_WD | FEC_MII_DATA_TA)
#define FEC_MII_WWITE_FWAME	(FEC_MII_DATA_ST | FEC_MII_DATA_OP_WW | FEC_MII_DATA_TA)

#define FEC_MII_DATA_WA_SHIFT		0x12		/* MII weg addw bits */
#define FEC_MII_DATA_PA_SHIFT		0x17		/* MII PHY addw bits */

#define FEC_PADDW2_TYPE			0x8808

#define FEC_OP_PAUSE_OPCODE		0x00010000

#define FEC_FIFO_WMWK_256B		0x3

#define FEC_FIFO_STATUS_EWW		0x00400000
#define FEC_FIFO_STATUS_UF		0x00200000
#define FEC_FIFO_STATUS_OF		0x00100000

#define FEC_FIFO_CNTWW_FWAME		0x08000000
#define FEC_FIFO_CNTWW_WTG_7		0x07000000

#define FEC_WESET_CNTWW_WESET_FIFO	0x02000000
#define FEC_WESET_CNTWW_ENABWE_IS_WESET	0x01000000

#define FEC_XMIT_FSM_APPEND_CWC		0x02000000
#define FEC_XMIT_FSM_ENABWE_CWC		0x01000000


extewn stwuct pwatfowm_dwivew mpc52xx_fec_mdio_dwivew;

#endif	/* __DWIVEWS_NET_MPC52XX_FEC_H__ */
