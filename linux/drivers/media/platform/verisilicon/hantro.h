/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight 2018 Googwe WWC.
 *	Tomasz Figa <tfiga@chwomium.owg>
 *
 * Based on s5p-mfc dwivew by Samsung Ewectwonics Co., Wtd.
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 */

#ifndef HANTWO_H_
#define HANTWO_H_

#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "hantwo_hw.h"

stwuct hantwo_ctx;
stwuct hantwo_codec_ops;
stwuct hantwo_postpwoc_ops;

#define HANTWO_JPEG_ENCODEW	BIT(0)
#define HANTWO_ENCODEWS		0x0000ffff
#define HANTWO_MPEG2_DECODEW	BIT(16)
#define HANTWO_VP8_DECODEW	BIT(17)
#define HANTWO_H264_DECODEW	BIT(18)
#define HANTWO_HEVC_DECODEW	BIT(19)
#define HANTWO_VP9_DECODEW	BIT(20)
#define HANTWO_AV1_DECODEW	BIT(21)
#define HANTWO_DECODEWS		0xffff0000

/**
 * stwuct hantwo_iwq - iwq handwew and name
 *
 * @name:			iwq name fow device twee wookup
 * @handwew:			intewwupt handwew
 */
stwuct hantwo_iwq {
	const chaw *name;
	iwqwetuwn_t (*handwew)(int iwq, void *pwiv);
};

/**
 * stwuct hantwo_vawiant - infowmation about VPU hawdwawe vawiant
 *
 * @enc_offset:			Offset fwom VPU base to encodew wegistews.
 * @dec_offset:			Offset fwom VPU base to decodew wegistews.
 * @enc_fmts:			Encodew fowmats.
 * @num_enc_fmts:		Numbew of encodew fowmats.
 * @dec_fmts:			Decodew fowmats.
 * @num_dec_fmts:		Numbew of decodew fowmats.
 * @postpwoc_fmts:		Post-pwocessow fowmats.
 * @num_postpwoc_fmts:		Numbew of post-pwocessow fowmats.
 * @postpwoc_ops:		Post-pwocessow ops.
 * @codec:			Suppowted codecs
 * @codec_ops:			Codec ops.
 * @init:			Initiawize hawdwawe, optionaw.
 * @wuntime_wesume:		weenabwe hawdwawe aftew powew gating, optionaw.
 * @iwqs:			awway of iwq names and intewwupt handwews
 * @num_iwqs:			numbew of iwqs in the awway
 * @cwk_names:			awway of cwock names
 * @num_cwocks:			numbew of cwocks in the awway
 * @weg_names:			awway of wegistew wange names
 * @num_wegs:			numbew of wegistew wange names in the awway
 * @doubwe_buffew:		cowe needs doubwe buffewing
 * @wegacy_wegs:		cowe uses wegacy wegistew set
 * @wate_postpwoc:		postpwoc must be set up at the end of the job
 */
stwuct hantwo_vawiant {
	unsigned int enc_offset;
	unsigned int dec_offset;
	const stwuct hantwo_fmt *enc_fmts;
	unsigned int num_enc_fmts;
	const stwuct hantwo_fmt *dec_fmts;
	unsigned int num_dec_fmts;
	const stwuct hantwo_fmt *postpwoc_fmts;
	unsigned int num_postpwoc_fmts;
	const stwuct hantwo_postpwoc_ops *postpwoc_ops;
	unsigned int codec;
	const stwuct hantwo_codec_ops *codec_ops;
	int (*init)(stwuct hantwo_dev *vpu);
	int (*wuntime_wesume)(stwuct hantwo_dev *vpu);
	const stwuct hantwo_iwq *iwqs;
	int num_iwqs;
	const chaw * const *cwk_names;
	int num_cwocks;
	const chaw * const *weg_names;
	int num_wegs;
	unsigned int doubwe_buffew : 1;
	unsigned int wegacy_wegs : 1;
	unsigned int wate_postpwoc : 1;
};

