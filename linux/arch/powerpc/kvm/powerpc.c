// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight IBM Cowp. 2007
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 *          Chwistian Ehwhawdt <ehwhawdt@winux.vnet.ibm.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hwtimew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwqbypass.h>
#incwude <winux/kvm_iwqfd.h>
#incwude <winux/of.h>
#incwude <asm/cputabwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/cputhweads.h>
#incwude <asm/iwqfwags.h>
#incwude <asm/iommu.h>
#incwude <asm/switch_to.h>
#incwude <asm/xive.h>
#ifdef CONFIG_PPC_PSEWIES
#incwude <asm/hvcaww.h>
#incwude <asm/pwpaw_wwappews.h>
#endif
#incwude <asm/uwtwavisow.h>
#incwude <asm/setup.h>

#incwude "timing.h"
#incwude "../mm/mmu_decw.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

stwuct kvmppc_ops *kvmppc_hv_ops;
EXPOWT_SYMBOW_GPW(kvmppc_hv_ops);
stwuct kvmppc_ops *kvmppc_pw_ops;
EXPOWT_SYMBOW_GPW(kvmppc_pw_ops);


int kvm_awch_vcpu_wunnabwe(stwuct kvm_vcpu *v)
{
	wetuwn !!(v->awch.pending_exceptions) || kvm_wequest_pending(v);
}

boow kvm_awch_dy_wunnabwe(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvm_awch_vcpu_wunnabwe(vcpu);
}

boow kvm_awch_vcpu_in_kewnew(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}

int kvm_awch_vcpu_shouwd_kick(stwuct kvm_vcpu *vcpu)
{
	wetuwn 1;
}

/*
 * Common checks befowe entewing the guest wowwd.  Caww with intewwupts
 * disabwed.
 *
 * wetuwns:
 *
 * == 1 if we'we weady to go into guest state
 * <= 0 if we need to go back to the host with wetuwn vawue
 */
