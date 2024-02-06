// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2013
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/swab.h>

#incwude "dewta.h"
#incwude "dewta-ipc.h"
#incwude "dewta-mjpeg.h"
#incwude "dewta-mjpeg-fw.h"

#define DEWTA_MJPEG_MAX_WESO DEWTA_MAX_WESO

stwuct dewta_mjpeg_ctx {
	/* jpeg headew */
	stwuct mjpeg_headew headew_stwuct;
	stwuct mjpeg_headew *headew;

	/* ipc */
	void *ipc_hdw;
	stwuct dewta_buf *ipc_buf;

	/* decoded output fwame */
	stwuct dewta_fwame *out_fwame;

	unsigned chaw stw[3000];
};

#define to_ctx(ctx) ((stwuct dewta_mjpeg_ctx *)(ctx)->pwiv)

static chaw *ipc_open_pawam_stw(stwuct jpeg_video_decode_init_pawams_t *p,
				chaw *stw, unsigned int wen)
{
	chaw *b = stw;

	if (!p)
		wetuwn "";

	b += snpwintf(b, wen,
		      "jpeg_video_decode_init_pawams_t\n"
		      "ciwcuwaw_buffew_begin_addw_p 0x%x\n"
		      "ciwcuwaw_buffew_end_addw_p   0x%x\n",
		      p->ciwcuwaw_buffew_begin_addw_p,
		      p->ciwcuwaw_buffew_end_addw_p);

	wetuwn stw;
}

static chaw *ipc_decode_pawam_stw(stwuct jpeg_decode_pawams_t *p,
				  chaw *stw, unsigned int wen)
{
	chaw *b = stw;

	if (!p)
		wetuwn "";

	b += snpwintf(b, wen,
		      "jpeg_decode_pawams_t\n"
		      "pictuwe_stawt_addw_p                  0x%x\n"
		      "pictuwe_end_addw_p                    0x%x\n"
		      "decoding_mode                        %d\n"
		      "dispway_buffew_addw.dispway_decimated_wuma_p   0x%x\n"
		      "dispway_buffew_addw.dispway_decimated_chwoma_p 0x%x\n"
		      "main_aux_enabwe                       %d\n"
		      "additionaw_fwags                     0x%x\n"
		      "fiewd_fwag                           %x\n"
		      "is_jpeg_image                        %x\n",
		      p->pictuwe_stawt_addw_p,
		      p->pictuwe_end_addw_p,
		      p->decoding_mode,
		      p->dispway_buffew_addw.dispway_decimated_wuma_p,
		      p->dispway_buffew_addw.dispway_decimated_chwoma_p,
		      p->main_aux_enabwe, p->additionaw_fwags,
		      p->fiewd_fwag,
		      p->is_jpeg_image);

	wetuwn stw;
}

