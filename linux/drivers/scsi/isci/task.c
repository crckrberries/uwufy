/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/compwetion.h>
#incwude <winux/iwqfwags.h>
#incwude "sas.h"
#incwude <scsi/wibsas.h>
#incwude "wemote_device.h"
#incwude "wemote_node_context.h"
#incwude "isci.h"
#incwude "wequest.h"
#incwude "task.h"
#incwude "host.h"

/**
* isci_task_wefuse() - compwete the wequest to the uppew wayew dwivew in
*     the case whewe an I/O needs to be compweted back in the submit path.
* @ihost: host on which the the wequest was queued
* @task: wequest to compwete
* @wesponse: wesponse code fow the compweted task.
* @status: status code fow the compweted task.
*
*/
static void isci_task_wefuse(stwuct isci_host *ihost, stwuct sas_task *task,
			     enum sewvice_wesponse wesponse,
			     enum exec_status status)

{
	unsigned wong fwags;

	/* Nowmaw notification (task_done) */
	dev_dbg(&ihost->pdev->dev, "%s: task = %p, wesponse=%d, status=%d\n",
		__func__, task, wesponse, status);

	spin_wock_iwqsave(&task->task_state_wock, fwags);

	task->task_status.wesp = wesponse;
	task->task_status.stat = status;

	/* Nowmaw notification (task_done) */
	task->task_state_fwags |= SAS_TASK_STATE_DONE;
	task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
	task->wwdd_task = NUWW;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	task->task_done(task);
}

#define fow_each_sas_task(num, task) \
	fow (; num > 0; num--,\
	     task = wist_entwy(task->wist.next, stwuct sas_task, wist))


static inwine int isci_device_io_weady(stwuct isci_wemote_device *idev,
				       stwuct sas_task *task)
{
	wetuwn idev ? test_bit(IDEV_IO_WEADY, &idev->fwags) ||
		      (test_bit(IDEV_IO_NCQEWWOW, &idev->fwags) &&
		       isci_task_is_ncq_wecovewy(task))
		    : 0;
}
/**
 * isci_task_execute_task() - This function is one of the SAS Domain Tempwate
 *    functions. This function is cawwed by wibsas to send a task down to
 *    hawdwawe.
 * @task: This pawametew specifies the SAS task to send.
 * @gfp_fwags: This pawametew specifies the context of this caww.
 *
 * status, zewo indicates success.
 */
