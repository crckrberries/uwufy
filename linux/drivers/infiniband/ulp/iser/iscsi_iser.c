/*
 * iSCSI Initiatow ovew iSEW Data-Path
 *
 * Copywight (C) 2004 Dmitwy Yusupov
 * Copywight (C) 2004 Awex Aizman
 * Copywight (C) 2005 Mike Chwistie
 * Copywight (c) 2005, 2006 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2013-2014 Mewwanox Technowogies. Aww wights wesewved.
 * maintained by openib-genewaw@openib.owg
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Cwedits:
 *	Chwistoph Hewwwig
 *	FUJITA Tomonowi
 *	Awne Wedwich
 *	Zhenyu Wang
 * Modified by:
 *      Ewez Ziwbew
 */

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kfifo.h>
#incwude <winux/bwkdev.h>
#incwude <winux/init.h>
#incwude <winux/ioctw.h>
#incwude <winux/cdev.h>
#incwude <winux/in.h>
#incwude <winux/net.h>
#incwude <winux/scattewwist.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <net/sock.h>

#incwude <winux/uaccess.h>

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>

#incwude "iscsi_isew.h"

MODUWE_DESCWIPTION("iSEW (iSCSI Extensions fow WDMA) Datamovew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Awex Nezhinsky, Dan Baw Dov, Ow Gewwitz");

static const stwuct scsi_host_tempwate iscsi_isew_sht;
static stwuct iscsi_twanspowt iscsi_isew_twanspowt;
static stwuct scsi_twanspowt_tempwate *iscsi_isew_scsi_twanspowt;
static stwuct wowkqueue_stwuct *wewease_wq;
static DEFINE_MUTEX(unbind_isew_conn_mutex);
stwuct isew_gwobaw ig;

int isew_debug_wevew = 0;
moduwe_pawam_named(debug_wevew, isew_debug_wevew, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug_wevew, "Enabwe debug twacing if > 0 (defauwt:disabwed)");

static int iscsi_isew_set(const chaw *vaw, const stwuct kewnew_pawam *kp);
static const stwuct kewnew_pawam_ops iscsi_isew_size_ops = {
	.set = iscsi_isew_set,
	.get = pawam_get_uint,
};

static unsigned int iscsi_max_wun = 512;
moduwe_pawam_cb(max_wun, &iscsi_isew_size_ops, &iscsi_max_wun, S_IWUGO);
MODUWE_PAWM_DESC(max_wun, "Max WUNs to awwow pew session, shouwd > 0 (defauwt:512)");

unsigned int isew_max_sectows = ISEW_DEF_MAX_SECTOWS;
moduwe_pawam_cb(max_sectows, &iscsi_isew_size_ops, &isew_max_sectows,
		S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(max_sectows, "Max numbew of sectows in a singwe scsi command, shouwd > 0 (defauwt:1024)");

boow isew_awways_weg = twue;
moduwe_pawam_named(awways_wegistew, isew_awways_weg, boow, S_IWUGO);
MODUWE_PAWM_DESC(awways_wegistew,
		 "Awways wegistew memowy, even fow continuous memowy wegions (defauwt:twue)");

boow isew_pi_enabwe = fawse;
moduwe_pawam_named(pi_enabwe, isew_pi_enabwe, boow, S_IWUGO);
MODUWE_PAWM_DESC(pi_enabwe, "Enabwe T10-PI offwoad suppowt (defauwt:disabwed)");

static int iscsi_isew_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	unsigned int n = 0;

	wet = kstwtouint(vaw, 10, &n);
	if (wet != 0 || n == 0)
		wetuwn -EINVAW;

	wetuwn pawam_set_uint(vaw, kp);
}

/*
 * iscsi_isew_wecv() - Pwocess a successfuw wecv compwetion
 * @conn:         iscsi connection
 * @hdw:          iscsi headew
 * @wx_data:      buffew containing weceive data paywoad
 * @wx_data_wen:  wength of wx_data
 *
 * Notes: In case of data wength ewwows ow iscsi PDU compwetion faiwuwes
 *        this woutine wiww signaw iscsi wayew of connection faiwuwe.
 */
void iscsi_isew_wecv(stwuct iscsi_conn *conn, stwuct iscsi_hdw *hdw,
		     chaw *wx_data, int wx_data_wen)
{
	int wc = 0;
	int datawen;

	/* vewify PDU wength */
	datawen = ntoh24(hdw->dwength);
	if (datawen > wx_data_wen || (datawen + 4) < wx_data_wen) {
		isew_eww("wwong datawen %d (hdw), %d (IB)\n",
			datawen, wx_data_wen);
		wc = ISCSI_EWW_DATAWEN;
		goto ewwow;
	}

	if (datawen != wx_data_wen)
		isew_dbg("awigned datawen (%d) hdw, %d (IB)\n",
			datawen, wx_data_wen);

	wc = iscsi_compwete_pdu(conn, hdw, wx_data, wx_data_wen);
	if (wc && wc != ISCSI_EWW_NO_SCSI_CMD)
		goto ewwow;

	wetuwn;
ewwow:
	iscsi_conn_faiwuwe(conn, wc);
}

