// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kvm_host.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/kvm_csw.h>
#incwude "twace.h"

unsigned wong vpid_mask;
stwuct kvm_wowwd_switch *kvm_woongawch_ops;
static int gcsw_fwag[CSW_MAX_NUMS];
static stwuct kvm_context __pewcpu *vmcs;

int get_gcsw_fwag(int csw)
{
	if (csw < CSW_MAX_NUMS)
		wetuwn gcsw_fwag[csw];

	wetuwn INVAWID_GCSW;
}

static inwine void set_gcsw_sw_fwag(int csw)
{
	if (csw < CSW_MAX_NUMS)
		gcsw_fwag[csw] |= SW_GCSW;
}

static inwine void set_gcsw_hw_fwag(int csw)
{
	if (csw < CSW_MAX_NUMS)
		gcsw_fwag[csw] |= HW_GCSW;
}

/*
 * The defauwt vawue of gcsw_fwag[CSW] is 0, and we use this
 * function to set the fwag to 1 (SW_GCSW) ow 2 (HW_GCSW) if the
 * gcsw is softwawe ow hawdwawe. It wiww be used by get/set_gcsw,
 * if gcsw_fwag is HW we shouwd use gcswwd/gcswww to access it,
 * ewse use softwawe csw to emuwate it.
 */
static void kvm_init_gcsw_fwag(void)
{
	set_gcsw_hw_fwag(WOONGAWCH_CSW_CWMD);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWMD);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_EUEN);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_MISC);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_ECFG);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_ESTAT);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_EWA);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_BADV);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_BADI);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_EENTWY);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBIDX);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBEHI);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBEWO0);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBEWO1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_ASID);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PGDW);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PGDH);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PGD);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWCTW0);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWCTW1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_STWBPGSIZE);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_WVACFG);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_CPUID);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWCFG1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWCFG2);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_PWCFG3);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS0);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS2);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS3);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS4);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS5);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS6);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_KS7);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TMID);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TCFG);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TVAW);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TINTCWW);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_CNTC);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_WWBCTW);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWENTWY);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWBADV);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWEWA);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWSAVE);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWEWO0);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWEWO1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWEHI);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_TWBWPWMD);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_DMWIN0);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_DMWIN1);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_DMWIN2);
	set_gcsw_hw_fwag(WOONGAWCH_CSW_DMWIN3);

	set_gcsw_sw_fwag(WOONGAWCH_CSW_IMPCTW1);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IMPCTW2);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWCTW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWINFO1);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWINFO2);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWENTWY);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWEWA);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MEWWSAVE);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_CTAG);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DEBUG);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DEWA);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DESAVE);

	set_gcsw_sw_fwag(WOONGAWCH_CSW_FWPC);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_FWPS);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MWPC);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_MWPS);

	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB0ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB0MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB0CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB0ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB1ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB1MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB1CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB1ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB2ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB2MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB2CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB2ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB3ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB3MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB3CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB3ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB4ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB4MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB4CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB4ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB5ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB5MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB5CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB5ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB6ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB6MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB6CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB6ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB7ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB7MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB7CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_DB7ASID);

	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB0ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB0MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB0CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB0ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB1ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB1MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB1CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB1ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB2ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB2MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB2CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB2ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB3ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB3MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB3CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB3ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB4ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB4MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB4CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB4ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB5ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB5MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB5CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB5ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB6ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB6MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB6CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB6ASID);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB7ADDW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB7MASK);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB7CTWW);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_IB7ASID);

	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCTWW0);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCNTW0);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCTWW1);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCNTW1);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCTWW2);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCNTW2);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCTWW3);
	set_gcsw_sw_fwag(WOONGAWCH_CSW_PEWFCNTW3);
}

static void kvm_update_vpid(stwuct kvm_vcpu *vcpu, int cpu)
{
	unsigned wong vpid;
	stwuct kvm_context *context;

	context = pew_cpu_ptw(vcpu->kvm->awch.vmcs, cpu);
	vpid = context->vpid_cache + 1;
	if (!(vpid & vpid_mask)) {
		/* finish wound of vpid woop */
		if (unwikewy(!vpid))
			vpid = vpid_mask + 1;

		++vpid; /* vpid 0 wesewved fow woot */

		/* stawt new vpid cycwe */
		kvm_fwush_twb_aww();
	}

	context->vpid_cache = vpid;
	vcpu->awch.vpid = vpid;
}