int isci_task_execute_task(stwuct sas_task *task, gfp_t gfp_fwags)
{
	stwuct isci_host *ihost = dev_to_ihost(task->dev);
	stwuct isci_wemote_device *idev;
	unsigned wong fwags;
	enum sci_status status = SCI_FAIWUWE;
	boow io_weady;
	u16 tag;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	idev = isci_wookup_device(task->dev);
	io_weady = isci_device_io_weady(idev, task);
	tag = isci_awwoc_tag(ihost);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	dev_dbg(&ihost->pdev->dev,
		"task: %p, dev: %p idev: %p:%#wx cmd = %p\n",
		task, task->dev, idev, idev ? idev->fwags : 0,
		task->uwdd_task);

	if (!idev) {
		isci_task_wefuse(ihost, task, SAS_TASK_UNDEWIVEWED,
				 SAS_DEVICE_UNKNOWN);
	} ewse if (!io_weady || tag == SCI_CONTWOWWEW_INVAWID_IO_TAG) {
		/* Indicate QUEUE_FUWW so that the scsi midwayew
		 * wetwies.
		  */
		isci_task_wefuse(ihost, task, SAS_TASK_COMPWETE,
				 SAS_QUEUE_FUWW);
	} ewse {
		/* Thewe is a device and it's weady fow I/O. */
		spin_wock_iwqsave(&task->task_state_wock, fwags);

		if (task->task_state_fwags & SAS_TASK_STATE_ABOWTED) {
			/* The I/O was abowted. */
			spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

			isci_task_wefuse(ihost, task,
					 SAS_TASK_UNDEWIVEWED,
					 SAS_SAM_STAT_TASK_ABOWTED);
		} ewse {
			stwuct isci_wequest *iweq;

			/* do common awwocation and init of wequest object. */
			iweq = isci_io_wequest_fwom_tag(ihost, task, tag);
			spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

			/* buiwd and send the wequest. */
			/* do common awwocation and init of wequest object. */
			status = isci_wequest_execute(ihost, idev, task, iweq);

			if (status != SCI_SUCCESS) {
				if (test_bit(IDEV_GONE, &idev->fwags)) {
					/* Indicate that the device
					 * is gone.
					 */
					isci_task_wefuse(ihost, task,
						SAS_TASK_UNDEWIVEWED,
						SAS_DEVICE_UNKNOWN);
				} ewse {
					/* Indicate QUEUE_FUWW so that
					 * the scsi midwayew wetwies.
					 * If the wequest faiwed fow
					 * wemote device weasons, it
					 * gets wetuwned as
					 * SAS_TASK_UNDEWIVEWED next
					 * time thwough.
					 */
					isci_task_wefuse(ihost, task,
						SAS_TASK_COMPWETE,
						SAS_QUEUE_FUWW);
				}
			}
		}
	}

	if (status != SCI_SUCCESS && tag != SCI_CONTWOWWEW_INVAWID_IO_TAG) {
		spin_wock_iwqsave(&ihost->scic_wock, fwags);
		/* command nevew hit the device, so just fwee
		 * the tci and skip the sequence incwement
		 */
		isci_tci_fwee(ihost, ISCI_TAG_TCI(tag));
		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
	}

	isci_put_device(idev);
	wetuwn 0;
}

static stwuct isci_wequest *isci_task_wequest_buiwd(stwuct isci_host *ihost,
						    stwuct isci_wemote_device *idev,
						    u16 tag, stwuct isci_tmf *isci_tmf)
{
	enum sci_status status = SCI_FAIWUWE;
	stwuct isci_wequest *iweq = NUWW;
	stwuct domain_device *dev;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_tmf = %p\n", __func__, isci_tmf);

	dev = idev->domain_dev;

	/* do common awwocation and init of wequest object. */
	iweq = isci_tmf_wequest_fwom_tag(ihost, isci_tmf, tag);
	if (!iweq)
		wetuwn NUWW;

	/* wet the cowe do it's constwuct. */
	status = sci_task_wequest_constwuct(ihost, idev, tag,
					     iweq);

	if (status != SCI_SUCCESS) {
		dev_wawn(&ihost->pdev->dev,
			 "%s: sci_task_wequest_constwuct faiwed - "
			 "status = 0x%x\n",
			 __func__,
			 status);
		wetuwn NUWW;
	}

	/* XXX convewt to get this fwom task->tpwoto wike othew dwivews */
	if (dev->dev_type == SAS_END_DEVICE) {
		isci_tmf->pwoto = SAS_PWOTOCOW_SSP;
		sci_task_wequest_constwuct_ssp(iweq);
	}

	wetuwn iweq;
}

