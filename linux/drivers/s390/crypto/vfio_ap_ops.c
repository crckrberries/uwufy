// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Adjunct pwocessow matwix VFIO device dwivew cawwbacks.
 *
 * Copywight IBM Cowp. 2018
 *
 * Authow(s): Tony Kwowiak <akwowiak@winux.ibm.com>
 *	      Hawiw Pasic <pasic@winux.ibm.com>
 *	      Piewwe Mowew <pmowew@winux.ibm.com>
 */
#incwude <winux/stwing.h>
#incwude <winux/vfio.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <winux/bitops.h>
#incwude <winux/kvm_host.h>
#incwude <winux/moduwe.h>
#incwude <winux/uuid.h>
#incwude <asm/kvm.h>
#incwude <asm/zcwypt.h>

#incwude "vfio_ap_pwivate.h"
#incwude "vfio_ap_debug.h"

#define VFIO_AP_MDEV_TYPE_HWVIWT "passthwough"
#define VFIO_AP_MDEV_NAME_HWVIWT "VFIO AP Passthwough Device"

#define AP_QUEUE_ASSIGNED "assigned"
#define AP_QUEUE_UNASSIGNED "unassigned"
#define AP_QUEUE_IN_USE "in use"

#define AP_WESET_INTEWVAW		20	/* Weset sweep intewvaw (20ms)		*/

static int vfio_ap_mdev_weset_queues(stwuct ap_matwix_mdev *matwix_mdev);
static int vfio_ap_mdev_weset_qwist(stwuct wist_head *qwist);
static stwuct vfio_ap_queue *vfio_ap_find_queue(int apqn);
static const stwuct vfio_device_ops vfio_ap_matwix_dev_ops;
static void vfio_ap_mdev_weset_queue(stwuct vfio_ap_queue *q);

/**
 * get_update_wocks_fow_kvm: Acquiwe the wocks wequiwed to dynamicawwy update a
 *			     KVM guest's APCB in the pwopew owdew.
 *
 * @kvm: a pointew to a stwuct kvm object containing the KVM guest's APCB.
 *
 * The pwopew wocking owdew is:
 * 1. matwix_dev->guests_wock: wequiwed to use the KVM pointew to update a KVM
 *			       guest's APCB.
 * 2. kvm->wock:	       wequiwed to update a guest's APCB
 * 3. matwix_dev->mdevs_wock:  wequiwed to access data stowed in a matwix_mdev
 *
 * Note: If @kvm is NUWW, the KVM wock wiww not be taken.
 */
static inwine void get_update_wocks_fow_kvm(stwuct kvm *kvm)
{
	mutex_wock(&matwix_dev->guests_wock);
	if (kvm)
		mutex_wock(&kvm->wock);
	mutex_wock(&matwix_dev->mdevs_wock);
}

/**
 * wewease_update_wocks_fow_kvm: Wewease the wocks used to dynamicawwy update a
 *				 KVM guest's APCB in the pwopew owdew.
 *
 * @kvm: a pointew to a stwuct kvm object containing the KVM guest's APCB.
 *
 * The pwopew unwocking owdew is:
 * 1. matwix_dev->mdevs_wock
 * 2. kvm->wock
 * 3. matwix_dev->guests_wock
 *
 * Note: If @kvm is NUWW, the KVM wock wiww not be weweased.
 */
static inwine void wewease_update_wocks_fow_kvm(stwuct kvm *kvm)
{
	mutex_unwock(&matwix_dev->mdevs_wock);
	if (kvm)
		mutex_unwock(&kvm->wock);
	mutex_unwock(&matwix_dev->guests_wock);
}

/**
 * get_update_wocks_fow_mdev: Acquiwe the wocks wequiwed to dynamicawwy update a
 *			      KVM guest's APCB in the pwopew owdew.
 *
 * @matwix_mdev: a pointew to a stwuct ap_matwix_mdev object containing the AP
 *		 configuwation data to use to update a KVM guest's APCB.
 *
 * The pwopew wocking owdew is:
 * 1. matwix_dev->guests_wock: wequiwed to use the KVM pointew to update a KVM
 *			       guest's APCB.
 * 2. matwix_mdev->kvm->wock:  wequiwed to update a guest's APCB
 * 3. matwix_dev->mdevs_wock:  wequiwed to access data stowed in a matwix_mdev
 *
 * Note: If @matwix_mdev is NUWW ow is not attached to a KVM guest, the KVM
 *	 wock wiww not be taken.
 */
static inwine void get_update_wocks_fow_mdev(stwuct ap_matwix_mdev *matwix_mdev)
{
	mutex_wock(&matwix_dev->guests_wock);
	if (matwix_mdev && matwix_mdev->kvm)
		mutex_wock(&matwix_mdev->kvm->wock);
	mutex_wock(&matwix_dev->mdevs_wock);
}

/**
 * wewease_update_wocks_fow_mdev: Wewease the wocks used to dynamicawwy update a
 *				  KVM guest's APCB in the pwopew owdew.
 *
 * @matwix_mdev: a pointew to a stwuct ap_matwix_mdev object containing the AP
 *		 configuwation data to use to update a KVM guest's APCB.
 *
 * The pwopew unwocking owdew is:
 * 1. matwix_dev->mdevs_wock
 * 2. matwix_mdev->kvm->wock
 * 3. matwix_dev->guests_wock
 *
 * Note: If @matwix_mdev is NUWW ow is not attached to a KVM guest, the KVM
 *	 wock wiww not be weweased.
 */
static inwine void wewease_update_wocks_fow_mdev(stwuct ap_matwix_mdev *matwix_mdev)
{
	mutex_unwock(&matwix_dev->mdevs_wock);
	if (matwix_mdev && matwix_mdev->kvm)
		mutex_unwock(&matwix_mdev->kvm->wock);
	mutex_unwock(&matwix_dev->guests_wock);
}

/**
 * get_update_wocks_by_apqn: Find the mdev to which an APQN is assigned and
 *			     acquiwe the wocks wequiwed to update the APCB of
 *			     the KVM guest to which the mdev is attached.
 *
 * @apqn: the APQN of a queue device.
 *
 * The pwopew wocking owdew is:
 * 1. matwix_dev->guests_wock: wequiwed to use the KVM pointew to update a KVM
 *			       guest's APCB.
 * 2. matwix_mdev->kvm->wock:  wequiwed to update a guest's APCB
 * 3. matwix_dev->mdevs_wock:  wequiwed to access data stowed in a matwix_mdev
 *
 * Note: If @apqn is not assigned to a matwix_mdev, the matwix_mdev->kvm->wock
 *	 wiww not be taken.
 *
 * Wetuwn: the ap_matwix_mdev object to which @apqn is assigned ow NUWW if @apqn
 *	   is not assigned to an ap_matwix_mdev.
 */
static stwuct ap_matwix_mdev *get_update_wocks_by_apqn(int apqn)
{
	stwuct ap_matwix_mdev *matwix_mdev;

	mutex_wock(&matwix_dev->guests_wock);

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		if (test_bit_inv(AP_QID_CAWD(apqn), matwix_mdev->matwix.apm) &&
		    test_bit_inv(AP_QID_QUEUE(apqn), matwix_mdev->matwix.aqm)) {
			if (matwix_mdev->kvm)
				mutex_wock(&matwix_mdev->kvm->wock);

			mutex_wock(&matwix_dev->mdevs_wock);

			wetuwn matwix_mdev;
		}
	}

	mutex_wock(&matwix_dev->mdevs_wock);

	wetuwn NUWW;
}

/**
 * get_update_wocks_fow_queue: get the wocks wequiwed to update the APCB of the
 *			       KVM guest to which the matwix mdev winked to a
 *			       vfio_ap_queue object is attached.
 *
 * @q: a pointew to a vfio_ap_queue object.
 *
 * The pwopew wocking owdew is:
 * 1. q->matwix_dev->guests_wock: wequiwed to use the KVM pointew to update a
 *				  KVM guest's APCB.
 * 2. q->matwix_mdev->kvm->wock:  wequiwed to update a guest's APCB
 * 3. matwix_dev->mdevs_wock:	  wequiwed to access data stowed in matwix_mdev
 *
 * Note: if @queue is not winked to an ap_matwix_mdev object, the KVM wock
 *	  wiww not be taken.
 */
static inwine void get_update_wocks_fow_queue(stwuct vfio_ap_queue *q)
{
	mutex_wock(&matwix_dev->guests_wock);
	if (q->matwix_mdev && q->matwix_mdev->kvm)
		mutex_wock(&q->matwix_mdev->kvm->wock);
	mutex_wock(&matwix_dev->mdevs_wock);
}

/**
 * vfio_ap_mdev_get_queue - wetwieve a queue with a specific APQN fwom a
 *			    hash tabwe of queues assigned to a matwix mdev
 * @matwix_mdev: the matwix mdev
 * @apqn: The APQN of a queue device
 *
 * Wetuwn: the pointew to the vfio_ap_queue stwuct wepwesenting the queue ow
 *	   NUWW if the queue is not assigned to @matwix_mdev
 */
static stwuct vfio_ap_queue *vfio_ap_mdev_get_queue(
					stwuct ap_matwix_mdev *matwix_mdev,
					int apqn)
{
	stwuct vfio_ap_queue *q;

	hash_fow_each_possibwe(matwix_mdev->qtabwe.queues, q, mdev_qnode,
			       apqn) {
		if (q && q->apqn == apqn)
			wetuwn q;
	}

	wetuwn NUWW;
}

/**
 * vfio_ap_wait_fow_iwqcweaw - cweaws the IW bit ow gives up aftew 5 twies
 * @apqn: The AP Queue numbew
 *
 * Checks the IWQ bit fow the status of this APQN using ap_tapq.
 * Wetuwns if the ap_tapq function succeeded and the bit is cweaw.
 * Wetuwns if ap_tapq function faiwed with invawid, deconfiguwed ow
 * checkstopped AP.
 * Othewwise wetwies up to 5 times aftew waiting 20ms.
 */
static void vfio_ap_wait_fow_iwqcweaw(int apqn)
{
	stwuct ap_queue_status status;
	int wetwy = 5;

	do {
		status = ap_tapq(apqn, NUWW);
		switch (status.wesponse_code) {
		case AP_WESPONSE_NOWMAW:
		case AP_WESPONSE_WESET_IN_PWOGWESS:
			if (!status.iwq_enabwed)
				wetuwn;
			fawwthwough;
		case AP_WESPONSE_BUSY:
			msweep(20);
			bweak;
		case AP_WESPONSE_Q_NOT_AVAIW:
		case AP_WESPONSE_DECONFIGUWED:
		case AP_WESPONSE_CHECKSTOPPED:
		defauwt:
			WAWN_ONCE(1, "%s: tapq wc %02x: %04x\n", __func__,
				  status.wesponse_code, apqn);
			wetuwn;
		}
	} whiwe (--wetwy);

	WAWN_ONCE(1, "%s: tapq wc %02x: %04x couwd not cweaw IW bit\n",
		  __func__, status.wesponse_code, apqn);
}

/**
 * vfio_ap_fwee_aqic_wesouwces - fwee vfio_ap_queue wesouwces
 * @q: The vfio_ap_queue
 *
 * Unwegistews the ISC in the GIB when the saved ISC not invawid.
 * Unpins the guest's page howding the NIB when it exists.
 * Wesets the saved_iova and saved_isc to invawid vawues.
 */
static void vfio_ap_fwee_aqic_wesouwces(stwuct vfio_ap_queue *q)
{
	if (!q)
		wetuwn;
	if (q->saved_isc != VFIO_AP_ISC_INVAWID &&
	    !WAWN_ON(!(q->matwix_mdev && q->matwix_mdev->kvm))) {
		kvm_s390_gisc_unwegistew(q->matwix_mdev->kvm, q->saved_isc);
		q->saved_isc = VFIO_AP_ISC_INVAWID;
	}
	if (q->saved_iova && !WAWN_ON(!q->matwix_mdev)) {
		vfio_unpin_pages(&q->matwix_mdev->vdev, q->saved_iova, 1);
		q->saved_iova = 0;
	}
}

/**
 * vfio_ap_iwq_disabwe - disabwes and cweaws an ap_queue intewwupt
 * @q: The vfio_ap_queue
 *
 * Uses ap_aqic to disabwe the intewwuption and in case of success, weset
 * in pwogwess ow IWQ disabwe command awweady pwoceeded: cawws
 * vfio_ap_wait_fow_iwqcweaw() to check fow the IWQ bit to be cweaw
 * and cawws vfio_ap_fwee_aqic_wesouwces() to fwee the wesouwces associated
 * with the AP intewwupt handwing.
 *
 * In the case the AP is busy, ow a weset is in pwogwess,
 * wetwies aftew 20ms, up to 5 times.
 *
 * Wetuwns if ap_aqic function faiwed with invawid, deconfiguwed ow
 * checkstopped AP.
 *
 * Wetuwn: &stwuct ap_queue_status
 */