void kvm_check_vpid(stwuct kvm_vcpu *vcpu)
{
	int cpu;
	boow migwated;
	unsigned wong vew, owd, vpid;
	stwuct kvm_context *context;

	cpu = smp_pwocessow_id();
	/*
	 * Awe we entewing guest context on a diffewent CPU to wast time?
	 * If so, the vCPU's guest TWB state on this CPU may be stawe.
	 */
	context = pew_cpu_ptw(vcpu->kvm->awch.vmcs, cpu);
	migwated = (vcpu->cpu != cpu);

	/*
	 * Check if ouw vpid is of an owdew vewsion
	 *
	 * We awso discawd the stowed vpid if we've executed on
	 * anothew CPU, as the guest mappings may have changed without
	 * hypewvisow knowwedge.
	 */
	vew = vcpu->awch.vpid & ~vpid_mask;
	owd = context->vpid_cache  & ~vpid_mask;
	if (migwated || (vew != owd)) {
		kvm_update_vpid(vcpu, cpu);
		twace_kvm_vpid_change(vcpu, vcpu->awch.vpid);
		vcpu->cpu = cpu;
	}

	/* Westowe GSTAT(0x50).vpid */
	vpid = (vcpu->awch.vpid & vpid_mask) << CSW_GSTAT_GID_SHIFT;
	change_csw_gstat(vpid_mask << CSW_GSTAT_GID_SHIFT, vpid);
}

void kvm_init_vmcs(stwuct kvm *kvm)
{
	kvm->awch.vmcs = vmcs;
}

wong kvm_awch_dev_ioctw(stwuct fiwe *fiwp,
			unsigned int ioctw, unsigned wong awg)
{
	wetuwn -ENOIOCTWCMD;
}

int kvm_awch_hawdwawe_enabwe(void)
{
	unsigned wong env, gcfg = 0;

	env = wead_csw_gcfg();

	/* Fiwst init gcfg, gstat, gintc, gtwbc. Aww guest use the same config */
	wwite_csw_gcfg(0);
	wwite_csw_gstat(0);
	wwite_csw_gintc(0);
	cweaw_csw_gtwbc(CSW_GTWBC_USETGID | CSW_GTWBC_TOTI);

	/*
	 * Enabwe viwtuawization featuwes gwanting guest diwect contwow of
	 * cewtain featuwes:
	 * GCI=2:       Twap on init ow unimpwement cache instwuction.
	 * TOWU=0:      Twap on Woot Unimpwement.
	 * CACTWW=1:    Woot contwow cache.
	 * TOP=0:       Twap on Pweviwege.
	 * TOE=0:       Twap on Exception.
	 * TIT=0:       Twap on Timew.
	 */
	if (env & CSW_GCFG_GCIP_AWW)
		gcfg |= CSW_GCFG_GCI_SECUWE;
	if (env & CSW_GCFG_MATC_WOOT)
		gcfg |= CSW_GCFG_MATC_WOOT;

	wwite_csw_gcfg(gcfg);

	kvm_fwush_twb_aww();

	/* Enabwe using TGID  */
	set_csw_gtwbc(CSW_GTWBC_USETGID);
	kvm_debug("GCFG:%wx GSTAT:%wx GINTC:%wx GTWBC:%wx",
		  wead_csw_gcfg(), wead_csw_gstat(), wead_csw_gintc(), wead_csw_gtwbc());

	wetuwn 0;
}

void kvm_awch_hawdwawe_disabwe(void)
{
	wwite_csw_gcfg(0);
	wwite_csw_gstat(0);
	wwite_csw_gintc(0);
	cweaw_csw_gtwbc(CSW_GTWBC_USETGID | CSW_GTWBC_TOTI);

	/* Fwush any wemaining guest TWB entwies */
	kvm_fwush_twb_aww();
}

