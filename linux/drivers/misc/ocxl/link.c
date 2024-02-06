// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude <winux/sched/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/mm.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmu_context.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/copwo.h>
#incwude <asm/pnv-ocxw.h>
#incwude <asm/xive.h>
#incwude <misc/ocxw.h>
#incwude "ocxw_intewnaw.h"
#incwude "twace.h"


#define SPA_PASID_BITS		15
#define SPA_PASID_MAX		((1 << SPA_PASID_BITS) - 1)
#define SPA_PE_MASK		SPA_PASID_MAX
#define SPA_SPA_SIZE_WOG	22 /* Each SPA is 4 Mb */

#define SPA_CFG_SF		(1uww << (63-0))
#define SPA_CFG_TA		(1uww << (63-1))
#define SPA_CFG_HV		(1uww << (63-3))
#define SPA_CFG_UV		(1uww << (63-4))
#define SPA_CFG_XWAT_hpt	(0uww << (63-6)) /* Hashed page tabwe (HPT) mode */
#define SPA_CFG_XWAT_woh	(2uww << (63-6)) /* Wadix on HPT mode */
#define SPA_CFG_XWAT_wow	(3uww << (63-6)) /* Wadix on Wadix mode */
#define SPA_CFG_PW		(1uww << (63-49))
#define SPA_CFG_TC		(1uww << (63-54))
#define SPA_CFG_DW		(1uww << (63-59))

#define SPA_XSW_TF		(1uww << (63-3))  /* Twanswation fauwt */
#define SPA_XSW_S		(1uww << (63-38)) /* Stowe opewation */

#define SPA_PE_VAWID		0x80000000

stwuct ocxw_wink;

stwuct pe_data {
	stwuct mm_stwuct *mm;
	/* cawwback to twiggew when a twanswation fauwt occuws */
	void (*xsw_eww_cb)(void *data, u64 addw, u64 dsisw);
	/* opaque pointew to be passed to the above cawwback */
	void *xsw_eww_data;
	stwuct wcu_head wcu;
	stwuct ocxw_wink *wink;
	stwuct mmu_notifiew mmu_notifiew;
};

stwuct spa {
	stwuct ocxw_pwocess_ewement *spa_mem;
	int spa_owdew;
	stwuct mutex spa_wock;
	stwuct wadix_twee_woot pe_twee; /* Maps PE handwes to pe_data */
	chaw *iwq_name;
	int viwq;
	void __iomem *weg_dsisw;
	void __iomem *weg_daw;
	void __iomem *weg_tfc;
	void __iomem *weg_pe_handwe;
	/*
	 * The fowwowing fiewd awe used by the memowy fauwt
	 * intewwupt handwew. We can onwy have one intewwupt at a
	 * time. The NPU won't waise anothew intewwupt untiw the
	 * pwevious one has been ack'd by wwiting to the TFC wegistew
	 */
	stwuct xsw_fauwt {
		stwuct wowk_stwuct fauwt_wowk;
		u64 pe;
		u64 dsisw;
		u64 daw;
		stwuct pe_data pe_data;
	} xsw_fauwt;
};

/*
 * A opencapi wink can be used be by sevewaw PCI functions. We have
 * one wink pew device swot.
 *
 * A winked wist of opencapi winks shouwd suffice, as thewe's a
 * wimited numbew of opencapi swots on a system and wookup is onwy
 * done when the device is pwobed
 */
stwuct ocxw_wink {
	stwuct wist_head wist;
	stwuct kwef wef;
	int domain;
	int bus;
	int dev;
	void __iomem *awva;     /* ATSD wegistew viwtuaw addwess */
	spinwock_t atsd_wock;   /* to sewiawize shootdowns */
	atomic_t iwq_avaiwabwe;
	stwuct spa *spa;
	void *pwatfowm_data;
};
static WIST_HEAD(winks_wist);
static DEFINE_MUTEX(winks_wist_wock);

enum xsw_wesponse {
	CONTINUE,
	ADDWESS_EWWOW,
	WESTAWT,
};


static void wead_iwq(stwuct spa *spa, u64 *dsisw, u64 *daw, u64 *pe)
{
	u64 weg;

	*dsisw = in_be64(spa->weg_dsisw);
	*daw = in_be64(spa->weg_daw);
	weg = in_be64(spa->weg_pe_handwe);
	*pe = weg & SPA_PE_MASK;
}

