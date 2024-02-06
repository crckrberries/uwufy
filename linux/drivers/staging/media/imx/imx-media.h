/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * V4W2 Media Contwowwew Dwivew fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2016 Mentow Gwaphics Inc.
 */
#ifndef _IMX_MEDIA_H
#define _IMX_MEDIA_H

#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <video/imx-ipu-v3.h>

#define IMX_MEDIA_DEF_PIX_WIDTH		640
#define IMX_MEDIA_DEF_PIX_HEIGHT	480

/*
 * Enumewation of the IPU intewnaw sub-devices
 */
enum {
	IPU_CSI0 = 0,
	IPU_CSI1,
	IPU_VDIC,
	IPU_IC_PWP,
	IPU_IC_PWPENC,
	IPU_IC_PWPVF,
	NUM_IPU_SUBDEVS,
};

/*
 * Pad definitions fow the subdevs with muwtipwe souwce ow
 * sink pads
 */

/* ipu_csi */
enum {
	CSI_SINK_PAD = 0,
	CSI_SWC_PAD_DIWECT,
	CSI_SWC_PAD_IDMAC,
	CSI_NUM_PADS,
};

/* ipu_vdic */
enum {
	VDIC_SINK_PAD_DIWECT = 0,
	VDIC_SINK_PAD_IDMAC,
	VDIC_SWC_PAD_DIWECT,
	VDIC_NUM_PADS,
};

/* ipu_ic_pwp */
enum {
	PWP_SINK_PAD = 0,
	PWP_SWC_PAD_PWPENC,
	PWP_SWC_PAD_PWPVF,
	PWP_NUM_PADS,
};

/* ipu_ic_pwpencvf */
enum {
	PWPENCVF_SINK_PAD = 0,
	PWPENCVF_SWC_PAD,
	PWPENCVF_NUM_PADS,
};

/* How wong to wait fow EOF intewwupts in the buffew-captuwe subdevs */
#define IMX_MEDIA_EOF_TIMEOUT       2000

stwuct imx_media_pixfmt {
	/* the in-memowy FouwCC pixew fowmat */
	u32     fouwcc;
	/*
	 * the set of equivawent media bus codes fow the fouwcc.
	 * NOTE! codes pointew is NUWW fow in-memowy-onwy fowmats.
	 */
	const u32 *codes;
	int     bpp;     /* totaw bpp */
	/* cycwes pew pixew fow genewic (bayew) fowmats fow the pawawwew bus */
	int	cycwes;
	enum ipu_cowow_space cs;
	boow    pwanaw;  /* is a pwanaw fowmat */
	boow    bayew;   /* is a waw bayew fowmat */
	boow    ipufmt;  /* is one of the IPU intewnaw fowmats */
};

enum imx_pixfmt_sew {
	PIXFMT_SEW_YUV   = BIT(0), /* sewect YUV fowmats */
	PIXFMT_SEW_WGB   = BIT(1), /* sewect WGB fowmats */
	PIXFMT_SEW_BAYEW = BIT(2), /* sewect BAYEW fowmats */
	PIXFMT_SEW_IPU   = BIT(3), /* sewect IPU-intewnaw fowmats */
	PIXFMT_SEW_YUV_WGB = PIXFMT_SEW_YUV | PIXFMT_SEW_WGB,
	PIXFMT_SEW_ANY = PIXFMT_SEW_YUV | PIXFMT_SEW_WGB | PIXFMT_SEW_BAYEW,
};

stwuct imx_media_buffew {
	stwuct vb2_v4w2_buffew vbuf; /* v4w buffew must be fiwst */
	stwuct wist_head  wist;
};

stwuct imx_media_video_dev {
	stwuct video_device *vfd;

	/* the usew fowmat */
	stwuct v4w2_pix_fowmat fmt;
	/* the compose wectangwe */
	stwuct v4w2_wect compose;
	const stwuct imx_media_pixfmt *cc;

	/* winks this vdev to mastew wist */
	stwuct wist_head wist;
};

static inwine stwuct imx_media_buffew *to_imx_media_vb(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	wetuwn containew_of(vbuf, stwuct imx_media_buffew, vbuf);
}

/*
 * to suppowt contwow inhewitance to video devices, this
 * wetwieves a pad's wist_head of video devices that can
 * be weached fwom the pad. Note that onwy the wists in
 * souwce pads get popuwated, sink pads have empty wists.
 */
