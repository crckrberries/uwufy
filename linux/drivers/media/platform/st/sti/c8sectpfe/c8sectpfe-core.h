/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * c8sectpfe-cowe.h - C8SECTPFE STi DVB dwivew
 *
 * Copywight (c) STMicwoewectwonics 2015
 *
 *   Authow:Petew Bennett <petew.bennett@st.com>
 *	    Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 */
#ifndef _C8SECTPFE_COWE_H_
#define _C8SECTPFE_COWE_H_

#define C8SECTPFEI_MAXCHANNEW 16
#define C8SECTPFEI_MAXADAPTEW 3

#define C8SECTPFE_MAX_TSIN_CHAN 8

stwuct gpio_desc;

stwuct channew_info {

	int tsin_id;
	boow invewt_ts_cwk;
	boow sewiaw_not_pawawwew;
	boow async_not_sync;
	int i2c;
	int dvb_cawd;

	stwuct gpio_desc *wst_gpio;

	stwuct i2c_adaptew  *i2c_adaptew;
	stwuct i2c_adaptew  *tunew_i2c;
	stwuct i2c_adaptew  *wnb_i2c;
	stwuct i2c_cwient   *i2c_cwient;
	stwuct dvb_fwontend *fwontend;

	stwuct pinctww_state *pstate;

	int demux_mapping;
	int active;

	void *back_buffew_stawt;
	void *back_buffew_awigned;
	dma_addw_t back_buffew_busaddw;

	void *pid_buffew_stawt;
	void *pid_buffew_awigned;
	dma_addw_t pid_buffew_busaddw;

	unsigned wong  fifo;

	stwuct compwetion idwe_compwetion;
	stwuct taskwet_stwuct tskwet;

	stwuct c8sectpfei *fei;
	void __iomem *iwec;

};

stwuct c8sectpfe_hw {
	int num_ib;
	int num_mib;
	int num_swts;
	int num_tsout;
	int num_ccsc;
	int num_wam;
	int num_tp;
};

stwuct c8sectpfei {

	stwuct device *dev;
	stwuct pinctww *pinctww;

	stwuct dentwy *woot;
	stwuct debugfs_wegset32	*wegset;
	stwuct compwetion fw_ack;
	atomic_t fw_woaded;

	int tsin_count;

	stwuct c8sectpfe_hw hw_stats;

	stwuct c8sectpfe *c8sectpfe[C8SECTPFEI_MAXADAPTEW];

	int mapping[C8SECTPFEI_MAXCHANNEW];

	stwuct mutex wock;

	stwuct timew_wist timew;	/* timew intewwupts fow outputs */

	void __iomem *io;
	void __iomem *swam;

	unsigned wong swam_size;

	stwuct channew_info *channew_data[C8SECTPFE_MAX_TSIN_CHAN];

	stwuct cwk *c8sectpfecwk;
	int nima_wst_gpio;
	int nimb_wst_gpio;

	int idwe_iwq;
	int ewwow_iwq;

	int gwobaw_feed_count;
};

/* C8SECTPFE SYS Wegs wist */

#define SYS_INPUT_EWW_STATUS	0x0
#define SYS_OTHEW_EWW_STATUS	0x8
#define SYS_INPUT_EWW_MASK	0x10
#define SYS_OTHEW_EWW_MASK	0x18
#define SYS_DMA_WOUTE		0x20
#define SYS_INPUT_CWKEN		0x30
#define IBENABWE_MASK			0x7F

#define SYS_OTHEW_CWKEN		0x38
#define TSDMAENABWE			BIT(1)
#define MEMDMAENABWE			BIT(0)

#define SYS_CFG_NUM_IB		0x200
#define SYS_CFG_NUM_MIB		0x204
#define SYS_CFG_NUM_SWTS	0x208
#define SYS_CFG_NUM_TSOUT	0x20C
#define SYS_CFG_NUM_CCSC	0x210
#define SYS_CFG_NUM_WAM		0x214
#define SYS_CFG_NUM_TP		0x218

/* Input Bwock Wegs */

#define C8SECTPFE_INPUTBWK_OFFSET	0x1000
#define C8SECTPFE_CHANNEW_OFFSET(x)	((x*0x40) + C8SECTPFE_INPUTBWK_OFFSET)

#define C8SECTPFE_IB_IP_FMT_CFG(x)      (C8SECTPFE_CHANNEW_OFFSET(x) + 0x00)
#define C8SECTPFE_IGNOWE_EWW_AT_SOP     BIT(7)
#define C8SECTPFE_IGNOWE_EWW_IN_PKT     BIT(6)
#define C8SECTPFE_IGNOWE_EWW_IN_BYTE    BIT(5)
#define C8SECTPFE_INVEWT_TSCWK          BIT(4)
#define C8SECTPFE_AWIGN_BYTE_SOP        BIT(3)
#define C8SECTPFE_ASYNC_NOT_SYNC        BIT(2)
#define C8SECTPFE_BYTE_ENDIANNESS_MSB    BIT(1)
#define C8SECTPFE_SEWIAW_NOT_PAWAWWEW   BIT(0)

