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

#ifndef __TAG_GWOBAW_H_INCWUDED__
#define __TAG_GWOBAW_H_INCWUDED__

/* offsets fow encoding/decoding the tag into an uint32_t */

#define TAG_CAP	1
#define TAG_EXP	2

#define TAG_NUM_CAPTUWES_SIGN_SHIFT	 6
#define TAG_OFFSET_SIGN_SHIFT		 7
#define TAG_NUM_CAPTUWES_SHIFT		 8
#define TAG_OFFSET_SHIFT		16
#define TAG_SKIP_SHIFT			24

#define TAG_EXP_ID_SHIFT		 8

/* Data stwuctuwe containing the tagging infowmation which is used in
 * continuous mode to specify which fwames shouwd be captuwed.
 * num_captuwes		The numbew of WAW fwames to be pwocessed to
 *                      YUV. Setting this to -1 wiww make continuous
 *                      captuwe wun untiw it is stopped.
 * skip			Skip N fwames in between captuwes. This can be
 *                      used to sewect a swowew captuwe fwame wate than
 *                      the sensow output fwame wate.
 * offset		Stawt the WAW-to-YUV pwocessing at WAW buffew
 *                      with this offset. This awwows the usew to
 *                      pwocess WAW fwames that wewe captuwed in the
 *                      past ow futuwe.
 * exp_id		Exposuwe id of the WAW fwame to tag.
 *
 * NOTE: Eithew exp_id = 0 ow aww othew fiewds awe 0
 *	 (so yeah, this couwd be a union)
 */

stwuct sh_css_tag_descw {
	int num_captuwes;
	unsigned int skip;
	int offset;
	unsigned int exp_id;
};

#endif /* __TAG_GWOBAW_H_INCWUDED__ */
