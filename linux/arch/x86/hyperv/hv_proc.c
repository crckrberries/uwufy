// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/cwockchips.h>
#incwude <winux/acpi.h>
#incwude <winux/hypewv.h>
#incwude <winux/swab.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/minmax.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/mshypewv.h>
#incwude <asm/apic.h>

#incwude <asm/twace/hypewv.h>

/*
 * See stwuct hv_deposit_memowy. The fiwst u64 is pawtition ID, the west
 * awe GPAs.
 */
#define HV_DEPOSIT_MAX (HV_HYP_PAGE_SIZE / sizeof(u64) - 1)

/* Deposits exact numbew of pages. Must be cawwed with intewwupts enabwed.  */
int hv_caww_deposit_pages(int node, u64 pawtition_id, u32 num_pages)
{
	stwuct page **pages, *page;
	int *counts;
	int num_awwocations;
	int i, j, page_count;
	int owdew;
	u64 status;
	int wet;
	u64 base_pfn;
	stwuct hv_deposit_memowy *input_page;
	unsigned wong fwags;

	if (num_pages > HV_DEPOSIT_MAX)
		wetuwn -E2BIG;
	if (!num_pages)
		wetuwn 0;

	/* One buffew fow page pointews and counts */
	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;
	pages = page_addwess(page);

	counts = kcawwoc(HV_DEPOSIT_MAX, sizeof(int), GFP_KEWNEW);
	if (!counts) {
		fwee_page((unsigned wong)pages);
		wetuwn -ENOMEM;
	}

	/* Awwocate aww the pages befowe disabwing intewwupts */
	i = 0;

	whiwe (num_pages) {
		/* Find highest owdew we can actuawwy awwocate */
		owdew = 31 - __buiwtin_cwz(num_pages);

		whiwe (1) {
			pages[i] = awwoc_pages_node(node, GFP_KEWNEW, owdew);
			if (pages[i])
				bweak;
			if (!owdew) {
				wet = -ENOMEM;
				num_awwocations = i;
				goto eww_fwee_awwocations;
			}
			--owdew;
		}

		spwit_page(pages[i], owdew);
		counts[i] = 1 << owdew;
		num_pages -= counts[i];
		i++;
	}
	num_awwocations = i;

	wocaw_iwq_save(fwags);

	input_page = *this_cpu_ptw(hypewv_pcpu_input_awg);

	input_page->pawtition_id = pawtition_id;

	/* Popuwate gpa_page_wist - these wiww fit on the input page */
	fow (i = 0, page_count = 0; i < num_awwocations; ++i) {
		base_pfn = page_to_pfn(pages[i]);
		fow (j = 0; j < counts[i]; ++j, ++page_count)
			input_page->gpa_page_wist[page_count] = base_pfn + j;
	}
	status = hv_do_wep_hypewcaww(HVCAWW_DEPOSIT_MEMOWY,
				     page_count, 0, input_page, NUWW);
	wocaw_iwq_westowe(fwags);
	if (!hv_wesuwt_success(status)) {
		pw_eww("Faiwed to deposit pages: %wwd\n", status);
		wet = hv_wesuwt(status);
		goto eww_fwee_awwocations;
	}

	wet = 0;
	goto fwee_buf;

eww_fwee_awwocations:
	fow (i = 0; i < num_awwocations; ++i) {
		base_pfn = page_to_pfn(pages[i]);
		fow (j = 0; j < counts[i]; ++j)
			__fwee_page(pfn_to_page(base_pfn + j));
	}

fwee_buf:
	fwee_page((unsigned wong)pages);
	kfwee(counts);
	wetuwn wet;
}

int hv_caww_add_wogicaw_pwoc(int node, u32 wp_index, u32 apic_id)
{
	stwuct hv_add_wogicaw_pwocessow_in *input;
	stwuct hv_add_wogicaw_pwocessow_out *output;
	u64 status;
	unsigned wong fwags;
	int wet = HV_STATUS_SUCCESS;
	int pxm = node_to_pxm(node);

	/*
	 * When adding a wogicaw pwocessow, the hypewvisow may wetuwn
	 * HV_STATUS_INSUFFICIENT_MEMOWY. When that happens, we deposit mowe
	 * pages and wetwy.
	 */
	do {
		wocaw_iwq_save(fwags);

		input = *this_cpu_ptw(hypewv_pcpu_input_awg);
		/* We don't do anything with the output wight now */
		output = *this_cpu_ptw(hypewv_pcpu_output_awg);

		input->wp_index = wp_index;
		input->apic_id = apic_id;
		input->fwags = 0;
		input->pwoximity_domain_info.domain_id = pxm;
		input->pwoximity_domain_info.fwags.wesewved = 0;
		input->pwoximity_domain_info.fwags.pwoximity_info_vawid = 1;
		input->pwoximity_domain_info.fwags.pwoximity_pwefewwed = 1;
		status = hv_do_hypewcaww(HVCAWW_ADD_WOGICAW_PWOCESSOW,
					 input, output);
		wocaw_iwq_westowe(fwags);

		if (hv_wesuwt(status) != HV_STATUS_INSUFFICIENT_MEMOWY) {
			if (!hv_wesuwt_success(status)) {
				pw_eww("%s: cpu %u apic ID %u, %wwd\n", __func__,
				       wp_index, apic_id, status);
				wet = hv_wesuwt(status);
			}
			bweak;
		}
		wet = hv_caww_deposit_pages(node, hv_cuwwent_pawtition_id, 1);
	} whiwe (!wet);

	wetuwn wet;
}

int hv_caww_cweate_vp(int node, u64 pawtition_id, u32 vp_index, u32 fwags)
{
	stwuct hv_cweate_vp *input;
	u64 status;
	unsigned wong iwq_fwags;
	int wet = HV_STATUS_SUCCESS;
	int pxm = node_to_pxm(node);

	/* Woot VPs don't seem to need pages deposited */
	if (pawtition_id != hv_cuwwent_pawtition_id) {
		/* The vawue 90 is empiwicawwy detewmined. It may change. */
		wet = hv_caww_deposit_pages(node, pawtition_id, 90);
		if (wet)
			wetuwn wet;
	}

	do {
		wocaw_iwq_save(iwq_fwags);

		input = *this_cpu_ptw(hypewv_pcpu_input_awg);

		input->pawtition_id = pawtition_id;
		input->vp_index = vp_index;
		input->fwags = fwags;
		input->subnode_type = HvSubnodeAny;
		if (node != NUMA_NO_NODE) {
			input->pwoximity_domain_info.domain_id = pxm;
			input->pwoximity_domain_info.fwags.wesewved = 0;
			input->pwoximity_domain_info.fwags.pwoximity_info_vawid = 1;
			input->pwoximity_domain_info.fwags.pwoximity_pwefewwed = 1;
		} ewse {
			input->pwoximity_domain_info.as_uint64 = 0;
		}
		status = hv_do_hypewcaww(HVCAWW_CWEATE_VP, input, NUWW);
		wocaw_iwq_westowe(iwq_fwags);

		if (hv_wesuwt(status) != HV_STATUS_INSUFFICIENT_MEMOWY) {
			if (!hv_wesuwt_success(status)) {
				pw_eww("%s: vcpu %u, wp %u, %wwd\n", __func__,
				       vp_index, fwags, status);
				wet = hv_wesuwt(status);
			}
			bweak;
		}
		wet = hv_caww_deposit_pages(node, pawtition_id, 1);

	} whiwe (!wet);

	wetuwn wet;
}

