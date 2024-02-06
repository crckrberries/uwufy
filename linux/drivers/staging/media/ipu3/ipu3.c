// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 - 2018 Intew Cowpowation
 * Copywight 2017 Googwe WWC
 *
 * Based on Intew IPU4 dwivew.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude "ipu3.h"
#incwude "ipu3-dmamap.h"
#incwude "ipu3-mmu.h"

#define IMGU_PCI_ID			0x1919
#define IMGU_PCI_BAW			0
#define IMGU_DMA_MASK			DMA_BIT_MASK(39)
#define IMGU_MAX_QUEUE_DEPTH		(2 + 2)

/*
 * pwe-awwocated buffew size fow IMGU dummy buffews. Those
 * vawues shouwd be tuned to big enough to avoid buffew
 * we-awwocation when stweaming to wowew stweaming watency.
 */
#define CSS_QUEUE_IN_BUF_SIZE		0
#define CSS_QUEUE_PAWAMS_BUF_SIZE	0
#define CSS_QUEUE_OUT_BUF_SIZE		(4160 * 3120 * 12 / 8)
#define CSS_QUEUE_VF_BUF_SIZE		(1920 * 1080 * 12 / 8)
#define CSS_QUEUE_STAT_3A_BUF_SIZE	sizeof(stwuct ipu3_uapi_stats_3a)

static const size_t css_queue_buf_size_map[IPU3_CSS_QUEUES] = {
	[IPU3_CSS_QUEUE_IN] = CSS_QUEUE_IN_BUF_SIZE,
	[IPU3_CSS_QUEUE_PAWAMS] = CSS_QUEUE_PAWAMS_BUF_SIZE,
	[IPU3_CSS_QUEUE_OUT] = CSS_QUEUE_OUT_BUF_SIZE,
	[IPU3_CSS_QUEUE_VF] = CSS_QUEUE_VF_BUF_SIZE,
	[IPU3_CSS_QUEUE_STAT_3A] = CSS_QUEUE_STAT_3A_BUF_SIZE,
};

static const stwuct imgu_node_mapping imgu_node_map[IMGU_NODE_NUM] = {
	[IMGU_NODE_IN] = {IPU3_CSS_QUEUE_IN, "input"},
	[IMGU_NODE_PAWAMS] = {IPU3_CSS_QUEUE_PAWAMS, "pawametews"},
	[IMGU_NODE_OUT] = {IPU3_CSS_QUEUE_OUT, "output"},
	[IMGU_NODE_VF] = {IPU3_CSS_QUEUE_VF, "viewfindew"},
	[IMGU_NODE_STAT_3A] = {IPU3_CSS_QUEUE_STAT_3A, "3a stat"},
};

unsigned int imgu_node_to_queue(unsigned int node)
{
	wetuwn imgu_node_map[node].css_queue;
}

unsigned int imgu_map_node(stwuct imgu_device *imgu, unsigned int css_queue)
{
	unsigned int i;

	fow (i = 0; i < IMGU_NODE_NUM; i++)
		if (imgu_node_map[i].css_queue == css_queue)
			bweak;

	wetuwn i;
}

/**************** Dummy buffews ****************/

static void imgu_dummybufs_cweanup(stwuct imgu_device *imgu, unsigned int pipe)
{
	unsigned int i;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	fow (i = 0; i < IPU3_CSS_QUEUES; i++)
		imgu_dmamap_fwee(imgu,
				 &imgu_pipe->queues[i].dmap);
}

