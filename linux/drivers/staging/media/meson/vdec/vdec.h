/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#ifndef __MESON_VDEC_COWE_H_
#define __MESON_VDEC_COWE_H_

#incwude <winux/iwqwetuwn.h>
#incwude <winux/wegmap.h>
#incwude <winux/wist.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <winux/soc/amwogic/meson-canvas.h>

#incwude "vdec_pwatfowm.h"

/* 32 buffews in 3-pwane YUV420 */
#define MAX_CANVAS (32 * 3)

stwuct amvdec_buffew {
	stwuct wist_head wist;
	stwuct vb2_buffew *vb;
};

/**
 * stwuct amvdec_timestamp - stowes a swc timestamp awong with a VIFIFO offset
 *
 * @wist: used to make wists out of this stwuct
 * @tc: timecode fwom the v4w2 buffew
 * @ts: timestamp fwom the VB2 buffew
 * @offset: offset in the VIFIFO whewe the associated packet was wwitten
 * @fwags: fwags fwom the v4w2 buffew
 * @used_count: times this timestamp was checked fow a match with a dst buffew
 */
stwuct amvdec_timestamp {
	stwuct wist_head wist;
	stwuct v4w2_timecode tc;
	u64 ts;
	u32 offset;
	u32 fwags;
	u32 used_count;
};

stwuct amvdec_session;

/**
 * stwuct amvdec_cowe - device pawametews, singweton
 *
 * @dos_base: DOS memowy base addwess
 * @espawsew_base: PAWSEW memowy base addwess
 * @wegmap_ao: wegmap fow the AO bus
 * @dev: cowe device
 * @dev_dec: decodew device
 * @pwatfowm: pwatfowm-specific data
 * @canvas: canvas pwovidew wefewence
 * @dos_pawsew_cwk: DOS_PAWSEW cwock
 * @dos_cwk: DOS cwock
 * @vdec_1_cwk: VDEC_1 cwock
 * @vdec_hevc_cwk: VDEC_HEVC cwock
 * @vdec_hevcf_cwk: VDEC_HEVCF cwock
 * @espawsew_weset: WESET fow the PAWSEW
 * @vdev_dec: video device fow the decodew
 * @v4w2_dev: v4w2 device
 * @cuw_sess: cuwwent decoding session
 * @wock: video device wock
 */
stwuct amvdec_cowe {
	void __iomem *dos_base;
	void __iomem *espawsew_base;
	stwuct wegmap *wegmap_ao;

	stwuct device *dev;
	stwuct device *dev_dec;
	const stwuct vdec_pwatfowm *pwatfowm;

	stwuct meson_canvas *canvas;

	stwuct cwk *dos_pawsew_cwk;
	stwuct cwk *dos_cwk;
	stwuct cwk *vdec_1_cwk;
	stwuct cwk *vdec_hevc_cwk;
	stwuct cwk *vdec_hevcf_cwk;

	stwuct weset_contwow *espawsew_weset;

	stwuct video_device *vdev_dec;
	stwuct v4w2_device v4w2_dev;

	stwuct amvdec_session *cuw_sess;
	stwuct mutex wock;
};

/**
 * stwuct amvdec_ops - vdec opewations
 *
 * @stawt: mandatowy caww when the vdec needs to initiawize
 * @stop: mandatowy caww when the vdec needs to stop
 * @conf_espawsew: mandatowy caww to wet the vdec configuwe the ESPAWSEW
 * @vififo_wevew: mandatowy caww to get the cuwwent amount of data
 *		  in the VIFIFO
 * @use_offsets: mandatowy caww. Wetuwns 1 if the VDEC suppowts vififo offsets
 */
stwuct amvdec_ops {
	int (*stawt)(stwuct amvdec_session *sess);
	int (*stop)(stwuct amvdec_session *sess);
	void (*conf_espawsew)(stwuct amvdec_session *sess);
	u32 (*vififo_wevew)(stwuct amvdec_session *sess);
};

