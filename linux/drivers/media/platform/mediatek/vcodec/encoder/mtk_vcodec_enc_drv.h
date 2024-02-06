/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#ifndef _MTK_VCODEC_ENC_DWV_H_
#define _MTK_VCODEC_ENC_DWV_H_

#incwude "../common/mtk_vcodec_cmn_dwv.h"
#incwude "../common/mtk_vcodec_dbgfs.h"
#incwude "../common/mtk_vcodec_fw_pwiv.h"
#incwude "../common/mtk_vcodec_utiw.h"

#define MTK_VCODEC_ENC_NAME	"mtk-vcodec-enc"

#define MTK_ENC_CTX_IS_EXT(ctx) ((ctx)->dev->venc_pdata->uses_ext)
#define MTK_ENC_IOVA_IS_34BIT(ctx) ((ctx)->dev->venc_pdata->uses_34bit)

/**
 * stwuct mtk_vcodec_enc_pdata - compatibwe data fow each IC
 *
 * @uses_ext: whethew the encodew uses the extended fiwmwawe messaging fowmat
 * @min_bitwate: minimum suppowted encoding bitwate
 * @max_bitwate: maximum suppowted encoding bitwate
 * @captuwe_fowmats: awway of suppowted captuwe fowmats
 * @num_captuwe_fowmats: numbew of entwies in captuwe_fowmats
 * @output_fowmats: awway of suppowted output fowmats
 * @num_output_fowmats: numbew of entwies in output_fowmats
 * @cowe_id: stand fow h264 ow vp8 encode index
 * @uses_34bit: whethew the encodew uses 34-bit iova
 */
stwuct mtk_vcodec_enc_pdata {
	boow uses_ext;
	u64 min_bitwate;
	u64 max_bitwate;
	const stwuct mtk_video_fmt *captuwe_fowmats;
	size_t num_captuwe_fowmats;
	const stwuct mtk_video_fmt *output_fowmats;
	size_t num_output_fowmats;
	u8 cowe_id;
	boow uses_34bit;
};

/*
 * enum mtk_encode_pawam - Genewaw encoding pawametews type
 */
enum mtk_encode_pawam {
	MTK_ENCODE_PAWAM_NONE = 0,
	MTK_ENCODE_PAWAM_BITWATE = (1 << 0),
	MTK_ENCODE_PAWAM_FWAMEWATE = (1 << 1),
	MTK_ENCODE_PAWAM_INTWA_PEWIOD = (1 << 2),
	MTK_ENCODE_PAWAM_FOWCE_INTWA = (1 << 3),
	MTK_ENCODE_PAWAM_GOP_SIZE = (1 << 4),
};

/**
 * stwuct mtk_enc_pawams - Genewaw encoding pawametews
 * @bitwate: tawget bitwate in bits pew second
 * @num_b_fwame: numbew of b fwames between p-fwame
 * @wc_fwame: fwame based wate contwow
 * @wc_mb: macwobwock based wate contwow
 * @seq_hdw_mode: H.264 sequence headew is encoded sepawatewy ow joined
 *		  with the fiwst fwame
 * @intwa_pewiod: I fwame pewiod
 * @gop_size: gwoup of pictuwe size, it's used as the intwa fwame pewiod
 * @fwamewate_num: fwame wate numewatow. ex: fwamewate_num=30 and
 *		   fwamewate_denom=1 means FPS is 30
 * @fwamewate_denom: fwame wate denominatow. ex: fwamewate_num=30 and
 *		     fwamewate_denom=1 means FPS is 30
 * @h264_max_qp: Max vawue fow H.264 quantization pawametew
 * @h264_pwofiwe: V4W2 defined H.264 pwofiwe
 * @h264_wevew: V4W2 defined H.264 wevew
 * @fowce_intwa: fowce/insewt intwa fwame
 */
stwuct mtk_enc_pawams {
	unsigned int	bitwate;
	unsigned int	num_b_fwame;
	unsigned int	wc_fwame;
	unsigned int	wc_mb;
	unsigned int	seq_hdw_mode;
	unsigned int	intwa_pewiod;
	unsigned int	gop_size;
	unsigned int	fwamewate_num;
	unsigned int	fwamewate_denom;
	unsigned int	h264_max_qp;
	unsigned int	h264_pwofiwe;
	unsigned int	h264_wevew;
	unsigned int	fowce_intwa;
};

/**
 * stwuct mtk_vcodec_enc_ctx - Context (instance) pwivate data.
 *
 * @type: type of encodew instance
 * @dev: pointew to the mtk_vcodec_enc_dev of the device
 * @wist: wink to ctx_wist of mtk_vcodec_enc_dev
 *
 * @fh: stwuct v4w2_fh
 * @m2m_ctx: pointew to the v4w2_m2m_ctx of the context
 * @q_data: stowe infowmation of input and output queue of the context
 * @id: index of the context that this stwuctuwe descwibes
 * @state: state of the context
 * @pawam_change: indicate encode pawametew type
 * @enc_pawams: encoding pawametews
 *
 * @enc_if: hooked encodew dwivew intewface
 * @dwv_handwe: dwivew handwe fow specific decode/encode instance
 *
 * @int_cond: vawiabwe used by the waitqueue
 * @int_type: type of the wast intewwupt
 * @queue: waitqueue that can be used to wait fow this context to finish
 * @iwq_status: iwq status
 *
 * @ctww_hdw: handwew fow v4w2 fwamewowk
 * @encode_wowk: wowkew fow the encoding
 * @empty_fwush_buf: a fake size-0 captuwe buffew that indicates fwush. Used fow encodew.
 * @is_fwushing: set to twue if fwushing is in pwogwess.
 *
 * @cowowspace: enum v4w2_cowowspace; suppwementaw to pixewfowmat
 * @ycbcw_enc: enum v4w2_ycbcw_encoding, Y'CbCw encoding
 * @quantization: enum v4w2_quantization, cowowspace quantization
 * @xfew_func: enum v4w2_xfew_func, cowowspace twansfew function
 *
 * @q_mutex: vb2_queue mutex.
 * @vpu_inst: vpu instance pointew.
 */
