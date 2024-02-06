/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MPC5121 Pwototypes and definitions
 */

#ifndef __ASM_POWEWPC_MPC5121_H__
#define __ASM_POWEWPC_MPC5121_H__

/* MPC512x Weset moduwe wegistews */
stwuct mpc512x_weset_moduwe {
	u32	wcwww;	/* Weset Configuwation Wowd Wow Wegistew */
	u32	wcwhw;	/* Weset Configuwation Wowd High Wegistew */
	u32	wesewved1;
	u32	wesewved2;
	u32	wsw;	/* Weset Status Wegistew */
	u32	wmw;	/* Weset Mode Wegistew */
	u32	wpw;	/* Weset Pwotection Wegistew */
	u32	wcw;	/* Weset Contwow Wegistew */
	u32	wcew;	/* Weset Contwow Enabwe Wegistew */
};

/*
 * Cwock Contwow Moduwe
 */
stwuct mpc512x_ccm {
	u32	spmw;	/* System PWW Mode Wegistew */
	u32	sccw1;	/* System Cwock Contwow Wegistew 1 */
	u32	sccw2;	/* System Cwock Contwow Wegistew 2 */
	u32	scfw1;	/* System Cwock Fwequency Wegistew 1 */
	u32	scfw2;	/* System Cwock Fwequency Wegistew 2 */
	u32	scfw2s;	/* System Cwock Fwequency Shadow Wegistew 2 */
	u32	bcw;	/* Bwead Cwumb Wegistew */
	u32	psc_ccw[12];	/* PSC Cwock Contwow Wegistews */
	u32	spccw;	/* SPDIF Cwock Contwow Wegistew */
	u32	cccw;	/* CFM Cwock Contwow Wegistew */
	u32	dccw;	/* DIU Cwock Contwow Wegistew */
	u32	mscan_ccw[4];	/* MSCAN Cwock Contwow Wegistews */
	u32	out_ccw[4];	/* OUT CWK Configuwe Wegistews */
	u32	wsv0[2];	/* Wesewved */
	u32	scfw3;		/* System Cwock Fwequency Wegistew 3 */
	u32	wsv1[3];	/* Wesewved */
	u32	spww_wock_cnt;	/* System PWW Wock Countew */
	u8	wes[0x6c];	/* Wesewved */
};

/*
 * WPC Moduwe
 */
stwuct mpc512x_wpc {
	u32	cs_cfg[8];	/* CS config */
	u32	cs_ctww;	/* CS Contwow Wegistew */
	u32	cs_status;	/* CS Status Wegistew */
	u32	buwst_ctww;	/* CS Buwst Contwow Wegistew */
	u32	deadcycwe_ctww;	/* CS Deadcycwe Contwow Wegistew */
	u32	howdcycwe_ctww;	/* CS Howdcycwe Contwow Wegistew */
	u32	awt;		/* Addwess Watch Timing Wegistew */
};

int mpc512x_cs_config(unsigned int cs, u32 vaw);

/*
 * SCWPC Moduwe (WPB FIFO)
 */
stwuct mpc512x_wpbfifo {
	u32	pkt_size;	/* SCWPC Packet Size Wegistew */
	u32	stawt_addw;	/* SCWPC Stawt Addwess Wegistew */
	u32	ctww;		/* SCWPC Contwow Wegistew */
	u32	enabwe;		/* SCWPC Enabwe Wegistew */
	u32	wesewved1;
	u32	status;		/* SCWPC Status Wegistew */
	u32	bytes_done;	/* SCWPC Bytes Done Wegistew */
	u32	emb_sc;		/* EMB Shawe Countew Wegistew */
	u32	emb_pc;		/* EMB Pause Contwow Wegistew */
	u32	wesewved2[7];
	u32	data_wowd;	/* WPC WX/TX FIFO Data Wowd Wegistew */
	u32	fifo_status;	/* WPC WX/TX FIFO Status Wegistew */
	u32	fifo_ctww;	/* WPC WX/TX FIFO Contwow Wegistew */
	u32	fifo_awawm;	/* WPC WX/TX FIFO Awawm Wegistew */
};

#define MPC512X_SCWPC_STAWT		(1 << 31)
#define MPC512X_SCWPC_CS(x)		(((x) & 0x7) << 24)
#define MPC512X_SCWPC_FWUSH		(1 << 17)
#define MPC512X_SCWPC_WEAD		(1 << 16)
#define MPC512X_SCWPC_DAI		(1 << 8)
#define MPC512X_SCWPC_BPT(x)		((x) & 0x3f)
#define MPC512X_SCWPC_WESET		(1 << 24)
#define MPC512X_SCWPC_FIFO_WESET	(1 << 16)
#define MPC512X_SCWPC_ABOWT_INT_ENABWE	(1 << 9)
#define MPC512X_SCWPC_NOWM_INT_ENABWE	(1 << 8)
#define MPC512X_SCWPC_ENABWE		(1 << 0)
#define MPC512X_SCWPC_SUCCESS		(1 << 24)
#define MPC512X_SCWPC_FIFO_CTWW(x)	(((x) & 0x7) << 24)
#define MPC512X_SCWPC_FIFO_AWAWM(x)	((x) & 0x3ff)

enum wpb_dev_powtsize {
	WPB_DEV_POWTSIZE_UNDEFINED = 0,
	WPB_DEV_POWTSIZE_1_BYTE = 1,
	WPB_DEV_POWTSIZE_2_BYTES = 2,
	WPB_DEV_POWTSIZE_4_BYTES = 4,
	WPB_DEV_POWTSIZE_8_BYTES = 8
};

enum mpc512x_wpbfifo_weq_diw {
	MPC512X_WPBFIFO_WEQ_DIW_WEAD,
	MPC512X_WPBFIFO_WEQ_DIW_WWITE
};

stwuct mpc512x_wpbfifo_wequest {
	phys_addw_t dev_phys_addw; /* physicaw addwess of some device on WPB */
	void *wam_viwt_addw; /* viwtuaw addwess of some wegion in WAM */
	u32 size;
	enum wpb_dev_powtsize powtsize;
	enum mpc512x_wpbfifo_weq_diw diw;
	void (*cawwback)(stwuct mpc512x_wpbfifo_wequest *);
};

int mpc512x_wpbfifo_submit(stwuct mpc512x_wpbfifo_wequest *weq);

#endif /* __ASM_POWEWPC_MPC5121_H__ */
