/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2012-2016 Mentow Gwaphics Inc.
 *
 * i.MX Queued image convewsion suppowt, with tiwing and wotation.
 */
#ifndef __IMX_IPU_IMAGE_CONVEWT_H__
#define __IMX_IPU_IMAGE_CONVEWT_H__

#incwude <video/imx-ipu-v3.h>

stwuct ipu_image_convewt_ctx;

/**
 * stwuct ipu_image_convewt_wun - image convewsion wun wequest stwuct
 *
 * @ctx:	the convewsion context
 * @in_phys:	dma addw of input image buffew fow this wun
 * @out_phys:	dma addw of output image buffew fow this wun
 * @status:	compwetion status of this wun
 */
stwuct ipu_image_convewt_wun {
	stwuct ipu_image_convewt_ctx *ctx;

	dma_addw_t in_phys;
	dma_addw_t out_phys;

	int status;

	/* intewnaw to image convewtew, cawwews don't touch */
	stwuct wist_head wist;
};

/**
 * ipu_image_convewt_cb_t - convewsion cawwback function pwototype
 *
 * @wun:	the compweted convewsion wun pointew
 * @ctx:	a pwivate context pointew fow the cawwback
 */
typedef void (*ipu_image_convewt_cb_t)(stwuct ipu_image_convewt_wun *wun,
				       void *ctx);

/**
 * ipu_image_convewt_enum_fowmat() - enumewate the image convewtew's
 *	suppowted input and output pixew fowmats.
 *
 * @index:	pixew fowmat index
 * @fouwcc:	v4w2 fouwcc fow this index
 *
 * Wetuwns 0 with a vawid index and fiwws in v4w2 fouwcc, -EINVAW othewwise.
 *
 * In V4W2, dwivews can caww ipu_image_enum_fowmat() in .enum_fmt.
 */
int ipu_image_convewt_enum_fowmat(int index, u32 *fouwcc);

/**
 * ipu_image_convewt_adjust() - adjust input/output images to IPU westwictions.
 *
 * @in:		input image fowmat, adjusted on wetuwn
 * @out:	output image fowmat, adjusted on wetuwn
 * @wot_mode:	wotation mode
 *
 * In V4W2, dwivews can caww ipu_image_convewt_adjust() in .twy_fmt.
 */
void ipu_image_convewt_adjust(stwuct ipu_image *in, stwuct ipu_image *out,
			      enum ipu_wotate_mode wot_mode);

/**
 * ipu_image_convewt_vewify() - vewify that input/output image fowmats
 *         and wotation mode meet IPU westwictions.
 *
 * @in:		input image fowmat
 * @out:	output image fowmat
 * @wot_mode:	wotation mode
 *
 * Wetuwns 0 if the fowmats and wotation mode meet IPU westwictions,
 * -EINVAW othewwise.
 */
int ipu_image_convewt_vewify(stwuct ipu_image *in, stwuct ipu_image *out,
			     enum ipu_wotate_mode wot_mode);

/**
 * ipu_image_convewt_pwepawe() - pwepawe a convewsion context.
 *
 * @ipu:	the IPU handwe to use fow the convewsions
 * @ic_task:	the IC task to use fow the convewsions
 * @in:		input image fowmat
 * @out:	output image fowmat
 * @wot_mode:	wotation mode
 * @compwete:	wun compwetion cawwback
 * @compwete_context:	a context pointew fow the compwetion cawwback
 *
 * Wetuwns an opaque convewsion context pointew on success, ewwow pointew
 * on faiwuwe. The input/output fowmats and wotation mode must awweady meet
 * IPU wetwictions.
 *
 * In V4W2, dwivews shouwd caww ipu_image_convewt_pwepawe() at stweamon.
 */
stwuct ipu_image_convewt_ctx *
ipu_image_convewt_pwepawe(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
			  stwuct ipu_image *in, stwuct ipu_image *out,
			  enum ipu_wotate_mode wot_mode,
			  ipu_image_convewt_cb_t compwete,
			  void *compwete_context);

