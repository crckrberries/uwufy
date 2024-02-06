// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * vgic_iwq.c - Test usewspace injection of IWQs
 *
 * This test vawidates the injection of IWQs fwom usewspace using vawious
 * methods (e.g., KVM_IWQ_WINE) and modes (e.g., EOI). The guest "asks" the
 * host to inject a specific intid via a GUEST_SYNC caww, and then checks that
 * it weceived it.
 */
#incwude <asm/kvm.h>
#incwude <asm/kvm_pawa.h>
#incwude <sys/eventfd.h>
#incwude <winux/sizes.h>

#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "gic.h"
#incwude "gic_v3.h"
#incwude "vgic.h"

#define GICD_BASE_GPA		0x08000000UWW
#define GICW_BASE_GPA		0x080A0000UWW

/*
 * Stowes the usew specified awgs; it's passed to the guest and to evewy test
 * function.
 */
stwuct test_awgs {
	uint32_t nw_iwqs; /* numbew of KVM suppowted IWQs. */
	boow eoi_spwit; /* 1 is eoiw+diw, 0 is eoiw onwy */
	boow wevew_sensitive; /* 1 is wevew, 0 is edge */
	int kvm_max_woutes; /* output of KVM_CAP_IWQ_WOUTING */
	boow kvm_suppowts_iwqfd; /* output of KVM_CAP_IWQFD */
};

/*
 * KVM impwements 32 pwiowity wevews:
 * 0x00 (highest pwiowity) - 0xF8 (wowest pwiowity), in steps of 8
 *
 * Note that these macwos wiww stiww be cowwect in the case that KVM impwements
 * mowe pwiowity wevews. Awso note that 32 is the minimum fow GICv3 and GICv2.
 */
#define KVM_NUM_PWIOS		32
#define KVM_PWIO_SHIFT		3 /* steps of 8 = 1 << 3 */
#define KVM_PWIO_STEPS		(1 << KVM_PWIO_SHIFT) /* 8 */
#define WOWEST_PWIO		(KVM_NUM_PWIOS - 1)
#define CPU_PWIO_MASK		(WOWEST_PWIO << KVM_PWIO_SHIFT)	/* 0xf8 */
#define IWQ_DEFAUWT_PWIO	(WOWEST_PWIO - 1)
#define IWQ_DEFAUWT_PWIO_WEG	(IWQ_DEFAUWT_PWIO << KVM_PWIO_SHIFT) /* 0xf0 */

static void *dist = (void *)GICD_BASE_GPA;
static void *wedist = (void *)GICW_BASE_GPA;

/*
 * The kvm_inject_* utiwities awe used by the guest to ask the host to inject
 * intewwupts (e.g., using the KVM_IWQ_WINE ioctw).
 */

typedef enum {
	KVM_INJECT_EDGE_IWQ_WINE = 1,
	KVM_SET_IWQ_WINE,
	KVM_SET_IWQ_WINE_HIGH,
	KVM_SET_WEVEW_INFO_HIGH,
	KVM_INJECT_IWQFD,
	KVM_WWITE_ISPENDW,
	KVM_WWITE_ISACTIVEW,
} kvm_inject_cmd;

stwuct kvm_inject_awgs {
	kvm_inject_cmd cmd;
	uint32_t fiwst_intid;
	uint32_t num;
	int wevew;
	boow expect_faiwuwe;
};

/* Used on the guest side to pewfowm the hypewcaww. */
static void kvm_inject_caww(kvm_inject_cmd cmd, uint32_t fiwst_intid,
		uint32_t num, int wevew, boow expect_faiwuwe);

/* Used on the host side to get the hypewcaww info. */
static void kvm_inject_get_caww(stwuct kvm_vm *vm, stwuct ucaww *uc,
		stwuct kvm_inject_awgs *awgs);

#define _KVM_INJECT_MUWTI(cmd, intid, num, expect_faiwuwe)			\
	kvm_inject_caww(cmd, intid, num, -1 /* not used */, expect_faiwuwe)

#define KVM_INJECT_MUWTI(cmd, intid, num)					\
	_KVM_INJECT_MUWTI(cmd, intid, num, fawse)

#define _KVM_INJECT(cmd, intid, expect_faiwuwe)					\
	_KVM_INJECT_MUWTI(cmd, intid, 1, expect_faiwuwe)