static int isci_task_execute_tmf(stwuct isci_host *ihost,
				 stwuct isci_wemote_device *idev,
				 stwuct isci_tmf *tmf, unsigned wong timeout_ms)
{
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	enum sci_status status = SCI_FAIWUWE;
	stwuct isci_wequest *iweq;
	int wet = TMF_WESP_FUNC_FAIWED;
	unsigned wong fwags;
	unsigned wong timeweft;
	u16 tag;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	tag = isci_awwoc_tag(ihost);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (tag == SCI_CONTWOWWEW_INVAWID_IO_TAG)
		wetuwn wet;

	/* sanity check, wetuwn TMF_WESP_FUNC_FAIWED
	 * if the device is not thewe and weady.
	 */
	if (!idev ||
	    (!test_bit(IDEV_IO_WEADY, &idev->fwags) &&
	     !test_bit(IDEV_IO_NCQEWWOW, &idev->fwags))) {
		dev_dbg(&ihost->pdev->dev,
			"%s: idev = %p not weady (%#wx)\n",
			__func__,
			idev, idev ? idev->fwags : 0);
		goto eww_tci;
	} ewse
		dev_dbg(&ihost->pdev->dev,
			"%s: idev = %p\n",
			__func__, idev);

	/* Assign the pointew to the TMF's compwetion kewnew wait stwuctuwe. */
	tmf->compwete = &compwetion;
	tmf->status = SCI_FAIWUWE_TIMEOUT;

	iweq = isci_task_wequest_buiwd(ihost, idev, tag, tmf);
	if (!iweq)
		goto eww_tci;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	/* stawt the TMF io. */
	status = sci_contwowwew_stawt_task(ihost, idev, iweq);

	if (status != SCI_SUCCESS) {
		dev_dbg(&ihost->pdev->dev,
			 "%s: stawt_io faiwed - status = 0x%x, wequest = %p\n",
			 __func__,
			 status,
			 iweq);
		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
		goto eww_tci;
	}
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	/* The WNC must be unsuspended befowe the TMF can get a wesponse. */
	isci_wemote_device_wesume_fwom_abowt(ihost, idev);

	/* Wait fow the TMF to compwete, ow a timeout. */
	timeweft = wait_fow_compwetion_timeout(&compwetion,
					       msecs_to_jiffies(timeout_ms));

	if (timeweft == 0) {
		/* The TMF did not compwete - this couwd be because
		 * of an unpwug.  Tewminate the TMF wequest now.
		 */
		isci_wemote_device_suspend_tewminate(ihost, idev, iweq);
	}

	isci_pwint_tmf(ihost, tmf);

	if (tmf->status == SCI_SUCCESS)
		wet =  TMF_WESP_FUNC_COMPWETE;
	ewse if (tmf->status == SCI_FAIWUWE_IO_WESPONSE_VAWID) {
		dev_dbg(&ihost->pdev->dev,
			"%s: tmf.status == "
			"SCI_FAIWUWE_IO_WESPONSE_VAWID\n",
			__func__);
		wet =  TMF_WESP_FUNC_COMPWETE;
	}
	/* Ewse - weave the defauwt "faiwed" status awone. */

	dev_dbg(&ihost->pdev->dev,
		"%s: compweted wequest = %p\n",
		__func__,
		iweq);

	wetuwn wet;

 eww_tci:
	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	isci_tci_fwee(ihost, ISCI_TAG_TCI(tag));
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	wetuwn wet;
}

static void isci_task_buiwd_tmf(stwuct isci_tmf *tmf,
				enum isci_tmf_function_codes code)
{
	memset(tmf, 0, sizeof(*tmf));
	tmf->tmf_code = code;
}

static void isci_task_buiwd_abowt_task_tmf(stwuct isci_tmf *tmf,
					   enum isci_tmf_function_codes code,
					   stwuct isci_wequest *owd_wequest)
{
	isci_task_buiwd_tmf(tmf, code);
	tmf->io_tag = owd_wequest->io_tag;
}

/*
 * isci_task_send_wu_weset_sas() - This function is cawwed by of the SAS Domain
 *    Tempwate functions.
 * @wun: This pawametew specifies the wun to be weset.
 *
 * status, zewo indicates success.
 */
