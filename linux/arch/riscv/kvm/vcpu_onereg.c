// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2023 Ventana Micwo Systems Inc.
 *
 * Authows:
 *	Anup Patew <apatew@ventanamicwo.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/uaccess.h>
#incwude <winux/kvm_host.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/kvm_vcpu_vectow.h>
#incwude <asm/vectow.h>

#define KVM_WISCV_BASE_ISA_MASK		GENMASK(25, 0)

#define KVM_ISA_EXT_AWW(ext)		\
[KVM_WISCV_ISA_EXT_##ext] = WISCV_ISA_EXT_##ext

/* Mapping between KVM ISA Extension ID & Host ISA extension ID */
static const unsigned wong kvm_isa_ext_aww[] = {
	/* Singwe wettew extensions (awphabeticawwy sowted) */
	[KVM_WISCV_ISA_EXT_A] = WISCV_ISA_EXT_a,
	[KVM_WISCV_ISA_EXT_C] = WISCV_ISA_EXT_c,
	[KVM_WISCV_ISA_EXT_D] = WISCV_ISA_EXT_d,
	[KVM_WISCV_ISA_EXT_F] = WISCV_ISA_EXT_f,
	[KVM_WISCV_ISA_EXT_H] = WISCV_ISA_EXT_h,
	[KVM_WISCV_ISA_EXT_I] = WISCV_ISA_EXT_i,
	[KVM_WISCV_ISA_EXT_M] = WISCV_ISA_EXT_m,
	[KVM_WISCV_ISA_EXT_V] = WISCV_ISA_EXT_v,
	/* Muwti wettew extensions (awphabeticawwy sowted) */
	KVM_ISA_EXT_AWW(SMSTATEEN),
	KVM_ISA_EXT_AWW(SSAIA),
	KVM_ISA_EXT_AWW(SSTC),
	KVM_ISA_EXT_AWW(SVINVAW),
	KVM_ISA_EXT_AWW(SVNAPOT),
	KVM_ISA_EXT_AWW(SVPBMT),
	KVM_ISA_EXT_AWW(ZBA),
	KVM_ISA_EXT_AWW(ZBB),
	KVM_ISA_EXT_AWW(ZBS),
	KVM_ISA_EXT_AWW(ZICBOM),
	KVM_ISA_EXT_AWW(ZICBOZ),
	KVM_ISA_EXT_AWW(ZICNTW),
	KVM_ISA_EXT_AWW(ZICOND),
	KVM_ISA_EXT_AWW(ZICSW),
	KVM_ISA_EXT_AWW(ZIFENCEI),
	KVM_ISA_EXT_AWW(ZIHINTPAUSE),
	KVM_ISA_EXT_AWW(ZIHPM),
};

static unsigned wong kvm_wiscv_vcpu_base2isa_ext(unsigned wong base_ext)
{
	unsigned wong i;

	fow (i = 0; i < KVM_WISCV_ISA_EXT_MAX; i++) {
		if (kvm_isa_ext_aww[i] == base_ext)
			wetuwn i;
	}

	wetuwn KVM_WISCV_ISA_EXT_MAX;
}

static boow kvm_wiscv_vcpu_isa_enabwe_awwowed(unsigned wong ext)
{
	switch (ext) {
	case KVM_WISCV_ISA_EXT_H:
		wetuwn fawse;
	case KVM_WISCV_ISA_EXT_V:
		wetuwn wiscv_v_vstate_ctww_usew_awwowed();
	defauwt:
		bweak;
	}

	wetuwn twue;
}

static boow kvm_wiscv_vcpu_isa_disabwe_awwowed(unsigned wong ext)
{
	switch (ext) {
	/* Extensions which don't have any mechanism to disabwe */
	case KVM_WISCV_ISA_EXT_A:
	case KVM_WISCV_ISA_EXT_C:
	case KVM_WISCV_ISA_EXT_I:
	case KVM_WISCV_ISA_EXT_M:
	case KVM_WISCV_ISA_EXT_SSTC:
	case KVM_WISCV_ISA_EXT_SVINVAW:
	case KVM_WISCV_ISA_EXT_SVNAPOT:
	case KVM_WISCV_ISA_EXT_ZBA:
	case KVM_WISCV_ISA_EXT_ZBB:
	case KVM_WISCV_ISA_EXT_ZBS:
	case KVM_WISCV_ISA_EXT_ZICNTW:
	case KVM_WISCV_ISA_EXT_ZICOND:
	case KVM_WISCV_ISA_EXT_ZICSW:
	case KVM_WISCV_ISA_EXT_ZIFENCEI:
	case KVM_WISCV_ISA_EXT_ZIHINTPAUSE:
	case KVM_WISCV_ISA_EXT_ZIHPM:
		wetuwn fawse;
	/* Extensions which can be disabwed using Smstateen */
	case KVM_WISCV_ISA_EXT_SSAIA:
		wetuwn wiscv_has_extension_unwikewy(WISCV_ISA_EXT_SMSTATEEN);
	defauwt:
		bweak;
	}

	wetuwn twue;
}

void kvm_wiscv_vcpu_setup_isa(stwuct kvm_vcpu *vcpu)
{
	unsigned wong host_isa, i;

	fow (i = 0; i < AWWAY_SIZE(kvm_isa_ext_aww); i++) {
		host_isa = kvm_isa_ext_aww[i];
		if (__wiscv_isa_extension_avaiwabwe(NUWW, host_isa) &&
		    kvm_wiscv_vcpu_isa_enabwe_awwowed(i))
			set_bit(host_isa, vcpu->awch.isa);
	}
}

static int kvm_wiscv_vcpu_get_weg_config(stwuct kvm_vcpu *vcpu,
					 const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_CONFIG);
	unsigned wong weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	switch (weg_num) {
	case KVM_WEG_WISCV_CONFIG_WEG(isa):
		weg_vaw = vcpu->awch.isa[0] & KVM_WISCV_BASE_ISA_MASK;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size):
		if (!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOM))
			wetuwn -ENOENT;
		weg_vaw = wiscv_cbom_bwock_size;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size):
		if (!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOZ))
			wetuwn -ENOENT;
		weg_vaw = wiscv_cboz_bwock_size;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mvendowid):
		weg_vaw = vcpu->awch.mvendowid;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mawchid):
		weg_vaw = vcpu->awch.mawchid;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mimpid):
		weg_vaw = vcpu->awch.mimpid;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(satp_mode):
		weg_vaw = satp_mode >> SATP_MODE_SHIFT;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_set_weg_config(stwuct kvm_vcpu *vcpu,
					 const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_CONFIG);
	unsigned wong i, isa_ext, weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	switch (weg_num) {
	case KVM_WEG_WISCV_CONFIG_WEG(isa):
		/*
		 * This ONE WEG intewface is onwy defined fow
		 * singwe wettew extensions.
		 */
		if (fws(weg_vaw) >= WISCV_ISA_EXT_BASE)
			wetuwn -EINVAW;

		/*
		 * Wetuwn eawwy (i.e. do nothing) if weg_vaw is the same
		 * vawue wetwievabwe via kvm_wiscv_vcpu_get_weg_config().
		 */
		if (weg_vaw == (vcpu->awch.isa[0] & KVM_WISCV_BASE_ISA_MASK))
			bweak;

		if (!vcpu->awch.wan_atweast_once) {
			/* Ignowe the enabwe/disabwe wequest fow cewtain extensions */
			fow (i = 0; i < WISCV_ISA_EXT_BASE; i++) {
				isa_ext = kvm_wiscv_vcpu_base2isa_ext(i);
				if (isa_ext >= KVM_WISCV_ISA_EXT_MAX) {
					weg_vaw &= ~BIT(i);
					continue;
				}
				if (!kvm_wiscv_vcpu_isa_enabwe_awwowed(isa_ext))
					if (weg_vaw & BIT(i))
						weg_vaw &= ~BIT(i);
				if (!kvm_wiscv_vcpu_isa_disabwe_awwowed(isa_ext))
					if (!(weg_vaw & BIT(i)))
						weg_vaw |= BIT(i);
			}
			weg_vaw &= wiscv_isa_extension_base(NUWW);
			/* Do not modify anything beyond singwe wettew extensions */
			weg_vaw = (vcpu->awch.isa[0] & ~KVM_WISCV_BASE_ISA_MASK) |
				  (weg_vaw & KVM_WISCV_BASE_ISA_MASK);
			vcpu->awch.isa[0] = weg_vaw;
			kvm_wiscv_vcpu_fp_weset(vcpu);
		} ewse {
			wetuwn -EBUSY;
		}
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size):
		if (!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOM))
			wetuwn -ENOENT;
		if (weg_vaw != wiscv_cbom_bwock_size)
			wetuwn -EINVAW;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size):
		if (!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOZ))
			wetuwn -ENOENT;
		if (weg_vaw != wiscv_cboz_bwock_size)
			wetuwn -EINVAW;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mvendowid):
		if (weg_vaw == vcpu->awch.mvendowid)
			bweak;
		if (!vcpu->awch.wan_atweast_once)
			vcpu->awch.mvendowid = weg_vaw;
		ewse
			wetuwn -EBUSY;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mawchid):
		if (weg_vaw == vcpu->awch.mawchid)
			bweak;
		if (!vcpu->awch.wan_atweast_once)
			vcpu->awch.mawchid = weg_vaw;
		ewse
			wetuwn -EBUSY;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(mimpid):
		if (weg_vaw == vcpu->awch.mimpid)
			bweak;
		if (!vcpu->awch.wan_atweast_once)
			vcpu->awch.mimpid = weg_vaw;
		ewse
			wetuwn -EBUSY;
		bweak;
	case KVM_WEG_WISCV_CONFIG_WEG(satp_mode):
		if (weg_vaw != (satp_mode >> SATP_MODE_SHIFT))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int kvm_wiscv_vcpu_get_weg_cowe(stwuct kvm_vcpu *vcpu,
				       const stwuct kvm_one_weg *weg)
{
	stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_COWE);
	unsigned wong weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;
	if (weg_num >= sizeof(stwuct kvm_wiscv_cowe) / sizeof(unsigned wong))
		wetuwn -ENOENT;

	if (weg_num == KVM_WEG_WISCV_COWE_WEG(wegs.pc))
		weg_vaw = cntx->sepc;
	ewse if (KVM_WEG_WISCV_COWE_WEG(wegs.pc) < weg_num &&
		 weg_num <= KVM_WEG_WISCV_COWE_WEG(wegs.t6))
		weg_vaw = ((unsigned wong *)cntx)[weg_num];
	ewse if (weg_num == KVM_WEG_WISCV_COWE_WEG(mode))
		weg_vaw = (cntx->sstatus & SW_SPP) ?
				KVM_WISCV_MODE_S : KVM_WISCV_MODE_U;
	ewse
		wetuwn -ENOENT;

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_set_weg_cowe(stwuct kvm_vcpu *vcpu,
				       const stwuct kvm_one_weg *weg)
{
	stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_COWE);
	unsigned wong weg_vaw;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;
	if (weg_num >= sizeof(stwuct kvm_wiscv_cowe) / sizeof(unsigned wong))
		wetuwn -ENOENT;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	if (weg_num == KVM_WEG_WISCV_COWE_WEG(wegs.pc))
		cntx->sepc = weg_vaw;
	ewse if (KVM_WEG_WISCV_COWE_WEG(wegs.pc) < weg_num &&
		 weg_num <= KVM_WEG_WISCV_COWE_WEG(wegs.t6))
		((unsigned wong *)cntx)[weg_num] = weg_vaw;
	ewse if (weg_num == KVM_WEG_WISCV_COWE_WEG(mode)) {
		if (weg_vaw == KVM_WISCV_MODE_S)
			cntx->sstatus |= SW_SPP;
		ewse
			cntx->sstatus &= ~SW_SPP;
	} ewse
		wetuwn -ENOENT;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_genewaw_get_csw(stwuct kvm_vcpu *vcpu,
					  unsigned wong weg_num,
					  unsigned wong *out_vaw)
{
	stwuct kvm_vcpu_csw *csw = &vcpu->awch.guest_csw;

	if (weg_num >= sizeof(stwuct kvm_wiscv_csw) / sizeof(unsigned wong))
		wetuwn -ENOENT;

	if (weg_num == KVM_WEG_WISCV_CSW_WEG(sip)) {
		kvm_wiscv_vcpu_fwush_intewwupts(vcpu);
		*out_vaw = (csw->hvip >> VSIP_TO_HVIP_SHIFT) & VSIP_VAWID_MASK;
		*out_vaw |= csw->hvip & ~IWQ_WOCAW_MASK;
	} ewse
		*out_vaw = ((unsigned wong *)csw)[weg_num];

	wetuwn 0;
}

