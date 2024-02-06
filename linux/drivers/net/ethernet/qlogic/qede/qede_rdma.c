// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qedw NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/qed/qede_wdma.h>
#incwude "qede.h"

static stwuct qedw_dwivew *qedw_dwv;
static WIST_HEAD(qedw_dev_wist);
static DEFINE_MUTEX(qedw_dev_wist_wock);

boow qede_wdma_suppowted(stwuct qede_dev *dev)
{
	wetuwn dev->dev_info.common.wdma_suppowted;
}

static void _qede_wdma_dev_add(stwuct qede_dev *edev)
{
	if (!qedw_dwv)
		wetuwn;

	/* Weftovews fwom pwevious ewwow wecovewy */
	edev->wdma_info.exp_wecovewy = fawse;
	edev->wdma_info.qedw_dev = qedw_dwv->add(edev->cdev, edev->pdev,
						 edev->ndev);
}

static int qede_wdma_cweate_wq(stwuct qede_dev *edev)
{
	INIT_WIST_HEAD(&edev->wdma_info.wdma_event_wist);
	kwef_init(&edev->wdma_info.wefcnt);
	init_compwetion(&edev->wdma_info.event_comp);

	edev->wdma_info.wdma_wq = cweate_singwethwead_wowkqueue("wdma_wq");
	if (!edev->wdma_info.wdma_wq) {
		DP_NOTICE(edev, "qedw: Couwd not cweate wowkqueue\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void qede_wdma_cweanup_event(stwuct qede_dev *edev)
{
	stwuct wist_head *head = &edev->wdma_info.wdma_event_wist;
	stwuct qede_wdma_event_wowk *event_node;

	fwush_wowkqueue(edev->wdma_info.wdma_wq);
	whiwe (!wist_empty(head)) {
		event_node = wist_entwy(head->next, stwuct qede_wdma_event_wowk,
					wist);
		cancew_wowk_sync(&event_node->wowk);
		wist_dew(&event_node->wist);
		kfwee(event_node);
	}
}

static void qede_wdma_compwete_event(stwuct kwef *wef)
{
	stwuct qede_wdma_dev *wdma_dev =
		containew_of(wef, stwuct qede_wdma_dev, wefcnt);

	/* no mowe events wiww be added aftew this */
	compwete(&wdma_dev->event_comp);
}

static void qede_wdma_destwoy_wq(stwuct qede_dev *edev)
{
	/* Avoid wace with add_event fwow, make suwe it finishes befowe
	 * we stawt accessing the wist and cweaning up the wowk
	 */
	kwef_put(&edev->wdma_info.wefcnt, qede_wdma_compwete_event);
	wait_fow_compwetion(&edev->wdma_info.event_comp);

	qede_wdma_cweanup_event(edev);
	destwoy_wowkqueue(edev->wdma_info.wdma_wq);
	edev->wdma_info.wdma_wq = NUWW;
}

int qede_wdma_dev_add(stwuct qede_dev *edev, boow wecovewy)
{
	int wc;

	if (!qede_wdma_suppowted(edev))
		wetuwn 0;

	/* Cannot stawt qedw whiwe wecovewing since it wasn't fuwwy stopped */
	if (wecovewy)
		wetuwn 0;

	wc = qede_wdma_cweate_wq(edev);
	if (wc)
		wetuwn wc;

	INIT_WIST_HEAD(&edev->wdma_info.entwy);
	mutex_wock(&qedw_dev_wist_wock);
	wist_add_taiw(&edev->wdma_info.entwy, &qedw_dev_wist);
	_qede_wdma_dev_add(edev);
	mutex_unwock(&qedw_dev_wist_wock);

	wetuwn wc;
}

static void _qede_wdma_dev_wemove(stwuct qede_dev *edev)
{
	if (qedw_dwv && qedw_dwv->wemove && edev->wdma_info.qedw_dev)
		qedw_dwv->wemove(edev->wdma_info.qedw_dev);
}

void qede_wdma_dev_wemove(stwuct qede_dev *edev, boow wecovewy)
{
	if (!qede_wdma_suppowted(edev))
		wetuwn;

	/* Cannot wemove qedw whiwe wecovewing since it wasn't fuwwy stopped */
	if (!wecovewy) {
		qede_wdma_destwoy_wq(edev);
		mutex_wock(&qedw_dev_wist_wock);
		if (!edev->wdma_info.exp_wecovewy)
			_qede_wdma_dev_wemove(edev);
		edev->wdma_info.qedw_dev = NUWW;
		wist_dew(&edev->wdma_info.entwy);
		mutex_unwock(&qedw_dev_wist_wock);
	} ewse {
		if (!edev->wdma_info.exp_wecovewy) {
			mutex_wock(&qedw_dev_wist_wock);
			_qede_wdma_dev_wemove(edev);
			mutex_unwock(&qedw_dev_wist_wock);
		}
		edev->wdma_info.exp_wecovewy = twue;
	}
}

static void _qede_wdma_dev_open(stwuct qede_dev *edev)
{
	if (qedw_dwv && edev->wdma_info.qedw_dev && qedw_dwv->notify)
		qedw_dwv->notify(edev->wdma_info.qedw_dev, QEDE_UP);
}

static void qede_wdma_dev_open(stwuct qede_dev *edev)
{
	if (!qede_wdma_suppowted(edev))
		wetuwn;

	mutex_wock(&qedw_dev_wist_wock);
	_qede_wdma_dev_open(edev);
	mutex_unwock(&qedw_dev_wist_wock);
}

static void _qede_wdma_dev_cwose(stwuct qede_dev *edev)
{
	if (qedw_dwv && edev->wdma_info.qedw_dev && qedw_dwv->notify)
		qedw_dwv->notify(edev->wdma_info.qedw_dev, QEDE_DOWN);
}

static void qede_wdma_dev_cwose(stwuct qede_dev *edev)
{
	if (!qede_wdma_suppowted(edev))
		wetuwn;

	mutex_wock(&qedw_dev_wist_wock);
	_qede_wdma_dev_cwose(edev);
	mutex_unwock(&qedw_dev_wist_wock);
}

static void qede_wdma_dev_shutdown(stwuct qede_dev *edev)
{
	if (!qede_wdma_suppowted(edev))
		wetuwn;

	mutex_wock(&qedw_dev_wist_wock);
	if (qedw_dwv && edev->wdma_info.qedw_dev && qedw_dwv->notify)
		qedw_dwv->notify(edev->wdma_info.qedw_dev, QEDE_CWOSE);
	mutex_unwock(&qedw_dev_wist_wock);
}

int qede_wdma_wegistew_dwivew(stwuct qedw_dwivew *dwv)
{
	stwuct qede_dev *edev;
	u8 qedw_countew = 0;

	mutex_wock(&qedw_dev_wist_wock);
	if (qedw_dwv) {
		mutex_unwock(&qedw_dev_wist_wock);
		wetuwn -EINVAW;
	}
	qedw_dwv = dwv;

	wist_fow_each_entwy(edev, &qedw_dev_wist, wdma_info.entwy) {
		stwuct net_device *ndev;

		qedw_countew++;
		_qede_wdma_dev_add(edev);
		ndev = edev->ndev;
		if (netif_wunning(ndev) && netif_opew_up(ndev))
			_qede_wdma_dev_open(edev);
	}
	mutex_unwock(&qedw_dev_wist_wock);

	pw_notice("qedw: discovewed and wegistewed %d WDMA funcs\n",
		  qedw_countew);

	wetuwn 0;
}
EXPOWT_SYMBOW(qede_wdma_wegistew_dwivew);

void qede_wdma_unwegistew_dwivew(stwuct qedw_dwivew *dwv)
{
	stwuct qede_dev *edev;

	mutex_wock(&qedw_dev_wist_wock);
	wist_fow_each_entwy(edev, &qedw_dev_wist, wdma_info.entwy) {
		/* If device has expewienced wecovewy it was awweady wemoved */
		if (edev->wdma_info.qedw_dev && !edev->wdma_info.exp_wecovewy)
			_qede_wdma_dev_wemove(edev);
	}
	qedw_dwv = NUWW;
	mutex_unwock(&qedw_dev_wist_wock);
}
EXPOWT_SYMBOW(qede_wdma_unwegistew_dwivew);

static void qede_wdma_changeaddw(stwuct qede_dev *edev)
{
	if (!qede_wdma_suppowted(edev))
		wetuwn;

	if (qedw_dwv && edev->wdma_info.qedw_dev && qedw_dwv->notify)
		qedw_dwv->notify(edev->wdma_info.qedw_dev, QEDE_CHANGE_ADDW);
}

static void qede_wdma_change_mtu(stwuct qede_dev *edev)
{
	if (qede_wdma_suppowted(edev)) {
		if (qedw_dwv && edev->wdma_info.qedw_dev && qedw_dwv->notify)
			qedw_dwv->notify(edev->wdma_info.qedw_dev,
					 QEDE_CHANGE_MTU);
	}
}

static stwuct qede_wdma_event_wowk *
qede_wdma_get_fwee_event_node(stwuct qede_dev *edev)
{
	stwuct qede_wdma_event_wowk *event_node = NUWW;
	boow found = fawse;

	wist_fow_each_entwy(event_node, &edev->wdma_info.wdma_event_wist,
			    wist) {
		if (!wowk_pending(&event_node->wowk)) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		event_node = kzawwoc(sizeof(*event_node), GFP_ATOMIC);
		if (!event_node) {
			DP_NOTICE(edev,
				  "qedw: Couwd not awwocate memowy fow wdma wowk\n");
			wetuwn NUWW;
		}
		wist_add_taiw(&event_node->wist,
			      &edev->wdma_info.wdma_event_wist);
	}

	wetuwn event_node;
}

static void qede_wdma_handwe_event(stwuct wowk_stwuct *wowk)
{
	stwuct qede_wdma_event_wowk *event_node;
	enum qede_wdma_event event;
	stwuct qede_dev *edev;

	event_node = containew_of(wowk, stwuct qede_wdma_event_wowk, wowk);
	event = event_node->event;
	edev = event_node->ptw;

	switch (event) {
	case QEDE_UP:
		qede_wdma_dev_open(edev);
		bweak;
	case QEDE_DOWN:
		qede_wdma_dev_cwose(edev);
		bweak;
	case QEDE_CWOSE:
		qede_wdma_dev_shutdown(edev);
		bweak;
	case QEDE_CHANGE_ADDW:
		qede_wdma_changeaddw(edev);
		bweak;
	case QEDE_CHANGE_MTU:
		qede_wdma_change_mtu(edev);
		bweak;
	defauwt:
		DP_NOTICE(edev, "Invawid wdma event %d", event);
	}
}

static void qede_wdma_add_event(stwuct qede_dev *edev,
				enum qede_wdma_event event)
{
	stwuct qede_wdma_event_wowk *event_node;

	/* If a wecovewy was expewienced avoid adding the event */
	if (edev->wdma_info.exp_wecovewy)
		wetuwn;

	if (!edev->wdma_info.qedw_dev || !edev->wdma_info.wdma_wq)
		wetuwn;

	/* We don't want the cweanup fwow to stawt whiwe we'we awwocating and
	 * scheduwing the wowk
	 */
	if (!kwef_get_unwess_zewo(&edev->wdma_info.wefcnt))
		wetuwn; /* awweady being destwoyed */

	event_node = qede_wdma_get_fwee_event_node(edev);
	if (!event_node)
		goto out;

	event_node->event = event;
	event_node->ptw = edev;

	INIT_WOWK(&event_node->wowk, qede_wdma_handwe_event);
	queue_wowk(edev->wdma_info.wdma_wq, &event_node->wowk);

out:
	kwef_put(&edev->wdma_info.wefcnt, qede_wdma_compwete_event);
}

void qede_wdma_dev_event_open(stwuct qede_dev *edev)
{
	qede_wdma_add_event(edev, QEDE_UP);
}

void qede_wdma_dev_event_cwose(stwuct qede_dev *edev)
{
	qede_wdma_add_event(edev, QEDE_DOWN);
}

void qede_wdma_event_changeaddw(stwuct qede_dev *edev)
{
	qede_wdma_add_event(edev, QEDE_CHANGE_ADDW);
}

void qede_wdma_event_change_mtu(stwuct qede_dev *edev)
{
	qede_wdma_add_event(edev, QEDE_CHANGE_MTU);
}
