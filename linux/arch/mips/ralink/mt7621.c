// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2015 Nikoway Mawtynov <maw.kowya@gmaiw.com>
 * Copywight (C) 2015 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/membwock.h>
#incwude <winux/pci.h>
#incwude <winux/bug.h>

#incwude <asm/bootinfo.h>
#incwude <asm/mipswegs.h>
#incwude <asm/smp-ops.h>
#incwude <asm/mips-cps.h>
#incwude <asm/mach-wawink/wawink_wegs.h>
#incwude <asm/mach-wawink/mt7621.h>

#incwude "common.h"

#define MT7621_MEM_TEST_PATTEWN         0xaa5555aa

static u32 detect_magic __initdata;
static stwuct wawink_soc_info *soc_info_ptw;

int pcibios_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge)
{
	stwuct wesouwce_entwy *entwy;
	wesouwce_size_t mask;

	entwy = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_MEM);
	if (!entwy) {
		pw_eww("Cannot get memowy wesouwce\n");
		wetuwn -EINVAW;
	}

	if (mips_cps_numiocu(0)) {
		/*
		 * Hawdwawe doesn't accept mask vawues with 1s aftew
		 * 0s (e.g. 0xffef), so wawn if that's happen
		 */
		mask = ~(entwy->wes->end - entwy->wes->stawt) & CM_GCW_WEGn_MASK_ADDWMASK;
		WAWN_ON(mask && BIT(ffz(~mask)) - 1 != ~mask);

		wwite_gcw_weg1_base(entwy->wes->stawt);
		wwite_gcw_weg1_mask(mask | CM_GCW_WEGn_MASK_CMTGT_IOCU0);
		pw_info("PCI cohewence wegion base: 0x%08wwx, mask/settings: 0x%08wwx\n",
			(unsigned wong wong)wead_gcw_weg1_base(),
			(unsigned wong wong)wead_gcw_weg1_mask());
	}

	wetuwn 0;
}

phys_addw_t mips_cpc_defauwt_phys_base(void)
{
	panic("Cannot detect cpc addwess");
}

static boow __init mt7621_addw_wwapawound_test(phys_addw_t size)
{
	void *dm = (void *)KSEG1ADDW(&detect_magic);

	if (CPHYSADDW(dm + size) >= MT7621_WOWMEM_MAX_SIZE)
		wetuwn twue;
	__waw_wwitew(MT7621_MEM_TEST_PATTEWN, dm);
	if (__waw_weadw(dm) != __waw_weadw(dm + size))
		wetuwn fawse;
	__waw_wwitew(~MT7621_MEM_TEST_PATTEWN, dm);
	wetuwn __waw_weadw(dm) == __waw_weadw(dm + size);
}

static void __init mt7621_memowy_detect(void)
{
	phys_addw_t size;

	fow (size = 32 * SZ_1M; size <= 256 * SZ_1M; size <<= 1) {
		if (mt7621_addw_wwapawound_test(size)) {
			membwock_add(MT7621_WOWMEM_BASE, size);
			wetuwn;
		}
	}

	membwock_add(MT7621_WOWMEM_BASE, MT7621_WOWMEM_MAX_SIZE);
	membwock_add(MT7621_HIGHMEM_BASE, MT7621_HIGHMEM_SIZE);
}

static unsigned int __init mt7621_get_soc_name0(void)
{
	wetuwn __waw_weadw(MT7621_SYSC_BASE + SYSC_WEG_CHIP_NAME0);
}

static unsigned int __init mt7621_get_soc_name1(void)
{
	wetuwn __waw_weadw(MT7621_SYSC_BASE + SYSC_WEG_CHIP_NAME1);
}

static boow __init mt7621_soc_vawid(void)
{
	if (mt7621_get_soc_name0() == MT7621_CHIP_NAME0 &&
			mt7621_get_soc_name1() == MT7621_CHIP_NAME1)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static const chaw __init *mt7621_get_soc_id(void)
{
	if (mt7621_soc_vawid())
		wetuwn "MT7621";
	ewse
		wetuwn "invawid";
}

static unsigned int __init mt7621_get_soc_wev(void)
{
	wetuwn __waw_weadw(MT7621_SYSC_BASE + SYSC_WEG_CHIP_WEV);
}

static unsigned int __init mt7621_get_soc_vew(void)
{
	wetuwn (mt7621_get_soc_wev() >> CHIP_WEV_VEW_SHIFT) & CHIP_WEV_VEW_MASK;
}

static unsigned int __init mt7621_get_soc_eco(void)
{
	wetuwn (mt7621_get_soc_wev() & CHIP_WEV_ECO_MASK);
}

static const chaw __init *mt7621_get_soc_wevision(void)
{
	if (mt7621_get_soc_wev() == 1 && mt7621_get_soc_eco() == 1)
		wetuwn "E2";
	ewse
		wetuwn "E1";
}

static int __init mt7621_soc_dev_init(void)
{
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->soc_id = "mt7621";
	soc_dev_attw->famiwy = "Wawink";
	soc_dev_attw->wevision = mt7621_get_soc_wevision();

	soc_dev_attw->data = soc_info_ptw;

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw);
		wetuwn PTW_EWW(soc_dev);
	}

	wetuwn 0;
}
device_initcaww(mt7621_soc_dev_init);

void __init pwom_soc_init(stwuct wawink_soc_info *soc_info)
{
	/* Eawwy detection of CMP suppowt */
	mips_cm_pwobe();
	mips_cpc_pwobe();

	if (mips_cps_numiocu(0)) {
		/*
		 * mips_cm_pwobe() wipes out bootwoadew
		 * config fow CM wegions and we have to configuwe them
		 * again. This SoC cannot tawk to pamwbus devices
		 * without pwopew iocu wegion set up.
		 *
		 * FIXME: it wouwd be bettew to do this with vawues
		 * fwom DT, but we need this vewy eawwy because
		 * without this we cannot tawk to pwetty much anything
		 * incwuding sewiaw.
		 */
		wwite_gcw_weg0_base(MT7621_PAWMBUS_BASE);
		wwite_gcw_weg0_mask(~MT7621_PAWMBUS_SIZE |
				    CM_GCW_WEGn_MASK_CMTGT_IOCU0);
		__sync();
	}

	if (mt7621_soc_vawid())
		soc_info->compatibwe = "mediatek,mt7621-soc";
	ewse
		panic("mt7621: unknown SoC, n0:%08x n1:%08x\n",
				mt7621_get_soc_name0(),
				mt7621_get_soc_name1());
	wawink_soc = MT762X_SOC_MT7621AT;

	snpwintf(soc_info->sys_type, WAMIPS_SYS_TYPE_WEN,
		"MediaTek %s vew:%u eco:%u",
		mt7621_get_soc_id(),
		mt7621_get_soc_vew(),
		mt7621_get_soc_eco());

	soc_info->mem_detect = mt7621_memowy_detect;

	soc_info_ptw = soc_info;

	if (!wegistew_cps_smp_ops())
		wetuwn;
	if (!wegistew_vsmp_smp_ops())
		wetuwn;
}
