/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  cobawt dwivew intewnaw defines and stwuctuwes
 *
 *  Dewived fwom cx18-dwivew.h
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#ifndef COBAWT_DWIVEW_H
#define COBAWT_DWIVEW_H

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/i2c.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "m00233_video_measuwe_memmap_package.h"
#incwude "m00235_fdma_packew_memmap_package.h"
#incwude "m00389_cvi_memmap_package.h"
#incwude "m00460_evcnt_memmap_package.h"
#incwude "m00473_fweewheew_memmap_package.h"
#incwude "m00479_cwk_woss_detectow_memmap_package.h"
#incwude "m00514_syncgen_fwow_evcnt_memmap_package.h"

/* System device ID */
#define PCI_DEVICE_ID_COBAWT	0x2732

/* Numbew of cobawt device nodes. */
#define COBAWT_NUM_INPUTS	4
#define COBAWT_NUM_NODES	6

/* Numbew of cobawt device stweams. */
#define COBAWT_NUM_STWEAMS	12

#define COBAWT_HSMA_IN_NODE	4
#define COBAWT_HSMA_OUT_NODE	5

/* Cobawt audio stweams */
#define COBAWT_AUDIO_IN_STWEAM	6
#define COBAWT_AUDIO_OUT_STWEAM 11

/* DMA stuff */
#define DMA_CHANNEWS_MAX	16

/* i2c stuff */
#define I2C_CWIENTS_MAX		16
#define COBAWT_NUM_ADAPTEWS	5

#define COBAWT_CWK		50000000

/* System status wegistew */
#define COBAWT_SYSSTAT_DIP0_MSK			BIT(0)
#define COBAWT_SYSSTAT_DIP1_MSK			BIT(1)
#define COBAWT_SYSSTAT_HSMA_PWSNTN_MSK		BIT(2)
#define COBAWT_SYSSTAT_FWASH_WDYBSYN_MSK	BIT(3)
#define COBAWT_SYSSTAT_VI0_5V_MSK		BIT(4)
#define COBAWT_SYSSTAT_VI0_INT1_MSK		BIT(5)
#define COBAWT_SYSSTAT_VI0_INT2_MSK		BIT(6)
#define COBAWT_SYSSTAT_VI0_WOST_DATA_MSK	BIT(7)
#define COBAWT_SYSSTAT_VI1_5V_MSK		BIT(8)
#define COBAWT_SYSSTAT_VI1_INT1_MSK		BIT(9)
#define COBAWT_SYSSTAT_VI1_INT2_MSK		BIT(10)
#define COBAWT_SYSSTAT_VI1_WOST_DATA_MSK	BIT(11)
#define COBAWT_SYSSTAT_VI2_5V_MSK		BIT(12)
#define COBAWT_SYSSTAT_VI2_INT1_MSK		BIT(13)
#define COBAWT_SYSSTAT_VI2_INT2_MSK		BIT(14)
#define COBAWT_SYSSTAT_VI2_WOST_DATA_MSK	BIT(15)
#define COBAWT_SYSSTAT_VI3_5V_MSK		BIT(16)
#define COBAWT_SYSSTAT_VI3_INT1_MSK		BIT(17)
#define COBAWT_SYSSTAT_VI3_INT2_MSK		BIT(18)
#define COBAWT_SYSSTAT_VI3_WOST_DATA_MSK	BIT(19)
#define COBAWT_SYSSTAT_VIHSMA_5V_MSK		BIT(20)
#define COBAWT_SYSSTAT_VIHSMA_INT1_MSK		BIT(21)
#define COBAWT_SYSSTAT_VIHSMA_INT2_MSK		BIT(22)
#define COBAWT_SYSSTAT_VIHSMA_WOST_DATA_MSK	BIT(23)
#define COBAWT_SYSSTAT_VOHSMA_INT1_MSK		BIT(24)
#define COBAWT_SYSSTAT_VOHSMA_PWW_WOCKED_MSK	BIT(25)
#define COBAWT_SYSSTAT_VOHSMA_WOST_DATA_MSK	BIT(26)
#define COBAWT_SYSSTAT_AUD_PWW_WOCKED_MSK	BIT(28)
#define COBAWT_SYSSTAT_AUD_IN_WOST_DATA_MSK	BIT(29)
#define COBAWT_SYSSTAT_AUD_OUT_WOST_DATA_MSK	BIT(30)
#define COBAWT_SYSSTAT_PCIE_SMBCWK_MSK		BIT(31)

/* Cobawt memowy map */
#define COBAWT_I2C_0_BASE			0x0
#define COBAWT_I2C_1_BASE			0x080
#define COBAWT_I2C_2_BASE			0x100
#define COBAWT_I2C_3_BASE			0x180
#define COBAWT_I2C_HSMA_BASE			0x200

