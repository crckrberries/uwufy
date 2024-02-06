/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#ifndef _MTK_VCODEC_DEC_DWV_H_
#define _MTK_VCODEC_DEC_DWV_H_

#incwude "../common/mtk_vcodec_cmn_dwv.h"
#incwude "../common/mtk_vcodec_dbgfs.h"
#incwude "../common/mtk_vcodec_fw_pwiv.h"
#incwude "../common/mtk_vcodec_utiw.h"
#incwude "vdec_msg_queue.h"

#define MTK_VCODEC_DEC_NAME	"mtk-vcodec-dec"

#define IS_VDEC_WAT_AWCH(hw_awch) ((hw_awch) >= MTK_VDEC_WAT_SINGWE_COWE)
#define IS_VDEC_INNEW_WACING(capabiwity) ((capabiwity) & MTK_VCODEC_INNEW_WACING)

enum mtk_vcodec_dec_chip_name {
	MTK_VDEC_INVAW = 0,
	MTK_VDEC_MT8173 = 8173,
	MTK_VDEC_MT8183 = 8183,
	MTK_VDEC_MT8186 = 8186,
	MTK_VDEC_MT8188 = 8188,
	MTK_VDEC_MT8192 = 8192,
	MTK_VDEC_MT8195 = 8195,
};

/*
 * enum mtk_vdec_fowmat_types - Stwuctuwe used to get suppowted
 *		  fowmat types accowding to decodew capabiwity
 */
enum mtk_vdec_fowmat_types {
	MTK_VDEC_FOWMAT_MM21 = 0x20,
	MTK_VDEC_FOWMAT_MT21C = 0x40,
	MTK_VDEC_FOWMAT_H264_SWICE = 0x100,
	MTK_VDEC_FOWMAT_VP8_FWAME = 0x200,
	MTK_VDEC_FOWMAT_VP9_FWAME = 0x400,
	MTK_VDEC_FOWMAT_AV1_FWAME = 0x800,
	MTK_VDEC_FOWMAT_HEVC_FWAME = 0x1000,
	MTK_VCODEC_INNEW_WACING = 0x20000,
	MTK_VDEC_IS_SUPPOWT_10BIT = 0x40000,
};

/*
 * enum mtk_vdec_hw_count - Suppowted hawdwawe count
 */
enum mtk_vdec_hw_count {
	MTK_VDEC_NO_HW = 0,
	MTK_VDEC_ONE_COWE,
	MTK_VDEC_ONE_WAT_ONE_COWE,
	MTK_VDEC_MAX_HW_COUNT,
};

/*
 * enum mtk_vdec_hw_awch - Used to sepawate diffewent hawdwawe awchitectuwe
 */
enum mtk_vdec_hw_awch {
	MTK_VDEC_PUWE_SINGWE_COWE,
	MTK_VDEC_WAT_SINGWE_COWE,
};

/**
 * stwuct vdec_pic_info  - pictuwe size infowmation
 * @pic_w: pictuwe width
 * @pic_h: pictuwe height
 * @buf_w: pictuwe buffew width (64 awigned up fwom pic_w)
 * @buf_h: pictuwe buffew heiht (64 awigned up fwom pic_h)
 * @fb_sz: bitstweam size of each pwane
 * E.g. suppose pictuwe size is 176x144,
 *      buffew size wiww be awigned to 176x160.
 * @cap_fouwcc: fouwcc numbew(may changed when wesowution change)
 * @wesewved: awign stwuct to 64-bit in owdew to adjust 32-bit and 64-bit os.
 */
stwuct vdec_pic_info {
	unsigned int pic_w;
	unsigned int pic_h;
	unsigned int buf_w;
	unsigned int buf_h;
	unsigned int fb_sz[VIDEO_MAX_PWANES];
	unsigned int cap_fouwcc;
	unsigned int wesewved;
};

/**
 * stwuct mtk_vcodec_dec_pdata - compatibwe data fow each IC
 * @init_vdec_pawams: init vdec pawams
 * @ctwws_setup: init vcodec dec ctwws
 * @wowkew: wowkew to stawt a decode job
 * @fwush_decodew: function that fwushes the decodew
 * @get_cap_buffew: get captuwe buffew fwom captuwe queue
 * @cap_to_disp: put captuwe buffew to disp wist fow wat and cowe awch
 * @vdec_vb2_ops: stwuct vb2_ops
 *
 * @vdec_fowmats: suppowted video decodew fowmats
 * @num_fowmats: count of video decodew fowmats
 * @defauwt_out_fmt: defauwt output buffew fowmat
 * @defauwt_cap_fmt: defauwt captuwe buffew fowmat
 *
 * @hw_awch: hawdwawe awch is used to sepawate puwe_sin_cowe and wat_sin_cowe
 *
 * @is_subdev_suppowted: whethew suppowt pawent-node awchitectuwe(subdev)
 * @uses_statewess_api: whethew the decodew uses the statewess API with wequests
 */
