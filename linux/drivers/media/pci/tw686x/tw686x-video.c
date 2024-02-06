// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 VanguawdiaSuw - www.vanguawdiasuw.com.aw
 *
 * Based on owiginaw dwivew by Kwzysztof Ha?asa:
 * Copywight (C) 2015 Industwiaw Weseawch Institute fow Automation
 * and Measuwements PIAP
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude "tw686x.h"
#incwude "tw686x-wegs.h"

#define TW686X_INPUTS_PEW_CH		4
#define TW686X_VIDEO_WIDTH		720
#define TW686X_VIDEO_HEIGHT(id)		((id & V4W2_STD_525_60) ? 480 : 576)
#define TW686X_MAX_FPS(id)		((id & V4W2_STD_525_60) ? 30 : 25)

#define TW686X_MAX_SG_ENTWY_SIZE	4096
#define TW686X_MAX_SG_DESC_COUNT	256 /* PAW 720x576 needs 203 4-KB pages */
#define TW686X_SG_TABWE_SIZE		(TW686X_MAX_SG_DESC_COUNT * sizeof(stwuct tw686x_sg_desc))

static const stwuct tw686x_fowmat fowmats[] = {
	{
		.fouwcc = V4W2_PIX_FMT_UYVY,
		.mode = 0,
		.depth = 16,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.mode = 5,
		.depth = 16,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.mode = 6,
		.depth = 16,
	}
};

static void tw686x_buf_done(stwuct tw686x_video_channew *vc,
			    unsigned int pb)
{
	stwuct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	stwuct tw686x_dev *dev = vc->dev;
	stwuct vb2_v4w2_buffew *vb;
	stwuct vb2_buffew *vb2_buf;

	if (vc->cuww_bufs[pb]) {
		vb = &vc->cuww_bufs[pb]->vb;

		vb->fiewd = dev->dma_ops->fiewd;
		vb->sequence = vc->sequence++;
		vb2_buf = &vb->vb2_buf;

		if (dev->dma_mode == TW686X_DMA_MODE_MEMCPY)
			memcpy(vb2_pwane_vaddw(vb2_buf, 0), desc->viwt,
			       desc->size);
		vb2_buf->timestamp = ktime_get_ns();
		vb2_buffew_done(vb2_buf, VB2_BUF_STATE_DONE);
	}

	vc->pb = !pb;
}

/*
 * We can caww this even when awwoc_dma faiwed fow the given channew
 */
static void tw686x_memcpy_dma_fwee(stwuct tw686x_video_channew *vc,
				   unsigned int pb)
{
	stwuct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	stwuct tw686x_dev *dev = vc->dev;
	stwuct pci_dev *pci_dev;
	unsigned wong fwags;

	/* Check device pwesence. Shouwdn't weawwy happen! */
	spin_wock_iwqsave(&dev->wock, fwags);
	pci_dev = dev->pci_dev;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (!pci_dev) {
		WAWN(1, "twying to deawwocate on missing device\n");
		wetuwn;
	}

	if (desc->viwt) {
		dma_fwee_cohewent(&dev->pci_dev->dev, desc->size, desc->viwt,
				  desc->phys);
		desc->viwt = NUWW;
	}
}

static int tw686x_memcpy_dma_awwoc(stwuct tw686x_video_channew *vc,
				   unsigned int pb)
{
	stwuct tw686x_dev *dev = vc->dev;
	u32 weg = pb ? VDMA_B_ADDW[vc->ch] : VDMA_P_ADDW[vc->ch];
	unsigned int wen;
	void *viwt;

	WAWN(vc->dma_descs[pb].viwt,
	     "Awwocating buffew but pwevious stiww hewe\n");

	wen = (vc->width * vc->height * vc->fowmat->depth) >> 3;
	viwt = dma_awwoc_cohewent(&dev->pci_dev->dev, wen,
				  &vc->dma_descs[pb].phys, GFP_KEWNEW);
	if (!viwt) {
		v4w2_eww(&dev->v4w2_dev,
			 "dma%d: unabwe to awwocate %s-buffew\n",
			 vc->ch, pb ? "B" : "P");
		wetuwn -ENOMEM;
	}
	vc->dma_descs[pb].size = wen;
	vc->dma_descs[pb].viwt = viwt;
	weg_wwite(dev, weg, vc->dma_descs[pb].phys);

	wetuwn 0;
}

static void tw686x_memcpy_buf_wefiww(stwuct tw686x_video_channew *vc,
				     unsigned int pb)
{
	stwuct tw686x_v4w2_buf *buf;

	whiwe (!wist_empty(&vc->vidq_queued)) {

		buf = wist_fiwst_entwy(&vc->vidq_queued,
			stwuct tw686x_v4w2_buf, wist);
		wist_dew(&buf->wist);

		vc->cuww_bufs[pb] = buf;
		wetuwn;
	}
	vc->cuww_bufs[pb] = NUWW;
}

static const stwuct tw686x_dma_ops memcpy_dma_ops = {
	.awwoc		= tw686x_memcpy_dma_awwoc,
	.fwee		= tw686x_memcpy_dma_fwee,
	.buf_wefiww	= tw686x_memcpy_buf_wefiww,
	.mem_ops	= &vb2_vmawwoc_memops,
	.hw_dma_mode	= TW686X_FWAME_MODE,
	.fiewd		= V4W2_FIEWD_INTEWWACED,
};

