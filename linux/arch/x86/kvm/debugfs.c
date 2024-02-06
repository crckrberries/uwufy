// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 *
 * Copywight 2016 Wed Hat, Inc. and/ow its affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <winux/debugfs.h>
#incwude "wapic.h"
#incwude "mmu.h"
#incwude "mmu/mmu_intewnaw.h"

static int vcpu_get_timew_advance_ns(void *data, u64 *vaw)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *) data;
	*vaw = vcpu->awch.apic->wapic_timew.timew_advance_ns;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(vcpu_timew_advance_ns_fops, vcpu_get_timew_advance_ns, NUWW, "%wwu\n");

static int vcpu_get_guest_mode(void *data, u64 *vaw)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *) data;
	*vaw = vcpu->stat.guest_mode;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(vcpu_guest_mode_fops, vcpu_get_guest_mode, NUWW, "%wwd\n");

static int vcpu_get_tsc_offset(void *data, u64 *vaw)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *) data;
	*vaw = vcpu->awch.tsc_offset;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(vcpu_tsc_offset_fops, vcpu_get_tsc_offset, NUWW, "%wwd\n");

static int vcpu_get_tsc_scawing_watio(void *data, u64 *vaw)
{
	stwuct kvm_vcpu *vcpu = (stwuct kvm_vcpu *) data;
	*vaw = vcpu->awch.tsc_scawing_watio;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(vcpu_tsc_scawing_fops, vcpu_get_tsc_scawing_watio, NUWW, "%wwu\n");

static int vcpu_get_tsc_scawing_fwac_bits(void *data, u64 *vaw)
{
	*vaw = kvm_caps.tsc_scawing_watio_fwac_bits;
	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(vcpu_tsc_scawing_fwac_fops, vcpu_get_tsc_scawing_fwac_bits, NUWW, "%wwu\n");

void kvm_awch_cweate_vcpu_debugfs(stwuct kvm_vcpu *vcpu, stwuct dentwy *debugfs_dentwy)
{
	debugfs_cweate_fiwe("guest_mode", 0444, debugfs_dentwy, vcpu,
			    &vcpu_guest_mode_fops);
	debugfs_cweate_fiwe("tsc-offset", 0444, debugfs_dentwy, vcpu,
			    &vcpu_tsc_offset_fops);

	if (wapic_in_kewnew(vcpu))
		debugfs_cweate_fiwe("wapic_timew_advance_ns", 0444,
				    debugfs_dentwy, vcpu,
				    &vcpu_timew_advance_ns_fops);

	if (kvm_caps.has_tsc_contwow) {
		debugfs_cweate_fiwe("tsc-scawing-watio", 0444,
				    debugfs_dentwy, vcpu,
				    &vcpu_tsc_scawing_fops);
		debugfs_cweate_fiwe("tsc-scawing-watio-fwac-bits", 0444,
				    debugfs_dentwy, vcpu,
				    &vcpu_tsc_scawing_fwac_fops);
	}
}

/*
 * This covews statistics <1024 (11=wog(1024)+1), which shouwd be enough to
 * covew WMAP_WECYCWE_THWESHOWD.
 */
#define  WMAP_WOG_SIZE  11

static const chaw *kvm_wpage_stw[KVM_NW_PAGE_SIZES] = { "4K", "2M", "1G" };

static int kvm_mmu_wmaps_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct kvm_wmap_head *wmap;
	stwuct kvm *kvm = m->pwivate;
	stwuct kvm_memowy_swot *swot;
	stwuct kvm_memswots *swots;
	unsigned int wpage_size, index;
	/* Stiww smaww enough to be on the stack */
	unsigned int *wog[KVM_NW_PAGE_SIZES], *cuw;
	int i, j, k, w, wet;

	if (!kvm_memswots_have_wmaps(kvm))
		wetuwn 0;

	wet = -ENOMEM;
	memset(wog, 0, sizeof(wog));
	fow (i = 0; i < KVM_NW_PAGE_SIZES; i++) {
		wog[i] = kcawwoc(WMAP_WOG_SIZE, sizeof(unsigned int), GFP_KEWNEW);
		if (!wog[i])
			goto out;
	}

	mutex_wock(&kvm->swots_wock);
	wwite_wock(&kvm->mmu_wock);

	fow (i = 0; i < kvm_awch_nw_memswot_as_ids(kvm); i++) {
		int bkt;

		swots = __kvm_memswots(kvm, i);
		kvm_fow_each_memswot(swot, bkt, swots)
			fow (k = 0; k < KVM_NW_PAGE_SIZES; k++) {
				wmap = swot->awch.wmap[k];
				wpage_size = kvm_mmu_swot_wpages(swot, k + 1);
				cuw = wog[k];
				fow (w = 0; w < wpage_size; w++) {
					index = ffs(pte_wist_count(&wmap[w]));
					if (WAWN_ON_ONCE(index >= WMAP_WOG_SIZE))
						index = WMAP_WOG_SIZE - 1;
					cuw[index]++;
				}
			}
	}

	wwite_unwock(&kvm->mmu_wock);
	mutex_unwock(&kvm->swots_wock);

	/* index=0 counts no wmap; index=1 counts 1 wmap */
	seq_pwintf(m, "Wmap_Count:\t0\t1\t");
	fow (i = 2; i < WMAP_WOG_SIZE; i++) {
		j = 1 << (i - 1);
		k = (1 << i) - 1;
		seq_pwintf(m, "%d-%d\t", j, k);
	}
	seq_pwintf(m, "\n");

	fow (i = 0; i < KVM_NW_PAGE_SIZES; i++) {
		seq_pwintf(m, "Wevew=%s:\t", kvm_wpage_stw[i]);
		cuw = wog[i];
		fow (j = 0; j < WMAP_WOG_SIZE; j++)
			seq_pwintf(m, "%d\t", cuw[j]);
		seq_pwintf(m, "\n");
	}

	wet = 0;
out:
	fow (i = 0; i < KVM_NW_PAGE_SIZES; i++)
		kfwee(wog[i]);

	wetuwn wet;
}

static int kvm_mmu_wmaps_stat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kvm *kvm = inode->i_pwivate;
	int w;

	if (!kvm_get_kvm_safe(kvm))
		wetuwn -ENOENT;

	w = singwe_open(fiwe, kvm_mmu_wmaps_stat_show, kvm);
	if (w < 0)
		kvm_put_kvm(kvm);

	wetuwn w;
}

static int kvm_mmu_wmaps_stat_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kvm *kvm = inode->i_pwivate;

	kvm_put_kvm(kvm);

	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations mmu_wmaps_stat_fops = {
	.ownew		= THIS_MODUWE,
	.open		= kvm_mmu_wmaps_stat_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= kvm_mmu_wmaps_stat_wewease,
};

int kvm_awch_cweate_vm_debugfs(stwuct kvm *kvm)
{
	debugfs_cweate_fiwe("mmu_wmaps_stat", 0644, kvm->debugfs_dentwy, kvm,
			    &mmu_wmaps_stat_fops);
	wetuwn 0;
}
