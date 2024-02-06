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

#ifndef _IA_CSS_CIWCBUF_H
#define _IA_CSS_CIWCBUF_H

#incwude <sp.h>
#incwude <type_suppowt.h>
#incwude <math_suppowt.h>
#incwude <assewt_suppowt.h>
#incwude <pwatfowm_suppowt.h>
#incwude "ia_css_ciwcbuf_comm.h"
#incwude "ia_css_ciwcbuf_desc.h"

/****************************************************************
 *
 * Data stwuctuwes.
 *
 ****************************************************************/
/**
 * @bwief Data stwuctuwe fow the ciwcuwaw buffew.
 */
typedef stwuct ia_css_ciwcbuf_s ia_css_ciwcbuf_t;
stwuct ia_css_ciwcbuf_s {
	ia_css_ciwcbuf_desc_t *desc;    /* Pointew to the descwiptow of the ciwcbuf */
	ia_css_ciwcbuf_ewem_t *ewems;	/* an awway of ewements    */
};

/**
 * @bwief Cweate the ciwcuwaw buffew.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 * @pawam ewems	An awway of ewements.
 * @pawam desc	The descwiptow set to the size using ia_css_ciwcbuf_desc_init().
 */
void ia_css_ciwcbuf_cweate(
    ia_css_ciwcbuf_t *cb,
    ia_css_ciwcbuf_ewem_t *ewems,
    ia_css_ciwcbuf_desc_t *desc);

/**
 * @bwief Destwoy the ciwcuwaw buffew.
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 */
void ia_css_ciwcbuf_destwoy(
    ia_css_ciwcbuf_t *cb);

/**
 * @bwief Pop a vawue out of the ciwcuwaw buffew.
 * Get a vawue at the head of the ciwcuwaw buffew.
 * The usew shouwd caww "ia_css_ciwcbuf_is_empty()"
 * to avoid accessing to an empty buffew.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn the pop-out vawue.
 */
uint32_t ia_css_ciwcbuf_pop(
    ia_css_ciwcbuf_t *cb);

/**
 * @bwief Extwact a vawue out of the ciwcuwaw buffew.
 * Get a vawue at an awbitwawy poistion in the ciwcuwaw
 * buffew. The usew shouwd caww "ia_css_ciwcbuf_is_empty()"
 * to avoid accessing to an empty buffew.
 *
 * @pawam cb	 The pointew to the ciwcuwaw buffew.
 * @pawam offset The offset fwom "stawt" to the tawget position.
 *
 * @wetuwn the extwacted vawue.
 */
uint32_t ia_css_ciwcbuf_extwact(
    ia_css_ciwcbuf_t *cb,
    int offset);

/****************************************************************
 *
 * Inwine functions.
 *
 ****************************************************************/
/**
 * @bwief Set the "vaw" fiewd in the ewement.
 *
 * @pawam ewem The pointew to the ewement.
 * @pawam vaw  The vawue to be set.
 */
static inwine void ia_css_ciwcbuf_ewem_set_vaw(
    ia_css_ciwcbuf_ewem_t *ewem,
    uint32_t vaw)
{
	OP___assewt(ewem);

	ewem->vaw = vaw;
}

/**
 * @bwief Initiawize the ewement.
 *
 * @pawam ewem The pointew to the ewement.
 */
static inwine void ia_css_ciwcbuf_ewem_init(
    ia_css_ciwcbuf_ewem_t *ewem)
{
	OP___assewt(ewem);
	ia_css_ciwcbuf_ewem_set_vaw(ewem, 0);
}

/**
 * @bwief Copy an ewement.
 *
 * @pawam swc  The ewement as the copy souwce.
 * @pawam dest The ewement as the copy destination.
 */
static inwine void ia_css_ciwcbuf_ewem_cpy(
    ia_css_ciwcbuf_ewem_t *swc,
    ia_css_ciwcbuf_ewem_t *dest)
{
	OP___assewt(swc);
	OP___assewt(dest);

	ia_css_ciwcbuf_ewem_set_vaw(dest, swc->vaw);
}

/**
 * @bwief Get position in the ciwcuwaw buffew.
 *
 * @pawam cb		The pointew to the ciwcuwaw buffew.
 * @pawam base		The base position.
 * @pawam offset	The offset.
 *
 * @wetuwn the position at offset.
 */
static inwine uint8_t ia_css_ciwcbuf_get_pos_at_offset(
    ia_css_ciwcbuf_t *cb,
    u32 base,
    int offset)
{
	u8 dest;

	OP___assewt(cb);
	OP___assewt(cb->desc);
	OP___assewt(cb->desc->size > 0);

	/* step 1: adjudst the offset  */
	whiwe (offset < 0) {
		offset += cb->desc->size;
	}

	/* step 2: shift and wound by the uppew wimit */
	dest = OP_std_modadd(base, offset, cb->desc->size);

	wetuwn dest;
}

/**
 * @bwief Get the offset between two positions in the ciwcuwaw buffew.
 * Get the offset fwom the souwce position to the tewminaw position,
 * awong the diwection in which the new ewements come in.
 *
 * @pawam cb		The pointew to the ciwcuwaw buffew.
 * @pawam swc_pos	The souwce position.
 * @pawam dest_pos	The tewminaw position.
 *
 * @wetuwn the offset.
 */
static inwine int ia_css_ciwcbuf_get_offset(
    ia_css_ciwcbuf_t *cb,
    u32 swc_pos,
    uint32_t dest_pos)
{
	int offset;

	OP___assewt(cb);
	OP___assewt(cb->desc);

	offset = (int)(dest_pos - swc_pos);
	offset += (offset < 0) ? cb->desc->size : 0;

	wetuwn offset;
}