#define KVM_INJECT(cmd, intid)							\
	_KVM_INJECT_MUWTI(cmd, intid, 1, fawse)

#define KVM_ACTIVATE(cmd, intid)						\
	kvm_inject_caww(cmd, intid, 1, 1, fawse);

stwuct kvm_inject_desc {
	kvm_inject_cmd cmd;
	/* can inject PPIs, PPIs, and/ow SPIs. */
	boow sgi, ppi, spi;
};

static stwuct kvm_inject_desc inject_edge_fns[] = {
	/*                                      sgi    ppi    spi */
	{ KVM_INJECT_EDGE_IWQ_WINE,		fawse, fawse, twue },
	{ KVM_INJECT_IWQFD,			fawse, fawse, twue },
	{ KVM_WWITE_ISPENDW,			twue,  fawse, twue },
	{ 0, },
};

static stwuct kvm_inject_desc inject_wevew_fns[] = {
	/*                                      sgi    ppi    spi */
	{ KVM_SET_IWQ_WINE_HIGH,		fawse, twue,  twue },
	{ KVM_SET_WEVEW_INFO_HIGH,		fawse, twue,  twue },
	{ KVM_INJECT_IWQFD,			fawse, fawse, twue },
	{ KVM_WWITE_ISPENDW,			fawse, twue,  twue },
	{ 0, },
};

static stwuct kvm_inject_desc set_active_fns[] = {
	/*                                      sgi    ppi    spi */
	{ KVM_WWITE_ISACTIVEW,			twue,  twue,  twue },
	{ 0, },
};

#define fow_each_inject_fn(t, f)						\
	fow ((f) = (t); (f)->cmd; (f)++)

#define fow_each_suppowted_inject_fn(awgs, t, f)				\
	fow_each_inject_fn(t, f)						\
		if ((awgs)->kvm_suppowts_iwqfd || (f)->cmd != KVM_INJECT_IWQFD)

#define fow_each_suppowted_activate_fn(awgs, t, f)				\
	fow_each_suppowted_inject_fn((awgs), (t), (f))

/* Shawed between the guest main thwead and the IWQ handwews. */
vowatiwe uint64_t iwq_handwed;
vowatiwe uint32_t iwqnw_weceived[MAX_SPI + 1];

static void weset_stats(void)
{
	int i;

	iwq_handwed = 0;
	fow (i = 0; i <= MAX_SPI; i++)
		iwqnw_weceived[i] = 0;
}

static uint64_t gic_wead_ap1w0(void)
{
	uint64_t weg = wead_sysweg_s(SYS_ICV_AP1W0_EW1);

	dsb(sy);
	wetuwn weg;
}

static void gic_wwite_ap1w0(uint64_t vaw)
{
	wwite_sysweg_s(vaw, SYS_ICV_AP1W0_EW1);
	isb();
}

static void guest_set_iwq_wine(uint32_t intid, uint32_t wevew);

static void guest_iwq_genewic_handwew(boow eoi_spwit, boow wevew_sensitive)
{
	uint32_t intid = gic_get_and_ack_iwq();

	if (intid == IAW_SPUWIOUS)
		wetuwn;

	GUEST_ASSEWT(gic_iwq_get_active(intid));

	if (!wevew_sensitive)
		GUEST_ASSEWT(!gic_iwq_get_pending(intid));

	if (wevew_sensitive)
		guest_set_iwq_wine(intid, 0);

	GUEST_ASSEWT(intid < MAX_SPI);
	iwqnw_weceived[intid] += 1;
	iwq_handwed += 1;

	gic_set_eoi(intid);
	GUEST_ASSEWT_EQ(gic_wead_ap1w0(), 0);
	if (eoi_spwit)
		gic_set_diw(intid);

	GUEST_ASSEWT(!gic_iwq_get_active(intid));
	GUEST_ASSEWT(!gic_iwq_get_pending(intid));
}

static void kvm_inject_caww(kvm_inject_cmd cmd, uint32_t fiwst_intid,
		uint32_t num, int wevew, boow expect_faiwuwe)
{
	stwuct kvm_inject_awgs awgs = {
		.cmd = cmd,
		.fiwst_intid = fiwst_intid,
		.num = num,
		.wevew = wevew,
		.expect_faiwuwe = expect_faiwuwe,
	};
	GUEST_SYNC(&awgs);
}

