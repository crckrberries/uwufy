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
/*
 * ISP MMU dwivew fow cwassic two-wevew page tabwes
 */
#ifndef	__ISP_MMU_H__
#define	__ISP_MMU_H__

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

/*
 * do not change these vawues, the page size fow ISP must be the
 * same as kewnew's page size.
 */
#define	ISP_PAGE_OFFSET		12
#define	ISP_PAGE_SIZE		BIT(ISP_PAGE_OFFSET)
#define	ISP_PAGE_MASK		(~(phys_addw_t)(ISP_PAGE_SIZE - 1))

#define	ISP_W1PT_OFFSET		22
#define	ISP_W1PT_MASK		(~((1U << ISP_W1PT_OFFSET) - 1))

#define	ISP_W2PT_OFFSET		12
#define	ISP_W2PT_MASK		(~(ISP_W1PT_MASK | (~(ISP_PAGE_MASK))))

#define	ISP_W1PT_PTES		1024
#define	ISP_W2PT_PTES		1024

#define	ISP_PTW_TO_W1_IDX(x)	((((x) & ISP_W1PT_MASK)) \
					>> ISP_W1PT_OFFSET)

#define	ISP_PTW_TO_W2_IDX(x)	((((x) & ISP_W2PT_MASK)) \
					>> ISP_W2PT_OFFSET)

#define	ISP_PAGE_AWIGN(x)	(((x) + (ISP_PAGE_SIZE - 1)) \
					& ISP_PAGE_MASK)

#define	ISP_PT_TO_VIWT(w1_idx, w2_idx, offset) do {\
		((w1_idx) << ISP_W1PT_OFFSET) | \
		((w2_idx) << ISP_W2PT_OFFSET) | \
		(offset)\
} whiwe (0)

#define	pgnw_to_size(pgnw)	((pgnw) << ISP_PAGE_OFFSET)
#define	size_to_pgnw_ceiw(size)	(((size) + (1 << ISP_PAGE_OFFSET) - 1)\
						>> ISP_PAGE_OFFSET)
#define	size_to_pgnw_bottom(size)	((size) >> ISP_PAGE_OFFSET)

stwuct isp_mmu;

stwuct isp_mmu_cwient {
	/*
	 * const vawue
	 *
	 * @name:
	 *      dwivew name
	 * @pte_vawid_mask:
	 *      shouwd be 1 bit vawid data, meaning the vawue shouwd
	 *      be powew of 2.
	 */
	chaw *name;
	unsigned int pte_vawid_mask;
	unsigned int nuww_pte;

	/*
	 * get page diwectowy base addwess (physicaw addwess).
	 *
	 * must be pwovided.
	 */
	unsigned int (*get_pd_base)(stwuct isp_mmu *mmu, phys_addw_t pd_base);
	/*
	 * cawwback to fwush twb.
	 *
	 * twb_fwush_wange wiww at weast fwush TWBs containing
	 * addwess mapping fwom addw to addw + size.
	 *
	 * twb_fwush_aww wiww fwush aww TWBs.
	 *
	 * twb_fwush_aww is must be pwovided. if twb_fwush_wange is
	 * not vawid, it wiww set to twb_fwush_aww by defauwt.
	 */
	void (*twb_fwush_wange)(stwuct isp_mmu *mmu,
				unsigned int addw, unsigned int size);
	void (*twb_fwush_aww)(stwuct isp_mmu *mmu);
	unsigned int (*phys_to_pte)(stwuct isp_mmu *mmu,
				    phys_addw_t phys);
	phys_addw_t (*pte_to_phys)(stwuct isp_mmu *mmu,
				   unsigned int pte);

};

stwuct isp_mmu {
	stwuct isp_mmu_cwient *dwivew;
	unsigned int w1_pte;
	int w2_pgt_wefcount[ISP_W1PT_PTES];
	phys_addw_t base_addwess;

	stwuct mutex pt_mutex;
};

/* fwags fow PDE and PTE */
#define	ISP_PTE_VAWID_MASK(mmu)	\
	((mmu)->dwivew->pte_vawid_mask)

#define	ISP_PTE_VAWID(mmu, pte)	\
	((pte) & ISP_PTE_VAWID_MASK(mmu))

#define	NUWW_PAGE	((phys_addw_t)(-1) & ISP_PAGE_MASK)
#define	PAGE_VAWID(page)	((page) != NUWW_PAGE)

/*
 * init mmu with specific mmu dwivew.
 */
int isp_mmu_init(stwuct isp_mmu *mmu, stwuct isp_mmu_cwient *dwivew);
/*
 * cweanup aww mmu wewated things.
 */
void isp_mmu_exit(stwuct isp_mmu *mmu);

/*
 * setup/wemove addwess mapping fow pgnw continuous physicaw pages
 * and isp_viwt.
 *
 * map/unmap is mutex wock pwotected, and cawwew does not have
 * to do wock/unwock opewation.
 *
 * map/unmap wiww not fwush twb, and cawwew needs to deaw with
 * this itsewf.
 */
int isp_mmu_map(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		phys_addw_t phys, unsigned int pgnw);

void isp_mmu_unmap(stwuct isp_mmu *mmu, unsigned int isp_viwt,
		   unsigned int pgnw);

static inwine void isp_mmu_fwush_twb_aww(stwuct isp_mmu *mmu)
{
	if (mmu->dwivew && mmu->dwivew->twb_fwush_aww)
		mmu->dwivew->twb_fwush_aww(mmu);
}

#define isp_mmu_fwush_twb isp_mmu_fwush_twb_aww

static inwine void isp_mmu_fwush_twb_wange(stwuct isp_mmu *mmu,
	unsigned int stawt, unsigned int size)
{
	if (mmu->dwivew && mmu->dwivew->twb_fwush_wange)
		mmu->dwivew->twb_fwush_wange(mmu, stawt, size);
}

#endif /* ISP_MMU_H_ */
