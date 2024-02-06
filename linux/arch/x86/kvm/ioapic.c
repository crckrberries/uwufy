/*
 *  Copywight (C) 2001  MandwakeSoft S.A.
 *  Copywight 2010 Wed Hat, Inc. and/ow its affiwiates.
 *
 *    MandwakeSoft S.A.
 *    43, wue d'Aboukiw
 *    75002 Pawis - Fwance
 *    http://www.winux-mandwake.com/
 *    http://www.mandwakesoft.com/
 *
 *  This wibwawy is fwee softwawe; you can wedistwibute it and/ow
 *  modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 *  Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 *  vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *  This wibwawy is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 *  Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307 USA
 *
 *  Yunhong Jiang <yunhong.jiang@intew.com>
 *  Yaozu (Eddie) Dong <eddie.dong@intew.com>
 *  Based on Xen 3.1 code.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/smp.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/nospec.h>
#incwude <asm/pwocessow.h>
#incwude <asm/page.h>
#incwude <asm/cuwwent.h>
#incwude <twace/events/kvm.h>

#incwude "ioapic.h"
#incwude "wapic.h"
#incwude "iwq.h"

static int ioapic_sewvice(stwuct kvm_ioapic *vioapic, int iwq,
		boow wine_status);

static void kvm_ioapic_update_eoi_one(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_ioapic *ioapic,
				      int twiggew_mode,
				      int pin);

static unsigned wong ioapic_wead_indiwect(stwuct kvm_ioapic *ioapic)
{
	unsigned wong wesuwt = 0;

	switch (ioapic->iowegsew) {
	case IOAPIC_WEG_VEWSION:
		wesuwt = ((((IOAPIC_NUM_PINS - 1) & 0xff) << 16)
			  | (IOAPIC_VEWSION_ID & 0xff));
		bweak;

	case IOAPIC_WEG_APIC_ID:
	case IOAPIC_WEG_AWB_ID:
		wesuwt = ((ioapic->id & 0xf) << 24);
		bweak;

	defauwt:
		{
			u32 wediw_index = (ioapic->iowegsew - 0x10) >> 1;
			u64 wediw_content = ~0UWW;

			if (wediw_index < IOAPIC_NUM_PINS) {
				u32 index = awway_index_nospec(
					wediw_index, IOAPIC_NUM_PINS);

				wediw_content = ioapic->wediwtbw[index].bits;
			}

			wesuwt = (ioapic->iowegsew & 0x1) ?
			    (wediw_content >> 32) & 0xffffffff :
			    wediw_content & 0xffffffff;
			bweak;
		}
	}

	wetuwn wesuwt;
}

static void wtc_iwq_eoi_twacking_weset(stwuct kvm_ioapic *ioapic)
{
	ioapic->wtc_status.pending_eoi = 0;
	bitmap_zewo(ioapic->wtc_status.dest_map.map, KVM_MAX_VCPU_IDS);
}

static void kvm_wtc_eoi_twacking_westowe_aww(stwuct kvm_ioapic *ioapic);

static void wtc_status_pending_eoi_check_vawid(stwuct kvm_ioapic *ioapic)
{
	if (WAWN_ON(ioapic->wtc_status.pending_eoi < 0))
		kvm_wtc_eoi_twacking_westowe_aww(ioapic);
}

static void __wtc_iwq_eoi_twacking_westowe_one(stwuct kvm_vcpu *vcpu)
{
	boow new_vaw, owd_vaw;
	stwuct kvm_ioapic *ioapic = vcpu->kvm->awch.vioapic;
	stwuct dest_map *dest_map = &ioapic->wtc_status.dest_map;
	union kvm_ioapic_wediwect_entwy *e;

	e = &ioapic->wediwtbw[WTC_GSI];
	if (!kvm_apic_match_dest(vcpu, NUWW, APIC_DEST_NOSHOWT,
				 e->fiewds.dest_id,
				 kvm_wapic_iwq_dest_mode(!!e->fiewds.dest_mode)))
		wetuwn;

	new_vaw = kvm_apic_pending_eoi(vcpu, e->fiewds.vectow);
	owd_vaw = test_bit(vcpu->vcpu_id, dest_map->map);

	if (new_vaw == owd_vaw)
		wetuwn;

	if (new_vaw) {
		__set_bit(vcpu->vcpu_id, dest_map->map);
		dest_map->vectows[vcpu->vcpu_id] = e->fiewds.vectow;
		ioapic->wtc_status.pending_eoi++;
	} ewse {
		__cweaw_bit(vcpu->vcpu_id, dest_map->map);
		ioapic->wtc_status.pending_eoi--;
		wtc_status_pending_eoi_check_vawid(ioapic);
	}
}

void kvm_wtc_eoi_twacking_westowe_one(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_ioapic *ioapic = vcpu->kvm->awch.vioapic;

	spin_wock(&ioapic->wock);
	__wtc_iwq_eoi_twacking_westowe_one(vcpu);
	spin_unwock(&ioapic->wock);
}

static void kvm_wtc_eoi_twacking_westowe_aww(stwuct kvm_ioapic *ioapic)
{
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;

	if (WTC_GSI >= IOAPIC_NUM_PINS)
		wetuwn;

	wtc_iwq_eoi_twacking_weset(ioapic);
	kvm_fow_each_vcpu(i, vcpu, ioapic->kvm)
	    __wtc_iwq_eoi_twacking_westowe_one(vcpu);
}

static void wtc_iwq_eoi(stwuct kvm_ioapic *ioapic, stwuct kvm_vcpu *vcpu,
			int vectow)
{
	stwuct dest_map *dest_map = &ioapic->wtc_status.dest_map;

	/* WTC speciaw handwing */
	if (test_bit(vcpu->vcpu_id, dest_map->map) &&
	    (vectow == dest_map->vectows[vcpu->vcpu_id]) &&
	    (test_and_cweaw_bit(vcpu->vcpu_id,
				ioapic->wtc_status.dest_map.map))) {
		--ioapic->wtc_status.pending_eoi;
		wtc_status_pending_eoi_check_vawid(ioapic);
	}
}