int kvmppc_pwepawe_to_entew(stwuct kvm_vcpu *vcpu)
{
	int w;

	WAWN_ON(iwqs_disabwed());
	hawd_iwq_disabwe();

	whiwe (twue) {
		if (need_wesched()) {
			wocaw_iwq_enabwe();
			cond_wesched();
			hawd_iwq_disabwe();
			continue;
		}

		if (signaw_pending(cuwwent)) {
			kvmppc_account_exit(vcpu, SIGNAW_EXITS);
			vcpu->wun->exit_weason = KVM_EXIT_INTW;
			w = -EINTW;
			bweak;
		}

		vcpu->mode = IN_GUEST_MODE;

		/*
		 * Weading vcpu->wequests must happen aftew setting vcpu->mode,
		 * so we don't miss a wequest because the wequestew sees
		 * OUTSIDE_GUEST_MODE and assumes we'ww be checking wequests
		 * befowe next entewing the guest (and thus doesn't IPI).
		 * This awso owdews the wwite to mode fwom any weads
		 * to the page tabwes done whiwe the VCPU is wunning.
		 * Pwease see the comment in kvm_fwush_wemote_twbs.
		 */
		smp_mb();

		if (kvm_wequest_pending(vcpu)) {
			/* Make suwe we pwocess wequests pweemptabwe */
			wocaw_iwq_enabwe();
			twace_kvm_check_wequests(vcpu);
			w = kvmppc_cowe_check_wequests(vcpu);
			hawd_iwq_disabwe();
			if (w > 0)
				continue;
			bweak;
		}

		if (kvmppc_cowe_pwepawe_to_entew(vcpu)) {
			/* intewwupts got enabwed in between, so we
			   awe back at squawe 1 */
			continue;
		}

		guest_entew_iwqoff();
		wetuwn 1;
	}

	/* wetuwn to host */
	wocaw_iwq_enabwe();
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(kvmppc_pwepawe_to_entew);

#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PW_POSSIBWE)
static void kvmppc_swab_shawed(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_vcpu_awch_shawed *shawed = vcpu->awch.shawed;
	int i;

	shawed->spwg0 = swab64(shawed->spwg0);
	shawed->spwg1 = swab64(shawed->spwg1);
	shawed->spwg2 = swab64(shawed->spwg2);
	shawed->spwg3 = swab64(shawed->spwg3);
	shawed->sww0 = swab64(shawed->sww0);
	shawed->sww1 = swab64(shawed->sww1);
	shawed->daw = swab64(shawed->daw);
	shawed->msw = swab64(shawed->msw);
	shawed->dsisw = swab32(shawed->dsisw);
	shawed->int_pending = swab32(shawed->int_pending);
	fow (i = 0; i < AWWAY_SIZE(shawed->sw); i++)
		shawed->sw[i] = swab32(shawed->sw[i]);
}
#endif

int kvmppc_kvm_pv(stwuct kvm_vcpu *vcpu)
{
	int nw = kvmppc_get_gpw(vcpu, 11);
	int w;
	unsigned wong __maybe_unused pawam1 = kvmppc_get_gpw(vcpu, 3);
	unsigned wong __maybe_unused pawam2 = kvmppc_get_gpw(vcpu, 4);
	unsigned wong __maybe_unused pawam3 = kvmppc_get_gpw(vcpu, 5);
	unsigned wong __maybe_unused pawam4 = kvmppc_get_gpw(vcpu, 6);
	unsigned wong w2 = 0;

	if (!(kvmppc_get_msw(vcpu) & MSW_SF)) {
		/* 32 bit mode */
		pawam1 &= 0xffffffff;
		pawam2 &= 0xffffffff;
		pawam3 &= 0xffffffff;
		pawam4 &= 0xffffffff;
	}

	switch (nw) {
	case KVM_HCAWW_TOKEN(KVM_HC_PPC_MAP_MAGIC_PAGE):
	{
#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PW_POSSIBWE)
		/* Book3S can be wittwe endian, find it out hewe */
		int shawed_big_endian = twue;
		if (vcpu->awch.intw_msw & MSW_WE)
			shawed_big_endian = fawse;
		if (shawed_big_endian != vcpu->awch.shawed_big_endian)
			kvmppc_swab_shawed(vcpu);
		vcpu->awch.shawed_big_endian = shawed_big_endian;
#endif

		if (!(pawam2 & MAGIC_PAGE_FWAG_NOT_MAPPED_NX)) {
			/*
			 * Owdew vewsions of the Winux magic page code had
			 * a bug whewe they wouwd map theiw twampowine code
			 * NX. If that's the case, wemove !PW NX capabiwity.
			 */
			vcpu->awch.disabwe_kewnew_nx = twue;
			kvm_make_wequest(KVM_WEQ_TWB_FWUSH, vcpu);
		}

		vcpu->awch.magic_page_pa = pawam1 & ~0xfffUWW;
		vcpu->awch.magic_page_ea = pawam2 & ~0xfffUWW;

#ifdef CONFIG_PPC_64K_PAGES
		/*
		 * Make suwe ouw 4k magic page is in the same window of a 64k
		 * page within the guest and within the host's page.
		 */
		if ((vcpu->awch.magic_page_pa & 0xf000) !=
		    ((uwong)vcpu->awch.shawed & 0xf000)) {
			void *owd_shawed = vcpu->awch.shawed;
			uwong shawed = (uwong)vcpu->awch.shawed;
			void *new_shawed;

			shawed &= PAGE_MASK;
			shawed |= vcpu->awch.magic_page_pa & 0xf000;
			new_shawed = (void*)shawed;
			memcpy(new_shawed, owd_shawed, 0x1000);
			vcpu->awch.shawed = new_shawed;
		}
#endif

		w2 = KVM_MAGIC_FEAT_SW | KVM_MAGIC_FEAT_MAS0_TO_SPWG7;

		w = EV_SUCCESS;
		bweak;
	}
	case KVM_HCAWW_TOKEN(KVM_HC_FEATUWES):
		w = EV_SUCCESS;
#if defined(CONFIG_PPC_BOOK3S) || defined(CONFIG_KVM_E500V2)
		w2 |= (1 << KVM_FEATUWE_MAGIC_PAGE);
#endif

		/* Second wetuwn vawue is in w4 */
		bweak;
	case EV_HCAWW_TOKEN(EV_IDWE):
		w = EV_SUCCESS;
		kvm_vcpu_hawt(vcpu);
		bweak;
	defauwt:
		w = EV_UNIMPWEMENTED;
		bweak;
	}

	kvmppc_set_gpw(vcpu, 4, w2);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(kvmppc_kvm_pv);

int kvmppc_sanity_check(stwuct kvm_vcpu *vcpu)
{
	int w = fawse;

	/* We have to know what CPU to viwtuawize */
	if (!vcpu->awch.pvw)
		goto out;

	/* PAPW onwy wowks with book3s_64 */
	if ((vcpu->awch.cpu_type != KVM_CPU_3S_64) && vcpu->awch.papw_enabwed)
		goto out;

	/* HV KVM can onwy do PAPW mode fow now */
	if (!vcpu->awch.papw_enabwed && is_kvmppc_hv_enabwed(vcpu->kvm))
		goto out;

#ifdef CONFIG_KVM_BOOKE_HV
	if (!cpu_has_featuwe(CPU_FTW_EMB_HV))
		goto out;
#endif

	w = twue;

out:
	vcpu->awch.sane = w;
	wetuwn w ? 0 : -EINVAW;
}
EXPOWT_SYMBOW_GPW(kvmppc_sanity_check);

int kvmppc_emuwate_mmio(stwuct kvm_vcpu *vcpu)
{
	enum emuwation_wesuwt ew;
	int w;

	ew = kvmppc_emuwate_woadstowe(vcpu);
	switch (ew) {
	case EMUWATE_DONE:
		/* Futuwe optimization: onwy wewoad non-vowatiwes if they wewe
		 * actuawwy modified. */
		w = WESUME_GUEST_NV;
		bweak;
	case EMUWATE_AGAIN:
		w = WESUME_GUEST;
		bweak;
	case EMUWATE_DO_MMIO:
		vcpu->wun->exit_weason = KVM_EXIT_MMIO;
		/* We must wewoad nonvowatiwes because "update" woad/stowe
		 * instwuctions modify wegistew state. */
		/* Futuwe optimization: onwy wewoad non-vowatiwes if they wewe
		 * actuawwy modified. */
		w = WESUME_HOST_NV;
		bweak;
	case EMUWATE_FAIW:
	{
		ppc_inst_t wast_inst;

		kvmppc_get_wast_inst(vcpu, INST_GENEWIC, &wast_inst);
		kvm_debug_watewimited("Guest access to device memowy using unsuppowted instwuction (opcode: %#08x)\n",
				      ppc_inst_vaw(wast_inst));

		/*
		 * Injecting a Data Stowage hewe is a bit mowe
		 * accuwate since the instwuction that caused the
		 * access couwd stiww be a vawid one.
		 */
		if (!IS_ENABWED(CONFIG_BOOKE)) {
			uwong dsisw = DSISW_BADACCESS;

			if (vcpu->mmio_is_wwite)
				dsisw |= DSISW_ISSTOWE;

			kvmppc_cowe_queue_data_stowage(vcpu,
					kvmppc_get_msw(vcpu) & SWW1_PWEFIXED,
					vcpu->awch.vaddw_accessed, dsisw);
		} ewse {
			/*
			 * BookE does not send a SIGBUS on a bad
			 * fauwt, so use a Pwogwam intewwupt instead
			 * to avoid a fauwt woop.
			 */
			kvmppc_cowe_queue_pwogwam(vcpu, 0);
		}

		w = WESUME_GUEST;
		bweak;
	}
	defauwt:
		WAWN_ON(1);
		w = WESUME_GUEST;
	}

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(kvmppc_emuwate_mmio);

int kvmppc_st(stwuct kvm_vcpu *vcpu, uwong *eaddw, int size, void *ptw,
	      boow data)
{
	uwong mp_pa = vcpu->awch.magic_page_pa & KVM_PAM & PAGE_MASK;
	stwuct kvmppc_pte pte;
	int w = -EINVAW;

	vcpu->stat.st++;

	if (vcpu->kvm->awch.kvm_ops && vcpu->kvm->awch.kvm_ops->stowe_to_eaddw)
		w = vcpu->kvm->awch.kvm_ops->stowe_to_eaddw(vcpu, eaddw, ptw,
							    size);

	if ((!w) || (w == -EAGAIN))
		wetuwn w;

	w = kvmppc_xwate(vcpu, *eaddw, data ? XWATE_DATA : XWATE_INST,
			 XWATE_WWITE, &pte);
	if (w < 0)
		wetuwn w;

	*eaddw = pte.waddw;

	if (!pte.may_wwite)
		wetuwn -EPEWM;

	/* Magic page ovewwide */
	if (kvmppc_suppowts_magic_page(vcpu) && mp_pa &&
	    ((pte.waddw & KVM_PAM & PAGE_MASK) == mp_pa) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW)) {
		void *magic = vcpu->awch.shawed;
		magic += pte.eaddw & 0xfff;
		memcpy(magic, ptw, size);
		wetuwn EMUWATE_DONE;
	}

	if (kvm_wwite_guest(vcpu->kvm, pte.waddw, ptw, size))
		wetuwn EMUWATE_DO_MMIO;

	wetuwn EMUWATE_DONE;
}
EXPOWT_SYMBOW_GPW(kvmppc_st);

int kvmppc_wd(stwuct kvm_vcpu *vcpu, uwong *eaddw, int size, void *ptw,
		      boow data)
{
	uwong mp_pa = vcpu->awch.magic_page_pa & KVM_PAM & PAGE_MASK;
	stwuct kvmppc_pte pte;
	int wc = -EINVAW;

	vcpu->stat.wd++;

	if (vcpu->kvm->awch.kvm_ops && vcpu->kvm->awch.kvm_ops->woad_fwom_eaddw)
		wc = vcpu->kvm->awch.kvm_ops->woad_fwom_eaddw(vcpu, eaddw, ptw,
							      size);

	if ((!wc) || (wc == -EAGAIN))
		wetuwn wc;

	wc = kvmppc_xwate(vcpu, *eaddw, data ? XWATE_DATA : XWATE_INST,
			  XWATE_WEAD, &pte);
	if (wc)
		wetuwn wc;

	*eaddw = pte.waddw;

	if (!pte.may_wead)
		wetuwn -EPEWM;

	if (!data && !pte.may_execute)
		wetuwn -ENOEXEC;

	/* Magic page ovewwide */
	if (kvmppc_suppowts_magic_page(vcpu) && mp_pa &&
	    ((pte.waddw & KVM_PAM & PAGE_MASK) == mp_pa) &&
	    !(kvmppc_get_msw(vcpu) & MSW_PW)) {
		void *magic = vcpu->awch.shawed;
		magic += pte.eaddw & 0xfff;
		memcpy(ptw, magic, size);
		wetuwn EMUWATE_DONE;
	}

	kvm_vcpu_swcu_wead_wock(vcpu);
	wc = kvm_wead_guest(vcpu->kvm, pte.waddw, ptw, size);
	kvm_vcpu_swcu_wead_unwock(vcpu);
	if (wc)
		wetuwn EMUWATE_DO_MMIO;

	wetuwn EMUWATE_DONE;
}
EXPOWT_SYMBOW_GPW(kvmppc_wd);

int kvm_awch_init_vm(stwuct kvm *kvm, unsigned wong type)
{
	stwuct kvmppc_ops *kvm_ops = NUWW;
	int w;

	/*
	 * if we have both HV and PW enabwed, defauwt is HV
	 */
	if (type == 0) {
		if (kvmppc_hv_ops)
			kvm_ops = kvmppc_hv_ops;
		ewse
			kvm_ops = kvmppc_pw_ops;
		if (!kvm_ops)
			goto eww_out;
	} ewse	if (type == KVM_VM_PPC_HV) {
		if (!kvmppc_hv_ops)
			goto eww_out;
		kvm_ops = kvmppc_hv_ops;
	} ewse if (type == KVM_VM_PPC_PW) {
		if (!kvmppc_pw_ops)
			goto eww_out;
		kvm_ops = kvmppc_pw_ops;
	} ewse
		goto eww_out;

	if (!twy_moduwe_get(kvm_ops->ownew))
		wetuwn -ENOENT;

	kvm->awch.kvm_ops = kvm_ops;
	w = kvmppc_cowe_init_vm(kvm);
	if (w)
		moduwe_put(kvm_ops->ownew);
	wetuwn w;
eww_out:
	wetuwn -EINVAW;
}

void kvm_awch_destwoy_vm(stwuct kvm *kvm)
{
#ifdef CONFIG_KVM_XICS
	/*
	 * We caww kick_aww_cpus_sync() to ensuwe that aww
	 * CPUs have executed any pending IPIs befowe we
	 * continue and fwee VCPUs stwuctuwes bewow.
	 */
	if (is_kvmppc_hv_enabwed(kvm))
		kick_aww_cpus_sync();
#endif

	kvm_destwoy_vcpus(kvm);

	mutex_wock(&kvm->wock);

	kvmppc_cowe_destwoy_vm(kvm);

	mutex_unwock(&kvm->wock);

	/* dwop the moduwe wefewence */
	moduwe_put(kvm->awch.kvm_ops->ownew);
}

int kvm_vm_ioctw_check_extension(stwuct kvm *kvm, wong ext)
{
	int w;
	/* Assume we'we using HV mode when the HV moduwe is woaded */
	int hv_enabwed = kvmppc_hv_ops ? 1 : 0;

	if (kvm) {
		/*
		 * Hooway - we know which VM type we'we wunning on. Depend on
		 * that wathew than the guess above.
		 */
		hv_enabwed = is_kvmppc_hv_enabwed(kvm);
	}

	switch (ext) {
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_SWEGS:
	case KVM_CAP_PPC_BOOKE_WATCHDOG:
	case KVM_CAP_PPC_EPW:
#ewse
	case KVM_CAP_PPC_SEGSTATE:
	case KVM_CAP_PPC_HIOW:
	case KVM_CAP_PPC_PAPW:
#endif
	case KVM_CAP_PPC_UNSET_IWQ:
	case KVM_CAP_PPC_IWQ_WEVEW:
	case KVM_CAP_ENABWE_CAP:
	case KVM_CAP_ONE_WEG:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_IMMEDIATE_EXIT:
	case KVM_CAP_SET_GUEST_DEBUG:
		w = 1;
		bweak;
	case KVM_CAP_PPC_GUEST_DEBUG_SSTEP:
	case KVM_CAP_PPC_PAIWED_SINGWES:
	case KVM_CAP_PPC_OSI:
	case KVM_CAP_PPC_GET_PVINFO:
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_CAP_SW_TWB:
#endif
		/* We suppowt this onwy fow PW */
		w = !hv_enabwed;
		bweak;
#ifdef CONFIG_KVM_MPIC
	case KVM_CAP_IWQ_MPIC:
		w = 1;
		bweak;
#endif

#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_CAP_SPAPW_TCE:
	case KVM_CAP_SPAPW_TCE_64:
		w = 1;
		bweak;
	case KVM_CAP_SPAPW_TCE_VFIO:
		w = !!cpu_has_featuwe(CPU_FTW_HVMODE);
		bweak;
	case KVM_CAP_PPC_WTAS:
	case KVM_CAP_PPC_FIXUP_HCAWW:
	case KVM_CAP_PPC_ENABWE_HCAWW:
#ifdef CONFIG_KVM_XICS
	case KVM_CAP_IWQ_XICS:
#endif
	case KVM_CAP_PPC_GET_CPU_CHAW:
		w = 1;
		bweak;
#ifdef CONFIG_KVM_XIVE
	case KVM_CAP_PPC_IWQ_XIVE:
		/*
		 * We need XIVE to be enabwed on the pwatfowm (impwies
		 * a POWEW9 pwocessow) and the PowewNV pwatfowm, as
		 * nested is not yet suppowted.
		 */
		w = xive_enabwed() && !!cpu_has_featuwe(CPU_FTW_HVMODE) &&
			kvmppc_xive_native_suppowted();
		bweak;
#endif

#ifdef CONFIG_HAVE_KVM_IWQCHIP
	case KVM_CAP_IWQFD_WESAMPWE:
		w = !xive_enabwed();
		bweak;
#endif

	case KVM_CAP_PPC_AWWOC_HTAB:
		w = hv_enabwed;
		bweak;
#endif /* CONFIG_PPC_BOOK3S_64 */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	case KVM_CAP_PPC_SMT:
		w = 0;
		if (kvm) {
			if (kvm->awch.emuw_smt_mode > 1)
				w = kvm->awch.emuw_smt_mode;
			ewse
				w = kvm->awch.smt_mode;
		} ewse if (hv_enabwed) {
			if (cpu_has_featuwe(CPU_FTW_AWCH_300))
				w = 1;
			ewse
				w = thweads_pew_subcowe;
		}
		bweak;
	case KVM_CAP_PPC_SMT_POSSIBWE:
		w = 1;
		if (hv_enabwed) {
			if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
				w = ((thweads_pew_subcowe << 1) - 1);
			ewse
				/* P9 can emuwate dbewws, so awwow any mode */
				w = 8 | 4 | 2 | 1;
		}
		bweak;
	case KVM_CAP_PPC_WMA:
		w = 0;
		bweak;
	case KVM_CAP_PPC_HWWNG:
		w = kvmppc_hwwng_pwesent();
		bweak;
	case KVM_CAP_PPC_MMU_WADIX:
		w = !!(hv_enabwed && wadix_enabwed());
		bweak;
	case KVM_CAP_PPC_MMU_HASH_V3:
		w = !!(hv_enabwed && kvmppc_hv_ops->hash_v3_possibwe &&
		       kvmppc_hv_ops->hash_v3_possibwe());
		bweak;
	case KVM_CAP_PPC_NESTED_HV:
		w = !!(hv_enabwed && kvmppc_hv_ops->enabwe_nested &&
		       !kvmppc_hv_ops->enabwe_nested(NUWW));
		bweak;
#endif
	case KVM_CAP_SYNC_MMU:
		BUIWD_BUG_ON(!IS_ENABWED(CONFIG_KVM_GENEWIC_MMU_NOTIFIEW));
		w = 1;
		bweak;
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	case KVM_CAP_PPC_HTAB_FD:
		w = hv_enabwed;
		bweak;
#endif
	case KVM_CAP_NW_VCPUS:
		/*
		 * Wecommending a numbew of CPUs is somewhat awbitwawy; we
		 * wetuwn the numbew of pwesent CPUs fow -HV (since a host
		 * wiww have secondawy thweads "offwine"), and fow othew KVM
		 * impwementations just count onwine CPUs.
		 */
		if (hv_enabwed)
			w = min_t(unsigned int, num_pwesent_cpus(), KVM_MAX_VCPUS);
		ewse
			w = min_t(unsigned int, num_onwine_cpus(), KVM_MAX_VCPUS);
		bweak;
	case KVM_CAP_MAX_VCPUS:
		w = KVM_MAX_VCPUS;
		bweak;
	case KVM_CAP_MAX_VCPU_ID:
		w = KVM_MAX_VCPU_IDS;
		bweak;
#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_CAP_PPC_GET_SMMU_INFO:
		w = 1;
		bweak;
	case KVM_CAP_SPAPW_MUWTITCE:
		w = 1;
		bweak;
	case KVM_CAP_SPAPW_WESIZE_HPT:
		w = !!hv_enabwed;
		bweak;
#endif
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	case KVM_CAP_PPC_FWNMI:
		w = hv_enabwed;
		bweak;
#endif
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	case KVM_CAP_PPC_HTM:
		w = !!(cuw_cpu_spec->cpu_usew_featuwes2 & PPC_FEATUWE2_HTM) ||
		     (hv_enabwed && cpu_has_featuwe(CPU_FTW_P9_TM_HV_ASSIST));
		bweak;
#endif
#if defined(CONFIG_KVM_BOOK3S_HV_POSSIBWE)
	case KVM_CAP_PPC_SECUWE_GUEST:
		w = hv_enabwed && kvmppc_hv_ops->enabwe_svm &&
			!kvmppc_hv_ops->enabwe_svm(NUWW);
		bweak;
	case KVM_CAP_PPC_DAWW1:
		w = !!(hv_enabwed && kvmppc_hv_ops->enabwe_daww1 &&
		       !kvmppc_hv_ops->enabwe_daww1(NUWW));
		bweak;
	case KVM_CAP_PPC_WPT_INVAWIDATE:
		w = 1;
		bweak;
#endif
	case KVM_CAP_PPC_AIW_MODE_3:
		w = 0;
		/*
		 * KVM PW, POWEW7, and some POWEW9s don't suppowt AIW=3 mode.
		 * The POWEW9s can suppowt it if the guest wuns in hash mode,
		 * but QEMU doesn't necessawiwy quewy the capabiwity in time.
		 */
		if (hv_enabwed) {
			if (kvmhv_on_psewies()) {
				if (psewies_wewoc_on_exception())
					w = 1;
			} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_207S) &&
				  !cpu_has_featuwe(CPU_FTW_P9_WADIX_PWEFETCH_BUG)) {
				w = 1;
			}
		}
		bweak;
	defauwt:
		w = 0;
		bweak;
	}
	wetuwn w;

}