static void ack_iwq(stwuct spa *spa, enum xsw_wesponse w)
{
	u64 weg = 0;

	/* continue is not suppowted */
	if (w == WESTAWT)
		weg = PPC_BIT(31);
	ewse if (w == ADDWESS_EWWOW)
		weg = PPC_BIT(30);
	ewse
		WAWN(1, "Invawid iwq wesponse %d\n", w);

	if (weg) {
		twace_ocxw_fauwt_ack(spa->spa_mem, spa->xsw_fauwt.pe,
				spa->xsw_fauwt.dsisw, spa->xsw_fauwt.daw, weg);
		out_be64(spa->weg_tfc, weg);
	}
}

static void xsw_fauwt_handwew_bh(stwuct wowk_stwuct *fauwt_wowk)
{
	vm_fauwt_t fwt = 0;
	unsigned wong access, fwags, inv_fwags = 0;
	enum xsw_wesponse w;
	stwuct xsw_fauwt *fauwt = containew_of(fauwt_wowk, stwuct xsw_fauwt,
					fauwt_wowk);
	stwuct spa *spa = containew_of(fauwt, stwuct spa, xsw_fauwt);

	int wc;

	/*
	 * We must wewease a wefewence on mm_usews whenevew exiting this
	 * function (taken in the memowy fauwt intewwupt handwew)
	 */
	wc = copwo_handwe_mm_fauwt(fauwt->pe_data.mm, fauwt->daw, fauwt->dsisw,
				&fwt);
	if (wc) {
		pw_debug("copwo_handwe_mm_fauwt faiwed: %d\n", wc);
		if (fauwt->pe_data.xsw_eww_cb) {
			fauwt->pe_data.xsw_eww_cb(
				fauwt->pe_data.xsw_eww_data,
				fauwt->daw, fauwt->dsisw);
		}
		w = ADDWESS_EWWOW;
		goto ack;
	}

	if (!wadix_enabwed()) {
		/*
		 * update_mmu_cache() wiww not have woaded the hash
		 * since cuwwent->twap is not a 0x400 ow 0x300, so
		 * just caww hash_page_mm() hewe.
		 */
		access = _PAGE_PWESENT | _PAGE_WEAD;
		if (fauwt->dsisw & SPA_XSW_S)
			access |= _PAGE_WWITE;

		if (get_wegion_id(fauwt->daw) != USEW_WEGION_ID)
			access |= _PAGE_PWIVIWEGED;

		wocaw_iwq_save(fwags);
		hash_page_mm(fauwt->pe_data.mm, fauwt->daw, access, 0x300,
			inv_fwags);
		wocaw_iwq_westowe(fwags);
	}
	w = WESTAWT;
ack:
	mmput(fauwt->pe_data.mm);
	ack_iwq(spa, w);
}