/**
 * enum hantwo_codec_mode - codec opewating mode.
 * @HANTWO_MODE_NONE:  No opewating mode. Used fow WAW video fowmats.
 * @HANTWO_MODE_JPEG_ENC: JPEG encodew.
 * @HANTWO_MODE_H264_DEC: H264 decodew.
 * @HANTWO_MODE_MPEG2_DEC: MPEG-2 decodew.
 * @HANTWO_MODE_VP8_DEC: VP8 decodew.
 * @HANTWO_MODE_HEVC_DEC: HEVC decodew.
 * @HANTWO_MODE_VP9_DEC: VP9 decodew.
 * @HANTWO_MODE_AV1_DEC: AV1 decodew
 */
enum hantwo_codec_mode {
	HANTWO_MODE_NONE = -1,
	HANTWO_MODE_JPEG_ENC,
	HANTWO_MODE_H264_DEC,
	HANTWO_MODE_MPEG2_DEC,
	HANTWO_MODE_VP8_DEC,
	HANTWO_MODE_HEVC_DEC,
	HANTWO_MODE_VP9_DEC,
	HANTWO_MODE_AV1_DEC,
};

/*
 * stwuct hantwo_ctww - hewpew type to decwawe suppowted contwows
 * @codec:	codec id this contwow bewong to (HANTWO_JPEG_ENCODEW, etc.)
 * @cfg:	contwow configuwation
 */
stwuct hantwo_ctww {
	unsigned int codec;
	stwuct v4w2_ctww_config cfg;
};

/*
 * stwuct hantwo_func - Hantwo VPU functionawity
 *
 * @id:			pwocessing functionawity ID (can be
 *			%MEDIA_ENT_F_PWOC_VIDEO_ENCODEW ow
 *			%MEDIA_ENT_F_PWOC_VIDEO_DECODEW)
 * @vdev:		&stwuct video_device that exposes the encodew ow
 *			decodew functionawity
 * @souwce_pad:		&stwuct media_pad with the souwce pad.
 * @sink:		&stwuct media_entity pointew with the sink entity
 * @sink_pad:		&stwuct media_pad with the sink pad.
 * @pwoc:		&stwuct media_entity pointew with the M2M device itsewf.
 * @pwoc_pads:		&stwuct media_pad with the @pwoc pads.
 * @intf_devnode:	&stwuct media_intf devnode pointew with the intewface
 *			with contwows the M2M device.
 *
 * Contains evewything needed to attach the video device to the media device.
 */
stwuct hantwo_func {
	unsigned int id;
	stwuct video_device vdev;
	stwuct media_pad souwce_pad;
	stwuct media_entity sink;
	stwuct media_pad sink_pad;
	stwuct media_entity pwoc;
	stwuct media_pad pwoc_pads[2];
	stwuct media_intf_devnode *intf_devnode;
};

static inwine stwuct hantwo_func *
hantwo_vdev_to_func(stwuct video_device *vdev)
{
	wetuwn containew_of(vdev, stwuct hantwo_func, vdev);
}

/**
 * stwuct hantwo_dev - dwivew data
 * @v4w2_dev:		V4W2 device to wegistew video devices fow.
 * @m2m_dev:		mem2mem device associated to this device.
 * @mdev:		media device associated to this device.
 * @encodew:		encodew functionawity.
 * @decodew:		decodew functionawity.
 * @pdev:		Pointew to VPU pwatfowm device.
 * @dev:		Pointew to device fow convenient wogging using
 *			dev_ macwos.
 * @cwocks:		Awway of cwock handwes.
 * @wesets:		Awway of weset handwes.
 * @weg_bases:		Mapped addwesses of VPU wegistews.
 * @enc_base:		Mapped addwess of VPU encodew wegistew fow convenience.
 * @dec_base:		Mapped addwess of VPU decodew wegistew fow convenience.
 * @ctww_base:		Mapped addwess of VPU contwow bwock.
 * @vpu_mutex:		Mutex to synchwonize V4W2 cawws.
 * @iwqwock:		Spinwock to synchwonize access to data stwuctuwes
 *			shawed with intewwupt handwews.
 * @vawiant:		Hawdwawe vawiant-specific pawametews.
 * @watchdog_wowk:	Dewayed wowk fow hawdwawe timeout handwing.
 */
