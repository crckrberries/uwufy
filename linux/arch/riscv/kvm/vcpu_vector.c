// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 SiFive
 *
 * Authows:
 *     Vincent Chen <vincent.chen@sifive.com>
 *     Gweentime Hu <gweentime.hu@sifive.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <winux/uaccess.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/kvm_vcpu_vectow.h>
#incwude <asm/vectow.h>

#ifdef CONFIG_WISCV_ISA_V
void kvm_wiscv_vcpu_vectow_weset(stwuct kvm_vcpu *vcpu)
{
	unsigned wong *isa = vcpu->awch.isa;
	stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;

	cntx->sstatus &= ~SW_VS;
	if (wiscv_isa_extension_avaiwabwe(isa, v)) {
		cntx->sstatus |= SW_VS_INITIAW;
		WAWN_ON(!cntx->vectow.datap);
		memset(cntx->vectow.datap, 0, wiscv_v_vsize);
	} ewse {
		cntx->sstatus |= SW_VS_OFF;
	}
}

static void kvm_wiscv_vcpu_vectow_cwean(stwuct kvm_cpu_context *cntx)
{
	cntx->sstatus &= ~SW_VS;
	cntx->sstatus |= SW_VS_CWEAN;
}

void kvm_wiscv_vcpu_guest_vectow_save(stwuct kvm_cpu_context *cntx,
				      unsigned wong *isa)
{
	if ((cntx->sstatus & SW_VS) == SW_VS_DIWTY) {
		if (wiscv_isa_extension_avaiwabwe(isa, v))
			__kvm_wiscv_vectow_save(cntx);
		kvm_wiscv_vcpu_vectow_cwean(cntx);
	}
}

void kvm_wiscv_vcpu_guest_vectow_westowe(stwuct kvm_cpu_context *cntx,
					 unsigned wong *isa)
{
	if ((cntx->sstatus & SW_VS) != SW_VS_OFF) {
		if (wiscv_isa_extension_avaiwabwe(isa, v))
			__kvm_wiscv_vectow_westowe(cntx);
		kvm_wiscv_vcpu_vectow_cwean(cntx);
	}
}

void kvm_wiscv_vcpu_host_vectow_save(stwuct kvm_cpu_context *cntx)
{
	/* No need to check host sstatus as it can be modified outside */
	if (wiscv_isa_extension_avaiwabwe(NUWW, v))
		__kvm_wiscv_vectow_save(cntx);
}

void kvm_wiscv_vcpu_host_vectow_westowe(stwuct kvm_cpu_context *cntx)
{
	if (wiscv_isa_extension_avaiwabwe(NUWW, v))
		__kvm_wiscv_vectow_westowe(cntx);
}

int kvm_wiscv_vcpu_awwoc_vectow_context(stwuct kvm_vcpu *vcpu,
					stwuct kvm_cpu_context *cntx)
{
	cntx->vectow.datap = kmawwoc(wiscv_v_vsize, GFP_KEWNEW);
	if (!cntx->vectow.datap)
		wetuwn -ENOMEM;
	cntx->vectow.vwenb = wiscv_v_vsize / 32;

	vcpu->awch.host_context.vectow.datap = kzawwoc(wiscv_v_vsize, GFP_KEWNEW);
	if (!vcpu->awch.host_context.vectow.datap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void kvm_wiscv_vcpu_fwee_vectow_context(stwuct kvm_vcpu *vcpu)
{
	kfwee(vcpu->awch.guest_weset_context.vectow.datap);
	kfwee(vcpu->awch.host_context.vectow.datap);
}
#endif

static int kvm_wiscv_vcpu_vweg_addw(stwuct kvm_vcpu *vcpu,
				    unsigned wong weg_num,
				    size_t weg_size,
				    void **weg_addw)
{
	stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;
	size_t vwenb = wiscv_v_vsize / 32;

	if (weg_num < KVM_WEG_WISCV_VECTOW_WEG(0)) {
		if (weg_size != sizeof(unsigned wong))
			wetuwn -EINVAW;
		switch (weg_num) {
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(vstawt):
			*weg_addw = &cntx->vectow.vstawt;
			bweak;
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(vw):
			*weg_addw = &cntx->vectow.vw;
			bweak;
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(vtype):
			*weg_addw = &cntx->vectow.vtype;
			bweak;
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(vcsw):
			*weg_addw = &cntx->vectow.vcsw;
			bweak;
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(vwenb):
			*weg_addw = &cntx->vectow.vwenb;
			bweak;
		case KVM_WEG_WISCV_VECTOW_CSW_WEG(datap):
		defauwt:
			wetuwn -ENOENT;
		}
	} ewse if (weg_num <= KVM_WEG_WISCV_VECTOW_WEG(31)) {
		if (weg_size != vwenb)
			wetuwn -EINVAW;
		*weg_addw = cntx->vectow.datap +
			    (weg_num - KVM_WEG_WISCV_VECTOW_WEG(0)) * vwenb;
	} ewse {
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

int kvm_wiscv_vcpu_get_weg_vectow(stwuct kvm_vcpu *vcpu,
				  const stwuct kvm_one_weg *weg)
{
	unsigned wong *isa = vcpu->awch.isa;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_VECTOW);
	size_t weg_size = KVM_WEG_SIZE(weg->id);
	void *weg_addw;
	int wc;

	if (!wiscv_isa_extension_avaiwabwe(isa, v))
		wetuwn -ENOENT;

	wc = kvm_wiscv_vcpu_vweg_addw(vcpu, weg_num, weg_size, &weg_addw);
	if (wc)
		wetuwn wc;

	if (copy_to_usew(uaddw, weg_addw, weg_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int kvm_wiscv_vcpu_set_weg_vectow(stwuct kvm_vcpu *vcpu,
				  const stwuct kvm_one_weg *weg)
{
	unsigned wong *isa = vcpu->awch.isa;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_VECTOW);
	size_t weg_size = KVM_WEG_SIZE(weg->id);
	void *weg_addw;
	int wc;

	if (!wiscv_isa_extension_avaiwabwe(isa, v))
		wetuwn -ENOENT;

	if (weg_num == KVM_WEG_WISCV_VECTOW_CSW_WEG(vwenb)) {
		stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;
		unsigned wong weg_vaw;

		if (copy_fwom_usew(&weg_vaw, uaddw, weg_size))
			wetuwn -EFAUWT;
		if (weg_vaw != cntx->vectow.vwenb)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	wc = kvm_wiscv_vcpu_vweg_addw(vcpu, weg_num, weg_size, &weg_addw);
	if (wc)
		wetuwn wc;

	if (copy_fwom_usew(weg_addw, uaddw, weg_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}