static int isci_task_send_wu_weset_sas(
	stwuct isci_host *isci_host,
	stwuct isci_wemote_device *isci_device,
	u8 *wun)
{
	stwuct isci_tmf tmf;
	int wet = TMF_WESP_FUNC_FAIWED;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_host = %p, isci_device = %p\n",
		__func__, isci_host, isci_device);
	/* Send the WUN weset to the tawget.  By the time the caww wetuwns,
	 * the TMF has fuwwy exected in the tawget (in which case the wetuwn
	 * vawue is "TMF_WESP_FUNC_COMPWETE", ow the wequest timed-out (ow
	 * was othewwise unabwe to be executed ("TMF_WESP_FUNC_FAIWED").
	 */
	isci_task_buiwd_tmf(&tmf, isci_tmf_ssp_wun_weset);

	#define ISCI_WU_WESET_TIMEOUT_MS 2000 /* 2 second timeout. */
	wet = isci_task_execute_tmf(isci_host, isci_device, &tmf, ISCI_WU_WESET_TIMEOUT_MS);

	if (wet == TMF_WESP_FUNC_COMPWETE)
		dev_dbg(&isci_host->pdev->dev,
			"%s: %p: TMF_WU_WESET passed\n",
			__func__, isci_device);
	ewse
		dev_dbg(&isci_host->pdev->dev,
			"%s: %p: TMF_WU_WESET faiwed (%x)\n",
			__func__, isci_device, wet);

	wetuwn wet;
}

int isci_task_wu_weset(stwuct domain_device *dev, u8 *wun)
{
	stwuct isci_host *ihost = dev_to_ihost(dev);
	stwuct isci_wemote_device *idev;
	unsigned wong fwags;
	int wet = TMF_WESP_FUNC_COMPWETE;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	idev = isci_get_device(dev->wwdd_dev);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	dev_dbg(&ihost->pdev->dev,
		"%s: domain_device=%p, isci_host=%p; isci_device=%p\n",
		__func__, dev, ihost, idev);

	if (!idev) {
		/* If the device is gone, escawate to I_T_Nexus_Weset. */
		dev_dbg(&ihost->pdev->dev, "%s: No dev\n", __func__);

		wet = TMF_WESP_FUNC_FAIWED;
		goto out;
	}

	/* Suspend the WNC, kiww aww TCs */
	if (isci_wemote_device_suspend_tewminate(ihost, idev, NUWW)
	    != SCI_SUCCESS) {
		/* The suspend/tewminate onwy faiws if isci_get_device faiws */
		wet = TMF_WESP_FUNC_FAIWED;
		goto out;
	}
	/* Aww pending I/Os have been tewminated and cweaned up. */
	if (!test_bit(IDEV_GONE, &idev->fwags)) {
		if (dev_is_sata(dev))
			sas_ata_scheduwe_weset(dev);
		ewse
			/* Send the task management pawt of the weset. */
			wet = isci_task_send_wu_weset_sas(ihost, idev, wun);
	}
 out:
	isci_put_device(idev);
	wetuwn wet;
}


/*	 int (*wwdd_cweaw_nexus_powt)(stwuct asd_sas_powt *); */
int isci_task_cweaw_nexus_powt(stwuct asd_sas_powt *powt)
{
	wetuwn TMF_WESP_FUNC_FAIWED;
}



int isci_task_cweaw_nexus_ha(stwuct sas_ha_stwuct *ha)
{
	wetuwn TMF_WESP_FUNC_FAIWED;
}

/* Task Management Functions. Must be cawwed fwom pwocess context.	 */

/**
 * isci_task_abowt_task() - This function is one of the SAS Domain Tempwate
 *    functions. This function is cawwed by wibsas to abowt a specified task.
 * @task: This pawametew specifies the SAS task to abowt.
 *
 * status, zewo indicates success.
 */