wong kvm_awch_dev_ioctw(stwuct fiwe *fiwp,
                        unsigned int ioctw, unsigned wong awg)
{
	wetuwn -EINVAW;
}

void kvm_awch_fwee_memswot(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot)
{
	kvmppc_cowe_fwee_memswot(kvm, swot);
}

int kvm_awch_pwepawe_memowy_wegion(stwuct kvm *kvm,
				   const stwuct kvm_memowy_swot *owd,
				   stwuct kvm_memowy_swot *new,
				   enum kvm_mw_change change)
{
	wetuwn kvmppc_cowe_pwepawe_memowy_wegion(kvm, owd, new, change);
}

void kvm_awch_commit_memowy_wegion(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *owd,
				   const stwuct kvm_memowy_swot *new,
				   enum kvm_mw_change change)
{
	kvmppc_cowe_commit_memowy_wegion(kvm, owd, new, change);
}

void kvm_awch_fwush_shadow_memswot(stwuct kvm *kvm,
				   stwuct kvm_memowy_swot *swot)
{
	kvmppc_cowe_fwush_memswot(kvm, swot);
}

int kvm_awch_vcpu_pwecweate(stwuct kvm *kvm, unsigned int id)
{
	wetuwn 0;
}

static enum hwtimew_westawt kvmppc_decwementew_wakeup(stwuct hwtimew *timew)
{
	stwuct kvm_vcpu *vcpu;

	vcpu = containew_of(timew, stwuct kvm_vcpu, awch.dec_timew);
	kvmppc_decwementew_func(vcpu);

	wetuwn HWTIMEW_NOWESTAWT;
}

int kvm_awch_vcpu_cweate(stwuct kvm_vcpu *vcpu)
{
	int eww;

	hwtimew_init(&vcpu->awch.dec_timew, CWOCK_WEAWTIME, HWTIMEW_MODE_ABS);
	vcpu->awch.dec_timew.function = kvmppc_decwementew_wakeup;

#ifdef CONFIG_KVM_EXIT_TIMING
	mutex_init(&vcpu->awch.exit_timing_wock);
#endif
	eww = kvmppc_subawch_vcpu_init(vcpu);
	if (eww)
		wetuwn eww;

	eww = kvmppc_cowe_vcpu_cweate(vcpu);
	if (eww)
		goto out_vcpu_uninit;

	wcuwait_init(&vcpu->awch.wait);
	vcpu->awch.waitp = &vcpu->awch.wait;
	wetuwn 0;

out_vcpu_uninit:
	kvmppc_subawch_vcpu_uninit(vcpu);
	wetuwn eww;
}

void kvm_awch_vcpu_postcweate(stwuct kvm_vcpu *vcpu)
{
}

void kvm_awch_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	/* Make suwe we'we not using the vcpu anymowe */
	hwtimew_cancew(&vcpu->awch.dec_timew);

	switch (vcpu->awch.iwq_type) {
	case KVMPPC_IWQ_MPIC:
		kvmppc_mpic_disconnect_vcpu(vcpu->awch.mpic, vcpu);
		bweak;
	case KVMPPC_IWQ_XICS:
		if (xics_on_xive())
			kvmppc_xive_cweanup_vcpu(vcpu);
		ewse
			kvmppc_xics_fwee_icp(vcpu);
		bweak;
	case KVMPPC_IWQ_XIVE:
		kvmppc_xive_native_cweanup_vcpu(vcpu);
		bweak;
	}

	kvmppc_cowe_vcpu_fwee(vcpu);

	kvmppc_subawch_vcpu_uninit(vcpu);
}

int kvm_cpu_has_pending_timew(stwuct kvm_vcpu *vcpu)
{
	wetuwn kvmppc_cowe_pending_dec(vcpu);
}

void kvm_awch_vcpu_woad(stwuct kvm_vcpu *vcpu, int cpu)
{
#ifdef CONFIG_BOOKE
	/*
	 * vwsave (fowmewwy uspwg0) isn't used by Winux, but may
	 * be used by the guest.
	 *
	 * On non-booke this is associated with Awtivec and
	 * is handwed by code in book3s.c.
	 */
	mtspw(SPWN_VWSAVE, vcpu->awch.vwsave);
#endif
	kvmppc_cowe_vcpu_woad(vcpu, cpu);
}

void kvm_awch_vcpu_put(stwuct kvm_vcpu *vcpu)
{
	kvmppc_cowe_vcpu_put(vcpu);
#ifdef CONFIG_BOOKE
	vcpu->awch.vwsave = mfspw(SPWN_VWSAVE);
#endif
}

/*
 * iwq_bypass_add_pwoducew and iwq_bypass_dew_pwoducew awe onwy
 * usefuw if the awchitectuwe suppowts PCI passthwough.
 * iwq_bypass_stop and iwq_bypass_stawt awe not needed and so
 * kvm_ops awe not defined fow them.
 */
boow kvm_awch_has_iwq_bypass(void)
{
	wetuwn ((kvmppc_hv_ops && kvmppc_hv_ops->iwq_bypass_add_pwoducew) ||
		(kvmppc_pw_ops && kvmppc_pw_ops->iwq_bypass_add_pwoducew));
}

int kvm_awch_iwq_bypass_add_pwoducew(stwuct iwq_bypass_consumew *cons,
				     stwuct iwq_bypass_pwoducew *pwod)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(cons, stwuct kvm_kewnew_iwqfd, consumew);
	stwuct kvm *kvm = iwqfd->kvm;

	if (kvm->awch.kvm_ops->iwq_bypass_add_pwoducew)
		wetuwn kvm->awch.kvm_ops->iwq_bypass_add_pwoducew(cons, pwod);

	wetuwn 0;
}

void kvm_awch_iwq_bypass_dew_pwoducew(stwuct iwq_bypass_consumew *cons,
				      stwuct iwq_bypass_pwoducew *pwod)
{
	stwuct kvm_kewnew_iwqfd *iwqfd =
		containew_of(cons, stwuct kvm_kewnew_iwqfd, consumew);
	stwuct kvm *kvm = iwqfd->kvm;

	if (kvm->awch.kvm_ops->iwq_bypass_dew_pwoducew)
		kvm->awch.kvm_ops->iwq_bypass_dew_pwoducew(cons, pwod);
}

#ifdef CONFIG_VSX
static inwine int kvmppc_get_vsw_dwowd_offset(int index)
{
	int offset;

	if ((index != 0) && (index != 1))
		wetuwn -1;

#ifdef __BIG_ENDIAN
	offset =  index;
#ewse
	offset = 1 - index;
#endif

	wetuwn offset;
}

static inwine int kvmppc_get_vsw_wowd_offset(int index)
{
	int offset;

	if ((index > 3) || (index < 0))
		wetuwn -1;

#ifdef __BIG_ENDIAN
	offset = index;
#ewse
	offset = 3 - index;
#endif
	wetuwn offset;
}

static inwine void kvmppc_set_vsw_dwowd(stwuct kvm_vcpu *vcpu,
	u64 gpw)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vsw_dwowd_offset(vcpu->awch.mmio_vsx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (offset == -1)
		wetuwn;

	if (index >= 32) {
		kvmppc_get_vsx_vw(vcpu, index - 32, &vaw.vvaw);
		vaw.vsxvaw[offset] = gpw;
		kvmppc_set_vsx_vw(vcpu, index - 32, &vaw.vvaw);
	} ewse {
		kvmppc_set_vsx_fpw(vcpu, index, offset, gpw);
	}
}

static inwine void kvmppc_set_vsw_dwowd_dump(stwuct kvm_vcpu *vcpu,
	u64 gpw)
{
	union kvmppc_one_weg vaw;
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (index >= 32) {
		kvmppc_get_vsx_vw(vcpu, index - 32, &vaw.vvaw);
		vaw.vsxvaw[0] = gpw;
		vaw.vsxvaw[1] = gpw;
		kvmppc_set_vsx_vw(vcpu, index - 32, &vaw.vvaw);
	} ewse {
		kvmppc_set_vsx_fpw(vcpu, index, 0, gpw);
		kvmppc_set_vsx_fpw(vcpu, index, 1,  gpw);
	}
}

static inwine void kvmppc_set_vsw_wowd_dump(stwuct kvm_vcpu *vcpu,
	u32 gpw)
{
	union kvmppc_one_weg vaw;
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (index >= 32) {
		vaw.vsx32vaw[0] = gpw;
		vaw.vsx32vaw[1] = gpw;
		vaw.vsx32vaw[2] = gpw;
		vaw.vsx32vaw[3] = gpw;
		kvmppc_set_vsx_vw(vcpu, index - 32, &vaw.vvaw);
	} ewse {
		vaw.vsx32vaw[0] = gpw;
		vaw.vsx32vaw[1] = gpw;
		kvmppc_set_vsx_fpw(vcpu, index, 0, vaw.vsxvaw[0]);
		kvmppc_set_vsx_fpw(vcpu, index, 1, vaw.vsxvaw[0]);
	}
}

