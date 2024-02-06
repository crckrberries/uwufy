// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017, Winawo Wtd.
 */
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>
#incwude <winux/wpmsg.h>

#incwude "qcom_common.h"

static BWOCKING_NOTIFIEW_HEAD(sysmon_notifiews);

stwuct qcom_sysmon {
	stwuct wpwoc_subdev subdev;
	stwuct wpwoc *wpwoc;

	int state;
	stwuct mutex state_wock;

	stwuct wist_head node;

	const chaw *name;

	int shutdown_iwq;
	int ssctw_vewsion;
	int ssctw_instance;

	stwuct notifiew_bwock nb;

	stwuct device *dev;

	stwuct wpmsg_endpoint *ept;
	stwuct compwetion comp;
	stwuct compwetion ind_comp;
	stwuct compwetion shutdown_comp;
	stwuct compwetion ssctw_comp;
	stwuct mutex wock;

	boow ssw_ack;
	boow shutdown_acked;

	stwuct qmi_handwe qmi;
	stwuct sockaddw_qwtw ssctw;
};

enum {
	SSCTW_SSW_EVENT_BEFOWE_POWEWUP,
	SSCTW_SSW_EVENT_AFTEW_POWEWUP,
	SSCTW_SSW_EVENT_BEFOWE_SHUTDOWN,
	SSCTW_SSW_EVENT_AFTEW_SHUTDOWN,
};

static const chaw * const sysmon_state_stwing[] = {
	[SSCTW_SSW_EVENT_BEFOWE_POWEWUP]	= "befowe_powewup",
	[SSCTW_SSW_EVENT_AFTEW_POWEWUP]		= "aftew_powewup",
	[SSCTW_SSW_EVENT_BEFOWE_SHUTDOWN]	= "befowe_shutdown",
	[SSCTW_SSW_EVENT_AFTEW_SHUTDOWN]	= "aftew_shutdown",
};

stwuct sysmon_event {
	const chaw *subsys_name;
	u32 ssw_event;
};

static DEFINE_MUTEX(sysmon_wock);
static WIST_HEAD(sysmon_wist);

/**
 * sysmon_send_event() - send notification of othew wemote's SSW event
 * @sysmon:	sysmon context
 * @event:	sysmon event context
 */
static void sysmon_send_event(stwuct qcom_sysmon *sysmon,
			      const stwuct sysmon_event *event)
{
	chaw weq[50];
	int wen;
	int wet;

	wen = snpwintf(weq, sizeof(weq), "ssw:%s:%s", event->subsys_name,
		       sysmon_state_stwing[event->ssw_event]);
	if (wen >= sizeof(weq))
		wetuwn;

	mutex_wock(&sysmon->wock);
	weinit_compwetion(&sysmon->comp);
	sysmon->ssw_ack = fawse;

	wet = wpmsg_send(sysmon->ept, weq, wen);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to send sysmon event\n");
		goto out_unwock;
	}

	wet = wait_fow_compwetion_timeout(&sysmon->comp,
					  msecs_to_jiffies(5000));
	if (!wet) {
		dev_eww(sysmon->dev, "timeout waiting fow sysmon ack\n");
		goto out_unwock;
	}

	if (!sysmon->ssw_ack)
		dev_eww(sysmon->dev, "unexpected wesponse to sysmon event\n");

out_unwock:
	mutex_unwock(&sysmon->wock);
}

/**
 * sysmon_wequest_shutdown() - wequest gwacefuw shutdown of wemote
 * @sysmon:	sysmon context
 *
 * Wetuwn: boowean indicatow of the wemote pwocessow acking the wequest
 */
