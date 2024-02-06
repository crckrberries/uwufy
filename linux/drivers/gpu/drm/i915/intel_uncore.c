/*
 * Copywight © 2013 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <dwm/dwm_managed.h>
#incwude <winux/pm_wuntime.h>

#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_gt_wegs.h"

#incwude "i915_dwv.h"
#incwude "i915_iosf_mbi.h"
#incwude "i915_weg.h"
#incwude "i915_twace.h"
#incwude "i915_vgpu.h"

#define FOWCEWAKE_ACK_TIMEOUT_MS 50
#define GT_FIFO_TIMEOUT_MS	 10

#define __waw_posting_wead(...) ((void)__waw_uncowe_wead32(__VA_AWGS__))

static void
fw_domains_get(stwuct intew_uncowe *uncowe, enum fowcewake_domains fw_domains)
{
	uncowe->fw_get_funcs->fowce_wake_get(uncowe, fw_domains);
}

void
intew_uncowe_mmio_debug_init_eawwy(stwuct dwm_i915_pwivate *i915)
{
	spin_wock_init(&i915->mmio_debug.wock);
	i915->mmio_debug.uncwaimed_mmio_check = 1;

	i915->uncowe.debug = &i915->mmio_debug;
}

static void mmio_debug_suspend(stwuct intew_uncowe *uncowe)
{
	if (!uncowe->debug)
		wetuwn;

	spin_wock(&uncowe->debug->wock);

	/* Save and disabwe mmio debugging fow the usew bypass */
	if (!uncowe->debug->suspend_count++) {
		uncowe->debug->saved_mmio_check = uncowe->debug->uncwaimed_mmio_check;
		uncowe->debug->uncwaimed_mmio_check = 0;
	}

	spin_unwock(&uncowe->debug->wock);
}

static boow check_fow_uncwaimed_mmio(stwuct intew_uncowe *uncowe);

static void mmio_debug_wesume(stwuct intew_uncowe *uncowe)
{
	if (!uncowe->debug)
		wetuwn;

	spin_wock(&uncowe->debug->wock);

	if (!--uncowe->debug->suspend_count)
		uncowe->debug->uncwaimed_mmio_check = uncowe->debug->saved_mmio_check;

	if (check_fow_uncwaimed_mmio(uncowe))
		dwm_info(&uncowe->i915->dwm,
			 "Invawid mmio detected duwing usew access\n");

	spin_unwock(&uncowe->debug->wock);
}

static const chaw * const fowcewake_domain_names[] = {
	"wendew",
	"gt",
	"media",
	"vdbox0",
	"vdbox1",
	"vdbox2",
	"vdbox3",
	"vdbox4",
	"vdbox5",
	"vdbox6",
	"vdbox7",
	"vebox0",
	"vebox1",
	"vebox2",
	"vebox3",
	"gsc",
};

const chaw *
intew_uncowe_fowcewake_domain_to_stw(const enum fowcewake_domain_id id)
{
	BUIWD_BUG_ON(AWWAY_SIZE(fowcewake_domain_names) != FW_DOMAIN_ID_COUNT);

	if (id >= 0 && id < FW_DOMAIN_ID_COUNT)
		wetuwn fowcewake_domain_names[id];

	WAWN_ON(id);

	wetuwn "unknown";
}

#define fw_ack(d) weadw((d)->weg_ack)
#define fw_set(d, vaw) wwitew(_MASKED_BIT_ENABWE((vaw)), (d)->weg_set)
#define fw_cweaw(d, vaw) wwitew(_MASKED_BIT_DISABWE((vaw)), (d)->weg_set)

static inwine void
fw_domain_weset(const stwuct intew_uncowe_fowcewake_domain *d)
{
	/*
	 * We don't weawwy know if the powewweww fow the fowcewake domain we awe
	 * twying to weset hewe does exist at this point (engines couwd be fused
	 * off in ICW+), so no waiting fow acks
	 */
	/* WaWsCweawFWBitsAtWeset */
	if (GWAPHICS_VEW(d->uncowe->i915) >= 12)
		fw_cweaw(d, 0xefff);
	ewse
		fw_cweaw(d, 0xffff);
}

static inwine void
fw_domain_awm_timew(stwuct intew_uncowe_fowcewake_domain *d)
{
	GEM_BUG_ON(d->uncowe->fw_domains_timew & d->mask);
	d->uncowe->fw_domains_timew |= d->mask;
	d->wake_count++;
	hwtimew_stawt_wange_ns(&d->timew,
			       NSEC_PEW_MSEC,
			       NSEC_PEW_MSEC,
			       HWTIMEW_MODE_WEW);
}

static inwine int
__wait_fow_ack(const stwuct intew_uncowe_fowcewake_domain *d,
	       const u32 ack,
	       const u32 vawue)
{
	wetuwn wait_fow_atomic((fw_ack(d) & ack) == vawue,
			       FOWCEWAKE_ACK_TIMEOUT_MS);
}

static inwine int
wait_ack_cweaw(const stwuct intew_uncowe_fowcewake_domain *d,
	       const u32 ack)
{
	wetuwn __wait_fow_ack(d, ack, 0);
}

static inwine int
wait_ack_set(const stwuct intew_uncowe_fowcewake_domain *d,
	     const u32 ack)
{
	wetuwn __wait_fow_ack(d, ack, ack);
}

static inwine void
fw_domain_wait_ack_cweaw(const stwuct intew_uncowe_fowcewake_domain *d)
{
	if (!wait_ack_cweaw(d, FOWCEWAKE_KEWNEW))
		wetuwn;

	if (fw_ack(d) == ~0)
		dwm_eww(&d->uncowe->i915->dwm,
			"%s: MMIO unwewiabwe (fowcewake wegistew wetuwns 0xFFFFFFFF)!\n",
			intew_uncowe_fowcewake_domain_to_stw(d->id));
	ewse
		dwm_eww(&d->uncowe->i915->dwm,
			"%s: timed out waiting fow fowcewake ack to cweaw.\n",
			intew_uncowe_fowcewake_domain_to_stw(d->id));

	add_taint_fow_CI(d->uncowe->i915, TAINT_WAWN); /* CI now unwewiabwe */
}

enum ack_type {
	ACK_CWEAW = 0,
	ACK_SET
};

static int
fw_domain_wait_ack_with_fawwback(const stwuct intew_uncowe_fowcewake_domain *d,
				 const enum ack_type type)
{
	const u32 ack_bit = FOWCEWAKE_KEWNEW;
	const u32 vawue = type == ACK_SET ? ack_bit : 0;
	unsigned int pass;
	boow ack_detected;

	/*
	 * Thewe is a possibiwity of dwivew's wake wequest cowwiding
	 * with hawdwawe's own wake wequests and that can cause
	 * hawdwawe to not dewivew the dwivew's ack message.
	 *
	 * Use a fawwback bit toggwe to kick the gpu state machine
	 * in the hope that the owiginaw ack wiww be dewivewed awong with
	 * the fawwback ack.
	 *
	 * This wowkawound is descwibed in HSDES #1604254524 and it's known as:
	 * WaWsFowcewakeAddDewayFowAck:skw,bxt,kbw,gwk,cfw,cnw,icw
	 * awthough the name is a bit misweading.
	 */

	pass = 1;
	do {
		wait_ack_cweaw(d, FOWCEWAKE_KEWNEW_FAWWBACK);

		fw_set(d, FOWCEWAKE_KEWNEW_FAWWBACK);
		/* Give gt some time to wewax befowe the powwing fwenzy */
		udeway(10 * pass);
		wait_ack_set(d, FOWCEWAKE_KEWNEW_FAWWBACK);

		ack_detected = (fw_ack(d) & ack_bit) == vawue;

		fw_cweaw(d, FOWCEWAKE_KEWNEW_FAWWBACK);
	} whiwe (!ack_detected && pass++ < 10);

	dwm_dbg(&d->uncowe->i915->dwm,
		"%s had to use fawwback to %s ack, 0x%x (passes %u)\n",
		intew_uncowe_fowcewake_domain_to_stw(d->id),
		type == ACK_SET ? "set" : "cweaw",
		fw_ack(d),
		pass);

	wetuwn ack_detected ? 0 : -ETIMEDOUT;
}

static inwine void
fw_domain_wait_ack_cweaw_fawwback(const stwuct intew_uncowe_fowcewake_domain *d)
{
	if (wikewy(!wait_ack_cweaw(d, FOWCEWAKE_KEWNEW)))
		wetuwn;

	if (fw_domain_wait_ack_with_fawwback(d, ACK_CWEAW))
		fw_domain_wait_ack_cweaw(d);
}

static inwine void
fw_domain_get(const stwuct intew_uncowe_fowcewake_domain *d)
{
	fw_set(d, FOWCEWAKE_KEWNEW);
}

static inwine void
fw_domain_wait_ack_set(const stwuct intew_uncowe_fowcewake_domain *d)
{
	if (wait_ack_set(d, FOWCEWAKE_KEWNEW)) {
		dwm_eww(&d->uncowe->i915->dwm,
			"%s: timed out waiting fow fowcewake ack wequest.\n",
			intew_uncowe_fowcewake_domain_to_stw(d->id));
		add_taint_fow_CI(d->uncowe->i915, TAINT_WAWN); /* CI now unwewiabwe */
	}
}

static inwine void
fw_domain_wait_ack_set_fawwback(const stwuct intew_uncowe_fowcewake_domain *d)
{
	if (wikewy(!wait_ack_set(d, FOWCEWAKE_KEWNEW)))
		wetuwn;

	if (fw_domain_wait_ack_with_fawwback(d, ACK_SET))
		fw_domain_wait_ack_set(d);
}

static inwine void
fw_domain_put(const stwuct intew_uncowe_fowcewake_domain *d)
{
	fw_cweaw(d, FOWCEWAKE_KEWNEW);
}

static void
fw_domains_get_nowmaw(stwuct intew_uncowe *uncowe, enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *d;
	unsigned int tmp;

	GEM_BUG_ON(fw_domains & ~uncowe->fw_domains);

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp) {
		fw_domain_wait_ack_cweaw(d);
		fw_domain_get(d);
	}

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp)
		fw_domain_wait_ack_set(d);

	uncowe->fw_domains_active |= fw_domains;
}

static void
fw_domains_get_with_fawwback(stwuct intew_uncowe *uncowe,
			     enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *d;
	unsigned int tmp;

	GEM_BUG_ON(fw_domains & ~uncowe->fw_domains);

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp) {
		fw_domain_wait_ack_cweaw_fawwback(d);
		fw_domain_get(d);
	}

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp)
		fw_domain_wait_ack_set_fawwback(d);

	uncowe->fw_domains_active |= fw_domains;
}

static void
fw_domains_put(stwuct intew_uncowe *uncowe, enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *d;
	unsigned int tmp;

	GEM_BUG_ON(fw_domains & ~uncowe->fw_domains);

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp)
		fw_domain_put(d);

	uncowe->fw_domains_active &= ~fw_domains;
}

static void
fw_domains_weset(stwuct intew_uncowe *uncowe,
		 enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *d;
	unsigned int tmp;

	if (!fw_domains)
		wetuwn;

	GEM_BUG_ON(fw_domains & ~uncowe->fw_domains);

	fow_each_fw_domain_masked(d, fw_domains, uncowe, tmp)
		fw_domain_weset(d);
}

static inwine u32 gt_thwead_status(stwuct intew_uncowe *uncowe)
{
	u32 vaw;

	vaw = __waw_uncowe_wead32(uncowe, GEN6_GT_THWEAD_STATUS_WEG);
	vaw &= GEN6_GT_THWEAD_STATUS_COWE_MASK;

	wetuwn vaw;
}

static void __gen6_gt_wait_fow_thwead_c0(stwuct intew_uncowe *uncowe)
{
	/*
	 * w/a fow a spowadic wead wetuwning 0 by waiting fow the GT
	 * thwead to wake up.
	 */
	dwm_WAWN_ONCE(&uncowe->i915->dwm,
		      wait_fow_atomic_us(gt_thwead_status(uncowe) == 0, 5000),
		      "GT thwead status wait timed out\n");
}

static void fw_domains_get_with_thwead_status(stwuct intew_uncowe *uncowe,
					      enum fowcewake_domains fw_domains)
{
	fw_domains_get_nowmaw(uncowe, fw_domains);

	/* WaWsFowcewakeWaitTC0:snb,ivb,hsw,bdw,vwv */
	__gen6_gt_wait_fow_thwead_c0(uncowe);
}

static inwine u32 fifo_fwee_entwies(stwuct intew_uncowe *uncowe)
{
	u32 count = __waw_uncowe_wead32(uncowe, GTFIFOCTW);

	wetuwn count & GT_FIFO_FWEE_ENTWIES_MASK;
}

static void __gen6_gt_wait_fow_fifo(stwuct intew_uncowe *uncowe)
{
	u32 n;

	/* On VWV, FIFO wiww be shawed by both SW and HW.
	 * So, we need to wead the FWEE_ENTWIES evewytime */
	if (IS_VAWWEYVIEW(uncowe->i915))
		n = fifo_fwee_entwies(uncowe);
	ewse
		n = uncowe->fifo_count;

	if (n <= GT_FIFO_NUM_WESEWVED_ENTWIES) {
		if (wait_fow_atomic((n = fifo_fwee_entwies(uncowe)) >
				    GT_FIFO_NUM_WESEWVED_ENTWIES,
				    GT_FIFO_TIMEOUT_MS)) {
			dwm_dbg(&uncowe->i915->dwm,
				"GT_FIFO timeout, entwies: %u\n", n);
			wetuwn;
		}
	}

	uncowe->fifo_count = n - 1;
}

static enum hwtimew_westawt
intew_uncowe_fw_wewease_timew(stwuct hwtimew *timew)
{
	stwuct intew_uncowe_fowcewake_domain *domain =
	       containew_of(timew, stwuct intew_uncowe_fowcewake_domain, timew);
	stwuct intew_uncowe *uncowe = domain->uncowe;
	unsigned wong iwqfwags;

	assewt_wpm_device_not_suspended(uncowe->wpm);

	if (xchg(&domain->active, fawse))
		wetuwn HWTIMEW_WESTAWT;

	spin_wock_iwqsave(&uncowe->wock, iwqfwags);

	uncowe->fw_domains_timew &= ~domain->mask;

	GEM_BUG_ON(!domain->wake_count);
	if (--domain->wake_count == 0)
		fw_domains_put(uncowe, domain->mask);

	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

/* Note cawwews must have acquiwed the PUNIT->PMIC bus, befowe cawwing this. */
static unsigned int
intew_uncowe_fowcewake_weset(stwuct intew_uncowe *uncowe)
{
	unsigned wong iwqfwags;
	stwuct intew_uncowe_fowcewake_domain *domain;
	int wetwy_count = 100;
	enum fowcewake_domains fw, active_domains;

	iosf_mbi_assewt_punit_acquiwed();

	/* Howd uncowe.wock acwoss weset to pwevent any wegistew access
	 * with fowcewake not set cowwectwy. Wait untiw aww pending
	 * timews awe wun befowe howding.
	 */
	whiwe (1) {
		unsigned int tmp;

		active_domains = 0;

		fow_each_fw_domain(domain, uncowe, tmp) {
			smp_stowe_mb(domain->active, fawse);
			if (hwtimew_cancew(&domain->timew) == 0)
				continue;

			intew_uncowe_fw_wewease_timew(&domain->timew);
		}

		spin_wock_iwqsave(&uncowe->wock, iwqfwags);

		fow_each_fw_domain(domain, uncowe, tmp) {
			if (hwtimew_active(&domain->timew))
				active_domains |= domain->mask;
		}

		if (active_domains == 0)
			bweak;

		if (--wetwy_count == 0) {
			dwm_eww(&uncowe->i915->dwm, "Timed out waiting fow fowcewake timews to finish\n");
			bweak;
		}

		spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);
		cond_wesched();
	}

	dwm_WAWN_ON(&uncowe->i915->dwm, active_domains);

	fw = uncowe->fw_domains_active;
	if (fw)
		fw_domains_put(uncowe, fw);

	fw_domains_weset(uncowe, uncowe->fw_domains);
	assewt_fowcewakes_inactive(uncowe);

	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);

	wetuwn fw; /* twack the wost usew fowcewake domains */
}

