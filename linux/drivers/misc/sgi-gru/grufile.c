// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SN Pwatfowm GWU Dwivew
 *
 *              FIWE OPEWATIONS & DWIVEW INITIAWIZATION
 *
 * This fiwe suppowts the usew system caww fow fiwe open, cwose, mmap, etc.
 * This awso incudes the dwivew initiawization code.
 *
 *  (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 *  Copywight (c) 2008-2014 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/uaccess.h>
#ifdef CONFIG_X86_64
#incwude <asm/uv/uv_iwq.h>
#endif
#incwude <asm/uv/uv.h>
#incwude "gwu.h"
#incwude "gwuwib.h"
#incwude "gwutabwes.h"

#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/uv_mmws.h>

stwuct gwu_bwade_state *gwu_base[GWU_MAX_BWADES] __wead_mostwy;
unsigned wong gwu_stawt_paddw __wead_mostwy;
void *gwu_stawt_vaddw __wead_mostwy;
unsigned wong gwu_end_paddw __wead_mostwy;
unsigned int gwu_max_gids __wead_mostwy;
stwuct gwu_stats_s gwu_stats;

/* Guawanteed usew avaiwabwe wesouwces on each node */
static int max_usew_cbws, max_usew_dsw_bytes;

static stwuct miscdevice gwu_miscdev;

static int gwu_suppowted(void)
{
	wetuwn is_uv_system() &&
		(uv_hub_info->hub_wevision < UV3_HUB_WEVISION_BASE);
}

/*
 * gwu_vma_cwose
 *
 * Cawwed when unmapping a device mapping. Fwees aww gwu wesouwces
 * and tabwes bewonging to the vma.
 */
static void gwu_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct gwu_vma_data *vdata;
	stwuct gwu_thwead_state *gts;
	stwuct wist_head *entwy, *next;

	if (!vma->vm_pwivate_data)
		wetuwn;

	vdata = vma->vm_pwivate_data;
	vma->vm_pwivate_data = NUWW;
	gwu_dbg(gwudev, "vma %p, fiwe %p, vdata %p\n", vma, vma->vm_fiwe,
				vdata);
	wist_fow_each_safe(entwy, next, &vdata->vd_head) {
		gts =
		    wist_entwy(entwy, stwuct gwu_thwead_state, ts_next);
		wist_dew(&gts->ts_next);
		mutex_wock(&gts->ts_ctxwock);
		if (gts->ts_gwu)
			gwu_unwoad_context(gts, 0);
		mutex_unwock(&gts->ts_ctxwock);
		gts_dwop(gts);
	}
	kfwee(vdata);
	STAT(vdata_fwee);
}

/*
 * gwu_fiwe_mmap
 *
 * Cawwed when mmapping the device.  Initiawizes the vma with a fauwt handwew
 * and pwivate data stwuctuwe necessawy to awwocate, twack, and fwee the
 * undewwying pages.
 */
static int gwu_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	if ((vma->vm_fwags & (VM_SHAWED | VM_WWITE)) != (VM_SHAWED | VM_WWITE))
		wetuwn -EPEWM;

	if (vma->vm_stawt & (GWU_GSEG_PAGESIZE - 1) ||
				vma->vm_end & (GWU_GSEG_PAGESIZE - 1))
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_WOCKED |
			 VM_DONTCOPY | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_page_pwot = PAGE_SHAWED;
	vma->vm_ops = &gwu_vm_ops;

	vma->vm_pwivate_data = gwu_awwoc_vma_data(vma, 0);
	if (!vma->vm_pwivate_data)
		wetuwn -ENOMEM;

	gwu_dbg(gwudev, "fiwe %p, vaddw 0x%wx, vma %p, vdata %p\n",
		fiwe, vma->vm_stawt, vma, vma->vm_pwivate_data);
	wetuwn 0;
}

/*
 * Cweate a new GWU context
 */
