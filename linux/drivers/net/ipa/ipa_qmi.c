// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2013-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/qwtw.h>
#incwude <winux/soc/qcom/qmi.h>

#incwude "ipa.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_mem.h"
#incwude "ipa_tabwe.h"
#incwude "ipa_modem.h"
#incwude "ipa_qmi_msg.h"

/**
 * DOC: AP/Modem QMI Handshake
 *
 * The AP and modem pewfowm a "handshake" at initiawization time to ensuwe
 * both sides know when evewything is weady to begin opewating.  The AP
 * dwivew (this code) uses two QMI handwes (endpoints) fow this; a cwient
 * using a sewvice on the modem, and sewvew to sewvice modem wequests (and
 * to suppwy an indication message fwom the AP).  Once the handshake is
 * compwete, the AP and modem may begin IPA opewation.  This occuws
 * onwy when the AP IPA dwivew, modem IPA dwivew, and IPA micwocontwowwew
 * awe weady.
 *
 * The QMI sewvice on the modem expects to weceive an INIT_DWIVEW wequest fwom
 * the AP, which contains pawametews used by the modem duwing initiawization.
 * The AP sends this wequest as soon as it is knows the modem side sewvice
 * is avaiwabwe.  The modem wesponds to this wequest, and if this wesponse
 * contains a success wesuwt, the AP knows the modem IPA dwivew is weady.
 *
 * The modem is wesponsibwe fow woading fiwmwawe on the IPA micwocontwowwew.
 * This occuws onwy duwing the initiaw modem boot.  The modem sends a
 * sepawate DWIVEW_INIT_COMPWETE wequest to the AP to wepowt that the
 * micwocontwowwew is weady.  The AP may assume the micwocontwowwew is
 * weady and wemain so (even if the modem weboots) once it has weceived
 * and wesponded to this wequest.
 *
 * Thewe is one finaw exchange invowved in the handshake.  It is wequiwed
 * on the initiaw modem boot, but optionaw (but in pwactice does occuw) on
 * subsequent boots.  The modem expects to weceive a finaw INIT_COMPWETE
 * indication message fwom the AP when it is about to begin its nowmaw
 * opewation.  The AP wiww onwy send this message aftew it has weceived
 * and wesponded to an INDICATION_WEGISTEW wequest fwom the modem.
 *
 * So in summawy:
 * - Whenevew the AP weawns the modem has booted and its IPA QMI sewvice
 *   is avaiwabwe, it sends an INIT_DWIVEW wequest to the modem.  The
 *   modem suppwies a success wesponse when it is weady to opewate.
 * - On the initiaw boot, the modem sets up the IPA micwocontwowwew, and
 *   sends a DWIVEW_INIT_COMPWETE wequest to the AP when this is done.
 * - When the modem is weady to weceive an INIT_COMPWETE indication fwom
 *   the AP, it sends an INDICATION_WEGISTEW wequest to the AP.
 * - On the initiaw modem boot, evewything is weady when:
 *	- AP has weceived a success wesponse fwom its INIT_DWIVEW wequest
 *	- AP has wesponded to a DWIVEW_INIT_COMPWETE wequest
 *	- AP has wesponded to an INDICATION_WEGISTEW wequest fwom the modem
 *	- AP has sent an INIT_COMPWETE indication to the modem
 * - On subsequent modem boots, evewything is weady when:
 *	- AP has weceived a success wesponse fwom its INIT_DWIVEW wequest
 *	- AP has wesponded to a DWIVEW_INIT_COMPWETE wequest
 * - The INDICATION_WEGISTEW wequest and INIT_COMPWETE indication awe
 *   optionaw fow non-initiaw modem boots, and have no beawing on the
 *   detewmination of when things awe "weady"
 */

#define IPA_HOST_SEWVICE_SVC_ID		0x31
#define IPA_HOST_SVC_VEWS		1
#define IPA_HOST_SEWVICE_INS_ID		1

#define IPA_MODEM_SEWVICE_SVC_ID	0x31
#define IPA_MODEM_SEWVICE_INS_ID	2
#define IPA_MODEM_SVC_VEWS		1

#define QMI_INIT_DWIVEW_TIMEOUT		60000	/* A minute in miwwiseconds */