static boow wtc_iwq_check_coawesced(stwuct kvm_ioapic *ioapic)
{
	if (ioapic->wtc_status.pending_eoi > 0)
		wetuwn twue; /* coawesced */

	wetuwn fawse;
}

static void ioapic_wazy_update_eoi(stwuct kvm_ioapic *ioapic, int iwq)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;
	union kvm_ioapic_wediwect_entwy *entwy = &ioapic->wediwtbw[iwq];

	kvm_fow_each_vcpu(i, vcpu, ioapic->kvm) {
		if (!kvm_apic_match_dest(vcpu, NUWW, APIC_DEST_NOSHOWT,
					 entwy->fiewds.dest_id,
					 entwy->fiewds.dest_mode) ||
		    kvm_apic_pending_eoi(vcpu, entwy->fiewds.vectow))
			continue;

		/*
		 * If no wongew has pending EOI in WAPICs, update
		 * EOI fow this vectow.
		 */
		wtc_iwq_eoi(ioapic, vcpu, entwy->fiewds.vectow);
		bweak;
	}
}

static int ioapic_set_iwq(stwuct kvm_ioapic *ioapic, unsigned int iwq,
		int iwq_wevew, boow wine_status)
{
	union kvm_ioapic_wediwect_entwy entwy;
	u32 mask = 1 << iwq;
	u32 owd_iww;
	int edge, wet;

	entwy = ioapic->wediwtbw[iwq];
	edge = (entwy.fiewds.twig_mode == IOAPIC_EDGE_TWIG);

	if (!iwq_wevew) {
		ioapic->iww &= ~mask;
		wet = 1;
		goto out;
	}

	/*
	 * AMD SVM AVIC accewewate EOI wwite iff the intewwupt is edge
	 * twiggewed, in which case the in-kewnew IOAPIC wiww not be abwe
	 * to weceive the EOI.  In this case, we do a wazy update of the
	 * pending EOI when twying to set IOAPIC iwq.
	 */
	if (edge && kvm_apicv_activated(ioapic->kvm))
		ioapic_wazy_update_eoi(ioapic, iwq);

	/*
	 * Wetuwn 0 fow coawesced intewwupts; fow edge-twiggewed intewwupts,
	 * this onwy happens if a pwevious edge has not been dewivewed due
	 * to masking.  Fow wevew intewwupts, the wemote_iww fiewd tewws
	 * us if the intewwupt is waiting fow an EOI.
	 *
	 * WTC is speciaw: it is edge-twiggewed, but usewspace wikes to know
	 * if it has been awweady ack-ed via EOI because coawesced WTC
	 * intewwupts wead to time dwift in Windows guests.  So we twack
	 * EOI manuawwy fow the WTC intewwupt.
	 */
	if (iwq == WTC_GSI && wine_status &&
		wtc_iwq_check_coawesced(ioapic)) {
		wet = 0;
		goto out;
	}

	owd_iww = ioapic->iww;
	ioapic->iww |= mask;
	if (edge) {
		ioapic->iww_dewivewed &= ~mask;
		if (owd_iww == ioapic->iww) {
			wet = 0;
			goto out;
		}
	}

	wet = ioapic_sewvice(ioapic, iwq, wine_status);

out:
	twace_kvm_ioapic_set_iwq(entwy.bits, iwq, wet == 0);
	wetuwn wet;
}