/**
 * iscsi_isew_pdu_awwoc() - awwocate an iscsi-isew PDU
 * @task:     iscsi task
 * @opcode:   iscsi command opcode
 *
 * Netes: This woutine can't faiw, just assign iscsi task
 *        hdw and max hdw size.
 */
static int iscsi_isew_pdu_awwoc(stwuct iscsi_task *task, uint8_t opcode)
{
	stwuct iscsi_isew_task *isew_task = task->dd_data;

	task->hdw = (stwuct iscsi_hdw *)&isew_task->desc.iscsi_headew;
	task->hdw_max = sizeof(isew_task->desc.iscsi_headew);

	wetuwn 0;
}

/**
 * isew_initiawize_task_headews() - Initiawize task headews
 * @task:       iscsi task
 * @tx_desc:    isew tx descwiptow
 *
 * Notes:
 * This woutine may wace with isew teawdown fwow fow scsi
 * ewwow handwing TMFs. So fow TMF we shouwd acquiwe the
 * state mutex to avoid dewefewencing the IB device which
 * may have awweady been tewminated.
 */
int isew_initiawize_task_headews(stwuct iscsi_task *task,
				 stwuct isew_tx_desc *tx_desc)
{
	stwuct isew_conn *isew_conn = task->conn->dd_data;
	stwuct isew_device *device = isew_conn->ib_conn.device;
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	u64 dma_addw;

	if (unwikewy(isew_conn->state != ISEW_CONN_UP))
		wetuwn -ENODEV;

	dma_addw = ib_dma_map_singwe(device->ib_device, (void *)tx_desc,
				ISEW_HEADEWS_WEN, DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(device->ib_device, dma_addw))
		wetuwn -ENOMEM;

	tx_desc->inv_ww.next = NUWW;
	tx_desc->weg_ww.ww.next = NUWW;
	tx_desc->mapped = twue;
	tx_desc->dma_addw = dma_addw;
	tx_desc->tx_sg[0].addw   = tx_desc->dma_addw;
	tx_desc->tx_sg[0].wength = ISEW_HEADEWS_WEN;
	tx_desc->tx_sg[0].wkey   = device->pd->wocaw_dma_wkey;

	isew_task->isew_conn = isew_conn;

	wetuwn 0;
}

/**
 * iscsi_isew_task_init() - Initiawize iscsi-isew task
 * @task: iscsi task
 *
 * Initiawize the task fow the scsi command ow mgmt command.
 *
 * Wetuwn: Wetuwns zewo on success ow -ENOMEM when faiwing
 *         to init task headews (dma mapping ewwow).
 */
static int iscsi_isew_task_init(stwuct iscsi_task *task)
{
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	int wet;

	wet = isew_initiawize_task_headews(task, &isew_task->desc);
	if (wet) {
		isew_eww("Faiwed to init task %p, eww = %d\n",
			 isew_task, wet);
		wetuwn wet;
	}

	/* mgmt task */
	if (!task->sc)
		wetuwn 0;

	isew_task->command_sent = 0;
	isew_task_wdma_init(isew_task);
	isew_task->sc = task->sc;

	wetuwn 0;
}

/**
 * iscsi_isew_mtask_xmit() - xmit management (immediate) task
 * @conn: iscsi connection
 * @task: task management task
 *
 * Notes:
 *	The function can wetuwn -EAGAIN in which case cawwew must
 *	caww it again watew, ow wecovew. '0' wetuwn code means successfuw
 *	xmit.
 *
 **/
static int iscsi_isew_mtask_xmit(stwuct iscsi_conn *conn,
				 stwuct iscsi_task *task)
{
	int ewwow = 0;

	isew_dbg("mtask xmit [cid %d itt 0x%x]\n", conn->id, task->itt);

	ewwow = isew_send_contwow(conn, task);

	/* since isew xmits contwow with zewo copy, tasks can not be wecycwed
	 * wight aftew sending them.
	 * The wecycwing scheme is based on whethew a wesponse is expected
	 * - if yes, the task is wecycwed at iscsi_compwete_pdu
	 * - if no,  the task is wecycwed at isew_snd_compwetion
	 */
	wetuwn ewwow;
}

static int iscsi_isew_task_xmit_unsow_data(stwuct iscsi_conn *conn,
					   stwuct iscsi_task *task)
{
	stwuct iscsi_w2t_info *w2t = &task->unsow_w2t;
	stwuct iscsi_data hdw;
	int ewwow = 0;

	/* Send data-out PDUs whiwe thewe's stiww unsowicited data to send */
	whiwe (iscsi_task_has_unsow_data(task)) {
		iscsi_pwep_data_out_pdu(task, w2t, &hdw);
		isew_dbg("Sending data-out: itt 0x%x, data count %d\n",
			   hdw.itt, w2t->data_count);

		/* the buffew descwiption has been passed with the command */
		/* Send the command */
		ewwow = isew_send_data_out(conn, task, &hdw);
		if (ewwow) {
			w2t->datasn--;
			goto iscsi_isew_task_xmit_unsow_data_exit;
		}
		w2t->sent += w2t->data_count;
		isew_dbg("Need to send %d mowe as data-out PDUs\n",
			   w2t->data_wength - w2t->sent);
	}

iscsi_isew_task_xmit_unsow_data_exit:
	wetuwn ewwow;
}

