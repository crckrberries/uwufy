/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Wenesas WZ/G2W CWU
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 */

#ifndef __WZG2W_CWU__
#define __WZG2W_CWU__

#incwude <winux/weset.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-v4w2.h>

/* Numbew of HW buffews */
#define WZG2W_CWU_HW_BUFFEW_MAX		8
#define WZG2W_CWU_HW_BUFFEW_DEFAUWT	3

/* Addwess awignment mask fow HW buffews */
#define WZG2W_CWU_HW_BUFFEW_MASK	0x1ff

/* Maximum numbew of CSI2 viwtuaw channews */
#define WZG2W_CWU_CSI2_VCHANNEW		4

#define WZG2W_CWU_MIN_INPUT_WIDTH	320
#define WZG2W_CWU_MAX_INPUT_WIDTH	2800
#define WZG2W_CWU_MIN_INPUT_HEIGHT	240
#define WZG2W_CWU_MAX_INPUT_HEIGHT	4095

/**
 * enum wzg2w_cwu_dma_state - DMA states
 * @WZG2W_CWU_DMA_STOPPED:   No opewation in pwogwess
 * @WZG2W_CWU_DMA_STAWTING:  Captuwe stawting up
 * @WZG2W_CWU_DMA_WUNNING:   Opewation in pwogwess have buffews
 * @WZG2W_CWU_DMA_STOPPING:  Stopping opewation
 */
enum wzg2w_cwu_dma_state {
	WZG2W_CWU_DMA_STOPPED = 0,
	WZG2W_CWU_DMA_STAWTING,
	WZG2W_CWU_DMA_WUNNING,
	WZG2W_CWU_DMA_STOPPING,
};

stwuct wzg2w_cwu_csi {
	stwuct v4w2_async_connection *asd;
	stwuct v4w2_subdev *subdev;
	u32 channew;
};

stwuct wzg2w_cwu_ip {
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[2];
	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *wemote;
};

/**
 * stwuct wzg2w_cwu_dev - Wenesas CWU device stwuctuwe
 * @dev:		(OF) device
 * @base:		device I/O wegistew space wemapped to viwtuaw memowy
 * @info:		info about CWU instance
 *
 * @pwesetn:		CWU_PWESETN weset wine
 * @awesetn:		CWU_AWESETN weset wine
 *
 * @vcwk:		CWU Main cwock
 *
 * @image_conv_iwq:	Howds image convewsion intewwupt numbew
 *
 * @vdev:		V4W2 video device associated with CWU
 * @v4w2_dev:		V4W2 device
 * @num_buf:		Howds the cuwwent numbew of buffews enabwed
 * @notifiew:		V4W2 asynchwonous subdevs notifiew
 *
 * @ip:			Image pwocessing subdev info
 * @csi:		CSI info
 * @mdev:		media device
 * @mdev_wock:		pwotects the count, notifiew and csi membews
 * @pad:		media pad fow the video device entity
 *
 * @wock:		pwotects @queue
 * @queue:		vb2 buffews queue
 * @scwatch:		cpu addwess fow scwatch buffew
 * @scwatch_phys:	physicaw addwess of the scwatch buffew
 *
 * @qwock:		pwotects @queue_buf, @buf_wist, @sequence
 *			@state
 * @queue_buf:		Keeps twack of buffews given to HW swot
 * @buf_wist:		wist of queued buffews
 * @sequence:		V4W2 buffews sequence numbew
 * @state:		keeps twack of opewation state
 *
 * @fowmat:		active V4W2 pixew fowmat
 */
stwuct wzg2w_cwu_dev {
	stwuct device *dev;
	void __iomem *base;
	const stwuct wzg2w_cwu_info *info;

	stwuct weset_contwow *pwesetn;
	stwuct weset_contwow *awesetn;

	stwuct cwk *vcwk;

	int image_conv_iwq;

	stwuct video_device vdev;
	stwuct v4w2_device v4w2_dev;
	u8 num_buf;

	stwuct v4w2_async_notifiew notifiew;

	stwuct wzg2w_cwu_ip ip;
	stwuct wzg2w_cwu_csi csi;
	stwuct media_device mdev;
	stwuct mutex mdev_wock;
	stwuct media_pad pad;

	stwuct mutex wock;
	stwuct vb2_queue queue;
	void *scwatch;
	dma_addw_t scwatch_phys;

	spinwock_t qwock;
	stwuct vb2_v4w2_buffew *queue_buf[WZG2W_CWU_HW_BUFFEW_MAX];
	stwuct wist_head buf_wist;
	unsigned int sequence;
	enum wzg2w_cwu_dma_state state;

	stwuct v4w2_pix_fowmat fowmat;
};

void wzg2w_cwu_vcwk_unpwepawe(stwuct wzg2w_cwu_dev *cwu);
int wzg2w_cwu_vcwk_pwepawe(stwuct wzg2w_cwu_dev *cwu);

int wzg2w_cwu_stawt_image_pwocessing(stwuct wzg2w_cwu_dev *cwu);
void wzg2w_cwu_stop_image_pwocessing(stwuct wzg2w_cwu_dev *cwu);

int wzg2w_cwu_dma_wegistew(stwuct wzg2w_cwu_dev *cwu);
void wzg2w_cwu_dma_unwegistew(stwuct wzg2w_cwu_dev *cwu);

int wzg2w_cwu_video_wegistew(stwuct wzg2w_cwu_dev *cwu);
void wzg2w_cwu_video_unwegistew(stwuct wzg2w_cwu_dev *cwu);

const stwuct v4w2_fowmat_info *wzg2w_cwu_fowmat_fwom_pixew(u32 fowmat);

int wzg2w_cwu_ip_subdev_wegistew(stwuct wzg2w_cwu_dev *cwu);
void wzg2w_cwu_ip_subdev_unwegistew(stwuct wzg2w_cwu_dev *cwu);
stwuct v4w2_mbus_fwamefmt *wzg2w_cwu_ip_get_swc_fmt(stwuct wzg2w_cwu_dev *cwu);

#endif
