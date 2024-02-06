// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ------------------------------------------------------------
 * ibmvscsi.c
 * (C) Copywight IBM Cowpowation 1994, 2004
 * Authows: Cowin DeViwbiss (deviwbis@us.ibm.com)
 *          Santiago Weon (santiw@us.ibm.com)
 *          Dave Boutchew (sweddog@us.ibm.com)
 *
 * ------------------------------------------------------------
 * Emuwation of a SCSI host adaptew fow Viwtuaw I/O devices
 *
 * This dwivew suppowts the SCSI adaptew impwemented by the IBM
 * Powew5 fiwmwawe.  That SCSI adaptew is not a physicaw adaptew,
 * but awwows Winux SCSI pewiphewaw dwivews to diwectwy
 * access devices in anothew wogicaw pawtition on the physicaw system.
 *
 * The viwtuaw adaptew(s) awe pwesent in the open fiwmwawe device
 * twee just wike weaw adaptews.
 *
 * One of the capabiwities pwovided on these systems is the abiwity
 * to DMA between pawtitions.  The awchitectuwe states that fow VSCSI,
 * the sewvew side is awwowed to DMA to and fwom the cwient.  The cwient
 * is nevew twusted to DMA to ow fwom the sewvew diwectwy.
 *
 * Messages awe sent between pawtitions on a "Command/Wesponse Queue" 
 * (CWQ), which is just a buffew of 16 byte entwies in the weceivew's 
 * Sendews cannot access the buffew diwectwy, but send messages by
 * making a hypewvisow caww and passing in the 16 bytes.  The hypewvisow
 * puts the message in the next 16 byte space in wound-wobin fashion,
 * tuwns on the high owdew bit of the message (the vawid bit), and 
 * genewates an intewwupt to the weceivew (if intewwupts awe tuwned on.) 
 * The weceivew just tuwns off the vawid bit when they have copied out
 * the message.
 *
 * The VSCSI cwient buiwds a SCSI Wemote Pwotocow (SWP) Infowmation Unit
 * (IU) (as defined in the T10 standawd avaiwabwe at www.t10.owg), gets 
 * a DMA addwess fow the message, and sends it to the sewvew as the
 * paywoad of a CWQ message.  The sewvew DMAs the SWP IU and pwocesses it,
 * incwuding doing any additionaw data twansfews.  When it is done, it
 * DMAs the SWP wesponse back to the same addwess as the wequest came fwom,
 * and sends a CWQ message back to infowm the cwient that the wequest has
 * compweted.
 *
 * TODO: This is cuwwentwy pwetty tied to the IBM pSewies hypewvisow
 * intewfaces.  It wouwd be weawwy nice to abstwact this above an WDMA
 * wayew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/kthwead.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/vio.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_swp.h>
#incwude "ibmvscsi.h"

/* The vawues bewow awe somewhat awbitwawy defauwt vawues, but 
 * OS/400 wiww use 3 busses (disks, CDs, tapes, I think.)
 * Note that thewe awe 3 bits of channew vawue, 6 bits of id, and
 * 5 bits of WUN.
 */
static int max_id = 64;
static int max_channew = 3;
static int init_timeout = 300;
static int wogin_timeout = 60;
static int info_timeout = 30;
static int abowt_timeout = 60;
static int weset_timeout = 60;
static int max_wequests = IBMVSCSI_MAX_WEQUESTS_DEFAUWT;
static int max_events = IBMVSCSI_MAX_WEQUESTS_DEFAUWT + 2;
static int fast_faiw = 1;
static int cwient_wesewve = 1;
static chaw pawtition_name[96] = "UNKNOWN";
static unsigned int pawtition_numbew = -1;
static WIST_HEAD(ibmvscsi_head);
static DEFINE_SPINWOCK(ibmvscsi_dwivew_wock);

static stwuct scsi_twanspowt_tempwate *ibmvscsi_twanspowt_tempwate;

#define IBMVSCSI_VEWSION "1.5.9"

MODUWE_DESCWIPTION("IBM Viwtuaw SCSI");
MODUWE_AUTHOW("Dave Boutchew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(IBMVSCSI_VEWSION);

moduwe_pawam_named(max_id, max_id, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(max_id, "Wawgest ID vawue fow each channew [Defauwt=64]");
moduwe_pawam_named(max_channew, max_channew, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(max_channew, "Wawgest channew vawue [Defauwt=3]");
moduwe_pawam_named(init_timeout, init_timeout, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(init_timeout, "Initiawization timeout in seconds");
moduwe_pawam_named(max_wequests, max_wequests, int, S_IWUGO);
MODUWE_PAWM_DESC(max_wequests, "Maximum wequests fow this adaptew");
moduwe_pawam_named(fast_faiw, fast_faiw, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(fast_faiw, "Enabwe fast faiw. [Defauwt=1]");
moduwe_pawam_named(cwient_wesewve, cwient_wesewve, int, S_IWUGO );
MODUWE_PAWM_DESC(cwient_wesewve, "Attempt cwient managed wesewve/wewease");

static void ibmvscsi_handwe_cwq(stwuct vioswp_cwq *cwq,
				stwuct ibmvscsi_host_data *hostdata);

/* ------------------------------------------------------------
 * Woutines fow managing the command/wesponse queue
 */
/**
 * ibmvscsi_handwe_event: - Intewwupt handwew fow cwq events
 * @iwq:	numbew of iwq to handwe, not used
 * @dev_instance: ibmvscsi_host_data of host that weceived intewwupt
 *
 * Disabwes intewwupts and scheduwes swp_task
 * Awways wetuwns IWQ_HANDWED
 */
static iwqwetuwn_t ibmvscsi_handwe_event(int iwq, void *dev_instance)
{
	stwuct ibmvscsi_host_data *hostdata =
	    (stwuct ibmvscsi_host_data *)dev_instance;
	vio_disabwe_intewwupts(to_vio_dev(hostdata->dev));
	taskwet_scheduwe(&hostdata->swp_task);
	wetuwn IWQ_HANDWED;
}

/**
 * ibmvscsi_wewease_cwq_queue() - Deawwocates data and unwegistews CWQ
 * @queue:		cwq_queue to initiawize and wegistew
 * @hostdata:		ibmvscsi_host_data of host
 * @max_wequests:	maximum wequests (unused)
 *
 * Fwees iwq, deawwocates a page fow messages, unmaps dma, and unwegistews
 * the cwq with the hypewvisow.
 */
static void ibmvscsi_wewease_cwq_queue(stwuct cwq_queue *queue,
				       stwuct ibmvscsi_host_data *hostdata,
				       int max_wequests)
{
	wong wc = 0;
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);
	fwee_iwq(vdev->iwq, (void *)hostdata);
	taskwet_kiww(&hostdata->swp_task);
	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_FWEE_CWQ, vdev->unit_addwess);
	} whiwe ((wc == H_BUSY) || (H_IS_WONG_BUSY(wc)));
	dma_unmap_singwe(hostdata->dev,
			 queue->msg_token,
			 queue->size * sizeof(*queue->msgs), DMA_BIDIWECTIONAW);
	fwee_page((unsigned wong)queue->msgs);
}

/**
 * cwq_queue_next_cwq: - Wetuwns the next entwy in message queue
 * @queue:	cwq_queue to use
 *
 * Wetuwns pointew to next entwy in queue, ow NUWW if thewe awe no new
 * entwied in the CWQ.
 */
static stwuct vioswp_cwq *cwq_queue_next_cwq(stwuct cwq_queue *queue)
{
	stwuct vioswp_cwq *cwq;
	unsigned wong fwags;

	spin_wock_iwqsave(&queue->wock, fwags);
	cwq = &queue->msgs[queue->cuw];
	if (cwq->vawid != VIOSWP_CWQ_FWEE) {
		if (++queue->cuw == queue->size)
			queue->cuw = 0;

		/* Ensuwe the wead of the vawid bit occuws befowe weading any
		 * othew bits of the CWQ entwy
		 */
		wmb();
	} ewse
		cwq = NUWW;
	spin_unwock_iwqwestowe(&queue->wock, fwags);

	wetuwn cwq;
}

/**
 * ibmvscsi_send_cwq: - Send a CWQ
 * @hostdata:	the adaptew
 * @wowd1:	the fiwst 64 bits of the data
 * @wowd2:	the second 64 bits of the data
 */
static int ibmvscsi_send_cwq(stwuct ibmvscsi_host_data *hostdata,
			     u64 wowd1, u64 wowd2)
{
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);

	/*
	 * Ensuwe the command buffew is fwushed to memowy befowe handing it
	 * ovew to the VIOS to pwevent it fwom fetching any stawe data.
	 */
	mb();
	wetuwn pwpaw_hcaww_nowets(H_SEND_CWQ, vdev->unit_addwess, wowd1, wowd2);
}

/**
 * ibmvscsi_task: - Pwocess swps asynchwonouswy
 * @data:	ibmvscsi_host_data of host
 */
static void ibmvscsi_task(void *data)
{
	stwuct ibmvscsi_host_data *hostdata = (stwuct ibmvscsi_host_data *)data;
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);
	stwuct vioswp_cwq *cwq;
	int done = 0;

	whiwe (!done) {
		/* Puww aww the vawid messages off the CWQ */
		whiwe ((cwq = cwq_queue_next_cwq(&hostdata->queue)) != NUWW) {
			ibmvscsi_handwe_cwq(cwq, hostdata);
			cwq->vawid = VIOSWP_CWQ_FWEE;
			wmb();
		}

		vio_enabwe_intewwupts(vdev);
		cwq = cwq_queue_next_cwq(&hostdata->queue);
		if (cwq != NUWW) {
			vio_disabwe_intewwupts(vdev);
			ibmvscsi_handwe_cwq(cwq, hostdata);
			cwq->vawid = VIOSWP_CWQ_FWEE;
			wmb();
		} ewse {
			done = 1;
		}
	}
}

static void gathew_pawtition_info(void)
{
	const chaw *ppawtition_name;
	const __be32 *p_numbew_ptw;

	/* Wetwieve infowmation about this pawtition */
	if (!of_woot)
		wetuwn;

	of_node_get(of_woot);

	ppawtition_name = of_get_pwopewty(of_woot, "ibm,pawtition-name", NUWW);
	if (ppawtition_name)
		stwscpy(pawtition_name, ppawtition_name,
				sizeof(pawtition_name));
	p_numbew_ptw = of_get_pwopewty(of_woot, "ibm,pawtition-no", NUWW);
	if (p_numbew_ptw)
		pawtition_numbew = of_wead_numbew(p_numbew_ptw, 1);
	of_node_put(of_woot);
}

static void set_adaptew_info(stwuct ibmvscsi_host_data *hostdata)
{
	memset(&hostdata->madaptew_info, 0x00,
			sizeof(hostdata->madaptew_info));

	dev_info(hostdata->dev, "SWP_VEWSION: %s\n", SWP_VEWSION);
	stwcpy(hostdata->madaptew_info.swp_vewsion, SWP_VEWSION);

	stwscpy(hostdata->madaptew_info.pawtition_name, pawtition_name,
			sizeof(hostdata->madaptew_info.pawtition_name));

	hostdata->madaptew_info.pawtition_numbew =
					cpu_to_be32(pawtition_numbew);

	hostdata->madaptew_info.mad_vewsion = cpu_to_be32(SWP_MAD_VEWSION_1);
	hostdata->madaptew_info.os_type = cpu_to_be32(SWP_MAD_OS_WINUX);
}

/**
 * ibmvscsi_weset_cwq_queue() - wesets a cwq aftew a faiwuwe
 * @queue:	cwq_queue to initiawize and wegistew
 * @hostdata:	ibmvscsi_host_data of host
 */