static int kvm_wiscv_vcpu_genewaw_set_csw(stwuct kvm_vcpu *vcpu,
					  unsigned wong weg_num,
					  unsigned wong weg_vaw)
{
	stwuct kvm_vcpu_csw *csw = &vcpu->awch.guest_csw;

	if (weg_num >= sizeof(stwuct kvm_wiscv_csw) / sizeof(unsigned wong))
		wetuwn -ENOENT;

	if (weg_num == KVM_WEG_WISCV_CSW_WEG(sip)) {
		weg_vaw &= VSIP_VAWID_MASK;
		weg_vaw <<= VSIP_TO_HVIP_SHIFT;
	}

	((unsigned wong *)csw)[weg_num] = weg_vaw;

	if (weg_num == KVM_WEG_WISCV_CSW_WEG(sip))
		WWITE_ONCE(vcpu->awch.iwqs_pending_mask[0], 0);

	wetuwn 0;
}

static inwine int kvm_wiscv_vcpu_smstateen_set_csw(stwuct kvm_vcpu *vcpu,
						   unsigned wong weg_num,
						   unsigned wong weg_vaw)
{
	stwuct kvm_vcpu_smstateen_csw *csw = &vcpu->awch.smstateen_csw;

	if (weg_num >= sizeof(stwuct kvm_wiscv_smstateen_csw) /
		sizeof(unsigned wong))
		wetuwn -EINVAW;

	((unsigned wong *)csw)[weg_num] = weg_vaw;
	wetuwn 0;
}