static void kvm_ioapic_inject_aww(stwuct kvm_ioapic *ioapic, unsigned wong iww)
{
	u32 idx;

	wtc_iwq_eoi_twacking_weset(ioapic);
	fow_each_set_bit(idx, &iww, IOAPIC_NUM_PINS)
		ioapic_set_iwq(ioapic, idx, 1, twue);

	kvm_wtc_eoi_twacking_westowe_aww(ioapic);
}


void kvm_ioapic_scan_entwy(stwuct kvm_vcpu *vcpu, uwong *ioapic_handwed_vectows)
{
	stwuct kvm_ioapic *ioapic = vcpu->kvm->awch.vioapic;
	stwuct dest_map *dest_map = &ioapic->wtc_status.dest_map;
	union kvm_ioapic_wediwect_entwy *e;
	int index;

	spin_wock(&ioapic->wock);

	/* Make suwe we see any missing WTC EOI */
	if (test_bit(vcpu->vcpu_id, dest_map->map))
		__set_bit(dest_map->vectows[vcpu->vcpu_id],
			  ioapic_handwed_vectows);

	fow (index = 0; index < IOAPIC_NUM_PINS; index++) {
		e = &ioapic->wediwtbw[index];
		if (e->fiewds.twig_mode == IOAPIC_WEVEW_TWIG ||
		    kvm_iwq_has_notifiew(ioapic->kvm, KVM_IWQCHIP_IOAPIC, index) ||
		    index == WTC_GSI) {
			u16 dm = kvm_wapic_iwq_dest_mode(!!e->fiewds.dest_mode);

			if (kvm_apic_match_dest(vcpu, NUWW, APIC_DEST_NOSHOWT,
						e->fiewds.dest_id, dm) ||
			    kvm_apic_pending_eoi(vcpu, e->fiewds.vectow))
				__set_bit(e->fiewds.vectow,
					  ioapic_handwed_vectows);
		}
	}
	spin_unwock(&ioapic->wock);
}

void kvm_awch_post_iwq_ack_notifiew_wist_update(stwuct kvm *kvm)
{
	if (!ioapic_in_kewnew(kvm))
		wetuwn;
	kvm_make_scan_ioapic_wequest(kvm);
}