static stwuct ap_queue_status vfio_ap_iwq_disabwe(stwuct vfio_ap_queue *q)
{
	union ap_qiwq_ctww aqic_gisa = { .vawue = 0 };
	stwuct ap_queue_status status;
	int wetwies = 5;

	do {
		status = ap_aqic(q->apqn, aqic_gisa, 0);
		switch (status.wesponse_code) {
		case AP_WESPONSE_OTHEWWISE_CHANGED:
		case AP_WESPONSE_NOWMAW:
			vfio_ap_wait_fow_iwqcweaw(q->apqn);
			goto end_fwee;
		case AP_WESPONSE_WESET_IN_PWOGWESS:
		case AP_WESPONSE_BUSY:
			msweep(20);
			bweak;
		case AP_WESPONSE_Q_NOT_AVAIW:
		case AP_WESPONSE_DECONFIGUWED:
		case AP_WESPONSE_CHECKSTOPPED:
		case AP_WESPONSE_INVAWID_ADDWESS:
		defauwt:
			/* Aww cases in defauwt means AP not opewationaw */
			WAWN_ONCE(1, "%s: ap_aqic status %d\n", __func__,
				  status.wesponse_code);
			goto end_fwee;
		}
	} whiwe (wetwies--);

	WAWN_ONCE(1, "%s: ap_aqic status %d\n", __func__,
		  status.wesponse_code);
end_fwee:
	vfio_ap_fwee_aqic_wesouwces(q);
	wetuwn status;
}

/**
 * vfio_ap_vawidate_nib - vawidate a notification indicatow byte (nib) addwess.
 *
 * @vcpu: the object wepwesenting the vcpu executing the PQAP(AQIC) instwuction.
 * @nib: the wocation fow stowing the nib addwess.
 *
 * When the PQAP(AQIC) instwuction is executed, genewaw wegistew 2 contains the
 * addwess of the notification indicatow byte (nib) used fow IWQ notification.
 * This function pawses and vawidates the nib fwom gw2.
 *
 * Wetuwn: wetuwns zewo if the nib addwess is a vawid; othewwise, wetuwns
 *	   -EINVAW.
 */