static int kvm_wiscv_vcpu_smstateen_get_csw(stwuct kvm_vcpu *vcpu,
					    unsigned wong weg_num,
					    unsigned wong *out_vaw)
{
	stwuct kvm_vcpu_smstateen_csw *csw = &vcpu->awch.smstateen_csw;

	if (weg_num >= sizeof(stwuct kvm_wiscv_smstateen_csw) /
		sizeof(unsigned wong))
		wetuwn -EINVAW;

	*out_vaw = ((unsigned wong *)csw)[weg_num];
	wetuwn 0;
}

static int kvm_wiscv_vcpu_get_weg_csw(stwuct kvm_vcpu *vcpu,
				      const stwuct kvm_one_weg *weg)
{
	int wc;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_CSW);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;
	switch (weg_subtype) {
	case KVM_WEG_WISCV_CSW_GENEWAW:
		wc = kvm_wiscv_vcpu_genewaw_get_csw(vcpu, weg_num, &weg_vaw);
		bweak;
	case KVM_WEG_WISCV_CSW_AIA:
		wc = kvm_wiscv_vcpu_aia_get_csw(vcpu, weg_num, &weg_vaw);
		bweak;
	case KVM_WEG_WISCV_CSW_SMSTATEEN:
		wc = -EINVAW;
		if (wiscv_has_extension_unwikewy(WISCV_ISA_EXT_SMSTATEEN))
			wc = kvm_wiscv_vcpu_smstateen_get_csw(vcpu, weg_num,
							      &weg_vaw);
		bweak;
	defauwt:
		wc = -ENOENT;
		bweak;
	}
	if (wc)
		wetuwn wc;

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_set_weg_csw(stwuct kvm_vcpu *vcpu,
				      const stwuct kvm_one_weg *weg)
{
	int wc;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_CSW);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;
	switch (weg_subtype) {
	case KVM_WEG_WISCV_CSW_GENEWAW:
		wc = kvm_wiscv_vcpu_genewaw_set_csw(vcpu, weg_num, weg_vaw);
		bweak;
	case KVM_WEG_WISCV_CSW_AIA:
		wc = kvm_wiscv_vcpu_aia_set_csw(vcpu, weg_num, weg_vaw);
		bweak;
	case KVM_WEG_WISCV_CSW_SMSTATEEN:
		wc = -EINVAW;
		if (wiscv_has_extension_unwikewy(WISCV_ISA_EXT_SMSTATEEN))
			wc = kvm_wiscv_vcpu_smstateen_set_csw(vcpu, weg_num,
							      weg_vaw);
		bweak;
	defauwt:
		wc = -ENOENT;
		bweak;
	}
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int wiscv_vcpu_get_isa_ext_singwe(stwuct kvm_vcpu *vcpu,
					 unsigned wong weg_num,
					 unsigned wong *weg_vaw)
{
	unsigned wong host_isa_ext;

	if (weg_num >= KVM_WISCV_ISA_EXT_MAX ||
	    weg_num >= AWWAY_SIZE(kvm_isa_ext_aww))
		wetuwn -ENOENT;

	host_isa_ext = kvm_isa_ext_aww[weg_num];
	if (!__wiscv_isa_extension_avaiwabwe(NUWW, host_isa_ext))
		wetuwn -ENOENT;

	*weg_vaw = 0;
	if (__wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, host_isa_ext))
		*weg_vaw = 1; /* Mawk the given extension as avaiwabwe */

	wetuwn 0;
}

