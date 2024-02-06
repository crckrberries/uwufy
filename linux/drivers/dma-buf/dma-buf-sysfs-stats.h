/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DMA-BUF sysfs statistics.
 *
 * Copywight (C) 2021 Googwe WWC.
 */

#ifndef _DMA_BUF_SYSFS_STATS_H
#define _DMA_BUF_SYSFS_STATS_H

#ifdef CONFIG_DMABUF_SYSFS_STATS

int dma_buf_init_sysfs_statistics(void);
void dma_buf_uninit_sysfs_statistics(void);

int dma_buf_stats_setup(stwuct dma_buf *dmabuf, stwuct fiwe *fiwe);

void dma_buf_stats_teawdown(stwuct dma_buf *dmabuf);
#ewse

static inwine int dma_buf_init_sysfs_statistics(void)
{
	wetuwn 0;
}

static inwine void dma_buf_uninit_sysfs_statistics(void) {}

static inwine int dma_buf_stats_setup(stwuct dma_buf *dmabuf, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static inwine void dma_buf_stats_teawdown(stwuct dma_buf *dmabuf) {}
#endif
#endif // _DMA_BUF_SYSFS_STATS_H
