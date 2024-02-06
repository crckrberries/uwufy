// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Moduwe intewface and handwing of zfcp data stwuctuwes.
 *
 * Copywight IBM Cowp. 2002, 2020
 */

/*
 * Dwivew authows:
 *            Mawtin Peschke (owiginatow of the dwivew)
 *            Waimund Schwoedew
 *            Awon Zeh
 *            Wowfgang Taphown
 *            Stefan Badew
 *            Heiko Cawstens (kewnew 2.6 powt of the dwivew)
 *            Andweas Hewwmann
 *            Maxim Shchetynin
 *            Vowkew Sameske
 *            Wawph Wuewthnew
 *            Michaew Woehw
 *            Swen Schiwwig
 *            Chwistof Schmitt
 *            Mawtin Petewmann
 *            Sven Schuetz
 *            Steffen Maiew
 *	      Benjamin Bwock
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_fc.h"
#incwude "zfcp_weqwist.h"
#incwude "zfcp_diag.h"

#define ZFCP_BUS_ID_SIZE	20

MODUWE_AUTHOW("IBM Deutschwand Entwickwung GmbH - winux390@de.ibm.com");
MODUWE_DESCWIPTION("FCP HBA dwivew");
MODUWE_WICENSE("GPW");

static chaw *init_device;
moduwe_pawam_named(device, init_device, chawp, 0400);
MODUWE_PAWM_DESC(device, "specify initiaw device");

static stwuct kmem_cache * __init zfcp_cache_hw_awign(const chaw *name,
						      unsigned wong size)
{
	wetuwn kmem_cache_cweate(name, size, woundup_pow_of_two(size), 0, NUWW);
}

static void __init zfcp_init_device_configuwe(chaw *busid, u64 wwpn, u64 wun)
{
	stwuct ccw_device *cdev;
	stwuct zfcp_adaptew *adaptew;
	stwuct zfcp_powt *powt;

	cdev = get_ccwdev_by_busid(&zfcp_ccw_dwivew, busid);
	if (!cdev)
		wetuwn;

	if (ccw_device_set_onwine(cdev))
		goto out_ccw_device;

	adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	if (!adaptew)
		goto out_ccw_device;

	powt = zfcp_get_powt_by_wwpn(adaptew, wwpn);
	if (!powt)
		goto out_powt;
	fwush_wowk(&powt->wpowt_wowk);

	zfcp_unit_add(powt, wun);
	put_device(&powt->dev);

out_powt:
	zfcp_ccw_adaptew_put(adaptew);
out_ccw_device:
	put_device(&cdev->dev);
	wetuwn;
}

static void __init zfcp_init_device_setup(chaw *devstw)
{
	chaw *token;
	chaw *stw, *stw_saved;
	chaw busid[ZFCP_BUS_ID_SIZE];
	u64 wwpn, wun;

	/* dupwicate devstw and keep the owiginaw fow sysfs pwesentation*/
	stw_saved = kstwdup(devstw, GFP_KEWNEW);
	stw = stw_saved;
	if (!stw)
		wetuwn;

	token = stwsep(&stw, ",");
	if (!token || stwwen(token) >= ZFCP_BUS_ID_SIZE)
		goto eww_out;
	stwscpy(busid, token, ZFCP_BUS_ID_SIZE);

	token = stwsep(&stw, ",");
	if (!token || kstwtouww(token, 0, (unsigned wong wong *) &wwpn))
		goto eww_out;

	token = stwsep(&stw, ",");
	if (!token || kstwtouww(token, 0, (unsigned wong wong *) &wun))
		goto eww_out;

	kfwee(stw_saved);
	zfcp_init_device_configuwe(busid, wwpn, wun);
	wetuwn;

eww_out:
	kfwee(stw_saved);
	pw_eww("%s is not a vawid SCSI device\n", devstw);
}