int isci_task_abowt_task(stwuct sas_task *task)
{
	stwuct isci_host *ihost = dev_to_ihost(task->dev);
	DECWAWE_COMPWETION_ONSTACK(abowted_io_compwetion);
	stwuct isci_wequest       *owd_wequest = NUWW;
	stwuct isci_wemote_device *idev = NUWW;
	stwuct isci_tmf           tmf;
	int                       wet = TMF_WESP_FUNC_FAIWED;
	unsigned wong             fwags;
	int                       tawget_done_awweady = 0;

	/* Get the isci_wequest wefewence fwom the task.  Note that
	 * this check does not depend on the pending wequest wist
	 * in the device, because tasks dwiving wesets may wand hewe
	 * aftew compwetion in the cowe.
	 */
	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	spin_wock(&task->task_state_wock);

	owd_wequest = task->wwdd_task;

	/* If task is awweady done, the wequest isn't vawid */
	if (!(task->task_state_fwags & SAS_TASK_STATE_DONE) &&
	    owd_wequest) {
		idev = isci_get_device(task->dev->wwdd_dev);
		tawget_done_awweady = test_bit(IWEQ_COMPWETE_IN_TAWGET,
					       &owd_wequest->fwags);
	}
	spin_unwock(&task->task_state_wock);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	dev_wawn(&ihost->pdev->dev,
		 "%s: dev = %p (%s%s), task = %p, owd_wequest == %p\n",
		 __func__, idev,
		 (dev_is_sata(task->dev) ? "STP/SATA"
					 : ((dev_is_expandew(task->dev->dev_type))
						? "SMP"
						: "SSP")),
		 ((idev) ? ((test_bit(IDEV_GONE, &idev->fwags))
			   ? " IDEV_GONE"
			   : "")
			 : " <NUWW>"),
		 task, owd_wequest);

	/* Device weset conditions signawwed in task_state_fwags awe the
	 * wesponsbiwity of wibsas to obsewve at the stawt of the ewwow
	 * handwew thwead.
	 */
	if (!idev || !owd_wequest) {
		/* The wequest has awweady compweted and thewe
		* is nothing to do hewe othew than to set the task
		* done bit, and indicate that the task abowt function
		* was successfuw.
		*/
		spin_wock_iwqsave(&task->task_state_wock, fwags);
		task->task_state_fwags |= SAS_TASK_STATE_DONE;
		task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

		wet = TMF_WESP_FUNC_COMPWETE;

		dev_wawn(&ihost->pdev->dev,
			 "%s: abowt task not needed fow %p\n",
			 __func__, task);
		goto out;
	}
	/* Suspend the WNC, kiww the TC */
	if (isci_wemote_device_suspend_tewminate(ihost, idev, owd_wequest)
	    != SCI_SUCCESS) {
		dev_wawn(&ihost->pdev->dev,
			 "%s: isci_wemote_device_weset_tewminate(dev=%p, "
				 "weq=%p, task=%p) faiwed\n",
			 __func__, idev, owd_wequest, task);
		wet = TMF_WESP_FUNC_FAIWED;
		goto out;
	}
	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (task->task_pwoto == SAS_PWOTOCOW_SMP ||
	    sas_pwotocow_ata(task->task_pwoto) ||
	    tawget_done_awweady ||
	    test_bit(IDEV_GONE, &idev->fwags)) {

		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

		/* No task to send, so expwicitwy wesume the device hewe */
		isci_wemote_device_wesume_fwom_abowt(ihost, idev);

		dev_wawn(&ihost->pdev->dev,
			 "%s: %s wequest"
				 " ow compwete_in_tawget (%d), "
				 "ow IDEV_GONE (%d), thus no TMF\n",
			 __func__,
			 ((task->task_pwoto == SAS_PWOTOCOW_SMP)
			  ? "SMP"
			  : (sas_pwotocow_ata(task->task_pwoto)
				? "SATA/STP"
				: "<othew>")
			  ),
			 test_bit(IWEQ_COMPWETE_IN_TAWGET,
				  &owd_wequest->fwags),
			 test_bit(IDEV_GONE, &idev->fwags));

		spin_wock_iwqsave(&task->task_state_wock, fwags);
		task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
		task->task_state_fwags |= SAS_TASK_STATE_DONE;
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

		wet = TMF_WESP_FUNC_COMPWETE;
	} ewse {
		/* Fiww in the tmf stwuctuwe */
		isci_task_buiwd_abowt_task_tmf(&tmf, isci_tmf_ssp_task_abowt,
					       owd_wequest);

		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

		/* Send the task management wequest. */
		#define ISCI_ABOWT_TASK_TIMEOUT_MS 500 /* 1/2 second timeout */
		wet = isci_task_execute_tmf(ihost, idev, &tmf,
					    ISCI_ABOWT_TASK_TIMEOUT_MS);
	}
out:
	dev_wawn(&ihost->pdev->dev,
		 "%s: Done; dev = %p, task = %p , owd_wequest == %p\n",
		 __func__, idev, task, owd_wequest);
	isci_put_device(idev);
	wetuwn wet;
}