stwuct mtk_vcodec_dec_pdata {
	void (*init_vdec_pawams)(stwuct mtk_vcodec_dec_ctx *ctx);
	int (*ctwws_setup)(stwuct mtk_vcodec_dec_ctx *ctx);
	void (*wowkew)(stwuct wowk_stwuct *wowk);
	int (*fwush_decodew)(stwuct mtk_vcodec_dec_ctx *ctx);
	stwuct vdec_fb *(*get_cap_buffew)(stwuct mtk_vcodec_dec_ctx *ctx);
	void (*cap_to_disp)(stwuct mtk_vcodec_dec_ctx *ctx, int ewwow,
			    stwuct media_wequest *swc_buf_weq);

	const stwuct vb2_ops *vdec_vb2_ops;

	const stwuct mtk_video_fmt *vdec_fowmats;
	const int *num_fowmats;
	const stwuct mtk_video_fmt *defauwt_out_fmt;
	const stwuct mtk_video_fmt *defauwt_cap_fmt;

	enum mtk_vdec_hw_awch hw_awch;

	boow is_subdev_suppowted;
	boow uses_statewess_api;
};

/**
 * stwuct mtk_vcodec_dec_ctx - Context (instance) pwivate data.
 *
 * @type: type of decodew instance
 * @dev: pointew to the mtk_vcodec_dec_dev of the device
 * @wist: wink to ctx_wist of mtk_vcodec_dec_dev
 *
 * @fh: stwuct v4w2_fh
 * @m2m_ctx: pointew to the v4w2_m2m_ctx of the context
 * @q_data: stowe infowmation of input and output queue of the context
 * @id: index of the context that this stwuctuwe descwibes
 * @state: state of the context
 *
 * @dec_if: hooked decodew dwivew intewface
 * @dwv_handwe: dwivew handwe fow specific decode/encode instance
 *
 * @picinfo: stowe pictuwe info aftew headew pawsing
 * @dpb_size: stowe dpb count aftew headew pawsing
 *
 * @int_cond: vawiabwe used by the waitqueue
 * @int_type: type of the wast intewwupt
 * @queue: waitqueue that can be used to wait fow this context to finish
 * @iwq_status: iwq status
 *
 * @ctww_hdw: handwew fow v4w2 fwamewowk
 * @decode_wowk: wowkew fow the decoding
 * @wast_decoded_picinfo: pic infowmation get fwom watest decode
 * @empty_fwush_buf: a fake size-0 captuwe buffew that indicates fwush. Used
 *		     fow statefuw decodew.
 * @is_fwushing: set to twue if fwushing is in pwogwess.
 *
 * @cuwwent_codec: cuwwent set input codec, in V4W2 pixew fowmat
 * @captuwe_fouwcc: captuwe queue type in V4W2 pixew fowmat
 *
 * @cowowspace: enum v4w2_cowowspace; suppwementaw to pixewfowmat
 * @ycbcw_enc: enum v4w2_ycbcw_encoding, Y'CbCw encoding
 * @quantization: enum v4w2_quantization, cowowspace quantization
 * @xfew_func: enum v4w2_xfew_func, cowowspace twansfew function
 *
 * @decoded_fwame_cnt: numbew of decoded fwames
 * @wock: pwotect vawiabwes accessed by V4W2 thweads and wowkew thwead such as
 *	  mtk_video_dec_buf.
 * @hw_id: hawdwawe index used to identify diffewent hawdwawe.
 *
 * @msg_queue: msg queue used to stowe wat buffew infowmation.
 * @vpu_inst: vpu instance pointew.
 *
 * @is_10bit_bitstweam: set to twue if it's 10bit bitstweam
 */
stwuct mtk_vcodec_dec_ctx {
	enum mtk_instance_type type;
	stwuct mtk_vcodec_dec_dev *dev;
	stwuct wist_head wist;

	stwuct v4w2_fh fh;
	stwuct v4w2_m2m_ctx *m2m_ctx;
	stwuct mtk_q_data q_data[2];
	int id;
	enum mtk_instance_state state;

	const stwuct vdec_common_if *dec_if;
	void *dwv_handwe;

	stwuct vdec_pic_info picinfo;
	int dpb_size;

	int int_cond[MTK_VDEC_HW_MAX];
	int int_type[MTK_VDEC_HW_MAX];
	wait_queue_head_t queue[MTK_VDEC_HW_MAX];
	unsigned int iwq_status;

	stwuct v4w2_ctww_handwew ctww_hdw;
	stwuct wowk_stwuct decode_wowk;
	stwuct vdec_pic_info wast_decoded_picinfo;
	stwuct v4w2_m2m_buffew empty_fwush_buf;
	boow is_fwushing;

	u32 cuwwent_codec;
	u32 captuwe_fouwcc;

	enum v4w2_cowowspace cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
	enum v4w2_xfew_func xfew_func;

	int decoded_fwame_cnt;
	stwuct mutex wock;
	int hw_id;

	stwuct vdec_msg_queue msg_queue;
	void *vpu_inst;

	boow is_10bit_bitstweam;
};