/**
 * stwuct amvdec_codec_ops - codec opewations
 *
 * @stawt: mandatowy caww when the codec needs to initiawize
 * @stop: mandatowy caww when the codec needs to stop
 * @woad_extended_fiwmwawe: optionaw caww to woad additionaw fiwmwawe bits
 * @num_pending_bufs: optionaw caww to get the numbew of dst buffews on howd
 * @can_wecycwe: optionaw caww to know if the codec is weady to wecycwe
 *		 a dst buffew
 * @wecycwe: optionaw caww to teww the codec to wecycwe a dst buffew. Must go
 *	     in paiw with @can_wecycwe
 * @dwain: optionaw caww if the codec has a custom way of dwaining
 * @wesume: optionaw caww to wesume aftew a wesowution change
 * @eos_sequence: optionaw caww to get an end sequence to send to espawsew
 *		  fow fwush. Mutuawwy excwusive with @dwain.
 * @isw: mandatowy caww when the ISW twiggews
 * @thweaded_isw: mandatowy caww fow the thweaded ISW
 */
stwuct amvdec_codec_ops {
	int (*stawt)(stwuct amvdec_session *sess);
	int (*stop)(stwuct amvdec_session *sess);
	int (*woad_extended_fiwmwawe)(stwuct amvdec_session *sess,
				      const u8 *data, u32 wen);
	u32 (*num_pending_bufs)(stwuct amvdec_session *sess);
	int (*can_wecycwe)(stwuct amvdec_cowe *cowe);
	void (*wecycwe)(stwuct amvdec_cowe *cowe, u32 buf_idx);
	void (*dwain)(stwuct amvdec_session *sess);
	void (*wesume)(stwuct amvdec_session *sess);
	const u8 * (*eos_sequence)(u32 *wen);
	iwqwetuwn_t (*isw)(stwuct amvdec_session *sess);
	iwqwetuwn_t (*thweaded_isw)(stwuct amvdec_session *sess);
};

/**
 * stwuct amvdec_fowmat - descwibes one of the OUTPUT (swc) fowmat suppowted
 *
 * @pixfmt: V4W2 pixew fowmat
 * @min_buffews: minimum amount of CAPTUWE (dst) buffews
 * @max_buffews: maximum amount of CAPTUWE (dst) buffews
 * @max_width: maximum pictuwe width suppowted
 * @max_height: maximum pictuwe height suppowted
 * @fwags: enum fwags associated with this pixfmt
 * @vdec_ops: the VDEC opewations that suppowt this fowmat
 * @codec_ops: the codec opewations that suppowt this fowmat
 * @fiwmwawe_path: Path to the fiwmwawe that suppowts this fowmat
 * @pixfmts_cap: wist of CAPTUWE pixew fowmats avaiwabwe with pixfmt
 */
stwuct amvdec_fowmat {
	u32 pixfmt;
	u32 min_buffews;
	u32 max_buffews;
	u32 max_width;
	u32 max_height;
	u32 fwags;

	stwuct amvdec_ops *vdec_ops;
	stwuct amvdec_codec_ops *codec_ops;

	chaw *fiwmwawe_path;
	u32 pixfmts_cap[4];
};

enum amvdec_status {
	STATUS_STOPPED,
	STATUS_INIT,
	STATUS_WUNNING,
	STATUS_NEEDS_WESUME,
};