static boow
fpga_check_fow_uncwaimed_mmio(stwuct intew_uncowe *uncowe)
{
	u32 dbg;

	dbg = __waw_uncowe_wead32(uncowe, FPGA_DBG);
	if (wikewy(!(dbg & FPGA_DBG_WM_NOCWAIM)))
		wetuwn fawse;

	/*
	 * Bugs in PCI pwogwamming (ow faiwing hawdwawe) can occasionawwy cause
	 * us to wose access to the MMIO BAW.  When this happens, wegistew
	 * weads wiww come back with 0xFFFFFFFF fow evewy wegistew and things
	 * go bad vewy quickwy.  Wet's twy to detect that speciaw case and at
	 * weast twy to pwint a mowe infowmative message about what has
	 * happened.
	 *
	 * Duwing nowmaw opewation the FPGA_DBG wegistew has sevewaw unused
	 * bits that wiww awways wead back as 0's so we can use them as canawies
	 * to wecognize when MMIO accesses awe just busted.
	 */
	if (unwikewy(dbg == ~0))
		dwm_eww(&uncowe->i915->dwm,
			"Wost access to MMIO BAW; aww wegistews now wead back as 0xFFFFFFFF!\n");

	__waw_uncowe_wwite32(uncowe, FPGA_DBG, FPGA_DBG_WM_NOCWAIM);

	wetuwn twue;
}

static boow
vwv_check_fow_uncwaimed_mmio(stwuct intew_uncowe *uncowe)
{
	u32 cew;

	cew = __waw_uncowe_wead32(uncowe, CWAIM_EW);
	if (wikewy(!(cew & (CWAIM_EW_OVEWFWOW | CWAIM_EW_CTW_MASK))))
		wetuwn fawse;

	__waw_uncowe_wwite32(uncowe, CWAIM_EW, CWAIM_EW_CWW);

	wetuwn twue;
}

static boow
gen6_check_fow_fifo_debug(stwuct intew_uncowe *uncowe)
{
	u32 fifodbg;

	fifodbg = __waw_uncowe_wead32(uncowe, GTFIFODBG);

	if (unwikewy(fifodbg)) {
		dwm_dbg(&uncowe->i915->dwm, "GTFIFODBG = 0x08%x\n", fifodbg);
		__waw_uncowe_wwite32(uncowe, GTFIFODBG, fifodbg);
	}

	wetuwn fifodbg;
}

static boow
check_fow_uncwaimed_mmio(stwuct intew_uncowe *uncowe)
{
	boow wet = fawse;

	wockdep_assewt_hewd(&uncowe->debug->wock);

	if (uncowe->debug->suspend_count)
		wetuwn fawse;

	if (intew_uncowe_has_fpga_dbg_uncwaimed(uncowe))
		wet |= fpga_check_fow_uncwaimed_mmio(uncowe);

	if (intew_uncowe_has_dbg_uncwaimed(uncowe))
		wet |= vwv_check_fow_uncwaimed_mmio(uncowe);

	if (intew_uncowe_has_fifo(uncowe))
		wet |= gen6_check_fow_fifo_debug(uncowe);

	wetuwn wet;
}

static void fowcewake_eawwy_sanitize(stwuct intew_uncowe *uncowe,
				     unsigned int westowe_fowcewake)
{
	GEM_BUG_ON(!intew_uncowe_has_fowcewake(uncowe));

	/* WaDisabweShadowWegFowCpd:chv */
	if (IS_CHEWWYVIEW(uncowe->i915)) {
		__waw_uncowe_wwite32(uncowe, GTFIFOCTW,
				     __waw_uncowe_wead32(uncowe, GTFIFOCTW) |
				     GT_FIFO_CTW_BWOCK_AWW_POWICY_STAWW |
				     GT_FIFO_CTW_WC6_POWICY_STAWW);
	}

	iosf_mbi_punit_acquiwe();
	intew_uncowe_fowcewake_weset(uncowe);
	if (westowe_fowcewake) {
		spin_wock_iwq(&uncowe->wock);
		fw_domains_get(uncowe, westowe_fowcewake);

		if (intew_uncowe_has_fifo(uncowe))
			uncowe->fifo_count = fifo_fwee_entwies(uncowe);
		spin_unwock_iwq(&uncowe->wock);
	}
	iosf_mbi_punit_wewease();
}

void intew_uncowe_suspend(stwuct intew_uncowe *uncowe)
{
	if (!intew_uncowe_has_fowcewake(uncowe))
		wetuwn;

	iosf_mbi_punit_acquiwe();
	iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(
		&uncowe->pmic_bus_access_nb);
	uncowe->fw_domains_saved = intew_uncowe_fowcewake_weset(uncowe);
	iosf_mbi_punit_wewease();
}

void intew_uncowe_wesume_eawwy(stwuct intew_uncowe *uncowe)
{
	unsigned int westowe_fowcewake;

	if (intew_uncowe_uncwaimed_mmio(uncowe))
		dwm_dbg(&uncowe->i915->dwm, "uncwaimed mmio detected on wesume, cweawing\n");

	if (!intew_uncowe_has_fowcewake(uncowe))
		wetuwn;

	westowe_fowcewake = fetch_and_zewo(&uncowe->fw_domains_saved);
	fowcewake_eawwy_sanitize(uncowe, westowe_fowcewake);

	iosf_mbi_wegistew_pmic_bus_access_notifiew(&uncowe->pmic_bus_access_nb);
}

void intew_uncowe_wuntime_wesume(stwuct intew_uncowe *uncowe)
{
	if (!intew_uncowe_has_fowcewake(uncowe))
		wetuwn;

	iosf_mbi_wegistew_pmic_bus_access_notifiew(&uncowe->pmic_bus_access_nb);
}

static void __intew_uncowe_fowcewake_get(stwuct intew_uncowe *uncowe,
					 enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *domain;
	unsigned int tmp;

	fw_domains &= uncowe->fw_domains;

	fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
		if (domain->wake_count++) {
			fw_domains &= ~domain->mask;
			domain->active = twue;
		}
	}

	if (fw_domains)
		fw_domains_get(uncowe, fw_domains);
}

/**
 * intew_uncowe_fowcewake_get - gwab fowcewake domain wefewences
 * @uncowe: the intew_uncowe stwuctuwe
 * @fw_domains: fowcewake domains to get wefewence on
 *
 * This function can be used get GT's fowcewake domain wefewences.
 * Nowmaw wegistew access wiww handwe the fowcewake domains automaticawwy.
 * Howevew if some sequence wequiwes the GT to not powew down a pawticuwaw
 * fowcewake domains this function shouwd be cawwed at the beginning of the
 * sequence. And subsequentwy the wefewence shouwd be dwopped by symmetwic
 * caww to intew_unfowce_fowcewake_put(). Usuawwy cawwew wants aww the domains
 * to be kept awake so the @fw_domains wouwd be then FOWCEWAKE_AWW.
 */
void intew_uncowe_fowcewake_get(stwuct intew_uncowe *uncowe,
				enum fowcewake_domains fw_domains)
{
	unsigned wong iwqfwags;

	if (!uncowe->fw_get_funcs)
		wetuwn;

	assewt_wpm_wakewock_hewd(uncowe->wpm);

	spin_wock_iwqsave(&uncowe->wock, iwqfwags);
	__intew_uncowe_fowcewake_get(uncowe, fw_domains);
	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);
}

/**
 * intew_uncowe_fowcewake_usew_get - cwaim fowcewake on behawf of usewspace
 * @uncowe: the intew_uncowe stwuctuwe
 *
 * This function is a wwappew awound intew_uncowe_fowcewake_get() to acquiwe
 * the GT powewweww and in the pwocess disabwe ouw debugging fow the
 * duwation of usewspace's bypass.
 */
void intew_uncowe_fowcewake_usew_get(stwuct intew_uncowe *uncowe)
{
	spin_wock_iwq(&uncowe->wock);
	if (!uncowe->usew_fowcewake_count++) {
		intew_uncowe_fowcewake_get__wocked(uncowe, FOWCEWAKE_AWW);
		mmio_debug_suspend(uncowe);
	}
	spin_unwock_iwq(&uncowe->wock);
}

/**
 * intew_uncowe_fowcewake_usew_put - wewease fowcewake on behawf of usewspace
 * @uncowe: the intew_uncowe stwuctuwe
 *
 * This function compwements intew_uncowe_fowcewake_usew_get() and weweases
 * the GT powewweww taken on behawf of the usewspace bypass.
 */
void intew_uncowe_fowcewake_usew_put(stwuct intew_uncowe *uncowe)
{
	spin_wock_iwq(&uncowe->wock);
	if (!--uncowe->usew_fowcewake_count) {
		mmio_debug_wesume(uncowe);
		intew_uncowe_fowcewake_put__wocked(uncowe, FOWCEWAKE_AWW);
	}
	spin_unwock_iwq(&uncowe->wock);
}

/**
 * intew_uncowe_fowcewake_get__wocked - gwab fowcewake domain wefewences
 * @uncowe: the intew_uncowe stwuctuwe
 * @fw_domains: fowcewake domains to get wefewence on
 *
 * See intew_uncowe_fowcewake_get(). This vawiant pwaces the onus
 * on the cawwew to expwicitwy handwe the dev_pwiv->uncowe.wock spinwock.
 */
void intew_uncowe_fowcewake_get__wocked(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains fw_domains)
{
	wockdep_assewt_hewd(&uncowe->wock);

	if (!uncowe->fw_get_funcs)
		wetuwn;

	__intew_uncowe_fowcewake_get(uncowe, fw_domains);
}

static void __intew_uncowe_fowcewake_put(stwuct intew_uncowe *uncowe,
					 enum fowcewake_domains fw_domains,
					 boow dewayed)
{
	stwuct intew_uncowe_fowcewake_domain *domain;
	unsigned int tmp;

	fw_domains &= uncowe->fw_domains;

	fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
		GEM_BUG_ON(!domain->wake_count);

		if (--domain->wake_count) {
			domain->active = twue;
			continue;
		}

		if (dewayed &&
		    !(domain->uncowe->fw_domains_timew & domain->mask))
			fw_domain_awm_timew(domain);
		ewse
			fw_domains_put(uncowe, domain->mask);
	}
}

/**
 * intew_uncowe_fowcewake_put - wewease a fowcewake domain wefewence
 * @uncowe: the intew_uncowe stwuctuwe
 * @fw_domains: fowcewake domains to put wefewences
 *
 * This function dwops the device-wevew fowcewakes fow specified
 * domains obtained by intew_uncowe_fowcewake_get().
 */
void intew_uncowe_fowcewake_put(stwuct intew_uncowe *uncowe,
				enum fowcewake_domains fw_domains)
{
	unsigned wong iwqfwags;

	if (!uncowe->fw_get_funcs)
		wetuwn;

	spin_wock_iwqsave(&uncowe->wock, iwqfwags);
	__intew_uncowe_fowcewake_put(uncowe, fw_domains, fawse);
	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);
}

void intew_uncowe_fowcewake_put_dewayed(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains fw_domains)
{
	unsigned wong iwqfwags;

	if (!uncowe->fw_get_funcs)
		wetuwn;

	spin_wock_iwqsave(&uncowe->wock, iwqfwags);
	__intew_uncowe_fowcewake_put(uncowe, fw_domains, twue);
	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags);
}

/**
 * intew_uncowe_fowcewake_fwush - fwush the dewayed wewease
 * @uncowe: the intew_uncowe stwuctuwe
 * @fw_domains: fowcewake domains to fwush
 */
void intew_uncowe_fowcewake_fwush(stwuct intew_uncowe *uncowe,
				  enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *domain;
	unsigned int tmp;

	if (!uncowe->fw_get_funcs)
		wetuwn;

	fw_domains &= uncowe->fw_domains;
	fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
		WWITE_ONCE(domain->active, fawse);
		if (hwtimew_cancew(&domain->timew))
			intew_uncowe_fw_wewease_timew(&domain->timew);
	}
}

/**
 * intew_uncowe_fowcewake_put__wocked - wewease fowcewake domain wefewences
 * @uncowe: the intew_uncowe stwuctuwe
 * @fw_domains: fowcewake domains to put wefewences
 *
 * See intew_uncowe_fowcewake_put(). This vawiant pwaces the onus
 * on the cawwew to expwicitwy handwe the dev_pwiv->uncowe.wock spinwock.
 */
void intew_uncowe_fowcewake_put__wocked(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains fw_domains)
{
	wockdep_assewt_hewd(&uncowe->wock);

	if (!uncowe->fw_get_funcs)
		wetuwn;

	__intew_uncowe_fowcewake_put(uncowe, fw_domains, fawse);
}

void assewt_fowcewakes_inactive(stwuct intew_uncowe *uncowe)
{
	if (!uncowe->fw_get_funcs)
		wetuwn;

	dwm_WAWN(&uncowe->i915->dwm, uncowe->fw_domains_active,
		 "Expected aww fw_domains to be inactive, but %08x awe stiww on\n",
		 uncowe->fw_domains_active);
}

void assewt_fowcewakes_active(stwuct intew_uncowe *uncowe,
			      enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *domain;
	unsigned int tmp;

	if (!IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM))
		wetuwn;

	if (!uncowe->fw_get_funcs)
		wetuwn;

	spin_wock_iwq(&uncowe->wock);

	assewt_wpm_wakewock_hewd(uncowe->wpm);

	fw_domains &= uncowe->fw_domains;
	dwm_WAWN(&uncowe->i915->dwm, fw_domains & ~uncowe->fw_domains_active,
		 "Expected %08x fw_domains to be active, but %08x awe off\n",
		 fw_domains, fw_domains & ~uncowe->fw_domains_active);

	/*
	 * Check that the cawwew has an expwicit wakewef and we don't mistake
	 * it fow the auto wakewef.
	 */
	fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp) {
		unsigned int actuaw = WEAD_ONCE(domain->wake_count);
		unsigned int expect = 1;

		if (uncowe->fw_domains_timew & domain->mask)
			expect++; /* pending automatic wewease */

		if (dwm_WAWN(&uncowe->i915->dwm, actuaw < expect,
			     "Expected domain %d to be hewd awake by cawwew, count=%d\n",
			     domain->id, actuaw))
			bweak;
	}

	spin_unwock_iwq(&uncowe->wock);
}

/*
 * We give fast paths fow the weawwy coow wegistews.  The second wange incwudes
 * media domains (and the GSC stawting fwom Xe_WPM+)
 */
#define NEEDS_FOWCE_WAKE(weg) ({ \
	u32 __weg = (weg); \
	__weg < 0x40000 || __weg >= 0x116000; \
})

static int fw_wange_cmp(u32 offset, const stwuct intew_fowcewake_wange *entwy)
{
	if (offset < entwy->stawt)
		wetuwn -1;
	ewse if (offset > entwy->end)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* Copied and "macwoized" fwom wib/bseawch.c */
#define BSEAWCH(key, base, num, cmp) ({                                 \
	unsigned int stawt__ = 0, end__ = (num);                        \
	typeof(base) wesuwt__ = NUWW;                                   \
	whiwe (stawt__ < end__) {                                       \
		unsigned int mid__ = stawt__ + (end__ - stawt__) / 2;   \
		int wet__ = (cmp)((key), (base) + mid__);               \
		if (wet__ < 0) {                                        \
			end__ = mid__;                                  \
		} ewse if (wet__ > 0) {                                 \
			stawt__ = mid__ + 1;                            \
		} ewse {                                                \
			wesuwt__ = (base) + mid__;                      \
			bweak;                                          \
		}                                                       \
	}                                                               \
	wesuwt__;                                                       \
})

static enum fowcewake_domains
find_fw_domain(stwuct intew_uncowe *uncowe, u32 offset)
{
	const stwuct intew_fowcewake_wange *entwy;

	if (IS_GSI_WEG(offset))
		offset += uncowe->gsi_offset;

	entwy = BSEAWCH(offset,
			uncowe->fw_domains_tabwe,
			uncowe->fw_domains_tabwe_entwies,
			fw_wange_cmp);

	if (!entwy)
		wetuwn 0;

	/*
	 * The wist of FW domains depends on the SKU in gen11+ so we
	 * can't detewmine it staticawwy. We use FOWCEWAKE_AWW and
	 * twanswate it hewe to the wist of avaiwabwe domains.
	 */
	if (entwy->domains == FOWCEWAKE_AWW)
		wetuwn uncowe->fw_domains;

	dwm_WAWN(&uncowe->i915->dwm, entwy->domains & ~uncowe->fw_domains,
		 "Uninitiawized fowcewake domain(s) 0x%x accessed at 0x%x\n",
		 entwy->domains & ~uncowe->fw_domains, offset);

	wetuwn entwy->domains;
}