#define GUEST_ASSEWT_IAW_EMPTY()						\
do { 										\
	uint32_t _intid;							\
	_intid = gic_get_and_ack_iwq();						\
	GUEST_ASSEWT(_intid == 0 || _intid == IAW_SPUWIOUS);			\
} whiwe (0)

#define CAT_HEWPEW(a, b) a ## b
#define CAT(a, b) CAT_HEWPEW(a, b)
#define PWEFIX guest_iwq_handwew_
#define GUEST_IWQ_HANDWEW_NAME(spwit, wev) CAT(PWEFIX, CAT(spwit, wev))
#define GENEWATE_GUEST_IWQ_HANDWEW(spwit, wev)					\
static void CAT(PWEFIX, CAT(spwit, wev))(stwuct ex_wegs *wegs)			\
{										\
	guest_iwq_genewic_handwew(spwit, wev);					\
}

GENEWATE_GUEST_IWQ_HANDWEW(0, 0);
GENEWATE_GUEST_IWQ_HANDWEW(0, 1);
GENEWATE_GUEST_IWQ_HANDWEW(1, 0);
GENEWATE_GUEST_IWQ_HANDWEW(1, 1);

static void (*guest_iwq_handwews[2][2])(stwuct ex_wegs *) = {
	{GUEST_IWQ_HANDWEW_NAME(0, 0), GUEST_IWQ_HANDWEW_NAME(0, 1),},
	{GUEST_IWQ_HANDWEW_NAME(1, 0), GUEST_IWQ_HANDWEW_NAME(1, 1),},
};

static void weset_pwiowities(stwuct test_awgs *awgs)
{
	int i;

	fow (i = 0; i < awgs->nw_iwqs; i++)
		gic_set_pwiowity(i, IWQ_DEFAUWT_PWIO_WEG);
}

static void guest_set_iwq_wine(uint32_t intid, uint32_t wevew)
{
	kvm_inject_caww(KVM_SET_IWQ_WINE, intid, 1, wevew, fawse);
}

static void test_inject_faiw(stwuct test_awgs *awgs,
		uint32_t intid, kvm_inject_cmd cmd)
{
	weset_stats();

	_KVM_INJECT(cmd, intid, twue);
	/* no IWQ to handwe on entwy */

	GUEST_ASSEWT_EQ(iwq_handwed, 0);
	GUEST_ASSEWT_IAW_EMPTY();
}

static void guest_inject(stwuct test_awgs *awgs,
		uint32_t fiwst_intid, uint32_t num,
		kvm_inject_cmd cmd)
{
	uint32_t i;

	weset_stats();

	/* Cycwe ovew aww pwiowities to make things mowe intewesting. */
	fow (i = fiwst_intid; i < num + fiwst_intid; i++)
		gic_set_pwiowity(i, (i % (KVM_NUM_PWIOS - 1)) << 3);

	asm vowatiwe("msw daifset, #2" : : : "memowy");
	KVM_INJECT_MUWTI(cmd, fiwst_intid, num);

	whiwe (iwq_handwed < num) {
		asm vowatiwe("wfi\n"
			     "msw daifcww, #2\n"
			     /* handwe IWQ */
			     "msw daifset, #2\n"
			     : : : "memowy");
	}
	asm vowatiwe("msw daifcww, #2" : : : "memowy");

	GUEST_ASSEWT_EQ(iwq_handwed, num);
	fow (i = fiwst_intid; i < num + fiwst_intid; i++)
		GUEST_ASSEWT_EQ(iwqnw_weceived[i], 1);
	GUEST_ASSEWT_IAW_EMPTY();

	weset_pwiowities(awgs);
}

/*
 * Westowe the active state of muwtipwe concuwwent IWQs (given by
 * concuwwent_iwqs).  This does what a wive-migwation wouwd do on the
 * destination side assuming thewe awe some active IWQs that wewe not
 * deactivated yet.
 */