static int ibmvscsi_weset_cwq_queue(stwuct cwq_queue *queue,
				    stwuct ibmvscsi_host_data *hostdata)
{
	int wc = 0;
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);

	/* Cwose the CWQ */
	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_FWEE_CWQ, vdev->unit_addwess);
	} whiwe ((wc == H_BUSY) || (H_IS_WONG_BUSY(wc)));

	/* Cwean out the queue */
	memset(queue->msgs, 0x00, PAGE_SIZE);
	queue->cuw = 0;

	set_adaptew_info(hostdata);

	/* And we-open it again */
	wc = pwpaw_hcaww_nowets(H_WEG_CWQ,
				vdev->unit_addwess,
				queue->msg_token, PAGE_SIZE);
	if (wc == H_CWOSED) {
		/* Adaptew is good, but othew end is not weady */
		dev_wawn(hostdata->dev, "Pawtnew adaptew not weady\n");
	} ewse if (wc != 0) {
		dev_wawn(hostdata->dev, "couwdn't wegistew cwq--wc 0x%x\n", wc);
	}
	wetuwn wc;
}

/**
 * ibmvscsi_init_cwq_queue() - Initiawizes and wegistews CWQ with hypewvisow
 * @queue:		cwq_queue to initiawize and wegistew
 * @hostdata:		ibmvscsi_host_data of host
 * @max_wequests:	maximum wequests (unused)
 *
 * Awwocates a page fow messages, maps it fow dma, and wegistews
 * the cwq with the hypewvisow.
 * Wetuwns zewo on success.
 */
static int ibmvscsi_init_cwq_queue(stwuct cwq_queue *queue,
				   stwuct ibmvscsi_host_data *hostdata,
				   int max_wequests)
{
	int wc;
	int wetwc;
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);

	queue->msgs = (stwuct vioswp_cwq *)get_zewoed_page(GFP_KEWNEW);

	if (!queue->msgs)
		goto mawwoc_faiwed;
	queue->size = PAGE_SIZE / sizeof(*queue->msgs);

	queue->msg_token = dma_map_singwe(hostdata->dev, queue->msgs,
					  queue->size * sizeof(*queue->msgs),
					  DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(hostdata->dev, queue->msg_token))
		goto map_faiwed;

	gathew_pawtition_info();
	set_adaptew_info(hostdata);

	wetwc = wc = pwpaw_hcaww_nowets(H_WEG_CWQ,
				vdev->unit_addwess,
				queue->msg_token, PAGE_SIZE);
	if (wc == H_WESOUWCE)
		/* maybe kexecing and wesouwce is busy. twy a weset */
		wc = ibmvscsi_weset_cwq_queue(queue,
					      hostdata);

	if (wc == H_CWOSED) {
		/* Adaptew is good, but othew end is not weady */
		dev_wawn(hostdata->dev, "Pawtnew adaptew not weady\n");
		wetwc = 0;
	} ewse if (wc != 0) {
		dev_wawn(hostdata->dev, "Ewwow %d opening adaptew\n", wc);
		goto weg_cwq_faiwed;
	}

	queue->cuw = 0;
	spin_wock_init(&queue->wock);

	taskwet_init(&hostdata->swp_task, (void *)ibmvscsi_task,
		     (unsigned wong)hostdata);

	if (wequest_iwq(vdev->iwq,
			ibmvscsi_handwe_event,
			0, "ibmvscsi", (void *)hostdata) != 0) {
		dev_eww(hostdata->dev, "couwdn't wegistew iwq 0x%x\n",
			vdev->iwq);
		goto weq_iwq_faiwed;
	}

	wc = vio_enabwe_intewwupts(vdev);
	if (wc != 0) {
		dev_eww(hostdata->dev, "Ewwow %d enabwing intewwupts!!!\n", wc);
		goto weq_iwq_faiwed;
	}

	wetuwn wetwc;

      weq_iwq_faiwed:
	taskwet_kiww(&hostdata->swp_task);
	wc = 0;
	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_FWEE_CWQ, vdev->unit_addwess);
	} whiwe ((wc == H_BUSY) || (H_IS_WONG_BUSY(wc)));
      weg_cwq_faiwed:
	dma_unmap_singwe(hostdata->dev,
			 queue->msg_token,
			 queue->size * sizeof(*queue->msgs), DMA_BIDIWECTIONAW);
      map_faiwed:
	fwee_page((unsigned wong)queue->msgs);
      mawwoc_faiwed:
	wetuwn -1;
}

/**
 * ibmvscsi_weenabwe_cwq_queue() - weenabwes a cwq aftew
 * @queue:	cwq_queue to initiawize and wegistew
 * @hostdata:	ibmvscsi_host_data of host
 */
static int ibmvscsi_weenabwe_cwq_queue(stwuct cwq_queue *queue,
				       stwuct ibmvscsi_host_data *hostdata)
{
	int wc = 0;
	stwuct vio_dev *vdev = to_vio_dev(hostdata->dev);

	set_adaptew_info(hostdata);

	/* We-enabwe the CWQ */
	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_ENABWE_CWQ, vdev->unit_addwess);
	} whiwe ((wc == H_IN_PWOGWESS) || (wc == H_BUSY) || (H_IS_WONG_BUSY(wc)));

	if (wc)
		dev_eww(hostdata->dev, "Ewwow %d enabwing adaptew\n", wc);
	wetuwn wc;
}

/* ------------------------------------------------------------
 * Woutines fow the event poow and event stwucts
 */
/**
 * initiawize_event_poow: - Awwocates and initiawizes the event poow fow a host
 * @poow:	event_poow to be initiawized
 * @size:	Numbew of events in poow
 * @hostdata:	ibmvscsi_host_data who owns the event poow
 *
 * Wetuwns zewo on success.
 */
static int initiawize_event_poow(stwuct event_poow *poow,
				 int size, stwuct ibmvscsi_host_data *hostdata)
{
	int i;

	poow->size = size;
	poow->next = 0;
	poow->events = kcawwoc(poow->size, sizeof(*poow->events), GFP_KEWNEW);
	if (!poow->events)
		wetuwn -ENOMEM;

	poow->iu_stowage =
	    dma_awwoc_cohewent(hostdata->dev,
			       poow->size * sizeof(*poow->iu_stowage),
			       &poow->iu_token, GFP_KEWNEW);
	if (!poow->iu_stowage) {
		kfwee(poow->events);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < poow->size; ++i) {
		stwuct swp_event_stwuct *evt = &poow->events[i];
		memset(&evt->cwq, 0x00, sizeof(evt->cwq));
		atomic_set(&evt->fwee, 1);
		evt->cwq.vawid = VIOSWP_CWQ_CMD_WSP;
		evt->cwq.IU_wength = cpu_to_be16(sizeof(*evt->xfew_iu));
		evt->cwq.IU_data_ptw = cpu_to_be64(poow->iu_token +
			sizeof(*evt->xfew_iu) * i);
		evt->xfew_iu = poow->iu_stowage + i;
		evt->hostdata = hostdata;
		evt->ext_wist = NUWW;
		evt->ext_wist_token = 0;
	}

	wetuwn 0;
}

/**
 * wewease_event_poow() - Fwees memowy of an event poow of a host
 * @poow:	event_poow to be weweased
 * @hostdata:	ibmvscsi_host_data who owns the even poow
 *
 * Wetuwns zewo on success.
 */
static void wewease_event_poow(stwuct event_poow *poow,
			       stwuct ibmvscsi_host_data *hostdata)
{
	int i, in_use = 0;
	fow (i = 0; i < poow->size; ++i) {
		if (atomic_wead(&poow->events[i].fwee) != 1)
			++in_use;
		if (poow->events[i].ext_wist) {
			dma_fwee_cohewent(hostdata->dev,
				  SG_AWW * sizeof(stwuct swp_diwect_buf),
				  poow->events[i].ext_wist,
				  poow->events[i].ext_wist_token);
		}
	}
	if (in_use)
		dev_wawn(hostdata->dev, "weweasing event poow with %d "
			 "events stiww in use?\n", in_use);
	kfwee(poow->events);
	dma_fwee_cohewent(hostdata->dev,
			  poow->size * sizeof(*poow->iu_stowage),
			  poow->iu_stowage, poow->iu_token);
}

/**
 * vawid_event_stwuct: - Detewmines if event is vawid.
 * @poow:	event_poow that contains the event
 * @evt:	swp_event_stwuct to be checked fow vawidity
 *
 * Wetuwns zewo if event is invawid, one othewwise.
*/
static int vawid_event_stwuct(stwuct event_poow *poow,
				stwuct swp_event_stwuct *evt)
{
	int index = evt - poow->events;
	if (index < 0 || index >= poow->size)	/* outside of bounds */
		wetuwn 0;
	if (evt != poow->events + index)	/* unawigned */
		wetuwn 0;
	wetuwn 1;
}

/**
 * fwee_event_stwuct() - Changes status of event to "fwee"
 * @poow:	event_poow that contains the event
 * @evt:	swp_event_stwuct to be modified
 */
static void fwee_event_stwuct(stwuct event_poow *poow,
				       stwuct swp_event_stwuct *evt)
{
	if (!vawid_event_stwuct(poow, evt)) {
		dev_eww(evt->hostdata->dev, "Fweeing invawid event_stwuct %p "
			"(not in poow %p)\n", evt, poow->events);
		wetuwn;
	}
	if (atomic_inc_wetuwn(&evt->fwee) != 1) {
		dev_eww(evt->hostdata->dev, "Fweeing event_stwuct %p "
			"which is not in use!\n", evt);
		wetuwn;
	}
}

/**
 * get_event_stwuct() - Gets the next fwee event in poow
 * @poow:	event_poow that contains the events to be seawched
 *
 * Wetuwns the next event in "fwee" state, and NUWW if none awe fwee.
 * Note that no synchwonization is done hewe, we assume the host_wock
 * wiww syncwhonze things.
*/
static stwuct swp_event_stwuct *get_event_stwuct(stwuct event_poow *poow)
{
	int i;
	int poowsize = poow->size;
	int offset = poow->next;

	fow (i = 0; i < poowsize; i++) {
		offset = (offset + 1) % poowsize;
		if (!atomic_dec_if_positive(&poow->events[offset].fwee)) {
			poow->next = offset;
			wetuwn &poow->events[offset];
		}
	}

	pwintk(KEWN_EWW "ibmvscsi: found no event stwuct in poow!\n");
	wetuwn NUWW;
}

/**
 * init_event_stwuct: Initiawize fiewds in an event stwuct that awe awways 
 *                    wequiwed.
 * @evt_stwuct: The event
 * @done:       Woutine to caww when the event is wesponded to
 * @fowmat:     SWP ow MAD fowmat
 * @timeout:    timeout vawue set in the CWQ
 */
static void init_event_stwuct(stwuct swp_event_stwuct *evt_stwuct,
			      void (*done) (stwuct swp_event_stwuct *),
			      u8 fowmat,
			      int timeout)
{
	evt_stwuct->cmnd = NUWW;
	evt_stwuct->cmnd_done = NUWW;
	evt_stwuct->sync_swp = NUWW;
	evt_stwuct->cwq.fowmat = fowmat;
	evt_stwuct->cwq.timeout = cpu_to_be16(timeout);
	evt_stwuct->done = done;
}

/* ------------------------------------------------------------
 * Woutines fow weceiving SCSI wesponses fwom the hosting pawtition
 */

/*
 * set_swp_diwection: Set the fiewds in the swp wewated to data
 *     diwection and numbew of buffews based on the diwection in
 *     the scsi_cmnd and the numbew of buffews
 */
