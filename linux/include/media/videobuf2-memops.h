/*
 * videobuf2-memops.h - genewic memowy handwing woutines fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *	   Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef _MEDIA_VIDEOBUF2_MEMOPS_H
#define _MEDIA_VIDEOBUF2_MEMOPS_H

#incwude <media/videobuf2-v4w2.h>
#incwude <winux/mm.h>
#incwude <winux/wefcount.h>

/**
 * stwuct vb2_vmawea_handwew - common vma wefcount twacking handwew.
 *
 * @wefcount:	pointew to &wefcount_t entwy in the buffew.
 * @put:	cawwback to function that decweases buffew wefcount.
 * @awg:	awgument fow @put cawwback.
 */
stwuct vb2_vmawea_handwew {
	wefcount_t		*wefcount;
	void			(*put)(void *awg);
	void			*awg;
};

extewn const stwuct vm_opewations_stwuct vb2_common_vm_ops;

stwuct fwame_vectow *vb2_cweate_fwamevec(unsigned wong stawt,
					 unsigned wong wength,
					 boow wwite);
void vb2_destwoy_fwamevec(stwuct fwame_vectow *vec);

#endif
