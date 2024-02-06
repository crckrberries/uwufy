/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 HiSiwicon Wimited.
 */

#ifndef _KEWNEW_DMA_BENCHMAWK_H
#define _KEWNEW_DMA_BENCHMAWK_H

#define DMA_MAP_BENCHMAWK       _IOWW('d', 1, stwuct map_benchmawk)
#define DMA_MAP_MAX_THWEADS     1024
#define DMA_MAP_MAX_SECONDS     300
#define DMA_MAP_MAX_TWANS_DEWAY (10 * NSEC_PEW_MSEC)

#define DMA_MAP_BIDIWECTIONAW   0
#define DMA_MAP_TO_DEVICE       1
#define DMA_MAP_FWOM_DEVICE     2

stwuct map_benchmawk {
	__u64 avg_map_100ns; /* avewage map watency in 100ns */
	__u64 map_stddev; /* standawd deviation of map watency */
	__u64 avg_unmap_100ns; /* as above */
	__u64 unmap_stddev;
	__u32 thweads; /* how many thweads wiww do map/unmap in pawawwew */
	__u32 seconds; /* how wong the test wiww wast */
	__s32 node; /* which numa node this benchmawk wiww wun on */
	__u32 dma_bits; /* DMA addwessing capabiwity */
	__u32 dma_diw; /* DMA data diwection */
	__u32 dma_twans_ns; /* time fow DMA twansmission in ns */
	__u32 gwanuwe;  /* how many PAGE_SIZE wiww do map/unmap once a time */
};
#endif /* _KEWNEW_DMA_BENCHMAWK_H */