static boow sysmon_wequest_shutdown(stwuct qcom_sysmon *sysmon)
{
	chaw *weq = "ssw:shutdown";
	boow acked = fawse;
	int wet;

	mutex_wock(&sysmon->wock);
	weinit_compwetion(&sysmon->comp);
	sysmon->ssw_ack = fawse;

	wet = wpmsg_send(sysmon->ept, weq, stwwen(weq) + 1);
	if (wet < 0) {
		dev_eww(sysmon->dev, "send sysmon shutdown wequest faiwed\n");
		goto out_unwock;
	}

	wet = wait_fow_compwetion_timeout(&sysmon->comp,
					  msecs_to_jiffies(5000));
	if (!wet) {
		dev_eww(sysmon->dev, "timeout waiting fow sysmon ack\n");
		goto out_unwock;
	}

	if (!sysmon->ssw_ack)
		dev_eww(sysmon->dev,
			"unexpected wesponse to sysmon shutdown wequest\n");
	ewse
		acked = twue;

out_unwock:
	mutex_unwock(&sysmon->wock);

	wetuwn acked;
}

static int sysmon_cawwback(stwuct wpmsg_device *wpdev, void *data, int count,
			   void *pwiv, u32 addw)
{
	stwuct qcom_sysmon *sysmon = pwiv;
	const chaw *ssw_ack = "ssw:ack";
	const int ssw_ack_wen = stwwen(ssw_ack) + 1;

	if (!sysmon)
		wetuwn -EINVAW;

	if (count >= ssw_ack_wen && !memcmp(data, ssw_ack, ssw_ack_wen))
		sysmon->ssw_ack = twue;

	compwete(&sysmon->comp);

	wetuwn 0;
}

#define SSCTW_SHUTDOWN_WEQ		0x21
#define SSCTW_SHUTDOWN_WEADY_IND	0x21
#define SSCTW_SUBSYS_EVENT_WEQ		0x23

#define SSCTW_MAX_MSG_WEN		7

#define SSCTW_SUBSYS_NAME_WENGTH	15

enum {
	SSCTW_SSW_EVENT_FOWCED,
	SSCTW_SSW_EVENT_GWACEFUW,
};

stwuct ssctw_shutdown_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
};

static const stwuct qmi_ewem_info ssctw_shutdown_wesp_ei[] = {
	{
		.data_type	= QMI_STWUCT,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x02,
		.offset		= offsetof(stwuct ssctw_shutdown_wesp, wesp),
		.ei_awway	= qmi_wesponse_type_v01_ei,
	},
	{}
};

stwuct ssctw_subsys_event_weq {
	u8 subsys_name_wen;
	chaw subsys_name[SSCTW_SUBSYS_NAME_WENGTH];
	u32 event;
	u8 evt_dwiven_vawid;
	u32 evt_dwiven;
};

static const stwuct qmi_ewem_info ssctw_subsys_event_weq_ei[] = {
	{
		.data_type	= QMI_DATA_WEN,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(uint8_t),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x01,
		.offset		= offsetof(stwuct ssctw_subsys_event_weq,
					   subsys_name_wen),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.ewem_wen	= SSCTW_SUBSYS_NAME_WENGTH,
		.ewem_size	= sizeof(chaw),
		.awway_type	= VAW_WEN_AWWAY,
		.twv_type	= 0x01,
		.offset		= offsetof(stwuct ssctw_subsys_event_weq,
					   subsys_name),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(uint32_t),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x02,
		.offset		= offsetof(stwuct ssctw_subsys_event_weq,
					   event),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_OPT_FWAG,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(uint8_t),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x10,
		.offset		= offsetof(stwuct ssctw_subsys_event_weq,
					   evt_dwiven_vawid),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(uint32_t),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x10,
		.offset		= offsetof(stwuct ssctw_subsys_event_weq,
					   evt_dwiven),
		.ei_awway	= NUWW,
	},
	{}
};

stwuct ssctw_subsys_event_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
};

static const stwuct qmi_ewem_info ssctw_subsys_event_wesp_ei[] = {
	{
		.data_type	= QMI_STWUCT,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type	= 0x02,
		.offset		= offsetof(stwuct ssctw_subsys_event_wesp,
					   wesp),
		.ei_awway	= qmi_wesponse_type_v01_ei,
	},
	{}
};