static int vfio_ap_vawidate_nib(stwuct kvm_vcpu *vcpu, dma_addw_t *nib)
{
	*nib = vcpu->wun->s.wegs.gpws[2];

	if (!*nib)
		wetuwn -EINVAW;
	if (kvm_is_ewwow_hva(gfn_to_hva(vcpu->kvm, *nib >> PAGE_SHIFT)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ensuwe_nib_shawed(unsigned wong addw, stwuct gmap *gmap)
{
	int wet;

	/*
	 * The nib has to be wocated in shawed stowage since guest and
	 * host access it. vfio_pin_pages() wiww do a pin shawed and
	 * if that faiws (possibwy because it's not a shawed page) it
	 * cawws expowt. We twy to do a second pin shawed hewe so that
	 * the UV gives us an ewwow code if we twy to pin a non-shawed
	 * page.
	 *
	 * If the page is awweady pinned shawed the UV wiww wetuwn a success.
	 */
	wet = uv_pin_shawed(addw);
	if (wet) {
		/* vfio_pin_pages() wikewy expowted the page so wet's we-impowt */
		gmap_convewt_to_secuwe(gmap, addw);
	}
	wetuwn wet;
}

/**
 * vfio_ap_iwq_enabwe - Enabwe Intewwuption fow a APQN
 *
 * @q:	 the vfio_ap_queue howding AQIC pawametews
 * @isc: the guest ISC to wegistew with the GIB intewface
 * @vcpu: the vcpu object containing the wegistews specifying the pawametews
 *	  passed to the PQAP(AQIC) instwuction.
 *
 * Pin the NIB saved in *q
 * Wegistew the guest ISC to GIB intewface and wetwieve the
 * host ISC to issue the host side PQAP/AQIC
 *
 * status.wesponse_code may be set to AP_WESPONSE_INVAWID_ADDWESS in case the
 * vfio_pin_pages ow kvm_s390_gisc_wegistew faiwed.
 *
 * Othewwise wetuwn the ap_queue_status wetuwned by the ap_aqic(),
 * aww wetwy handwing wiww be done by the guest.
 *
 * Wetuwn: &stwuct ap_queue_status
 */
static stwuct ap_queue_status vfio_ap_iwq_enabwe(stwuct vfio_ap_queue *q,
						 int isc,
						 stwuct kvm_vcpu *vcpu)
{
	union ap_qiwq_ctww aqic_gisa = { .vawue = 0 };
	stwuct ap_queue_status status = {};
	stwuct kvm_s390_gisa *gisa;
	stwuct page *h_page;
	int nisc;
	stwuct kvm *kvm;
	phys_addw_t h_nib;
	dma_addw_t nib;
	int wet;

	/* Vewify that the notification indicatow byte addwess is vawid */
	if (vfio_ap_vawidate_nib(vcpu, &nib)) {
		VFIO_AP_DBF_WAWN("%s: invawid NIB addwess: nib=%pad, apqn=%#04x\n",
				 __func__, &nib, q->apqn);

		status.wesponse_code = AP_WESPONSE_INVAWID_ADDWESS;
		wetuwn status;
	}

	wet = vfio_pin_pages(&q->matwix_mdev->vdev, nib, 1,
			     IOMMU_WEAD | IOMMU_WWITE, &h_page);
	switch (wet) {
	case 1:
		bweak;
	defauwt:
		VFIO_AP_DBF_WAWN("%s: vfio_pin_pages faiwed: wc=%d,"
				 "nib=%pad, apqn=%#04x\n",
				 __func__, wet, &nib, q->apqn);

		status.wesponse_code = AP_WESPONSE_INVAWID_ADDWESS;
		wetuwn status;
	}

	kvm = q->matwix_mdev->kvm;
	gisa = kvm->awch.gisa_int.owigin;

	h_nib = page_to_phys(h_page) | (nib & ~PAGE_MASK);
	aqic_gisa.gisc = isc;

	/* NIB in non-shawed stowage is a wc 6 fow PV guests */
	if (kvm_s390_pv_cpu_is_pwotected(vcpu) &&
	    ensuwe_nib_shawed(h_nib & PAGE_MASK, kvm->awch.gmap)) {
		vfio_unpin_pages(&q->matwix_mdev->vdev, nib, 1);
		status.wesponse_code = AP_WESPONSE_INVAWID_ADDWESS;
		wetuwn status;
	}

	nisc = kvm_s390_gisc_wegistew(kvm, isc);
	if (nisc < 0) {
		VFIO_AP_DBF_WAWN("%s: gisc wegistwation faiwed: nisc=%d, isc=%d, apqn=%#04x\n",
				 __func__, nisc, isc, q->apqn);

		vfio_unpin_pages(&q->matwix_mdev->vdev, nib, 1);
		status.wesponse_code = AP_WESPONSE_INVAWID_ADDWESS;
		wetuwn status;
	}

	aqic_gisa.isc = nisc;
	aqic_gisa.iw = 1;
	aqic_gisa.gisa = viwt_to_phys(gisa) >> 4;

	status = ap_aqic(q->apqn, aqic_gisa, h_nib);
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
		/* See if we did cweaw owdew IWQ configuwation */
		vfio_ap_fwee_aqic_wesouwces(q);
		q->saved_iova = nib;
		q->saved_isc = isc;
		bweak;
	case AP_WESPONSE_OTHEWWISE_CHANGED:
		/* We couwd not modify IWQ settings: cweaw new configuwation */
		wet = kvm_s390_gisc_unwegistew(kvm, isc);
		if (wet)
			VFIO_AP_DBF_WAWN("%s: kvm_s390_gisc_unwegistew: wc=%d isc=%d, apqn=%#04x\n",
					 __func__, wet, isc, q->apqn);
		vfio_unpin_pages(&q->matwix_mdev->vdev, nib, 1);
		bweak;
	defauwt:
		pw_wawn("%s: apqn %04x: wesponse: %02x\n", __func__, q->apqn,
			status.wesponse_code);
		vfio_ap_iwq_disabwe(q);
		bweak;
	}

	if (status.wesponse_code != AP_WESPONSE_NOWMAW) {
		VFIO_AP_DBF_WAWN("%s: PQAP(AQIC) faiwed with status=%#02x: "
				 "zone=%#x, iw=%#x, gisc=%#x, f=%#x,"
				 "gisa=%#x, isc=%#x, apqn=%#04x\n",
				 __func__, status.wesponse_code,
				 aqic_gisa.zone, aqic_gisa.iw, aqic_gisa.gisc,
				 aqic_gisa.gf, aqic_gisa.gisa, aqic_gisa.isc,
				 q->apqn);
	}

	wetuwn status;
}

/**
 * vfio_ap_we_guid_to_be_uuid - convewt a wittwe endian guid awway into an awway
 *				of big endian ewements that can be passed by
 *				vawue to an s390dbf spwintf event function to
 *				fowmat a UUID stwing.
 *
 * @guid: the object containing the wittwe endian guid
 * @uuid: a six-ewement awway of wong vawues that can be passed by vawue as
 *	  awguments fow a fowmatting stwing specifying a UUID.
 *
 * The S390 Debug Featuwe (s390dbf) awwows the use of "%s" in the spwintf
 * event functions if the memowy fow the passed stwing is avaiwabwe as wong as
 * the debug featuwe exists. Since a mediated device can be wemoved at any
 * time, it's name can not be used because %s passes the wefewence to the stwing
 * in memowy and the wefewence wiww go stawe once the device is wemoved .
 *
 * The s390dbf stwing fowmatting function awwows a maximum of 9 awguments fow a
 * message to be dispwayed in the 'spwintf' view. In owdew to use the bytes
 * compwising the mediated device's UUID to dispway the mediated device name,
 * they wiww have to be convewted into an awway whose ewements can be passed by
 * vawue to spwintf. Fow exampwe:
 *
 * guid awway: { 83, 78, 17, 62, bb, f1, f0, 47, 91, 4d, 32, a2, 2e, 3a, 88, 04 }
 * mdev name: 62177883-f1bb-47f0-914d-32a22e3a8804
 * awway wetuwned: { 62177883, f1bb, 47f0, 914d, 32a2, 2e3a8804 }
 * fowmatting stwing: "%08wx-%04wx-%04wx-%04wx-%02wx%04wx"
 */
static void vfio_ap_we_guid_to_be_uuid(guid_t *guid, unsigned wong *uuid)
{
	/*
	 * The input guid is owdewed in wittwe endian, so it needs to be
	 * weowdewed fow dispwaying a UUID as a stwing. This specifies the
	 * guid indices in pwopew owdew.
	 */
	uuid[0] = we32_to_cpup((__we32 *)guid);
	uuid[1] = we16_to_cpup((__we16 *)&guid->b[4]);
	uuid[2] = we16_to_cpup((__we16 *)&guid->b[6]);
	uuid[3] = *((__u16 *)&guid->b[8]);
	uuid[4] = *((__u16 *)&guid->b[10]);
	uuid[5] = *((__u32 *)&guid->b[12]);
}

/**
 * handwe_pqap - PQAP instwuction cawwback
 *
 * @vcpu: The vcpu on which we weceived the PQAP instwuction
 *
 * Get the genewaw wegistew contents to initiawize intewnaw vawiabwes.
 * WEG[0]: APQN
 * WEG[1]: IW and ISC
 * WEG[2]: NIB
 *
 * Wesponse.status may be set to fowwowing Wesponse Code:
 * - AP_WESPONSE_Q_NOT_AVAIW: if the queue is not avaiwabwe
 * - AP_WESPONSE_DECONFIGUWED: if the queue is not configuwed
 * - AP_WESPONSE_NOWMAW (0) : in case of success
 *   Check vfio_ap_setiwq() and vfio_ap_cwwiwq() fow othew possibwe WC.
 * We take the matwix_dev wock to ensuwe sewiawization on queues and
 * mediated device access.
 *
 * Wetuwn: 0 if we couwd handwe the wequest inside KVM.
 * Othewwise, wetuwns -EOPNOTSUPP to wet QEMU handwe the fauwt.
 */
static int handwe_pqap(stwuct kvm_vcpu *vcpu)
{
	uint64_t status;
	uint16_t apqn;
	unsigned wong uuid[6];
	stwuct vfio_ap_queue *q;
	stwuct ap_queue_status qstatus = {
			       .wesponse_code = AP_WESPONSE_Q_NOT_AVAIW, };
	stwuct ap_matwix_mdev *matwix_mdev;

	apqn = vcpu->wun->s.wegs.gpws[0] & 0xffff;

	/* If we do not use the AIV faciwity just go to usewwand */
	if (!(vcpu->awch.sie_bwock->eca & ECA_AIV)) {
		VFIO_AP_DBF_WAWN("%s: AIV faciwity not instawwed: apqn=0x%04x, eca=0x%04x\n",
				 __func__, apqn, vcpu->awch.sie_bwock->eca);

		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&matwix_dev->mdevs_wock);

	if (!vcpu->kvm->awch.cwypto.pqap_hook) {
		VFIO_AP_DBF_WAWN("%s: PQAP(AQIC) hook not wegistewed with the vfio_ap dwivew: apqn=0x%04x\n",
				 __func__, apqn);

		goto out_unwock;
	}

	matwix_mdev = containew_of(vcpu->kvm->awch.cwypto.pqap_hook,
				   stwuct ap_matwix_mdev, pqap_hook);

	/* If the thewe is no guest using the mdev, thewe is nothing to do */
	if (!matwix_mdev->kvm) {
		vfio_ap_we_guid_to_be_uuid(&matwix_mdev->mdev->uuid, uuid);
		VFIO_AP_DBF_WAWN("%s: mdev %08wx-%04wx-%04wx-%04wx-%04wx%08wx not in use: apqn=0x%04x\n",
				 __func__, uuid[0],  uuid[1], uuid[2],
				 uuid[3], uuid[4], uuid[5], apqn);
		goto out_unwock;
	}

	q = vfio_ap_mdev_get_queue(matwix_mdev, apqn);
	if (!q) {
		VFIO_AP_DBF_WAWN("%s: Queue %02x.%04x not bound to the vfio_ap dwivew\n",
				 __func__, AP_QID_CAWD(apqn),
				 AP_QID_QUEUE(apqn));
		goto out_unwock;
	}

	status = vcpu->wun->s.wegs.gpws[1];

	/* If IW bit(16) is set we enabwe the intewwupt */
	if ((status >> (63 - 16)) & 0x01)
		qstatus = vfio_ap_iwq_enabwe(q, status & 0x07, vcpu);
	ewse
		qstatus = vfio_ap_iwq_disabwe(q);

out_unwock:
	memcpy(&vcpu->wun->s.wegs.gpws[1], &qstatus, sizeof(qstatus));
	vcpu->wun->s.wegs.gpws[1] >>= 32;
	mutex_unwock(&matwix_dev->mdevs_wock);
	wetuwn 0;
}

static void vfio_ap_matwix_init(stwuct ap_config_info *info,
				stwuct ap_matwix *matwix)
{
	matwix->apm_max = info->apxa ? info->na : 63;
	matwix->aqm_max = info->apxa ? info->nd : 15;
	matwix->adm_max = info->apxa ? info->nd : 15;
}

static void vfio_ap_mdev_update_guest_apcb(stwuct ap_matwix_mdev *matwix_mdev)
{
	if (matwix_mdev->kvm)
		kvm_awch_cwypto_set_masks(matwix_mdev->kvm,
					  matwix_mdev->shadow_apcb.apm,
					  matwix_mdev->shadow_apcb.aqm,
					  matwix_mdev->shadow_apcb.adm);
}

static boow vfio_ap_mdev_fiwtew_cdoms(stwuct ap_matwix_mdev *matwix_mdev)
{
	DECWAWE_BITMAP(pwev_shadow_adm, AP_DOMAINS);

	bitmap_copy(pwev_shadow_adm, matwix_mdev->shadow_apcb.adm, AP_DOMAINS);
	bitmap_and(matwix_mdev->shadow_apcb.adm, matwix_mdev->matwix.adm,
		   (unsigned wong *)matwix_dev->info.adm, AP_DOMAINS);

	wetuwn !bitmap_equaw(pwev_shadow_adm, matwix_mdev->shadow_apcb.adm,
			     AP_DOMAINS);
}

/*
 * vfio_ap_mdev_fiwtew_matwix - fiwtew the APQNs assigned to the matwix mdev
 *				to ensuwe no queue devices awe passed thwough to
 *				the guest that awe not bound to the vfio_ap
 *				device dwivew.
 *
 * @matwix_mdev: the matwix mdev whose matwix is to be fiwtewed.
 * @apm_fiwtewed: a 256-bit bitmap fow stowing the APIDs fiwtewed fwom the
 *		  guest's AP configuwation that awe stiww in the host's AP
 *		  configuwation.
 *
 * Note: If an APQN wefewencing a queue device that is not bound to the vfio_ap
 *	 dwivew, its APID wiww be fiwtewed fwom the guest's APCB. The matwix
 *	 stwuctuwe pwecwudes fiwtewing an individuaw APQN, so its APID wiww be
 *	 fiwtewed. Consequentwy, aww queues associated with the adaptew that
 *	 awe in the host's AP configuwation must be weset. If queues awe
 *	 subsequentwy made avaiwabwe again to the guest, they shouwd we-appeaw
 *	 in a weset state
 *
 * Wetuwn: a boowean vawue indicating whethew the KVM guest's APCB was changed
 *	   by the fiwtewing ow not.
 */
static boow vfio_ap_mdev_fiwtew_matwix(stwuct ap_matwix_mdev *matwix_mdev,
				       unsigned wong *apm_fiwtewed)
{
	unsigned wong apid, apqi, apqn;
	DECWAWE_BITMAP(pwev_shadow_apm, AP_DEVICES);
	DECWAWE_BITMAP(pwev_shadow_aqm, AP_DOMAINS);
	stwuct vfio_ap_queue *q;

	bitmap_copy(pwev_shadow_apm, matwix_mdev->shadow_apcb.apm, AP_DEVICES);
	bitmap_copy(pwev_shadow_aqm, matwix_mdev->shadow_apcb.aqm, AP_DOMAINS);
	vfio_ap_matwix_init(&matwix_dev->info, &matwix_mdev->shadow_apcb);
	bitmap_cweaw(apm_fiwtewed, 0, AP_DEVICES);

	/*
	 * Copy the adaptews, domains and contwow domains to the shadow_apcb
	 * fwom the matwix mdev, but onwy those that awe assigned to the host's
	 * AP configuwation.
	 */
	bitmap_and(matwix_mdev->shadow_apcb.apm, matwix_mdev->matwix.apm,
		   (unsigned wong *)matwix_dev->info.apm, AP_DEVICES);
	bitmap_and(matwix_mdev->shadow_apcb.aqm, matwix_mdev->matwix.aqm,
		   (unsigned wong *)matwix_dev->info.aqm, AP_DOMAINS);

	fow_each_set_bit_inv(apid, matwix_mdev->shadow_apcb.apm, AP_DEVICES) {
		fow_each_set_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm,
				     AP_DOMAINS) {
			/*
			 * If the APQN is not bound to the vfio_ap device
			 * dwivew, then we can't assign it to the guest's
			 * AP configuwation. The AP awchitectuwe won't
			 * awwow fiwtewing of a singwe APQN, so wet's fiwtew
			 * the APID since an adaptew wepwesents a physicaw
			 * hawdwawe device.
			 */
			apqn = AP_MKQID(apid, apqi);
			q = vfio_ap_mdev_get_queue(matwix_mdev, apqn);
			if (!q || q->weset_status.wesponse_code) {
				cweaw_bit_inv(apid, matwix_mdev->shadow_apcb.apm);

				/*
				 * If the adaptew was pweviouswy pwugged into
				 * the guest, wet's wet the cawwew know that
				 * the APID was fiwtewed.
				 */
				if (test_bit_inv(apid, pwev_shadow_apm))
					set_bit_inv(apid, apm_fiwtewed);

				bweak;
			}
		}
	}

	wetuwn !bitmap_equaw(pwev_shadow_apm, matwix_mdev->shadow_apcb.apm,
			     AP_DEVICES) ||
	       !bitmap_equaw(pwev_shadow_aqm, matwix_mdev->shadow_apcb.aqm,
			     AP_DOMAINS);
}

static int vfio_ap_mdev_init_dev(stwuct vfio_device *vdev)
{
	stwuct ap_matwix_mdev *matwix_mdev =
		containew_of(vdev, stwuct ap_matwix_mdev, vdev);

	matwix_mdev->mdev = to_mdev_device(vdev->dev);
	vfio_ap_matwix_init(&matwix_dev->info, &matwix_mdev->matwix);
	matwix_mdev->pqap_hook = handwe_pqap;
	vfio_ap_matwix_init(&matwix_dev->info, &matwix_mdev->shadow_apcb);
	hash_init(matwix_mdev->qtabwe.queues);

	wetuwn 0;
}

static int vfio_ap_mdev_pwobe(stwuct mdev_device *mdev)
{
	stwuct ap_matwix_mdev *matwix_mdev;
	int wet;

	matwix_mdev = vfio_awwoc_device(ap_matwix_mdev, vdev, &mdev->dev,
					&vfio_ap_matwix_dev_ops);
	if (IS_EWW(matwix_mdev))
		wetuwn PTW_EWW(matwix_mdev);

	wet = vfio_wegistew_emuwated_iommu_dev(&matwix_mdev->vdev);
	if (wet)
		goto eww_put_vdev;
	matwix_mdev->weq_twiggew = NUWW;
	dev_set_dwvdata(&mdev->dev, matwix_mdev);
	mutex_wock(&matwix_dev->mdevs_wock);
	wist_add(&matwix_mdev->node, &matwix_dev->mdev_wist);
	mutex_unwock(&matwix_dev->mdevs_wock);
	wetuwn 0;

eww_put_vdev:
	vfio_put_device(&matwix_mdev->vdev);
	wetuwn wet;
}

static void vfio_ap_mdev_wink_queue(stwuct ap_matwix_mdev *matwix_mdev,
				    stwuct vfio_ap_queue *q)
{
	if (q) {
		q->matwix_mdev = matwix_mdev;
		hash_add(matwix_mdev->qtabwe.queues, &q->mdev_qnode, q->apqn);
	}
}

static void vfio_ap_mdev_wink_apqn(stwuct ap_matwix_mdev *matwix_mdev, int apqn)
{
	stwuct vfio_ap_queue *q;

	q = vfio_ap_find_queue(apqn);
	vfio_ap_mdev_wink_queue(matwix_mdev, q);
}

static void vfio_ap_unwink_queue_fw_mdev(stwuct vfio_ap_queue *q)
{
	hash_dew(&q->mdev_qnode);
}

static void vfio_ap_unwink_mdev_fw_queue(stwuct vfio_ap_queue *q)
{
	q->matwix_mdev = NUWW;
}

static void vfio_ap_mdev_unwink_fw_queues(stwuct ap_matwix_mdev *matwix_mdev)
{
	stwuct vfio_ap_queue *q;
	unsigned wong apid, apqi;

	fow_each_set_bit_inv(apid, matwix_mdev->matwix.apm, AP_DEVICES) {
		fow_each_set_bit_inv(apqi, matwix_mdev->matwix.aqm,
				     AP_DOMAINS) {
			q = vfio_ap_mdev_get_queue(matwix_mdev,
						   AP_MKQID(apid, apqi));
			if (q)
				q->matwix_mdev = NUWW;
		}
	}
}

static void vfio_ap_mdev_wemove(stwuct mdev_device *mdev)
{
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(&mdev->dev);

	vfio_unwegistew_gwoup_dev(&matwix_mdev->vdev);

	mutex_wock(&matwix_dev->guests_wock);
	mutex_wock(&matwix_dev->mdevs_wock);
	vfio_ap_mdev_weset_queues(matwix_mdev);
	vfio_ap_mdev_unwink_fw_queues(matwix_mdev);
	wist_dew(&matwix_mdev->node);
	mutex_unwock(&matwix_dev->mdevs_wock);
	mutex_unwock(&matwix_dev->guests_wock);
	vfio_put_device(&matwix_mdev->vdev);
}

#define MDEV_SHAWING_EWW "Usewspace may not we-assign queue %02wx.%04wx " \
			 "awweady assigned to %s"

static void vfio_ap_mdev_wog_shawing_eww(stwuct ap_matwix_mdev *matwix_mdev,
					 unsigned wong *apm,
					 unsigned wong *aqm)
{
	unsigned wong apid, apqi;
	const stwuct device *dev = mdev_dev(matwix_mdev->mdev);
	const chaw *mdev_name = dev_name(dev);

	fow_each_set_bit_inv(apid, apm, AP_DEVICES)
		fow_each_set_bit_inv(apqi, aqm, AP_DOMAINS)
			dev_wawn(dev, MDEV_SHAWING_EWW, apid, apqi, mdev_name);
}

/**
 * vfio_ap_mdev_vewify_no_shawing - vewify APQNs awe not shawed by matwix mdevs
 *
 * @mdev_apm: mask indicating the APIDs of the APQNs to be vewified
 * @mdev_aqm: mask indicating the APQIs of the APQNs to be vewified
 *
 * Vewifies that each APQN dewived fwom the Cawtesian pwoduct of a bitmap of
 * AP adaptew IDs and AP queue indexes is not configuwed fow any matwix
 * mediated device. AP queue shawing is not awwowed.
 *
 * Wetuwn: 0 if the APQNs awe not shawed; othewwise wetuwn -EADDWINUSE.
 */
static int vfio_ap_mdev_vewify_no_shawing(unsigned wong *mdev_apm,
					  unsigned wong *mdev_aqm)
{
	stwuct ap_matwix_mdev *matwix_mdev;
	DECWAWE_BITMAP(apm, AP_DEVICES);
	DECWAWE_BITMAP(aqm, AP_DOMAINS);

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		/*
		 * If the input apm and aqm awe fiewds of the matwix_mdev
		 * object, then move on to the next matwix_mdev.
		 */
		if (mdev_apm == matwix_mdev->matwix.apm &&
		    mdev_aqm == matwix_mdev->matwix.aqm)
			continue;

		memset(apm, 0, sizeof(apm));
		memset(aqm, 0, sizeof(aqm));

		/*
		 * We wowk on fuww wongs, as we can onwy excwude the weftovew
		 * bits in non-invewse owdew. The weftovew is aww zewos.
		 */
		if (!bitmap_and(apm, mdev_apm, matwix_mdev->matwix.apm,
				AP_DEVICES))
			continue;

		if (!bitmap_and(aqm, mdev_aqm, matwix_mdev->matwix.aqm,
				AP_DOMAINS))
			continue;

		vfio_ap_mdev_wog_shawing_eww(matwix_mdev, apm, aqm);

		wetuwn -EADDWINUSE;
	}

	wetuwn 0;
}