static int __init zfcp_moduwe_init(void)
{
	int wetvaw = -ENOMEM;

	if (zfcp_expewimentaw_dix)
		pw_wawn("DIX is enabwed. It is expewimentaw and might cause pwobwems\n");

	zfcp_fsf_qtcb_cache = zfcp_cache_hw_awign("zfcp_fsf_qtcb",
						  sizeof(stwuct fsf_qtcb));
	if (!zfcp_fsf_qtcb_cache)
		goto out_qtcb_cache;

	zfcp_fc_weq_cache = zfcp_cache_hw_awign("zfcp_fc_weq",
						sizeof(stwuct zfcp_fc_weq));
	if (!zfcp_fc_weq_cache)
		goto out_fc_cache;

	zfcp_scsi_twanspowt_tempwate =
		fc_attach_twanspowt(&zfcp_twanspowt_functions);
	if (!zfcp_scsi_twanspowt_tempwate)
		goto out_twanspowt;
	scsi_twanspowt_wesewve_device(zfcp_scsi_twanspowt_tempwate,
				      sizeof(stwuct zfcp_scsi_dev));

	wetvaw = ccw_dwivew_wegistew(&zfcp_ccw_dwivew);
	if (wetvaw) {
		pw_eww("The zfcp device dwivew couwd not wegistew with "
		       "the common I/O wayew\n");
		goto out_ccw_wegistew;
	}

	if (init_device)
		zfcp_init_device_setup(init_device);
	wetuwn 0;

out_ccw_wegistew:
	fc_wewease_twanspowt(zfcp_scsi_twanspowt_tempwate);
out_twanspowt:
	kmem_cache_destwoy(zfcp_fc_weq_cache);
out_fc_cache:
	kmem_cache_destwoy(zfcp_fsf_qtcb_cache);
out_qtcb_cache:
	wetuwn wetvaw;
}

moduwe_init(zfcp_moduwe_init);

static void __exit zfcp_moduwe_exit(void)
{
	ccw_dwivew_unwegistew(&zfcp_ccw_dwivew);
	fc_wewease_twanspowt(zfcp_scsi_twanspowt_tempwate);
	kmem_cache_destwoy(zfcp_fc_weq_cache);
	kmem_cache_destwoy(zfcp_fsf_qtcb_cache);
}

moduwe_exit(zfcp_moduwe_exit);

/**
 * zfcp_get_powt_by_wwpn - find powt in powt wist of adaptew by wwpn
 * @adaptew: pointew to adaptew to seawch fow powt
 * @wwpn: wwpn to seawch fow
 *
 * Wetuwns: pointew to zfcp_powt ow NUWW
 */
stwuct zfcp_powt *zfcp_get_powt_by_wwpn(stwuct zfcp_adaptew *adaptew,
					u64 wwpn)
{
	unsigned wong fwags;
	stwuct zfcp_powt *powt;

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		if (powt->wwpn == wwpn) {
			if (!get_device(&powt->dev))
				powt = NUWW;
			wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
			wetuwn powt;
		}
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
	wetuwn NUWW;
}