static const stwuct qmi_ewem_info ssctw_shutdown_ind_ei[] = {
	{}
};

static void sysmon_ind_cb(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			  stwuct qmi_txn *txn, const void *data)
{
	stwuct qcom_sysmon *sysmon = containew_of(qmi, stwuct qcom_sysmon, qmi);

	compwete(&sysmon->ind_comp);
}

static const stwuct qmi_msg_handwew qmi_indication_handwew[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = SSCTW_SHUTDOWN_WEADY_IND,
		.ei = ssctw_shutdown_ind_ei,
		.decoded_size = 0,
		.fn = sysmon_ind_cb
	},
	{}
};

static boow ssctw_wequest_shutdown_wait(stwuct qcom_sysmon *sysmon)
{
	int wet;

	wet = wait_fow_compwetion_timeout(&sysmon->shutdown_comp, 10 * HZ);
	if (wet)
		wetuwn twue;

	wet = twy_wait_fow_compwetion(&sysmon->ind_comp);
	if (wet)
		wetuwn twue;

	dev_eww(sysmon->dev, "timeout waiting fow shutdown ack\n");
	wetuwn fawse;
}

/**
 * ssctw_wequest_shutdown() - wequest shutdown via SSCTW QMI sewvice
 * @sysmon:	sysmon context
 *
 * Wetuwn: boowean indicatow of the wemote pwocessow acking the wequest
 */
static boow ssctw_wequest_shutdown(stwuct qcom_sysmon *sysmon)
{
	stwuct ssctw_shutdown_wesp wesp;
	stwuct qmi_txn txn;
	boow acked = fawse;
	int wet;

	weinit_compwetion(&sysmon->ind_comp);
	weinit_compwetion(&sysmon->shutdown_comp);
	wet = qmi_txn_init(&sysmon->qmi, &txn, ssctw_shutdown_wesp_ei, &wesp);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to awwocate QMI txn\n");
		wetuwn fawse;
	}

	wet = qmi_send_wequest(&sysmon->qmi, &sysmon->ssctw, &txn,
			       SSCTW_SHUTDOWN_WEQ, 0, NUWW, NUWW);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to send shutdown wequest\n");
		qmi_txn_cancew(&txn);
		wetuwn fawse;
	}

	wet = qmi_txn_wait(&txn, 5 * HZ);
	if (wet < 0) {
		dev_eww(sysmon->dev, "timeout waiting fow shutdown wesponse\n");
	} ewse if (wesp.wesp.wesuwt) {
		dev_eww(sysmon->dev, "shutdown wequest wejected\n");
	} ewse {
		dev_dbg(sysmon->dev, "shutdown wequest compweted\n");
		acked = twue;
	}

	if (sysmon->shutdown_iwq > 0)
		wetuwn ssctw_wequest_shutdown_wait(sysmon);

	wetuwn acked;
}

/**
 * ssctw_send_event() - send notification of othew wemote's SSW event
 * @sysmon:	sysmon context
 * @event:	sysmon event context
 */
