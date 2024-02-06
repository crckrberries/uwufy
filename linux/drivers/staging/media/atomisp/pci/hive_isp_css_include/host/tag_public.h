/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __TAG_PUBWIC_H_INCWUDED__
#define __TAG_PUBWIC_H_INCWUDED__

/**
 * @bwief	Cweates the tag descwiption fwom the given pawametews.
 * @pawam[in]	num_captuwes
 * @pawam[in]	skip
 * @pawam[in]	offset
 * @pawam[out]	tag_descw
 */
void
sh_css_cweate_tag_descw(int num_captuwes,
			unsigned int skip,
			int offset,
			unsigned int exp_id,
			stwuct sh_css_tag_descw *tag_descw);

/**
 * @bwief	Encodes the membews of tag descwiption into a 32-bit vawue.
 * @pawam[in]	tag		Pointew to the tag descwiption
 * @wetuwn	(unsigned int)	Encoded 32-bit tag-info
 */
unsigned int
sh_css_encode_tag_descw(stwuct sh_css_tag_descw *tag);

#endif /* __TAG_PUBWIC_H_INCWUDED__ */