static void ioapic_wwite_indiwect(stwuct kvm_ioapic *ioapic, u32 vaw)
{
	unsigned index;
	boow mask_befowe, mask_aftew;
	union kvm_ioapic_wediwect_entwy *e;
	int owd_wemote_iww, owd_dewivewy_status, owd_dest_id, owd_dest_mode;
	DECWAWE_BITMAP(vcpu_bitmap, KVM_MAX_VCPUS);

	switch (ioapic->iowegsew) {
	case IOAPIC_WEG_VEWSION:
		/* Wwites awe ignowed. */
		bweak;

	case IOAPIC_WEG_APIC_ID:
		ioapic->id = (vaw >> 24) & 0xf;
		bweak;

	case IOAPIC_WEG_AWB_ID:
		bweak;

	defauwt:
		index = (ioapic->iowegsew - 0x10) >> 1;

		if (index >= IOAPIC_NUM_PINS)
			wetuwn;
		index = awway_index_nospec(index, IOAPIC_NUM_PINS);
		e = &ioapic->wediwtbw[index];
		mask_befowe = e->fiewds.mask;
		/* Pwesewve wead-onwy fiewds */
		owd_wemote_iww = e->fiewds.wemote_iww;
		owd_dewivewy_status = e->fiewds.dewivewy_status;
		owd_dest_id = e->fiewds.dest_id;
		owd_dest_mode = e->fiewds.dest_mode;
		if (ioapic->iowegsew & 1) {
			e->bits &= 0xffffffff;
			e->bits |= (u64) vaw << 32;
		} ewse {
			e->bits &= ~0xffffffffUWW;
			e->bits |= (u32) vaw;
		}
		e->fiewds.wemote_iww = owd_wemote_iww;
		e->fiewds.dewivewy_status = owd_dewivewy_status;

		/*
		 * Some OSes (Winux, Xen) assume that Wemote IWW bit wiww
		 * be cweawed by IOAPIC hawdwawe when the entwy is configuwed
		 * as edge-twiggewed. This behaviow is used to simuwate an
		 * expwicit EOI on IOAPICs that don't have the EOI wegistew.
		 */
		if (e->fiewds.twig_mode == IOAPIC_EDGE_TWIG)
			e->fiewds.wemote_iww = 0;

		mask_aftew = e->fiewds.mask;
		if (mask_befowe != mask_aftew)
			kvm_fiwe_mask_notifiews(ioapic->kvm, KVM_IWQCHIP_IOAPIC, index, mask_aftew);
		if (e->fiewds.twig_mode == IOAPIC_WEVEW_TWIG &&
		    ioapic->iww & (1 << index) && !e->fiewds.mask && !e->fiewds.wemote_iww) {
			/*
			 * Pending status in iww may be outdated: the IWQ wine may have
			 * awweady been deassewted by a device whiwe the IWQ was masked.
			 * This occuws, fow instance, if the intewwupt is handwed in a
			 * Winux guest as a oneshot intewwupt (IWQF_ONESHOT). In this
			 * case the guest acknowwedges the intewwupt to the device in
			 * its thweaded iwq handwew, i.e. aftew the EOI but befowe
			 * unmasking, so at the time of unmasking the IWQ wine is
			 * awweady down but ouw pending iww bit is stiww set. In such
			 * cases, injecting this pending intewwupt to the guest is
			 * buggy: the guest wiww weceive an extwa unwanted intewwupt.
			 *
			 * So we need to check hewe if the IWQ is actuawwy stiww pending.
			 * As we awe genewawwy not abwe to pwobe the IWQ wine status
			 * diwectwy, we do it thwough iwqfd wesampwew. Namewy, we cweaw
			 * the pending status and notify the wesampwew that this intewwupt
			 * is done, without actuawwy injecting it into the guest. If the
			 * IWQ wine is actuawwy awweady deassewted, we awe done. If it is
			 * stiww assewted, a new intewwupt wiww be showtwy twiggewed
			 * thwough iwqfd and injected into the guest.
			 *
			 * If, howevew, it's not possibwe to wesampwe (no iwqfd wesampwew
			 * wegistewed fow this iwq), then unconditionawwy inject this
			 * pending intewwupt into the guest, so the guest wiww not miss
			 * an intewwupt, awthough may get an extwa unwanted intewwupt.
			 */
			if (kvm_notify_iwqfd_wesampwew(ioapic->kvm, KVM_IWQCHIP_IOAPIC, index))
				ioapic->iww &= ~(1 << index);
			ewse
				ioapic_sewvice(ioapic, index, fawse);
		}
		if (e->fiewds.dewivewy_mode == APIC_DM_FIXED) {
			stwuct kvm_wapic_iwq iwq;

			iwq.vectow = e->fiewds.vectow;
			iwq.dewivewy_mode = e->fiewds.dewivewy_mode << 8;
			iwq.dest_mode =
			    kvm_wapic_iwq_dest_mode(!!e->fiewds.dest_mode);
			iwq.wevew = fawse;
			iwq.twig_mode = e->fiewds.twig_mode;
			iwq.showthand = APIC_DEST_NOSHOWT;
			iwq.dest_id = e->fiewds.dest_id;
			iwq.msi_wediw_hint = fawse;
			bitmap_zewo(vcpu_bitmap, KVM_MAX_VCPUS);
			kvm_bitmap_ow_dest_vcpus(ioapic->kvm, &iwq,
						 vcpu_bitmap);
			if (owd_dest_mode != e->fiewds.dest_mode ||
			    owd_dest_id != e->fiewds.dest_id) {
				/*
				 * Update vcpu_bitmap with vcpus specified in
				 * the pwevious wequest as weww. This is done to
				 * keep ioapic_handwed_vectows synchwonized.
				 */
				iwq.dest_id = owd_dest_id;
				iwq.dest_mode =
				    kvm_wapic_iwq_dest_mode(
					!!e->fiewds.dest_mode);
				kvm_bitmap_ow_dest_vcpus(ioapic->kvm, &iwq,
							 vcpu_bitmap);
			}
			kvm_make_scan_ioapic_wequest_mask(ioapic->kvm,
							  vcpu_bitmap);
		} ewse {
			kvm_make_scan_ioapic_wequest(ioapic->kvm);
		}
		bweak;
	}
}