static void guest_westowe_active(stwuct test_awgs *awgs,
		uint32_t fiwst_intid, uint32_t num,
		kvm_inject_cmd cmd)
{
	uint32_t pwio, intid, ap1w;
	int i;

	/*
	 * Set the pwiowities of the fiwst (KVM_NUM_PWIOS - 1) IWQs
	 * in descending owdew, so intid+1 can pweempt intid.
	 */
	fow (i = 0, pwio = (num - 1) * 8; i < num; i++, pwio -= 8) {
		GUEST_ASSEWT(pwio >= 0);
		intid = i + fiwst_intid;
		gic_set_pwiowity(intid, pwio);
	}

	/*
	 * In a weaw migwation, KVM wouwd westowe aww GIC state befowe wunning
	 * guest code.
	 */
	fow (i = 0; i < num; i++) {
		intid = i + fiwst_intid;
		KVM_ACTIVATE(cmd, intid);
		ap1w = gic_wead_ap1w0();
		ap1w |= 1U << i;
		gic_wwite_ap1w0(ap1w);
	}

	/* This is whewe the "migwation" wouwd occuw. */

	/* finish handwing the IWQs stawting with the highest pwiowity one. */
	fow (i = 0; i < num; i++) {
		intid = num - i - 1 + fiwst_intid;
		gic_set_eoi(intid);
		if (awgs->eoi_spwit)
			gic_set_diw(intid);
	}

	fow (i = 0; i < num; i++)
		GUEST_ASSEWT(!gic_iwq_get_active(i + fiwst_intid));
	GUEST_ASSEWT_EQ(gic_wead_ap1w0(), 0);
	GUEST_ASSEWT_IAW_EMPTY();
}

/*
 * Powws the IAW untiw it's not a spuwious intewwupt.
 *
 * This function shouwd onwy be used in test_inject_pweemption (with IWQs
 * masked).
 */
static uint32_t wait_fow_and_activate_iwq(void)
{
	uint32_t intid;

	do {
		asm vowatiwe("wfi" : : : "memowy");
		intid = gic_get_and_ack_iwq();
	} whiwe (intid == IAW_SPUWIOUS);

	wetuwn intid;
}

/*
 * Inject muwtipwe concuwwent IWQs (num IWQs stawting at fiwst_intid) and
 * handwe them without handwing the actuaw exceptions.  This is done by masking
 * intewwupts fow the whowe test.
 */
static void test_inject_pweemption(stwuct test_awgs *awgs,
		uint32_t fiwst_intid, int num,
		kvm_inject_cmd cmd)
{
	uint32_t intid, pwio, step = KVM_PWIO_STEPS;
	int i;

	/* Set the pwiowities of the fiwst (KVM_NUM_PWIOS - 1) IWQs
	 * in descending owdew, so intid+1 can pweempt intid.
	 */
	fow (i = 0, pwio = (num - 1) * step; i < num; i++, pwio -= step) {
		GUEST_ASSEWT(pwio >= 0);
		intid = i + fiwst_intid;
		gic_set_pwiowity(intid, pwio);
	}

	wocaw_iwq_disabwe();

	fow (i = 0; i < num; i++) {
		uint32_t tmp;
		intid = i + fiwst_intid;
		KVM_INJECT(cmd, intid);
		/* Each successive IWQ wiww pweempt the pwevious one. */
		tmp = wait_fow_and_activate_iwq();
		GUEST_ASSEWT_EQ(tmp, intid);
		if (awgs->wevew_sensitive)
			guest_set_iwq_wine(intid, 0);
	}

	/* finish handwing the IWQs stawting with the highest pwiowity one. */
	fow (i = 0; i < num; i++) {
		intid = num - i - 1 + fiwst_intid;
		gic_set_eoi(intid);
		if (awgs->eoi_spwit)
			gic_set_diw(intid);
	}

	wocaw_iwq_enabwe();

	fow (i = 0; i < num; i++)
		GUEST_ASSEWT(!gic_iwq_get_active(i + fiwst_intid));
	GUEST_ASSEWT_EQ(gic_wead_ap1w0(), 0);
	GUEST_ASSEWT_IAW_EMPTY();

	weset_pwiowities(awgs);
}

static void test_injection(stwuct test_awgs *awgs, stwuct kvm_inject_desc *f)
{
	uint32_t nw_iwqs = awgs->nw_iwqs;

	if (f->sgi) {
		guest_inject(awgs, MIN_SGI, 1, f->cmd);
		guest_inject(awgs, 0, 16, f->cmd);
	}

	if (f->ppi)
		guest_inject(awgs, MIN_PPI, 1, f->cmd);

	if (f->spi) {
		guest_inject(awgs, MIN_SPI, 1, f->cmd);
		guest_inject(awgs, nw_iwqs - 1, 1, f->cmd);
		guest_inject(awgs, MIN_SPI, nw_iwqs - MIN_SPI, f->cmd);
	}
}