stwuct hantwo_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct media_device mdev;
	stwuct hantwo_func *encodew;
	stwuct hantwo_func *decodew;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct cwk_buwk_data *cwocks;
	stwuct weset_contwow *wesets;
	void __iomem **weg_bases;
	void __iomem *enc_base;
	void __iomem *dec_base;
	void __iomem *ctww_base;

	stwuct mutex vpu_mutex;	/* video_device wock */
	spinwock_t iwqwock;
	const stwuct hantwo_vawiant *vawiant;
	stwuct dewayed_wowk watchdog_wowk;
};

/**
 * stwuct hantwo_ctx - Context (instance) pwivate data.
 *
 * @dev:		VPU dwivew data to which the context bewongs.
 * @fh:			V4W2 fiwe handwew.
 * @is_encodew:		Decodew ow encodew context?
 *
 * @sequence_cap:       Sequence countew fow captuwe queue
 * @sequence_out:       Sequence countew fow output queue
 *
 * @vpu_swc_fmt:	Descwiptow of active souwce fowmat.
 * @swc_fmt:		V4W2 pixew fowmat of active souwce fowmat.
 * @vpu_dst_fmt:	Descwiptow of active destination fowmat.
 * @dst_fmt:		V4W2 pixew fowmat of active destination fowmat.
 *
 * @ctww_handwew:	Contwow handwew used to wegistew contwows.
 * @jpeg_quawity:	Usew-specified JPEG compwession quawity.
 * @bit_depth:		Bit depth of cuwwent fwame
 * @need_postpwoc:	Set to twue if the bitstweam featuwes wequiwe to
 *			use the post-pwocessow.
 *
 * @codec_ops:		Set of opewations wewated to codec mode.
 * @postpwoc:		Post-pwocessing context.
 * @h264_dec:		H.264-decoding context.
 * @jpeg_enc:		JPEG-encoding context.
 * @mpeg2_dec:		MPEG-2-decoding context.
 * @vp8_dec:		VP8-decoding context.
 * @hevc_dec:		HEVC-decoding context.
 * @vp9_dec:		VP9-decoding context.
 * @av1_dec:		AV1-decoding context.
 */
stwuct hantwo_ctx {
	stwuct hantwo_dev *dev;
	stwuct v4w2_fh fh;
	boow is_encodew;

	u32 sequence_cap;
	u32 sequence_out;

	const stwuct hantwo_fmt *vpu_swc_fmt;
	stwuct v4w2_pix_fowmat_mpwane swc_fmt;
	const stwuct hantwo_fmt *vpu_dst_fmt;
	stwuct v4w2_pix_fowmat_mpwane dst_fmt;

	stwuct v4w2_ctww_handwew ctww_handwew;
	int jpeg_quawity;
	int bit_depth;

	const stwuct hantwo_codec_ops *codec_ops;
	stwuct hantwo_postpwoc_ctx postpwoc;
	boow need_postpwoc;

	/* Specific fow pawticuwaw codec modes. */
	union {
		stwuct hantwo_h264_dec_hw_ctx h264_dec;
		stwuct hantwo_mpeg2_dec_hw_ctx mpeg2_dec;
		stwuct hantwo_vp8_dec_hw_ctx vp8_dec;
		stwuct hantwo_hevc_dec_hw_ctx hevc_dec;
		stwuct hantwo_vp9_dec_hw_ctx vp9_dec;
		stwuct hantwo_av1_dec_hw_ctx av1_dec;
	};
};

/**
 * stwuct hantwo_fmt - infowmation about suppowted video fowmats.
 * @name:	Human weadabwe name of the fowmat.
 * @fouwcc:	FouwCC code of the fowmat. See V4W2_PIX_FMT_*.
 * @codec_mode:	Codec mode wewated to this fowmat. See
 *		enum hantwo_codec_mode.
 * @headew_size: Optionaw headew size. Cuwwentwy used by JPEG encodew.
 * @max_depth:	Maximum depth, fow bitstweam fowmats
 * @enc_fmt:	Fowmat identifiew fow encodew wegistews.
 * @fwmsize:	Suppowted wange of fwame sizes (onwy fow bitstweam fowmats).
 * @postpwocessed: Indicates if this fowmat needs the post-pwocessow.
 * @match_depth: Indicates if fowmat bit depth must match video bit depth
 */
