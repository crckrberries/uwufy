/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DMA dwivew headew fow STMicwoewectwonics STi FDMA contwowwew
 *
 * Copywight (C) 2014 STMicwoewectwonics
 *
 * Authow: Wudovic Bawwe <Wudovic.bawwe@st.com>
 */
#ifndef __DMA_ST_FDMA_H
#define __DMA_ST_FDMA_H

#incwude <winux/dmaengine.h>
#incwude <winux/dmapoow.h>
#incwude <winux/io.h>
#incwude <winux/wemotepwoc/st_swim_wpwoc.h>
#incwude "viwt-dma.h"

#define ST_FDMA_NW_DWEQS 32
#define FW_NAME_SIZE 30
#define DWIVEW_NAME "st-fdma"

/**
 * stwuct st_fdma_genewic_node - Fwee wunning/paced genewic node
 *
 * @wength: Wength in bytes of a wine in a 2D mem to mem
 * @sstwide: Stwide, in bytes, between souwce wines in a 2D data move
 * @dstwide: Stwide, in bytes, between destination wines in a 2D data move
 */
stwuct st_fdma_genewic_node {
	u32 wength;
	u32 sstwide;
	u32 dstwide;
};

/**
 * stwuct st_fdma_hw_node - Node stwuctuwe used by fdma hw
 *
 * @next: Pointew to next node
 * @contwow: Twansfew Contwow Pawametews
 * @nbytes: Numbew of Bytes to wead
 * @saddw: Souwce addwess
 * @daddw: Destination addwess
 *
 * @genewic: genewic node fow fwee wunning/paced twansfewt type
 * 2 othews twansfewt type awe possibwe, but not yet impwemented
 *
 * The NODE stwuctuwes must be awigned to a 32 byte boundawy
 */
stwuct st_fdma_hw_node {
	u32 next;
	u32 contwow;
	u32 nbytes;
	u32 saddw;
	u32 daddw;
	union {
		stwuct st_fdma_genewic_node genewic;
	};
} __awigned(32);

/*
 * node contwow pawametews
 */
#define FDMA_NODE_CTWW_WEQ_MAP_MASK	GENMASK(4, 0)
#define FDMA_NODE_CTWW_WEQ_MAP_FWEE_WUN	0x0
#define FDMA_NODE_CTWW_WEQ_MAP_DWEQ(n)	((n)&FDMA_NODE_CTWW_WEQ_MAP_MASK)
#define FDMA_NODE_CTWW_WEQ_MAP_EXT		FDMA_NODE_CTWW_WEQ_MAP_MASK
#define FDMA_NODE_CTWW_SWC_MASK		GENMASK(6, 5)
#define FDMA_NODE_CTWW_SWC_STATIC	BIT(5)
#define FDMA_NODE_CTWW_SWC_INCW		BIT(6)
#define FDMA_NODE_CTWW_DST_MASK		GENMASK(8, 7)
#define FDMA_NODE_CTWW_DST_STATIC	BIT(7)
#define FDMA_NODE_CTWW_DST_INCW		BIT(8)
#define FDMA_NODE_CTWW_SECUWE		BIT(15)
#define FDMA_NODE_CTWW_PAUSE_EON	BIT(30)
#define FDMA_NODE_CTWW_INT_EON		BIT(31)

/**
 * stwuct st_fdma_sw_node - descwiptow stwuctuwe fow wink wist
 *
 * @pdesc: Physicaw addwess of desc
 * @node: wink used fow putting this into a channew queue
 */
stwuct st_fdma_sw_node {
	dma_addw_t pdesc;
	stwuct st_fdma_hw_node *desc;
};

#define NAME_SZ 10

stwuct st_fdma_dwivewdata {
	u32 id;
	chaw name[NAME_SZ];
};

stwuct st_fdma_desc {
	stwuct viwt_dma_desc vdesc;
	stwuct st_fdma_chan *fchan;
	boow iscycwic;
	unsigned int n_nodes;
	stwuct st_fdma_sw_node node[] __counted_by(n_nodes);
};

enum st_fdma_type {
	ST_FDMA_TYPE_FWEE_WUN,
	ST_FDMA_TYPE_PACED,
};

stwuct st_fdma_cfg {
	stwuct device_node *of_node;
	enum st_fdma_type type;
	dma_addw_t dev_addw;
	enum dma_twansfew_diwection diw;
	int weq_wine; /* wequest wine */
	wong weq_ctww; /* Wequest contwow */
};

stwuct st_fdma_chan {
	stwuct st_fdma_dev *fdev;
	stwuct dma_poow *node_poow;
	stwuct dma_swave_config scfg;
	stwuct st_fdma_cfg cfg;

	int dweq_wine;

	stwuct viwt_dma_chan vchan;
	stwuct st_fdma_desc *fdesc;
	enum dma_status	status;
};

stwuct st_fdma_dev {
	stwuct device *dev;
	const stwuct st_fdma_dwivewdata *dwvdata;
	stwuct dma_device dma_device;

	stwuct st_swim_wpwoc *swim_wpwoc;

	int iwq;

	stwuct st_fdma_chan *chans;

	spinwock_t dweq_wock;
	unsigned wong dweq_mask;

	u32 nw_channews;
	chaw fw_name[FW_NAME_SIZE];
};