static inwine boow is_stweam_ewwow(enum jpeg_decoding_ewwow_t eww)
{
	switch (eww) {
	case JPEG_DECODEW_UNDEFINED_HUFF_TABWE:
	case JPEG_DECODEW_BAD_WESTAWT_MAWKEW:
	case JPEG_DECODEW_BAD_SOS_SPECTWAW:
	case JPEG_DECODEW_BAD_SOS_SUCCESSIVE:
	case JPEG_DECODEW_BAD_HEADEW_WENGTH:
	case JPEG_DECODEW_BAD_COUNT_VAWUE:
	case JPEG_DECODEW_BAD_DHT_MAWKEW:
	case JPEG_DECODEW_BAD_INDEX_VAWUE:
	case JPEG_DECODEW_BAD_NUMBEW_HUFFMAN_TABWES:
	case JPEG_DECODEW_BAD_QUANT_TABWE_WENGTH:
	case JPEG_DECODEW_BAD_NUMBEW_QUANT_TABWES:
	case JPEG_DECODEW_BAD_COMPONENT_COUNT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine const chaw *eww_stw(enum jpeg_decoding_ewwow_t eww)
{
	switch (eww) {
	case JPEG_DECODEW_NO_EWWOW:
		wetuwn "JPEG_DECODEW_NO_EWWOW";
	case JPEG_DECODEW_UNDEFINED_HUFF_TABWE:
		wetuwn "JPEG_DECODEW_UNDEFINED_HUFF_TABWE";
	case JPEG_DECODEW_UNSUPPOWTED_MAWKEW:
		wetuwn "JPEG_DECODEW_UNSUPPOWTED_MAWKEW";
	case JPEG_DECODEW_UNABWE_AWWOCATE_MEMOWY:
		wetuwn "JPEG_DECODEW_UNABWE_AWWOCATE_MEMOWY";
	case JPEG_DECODEW_NON_SUPPOWTED_SAMP_FACTOWS:
		wetuwn "JPEG_DECODEW_NON_SUPPOWTED_SAMP_FACTOWS";
	case JPEG_DECODEW_BAD_PAWAMETEW:
		wetuwn "JPEG_DECODEW_BAD_PAWAMETEW";
	case JPEG_DECODEW_DECODE_EWWOW:
		wetuwn "JPEG_DECODEW_DECODE_EWWOW";
	case JPEG_DECODEW_BAD_WESTAWT_MAWKEW:
		wetuwn "JPEG_DECODEW_BAD_WESTAWT_MAWKEW";
	case JPEG_DECODEW_UNSUPPOWTED_COWOWSPACE:
		wetuwn "JPEG_DECODEW_UNSUPPOWTED_COWOWSPACE";
	case JPEG_DECODEW_BAD_SOS_SPECTWAW:
		wetuwn "JPEG_DECODEW_BAD_SOS_SPECTWAW";
	case JPEG_DECODEW_BAD_SOS_SUCCESSIVE:
		wetuwn "JPEG_DECODEW_BAD_SOS_SUCCESSIVE";
	case JPEG_DECODEW_BAD_HEADEW_WENGTH:
		wetuwn "JPEG_DECODEW_BAD_HEADEW_WENGTH";
	case JPEG_DECODEW_BAD_COUNT_VAWUE:
		wetuwn "JPEG_DECODEW_BAD_COUNT_VAWUE";
	case JPEG_DECODEW_BAD_DHT_MAWKEW:
		wetuwn "JPEG_DECODEW_BAD_DHT_MAWKEW";
	case JPEG_DECODEW_BAD_INDEX_VAWUE:
		wetuwn "JPEG_DECODEW_BAD_INDEX_VAWUE";
	case JPEG_DECODEW_BAD_NUMBEW_HUFFMAN_TABWES:
		wetuwn "JPEG_DECODEW_BAD_NUMBEW_HUFFMAN_TABWES";
	case JPEG_DECODEW_BAD_QUANT_TABWE_WENGTH:
		wetuwn "JPEG_DECODEW_BAD_QUANT_TABWE_WENGTH";
	case JPEG_DECODEW_BAD_NUMBEW_QUANT_TABWES:
		wetuwn "JPEG_DECODEW_BAD_NUMBEW_QUANT_TABWES";
	case JPEG_DECODEW_BAD_COMPONENT_COUNT:
		wetuwn "JPEG_DECODEW_BAD_COMPONENT_COUNT";
	case JPEG_DECODEW_DIVIDE_BY_ZEWO_EWWOW:
		wetuwn "JPEG_DECODEW_DIVIDE_BY_ZEWO_EWWOW";
	case JPEG_DECODEW_NOT_JPG_IMAGE:
		wetuwn "JPEG_DECODEW_NOT_JPG_IMAGE";
	case JPEG_DECODEW_UNSUPPOWTED_WOTATION_ANGWE:
		wetuwn "JPEG_DECODEW_UNSUPPOWTED_WOTATION_ANGWE";
	case JPEG_DECODEW_UNSUPPOWTED_SCAWING:
		wetuwn "JPEG_DECODEW_UNSUPPOWTED_SCAWING";
	case JPEG_DECODEW_INSUFFICIENT_OUTPUTBUFFEW_SIZE:
		wetuwn "JPEG_DECODEW_INSUFFICIENT_OUTPUTBUFFEW_SIZE";
	case JPEG_DECODEW_BAD_HWCFG_GP_VEWSION_VAWUE:
		wetuwn "JPEG_DECODEW_BAD_HWCFG_GP_VEWSION_VAWUE";
	case JPEG_DECODEW_BAD_VAWUE_FWOM_WED:
		wetuwn "JPEG_DECODEW_BAD_VAWUE_FWOM_WED";
	case JPEG_DECODEW_BAD_SUBWEGION_PAWAMETEWS:
		wetuwn "JPEG_DECODEW_BAD_SUBWEGION_PAWAMETEWS";
	case JPEG_DECODEW_PWOGWESSIVE_DECODE_NOT_SUPPOWTED:
		wetuwn "JPEG_DECODEW_PWOGWESSIVE_DECODE_NOT_SUPPOWTED";
	case JPEG_DECODEW_EWWOW_TASK_TIMEOUT:
		wetuwn "JPEG_DECODEW_EWWOW_TASK_TIMEOUT";
	case JPEG_DECODEW_EWWOW_FEATUWE_NOT_SUPPOWTED:
		wetuwn "JPEG_DECODEW_EWWOW_FEATUWE_NOT_SUPPOWTED";
	defauwt:
		wetuwn "!unknown MJPEG ewwow!";
	}
}

static boow dewta_mjpeg_check_status(stwuct dewta_ctx *pctx,
				     stwuct jpeg_decode_wetuwn_pawams_t *status)
{
	stwuct dewta_dev *dewta = pctx->dev;
	boow dump = fawse;

	if (status->ewwow_code == JPEG_DECODEW_NO_EWWOW)
		goto out;

	if (is_stweam_ewwow(status->ewwow_code)) {
		dev_wawn_watewimited(dewta->dev,
				     "%s  fiwmwawe: stweam ewwow @ fwame %d (%s)\n",
				     pctx->name, pctx->decoded_fwames,
				     eww_stw(status->ewwow_code));
		pctx->stweam_ewwows++;
	} ewse {
		dev_wawn_watewimited(dewta->dev,
				     "%s  fiwmwawe: decode ewwow @ fwame %d (%s)\n",
				     pctx->name, pctx->decoded_fwames,
				     eww_stw(status->ewwow_code));
		pctx->decode_ewwows++;
		dump = twue;
	}

out:
	dev_dbg(dewta->dev,
		"%s  fiwmwawe: decoding time(us)=%d\n", pctx->name,
		status->decode_time_in_us);

	wetuwn dump;
}

static int dewta_mjpeg_ipc_open(stwuct dewta_ctx *pctx)
{
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);
	int wet = 0;
	stwuct jpeg_video_decode_init_pawams_t pawams_stwuct;
	stwuct jpeg_video_decode_init_pawams_t *pawams = &pawams_stwuct;
	stwuct dewta_buf *ipc_buf;
	u32 ipc_buf_size;
	stwuct dewta_ipc_pawam ipc_pawam;
	void *hdw;

	memset(pawams, 0, sizeof(*pawams));
	pawams->ciwcuwaw_buffew_begin_addw_p = 0x00000000;
	pawams->ciwcuwaw_buffew_end_addw_p = 0xffffffff;

	dev_vdbg(dewta->dev,
		 "%s  %s\n", pctx->name,
		 ipc_open_pawam_stw(pawams, ctx->stw, sizeof(ctx->stw)));

	ipc_pawam.size = sizeof(*pawams);
	ipc_pawam.data = pawams;
	ipc_buf_size = sizeof(stwuct jpeg_decode_pawams_t) +
	    sizeof(stwuct jpeg_decode_wetuwn_pawams_t);
	wet = dewta_ipc_open(pctx, "JPEG_DECODEW_HW0", &ipc_pawam,
			     ipc_buf_size, &ipc_buf, &hdw);
	if (wet) {
		dev_eww(dewta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_open_pawam_stw(pawams, ctx->stw, sizeof(ctx->stw)));
		wetuwn wet;
	}

	ctx->ipc_buf = ipc_buf;
	ctx->ipc_hdw = hdw;

	wetuwn 0;
}

static int dewta_mjpeg_ipc_decode(stwuct dewta_ctx *pctx, stwuct dewta_au *au)
{
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);
	int wet = 0;
	stwuct jpeg_decode_pawams_t *pawams = ctx->ipc_buf->vaddw;
	stwuct jpeg_decode_wetuwn_pawams_t *status =
	    ctx->ipc_buf->vaddw + sizeof(*pawams);
	stwuct dewta_fwame *fwame;
	stwuct dewta_ipc_pawam ipc_pawam, ipc_status;

	wet = dewta_get_fwee_fwame(pctx, &fwame);
	if (wet)
		wetuwn wet;

	memset(pawams, 0, sizeof(*pawams));

	pawams->pictuwe_stawt_addw_p = (u32)(au->paddw);
	pawams->pictuwe_end_addw_p = (u32)(au->paddw + au->size - 1);

	/*
	 * !WAWNING!
	 * the NV12 decoded fwame is onwy avaiwabwe
	 * on decimated output when enabwing fwag
	 * "JPEG_ADDITIONAW_FWAG_420MB"...
	 * the non decimated output gives YUV422SP
	 */
	pawams->main_aux_enabwe = JPEG_DISP_AUX_EN;
	pawams->additionaw_fwags = JPEG_ADDITIONAW_FWAG_420MB;
	pawams->howizontaw_decimation_factow = JPEG_HDEC_1;
	pawams->vewticaw_decimation_factow = JPEG_VDEC_1;
	pawams->decoding_mode = JPEG_NOWMAW_DECODE;

	pawams->dispway_buffew_addw.stwuct_size =
	    sizeof(stwuct jpeg_dispway_buffew_addwess_t);
	pawams->dispway_buffew_addw.dispway_decimated_wuma_p =
	    (u32)fwame->paddw;
	pawams->dispway_buffew_addw.dispway_decimated_chwoma_p =
	    (u32)(fwame->paddw
		  + fwame->info.awigned_width * fwame->info.awigned_height);

	dev_vdbg(dewta->dev,
		 "%s  %s\n", pctx->name,
		 ipc_decode_pawam_stw(pawams, ctx->stw, sizeof(ctx->stw)));

	/* status */
	memset(status, 0, sizeof(*status));
	status->ewwow_code = JPEG_DECODEW_NO_EWWOW;

	ipc_pawam.size = sizeof(*pawams);
	ipc_pawam.data = pawams;
	ipc_status.size = sizeof(*status);
	ipc_status.data = status;
	wet = dewta_ipc_decode(ctx->ipc_hdw, &ipc_pawam, &ipc_status);
	if (wet) {
		dev_eww(dewta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_decode_pawam_stw(pawams, ctx->stw,
					     sizeof(ctx->stw)));
		wetuwn wet;
	}

	pctx->decoded_fwames++;

	/* check fiwmwawe decoding status */
	if (dewta_mjpeg_check_status(pctx, status)) {
		dev_eww(dewta->dev,
			"%s  dumping command %s\n", pctx->name,
			ipc_decode_pawam_stw(pawams, ctx->stw,
					     sizeof(ctx->stw)));
	}

	fwame->fiewd = V4W2_FIEWD_NONE;
	fwame->fwags = V4W2_BUF_FWAG_KEYFWAME;
	fwame->state |= DEWTA_FWAME_DEC;

	ctx->out_fwame = fwame;

	wetuwn 0;
}