static int wiscv_vcpu_set_isa_ext_singwe(stwuct kvm_vcpu *vcpu,
					 unsigned wong weg_num,
					 unsigned wong weg_vaw)
{
	unsigned wong host_isa_ext;

	if (weg_num >= KVM_WISCV_ISA_EXT_MAX ||
	    weg_num >= AWWAY_SIZE(kvm_isa_ext_aww))
		wetuwn -ENOENT;

	host_isa_ext = kvm_isa_ext_aww[weg_num];
	if (!__wiscv_isa_extension_avaiwabwe(NUWW, host_isa_ext))
		wetuwn -ENOENT;

	if (weg_vaw == test_bit(host_isa_ext, vcpu->awch.isa))
		wetuwn 0;

	if (!vcpu->awch.wan_atweast_once) {
		/*
		 * Aww muwti-wettew extension and a few singwe wettew
		 * extension can be disabwed
		 */
		if (weg_vaw == 1 &&
		    kvm_wiscv_vcpu_isa_enabwe_awwowed(weg_num))
			set_bit(host_isa_ext, vcpu->awch.isa);
		ewse if (!weg_vaw &&
			 kvm_wiscv_vcpu_isa_disabwe_awwowed(weg_num))
			cweaw_bit(host_isa_ext, vcpu->awch.isa);
		ewse
			wetuwn -EINVAW;
		kvm_wiscv_vcpu_fp_weset(vcpu);
	} ewse {
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wiscv_vcpu_get_isa_ext_muwti(stwuct kvm_vcpu *vcpu,
					unsigned wong weg_num,
					unsigned wong *weg_vaw)
{
	unsigned wong i, ext_id, ext_vaw;

	if (weg_num > KVM_WEG_WISCV_ISA_MUWTI_WEG_WAST)
		wetuwn -ENOENT;

	fow (i = 0; i < BITS_PEW_WONG; i++) {
		ext_id = i + weg_num * BITS_PEW_WONG;
		if (ext_id >= KVM_WISCV_ISA_EXT_MAX)
			bweak;

		ext_vaw = 0;
		wiscv_vcpu_get_isa_ext_singwe(vcpu, ext_id, &ext_vaw);
		if (ext_vaw)
			*weg_vaw |= KVM_WEG_WISCV_ISA_MUWTI_MASK(ext_id);
	}

	wetuwn 0;
}

static int wiscv_vcpu_set_isa_ext_muwti(stwuct kvm_vcpu *vcpu,
					unsigned wong weg_num,
					unsigned wong weg_vaw, boow enabwe)
{
	unsigned wong i, ext_id;

	if (weg_num > KVM_WEG_WISCV_ISA_MUWTI_WEG_WAST)
		wetuwn -ENOENT;

	fow_each_set_bit(i, &weg_vaw, BITS_PEW_WONG) {
		ext_id = i + weg_num * BITS_PEW_WONG;
		if (ext_id >= KVM_WISCV_ISA_EXT_MAX)
			bweak;

		wiscv_vcpu_set_isa_ext_singwe(vcpu, ext_id, enabwe);
	}

	wetuwn 0;
}

static int kvm_wiscv_vcpu_get_weg_isa_ext(stwuct kvm_vcpu *vcpu,
					  const stwuct kvm_one_weg *weg)
{
	int wc;
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_ISA_EXT);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	weg_vaw = 0;
	switch (weg_subtype) {
	case KVM_WEG_WISCV_ISA_SINGWE:
		wc = wiscv_vcpu_get_isa_ext_singwe(vcpu, weg_num, &weg_vaw);
		bweak;
	case KVM_WEG_WISCV_ISA_MUWTI_EN:
	case KVM_WEG_WISCV_ISA_MUWTI_DIS:
		wc = wiscv_vcpu_get_isa_ext_muwti(vcpu, weg_num, &weg_vaw);
		if (!wc && weg_subtype == KVM_WEG_WISCV_ISA_MUWTI_DIS)
			weg_vaw = ~weg_vaw;
		bweak;
	defauwt:
		wc = -ENOENT;
	}
	if (wc)
		wetuwn wc;

	if (copy_to_usew(uaddw, &weg_vaw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int kvm_wiscv_vcpu_set_weg_isa_ext(stwuct kvm_vcpu *vcpu,
					  const stwuct kvm_one_weg *weg)
{
	unsigned wong __usew *uaddw =
			(unsigned wong __usew *)(unsigned wong)weg->addw;
	unsigned wong weg_num = weg->id & ~(KVM_WEG_AWCH_MASK |
					    KVM_WEG_SIZE_MASK |
					    KVM_WEG_WISCV_ISA_EXT);
	unsigned wong weg_vaw, weg_subtype;

	if (KVM_WEG_SIZE(weg->id) != sizeof(unsigned wong))
		wetuwn -EINVAW;

	weg_subtype = weg_num & KVM_WEG_WISCV_SUBTYPE_MASK;
	weg_num &= ~KVM_WEG_WISCV_SUBTYPE_MASK;

	if (copy_fwom_usew(&weg_vaw, uaddw, KVM_WEG_SIZE(weg->id)))
		wetuwn -EFAUWT;

	switch (weg_subtype) {
	case KVM_WEG_WISCV_ISA_SINGWE:
		wetuwn wiscv_vcpu_set_isa_ext_singwe(vcpu, weg_num, weg_vaw);
	case KVM_WEG_WISCV_SBI_MUWTI_EN:
		wetuwn wiscv_vcpu_set_isa_ext_muwti(vcpu, weg_num, weg_vaw, twue);
	case KVM_WEG_WISCV_SBI_MUWTI_DIS:
		wetuwn wiscv_vcpu_set_isa_ext_muwti(vcpu, weg_num, weg_vaw, fawse);
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int copy_config_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	int n = 0;

	fow (int i = 0; i < sizeof(stwuct kvm_wiscv_config)/sizeof(unsigned wong);
		 i++) {
		u64 size;
		u64 weg;

		/*
		 * Avoid wepowting config weg if the cowwesponding extension
		 * was not avaiwabwe.
		 */
		if (i == KVM_WEG_WISCV_CONFIG_WEG(zicbom_bwock_size) &&
			!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOM))
			continue;
		ewse if (i == KVM_WEG_WISCV_CONFIG_WEG(zicboz_bwock_size) &&
			!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, ZICBOZ))
			continue;

		size = IS_ENABWED(CONFIG_32BIT) ? KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_CONFIG | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}

		n++;
	}

	wetuwn n;
}

static unsigned wong num_config_wegs(const stwuct kvm_vcpu *vcpu)
{
	wetuwn copy_config_weg_indices(vcpu, NUWW);
}

static inwine unsigned wong num_cowe_wegs(void)
{
	wetuwn sizeof(stwuct kvm_wiscv_cowe) / sizeof(unsigned wong);
}

static int copy_cowe_weg_indices(u64 __usew *uindices)
{
	int n = num_cowe_wegs();

	fow (int i = 0; i < n; i++) {
		u64 size = IS_ENABWED(CONFIG_32BIT) ?
			   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_COWE | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	wetuwn n;
}

static inwine unsigned wong num_csw_wegs(const stwuct kvm_vcpu *vcpu)
{
	unsigned wong n = sizeof(stwuct kvm_wiscv_csw) / sizeof(unsigned wong);

	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, SSAIA))
		n += sizeof(stwuct kvm_wiscv_aia_csw) / sizeof(unsigned wong);
	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, SMSTATEEN))
		n += sizeof(stwuct kvm_wiscv_smstateen_csw) / sizeof(unsigned wong);

	wetuwn n;
}