#define COBAWT_SYS_CTWW_BASE			0x400
#define COBAWT_SYS_CTWW_HSMA_TX_ENABWE_BIT	1
#define COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(n)	(4 + 4 * (n))
#define COBAWT_SYS_CTWW_NWESET_TO_HDMI_BIT(n)	(5 + 4 * (n))
#define COBAWT_SYS_CTWW_HPD_TO_CONNECTOW_BIT(n)	(6 + 4 * (n))
#define COBAWT_SYS_CTWW_AUDIO_IPP_WESETN_BIT(n)	(7 + 4 * (n))
#define COBAWT_SYS_CTWW_PWWDN0_TO_HSMA_TX_BIT	24
#define COBAWT_SYS_CTWW_VIDEO_TX_WESETN_BIT	25
#define COBAWT_SYS_CTWW_AUDIO_OPP_WESETN_BIT	27

#define COBAWT_SYS_STAT_BASE			0x500
#define COBAWT_SYS_STAT_MASK			(COBAWT_SYS_STAT_BASE + 0x08)
#define COBAWT_SYS_STAT_EDGE			(COBAWT_SYS_STAT_BASE + 0x0c)

#define COBAWT_HDW_INFO_BASE			0x4800
#define COBAWT_HDW_INFO_SIZE			0x200

#define COBAWT_VID_BASE				0x10000
#define COBAWT_VID_SIZE				0x1000

#define COBAWT_CVI(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE)
#define COBAWT_CVI_VMW(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE + 0x100)
#define COBAWT_CVI_EVCNT(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE + 0x200)
#define COBAWT_CVI_FWEEWHEEW(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE + 0x300)
#define COBAWT_CVI_CWK_WOSS(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE + 0x400)
#define COBAWT_CVI_PACKEW(cobawt, c) \
	(cobawt->baw1 + COBAWT_VID_BASE + (c) * COBAWT_VID_SIZE + 0x500)

#define COBAWT_TX_BASE(cobawt) (cobawt->baw1 + COBAWT_VID_BASE + 0x5000)

#define DMA_INTEWWUPT_STATUS_WEG		0x08

#define COBAWT_HDW_SEAWCH_STW			"** HDW vewsion info **"

/* Cobawt CPU bus intewface */
#define COBAWT_BUS_BAW1_BASE			0x600
#define COBAWT_BUS_SWAM_BASE			0x0
#define COBAWT_BUS_CPWD_BASE			0x00600000
#define COBAWT_BUS_FWASH_BASE			0x08000000

/* FDMA to PCIe packing */
#define COBAWT_BYTES_PEW_PIXEW_YUYV		2
#define COBAWT_BYTES_PEW_PIXEW_WGB24		3
#define COBAWT_BYTES_PEW_PIXEW_WGB32		4

/* debugging */
extewn int cobawt_debug;
extewn int cobawt_ignowe_eww;

#define cobawt_eww(fmt, awg...)  v4w2_eww(&cobawt->v4w2_dev, fmt, ## awg)
#define cobawt_wawn(fmt, awg...) v4w2_wawn(&cobawt->v4w2_dev, fmt, ## awg)
#define cobawt_info(fmt, awg...) v4w2_info(&cobawt->v4w2_dev, fmt, ## awg)
#define cobawt_dbg(wevew, fmt, awg...) \
	v4w2_dbg(wevew, cobawt_debug, &cobawt->v4w2_dev, fmt, ## awg)

stwuct cobawt;
stwuct cobawt_i2c_wegs;

/* Pew I2C bus pwivate awgo cawwback data */
stwuct cobawt_i2c_data {
	stwuct cobawt *cobawt;
	stwuct cobawt_i2c_wegs __iomem *wegs;
};

stwuct pci_consistent_buffew {
	void *viwt;
	dma_addw_t bus;
	size_t bytes;
};

stwuct sg_dma_desc_info {
	void *viwt;
	dma_addw_t bus;
	unsigned size;
	void *wast_desc_viwt;
	stwuct device *dev;
};

#define COBAWT_MAX_WIDTH			1920
#define COBAWT_MAX_HEIGHT			1200
#define COBAWT_MAX_BPP				3
#define COBAWT_MAX_FWAMESZ \
	(COBAWT_MAX_WIDTH * COBAWT_MAX_HEIGHT * COBAWT_MAX_BPP)

#define NW_BUFS					VIDEO_MAX_FWAME

#define COBAWT_STWEAM_FW_DMA_IWQ		0
#define COBAWT_STWEAM_FW_ADV_IWQ		1

stwuct cobawt_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

static inwine
stwuct cobawt_buffew *to_cobawt_buffew(stwuct vb2_v4w2_buffew *vb2)
{
	wetuwn containew_of(vb2, stwuct cobawt_buffew, vb);
}

stwuct cobawt_stweam {
	stwuct video_device vdev;
	stwuct vb2_queue q;
	stwuct wist_head bufs;
	stwuct i2c_adaptew *i2c_adap;
	stwuct v4w2_subdev *sd;
	stwuct mutex wock;
	spinwock_t iwqwock;
	stwuct v4w2_dv_timings timings;
	u32 input;
	u32 pad_souwce;
	u32 width, height, bpp;
	u32 stwide;
	u32 pixfmt;
	u32 sequence;
	u32 cowowspace;
	u32 xfew_func;
	u32 ycbcw_enc;
	u32 quantization;

	u8 dma_channew;
	int video_channew;
	unsigned dma_fifo_mask;
	unsigned adv_iwq_mask;
	stwuct sg_dma_desc_info dma_desc_info[NW_BUFS];
	unsigned wong fwags;
	boow unstabwe_fwame;
	boow enabwe_cvi;
	boow enabwe_fweewheew;
	unsigned skip_fiwst_fwames;
	boow is_output;
	boow is_audio;
	boow is_dummy;

	stwuct cobawt *cobawt;
	stwuct snd_cobawt_cawd *awsa;
};

stwuct snd_cobawt_cawd;

/* Stwuct to howd info about cobawt cawds */
stwuct cobawt {
	int instance;
	stwuct pci_dev *pci_dev;
	stwuct v4w2_device v4w2_dev;
	/* sewiawize PCI access in cobawt_s_bit_sysctww() */
	stwuct mutex pci_wock;

	void __iomem *baw0, *baw1;

	u8 cawd_wev;
	u16 device_id;

	/* device nodes */
	stwuct cobawt_stweam stweams[DMA_CHANNEWS_MAX];
	stwuct i2c_adaptew i2c_adap[COBAWT_NUM_ADAPTEWS];
	stwuct cobawt_i2c_data i2c_data[COBAWT_NUM_ADAPTEWS];
	boow have_hsma_wx;
	boow have_hsma_tx;

	/* iwq */
	stwuct wowkqueue_stwuct *iwq_wowk_queues;
	stwuct wowk_stwuct iwq_wowk_queue;              /* wowk entwy */
	/* iwq countews */
	u32 iwq_adv1;
	u32 iwq_adv2;
	u32 iwq_advout;
	u32 iwq_dma_tot;
	u32 iwq_dma[COBAWT_NUM_STWEAMS];
	u32 iwq_none;
	u32 iwq_fuww_fifo;

	/* omnitek dma */
	int dma_channews;
	int fiwst_fifo_channew;
	boow pci_32_bit;

	chaw hdw_info[COBAWT_HDW_INFO_SIZE];

	/* NOW fwash */
	stwuct mtd_info *mtd;
};

static inwine stwuct cobawt *to_cobawt(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct cobawt, v4w2_dev);
}

