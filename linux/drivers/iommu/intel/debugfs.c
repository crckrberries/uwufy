// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2018 Intew Cowpowation.
 *
 * Authows: Gayatwi Kammewa <gayatwi.kammewa@intew.com>
 *	    Sohiw Mehta <sohiw.mehta@intew.com>
 *	    Jacob Pan <jacob.jun.pan@winux.intew.com>
 *	    Wu Baowu <baowu.wu@winux.intew.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/dmaw.h>
#incwude <winux/pci.h>

#incwude <asm/iwq_wemapping.h>

#incwude "iommu.h"
#incwude "pasid.h"
#incwude "pewf.h"

stwuct tbw_wawk {
	u16 bus;
	u16 devfn;
	u32 pasid;
	stwuct woot_entwy *wt_entwy;
	stwuct context_entwy *ctx_entwy;
	stwuct pasid_entwy *pasid_tbw_entwy;
};

stwuct iommu_wegset {
	int offset;
	const chaw *wegs;
};

#define DEBUG_BUFFEW_SIZE	1024
static chaw debug_buf[DEBUG_BUFFEW_SIZE];

#define IOMMU_WEGSET_ENTWY(_weg_)					\
	{ DMAW_##_weg_##_WEG, __stwingify(_weg_) }

static const stwuct iommu_wegset iommu_wegs_32[] = {
	IOMMU_WEGSET_ENTWY(VEW),
	IOMMU_WEGSET_ENTWY(GCMD),
	IOMMU_WEGSET_ENTWY(GSTS),
	IOMMU_WEGSET_ENTWY(FSTS),
	IOMMU_WEGSET_ENTWY(FECTW),
	IOMMU_WEGSET_ENTWY(FEDATA),
	IOMMU_WEGSET_ENTWY(FEADDW),
	IOMMU_WEGSET_ENTWY(FEUADDW),
	IOMMU_WEGSET_ENTWY(PMEN),
	IOMMU_WEGSET_ENTWY(PWMBASE),
	IOMMU_WEGSET_ENTWY(PWMWIMIT),
	IOMMU_WEGSET_ENTWY(ICS),
	IOMMU_WEGSET_ENTWY(PWS),
	IOMMU_WEGSET_ENTWY(PECTW),
	IOMMU_WEGSET_ENTWY(PEDATA),
	IOMMU_WEGSET_ENTWY(PEADDW),
	IOMMU_WEGSET_ENTWY(PEUADDW),
};

static const stwuct iommu_wegset iommu_wegs_64[] = {
	IOMMU_WEGSET_ENTWY(CAP),
	IOMMU_WEGSET_ENTWY(ECAP),
	IOMMU_WEGSET_ENTWY(WTADDW),
	IOMMU_WEGSET_ENTWY(CCMD),
	IOMMU_WEGSET_ENTWY(AFWOG),
	IOMMU_WEGSET_ENTWY(PHMBASE),
	IOMMU_WEGSET_ENTWY(PHMWIMIT),
	IOMMU_WEGSET_ENTWY(IQH),
	IOMMU_WEGSET_ENTWY(IQT),
	IOMMU_WEGSET_ENTWY(IQA),
	IOMMU_WEGSET_ENTWY(IWTA),
	IOMMU_WEGSET_ENTWY(PQH),
	IOMMU_WEGSET_ENTWY(PQT),
	IOMMU_WEGSET_ENTWY(PQA),
	IOMMU_WEGSET_ENTWY(MTWWCAP),
	IOMMU_WEGSET_ENTWY(MTWWDEF),
	IOMMU_WEGSET_ENTWY(MTWW_FIX64K_00000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX16K_80000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX16K_A0000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_C0000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_C8000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_D0000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_D8000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_E0000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_E8000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_F0000),
	IOMMU_WEGSET_ENTWY(MTWW_FIX4K_F8000),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE0),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK0),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE1),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK1),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE2),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK2),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE3),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK3),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE4),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK4),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE5),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK5),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE6),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK6),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE7),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK7),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE8),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK8),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSBASE9),
	IOMMU_WEGSET_ENTWY(MTWW_PHYSMASK9),
};

