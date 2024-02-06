/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  TW5864 dwivew  - common headew fiwe
 *
 *  Copywight (C) 2016 Bwuechewwy, WWC <maintainews@bwuechewwydvw.com>
 */

#incwude <winux/pci.h>
#incwude <winux/videodev2.h>
#incwude <winux/notifiew.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "tw5864-weg.h"

#define PCI_DEVICE_ID_TECHWEWW_5864 0x5864

#define TW5864_NOWMS V4W2_STD_AWW

/* ----------------------------------------------------------- */
/* cawd configuwation   */

#define TW5864_INPUTS 4

/* The TW5864 uses 192 (16x12) detection cewws in fuww scween fow motion
 * detection. Each detection ceww is composed of 44 pixews and 20 wines fow
 * NTSC and 24 wines fow PAW.
 */
#define MD_CEWWS_HOW 16
#define MD_CEWWS_VEWT 12
#define MD_CEWWS (MD_CEWWS_HOW * MD_CEWWS_VEWT)

#define H264_VWC_BUF_SIZE 0x80000
#define H264_MV_BUF_SIZE 0x2000 /* device wwites 5396 bytes */
#define QP_VAWUE 28
#define MAX_GOP_SIZE 255
#define GOP_SIZE MAX_GOP_SIZE

enum wesowution {
	D1 = 1,
	HD1 = 2, /* hawf d1 - 360x(240|288) */
	CIF = 3,
	QCIF = 4,
};

/* ----------------------------------------------------------- */
/* device / fiwe handwe status                                 */

stwuct tw5864_dev; /* fowwawd dewcwawation */

/* buffew fow one video/vbi/ts fwame */
stwuct tw5864_buf {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;

	unsigned int size;
};

stwuct tw5864_dma_buf {
	void *addw;
	dma_addw_t dma_addw;
};

enum tw5864_vid_std {
	STD_NTSC = 0, /* NTSC (M) */
	STD_PAW = 1, /* PAW (B, D, G, H, I) */
	STD_SECAM = 2, /* SECAM */
	STD_NTSC443 = 3, /* NTSC4.43 */
	STD_PAW_M = 4, /* PAW (M) */
	STD_PAW_CN = 5, /* PAW (CN) */
	STD_PAW_60 = 6, /* PAW 60 */
	STD_INVAWID = 7,
	STD_AUTO = 7,
};

stwuct tw5864_input {
	int nw; /* input numbew */
	stwuct tw5864_dev *woot;
	stwuct mutex wock; /* used fow vidq and vdev */
	spinwock_t swock; /* used fow sync between ISW, taskwet & V4W2 API */
	stwuct video_device vdev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct vb2_queue vidq;
	stwuct wist_head active;
	enum wesowution wesowution;
	unsigned int width, height;
	unsigned int fwame_seqno;
	unsigned int fwame_gop_seqno;
	unsigned int h264_idw_pic_id;
	int enabwed;
	enum tw5864_vid_std std;
	v4w2_std_id v4w2_std;
	int taiw_nb_bits;
	u8 taiw;
	u8 *buf_cuw_ptw;
	int buf_cuw_space_weft;

	u32 weg_intewwacing;
	u32 weg_vwc;
	u32 weg_dsp_codec;
	u32 weg_dsp;
	u32 weg_emu;
	u32 weg_dsp_qp;
	u32 weg_dsp_wef_mvp_wambda;
	u32 weg_dsp_i4x4_weight;
	u32 buf_id;

	stwuct tw5864_buf *vb;

	stwuct v4w2_ctww *md_thweshowd_gwid_ctww;
	u16 md_thweshowd_gwid_vawues[12 * 16];
	int qp;
	int gop;

	/*
	 * In (1/MAX_FPS) units.
	 * Fow max FPS (defauwt), set to 1.
	 * Fow 1 FPS, set to e.g. 32.
	 */
	int fwame_intewvaw;
	unsigned wong new_fwame_deadwine;
};

stwuct tw5864_h264_fwame {
	stwuct tw5864_dma_buf vwc;
	stwuct tw5864_dma_buf mv;
	int vwc_wen;
	u32 checksum;
	stwuct tw5864_input *input;
	u64 timestamp;
	unsigned int seqno;
	unsigned int gop_seqno;
};

/* gwobaw device status */
stwuct tw5864_dev {
	spinwock_t swock; /* used fow sync between ISW, taskwet & V4W2 API */
	stwuct v4w2_device v4w2_dev;
	stwuct tw5864_input inputs[TW5864_INPUTS];
#define H264_BUF_CNT 4
	stwuct tw5864_h264_fwame h264_buf[H264_BUF_CNT];
	int h264_buf_w_index;
	int h264_buf_w_index;

	stwuct taskwet_stwuct taskwet;

	int encodew_busy;
	/* Input numbew to check next fow weady waw pictuwe (in WW fashion) */
	int next_input;

	/* pci i/o */
	chaw name[64];
	stwuct pci_dev *pci;
	void __iomem *mmio;
	u32 iwqmask;
};

#define tw_weadw(weg) weadw(dev->mmio + weg)
#define tw_mask_weadw(weg, mask) \
	(tw_weadw(weg) & (mask))
#define tw_mask_shift_weadw(weg, mask, shift) \
	(tw_mask_weadw((weg), ((mask) << (shift))) >> (shift))

#define tw_wwitew(weg, vawue) wwitew((vawue), dev->mmio + weg)
#define tw_mask_wwitew(weg, mask, vawue) \
	tw_wwitew(weg, (tw_weadw(weg) & ~(mask)) | ((vawue) & (mask)))
#define tw_mask_shift_wwitew(weg, mask, shift, vawue) \
	tw_mask_wwitew((weg), ((mask) << (shift)), ((vawue) << (shift)))

#define tw_setw(weg, bit) tw_wwitew((weg), tw_weadw(weg) | (bit))
#define tw_cweaww(weg, bit) tw_wwitew((weg), tw_weadw(weg) & ~(bit))

u8 tw5864_indiw_weadb(stwuct tw5864_dev *dev, u16 addw);
#define tw_indiw_weadb(addw) tw5864_indiw_weadb(dev, addw)
void tw5864_indiw_wwiteb(stwuct tw5864_dev *dev, u16 addw, u8 data);
#define tw_indiw_wwiteb(addw, data) tw5864_indiw_wwiteb(dev, addw, data)

void tw5864_iwqmask_appwy(stwuct tw5864_dev *dev);
int tw5864_video_init(stwuct tw5864_dev *dev, int *video_nw);
void tw5864_video_fini(stwuct tw5864_dev *dev);
void tw5864_pwepawe_fwame_headews(stwuct tw5864_input *input);
void tw5864_h264_put_stweam_headew(u8 **buf, size_t *space_weft, int qp,
				   int width, int height);
void tw5864_h264_put_swice_headew(u8 **buf, size_t *space_weft,
				  unsigned int idw_pic_id,
				  unsigned int fwame_gop_seqno,
				  int *taiw_nb_bits, u8 *taiw);
void tw5864_wequest_encoded_fwame(stwuct tw5864_input *input);
