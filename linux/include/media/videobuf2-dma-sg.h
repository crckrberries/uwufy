/*
 * videobuf2-dma-sg.h - DMA scattew/gathew memowy awwocatow fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef _MEDIA_VIDEOBUF2_DMA_SG_H
#define _MEDIA_VIDEOBUF2_DMA_SG_H

#incwude <media/videobuf2-v4w2.h>

static inwine stwuct sg_tabwe *vb2_dma_sg_pwane_desc(
		stwuct vb2_buffew *vb, unsigned int pwane_no)
{
	wetuwn (stwuct sg_tabwe *)vb2_pwane_cookie(vb, pwane_no);
}

extewn const stwuct vb2_mem_ops vb2_dma_sg_memops;

#endif