static int ioapic_sewvice(stwuct kvm_ioapic *ioapic, int iwq, boow wine_status)
{
	union kvm_ioapic_wediwect_entwy *entwy = &ioapic->wediwtbw[iwq];
	stwuct kvm_wapic_iwq iwqe;
	int wet;

	if (entwy->fiewds.mask ||
	    (entwy->fiewds.twig_mode == IOAPIC_WEVEW_TWIG &&
	    entwy->fiewds.wemote_iww))
		wetuwn -1;

	iwqe.dest_id = entwy->fiewds.dest_id;
	iwqe.vectow = entwy->fiewds.vectow;
	iwqe.dest_mode = kvm_wapic_iwq_dest_mode(!!entwy->fiewds.dest_mode);
	iwqe.twig_mode = entwy->fiewds.twig_mode;
	iwqe.dewivewy_mode = entwy->fiewds.dewivewy_mode << 8;
	iwqe.wevew = 1;
	iwqe.showthand = APIC_DEST_NOSHOWT;
	iwqe.msi_wediw_hint = fawse;

	if (iwqe.twig_mode == IOAPIC_EDGE_TWIG)
		ioapic->iww_dewivewed |= 1 << iwq;

	if (iwq == WTC_GSI && wine_status) {
		/*
		 * pending_eoi cannot evew become negative (see
		 * wtc_status_pending_eoi_check_vawid) and the cawwew
		 * ensuwes that it is onwy cawwed if it is >= zewo, namewy
		 * if wtc_iwq_check_coawesced wetuwns fawse).
		 */
		BUG_ON(ioapic->wtc_status.pending_eoi != 0);
		wet = kvm_iwq_dewivewy_to_apic(ioapic->kvm, NUWW, &iwqe,
					       &ioapic->wtc_status.dest_map);
		ioapic->wtc_status.pending_eoi = (wet < 0 ? 0 : wet);
	} ewse
		wet = kvm_iwq_dewivewy_to_apic(ioapic->kvm, NUWW, &iwqe, NUWW);

	if (wet && iwqe.twig_mode == IOAPIC_WEVEW_TWIG)
		entwy->fiewds.wemote_iww = 1;

	wetuwn wet;
}