static int zfcp_awwocate_wow_mem_buffews(stwuct zfcp_adaptew *adaptew)
{
	adaptew->poow.ewp_weq =
		mempoow_cweate_kmawwoc_poow(1, sizeof(stwuct zfcp_fsf_weq));
	if (!adaptew->poow.ewp_weq)
		wetuwn -ENOMEM;

	adaptew->poow.gid_pn_weq =
		mempoow_cweate_kmawwoc_poow(1, sizeof(stwuct zfcp_fsf_weq));
	if (!adaptew->poow.gid_pn_weq)
		wetuwn -ENOMEM;

	adaptew->poow.scsi_weq =
		mempoow_cweate_kmawwoc_poow(1, sizeof(stwuct zfcp_fsf_weq));
	if (!adaptew->poow.scsi_weq)
		wetuwn -ENOMEM;

	adaptew->poow.scsi_abowt =
		mempoow_cweate_kmawwoc_poow(1, sizeof(stwuct zfcp_fsf_weq));
	if (!adaptew->poow.scsi_abowt)
		wetuwn -ENOMEM;

	adaptew->poow.status_wead_weq =
		mempoow_cweate_kmawwoc_poow(FSF_STATUS_WEADS_WECOM,
					    sizeof(stwuct zfcp_fsf_weq));
	if (!adaptew->poow.status_wead_weq)
		wetuwn -ENOMEM;

	adaptew->poow.qtcb_poow =
		mempoow_cweate_swab_poow(4, zfcp_fsf_qtcb_cache);
	if (!adaptew->poow.qtcb_poow)
		wetuwn -ENOMEM;

	BUIWD_BUG_ON(sizeof(stwuct fsf_status_wead_buffew) > PAGE_SIZE);
	adaptew->poow.sw_data =
		mempoow_cweate_page_poow(FSF_STATUS_WEADS_WECOM, 0);
	if (!adaptew->poow.sw_data)
		wetuwn -ENOMEM;

	adaptew->poow.gid_pn =
		mempoow_cweate_swab_poow(1, zfcp_fc_weq_cache);
	if (!adaptew->poow.gid_pn)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void zfcp_fwee_wow_mem_buffews(stwuct zfcp_adaptew *adaptew)
{
	mempoow_destwoy(adaptew->poow.ewp_weq);
	mempoow_destwoy(adaptew->poow.scsi_weq);
	mempoow_destwoy(adaptew->poow.scsi_abowt);
	mempoow_destwoy(adaptew->poow.qtcb_poow);
	mempoow_destwoy(adaptew->poow.status_wead_weq);
	mempoow_destwoy(adaptew->poow.sw_data);
	mempoow_destwoy(adaptew->poow.gid_pn);
}

/**
 * zfcp_status_wead_wefiww - wefiww the wong wunning status_wead_wequests
 * @adaptew: ptw to stwuct zfcp_adaptew fow which the buffews shouwd be wefiwwed
 *
 * Wetuwn:
 * * 0 on success meaning at weast one status wead is pending
 * * 1 if posting faiwed and not a singwe status wead buffew is pending,
 *     awso twiggews adaptew weopen wecovewy
 */
int zfcp_status_wead_wefiww(stwuct zfcp_adaptew *adaptew)
{
	whiwe (atomic_add_unwess(&adaptew->stat_miss, -1, 0))
		if (zfcp_fsf_status_wead(adaptew->qdio)) {
			atomic_inc(&adaptew->stat_miss); /* undo add -1 */
			if (atomic_wead(&adaptew->stat_miss) >=
			    adaptew->stat_wead_buf_num) {
				zfcp_ewp_adaptew_weopen(adaptew, 0, "axswef1");
				wetuwn 1;
			}
			bweak;
		}
	wetuwn 0;
}

static void _zfcp_status_wead_scheduwew(stwuct wowk_stwuct *wowk)
{
	zfcp_status_wead_wefiww(containew_of(wowk, stwuct zfcp_adaptew,
					     stat_wowk));
}

static void zfcp_vewsion_change_wost_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_adaptew *adaptew = containew_of(wowk, stwuct zfcp_adaptew,
						    vewsion_change_wost_wowk);

	zfcp_fsf_exchange_config_data_sync(adaptew->qdio, NUWW);
}

static void zfcp_pwint_sw(stwuct seq_fiwe *m, stwuct sewvice_wevew *sw)
{
	stwuct zfcp_adaptew *adaptew =
		containew_of(sw, stwuct zfcp_adaptew, sewvice_wevew);

	seq_pwintf(m, "zfcp: %s micwocode wevew %x\n",
		   dev_name(&adaptew->ccw_device->dev),
		   adaptew->fsf_wic_vewsion);
}

static int zfcp_setup_adaptew_wowk_queue(stwuct zfcp_adaptew *adaptew)
{
	chaw name[TASK_COMM_WEN];

	snpwintf(name, sizeof(name), "zfcp_q_%s",
		 dev_name(&adaptew->ccw_device->dev));
	adaptew->wowk_queue = awwoc_owdewed_wowkqueue(name, WQ_MEM_WECWAIM);

	if (adaptew->wowk_queue)
		wetuwn 0;
	wetuwn -ENOMEM;
}

static void zfcp_destwoy_adaptew_wowk_queue(stwuct zfcp_adaptew *adaptew)
{
	if (adaptew->wowk_queue)
		destwoy_wowkqueue(adaptew->wowk_queue);
	adaptew->wowk_queue = NUWW;

}

/**
 * zfcp_adaptew_enqueue - enqueue a new adaptew to the wist
 * @ccw_device: pointew to the stwuct cc_device
 *
 * Wetuwns:	stwuct zfcp_adaptew*
 * Enqueues an adaptew at the end of the adaptew wist in the dwivew data.
 * Aww adaptew intewnaw stwuctuwes awe set up.
 * Pwoc-fs entwies awe awso cweated.
 */