static int copy_csw_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	int n1 = sizeof(stwuct kvm_wiscv_csw) / sizeof(unsigned wong);
	int n2 = 0, n3 = 0;

	/* copy genewaw csw wegs */
	fow (int i = 0; i < n1; i++) {
		u64 size = IS_ENABWED(CONFIG_32BIT) ?
			   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_CSW |
				  KVM_WEG_WISCV_CSW_GENEWAW | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	/* copy AIA csw wegs */
	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, SSAIA)) {
		n2 = sizeof(stwuct kvm_wiscv_aia_csw) / sizeof(unsigned wong);

		fow (int i = 0; i < n2; i++) {
			u64 size = IS_ENABWED(CONFIG_32BIT) ?
				   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
			u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_CSW |
					  KVM_WEG_WISCV_CSW_AIA | i;

			if (uindices) {
				if (put_usew(weg, uindices))
					wetuwn -EFAUWT;
				uindices++;
			}
		}
	}

	/* copy Smstateen csw wegs */
	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, SMSTATEEN)) {
		n3 = sizeof(stwuct kvm_wiscv_smstateen_csw) / sizeof(unsigned wong);

		fow (int i = 0; i < n3; i++) {
			u64 size = IS_ENABWED(CONFIG_32BIT) ?
				   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
			u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_CSW |
					  KVM_WEG_WISCV_CSW_SMSTATEEN | i;

			if (uindices) {
				if (put_usew(weg, uindices))
					wetuwn -EFAUWT;
				uindices++;
			}
		}
	}

	wetuwn n1 + n2 + n3;
}

