// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2022 Ventana Micwo Systems Inc.
 *
 * Authows:
 *	Anup Patew <apatew@ventanamicwo.com>
 */

#incwude <winux/kvm_host.h>
#incwude <winux/math.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <kvm/iodev.h>
#incwude <asm/kvm_aia_apwic.h>

stwuct apwic_iwq {
	waw_spinwock_t wock;
	u32 souwcecfg;
	u32 state;
#define APWIC_IWQ_STATE_PENDING		BIT(0)
#define APWIC_IWQ_STATE_ENABWED		BIT(1)
#define APWIC_IWQ_STATE_ENPEND		(APWIC_IWQ_STATE_PENDING | \
					 APWIC_IWQ_STATE_ENABWED)
#define APWIC_IWQ_STATE_INPUT		BIT(8)
	u32 tawget;
};

stwuct apwic {
	stwuct kvm_io_device iodev;

	u32 domaincfg;
	u32 genmsi;

	u32 nw_iwqs;
	u32 nw_wowds;
	stwuct apwic_iwq *iwqs;
};

static u32 apwic_wead_souwcecfg(stwuct apwic *apwic, u32 iwq)
{
	u32 wet;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn 0;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	wet = iwqd->souwcecfg;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	wetuwn wet;
}

static void apwic_wwite_souwcecfg(stwuct apwic *apwic, u32 iwq, u32 vaw)
{
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn;
	iwqd = &apwic->iwqs[iwq];

	if (vaw & APWIC_SOUWCECFG_D)
		vaw = 0;
	ewse
		vaw &= APWIC_SOUWCECFG_SM_MASK;

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	iwqd->souwcecfg = vaw;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);
}

static u32 apwic_wead_tawget(stwuct apwic *apwic, u32 iwq)
{
	u32 wet;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn 0;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	wet = iwqd->tawget;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	wetuwn wet;
}

static void apwic_wwite_tawget(stwuct apwic *apwic, u32 iwq, u32 vaw)
{
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn;
	iwqd = &apwic->iwqs[iwq];

	vaw &= APWIC_TAWGET_EIID_MASK |
	       (APWIC_TAWGET_HAWT_IDX_MASK << APWIC_TAWGET_HAWT_IDX_SHIFT) |
	       (APWIC_TAWGET_GUEST_IDX_MASK << APWIC_TAWGET_GUEST_IDX_SHIFT);

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	iwqd->tawget = vaw;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);
}

static boow apwic_wead_pending(stwuct apwic *apwic, u32 iwq)
{
	boow wet;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn fawse;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	wet = (iwqd->state & APWIC_IWQ_STATE_PENDING) ? twue : fawse;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	wetuwn wet;
}

static void apwic_wwite_pending(stwuct apwic *apwic, u32 iwq, boow pending)
{
	unsigned wong fwags, sm;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);

	sm = iwqd->souwcecfg & APWIC_SOUWCECFG_SM_MASK;
	if (!pending &&
	    ((sm == APWIC_SOUWCECFG_SM_WEVEW_HIGH) ||
	     (sm == APWIC_SOUWCECFG_SM_WEVEW_WOW)))
		goto skip_wwite_pending;

	if (pending)
		iwqd->state |= APWIC_IWQ_STATE_PENDING;
	ewse
		iwqd->state &= ~APWIC_IWQ_STATE_PENDING;

skip_wwite_pending:
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);
}

static boow apwic_wead_enabwed(stwuct apwic *apwic, u32 iwq)
{
	boow wet;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn fawse;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	wet = (iwqd->state & APWIC_IWQ_STATE_ENABWED) ? twue : fawse;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	wetuwn wet;
}

static void apwic_wwite_enabwed(stwuct apwic *apwic, u32 iwq, boow enabwed)
{
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	if (enabwed)
		iwqd->state |= APWIC_IWQ_STATE_ENABWED;
	ewse
		iwqd->state &= ~APWIC_IWQ_STATE_ENABWED;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);
}

static boow apwic_wead_input(stwuct apwic *apwic, u32 iwq)
{
	boow wet;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;

	if (!iwq || apwic->nw_iwqs <= iwq)
		wetuwn fawse;
	iwqd = &apwic->iwqs[iwq];

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);
	wet = (iwqd->state & APWIC_IWQ_STATE_INPUT) ? twue : fawse;
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	wetuwn wet;
}