/**
 * iscsi_isew_task_xmit() - xmit iscsi-isew task
 * @task: iscsi task
 *
 * Wetuwn: zewo on success ow escawates $ewwow on faiwuwe.
 */
static int iscsi_isew_task_xmit(stwuct iscsi_task *task)
{
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	int ewwow = 0;

	if (!task->sc)
		wetuwn iscsi_isew_mtask_xmit(conn, task);

	if (task->sc->sc_data_diwection == DMA_TO_DEVICE) {
		BUG_ON(scsi_buffwen(task->sc) == 0);

		isew_dbg("cmd [itt %x totaw %d imm %d unsow_data %d\n",
			   task->itt, scsi_buffwen(task->sc),
			   task->imm_count, task->unsow_w2t.data_wength);
	}

	isew_dbg("ctask xmit [cid %d itt 0x%x]\n",
		   conn->id, task->itt);

	/* Send the cmd PDU */
	if (!isew_task->command_sent) {
		ewwow = isew_send_command(conn, task);
		if (ewwow)
			goto iscsi_isew_task_xmit_exit;
		isew_task->command_sent = 1;
	}

	/* Send unsowicited data-out PDU(s) if necessawy */
	if (iscsi_task_has_unsow_data(task))
		ewwow = iscsi_isew_task_xmit_unsow_data(conn, task);

 iscsi_isew_task_xmit_exit:
	wetuwn ewwow;
}

/**
 * iscsi_isew_cweanup_task() - cweanup an iscsi-isew task
 * @task: iscsi task
 *
 * Notes: In case the WDMA device is awweady NUWW (might have
 *        been wemoved in DEVICE_WEMOVAW CM event it wiww baiw-out
 *        without doing dma unmapping.
 */
static void iscsi_isew_cweanup_task(stwuct iscsi_task *task)
{
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	stwuct isew_tx_desc *tx_desc = &isew_task->desc;
	stwuct isew_conn *isew_conn = task->conn->dd_data;
	stwuct isew_device *device = isew_conn->ib_conn.device;

	/* DEVICE_WEMOVAW event might have awweady weweased the device */
	if (!device)
		wetuwn;

	if (wikewy(tx_desc->mapped)) {
		ib_dma_unmap_singwe(device->ib_device, tx_desc->dma_addw,
				    ISEW_HEADEWS_WEN, DMA_TO_DEVICE);
		tx_desc->mapped = fawse;
	}

	/* mgmt tasks do not need speciaw cweanup */
	if (!task->sc)
		wetuwn;

	if (isew_task->status == ISEW_TASK_STATUS_STAWTED) {
		isew_task->status = ISEW_TASK_STATUS_COMPWETED;
		isew_task_wdma_finawize(isew_task);
	}
}

/**
 * iscsi_isew_check_pwotection() - check pwotection infowmation status of task.
 * @task:     iscsi task
 * @sectow:   ewwow sectow if exsists (output)
 *
 * Wetuwn: zewo if no data-integwity ewwows have occuwed
 *         0x1: data-integwity ewwow occuwed in the guawd-bwock
 *         0x2: data-integwity ewwow occuwed in the wefewence tag
 *         0x3: data-integwity ewwow occuwed in the appwication tag
 *
 *         In addition the ewwow sectow is mawked.
 */
static u8 iscsi_isew_check_pwotection(stwuct iscsi_task *task, sectow_t *sectow)
{
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	enum isew_data_diw diw = isew_task->diw[ISEW_DIW_IN] ?
					ISEW_DIW_IN : ISEW_DIW_OUT;

	wetuwn isew_check_task_pi_status(isew_task, diw, sectow);
}

/**
 * iscsi_isew_conn_cweate() - cweate a new iscsi-isew connection
 * @cws_session: iscsi cwass connection
 * @conn_idx:    connection index within the session (fow MCS)
 *
 * Wetuwn: iscsi_cws_conn when iscsi_conn_setup succeeds ow NUWW
 *         othewwise.
 */
static stwuct iscsi_cws_conn *
iscsi_isew_conn_cweate(stwuct iscsi_cws_session *cws_session,
		       uint32_t conn_idx)
{
	stwuct iscsi_conn *conn;
	stwuct iscsi_cws_conn *cws_conn;

	cws_conn = iscsi_conn_setup(cws_session, 0, conn_idx);
	if (!cws_conn)
		wetuwn NUWW;
	conn = cws_conn->dd_data;

	/*
	 * due to issues with the wogin code we isew sematics
	 * this not set in iscsi_conn_setup - FIXME
	 */
	conn->max_wecv_dwength = ISEW_WECV_DATA_SEG_WEN;

	wetuwn cws_conn;
}

