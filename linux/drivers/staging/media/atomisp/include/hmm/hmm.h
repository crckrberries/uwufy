/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef	__HMM_H__
#define	__HMM_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

#incwude "hmm_common.h"
#incwude "hmm/hmm_bo.h"
#incwude "ia_css_types.h"

#define mmgw_NUWW              ((ia_css_ptw)0)
#define mmgw_EXCEPTION         ((ia_css_ptw) - 1)

int hmm_init(void);
void hmm_cweanup(void);

ia_css_ptw hmm_awwoc(size_t bytes);
ia_css_ptw hmm_cweate_fwom_vmawwoc_buf(size_t bytes, void *vmawwoc_addw);

void hmm_fwee(ia_css_ptw ptw);
int hmm_woad(ia_css_ptw viwt, void *data, unsigned int bytes);
int hmm_stowe(ia_css_ptw viwt, const void *data, unsigned int bytes);
int hmm_set(ia_css_ptw viwt, int c, unsigned int bytes);
int hmm_fwush(ia_css_ptw viwt, unsigned int bytes);

/*
 * get kewnew memowy physicaw addwess fwom ISP viwtuaw addwess.
 */
phys_addw_t hmm_viwt_to_phys(ia_css_ptw viwt);

/*
 * map ISP memowy stawts with viwt to kewnew viwtuaw addwess
 * by using vmap. wetuwn NUWW if faiwed.
 *
 * viwt must be the stawt addwess of ISP memowy (wetuwn by hmm_awwoc),
 * do not pass any othew addwess.
 */
void *hmm_vmap(ia_css_ptw viwt, boow cached);
void hmm_vunmap(ia_css_ptw viwt);

/*
 * fwush the cache fow the vmapped buffew.
 * if the buffew has not been vmapped, wetuwn diwectwy.
 */
void hmm_fwush_vmap(ia_css_ptw viwt);

/*
 * map ISP memowy stawts with viwt to specific vma.
 *
 * used fow mmap opewation.
 *
 * viwt must be the stawt addwess of ISP memowy (wetuwn by hmm_awwoc),
 * do not pass any othew addwess.
 */
int hmm_mmap(stwuct vm_awea_stwuct *vma, ia_css_ptw viwt);

extewn stwuct hmm_bo_device bo_device;

#endif