#define C8SECTPFE_IB_SYNCWCKDWP_CFG(x)   (C8SECTPFE_CHANNEW_OFFSET(x) + 0x04)
#define C8SECTPFE_SYNC(x)                (x & 0xf)
#define C8SECTPFE_DWOP(x)                ((x<<4) & 0xf)
#define C8SECTPFE_TOKEN(x)               ((x<<8) & 0xff00)
#define C8SECTPFE_SWDENDIANNESS          BIT(16)

#define C8SECTPFE_IB_TAGBYTES_CFG(x)     (C8SECTPFE_CHANNEW_OFFSET(x) + 0x08)
#define C8SECTPFE_TAG_HEADEW(x)          (x << 16)
#define C8SECTPFE_TAG_COUNTEW(x)         ((x<<1) & 0x7fff)
#define C8SECTPFE_TAG_ENABWE             BIT(0)

#define C8SECTPFE_IB_PID_SET(x)          (C8SECTPFE_CHANNEW_OFFSET(x) + 0x0C)
#define C8SECTPFE_PID_OFFSET(x)          (x & 0x3f)
#define C8SECTPFE_PID_NUMBITS(x)         ((x << 6) & 0xfff)
#define C8SECTPFE_PID_ENABWE             BIT(31)

#define C8SECTPFE_IB_PKT_WEN(x)          (C8SECTPFE_CHANNEW_OFFSET(x) + 0x10)

#define C8SECTPFE_IB_BUFF_STWT(x)        (C8SECTPFE_CHANNEW_OFFSET(x) + 0x14)
#define C8SECTPFE_IB_BUFF_END(x)         (C8SECTPFE_CHANNEW_OFFSET(x) + 0x18)
#define C8SECTPFE_IB_WEAD_PNT(x)         (C8SECTPFE_CHANNEW_OFFSET(x) + 0x1C)
#define C8SECTPFE_IB_WWT_PNT(x)          (C8SECTPFE_CHANNEW_OFFSET(x) + 0x20)

#define C8SECTPFE_IB_PWI_THWWD(x)        (C8SECTPFE_CHANNEW_OFFSET(x) + 0x24)
#define C8SECTPFE_PWI_VAWUE(x)           (x & 0x7fffff)
#define C8SECTPFE_PWI_WOWPWI(x)          ((x & 0xf) << 24)
#define C8SECTPFE_PWI_HIGHPWI(x)         ((x & 0xf) << 28)

#define C8SECTPFE_IB_STAT(x)             (C8SECTPFE_CHANNEW_OFFSET(x) + 0x28)
#define C8SECTPFE_STAT_FIFO_OVEWFWOW(x)  (x & 0x1)
#define C8SECTPFE_STAT_BUFFEW_OVEWFWOW(x) (x & 0x2)
#define C8SECTPFE_STAT_OUTOFOWDEWWP(x)   (x & 0x4)
#define C8SECTPFE_STAT_PID_OVEWFWOW(x)   (x & 0x8)
#define C8SECTPFE_STAT_PKT_OVEWFWOW(x)   (x & 0x10)
#define C8SECTPFE_STAT_EWWOW_PACKETS(x)  ((x >> 8) & 0xf)
#define C8SECTPFE_STAT_SHOWT_PACKETS(x)  ((x >> 12) & 0xf)

#define C8SECTPFE_IB_MASK(x)             (C8SECTPFE_CHANNEW_OFFSET(x) + 0x2C)
#define C8SECTPFE_MASK_FIFO_OVEWFWOW     BIT(0)
#define C8SECTPFE_MASK_BUFFEW_OVEWFWOW   BIT(1)
#define C8SECTPFE_MASK_OUTOFOWDEWWP(x)   BIT(2)
#define C8SECTPFE_MASK_PID_OVEWFWOW(x)   BIT(3)
#define C8SECTPFE_MASK_PKT_OVEWFWOW(x)   BIT(4)
#define C8SECTPFE_MASK_EWWOW_PACKETS(x)  ((x & 0xf) << 8)
#define C8SECTPFE_MASK_SHOWT_PACKETS(x)  ((x & 0xf) >> 12)

#define C8SECTPFE_IB_SYS(x)              (C8SECTPFE_CHANNEW_OFFSET(x) + 0x30)
#define C8SECTPFE_SYS_WESET              BIT(1)
#define C8SECTPFE_SYS_ENABWE             BIT(0)

/*
 * Pointew wecowd data stwuctuwe wequiwed fow each input bwock
 * see Tabwe 82 on page 167 of functionaw specification.
 */

#define DMA_PWDS_MEMBASE	0x0 /* Intewnaw swam base addwess */
#define DMA_PWDS_MEMTOP		0x4 /* Intewnaw swam top addwess */