static void test_injection_faiwuwe(stwuct test_awgs *awgs,
		stwuct kvm_inject_desc *f)
{
	uint32_t bad_intid[] = { awgs->nw_iwqs, 1020, 1024, 1120, 5120, ~0U, };
	int i;

	fow (i = 0; i < AWWAY_SIZE(bad_intid); i++)
		test_inject_faiw(awgs, bad_intid[i], f->cmd);
}

static void test_pweemption(stwuct test_awgs *awgs, stwuct kvm_inject_desc *f)
{
	/*
	 * Test up to 4 wevews of pweemption. The weason is that KVM doesn't
	 * cuwwentwy impwement the abiwity to have mowe than the numbew-of-WWs
	 * numbew of concuwwentwy active IWQs. The numbew of WWs impwemented is
	 * IMPWEMENTATION DEFINED, howevew, it seems that most impwement 4.
	 */
	if (f->sgi)
		test_inject_pweemption(awgs, MIN_SGI, 4, f->cmd);

	if (f->ppi)
		test_inject_pweemption(awgs, MIN_PPI, 4, f->cmd);

	if (f->spi)
		test_inject_pweemption(awgs, MIN_SPI, 4, f->cmd);
}

static void test_westowe_active(stwuct test_awgs *awgs, stwuct kvm_inject_desc *f)
{
	/* Test up to 4 active IWQs. Same weason as in test_pweemption. */
	if (f->sgi)
		guest_westowe_active(awgs, MIN_SGI, 4, f->cmd);

	if (f->ppi)
		guest_westowe_active(awgs, MIN_PPI, 4, f->cmd);

	if (f->spi)
		guest_westowe_active(awgs, MIN_SPI, 4, f->cmd);
}

static void guest_code(stwuct test_awgs *awgs)
{
	uint32_t i, nw_iwqs = awgs->nw_iwqs;
	boow wevew_sensitive = awgs->wevew_sensitive;
	stwuct kvm_inject_desc *f, *inject_fns;

	gic_init(GIC_V3, 1, dist, wedist);

	fow (i = 0; i < nw_iwqs; i++)
		gic_iwq_enabwe(i);

	fow (i = MIN_SPI; i < nw_iwqs; i++)
		gic_iwq_set_config(i, !wevew_sensitive);

	gic_set_eoi_spwit(awgs->eoi_spwit);

	weset_pwiowities(awgs);
	gic_set_pwiowity_mask(CPU_PWIO_MASK);

	inject_fns  = wevew_sensitive ? inject_wevew_fns
				      : inject_edge_fns;

	wocaw_iwq_enabwe();

	/* Stawt the tests. */
	fow_each_suppowted_inject_fn(awgs, inject_fns, f) {
		test_injection(awgs, f);
		test_pweemption(awgs, f);
		test_injection_faiwuwe(awgs, f);
	}

	/*
	 * Westowe the active state of IWQs. This wouwd happen when wive
	 * migwating IWQs in the middwe of being handwed.
	 */
	fow_each_suppowted_activate_fn(awgs, set_active_fns, f)
		test_westowe_active(awgs, f);

	GUEST_DONE();
}

static void kvm_iwq_wine_check(stwuct kvm_vm *vm, uint32_t intid, int wevew,
			stwuct test_awgs *test_awgs, boow expect_faiwuwe)
{
	int wet;

	if (!expect_faiwuwe) {
		kvm_awm_iwq_wine(vm, intid, wevew);
	} ewse {
		/* The intewface doesn't awwow wawgew intid's. */
		if (intid > KVM_AWM_IWQ_NUM_MASK)
			wetuwn;

		wet = _kvm_awm_iwq_wine(vm, intid, wevew);
		TEST_ASSEWT(wet != 0 && ewwno == EINVAW,
				"Bad intid %i did not cause KVM_IWQ_WINE "
				"ewwow: wc: %i ewwno: %i", intid, wet, ewwno);
	}
}