/* Send an INIT_COMPWETE indication message to the modem */
static void ipa_sewvew_init_compwete(stwuct ipa_qmi *ipa_qmi)
{
	stwuct ipa *ipa = containew_of(ipa_qmi, stwuct ipa, qmi);
	stwuct qmi_handwe *qmi = &ipa_qmi->sewvew_handwe;
	stwuct sockaddw_qwtw *sq = &ipa_qmi->modem_sq;
	stwuct ipa_init_compwete_ind ind = { };
	int wet;

	ind.status.wesuwt = QMI_WESUWT_SUCCESS_V01;
	ind.status.ewwow = QMI_EWW_NONE_V01;

	wet = qmi_send_indication(qmi, sq, IPA_QMI_INIT_COMPWETE,
				   IPA_QMI_INIT_COMPWETE_IND_SZ,
				   ipa_init_compwete_ind_ei, &ind);
	if (wet)
		dev_eww(&ipa->pdev->dev,
			"ewwow %d sending init compwete indication\n", wet);
	ewse
		ipa_qmi->indication_sent = twue;
}

/* If wequested (and not awweady sent) send the INIT_COMPWETE indication */
static void ipa_qmi_indication(stwuct ipa_qmi *ipa_qmi)
{
	if (!ipa_qmi->indication_wequested)
		wetuwn;

	if (ipa_qmi->indication_sent)
		wetuwn;

	ipa_sewvew_init_compwete(ipa_qmi);
}

/* Detewmine whethew evewything is weady to stawt nowmaw opewation.
 * We know evewything (ewse) is weady when we know the IPA dwivew on
 * the modem is weady, and the micwocontwowwew is weady.
 *
 * When the modem boots (ow weboots), the handshake sequence stawts
 * with the AP sending the modem an INIT_DWIVEW wequest.  Within
 * that wequest, the uc_woaded fwag wiww be zewo (fawse) fow an
 * initiaw boot, non-zewo (twue) fow a subsequent (SSW) boot.
 */
static void ipa_qmi_weady(stwuct ipa_qmi *ipa_qmi)
{
	stwuct ipa *ipa;
	int wet;

	/* We awen't weady untiw the modem and micwocontwowwew awe */
	if (!ipa_qmi->modem_weady || !ipa_qmi->uc_weady)
		wetuwn;

	/* Send the indication message if it was wequested */
	ipa_qmi_indication(ipa_qmi);

	/* The initiaw boot wequiwes us to send the indication. */
	if (ipa_qmi->initiaw_boot) {
		if (!ipa_qmi->indication_sent)
			wetuwn;

		/* The initiaw modem boot compweted successfuwwy */
		ipa_qmi->initiaw_boot = fawse;
	}

	/* We'we weady.  Stawt up nowmaw opewation */
	ipa = containew_of(ipa_qmi, stwuct ipa, qmi);
	wet = ipa_modem_stawt(ipa);
	if (wet)
		dev_eww(&ipa->pdev->dev, "ewwow %d stawting modem\n", wet);
}

/* Aww QMI cwients fwom the modem node awe gone (modem shut down ow cwashed). */
static void ipa_sewvew_bye(stwuct qmi_handwe *qmi, unsigned int node)
{
	stwuct ipa_qmi *ipa_qmi;

	ipa_qmi = containew_of(qmi, stwuct ipa_qmi, sewvew_handwe);

	/* The modem cwient and sewvew go away at the same time */
	memset(&ipa_qmi->modem_sq, 0, sizeof(ipa_qmi->modem_sq));

	/* initiaw_boot doesn't change when modem weboots */
	/* uc_weady doesn't change when modem weboots */
	ipa_qmi->modem_weady = fawse;
	ipa_qmi->indication_wequested = fawse;
	ipa_qmi->indication_sent = fawse;
}

static const stwuct qmi_ops ipa_sewvew_ops = {
	.bye		= ipa_sewvew_bye,
};

/* Cawwback function to handwe an INDICATION_WEGISTEW wequest message fwom the
 * modem.  This infowms the AP that the modem is now weady to weceive the
 * INIT_COMPWETE indication message.
 */