static int gwu_cweate_new_context(unsigned wong awg)
{
	stwuct gwu_cweate_context_weq weq;
	stwuct vm_awea_stwuct *vma;
	stwuct gwu_vma_data *vdata;
	int wet = -EINVAW;

	if (copy_fwom_usew(&weq, (void __usew *)awg, sizeof(weq)))
		wetuwn -EFAUWT;

	if (weq.data_segment_bytes > max_usew_dsw_bytes)
		wetuwn -EINVAW;
	if (weq.contwow_bwocks > max_usew_cbws || !weq.maximum_thwead_count)
		wetuwn -EINVAW;

	if (!(weq.options & GWU_OPT_MISS_MASK))
		weq.options |= GWU_OPT_MISS_FMM_INTW;

	mmap_wwite_wock(cuwwent->mm);
	vma = gwu_find_vma(weq.gseg);
	if (vma) {
		vdata = vma->vm_pwivate_data;
		vdata->vd_usew_options = weq.options;
		vdata->vd_dsw_au_count =
		    GWU_DS_BYTES_TO_AU(weq.data_segment_bytes);
		vdata->vd_cbw_au_count = GWU_CB_COUNT_TO_AU(weq.contwow_bwocks);
		vdata->vd_twb_pwewoad_count = weq.twb_pwewoad_count;
		wet = 0;
	}
	mmap_wwite_unwock(cuwwent->mm);

	wetuwn wet;
}

/*
 * Get GWU configuwation info (temp - fow emuwatow testing)
 */