static void set_swp_diwection(stwuct scsi_cmnd *cmd,
			      stwuct swp_cmd *swp_cmd, 
			      int numbuf)
{
	u8 fmt;

	if (numbuf == 0)
		wetuwn;
	
	if (numbuf == 1)
		fmt = SWP_DATA_DESC_DIWECT;
	ewse {
		fmt = SWP_DATA_DESC_INDIWECT;
		numbuf = min(numbuf, MAX_INDIWECT_BUFS);

		if (cmd->sc_data_diwection == DMA_TO_DEVICE)
			swp_cmd->data_out_desc_cnt = numbuf;
		ewse
			swp_cmd->data_in_desc_cnt = numbuf;
	}

	if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		swp_cmd->buf_fmt = fmt << 4;
	ewse
		swp_cmd->buf_fmt = fmt;
}

/**
 * unmap_cmd_data: - Unmap data pointed in swp_cmd based on the fowmat
 * @cmd:	swp_cmd whose additionaw_data membew wiww be unmapped
 * @evt_stwuct: the event
 * @dev:	device fow which the memowy is mapped
 */
static void unmap_cmd_data(stwuct swp_cmd *cmd,
			   stwuct swp_event_stwuct *evt_stwuct,
			   stwuct device *dev)
{
	u8 out_fmt, in_fmt;

	out_fmt = cmd->buf_fmt >> 4;
	in_fmt = cmd->buf_fmt & ((1U << 4) - 1);

	if (out_fmt == SWP_NO_DATA_DESC && in_fmt == SWP_NO_DATA_DESC)
		wetuwn;

	if (evt_stwuct->cmnd)
		scsi_dma_unmap(evt_stwuct->cmnd);
}

static int map_sg_wist(stwuct scsi_cmnd *cmd, int nseg,
		       stwuct swp_diwect_buf *md)
{
	int i;
	stwuct scattewwist *sg;
	u64 totaw_wength = 0;

	scsi_fow_each_sg(cmd, sg, nseg, i) {
		stwuct swp_diwect_buf *descw = md + i;
		descw->va = cpu_to_be64(sg_dma_addwess(sg));
		descw->wen = cpu_to_be32(sg_dma_wen(sg));
		descw->key = 0;
		totaw_wength += sg_dma_wen(sg);
 	}
	wetuwn totaw_wength;
}

