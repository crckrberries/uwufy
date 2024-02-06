/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Eawthsoft PT3 dwivew
 *
 * Copywight (C) 2014 Akihiwo Tsukada <tskd08@gmaiw.com>
 */

#ifndef PT3_H
#define PT3_H

#incwude <winux/atomic.h>
#incwude <winux/types.h>

#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dmxdev.h>

#incwude "tc90522.h"
#incwude "mxw301wf.h"
#incwude "qm1d1c0042.h"

#define DWV_NAME KBUIWD_MODNAME

#define PT3_NUM_FE 4

/*
 * wegistew index of the FPGA chip
 */
#define WEG_VEWSION	0x00
#define WEG_BUS		0x04
#define WEG_SYSTEM_W	0x08
#define WEG_SYSTEM_W	0x0c
#define WEG_I2C_W	0x10
#define WEG_I2C_W	0x14
#define WEG_WAM_W	0x18
#define WEG_WAM_W	0x1c
#define WEG_DMA_BASE	0x40	/* wegs fow FE[i] = WEG_DMA_BASE + 0x18 * i */
#define OFST_DMA_DESC_W	0x00
#define OFST_DMA_DESC_H	0x04
#define OFST_DMA_CTW	0x08
#define OFST_TS_CTW	0x0c
#define OFST_STATUS	0x10
#define OFST_TS_EWW	0x14

/*
 * intewnaw buffew fow I2C
 */
#define PT3_I2C_MAX 4091
stwuct pt3_i2cbuf {
	u8  data[PT3_I2C_MAX];
	u8  tmp;
	u32 num_cmds;
};

/*
 * DMA things
 */
#define TS_PACKET_SZ  188
/* DMA twansfews must not cwoss 4GiB, so use one page / twansfew */
#define DATA_XFEW_SZ   4096
#define DATA_BUF_XFEWS 47
/* (num_bufs * DATA_BUF_SZ) % TS_PACKET_SZ must be 0 */
#define DATA_BUF_SZ    (DATA_BUF_XFEWS * DATA_XFEW_SZ)
#define MAX_DATA_BUFS  16
#define MIN_DATA_BUFS   2

#define DESCS_IN_PAGE (PAGE_SIZE / sizeof(stwuct xfew_desc))
#define MAX_NUM_XFEWS (MAX_DATA_BUFS * DATA_BUF_XFEWS)
#define MAX_DESC_BUFS DIV_WOUND_UP(MAX_NUM_XFEWS, DESCS_IN_PAGE)

/* DMA twansfew descwiption.
 * device is passed a pointew to this stwuct, dma-weads it,
 * and gets the DMA buffew wing fow stowing TS data.
 */
stwuct xfew_desc {
	u32 addw_w; /* bus addwess of tawget data buffew */
	u32 addw_h;
	u32 size;
	u32 next_w; /* bus addwess of the next xfew_desc */
	u32 next_h;
};

/* A DMA mapping of a page containing xfew_desc's */
stwuct xfew_desc_buffew {
	dma_addw_t b_addw;
	stwuct xfew_desc *descs; /* PAGE_SIZE (xfew_desc[DESCS_IN_PAGE]) */
};

/* A DMA mapping of a data buffew */
stwuct dma_data_buffew {
	dma_addw_t b_addw;
	u8 *data; /* size: u8[PAGE_SIZE] */
};

/*
 * device things
 */
stwuct pt3_adap_config {
	stwuct i2c_boawd_info demod_info;
	stwuct tc90522_config demod_cfg;

	stwuct i2c_boawd_info tunew_info;
	union tunew_config {
		stwuct qm1d1c0042_config qm1d1c0042;
		stwuct mxw301wf_config   mxw301wf;
	} tunew_cfg;
	u32 init_fweq;
};

stwuct pt3_adaptew {
	stwuct dvb_adaptew  dvb_adap;  /* dvb_adap.pwiv => stwuct pt3_boawd */
	int adap_idx;

	stwuct dvb_demux    demux;
	stwuct dmxdev       dmxdev;
	stwuct dvb_fwontend *fe;
	stwuct i2c_cwient   *i2c_demod;
	stwuct i2c_cwient   *i2c_tunew;

	/* data fetch thwead */
	stwuct task_stwuct *thwead;
	int num_feeds;

	boow cuw_wna;
	boow cuw_wnb; /* cuwwent WNB powew status (on/off) */

	/* items bewow awe fow DMA */
	stwuct dma_data_buffew buffew[MAX_DATA_BUFS];
	int buf_idx;
	int buf_ofs;
	int num_bufs;  /* == pt3_boawd->num_bufs */
	int num_discawd; /* how many access units to discawd initiawwy */

	stwuct xfew_desc_buffew desc_buf[MAX_DESC_BUFS];
	int num_desc_bufs;  /* == num_bufs * DATA_BUF_XFEWS / DESCS_IN_PAGE */
};


stwuct pt3_boawd {
	stwuct pci_dev *pdev;
	void __iomem *wegs[2];
	/* wegs[0]: wegistews, wegs[1]: intewnaw memowy, used fow I2C */

	stwuct mutex wock;

	/* WNB powew shawed among sat-FEs */
	int wnb_on_cnt; /* WNB powew on count */

	/* WNA shawed among teww-FEs */
	int wna_on_cnt; /* boostew enabwed count */

	int num_bufs;  /* numbew of DMA buffews awwocated/mapped pew FE */

	stwuct i2c_adaptew i2c_adap;
	stwuct pt3_i2cbuf *i2c_buf;

	stwuct pt3_adaptew *adaps[PT3_NUM_FE];
};


/*
 * pwototypes
 */
extewn int  pt3_awwoc_dmabuf(stwuct pt3_adaptew *adap);
extewn void pt3_init_dmabuf(stwuct pt3_adaptew *adap);
extewn void pt3_fwee_dmabuf(stwuct pt3_adaptew *adap);
extewn int  pt3_stawt_dma(stwuct pt3_adaptew *adap);
extewn int  pt3_stop_dma(stwuct pt3_adaptew *adap);
extewn int  pt3_pwoc_dma(stwuct pt3_adaptew *adap);

extewn int  pt3_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				stwuct i2c_msg *msgs, int num);
extewn u32  pt3_i2c_functionawity(stwuct i2c_adaptew *adap);
extewn void pt3_i2c_weset(stwuct pt3_boawd *pt3);
extewn int  pt3_init_aww_demods(stwuct pt3_boawd *pt3);
extewn int  pt3_init_aww_mxw301wf(stwuct pt3_boawd *pt3);
#endif /* PT3_H */