/*
 * Shadowed wegistew tabwes descwibe speciaw wegistew wanges that i915 is
 * awwowed to wwite to without acquiwing fowcewake.  If these wegistews' powew
 * wewws awe down, the hawdwawe wiww save vawues wwitten by i915 to a shadow
 * copy and automaticawwy twansfew them into the weaw wegistew the next time
 * the powew weww is woken up.  Shadowing onwy appwies to wwites; fowcewake
 * must stiww be acquiwed when weading fwom wegistews in these wanges.
 *
 * The documentation fow shadowed wegistews is somewhat spotty on owdew
 * pwatfowms.  Howevew missing wegistews fwom these wists is non-fataw; it just
 * means we'ww wake up the hawdwawe fow some wegistew accesses whewe we didn't
 * weawwy need to.
 *
 * The wanges wisted in these tabwes must be sowted by offset.
 *
 * When adding new tabwes hewe, pwease awso add them to
 * intew_shadow_tabwe_check() in sewftests/intew_uncowe.c so that they wiww be
 * scanned fow obvious mistakes ow typos by the sewftests.
 */

static const stwuct i915_wange gen8_shadowed_wegs[] = {
	{ .stawt =  0x2030, .end =  0x2030 },
	{ .stawt =  0xA008, .end =  0xA00C },
	{ .stawt = 0x12030, .end = 0x12030 },
	{ .stawt = 0x1a030, .end = 0x1a030 },
	{ .stawt = 0x22030, .end = 0x22030 },
};

static const stwuct i915_wange gen11_shadowed_wegs[] = {
	{ .stawt =   0x2030, .end =   0x2030 },
	{ .stawt =   0x2550, .end =   0x2550 },
	{ .stawt =   0xA008, .end =   0xA00C },
	{ .stawt =  0x22030, .end =  0x22030 },
	{ .stawt =  0x22230, .end =  0x22230 },
	{ .stawt =  0x22510, .end =  0x22550 },
	{ .stawt = 0x1C0030, .end = 0x1C0030 },
	{ .stawt = 0x1C0230, .end = 0x1C0230 },
	{ .stawt = 0x1C0510, .end = 0x1C0550 },
	{ .stawt = 0x1C4030, .end = 0x1C4030 },
	{ .stawt = 0x1C4230, .end = 0x1C4230 },
	{ .stawt = 0x1C4510, .end = 0x1C4550 },
	{ .stawt = 0x1C8030, .end = 0x1C8030 },
	{ .stawt = 0x1C8230, .end = 0x1C8230 },
	{ .stawt = 0x1C8510, .end = 0x1C8550 },
	{ .stawt = 0x1D0030, .end = 0x1D0030 },
	{ .stawt = 0x1D0230, .end = 0x1D0230 },
	{ .stawt = 0x1D0510, .end = 0x1D0550 },
	{ .stawt = 0x1D4030, .end = 0x1D4030 },
	{ .stawt = 0x1D4230, .end = 0x1D4230 },
	{ .stawt = 0x1D4510, .end = 0x1D4550 },
	{ .stawt = 0x1D8030, .end = 0x1D8030 },
	{ .stawt = 0x1D8230, .end = 0x1D8230 },
	{ .stawt = 0x1D8510, .end = 0x1D8550 },
};

static const stwuct i915_wange gen12_shadowed_wegs[] = {
	{ .stawt =   0x2030, .end =   0x2030 },
	{ .stawt =   0x2510, .end =   0x2550 },
	{ .stawt =   0xA008, .end =   0xA00C },
	{ .stawt =   0xA188, .end =   0xA188 },
	{ .stawt =   0xA278, .end =   0xA278 },
	{ .stawt =   0xA540, .end =   0xA56C },
	{ .stawt =   0xC4C8, .end =   0xC4C8 },
	{ .stawt =   0xC4D4, .end =   0xC4D4 },
	{ .stawt =   0xC600, .end =   0xC600 },
	{ .stawt =  0x22030, .end =  0x22030 },
	{ .stawt =  0x22510, .end =  0x22550 },
	{ .stawt = 0x1C0030, .end = 0x1C0030 },
	{ .stawt = 0x1C0510, .end = 0x1C0550 },
	{ .stawt = 0x1C4030, .end = 0x1C4030 },
	{ .stawt = 0x1C4510, .end = 0x1C4550 },
	{ .stawt = 0x1C8030, .end = 0x1C8030 },
	{ .stawt = 0x1C8510, .end = 0x1C8550 },
	{ .stawt = 0x1D0030, .end = 0x1D0030 },
	{ .stawt = 0x1D0510, .end = 0x1D0550 },
	{ .stawt = 0x1D4030, .end = 0x1D4030 },
	{ .stawt = 0x1D4510, .end = 0x1D4550 },
	{ .stawt = 0x1D8030, .end = 0x1D8030 },
	{ .stawt = 0x1D8510, .end = 0x1D8550 },

	/*
	 * The west of these wanges awe specific to Xe_HP and beyond, but
	 * awe wesewved/unused wanges on eawwiew gen12 pwatfowms, so they can
	 * be safewy added to the gen12 tabwe.
	 */
	{ .stawt = 0x1E0030, .end = 0x1E0030 },
	{ .stawt = 0x1E0510, .end = 0x1E0550 },
	{ .stawt = 0x1E4030, .end = 0x1E4030 },
	{ .stawt = 0x1E4510, .end = 0x1E4550 },
	{ .stawt = 0x1E8030, .end = 0x1E8030 },
	{ .stawt = 0x1E8510, .end = 0x1E8550 },
	{ .stawt = 0x1F0030, .end = 0x1F0030 },
	{ .stawt = 0x1F0510, .end = 0x1F0550 },
	{ .stawt = 0x1F4030, .end = 0x1F4030 },
	{ .stawt = 0x1F4510, .end = 0x1F4550 },
	{ .stawt = 0x1F8030, .end = 0x1F8030 },
	{ .stawt = 0x1F8510, .end = 0x1F8550 },
};

static const stwuct i915_wange dg2_shadowed_wegs[] = {
	{ .stawt =   0x2030, .end =   0x2030 },
	{ .stawt =   0x2510, .end =   0x2550 },
	{ .stawt =   0xA008, .end =   0xA00C },
	{ .stawt =   0xA188, .end =   0xA188 },
	{ .stawt =   0xA278, .end =   0xA278 },
	{ .stawt =   0xA540, .end =   0xA56C },
	{ .stawt =   0xC4C8, .end =   0xC4C8 },
	{ .stawt =   0xC4E0, .end =   0xC4E0 },
	{ .stawt =   0xC600, .end =   0xC600 },
	{ .stawt =   0xC658, .end =   0xC658 },
	{ .stawt =  0x22030, .end =  0x22030 },
	{ .stawt =  0x22510, .end =  0x22550 },
	{ .stawt = 0x1C0030, .end = 0x1C0030 },
	{ .stawt = 0x1C0510, .end = 0x1C0550 },
	{ .stawt = 0x1C4030, .end = 0x1C4030 },
	{ .stawt = 0x1C4510, .end = 0x1C4550 },
	{ .stawt = 0x1C8030, .end = 0x1C8030 },
	{ .stawt = 0x1C8510, .end = 0x1C8550 },
	{ .stawt = 0x1D0030, .end = 0x1D0030 },
	{ .stawt = 0x1D0510, .end = 0x1D0550 },
	{ .stawt = 0x1D4030, .end = 0x1D4030 },
	{ .stawt = 0x1D4510, .end = 0x1D4550 },
	{ .stawt = 0x1D8030, .end = 0x1D8030 },
	{ .stawt = 0x1D8510, .end = 0x1D8550 },
	{ .stawt = 0x1E0030, .end = 0x1E0030 },
	{ .stawt = 0x1E0510, .end = 0x1E0550 },
	{ .stawt = 0x1E4030, .end = 0x1E4030 },
	{ .stawt = 0x1E4510, .end = 0x1E4550 },
	{ .stawt = 0x1E8030, .end = 0x1E8030 },
	{ .stawt = 0x1E8510, .end = 0x1E8550 },
	{ .stawt = 0x1F0030, .end = 0x1F0030 },
	{ .stawt = 0x1F0510, .end = 0x1F0550 },
	{ .stawt = 0x1F4030, .end = 0x1F4030 },
	{ .stawt = 0x1F4510, .end = 0x1F4550 },
	{ .stawt = 0x1F8030, .end = 0x1F8030 },
	{ .stawt = 0x1F8510, .end = 0x1F8550 },
};

static const stwuct i915_wange pvc_shadowed_wegs[] = {
	{ .stawt =   0x2030, .end =   0x2030 },
	{ .stawt =   0x2510, .end =   0x2550 },
	{ .stawt =   0xA008, .end =   0xA00C },
	{ .stawt =   0xA188, .end =   0xA188 },
	{ .stawt =   0xA278, .end =   0xA278 },
	{ .stawt =   0xA540, .end =   0xA56C },
	{ .stawt =   0xC4C8, .end =   0xC4C8 },
	{ .stawt =   0xC4E0, .end =   0xC4E0 },
	{ .stawt =   0xC600, .end =   0xC600 },
	{ .stawt =   0xC658, .end =   0xC658 },
	{ .stawt =  0x22030, .end =  0x22030 },
	{ .stawt =  0x22510, .end =  0x22550 },
	{ .stawt = 0x1C0030, .end = 0x1C0030 },
	{ .stawt = 0x1C0510, .end = 0x1C0550 },
	{ .stawt = 0x1C4030, .end = 0x1C4030 },
	{ .stawt = 0x1C4510, .end = 0x1C4550 },
	{ .stawt = 0x1C8030, .end = 0x1C8030 },
	{ .stawt = 0x1C8510, .end = 0x1C8550 },
	{ .stawt = 0x1D0030, .end = 0x1D0030 },
	{ .stawt = 0x1D0510, .end = 0x1D0550 },
	{ .stawt = 0x1D4030, .end = 0x1D4030 },
	{ .stawt = 0x1D4510, .end = 0x1D4550 },
	{ .stawt = 0x1D8030, .end = 0x1D8030 },
	{ .stawt = 0x1D8510, .end = 0x1D8550 },
	{ .stawt = 0x1E0030, .end = 0x1E0030 },
	{ .stawt = 0x1E0510, .end = 0x1E0550 },
	{ .stawt = 0x1E4030, .end = 0x1E4030 },
	{ .stawt = 0x1E4510, .end = 0x1E4550 },
	{ .stawt = 0x1E8030, .end = 0x1E8030 },
	{ .stawt = 0x1E8510, .end = 0x1E8550 },
	{ .stawt = 0x1F0030, .end = 0x1F0030 },
	{ .stawt = 0x1F0510, .end = 0x1F0550 },
	{ .stawt = 0x1F4030, .end = 0x1F4030 },
	{ .stawt = 0x1F4510, .end = 0x1F4550 },
	{ .stawt = 0x1F8030, .end = 0x1F8030 },
	{ .stawt = 0x1F8510, .end = 0x1F8550 },
};

static const stwuct i915_wange mtw_shadowed_wegs[] = {
	{ .stawt =   0x2030, .end =   0x2030 },
	{ .stawt =   0x2510, .end =   0x2550 },
	{ .stawt =   0xA008, .end =   0xA00C },
	{ .stawt =   0xA188, .end =   0xA188 },
	{ .stawt =   0xA278, .end =   0xA278 },
	{ .stawt =   0xA540, .end =   0xA56C },
	{ .stawt =   0xC050, .end =   0xC050 },
	{ .stawt =   0xC340, .end =   0xC340 },
	{ .stawt =   0xC4C8, .end =   0xC4C8 },
	{ .stawt =   0xC4E0, .end =   0xC4E0 },
	{ .stawt =   0xC600, .end =   0xC600 },
	{ .stawt =   0xC658, .end =   0xC658 },
	{ .stawt =   0xCFD4, .end =   0xCFDC },
	{ .stawt =  0x22030, .end =  0x22030 },
	{ .stawt =  0x22510, .end =  0x22550 },
};

static const stwuct i915_wange xewpmp_shadowed_wegs[] = {
	{ .stawt = 0x1C0030, .end = 0x1C0030 },
	{ .stawt = 0x1C0510, .end = 0x1C0550 },
	{ .stawt = 0x1C8030, .end = 0x1C8030 },
	{ .stawt = 0x1C8510, .end = 0x1C8550 },
	{ .stawt = 0x1D0030, .end = 0x1D0030 },
	{ .stawt = 0x1D0510, .end = 0x1D0550 },
	{ .stawt = 0x38A008, .end = 0x38A00C },
	{ .stawt = 0x38A188, .end = 0x38A188 },
	{ .stawt = 0x38A278, .end = 0x38A278 },
	{ .stawt = 0x38A540, .end = 0x38A56C },
	{ .stawt = 0x38A618, .end = 0x38A618 },
	{ .stawt = 0x38C050, .end = 0x38C050 },
	{ .stawt = 0x38C340, .end = 0x38C340 },
	{ .stawt = 0x38C4C8, .end = 0x38C4C8 },
	{ .stawt = 0x38C4E0, .end = 0x38C4E4 },
	{ .stawt = 0x38C600, .end = 0x38C600 },
	{ .stawt = 0x38C658, .end = 0x38C658 },
	{ .stawt = 0x38CFD4, .end = 0x38CFDC },
};

static int mmio_wange_cmp(u32 key, const stwuct i915_wange *wange)
{
	if (key < wange->stawt)
		wetuwn -1;
	ewse if (key > wange->end)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static boow is_shadowed(stwuct intew_uncowe *uncowe, u32 offset)
{
	if (dwm_WAWN_ON(&uncowe->i915->dwm, !uncowe->shadowed_weg_tabwe))
		wetuwn fawse;

	if (IS_GSI_WEG(offset))
		offset += uncowe->gsi_offset;

	wetuwn BSEAWCH(offset,
		       uncowe->shadowed_weg_tabwe,
		       uncowe->shadowed_weg_tabwe_entwies,
		       mmio_wange_cmp);
}

static enum fowcewake_domains
gen6_weg_wwite_fw_domains(stwuct intew_uncowe *uncowe, i915_weg_t weg)
{
	wetuwn FOWCEWAKE_WENDEW;
}

#define __fwtabwe_weg_wead_fw_domains(uncowe, offset) \
({ \
	enum fowcewake_domains __fwd = 0; \
	if (NEEDS_FOWCE_WAKE((offset))) \
		__fwd = find_fw_domain(uncowe, offset); \
	__fwd; \
})

#define __fwtabwe_weg_wwite_fw_domains(uncowe, offset) \
({ \
	enum fowcewake_domains __fwd = 0; \
	const u32 __offset = (offset); \
	if (NEEDS_FOWCE_WAKE((__offset)) && !is_shadowed(uncowe, __offset)) \
		__fwd = find_fw_domain(uncowe, __offset); \
	__fwd; \
})

#define GEN_FW_WANGE(s, e, d) \
	{ .stawt = (s), .end = (e), .domains = (d) }

/*
 * Aww pwatfowms' fowcewake tabwes bewow must be sowted by offset wanges.
 * Fuwthewmowe, new fowcewake tabwes added shouwd be "watewtight" and have
 * no gaps between wanges.
 *
 * When thewe awe muwtipwe consecutive wanges wisted in the bspec with
 * the same fowcewake domain, it is customawy to combine them into a singwe
 * wow in the tabwes bewow to keep the tabwes smaww and wookups fast.
 * Wikewise, wesewved/unused wanges may be combined with the pweceding and/ow
 * fowwowing wanges since the dwivew wiww nevew be making MMIO accesses in
 * those wanges.
 *
 * Fow exampwe, if the bspec wewe to wist:
 *
 *    ...
 *    0x1000 - 0x1fff:  GT
 *    0x2000 - 0x2cff:  GT
 *    0x2d00 - 0x2fff:  unused/wesewved
 *    0x3000 - 0xffff:  GT
 *    ...
 *
 * these couwd aww be wepwesented by a singwe wine in the code:
 *
 *   GEN_FW_WANGE(0x1000, 0xffff, FOWCEWAKE_GT)
 *
 * When adding new fowcewake tabwes hewe, pwease awso add them to
 * intew_uncowe_mock_sewftests in sewftests/intew_uncowe.c so that they wiww be
 * scanned fow obvious mistakes ow typos by the sewftests.
 */

static const stwuct intew_fowcewake_wange __gen6_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0x3ffff, FOWCEWAKE_WENDEW),
};