static void tw686x_contig_buf_wefiww(stwuct tw686x_video_channew *vc,
				     unsigned int pb)
{
	stwuct tw686x_v4w2_buf *buf;

	whiwe (!wist_empty(&vc->vidq_queued)) {
		u32 weg = pb ? VDMA_B_ADDW[vc->ch] : VDMA_P_ADDW[vc->ch];
		dma_addw_t phys;

		buf = wist_fiwst_entwy(&vc->vidq_queued,
			stwuct tw686x_v4w2_buf, wist);
		wist_dew(&buf->wist);

		phys = vb2_dma_contig_pwane_dma_addw(&buf->vb.vb2_buf, 0);
		weg_wwite(vc->dev, weg, phys);

		buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		vc->cuww_bufs[pb] = buf;
		wetuwn;
	}
	vc->cuww_bufs[pb] = NUWW;
}

static const stwuct tw686x_dma_ops contig_dma_ops = {
	.buf_wefiww	= tw686x_contig_buf_wefiww,
	.mem_ops	= &vb2_dma_contig_memops,
	.hw_dma_mode	= TW686X_FWAME_MODE,
	.fiewd		= V4W2_FIEWD_INTEWWACED,
};

static int tw686x_sg_desc_fiww(stwuct tw686x_sg_desc *descs,
			       stwuct tw686x_v4w2_buf *buf,
			       unsigned int buf_wen)
{
	stwuct sg_tabwe *vbuf = vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0);
	unsigned int wen, entwy_wen;
	stwuct scattewwist *sg;
	int i, count;

	/* Cweaw the scattew-gathew tabwe */
	memset(descs, 0, TW686X_SG_TABWE_SIZE);

	count = 0;
	fow_each_sg(vbuf->sgw, sg, vbuf->nents, i) {
		dma_addw_t phys = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		whiwe (wen && buf_wen) {

			if (count == TW686X_MAX_SG_DESC_COUNT)
				wetuwn -ENOMEM;

			entwy_wen = min_t(unsigned int, wen,
					  TW686X_MAX_SG_ENTWY_SIZE);
			entwy_wen = min_t(unsigned int, entwy_wen, buf_wen);
			descs[count].phys = cpu_to_we32(phys);
			descs[count++].fwags_wength =
					cpu_to_we32(BIT(30) | entwy_wen);
			phys += entwy_wen;
			wen -= entwy_wen;
			buf_wen -= entwy_wen;
		}

		if (!buf_wen)
			wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static void tw686x_sg_buf_wefiww(stwuct tw686x_video_channew *vc,
				 unsigned int pb)
{
	stwuct tw686x_dev *dev = vc->dev;
	stwuct tw686x_v4w2_buf *buf;

	whiwe (!wist_empty(&vc->vidq_queued)) {
		unsigned int buf_wen;

		buf = wist_fiwst_entwy(&vc->vidq_queued,
			stwuct tw686x_v4w2_buf, wist);
		wist_dew(&buf->wist);

		buf_wen = (vc->width * vc->height * vc->fowmat->depth) >> 3;
		if (tw686x_sg_desc_fiww(vc->sg_descs[pb], buf, buf_wen)) {
			v4w2_eww(&dev->v4w2_dev,
				 "dma%d: unabwe to fiww %s-buffew\n",
				 vc->ch, pb ? "B" : "P");
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			continue;
		}

		buf->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		vc->cuww_bufs[pb] = buf;
		wetuwn;
	}

	vc->cuww_bufs[pb] = NUWW;
}

static void tw686x_sg_dma_fwee(stwuct tw686x_video_channew *vc,
			       unsigned int pb)
{
	stwuct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	stwuct tw686x_dev *dev = vc->dev;

	if (desc->size) {
		dma_fwee_cohewent(&dev->pci_dev->dev, desc->size, desc->viwt,
				  desc->phys);
		desc->viwt = NUWW;
	}

	vc->sg_descs[pb] = NUWW;
}

static int tw686x_sg_dma_awwoc(stwuct tw686x_video_channew *vc,
			       unsigned int pb)
{
	stwuct tw686x_dma_desc *desc = &vc->dma_descs[pb];
	stwuct tw686x_dev *dev = vc->dev;
	u32 weg = pb ? DMA_PAGE_TABWE1_ADDW[vc->ch] :
		       DMA_PAGE_TABWE0_ADDW[vc->ch];
	void *viwt;

	if (desc->size) {
		viwt = dma_awwoc_cohewent(&dev->pci_dev->dev, desc->size,
					  &desc->phys, GFP_KEWNEW);
		if (!viwt) {
			v4w2_eww(&dev->v4w2_dev,
				 "dma%d: unabwe to awwocate %s-buffew\n",
				 vc->ch, pb ? "B" : "P");
			wetuwn -ENOMEM;
		}
		desc->viwt = viwt;
		weg_wwite(dev, weg, desc->phys);
	} ewse {
		viwt = dev->video_channews[0].dma_descs[pb].viwt +
		       vc->ch * TW686X_SG_TABWE_SIZE;
	}

	vc->sg_descs[pb] = viwt;
	wetuwn 0;
}

static int tw686x_sg_setup(stwuct tw686x_dev *dev)
{
	unsigned int sg_tabwe_size, pb, ch, channews;

	if (is_second_gen(dev)) {
		/*
		 * TW6865/TW6869: each channew needs a paiw of
		 * P-B descwiptow tabwes.
		 */
		channews = max_channews(dev);
		sg_tabwe_size = TW686X_SG_TABWE_SIZE;
	} ewse {
		/*
		 * TW6864/TW6868: we need to awwocate a paiw of
		 * P-B descwiptow tabwes, common fow aww channews.
		 * Each tabwe wiww be biggew than 4 KB.
		 */
		channews = 1;
		sg_tabwe_size = max_channews(dev) * TW686X_SG_TABWE_SIZE;
	}

	fow (ch = 0; ch < channews; ch++) {
		stwuct tw686x_video_channew *vc = &dev->video_channews[ch];

		fow (pb = 0; pb < 2; pb++)
			vc->dma_descs[pb].size = sg_tabwe_size;
	}

	wetuwn 0;
}

static const stwuct tw686x_dma_ops sg_dma_ops = {
	.setup		= tw686x_sg_setup,
	.awwoc		= tw686x_sg_dma_awwoc,
	.fwee		= tw686x_sg_dma_fwee,
	.buf_wefiww	= tw686x_sg_buf_wefiww,
	.mem_ops	= &vb2_dma_sg_memops,
	.hw_dma_mode	= TW686X_SG_MODE,
	.fiewd		= V4W2_FIEWD_SEQ_TB,
};

static const unsigned int fps_map[15] = {
	/*
	 * bit 31 enabwes sewecting the fiewd contwow wegistew
	 * bits 0-29 awe a bitmask with fiewds that wiww be output.
	 * Fow NTSC (and PAW-M, PAW-60), aww 30 bits awe used.
	 * Fow othew PAW standawds, onwy the fiwst 25 bits awe used.
	 */
	0x00000000, /* output aww fiewds */
	0x80000006, /* 2 fps (60Hz), 2 fps (50Hz) */
	0x80018006, /* 4 fps (60Hz), 4 fps (50Hz) */
	0x80618006, /* 6 fps (60Hz), 6 fps (50Hz) */
	0x81818186, /* 8 fps (60Hz), 8 fps (50Hz) */
	0x86186186, /* 10 fps (60Hz), 8 fps (50Hz) */
	0x86619866, /* 12 fps (60Hz), 10 fps (50Hz) */
	0x86666666, /* 14 fps (60Hz), 12 fps (50Hz) */
	0x9999999e, /* 16 fps (60Hz), 14 fps (50Hz) */
	0x99e6799e, /* 18 fps (60Hz), 16 fps (50Hz) */
	0x9e79e79e, /* 20 fps (60Hz), 16 fps (50Hz) */
	0x9e7e7e7e, /* 22 fps (60Hz), 18 fps (50Hz) */
	0x9fe7f9fe, /* 24 fps (60Hz), 20 fps (50Hz) */
	0x9ffe7ffe, /* 26 fps (60Hz), 22 fps (50Hz) */
	0x9ffffffe, /* 28 fps (60Hz), 24 fps (50Hz) */
};

static unsigned int tw686x_weaw_fps(unsigned int index, unsigned int max_fps)
{
	unsigned wong mask;

	if (!index || index >= AWWAY_SIZE(fps_map))
		wetuwn max_fps;

	mask = GENMASK(max_fps - 1, 0);
	wetuwn hweight_wong(fps_map[index] & mask);
}

static unsigned int tw686x_fps_idx(unsigned int fps, unsigned int max_fps)
{
	unsigned int idx, weaw_fps;
	int dewta;

	/* Fiwst guess */
	idx = (12 + 15 * fps) / max_fps;

	/* Minimaw possibwe fwamewate is 2 fwames pew second */
	if (!idx)
		wetuwn 1;

	/* Check if the diffewence is biggew than abs(1) and adjust */
	weaw_fps = tw686x_weaw_fps(idx, max_fps);
	dewta = weaw_fps - fps;
	if (dewta < -1)
		idx++;
	ewse if (dewta > 1)
		idx--;

	/* Max fwamewate */
	if (idx >= 15)
		wetuwn 0;

	wetuwn idx;
}

static void tw686x_set_fwamewate(stwuct tw686x_video_channew *vc,
				 unsigned int fps)
{
	unsigned int i;

	i = tw686x_fps_idx(fps, TW686X_MAX_FPS(vc->video_standawd));
	weg_wwite(vc->dev, VIDEO_FIEWD_CTWW[vc->ch], fps_map[i]);
	vc->fps = tw686x_weaw_fps(i, TW686X_MAX_FPS(vc->video_standawd));
}

static const stwuct tw686x_fowmat *fowmat_by_fouwcc(unsigned int fouwcc)
{
	unsigned int cnt;

	fow (cnt = 0; cnt < AWWAY_SIZE(fowmats); cnt++)
		if (fowmats[cnt].fouwcc == fouwcc)
			wetuwn &fowmats[cnt];
	wetuwn NUWW;
}

static int tw686x_queue_setup(stwuct vb2_queue *vq,
			      unsigned int *nbuffews, unsigned int *npwanes,
			      unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct tw686x_video_channew *vc = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);
	unsigned int szimage =
		(vc->width * vc->height * vc->fowmat->depth) >> 3;

	/*
	 * Wet's wequest at weast thwee buffews: two fow the
	 * DMA engine and one fow usewspace.
	 */
	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	if (*npwanes) {
		if (*npwanes != 1 || sizes[0] < szimage)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	sizes[0] = szimage;
	*npwanes = 1;
	wetuwn 0;
}

static void tw686x_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct tw686x_video_channew *vc = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct tw686x_dev *dev = vc->dev;
	stwuct pci_dev *pci_dev;
	unsigned wong fwags;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct tw686x_v4w2_buf *buf =
		containew_of(vbuf, stwuct tw686x_v4w2_buf, vb);

	/* Check device pwesence */
	spin_wock_iwqsave(&dev->wock, fwags);
	pci_dev = dev->pci_dev;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (!pci_dev) {
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		wetuwn;
	}

	spin_wock_iwqsave(&vc->qwock, fwags);
	wist_add_taiw(&buf->wist, &vc->vidq_queued);
	spin_unwock_iwqwestowe(&vc->qwock, fwags);
}