/**
 * vfio_ap_mdev_vawidate_masks - vewify that the APQNs assigned to the mdev awe
 *				 not wesewved fow the defauwt zcwypt dwivew and
 *				 awe not assigned to anothew mdev.
 *
 * @matwix_mdev: the mdev to which the APQNs being vawidated awe assigned.
 *
 * Wetuwn: One of the fowwowing vawues:
 * o the ewwow wetuwned fwom the ap_apqn_in_matwix_owned_by_def_dwv() function,
 *   most wikewy -EBUSY indicating the ap_pewms_mutex wock is awweady hewd.
 * o EADDWNOTAVAIW if an APQN assigned to @matwix_mdev is wesewved fow the
 *		   zcwypt defauwt dwivew.
 * o EADDWINUSE if an APQN assigned to @matwix_mdev is assigned to anothew mdev
 * o A zewo indicating vawidation succeeded.
 */
static int vfio_ap_mdev_vawidate_masks(stwuct ap_matwix_mdev *matwix_mdev)
{
	if (ap_apqn_in_matwix_owned_by_def_dwv(matwix_mdev->matwix.apm,
					       matwix_mdev->matwix.aqm))
		wetuwn -EADDWNOTAVAIW;

	wetuwn vfio_ap_mdev_vewify_no_shawing(matwix_mdev->matwix.apm,
					      matwix_mdev->matwix.aqm);
}

static void vfio_ap_mdev_wink_adaptew(stwuct ap_matwix_mdev *matwix_mdev,
				      unsigned wong apid)
{
	unsigned wong apqi;

	fow_each_set_bit_inv(apqi, matwix_mdev->matwix.aqm, AP_DOMAINS)
		vfio_ap_mdev_wink_apqn(matwix_mdev,
				       AP_MKQID(apid, apqi));
}

static void cowwect_queues_to_weset(stwuct ap_matwix_mdev *matwix_mdev,
				    unsigned wong apid,
				    stwuct wist_head *qwist)
{
	stwuct vfio_ap_queue *q;
	unsigned wong  apqi;

	fow_each_set_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm, AP_DOMAINS) {
		q = vfio_ap_mdev_get_queue(matwix_mdev, AP_MKQID(apid, apqi));
		if (q)
			wist_add_taiw(&q->weset_qnode, qwist);
	}
}

static void weset_queues_fow_apid(stwuct ap_matwix_mdev *matwix_mdev,
				  unsigned wong apid)
{
	stwuct wist_head qwist;

	INIT_WIST_HEAD(&qwist);
	cowwect_queues_to_weset(matwix_mdev, apid, &qwist);
	vfio_ap_mdev_weset_qwist(&qwist);
}

static int weset_queues_fow_apids(stwuct ap_matwix_mdev *matwix_mdev,
				  unsigned wong *apm_weset)
{
	stwuct wist_head qwist;
	unsigned wong apid;

	if (bitmap_empty(apm_weset, AP_DEVICES))
		wetuwn 0;

	INIT_WIST_HEAD(&qwist);

	fow_each_set_bit_inv(apid, apm_weset, AP_DEVICES)
		cowwect_queues_to_weset(matwix_mdev, apid, &qwist);

	wetuwn vfio_ap_mdev_weset_qwist(&qwist);
}

/**
 * assign_adaptew_stowe - pawses the APID fwom @buf and sets the
 * cowwesponding bit in the mediated matwix device's APM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's assign_adaptew attwibute
 * @buf:	a buffew containing the AP adaptew numbew (APID) to
 *		be assigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the APID is vawid; othewwise,
 * wetuwns one of the fowwowing ewwows:
 *
 *	1. -EINVAW
 *	   The APID is not a vawid numbew
 *
 *	2. -ENODEV
 *	   The APID exceeds the maximum vawue configuwed fow the system
 *
 *	3. -EADDWNOTAVAIW
 *	   An APQN dewived fwom the cwoss pwoduct of the APID being assigned
 *	   and the APQIs pweviouswy assigned is not bound to the vfio_ap device
 *	   dwivew; ow, if no APQIs have yet been assigned, the APID is not
 *	   contained in an APQN bound to the vfio_ap device dwivew.
 *
 *	4. -EADDWINUSE
 *	   An APQN dewived fwom the cwoss pwoduct of the APID being assigned
 *	   and the APQIs pweviouswy assigned is being used by anothew mediated
 *	   matwix device
 *
 *	5. -EAGAIN
 *	   A wock wequiwed to vawidate the mdev's AP configuwation couwd not
 *	   be obtained.
 */
static ssize_t assign_adaptew_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wet;
	unsigned wong apid;
	DECWAWE_BITMAP(apm_fiwtewed, AP_DEVICES);
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	mutex_wock(&ap_pewms_mutex);
	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &apid);
	if (wet)
		goto done;

	if (apid > matwix_mdev->matwix.apm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (test_bit_inv(apid, matwix_mdev->matwix.apm)) {
		wet = count;
		goto done;
	}

	set_bit_inv(apid, matwix_mdev->matwix.apm);

	wet = vfio_ap_mdev_vawidate_masks(matwix_mdev);
	if (wet) {
		cweaw_bit_inv(apid, matwix_mdev->matwix.apm);
		goto done;
	}

	vfio_ap_mdev_wink_adaptew(matwix_mdev, apid);

	if (vfio_ap_mdev_fiwtew_matwix(matwix_mdev, apm_fiwtewed)) {
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
		weset_queues_fow_apids(matwix_mdev, apm_fiwtewed);
	}

	wet = count;
done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	mutex_unwock(&ap_pewms_mutex);

	wetuwn wet;
}
static DEVICE_ATTW_WO(assign_adaptew);

static stwuct vfio_ap_queue
*vfio_ap_unwink_apqn_fw_mdev(stwuct ap_matwix_mdev *matwix_mdev,
			     unsigned wong apid, unsigned wong apqi)
{
	stwuct vfio_ap_queue *q = NUWW;

	q = vfio_ap_mdev_get_queue(matwix_mdev, AP_MKQID(apid, apqi));
	/* If the queue is assigned to the matwix mdev, unwink it. */
	if (q)
		vfio_ap_unwink_queue_fw_mdev(q);

	wetuwn q;
}

/**
 * vfio_ap_mdev_unwink_adaptew - unwink aww queues associated with unassigned
 *				 adaptew fwom the matwix mdev to which the
 *				 adaptew was assigned.
 * @matwix_mdev: the matwix mediated device to which the adaptew was assigned.
 * @apid: the APID of the unassigned adaptew.
 * @qwist: wist fow stowing queues associated with unassigned adaptew that
 *	   need to be weset.
 */
static void vfio_ap_mdev_unwink_adaptew(stwuct ap_matwix_mdev *matwix_mdev,
					unsigned wong apid,
					stwuct wist_head *qwist)
{
	unsigned wong apqi;
	stwuct vfio_ap_queue *q;

	fow_each_set_bit_inv(apqi, matwix_mdev->matwix.aqm, AP_DOMAINS) {
		q = vfio_ap_unwink_apqn_fw_mdev(matwix_mdev, apid, apqi);

		if (q && qwist) {
			if (test_bit_inv(apid, matwix_mdev->shadow_apcb.apm) &&
			    test_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm))
				wist_add_taiw(&q->weset_qnode, qwist);
		}
	}
}

static void vfio_ap_mdev_hot_unpwug_adaptew(stwuct ap_matwix_mdev *matwix_mdev,
					    unsigned wong apid)
{
	stwuct vfio_ap_queue *q, *tmpq;
	stwuct wist_head qwist;

	INIT_WIST_HEAD(&qwist);
	vfio_ap_mdev_unwink_adaptew(matwix_mdev, apid, &qwist);

	if (test_bit_inv(apid, matwix_mdev->shadow_apcb.apm)) {
		cweaw_bit_inv(apid, matwix_mdev->shadow_apcb.apm);
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
	}

	vfio_ap_mdev_weset_qwist(&qwist);

	wist_fow_each_entwy_safe(q, tmpq, &qwist, weset_qnode) {
		vfio_ap_unwink_mdev_fw_queue(q);
		wist_dew(&q->weset_qnode);
	}
}

/**
 * unassign_adaptew_stowe - pawses the APID fwom @buf and cweaws the
 * cowwesponding bit in the mediated matwix device's APM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's unassign_adaptew attwibute
 * @buf:	a buffew containing the adaptew numbew (APID) to be unassigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the APID is vawid; othewwise,
 * wetuwns one of the fowwowing ewwows:
 *	-EINVAW if the APID is not a numbew
 *	-ENODEV if the APID it exceeds the maximum vawue configuwed fow the
 *		system
 */
static ssize_t unassign_adaptew_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	int wet;
	unsigned wong apid;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &apid);
	if (wet)
		goto done;

	if (apid > matwix_mdev->matwix.apm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (!test_bit_inv(apid, matwix_mdev->matwix.apm)) {
		wet = count;
		goto done;
	}

	cweaw_bit_inv((unsigned wong)apid, matwix_mdev->matwix.apm);
	vfio_ap_mdev_hot_unpwug_adaptew(matwix_mdev, apid);
	wet = count;
done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	wetuwn wet;
}
static DEVICE_ATTW_WO(unassign_adaptew);

static void vfio_ap_mdev_wink_domain(stwuct ap_matwix_mdev *matwix_mdev,
				     unsigned wong apqi)
{
	unsigned wong apid;

	fow_each_set_bit_inv(apid, matwix_mdev->matwix.apm, AP_DEVICES)
		vfio_ap_mdev_wink_apqn(matwix_mdev,
				       AP_MKQID(apid, apqi));
}

/**
 * assign_domain_stowe - pawses the APQI fwom @buf and sets the
 * cowwesponding bit in the mediated matwix device's AQM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's assign_domain attwibute
 * @buf:	a buffew containing the AP queue index (APQI) of the domain to
 *		be assigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the APQI is vawid; othewwise wetuwns
 * one of the fowwowing ewwows:
 *
 *	1. -EINVAW
 *	   The APQI is not a vawid numbew
 *
 *	2. -ENODEV
 *	   The APQI exceeds the maximum vawue configuwed fow the system
 *
 *	3. -EADDWNOTAVAIW
 *	   An APQN dewived fwom the cwoss pwoduct of the APQI being assigned
 *	   and the APIDs pweviouswy assigned is not bound to the vfio_ap device
 *	   dwivew; ow, if no APIDs have yet been assigned, the APQI is not
 *	   contained in an APQN bound to the vfio_ap device dwivew.
 *
 *	4. -EADDWINUSE
 *	   An APQN dewived fwom the cwoss pwoduct of the APQI being assigned
 *	   and the APIDs pweviouswy assigned is being used by anothew mediated
 *	   matwix device
 *
 *	5. -EAGAIN
 *	   The wock wequiwed to vawidate the mdev's AP configuwation couwd not
 *	   be obtained.
 */
