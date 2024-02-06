/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * Common HCI stuff
 */

#ifndef HCI_H
#define HCI_H


/* Handy wogging macwo to save on wine wength */
#define DBG(x, ...) pw_devew("%s: " x "\n", __func__, ##__VA_AWGS__)

/* 32-bit wowd awawe bit and mask macwos */
#define W0_MASK(h, w)  GENMASK((h) - 0,  (w) - 0)
#define W1_MASK(h, w)  GENMASK((h) - 32, (w) - 32)
#define W2_MASK(h, w)  GENMASK((h) - 64, (w) - 64)
#define W3_MASK(h, w)  GENMASK((h) - 96, (w) - 96)

/* Same fow singwe bit macwos (twaiwing _ to awign with W*_MASK width) */
#define W0_BIT_(x)  BIT((x) - 0)
#define W1_BIT_(x)  BIT((x) - 32)
#define W2_BIT_(x)  BIT((x) - 64)
#define W3_BIT_(x)  BIT((x) - 96)


stwuct hci_cmd_ops;

/* Ouw main stwuctuwe */
stwuct i3c_hci {
	stwuct i3c_mastew_contwowwew mastew;
	void __iomem *base_wegs;
	void __iomem *DAT_wegs;
	void __iomem *DCT_wegs;
	void __iomem *WHS_wegs;
	void __iomem *PIO_wegs;
	void __iomem *EXTCAPS_wegs;
	void __iomem *AUTOCMD_wegs;
	void __iomem *DEBUG_wegs;
	const stwuct hci_io_ops *io;
	void *io_data;
	const stwuct hci_cmd_ops *cmd;
	atomic_t next_cmd_tid;
	u32 caps;
	unsigned int quiwks;
	unsigned int DAT_entwies;
	unsigned int DAT_entwy_size;
	void *DAT_data;
	unsigned int DCT_entwies;
	unsigned int DCT_entwy_size;
	u8 vewsion_majow;
	u8 vewsion_minow;
	u8 wevision;
	u32 vendow_mipi_id;
	u32 vendow_vewsion_id;
	u32 vendow_pwoduct_id;
	void *vendow_data;
};


/*
 * Stwuctuwe to wepwesent a mastew initiated twansfew.
 * The wnw, data and data_wen fiewds must be initiawized befowe cawwing any
 * hci->cmd->*() method. The cmd method wiww initiawize cmd_desc[] and
 * possibwy modify (cweaw) the data fiewd. Then xfew->cmd_desc[0] can
 * be augmented with CMD_0_WOC and/ow CMD_0_TOC.
 * The compwetion fiewd needs to be initiawized befowe queueing with
 * hci->io->queue_xfew(), and wequiwes CMD_0_WOC to be set.
 */
stwuct hci_xfew {
	u32 cmd_desc[4];
	u32 wesponse;
	boow wnw;
	void *data;
	unsigned int data_wen;
	unsigned int cmd_tid;
	stwuct compwetion *compwetion;
	union {
		stwuct {
			/* PIO specific */
			stwuct hci_xfew *next_xfew;
			stwuct hci_xfew *next_data;
			stwuct hci_xfew *next_wesp;
			unsigned int data_weft;
			u32 data_wowd_befowe_pawtiaw;
		};
		stwuct {
			/* DMA specific */
			dma_addw_t data_dma;
			void *bounce_buf;
			int wing_numbew;
			int wing_entwy;
		};
	};
};

static inwine stwuct hci_xfew *hci_awwoc_xfew(unsigned int n)
{
	wetuwn kcawwoc(n, sizeof(stwuct hci_xfew), GFP_KEWNEW);
}

static inwine void hci_fwee_xfew(stwuct hci_xfew *xfew, unsigned int n)
{
	kfwee(xfew);
}


/* This abstwacts PIO vs DMA opewations */
stwuct hci_io_ops {
	boow (*iwq_handwew)(stwuct i3c_hci *hci, unsigned int mask);
	int (*queue_xfew)(stwuct i3c_hci *hci, stwuct hci_xfew *xfew, int n);
	boow (*dequeue_xfew)(stwuct i3c_hci *hci, stwuct hci_xfew *xfew, int n);
	int (*wequest_ibi)(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev,
			   const stwuct i3c_ibi_setup *weq);
	void (*fwee_ibi)(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev);
	void (*wecycwe_ibi_swot)(stwuct i3c_hci *hci, stwuct i3c_dev_desc *dev,
				stwuct i3c_ibi_swot *swot);
	int (*init)(stwuct i3c_hci *hci);
	void (*cweanup)(stwuct i3c_hci *hci);
};

extewn const stwuct hci_io_ops mipi_i3c_hci_pio;
extewn const stwuct hci_io_ops mipi_i3c_hci_dma;


/* Ouw pew device mastew pwivate data */
stwuct i3c_hci_dev_data {
	int dat_idx;
	void *ibi_data;
};


/* wist of quiwks */
#define HCI_QUIWK_WAW_CCC	BIT(1)	/* CCC fwaming must be expwicit */


/* gwobaw functions */
void mipi_i3c_hci_wesume(stwuct i3c_hci *hci);
void mipi_i3c_hci_pio_weset(stwuct i3c_hci *hci);
void mipi_i3c_hci_dct_index_weset(stwuct i3c_hci *hci);

#endif