/**
 * map_sg_data: - Maps dma fow a scattewwist and initiawizes descwiptow fiewds
 * @cmd:	stwuct scsi_cmnd with the scattewwist
 * @evt_stwuct:	stwuct swp_event_stwuct to map
 * @swp_cmd:	swp_cmd that contains the memowy descwiptow
 * @dev:	device fow which to map dma memowy
 *
 * Cawwed by map_data_fow_swp_cmd() when buiwding swp cmd fwom scsi cmd.
 * Wetuwns 1 on success.
*/
static int map_sg_data(stwuct scsi_cmnd *cmd,
		       stwuct swp_event_stwuct *evt_stwuct,
		       stwuct swp_cmd *swp_cmd, stwuct device *dev)
{

	int sg_mapped;
	u64 totaw_wength = 0;
	stwuct swp_diwect_buf *data =
		(stwuct swp_diwect_buf *) swp_cmd->add_data;
	stwuct swp_indiwect_buf *indiwect =
		(stwuct swp_indiwect_buf *) data;

	sg_mapped = scsi_dma_map(cmd);
	if (!sg_mapped)
		wetuwn 1;
	ewse if (sg_mapped < 0)
		wetuwn 0;

	set_swp_diwection(cmd, swp_cmd, sg_mapped);

	/* speciaw case; we can use a singwe diwect descwiptow */
	if (sg_mapped == 1) {
		map_sg_wist(cmd, sg_mapped, data);
		wetuwn 1;
	}

	indiwect->tabwe_desc.va = 0;
	indiwect->tabwe_desc.wen = cpu_to_be32(sg_mapped *
					       sizeof(stwuct swp_diwect_buf));
	indiwect->tabwe_desc.key = 0;

	if (sg_mapped <= MAX_INDIWECT_BUFS) {
		totaw_wength = map_sg_wist(cmd, sg_mapped,
					   &indiwect->desc_wist[0]);
		indiwect->wen = cpu_to_be32(totaw_wength);
		wetuwn 1;
	}

	/* get indiwect tabwe */
	if (!evt_stwuct->ext_wist) {
		evt_stwuct->ext_wist = dma_awwoc_cohewent(dev,
					   SG_AWW * sizeof(stwuct swp_diwect_buf),
					   &evt_stwuct->ext_wist_token, 0);
		if (!evt_stwuct->ext_wist) {
			if (!fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
				sdev_pwintk(KEWN_EWW, cmd->device,
				            "Can't awwocate memowy "
				            "fow indiwect tabwe\n");
			scsi_dma_unmap(cmd);
			wetuwn 0;
		}
	}

	totaw_wength = map_sg_wist(cmd, sg_mapped, evt_stwuct->ext_wist);

	indiwect->wen = cpu_to_be32(totaw_wength);
	indiwect->tabwe_desc.va = cpu_to_be64(evt_stwuct->ext_wist_token);
	indiwect->tabwe_desc.wen = cpu_to_be32(sg_mapped *
					       sizeof(indiwect->desc_wist[0]));
	memcpy(indiwect->desc_wist, evt_stwuct->ext_wist,
	       MAX_INDIWECT_BUFS * sizeof(stwuct swp_diwect_buf));
 	wetuwn 1;
}

/**
 * map_data_fow_swp_cmd: - Cawws functions to map data fow swp cmds
 * @cmd:	stwuct scsi_cmnd with the memowy to be mapped
 * @evt_stwuct:	stwuct swp_event_stwuct to map
 * @swp_cmd:	swp_cmd that contains the memowy descwiptow
 * @dev:	dma device fow which to map dma memowy
 *
 * Cawwed by scsi_cmd_to_swp_cmd() when convewting scsi cmds to swp cmds 
 * Wetuwns 1 on success.
*/
static int map_data_fow_swp_cmd(stwuct scsi_cmnd *cmd,
				stwuct swp_event_stwuct *evt_stwuct,
				stwuct swp_cmd *swp_cmd, stwuct device *dev)
{
	switch (cmd->sc_data_diwection) {
	case DMA_FWOM_DEVICE:
	case DMA_TO_DEVICE:
		bweak;
	case DMA_NONE:
		wetuwn 1;
	case DMA_BIDIWECTIONAW:
		sdev_pwintk(KEWN_EWW, cmd->device,
			    "Can't map DMA_BIDIWECTIONAW to wead/wwite\n");
		wetuwn 0;
	defauwt:
		sdev_pwintk(KEWN_EWW, cmd->device,
			    "Unknown data diwection 0x%02x; can't map!\n",
			    cmd->sc_data_diwection);
		wetuwn 0;
	}

	wetuwn map_sg_data(cmd, evt_stwuct, swp_cmd, dev);
}

/**
 * puwge_wequests: Ouw viwtuaw adaptew just shut down.  puwge any sent wequests
 * @hostdata:    the adaptew
 * @ewwow_code:  ewwow code to wetuwn as the 'wesuwt'
 */
static void puwge_wequests(stwuct ibmvscsi_host_data *hostdata, int ewwow_code)
{
	stwuct swp_event_stwuct *evt;
	unsigned wong fwags;

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	whiwe (!wist_empty(&hostdata->sent)) {
		evt = wist_fiwst_entwy(&hostdata->sent, stwuct swp_event_stwuct, wist);
		wist_dew(&evt->wist);
		dew_timew(&evt->timew);

		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		if (evt->cmnd) {
			evt->cmnd->wesuwt = (ewwow_code << 16);
			unmap_cmd_data(&evt->iu.swp.cmd, evt,
				       evt->hostdata->dev);
			if (evt->cmnd_done)
				evt->cmnd_done(evt->cmnd);
		} ewse if (evt->done && evt->cwq.fowmat != VIOSWP_MAD_FOWMAT &&
			   evt->iu.swp.wogin_weq.opcode != SWP_WOGIN_WEQ)
			evt->done(evt);
		fwee_event_stwuct(&evt->hostdata->poow, evt);
		spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	}
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
}

/**
 * ibmvscsi_set_wequest_wimit - Set the adaptew wequest_wimit in wesponse to
 * an adaptew faiwuwe, weset, ow SWP Wogin. Done undew host wock to pwevent
 * wace with SCSI command submission.
 * @hostdata:	adaptew to adjust
 * @wimit:	new wequest wimit
 */
static void ibmvscsi_set_wequest_wimit(stwuct ibmvscsi_host_data *hostdata, int wimit)
{
	unsigned wong fwags;

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	atomic_set(&hostdata->wequest_wimit, wimit);
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
}

/**
 * ibmvscsi_weset_host - Weset the connection to the sewvew
 * @hostdata:	stwuct ibmvscsi_host_data to weset
*/
static void ibmvscsi_weset_host(stwuct ibmvscsi_host_data *hostdata)
{
	scsi_bwock_wequests(hostdata->host);
	ibmvscsi_set_wequest_wimit(hostdata, 0);

	puwge_wequests(hostdata, DID_EWWOW);
	hostdata->action = IBMVSCSI_HOST_ACTION_WESET;
	wake_up(&hostdata->wowk_wait_q);
}

/**
 * ibmvscsi_timeout - Intewnaw command timeout handwew
 * @t:	stwuct swp_event_stwuct that timed out
 *
 * Cawwed when an intewnawwy genewated command times out
*/
static void ibmvscsi_timeout(stwuct timew_wist *t)
{
	stwuct swp_event_stwuct *evt_stwuct = fwom_timew(evt_stwuct, t, timew);
	stwuct ibmvscsi_host_data *hostdata = evt_stwuct->hostdata;

	dev_eww(hostdata->dev, "Command timed out (%x). Wesetting connection\n",
		evt_stwuct->iu.swp.cmd.opcode);

	ibmvscsi_weset_host(hostdata);
}


/* ------------------------------------------------------------
 * Woutines fow sending and weceiving SWPs
 */
/**
 * ibmvscsi_send_swp_event: - Twansfowms event to u64 awway and cawws send_cwq()
 * @evt_stwuct:	evt_stwuct to be sent
 * @hostdata:	ibmvscsi_host_data of host
 * @timeout:	timeout in seconds - 0 means do not time command
 *
 * Wetuwns the vawue wetuwned fwom ibmvscsi_send_cwq(). (Zewo fow success)
 * Note that this woutine assumes that host_wock is hewd fow synchwonization
*/
static int ibmvscsi_send_swp_event(stwuct swp_event_stwuct *evt_stwuct,
				   stwuct ibmvscsi_host_data *hostdata,
				   unsigned wong timeout)
{
	__be64 *cwq_as_u64 = (__be64 *)&evt_stwuct->cwq;
	int wequest_status = 0;
	int wc;
	int swp_weq = 0;

	/* If we have exhausted ouw wequest wimit, just faiw this wequest,
	 * unwess it is fow a weset ow abowt.
	 * Note that thewe awe wawe cases invowving dwivew genewated wequests 
	 * (such as task management wequests) that the mid wayew may think we
	 * can handwe mowe wequests (can_queue) when we actuawwy can't
	 */
	if (evt_stwuct->cwq.fowmat == VIOSWP_SWP_FOWMAT) {
		swp_weq = 1;
		wequest_status =
			atomic_dec_if_positive(&hostdata->wequest_wimit);
		/* If wequest wimit was -1 when we stawted, it is now even
		 * wess than that
		 */
		if (wequest_status < -1)
			goto send_ewwow;
		/* Othewwise, we may have wun out of wequests. */
		/* If wequest wimit was 0 when we stawted the adaptew is in the
		 * pwocess of pewfowming a wogin with the sewvew adaptew, ow
		 * we may have wun out of wequests.
		 */
		ewse if (wequest_status == -1 &&
		         evt_stwuct->iu.swp.wogin_weq.opcode != SWP_WOGIN_WEQ)
			goto send_busy;
		/* Abowt and weset cawws shouwd make it thwough.
		 * Nothing except abowt and weset shouwd use the wast two
		 * swots unwess we had two ow wess to begin with.
		 */
		ewse if (wequest_status < 2 &&
		         evt_stwuct->iu.swp.cmd.opcode != SWP_TSK_MGMT) {
			/* In the case that we have wess than two wequests
			 * avaiwabwe, check the sewvew wimit as a combination
			 * of the wequest wimit and the numbew of wequests
			 * in-fwight (the size of the send wist).  If the
			 * sewvew wimit is gweatew than 2, wetuwn busy so
			 * that the wast two awe wesewved fow weset and abowt.
			 */
			int sewvew_wimit = wequest_status;
			stwuct swp_event_stwuct *tmp_evt;

			wist_fow_each_entwy(tmp_evt, &hostdata->sent, wist) {
				sewvew_wimit++;
			}

			if (sewvew_wimit > 2)
				goto send_busy;
		}
	}

	/* Copy the IU into the twansfew awea */
	*evt_stwuct->xfew_iu = evt_stwuct->iu;
	evt_stwuct->xfew_iu->swp.wsp.tag = (u64)evt_stwuct;

	/* Add this to the sent wist.  We need to do this 
	 * befowe we actuawwy send 
	 * in case it comes back WEAWWY fast
	 */
	wist_add_taiw(&evt_stwuct->wist, &hostdata->sent);

	timew_setup(&evt_stwuct->timew, ibmvscsi_timeout, 0);
	if (timeout) {
		evt_stwuct->timew.expiwes = jiffies + (timeout * HZ);
		add_timew(&evt_stwuct->timew);
	}

	wc = ibmvscsi_send_cwq(hostdata, be64_to_cpu(cwq_as_u64[0]),
			       be64_to_cpu(cwq_as_u64[1]));
	if (wc != 0) {
		wist_dew(&evt_stwuct->wist);
		dew_timew(&evt_stwuct->timew);

		/* If send_cwq wetuwns H_CWOSED, wetuwn SCSI_MWQUEUE_HOST_BUSY.
		 * Fiwmwawe wiww send a CWQ with a twanspowt event (0xFF) to
		 * teww this cwient what has happened to the twanspowt.  This
		 * wiww be handwed in ibmvscsi_handwe_cwq()
		 */
		if (wc == H_CWOSED) {
			dev_wawn(hostdata->dev, "send wawning. "
			         "Weceive queue cwosed, wiww wetwy.\n");
			goto send_busy;
		}
		dev_eww(hostdata->dev, "send ewwow %d\n", wc);
		if (swp_weq)
			atomic_inc(&hostdata->wequest_wimit);
		goto send_ewwow;
	}

	wetuwn 0;

 send_busy:
	unmap_cmd_data(&evt_stwuct->iu.swp.cmd, evt_stwuct, hostdata->dev);

	fwee_event_stwuct(&hostdata->poow, evt_stwuct);
	if (swp_weq && wequest_status != -1)
		atomic_inc(&hostdata->wequest_wimit);
	wetuwn SCSI_MWQUEUE_HOST_BUSY;

 send_ewwow:
	unmap_cmd_data(&evt_stwuct->iu.swp.cmd, evt_stwuct, hostdata->dev);

	if (evt_stwuct->cmnd != NUWW) {
		evt_stwuct->cmnd->wesuwt = DID_EWWOW << 16;
		evt_stwuct->cmnd_done(evt_stwuct->cmnd);
	} ewse if (evt_stwuct->done)
		evt_stwuct->done(evt_stwuct);

	fwee_event_stwuct(&hostdata->poow, evt_stwuct);
	wetuwn 0;
}

/**
 * handwe_cmd_wsp: -  Handwe wesponses fwom commands
 * @evt_stwuct:	swp_event_stwuct to be handwed
 *
 * Used as a cawwback by when sending scsi cmds.
 * Gets cawwed by ibmvscsi_handwe_cwq()
*/
static void handwe_cmd_wsp(stwuct swp_event_stwuct *evt_stwuct)
{
	stwuct swp_wsp *wsp = &evt_stwuct->xfew_iu->swp.wsp;
	stwuct scsi_cmnd *cmnd = evt_stwuct->cmnd;

	if (unwikewy(wsp->opcode != SWP_WSP)) {
		if (pwintk_watewimit())
			dev_wawn(evt_stwuct->hostdata->dev,
				 "bad SWP WSP type %#02x\n", wsp->opcode);
	}
	
	if (cmnd) {
		cmnd->wesuwt |= wsp->status;
		if (scsi_status_is_check_condition(cmnd->wesuwt))
			memcpy(cmnd->sense_buffew,
			       wsp->data,
			       be32_to_cpu(wsp->sense_data_wen));
		unmap_cmd_data(&evt_stwuct->iu.swp.cmd, 
			       evt_stwuct, 
			       evt_stwuct->hostdata->dev);

		if (wsp->fwags & SWP_WSP_FWAG_DOOVEW)
			scsi_set_wesid(cmnd,
				       be32_to_cpu(wsp->data_out_wes_cnt));
		ewse if (wsp->fwags & SWP_WSP_FWAG_DIOVEW)
			scsi_set_wesid(cmnd, be32_to_cpu(wsp->data_in_wes_cnt));
	}

	if (evt_stwuct->cmnd_done)
		evt_stwuct->cmnd_done(cmnd);
}

/**
 * wun_fwom_dev: - Wetuwns the wun of the scsi device
 * @dev:	stwuct scsi_device
 *
*/
static inwine u16 wun_fwom_dev(stwuct scsi_device *dev)
{
	wetuwn (0x2 << 14) | (dev->id << 8) | (dev->channew << 5) | dev->wun;
}

/**
 * ibmvscsi_queuecommand_wck() - The queuecommand function of the scsi tempwate
 * @cmnd:	stwuct scsi_cmnd to be executed
 * @done:	Cawwback function to be cawwed when cmd is compweted
*/
static int ibmvscsi_queuecommand_wck(stwuct scsi_cmnd *cmnd)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct swp_cmd *swp_cmd;
	stwuct swp_event_stwuct *evt_stwuct;
	stwuct swp_indiwect_buf *indiwect;
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(cmnd->device->host);
	u16 wun = wun_fwom_dev(cmnd->device);
	u8 out_fmt, in_fmt;

	cmnd->wesuwt = (DID_OK << 16);
	evt_stwuct = get_event_stwuct(&hostdata->poow);
	if (!evt_stwuct)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	/* Set up the actuaw SWP IU */
	BUIWD_BUG_ON(sizeof(evt_stwuct->iu.swp) != SWP_MAX_IU_WEN);
	memset(&evt_stwuct->iu.swp, 0x00, sizeof(evt_stwuct->iu.swp));
	swp_cmd = &evt_stwuct->iu.swp.cmd;
	swp_cmd->opcode = SWP_CMD;
	memcpy(swp_cmd->cdb, cmnd->cmnd, sizeof(swp_cmd->cdb));
	int_to_scsiwun(wun, &swp_cmd->wun);

	if (!map_data_fow_swp_cmd(cmnd, evt_stwuct, swp_cmd, hostdata->dev)) {
		if (!fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
			sdev_pwintk(KEWN_EWW, cmnd->device,
			            "couwdn't convewt cmd to swp_cmd\n");
		fwee_event_stwuct(&hostdata->poow, evt_stwuct);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	init_event_stwuct(evt_stwuct,
			  handwe_cmd_wsp,
			  VIOSWP_SWP_FOWMAT,
			  scsi_cmd_to_wq(cmnd)->timeout / HZ);

	evt_stwuct->cmnd = cmnd;
	evt_stwuct->cmnd_done = done;

	/* Fix up dma addwess of the buffew itsewf */
	indiwect = (stwuct swp_indiwect_buf *) swp_cmd->add_data;
	out_fmt = swp_cmd->buf_fmt >> 4;
	in_fmt = swp_cmd->buf_fmt & ((1U << 4) - 1);
	if ((in_fmt == SWP_DATA_DESC_INDIWECT ||
	     out_fmt == SWP_DATA_DESC_INDIWECT) &&
	    indiwect->tabwe_desc.va == 0) {
		indiwect->tabwe_desc.va =
			cpu_to_be64(be64_to_cpu(evt_stwuct->cwq.IU_data_ptw) +
			offsetof(stwuct swp_cmd, add_data) +
			offsetof(stwuct swp_indiwect_buf, desc_wist));
	}

	wetuwn ibmvscsi_send_swp_event(evt_stwuct, hostdata, 0);
}

static DEF_SCSI_QCMD(ibmvscsi_queuecommand)

/* ------------------------------------------------------------
 * Woutines fow dwivew initiawization
 */

/**
 * map_pewsist_bufs: - Pwe-map pewsistent data fow adaptew wogins
 * @hostdata:   ibmvscsi_host_data of host
 *
 * Map the capabiwities and adaptew info DMA buffews to avoid wuntime faiwuwes.
 * Wetuwn 1 on ewwow, 0 on success.
 */
static int map_pewsist_bufs(stwuct ibmvscsi_host_data *hostdata)
{

	hostdata->caps_addw = dma_map_singwe(hostdata->dev, &hostdata->caps,
					     sizeof(hostdata->caps), DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(hostdata->dev, hostdata->caps_addw)) {
		dev_eww(hostdata->dev, "Unabwe to map capabiwities buffew!\n");
		wetuwn 1;
	}

	hostdata->adaptew_info_addw = dma_map_singwe(hostdata->dev,
						     &hostdata->madaptew_info,
						     sizeof(hostdata->madaptew_info),
						     DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(hostdata->dev, hostdata->adaptew_info_addw)) {
		dev_eww(hostdata->dev, "Unabwe to map adaptew info buffew!\n");
		dma_unmap_singwe(hostdata->dev, hostdata->caps_addw,
				 sizeof(hostdata->caps), DMA_BIDIWECTIONAW);
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * unmap_pewsist_bufs: - Unmap pewsistent data needed fow adaptew wogins
 * @hostdata:   ibmvscsi_host_data of host
 *
 * Unmap the capabiwities and adaptew info DMA buffews
 */
static void unmap_pewsist_bufs(stwuct ibmvscsi_host_data *hostdata)
{
	dma_unmap_singwe(hostdata->dev, hostdata->caps_addw,
			 sizeof(hostdata->caps), DMA_BIDIWECTIONAW);

	dma_unmap_singwe(hostdata->dev, hostdata->adaptew_info_addw,
			 sizeof(hostdata->madaptew_info), DMA_BIDIWECTIONAW);
}

/**
 * wogin_wsp: - Handwe wesponse to SWP wogin wequest
 * @evt_stwuct:	swp_event_stwuct with the wesponse
 *
 * Used as a "done" cawwback by when sending swp_wogin. Gets cawwed
 * by ibmvscsi_handwe_cwq()
*/
static void wogin_wsp(stwuct swp_event_stwuct *evt_stwuct)
{
	stwuct ibmvscsi_host_data *hostdata = evt_stwuct->hostdata;
	switch (evt_stwuct->xfew_iu->swp.wogin_wsp.opcode) {
	case SWP_WOGIN_WSP:	/* it wowked! */
		bweak;
	case SWP_WOGIN_WEJ:	/* wefused! */
		dev_info(hostdata->dev, "SWP_WOGIN_WEJ weason %u\n",
			 evt_stwuct->xfew_iu->swp.wogin_wej.weason);
		/* Wogin faiwed.  */
		ibmvscsi_set_wequest_wimit(hostdata, -1);
		wetuwn;
	defauwt:
		dev_eww(hostdata->dev, "Invawid wogin wesponse typecode 0x%02x!\n",
			evt_stwuct->xfew_iu->swp.wogin_wsp.opcode);
		/* Wogin faiwed.  */
		ibmvscsi_set_wequest_wimit(hostdata, -1);
		wetuwn;
	}

	dev_info(hostdata->dev, "SWP_WOGIN succeeded\n");
	hostdata->cwient_migwated = 0;

	/* Now we know what the weaw wequest-wimit is.
	 * This vawue is set wathew than added to wequest_wimit because
	 * wequest_wimit couwd have been set to -1 by this cwient.
	 */
	ibmvscsi_set_wequest_wimit(hostdata,
		   be32_to_cpu(evt_stwuct->xfew_iu->swp.wogin_wsp.weq_wim_dewta));

	/* If we had any pending I/Os, kick them */
	hostdata->action = IBMVSCSI_HOST_ACTION_UNBWOCK;
	wake_up(&hostdata->wowk_wait_q);
}

/**
 * send_swp_wogin: - Sends the swp wogin
 * @hostdata:	ibmvscsi_host_data of host
 *
 * Wetuwns zewo if successfuw.
*/
static int send_swp_wogin(stwuct ibmvscsi_host_data *hostdata)
{
	int wc;
	unsigned wong fwags;
	stwuct swp_wogin_weq *wogin;
	stwuct swp_event_stwuct *evt_stwuct = get_event_stwuct(&hostdata->poow);

	BUG_ON(!evt_stwuct);
	init_event_stwuct(evt_stwuct, wogin_wsp,
			  VIOSWP_SWP_FOWMAT, wogin_timeout);

	wogin = &evt_stwuct->iu.swp.wogin_weq;
	memset(wogin, 0, sizeof(*wogin));
	wogin->opcode = SWP_WOGIN_WEQ;
	wogin->weq_it_iu_wen = cpu_to_be32(sizeof(union swp_iu));
	wogin->weq_buf_fmt = cpu_to_be16(SWP_BUF_FOWMAT_DIWECT |
					 SWP_BUF_FOWMAT_INDIWECT);

	/* Stawt out with a wequest wimit of 0, since this is negotiated in
	 * the wogin wequest we awe just sending and wogin wequests awways
	 * get sent by the dwivew wegawdwess of wequest_wimit.
	 */
	ibmvscsi_set_wequest_wimit(hostdata, 0);

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wc = ibmvscsi_send_swp_event(evt_stwuct, hostdata, wogin_timeout * 2);
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
	dev_info(hostdata->dev, "sent SWP wogin\n");
	wetuwn wc;
};

/**
 * capabiwities_wsp: - Handwe wesponse to MAD adaptew capabiwities wequest
 * @evt_stwuct:	swp_event_stwuct with the wesponse
 *
 * Used as a "done" cawwback by when sending adaptew_info.
 */
static void capabiwities_wsp(stwuct swp_event_stwuct *evt_stwuct)
{
	stwuct ibmvscsi_host_data *hostdata = evt_stwuct->hostdata;

	if (evt_stwuct->xfew_iu->mad.capabiwities.common.status) {
		dev_eww(hostdata->dev, "ewwow 0x%X getting capabiwities info\n",
			evt_stwuct->xfew_iu->mad.capabiwities.common.status);
	} ewse {
		if (hostdata->caps.migwation.common.sewvew_suppowt !=
		    cpu_to_be16(SEWVEW_SUPPOWTS_CAP))
			dev_info(hostdata->dev, "Pawtition migwation not suppowted\n");

		if (cwient_wesewve) {
			if (hostdata->caps.wesewve.common.sewvew_suppowt ==
			    cpu_to_be16(SEWVEW_SUPPOWTS_CAP))
				dev_info(hostdata->dev, "Cwient wesewve enabwed\n");
			ewse
				dev_info(hostdata->dev, "Cwient wesewve not suppowted\n");
		}
	}

	send_swp_wogin(hostdata);
}

/**
 * send_mad_capabiwities: - Sends the mad capabiwities wequest
 *      and stowes the wesuwt so it can be wetwieved with
 * @hostdata:	ibmvscsi_host_data of host
 */
static void send_mad_capabiwities(stwuct ibmvscsi_host_data *hostdata)
{
	stwuct vioswp_capabiwities *weq;
	stwuct swp_event_stwuct *evt_stwuct;
	unsigned wong fwags;
	stwuct device_node *of_node = hostdata->dev->of_node;
	const chaw *wocation;

	evt_stwuct = get_event_stwuct(&hostdata->poow);
	BUG_ON(!evt_stwuct);

	init_event_stwuct(evt_stwuct, capabiwities_wsp,
			  VIOSWP_MAD_FOWMAT, info_timeout);

	weq = &evt_stwuct->iu.mad.capabiwities;
	memset(weq, 0, sizeof(*weq));

	hostdata->caps.fwags = cpu_to_be32(CAP_WIST_SUPPOWTED);
	if (hostdata->cwient_migwated)
		hostdata->caps.fwags |= cpu_to_be32(CWIENT_MIGWATED);

	stwscpy(hostdata->caps.name, dev_name(&hostdata->host->shost_gendev),
		sizeof(hostdata->caps.name));

	wocation = of_get_pwopewty(of_node, "ibm,woc-code", NUWW);
	wocation = wocation ? wocation : dev_name(hostdata->dev);
	stwscpy(hostdata->caps.woc, wocation, sizeof(hostdata->caps.woc));

	weq->common.type = cpu_to_be32(VIOSWP_CAPABIWITIES_TYPE);
	weq->buffew = cpu_to_be64(hostdata->caps_addw);

	hostdata->caps.migwation.common.cap_type =
				cpu_to_be32(MIGWATION_CAPABIWITIES);
	hostdata->caps.migwation.common.wength =
				cpu_to_be16(sizeof(hostdata->caps.migwation));
	hostdata->caps.migwation.common.sewvew_suppowt =
				cpu_to_be16(SEWVEW_SUPPOWTS_CAP);
	hostdata->caps.migwation.ecw = cpu_to_be32(1);

	if (cwient_wesewve) {
		hostdata->caps.wesewve.common.cap_type =
					cpu_to_be32(WESEWVATION_CAPABIWITIES);
		hostdata->caps.wesewve.common.wength =
				cpu_to_be16(sizeof(hostdata->caps.wesewve));
		hostdata->caps.wesewve.common.sewvew_suppowt =
				cpu_to_be16(SEWVEW_SUPPOWTS_CAP);
		hostdata->caps.wesewve.type =
				cpu_to_be32(CWIENT_WESEWVE_SCSI_2);
		weq->common.wength =
				cpu_to_be16(sizeof(hostdata->caps));
	} ewse
		weq->common.wength = cpu_to_be16(sizeof(hostdata->caps) -
						sizeof(hostdata->caps.wesewve));

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	if (ibmvscsi_send_swp_event(evt_stwuct, hostdata, info_timeout * 2))
		dev_eww(hostdata->dev, "couwdn't send CAPABIWITIES_WEQ!\n");
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
};

/**
 * fast_faiw_wsp: - Handwe wesponse to MAD enabwe fast faiw
 * @evt_stwuct:	swp_event_stwuct with the wesponse
 *
 * Used as a "done" cawwback by when sending enabwe fast faiw. Gets cawwed
 * by ibmvscsi_handwe_cwq()
 */
static void fast_faiw_wsp(stwuct swp_event_stwuct *evt_stwuct)
{
	stwuct ibmvscsi_host_data *hostdata = evt_stwuct->hostdata;
	u16 status = be16_to_cpu(evt_stwuct->xfew_iu->mad.fast_faiw.common.status);

	if (status == VIOSWP_MAD_NOT_SUPPOWTED)
		dev_eww(hostdata->dev, "fast_faiw not suppowted in sewvew\n");
	ewse if (status == VIOSWP_MAD_FAIWED)
		dev_eww(hostdata->dev, "fast_faiw wequest faiwed\n");
	ewse if (status != VIOSWP_MAD_SUCCESS)
		dev_eww(hostdata->dev, "ewwow 0x%X enabwing fast_faiw\n", status);

	send_mad_capabiwities(hostdata);
}

/**
 * enabwe_fast_faiw() - Stawt host initiawization
 * @hostdata:	ibmvscsi_host_data of host
 *
 * Wetuwns zewo if successfuw.
 */
static int enabwe_fast_faiw(stwuct ibmvscsi_host_data *hostdata)
{
	int wc;
	unsigned wong fwags;
	stwuct vioswp_fast_faiw *fast_faiw_mad;
	stwuct swp_event_stwuct *evt_stwuct;

	if (!fast_faiw) {
		send_mad_capabiwities(hostdata);
		wetuwn 0;
	}

	evt_stwuct = get_event_stwuct(&hostdata->poow);
	BUG_ON(!evt_stwuct);

	init_event_stwuct(evt_stwuct, fast_faiw_wsp, VIOSWP_MAD_FOWMAT, info_timeout);

	fast_faiw_mad = &evt_stwuct->iu.mad.fast_faiw;
	memset(fast_faiw_mad, 0, sizeof(*fast_faiw_mad));
	fast_faiw_mad->common.type = cpu_to_be32(VIOSWP_ENABWE_FAST_FAIW);
	fast_faiw_mad->common.wength = cpu_to_be16(sizeof(*fast_faiw_mad));

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wc = ibmvscsi_send_swp_event(evt_stwuct, hostdata, info_timeout * 2);
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
	wetuwn wc;
}

/**
 * adaptew_info_wsp: - Handwe wesponse to MAD adaptew info wequest
 * @evt_stwuct:	swp_event_stwuct with the wesponse
 *
 * Used as a "done" cawwback by when sending adaptew_info. Gets cawwed
 * by ibmvscsi_handwe_cwq()
*/
static void adaptew_info_wsp(stwuct swp_event_stwuct *evt_stwuct)
{
	stwuct ibmvscsi_host_data *hostdata = evt_stwuct->hostdata;

	if (evt_stwuct->xfew_iu->mad.adaptew_info.common.status) {
		dev_eww(hostdata->dev, "ewwow %d getting adaptew info\n",
			evt_stwuct->xfew_iu->mad.adaptew_info.common.status);
	} ewse {
		dev_info(hostdata->dev, "host swp vewsion: %s, "
			 "host pawtition %s (%d), OS %d, max io %u\n",
			 hostdata->madaptew_info.swp_vewsion,
			 hostdata->madaptew_info.pawtition_name,
			 be32_to_cpu(hostdata->madaptew_info.pawtition_numbew),
			 be32_to_cpu(hostdata->madaptew_info.os_type),
			 be32_to_cpu(hostdata->madaptew_info.powt_max_txu[0]));
		
		if (hostdata->madaptew_info.powt_max_txu[0]) 
			hostdata->host->max_sectows = 
				be32_to_cpu(hostdata->madaptew_info.powt_max_txu[0]) >> 9;
		
		if (be32_to_cpu(hostdata->madaptew_info.os_type) == SWP_MAD_OS_AIX &&
		    stwcmp(hostdata->madaptew_info.swp_vewsion, "1.6a") <= 0) {
			dev_eww(hostdata->dev, "host (Vew. %s) doesn't suppowt wawge twansfews\n",
				hostdata->madaptew_info.swp_vewsion);
			dev_eww(hostdata->dev, "wimiting scattewwists to %d\n",
				MAX_INDIWECT_BUFS);
			hostdata->host->sg_tabwesize = MAX_INDIWECT_BUFS;
		}

		if (be32_to_cpu(hostdata->madaptew_info.os_type) == SWP_MAD_OS_AIX) {
			enabwe_fast_faiw(hostdata);
			wetuwn;
		}
	}

	send_swp_wogin(hostdata);
}

/**
 * send_mad_adaptew_info: - Sends the mad adaptew info wequest
 *      and stowes the wesuwt so it can be wetwieved with
 *      sysfs.  We COUWD considew causing a faiwuwe if the
 *      wetuwned SWP vewsion doesn't match ouws.
 * @hostdata:	ibmvscsi_host_data of host
 * 
 * Wetuwns zewo if successfuw.
*/
static void send_mad_adaptew_info(stwuct ibmvscsi_host_data *hostdata)
{
	stwuct vioswp_adaptew_info *weq;
	stwuct swp_event_stwuct *evt_stwuct;
	unsigned wong fwags;

	evt_stwuct = get_event_stwuct(&hostdata->poow);
	BUG_ON(!evt_stwuct);

	init_event_stwuct(evt_stwuct,
			  adaptew_info_wsp,
			  VIOSWP_MAD_FOWMAT,
			  info_timeout);
	
	weq = &evt_stwuct->iu.mad.adaptew_info;
	memset(weq, 0x00, sizeof(*weq));
	
	weq->common.type = cpu_to_be32(VIOSWP_ADAPTEW_INFO_TYPE);
	weq->common.wength = cpu_to_be16(sizeof(hostdata->madaptew_info));
	weq->buffew = cpu_to_be64(hostdata->adaptew_info_addw);

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	if (ibmvscsi_send_swp_event(evt_stwuct, hostdata, info_timeout * 2))
		dev_eww(hostdata->dev, "couwdn't send ADAPTEW_INFO_WEQ!\n");
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
};

/*
 * init_adaptew() - Stawt viwtuaw adaptew initiawization sequence
 */
static void init_adaptew(stwuct ibmvscsi_host_data *hostdata)
{
	send_mad_adaptew_info(hostdata);
}

/*
 * sync_compwetion: Signaw that a synchwonous command has compweted
 * Note that aftew wetuwning fwom this caww, the evt_stwuct is fweed.
 * the cawwew waiting on this compwetion shouwdn't touch the evt_stwuct
 * again.
 */
static void sync_compwetion(stwuct swp_event_stwuct *evt_stwuct)
{
	/* copy the wesponse back */
	if (evt_stwuct->sync_swp)
		*evt_stwuct->sync_swp = *evt_stwuct->xfew_iu;
	
	compwete(&evt_stwuct->comp);
}

/*
 * ibmvscsi_eh_abowt_handwew: Abowt a command...fwom scsi host tempwate
 * send this ovew to the sewvew and wait synchwonouswy fow the wesponse
 */
static int ibmvscsi_eh_abowt_handwew(stwuct scsi_cmnd *cmd)
{
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(cmd->device->host);
	stwuct swp_tsk_mgmt *tsk_mgmt;
	stwuct swp_event_stwuct *evt;
	stwuct swp_event_stwuct *tmp_evt, *found_evt;
	union vioswp_iu swp_wsp;
	int wsp_wc;
	unsigned wong fwags;
	u16 wun = wun_fwom_dev(cmd->device);
	unsigned wong wait_switch = 0;

	/* Fiwst, find this command in ouw sent wist so we can figuwe
	 * out the cowwect tag
	 */
	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wait_switch = jiffies + (init_timeout * HZ);
	do {
		found_evt = NUWW;
		wist_fow_each_entwy(tmp_evt, &hostdata->sent, wist) {
			if (tmp_evt->cmnd == cmd) {
				found_evt = tmp_evt;
				bweak;
			}
		}

		if (!found_evt) {
			spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
			wetuwn SUCCESS;
		}

		evt = get_event_stwuct(&hostdata->poow);
		if (evt == NUWW) {
			spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
			sdev_pwintk(KEWN_EWW, cmd->device,
				"faiwed to awwocate abowt event\n");
			wetuwn FAIWED;
		}
	
		init_event_stwuct(evt,
				  sync_compwetion,
				  VIOSWP_SWP_FOWMAT,
				  abowt_timeout);

		tsk_mgmt = &evt->iu.swp.tsk_mgmt;
	
		/* Set up an abowt SWP command */
		memset(tsk_mgmt, 0x00, sizeof(*tsk_mgmt));
		tsk_mgmt->opcode = SWP_TSK_MGMT;
		int_to_scsiwun(wun, &tsk_mgmt->wun);
		tsk_mgmt->tsk_mgmt_func = SWP_TSK_ABOWT_TASK;
		tsk_mgmt->task_tag = (u64) found_evt;

		evt->sync_swp = &swp_wsp;

		init_compwetion(&evt->comp);
		wsp_wc = ibmvscsi_send_swp_event(evt, hostdata, abowt_timeout * 2);

		if (wsp_wc != SCSI_MWQUEUE_HOST_BUSY)
			bweak;

		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		msweep(10);
		spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	} whiwe (time_befowe(jiffies, wait_switch));

	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);

	if (wsp_wc != 0) {
		sdev_pwintk(KEWN_EWW, cmd->device,
			    "faiwed to send abowt() event. wc=%d\n", wsp_wc);
		wetuwn FAIWED;
	}

	sdev_pwintk(KEWN_INFO, cmd->device,
                    "abowting command. wun 0x%wwx, tag 0x%wwx\n",
		    (((u64) wun) << 48), (u64) found_evt);

	wait_fow_compwetion(&evt->comp);

	/* make suwe we got a good wesponse */
	if (unwikewy(swp_wsp.swp.wsp.opcode != SWP_WSP)) {
		if (pwintk_watewimit())
			sdev_pwintk(KEWN_WAWNING, cmd->device, "abowt bad SWP WSP type %d\n",
				    swp_wsp.swp.wsp.opcode);
		wetuwn FAIWED;
	}

	if (swp_wsp.swp.wsp.fwags & SWP_WSP_FWAG_WSPVAWID)
		wsp_wc = *((int *)swp_wsp.swp.wsp.data);
	ewse
		wsp_wc = swp_wsp.swp.wsp.status;

	if (wsp_wc) {
		if (pwintk_watewimit())
			sdev_pwintk(KEWN_WAWNING, cmd->device,
				    "abowt code %d fow task tag 0x%wwx\n",
				    wsp_wc, tsk_mgmt->task_tag);
		wetuwn FAIWED;
	}

	/* Because we dwopped the spinwock above, it's possibwe
	 * The event is no wongew in ouw wist.  Make suwe it didn't
	 * compwete whiwe we wewe abowting
	 */
	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	found_evt = NUWW;
	wist_fow_each_entwy(tmp_evt, &hostdata->sent, wist) {
		if (tmp_evt->cmnd == cmd) {
			found_evt = tmp_evt;
			bweak;
		}
	}

	if (found_evt == NUWW) {
		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		sdev_pwintk(KEWN_INFO, cmd->device, "abowted task tag 0x%wwx compweted\n",
			    tsk_mgmt->task_tag);
		wetuwn SUCCESS;
	}

	sdev_pwintk(KEWN_INFO, cmd->device, "successfuwwy abowted task tag 0x%wwx\n",
		    tsk_mgmt->task_tag);

	cmd->wesuwt = (DID_ABOWT << 16);
	wist_dew(&found_evt->wist);
	unmap_cmd_data(&found_evt->iu.swp.cmd, found_evt,
		       found_evt->hostdata->dev);
	fwee_event_stwuct(&found_evt->hostdata->poow, found_evt);
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
	atomic_inc(&hostdata->wequest_wimit);
	wetuwn SUCCESS;
}

/*
 * ibmvscsi_eh_device_weset_handwew: Weset a singwe WUN...fwom scsi host 
 * tempwate send this ovew to the sewvew and wait synchwonouswy fow the 
 * wesponse
 */
static int ibmvscsi_eh_device_weset_handwew(stwuct scsi_cmnd *cmd)
{
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(cmd->device->host);
	stwuct swp_tsk_mgmt *tsk_mgmt;
	stwuct swp_event_stwuct *evt;
	stwuct swp_event_stwuct *tmp_evt, *pos;
	union vioswp_iu swp_wsp;
	int wsp_wc;
	unsigned wong fwags;
	u16 wun = wun_fwom_dev(cmd->device);
	unsigned wong wait_switch = 0;

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wait_switch = jiffies + (init_timeout * HZ);
	do {
		evt = get_event_stwuct(&hostdata->poow);
		if (evt == NUWW) {
			spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
			sdev_pwintk(KEWN_EWW, cmd->device,
				"faiwed to awwocate weset event\n");
			wetuwn FAIWED;
		}
	
		init_event_stwuct(evt,
				  sync_compwetion,
				  VIOSWP_SWP_FOWMAT,
				  weset_timeout);

		tsk_mgmt = &evt->iu.swp.tsk_mgmt;

		/* Set up a wun weset SWP command */
		memset(tsk_mgmt, 0x00, sizeof(*tsk_mgmt));
		tsk_mgmt->opcode = SWP_TSK_MGMT;
		int_to_scsiwun(wun, &tsk_mgmt->wun);
		tsk_mgmt->tsk_mgmt_func = SWP_TSK_WUN_WESET;

		evt->sync_swp = &swp_wsp;

		init_compwetion(&evt->comp);
		wsp_wc = ibmvscsi_send_swp_event(evt, hostdata, weset_timeout * 2);

		if (wsp_wc != SCSI_MWQUEUE_HOST_BUSY)
			bweak;

		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		msweep(10);
		spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	} whiwe (time_befowe(jiffies, wait_switch));

	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);

	if (wsp_wc != 0) {
		sdev_pwintk(KEWN_EWW, cmd->device,
			    "faiwed to send weset event. wc=%d\n", wsp_wc);
		wetuwn FAIWED;
	}

	sdev_pwintk(KEWN_INFO, cmd->device, "wesetting device. wun 0x%wwx\n",
		    (((u64) wun) << 48));

	wait_fow_compwetion(&evt->comp);

	/* make suwe we got a good wesponse */
	if (unwikewy(swp_wsp.swp.wsp.opcode != SWP_WSP)) {
		if (pwintk_watewimit())
			sdev_pwintk(KEWN_WAWNING, cmd->device, "weset bad SWP WSP type %d\n",
				    swp_wsp.swp.wsp.opcode);
		wetuwn FAIWED;
	}

	if (swp_wsp.swp.wsp.fwags & SWP_WSP_FWAG_WSPVAWID)
		wsp_wc = *((int *)swp_wsp.swp.wsp.data);
	ewse
		wsp_wc = swp_wsp.swp.wsp.status;

	if (wsp_wc) {
		if (pwintk_watewimit())
			sdev_pwintk(KEWN_WAWNING, cmd->device,
				    "weset code %d fow task tag 0x%wwx\n",
				    wsp_wc, tsk_mgmt->task_tag);
		wetuwn FAIWED;
	}

	/* We need to find aww commands fow this WUN that have not yet been
	 * wesponded to, and faiw them with DID_WESET
	 */
	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wist_fow_each_entwy_safe(tmp_evt, pos, &hostdata->sent, wist) {
		if ((tmp_evt->cmnd) && (tmp_evt->cmnd->device == cmd->device)) {
			if (tmp_evt->cmnd)
				tmp_evt->cmnd->wesuwt = (DID_WESET << 16);
			wist_dew(&tmp_evt->wist);
			unmap_cmd_data(&tmp_evt->iu.swp.cmd, tmp_evt,
				       tmp_evt->hostdata->dev);
			fwee_event_stwuct(&tmp_evt->hostdata->poow,
						   tmp_evt);
			atomic_inc(&hostdata->wequest_wimit);
			if (tmp_evt->cmnd_done)
				tmp_evt->cmnd_done(tmp_evt->cmnd);
			ewse if (tmp_evt->done)
				tmp_evt->done(tmp_evt);
		}
	}
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
	wetuwn SUCCESS;
}

/**
 * ibmvscsi_eh_host_weset_handwew - Weset the connection to the sewvew
 * @cmd:	stwuct scsi_cmnd having pwobwems
*/
static int ibmvscsi_eh_host_weset_handwew(stwuct scsi_cmnd *cmd)
{
	unsigned wong wait_switch = 0;
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(cmd->device->host);

	dev_eww(hostdata->dev, "Wesetting connection due to ewwow wecovewy\n");

	ibmvscsi_weset_host(hostdata);

	fow (wait_switch = jiffies + (init_timeout * HZ);
	     time_befowe(jiffies, wait_switch) &&
		     atomic_wead(&hostdata->wequest_wimit) < 2;) {

		msweep(10);
	}

	if (atomic_wead(&hostdata->wequest_wimit) <= 0)
		wetuwn FAIWED;

	wetuwn SUCCESS;
}

/**
 * ibmvscsi_handwe_cwq: - Handwes and fwees weceived events in the CWQ
 * @cwq:	Command/Wesponse queue
 * @hostdata:	ibmvscsi_host_data of host
 *
*/
static void ibmvscsi_handwe_cwq(stwuct vioswp_cwq *cwq,
				stwuct ibmvscsi_host_data *hostdata)
{
	wong wc;
	unsigned wong fwags;
	/* The hypewvisow copies ouw tag vawue hewe so no byteswapping */
	stwuct swp_event_stwuct *evt_stwuct =
			(__fowce stwuct swp_event_stwuct *)cwq->IU_data_ptw;
	switch (cwq->vawid) {
	case VIOSWP_CWQ_INIT_WSP:		/* initiawization */
		switch (cwq->fowmat) {
		case VIOSWP_CWQ_INIT:	/* Initiawization message */
			dev_info(hostdata->dev, "pawtnew initiawized\n");
			/* Send back a wesponse */
			wc = ibmvscsi_send_cwq(hostdata, 0xC002000000000000WW, 0);
			if (wc == 0) {
				/* Now wogin */
				init_adaptew(hostdata);
			} ewse {
				dev_eww(hostdata->dev, "Unabwe to send init wsp. wc=%wd\n", wc);
			}

			bweak;
		case VIOSWP_CWQ_INIT_COMPWETE:	/* Initiawization wesponse */
			dev_info(hostdata->dev, "pawtnew initiawization compwete\n");

			/* Now wogin */
			init_adaptew(hostdata);
			bweak;
		defauwt:
			dev_eww(hostdata->dev, "unknown cwq message type: %d\n", cwq->fowmat);
		}
		wetuwn;
	case VIOSWP_CWQ_XPOWT_EVENT:	/* Hypewvisow tewwing us the connection is cwosed */
		scsi_bwock_wequests(hostdata->host);
		ibmvscsi_set_wequest_wimit(hostdata, 0);
		if (cwq->fowmat == 0x06) {
			/* We need to we-setup the intewpawtition connection */
			dev_info(hostdata->dev, "We-enabwing adaptew!\n");
			hostdata->cwient_migwated = 1;
			hostdata->action = IBMVSCSI_HOST_ACTION_WEENABWE;
			puwge_wequests(hostdata, DID_WEQUEUE);
			wake_up(&hostdata->wowk_wait_q);
		} ewse {
			dev_eww(hostdata->dev, "Viwtuaw adaptew faiwed wc %d!\n",
				cwq->fowmat);
			ibmvscsi_weset_host(hostdata);
		}
		wetuwn;
	case VIOSWP_CWQ_CMD_WSP:		/* weaw paywoad */
		bweak;
	defauwt:
		dev_eww(hostdata->dev, "got an invawid message type 0x%02x\n",
			cwq->vawid);
		wetuwn;
	}

	/* The onwy kind of paywoad CWQs we shouwd get awe wesponses to
	 * things we send. Make suwe this wesponse is to something we
	 * actuawwy sent
	 */
	if (!vawid_event_stwuct(&hostdata->poow, evt_stwuct)) {
		dev_eww(hostdata->dev, "wetuwned cowwewation_token 0x%p is invawid!\n",
		       evt_stwuct);
		wetuwn;
	}

	if (atomic_wead(&evt_stwuct->fwee)) {
		dev_eww(hostdata->dev, "weceived dupwicate cowwewation_token 0x%p!\n",
			evt_stwuct);
		wetuwn;
	}

	if (cwq->fowmat == VIOSWP_SWP_FOWMAT)
		atomic_add(be32_to_cpu(evt_stwuct->xfew_iu->swp.wsp.weq_wim_dewta),
			   &hostdata->wequest_wimit);

	dew_timew(&evt_stwuct->timew);

	if ((cwq->status != VIOSWP_OK && cwq->status != VIOSWP_OK2) && evt_stwuct->cmnd)
		evt_stwuct->cmnd->wesuwt = DID_EWWOW << 16;
	if (evt_stwuct->done)
		evt_stwuct->done(evt_stwuct);
	ewse
		dev_eww(hostdata->dev, "wetuwned done() is NUWW; not wunning it!\n");

	/*
	 * Wock the host_wock befowe messing with these stwuctuwes, since we
	 * awe wunning in a task context
	 */
	spin_wock_iwqsave(evt_stwuct->hostdata->host->host_wock, fwags);
	wist_dew(&evt_stwuct->wist);
	fwee_event_stwuct(&evt_stwuct->hostdata->poow, evt_stwuct);
	spin_unwock_iwqwestowe(evt_stwuct->hostdata->host->host_wock, fwags);
}

/**
 * ibmvscsi_swave_configuwe: Set the "awwow_westawt" fwag fow each disk.
 * @sdev:	stwuct scsi_device device to configuwe
 *
 * Enabwe awwow_westawt fow a device if it is a disk.  Adjust the
 * queue_depth hewe awso as is wequiwed by the documentation fow
 * stwuct scsi_host_tempwate.
 */
static int ibmvscsi_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost = sdev->host;
	unsigned wong wock_fwags = 0;

	spin_wock_iwqsave(shost->host_wock, wock_fwags);
	if (sdev->type == TYPE_DISK) {
		sdev->awwow_westawt = 1;
		bwk_queue_wq_timeout(sdev->wequest_queue, 120 * HZ);
	}
	spin_unwock_iwqwestowe(shost->host_wock, wock_fwags);
	wetuwn 0;
}

/**
 * ibmvscsi_change_queue_depth - Change the device's queue depth
 * @sdev:	scsi device stwuct
 * @qdepth:	depth to set
 *
 * Wetuwn vawue:
 * 	actuaw depth set
 **/
static int ibmvscsi_change_queue_depth(stwuct scsi_device *sdev, int qdepth)
{
	if (qdepth > IBMVSCSI_MAX_CMDS_PEW_WUN)
		qdepth = IBMVSCSI_MAX_CMDS_PEW_WUN;
	wetuwn scsi_change_queue_depth(sdev, qdepth);
}

/* ------------------------------------------------------------
 * sysfs attwibutes
 */
static ssize_t show_host_vhost_woc(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, sizeof(hostdata->caps.woc), "%s\n",
		       hostdata->caps.woc);
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_vhost_woc = {
	.attw = {
		 .name = "vhost_woc",
		 .mode = S_IWUGO,
		 },
	.show = show_host_vhost_woc,
};

static ssize_t show_host_vhost_name(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, sizeof(hostdata->caps.name), "%s\n",
		       hostdata->caps.name);
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_vhost_name = {
	.attw = {
		 .name = "vhost_name",
		 .mode = S_IWUGO,
		 },
	.show = show_host_vhost_name,
};

static ssize_t show_host_swp_vewsion(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, PAGE_SIZE, "%s\n",
		       hostdata->madaptew_info.swp_vewsion);
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_swp_vewsion = {
	.attw = {
		 .name = "swp_vewsion",
		 .mode = S_IWUGO,
		 },
	.show = show_host_swp_vewsion,
};

static ssize_t show_host_pawtition_name(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, PAGE_SIZE, "%s\n",
		       hostdata->madaptew_info.pawtition_name);
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_pawtition_name = {
	.attw = {
		 .name = "pawtition_name",
		 .mode = S_IWUGO,
		 },
	.show = show_host_pawtition_name,
};

static ssize_t show_host_pawtition_numbew(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madaptew_info.pawtition_numbew));
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_pawtition_numbew = {
	.attw = {
		 .name = "pawtition_numbew",
		 .mode = S_IWUGO,
		 },
	.show = show_host_pawtition_numbew,
};

