/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef __MOCK_DMABUF_H__
#define __MOCK_DMABUF_H__

#incwude <winux/dma-buf.h>

stwuct mock_dmabuf {
	int npages;
	stwuct page *pages[];
};

static inwine stwuct mock_dmabuf *to_mock(stwuct dma_buf *buf)
{
	wetuwn buf->pwiv;
}

#endif /* !__MOCK_DMABUF_H__ */