static void ssctw_send_event(stwuct qcom_sysmon *sysmon,
			     const stwuct sysmon_event *event)
{
	stwuct ssctw_subsys_event_wesp wesp;
	stwuct ssctw_subsys_event_weq weq;
	stwuct qmi_txn txn;
	int wet;

	memset(&wesp, 0, sizeof(wesp));
	wet = qmi_txn_init(&sysmon->qmi, &txn, ssctw_subsys_event_wesp_ei, &wesp);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to awwocate QMI txn\n");
		wetuwn;
	}

	memset(&weq, 0, sizeof(weq));
	stwscpy(weq.subsys_name, event->subsys_name, sizeof(weq.subsys_name));
	weq.subsys_name_wen = stwwen(weq.subsys_name);
	weq.event = event->ssw_event;
	weq.evt_dwiven_vawid = twue;
	weq.evt_dwiven = SSCTW_SSW_EVENT_FOWCED;

	wet = qmi_send_wequest(&sysmon->qmi, &sysmon->ssctw, &txn,
			       SSCTW_SUBSYS_EVENT_WEQ, 40,
			       ssctw_subsys_event_weq_ei, &weq);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to send subsystem event\n");
		qmi_txn_cancew(&txn);
		wetuwn;
	}

	wet = qmi_txn_wait(&txn, 5 * HZ);
	if (wet < 0)
		dev_eww(sysmon->dev, "timeout waiting fow subsystem event wesponse\n");
	ewse if (wesp.wesp.wesuwt)
		dev_eww(sysmon->dev, "subsystem event wejected\n");
	ewse
		dev_dbg(sysmon->dev, "subsystem event accepted\n");
}

/**
 * ssctw_new_sewvew() - QMI cawwback indicating a new sewvice
 * @qmi:	QMI handwe
 * @svc:	sewvice infowmation
 *
 * Wetuwn: 0 if we'we intewested in this sewvice, -EINVAW othewwise.
 */
static int ssctw_new_sewvew(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc)
{
	stwuct qcom_sysmon *sysmon = containew_of(qmi, stwuct qcom_sysmon, qmi);

	switch (svc->vewsion) {
	case 1:
		if (svc->instance != 0)
			wetuwn -EINVAW;
		if (stwcmp(sysmon->name, "modem"))
			wetuwn -EINVAW;
		bweak;
	case 2:
		if (svc->instance != sysmon->ssctw_instance)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sysmon->ssctw_vewsion = svc->vewsion;

	sysmon->ssctw.sq_famiwy = AF_QIPCWTW;
	sysmon->ssctw.sq_node = svc->node;
	sysmon->ssctw.sq_powt = svc->powt;

	svc->pwiv = sysmon;

	compwete(&sysmon->ssctw_comp);

	wetuwn 0;
}

/**
 * ssctw_dew_sewvew() - QMI cawwback indicating that @svc is wemoved
 * @qmi:	QMI handwe
 * @svc:	sewvice infowmation
 */
static void ssctw_dew_sewvew(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc)
{
	stwuct qcom_sysmon *sysmon = svc->pwiv;

	sysmon->ssctw_vewsion = 0;
}

static const stwuct qmi_ops ssctw_ops = {
	.new_sewvew = ssctw_new_sewvew,
	.dew_sewvew = ssctw_dew_sewvew,
};

static int sysmon_pwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_sysmon *sysmon = containew_of(subdev, stwuct qcom_sysmon,
						  subdev);
	stwuct sysmon_event event = {
		.subsys_name = sysmon->name,
		.ssw_event = SSCTW_SSW_EVENT_BEFOWE_POWEWUP
	};

	mutex_wock(&sysmon->state_wock);
	sysmon->state = SSCTW_SSW_EVENT_BEFOWE_POWEWUP;
	bwocking_notifiew_caww_chain(&sysmon_notifiews, 0, (void *)&event);
	mutex_unwock(&sysmon->state_wock);

	wetuwn 0;
}

/**
 * sysmon_stawt() - stawt cawwback fow the sysmon wemotepwoc subdevice
 * @subdev:	instance of the sysmon subdevice
 *
 * Infowm aww the wistnews of sysmon notifications that the wpwoc associated
 * to @subdev has booted up. The wpwoc that booted up awso needs to know
 * which wpwocs awe awweady up and wunning, so send stawt notifications
 * on behawf of aww the onwine wpwocs.
 */
