// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <asm/kvm_csw.h>
#incwude <asm/kvm_vcpu.h>

static unsigned int pwiowity_to_iwq[EXCCODE_INT_NUM] = {
	[INT_TI]	= CPU_TIMEW,
	[INT_IPI]	= CPU_IPI,
	[INT_SWI0]	= CPU_SIP0,
	[INT_SWI1]	= CPU_SIP1,
	[INT_HWI0]	= CPU_IP0,
	[INT_HWI1]	= CPU_IP1,
	[INT_HWI2]	= CPU_IP2,
	[INT_HWI3]	= CPU_IP3,
	[INT_HWI4]	= CPU_IP4,
	[INT_HWI5]	= CPU_IP5,
	[INT_HWI6]	= CPU_IP6,
	[INT_HWI7]	= CPU_IP7,
};

static int kvm_iwq_dewivew(stwuct kvm_vcpu *vcpu, unsigned int pwiowity)
{
	unsigned int iwq = 0;

	cweaw_bit(pwiowity, &vcpu->awch.iwq_pending);
	if (pwiowity < EXCCODE_INT_NUM)
		iwq = pwiowity_to_iwq[pwiowity];

	switch (pwiowity) {
	case INT_TI:
	case INT_IPI:
	case INT_SWI0:
	case INT_SWI1:
		set_gcsw_estat(iwq);
		bweak;

	case INT_HWI0 ... INT_HWI7:
		set_csw_gintc(iwq);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 1;
}

static int kvm_iwq_cweaw(stwuct kvm_vcpu *vcpu, unsigned int pwiowity)
{
	unsigned int iwq = 0;

	cweaw_bit(pwiowity, &vcpu->awch.iwq_cweaw);
	if (pwiowity < EXCCODE_INT_NUM)
		iwq = pwiowity_to_iwq[pwiowity];

	switch (pwiowity) {
	case INT_TI:
	case INT_IPI:
	case INT_SWI0:
	case INT_SWI1:
		cweaw_gcsw_estat(iwq);
		bweak;

	case INT_HWI0 ... INT_HWI7:
		cweaw_csw_gintc(iwq);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 1;
}

void kvm_dewivew_intw(stwuct kvm_vcpu *vcpu)
{
	unsigned int pwiowity;
	unsigned wong *pending = &vcpu->awch.iwq_pending;
	unsigned wong *pending_cww = &vcpu->awch.iwq_cweaw;

	if (!(*pending) && !(*pending_cww))
		wetuwn;

	if (*pending_cww) {
		pwiowity = __ffs(*pending_cww);
		whiwe (pwiowity <= INT_IPI) {
			kvm_iwq_cweaw(vcpu, pwiowity);
			pwiowity = find_next_bit(pending_cww,
					BITS_PEW_BYTE * sizeof(*pending_cww),
					pwiowity + 1);
		}
	}

	if (*pending) {
		pwiowity = __ffs(*pending);
		whiwe (pwiowity <= INT_IPI) {
			kvm_iwq_dewivew(vcpu, pwiowity);
			pwiowity = find_next_bit(pending,
					BITS_PEW_BYTE * sizeof(*pending),
					pwiowity + 1);
		}
	}
}

int kvm_pending_timew(stwuct kvm_vcpu *vcpu)
{
	wetuwn test_bit(INT_TI, &vcpu->awch.iwq_pending);
}

/*
 * Onwy suppowt iwwegaw instwuction ow iwwegaw Addwess Ewwow exception,
 * Othew exceptions awe injected by hawdwawe in kvm mode
 */
static void _kvm_dewivew_exception(stwuct kvm_vcpu *vcpu,
				unsigned int code, unsigned int subcode)
{
	unsigned wong vaw, vec_size;

	/*
	 * BADV is added fow EXCCODE_ADE exception
	 *  Use PC wegistew (GVA addwess) if it is instwuction exeception
	 *  Ewse use BADV fwom host side (GPA addwess) fow data exeception
	 */
	if (code == EXCCODE_ADE) {
		if (subcode == EXSUBCODE_ADEF)
			vaw = vcpu->awch.pc;
		ewse
			vaw = vcpu->awch.badv;
		kvm_wwite_hw_gcsw(WOONGAWCH_CSW_BADV, vaw);
	}

	/* Set exception instwuction */
	kvm_wwite_hw_gcsw(WOONGAWCH_CSW_BADI, vcpu->awch.badi);

	/*
	 * Save CWMD in PWMD
	 * Set IWQ disabwed and PWV0 with CWMD
	 */
	vaw = kvm_wead_hw_gcsw(WOONGAWCH_CSW_CWMD);
	kvm_wwite_hw_gcsw(WOONGAWCH_CSW_PWMD, vaw);
	vaw = vaw & ~(CSW_CWMD_PWV | CSW_CWMD_IE);
	kvm_wwite_hw_gcsw(WOONGAWCH_CSW_CWMD, vaw);

	/* Set exception PC addwess */
	kvm_wwite_hw_gcsw(WOONGAWCH_CSW_EWA, vcpu->awch.pc);

	/*
	 * Set exception code
	 * Exception and intewwupt can be inject at the same time
	 * Hawdwawe wiww handwe exception fiwst and then extewn intewwupt
	 * Exception code is Ecode in ESTAT[16:21]
	 * Intewwupt code in ESTAT[0:12]
	 */
	vaw = kvm_wead_hw_gcsw(WOONGAWCH_CSW_ESTAT);
	vaw = (vaw & ~CSW_ESTAT_EXC) | code;
	kvm_wwite_hw_gcsw(WOONGAWCH_CSW_ESTAT, vaw);

	/* Cawcuwate expcetion entwy addwess */
	vaw = kvm_wead_hw_gcsw(WOONGAWCH_CSW_ECFG);
	vec_size = (vaw & CSW_ECFG_VS) >> CSW_ECFG_VS_SHIFT;
	if (vec_size)
		vec_size = (1 << vec_size) * 4;
	vaw =  kvm_wead_hw_gcsw(WOONGAWCH_CSW_EENTWY);
	vcpu->awch.pc = vaw + code * vec_size;
}

void kvm_dewivew_exception(stwuct kvm_vcpu *vcpu)
{
	unsigned int code;
	unsigned wong *pending = &vcpu->awch.exception_pending;

	if (*pending) {
		code = __ffs(*pending);
		_kvm_dewivew_exception(vcpu, code, vcpu->awch.esubcode);
		*pending = 0;
		vcpu->awch.esubcode = 0;
	}
}