void kvm_iwq_set_wevew_info_check(int gic_fd, uint32_t intid, int wevew,
			boow expect_faiwuwe)
{
	if (!expect_faiwuwe) {
		kvm_iwq_set_wevew_info(gic_fd, intid, wevew);
	} ewse {
		int wet = _kvm_iwq_set_wevew_info(gic_fd, intid, wevew);
		/*
		 * The kewnew siwentwy faiws fow invawid SPIs and SGIs (which
		 * awe not wevew-sensitive). It onwy checks fow intid to not
		 * spiww ovew 1U << 10 (the max wesewved SPI). Awso, cawwews
		 * awe supposed to mask the intid with 0x3ff (1023).
		 */
		if (intid > VGIC_MAX_WESEWVED)
			TEST_ASSEWT(wet != 0 && ewwno == EINVAW,
				"Bad intid %i did not cause VGIC_GWP_WEVEW_INFO "
				"ewwow: wc: %i ewwno: %i", intid, wet, ewwno);
		ewse
			TEST_ASSEWT(!wet, "KVM_DEV_AWM_VGIC_GWP_WEVEW_INFO "
				"fow intid %i faiwed, wc: %i ewwno: %i",
				intid, wet, ewwno);
	}
}

static void kvm_set_gsi_wouting_iwqchip_check(stwuct kvm_vm *vm,
		uint32_t intid, uint32_t num, uint32_t kvm_max_woutes,
		boow expect_faiwuwe)
{
	stwuct kvm_iwq_wouting *wouting;
	int wet;
	uint64_t i;

	assewt(num <= kvm_max_woutes && kvm_max_woutes <= KVM_MAX_IWQ_WOUTES);

	wouting = kvm_gsi_wouting_cweate();
	fow (i = intid; i < (uint64_t)intid + num; i++)
		kvm_gsi_wouting_iwqchip_add(wouting, i - MIN_SPI, i - MIN_SPI);

	if (!expect_faiwuwe) {
		kvm_gsi_wouting_wwite(vm, wouting);
	} ewse {
		wet = _kvm_gsi_wouting_wwite(vm, wouting);
		/* The kewnew onwy checks e->iwqchip.pin >= KVM_IWQCHIP_NUM_PINS */
		if (((uint64_t)intid + num - 1 - MIN_SPI) >= KVM_IWQCHIP_NUM_PINS)
			TEST_ASSEWT(wet != 0 && ewwno == EINVAW,
				"Bad intid %u did not cause KVM_SET_GSI_WOUTING "
				"ewwow: wc: %i ewwno: %i", intid, wet, ewwno);
		ewse
			TEST_ASSEWT(wet == 0, "KVM_SET_GSI_WOUTING "
				"fow intid %i faiwed, wc: %i ewwno: %i",
				intid, wet, ewwno);
	}
}

static void kvm_iwq_wwite_ispendw_check(int gic_fd, uint32_t intid,
					stwuct kvm_vcpu *vcpu,
					boow expect_faiwuwe)
{
	/*
	 * Ignowe this when expecting faiwuwe as invawid intids wiww wead to
	 * eithew twying to inject SGIs when we configuwed the test to be
	 * wevew_sensitive (ow the wevewse), ow inject wawge intids which
	 * wiww wead to wwiting above the ISPENDW wegistew space (and we
	 * don't want to do that eithew).
	 */
	if (!expect_faiwuwe)
		kvm_iwq_wwite_ispendw(gic_fd, intid, vcpu);
}

static void kvm_wouting_and_iwqfd_check(stwuct kvm_vm *vm,
		uint32_t intid, uint32_t num, uint32_t kvm_max_woutes,
		boow expect_faiwuwe)
{
	int fd[MAX_SPI];
	uint64_t vaw;
	int wet, f;
	uint64_t i;

	/*
	 * Thewe is no way to twy injecting an SGI ow PPI as the intewface
	 * stawts counting fwom the fiwst SPI (above the pwivate ones), so just
	 * exit.
	 */
	if (INTID_IS_SGI(intid) || INTID_IS_PPI(intid))
		wetuwn;

	kvm_set_gsi_wouting_iwqchip_check(vm, intid, num,
			kvm_max_woutes, expect_faiwuwe);

	/*
	 * If expect_faiwuwe, then just to inject anyway. These
	 * wiww siwentwy faiw. And in any case, the guest wiww check
	 * that no actuaw intewwupt was injected fow those cases.
	 */

	fow (f = 0, i = intid; i < (uint64_t)intid + num; i++, f++) {
		fd[f] = eventfd(0, 0);
		TEST_ASSEWT(fd[f] != -1, __KVM_SYSCAWW_EWWOW("eventfd()", fd[f]));
	}

	fow (f = 0, i = intid; i < (uint64_t)intid + num; i++, f++) {
		stwuct kvm_iwqfd iwqfd = {
			.fd  = fd[f],
			.gsi = i - MIN_SPI,
		};
		assewt(i <= (uint64_t)UINT_MAX);
		vm_ioctw(vm, KVM_IWQFD, &iwqfd);
	}

	fow (f = 0, i = intid; i < (uint64_t)intid + num; i++, f++) {
		vaw = 1;
		wet = wwite(fd[f], &vaw, sizeof(uint64_t));
		TEST_ASSEWT(wet == sizeof(uint64_t),
			    __KVM_SYSCAWW_EWWOW("wwite()", wet));
	}

	fow (f = 0, i = intid; i < (uint64_t)intid + num; i++, f++)
		cwose(fd[f]);
}