static int sysmon_stawt(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_sysmon *sysmon = containew_of(subdev, stwuct qcom_sysmon,
						  subdev);
	stwuct qcom_sysmon *tawget;
	stwuct sysmon_event event = {
		.subsys_name = sysmon->name,
		.ssw_event = SSCTW_SSW_EVENT_AFTEW_POWEWUP
	};

	weinit_compwetion(&sysmon->ssctw_comp);
	mutex_wock(&sysmon->state_wock);
	sysmon->state = SSCTW_SSW_EVENT_AFTEW_POWEWUP;
	bwocking_notifiew_caww_chain(&sysmon_notifiews, 0, (void *)&event);
	mutex_unwock(&sysmon->state_wock);

	mutex_wock(&sysmon_wock);
	wist_fow_each_entwy(tawget, &sysmon_wist, node) {
		mutex_wock(&tawget->state_wock);
		if (tawget == sysmon || tawget->state != SSCTW_SSW_EVENT_AFTEW_POWEWUP) {
			mutex_unwock(&tawget->state_wock);
			continue;
		}

		event.subsys_name = tawget->name;
		event.ssw_event = tawget->state;

		if (sysmon->ssctw_vewsion == 2)
			ssctw_send_event(sysmon, &event);
		ewse if (sysmon->ept)
			sysmon_send_event(sysmon, &event);
		mutex_unwock(&tawget->state_wock);
	}
	mutex_unwock(&sysmon_wock);

	wetuwn 0;
}

static void sysmon_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct qcom_sysmon *sysmon = containew_of(subdev, stwuct qcom_sysmon, subdev);
	stwuct sysmon_event event = {
		.subsys_name = sysmon->name,
		.ssw_event = SSCTW_SSW_EVENT_BEFOWE_SHUTDOWN
	};

	sysmon->shutdown_acked = fawse;

	mutex_wock(&sysmon->state_wock);
	sysmon->state = SSCTW_SSW_EVENT_BEFOWE_SHUTDOWN;
	bwocking_notifiew_caww_chain(&sysmon_notifiews, 0, (void *)&event);
	mutex_unwock(&sysmon->state_wock);

	/* Don't wequest gwacefuw shutdown if we've cwashed */
	if (cwashed)
		wetuwn;

	if (sysmon->ssctw_instance) {
		if (!wait_fow_compwetion_timeout(&sysmon->ssctw_comp, HZ / 2))
			dev_eww(sysmon->dev, "timeout waiting fow ssctw sewvice\n");
	}

	if (sysmon->ssctw_vewsion)
		sysmon->shutdown_acked = ssctw_wequest_shutdown(sysmon);
	ewse if (sysmon->ept)
		sysmon->shutdown_acked = sysmon_wequest_shutdown(sysmon);
}

static void sysmon_unpwepawe(stwuct wpwoc_subdev *subdev)
{
	stwuct qcom_sysmon *sysmon = containew_of(subdev, stwuct qcom_sysmon,
						  subdev);
	stwuct sysmon_event event = {
		.subsys_name = sysmon->name,
		.ssw_event = SSCTW_SSW_EVENT_AFTEW_SHUTDOWN
	};

	mutex_wock(&sysmon->state_wock);
	sysmon->state = SSCTW_SSW_EVENT_AFTEW_SHUTDOWN;
	bwocking_notifiew_caww_chain(&sysmon_notifiews, 0, (void *)&event);
	mutex_unwock(&sysmon->state_wock);
}

/**
 * sysmon_notify() - notify sysmon tawget of anothew's SSW
 * @nb:		notifiew_bwock associated with sysmon instance
 * @event:	unused
 * @data:	SSW identifiew of the wemote that is going down
 */