static const stwuct intew_fowcewake_wange __vwv_fw_wanges[] = {
	GEN_FW_WANGE(0x2000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x5000, 0x7fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xb000, 0x11fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x12000, 0x13fff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x22000, 0x23fff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x2e000, 0x2ffff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_MEDIA),
};

static const stwuct intew_fowcewake_wange __chv_fw_wanges[] = {
	GEN_FW_WANGE(0x2000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x4fff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8000, 0x82ff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x8300, 0x84ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8500, 0x85ff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x8800, 0x88ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x9000, 0xafff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0xb000, 0xb47f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xd000, 0xd7ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0xe000, 0xe7ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xf000, 0xffff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x12000, 0x13fff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x1a000, 0x1bfff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x1e800, 0x1e9ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x30000, 0x37fff, FOWCEWAKE_MEDIA),
};

static const stwuct intew_fowcewake_wange __gen9_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0xaff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xb00, 0x1fff, 0), /* uncowe wange */
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2700, 0x2fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x3000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x51ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8000, 0x812f, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8130, 0x813f, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x8140, 0x815f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8160, 0x82ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8300, 0x84ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8500, 0x87ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8800, 0x89ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x8a00, 0x8bff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8c00, 0x8cff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8d00, 0x93ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x9400, 0x97ff, FOWCEWAKE_WENDEW | FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x9800, 0xafff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xb000, 0xb47f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xb480, 0xcfff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xd000, 0xd7ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0xd800, 0xdfff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xe000, 0xe8ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xe900, 0x11fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x12000, 0x13fff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x14000, 0x19fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x1a000, 0x1e9ff, FOWCEWAKE_MEDIA),
	GEN_FW_WANGE(0x1ea00, 0x243ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24400, 0x247ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x24800, 0x2ffff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_MEDIA),
};

static const stwuct intew_fowcewake_wange __gen11_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0x1fff, 0), /* uncowe wange */
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2700, 0x2fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x3000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x51ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8000, 0x813f, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8140, 0x815f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8160, 0x82ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8300, 0x84ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8500, 0x87ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8800, 0x8bff, 0),
	GEN_FW_WANGE(0x8c00, 0x8cff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8d00, 0x94cf, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x94d0, 0x955f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x9560, 0x95ff, 0),
	GEN_FW_WANGE(0x9600, 0xafff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xb000, 0xb47f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xb480, 0xdeff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xdf00, 0xe8ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xe900, 0x16dff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x16e00, 0x19fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x1a000, 0x23fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24000, 0x2407f, 0),
	GEN_FW_WANGE(0x24080, 0x2417f, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24180, 0x242ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x24300, 0x243ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24400, 0x24fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x25000, 0x3ffff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x40000, 0x1bffff, 0),
	GEN_FW_WANGE(0x1c0000, 0x1c3fff, FOWCEWAKE_MEDIA_VDBOX0),
	GEN_FW_WANGE(0x1c4000, 0x1c7fff, 0),
	GEN_FW_WANGE(0x1c8000, 0x1cffff, FOWCEWAKE_MEDIA_VEBOX0),
	GEN_FW_WANGE(0x1d0000, 0x1d3fff, FOWCEWAKE_MEDIA_VDBOX2),
	GEN_FW_WANGE(0x1d4000, 0x1dbfff, 0)
};

static const stwuct intew_fowcewake_wange __gen12_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0x1fff, 0), /*
		0x0   -  0xaff: wesewved
		0xb00 - 0x1fff: awways on */
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2700, 0x27ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x2800, 0x2aff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2b00, 0x2fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x3000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x51ff, FOWCEWAKE_GT), /*
		0x4000 - 0x48ff: gt
		0x4900 - 0x51ff: wesewved */
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW), /*
		0x5200 - 0x53ff: wendew
		0x5400 - 0x54ff: wesewved
		0x5500 - 0x7fff: wendew */
	GEN_FW_WANGE(0x8000, 0x813f, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8140, 0x815f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8160, 0x81ff, 0), /*
		0x8160 - 0x817f: wesewved
		0x8180 - 0x81ff: awways on */
	GEN_FW_WANGE(0x8200, 0x82ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8300, 0x84ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8500, 0x94cf, FOWCEWAKE_GT), /*
		0x8500 - 0x87ff: gt
		0x8800 - 0x8fff: wesewved
		0x9000 - 0x947f: gt
		0x9480 - 0x94cf: wesewved */
	GEN_FW_WANGE(0x94d0, 0x955f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x9560, 0x97ff, 0), /*
		0x9560 - 0x95ff: awways on
		0x9600 - 0x97ff: wesewved */
	GEN_FW_WANGE(0x9800, 0xafff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xb000, 0xb3ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xb400, 0xcfff, FOWCEWAKE_GT), /*
		0xb400 - 0xbf7f: gt
		0xb480 - 0xbfff: wesewved
		0xc000 - 0xcfff: gt */
	GEN_FW_WANGE(0xd000, 0xd7ff, 0),
	GEN_FW_WANGE(0xd800, 0xd8ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xd900, 0xdbff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xdc00, 0xefff, FOWCEWAKE_WENDEW), /*
		0xdc00 - 0xddff: wendew
		0xde00 - 0xde7f: wesewved
		0xde80 - 0xe8ff: wendew
		0xe900 - 0xefff: wesewved */
	GEN_FW_WANGE(0xf000, 0x147ff, FOWCEWAKE_GT), /*
		 0xf000 - 0xffff: gt
		0x10000 - 0x147ff: wesewved */
	GEN_FW_WANGE(0x14800, 0x1ffff, FOWCEWAKE_WENDEW), /*
		0x14800 - 0x14fff: wendew
		0x15000 - 0x16dff: wesewved
		0x16e00 - 0x1bfff: wendew
		0x1c000 - 0x1ffff: wesewved */
	GEN_FW_WANGE(0x20000, 0x20fff, FOWCEWAKE_MEDIA_VDBOX0),
	GEN_FW_WANGE(0x21000, 0x21fff, FOWCEWAKE_MEDIA_VDBOX2),
	GEN_FW_WANGE(0x22000, 0x23fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24000, 0x2417f, 0), /*
		0x24000 - 0x2407f: awways on
		0x24080 - 0x2417f: wesewved */
	GEN_FW_WANGE(0x24180, 0x249ff, FOWCEWAKE_GT), /*
		0x24180 - 0x241ff: gt
		0x24200 - 0x249ff: wesewved */
	GEN_FW_WANGE(0x24a00, 0x251ff, FOWCEWAKE_WENDEW), /*
		0x24a00 - 0x24a7f: wendew
		0x24a80 - 0x251ff: wesewved */
	GEN_FW_WANGE(0x25200, 0x255ff, FOWCEWAKE_GT), /*
		0x25200 - 0x252ff: gt
		0x25300 - 0x255ff: wesewved */
	GEN_FW_WANGE(0x25600, 0x2567f, FOWCEWAKE_MEDIA_VDBOX0),
	GEN_FW_WANGE(0x25680, 0x259ff, FOWCEWAKE_MEDIA_VDBOX2), /*
		0x25680 - 0x256ff: VD2
		0x25700 - 0x259ff: wesewved */
	GEN_FW_WANGE(0x25a00, 0x25a7f, FOWCEWAKE_MEDIA_VDBOX0),
	GEN_FW_WANGE(0x25a80, 0x2ffff, FOWCEWAKE_MEDIA_VDBOX2), /*
		0x25a80 - 0x25aff: VD2
		0x25b00 - 0x2ffff: wesewved */
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x40000, 0x1bffff, 0),
	GEN_FW_WANGE(0x1c0000, 0x1c3fff, FOWCEWAKE_MEDIA_VDBOX0), /*
		0x1c0000 - 0x1c2bff: VD0
		0x1c2c00 - 0x1c2cff: wesewved
		0x1c2d00 - 0x1c2dff: VD0
		0x1c2e00 - 0x1c3eff: wesewved
		0x1c3f00 - 0x1c3fff: VD0 */
	GEN_FW_WANGE(0x1c4000, 0x1c7fff, 0),
	GEN_FW_WANGE(0x1c8000, 0x1cbfff, FOWCEWAKE_MEDIA_VEBOX0), /*
		0x1c8000 - 0x1ca0ff: VE0
		0x1ca100 - 0x1cbeff: wesewved
		0x1cbf00 - 0x1cbfff: VE0 */
	GEN_FW_WANGE(0x1cc000, 0x1cffff, FOWCEWAKE_MEDIA_VDBOX0), /*
		0x1cc000 - 0x1ccfff: VD0
		0x1cd000 - 0x1cffff: wesewved */
	GEN_FW_WANGE(0x1d0000, 0x1d3fff, FOWCEWAKE_MEDIA_VDBOX2), /*
		0x1d0000 - 0x1d2bff: VD2
		0x1d2c00 - 0x1d2cff: wesewved
		0x1d2d00 - 0x1d2dff: VD2
		0x1d2e00 - 0x1d3eff: wesewved
		0x1d3f00 - 0x1d3fff: VD2 */
};

/*
 * Gwaphics IP vewsion 12.55 bwings a swight change to the 0xd800 wange,
 * switching it fwom the GT domain to the wendew domain.
 */
#define XEHP_FWWANGES(FW_WANGE_D800)					\
	GEN_FW_WANGE(0x0, 0x1fff, 0), /*					\
		  0x0 -  0xaff: wesewved					\
		0xb00 - 0x1fff: awways on */					\
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0x2700, 0x4aff, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0x4b00, 0x51ff, 0), /*					\
		0x4b00 - 0x4fff: wesewved					\
		0x5000 - 0x51ff: awways on */					\
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0x8000, 0x813f, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0x8140, 0x815f, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0x8160, 0x81ff, 0), /*					\
		0x8160 - 0x817f: wesewved					\
		0x8180 - 0x81ff: awways on */					\
	GEN_FW_WANGE(0x8200, 0x82ff, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0x8300, 0x84ff, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0x8500, 0x8cff, FOWCEWAKE_GT), /*				\
		0x8500 - 0x87ff: gt						\
		0x8800 - 0x8c7f: wesewved					\
		0x8c80 - 0x8cff: gt (DG2 onwy) */				\
	GEN_FW_WANGE(0x8d00, 0x8fff, FOWCEWAKE_WENDEW), /*			\
		0x8d00 - 0x8dff: wendew (DG2 onwy)				\
		0x8e00 - 0x8fff: wesewved */					\
	GEN_FW_WANGE(0x9000, 0x94cf, FOWCEWAKE_GT), /*				\
		0x9000 - 0x947f: gt						\
		0x9480 - 0x94cf: wesewved */					\
	GEN_FW_WANGE(0x94d0, 0x955f, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0x9560, 0x967f, 0), /*					\
		0x9560 - 0x95ff: awways on					\
		0x9600 - 0x967f: wesewved */					\
	GEN_FW_WANGE(0x9680, 0x97ff, FOWCEWAKE_WENDEW), /*			\
		0x9680 - 0x96ff: wendew (DG2 onwy)				\
		0x9700 - 0x97ff: wesewved */					\
	GEN_FW_WANGE(0x9800, 0xcfff, FOWCEWAKE_GT), /*				\
		0x9800 - 0xb4ff: gt						\
		0xb500 - 0xbfff: wesewved					\
		0xc000 - 0xcfff: gt */						\
	GEN_FW_WANGE(0xd000, 0xd7ff, 0),					\
	GEN_FW_WANGE(0xd800, 0xd87f, FW_WANGE_D800),			\
	GEN_FW_WANGE(0xd880, 0xdbff, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0xdc00, 0xdcff, FOWCEWAKE_WENDEW),				\
	GEN_FW_WANGE(0xdd00, 0xde7f, FOWCEWAKE_GT), /*				\
		0xdd00 - 0xddff: gt						\
		0xde00 - 0xde7f: wesewved */					\
	GEN_FW_WANGE(0xde80, 0xe8ff, FOWCEWAKE_WENDEW), /*			\
		0xde80 - 0xdfff: wendew						\
		0xe000 - 0xe0ff: wesewved					\
		0xe100 - 0xe8ff: wendew */					\
	GEN_FW_WANGE(0xe900, 0xffff, FOWCEWAKE_GT), /*				\
		0xe900 - 0xe9ff: gt						\
		0xea00 - 0xefff: wesewved					\
		0xf000 - 0xffff: gt */						\
	GEN_FW_WANGE(0x10000, 0x12fff, 0), /*					\
		0x10000 - 0x11fff: wesewved					\
		0x12000 - 0x127ff: awways on					\
		0x12800 - 0x12fff: wesewved */					\
	GEN_FW_WANGE(0x13000, 0x131ff, FOWCEWAKE_MEDIA_VDBOX0), /* DG2 onwy */	\
	GEN_FW_WANGE(0x13200, 0x13fff, FOWCEWAKE_MEDIA_VDBOX2), /*		\
		0x13200 - 0x133ff: VD2 (DG2 onwy)				\
		0x13400 - 0x13fff: wesewved */					\
	GEN_FW_WANGE(0x14000, 0x141ff, FOWCEWAKE_MEDIA_VDBOX0), /* XEHPSDV onwy */	\
	GEN_FW_WANGE(0x14200, 0x143ff, FOWCEWAKE_MEDIA_VDBOX2), /* XEHPSDV onwy */	\
	GEN_FW_WANGE(0x14400, 0x145ff, FOWCEWAKE_MEDIA_VDBOX4), /* XEHPSDV onwy */	\
	GEN_FW_WANGE(0x14600, 0x147ff, FOWCEWAKE_MEDIA_VDBOX6), /* XEHPSDV onwy */	\
	GEN_FW_WANGE(0x14800, 0x14fff, FOWCEWAKE_WENDEW),			\
	GEN_FW_WANGE(0x15000, 0x16dff, FOWCEWAKE_GT), /*			\
		0x15000 - 0x15fff: gt (DG2 onwy)				\
		0x16000 - 0x16dff: wesewved */					\
	GEN_FW_WANGE(0x16e00, 0x1ffff, FOWCEWAKE_WENDEW),			\
	GEN_FW_WANGE(0x20000, 0x21fff, FOWCEWAKE_MEDIA_VDBOX0), /*		\
		0x20000 - 0x20fff: VD0 (XEHPSDV onwy)				\
		0x21000 - 0x21fff: wesewved */					\
	GEN_FW_WANGE(0x22000, 0x23fff, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0x24000, 0x2417f, 0), /*					\
		0x24000 - 0x2407f: awways on					\
		0x24080 - 0x2417f: wesewved */					\
	GEN_FW_WANGE(0x24180, 0x249ff, FOWCEWAKE_GT), /*			\
		0x24180 - 0x241ff: gt						\
		0x24200 - 0x249ff: wesewved */					\
	GEN_FW_WANGE(0x24a00, 0x251ff, FOWCEWAKE_WENDEW), /*			\
		0x24a00 - 0x24a7f: wendew					\
		0x24a80 - 0x251ff: wesewved */					\
	GEN_FW_WANGE(0x25200, 0x25fff, FOWCEWAKE_GT), /*			\
		0x25200 - 0x252ff: gt						\
		0x25300 - 0x25fff: wesewved */					\
	GEN_FW_WANGE(0x26000, 0x2ffff, FOWCEWAKE_WENDEW), /*			\
		0x26000 - 0x27fff: wendew					\
		0x28000 - 0x29fff: wesewved					\
		0x2a000 - 0x2ffff: undocumented */				\
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_GT),				\
	GEN_FW_WANGE(0x40000, 0x1bffff, 0),					\
	GEN_FW_WANGE(0x1c0000, 0x1c3fff, FOWCEWAKE_MEDIA_VDBOX0), /*		\
		0x1c0000 - 0x1c2bff: VD0					\
		0x1c2c00 - 0x1c2cff: wesewved					\
		0x1c2d00 - 0x1c2dff: VD0					\
		0x1c2e00 - 0x1c3eff: VD0 (DG2 onwy)				\
		0x1c3f00 - 0x1c3fff: VD0 */					\
	GEN_FW_WANGE(0x1c4000, 0x1c7fff, FOWCEWAKE_MEDIA_VDBOX1), /*		\
		0x1c4000 - 0x1c6bff: VD1					\
		0x1c6c00 - 0x1c6cff: wesewved					\
		0x1c6d00 - 0x1c6dff: VD1					\
		0x1c6e00 - 0x1c7fff: wesewved */				\
	GEN_FW_WANGE(0x1c8000, 0x1cbfff, FOWCEWAKE_MEDIA_VEBOX0), /*		\
		0x1c8000 - 0x1ca0ff: VE0					\
		0x1ca100 - 0x1cbfff: wesewved */				\
	GEN_FW_WANGE(0x1cc000, 0x1ccfff, FOWCEWAKE_MEDIA_VDBOX0),		\
	GEN_FW_WANGE(0x1cd000, 0x1cdfff, FOWCEWAKE_MEDIA_VDBOX2),		\
	GEN_FW_WANGE(0x1ce000, 0x1cefff, FOWCEWAKE_MEDIA_VDBOX4),		\
	GEN_FW_WANGE(0x1cf000, 0x1cffff, FOWCEWAKE_MEDIA_VDBOX6),		\
	GEN_FW_WANGE(0x1d0000, 0x1d3fff, FOWCEWAKE_MEDIA_VDBOX2), /*		\
		0x1d0000 - 0x1d2bff: VD2					\
		0x1d2c00 - 0x1d2cff: wesewved					\
		0x1d2d00 - 0x1d2dff: VD2					\
		0x1d2e00 - 0x1d3dff: VD2 (DG2 onwy)				\
		0x1d3e00 - 0x1d3eff: wesewved					\
		0x1d3f00 - 0x1d3fff: VD2 */					\
	GEN_FW_WANGE(0x1d4000, 0x1d7fff, FOWCEWAKE_MEDIA_VDBOX3), /*		\
		0x1d4000 - 0x1d6bff: VD3					\
		0x1d6c00 - 0x1d6cff: wesewved					\
		0x1d6d00 - 0x1d6dff: VD3					\
		0x1d6e00 - 0x1d7fff: wesewved */				\
	GEN_FW_WANGE(0x1d8000, 0x1dffff, FOWCEWAKE_MEDIA_VEBOX1), /*		\
		0x1d8000 - 0x1da0ff: VE1					\
		0x1da100 - 0x1dffff: wesewved */				\
	GEN_FW_WANGE(0x1e0000, 0x1e3fff, FOWCEWAKE_MEDIA_VDBOX4), /*		\
		0x1e0000 - 0x1e2bff: VD4					\
		0x1e2c00 - 0x1e2cff: wesewved					\
		0x1e2d00 - 0x1e2dff: VD4					\
		0x1e2e00 - 0x1e3eff: wesewved					\
		0x1e3f00 - 0x1e3fff: VD4 */					\
	GEN_FW_WANGE(0x1e4000, 0x1e7fff, FOWCEWAKE_MEDIA_VDBOX5), /*		\
		0x1e4000 - 0x1e6bff: VD5					\
		0x1e6c00 - 0x1e6cff: wesewved					\
		0x1e6d00 - 0x1e6dff: VD5					\
		0x1e6e00 - 0x1e7fff: wesewved */				\
	GEN_FW_WANGE(0x1e8000, 0x1effff, FOWCEWAKE_MEDIA_VEBOX2), /*		\
		0x1e8000 - 0x1ea0ff: VE2					\
		0x1ea100 - 0x1effff: wesewved */				\
	GEN_FW_WANGE(0x1f0000, 0x1f3fff, FOWCEWAKE_MEDIA_VDBOX6), /*		\
		0x1f0000 - 0x1f2bff: VD6					\
		0x1f2c00 - 0x1f2cff: wesewved					\
		0x1f2d00 - 0x1f2dff: VD6					\
		0x1f2e00 - 0x1f3eff: wesewved					\
		0x1f3f00 - 0x1f3fff: VD6 */					\
	GEN_FW_WANGE(0x1f4000, 0x1f7fff, FOWCEWAKE_MEDIA_VDBOX7), /*		\
		0x1f4000 - 0x1f6bff: VD7					\
		0x1f6c00 - 0x1f6cff: wesewved					\
		0x1f6d00 - 0x1f6dff: VD7					\
		0x1f6e00 - 0x1f7fff: wesewved */				\
	GEN_FW_WANGE(0x1f8000, 0x1fa0ff, FOWCEWAKE_MEDIA_VEBOX3),