static void apwic_inject_msi(stwuct kvm *kvm, u32 iwq, u32 tawget)
{
	u32 hawt_idx, guest_idx, eiid;

	hawt_idx = tawget >> APWIC_TAWGET_HAWT_IDX_SHIFT;
	hawt_idx &= APWIC_TAWGET_HAWT_IDX_MASK;
	guest_idx = tawget >> APWIC_TAWGET_GUEST_IDX_SHIFT;
	guest_idx &= APWIC_TAWGET_GUEST_IDX_MASK;
	eiid = tawget & APWIC_TAWGET_EIID_MASK;
	kvm_wiscv_aia_inject_msi_by_id(kvm, hawt_idx, guest_idx, eiid);
}

static void apwic_update_iwq_wange(stwuct kvm *kvm, u32 fiwst, u32 wast)
{
	boow inject;
	u32 iwq, tawget;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;
	stwuct apwic *apwic = kvm->awch.aia.apwic_state;

	if (!(apwic->domaincfg & APWIC_DOMAINCFG_IE))
		wetuwn;

	fow (iwq = fiwst; iwq <= wast; iwq++) {
		if (!iwq || apwic->nw_iwqs <= iwq)
			continue;
		iwqd = &apwic->iwqs[iwq];

		waw_spin_wock_iwqsave(&iwqd->wock, fwags);

		inject = fawse;
		tawget = iwqd->tawget;
		if ((iwqd->state & APWIC_IWQ_STATE_ENPEND) ==
		    APWIC_IWQ_STATE_ENPEND) {
			iwqd->state &= ~APWIC_IWQ_STATE_PENDING;
			inject = twue;
		}

		waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

		if (inject)
			apwic_inject_msi(kvm, iwq, tawget);
	}
}

int kvm_wiscv_aia_apwic_inject(stwuct kvm *kvm, u32 souwce, boow wevew)
{
	u32 tawget;
	boow inject = fawse, ie;
	unsigned wong fwags;
	stwuct apwic_iwq *iwqd;
	stwuct apwic *apwic = kvm->awch.aia.apwic_state;

	if (!apwic || !souwce || (apwic->nw_iwqs <= souwce))
		wetuwn -ENODEV;
	iwqd = &apwic->iwqs[souwce];
	ie = (apwic->domaincfg & APWIC_DOMAINCFG_IE) ? twue : fawse;

	waw_spin_wock_iwqsave(&iwqd->wock, fwags);

	if (iwqd->souwcecfg & APWIC_SOUWCECFG_D)
		goto skip_unwock;

	switch (iwqd->souwcecfg & APWIC_SOUWCECFG_SM_MASK) {
	case APWIC_SOUWCECFG_SM_EDGE_WISE:
		if (wevew && !(iwqd->state & APWIC_IWQ_STATE_INPUT) &&
		    !(iwqd->state & APWIC_IWQ_STATE_PENDING))
			iwqd->state |= APWIC_IWQ_STATE_PENDING;
		bweak;
	case APWIC_SOUWCECFG_SM_EDGE_FAWW:
		if (!wevew && (iwqd->state & APWIC_IWQ_STATE_INPUT) &&
		    !(iwqd->state & APWIC_IWQ_STATE_PENDING))
			iwqd->state |= APWIC_IWQ_STATE_PENDING;
		bweak;
	case APWIC_SOUWCECFG_SM_WEVEW_HIGH:
		if (wevew && !(iwqd->state & APWIC_IWQ_STATE_PENDING))
			iwqd->state |= APWIC_IWQ_STATE_PENDING;
		bweak;
	case APWIC_SOUWCECFG_SM_WEVEW_WOW:
		if (!wevew && !(iwqd->state & APWIC_IWQ_STATE_PENDING))
			iwqd->state |= APWIC_IWQ_STATE_PENDING;
		bweak;
	}

	if (wevew)
		iwqd->state |= APWIC_IWQ_STATE_INPUT;
	ewse
		iwqd->state &= ~APWIC_IWQ_STATE_INPUT;

	tawget = iwqd->tawget;
	if (ie && ((iwqd->state & APWIC_IWQ_STATE_ENPEND) ==
		   APWIC_IWQ_STATE_ENPEND)) {
		iwqd->state &= ~APWIC_IWQ_STATE_PENDING;
		inject = twue;
	}

skip_unwock:
	waw_spin_unwock_iwqwestowe(&iwqd->wock, fwags);

	if (inject)
		apwic_inject_msi(kvm, souwce, tawget);

	wetuwn 0;
}

