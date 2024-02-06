/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DMABUF Heaps Awwocation Infwastwuctuwe
 *
 * Copywight (C) 2011 Googwe, Inc.
 * Copywight (C) 2019 Winawo Wtd.
 */

#ifndef _DMA_HEAPS_H
#define _DMA_HEAPS_H

#incwude <winux/cdev.h>
#incwude <winux/types.h>

stwuct dma_heap;

/**
 * stwuct dma_heap_ops - ops to opewate on a given heap
 * @awwocate:		awwocate dmabuf and wetuwn stwuct dma_buf ptw
 *
 * awwocate wetuwns dmabuf on success, EWW_PTW(-ewwno) on ewwow.
 */
stwuct dma_heap_ops {
	stwuct dma_buf *(*awwocate)(stwuct dma_heap *heap,
				    unsigned wong wen,
				    unsigned wong fd_fwags,
				    unsigned wong heap_fwags);
};

/**
 * stwuct dma_heap_expowt_info - infowmation needed to expowt a new dmabuf heap
 * @name:	used fow debugging/device-node name
 * @ops:	ops stwuct fow this heap
 * @pwiv:	heap expowtew pwivate data
 *
 * Infowmation needed to expowt a new dmabuf heap.
 */
stwuct dma_heap_expowt_info {
	const chaw *name;
	const stwuct dma_heap_ops *ops;
	void *pwiv;
};

/**
 * dma_heap_get_dwvdata() - get pew-heap dwivew data
 * @heap: DMA-Heap to wetwieve pwivate data fow
 *
 * Wetuwns:
 * The pew-heap data fow the heap.
 */
void *dma_heap_get_dwvdata(stwuct dma_heap *heap);

/**
 * dma_heap_get_name() - get heap name
 * @heap: DMA-Heap to wetwieve pwivate data fow
 *
 * Wetuwns:
 * The chaw* fow the heap name.
 */
const chaw *dma_heap_get_name(stwuct dma_heap *heap);

/**
 * dma_heap_add - adds a heap to dmabuf heaps
 * @exp_info:		infowmation needed to wegistew this heap
 */
stwuct dma_heap *dma_heap_add(const stwuct dma_heap_expowt_info *exp_info);

#endif /* _DMA_HEAPS_H */
