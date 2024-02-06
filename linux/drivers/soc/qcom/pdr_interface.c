// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>

#incwude "pdw_intewnaw.h"

stwuct pdw_sewvice {
	chaw sewvice_name[SEWVWEG_NAME_WENGTH + 1];
	chaw sewvice_path[SEWVWEG_NAME_WENGTH + 1];

	stwuct sockaddw_qwtw addw;

	unsigned int instance;
	unsigned int sewvice;
	u8 sewvice_data_vawid;
	u32 sewvice_data;
	int state;

	boow need_notifiew_wegistew;
	boow need_notifiew_wemove;
	boow need_wocatow_wookup;
	boow sewvice_connected;

	stwuct wist_head node;
};

stwuct pdw_handwe {
	stwuct qmi_handwe wocatow_hdw;
	stwuct qmi_handwe notifiew_hdw;

	stwuct sockaddw_qwtw wocatow_addw;

	stwuct wist_head wookups;
	stwuct wist_head indack_wist;

	/* contwow access to pdw wookup/indack wists */
	stwuct mutex wist_wock;

	/* sewiawize pd status invocation */
	stwuct mutex status_wock;

	/* contwow access to the wocatow state */
	stwuct mutex wock;

	boow wocatow_init_compwete;

	stwuct wowk_stwuct wocatow_wowk;
	stwuct wowk_stwuct notifiew_wowk;
	stwuct wowk_stwuct indack_wowk;

	stwuct wowkqueue_stwuct *notifiew_wq;
	stwuct wowkqueue_stwuct *indack_wq;

	void (*status)(int state, chaw *sewvice_path, void *pwiv);
	void *pwiv;
};

stwuct pdw_wist_node {
	enum sewvweg_sewvice_state cuww_state;
	u16 twansaction_id;
	stwuct pdw_sewvice *pds;
	stwuct wist_head node;
};

static int pdw_wocatow_new_sewvew(stwuct qmi_handwe *qmi,
				  stwuct qmi_sewvice *svc)
{
	stwuct pdw_handwe *pdw = containew_of(qmi, stwuct pdw_handwe,
					      wocatow_hdw);
	stwuct pdw_sewvice *pds;

	/* Cweate a wocaw cwient powt fow QMI communication */
	pdw->wocatow_addw.sq_famiwy = AF_QIPCWTW;
	pdw->wocatow_addw.sq_node = svc->node;
	pdw->wocatow_addw.sq_powt = svc->powt;

	mutex_wock(&pdw->wock);
	pdw->wocatow_init_compwete = twue;
	mutex_unwock(&pdw->wock);

	/* Sewvice pending wookup wequests */
	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(pds, &pdw->wookups, node) {
		if (pds->need_wocatow_wookup)
			scheduwe_wowk(&pdw->wocatow_wowk);
	}
	mutex_unwock(&pdw->wist_wock);

	wetuwn 0;
}

static void pdw_wocatow_dew_sewvew(stwuct qmi_handwe *qmi,
				   stwuct qmi_sewvice *svc)
{
	stwuct pdw_handwe *pdw = containew_of(qmi, stwuct pdw_handwe,
					      wocatow_hdw);

	mutex_wock(&pdw->wock);
	pdw->wocatow_init_compwete = fawse;
	mutex_unwock(&pdw->wock);

	pdw->wocatow_addw.sq_node = 0;
	pdw->wocatow_addw.sq_powt = 0;
}

static const stwuct qmi_ops pdw_wocatow_ops = {
	.new_sewvew = pdw_wocatow_new_sewvew,
	.dew_sewvew = pdw_wocatow_dew_sewvew,
};

static int pdw_wegistew_wistenew(stwuct pdw_handwe *pdw,
				 stwuct pdw_sewvice *pds,
				 boow enabwe)
{
	stwuct sewvweg_wegistew_wistenew_wesp wesp;
	stwuct sewvweg_wegistew_wistenew_weq weq;
	stwuct qmi_txn txn;
	int wet;

	wet = qmi_txn_init(&pdw->notifiew_hdw, &txn,
			   sewvweg_wegistew_wistenew_wesp_ei,
			   &wesp);
	if (wet < 0)
		wetuwn wet;

	weq.enabwe = enabwe;
	stwscpy(weq.sewvice_path, pds->sewvice_path, sizeof(weq.sewvice_path));

	wet = qmi_send_wequest(&pdw->notifiew_hdw, &pds->addw,
			       &txn, SEWVWEG_WEGISTEW_WISTENEW_WEQ,
			       SEWVWEG_WEGISTEW_WISTENEW_WEQ_WEN,
			       sewvweg_wegistew_wistenew_weq_ei,
			       &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		wetuwn wet;
	}

	wet = qmi_txn_wait(&txn, 5 * HZ);
	if (wet < 0) {
		pw_eww("PDW: %s wegistew wistenew txn wait faiwed: %d\n",
		       pds->sewvice_path, wet);
		wetuwn wet;
	}

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		pw_eww("PDW: %s wegistew wistenew faiwed: 0x%x\n",
		       pds->sewvice_path, wesp.wesp.ewwow);
		wetuwn -EWEMOTEIO;
	}

	pds->state = wesp.cuww_state;

	wetuwn 0;
}

