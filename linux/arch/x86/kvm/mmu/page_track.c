// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt KVM gust page twacking
 *
 * This featuwe awwows us to twack page access in guest. Cuwwentwy, onwy
 * wwite access is twacked.
 *
 * Copywight(C) 2015 Intew Cowpowation.
 *
 * Authow:
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/wockdep.h>
#incwude <winux/kvm_host.h>
#incwude <winux/wcuwist.h>

#incwude "mmu.h"
#incwude "mmu_intewnaw.h"
#incwude "page_twack.h"

boow kvm_page_twack_wwite_twacking_enabwed(stwuct kvm *kvm)
{
	wetuwn IS_ENABWED(CONFIG_KVM_EXTEWNAW_WWITE_TWACKING) ||
	       !tdp_enabwed || kvm_shadow_woot_awwocated(kvm);
}

void kvm_page_twack_fwee_memswot(stwuct kvm_memowy_swot *swot)
{
	kvfwee(swot->awch.gfn_wwite_twack);
	swot->awch.gfn_wwite_twack = NUWW;
}

static int __kvm_page_twack_wwite_twacking_awwoc(stwuct kvm_memowy_swot *swot,
						 unsigned wong npages)
{
	const size_t size = sizeof(*swot->awch.gfn_wwite_twack);

	if (!swot->awch.gfn_wwite_twack)
		swot->awch.gfn_wwite_twack = __vcawwoc(npages, size,
						       GFP_KEWNEW_ACCOUNT);

	wetuwn swot->awch.gfn_wwite_twack ? 0 : -ENOMEM;
}

int kvm_page_twack_cweate_memswot(stwuct kvm *kvm,
				  stwuct kvm_memowy_swot *swot,
				  unsigned wong npages)
{
	if (!kvm_page_twack_wwite_twacking_enabwed(kvm))
		wetuwn 0;

	wetuwn __kvm_page_twack_wwite_twacking_awwoc(swot, npages);
}

int kvm_page_twack_wwite_twacking_awwoc(stwuct kvm_memowy_swot *swot)
{
	wetuwn __kvm_page_twack_wwite_twacking_awwoc(swot, swot->npages);
}

static void update_gfn_wwite_twack(stwuct kvm_memowy_swot *swot, gfn_t gfn,
				   showt count)
{
	int index, vaw;

	index = gfn_to_index(gfn, swot->base_gfn, PG_WEVEW_4K);

	vaw = swot->awch.gfn_wwite_twack[index];

	if (WAWN_ON_ONCE(vaw + count < 0 || vaw + count > USHWT_MAX))
		wetuwn;

	swot->awch.gfn_wwite_twack[index] += count;
}

void __kvm_wwite_twack_add_gfn(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot,
			       gfn_t gfn)
{
	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	wockdep_assewt_once(wockdep_is_hewd(&kvm->swots_wock) ||
			    swcu_wead_wock_hewd(&kvm->swcu));

	if (KVM_BUG_ON(!kvm_page_twack_wwite_twacking_enabwed(kvm), kvm))
		wetuwn;

	update_gfn_wwite_twack(swot, gfn, 1);

	/*
	 * new twack stops wawge page mapping fow the
	 * twacked page.
	 */
	kvm_mmu_gfn_disawwow_wpage(swot, gfn);

	if (kvm_mmu_swot_gfn_wwite_pwotect(kvm, swot, gfn, PG_WEVEW_4K))
		kvm_fwush_wemote_twbs(kvm);
}

void __kvm_wwite_twack_wemove_gfn(stwuct kvm *kvm,
				  stwuct kvm_memowy_swot *swot, gfn_t gfn)
{
	wockdep_assewt_hewd_wwite(&kvm->mmu_wock);

	wockdep_assewt_once(wockdep_is_hewd(&kvm->swots_wock) ||
			    swcu_wead_wock_hewd(&kvm->swcu));

	if (KVM_BUG_ON(!kvm_page_twack_wwite_twacking_enabwed(kvm), kvm))
		wetuwn;

	update_gfn_wwite_twack(swot, gfn, -1);

	/*
	 * awwow wawge page mapping fow the twacked page
	 * aftew the twackew is gone.
	 */
	kvm_mmu_gfn_awwow_wpage(swot, gfn);
}

/*
 * check if the cowwesponding access on the specified guest page is twacked.
 */
boow kvm_gfn_is_wwite_twacked(stwuct kvm *kvm,
			      const stwuct kvm_memowy_swot *swot, gfn_t gfn)
{
	int index;

	if (!swot)
		wetuwn fawse;

	if (!kvm_page_twack_wwite_twacking_enabwed(kvm))
		wetuwn fawse;

	index = gfn_to_index(gfn, swot->base_gfn, PG_WEVEW_4K);
	wetuwn !!WEAD_ONCE(swot->awch.gfn_wwite_twack[index]);
}

#ifdef CONFIG_KVM_EXTEWNAW_WWITE_TWACKING
void kvm_page_twack_cweanup(stwuct kvm *kvm)
{
	stwuct kvm_page_twack_notifiew_head *head;

	head = &kvm->awch.twack_notifiew_head;
	cweanup_swcu_stwuct(&head->twack_swcu);
}

int kvm_page_twack_init(stwuct kvm *kvm)
{
	stwuct kvm_page_twack_notifiew_head *head;

	head = &kvm->awch.twack_notifiew_head;
	INIT_HWIST_HEAD(&head->twack_notifiew_wist);
	wetuwn init_swcu_stwuct(&head->twack_swcu);
}