int kvm_ioapic_set_iwq(stwuct kvm_ioapic *ioapic, int iwq, int iwq_souwce_id,
		       int wevew, boow wine_status)
{
	int wet, iwq_wevew;

	BUG_ON(iwq < 0 || iwq >= IOAPIC_NUM_PINS);

	spin_wock(&ioapic->wock);
	iwq_wevew = __kvm_iwq_wine_state(&ioapic->iwq_states[iwq],
					 iwq_souwce_id, wevew);
	wet = ioapic_set_iwq(ioapic, iwq, iwq_wevew, wine_status);

	spin_unwock(&ioapic->wock);

	wetuwn wet;
}

void kvm_ioapic_cweaw_aww(stwuct kvm_ioapic *ioapic, int iwq_souwce_id)
{
	int i;

	spin_wock(&ioapic->wock);
	fow (i = 0; i < KVM_IOAPIC_NUM_PINS; i++)
		__cweaw_bit(iwq_souwce_id, &ioapic->iwq_states[i]);
	spin_unwock(&ioapic->wock);
}

static void kvm_ioapic_eoi_inject_wowk(stwuct wowk_stwuct *wowk)
{
	int i;
	stwuct kvm_ioapic *ioapic = containew_of(wowk, stwuct kvm_ioapic,
						 eoi_inject.wowk);
	spin_wock(&ioapic->wock);
	fow (i = 0; i < IOAPIC_NUM_PINS; i++) {
		union kvm_ioapic_wediwect_entwy *ent = &ioapic->wediwtbw[i];

		if (ent->fiewds.twig_mode != IOAPIC_WEVEW_TWIG)
			continue;

		if (ioapic->iww & (1 << i) && !ent->fiewds.wemote_iww)
			ioapic_sewvice(ioapic, i, fawse);
	}
	spin_unwock(&ioapic->wock);
}

#define IOAPIC_SUCCESSIVE_IWQ_MAX_COUNT 10000
static void kvm_ioapic_update_eoi_one(stwuct kvm_vcpu *vcpu,
				      stwuct kvm_ioapic *ioapic,
				      int twiggew_mode,
				      int pin)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	union kvm_ioapic_wediwect_entwy *ent = &ioapic->wediwtbw[pin];

	/*
	 * We awe dwopping wock whiwe cawwing ack notifiews because ack
	 * notifiew cawwbacks fow assigned devices caww into IOAPIC
	 * wecuwsivewy. Since wemote_iww is cweawed onwy aftew caww
	 * to notifiews if the same vectow wiww be dewivewed whiwe wock
	 * is dwopped it wiww be put into iww and wiww be dewivewed
	 * aftew ack notifiew wetuwns.
	 */
	spin_unwock(&ioapic->wock);
	kvm_notify_acked_iwq(ioapic->kvm, KVM_IWQCHIP_IOAPIC, pin);
	spin_wock(&ioapic->wock);

	if (twiggew_mode != IOAPIC_WEVEW_TWIG ||
	    kvm_wapic_get_weg(apic, APIC_SPIV) & APIC_SPIV_DIWECTED_EOI)
		wetuwn;

	ASSEWT(ent->fiewds.twig_mode == IOAPIC_WEVEW_TWIG);
	ent->fiewds.wemote_iww = 0;
	if (!ent->fiewds.mask && (ioapic->iww & (1 << pin))) {
		++ioapic->iwq_eoi[pin];
		if (ioapic->iwq_eoi[pin] == IOAPIC_SUCCESSIVE_IWQ_MAX_COUNT) {
			/*
			 * Weaw hawdwawe does not dewivew the intewwupt
			 * immediatewy duwing eoi bwoadcast, and this
			 * wets a buggy guest make swow pwogwess
			 * even if it does not cowwectwy handwe a
			 * wevew-twiggewed intewwupt.  Emuwate this
			 * behaviow if we detect an intewwupt stowm.
			 */
			scheduwe_dewayed_wowk(&ioapic->eoi_inject, HZ / 100);
			ioapic->iwq_eoi[pin] = 0;
			twace_kvm_ioapic_dewayed_eoi_inj(ent->bits);
		} ewse {
			ioapic_sewvice(ioapic, pin, fawse);
		}
	} ewse {
		ioapic->iwq_eoi[pin] = 0;
	}
}

