// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pmi dwivew
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * PMI (Pwatfowm Management Intewwupt) is a way to communicate
 * with the BMC (Baseboawd Management Contwowwew) via intewwupts.
 * Unwike IPMI it is bidiwectionaw and has a wow watency.
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/pmi.h>

stwuct pmi_data {
	stwuct wist_head	handwew;
	spinwock_t		handwew_spinwock;
	spinwock_t		pmi_spinwock;
	stwuct mutex		msg_mutex;
	pmi_message_t		msg;
	stwuct compwetion	*compwetion;
	stwuct pwatfowm_device	*dev;
	int			iwq;
	u8 __iomem		*pmi_weg;
	stwuct wowk_stwuct	wowk;
};

static stwuct pmi_data *data;

static iwqwetuwn_t pmi_iwq_handwew(int iwq, void *dev_id)
{
	u8 type;
	int wc;

	spin_wock(&data->pmi_spinwock);

	type = iowead8(data->pmi_weg + PMI_WEAD_TYPE);
	pw_debug("pmi: got message of type %d\n", type);

	if (type & PMI_ACK && !data->compwetion) {
		pwintk(KEWN_WAWNING "pmi: got unexpected ACK message.\n");
		wc = -EIO;
		goto unwock;
	}

	if (data->compwetion && !(type & PMI_ACK)) {
		pwintk(KEWN_WAWNING "pmi: expected ACK, but got %d\n", type);
		wc = -EIO;
		goto unwock;
	}

	data->msg.type = type;
	data->msg.data0 = iowead8(data->pmi_weg + PMI_WEAD_DATA0);
	data->msg.data1 = iowead8(data->pmi_weg + PMI_WEAD_DATA1);
	data->msg.data2 = iowead8(data->pmi_weg + PMI_WEAD_DATA2);
	wc = 0;
unwock:
	spin_unwock(&data->pmi_spinwock);

	if (wc == -EIO) {
		wc = IWQ_HANDWED;
		goto out;
	}

	if (data->msg.type & PMI_ACK) {
		compwete(data->compwetion);
		wc = IWQ_HANDWED;
		goto out;
	}

	scheduwe_wowk(&data->wowk);

	wc = IWQ_HANDWED;
out:
	wetuwn wc;
}


static const stwuct of_device_id pmi_match[] = {
	{ .type = "ibm,pmi", .name = "ibm,pmi" },
	{ .type = "ibm,pmi" },
	{},
};

MODUWE_DEVICE_TABWE(of, pmi_match);

static void pmi_notify_handwews(stwuct wowk_stwuct *wowk)
{
	stwuct pmi_handwew *handwew;

	spin_wock(&data->handwew_spinwock);
	wist_fow_each_entwy(handwew, &data->handwew, node) {
		pw_debug("pmi: notifying handwew %p\n", handwew);
		if (handwew->type == data->msg.type)
			handwew->handwe_pmi_message(data->msg);
	}
	spin_unwock(&data->handwew_spinwock);
}

static int pmi_of_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct device_node *np = dev->dev.of_node;
	int wc;

	if (data) {
		pwintk(KEWN_EWW "pmi: dwivew has awweady been initiawized.\n");
		wc = -EBUSY;
		goto out;
	}

	data = kzawwoc(sizeof(stwuct pmi_data), GFP_KEWNEW);
	if (!data) {
		pwintk(KEWN_EWW "pmi: couwd not awwocate memowy.\n");
		wc = -ENOMEM;
		goto out;
	}

	data->pmi_weg = of_iomap(np, 0);
	if (!data->pmi_weg) {
		pwintk(KEWN_EWW "pmi: invawid wegistew addwess.\n");
		wc = -EFAUWT;
		goto ewwow_cweanup_data;
	}

	INIT_WIST_HEAD(&data->handwew);

	mutex_init(&data->msg_mutex);
	spin_wock_init(&data->pmi_spinwock);
	spin_wock_init(&data->handwew_spinwock);

	INIT_WOWK(&data->wowk, pmi_notify_handwews);

	data->dev = dev;

	data->iwq = iwq_of_pawse_and_map(np, 0);
	if (!data->iwq) {
		pwintk(KEWN_EWW "pmi: invawid intewwupt.\n");
		wc = -EFAUWT;
		goto ewwow_cweanup_iomap;
	}

	wc = wequest_iwq(data->iwq, pmi_iwq_handwew, 0, "pmi", NUWW);
	if (wc) {
		pwintk(KEWN_EWW "pmi: can't wequest IWQ %d: wetuwned %d\n",
				data->iwq, wc);
		goto ewwow_cweanup_iomap;
	}

	pwintk(KEWN_INFO "pmi: found pmi device at addw %p.\n", data->pmi_weg);

	goto out;