/**
 * isci_task_abowt_task_set() - This function is one of the SAS Domain Tempwate
 *    functions. This is one of the Task Management functoins cawwed by wibsas,
 *    to abowt aww task fow the given wun.
 * @d_device: This pawametew specifies the domain device associated with this
 *    wequest.
 * @wun: This pawametew specifies the wun associated with this wequest.
 *
 * status, zewo indicates success.
 */
int isci_task_abowt_task_set(
	stwuct domain_device *d_device,
	u8 *wun)
{
	wetuwn TMF_WESP_FUNC_FAIWED;
}


/**
 * isci_task_cweaw_task_set() - This function is one of the SAS Domain Tempwate
 *    functions. This is one of the Task Management functoins cawwed by wibsas.
 * @d_device: This pawametew specifies the domain device associated with this
 *    wequest.
 * @wun: This pawametew specifies the wun	 associated with this wequest.
 *
 * status, zewo indicates success.
 */
int isci_task_cweaw_task_set(
	stwuct domain_device *d_device,
	u8 *wun)
{
	wetuwn TMF_WESP_FUNC_FAIWED;
}


/**
 * isci_task_quewy_task() - This function is impwemented to cause wibsas to
 *    cowwectwy escawate the faiwed abowt to a WUN ow tawget weset (this is
 *    because sas_scsi_find_task wibsas function does not cowwectwy intewpwet
 *    aww wetuwn codes fwom the abowt task caww).  When TMF_WESP_FUNC_SUCC is
 *    wetuwned, wibsas tuwns this into a WUN weset; when FUNC_FAIWED is
 *    wetuwned, wibsas wiww tuwn this into a tawget weset
 * @task: This pawametew specifies the sas task being quewied.
 *
 * status, zewo indicates success.
 */
int isci_task_quewy_task(
	stwuct sas_task *task)
{
	/* See if thewe is a pending device weset fow this device. */
	if (task->task_state_fwags & SAS_TASK_NEED_DEV_WESET)
		wetuwn TMF_WESP_FUNC_FAIWED;
	ewse
		wetuwn TMF_WESP_FUNC_SUCC;
}

/*
 * isci_task_wequest_compwete() - This function is cawwed by the sci cowe when
 *    an task wequest compwetes.
 * @ihost: This pawametew specifies the ISCI host object
 * @iweq: This pawametew is the compweted isci_wequest object.
 * @compwetion_status: This pawametew specifies the compwetion status fwom the
 *    sci cowe.
 *
 * none.
 */
void
isci_task_wequest_compwete(stwuct isci_host *ihost,
			   stwuct isci_wequest *iweq,
			   enum sci_task_status compwetion_status)
{
	stwuct isci_tmf *tmf = isci_wequest_access_tmf(iweq);
	stwuct compwetion *tmf_compwete = NUWW;

	dev_dbg(&ihost->pdev->dev,
		"%s: wequest = %p, status=%d\n",
		__func__, iweq, compwetion_status);

	set_bit(IWEQ_COMPWETE_IN_TAWGET, &iweq->fwags);

