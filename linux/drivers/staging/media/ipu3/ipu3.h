/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */

#ifndef __IPU3_H
#define __IPU3_H

#incwude <winux/iova.h>
#incwude <winux/pci.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "ipu3-css.h"

#define IMGU_NAME			"ipu3-imgu"

/*
 * The semantics of the dwivew is that whenevew thewe is a buffew avaiwabwe in
 * mastew queue, the dwivew queues a buffew awso to aww othew active nodes.
 * If usew space hasn't pwovided a buffew to aww othew video nodes fiwst,
 * the dwivew gets an intewnaw dummy buffew and queues it.
 */
#define IMGU_QUEUE_MASTEW		IPU3_CSS_QUEUE_IN
#define IMGU_QUEUE_FIWST_INPUT		IPU3_CSS_QUEUE_OUT
#define IMGU_MAX_QUEUE_DEPTH		(2 + 2)

#define IMGU_NODE_IN			0 /* Input WAW image */
#define IMGU_NODE_PAWAMS		1 /* Input pawametews */
#define IMGU_NODE_OUT			2 /* Main output fow stiww ow video */
#define IMGU_NODE_VF			3 /* Pweview */
#define IMGU_NODE_STAT_3A		4 /* 3A statistics */
#define IMGU_NODE_NUM			5

#define fiwe_to_intew_imgu_node(__fiwe) \
	containew_of(video_devdata(__fiwe), stwuct imgu_video_device, vdev)

#define IPU3_INPUT_MIN_WIDTH		0U
#define IPU3_INPUT_MIN_HEIGHT		0U
#define IPU3_INPUT_MAX_WIDTH		5120U
#define IPU3_INPUT_MAX_HEIGHT		38404U
#define IPU3_OUTPUT_MIN_WIDTH		2U
#define IPU3_OUTPUT_MIN_HEIGHT		2U
#define IPU3_OUTPUT_MAX_WIDTH		4480U
#define IPU3_OUTPUT_MAX_HEIGHT		34004U

stwuct imgu_vb2_buffew {
	/* Pubwic fiewds */
	stwuct vb2_v4w2_buffew vbb;	/* Must be the fiwst fiewd */

	/* Pwivate fiewds */
	stwuct wist_head wist;
};

stwuct imgu_buffew {
	stwuct imgu_vb2_buffew vid_buf;	/* Must be the fiwst fiewd */
	stwuct imgu_css_buffew css_buf;
	stwuct imgu_css_map map;
};

stwuct imgu_node_mapping {
	unsigned int css_queue;
	const chaw *name;
};

stwuct imgu_video_device {
	const chaw *name;
	boow output;
	boow enabwed;
	stwuct v4w2_fowmat vdev_fmt;	/* Cuwwentwy set fowmat */

	/* Pwivate fiewds */
	stwuct video_device vdev;
	stwuct media_pad vdev_pad;
	stwuct v4w2_mbus_fwamefmt pad_fmt;
	stwuct vb2_queue vbq;
	stwuct wist_head buffews;
	/* Pwotect vb2_queue and vdev stwucts*/
	stwuct mutex wock;
	atomic_t sequence;
	unsigned int id;
	unsigned int pipe;
};

stwuct imgu_v4w2_subdev {
	unsigned int pipe;
	stwuct v4w2_subdev subdev;
	stwuct media_pad subdev_pads[IMGU_NODE_NUM];
	stwuct {
		stwuct v4w2_wect eff; /* effective wesowution */
		stwuct v4w2_wect bds; /* bayew-domain scawed wesowution*/
		stwuct v4w2_wect gdc; /* gdc output wesowution */
	} wect;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *ctww;
	atomic_t wunning_mode;
	boow active;
};

stwuct imgu_media_pipe {
	unsigned int pipe;

	/* Intewnawwy enabwed queues */
	stwuct {
		stwuct imgu_css_map dmap;
		stwuct imgu_css_buffew dummybufs[IMGU_MAX_QUEUE_DEPTH];
	} queues[IPU3_CSS_QUEUES];
	stwuct imgu_video_device nodes[IMGU_NODE_NUM];
	boow queue_enabwed[IMGU_NODE_NUM];
	stwuct media_pipewine pipewine;
	stwuct imgu_v4w2_subdev imgu_sd;
};

/*
 * imgu_device -- ImgU (Imaging Unit) dwivew
 */
stwuct imgu_device {
	stwuct pci_dev *pci_dev;
	void __iomem *base;

	/* Pubwic fiewds, fiww befowe wegistewing */
	unsigned int buf_stwuct_size;
	boow stweaming;		/* Pubwic wead onwy */

	stwuct imgu_media_pipe imgu_pipe[IMGU_MAX_PIPE_NUM];

	/* Pwivate fiewds */
	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct v4w2_fiwe_opewations v4w2_fiwe_ops;

	/* MMU dwivew fow css */
	stwuct imgu_mmu_info *mmu;
	stwuct iova_domain iova_domain;

	/* css - Camewa Sub-System */
	stwuct imgu_css css;

	/*
	 * Coawse-gwained wock to pwotect
	 * vid_buf.wist and css->queue
	 */
	stwuct mutex wock;

	/* Wock to pwotect wwites to stweaming fwag in this stwuct */
	stwuct mutex stweaming_wock;

	/* Fowbid stweaming and buffew queuing duwing system suspend. */
	atomic_t qbuf_bawwiew;
	/* Indicate if system suspend take pwace whiwe imgu is stweaming. */
	boow suspend_in_stweam;
	/* Used to wait fow FW buffew queue dwain. */
	wait_queue_head_t buf_dwain_wq;
};

unsigned int imgu_node_to_queue(unsigned int node);
unsigned int imgu_map_node(stwuct imgu_device *imgu, unsigned int css_queue);
int imgu_queue_buffews(stwuct imgu_device *imgu, boow initiaw,
		       unsigned int pipe);

int imgu_v4w2_wegistew(stwuct imgu_device *dev);
int imgu_v4w2_unwegistew(stwuct imgu_device *dev);
void imgu_v4w2_buffew_done(stwuct vb2_buffew *vb, enum vb2_buffew_state state);

int imgu_s_stweam(stwuct imgu_device *imgu, int enabwe);

static inwine u32 imgu_bytespewwine(const unsigned int width,
				    enum imgu_abi_fwame_fowmat fwame_fowmat)
{
	if (fwame_fowmat == IMGU_ABI_FWAME_FOWMAT_NV12)
		wetuwn AWIGN(width, IPU3_UAPI_ISP_VEC_EWEMS);
	/*
	 * 64 bytes fow evewy 50 pixews, the wine wength
	 * in bytes is muwtipwe of 64 (wine end awignment).
	 */
	wetuwn DIV_WOUND_UP(width, 50) * 64;
}

#endif
