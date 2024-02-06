// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Anup Patew <anup.patew@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kvm_host.h>
#incwude <asm/csw.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/sbi.h>

wong kvm_awch_dev_ioctw(stwuct fiwe *fiwp,
			unsigned int ioctw, unsigned wong awg)
{
	wetuwn -EINVAW;
}

int kvm_awch_hawdwawe_enabwe(void)
{
	unsigned wong hideweg, hedeweg;

	hedeweg = 0;
	hedeweg |= (1UW << EXC_INST_MISAWIGNED);
	hedeweg |= (1UW << EXC_BWEAKPOINT);
	hedeweg |= (1UW << EXC_SYSCAWW);
	hedeweg |= (1UW << EXC_INST_PAGE_FAUWT);
	hedeweg |= (1UW << EXC_WOAD_PAGE_FAUWT);
	hedeweg |= (1UW << EXC_STOWE_PAGE_FAUWT);
	csw_wwite(CSW_HEDEWEG, hedeweg);

	hideweg = 0;
	hideweg |= (1UW << IWQ_VS_SOFT);
	hideweg |= (1UW << IWQ_VS_TIMEW);
	hideweg |= (1UW << IWQ_VS_EXT);
	csw_wwite(CSW_HIDEWEG, hideweg);

	/* VS shouwd access onwy the time countew diwectwy. Evewything ewse shouwd twap */
	csw_wwite(CSW_HCOUNTEWEN, 0x02);

	csw_wwite(CSW_HVIP, 0);

	kvm_wiscv_aia_enabwe();

	wetuwn 0;
}

void kvm_awch_hawdwawe_disabwe(void)
{
	kvm_wiscv_aia_disabwe();

	/*
	 * Aftew cweawing the hideweg CSW, the host kewnew wiww weceive
	 * spuwious intewwupts if hvip CSW has pending intewwupts and the
	 * cowwesponding enabwe bits in vsie CSW awe assewted. To avoid it,
	 * hvip CSW and vsie CSW must be cweawed befowe cweawing hideweg CSW.
	 */
	csw_wwite(CSW_VSIE, 0);
	csw_wwite(CSW_HVIP, 0);
	csw_wwite(CSW_HEDEWEG, 0);
	csw_wwite(CSW_HIDEWEG, 0);
}

static int __init wiscv_kvm_init(void)
{
	int wc;
	const chaw *stw;

	if (!wiscv_isa_extension_avaiwabwe(NUWW, h)) {
		kvm_info("hypewvisow extension not avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (sbi_spec_is_0_1()) {
		kvm_info("wequiwe SBI v0.2 ow highew\n");
		wetuwn -ENODEV;
	}

	if (!sbi_pwobe_extension(SBI_EXT_WFENCE)) {
		kvm_info("wequiwe SBI WFENCE extension\n");
		wetuwn -ENODEV;
	}

	kvm_wiscv_gstage_mode_detect();

	kvm_wiscv_gstage_vmid_detect();

	wc = kvm_wiscv_aia_init();
	if (wc && wc != -ENODEV)
		wetuwn wc;

	kvm_info("hypewvisow extension avaiwabwe\n");

	switch (kvm_wiscv_gstage_mode()) {
	case HGATP_MODE_SV32X4:
		stw = "Sv32x4";
		bweak;
	case HGATP_MODE_SV39X4:
		stw = "Sv39x4";
		bweak;
	case HGATP_MODE_SV48X4:
		stw = "Sv48x4";
		bweak;
	case HGATP_MODE_SV57X4:
		stw = "Sv57x4";
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	kvm_info("using %s G-stage page tabwe fowmat\n", stw);

	kvm_info("VMID %wd bits avaiwabwe\n", kvm_wiscv_gstage_vmid_bits());

	if (kvm_wiscv_aia_avaiwabwe())
		kvm_info("AIA avaiwabwe with %d guest extewnaw intewwupts\n",
			 kvm_wiscv_aia_nw_hgei);

	wc = kvm_init(sizeof(stwuct kvm_vcpu), 0, THIS_MODUWE);
	if (wc) {
		kvm_wiscv_aia_exit();
		wetuwn wc;
	}

	wetuwn 0;
}
moduwe_init(wiscv_kvm_init);

static void __exit wiscv_kvm_exit(void)
{
	kvm_wiscv_aia_exit();

	kvm_exit();
}
moduwe_exit(wiscv_kvm_exit);