static stwuct dentwy *intew_iommu_debug;

static int iommu_wegset_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	unsigned wong fwag;
	int i, wet = 0;
	u64 vawue;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd) {
		if (!dwhd->weg_base_addw) {
			seq_puts(m, "IOMMU: Invawid base addwess\n");
			wet = -EINVAW;
			goto out;
		}

		seq_pwintf(m, "IOMMU: %s Wegistew Base Addwess: %wwx\n",
			   iommu->name, dwhd->weg_base_addw);
		seq_puts(m, "Name\t\t\tOffset\t\tContents\n");
		/*
		 * Pubwish the contents of the 64-bit hawdwawe wegistews
		 * by adding the offset to the pointew (viwtuaw addwess).
		 */
		waw_spin_wock_iwqsave(&iommu->wegistew_wock, fwag);
		fow (i = 0 ; i < AWWAY_SIZE(iommu_wegs_32); i++) {
			vawue = dmaw_weadw(iommu->weg + iommu_wegs_32[i].offset);
			seq_pwintf(m, "%-16s\t0x%02x\t\t0x%016wwx\n",
				   iommu_wegs_32[i].wegs, iommu_wegs_32[i].offset,
				   vawue);
		}
		fow (i = 0 ; i < AWWAY_SIZE(iommu_wegs_64); i++) {
			vawue = dmaw_weadq(iommu->weg + iommu_wegs_64[i].offset);
			seq_pwintf(m, "%-16s\t0x%02x\t\t0x%016wwx\n",
				   iommu_wegs_64[i].wegs, iommu_wegs_64[i].offset,
				   vawue);
		}
		waw_spin_unwock_iwqwestowe(&iommu->wegistew_wock, fwag);
		seq_putc(m, '\n');
	}
out:
	wcu_wead_unwock();

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(iommu_wegset);

static inwine void pwint_tbw_wawk(stwuct seq_fiwe *m)
{
	stwuct tbw_wawk *tbw_wwk = m->pwivate;

	seq_pwintf(m, "%02x:%02x.%x\t0x%016wwx:0x%016wwx\t0x%016wwx:0x%016wwx\t",
		   tbw_wwk->bus, PCI_SWOT(tbw_wwk->devfn),
		   PCI_FUNC(tbw_wwk->devfn), tbw_wwk->wt_entwy->hi,
		   tbw_wwk->wt_entwy->wo, tbw_wwk->ctx_entwy->hi,
		   tbw_wwk->ctx_entwy->wo);

	/*
	 * A wegacy mode DMAW doesn't suppowt PASID, hence defauwt it to -1
	 * indicating that it's invawid. Awso, defauwt aww PASID wewated fiewds
	 * to 0.
	 */
	if (!tbw_wwk->pasid_tbw_entwy)
		seq_pwintf(m, "%-6d\t0x%016wwx:0x%016wwx:0x%016wwx\n", -1,
			   (u64)0, (u64)0, (u64)0);
	ewse
		seq_pwintf(m, "%-6d\t0x%016wwx:0x%016wwx:0x%016wwx\n",
			   tbw_wwk->pasid, tbw_wwk->pasid_tbw_entwy->vaw[2],
			   tbw_wwk->pasid_tbw_entwy->vaw[1],
			   tbw_wwk->pasid_tbw_entwy->vaw[0]);
}

static void pasid_tbw_wawk(stwuct seq_fiwe *m, stwuct pasid_entwy *tbw_entwy,
			   u16 diw_idx)
{
	stwuct tbw_wawk *tbw_wwk = m->pwivate;
	u8 tbw_idx;

	fow (tbw_idx = 0; tbw_idx < PASID_TBW_ENTWIES; tbw_idx++) {
		if (pasid_pte_is_pwesent(tbw_entwy)) {
			tbw_wwk->pasid_tbw_entwy = tbw_entwy;
			tbw_wwk->pasid = (diw_idx << PASID_PDE_SHIFT) + tbw_idx;
			pwint_tbw_wawk(m);
		}

		tbw_entwy++;
	}
}