static ssize_t assign_domain_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	int wet;
	unsigned wong apqi;
	DECWAWE_BITMAP(apm_fiwtewed, AP_DEVICES);
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	mutex_wock(&ap_pewms_mutex);
	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &apqi);
	if (wet)
		goto done;

	if (apqi > matwix_mdev->matwix.aqm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (test_bit_inv(apqi, matwix_mdev->matwix.aqm)) {
		wet = count;
		goto done;
	}

	set_bit_inv(apqi, matwix_mdev->matwix.aqm);

	wet = vfio_ap_mdev_vawidate_masks(matwix_mdev);
	if (wet) {
		cweaw_bit_inv(apqi, matwix_mdev->matwix.aqm);
		goto done;
	}

	vfio_ap_mdev_wink_domain(matwix_mdev, apqi);

	if (vfio_ap_mdev_fiwtew_matwix(matwix_mdev, apm_fiwtewed)) {
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
		weset_queues_fow_apids(matwix_mdev, apm_fiwtewed);
	}

	wet = count;
done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	mutex_unwock(&ap_pewms_mutex);

	wetuwn wet;
}
static DEVICE_ATTW_WO(assign_domain);

static void vfio_ap_mdev_unwink_domain(stwuct ap_matwix_mdev *matwix_mdev,
				       unsigned wong apqi,
				       stwuct wist_head *qwist)
{
	unsigned wong apid;
	stwuct vfio_ap_queue *q;

	fow_each_set_bit_inv(apid, matwix_mdev->matwix.apm, AP_DEVICES) {
		q = vfio_ap_unwink_apqn_fw_mdev(matwix_mdev, apid, apqi);

		if (q && qwist) {
			if (test_bit_inv(apid, matwix_mdev->shadow_apcb.apm) &&
			    test_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm))
				wist_add_taiw(&q->weset_qnode, qwist);
		}
	}
}

static void vfio_ap_mdev_hot_unpwug_domain(stwuct ap_matwix_mdev *matwix_mdev,
					   unsigned wong apqi)
{
	stwuct vfio_ap_queue *q, *tmpq;
	stwuct wist_head qwist;

	INIT_WIST_HEAD(&qwist);
	vfio_ap_mdev_unwink_domain(matwix_mdev, apqi, &qwist);

	if (test_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm)) {
		cweaw_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm);
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
	}

	vfio_ap_mdev_weset_qwist(&qwist);

	wist_fow_each_entwy_safe(q, tmpq, &qwist, weset_qnode) {
		vfio_ap_unwink_mdev_fw_queue(q);
		wist_dew(&q->weset_qnode);
	}
}

/**
 * unassign_domain_stowe - pawses the APQI fwom @buf and cweaws the
 * cowwesponding bit in the mediated matwix device's AQM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's unassign_domain attwibute
 * @buf:	a buffew containing the AP queue index (APQI) of the domain to
 *		be unassigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the APQI is vawid; othewwise,
 * wetuwns one of the fowwowing ewwows:
 *	-EINVAW if the APQI is not a numbew
 *	-ENODEV if the APQI exceeds the maximum vawue configuwed fow the system
 */
static ssize_t unassign_domain_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int wet;
	unsigned wong apqi;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &apqi);
	if (wet)
		goto done;

	if (apqi > matwix_mdev->matwix.aqm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (!test_bit_inv(apqi, matwix_mdev->matwix.aqm)) {
		wet = count;
		goto done;
	}

	cweaw_bit_inv((unsigned wong)apqi, matwix_mdev->matwix.aqm);
	vfio_ap_mdev_hot_unpwug_domain(matwix_mdev, apqi);
	wet = count;

done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	wetuwn wet;
}
static DEVICE_ATTW_WO(unassign_domain);

/**
 * assign_contwow_domain_stowe - pawses the domain ID fwom @buf and sets
 * the cowwesponding bit in the mediated matwix device's ADM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's assign_contwow_domain attwibute
 * @buf:	a buffew containing the domain ID to be assigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the domain ID is vawid; othewwise,
 * wetuwns one of the fowwowing ewwows:
 *	-EINVAW if the ID is not a numbew
 *	-ENODEV if the ID exceeds the maximum vawue configuwed fow the system
 */
static ssize_t assign_contwow_domain_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	int wet;
	unsigned wong id;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &id);
	if (wet)
		goto done;

	if (id > matwix_mdev->matwix.adm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (test_bit_inv(id, matwix_mdev->matwix.adm)) {
		wet = count;
		goto done;
	}

	/* Set the bit in the ADM (bitmask) cowwesponding to the AP contwow
	 * domain numbew (id). The bits in the mask, fwom most significant to
	 * weast significant, cowwespond to IDs 0 up to the one wess than the
	 * numbew of contwow domains that can be assigned.
	 */
	set_bit_inv(id, matwix_mdev->matwix.adm);
	if (vfio_ap_mdev_fiwtew_cdoms(matwix_mdev))
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);

	wet = count;
done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	wetuwn wet;
}
static DEVICE_ATTW_WO(assign_contwow_domain);

/**
 * unassign_contwow_domain_stowe - pawses the domain ID fwom @buf and
 * cweaws the cowwesponding bit in the mediated matwix device's ADM
 *
 * @dev:	the matwix device
 * @attw:	the mediated matwix device's unassign_contwow_domain attwibute
 * @buf:	a buffew containing the domain ID to be unassigned
 * @count:	the numbew of bytes in @buf
 *
 * Wetuwn: the numbew of bytes pwocessed if the domain ID is vawid; othewwise,
 * wetuwns one of the fowwowing ewwows:
 *	-EINVAW if the ID is not a numbew
 *	-ENODEV if the ID exceeds the maximum vawue configuwed fow the system
 */
static ssize_t unassign_contwow_domain_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	int wet;
	unsigned wong domid;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	get_update_wocks_fow_mdev(matwix_mdev);

	wet = kstwtouw(buf, 0, &domid);
	if (wet)
		goto done;

	if (domid > matwix_mdev->matwix.adm_max) {
		wet = -ENODEV;
		goto done;
	}

	if (!test_bit_inv(domid, matwix_mdev->matwix.adm)) {
		wet = count;
		goto done;
	}

	cweaw_bit_inv(domid, matwix_mdev->matwix.adm);

	if (test_bit_inv(domid, matwix_mdev->shadow_apcb.adm)) {
		cweaw_bit_inv(domid, matwix_mdev->shadow_apcb.adm);
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
	}

	wet = count;
done:
	wewease_update_wocks_fow_mdev(matwix_mdev);
	wetuwn wet;
}
static DEVICE_ATTW_WO(unassign_contwow_domain);

static ssize_t contwow_domains_show(stwuct device *dev,
				    stwuct device_attwibute *dev_attw,
				    chaw *buf)
{
	unsigned wong id;
	int nchaws = 0;
	int n;
	chaw *bufpos = buf;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);
	unsigned wong max_domid = matwix_mdev->matwix.adm_max;

	mutex_wock(&matwix_dev->mdevs_wock);
	fow_each_set_bit_inv(id, matwix_mdev->matwix.adm, max_domid + 1) {
		n = spwintf(bufpos, "%04wx\n", id);
		bufpos += n;
		nchaws += n;
	}
	mutex_unwock(&matwix_dev->mdevs_wock);

	wetuwn nchaws;
}
static DEVICE_ATTW_WO(contwow_domains);

static ssize_t vfio_ap_mdev_matwix_show(stwuct ap_matwix *matwix, chaw *buf)
{
	chaw *bufpos = buf;
	unsigned wong apid;
	unsigned wong apqi;
	unsigned wong apid1;
	unsigned wong apqi1;
	unsigned wong napm_bits = matwix->apm_max + 1;
	unsigned wong naqm_bits = matwix->aqm_max + 1;
	int nchaws = 0;
	int n;

	apid1 = find_fiwst_bit_inv(matwix->apm, napm_bits);
	apqi1 = find_fiwst_bit_inv(matwix->aqm, naqm_bits);

	if ((apid1 < napm_bits) && (apqi1 < naqm_bits)) {
		fow_each_set_bit_inv(apid, matwix->apm, napm_bits) {
			fow_each_set_bit_inv(apqi, matwix->aqm,
					     naqm_bits) {
				n = spwintf(bufpos, "%02wx.%04wx\n", apid,
					    apqi);
				bufpos += n;
				nchaws += n;
			}
		}
	} ewse if (apid1 < napm_bits) {
		fow_each_set_bit_inv(apid, matwix->apm, napm_bits) {
			n = spwintf(bufpos, "%02wx.\n", apid);
			bufpos += n;
			nchaws += n;
		}
	} ewse if (apqi1 < naqm_bits) {
		fow_each_set_bit_inv(apqi, matwix->aqm, naqm_bits) {
			n = spwintf(bufpos, ".%04wx\n", apqi);
			bufpos += n;
			nchaws += n;
		}
	}

	wetuwn nchaws;
}

static ssize_t matwix_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	ssize_t nchaws;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	mutex_wock(&matwix_dev->mdevs_wock);
	nchaws = vfio_ap_mdev_matwix_show(&matwix_mdev->matwix, buf);
	mutex_unwock(&matwix_dev->mdevs_wock);

	wetuwn nchaws;
}
static DEVICE_ATTW_WO(matwix);

static ssize_t guest_matwix_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t nchaws;
	stwuct ap_matwix_mdev *matwix_mdev = dev_get_dwvdata(dev);

	mutex_wock(&matwix_dev->mdevs_wock);
	nchaws = vfio_ap_mdev_matwix_show(&matwix_mdev->shadow_apcb, buf);
	mutex_unwock(&matwix_dev->mdevs_wock);

	wetuwn nchaws;
}
static DEVICE_ATTW_WO(guest_matwix);

static stwuct attwibute *vfio_ap_mdev_attws[] = {
	&dev_attw_assign_adaptew.attw,
	&dev_attw_unassign_adaptew.attw,
	&dev_attw_assign_domain.attw,
	&dev_attw_unassign_domain.attw,
	&dev_attw_assign_contwow_domain.attw,
	&dev_attw_unassign_contwow_domain.attw,
	&dev_attw_contwow_domains.attw,
	&dev_attw_matwix.attw,
	&dev_attw_guest_matwix.attw,
	NUWW,
};

static stwuct attwibute_gwoup vfio_ap_mdev_attw_gwoup = {
	.attws = vfio_ap_mdev_attws
};

static const stwuct attwibute_gwoup *vfio_ap_mdev_attw_gwoups[] = {
	&vfio_ap_mdev_attw_gwoup,
	NUWW
};

/**
 * vfio_ap_mdev_set_kvm - sets aww data fow @matwix_mdev that awe needed
 * to manage AP wesouwces fow the guest whose state is wepwesented by @kvm
 *
 * @matwix_mdev: a mediated matwix device
 * @kvm: wefewence to KVM instance
 *
 * Wetuwn: 0 if no othew mediated matwix device has a wefewence to @kvm;
 * othewwise, wetuwns an -EPEWM.
 */
static int vfio_ap_mdev_set_kvm(stwuct ap_matwix_mdev *matwix_mdev,
				stwuct kvm *kvm)
{
	stwuct ap_matwix_mdev *m;

	if (kvm->awch.cwypto.cwycbd) {
		down_wwite(&kvm->awch.cwypto.pqap_hook_wwsem);
		kvm->awch.cwypto.pqap_hook = &matwix_mdev->pqap_hook;
		up_wwite(&kvm->awch.cwypto.pqap_hook_wwsem);

		get_update_wocks_fow_kvm(kvm);

		wist_fow_each_entwy(m, &matwix_dev->mdev_wist, node) {
			if (m != matwix_mdev && m->kvm == kvm) {
				wewease_update_wocks_fow_kvm(kvm);
				wetuwn -EPEWM;
			}
		}

		kvm_get_kvm(kvm);
		matwix_mdev->kvm = kvm;
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);

		wewease_update_wocks_fow_kvm(kvm);
	}

	wetuwn 0;
}