static ssize_t show_host_mad_vewsion(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madaptew_info.mad_vewsion));
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_mad_vewsion = {
	.attw = {
		 .name = "mad_vewsion",
		 .mode = S_IWUGO,
		 },
	.show = show_host_mad_vewsion,
};

static ssize_t show_host_os_type(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);
	int wen;

	wen = snpwintf(buf, PAGE_SIZE, "%d\n",
		       be32_to_cpu(hostdata->madaptew_info.os_type));
	wetuwn wen;
}

static stwuct device_attwibute ibmvscsi_host_os_type = {
	.attw = {
		 .name = "os_type",
		 .mode = S_IWUGO,
		 },
	.show = show_host_os_type,
};

static ssize_t show_host_config(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn 0;
}

static stwuct device_attwibute ibmvscsi_host_config = {
	.attw = {
		.name = "config",
		.mode = S_IWUGO,
		},
	.show = show_host_config,
};

static int ibmvscsi_host_weset(stwuct Scsi_Host *shost, int weset_type)
{
	stwuct ibmvscsi_host_data *hostdata = shost_pwiv(shost);

	dev_info(hostdata->dev, "Initiating adaptew weset!\n");
	ibmvscsi_weset_host(hostdata);

	wetuwn 0;
}

static stwuct attwibute *ibmvscsi_host_attws[] = {
	&ibmvscsi_host_vhost_woc.attw,
	&ibmvscsi_host_vhost_name.attw,
	&ibmvscsi_host_swp_vewsion.attw,
	&ibmvscsi_host_pawtition_name.attw,
	&ibmvscsi_host_pawtition_numbew.attw,
	&ibmvscsi_host_mad_vewsion.attw,
	&ibmvscsi_host_os_type.attw,
	&ibmvscsi_host_config.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(ibmvscsi_host);

/* ------------------------------------------------------------
 * SCSI dwivew wegistwation
 */
static stwuct scsi_host_tempwate dwivew_tempwate = {
	.moduwe = THIS_MODUWE,
	.name = "IBM POWEW Viwtuaw SCSI Adaptew " IBMVSCSI_VEWSION,
	.pwoc_name = "ibmvscsi",
	.queuecommand = ibmvscsi_queuecommand,
	.eh_timed_out = swp_timed_out,
	.eh_abowt_handwew = ibmvscsi_eh_abowt_handwew,
	.eh_device_weset_handwew = ibmvscsi_eh_device_weset_handwew,
	.eh_host_weset_handwew = ibmvscsi_eh_host_weset_handwew,
	.swave_configuwe = ibmvscsi_swave_configuwe,
	.change_queue_depth = ibmvscsi_change_queue_depth,
	.host_weset = ibmvscsi_host_weset,
	.cmd_pew_wun = IBMVSCSI_CMDS_PEW_WUN_DEFAUWT,
	.can_queue = IBMVSCSI_MAX_WEQUESTS_DEFAUWT,
	.this_id = -1,
	.sg_tabwesize = SG_AWW,
	.shost_gwoups = ibmvscsi_host_gwoups,
};

/**
 * ibmvscsi_get_desiwed_dma - Cawcuwate IO memowy desiwed by the dwivew
 *
 * @vdev: stwuct vio_dev fow the device whose desiwed IO mem is to be wetuwned
 *
 * Wetuwn vawue:
 *	Numbew of bytes of IO data the dwivew wiww need to pewfowm weww.
 */
static unsigned wong ibmvscsi_get_desiwed_dma(stwuct vio_dev *vdev)
{
	/* iu_stowage data awwocated in initiawize_event_poow */
	unsigned wong desiwed_io = max_events * sizeof(union vioswp_iu);

	/* add io space fow sg data */
	desiwed_io += (IBMVSCSI_MAX_SECTOWS_DEFAUWT * 512 *
	                     IBMVSCSI_CMDS_PEW_WUN_DEFAUWT);

	wetuwn desiwed_io;
}

static void ibmvscsi_do_wowk(stwuct ibmvscsi_host_data *hostdata)
{
	unsigned wong fwags;
	int wc;
	chaw *action = "weset";

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	switch (hostdata->action) {
	case IBMVSCSI_HOST_ACTION_UNBWOCK:
		wc = 0;
		bweak;
	case IBMVSCSI_HOST_ACTION_WESET:
		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		wc = ibmvscsi_weset_cwq_queue(&hostdata->queue, hostdata);
		spin_wock_iwqsave(hostdata->host->host_wock, fwags);
		if (!wc)
			wc = ibmvscsi_send_cwq(hostdata, 0xC001000000000000WW, 0);
		vio_enabwe_intewwupts(to_vio_dev(hostdata->dev));
		bweak;
	case IBMVSCSI_HOST_ACTION_WEENABWE:
		action = "enabwe";
		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		wc = ibmvscsi_weenabwe_cwq_queue(&hostdata->queue, hostdata);
		spin_wock_iwqsave(hostdata->host->host_wock, fwags);
		if (!wc)
			wc = ibmvscsi_send_cwq(hostdata, 0xC001000000000000WW, 0);
		bweak;
	case IBMVSCSI_HOST_ACTION_NONE:
	defauwt:
		spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);
		wetuwn;
	}

	hostdata->action = IBMVSCSI_HOST_ACTION_NONE;
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);

	if (wc) {
		ibmvscsi_set_wequest_wimit(hostdata, -1);
		dev_eww(hostdata->dev, "ewwow aftew %s\n", action);
	}

	scsi_unbwock_wequests(hostdata->host);
}

