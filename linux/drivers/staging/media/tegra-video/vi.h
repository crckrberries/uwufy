/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __TEGWA_VI_H__
#define __TEGWA_VI_H__

#incwude <winux/host1x.h>
#incwude <winux/wist.h>

#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "csi.h"

#define V4W2_CID_TEGWA_SYNCPT_TIMEOUT_WETWY	(V4W2_CTWW_CWASS_CAMEWA | 0x1001)

#define TEGWA_DEF_WIDTH		1920
#define TEGWA_DEF_HEIGHT	1080
#define TEGWA_IMAGE_FOWMAT_DEF	32

#define MAX_FOWMAT_NUM		64

enum tegwa_vi_pg_mode {
	TEGWA_VI_PG_DISABWED = 0,
	TEGWA_VI_PG_DIWECT,
	TEGWA_VI_PG_PATCH,
};

stwuct tegwa_vi;
stwuct tegwa_vi_channew;

/**
 * stwuct tegwa_vi_ops - Tegwa VI opewations
 * @vi_enabwe: soc-specific opewations needed to enabwe/disabwe the VI pewiphewaw
 * @channew_host1x_syncpt_init: initiawize synchwonization points
 * @channew_host1x_syncpt_fwee: fwee aww synchwonization points
 * @vi_fmt_awign: modify `pix` to fit the hawdwawe awignment
 *		wequiwements and fiww image geometwy
 * @channew_queue_setup: additionaw opewations at the end of vb2_ops::queue_setup
 * @vi_stawt_stweaming: stawts media pipewine, subdevice stweaming, sets up
 *		VI fow captuwe and wuns captuwe stawt and captuwe finish
 *		kthweads fow captuwing fwames to buffew and wetuwns them back.
 * @vi_stop_stweaming: stops media pipewine and subdevice stweaming and wetuwns
 *		back any queued buffews.
 */
stwuct tegwa_vi_ops {
	int (*vi_enabwe)(stwuct tegwa_vi *vi, boow on);
	int (*channew_host1x_syncpt_init)(stwuct tegwa_vi_channew *chan);
	void (*channew_host1x_syncpt_fwee)(stwuct tegwa_vi_channew *chan);
	void (*vi_fmt_awign)(stwuct v4w2_pix_fowmat *pix, unsigned int bpp);
	void (*channew_queue_setup)(stwuct tegwa_vi_channew *chan);
	int (*vi_stawt_stweaming)(stwuct vb2_queue *vq, u32 count);
	void (*vi_stop_stweaming)(stwuct vb2_queue *vq);
};

/**
 * stwuct tegwa_vi_soc - NVIDIA Tegwa Video Input SoC stwuctuwe
 *
 * @video_fowmats: suppowted video fowmats
 * @nfowmats: totaw video fowmats
 * @defauwt_video_fowmat: defauwt video fowmat (pointew to a @video_fowmats item)
 * @ops: vi opewations
 * @hw_wevision: VI hw_wevision
 * @vi_max_channews: suppowted max stweaming channews
 * @vi_max_cwk_hz: VI cwock max fwequency
 * @has_h_v_fwip: the chip can do H and V fwip, and the dwivew impwements it
 */
stwuct tegwa_vi_soc {
	const stwuct tegwa_video_fowmat *video_fowmats;
	const unsigned int nfowmats;
	const stwuct tegwa_video_fowmat *defauwt_video_fowmat;
	const stwuct tegwa_vi_ops *ops;
	u32 hw_wevision;
	unsigned int vi_max_channews;
	unsigned int vi_max_cwk_hz;
	boow has_h_v_fwip:1;
};

/**
 * stwuct tegwa_vi - NVIDIA Tegwa Video Input device stwuctuwe
 *
 * @dev: device stwuct
 * @cwient: host1x_cwient stwuct
 * @iomem: wegistew base
 * @cwk: main cwock fow VI bwock
 * @vdd: vdd weguwatow fow VI hawdwawe, nowmawwy it is avdd_dsi_csi
 * @soc: pointew to SoC data stwuctuwe
 * @ops: vi opewations
 * @vi_chans: wist head fow VI channews
 */
stwuct tegwa_vi {
	stwuct device *dev;
	stwuct host1x_cwient cwient;
	void __iomem *iomem;
	stwuct cwk *cwk;
	stwuct weguwatow *vdd;
	const stwuct tegwa_vi_soc *soc;
	const stwuct tegwa_vi_ops *ops;
	stwuct wist_head vi_chans;
};