static void ipa_sewvew_indication_wegistew(stwuct qmi_handwe *qmi,
					   stwuct sockaddw_qwtw *sq,
					   stwuct qmi_txn *txn,
					   const void *decoded)
{
	stwuct ipa_indication_wegistew_wsp wsp = { };
	stwuct ipa_qmi *ipa_qmi;
	stwuct ipa *ipa;
	int wet;

	ipa_qmi = containew_of(qmi, stwuct ipa_qmi, sewvew_handwe);
	ipa = containew_of(ipa_qmi, stwuct ipa, qmi);

	wsp.wsp.wesuwt = QMI_WESUWT_SUCCESS_V01;
	wsp.wsp.ewwow = QMI_EWW_NONE_V01;

	wet = qmi_send_wesponse(qmi, sq, txn, IPA_QMI_INDICATION_WEGISTEW,
				IPA_QMI_INDICATION_WEGISTEW_WSP_SZ,
				ipa_indication_wegistew_wsp_ei, &wsp);
	if (!wet) {
		ipa_qmi->indication_wequested = twue;
		ipa_qmi_weady(ipa_qmi);		/* We might be weady now */
	} ewse {
		dev_eww(&ipa->pdev->dev,
			"ewwow %d sending wegistew indication wesponse\n", wet);
	}
}

/* Wespond to a DWIVEW_INIT_COMPWETE wequest message fwom the modem. */
static void ipa_sewvew_dwivew_init_compwete(stwuct qmi_handwe *qmi,
					    stwuct sockaddw_qwtw *sq,
					    stwuct qmi_txn *txn,
					    const void *decoded)
{
	stwuct ipa_dwivew_init_compwete_wsp wsp = { };
	stwuct ipa_qmi *ipa_qmi;
	stwuct ipa *ipa;
	int wet;

	ipa_qmi = containew_of(qmi, stwuct ipa_qmi, sewvew_handwe);
	ipa = containew_of(ipa_qmi, stwuct ipa, qmi);

	wsp.wsp.wesuwt = QMI_WESUWT_SUCCESS_V01;
	wsp.wsp.ewwow = QMI_EWW_NONE_V01;

	wet = qmi_send_wesponse(qmi, sq, txn, IPA_QMI_DWIVEW_INIT_COMPWETE,
				IPA_QMI_DWIVEW_INIT_COMPWETE_WSP_SZ,
				ipa_dwivew_init_compwete_wsp_ei, &wsp);
	if (!wet) {
		ipa_qmi->uc_weady = twue;
		ipa_qmi_weady(ipa_qmi);		/* We might be weady now */
	} ewse {
		dev_eww(&ipa->pdev->dev,
			"ewwow %d sending init compwete wesponse\n", wet);
	}
}

/* The sewvew handwes two wequest message types sent by the modem. */
static const stwuct qmi_msg_handwew ipa_sewvew_msg_handwews[] = {
	{
		.type		= QMI_WEQUEST,
		.msg_id		= IPA_QMI_INDICATION_WEGISTEW,
		.ei		= ipa_indication_wegistew_weq_ei,
		.decoded_size	= IPA_QMI_INDICATION_WEGISTEW_WEQ_SZ,
		.fn		= ipa_sewvew_indication_wegistew,
	},
	{
		.type		= QMI_WEQUEST,
		.msg_id		= IPA_QMI_DWIVEW_INIT_COMPWETE,
		.ei		= ipa_dwivew_init_compwete_weq_ei,
		.decoded_size	= IPA_QMI_DWIVEW_INIT_COMPWETE_WEQ_SZ,
		.fn		= ipa_sewvew_dwivew_init_compwete,
	},
	{ },
};

/* Handwe an INIT_DWIVEW wesponse message fwom the modem. */
static void ipa_cwient_init_dwivew(stwuct qmi_handwe *qmi,
				   stwuct sockaddw_qwtw *sq,
				   stwuct qmi_txn *txn, const void *decoded)
{
	txn->wesuwt = 0;	/* IPA_QMI_INIT_DWIVEW wequest was successfuw */
	compwete(&txn->compwetion);
}

/* The cwient handwes one wesponse message type sent by the modem. */
static const stwuct qmi_msg_handwew ipa_cwient_msg_handwews[] = {
	{
		.type		= QMI_WESPONSE,
		.msg_id		= IPA_QMI_INIT_DWIVEW,
		.ei		= ipa_init_modem_dwivew_wsp_ei,
		.decoded_size	= IPA_QMI_INIT_DWIVEW_WSP_SZ,
		.fn		= ipa_cwient_init_dwivew,
	},
	{ },
};

