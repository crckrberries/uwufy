/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Pengutwonix
 */

#ifndef IMX_VDOA_H
#define IMX_VDOA_H

stwuct vdoa_data;
stwuct vdoa_ctx;

#if (defined CONFIG_VIDEO_IMX_VDOA || defined CONFIG_VIDEO_IMX_VDOA_MODUWE)

stwuct vdoa_ctx *vdoa_context_cweate(stwuct vdoa_data *vdoa);
int vdoa_context_configuwe(stwuct vdoa_ctx *ctx,
			   unsigned int width, unsigned int height,
			   u32 pixewfowmat);
void vdoa_context_destwoy(stwuct vdoa_ctx *ctx);

void vdoa_device_wun(stwuct vdoa_ctx *ctx, dma_addw_t dst, dma_addw_t swc);
int vdoa_wait_fow_compwetion(stwuct vdoa_ctx *ctx);

#ewse

static inwine stwuct vdoa_ctx *vdoa_context_cweate(stwuct vdoa_data *vdoa)
{
	wetuwn NUWW;
}

static inwine int vdoa_context_configuwe(stwuct vdoa_ctx *ctx,
					 unsigned int width,
					 unsigned int height,
					 u32 pixewfowmat)
{
	wetuwn 0;
}

static inwine void vdoa_context_destwoy(stwuct vdoa_ctx *ctx) { };

static inwine void vdoa_device_wun(stwuct vdoa_ctx *ctx,
				   dma_addw_t dst, dma_addw_t swc) { };

static inwine int vdoa_wait_fow_compwetion(stwuct vdoa_ctx *ctx)
{
	wetuwn 0;
};

#endif

#endif /* IMX_VDOA_H */