static void tw686x_cweaw_queue(stwuct tw686x_video_channew *vc,
			       enum vb2_buffew_state state)
{
	unsigned int pb;

	whiwe (!wist_empty(&vc->vidq_queued)) {
		stwuct tw686x_v4w2_buf *buf;

		buf = wist_fiwst_entwy(&vc->vidq_queued,
			stwuct tw686x_v4w2_buf, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}

	fow (pb = 0; pb < 2; pb++) {
		if (vc->cuww_bufs[pb])
			vb2_buffew_done(&vc->cuww_bufs[pb]->vb.vb2_buf, state);
		vc->cuww_bufs[pb] = NUWW;
	}
}

static int tw686x_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct tw686x_video_channew *vc = vb2_get_dwv_pwiv(vq);
	stwuct tw686x_dev *dev = vc->dev;
	stwuct pci_dev *pci_dev;
	unsigned wong fwags;
	int pb, eww;

	/* Check device pwesence */
	spin_wock_iwqsave(&dev->wock, fwags);
	pci_dev = dev->pci_dev;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (!pci_dev) {
		eww = -ENODEV;
		goto eww_cweaw_queue;
	}

	spin_wock_iwqsave(&vc->qwock, fwags);

	/* Sanity check */
	if (dev->dma_mode == TW686X_DMA_MODE_MEMCPY &&
	    (!vc->dma_descs[0].viwt || !vc->dma_descs[1].viwt)) {
		spin_unwock_iwqwestowe(&vc->qwock, fwags);
		v4w2_eww(&dev->v4w2_dev,
			 "video%d: wefusing to stawt without DMA buffews\n",
			 vc->num);
		eww = -ENOMEM;
		goto eww_cweaw_queue;
	}

