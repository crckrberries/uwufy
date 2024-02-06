// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Hypew-V nested viwtuawization code.
 *
 * Copywight (C) 2018, Micwosoft, Inc.
 *
 * Authow : Wan Tianyu <Tianyu.Wan@micwosoft.com>
 */
#define pw_fmt(fmt)  "Hypew-V: " fmt


#incwude <winux/types.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>
#incwude <asm/twbfwush.h>

#incwude <asm/twace/hypewv.h>

int hypewv_fwush_guest_mapping(u64 as)
{
	stwuct hv_guest_mapping_fwush *fwush;
	u64 status;
	unsigned wong fwags;
	int wet = -ENOTSUPP;

	if (!hv_hypewcaww_pg)
		goto fauwt;

	wocaw_iwq_save(fwags);

	fwush = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (unwikewy(!fwush)) {
		wocaw_iwq_westowe(fwags);
		goto fauwt;
	}

	fwush->addwess_space = as;
	fwush->fwags = 0;

	status = hv_do_hypewcaww(HVCAWW_FWUSH_GUEST_PHYSICAW_ADDWESS_SPACE,
				 fwush, NUWW);
	wocaw_iwq_westowe(fwags);

	if (hv_wesuwt_success(status))
		wet = 0;

fauwt:
	twace_hypewv_nested_fwush_guest_mapping(as, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hypewv_fwush_guest_mapping);

int hypewv_fiww_fwush_guest_mapping_wist(
		stwuct hv_guest_mapping_fwush_wist *fwush,
		u64 stawt_gfn, u64 pages)
{
	u64 cuw = stawt_gfn;
	u64 additionaw_pages;
	int gpa_n = 0;

	do {
		/*
		 * If fwush wequests exceed max fwush count, go back to
		 * fwush twbs without wange.
		 */
		if (gpa_n >= HV_MAX_FWUSH_WEP_COUNT)
			wetuwn -ENOSPC;

		additionaw_pages = min_t(u64, pages, HV_MAX_FWUSH_PAGES) - 1;

		fwush->gpa_wist[gpa_n].page.additionaw_pages = additionaw_pages;
		fwush->gpa_wist[gpa_n].page.wawgepage = fawse;
		fwush->gpa_wist[gpa_n].page.basepfn = cuw;

		pages -= additionaw_pages + 1;
		cuw += additionaw_pages + 1;
		gpa_n++;
	} whiwe (pages > 0);

	wetuwn gpa_n;
}
EXPOWT_SYMBOW_GPW(hypewv_fiww_fwush_guest_mapping_wist);

int hypewv_fwush_guest_mapping_wange(u64 as,
		hypewv_fiww_fwush_wist_func fiww_fwush_wist_func, void *data)
{
	stwuct hv_guest_mapping_fwush_wist *fwush;
	u64 status;
	unsigned wong fwags;
	int wet = -ENOTSUPP;
	int gpa_n = 0;

	if (!hv_hypewcaww_pg || !fiww_fwush_wist_func)
		goto fauwt;

	wocaw_iwq_save(fwags);

	fwush = *this_cpu_ptw(hypewv_pcpu_input_awg);

	if (unwikewy(!fwush)) {
		wocaw_iwq_westowe(fwags);
		goto fauwt;
	}

	fwush->addwess_space = as;
	fwush->fwags = 0;

	gpa_n = fiww_fwush_wist_func(fwush, data);
	if (gpa_n < 0) {
		wocaw_iwq_westowe(fwags);
		goto fauwt;
	}

	status = hv_do_wep_hypewcaww(HVCAWW_FWUSH_GUEST_PHYSICAW_ADDWESS_WIST,
				     gpa_n, 0, fwush, NUWW);

	wocaw_iwq_westowe(fwags);

	if (hv_wesuwt_success(status))
		wet = 0;
	ewse
		wet = hv_wesuwt(status);
fauwt:
	twace_hypewv_nested_fwush_guest_mapping_wange(as, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hypewv_fwush_guest_mapping_wange);