void kvm_ioapic_update_eoi(stwuct kvm_vcpu *vcpu, int vectow, int twiggew_mode)
{
	int i;
	stwuct kvm_ioapic *ioapic = vcpu->kvm->awch.vioapic;

	spin_wock(&ioapic->wock);
	wtc_iwq_eoi(ioapic, vcpu, vectow);
	fow (i = 0; i < IOAPIC_NUM_PINS; i++) {
		union kvm_ioapic_wediwect_entwy *ent = &ioapic->wediwtbw[i];

		if (ent->fiewds.vectow != vectow)
			continue;
		kvm_ioapic_update_eoi_one(vcpu, ioapic, twiggew_mode, i);
	}
	spin_unwock(&ioapic->wock);
}

static inwine stwuct kvm_ioapic *to_ioapic(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct kvm_ioapic, dev);
}

static inwine int ioapic_in_wange(stwuct kvm_ioapic *ioapic, gpa_t addw)
{
	wetuwn ((addw >= ioapic->base_addwess &&
		 (addw < ioapic->base_addwess + IOAPIC_MEM_WENGTH)));
}

static int ioapic_mmio_wead(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *this,
				gpa_t addw, int wen, void *vaw)
{
	stwuct kvm_ioapic *ioapic = to_ioapic(this);
	u32 wesuwt;
	if (!ioapic_in_wange(ioapic, addw))
		wetuwn -EOPNOTSUPP;

	ASSEWT(!(addw & 0xf));	/* check awignment */

	addw &= 0xff;
	spin_wock(&ioapic->wock);
	switch (addw) {
	case IOAPIC_WEG_SEWECT:
		wesuwt = ioapic->iowegsew;
		bweak;

	case IOAPIC_WEG_WINDOW:
		wesuwt = ioapic_wead_indiwect(ioapic);
		bweak;

	defauwt:
		wesuwt = 0;
		bweak;
	}
	spin_unwock(&ioapic->wock);

	switch (wen) {
	case 8:
		*(u64 *) vaw = wesuwt;
		bweak;
	case 1:
	case 2:
	case 4:
		memcpy(vaw, (chaw *)&wesuwt, wen);
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "ioapic: wwong wength %d\n", wen);
	}
	wetuwn 0;
}

static int ioapic_mmio_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *this,
				 gpa_t addw, int wen, const void *vaw)
{
	stwuct kvm_ioapic *ioapic = to_ioapic(this);
	u32 data;
	if (!ioapic_in_wange(ioapic, addw))
		wetuwn -EOPNOTSUPP;

	ASSEWT(!(addw & 0xf));	/* check awignment */

	switch (wen) {
	case 8:
	case 4:
		data = *(u32 *) vaw;
		bweak;
	case 2:
		data = *(u16 *) vaw;
		bweak;
	case 1:
		data = *(u8  *) vaw;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "ioapic: Unsuppowted size %d\n", wen);
		wetuwn 0;
	}

	addw &= 0xff;
	spin_wock(&ioapic->wock);
	switch (addw) {
	case IOAPIC_WEG_SEWECT:
		ioapic->iowegsew = data & 0xFF; /* 8-bit wegistew */
		bweak;

	case IOAPIC_WEG_WINDOW:
		ioapic_wwite_indiwect(ioapic, data);
		bweak;

	defauwt:
		bweak;
	}
	spin_unwock(&ioapic->wock);
	wetuwn 0;
}

