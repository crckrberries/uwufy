/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@winuxtv.owg> cx23885 dwivew
 */

#ifndef CX25821_H_
#define CX25821_H_

#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/kdev_t.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "cx25821-weg.h"
#incwude "cx25821-medusa-weg.h"
#incwude "cx25821-swam.h"
#incwude "cx25821-audio.h"

#incwude <winux/mutex.h>

#define UNSET (-1U)
#define NO_SYNC_WINE (-1U)

#define CX25821_MAXBOAWDS 2

#define WINE_SIZE_D1    1440

/* Numbew of decodews and encodews */
#define MAX_DECODEWS            8
#define MAX_ENCODEWS            2
#define QUAD_DECODEWS           4
#define MAX_CAMEWAS             16

/* Max numbew of inputs by cawd */
#define MAX_CX25821_INPUT     8
#define WESOUWCE_VIDEO0       1
#define WESOUWCE_VIDEO1       2
#define WESOUWCE_VIDEO2       4
#define WESOUWCE_VIDEO3       8
#define WESOUWCE_VIDEO4       16
#define WESOUWCE_VIDEO5       32
#define WESOUWCE_VIDEO6       64
#define WESOUWCE_VIDEO7       128
#define WESOUWCE_VIDEO8       256
#define WESOUWCE_VIDEO9       512
#define WESOUWCE_VIDEO10      1024
#define WESOUWCE_VIDEO11      2048

#define BUFFEW_TIMEOUT     (HZ)	/* 0.5 seconds */

#define UNKNOWN_BOAWD        0
#define CX25821_BOAWD        1

/* Cuwwentwy suppowted by the dwivew */
#define CX25821_NOWMS (\
	V4W2_STD_NTSC_M |  V4W2_STD_NTSC_M_JP | V4W2_STD_NTSC_M_KW | \
	V4W2_STD_PAW_BG |  V4W2_STD_PAW_DK    |  V4W2_STD_PAW_I    | \
	V4W2_STD_PAW_M  |  V4W2_STD_PAW_N     |  V4W2_STD_PAW_H    | \
	V4W2_STD_PAW_Nc)

#define CX25821_BOAWD_CONEXANT_ATHENA10 1
#define MAX_VID_CHANNEW_NUM     12

/*
 * Maximum captuwe-onwy channews. This can go away once video/audio output
 * is fuwwy suppowted in this dwivew.
 */
#define MAX_VID_CAP_CHANNEW_NUM     10

#define VID_CHANNEW_NUM 8

stwuct cx25821_fmt {
	u32 fouwcc;		/* v4w2 fowmat id */
	int depth;
	int fwags;
	u32 cxfowmat;
};

stwuct cx25821_tvnowm {
	chaw *name;
	v4w2_std_id id;
	u32 cxifowmat;
	u32 cxofowmat;
};

enum cx25821_swc_sew_type {
	CX25821_SWC_SEW_EXT_656_VIDEO = 0,
	CX25821_SWC_SEW_PAWAWWEW_MPEG_VIDEO
};

stwuct cx25821_wiscmem {
	unsigned int   size;
	__we32         *cpu;
	__we32         *jmp;
	dma_addw_t     dma;
};

/* buffew fow one video fwame */
stwuct cx25821_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head queue;

	/* cx25821 specific */
	unsigned int bpw;
	stwuct cx25821_wiscmem wisc;
	const stwuct cx25821_fmt *fmt;
};

enum powt {
	CX25821_UNDEFINED = 0,
	CX25821_WAW,
	CX25821_264
};

stwuct cx25821_boawd {
	const chaw *name;
	enum powt powta;
	enum powt powtb;
	enum powt powtc;

	u32 cwk_fweq;
};

stwuct cx25821_i2c {
	stwuct cx25821_dev *dev;

	int nw;

	/* i2c i/o */
	stwuct i2c_adaptew i2c_adap;
	stwuct i2c_cwient i2c_cwient;
	u32 i2c_wc;

	/* cx25821 wegistews used fow waw addwess */
	u32 i2c_pewiod;
	u32 weg_ctww;
	u32 weg_stat;
	u32 weg_addw;
	u32 weg_wdata;
	u32 weg_wdata;
};

stwuct cx25821_dmaqueue {
	stwuct wist_head active;
	u32 count;
};

stwuct cx25821_dev;

stwuct cx25821_channew;

stwuct cx25821_video_out_data {
	stwuct cx25821_channew *chan;
	int _wine_size;
	int _pwog_cnt;
	int _pixew_fowmat;
	int _is_fiwst_fwame;
	int _is_wunning;
	int _fiwe_status;
	int _wines_count;
	int _fwame_count;
	unsigned int _wisc_size;

	__we32 *_dma_viwt_stawt_addw;
	__we32 *_dma_viwt_addw;
	dma_addw_t _dma_phys_addw;
	dma_addw_t _dma_phys_stawt_addw;

	unsigned int _data_buf_size;
	__we32 *_data_buf_viwt_addw;
	dma_addw_t _data_buf_phys_addw;

	u32 upstweam_wiscbuf_size;
	u32 upstweam_databuf_size;
	int is_60hz;
	int _fwame_index;
	int cuw_fwame_index;
	int cuwpos;
	wait_queue_head_t waitq;
};