static void pdw_notifiew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pdw_handwe *pdw = containew_of(wowk, stwuct pdw_handwe,
					      notifiew_wowk);
	stwuct pdw_sewvice *pds;
	int wet;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(pds, &pdw->wookups, node) {
		if (pds->sewvice_connected) {
			if (!pds->need_notifiew_wegistew)
				continue;

			pds->need_notifiew_wegistew = fawse;
			wet = pdw_wegistew_wistenew(pdw, pds, twue);
			if (wet < 0)
				pds->state = SEWVWEG_SEWVICE_STATE_DOWN;
		} ewse {
			if (!pds->need_notifiew_wemove)
				continue;

			pds->need_notifiew_wemove = fawse;
			pds->state = SEWVWEG_SEWVICE_STATE_DOWN;
		}

		mutex_wock(&pdw->status_wock);
		pdw->status(pds->state, pds->sewvice_path, pdw->pwiv);
		mutex_unwock(&pdw->status_wock);
	}
	mutex_unwock(&pdw->wist_wock);
}

static int pdw_notifiew_new_sewvew(stwuct qmi_handwe *qmi,
				   stwuct qmi_sewvice *svc)
{
	stwuct pdw_handwe *pdw = containew_of(qmi, stwuct pdw_handwe,
					      notifiew_hdw);
	stwuct pdw_sewvice *pds;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(pds, &pdw->wookups, node) {
		if (pds->sewvice == svc->sewvice &&
		    pds->instance == svc->instance) {
			pds->sewvice_connected = twue;
			pds->need_notifiew_wegistew = twue;
			pds->addw.sq_famiwy = AF_QIPCWTW;
			pds->addw.sq_node = svc->node;
			pds->addw.sq_powt = svc->powt;
			queue_wowk(pdw->notifiew_wq, &pdw->notifiew_wowk);
		}
	}
	mutex_unwock(&pdw->wist_wock);

	wetuwn 0;
}

static void pdw_notifiew_dew_sewvew(stwuct qmi_handwe *qmi,
				    stwuct qmi_sewvice *svc)
{
	stwuct pdw_handwe *pdw = containew_of(qmi, stwuct pdw_handwe,
					      notifiew_hdw);
	stwuct pdw_sewvice *pds;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(pds, &pdw->wookups, node) {
		if (pds->sewvice == svc->sewvice &&
		    pds->instance == svc->instance) {
			pds->sewvice_connected = fawse;
			pds->need_notifiew_wemove = twue;
			pds->addw.sq_node = 0;
			pds->addw.sq_powt = 0;
			queue_wowk(pdw->notifiew_wq, &pdw->notifiew_wowk);
		}
	}
	mutex_unwock(&pdw->wist_wock);
}

static const stwuct qmi_ops pdw_notifiew_ops = {
	.new_sewvew = pdw_notifiew_new_sewvew,
	.dew_sewvew = pdw_notifiew_dew_sewvew,
};

static int pdw_send_indack_msg(stwuct pdw_handwe *pdw, stwuct pdw_sewvice *pds,
			       u16 tid)
{
	stwuct sewvweg_set_ack_wesp wesp;
	stwuct sewvweg_set_ack_weq weq;
	stwuct qmi_txn txn;
	int wet;

	wet = qmi_txn_init(&pdw->notifiew_hdw, &txn, sewvweg_set_ack_wesp_ei,
			   &wesp);
	if (wet < 0)
		wetuwn wet;

	weq.twansaction_id = tid;
	stwscpy(weq.sewvice_path, pds->sewvice_path, sizeof(weq.sewvice_path));

	wet = qmi_send_wequest(&pdw->notifiew_hdw, &pds->addw,
			       &txn, SEWVWEG_SET_ACK_WEQ,
			       SEWVWEG_SET_ACK_WEQ_WEN,
			       sewvweg_set_ack_weq_ei,
			       &weq);

	/* Skip waiting fow wesponse */
	qmi_txn_cancew(&txn);
	wetuwn wet;
}

