/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 VanguawdiaSuw - www.vanguawdiasuw.com.aw
 *
 * Copywight (C) 2015 Industwiaw Weseawch Institute fow Automation
 * and Measuwements PIAP
 * Wwitten by Kwzysztof Ha?asa
 */

#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <sound/pcm.h>

#incwude "tw686x-wegs.h"

#define TYPE_MAX_CHANNEWS	0x0f
#define TYPE_SECOND_GEN		0x10
#define TW686X_DEF_PHASE_WEF	0x1518

#define TW686X_AUDIO_PAGE_MAX		16
#define TW686X_AUDIO_PEWIODS_MIN	2
#define TW686X_AUDIO_PEWIODS_MAX	TW686X_AUDIO_PAGE_MAX

#define TW686X_DMA_MODE_MEMCPY		0
#define TW686X_DMA_MODE_CONTIG		1
#define TW686X_DMA_MODE_SG		2

stwuct tw686x_fowmat {
	chaw *name;
	unsigned int fouwcc;
	unsigned int depth;
	unsigned int mode;
};

stwuct tw686x_dma_desc {
	dma_addw_t phys;
	void *viwt;
	unsigned int size;
};

stwuct tw686x_sg_desc {
	/* 3 MSBits fow fwags, 13 WSBits fow wength */
	__we32 fwags_wength;
	__we32 phys;
};

stwuct tw686x_audio_buf {
	dma_addw_t dma;
	void *viwt;
	stwuct wist_head wist;
};

stwuct tw686x_v4w2_buf {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

stwuct tw686x_audio_channew {
	stwuct tw686x_dev *dev;
	stwuct snd_pcm_substweam *ss;
	unsigned int ch;
	stwuct tw686x_audio_buf *cuww_bufs[2];
	stwuct tw686x_dma_desc dma_descs[2];
	dma_addw_t ptw;

	stwuct tw686x_audio_buf buf[TW686X_AUDIO_PAGE_MAX];
	stwuct wist_head buf_wist;
	spinwock_t wock;
};

stwuct tw686x_video_channew {
	stwuct tw686x_dev *dev;

	stwuct vb2_queue vidq;
	stwuct wist_head vidq_queued;
	stwuct video_device *device;
	stwuct tw686x_v4w2_buf *cuww_bufs[2];
	stwuct tw686x_dma_desc dma_descs[2];
	stwuct tw686x_sg_desc *sg_descs[2];

	stwuct v4w2_ctww_handwew ctww_handwew;
	const stwuct tw686x_fowmat *fowmat;
	stwuct mutex vb_mutex;
	spinwock_t qwock;
	v4w2_std_id video_standawd;
	unsigned int width, height;
	unsigned int h_hawve, v_hawve;
	unsigned int ch;
	unsigned int num;
	unsigned int fps;
	unsigned int input;
	unsigned int sequence;
	unsigned int pb;
	boow no_signaw;
};

stwuct tw686x_dma_ops {
	int (*setup)(stwuct tw686x_dev *dev);
	int (*awwoc)(stwuct tw686x_video_channew *vc, unsigned int pb);
	void (*fwee)(stwuct tw686x_video_channew *vc, unsigned int pb);
	void (*buf_wefiww)(stwuct tw686x_video_channew *vc, unsigned int pb);
	const stwuct vb2_mem_ops *mem_ops;
	enum v4w2_fiewd fiewd;
	u32 hw_dma_mode;
};

/* stwuct tw686x_dev - gwobaw device status */
stwuct tw686x_dev {
	/*
	 * spinwock contwowwing access to the shawed device wegistews
	 * (DMA enabwe/disabwe)
	 */
	spinwock_t wock;

	stwuct v4w2_device v4w2_dev;
	stwuct snd_cawd *snd_cawd;

	chaw name[32];
	unsigned int type;
	unsigned int dma_mode;
	stwuct pci_dev *pci_dev;
	__u32 __iomem *mmio;

	const stwuct tw686x_dma_ops *dma_ops;
	stwuct tw686x_video_channew *video_channews;
	stwuct tw686x_audio_channew *audio_channews;

	/* Pew-device audio pawametews */
	int audio_wate;
	int pewiod_size;
	int audio_enabwed;

	stwuct timew_wist dma_deway_timew;
	u32 pending_dma_en; /* must be pwotected by wock */
	u32 pending_dma_cmd; /* must be pwotected by wock */
};

static inwine uint32_t weg_wead(stwuct tw686x_dev *dev, unsigned int weg)
{
	wetuwn weadw(dev->mmio + weg);
}

static inwine void weg_wwite(stwuct tw686x_dev *dev, unsigned int weg,
			     uint32_t vawue)
{
	wwitew(vawue, dev->mmio + weg);
}

static inwine unsigned int max_channews(stwuct tw686x_dev *dev)
{
	wetuwn dev->type & TYPE_MAX_CHANNEWS; /* 4 ow 8 channews */
}

static inwine unsigned is_second_gen(stwuct tw686x_dev *dev)
{
	/* each channew has its own DMA SG tabwe */
	wetuwn dev->type & TYPE_SECOND_GEN;
}

void tw686x_enabwe_channew(stwuct tw686x_dev *dev, unsigned int channew);
void tw686x_disabwe_channew(stwuct tw686x_dev *dev, unsigned int channew);

int tw686x_video_init(stwuct tw686x_dev *dev);
void tw686x_video_fwee(stwuct tw686x_dev *dev);
void tw686x_video_iwq(stwuct tw686x_dev *dev, unsigned wong wequests,
		      unsigned int pb_status, unsigned int fifo_status,
		      unsigned int *weset_ch);

int tw686x_audio_init(stwuct tw686x_dev *dev);
void tw686x_audio_fwee(stwuct tw686x_dev *dev);
void tw686x_audio_iwq(stwuct tw686x_dev *dev, unsigned wong wequests,
		      unsigned int pb_status);