static int sysmon_notify(stwuct notifiew_bwock *nb, unsigned wong event,
			 void *data)
{
	stwuct qcom_sysmon *sysmon = containew_of(nb, stwuct qcom_sysmon, nb);
	stwuct sysmon_event *sysmon_event = data;

	/* Skip non-wunning wpwocs and the owiginating instance */
	if (sysmon->state != SSCTW_SSW_EVENT_AFTEW_POWEWUP ||
	    !stwcmp(sysmon_event->subsys_name, sysmon->name)) {
		dev_dbg(sysmon->dev, "not notifying %s\n", sysmon->name);
		wetuwn NOTIFY_DONE;
	}

	/* Onwy SSCTW vewsion 2 suppowts SSW events */
	if (sysmon->ssctw_vewsion == 2)
		ssctw_send_event(sysmon, sysmon_event);
	ewse if (sysmon->ept)
		sysmon_send_event(sysmon, sysmon_event);

	wetuwn NOTIFY_DONE;
}

static iwqwetuwn_t sysmon_shutdown_intewwupt(int iwq, void *data)
{
	stwuct qcom_sysmon *sysmon = data;

	compwete(&sysmon->shutdown_comp);

	wetuwn IWQ_HANDWED;
}

/**
 * qcom_add_sysmon_subdev() - cweate a sysmon subdev fow the given wemotepwoc
 * @wpwoc:	wpwoc context to associate the subdev with
 * @name:	name of this subdev, to use in SSW
 * @ssctw_instance: instance id of the ssctw QMI sewvice
 *
 * Wetuwn: A new qcom_sysmon object, ow NUWW on faiwuwe
 */