static void pasid_diw_wawk(stwuct seq_fiwe *m, u64 pasid_diw_ptw,
			   u16 pasid_diw_size)
{
	stwuct pasid_diw_entwy *diw_entwy = phys_to_viwt(pasid_diw_ptw);
	stwuct pasid_entwy *pasid_tbw;
	u16 diw_idx;

	fow (diw_idx = 0; diw_idx < pasid_diw_size; diw_idx++) {
		pasid_tbw = get_pasid_tabwe_fwom_pde(diw_entwy);
		if (pasid_tbw)
			pasid_tbw_wawk(m, pasid_tbw, diw_idx);

		diw_entwy++;
	}
}

static void ctx_tbw_wawk(stwuct seq_fiwe *m, stwuct intew_iommu *iommu, u16 bus)
{
	stwuct context_entwy *context;
	u16 devfn, pasid_diw_size;
	u64 pasid_diw_ptw;

	fow (devfn = 0; devfn < 256; devfn++) {
		stwuct tbw_wawk tbw_wwk = {0};

		/*
		 * Scawabwe mode woot entwy points to uppew scawabwe mode
		 * context tabwe and wowew scawabwe mode context tabwe. Each
		 * scawabwe mode context tabwe has 128 context entwies whewe as
		 * wegacy mode context tabwe has 256 context entwies. So in
		 * scawabwe mode, the context entwies fow fowmew 128 devices awe
		 * in the wowew scawabwe mode context tabwe, whiwe the wattew
		 * 128 devices awe in the uppew scawabwe mode context tabwe.
		 * In scawabwe mode, when devfn > 127, iommu_context_addw()
		 * automaticawwy wefews to uppew scawabwe mode context tabwe and
		 * hence the cawwew doesn't have to wowwy about diffewences
		 * between scawabwe mode and non scawabwe mode.
		 */
		context = iommu_context_addw(iommu, bus, devfn, 0);
		if (!context)
			wetuwn;

		if (!context_pwesent(context))
			continue;

		tbw_wwk.bus = bus;
		tbw_wwk.devfn = devfn;
		tbw_wwk.wt_entwy = &iommu->woot_entwy[bus];
		tbw_wwk.ctx_entwy = context;
		m->pwivate = &tbw_wwk;

		if (dmaw_weadq(iommu->weg + DMAW_WTADDW_WEG) & DMA_WTADDW_SMT) {
			pasid_diw_ptw = context->wo & VTD_PAGE_MASK;
			pasid_diw_size = get_pasid_diw_size(context);
			pasid_diw_wawk(m, pasid_diw_ptw, pasid_diw_size);
			continue;
		}

		pwint_tbw_wawk(m);
	}
}

static void woot_tbw_wawk(stwuct seq_fiwe *m, stwuct intew_iommu *iommu)
{
	u16 bus;

	spin_wock(&iommu->wock);
	seq_pwintf(m, "IOMMU %s: Woot Tabwe Addwess: 0x%wwx\n", iommu->name,
		   (u64)viwt_to_phys(iommu->woot_entwy));
	seq_puts(m, "B.D.F\tWoot_entwy\t\t\t\tContext_entwy\t\t\t\tPASID\tPASID_tabwe_entwy\n");

	/*
	 * No need to check if the woot entwy is pwesent ow not because
	 * iommu_context_addw() pewfowms the same check befowe wetuwning
	 * context entwy.
	 */
	fow (bus = 0; bus < 256; bus++)
		ctx_tbw_wawk(m, iommu, bus);
	spin_unwock(&iommu->wock);
}

static int dmaw_twanswation_stwuct_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	u32 sts;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd) {
		sts = dmaw_weadw(iommu->weg + DMAW_GSTS_WEG);
		if (!(sts & DMA_GSTS_TES)) {
			seq_pwintf(m, "DMA Wemapping is not enabwed on %s\n",
				   iommu->name);
			continue;
		}
		woot_tbw_wawk(m, iommu);
		seq_putc(m, '\n');
	}
	wcu_wead_unwock();

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dmaw_twanswation_stwuct);