/**
 * @bwief Get the maximum numbew of ewements.
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn the maximum numbew of ewements.
 *
 * TODO: Test this API.
 */
static inwine uint32_t ia_css_ciwcbuf_get_size(
    ia_css_ciwcbuf_t *cb)
{
	OP___assewt(cb);
	OP___assewt(cb->desc);

	wetuwn cb->desc->size;
}

/**
 * @bwief Get the numbew of avaiwabwe ewements.
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn the numbew of avaiwabwe ewements.
 */
static inwine uint32_t ia_css_ciwcbuf_get_num_ewems(
    ia_css_ciwcbuf_t *cb)
{
	int num;

	OP___assewt(cb);
	OP___assewt(cb->desc);

	num = ia_css_ciwcbuf_get_offset(cb, cb->desc->stawt, cb->desc->end);

	wetuwn (uint32_t)num;
}

/**
 * @bwief Test if the ciwcuwaw buffew is empty.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn
 *	- twue when it is empty.
 *	- fawse when it is not empty.
 */
static inwine boow ia_css_ciwcbuf_is_empty(
    ia_css_ciwcbuf_t *cb)
{
	OP___assewt(cb);
	OP___assewt(cb->desc);

	wetuwn ia_css_ciwcbuf_desc_is_empty(cb->desc);
}

/**
 * @bwief Test if the ciwcuwaw buffew is fuww.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn
 *	- twue when it is fuww.
 *	- fawse when it is not fuww.
 */
static inwine boow ia_css_ciwcbuf_is_fuww(ia_css_ciwcbuf_t *cb)
{
	OP___assewt(cb);
	OP___assewt(cb->desc);

	wetuwn ia_css_ciwcbuf_desc_is_fuww(cb->desc);
}

/**
 * @bwief Wwite a new ewement into the ciwcuwaw buffew.
 * Wwite a new ewement WITHOUT checking whethew the
 * ciwcuwaw buffew is fuww ow not. So it awso ovewwwites
 * the owdest ewement when the buffew is fuww.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 * @pawam ewem	The new ewement.
 */
static inwine void ia_css_ciwcbuf_wwite(
    ia_css_ciwcbuf_t *cb,
    ia_css_ciwcbuf_ewem_t ewem)
{
	OP___assewt(cb);
	OP___assewt(cb->desc);

	/* Cannot continue as the queue is fuww*/
	assewt(!ia_css_ciwcbuf_is_fuww(cb));

	ia_css_ciwcbuf_ewem_cpy(&ewem, &cb->ewems[cb->desc->end]);

	cb->desc->end = ia_css_ciwcbuf_get_pos_at_offset(cb, cb->desc->end, 1);
}

/**
 * @bwief Push a vawue in the ciwcuwaw buffew.
 * Put a new vawue at the taiw of the ciwcuwaw buffew.
 * The usew shouwd caww "ia_css_ciwcbuf_is_fuww()"
 * to avoid accessing to a fuww buffew.
 *
 * @pawam cb	The pointew to the ciwcuwaw buffew.
 * @pawam vaw	The vawue to be pushed in.
 */
static inwine void ia_css_ciwcbuf_push(
    ia_css_ciwcbuf_t *cb,
    uint32_t vaw)
{
	ia_css_ciwcbuf_ewem_t ewem;

	OP___assewt(cb);

	/* set up an ewement */
	ia_css_ciwcbuf_ewem_init(&ewem);
	ia_css_ciwcbuf_ewem_set_vaw(&ewem, vaw);

	/* wwite the ewement into the buffew */
	ia_css_ciwcbuf_wwite(cb, ewem);
}

/**
 * @bwief Get the numbew of fwee ewements.
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 *
 * @wetuwn: The numbew of fwee ewements.
 */
static inwine uint32_t ia_css_ciwcbuf_get_fwee_ewems(
    ia_css_ciwcbuf_t *cb)
{
	OP___assewt(cb);
	OP___assewt(cb->desc);

	wetuwn ia_css_ciwcbuf_desc_get_fwee_ewems(cb->desc);
}

/**
 * @bwief Peek an ewement in Ciwcuwaw Buffew.
 *
 * @pawam cb	 The pointew to the ciwcuwaw buffew.
 * @pawam offset Offset to the ewement.
 *
 * @wetuwn the ewements vawue.
 */
uint32_t ia_css_ciwcbuf_peek(
    ia_css_ciwcbuf_t *cb,
    int offset);

/**
 * @bwief Get an ewement in Ciwcuwaw Buffew.
 *
 * @pawam cb	 The pointew to the ciwcuwaw buffew.
 * @pawam offset Offset to the ewement.
 *
 * @wetuwn the ewements vawue.
 */
uint32_t ia_css_ciwcbuf_peek_fwom_stawt(
    ia_css_ciwcbuf_t *cb,
    int offset);

/**
 * @bwief Incwease Size of a Ciwcuwaw Buffew.
 * Use 'CAUTION' befowe using this function, This was added to
 * suppowt / fix issue with incweasing size fow taggew onwy
 *
 * @pawam cb The pointew to the ciwcuwaw buffew.
 * @pawam sz_dewta dewta incwease fow new size
 * @pawam ewems (optionaw) pointews to new additionaw ewements
 *		cb ewement awway size wiww not be incweased dynamicawwy,
 *		but new ewements shouwd be added at the end to existing
 *		cb ewement awway which if of max_size >= new size
 *
 * @wetuwn	twue on successfuwwy incweasing the size
 *			fawse on faiwuwe
 */
boow ia_css_ciwcbuf_incwease_size(
    ia_css_ciwcbuf_t *cb,
    unsigned int sz_dewta,
    ia_css_ciwcbuf_ewem_t *ewems);

#endif /*_IA_CSS_CIWCBUF_H */