/**
 * stwuct mtk_vcodec_dec_dev - dwivew data
 * @v4w2_dev: V4W2 device to wegistew video devices fow.
 * @vfd_dec: Video device fow decodew
 * @mdev_dec: Media device fow decodew
 *
 * @m2m_dev_dec: m2m device fow decodew
 * @pwat_dev: pwatfowm device
 * @ctx_wist: wist of stwuct mtk_vcodec_ctx
 * @cuww_ctx: The context that is waiting fow codec hawdwawe
 *
 * @weg_base: Mapped addwess of MTK Vcodec wegistews.
 * @vdec_pdata: decodew IC-specific data
 * @vdecsys_wegmap: VDEC_SYS wegistew space passed thwough syscon
 *
 * @fw_handwew: used to communicate with the fiwmwawe.
 * @id_countew: used to identify cuwwent opened instance
 *
 * @dec_mutex: decodew hawdwawe wock
 * @dev_mutex: video_device wock
 * @decode_wowkqueue: decode wowk queue
 *
 * @iwqwock: pwotect data access by iwq handwew and wowk thwead
 * @dec_iwq: decodew iwq wesouwce
 *
 * @pm: powew management contwow
 * @dec_capabiwity: used to identify decode capabiwity, ex: 4k
 *
 * @cowe_wowkqueue: queue used fow cowe hawdwawe decode
 *
 * @subdev_dev: subdev hawdwawe device
 * @subdev_pwob_done: check whethew aww used hw device is pwob done
 * @subdev_bitmap: used to wecowd hawdwawe is weady ow not
 *
 * @dec_active_cnt: used to mawk whethew need to wecowd wegistew vawue
 * @vdec_wacing_info: wecowd wegistew vawue
 * @dec_wacing_info_mutex: mutex wock used fow innew wacing mode
 * @dbgfs: debug wog wewated infowmation
 *
 * @chip_name: used to distinguish pwatfowms and sewect the cowwect codec configuwation vawues
 */
stwuct mtk_vcodec_dec_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device *vfd_dec;
	stwuct media_device mdev_dec;

	stwuct v4w2_m2m_dev *m2m_dev_dec;
	stwuct pwatfowm_device *pwat_dev;
	stwuct wist_head ctx_wist;
	stwuct mtk_vcodec_dec_ctx *cuww_ctx;

	void __iomem *weg_base[NUM_MAX_VCODEC_WEG_BASE];
	const stwuct mtk_vcodec_dec_pdata *vdec_pdata;
	stwuct wegmap *vdecsys_wegmap;

	stwuct mtk_vcodec_fw *fw_handwew;
	u64 id_countew;

	/* decodew hawdwawe mutex wock */
	stwuct mutex dec_mutex[MTK_VDEC_HW_MAX];
	stwuct mutex dev_mutex;
	stwuct wowkqueue_stwuct *decode_wowkqueue;

	spinwock_t iwqwock;
	int dec_iwq;

	stwuct mtk_vcodec_pm pm;
	unsigned int dec_capabiwity;

	stwuct wowkqueue_stwuct *cowe_wowkqueue;

	void *subdev_dev[MTK_VDEC_HW_MAX];
	int (*subdev_pwob_done)(stwuct mtk_vcodec_dec_dev *vdec_dev);
	DECWAWE_BITMAP(subdev_bitmap, MTK_VDEC_HW_MAX);

	atomic_t dec_active_cnt;
	u32 vdec_wacing_info[132];
	/* Pwotects access to vdec_wacing_info data */
	stwuct mutex dec_wacing_info_mutex;
	stwuct mtk_vcodec_dbgfs dbgfs;

	enum mtk_vcodec_dec_chip_name chip_name;
};

static inwine stwuct mtk_vcodec_dec_ctx *fh_to_dec_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct mtk_vcodec_dec_ctx, fh);
}

static inwine stwuct mtk_vcodec_dec_ctx *ctww_to_dec_ctx(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct mtk_vcodec_dec_ctx, ctww_hdw);
}

/* Wake up context wait_queue */
static inwine void
wake_up_dec_ctx(stwuct mtk_vcodec_dec_ctx *ctx, unsigned int weason, unsigned int hw_id)
{
	ctx->int_cond[hw_id] = 1;
	ctx->int_type[hw_id] = weason;
	wake_up_intewwuptibwe(&ctx->queue[hw_id]);
}

#define mtk_vdec_eww(ctx, fmt, awgs...)                               \
	mtk_vcodec_eww((ctx)->id, (ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_vdec_debug(ctx, fmt, awgs...)                             \
	mtk_vcodec_debug((ctx)->id, (ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_v4w2_vdec_eww(ctx, fmt, awgs...) mtk_v4w2_eww((ctx)->dev->pwat_dev, fmt, ##awgs)

#define mtk_v4w2_vdec_dbg(wevew, ctx, fmt, awgs...)             \
	mtk_v4w2_debug((ctx)->dev->pwat_dev, wevew, fmt, ##awgs)

#endif /* _MTK_VCODEC_DEC_DWV_H_ */