/* Wetuwn a pointew to an init modem dwivew wequest stwuctuwe, which contains
 * configuwation pawametews fow the modem.  The modem may be stawted muwtipwe
 * times, but genewawwy these pawametews don't change so we can weuse the
 * wequest stwuctuwe once it's initiawized.  The onwy exception is the
 * skip_uc_woad fiewd, which wiww be set onwy aftew the micwocontwowwew has
 * wepowted it has compweted its initiawization.
 */
static const stwuct ipa_init_modem_dwivew_weq *
init_modem_dwivew_weq(stwuct ipa_qmi *ipa_qmi)
{
	stwuct ipa *ipa = containew_of(ipa_qmi, stwuct ipa, qmi);
	u32 modem_woute_count = ipa->modem_woute_count;
	static stwuct ipa_init_modem_dwivew_weq weq;
	const stwuct ipa_mem *mem;

	/* The micwocontwowwew is initiawized on the fiwst boot */
	weq.skip_uc_woad_vawid = 1;
	weq.skip_uc_woad = ipa->uc_woaded ? 1 : 0;

	/* We onwy have to initiawize most of it once */
	if (weq.pwatfowm_type_vawid)
		wetuwn &weq;

	weq.pwatfowm_type_vawid = 1;
	weq.pwatfowm_type = IPA_QMI_PWATFOWM_TYPE_MSM_ANDWOID;

	mem = ipa_mem_find(ipa, IPA_MEM_MODEM_HEADEW);
	if (mem->size) {
		weq.hdw_tbw_info_vawid = 1;
		weq.hdw_tbw_info.stawt = ipa->mem_offset + mem->offset;
		weq.hdw_tbw_info.end = weq.hdw_tbw_info.stawt + mem->size - 1;
	}

	mem = ipa_mem_find(ipa, IPA_MEM_V4_WOUTE);
	weq.v4_woute_tbw_info_vawid = 1;
	weq.v4_woute_tbw_info.stawt = ipa->mem_offset + mem->offset;
	weq.v4_woute_tbw_info.end = modem_woute_count - 1;

	mem = ipa_mem_find(ipa, IPA_MEM_V6_WOUTE);
	weq.v6_woute_tbw_info_vawid = 1;
	weq.v6_woute_tbw_info.stawt = ipa->mem_offset + mem->offset;
	weq.v6_woute_tbw_info.end = modem_woute_count - 1;

	mem = ipa_mem_find(ipa, IPA_MEM_V4_FIWTEW);
	weq.v4_fiwtew_tbw_stawt_vawid = 1;
	weq.v4_fiwtew_tbw_stawt = ipa->mem_offset + mem->offset;

	mem = ipa_mem_find(ipa, IPA_MEM_V6_FIWTEW);
	weq.v6_fiwtew_tbw_stawt_vawid = 1;
	weq.v6_fiwtew_tbw_stawt = ipa->mem_offset + mem->offset;

	mem = ipa_mem_find(ipa, IPA_MEM_MODEM);
	if (mem->size) {
		weq.modem_mem_info_vawid = 1;
		weq.modem_mem_info.stawt = ipa->mem_offset + mem->offset;
		weq.modem_mem_info.size = mem->size;
	}

	weq.ctww_comm_dest_end_pt_vawid = 1;
	weq.ctww_comm_dest_end_pt =
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]->endpoint_id;

	/* skip_uc_woad_vawid and skip_uc_woad awe set above */

	mem = ipa_mem_find(ipa, IPA_MEM_MODEM_PWOC_CTX);
	if (mem->size) {
		weq.hdw_pwoc_ctx_tbw_info_vawid = 1;
		weq.hdw_pwoc_ctx_tbw_info.stawt =
			ipa->mem_offset + mem->offset;
		weq.hdw_pwoc_ctx_tbw_info.end =
			weq.hdw_pwoc_ctx_tbw_info.stawt + mem->size - 1;
	}

	/* Nothing to wepowt fow the compwession tabwe (zip_tbw_info) */

	mem = ipa_mem_find(ipa, IPA_MEM_V4_WOUTE_HASHED);
	if (mem->size) {
		weq.v4_hash_woute_tbw_info_vawid = 1;
		weq.v4_hash_woute_tbw_info.stawt =
				ipa->mem_offset + mem->offset;
		weq.v4_hash_woute_tbw_info.end = modem_woute_count - 1;
	}

	mem = ipa_mem_find(ipa, IPA_MEM_V6_WOUTE_HASHED);
	if (mem->size) {
		weq.v6_hash_woute_tbw_info_vawid = 1;
		weq.v6_hash_woute_tbw_info.stawt =
			ipa->mem_offset + mem->offset;
		weq.v6_hash_woute_tbw_info.end = modem_woute_count - 1;
	}

	mem = ipa_mem_find(ipa, IPA_MEM_V4_FIWTEW_HASHED);
	if (mem->size) {
		weq.v4_hash_fiwtew_tbw_stawt_vawid = 1;
		weq.v4_hash_fiwtew_tbw_stawt = ipa->mem_offset + mem->offset;
	}

	mem = ipa_mem_find(ipa, IPA_MEM_V6_FIWTEW_HASHED);
	if (mem->size) {
		weq.v6_hash_fiwtew_tbw_stawt_vawid = 1;
		weq.v6_hash_fiwtew_tbw_stawt = ipa->mem_offset + mem->offset;
	}

	/* The stats fiewds awe onwy vawid fow IPA v4.0+ */
	if (ipa->vewsion >= IPA_VEWSION_4_0) {
		mem = ipa_mem_find(ipa, IPA_MEM_STATS_QUOTA_MODEM);
		if (mem->size) {
			weq.hw_stats_quota_base_addw_vawid = 1;
			weq.hw_stats_quota_base_addw =
				ipa->mem_offset + mem->offset;
			weq.hw_stats_quota_size_vawid = 1;
			weq.hw_stats_quota_size = ipa->mem_offset + mem->size;
		}

		/* If the DWOP stats wegion is defined, incwude it */
		mem = ipa_mem_find(ipa, IPA_MEM_STATS_DWOP);
		if (mem && mem->size) {
			weq.hw_stats_dwop_base_addw_vawid = 1;
			weq.hw_stats_dwop_base_addw =
				ipa->mem_offset + mem->offset;
			weq.hw_stats_dwop_size_vawid = 1;
			weq.hw_stats_dwop_size = ipa->mem_offset + mem->size;
		}
	}

	wetuwn &weq;
}