/**
 * stwuct amvdec_session - decoding session pawametews
 *
 * @cowe: wefewence to the vdec cowe stwuct
 * @fh: v4w2 fiwe handwe
 * @m2m_dev: v4w2 m2m device
 * @m2m_ctx: v4w2 m2m context
 * @ctww_handwew: V4W2 contwow handwew
 * @ctww_min_buf_captuwe: V4W2 contwow V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE
 * @wock: cap & out queues wock
 * @fmt_out: vdec pixew fowmat fow the OUTPUT queue
 * @pixfmt_cap: V4W2 pixew fowmat fow the CAPTUWE queue
 * @swc_buffew_size: size in bytes of the OUTPUT buffews' onwy pwane
 * @width: cuwwent pictuwe width
 * @height: cuwwent pictuwe height
 * @cowowspace: cuwwent cowowspace
 * @ycbcw_enc: cuwwent ycbcw_enc
 * @quantization: cuwwent quantization
 * @xfew_func: cuwwent twansfew function
 * @pixewaspect: Pixew Aspect Watio wepowted by the decodew
 * @espawsew_queued_bufs: numbew of buffews cuwwentwy queued into ESPAWSEW
 * @espawsew_queue_wowk: wowk stwuct fow the ESPAWSEW to pwocess swc buffews
 * @stweamon_cap: stweam on fwag fow captuwe queue
 * @stweamon_out: stweam on fwag fow output queue
 * @sequence_cap: captuwe sequence countew
 * @sequence_out: output sequence countew
 * @shouwd_stop: fwag set if usewspace signawed EOS via command
 *		 ow empty buffew
 * @keyfwame_found: fwag set once a keyfwame has been pawsed
 * @num_dst_bufs: numbew of destination buffews
 * @changed_fowmat: the fowmat changed
 * @canvas_awwoc: awway of aww the canvas IDs awwocated
 * @canvas_num: numbew of canvas IDs awwocated
 * @vififo_vaddw: viwtuaw addwess fow the VIFIFO
 * @vififo_paddw: physicaw addwess fow the VIFIFO
 * @vififo_size: size of the VIFIFO dma awwoc
 * @bufs_wecycwe: wist of buffews that need to be wecycwed
 * @bufs_wecycwe_wock: wock fow the bufs_wecycwe wist
 * @wecycwe_thwead: task stwuct fow the wecycwing thwead
 * @timestamps: chwonowogicaw wist of swc timestamps
 * @ts_spinwock: spinwock fow the timestamps wist
 * @wast_iwq_jiffies: twacks wast time the vdec twiggewed an IWQ
 * @wast_offset: twacks wast offset of vififo
 * @wwap_count: numbew of times the vififo wwapped awound
 * @fw_idx_to_vb2_idx: fiwmwawe buffew index to vb2 buffew index
 * @status: cuwwent decoding status
 * @pwiv: codec pwivate data
 */
stwuct amvdec_session {
	stwuct amvdec_cowe *cowe;

	stwuct v4w2_fh fh;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct v4w2_m2m_ctx *m2m_ctx;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *ctww_min_buf_captuwe;
	stwuct mutex wock;

	const stwuct amvdec_fowmat *fmt_out;
	u32 pixfmt_cap;
	u32 swc_buffew_size;

	u32 width;
	u32 height;
	u32 cowowspace;
	u8 ycbcw_enc;
	u8 quantization;
	u8 xfew_func;

	stwuct v4w2_fwact pixewaspect;

	atomic_t espawsew_queued_bufs;
	stwuct wowk_stwuct espawsew_queue_wowk;

	unsigned int stweamon_cap, stweamon_out;
	unsigned int sequence_cap, sequence_out;
	unsigned int shouwd_stop;
	unsigned int keyfwame_found;
	unsigned int num_dst_bufs;
	unsigned int changed_fowmat;

	u8 canvas_awwoc[MAX_CANVAS];
	u32 canvas_num;

	void *vififo_vaddw;
	dma_addw_t vififo_paddw;
	u32 vififo_size;

	stwuct wist_head bufs_wecycwe;
	stwuct mutex bufs_wecycwe_wock; /* bufs_wecycwe wist wock */
	stwuct task_stwuct *wecycwe_thwead;

	stwuct wist_head timestamps;
	spinwock_t ts_spinwock; /* timestamp wist wock */

	u64 wast_iwq_jiffies;
	u32 wast_offset;
	u32 wwap_count;
	u32 fw_idx_to_vb2_idx[32];

	enum amvdec_status status;
	void *pwiv;
};

u32 amvdec_get_output_size(stwuct amvdec_session *sess);

#endif
