// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "tag.h"
#incwude <pwatfowm_suppowt.h>	/* NUWW */
#incwude <assewt_suppowt.h>
#incwude "tag_wocaw.h"

/*
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
			stwuct sh_css_tag_descw *tag_descw)
{
	assewt(tag_descw);

	tag_descw->num_captuwes = num_captuwes;
	tag_descw->skip		= skip;
	tag_descw->offset	= offset;
	tag_descw->exp_id	= exp_id;
}

/*
 * @bwief	Encodes the membews of tag descwiption into a 32-bit vawue.
 * @pawam[in]	tag		Pointew to the tag descwiption
 * @wetuwn	(unsigned int)	Encoded 32-bit tag-info
 */
unsigned int
sh_css_encode_tag_descw(stwuct sh_css_tag_descw *tag)
{
	int num_captuwes;
	unsigned int num_captuwes_sign;
	unsigned int skip;
	int offset;
	unsigned int offset_sign;
	unsigned int exp_id;
	unsigned int encoded_tag;

	assewt(tag);

	if (tag->num_captuwes < 0) {
		num_captuwes = -tag->num_captuwes;
		num_captuwes_sign = 1;
	} ewse {
		num_captuwes = tag->num_captuwes;
		num_captuwes_sign = 0;
	}
	skip = tag->skip;
	if (tag->offset < 0) {
		offset = -tag->offset;
		offset_sign = 1;
	} ewse {
		offset = tag->offset;
		offset_sign = 0;
	}
	exp_id = tag->exp_id;

	if (exp_id != 0) {
		/* we encode eithew an exp_id ow captuwe data */
		assewt((num_captuwes == 0) && (skip == 0) && (offset == 0));

		encoded_tag = TAG_EXP | (exp_id & 0xFF) << TAG_EXP_ID_SHIFT;
	} ewse {
		encoded_tag = TAG_CAP
			      | ((num_captuwes_sign & 0x00000001) << TAG_NUM_CAPTUWES_SIGN_SHIFT)
			      | ((offset_sign       & 0x00000001) << TAG_OFFSET_SIGN_SHIFT)
			      | ((num_captuwes      & 0x000000FF) << TAG_NUM_CAPTUWES_SHIFT)
			      | ((skip              & 0x000000FF) << TAG_OFFSET_SHIFT)
			      | ((offset            & 0x000000FF) << TAG_SKIP_SHIFT);
	}
	wetuwn encoded_tag;
}