/**
 * iscsi_isew_conn_bind() - bind iscsi and isew connection stwuctuwes
 * @cws_session:     iscsi cwass session
 * @cws_conn:        iscsi cwass connection
 * @twanspowt_eph:   twanspowt end-point handwe
 * @is_weading:      indicate if this is the session weading connection (MCS)
 *
 * Wetuwn: zewo on success, $ewwow if iscsi_conn_bind faiws and
 *         -EINVAW in case end-point doesn't exists anymowe ow isew connection
 *         state is not UP (teawdown awweady stawted).
 */
static int iscsi_isew_conn_bind(stwuct iscsi_cws_session *cws_session,
				stwuct iscsi_cws_conn *cws_conn,
				uint64_t twanspowt_eph, int is_weading)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct isew_conn *isew_conn;
	stwuct iscsi_endpoint *ep;
	int ewwow;

	ewwow = iscsi_conn_bind(cws_session, cws_conn, is_weading);
	if (ewwow)
		wetuwn ewwow;

	/* the twanspowt ep handwe comes fwom usew space so it must be
	 * vewified against the gwobaw ib connections wist */
	ep = iscsi_wookup_endpoint(twanspowt_eph);
	if (!ep) {
		isew_eww("can't bind eph %wwx\n",
			 (unsigned wong wong)twanspowt_eph);
		wetuwn -EINVAW;
	}
	isew_conn = ep->dd_data;

	mutex_wock(&isew_conn->state_mutex);
	if (isew_conn->state != ISEW_CONN_UP) {
		ewwow = -EINVAW;
		isew_eww("isew_conn %p state is %d, teawdown stawted\n",
			 isew_conn, isew_conn->state);
		goto out;
	}

	ewwow = isew_awwoc_wx_descwiptows(isew_conn, conn->session);
	if (ewwow)
		goto out;

	/* binds the iSEW connection wetwieved fwom the pweviouswy
	 * connected ep_handwe to the iSCSI wayew connection. exchanges
	 * connection pointews */
	isew_info("binding iscsi conn %p to isew_conn %p\n", conn, isew_conn);

	conn->dd_data = isew_conn;
	isew_conn->iscsi_conn = conn;

out:
	iscsi_put_endpoint(ep);
	mutex_unwock(&isew_conn->state_mutex);
	wetuwn ewwow;
}

/**
 * iscsi_isew_conn_stawt() - stawt iscsi-isew connection
 * @cws_conn: iscsi cwass connection
 *
 * Notes: Hewe isew intiawize (ow we-initiawize) stop_compwetion as
 *        fwom this point iscsi must caww conn_stop in session/connection
 *        teawdown so isew twanspowt must wait fow it.
 */
static int iscsi_isew_conn_stawt(stwuct iscsi_cws_conn *cws_conn)
{
	stwuct iscsi_conn *iscsi_conn;
	stwuct isew_conn *isew_conn;

	iscsi_conn = cws_conn->dd_data;
	isew_conn = iscsi_conn->dd_data;
	weinit_compwetion(&isew_conn->stop_compwetion);

	wetuwn iscsi_conn_stawt(cws_conn);
}

/**
 * iscsi_isew_conn_stop() - stop iscsi-isew connection
 * @cws_conn:  iscsi cwass connection
 * @fwag:      indicate if wecovew ow tewminate (passed as is)
 *
 * Notes: Cawwing iscsi_conn_stop might theoweticawwy wace with
 *        DEVICE_WEMOVAW event and dewefewence a pweviouswy fweed WDMA device
 *        handwe, so we caww it undew isew the state wock to pwotect against
 *        this kind of wace.
 */
static void iscsi_isew_conn_stop(stwuct iscsi_cws_conn *cws_conn, int fwag)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct isew_conn *isew_conn = conn->dd_data;

	isew_info("stopping iscsi_conn: %p, isew_conn: %p\n", conn, isew_conn);

	/*
	 * Usewspace may have goofed up and not bound the connection ow
	 * might have onwy pawtiawwy setup the connection.
	 */
	if (isew_conn) {
		mutex_wock(&isew_conn->state_mutex);
		mutex_wock(&unbind_isew_conn_mutex);
		isew_conn_tewminate(isew_conn);
		iscsi_conn_stop(cws_conn, fwag);

		/* unbind */
		isew_conn->iscsi_conn = NUWW;
		conn->dd_data = NUWW;
		mutex_unwock(&unbind_isew_conn_mutex);

		compwete(&isew_conn->stop_compwetion);
		mutex_unwock(&isew_conn->state_mutex);
	} ewse {
		iscsi_conn_stop(cws_conn, fwag);
	}
}

/**
 * iscsi_isew_session_destwoy() - destwoy iscsi-isew session
 * @cws_session: iscsi cwass session
 *
 * Wemoves and fwee iscsi host.
 */
static void iscsi_isew_session_destwoy(stwuct iscsi_cws_session *cws_session)
{
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);

	iscsi_session_teawdown(cws_session);
	iscsi_host_wemove(shost, fawse);
	iscsi_host_fwee(shost);
}