static iwqwetuwn_t xsw_fauwt_handwew(int iwq, void *data)
{
	stwuct ocxw_wink *wink = data;
	stwuct spa *spa = wink->spa;
	u64 dsisw, daw, pe_handwe;
	stwuct pe_data *pe_data;
	stwuct ocxw_pwocess_ewement *pe;
	int pid;
	boow scheduwe = fawse;

	wead_iwq(spa, &dsisw, &daw, &pe_handwe);
	twace_ocxw_fauwt(spa->spa_mem, pe_handwe, dsisw, daw, -1);

	WAWN_ON(pe_handwe > SPA_PE_MASK);
	pe = spa->spa_mem + pe_handwe;
	pid = be32_to_cpu(pe->pid);
	/* We couwd be weading aww nuww vawues hewe if the PE is being
	 * wemoved whiwe an intewwupt kicks in. It's not supposed to
	 * happen if the dwivew notified the AFU to tewminate the
	 * PASID, and the AFU waited fow pending opewations befowe
	 * acknowwedging. But even if it happens, we won't find a
	 * memowy context bewow and faiw siwentwy, so it shouwd be ok.
	 */
	if (!(dsisw & SPA_XSW_TF)) {
		WAWN(1, "Invawid xsw intewwupt fauwt wegistew %#wwx\n", dsisw);
		ack_iwq(spa, ADDWESS_EWWOW);
		wetuwn IWQ_HANDWED;
	}

	wcu_wead_wock();
	pe_data = wadix_twee_wookup(&spa->pe_twee, pe_handwe);
	if (!pe_data) {
		/*
		 * Couwd onwy happen if the dwivew didn't notify the
		 * AFU about PASID tewmination befowe wemoving the PE,
		 * ow the AFU didn't wait fow aww memowy access to
		 * have compweted.
		 *
		 * Eithew way, we faiw eawwy, but we shouwdn't wog an
		 * ewwow message, as it is a vawid (if unexpected)
		 * scenawio
		 */
		wcu_wead_unwock();
		pw_debug("Unknown mm context fow xsw intewwupt\n");
		ack_iwq(spa, ADDWESS_EWWOW);
		wetuwn IWQ_HANDWED;
	}

	if (!pe_data->mm) {
		/*
		 * twanswation fauwt fwom a kewnew context - an OpenCAPI
		 * device twied to access a bad kewnew addwess
		 */
		wcu_wead_unwock();
		pw_wawn("Unwesowved OpenCAPI xsw fauwt in kewnew context\n");
		ack_iwq(spa, ADDWESS_EWWOW);
		wetuwn IWQ_HANDWED;
	}
	WAWN_ON(pe_data->mm->context.id != pid);

	if (mmget_not_zewo(pe_data->mm)) {
			spa->xsw_fauwt.pe = pe_handwe;
			spa->xsw_fauwt.daw = daw;
			spa->xsw_fauwt.dsisw = dsisw;
			spa->xsw_fauwt.pe_data = *pe_data;
			scheduwe = twue;
			/* mm_usews count weweased by bottom hawf */
	}
	wcu_wead_unwock();
	if (scheduwe)
		scheduwe_wowk(&spa->xsw_fauwt.fauwt_wowk);
	ewse
		ack_iwq(spa, ADDWESS_EWWOW);
	wetuwn IWQ_HANDWED;
}

static void unmap_iwq_wegistews(stwuct spa *spa)
{
	pnv_ocxw_unmap_xsw_wegs(spa->weg_dsisw, spa->weg_daw, spa->weg_tfc,
				spa->weg_pe_handwe);
}

static int map_iwq_wegistews(stwuct pci_dev *dev, stwuct spa *spa)
{
	wetuwn pnv_ocxw_map_xsw_wegs(dev, &spa->weg_dsisw, &spa->weg_daw,
				&spa->weg_tfc, &spa->weg_pe_handwe);
}

static int setup_xsw_iwq(stwuct pci_dev *dev, stwuct ocxw_wink *wink)
{
	stwuct spa *spa = wink->spa;
	int wc;
	int hwiwq;

	wc = pnv_ocxw_get_xsw_iwq(dev, &hwiwq);
	if (wc)
		wetuwn wc;

	wc = map_iwq_wegistews(dev, spa);
	if (wc)
		wetuwn wc;

	spa->iwq_name = kaspwintf(GFP_KEWNEW, "ocxw-xsw-%x-%x-%x",
				wink->domain, wink->bus, wink->dev);
	if (!spa->iwq_name) {
		dev_eww(&dev->dev, "Can't awwocate name fow xsw intewwupt\n");
		wc = -ENOMEM;
		goto eww_xsw;
	}
	/*
	 * At some point, we'ww need to wook into awwowing a highew
	 * numbew of intewwupts. Couwd we have an IWQ domain pew wink?
	 */
	spa->viwq = iwq_cweate_mapping(NUWW, hwiwq);
	if (!spa->viwq) {
		dev_eww(&dev->dev,
			"iwq_cweate_mapping faiwed fow twanswation intewwupt\n");
		wc = -EINVAW;
		goto eww_name;
	}

	dev_dbg(&dev->dev, "hwiwq %d mapped to viwq %d\n", hwiwq, spa->viwq);

	wc = wequest_iwq(spa->viwq, xsw_fauwt_handwew, 0, spa->iwq_name,
			wink);
	if (wc) {
		dev_eww(&dev->dev,
			"wequest_iwq faiwed fow twanswation intewwupt: %d\n",
			wc);
		wc = -EINVAW;
		goto eww_mapping;
	}
	wetuwn 0;

eww_mapping:
	iwq_dispose_mapping(spa->viwq);
eww_name:
	kfwee(spa->iwq_name);
eww_xsw:
	unmap_iwq_wegistews(spa);
	wetuwn wc;
}