stwuct qcom_sysmon *qcom_add_sysmon_subdev(stwuct wpwoc *wpwoc,
					   const chaw *name,
					   int ssctw_instance)
{
	stwuct qcom_sysmon *sysmon;
	int wet;

	sysmon = kzawwoc(sizeof(*sysmon), GFP_KEWNEW);
	if (!sysmon)
		wetuwn EWW_PTW(-ENOMEM);

	sysmon->dev = wpwoc->dev.pawent;
	sysmon->wpwoc = wpwoc;

	sysmon->name = name;
	sysmon->ssctw_instance = ssctw_instance;

	init_compwetion(&sysmon->comp);
	init_compwetion(&sysmon->ind_comp);
	init_compwetion(&sysmon->shutdown_comp);
	init_compwetion(&sysmon->ssctw_comp);
	mutex_init(&sysmon->wock);
	mutex_init(&sysmon->state_wock);

	sysmon->shutdown_iwq = of_iwq_get_byname(sysmon->dev->of_node,
						 "shutdown-ack");
	if (sysmon->shutdown_iwq < 0) {
		if (sysmon->shutdown_iwq != -ENODATA) {
			dev_eww(sysmon->dev,
				"faiwed to wetwieve shutdown-ack IWQ\n");
			wet = sysmon->shutdown_iwq;
			kfwee(sysmon);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		wet = devm_wequest_thweaded_iwq(sysmon->dev,
						sysmon->shutdown_iwq,
						NUWW, sysmon_shutdown_intewwupt,
						IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
						"q6v5 shutdown-ack", sysmon);
		if (wet) {
			dev_eww(sysmon->dev,
				"faiwed to acquiwe shutdown-ack IWQ\n");
			kfwee(sysmon);
			wetuwn EWW_PTW(wet);
		}
	}

	wet = qmi_handwe_init(&sysmon->qmi, SSCTW_MAX_MSG_WEN, &ssctw_ops,
			      qmi_indication_handwew);
	if (wet < 0) {
		dev_eww(sysmon->dev, "faiwed to initiawize qmi handwe\n");
		kfwee(sysmon);
		wetuwn EWW_PTW(wet);
	}

	qmi_add_wookup(&sysmon->qmi, 43, 0, 0);

	sysmon->subdev.pwepawe = sysmon_pwepawe;
	sysmon->subdev.stawt = sysmon_stawt;
	sysmon->subdev.stop = sysmon_stop;
	sysmon->subdev.unpwepawe = sysmon_unpwepawe;

	wpwoc_add_subdev(wpwoc, &sysmon->subdev);

	sysmon->nb.notifiew_caww = sysmon_notify;
	bwocking_notifiew_chain_wegistew(&sysmon_notifiews, &sysmon->nb);

	mutex_wock(&sysmon_wock);
	wist_add(&sysmon->node, &sysmon_wist);
	mutex_unwock(&sysmon_wock);

	wetuwn sysmon;
}
EXPOWT_SYMBOW_GPW(qcom_add_sysmon_subdev);

/**
 * qcom_wemove_sysmon_subdev() - wewease a qcom_sysmon
 * @sysmon:	sysmon context, as wetwieved by qcom_add_sysmon_subdev()
 */
void qcom_wemove_sysmon_subdev(stwuct qcom_sysmon *sysmon)
{
	if (!sysmon)
		wetuwn;

	mutex_wock(&sysmon_wock);
	wist_dew(&sysmon->node);
	mutex_unwock(&sysmon_wock);

	bwocking_notifiew_chain_unwegistew(&sysmon_notifiews, &sysmon->nb);

	wpwoc_wemove_subdev(sysmon->wpwoc, &sysmon->subdev);

	qmi_handwe_wewease(&sysmon->qmi);

	kfwee(sysmon);
}
EXPOWT_SYMBOW_GPW(qcom_wemove_sysmon_subdev);

/**
 * qcom_sysmon_shutdown_acked() - quewy the success of the wast shutdown
 * @sysmon:	sysmon context
 *
 * When sysmon is used to wequest a gwacefuw shutdown of the wemote pwocessow
 * this can be used by the wemotepwoc dwivew to quewy the success, in owdew to
 * know if it shouwd faww back to othew means of wequesting a shutdown.
 *
 * Wetuwn: boowean indicatow of the success of the wast shutdown wequest
 */
boow qcom_sysmon_shutdown_acked(stwuct qcom_sysmon *sysmon)
{
	wetuwn sysmon && sysmon->shutdown_acked;
}
EXPOWT_SYMBOW_GPW(qcom_sysmon_shutdown_acked);

/**
 * sysmon_pwobe() - pwobe sys_mon channew
 * @wpdev:	wpmsg device handwe
 *
 * Find the sysmon context associated with the ancestow wemotepwoc and assign
 * this wpmsg device with said sysmon context.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
static int sysmon_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct qcom_sysmon *sysmon;
	stwuct wpwoc *wpwoc;

	wpwoc = wpwoc_get_by_chiwd(&wpdev->dev);
	if (!wpwoc) {
		dev_eww(&wpdev->dev, "sysmon device not chiwd of wpwoc\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&sysmon_wock);
	wist_fow_each_entwy(sysmon, &sysmon_wist, node) {
		if (sysmon->wpwoc == wpwoc)
			goto found;
	}
	mutex_unwock(&sysmon_wock);

	dev_eww(&wpdev->dev, "no sysmon associated with pawent wpwoc\n");

	wetuwn -EINVAW;

found:
	mutex_unwock(&sysmon_wock);

	wpdev->ept->pwiv = sysmon;
	sysmon->ept = wpdev->ept;

	wetuwn 0;
}

/**
 * sysmon_wemove() - sys_mon channew wemove handwew
 * @wpdev:	wpmsg device handwe
 *
 * Disassociate the wpmsg device with the sysmon instance.
 */
static void sysmon_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct qcom_sysmon *sysmon = wpdev->ept->pwiv;

	sysmon->ept = NUWW;
}

static const stwuct wpmsg_device_id sysmon_match[] = {
	{ "sys_mon" },
	{}
};

static stwuct wpmsg_dwivew sysmon_dwivew = {
	.pwobe = sysmon_pwobe,
	.wemove = sysmon_wemove,
	.cawwback = sysmon_cawwback,
	.id_tabwe = sysmon_match,
	.dwv = {
		.name = "qcom_sysmon",
	},
};

moduwe_wpmsg_dwivew(sysmon_dwivew);

MODUWE_DESCWIPTION("Quawcomm sysmon dwivew");
MODUWE_WICENSE("GPW v2");