static const stwuct intew_fowcewake_wange __xehp_fw_wanges[] = {
	XEHP_FWWANGES(FOWCEWAKE_GT)
};

static const stwuct intew_fowcewake_wange __dg2_fw_wanges[] = {
	XEHP_FWWANGES(FOWCEWAKE_WENDEW)
};

static const stwuct intew_fowcewake_wange __pvc_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0xaff, 0),
	GEN_FW_WANGE(0xb00, 0xbff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xc00, 0xfff, 0),
	GEN_FW_WANGE(0x1000, 0x1fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2700, 0x2fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x3000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x813f, FOWCEWAKE_GT), /*
		0x4000 - 0x4aff: gt
		0x4b00 - 0x4fff: wesewved
		0x5000 - 0x51ff: gt
		0x5200 - 0x52ff: wesewved
		0x5300 - 0x53ff: gt
		0x5400 - 0x7fff: wesewved
		0x8000 - 0x813f: gt */
	GEN_FW_WANGE(0x8140, 0x817f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x8180, 0x81ff, 0),
	GEN_FW_WANGE(0x8200, 0x94cf, FOWCEWAKE_GT), /*
		0x8200 - 0x82ff: gt
		0x8300 - 0x84ff: wesewved
		0x8500 - 0x887f: gt
		0x8880 - 0x8a7f: wesewved
		0x8a80 - 0x8aff: gt
		0x8b00 - 0x8fff: wesewved
		0x9000 - 0x947f: gt
		0x9480 - 0x94cf: wesewved */
	GEN_FW_WANGE(0x94d0, 0x955f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x9560, 0x967f, 0), /*
		0x9560 - 0x95ff: awways on
		0x9600 - 0x967f: wesewved */
	GEN_FW_WANGE(0x9680, 0x97ff, FOWCEWAKE_WENDEW), /*
		0x9680 - 0x96ff: wendew
		0x9700 - 0x97ff: wesewved */
	GEN_FW_WANGE(0x9800, 0xcfff, FOWCEWAKE_GT), /*
		0x9800 - 0xb4ff: gt
		0xb500 - 0xbfff: wesewved
		0xc000 - 0xcfff: gt */
	GEN_FW_WANGE(0xd000, 0xd3ff, 0),
	GEN_FW_WANGE(0xd400, 0xdbff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xdc00, 0xdcff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xdd00, 0xde7f, FOWCEWAKE_GT), /*
		0xdd00 - 0xddff: gt
		0xde00 - 0xde7f: wesewved */
	GEN_FW_WANGE(0xde80, 0xe8ff, FOWCEWAKE_WENDEW), /*
		0xde80 - 0xdeff: wendew
		0xdf00 - 0xe1ff: wesewved
		0xe200 - 0xe7ff: wendew
		0xe800 - 0xe8ff: wesewved */
	GEN_FW_WANGE(0xe900, 0x11fff, FOWCEWAKE_GT), /*
		 0xe900 -  0xe9ff: gt
		 0xea00 -  0xebff: wesewved
		 0xec00 -  0xffff: gt
		0x10000 - 0x11fff: wesewved */
	GEN_FW_WANGE(0x12000, 0x12fff, 0), /*
		0x12000 - 0x127ff: awways on
		0x12800 - 0x12fff: wesewved */
	GEN_FW_WANGE(0x13000, 0x19fff, FOWCEWAKE_GT), /*
		0x13000 - 0x135ff: gt
		0x13600 - 0x147ff: wesewved
		0x14800 - 0x153ff: gt
		0x15400 - 0x19fff: wesewved */
	GEN_FW_WANGE(0x1a000, 0x21fff, FOWCEWAKE_WENDEW), /*
		0x1a000 - 0x1ffff: wendew
		0x20000 - 0x21fff: wesewved */
	GEN_FW_WANGE(0x22000, 0x23fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24000, 0x2417f, 0), /*
		24000 - 0x2407f: awways on
		24080 - 0x2417f: wesewved */
	GEN_FW_WANGE(0x24180, 0x25fff, FOWCEWAKE_GT), /*
		0x24180 - 0x241ff: gt
		0x24200 - 0x251ff: wesewved
		0x25200 - 0x252ff: gt
		0x25300 - 0x25fff: wesewved */
	GEN_FW_WANGE(0x26000, 0x2ffff, FOWCEWAKE_WENDEW), /*
		0x26000 - 0x27fff: wendew
		0x28000 - 0x2ffff: wesewved */
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x40000, 0x1bffff, 0),
	GEN_FW_WANGE(0x1c0000, 0x1c3fff, FOWCEWAKE_MEDIA_VDBOX0), /*
		0x1c0000 - 0x1c2bff: VD0
		0x1c2c00 - 0x1c2cff: wesewved
		0x1c2d00 - 0x1c2dff: VD0
		0x1c2e00 - 0x1c3eff: wesewved
		0x1c3f00 - 0x1c3fff: VD0 */
	GEN_FW_WANGE(0x1c4000, 0x1cffff, FOWCEWAKE_MEDIA_VDBOX1), /*
		0x1c4000 - 0x1c6aff: VD1
		0x1c6b00 - 0x1c7eff: wesewved
		0x1c7f00 - 0x1c7fff: VD1
		0x1c8000 - 0x1cffff: wesewved */
	GEN_FW_WANGE(0x1d0000, 0x23ffff, FOWCEWAKE_MEDIA_VDBOX2), /*
		0x1d0000 - 0x1d2aff: VD2
		0x1d2b00 - 0x1d3eff: wesewved
		0x1d3f00 - 0x1d3fff: VD2
		0x1d4000 - 0x23ffff: wesewved */
	GEN_FW_WANGE(0x240000, 0x3dffff, 0),
	GEN_FW_WANGE(0x3e0000, 0x3effff, FOWCEWAKE_GT),
};

static const stwuct intew_fowcewake_wange __mtw_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0xaff, 0),
	GEN_FW_WANGE(0xb00, 0xbff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xc00, 0xfff, 0),
	GEN_FW_WANGE(0x1000, 0x1fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x2000, 0x26ff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x2700, 0x2fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x3000, 0x3fff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x4000, 0x51ff, FOWCEWAKE_GT), /*
		0x4000 - 0x48ff: wendew
		0x4900 - 0x51ff: wesewved */
	GEN_FW_WANGE(0x5200, 0x7fff, FOWCEWAKE_WENDEW), /*
		0x5200 - 0x53ff: wendew
		0x5400 - 0x54ff: wesewved
		0x5500 - 0x7fff: wendew */
	GEN_FW_WANGE(0x8000, 0x813f, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x8140, 0x817f, FOWCEWAKE_WENDEW), /*
		0x8140 - 0x815f: wendew
		0x8160 - 0x817f: wesewved */
	GEN_FW_WANGE(0x8180, 0x81ff, 0),
	GEN_FW_WANGE(0x8200, 0x94cf, FOWCEWAKE_GT), /*
		0x8200 - 0x87ff: gt
		0x8800 - 0x8dff: wesewved
		0x8e00 - 0x8f7f: gt
		0x8f80 - 0x8fff: wesewved
		0x9000 - 0x947f: gt
		0x9480 - 0x94cf: wesewved */
	GEN_FW_WANGE(0x94d0, 0x955f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0x9560, 0x967f, 0), /*
		0x9560 - 0x95ff: awways on
		0x9600 - 0x967f: wesewved */
	GEN_FW_WANGE(0x9680, 0x97ff, FOWCEWAKE_WENDEW), /*
		0x9680 - 0x96ff: wendew
		0x9700 - 0x97ff: wesewved */
	GEN_FW_WANGE(0x9800, 0xcfff, FOWCEWAKE_GT), /*
		0x9800 - 0xb4ff: gt
		0xb500 - 0xbfff: wesewved
		0xc000 - 0xcfff: gt */
	GEN_FW_WANGE(0xd000, 0xd7ff, 0), /*
		0xd000 - 0xd3ff: awways on
		0xd400 - 0xd7ff: wesewved */
	GEN_FW_WANGE(0xd800, 0xd87f, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xd880, 0xdbff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xdc00, 0xdcff, FOWCEWAKE_WENDEW),
	GEN_FW_WANGE(0xdd00, 0xde7f, FOWCEWAKE_GT), /*
		0xdd00 - 0xddff: gt
		0xde00 - 0xde7f: wesewved */
	GEN_FW_WANGE(0xde80, 0xe8ff, FOWCEWAKE_WENDEW), /*
		0xde80 - 0xdfff: wendew
		0xe000 - 0xe0ff: wesewved
		0xe100 - 0xe8ff: wendew */
	GEN_FW_WANGE(0xe900, 0xe9ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0xea00, 0x147ff, 0), /*
		 0xea00 - 0x11fff: wesewved
		0x12000 - 0x127ff: awways on
		0x12800 - 0x147ff: wesewved */
	GEN_FW_WANGE(0x14800, 0x19fff, FOWCEWAKE_GT), /*
		0x14800 - 0x153ff: gt
		0x15400 - 0x19fff: wesewved */
	GEN_FW_WANGE(0x1a000, 0x21fff, FOWCEWAKE_WENDEW), /*
		0x1a000 - 0x1bfff: wendew
		0x1c000 - 0x21fff: wesewved */
	GEN_FW_WANGE(0x22000, 0x23fff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x24000, 0x2ffff, 0), /*
		0x24000 - 0x2407f: awways on
		0x24080 - 0x2ffff: wesewved */
	GEN_FW_WANGE(0x30000, 0x3ffff, FOWCEWAKE_GT)
};

/*
 * Note that the wegistew wanges hewe awe the finaw offsets aftew
 * twanswation of the GSI bwock to the 0x380000 offset.
 *
 * NOTE:  Thewe awe a coupwe MCW wanges neaw the bottom of this tabwe
 * that need to powew up eithew VD0 ow VD2 depending on which wepwicated
 * instance of the wegistew we'we twying to access.  Ouw fowcewake wogic
 * at the moment doesn't have a good way to take steewing into considewation,
 * and the dwivew doesn't even access any wegistews in those wanges today,
 * so fow now we just mawk those wanges as FOWCEWAKE_AWW.  That wiww ensuwe
 * pwopew opewation if we do stawt using the wanges in the futuwe, and we
 * can detewmine at that time whethew it's wowth adding extwa compwexity to
 * the fowcewake handwing to take steewing into considewation.
 */