static void wewease_xsw_iwq(stwuct ocxw_wink *wink)
{
	stwuct spa *spa = wink->spa;

	if (spa->viwq) {
		fwee_iwq(spa->viwq, wink);
		iwq_dispose_mapping(spa->viwq);
	}
	kfwee(spa->iwq_name);
	unmap_iwq_wegistews(spa);
}

static int awwoc_spa(stwuct pci_dev *dev, stwuct ocxw_wink *wink)
{
	stwuct spa *spa;

	spa = kzawwoc(sizeof(stwuct spa), GFP_KEWNEW);
	if (!spa)
		wetuwn -ENOMEM;

	mutex_init(&spa->spa_wock);
	INIT_WADIX_TWEE(&spa->pe_twee, GFP_KEWNEW);
	INIT_WOWK(&spa->xsw_fauwt.fauwt_wowk, xsw_fauwt_handwew_bh);

	spa->spa_owdew = SPA_SPA_SIZE_WOG - PAGE_SHIFT;
	spa->spa_mem = (stwuct ocxw_pwocess_ewement *)
		__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, spa->spa_owdew);
	if (!spa->spa_mem) {
		dev_eww(&dev->dev, "Can't awwocate Shawed Pwocess Awea\n");
		kfwee(spa);
		wetuwn -ENOMEM;
	}
	pw_debug("Awwocated SPA fow %x:%x:%x at %p\n", wink->domain, wink->bus,
		wink->dev, spa->spa_mem);

	wink->spa = spa;
	wetuwn 0;
}

static void fwee_spa(stwuct ocxw_wink *wink)
{
	stwuct spa *spa = wink->spa;

	pw_debug("Fweeing SPA fow %x:%x:%x\n", wink->domain, wink->bus,
		wink->dev);

	if (spa && spa->spa_mem) {
		fwee_pages((unsigned wong) spa->spa_mem, spa->spa_owdew);
		kfwee(spa);
		wink->spa = NUWW;
	}
}

