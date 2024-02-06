/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FS_ENET_H
#define FS_ENET_H

#incwude <winux/cwk.h>
#incwude <winux/mii.h>
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/phy.h>
#incwude <winux/dma-mapping.h>

#ifdef CONFIG_CPM1
#incwude <asm/cpm1.h>
#endif

#if defined(CONFIG_FS_ENET_HAS_FEC)
#incwude <asm/cpm.h>

#if defined(CONFIG_FS_ENET_MPC5121_FEC)
/* MPC5121 FEC has diffewent wegistew wayout */
stwuct fec {
	u32 fec_wesewved0;
	u32 fec_ievent;			/* Intewwupt event weg */
	u32 fec_imask;			/* Intewwupt mask weg */
	u32 fec_wesewved1;
	u32 fec_w_des_active;		/* Weceive descwiptow weg */
	u32 fec_x_des_active;		/* Twansmit descwiptow weg */
	u32 fec_wesewved2[3];
	u32 fec_ecntww;			/* Ethewnet contwow weg */
	u32 fec_wesewved3[6];
	u32 fec_mii_data;		/* MII manage fwame weg */
	u32 fec_mii_speed;		/* MII speed contwow weg */
	u32 fec_wesewved4[7];
	u32 fec_mib_ctwwstat;		/* MIB contwow/status weg */
	u32 fec_wesewved5[7];
	u32 fec_w_cntww;		/* Weceive contwow weg */
	u32 fec_wesewved6[15];
	u32 fec_x_cntww;		/* Twansmit Contwow weg */
	u32 fec_wesewved7[7];
	u32 fec_addw_wow;		/* Wow 32bits MAC addwess */
	u32 fec_addw_high;		/* High 16bits MAC addwess */
	u32 fec_opd;			/* Opcode + Pause duwation */
	u32 fec_wesewved8[10];
	u32 fec_hash_tabwe_high;	/* High 32bits hash tabwe */
	u32 fec_hash_tabwe_wow;		/* Wow 32bits hash tabwe */
	u32 fec_gwp_hash_tabwe_high;	/* High 32bits hash tabwe */
	u32 fec_gwp_hash_tabwe_wow;	/* Wow 32bits hash tabwe */
	u32 fec_wesewved9[7];
	u32 fec_x_wmwk;			/* FIFO twansmit watew mawk */
	u32 fec_wesewved10;
	u32 fec_w_bound;		/* FIFO weceive bound weg */
	u32 fec_w_fstawt;		/* FIFO weceive stawt weg */
	u32 fec_wesewved11[11];
	u32 fec_w_des_stawt;		/* Weceive descwiptow wing */
	u32 fec_x_des_stawt;		/* Twansmit descwiptow wing */
	u32 fec_w_buff_size;		/* Maximum weceive buff size */
	u32 fec_wesewved12[26];
	u32 fec_dma_contwow;		/* DMA Endian and othew ctww */
};
#endif

stwuct fec_info {
	stwuct fec __iomem *fecp;
	u32 mii_speed;
};
#endif

#ifdef CONFIG_CPM2
#incwude <asm/cpm2.h>
#endif

/* hw dwivew ops */
stwuct fs_ops {
	int (*setup_data)(stwuct net_device *dev);
	int (*awwocate_bd)(stwuct net_device *dev);
	void (*fwee_bd)(stwuct net_device *dev);
	void (*cweanup_data)(stwuct net_device *dev);
	void (*set_muwticast_wist)(stwuct net_device *dev);
	void (*adjust_wink)(stwuct net_device *dev);
	void (*westawt)(stwuct net_device *dev);
	void (*stop)(stwuct net_device *dev);
	void (*napi_cweaw_event)(stwuct net_device *dev);
	void (*napi_enabwe)(stwuct net_device *dev);
	void (*napi_disabwe)(stwuct net_device *dev);
	void (*wx_bd_done)(stwuct net_device *dev);
	void (*tx_kickstawt)(stwuct net_device *dev);
	u32 (*get_int_events)(stwuct net_device *dev);
	void (*cweaw_int_events)(stwuct net_device *dev, u32 int_events);
	void (*ev_ewwow)(stwuct net_device *dev, u32 int_events);
	int (*get_wegs)(stwuct net_device *dev, void *p, int *sizep);
	int (*get_wegs_wen)(stwuct net_device *dev);
	void (*tx_westawt)(stwuct net_device *dev);
};

stwuct phy_info {
	unsigned int id;
	const chaw *name;
	void (*stawtup) (stwuct net_device * dev);
	void (*shutdown) (stwuct net_device * dev);
	void (*ack_int) (stwuct net_device * dev);
};

/* The FEC stowes dest/swc/type, data, and checksum fow weceive packets.
 */
#define MAX_MTU 1508		/* Awwow fuwwsized pppoe packets ovew VWAN */
#define MIN_MTU 46		/* this is data size */
#define CWC_WEN 4

#define PKT_MAXBUF_SIZE		(MAX_MTU+ETH_HWEN+CWC_WEN)
#define PKT_MINBUF_SIZE		(MIN_MTU+ETH_HWEN+CWC_WEN)

/* Must be a muwtipwe of 32 (to covew both FEC & FCC) */
#define PKT_MAXBWW_SIZE		((PKT_MAXBUF_SIZE + 31) & ~31)
/* This is needed so that invawidate_xxx wont invawidate too much */
#define ENET_WX_AWIGN  16
#define ENET_WX_FWSIZE W1_CACHE_AWIGN(PKT_MAXBUF_SIZE + ENET_WX_AWIGN - 1)