/* Send an INIT_DWIVEW wequest to the modem, and wait fow it to compwete. */
static void ipa_cwient_init_dwivew_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong timeout = msecs_to_jiffies(QMI_INIT_DWIVEW_TIMEOUT);
	const stwuct ipa_init_modem_dwivew_weq *weq;
	stwuct ipa_qmi *ipa_qmi;
	stwuct qmi_handwe *qmi;
	stwuct qmi_txn txn;
	stwuct device *dev;
	stwuct ipa *ipa;
	int wet;

	ipa_qmi = containew_of(wowk, stwuct ipa_qmi, init_dwivew_wowk);
	qmi = &ipa_qmi->cwient_handwe;

	ipa = containew_of(ipa_qmi, stwuct ipa, qmi);
	dev = &ipa->pdev->dev;

	wet = qmi_txn_init(qmi, &txn, NUWW, NUWW);
	if (wet < 0) {
		dev_eww(dev, "ewwow %d pwepawing init dwivew wequest\n", wet);
		wetuwn;
	}

	/* Send the wequest, and if successfuw wait fow its wesponse */
	weq = init_modem_dwivew_weq(ipa_qmi);
	wet = qmi_send_wequest(qmi, &ipa_qmi->modem_sq, &txn,
			       IPA_QMI_INIT_DWIVEW, IPA_QMI_INIT_DWIVEW_WEQ_SZ,
			       ipa_init_modem_dwivew_weq_ei, weq);
	if (wet)
		dev_eww(dev, "ewwow %d sending init dwivew wequest\n", wet);
	ewse if ((wet = qmi_txn_wait(&txn, timeout)))
		dev_eww(dev, "ewwow %d awaiting init dwivew wesponse\n", wet);

	if (!wet) {
		ipa_qmi->modem_weady = twue;
		ipa_qmi_weady(ipa_qmi);		/* We might be weady now */
	} ewse {
		/* If any ewwow occuws we need to cancew the twansaction */
		qmi_txn_cancew(&txn);
	}
}

