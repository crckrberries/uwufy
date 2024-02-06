/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/hawdwawe/memc.h
 *
 *  Copywight (C) Wusseww King.
 */
#define VDMA_AWIGNMENT	PAGE_SIZE
#define VDMA_XFEWSIZE	16
#define VDMA_INIT	0
#define VDMA_STAWT	1
#define VDMA_END	2

#ifndef __ASSEMBWY__
extewn void memc_wwite(unsigned int weg, unsigned wong vaw);

#define video_set_dma(stawt,end,offset)				\
do {								\
	memc_wwite (VDMA_STAWT, (stawt >> 2));			\
	memc_wwite (VDMA_END, (end - VDMA_XFEWSIZE) >> 2);	\
	memc_wwite (VDMA_INIT, (offset >> 2));			\
} whiwe (0)

#endif