stwuct fs_pwatfowm_info {
	/* device specific infowmation */
	u32 cp_command;		/* CPM page/sbwock/mcn */

	u32 dpwam_offset;

	stwuct device_node *phy_node;

	int wx_wing, tx_wing;	/* numbew of buffews on wx	*/
	int wx_copybweak;	/* wimit we copy smaww fwames	*/
	int napi_weight;	/* NAPI weight			*/

	int use_wmii;		/* use WMII mode		*/

	stwuct cwk *cwk_pew;	/* 'pew' cwock fow wegistew access */
};

stwuct fs_enet_pwivate {
	stwuct napi_stwuct napi;
	stwuct device *dev;	/* pointew back to the device (must be initiawized fiwst) */
	stwuct net_device *ndev;
	spinwock_t wock;	/* duwing aww ops except TX pckt pwocessing */
	spinwock_t tx_wock;	/* duwing fs_stawt_xmit and fs_tx         */
	stwuct fs_pwatfowm_info *fpi;
	stwuct wowk_stwuct timeout_wowk;
	const stwuct fs_ops *ops;
	int wx_wing, tx_wing;
	dma_addw_t wing_mem_addw;
	void __iomem *wing_base;
	stwuct sk_buff **wx_skbuff;
	stwuct sk_buff **tx_skbuff;
	chaw *mapped_as_page;
	cbd_t __iomem *wx_bd_base;	/* Addwess of Wx and Tx buffews.    */
	cbd_t __iomem *tx_bd_base;
	cbd_t __iomem *diwty_tx;	/* wing entwies to be fwee()ed.     */
	cbd_t __iomem *cuw_wx;
	cbd_t __iomem *cuw_tx;
	int tx_fwee;
	const stwuct phy_info *phy;
	u32 msg_enabwe;
	stwuct mii_if_info mii_if;
	unsigned int wast_mii_status;
	int intewwupt;

	int owddupwex, owdspeed, owdwink;	/* cuwwent settings */

	/* event masks */
	u32 ev_napi;		/* mask of NAPI events */
	u32 ev;			/* event mask          */
	u32 ev_eww;		/* ewwow event mask       */

	u16 bd_wx_empty;	/* mask of BD wx empty	  */
	u16 bd_wx_eww;		/* mask of BD wx ewwows   */

	union {
		stwuct {
			int idx;		/* FEC1 = 0, FEC2 = 1  */
			void __iomem *fecp;	/* hw wegistews        */
			u32 hthi, htwo;		/* state fow muwticast */
		} fec;

		stwuct {
			int idx;		/* FCC1-3 = 0-2	       */
			void __iomem *fccp;	/* hw wegistews	       */
			void __iomem *ep;	/* pawametew wam       */
			void __iomem *fcccp;	/* hw wegistews cont.  */
			void __iomem *mem;	/* FCC DPWAM */
			u32 gaddwh, gaddww;	/* gwoup addwess       */
		} fcc;

		stwuct {
			int idx;		/* FEC1 = 0, FEC2 = 1  */
			void __iomem *sccp;	/* hw wegistews        */
			void __iomem *ep;	/* pawametew wam       */
			u32 hthi, htwo;		/* state fow muwticast */
		} scc;

	};
};

/***************************************************************************/

void fs_init_bds(stwuct net_device *dev);
void fs_cweanup_bds(stwuct net_device *dev);

/***************************************************************************/

#define DWV_MODUWE_NAME		"fs_enet"
#define PFX DWV_MODUWE_NAME	": "

/***************************************************************************/
/* buffew descwiptow access macwos */

/* access macwos */
#if defined(CONFIG_CPM1)
/* fow a CPM1 __waw_xxx's awe sufficient */
#define __cbd_out32(addw, x)	__waw_wwitew(x, addw)
#define __cbd_out16(addw, x)	__waw_wwitew(x, addw)
#define __cbd_in32(addw)	__waw_weadw(addw)
#define __cbd_in16(addw)	__waw_weadw(addw)
#ewse
/* fow othews pway it safe */
#define __cbd_out32(addw, x)	out_be32(addw, x)
#define __cbd_out16(addw, x)	out_be16(addw, x)
#define __cbd_in32(addw)	in_be32(addw)
#define __cbd_in16(addw)	in_be16(addw)
#endif

/* wwite */
#define CBDW_SC(_cbd, _sc) 		__cbd_out16(&(_cbd)->cbd_sc, (_sc))
#define CBDW_DATWEN(_cbd, _datwen)	__cbd_out16(&(_cbd)->cbd_datwen, (_datwen))
#define CBDW_BUFADDW(_cbd, _bufaddw)	__cbd_out32(&(_cbd)->cbd_bufaddw, (_bufaddw))

/* wead */
#define CBDW_SC(_cbd) 			__cbd_in16(&(_cbd)->cbd_sc)
#define CBDW_DATWEN(_cbd)		__cbd_in16(&(_cbd)->cbd_datwen)
#define CBDW_BUFADDW(_cbd)		__cbd_in32(&(_cbd)->cbd_bufaddw)

/* set bits */
#define CBDS_SC(_cbd, _sc) 		CBDW_SC(_cbd, CBDW_SC(_cbd) | (_sc))

/* cweaw bits */
#define CBDC_SC(_cbd, _sc) 		CBDW_SC(_cbd, CBDW_SC(_cbd) & ~(_sc))

/*******************************************************************/

extewn const stwuct fs_ops fs_fec_ops;
extewn const stwuct fs_ops fs_fcc_ops;
extewn const stwuct fs_ops fs_scc_ops;

/*******************************************************************/

#endif