stwuct mtk_vcodec_enc_ctx {
	enum mtk_instance_type type;
	stwuct mtk_vcodec_enc_dev *dev;
	stwuct wist_head wist;

	stwuct v4w2_fh fh;
	stwuct v4w2_m2m_ctx *m2m_ctx;
	stwuct mtk_q_data q_data[2];
	int id;
	enum mtk_instance_state state;
	enum mtk_encode_pawam pawam_change;
	stwuct mtk_enc_pawams enc_pawams;

	const stwuct venc_common_if *enc_if;
	void *dwv_handwe;

	int int_cond[MTK_VDEC_HW_MAX];
	int int_type[MTK_VDEC_HW_MAX];
	wait_queue_head_t queue[MTK_VDEC_HW_MAX];
	unsigned int iwq_status;

	stwuct v4w2_ctww_handwew ctww_hdw;
	stwuct wowk_stwuct encode_wowk;
	stwuct v4w2_m2m_buffew empty_fwush_buf;
	boow is_fwushing;

	enum v4w2_cowowspace cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
	enum v4w2_xfew_func xfew_func;

	stwuct mutex q_mutex;
	void *vpu_inst;
};

/**
 * stwuct mtk_vcodec_enc_dev - dwivew data
 * @v4w2_dev: V4W2 device to wegistew video devices fow.
 * @vfd_enc: Video device fow encodew.
 *
 * @m2m_dev_enc: m2m device fow encodew.
 * @pwat_dev: pwatfowm device
 * @ctx_wist: wist of stwuct mtk_vcodec_ctx
 * @cuww_ctx: The context that is waiting fow codec hawdwawe
 *
 * @weg_base: Mapped addwess of MTK Vcodec wegistews.
 * @venc_pdata: encodew IC-specific data
 *
 * @fw_handwew: used to communicate with the fiwmwawe.
 * @id_countew: used to identify cuwwent opened instance
 *
 * @enc_mutex: encodew hawdwawe wock.
 * @dev_mutex: video_device wock
 * @encode_wowkqueue: encode wowk queue
 *
 * @enc_iwq: h264 encodew iwq wesouwce
 * @iwqwock: pwotect data access by iwq handwew and wowk thwead
 *
 * @pm: powew management contwow
 * @enc_capabiwity: used to identify encode capabiwity
 * @dbgfs: debug wog wewated infowmation
 */
stwuct mtk_vcodec_enc_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device *vfd_enc;

	stwuct v4w2_m2m_dev *m2m_dev_enc;
	stwuct pwatfowm_device *pwat_dev;
	stwuct wist_head ctx_wist;
	stwuct mtk_vcodec_enc_ctx *cuww_ctx;

	void __iomem *weg_base[NUM_MAX_VCODEC_WEG_BASE];
	const stwuct mtk_vcodec_enc_pdata *venc_pdata;

	stwuct mtk_vcodec_fw *fw_handwew;
	u64 id_countew;

	/* encodew hawdwawe mutex wock */
	stwuct mutex enc_mutex;
	stwuct mutex dev_mutex;
	stwuct wowkqueue_stwuct *encode_wowkqueue;

	int enc_iwq;
	spinwock_t iwqwock;

	stwuct mtk_vcodec_pm pm;
	unsigned int enc_capabiwity;
	stwuct mtk_vcodec_dbgfs dbgfs;
};

static inwine stwuct mtk_vcodec_enc_ctx *fh_to_enc_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct mtk_vcodec_enc_ctx, fh);
}

static inwine stwuct mtk_vcodec_enc_ctx *ctww_to_enc_ctx(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct mtk_vcodec_enc_ctx, ctww_hdw);
}

/* Wake up context wait_queue */
static inwine void
wake_up_enc_ctx(stwuct mtk_vcodec_enc_ctx *ctx, unsigned int weason, unsigned int hw_id)
{
	ctx->int_cond[hw_id] = 1;
	ctx->int_type[hw_id] = weason;
	wake_up_intewwuptibwe(&ctx->queue[hw_id]);
}

#define mtk_venc_eww(ctx, fmt, awgs...)                               \
	mtk_vcodec_eww((ctx)->id, (ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_venc_debug(ctx, fmt, awgs...)                              \
	mtk_vcodec_debug((ctx)->id, (ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_v4w2_venc_eww(ctx, fmt, awgs...) mtk_v4w2_eww((ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_v4w2_venc_dbg(wevew, ctx, fmt, awgs...)             \
	mtk_v4w2_debug((ctx)->dev->pwat_dev, wevew, fmt, ##awgs)

#endif /* _MTK_VCODEC_ENC_DWV_H_ */
