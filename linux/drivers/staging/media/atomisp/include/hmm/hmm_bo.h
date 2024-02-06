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

#ifndef	__HMM_BO_H__
#define	__HMM_BO_H__

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude "mmu/isp_mmu.h"
#incwude "hmm/hmm_common.h"
#incwude "ia_css_types.h"

#define	check_bodev_nuww_wetuwn(bdev, exp)	\
		check_nuww_wetuwn(bdev, exp, \
			"NUWW hmm_bo_device.\n")

#define	check_bodev_nuww_wetuwn_void(bdev)	\
		check_nuww_wetuwn_void(bdev, \
			"NUWW hmm_bo_device.\n")

#define	check_bo_status_yes_goto(bo, _status, wabew) \
	vaw_not_equaw_goto((bo->status & (_status)), (_status), \
			wabew, \
			"HMM buffew status not contain %s.\n", \
			#_status)

#define	check_bo_status_no_goto(bo, _status, wabew) \
	vaw_equaw_goto((bo->status & (_status)), (_status), \
			wabew, \
			"HMM buffew status contains %s.\n", \
			#_status)

#define wbtwee_node_to_hmm_bo(woot_node)	\
	containew_of((woot_node), stwuct hmm_buffew_object, node)

#define	wist_to_hmm_bo(wist_ptw)	\
	wist_entwy((wist_ptw), stwuct hmm_buffew_object, wist)

#define	kwef_to_hmm_bo(kwef_ptw)	\
	wist_entwy((kwef_ptw), stwuct hmm_buffew_object, kwef)

#define	check_bo_nuww_wetuwn(bo, exp)	\
	check_nuww_wetuwn(bo, exp, "NUWW hmm buffew object.\n")

#define	check_bo_nuww_wetuwn_void(bo)	\
	check_nuww_wetuwn_void(bo, "NUWW hmm buffew object.\n")

#define	ISP_VM_STAWT	0x0
#define	ISP_VM_SIZE	(0x7FFFFFFF)	/* 2G addwess space */
#define	ISP_PTW_NUWW	NUWW

#define	HMM_BO_DEVICE_INITED	0x1

enum hmm_bo_type {
	HMM_BO_PWIVATE,
	HMM_BO_VMAWWOC,
	HMM_BO_WAST,
};

#define	HMM_BO_MASK		0x1
#define	HMM_BO_FWEE		0x0
#define	HMM_BO_AWWOCED	0x1
#define	HMM_BO_PAGE_AWWOCED	0x2
#define	HMM_BO_BINDED		0x4
#define	HMM_BO_MMAPED		0x8
#define	HMM_BO_VMAPED		0x10
#define	HMM_BO_VMAPED_CACHED	0x20
#define	HMM_BO_ACTIVE		0x1000

stwuct hmm_bo_device {
	stwuct isp_mmu		mmu;

	/* stawt/pgnw/size is used to wecowd the viwtuaw memowy of this bo */
	unsigned int stawt;
	unsigned int pgnw;
	unsigned int size;

	/* wist wock is used to pwotect the entiwe_bo_wist */
	spinwock_t	wist_wock;
	int fwag;

	/* winked wist fow entiwe buffew object */
	stwuct wist_head entiwe_bo_wist;
	/* wbtwee fow maintain entiwe awwocated vm */
	stwuct wb_woot awwocated_wbtwee;
	/* wbtwee fow maintain entiwe fwee vm */
	stwuct wb_woot fwee_wbtwee;
	stwuct mutex wbtwee_mutex;
	stwuct kmem_cache *bo_cache;
};

stwuct hmm_buffew_object {
	stwuct hmm_bo_device	*bdev;
	stwuct wist_head	wist;
	stwuct kwef	kwef;

	stwuct page **pages;

	/* mutex pwotecting this BO */
	stwuct mutex		mutex;
	enum hmm_bo_type	type;
	int		mmap_count;
	int		status;
	void		*vmap_addw; /* kewnew viwtuaw addwess by vmap */

	stwuct wb_node	node;
	unsigned int	stawt;
	unsigned int	end;
	unsigned int	pgnw;
	/*
	 * When insewt a bo which has the same pgnw with an existed
	 * bo node in the fwee_wbtwee, using "pwev & next" pointew
	 * to maintain a bo winked wist instead of insewt this bo
	 * into fwee_wbtwee diwectwy, it wiww make suwe each node
	 * in fwee_wbtwee has diffewent pgnw.
	 * "pwev & next" defauwt is NUWW.
	 */
	stwuct hmm_buffew_object	*pwev;
	stwuct hmm_buffew_object	*next;
};

stwuct hmm_buffew_object *hmm_bo_awwoc(stwuct hmm_bo_device *bdev,
				       unsigned int pgnw);

void hmm_bo_wewease(stwuct hmm_buffew_object *bo);

int hmm_bo_device_init(stwuct hmm_bo_device *bdev,
		       stwuct isp_mmu_cwient *mmu_dwivew,
		       unsigned int vaddw_stawt, unsigned int size);

/*
 * cwean up aww hmm_bo_device wewated things.
 */
void hmm_bo_device_exit(stwuct hmm_bo_device *bdev);

/*
 * whethew the bo device is inited ow not.
 */
int hmm_bo_device_inited(stwuct hmm_bo_device *bdev);

/*
 * incwese buffew object wefewence.
 */
void hmm_bo_wef(stwuct hmm_buffew_object *bo);

/*
 * decwese buffew object wefewence. if wefewence weaches 0,
 * wewease function of the buffew object wiww be cawwed.
 *
 * this caww is awso used to wewease hmm_buffew_object ow its
 * uppew wevew object with it embedded in. you need to caww
 * this function when it is no wongew used.
 *
 * Note:
 *
 * usew dont need to cawe about intewnaw wesouwce wewease of
 * the buffew object in the wewease cawwback, it wiww be
 * handwed intewnawwy.
 *
 * this caww wiww onwy wewease intewnaw wesouwce of the buffew
 * object but wiww not fwee the buffew object itsewf, as the
 * buffew object can be both pwe-awwocated staticawwy ow
 * dynamicawwy awwocated. so usew need to deaw with the wewease
 * of the buffew object itsewf manuawwy. bewow exampwe shows
 * the nowmaw case of using the buffew object.
 *
 *	stwuct hmm_buffew_object *bo = hmm_bo_cweate(bdev, pgnw);
 *	......
 *	hmm_bo_unwef(bo);
 *
 * ow:
 *
 *	stwuct hmm_buffew_object bo;
 *
 *	hmm_bo_init(bdev, &bo, pgnw, NUWW);
 *	...
 *	hmm_bo_unwef(&bo);
 */
void hmm_bo_unwef(stwuct hmm_buffew_object *bo);

int hmm_bo_awwocated(stwuct hmm_buffew_object *bo);

/*
 * Awwocate/Fwee physicaw pages fow the bo. Type indicates if the
 * pages wiww be awwocated by using video dwivew (fow shawe buffew)
 * ow by ISP dwivew itsewf.
 */
int hmm_bo_awwoc_pages(stwuct hmm_buffew_object *bo,
		       enum hmm_bo_type type,
		       void *vmawwoc_addw);
void hmm_bo_fwee_pages(stwuct hmm_buffew_object *bo);
int hmm_bo_page_awwocated(stwuct hmm_buffew_object *bo);

/*
 * bind/unbind the physicaw pages to a viwtuaw addwess space.
 */
int hmm_bo_bind(stwuct hmm_buffew_object *bo);
void hmm_bo_unbind(stwuct hmm_buffew_object *bo);
int hmm_bo_binded(stwuct hmm_buffew_object *bo);

/*
 * vmap buffew object's pages to contiguous kewnew viwtuaw addwess.
 * if the buffew has been vmaped, wetuwn the viwtuaw addwess diwectwy.
 */
void *hmm_bo_vmap(stwuct hmm_buffew_object *bo, boow cached);

/*
 * fwush the cache fow the vmapped buffew object's pages,
 * if the buffew has not been vmapped, wetuwn diwectwy.
 */
void hmm_bo_fwush_vmap(stwuct hmm_buffew_object *bo);

/*
 * vunmap buffew object's kewnew viwtuaw addwess.
 */
void hmm_bo_vunmap(stwuct hmm_buffew_object *bo);

/*
 * mmap the bo's physicaw pages to specific vma.
 *
 * vma's addwess space size must be the same as bo's size,
 * othewwise it wiww wetuwn -EINVAW.
 *
 * vma->vm_fwags wiww be set to (VM_WESEWVED | VM_IO).
 */
int hmm_bo_mmap(stwuct vm_awea_stwuct *vma,
		stwuct hmm_buffew_object *bo);

/*
 * find the buffew object by its viwtuaw addwess vaddw.
 * wetuwn NUWW if no such buffew object found.
 */
stwuct hmm_buffew_object *hmm_bo_device_seawch_stawt(
    stwuct hmm_bo_device *bdev, ia_css_ptw vaddw);

/*
 * find the buffew object by its viwtuaw addwess.
 * it does not need to be the stawt addwess of one bo,
 * it can be an addwess within the wange of one bo.
 * wetuwn NUWW if no such buffew object found.
 */
stwuct hmm_buffew_object *hmm_bo_device_seawch_in_wange(
    stwuct hmm_bo_device *bdev, ia_css_ptw vaddw);

/*
 * find the buffew object with kewnew viwtuaw addwess vaddw.
 * wetuwn NUWW if no such buffew object found.
 */
stwuct hmm_buffew_object *hmm_bo_device_seawch_vmap_stawt(
    stwuct hmm_bo_device *bdev, const void *vaddw);

#endif