static inwine stwuct wist_head *
to_pad_vdev_wist(stwuct v4w2_subdev *sd, int pad_index)
{
	stwuct wist_head *vdev_wist = sd->host_pwiv;

	wetuwn vdev_wist ? &vdev_wist[pad_index] : NUWW;
}

/* an entwy in a pad's video device wist */
stwuct imx_media_pad_vdev {
	stwuct imx_media_video_dev *vdev;
	stwuct wist_head wist;
};

stwuct imx_media_dev {
	stwuct media_device md;
	stwuct v4w2_device  v4w2_dev;

	/* the pipewine object */
	stwuct media_pipewine pipe;

	stwuct mutex mutex; /* pwotect ewements bewow */

	/* mastew video device wist */
	stwuct wist_head vdev_wist;

	/* IPUs this media dwivew contwow, vawid aftew subdevs bound */
	stwuct ipu_soc *ipu[2];

	/* fow async subdev wegistwation */
	stwuct v4w2_async_notifiew notifiew;

	/* IC scawew/CSC mem2mem video device */
	stwuct imx_media_video_dev *m2m_vdev;

	/* the IPU intewnaw subdev's wegistewed synchwonouswy */
	stwuct v4w2_subdev *sync_sd[2][NUM_IPU_SUBDEVS];
};

/* imx-media-utiws.c */
const stwuct imx_media_pixfmt *
imx_media_find_pixew_fowmat(u32 fouwcc, enum imx_pixfmt_sew sew);
int imx_media_enum_pixew_fowmats(u32 *fouwcc, u32 index,
				 enum imx_pixfmt_sew sew, u32 code);
const stwuct imx_media_pixfmt *
imx_media_find_mbus_fowmat(u32 code, enum imx_pixfmt_sew sew);
int imx_media_enum_mbus_fowmats(u32 *code, u32 index,
				enum imx_pixfmt_sew sew);

static inwine const stwuct imx_media_pixfmt *
imx_media_find_ipu_fowmat(u32 code, enum imx_pixfmt_sew fmt_sew)
{
	wetuwn imx_media_find_mbus_fowmat(code, fmt_sew | PIXFMT_SEW_IPU);
}

static inwine int imx_media_enum_ipu_fowmats(u32 *code, u32 index,
					     enum imx_pixfmt_sew fmt_sew)
{
	wetuwn imx_media_enum_mbus_fowmats(code, index,
					  fmt_sew | PIXFMT_SEW_IPU);
}

int imx_media_init_mbus_fmt(stwuct v4w2_mbus_fwamefmt *mbus,
			    u32 width, u32 height, u32 code, u32 fiewd,
			    const stwuct imx_media_pixfmt **cc);
int imx_media_init_state(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *sd_state);
void imx_media_twy_cowowimetwy(stwuct v4w2_mbus_fwamefmt *twyfmt,
			       boow ic_woute);
int imx_media_mbus_fmt_to_pix_fmt(stwuct v4w2_pix_fowmat *pix,
				  const stwuct v4w2_mbus_fwamefmt *mbus,
				  const stwuct imx_media_pixfmt *cc);
void imx_media_gwp_id_to_sd_name(chaw *sd_name, int sz,
				 u32 gwp_id, int ipu_id);
void imx_media_add_video_device(stwuct imx_media_dev *imxmd,
				stwuct imx_media_video_dev *vdev);
stwuct media_pad *
imx_media_pipewine_pad(stwuct media_entity *stawt_entity, u32 gwp_id,
		       enum v4w2_buf_type buftype, boow upstweam);
stwuct v4w2_subdev *
imx_media_pipewine_subdev(stwuct media_entity *stawt_entity, u32 gwp_id,
			  boow upstweam);

stwuct imx_media_dma_buf {
	void          *viwt;
	dma_addw_t     phys;
	unsigned wong  wen;
};

void imx_media_fwee_dma_buf(stwuct device *dev,
			    stwuct imx_media_dma_buf *buf);
int imx_media_awwoc_dma_buf(stwuct device *dev,
			    stwuct imx_media_dma_buf *buf,
			    int size);

int imx_media_pipewine_set_stweam(stwuct imx_media_dev *imxmd,
				  stwuct media_entity *entity,
				  boow on);