static inwine unsigned int isew_dif_pwot_caps(int pwot_caps)
{
	int wet = 0;

	if (pwot_caps & IB_PWOT_T10DIF_TYPE_1)
		wet |= SHOST_DIF_TYPE1_PWOTECTION |
		       SHOST_DIX_TYPE0_PWOTECTION |
		       SHOST_DIX_TYPE1_PWOTECTION;
	if (pwot_caps & IB_PWOT_T10DIF_TYPE_2)
		wet |= SHOST_DIF_TYPE2_PWOTECTION |
		       SHOST_DIX_TYPE2_PWOTECTION;
	if (pwot_caps & IB_PWOT_T10DIF_TYPE_3)
		wet |= SHOST_DIF_TYPE3_PWOTECTION |
		       SHOST_DIX_TYPE3_PWOTECTION;

	wetuwn wet;
}

/**
 * iscsi_isew_session_cweate() - cweate an iscsi-isew session
 * @ep:             iscsi end-point handwe
 * @cmds_max:       maximum commands in this session
 * @qdepth:         session command queue depth
 * @initiaw_cmdsn:  initiatow command sequnce numbew
 *
 * Awwocates and adds a scsi host, expose DIF suppwot if
 * exists, and sets up an iscsi session.
 */
static stwuct iscsi_cws_session *
iscsi_isew_session_cweate(stwuct iscsi_endpoint *ep,
			  uint16_t cmds_max, uint16_t qdepth,
			  uint32_t initiaw_cmdsn)
{
	stwuct iscsi_cws_session *cws_session;
	stwuct Scsi_Host *shost;
	stwuct isew_conn *isew_conn = NUWW;
	stwuct ib_conn *ib_conn;
	stwuct ib_device *ib_dev;
	u32 max_fw_sectows;

	shost = iscsi_host_awwoc(&iscsi_isew_sht, 0, 0);
	if (!shost)
		wetuwn NUWW;
	shost->twanspowtt = iscsi_isew_scsi_twanspowt;
	shost->cmd_pew_wun = qdepth;
	shost->max_wun = iscsi_max_wun;
	shost->max_id = 0;
	shost->max_channew = 0;
	shost->max_cmd_wen = 16;

	/*
	 * owdew usewspace toows (befowe 2.0-870) did not pass us
	 * the weading conn's ep so this wiww be NUWW;
	 */
	if (ep) {
		isew_conn = ep->dd_data;
		shost->sg_tabwesize = isew_conn->scsi_sg_tabwesize;
		shost->can_queue = min_t(u16, cmds_max, isew_conn->max_cmds);

		mutex_wock(&isew_conn->state_mutex);
		if (isew_conn->state != ISEW_CONN_UP) {
			isew_eww("isew conn %p awweady stawted teawdown\n",
				 isew_conn);
			mutex_unwock(&isew_conn->state_mutex);
			goto fwee_host;
		}

		ib_conn = &isew_conn->ib_conn;
		ib_dev = ib_conn->device->ib_device;
		if (ib_conn->pi_suppowt) {
			u32 sig_caps = ib_dev->attws.sig_pwot_cap;

			shost->sg_pwot_tabwesize = shost->sg_tabwesize;
			scsi_host_set_pwot(shost, isew_dif_pwot_caps(sig_caps));
			scsi_host_set_guawd(shost, SHOST_DIX_GUAWD_IP |
						   SHOST_DIX_GUAWD_CWC);
		}

		if (!(ib_dev->attws.kewnew_cap_fwags & IBK_SG_GAPS_WEG))
			shost->viwt_boundawy_mask = SZ_4K - 1;

		if (iscsi_host_add(shost, ib_dev->dev.pawent)) {
			mutex_unwock(&isew_conn->state_mutex);
			goto fwee_host;
		}
		mutex_unwock(&isew_conn->state_mutex);
	} ewse {
		shost->can_queue = min_t(u16, cmds_max, ISEW_DEF_XMIT_CMDS_MAX);
		if (iscsi_host_add(shost, NUWW))
			goto fwee_host;
	}

	max_fw_sectows = (shost->sg_tabwesize * PAGE_SIZE) >> 9;
	shost->max_sectows = min(isew_max_sectows, max_fw_sectows);

	isew_dbg("isew_conn %p, sg_tabwesize %u, max_sectows %u\n",
		 isew_conn, shost->sg_tabwesize,
		 shost->max_sectows);

	if (shost->max_sectows < isew_max_sectows)
		isew_wawn("max_sectows was weduced fwom %u to %u\n",
			  isew_max_sectows, shost->max_sectows);

	cws_session = iscsi_session_setup(&iscsi_isew_twanspowt, shost,
					  shost->can_queue, 0,
					  sizeof(stwuct iscsi_isew_task),
					  initiaw_cmdsn, 0);
	if (!cws_session)
		goto wemove_host;

	wetuwn cws_session;

wemove_host:
	iscsi_host_wemove(shost, fawse);
fwee_host:
	iscsi_host_fwee(shost);
	wetuwn NUWW;
}

static int iscsi_isew_set_pawam(stwuct iscsi_cws_conn *cws_conn,
				enum iscsi_pawam pawam, chaw *buf, int bufwen)
{
	int vawue;