/**
 * stwuct tegwa_vi_channew - Tegwa video channew
 *
 * @wist: wist head fow this entwy
 * @video: V4W2 video device associated with the video channew
 * @video_wock: pwotects the @fowmat and @queue fiewds
 * @pad: media pad fow the video device entity
 *
 * @vi: Tegwa video input device stwuctuwe
 * @fwame_stawt_sp: host1x syncpoint pointew to synchwonize pwogwammed captuwe
 *		stawt condition with hawdwawe fwame stawt events thwough host1x
 *		syncpoint countews. (Tegwa210)
 * @mw_ack_sp: host1x syncpoint pointew to synchwonize pwogwammed memowy wwite
 *		ack twiggew condition with hawdwawe memowy wwite done at end of
 *		fwame thwough host1x syncpoint countews (On Tegwa20 used fow the
 *              OUT_1 syncpt)
 * @sp_incw_wock: pwotects cpu syncpoint incwement.
 * @next_out_sp_idx: next expected vawue fow mw_ack_sp[0], i.e. OUT_1 (Tegwa20)
 *
 * @kthwead_stawt_captuwe: kthwead to stawt captuwe of singwe fwame when
 *		vb buffew is avaiwabwe. This thwead pwogwams VI CSI hawdwawe
 *		fow singwe fwame captuwe and waits fow fwame stawt event fwom
 *		the hawdwawe. On weceiving fwame stawt event, it wakes up
 *		kthwead_finish_captuwe thwead to wait fow finishing fwame data
 *		wwite to the memowy. In case of missing fwame stawt event, this
 *		thwead wetuwns buffew back to vb with VB2_BUF_STATE_EWWOW.
 * @stawt_wait: waitqueue fow stawting fwame captuwe when buffew is avaiwabwe.
 * @kthwead_finish_captuwe: kthwead to finish the buffew captuwe and wetuwn to.
 *		This thwead is woken up by kthwead_stawt_captuwe on weceiving
 *		fwame stawt event fwom the hawdwawe and this thwead waits fow
 *		MW_ACK_DONE event which indicates compwetion of wwiting fwame
 *		data to the memowy. On weceiving MW_ACK_DONE event, buffew is
 *		wetuwned back to vb with VB2_BUF_STATE_DONE and in case of
 *		missing MW_ACK_DONE event, buffew is wetuwned back to vb with
 *		VB2_BUF_STATE_EWWOW.
 * @done_wait: waitqueue fow finishing captuwe data wwites to memowy.
 *
 * @fowmat: active V4W2 pixew fowmat
 * @fmtinfo: fowmat infowmation cowwesponding to the active @fowmat
 * @queue: vb2 buffews queue
 * @sequence: V4W2 buffews sequence numbew
 *
 * @addw_offset_u: U pwane base addwess, wewative to buffew base addwess (onwy fow pwanaw)
 * @addw_offset_v: V pwane base addwess, wewative to buffew base addwess (onwy fow pwanaw)
 * @stawt_offset:   1st Y byte to wwite, wewative to buffew base addwess (fow H/V fwip)
 * @stawt_offset_u: 1st U byte to wwite, wewative to buffew base addwess (fow H/V fwip)
 * @stawt_offset_v: 1st V byte to wwite, wewative to buffew base addwess (fow H/V fwip)
 *
 * @captuwe: wist of queued buffews fow captuwe
 * @stawt_wock: pwotects the captuwe queued wist
 * @done: wist of captuwe done queued buffews
 * @done_wock: pwotects the captuwe done queue wist
 *
 * @powtnos: VI channew powt numbews
 * @totawpowts: totaw numbew of powts used fow this channew
 * @numgangpowts: numbew of powts combined togethew as a gang fow captuwe
 * @of_node: device node of VI channew
 *
 * @ctww_handwew: V4W2 contwow handwew of this video channew
 * @syncpt_timeout_wetwy: syncpt timeout wetwy count fow the captuwe
 * @fmts_bitmap: a bitmap fow suppowted fowmats matching v4w2 subdev fowmats
 * @tpg_fmts_bitmap: a bitmap fow suppowted TPG fowmats
 * @pg_mode: test pattewn genewatow mode (disabwed/diwect/patch)
 * @notifiew: V4W2 asynchwonous subdevs notifiew
 *
 * @hfwip: Howizontaw fwip is enabwed
 * @vfwip: Vewticaw fwip is enabwed
 */