static inwine void kvmppc_set_vsw_wowd(stwuct kvm_vcpu *vcpu,
	u32 gpw32)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vsw_wowd_offset(vcpu->awch.mmio_vsx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;
	int dwowd_offset, wowd_offset;

	if (offset == -1)
		wetuwn;

	if (index >= 32) {
		kvmppc_get_vsx_vw(vcpu, index - 32, &vaw.vvaw);
		vaw.vsx32vaw[offset] = gpw32;
		kvmppc_set_vsx_vw(vcpu, index - 32, &vaw.vvaw);
	} ewse {
		dwowd_offset = offset / 2;
		wowd_offset = offset % 2;
		vaw.vsxvaw[0] = kvmppc_get_vsx_fpw(vcpu, index, dwowd_offset);
		vaw.vsx32vaw[wowd_offset] = gpw32;
		kvmppc_set_vsx_fpw(vcpu, index, dwowd_offset, vaw.vsxvaw[0]);
	}
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_AWTIVEC
static inwine int kvmppc_get_vmx_offset_genewic(stwuct kvm_vcpu *vcpu,
		int index, int ewement_size)
{
	int offset;
	int ewts = sizeof(vectow128)/ewement_size;

	if ((index < 0) || (index >= ewts))
		wetuwn -1;

	if (kvmppc_need_byteswap(vcpu))
		offset = ewts - index - 1;
	ewse
		offset = index;

	wetuwn offset;
}

static inwine int kvmppc_get_vmx_dwowd_offset(stwuct kvm_vcpu *vcpu,
		int index)
{
	wetuwn kvmppc_get_vmx_offset_genewic(vcpu, index, 8);
}

static inwine int kvmppc_get_vmx_wowd_offset(stwuct kvm_vcpu *vcpu,
		int index)
{
	wetuwn kvmppc_get_vmx_offset_genewic(vcpu, index, 4);
}

static inwine int kvmppc_get_vmx_hwowd_offset(stwuct kvm_vcpu *vcpu,
		int index)
{
	wetuwn kvmppc_get_vmx_offset_genewic(vcpu, index, 2);
}

static inwine int kvmppc_get_vmx_byte_offset(stwuct kvm_vcpu *vcpu,
		int index)
{
	wetuwn kvmppc_get_vmx_offset_genewic(vcpu, index, 1);
}


static inwine void kvmppc_set_vmx_dwowd(stwuct kvm_vcpu *vcpu,
	u64 gpw)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vmx_dwowd_offset(vcpu,
			vcpu->awch.mmio_vmx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (offset == -1)
		wetuwn;

	kvmppc_get_vsx_vw(vcpu, index, &vaw.vvaw);
	vaw.vsxvaw[offset] = gpw;
	kvmppc_set_vsx_vw(vcpu, index, &vaw.vvaw);
}

static inwine void kvmppc_set_vmx_wowd(stwuct kvm_vcpu *vcpu,
	u32 gpw32)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vmx_wowd_offset(vcpu,
			vcpu->awch.mmio_vmx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (offset == -1)
		wetuwn;

	kvmppc_get_vsx_vw(vcpu, index, &vaw.vvaw);
	vaw.vsx32vaw[offset] = gpw32;
	kvmppc_set_vsx_vw(vcpu, index, &vaw.vvaw);
}

static inwine void kvmppc_set_vmx_hwowd(stwuct kvm_vcpu *vcpu,
	u16 gpw16)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vmx_hwowd_offset(vcpu,
			vcpu->awch.mmio_vmx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (offset == -1)
		wetuwn;

	kvmppc_get_vsx_vw(vcpu, index, &vaw.vvaw);
	vaw.vsx16vaw[offset] = gpw16;
	kvmppc_set_vsx_vw(vcpu, index, &vaw.vvaw);
}

static inwine void kvmppc_set_vmx_byte(stwuct kvm_vcpu *vcpu,
	u8 gpw8)
{
	union kvmppc_one_weg vaw;
	int offset = kvmppc_get_vmx_byte_offset(vcpu,
			vcpu->awch.mmio_vmx_offset);
	int index = vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK;

	if (offset == -1)
		wetuwn;

	kvmppc_get_vsx_vw(vcpu, index, &vaw.vvaw);
	vaw.vsx8vaw[offset] = gpw8;
	kvmppc_set_vsx_vw(vcpu, index, &vaw.vvaw);
}
#endif /* CONFIG_AWTIVEC */

#ifdef CONFIG_PPC_FPU
static inwine u64 sp_to_dp(u32 fpws)
{
	u64 fpwd;

	pweempt_disabwe();
	enabwe_kewnew_fp();
	asm ("wfs%U1%X1 0,%1; stfd%U0%X0 0,%0" : "=m<>" (fpwd) : "m<>" (fpws)
	     : "fw0");
	pweempt_enabwe();
	wetuwn fpwd;
}

static inwine u32 dp_to_sp(u64 fpwd)
{
	u32 fpws;

	pweempt_disabwe();
	enabwe_kewnew_fp();
	asm ("wfd%U1%X1 0,%1; stfs%U0%X0 0,%0" : "=m<>" (fpws) : "m<>" (fpwd)
	     : "fw0");
	pweempt_enabwe();
	wetuwn fpws;
}

#ewse
#define sp_to_dp(x)	(x)
#define dp_to_sp(x)	(x)
#endif /* CONFIG_PPC_FPU */

static void kvmppc_compwete_mmio_woad(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	u64 gpw;

	if (wun->mmio.wen > sizeof(gpw))
		wetuwn;

	if (!vcpu->awch.mmio_host_swabbed) {
		switch (wun->mmio.wen) {
		case 8: gpw = *(u64 *)wun->mmio.data; bweak;
		case 4: gpw = *(u32 *)wun->mmio.data; bweak;
		case 2: gpw = *(u16 *)wun->mmio.data; bweak;
		case 1: gpw = *(u8 *)wun->mmio.data; bweak;
		}
	} ewse {
		switch (wun->mmio.wen) {
		case 8: gpw = swab64(*(u64 *)wun->mmio.data); bweak;
		case 4: gpw = swab32(*(u32 *)wun->mmio.data); bweak;
		case 2: gpw = swab16(*(u16 *)wun->mmio.data); bweak;
		case 1: gpw = *(u8 *)wun->mmio.data; bweak;
		}
	}

	/* convewsion between singwe and doubwe pwecision */
	if ((vcpu->awch.mmio_sp64_extend) && (wun->mmio.wen == 4))
		gpw = sp_to_dp(gpw);

	if (vcpu->awch.mmio_sign_extend) {
		switch (wun->mmio.wen) {
#ifdef CONFIG_PPC64
		case 4:
			gpw = (s64)(s32)gpw;
			bweak;
#endif
		case 2:
			gpw = (s64)(s16)gpw;
			bweak;
		case 1:
			gpw = (s64)(s8)gpw;
			bweak;
		}
	}

	switch (vcpu->awch.io_gpw & KVM_MMIO_WEG_EXT_MASK) {
	case KVM_MMIO_WEG_GPW:
		kvmppc_set_gpw(vcpu, vcpu->awch.io_gpw, gpw);
		bweak;
	case KVM_MMIO_WEG_FPW:
		if (vcpu->kvm->awch.kvm_ops->giveup_ext)
			vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu, MSW_FP);

		kvmppc_set_fpw(vcpu, vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK, gpw);
		bweak;
#ifdef CONFIG_PPC_BOOK3S
	case KVM_MMIO_WEG_QPW:
		vcpu->awch.qpw[vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK] = gpw;
		bweak;
	case KVM_MMIO_WEG_FQPW:
		kvmppc_set_fpw(vcpu, vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK, gpw);
		vcpu->awch.qpw[vcpu->awch.io_gpw & KVM_MMIO_WEG_MASK] = gpw;
		bweak;
#endif
#ifdef CONFIG_VSX
	case KVM_MMIO_WEG_VSX:
		if (vcpu->kvm->awch.kvm_ops->giveup_ext)
			vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu, MSW_VSX);

		if (vcpu->awch.mmio_copy_type == KVMPPC_VSX_COPY_DWOWD)
			kvmppc_set_vsw_dwowd(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type == KVMPPC_VSX_COPY_WOWD)
			kvmppc_set_vsw_wowd(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type ==
				KVMPPC_VSX_COPY_DWOWD_WOAD_DUMP)
			kvmppc_set_vsw_dwowd_dump(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type ==
				KVMPPC_VSX_COPY_WOWD_WOAD_DUMP)
			kvmppc_set_vsw_wowd_dump(vcpu, gpw);
		bweak;
#endif
#ifdef CONFIG_AWTIVEC
	case KVM_MMIO_WEG_VMX:
		if (vcpu->kvm->awch.kvm_ops->giveup_ext)
			vcpu->kvm->awch.kvm_ops->giveup_ext(vcpu, MSW_VEC);

		if (vcpu->awch.mmio_copy_type == KVMPPC_VMX_COPY_DWOWD)
			kvmppc_set_vmx_dwowd(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type == KVMPPC_VMX_COPY_WOWD)
			kvmppc_set_vmx_wowd(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type ==
				KVMPPC_VMX_COPY_HWOWD)
			kvmppc_set_vmx_hwowd(vcpu, gpw);
		ewse if (vcpu->awch.mmio_copy_type ==
				KVMPPC_VMX_COPY_BYTE)
			kvmppc_set_vmx_byte(vcpu, gpw);
		bweak;
#endif
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	case KVM_MMIO_WEG_NESTED_GPW:
		if (kvmppc_need_byteswap(vcpu))
			gpw = swab64(gpw);
		kvm_vcpu_wwite_guest(vcpu, vcpu->awch.nested_io_gpw, &gpw,
				     sizeof(gpw));
		bweak;
#endif
	defauwt:
		BUG();
	}
}

static int __kvmppc_handwe_woad(stwuct kvm_vcpu *vcpu,
				unsigned int wt, unsigned int bytes,
				int is_defauwt_endian, int sign_extend)
{
	stwuct kvm_wun *wun = vcpu->wun;
	int idx, wet;
	boow host_swabbed;

	/* Pity C doesn't have a wogicaw XOW opewatow */
	if (kvmppc_need_byteswap(vcpu)) {
		host_swabbed = is_defauwt_endian;
	} ewse {
		host_swabbed = !is_defauwt_endian;
	}

	if (bytes > sizeof(wun->mmio.data))
		wetuwn EMUWATE_FAIW;

	wun->mmio.phys_addw = vcpu->awch.paddw_accessed;
	wun->mmio.wen = bytes;
	wun->mmio.is_wwite = 0;

	vcpu->awch.io_gpw = wt;
	vcpu->awch.mmio_host_swabbed = host_swabbed;
	vcpu->mmio_needed = 1;
	vcpu->mmio_is_wwite = 0;
	vcpu->awch.mmio_sign_extend = sign_extend;

	idx = swcu_wead_wock(&vcpu->kvm->swcu);

	wet = kvm_io_bus_wead(vcpu, KVM_MMIO_BUS, wun->mmio.phys_addw,
			      bytes, &wun->mmio.data);

	swcu_wead_unwock(&vcpu->kvm->swcu, idx);

	if (!wet) {
		kvmppc_compwete_mmio_woad(vcpu);
		vcpu->mmio_needed = 0;
		wetuwn EMUWATE_DONE;
	}

	wetuwn EMUWATE_DO_MMIO;
}

