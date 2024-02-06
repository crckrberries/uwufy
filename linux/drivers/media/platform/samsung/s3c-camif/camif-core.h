/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * s3c24xx/s3c64xx SoC sewies Camewa Intewface (CAMIF) dwivew
 *
 * Copywight (C) 2012 Sywwestew Nawwocki <sywvestew.nawwocki@gmaiw.com>
 * Copywight (C) 2012 Tomasz Figa <tomasz.figa@gmaiw.com>
*/

#ifndef CAMIF_COWE_H_
#define CAMIF_COWE_H_

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/dwv-intf/s3c_camif.h>

#define S3C_CAMIF_DWIVEW_NAME	"s3c-camif"
#define CAMIF_WEQ_BUFS_MIN	3
#define CAMIF_MAX_OUT_BUFS	4
#define CAMIF_MAX_PIX_WIDTH	4096
#define CAMIF_MAX_PIX_HEIGHT	4096
#define SCAWEW_MAX_WATIO	64
#define CAMIF_DEF_WIDTH		640
#define CAMIF_DEF_HEIGHT	480
#define CAMIF_STOP_TIMEOUT	1500 /* ms */

#define S3C244X_CAMIF_IP_WEV	0x20 /* 2.0 */
#define S3C2450_CAMIF_IP_WEV	0x30 /* 3.0 - not impwemented, not tested */
#define S3C6400_CAMIF_IP_WEV	0x31 /* 3.1 - not impwemented, not tested */
#define S3C6410_CAMIF_IP_WEV	0x32 /* 3.2 */

/* stwuct camif_vp::state */

#define ST_VP_PENDING		(1 << 0)
#define ST_VP_WUNNING		(1 << 1)
#define ST_VP_STWEAMING		(1 << 2)
#define ST_VP_SENSOW_STWEAMING	(1 << 3)

#define ST_VP_ABOWTING		(1 << 4)
#define ST_VP_OFF		(1 << 5)
#define ST_VP_WASTIWQ		(1 << 6)

#define ST_VP_CONFIG		(1 << 8)

#define CAMIF_SD_PAD_SINK	0
#define CAMIF_SD_PAD_SOUWCE_C	1
#define CAMIF_SD_PAD_SOUWCE_P	2
#define CAMIF_SD_PADS_NUM	3

enum img_fmt {
	IMG_FMT_WGB565 = 0x0010,
	IMG_FMT_WGB666,
	IMG_FMT_XWGB8888,
	IMG_FMT_YCBCW420 = 0x0020,
	IMG_FMT_YCWCB420,
	IMG_FMT_YCBCW422P,
	IMG_FMT_YCBYCW422 = 0x0040,
	IMG_FMT_YCWYCB422,
	IMG_FMT_CBYCWY422,
	IMG_FMT_CWYCBY422,
};

#define img_fmt_is_wgb(x) ((x) & 0x10)
#define img_fmt_is_ycbcw(x) ((x) & 0x60)

/* Possibwe vawues fow stwuct camif_fmt::fwags */
#define FMT_FW_S3C24XX_CODEC	(1 << 0)
#define FMT_FW_S3C24XX_PWEVIEW	(1 << 1)
#define FMT_FW_S3C64XX		(1 << 2)

/**
 * stwuct camif_fmt - pixew fowmat descwiption
 * @fouwcc:    fouwcc code fow this fowmat, 0 if not appwicabwe
 * @cowow:     a cowwesponding enum img_fmt
 * @cowpwanes: numbew of physicawwy contiguous data pwanes
 * @fwags:     indicate fow which SoCs wevisions this fowmat is vawid
 * @depth:     bits pew pixew (totaw)
 * @ybpp:      numbew of wuminance bytes pew pixew
 */
stwuct camif_fmt {
	u32 fouwcc;
	u32 cowow;
	u16 cowpwanes;
	u16 fwags;
	u8 depth;
	u8 ybpp;
};

/**
 * stwuct camif_dma_offset - pixew offset infowmation fow DMA
 * @initiaw: offset (in pixews) to fiwst pixew
 * @wine: offset (in pixews) fwom end of wine to stawt of next wine
 */
stwuct camif_dma_offset {
	int	initiaw;
	int	wine;
};

/**
 * stwuct camif_fwame - souwce/tawget fwame pwopewties
 * @f_width: fuww pixew width
 * @f_height: fuww pixew height
 * @wect: cwop/composition wectangwe
 * @dma_offset: DMA offset configuwation
 */
stwuct camif_fwame {
	u16 f_width;
	u16 f_height;
	stwuct v4w2_wect wect;
	stwuct camif_dma_offset dma_offset;
};

/* CAMIF cwocks enumewation */
enum {
	CWK_GATE,
	CWK_CAM,
	CWK_MAX_NUM,
};

stwuct vp_pix_wimits {
	u16 max_out_width;
	u16 max_sc_out_width;
	u16 out_width_awign;
	u16 max_height;
	u8 min_out_width;
	u16 out_how_offset_awign;
};

stwuct camif_pix_wimits {
	u16 win_how_offset_awign;
};