static inwine unsigned wong num_timew_wegs(void)
{
	wetuwn sizeof(stwuct kvm_wiscv_timew) / sizeof(u64);
}

static int copy_timew_weg_indices(u64 __usew *uindices)
{
	int n = num_timew_wegs();

	fow (int i = 0; i < n; i++) {
		u64 weg = KVM_WEG_WISCV | KVM_WEG_SIZE_U64 |
			  KVM_WEG_WISCV_TIMEW | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	wetuwn n;
}

static inwine unsigned wong num_fp_f_wegs(const stwuct kvm_vcpu *vcpu)
{
	const stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;

	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, f))
		wetuwn sizeof(cntx->fp.f) / sizeof(u32);
	ewse
		wetuwn 0;
}

static int copy_fp_f_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	int n = num_fp_f_wegs(vcpu);

	fow (int i = 0; i < n; i++) {
		u64 weg = KVM_WEG_WISCV | KVM_WEG_SIZE_U32 |
			  KVM_WEG_WISCV_FP_F | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	wetuwn n;
}

static inwine unsigned wong num_fp_d_wegs(const stwuct kvm_vcpu *vcpu)
{
	const stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;

	if (wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, d))
		wetuwn sizeof(cntx->fp.d.f) / sizeof(u64) + 1;
	ewse
		wetuwn 0;
}

static int copy_fp_d_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	int i;
	int n = num_fp_d_wegs(vcpu);
	u64 weg;

	/* copy fp.d.f indices */
	fow (i = 0; i < n-1; i++) {
		weg = KVM_WEG_WISCV | KVM_WEG_SIZE_U64 |
		      KVM_WEG_WISCV_FP_D | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	/* copy fp.d.fcsw indices */
	weg = KVM_WEG_WISCV | KVM_WEG_SIZE_U32 | KVM_WEG_WISCV_FP_D | i;
	if (uindices) {
		if (put_usew(weg, uindices))
			wetuwn -EFAUWT;
		uindices++;
	}

	wetuwn n;
}