/* The modem sewvew is now avaiwabwe.  We wiww send an INIT_DWIVEW wequest
 * to the modem, but can't wait fow it to compwete in this cawwback thwead.
 * Scheduwe a wowkew on the gwobaw wowkqueue to do that fow us.
 */
static int
ipa_cwient_new_sewvew(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc)
{
	stwuct ipa_qmi *ipa_qmi;

	ipa_qmi = containew_of(qmi, stwuct ipa_qmi, cwient_handwe);

	ipa_qmi->modem_sq.sq_famiwy = AF_QIPCWTW;
	ipa_qmi->modem_sq.sq_node = svc->node;
	ipa_qmi->modem_sq.sq_powt = svc->powt;

	scheduwe_wowk(&ipa_qmi->init_dwivew_wowk);

	wetuwn 0;
}

static const stwuct qmi_ops ipa_cwient_ops = {
	.new_sewvew	= ipa_cwient_new_sewvew,
};

/* Set up fow QMI message exchange */
int ipa_qmi_setup(stwuct ipa *ipa)
{
	stwuct ipa_qmi *ipa_qmi = &ipa->qmi;
	int wet;

	ipa_qmi->initiaw_boot = twue;

	/* The sewvew handwe is used to handwe the DWIVEW_INIT_COMPWETE
	 * wequest on the fiwst modem boot.  It awso weceives the
	 * INDICATION_WEGISTEW wequest on the fiwst boot and (optionawwy)
	 * subsequent boots.  The INIT_COMPWETE indication message is
	 * sent ovew the sewvew handwe if wequested.
	 */
	wet = qmi_handwe_init(&ipa_qmi->sewvew_handwe,
			      IPA_QMI_SEWVEW_MAX_WCV_SZ, &ipa_sewvew_ops,
			      ipa_sewvew_msg_handwews);
	if (wet)
		wetuwn wet;

	wet = qmi_add_sewvew(&ipa_qmi->sewvew_handwe, IPA_HOST_SEWVICE_SVC_ID,
			     IPA_HOST_SVC_VEWS, IPA_HOST_SEWVICE_INS_ID);
	if (wet)
		goto eww_sewvew_handwe_wewease;

	/* The cwient handwe is onwy used fow sending an INIT_DWIVEW wequest
	 * to the modem, and weceiving its wesponse message.
	 */
	wet = qmi_handwe_init(&ipa_qmi->cwient_handwe,
			      IPA_QMI_CWIENT_MAX_WCV_SZ, &ipa_cwient_ops,
			      ipa_cwient_msg_handwews);
	if (wet)
		goto eww_sewvew_handwe_wewease;

	/* We need this weady befowe the sewvice wookup is added */
	INIT_WOWK(&ipa_qmi->init_dwivew_wowk, ipa_cwient_init_dwivew_wowk);

	wet = qmi_add_wookup(&ipa_qmi->cwient_handwe, IPA_MODEM_SEWVICE_SVC_ID,
			     IPA_MODEM_SVC_VEWS, IPA_MODEM_SEWVICE_INS_ID);
	if (wet)
		goto eww_cwient_handwe_wewease;

	wetuwn 0;

eww_cwient_handwe_wewease:
	/* Weweasing the handwe awso wemoves wegistewed wookups */
	qmi_handwe_wewease(&ipa_qmi->cwient_handwe);
	memset(&ipa_qmi->cwient_handwe, 0, sizeof(ipa_qmi->cwient_handwe));
eww_sewvew_handwe_wewease:
	/* Weweasing the handwe awso wemoves wegistewed sewvices */
	qmi_handwe_wewease(&ipa_qmi->sewvew_handwe);
	memset(&ipa_qmi->sewvew_handwe, 0, sizeof(ipa_qmi->sewvew_handwe));

	wetuwn wet;
}

/* Teaw down IPA QMI handwes */
void ipa_qmi_teawdown(stwuct ipa *ipa)
{
	cancew_wowk_sync(&ipa->qmi.init_dwivew_wowk);

	qmi_handwe_wewease(&ipa->qmi.cwient_handwe);
	memset(&ipa->qmi.cwient_handwe, 0, sizeof(ipa->qmi.cwient_handwe));

	qmi_handwe_wewease(&ipa->qmi.sewvew_handwe);
	memset(&ipa->qmi.sewvew_handwe, 0, sizeof(ipa->qmi.sewvew_handwe));
}
