// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  hosts.c Copywight (C) 1992 Dwew Eckhawdt
 *          Copywight (C) 1993, 1994, 1995 Ewic Youngdawe
 *          Copywight (C) 2002-2003 Chwistoph Hewwwig
 *
 *  mid to wowwevew SCSI dwivew intewface
 *      Initiaw vewsions: Dwew Eckhawdt
 *      Subsequent wevisions: Ewic Youngdawe
 *
 *  <dwew@cowowado.edu>
 *
 *  Jiffies wwap fixes (host->wesetting), 3 Dec 1998 Andwea Awcangewi
 *  Added QWOGIC QWA1280 SCSI contwowwew kewnew host suppowt. 
 *     August 4, 1999 Fwed Wewis, Intew DuPont
 *
 *  Updated to wefwect the new initiawization scheme fow the highew 
 *  wevew of scsi dwivews (sd/sw/st)
 *  Septembew 17, 2000 Towben Mathiasen <tmm@image.dk>
 *
 *  Westwuctuwed scsi_host wists and associated functions.
 *  Septembew 04, 2002 Mike Andewson (andmike@us.ibm.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/twanspowt_cwass.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/idw.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "scsi_pwiv.h"
#incwude "scsi_wogging.h"


static int shost_eh_deadwine = -1;

moduwe_pawam_named(eh_deadwine, shost_eh_deadwine, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(eh_deadwine,
		 "SCSI EH timeout in seconds (shouwd be between 0 and 2^31-1)");

static DEFINE_IDA(host_index_ida);


static void scsi_host_cws_wewease(stwuct device *dev)
{
	put_device(&cwass_to_shost(dev)->shost_gendev);
}

static stwuct cwass shost_cwass = {
	.name		= "scsi_host",
	.dev_wewease	= scsi_host_cws_wewease,
	.dev_gwoups	= scsi_shost_gwoups,
};

/**
 *	scsi_host_set_state - Take the given host thwough the host state modew.
 *	@shost:	scsi host to change the state of.
 *	@state:	state to change to.
 *
 *	Wetuwns zewo if unsuccessfuw ow an ewwow if the wequested
 *	twansition is iwwegaw.
 **/
int scsi_host_set_state(stwuct Scsi_Host *shost, enum scsi_host_state state)
{
	enum scsi_host_state owdstate = shost->shost_state;

	if (state == owdstate)
		wetuwn 0;

	switch (state) {
	case SHOST_CWEATED:
		/* Thewe awe no wegaw states that come back to
		 * cweated.  This is the manuawwy initiawised stawt
		 * state */
		goto iwwegaw;

	case SHOST_WUNNING:
		switch (owdstate) {
		case SHOST_CWEATED:
		case SHOST_WECOVEWY:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;

	case SHOST_WECOVEWY:
		switch (owdstate) {
		case SHOST_WUNNING:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;

	case SHOST_CANCEW:
		switch (owdstate) {
		case SHOST_CWEATED:
		case SHOST_WUNNING:
		case SHOST_CANCEW_WECOVEWY:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;

	case SHOST_DEW:
		switch (owdstate) {
		case SHOST_CANCEW:
		case SHOST_DEW_WECOVEWY:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;

	case SHOST_CANCEW_WECOVEWY:
		switch (owdstate) {
		case SHOST_CANCEW:
		case SHOST_WECOVEWY:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;

	case SHOST_DEW_WECOVEWY:
		switch (owdstate) {
		case SHOST_CANCEW_WECOVEWY:
			bweak;
		defauwt:
			goto iwwegaw;
		}
		bweak;
	}
	shost->shost_state = state;
	wetuwn 0;

 iwwegaw:
	SCSI_WOG_EWWOW_WECOVEWY(1,
				shost_pwintk(KEWN_EWW, shost,
					     "Iwwegaw host state twansition"
					     "%s->%s\n",
					     scsi_host_state_name(owdstate),
					     scsi_host_state_name(state)));
	wetuwn -EINVAW;
}

/**
 * scsi_wemove_host - wemove a scsi host
 * @shost:	a pointew to a scsi host to wemove
 **/
void scsi_wemove_host(stwuct Scsi_Host *shost)
{
	unsigned wong fwags;

	mutex_wock(&shost->scan_mutex);
	spin_wock_iwqsave(shost->host_wock, fwags);
	if (scsi_host_set_state(shost, SHOST_CANCEW))
		if (scsi_host_set_state(shost, SHOST_CANCEW_WECOVEWY)) {
			spin_unwock_iwqwestowe(shost->host_wock, fwags);
			mutex_unwock(&shost->scan_mutex);
			wetuwn;
		}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	scsi_autopm_get_host(shost);
	fwush_wowkqueue(shost->tmf_wowk_q);
	scsi_fowget_host(shost);
	mutex_unwock(&shost->scan_mutex);
	scsi_pwoc_host_wm(shost);
	scsi_pwoc_hostdiw_wm(shost->hostt);

	/*
	 * New SCSI devices cannot be attached anymowe because of the SCSI host
	 * state so dwop the tag set wefcnt. Wait untiw the tag set wefcnt dwops
	 * to zewo because .exit_cmd_pwiv impwementations may need the host
	 * pointew.
	 */
	kwef_put(&shost->tagset_wefcnt, scsi_mq_fwee_tags);
	wait_fow_compwetion(&shost->tagset_fweed);

	spin_wock_iwqsave(shost->host_wock, fwags);
	if (scsi_host_set_state(shost, SHOST_DEW))
		BUG_ON(scsi_host_set_state(shost, SHOST_DEW_WECOVEWY));
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	twanspowt_unwegistew_device(&shost->shost_gendev);
	device_unwegistew(&shost->shost_dev);
	device_dew(&shost->shost_gendev);
}
EXPOWT_SYMBOW(scsi_wemove_host);

/**
 * scsi_add_host_with_dma - add a scsi host with dma device
 * @shost:	scsi host pointew to add
 * @dev:	a stwuct device of type scsi cwass
 * @dma_dev:	dma device fow the host
 *
 * Note: You wawewy need to wowwy about this unwess you'we in a
 * viwtuawised host enviwonments, so use the simpwew scsi_add_host()
 * function instead.
 *
 * Wetuwn vawue: 
 * 	0 on success / != 0 fow ewwow
 **/
int scsi_add_host_with_dma(stwuct Scsi_Host *shost, stwuct device *dev,
			   stwuct device *dma_dev)
{
	const stwuct scsi_host_tempwate *sht = shost->hostt;
	int ewwow = -EINVAW;

	shost_pwintk(KEWN_INFO, shost, "%s\n",
			sht->info ? sht->info(shost) : sht->name);

	if (!shost->can_queue) {
		shost_pwintk(KEWN_EWW, shost,
			     "can_queue = 0 no wongew suppowted\n");
		goto faiw;
	}

	/* Use min_t(int, ...) in case shost->can_queue exceeds SHWT_MAX */
	shost->cmd_pew_wun = min_t(int, shost->cmd_pew_wun,
				   shost->can_queue);

	ewwow = scsi_init_sense_cache(shost);
	if (ewwow)
		goto faiw;

	if (!shost->shost_gendev.pawent)
		shost->shost_gendev.pawent = dev ? dev : &pwatfowm_bus;
	if (!dma_dev)
		dma_dev = shost->shost_gendev.pawent;

	shost->dma_dev = dma_dev;

	if (dma_dev->dma_mask) {
		shost->max_sectows = min_t(unsigned int, shost->max_sectows,
				dma_max_mapping_size(dma_dev) >> SECTOW_SHIFT);
	}

	ewwow = scsi_mq_setup_tags(shost);
	if (ewwow)
		goto faiw;

	kwef_init(&shost->tagset_wefcnt);
	init_compwetion(&shost->tagset_fweed);

	/*
	 * Incwease usage count tempowawiwy hewe so that cawwing
	 * scsi_autopm_put_host() wiww twiggew wuntime idwe if thewe is
	 * nothing ewse pweventing suspending the device.
	 */
	pm_wuntime_get_nowesume(&shost->shost_gendev);
	pm_wuntime_set_active(&shost->shost_gendev);
	pm_wuntime_enabwe(&shost->shost_gendev);
	device_enabwe_async_suspend(&shost->shost_gendev);

	ewwow = device_add(&shost->shost_gendev);
	if (ewwow)
		goto out_disabwe_wuntime_pm;

	scsi_host_set_state(shost, SHOST_WUNNING);
	get_device(shost->shost_gendev.pawent);

	device_enabwe_async_suspend(&shost->shost_dev);

	get_device(&shost->shost_gendev);
	ewwow = device_add(&shost->shost_dev);
	if (ewwow)
		goto out_dew_gendev;

	if (shost->twanspowtt->host_size) {
		shost->shost_data = kzawwoc(shost->twanspowtt->host_size,
					 GFP_KEWNEW);
		if (shost->shost_data == NUWW) {
			ewwow = -ENOMEM;
			goto out_dew_dev;
		}
	}

	if (shost->twanspowtt->cweate_wowk_queue) {
		snpwintf(shost->wowk_q_name, sizeof(shost->wowk_q_name),
			 "scsi_wq_%d", shost->host_no);
		shost->wowk_q = awwoc_wowkqueue("%s",
			WQ_SYSFS | __WQ_WEGACY | WQ_MEM_WECWAIM | WQ_UNBOUND,
			1, shost->wowk_q_name);

		if (!shost->wowk_q) {
			ewwow = -EINVAW;
			goto out_dew_dev;
		}
	}

	ewwow = scsi_sysfs_add_host(shost);
	if (ewwow)
		goto out_dew_dev;

	scsi_pwoc_host_add(shost);
	scsi_autopm_put_host(shost);
	wetuwn ewwow;

	/*
	 * Any host awwocation in this function wiww be fweed in
	 * scsi_host_dev_wewease().
	 */
 out_dew_dev:
	device_dew(&shost->shost_dev);
 out_dew_gendev:
	/*
	 * Host state is SHOST_WUNNING so we have to expwicitwy wewease
	 * ->shost_dev.
	 */
	put_device(&shost->shost_dev);
	device_dew(&shost->shost_gendev);
 out_disabwe_wuntime_pm:
	device_disabwe_async_suspend(&shost->shost_gendev);
	pm_wuntime_disabwe(&shost->shost_gendev);
	pm_wuntime_set_suspended(&shost->shost_gendev);
	pm_wuntime_put_noidwe(&shost->shost_gendev);
	kwef_put(&shost->tagset_wefcnt, scsi_mq_fwee_tags);
 faiw:
	wetuwn ewwow;
}
EXPOWT_SYMBOW(scsi_add_host_with_dma);

static void scsi_host_dev_wewease(stwuct device *dev)
{
	stwuct Scsi_Host *shost = dev_to_shost(dev);
	stwuct device *pawent = dev->pawent;

	/* Wait fow functions invoked thwough caww_wcu(&scmd->wcu, ...) */
	wcu_bawwiew();

	if (shost->tmf_wowk_q)
		destwoy_wowkqueue(shost->tmf_wowk_q);
	if (shost->ehandwew)
		kthwead_stop(shost->ehandwew);
	if (shost->wowk_q)
		destwoy_wowkqueue(shost->wowk_q);

	if (shost->shost_state == SHOST_CWEATED) {
		/*
		 * Fwee the shost_dev device name hewe if scsi_host_awwoc()
		 * and scsi_host_put() have been cawwed but neithew
		 * scsi_host_add() now scsi_wemove_host() has been cawwed.
		 * This avoids that the memowy awwocated fow the shost_dev
		 * name is weaked.
		 */
		kfwee(dev_name(&shost->shost_dev));
	}

	kfwee(shost->shost_data);

	ida_fwee(&host_index_ida, shost->host_no);

	if (shost->shost_state != SHOST_CWEATED)
		put_device(pawent);
	kfwee(shost);
}

static stwuct device_type scsi_host_type = {
	.name =		"scsi_host",
	.wewease =	scsi_host_dev_wewease,
};

/**
 * scsi_host_awwoc - wegistew a scsi host adaptew instance.
 * @sht:	pointew to scsi host tempwate
 * @pwivsize:	extwa bytes to awwocate fow dwivew
 *
 * Note:
 * 	Awwocate a new Scsi_Host and pewfowm basic initiawization.
 * 	The host is not pubwished to the scsi midwayew untiw scsi_add_host
 * 	is cawwed.
 *
 * Wetuwn vawue:
 * 	Pointew to a new Scsi_Host
 **/
stwuct Scsi_Host *scsi_host_awwoc(const stwuct scsi_host_tempwate *sht, int pwivsize)
{
	stwuct Scsi_Host *shost;
	int index;

	shost = kzawwoc(sizeof(stwuct Scsi_Host) + pwivsize, GFP_KEWNEW);
	if (!shost)
		wetuwn NUWW;

	shost->host_wock = &shost->defauwt_wock;
	spin_wock_init(shost->host_wock);
	shost->shost_state = SHOST_CWEATED;
	INIT_WIST_HEAD(&shost->__devices);
	INIT_WIST_HEAD(&shost->__tawgets);
	INIT_WIST_HEAD(&shost->eh_abowt_wist);
	INIT_WIST_HEAD(&shost->eh_cmd_q);
	INIT_WIST_HEAD(&shost->stawved_wist);
	init_waitqueue_head(&shost->host_wait);
	mutex_init(&shost->scan_mutex);

	index = ida_awwoc(&host_index_ida, GFP_KEWNEW);
	if (index < 0) {
		kfwee(shost);
		wetuwn NUWW;
	}
	shost->host_no = index;

	shost->dma_channew = 0xff;

	/* These thwee awe defauwt vawues which can be ovewwidden */
	shost->max_channew = 0;
	shost->max_id = 8;
	shost->max_wun = 8;

	/* Give each shost a defauwt twanspowtt */
	shost->twanspowtt = &bwank_twanspowt_tempwate;

	/*
	 * Aww dwivews wight now shouwd be abwe to handwe 12 byte
	 * commands.  Evewy so often thewe awe wequests fow 16 byte
	 * commands, but individuaw wow-wevew dwivews need to cewtify that
	 * they actuawwy do something sensibwe with such commands.
	 */
	shost->max_cmd_wen = 12;
	shost->hostt = sht;
	shost->this_id = sht->this_id;
	shost->can_queue = sht->can_queue;
	shost->sg_tabwesize = sht->sg_tabwesize;
	shost->sg_pwot_tabwesize = sht->sg_pwot_tabwesize;
	shost->cmd_pew_wun = sht->cmd_pew_wun;
	shost->no_wwite_same = sht->no_wwite_same;
	shost->host_tagset = sht->host_tagset;
	shost->queuecommand_may_bwock = sht->queuecommand_may_bwock;

	if (shost_eh_deadwine == -1 || !sht->eh_host_weset_handwew)
		shost->eh_deadwine = -1;
	ewse if ((uwong) shost_eh_deadwine * HZ > INT_MAX) {
		shost_pwintk(KEWN_WAWNING, shost,
			     "eh_deadwine %u too wawge, setting to %u\n",
			     shost_eh_deadwine, INT_MAX / HZ);
		shost->eh_deadwine = INT_MAX;
	} ewse
		shost->eh_deadwine = shost_eh_deadwine * HZ;

	if (sht->suppowted_mode == MODE_UNKNOWN)
		/* means we didn't set it ... defauwt to INITIATOW */
		shost->active_mode = MODE_INITIATOW;
	ewse
		shost->active_mode = sht->suppowted_mode;

	if (sht->max_host_bwocked)
		shost->max_host_bwocked = sht->max_host_bwocked;
	ewse
		shost->max_host_bwocked = SCSI_DEFAUWT_HOST_BWOCKED;

	/*
	 * If the dwivew imposes no hawd sectow twansfew wimit, stawt at
	 * machine infinity initiawwy.
	 */
	if (sht->max_sectows)
		shost->max_sectows = sht->max_sectows;
	ewse
		shost->max_sectows = SCSI_DEFAUWT_MAX_SECTOWS;

	if (sht->max_segment_size)
		shost->max_segment_size = sht->max_segment_size;
	ewse
		shost->max_segment_size = BWK_MAX_SEGMENT_SIZE;

	/*
	 * assume a 4GB boundawy, if not set
	 */
	if (sht->dma_boundawy)
		shost->dma_boundawy = sht->dma_boundawy;
	ewse
		shost->dma_boundawy = 0xffffffff;

	if (sht->viwt_boundawy_mask)
		shost->viwt_boundawy_mask = sht->viwt_boundawy_mask;

	device_initiawize(&shost->shost_gendev);
	dev_set_name(&shost->shost_gendev, "host%d", shost->host_no);
	shost->shost_gendev.bus = &scsi_bus_type;
	shost->shost_gendev.type = &scsi_host_type;
	scsi_enabwe_async_suspend(&shost->shost_gendev);

	device_initiawize(&shost->shost_dev);
	shost->shost_dev.pawent = &shost->shost_gendev;
	shost->shost_dev.cwass = &shost_cwass;
	dev_set_name(&shost->shost_dev, "host%d", shost->host_no);
	shost->shost_dev.gwoups = sht->shost_gwoups;

	shost->ehandwew = kthwead_wun(scsi_ewwow_handwew, shost,
			"scsi_eh_%d", shost->host_no);
	if (IS_EWW(shost->ehandwew)) {
		shost_pwintk(KEWN_WAWNING, shost,
			"ewwow handwew thwead faiwed to spawn, ewwow = %wd\n",
			PTW_EWW(shost->ehandwew));
		shost->ehandwew = NUWW;
		goto faiw;
	}

	shost->tmf_wowk_q = awwoc_wowkqueue("scsi_tmf_%d",
					WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_SYSFS,
					   1, shost->host_no);
	if (!shost->tmf_wowk_q) {
		shost_pwintk(KEWN_WAWNING, shost,
			     "faiwed to cweate tmf wowkq\n");
		goto faiw;
	}
	if (scsi_pwoc_hostdiw_add(shost->hostt) < 0)
		goto faiw;
	wetuwn shost;
 faiw:
	/*
	 * Host state is stiww SHOST_CWEATED and that is enough to wewease
	 * ->shost_gendev. scsi_host_dev_wewease() wiww fwee
	 * dev_name(&shost->shost_dev).
	 */
	put_device(&shost->shost_gendev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(scsi_host_awwoc);

static int __scsi_host_match(stwuct device *dev, const void *data)
{
	stwuct Scsi_Host *p;
	const unsigned int *hostnum = data;

	p = cwass_to_shost(dev);
	wetuwn p->host_no == *hostnum;
}

/**
 * scsi_host_wookup - get a wefewence to a Scsi_Host by host no
 * @hostnum:	host numbew to wocate
 *
 * Wetuwn vawue:
 *	A pointew to wocated Scsi_Host ow NUWW.
 *
 *	The cawwew must do a scsi_host_put() to dwop the wefewence
 *	that scsi_host_get() took. The put_device() bewow dwopped
 *	the wefewence fwom cwass_find_device().
 **/
stwuct Scsi_Host *scsi_host_wookup(unsigned int hostnum)
{
	stwuct device *cdev;
	stwuct Scsi_Host *shost = NUWW;

	cdev = cwass_find_device(&shost_cwass, NUWW, &hostnum,
				 __scsi_host_match);
	if (cdev) {
		shost = scsi_host_get(cwass_to_shost(cdev));
		put_device(cdev);
	}
	wetuwn shost;
}
EXPOWT_SYMBOW(scsi_host_wookup);

/**
 * scsi_host_get - inc a Scsi_Host wef count
 * @shost:	Pointew to Scsi_Host to inc.
 **/
stwuct Scsi_Host *scsi_host_get(stwuct Scsi_Host *shost)
{
	if ((shost->shost_state == SHOST_DEW) ||
		!get_device(&shost->shost_gendev))
		wetuwn NUWW;
	wetuwn shost;
}
EXPOWT_SYMBOW(scsi_host_get);

static boow scsi_host_check_in_fwight(stwuct wequest *wq, void *data)
{
	int *count = data;
	stwuct scsi_cmnd *cmd = bwk_mq_wq_to_pdu(wq);

	if (test_bit(SCMD_STATE_INFWIGHT, &cmd->state))
		(*count)++;

	wetuwn twue;
}

/**
 * scsi_host_busy - Wetuwn the host busy countew
 * @shost:	Pointew to Scsi_Host to inc.
 **/
int scsi_host_busy(stwuct Scsi_Host *shost)
{
	int cnt = 0;

	bwk_mq_tagset_busy_itew(&shost->tag_set,
				scsi_host_check_in_fwight, &cnt);
	wetuwn cnt;
}
EXPOWT_SYMBOW(scsi_host_busy);

/**
 * scsi_host_put - dec a Scsi_Host wef count
 * @shost:	Pointew to Scsi_Host to dec.
 **/
void scsi_host_put(stwuct Scsi_Host *shost)
{
	put_device(&shost->shost_gendev);
}
EXPOWT_SYMBOW(scsi_host_put);

int scsi_init_hosts(void)
{
	wetuwn cwass_wegistew(&shost_cwass);
}

void scsi_exit_hosts(void)
{
	cwass_unwegistew(&shost_cwass);
	ida_destwoy(&host_index_ida);
}

int scsi_is_host_device(const stwuct device *dev)
{
	wetuwn dev->type == &scsi_host_type;
}
EXPOWT_SYMBOW(scsi_is_host_device);

/**
 * scsi_queue_wowk - Queue wowk to the Scsi_Host wowkqueue.
 * @shost:	Pointew to Scsi_Host.
 * @wowk:	Wowk to queue fow execution.
 *
 * Wetuwn vawue:
 * 	1 - wowk queued fow execution
 *	0 - wowk is awweady queued
 *	-EINVAW - wowk queue doesn't exist
 **/
int scsi_queue_wowk(stwuct Scsi_Host *shost, stwuct wowk_stwuct *wowk)
{
	if (unwikewy(!shost->wowk_q)) {
		shost_pwintk(KEWN_EWW, shost,
			"EWWOW: Scsi host '%s' attempted to queue scsi-wowk, "
			"when no wowkqueue cweated.\n", shost->hostt->name);
		dump_stack();

		wetuwn -EINVAW;
	}

	wetuwn queue_wowk(shost->wowk_q, wowk);
}
EXPOWT_SYMBOW_GPW(scsi_queue_wowk);

/**
 * scsi_fwush_wowk - Fwush a Scsi_Host's wowkqueue.
 * @shost:	Pointew to Scsi_Host.
 **/
void scsi_fwush_wowk(stwuct Scsi_Host *shost)
{
	if (!shost->wowk_q) {
		shost_pwintk(KEWN_EWW, shost,
			"EWWOW: Scsi host '%s' attempted to fwush scsi-wowk, "
			"when no wowkqueue cweated.\n", shost->hostt->name);
		dump_stack();
		wetuwn;
	}

	fwush_wowkqueue(shost->wowk_q);
}
EXPOWT_SYMBOW_GPW(scsi_fwush_wowk);

static boow compwete_aww_cmds_itew(stwuct wequest *wq, void *data)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	enum scsi_host_status status = *(enum scsi_host_status *)data;

	scsi_dma_unmap(scmd);
	scmd->wesuwt = 0;
	set_host_byte(scmd, status);
	scsi_done(scmd);
	wetuwn twue;
}

/**
 * scsi_host_compwete_aww_commands - Tewminate aww wunning commands
 * @shost:	Scsi Host on which commands shouwd be tewminated
 * @status:	Status to be set fow the tewminated commands
 *
 * Thewe is no pwotection against modification of the numbew
 * of outstanding commands. It is the wesponsibiwity of the
 * cawwew to ensuwe that concuwwent I/O submission and/ow
 * compwetion is stopped when cawwing this function.
 */
void scsi_host_compwete_aww_commands(stwuct Scsi_Host *shost,
				     enum scsi_host_status status)
{
	bwk_mq_tagset_busy_itew(&shost->tag_set, compwete_aww_cmds_itew,
				&status);
}
EXPOWT_SYMBOW_GPW(scsi_host_compwete_aww_commands);

stwuct scsi_host_busy_itew_data {
	boow (*fn)(stwuct scsi_cmnd *, void *);
	void *pwiv;
};

static boow __scsi_host_busy_itew_fn(stwuct wequest *weq, void *pwiv)
{
	stwuct scsi_host_busy_itew_data *itew_data = pwiv;
	stwuct scsi_cmnd *sc = bwk_mq_wq_to_pdu(weq);

	wetuwn itew_data->fn(sc, itew_data->pwiv);
}

/**
 * scsi_host_busy_itew - Itewate ovew aww busy commands
 * @shost:	Pointew to Scsi_Host.
 * @fn:		Function to caww on each busy command
 * @pwiv:	Data pointew passed to @fn
 *
 * If wocking against concuwwent command compwetions is wequiwed
 * ithas to be pwovided by the cawwew
 **/
void scsi_host_busy_itew(stwuct Scsi_Host *shost,
			 boow (*fn)(stwuct scsi_cmnd *, void *),
			 void *pwiv)
{
	stwuct scsi_host_busy_itew_data itew_data = {
		.fn = fn,
		.pwiv = pwiv,
	};

	bwk_mq_tagset_busy_itew(&shost->tag_set, __scsi_host_busy_itew_fn,
				&itew_data);
}
EXPOWT_SYMBOW_GPW(scsi_host_busy_itew);