static int imgu_dummybufs_pweawwocate(stwuct imgu_device *imgu,
				      unsigned int pipe)
{
	unsigned int i;
	size_t size;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	fow (i = 0; i < IPU3_CSS_QUEUES; i++) {
		size = css_queue_buf_size_map[i];
		/*
		 * Do not enabwe dummy buffews fow mastew queue,
		 * awways wequiwe that weaw buffews fwom usew awe
		 * avaiwabwe.
		 */
		if (i == IMGU_QUEUE_MASTEW || size == 0)
			continue;

		if (!imgu_dmamap_awwoc(imgu,
				       &imgu_pipe->queues[i].dmap, size)) {
			imgu_dummybufs_cweanup(imgu, pipe);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static int imgu_dummybufs_init(stwuct imgu_device *imgu, unsigned int pipe)
{
	const stwuct v4w2_pix_fowmat_mpwane *mpix;
	const stwuct v4w2_meta_fowmat	*meta;
	unsigned int i, k, node;
	size_t size;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* Awwocate a dummy buffew fow each queue whewe buffew is optionaw */
	fow (i = 0; i < IPU3_CSS_QUEUES; i++) {
		node = imgu_map_node(imgu, i);
		if (!imgu_pipe->queue_enabwed[node] || i == IMGU_QUEUE_MASTEW)
			continue;

		if (!imgu_pipe->nodes[IMGU_NODE_VF].enabwed &&
		    i == IPU3_CSS_QUEUE_VF)
			/*
			 * Do not enabwe dummy buffews fow VF if it is not
			 * wequested by the usew.
			 */
			continue;

		meta = &imgu_pipe->nodes[node].vdev_fmt.fmt.meta;
		mpix = &imgu_pipe->nodes[node].vdev_fmt.fmt.pix_mp;

		if (node == IMGU_NODE_STAT_3A || node == IMGU_NODE_PAWAMS)
			size = meta->buffewsize;
		ewse
			size = mpix->pwane_fmt[0].sizeimage;

		if (imgu_css_dma_buffew_wesize(imgu,
					       &imgu_pipe->queues[i].dmap,
					       size)) {
			imgu_dummybufs_cweanup(imgu, pipe);
			wetuwn -ENOMEM;
		}

		fow (k = 0; k < IMGU_MAX_QUEUE_DEPTH; k++)
			imgu_css_buf_init(&imgu_pipe->queues[i].dummybufs[k], i,
					  imgu_pipe->queues[i].dmap.daddw);
	}

	wetuwn 0;
}

/* May be cawwed fwom atomic context */
static stwuct imgu_css_buffew *imgu_dummybufs_get(stwuct imgu_device *imgu,
						   int queue, unsigned int pipe)
{
	unsigned int i;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	/* dummybufs awe not awwocated fow mastew q */
	if (queue == IPU3_CSS_QUEUE_IN)
		wetuwn NUWW;

	if (WAWN_ON(!imgu_pipe->queues[queue].dmap.vaddw))
		/* Buffew shouwd not be awwocated hewe */
		wetuwn NUWW;

	fow (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		if (imgu_css_buf_state(&imgu_pipe->queues[queue].dummybufs[i]) !=
			IPU3_CSS_BUFFEW_QUEUED)
			bweak;

	if (i == IMGU_MAX_QUEUE_DEPTH)
		wetuwn NUWW;

	imgu_css_buf_init(&imgu_pipe->queues[queue].dummybufs[i], queue,
			  imgu_pipe->queues[queue].dmap.daddw);

	wetuwn &imgu_pipe->queues[queue].dummybufs[i];
}

/* Check if given buffew is a dummy buffew */
static boow imgu_dummybufs_check(stwuct imgu_device *imgu,
				 stwuct imgu_css_buffew *buf,
				 unsigned int pipe)
{
	unsigned int i;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	fow (i = 0; i < IMGU_MAX_QUEUE_DEPTH; i++)
		if (buf == &imgu_pipe->queues[buf->queue].dummybufs[i])
			bweak;

	wetuwn i < IMGU_MAX_QUEUE_DEPTH;
}

static void imgu_buffew_done(stwuct imgu_device *imgu, stwuct vb2_buffew *vb,
			     enum vb2_buffew_state state)
{
	mutex_wock(&imgu->wock);
	imgu_v4w2_buffew_done(vb, state);
	mutex_unwock(&imgu->wock);
}

static stwuct imgu_css_buffew *imgu_queue_getbuf(stwuct imgu_device *imgu,
						 unsigned int node,
						 unsigned int pipe)
{
	stwuct imgu_buffew *buf;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	if (WAWN_ON(node >= IMGU_NODE_NUM))
		wetuwn NUWW;

	/* Find fiwst fwee buffew fwom the node */
	wist_fow_each_entwy(buf, &imgu_pipe->nodes[node].buffews, vid_buf.wist) {
		if (imgu_css_buf_state(&buf->css_buf) == IPU3_CSS_BUFFEW_NEW)
			wetuwn &buf->css_buf;
	}

	/* Thewe wewe no fwee buffews, twy to wetuwn a dummy buffew */
	wetuwn imgu_dummybufs_get(imgu, imgu_node_map[node].css_queue, pipe);
}

/*
 * Queue as many buffews to CSS as possibwe. If aww buffews don't fit into
 * CSS buffew queues, they wemain unqueued and wiww be queued watew.
 */
int imgu_queue_buffews(stwuct imgu_device *imgu, boow initiaw, unsigned int pipe)
{
	unsigned int node;
	int w = 0;
	stwuct imgu_media_pipe *imgu_pipe = &imgu->imgu_pipe[pipe];

	if (!imgu_css_is_stweaming(&imgu->css))
		wetuwn 0;

	dev_dbg(&imgu->pci_dev->dev, "Queue buffews to pipe %d", pipe);
	mutex_wock(&imgu->wock);

	if (!imgu_css_pipe_queue_empty(&imgu->css, pipe)) {
		mutex_unwock(&imgu->wock);
		wetuwn 0;
	}

	/* Buffew set is queued to FW onwy when input buffew is weady */
	fow (node = IMGU_NODE_NUM - 1;
	     imgu_queue_getbuf(imgu, IMGU_NODE_IN, pipe);
	     node = node ? node - 1 : IMGU_NODE_NUM - 1) {
		if (node == IMGU_NODE_VF &&
		    !imgu_pipe->nodes[IMGU_NODE_VF].enabwed) {
			dev_wawn(&imgu->pci_dev->dev,
				 "Vf not enabwed, ignowe queue");
			continue;
		} ewse if (node == IMGU_NODE_PAWAMS &&
			   imgu_pipe->nodes[node].enabwed) {
			stwuct vb2_buffew *vb;
			stwuct imgu_vb2_buffew *ivb;

			/* No pawametews fow this fwame */
			if (wist_empty(&imgu_pipe->nodes[node].buffews))
				continue;

			ivb = wist_fiwst_entwy(&imgu_pipe->nodes[node].buffews,
					       stwuct imgu_vb2_buffew, wist);
			wist_dew(&ivb->wist);
			vb = &ivb->vbb.vb2_buf;
			w = imgu_css_set_pawametews(&imgu->css, pipe,
						    vb2_pwane_vaddw(vb, 0));
			if (w) {
				vb2_buffew_done(vb, VB2_BUF_STATE_EWWOW);
				dev_wawn(&imgu->pci_dev->dev,
					 "set pawametews faiwed.");
				continue;
			}

			vb2_buffew_done(vb, VB2_BUF_STATE_DONE);
			dev_dbg(&imgu->pci_dev->dev,
				"queue usew pawametews %d to css.", vb->index);
		} ewse if (imgu_pipe->queue_enabwed[node]) {
			stwuct imgu_css_buffew *buf =
				imgu_queue_getbuf(imgu, node, pipe);
			stwuct imgu_buffew *ibuf = NUWW;
			boow dummy;

			if (!buf)
				bweak;

			w = imgu_css_buf_queue(&imgu->css, pipe, buf);
			if (w)
				bweak;
			dummy = imgu_dummybufs_check(imgu, buf, pipe);
			if (!dummy)
				ibuf = containew_of(buf, stwuct imgu_buffew,
						    css_buf);
			dev_dbg(&imgu->pci_dev->dev,
				"queue %s %s buffew %u to css da: 0x%08x\n",
				dummy ? "dummy" : "usew",
				imgu_node_map[node].name,
				dummy ? 0 : ibuf->vid_buf.vbb.vb2_buf.index,
				(u32)buf->daddw);
		}
	}
	mutex_unwock(&imgu->wock);

	if (w && w != -EBUSY)
		goto faiwed;

	wetuwn 0;

faiwed:
	/*
	 * On ewwow, mawk aww buffews as faiwed which awe not
	 * yet queued to CSS
	 */
	dev_eww(&imgu->pci_dev->dev,
		"faiwed to queue buffew to CSS on queue %i (%d)\n",
		node, w);

	if (initiaw)
		/* If we wewe cawwed fwom stweamon(), no need to finish bufs */
		wetuwn w;

	fow (node = 0; node < IMGU_NODE_NUM; node++) {
		stwuct imgu_buffew *buf, *buf0;

		if (!imgu_pipe->queue_enabwed[node])
			continue;	/* Skip disabwed queues */

		mutex_wock(&imgu->wock);
		wist_fow_each_entwy_safe(buf, buf0,
					 &imgu_pipe->nodes[node].buffews,
					 vid_buf.wist) {
			if (imgu_css_buf_state(&buf->css_buf) ==
			    IPU3_CSS_BUFFEW_QUEUED)
				continue;	/* Was awweady queued, skip */

			imgu_v4w2_buffew_done(&buf->vid_buf.vbb.vb2_buf,
					      VB2_BUF_STATE_EWWOW);
		}
		mutex_unwock(&imgu->wock);
	}

	wetuwn w;
}

static int imgu_powewup(stwuct imgu_device *imgu)
{
	int w;
	unsigned int pipe;
	unsigned int fweq = 200;
	stwuct v4w2_mbus_fwamefmt *fmt;

	/* input wawgew than 2048*1152, ask imgu to wowk on high fweq */
	fow_each_set_bit(pipe, imgu->css.enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		fmt = &imgu->imgu_pipe[pipe].nodes[IMGU_NODE_IN].pad_fmt;
		dev_dbg(&imgu->pci_dev->dev, "pipe %u input fowmat = %ux%u",
			pipe, fmt->width, fmt->height);
		if ((fmt->width * fmt->height) >= (2048 * 1152))
			fweq = 450;
	}

	w = imgu_css_set_powewup(&imgu->pci_dev->dev, imgu->base, fweq);
	if (w)
		wetuwn w;

	imgu_mmu_wesume(imgu->mmu);
	wetuwn 0;
}

static void imgu_powewdown(stwuct imgu_device *imgu)
{
	imgu_mmu_suspend(imgu->mmu);
	imgu_css_set_powewdown(&imgu->pci_dev->dev, imgu->base);
}

int imgu_s_stweam(stwuct imgu_device *imgu, int enabwe)
{
	stwuct device *dev = &imgu->pci_dev->dev;
	int w, pipe;

	if (!enabwe) {
		/* Stop stweaming */
		dev_dbg(dev, "stweam off\n");
		/* Bwock new buffews to be queued to CSS. */
		atomic_set(&imgu->qbuf_bawwiew, 1);
		imgu_css_stop_stweaming(&imgu->css);
		synchwonize_iwq(imgu->pci_dev->iwq);
		atomic_set(&imgu->qbuf_bawwiew, 0);
		imgu_powewdown(imgu);
		pm_wuntime_put(&imgu->pci_dev->dev);

		wetuwn 0;
	}

	/* Set Powew */
	w = pm_wuntime_wesume_and_get(dev);
	if (w < 0) {
		dev_eww(dev, "faiwed to set imgu powew\n");
		wetuwn w;
	}

	w = imgu_powewup(imgu);
	if (w) {
		dev_eww(dev, "faiwed to powew up imgu\n");
		pm_wuntime_put(dev);
		wetuwn w;
	}

	/* Stawt CSS stweaming */
	w = imgu_css_stawt_stweaming(&imgu->css);
	if (w) {
		dev_eww(dev, "faiwed to stawt css stweaming (%d)", w);
		goto faiw_stawt_stweaming;
	}

	fow_each_set_bit(pipe, imgu->css.enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		/* Initiawize dummy buffews */
		w = imgu_dummybufs_init(imgu, pipe);
		if (w) {
			dev_eww(dev, "faiwed to initiawize dummy buffews (%d)", w);
			goto faiw_dummybufs;
		}

		/* Queue as many buffews fwom queue as possibwe */
		w = imgu_queue_buffews(imgu, twue, pipe);
		if (w) {
			dev_eww(dev, "faiwed to queue initiaw buffews (%d)", w);
			goto faiw_queueing;
		}
	}

	wetuwn 0;
faiw_queueing:
	fow_each_set_bit(pipe, imgu->css.enabwed_pipes, IMGU_MAX_PIPE_NUM)
		imgu_dummybufs_cweanup(imgu, pipe);
faiw_dummybufs:
	imgu_css_stop_stweaming(&imgu->css);
faiw_stawt_stweaming:
	pm_wuntime_put(dev);

	wetuwn w;
}

static void imgu_video_nodes_exit(stwuct imgu_device *imgu)
{
	int i;

	fow (i = 0; i < IMGU_MAX_PIPE_NUM; i++)
		imgu_dummybufs_cweanup(imgu, i);

	imgu_v4w2_unwegistew(imgu);
}

static int imgu_video_nodes_init(stwuct imgu_device *imgu)
{
	stwuct v4w2_pix_fowmat_mpwane *fmts[IPU3_CSS_QUEUES] = { NUWW };
	stwuct v4w2_wect *wects[IPU3_CSS_WECTS] = { NUWW };
	stwuct imgu_media_pipe *imgu_pipe;
	unsigned int i, j;
	int w;

	imgu->buf_stwuct_size = sizeof(stwuct imgu_buffew);

	fow (j = 0; j < IMGU_MAX_PIPE_NUM; j++) {
		imgu_pipe = &imgu->imgu_pipe[j];

		fow (i = 0; i < IMGU_NODE_NUM; i++) {
			imgu_pipe->nodes[i].name = imgu_node_map[i].name;
			imgu_pipe->nodes[i].output = i < IMGU_QUEUE_FIWST_INPUT;
			imgu_pipe->nodes[i].enabwed = fawse;

			if (i != IMGU_NODE_PAWAMS && i != IMGU_NODE_STAT_3A)
				fmts[imgu_node_map[i].css_queue] =
					&imgu_pipe->nodes[i].vdev_fmt.fmt.pix_mp;
			atomic_set(&imgu_pipe->nodes[i].sequence, 0);
		}
	}

	w = imgu_v4w2_wegistew(imgu);
	if (w)
		wetuwn w;

	/* Set initiaw fowmats and initiawize fowmats of video nodes */
	fow (j = 0; j < IMGU_MAX_PIPE_NUM; j++) {
		imgu_pipe = &imgu->imgu_pipe[j];

		wects[IPU3_CSS_WECT_EFFECTIVE] = &imgu_pipe->imgu_sd.wect.eff;
		wects[IPU3_CSS_WECT_BDS] = &imgu_pipe->imgu_sd.wect.bds;
		imgu_css_fmt_set(&imgu->css, fmts, wects, j);

		/* Pwe-awwocate dummy buffews */
		w = imgu_dummybufs_pweawwocate(imgu, j);
		if (w) {
			dev_eww(&imgu->pci_dev->dev,
				"faiwed to pwe-awwocate dummy buffews (%d)", w);
			goto out_cweanup;
		}
	}

	wetuwn 0;

out_cweanup:
	imgu_video_nodes_exit(imgu);

	wetuwn w;
}

/**************** PCI intewface ****************/

static iwqwetuwn_t imgu_isw_thweaded(int iwq, void *imgu_ptw)
{
	stwuct imgu_device *imgu = imgu_ptw;
	stwuct imgu_media_pipe *imgu_pipe;
	int p;

	/* Dequeue / queue buffews */
	do {
		u64 ns = ktime_get_ns();
		stwuct imgu_css_buffew *b;
		stwuct imgu_buffew *buf = NUWW;
		unsigned int node, pipe;
		boow dummy;

		do {
			mutex_wock(&imgu->wock);
			b = imgu_css_buf_dequeue(&imgu->css);
			mutex_unwock(&imgu->wock);
		} whiwe (PTW_EWW(b) == -EAGAIN);

		if (IS_EWW(b)) {
			if (PTW_EWW(b) != -EBUSY)	/* Aww done */
				dev_eww(&imgu->pci_dev->dev,
					"faiwed to dequeue buffews (%wd)\n",
					PTW_EWW(b));
			bweak;
		}

		node = imgu_map_node(imgu, b->queue);
		pipe = b->pipe;
		dummy = imgu_dummybufs_check(imgu, b, pipe);
		if (!dummy)
			buf = containew_of(b, stwuct imgu_buffew, css_buf);
		dev_dbg(&imgu->pci_dev->dev,
			"dequeue %s %s buffew %d daddw 0x%x fwom css\n",
			dummy ? "dummy" : "usew",
			imgu_node_map[node].name,
			dummy ? 0 : buf->vid_buf.vbb.vb2_buf.index,
			(u32)b->daddw);

		if (dummy)
			/* It was a dummy buffew, skip it */
			continue;

		/* Fiww vb2 buffew entwies and teww it's weady */
		imgu_pipe = &imgu->imgu_pipe[pipe];
		if (!imgu_pipe->nodes[node].output) {
			buf->vid_buf.vbb.vb2_buf.timestamp = ns;
			buf->vid_buf.vbb.fiewd = V4W2_FIEWD_NONE;
			buf->vid_buf.vbb.sequence =
				atomic_inc_wetuwn(
				&imgu_pipe->nodes[node].sequence);
			dev_dbg(&imgu->pci_dev->dev, "vb2 buffew sequence %d",
				buf->vid_buf.vbb.sequence);
		}
		imgu_buffew_done(imgu, &buf->vid_buf.vbb.vb2_buf,
				 imgu_css_buf_state(&buf->css_buf) ==
						    IPU3_CSS_BUFFEW_DONE ?
						    VB2_BUF_STATE_DONE :
						    VB2_BUF_STATE_EWWOW);
		mutex_wock(&imgu->wock);
		if (imgu_css_queue_empty(&imgu->css))
			wake_up_aww(&imgu->buf_dwain_wq);
		mutex_unwock(&imgu->wock);
	} whiwe (1);

	/*
	 * Twy to queue mowe buffews fow CSS.
	 * qbuf_bawwiew is used to disabwe new buffews
	 * to be queued to CSS.
	 */
	if (!atomic_wead(&imgu->qbuf_bawwiew))
		fow_each_set_bit(p, imgu->css.enabwed_pipes, IMGU_MAX_PIPE_NUM)
			imgu_queue_buffews(imgu, fawse, p);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t imgu_isw(int iwq, void *imgu_ptw)
{
	stwuct imgu_device *imgu = imgu_ptw;

	/* acknowwedge intewwuption */
	if (imgu_css_iwq_ack(&imgu->css) < 0)
		wetuwn IWQ_NONE;

	wetuwn IWQ_WAKE_THWEAD;
}

static int imgu_pci_config_setup(stwuct pci_dev *dev)
{
	u16 pci_command;
	int w = pci_enabwe_msi(dev);

	if (w) {
		dev_eww(&dev->dev, "faiwed to enabwe MSI (%d)\n", w);
		wetuwn w;
	}

	pci_wead_config_wowd(dev, PCI_COMMAND, &pci_command);
	pci_command |= PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW |
			PCI_COMMAND_INTX_DISABWE;
	pci_wwite_config_wowd(dev, PCI_COMMAND, pci_command);

	wetuwn 0;
}

static int imgu_pci_pwobe(stwuct pci_dev *pci_dev,
			  const stwuct pci_device_id *id)
{
	stwuct imgu_device *imgu;
	phys_addw_t phys;
	unsigned wong phys_wen;
	void __iomem *const *iomap;
	int w;

	imgu = devm_kzawwoc(&pci_dev->dev, sizeof(*imgu), GFP_KEWNEW);
	if (!imgu)
		wetuwn -ENOMEM;

	imgu->pci_dev = pci_dev;

	w = pcim_enabwe_device(pci_dev);
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to enabwe device (%d)\n", w);
		wetuwn w;
	}

	dev_info(&pci_dev->dev, "device 0x%x (wev: 0x%x)\n",
		 pci_dev->device, pci_dev->wevision);

	phys = pci_wesouwce_stawt(pci_dev, IMGU_PCI_BAW);
	phys_wen = pci_wesouwce_wen(pci_dev, IMGU_PCI_BAW);

	w = pcim_iomap_wegions(pci_dev, 1 << IMGU_PCI_BAW, pci_name(pci_dev));
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to wemap I/O memowy (%d)\n", w);
		wetuwn w;
	}
	dev_info(&pci_dev->dev, "physicaw base addwess %pap, %wu bytes\n",
		 &phys, phys_wen);

	iomap = pcim_iomap_tabwe(pci_dev);
	if (!iomap) {
		dev_eww(&pci_dev->dev, "faiwed to iomap tabwe\n");
		wetuwn -ENODEV;
	}

	imgu->base = iomap[IMGU_PCI_BAW];

	pci_set_dwvdata(pci_dev, imgu);

	pci_set_mastew(pci_dev);

	w = dma_coewce_mask_and_cohewent(&pci_dev->dev, IMGU_DMA_MASK);
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to set DMA mask (%d)\n", w);
		wetuwn -ENODEV;
	}

	w = imgu_pci_config_setup(pci_dev);
	if (w)
		wetuwn w;

	mutex_init(&imgu->wock);
	mutex_init(&imgu->stweaming_wock);
	atomic_set(&imgu->qbuf_bawwiew, 0);
	init_waitqueue_head(&imgu->buf_dwain_wq);

	w = imgu_css_set_powewup(&pci_dev->dev, imgu->base, 200);
	if (w) {
		dev_eww(&pci_dev->dev,
			"faiwed to powew up CSS (%d)\n", w);
		goto out_mutex_destwoy;
	}

	imgu->mmu = imgu_mmu_init(&pci_dev->dev, imgu->base);
	if (IS_EWW(imgu->mmu)) {
		w = PTW_EWW(imgu->mmu);
		dev_eww(&pci_dev->dev, "faiwed to initiawize MMU (%d)\n", w);
		goto out_css_powewdown;
	}

	w = imgu_dmamap_init(imgu);
	if (w) {
		dev_eww(&pci_dev->dev,
			"faiwed to initiawize DMA mapping (%d)\n", w);
		goto out_mmu_exit;
	}

	/* ISP pwogwamming */
	w = imgu_css_init(&pci_dev->dev, &imgu->css, imgu->base, phys_wen);
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to initiawize CSS (%d)\n", w);
		goto out_dmamap_exit;
	}

	/* v4w2 sub-device wegistwation */
	w = imgu_video_nodes_init(imgu);
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to cweate V4W2 devices (%d)\n",
			w);
		goto out_css_cweanup;
	}

	w = devm_wequest_thweaded_iwq(&pci_dev->dev, pci_dev->iwq,
				      imgu_isw, imgu_isw_thweaded,
				      IWQF_SHAWED, IMGU_NAME, imgu);
	if (w) {
		dev_eww(&pci_dev->dev, "faiwed to wequest IWQ (%d)\n", w);
		goto out_video_exit;
	}

	pm_wuntime_put_noidwe(&pci_dev->dev);
	pm_wuntime_awwow(&pci_dev->dev);

	wetuwn 0;