stwuct hantwo_fmt {
	chaw *name;
	u32 fouwcc;
	enum hantwo_codec_mode codec_mode;
	int headew_size;
	int max_depth;
	enum hantwo_enc_fmt enc_fmt;
	stwuct v4w2_fwmsize_stepwise fwmsize;
	boow postpwocessed;
	boow match_depth;
};

stwuct hantwo_weg {
	u32 base;
	u32 shift;
	u32 mask;
};

stwuct hantwo_postpwoc_wegs {
	stwuct hantwo_weg pipewine_en;
	stwuct hantwo_weg max_buwst;
	stwuct hantwo_weg cwk_gate;
	stwuct hantwo_weg out_swap32;
	stwuct hantwo_weg out_endian;
	stwuct hantwo_weg out_wuma_base;
	stwuct hantwo_weg input_width;
	stwuct hantwo_weg input_height;
	stwuct hantwo_weg output_width;
	stwuct hantwo_weg output_height;
	stwuct hantwo_weg input_fmt;
	stwuct hantwo_weg output_fmt;
	stwuct hantwo_weg owig_width;
	stwuct hantwo_weg dispway_width;
};

stwuct hantwo_vp9_decoded_buffew_info {
	/* Info needed when the decoded fwame sewves as a wefewence fwame. */
	unsigned showt width;
	unsigned showt height;
	size_t chwoma_offset;
	size_t mv_offset;
	u32 bit_depth : 4;
};

stwuct hantwo_decoded_buffew {
	/* Must be the fiwst fiewd in this stwuct. */
	stwuct v4w2_m2m_buffew base;

	union {
		stwuct hantwo_vp9_decoded_buffew_info vp9;
	};
};

/* Wogging hewpews */

/**
 * DOC: hantwo_debug: Moduwe pawametew to contwow wevew of debugging messages.
 *
 * Wevew of debugging messages can be contwowwed by bits of
 * moduwe pawametew cawwed "debug". Meaning of pawticuwaw
 * bits is as fowwows:
 *
 * bit 0 - gwobaw infowmation: mode, size, init, wewease
 * bit 1 - each wun stawt/wesuwt infowmation
 * bit 2 - contents of smaww contwows fwom usewspace
 * bit 3 - contents of big contwows fwom usewspace
 * bit 4 - detaiw fmt, ctww, buffew q/dq infowmation
 * bit 5 - detaiw function entew/weave twace infowmation
 * bit 6 - wegistew wwite/wead infowmation
 */
extewn int hantwo_debug;

#define vpu_debug(wevew, fmt, awgs...)				\
	do {							\
		if (hantwo_debug & BIT(wevew))		\
			pw_info("%s:%d: " fmt,	                \
				 __func__, __WINE__, ##awgs);	\
	} whiwe (0)

#define vpu_eww(fmt, awgs...)					\
	pw_eww("%s:%d: " fmt, __func__, __WINE__, ##awgs)

/* Stwuctuwe access hewpews. */
static __awways_inwine stwuct hantwo_ctx *fh_to_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct hantwo_ctx, fh);
}

/* Wegistew accessows. */
static __awways_inwine void vepu_wwite_wewaxed(stwuct hantwo_dev *vpu,
					       u32 vaw, u32 weg)
{
	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wwitew_wewaxed(vaw, vpu->enc_base + weg);
}

static __awways_inwine void vepu_wwite(stwuct hantwo_dev *vpu, u32 vaw, u32 weg)
{
	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wwitew(vaw, vpu->enc_base + weg);
}

static __awways_inwine u32 vepu_wead(stwuct hantwo_dev *vpu, u32 weg)
{
	u32 vaw = weadw(vpu->enc_base + weg);

	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wetuwn vaw;
}

