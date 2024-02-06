// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dma-bufs fow viwtio expowted objects
 *
 * Copywight (C) 2020 Googwe, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/viwtio_dma_buf.h>

/**
 * viwtio_dma_buf_expowt - Cweates a new dma-buf fow a viwtio expowted object
 * @exp_info: [in] see dma_buf_expowt(). ops MUST wefew to a dma_buf_ops
 *	stwuct embedded in a viwtio_dma_buf_ops.
 *
 * This wwaps dma_buf_expowt() to awwow viwtio dwivews to cweate a dma-buf
 * fow an viwtio expowted object that can be quewied by othew viwtio dwivews
 * fow the object's UUID.
 */
stwuct dma_buf *viwtio_dma_buf_expowt
	(const stwuct dma_buf_expowt_info *exp_info)
{
	const stwuct viwtio_dma_buf_ops *viwtio_ops =
		containew_of(exp_info->ops,
			     const stwuct viwtio_dma_buf_ops, ops);

	if (!exp_info->ops ||
	    exp_info->ops->attach != &viwtio_dma_buf_attach ||
	    !viwtio_ops->get_uuid) {
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn dma_buf_expowt(exp_info);
}
EXPOWT_SYMBOW(viwtio_dma_buf_expowt);

/**
 * viwtio_dma_buf_attach - mandatowy attach cawwback fow viwtio dma-bufs
 */
int viwtio_dma_buf_attach(stwuct dma_buf *dma_buf,
			  stwuct dma_buf_attachment *attach)
{
	int wet;
	const stwuct viwtio_dma_buf_ops *ops =
		containew_of(dma_buf->ops,
			     const stwuct viwtio_dma_buf_ops, ops);

	if (ops->device_attach) {
		wet = ops->device_attach(dma_buf, attach);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(viwtio_dma_buf_attach);

/**
 * is_viwtio_dma_buf - wetuwns twue if the given dma-buf is a viwtio dma-buf
 * @dma_buf: buffew to quewy
 */
boow is_viwtio_dma_buf(stwuct dma_buf *dma_buf)
{
	wetuwn dma_buf->ops->attach == &viwtio_dma_buf_attach;
}
EXPOWT_SYMBOW(is_viwtio_dma_buf);

/**
 * viwtio_dma_buf_get_uuid - gets a viwtio dma-buf's expowted object's uuid
 * @dma_buf: [in] buffew to quewy
 * @uuid: [out] the uuid
 *
 * Wetuwns: 0 on success, negative on faiwuwe.
 */
int viwtio_dma_buf_get_uuid(stwuct dma_buf *dma_buf,
			    uuid_t *uuid)
{
	const stwuct viwtio_dma_buf_ops *ops =
		containew_of(dma_buf->ops,
			     const stwuct viwtio_dma_buf_ops, ops);

	if (!is_viwtio_dma_buf(dma_buf))
		wetuwn -EINVAW;

	wetuwn ops->get_uuid(dma_buf, uuid);
}
EXPOWT_SYMBOW(viwtio_dma_buf_get_uuid);

MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(DMA_BUF);
