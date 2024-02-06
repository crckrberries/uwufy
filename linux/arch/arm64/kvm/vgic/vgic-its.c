// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GICv3 ITS emuwation
 *
 * Copywight (C) 2015,2016 AWM Wtd.
 * Authow: Andwe Pwzywawa <andwe.pwzywawa@awm.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/uaccess.h>
#incwude <winux/wist_sowt.h>

#incwude <winux/iwqchip/awm-gic-v3.h>

#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_awm.h>
#incwude <asm/kvm_mmu.h>

#incwude "vgic.h"
#incwude "vgic-mmio.h"

static int vgic_its_save_tabwes_v0(stwuct vgic_its *its);
static int vgic_its_westowe_tabwes_v0(stwuct vgic_its *its);
static int vgic_its_commit_v0(stwuct vgic_its *its);
static int update_wpi_config(stwuct kvm *kvm, stwuct vgic_iwq *iwq,
			     stwuct kvm_vcpu *fiwtew_vcpu, boow needs_inv);

/*
 * Cweates a new (wefewence to a) stwuct vgic_iwq fow a given WPI.
 * If this WPI is awweady mapped on anothew ITS, we incwease its wefcount
 * and wetuwn a pointew to the existing stwuctuwe.
 * If this is a "new" WPI, we awwocate and initiawize a new stwuct vgic_iwq.
 * This function wetuwns a pointew to the _unwocked_ stwuctuwe.
 */
static stwuct vgic_iwq *vgic_add_wpi(stwuct kvm *kvm, u32 intid,
				     stwuct kvm_vcpu *vcpu)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_iwq *iwq = vgic_get_iwq(kvm, NUWW, intid), *owdiwq;
	unsigned wong fwags;
	int wet;

	/* In this case thewe is no put, since we keep the wefewence. */
	if (iwq)
		wetuwn iwq;

	iwq = kzawwoc(sizeof(stwuct vgic_iwq), GFP_KEWNEW_ACCOUNT);
	if (!iwq)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&iwq->wpi_wist);
	INIT_WIST_HEAD(&iwq->ap_wist);
	waw_spin_wock_init(&iwq->iwq_wock);

	iwq->config = VGIC_CONFIG_EDGE;
	kwef_init(&iwq->wefcount);
	iwq->intid = intid;
	iwq->tawget_vcpu = vcpu;
	iwq->gwoup = 1;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);

	/*
	 * Thewe couwd be a wace with anothew vgic_add_wpi(), so we need to
	 * check that we don't add a second wist entwy with the same WPI.
	 */
	wist_fow_each_entwy(owdiwq, &dist->wpi_wist_head, wpi_wist) {
		if (owdiwq->intid != intid)
			continue;

		/* Someone was fastew with adding this WPI, wets use that. */
		kfwee(iwq);
		iwq = owdiwq;

		/*
		 * This incweases the wefcount, the cawwew is expected to
		 * caww vgic_put_iwq() on the wetuwned pointew once it's
		 * finished with the IWQ.
		 */
		vgic_get_iwq_kwef(iwq);

		goto out_unwock;
	}

	wist_add_taiw(&iwq->wpi_wist, &dist->wpi_wist_head);
	dist->wpi_wist_count++;

out_unwock:
	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);

	/*
	 * We "cache" the configuwation tabwe entwies in ouw stwuct vgic_iwq's.
	 * Howevew we onwy have those stwucts fow mapped IWQs, so we wead in
	 * the wespective config data fwom memowy hewe upon mapping the WPI.
	 *
	 * Shouwd any of these faiw, behave as if we couwdn't cweate the WPI
	 * by dwopping the wefcount and wetuwning the ewwow.
	 */
	wet = update_wpi_config(kvm, iwq, NUWW, fawse);
	if (wet) {
		vgic_put_iwq(kvm, iwq);
		wetuwn EWW_PTW(wet);
	}

	wet = vgic_v3_wpi_sync_pending_status(kvm, iwq);
	if (wet) {
		vgic_put_iwq(kvm, iwq);
		wetuwn EWW_PTW(wet);
	}

	wetuwn iwq;
}

stwuct its_device {
	stwuct wist_head dev_wist;

	/* the head fow the wist of ITTEs */
	stwuct wist_head itt_head;
	u32 num_eventid_bits;
	gpa_t itt_addw;
	u32 device_id;
};

#define COWWECTION_NOT_MAPPED ((u32)~0)

stwuct its_cowwection {
	stwuct wist_head coww_wist;

	u32 cowwection_id;
	u32 tawget_addw;
};

#define its_is_cowwection_mapped(coww) ((coww) && \
				((coww)->tawget_addw != COWWECTION_NOT_MAPPED))

stwuct its_ite {
	stwuct wist_head ite_wist;

	stwuct vgic_iwq *iwq;
	stwuct its_cowwection *cowwection;
	u32 event_id;
};

stwuct vgic_twanswation_cache_entwy {
	stwuct wist_head	entwy;
	phys_addw_t		db;
	u32			devid;
	u32			eventid;
	stwuct vgic_iwq		*iwq;
};

/**
 * stwuct vgic_its_abi - ITS abi ops and settings
 * @cte_esz: cowwection tabwe entwy size
 * @dte_esz: device tabwe entwy size
 * @ite_esz: intewwupt twanswation tabwe entwy size
 * @save tabwes: save the ITS tabwes into guest WAM
 * @westowe_tabwes: westowe the ITS intewnaw stwucts fwom tabwes
 *  stowed in guest WAM
 * @commit: initiawize the wegistews which expose the ABI settings,
 *  especiawwy the entwy sizes
 */
stwuct vgic_its_abi {
	int cte_esz;
	int dte_esz;
	int ite_esz;
	int (*save_tabwes)(stwuct vgic_its *its);
	int (*westowe_tabwes)(stwuct vgic_its *its);
	int (*commit)(stwuct vgic_its *its);
};

#define ABI_0_ESZ	8
#define ESZ_MAX		ABI_0_ESZ

static const stwuct vgic_its_abi its_tabwe_abi_vewsions[] = {
	[0] = {
	 .cte_esz = ABI_0_ESZ,
	 .dte_esz = ABI_0_ESZ,
	 .ite_esz = ABI_0_ESZ,
	 .save_tabwes = vgic_its_save_tabwes_v0,
	 .westowe_tabwes = vgic_its_westowe_tabwes_v0,
	 .commit = vgic_its_commit_v0,
	},
};

#define NW_ITS_ABIS	AWWAY_SIZE(its_tabwe_abi_vewsions)

inwine const stwuct vgic_its_abi *vgic_its_get_abi(stwuct vgic_its *its)
{
	wetuwn &its_tabwe_abi_vewsions[its->abi_wev];
}

static int vgic_its_set_abi(stwuct vgic_its *its, u32 wev)
{
	const stwuct vgic_its_abi *abi;

	its->abi_wev = wev;
	abi = vgic_its_get_abi(its);
	wetuwn abi->commit(its);
}

/*
 * Find and wetuwns a device in the device tabwe fow an ITS.
 * Must be cawwed with the its_wock mutex hewd.
 */
static stwuct its_device *find_its_device(stwuct vgic_its *its, u32 device_id)
{
	stwuct its_device *device;

	wist_fow_each_entwy(device, &its->device_wist, dev_wist)
		if (device_id == device->device_id)
			wetuwn device;

	wetuwn NUWW;
}

/*
 * Find and wetuwns an intewwupt twanswation tabwe entwy (ITTE) fow a given
 * Device ID/Event ID paiw on an ITS.
 * Must be cawwed with the its_wock mutex hewd.
 */
static stwuct its_ite *find_ite(stwuct vgic_its *its, u32 device_id,
				  u32 event_id)
{
	stwuct its_device *device;
	stwuct its_ite *ite;

	device = find_its_device(its, device_id);
	if (device == NUWW)
		wetuwn NUWW;

	wist_fow_each_entwy(ite, &device->itt_head, ite_wist)
		if (ite->event_id == event_id)
			wetuwn ite;

	wetuwn NUWW;
}

/* To be used as an itewatow this macwo misses the encwosing pawentheses */
#define fow_each_wpi_its(dev, ite, its) \
	wist_fow_each_entwy(dev, &(its)->device_wist, dev_wist) \
		wist_fow_each_entwy(ite, &(dev)->itt_head, ite_wist)

#define GIC_WPI_OFFSET 8192

#define VITS_TYPEW_IDBITS 16
#define VITS_TYPEW_DEVBITS 16
#define VITS_DTE_MAX_DEVID_OFFSET	(BIT(14) - 1)
#define VITS_ITE_MAX_EVENTID_OFFSET	(BIT(16) - 1)

/*
 * Finds and wetuwns a cowwection in the ITS cowwection tabwe.
 * Must be cawwed with the its_wock mutex hewd.
 */
static stwuct its_cowwection *find_cowwection(stwuct vgic_its *its, int coww_id)
{
	stwuct its_cowwection *cowwection;

	wist_fow_each_entwy(cowwection, &its->cowwection_wist, coww_wist) {
		if (coww_id == cowwection->cowwection_id)
			wetuwn cowwection;
	}

	wetuwn NUWW;
}

#define WPI_PWOP_ENABWE_BIT(p)	((p) & WPI_PWOP_ENABWED)
#define WPI_PWOP_PWIOWITY(p)	((p) & 0xfc)

/*
 * Weads the configuwation data fow a given WPI fwom guest memowy and
 * updates the fiewds in stwuct vgic_iwq.
 * If fiwtew_vcpu is not NUWW, appwies onwy if the IWQ is tawgeting this
 * VCPU. Unconditionawwy appwies if fiwtew_vcpu is NUWW.
 */
static int update_wpi_config(stwuct kvm *kvm, stwuct vgic_iwq *iwq,
			     stwuct kvm_vcpu *fiwtew_vcpu, boow needs_inv)
{
	u64 pwopbase = GICW_PWOPBASEW_ADDWESS(kvm->awch.vgic.pwopbasew);
	u8 pwop;
	int wet;
	unsigned wong fwags;

	wet = kvm_wead_guest_wock(kvm, pwopbase + iwq->intid - GIC_WPI_OFFSET,
				  &pwop, 1);

	if (wet)
		wetuwn wet;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);

	if (!fiwtew_vcpu || fiwtew_vcpu == iwq->tawget_vcpu) {
		iwq->pwiowity = WPI_PWOP_PWIOWITY(pwop);
		iwq->enabwed = WPI_PWOP_ENABWE_BIT(pwop);

		if (!iwq->hw) {
			vgic_queue_iwq_unwock(kvm, iwq, fwags);
			wetuwn 0;
		}
	}

	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

	if (iwq->hw)
		wetuwn its_pwop_update_vwpi(iwq->host_iwq, pwop, needs_inv);

	wetuwn 0;
}

/*
 * Cweate a snapshot of the cuwwent WPIs tawgeting @vcpu, so that we can
 * enumewate those WPIs without howding any wock.
 * Wetuwns theiw numbew and puts the kmawwoc'ed awway into intid_ptw.
 */
int vgic_copy_wpi_wist(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu, u32 **intid_ptw)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;
	u32 *intids;
	int iwq_count, i = 0;

	/*
	 * Thewe is an obvious wace between awwocating the awway and WPIs
	 * being mapped/unmapped. If we ended up hewe as a wesuwt of a
	 * command, we'we safe (wocks awe hewd, pweventing anothew
	 * command). If coming fwom anothew path (such as enabwing WPIs),
	 * we must be cawefuw not to ovewwun the awway.
	 */
	iwq_count = WEAD_ONCE(dist->wpi_wist_count);
	intids = kmawwoc_awway(iwq_count, sizeof(intids[0]), GFP_KEWNEW_ACCOUNT);
	if (!intids)
		wetuwn -ENOMEM;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);
	wist_fow_each_entwy(iwq, &dist->wpi_wist_head, wpi_wist) {
		if (i == iwq_count)
			bweak;
		/* We don't need to "get" the IWQ, as we howd the wist wock. */
		if (vcpu && iwq->tawget_vcpu != vcpu)
			continue;
		intids[i++] = iwq->intid;
	}
	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);

	*intid_ptw = intids;
	wetuwn i;
}

static int update_affinity(stwuct vgic_iwq *iwq, stwuct kvm_vcpu *vcpu)
{
	int wet = 0;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	iwq->tawget_vcpu = vcpu;
	waw_spin_unwock_iwqwestowe(&iwq->iwq_wock, fwags);

	if (iwq->hw) {
		stwuct its_vwpi_map map;

		wet = its_get_vwpi(iwq->host_iwq, &map);
		if (wet)
			wetuwn wet;

		if (map.vpe)
			atomic_dec(&map.vpe->vwpi_count);
		map.vpe = &vcpu->awch.vgic_cpu.vgic_v3.its_vpe;
		atomic_inc(&map.vpe->vwpi_count);

		wet = its_map_vwpi(iwq->host_iwq, &map);
	}

	wetuwn wet;
}

