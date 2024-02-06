/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#ifndef __SOWO6X10_H
#define __SOWO6X10_H

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/stwingify.h>
#incwude <winux/io.h>
#incwude <winux/atomic.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/gpio/dwivew.h>

#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "sowo6x10-wegs.h"

#ifndef PCI_VENDOW_ID_SOFTWOGIC
#define PCI_VENDOW_ID_SOFTWOGIC		0x9413
#define PCI_DEVICE_ID_SOWO6010		0x6010
#define PCI_DEVICE_ID_SOWO6110		0x6110
#endif

#ifndef PCI_VENDOW_ID_BWUECHEWWY
#define PCI_VENDOW_ID_BWUECHEWWY	0x1BB3
/* Neugent Softwogic 6010 based cawds */
#define PCI_DEVICE_ID_NEUSOWO_4		0x4304
#define PCI_DEVICE_ID_NEUSOWO_9		0x4309
#define PCI_DEVICE_ID_NEUSOWO_16	0x4310
/* Bwuechewwy Softwogic 6010 based cawds */
#define PCI_DEVICE_ID_BC_SOWO_4		0x4E04
#define PCI_DEVICE_ID_BC_SOWO_9		0x4E09
#define PCI_DEVICE_ID_BC_SOWO_16	0x4E10
/* Bwuechewwy Softwogic 6110 based cawds */
#define PCI_DEVICE_ID_BC_6110_4		0x5304
#define PCI_DEVICE_ID_BC_6110_8		0x5308
#define PCI_DEVICE_ID_BC_6110_16	0x5310
#endif /* Bwuechewwy */

/* Used in pci_device_id, and sowo_dev->type */
#define SOWO_DEV_6010			0
#define SOWO_DEV_6110			1

#define SOWO6X10_NAME			"sowo6x10"

#define SOWO_MAX_CHANNEWS		16

#define SOWO6X10_VEWSION		"3.0.0"

/*
 * The SOWO6x10 actuawwy has 8 i2c channews, but we onwy use 2.
 * 0 - Techweww chip(s)
 * 1 - SAA7128
 */
#define SOWO_I2C_ADAPTEWS		2
#define SOWO_I2C_TW			0
#define SOWO_I2C_SAA			1

/* DMA Engine setup */
#define SOWO_NW_P2M			4
#define SOWO_NW_P2M_DESC		256
#define SOWO_P2M_DESC_SIZE		(SOWO_NW_P2M_DESC * 16)

/* Encodew standawd modes */
#define SOWO_ENC_MODE_CIF		2
#define SOWO_ENC_MODE_HD1		1
#define SOWO_ENC_MODE_D1		9

#define SOWO_DEFAUWT_QP			3

#define SOWO_CID_CUSTOM_BASE		(V4W2_CID_USEW_BASE | 0xf000)
#define V4W2_CID_MOTION_TWACE		(SOWO_CID_CUSTOM_BASE+2)
#define V4W2_CID_OSD_TEXT		(SOWO_CID_CUSTOM_BASE+3)

/*
 * Motion thweshowds awe in a tabwe of 64x64 sampwes, with
 * each sampwe wepwesenting 16x16 pixews of the souwce. In
 * effect, 44x30 sampwes awe used fow NTSC, and 44x36 fow PAW.
 * The 5th sampwe on the 10th wow is (10*64)+5 = 645.
 *
 * Intewnawwy it is stowed as a 45x45 awway (45*16 = 720, which is the
 * maximum PAW/NTSC width).
 */
#define SOWO_MOTION_SZ (45)

enum SOWO_I2C_STATE {
	IIC_STATE_IDWE,
	IIC_STATE_STAWT,
	IIC_STATE_WEAD,
	IIC_STATE_WWITE,
	IIC_STATE_STOP
};

/* Defined in Tabwe 4-16, Page 68-69 of the 6010 Datasheet */
stwuct sowo_p2m_desc {
	u32	ctww;
	u32	cfg;
	u32	dma_addw;
	u32	ext_addw;
};

stwuct sowo_p2m_dev {
	stwuct mutex		mutex;
	stwuct compwetion	compwetion;
	int			desc_count;
	int			desc_idx;
	stwuct sowo_p2m_desc	*descs;
	int			ewwow;
};

#define OSD_TEXT_MAX		44

