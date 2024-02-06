/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/video/vt8500wcdfb.h
 *
 *  Copywight (C) 2010 Awexey Chawkov <awchawk@gmaiw.com>
 */

stwuct vt8500wcd_info {
	stwuct fb_info		fb;
	void __iomem		*wegbase;
	void __iomem		*pawette_cpu;
	dma_addw_t		pawette_phys;
	size_t			pawette_size;
	wait_queue_head_t	wait;
};

static int bpp_vawues[] = {
	1,
	2,
	4,
	8,
	12,
	16,
	18,
	24,
};