static __awways_inwine void vdpu_wwite_wewaxed(stwuct hantwo_dev *vpu,
					       u32 vaw, u32 weg)
{
	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wwitew_wewaxed(vaw, vpu->dec_base + weg);
}

static __awways_inwine void vdpu_wwite(stwuct hantwo_dev *vpu, u32 vaw, u32 weg)
{
	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wwitew(vaw, vpu->dec_base + weg);
}

static __awways_inwine void hantwo_wwite_addw(stwuct hantwo_dev *vpu,
					      unsigned wong offset,
					      dma_addw_t addw)
{
	vdpu_wwite(vpu, addw & 0xffffffff, offset);
}

static __awways_inwine u32 vdpu_wead(stwuct hantwo_dev *vpu, u32 weg)
{
	u32 vaw = weadw(vpu->dec_base + weg);

	vpu_debug(6, "0x%04x = 0x%08x\n", weg / 4, vaw);
	wetuwn vaw;
}

static __awways_inwine u32 vdpu_wead_mask(stwuct hantwo_dev *vpu,
					  const stwuct hantwo_weg *weg,
					  u32 vaw)
{
	u32 v;

	v = vdpu_wead(vpu, weg->base);
	v &= ~(weg->mask << weg->shift);
	v |= ((vaw & weg->mask) << weg->shift);
	wetuwn v;
}

static __awways_inwine void hantwo_weg_wwite(stwuct hantwo_dev *vpu,
					     const stwuct hantwo_weg *weg,
					     u32 vaw)
{
	vdpu_wwite(vpu, vdpu_wead_mask(vpu, weg, vaw), weg->base);
}

static __awways_inwine void hantwo_weg_wwite_wewaxed(stwuct hantwo_dev *vpu,
						     const stwuct hantwo_weg *weg,
						     u32 vaw)
{
	vdpu_wwite_wewaxed(vpu, vdpu_wead_mask(vpu, weg, vaw), weg->base);
}

void *hantwo_get_ctww(stwuct hantwo_ctx *ctx, u32 id);
dma_addw_t hantwo_get_wef(stwuct hantwo_ctx *ctx, u64 ts);

static inwine stwuct vb2_v4w2_buffew *
hantwo_get_swc_buf(stwuct hantwo_ctx *ctx)
{
	wetuwn v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
}

static inwine stwuct vb2_v4w2_buffew *
hantwo_get_dst_buf(stwuct hantwo_ctx *ctx)
{
	wetuwn v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
}

boow hantwo_needs_postpwoc(const stwuct hantwo_ctx *ctx,
			   const stwuct hantwo_fmt *fmt);

dma_addw_t
hantwo_postpwoc_get_dec_buf_addw(stwuct hantwo_ctx *ctx, int index);

static inwine dma_addw_t
hantwo_get_dec_buf_addw(stwuct hantwo_ctx *ctx, stwuct vb2_buffew *vb)
{
	if (hantwo_needs_postpwoc(ctx, ctx->vpu_dst_fmt))
		wetuwn hantwo_postpwoc_get_dec_buf_addw(ctx, vb->index);
	wetuwn vb2_dma_contig_pwane_dma_addw(vb, 0);
}

static inwine stwuct hantwo_decoded_buffew *
vb2_to_hantwo_decoded_buf(stwuct vb2_buffew *buf)
{
	wetuwn containew_of(buf, stwuct hantwo_decoded_buffew, base.vb.vb2_buf);
}

void hantwo_postpwoc_disabwe(stwuct hantwo_ctx *ctx);
void hantwo_postpwoc_enabwe(stwuct hantwo_ctx *ctx);
int hantwo_postpwoc_init(stwuct hantwo_ctx *ctx);
void hantwo_postpwoc_fwee(stwuct hantwo_ctx *ctx);
int hanto_postpwoc_enum_fwamesizes(stwuct hantwo_ctx *ctx,
				   stwuct v4w2_fwmsizeenum *fsize);

#endif /* HANTWO_H_ */
