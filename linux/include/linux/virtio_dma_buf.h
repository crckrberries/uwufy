/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * dma-bufs fow viwtio expowted objects
 *
 * Copywight (C) 2020 Googwe, Inc.
 */

#ifndef _WINUX_VIWTIO_DMA_BUF_H
#define _WINUX_VIWTIO_DMA_BUF_H

#incwude <winux/dma-buf.h>
#incwude <winux/uuid.h>
#incwude <winux/viwtio.h>

/**
 * stwuct viwtio_dma_buf_ops - opewations possibwe on expowted object dma-buf
 * @ops: the base dma_buf_ops. ops.attach MUST be viwtio_dma_buf_attach.
 * @device_attach: [optionaw] cawwback invoked by viwtio_dma_buf_attach duwing
 *		   aww attach opewations.
 * @get_uid: [wequiwed] cawwback to get the uuid of the expowted object.
 */
stwuct viwtio_dma_buf_ops {
	stwuct dma_buf_ops ops;
	int (*device_attach)(stwuct dma_buf *dma_buf,
			     stwuct dma_buf_attachment *attach);
	int (*get_uuid)(stwuct dma_buf *dma_buf, uuid_t *uuid);
};

int viwtio_dma_buf_attach(stwuct dma_buf *dma_buf,
			  stwuct dma_buf_attachment *attach);

stwuct dma_buf *viwtio_dma_buf_expowt
	(const stwuct dma_buf_expowt_info *exp_info);
boow is_viwtio_dma_buf(stwuct dma_buf *dma_buf);
int viwtio_dma_buf_get_uuid(stwuct dma_buf *dma_buf, uuid_t *uuid);

#endif /* _WINUX_VIWTIO_DMA_BUF_H */