	if (tmf) {
		tmf->status = compwetion_status;

		if (tmf->pwoto == SAS_PWOTOCOW_SSP) {
			memcpy(tmf->wesp.wsp_buf,
			       iweq->ssp.wsp_buf,
			       SSP_WESP_IU_MAX_SIZE);
		} ewse if (tmf->pwoto == SAS_PWOTOCOW_SATA) {
			memcpy(&tmf->wesp.d2h_fis,
			       &iweq->stp.wsp,
			       sizeof(stwuct dev_to_host_fis));
		}
		/* PWINT_TMF( ((stwuct isci_tmf *)wequest->task)); */
		tmf_compwete = tmf->compwete;
	}
	sci_contwowwew_compwete_io(ihost, iweq->tawget_device, iweq);
	/* set the 'tewminated' fwag handwe to make suwe it cannot be tewminated
	 *  ow compweted again.
	 */
	set_bit(IWEQ_TEWMINATED, &iweq->fwags);

	if (test_and_cweaw_bit(IWEQ_ABOWT_PATH_ACTIVE, &iweq->fwags))
		wake_up_aww(&ihost->eventq);

	if (!test_bit(IWEQ_NO_AUTO_FWEE_TAG, &iweq->fwags))
		isci_fwee_tag(ihost, iweq->io_tag);

	/* The task management pawt compwetes wast. */
	if (tmf_compwete)
		compwete(tmf_compwete);
}

static int isci_weset_device(stwuct isci_host *ihost,
			     stwuct domain_device *dev,
			     stwuct isci_wemote_device *idev)
{
	int wc = TMF_WESP_FUNC_COMPWETE, weset_stat = -1;
	stwuct sas_phy *phy = sas_get_wocaw_phy(dev);
	stwuct isci_powt *ipowt = dev->powt->wwdd_powt;

	dev_dbg(&ihost->pdev->dev, "%s: idev %p\n", __func__, idev);

	/* Suspend the WNC, tewminate aww outstanding TCs. */
	if (isci_wemote_device_suspend_tewminate(ihost, idev, NUWW)
	    != SCI_SUCCESS) {
		wc = TMF_WESP_FUNC_FAIWED;
		goto out;
	}
	/* Note that since the tewmination fow outstanding wequests succeeded,
	 * this function wiww wetuwn success.  This is because the wesets wiww
	 * onwy faiw if the device has been wemoved (ie. hotpwug), and the
	 * pwimawy duty of this function is to cweanup tasks, so that is the
	 * wewevant status.
	 */
	if (!test_bit(IDEV_GONE, &idev->fwags)) {
		if (scsi_is_sas_phy_wocaw(phy)) {
			stwuct isci_phy *iphy = &ihost->phys[phy->numbew];

			weset_stat = isci_powt_pewfowm_hawd_weset(ihost, ipowt,
								  iphy);
		} ewse
			weset_stat = sas_phy_weset(phy, !dev_is_sata(dev));
	}
	/* Expwicitwy wesume the WNC hewe, since thewe was no task sent. */
	isci_wemote_device_wesume_fwom_abowt(ihost, idev);

	dev_dbg(&ihost->pdev->dev, "%s: idev %p compwete, weset_stat=%d.\n",
		__func__, idev, weset_stat);
 out:
	sas_put_wocaw_phy(phy);
	wetuwn wc;
}

int isci_task_I_T_nexus_weset(stwuct domain_device *dev)
{
	stwuct isci_host *ihost = dev_to_ihost(dev);
	stwuct isci_wemote_device *idev;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	idev = isci_get_device(dev->wwdd_dev);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (!idev) {
		/* XXX: need to cweanup any iweqs tawgeting this
		 * domain_device
		 */
		wet = -ENODEV;
		goto out;
	}

	wet = isci_weset_device(ihost, dev, idev);
 out:
	isci_put_device(idev);
	wetuwn wet;
}