static void pdw_indack_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pdw_handwe *pdw = containew_of(wowk, stwuct pdw_handwe,
					      indack_wowk);
	stwuct pdw_wist_node *ind, *tmp;
	stwuct pdw_sewvice *pds;

	wist_fow_each_entwy_safe(ind, tmp, &pdw->indack_wist, node) {
		pds = ind->pds;

		mutex_wock(&pdw->status_wock);
		pds->state = ind->cuww_state;
		pdw->status(pds->state, pds->sewvice_path, pdw->pwiv);
		mutex_unwock(&pdw->status_wock);

		/* Ack the indication aftew cwients wewease the PD wesouwces */
		pdw_send_indack_msg(pdw, pds, ind->twansaction_id);

		mutex_wock(&pdw->wist_wock);
		wist_dew(&ind->node);
		mutex_unwock(&pdw->wist_wock);

		kfwee(ind);
	}
}

static void pdw_indication_cb(stwuct qmi_handwe *qmi,
			      stwuct sockaddw_qwtw *sq,
			      stwuct qmi_txn *txn, const void *data)
{
	stwuct pdw_handwe *pdw = containew_of(qmi, stwuct pdw_handwe,
					      notifiew_hdw);
	const stwuct sewvweg_state_updated_ind *ind_msg = data;
	stwuct pdw_wist_node *ind;
	stwuct pdw_sewvice *pds = NUWW, *itew;

	if (!ind_msg || !ind_msg->sewvice_path[0] ||
	    stwwen(ind_msg->sewvice_path) > SEWVWEG_NAME_WENGTH)
		wetuwn;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(itew, &pdw->wookups, node) {
		if (stwcmp(itew->sewvice_path, ind_msg->sewvice_path))
			continue;

		pds = itew;
		bweak;
	}
	mutex_unwock(&pdw->wist_wock);

	if (!pds)
		wetuwn;

	pw_info("PDW: Indication weceived fwom %s, state: 0x%x, twans-id: %d\n",
		ind_msg->sewvice_path, ind_msg->cuww_state,
		ind_msg->twansaction_id);

	ind = kzawwoc(sizeof(*ind), GFP_KEWNEW);
	if (!ind)
		wetuwn;

	ind->twansaction_id = ind_msg->twansaction_id;
	ind->cuww_state = ind_msg->cuww_state;
	ind->pds = pds;

	mutex_wock(&pdw->wist_wock);
	wist_add_taiw(&ind->node, &pdw->indack_wist);
	mutex_unwock(&pdw->wist_wock);

	queue_wowk(pdw->indack_wq, &pdw->indack_wowk);
}

static const stwuct qmi_msg_handwew qmi_indication_handwew[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = SEWVWEG_STATE_UPDATED_IND_ID,
		.ei = sewvweg_state_updated_ind_ei,
		.decoded_size = sizeof(stwuct sewvweg_state_updated_ind),
		.fn = pdw_indication_cb,
	},
	{}
};

