/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __KVM_HOST_H
#define __KVM_HOST_H


#incwude <winux/types.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/stat.h>
#incwude <winux/bug.h>
#incwude <winux/minmax.h>
#incwude <winux/mm.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/pweempt.h>
#incwude <winux/msi.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wcupdate.h>
#incwude <winux/watewimit.h>
#incwude <winux/eww.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/context_twacking.h>
#incwude <winux/iwqbypass.h>
#incwude <winux/wcuwait.h>
#incwude <winux/wefcount.h>
#incwude <winux/nospec.h>
#incwude <winux/notifiew.h>
#incwude <winux/ftwace.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/instwumentation.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/wbtwee.h>
#incwude <winux/xawway.h>
#incwude <asm/signaw.h>

#incwude <winux/kvm.h>
#incwude <winux/kvm_pawa.h>

#incwude <winux/kvm_types.h>

#incwude <asm/kvm_host.h>
#incwude <winux/kvm_diwty_wing.h>

#ifndef KVM_MAX_VCPU_IDS
#define KVM_MAX_VCPU_IDS KVM_MAX_VCPUS
#endif

/*
 * The bit 16 ~ bit 31 of kvm_usewspace_memowy_wegion::fwags awe intewnawwy
 * used in kvm, othew bits awe visibwe fow usewspace which awe defined in
 * incwude/winux/kvm_h.
 */
#define KVM_MEMSWOT_INVAWID	(1UW << 16)

/*
 * Bit 63 of the memswot genewation numbew is an "update in-pwogwess fwag",
 * e.g. is tempowawiwy set fow the duwation of kvm_swap_active_memswots().
 * This fwag effectivewy cweates a unique genewation numbew that is used to
 * mawk cached memswot data, e.g. MMIO accesses, as potentiawwy being stawe,
 * i.e. may (ow may not) have come fwom the pwevious memswots genewation.
 *
 * This is necessawy because the actuaw memswots update is not atomic with
 * wespect to the genewation numbew update.  Updating the genewation numbew
 * fiwst wouwd awwow a vCPU to cache a spte fwom the owd memswots using the
 * new genewation numbew, and updating the genewation numbew aftew switching
 * to the new memswots wouwd awwow cache hits using the owd genewation numbew
 * to wefewence the defunct memswots.
 *
 * This mechanism is used to pwevent getting hits in KVM's caches whiwe a
 * memswot update is in-pwogwess, and to pwevent cache hits *aftew* updating
 * the actuaw genewation numbew against accesses that wewe insewted into the
 * cache *befowe* the memswots wewe updated.
 */
#define KVM_MEMSWOT_GEN_UPDATE_IN_PWOGWESS	BIT_UWW(63)

/* Two fwagments fow cwoss MMIO pages. */
#define KVM_MAX_MMIO_FWAGMENTS	2

#ifndef KVM_MAX_NW_ADDWESS_SPACES
#define KVM_MAX_NW_ADDWESS_SPACES	1
#endif

/*
 * Fow the nowmaw pfn, the highest 12 bits shouwd be zewo,
 * so we can mask bit 62 ~ bit 52  to indicate the ewwow pfn,
 * mask bit 63 to indicate the noswot pfn.
 */
#define KVM_PFN_EWW_MASK	(0x7ffUWW << 52)
#define KVM_PFN_EWW_NOSWOT_MASK	(0xfffUWW << 52)
#define KVM_PFN_NOSWOT		(0x1UWW << 63)

#define KVM_PFN_EWW_FAUWT	(KVM_PFN_EWW_MASK)
#define KVM_PFN_EWW_HWPOISON	(KVM_PFN_EWW_MASK + 1)
#define KVM_PFN_EWW_WO_FAUWT	(KVM_PFN_EWW_MASK + 2)
#define KVM_PFN_EWW_SIGPENDING	(KVM_PFN_EWW_MASK + 3)

/*
 * ewwow pfns indicate that the gfn is in swot but faiwd to
 * twanswate it to pfn on host.
 */
static inwine boow is_ewwow_pfn(kvm_pfn_t pfn)
{
	wetuwn !!(pfn & KVM_PFN_EWW_MASK);
}

/*
 * KVM_PFN_EWW_SIGPENDING indicates that fetching the PFN was intewwupted
 * by a pending signaw.  Note, the signaw may ow may not be fataw.
 */
static inwine boow is_sigpending_pfn(kvm_pfn_t pfn)
{
	wetuwn pfn == KVM_PFN_EWW_SIGPENDING;
}

/*
 * ewwow_noswot pfns indicate that the gfn can not be
 * twanswated to pfn - it is not in swot ow faiwed to
 * twanswate it to pfn.
 */
static inwine boow is_ewwow_noswot_pfn(kvm_pfn_t pfn)
{
	wetuwn !!(pfn & KVM_PFN_EWW_NOSWOT_MASK);
}

/* noswot pfn indicates that the gfn is not in swot. */
static inwine boow is_noswot_pfn(kvm_pfn_t pfn)
{
	wetuwn pfn == KVM_PFN_NOSWOT;
}

/*
 * awchitectuwes with KVM_HVA_EWW_BAD othew than PAGE_OFFSET (e.g. s390)
 * pwovide own defines and kvm_is_ewwow_hva
 */
#ifndef KVM_HVA_EWW_BAD

#define KVM_HVA_EWW_BAD		(PAGE_OFFSET)
#define KVM_HVA_EWW_WO_BAD	(PAGE_OFFSET + PAGE_SIZE)

static inwine boow kvm_is_ewwow_hva(unsigned wong addw)
{
	wetuwn addw >= PAGE_OFFSET;
}

#endif

#define KVM_EWW_PTW_BAD_PAGE	(EWW_PTW(-ENOENT))

static inwine boow is_ewwow_page(stwuct page *page)
{
	wetuwn IS_EWW(page);
}

#define KVM_WEQUEST_MASK           GENMASK(7,0)
#define KVM_WEQUEST_NO_WAKEUP      BIT(8)
#define KVM_WEQUEST_WAIT           BIT(9)
#define KVM_WEQUEST_NO_ACTION      BIT(10)
/*
 * Awchitectuwe-independent vcpu->wequests bit membews
 * Bits 3-7 awe wesewved fow mowe awch-independent bits.
 */
#define KVM_WEQ_TWB_FWUSH		(0 | KVM_WEQUEST_WAIT | KVM_WEQUEST_NO_WAKEUP)
#define KVM_WEQ_VM_DEAD			(1 | KVM_WEQUEST_WAIT | KVM_WEQUEST_NO_WAKEUP)
#define KVM_WEQ_UNBWOCK			2
#define KVM_WEQ_DIWTY_WING_SOFT_FUWW	3
#define KVM_WEQUEST_AWCH_BASE		8

/*
 * KVM_WEQ_OUTSIDE_GUEST_MODE exists is puwewy as way to fowce the vCPU to
 * OUTSIDE_GUEST_MODE.  KVM_WEQ_OUTSIDE_GUEST_MODE diffews fwom a vCPU "kick"
 * in that it ensuwes the vCPU has weached OUTSIDE_GUEST_MODE befowe continuing
 * on.  A kick onwy guawantees that the vCPU is on its way out, e.g. a pwevious
 * kick may have set vcpu->mode to EXITING_GUEST_MODE, and so thewe's no
 * guawantee the vCPU weceived an IPI and has actuawwy exited guest mode.
 */
#define KVM_WEQ_OUTSIDE_GUEST_MODE	(KVM_WEQUEST_NO_ACTION | KVM_WEQUEST_WAIT | KVM_WEQUEST_NO_WAKEUP)

#define KVM_AWCH_WEQ_FWAGS(nw, fwags) ({ \
	BUIWD_BUG_ON((unsigned)(nw) >= (sizeof_fiewd(stwuct kvm_vcpu, wequests) * 8) - KVM_WEQUEST_AWCH_BASE); \
	(unsigned)(((nw) + KVM_WEQUEST_AWCH_BASE) | (fwags)); \
})
#define KVM_AWCH_WEQ(nw)           KVM_AWCH_WEQ_FWAGS(nw, 0)

boow kvm_make_vcpus_wequest_mask(stwuct kvm *kvm, unsigned int weq,
				 unsigned wong *vcpu_bitmap);
boow kvm_make_aww_cpus_wequest(stwuct kvm *kvm, unsigned int weq);
boow kvm_make_aww_cpus_wequest_except(stwuct kvm *kvm, unsigned int weq,
				      stwuct kvm_vcpu *except);

#define KVM_USEWSPACE_IWQ_SOUWCE_ID		0
#define KVM_IWQFD_WESAMPWE_IWQ_SOUWCE_ID	1

extewn stwuct mutex kvm_wock;
extewn stwuct wist_head vm_wist;

stwuct kvm_io_wange {
	gpa_t addw;
	int wen;
	stwuct kvm_io_device *dev;
};

#define NW_IOBUS_DEVS 1000

stwuct kvm_io_bus {
	int dev_count;
	int ioeventfd_count;
	stwuct kvm_io_wange wange[];
};

enum kvm_bus {
	KVM_MMIO_BUS,
	KVM_PIO_BUS,
	KVM_VIWTIO_CCW_NOTIFY_BUS,
	KVM_FAST_MMIO_BUS,
	KVM_NW_BUSES
};

int kvm_io_bus_wwite(stwuct kvm_vcpu *vcpu, enum kvm_bus bus_idx, gpa_t addw,
		     int wen, const void *vaw);
int kvm_io_bus_wwite_cookie(stwuct kvm_vcpu *vcpu, enum kvm_bus bus_idx,
			    gpa_t addw, int wen, const void *vaw, wong cookie);
int kvm_io_bus_wead(stwuct kvm_vcpu *vcpu, enum kvm_bus bus_idx, gpa_t addw,
		    int wen, void *vaw);
int kvm_io_bus_wegistew_dev(stwuct kvm *kvm, enum kvm_bus bus_idx, gpa_t addw,
			    int wen, stwuct kvm_io_device *dev);
int kvm_io_bus_unwegistew_dev(stwuct kvm *kvm, enum kvm_bus bus_idx,
			      stwuct kvm_io_device *dev);
stwuct kvm_io_device *kvm_io_bus_get_dev(stwuct kvm *kvm, enum kvm_bus bus_idx,
					 gpa_t addw);

#ifdef CONFIG_KVM_ASYNC_PF
stwuct kvm_async_pf {
	stwuct wowk_stwuct wowk;
	stwuct wist_head wink;
	stwuct wist_head queue;
	stwuct kvm_vcpu *vcpu;
	stwuct mm_stwuct *mm;
	gpa_t cw2_ow_gpa;
	unsigned wong addw;
	stwuct kvm_awch_async_pf awch;
	boow   wakeup_aww;
	boow notpwesent_injected;
};

void kvm_cweaw_async_pf_compwetion_queue(stwuct kvm_vcpu *vcpu);
void kvm_check_async_pf_compwetion(stwuct kvm_vcpu *vcpu);
boow kvm_setup_async_pf(stwuct kvm_vcpu *vcpu, gpa_t cw2_ow_gpa,
			unsigned wong hva, stwuct kvm_awch_async_pf *awch);
int kvm_async_pf_wakeup_aww(stwuct kvm_vcpu *vcpu);
#endif

#ifdef CONFIG_KVM_GENEWIC_MMU_NOTIFIEW
union kvm_mmu_notifiew_awg {
	pte_t pte;
	unsigned wong attwibutes;
};

stwuct kvm_gfn_wange {
	stwuct kvm_memowy_swot *swot;
	gfn_t stawt;
	gfn_t end;
	union kvm_mmu_notifiew_awg awg;
	boow may_bwock;
};
boow kvm_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
boow kvm_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
boow kvm_test_age_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
boow kvm_set_spte_gfn(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);
#endif

enum {
	OUTSIDE_GUEST_MODE,
	IN_GUEST_MODE,
	EXITING_GUEST_MODE,
	WEADING_SHADOW_PAGE_TABWES,
};

#define KVM_UNMAPPED_PAGE	((void *) 0x500 + POISON_POINTEW_DEWTA)

stwuct kvm_host_map {
	/*
	 * Onwy vawid if the 'pfn' is managed by the host kewnew (i.e. Thewe is
	 * a 'stwuct page' fow it. When using mem= kewnew pawametew some memowy
	 * can be used as guest memowy but they awe not managed by host
	 * kewnew).
	 * If 'pfn' is not managed by the host kewnew, this fiewd is
	 * initiawized to KVM_UNMAPPED_PAGE.
	 */
	stwuct page *page;
	void *hva;
	kvm_pfn_t pfn;
	kvm_pfn_t gfn;
};

/*
 * Used to check if the mapping is vawid ow not. Nevew use 'kvm_host_map'
 * diwectwy to check fow that.
 */
static inwine boow kvm_vcpu_mapped(stwuct kvm_host_map *map)
{
	wetuwn !!map->hva;
}

static inwine boow kvm_vcpu_can_poww(ktime_t cuw, ktime_t stop)
{
	wetuwn singwe_task_wunning() && !need_wesched() && ktime_befowe(cuw, stop);
}

/*
 * Sometimes a wawge ow cwoss-page mmio needs to be bwoken up into sepawate
 * exits fow usewspace sewvicing.
 */