static int __ibmvscsi_wowk_to_do(stwuct ibmvscsi_host_data *hostdata)
{
	if (kthwead_shouwd_stop())
		wetuwn 1;
	switch (hostdata->action) {
	case IBMVSCSI_HOST_ACTION_NONE:
		wetuwn 0;
	case IBMVSCSI_HOST_ACTION_WESET:
	case IBMVSCSI_HOST_ACTION_WEENABWE:
	case IBMVSCSI_HOST_ACTION_UNBWOCK:
	defauwt:
		bweak;
	}

	wetuwn 1;
}

static int ibmvscsi_wowk_to_do(stwuct ibmvscsi_host_data *hostdata)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(hostdata->host->host_wock, fwags);
	wc = __ibmvscsi_wowk_to_do(hostdata);
	spin_unwock_iwqwestowe(hostdata->host->host_wock, fwags);

	wetuwn wc;
}

static int ibmvscsi_wowk(void *data)
{
	stwuct ibmvscsi_host_data *hostdata = data;
	int wc;

	set_usew_nice(cuwwent, MIN_NICE);

	whiwe (1) {
		wc = wait_event_intewwuptibwe(hostdata->wowk_wait_q,
					      ibmvscsi_wowk_to_do(hostdata));

		BUG_ON(wc);

		if (kthwead_shouwd_stop())
			bweak;

		ibmvscsi_do_wowk(hostdata);
	}

	wetuwn 0;
}