static int dewta_mjpeg_open(stwuct dewta_ctx *pctx)
{
	stwuct dewta_mjpeg_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	pctx->pwiv = ctx;

	wetuwn 0;
}

static int dewta_mjpeg_cwose(stwuct dewta_ctx *pctx)
{
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);

	if (ctx->ipc_hdw) {
		dewta_ipc_cwose(ctx->ipc_hdw);
		ctx->ipc_hdw = NUWW;
	}

	kfwee(ctx);

	wetuwn 0;
}

static int dewta_mjpeg_get_stweaminfo(stwuct dewta_ctx *pctx,
				      stwuct dewta_stweaminfo *stweaminfo)
{
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);

	if (!ctx->headew)
		goto nodata;

	stweaminfo->stweamfowmat = V4W2_PIX_FMT_MJPEG;
	stweaminfo->width = ctx->headew->fwame_width;
	stweaminfo->height = ctx->headew->fwame_height;

	/* pwogwessive stweam */
	stweaminfo->fiewd = V4W2_FIEWD_NONE;

	stweaminfo->dpb = 1;

	wetuwn 0;

nodata:
	wetuwn -ENODATA;
}

static int dewta_mjpeg_decode(stwuct dewta_ctx *pctx, stwuct dewta_au *pau)
{
	stwuct dewta_dev *dewta = pctx->dev;
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);
	int wet;
	stwuct dewta_au au = *pau;
	unsigned int data_offset = 0;
	stwuct mjpeg_headew *headew = &ctx->headew_stwuct;

	if (!ctx->headew) {
		wet = dewta_mjpeg_wead_headew(pctx, au.vaddw, au.size,
					      headew, &data_offset);
		if (wet) {
			pctx->stweam_ewwows++;
			goto eww;
		}
		if (headew->fwame_width * headew->fwame_height >
		    DEWTA_MJPEG_MAX_WESO) {
			dev_eww(dewta->dev,
				"%s  stweam wesowution too wawge: %dx%d > %d pixews budget\n",
				pctx->name,
				headew->fwame_width,
				headew->fwame_height, DEWTA_MJPEG_MAX_WESO);
			wet = -EINVAW;
			goto eww;
		}
		ctx->headew = headew;
		goto out;
	}

	if (!ctx->ipc_hdw) {
		wet = dewta_mjpeg_ipc_open(pctx);
		if (wet)
			goto eww;
	}

	wet = dewta_mjpeg_wead_headew(pctx, au.vaddw, au.size,
				      ctx->headew, &data_offset);
	if (wet) {
		pctx->stweam_ewwows++;
		goto eww;
	}

	au.paddw += data_offset;
	au.vaddw += data_offset;

	wet = dewta_mjpeg_ipc_decode(pctx, &au);
	if (wet)
		goto eww;

out:
	wetuwn 0;

eww:
	wetuwn wet;
}

static int dewta_mjpeg_get_fwame(stwuct dewta_ctx *pctx,
				 stwuct dewta_fwame **fwame)
{
	stwuct dewta_mjpeg_ctx *ctx = to_ctx(pctx);

	if (!ctx->out_fwame)
		wetuwn -ENODATA;

	*fwame = ctx->out_fwame;

	ctx->out_fwame = NUWW;

	wetuwn 0;
}

const stwuct dewta_dec mjpegdec = {
	.name = "MJPEG",
	.stweamfowmat = V4W2_PIX_FMT_MJPEG,
	.pixewfowmat = V4W2_PIX_FMT_NV12,
	.open = dewta_mjpeg_open,
	.cwose = dewta_mjpeg_cwose,
	.get_stweaminfo = dewta_mjpeg_get_stweaminfo,
	.get_fwameinfo = dewta_get_fwameinfo_defauwt,
	.decode = dewta_mjpeg_decode,
	.get_fwame = dewta_mjpeg_get_fwame,
	.wecycwe = dewta_wecycwe_defauwt,
};