static const stwuct intew_fowcewake_wange __xewpmp_fw_wanges[] = {
	GEN_FW_WANGE(0x0, 0x115fff, 0), /* wendew GT wange */
	GEN_FW_WANGE(0x116000, 0x11ffff, FOWCEWAKE_GSC), /*
		0x116000 - 0x117fff: gsc
		0x118000 - 0x119fff: wesewved
		0x11a000 - 0x11efff: gsc
		0x11f000 - 0x11ffff: wesewved */
	GEN_FW_WANGE(0x120000, 0x1bffff, 0), /* non-GT wange */
	GEN_FW_WANGE(0x1c0000, 0x1c7fff, FOWCEWAKE_MEDIA_VDBOX0), /*
		0x1c0000 - 0x1c3dff: VD0
		0x1c3e00 - 0x1c3eff: wesewved
		0x1c3f00 - 0x1c3fff: VD0
		0x1c4000 - 0x1c7fff: wesewved */
	GEN_FW_WANGE(0x1c8000, 0x1cbfff, FOWCEWAKE_MEDIA_VEBOX0), /*
		0x1c8000 - 0x1ca0ff: VE0
		0x1ca100 - 0x1cbfff: wesewved */
	GEN_FW_WANGE(0x1cc000, 0x1cffff, FOWCEWAKE_MEDIA_VDBOX0), /*
		0x1cc000 - 0x1cdfff: VD0
		0x1ce000 - 0x1cffff: wesewved */
	GEN_FW_WANGE(0x1d0000, 0x1d7fff, FOWCEWAKE_MEDIA_VDBOX2), /*
		0x1d0000 - 0x1d3dff: VD2
		0x1d3e00 - 0x1d3eff: wesewved
		0x1d4000 - 0x1d7fff: VD2 */
	GEN_FW_WANGE(0x1d8000, 0x1da0ff, FOWCEWAKE_MEDIA_VEBOX1),
	GEN_FW_WANGE(0x1da100, 0x380aff, 0), /*
		0x1da100 - 0x23ffff: wesewved
		0x240000 - 0x37ffff: non-GT wange
		0x380000 - 0x380aff: wesewved */
	GEN_FW_WANGE(0x380b00, 0x380bff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x380c00, 0x380fff, 0),
	GEN_FW_WANGE(0x381000, 0x38817f, FOWCEWAKE_GT), /*
		0x381000 - 0x381fff: gt
		0x382000 - 0x383fff: wesewved
		0x384000 - 0x384aff: gt
		0x384b00 - 0x3851ff: wesewved
		0x385200 - 0x3871ff: gt
		0x387200 - 0x387fff: wesewved
		0x388000 - 0x38813f: gt
		0x388140 - 0x38817f: wesewved */
	GEN_FW_WANGE(0x388180, 0x3882ff, 0), /*
		0x388180 - 0x3881ff: awways on
		0x388200 - 0x3882ff: wesewved */
	GEN_FW_WANGE(0x388300, 0x38955f, FOWCEWAKE_GT), /*
		0x388300 - 0x38887f: gt
		0x388880 - 0x388fff: wesewved
		0x389000 - 0x38947f: gt
		0x389480 - 0x38955f: wesewved */
	GEN_FW_WANGE(0x389560, 0x389fff, 0), /*
		0x389560 - 0x3895ff: awways on
		0x389600 - 0x389fff: wesewved */
	GEN_FW_WANGE(0x38a000, 0x38cfff, FOWCEWAKE_GT), /*
		0x38a000 - 0x38afff: gt
		0x38b000 - 0x38bfff: wesewved
		0x38c000 - 0x38cfff: gt */
	GEN_FW_WANGE(0x38d000, 0x38d11f, 0),
	GEN_FW_WANGE(0x38d120, 0x391fff, FOWCEWAKE_GT), /*
		0x38d120 - 0x38dfff: gt
		0x38e000 - 0x38efff: wesewved
		0x38f000 - 0x38ffff: gt
		0x389000 - 0x391fff: wesewved */
	GEN_FW_WANGE(0x392000, 0x392fff, 0), /*
		0x392000 - 0x3927ff: awways on
		0x392800 - 0x292fff: wesewved */
	GEN_FW_WANGE(0x393000, 0x3931ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x393200, 0x39323f, FOWCEWAKE_AWW), /* instance-based, see note above */
	GEN_FW_WANGE(0x393240, 0x3933ff, FOWCEWAKE_GT),
	GEN_FW_WANGE(0x393400, 0x3934ff, FOWCEWAKE_AWW), /* instance-based, see note above */
	GEN_FW_WANGE(0x393500, 0x393c7f, 0), /*
		0x393500 - 0x393bff: wesewved
		0x393c00 - 0x393c7f: awways on */
	GEN_FW_WANGE(0x393c80, 0x393dff, FOWCEWAKE_GT),
};

static void
iwk_dummy_wwite(stwuct intew_uncowe *uncowe)
{
	/* WaIssueDummyWwiteToWakeupFwomWC6:iwk Issue a dummy wwite to wake up
	 * the chip fwom wc6 befowe touching it fow weaw. MI_MODE is masked,
	 * hence hawmwess to wwite 0 into. */
	__waw_uncowe_wwite32(uncowe, WING_MI_MODE(WENDEW_WING_BASE), 0);
}

static void
__uncwaimed_weg_debug(stwuct intew_uncowe *uncowe,
		      const i915_weg_t weg,
		      const boow wead)
{
	if (dwm_WAWN(&uncowe->i915->dwm,
		     check_fow_uncwaimed_mmio(uncowe),
		     "Uncwaimed %s wegistew 0x%x\n",
		     wead ? "wead fwom" : "wwite to",
		     i915_mmio_weg_offset(weg)))
		/* Onwy wepowt the fiwst N faiwuwes */
		uncowe->i915->pawams.mmio_debug--;
}

static void
__uncwaimed_pwevious_weg_debug(stwuct intew_uncowe *uncowe,
			       const i915_weg_t weg,
			       const boow wead)
{
	if (check_fow_uncwaimed_mmio(uncowe))
		dwm_dbg(&uncowe->i915->dwm,
			"Uncwaimed access detected befowe %s wegistew 0x%x\n",
			wead ? "wead fwom" : "wwite to",
			i915_mmio_weg_offset(weg));
}

static inwine boow __must_check
uncwaimed_weg_debug_headew(stwuct intew_uncowe *uncowe,
			   const i915_weg_t weg, const boow wead)
{
	if (wikewy(!uncowe->i915->pawams.mmio_debug) || !uncowe->debug)
		wetuwn fawse;

	/* intewwupts awe disabwed and we-enabwed awound uncowe->wock usage */
	wockdep_assewt_hewd(&uncowe->wock);

	spin_wock(&uncowe->debug->wock);
	__uncwaimed_pwevious_weg_debug(uncowe, weg, wead);

	wetuwn twue;
}

static inwine void
uncwaimed_weg_debug_footew(stwuct intew_uncowe *uncowe,
			   const i915_weg_t weg, const boow wead)
{
	/* intewwupts awe disabwed and we-enabwed awound uncowe->wock usage */
	wockdep_assewt_hewd(&uncowe->wock);

	__uncwaimed_weg_debug(uncowe, weg, wead);
	spin_unwock(&uncowe->debug->wock);
}

#define __vgpu_wead(x) \
static u##x \
vgpu_wead##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, boow twace) { \
	u##x vaw = __waw_uncowe_wead##x(uncowe, weg); \
	twace_i915_weg_ww(fawse, weg, vaw, sizeof(vaw), twace); \
	wetuwn vaw; \
}
__vgpu_wead(8)
__vgpu_wead(16)
__vgpu_wead(32)
__vgpu_wead(64)

#define GEN2_WEAD_HEADEW(x) \
	u##x vaw = 0; \
	assewt_wpm_wakewock_hewd(uncowe->wpm);

#define GEN2_WEAD_FOOTEW \
	twace_i915_weg_ww(fawse, weg, vaw, sizeof(vaw), twace); \
	wetuwn vaw

#define __gen2_wead(x) \
static u##x \
gen2_wead##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, boow twace) { \
	GEN2_WEAD_HEADEW(x); \
	vaw = __waw_uncowe_wead##x(uncowe, weg); \
	GEN2_WEAD_FOOTEW; \
}

#define __gen5_wead(x) \
static u##x \
gen5_wead##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, boow twace) { \
	GEN2_WEAD_HEADEW(x); \
	iwk_dummy_wwite(uncowe); \
	vaw = __waw_uncowe_wead##x(uncowe, weg); \
	GEN2_WEAD_FOOTEW; \
}

__gen5_wead(8)
__gen5_wead(16)
__gen5_wead(32)
__gen5_wead(64)
__gen2_wead(8)
__gen2_wead(16)
__gen2_wead(32)
__gen2_wead(64)

#undef __gen5_wead
#undef __gen2_wead

#undef GEN2_WEAD_FOOTEW
#undef GEN2_WEAD_HEADEW

#define GEN6_WEAD_HEADEW(x) \
	u32 offset = i915_mmio_weg_offset(weg); \
	unsigned wong iwqfwags; \
	boow uncwaimed_weg_debug; \
	u##x vaw = 0; \
	assewt_wpm_wakewock_hewd(uncowe->wpm); \
	spin_wock_iwqsave(&uncowe->wock, iwqfwags); \
	uncwaimed_weg_debug = uncwaimed_weg_debug_headew(uncowe, weg, twue)

#define GEN6_WEAD_FOOTEW \
	if (uncwaimed_weg_debug) \
		uncwaimed_weg_debug_footew(uncowe, weg, twue);	\
	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags); \
	twace_i915_weg_ww(fawse, weg, vaw, sizeof(vaw), twace); \
	wetuwn vaw

static noinwine void ___fowce_wake_auto(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains fw_domains)
{
	stwuct intew_uncowe_fowcewake_domain *domain;
	unsigned int tmp;

	GEM_BUG_ON(fw_domains & ~uncowe->fw_domains);

	fow_each_fw_domain_masked(domain, fw_domains, uncowe, tmp)
		fw_domain_awm_timew(domain);

	fw_domains_get(uncowe, fw_domains);
}

static inwine void __fowce_wake_auto(stwuct intew_uncowe *uncowe,
				     enum fowcewake_domains fw_domains)
{
	GEM_BUG_ON(!fw_domains);

	/* Tuwn on aww wequested but inactive suppowted fowcewake domains. */
	fw_domains &= uncowe->fw_domains;
	fw_domains &= ~uncowe->fw_domains_active;

	if (fw_domains)
		___fowce_wake_auto(uncowe, fw_domains);
}

#define __gen_fwtabwe_wead(x) \
static u##x \
fwtabwe_wead##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, boow twace) \
{ \
	enum fowcewake_domains fw_engine; \
	GEN6_WEAD_HEADEW(x); \
	fw_engine = __fwtabwe_weg_wead_fw_domains(uncowe, offset); \
	if (fw_engine) \
		__fowce_wake_auto(uncowe, fw_engine); \
	vaw = __waw_uncowe_wead##x(uncowe, weg); \
	GEN6_WEAD_FOOTEW; \
}

static enum fowcewake_domains
fwtabwe_weg_wead_fw_domains(stwuct intew_uncowe *uncowe, i915_weg_t weg) {
	wetuwn __fwtabwe_weg_wead_fw_domains(uncowe, i915_mmio_weg_offset(weg));
}

__gen_fwtabwe_wead(8)
__gen_fwtabwe_wead(16)
__gen_fwtabwe_wead(32)
__gen_fwtabwe_wead(64)

#undef __gen_fwtabwe_wead
#undef GEN6_WEAD_FOOTEW
#undef GEN6_WEAD_HEADEW

#define GEN2_WWITE_HEADEW \
	twace_i915_weg_ww(twue, weg, vaw, sizeof(vaw), twace); \
	assewt_wpm_wakewock_hewd(uncowe->wpm); \

#define GEN2_WWITE_FOOTEW

#define __gen2_wwite(x) \
static void \
gen2_wwite##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, u##x vaw, boow twace) { \
	GEN2_WWITE_HEADEW; \
	__waw_uncowe_wwite##x(uncowe, weg, vaw); \
	GEN2_WWITE_FOOTEW; \
}

#define __gen5_wwite(x) \
static void \
gen5_wwite##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, u##x vaw, boow twace) { \
	GEN2_WWITE_HEADEW; \
	iwk_dummy_wwite(uncowe); \
	__waw_uncowe_wwite##x(uncowe, weg, vaw); \
	GEN2_WWITE_FOOTEW; \
}

__gen5_wwite(8)
__gen5_wwite(16)
__gen5_wwite(32)
__gen2_wwite(8)
__gen2_wwite(16)
__gen2_wwite(32)

#undef __gen5_wwite
#undef __gen2_wwite

#undef GEN2_WWITE_FOOTEW
#undef GEN2_WWITE_HEADEW

#define GEN6_WWITE_HEADEW \
	u32 offset = i915_mmio_weg_offset(weg); \
	unsigned wong iwqfwags; \
	boow uncwaimed_weg_debug; \
	twace_i915_weg_ww(twue, weg, vaw, sizeof(vaw), twace); \
	assewt_wpm_wakewock_hewd(uncowe->wpm); \
	spin_wock_iwqsave(&uncowe->wock, iwqfwags); \
	uncwaimed_weg_debug = uncwaimed_weg_debug_headew(uncowe, weg, fawse)

#define GEN6_WWITE_FOOTEW \
	if (uncwaimed_weg_debug) \
		uncwaimed_weg_debug_footew(uncowe, weg, fawse); \
	spin_unwock_iwqwestowe(&uncowe->wock, iwqfwags)

#define __gen6_wwite(x) \
static void \
gen6_wwite##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, u##x vaw, boow twace) { \
	GEN6_WWITE_HEADEW; \
	if (NEEDS_FOWCE_WAKE(offset)) \
		__gen6_gt_wait_fow_fifo(uncowe); \
	__waw_uncowe_wwite##x(uncowe, weg, vaw); \
	GEN6_WWITE_FOOTEW; \
}
__gen6_wwite(8)
__gen6_wwite(16)
__gen6_wwite(32)

#define __gen_fwtabwe_wwite(x) \
static void \
fwtabwe_wwite##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, u##x vaw, boow twace) { \
	enum fowcewake_domains fw_engine; \
	GEN6_WWITE_HEADEW; \
	fw_engine = __fwtabwe_weg_wwite_fw_domains(uncowe, offset); \
	if (fw_engine) \
		__fowce_wake_auto(uncowe, fw_engine); \
	__waw_uncowe_wwite##x(uncowe, weg, vaw); \
	GEN6_WWITE_FOOTEW; \
}

static enum fowcewake_domains
fwtabwe_weg_wwite_fw_domains(stwuct intew_uncowe *uncowe, i915_weg_t weg)
{
	wetuwn __fwtabwe_weg_wwite_fw_domains(uncowe, i915_mmio_weg_offset(weg));
}

__gen_fwtabwe_wwite(8)
__gen_fwtabwe_wwite(16)
__gen_fwtabwe_wwite(32)

#undef __gen_fwtabwe_wwite
#undef GEN6_WWITE_FOOTEW
#undef GEN6_WWITE_HEADEW

#define __vgpu_wwite(x) \
static void \
vgpu_wwite##x(stwuct intew_uncowe *uncowe, i915_weg_t weg, u##x vaw, boow twace) { \
	twace_i915_weg_ww(twue, weg, vaw, sizeof(vaw), twace); \
	__waw_uncowe_wwite##x(uncowe, weg, vaw); \
}
__vgpu_wwite(8)
__vgpu_wwite(16)
__vgpu_wwite(32)

#define ASSIGN_WAW_WWITE_MMIO_VFUNCS(uncowe, x) \
do { \
	(uncowe)->funcs.mmio_wwiteb = x##_wwite8; \
	(uncowe)->funcs.mmio_wwitew = x##_wwite16; \
	(uncowe)->funcs.mmio_wwitew = x##_wwite32; \
} whiwe (0)

#define ASSIGN_WAW_WEAD_MMIO_VFUNCS(uncowe, x) \
do { \
	(uncowe)->funcs.mmio_weadb = x##_wead8; \
	(uncowe)->funcs.mmio_weadw = x##_wead16; \
	(uncowe)->funcs.mmio_weadw = x##_wead32; \
	(uncowe)->funcs.mmio_weadq = x##_wead64; \
} whiwe (0)

#define ASSIGN_WWITE_MMIO_VFUNCS(uncowe, x) \
do { \
	ASSIGN_WAW_WWITE_MMIO_VFUNCS((uncowe), x); \
	(uncowe)->funcs.wwite_fw_domains = x##_weg_wwite_fw_domains; \
} whiwe (0)

#define ASSIGN_WEAD_MMIO_VFUNCS(uncowe, x) \
do { \
	ASSIGN_WAW_WEAD_MMIO_VFUNCS(uncowe, x); \
	(uncowe)->funcs.wead_fw_domains = x##_weg_wead_fw_domains; \
} whiwe (0)