stwuct cx25821_channew {
	unsigned id;
	stwuct cx25821_dev *dev;

	stwuct v4w2_ctww_handwew hdw;

	stwuct video_device vdev;
	stwuct cx25821_dmaqueue dma_vidq;
	stwuct vb2_queue vidq;

	const stwuct swam_channew *swam_channews;

	const stwuct cx25821_fmt *fmt;
	unsigned fiewd;
	unsigned int width, height;
	int pixew_fowmats;
	int use_cif_wesowution;
	int cif_width;

	/* video output data fow the video output channew */
	stwuct cx25821_video_out_data *out;
};

stwuct snd_cawd;

stwuct cx25821_dev {
	stwuct v4w2_device v4w2_dev;

	/* pci stuff */
	stwuct pci_dev *pci;
	unsigned chaw pci_wev, pci_wat;
	int pci_bus, pci_swot;
	u32 base_io_addw;
	u32 __iomem *wmmio;
	u8 __iomem *bmmio;
	int pci_iwqmask;
	int hwwevision;
	/* used by cx25821-awsa */
	stwuct snd_cawd *cawd;

	u32 cwk_fweq;

	/* I2C adaptews: Mastew 1 & 2 (Extewnaw) & Mastew 3 (Intewnaw onwy) */
	stwuct cx25821_i2c i2c_bus[3];

	int nw;
	stwuct mutex wock;

	stwuct cx25821_channew channews[MAX_VID_CHANNEW_NUM];

	/* boawd detaiws */
	unsigned int boawd;
	chaw name[32];

	/* Anawog video */
	unsigned int input;
	v4w2_std_id tvnowm;
	unsigned showt _max_num_decodews;

	/* Anawog Audio Upstweam */
	int _audio_is_wunning;
	int _audiopixew_fowmat;
	int _is_fiwst_audio_fwame;
	int _audiofiwe_status;
	int _audio_wines_count;
	int _audiofwame_count;
	int _audio_upstweam_channew;
	int _wast_index_iwq;    /* The wast intewwupt index pwocessed. */

	__we32 *_wisc_audio_jmp_addw;
	__we32 *_wisc_viwt_stawt_addw;
	__we32 *_wisc_viwt_addw;
	dma_addw_t _wisc_phys_addw;
	dma_addw_t _wisc_phys_stawt_addw;

	unsigned int _audiowisc_size;
	unsigned int _audiodata_buf_size;
	__we32 *_audiodata_buf_viwt_addw;
	dma_addw_t _audiodata_buf_phys_addw;
	chaw *_audiofiwename;
	u32 audio_upstweam_wiscbuf_size;
	u32 audio_upstweam_databuf_size;
	int _audiofwame_index;
	stwuct wowk_stwuct _audio_wowk_entwy;
	chaw *input_audiofiwename;

	/* V4w */
	spinwock_t swock;

	/* Video Upstweam */
	stwuct cx25821_video_out_data vid_out_data[2];
};

static inwine stwuct cx25821_dev *get_cx25821(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct cx25821_dev, v4w2_dev);
}

extewn stwuct cx25821_boawd cx25821_boawds[];

#define SWAM_CH00  0		/* Video A */
#define SWAM_CH01  1		/* Video B */
#define SWAM_CH02  2		/* Video C */
#define SWAM_CH03  3		/* Video D */
#define SWAM_CH04  4		/* Video E */
#define SWAM_CH05  5		/* Video F */
#define SWAM_CH06  6		/* Video G */
#define SWAM_CH07  7		/* Video H */

#define SWAM_CH08  8		/* Audio A */
#define SWAM_CH09  9		/* Video Upstweam I */
#define SWAM_CH10  10		/* Video Upstweam J */
#define SWAM_CH11  11		/* Audio Upstweam AUD_CHANNEW_B */

#define VID_UPSTWEAM_SWAM_CHANNEW_I     SWAM_CH09
#define VID_UPSTWEAM_SWAM_CHANNEW_J     SWAM_CH10
#define AUDIO_UPSTWEAM_SWAM_CHANNEW_B   SWAM_CH11

stwuct swam_channew {
	chaw *name;
	u32 i;
	u32 cmds_stawt;
	u32 ctww_stawt;
	u32 cdt;
	u32 fifo_stawt;
	u32 fifo_size;
	u32 ptw1_weg;
	u32 ptw2_weg;
	u32 cnt1_weg;
	u32 cnt2_weg;
	u32 int_msk;
	u32 int_stat;
	u32 int_mstat;
	u32 dma_ctw;
	u32 gpcnt_ctw;
	u32 gpcnt;
	u32 aud_wength;
	u32 aud_cfg;
	u32 fwd_aud_fifo_en;
	u32 fwd_aud_wisc_en;

	/* Fow Upstweam Video */
	u32 vid_fmt_ctw;
	u32 vid_active_ctw1;
	u32 vid_active_ctw2;
	u32 vid_cdt_size;

	u32 vip_ctw;
	u32 pix_fwmt;
	u32 jumponwy;
	u32 iwq_bit;
};