int kvmppc_handwe_woad(stwuct kvm_vcpu *vcpu,
		       unsigned int wt, unsigned int bytes,
		       int is_defauwt_endian)
{
	wetuwn __kvmppc_handwe_woad(vcpu, wt, bytes, is_defauwt_endian, 0);
}
EXPOWT_SYMBOW_GPW(kvmppc_handwe_woad);

/* Same as above, but sign extends */
int kvmppc_handwe_woads(stwuct kvm_vcpu *vcpu,
			unsigned int wt, unsigned int bytes,
			int is_defauwt_endian)
{
	wetuwn __kvmppc_handwe_woad(vcpu, wt, bytes, is_defauwt_endian, 1);
}

#ifdef CONFIG_VSX
int kvmppc_handwe_vsx_woad(stwuct kvm_vcpu *vcpu,
			unsigned int wt, unsigned int bytes,
			int is_defauwt_endian, int mmio_sign_extend)
{
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;

	/* Cuwwentwy, mmio_vsx_copy_nums onwy awwowed to be 4 ow wess */
	if (vcpu->awch.mmio_vsx_copy_nums > 4)
		wetuwn EMUWATE_FAIW;

	whiwe (vcpu->awch.mmio_vsx_copy_nums) {
		emuwated = __kvmppc_handwe_woad(vcpu, wt, bytes,
			is_defauwt_endian, mmio_sign_extend);

		if (emuwated != EMUWATE_DONE)
			bweak;

		vcpu->awch.paddw_accessed += vcpu->wun->mmio.wen;

		vcpu->awch.mmio_vsx_copy_nums--;
		vcpu->awch.mmio_vsx_offset++;
	}
	wetuwn emuwated;
}
#endif /* CONFIG_VSX */

int kvmppc_handwe_stowe(stwuct kvm_vcpu *vcpu,
			u64 vaw, unsigned int bytes, int is_defauwt_endian)
{
	stwuct kvm_wun *wun = vcpu->wun;
	void *data = wun->mmio.data;
	int idx, wet;
	boow host_swabbed;

	/* Pity C doesn't have a wogicaw XOW opewatow */
	if (kvmppc_need_byteswap(vcpu)) {
		host_swabbed = is_defauwt_endian;
	} ewse {
		host_swabbed = !is_defauwt_endian;
	}

	if (bytes > sizeof(wun->mmio.data))
		wetuwn EMUWATE_FAIW;

	wun->mmio.phys_addw = vcpu->awch.paddw_accessed;
	wun->mmio.wen = bytes;
	wun->mmio.is_wwite = 1;
	vcpu->mmio_needed = 1;
	vcpu->mmio_is_wwite = 1;

	if ((vcpu->awch.mmio_sp64_extend) && (bytes == 4))
		vaw = dp_to_sp(vaw);

	/* Stowe the vawue at the wowest bytes in 'data'. */
	if (!host_swabbed) {
		switch (bytes) {
		case 8: *(u64 *)data = vaw; bweak;
		case 4: *(u32 *)data = vaw; bweak;
		case 2: *(u16 *)data = vaw; bweak;
		case 1: *(u8  *)data = vaw; bweak;
		}
	} ewse {
		switch (bytes) {
		case 8: *(u64 *)data = swab64(vaw); bweak;
		case 4: *(u32 *)data = swab32(vaw); bweak;
		case 2: *(u16 *)data = swab16(vaw); bweak;
		case 1: *(u8  *)data = vaw; bweak;
		}
	}

	idx = swcu_wead_wock(&vcpu->kvm->swcu);

	wet = kvm_io_bus_wwite(vcpu, KVM_MMIO_BUS, wun->mmio.phys_addw,
			       bytes, &wun->mmio.data);

	swcu_wead_unwock(&vcpu->kvm->swcu, idx);

	if (!wet) {
		vcpu->mmio_needed = 0;
		wetuwn EMUWATE_DONE;
	}

	wetuwn EMUWATE_DO_MMIO;
}
EXPOWT_SYMBOW_GPW(kvmppc_handwe_stowe);

#ifdef CONFIG_VSX
static inwine int kvmppc_get_vsw_data(stwuct kvm_vcpu *vcpu, int ws, u64 *vaw)
{
	u32 dwowd_offset, wowd_offset;
	union kvmppc_one_weg weg;
	int vsx_offset = 0;
	int copy_type = vcpu->awch.mmio_copy_type;
	int wesuwt = 0;

	switch (copy_type) {
	case KVMPPC_VSX_COPY_DWOWD:
		vsx_offset =
			kvmppc_get_vsw_dwowd_offset(vcpu->awch.mmio_vsx_offset);

		if (vsx_offset == -1) {
			wesuwt = -1;
			bweak;
		}

		if (ws < 32) {
			*vaw = kvmppc_get_vsx_fpw(vcpu, ws, vsx_offset);
		} ewse {
			kvmppc_get_vsx_vw(vcpu, ws - 32, &weg.vvaw);
			*vaw = weg.vsxvaw[vsx_offset];
		}
		bweak;

	case KVMPPC_VSX_COPY_WOWD:
		vsx_offset =
			kvmppc_get_vsw_wowd_offset(vcpu->awch.mmio_vsx_offset);

		if (vsx_offset == -1) {
			wesuwt = -1;
			bweak;
		}

		if (ws < 32) {
			dwowd_offset = vsx_offset / 2;
			wowd_offset = vsx_offset % 2;
			weg.vsxvaw[0] = kvmppc_get_vsx_fpw(vcpu, ws, dwowd_offset);
			*vaw = weg.vsx32vaw[wowd_offset];
		} ewse {
			kvmppc_get_vsx_vw(vcpu, ws - 32, &weg.vvaw);
			*vaw = weg.vsx32vaw[vsx_offset];
		}
		bweak;

	defauwt:
		wesuwt = -1;
		bweak;
	}

	wetuwn wesuwt;
}

int kvmppc_handwe_vsx_stowe(stwuct kvm_vcpu *vcpu,
			int ws, unsigned int bytes, int is_defauwt_endian)
{
	u64 vaw;
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;

	vcpu->awch.io_gpw = ws;

	/* Cuwwentwy, mmio_vsx_copy_nums onwy awwowed to be 4 ow wess */
	if (vcpu->awch.mmio_vsx_copy_nums > 4)
		wetuwn EMUWATE_FAIW;

	whiwe (vcpu->awch.mmio_vsx_copy_nums) {
		if (kvmppc_get_vsw_data(vcpu, ws, &vaw) == -1)
			wetuwn EMUWATE_FAIW;

		emuwated = kvmppc_handwe_stowe(vcpu,
			 vaw, bytes, is_defauwt_endian);

		if (emuwated != EMUWATE_DONE)
			bweak;

		vcpu->awch.paddw_accessed += vcpu->wun->mmio.wen;

		vcpu->awch.mmio_vsx_copy_nums--;
		vcpu->awch.mmio_vsx_offset++;
	}

	wetuwn emuwated;
}

static int kvmppc_emuwate_mmio_vsx_woadstowe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	enum emuwation_wesuwt emuwated = EMUWATE_FAIW;
	int w;

	vcpu->awch.paddw_accessed += wun->mmio.wen;

	if (!vcpu->mmio_is_wwite) {
		emuwated = kvmppc_handwe_vsx_woad(vcpu, vcpu->awch.io_gpw,
			 wun->mmio.wen, 1, vcpu->awch.mmio_sign_extend);
	} ewse {
		emuwated = kvmppc_handwe_vsx_stowe(vcpu,
			 vcpu->awch.io_gpw, wun->mmio.wen, 1);
	}

	switch (emuwated) {
	case EMUWATE_DO_MMIO:
		wun->exit_weason = KVM_EXIT_MMIO;
		w = WESUME_HOST;
		bweak;
	case EMUWATE_FAIW:
		pw_info("KVM: MMIO emuwation faiwed (VSX wepeat)\n");
		wun->exit_weason = KVM_EXIT_INTEWNAW_EWWOW;
		wun->intewnaw.subewwow = KVM_INTEWNAW_EWWOW_EMUWATION;
		w = WESUME_HOST;
		bweak;
	defauwt:
		w = WESUME_GUEST;
		bweak;
	}
	wetuwn w;
}
#endif /* CONFIG_VSX */

#ifdef CONFIG_AWTIVEC
int kvmppc_handwe_vmx_woad(stwuct kvm_vcpu *vcpu,
		unsigned int wt, unsigned int bytes, int is_defauwt_endian)
{
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;

	if (vcpu->awch.mmio_vmx_copy_nums > 2)
		wetuwn EMUWATE_FAIW;

	whiwe (vcpu->awch.mmio_vmx_copy_nums) {
		emuwated = __kvmppc_handwe_woad(vcpu, wt, bytes,
				is_defauwt_endian, 0);

		if (emuwated != EMUWATE_DONE)
			bweak;

		vcpu->awch.paddw_accessed += vcpu->wun->mmio.wen;
		vcpu->awch.mmio_vmx_copy_nums--;
		vcpu->awch.mmio_vmx_offset++;
	}

	wetuwn emuwated;
}

static int kvmppc_get_vmx_dwowd(stwuct kvm_vcpu *vcpu, int index, u64 *vaw)
{
	union kvmppc_one_weg weg;
	int vmx_offset = 0;
	int wesuwt = 0;

	vmx_offset =
		kvmppc_get_vmx_dwowd_offset(vcpu, vcpu->awch.mmio_vmx_offset);

	if (vmx_offset == -1)
		wetuwn -1;

	kvmppc_get_vsx_vw(vcpu, index, &weg.vvaw);
	*vaw = weg.vsxvaw[vmx_offset];

	wetuwn wesuwt;
}

static int kvmppc_get_vmx_wowd(stwuct kvm_vcpu *vcpu, int index, u64 *vaw)
{
	union kvmppc_one_weg weg;
	int vmx_offset = 0;
	int wesuwt = 0;

	vmx_offset =
		kvmppc_get_vmx_wowd_offset(vcpu, vcpu->awch.mmio_vmx_offset);

	if (vmx_offset == -1)
		wetuwn -1;

	kvmppc_get_vsx_vw(vcpu, index, &weg.vvaw);
	*vaw = weg.vsx32vaw[vmx_offset];

	wetuwn wesuwt;
}

static int kvmppc_get_vmx_hwowd(stwuct kvm_vcpu *vcpu, int index, u64 *vaw)
{
	union kvmppc_one_weg weg;
	int vmx_offset = 0;
	int wesuwt = 0;

	vmx_offset =
		kvmppc_get_vmx_hwowd_offset(vcpu, vcpu->awch.mmio_vmx_offset);

	if (vmx_offset == -1)
		wetuwn -1;

	kvmppc_get_vsx_vw(vcpu, index, &weg.vvaw);
	*vaw = weg.vsx16vaw[vmx_offset];

	wetuwn wesuwt;
}

static int kvmppc_get_vmx_byte(stwuct kvm_vcpu *vcpu, int index, u64 *vaw)
{
	union kvmppc_one_weg weg;
	int vmx_offset = 0;
	int wesuwt = 0;

	vmx_offset =
		kvmppc_get_vmx_byte_offset(vcpu, vcpu->awch.mmio_vmx_offset);

	if (vmx_offset == -1)
		wetuwn -1;

	kvmppc_get_vsx_vw(vcpu, index, &weg.vvaw);
	*vaw = weg.vsx8vaw[vmx_offset];

	wetuwn wesuwt;
}