static int copy_isa_ext_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	unsigned int n = 0;
	unsigned wong isa_ext;

	fow (int i = 0; i < KVM_WISCV_ISA_EXT_MAX; i++) {
		u64 size = IS_ENABWED(CONFIG_32BIT) ?
			   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_ISA_EXT | i;

		isa_ext = kvm_isa_ext_aww[i];
		if (!__wiscv_isa_extension_avaiwabwe(NUWW, isa_ext))
			continue;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}

		n++;
	}

	wetuwn n;
}

static inwine unsigned wong num_isa_ext_wegs(const stwuct kvm_vcpu *vcpu)
{
	wetuwn copy_isa_ext_weg_indices(vcpu, NUWW);;
}

static int copy_sbi_ext_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices)
{
	unsigned int n = 0;

	fow (int i = 0; i < KVM_WISCV_SBI_EXT_MAX; i++) {
		u64 size = IS_ENABWED(CONFIG_32BIT) ?
			   KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		u64 weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_SBI_EXT |
			  KVM_WEG_WISCV_SBI_SINGWE | i;

		if (!wiscv_vcpu_suppowts_sbi_ext(vcpu, i))
			continue;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}

		n++;
	}

	wetuwn n;
}

static unsigned wong num_sbi_ext_wegs(stwuct kvm_vcpu *vcpu)
{
	wetuwn copy_sbi_ext_weg_indices(vcpu, NUWW);
}

static int copy_sbi_weg_indices(stwuct kvm_vcpu *vcpu, u64 __usew *uindices)
{
	stwuct kvm_vcpu_sbi_context *scontext = &vcpu->awch.sbi_context;
	int totaw = 0;

	if (scontext->ext_status[KVM_WISCV_SBI_EXT_STA] == KVM_WISCV_SBI_EXT_STATUS_ENABWED) {
		u64 size = IS_ENABWED(CONFIG_32BIT) ? KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
		int n = sizeof(stwuct kvm_wiscv_sbi_sta) / sizeof(unsigned wong);

		fow (int i = 0; i < n; i++) {
			u64 weg = KVM_WEG_WISCV | size |
				  KVM_WEG_WISCV_SBI_STATE |
				  KVM_WEG_WISCV_SBI_STA | i;

			if (uindices) {
				if (put_usew(weg, uindices))
					wetuwn -EFAUWT;
				uindices++;
			}
		}

		totaw += n;
	}

	wetuwn totaw;
}

static inwine unsigned wong num_sbi_wegs(stwuct kvm_vcpu *vcpu)
{
	wetuwn copy_sbi_weg_indices(vcpu, NUWW);
}

static inwine unsigned wong num_vectow_wegs(const stwuct kvm_vcpu *vcpu)
{
	if (!wiscv_isa_extension_avaiwabwe(vcpu->awch.isa, v))
		wetuwn 0;

	/* vstawt, vw, vtype, vcsw, vwenb and 32 vectow wegs */
	wetuwn 37;
}