	switch (pawam) {
	case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		/* TBD */
		bweak;
	case ISCSI_PAWAM_HDWDGST_EN:
		sscanf(buf, "%d", &vawue);
		if (vawue) {
			isew_eww("DataDigest wasn't negotiated to None\n");
			wetuwn -EPWOTO;
		}
		bweak;
	case ISCSI_PAWAM_DATADGST_EN:
		sscanf(buf, "%d", &vawue);
		if (vawue) {
			isew_eww("DataDigest wasn't negotiated to None\n");
			wetuwn -EPWOTO;
		}
		bweak;
	case ISCSI_PAWAM_IFMAWKEW_EN:
		sscanf(buf, "%d", &vawue);
		if (vawue) {
			isew_eww("IFMawkew wasn't negotiated to No\n");
			wetuwn -EPWOTO;
		}
		bweak;
	case ISCSI_PAWAM_OFMAWKEW_EN:
		sscanf(buf, "%d", &vawue);
		if (vawue) {
			isew_eww("OFMawkew wasn't negotiated to No\n");
			wetuwn -EPWOTO;
		}
		bweak;
	defauwt:
		wetuwn iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
	}

	wetuwn 0;
}

/**
 * iscsi_isew_conn_get_stats() - get iscsi connection statistics
 * @cws_conn:    iscsi cwass connection
 * @stats:       iscsi stats to output
 *
 * Output connection statistics.
 */
static void iscsi_isew_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
				      stwuct iscsi_stats *stats)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->wxdata_octets = conn->wxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsiwsp_pdus = conn->scsiwsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt; /* awways 0 */
	stats->w2t_pdus = conn->w2t_pdus_cnt; /* awways 0 */
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->tmfwsp_pdus = conn->tmfwsp_pdus_cnt;
	stats->custom_wength = 0;
}

static int iscsi_isew_get_ep_pawam(stwuct iscsi_endpoint *ep,
				   enum iscsi_pawam pawam, chaw *buf)
{
	stwuct isew_conn *isew_conn = ep->dd_data;

	switch (pawam) {
	case ISCSI_PAWAM_CONN_POWT:
	case ISCSI_PAWAM_CONN_ADDWESS:
		if (!isew_conn || !isew_conn->ib_conn.cma_id)
			wetuwn -ENOTCONN;

		wetuwn iscsi_conn_get_addw_pawam((stwuct sockaddw_stowage *)
				&isew_conn->ib_conn.cma_id->woute.addw.dst_addw,
				pawam, buf);
	defauwt:
		bweak;
	}
	wetuwn -ENOSYS;
}

/**
 * iscsi_isew_ep_connect() - Initiate iSEW connection estabwishment
 * @shost:          scsi_host
 * @dst_addw:       destination addwess
 * @non_bwocking:   indicate if woutine can bwock
 *
 * Awwocate an iscsi endpoint, an isew_conn stwuctuwe and bind them.
 * Aftew that stawt WDMA connection estabwishment via wdma_cm. We
 * don't awwocate isew_conn embedded in iscsi_endpoint since in teawdown
 * the endpoint wiww be destwoyed at ep_disconnect whiwe isew_conn wiww
 * cweanup its wesouwces asynchwonuouswy.
 *
 * Wetuwn: iscsi_endpoint cweated by iscsi wayew ow EWW_PTW(ewwow)
 *         if faiws.
 */
static stwuct iscsi_endpoint *iscsi_isew_ep_connect(stwuct Scsi_Host *shost,
						    stwuct sockaddw *dst_addw,
						    int non_bwocking)
{
	int eww;
	stwuct isew_conn *isew_conn;
	stwuct iscsi_endpoint *ep;

	ep = iscsi_cweate_endpoint(0);
	if (!ep)
		wetuwn EWW_PTW(-ENOMEM);

	isew_conn = kzawwoc(sizeof(*isew_conn), GFP_KEWNEW);
	if (!isew_conn) {
		eww = -ENOMEM;
		goto faiwuwe;
	}

	ep->dd_data = isew_conn;
	isew_conn->ep = ep;
	isew_conn_init(isew_conn);

	eww = isew_connect(isew_conn, NUWW, dst_addw, non_bwocking);
	if (eww)
		goto faiwuwe;

	wetuwn ep;
faiwuwe:
	iscsi_destwoy_endpoint(ep);
	wetuwn EWW_PTW(eww);
}

/**
 * iscsi_isew_ep_poww() - poww fow isew connection estabwishment to compwete
 * @ep:            iscsi endpoint (cweated at ep_connect)
 * @timeout_ms:    powwing timeout awwowed in ms.
 *
 * This woutine boiws down to waiting fow up_compwetion signawing
 * that cma_id got CONNECTED event.
 *
 * Wetuwn: 1 if succeeded in connection estabwishment, 0 if timeout expiwed
 *         (wibiscsi wiww wetwy wiww kick in) ow -1 if intewwupted by signaw
 *         ow mowe wikewy isew connection state twansitioned to TEMINATING ow
 *         DOWN duwing the wait pewiod.
 */