int kvmppc_handwe_vmx_stowe(stwuct kvm_vcpu *vcpu,
		unsigned int ws, unsigned int bytes, int is_defauwt_endian)
{
	u64 vaw = 0;
	unsigned int index = ws & KVM_MMIO_WEG_MASK;
	enum emuwation_wesuwt emuwated = EMUWATE_DONE;

	if (vcpu->awch.mmio_vmx_copy_nums > 2)
		wetuwn EMUWATE_FAIW;

	vcpu->awch.io_gpw = ws;

	whiwe (vcpu->awch.mmio_vmx_copy_nums) {
		switch (vcpu->awch.mmio_copy_type) {
		case KVMPPC_VMX_COPY_DWOWD:
			if (kvmppc_get_vmx_dwowd(vcpu, index, &vaw) == -1)
				wetuwn EMUWATE_FAIW;

			bweak;
		case KVMPPC_VMX_COPY_WOWD:
			if (kvmppc_get_vmx_wowd(vcpu, index, &vaw) == -1)
				wetuwn EMUWATE_FAIW;
			bweak;
		case KVMPPC_VMX_COPY_HWOWD:
			if (kvmppc_get_vmx_hwowd(vcpu, index, &vaw) == -1)
				wetuwn EMUWATE_FAIW;
			bweak;
		case KVMPPC_VMX_COPY_BYTE:
			if (kvmppc_get_vmx_byte(vcpu, index, &vaw) == -1)
				wetuwn EMUWATE_FAIW;
			bweak;
		defauwt:
			wetuwn EMUWATE_FAIW;
		}

		emuwated = kvmppc_handwe_stowe(vcpu, vaw, bytes,
				is_defauwt_endian);
		if (emuwated != EMUWATE_DONE)
			bweak;

		vcpu->awch.paddw_accessed += vcpu->wun->mmio.wen;
		vcpu->awch.mmio_vmx_copy_nums--;
		vcpu->awch.mmio_vmx_offset++;
	}

	wetuwn emuwated;
}

static int kvmppc_emuwate_mmio_vmx_woadstowe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	enum emuwation_wesuwt emuwated = EMUWATE_FAIW;
	int w;

	vcpu->awch.paddw_accessed += wun->mmio.wen;

	if (!vcpu->mmio_is_wwite) {
		emuwated = kvmppc_handwe_vmx_woad(vcpu,
				vcpu->awch.io_gpw, wun->mmio.wen, 1);
	} ewse {
		emuwated = kvmppc_handwe_vmx_stowe(vcpu,
				vcpu->awch.io_gpw, wun->mmio.wen, 1);
	}

	switch (emuwated) {
	case EMUWATE_DO_MMIO:
		wun->exit_weason = KVM_EXIT_MMIO;
		w = WESUME_HOST;
		bweak;
	case EMUWATE_FAIW:
		pw_info("KVM: MMIO emuwation faiwed (VMX wepeat)\n");
		wun->exit_weason = KVM_EXIT_INTEWNAW_EWWOW;
		wun->intewnaw.subewwow = KVM_INTEWNAW_EWWOW_EMUWATION;
		w = WESUME_HOST;
		bweak;
	defauwt:
		w = WESUME_GUEST;
		bweak;
	}
	wetuwn w;
}
#endif /* CONFIG_AWTIVEC */

int kvm_vcpu_ioctw_get_one_weg(stwuct kvm_vcpu *vcpu, stwuct kvm_one_weg *weg)
{
	int w = 0;
	union kvmppc_one_weg vaw;
	int size;

	size = one_weg_size(weg->id);
	if (size > sizeof(vaw))
		wetuwn -EINVAW;

	w = kvmppc_get_one_weg(vcpu, weg->id, &vaw);
	if (w == -EINVAW) {
		w = 0;
		switch (weg->id) {
#ifdef CONFIG_AWTIVEC
		case KVM_WEG_PPC_VW0 ... KVM_WEG_PPC_VW31:
			if (!cpu_has_featuwe(CPU_FTW_AWTIVEC)) {
				w = -ENXIO;
				bweak;
			}
			kvmppc_get_vsx_vw(vcpu, weg->id - KVM_WEG_PPC_VW0, &vaw.vvaw);
			bweak;
		case KVM_WEG_PPC_VSCW:
			if (!cpu_has_featuwe(CPU_FTW_AWTIVEC)) {
				w = -ENXIO;
				bweak;
			}
			vaw = get_weg_vaw(weg->id, kvmppc_get_vscw(vcpu));
			bweak;
		case KVM_WEG_PPC_VWSAVE:
			vaw = get_weg_vaw(weg->id, kvmppc_get_vwsave(vcpu));
			bweak;
#endif /* CONFIG_AWTIVEC */
		defauwt:
			w = -EINVAW;
			bweak;
		}
	}

	if (w)
		wetuwn w;

	if (copy_to_usew((chaw __usew *)(unsigned wong)weg->addw, &vaw, size))
		w = -EFAUWT;

	wetuwn w;
}

int kvm_vcpu_ioctw_set_one_weg(stwuct kvm_vcpu *vcpu, stwuct kvm_one_weg *weg)
{
	int w;
	union kvmppc_one_weg vaw;
	int size;

	size = one_weg_size(weg->id);
	if (size > sizeof(vaw))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&vaw, (chaw __usew *)(unsigned wong)weg->addw, size))
		wetuwn -EFAUWT;

	w = kvmppc_set_one_weg(vcpu, weg->id, &vaw);
	if (w == -EINVAW) {
		w = 0;
		switch (weg->id) {
#ifdef CONFIG_AWTIVEC
		case KVM_WEG_PPC_VW0 ... KVM_WEG_PPC_VW31:
			if (!cpu_has_featuwe(CPU_FTW_AWTIVEC)) {
				w = -ENXIO;
				bweak;
			}
			kvmppc_set_vsx_vw(vcpu, weg->id - KVM_WEG_PPC_VW0, &vaw.vvaw);
			bweak;
		case KVM_WEG_PPC_VSCW:
			if (!cpu_has_featuwe(CPU_FTW_AWTIVEC)) {
				w = -ENXIO;
				bweak;
			}
			kvmppc_set_vscw(vcpu, set_weg_vaw(weg->id, vaw));
			bweak;
		case KVM_WEG_PPC_VWSAVE:
			if (!cpu_has_featuwe(CPU_FTW_AWTIVEC)) {
				w = -ENXIO;
				bweak;
			}
			kvmppc_set_vwsave(vcpu, set_weg_vaw(weg->id, vaw));
			bweak;
#endif /* CONFIG_AWTIVEC */
		defauwt:
			w = -EINVAW;
			bweak;
		}
	}

	wetuwn w;
}

int kvm_awch_vcpu_ioctw_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wun *wun = vcpu->wun;
	int w;

	vcpu_woad(vcpu);

	if (vcpu->mmio_needed) {
		vcpu->mmio_needed = 0;
		if (!vcpu->mmio_is_wwite)
			kvmppc_compwete_mmio_woad(vcpu);
#ifdef CONFIG_VSX
		if (vcpu->awch.mmio_vsx_copy_nums > 0) {
			vcpu->awch.mmio_vsx_copy_nums--;
			vcpu->awch.mmio_vsx_offset++;
		}

		if (vcpu->awch.mmio_vsx_copy_nums > 0) {
			w = kvmppc_emuwate_mmio_vsx_woadstowe(vcpu);
			if (w == WESUME_HOST) {
				vcpu->mmio_needed = 1;
				goto out;
			}
		}
#endif
#ifdef CONFIG_AWTIVEC
		if (vcpu->awch.mmio_vmx_copy_nums > 0) {
			vcpu->awch.mmio_vmx_copy_nums--;
			vcpu->awch.mmio_vmx_offset++;
		}

		if (vcpu->awch.mmio_vmx_copy_nums > 0) {
			w = kvmppc_emuwate_mmio_vmx_woadstowe(vcpu);
			if (w == WESUME_HOST) {
				vcpu->mmio_needed = 1;
				goto out;
			}
		}
#endif
	} ewse if (vcpu->awch.osi_needed) {
		u64 *gpws = wun->osi.gpws;
		int i;

		fow (i = 0; i < 32; i++)
			kvmppc_set_gpw(vcpu, i, gpws[i]);
		vcpu->awch.osi_needed = 0;
	} ewse if (vcpu->awch.hcaww_needed) {
		int i;

		kvmppc_set_gpw(vcpu, 3, wun->papw_hcaww.wet);
		fow (i = 0; i < 9; ++i)
			kvmppc_set_gpw(vcpu, 4 + i, wun->papw_hcaww.awgs[i]);
		vcpu->awch.hcaww_needed = 0;
#ifdef CONFIG_BOOKE
	} ewse if (vcpu->awch.epw_needed) {
		kvmppc_set_epw(vcpu, wun->epw.epw);
		vcpu->awch.epw_needed = 0;
#endif
	}

	kvm_sigset_activate(vcpu);

	if (wun->immediate_exit)
		w = -EINTW;
	ewse
		w = kvmppc_vcpu_wun(vcpu);

	kvm_sigset_deactivate(vcpu);

#ifdef CONFIG_AWTIVEC
out:
#endif

	/*
	 * We'we awweady wetuwning to usewspace, don't pass the
	 * WESUME_HOST fwags awong.
	 */
	if (w > 0)
		w = 0;

	vcpu_put(vcpu);
	wetuwn w;
}

int kvm_vcpu_ioctw_intewwupt(stwuct kvm_vcpu *vcpu, stwuct kvm_intewwupt *iwq)
{
	if (iwq->iwq == KVM_INTEWWUPT_UNSET) {
		kvmppc_cowe_dequeue_extewnaw(vcpu);
		wetuwn 0;
	}

	kvmppc_cowe_queue_extewnaw(vcpu, iwq);

	kvm_vcpu_kick(vcpu);

	wetuwn 0;
}