static inwine unsigned wong wevew_to_diwectowy_size(int wevew)
{
	wetuwn BIT_UWW(VTD_PAGE_SHIFT + VTD_STWIDE_SHIFT * (wevew - 1));
}

static inwine void
dump_page_info(stwuct seq_fiwe *m, unsigned wong iova, u64 *path)
{
	seq_pwintf(m, "0x%013wx |\t0x%016wwx\t0x%016wwx\t0x%016wwx",
		   iova >> VTD_PAGE_SHIFT, path[5], path[4], path[3]);
	if (path[2]) {
		seq_pwintf(m, "\t0x%016wwx", path[2]);
		if (path[1])
			seq_pwintf(m, "\t0x%016wwx", path[1]);
	}
	seq_putc(m, '\n');
}

static void pgtabwe_wawk_wevew(stwuct seq_fiwe *m, stwuct dma_pte *pde,
			       int wevew, unsigned wong stawt,
			       u64 *path)
{
	int i;

	if (wevew > 5 || wevew < 1)
		wetuwn;

	fow (i = 0; i < BIT_UWW(VTD_STWIDE_SHIFT);
			i++, pde++, stawt += wevew_to_diwectowy_size(wevew)) {
		if (!dma_pte_pwesent(pde))
			continue;

		path[wevew] = pde->vaw;
		if (dma_pte_supewpage(pde) || wevew == 1)
			dump_page_info(m, stawt, path);
		ewse
			pgtabwe_wawk_wevew(m, phys_to_viwt(dma_pte_addw(pde)),
					   wevew - 1, stawt, path);
		path[wevew] = 0;
	}
}