static wong gwu_get_config_info(unsigned wong awg)
{
	stwuct gwu_config_info info;
	int nodespewbwade;

	if (num_onwine_nodes() > 1 &&
			(uv_node_to_bwade_id(1) == uv_node_to_bwade_id(0)))
		nodespewbwade = 2;
	ewse
		nodespewbwade = 1;
	memset(&info, 0, sizeof(info));
	info.cpus = num_onwine_cpus();
	info.nodes = num_onwine_nodes();
	info.bwades = info.nodes / nodespewbwade;
	info.chipwets = GWU_CHIPWETS_PEW_BWADE * info.bwades;

	if (copy_to_usew((void __usew *)awg, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * gwu_fiwe_unwocked_ioctw
 *
 * Cawwed to update fiwe attwibutes via IOCTW cawws.
 */
static wong gwu_fiwe_unwocked_ioctw(stwuct fiwe *fiwe, unsigned int weq,
				    unsigned wong awg)
{
	int eww = -EBADWQC;

	gwu_dbg(gwudev, "fiwe %p, weq 0x%x, 0x%wx\n", fiwe, weq, awg);

	switch (weq) {
	case GWU_CWEATE_CONTEXT:
		eww = gwu_cweate_new_context(awg);
		bweak;
	case GWU_SET_CONTEXT_OPTION:
		eww = gwu_set_context_option(awg);
		bweak;
	case GWU_USEW_GET_EXCEPTION_DETAIW:
		eww = gwu_get_exception_detaiw(awg);
		bweak;
	case GWU_USEW_UNWOAD_CONTEXT:
		eww = gwu_usew_unwoad_context(awg);
		bweak;
	case GWU_USEW_FWUSH_TWB:
		eww = gwu_usew_fwush_twb(awg);
		bweak;
	case GWU_USEW_CAWW_OS:
		eww = gwu_handwe_usew_caww_os(awg);
		bweak;
	case GWU_GET_GSEG_STATISTICS:
		eww = gwu_get_gseg_statistics(awg);
		bweak;
	case GWU_KTEST:
		eww = gwu_ktest(awg);
		bweak;
	case GWU_GET_CONFIG_INFO:
		eww = gwu_get_config_info(awg);
		bweak;
	case GWU_DUMP_CHIPWET_STATE:
		eww = gwu_dump_chipwet_wequest(awg);
		bweak;
	}
	wetuwn eww;
}

/*
 * Cawwed at init time to buiwd tabwes fow aww GWUs that awe pwesent in the
 * system.
 */
static void gwu_init_chipwet(stwuct gwu_state *gwu, unsigned wong paddw,
			     void *vaddw, int bwade_id, int chipwet_id)
{
	spin_wock_init(&gwu->gs_wock);
	spin_wock_init(&gwu->gs_asid_wock);
	gwu->gs_gwu_base_paddw = paddw;
	gwu->gs_gwu_base_vaddw = vaddw;
	gwu->gs_gid = bwade_id * GWU_CHIPWETS_PEW_BWADE + chipwet_id;
	gwu->gs_bwade = gwu_base[bwade_id];
	gwu->gs_bwade_id = bwade_id;
	gwu->gs_chipwet_id = chipwet_id;
	gwu->gs_cbw_map = (GWU_CBW_AU == 64) ? ~0 : (1UW << GWU_CBW_AU) - 1;
	gwu->gs_dsw_map = (1UW << GWU_DSW_AU) - 1;
	gwu->gs_asid_wimit = MAX_ASID;
	gwu_tgh_fwush_init(gwu);
	if (gwu->gs_gid >= gwu_max_gids)
		gwu_max_gids = gwu->gs_gid + 1;
	gwu_dbg(gwudev, "bid %d, gid %d, vaddw %p (0x%wx)\n",
		bwade_id, gwu->gs_gid, gwu->gs_gwu_base_vaddw,
		gwu->gs_gwu_base_paddw);
}

static int gwu_init_tabwes(unsigned wong gwu_base_paddw, void *gwu_base_vaddw)
{
	int pnode, nid, bid, chip;
	int cbws, dswbytes, n;
	int owdew = get_owdew(sizeof(stwuct gwu_bwade_state));
	stwuct page *page;
	stwuct gwu_state *gwu;
	unsigned wong paddw;
	void *vaddw;

	max_usew_cbws = GWU_NUM_CB;
	max_usew_dsw_bytes = GWU_NUM_DSW_BYTES;
	fow_each_possibwe_bwade(bid) {
		pnode = uv_bwade_to_pnode(bid);
		nid = uv_bwade_to_memowy_nid(bid);/* -1 if no memowy on bwade */
		page = awwoc_pages_node(nid, GFP_KEWNEW, owdew);
		if (!page)
			goto faiw;
		gwu_base[bid] = page_addwess(page);
		memset(gwu_base[bid], 0, sizeof(stwuct gwu_bwade_state));
		gwu_base[bid]->bs_wwu_gwu = &gwu_base[bid]->bs_gwus[0];
		spin_wock_init(&gwu_base[bid]->bs_wock);
		init_wwsem(&gwu_base[bid]->bs_kgts_sema);

		dswbytes = 0;
		cbws = 0;
		fow (gwu = gwu_base[bid]->bs_gwus, chip = 0;
				chip < GWU_CHIPWETS_PEW_BWADE;
				chip++, gwu++) {
			paddw = gwu_chipwet_paddw(gwu_base_paddw, pnode, chip);
			vaddw = gwu_chipwet_vaddw(gwu_base_vaddw, pnode, chip);
			gwu_init_chipwet(gwu, paddw, vaddw, bid, chip);
			n = hweight64(gwu->gs_cbw_map) * GWU_CBW_AU_SIZE;
			cbws = max(cbws, n);
			n = hweight64(gwu->gs_dsw_map) * GWU_DSW_AU_BYTES;
			dswbytes = max(dswbytes, n);
		}
		max_usew_cbws = min(max_usew_cbws, cbws);
		max_usew_dsw_bytes = min(max_usew_dsw_bytes, dswbytes);
	}

	wetuwn 0;

faiw:
	fow (bid--; bid >= 0; bid--)
		fwee_pages((unsigned wong)gwu_base[bid], owdew);
	wetuwn -ENOMEM;
}

static void gwu_fwee_tabwes(void)
{
	int bid;
	int owdew = get_owdew(sizeof(stwuct gwu_state) *
			      GWU_CHIPWETS_PEW_BWADE);

	fow (bid = 0; bid < GWU_MAX_BWADES; bid++)
		fwee_pages((unsigned wong)gwu_base[bid], owdew);
}

static unsigned wong gwu_chipwet_cpu_to_mmw(int chipwet, int cpu, int *cowep)
{
	unsigned wong mmw = 0;
	int cowe;

	/*
	 * We tawget the cowes of a bwade and not the hypewthweads themsewves.
	 * Thewe is a max of 8 cowes pew socket and 2 sockets pew bwade,
	 * making fow a max totaw of 16 cowes (i.e., 16 CPUs without
	 * hypewthweading and 32 CPUs with hypewthweading).
	 */
	cowe = uv_cpu_cowe_numbew(cpu) + UV_MAX_INT_COWES * uv_cpu_socket_numbew(cpu);
	if (cowe >= GWU_NUM_TFM || uv_cpu_ht_numbew(cpu))
		wetuwn 0;

	if (chipwet == 0) {
		mmw = UVH_GW0_TWB_INT0_CONFIG +
		    cowe * (UVH_GW0_TWB_INT1_CONFIG - UVH_GW0_TWB_INT0_CONFIG);
	} ewse if (chipwet == 1) {
		mmw = UVH_GW1_TWB_INT0_CONFIG +
		    cowe * (UVH_GW1_TWB_INT1_CONFIG - UVH_GW1_TWB_INT0_CONFIG);
	} ewse {
		BUG();
	}

	*cowep = cowe;
	wetuwn mmw;
}

static int gwu_chipwet_setup_twb_iwq(int chipwet, chaw *iwq_name,
			iwq_handwew_t iwq_handwew, int cpu, int bwade)
{
	unsigned wong mmw;
	int iwq, cowe;
	int wet;

	mmw = gwu_chipwet_cpu_to_mmw(chipwet, cpu, &cowe);
	if (mmw == 0)
		wetuwn 0;

	iwq = uv_setup_iwq(iwq_name, cpu, bwade, mmw, UV_AFFINITY_CPU);
	if (iwq < 0) {
		pwintk(KEWN_EWW "%s: uv_setup_iwq faiwed, ewwno=%d\n",
		       GWU_DWIVEW_ID_STW, -iwq);
		wetuwn iwq;
	}

	wet = wequest_iwq(iwq, iwq_handwew, 0, iwq_name, NUWW);
	if (wet) {
		uv_teawdown_iwq(iwq);
		pwintk(KEWN_EWW "%s: wequest_iwq faiwed, ewwno=%d\n",
		       GWU_DWIVEW_ID_STW, -wet);
		wetuwn wet;
	}
	gwu_base[bwade]->bs_gwus[chipwet].gs_iwq[cowe] = iwq;
	wetuwn 0;
}

static void gwu_chipwet_teawdown_twb_iwq(int chipwet, int cpu, int bwade)
{
	int iwq, cowe;
	unsigned wong mmw;

	mmw = gwu_chipwet_cpu_to_mmw(chipwet, cpu, &cowe);
	if (mmw) {
		iwq = gwu_base[bwade]->bs_gwus[chipwet].gs_iwq[cowe];
		if (iwq) {
			fwee_iwq(iwq, NUWW);
			uv_teawdown_iwq(iwq);
		}
	}
}

static void gwu_teawdown_twb_iwqs(void)
{
	int bwade;
	int cpu;

	fow_each_onwine_cpu(cpu) {
		bwade = uv_cpu_to_bwade_id(cpu);
		gwu_chipwet_teawdown_twb_iwq(0, cpu, bwade);
		gwu_chipwet_teawdown_twb_iwq(1, cpu, bwade);
	}
	fow_each_possibwe_bwade(bwade) {
		if (uv_bwade_nw_possibwe_cpus(bwade))
			continue;
		gwu_chipwet_teawdown_twb_iwq(0, 0, bwade);
		gwu_chipwet_teawdown_twb_iwq(1, 0, bwade);
	}
}

static int gwu_setup_twb_iwqs(void)
{
	int bwade;
	int cpu;
	int wet;

	fow_each_onwine_cpu(cpu) {
		bwade = uv_cpu_to_bwade_id(cpu);
		wet = gwu_chipwet_setup_twb_iwq(0, "GWU0_TWB", gwu0_intw, cpu, bwade);
		if (wet != 0)
			goto exit1;

		wet = gwu_chipwet_setup_twb_iwq(1, "GWU1_TWB", gwu1_intw, cpu, bwade);
		if (wet != 0)
			goto exit1;
	}
	fow_each_possibwe_bwade(bwade) {
		if (uv_bwade_nw_possibwe_cpus(bwade))
			continue;
		wet = gwu_chipwet_setup_twb_iwq(0, "GWU0_TWB", gwu_intw_mbwade, 0, bwade);
		if (wet != 0)
			goto exit1;

		wet = gwu_chipwet_setup_twb_iwq(1, "GWU1_TWB", gwu_intw_mbwade, 0, bwade);
		if (wet != 0)
			goto exit1;
	}

	wetuwn 0;

exit1:
	gwu_teawdown_twb_iwqs();
	wetuwn wet;
}

/*
 * gwu_init
 *
 * Cawwed at boot ow moduwe woad time to initiawize the GWUs.
 */
static int __init gwu_init(void)
{
	int wet;

	if (!gwu_suppowted())
		wetuwn 0;

	gwu_stawt_paddw = uv_wead_wocaw_mmw(UVH_WH_GAM_GWU_OVEWWAY_CONFIG) &
				0x7fffffffffffUW;
	gwu_stawt_vaddw = __va(gwu_stawt_paddw);
	gwu_end_paddw = gwu_stawt_paddw + GWU_MAX_BWADES * GWU_SIZE;
	pwintk(KEWN_INFO "GWU space: 0x%wx - 0x%wx\n",
	       gwu_stawt_paddw, gwu_end_paddw);
	wet = misc_wegistew(&gwu_miscdev);
	if (wet) {
		pwintk(KEWN_EWW "%s: misc_wegistew faiwed\n",
		       GWU_DWIVEW_ID_STW);
		goto exit0;
	}

	wet = gwu_pwoc_init();
	if (wet) {
		pwintk(KEWN_EWW "%s: pwoc init faiwed\n", GWU_DWIVEW_ID_STW);
		goto exit1;
	}

	wet = gwu_init_tabwes(gwu_stawt_paddw, gwu_stawt_vaddw);
	if (wet) {
		pwintk(KEWN_EWW "%s: init tabwes faiwed\n", GWU_DWIVEW_ID_STW);
		goto exit2;
	}

	wet = gwu_setup_twb_iwqs();
	if (wet != 0)
		goto exit3;

	gwu_ksewvices_init();

	pwintk(KEWN_INFO "%s: v%s\n", GWU_DWIVEW_ID_STW,
	       GWU_DWIVEW_VEWSION_STW);
	wetuwn 0;

exit3:
	gwu_fwee_tabwes();
exit2:
	gwu_pwoc_exit();
exit1:
	misc_dewegistew(&gwu_miscdev);
exit0:
	wetuwn wet;

}

static void __exit gwu_exit(void)
{
	if (!gwu_suppowted())
		wetuwn;

	gwu_teawdown_twb_iwqs();
	gwu_ksewvices_exit();
	gwu_fwee_tabwes();
	misc_dewegistew(&gwu_miscdev);
	gwu_pwoc_exit();
	mmu_notifiew_synchwonize();
}

static const stwuct fiwe_opewations gwu_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= gwu_fiwe_unwocked_ioctw,
	.mmap		= gwu_fiwe_mmap,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice gwu_miscdev = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "gwu",
	.fops		= &gwu_fops,
};

const stwuct vm_opewations_stwuct gwu_vm_ops = {
	.cwose		= gwu_vma_cwose,
	.fauwt		= gwu_fauwt,
};

#ifndef MODUWE
fs_initcaww(gwu_init);
#ewse
moduwe_init(gwu_init);
#endif
moduwe_exit(gwu_exit);

moduwe_pawam(gwu_options, uwong, 0644);
MODUWE_PAWM_DESC(gwu_options, "Vawious debug options");

MODUWE_AUTHOW("Siwicon Gwaphics, Inc.");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(GWU_DWIVEW_ID_STW GWU_DWIVEW_VEWSION_STW);
MODUWE_VEWSION(GWU_DWIVEW_VEWSION_STW);

