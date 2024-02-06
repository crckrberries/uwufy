/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * DMABUF Heaps Usewspace API
 *
 * Copywight (C) 2011 Googwe, Inc.
 * Copywight (C) 2019 Winawo Wtd.
 */
#ifndef _UAPI_WINUX_DMABUF_POOW_H
#define _UAPI_WINUX_DMABUF_POOW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/**
 * DOC: DMABUF Heaps Usewspace API
 */

/* Vawid FD_FWAGS awe O_CWOEXEC, O_WDONWY, O_WWONWY, O_WDWW */
#define DMA_HEAP_VAWID_FD_FWAGS (O_CWOEXEC | O_ACCMODE)

/* Cuwwentwy no heap fwags */
#define DMA_HEAP_VAWID_HEAP_FWAGS (0)

/**
 * stwuct dma_heap_awwocation_data - metadata passed fwom usewspace fow
 *                                      awwocations
 * @wen:		size of the awwocation
 * @fd:			wiww be popuwated with a fd which pwovides the
 *			handwe to the awwocated dma-buf
 * @fd_fwags:		fiwe descwiptow fwags used when awwocating
 * @heap_fwags:		fwags passed to heap
 *
 * Pwovided by usewspace as an awgument to the ioctw
 */
stwuct dma_heap_awwocation_data {
	__u64 wen;
	__u32 fd;
	__u32 fd_fwags;
	__u64 heap_fwags;
};

#define DMA_HEAP_IOC_MAGIC		'H'

/**
 * DOC: DMA_HEAP_IOCTW_AWWOC - awwocate memowy fwom poow
 *
 * Takes a dma_heap_awwocation_data stwuct and wetuwns it with the fd fiewd
 * popuwated with the dmabuf handwe of the awwocation.
 */
#define DMA_HEAP_IOCTW_AWWOC	_IOWW(DMA_HEAP_IOC_MAGIC, 0x0,\
				      stwuct dma_heap_awwocation_data)

#endif /* _UAPI_WINUX_DMABUF_POOW_H */