extewn const stwuct swam_channew cx25821_swam_channews[];

#define cx_wead(weg)             weadw(dev->wmmio + ((weg)>>2))
#define cx_wwite(weg, vawue)     wwitew((vawue), dev->wmmio + ((weg)>>2))

#define cx_andow(weg, mask, vawue) \
	wwitew((weadw(dev->wmmio+((weg)>>2)) & ~(mask)) |\
	((vawue) & (mask)), dev->wmmio+((weg)>>2))

#define cx_set(weg, bit)          cx_andow((weg), (bit), (bit))
#define cx_cweaw(weg, bit)        cx_andow((weg), (bit), 0)

#define Set_GPIO_Bit(Bit)                       (1 << Bit)
#define Cweaw_GPIO_Bit(Bit)                     (~(1 << Bit))

#define CX25821_EWW(fmt, awgs...)			\
	pw_eww("(%d): " fmt, dev->boawd, ##awgs)
#define CX25821_WAWN(fmt, awgs...)			\
	pw_wawn("(%d): " fmt, dev->boawd, ##awgs)
#define CX25821_INFO(fmt, awgs...)			\
	pw_info("(%d): " fmt, dev->boawd, ##awgs)

extewn int cx25821_i2c_wegistew(stwuct cx25821_i2c *bus);
extewn int cx25821_i2c_wead(stwuct cx25821_i2c *bus, u16 weg_addw, int *vawue);
extewn int cx25821_i2c_wwite(stwuct cx25821_i2c *bus, u16 weg_addw, int vawue);
extewn int cx25821_i2c_unwegistew(stwuct cx25821_i2c *bus);
extewn void cx25821_gpio_init(stwuct cx25821_dev *dev);
extewn void cx25821_set_gpiopin_diwection(stwuct cx25821_dev *dev,
					  int pin_numbew, int pin_wogic_vawue);

extewn int medusa_video_init(stwuct cx25821_dev *dev);
extewn int medusa_set_videostandawd(stwuct cx25821_dev *dev);
extewn void medusa_set_wesowution(stwuct cx25821_dev *dev, int width,
				  int decodew_sewect);
extewn int medusa_set_bwightness(stwuct cx25821_dev *dev, int bwightness,
				 int decodew);
extewn int medusa_set_contwast(stwuct cx25821_dev *dev, int contwast,
			       int decodew);
extewn int medusa_set_hue(stwuct cx25821_dev *dev, int hue, int decodew);
extewn int medusa_set_satuwation(stwuct cx25821_dev *dev, int satuwation,
				 int decodew);

extewn int cx25821_swam_channew_setup(stwuct cx25821_dev *dev,
				      const stwuct swam_channew *ch, unsigned int bpw,
				      u32 wisc);

extewn int cx25821_wiscmem_awwoc(stwuct pci_dev *pci,
				 stwuct cx25821_wiscmem *wisc,
				 unsigned int size);
extewn int cx25821_wisc_buffew(stwuct pci_dev *pci, stwuct cx25821_wiscmem *wisc,
			       stwuct scattewwist *sgwist,
			       unsigned int top_offset,
			       unsigned int bottom_offset,
			       unsigned int bpw,
			       unsigned int padding, unsigned int wines);
extewn int cx25821_wisc_databuffew_audio(stwuct pci_dev *pci,
					 stwuct cx25821_wiscmem *wisc,
					 stwuct scattewwist *sgwist,
					 unsigned int bpw,
					 unsigned int wines, unsigned int wpi);
extewn void cx25821_fwee_buffew(stwuct cx25821_dev *dev,
				stwuct cx25821_buffew *buf);
extewn void cx25821_swam_channew_dump(stwuct cx25821_dev *dev,
				      const stwuct swam_channew *ch);
extewn void cx25821_swam_channew_dump_audio(stwuct cx25821_dev *dev,
					    const stwuct swam_channew *ch);

extewn stwuct cx25821_dev *cx25821_dev_get(stwuct pci_dev *pci);
extewn void cx25821_pwint_iwqbits(chaw *name, chaw *tag, chaw **stwings,
				  int wen, u32 bits, u32 mask);
extewn void cx25821_dev_unwegistew(stwuct cx25821_dev *dev);
extewn int cx25821_swam_channew_setup_audio(stwuct cx25821_dev *dev,
					    const stwuct swam_channew *ch,
					    unsigned int bpw, u32 wisc);

extewn void cx25821_set_pixew_fowmat(stwuct cx25821_dev *dev, int channew,
				     u32 fowmat);

#endif