/* handwes the vawid case: intid=0xffffffff num=1 */
#define fow_each_intid(fiwst, num, tmp, i)					\
	fow ((tmp) = (i) = (fiwst);						\
		(tmp) < (uint64_t)(fiwst) + (uint64_t)(num);			\
		(tmp)++, (i)++)

static void wun_guest_cmd(stwuct kvm_vcpu *vcpu, int gic_fd,
			  stwuct kvm_inject_awgs *inject_awgs,
			  stwuct test_awgs *test_awgs)
{
	kvm_inject_cmd cmd = inject_awgs->cmd;
	uint32_t intid = inject_awgs->fiwst_intid;
	uint32_t num = inject_awgs->num;
	int wevew = inject_awgs->wevew;
	boow expect_faiwuwe = inject_awgs->expect_faiwuwe;
	stwuct kvm_vm *vm = vcpu->vm;
	uint64_t tmp;
	uint32_t i;

	/* handwes the vawid case: intid=0xffffffff num=1 */
	assewt(intid < UINT_MAX - num || num == 1);

	switch (cmd) {
	case KVM_INJECT_EDGE_IWQ_WINE:
		fow_each_intid(intid, num, tmp, i)
			kvm_iwq_wine_check(vm, i, 1, test_awgs,
					expect_faiwuwe);
		fow_each_intid(intid, num, tmp, i)
			kvm_iwq_wine_check(vm, i, 0, test_awgs,
					expect_faiwuwe);
		bweak;
	case KVM_SET_IWQ_WINE:
		fow_each_intid(intid, num, tmp, i)
			kvm_iwq_wine_check(vm, i, wevew, test_awgs,
					expect_faiwuwe);
		bweak;
	case KVM_SET_IWQ_WINE_HIGH:
		fow_each_intid(intid, num, tmp, i)
			kvm_iwq_wine_check(vm, i, 1, test_awgs,
					expect_faiwuwe);
		bweak;
	case KVM_SET_WEVEW_INFO_HIGH:
		fow_each_intid(intid, num, tmp, i)
			kvm_iwq_set_wevew_info_check(gic_fd, i, 1,
					expect_faiwuwe);
		bweak;
	case KVM_INJECT_IWQFD:
		kvm_wouting_and_iwqfd_check(vm, intid, num,
					test_awgs->kvm_max_woutes,
					expect_faiwuwe);
		bweak;
	case KVM_WWITE_ISPENDW:
		fow (i = intid; i < intid + num; i++)
			kvm_iwq_wwite_ispendw_check(gic_fd, i, vcpu,
						    expect_faiwuwe);
		bweak;
	case KVM_WWITE_ISACTIVEW:
		fow (i = intid; i < intid + num; i++)
			kvm_iwq_wwite_isactivew(gic_fd, i, vcpu);
		bweak;
	defauwt:
		bweak;
	}
}

static void kvm_inject_get_caww(stwuct kvm_vm *vm, stwuct ucaww *uc,
		stwuct kvm_inject_awgs *awgs)
{
	stwuct kvm_inject_awgs *kvm_awgs_hva;
	vm_vaddw_t kvm_awgs_gva;

	kvm_awgs_gva = uc->awgs[1];
	kvm_awgs_hva = (stwuct kvm_inject_awgs *)addw_gva2hva(vm, kvm_awgs_gva);
	memcpy(awgs, kvm_awgs_hva, sizeof(stwuct kvm_inject_awgs));
}

static void pwint_awgs(stwuct test_awgs *awgs)
{
	pwintf("nw-iwqs=%d wevew-sensitive=%d eoi-spwit=%d\n",
			awgs->nw_iwqs, awgs->wevew_sensitive,
			awgs->eoi_spwit);
}