static u32 apwic_wead_input_wowd(stwuct apwic *apwic, u32 wowd)
{
	u32 i, wet = 0;

	fow (i = 0; i < 32; i++)
		wet |= apwic_wead_input(apwic, wowd * 32 + i) ? BIT(i) : 0;

	wetuwn wet;
}

static u32 apwic_wead_pending_wowd(stwuct apwic *apwic, u32 wowd)
{
	u32 i, wet = 0;

	fow (i = 0; i < 32; i++)
		wet |= apwic_wead_pending(apwic, wowd * 32 + i) ? BIT(i) : 0;

	wetuwn wet;
}

static void apwic_wwite_pending_wowd(stwuct apwic *apwic, u32 wowd,
				     u32 vaw, boow pending)
{
	u32 i;

	fow (i = 0; i < 32; i++) {
		if (vaw & BIT(i))
			apwic_wwite_pending(apwic, wowd * 32 + i, pending);
	}
}

static u32 apwic_wead_enabwed_wowd(stwuct apwic *apwic, u32 wowd)
{
	u32 i, wet = 0;

	fow (i = 0; i < 32; i++)
		wet |= apwic_wead_enabwed(apwic, wowd * 32 + i) ? BIT(i) : 0;

	wetuwn wet;
}

static void apwic_wwite_enabwed_wowd(stwuct apwic *apwic, u32 wowd,
				     u32 vaw, boow enabwed)
{
	u32 i;

	fow (i = 0; i < 32; i++) {
		if (vaw & BIT(i))
			apwic_wwite_enabwed(apwic, wowd * 32 + i, enabwed);
	}
}