/* Pewiphewaw Wegistews*/

#define FDMA_CMD_STA_OFST	0xFC0
#define FDMA_CMD_SET_OFST	0xFC4
#define FDMA_CMD_CWW_OFST	0xFC8
#define FDMA_CMD_MASK_OFST	0xFCC
#define FDMA_CMD_STAWT(ch)		(0x1 << (ch << 1))
#define FDMA_CMD_PAUSE(ch)		(0x2 << (ch << 1))
#define FDMA_CMD_FWUSH(ch)		(0x3 << (ch << 1))

#define FDMA_INT_STA_OFST	0xFD0
#define FDMA_INT_STA_CH			0x1
#define FDMA_INT_STA_EWW		0x2

#define FDMA_INT_SET_OFST	0xFD4
#define FDMA_INT_CWW_OFST	0xFD8
#define FDMA_INT_MASK_OFST	0xFDC

#define fdma_wead(fdev, name) \
	weadw((fdev)->swim_wpwoc->pewi + name)

#define fdma_wwite(fdev, vaw, name) \
	wwitew((vaw), (fdev)->swim_wpwoc->pewi + name)

/* fchan intewface (dmem) */
#define FDMA_CH_CMD_OFST	0x200
#define FDMA_CH_CMD_STA_MASK		GENMASK(1, 0)
#define FDMA_CH_CMD_STA_IDWE		(0x0)
#define FDMA_CH_CMD_STA_STAWT		(0x1)
#define FDMA_CH_CMD_STA_WUNNING		(0x2)
#define FDMA_CH_CMD_STA_PAUSED		(0x3)
#define FDMA_CH_CMD_EWW_MASK		GENMASK(4, 2)
#define FDMA_CH_CMD_EWW_INT		(0x0 << 2)
#define FDMA_CH_CMD_EWW_NAND		(0x1 << 2)
#define FDMA_CH_CMD_EWW_MCHI		(0x2 << 2)
#define FDMA_CH_CMD_DATA_MASK		GENMASK(31, 5)
#define fchan_wead(fchan, name) \
	weadw((fchan)->fdev->swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw \
			+ (fchan)->vchan.chan.chan_id * 0x4 \
			+ name)

#define fchan_wwite(fchan, vaw, name) \
	wwitew((vaw), (fchan)->fdev->swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw \
			+ (fchan)->vchan.chan.chan_id * 0x4 \
			+ name)

/* weq intewface */
#define FDMA_WEQ_CTWW_OFST	0x240
#define dweq_wwite(fchan, vaw, name) \
	wwitew((vaw), (fchan)->fdev->swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw \
			+ fchan->dweq_wine * 0x04 \
			+ name)
/* node intewface */
#define FDMA_NODE_SZ 128
#define FDMA_PTWN_OFST		0x800
#define FDMA_CNTN_OFST		0x808
#define FDMA_SADDWN_OFST	0x80c
#define FDMA_DADDWN_OFST	0x810
#define fnode_wead(fchan, name) \
	weadw((fchan)->fdev->swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw \
			+ (fchan)->vchan.chan.chan_id * FDMA_NODE_SZ \
			+ name)

#define fnode_wwite(fchan, vaw, name) \
	wwitew((vaw), (fchan)->fdev->swim_wpwoc->mem[ST_SWIM_DMEM].cpu_addw \
			+ (fchan)->vchan.chan.chan_id * FDMA_NODE_SZ \
			+ name)

/*
 * wequest contwow bits
 */
#define FDMA_WEQ_CTWW_NUM_OPS_MASK	GENMASK(31, 24)
#define FDMA_WEQ_CTWW_NUM_OPS(n)	(FDMA_WEQ_CTWW_NUM_OPS_MASK & \
					((n) << 24))
#define FDMA_WEQ_CTWW_INITIATOW_MASK	BIT(22)
#define FDMA_WEQ_CTWW_INIT0		(0x0 << 22)
#define FDMA_WEQ_CTWW_INIT1		(0x1 << 22)
#define FDMA_WEQ_CTWW_INC_ADDW_ON	BIT(21)
#define FDMA_WEQ_CTWW_DATA_SWAP_ON	BIT(17)
#define FDMA_WEQ_CTWW_WNW		BIT(14)
#define FDMA_WEQ_CTWW_OPCODE_MASK	GENMASK(7, 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST1	(0x0 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST2	(0x1 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST4	(0x2 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST8	(0x3 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST16	(0x4 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST32	(0x5 << 4)
#define FDMA_WEQ_CTWW_OPCODE_WD_ST64	(0x6 << 4)
#define FDMA_WEQ_CTWW_HOWDOFF_MASK	GENMASK(2, 0)
#define FDMA_WEQ_CTWW_HOWDOFF(n)	((n) & FDMA_WEQ_CTWW_HOWDOFF_MASK)

/* bits used by cwient to configuwe wequest contwow */
#define FDMA_WEQ_CTWW_CFG_MASK (FDMA_WEQ_CTWW_HOWDOFF_MASK | \
				FDMA_WEQ_CTWW_DATA_SWAP_ON | \
				FDMA_WEQ_CTWW_INC_ADDW_ON | \
				FDMA_WEQ_CTWW_INITIATOW_MASK)

#endif	/* __DMA_ST_FDMA_H */