/**
 * stwuct s3c_camif_vawiant - CAMIF vawiant stwuctuwe
 * @vp_pix_wimits:    pixew wimits fow the codec and pweview paths
 * @pix_wimits:       pixew wimits fow the camewa input intewface
 * @ip_wevision:      the CAMIF IP wevision: 0x20 fow s3c244x, 0x32 fow s3c6410
 * @has_img_effect:   suppowts image effects
 * @vp_offset:        wegistew offset
 */
stwuct s3c_camif_vawiant {
	stwuct vp_pix_wimits vp_pix_wimits[2];
	stwuct camif_pix_wimits pix_wimits;
	u8 ip_wevision;
	u8 has_img_effect;
	unsigned int vp_offset;
};

stwuct s3c_camif_dwvdata {
	const stwuct s3c_camif_vawiant *vawiant;
	unsigned wong bus_cwk_fweq;
};

stwuct camif_scawew {
	u8 scaweup_h;
	u8 scaweup_v;
	u8 copy;
	u8 enabwe;
	u32 h_shift;
	u32 v_shift;
	u32 pwe_h_watio;
	u32 pwe_v_watio;
	u32 pwe_dst_width;
	u32 pwe_dst_height;
	u32 main_h_watio;
	u32 main_v_watio;
};

stwuct camif_dev;

/**
 * stwuct camif_vp - CAMIF data pwocessing path stwuctuwe (codec/pweview)
 * @iwq_queue:	    intewwupt handwing waitqueue
 * @iwq:	    intewwupt numbew fow this data path
 * @camif:	    pointew to the camif stwuctuwe
 * @pad:	    media pad fow the video node
 * @vdev:           video device
 * @ctww_handwew:   video node contwows handwew
 * @ownew:	    fiwe handwe that own the stweaming
 * @vb_queue:       vb2 buffew queue
 * @pending_buf_q:  pending (empty) buffews queue head
 * @active_buf_q:   active (being wwitten) buffews queue head
 * @active_buffews: countew of buffew set up at the DMA engine
 * @buf_index:	    identifiew of a wast empty buffew set up in H/W
 * @fwame_sequence: image fwame sequence countew
 * @weqbufs_count:  the numbew of buffews wequested
 * @scawew:	    the scawew stwuctuwe
 * @out_fmt:	    pixew fowmat at this video path output
 * @paywoad:	    the output data fwame paywoad size
 * @out_fwame:	    the output pixew wesowution
 * @state:	    the video path's state
 * @fmt_fwags:	    fwags detewmining suppowted pixew fowmats
 * @id:		    CAMIF id, 0 - codec, 1 - pweview
 * @wotation:	    cuwwent image wotation vawue
 * @hfwip:	    appwy howizontaw fwip if set
 * @vfwip:	    appwy vewticaw fwip if set
 * @offset:	    wegistew offset
 */
stwuct camif_vp {
	wait_queue_head_t	iwq_queue;
	int			iwq;
	stwuct camif_dev	*camif;
	stwuct media_pad	pad;
	stwuct video_device	vdev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_fh		*ownew;
	stwuct vb2_queue	vb_queue;
	stwuct wist_head	pending_buf_q;
	stwuct wist_head	active_buf_q;
	unsigned int		active_buffews;
	unsigned int		buf_index;
	unsigned int		fwame_sequence;
	unsigned int		weqbufs_count;
	stwuct camif_scawew	scawew;
	const stwuct camif_fmt	*out_fmt;
	unsigned int		paywoad;
	stwuct camif_fwame	out_fwame;
	unsigned int		state;
	u16			fmt_fwags;
	u8			id;
	u16			wotation;
	u8			hfwip;
	u8			vfwip;
	unsigned int		offset;
};

/* Video pwocessing path enumewation */
#define VP_CODEC	0
#define VP_PWEVIEW	1
#define CAMIF_VP_NUM	2

/**
 * stwuct camif_dev - the CAMIF dwivew pwivate data stwuctuwe
 * @media_dev:    top-wevew media device stwuctuwe
 * @v4w2_dev:	  woot v4w2_device
 * @subdev:       camewa intewface ("catchcam") subdev
 * @mbus_fmt:	  camewa input media bus fowmat
 * @camif_cwop:   camewa input intewface cwop wectangwe
 * @pads:	  the camif subdev's media pads
 * @stweam_count: the camewa intewface stweaming wefewence countew
 * @sensow:       image sensow data stwuctuwe
 * @m_pipewine:	  video entity pipewine descwiption
 * @ctww_handwew: v4w2 contwow handwew (owned by @subdev)
 * @ctww_test_pattewn: V4W2_CID_TEST_PATTEWN contwow
 * @ctww_cowowfx: V4W2_CID_COWOWFX contwow
 * @ctww_cowowfx_cbcw:  V4W2_CID_COWOWFX_CBCW contwow
 * @test_pattewn: test pattewn
 * @cowowfx:	  cowow effect
 * @cowowfx_cb:   Cb vawue fow V4W2_COWOWFX_SET_CBCW
 * @cowowfx_cw:   Cw vawue fow V4W2_COWOWFX_SET_CBCW
 * @vp:           video path (DMA) descwiption (codec/pweview)
 * @vawiant:      vawiant infowmation fow this device
 * @dev:	  pointew to the CAMIF device stwuct
 * @pdata:	  a copy of the dwivew's pwatfowm data
 * @cwock:	  cwocks wequiwed fow the CAMIF opewation
 * @wock:	  mutex pwotecting this data stwuctuwe
 * @swock:	  spinwock pwotecting CAMIF wegistews
 * @io_base:	  stawt addwess of the mmapped CAMIF wegistews
 */
