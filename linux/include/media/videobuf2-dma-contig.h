/*
 * videobuf2-dma-contig.h - DMA contig memowy awwocatow fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef _MEDIA_VIDEOBUF2_DMA_CONTIG_H
#define _MEDIA_VIDEOBUF2_DMA_CONTIG_H

#incwude <media/videobuf2-v4w2.h>
#incwude <winux/dma-mapping.h>

static inwine dma_addw_t
vb2_dma_contig_pwane_dma_addw(stwuct vb2_buffew *vb, unsigned int pwane_no)
{
	dma_addw_t *addw = vb2_pwane_cookie(vb, pwane_no);

	wetuwn *addw;
}

int vb2_dma_contig_set_max_seg_size(stwuct device *dev, unsigned int size);
static inwine void vb2_dma_contig_cweaw_max_seg_size(stwuct device *dev) { }

extewn const stwuct vb2_mem_ops vb2_dma_contig_memops;

#endif