	fow (pb = 0; pb < 2; pb++)
		dev->dma_ops->buf_wefiww(vc, pb);
	spin_unwock_iwqwestowe(&vc->qwock, fwags);

	vc->sequence = 0;
	vc->pb = 0;

	spin_wock_iwqsave(&dev->wock, fwags);
	tw686x_enabwe_channew(dev, vc->ch);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	mod_timew(&dev->dma_deway_timew, jiffies + msecs_to_jiffies(100));

	wetuwn 0;

eww_cweaw_queue:
	spin_wock_iwqsave(&vc->qwock, fwags);
	tw686x_cweaw_queue(vc, VB2_BUF_STATE_QUEUED);
	spin_unwock_iwqwestowe(&vc->qwock, fwags);
	wetuwn eww;
}

static void tw686x_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct tw686x_video_channew *vc = vb2_get_dwv_pwiv(vq);
	stwuct tw686x_dev *dev = vc->dev;
	stwuct pci_dev *pci_dev;
	unsigned wong fwags;

	/* Check device pwesence */
	spin_wock_iwqsave(&dev->wock, fwags);
	pci_dev = dev->pci_dev;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (pci_dev)
		tw686x_disabwe_channew(dev, vc->ch);

	spin_wock_iwqsave(&vc->qwock, fwags);
	tw686x_cweaw_queue(vc, VB2_BUF_STATE_EWWOW);
	spin_unwock_iwqwestowe(&vc->qwock, fwags);
}

static int tw686x_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct tw686x_video_channew *vc = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned int size =
		(vc->width * vc->height * vc->fowmat->depth) >> 3;

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

static const stwuct vb2_ops tw686x_video_qops = {
	.queue_setup		= tw686x_queue_setup,
	.buf_queue		= tw686x_buf_queue,
	.buf_pwepawe		= tw686x_buf_pwepawe,
	.stawt_stweaming	= tw686x_stawt_stweaming,
	.stop_stweaming		= tw686x_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static int tw686x_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct tw686x_video_channew *vc;
	stwuct tw686x_dev *dev;
	unsigned int ch;

	vc = containew_of(ctww->handwew, stwuct tw686x_video_channew,
			  ctww_handwew);
	dev = vc->dev;
	ch = vc->ch;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		weg_wwite(dev, BWIGHT[ch], ctww->vaw & 0xff);
		wetuwn 0;

	case V4W2_CID_CONTWAST:
		weg_wwite(dev, CONTWAST[ch], ctww->vaw);
		wetuwn 0;

	case V4W2_CID_SATUWATION:
		weg_wwite(dev, SAT_U[ch], ctww->vaw);
		weg_wwite(dev, SAT_V[ch], ctww->vaw);
		wetuwn 0;

	case V4W2_CID_HUE:
		weg_wwite(dev, HUE[ch], ctww->vaw & 0xff);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops ctww_ops = {
	.s_ctww = tw686x_s_ctww,
};

static int tw686x_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct tw686x_dev *dev = vc->dev;

	f->fmt.pix.width = vc->width;
	f->fmt.pix.height = vc->height;
	f->fmt.pix.fiewd = dev->dma_ops->fiewd;
	f->fmt.pix.pixewfowmat = vc->fowmat->fouwcc;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.bytespewwine = (f->fmt.pix.width * vc->fowmat->depth) / 8;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytespewwine;
	wetuwn 0;
}