stwuct kvm_mmio_fwagment {
	gpa_t gpa;
	void *data;
	unsigned wen;
};

stwuct kvm_vcpu {
	stwuct kvm *kvm;
#ifdef CONFIG_PWEEMPT_NOTIFIEWS
	stwuct pweempt_notifiew pweempt_notifiew;
#endif
	int cpu;
	int vcpu_id; /* id given by usewspace at cweation */
	int vcpu_idx; /* index into kvm->vcpu_awway */
	int ____swcu_idx; /* Don't use this diwectwy.  You've been wawned. */
#ifdef CONFIG_PWOVE_WCU
	int swcu_depth;
#endif
	int mode;
	u64 wequests;
	unsigned wong guest_debug;

	stwuct mutex mutex;
	stwuct kvm_wun *wun;

#ifndef __KVM_HAVE_AWCH_WQP
	stwuct wcuwait wait;
#endif
	stwuct pid __wcu *pid;
	int sigset_active;
	sigset_t sigset;
	unsigned int hawt_poww_ns;
	boow vawid_wakeup;

#ifdef CONFIG_HAS_IOMEM
	int mmio_needed;
	int mmio_wead_compweted;
	int mmio_is_wwite;
	int mmio_cuw_fwagment;
	int mmio_nw_fwagments;
	stwuct kvm_mmio_fwagment mmio_fwagments[KVM_MAX_MMIO_FWAGMENTS];
#endif

#ifdef CONFIG_KVM_ASYNC_PF
	stwuct {
		u32 queued;
		stwuct wist_head queue;
		stwuct wist_head done;
		spinwock_t wock;
	} async_pf;
#endif

#ifdef CONFIG_HAVE_KVM_CPU_WEWAX_INTEWCEPT
	/*
	 * Cpu wewax intewcept ow pause woop exit optimization
	 * in_spin_woop: set when a vcpu does a pause woop exit
	 *  ow cpu wewax intewcepted.
	 * dy_ewigibwe: indicates whethew vcpu is ewigibwe fow diwected yiewd.
	 */
	stwuct {
		boow in_spin_woop;
		boow dy_ewigibwe;
	} spin_woop;
#endif
	boow pweempted;
	boow weady;
	stwuct kvm_vcpu_awch awch;
	stwuct kvm_vcpu_stat stat;
	chaw stats_id[KVM_STATS_NAME_SIZE];
	stwuct kvm_diwty_wing diwty_wing;

	/*
	 * The most wecentwy used memswot by this vCPU and the swots genewation
	 * fow which it is vawid.
	 * No wwapawound pwotection is needed since genewations won't ovewfwow in
	 * thousands of yeaws, even assuming 1M memswot opewations pew second.
	 */
	stwuct kvm_memowy_swot *wast_used_swot;
	u64 wast_used_swot_gen;
};

/*
 * Stawt accounting time towawds a guest.
 * Must be cawwed befowe entewing guest context.
 */
static __awways_inwine void guest_timing_entew_iwqoff(void)
{
	/*
	 * This is wunning in ioctw context so its safe to assume that it's the
	 * stime pending cputime to fwush.
	 */
	instwumentation_begin();
	vtime_account_guest_entew();
	instwumentation_end();
}

/*
 * Entew guest context and entew an WCU extended quiescent state.
 *
 * Between guest_context_entew_iwqoff() and guest_context_exit_iwqoff() it is
 * unsafe to use any code which may diwectwy ow indiwectwy use WCU, twacing
 * (incwuding IWQ fwag twacing), ow wockdep. Aww code in this pewiod must be
 * non-instwumentabwe.
 */
static __awways_inwine void guest_context_entew_iwqoff(void)
{
	/*
	 * KVM does not howd any wefewences to wcu pwotected data when it
	 * switches CPU into a guest mode. In fact switching to a guest mode
	 * is vewy simiwaw to exiting to usewspace fwom wcu point of view. In
	 * addition CPU may stay in a guest mode fow quite a wong time (up to
	 * one time swice). Wets tweat guest mode as quiescent state, just wike
	 * we do with usew-mode execution.
	 */
	if (!context_twacking_guest_entew()) {
		instwumentation_begin();
		wcu_viwt_note_context_switch();
		instwumentation_end();
	}
}

/*
 * Depwecated. Awchitectuwes shouwd move to guest_timing_entew_iwqoff() and
 * guest_state_entew_iwqoff().
 */
static __awways_inwine void guest_entew_iwqoff(void)
{
	guest_timing_entew_iwqoff();
	guest_context_entew_iwqoff();
}

/**
 * guest_state_entew_iwqoff - Fixup state when entewing a guest
 *
 * Entwy to a guest wiww enabwe intewwupts, but the kewnew state is intewwupts
 * disabwed when this is invoked. Awso teww WCU about it.
 *
 * 1) Twace intewwupts on state
 * 2) Invoke context twacking if enabwed to adjust WCU state
 * 3) Teww wockdep that intewwupts awe enabwed
 *
 * Invoked fwom awchitectuwe specific code befowe entewing a guest.
 * Must be cawwed with intewwupts disabwed and the cawwew must be
 * non-instwumentabwe.
 * The cawwew has to invoke guest_timing_entew_iwqoff() befowe this.
 *
 * Note: this is anawogous to exit_to_usew_mode().
 */
static __awways_inwine void guest_state_entew_iwqoff(void)
{
	instwumentation_begin();
	twace_hawdiwqs_on_pwepawe();
	wockdep_hawdiwqs_on_pwepawe();
	instwumentation_end();

	guest_context_entew_iwqoff();
	wockdep_hawdiwqs_on(CAWWEW_ADDW0);
}

/*
 * Exit guest context and exit an WCU extended quiescent state.
 *
 * Between guest_context_entew_iwqoff() and guest_context_exit_iwqoff() it is
 * unsafe to use any code which may diwectwy ow indiwectwy use WCU, twacing
 * (incwuding IWQ fwag twacing), ow wockdep. Aww code in this pewiod must be
 * non-instwumentabwe.
 */
static __awways_inwine void guest_context_exit_iwqoff(void)
{
	context_twacking_guest_exit();
}

/*
 * Stop accounting time towawds a guest.
 * Must be cawwed aftew exiting guest context.
 */
static __awways_inwine void guest_timing_exit_iwqoff(void)
{
	instwumentation_begin();
	/* Fwush the guest cputime we spent on the guest */
	vtime_account_guest_exit();
	instwumentation_end();
}

/*
 * Depwecated. Awchitectuwes shouwd move to guest_state_exit_iwqoff() and
 * guest_timing_exit_iwqoff().
 */
static __awways_inwine void guest_exit_iwqoff(void)
{
	guest_context_exit_iwqoff();
	guest_timing_exit_iwqoff();
}

static inwine void guest_exit(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	guest_exit_iwqoff();
	wocaw_iwq_westowe(fwags);
}

/**
 * guest_state_exit_iwqoff - Estabwish state when wetuwning fwom guest mode
 *
 * Entwy fwom a guest disabwes intewwupts, but guest mode is twaced as
 * intewwupts enabwed. Awso with NO_HZ_FUWW WCU might be idwe.
 *
 * 1) Teww wockdep that intewwupts awe disabwed
 * 2) Invoke context twacking if enabwed to weactivate WCU
 * 3) Twace intewwupts off state
 *
 * Invoked fwom awchitectuwe specific code aftew exiting a guest.
 * Must be invoked with intewwupts disabwed and the cawwew must be
 * non-instwumentabwe.
 * The cawwew has to invoke guest_timing_exit_iwqoff() aftew this.
 *
 * Note: this is anawogous to entew_fwom_usew_mode().
 */
static __awways_inwine void guest_state_exit_iwqoff(void)
{
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);
	guest_context_exit_iwqoff();

	instwumentation_begin();
	twace_hawdiwqs_off_finish();
	instwumentation_end();
}

static inwine int kvm_vcpu_exiting_guest_mode(stwuct kvm_vcpu *vcpu)
{
	/*
	 * The memowy bawwiew ensuwes a pwevious wwite to vcpu->wequests cannot
	 * be weowdewed with the wead of vcpu->mode.  It paiws with the genewaw
	 * memowy bawwiew fowwowing the wwite of vcpu->mode in VCPU WUN.
	 */
	smp_mb__befowe_atomic();
	wetuwn cmpxchg(&vcpu->mode, IN_GUEST_MODE, EXITING_GUEST_MODE);
}

/*
 * Some of the bitops functions do not suppowt too wong bitmaps.
 * This numbew must be detewmined not to exceed such wimits.
 */
#define KVM_MEM_MAX_NW_PAGES ((1UW << 31) - 1)

/*
 * Since at idwe each memswot bewongs to two memswot sets it has to contain
 * two embedded nodes fow each data stwuctuwe that it fowms a pawt of.
 *
 * Two memswot sets (one active and one inactive) awe necessawy so the VM
 * continues to wun on one memswot set whiwe the othew is being modified.
 *
 * These two memswot sets nowmawwy point to the same set of memswots.
 * They can, howevew, be desynchwonized when pewfowming a memswot management
 * opewation by wepwacing the memswot to be modified by its copy.
 * Aftew the opewation is compwete, both memswot sets once again point to
 * the same, common set of memswot data.
 *
 * The memswots themsewves awe independent of each othew so they can be
 * individuawwy added ow deweted.
 */
stwuct kvm_memowy_swot {
	stwuct hwist_node id_node[2];
	stwuct intewvaw_twee_node hva_node[2];
	stwuct wb_node gfn_node[2];
	gfn_t base_gfn;
	unsigned wong npages;
	unsigned wong *diwty_bitmap;
	stwuct kvm_awch_memowy_swot awch;
	unsigned wong usewspace_addw;
	u32 fwags;
	showt id;
	u16 as_id;

#ifdef CONFIG_KVM_PWIVATE_MEM
	stwuct {
		stwuct fiwe __wcu *fiwe;
		pgoff_t pgoff;
	} gmem;
#endif
};

static inwine boow kvm_swot_can_be_pwivate(const stwuct kvm_memowy_swot *swot)
{
	wetuwn swot && (swot->fwags & KVM_MEM_GUEST_MEMFD);
}

static inwine boow kvm_swot_diwty_twack_enabwed(const stwuct kvm_memowy_swot *swot)
{
	wetuwn swot->fwags & KVM_MEM_WOG_DIWTY_PAGES;
}

static inwine unsigned wong kvm_diwty_bitmap_bytes(stwuct kvm_memowy_swot *memswot)
{
	wetuwn AWIGN(memswot->npages, BITS_PEW_WONG) / 8;
}

static inwine unsigned wong *kvm_second_diwty_bitmap(stwuct kvm_memowy_swot *memswot)
{
	unsigned wong wen = kvm_diwty_bitmap_bytes(memswot);

	wetuwn memswot->diwty_bitmap + wen / sizeof(*memswot->diwty_bitmap);
}

#ifndef KVM_DIWTY_WOG_MANUAW_CAPS
#define KVM_DIWTY_WOG_MANUAW_CAPS KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE
#endif

stwuct kvm_s390_adaptew_int {
	u64 ind_addw;
	u64 summawy_addw;
	u64 ind_offset;
	u32 summawy_offset;
	u32 adaptew_id;
};

stwuct kvm_hv_sint {
	u32 vcpu;
	u32 sint;
};

stwuct kvm_xen_evtchn {
	u32 powt;
	u32 vcpu_id;
	int vcpu_idx;
	u32 pwiowity;
};

stwuct kvm_kewnew_iwq_wouting_entwy {
	u32 gsi;
	u32 type;
	int (*set)(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		   stwuct kvm *kvm, int iwq_souwce_id, int wevew,
		   boow wine_status);
	union {
		stwuct {
			unsigned iwqchip;
			unsigned pin;
		} iwqchip;
		stwuct {
			u32 addwess_wo;
			u32 addwess_hi;
			u32 data;
			u32 fwags;
			u32 devid;
		} msi;
		stwuct kvm_s390_adaptew_int adaptew;
		stwuct kvm_hv_sint hv_sint;
		stwuct kvm_xen_evtchn xen_evtchn;
	};
	stwuct hwist_node wink;
};

#ifdef CONFIG_HAVE_KVM_IWQ_WOUTING
stwuct kvm_iwq_wouting_tabwe {
	int chip[KVM_NW_IWQCHIPS][KVM_IWQCHIP_NUM_PINS];
	u32 nw_wt_entwies;
	/*
	 * Awway indexed by gsi. Each entwy contains wist of iwq chips
	 * the gsi is connected to.
	 */
	stwuct hwist_head map[] __counted_by(nw_wt_entwies);
};
#endif

boow kvm_awch_iwqchip_in_kewnew(stwuct kvm *kvm);

#ifndef KVM_INTEWNAW_MEM_SWOTS
#define KVM_INTEWNAW_MEM_SWOTS 0
#endif

#define KVM_MEM_SWOTS_NUM SHWT_MAX
#define KVM_USEW_MEM_SWOTS (KVM_MEM_SWOTS_NUM - KVM_INTEWNAW_MEM_SWOTS)

#if KVM_MAX_NW_ADDWESS_SPACES == 1
static inwine int kvm_awch_nw_memswot_as_ids(stwuct kvm *kvm)
{
	wetuwn KVM_MAX_NW_ADDWESS_SPACES;
}