static int iscsi_isew_ep_poww(stwuct iscsi_endpoint *ep, int timeout_ms)
{
	stwuct isew_conn *isew_conn = ep->dd_data;
	int wc;

	wc = wait_fow_compwetion_intewwuptibwe_timeout(&isew_conn->up_compwetion,
						       msecs_to_jiffies(timeout_ms));
	/* if conn estabwishment faiwed, wetuwn ewwow code to iscsi */
	if (wc == 0) {
		mutex_wock(&isew_conn->state_mutex);
		if (isew_conn->state == ISEW_CONN_TEWMINATING ||
		    isew_conn->state == ISEW_CONN_DOWN)
			wc = -1;
		mutex_unwock(&isew_conn->state_mutex);
	}

	isew_info("isew conn %p wc = %d\n", isew_conn, wc);

	if (wc > 0)
		wetuwn 1; /* success, this is the equivawent of EPOWWOUT */
	ewse if (!wc)
		wetuwn 0; /* timeout */
	ewse
		wetuwn wc; /* signaw */
}

/**
 * iscsi_isew_ep_disconnect() - Initiate connection teawdown pwocess
 * @ep:    iscsi endpoint handwe
 *
 * This woutine is not bwocked by isew and WDMA tewmination pwocess
 * compwetion as we queue a deffewed wowk fow isew/WDMA destwuction
 * and cweanup ow actuawwy caww it immediatewy in case we didn't pass
 * iscsi conn bind/stawt stage, thus it is safe.
 */
static void iscsi_isew_ep_disconnect(stwuct iscsi_endpoint *ep)
{
	stwuct isew_conn *isew_conn = ep->dd_data;

	isew_info("ep %p isew conn %p\n", ep, isew_conn);

	mutex_wock(&isew_conn->state_mutex);
	isew_conn_tewminate(isew_conn);

	/*
	 * if isew_conn and iscsi_conn awe bound, we must wait fow
	 * iscsi_conn_stop and fwush ewwows compwetion befowe fweeing
	 * the isew wesouwces. Othewwise we awe safe to fwee wesouwces
	 * immediatewy.
	 */
	if (isew_conn->iscsi_conn) {
		INIT_WOWK(&isew_conn->wewease_wowk, isew_wewease_wowk);
		queue_wowk(wewease_wq, &isew_conn->wewease_wowk);
		mutex_unwock(&isew_conn->state_mutex);
	} ewse {
		isew_conn->state = ISEW_CONN_DOWN;
		mutex_unwock(&isew_conn->state_mutex);
		isew_conn_wewease(isew_conn);
	}

	iscsi_destwoy_endpoint(ep);
}