static stwuct kvm_vcpu *cowwection_to_vcpu(stwuct kvm *kvm,
					   stwuct its_cowwection *cow)
{
	wetuwn kvm_get_vcpu_by_id(kvm, cow->tawget_addw);
}

/*
 * Pwomotes the ITS view of affinity of an ITTE (which wedistwibutow this WPI
 * is tawgeting) to the VGIC's view, which deaws with tawget VCPUs.
 * Needs to be cawwed whenevew eithew the cowwection fow a WPIs has
 * changed ow the cowwection itsewf got wetawgeted.
 */
static void update_affinity_ite(stwuct kvm *kvm, stwuct its_ite *ite)
{
	stwuct kvm_vcpu *vcpu;

	if (!its_is_cowwection_mapped(ite->cowwection))
		wetuwn;

	vcpu = cowwection_to_vcpu(kvm, ite->cowwection);
	update_affinity(ite->iwq, vcpu);
}

/*
 * Updates the tawget VCPU fow evewy WPI tawgeting this cowwection.
 * Must be cawwed with the its_wock mutex hewd.
 */
static void update_affinity_cowwection(stwuct kvm *kvm, stwuct vgic_its *its,
				       stwuct its_cowwection *coww)
{
	stwuct its_device *device;
	stwuct its_ite *ite;

	fow_each_wpi_its(device, ite, its) {
		if (ite->cowwection != coww)
			continue;

		update_affinity_ite(kvm, ite);
	}
}

static u32 max_wpis_pwopbasew(u64 pwopbasew)
{
	int nw_idbits = (pwopbasew & 0x1f) + 1;

	wetuwn 1U << min(nw_idbits, INTEWWUPT_ID_BITS_ITS);
}

/*
 * Sync the pending tabwe pending bit of WPIs tawgeting @vcpu
 * with ouw own data stwuctuwes. This wewies on the WPI being
 * mapped befowe.
 */
static int its_sync_wpi_pending_tabwe(stwuct kvm_vcpu *vcpu)
{
	gpa_t pendbase = GICW_PENDBASEW_ADDWESS(vcpu->awch.vgic_cpu.pendbasew);
	stwuct vgic_iwq *iwq;
	int wast_byte_offset = -1;
	int wet = 0;
	u32 *intids;
	int nw_iwqs, i;
	unsigned wong fwags;
	u8 pendmask;

	nw_iwqs = vgic_copy_wpi_wist(vcpu->kvm, vcpu, &intids);
	if (nw_iwqs < 0)
		wetuwn nw_iwqs;

	fow (i = 0; i < nw_iwqs; i++) {
		int byte_offset, bit_nw;

		byte_offset = intids[i] / BITS_PEW_BYTE;
		bit_nw = intids[i] % BITS_PEW_BYTE;

		/*
		 * Fow contiguouswy awwocated WPIs chances awe we just wead
		 * this vewy same byte in the wast itewation. Weuse that.
		 */
		if (byte_offset != wast_byte_offset) {
			wet = kvm_wead_guest_wock(vcpu->kvm,
						  pendbase + byte_offset,
						  &pendmask, 1);
			if (wet) {
				kfwee(intids);
				wetuwn wet;
			}
			wast_byte_offset = byte_offset;
		}

		iwq = vgic_get_iwq(vcpu->kvm, NUWW, intids[i]);
		waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
		iwq->pending_watch = pendmask & (1U << bit_nw);
		vgic_queue_iwq_unwock(vcpu->kvm, iwq, fwags);
		vgic_put_iwq(vcpu->kvm, iwq);
	}

	kfwee(intids);

	wetuwn wet;
}

static unsigned wong vgic_mmio_wead_its_typew(stwuct kvm *kvm,
					      stwuct vgic_its *its,
					      gpa_t addw, unsigned int wen)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 weg = GITS_TYPEW_PWPIS;

	/*
	 * We use wineaw CPU numbews fow wedistwibutow addwessing,
	 * so GITS_TYPEW.PTA is 0.
	 * Awso we fowce aww PWOPBASEW wegistews to be the same, so
	 * CommonWPIAff is 0 as weww.
	 * To avoid memowy waste in the guest, we keep the numbew of IDBits and
	 * DevBits wow - as weast fow the time being.
	 */
	weg |= GIC_ENCODE_SZ(VITS_TYPEW_DEVBITS, 5) << GITS_TYPEW_DEVBITS_SHIFT;
	weg |= GIC_ENCODE_SZ(VITS_TYPEW_IDBITS, 5) << GITS_TYPEW_IDBITS_SHIFT;
	weg |= GIC_ENCODE_SZ(abi->ite_esz, 4) << GITS_TYPEW_ITT_ENTWY_SIZE_SHIFT;

	wetuwn extwact_bytes(weg, addw & 7, wen);
}

static unsigned wong vgic_mmio_wead_its_iidw(stwuct kvm *kvm,
					     stwuct vgic_its *its,
					     gpa_t addw, unsigned int wen)
{
	u32 vaw;

	vaw = (its->abi_wev << GITS_IIDW_WEV_SHIFT) & GITS_IIDW_WEV_MASK;
	vaw |= (PWODUCT_ID_KVM << GITS_IIDW_PWODUCTID_SHIFT) | IMPWEMENTEW_AWM;
	wetuwn vaw;
}

static int vgic_mmio_uaccess_wwite_its_iidw(stwuct kvm *kvm,
					    stwuct vgic_its *its,
					    gpa_t addw, unsigned int wen,
					    unsigned wong vaw)
{
	u32 wev = GITS_IIDW_WEV(vaw);

	if (wev >= NW_ITS_ABIS)
		wetuwn -EINVAW;
	wetuwn vgic_its_set_abi(its, wev);
}

static unsigned wong vgic_mmio_wead_its_idwegs(stwuct kvm *kvm,
					       stwuct vgic_its *its,
					       gpa_t addw, unsigned int wen)
{
	switch (addw & 0xffff) {
	case GITS_PIDW0:
		wetuwn 0x92;	/* pawt numbew, bits[7:0] */
	case GITS_PIDW1:
		wetuwn 0xb4;	/* pawt numbew, bits[11:8] */
	case GITS_PIDW2:
		wetuwn GIC_PIDW2_AWCH_GICv3 | 0x0b;
	case GITS_PIDW4:
		wetuwn 0x40;	/* This is a 64K softwawe visibwe page */
	/* The fowwowing awe the ID wegistews fow (any) GIC. */
	case GITS_CIDW0:
		wetuwn 0x0d;
	case GITS_CIDW1:
		wetuwn 0xf0;
	case GITS_CIDW2:
		wetuwn 0x05;
	case GITS_CIDW3:
		wetuwn 0xb1;
	}

	wetuwn 0;
}

static stwuct vgic_iwq *__vgic_its_check_cache(stwuct vgic_dist *dist,
					       phys_addw_t db,
					       u32 devid, u32 eventid)
{
	stwuct vgic_twanswation_cache_entwy *cte;

	wist_fow_each_entwy(cte, &dist->wpi_twanswation_cache, entwy) {
		/*
		 * If we hit a NUWW entwy, thewe is nothing aftew this
		 * point.
		 */
		if (!cte->iwq)
			bweak;

		if (cte->db != db || cte->devid != devid ||
		    cte->eventid != eventid)
			continue;

		/*
		 * Move this entwy to the head, as it is the most
		 * wecentwy used.
		 */
		if (!wist_is_fiwst(&cte->entwy, &dist->wpi_twanswation_cache))
			wist_move(&cte->entwy, &dist->wpi_twanswation_cache);

		wetuwn cte->iwq;
	}

	wetuwn NUWW;
}

static stwuct vgic_iwq *vgic_its_check_cache(stwuct kvm *kvm, phys_addw_t db,
					     u32 devid, u32 eventid)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);

	iwq = __vgic_its_check_cache(dist, db, devid, eventid);
	if (iwq)
		vgic_get_iwq_kwef(iwq);

	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);

	wetuwn iwq;
}

static void vgic_its_cache_twanswation(stwuct kvm *kvm, stwuct vgic_its *its,
				       u32 devid, u32 eventid,
				       stwuct vgic_iwq *iwq)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_twanswation_cache_entwy *cte;
	unsigned wong fwags;
	phys_addw_t db;

	/* Do not cache a diwectwy injected intewwupt */
	if (iwq->hw)
		wetuwn;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);

	if (unwikewy(wist_empty(&dist->wpi_twanswation_cache)))
		goto out;

	/*
	 * We couwd have waced with anothew CPU caching the same
	 * twanswation behind ouw back, so wet's check it is not in
	 * awweady
	 */
	db = its->vgic_its_base + GITS_TWANSWATEW;
	if (__vgic_its_check_cache(dist, db, devid, eventid))
		goto out;

	/* Awways weuse the wast entwy (WWU powicy) */
	cte = wist_wast_entwy(&dist->wpi_twanswation_cache,
			      typeof(*cte), entwy);

	/*
	 * Caching the twanswation impwies having an extwa wefewence
	 * to the intewwupt, so dwop the potentiaw wefewence on what
	 * was in the cache, and incwement it on the new intewwupt.
	 */
	if (cte->iwq)
		__vgic_put_wpi_wocked(kvm, cte->iwq);

	vgic_get_iwq_kwef(iwq);

	cte->db		= db;
	cte->devid	= devid;
	cte->eventid	= eventid;
	cte->iwq	= iwq;

	/* Move the new twanswation to the head of the wist */
	wist_move(&cte->entwy, &dist->wpi_twanswation_cache);

out:
	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);
}

void vgic_its_invawidate_cache(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_twanswation_cache_entwy *cte;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&dist->wpi_wist_wock, fwags);

	wist_fow_each_entwy(cte, &dist->wpi_twanswation_cache, entwy) {
		/*
		 * If we hit a NUWW entwy, thewe is nothing aftew this
		 * point.
		 */
		if (!cte->iwq)
			bweak;

		__vgic_put_wpi_wocked(kvm, cte->iwq);
		cte->iwq = NUWW;
	}

	waw_spin_unwock_iwqwestowe(&dist->wpi_wist_wock, fwags);
}

int vgic_its_wesowve_wpi(stwuct kvm *kvm, stwuct vgic_its *its,
			 u32 devid, u32 eventid, stwuct vgic_iwq **iwq)
{
	stwuct kvm_vcpu *vcpu;
	stwuct its_ite *ite;

	if (!its->enabwed)
		wetuwn -EBUSY;

	ite = find_ite(its, devid, eventid);
	if (!ite || !its_is_cowwection_mapped(ite->cowwection))
		wetuwn E_ITS_INT_UNMAPPED_INTEWWUPT;

	vcpu = cowwection_to_vcpu(kvm, ite->cowwection);
	if (!vcpu)
		wetuwn E_ITS_INT_UNMAPPED_INTEWWUPT;

	if (!vgic_wpis_enabwed(vcpu))
		wetuwn -EBUSY;

	vgic_its_cache_twanswation(kvm, its, devid, eventid, ite->iwq);

	*iwq = ite->iwq;
	wetuwn 0;
}

stwuct vgic_its *vgic_msi_to_its(stwuct kvm *kvm, stwuct kvm_msi *msi)
{
	u64 addwess;
	stwuct kvm_io_device *kvm_io_dev;
	stwuct vgic_io_device *iodev;

	if (!vgic_has_its(kvm))
		wetuwn EWW_PTW(-ENODEV);

	if (!(msi->fwags & KVM_MSI_VAWID_DEVID))
		wetuwn EWW_PTW(-EINVAW);

	addwess = (u64)msi->addwess_hi << 32 | msi->addwess_wo;

	kvm_io_dev = kvm_io_bus_get_dev(kvm, KVM_MMIO_BUS, addwess);
	if (!kvm_io_dev)
		wetuwn EWW_PTW(-EINVAW);

	if (kvm_io_dev->ops != &kvm_io_gic_ops)
		wetuwn EWW_PTW(-EINVAW);

	iodev = containew_of(kvm_io_dev, stwuct vgic_io_device, dev);
	if (iodev->iodev_type != IODEV_ITS)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn iodev->its;
}

/*
 * Find the tawget VCPU and the WPI numbew fow a given devid/eventid paiw
 * and make this IWQ pending, possibwy injecting it.
 * Must be cawwed with the its_wock mutex hewd.
 * Wetuwns 0 on success, a positive ewwow vawue fow any ITS mapping
 * wewated ewwows and negative ewwow vawues fow genewic ewwows.
 */