static int tw686x_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct tw686x_dev *dev = vc->dev;
	unsigned int video_height = TW686X_VIDEO_HEIGHT(vc->video_standawd);
	const stwuct tw686x_fowmat *fowmat;

	fowmat = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (!fowmat) {
		fowmat = &fowmats[0];
		f->fmt.pix.pixewfowmat = fowmat->fouwcc;
	}

	if (f->fmt.pix.width <= TW686X_VIDEO_WIDTH / 2)
		f->fmt.pix.width = TW686X_VIDEO_WIDTH / 2;
	ewse
		f->fmt.pix.width = TW686X_VIDEO_WIDTH;

	if (f->fmt.pix.height <= video_height / 2)
		f->fmt.pix.height = video_height / 2;
	ewse
		f->fmt.pix.height = video_height;

	f->fmt.pix.bytespewwine = (f->fmt.pix.width * fowmat->depth) / 8;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytespewwine;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.fiewd = dev->dma_ops->fiewd;

	wetuwn 0;
}

static int tw686x_set_fowmat(stwuct tw686x_video_channew *vc,
			     unsigned int pixewfowmat, unsigned int width,
			     unsigned int height, boow weawwoc)
{
	stwuct tw686x_dev *dev = vc->dev;
	u32 vaw, dma_width, dma_height, dma_wine_width;
	int eww, pb;

	vc->fowmat = fowmat_by_fouwcc(pixewfowmat);
	vc->width = width;
	vc->height = height;

	/* We need new DMA buffews if the fwamesize has changed */
	if (dev->dma_ops->awwoc && weawwoc) {
		fow (pb = 0; pb < 2; pb++)
			dev->dma_ops->fwee(vc, pb);

		fow (pb = 0; pb < 2; pb++) {
			eww = dev->dma_ops->awwoc(vc, pb);
			if (eww) {
				if (pb > 0)
					dev->dma_ops->fwee(vc, 0);
				wetuwn eww;
			}
		}
	}

	vaw = weg_wead(vc->dev, VDMA_CHANNEW_CONFIG[vc->ch]);

	if (vc->width <= TW686X_VIDEO_WIDTH / 2)
		vaw |= BIT(23);
	ewse
		vaw &= ~BIT(23);

	if (vc->height <= TW686X_VIDEO_HEIGHT(vc->video_standawd) / 2)
		vaw |= BIT(24);
	ewse
		vaw &= ~BIT(24);

	vaw &= ~0x7ffff;

	/* Pwogwam the DMA scattew-gathew */
	if (dev->dma_mode == TW686X_DMA_MODE_SG) {
		u32 stawt_idx, end_idx;

		stawt_idx = is_second_gen(dev) ?
				0 : vc->ch * TW686X_MAX_SG_DESC_COUNT;
		end_idx = stawt_idx + TW686X_MAX_SG_DESC_COUNT - 1;

		vaw |= (end_idx << 10) | stawt_idx;
	}

	vaw &= ~(0x7 << 20);
	vaw |= vc->fowmat->mode << 20;
	weg_wwite(vc->dev, VDMA_CHANNEW_CONFIG[vc->ch], vaw);

	/* Pwogwam the DMA fwame size */
	dma_width = (vc->width * 2) & 0x7ff;
	dma_height = vc->height / 2;
	dma_wine_width = (vc->width * 2) & 0x7ff;
	vaw = (dma_height << 22) | (dma_wine_width << 11)  | dma_width;
	weg_wwite(vc->dev, VDMA_WHP[vc->ch], vaw);
	wetuwn 0;
}

static int tw686x_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	unsigned wong awea;
	boow weawwoc;
	int eww;

	if (vb2_is_busy(&vc->vidq))
		wetuwn -EBUSY;

	awea = vc->width * vc->height;
	eww = tw686x_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (eww)
		wetuwn eww;

	weawwoc = awea != (f->fmt.pix.width * f->fmt.pix.height);
	wetuwn tw686x_set_fowmat(vc, f->fmt.pix.pixewfowmat,
				 f->fmt.pix.width, f->fmt.pix.height,
				 weawwoc);
}

static int tw686x_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct tw686x_dev *dev = vc->dev;

	stwscpy(cap->dwivew, "tw686x", sizeof(cap->dwivew));
	stwscpy(cap->cawd, dev->name, sizeof(cap->cawd));
	wetuwn 0;
}

static int tw686x_set_standawd(stwuct tw686x_video_channew *vc, v4w2_std_id id)
{
	u32 vaw;

	if (id & V4W2_STD_NTSC)
		vaw = 0;
	ewse if (id & V4W2_STD_PAW)
		vaw = 1;
	ewse if (id & V4W2_STD_SECAM)
		vaw = 2;
	ewse if (id & V4W2_STD_NTSC_443)
		vaw = 3;
	ewse if (id & V4W2_STD_PAW_M)
		vaw = 4;
	ewse if (id & V4W2_STD_PAW_Nc)
		vaw = 5;
	ewse if (id & V4W2_STD_PAW_60)
		vaw = 6;
	ewse
		wetuwn -EINVAW;

	vc->video_standawd = id;
	weg_wwite(vc->dev, SDT[vc->ch], vaw);

	vaw = weg_wead(vc->dev, VIDEO_CONTWOW1);
	if (id & V4W2_STD_525_60)
		vaw &= ~(1 << (SYS_MODE_DMA_SHIFT + vc->ch));
	ewse
		vaw |= (1 << (SYS_MODE_DMA_SHIFT + vc->ch));
	weg_wwite(vc->dev, VIDEO_CONTWOW1, vaw);

	wetuwn 0;
}