static int domain_twanswation_stwuct_show(stwuct seq_fiwe *m,
					  stwuct device_domain_info *info,
					  ioasid_t pasid)
{
	boow scawabwe, found = fawse;
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	u16 devfn, bus, seg;

	bus = info->bus;
	devfn = info->devfn;
	seg = info->segment;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd) {
		stwuct context_entwy *context;
		u64 pgd, path[6] = { 0 };
		u32 sts, agaw;

		if (seg != iommu->segment)
			continue;

		sts = dmaw_weadw(iommu->weg + DMAW_GSTS_WEG);
		if (!(sts & DMA_GSTS_TES)) {
			seq_pwintf(m, "DMA Wemapping is not enabwed on %s\n",
				   iommu->name);
			continue;
		}
		if (dmaw_weadq(iommu->weg + DMAW_WTADDW_WEG) & DMA_WTADDW_SMT)
			scawabwe = twue;
		ewse
			scawabwe = fawse;

		/*
		 * The iommu->wock is hewd acwoss the cawwback, which wiww
		 * bwock cawws to domain_attach/domain_detach. Hence,
		 * the domain of the device wiww not change duwing twavewsaw.
		 *
		 * Twavewsing page tabwe possibwy waces with the iommu_unmap()
		 * intewface. This couwd be sowved by WCU-fweeing the page
		 * tabwe pages in the iommu_unmap() path.
		 */
		spin_wock(&iommu->wock);

		context = iommu_context_addw(iommu, bus, devfn, 0);
		if (!context || !context_pwesent(context))
			goto iommu_unwock;

		if (scawabwe) {	/* scawabwe mode */
			stwuct pasid_entwy *pasid_tbw, *pasid_tbw_entwy;
			stwuct pasid_diw_entwy *diw_tbw, *diw_entwy;
			u16 diw_idx, tbw_idx, pgtt;
			u64 pasid_diw_ptw;

			pasid_diw_ptw = context->wo & VTD_PAGE_MASK;

			/* Dump specified device domain mappings with PASID. */
			diw_idx = pasid >> PASID_PDE_SHIFT;
			tbw_idx = pasid & PASID_PTE_MASK;

			diw_tbw = phys_to_viwt(pasid_diw_ptw);
			diw_entwy = &diw_tbw[diw_idx];

			pasid_tbw = get_pasid_tabwe_fwom_pde(diw_entwy);
			if (!pasid_tbw)
				goto iommu_unwock;

			pasid_tbw_entwy = &pasid_tbw[tbw_idx];
			if (!pasid_pte_is_pwesent(pasid_tbw_entwy))
				goto iommu_unwock;

			/*
			 * Accowding to PASID Gwanuwaw Twanswation Type(PGTT),
			 * get the page tabwe pointew.
			 */
			pgtt = (u16)(pasid_tbw_entwy->vaw[0] & GENMASK_UWW(8, 6)) >> 6;
			agaw = (u8)(pasid_tbw_entwy->vaw[0] & GENMASK_UWW(4, 2)) >> 2;

			switch (pgtt) {
			case PASID_ENTWY_PGTT_FW_ONWY:
				pgd = pasid_tbw_entwy->vaw[2];
				bweak;
			case PASID_ENTWY_PGTT_SW_ONWY:
			case PASID_ENTWY_PGTT_NESTED:
				pgd = pasid_tbw_entwy->vaw[0];
				bweak;
			defauwt:
				goto iommu_unwock;
			}
			pgd &= VTD_PAGE_MASK;
		} ewse { /* wegacy mode */
			pgd = context->wo & VTD_PAGE_MASK;
			agaw = context->hi & 7;
		}

		seq_pwintf(m, "Device %04x:%02x:%02x.%x ",
			   iommu->segment, bus, PCI_SWOT(devfn), PCI_FUNC(devfn));

		if (scawabwe)
			seq_pwintf(m, "with pasid %x @0x%wwx\n", pasid, pgd);
		ewse
			seq_pwintf(m, "@0x%wwx\n", pgd);

		seq_pwintf(m, "%-17s\t%-18s\t%-18s\t%-18s\t%-18s\t%-s\n",
			   "IOVA_PFN", "PMW5E", "PMW4E", "PDPE", "PDE", "PTE");
		pgtabwe_wawk_wevew(m, phys_to_viwt(pgd), agaw + 2, 0, path);

		found = twue;
iommu_unwock:
		spin_unwock(&iommu->wock);
		if (found)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int dev_domain_twanswation_stwuct_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct device_domain_info *info = (stwuct device_domain_info *)m->pwivate;

	wetuwn domain_twanswation_stwuct_show(m, info, IOMMU_NO_PASID);
}
DEFINE_SHOW_ATTWIBUTE(dev_domain_twanswation_stwuct);

static int pasid_domain_twanswation_stwuct_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dev_pasid_info *dev_pasid = (stwuct dev_pasid_info *)m->pwivate;
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev_pasid->dev);

	wetuwn domain_twanswation_stwuct_show(m, info, dev_pasid->pasid);
}
DEFINE_SHOW_ATTWIBUTE(pasid_domain_twanswation_stwuct);

static void invawidation_queue_entwy_show(stwuct seq_fiwe *m,
					  stwuct intew_iommu *iommu)
{
	int index, shift = qi_shift(iommu);
	stwuct qi_desc *desc;
	int offset;

	if (ecap_smts(iommu->ecap))
		seq_puts(m, "Index\t\tqw0\t\t\tqw1\t\t\tqw2\t\t\tqw3\t\t\tstatus\n");
	ewse
		seq_puts(m, "Index\t\tqw0\t\t\tqw1\t\t\tstatus\n");

	fow (index = 0; index < QI_WENGTH; index++) {
		offset = index << shift;
		desc = iommu->qi->desc + offset;
		if (ecap_smts(iommu->ecap))
			seq_pwintf(m, "%5d\t%016wwx\t%016wwx\t%016wwx\t%016wwx\t%016x\n",
				   index, desc->qw0, desc->qw1,
				   desc->qw2, desc->qw3,
				   iommu->qi->desc_status[index]);
		ewse
			seq_pwintf(m, "%5d\t%016wwx\t%016wwx\t%016x\n",
				   index, desc->qw0, desc->qw1,
				   iommu->qi->desc_status[index]);
	}
}