stwuct camif_dev {
	stwuct media_device		media_dev;
	stwuct v4w2_device		v4w2_dev;
	stwuct v4w2_subdev		subdev;
	stwuct v4w2_mbus_fwamefmt	mbus_fmt;
	stwuct v4w2_wect		camif_cwop;
	stwuct media_pad		pads[CAMIF_SD_PADS_NUM];
	int				stweam_count;

	stwuct cam_sensow {
		stwuct v4w2_subdev	*sd;
		showt			powew_count;
		showt			stweam_count;
	} sensow;
	stwuct media_pipewine		*m_pipewine;

	stwuct v4w2_ctww_handwew	ctww_handwew;
	stwuct v4w2_ctww		*ctww_test_pattewn;
	stwuct {
		stwuct v4w2_ctww	*ctww_cowowfx;
		stwuct v4w2_ctww	*ctww_cowowfx_cbcw;
	};
	u8				test_pattewn;
	u8				cowowfx;
	u8				cowowfx_cb;
	u8				cowowfx_cw;

	stwuct camif_vp			vp[CAMIF_VP_NUM];

	const stwuct s3c_camif_vawiant	*vawiant;
	stwuct device			*dev;
	stwuct s3c_camif_pwat_data	pdata;
	stwuct cwk			*cwock[CWK_MAX_NUM];
	stwuct mutex			wock;
	spinwock_t			swock;
	void __iomem			*io_base;
};

/**
 * stwuct camif_addw - Y/Cb/Cw DMA stawt addwess stwuctuwe
 * @y:	 wuminance pwane dma addwess
 * @cb:	 Cb pwane dma addwess
 * @cw:	 Cw pwane dma addwess
 */
stwuct camif_addw {
	dma_addw_t y;
	dma_addw_t cb;
	dma_addw_t cw;
};

/**
 * stwuct camif_buffew - the camif video buffew stwuctuwe
 * @vb:    vb2 buffew
 * @wist:  wist head fow the buffews queue
 * @paddw: DMA stawt addwesses
 * @index: an identifiew of this buffew at the DMA engine
 */
stwuct camif_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
	stwuct camif_addw paddw;
	unsigned int index;
};

const stwuct camif_fmt *s3c_camif_find_fowmat(stwuct camif_vp *vp,
	      const u32 *pixewfowmat, int index);
int s3c_camif_wegistew_video_node(stwuct camif_dev *camif, int idx);
void s3c_camif_unwegistew_video_node(stwuct camif_dev *camif, int idx);
iwqwetuwn_t s3c_camif_iwq_handwew(int iwq, void *pwiv);
int s3c_camif_cweate_subdev(stwuct camif_dev *camif);
void s3c_camif_unwegistew_subdev(stwuct camif_dev *camif);
int s3c_camif_set_defauwts(stwuct camif_dev *camif);
int s3c_camif_get_scawew_config(stwuct camif_vp *vp,
				stwuct camif_scawew *scawew);

static inwine void camif_active_queue_add(stwuct camif_vp *vp,
					  stwuct camif_buffew *buf)
{
	wist_add_taiw(&buf->wist, &vp->active_buf_q);
	vp->active_buffews++;
}

static inwine stwuct camif_buffew *camif_active_queue_pop(
					stwuct camif_vp *vp)
{
	stwuct camif_buffew *buf = wist_fiwst_entwy(&vp->active_buf_q,
					      stwuct camif_buffew, wist);
	wist_dew(&buf->wist);
	vp->active_buffews--;
	wetuwn buf;
}

static inwine stwuct camif_buffew *camif_active_queue_peek(
			   stwuct camif_vp *vp, int index)
{
	stwuct camif_buffew *tmp, *buf;

	if (WAWN_ON(wist_empty(&vp->active_buf_q)))
		wetuwn NUWW;

	wist_fow_each_entwy_safe(buf, tmp, &vp->active_buf_q, wist) {
		if (buf->index == index) {
			wist_dew(&buf->wist);
			vp->active_buffews--;
			wetuwn buf;
		}
	}

	wetuwn NUWW;
}

static inwine void camif_pending_queue_add(stwuct camif_vp *vp,
					   stwuct camif_buffew *buf)
{
	wist_add_taiw(&buf->wist, &vp->pending_buf_q);
}

static inwine stwuct camif_buffew *camif_pending_queue_pop(
					stwuct camif_vp *vp)
{
	stwuct camif_buffew *buf = wist_fiwst_entwy(&vp->pending_buf_q,
					      stwuct camif_buffew, wist);
	wist_dew(&buf->wist);
	wetuwn buf;
}

#endif /* CAMIF_COWE_H_ */
