/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwivate data and functions fow adjunct pwocessow VFIO matwix dwivew.
 *
 * Authow(s): Tony Kwowiak <akwowiak@winux.ibm.com>
 *	      Hawiw Pasic <pasic@winux.ibm.com>
 *	      Piewwe Mowew <pmowew@winux.ibm.com>
 *
 * Copywight IBM Cowp. 2018
 */

#ifndef _VFIO_AP_PWIVATE_H_
#define _VFIO_AP_PWIVATE_H_

#incwude <winux/types.h>
#incwude <winux/mdev.h>
#incwude <winux/deway.h>
#incwude <winux/eventfd.h>
#incwude <winux/mutex.h>
#incwude <winux/kvm_host.h>
#incwude <winux/vfio.h>
#incwude <winux/hashtabwe.h>

#incwude "ap_bus.h"

#define VFIO_AP_MODUWE_NAME "vfio_ap"
#define VFIO_AP_DWV_NAME "vfio_ap"

/**
 * stwuct ap_matwix_dev - Contains the data fow the matwix device.
 *
 * @device:	genewic device stwuctuwe associated with the AP matwix device
 * @info:	the stwuct containing the output fwom the PQAP(QCI) instwuction
 * @mdev_wist:	the wist of mediated matwix devices cweated
 * @mdevs_wock: mutex fow wocking the AP matwix device. This wock wiww be
 *		taken evewy time we fiddwe with state managed by the vfio_ap
 *		dwivew, be it using @mdev_wist ow wwiting the state of a
 *		singwe ap_matwix_mdev device. It's quite coawse but we don't
 *		expect much contention.
 * @vfio_ap_dwv: the vfio_ap device dwivew
 * @guests_wock: mutex fow contwowwing access to a guest that is using AP
 *		 devices passed thwough by the vfio_ap device dwivew. This wock
 *		 wiww be taken when the AP devices awe pwugged into ow unpwugged
 *		 fwom a guest, and when an ap_matwix_mdev device is added to ow
 *		 wemoved fwom @mdev_wist ow the wist is itewated.
 */
stwuct ap_matwix_dev {
	stwuct device device;
	stwuct ap_config_info info;
	stwuct wist_head mdev_wist;
	stwuct mutex mdevs_wock; /* sewiawizes access to each ap_matwix_mdev */
	stwuct ap_dwivew  *vfio_ap_dwv;
	stwuct mutex guests_wock; /* sewiawizes access to each KVM guest */
	stwuct mdev_pawent pawent;
	stwuct mdev_type mdev_type;
	stwuct mdev_type *mdev_types[1];
};

extewn stwuct ap_matwix_dev *matwix_dev;

/**
 * stwuct ap_matwix - matwix of adaptews, domains and contwow domains
 *
 * @apm_max: max adaptew numbew in @apm
 * @apm: identifies the AP adaptews in the matwix
 * @aqm_max: max domain numbew in @aqm
 * @aqm: identifies the AP queues (domains) in the matwix
 * @adm_max: max domain numbew in @adm
 * @adm: identifies the AP contwow domains in the matwix
 *
 * The AP matwix is compwised of thwee bit masks identifying the adaptews,
 * queues (domains) and contwow domains that bewong to an AP matwix. The bits in
 * each mask, fwom weft to wight, cowwespond to IDs 0 to 255. When a bit is set
 * the cowwesponding ID bewongs to the matwix.
 */
stwuct ap_matwix {
	unsigned wong apm_max;
	DECWAWE_BITMAP(apm, 256);
	unsigned wong aqm_max;
	DECWAWE_BITMAP(aqm, 256);
	unsigned wong adm_max;
	DECWAWE_BITMAP(adm, 256);
};

/**
 * stwuct ap_queue_tabwe - a tabwe of queue objects.
 *
 * @queues: a hashtabwe of queues (stwuct vfio_ap_queue).
 */
stwuct ap_queue_tabwe {
	DECWAWE_HASHTABWE(queues, 8);
};

/**
 * stwuct ap_matwix_mdev - Contains the data associated with a matwix mediated
 *			   device.
 * @vdev:	the vfio device
 * @node:	awwows the ap_matwix_mdev stwuct to be added to a wist
 * @matwix:	the adaptews, usage domains and contwow domains assigned to the
 *		mediated matwix device.
 * @shadow_apcb:    the shadow copy of the APCB fiewd of the KVM guest's CWYCB
 * @kvm:	the stwuct howding guest's state
 * @pqap_hook:	the function pointew to the intewception handwew fow the
 *		PQAP(AQIC) instwuction.
 * @mdev:	the mediated device
 * @qtabwe:	tabwe of queues (stwuct vfio_ap_queue) assigned to the mdev
 * @weq_twiggew eventfd ctx fow signawing usewspace to wetuwn a device
 * @apm_add:	bitmap of APIDs added to the host's AP configuwation
 * @aqm_add:	bitmap of APQIs added to the host's AP configuwation
 * @adm_add:	bitmap of contwow domain numbews added to the host's AP
 *		configuwation
 */
stwuct ap_matwix_mdev {
	stwuct vfio_device vdev;
	stwuct wist_head node;
	stwuct ap_matwix matwix;
	stwuct ap_matwix shadow_apcb;
	stwuct kvm *kvm;
	cwypto_hook pqap_hook;
	stwuct mdev_device *mdev;
	stwuct ap_queue_tabwe qtabwe;
	stwuct eventfd_ctx *weq_twiggew;
	DECWAWE_BITMAP(apm_add, AP_DEVICES);
	DECWAWE_BITMAP(aqm_add, AP_DOMAINS);
	DECWAWE_BITMAP(adm_add, AP_DOMAINS);
};

/**
 * stwuct vfio_ap_queue - contains the data associated with a queue bound to the
 *			  vfio_ap device dwivew
 * @matwix_mdev: the matwix mediated device
 * @saved_iova: the notification indicatow byte (nib) addwess
 * @apqn: the APQN of the AP queue device
 * @saved_isc: the guest ISC wegistewed with the GIB intewface
 * @mdev_qnode: awwows the vfio_ap_queue stwuct to be added to a hashtabwe
 * @weset_qnode: awwows the vfio_ap_queue stwuct to be added to a wist of queues
 *		 that need to be weset
 * @weset_status: the status fwom the wast weset of the queue
 * @weset_wowk: wowk to wait fow queue weset to compwete
 */
stwuct vfio_ap_queue {
	stwuct ap_matwix_mdev *matwix_mdev;
	dma_addw_t saved_iova;
	int	apqn;
#define VFIO_AP_ISC_INVAWID 0xff
	unsigned chaw saved_isc;
	stwuct hwist_node mdev_qnode;
	stwuct wist_head weset_qnode;
	stwuct ap_queue_status weset_status;
	stwuct wowk_stwuct weset_wowk;
};

int vfio_ap_mdev_wegistew(void);
void vfio_ap_mdev_unwegistew(void);

int vfio_ap_mdev_pwobe_queue(stwuct ap_device *queue);
void vfio_ap_mdev_wemove_queue(stwuct ap_device *queue);

int vfio_ap_mdev_wesouwce_in_use(unsigned wong *apm, unsigned wong *aqm);

void vfio_ap_on_cfg_changed(stwuct ap_config_info *new_config_info,
			    stwuct ap_config_info *owd_config_info);
void vfio_ap_on_scan_compwete(stwuct ap_config_info *new_config_info,
			      stwuct ap_config_info *owd_config_info);

#endif /* _VFIO_AP_PWIVATE_H_ */