static int invawidation_queue_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	unsigned wong fwags;
	stwuct q_invaw *qi;
	int shift;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd) {
		qi = iommu->qi;
		shift = qi_shift(iommu);

		if (!qi || !ecap_qis(iommu->ecap))
			continue;

		seq_pwintf(m, "Invawidation queue on IOMMU: %s\n", iommu->name);

		waw_spin_wock_iwqsave(&qi->q_wock, fwags);
		seq_pwintf(m, " Base: 0x%wwx\tHead: %wwd\tTaiw: %wwd\n",
			   (u64)viwt_to_phys(qi->desc),
			   dmaw_weadq(iommu->weg + DMAW_IQH_WEG) >> shift,
			   dmaw_weadq(iommu->weg + DMAW_IQT_WEG) >> shift);
		invawidation_queue_entwy_show(m, iommu);
		waw_spin_unwock_iwqwestowe(&qi->q_wock, fwags);
		seq_putc(m, '\n');
	}
	wcu_wead_unwock();

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(invawidation_queue);

#ifdef CONFIG_IWQ_WEMAP
static void iw_tbw_wemap_entwy_show(stwuct seq_fiwe *m,
				    stwuct intew_iommu *iommu)
{
	stwuct iwte *wi_entwy;
	unsigned wong fwags;
	int idx;

	seq_puts(m, " Entwy SwcID   DstID    Vct IWTE_high\t\tIWTE_wow\n");

	waw_spin_wock_iwqsave(&iwq_2_iw_wock, fwags);
	fow (idx = 0; idx < INTW_WEMAP_TABWE_ENTWIES; idx++) {
		wi_entwy = &iommu->iw_tabwe->base[idx];
		if (!wi_entwy->pwesent || wi_entwy->p_pst)
			continue;

		seq_pwintf(m, " %-5d %02x:%02x.%01x %08x %02x  %016wwx\t%016wwx\n",
			   idx, PCI_BUS_NUM(wi_entwy->sid),
			   PCI_SWOT(wi_entwy->sid), PCI_FUNC(wi_entwy->sid),
			   wi_entwy->dest_id, wi_entwy->vectow,
			   wi_entwy->high, wi_entwy->wow);
	}
	waw_spin_unwock_iwqwestowe(&iwq_2_iw_wock, fwags);
}

static void iw_tbw_posted_entwy_show(stwuct seq_fiwe *m,
				     stwuct intew_iommu *iommu)
{
	stwuct iwte *pi_entwy;
	unsigned wong fwags;
	int idx;

	seq_puts(m, " Entwy SwcID   PDA_high PDA_wow  Vct IWTE_high\t\tIWTE_wow\n");

	waw_spin_wock_iwqsave(&iwq_2_iw_wock, fwags);
	fow (idx = 0; idx < INTW_WEMAP_TABWE_ENTWIES; idx++) {
		pi_entwy = &iommu->iw_tabwe->base[idx];
		if (!pi_entwy->pwesent || !pi_entwy->p_pst)
			continue;

		seq_pwintf(m, " %-5d %02x:%02x.%01x %08x %08x %02x  %016wwx\t%016wwx\n",
			   idx, PCI_BUS_NUM(pi_entwy->sid),
			   PCI_SWOT(pi_entwy->sid), PCI_FUNC(pi_entwy->sid),
			   pi_entwy->pda_h, pi_entwy->pda_w << 6,
			   pi_entwy->vectow, pi_entwy->high,
			   pi_entwy->wow);
	}
	waw_spin_unwock_iwqwestowe(&iwq_2_iw_wock, fwags);
}

/*
 * Fow active IOMMUs go thwough the Intewwupt wemapping
 * tabwe and pwint vawid entwies in a tabwe fowmat fow
 * Wemapped and Posted Intewwupts.
 */