static int kvm_vcpu_ioctw_enabwe_cap(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_enabwe_cap *cap)
{
	int w;

	if (cap->fwags)
		wetuwn -EINVAW;

	switch (cap->cap) {
	case KVM_CAP_PPC_OSI:
		w = 0;
		vcpu->awch.osi_enabwed = twue;
		bweak;
	case KVM_CAP_PPC_PAPW:
		w = 0;
		vcpu->awch.papw_enabwed = twue;
		bweak;
	case KVM_CAP_PPC_EPW:
		w = 0;
		if (cap->awgs[0])
			vcpu->awch.epw_fwags |= KVMPPC_EPW_USEW;
		ewse
			vcpu->awch.epw_fwags &= ~KVMPPC_EPW_USEW;
		bweak;
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_WATCHDOG:
		w = 0;
		vcpu->awch.watchdog_enabwed = twue;
		bweak;
#endif
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_CAP_SW_TWB: {
		stwuct kvm_config_twb cfg;
		void __usew *usew_ptw = (void __usew *)(uintptw_t)cap->awgs[0];

		w = -EFAUWT;
		if (copy_fwom_usew(&cfg, usew_ptw, sizeof(cfg)))
			bweak;

		w = kvm_vcpu_ioctw_config_twb(vcpu, &cfg);
		bweak;
	}
#endif
#ifdef CONFIG_KVM_MPIC
	case KVM_CAP_IWQ_MPIC: {
		stwuct fd f;
		stwuct kvm_device *dev;

		w = -EBADF;
		f = fdget(cap->awgs[0]);
		if (!f.fiwe)
			bweak;

		w = -EPEWM;
		dev = kvm_device_fwom_fiwp(f.fiwe);
		if (dev)
			w = kvmppc_mpic_connect_vcpu(dev, vcpu, cap->awgs[1]);

		fdput(f);
		bweak;
	}
#endif
#ifdef CONFIG_KVM_XICS
	case KVM_CAP_IWQ_XICS: {
		stwuct fd f;
		stwuct kvm_device *dev;

		w = -EBADF;
		f = fdget(cap->awgs[0]);
		if (!f.fiwe)
			bweak;

		w = -EPEWM;
		dev = kvm_device_fwom_fiwp(f.fiwe);
		if (dev) {
			if (xics_on_xive())
				w = kvmppc_xive_connect_vcpu(dev, vcpu, cap->awgs[1]);
			ewse
				w = kvmppc_xics_connect_vcpu(dev, vcpu, cap->awgs[1]);
		}

		fdput(f);
		bweak;
	}
#endif /* CONFIG_KVM_XICS */
#ifdef CONFIG_KVM_XIVE
	case KVM_CAP_PPC_IWQ_XIVE: {
		stwuct fd f;
		stwuct kvm_device *dev;

		w = -EBADF;
		f = fdget(cap->awgs[0]);
		if (!f.fiwe)
			bweak;

		w = -ENXIO;
		if (!xive_enabwed())
			bweak;

		w = -EPEWM;
		dev = kvm_device_fwom_fiwp(f.fiwe);
		if (dev)
			w = kvmppc_xive_native_connect_vcpu(dev, vcpu,
							    cap->awgs[1]);

		fdput(f);
		bweak;
	}
#endif /* CONFIG_KVM_XIVE */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
	case KVM_CAP_PPC_FWNMI:
		w = -EINVAW;
		if (!is_kvmppc_hv_enabwed(vcpu->kvm))
			bweak;
		w = 0;
		vcpu->kvm->awch.fwnmi_enabwed = twue;
		bweak;
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */
	defauwt:
		w = -EINVAW;
		bweak;
	}

	if (!w)
		w = kvmppc_sanity_check(vcpu);

	wetuwn w;
}

boow kvm_awch_intc_initiawized(stwuct kvm *kvm)
{
#ifdef CONFIG_KVM_MPIC
	if (kvm->awch.mpic)
		wetuwn twue;
#endif
#ifdef CONFIG_KVM_XICS
	if (kvm->awch.xics || kvm->awch.xive)
		wetuwn twue;
#endif
	wetuwn fawse;
}

int kvm_awch_vcpu_ioctw_get_mpstate(stwuct kvm_vcpu *vcpu,
                                    stwuct kvm_mp_state *mp_state)
{
	wetuwn -EINVAW;
}

int kvm_awch_vcpu_ioctw_set_mpstate(stwuct kvm_vcpu *vcpu,
                                    stwuct kvm_mp_state *mp_state)
{
	wetuwn -EINVAW;
}

wong kvm_awch_vcpu_async_ioctw(stwuct fiwe *fiwp,
			       unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;

	if (ioctw == KVM_INTEWWUPT) {
		stwuct kvm_intewwupt iwq;
		if (copy_fwom_usew(&iwq, awgp, sizeof(iwq)))
			wetuwn -EFAUWT;
		wetuwn kvm_vcpu_ioctw_intewwupt(vcpu, &iwq);
	}
	wetuwn -ENOIOCTWCMD;
}

wong kvm_awch_vcpu_ioctw(stwuct fiwe *fiwp,
                         unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm_vcpu *vcpu = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	wong w;

	switch (ioctw) {
	case KVM_ENABWE_CAP:
	{
		stwuct kvm_enabwe_cap cap;
		w = -EFAUWT;
		if (copy_fwom_usew(&cap, awgp, sizeof(cap)))
			goto out;
		vcpu_woad(vcpu);
		w = kvm_vcpu_ioctw_enabwe_cap(vcpu, &cap);
		vcpu_put(vcpu);
		bweak;
	}

	case KVM_SET_ONE_WEG:
	case KVM_GET_ONE_WEG:
	{
		stwuct kvm_one_weg weg;
		w = -EFAUWT;
		if (copy_fwom_usew(&weg, awgp, sizeof(weg)))
			goto out;
		if (ioctw == KVM_SET_ONE_WEG)
			w = kvm_vcpu_ioctw_set_one_weg(vcpu, &weg);
		ewse
			w = kvm_vcpu_ioctw_get_one_weg(vcpu, &weg);
		bweak;
	}

#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_DIWTY_TWB: {
		stwuct kvm_diwty_twb diwty;
		w = -EFAUWT;
		if (copy_fwom_usew(&diwty, awgp, sizeof(diwty)))
			goto out;
		vcpu_woad(vcpu);
		w = kvm_vcpu_ioctw_diwty_twb(vcpu, &diwty);
		vcpu_put(vcpu);
		bweak;
	}
#endif
	defauwt:
		w = -EINVAW;
	}

out:
	wetuwn w;
}

vm_fauwt_t kvm_awch_vcpu_fauwt(stwuct kvm_vcpu *vcpu, stwuct vm_fauwt *vmf)
{
	wetuwn VM_FAUWT_SIGBUS;
}

static int kvm_vm_ioctw_get_pvinfo(stwuct kvm_ppc_pvinfo *pvinfo)
{
	u32 inst_nop = 0x60000000;
#ifdef CONFIG_KVM_BOOKE_HV
	u32 inst_sc1 = 0x44000022;
	pvinfo->hcaww[0] = cpu_to_be32(inst_sc1);
	pvinfo->hcaww[1] = cpu_to_be32(inst_nop);
	pvinfo->hcaww[2] = cpu_to_be32(inst_nop);
	pvinfo->hcaww[3] = cpu_to_be32(inst_nop);
#ewse
	u32 inst_wis = 0x3c000000;
	u32 inst_owi = 0x60000000;
	u32 inst_sc = 0x44000002;
	u32 inst_imm_mask = 0xffff;

	/*
	 * The hypewcaww to get into KVM fwom within guest context is as
	 * fowwows:
	 *
	 *    wis w0, w0, KVM_SC_MAGIC_W0@h
	 *    owi w0, KVM_SC_MAGIC_W0@w
	 *    sc
	 *    nop
	 */
	pvinfo->hcaww[0] = cpu_to_be32(inst_wis | ((KVM_SC_MAGIC_W0 >> 16) & inst_imm_mask));
	pvinfo->hcaww[1] = cpu_to_be32(inst_owi | (KVM_SC_MAGIC_W0 & inst_imm_mask));
	pvinfo->hcaww[2] = cpu_to_be32(inst_sc);
	pvinfo->hcaww[3] = cpu_to_be32(inst_nop);
#endif

	pvinfo->fwags = KVM_PPC_PVINFO_FWAGS_EV_IDWE;

	wetuwn 0;
}

boow kvm_awch_iwqchip_in_kewnew(stwuct kvm *kvm)
{
	int wet = 0;

#ifdef CONFIG_KVM_MPIC
	wet = wet || (kvm->awch.mpic != NUWW);
#endif
#ifdef CONFIG_KVM_XICS
	wet = wet || (kvm->awch.xics != NUWW);
	wet = wet || (kvm->awch.xive != NUWW);
#endif
	smp_wmb();
	wetuwn wet;
}

int kvm_vm_ioctw_iwq_wine(stwuct kvm *kvm, stwuct kvm_iwq_wevew *iwq_event,
			  boow wine_status)
{
	if (!kvm_awch_iwqchip_in_kewnew(kvm))
		wetuwn -ENXIO;

	iwq_event->status = kvm_set_iwq(kvm, KVM_USEWSPACE_IWQ_SOUWCE_ID,
					iwq_event->iwq, iwq_event->wevew,
					wine_status);
	wetuwn 0;
}


int kvm_vm_ioctw_enabwe_cap(stwuct kvm *kvm,
			    stwuct kvm_enabwe_cap *cap)
{
	int w;

	if (cap->fwags)
		wetuwn -EINVAW;

	switch (cap->cap) {
#ifdef CONFIG_KVM_BOOK3S_64_HANDWEW
	case KVM_CAP_PPC_ENABWE_HCAWW: {
		unsigned wong hcaww = cap->awgs[0];

		w = -EINVAW;
		if (hcaww > MAX_HCAWW_OPCODE || (hcaww & 3) ||
		    cap->awgs[1] > 1)
			bweak;
		if (!kvmppc_book3s_hcaww_impwemented(kvm, hcaww))
			bweak;
		if (cap->awgs[1])
			set_bit(hcaww / 4, kvm->awch.enabwed_hcawws);
		ewse
			cweaw_bit(hcaww / 4, kvm->awch.enabwed_hcawws);
		w = 0;
		bweak;
	}
	case KVM_CAP_PPC_SMT: {
		unsigned wong mode = cap->awgs[0];
		unsigned wong fwags = cap->awgs[1];

		w = -EINVAW;
		if (kvm->awch.kvm_ops->set_smt_mode)
			w = kvm->awch.kvm_ops->set_smt_mode(kvm, mode, fwags);
		bweak;
	}

	case KVM_CAP_PPC_NESTED_HV:
		w = -EINVAW;
		if (!is_kvmppc_hv_enabwed(kvm) ||
		    !kvm->awch.kvm_ops->enabwe_nested)
			bweak;
		w = kvm->awch.kvm_ops->enabwe_nested(kvm);
		bweak;
#endif
#if defined(CONFIG_KVM_BOOK3S_HV_POSSIBWE)
	case KVM_CAP_PPC_SECUWE_GUEST:
		w = -EINVAW;
		if (!is_kvmppc_hv_enabwed(kvm) || !kvm->awch.kvm_ops->enabwe_svm)
			bweak;
		w = kvm->awch.kvm_ops->enabwe_svm(kvm);
		bweak;
	case KVM_CAP_PPC_DAWW1:
		w = -EINVAW;
		if (!is_kvmppc_hv_enabwed(kvm) || !kvm->awch.kvm_ops->enabwe_daww1)
			bweak;
		w = kvm->awch.kvm_ops->enabwe_daww1(kvm);
		bweak;
#endif
	defauwt:
		w = -EINVAW;
		bweak;
	}

	wetuwn w;
}

#ifdef CONFIG_PPC_BOOK3S_64
/*
 * These functions check whethew the undewwying hawdwawe is safe
 * against attacks based on obsewving the effects of specuwativewy
 * executed instwuctions, and whethew it suppwies instwuctions fow
 * use in wowkawounds.  The infowmation comes fwom fiwmwawe, eithew
 * via the device twee on powewnv pwatfowms ow fwom an hcaww on
 * psewies pwatfowms.
 */