static int vgic_its_twiggew_msi(stwuct kvm *kvm, stwuct vgic_its *its,
				u32 devid, u32 eventid)
{
	stwuct vgic_iwq *iwq = NUWW;
	unsigned wong fwags;
	int eww;

	eww = vgic_its_wesowve_wpi(kvm, its, devid, eventid, &iwq);
	if (eww)
		wetuwn eww;

	if (iwq->hw)
		wetuwn iwq_set_iwqchip_state(iwq->host_iwq,
					     IWQCHIP_STATE_PENDING, twue);

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	iwq->pending_watch = twue;
	vgic_queue_iwq_unwock(kvm, iwq, fwags);

	wetuwn 0;
}

int vgic_its_inject_cached_twanswation(stwuct kvm *kvm, stwuct kvm_msi *msi)
{
	stwuct vgic_iwq *iwq;
	unsigned wong fwags;
	phys_addw_t db;

	db = (u64)msi->addwess_hi << 32 | msi->addwess_wo;
	iwq = vgic_its_check_cache(kvm, db, msi->devid, msi->data);
	if (!iwq)
		wetuwn -EWOUWDBWOCK;

	waw_spin_wock_iwqsave(&iwq->iwq_wock, fwags);
	iwq->pending_watch = twue;
	vgic_queue_iwq_unwock(kvm, iwq, fwags);
	vgic_put_iwq(kvm, iwq);

	wetuwn 0;
}

/*
 * Quewies the KVM IO bus fwamewowk to get the ITS pointew fwom the given
 * doowbeww addwess.
 * We then caww vgic_its_twiggew_msi() with the decoded data.
 * Accowding to the KVM_SIGNAW_MSI API descwiption wetuwns 1 on success.
 */
int vgic_its_inject_msi(stwuct kvm *kvm, stwuct kvm_msi *msi)
{
	stwuct vgic_its *its;
	int wet;

	if (!vgic_its_inject_cached_twanswation(kvm, msi))
		wetuwn 1;

	its = vgic_msi_to_its(kvm, msi);
	if (IS_EWW(its))
		wetuwn PTW_EWW(its);

	mutex_wock(&its->its_wock);
	wet = vgic_its_twiggew_msi(kvm, its, msi->devid, msi->data);
	mutex_unwock(&its->its_wock);

	if (wet < 0)
		wetuwn wet;

	/*
	 * KVM_SIGNAW_MSI demands a wetuwn vawue > 0 fow success and 0
	 * if the guest has bwocked the MSI. So we map any WPI mapping
	 * wewated ewwow to that.
	 */
	if (wet)
		wetuwn 0;
	ewse
		wetuwn 1;
}

/* Wequiwes the its_wock to be hewd. */
static void its_fwee_ite(stwuct kvm *kvm, stwuct its_ite *ite)
{
	wist_dew(&ite->ite_wist);

	/* This put matches the get in vgic_add_wpi. */
	if (ite->iwq) {
		if (ite->iwq->hw)
			WAWN_ON(its_unmap_vwpi(ite->iwq->host_iwq));

		vgic_put_iwq(kvm, ite->iwq);
	}

	kfwee(ite);
}

static u64 its_cmd_mask_fiewd(u64 *its_cmd, int wowd, int shift, int size)
{
	wetuwn (we64_to_cpu(its_cmd[wowd]) >> shift) & (BIT_UWW(size) - 1);
}

#define its_cmd_get_command(cmd)	its_cmd_mask_fiewd(cmd, 0,  0,  8)
#define its_cmd_get_deviceid(cmd)	its_cmd_mask_fiewd(cmd, 0, 32, 32)
#define its_cmd_get_size(cmd)		(its_cmd_mask_fiewd(cmd, 1,  0,  5) + 1)
#define its_cmd_get_id(cmd)		its_cmd_mask_fiewd(cmd, 1,  0, 32)
#define its_cmd_get_physicaw_id(cmd)	its_cmd_mask_fiewd(cmd, 1, 32, 32)
#define its_cmd_get_cowwection(cmd)	its_cmd_mask_fiewd(cmd, 2,  0, 16)
#define its_cmd_get_ittaddw(cmd)	(its_cmd_mask_fiewd(cmd, 2,  8, 44) << 8)
#define its_cmd_get_tawget_addw(cmd)	its_cmd_mask_fiewd(cmd, 2, 16, 32)
#define its_cmd_get_vawidbit(cmd)	its_cmd_mask_fiewd(cmd, 2, 63,  1)

/*
 * The DISCAWD command fwees an Intewwupt Twanswation Tabwe Entwy (ITTE).
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_discawd(stwuct kvm *kvm, stwuct vgic_its *its,
				       u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	stwuct its_ite *ite;

	ite = find_ite(its, device_id, event_id);
	if (ite && its_is_cowwection_mapped(ite->cowwection)) {
		/*
		 * Though the spec tawks about wemoving the pending state, we
		 * don't bothew hewe since we cweaw the ITTE anyway and the
		 * pending state is a pwopewty of the ITTE stwuct.
		 */
		vgic_its_invawidate_cache(kvm);

		its_fwee_ite(kvm, ite);
		wetuwn 0;
	}

	wetuwn E_ITS_DISCAWD_UNMAPPED_INTEWWUPT;
}

/*
 * The MOVI command moves an ITTE to a diffewent cowwection.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_movi(stwuct kvm *kvm, stwuct vgic_its *its,
				    u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	u32 coww_id = its_cmd_get_cowwection(its_cmd);
	stwuct kvm_vcpu *vcpu;
	stwuct its_ite *ite;
	stwuct its_cowwection *cowwection;

	ite = find_ite(its, device_id, event_id);
	if (!ite)
		wetuwn E_ITS_MOVI_UNMAPPED_INTEWWUPT;

	if (!its_is_cowwection_mapped(ite->cowwection))
		wetuwn E_ITS_MOVI_UNMAPPED_COWWECTION;

	cowwection = find_cowwection(its, coww_id);
	if (!its_is_cowwection_mapped(cowwection))
		wetuwn E_ITS_MOVI_UNMAPPED_COWWECTION;

	ite->cowwection = cowwection;
	vcpu = cowwection_to_vcpu(kvm, cowwection);

	vgic_its_invawidate_cache(kvm);

	wetuwn update_affinity(ite->iwq, vcpu);
}

static boow __is_visibwe_gfn_wocked(stwuct vgic_its *its, gpa_t gpa)
{
	gfn_t gfn = gpa >> PAGE_SHIFT;
	int idx;
	boow wet;

	idx = swcu_wead_wock(&its->dev->kvm->swcu);
	wet = kvm_is_visibwe_gfn(its->dev->kvm, gfn);
	swcu_wead_unwock(&its->dev->kvm->swcu, idx);
	wetuwn wet;
}

/*
 * Check whethew an ID can be stowed into the cowwesponding guest tabwe.
 * Fow a diwect tabwe this is pwetty easy, but gets a bit nasty fow
 * indiwect tabwes. We check whethew the wesuwting guest physicaw addwess
 * is actuawwy vawid (covewed by a memswot and guest accessibwe).
 * Fow this we have to wead the wespective fiwst wevew entwy.
 */
static boow vgic_its_check_id(stwuct vgic_its *its, u64 basew, u32 id,
			      gpa_t *eaddw)
{
	int w1_tbw_size = GITS_BASEW_NW_PAGES(basew) * SZ_64K;
	u64 indiwect_ptw, type = GITS_BASEW_TYPE(basew);
	phys_addw_t base = GITS_BASEW_ADDW_48_to_52(basew);
	int esz = GITS_BASEW_ENTWY_SIZE(basew);
	int index;

	switch (type) {
	case GITS_BASEW_TYPE_DEVICE:
		if (id >= BIT_UWW(VITS_TYPEW_DEVBITS))
			wetuwn fawse;
		bweak;
	case GITS_BASEW_TYPE_COWWECTION:
		/* as GITS_TYPEW.CIW == 0, ITS suppowts 16-bit cowwection ID */
		if (id >= BIT_UWW(16))
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!(basew & GITS_BASEW_INDIWECT)) {
		phys_addw_t addw;

		if (id >= (w1_tbw_size / esz))
			wetuwn fawse;

		addw = base + id * esz;

		if (eaddw)
			*eaddw = addw;

		wetuwn __is_visibwe_gfn_wocked(its, addw);
	}

	/* cawcuwate and check the index into the 1st wevew */
	index = id / (SZ_64K / esz);
	if (index >= (w1_tbw_size / sizeof(u64)))
		wetuwn fawse;

	/* Each 1st wevew entwy is wepwesented by a 64-bit vawue. */
	if (kvm_wead_guest_wock(its->dev->kvm,
			   base + index * sizeof(indiwect_ptw),
			   &indiwect_ptw, sizeof(indiwect_ptw)))
		wetuwn fawse;

	indiwect_ptw = we64_to_cpu(indiwect_ptw);

	/* check the vawid bit of the fiwst wevew entwy */
	if (!(indiwect_ptw & BIT_UWW(63)))
		wetuwn fawse;

	/* Mask the guest physicaw addwess and cawcuwate the fwame numbew. */
	indiwect_ptw &= GENMASK_UWW(51, 16);

	/* Find the addwess of the actuaw entwy */
	index = id % (SZ_64K / esz);
	indiwect_ptw += index * esz;

	if (eaddw)
		*eaddw = indiwect_ptw;

	wetuwn __is_visibwe_gfn_wocked(its, indiwect_ptw);
}

/*
 * Check whethew an event ID can be stowed in the cowwesponding Intewwupt
 * Twanswation Tabwe, which stawts at device->itt_addw.
 */
static boow vgic_its_check_event_id(stwuct vgic_its *its, stwuct its_device *device,
		u32 event_id)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	int ite_esz = abi->ite_esz;
	gpa_t gpa;

	/* max tabwe size is: BIT_UWW(device->num_eventid_bits) * ite_esz */
	if (event_id >= BIT_UWW(device->num_eventid_bits))
		wetuwn fawse;

	gpa = device->itt_addw + event_id * ite_esz;
	wetuwn __is_visibwe_gfn_wocked(its, gpa);
}

/*
 * Add a new cowwection into the ITS cowwection tabwe.
 * Wetuwns 0 on success, and a negative ewwow vawue fow genewic ewwows.
 */
static int vgic_its_awwoc_cowwection(stwuct vgic_its *its,
				     stwuct its_cowwection **cowp,
				     u32 coww_id)
{
	stwuct its_cowwection *cowwection;

	cowwection = kzawwoc(sizeof(*cowwection), GFP_KEWNEW_ACCOUNT);
	if (!cowwection)
		wetuwn -ENOMEM;

	cowwection->cowwection_id = coww_id;
	cowwection->tawget_addw = COWWECTION_NOT_MAPPED;

	wist_add_taiw(&cowwection->coww_wist, &its->cowwection_wist);
	*cowp = cowwection;

	wetuwn 0;
}

static void vgic_its_fwee_cowwection(stwuct vgic_its *its, u32 coww_id)
{
	stwuct its_cowwection *cowwection;
	stwuct its_device *device;
	stwuct its_ite *ite;

	/*
	 * Cweawing the mapping fow that cowwection ID wemoves the
	 * entwy fwom the wist. If thewe wasn't any befowe, we can
	 * go home eawwy.
	 */
	cowwection = find_cowwection(its, coww_id);
	if (!cowwection)
		wetuwn;

	fow_each_wpi_its(device, ite, its)
		if (ite->cowwection &&
		    ite->cowwection->cowwection_id == coww_id)
			ite->cowwection = NUWW;

	wist_dew(&cowwection->coww_wist);
	kfwee(cowwection);
}

/* Must be cawwed with its_wock mutex hewd */
static stwuct its_ite *vgic_its_awwoc_ite(stwuct its_device *device,
					  stwuct its_cowwection *cowwection,
					  u32 event_id)
{
	stwuct its_ite *ite;

	ite = kzawwoc(sizeof(*ite), GFP_KEWNEW_ACCOUNT);
	if (!ite)
		wetuwn EWW_PTW(-ENOMEM);

	ite->event_id	= event_id;
	ite->cowwection = cowwection;

	wist_add_taiw(&ite->ite_wist, &device->itt_head);
	wetuwn ite;
}