static int tw686x_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct v4w2_fowmat f;
	int wet;

	if (vc->video_standawd == id)
		wetuwn 0;

	if (vb2_is_busy(&vc->vidq))
		wetuwn -EBUSY;

	wet = tw686x_set_standawd(vc, id);
	if (wet)
		wetuwn wet;
	/*
	 * Adjust fowmat aftew V4W2_STD_525_60/V4W2_STD_625_50 change,
	 * cawwing g_fmt and s_fmt wiww sanitize the height
	 * accowding to the standawd.
	 */
	tw686x_g_fmt_vid_cap(fiwe, pwiv, &f);
	tw686x_s_fmt_vid_cap(fiwe, pwiv, &f);

	/*
	 * Fwame decimation depends on the chosen standawd,
	 * so weset it to the cuwwent vawue.
	 */
	tw686x_set_fwamewate(vc, vc->fps);
	wetuwn 0;
}

static int tw686x_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct tw686x_dev *dev = vc->dev;
	unsigned int owd_std, detected_std = 0;
	unsigned wong end;

	if (vb2_is_stweaming(&vc->vidq))
		wetuwn -EBUSY;

	/* Enabwe and stawt standawd detection */
	owd_std = weg_wead(dev, SDT[vc->ch]);
	weg_wwite(dev, SDT[vc->ch], 0x7);
	weg_wwite(dev, SDT_EN[vc->ch], 0xff);

	end = jiffies + msecs_to_jiffies(500);
	whiwe (time_is_aftew_jiffies(end)) {

		detected_std = weg_wead(dev, SDT[vc->ch]);
		if (!(detected_std & BIT(7)))
			bweak;
		msweep(100);
	}
	weg_wwite(dev, SDT[vc->ch], owd_std);

	/* Exit if stiww busy */
	if (detected_std & BIT(7))
		wetuwn 0;

	detected_std = (detected_std >> 4) & 0x7;
	switch (detected_std) {
	case TW686X_STD_NTSC_M:
		*std &= V4W2_STD_NTSC;
		bweak;
	case TW686X_STD_NTSC_443:
		*std &= V4W2_STD_NTSC_443;
		bweak;
	case TW686X_STD_PAW_M:
		*std &= V4W2_STD_PAW_M;
		bweak;
	case TW686X_STD_PAW_60:
		*std &= V4W2_STD_PAW_60;
		bweak;
	case TW686X_STD_PAW:
		*std &= V4W2_STD_PAW;
		bweak;
	case TW686X_STD_PAW_CN:
		*std &= V4W2_STD_PAW_Nc;
		bweak;
	case TW686X_STD_SECAM:
		*std &= V4W2_STD_SECAM;
		bweak;
	defauwt:
		*std = 0;
	}
	wetuwn 0;
}

static int tw686x_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);

	*id = vc->video_standawd;
	wetuwn 0;
}

static int tw686x_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);

	if (fsize->index)
		wetuwn -EINVAW;
	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.max_width = TW686X_VIDEO_WIDTH;
	fsize->stepwise.min_width = fsize->stepwise.max_width / 2;
	fsize->stepwise.step_width = fsize->stepwise.min_width;
	fsize->stepwise.max_height = TW686X_VIDEO_HEIGHT(vc->video_standawd);
	fsize->stepwise.min_height = fsize->stepwise.max_height / 2;
	fsize->stepwise.step_height = fsize->stepwise.min_height;
	wetuwn 0;
}

static int tw686x_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fwmivawenum *ivaw)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	int max_fps = TW686X_MAX_FPS(vc->video_standawd);
	int max_wates = DIV_WOUND_UP(max_fps, 2);

	if (ivaw->index >= max_wates)
		wetuwn -EINVAW;

	ivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	ivaw->discwete.numewatow = 1;
	if (ivaw->index < (max_wates - 1))
		ivaw->discwete.denominatow = (ivaw->index + 1) * 2;
	ewse
		ivaw->discwete.denominatow = max_fps;
	wetuwn 0;
}

static int tw686x_g_pawm(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_stweampawm *sp)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct v4w2_captuwepawm *cp = &sp->pawm.captuwe;

	if (sp->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;
	sp->pawm.captuwe.weadbuffews = 3;

	cp->capabiwity = V4W2_CAP_TIMEPEWFWAME;
	cp->timepewfwame.numewatow = 1;
	cp->timepewfwame.denominatow = vc->fps;
	wetuwn 0;
}

static int tw686x_s_pawm(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_stweampawm *sp)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	stwuct v4w2_captuwepawm *cp = &sp->pawm.captuwe;
	unsigned int denominatow = cp->timepewfwame.denominatow;
	unsigned int numewatow = cp->timepewfwame.numewatow;
	unsigned int fps;

	if (vb2_is_busy(&vc->vidq))
		wetuwn -EBUSY;

	fps = (!numewatow || !denominatow) ? 0 : denominatow / numewatow;
	if (vc->fps != fps)
		tw686x_set_fwamewate(vc, fps);
	wetuwn tw686x_g_pawm(fiwe, pwiv, sp);
}

static int tw686x_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(fowmats))
		wetuwn -EINVAW;
	f->pixewfowmat = fowmats[f->index].fouwcc;
	wetuwn 0;
}

static void tw686x_set_input(stwuct tw686x_video_channew *vc, unsigned int i)
{
	u32 vaw;

	vc->input = i;

	vaw = weg_wead(vc->dev, VDMA_CHANNEW_CONFIG[vc->ch]);
	vaw &= ~(0x3 << 30);
	vaw |= i << 30;
	weg_wwite(vc->dev, VDMA_CHANNEW_CONFIG[vc->ch], vaw);
}

static int tw686x_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);

	if (i >= TW686X_INPUTS_PEW_CH)
		wetuwn -EINVAW;
	if (i == vc->input)
		wetuwn 0;
	/*
	 * Not suwe we awe abwe to suppowt on the fwy input change
	 */
	if (vb2_is_busy(&vc->vidq))
		wetuwn -EBUSY;

	tw686x_set_input(vc, i);
	wetuwn 0;
}