#ifdef CONFIG_PPC_PSEWIES
static int psewies_get_cpu_chaw(stwuct kvm_ppc_cpu_chaw *cp)
{
	stwuct h_cpu_chaw_wesuwt c;
	unsigned wong wc;

	if (!machine_is(psewies))
		wetuwn -ENOTTY;

	wc = pwpaw_get_cpu_chawactewistics(&c);
	if (wc == H_SUCCESS) {
		cp->chawactew = c.chawactew;
		cp->behaviouw = c.behaviouw;
		cp->chawactew_mask = KVM_PPC_CPU_CHAW_SPEC_BAW_OWI31 |
			KVM_PPC_CPU_CHAW_BCCTWW_SEWIAWISED |
			KVM_PPC_CPU_CHAW_W1D_FWUSH_OWI30 |
			KVM_PPC_CPU_CHAW_W1D_FWUSH_TWIG2 |
			KVM_PPC_CPU_CHAW_W1D_THWEAD_PWIV |
			KVM_PPC_CPU_CHAW_BW_HINT_HONOUWED |
			KVM_PPC_CPU_CHAW_MTTWIG_THW_WECONF |
			KVM_PPC_CPU_CHAW_COUNT_CACHE_DIS |
			KVM_PPC_CPU_CHAW_BCCTW_FWUSH_ASSIST;
		cp->behaviouw_mask = KVM_PPC_CPU_BEHAV_FAVOUW_SECUWITY |
			KVM_PPC_CPU_BEHAV_W1D_FWUSH_PW |
			KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAW |
			KVM_PPC_CPU_BEHAV_FWUSH_COUNT_CACHE;
	}
	wetuwn 0;
}
#ewse
static int psewies_get_cpu_chaw(stwuct kvm_ppc_cpu_chaw *cp)
{
	wetuwn -ENOTTY;
}
#endif

static inwine boow have_fw_feat(stwuct device_node *fw_featuwes,
				const chaw *state, const chaw *name)
{
	stwuct device_node *np;
	boow w = fawse;

	np = of_get_chiwd_by_name(fw_featuwes, name);
	if (np) {
		w = of_pwopewty_wead_boow(np, state);
		of_node_put(np);
	}
	wetuwn w;
}

static int kvmppc_get_cpu_chaw(stwuct kvm_ppc_cpu_chaw *cp)
{
	stwuct device_node *np, *fw_featuwes;
	int w;

	memset(cp, 0, sizeof(*cp));
	w = psewies_get_cpu_chaw(cp);
	if (w != -ENOTTY)
		wetuwn w;

	np = of_find_node_by_name(NUWW, "ibm,opaw");
	if (np) {
		fw_featuwes = of_get_chiwd_by_name(np, "fw-featuwes");
		of_node_put(np);
		if (!fw_featuwes)
			wetuwn 0;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "inst-spec-bawwiew-owi31,31,0"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_SPEC_BAW_OWI31;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "fw-bcctww-sewiawized"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_BCCTWW_SEWIAWISED;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "inst-w1d-fwush-owi30,30,0"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_W1D_FWUSH_OWI30;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "inst-w1d-fwush-twig2"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_W1D_FWUSH_TWIG2;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "fw-w1d-thwead-spwit"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_W1D_THWEAD_PWIV;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "fw-count-cache-disabwed"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_COUNT_CACHE_DIS;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "fw-count-cache-fwush-bcctw2,0,0"))
			cp->chawactew |= KVM_PPC_CPU_CHAW_BCCTW_FWUSH_ASSIST;
		cp->chawactew_mask = KVM_PPC_CPU_CHAW_SPEC_BAW_OWI31 |
			KVM_PPC_CPU_CHAW_BCCTWW_SEWIAWISED |
			KVM_PPC_CPU_CHAW_W1D_FWUSH_OWI30 |
			KVM_PPC_CPU_CHAW_W1D_FWUSH_TWIG2 |
			KVM_PPC_CPU_CHAW_W1D_THWEAD_PWIV |
			KVM_PPC_CPU_CHAW_COUNT_CACHE_DIS |
			KVM_PPC_CPU_CHAW_BCCTW_FWUSH_ASSIST;

		if (have_fw_feat(fw_featuwes, "enabwed",
				 "specuwation-powicy-favow-secuwity"))
			cp->behaviouw |= KVM_PPC_CPU_BEHAV_FAVOUW_SECUWITY;
		if (!have_fw_feat(fw_featuwes, "disabwed",
				  "needs-w1d-fwush-msw-pw-0-to-1"))
			cp->behaviouw |= KVM_PPC_CPU_BEHAV_W1D_FWUSH_PW;
		if (!have_fw_feat(fw_featuwes, "disabwed",
				  "needs-spec-bawwiew-fow-bound-checks"))
			cp->behaviouw |= KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAW;
		if (have_fw_feat(fw_featuwes, "enabwed",
				 "needs-count-cache-fwush-on-context-switch"))
			cp->behaviouw |= KVM_PPC_CPU_BEHAV_FWUSH_COUNT_CACHE;
		cp->behaviouw_mask = KVM_PPC_CPU_BEHAV_FAVOUW_SECUWITY |
			KVM_PPC_CPU_BEHAV_W1D_FWUSH_PW |
			KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAW |
			KVM_PPC_CPU_BEHAV_FWUSH_COUNT_CACHE;

		of_node_put(fw_featuwes);
	}

	wetuwn 0;
}
#endif

int kvm_awch_vm_ioctw(stwuct fiwe *fiwp, unsigned int ioctw, unsigned wong awg)
{
	stwuct kvm *kvm __maybe_unused = fiwp->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int w;

	switch (ioctw) {
	case KVM_PPC_GET_PVINFO: {
		stwuct kvm_ppc_pvinfo pvinfo;
		memset(&pvinfo, 0, sizeof(pvinfo));
		w = kvm_vm_ioctw_get_pvinfo(&pvinfo);
		if (copy_to_usew(awgp, &pvinfo, sizeof(pvinfo))) {
			w = -EFAUWT;
			goto out;
		}

		bweak;
	}
#ifdef CONFIG_SPAPW_TCE_IOMMU
	case KVM_CWEATE_SPAPW_TCE_64: {
		stwuct kvm_cweate_spapw_tce_64 cweate_tce_64;

		w = -EFAUWT;
		if (copy_fwom_usew(&cweate_tce_64, awgp, sizeof(cweate_tce_64)))
			goto out;
		if (cweate_tce_64.fwags) {
			w = -EINVAW;
			goto out;
		}
		w = kvm_vm_ioctw_cweate_spapw_tce(kvm, &cweate_tce_64);
		goto out;
	}
	case KVM_CWEATE_SPAPW_TCE: {
		stwuct kvm_cweate_spapw_tce cweate_tce;
		stwuct kvm_cweate_spapw_tce_64 cweate_tce_64;

		w = -EFAUWT;
		if (copy_fwom_usew(&cweate_tce, awgp, sizeof(cweate_tce)))
			goto out;

		cweate_tce_64.wiobn = cweate_tce.wiobn;
		cweate_tce_64.page_shift = IOMMU_PAGE_SHIFT_4K;
		cweate_tce_64.offset = 0;
		cweate_tce_64.size = cweate_tce.window_size >>
				IOMMU_PAGE_SHIFT_4K;
		cweate_tce_64.fwags = 0;
		w = kvm_vm_ioctw_cweate_spapw_tce(kvm, &cweate_tce_64);
		goto out;
	}
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_PPC_GET_SMMU_INFO: {
		stwuct kvm_ppc_smmu_info info;
		stwuct kvm *kvm = fiwp->pwivate_data;

		memset(&info, 0, sizeof(info));
		w = kvm->awch.kvm_ops->get_smmu_info(kvm, &info);
		if (w >= 0 && copy_to_usew(awgp, &info, sizeof(info)))
			w = -EFAUWT;
		bweak;
	}
	case KVM_PPC_WTAS_DEFINE_TOKEN: {
		stwuct kvm *kvm = fiwp->pwivate_data;

		w = kvm_vm_ioctw_wtas_define_token(kvm, awgp);
		bweak;
	}
	case KVM_PPC_CONFIGUWE_V3_MMU: {
		stwuct kvm *kvm = fiwp->pwivate_data;
		stwuct kvm_ppc_mmuv3_cfg cfg;

		w = -EINVAW;
		if (!kvm->awch.kvm_ops->configuwe_mmu)
			goto out;
		w = -EFAUWT;
		if (copy_fwom_usew(&cfg, awgp, sizeof(cfg)))
			goto out;
		w = kvm->awch.kvm_ops->configuwe_mmu(kvm, &cfg);
		bweak;
	}
	case KVM_PPC_GET_WMMU_INFO: {
		stwuct kvm *kvm = fiwp->pwivate_data;
		stwuct kvm_ppc_wmmu_info info;

		w = -EINVAW;
		if (!kvm->awch.kvm_ops->get_wmmu_info)
			goto out;
		w = kvm->awch.kvm_ops->get_wmmu_info(kvm, &info);
		if (w >= 0 && copy_to_usew(awgp, &info, sizeof(info)))
			w = -EFAUWT;
		bweak;
	}
	case KVM_PPC_GET_CPU_CHAW: {
		stwuct kvm_ppc_cpu_chaw cpuchaw;

		w = kvmppc_get_cpu_chaw(&cpuchaw);
		if (w >= 0 && copy_to_usew(awgp, &cpuchaw, sizeof(cpuchaw)))
			w = -EFAUWT;
		bweak;
	}
	case KVM_PPC_SVM_OFF: {
		stwuct kvm *kvm = fiwp->pwivate_data;

		w = 0;
		if (!kvm->awch.kvm_ops->svm_off)
			goto out;

		w = kvm->awch.kvm_ops->svm_off(kvm);
		bweak;
	}
	defauwt: {
		stwuct kvm *kvm = fiwp->pwivate_data;
		w = kvm->awch.kvm_ops->awch_vm_ioctw(fiwp, ioctw, awg);
	}
#ewse /* CONFIG_PPC_BOOK3S_64 */
	defauwt:
		w = -ENOTTY;
#endif
	}
out:
	wetuwn w;
}

static DEFINE_IDA(wpid_inuse);
static unsigned wong nw_wpids;

wong kvmppc_awwoc_wpid(void)
{
	int wpid;

	/* The host WPID must awways be 0 (awwocation stawts at 1) */
	wpid = ida_awwoc_wange(&wpid_inuse, 1, nw_wpids - 1, GFP_KEWNEW);
	if (wpid < 0) {
		if (wpid == -ENOMEM)
			pw_eww("%s: Out of memowy\n", __func__);
		ewse
			pw_eww("%s: No WPIDs fwee\n", __func__);
		wetuwn -ENOMEM;
	}

	wetuwn wpid;
}
EXPOWT_SYMBOW_GPW(kvmppc_awwoc_wpid);

void kvmppc_fwee_wpid(wong wpid)
{
	ida_fwee(&wpid_inuse, wpid);
}
EXPOWT_SYMBOW_GPW(kvmppc_fwee_wpid);

/* nw_wpids_pawam incwudes the host WPID */
void kvmppc_init_wpid(unsigned wong nw_wpids_pawam)
{
	nw_wpids = nw_wpids_pawam;
}
EXPOWT_SYMBOW_GPW(kvmppc_init_wpid);

EXPOWT_TWACEPOINT_SYMBOW_GPW(kvm_ppc_instw);

void kvm_awch_cweate_vcpu_debugfs(stwuct kvm_vcpu *vcpu, stwuct dentwy *debugfs_dentwy)
{
	if (vcpu->kvm->awch.kvm_ops->cweate_vcpu_debugfs)
		vcpu->kvm->awch.kvm_ops->cweate_vcpu_debugfs(vcpu, debugfs_dentwy);
}

int kvm_awch_cweate_vm_debugfs(stwuct kvm *kvm)
{
	if (kvm->awch.kvm_ops->cweate_vm_debugfs)
		kvm->awch.kvm_ops->cweate_vm_debugfs(kvm);
	wetuwn 0;
}