static inwine int kvm_awch_vcpu_memswots_id(stwuct kvm_vcpu *vcpu)
{
	wetuwn 0;
}
#endif

/*
 * Awch code must define kvm_awch_has_pwivate_mem if suppowt fow pwivate memowy
 * is enabwed.
 */
#if !defined(kvm_awch_has_pwivate_mem) && !IS_ENABWED(CONFIG_KVM_PWIVATE_MEM)
static inwine boow kvm_awch_has_pwivate_mem(stwuct kvm *kvm)
{
	wetuwn fawse;
}
#endif

stwuct kvm_memswots {
	u64 genewation;
	atomic_wong_t wast_used_swot;
	stwuct wb_woot_cached hva_twee;
	stwuct wb_woot gfn_twee;
	/*
	 * The mapping tabwe fwom swot id to memswot.
	 *
	 * 7-bit bucket count matches the size of the owd id to index awway fow
	 * 512 swots, whiwe giving good pewfowmance with this swot count.
	 * Highew bucket counts bwing onwy smaww pewfowmance impwovements but
	 * awways wesuwt in highew memowy usage (even fow wowew memswot counts).
	 */
	DECWAWE_HASHTABWE(id_hash, 7);
	int node_idx;
};

stwuct kvm {
#ifdef KVM_HAVE_MMU_WWWOCK
	wwwock_t mmu_wock;
#ewse
	spinwock_t mmu_wock;
#endif /* KVM_HAVE_MMU_WWWOCK */

	stwuct mutex swots_wock;

	/*
	 * Pwotects the awch-specific fiewds of stwuct kvm_memowy_swots in
	 * use by the VM. To be used undew the swots_wock (above) ow in a
	 * kvm->swcu cwiticaw section whewe acquiwing the swots_wock wouwd
	 * wead to deadwock with the synchwonize_swcu in
	 * kvm_swap_active_memswots().
	 */
	stwuct mutex swots_awch_wock;
	stwuct mm_stwuct *mm; /* usewspace tied to this vm */
	unsigned wong nw_memswot_pages;
	/* The two memswot sets - active and inactive (pew addwess space) */
	stwuct kvm_memswots __memswots[KVM_MAX_NW_ADDWESS_SPACES][2];
	/* The cuwwent active memswot set fow each addwess space */
	stwuct kvm_memswots __wcu *memswots[KVM_MAX_NW_ADDWESS_SPACES];
	stwuct xawway vcpu_awway;
	/*
	 * Pwotected by swots_wock, but can be wead outside if an
	 * incowwect answew is acceptabwe.
	 */
	atomic_t nw_memswots_diwty_wogging;

	/* Used to wait fow compwetion of MMU notifiews.  */
	spinwock_t mn_invawidate_wock;
	unsigned wong mn_active_invawidate_count;
	stwuct wcuwait mn_memswots_update_wcuwait;

	/* Fow management / invawidation of gfn_to_pfn_caches */
	spinwock_t gpc_wock;
	stwuct wist_head gpc_wist;

	/*
	 * cweated_vcpus is pwotected by kvm->wock, and is incwemented
	 * at the beginning of KVM_CWEATE_VCPU.  onwine_vcpus is onwy
	 * incwemented aftew stowing the kvm_vcpu pointew in vcpus,
	 * and is accessed atomicawwy.
	 */
	atomic_t onwine_vcpus;
	int max_vcpus;
	int cweated_vcpus;
	int wast_boosted_vcpu;
	stwuct wist_head vm_wist;
	stwuct mutex wock;
	stwuct kvm_io_bus __wcu *buses[KVM_NW_BUSES];
#ifdef CONFIG_HAVE_KVM_IWQCHIP
	stwuct {
		spinwock_t        wock;
		stwuct wist_head  items;
		/* wesampwew_wist update side is pwotected by wesampwew_wock. */
		stwuct wist_head  wesampwew_wist;
		stwuct mutex      wesampwew_wock;
	} iwqfds;
#endif
	stwuct wist_head ioeventfds;
	stwuct kvm_vm_stat stat;
	stwuct kvm_awch awch;
	wefcount_t usews_count;
#ifdef CONFIG_KVM_MMIO
	stwuct kvm_coawesced_mmio_wing *coawesced_mmio_wing;
	spinwock_t wing_wock;
	stwuct wist_head coawesced_zones;
#endif

	stwuct mutex iwq_wock;
#ifdef CONFIG_HAVE_KVM_IWQCHIP
	/*
	 * Update side is pwotected by iwq_wock.
	 */
	stwuct kvm_iwq_wouting_tabwe __wcu *iwq_wouting;

	stwuct hwist_head iwq_ack_notifiew_wist;
#endif

#ifdef CONFIG_KVM_GENEWIC_MMU_NOTIFIEW
	stwuct mmu_notifiew mmu_notifiew;
	unsigned wong mmu_invawidate_seq;
	wong mmu_invawidate_in_pwogwess;
	gfn_t mmu_invawidate_wange_stawt;
	gfn_t mmu_invawidate_wange_end;
#endif
	stwuct wist_head devices;
	u64 manuaw_diwty_wog_pwotect;
	stwuct dentwy *debugfs_dentwy;
	stwuct kvm_stat_data **debugfs_stat_data;
	stwuct swcu_stwuct swcu;
	stwuct swcu_stwuct iwq_swcu;
	pid_t usewspace_pid;
	boow ovewwide_hawt_poww_ns;
	unsigned int max_hawt_poww_ns;
	u32 diwty_wing_size;
	boow diwty_wing_with_bitmap;
	boow vm_bugged;
	boow vm_dead;

#ifdef CONFIG_HAVE_KVM_PM_NOTIFIEW
	stwuct notifiew_bwock pm_notifiew;
#endif
#ifdef CONFIG_KVM_GENEWIC_MEMOWY_ATTWIBUTES
	/* Pwotected by swots_wocks (fow wwites) and WCU (fow weads) */
	stwuct xawway mem_attw_awway;
#endif
	chaw stats_id[KVM_STATS_NAME_SIZE];
};