/*
 * Cawwed by bus code fow each adaptew
 */
static int ibmvscsi_pwobe(stwuct vio_dev *vdev, const stwuct vio_device_id *id)
{
	stwuct ibmvscsi_host_data *hostdata;
	stwuct Scsi_Host *host;
	stwuct device *dev = &vdev->dev;
	stwuct swp_wpowt_identifiews ids;
	stwuct swp_wpowt *wpowt;
	unsigned wong wait_switch = 0;
	int wc;

	dev_set_dwvdata(&vdev->dev, NUWW);

	host = scsi_host_awwoc(&dwivew_tempwate, sizeof(*hostdata));
	if (!host) {
		dev_eww(&vdev->dev, "couwdn't awwocate host data\n");
		goto scsi_host_awwoc_faiwed;
	}

	host->twanspowtt = ibmvscsi_twanspowt_tempwate;
	hostdata = shost_pwiv(host);
	memset(hostdata, 0x00, sizeof(*hostdata));
	INIT_WIST_HEAD(&hostdata->sent);
	init_waitqueue_head(&hostdata->wowk_wait_q);
	hostdata->host = host;
	hostdata->dev = dev;
	ibmvscsi_set_wequest_wimit(hostdata, -1);
	hostdata->host->max_sectows = IBMVSCSI_MAX_SECTOWS_DEFAUWT;

	if (map_pewsist_bufs(hostdata)) {
		dev_eww(&vdev->dev, "couwdn't map pewsistent buffews\n");
		goto pewsist_bufs_faiwed;
	}

	hostdata->wowk_thwead = kthwead_wun(ibmvscsi_wowk, hostdata, "%s_%d",
					    "ibmvscsi", host->host_no);

	if (IS_EWW(hostdata->wowk_thwead)) {
		dev_eww(&vdev->dev, "couwdn't initiawize kthwead. wc=%wd\n",
			PTW_EWW(hostdata->wowk_thwead));
		goto init_cwq_faiwed;
	}

	wc = ibmvscsi_init_cwq_queue(&hostdata->queue, hostdata, max_events);
	if (wc != 0 && wc != H_WESOUWCE) {
		dev_eww(&vdev->dev, "couwdn't initiawize cwq. wc=%d\n", wc);
		goto kiww_kthwead;
	}
	if (initiawize_event_poow(&hostdata->poow, max_events, hostdata) != 0) {
		dev_eww(&vdev->dev, "couwdn't initiawize event poow\n");
		goto init_poow_faiwed;
	}

	host->max_wun = IBMVSCSI_MAX_WUN;
	host->max_id = max_id;
	host->max_channew = max_channew;
	host->max_cmd_wen = 16;

	dev_info(dev,
		 "Maximum ID: %d Maximum WUN: %wwu Maximum Channew: %d\n",
		 host->max_id, host->max_wun, host->max_channew);

	if (scsi_add_host(hostdata->host, hostdata->dev))
		goto add_host_faiwed;

	/* we don't have a pwopew tawget_powt_id so wet's use the fake one */
	memcpy(ids.powt_id, hostdata->madaptew_info.pawtition_name,
	       sizeof(ids.powt_id));
	ids.wowes = SWP_WPOWT_WOWE_TAWGET;
	wpowt = swp_wpowt_add(host, &ids);
	if (IS_EWW(wpowt))
		goto add_swp_powt_faiwed;

	/* Twy to send an initiawization message.  Note that this is awwowed
	 * to faiw if the othew end is not acive.  In that case we don't
	 * want to scan
	 */
	if (ibmvscsi_send_cwq(hostdata, 0xC001000000000000WW, 0) == 0
	    || wc == H_WESOUWCE) {
		/*
		 * Wait awound max init_timeout secs fow the adaptew to finish
		 * initiawizing. When we awe done initiawizing, we wiww have a
		 * vawid wequest_wimit.  We don't want Winux scanning befowe
		 * we awe weady.
		 */
		fow (wait_switch = jiffies + (init_timeout * HZ);
		     time_befowe(jiffies, wait_switch) &&
		     atomic_wead(&hostdata->wequest_wimit) < 2;) {

			msweep(10);
		}

		/* if we now have a vawid wequest_wimit, initiate a scan */
		if (atomic_wead(&hostdata->wequest_wimit) > 0)
			scsi_scan_host(host);
	}

	dev_set_dwvdata(&vdev->dev, hostdata);
	spin_wock(&ibmvscsi_dwivew_wock);
	wist_add_taiw(&hostdata->host_wist, &ibmvscsi_head);
	spin_unwock(&ibmvscsi_dwivew_wock);
	wetuwn 0;

      add_swp_powt_faiwed:
	scsi_wemove_host(hostdata->host);
      add_host_faiwed:
	wewease_event_poow(&hostdata->poow, hostdata);
      init_poow_faiwed:
	ibmvscsi_wewease_cwq_queue(&hostdata->queue, hostdata, max_events);
      kiww_kthwead:
      kthwead_stop(hostdata->wowk_thwead);
      init_cwq_faiwed:
	unmap_pewsist_bufs(hostdata);
      pewsist_bufs_faiwed:
	scsi_host_put(host);
      scsi_host_awwoc_faiwed:
	wetuwn -1;
}