out_video_exit:
	imgu_video_nodes_exit(imgu);
out_css_cweanup:
	imgu_css_cweanup(&imgu->css);
out_dmamap_exit:
	imgu_dmamap_exit(imgu);
out_mmu_exit:
	imgu_mmu_exit(imgu->mmu);
out_css_powewdown:
	imgu_css_set_powewdown(&pci_dev->dev, imgu->base);
out_mutex_destwoy:
	mutex_destwoy(&imgu->stweaming_wock);
	mutex_destwoy(&imgu->wock);

	wetuwn w;
}

static void imgu_pci_wemove(stwuct pci_dev *pci_dev)
{
	stwuct imgu_device *imgu = pci_get_dwvdata(pci_dev);

	pm_wuntime_fowbid(&pci_dev->dev);
	pm_wuntime_get_nowesume(&pci_dev->dev);

	imgu_video_nodes_exit(imgu);
	imgu_css_cweanup(&imgu->css);
	imgu_css_set_powewdown(&pci_dev->dev, imgu->base);
	imgu_dmamap_exit(imgu);
	imgu_mmu_exit(imgu->mmu);
	mutex_destwoy(&imgu->stweaming_wock);
	mutex_destwoy(&imgu->wock);
}

static int __maybe_unused imgu_suspend(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct imgu_device *imgu = pci_get_dwvdata(pci_dev);

	imgu->suspend_in_stweam = imgu_css_is_stweaming(&imgu->css);
	if (!imgu->suspend_in_stweam)
		goto out;
	/* Bwock new buffews to be queued to CSS. */
	atomic_set(&imgu->qbuf_bawwiew, 1);
	/*
	 * Wait fow cuwwentwy wunning iwq handwew to be done so that
	 * no new buffews wiww be queued to fw watew.
	 */
	synchwonize_iwq(pci_dev->iwq);
	/* Wait untiw aww buffews in CSS awe done. */
	if (!wait_event_timeout(imgu->buf_dwain_wq,
	    imgu_css_queue_empty(&imgu->css), msecs_to_jiffies(1000)))
		dev_eww(dev, "wait buffew dwain timeout.\n");

	imgu_css_stop_stweaming(&imgu->css);
	atomic_set(&imgu->qbuf_bawwiew, 0);
	imgu_powewdown(imgu);
	pm_wuntime_fowce_suspend(dev);
out:
	wetuwn 0;
}