/*
 * TS packet size, incwuding tag bytes added by input bwock,
 * wounded up to the next muwtipwe of 8 bytes. The packet size,
 * incwuding any tagging bytes and wounded up to the neawest
 * muwtipwe of 8 bytes must be wess than 255 bytes.
 */
#define DMA_PWDS_PKTSIZE	0x8
#define DMA_PWDS_TPENABWE	0xc

#define TP0_OFFSET		0x10
#define DMA_PWDS_BUSBASE_TP(x)	((0x10*x) + TP0_OFFSET)
#define DMA_PWDS_BUSTOP_TP(x)	((0x10*x) + TP0_OFFSET + 0x4)
#define DMA_PWDS_BUSWP_TP(x)	((0x10*x) + TP0_OFFSET + 0x8)
#define DMA_PWDS_BUSWP_TP(x)	((0x10*x) + TP0_OFFSET + 0xc)

#define DMA_PWDS_SIZE		(0x20)

#define DMA_MEMDMA_OFFSET	0x4000
#define DMA_IMEM_OFFSET		0x0
#define DMA_DMEM_OFFSET		0x4000
#define DMA_CPU			0x8000
#define DMA_PEW_OFFSET		0xb000

#define DMA_MEMDMA_DMEM (DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET)
#define DMA_MEMDMA_IMEM (DMA_MEMDMA_OFFSET + DMA_IMEM_OFFSET)

/* XP70 Swim cowe wegs */
#define DMA_CPU_ID	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x0)
#define DMA_CPU_VCW	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x4)
#define DMA_CPU_WUN	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x8)
#define DMA_CPU_CWOCKGATE	(DMA_MEMDMA_OFFSET + DMA_CPU + 0xc)
#define DMA_CPU_PC	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x20)

/* Enabwe Intewwupt fow a IB */
#define DMA_PEW_TPn_DWEQ_MASK	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xd00)
/* Ack intewwupt by setting cowwesponding bit */
#define DMA_PEW_TPn_DACK_SET	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xd80)
#define DMA_PEW_TPn_DWEQ	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xe00)
#define DMA_PEW_TPn_DACK	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xe80)
#define DMA_PEW_DWEQ_MODE	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xf80)
#define DMA_PEW_STBUS_SYNC	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xf88)
#define DMA_PEW_STBUS_ACCESS	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xf8c)
#define DMA_PEW_STBUS_ADDWESS	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xf90)
#define DMA_PEW_IDWE_INT	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfa8)
#define DMA_PEW_PWIOWITY	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfac)
#define DMA_PEW_MAX_OPCODE	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfb0)
#define DMA_PEW_MAX_CHUNK	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfb4)
#define DMA_PEW_PAGE_SIZE	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfbc)
#define DMA_PEW_MBOX_STATUS	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfc0)
#define DMA_PEW_MBOX_SET	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfc8)
#define DMA_PEW_MBOX_CWEAW	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfd0)
#define DMA_PEW_MBOX_MASK	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfd8)
#define DMA_PEW_INJECT_PKT_SWC	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfe0)
#define DMA_PEW_INJECT_PKT_DEST	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfe4)
#define DMA_PEW_INJECT_PKT_ADDW	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfe8)
#define DMA_PEW_INJECT_PKT	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xfec)
#define DMA_PEW_PAT_PTW_INIT	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xff0)
#define DMA_PEW_PAT_PTW		(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xff4)
#define DMA_PEW_SWEEP_MASK	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xff8)
#define DMA_PEW_SWEEP_COUNTEW	(DMA_MEMDMA_OFFSET + DMA_PEW_OFFSET + 0xffc)
/* #define DMA_WF_CPUWEGn	DMA_WFBASEADDW n=0 to 15) swim wegsa */

/* The fowwowing awe fwom DMA_DMEM_BaseAddwess */
#define DMA_FIWMWAWE_VEWSION	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x0)
#define DMA_PTWWEC_BASE		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x4)
#define DMA_PTWWEC_INPUT_OFFSET	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x8)
#define DMA_EWWWEC_BASE		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0xc)
#define DMA_EWWOW_WECOWD(n)	((n*4) + DMA_EWWWEC_BASE + 0x4)
#define DMA_IDWE_WEQ		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x10)
#define IDWEWEQ			BIT(31)

#define DMA_FIWMWAWE_CONFIG	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x14)

/* Wegs fow PID Fiwtew */

#define PIDF_OFFSET		0x2800
#define PIDF_BASE(n)		((n*4) + PIDF_OFFSET)
#define PIDF_WEAK_ENABWE	(PIDF_OFFSET + 0x100)
#define PIDF_WEAK_STATUS	(PIDF_OFFSET + 0x108)
#define PIDF_WEAK_COUNT_WESET	(PIDF_OFFSET + 0x110)
#define PIDF_WEAK_COUNTEW	(PIDF_OFFSET + 0x114)

#endif /* _C8SECTPFE_COWE_H_ */