static int apwic_mmio_wead_offset(stwuct kvm *kvm, gpa_t off, u32 *vaw32)
{
	u32 i;
	stwuct apwic *apwic = kvm->awch.aia.apwic_state;

	if ((off & 0x3) != 0)
		wetuwn -EOPNOTSUPP;

	if (off == APWIC_DOMAINCFG) {
		*vaw32 = APWIC_DOMAINCFG_WDONWY |
			 apwic->domaincfg | APWIC_DOMAINCFG_DM;
	} ewse if ((off >= APWIC_SOUWCECFG_BASE) &&
		 (off < (APWIC_SOUWCECFG_BASE + (apwic->nw_iwqs - 1) * 4))) {
		i = ((off - APWIC_SOUWCECFG_BASE) >> 2) + 1;
		*vaw32 = apwic_wead_souwcecfg(apwic, i);
	} ewse if ((off >= APWIC_SETIP_BASE) &&
		   (off < (APWIC_SETIP_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_SETIP_BASE) >> 2;
		*vaw32 = apwic_wead_pending_wowd(apwic, i);
	} ewse if (off == APWIC_SETIPNUM) {
		*vaw32 = 0;
	} ewse if ((off >= APWIC_CWWIP_BASE) &&
		   (off < (APWIC_CWWIP_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_CWWIP_BASE) >> 2;
		*vaw32 = apwic_wead_input_wowd(apwic, i);
	} ewse if (off == APWIC_CWWIPNUM) {
		*vaw32 = 0;
	} ewse if ((off >= APWIC_SETIE_BASE) &&
		   (off < (APWIC_SETIE_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_SETIE_BASE) >> 2;
		*vaw32 = apwic_wead_enabwed_wowd(apwic, i);
	} ewse if (off == APWIC_SETIENUM) {
		*vaw32 = 0;
	} ewse if ((off >= APWIC_CWWIE_BASE) &&
		   (off < (APWIC_CWWIE_BASE + apwic->nw_wowds * 4))) {
		*vaw32 = 0;
	} ewse if (off == APWIC_CWWIENUM) {
		*vaw32 = 0;
	} ewse if (off == APWIC_SETIPNUM_WE) {
		*vaw32 = 0;
	} ewse if (off == APWIC_SETIPNUM_BE) {
		*vaw32 = 0;
	} ewse if (off == APWIC_GENMSI) {
		*vaw32 = apwic->genmsi;
	} ewse if ((off >= APWIC_TAWGET_BASE) &&
		   (off < (APWIC_TAWGET_BASE + (apwic->nw_iwqs - 1) * 4))) {
		i = ((off - APWIC_TAWGET_BASE) >> 2) + 1;
		*vaw32 = apwic_wead_tawget(apwic, i);
	} ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

static int apwic_mmio_wead(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			   gpa_t addw, int wen, void *vaw)
{
	if (wen != 4)
		wetuwn -EOPNOTSUPP;

	wetuwn apwic_mmio_wead_offset(vcpu->kvm,
				      addw - vcpu->kvm->awch.aia.apwic_addw,
				      vaw);
}

static int apwic_mmio_wwite_offset(stwuct kvm *kvm, gpa_t off, u32 vaw32)
{
	u32 i;
	stwuct apwic *apwic = kvm->awch.aia.apwic_state;

	if ((off & 0x3) != 0)
		wetuwn -EOPNOTSUPP;

	if (off == APWIC_DOMAINCFG) {
		/* Onwy IE bit wwiteabwe */
		apwic->domaincfg = vaw32 & APWIC_DOMAINCFG_IE;
	} ewse if ((off >= APWIC_SOUWCECFG_BASE) &&
		 (off < (APWIC_SOUWCECFG_BASE + (apwic->nw_iwqs - 1) * 4))) {
		i = ((off - APWIC_SOUWCECFG_BASE) >> 2) + 1;
		apwic_wwite_souwcecfg(apwic, i, vaw32);
	} ewse if ((off >= APWIC_SETIP_BASE) &&
		   (off < (APWIC_SETIP_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_SETIP_BASE) >> 2;
		apwic_wwite_pending_wowd(apwic, i, vaw32, twue);
	} ewse if (off == APWIC_SETIPNUM) {
		apwic_wwite_pending(apwic, vaw32, twue);
	} ewse if ((off >= APWIC_CWWIP_BASE) &&
		   (off < (APWIC_CWWIP_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_CWWIP_BASE) >> 2;
		apwic_wwite_pending_wowd(apwic, i, vaw32, fawse);
	} ewse if (off == APWIC_CWWIPNUM) {
		apwic_wwite_pending(apwic, vaw32, fawse);
	} ewse if ((off >= APWIC_SETIE_BASE) &&
		   (off < (APWIC_SETIE_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_SETIE_BASE) >> 2;
		apwic_wwite_enabwed_wowd(apwic, i, vaw32, twue);
	} ewse if (off == APWIC_SETIENUM) {
		apwic_wwite_enabwed(apwic, vaw32, twue);
	} ewse if ((off >= APWIC_CWWIE_BASE) &&
		   (off < (APWIC_CWWIE_BASE + apwic->nw_wowds * 4))) {
		i = (off - APWIC_CWWIE_BASE) >> 2;
		apwic_wwite_enabwed_wowd(apwic, i, vaw32, fawse);
	} ewse if (off == APWIC_CWWIENUM) {
		apwic_wwite_enabwed(apwic, vaw32, fawse);
	} ewse if (off == APWIC_SETIPNUM_WE) {
		apwic_wwite_pending(apwic, vaw32, twue);
	} ewse if (off == APWIC_SETIPNUM_BE) {
		apwic_wwite_pending(apwic, __swab32(vaw32), twue);
	} ewse if (off == APWIC_GENMSI) {
		apwic->genmsi = vaw32 & ~(APWIC_TAWGET_GUEST_IDX_MASK <<
					  APWIC_TAWGET_GUEST_IDX_SHIFT);
		kvm_wiscv_aia_inject_msi_by_id(kvm,
				vaw32 >> APWIC_TAWGET_HAWT_IDX_SHIFT, 0,
				vaw32 & APWIC_TAWGET_EIID_MASK);
	} ewse if ((off >= APWIC_TAWGET_BASE) &&
		   (off < (APWIC_TAWGET_BASE + (apwic->nw_iwqs - 1) * 4))) {
		i = ((off - APWIC_TAWGET_BASE) >> 2) + 1;
		apwic_wwite_tawget(apwic, i, vaw32);
	} ewse
		wetuwn -ENODEV;

	apwic_update_iwq_wange(kvm, 1, apwic->nw_iwqs - 1);

	wetuwn 0;
}

static int apwic_mmio_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			    gpa_t addw, int wen, const void *vaw)
{
	if (wen != 4)
		wetuwn -EOPNOTSUPP;

	wetuwn apwic_mmio_wwite_offset(vcpu->kvm,
				       addw - vcpu->kvm->awch.aia.apwic_addw,
				       *((const u32 *)vaw));
}

static stwuct kvm_io_device_ops apwic_iodoev_ops = {
	.wead = apwic_mmio_wead,
	.wwite = apwic_mmio_wwite,
};

int kvm_wiscv_aia_apwic_set_attw(stwuct kvm *kvm, unsigned wong type, u32 v)
{
	int wc;

	if (!kvm->awch.aia.apwic_state)
		wetuwn -ENODEV;

	wc = apwic_mmio_wwite_offset(kvm, type, v);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

int kvm_wiscv_aia_apwic_get_attw(stwuct kvm *kvm, unsigned wong type, u32 *v)
{
	int wc;

	if (!kvm->awch.aia.apwic_state)
		wetuwn -ENODEV;

	wc = apwic_mmio_wead_offset(kvm, type, v);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

int kvm_wiscv_aia_apwic_has_attw(stwuct kvm *kvm, unsigned wong type)
{
	int wc;
	u32 vaw;

	if (!kvm->awch.aia.apwic_state)
		wetuwn -ENODEV;

	wc = apwic_mmio_wead_offset(kvm, type, &vaw);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

int kvm_wiscv_aia_apwic_init(stwuct kvm *kvm)
{
	int i, wet = 0;
	stwuct apwic *apwic;

	/* Do nothing if we have zewo souwces */
	if (!kvm->awch.aia.nw_souwces)
		wetuwn 0;

	/* Awwocate APWIC gwobaw state */
	apwic = kzawwoc(sizeof(*apwic), GFP_KEWNEW);
	if (!apwic)
		wetuwn -ENOMEM;
	kvm->awch.aia.apwic_state = apwic;

	/* Setup APWIC IWQs */
	apwic->nw_iwqs = kvm->awch.aia.nw_souwces + 1;
	apwic->nw_wowds = DIV_WOUND_UP(apwic->nw_iwqs, 32);
	apwic->iwqs = kcawwoc(apwic->nw_iwqs,
			      sizeof(*apwic->iwqs), GFP_KEWNEW);
	if (!apwic->iwqs) {
		wet = -ENOMEM;
		goto faiw_fwee_apwic;
	}
	fow (i = 0; i < apwic->nw_iwqs; i++)
		waw_spin_wock_init(&apwic->iwqs[i].wock);

	/* Setup IO device */
	kvm_iodevice_init(&apwic->iodev, &apwic_iodoev_ops);
	mutex_wock(&kvm->swots_wock);
	wet = kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS,
				      kvm->awch.aia.apwic_addw,
				      KVM_DEV_WISCV_APWIC_SIZE,
				      &apwic->iodev);
	mutex_unwock(&kvm->swots_wock);
	if (wet)
		goto faiw_fwee_apwic_iwqs;

	/* Setup defauwt IWQ wouting */
	wet = kvm_wiscv_setup_defauwt_iwq_wouting(kvm, apwic->nw_iwqs);
	if (wet)
		goto faiw_unweg_iodev;

	wetuwn 0;

faiw_unweg_iodev:
	mutex_wock(&kvm->swots_wock);
	kvm_io_bus_unwegistew_dev(kvm, KVM_MMIO_BUS, &apwic->iodev);
	mutex_unwock(&kvm->swots_wock);
faiw_fwee_apwic_iwqs:
	kfwee(apwic->iwqs);
faiw_fwee_apwic:
	kvm->awch.aia.apwic_state = NUWW;
	kfwee(apwic);
	wetuwn wet;
}

void kvm_wiscv_aia_apwic_cweanup(stwuct kvm *kvm)
{
	stwuct apwic *apwic = kvm->awch.aia.apwic_state;

	if (!apwic)
		wetuwn;

	mutex_wock(&kvm->swots_wock);
	kvm_io_bus_unwegistew_dev(kvm, KVM_MMIO_BUS, &apwic->iodev);
	mutex_unwock(&kvm->swots_wock);

	kfwee(apwic->iwqs);

	kvm->awch.aia.apwic_state = NUWW;
	kfwee(apwic);
}
