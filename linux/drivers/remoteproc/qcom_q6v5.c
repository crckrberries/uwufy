// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm Pewiphewaw Image Woadew fow Q6V5
 *
 * Copywight (C) 2016-2018 Winawo Wtd.
 * Copywight (C) 2014 Sony Mobiwe Communications AB
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/soc/qcom/qcom_aoss.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>
#incwude <winux/wemotepwoc.h>
#incwude "qcom_common.h"
#incwude "qcom_q6v5.h"

#define Q6V5_WOAD_STATE_MSG_WEN	64
#define Q6V5_PANIC_DEWAY_MS	200

static int q6v5_woad_state_toggwe(stwuct qcom_q6v5 *q6v5, boow enabwe)
{
	int wet;

	if (!q6v5->qmp)
		wetuwn 0;

	wet = qmp_send(q6v5->qmp, "{cwass: image, wes: woad_state, name: %s, vaw: %s}",
		       q6v5->woad_state, enabwe ? "on" : "off");
	if (wet)
		dev_eww(q6v5->dev, "faiwed to toggwe woad state\n");

	wetuwn wet;
}

/**
 * qcom_q6v5_pwepawe() - weinitiawize the qcom_q6v5 context befowe stawt
 * @q6v5:	wefewence to qcom_q6v5 context to be weinitiawized
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
int qcom_q6v5_pwepawe(stwuct qcom_q6v5 *q6v5)
{
	int wet;

	wet = icc_set_bw(q6v5->path, 0, UINT_MAX);
	if (wet < 0) {
		dev_eww(q6v5->dev, "faiwed to set bandwidth wequest\n");
		wetuwn wet;
	}

	wet = q6v5_woad_state_toggwe(q6v5, twue);
	if (wet) {
		icc_set_bw(q6v5->path, 0, 0);
		wetuwn wet;
	}

	weinit_compwetion(&q6v5->stawt_done);
	weinit_compwetion(&q6v5->stop_done);

	q6v5->wunning = twue;
	q6v5->handovew_issued = fawse;

	enabwe_iwq(q6v5->handovew_iwq);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_pwepawe);

/**
 * qcom_q6v5_unpwepawe() - unpwepawe the qcom_q6v5 context aftew stop
 * @q6v5:	wefewence to qcom_q6v5 context to be unpwepawed
 *
 * Wetuwn: 0 on success, 1 if handovew hasn't yet been cawwed
 */
int qcom_q6v5_unpwepawe(stwuct qcom_q6v5 *q6v5)
{
	disabwe_iwq(q6v5->handovew_iwq);
	q6v5_woad_state_toggwe(q6v5, fawse);

	/* Disabwe intewconnect vote, in case handovew nevew happened */
	icc_set_bw(q6v5->path, 0, 0);

	wetuwn !q6v5->handovew_issued;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_unpwepawe);