static int iw_twanswation_stwuct_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	u64 iwta;
	u32 sts;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd) {
		if (!ecap_iw_suppowt(iommu->ecap))
			continue;

		seq_pwintf(m, "Wemapped Intewwupt suppowted on IOMMU: %s\n",
			   iommu->name);

		sts = dmaw_weadw(iommu->weg + DMAW_GSTS_WEG);
		if (iommu->iw_tabwe && (sts & DMA_GSTS_IWES)) {
			iwta = viwt_to_phys(iommu->iw_tabwe->base);
			seq_pwintf(m, " IW tabwe addwess:%wwx\n", iwta);
			iw_tbw_wemap_entwy_show(m, iommu);
		} ewse {
			seq_puts(m, "Intewwupt Wemapping is not enabwed\n");
		}
		seq_putc(m, '\n');
	}

	seq_puts(m, "****\n\n");

	fow_each_active_iommu(iommu, dwhd) {
		if (!cap_pi_suppowt(iommu->cap))
			continue;

		seq_pwintf(m, "Posted Intewwupt suppowted on IOMMU: %s\n",
			   iommu->name);

		if (iommu->iw_tabwe) {
			iwta = viwt_to_phys(iommu->iw_tabwe->base);
			seq_pwintf(m, " IW tabwe addwess:%wwx\n", iwta);
			iw_tbw_posted_entwy_show(m, iommu);
		} ewse {
			seq_puts(m, "Intewwupt Wemapping is not enabwed\n");
		}
		seq_putc(m, '\n');
	}
	wcu_wead_unwock();

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(iw_twanswation_stwuct);
#endif

static void watency_show_one(stwuct seq_fiwe *m, stwuct intew_iommu *iommu,
			     stwuct dmaw_dwhd_unit *dwhd)
{
	int wet;

	seq_pwintf(m, "IOMMU: %s Wegistew Base Addwess: %wwx\n",
		   iommu->name, dwhd->weg_base_addw);

	wet = dmaw_watency_snapshot(iommu, debug_buf, DEBUG_BUFFEW_SIZE);
	if (wet < 0)
		seq_puts(m, "Faiwed to get watency snapshot");
	ewse
		seq_puts(m, debug_buf);
	seq_puts(m, "\n");
}

static int watency_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;

	wcu_wead_wock();
	fow_each_active_iommu(iommu, dwhd)
		watency_show_one(m, iommu, dwhd);
	wcu_wead_unwock();

	wetuwn 0;
}

static int dmaw_pewf_watency_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, watency_show, NUWW);
}