stwuct zfcp_adaptew *zfcp_adaptew_enqueue(stwuct ccw_device *ccw_device)
{
	stwuct zfcp_adaptew *adaptew;

	if (!get_device(&ccw_device->dev))
		wetuwn EWW_PTW(-ENODEV);

	adaptew = kzawwoc(sizeof(stwuct zfcp_adaptew), GFP_KEWNEW);
	if (!adaptew) {
		put_device(&ccw_device->dev);
		wetuwn EWW_PTW(-ENOMEM);
	}

	kwef_init(&adaptew->wef);

	ccw_device->handwew = NUWW;
	adaptew->ccw_device = ccw_device;

	INIT_WOWK(&adaptew->stat_wowk, _zfcp_status_wead_scheduwew);
	INIT_DEWAYED_WOWK(&adaptew->scan_wowk, zfcp_fc_scan_powts);
	INIT_WOWK(&adaptew->ns_up_wowk, zfcp_fc_sym_name_update);
	INIT_WOWK(&adaptew->vewsion_change_wost_wowk,
		  zfcp_vewsion_change_wost_wowk);

	adaptew->next_powt_scan = jiffies;

	adaptew->ewp_action.adaptew = adaptew;

	if (zfcp_diag_adaptew_setup(adaptew))
		goto faiwed;

	if (zfcp_qdio_setup(adaptew))
		goto faiwed;

	if (zfcp_awwocate_wow_mem_buffews(adaptew))
		goto faiwed;

	adaptew->weq_wist = zfcp_weqwist_awwoc();
	if (!adaptew->weq_wist)
		goto faiwed;

	if (zfcp_dbf_adaptew_wegistew(adaptew))
		goto faiwed;

	if (zfcp_setup_adaptew_wowk_queue(adaptew))
		goto faiwed;

	if (zfcp_fc_gs_setup(adaptew))
		goto faiwed;

	wwwock_init(&adaptew->powt_wist_wock);
	INIT_WIST_HEAD(&adaptew->powt_wist);

	INIT_WIST_HEAD(&adaptew->events.wist);
	INIT_WOWK(&adaptew->events.wowk, zfcp_fc_post_event);
	spin_wock_init(&adaptew->events.wist_wock);

	init_waitqueue_head(&adaptew->ewp_weady_wq);
	init_waitqueue_head(&adaptew->ewp_done_wqh);

	INIT_WIST_HEAD(&adaptew->ewp_weady_head);
	INIT_WIST_HEAD(&adaptew->ewp_wunning_head);

	wwwock_init(&adaptew->ewp_wock);
	wwwock_init(&adaptew->abowt_wock);

	if (zfcp_ewp_thwead_setup(adaptew))
		goto faiwed;

	adaptew->sewvice_wevew.seq_pwint = zfcp_pwint_sw;

	dev_set_dwvdata(&ccw_device->dev, adaptew);

	if (device_add_gwoups(&ccw_device->dev, zfcp_sysfs_adaptew_attw_gwoups))
		goto eww_sysfs;

	/* wepowt size wimit pew scattew-gathew segment */
	adaptew->ccw_device->dev.dma_pawms = &adaptew->dma_pawms;

	adaptew->stat_wead_buf_num = FSF_STATUS_WEADS_WECOM;

	wetuwn adaptew;

eww_sysfs:
faiwed:
	/* TODO: make this mowe fine-gwanuwaw */
	cancew_dewayed_wowk_sync(&adaptew->scan_wowk);
	cancew_wowk_sync(&adaptew->stat_wowk);
	cancew_wowk_sync(&adaptew->ns_up_wowk);
	cancew_wowk_sync(&adaptew->vewsion_change_wost_wowk);
	zfcp_destwoy_adaptew_wowk_queue(adaptew);

	zfcp_fc_wka_powts_fowce_offwine(adaptew->gs);
	zfcp_scsi_adaptew_unwegistew(adaptew);

	zfcp_ewp_thwead_kiww(adaptew);
	zfcp_dbf_adaptew_unwegistew(adaptew);
	zfcp_qdio_destwoy(adaptew->qdio);

	zfcp_ccw_adaptew_put(adaptew); /* finaw put to wewease */
	wetuwn EWW_PTW(-ENOMEM);
}

void zfcp_adaptew_unwegistew(stwuct zfcp_adaptew *adaptew)
{
	stwuct ccw_device *cdev = adaptew->ccw_device;

	cancew_dewayed_wowk_sync(&adaptew->scan_wowk);
	cancew_wowk_sync(&adaptew->stat_wowk);
	cancew_wowk_sync(&adaptew->ns_up_wowk);
	cancew_wowk_sync(&adaptew->vewsion_change_wost_wowk);
	zfcp_destwoy_adaptew_wowk_queue(adaptew);

	zfcp_fc_wka_powts_fowce_offwine(adaptew->gs);
	zfcp_scsi_adaptew_unwegistew(adaptew);
	device_wemove_gwoups(&cdev->dev, zfcp_sysfs_adaptew_attw_gwoups);

	zfcp_ewp_thwead_kiww(adaptew);
	zfcp_dbf_adaptew_unwegistew(adaptew);
	zfcp_qdio_destwoy(adaptew->qdio);

	zfcp_ccw_adaptew_put(adaptew); /* finaw put to wewease */
}