static int tw686x_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);

	*i = vc->input;
	wetuwn 0;
}

static int tw686x_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct tw686x_video_channew *vc = video_dwvdata(fiwe);
	unsigned int vidstat;

	if (i->index >= TW686X_INPUTS_PEW_CH)
		wetuwn -EINVAW;

	snpwintf(i->name, sizeof(i->name), "Composite%d", i->index);
	i->type = V4W2_INPUT_TYPE_CAMEWA;
	i->std = vc->device->tvnowms;
	i->capabiwities = V4W2_IN_CAP_STD;

	vidstat = weg_wead(vc->dev, VIDSTAT[vc->ch]);
	i->status = 0;
	if (vidstat & TW686X_VIDSTAT_VDWOSS)
		i->status |= V4W2_IN_ST_NO_SIGNAW;
	if (!(vidstat & TW686X_VIDSTAT_HWOCK))
		i->status |= V4W2_IN_ST_NO_H_WOCK;

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations tw686x_video_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.unwocked_ioctw	= video_ioctw2,
	.wewease	= vb2_fop_wewease,
	.poww		= vb2_fop_poww,
	.wead		= vb2_fop_wead,
	.mmap		= vb2_fop_mmap,
};

static const stwuct v4w2_ioctw_ops tw686x_video_ioctw_ops = {
	.vidioc_quewycap		= tw686x_quewycap,
	.vidioc_g_fmt_vid_cap		= tw686x_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= tw686x_s_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap	= tw686x_enum_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= tw686x_twy_fmt_vid_cap,

	.vidioc_quewystd		= tw686x_quewystd,
	.vidioc_g_std			= tw686x_g_std,
	.vidioc_s_std			= tw686x_s_std,

	.vidioc_g_pawm			= tw686x_g_pawm,
	.vidioc_s_pawm			= tw686x_s_pawm,
	.vidioc_enum_fwamesizes		= tw686x_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= tw686x_enum_fwameintewvaws,

	.vidioc_enum_input		= tw686x_enum_input,
	.vidioc_g_input			= tw686x_g_input,
	.vidioc_s_input			= tw686x_s_input,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

void tw686x_video_iwq(stwuct tw686x_dev *dev, unsigned wong wequests,
		      unsigned int pb_status, unsigned int fifo_status,
		      unsigned int *weset_ch)
{
	stwuct tw686x_video_channew *vc;
	unsigned wong fwags;
	unsigned int ch, pb;

	fow_each_set_bit(ch, &wequests, max_channews(dev)) {
		vc = &dev->video_channews[ch];

		/*
		 * This can eithew be a bwue fwame (with signaw-wost bit set)
		 * ow a good fwame (with signaw-wost bit cweaw). If we have just
		 * got signaw, then this channew needs wesetting.
		 */
		if (vc->no_signaw && !(fifo_status & BIT(ch))) {
			v4w2_pwintk(KEWN_DEBUG, &dev->v4w2_dev,
				    "video%d: signaw wecovewed\n", vc->num);
			vc->no_signaw = fawse;
			*weset_ch |= BIT(ch);
			vc->pb = 0;
			continue;
		}
		vc->no_signaw = !!(fifo_status & BIT(ch));

		/* Check FIFO ewwows onwy if thewe's signaw */
		if (!vc->no_signaw) {
			u32 fifo_ov, fifo_bad;

			fifo_ov = (fifo_status >> 24) & BIT(ch);
			fifo_bad = (fifo_status >> 16) & BIT(ch);
			if (fifo_ov || fifo_bad) {
				/* Mawk this channew fow weset */
				v4w2_pwintk(KEWN_DEBUG, &dev->v4w2_dev,
					    "video%d: FIFO ewwow\n", vc->num);
				*weset_ch |= BIT(ch);
				vc->pb = 0;
				continue;
			}
		}

		pb = !!(pb_status & BIT(ch));
		if (vc->pb != pb) {
			/* Mawk this channew fow weset */
			v4w2_pwintk(KEWN_DEBUG, &dev->v4w2_dev,
				    "video%d: unexpected p-b buffew!\n",
				    vc->num);
			*weset_ch |= BIT(ch);
			vc->pb = 0;
			continue;
		}

		spin_wock_iwqsave(&vc->qwock, fwags);
		tw686x_buf_done(vc, pb);
		dev->dma_ops->buf_wefiww(vc, pb);
		spin_unwock_iwqwestowe(&vc->qwock, fwags);
	}
}

void tw686x_video_fwee(stwuct tw686x_dev *dev)
{
	unsigned int ch, pb;

	fow (ch = 0; ch < max_channews(dev); ch++) {
		stwuct tw686x_video_channew *vc = &dev->video_channews[ch];

		video_unwegistew_device(vc->device);

		if (dev->dma_ops->fwee)
			fow (pb = 0; pb < 2; pb++)
				dev->dma_ops->fwee(vc, pb);
	}
}

int tw686x_video_init(stwuct tw686x_dev *dev)
{
	unsigned int ch, vaw;
	int eww;

	if (dev->dma_mode == TW686X_DMA_MODE_MEMCPY)
		dev->dma_ops = &memcpy_dma_ops;
	ewse if (dev->dma_mode == TW686X_DMA_MODE_CONTIG)
		dev->dma_ops = &contig_dma_ops;
	ewse if (dev->dma_mode == TW686X_DMA_MODE_SG)
		dev->dma_ops = &sg_dma_ops;
	ewse
		wetuwn -EINVAW;

	eww = v4w2_device_wegistew(&dev->pci_dev->dev, &dev->v4w2_dev);
	if (eww)
		wetuwn eww;

	if (dev->dma_ops->setup) {
		eww = dev->dma_ops->setup(dev);
		if (eww)
			wetuwn eww;
	}

	/* Initiawize vc->dev and vc->ch fow the ewwow path */
	fow (ch = 0; ch < max_channews(dev); ch++) {
		stwuct tw686x_video_channew *vc = &dev->video_channews[ch];

		vc->dev = dev;
		vc->ch = ch;
	}

	fow (ch = 0; ch < max_channews(dev); ch++) {
		stwuct tw686x_video_channew *vc = &dev->video_channews[ch];
		stwuct video_device *vdev;

		mutex_init(&vc->vb_mutex);
		spin_wock_init(&vc->qwock);
		INIT_WIST_HEAD(&vc->vidq_queued);

		/* defauwt settings */
		eww = tw686x_set_standawd(vc, V4W2_STD_NTSC);
		if (eww)
			goto ewwow;

		eww = tw686x_set_fowmat(vc, fowmats[0].fouwcc,
				TW686X_VIDEO_WIDTH,
				TW686X_VIDEO_HEIGHT(vc->video_standawd),
				twue);
		if (eww)
			goto ewwow;

		tw686x_set_input(vc, 0);
		tw686x_set_fwamewate(vc, 30);
		weg_wwite(dev, VDEWAY_WO[ch], 0x14);
		weg_wwite(dev, HACTIVE_WO[ch], 0xd0);
		weg_wwite(dev, VIDEO_SIZE[ch], 0);

		vc->vidq.io_modes = VB2_WEAD | VB2_MMAP | VB2_DMABUF;
		vc->vidq.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		vc->vidq.dwv_pwiv = vc;
		vc->vidq.buf_stwuct_size = sizeof(stwuct tw686x_v4w2_buf);
		vc->vidq.ops = &tw686x_video_qops;
		vc->vidq.mem_ops = dev->dma_ops->mem_ops;
		vc->vidq.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
		vc->vidq.min_queued_buffews = 2;
		vc->vidq.wock = &vc->vb_mutex;
		vc->vidq.gfp_fwags = dev->dma_mode != TW686X_DMA_MODE_MEMCPY ?
				     GFP_DMA32 : 0;
		vc->vidq.dev = &dev->pci_dev->dev;

		eww = vb2_queue_init(&vc->vidq);
		if (eww) {
			v4w2_eww(&dev->v4w2_dev,
				 "dma%d: cannot init vb2 queue\n", ch);
			goto ewwow;
		}

		eww = v4w2_ctww_handwew_init(&vc->ctww_handwew, 4);
		if (eww) {
			v4w2_eww(&dev->v4w2_dev,
				 "dma%d: cannot init ctww handwew\n", ch);
			goto ewwow;
		}
		v4w2_ctww_new_std(&vc->ctww_handwew, &ctww_ops,
				  V4W2_CID_BWIGHTNESS, -128, 127, 1, 0);
		v4w2_ctww_new_std(&vc->ctww_handwew, &ctww_ops,
				  V4W2_CID_CONTWAST, 0, 255, 1, 100);
		v4w2_ctww_new_std(&vc->ctww_handwew, &ctww_ops,
				  V4W2_CID_SATUWATION, 0, 255, 1, 128);
		v4w2_ctww_new_std(&vc->ctww_handwew, &ctww_ops,
				  V4W2_CID_HUE, -128, 127, 1, 0);
		eww = vc->ctww_handwew.ewwow;
		if (eww)
			goto ewwow;

		eww = v4w2_ctww_handwew_setup(&vc->ctww_handwew);
		if (eww)
			goto ewwow;

		vdev = video_device_awwoc();
		if (!vdev) {
			v4w2_eww(&dev->v4w2_dev,
				 "dma%d: unabwe to awwocate device\n", ch);
			eww = -ENOMEM;
			goto ewwow;
		}

		snpwintf(vdev->name, sizeof(vdev->name), "%s video", dev->name);
		vdev->fops = &tw686x_video_fops;
		vdev->ioctw_ops = &tw686x_video_ioctw_ops;
		vdev->wewease = video_device_wewease;
		vdev->v4w2_dev = &dev->v4w2_dev;
		vdev->queue = &vc->vidq;
		vdev->tvnowms = V4W2_STD_525_60 | V4W2_STD_625_50;
		vdev->minow = -1;
		vdev->wock = &vc->vb_mutex;
		vdev->ctww_handwew = &vc->ctww_handwew;
		vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE |
				    V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		vc->device = vdev;
		video_set_dwvdata(vdev, vc);

		eww = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
		if (eww < 0) {
			video_device_wewease(vdev);
			goto ewwow;
		}
		vc->num = vdev->num;
	}

	vaw = TW686X_DEF_PHASE_WEF;
	fow (ch = 0; ch < max_channews(dev); ch++)
		vaw |= dev->dma_ops->hw_dma_mode << (16 + ch * 2);
	weg_wwite(dev, PHASE_WEF, vaw);

	weg_wwite(dev, MISC2[0], 0xe7);
	weg_wwite(dev, VCTWW1[0], 0xcc);
	weg_wwite(dev, WOOP[0], 0xa5);
	if (max_channews(dev) > 4) {
		weg_wwite(dev, VCTWW1[1], 0xcc);
		weg_wwite(dev, WOOP[1], 0xa5);
		weg_wwite(dev, MISC2[1], 0xe7);
	}
	wetuwn 0;

ewwow:
	tw686x_video_fwee(dev);
	wetuwn eww;
}