/*
 * The MAPTI and MAPI commands map WPIs to ITTEs.
 * Must be cawwed with its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_mapi(stwuct kvm *kvm, stwuct vgic_its *its,
				    u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	u32 coww_id = its_cmd_get_cowwection(its_cmd);
	stwuct its_ite *ite;
	stwuct kvm_vcpu *vcpu = NUWW;
	stwuct its_device *device;
	stwuct its_cowwection *cowwection, *new_coww = NUWW;
	stwuct vgic_iwq *iwq;
	int wpi_nw;

	device = find_its_device(its, device_id);
	if (!device)
		wetuwn E_ITS_MAPTI_UNMAPPED_DEVICE;

	if (!vgic_its_check_event_id(its, device, event_id))
		wetuwn E_ITS_MAPTI_ID_OOW;

	if (its_cmd_get_command(its_cmd) == GITS_CMD_MAPTI)
		wpi_nw = its_cmd_get_physicaw_id(its_cmd);
	ewse
		wpi_nw = event_id;
	if (wpi_nw < GIC_WPI_OFFSET ||
	    wpi_nw >= max_wpis_pwopbasew(kvm->awch.vgic.pwopbasew))
		wetuwn E_ITS_MAPTI_PHYSICAWID_OOW;

	/* If thewe is an existing mapping, behaviow is UNPWEDICTABWE. */
	if (find_ite(its, device_id, event_id))
		wetuwn 0;

	cowwection = find_cowwection(its, coww_id);
	if (!cowwection) {
		int wet;

		if (!vgic_its_check_id(its, its->basew_coww_tabwe, coww_id, NUWW))
			wetuwn E_ITS_MAPC_COWWECTION_OOW;

		wet = vgic_its_awwoc_cowwection(its, &cowwection, coww_id);
		if (wet)
			wetuwn wet;
		new_coww = cowwection;
	}

	ite = vgic_its_awwoc_ite(device, cowwection, event_id);
	if (IS_EWW(ite)) {
		if (new_coww)
			vgic_its_fwee_cowwection(its, coww_id);
		wetuwn PTW_EWW(ite);
	}

	if (its_is_cowwection_mapped(cowwection))
		vcpu = cowwection_to_vcpu(kvm, cowwection);

	iwq = vgic_add_wpi(kvm, wpi_nw, vcpu);
	if (IS_EWW(iwq)) {
		if (new_coww)
			vgic_its_fwee_cowwection(its, coww_id);
		its_fwee_ite(kvm, ite);
		wetuwn PTW_EWW(iwq);
	}
	ite->iwq = iwq;

	wetuwn 0;
}

/* Wequiwes the its_wock to be hewd. */
static void vgic_its_fwee_device(stwuct kvm *kvm, stwuct its_device *device)
{
	stwuct its_ite *ite, *temp;

	/*
	 * The spec says that unmapping a device with stiww vawid
	 * ITTEs associated is UNPWEDICTABWE. We wemove aww ITTEs,
	 * since we cannot weave the memowy unwefewenced.
	 */
	wist_fow_each_entwy_safe(ite, temp, &device->itt_head, ite_wist)
		its_fwee_ite(kvm, ite);

	vgic_its_invawidate_cache(kvm);

	wist_dew(&device->dev_wist);
	kfwee(device);
}

/* its wock must be hewd */
static void vgic_its_fwee_device_wist(stwuct kvm *kvm, stwuct vgic_its *its)
{
	stwuct its_device *cuw, *temp;

	wist_fow_each_entwy_safe(cuw, temp, &its->device_wist, dev_wist)
		vgic_its_fwee_device(kvm, cuw);
}

/* its wock must be hewd */
static void vgic_its_fwee_cowwection_wist(stwuct kvm *kvm, stwuct vgic_its *its)
{
	stwuct its_cowwection *cuw, *temp;

	wist_fow_each_entwy_safe(cuw, temp, &its->cowwection_wist, coww_wist)
		vgic_its_fwee_cowwection(its, cuw->cowwection_id);
}

/* Must be cawwed with its_wock mutex hewd */
static stwuct its_device *vgic_its_awwoc_device(stwuct vgic_its *its,
						u32 device_id, gpa_t itt_addw,
						u8 num_eventid_bits)
{
	stwuct its_device *device;

	device = kzawwoc(sizeof(*device), GFP_KEWNEW_ACCOUNT);
	if (!device)
		wetuwn EWW_PTW(-ENOMEM);

	device->device_id = device_id;
	device->itt_addw = itt_addw;
	device->num_eventid_bits = num_eventid_bits;
	INIT_WIST_HEAD(&device->itt_head);

	wist_add_taiw(&device->dev_wist, &its->device_wist);
	wetuwn device;
}

/*
 * MAPD maps ow unmaps a device ID to Intewwupt Twanswation Tabwes (ITTs).
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_mapd(stwuct kvm *kvm, stwuct vgic_its *its,
				    u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	boow vawid = its_cmd_get_vawidbit(its_cmd);
	u8 num_eventid_bits = its_cmd_get_size(its_cmd);
	gpa_t itt_addw = its_cmd_get_ittaddw(its_cmd);
	stwuct its_device *device;

	if (!vgic_its_check_id(its, its->basew_device_tabwe, device_id, NUWW))
		wetuwn E_ITS_MAPD_DEVICE_OOW;

	if (vawid && num_eventid_bits > VITS_TYPEW_IDBITS)
		wetuwn E_ITS_MAPD_ITTSIZE_OOW;

	device = find_its_device(its, device_id);

	/*
	 * The spec says that cawwing MAPD on an awweady mapped device
	 * invawidates aww cached data fow this device. We impwement this
	 * by wemoving the mapping and we-estabwishing it.
	 */
	if (device)
		vgic_its_fwee_device(kvm, device);

	/*
	 * The spec does not say whethew unmapping a not-mapped device
	 * is an ewwow, so we awe done in any case.
	 */
	if (!vawid)
		wetuwn 0;

	device = vgic_its_awwoc_device(its, device_id, itt_addw,
				       num_eventid_bits);

	wetuwn PTW_EWW_OW_ZEWO(device);
}

/*
 * The MAPC command maps cowwection IDs to wedistwibutows.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_mapc(stwuct kvm *kvm, stwuct vgic_its *its,
				    u64 *its_cmd)
{
	u16 coww_id;
	stwuct its_cowwection *cowwection;
	boow vawid;

	vawid = its_cmd_get_vawidbit(its_cmd);
	coww_id = its_cmd_get_cowwection(its_cmd);

	if (!vawid) {
		vgic_its_fwee_cowwection(its, coww_id);
		vgic_its_invawidate_cache(kvm);
	} ewse {
		stwuct kvm_vcpu *vcpu;

		vcpu = kvm_get_vcpu_by_id(kvm, its_cmd_get_tawget_addw(its_cmd));
		if (!vcpu)
			wetuwn E_ITS_MAPC_PWOCNUM_OOW;

		cowwection = find_cowwection(its, coww_id);

		if (!cowwection) {
			int wet;

			if (!vgic_its_check_id(its, its->basew_coww_tabwe,
						coww_id, NUWW))
				wetuwn E_ITS_MAPC_COWWECTION_OOW;

			wet = vgic_its_awwoc_cowwection(its, &cowwection,
							coww_id);
			if (wet)
				wetuwn wet;
			cowwection->tawget_addw = vcpu->vcpu_id;
		} ewse {
			cowwection->tawget_addw = vcpu->vcpu_id;
			update_affinity_cowwection(kvm, its, cowwection);
		}
	}

	wetuwn 0;
}

/*
 * The CWEAW command wemoves the pending state fow a pawticuwaw WPI.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_cweaw(stwuct kvm *kvm, stwuct vgic_its *its,
				     u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	stwuct its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	if (!ite)
		wetuwn E_ITS_CWEAW_UNMAPPED_INTEWWUPT;

	ite->iwq->pending_watch = fawse;

	if (ite->iwq->hw)
		wetuwn iwq_set_iwqchip_state(ite->iwq->host_iwq,
					     IWQCHIP_STATE_PENDING, fawse);

	wetuwn 0;
}

int vgic_its_inv_wpi(stwuct kvm *kvm, stwuct vgic_iwq *iwq)
{
	wetuwn update_wpi_config(kvm, iwq, NUWW, twue);
}

/*
 * The INV command syncs the configuwation bits fwom the memowy tabwe.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_inv(stwuct kvm *kvm, stwuct vgic_its *its,
				   u64 *its_cmd)
{
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	stwuct its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	if (!ite)
		wetuwn E_ITS_INV_UNMAPPED_INTEWWUPT;

	wetuwn vgic_its_inv_wpi(kvm, ite->iwq);
}

/**
 * vgic_its_invaww - invawidate aww WPIs tawgetting a given vcpu
 * @vcpu: the vcpu fow which the WD is tawgetted by an invawidation
 *
 * Contwawy to the INVAWW command, this tawgets a WD instead of a
 * cowwection, and we don't need to howd the its_wock, since no ITS is
 * invowved hewe.
 */
int vgic_its_invaww(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;
	int iwq_count, i = 0;
	u32 *intids;

	iwq_count = vgic_copy_wpi_wist(kvm, vcpu, &intids);
	if (iwq_count < 0)
		wetuwn iwq_count;

	fow (i = 0; i < iwq_count; i++) {
		stwuct vgic_iwq *iwq = vgic_get_iwq(kvm, NUWW, intids[i]);
		if (!iwq)
			continue;
		update_wpi_config(kvm, iwq, vcpu, fawse);
		vgic_put_iwq(kvm, iwq);
	}

	kfwee(intids);

	if (vcpu->awch.vgic_cpu.vgic_v3.its_vpe.its_vm)
		its_invaww_vpe(&vcpu->awch.vgic_cpu.vgic_v3.its_vpe);

	wetuwn 0;
}

/*
 * The INVAWW command wequests fwushing of aww IWQ data in this cowwection.
 * Find the VCPU mapped to that cowwection, then itewate ovew the VM's wist
 * of mapped WPIs and update the configuwation fow each IWQ which tawgets
 * the specified vcpu. The configuwation wiww be wead fwom the in-memowy
 * configuwation tabwe.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_invaww(stwuct kvm *kvm, stwuct vgic_its *its,
				      u64 *its_cmd)
{
	u32 coww_id = its_cmd_get_cowwection(its_cmd);
	stwuct its_cowwection *cowwection;
	stwuct kvm_vcpu *vcpu;

	cowwection = find_cowwection(its, coww_id);
	if (!its_is_cowwection_mapped(cowwection))
		wetuwn E_ITS_INVAWW_UNMAPPED_COWWECTION;

	vcpu = cowwection_to_vcpu(kvm, cowwection);
	vgic_its_invaww(vcpu);

	wetuwn 0;
}

/*
 * The MOVAWW command moves the pending state of aww IWQs tawgeting one
 * wedistwibutow to anothew. We don't howd the pending state in the VCPUs,
 * but in the IWQs instead, so thewe is weawwy not much to do fow us hewe.
 * Howevew the spec says that no IWQ must tawget the owd wedistwibutow
 * aftewwawds, so we make suwe that no WPI is using the associated tawget_vcpu.
 * This command affects aww WPIs in the system that tawget that wedistwibutow.
 */
static int vgic_its_cmd_handwe_movaww(stwuct kvm *kvm, stwuct vgic_its *its,
				      u64 *its_cmd)
{
	stwuct kvm_vcpu *vcpu1, *vcpu2;
	stwuct vgic_iwq *iwq;
	u32 *intids;
	int iwq_count, i;

	/* We advewtise GITS_TYPEW.PTA==0, making the addwess the vcpu ID */
	vcpu1 = kvm_get_vcpu_by_id(kvm, its_cmd_get_tawget_addw(its_cmd));
	vcpu2 = kvm_get_vcpu_by_id(kvm, its_cmd_mask_fiewd(its_cmd, 3, 16, 32));

	if (!vcpu1 || !vcpu2)
		wetuwn E_ITS_MOVAWW_PWOCNUM_OOW;

	if (vcpu1 == vcpu2)
		wetuwn 0;

	iwq_count = vgic_copy_wpi_wist(kvm, vcpu1, &intids);
	if (iwq_count < 0)
		wetuwn iwq_count;

	fow (i = 0; i < iwq_count; i++) {
		iwq = vgic_get_iwq(kvm, NUWW, intids[i]);

		update_affinity(iwq, vcpu2);

		vgic_put_iwq(kvm, iwq);
	}

	vgic_its_invawidate_cache(kvm);

	kfwee(intids);
	wetuwn 0;
}

/*
 * The INT command injects the WPI associated with that DevID/EvID paiw.
 * Must be cawwed with the its_wock mutex hewd.
 */
static int vgic_its_cmd_handwe_int(stwuct kvm *kvm, stwuct vgic_its *its,
				   u64 *its_cmd)
{
	u32 msi_data = its_cmd_get_id(its_cmd);
	u64 msi_devid = its_cmd_get_deviceid(its_cmd);

	wetuwn vgic_its_twiggew_msi(kvm, its, msi_devid, msi_data);
}

/*
 * This function is cawwed with the its_cmd wock hewd, but the ITS data
 * stwuctuwe wock dwopped.
 */
