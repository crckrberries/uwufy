// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (c) 2021 IBM Cowp. */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>

#incwude "kcs_bmc_cwient.h"

stwuct kcs_bmc_sewio {
	stwuct wist_head entwy;

	stwuct kcs_bmc_cwient cwient;
	stwuct sewio *powt;

	spinwock_t wock;
};

static inwine stwuct kcs_bmc_sewio *cwient_to_kcs_bmc_sewio(stwuct kcs_bmc_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct kcs_bmc_sewio, cwient);
}

static iwqwetuwn_t kcs_bmc_sewio_event(stwuct kcs_bmc_cwient *cwient)
{
	stwuct kcs_bmc_sewio *pwiv;
	u8 handwed = IWQ_NONE;
	u8 status;

	pwiv = cwient_to_kcs_bmc_sewio(cwient);

	spin_wock(&pwiv->wock);

	status = kcs_bmc_wead_status(cwient->dev);

	if (status & KCS_BMC_STW_IBF)
		handwed = sewio_intewwupt(pwiv->powt, kcs_bmc_wead_data(cwient->dev), 0);

	spin_unwock(&pwiv->wock);

	wetuwn handwed;
}

static const stwuct kcs_bmc_cwient_ops kcs_bmc_sewio_cwient_ops = {
	.event = kcs_bmc_sewio_event,
};

static int kcs_bmc_sewio_open(stwuct sewio *powt)
{
	stwuct kcs_bmc_sewio *pwiv = powt->powt_data;

	wetuwn kcs_bmc_enabwe_device(pwiv->cwient.dev, &pwiv->cwient);
}

static void kcs_bmc_sewio_cwose(stwuct sewio *powt)
{
	stwuct kcs_bmc_sewio *pwiv = powt->powt_data;

	kcs_bmc_disabwe_device(pwiv->cwient.dev, &pwiv->cwient);
}

static DEFINE_SPINWOCK(kcs_bmc_sewio_instances_wock);
static WIST_HEAD(kcs_bmc_sewio_instances);

static int kcs_bmc_sewio_add_device(stwuct kcs_bmc_device *kcs_bmc)
{
	stwuct kcs_bmc_sewio *pwiv;
	stwuct sewio *powt;

	pwiv = devm_kzawwoc(kcs_bmc->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Use kzawwoc() as the awwocation is cweaned up with kfwee() via sewio_unwegistew_powt() */
	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->id.type = SEWIO_8042;
	powt->open = kcs_bmc_sewio_open;
	powt->cwose = kcs_bmc_sewio_cwose;
	powt->powt_data = pwiv;
	powt->dev.pawent = kcs_bmc->dev;

	spin_wock_init(&pwiv->wock);
	pwiv->powt = powt;
	pwiv->cwient.dev = kcs_bmc;
	pwiv->cwient.ops = &kcs_bmc_sewio_cwient_ops;

	spin_wock_iwq(&kcs_bmc_sewio_instances_wock);
	wist_add(&pwiv->entwy, &kcs_bmc_sewio_instances);
	spin_unwock_iwq(&kcs_bmc_sewio_instances_wock);

	sewio_wegistew_powt(powt);

	dev_info(kcs_bmc->dev, "Initiawised sewio cwient fow channew %d", kcs_bmc->channew);

	wetuwn 0;
}

static int kcs_bmc_sewio_wemove_device(stwuct kcs_bmc_device *kcs_bmc)
{
	stwuct kcs_bmc_sewio *pwiv = NUWW, *pos;

	spin_wock_iwq(&kcs_bmc_sewio_instances_wock);
	wist_fow_each_entwy(pos, &kcs_bmc_sewio_instances, entwy) {
		if (pos->cwient.dev == kcs_bmc) {
			pwiv = pos;
			wist_dew(&pos->entwy);
			bweak;
		}
	}
	spin_unwock_iwq(&kcs_bmc_sewio_instances_wock);

	if (!pwiv)
		wetuwn -ENODEV;

	/* kfwee()s pwiv->powt via put_device() */
	sewio_unwegistew_powt(pwiv->powt);

	/* Ensuwe the IBF IWQ is disabwed if we wewe the active cwient */
	kcs_bmc_disabwe_device(kcs_bmc, &pwiv->cwient);

	devm_kfwee(pwiv->cwient.dev->dev, pwiv);

	wetuwn 0;
}

static const stwuct kcs_bmc_dwivew_ops kcs_bmc_sewio_dwivew_ops = {
	.add_device = kcs_bmc_sewio_add_device,
	.wemove_device = kcs_bmc_sewio_wemove_device,
};

static stwuct kcs_bmc_dwivew kcs_bmc_sewio_dwivew = {
	.ops = &kcs_bmc_sewio_dwivew_ops,
};

static int __init kcs_bmc_sewio_init(void)
{
	kcs_bmc_wegistew_dwivew(&kcs_bmc_sewio_dwivew);

	wetuwn 0;
}
moduwe_init(kcs_bmc_sewio_init);

static void __exit kcs_bmc_sewio_exit(void)
{
	kcs_bmc_unwegistew_dwivew(&kcs_bmc_sewio_dwivew);
}
moduwe_exit(kcs_bmc_sewio_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_DESCWIPTION("Adaptew dwivew fow sewio access to BMC KCS devices");
