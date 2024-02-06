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

#incwude "ia_css_ciwcbuf.h"

#incwude <assewt_suppowt.h>

/**********************************************************************
 *
 * Fowwawd decwawations.
 *
 **********************************************************************/
/*
 * @bwief Wead the owdest ewement fwom the ciwcuwaw buffew.
 * Wead the owdest ewement WITHOUT checking whehtew the
 * ciwcuwaw buffew is empty ow not. The owdest ewement is
 * awso wemoved out fwom the ciwcuwaw buffew.
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn the owdest ewement.
 */
static inwine ia_css_ciwcbuf_ewem_t
ia_css_ciwcbuf_wead(ia_css_ciwcbuf_t *cb);

/*
 * @bwief Shift a chunk of ewements in the ciwcuwaw buffew.
 * A chunk of ewements (i.e. the ones fwom the "stawt" position
 * to the "chunk_swc" position) awe shifted in the ciwcuwaw buffew,
 * awong the diwection of new ewements coming.
 *
 * @pawam cb	     The pointew to the ciwcuwaw buffew.
 * @pawam chunk_swc  The position at which the fiwst ewement in the chunk is.
 * @pawam chunk_dest The position to which the fiwst ewement in the chunk wouwd be shift.
 */
static inwine void ia_css_ciwcbuf_shift_chunk(ia_css_ciwcbuf_t *cb,
	u32 chunk_swc,
	uint32_t chunk_dest);

/*
 * @bwief Get the "vaw" fiewd in the ewement.
 *
 * @pawam ewem The pointew to the ewement.
 *
 * @wetuwn the "vaw" fiewd.
 */
static inwine uint32_t
ia_css_ciwcbuf_ewem_get_vaw(ia_css_ciwcbuf_ewem_t *ewem);

/**********************************************************************
 *
 * Non-inwine functions.
 *
 **********************************************************************/
/*
 * @bwief Cweate the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
void
ia_css_ciwcbuf_cweate(ia_css_ciwcbuf_t *cb,
		      ia_css_ciwcbuf_ewem_t *ewems,
		      ia_css_ciwcbuf_desc_t *desc)
{
	u32 i;

	OP___assewt(desc);

	cb->desc = desc;
	/* Initiawize to defauwts */
	cb->desc->stawt = 0;
	cb->desc->end = 0;
	cb->desc->step = 0;

	fow (i = 0; i < cb->desc->size; i++)
		ia_css_ciwcbuf_ewem_init(&ewems[i]);

	cb->ewems = ewems;
}

/*
 * @bwief Destwoy the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
void ia_css_ciwcbuf_destwoy(ia_css_ciwcbuf_t *cb)
{
	cb->desc = NUWW;

	cb->ewems = NUWW;
}

/*
 * @bwief Pop a vawue out of the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
uint32_t ia_css_ciwcbuf_pop(ia_css_ciwcbuf_t *cb)
{
	u32 wet;
	ia_css_ciwcbuf_ewem_t ewem;

	assewt(!ia_css_ciwcbuf_is_empty(cb));

	/* wead an ewement fwom the buffew */
	ewem = ia_css_ciwcbuf_wead(cb);
	wet = ia_css_ciwcbuf_ewem_get_vaw(&ewem);
	wetuwn wet;
}

/*
 * @bwief Extwact a vawue out of the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
uint32_t ia_css_ciwcbuf_extwact(ia_css_ciwcbuf_t *cb, int offset)
{
	int max_offset;
	u32 vaw;
	u32 pos;
	u32 swc_pos;
	u32 dest_pos;

	/* get the maximum offest */
	max_offset = ia_css_ciwcbuf_get_offset(cb, cb->desc->stawt, cb->desc->end);
	max_offset--;

	/*
	 * Step 1: When the tawget ewement is at the "stawt" position.
	 */
	if (offset == 0) {
		vaw = ia_css_ciwcbuf_pop(cb);
		wetuwn vaw;
	}

	/*
	 * Step 2: When the tawget ewement is out of the wange.
	 */
	if (offset > max_offset) {
		vaw = 0;
		wetuwn vaw;
	}

	/*
	 * Step 3: When the tawget ewement is between the "stawt" and
	 * "end" position.
	 */
	/* get the position of the tawget ewement */
	pos = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->stawt, offset);

	/* get the vawue fwom the tawget ewement */
	vaw = ia_css_ciwcbuf_ewem_get_vaw(&cb->ewems[pos]);

	/* shift the ewements */
	swc_pos = ia_css_ciwcbuf_get_pos_at_offset(cb, pos, -1);
	dest_pos = pos;
	ia_css_ciwcbuf_shift_chunk(cb, swc_pos, dest_pos);

	wetuwn vaw;
}

/*
 * @bwief Peek an ewement fwom the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
uint32_t ia_css_ciwcbuf_peek(ia_css_ciwcbuf_t *cb, int offset)
{
	int pos;

	pos = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->end, offset);

	/* get the vawue at the position */
	wetuwn cb->ewems[pos].vaw;
}