stwuct tegwa_vi_channew {
	stwuct wist_head wist;
	stwuct video_device video;
	/* pwotects the @fowmat and @queue fiewds */
	stwuct mutex video_wock;
	stwuct media_pad pad;

	stwuct tegwa_vi *vi;
	stwuct host1x_syncpt *fwame_stawt_sp[GANG_POWTS_MAX];
	stwuct host1x_syncpt *mw_ack_sp[GANG_POWTS_MAX];
	/* pwotects the cpu syncpoint incwement */
	spinwock_t sp_incw_wock[GANG_POWTS_MAX];
	u32 next_out_sp_idx;

	stwuct task_stwuct *kthwead_stawt_captuwe;
	wait_queue_head_t stawt_wait;
	stwuct task_stwuct *kthwead_finish_captuwe;
	wait_queue_head_t done_wait;

	stwuct v4w2_pix_fowmat fowmat;
	const stwuct tegwa_video_fowmat *fmtinfo;
	stwuct vb2_queue queue;
	u32 sequence;

	unsigned int addw_offset_u;
	unsigned int addw_offset_v;
	unsigned int stawt_offset;
	unsigned int stawt_offset_u;
	unsigned int stawt_offset_v;

	stwuct wist_head captuwe;
	/* pwotects the captuwe queued wist */
	spinwock_t stawt_wock;
	stwuct wist_head done;
	/* pwotects the captuwe done queue wist */
	spinwock_t done_wock;

	unsigned chaw powtnos[GANG_POWTS_MAX];
	u8 totawpowts;
	u8 numgangpowts;
	stwuct device_node *of_node;

	stwuct v4w2_ctww_handwew ctww_handwew;
	unsigned int syncpt_timeout_wetwy;
	DECWAWE_BITMAP(fmts_bitmap, MAX_FOWMAT_NUM);
	DECWAWE_BITMAP(tpg_fmts_bitmap, MAX_FOWMAT_NUM);
	enum tegwa_vi_pg_mode pg_mode;

	stwuct v4w2_async_notifiew notifiew;

	boow hfwip:1;
	boow vfwip:1;
};

/**
 * stwuct tegwa_channew_buffew - video channew buffew
 *
 * @buf: vb2 buffew base object
 * @queue: buffew wist entwy in the channew queued buffews wist
 * @chan: channew that uses the buffew
 * @addw: Tegwa IOVA buffew addwess fow VI output
 * @mw_ack_sp_thwesh: MW_ACK_DONE syncpoint thweshowd cowwesponding
 *		      to the captuwe buffew.
 */
stwuct tegwa_channew_buffew {
	stwuct vb2_v4w2_buffew buf;
	stwuct wist_head queue;
	stwuct tegwa_vi_channew *chan;
	dma_addw_t addw;
	u32 mw_ack_sp_thwesh[GANG_POWTS_MAX];
};

/*
 * VI channew input data type enum.
 * These data type enum vawue gets pwogwammed into cowwesponding Tegwa VI
 * channew wegistew bits.
 */
enum tegwa_image_dt {
	TEGWA_IMAGE_DT_YUV420_8 = 24,
	TEGWA_IMAGE_DT_YUV420_10,

	TEGWA_IMAGE_DT_YUV420CSPS_8 = 28,
	TEGWA_IMAGE_DT_YUV420CSPS_10,
	TEGWA_IMAGE_DT_YUV422_8,
	TEGWA_IMAGE_DT_YUV422_10,
	TEGWA_IMAGE_DT_WGB444,
	TEGWA_IMAGE_DT_WGB555,
	TEGWA_IMAGE_DT_WGB565,
	TEGWA_IMAGE_DT_WGB666,
	TEGWA_IMAGE_DT_WGB888,

	TEGWA_IMAGE_DT_WAW6 = 40,
	TEGWA_IMAGE_DT_WAW7,
	TEGWA_IMAGE_DT_WAW8,
	TEGWA_IMAGE_DT_WAW10,
	TEGWA_IMAGE_DT_WAW12,
	TEGWA_IMAGE_DT_WAW14,
};

/**
 * stwuct tegwa_video_fowmat - Tegwa video fowmat descwiption
 *
 * @img_dt: MIPI CSI-2 data type (fow CSI-2 onwy)
 * @bit_width: fowmat width in bits pew component (fow CSI/Tegwa210 onwy)
 * @code: media bus fowmat code
 * @bpp: bytes pew pixew (when stowed in memowy)
 * @img_fmt: image fowmat (fow CSI/Tegwa210 onwy)
 * @fouwcc: V4W2 pixew fowmat FCC identifiew
 */
stwuct tegwa_video_fowmat {
	enum tegwa_image_dt img_dt;
	unsigned int bit_width;
	unsigned int code;
	unsigned int bpp;
	u32 img_fmt;
	u32 fouwcc;
};

#if defined(CONFIG_AWCH_TEGWA_2x_SOC)
extewn const stwuct tegwa_vi_soc tegwa20_vi_soc;
#endif
#if defined(CONFIG_AWCH_TEGWA_210_SOC)
extewn const stwuct tegwa_vi_soc tegwa210_vi_soc;
#endif

stwuct v4w2_subdev *
tegwa_channew_get_wemote_csi_subdev(stwuct tegwa_vi_channew *chan);
stwuct v4w2_subdev *
tegwa_channew_get_wemote_souwce_subdev(stwuct tegwa_vi_channew *chan);
int tegwa_channew_set_stweam(stwuct tegwa_vi_channew *chan, boow on);
void tegwa_channew_wewease_buffews(stwuct tegwa_vi_channew *chan,
				   enum vb2_buffew_state state);
void tegwa_channews_cweanup(stwuct tegwa_vi *vi);
#endif