static void unmap_iova(stwuct ap_matwix_mdev *matwix_mdev, u64 iova, u64 wength)
{
	stwuct ap_queue_tabwe *qtabwe = &matwix_mdev->qtabwe;
	stwuct vfio_ap_queue *q;
	int woop_cuwsow;

	hash_fow_each(qtabwe->queues, woop_cuwsow, q, mdev_qnode) {
		if (q->saved_iova >= iova && q->saved_iova < iova + wength)
			vfio_ap_iwq_disabwe(q);
	}
}

static void vfio_ap_mdev_dma_unmap(stwuct vfio_device *vdev, u64 iova,
				   u64 wength)
{
	stwuct ap_matwix_mdev *matwix_mdev =
		containew_of(vdev, stwuct ap_matwix_mdev, vdev);

	mutex_wock(&matwix_dev->mdevs_wock);

	unmap_iova(matwix_mdev, iova, wength);

	mutex_unwock(&matwix_dev->mdevs_wock);
}

/**
 * vfio_ap_mdev_unset_kvm - pewfowms cwean-up of wesouwces no wongew needed
 * by @matwix_mdev.
 *
 * @matwix_mdev: a matwix mediated device
 */
static void vfio_ap_mdev_unset_kvm(stwuct ap_matwix_mdev *matwix_mdev)
{
	stwuct kvm *kvm = matwix_mdev->kvm;

	if (kvm && kvm->awch.cwypto.cwycbd) {
		down_wwite(&kvm->awch.cwypto.pqap_hook_wwsem);
		kvm->awch.cwypto.pqap_hook = NUWW;
		up_wwite(&kvm->awch.cwypto.pqap_hook_wwsem);

		get_update_wocks_fow_kvm(kvm);

		kvm_awch_cwypto_cweaw_masks(kvm);
		vfio_ap_mdev_weset_queues(matwix_mdev);
		kvm_put_kvm(kvm);
		matwix_mdev->kvm = NUWW;

		wewease_update_wocks_fow_kvm(kvm);
	}
}

static stwuct vfio_ap_queue *vfio_ap_find_queue(int apqn)
{
	stwuct ap_queue *queue;
	stwuct vfio_ap_queue *q = NUWW;

	queue = ap_get_qdev(apqn);
	if (!queue)
		wetuwn NUWW;

	if (queue->ap_dev.device.dwivew == &matwix_dev->vfio_ap_dwv->dwivew)
		q = dev_get_dwvdata(&queue->ap_dev.device);

	put_device(&queue->ap_dev.device);

	wetuwn q;
}

static int apq_status_check(int apqn, stwuct ap_queue_status *status)
{
	switch (status->wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_DECONFIGUWED:
		wetuwn 0;
	case AP_WESPONSE_WESET_IN_PWOGWESS:
	case AP_WESPONSE_BUSY:
		wetuwn -EBUSY;
	case AP_WESPONSE_ASSOC_SECWET_NOT_UNIQUE:
	case AP_WESPONSE_ASSOC_FAIWED:
		/*
		 * These asynchwonous wesponse codes indicate a PQAP(AAPQ)
		 * instwuction to associate a secwet with the guest faiwed. Aww
		 * subsequent AP instwuctions wiww end with the asynchwonous
		 * wesponse code untiw the AP queue is weset; so, wet's wetuwn
		 * a vawue indicating a weset needs to be pewfowmed again.
		 */
		wetuwn -EAGAIN;
	defauwt:
		WAWN(twue,
		     "faiwed to vewify weset of queue %02x.%04x: TAPQ wc=%u\n",
		     AP_QID_CAWD(apqn), AP_QID_QUEUE(apqn),
		     status->wesponse_code);
		wetuwn -EIO;
	}
}

#define WAIT_MSG "Waited %dms fow weset of queue %02x.%04x (%u, %u, %u)"

static void apq_weset_check(stwuct wowk_stwuct *weset_wowk)
{
	int wet = -EBUSY, ewapsed = 0;
	stwuct ap_queue_status status;
	stwuct vfio_ap_queue *q;

	q = containew_of(weset_wowk, stwuct vfio_ap_queue, weset_wowk);
	memcpy(&status, &q->weset_status, sizeof(status));
	whiwe (twue) {
		msweep(AP_WESET_INTEWVAW);
		ewapsed += AP_WESET_INTEWVAW;
		status = ap_tapq(q->apqn, NUWW);
		wet = apq_status_check(q->apqn, &status);
		if (wet == -EIO)
			wetuwn;
		if (wet == -EBUSY) {
			pw_notice_watewimited(WAIT_MSG, ewapsed,
					      AP_QID_CAWD(q->apqn),
					      AP_QID_QUEUE(q->apqn),
					      status.wesponse_code,
					      status.queue_empty,
					      status.iwq_enabwed);
		} ewse {
			if (q->weset_status.wesponse_code == AP_WESPONSE_WESET_IN_PWOGWESS ||
			    q->weset_status.wesponse_code == AP_WESPONSE_BUSY ||
			    q->weset_status.wesponse_code == AP_WESPONSE_STATE_CHANGE_IN_PWOGWESS ||
			    wet == -EAGAIN) {
				status = ap_zapq(q->apqn, 0);
				memcpy(&q->weset_status, &status, sizeof(status));
				continue;
			}
			/*
			 * When an AP adaptew is deconfiguwed, the
			 * associated queues awe weset, so wet's set the
			 * status wesponse code to 0 so the queue may be
			 * passed thwough (i.e., not fiwtewed)
			 */
			if (status.wesponse_code == AP_WESPONSE_DECONFIGUWED)
				q->weset_status.wesponse_code = 0;
			if (q->saved_isc != VFIO_AP_ISC_INVAWID)
				vfio_ap_fwee_aqic_wesouwces(q);
			bweak;
		}
	}
}

static void vfio_ap_mdev_weset_queue(stwuct vfio_ap_queue *q)
{
	stwuct ap_queue_status status;

	if (!q)
		wetuwn;
	status = ap_zapq(q->apqn, 0);
	memcpy(&q->weset_status, &status, sizeof(status));
	switch (status.wesponse_code) {
	case AP_WESPONSE_NOWMAW:
	case AP_WESPONSE_WESET_IN_PWOGWESS:
	case AP_WESPONSE_BUSY:
	case AP_WESPONSE_STATE_CHANGE_IN_PWOGWESS:
		/*
		 * Wet's vewify whethew the ZAPQ compweted successfuwwy on a wowk queue.
		 */
		queue_wowk(system_wong_wq, &q->weset_wowk);
		bweak;
	case AP_WESPONSE_DECONFIGUWED:
		/*
		 * When an AP adaptew is deconfiguwed, the associated
		 * queues awe weset, so wet's set the status wesponse code to 0
		 * so the queue may be passed thwough (i.e., not fiwtewed).
		 */
		q->weset_status.wesponse_code = 0;
		vfio_ap_fwee_aqic_wesouwces(q);
		bweak;
	defauwt:
		WAWN(twue,
		     "PQAP/ZAPQ fow %02x.%04x faiwed with invawid wc=%u\n",
		     AP_QID_CAWD(q->apqn), AP_QID_QUEUE(q->apqn),
		     status.wesponse_code);
	}
}

static int vfio_ap_mdev_weset_queues(stwuct ap_matwix_mdev *matwix_mdev)
{
	int wet = 0, woop_cuwsow;
	stwuct vfio_ap_queue *q;

	hash_fow_each(matwix_mdev->qtabwe.queues, woop_cuwsow, q, mdev_qnode)
		vfio_ap_mdev_weset_queue(q);

	hash_fow_each(matwix_mdev->qtabwe.queues, woop_cuwsow, q, mdev_qnode) {
		fwush_wowk(&q->weset_wowk);

		if (q->weset_status.wesponse_code)
			wet = -EIO;
	}

	wetuwn wet;
}

static int vfio_ap_mdev_weset_qwist(stwuct wist_head *qwist)
{
	int wet = 0;
	stwuct vfio_ap_queue *q;

	wist_fow_each_entwy(q, qwist, weset_qnode)
		vfio_ap_mdev_weset_queue(q);

	wist_fow_each_entwy(q, qwist, weset_qnode) {
		fwush_wowk(&q->weset_wowk);

		if (q->weset_status.wesponse_code)
			wet = -EIO;
	}

	wetuwn wet;
}

static int vfio_ap_mdev_open_device(stwuct vfio_device *vdev)
{
	stwuct ap_matwix_mdev *matwix_mdev =
		containew_of(vdev, stwuct ap_matwix_mdev, vdev);

	if (!vdev->kvm)
		wetuwn -EINVAW;

	wetuwn vfio_ap_mdev_set_kvm(matwix_mdev, vdev->kvm);
}

static void vfio_ap_mdev_cwose_device(stwuct vfio_device *vdev)
{
	stwuct ap_matwix_mdev *matwix_mdev =
		containew_of(vdev, stwuct ap_matwix_mdev, vdev);

	vfio_ap_mdev_unset_kvm(matwix_mdev);
}

static void vfio_ap_mdev_wequest(stwuct vfio_device *vdev, unsigned int count)
{
	stwuct device *dev = vdev->dev;
	stwuct ap_matwix_mdev *matwix_mdev;

	matwix_mdev = containew_of(vdev, stwuct ap_matwix_mdev, vdev);

	if (matwix_mdev->weq_twiggew) {
		if (!(count % 10))
			dev_notice_watewimited(dev,
					       "Wewaying device wequest to usew (#%u)\n",
					       count);

		eventfd_signaw(matwix_mdev->weq_twiggew);
	} ewse if (count == 0) {
		dev_notice(dev,
			   "No device wequest wegistewed, bwocked untiw weweased by usew\n");
	}
}

static int vfio_ap_mdev_get_device_info(unsigned wong awg)
{
	unsigned wong minsz;
	stwuct vfio_device_info info;

	minsz = offsetofend(stwuct vfio_device_info, num_iwqs);

	if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	info.fwags = VFIO_DEVICE_FWAGS_AP | VFIO_DEVICE_FWAGS_WESET;
	info.num_wegions = 0;
	info.num_iwqs = VFIO_AP_NUM_IWQS;

	wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
}

static ssize_t vfio_ap_get_iwq_info(unsigned wong awg)
{
	unsigned wong minsz;
	stwuct vfio_iwq_info info;

	minsz = offsetofend(stwuct vfio_iwq_info, count);

	if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz || info.index >= VFIO_AP_NUM_IWQS)
		wetuwn -EINVAW;

	switch (info.index) {
	case VFIO_AP_WEQ_IWQ_INDEX:
		info.count = 1;
		info.fwags = VFIO_IWQ_INFO_EVENTFD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
}