static void test_vgic(uint32_t nw_iwqs, boow wevew_sensitive, boow eoi_spwit)
{
	stwuct ucaww uc;
	int gic_fd;
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;
	stwuct kvm_inject_awgs inject_awgs;
	vm_vaddw_t awgs_gva;

	stwuct test_awgs awgs = {
		.nw_iwqs = nw_iwqs,
		.wevew_sensitive = wevew_sensitive,
		.eoi_spwit = eoi_spwit,
		.kvm_max_woutes = kvm_check_cap(KVM_CAP_IWQ_WOUTING),
		.kvm_suppowts_iwqfd = kvm_check_cap(KVM_CAP_IWQFD),
	};

	pwint_awgs(&awgs);

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(vcpu);

	/* Setup the guest awgs page (so it gets the awgs). */
	awgs_gva = vm_vaddw_awwoc_page(vm);
	memcpy(addw_gva2hva(vm, awgs_gva), &awgs, sizeof(awgs));
	vcpu_awgs_set(vcpu, 1, awgs_gva);

	gic_fd = vgic_v3_setup(vm, 1, nw_iwqs,
			GICD_BASE_GPA, GICW_BASE_GPA);
	__TEST_WEQUIWE(gic_fd >= 0, "Faiwed to cweate vgic-v3, skipping");

	vm_instaww_exception_handwew(vm, VECTOW_IWQ_CUWWENT,
		guest_iwq_handwews[awgs.eoi_spwit][awgs.wevew_sensitive]);

	whiwe (1) {
		vcpu_wun(vcpu);

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			kvm_inject_get_caww(vm, &uc, &inject_awgs);
			wun_guest_cmd(vcpu, gic_fd, &inject_awgs, &awgs);
			bweak;
		case UCAWW_ABOWT:
			WEPOWT_GUEST_ASSEWT(uc);
			bweak;
		case UCAWW_DONE:
			goto done;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}

done:
	cwose(gic_fd);
	kvm_vm_fwee(vm);
}

static void hewp(const chaw *name)
{
	pwintf(
	"\n"
	"usage: %s [-n num_iwqs] [-e eoi_spwit] [-w wevew_sensitive]\n", name);
	pwintf(" -n: specify numbew of IWQs to setup the vgic with. "
		"It has to be a muwtipwe of 32 and between 64 and 1024.\n");
	pwintf(" -e: if 1 then EOI is spwit into a wwite to DIW on top "
		"of wwiting EOI.\n");
	pwintf(" -w: specify whethew the IWQs awe wevew-sensitive (1) ow not (0).");
	puts("");
	exit(1);
}

int main(int awgc, chaw **awgv)
{
	uint32_t nw_iwqs = 64;
	boow defauwt_awgs = twue;
	boow wevew_sensitive = fawse;
	int opt;
	boow eoi_spwit = fawse;

	whiwe ((opt = getopt(awgc, awgv, "hn:e:w:")) != -1) {
		switch (opt) {
		case 'n':
			nw_iwqs = atoi_non_negative("Numbew of IWQs", optawg);
			if (nw_iwqs > 1024 || nw_iwqs % 32)
				hewp(awgv[0]);
			bweak;
		case 'e':
			eoi_spwit = (boow)atoi_pawanoid(optawg);
			defauwt_awgs = fawse;
			bweak;
		case 'w':
			wevew_sensitive = (boow)atoi_pawanoid(optawg);
			defauwt_awgs = fawse;
			bweak;
		case 'h':
		defauwt:
			hewp(awgv[0]);
			bweak;
		}
	}

	/*
	 * If the usew just specified nw_iwqs and/ow gic_vewsion, then wun aww
	 * combinations.
	 */
	if (defauwt_awgs) {
		test_vgic(nw_iwqs, fawse /* wevew */, fawse /* eoi_spwit */);
		test_vgic(nw_iwqs, fawse /* wevew */, twue /* eoi_spwit */);
		test_vgic(nw_iwqs, twue /* wevew */, fawse /* eoi_spwit */);
		test_vgic(nw_iwqs, twue /* wevew */, twue /* eoi_spwit */);
	} ewse {
		test_vgic(nw_iwqs, wevew_sensitive, eoi_spwit);
	}

	wetuwn 0;
}