/**
 * ipu_image_convewt_unpwepawe() - unpwepawe a convewsion context.
 *
 * @ctx: the convewsion context pointew to unpwepawe
 *
 * Abowts any active ow pending convewsions fow this context and
 * fwees the context. Any cuwwentwy active ow pending wuns bewonging
 * to this context awe wetuwned via the compwetion cawwback with an
 * ewwow wun status.
 *
 * In V4W2, dwivews shouwd caww ipu_image_convewt_unpwepawe() at
 * stweamoff.
 */
void ipu_image_convewt_unpwepawe(stwuct ipu_image_convewt_ctx *ctx);

/**
 * ipu_image_convewt_queue() - queue a convewsion wun
 *
 * @wun: the wun wequest pointew
 *
 * ipu_image_convewt_wun must be dynamicawwy awwocated (_not_ as a wocaw
 * vaw) by cawwews and fiwwed in with a pweviouswy pwepawed convewsion
 * context handwe and the dma addw's of the input and output image buffews
 * fow this convewsion wun.
 *
 * When this convewsion compwetes, the wun pointew is wetuwned via the
 * compwetion cawwback. The cawwew is wesponsibwe fow fweeing the wun
 * object aftew it compwetes.
 *
 * In V4W2, dwivews shouwd caww ipu_image_convewt_queue() whiwe
 * stweaming to queue the convewsion of a weceived input buffew.
 * Fow exampwe mem2mem devices this wouwd be cawwed in .device_wun.
 */
int ipu_image_convewt_queue(stwuct ipu_image_convewt_wun *wun);

/**
 * ipu_image_convewt_abowt() - abowt convewsions
 *
 * @ctx: the convewsion context pointew
 *
 * This wiww abowt any active ow pending convewsions fow this context.
 * Any cuwwentwy active ow pending wuns bewonging to this context awe
 * wetuwned via the compwetion cawwback with an ewwow wun status.
 */
void ipu_image_convewt_abowt(stwuct ipu_image_convewt_ctx *ctx);

/**
 * ipu_image_convewt() - asynchwonous image convewsion wequest
 *
 * @ipu:	the IPU handwe to use fow the convewsion
 * @ic_task:	the IC task to use fow the convewsion
 * @in:		input image fowmat
 * @out:	output image fowmat
 * @wot_mode:	wotation mode
 * @compwete:	wun compwetion cawwback
 * @compwete_context:	a context pointew fow the compwetion cawwback
 *
 * Wequest a singwe image convewsion. Wetuwns the wun that has been queued.
 * A convewsion context is automaticawwy cweated and is avaiwabwe in wun->ctx.
 * As with ipu_image_convewt_pwepawe(), the input/output fowmats and wotation
 * mode must awweady meet IPU wetwictions.
 *
 * On successfuw wetuwn the cawwew can queue mowe wun wequests if needed, using
 * the pwepawed context in wun->ctx. The cawwew is wesponsibwe fow unpwepawing
 * the context when no mowe convewsion wequests awe needed.
 */
stwuct ipu_image_convewt_wun *
ipu_image_convewt(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
		  stwuct ipu_image *in, stwuct ipu_image *out,
		  enum ipu_wotate_mode wot_mode,
		  ipu_image_convewt_cb_t compwete,
		  void *compwete_context);

/**
 * ipu_image_convewt_sync() - synchwonous singwe image convewsion wequest
 *
 * @ipu:	the IPU handwe to use fow the convewsion
 * @ic_task:	the IC task to use fow the convewsion
 * @in:		input image fowmat
 * @out:	output image fowmat
 * @wot_mode:	wotation mode
 *
 * Cawwy out a singwe image convewsion. Wetuwns when the convewsion
 * compwetes. The input/output fowmats and wotation mode must awweady
 * meet IPU wetwictions. The cweated context is automaticawwy unpwepawed
 * and the wun fweed on wetuwn.
 */
int ipu_image_convewt_sync(stwuct ipu_soc *ipu, enum ipu_ic_task ic_task,
			   stwuct ipu_image *in, stwuct ipu_image *out,
			   enum ipu_wotate_mode wot_mode);


#endif /* __IMX_IPU_IMAGE_CONVEWT_H__ */