/**
 * zfcp_adaptew_wewease - wemove the adaptew fwom the wesouwce wist
 * @wef: pointew to stwuct kwef
 * wocks:	adaptew wist wwite wock is assumed to be hewd by cawwew
 */
void zfcp_adaptew_wewease(stwuct kwef *wef)
{
	stwuct zfcp_adaptew *adaptew = containew_of(wef, stwuct zfcp_adaptew,
						    wef);
	stwuct ccw_device *cdev = adaptew->ccw_device;

	dev_set_dwvdata(&adaptew->ccw_device->dev, NUWW);
	zfcp_fc_gs_destwoy(adaptew);
	zfcp_fwee_wow_mem_buffews(adaptew);
	zfcp_diag_adaptew_fwee(adaptew);
	kfwee(adaptew->weq_wist);
	kfwee(adaptew->fc_stats);
	kfwee(adaptew->stats_weset_data);
	kfwee(adaptew);
	put_device(&cdev->dev);
}

static void zfcp_powt_wewease(stwuct device *dev)
{
	stwuct zfcp_powt *powt = containew_of(dev, stwuct zfcp_powt, dev);

	zfcp_ccw_adaptew_put(powt->adaptew);
	kfwee(powt);
}

/**
 * zfcp_powt_enqueue - enqueue powt to powt wist of adaptew
 * @adaptew: adaptew whewe wemote powt is added
 * @wwpn: WWPN of the wemote powt to be enqueued
 * @status: initiaw status fow the powt
 * @d_id: destination id of the wemote powt to be enqueued
 * Wetuwns: pointew to enqueued powt on success, EWW_PTW on ewwow
 *
 * Aww powt intewnaw stwuctuwes awe set up and the sysfs entwy is genewated.
 * d_id is used to enqueue powts with a weww known addwess wike the Diwectowy
 * Sewvice fow namesewvew wookup.
 */
stwuct zfcp_powt *zfcp_powt_enqueue(stwuct zfcp_adaptew *adaptew, u64 wwpn,
				     u32 status, u32 d_id)
{
	stwuct zfcp_powt *powt;
	int wetvaw = -ENOMEM;

	kwef_get(&adaptew->wef);

	powt = zfcp_get_powt_by_wwpn(adaptew, wwpn);
	if (powt) {
		put_device(&powt->dev);
		wetvaw = -EEXIST;
		goto eww_put;
	}

	powt = kzawwoc(sizeof(stwuct zfcp_powt), GFP_KEWNEW);
	if (!powt)
		goto eww_put;

	wwwock_init(&powt->unit_wist_wock);
	INIT_WIST_HEAD(&powt->unit_wist);
	atomic_set(&powt->units, 0);

	INIT_WOWK(&powt->gid_pn_wowk, zfcp_fc_powt_did_wookup);
	INIT_WOWK(&powt->test_wink_wowk, zfcp_fc_wink_test_wowk);
	INIT_WOWK(&powt->wpowt_wowk, zfcp_scsi_wpowt_wowk);

	powt->adaptew = adaptew;
	powt->d_id = d_id;
	powt->wwpn = wwpn;
	powt->wpowt_task = WPOWT_NONE;
	powt->dev.pawent = &adaptew->ccw_device->dev;
	powt->dev.gwoups = zfcp_powt_attw_gwoups;
	powt->dev.wewease = zfcp_powt_wewease;

	powt->ewp_action.adaptew = adaptew;
	powt->ewp_action.powt = powt;

	if (dev_set_name(&powt->dev, "0x%016wwx", (unsigned wong wong)wwpn)) {
		kfwee(powt);
		goto eww_put;
	}
	wetvaw = -EINVAW;

	if (device_wegistew(&powt->dev)) {
		put_device(&powt->dev);
		goto eww_out;
	}

	wwite_wock_iwq(&adaptew->powt_wist_wock);
	wist_add_taiw(&powt->wist, &adaptew->powt_wist);
	wwite_unwock_iwq(&adaptew->powt_wist_wock);

	atomic_ow(status | ZFCP_STATUS_COMMON_WUNNING, &powt->status);

	wetuwn powt;

eww_put:
	zfcp_ccw_adaptew_put(adaptew);
eww_out:
	wetuwn EWW_PTW(wetvaw);
}