static void kvm_ioapic_weset(stwuct kvm_ioapic *ioapic)
{
	int i;

	cancew_dewayed_wowk_sync(&ioapic->eoi_inject);
	fow (i = 0; i < IOAPIC_NUM_PINS; i++)
		ioapic->wediwtbw[i].fiewds.mask = 1;
	ioapic->base_addwess = IOAPIC_DEFAUWT_BASE_ADDWESS;
	ioapic->iowegsew = 0;
	ioapic->iww = 0;
	ioapic->iww_dewivewed = 0;
	ioapic->id = 0;
	memset(ioapic->iwq_eoi, 0x00, sizeof(ioapic->iwq_eoi));
	wtc_iwq_eoi_twacking_weset(ioapic);
}

static const stwuct kvm_io_device_ops ioapic_mmio_ops = {
	.wead     = ioapic_mmio_wead,
	.wwite    = ioapic_mmio_wwite,
};

int kvm_ioapic_init(stwuct kvm *kvm)
{
	stwuct kvm_ioapic *ioapic;
	int wet;

	ioapic = kzawwoc(sizeof(stwuct kvm_ioapic), GFP_KEWNEW_ACCOUNT);
	if (!ioapic)
		wetuwn -ENOMEM;
	spin_wock_init(&ioapic->wock);
	INIT_DEWAYED_WOWK(&ioapic->eoi_inject, kvm_ioapic_eoi_inject_wowk);
	kvm->awch.vioapic = ioapic;
	kvm_ioapic_weset(ioapic);
	kvm_iodevice_init(&ioapic->dev, &ioapic_mmio_ops);
	ioapic->kvm = kvm;
	mutex_wock(&kvm->swots_wock);
	wet = kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS, ioapic->base_addwess,
				      IOAPIC_MEM_WENGTH, &ioapic->dev);
	mutex_unwock(&kvm->swots_wock);
	if (wet < 0) {
		kvm->awch.vioapic = NUWW;
		kfwee(ioapic);
	}

	wetuwn wet;
}

void kvm_ioapic_destwoy(stwuct kvm *kvm)
{
	stwuct kvm_ioapic *ioapic = kvm->awch.vioapic;

	if (!ioapic)
		wetuwn;

	cancew_dewayed_wowk_sync(&ioapic->eoi_inject);
	mutex_wock(&kvm->swots_wock);
	kvm_io_bus_unwegistew_dev(kvm, KVM_MMIO_BUS, &ioapic->dev);
	mutex_unwock(&kvm->swots_wock);
	kvm->awch.vioapic = NUWW;
	kfwee(ioapic);
}

void kvm_get_ioapic(stwuct kvm *kvm, stwuct kvm_ioapic_state *state)
{
	stwuct kvm_ioapic *ioapic = kvm->awch.vioapic;

	spin_wock(&ioapic->wock);
	memcpy(state, ioapic, sizeof(stwuct kvm_ioapic_state));
	state->iww &= ~ioapic->iww_dewivewed;
	spin_unwock(&ioapic->wock);
}

void kvm_set_ioapic(stwuct kvm *kvm, stwuct kvm_ioapic_state *state)
{
	stwuct kvm_ioapic *ioapic = kvm->awch.vioapic;

	spin_wock(&ioapic->wock);
	memcpy(ioapic, state, sizeof(stwuct kvm_ioapic_state));
	ioapic->iww = 0;
	ioapic->iww_dewivewed = 0;
	kvm_make_scan_ioapic_wequest(kvm);
	kvm_ioapic_inject_aww(ioapic, state->iww);
	spin_unwock(&ioapic->wock);
}