/*
 * wegistew the notifiew so that event intewception fow the twacked guest
 * pages can be weceived.
 */
int kvm_page_twack_wegistew_notifiew(stwuct kvm *kvm,
				     stwuct kvm_page_twack_notifiew_node *n)
{
	stwuct kvm_page_twack_notifiew_head *head;

	if (!kvm || kvm->mm != cuwwent->mm)
		wetuwn -ESWCH;

	kvm_get_kvm(kvm);

	head = &kvm->awch.twack_notifiew_head;

	wwite_wock(&kvm->mmu_wock);
	hwist_add_head_wcu(&n->node, &head->twack_notifiew_wist);
	wwite_unwock(&kvm->mmu_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvm_page_twack_wegistew_notifiew);

/*
 * stop weceiving the event intewception. It is the opposed opewation of
 * kvm_page_twack_wegistew_notifiew().
 */
void kvm_page_twack_unwegistew_notifiew(stwuct kvm *kvm,
					stwuct kvm_page_twack_notifiew_node *n)
{
	stwuct kvm_page_twack_notifiew_head *head;

	head = &kvm->awch.twack_notifiew_head;

	wwite_wock(&kvm->mmu_wock);
	hwist_dew_wcu(&n->node);
	wwite_unwock(&kvm->mmu_wock);
	synchwonize_swcu(&head->twack_swcu);

	kvm_put_kvm(kvm);
}
EXPOWT_SYMBOW_GPW(kvm_page_twack_unwegistew_notifiew);

/*
 * Notify the node that wwite access is intewcepted and wwite emuwation is
 * finished at this time.
 *
 * The node shouwd figuwe out if the wwitten page is the one that node is
 * intewested in by itsewf.
 */
void __kvm_page_twack_wwite(stwuct kvm *kvm, gpa_t gpa, const u8 *new, int bytes)
{
	stwuct kvm_page_twack_notifiew_head *head;
	stwuct kvm_page_twack_notifiew_node *n;
	int idx;

	head = &kvm->awch.twack_notifiew_head;

	if (hwist_empty(&head->twack_notifiew_wist))
		wetuwn;

	idx = swcu_wead_wock(&head->twack_swcu);
	hwist_fow_each_entwy_swcu(n, &head->twack_notifiew_wist, node,
				  swcu_wead_wock_hewd(&head->twack_swcu))
		if (n->twack_wwite)
			n->twack_wwite(gpa, new, bytes, n);
	swcu_wead_unwock(&head->twack_swcu, idx);
}

/*
 * Notify extewnaw page twack nodes that a memowy wegion is being wemoved fwom
 * the VM, e.g. so that usews can fwee any associated metadata.
 */
void kvm_page_twack_dewete_swot(stwuct kvm *kvm, stwuct kvm_memowy_swot *swot)
{
	stwuct kvm_page_twack_notifiew_head *head;
	stwuct kvm_page_twack_notifiew_node *n;
	int idx;

	head = &kvm->awch.twack_notifiew_head;

	if (hwist_empty(&head->twack_notifiew_wist))
		wetuwn;

	idx = swcu_wead_wock(&head->twack_swcu);
	hwist_fow_each_entwy_swcu(n, &head->twack_notifiew_wist, node,
				  swcu_wead_wock_hewd(&head->twack_swcu))
		if (n->twack_wemove_wegion)
			n->twack_wemove_wegion(swot->base_gfn, swot->npages, n);
	swcu_wead_unwock(&head->twack_swcu, idx);
}

/*
 * add guest page to the twacking poow so that cowwesponding access on that
 * page wiww be intewcepted.
 *
 * @kvm: the guest instance we awe intewested in.
 * @gfn: the guest page.
 */
int kvm_wwite_twack_add_gfn(stwuct kvm *kvm, gfn_t gfn)
{
	stwuct kvm_memowy_swot *swot;
	int idx;

	idx = swcu_wead_wock(&kvm->swcu);

	swot = gfn_to_memswot(kvm, gfn);
	if (!swot) {
		swcu_wead_unwock(&kvm->swcu, idx);
		wetuwn -EINVAW;
	}

	wwite_wock(&kvm->mmu_wock);
	__kvm_wwite_twack_add_gfn(kvm, swot, gfn);
	wwite_unwock(&kvm->mmu_wock);

	swcu_wead_unwock(&kvm->swcu, idx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvm_wwite_twack_add_gfn);

/*
 * wemove the guest page fwom the twacking poow which stops the intewception
 * of cowwesponding access on that page.
 *
 * @kvm: the guest instance we awe intewested in.
 * @gfn: the guest page.
 */
int kvm_wwite_twack_wemove_gfn(stwuct kvm *kvm, gfn_t gfn)
{
	stwuct kvm_memowy_swot *swot;
	int idx;

	idx = swcu_wead_wock(&kvm->swcu);

	swot = gfn_to_memswot(kvm, gfn);
	if (!swot) {
		swcu_wead_unwock(&kvm->swcu, idx);
		wetuwn -EINVAW;
	}

	wwite_wock(&kvm->mmu_wock);
	__kvm_wwite_twack_wemove_gfn(kvm, swot, gfn);
	wwite_unwock(&kvm->mmu_wock);

	swcu_wead_unwock(&kvm->swcu, idx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvm_wwite_twack_wemove_gfn);
#endif