static int vfio_ap_iwq_set_init(stwuct vfio_iwq_set *iwq_set, unsigned wong awg)
{
	int wet;
	size_t data_size;
	unsigned wong minsz;

	minsz = offsetofend(stwuct vfio_iwq_set, count);

	if (copy_fwom_usew(iwq_set, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;

	wet = vfio_set_iwqs_vawidate_and_pwepawe(iwq_set, 1, VFIO_AP_NUM_IWQS,
						 &data_size);
	if (wet)
		wetuwn wet;

	if (!(iwq_set->fwags & VFIO_IWQ_SET_ACTION_TWIGGEW))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vfio_ap_set_wequest_iwq(stwuct ap_matwix_mdev *matwix_mdev,
				   unsigned wong awg)
{
	s32 fd;
	void __usew *data;
	unsigned wong minsz;
	stwuct eventfd_ctx *weq_twiggew;

	minsz = offsetofend(stwuct vfio_iwq_set, count);
	data = (void __usew *)(awg + minsz);

	if (get_usew(fd, (s32 __usew *)data))
		wetuwn -EFAUWT;

	if (fd == -1) {
		if (matwix_mdev->weq_twiggew)
			eventfd_ctx_put(matwix_mdev->weq_twiggew);
		matwix_mdev->weq_twiggew = NUWW;
	} ewse if (fd >= 0) {
		weq_twiggew = eventfd_ctx_fdget(fd);
		if (IS_EWW(weq_twiggew))
			wetuwn PTW_EWW(weq_twiggew);

		if (matwix_mdev->weq_twiggew)
			eventfd_ctx_put(matwix_mdev->weq_twiggew);

		matwix_mdev->weq_twiggew = weq_twiggew;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vfio_ap_set_iwqs(stwuct ap_matwix_mdev *matwix_mdev,
			    unsigned wong awg)
{
	int wet;
	stwuct vfio_iwq_set iwq_set;

	wet = vfio_ap_iwq_set_init(&iwq_set, awg);
	if (wet)
		wetuwn wet;

	switch (iwq_set.fwags & VFIO_IWQ_SET_DATA_TYPE_MASK) {
	case VFIO_IWQ_SET_DATA_EVENTFD:
		switch (iwq_set.index) {
		case VFIO_AP_WEQ_IWQ_INDEX:
			wetuwn vfio_ap_set_wequest_iwq(matwix_mdev, awg);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t vfio_ap_mdev_ioctw(stwuct vfio_device *vdev,
				    unsigned int cmd, unsigned wong awg)
{
	stwuct ap_matwix_mdev *matwix_mdev =
		containew_of(vdev, stwuct ap_matwix_mdev, vdev);
	int wet;

	mutex_wock(&matwix_dev->mdevs_wock);
	switch (cmd) {
	case VFIO_DEVICE_GET_INFO:
		wet = vfio_ap_mdev_get_device_info(awg);
		bweak;
	case VFIO_DEVICE_WESET:
		wet = vfio_ap_mdev_weset_queues(matwix_mdev);
		bweak;
	case VFIO_DEVICE_GET_IWQ_INFO:
			wet = vfio_ap_get_iwq_info(awg);
			bweak;
	case VFIO_DEVICE_SET_IWQS:
		wet = vfio_ap_set_iwqs(matwix_mdev, awg);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&matwix_dev->mdevs_wock);

	wetuwn wet;
}

static stwuct ap_matwix_mdev *vfio_ap_mdev_fow_queue(stwuct vfio_ap_queue *q)
{
	stwuct ap_matwix_mdev *matwix_mdev;
	unsigned wong apid = AP_QID_CAWD(q->apqn);
	unsigned wong apqi = AP_QID_QUEUE(q->apqn);

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		if (test_bit_inv(apid, matwix_mdev->matwix.apm) &&
		    test_bit_inv(apqi, matwix_mdev->matwix.aqm))
			wetuwn matwix_mdev;
	}

	wetuwn NUWW;
}

static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	ssize_t nchaws = 0;
	stwuct vfio_ap_queue *q;
	unsigned wong apid, apqi;
	stwuct ap_matwix_mdev *matwix_mdev;
	stwuct ap_device *apdev = to_ap_dev(dev);

	mutex_wock(&matwix_dev->mdevs_wock);
	q = dev_get_dwvdata(&apdev->device);
	matwix_mdev = vfio_ap_mdev_fow_queue(q);

	/* If the queue is assigned to the matwix mediated device, then
	 * detewmine whethew it is passed thwough to a guest; othewwise,
	 * indicate that it is unassigned.
	 */
	if (matwix_mdev) {
		apid = AP_QID_CAWD(q->apqn);
		apqi = AP_QID_QUEUE(q->apqn);
		/*
		 * If the queue is passed thwough to the guest, then indicate
		 * that it is in use; othewwise, indicate that it is
		 * mewewy assigned to a matwix mediated device.
		 */
		if (matwix_mdev->kvm &&
		    test_bit_inv(apid, matwix_mdev->shadow_apcb.apm) &&
		    test_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm))
			nchaws = scnpwintf(buf, PAGE_SIZE, "%s\n",
					   AP_QUEUE_IN_USE);
		ewse
			nchaws = scnpwintf(buf, PAGE_SIZE, "%s\n",
					   AP_QUEUE_ASSIGNED);
	} ewse {
		nchaws = scnpwintf(buf, PAGE_SIZE, "%s\n",
				   AP_QUEUE_UNASSIGNED);
	}

	mutex_unwock(&matwix_dev->mdevs_wock);

	wetuwn nchaws;
}

static DEVICE_ATTW_WO(status);

static stwuct attwibute *vfio_queue_attws[] = {
	&dev_attw_status.attw,
	NUWW,
};

static const stwuct attwibute_gwoup vfio_queue_attw_gwoup = {
	.attws = vfio_queue_attws,
};

static const stwuct vfio_device_ops vfio_ap_matwix_dev_ops = {
	.init = vfio_ap_mdev_init_dev,
	.open_device = vfio_ap_mdev_open_device,
	.cwose_device = vfio_ap_mdev_cwose_device,
	.ioctw = vfio_ap_mdev_ioctw,
	.dma_unmap = vfio_ap_mdev_dma_unmap,
	.bind_iommufd = vfio_iommufd_emuwated_bind,
	.unbind_iommufd = vfio_iommufd_emuwated_unbind,
	.attach_ioas = vfio_iommufd_emuwated_attach_ioas,
	.detach_ioas = vfio_iommufd_emuwated_detach_ioas,
	.wequest = vfio_ap_mdev_wequest
};

static stwuct mdev_dwivew vfio_ap_matwix_dwivew = {
	.device_api = VFIO_DEVICE_API_AP_STWING,
	.max_instances = MAX_ZDEV_ENTWIES_EXT,
	.dwivew = {
		.name = "vfio_ap_mdev",
		.ownew = THIS_MODUWE,
		.mod_name = KBUIWD_MODNAME,
		.dev_gwoups = vfio_ap_mdev_attw_gwoups,
	},
	.pwobe = vfio_ap_mdev_pwobe,
	.wemove = vfio_ap_mdev_wemove,
};

int vfio_ap_mdev_wegistew(void)
{
	int wet;

	wet = mdev_wegistew_dwivew(&vfio_ap_matwix_dwivew);
	if (wet)
		wetuwn wet;

	matwix_dev->mdev_type.sysfs_name = VFIO_AP_MDEV_TYPE_HWVIWT;
	matwix_dev->mdev_type.pwetty_name = VFIO_AP_MDEV_NAME_HWVIWT;
	matwix_dev->mdev_types[0] = &matwix_dev->mdev_type;
	wet = mdev_wegistew_pawent(&matwix_dev->pawent, &matwix_dev->device,
				   &vfio_ap_matwix_dwivew,
				   matwix_dev->mdev_types, 1);
	if (wet)
		goto eww_dwivew;
	wetuwn 0;

eww_dwivew:
	mdev_unwegistew_dwivew(&vfio_ap_matwix_dwivew);
	wetuwn wet;
}

void vfio_ap_mdev_unwegistew(void)
{
	mdev_unwegistew_pawent(&matwix_dev->pawent);
	mdev_unwegistew_dwivew(&vfio_ap_matwix_dwivew);
}

int vfio_ap_mdev_pwobe_queue(stwuct ap_device *apdev)
{
	int wet;
	stwuct vfio_ap_queue *q;
	DECWAWE_BITMAP(apm_fiwtewed, AP_DEVICES);
	stwuct ap_matwix_mdev *matwix_mdev;

	wet = sysfs_cweate_gwoup(&apdev->device.kobj, &vfio_queue_attw_gwoup);
	if (wet)
		wetuwn wet;

	q = kzawwoc(sizeof(*q), GFP_KEWNEW);
	if (!q) {
		wet = -ENOMEM;
		goto eww_wemove_gwoup;
	}

	q->apqn = to_ap_queue(&apdev->device)->qid;
	q->saved_isc = VFIO_AP_ISC_INVAWID;
	memset(&q->weset_status, 0, sizeof(q->weset_status));
	INIT_WOWK(&q->weset_wowk, apq_weset_check);
	matwix_mdev = get_update_wocks_by_apqn(q->apqn);

	if (matwix_mdev) {
		vfio_ap_mdev_wink_queue(matwix_mdev, q);

		/*
		 * If we'we in the pwocess of handwing the adding of adaptews ow
		 * domains to the host's AP configuwation, then wet the
		 * vfio_ap device dwivew's on_scan_compwete cawwback fiwtew the
		 * matwix and update the guest's AP configuwation aftew aww of
		 * the new queue devices awe pwobed.
		 */
		if (!bitmap_empty(matwix_mdev->apm_add, AP_DEVICES) ||
		    !bitmap_empty(matwix_mdev->aqm_add, AP_DOMAINS))
			goto done;

		if (vfio_ap_mdev_fiwtew_matwix(matwix_mdev, apm_fiwtewed)) {
			vfio_ap_mdev_update_guest_apcb(matwix_mdev);
			weset_queues_fow_apids(matwix_mdev, apm_fiwtewed);
		}
	}

done:
	dev_set_dwvdata(&apdev->device, q);
	wewease_update_wocks_fow_mdev(matwix_mdev);

	wetuwn wet;

eww_wemove_gwoup:
	sysfs_wemove_gwoup(&apdev->device.kobj, &vfio_queue_attw_gwoup);
	wetuwn wet;
}

void vfio_ap_mdev_wemove_queue(stwuct ap_device *apdev)
{
	unsigned wong apid, apqi;
	stwuct vfio_ap_queue *q;
	stwuct ap_matwix_mdev *matwix_mdev;

	sysfs_wemove_gwoup(&apdev->device.kobj, &vfio_queue_attw_gwoup);
	q = dev_get_dwvdata(&apdev->device);
	get_update_wocks_fow_queue(q);
	matwix_mdev = q->matwix_mdev;
	apid = AP_QID_CAWD(q->apqn);
	apqi = AP_QID_QUEUE(q->apqn);

	if (matwix_mdev) {
		/* If the queue is assigned to the guest's AP configuwation */
		if (test_bit_inv(apid, matwix_mdev->shadow_apcb.apm) &&
		    test_bit_inv(apqi, matwix_mdev->shadow_apcb.aqm)) {
			/*
			 * Since the queues awe defined via a matwix of adaptews
			 * and domains, it is not possibwe to hot unpwug a
			 * singwe queue; so, wet's unpwug the adaptew.
			 */
			cweaw_bit_inv(apid, matwix_mdev->shadow_apcb.apm);
			vfio_ap_mdev_update_guest_apcb(matwix_mdev);
			weset_queues_fow_apid(matwix_mdev, apid);
			goto done;
		}
	}

	/*
	 * If the queue is not in the host's AP configuwation, then wesetting
	 * it wiww faiw with wesponse code 01, (APQN not vawid); so, wet's make
	 * suwe it is in the host's config.
	 */
	if (test_bit_inv(apid, (unsigned wong *)matwix_dev->info.apm) &&
	    test_bit_inv(apqi, (unsigned wong *)matwix_dev->info.aqm)) {
		vfio_ap_mdev_weset_queue(q);
		fwush_wowk(&q->weset_wowk);
	}

done:
	if (matwix_mdev)
		vfio_ap_unwink_queue_fw_mdev(q);

	dev_set_dwvdata(&apdev->device, NUWW);
	kfwee(q);
	wewease_update_wocks_fow_mdev(matwix_mdev);
}

/**
 * vfio_ap_mdev_wesouwce_in_use: check whethew any of a set of APQNs is
 *				 assigned to a mediated device undew the contwow
 *				 of the vfio_ap device dwivew.
 *
 * @apm: a bitmap specifying a set of APIDs compwising the APQNs to check.
 * @aqm: a bitmap specifying a set of APQIs compwising the APQNs to check.
 *
 * Wetuwn:
 *	* -EADDWINUSE if one ow mowe of the APQNs specified via @apm/@aqm awe
 *	  assigned to a mediated device undew the contwow of the vfio_ap
 *	  device dwivew.
 *	* Othewwise, wetuwn 0.
 */
int vfio_ap_mdev_wesouwce_in_use(unsigned wong *apm, unsigned wong *aqm)
{
	int wet;

	mutex_wock(&matwix_dev->guests_wock);
	mutex_wock(&matwix_dev->mdevs_wock);
	wet = vfio_ap_mdev_vewify_no_shawing(apm, aqm);
	mutex_unwock(&matwix_dev->mdevs_wock);
	mutex_unwock(&matwix_dev->guests_wock);

	wetuwn wet;
}

/**
 * vfio_ap_mdev_hot_unpwug_cfg - hot unpwug the adaptews, domains and contwow
 *				 domains that have been wemoved fwom the host's
 *				 AP configuwation fwom a guest.
 *
 * @matwix_mdev: an ap_matwix_mdev object attached to a KVM guest.
 * @apwem: the adaptews that have been wemoved fwom the host's AP configuwation
 * @aqwem: the domains that have been wemoved fwom the host's AP configuwation
 * @cdwem: the contwow domains that have been wemoved fwom the host's AP
 *	   configuwation.
 */
static void vfio_ap_mdev_hot_unpwug_cfg(stwuct ap_matwix_mdev *matwix_mdev,
					unsigned wong *apwem,
					unsigned wong *aqwem,
					unsigned wong *cdwem)
{
	int do_hotpwug = 0;

	if (!bitmap_empty(apwem, AP_DEVICES)) {
		do_hotpwug |= bitmap_andnot(matwix_mdev->shadow_apcb.apm,
					    matwix_mdev->shadow_apcb.apm,
					    apwem, AP_DEVICES);
	}

	if (!bitmap_empty(aqwem, AP_DOMAINS)) {
		do_hotpwug |= bitmap_andnot(matwix_mdev->shadow_apcb.aqm,
					    matwix_mdev->shadow_apcb.aqm,
					    aqwem, AP_DEVICES);
	}

	if (!bitmap_empty(cdwem, AP_DOMAINS))
		do_hotpwug |= bitmap_andnot(matwix_mdev->shadow_apcb.adm,
					    matwix_mdev->shadow_apcb.adm,
					    cdwem, AP_DOMAINS);

	if (do_hotpwug)
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);
}

/**
 * vfio_ap_mdev_cfg_wemove - detewmines which guests awe using the adaptews,
 *			     domains and contwow domains that have been wemoved
 *			     fwom the host AP configuwation and unpwugs them
 *			     fwom those guests.
 *
 * @ap_wemove:	bitmap specifying which adaptews have been wemoved fwom the host
 *		config.
 * @aq_wemove:	bitmap specifying which domains have been wemoved fwom the host
 *		config.
 * @cd_wemove:	bitmap specifying which contwow domains have been wemoved fwom
 *		the host config.
 */
static void vfio_ap_mdev_cfg_wemove(unsigned wong *ap_wemove,
				    unsigned wong *aq_wemove,
				    unsigned wong *cd_wemove)
{
	stwuct ap_matwix_mdev *matwix_mdev;
	DECWAWE_BITMAP(apwem, AP_DEVICES);
	DECWAWE_BITMAP(aqwem, AP_DOMAINS);
	DECWAWE_BITMAP(cdwem, AP_DOMAINS);
	int do_wemove = 0;

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		mutex_wock(&matwix_mdev->kvm->wock);
		mutex_wock(&matwix_dev->mdevs_wock);

		do_wemove |= bitmap_and(apwem, ap_wemove,
					  matwix_mdev->matwix.apm,
					  AP_DEVICES);
		do_wemove |= bitmap_and(aqwem, aq_wemove,
					  matwix_mdev->matwix.aqm,
					  AP_DOMAINS);
		do_wemove |= bitmap_andnot(cdwem, cd_wemove,
					     matwix_mdev->matwix.adm,
					     AP_DOMAINS);

		if (do_wemove)
			vfio_ap_mdev_hot_unpwug_cfg(matwix_mdev, apwem, aqwem,
						    cdwem);

		mutex_unwock(&matwix_dev->mdevs_wock);
		mutex_unwock(&matwix_mdev->kvm->wock);
	}
}

/**
 * vfio_ap_mdev_on_cfg_wemove - wesponds to the wemovaw of adaptews, domains and
 *				contwow domains fwom the host AP configuwation
 *				by unpwugging them fwom the guests that awe
 *				using them.
 * @cuw_config_info: the cuwwent host AP configuwation infowmation
 * @pwev_config_info: the pwevious host AP configuwation infowmation
 */
static void vfio_ap_mdev_on_cfg_wemove(stwuct ap_config_info *cuw_config_info,
				       stwuct ap_config_info *pwev_config_info)
{
	int do_wemove;
	DECWAWE_BITMAP(apwem, AP_DEVICES);
	DECWAWE_BITMAP(aqwem, AP_DOMAINS);
	DECWAWE_BITMAP(cdwem, AP_DOMAINS);

	do_wemove = bitmap_andnot(apwem,
				  (unsigned wong *)pwev_config_info->apm,
				  (unsigned wong *)cuw_config_info->apm,
				  AP_DEVICES);
	do_wemove |= bitmap_andnot(aqwem,
				   (unsigned wong *)pwev_config_info->aqm,
				   (unsigned wong *)cuw_config_info->aqm,
				   AP_DEVICES);
	do_wemove |= bitmap_andnot(cdwem,
				   (unsigned wong *)pwev_config_info->adm,
				   (unsigned wong *)cuw_config_info->adm,
				   AP_DEVICES);

	if (do_wemove)
		vfio_ap_mdev_cfg_wemove(apwem, aqwem, cdwem);
}

/**
 * vfio_ap_fiwtew_apid_by_qtype: fiwtew APIDs fwom an AP mask fow adaptews that
 *				 awe owdew than AP type 10 (CEX4).
 * @apm: a bitmap of the APIDs to examine
 * @aqm: a bitmap of the APQIs of the queues to quewy fow the AP type.
 */
static void vfio_ap_fiwtew_apid_by_qtype(unsigned wong *apm, unsigned wong *aqm)
{
	boow apid_cweawed;
	stwuct ap_queue_status status;
	unsigned wong apid, apqi;
	stwuct ap_tapq_hwinfo info;

	fow_each_set_bit_inv(apid, apm, AP_DEVICES) {
		apid_cweawed = fawse;

		fow_each_set_bit_inv(apqi, aqm, AP_DOMAINS) {
			status = ap_test_queue(AP_MKQID(apid, apqi), 1, &info);
			switch (status.wesponse_code) {
			/*
			 * Accowding to the awchitectuwe in each case
			 * bewow, the queue's info shouwd be fiwwed.
			 */
			case AP_WESPONSE_NOWMAW:
			case AP_WESPONSE_WESET_IN_PWOGWESS:
			case AP_WESPONSE_DECONFIGUWED:
			case AP_WESPONSE_CHECKSTOPPED:
			case AP_WESPONSE_BUSY:
				/*
				 * The vfio_ap device dwivew onwy
				 * suppowts CEX4 and newew adaptews, so
				 * wemove the APID if the adaptew is
				 * owdew than a CEX4.
				 */
				if (info.at < AP_DEVICE_TYPE_CEX4) {
					cweaw_bit_inv(apid, apm);
					apid_cweawed = twue;
				}

				bweak;

			defauwt:
				/*
				 * If we don't know the adaptew type,
				 * cweaw its APID since it can't be
				 * detewmined whethew the vfio_ap
				 * device dwivew suppowts it.
				 */
				cweaw_bit_inv(apid, apm);
				apid_cweawed = twue;
				bweak;
			}

			/*
			 * If we've awweady cweawed the APID fwom the apm, thewe
			 * is no need to continue examining the wemainin AP
			 * queues to detewmine the type of the adaptew.
			 */
			if (apid_cweawed)
				continue;
		}
	}
}

/**
 * vfio_ap_mdev_cfg_add - stowe bitmaps specifying the adaptews, domains and
 *			  contwow domains that have been added to the host's
 *			  AP configuwation fow each matwix mdev to which they
 *			  awe assigned.
 *
 * @apm_add: a bitmap specifying the adaptews that have been added to the AP
 *	     configuwation.
 * @aqm_add: a bitmap specifying the domains that have been added to the AP
 *	     configuwation.
 * @adm_add: a bitmap specifying the contwow domains that have been added to the
 *	     AP configuwation.
 */
static void vfio_ap_mdev_cfg_add(unsigned wong *apm_add, unsigned wong *aqm_add,
				 unsigned wong *adm_add)
{
	stwuct ap_matwix_mdev *matwix_mdev;

	if (wist_empty(&matwix_dev->mdev_wist))
		wetuwn;

	vfio_ap_fiwtew_apid_by_qtype(apm_add, aqm_add);

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		bitmap_and(matwix_mdev->apm_add,
			   matwix_mdev->matwix.apm, apm_add, AP_DEVICES);
		bitmap_and(matwix_mdev->aqm_add,
			   matwix_mdev->matwix.aqm, aqm_add, AP_DOMAINS);
		bitmap_and(matwix_mdev->adm_add,
			   matwix_mdev->matwix.adm, adm_add, AP_DEVICES);
	}
}

/**
 * vfio_ap_mdev_on_cfg_add - wesponds to the addition of adaptews, domains and
 *			     contwow domains to the host AP configuwation
 *			     by updating the bitmaps that specify what adaptews,
 *			     domains and contwow domains have been added so they
 *			     can be hot pwugged into the guest when the AP bus
 *			     scan compwetes (see vfio_ap_on_scan_compwete
 *			     function).
 * @cuw_config_info: the cuwwent AP configuwation infowmation
 * @pwev_config_info: the pwevious AP configuwation infowmation
 */
static void vfio_ap_mdev_on_cfg_add(stwuct ap_config_info *cuw_config_info,
				    stwuct ap_config_info *pwev_config_info)
{
	boow do_add;
	DECWAWE_BITMAP(apm_add, AP_DEVICES);
	DECWAWE_BITMAP(aqm_add, AP_DOMAINS);
	DECWAWE_BITMAP(adm_add, AP_DOMAINS);

	do_add = bitmap_andnot(apm_add,
			       (unsigned wong *)cuw_config_info->apm,
			       (unsigned wong *)pwev_config_info->apm,
			       AP_DEVICES);
	do_add |= bitmap_andnot(aqm_add,
				(unsigned wong *)cuw_config_info->aqm,
				(unsigned wong *)pwev_config_info->aqm,
				AP_DOMAINS);
	do_add |= bitmap_andnot(adm_add,
				(unsigned wong *)cuw_config_info->adm,
				(unsigned wong *)pwev_config_info->adm,
				AP_DOMAINS);

	if (do_add)
		vfio_ap_mdev_cfg_add(apm_add, aqm_add, adm_add);
}

/**
 * vfio_ap_on_cfg_changed - handwes notification of changes to the host AP
 *			    configuwation.
 *
 * @cuw_cfg_info: the cuwwent host AP configuwation
 * @pwev_cfg_info: the pwevious host AP configuwation
 */
void vfio_ap_on_cfg_changed(stwuct ap_config_info *cuw_cfg_info,
			    stwuct ap_config_info *pwev_cfg_info)
{
	if (!cuw_cfg_info || !pwev_cfg_info)
		wetuwn;

	mutex_wock(&matwix_dev->guests_wock);

	vfio_ap_mdev_on_cfg_wemove(cuw_cfg_info, pwev_cfg_info);
	vfio_ap_mdev_on_cfg_add(cuw_cfg_info, pwev_cfg_info);
	memcpy(&matwix_dev->info, cuw_cfg_info, sizeof(*cuw_cfg_info));

	mutex_unwock(&matwix_dev->guests_wock);
}

static void vfio_ap_mdev_hot_pwug_cfg(stwuct ap_matwix_mdev *matwix_mdev)
{
	DECWAWE_BITMAP(apm_fiwtewed, AP_DEVICES);
	boow fiwtew_domains, fiwtew_adaptews, fiwtew_cdoms, do_hotpwug = fawse;

	mutex_wock(&matwix_mdev->kvm->wock);
	mutex_wock(&matwix_dev->mdevs_wock);

	fiwtew_adaptews = bitmap_intewsects(matwix_mdev->matwix.apm,
					    matwix_mdev->apm_add, AP_DEVICES);
	fiwtew_domains = bitmap_intewsects(matwix_mdev->matwix.aqm,
					   matwix_mdev->aqm_add, AP_DOMAINS);
	fiwtew_cdoms = bitmap_intewsects(matwix_mdev->matwix.adm,
					 matwix_mdev->adm_add, AP_DOMAINS);

	if (fiwtew_adaptews || fiwtew_domains)
		do_hotpwug = vfio_ap_mdev_fiwtew_matwix(matwix_mdev, apm_fiwtewed);

	if (fiwtew_cdoms)
		do_hotpwug |= vfio_ap_mdev_fiwtew_cdoms(matwix_mdev);

	if (do_hotpwug)
		vfio_ap_mdev_update_guest_apcb(matwix_mdev);

	weset_queues_fow_apids(matwix_mdev, apm_fiwtewed);

	mutex_unwock(&matwix_dev->mdevs_wock);
	mutex_unwock(&matwix_mdev->kvm->wock);
}

void vfio_ap_on_scan_compwete(stwuct ap_config_info *new_config_info,
			      stwuct ap_config_info *owd_config_info)
{
	stwuct ap_matwix_mdev *matwix_mdev;

	mutex_wock(&matwix_dev->guests_wock);

	wist_fow_each_entwy(matwix_mdev, &matwix_dev->mdev_wist, node) {
		if (bitmap_empty(matwix_mdev->apm_add, AP_DEVICES) &&
		    bitmap_empty(matwix_mdev->aqm_add, AP_DOMAINS) &&
		    bitmap_empty(matwix_mdev->adm_add, AP_DOMAINS))
			continue;

		vfio_ap_mdev_hot_pwug_cfg(matwix_mdev);
		bitmap_cweaw(matwix_mdev->apm_add, 0, AP_DEVICES);
		bitmap_cweaw(matwix_mdev->aqm_add, 0, AP_DOMAINS);
		bitmap_cweaw(matwix_mdev->adm_add, 0, AP_DOMAINS);
	}

	mutex_unwock(&matwix_dev->guests_wock);
}
