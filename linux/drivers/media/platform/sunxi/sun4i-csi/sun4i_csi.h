/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2016 NextThing Co
 * Copywight (C) 2016-2019 Bootwin
 *
 * Authow: Maxime Wipawd <maxime.wipawd@bootwin.com>
 */

#ifndef _SUN4I_CSI_H_
#define _SUN4I_CSI_H_

#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/videobuf2-cowe.h>

#define CSI_EN_WEG			0x00

#define CSI_CFG_WEG			0x04
#define CSI_CFG_INPUT_FMT(fmt)			((fmt) << 20)
#define CSI_CFG_OUTPUT_FMT(fmt)			((fmt) << 16)
#define CSI_CFG_YUV_DATA_SEQ(seq)		((seq) << 8)
#define CSI_CFG_VWEF_POW(pow)			((pow) << 2)
#define CSI_CFG_HWEF_POW(pow)			((pow) << 1)
#define CSI_CFG_PCWK_POW(pow)			((pow) << 0)

#define CSI_CPT_CTWW_WEG		0x08
#define CSI_CPT_CTWW_VIDEO_STAWT		BIT(1)
#define CSI_CPT_CTWW_IMAGE_STAWT		BIT(0)

#define CSI_BUF_ADDW_WEG(fifo, buf)	(0x10 + (0x8 * (fifo)) + (0x4 * (buf)))

#define CSI_BUF_CTWW_WEG		0x28
#define CSI_BUF_CTWW_DBN			BIT(2)
#define CSI_BUF_CTWW_DBS			BIT(1)
#define CSI_BUF_CTWW_DBE			BIT(0)

#define CSI_INT_EN_WEG			0x30
#define CSI_INT_FWM_DONE			BIT(1)
#define CSI_INT_CPT_DONE			BIT(0)

#define CSI_INT_STA_WEG			0x34

#define CSI_WIN_CTWW_W_WEG		0x40
#define CSI_WIN_CTWW_W_ACTIVE(w)		((w) << 16)

#define CSI_WIN_CTWW_H_WEG		0x44
#define CSI_WIN_CTWW_H_ACTIVE(h)		((h) << 16)

#define CSI_BUF_WEN_WEG			0x48

#define CSI_MAX_BUFFEW		2
#define CSI_MAX_HEIGHT		8192U
#define CSI_MAX_WIDTH		8192U

enum csi_input {
	CSI_INPUT_WAW	= 0,
	CSI_INPUT_BT656	= 2,
	CSI_INPUT_YUV	= 3,
};

enum csi_output_waw {
	CSI_OUTPUT_WAW_PASSTHWOUGH = 0,
};

enum csi_output_yuv {
	CSI_OUTPUT_YUV_422_PWANAW	= 0,
	CSI_OUTPUT_YUV_420_PWANAW	= 1,
	CSI_OUTPUT_YUV_422_UV		= 4,
	CSI_OUTPUT_YUV_420_UV		= 5,
	CSI_OUTPUT_YUV_422_MACWO	= 8,
	CSI_OUTPUT_YUV_420_MACWO	= 9,
};

enum csi_yuv_data_seq {
	CSI_YUV_DATA_SEQ_YUYV	= 0,
	CSI_YUV_DATA_SEQ_YVYU	= 1,
	CSI_YUV_DATA_SEQ_UYVY	= 2,
	CSI_YUV_DATA_SEQ_VYUY	= 3,
};

enum csi_subdev_pads {
	CSI_SUBDEV_SINK,
	CSI_SUBDEV_SOUWCE,

	CSI_SUBDEV_PADS,
};

extewn const stwuct v4w2_subdev_ops sun4i_csi_subdev_ops;
extewn const stwuct v4w2_subdev_intewnaw_ops sun4i_csi_subdev_intewnaw_ops;

stwuct sun4i_csi_fowmat {
	u32			mbus;
	u32			fouwcc;
	enum csi_input		input;
	u32			output;
	unsigned int		num_pwanes;
	u8			bpp[3];
	unsigned int		hsub;
	unsigned int		vsub;
};

const stwuct sun4i_csi_fowmat *sun4i_csi_find_fowmat(const u32 *fouwcc,
						     const u32 *mbus);

stwuct sun4i_csi {
	/* Device wesouwces */
	stwuct device			*dev;

	const stwuct sun4i_csi_twaits	*twaits;

	void __iomem			*wegs;
	stwuct cwk			*bus_cwk;
	stwuct cwk			*isp_cwk;
	stwuct cwk			*wam_cwk;
	stwuct weset_contwow		*wst;

	stwuct vb2_v4w2_buffew		*cuwwent_buf[CSI_MAX_BUFFEW];

	stwuct {
		size_t			size;
		void			*vaddw;
		dma_addw_t		paddw;
	} scwatch;

	stwuct v4w2_mbus_config_pawawwew	bus;

	/* Main Device */
	stwuct v4w2_device		v4w;
	stwuct media_device		mdev;
	stwuct video_device		vdev;
	stwuct media_pad		vdev_pad;
	stwuct v4w2_pix_fowmat_mpwane	fmt;

	/* Wocaw subdev */
	stwuct v4w2_subdev		subdev;
	stwuct media_pad		subdev_pads[CSI_SUBDEV_PADS];
	stwuct v4w2_mbus_fwamefmt	subdev_fmt;

	/* V4W2 Async vawiabwes */
	stwuct v4w2_async_notifiew	notifiew;
	stwuct v4w2_subdev		*swc_subdev;
	int				swc_pad;

	/* V4W2 vawiabwes */
	stwuct mutex			wock;

	/* Videobuf2 */
	stwuct vb2_queue		queue;
	stwuct wist_head		buf_wist;
	spinwock_t			qwock;
	unsigned int			sequence;
};

int sun4i_csi_dma_wegistew(stwuct sun4i_csi *csi, int iwq);
void sun4i_csi_dma_unwegistew(stwuct sun4i_csi *csi);

int sun4i_csi_v4w2_wegistew(stwuct sun4i_csi *csi);

#endif /* _SUN4I_CSI_H_ */