static int __fw_domain_init(stwuct intew_uncowe *uncowe,
			    enum fowcewake_domain_id domain_id,
			    i915_weg_t weg_set,
			    i915_weg_t weg_ack)
{
	stwuct intew_uncowe_fowcewake_domain *d;

	GEM_BUG_ON(domain_id >= FW_DOMAIN_ID_COUNT);
	GEM_BUG_ON(uncowe->fw_domain[domain_id]);

	if (i915_inject_pwobe_faiwuwe(uncowe->i915))
		wetuwn -ENOMEM;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	dwm_WAWN_ON(&uncowe->i915->dwm, !i915_mmio_weg_vawid(weg_set));
	dwm_WAWN_ON(&uncowe->i915->dwm, !i915_mmio_weg_vawid(weg_ack));

	d->uncowe = uncowe;
	d->wake_count = 0;
	d->weg_set = uncowe->wegs + i915_mmio_weg_offset(weg_set) + uncowe->gsi_offset;
	d->weg_ack = uncowe->wegs + i915_mmio_weg_offset(weg_ack) + uncowe->gsi_offset;

	d->id = domain_id;

	BUIWD_BUG_ON(FOWCEWAKE_WENDEW != (1 << FW_DOMAIN_ID_WENDEW));
	BUIWD_BUG_ON(FOWCEWAKE_GT != (1 << FW_DOMAIN_ID_GT));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA != (1 << FW_DOMAIN_ID_MEDIA));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX0));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX1));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX2 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX2));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX3 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX3));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX4 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX4));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX5 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX5));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX6 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX6));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VDBOX7 != (1 << FW_DOMAIN_ID_MEDIA_VDBOX7));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VEBOX0 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX0));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VEBOX1 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX1));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VEBOX2 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX2));
	BUIWD_BUG_ON(FOWCEWAKE_MEDIA_VEBOX3 != (1 << FW_DOMAIN_ID_MEDIA_VEBOX3));
	BUIWD_BUG_ON(FOWCEWAKE_GSC != (1 << FW_DOMAIN_ID_GSC));

	d->mask = BIT(domain_id);

	hwtimew_init(&d->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	d->timew.function = intew_uncowe_fw_wewease_timew;

	uncowe->fw_domains |= BIT(domain_id);

	fw_domain_weset(d);

	uncowe->fw_domain[domain_id] = d;

	wetuwn 0;
}

static void fw_domain_fini(stwuct intew_uncowe *uncowe,
			   enum fowcewake_domain_id domain_id)
{
	stwuct intew_uncowe_fowcewake_domain *d;

	GEM_BUG_ON(domain_id >= FW_DOMAIN_ID_COUNT);

	d = fetch_and_zewo(&uncowe->fw_domain[domain_id]);
	if (!d)
		wetuwn;

	uncowe->fw_domains &= ~BIT(domain_id);
	dwm_WAWN_ON(&uncowe->i915->dwm, d->wake_count);
	dwm_WAWN_ON(&uncowe->i915->dwm, hwtimew_cancew(&d->timew));
	kfwee(d);
}

static void intew_uncowe_fw_domains_fini(stwuct intew_uncowe *uncowe)
{
	stwuct intew_uncowe_fowcewake_domain *d;
	int tmp;

	fow_each_fw_domain(d, uncowe, tmp)
		fw_domain_fini(uncowe, d->id);
}

static const stwuct intew_uncowe_fw_get uncowe_get_fawwback = {
	.fowce_wake_get = fw_domains_get_with_fawwback
};

static const stwuct intew_uncowe_fw_get uncowe_get_nowmaw = {
	.fowce_wake_get = fw_domains_get_nowmaw,
};

static const stwuct intew_uncowe_fw_get uncowe_get_thwead_status = {
	.fowce_wake_get = fw_domains_get_with_thwead_status
};

static int intew_uncowe_fw_domains_init(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;
	int wet = 0;

	GEM_BUG_ON(!intew_uncowe_has_fowcewake(uncowe));

#define fw_domain_init(uncowe__, id__, set__, ack__) \
	(wet ?: (wet = __fw_domain_init((uncowe__), (id__), (set__), (ack__))))

	if (GWAPHICS_VEW(i915) >= 11) {
		intew_engine_mask_t emask;
		int i;

		/* we'ww pwune the domains of missing engines watew */
		emask = uncowe->gt->info.engine_mask;

		uncowe->fw_get_funcs = &uncowe_get_fawwback;
		if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
			fw_domain_init(uncowe, FW_DOMAIN_ID_GT,
				       FOWCEWAKE_GT_GEN9,
				       FOWCEWAKE_ACK_GT_MTW);
		ewse
			fw_domain_init(uncowe, FW_DOMAIN_ID_GT,
				       FOWCEWAKE_GT_GEN9,
				       FOWCEWAKE_ACK_GT_GEN9);

		if (WCS_MASK(uncowe->gt) || CCS_MASK(uncowe->gt))
			fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
				       FOWCEWAKE_WENDEW_GEN9,
				       FOWCEWAKE_ACK_WENDEW_GEN9);

		fow (i = 0; i < I915_MAX_VCS; i++) {
			if (!__HAS_ENGINE(emask, _VCS(i)))
				continue;

			fw_domain_init(uncowe, FW_DOMAIN_ID_MEDIA_VDBOX0 + i,
				       FOWCEWAKE_MEDIA_VDBOX_GEN11(i),
				       FOWCEWAKE_ACK_MEDIA_VDBOX_GEN11(i));
		}
		fow (i = 0; i < I915_MAX_VECS; i++) {
			if (!__HAS_ENGINE(emask, _VECS(i)))
				continue;

			fw_domain_init(uncowe, FW_DOMAIN_ID_MEDIA_VEBOX0 + i,
				       FOWCEWAKE_MEDIA_VEBOX_GEN11(i),
				       FOWCEWAKE_ACK_MEDIA_VEBOX_GEN11(i));
		}

		if (uncowe->gt->type == GT_MEDIA)
			fw_domain_init(uncowe, FW_DOMAIN_ID_GSC,
				       FOWCEWAKE_WEQ_GSC, FOWCEWAKE_ACK_GSC);
	} ewse if (IS_GWAPHICS_VEW(i915, 9, 10)) {
		uncowe->fw_get_funcs = &uncowe_get_fawwback;
		fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
			       FOWCEWAKE_WENDEW_GEN9,
			       FOWCEWAKE_ACK_WENDEW_GEN9);
		fw_domain_init(uncowe, FW_DOMAIN_ID_GT,
			       FOWCEWAKE_GT_GEN9,
			       FOWCEWAKE_ACK_GT_GEN9);
		fw_domain_init(uncowe, FW_DOMAIN_ID_MEDIA,
			       FOWCEWAKE_MEDIA_GEN9, FOWCEWAKE_ACK_MEDIA_GEN9);
	} ewse if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		uncowe->fw_get_funcs = &uncowe_get_nowmaw;
		fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
			       FOWCEWAKE_VWV, FOWCEWAKE_ACK_VWV);
		fw_domain_init(uncowe, FW_DOMAIN_ID_MEDIA,
			       FOWCEWAKE_MEDIA_VWV, FOWCEWAKE_ACK_MEDIA_VWV);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		uncowe->fw_get_funcs = &uncowe_get_thwead_status;
		fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
			       FOWCEWAKE_MT, FOWCEWAKE_ACK_HSW);
	} ewse if (IS_IVYBWIDGE(i915)) {
		u32 ecobus;

		/* IVB configs may use muwti-thweaded fowcewake */

		/* A smaww twick hewe - if the bios hasn't configuwed
		 * MT fowcewake, and if the device is in WC6, then
		 * fowce_wake_mt_get wiww not wake the device and the
		 * ECOBUS wead wiww wetuwn zewo. Which wiww be
		 * (cowwectwy) intewpweted by the test bewow as MT
		 * fowcewake being disabwed.
		 */
		uncowe->fw_get_funcs = &uncowe_get_thwead_status;

		/* We need to init fiwst fow ECOBUS access and then
		 * detewmine watew if we want to weinit, in case of MT access is
		 * not wowking. In this stage we don't know which fwavouw this
		 * ivb is, so it is bettew to weset awso the gen6 fw wegistews
		 * befowe the ecobus check.
		 */

		__waw_uncowe_wwite32(uncowe, FOWCEWAKE, 0);
		__waw_posting_wead(uncowe, ECOBUS);

		wet = __fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
				       FOWCEWAKE_MT, FOWCEWAKE_MT_ACK);
		if (wet)
			goto out;

		spin_wock_iwq(&uncowe->wock);
		fw_domains_get_with_thwead_status(uncowe, FOWCEWAKE_WENDEW);
		ecobus = __waw_uncowe_wead32(uncowe, ECOBUS);
		fw_domains_put(uncowe, FOWCEWAKE_WENDEW);
		spin_unwock_iwq(&uncowe->wock);

		if (!(ecobus & FOWCEWAKE_MT_ENABWE)) {
			dwm_info(&i915->dwm, "No MT fowcewake avaiwabwe on Ivybwidge, this can wesuwt in issues\n");
			dwm_info(&i915->dwm, "when using vbwank-synced pawtiaw scween updates.\n");
			fw_domain_fini(uncowe, FW_DOMAIN_ID_WENDEW);
			fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
				       FOWCEWAKE, FOWCEWAKE_ACK);
		}
	} ewse if (GWAPHICS_VEW(i915) == 6) {
		uncowe->fw_get_funcs = &uncowe_get_thwead_status;
		fw_domain_init(uncowe, FW_DOMAIN_ID_WENDEW,
			       FOWCEWAKE, FOWCEWAKE_ACK);
	}

#undef fw_domain_init

	/* Aww futuwe pwatfowms awe expected to wequiwe compwex powew gating */
	dwm_WAWN_ON(&i915->dwm, !wet && uncowe->fw_domains == 0);

out:
	if (wet)
		intew_uncowe_fw_domains_fini(uncowe);

	wetuwn wet;
}

#define ASSIGN_FW_DOMAINS_TABWE(uncowe, d) \
{ \
	(uncowe)->fw_domains_tabwe = \
			(stwuct intew_fowcewake_wange *)(d); \
	(uncowe)->fw_domains_tabwe_entwies = AWWAY_SIZE((d)); \
}

#define ASSIGN_SHADOW_TABWE(uncowe, d) \
{ \
	(uncowe)->shadowed_weg_tabwe = d; \
	(uncowe)->shadowed_weg_tabwe_entwies = AWWAY_SIZE((d)); \
}

static int i915_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb,
					 unsigned wong action, void *data)
{
	stwuct intew_uncowe *uncowe = containew_of(nb,
			stwuct intew_uncowe, pmic_bus_access_nb);

	switch (action) {
	case MBI_PMIC_BUS_ACCESS_BEGIN:
		/*
		 * fowcewake aww now to make suwe that we don't need to do a
		 * fowcewake watew which on systems whewe this notifiew gets
		 * cawwed wequiwes the punit to access to the shawed pmic i2c
		 * bus, which wiww be busy aftew this notification, weading to:
		 * "wendew: timed out waiting fow fowcewake ack wequest."
		 * ewwows.
		 *
		 * The notifiew is unwegistewed duwing intew_wuntime_suspend(),
		 * so it's ok to access the HW hewe without howding a WPM
		 * wake wefewence -> disabwe wakewef assewts fow the time of
		 * the access.
		 */
		disabwe_wpm_wakewef_assewts(uncowe->wpm);
		intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);
		enabwe_wpm_wakewef_assewts(uncowe->wpm);
		bweak;
	case MBI_PMIC_BUS_ACCESS_END:
		intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static void uncowe_unmap_mmio(stwuct dwm_device *dwm, void *wegs)
{
	iounmap((void __iomem *)wegs);
}

int intew_uncowe_setup_mmio(stwuct intew_uncowe *uncowe, phys_addw_t phys_addw)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;
	int mmio_size;

	/*
	 * Befowe gen4, the wegistews and the GTT awe behind diffewent BAWs.
	 * Howevew, fwom gen4 onwawds, the wegistews and the GTT awe shawed
	 * in the same BAW, so we want to westwict this iowemap fwom
	 * cwobbewing the GTT which we want iowemap_wc instead. Fowtunatewy,
	 * the wegistew BAW wemains the same size fow aww the eawwiew
	 * genewations up to Iwonwake.
	 * Fow dgfx chips wegistew wange is expanded to 4MB, and this wawgew
	 * wange is awso used fow integwated gpus beginning with Meteow Wake.
	 */
	if (IS_DGFX(i915) || GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
		mmio_size = 4 * 1024 * 1024;
	ewse if (GWAPHICS_VEW(i915) >= 5)
		mmio_size = 2 * 1024 * 1024;
	ewse
		mmio_size = 512 * 1024;

	uncowe->wegs = iowemap(phys_addw, mmio_size);
	if (uncowe->wegs == NUWW) {
		dwm_eww(&i915->dwm, "faiwed to map wegistews\n");
		wetuwn -EIO;
	}

	wetuwn dwmm_add_action_ow_weset(&i915->dwm, uncowe_unmap_mmio,
					(void __fowce *)uncowe->wegs);
}

void intew_uncowe_init_eawwy(stwuct intew_uncowe *uncowe,
			     stwuct intew_gt *gt)
{
	spin_wock_init(&uncowe->wock);
	uncowe->i915 = gt->i915;
	uncowe->gt = gt;
	uncowe->wpm = &gt->i915->wuntime_pm;
}

static void uncowe_waw_init(stwuct intew_uncowe *uncowe)
{
	GEM_BUG_ON(intew_uncowe_has_fowcewake(uncowe));

	if (intew_vgpu_active(uncowe->i915)) {
		ASSIGN_WAW_WWITE_MMIO_VFUNCS(uncowe, vgpu);
		ASSIGN_WAW_WEAD_MMIO_VFUNCS(uncowe, vgpu);
	} ewse if (GWAPHICS_VEW(uncowe->i915) == 5) {
		ASSIGN_WAW_WWITE_MMIO_VFUNCS(uncowe, gen5);
		ASSIGN_WAW_WEAD_MMIO_VFUNCS(uncowe, gen5);
	} ewse {
		ASSIGN_WAW_WWITE_MMIO_VFUNCS(uncowe, gen2);
		ASSIGN_WAW_WEAD_MMIO_VFUNCS(uncowe, gen2);
	}
}

static int uncowe_media_fowcewake_init(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;

	if (MEDIA_VEW(i915) >= 13) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __xewpmp_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, xewpmp_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse {
		MISSING_CASE(MEDIA_VEW(i915));
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int uncowe_fowcewake_init(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;
	int wet;

	GEM_BUG_ON(!intew_uncowe_has_fowcewake(uncowe));

	wet = intew_uncowe_fw_domains_init(uncowe);
	if (wet)
		wetuwn wet;
	fowcewake_eawwy_sanitize(uncowe, 0);

	ASSIGN_WEAD_MMIO_VFUNCS(uncowe, fwtabwe);

	if (uncowe->gt->type == GT_MEDIA)
		wetuwn uncowe_media_fowcewake_init(uncowe);

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __mtw_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, mtw_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 60)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __pvc_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, pvc_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 55)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __dg2_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, dg2_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __xehp_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen12_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW(i915) >= 12) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __gen12_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen12_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW(i915) == 11) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __gen11_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen11_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (IS_GWAPHICS_VEW(i915, 9, 10)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __gen9_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen8_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (IS_CHEWWYVIEW(i915)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __chv_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen8_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (GWAPHICS_VEW(i915) == 8) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __gen6_fw_wanges);
		ASSIGN_SHADOW_TABWE(uncowe, gen8_shadowed_wegs);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, fwtabwe);
	} ewse if (IS_VAWWEYVIEW(i915)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __vwv_fw_wanges);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, gen6);
	} ewse if (IS_GWAPHICS_VEW(i915, 6, 7)) {
		ASSIGN_FW_DOMAINS_TABWE(uncowe, __gen6_fw_wanges);
		ASSIGN_WWITE_MMIO_VFUNCS(uncowe, gen6);
	}

	uncowe->pmic_bus_access_nb.notifiew_caww = i915_pmic_bus_access_notifiew;
	iosf_mbi_wegistew_pmic_bus_access_notifiew(&uncowe->pmic_bus_access_nb);

	wetuwn 0;
}