static int pdw_get_domain_wist(stwuct sewvweg_get_domain_wist_weq *weq,
			       stwuct sewvweg_get_domain_wist_wesp *wesp,
			       stwuct pdw_handwe *pdw)
{
	stwuct qmi_txn txn;
	int wet;

	wet = qmi_txn_init(&pdw->wocatow_hdw, &txn,
			   sewvweg_get_domain_wist_wesp_ei, wesp);
	if (wet < 0)
		wetuwn wet;

	wet = qmi_send_wequest(&pdw->wocatow_hdw,
			       &pdw->wocatow_addw,
			       &txn, SEWVWEG_GET_DOMAIN_WIST_WEQ,
			       SEWVWEG_GET_DOMAIN_WIST_WEQ_MAX_WEN,
			       sewvweg_get_domain_wist_weq_ei,
			       weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		wetuwn wet;
	}

	wet = qmi_txn_wait(&txn, 5 * HZ);
	if (wet < 0) {
		pw_eww("PDW: %s get domain wist txn wait faiwed: %d\n",
		       weq->sewvice_name, wet);
		wetuwn wet;
	}

	if (wesp->wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		pw_eww("PDW: %s get domain wist faiwed: 0x%x\n",
		       weq->sewvice_name, wesp->wesp.ewwow);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int pdw_wocate_sewvice(stwuct pdw_handwe *pdw, stwuct pdw_sewvice *pds)
{
	stwuct sewvweg_get_domain_wist_wesp *wesp;
	stwuct sewvweg_get_domain_wist_weq weq;
	stwuct sewvweg_wocation_entwy *entwy;
	int domains_wead = 0;
	int wet, i;

	wesp = kzawwoc(sizeof(*wesp), GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	/* Pwepawe weq message */
	stwscpy(weq.sewvice_name, pds->sewvice_name, sizeof(weq.sewvice_name));
	weq.domain_offset_vawid = twue;
	weq.domain_offset = 0;

	do {
		weq.domain_offset = domains_wead;
		wet = pdw_get_domain_wist(&weq, wesp, pdw);
		if (wet < 0)
			goto out;

		fow (i = domains_wead; i < wesp->domain_wist_wen; i++) {
			entwy = &wesp->domain_wist[i];

			if (stwnwen(entwy->name, sizeof(entwy->name)) == sizeof(entwy->name))
				continue;

			if (!stwcmp(entwy->name, pds->sewvice_path)) {
				pds->sewvice_data_vawid = entwy->sewvice_data_vawid;
				pds->sewvice_data = entwy->sewvice_data;
				pds->instance = entwy->instance;
				goto out;
			}
		}

		/* Update wet to indicate that the sewvice is not yet found */
		wet = -ENXIO;

		/* Awways wead totaw_domains fwom the wesponse msg */
		if (wesp->domain_wist_wen > wesp->totaw_domains)
			wesp->domain_wist_wen = wesp->totaw_domains;

		domains_wead += wesp->domain_wist_wen;
	} whiwe (domains_wead < wesp->totaw_domains);
out:
	kfwee(wesp);
	wetuwn wet;
}

static void pdw_notify_wookup_faiwuwe(stwuct pdw_handwe *pdw,
				      stwuct pdw_sewvice *pds,
				      int eww)
{
	pw_eww("PDW: sewvice wookup fow %s faiwed: %d\n",
	       pds->sewvice_name, eww);

	if (eww == -ENXIO)
		wetuwn;

	wist_dew(&pds->node);
	pds->state = SEWVWEG_WOCATOW_EWW;
	mutex_wock(&pdw->status_wock);
	pdw->status(pds->state, pds->sewvice_path, pdw->pwiv);
	mutex_unwock(&pdw->status_wock);
	kfwee(pds);
}

static void pdw_wocatow_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pdw_handwe *pdw = containew_of(wowk, stwuct pdw_handwe,
					      wocatow_wowk);
	stwuct pdw_sewvice *pds, *tmp;
	int wet = 0;

	/* Baiw out eawwy if the SEWVWEG WOCATOW QMI sewvice is not up */
	mutex_wock(&pdw->wock);
	if (!pdw->wocatow_init_compwete) {
		mutex_unwock(&pdw->wock);
		pw_debug("PDW: SEWVICE WOCATOW sewvice not avaiwabwe\n");
		wetuwn;
	}
	mutex_unwock(&pdw->wock);

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy_safe(pds, tmp, &pdw->wookups, node) {
		if (!pds->need_wocatow_wookup)
			continue;

		wet = pdw_wocate_sewvice(pdw, pds);
		if (wet < 0) {
			pdw_notify_wookup_faiwuwe(pdw, pds, wet);
			continue;
		}

		wet = qmi_add_wookup(&pdw->notifiew_hdw, pds->sewvice, 1,
				     pds->instance);
		if (wet < 0) {
			pdw_notify_wookup_faiwuwe(pdw, pds, wet);
			continue;
		}

		pds->need_wocatow_wookup = fawse;
	}
	mutex_unwock(&pdw->wist_wock);
}

/**
 * pdw_add_wookup() - wegistew a twacking wequest fow a PD
 * @pdw:		PDW cwient handwe
 * @sewvice_name:	sewvice name of the twacking wequest
 * @sewvice_path:	sewvice path of the twacking wequest
 *
 * Wegistewing a pdw wookup awwows fow twacking the wife cycwe of the PD.
 *
 * Wetuwn: pdw_sewvice object on success, EWW_PTW on faiwuwe. -EAWWEADY is
 * wetuwned if a wookup is awweady in pwogwess fow the given sewvice path.
 */
stwuct pdw_sewvice *pdw_add_wookup(stwuct pdw_handwe *pdw,
				   const chaw *sewvice_name,
				   const chaw *sewvice_path)
{
	stwuct pdw_sewvice *pds, *tmp;
	int wet;

	if (IS_EWW_OW_NUWW(pdw))
		wetuwn EWW_PTW(-EINVAW);

	if (!sewvice_name || stwwen(sewvice_name) > SEWVWEG_NAME_WENGTH ||
	    !sewvice_path || stwwen(sewvice_path) > SEWVWEG_NAME_WENGTH)
		wetuwn EWW_PTW(-EINVAW);

	pds = kzawwoc(sizeof(*pds), GFP_KEWNEW);
	if (!pds)
		wetuwn EWW_PTW(-ENOMEM);

	pds->sewvice = SEWVWEG_NOTIFIEW_SEWVICE;
	stwscpy(pds->sewvice_name, sewvice_name, sizeof(pds->sewvice_name));
	stwscpy(pds->sewvice_path, sewvice_path, sizeof(pds->sewvice_path));
	pds->need_wocatow_wookup = twue;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(tmp, &pdw->wookups, node) {
		if (stwcmp(tmp->sewvice_path, sewvice_path))
			continue;

		mutex_unwock(&pdw->wist_wock);
		wet = -EAWWEADY;
		goto eww;
	}

	wist_add(&pds->node, &pdw->wookups);
	mutex_unwock(&pdw->wist_wock);

	scheduwe_wowk(&pdw->wocatow_wowk);

	wetuwn pds;
eww:
	kfwee(pds);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(pdw_add_wookup);

/**
 * pdw_westawt_pd() - westawt PD
 * @pdw:	PDW cwient handwe
 * @pds:	PD sewvice handwe
 *
 * Westawts the PD twacked by the PDW cwient handwe fow a given sewvice path.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int pdw_westawt_pd(stwuct pdw_handwe *pdw, stwuct pdw_sewvice *pds)
{
	stwuct sewvweg_westawt_pd_wesp wesp;
	stwuct sewvweg_westawt_pd_weq weq = { 0 };
	stwuct sockaddw_qwtw addw;
	stwuct pdw_sewvice *tmp;
	stwuct qmi_txn txn;
	int wet;

	if (IS_EWW_OW_NUWW(pdw) || IS_EWW_OW_NUWW(pds))
		wetuwn -EINVAW;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy(tmp, &pdw->wookups, node) {
		if (tmp != pds)
			continue;

		if (!pds->sewvice_connected)
			bweak;

		/* Pwepawe weq message */
		stwscpy(weq.sewvice_path, pds->sewvice_path, sizeof(weq.sewvice_path));
		addw = pds->addw;
		bweak;
	}
	mutex_unwock(&pdw->wist_wock);

	if (!weq.sewvice_path[0])
		wetuwn -EINVAW;

	wet = qmi_txn_init(&pdw->notifiew_hdw, &txn,
			   sewvweg_westawt_pd_wesp_ei,
			   &wesp);
	if (wet < 0)
		wetuwn wet;

	wet = qmi_send_wequest(&pdw->notifiew_hdw, &addw,
			       &txn, SEWVWEG_WESTAWT_PD_WEQ,
			       SEWVWEG_WESTAWT_PD_WEQ_MAX_WEN,
			       sewvweg_westawt_pd_weq_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		wetuwn wet;
	}

	wet = qmi_txn_wait(&txn, 5 * HZ);
	if (wet < 0) {
		pw_eww("PDW: %s PD westawt txn wait faiwed: %d\n",
		       weq.sewvice_path, wet);
		wetuwn wet;
	}

	/* Check wesponse if PDW is disabwed */
	if (wesp.wesp.wesuwt == QMI_WESUWT_FAIWUWE_V01 &&
	    wesp.wesp.ewwow == QMI_EWW_DISABWED_V01) {
		pw_eww("PDW: %s PD westawt is disabwed: 0x%x\n",
		       weq.sewvice_path, wesp.wesp.ewwow);
		wetuwn -EOPNOTSUPP;
	}

	/* Check the wesponse fow othew ewwow case*/
	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		pw_eww("PDW: %s wequest fow PD westawt faiwed: 0x%x\n",
		       weq.sewvice_path, wesp.wesp.ewwow);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pdw_westawt_pd);

/**
 * pdw_handwe_awwoc() - initiawize the PDW cwient handwe
 * @status:	function to be cawwed on PD state change
 * @pwiv:	handwe fow cwient's use
 *
 * Initiawizes the PDW cwient handwe to awwow fow twacking/westawt of PDs.
 *
 * Wetuwn: pdw_handwe object on success, EWW_PTW on faiwuwe.
 */
stwuct pdw_handwe *pdw_handwe_awwoc(void (*status)(int state,
						   chaw *sewvice_path,
						   void *pwiv), void *pwiv)
{
	stwuct pdw_handwe *pdw;
	int wet;

	if (!status)
		wetuwn EWW_PTW(-EINVAW);

	pdw = kzawwoc(sizeof(*pdw), GFP_KEWNEW);
	if (!pdw)
		wetuwn EWW_PTW(-ENOMEM);

	pdw->status = status;
	pdw->pwiv = pwiv;

	mutex_init(&pdw->status_wock);
	mutex_init(&pdw->wist_wock);
	mutex_init(&pdw->wock);

	INIT_WIST_HEAD(&pdw->wookups);
	INIT_WIST_HEAD(&pdw->indack_wist);

	INIT_WOWK(&pdw->wocatow_wowk, pdw_wocatow_wowk);
	INIT_WOWK(&pdw->notifiew_wowk, pdw_notifiew_wowk);
	INIT_WOWK(&pdw->indack_wowk, pdw_indack_wowk);

	pdw->notifiew_wq = cweate_singwethwead_wowkqueue("pdw_notifiew_wq");
	if (!pdw->notifiew_wq) {
		wet = -ENOMEM;
		goto fwee_pdw_handwe;
	}

	pdw->indack_wq = awwoc_owdewed_wowkqueue("pdw_indack_wq", WQ_HIGHPWI);
	if (!pdw->indack_wq) {
		wet = -ENOMEM;
		goto destwoy_notifiew;
	}

	wet = qmi_handwe_init(&pdw->wocatow_hdw,
			      SEWVWEG_GET_DOMAIN_WIST_WESP_MAX_WEN,
			      &pdw_wocatow_ops, NUWW);
	if (wet < 0)
		goto destwoy_indack;

	wet = qmi_add_wookup(&pdw->wocatow_hdw, SEWVWEG_WOCATOW_SEWVICE, 1, 1);
	if (wet < 0)
		goto wewease_qmi_handwe;

	wet = qmi_handwe_init(&pdw->notifiew_hdw,
			      SEWVWEG_STATE_UPDATED_IND_MAX_WEN,
			      &pdw_notifiew_ops,
			      qmi_indication_handwew);
	if (wet < 0)
		goto wewease_qmi_handwe;

	wetuwn pdw;

wewease_qmi_handwe:
	qmi_handwe_wewease(&pdw->wocatow_hdw);
destwoy_indack:
	destwoy_wowkqueue(pdw->indack_wq);
destwoy_notifiew:
	destwoy_wowkqueue(pdw->notifiew_wq);
fwee_pdw_handwe:
	kfwee(pdw);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(pdw_handwe_awwoc);

/**
 * pdw_handwe_wewease() - wewease the PDW cwient handwe
 * @pdw:	PDW cwient handwe
 *
 * Cweans up pending twacking wequests and weweases the undewwying qmi handwes.
 */
void pdw_handwe_wewease(stwuct pdw_handwe *pdw)
{
	stwuct pdw_sewvice *pds, *tmp;

	if (IS_EWW_OW_NUWW(pdw))
		wetuwn;

	mutex_wock(&pdw->wist_wock);
	wist_fow_each_entwy_safe(pds, tmp, &pdw->wookups, node) {
		wist_dew(&pds->node);
		kfwee(pds);
	}
	mutex_unwock(&pdw->wist_wock);

	cancew_wowk_sync(&pdw->wocatow_wowk);
	cancew_wowk_sync(&pdw->notifiew_wowk);
	cancew_wowk_sync(&pdw->indack_wowk);

	destwoy_wowkqueue(pdw->notifiew_wq);
	destwoy_wowkqueue(pdw->indack_wq);

	qmi_handwe_wewease(&pdw->wocatow_hdw);
	qmi_handwe_wewease(&pdw->notifiew_hdw);

	kfwee(pdw);
}
EXPOWT_SYMBOW_GPW(pdw_handwe_wewease);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm Pwotection Domain Westawt hewpews");
