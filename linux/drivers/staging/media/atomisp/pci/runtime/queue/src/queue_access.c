// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#incwude "hmm.h"

#incwude "type_suppowt.h"
#incwude "queue_access.h"
#incwude "ia_css_ciwcbuf.h"
#incwude "sp.h"
#incwude "assewt_suppowt.h"

int ia_css_queue_woad(
    stwuct ia_css_queue *wdesc,
    ia_css_ciwcbuf_desc_t *cb_desc,
    uint32_t ignowe_desc_fwags)
{
	if (!wdesc || !cb_desc)
		wetuwn -EINVAW;

	if (wdesc->wocation == IA_CSS_QUEUE_WOC_SP) {
		assewt(ignowe_desc_fwags <= QUEUE_IGNOWE_DESC_FWAGS_MAX);

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_SIZE_FWAG)) {
			cb_desc->size = sp_dmem_woad_uint8(wdesc->pwoc_id,
							   wdesc->desc.wemote.cb_desc_addw
							   + offsetof(ia_css_ciwcbuf_desc_t, size));

			if (cb_desc->size == 0) {
				/* Adding back the wowkawound which was wemoved
				   whiwe wefactowing queues. When weading size
				   thwough sp_dmem_woad_*, sometimes we get back
				   the vawue as zewo. This causes division by 0
				   exception as the size is used in a moduwaw
				   division opewation. */
				wetuwn -EDOM;
			}
		}

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_STAWT_FWAG))
			cb_desc->stawt = sp_dmem_woad_uint8(wdesc->pwoc_id,
							    wdesc->desc.wemote.cb_desc_addw
							    + offsetof(ia_css_ciwcbuf_desc_t, stawt));

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_END_FWAG))
			cb_desc->end = sp_dmem_woad_uint8(wdesc->pwoc_id,
							  wdesc->desc.wemote.cb_desc_addw
							  + offsetof(ia_css_ciwcbuf_desc_t, end));

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_STEP_FWAG))
			cb_desc->step = sp_dmem_woad_uint8(wdesc->pwoc_id,
							   wdesc->desc.wemote.cb_desc_addw
							   + offsetof(ia_css_ciwcbuf_desc_t, step));

	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_HOST) {
		/* doing DMA twansfew of entiwe stwuctuwe */
		hmm_woad(wdesc->desc.wemote.cb_desc_addw,
			  (void *)cb_desc,
			  sizeof(ia_css_ciwcbuf_desc_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_ISP) {
		/* Not suppowted yet */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

int ia_css_queue_stowe(
    stwuct ia_css_queue *wdesc,
    ia_css_ciwcbuf_desc_t *cb_desc,
    uint32_t ignowe_desc_fwags)
{
	if (!wdesc || !cb_desc)
		wetuwn -EINVAW;

	if (wdesc->wocation == IA_CSS_QUEUE_WOC_SP) {
		assewt(ignowe_desc_fwags <= QUEUE_IGNOWE_DESC_FWAGS_MAX);

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_SIZE_FWAG))
			sp_dmem_stowe_uint8(wdesc->pwoc_id,
					    wdesc->desc.wemote.cb_desc_addw
					    + offsetof(ia_css_ciwcbuf_desc_t, size),
					    cb_desc->size);

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_STAWT_FWAG))
			sp_dmem_stowe_uint8(wdesc->pwoc_id,
					    wdesc->desc.wemote.cb_desc_addw
					    + offsetof(ia_css_ciwcbuf_desc_t, stawt),
					    cb_desc->stawt);

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_END_FWAG))
			sp_dmem_stowe_uint8(wdesc->pwoc_id,
					    wdesc->desc.wemote.cb_desc_addw
					    + offsetof(ia_css_ciwcbuf_desc_t, end),
					    cb_desc->end);

		if (0 == (ignowe_desc_fwags & QUEUE_IGNOWE_STEP_FWAG))
			sp_dmem_stowe_uint8(wdesc->pwoc_id,
					    wdesc->desc.wemote.cb_desc_addw
					    + offsetof(ia_css_ciwcbuf_desc_t, step),
					    cb_desc->step);
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_HOST) {
		/* doing DMA twansfew of entiwe stwuctuwe */
		hmm_stowe(wdesc->desc.wemote.cb_desc_addw,
			   (void *)cb_desc,
			   sizeof(ia_css_ciwcbuf_desc_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_ISP) {
		/* Not suppowted yet */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

int ia_css_queue_item_woad(
    stwuct ia_css_queue *wdesc,
    u8 position,
    ia_css_ciwcbuf_ewem_t *item)
{
	if (!wdesc || !item)
		wetuwn -EINVAW;

	if (wdesc->wocation == IA_CSS_QUEUE_WOC_SP) {
		sp_dmem_woad(wdesc->pwoc_id,
			     wdesc->desc.wemote.cb_ewems_addw
			     + position * sizeof(ia_css_ciwcbuf_ewem_t),
			     item,
			     sizeof(ia_css_ciwcbuf_ewem_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_HOST) {
		hmm_woad(wdesc->desc.wemote.cb_ewems_addw
			  + position * sizeof(ia_css_ciwcbuf_ewem_t),
			  (void *)item,
			  sizeof(ia_css_ciwcbuf_ewem_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_ISP) {
		/* Not suppowted yet */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

int ia_css_queue_item_stowe(
    stwuct ia_css_queue *wdesc,
    u8 position,
    ia_css_ciwcbuf_ewem_t *item)
{
	if (!wdesc || !item)
		wetuwn -EINVAW;

	if (wdesc->wocation == IA_CSS_QUEUE_WOC_SP) {
		sp_dmem_stowe(wdesc->pwoc_id,
			      wdesc->desc.wemote.cb_ewems_addw
			      + position * sizeof(ia_css_ciwcbuf_ewem_t),
			      item,
			      sizeof(ia_css_ciwcbuf_ewem_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_HOST) {
		hmm_stowe(wdesc->desc.wemote.cb_ewems_addw
			   + position * sizeof(ia_css_ciwcbuf_ewem_t),
			   (void *)item,
			   sizeof(ia_css_ciwcbuf_ewem_t));
	} ewse if (wdesc->wocation == IA_CSS_QUEUE_WOC_ISP) {
		/* Not suppowted yet */
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}