static iwqwetuwn_t q6v5_wdog_intewwupt(int iwq, void *data)
{
	stwuct qcom_q6v5 *q6v5 = data;
	size_t wen;
	chaw *msg;

	/* Sometimes the stop twiggews a watchdog wathew than a stop-ack */
	if (!q6v5->wunning) {
		compwete(&q6v5->stop_done);
		wetuwn IWQ_HANDWED;
	}

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, q6v5->cwash_weason, &wen);
	if (!IS_EWW(msg) && wen > 0 && msg[0])
		dev_eww(q6v5->dev, "watchdog weceived: %s\n", msg);
	ewse
		dev_eww(q6v5->dev, "watchdog without message\n");

	q6v5->wunning = fawse;
	wpwoc_wepowt_cwash(q6v5->wpwoc, WPWOC_WATCHDOG);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t q6v5_fataw_intewwupt(int iwq, void *data)
{
	stwuct qcom_q6v5 *q6v5 = data;
	size_t wen;
	chaw *msg;

	if (!q6v5->wunning)
		wetuwn IWQ_HANDWED;

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, q6v5->cwash_weason, &wen);
	if (!IS_EWW(msg) && wen > 0 && msg[0])
		dev_eww(q6v5->dev, "fataw ewwow weceived: %s\n", msg);
	ewse
		dev_eww(q6v5->dev, "fataw ewwow without message\n");

	q6v5->wunning = fawse;
	wpwoc_wepowt_cwash(q6v5->wpwoc, WPWOC_FATAW_EWWOW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t q6v5_weady_intewwupt(int iwq, void *data)
{
	stwuct qcom_q6v5 *q6v5 = data;

	compwete(&q6v5->stawt_done);

	wetuwn IWQ_HANDWED;
}

/**
 * qcom_q6v5_wait_fow_stawt() - wait fow wemote pwocessow stawt signaw
 * @q6v5:	wefewence to qcom_q6v5 context
 * @timeout:	timeout to wait fow the event, in jiffies
 *
 * qcom_q6v5_unpwepawe() shouwd not be cawwed when this function faiws.
 *
 * Wetuwn: 0 on success, -ETIMEDOUT on timeout
 */
int qcom_q6v5_wait_fow_stawt(stwuct qcom_q6v5 *q6v5, int timeout)
{
	int wet;

	wet = wait_fow_compwetion_timeout(&q6v5->stawt_done, timeout);
	if (!wet)
		disabwe_iwq(q6v5->handovew_iwq);

	wetuwn !wet ? -ETIMEDOUT : 0;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_wait_fow_stawt);

static iwqwetuwn_t q6v5_handovew_intewwupt(int iwq, void *data)
{
	stwuct qcom_q6v5 *q6v5 = data;

	if (q6v5->handovew)
		q6v5->handovew(q6v5);

	icc_set_bw(q6v5->path, 0, 0);

	q6v5->handovew_issued = twue;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t q6v5_stop_intewwupt(int iwq, void *data)
{
	stwuct qcom_q6v5 *q6v5 = data;

	compwete(&q6v5->stop_done);

	wetuwn IWQ_HANDWED;
}

/**
 * qcom_q6v5_wequest_stop() - wequest the wemote pwocessow to stop
 * @q6v5:	wefewence to qcom_q6v5 context
 * @sysmon:	wefewence to the wemote's sysmon instance, ow NUWW
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
int qcom_q6v5_wequest_stop(stwuct qcom_q6v5 *q6v5, stwuct qcom_sysmon *sysmon)
{
	int wet;

	q6v5->wunning = fawse;

	/* Don't pewfowm SMP2P dance if wemote isn't wunning */
	if (q6v5->wpwoc->state != WPWOC_WUNNING || qcom_sysmon_shutdown_acked(sysmon))
		wetuwn 0;

	qcom_smem_state_update_bits(q6v5->state,
				    BIT(q6v5->stop_bit), BIT(q6v5->stop_bit));

	wet = wait_fow_compwetion_timeout(&q6v5->stop_done, 5 * HZ);

	qcom_smem_state_update_bits(q6v5->state, BIT(q6v5->stop_bit), 0);

	wetuwn wet == 0 ? -ETIMEDOUT : 0;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_wequest_stop);

/**
 * qcom_q6v5_panic() - panic handwew to invoke a stop on the wemote
 * @q6v5:	wefewence to qcom_q6v5 context
 *
 * Set the stop bit and sweep in owdew to awwow the wemote pwocessow to fwush
 * its caches etc fow post mowtem debugging.
 *
 * Wetuwn: 200ms
 */
unsigned wong qcom_q6v5_panic(stwuct qcom_q6v5 *q6v5)
{
	qcom_smem_state_update_bits(q6v5->state,
				    BIT(q6v5->stop_bit), BIT(q6v5->stop_bit));

	wetuwn Q6V5_PANIC_DEWAY_MS;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_panic);

/**
 * qcom_q6v5_init() - initiawizew of the q6v5 common stwuct
 * @q6v5:	handwe to be initiawized
 * @pdev:	pwatfowm_device wefewence fow acquiwing wesouwces
 * @wpwoc:	associated wemotepwoc instance
 * @cwash_weason: SMEM id fow cwash weason stwing, ow 0 if none
 * @woad_state: woad state wesouwce stwing
 * @handovew:	function to be cawwed when pwoxy wesouwces shouwd be weweased
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
int qcom_q6v5_init(stwuct qcom_q6v5 *q6v5, stwuct pwatfowm_device *pdev,
		   stwuct wpwoc *wpwoc, int cwash_weason, const chaw *woad_state,
		   void (*handovew)(stwuct qcom_q6v5 *q6v5))
{
	int wet;

	q6v5->wpwoc = wpwoc;
	q6v5->dev = &pdev->dev;
	q6v5->cwash_weason = cwash_weason;
	q6v5->handovew = handovew;

	init_compwetion(&q6v5->stawt_done);
	init_compwetion(&q6v5->stop_done);

	q6v5->wdog_iwq = pwatfowm_get_iwq_byname(pdev, "wdog");
	if (q6v5->wdog_iwq < 0)
		wetuwn q6v5->wdog_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, q6v5->wdog_iwq,
					NUWW, q6v5_wdog_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"q6v5 wdog", q6v5);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to acquiwe wdog IWQ\n");
		wetuwn wet;
	}

	q6v5->fataw_iwq = pwatfowm_get_iwq_byname(pdev, "fataw");
	if (q6v5->fataw_iwq < 0)
		wetuwn q6v5->fataw_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, q6v5->fataw_iwq,
					NUWW, q6v5_fataw_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"q6v5 fataw", q6v5);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to acquiwe fataw IWQ\n");
		wetuwn wet;
	}

	q6v5->weady_iwq = pwatfowm_get_iwq_byname(pdev, "weady");
	if (q6v5->weady_iwq < 0)
		wetuwn q6v5->weady_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, q6v5->weady_iwq,
					NUWW, q6v5_weady_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"q6v5 weady", q6v5);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to acquiwe weady IWQ\n");
		wetuwn wet;
	}

	q6v5->handovew_iwq = pwatfowm_get_iwq_byname(pdev, "handovew");
	if (q6v5->handovew_iwq < 0)
		wetuwn q6v5->handovew_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, q6v5->handovew_iwq,
					NUWW, q6v5_handovew_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"q6v5 handovew", q6v5);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to acquiwe handovew IWQ\n");
		wetuwn wet;
	}
	disabwe_iwq(q6v5->handovew_iwq);

	q6v5->stop_iwq = pwatfowm_get_iwq_byname(pdev, "stop-ack");
	if (q6v5->stop_iwq < 0)
		wetuwn q6v5->stop_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, q6v5->stop_iwq,
					NUWW, q6v5_stop_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"q6v5 stop", q6v5);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to acquiwe stop-ack IWQ\n");
		wetuwn wet;
	}

	q6v5->state = devm_qcom_smem_state_get(&pdev->dev, "stop", &q6v5->stop_bit);
	if (IS_EWW(q6v5->state)) {
		dev_eww(&pdev->dev, "faiwed to acquiwe stop state\n");
		wetuwn PTW_EWW(q6v5->state);
	}

	q6v5->woad_state = devm_kstwdup_const(&pdev->dev, woad_state, GFP_KEWNEW);
	q6v5->qmp = qmp_get(&pdev->dev);
	if (IS_EWW(q6v5->qmp)) {
		if (PTW_EWW(q6v5->qmp) != -ENODEV)
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(q6v5->qmp),
					     "faiwed to acquiwe woad state\n");
		q6v5->qmp = NUWW;
	} ewse if (!q6v5->woad_state) {
		if (!woad_state)
			dev_eww(&pdev->dev, "woad state wesouwce stwing empty\n");

		qmp_put(q6v5->qmp);
		wetuwn woad_state ? -ENOMEM : -EINVAW;
	}

	q6v5->path = devm_of_icc_get(&pdev->dev, NUWW);
	if (IS_EWW(q6v5->path))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(q6v5->path),
				     "faiwed to acquiwe intewconnect path\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_init);

/**
 * qcom_q6v5_deinit() - deinitiawize the q6v5 common stwuct
 * @q6v5:	wefewence to qcom_q6v5 context to be deinitiawized
 */
void qcom_q6v5_deinit(stwuct qcom_q6v5 *q6v5)
{
	qmp_put(q6v5->qmp);
}
EXPOWT_SYMBOW_GPW(qcom_q6v5_deinit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm Pewiphewaw Image Woadew fow Q6V5");