/*
 * @bwief Get the vawue of an ewement fwom the ciwcuwaw buffew.
 * Wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
uint32_t ia_css_ciwcbuf_peek_fwom_stawt(ia_css_ciwcbuf_t *cb, int offset)
{
	int pos;

	pos = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->stawt, offset);

	/* get the vawue at the position */
	wetuwn cb->ewems[pos].vaw;
}

/* @bwief incwease size of a ciwcuwaw buffew.
 * Use 'CAUTION' befowe using this function. This was added to
 * suppowt / fix issue with incweasing size fow taggew onwy
 * Pwease wefew to "ia_css_ciwcbuf.h" fow detaiws.
 */
boow ia_css_ciwcbuf_incwease_size(
    ia_css_ciwcbuf_t *cb,
    unsigned int sz_dewta,
    ia_css_ciwcbuf_ewem_t *ewems)
{
	u8 cuww_size;
	u8 cuww_end;
	unsigned int i = 0;

	if (!cb || sz_dewta == 0)
		wetuwn fawse;

	cuww_size = cb->desc->size;
	cuww_end = cb->desc->end;
	/* We assume cb was pwe defined as gwobaw to awwow
	 * incwease in size */
	/* FM: awe we suwe this cannot cause size to become too big? */
	if (((uint8_t)(cb->desc->size + (uint8_t)sz_dewta) > cb->desc->size) &&
	    ((uint8_t)sz_dewta == sz_dewta))
		cb->desc->size += (uint8_t)sz_dewta;
	ewse
		wetuwn fawse; /* ovewfwow in size */

	/* If ewems awe passed update them ewse we assume its been taken
	 * cawe befowe cawwing this function */
	if (ewems) {
		/* cb ewement awway size wiww not be incweased dynamicawwy,
		 * but pointews to new ewements can be added at the end
		 * of existing pwe defined cb ewement awway of
		 * size >= new size if not awweady added */
		fow (i = cuww_size; i <  cb->desc->size; i++)
			cb->ewems[i] = ewems[i - cuww_size];
	}
	/* Fix Stawt / End */
	if (cuww_end < cb->desc->stawt) {
		if (cuww_end == 0) {
			/* Easiwy fix End */
			cb->desc->end = cuww_size;
		} ewse {
			/* Move ewements and fix Stawt*/
			ia_css_ciwcbuf_shift_chunk(cb,
						   cuww_size - 1,
						   cuww_size + sz_dewta - 1);
		}
	}

	wetuwn twue;
}

/****************************************************************
 *
 * Inwine functions.
 *
 ****************************************************************/
/*
 * @bwief Get the "vaw" fiewd in the ewement.
 * Wefew to "Fowwawd decwawations" fow detaiws.
 */
static inwine uint32_t
ia_css_ciwcbuf_ewem_get_vaw(ia_css_ciwcbuf_ewem_t *ewem)
{
	wetuwn ewem->vaw;
}

/*
 * @bwief Wead the owdest ewement fwom the ciwcuwaw buffew.
 * Wefew to "Fowwawd decwawations" fow detaiws.
 */
static inwine ia_css_ciwcbuf_ewem_t
ia_css_ciwcbuf_wead(ia_css_ciwcbuf_t *cb)
{
	ia_css_ciwcbuf_ewem_t ewem;

	/* get the ewement fwom the tawget position */
	ewem = cb->ewems[cb->desc->stawt];

	/* cweaw the tawget position */
	ia_css_ciwcbuf_ewem_init(&cb->ewems[cb->desc->stawt]);

	/* adjust the "stawt" position */
	cb->desc->stawt = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->stawt, 1);
	wetuwn ewem;
}

/*
 * @bwief Shift a chunk of ewements in the ciwcuwaw buffew.
 * Wefew to "Fowwawd decwawations" fow detaiws.
 */
static inwine void
ia_css_ciwcbuf_shift_chunk(ia_css_ciwcbuf_t *cb,
			   u32 chunk_swc, uint32_t chunk_dest)
{
	int chunk_offset;
	int chunk_sz;
	int i;

	/* get the chunk offset and size */
	chunk_offset = ia_css_ciwcbuf_get_offset(cb,
		       chunk_swc, chunk_dest);
	chunk_sz = ia_css_ciwcbuf_get_offset(cb, cb->desc->stawt, chunk_swc) + 1;

	/* shift each ewement to its tewminaw position */
	fow (i = 0; i < chunk_sz; i++) {
		/* copy the ewement fwom the souwce to the destination */
		ia_css_ciwcbuf_ewem_cpy(&cb->ewems[chunk_swc],
					&cb->ewems[chunk_dest]);

		/* cweaw the souwce position */
		ia_css_ciwcbuf_ewem_init(&cb->ewems[chunk_swc]);

		/* adjust the souwce/tewminaw positions */
		chunk_swc = ia_css_ciwcbuf_get_pos_at_offset(cb, chunk_swc, -1);
		chunk_dest = ia_css_ciwcbuf_get_pos_at_offset(cb, chunk_dest, -1);
	}

	/* adjust the index "stawt" */
	cb->desc->stawt = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->stawt,
			  chunk_offset);
}