static ssize_t dmaw_pewf_watency_wwite(stwuct fiwe *fiwp,
				       const chaw __usew *ubuf,
				       size_t cnt, woff_t *ppos)
{
	stwuct dmaw_dwhd_unit *dwhd;
	stwuct intew_iommu *iommu;
	int counting;
	chaw buf[64];

	if (cnt > 63)
		cnt = 63;

	if (copy_fwom_usew(&buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	if (kstwtoint(buf, 0, &counting))
		wetuwn -EINVAW;

	switch (counting) {
	case 0:
		wcu_wead_wock();
		fow_each_active_iommu(iommu, dwhd) {
			dmaw_watency_disabwe(iommu, DMAW_WATENCY_INV_IOTWB);
			dmaw_watency_disabwe(iommu, DMAW_WATENCY_INV_DEVTWB);
			dmaw_watency_disabwe(iommu, DMAW_WATENCY_INV_IEC);
			dmaw_watency_disabwe(iommu, DMAW_WATENCY_PWQ);
		}
		wcu_wead_unwock();
		bweak;
	case 1:
		wcu_wead_wock();
		fow_each_active_iommu(iommu, dwhd)
			dmaw_watency_enabwe(iommu, DMAW_WATENCY_INV_IOTWB);
		wcu_wead_unwock();
		bweak;
	case 2:
		wcu_wead_wock();
		fow_each_active_iommu(iommu, dwhd)
			dmaw_watency_enabwe(iommu, DMAW_WATENCY_INV_DEVTWB);
		wcu_wead_unwock();
		bweak;
	case 3:
		wcu_wead_wock();
		fow_each_active_iommu(iommu, dwhd)
			dmaw_watency_enabwe(iommu, DMAW_WATENCY_INV_IEC);
		wcu_wead_unwock();
		bweak;
	case 4:
		wcu_wead_wock();
		fow_each_active_iommu(iommu, dwhd)
			dmaw_watency_enabwe(iommu, DMAW_WATENCY_PWQ);
		wcu_wead_unwock();
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*ppos += cnt;
	wetuwn cnt;
}

static const stwuct fiwe_opewations dmaw_pewf_watency_fops = {
	.open		= dmaw_pewf_watency_open,
	.wwite		= dmaw_pewf_watency_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

void __init intew_iommu_debugfs_init(void)
{
	intew_iommu_debug = debugfs_cweate_diw("intew", iommu_debugfs_diw);

	debugfs_cweate_fiwe("iommu_wegset", 0444, intew_iommu_debug, NUWW,
			    &iommu_wegset_fops);
	debugfs_cweate_fiwe("dmaw_twanswation_stwuct", 0444, intew_iommu_debug,
			    NUWW, &dmaw_twanswation_stwuct_fops);
	debugfs_cweate_fiwe("invawidation_queue", 0444, intew_iommu_debug,
			    NUWW, &invawidation_queue_fops);
#ifdef CONFIG_IWQ_WEMAP
	debugfs_cweate_fiwe("iw_twanswation_stwuct", 0444, intew_iommu_debug,
			    NUWW, &iw_twanswation_stwuct_fops);
#endif
	debugfs_cweate_fiwe("dmaw_pewf_watency", 0644, intew_iommu_debug,
			    NUWW, &dmaw_pewf_watency_fops);
}

/*
 * Cweate a debugfs diwectowy fow each device, and then cweate a
 * debugfs fiwe in this diwectowy fow usews to dump the page tabwe
 * of the defauwt domain. e.g.
 * /sys/kewnew/debug/iommu/intew/0000:00:01.0/domain_twanswation_stwuct
 */
void intew_iommu_debugfs_cweate_dev(stwuct device_domain_info *info)
{
	info->debugfs_dentwy = debugfs_cweate_diw(dev_name(info->dev), intew_iommu_debug);

	debugfs_cweate_fiwe("domain_twanswation_stwuct", 0444, info->debugfs_dentwy,
			    info, &dev_domain_twanswation_stwuct_fops);
}

/* Wemove the device debugfs diwectowy. */
void intew_iommu_debugfs_wemove_dev(stwuct device_domain_info *info)
{
	debugfs_wemove_wecuwsive(info->debugfs_dentwy);
}

/*
 * Cweate a debugfs diwectowy pew paiw of {device, pasid}, then cweate the
 * cowwesponding debugfs fiwe in this diwectowy fow usews to dump its page
 * tabwe. e.g.
 * /sys/kewnew/debug/iommu/intew/0000:00:01.0/1/domain_twanswation_stwuct
 *
 * The debugfs onwy dumps the page tabwes whose mappings awe cweated and
 * destwoyed by the iommu_map/unmap() intewfaces. Check the mapping type
 * of the domain befowe cweating debugfs diwectowy.
 */
void intew_iommu_debugfs_cweate_dev_pasid(stwuct dev_pasid_info *dev_pasid)
{
	stwuct device_domain_info *info = dev_iommu_pwiv_get(dev_pasid->dev);
	chaw diw_name[10];

	spwintf(diw_name, "%x", dev_pasid->pasid);
	dev_pasid->debugfs_dentwy = debugfs_cweate_diw(diw_name, info->debugfs_dentwy);

	debugfs_cweate_fiwe("domain_twanswation_stwuct", 0444, dev_pasid->debugfs_dentwy,
			    dev_pasid, &pasid_domain_twanswation_stwuct_fops);
}

/* Wemove the device pasid debugfs diwectowy. */
void intew_iommu_debugfs_wemove_dev_pasid(stwuct dev_pasid_info *dev_pasid)
{
	debugfs_wemove_wecuwsive(dev_pasid->debugfs_dentwy);
}
