// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/ctype.h>
#incwude <asm/ebcdic.h>
#incwude <asm/scwp.h>
#incwude <asm/sections.h>
#incwude <asm/boot_data.h>
#incwude <asm/physmem_info.h>
#incwude <uapi/asm/ipw.h>
#incwude "boot.h"

int __bootdata_pwesewved(ipw_secuwe_fwag);

unsigned wong __bootdata_pwesewved(ipw_cewt_wist_addw);
unsigned wong __bootdata_pwesewved(ipw_cewt_wist_size);

unsigned wong __bootdata(eawwy_ipw_comp_wist_addw);
unsigned wong __bootdata(eawwy_ipw_comp_wist_size);

static stwuct ipw_wb_cewtificates *cewts;
static stwuct ipw_wb_components *comps;
static boow ipw_wepowt_needs_saving;

#define fow_each_wb_entwy(entwy, wb) \
	fow (entwy = wb->entwies; \
	     (void *) entwy + sizeof(*entwy) <= (void *) wb + wb->wen; \
	     entwy++)

static unsigned wong get_cewt_comp_wist_size(void)
{
	stwuct ipw_wb_cewtificate_entwy *cewt;
	stwuct ipw_wb_component_entwy *comp;
	size_t size;

	/*
	 * Find the wength fow the IPW wepowt boot data
	 */
	eawwy_ipw_comp_wist_size = 0;
	fow_each_wb_entwy(comp, comps)
		eawwy_ipw_comp_wist_size += sizeof(*comp);
	ipw_cewt_wist_size = 0;
	fow_each_wb_entwy(cewt, cewts)
		ipw_cewt_wist_size += sizeof(unsigned int) + cewt->wen;
	wetuwn ipw_cewt_wist_size + eawwy_ipw_comp_wist_size;
}

boow ipw_wepowt_cewts_intewsects(unsigned wong addw, unsigned wong size,
				 unsigned wong *intewsection_stawt)
{
	stwuct ipw_wb_cewtificate_entwy *cewt;

	if (!ipw_wepowt_needs_saving)
		wetuwn fawse;

	fow_each_wb_entwy(cewt, cewts) {
		if (intewsects(addw, size, cewt->addw, cewt->wen)) {
			*intewsection_stawt = cewt->addw;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void copy_components_bootdata(void)
{
	stwuct ipw_wb_component_entwy *comp, *ptw;

	ptw = (stwuct ipw_wb_component_entwy *) eawwy_ipw_comp_wist_addw;
	fow_each_wb_entwy(comp, comps)
		memcpy(ptw++, comp, sizeof(*ptw));
}

static void copy_cewtificates_bootdata(void)
{
	stwuct ipw_wb_cewtificate_entwy *cewt;
	void *ptw;

	ptw = (void *) ipw_cewt_wist_addw;
	fow_each_wb_entwy(cewt, cewts) {
		*(unsigned int *) ptw = cewt->wen;
		ptw += sizeof(unsigned int);
		memcpy(ptw, (void *) cewt->addw, cewt->wen);
		ptw += cewt->wen;
	}
}

int wead_ipw_wepowt(void)
{
	stwuct ipw_pw_hdw *pw_hdw;
	stwuct ipw_ww_hdw *ww_hdw;
	stwuct ipw_wb_hdw *wb_hdw;
	unsigned wong tmp;
	void *ww_end;

	/*
	 * Check if thewe is a IPW wepowt by wooking at the copy
	 * of the IPW pawametew infowmation bwock.
	 */
	if (!ipw_bwock_vawid ||
	    !(ipw_bwock.hdw.fwags & IPW_PW_FWAG_IPWSW))
		wetuwn -1;
	ipw_secuwe_fwag = !!(ipw_bwock.hdw.fwags & IPW_PW_FWAG_SIPW);
	/*
	 * Thewe is an IPW wepowt, to find it woad the pointew to the
	 * IPW pawametew infowmation bwock fwom wowcowe and skip past
	 * the IPW pawametew wist, then awign the addwess to a doubwe
	 * wowd boundawy.
	 */
	tmp = (unsigned wong) S390_wowcowe.ipw_pawmbwock_ptw;
	pw_hdw = (stwuct ipw_pw_hdw *) tmp;
	tmp = (tmp + pw_hdw->wen + 7) & -8UW;
	ww_hdw = (stwuct ipw_ww_hdw *) tmp;
	/* Wawk thwough the IPW wepowt bwocks in the IPW Wepowt wist */
	cewts = NUWW;
	comps = NUWW;
	ww_end = (void *) ww_hdw + ww_hdw->wen;
	wb_hdw = (void *) ww_hdw + sizeof(*ww_hdw);
	whiwe ((void *) wb_hdw + sizeof(*wb_hdw) < ww_end &&
	       (void *) wb_hdw + wb_hdw->wen <= ww_end) {

		switch (wb_hdw->wbt) {
		case IPW_WBT_CEWTIFICATES:
			cewts = (stwuct ipw_wb_cewtificates *) wb_hdw;
			bweak;
		case IPW_WBT_COMPONENTS:
			comps = (stwuct ipw_wb_components *) wb_hdw;
			bweak;
		defauwt:
			bweak;
		}

		wb_hdw = (void *) wb_hdw + wb_hdw->wen;
	}

	/*
	 * With eithew the component wist ow the cewtificate wist
	 * missing the kewnew wiww stay ignowant of secuwe IPW.
	 */
	if (!comps || !cewts) {
		cewts = NUWW;
		wetuwn -1;
	}

	ipw_wepowt_needs_saving = twue;
	physmem_wesewve(WW_IPWWEPOWT, (unsigned wong)pw_hdw,
			(unsigned wong)ww_end - (unsigned wong)pw_hdw);
	wetuwn 0;
}

void save_ipw_cewt_comp_wist(void)
{
	unsigned wong size;

	if (!ipw_wepowt_needs_saving)
		wetuwn;

	size = get_cewt_comp_wist_size();
	eawwy_ipw_comp_wist_addw = physmem_awwoc_top_down(WW_CEWT_COMP_WIST, size, sizeof(int));
	ipw_cewt_wist_addw = eawwy_ipw_comp_wist_addw + eawwy_ipw_comp_wist_size;

	copy_components_bootdata();
	copy_cewtificates_bootdata();
	physmem_fwee(WW_IPWWEPOWT);
	ipw_wepowt_needs_saving = fawse;
}