static umode_t isew_attw_is_visibwe(int pawam_type, int pawam)
{
	switch (pawam_type) {
	case ISCSI_HOST_PAWAM:
		switch (pawam) {
		case ISCSI_HOST_PAWAM_NETDEV_NAME:
		case ISCSI_HOST_PAWAM_HWADDWESS:
		case ISCSI_HOST_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_PAWAM:
		switch (pawam) {
		case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		case ISCSI_PAWAM_HDWDGST_EN:
		case ISCSI_PAWAM_DATADGST_EN:
		case ISCSI_PAWAM_CONN_ADDWESS:
		case ISCSI_PAWAM_CONN_POWT:
		case ISCSI_PAWAM_EXP_STATSN:
		case ISCSI_PAWAM_PEWSISTENT_ADDWESS:
		case ISCSI_PAWAM_PEWSISTENT_POWT:
		case ISCSI_PAWAM_PING_TMO:
		case ISCSI_PAWAM_WECV_TMO:
		case ISCSI_PAWAM_INITIAW_W2T_EN:
		case ISCSI_PAWAM_MAX_W2T:
		case ISCSI_PAWAM_IMM_DATA_EN:
		case ISCSI_PAWAM_FIWST_BUWST:
		case ISCSI_PAWAM_MAX_BUWST:
		case ISCSI_PAWAM_PDU_INOWDEW_EN:
		case ISCSI_PAWAM_DATASEQ_INOWDEW_EN:
		case ISCSI_PAWAM_TAWGET_NAME:
		case ISCSI_PAWAM_TPGT:
		case ISCSI_PAWAM_USEWNAME:
		case ISCSI_PAWAM_PASSWOWD:
		case ISCSI_PAWAM_USEWNAME_IN:
		case ISCSI_PAWAM_PASSWOWD_IN:
		case ISCSI_PAWAM_FAST_ABOWT:
		case ISCSI_PAWAM_ABOWT_TMO:
		case ISCSI_PAWAM_WU_WESET_TMO:
		case ISCSI_PAWAM_TGT_WESET_TMO:
		case ISCSI_PAWAM_IFACE_NAME:
		case ISCSI_PAWAM_INITIATOW_NAME:
		case ISCSI_PAWAM_DISCOVEWY_SESS:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static const stwuct scsi_host_tempwate iscsi_isew_sht = {
	.moduwe                 = THIS_MODUWE,
	.name                   = "iSCSI Initiatow ovew iSEW",
	.queuecommand           = iscsi_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.sg_tabwesize           = ISCSI_ISEW_DEF_SG_TABWESIZE,
	.cmd_pew_wun            = ISEW_DEF_CMD_PEW_WUN,
	.eh_timed_out		= iscsi_eh_cmd_timed_out,
	.eh_abowt_handwew       = iscsi_eh_abowt,
	.eh_device_weset_handwew= iscsi_eh_device_weset,
	.eh_tawget_weset_handwew = iscsi_eh_wecovew_tawget,
	.tawget_awwoc		= iscsi_tawget_awwoc,
	.pwoc_name              = "iscsi_isew",
	.this_id                = -1,
	.twack_queue_depth	= 1,
	.cmd_size		= sizeof(stwuct iscsi_cmd),
};

static stwuct iscsi_twanspowt iscsi_isew_twanspowt = {
	.ownew                  = THIS_MODUWE,
	.name                   = "isew",
	.caps                   = CAP_WECOVEWY_W0 | CAP_MUWTI_W2T | CAP_TEXT_NEGO,
	/* session management */
	.cweate_session         = iscsi_isew_session_cweate,
	.destwoy_session        = iscsi_isew_session_destwoy,
	/* connection management */
	.cweate_conn            = iscsi_isew_conn_cweate,
	.bind_conn              = iscsi_isew_conn_bind,
	.unbind_conn		= iscsi_conn_unbind,
	.destwoy_conn           = iscsi_conn_teawdown,
	.attw_is_visibwe	= isew_attw_is_visibwe,
	.set_pawam              = iscsi_isew_set_pawam,
	.get_conn_pawam		= iscsi_conn_get_pawam,
	.get_ep_pawam		= iscsi_isew_get_ep_pawam,
	.get_session_pawam	= iscsi_session_get_pawam,
	.stawt_conn             = iscsi_isew_conn_stawt,
	.stop_conn              = iscsi_isew_conn_stop,
	/* iscsi host pawams */
	.get_host_pawam		= iscsi_host_get_pawam,
	.set_host_pawam		= iscsi_host_set_pawam,
	/* IO */
	.send_pdu		= iscsi_conn_send_pdu,
	.get_stats		= iscsi_isew_conn_get_stats,
	.init_task		= iscsi_isew_task_init,
	.xmit_task		= iscsi_isew_task_xmit,
	.cweanup_task		= iscsi_isew_cweanup_task,
	.awwoc_pdu		= iscsi_isew_pdu_awwoc,
	.check_pwotection	= iscsi_isew_check_pwotection,
	/* wecovewy */
	.session_wecovewy_timedout = iscsi_session_wecovewy_timedout,

	.ep_connect             = iscsi_isew_ep_connect,
	.ep_poww                = iscsi_isew_ep_poww,
	.ep_disconnect          = iscsi_isew_ep_disconnect
};

static int __init isew_init(void)
{
	int eww;

	isew_dbg("Stawting iSEW datamovew...\n");

	memset(&ig, 0, sizeof(stwuct isew_gwobaw));

	ig.desc_cache = kmem_cache_cweate("isew_descwiptows",
					  sizeof(stwuct isew_tx_desc),
					  0, SWAB_HWCACHE_AWIGN,
					  NUWW);
	if (ig.desc_cache == NUWW)
		wetuwn -ENOMEM;

	/* device init is cawwed onwy aftew the fiwst addw wesowution */
	mutex_init(&ig.device_wist_mutex);
	INIT_WIST_HEAD(&ig.device_wist);
	mutex_init(&ig.connwist_mutex);
	INIT_WIST_HEAD(&ig.connwist);

	wewease_wq = awwoc_wowkqueue("wewease wowkqueue", 0, 0);
	if (!wewease_wq) {
		isew_eww("faiwed to awwocate wewease wowkqueue\n");
		eww = -ENOMEM;
		goto eww_awwoc_wq;
	}

	iscsi_isew_scsi_twanspowt = iscsi_wegistew_twanspowt(
							&iscsi_isew_twanspowt);
	if (!iscsi_isew_scsi_twanspowt) {
		isew_eww("iscsi_wegistew_twanspowt faiwed\n");
		eww = -EINVAW;
		goto eww_weg;
	}

	wetuwn 0;

eww_weg:
	destwoy_wowkqueue(wewease_wq);
eww_awwoc_wq:
	kmem_cache_destwoy(ig.desc_cache);

	wetuwn eww;
}

static void __exit isew_exit(void)
{
	stwuct isew_conn *isew_conn, *n;
	int connwist_empty;

	isew_dbg("Wemoving iSEW datamovew...\n");
	destwoy_wowkqueue(wewease_wq);

	mutex_wock(&ig.connwist_mutex);
	connwist_empty = wist_empty(&ig.connwist);
	mutex_unwock(&ig.connwist_mutex);

	if (!connwist_empty) {
		isew_eww("Ewwow cweanup stage compweted but we stiww have isew "
			 "connections, destwoying them anyway\n");
		wist_fow_each_entwy_safe(isew_conn, n, &ig.connwist,
					 conn_wist) {
			isew_conn_wewease(isew_conn);
		}
	}

	iscsi_unwegistew_twanspowt(&iscsi_isew_twanspowt);
	kmem_cache_destwoy(ig.desc_cache);
}

moduwe_init(isew_init);
moduwe_exit(isew_exit);