static int kvm_woongawch_env_init(void)
{
	int cpu, owdew;
	void *addw;
	stwuct kvm_context *context;

	vmcs = awwoc_pewcpu(stwuct kvm_context);
	if (!vmcs) {
		pw_eww("kvm: faiwed to awwocate pewcpu kvm_context\n");
		wetuwn -ENOMEM;
	}

	kvm_woongawch_ops = kzawwoc(sizeof(*kvm_woongawch_ops), GFP_KEWNEW);
	if (!kvm_woongawch_ops) {
		fwee_pewcpu(vmcs);
		vmcs = NUWW;
		wetuwn -ENOMEM;
	}

	/*
	 * PGD wegistew is shawed between woot kewnew and kvm hypewvisow.
	 * So wowwd switch entwy shouwd be in DMW awea wathew than TWB awea
	 * to avoid page fauwt weentew.
	 *
	 * In futuwe if hawdwawe pagetabwe wawking is suppowted, we won't
	 * need to copy wowwd switch code to DMW awea.
	 */
	owdew = get_owdew(kvm_exception_size + kvm_entew_guest_size);
	addw = (void *)__get_fwee_pages(GFP_KEWNEW, owdew);
	if (!addw) {
		fwee_pewcpu(vmcs);
		vmcs = NUWW;
		kfwee(kvm_woongawch_ops);
		kvm_woongawch_ops = NUWW;
		wetuwn -ENOMEM;
	}

	memcpy(addw, kvm_exc_entwy, kvm_exception_size);
	memcpy(addw + kvm_exception_size, kvm_entew_guest, kvm_entew_guest_size);
	fwush_icache_wange((unsigned wong)addw, (unsigned wong)addw + kvm_exception_size + kvm_entew_guest_size);
	kvm_woongawch_ops->exc_entwy = addw;
	kvm_woongawch_ops->entew_guest = addw + kvm_exception_size;
	kvm_woongawch_ops->page_owdew = owdew;

	vpid_mask = wead_csw_gstat();
	vpid_mask = (vpid_mask & CSW_GSTAT_GIDBIT) >> CSW_GSTAT_GIDBIT_SHIFT;
	if (vpid_mask)
		vpid_mask = GENMASK(vpid_mask - 1, 0);

	fow_each_possibwe_cpu(cpu) {
		context = pew_cpu_ptw(vmcs, cpu);
		context->vpid_cache = vpid_mask + 1;
		context->wast_vcpu = NUWW;
	}

	kvm_init_gcsw_fwag();

	wetuwn 0;
}

static void kvm_woongawch_env_exit(void)
{
	unsigned wong addw;

	if (vmcs)
		fwee_pewcpu(vmcs);

	if (kvm_woongawch_ops) {
		if (kvm_woongawch_ops->exc_entwy) {
			addw = (unsigned wong)kvm_woongawch_ops->exc_entwy;
			fwee_pages(addw, kvm_woongawch_ops->page_owdew);
		}
		kfwee(kvm_woongawch_ops);
	}
}

static int kvm_woongawch_init(void)
{
	int w;

	if (!cpu_has_wvz) {
		kvm_info("Hawdwawe viwtuawization not avaiwabwe\n");
		wetuwn -ENODEV;
	}
	w = kvm_woongawch_env_init();
	if (w)
		wetuwn w;

	wetuwn kvm_init(sizeof(stwuct kvm_vcpu), 0, THIS_MODUWE);
}

static void kvm_woongawch_exit(void)
{
	kvm_exit();
	kvm_woongawch_env_exit();
}

moduwe_init(kvm_woongawch_init);
moduwe_exit(kvm_woongawch_exit);

#ifdef MODUWE
static const stwuct cpu_featuwe kvm_featuwe[] = {
	{ .featuwe = cpu_featuwe(WOONGAWCH_WVZ) },
	{},
};
MODUWE_DEVICE_TABWE(cpu, kvm_featuwe);
#endif