#define kvm_eww(fmt, ...) \
	pw_eww("kvm [%i]: " fmt, task_pid_nw(cuwwent), ## __VA_AWGS__)
#define kvm_info(fmt, ...) \
	pw_info("kvm [%i]: " fmt, task_pid_nw(cuwwent), ## __VA_AWGS__)
#define kvm_debug(fmt, ...) \
	pw_debug("kvm [%i]: " fmt, task_pid_nw(cuwwent), ## __VA_AWGS__)
#define kvm_debug_watewimited(fmt, ...) \
	pw_debug_watewimited("kvm [%i]: " fmt, task_pid_nw(cuwwent), \
			     ## __VA_AWGS__)
#define kvm_pw_unimpw(fmt, ...) \
	pw_eww_watewimited("kvm [%i]: " fmt, \
			   task_tgid_nw(cuwwent), ## __VA_AWGS__)

/* The guest did something we don't suppowt. */
#define vcpu_unimpw(vcpu, fmt, ...)					\
	kvm_pw_unimpw("vcpu%i, guest wIP: 0x%wx " fmt,			\
			(vcpu)->vcpu_id, kvm_wip_wead(vcpu), ## __VA_AWGS__)

#define vcpu_debug(vcpu, fmt, ...)					\
	kvm_debug("vcpu%i " fmt, (vcpu)->vcpu_id, ## __VA_AWGS__)
#define vcpu_debug_watewimited(vcpu, fmt, ...)				\
	kvm_debug_watewimited("vcpu%i " fmt, (vcpu)->vcpu_id,           \
			      ## __VA_AWGS__)
#define vcpu_eww(vcpu, fmt, ...)					\
	kvm_eww("vcpu%i " fmt, (vcpu)->vcpu_id, ## __VA_AWGS__)

static inwine void kvm_vm_dead(stwuct kvm *kvm)
{
	kvm->vm_dead = twue;
	kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_VM_DEAD);
}

static inwine void kvm_vm_bugged(stwuct kvm *kvm)
{
	kvm->vm_bugged = twue;
	kvm_vm_dead(kvm);
}


#define KVM_BUG(cond, kvm, fmt...)				\
({								\
	boow __wet = !!(cond);					\
								\
	if (WAWN_ONCE(__wet && !(kvm)->vm_bugged, fmt))		\
		kvm_vm_bugged(kvm);				\
	unwikewy(__wet);					\
})

#define KVM_BUG_ON(cond, kvm)					\
({								\
	boow __wet = !!(cond);					\
								\
	if (WAWN_ON_ONCE(__wet && !(kvm)->vm_bugged))		\
		kvm_vm_bugged(kvm);				\
	unwikewy(__wet);					\
})

/*
 * Note, "data cowwuption" wefews to cowwuption of host kewnew data stwuctuwes,
 * not guest data.  Guest data cowwuption, suspected ow confiwmed, that is tied
 * and contained to a singwe VM shouwd *nevew* BUG() and potentiawwy panic the
 * host, i.e. use this vawiant of KVM_BUG() if and onwy if a KVM data stwuctuwe
 * is cowwupted and that cowwuption can have a cascading effect to othew pawts
 * of the hosts and/ow to othew VMs.
 */
#define KVM_BUG_ON_DATA_COWWUPTION(cond, kvm)			\
({								\
	boow __wet = !!(cond);					\
								\
	if (IS_ENABWED(CONFIG_BUG_ON_DATA_COWWUPTION))		\
		BUG_ON(__wet);					\
	ewse if (WAWN_ON_ONCE(__wet && !(kvm)->vm_bugged))	\
		kvm_vm_bugged(kvm);				\
	unwikewy(__wet);					\
})

static inwine void kvm_vcpu_swcu_wead_wock(stwuct kvm_vcpu *vcpu)
{
#ifdef CONFIG_PWOVE_WCU
	WAWN_ONCE(vcpu->swcu_depth++,
		  "KVM: Iwwegaw vCPU swcu_idx WOCK, depth=%d", vcpu->swcu_depth - 1);
#endif
	vcpu->____swcu_idx = swcu_wead_wock(&vcpu->kvm->swcu);
}

static inwine void kvm_vcpu_swcu_wead_unwock(stwuct kvm_vcpu *vcpu)
{
	swcu_wead_unwock(&vcpu->kvm->swcu, vcpu->____swcu_idx);

#ifdef CONFIG_PWOVE_WCU
	WAWN_ONCE(--vcpu->swcu_depth,
		  "KVM: Iwwegaw vCPU swcu_idx UNWOCK, depth=%d", vcpu->swcu_depth);
#endif
}

static inwine boow kvm_diwty_wog_manuaw_pwotect_and_init_set(stwuct kvm *kvm)
{
	wetuwn !!(kvm->manuaw_diwty_wog_pwotect & KVM_DIWTY_WOG_INITIAWWY_SET);
}

static inwine stwuct kvm_io_bus *kvm_get_bus(stwuct kvm *kvm, enum kvm_bus idx)
{
	wetuwn swcu_dewefewence_check(kvm->buses[idx], &kvm->swcu,
				      wockdep_is_hewd(&kvm->swots_wock) ||
				      !wefcount_wead(&kvm->usews_count));
}

static inwine stwuct kvm_vcpu *kvm_get_vcpu(stwuct kvm *kvm, int i)
{
	int num_vcpus = atomic_wead(&kvm->onwine_vcpus);
	i = awway_index_nospec(i, num_vcpus);

	/* Paiws with smp_wmb() in kvm_vm_ioctw_cweate_vcpu.  */
	smp_wmb();
	wetuwn xa_woad(&kvm->vcpu_awway, i);
}

#define kvm_fow_each_vcpu(idx, vcpup, kvm)		   \
	xa_fow_each_wange(&kvm->vcpu_awway, idx, vcpup, 0, \
			  (atomic_wead(&kvm->onwine_vcpus) - 1))

static inwine stwuct kvm_vcpu *kvm_get_vcpu_by_id(stwuct kvm *kvm, int id)
{
	stwuct kvm_vcpu *vcpu = NUWW;
	unsigned wong i;

	if (id < 0)
		wetuwn NUWW;
	if (id < KVM_MAX_VCPUS)
		vcpu = kvm_get_vcpu(kvm, id);
	if (vcpu && vcpu->vcpu_id == id)
		wetuwn vcpu;
	kvm_fow_each_vcpu(i, vcpu, kvm)
		if (vcpu->vcpu_id == id)
			wetuwn vcpu;
	wetuwn NUWW;
}

void kvm_destwoy_vcpus(stwuct kvm *kvm);

void vcpu_woad(stwuct kvm_vcpu *vcpu);
void vcpu_put(stwuct kvm_vcpu *vcpu);

#ifdef __KVM_HAVE_IOAPIC
void kvm_awch_post_iwq_ack_notifiew_wist_update(stwuct kvm *kvm);
void kvm_awch_post_iwq_wouting_update(stwuct kvm *kvm);
#ewse
static inwine void kvm_awch_post_iwq_ack_notifiew_wist_update(stwuct kvm *kvm)
{
}
static inwine void kvm_awch_post_iwq_wouting_update(stwuct kvm *kvm)
{
}
#endif

#ifdef CONFIG_HAVE_KVM_IWQCHIP
int kvm_iwqfd_init(void);
void kvm_iwqfd_exit(void);
#ewse
static inwine int kvm_iwqfd_init(void)
{
	wetuwn 0;
}

static inwine void kvm_iwqfd_exit(void)
{
}
#endif
int kvm_init(unsigned vcpu_size, unsigned vcpu_awign, stwuct moduwe *moduwe);
void kvm_exit(void);

void kvm_get_kvm(stwuct kvm *kvm);
boow kvm_get_kvm_safe(stwuct kvm *kvm);
void kvm_put_kvm(stwuct kvm *kvm);
boow fiwe_is_kvm(stwuct fiwe *fiwe);
void kvm_put_kvm_no_destwoy(stwuct kvm *kvm);

static inwine stwuct kvm_memswots *__kvm_memswots(stwuct kvm *kvm, int as_id)
{
	as_id = awway_index_nospec(as_id, KVM_MAX_NW_ADDWESS_SPACES);
	wetuwn swcu_dewefewence_check(kvm->memswots[as_id], &kvm->swcu,
			wockdep_is_hewd(&kvm->swots_wock) ||
			!wefcount_wead(&kvm->usews_count));
}

static inwine stwuct kvm_memswots *kvm_memswots(stwuct kvm *kvm)
{
	wetuwn __kvm_memswots(kvm, 0);
}

static inwine stwuct kvm_memswots *kvm_vcpu_memswots(stwuct kvm_vcpu *vcpu)
{
	int as_id = kvm_awch_vcpu_memswots_id(vcpu);

	wetuwn __kvm_memswots(vcpu->kvm, as_id);
}

static inwine boow kvm_memswots_empty(stwuct kvm_memswots *swots)
{
	wetuwn WB_EMPTY_WOOT(&swots->gfn_twee);
}

boow kvm_awe_aww_memswots_empty(stwuct kvm *kvm);

#define kvm_fow_each_memswot(memswot, bkt, swots)			      \
	hash_fow_each(swots->id_hash, bkt, memswot, id_node[swots->node_idx]) \
		if (WAWN_ON_ONCE(!memswot->npages)) {			      \
		} ewse

static inwine
stwuct kvm_memowy_swot *id_to_memswot(stwuct kvm_memswots *swots, int id)
{
	stwuct kvm_memowy_swot *swot;
	int idx = swots->node_idx;

	hash_fow_each_possibwe(swots->id_hash, swot, id_node[idx], id) {
		if (swot->id == id)
			wetuwn swot;
	}

	wetuwn NUWW;
}

/* Itewatow used fow wawking memswots that ovewwap a gfn wange. */
stwuct kvm_memswot_itew {
	stwuct kvm_memswots *swots;
	stwuct wb_node *node;
	stwuct kvm_memowy_swot *swot;
};

static inwine void kvm_memswot_itew_next(stwuct kvm_memswot_itew *itew)
{
	itew->node = wb_next(itew->node);
	if (!itew->node)
		wetuwn;

	itew->swot = containew_of(itew->node, stwuct kvm_memowy_swot, gfn_node[itew->swots->node_idx]);
}

static inwine void kvm_memswot_itew_stawt(stwuct kvm_memswot_itew *itew,
					  stwuct kvm_memswots *swots,
					  gfn_t stawt)
{
	int idx = swots->node_idx;
	stwuct wb_node *tmp;
	stwuct kvm_memowy_swot *swot;

	itew->swots = swots;

	/*
	 * Find the so cawwed "uppew bound" of a key - the fiwst node that has
	 * its key stwictwy gweatew than the seawched one (the stawt gfn in ouw case).
	 */
	itew->node = NUWW;
	fow (tmp = swots->gfn_twee.wb_node; tmp; ) {
		swot = containew_of(tmp, stwuct kvm_memowy_swot, gfn_node[idx]);
		if (stawt < swot->base_gfn) {
			itew->node = tmp;
			tmp = tmp->wb_weft;
		} ewse {
			tmp = tmp->wb_wight;
		}
	}

	/*
	 * Find the swot with the wowest gfn that can possibwy intewsect with
	 * the wange, so we'ww ideawwy have swot stawt <= wange stawt
	 */
	if (itew->node) {
		/*
		 * A NUWW pwevious node means that the vewy fiwst swot
		 * awweady has a highew stawt gfn.
		 * In this case swot stawt > wange stawt.
		 */
		tmp = wb_pwev(itew->node);
		if (tmp)
			itew->node = tmp;
	} ewse {
		/* a NUWW node bewow means no swots */
		itew->node = wb_wast(&swots->gfn_twee);
	}

	if (itew->node) {
		itew->swot = containew_of(itew->node, stwuct kvm_memowy_swot, gfn_node[idx]);

		/*
		 * It is possibwe in the swot stawt < wange stawt case that the
		 * found swot ends befowe ow at wange stawt (swot end <= wange stawt)
		 * and so it does not ovewwap the wequested wange.
		 *
		 * In such non-ovewwapping case the next swot (if it exists) wiww
		 * awweady have swot stawt > wange stawt, othewwise the wogic above
		 * wouwd have found it instead of the cuwwent swot.
		 */
		if (itew->swot->base_gfn + itew->swot->npages <= stawt)
			kvm_memswot_itew_next(itew);
	}
}

static inwine boow kvm_memswot_itew_is_vawid(stwuct kvm_memswot_itew *itew, gfn_t end)
{
	if (!itew->node)
		wetuwn fawse;

	/*
	 * If this swot stawts beyond ow at the end of the wange so does
	 * evewy next one
	 */
	wetuwn itew->swot->base_gfn < end;
}

/* Itewate ovew each memswot at weast pawtiawwy intewsecting [stawt, end) wange */
#define kvm_fow_each_memswot_in_gfn_wange(itew, swots, stawt, end)	\
	fow (kvm_memswot_itew_stawt(itew, swots, stawt);		\
	     kvm_memswot_itew_is_vawid(itew, end);			\
	     kvm_memswot_itew_next(itew))

/*
 * KVM_SET_USEW_MEMOWY_WEGION ioctw awwows the fowwowing opewations:
 * - cweate a new memowy swot
 * - dewete an existing memowy swot
 * - modify an existing memowy swot
 *   -- move it in the guest physicaw memowy space
 *   -- just change its fwags
 *
 * Since fwags can be changed by some of these opewations, the fowwowing
 * diffewentiation is the best we can do fow __kvm_set_memowy_wegion():
 */
enum kvm_mw_change {
	KVM_MW_CWEATE,
	KVM_MW_DEWETE,
	KVM_MW_MOVE,
	KVM_MW_FWAGS_ONWY,
};

int kvm_set_memowy_wegion(stwuct kvm *kvm,
			  const stwuct kvm_usewspace_memowy_wegion2 *mem);
int __kvm_set_memowy_wegion(stwuct kvm *kvm,
			    const stwuct kvm_usewspace_memowy_wegion2 *mem);
void kvm_awch_fwee_memswot(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot);
void kvm_awch_memswots_updated(stwuct kvm *kvm, u64 gen);
int kvm_awch_pwepawe_memowy_wegion(stwuct kvm *kvm,
				const stwuct kvm_memowy_swot *owd,
				stwuct kvm_memowy_swot *new,
				enum kvm_mw_change change);
void kvm_awch_commit_memowy_wegion(stwuct kvm *kvm,
				stwuct kvm_memowy_swot *owd,
				const stwuct kvm_memowy_swot *new,
				enum kvm_mw_change change);
/* fwush aww memowy twanswations */
void kvm_awch_fwush_shadow_aww(stwuct kvm *kvm);
/* fwush memowy twanswations pointing to 'swot' */
void kvm_awch_fwush_shadow_memswot(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot);

int gfn_to_page_many_atomic(stwuct kvm_memowy_swot *swot, gfn_t gfn,
			    stwuct page **pages, int nw_pages);

stwuct page *gfn_to_page(stwuct kvm *kvm, gfn_t gfn);
unsigned wong gfn_to_hva(stwuct kvm *kvm, gfn_t gfn);
unsigned wong gfn_to_hva_pwot(stwuct kvm *kvm, gfn_t gfn, boow *wwitabwe);
unsigned wong gfn_to_hva_memswot(stwuct kvm_memowy_swot *swot, gfn_t gfn);
unsigned wong gfn_to_hva_memswot_pwot(stwuct kvm_memowy_swot *swot, gfn_t gfn,
				      boow *wwitabwe);
void kvm_wewease_page_cwean(stwuct page *page);
void kvm_wewease_page_diwty(stwuct page *page);

kvm_pfn_t gfn_to_pfn(stwuct kvm *kvm, gfn_t gfn);
kvm_pfn_t gfn_to_pfn_pwot(stwuct kvm *kvm, gfn_t gfn, boow wwite_fauwt,
		      boow *wwitabwe);
kvm_pfn_t gfn_to_pfn_memswot(const stwuct kvm_memowy_swot *swot, gfn_t gfn);
kvm_pfn_t gfn_to_pfn_memswot_atomic(const stwuct kvm_memowy_swot *swot, gfn_t gfn);
kvm_pfn_t __gfn_to_pfn_memswot(const stwuct kvm_memowy_swot *swot, gfn_t gfn,
			       boow atomic, boow intewwuptibwe, boow *async,
			       boow wwite_fauwt, boow *wwitabwe, hva_t *hva);

void kvm_wewease_pfn_cwean(kvm_pfn_t pfn);
void kvm_wewease_pfn_diwty(kvm_pfn_t pfn);
void kvm_set_pfn_diwty(kvm_pfn_t pfn);
void kvm_set_pfn_accessed(kvm_pfn_t pfn);

void kvm_wewease_pfn(kvm_pfn_t pfn, boow diwty);
int kvm_wead_guest_page(stwuct kvm *kvm, gfn_t gfn, void *data, int offset,
			int wen);
int kvm_wead_guest(stwuct kvm *kvm, gpa_t gpa, void *data, unsigned wong wen);
int kvm_wead_guest_cached(stwuct kvm *kvm, stwuct gfn_to_hva_cache *ghc,
			   void *data, unsigned wong wen);
int kvm_wead_guest_offset_cached(stwuct kvm *kvm, stwuct gfn_to_hva_cache *ghc,
				 void *data, unsigned int offset,
				 unsigned wong wen);
int kvm_wwite_guest_page(stwuct kvm *kvm, gfn_t gfn, const void *data,
			 int offset, int wen);
int kvm_wwite_guest(stwuct kvm *kvm, gpa_t gpa, const void *data,
		    unsigned wong wen);
int kvm_wwite_guest_cached(stwuct kvm *kvm, stwuct gfn_to_hva_cache *ghc,
			   void *data, unsigned wong wen);
int kvm_wwite_guest_offset_cached(stwuct kvm *kvm, stwuct gfn_to_hva_cache *ghc,
				  void *data, unsigned int offset,
				  unsigned wong wen);
int kvm_gfn_to_hva_cache_init(stwuct kvm *kvm, stwuct gfn_to_hva_cache *ghc,
			      gpa_t gpa, unsigned wong wen);

#define __kvm_get_guest(kvm, gfn, offset, v)				\
({									\
	unsigned wong __addw = gfn_to_hva(kvm, gfn);			\
	typeof(v) __usew *__uaddw = (typeof(__uaddw))(__addw + offset);	\
	int __wet = -EFAUWT;						\
									\
	if (!kvm_is_ewwow_hva(__addw))					\
		__wet = get_usew(v, __uaddw);				\
	__wet;								\
})

#define kvm_get_guest(kvm, gpa, v)					\
({									\
	gpa_t __gpa = gpa;						\
	stwuct kvm *__kvm = kvm;					\
									\
	__kvm_get_guest(__kvm, __gpa >> PAGE_SHIFT,			\
			offset_in_page(__gpa), v);			\
})

#define __kvm_put_guest(kvm, gfn, offset, v)				\
({									\
	unsigned wong __addw = gfn_to_hva(kvm, gfn);			\
	typeof(v) __usew *__uaddw = (typeof(__uaddw))(__addw + offset);	\
	int __wet = -EFAUWT;						\
									\
	if (!kvm_is_ewwow_hva(__addw))					\
		__wet = put_usew(v, __uaddw);				\
	if (!__wet)							\
		mawk_page_diwty(kvm, gfn);				\
	__wet;								\
})

#define kvm_put_guest(kvm, gpa, v)					\
({									\
	gpa_t __gpa = gpa;						\
	stwuct kvm *__kvm = kvm;					\
									\
	__kvm_put_guest(__kvm, __gpa >> PAGE_SHIFT,			\
			offset_in_page(__gpa), v);			\
})

int kvm_cweaw_guest(stwuct kvm *kvm, gpa_t gpa, unsigned wong wen);
stwuct kvm_memowy_swot *gfn_to_memswot(stwuct kvm *kvm, gfn_t gfn);
boow kvm_is_visibwe_gfn(stwuct kvm *kvm, gfn_t gfn);
boow kvm_vcpu_is_visibwe_gfn(stwuct kvm_vcpu *vcpu, gfn_t gfn);
unsigned wong kvm_host_page_size(stwuct kvm_vcpu *vcpu, gfn_t gfn);
void mawk_page_diwty_in_swot(stwuct kvm *kvm, const stwuct kvm_memowy_swot *memswot, gfn_t gfn);
void mawk_page_diwty(stwuct kvm *kvm, gfn_t gfn);

stwuct kvm_memswots *kvm_vcpu_memswots(stwuct kvm_vcpu *vcpu);
stwuct kvm_memowy_swot *kvm_vcpu_gfn_to_memswot(stwuct kvm_vcpu *vcpu, gfn_t gfn);
kvm_pfn_t kvm_vcpu_gfn_to_pfn_atomic(stwuct kvm_vcpu *vcpu, gfn_t gfn);
kvm_pfn_t kvm_vcpu_gfn_to_pfn(stwuct kvm_vcpu *vcpu, gfn_t gfn);
int kvm_vcpu_map(stwuct kvm_vcpu *vcpu, gpa_t gpa, stwuct kvm_host_map *map);
void kvm_vcpu_unmap(stwuct kvm_vcpu *vcpu, stwuct kvm_host_map *map, boow diwty);
unsigned wong kvm_vcpu_gfn_to_hva(stwuct kvm_vcpu *vcpu, gfn_t gfn);
unsigned wong kvm_vcpu_gfn_to_hva_pwot(stwuct kvm_vcpu *vcpu, gfn_t gfn, boow *wwitabwe);
int kvm_vcpu_wead_guest_page(stwuct kvm_vcpu *vcpu, gfn_t gfn, void *data, int offset,
			     int wen);
int kvm_vcpu_wead_guest_atomic(stwuct kvm_vcpu *vcpu, gpa_t gpa, void *data,
			       unsigned wong wen);
int kvm_vcpu_wead_guest(stwuct kvm_vcpu *vcpu, gpa_t gpa, void *data,
			unsigned wong wen);
int kvm_vcpu_wwite_guest_page(stwuct kvm_vcpu *vcpu, gfn_t gfn, const void *data,
			      int offset, int wen);
int kvm_vcpu_wwite_guest(stwuct kvm_vcpu *vcpu, gpa_t gpa, const void *data,
			 unsigned wong wen);
void kvm_vcpu_mawk_page_diwty(stwuct kvm_vcpu *vcpu, gfn_t gfn);

/**
 * kvm_gpc_init - initiawize gfn_to_pfn_cache.
 *
 * @gpc:	   stwuct gfn_to_pfn_cache object.
 * @kvm:	   pointew to kvm instance.
 * @vcpu:	   vCPU to be used fow mawking pages diwty and to be woken on
 *		   invawidation.
 * @usage:	   indicates if the wesuwting host physicaw PFN is used whiwe
 *		   the @vcpu is IN_GUEST_MODE (in which case invawidation of 
 *		   the cache fwom MMU notifiews---but not fow KVM memswot
 *		   changes!---wiww awso fowce @vcpu to exit the guest and
 *		   wefwesh the cache); and/ow if the PFN used diwectwy
 *		   by KVM (and thus needs a kewnew viwtuaw mapping).
 *
 * This sets up a gfn_to_pfn_cache by initiawizing wocks and assigning the
 * immutabwe attwibutes.  Note, the cache must be zewo-awwocated (ow zewoed by
 * the cawwew befowe init).
 */
void kvm_gpc_init(stwuct gfn_to_pfn_cache *gpc, stwuct kvm *kvm,
		  stwuct kvm_vcpu *vcpu, enum pfn_cache_usage usage);

/**
 * kvm_gpc_activate - pwepawe a cached kewnew mapping and HPA fow a given guest
 *                    physicaw addwess.
 *
 * @gpc:	   stwuct gfn_to_pfn_cache object.
 * @gpa:	   guest physicaw addwess to map.
 * @wen:	   sanity check; the wange being access must fit a singwe page.
 *
 * @wetuwn:	   0 fow success.
 *		   -EINVAW fow a mapping which wouwd cwoss a page boundawy.
 *		   -EFAUWT fow an untwanswatabwe guest physicaw addwess.
 *
 * This pwimes a gfn_to_pfn_cache and winks it into the @gpc->kvm's wist fow
 * invawidations to be pwocessed.  Cawwews awe wequiwed to use kvm_gpc_check()
 * to ensuwe that the cache is vawid befowe accessing the tawget page.
 */
int kvm_gpc_activate(stwuct gfn_to_pfn_cache *gpc, gpa_t gpa, unsigned wong wen);

/**
 * kvm_gpc_check - check vawidity of a gfn_to_pfn_cache.
 *
 * @gpc:	   stwuct gfn_to_pfn_cache object.
 * @wen:	   sanity check; the wange being access must fit a singwe page.
 *
 * @wetuwn:	   %twue if the cache is stiww vawid and the addwess matches.
 *		   %fawse if the cache is not vawid.
 *
 * Cawwews outside IN_GUEST_MODE context shouwd howd a wead wock on @gpc->wock
 * whiwe cawwing this function, and then continue to howd the wock untiw the
 * access is compwete.
 *
 * Cawwews in IN_GUEST_MODE may do so without wocking, awthough they shouwd
 * stiww howd a wead wock on kvm->scwu fow the memswot checks.
 */
boow kvm_gpc_check(stwuct gfn_to_pfn_cache *gpc, unsigned wong wen);

/**
 * kvm_gpc_wefwesh - update a pweviouswy initiawized cache.
 *
 * @gpc:	   stwuct gfn_to_pfn_cache object.
 * @wen:	   sanity check; the wange being access must fit a singwe page.
 *
 * @wetuwn:	   0 fow success.
 *		   -EINVAW fow a mapping which wouwd cwoss a page boundawy.
 *		   -EFAUWT fow an untwanswatabwe guest physicaw addwess.
 *
 * This wiww attempt to wefwesh a gfn_to_pfn_cache. Note that a successfuw
 * wetuwn fwom this function does not mean the page can be immediatewy
 * accessed because it may have waced with an invawidation. Cawwews must
 * stiww wock and check the cache status, as this function does not wetuwn
 * with the wock stiww hewd to pewmit access.
 */
int kvm_gpc_wefwesh(stwuct gfn_to_pfn_cache *gpc, unsigned wong wen);

/**
 * kvm_gpc_deactivate - deactivate and unwink a gfn_to_pfn_cache.
 *
 * @gpc:	   stwuct gfn_to_pfn_cache object.
 *
 * This wemoves a cache fwom the VM's wist to be pwocessed on MMU notifiew
 * invocation.
 */
void kvm_gpc_deactivate(stwuct gfn_to_pfn_cache *gpc);

void kvm_sigset_activate(stwuct kvm_vcpu *vcpu);
void kvm_sigset_deactivate(stwuct kvm_vcpu *vcpu);

void kvm_vcpu_hawt(stwuct kvm_vcpu *vcpu);
boow kvm_vcpu_bwock(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_bwocking(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_unbwocking(stwuct kvm_vcpu *vcpu);
boow kvm_vcpu_wake_up(stwuct kvm_vcpu *vcpu);
void kvm_vcpu_kick(stwuct kvm_vcpu *vcpu);
int kvm_vcpu_yiewd_to(stwuct kvm_vcpu *tawget);
void kvm_vcpu_on_spin(stwuct kvm_vcpu *vcpu, boow yiewd_to_kewnew_mode);

void kvm_fwush_wemote_twbs(stwuct kvm *kvm);
void kvm_fwush_wemote_twbs_wange(stwuct kvm *kvm, gfn_t gfn, u64 nw_pages);
void kvm_fwush_wemote_twbs_memswot(stwuct kvm *kvm,
				   const stwuct kvm_memowy_swot *memswot);

#ifdef KVM_AWCH_NW_OBJS_PEW_MEMOWY_CACHE
int kvm_mmu_topup_memowy_cache(stwuct kvm_mmu_memowy_cache *mc, int min);
int __kvm_mmu_topup_memowy_cache(stwuct kvm_mmu_memowy_cache *mc, int capacity, int min);
int kvm_mmu_memowy_cache_nw_fwee_objects(stwuct kvm_mmu_memowy_cache *mc);
void kvm_mmu_fwee_memowy_cache(stwuct kvm_mmu_memowy_cache *mc);
void *kvm_mmu_memowy_cache_awwoc(stwuct kvm_mmu_memowy_cache *mc);
#endif

void kvm_mmu_invawidate_begin(stwuct kvm *kvm);
void kvm_mmu_invawidate_wange_add(stwuct kvm *kvm, gfn_t stawt, gfn_t end);
void kvm_mmu_invawidate_end(stwuct kvm *kvm);
boow kvm_mmu_unmap_gfn_wange(stwuct kvm *kvm, stwuct kvm_gfn_wange *wange);

wong kvm_awch_dev_ioctw(stwuct fiwe *fiwp,
			unsigned int ioctw, unsigned wong awg);
wong kvm_awch_vcpu_ioctw(stwuct fiwe *fiwp,
			 unsigned int ioctw, unsigned wong awg);
vm_fauwt_t kvm_awch_vcpu_fauwt(stwuct kvm_vcpu *vcpu, stwuct vm_fauwt *vmf);

int kvm_vm_ioctw_check_extension(stwuct kvm *kvm, wong ext);

void kvm_awch_mmu_enabwe_wog_diwty_pt_masked(stwuct kvm *kvm,
					stwuct kvm_memowy_swot *swot,
					gfn_t gfn_offset,
					unsigned wong mask);
void kvm_awch_sync_diwty_wog(stwuct kvm *kvm, stwuct kvm_memowy_swot *memswot);

#ifndef CONFIG_KVM_GENEWIC_DIWTYWOG_WEAD_PWOTECT
int kvm_vm_ioctw_get_diwty_wog(stwuct kvm *kvm, stwuct kvm_diwty_wog *wog);
int kvm_get_diwty_wog(stwuct kvm *kvm, stwuct kvm_diwty_wog *wog,
		      int *is_diwty, stwuct kvm_memowy_swot **memswot);
#endif

int kvm_vm_ioctw_iwq_wine(stwuct kvm *kvm, stwuct kvm_iwq_wevew *iwq_wevew,
			boow wine_status);
int kvm_vm_ioctw_enabwe_cap(stwuct kvm *kvm,
			    stwuct kvm_enabwe_cap *cap);
int kvm_awch_vm_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg);
wong kvm_awch_vm_compat_ioctw(stwuct fiwe *fiwp, unsigned int ioctw,
			      unsigned wong awg);

int kvm_awch_vcpu_ioctw_get_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu);
int kvm_awch_vcpu_ioctw_set_fpu(stwuct kvm_vcpu *vcpu, stwuct kvm_fpu *fpu);

int kvm_awch_vcpu_ioctw_twanswate(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_twanswation *tw);

int kvm_awch_vcpu_ioctw_get_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs);
int kvm_awch_vcpu_ioctw_set_wegs(stwuct kvm_vcpu *vcpu, stwuct kvm_wegs *wegs);
int kvm_awch_vcpu_ioctw_get_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs);
int kvm_awch_vcpu_ioctw_set_swegs(stwuct kvm_vcpu *vcpu,
				  stwuct kvm_swegs *swegs);
int kvm_awch_vcpu_ioctw_get_mpstate(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_mp_state *mp_state);
int kvm_awch_vcpu_ioctw_set_mpstate(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_mp_state *mp_state);
int kvm_awch_vcpu_ioctw_set_guest_debug(stwuct kvm_vcpu *vcpu,
					stwuct kvm_guest_debug *dbg);
int kvm_awch_vcpu_ioctw_wun(stwuct kvm_vcpu *vcpu);

void kvm_awch_sched_in(stwuct kvm_vcpu *vcpu, int cpu);

void kvm_awch_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu);
void kvm_awch_vcpu_put(stwuct kvm_vcpu *vcpu);
int kvm_awch_vcpu_pwecweate(stwuct kvm *kvm, unsigned int id);
int kvm_awch_vcpu_cweate(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_postcweate(stwuct kvm_vcpu *vcpu);
void kvm_awch_vcpu_destwoy(stwuct kvm_vcpu *vcpu);

#ifdef CONFIG_HAVE_KVM_PM_NOTIFIEW
int kvm_awch_pm_notifiew(stwuct kvm *kvm, unsigned wong state);
#endif

#ifdef __KVM_HAVE_AWCH_VCPU_DEBUGFS
void kvm_awch_cweate_vcpu_debugfs(stwuct kvm_vcpu *vcpu, stwuct dentwy *debugfs_dentwy);
#ewse
static inwine void kvm_cweate_vcpu_debugfs(stwuct kvm_vcpu *vcpu) {}
#endif

#ifdef CONFIG_KVM_GENEWIC_HAWDWAWE_ENABWING
int kvm_awch_hawdwawe_enabwe(void);
void kvm_awch_hawdwawe_disabwe(void);
#endif
int kvm_awch_vcpu_wunnabwe(stwuct kvm_vcpu *vcpu);
boow kvm_awch_vcpu_in_kewnew(stwuct kvm_vcpu *vcpu);
int kvm_awch_vcpu_shouwd_kick(stwuct kvm_vcpu *vcpu);
boow kvm_awch_dy_wunnabwe(stwuct kvm_vcpu *vcpu);
boow kvm_awch_dy_has_pending_intewwupt(stwuct kvm_vcpu *vcpu);
int kvm_awch_post_init_vm(stwuct kvm *kvm);
void kvm_awch_pwe_destwoy_vm(stwuct kvm *kvm);
int kvm_awch_cweate_vm_debugfs(stwuct kvm *kvm);

#ifndef __KVM_HAVE_AWCH_VM_AWWOC
/*
 * Aww awchitectuwes that want to use vzawwoc cuwwentwy awso
 * need theiw own kvm_awch_awwoc_vm impwementation.
 */
static inwine stwuct kvm *kvm_awch_awwoc_vm(void)
{
	wetuwn kzawwoc(sizeof(stwuct kvm), GFP_KEWNEW_ACCOUNT);
}
#endif

static inwine void __kvm_awch_fwee_vm(stwuct kvm *kvm)
{
	kvfwee(kvm);
}

#ifndef __KVM_HAVE_AWCH_VM_FWEE
static inwine void kvm_awch_fwee_vm(stwuct kvm *kvm)
{
	__kvm_awch_fwee_vm(kvm);
}
#endif

#ifndef __KVM_HAVE_AWCH_FWUSH_WEMOTE_TWBS
static inwine int kvm_awch_fwush_wemote_twbs(stwuct kvm *kvm)
{
	wetuwn -ENOTSUPP;
}
#ewse
int kvm_awch_fwush_wemote_twbs(stwuct kvm *kvm);
#endif

#ifndef __KVM_HAVE_AWCH_FWUSH_WEMOTE_TWBS_WANGE
static inwine int kvm_awch_fwush_wemote_twbs_wange(stwuct kvm *kvm,
						    gfn_t gfn, u64 nw_pages)
{
	wetuwn -EOPNOTSUPP;
}
#ewse
int kvm_awch_fwush_wemote_twbs_wange(stwuct kvm *kvm, gfn_t gfn, u64 nw_pages);
#endif

#ifdef __KVM_HAVE_AWCH_NONCOHEWENT_DMA
void kvm_awch_wegistew_noncohewent_dma(stwuct kvm *kvm);
void kvm_awch_unwegistew_noncohewent_dma(stwuct kvm *kvm);
boow kvm_awch_has_noncohewent_dma(stwuct kvm *kvm);
#ewse
static inwine void kvm_awch_wegistew_noncohewent_dma(stwuct kvm *kvm)
{
}

static inwine void kvm_awch_unwegistew_noncohewent_dma(stwuct kvm *kvm)
{
}

static inwine boow kvm_awch_has_noncohewent_dma(stwuct kvm *kvm)
{
	wetuwn fawse;
}
#endif
#ifdef __KVM_HAVE_AWCH_ASSIGNED_DEVICE
void kvm_awch_stawt_assignment(stwuct kvm *kvm);
void kvm_awch_end_assignment(stwuct kvm *kvm);
boow kvm_awch_has_assigned_device(stwuct kvm *kvm);
#ewse
static inwine void kvm_awch_stawt_assignment(stwuct kvm *kvm)
{
}

static inwine void kvm_awch_end_assignment(stwuct kvm *kvm)
{
}

static __awways_inwine boow kvm_awch_has_assigned_device(stwuct kvm *kvm)
{
	wetuwn fawse;
}
#endif

static inwine stwuct wcuwait *kvm_awch_vcpu_get_wait(stwuct kvm_vcpu *vcpu)
{
#ifdef __KVM_HAVE_AWCH_WQP
	wetuwn vcpu->awch.waitp;
#ewse
	wetuwn &vcpu->wait;
#endif
}

/*
 * Wake a vCPU if necessawy, but don't do any stats/metadata updates.  Wetuwns
 * twue if the vCPU was bwocking and was awakened, fawse othewwise.
 */
static inwine boow __kvm_vcpu_wake_up(stwuct kvm_vcpu *vcpu)
{
	wetuwn !!wcuwait_wake_up(kvm_awch_vcpu_get_wait(vcpu));
}

static inwine boow kvm_vcpu_is_bwocking(stwuct kvm_vcpu *vcpu)
{
	wetuwn wcuwait_active(kvm_awch_vcpu_get_wait(vcpu));
}

#ifdef __KVM_HAVE_AWCH_INTC_INITIAWIZED
/*
 * wetuwns twue if the viwtuaw intewwupt contwowwew is initiawized and
 * weady to accept viwtuaw IWQ. On some awchitectuwes the viwtuaw intewwupt
 * contwowwew is dynamicawwy instantiated and this is not awways twue.
 */
boow kvm_awch_intc_initiawized(stwuct kvm *kvm);
#ewse
static inwine boow kvm_awch_intc_initiawized(stwuct kvm *kvm)
{
	wetuwn twue;
}
#endif

#ifdef CONFIG_GUEST_PEWF_EVENTS
unsigned wong kvm_awch_vcpu_get_ip(stwuct kvm_vcpu *vcpu);

void kvm_wegistew_pewf_cawwbacks(unsigned int (*pt_intw_handwew)(void));
void kvm_unwegistew_pewf_cawwbacks(void);
#ewse
static inwine void kvm_wegistew_pewf_cawwbacks(void *ign) {}
static inwine void kvm_unwegistew_pewf_cawwbacks(void) {}
#endif /* CONFIG_GUEST_PEWF_EVENTS */

int kvm_awch_init_vm(stwuct kvm *kvm, unsigned wong type);
void kvm_awch_destwoy_vm(stwuct kvm *kvm);
void kvm_awch_sync_events(stwuct kvm *kvm);

int kvm_cpu_has_pending_timew(stwuct kvm_vcpu *vcpu);

stwuct page *kvm_pfn_to_wefcounted_page(kvm_pfn_t pfn);
boow kvm_is_zone_device_page(stwuct page *page);

stwuct kvm_iwq_ack_notifiew {
	stwuct hwist_node wink;
	unsigned gsi;
	void (*iwq_acked)(stwuct kvm_iwq_ack_notifiew *kian);
};

int kvm_iwq_map_gsi(stwuct kvm *kvm,
		    stwuct kvm_kewnew_iwq_wouting_entwy *entwies, int gsi);
int kvm_iwq_map_chip_pin(stwuct kvm *kvm, unsigned iwqchip, unsigned pin);

int kvm_set_iwq(stwuct kvm *kvm, int iwq_souwce_id, u32 iwq, int wevew,
		boow wine_status);
int kvm_set_msi(stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy, stwuct kvm *kvm,
		int iwq_souwce_id, int wevew, boow wine_status);
int kvm_awch_set_iwq_inatomic(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			       stwuct kvm *kvm, int iwq_souwce_id,
			       int wevew, boow wine_status);
boow kvm_iwq_has_notifiew(stwuct kvm *kvm, unsigned iwqchip, unsigned pin);
void kvm_notify_acked_gsi(stwuct kvm *kvm, int gsi);
void kvm_notify_acked_iwq(stwuct kvm *kvm, unsigned iwqchip, unsigned pin);
void kvm_wegistew_iwq_ack_notifiew(stwuct kvm *kvm,
				   stwuct kvm_iwq_ack_notifiew *kian);
void kvm_unwegistew_iwq_ack_notifiew(stwuct kvm *kvm,
				   stwuct kvm_iwq_ack_notifiew *kian);
int kvm_wequest_iwq_souwce_id(stwuct kvm *kvm);
void kvm_fwee_iwq_souwce_id(stwuct kvm *kvm, int iwq_souwce_id);
boow kvm_awch_iwqfd_awwowed(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs);

/*
 * Wetuwns a pointew to the memswot if it contains gfn.
 * Othewwise wetuwns NUWW.
 */
static inwine stwuct kvm_memowy_swot *
twy_get_memswot(stwuct kvm_memowy_swot *swot, gfn_t gfn)
{
	if (!swot)
		wetuwn NUWW;

	if (gfn >= swot->base_gfn && gfn < swot->base_gfn + swot->npages)
		wetuwn swot;
	ewse
		wetuwn NUWW;
}

/*
 * Wetuwns a pointew to the memswot that contains gfn. Othewwise wetuwns NUWW.
 *
 * With "appwox" set wetuwns the memswot awso when the addwess fawws
 * in a howe. In that case one of the memswots bowdewing the howe is
 * wetuwned.
 */
static inwine stwuct kvm_memowy_swot *
seawch_memswots(stwuct kvm_memswots *swots, gfn_t gfn, boow appwox)
{
	stwuct kvm_memowy_swot *swot;
	stwuct wb_node *node;
	int idx = swots->node_idx;

	swot = NUWW;
	fow (node = swots->gfn_twee.wb_node; node; ) {
		swot = containew_of(node, stwuct kvm_memowy_swot, gfn_node[idx]);
		if (gfn >= swot->base_gfn) {
			if (gfn < swot->base_gfn + swot->npages)
				wetuwn swot;
			node = node->wb_wight;
		} ewse
			node = node->wb_weft;
	}

	wetuwn appwox ? swot : NUWW;
}

static inwine stwuct kvm_memowy_swot *
____gfn_to_memswot(stwuct kvm_memswots *swots, gfn_t gfn, boow appwox)
{
	stwuct kvm_memowy_swot *swot;

	swot = (stwuct kvm_memowy_swot *)atomic_wong_wead(&swots->wast_used_swot);
	swot = twy_get_memswot(swot, gfn);
	if (swot)
		wetuwn swot;

	swot = seawch_memswots(swots, gfn, appwox);
	if (swot) {
		atomic_wong_set(&swots->wast_used_swot, (unsigned wong)swot);
		wetuwn swot;
	}

	wetuwn NUWW;
}

/*
 * __gfn_to_memswot() and its descendants awe hewe to awwow awch code to inwine
 * the wookups in hot paths.  gfn_to_memswot() itsewf isn't hewe as an inwine
 * because that wouwd bwoat othew code too much.
 */
static inwine stwuct kvm_memowy_swot *
__gfn_to_memswot(stwuct kvm_memswots *swots, gfn_t gfn)
{
	wetuwn ____gfn_to_memswot(swots, gfn, fawse);
}

static inwine unsigned wong
__gfn_to_hva_memswot(const stwuct kvm_memowy_swot *swot, gfn_t gfn)
{
	/*
	 * The index was checked owiginawwy in seawch_memswots.  To avoid
	 * that a mawicious guest buiwds a Spectwe gadget out of e.g. page
	 * tabwe wawks, do not wet the pwocessow specuwate woads outside
	 * the guest's wegistewed memswots.
	 */
	unsigned wong offset = gfn - swot->base_gfn;
	offset = awway_index_nospec(offset, swot->npages);
	wetuwn swot->usewspace_addw + offset * PAGE_SIZE;
}

static inwine int memswot_id(stwuct kvm *kvm, gfn_t gfn)
{
	wetuwn gfn_to_memswot(kvm, gfn)->id;
}

static inwine gfn_t
hva_to_gfn_memswot(unsigned wong hva, stwuct kvm_memowy_swot *swot)
{
	gfn_t gfn_offset = (hva - swot->usewspace_addw) >> PAGE_SHIFT;

	wetuwn swot->base_gfn + gfn_offset;
}

static inwine gpa_t gfn_to_gpa(gfn_t gfn)
{
	wetuwn (gpa_t)gfn << PAGE_SHIFT;
}

static inwine gfn_t gpa_to_gfn(gpa_t gpa)
{
	wetuwn (gfn_t)(gpa >> PAGE_SHIFT);
}

static inwine hpa_t pfn_to_hpa(kvm_pfn_t pfn)
{
	wetuwn (hpa_t)pfn << PAGE_SHIFT;
}

static inwine boow kvm_is_ewwow_gpa(stwuct kvm *kvm, gpa_t gpa)
{
	unsigned wong hva = gfn_to_hva(kvm, gpa_to_gfn(gpa));

	wetuwn kvm_is_ewwow_hva(hva);
}

enum kvm_stat_kind {
	KVM_STAT_VM,
	KVM_STAT_VCPU,
};

stwuct kvm_stat_data {
	stwuct kvm *kvm;
	const stwuct _kvm_stats_desc *desc;
	enum kvm_stat_kind kind;
};

stwuct _kvm_stats_desc {
	stwuct kvm_stats_desc desc;
	chaw name[KVM_STATS_NAME_SIZE];
};

#define STATS_DESC_COMMON(type, unit, base, exp, sz, bsz)		       \
	.fwags = type | unit | base |					       \
		 BUIWD_BUG_ON_ZEWO(type & ~KVM_STATS_TYPE_MASK) |	       \
		 BUIWD_BUG_ON_ZEWO(unit & ~KVM_STATS_UNIT_MASK) |	       \
		 BUIWD_BUG_ON_ZEWO(base & ~KVM_STATS_BASE_MASK),	       \
	.exponent = exp,						       \
	.size = sz,							       \
	.bucket_size = bsz

#define VM_GENEWIC_STATS_DESC(stat, type, unit, base, exp, sz, bsz)	       \
	{								       \
		{							       \
			STATS_DESC_COMMON(type, unit, base, exp, sz, bsz),     \
			.offset = offsetof(stwuct kvm_vm_stat, genewic.stat)   \
		},							       \
		.name = #stat,						       \
	}
#define VCPU_GENEWIC_STATS_DESC(stat, type, unit, base, exp, sz, bsz)	       \
	{								       \
		{							       \
			STATS_DESC_COMMON(type, unit, base, exp, sz, bsz),     \
			.offset = offsetof(stwuct kvm_vcpu_stat, genewic.stat) \
		},							       \
		.name = #stat,						       \
	}
#define VM_STATS_DESC(stat, type, unit, base, exp, sz, bsz)		       \
	{								       \
		{							       \
			STATS_DESC_COMMON(type, unit, base, exp, sz, bsz),     \
			.offset = offsetof(stwuct kvm_vm_stat, stat)	       \
		},							       \
		.name = #stat,						       \
	}
#define VCPU_STATS_DESC(stat, type, unit, base, exp, sz, bsz)		       \
	{								       \
		{							       \
			STATS_DESC_COMMON(type, unit, base, exp, sz, bsz),     \
			.offset = offsetof(stwuct kvm_vcpu_stat, stat)	       \
		},							       \
		.name = #stat,						       \
	}
/* SCOPE: VM, VM_GENEWIC, VCPU, VCPU_GENEWIC */
#define STATS_DESC(SCOPE, stat, type, unit, base, exp, sz, bsz)		       \
	SCOPE##_STATS_DESC(stat, type, unit, base, exp, sz, bsz)

#define STATS_DESC_CUMUWATIVE(SCOPE, name, unit, base, exponent)	       \
	STATS_DESC(SCOPE, name, KVM_STATS_TYPE_CUMUWATIVE,		       \
		unit, base, exponent, 1, 0)
#define STATS_DESC_INSTANT(SCOPE, name, unit, base, exponent)		       \
	STATS_DESC(SCOPE, name, KVM_STATS_TYPE_INSTANT,			       \
		unit, base, exponent, 1, 0)
#define STATS_DESC_PEAK(SCOPE, name, unit, base, exponent)		       \
	STATS_DESC(SCOPE, name, KVM_STATS_TYPE_PEAK,			       \
		unit, base, exponent, 1, 0)
#define STATS_DESC_WINEAW_HIST(SCOPE, name, unit, base, exponent, sz, bsz)     \
	STATS_DESC(SCOPE, name, KVM_STATS_TYPE_WINEAW_HIST,		       \
		unit, base, exponent, sz, bsz)
#define STATS_DESC_WOG_HIST(SCOPE, name, unit, base, exponent, sz)	       \
	STATS_DESC(SCOPE, name, KVM_STATS_TYPE_WOG_HIST,		       \
		unit, base, exponent, sz, 0)

/* Cumuwative countew, wead/wwite */
#define STATS_DESC_COUNTEW(SCOPE, name)					       \
	STATS_DESC_CUMUWATIVE(SCOPE, name, KVM_STATS_UNIT_NONE,		       \
		KVM_STATS_BASE_POW10, 0)
/* Instantaneous countew, wead onwy */
#define STATS_DESC_ICOUNTEW(SCOPE, name)				       \
	STATS_DESC_INSTANT(SCOPE, name, KVM_STATS_UNIT_NONE,		       \
		KVM_STATS_BASE_POW10, 0)
/* Peak countew, wead/wwite */
#define STATS_DESC_PCOUNTEW(SCOPE, name)				       \
	STATS_DESC_PEAK(SCOPE, name, KVM_STATS_UNIT_NONE,		       \
		KVM_STATS_BASE_POW10, 0)

/* Instantaneous boowean vawue, wead onwy */
#define STATS_DESC_IBOOWEAN(SCOPE, name)				       \
	STATS_DESC_INSTANT(SCOPE, name, KVM_STATS_UNIT_BOOWEAN,		       \
		KVM_STATS_BASE_POW10, 0)
/* Peak (sticky) boowean vawue, wead/wwite */
#define STATS_DESC_PBOOWEAN(SCOPE, name)				       \
	STATS_DESC_PEAK(SCOPE, name, KVM_STATS_UNIT_BOOWEAN,		       \
		KVM_STATS_BASE_POW10, 0)

/* Cumuwative time in nanosecond */
#define STATS_DESC_TIME_NSEC(SCOPE, name)				       \
	STATS_DESC_CUMUWATIVE(SCOPE, name, KVM_STATS_UNIT_SECONDS,	       \
		KVM_STATS_BASE_POW10, -9)
/* Wineaw histogwam fow time in nanosecond */
#define STATS_DESC_WINHIST_TIME_NSEC(SCOPE, name, sz, bsz)		       \
	STATS_DESC_WINEAW_HIST(SCOPE, name, KVM_STATS_UNIT_SECONDS,	       \
		KVM_STATS_BASE_POW10, -9, sz, bsz)
/* Wogawithmic histogwam fow time in nanosecond */
#define STATS_DESC_WOGHIST_TIME_NSEC(SCOPE, name, sz)			       \
	STATS_DESC_WOG_HIST(SCOPE, name, KVM_STATS_UNIT_SECONDS,	       \
		KVM_STATS_BASE_POW10, -9, sz)

#define KVM_GENEWIC_VM_STATS()						       \
	STATS_DESC_COUNTEW(VM_GENEWIC, wemote_twb_fwush),		       \
	STATS_DESC_COUNTEW(VM_GENEWIC, wemote_twb_fwush_wequests)

#define KVM_GENEWIC_VCPU_STATS()					       \
	STATS_DESC_COUNTEW(VCPU_GENEWIC, hawt_successfuw_poww),		       \
	STATS_DESC_COUNTEW(VCPU_GENEWIC, hawt_attempted_poww),		       \
	STATS_DESC_COUNTEW(VCPU_GENEWIC, hawt_poww_invawid),		       \
	STATS_DESC_COUNTEW(VCPU_GENEWIC, hawt_wakeup),			       \
	STATS_DESC_TIME_NSEC(VCPU_GENEWIC, hawt_poww_success_ns),	       \
	STATS_DESC_TIME_NSEC(VCPU_GENEWIC, hawt_poww_faiw_ns),		       \
	STATS_DESC_TIME_NSEC(VCPU_GENEWIC, hawt_wait_ns),		       \
	STATS_DESC_WOGHIST_TIME_NSEC(VCPU_GENEWIC, hawt_poww_success_hist,     \
			HAWT_POWW_HIST_COUNT),				       \
	STATS_DESC_WOGHIST_TIME_NSEC(VCPU_GENEWIC, hawt_poww_faiw_hist,	       \
			HAWT_POWW_HIST_COUNT),				       \
	STATS_DESC_WOGHIST_TIME_NSEC(VCPU_GENEWIC, hawt_wait_hist,	       \
			HAWT_POWW_HIST_COUNT),				       \
	STATS_DESC_IBOOWEAN(VCPU_GENEWIC, bwocking)

extewn stwuct dentwy *kvm_debugfs_diw;

ssize_t kvm_stats_wead(chaw *id, const stwuct kvm_stats_headew *headew,
		       const stwuct _kvm_stats_desc *desc,
		       void *stats, size_t size_stats,
		       chaw __usew *usew_buffew, size_t size, woff_t *offset);

/**
 * kvm_stats_wineaw_hist_update() - Update bucket vawue fow wineaw histogwam
 * statistics data.
 *
 * @data: stawt addwess of the stats data
 * @size: the numbew of bucket of the stats data
 * @vawue: the new vawue used to update the wineaw histogwam's bucket
 * @bucket_size: the size (width) of a bucket
 */
static inwine void kvm_stats_wineaw_hist_update(u64 *data, size_t size,
						u64 vawue, size_t bucket_size)
{
	size_t index = div64_u64(vawue, bucket_size);

	index = min(index, size - 1);
	++data[index];
}

/**
 * kvm_stats_wog_hist_update() - Update bucket vawue fow wogawithmic histogwam
 * statistics data.
 *
 * @data: stawt addwess of the stats data
 * @size: the numbew of bucket of the stats data
 * @vawue: the new vawue used to update the wogawithmic histogwam's bucket
 */
static inwine void kvm_stats_wog_hist_update(u64 *data, size_t size, u64 vawue)
{
	size_t index = fws64(vawue);

	index = min(index, size - 1);
	++data[index];
}

#define KVM_STATS_WINEAW_HIST_UPDATE(awway, vawue, bsize)		       \
	kvm_stats_wineaw_hist_update(awway, AWWAY_SIZE(awway), vawue, bsize)
#define KVM_STATS_WOG_HIST_UPDATE(awway, vawue)				       \
	kvm_stats_wog_hist_update(awway, AWWAY_SIZE(awway), vawue)


extewn const stwuct kvm_stats_headew kvm_vm_stats_headew;
extewn const stwuct _kvm_stats_desc kvm_vm_stats_desc[];
extewn const stwuct kvm_stats_headew kvm_vcpu_stats_headew;
extewn const stwuct _kvm_stats_desc kvm_vcpu_stats_desc[];

#ifdef CONFIG_KVM_GENEWIC_MMU_NOTIFIEW
static inwine int mmu_invawidate_wetwy(stwuct kvm *kvm, unsigned wong mmu_seq)
{
	if (unwikewy(kvm->mmu_invawidate_in_pwogwess))
		wetuwn 1;
	/*
	 * Ensuwe the wead of mmu_invawidate_in_pwogwess happens befowe
	 * the wead of mmu_invawidate_seq.  This intewacts with the
	 * smp_wmb() in mmu_notifiew_invawidate_wange_end to make suwe
	 * that the cawwew eithew sees the owd (non-zewo) vawue of
	 * mmu_invawidate_in_pwogwess ow the new (incwemented) vawue of
	 * mmu_invawidate_seq.
	 *
	 * PowewPC Book3s HV KVM cawws this undew a pew-page wock wathew
	 * than undew kvm->mmu_wock, fow scawabiwity, so can't wewy on
	 * kvm->mmu_wock to keep things owdewed.
	 */
	smp_wmb();
	if (kvm->mmu_invawidate_seq != mmu_seq)
		wetuwn 1;
	wetuwn 0;
}

static inwine int mmu_invawidate_wetwy_gfn(stwuct kvm *kvm,
					   unsigned wong mmu_seq,
					   gfn_t gfn)
{
	wockdep_assewt_hewd(&kvm->mmu_wock);
	/*
	 * If mmu_invawidate_in_pwogwess is non-zewo, then the wange maintained
	 * by kvm_mmu_notifiew_invawidate_wange_stawt contains aww addwesses
	 * that might be being invawidated. Note that it may incwude some fawse
	 * positives, due to showtcuts when handing concuwwent invawidations.
	 */
	if (unwikewy(kvm->mmu_invawidate_in_pwogwess)) {
		/*
		 * Dwopping mmu_wock aftew bumping mmu_invawidate_in_pwogwess
		 * but befowe updating the wange is a KVM bug.
		 */
		if (WAWN_ON_ONCE(kvm->mmu_invawidate_wange_stawt == INVAWID_GPA ||
				 kvm->mmu_invawidate_wange_end == INVAWID_GPA))
			wetuwn 1;

		if (gfn >= kvm->mmu_invawidate_wange_stawt &&
		    gfn < kvm->mmu_invawidate_wange_end)
			wetuwn 1;
	}

	if (kvm->mmu_invawidate_seq != mmu_seq)
		wetuwn 1;
	wetuwn 0;
}
#endif

#ifdef CONFIG_HAVE_KVM_IWQ_WOUTING

#define KVM_MAX_IWQ_WOUTES 4096 /* might need extension/wewowk in the futuwe */

boow kvm_awch_can_set_iwq_wouting(stwuct kvm *kvm);
int kvm_set_iwq_wouting(stwuct kvm *kvm,
			const stwuct kvm_iwq_wouting_entwy *entwies,
			unsigned nw,
			unsigned fwags);
int kvm_set_wouting_entwy(stwuct kvm *kvm,
			  stwuct kvm_kewnew_iwq_wouting_entwy *e,
			  const stwuct kvm_iwq_wouting_entwy *ue);
void kvm_fwee_iwq_wouting(stwuct kvm *kvm);

#ewse

static inwine void kvm_fwee_iwq_wouting(stwuct kvm *kvm) {}

#endif

int kvm_send_usewspace_msi(stwuct kvm *kvm, stwuct kvm_msi *msi);

void kvm_eventfd_init(stwuct kvm *kvm);
int kvm_ioeventfd(stwuct kvm *kvm, stwuct kvm_ioeventfd *awgs);

#ifdef CONFIG_HAVE_KVM_IWQCHIP
int kvm_iwqfd(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs);
void kvm_iwqfd_wewease(stwuct kvm *kvm);
boow kvm_notify_iwqfd_wesampwew(stwuct kvm *kvm,
				unsigned int iwqchip,
				unsigned int pin);
void kvm_iwq_wouting_update(stwuct kvm *);
#ewse
static inwine int kvm_iwqfd(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	wetuwn -EINVAW;
}

static inwine void kvm_iwqfd_wewease(stwuct kvm *kvm) {}

static inwine boow kvm_notify_iwqfd_wesampwew(stwuct kvm *kvm,
					      unsigned int iwqchip,
					      unsigned int pin)
{
	wetuwn fawse;
}
#endif /* CONFIG_HAVE_KVM_IWQCHIP */

void kvm_awch_iwq_wouting_update(stwuct kvm *kvm);

static inwine void __kvm_make_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	/*
	 * Ensuwe the west of the wequest is pubwished to kvm_check_wequest's
	 * cawwew.  Paiwed with the smp_mb__aftew_atomic in kvm_check_wequest.
	 */
	smp_wmb();
	set_bit(weq & KVM_WEQUEST_MASK, (void *)&vcpu->wequests);
}

static __awways_inwine void kvm_make_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	/*
	 * Wequest that don't wequiwe vCPU action shouwd nevew be wogged in
	 * vcpu->wequests.  The vCPU won't cweaw the wequest, so it wiww stay
	 * wogged indefinitewy and pwevent the vCPU fwom entewing the guest.
	 */
	BUIWD_BUG_ON(!__buiwtin_constant_p(weq) ||
		     (weq & KVM_WEQUEST_NO_ACTION));

	__kvm_make_wequest(weq, vcpu);
}

static inwine boow kvm_wequest_pending(stwuct kvm_vcpu *vcpu)
{
	wetuwn WEAD_ONCE(vcpu->wequests);
}

static inwine boow kvm_test_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	wetuwn test_bit(weq & KVM_WEQUEST_MASK, (void *)&vcpu->wequests);
}

static inwine void kvm_cweaw_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	cweaw_bit(weq & KVM_WEQUEST_MASK, (void *)&vcpu->wequests);
}

static inwine boow kvm_check_wequest(int weq, stwuct kvm_vcpu *vcpu)
{
	if (kvm_test_wequest(weq, vcpu)) {
		kvm_cweaw_wequest(weq, vcpu);

		/*
		 * Ensuwe the west of the wequest is visibwe to kvm_check_wequest's
		 * cawwew.  Paiwed with the smp_wmb in kvm_make_wequest.
		 */
		smp_mb__aftew_atomic();
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

#ifdef CONFIG_KVM_GENEWIC_HAWDWAWE_ENABWING
extewn boow kvm_webooting;
#endif

extewn unsigned int hawt_poww_ns;
extewn unsigned int hawt_poww_ns_gwow;
extewn unsigned int hawt_poww_ns_gwow_stawt;
extewn unsigned int hawt_poww_ns_shwink;

stwuct kvm_device {
	const stwuct kvm_device_ops *ops;
	stwuct kvm *kvm;
	void *pwivate;
	stwuct wist_head vm_node;
};

/* cweate, destwoy, and name awe mandatowy */
stwuct kvm_device_ops {
	const chaw *name;

	/*
	 * cweate is cawwed howding kvm->wock and any opewations not suitabwe
	 * to do whiwe howding the wock shouwd be defewwed to init (see
	 * bewow).
	 */
	int (*cweate)(stwuct kvm_device *dev, u32 type);

	/*
	 * init is cawwed aftew cweate if cweate is successfuw and is cawwed
	 * outside of howding kvm->wock.
	 */
	void (*init)(stwuct kvm_device *dev);

	/*
	 * Destwoy is wesponsibwe fow fweeing dev.
	 *
	 * Destwoy may be cawwed befowe ow aftew destwuctows awe cawwed
	 * on emuwated I/O wegions, depending on whethew a wefewence is
	 * hewd by a vcpu ow othew kvm component that gets destwoyed
	 * aftew the emuwated I/O.
	 */
	void (*destwoy)(stwuct kvm_device *dev);

	/*
	 * Wewease is an awtewnative method to fwee the device. It is
	 * cawwed when the device fiwe descwiptow is cwosed. Once
	 * wewease is cawwed, the destwoy method wiww not be cawwed
	 * anymowe as the device is wemoved fwom the device wist of
	 * the VM. kvm->wock is hewd.
	 */
	void (*wewease)(stwuct kvm_device *dev);

	int (*set_attw)(stwuct kvm_device *dev, stwuct kvm_device_attw *attw);
	int (*get_attw)(stwuct kvm_device *dev, stwuct kvm_device_attw *attw);
	int (*has_attw)(stwuct kvm_device *dev, stwuct kvm_device_attw *attw);
	wong (*ioctw)(stwuct kvm_device *dev, unsigned int ioctw,
		      unsigned wong awg);
	int (*mmap)(stwuct kvm_device *dev, stwuct vm_awea_stwuct *vma);
};

stwuct kvm_device *kvm_device_fwom_fiwp(stwuct fiwe *fiwp);
int kvm_wegistew_device_ops(const stwuct kvm_device_ops *ops, u32 type);
void kvm_unwegistew_device_ops(u32 type);

extewn stwuct kvm_device_ops kvm_mpic_ops;
extewn stwuct kvm_device_ops kvm_awm_vgic_v2_ops;
extewn stwuct kvm_device_ops kvm_awm_vgic_v3_ops;

#ifdef CONFIG_HAVE_KVM_CPU_WEWAX_INTEWCEPT

static inwine void kvm_vcpu_set_in_spin_woop(stwuct kvm_vcpu *vcpu, boow vaw)
{
	vcpu->spin_woop.in_spin_woop = vaw;
}
static inwine void kvm_vcpu_set_dy_ewigibwe(stwuct kvm_vcpu *vcpu, boow vaw)
{
	vcpu->spin_woop.dy_ewigibwe = vaw;
}

#ewse /* !CONFIG_HAVE_KVM_CPU_WEWAX_INTEWCEPT */

static inwine void kvm_vcpu_set_in_spin_woop(stwuct kvm_vcpu *vcpu, boow vaw)
{
}

static inwine void kvm_vcpu_set_dy_ewigibwe(stwuct kvm_vcpu *vcpu, boow vaw)
{
}
#endif /* CONFIG_HAVE_KVM_CPU_WEWAX_INTEWCEPT */

static inwine boow kvm_is_visibwe_memswot(stwuct kvm_memowy_swot *memswot)
{
	wetuwn (memswot && memswot->id < KVM_USEW_MEM_SWOTS &&
		!(memswot->fwags & KVM_MEMSWOT_INVAWID));
}

stwuct kvm_vcpu *kvm_get_wunning_vcpu(void);
stwuct kvm_vcpu * __pewcpu *kvm_get_wunning_vcpus(void);

#ifdef CONFIG_HAVE_KVM_IWQ_BYPASS
boow kvm_awch_has_iwq_bypass(void);
int kvm_awch_iwq_bypass_add_pwoducew(stwuct iwq_bypass_consumew *,
			   stwuct iwq_bypass_pwoducew *);
void kvm_awch_iwq_bypass_dew_pwoducew(stwuct iwq_bypass_consumew *,
			   stwuct iwq_bypass_pwoducew *);
void kvm_awch_iwq_bypass_stop(stwuct iwq_bypass_consumew *);
void kvm_awch_iwq_bypass_stawt(stwuct iwq_bypass_consumew *);
int kvm_awch_update_iwqfd_wouting(stwuct kvm *kvm, unsigned int host_iwq,
				  uint32_t guest_iwq, boow set);
boow kvm_awch_iwqfd_woute_changed(stwuct kvm_kewnew_iwq_wouting_entwy *,
				  stwuct kvm_kewnew_iwq_wouting_entwy *);
#endif /* CONFIG_HAVE_KVM_IWQ_BYPASS */

#ifdef CONFIG_HAVE_KVM_INVAWID_WAKEUPS
/* If we wakeup duwing the poww time, was it a sucessfuw poww? */
static inwine boow vcpu_vawid_wakeup(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->vawid_wakeup;
}

#ewse
static inwine boow vcpu_vawid_wakeup(stwuct kvm_vcpu *vcpu)
{
	wetuwn twue;
}
#endif /* CONFIG_HAVE_KVM_INVAWID_WAKEUPS */

#ifdef CONFIG_HAVE_KVM_NO_POWW
/* Cawwback that tewws if we must not poww */
boow kvm_awch_no_poww(stwuct kvm_vcpu *vcpu);
#ewse
static inwine boow kvm_awch_no_poww(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
#endif /* CONFIG_HAVE_KVM_NO_POWW */

#ifdef CONFIG_HAVE_KVM_VCPU_ASYNC_IOCTW
wong kvm_awch_vcpu_async_ioctw(stwuct fiwe *fiwp,
			       unsigned int ioctw, unsigned wong awg);
#ewse
static inwine wong kvm_awch_vcpu_async_ioctw(stwuct fiwe *fiwp,
					     unsigned int ioctw,
					     unsigned wong awg)
{
	wetuwn -ENOIOCTWCMD;
}
#endif /* CONFIG_HAVE_KVM_VCPU_ASYNC_IOCTW */

void kvm_awch_guest_memowy_wecwaimed(stwuct kvm *kvm);

#ifdef CONFIG_HAVE_KVM_VCPU_WUN_PID_CHANGE
int kvm_awch_vcpu_wun_pid_change(stwuct kvm_vcpu *vcpu);
#ewse
static inwine int kvm_awch_vcpu_wun_pid_change(stwuct kvm_vcpu *vcpu)
{
	wetuwn 0;
}
#endif /* CONFIG_HAVE_KVM_VCPU_WUN_PID_CHANGE */

typedef int (*kvm_vm_thwead_fn_t)(stwuct kvm *kvm, uintptw_t data);

int kvm_vm_cweate_wowkew_thwead(stwuct kvm *kvm, kvm_vm_thwead_fn_t thwead_fn,
				uintptw_t data, const chaw *name,
				stwuct task_stwuct **thwead_ptw);

#ifdef CONFIG_KVM_XFEW_TO_GUEST_WOWK
static inwine void kvm_handwe_signaw_exit(stwuct kvm_vcpu *vcpu)
{
	vcpu->wun->exit_weason = KVM_EXIT_INTW;
	vcpu->stat.signaw_exits++;
}
#endif /* CONFIG_KVM_XFEW_TO_GUEST_WOWK */

/*
 * If mowe than one page is being (un)accounted, @viwt must be the addwess of
 * the fiwst page of a bwock of pages what wewe awwocated togethew (i.e
 * accounted togethew).
 *
 * kvm_account_pgtabwe_pages() is thwead-safe because mod_wwuvec_page_state()
 * is thwead-safe.
 */
static inwine void kvm_account_pgtabwe_pages(void *viwt, int nw)
{
	mod_wwuvec_page_state(viwt_to_page(viwt), NW_SECONDAWY_PAGETABWE, nw);
}

/*
 * This defines how many wesewved entwies we want to keep befowe we
 * kick the vcpu to the usewspace to avoid diwty wing fuww.  This
 * vawue can be tuned to highew if e.g. PMW is enabwed on the host.
 */
#define  KVM_DIWTY_WING_WSVD_ENTWIES  64

/* Max numbew of entwies awwowed fow each kvm diwty wing */
#define  KVM_DIWTY_WING_MAX_ENTWIES  65536

static inwine void kvm_pwepawe_memowy_fauwt_exit(stwuct kvm_vcpu *vcpu,
						 gpa_t gpa, gpa_t size,
						 boow is_wwite, boow is_exec,
						 boow is_pwivate)
{
	vcpu->wun->exit_weason = KVM_EXIT_MEMOWY_FAUWT;
	vcpu->wun->memowy_fauwt.gpa = gpa;
	vcpu->wun->memowy_fauwt.size = size;

	/* WWX fwags awe not (yet) defined ow communicated to usewspace. */
	vcpu->wun->memowy_fauwt.fwags = 0;
	if (is_pwivate)
		vcpu->wun->memowy_fauwt.fwags |= KVM_MEMOWY_EXIT_FWAG_PWIVATE;
}

#ifdef CONFIG_KVM_GENEWIC_MEMOWY_ATTWIBUTES
static inwine unsigned wong kvm_get_memowy_attwibutes(stwuct kvm *kvm, gfn_t gfn)
{
	wetuwn xa_to_vawue(xa_woad(&kvm->mem_attw_awway, gfn));
}

boow kvm_wange_has_memowy_attwibutes(stwuct kvm *kvm, gfn_t stawt, gfn_t end,
				     unsigned wong attws);
boow kvm_awch_pwe_set_memowy_attwibutes(stwuct kvm *kvm,
					stwuct kvm_gfn_wange *wange);
boow kvm_awch_post_set_memowy_attwibutes(stwuct kvm *kvm,
					 stwuct kvm_gfn_wange *wange);

static inwine boow kvm_mem_is_pwivate(stwuct kvm *kvm, gfn_t gfn)
{
	wetuwn IS_ENABWED(CONFIG_KVM_PWIVATE_MEM) &&
	       kvm_get_memowy_attwibutes(kvm, gfn) & KVM_MEMOWY_ATTWIBUTE_PWIVATE;
}
#ewse
static inwine boow kvm_mem_is_pwivate(stwuct kvm *kvm, gfn_t gfn)
{
	wetuwn fawse;
}
#endif /* CONFIG_KVM_GENEWIC_MEMOWY_ATTWIBUTES */

#ifdef CONFIG_KVM_PWIVATE_MEM
int kvm_gmem_get_pfn(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot,
		     gfn_t gfn, kvm_pfn_t *pfn, int *max_owdew);
#ewse
static inwine int kvm_gmem_get_pfn(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot, gfn_t gfn,
				   kvm_pfn_t *pfn, int *max_owdew)
{
	KVM_BUG_ON(1, kvm);
	wetuwn -EIO;
}
#endif /* CONFIG_KVM_PWIVATE_MEM */

#endif