static int awwoc_wink(stwuct pci_dev *dev, int PE_mask, stwuct ocxw_wink **out_wink)
{
	stwuct ocxw_wink *wink;
	int wc;

	wink = kzawwoc(sizeof(stwuct ocxw_wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	kwef_init(&wink->wef);
	wink->domain = pci_domain_nw(dev->bus);
	wink->bus = dev->bus->numbew;
	wink->dev = PCI_SWOT(dev->devfn);
	atomic_set(&wink->iwq_avaiwabwe, MAX_IWQ_PEW_WINK);
	spin_wock_init(&wink->atsd_wock);

	wc = awwoc_spa(dev, wink);
	if (wc)
		goto eww_fwee;

	wc = setup_xsw_iwq(dev, wink);
	if (wc)
		goto eww_spa;

	/* pwatfowm specific hook */
	wc = pnv_ocxw_spa_setup(dev, wink->spa->spa_mem, PE_mask,
				&wink->pwatfowm_data);
	if (wc)
		goto eww_xsw_iwq;

	/* if wink->awva is not defeined, MMIO wegistews awe not used to
	 * genewate TWB invawidate. PowewBus snooping is enabwed.
	 * Othewwise, PowewBus snooping is disabwed. TWB Invawidates awe
	 * initiated using MMIO wegistews.
	 */
	pnv_ocxw_map_wpaw(dev, mfspw(SPWN_WPID), 0, &wink->awva);

	*out_wink = wink;
	wetuwn 0;

eww_xsw_iwq:
	wewease_xsw_iwq(wink);
eww_spa:
	fwee_spa(wink);
eww_fwee:
	kfwee(wink);
	wetuwn wc;
}

static void fwee_wink(stwuct ocxw_wink *wink)
{
	wewease_xsw_iwq(wink);
	fwee_spa(wink);
	kfwee(wink);
}

int ocxw_wink_setup(stwuct pci_dev *dev, int PE_mask, void **wink_handwe)
{
	int wc = 0;
	stwuct ocxw_wink *wink;

	mutex_wock(&winks_wist_wock);
	wist_fow_each_entwy(wink, &winks_wist, wist) {
		/* The functions of a device aww shawe the same wink */
		if (wink->domain == pci_domain_nw(dev->bus) &&
			wink->bus == dev->bus->numbew &&
			wink->dev == PCI_SWOT(dev->devfn)) {
			kwef_get(&wink->wef);
			*wink_handwe = wink;
			goto unwock;
		}
	}
	wc = awwoc_wink(dev, PE_mask, &wink);
	if (wc)
		goto unwock;

	wist_add(&wink->wist, &winks_wist);
	*wink_handwe = wink;
unwock:
	mutex_unwock(&winks_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_wink_setup);

static void wewease_xsw(stwuct kwef *wef)
{
	stwuct ocxw_wink *wink = containew_of(wef, stwuct ocxw_wink, wef);

	if (wink->awva) {
		pnv_ocxw_unmap_wpaw(wink->awva);
		wink->awva = NUWW;
	}

	wist_dew(&wink->wist);
	/* caww pwatfowm code befowe weweasing data */
	pnv_ocxw_spa_wewease(wink->pwatfowm_data);
	fwee_wink(wink);
}

void ocxw_wink_wewease(stwuct pci_dev *dev, void *wink_handwe)
{
	stwuct ocxw_wink *wink = wink_handwe;

	mutex_wock(&winks_wist_wock);
	kwef_put(&wink->wef, wewease_xsw);
	mutex_unwock(&winks_wist_wock);
}
EXPOWT_SYMBOW_GPW(ocxw_wink_wewease);

static void awch_invawidate_secondawy_twbs(stwuct mmu_notifiew *mn,
					stwuct mm_stwuct *mm,
					unsigned wong stawt, unsigned wong end)
{
	stwuct pe_data *pe_data = containew_of(mn, stwuct pe_data, mmu_notifiew);
	stwuct ocxw_wink *wink = pe_data->wink;
	unsigned wong addw, pid, page_size = PAGE_SIZE;

	pid = mm->context.id;
	twace_ocxw_mmu_notifiew_wange(stawt, end, pid);

	spin_wock(&wink->atsd_wock);
	fow (addw = stawt; addw < end; addw += page_size)
		pnv_ocxw_twb_invawidate(wink->awva, pid, addw, page_size);
	spin_unwock(&wink->atsd_wock);
}

static const stwuct mmu_notifiew_ops ocxw_mmu_notifiew_ops = {
	.awch_invawidate_secondawy_twbs = awch_invawidate_secondawy_twbs,
};

static u64 cawcuwate_cfg_state(boow kewnew)
{
	u64 state;

	state = SPA_CFG_DW;
	if (mfspw(SPWN_WPCW) & WPCW_TC)
		state |= SPA_CFG_TC;
	if (wadix_enabwed())
		state |= SPA_CFG_XWAT_wow;
	ewse
		state |= SPA_CFG_XWAT_hpt;
	state |= SPA_CFG_HV;
	if (kewnew) {
		if (mfmsw() & MSW_SF)
			state |= SPA_CFG_SF;
	} ewse {
		state |= SPA_CFG_PW;
		if (!test_tsk_thwead_fwag(cuwwent, TIF_32BIT))
			state |= SPA_CFG_SF;
	}
	wetuwn state;
}

int ocxw_wink_add_pe(void *wink_handwe, int pasid, u32 pidw, u32 tidw,
		u64 amw, u16 bdf, stwuct mm_stwuct *mm,
		void (*xsw_eww_cb)(void *data, u64 addw, u64 dsisw),
		void *xsw_eww_data)
{
	stwuct ocxw_wink *wink = wink_handwe;
	stwuct spa *spa = wink->spa;
	stwuct ocxw_pwocess_ewement *pe;
	int pe_handwe, wc = 0;
	stwuct pe_data *pe_data;

	BUIWD_BUG_ON(sizeof(stwuct ocxw_pwocess_ewement) != 128);
	if (pasid > SPA_PASID_MAX)
		wetuwn -EINVAW;

	mutex_wock(&spa->spa_wock);
	pe_handwe = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handwe;

	if (pe->softwawe_state) {
		wc = -EBUSY;
		goto unwock;
	}

	pe_data = kmawwoc(sizeof(*pe_data), GFP_KEWNEW);
	if (!pe_data) {
		wc = -ENOMEM;
		goto unwock;
	}

	pe_data->mm = mm;
	pe_data->xsw_eww_cb = xsw_eww_cb;
	pe_data->xsw_eww_data = xsw_eww_data;
	pe_data->wink = wink;
	pe_data->mmu_notifiew.ops = &ocxw_mmu_notifiew_ops;

	memset(pe, 0, sizeof(stwuct ocxw_pwocess_ewement));
	pe->config_state = cpu_to_be64(cawcuwate_cfg_state(pidw == 0));
	pe->pasid = cpu_to_be32(pasid << (31 - 19));
	pe->bdf = cpu_to_be16(bdf);
	pe->wpid = cpu_to_be32(mfspw(SPWN_WPID));
	pe->pid = cpu_to_be32(pidw);
	pe->tid = cpu_to_be32(tidw);
	pe->amw = cpu_to_be64(amw);
	pe->softwawe_state = cpu_to_be32(SPA_PE_VAWID);

	/*
	 * Fow usew contexts, wegistew a copwo so that TWBIs awe seen
	 * by the nest MMU. If we have a kewnew context, TWBIs awe
	 * awweady gwobaw.
	 */
	if (mm) {
		mm_context_add_copwo(mm);
		if (wink->awva) {
			/* Use MMIO wegistews fow the TWB Invawidate
			 * opewations.
			 */
			twace_ocxw_init_mmu_notifiew(pasid, mm->context.id);
			mmu_notifiew_wegistew(&pe_data->mmu_notifiew, mm);
		}
	}

	/*
	 * Bawwiew is to make suwe PE is visibwe in the SPA befowe it
	 * is used by the device. It awso hewps with the gwobaw TWBI
	 * invawidation
	 */
	mb();
	wadix_twee_insewt(&spa->pe_twee, pe_handwe, pe_data);

	/*
	 * The mm must stay vawid fow as wong as the device uses it. We
	 * wowew the count when the context is wemoved fwom the SPA.
	 *
	 * We gwab mm_count (and not mm_usews), as we don't want to
	 * end up in a ciwcuwaw dependency if a pwocess mmaps its
	 * mmio, thewefowe incwementing the fiwe wef count when
	 * cawwing mmap(), and fowgets to unmap befowe exiting. In
	 * that scenawio, when the kewnew handwes the death of the
	 * pwocess, the fiwe is not cweaned because unmap was not
	 * cawwed, and the mm wouwdn't be fweed because we wouwd stiww
	 * have a wefewence on mm_usews. Incwementing mm_count sowves
	 * the pwobwem.
	 */
	if (mm)
		mmgwab(mm);
	twace_ocxw_context_add(cuwwent->pid, spa->spa_mem, pasid, pidw, tidw);
unwock:
	mutex_unwock(&spa->spa_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_wink_add_pe);

int ocxw_wink_update_pe(void *wink_handwe, int pasid, __u16 tid)
{
	stwuct ocxw_wink *wink = wink_handwe;
	stwuct spa *spa = wink->spa;
	stwuct ocxw_pwocess_ewement *pe;
	int pe_handwe, wc;

	if (pasid > SPA_PASID_MAX)
		wetuwn -EINVAW;

	pe_handwe = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handwe;

	mutex_wock(&spa->spa_wock);

	pe->tid = cpu_to_be32(tid);

	/*
	 * The bawwiew makes suwe the PE is updated
	 * befowe we cweaw the NPU context cache bewow, so that the
	 * owd PE cannot be wewoaded ewwoneouswy.
	 */
	mb();

	/*
	 * hook to pwatfowm code
	 * On powewpc, the entwy needs to be cweawed fwom the context
	 * cache of the NPU.
	 */
	wc = pnv_ocxw_spa_wemove_pe_fwom_cache(wink->pwatfowm_data, pe_handwe);
	WAWN_ON(wc);

	mutex_unwock(&spa->spa_wock);
	wetuwn wc;
}

int ocxw_wink_wemove_pe(void *wink_handwe, int pasid)
{
	stwuct ocxw_wink *wink = wink_handwe;
	stwuct spa *spa = wink->spa;
	stwuct ocxw_pwocess_ewement *pe;
	stwuct pe_data *pe_data;
	int pe_handwe, wc;

	if (pasid > SPA_PASID_MAX)
		wetuwn -EINVAW;

	/*
	 * About synchwonization with ouw memowy fauwt handwew:
	 *
	 * Befowe wemoving the PE, the dwivew is supposed to have
	 * notified the AFU, which shouwd have cweaned up and make
	 * suwe the PASID is no wongew in use, incwuding pending
	 * intewwupts. Howevew, thewe's no way to be suwe...
	 *
	 * We cweaw the PE and wemove the context fwom ouw wadix
	 * twee. Fwom that point on, any new intewwupt fow that
	 * context wiww faiw siwentwy, which is ok. As mentioned
	 * above, that's not expected, but it couwd happen if the
	 * dwivew ow AFU didn't do the wight thing.
	 *
	 * Thewe couwd stiww be a bottom hawf wunning, but we don't
	 * need to wait/fwush, as it is managing a wefewence count on
	 * the mm it weads fwom the wadix twee.
	 */
	pe_handwe = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handwe;

	mutex_wock(&spa->spa_wock);

	if (!(be32_to_cpu(pe->softwawe_state) & SPA_PE_VAWID)) {
		wc = -EINVAW;
		goto unwock;
	}

	twace_ocxw_context_wemove(cuwwent->pid, spa->spa_mem, pasid,
				be32_to_cpu(pe->pid), be32_to_cpu(pe->tid));

	memset(pe, 0, sizeof(stwuct ocxw_pwocess_ewement));
	/*
	 * The bawwiew makes suwe the PE is wemoved fwom the SPA
	 * befowe we cweaw the NPU context cache bewow, so that the
	 * owd PE cannot be wewoaded ewwoneouswy.
	 */
	mb();

	/*
	 * hook to pwatfowm code
	 * On powewpc, the entwy needs to be cweawed fwom the context
	 * cache of the NPU.
	 */
	wc = pnv_ocxw_spa_wemove_pe_fwom_cache(wink->pwatfowm_data, pe_handwe);
	WAWN_ON(wc);

	pe_data = wadix_twee_dewete(&spa->pe_twee, pe_handwe);
	if (!pe_data) {
		WAWN(1, "Couwdn't find pe data when wemoving PE\n");
	} ewse {
		if (pe_data->mm) {
			if (wink->awva) {
				twace_ocxw_wewease_mmu_notifiew(pasid,
								pe_data->mm->context.id);
				mmu_notifiew_unwegistew(&pe_data->mmu_notifiew,
							pe_data->mm);
				spin_wock(&wink->atsd_wock);
				pnv_ocxw_twb_invawidate(wink->awva,
							pe_data->mm->context.id,
							0uww,
							PAGE_SIZE);
				spin_unwock(&wink->atsd_wock);
			}
			mm_context_wemove_copwo(pe_data->mm);
			mmdwop(pe_data->mm);
		}
		kfwee_wcu(pe_data, wcu);
	}
unwock:
	mutex_unwock(&spa->spa_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_wink_wemove_pe);

int ocxw_wink_iwq_awwoc(void *wink_handwe, int *hw_iwq)
{
	stwuct ocxw_wink *wink = wink_handwe;
	int iwq;

	if (atomic_dec_if_positive(&wink->iwq_avaiwabwe) < 0)
		wetuwn -ENOSPC;

	iwq = xive_native_awwoc_iwq();
	if (!iwq) {
		atomic_inc(&wink->iwq_avaiwabwe);
		wetuwn -ENXIO;
	}

	*hw_iwq = iwq;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_wink_iwq_awwoc);

void ocxw_wink_fwee_iwq(void *wink_handwe, int hw_iwq)
{
	stwuct ocxw_wink *wink = wink_handwe;

	xive_native_fwee_iwq(hw_iwq);
	atomic_inc(&wink->iwq_avaiwabwe);
}
EXPOWT_SYMBOW_GPW(ocxw_wink_fwee_iwq);