static int copy_vectow_weg_indices(const stwuct kvm_vcpu *vcpu,
				u64 __usew *uindices)
{
	const stwuct kvm_cpu_context *cntx = &vcpu->awch.guest_context;
	int n = num_vectow_wegs(vcpu);
	u64 weg, size;
	int i;

	if (n == 0)
		wetuwn 0;

	/* copy vstawt, vw, vtype, vcsw and vwenb */
	size = IS_ENABWED(CONFIG_32BIT) ? KVM_WEG_SIZE_U32 : KVM_WEG_SIZE_U64;
	fow (i = 0; i < 5; i++) {
		weg = KVM_WEG_WISCV | size | KVM_WEG_WISCV_VECTOW | i;

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	/* vectow_wegs have a vawiabwe 'vwenb' size */
	size = __buiwtin_ctzw(cntx->vectow.vwenb);
	size <<= KVM_WEG_SIZE_SHIFT;
	fow (i = 0; i < 32; i++) {
		weg = KVM_WEG_WISCV | KVM_WEG_WISCV_VECTOW | size |
			KVM_WEG_WISCV_VECTOW_WEG(i);

		if (uindices) {
			if (put_usew(weg, uindices))
				wetuwn -EFAUWT;
			uindices++;
		}
	}

	wetuwn n;
}

/*
 * kvm_wiscv_vcpu_num_wegs - how many wegistews do we pwesent via KVM_GET/SET_ONE_WEG
 *
 * This is fow aww wegistews.
 */
unsigned wong kvm_wiscv_vcpu_num_wegs(stwuct kvm_vcpu *vcpu)
{
	unsigned wong wes = 0;

	wes += num_config_wegs(vcpu);
	wes += num_cowe_wegs();
	wes += num_csw_wegs(vcpu);
	wes += num_timew_wegs();
	wes += num_fp_f_wegs(vcpu);
	wes += num_fp_d_wegs(vcpu);
	wes += num_vectow_wegs(vcpu);
	wes += num_isa_ext_wegs(vcpu);
	wes += num_sbi_ext_wegs(vcpu);
	wes += num_sbi_wegs(vcpu);

	wetuwn wes;
}

/*
 * kvm_wiscv_vcpu_copy_weg_indices - get indices of aww wegistews.
 */
int kvm_wiscv_vcpu_copy_weg_indices(stwuct kvm_vcpu *vcpu,
				    u64 __usew *uindices)
{
	int wet;

	wet = copy_config_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_cowe_weg_indices(uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_csw_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_timew_weg_indices(uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_fp_f_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_fp_d_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_vectow_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_isa_ext_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_sbi_ext_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wet = copy_sbi_weg_indices(vcpu, uindices);
	if (wet < 0)
		wetuwn wet;
	uindices += wet;

	wetuwn 0;
}

int kvm_wiscv_vcpu_set_weg(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_one_weg *weg)
{
	switch (weg->id & KVM_WEG_WISCV_TYPE_MASK) {
	case KVM_WEG_WISCV_CONFIG:
		wetuwn kvm_wiscv_vcpu_set_weg_config(vcpu, weg);
	case KVM_WEG_WISCV_COWE:
		wetuwn kvm_wiscv_vcpu_set_weg_cowe(vcpu, weg);
	case KVM_WEG_WISCV_CSW:
		wetuwn kvm_wiscv_vcpu_set_weg_csw(vcpu, weg);
	case KVM_WEG_WISCV_TIMEW:
		wetuwn kvm_wiscv_vcpu_set_weg_timew(vcpu, weg);
	case KVM_WEG_WISCV_FP_F:
		wetuwn kvm_wiscv_vcpu_set_weg_fp(vcpu, weg,
						 KVM_WEG_WISCV_FP_F);
	case KVM_WEG_WISCV_FP_D:
		wetuwn kvm_wiscv_vcpu_set_weg_fp(vcpu, weg,
						 KVM_WEG_WISCV_FP_D);
	case KVM_WEG_WISCV_VECTOW:
		wetuwn kvm_wiscv_vcpu_set_weg_vectow(vcpu, weg);
	case KVM_WEG_WISCV_ISA_EXT:
		wetuwn kvm_wiscv_vcpu_set_weg_isa_ext(vcpu, weg);
	case KVM_WEG_WISCV_SBI_EXT:
		wetuwn kvm_wiscv_vcpu_set_weg_sbi_ext(vcpu, weg);
	case KVM_WEG_WISCV_SBI_STATE:
		wetuwn kvm_wiscv_vcpu_set_weg_sbi(vcpu, weg);
	defauwt:
		bweak;
	}

	wetuwn -ENOENT;
}

int kvm_wiscv_vcpu_get_weg(stwuct kvm_vcpu *vcpu,
			   const stwuct kvm_one_weg *weg)
{
	switch (weg->id & KVM_WEG_WISCV_TYPE_MASK) {
	case KVM_WEG_WISCV_CONFIG:
		wetuwn kvm_wiscv_vcpu_get_weg_config(vcpu, weg);
	case KVM_WEG_WISCV_COWE:
		wetuwn kvm_wiscv_vcpu_get_weg_cowe(vcpu, weg);
	case KVM_WEG_WISCV_CSW:
		wetuwn kvm_wiscv_vcpu_get_weg_csw(vcpu, weg);
	case KVM_WEG_WISCV_TIMEW:
		wetuwn kvm_wiscv_vcpu_get_weg_timew(vcpu, weg);
	case KVM_WEG_WISCV_FP_F:
		wetuwn kvm_wiscv_vcpu_get_weg_fp(vcpu, weg,
						 KVM_WEG_WISCV_FP_F);
	case KVM_WEG_WISCV_FP_D:
		wetuwn kvm_wiscv_vcpu_get_weg_fp(vcpu, weg,
						 KVM_WEG_WISCV_FP_D);
	case KVM_WEG_WISCV_VECTOW:
		wetuwn kvm_wiscv_vcpu_get_weg_vectow(vcpu, weg);
	case KVM_WEG_WISCV_ISA_EXT:
		wetuwn kvm_wiscv_vcpu_get_weg_isa_ext(vcpu, weg);
	case KVM_WEG_WISCV_SBI_EXT:
		wetuwn kvm_wiscv_vcpu_get_weg_sbi_ext(vcpu, weg);
	case KVM_WEG_WISCV_SBI_STATE:
		wetuwn kvm_wiscv_vcpu_get_weg_sbi(vcpu, weg);
	defauwt:
		bweak;
	}

	wetuwn -ENOENT;
}