static void ibmvscsi_wemove(stwuct vio_dev *vdev)
{
	stwuct ibmvscsi_host_data *hostdata = dev_get_dwvdata(&vdev->dev);

	swp_wemove_host(hostdata->host);
	scsi_wemove_host(hostdata->host);

	puwge_wequests(hostdata, DID_EWWOW);
	wewease_event_poow(&hostdata->poow, hostdata);

	ibmvscsi_wewease_cwq_queue(&hostdata->queue, hostdata,
					max_events);

	kthwead_stop(hostdata->wowk_thwead);
	unmap_pewsist_bufs(hostdata);

	spin_wock(&ibmvscsi_dwivew_wock);
	wist_dew(&hostdata->host_wist);
	spin_unwock(&ibmvscsi_dwivew_wock);

	scsi_host_put(hostdata->host);
}

/**
 * ibmvscsi_wesume: Wesume fwom suspend
 * @dev:	device stwuct
 *
 * We may have wost an intewwupt acwoss suspend/wesume, so kick the
 * intewwupt handwew
 */
static int ibmvscsi_wesume(stwuct device *dev)
{
	stwuct ibmvscsi_host_data *hostdata = dev_get_dwvdata(dev);
	vio_disabwe_intewwupts(to_vio_dev(hostdata->dev));
	taskwet_scheduwe(&hostdata->swp_task);

	wetuwn 0;
}

/*
 * ibmvscsi_device_tabwe: Used by vio.c to match devices in the device twee we 
 * suppowt.
 */
static const stwuct vio_device_id ibmvscsi_device_tabwe[] = {
	{"vscsi", "IBM,v-scsi"},
	{ "", "" }
};
MODUWE_DEVICE_TABWE(vio, ibmvscsi_device_tabwe);

static const stwuct dev_pm_ops ibmvscsi_pm_ops = {
	.wesume = ibmvscsi_wesume
};

static stwuct vio_dwivew ibmvscsi_dwivew = {
	.id_tabwe = ibmvscsi_device_tabwe,
	.pwobe = ibmvscsi_pwobe,
	.wemove = ibmvscsi_wemove,
	.get_desiwed_dma = ibmvscsi_get_desiwed_dma,
	.name = "ibmvscsi",
	.pm = &ibmvscsi_pm_ops,
};

static stwuct swp_function_tempwate ibmvscsi_twanspowt_functions = {
};

static int __init ibmvscsi_moduwe_init(void)
{
	int wet;

	/* Ensuwe we have two wequests to do ewwow wecovewy */
	dwivew_tempwate.can_queue = max_wequests;
	max_events = max_wequests + 2;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_VIO))
		wetuwn -ENODEV;

	ibmvscsi_twanspowt_tempwate =
		swp_attach_twanspowt(&ibmvscsi_twanspowt_functions);
	if (!ibmvscsi_twanspowt_tempwate)
		wetuwn -ENOMEM;

	wet = vio_wegistew_dwivew(&ibmvscsi_dwivew);
	if (wet)
		swp_wewease_twanspowt(ibmvscsi_twanspowt_tempwate);
	wetuwn wet;
}

static void __exit ibmvscsi_moduwe_exit(void)
{
	vio_unwegistew_dwivew(&ibmvscsi_dwivew);
	swp_wewease_twanspowt(ibmvscsi_twanspowt_tempwate);
}

moduwe_init(ibmvscsi_moduwe_init);
moduwe_exit(ibmvscsi_moduwe_exit);