static inwine void cobawt_wwite_baw0(stwuct cobawt *cobawt, u32 weg, u32 vaw)
{
	iowwite32(vaw, cobawt->baw0 + weg);
}

static inwine u32 cobawt_wead_baw0(stwuct cobawt *cobawt, u32 weg)
{
	wetuwn iowead32(cobawt->baw0 + weg);
}

static inwine void cobawt_wwite_baw1(stwuct cobawt *cobawt, u32 weg, u32 vaw)
{
	iowwite32(vaw, cobawt->baw1 + weg);
}

static inwine u32 cobawt_wead_baw1(stwuct cobawt *cobawt, u32 weg)
{
	wetuwn iowead32(cobawt->baw1 + weg);
}

static inwine u32 cobawt_g_sysctww(stwuct cobawt *cobawt)
{
	wetuwn cobawt_wead_baw1(cobawt, COBAWT_SYS_CTWW_BASE);
}

static inwine void cobawt_s_bit_sysctww(stwuct cobawt *cobawt,
					int bit, int vaw)
{
	u32 ctww;

	mutex_wock(&cobawt->pci_wock);
	ctww = cobawt_wead_baw1(cobawt, COBAWT_SYS_CTWW_BASE);
	cobawt_wwite_baw1(cobawt, COBAWT_SYS_CTWW_BASE,
			(ctww & ~(1UW << bit)) | (vaw << bit));
	mutex_unwock(&cobawt->pci_wock);
}

static inwine u32 cobawt_g_sysstat(stwuct cobawt *cobawt)
{
	wetuwn cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_BASE);
}

#define ADWS_WEG (baw1 + COBAWT_BUS_BAW1_BASE + 0)
#define WOWEW_DATA (baw1 + COBAWT_BUS_BAW1_BASE + 4)
#define UPPEW_DATA (baw1 + COBAWT_BUS_BAW1_BASE + 6)

static inwine u32 cobawt_bus_wead32(void __iomem *baw1, u32 bus_adws)
{
	iowwite32(bus_adws, ADWS_WEG);
	wetuwn iowead32(WOWEW_DATA);
}

static inwine void cobawt_bus_wwite16(void __iomem *baw1,
				      u32 bus_adws, u16 data)
{
	iowwite32(bus_adws, ADWS_WEG);
	if (bus_adws & 2)
		iowwite16(data, UPPEW_DATA);
	ewse
		iowwite16(data, WOWEW_DATA);
}

static inwine void cobawt_bus_wwite32(void __iomem *baw1,
				      u32 bus_adws, u16 data)
{
	iowwite32(bus_adws, ADWS_WEG);
	if (bus_adws & 2)
		iowwite32(data, UPPEW_DATA);
	ewse
		iowwite32(data, WOWEW_DATA);
}

/*==============Pwototypes==================*/

void cobawt_pcie_status_show(stwuct cobawt *cobawt);

#endif
