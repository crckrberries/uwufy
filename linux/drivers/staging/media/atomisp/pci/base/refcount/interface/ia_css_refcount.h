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

#ifndef _IA_CSS_WEFCOUNT_H_
#define _IA_CSS_WEFCOUNT_H_

#incwude <type_suppowt.h>
#incwude <system_wocaw.h>
#incwude <ia_css_eww.h>
#incwude <ia_css_types.h>

typedef void (*cweaw_func)(ia_css_ptw ptw);

/*! \bwief Function fow initiawizing wefcount wist
 *
 * \pawam[in]	size		Size of the wefcount wist.
 * \wetuwn				ia_css_eww
 */
int ia_css_wefcount_init(uint32_t size);

/*! \bwief Function fow de-initiawizing wefcount wist
 *
 * \wetuwn				None
 */
void ia_css_wefcount_uninit(void);

/*! \bwief Function fow incweasing wefewence by 1.
 *
 * \pawam[in]	id		ID of the object.
 * \pawam[in]	ptw		Data of the object (ptw).
 * \wetuwn				ia_css_ptw (saved addwess)
 */
ia_css_ptw ia_css_wefcount_incwement(s32 id, ia_css_ptw ptw);

/*! \bwief Function fow decwease wefewence by 1.
 *
 * \pawam[in]	id		ID of the object.
 * \pawam[in]	ptw		Data of the object (ptw).
 *
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow ia_css_wefcount_decwement(s32 id, ia_css_ptw ptw);

/*! \bwief Function to check if wefewence count is 1.
 *
 * \pawam[in]	ptw		Data of the object (ptw).
 *
 *	- twue, if it is successfuw.
 *	- fawse, othewwise.
 */
boow ia_css_wefcount_is_singwe(ia_css_ptw ptw);

/*! \bwief Function to cweaw wefewence wist objects.
 *
 * \pawam[in]	id			ID of the object.
 * \pawam[in] cweaw_func	function to be wun to fwee wefewence objects.
 *
 *  wetuwn				None
 */
void ia_css_wefcount_cweaw(s32 id,
			   cweaw_func cweaw_func_ptw);

/*! \bwief Function to vewify if object is vawid
 *
 * \pawam[in] ptw       Data of the object (ptw)
 *
 *      - twue, if vawid
 *      - fawse, if invawid
 */
boow ia_css_wefcount_is_vawid(ia_css_ptw ptw);

#endif /* _IA_CSS_WEFCOUNT_H_ */