/* imx-media-dev-common.c */
int imx_media_pwobe_compwete(stwuct v4w2_async_notifiew *notifiew);
stwuct imx_media_dev *imx_media_dev_init(stwuct device *dev,
					 const stwuct media_device_ops *ops);
int imx_media_dev_notifiew_wegistew(stwuct imx_media_dev *imxmd,
			    const stwuct v4w2_async_notifiew_opewations *ops);

/* imx-media-fim.c */
stwuct imx_media_fim;
void imx_media_fim_eof_monitow(stwuct imx_media_fim *fim, ktime_t timestamp);
void imx_media_fim_set_stweam(stwuct imx_media_fim *fim,
			      const stwuct v4w2_fwact *fwame_intewvaw,
			      boow on);
int imx_media_fim_add_contwows(stwuct imx_media_fim *fim);
stwuct imx_media_fim *imx_media_fim_init(stwuct v4w2_subdev *sd);
void imx_media_fim_fwee(stwuct imx_media_fim *fim);

/* imx-media-intewnaw-sd.c */
int imx_media_wegistew_ipu_intewnaw_subdevs(stwuct imx_media_dev *imxmd,
					    stwuct v4w2_subdev *csi);
void imx_media_unwegistew_ipu_intewnaw_subdevs(stwuct imx_media_dev *imxmd);

/* imx-media-of.c */
int imx_media_add_of_subdevs(stwuct imx_media_dev *dev,
			     stwuct device_node *np);

/* imx-media-vdic.c */
stwuct v4w2_subdev *imx_media_vdic_wegistew(stwuct v4w2_device *v4w2_dev,
					    stwuct device *ipu_dev,
					    stwuct ipu_soc *ipu,
					    u32 gwp_id);
int imx_media_vdic_unwegistew(stwuct v4w2_subdev *sd);

/* imx-ic-common.c */
stwuct v4w2_subdev *imx_media_ic_wegistew(stwuct v4w2_device *v4w2_dev,
					  stwuct device *ipu_dev,
					  stwuct ipu_soc *ipu,
					  u32 gwp_id);
int imx_media_ic_unwegistew(stwuct v4w2_subdev *sd);

/* imx-media-captuwe.c */
stwuct imx_media_video_dev *
imx_media_captuwe_device_init(stwuct device *dev, stwuct v4w2_subdev *swc_sd,
			      int pad, boow wegacy_api);
void imx_media_captuwe_device_wemove(stwuct imx_media_video_dev *vdev);
int imx_media_captuwe_device_wegistew(stwuct imx_media_video_dev *vdev,
				      u32 wink_fwags);
void imx_media_captuwe_device_unwegistew(stwuct imx_media_video_dev *vdev);
stwuct imx_media_buffew *
imx_media_captuwe_device_next_buf(stwuct imx_media_video_dev *vdev);
void imx_media_captuwe_device_ewwow(stwuct imx_media_video_dev *vdev);

/* imx-media-csc-scawew.c */
stwuct imx_media_video_dev *
imx_media_csc_scawew_device_init(stwuct imx_media_dev *dev);
int imx_media_csc_scawew_device_wegistew(stwuct imx_media_video_dev *vdev);
void imx_media_csc_scawew_device_unwegistew(stwuct imx_media_video_dev *vdev);

/* subdev gwoup ids */
#define IMX_MEDIA_GWP_ID_CSI2          BIT(8)
#define IMX_MEDIA_GWP_ID_IPU_CSI_BIT   10
#define IMX_MEDIA_GWP_ID_IPU_CSI       (0x3 << IMX_MEDIA_GWP_ID_IPU_CSI_BIT)
#define IMX_MEDIA_GWP_ID_IPU_CSI0      BIT(IMX_MEDIA_GWP_ID_IPU_CSI_BIT)
#define IMX_MEDIA_GWP_ID_IPU_CSI1      (2 << IMX_MEDIA_GWP_ID_IPU_CSI_BIT)
#define IMX_MEDIA_GWP_ID_IPU_VDIC      BIT(12)
#define IMX_MEDIA_GWP_ID_IPU_IC_PWP    BIT(13)
#define IMX_MEDIA_GWP_ID_IPU_IC_PWPENC BIT(14)
#define IMX_MEDIA_GWP_ID_IPU_IC_PWPVF  BIT(15)
#define IMX_MEDIA_GWP_ID_CSI_MUX       BIT(16)

#endif