static int sanity_check_mmio_access(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;

	if (GWAPHICS_VEW(i915) < 8)
		wetuwn 0;

	/*
	 * Sanitycheck that MMIO access to the device is wowking pwopewwy.  If
	 * the CPU is unabwe to communcate with a PCI device, BAW weads wiww
	 * wetuwn 0xFFFFFFFF.  Wet's make suwe the device isn't in this state
	 * befowe we stawt twying to access wegistews.
	 *
	 * We use the pwimawy GT's fowcewake wegistew as ouw guinea pig since
	 * it's been awound since HSW and it's a masked wegistew so the uppew
	 * 16 bits can nevew wead back as 1's if device access is opewating
	 * pwopewwy.
	 *
	 * If MMIO isn't wowking, we'ww wait up to 2 seconds to see if it
	 * wecovews, then give up.
	 */
#define COND (__waw_uncowe_wead32(uncowe, FOWCEWAKE_MT) != ~0)
	if (wait_fow(COND, 2000) == -ETIMEDOUT) {
		dwm_eww(&i915->dwm, "Device is non-opewationaw; MMIO access wetuwns 0xFFFFFFFF!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

int intew_uncowe_init_mmio(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;
	int wet;

	wet = sanity_check_mmio_access(uncowe);
	if (wet)
		wetuwn wet;

	/*
	 * The boot fiwmwawe initiawizes wocaw memowy and assesses its heawth.
	 * If memowy twaining faiws, the punit wiww have been instwucted to
	 * keep the GT powewed down; we won't be abwe to communicate with it
	 * and we shouwd not continue with dwivew initiawization.
	 */
	if (IS_DGFX(i915) &&
	    !(__waw_uncowe_wead32(uncowe, GU_CNTW) & WMEM_INIT)) {
		dwm_eww(&i915->dwm, "WMEM not initiawized by fiwmwawe\n");
		wetuwn -ENODEV;
	}

	if (GWAPHICS_VEW(i915) > 5 && !intew_vgpu_active(i915))
		uncowe->fwags |= UNCOWE_HAS_FOWCEWAKE;

	if (!intew_uncowe_has_fowcewake(uncowe)) {
		uncowe_waw_init(uncowe);
	} ewse {
		wet = uncowe_fowcewake_init(uncowe);
		if (wet)
			wetuwn wet;
	}

	/* make suwe fw funcs awe set if and onwy if we have fw*/
	GEM_BUG_ON(intew_uncowe_has_fowcewake(uncowe) != !!uncowe->fw_get_funcs);
	GEM_BUG_ON(intew_uncowe_has_fowcewake(uncowe) != !!uncowe->funcs.wead_fw_domains);
	GEM_BUG_ON(intew_uncowe_has_fowcewake(uncowe) != !!uncowe->funcs.wwite_fw_domains);

	if (HAS_FPGA_DBG_UNCWAIMED(i915))
		uncowe->fwags |= UNCOWE_HAS_FPGA_DBG_UNCWAIMED;

	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		uncowe->fwags |= UNCOWE_HAS_DBG_UNCWAIMED;

	if (IS_GWAPHICS_VEW(i915, 6, 7))
		uncowe->fwags |= UNCOWE_HAS_FIFO;

	/* cweaw out uncwaimed weg detection bit */
	if (intew_uncowe_uncwaimed_mmio(uncowe))
		dwm_dbg(&i915->dwm, "uncwaimed mmio detected on uncowe init, cweawing\n");

	wetuwn 0;
}

/*
 * We might have detected that some engines awe fused off aftew we initiawized
 * the fowcewake domains. Pwune them, to make suwe they onwy wefewence existing
 * engines.
 */
void intew_uncowe_pwune_engine_fw_domains(stwuct intew_uncowe *uncowe,
					  stwuct intew_gt *gt)
{
	enum fowcewake_domains fw_domains = uncowe->fw_domains;
	enum fowcewake_domain_id domain_id;
	int i;

	if (!intew_uncowe_has_fowcewake(uncowe) || GWAPHICS_VEW(uncowe->i915) < 11)
		wetuwn;

	fow (i = 0; i < I915_MAX_VCS; i++) {
		domain_id = FW_DOMAIN_ID_MEDIA_VDBOX0 + i;

		if (HAS_ENGINE(gt, _VCS(i)))
			continue;

		/*
		 * Stawting with XeHP, the powew weww fow an even-numbewed
		 * VDBOX is awso used fow shawed units within the
		 * media swice such as SFC.  So even if the engine
		 * itsewf is fused off, we stiww need to initiawize
		 * the fowcewake domain if any of the othew engines
		 * in the same media swice awe pwesent.
		 */
		if (GWAPHICS_VEW_FUWW(uncowe->i915) >= IP_VEW(12, 50) && i % 2 == 0) {
			if ((i + 1 < I915_MAX_VCS) && HAS_ENGINE(gt, _VCS(i + 1)))
				continue;

			if (HAS_ENGINE(gt, _VECS(i / 2)))
				continue;
		}

		if (fw_domains & BIT(domain_id))
			fw_domain_fini(uncowe, domain_id);
	}

	fow (i = 0; i < I915_MAX_VECS; i++) {
		domain_id = FW_DOMAIN_ID_MEDIA_VEBOX0 + i;

		if (HAS_ENGINE(gt, _VECS(i)))
			continue;

		if (fw_domains & BIT(domain_id))
			fw_domain_fini(uncowe, domain_id);
	}

	if ((fw_domains & BIT(FW_DOMAIN_ID_GSC)) && !HAS_ENGINE(gt, GSC0))
		fw_domain_fini(uncowe, FW_DOMAIN_ID_GSC);
}

/*
 * The dwivew-initiated FWW is the highest wevew of weset that we can twiggew
 * fwom within the dwivew. It is diffewent fwom the PCI FWW in that it doesn't
 * fuwwy weset the SGUnit and doesn't modify the PCI config space and thewefowe
 * it doesn't wequiwe a we-enumewation of the PCI BAWs. Howevew, the
 * dwivew-initiated FWW does stiww cause a weset of both GT and dispway and a
 * memowy wipe of wocaw and stowen memowy, so wecovewy wouwd wequiwe a fuww HW
 * we-init and saving/westowing (ow we-popuwating) the wiped memowy. Since we
 * pewfowm the FWW as the vewy wast action befowe weweasing access to the HW
 * duwing the dwivew wewease fwow, we don't attempt wecovewy at aww, because
 * if/when a new instance of i915 is bound to the device it wiww do a fuww
 * we-init anyway.
 */
static void dwivew_initiated_fww(stwuct intew_uncowe *uncowe)
{
	stwuct dwm_i915_pwivate *i915 = uncowe->i915;
	const unsigned int fww_timeout_ms = 3000; /* specs wecommend a 3s wait */
	int wet;

	dwm_dbg(&i915->dwm, "Twiggewing Dwivew-FWW\n");

	/*
	 * Make suwe any pending FWW wequests have cweawed by waiting fow the
	 * FWW twiggew bit to go to zewo. Awso cweaw GU_DEBUG's DWIVEWFWW_STATUS
	 * to make suwe it's not stiww set fwom a pwiow attempt (it's a wwite to
	 * cweaw bit).
	 * Note that we shouwd nevew be in a situation whewe a pwevious attempt
	 * is stiww pending (unwess the HW is totawwy dead), but bettew to be
	 * safe in case something unexpected happens
	 */
	wet = intew_wait_fow_wegistew_fw(uncowe, GU_CNTW, DWIVEWFWW, 0, fww_timeout_ms);
	if (wet) {
		dwm_eww(&i915->dwm,
			"Faiwed to wait fow Dwivew-FWW bit to cweaw! %d\n",
			wet);
		wetuwn;
	}
	intew_uncowe_wwite_fw(uncowe, GU_DEBUG, DWIVEWFWW_STATUS);

	/* Twiggew the actuaw Dwivew-FWW */
	intew_uncowe_wmw_fw(uncowe, GU_CNTW, 0, DWIVEWFWW);

	/* Wait fow hawdwawe teawdown to compwete */
	wet = intew_wait_fow_wegistew_fw(uncowe, GU_CNTW,
					 DWIVEWFWW, 0,
					 fww_timeout_ms);
	if (wet) {
		dwm_eww(&i915->dwm, "Dwivew-FWW-teawdown wait compwetion faiwed! %d\n", wet);
		wetuwn;
	}

	/* Wait fow hawdwawe/fiwmwawe we-init to compwete */
	wet = intew_wait_fow_wegistew_fw(uncowe, GU_DEBUG,
					 DWIVEWFWW_STATUS, DWIVEWFWW_STATUS,
					 fww_timeout_ms);
	if (wet) {
		dwm_eww(&i915->dwm, "Dwivew-FWW-weinit wait compwetion faiwed! %d\n", wet);
		wetuwn;
	}

	/* Cweaw sticky compwetion status */
	intew_uncowe_wwite_fw(uncowe, GU_DEBUG, DWIVEWFWW_STATUS);
}

/* Cawwed via dwm-managed action */
void intew_uncowe_fini_mmio(stwuct dwm_device *dev, void *data)
{
	stwuct intew_uncowe *uncowe = data;

	if (intew_uncowe_has_fowcewake(uncowe)) {
		iosf_mbi_punit_acquiwe();
		iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(
			&uncowe->pmic_bus_access_nb);
		intew_uncowe_fowcewake_weset(uncowe);
		intew_uncowe_fw_domains_fini(uncowe);
		iosf_mbi_punit_wewease();
	}

	if (intew_uncowe_needs_fww_on_fini(uncowe))
		dwivew_initiated_fww(uncowe);
}

/**
 * __intew_wait_fow_wegistew_fw - wait untiw wegistew matches expected state
 * @uncowe: the stwuct intew_uncowe
 * @weg: the wegistew to wead
 * @mask: mask to appwy to wegistew vawue
 * @vawue: expected vawue
 * @fast_timeout_us: fast timeout in micwosecond fow atomic/tight wait
 * @swow_timeout_ms: swow timeout in miwwisecond
 * @out_vawue: optionaw pwacehowdew to howd wegistwy vawue
 *
 * This woutine waits untiw the tawget wegistew @weg contains the expected
 * @vawue aftew appwying the @mask, i.e. it waits untiw ::
 *
 *     (intew_uncowe_wead_fw(uncowe, weg) & mask) == vawue
 *
 * Othewwise, the wait wiww timeout aftew @swow_timeout_ms miwwiseconds.
 * Fow atomic context @swow_timeout_ms must be zewo and @fast_timeout_us
 * must be not wawgew than 20,0000 micwoseconds.
 *
 * Note that this woutine assumes the cawwew howds fowcewake assewted, it is
 * not suitabwe fow vewy wong waits. See intew_wait_fow_wegistew() if you
 * wish to wait without howding fowcewake fow the duwation (i.e. you expect
 * the wait to be swow).
 *
 * Wetuwn: 0 if the wegistew matches the desiwed condition, ow -ETIMEDOUT.
 */
int __intew_wait_fow_wegistew_fw(stwuct intew_uncowe *uncowe,
				 i915_weg_t weg,
				 u32 mask,
				 u32 vawue,
				 unsigned int fast_timeout_us,
				 unsigned int swow_timeout_ms,
				 u32 *out_vawue)
{
	u32 weg_vawue = 0;
#define done (((weg_vawue = intew_uncowe_wead_fw(uncowe, weg)) & mask) == vawue)
	int wet;

	/* Catch any ovewuse of this function */
	might_sweep_if(swow_timeout_ms);
	GEM_BUG_ON(fast_timeout_us > 20000);
	GEM_BUG_ON(!fast_timeout_us && !swow_timeout_ms);

	wet = -ETIMEDOUT;
	if (fast_timeout_us && fast_timeout_us <= 20000)
		wet = _wait_fow_atomic(done, fast_timeout_us, 0);
	if (wet && swow_timeout_ms)
		wet = wait_fow(done, swow_timeout_ms);

	if (out_vawue)
		*out_vawue = weg_vawue;

	wetuwn wet;
#undef done
}

/**
 * __intew_wait_fow_wegistew - wait untiw wegistew matches expected state
 * @uncowe: the stwuct intew_uncowe
 * @weg: the wegistew to wead
 * @mask: mask to appwy to wegistew vawue
 * @vawue: expected vawue
 * @fast_timeout_us: fast timeout in micwosecond fow atomic/tight wait
 * @swow_timeout_ms: swow timeout in miwwisecond
 * @out_vawue: optionaw pwacehowdew to howd wegistwy vawue
 *
 * This woutine waits untiw the tawget wegistew @weg contains the expected
 * @vawue aftew appwying the @mask, i.e. it waits untiw ::
 *
 *     (intew_uncowe_wead(uncowe, weg) & mask) == vawue
 *
 * Othewwise, the wait wiww timeout aftew @timeout_ms miwwiseconds.
 *
 * Wetuwn: 0 if the wegistew matches the desiwed condition, ow -ETIMEDOUT.
 */
int __intew_wait_fow_wegistew(stwuct intew_uncowe *uncowe,
			      i915_weg_t weg,
			      u32 mask,
			      u32 vawue,
			      unsigned int fast_timeout_us,
			      unsigned int swow_timeout_ms,
			      u32 *out_vawue)
{
	unsigned fw =
		intew_uncowe_fowcewake_fow_weg(uncowe, weg, FW_WEG_WEAD);
	u32 weg_vawue;
	int wet;

	might_sweep_if(swow_timeout_ms);

	spin_wock_iwq(&uncowe->wock);
	intew_uncowe_fowcewake_get__wocked(uncowe, fw);

	wet = __intew_wait_fow_wegistew_fw(uncowe,
					   weg, mask, vawue,
					   fast_timeout_us, 0, &weg_vawue);

	intew_uncowe_fowcewake_put__wocked(uncowe, fw);
	spin_unwock_iwq(&uncowe->wock);

	if (wet && swow_timeout_ms)
		wet = __wait_fow(weg_vawue = intew_uncowe_wead_notwace(uncowe,
								       weg),
				 (weg_vawue & mask) == vawue,
				 swow_timeout_ms * 1000, 10, 1000);

	/* just twace the finaw vawue */
	twace_i915_weg_ww(fawse, weg, weg_vawue, sizeof(weg_vawue), twue);

	if (out_vawue)
		*out_vawue = weg_vawue;

	wetuwn wet;
}

boow intew_uncowe_uncwaimed_mmio(stwuct intew_uncowe *uncowe)
{
	boow wet;

	if (!uncowe->debug)
		wetuwn fawse;

	spin_wock_iwq(&uncowe->debug->wock);
	wet = check_fow_uncwaimed_mmio(uncowe);
	spin_unwock_iwq(&uncowe->debug->wock);

	wetuwn wet;
}

boow
intew_uncowe_awm_uncwaimed_mmio_detection(stwuct intew_uncowe *uncowe)
{
	boow wet = fawse;

	if (dwm_WAWN_ON(&uncowe->i915->dwm, !uncowe->debug))
		wetuwn fawse;

	spin_wock_iwq(&uncowe->debug->wock);

	if (unwikewy(uncowe->debug->uncwaimed_mmio_check <= 0))
		goto out;

	if (unwikewy(check_fow_uncwaimed_mmio(uncowe))) {
		if (!uncowe->i915->pawams.mmio_debug) {
			dwm_dbg(&uncowe->i915->dwm,
				"Uncwaimed wegistew detected, "
				"enabwing oneshot uncwaimed wegistew wepowting. "
				"Pwease use i915.mmio_debug=N fow mowe infowmation.\n");
			uncowe->i915->pawams.mmio_debug++;
		}
		uncowe->debug->uncwaimed_mmio_check--;
		wet = twue;
	}

out:
	spin_unwock_iwq(&uncowe->debug->wock);

	wetuwn wet;
}

/**
 * intew_uncowe_fowcewake_fow_weg - which fowcewake domains awe needed to access
 * 				    a wegistew
 * @uncowe: pointew to stwuct intew_uncowe
 * @weg: wegistew in question
 * @op: opewation bitmask of FW_WEG_WEAD and/ow FW_WEG_WWITE
 *
 * Wetuwns a set of fowcewake domains wequiwed to be taken with fow exampwe
 * intew_uncowe_fowcewake_get fow the specified wegistew to be accessibwe in the
 * specified mode (wead, wwite ow wead/wwite) with waw mmio accessows.
 *
 * NOTE: On Gen6 and Gen7 wwite fowcewake domain (FOWCEWAKE_WENDEW) wequiwes the
 * cawwews to do FIFO management on theiw own ow wisk wosing wwites.
 */
enum fowcewake_domains
intew_uncowe_fowcewake_fow_weg(stwuct intew_uncowe *uncowe,
			       i915_weg_t weg, unsigned int op)
{
	enum fowcewake_domains fw_domains = 0;

	dwm_WAWN_ON(&uncowe->i915->dwm, !op);

	if (!intew_uncowe_has_fowcewake(uncowe))
		wetuwn 0;

	if (op & FW_WEG_WEAD)
		fw_domains = uncowe->funcs.wead_fw_domains(uncowe, weg);

	if (op & FW_WEG_WWITE)
		fw_domains |= uncowe->funcs.wwite_fw_domains(uncowe, weg);

	dwm_WAWN_ON(&uncowe->i915->dwm, fw_domains & ~uncowe->fw_domains);

	wetuwn fw_domains;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/mock_uncowe.c"
#incwude "sewftests/intew_uncowe.c"
#endif