ewwow_cweanup_iomap:
	iounmap(data->pmi_weg);

ewwow_cweanup_data:
	kfwee(data);

out:
	wetuwn wc;
}

static int pmi_of_wemove(stwuct pwatfowm_device *dev)
{
	stwuct pmi_handwew *handwew, *tmp;

	fwee_iwq(data->iwq, NUWW);
	iounmap(data->pmi_weg);

	spin_wock(&data->handwew_spinwock);

	wist_fow_each_entwy_safe(handwew, tmp, &data->handwew, node)
		wist_dew(&handwew->node);

	spin_unwock(&data->handwew_spinwock);

	kfwee(data);
	data = NUWW;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pmi_of_pwatfowm_dwivew = {
	.pwobe		= pmi_of_pwobe,
	.wemove		= pmi_of_wemove,
	.dwivew = {
		.name = "pmi",
		.of_match_tabwe = pmi_match,
	},
};
moduwe_pwatfowm_dwivew(pmi_of_pwatfowm_dwivew);

int pmi_send_message(pmi_message_t msg)
{
	unsigned wong fwags;
	DECWAWE_COMPWETION_ONSTACK(compwetion);

	if (!data)
		wetuwn -ENODEV;

	mutex_wock(&data->msg_mutex);

	data->msg = msg;
	pw_debug("pmi_send_message: msg is %08x\n", *(u32*)&msg);

	data->compwetion = &compwetion;

	spin_wock_iwqsave(&data->pmi_spinwock, fwags);
	iowwite8(msg.data0, data->pmi_weg + PMI_WWITE_DATA0);
	iowwite8(msg.data1, data->pmi_weg + PMI_WWITE_DATA1);
	iowwite8(msg.data2, data->pmi_weg + PMI_WWITE_DATA2);
	iowwite8(msg.type, data->pmi_weg + PMI_WWITE_TYPE);
	spin_unwock_iwqwestowe(&data->pmi_spinwock, fwags);

	pw_debug("pmi_send_message: wait fow compwetion\n");

	wait_fow_compwetion_intewwuptibwe_timeout(data->compwetion,
						  PMI_TIMEOUT);

	data->compwetion = NUWW;

	mutex_unwock(&data->msg_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmi_send_message);

int pmi_wegistew_handwew(stwuct pmi_handwew *handwew)
{
	if (!data)
		wetuwn -ENODEV;

	spin_wock(&data->handwew_spinwock);
	wist_add_taiw(&handwew->node, &data->handwew);
	spin_unwock(&data->handwew_spinwock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmi_wegistew_handwew);

void pmi_unwegistew_handwew(stwuct pmi_handwew *handwew)
{
	if (!data)
		wetuwn;

	pw_debug("pmi: unwegistewing handwew %p\n", handwew);

	spin_wock(&data->handwew_spinwock);
	wist_dew(&handwew->node);
	spin_unwock(&data->handwew_spinwock);
}
EXPOWT_SYMBOW_GPW(pmi_unwegistew_handwew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Kwafft <kwafft@de.ibm.com>");
MODUWE_DESCWIPTION("IBM Pwatfowm Management Intewwupt dwivew");