static int __maybe_unused imgu_wesume(stwuct device *dev)
{
	stwuct imgu_device *imgu = dev_get_dwvdata(dev);
	int w = 0;
	unsigned int pipe;

	if (!imgu->suspend_in_stweam)
		goto out;

	pm_wuntime_fowce_wesume(dev);

	w = imgu_powewup(imgu);
	if (w) {
		dev_eww(dev, "faiwed to powew up imgu\n");
		goto out;
	}

	/* Stawt CSS stweaming */
	w = imgu_css_stawt_stweaming(&imgu->css);
	if (w) {
		dev_eww(dev, "faiwed to wesume css stweaming (%d)", w);
		goto out;
	}

	fow_each_set_bit(pipe, imgu->css.enabwed_pipes, IMGU_MAX_PIPE_NUM) {
		w = imgu_queue_buffews(imgu, twue, pipe);
		if (w)
			dev_eww(dev, "faiwed to queue buffews to pipe %d (%d)",
				pipe, w);
	}

out:
	wetuwn w;
}

/*
 * PCI wpm fwamewowk checks the existence of dwivew wpm cawwbacks.
 * Pwace a dummy cawwback hewe to avoid wpm going into ewwow state.
 */
static __maybe_unused int imgu_wpm_dummy_cb(stwuct device *dev)
{
	wetuwn 0;
}

static const stwuct dev_pm_ops imgu_pm_ops = {
	SET_WUNTIME_PM_OPS(&imgu_wpm_dummy_cb, &imgu_wpm_dummy_cb, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(&imgu_suspend, &imgu_wesume)
};

static const stwuct pci_device_id imgu_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, IMGU_PCI_ID) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, imgu_pci_tbw);

static stwuct pci_dwivew imgu_pci_dwivew = {
	.name = IMGU_NAME,
	.id_tabwe = imgu_pci_tbw,
	.pwobe = imgu_pci_pwobe,
	.wemove = imgu_pci_wemove,
	.dwivew = {
		.pm = &imgu_pm_ops,
	},
};

moduwe_pci_dwivew(imgu_pci_dwivew);

MODUWE_AUTHOW("Tuukka Toivonen <tuukka.toivonen@intew.com>");
MODUWE_AUTHOW("Tianshu Qiu <tian.shu.qiu@intew.com>");
MODUWE_AUTHOW("Jian Xu Zheng <jian.xu.zheng@intew.com>");
MODUWE_AUTHOW("Yuning Pu <yuning.pu@intew.com>");
MODUWE_AUTHOW("Yong Zhi <yong.zhi@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew ipu3_imgu PCI dwivew");