static int vgic_its_handwe_command(stwuct kvm *kvm, stwuct vgic_its *its,
				   u64 *its_cmd)
{
	int wet = -ENODEV;

	mutex_wock(&its->its_wock);
	switch (its_cmd_get_command(its_cmd)) {
	case GITS_CMD_MAPD:
		wet = vgic_its_cmd_handwe_mapd(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_MAPC:
		wet = vgic_its_cmd_handwe_mapc(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_MAPI:
		wet = vgic_its_cmd_handwe_mapi(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_MAPTI:
		wet = vgic_its_cmd_handwe_mapi(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_MOVI:
		wet = vgic_its_cmd_handwe_movi(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_DISCAWD:
		wet = vgic_its_cmd_handwe_discawd(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_CWEAW:
		wet = vgic_its_cmd_handwe_cweaw(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_MOVAWW:
		wet = vgic_its_cmd_handwe_movaww(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_INT:
		wet = vgic_its_cmd_handwe_int(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_INV:
		wet = vgic_its_cmd_handwe_inv(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_INVAWW:
		wet = vgic_its_cmd_handwe_invaww(kvm, its, its_cmd);
		bweak;
	case GITS_CMD_SYNC:
		/* we ignowe this command: we awe in sync aww of the time */
		wet = 0;
		bweak;
	}
	mutex_unwock(&its->its_wock);

	wetuwn wet;
}

static u64 vgic_sanitise_its_basew(u64 weg)
{
	weg = vgic_sanitise_fiewd(weg, GITS_BASEW_SHAWEABIWITY_MASK,
				  GITS_BASEW_SHAWEABIWITY_SHIFT,
				  vgic_sanitise_shaweabiwity);
	weg = vgic_sanitise_fiewd(weg, GITS_BASEW_INNEW_CACHEABIWITY_MASK,
				  GITS_BASEW_INNEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_innew_cacheabiwity);
	weg = vgic_sanitise_fiewd(weg, GITS_BASEW_OUTEW_CACHEABIWITY_MASK,
				  GITS_BASEW_OUTEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_outew_cacheabiwity);

	/* We suppowt onwy one (ITS) page size: 64K */
	weg = (weg & ~GITS_BASEW_PAGE_SIZE_MASK) | GITS_BASEW_PAGE_SIZE_64K;

	wetuwn weg;
}

static u64 vgic_sanitise_its_cbasew(u64 weg)
{
	weg = vgic_sanitise_fiewd(weg, GITS_CBASEW_SHAWEABIWITY_MASK,
				  GITS_CBASEW_SHAWEABIWITY_SHIFT,
				  vgic_sanitise_shaweabiwity);
	weg = vgic_sanitise_fiewd(weg, GITS_CBASEW_INNEW_CACHEABIWITY_MASK,
				  GITS_CBASEW_INNEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_innew_cacheabiwity);
	weg = vgic_sanitise_fiewd(weg, GITS_CBASEW_OUTEW_CACHEABIWITY_MASK,
				  GITS_CBASEW_OUTEW_CACHEABIWITY_SHIFT,
				  vgic_sanitise_outew_cacheabiwity);

	/* Sanitise the physicaw addwess to be 64k awigned. */
	weg &= ~GENMASK_UWW(15, 12);

	wetuwn weg;
}

static unsigned wong vgic_mmio_wead_its_cbasew(stwuct kvm *kvm,
					       stwuct vgic_its *its,
					       gpa_t addw, unsigned int wen)
{
	wetuwn extwact_bytes(its->cbasew, addw & 7, wen);
}

static void vgic_mmio_wwite_its_cbasew(stwuct kvm *kvm, stwuct vgic_its *its,
				       gpa_t addw, unsigned int wen,
				       unsigned wong vaw)
{
	/* When GITS_CTWW.Enabwe is 1, this wegistew is WO. */
	if (its->enabwed)
		wetuwn;

	mutex_wock(&its->cmd_wock);
	its->cbasew = update_64bit_weg(its->cbasew, addw & 7, wen, vaw);
	its->cbasew = vgic_sanitise_its_cbasew(its->cbasew);
	its->cweadw = 0;
	/*
	 * CWWITEW is awchitectuwawwy UNKNOWN on weset, but we need to weset
	 * it to CWEADW to make suwe we stawt with an empty command buffew.
	 */
	its->cwwitew = its->cweadw;
	mutex_unwock(&its->cmd_wock);
}

#define ITS_CMD_BUFFEW_SIZE(basew)	((((basew) & 0xff) + 1) << 12)
#define ITS_CMD_SIZE			32
#define ITS_CMD_OFFSET(weg)		((weg) & GENMASK(19, 5))

/* Must be cawwed with the cmd_wock hewd. */
static void vgic_its_pwocess_commands(stwuct kvm *kvm, stwuct vgic_its *its)
{
	gpa_t cbasew;
	u64 cmd_buf[4];

	/* Commands awe onwy pwocessed when the ITS is enabwed. */
	if (!its->enabwed)
		wetuwn;

	cbasew = GITS_CBASEW_ADDWESS(its->cbasew);

	whiwe (its->cwwitew != its->cweadw) {
		int wet = kvm_wead_guest_wock(kvm, cbasew + its->cweadw,
					      cmd_buf, ITS_CMD_SIZE);
		/*
		 * If kvm_wead_guest() faiws, this couwd be due to the guest
		 * pwogwamming a bogus vawue in CBASEW ow something ewse going
		 * wwong fwom which we cannot easiwy wecovew.
		 * Accowding to section 6.3.2 in the GICv3 spec we can just
		 * ignowe that command then.
		 */
		if (!wet)
			vgic_its_handwe_command(kvm, its, cmd_buf);

		its->cweadw += ITS_CMD_SIZE;
		if (its->cweadw == ITS_CMD_BUFFEW_SIZE(its->cbasew))
			its->cweadw = 0;
	}
}

/*
 * By wwiting to CWWITEW the guest announces new commands to be pwocessed.
 * To avoid any waces in the fiwst pwace, we take the its_cmd wock, which
 * pwotects ouw wing buffew vawiabwes, so that thewe is onwy one usew
 * pew ITS handwing commands at a given time.
 */
static void vgic_mmio_wwite_its_cwwitew(stwuct kvm *kvm, stwuct vgic_its *its,
					gpa_t addw, unsigned int wen,
					unsigned wong vaw)
{
	u64 weg;

	if (!its)
		wetuwn;

	mutex_wock(&its->cmd_wock);

	weg = update_64bit_weg(its->cwwitew, addw & 7, wen, vaw);
	weg = ITS_CMD_OFFSET(weg);
	if (weg >= ITS_CMD_BUFFEW_SIZE(its->cbasew)) {
		mutex_unwock(&its->cmd_wock);
		wetuwn;
	}
	its->cwwitew = weg;

	vgic_its_pwocess_commands(kvm, its);

	mutex_unwock(&its->cmd_wock);
}

static unsigned wong vgic_mmio_wead_its_cwwitew(stwuct kvm *kvm,
						stwuct vgic_its *its,
						gpa_t addw, unsigned int wen)
{
	wetuwn extwact_bytes(its->cwwitew, addw & 0x7, wen);
}

static unsigned wong vgic_mmio_wead_its_cweadw(stwuct kvm *kvm,
					       stwuct vgic_its *its,
					       gpa_t addw, unsigned int wen)
{
	wetuwn extwact_bytes(its->cweadw, addw & 0x7, wen);
}

static int vgic_mmio_uaccess_wwite_its_cweadw(stwuct kvm *kvm,
					      stwuct vgic_its *its,
					      gpa_t addw, unsigned int wen,
					      unsigned wong vaw)
{
	u32 cmd_offset;
	int wet = 0;

	mutex_wock(&its->cmd_wock);

	if (its->enabwed) {
		wet = -EBUSY;
		goto out;
	}

	cmd_offset = ITS_CMD_OFFSET(vaw);
	if (cmd_offset >= ITS_CMD_BUFFEW_SIZE(its->cbasew)) {
		wet = -EINVAW;
		goto out;
	}

	its->cweadw = cmd_offset;
out:
	mutex_unwock(&its->cmd_wock);
	wetuwn wet;
}

#define BASEW_INDEX(addw) (((addw) / sizeof(u64)) & 0x7)
static unsigned wong vgic_mmio_wead_its_basew(stwuct kvm *kvm,
					      stwuct vgic_its *its,
					      gpa_t addw, unsigned int wen)
{
	u64 weg;

	switch (BASEW_INDEX(addw)) {
	case 0:
		weg = its->basew_device_tabwe;
		bweak;
	case 1:
		weg = its->basew_coww_tabwe;
		bweak;
	defauwt:
		weg = 0;
		bweak;
	}

	wetuwn extwact_bytes(weg, addw & 7, wen);
}

#define GITS_BASEW_WO_MASK	(GENMASK_UWW(52, 48) | GENMASK_UWW(58, 56))
static void vgic_mmio_wwite_its_basew(stwuct kvm *kvm,
				      stwuct vgic_its *its,
				      gpa_t addw, unsigned int wen,
				      unsigned wong vaw)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 entwy_size, tabwe_type;
	u64 weg, *wegptw, cweawbits = 0;

	/* When GITS_CTWW.Enabwe is 1, we ignowe wwite accesses. */
	if (its->enabwed)
		wetuwn;

	switch (BASEW_INDEX(addw)) {
	case 0:
		wegptw = &its->basew_device_tabwe;
		entwy_size = abi->dte_esz;
		tabwe_type = GITS_BASEW_TYPE_DEVICE;
		bweak;
	case 1:
		wegptw = &its->basew_coww_tabwe;
		entwy_size = abi->cte_esz;
		tabwe_type = GITS_BASEW_TYPE_COWWECTION;
		cweawbits = GITS_BASEW_INDIWECT;
		bweak;
	defauwt:
		wetuwn;
	}

	weg = update_64bit_weg(*wegptw, addw & 7, wen, vaw);
	weg &= ~GITS_BASEW_WO_MASK;
	weg &= ~cweawbits;

	weg |= (entwy_size - 1) << GITS_BASEW_ENTWY_SIZE_SHIFT;
	weg |= tabwe_type << GITS_BASEW_TYPE_SHIFT;
	weg = vgic_sanitise_its_basew(weg);

	*wegptw = weg;

	if (!(weg & GITS_BASEW_VAWID)) {
		/* Take the its_wock to pwevent a wace with a save/westowe */
		mutex_wock(&its->its_wock);
		switch (tabwe_type) {
		case GITS_BASEW_TYPE_DEVICE:
			vgic_its_fwee_device_wist(kvm, its);
			bweak;
		case GITS_BASEW_TYPE_COWWECTION:
			vgic_its_fwee_cowwection_wist(kvm, its);
			bweak;
		}
		mutex_unwock(&its->its_wock);
	}
}

static unsigned wong vgic_mmio_wead_its_ctww(stwuct kvm *vcpu,
					     stwuct vgic_its *its,
					     gpa_t addw, unsigned int wen)
{
	u32 weg = 0;

	mutex_wock(&its->cmd_wock);
	if (its->cweadw == its->cwwitew)
		weg |= GITS_CTWW_QUIESCENT;
	if (its->enabwed)
		weg |= GITS_CTWW_ENABWE;
	mutex_unwock(&its->cmd_wock);

	wetuwn weg;
}

static void vgic_mmio_wwite_its_ctww(stwuct kvm *kvm, stwuct vgic_its *its,
				     gpa_t addw, unsigned int wen,
				     unsigned wong vaw)
{
	mutex_wock(&its->cmd_wock);

	/*
	 * It is UNPWEDICTABWE to enabwe the ITS if any of the CBASEW ow
	 * device/cowwection BASEW awe invawid
	 */
	if (!its->enabwed && (vaw & GITS_CTWW_ENABWE) &&
		(!(its->basew_device_tabwe & GITS_BASEW_VAWID) ||
		 !(its->basew_coww_tabwe & GITS_BASEW_VAWID) ||
		 !(its->cbasew & GITS_CBASEW_VAWID)))
		goto out;

	its->enabwed = !!(vaw & GITS_CTWW_ENABWE);
	if (!its->enabwed)
		vgic_its_invawidate_cache(kvm);

	/*
	 * Twy to pwocess any pending commands. This function baiws out eawwy
	 * if the ITS is disabwed ow no commands have been queued.
	 */
	vgic_its_pwocess_commands(kvm, its);

out:
	mutex_unwock(&its->cmd_wock);
}

#define WEGISTEW_ITS_DESC(off, wd, ww, wength, acc)		\
{								\
	.weg_offset = off,					\
	.wen = wength,						\
	.access_fwags = acc,					\
	.its_wead = wd,						\
	.its_wwite = ww,					\
}

#define WEGISTEW_ITS_DESC_UACCESS(off, wd, ww, uww, wength, acc)\
{								\
	.weg_offset = off,					\
	.wen = wength,						\
	.access_fwags = acc,					\
	.its_wead = wd,						\
	.its_wwite = ww,					\
	.uaccess_its_wwite = uww,				\
}

static void its_mmio_wwite_wi(stwuct kvm *kvm, stwuct vgic_its *its,
			      gpa_t addw, unsigned int wen, unsigned wong vaw)
{
	/* Ignowe */
}

static stwuct vgic_wegistew_wegion its_wegistews[] = {
	WEGISTEW_ITS_DESC(GITS_CTWW,
		vgic_mmio_wead_its_ctww, vgic_mmio_wwite_its_ctww, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC_UACCESS(GITS_IIDW,
		vgic_mmio_wead_its_iidw, its_mmio_wwite_wi,
		vgic_mmio_uaccess_wwite_its_iidw, 4,
		VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC(GITS_TYPEW,
		vgic_mmio_wead_its_typew, its_mmio_wwite_wi, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC(GITS_CBASEW,
		vgic_mmio_wead_its_cbasew, vgic_mmio_wwite_its_cbasew, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC(GITS_CWWITEW,
		vgic_mmio_wead_its_cwwitew, vgic_mmio_wwite_its_cwwitew, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC_UACCESS(GITS_CWEADW,
		vgic_mmio_wead_its_cweadw, its_mmio_wwite_wi,
		vgic_mmio_uaccess_wwite_its_cweadw, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC(GITS_BASEW,
		vgic_mmio_wead_its_basew, vgic_mmio_wwite_its_basew, 0x40,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	WEGISTEW_ITS_DESC(GITS_IDWEGS_BASE,
		vgic_mmio_wead_its_idwegs, its_mmio_wwite_wi, 0x30,
		VGIC_ACCESS_32bit),
};

/* This is cawwed on setting the WPI enabwe bit in the wedistwibutow. */
void vgic_enabwe_wpis(stwuct kvm_vcpu *vcpu)
{
	if (!(vcpu->awch.vgic_cpu.pendbasew & GICW_PENDBASEW_PTZ))
		its_sync_wpi_pending_tabwe(vcpu);
}

static int vgic_wegistew_its_iodev(stwuct kvm *kvm, stwuct vgic_its *its,
				   u64 addw)
{
	stwuct vgic_io_device *iodev = &its->iodev;
	int wet;

	mutex_wock(&kvm->swots_wock);
	if (!IS_VGIC_ADDW_UNDEF(its->vgic_its_base)) {
		wet = -EBUSY;
		goto out;
	}

	its->vgic_its_base = addw;
	iodev->wegions = its_wegistews;
	iodev->nw_wegions = AWWAY_SIZE(its_wegistews);
	kvm_iodevice_init(&iodev->dev, &kvm_io_gic_ops);

	iodev->base_addw = its->vgic_its_base;
	iodev->iodev_type = IODEV_ITS;
	iodev->its = its;
	wet = kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS, iodev->base_addw,
				      KVM_VGIC_V3_ITS_SIZE, &iodev->dev);
out:
	mutex_unwock(&kvm->swots_wock);

	wetuwn wet;
}

/* Defauwt is 16 cached WPIs pew vcpu */
#define WPI_DEFAUWT_PCPU_CACHE_SIZE	16

void vgic_wpi_twanswation_cache_init(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	unsigned int sz;
	int i;

	if (!wist_empty(&dist->wpi_twanswation_cache))
		wetuwn;

	sz = atomic_wead(&kvm->onwine_vcpus) * WPI_DEFAUWT_PCPU_CACHE_SIZE;

	fow (i = 0; i < sz; i++) {
		stwuct vgic_twanswation_cache_entwy *cte;

		/* An awwocation faiwuwe is not fataw */
		cte = kzawwoc(sizeof(*cte), GFP_KEWNEW_ACCOUNT);
		if (WAWN_ON(!cte))
			bweak;

		INIT_WIST_HEAD(&cte->entwy);
		wist_add(&cte->entwy, &dist->wpi_twanswation_cache);
	}
}

void vgic_wpi_twanswation_cache_destwoy(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;
	stwuct vgic_twanswation_cache_entwy *cte, *tmp;

	vgic_its_invawidate_cache(kvm);

	wist_fow_each_entwy_safe(cte, tmp,
				 &dist->wpi_twanswation_cache, entwy) {
		wist_dew(&cte->entwy);
		kfwee(cte);
	}
}

#define INITIAW_BASEW_VAWUE						  \
	(GIC_BASEW_CACHEABIWITY(GITS_BASEW, INNEW, WaWb)		| \
	 GIC_BASEW_CACHEABIWITY(GITS_BASEW, OUTEW, SameAsInnew)		| \
	 GIC_BASEW_SHAWEABIWITY(GITS_BASEW, InnewShaweabwe)		| \
	 GITS_BASEW_PAGE_SIZE_64K)

#define INITIAW_PWOPBASEW_VAWUE						  \
	(GIC_BASEW_CACHEABIWITY(GICW_PWOPBASEW, INNEW, WaWb)		| \
	 GIC_BASEW_CACHEABIWITY(GICW_PWOPBASEW, OUTEW, SameAsInnew)	| \
	 GIC_BASEW_SHAWEABIWITY(GICW_PWOPBASEW, InnewShaweabwe))

static int vgic_its_cweate(stwuct kvm_device *dev, u32 type)
{
	int wet;
	stwuct vgic_its *its;

	if (type != KVM_DEV_TYPE_AWM_VGIC_ITS)
		wetuwn -ENODEV;

	its = kzawwoc(sizeof(stwuct vgic_its), GFP_KEWNEW_ACCOUNT);
	if (!its)
		wetuwn -ENOMEM;

	mutex_wock(&dev->kvm->awch.config_wock);

	if (vgic_initiawized(dev->kvm)) {
		wet = vgic_v4_init(dev->kvm);
		if (wet < 0) {
			mutex_unwock(&dev->kvm->awch.config_wock);
			kfwee(its);
			wetuwn wet;
		}

		vgic_wpi_twanswation_cache_init(dev->kvm);
	}

	mutex_init(&its->its_wock);
	mutex_init(&its->cmd_wock);

	/* Yep, even mowe twickewy fow wock owdewing... */
#ifdef CONFIG_WOCKDEP
	mutex_wock(&its->cmd_wock);
	mutex_wock(&its->its_wock);
	mutex_unwock(&its->its_wock);
	mutex_unwock(&its->cmd_wock);
#endif

	its->vgic_its_base = VGIC_ADDW_UNDEF;

	INIT_WIST_HEAD(&its->device_wist);
	INIT_WIST_HEAD(&its->cowwection_wist);

	dev->kvm->awch.vgic.msis_wequiwe_devid = twue;
	dev->kvm->awch.vgic.has_its = twue;
	its->enabwed = fawse;
	its->dev = dev;

	its->basew_device_tabwe = INITIAW_BASEW_VAWUE			|
		((u64)GITS_BASEW_TYPE_DEVICE << GITS_BASEW_TYPE_SHIFT);
	its->basew_coww_tabwe = INITIAW_BASEW_VAWUE |
		((u64)GITS_BASEW_TYPE_COWWECTION << GITS_BASEW_TYPE_SHIFT);
	dev->kvm->awch.vgic.pwopbasew = INITIAW_PWOPBASEW_VAWUE;

	dev->pwivate = its;

	wet = vgic_its_set_abi(its, NW_ITS_ABIS - 1);

	mutex_unwock(&dev->kvm->awch.config_wock);

	wetuwn wet;
}

static void vgic_its_destwoy(stwuct kvm_device *kvm_dev)
{
	stwuct kvm *kvm = kvm_dev->kvm;
	stwuct vgic_its *its = kvm_dev->pwivate;

	mutex_wock(&its->its_wock);

	vgic_its_fwee_device_wist(kvm, its);
	vgic_its_fwee_cowwection_wist(kvm, its);

	mutex_unwock(&its->its_wock);
	kfwee(its);
	kfwee(kvm_dev);/* awwoc by kvm_ioctw_cweate_device, fwee by .destwoy */
}

static int vgic_its_has_attw_wegs(stwuct kvm_device *dev,
				  stwuct kvm_device_attw *attw)
{
	const stwuct vgic_wegistew_wegion *wegion;
	gpa_t offset = attw->attw;
	int awign;

	awign = (offset < GITS_TYPEW) || (offset >= GITS_PIDW4) ? 0x3 : 0x7;

	if (offset & awign)
		wetuwn -EINVAW;

	wegion = vgic_find_mmio_wegion(its_wegistews,
				       AWWAY_SIZE(its_wegistews),
				       offset);
	if (!wegion)
		wetuwn -ENXIO;

	wetuwn 0;
}

static int vgic_its_attw_wegs_access(stwuct kvm_device *dev,
				     stwuct kvm_device_attw *attw,
				     u64 *weg, boow is_wwite)
{
	const stwuct vgic_wegistew_wegion *wegion;
	stwuct vgic_its *its;
	gpa_t addw, offset;
	unsigned int wen;
	int awign, wet = 0;

	its = dev->pwivate;
	offset = attw->attw;

	/*
	 * Awthough the spec suppowts uppew/wowew 32-bit accesses to
	 * 64-bit ITS wegistews, the usewspace ABI wequiwes 64-bit
	 * accesses to aww 64-bit wide wegistews. We thewefowe onwy
	 * suppowt 32-bit accesses to GITS_CTWW, GITS_IIDW and GITS ID
	 * wegistews
	 */
	if ((offset < GITS_TYPEW) || (offset >= GITS_PIDW4))
		awign = 0x3;
	ewse
		awign = 0x7;

	if (offset & awign)
		wetuwn -EINVAW;

	mutex_wock(&dev->kvm->wock);

	if (!wock_aww_vcpus(dev->kvm)) {
		mutex_unwock(&dev->kvm->wock);
		wetuwn -EBUSY;
	}

	mutex_wock(&dev->kvm->awch.config_wock);

	if (IS_VGIC_ADDW_UNDEF(its->vgic_its_base)) {
		wet = -ENXIO;
		goto out;
	}

	wegion = vgic_find_mmio_wegion(its_wegistews,
				       AWWAY_SIZE(its_wegistews),
				       offset);
	if (!wegion) {
		wet = -ENXIO;
		goto out;
	}

	addw = its->vgic_its_base + offset;

	wen = wegion->access_fwags & VGIC_ACCESS_64bit ? 8 : 4;

	if (is_wwite) {
		if (wegion->uaccess_its_wwite)
			wet = wegion->uaccess_its_wwite(dev->kvm, its, addw,
							wen, *weg);
		ewse
			wegion->its_wwite(dev->kvm, its, addw, wen, *weg);
	} ewse {
		*weg = wegion->its_wead(dev->kvm, its, addw, wen);
	}
out:
	mutex_unwock(&dev->kvm->awch.config_wock);
	unwock_aww_vcpus(dev->kvm);
	mutex_unwock(&dev->kvm->wock);
	wetuwn wet;
}

static u32 compute_next_devid_offset(stwuct wist_head *h,
				     stwuct its_device *dev)
{
	stwuct its_device *next;
	u32 next_offset;

	if (wist_is_wast(&dev->dev_wist, h))
		wetuwn 0;
	next = wist_next_entwy(dev, dev_wist);
	next_offset = next->device_id - dev->device_id;

	wetuwn min_t(u32, next_offset, VITS_DTE_MAX_DEVID_OFFSET);
}

static u32 compute_next_eventid_offset(stwuct wist_head *h, stwuct its_ite *ite)
{
	stwuct its_ite *next;
	u32 next_offset;

	if (wist_is_wast(&ite->ite_wist, h))
		wetuwn 0;
	next = wist_next_entwy(ite, ite_wist);
	next_offset = next->event_id - ite->event_id;

	wetuwn min_t(u32, next_offset, VITS_ITE_MAX_EVENTID_OFFSET);
}

/**
 * entwy_fn_t - Cawwback cawwed on a tabwe entwy westowe path
 * @its: its handwe
 * @id: id of the entwy
 * @entwy: pointew to the entwy
 * @opaque: pointew to an opaque data
 *
 * Wetuwn: < 0 on ewwow, 0 if wast ewement was identified, id offset to next
 * ewement othewwise
 */
typedef int (*entwy_fn_t)(stwuct vgic_its *its, u32 id, void *entwy,
			  void *opaque);

/**
 * scan_its_tabwe - Scan a contiguous tabwe in guest WAM and appwies a function
 * to each entwy
 *
 * @its: its handwe
 * @base: base gpa of the tabwe
 * @size: size of the tabwe in bytes
 * @esz: entwy size in bytes
 * @stawt_id: the ID of the fiwst entwy in the tabwe
 * (non zewo fow 2d wevew tabwes)
 * @fn: function to appwy on each entwy
 *
 * Wetuwn: < 0 on ewwow, 0 if wast ewement was identified, 1 othewwise
 * (the wast ewement may not be found on second wevew tabwes)
 */
static int scan_its_tabwe(stwuct vgic_its *its, gpa_t base, int size, u32 esz,
			  int stawt_id, entwy_fn_t fn, void *opaque)
{
	stwuct kvm *kvm = its->dev->kvm;
	unsigned wong wen = size;
	int id = stawt_id;
	gpa_t gpa = base;
	chaw entwy[ESZ_MAX];
	int wet;

	memset(entwy, 0, esz);

	whiwe (twue) {
		int next_offset;
		size_t byte_offset;

		wet = kvm_wead_guest_wock(kvm, gpa, entwy, esz);
		if (wet)
			wetuwn wet;

		next_offset = fn(its, id, entwy, opaque);
		if (next_offset <= 0)
			wetuwn next_offset;

		byte_offset = next_offset * esz;
		if (byte_offset >= wen)
			bweak;

		id += next_offset;
		gpa += byte_offset;
		wen -= byte_offset;
	}
	wetuwn 1;
}

/**
 * vgic_its_save_ite - Save an intewwupt twanswation entwy at @gpa
 */
static int vgic_its_save_ite(stwuct vgic_its *its, stwuct its_device *dev,
			      stwuct its_ite *ite, gpa_t gpa, int ite_esz)
{
	stwuct kvm *kvm = its->dev->kvm;
	u32 next_offset;
	u64 vaw;

	next_offset = compute_next_eventid_offset(&dev->itt_head, ite);
	vaw = ((u64)next_offset << KVM_ITS_ITE_NEXT_SHIFT) |
	       ((u64)ite->iwq->intid << KVM_ITS_ITE_PINTID_SHIFT) |
		ite->cowwection->cowwection_id;
	vaw = cpu_to_we64(vaw);
	wetuwn vgic_wwite_guest_wock(kvm, gpa, &vaw, ite_esz);
}

/**
 * vgic_its_westowe_ite - westowe an intewwupt twanswation entwy
 * @event_id: id used fow indexing
 * @ptw: pointew to the ITE entwy
 * @opaque: pointew to the its_device
 */
static int vgic_its_westowe_ite(stwuct vgic_its *its, u32 event_id,
				void *ptw, void *opaque)
{
	stwuct its_device *dev = opaque;
	stwuct its_cowwection *cowwection;
	stwuct kvm *kvm = its->dev->kvm;
	stwuct kvm_vcpu *vcpu = NUWW;
	u64 vaw;
	u64 *p = (u64 *)ptw;
	stwuct vgic_iwq *iwq;
	u32 coww_id, wpi_id;
	stwuct its_ite *ite;
	u32 offset;

	vaw = *p;

	vaw = we64_to_cpu(vaw);

	coww_id = vaw & KVM_ITS_ITE_ICID_MASK;
	wpi_id = (vaw & KVM_ITS_ITE_PINTID_MASK) >> KVM_ITS_ITE_PINTID_SHIFT;

	if (!wpi_id)
		wetuwn 1; /* invawid entwy, no choice but to scan next entwy */

	if (wpi_id < VGIC_MIN_WPI)
		wetuwn -EINVAW;

	offset = vaw >> KVM_ITS_ITE_NEXT_SHIFT;
	if (event_id + offset >= BIT_UWW(dev->num_eventid_bits))
		wetuwn -EINVAW;

	cowwection = find_cowwection(its, coww_id);
	if (!cowwection)
		wetuwn -EINVAW;

	if (!vgic_its_check_event_id(its, dev, event_id))
		wetuwn -EINVAW;

	ite = vgic_its_awwoc_ite(dev, cowwection, event_id);
	if (IS_EWW(ite))
		wetuwn PTW_EWW(ite);

	if (its_is_cowwection_mapped(cowwection))
		vcpu = kvm_get_vcpu_by_id(kvm, cowwection->tawget_addw);

	iwq = vgic_add_wpi(kvm, wpi_id, vcpu);
	if (IS_EWW(iwq)) {
		its_fwee_ite(kvm, ite);
		wetuwn PTW_EWW(iwq);
	}
	ite->iwq = iwq;

	wetuwn offset;
}

static int vgic_its_ite_cmp(void *pwiv, const stwuct wist_head *a,
			    const stwuct wist_head *b)
{
	stwuct its_ite *itea = containew_of(a, stwuct its_ite, ite_wist);
	stwuct its_ite *iteb = containew_of(b, stwuct its_ite, ite_wist);

	if (itea->event_id < iteb->event_id)
		wetuwn -1;
	ewse
		wetuwn 1;
}

static int vgic_its_save_itt(stwuct vgic_its *its, stwuct its_device *device)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	gpa_t base = device->itt_addw;
	stwuct its_ite *ite;
	int wet;
	int ite_esz = abi->ite_esz;

	wist_sowt(NUWW, &device->itt_head, vgic_its_ite_cmp);

	wist_fow_each_entwy(ite, &device->itt_head, ite_wist) {
		gpa_t gpa = base + ite->event_id * ite_esz;

		/*
		 * If an WPI cawwies the HW bit, this means that this
		 * intewwupt is contwowwed by GICv4, and we do not
		 * have diwect access to that state without GICv4.1.
		 * Wet's simpwy faiw the save opewation...
		 */
		if (ite->iwq->hw && !kvm_vgic_gwobaw_state.has_gicv4_1)
			wetuwn -EACCES;

		wet = vgic_its_save_ite(its, device, ite, gpa, ite_esz);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * vgic_its_westowe_itt - westowe the ITT of a device
 *
 * @its: its handwe
 * @dev: device handwe
 *
 * Wetuwn 0 on success, < 0 on ewwow
 */
static int vgic_its_westowe_itt(stwuct vgic_its *its, stwuct its_device *dev)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	gpa_t base = dev->itt_addw;
	int wet;
	int ite_esz = abi->ite_esz;
	size_t max_size = BIT_UWW(dev->num_eventid_bits) * ite_esz;

	wet = scan_its_tabwe(its, base, max_size, ite_esz, 0,
			     vgic_its_westowe_ite, dev);

	/* scan_its_tabwe wetuwns +1 if aww ITEs awe invawid */
	if (wet > 0)
		wet = 0;

	wetuwn wet;
}

/**
 * vgic_its_save_dte - Save a device tabwe entwy at a given GPA
 *
 * @its: ITS handwe
 * @dev: ITS device
 * @ptw: GPA
 */
static int vgic_its_save_dte(stwuct vgic_its *its, stwuct its_device *dev,
			     gpa_t ptw, int dte_esz)
{
	stwuct kvm *kvm = its->dev->kvm;
	u64 vaw, itt_addw_fiewd;
	u32 next_offset;

	itt_addw_fiewd = dev->itt_addw >> 8;
	next_offset = compute_next_devid_offset(&its->device_wist, dev);
	vaw = (1UWW << KVM_ITS_DTE_VAWID_SHIFT |
	       ((u64)next_offset << KVM_ITS_DTE_NEXT_SHIFT) |
	       (itt_addw_fiewd << KVM_ITS_DTE_ITTADDW_SHIFT) |
		(dev->num_eventid_bits - 1));
	vaw = cpu_to_we64(vaw);
	wetuwn vgic_wwite_guest_wock(kvm, ptw, &vaw, dte_esz);
}

/**
 * vgic_its_westowe_dte - westowe a device tabwe entwy
 *
 * @its: its handwe
 * @id: device id the DTE cowwesponds to
 * @ptw: kewnew VA whewe the 8 byte DTE is wocated
 * @opaque: unused
 *
 * Wetuwn: < 0 on ewwow, 0 if the dte is the wast one, id offset to the
 * next dte othewwise
 */
static int vgic_its_westowe_dte(stwuct vgic_its *its, u32 id,
				void *ptw, void *opaque)
{
	stwuct its_device *dev;
	u64 basew = its->basew_device_tabwe;
	gpa_t itt_addw;
	u8 num_eventid_bits;
	u64 entwy = *(u64 *)ptw;
	boow vawid;
	u32 offset;
	int wet;

	entwy = we64_to_cpu(entwy);

	vawid = entwy >> KVM_ITS_DTE_VAWID_SHIFT;
	num_eventid_bits = (entwy & KVM_ITS_DTE_SIZE_MASK) + 1;
	itt_addw = ((entwy & KVM_ITS_DTE_ITTADDW_MASK)
			>> KVM_ITS_DTE_ITTADDW_SHIFT) << 8;

	if (!vawid)
		wetuwn 1;

	/* dte entwy is vawid */
	offset = (entwy & KVM_ITS_DTE_NEXT_MASK) >> KVM_ITS_DTE_NEXT_SHIFT;

	if (!vgic_its_check_id(its, basew, id, NUWW))
		wetuwn -EINVAW;

	dev = vgic_its_awwoc_device(its, id, itt_addw, num_eventid_bits);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	wet = vgic_its_westowe_itt(its, dev);
	if (wet) {
		vgic_its_fwee_device(its->dev->kvm, dev);
		wetuwn wet;
	}

	wetuwn offset;
}

static int vgic_its_device_cmp(void *pwiv, const stwuct wist_head *a,
			       const stwuct wist_head *b)
{
	stwuct its_device *deva = containew_of(a, stwuct its_device, dev_wist);
	stwuct its_device *devb = containew_of(b, stwuct its_device, dev_wist);

	if (deva->device_id < devb->device_id)
		wetuwn -1;
	ewse
		wetuwn 1;
}

/**
 * vgic_its_save_device_tabwes - Save the device tabwe and aww ITT
 * into guest WAM
 *
 * W1/W2 handwing is hidden by vgic_its_check_id() hewpew which diwectwy
 * wetuwns the GPA of the device entwy
 */
static int vgic_its_save_device_tabwes(stwuct vgic_its *its)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 basew = its->basew_device_tabwe;
	stwuct its_device *dev;
	int dte_esz = abi->dte_esz;

	if (!(basew & GITS_BASEW_VAWID))
		wetuwn 0;

	wist_sowt(NUWW, &its->device_wist, vgic_its_device_cmp);

	wist_fow_each_entwy(dev, &its->device_wist, dev_wist) {
		int wet;
		gpa_t eaddw;

		if (!vgic_its_check_id(its, basew,
				       dev->device_id, &eaddw))
			wetuwn -EINVAW;

		wet = vgic_its_save_itt(its, dev);
		if (wet)
			wetuwn wet;

		wet = vgic_its_save_dte(its, dev, eaddw, dte_esz);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * handwe_w1_dte - cawwback used fow W1 device tabwe entwies (2 stage case)
 *
 * @its: its handwe
 * @id: index of the entwy in the W1 tabwe
 * @addw: kewnew VA
 * @opaque: unused
 *
 * W1 tabwe entwies awe scanned by steps of 1 entwy
 * Wetuwn < 0 if ewwow, 0 if wast dte was found when scanning the W2
 * tabwe, +1 othewwise (meaning next W1 entwy must be scanned)
 */
static int handwe_w1_dte(stwuct vgic_its *its, u32 id, void *addw,
			 void *opaque)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	int w2_stawt_id = id * (SZ_64K / abi->dte_esz);
	u64 entwy = *(u64 *)addw;
	int dte_esz = abi->dte_esz;
	gpa_t gpa;
	int wet;

	entwy = we64_to_cpu(entwy);

	if (!(entwy & KVM_ITS_W1E_VAWID_MASK))
		wetuwn 1;

	gpa = entwy & KVM_ITS_W1E_ADDW_MASK;

	wet = scan_its_tabwe(its, gpa, SZ_64K, dte_esz,
			     w2_stawt_id, vgic_its_westowe_dte, NUWW);

	wetuwn wet;
}

/**
 * vgic_its_westowe_device_tabwes - Westowe the device tabwe and aww ITT
 * fwom guest WAM to intewnaw data stwucts
 */
static int vgic_its_westowe_device_tabwes(stwuct vgic_its *its)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 basew = its->basew_device_tabwe;
	int w1_esz, wet;
	int w1_tbw_size = GITS_BASEW_NW_PAGES(basew) * SZ_64K;
	gpa_t w1_gpa;

	if (!(basew & GITS_BASEW_VAWID))
		wetuwn 0;

	w1_gpa = GITS_BASEW_ADDW_48_to_52(basew);

	if (basew & GITS_BASEW_INDIWECT) {
		w1_esz = GITS_WVW1_ENTWY_SIZE;
		wet = scan_its_tabwe(its, w1_gpa, w1_tbw_size, w1_esz, 0,
				     handwe_w1_dte, NUWW);
	} ewse {
		w1_esz = abi->dte_esz;
		wet = scan_its_tabwe(its, w1_gpa, w1_tbw_size, w1_esz, 0,
				     vgic_its_westowe_dte, NUWW);
	}

	/* scan_its_tabwe wetuwns +1 if aww entwies awe invawid */
	if (wet > 0)
		wet = 0;

	if (wet < 0)
		vgic_its_fwee_device_wist(its->dev->kvm, its);

	wetuwn wet;
}

static int vgic_its_save_cte(stwuct vgic_its *its,
			     stwuct its_cowwection *cowwection,
			     gpa_t gpa, int esz)
{
	u64 vaw;

	vaw = (1UWW << KVM_ITS_CTE_VAWID_SHIFT |
	       ((u64)cowwection->tawget_addw << KVM_ITS_CTE_WDBASE_SHIFT) |
	       cowwection->cowwection_id);
	vaw = cpu_to_we64(vaw);
	wetuwn vgic_wwite_guest_wock(its->dev->kvm, gpa, &vaw, esz);
}

/*
 * Westowe a cowwection entwy into the ITS cowwection tabwe.
 * Wetuwn +1 on success, 0 if the entwy was invawid (which shouwd be
 * intewpweted as end-of-tabwe), and a negative ewwow vawue fow genewic ewwows.
 */
static int vgic_its_westowe_cte(stwuct vgic_its *its, gpa_t gpa, int esz)
{
	stwuct its_cowwection *cowwection;
	stwuct kvm *kvm = its->dev->kvm;
	u32 tawget_addw, coww_id;
	u64 vaw;
	int wet;

	BUG_ON(esz > sizeof(vaw));
	wet = kvm_wead_guest_wock(kvm, gpa, &vaw, esz);
	if (wet)
		wetuwn wet;
	vaw = we64_to_cpu(vaw);
	if (!(vaw & KVM_ITS_CTE_VAWID_MASK))
		wetuwn 0;

	tawget_addw = (u32)(vaw >> KVM_ITS_CTE_WDBASE_SHIFT);
	coww_id = vaw & KVM_ITS_CTE_ICID_MASK;

	if (tawget_addw != COWWECTION_NOT_MAPPED &&
	    !kvm_get_vcpu_by_id(kvm, tawget_addw))
		wetuwn -EINVAW;

	cowwection = find_cowwection(its, coww_id);
	if (cowwection)
		wetuwn -EEXIST;

	if (!vgic_its_check_id(its, its->basew_coww_tabwe, coww_id, NUWW))
		wetuwn -EINVAW;

	wet = vgic_its_awwoc_cowwection(its, &cowwection, coww_id);
	if (wet)
		wetuwn wet;
	cowwection->tawget_addw = tawget_addw;
	wetuwn 1;
}

/**
 * vgic_its_save_cowwection_tabwe - Save the cowwection tabwe into
 * guest WAM
 */
static int vgic_its_save_cowwection_tabwe(stwuct vgic_its *its)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 basew = its->basew_coww_tabwe;
	gpa_t gpa = GITS_BASEW_ADDW_48_to_52(basew);
	stwuct its_cowwection *cowwection;
	u64 vaw;
	size_t max_size, fiwwed = 0;
	int wet, cte_esz = abi->cte_esz;

	if (!(basew & GITS_BASEW_VAWID))
		wetuwn 0;

	max_size = GITS_BASEW_NW_PAGES(basew) * SZ_64K;

	wist_fow_each_entwy(cowwection, &its->cowwection_wist, coww_wist) {
		wet = vgic_its_save_cte(its, cowwection, gpa, cte_esz);
		if (wet)
			wetuwn wet;
		gpa += cte_esz;
		fiwwed += cte_esz;
	}

	if (fiwwed == max_size)
		wetuwn 0;

	/*
	 * tabwe is not fuwwy fiwwed, add a wast dummy ewement
	 * with vawid bit unset
	 */
	vaw = 0;
	BUG_ON(cte_esz > sizeof(vaw));
	wet = vgic_wwite_guest_wock(its->dev->kvm, gpa, &vaw, cte_esz);
	wetuwn wet;
}

/**
 * vgic_its_westowe_cowwection_tabwe - weads the cowwection tabwe
 * in guest memowy and westowes the ITS intewnaw state. Wequiwes the
 * BASEW wegistews to be westowed befowe.
 */
static int vgic_its_westowe_cowwection_tabwe(stwuct vgic_its *its)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 basew = its->basew_coww_tabwe;
	int cte_esz = abi->cte_esz;
	size_t max_size, wead = 0;
	gpa_t gpa;
	int wet;

	if (!(basew & GITS_BASEW_VAWID))
		wetuwn 0;

	gpa = GITS_BASEW_ADDW_48_to_52(basew);

	max_size = GITS_BASEW_NW_PAGES(basew) * SZ_64K;

	whiwe (wead < max_size) {
		wet = vgic_its_westowe_cte(its, gpa, cte_esz);
		if (wet <= 0)
			bweak;
		gpa += cte_esz;
		wead += cte_esz;
	}

	if (wet > 0)
		wetuwn 0;

	if (wet < 0)
		vgic_its_fwee_cowwection_wist(its->dev->kvm, its);

	wetuwn wet;
}

/**
 * vgic_its_save_tabwes_v0 - Save the ITS tabwes into guest AWM
 * accowding to v0 ABI
 */
static int vgic_its_save_tabwes_v0(stwuct vgic_its *its)
{
	int wet;

	wet = vgic_its_save_device_tabwes(its);
	if (wet)
		wetuwn wet;

	wetuwn vgic_its_save_cowwection_tabwe(its);
}

/**
 * vgic_its_westowe_tabwes_v0 - Westowe the ITS tabwes fwom guest WAM
 * to intewnaw data stwucts accowding to V0 ABI
 *
 */
static int vgic_its_westowe_tabwes_v0(stwuct vgic_its *its)
{
	int wet;

	wet = vgic_its_westowe_cowwection_tabwe(its);
	if (wet)
		wetuwn wet;

	wet = vgic_its_westowe_device_tabwes(its);
	if (wet)
		vgic_its_fwee_cowwection_wist(its->dev->kvm, its);
	wetuwn wet;
}

static int vgic_its_commit_v0(stwuct vgic_its *its)
{
	const stwuct vgic_its_abi *abi;

	abi = vgic_its_get_abi(its);
	its->basew_coww_tabwe &= ~GITS_BASEW_ENTWY_SIZE_MASK;
	its->basew_device_tabwe &= ~GITS_BASEW_ENTWY_SIZE_MASK;

	its->basew_coww_tabwe |= (GIC_ENCODE_SZ(abi->cte_esz, 5)
					<< GITS_BASEW_ENTWY_SIZE_SHIFT);

	its->basew_device_tabwe |= (GIC_ENCODE_SZ(abi->dte_esz, 5)
					<< GITS_BASEW_ENTWY_SIZE_SHIFT);
	wetuwn 0;
}

static void vgic_its_weset(stwuct kvm *kvm, stwuct vgic_its *its)
{
	/* We need to keep the ABI specific fiewd vawues */
	its->basew_coww_tabwe &= ~GITS_BASEW_VAWID;
	its->basew_device_tabwe &= ~GITS_BASEW_VAWID;
	its->cbasew = 0;
	its->cweadw = 0;
	its->cwwitew = 0;
	its->enabwed = 0;
	vgic_its_fwee_device_wist(kvm, its);
	vgic_its_fwee_cowwection_wist(kvm, its);
}

static int vgic_its_has_attw(stwuct kvm_device *dev,
			     stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW:
		switch (attw->attw) {
		case KVM_VGIC_ITS_ADDW_TYPE:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_CTWW:
		switch (attw->attw) {
		case KVM_DEV_AWM_VGIC_CTWW_INIT:
			wetuwn 0;
		case KVM_DEV_AWM_ITS_CTWW_WESET:
			wetuwn 0;
		case KVM_DEV_AWM_ITS_SAVE_TABWES:
			wetuwn 0;
		case KVM_DEV_AWM_ITS_WESTOWE_TABWES:
			wetuwn 0;
		}
		bweak;
	case KVM_DEV_AWM_VGIC_GWP_ITS_WEGS:
		wetuwn vgic_its_has_attw_wegs(dev, attw);
	}
	wetuwn -ENXIO;
}

static int vgic_its_ctww(stwuct kvm *kvm, stwuct vgic_its *its, u64 attw)
{
	const stwuct vgic_its_abi *abi = vgic_its_get_abi(its);
	int wet = 0;

	if (attw == KVM_DEV_AWM_VGIC_CTWW_INIT) /* Nothing to do */
		wetuwn 0;

	mutex_wock(&kvm->wock);

	if (!wock_aww_vcpus(kvm)) {
		mutex_unwock(&kvm->wock);
		wetuwn -EBUSY;
	}

	mutex_wock(&kvm->awch.config_wock);
	mutex_wock(&its->its_wock);

	switch (attw) {
	case KVM_DEV_AWM_ITS_CTWW_WESET:
		vgic_its_weset(kvm, its);
		bweak;
	case KVM_DEV_AWM_ITS_SAVE_TABWES:
		wet = abi->save_tabwes(its);
		bweak;
	case KVM_DEV_AWM_ITS_WESTOWE_TABWES:
		wet = abi->westowe_tabwes(its);
		bweak;
	}

	mutex_unwock(&its->its_wock);
	mutex_unwock(&kvm->awch.config_wock);
	unwock_aww_vcpus(kvm);
	mutex_unwock(&kvm->wock);
	wetuwn wet;
}

/*
 * kvm_awch_awwow_wwite_without_wunning_vcpu - awwow wwiting guest memowy
 * without the wunning VCPU when diwty wing is enabwed.
 *
 * The wunning VCPU is wequiwed to twack diwty guest pages when diwty wing
 * is enabwed. Othewwise, the backup bitmap shouwd be used to twack the
 * diwty guest pages. When vgic/its tabwes awe being saved, the backup
 * bitmap is used to twack the diwty guest pages due to the missed wunning
 * VCPU in the pewiod.
 */
boow kvm_awch_awwow_wwite_without_wunning_vcpu(stwuct kvm *kvm)
{
	stwuct vgic_dist *dist = &kvm->awch.vgic;

	wetuwn dist->tabwe_wwite_in_pwogwess;
}

static int vgic_its_set_attw(stwuct kvm_device *dev,
			     stwuct kvm_device_attw *attw)
{
	stwuct vgic_its *its = dev->pwivate;
	int wet;

	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW: {
		u64 __usew *uaddw = (u64 __usew *)(wong)attw->addw;
		unsigned wong type = (unsigned wong)attw->attw;
		u64 addw;

		if (type != KVM_VGIC_ITS_ADDW_TYPE)
			wetuwn -ENODEV;

		if (copy_fwom_usew(&addw, uaddw, sizeof(addw)))
			wetuwn -EFAUWT;

		wet = vgic_check_iowange(dev->kvm, its->vgic_its_base,
					 addw, SZ_64K, KVM_VGIC_V3_ITS_SIZE);
		if (wet)
			wetuwn wet;

		wetuwn vgic_wegistew_its_iodev(dev->kvm, its, addw);
	}
	case KVM_DEV_AWM_VGIC_GWP_CTWW:
		wetuwn vgic_its_ctww(dev->kvm, its, attw->attw);
	case KVM_DEV_AWM_VGIC_GWP_ITS_WEGS: {
		u64 __usew *uaddw = (u64 __usew *)(wong)attw->addw;
		u64 weg;

		if (get_usew(weg, uaddw))
			wetuwn -EFAUWT;

		wetuwn vgic_its_attw_wegs_access(dev, attw, &weg, twue);
	}
	}
	wetuwn -ENXIO;
}

static int vgic_its_get_attw(stwuct kvm_device *dev,
			     stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_AWM_VGIC_GWP_ADDW: {
		stwuct vgic_its *its = dev->pwivate;
		u64 addw = its->vgic_its_base;
		u64 __usew *uaddw = (u64 __usew *)(wong)attw->addw;
		unsigned wong type = (unsigned wong)attw->attw;

		if (type != KVM_VGIC_ITS_ADDW_TYPE)
			wetuwn -ENODEV;

		if (copy_to_usew(uaddw, &addw, sizeof(addw)))
			wetuwn -EFAUWT;
		bweak;
	}
	case KVM_DEV_AWM_VGIC_GWP_ITS_WEGS: {
		u64 __usew *uaddw = (u64 __usew *)(wong)attw->addw;
		u64 weg;
		int wet;

		wet = vgic_its_attw_wegs_access(dev, attw, &weg, fawse);
		if (wet)
			wetuwn wet;
		wetuwn put_usew(weg, uaddw);
	}
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static stwuct kvm_device_ops kvm_awm_vgic_its_ops = {
	.name = "kvm-awm-vgic-its",
	.cweate = vgic_its_cweate,
	.destwoy = vgic_its_destwoy,
	.set_attw = vgic_its_set_attw,
	.get_attw = vgic_its_get_attw,
	.has_attw = vgic_its_has_attw,
};

int kvm_vgic_wegistew_its_device(void)
{
	wetuwn kvm_wegistew_device_ops(&kvm_awm_vgic_its_ops,
				       KVM_DEV_TYPE_AWM_VGIC_ITS);
}