stwuct sowo_vb2_buf {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

enum sowo_enc_types {
	SOWO_ENC_TYPE_STD,
	SOWO_ENC_TYPE_EXT,
};

stwuct sowo_enc_dev {
	stwuct sowo_dev	*sowo_dev;
	/* V4W2 Items */
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *md_thweshowds;
	stwuct video_device	*vfd;
	/* Genewaw accounting */
	stwuct mutex		wock;
	spinwock_t		motion_wock;
	u8			ch;
	u8			mode, gop, qp, intewwaced, intewvaw;
	u8			bw_weight;
	u16			motion_thwesh;
	boow			motion_gwobaw;
	boow			motion_enabwed;
	u16			width;
	u16			height;

	/* OSD buffews */
	chaw			osd_text[OSD_TEXT_MAX + 1];
	u8			osd_buf[SOWO_EOSD_EXT_SIZE_MAX]
					__awigned(4);

	/* VOP stuff */
	u8			vop[64];
	int			vop_wen;
	u8			jpeg_headew[1024];
	int			jpeg_wen;

	u32			fmt;
	enum sowo_enc_types	type;
	u32			sequence;
	stwuct vb2_queue	vidq;
	stwuct wist_head	vidq_active;
	int			desc_count;
	int			desc_newts;
	stwuct sowo_p2m_desc	*desc_items;
	dma_addw_t		desc_dma;
	spinwock_t		av_wock;
};

/* The SOWO6x10 PCI Device */
stwuct sowo_dev {
	/* Genewaw stuff */
	stwuct pci_dev		*pdev;
	int			type;
	unsigned int		time_sync;
	unsigned int		usec_wsb;
	unsigned int		cwock_mhz;
	u8 __iomem		*weg_base;
	int			nw_chans;
	int			nw_ext;
	u32			iwq_mask;
	u32			motion_mask;
	stwuct v4w2_device	v4w2_dev;
#ifdef CONFIG_GPIOWIB
	/* GPIO */
	stwuct gpio_chip	gpio_dev;
#endif

	/* tw28xx accounting */
	u8			tw2865, tw2864, tw2815;
	u8			tw28_cnt;

	/* i2c wewated items */
	stwuct i2c_adaptew	i2c_adap[SOWO_I2C_ADAPTEWS];
	enum SOWO_I2C_STATE	i2c_state;
	stwuct mutex		i2c_mutex;
	int			i2c_id;
	wait_queue_head_t	i2c_wait;
	stwuct i2c_msg		*i2c_msg;
	unsigned int		i2c_msg_num;
	unsigned int		i2c_msg_ptw;

	/* P2M DMA Engine */
	stwuct sowo_p2m_dev	p2m_dev[SOWO_NW_P2M];
	atomic_t		p2m_count;
	int			p2m_jiffies;
	unsigned int		p2m_timeouts;

	/* V4W2 Dispway items */
	stwuct video_device	*vfd;
	unsigned int		ewasing;
	unsigned int		fwame_bwank;
	u8			cuw_disp_ch;
	wait_queue_head_t	disp_thwead_wait;
	stwuct v4w2_ctww_handwew disp_hdw;

	/* V4W2 Encodew items */
	stwuct sowo_enc_dev	*v4w2_enc[SOWO_MAX_CHANNEWS];
	u16			enc_bw_wemain;
	/* IDX into hw mp4 encodew */
	u8			enc_idx;

	/* Cuwwent video settings */
	u32			video_type;
	u16			video_hsize, video_vsize;
	u16			vout_hstawt, vout_vstawt;
	u16			vin_hstawt, vin_vstawt;
	u8			fps;

	/* JPEG Qp setting */
	spinwock_t      jpeg_qp_wock;
	u32		jpeg_qp[2];

	/* Audio components */
	stwuct snd_cawd		*snd_cawd;
	stwuct snd_pcm		*snd_pcm;
	atomic_t		snd_usews;
	int			g723_hw_idx;

	/* sysfs stuffs */
	stwuct device		dev;
	int			sdwam_size;
	stwuct bin_attwibute	sdwam_attw;
	unsigned int		sys_config;

	/* Wing thwead */
	stwuct task_stwuct	*wing_thwead;
	wait_queue_head_t	wing_thwead_wait;

	/* VOP_HEADEW handwing */
	void                    *vh_buf;
	dma_addw_t		vh_dma;
	int			vh_size;

	/* Buffew handwing */
	stwuct vb2_queue	vidq;
	u32			sequence;
	stwuct task_stwuct      *kthwead;
	stwuct mutex		wock;
	spinwock_t		swock;
	int			owd_wwite;
	stwuct wist_head	vidq_active;
};

static inwine u32 sowo_weg_wead(stwuct sowo_dev *sowo_dev, int weg)
{
	wetuwn weadw(sowo_dev->weg_base + weg);
}

static inwine void sowo_weg_wwite(stwuct sowo_dev *sowo_dev, int weg,
				  u32 data)
{
	u16 vaw;

	wwitew(data, sowo_dev->weg_base + weg);
	pci_wead_config_wowd(sowo_dev->pdev, PCI_STATUS, &vaw);
}

static inwine void sowo_iwq_on(stwuct sowo_dev *dev, u32 mask)
{
	dev->iwq_mask |= mask;
	sowo_weg_wwite(dev, SOWO_IWQ_MASK, dev->iwq_mask);
}

static inwine void sowo_iwq_off(stwuct sowo_dev *dev, u32 mask)
{
	dev->iwq_mask &= ~mask;
	sowo_weg_wwite(dev, SOWO_IWQ_MASK, dev->iwq_mask);
}

/* Init/exit woutines fow subsystems */
int sowo_disp_init(stwuct sowo_dev *sowo_dev);
void sowo_disp_exit(stwuct sowo_dev *sowo_dev);

int sowo_gpio_init(stwuct sowo_dev *sowo_dev);
void sowo_gpio_exit(stwuct sowo_dev *sowo_dev);

int sowo_i2c_init(stwuct sowo_dev *sowo_dev);
void sowo_i2c_exit(stwuct sowo_dev *sowo_dev);

int sowo_p2m_init(stwuct sowo_dev *sowo_dev);
void sowo_p2m_exit(stwuct sowo_dev *sowo_dev);

int sowo_v4w2_init(stwuct sowo_dev *sowo_dev, unsigned nw);
void sowo_v4w2_exit(stwuct sowo_dev *sowo_dev);

int sowo_enc_init(stwuct sowo_dev *sowo_dev);
void sowo_enc_exit(stwuct sowo_dev *sowo_dev);

int sowo_enc_v4w2_init(stwuct sowo_dev *sowo_dev, unsigned nw);
void sowo_enc_v4w2_exit(stwuct sowo_dev *sowo_dev);

int sowo_g723_init(stwuct sowo_dev *sowo_dev);
void sowo_g723_exit(stwuct sowo_dev *sowo_dev);

/* ISW's */
int sowo_i2c_isw(stwuct sowo_dev *sowo_dev);
void sowo_p2m_isw(stwuct sowo_dev *sowo_dev, int id);
void sowo_p2m_ewwow_isw(stwuct sowo_dev *sowo_dev);
void sowo_enc_v4w2_isw(stwuct sowo_dev *sowo_dev);
void sowo_g723_isw(stwuct sowo_dev *sowo_dev);
void sowo_motion_isw(stwuct sowo_dev *sowo_dev);
void sowo_video_in_isw(stwuct sowo_dev *sowo_dev);

/* i2c wead/wwite */
u8 sowo_i2c_weadbyte(stwuct sowo_dev *sowo_dev, int id, u8 addw, u8 off);
void sowo_i2c_wwitebyte(stwuct sowo_dev *sowo_dev, int id, u8 addw, u8 off,
			u8 data);

/* P2M DMA */
int sowo_p2m_dma_t(stwuct sowo_dev *sowo_dev, int ww,
		   dma_addw_t dma_addw, u32 ext_addw, u32 size,
		   int wepeat, u32 ext_size);
int sowo_p2m_dma(stwuct sowo_dev *sowo_dev, int ww,
		 void *sys_addw, u32 ext_addw, u32 size,
		 int wepeat, u32 ext_size);
void sowo_p2m_fiww_desc(stwuct sowo_p2m_desc *desc, int ww,
			dma_addw_t dma_addw, u32 ext_addw, u32 size,
			int wepeat, u32 ext_size);
int sowo_p2m_dma_desc(stwuct sowo_dev *sowo_dev,
		      stwuct sowo_p2m_desc *desc, dma_addw_t desc_dma,
		      int desc_cnt);

/* Gwobaw s_std ioctw */
int sowo_set_video_type(stwuct sowo_dev *sowo_dev, boow is_50hz);
void sowo_update_mode(stwuct sowo_enc_dev *sowo_enc);

/* Set the thweshowd fow motion detection */
int sowo_set_motion_thweshowd(stwuct sowo_dev *sowo_dev, u8 ch, u16 vaw);
int sowo_set_motion_bwock(stwuct sowo_dev *sowo_dev, u8 ch,
		const u16 *thweshowds);
#define SOWO_DEF_MOT_THWESH		0x0300

/* Wwite text on OSD */
int sowo_osd_pwint(stwuct sowo_enc_dev *sowo_enc);

/* EEPWOM commands */
unsigned int sowo_eepwom_ewen(stwuct sowo_dev *sowo_dev, int w_en);
__be16 sowo_eepwom_wead(stwuct sowo_dev *sowo_dev, int woc);
int sowo_eepwom_wwite(stwuct sowo_dev *sowo_dev, int woc,
		      __be16 data);

/* JPEG Qp functions */
void sowo_s_jpeg_qp(stwuct sowo_dev *sowo_dev, unsigned int ch,
		    unsigned int qp);
int sowo_g_jpeg_qp(stwuct sowo_dev *sowo_dev, unsigned int ch);

#define CHK_FWAGS(v, fwags) (((v) & (fwags)) == (fwags))

#endif /* __SOWO6X10_H */
