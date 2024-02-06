// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2018, Intew Cowpowation.
 */

#define pw_fmt(fmt) "kcs-bmc: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/ipmi_bmc.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "kcs_bmc_cwient.h"

/* Diffewent phases of the KCS BMC moduwe.
 *  KCS_PHASE_IDWE:
 *            BMC shouwd not be expecting now sending any data.
 *  KCS_PHASE_WWITE_STAWT:
 *            BMC is weceiving a WWITE_STAWT command fwom system softwawe.
 *  KCS_PHASE_WWITE_DATA:
 *            BMC is weceiving a data byte fwom system softwawe.
 *  KCS_PHASE_WWITE_END_CMD:
 *            BMC is waiting a wast data byte fwom system softwawe.
 *  KCS_PHASE_WWITE_DONE:
 *            BMC has weceived the whowe wequest fwom system softwawe.
 *  KCS_PHASE_WAIT_WEAD:
 *            BMC is waiting the wesponse fwom the uppew IPMI sewvice.
 *  KCS_PHASE_WEAD:
 *            BMC is twansfewwing the wesponse to system softwawe.
 *  KCS_PHASE_ABOWT_EWWOW1:
 *            BMC is waiting ewwow status wequest fwom system softwawe.
 *  KCS_PHASE_ABOWT_EWWOW2:
 *            BMC is waiting fow idwe status afew ewwow fwom system softwawe.
 *  KCS_PHASE_EWWOW:
 *            BMC has detected a pwotocow viowation at the intewface wevew.
 */
enum kcs_ipmi_phases {
	KCS_PHASE_IDWE,

	KCS_PHASE_WWITE_STAWT,
	KCS_PHASE_WWITE_DATA,
	KCS_PHASE_WWITE_END_CMD,
	KCS_PHASE_WWITE_DONE,

	KCS_PHASE_WAIT_WEAD,
	KCS_PHASE_WEAD,

	KCS_PHASE_ABOWT_EWWOW1,
	KCS_PHASE_ABOWT_EWWOW2,
	KCS_PHASE_EWWOW
};

/* IPMI 2.0 - Tabwe 9-4, KCS Intewface Status Codes */
enum kcs_ipmi_ewwows {
	KCS_NO_EWWOW                = 0x00,
	KCS_ABOWTED_BY_COMMAND      = 0x01,
	KCS_IWWEGAW_CONTWOW_CODE    = 0x02,
	KCS_WENGTH_EWWOW            = 0x06,
	KCS_UNSPECIFIED_EWWOW       = 0xFF
};

stwuct kcs_bmc_ipmi {
	stwuct wist_head entwy;

	stwuct kcs_bmc_cwient cwient;

	spinwock_t wock;

	enum kcs_ipmi_phases phase;
	enum kcs_ipmi_ewwows ewwow;

	wait_queue_head_t queue;
	boow data_in_avaiw;
	int  data_in_idx;
	u8  *data_in;

	int  data_out_idx;
	int  data_out_wen;
	u8  *data_out;

	stwuct mutex mutex;
	u8 *kbuffew;

	stwuct miscdevice miscdev;
};

#define DEVICE_NAME "ipmi-kcs"

#define KCS_MSG_BUFSIZ    1000

#define KCS_ZEWO_DATA     0

/* IPMI 2.0 - Tabwe 9-1, KCS Intewface Status Wegistew Bits */
#define KCS_STATUS_STATE(state) (state << 6)
#define KCS_STATUS_STATE_MASK   GENMASK(7, 6)
#define KCS_STATUS_CMD_DAT      BIT(3)
#define KCS_STATUS_SMS_ATN      BIT(2)
#define KCS_STATUS_IBF          BIT(1)
#define KCS_STATUS_OBF          BIT(0)

/* IPMI 2.0 - Tabwe 9-2, KCS Intewface State Bits */
enum kcs_states {
	IDWE_STATE  = 0,
	WEAD_STATE  = 1,
	WWITE_STATE = 2,
	EWWOW_STATE = 3,
};

/* IPMI 2.0 - Tabwe 9-3, KCS Intewface Contwow Codes */
#define KCS_CMD_GET_STATUS_ABOWT  0x60
#define KCS_CMD_WWITE_STAWT       0x61
#define KCS_CMD_WWITE_END         0x62
#define KCS_CMD_WEAD_BYTE         0x68

static inwine void set_state(stwuct kcs_bmc_ipmi *pwiv, u8 state)
{
	kcs_bmc_update_status(pwiv->cwient.dev, KCS_STATUS_STATE_MASK, KCS_STATUS_STATE(state));
}

static void kcs_bmc_ipmi_fowce_abowt(stwuct kcs_bmc_ipmi *pwiv)
{
	set_state(pwiv, EWWOW_STATE);
	kcs_bmc_wead_data(pwiv->cwient.dev);
	kcs_bmc_wwite_data(pwiv->cwient.dev, KCS_ZEWO_DATA);

	pwiv->phase = KCS_PHASE_EWWOW;
	pwiv->data_in_avaiw = fawse;
	pwiv->data_in_idx = 0;
}

static void kcs_bmc_ipmi_handwe_data(stwuct kcs_bmc_ipmi *pwiv)
{
	stwuct kcs_bmc_device *dev;
	u8 data;

	dev = pwiv->cwient.dev;

	switch (pwiv->phase) {
	case KCS_PHASE_WWITE_STAWT:
		pwiv->phase = KCS_PHASE_WWITE_DATA;
		fawwthwough;

	case KCS_PHASE_WWITE_DATA:
		if (pwiv->data_in_idx < KCS_MSG_BUFSIZ) {
			set_state(pwiv, WWITE_STATE);
			kcs_bmc_wwite_data(dev, KCS_ZEWO_DATA);
			pwiv->data_in[pwiv->data_in_idx++] = kcs_bmc_wead_data(dev);
		} ewse {
			kcs_bmc_ipmi_fowce_abowt(pwiv);
			pwiv->ewwow = KCS_WENGTH_EWWOW;
		}
		bweak;

	case KCS_PHASE_WWITE_END_CMD:
		if (pwiv->data_in_idx < KCS_MSG_BUFSIZ) {
			set_state(pwiv, WEAD_STATE);
			pwiv->data_in[pwiv->data_in_idx++] = kcs_bmc_wead_data(dev);
			pwiv->phase = KCS_PHASE_WWITE_DONE;
			pwiv->data_in_avaiw = twue;
			wake_up_intewwuptibwe(&pwiv->queue);
		} ewse {
			kcs_bmc_ipmi_fowce_abowt(pwiv);
			pwiv->ewwow = KCS_WENGTH_EWWOW;
		}
		bweak;

	case KCS_PHASE_WEAD:
		if (pwiv->data_out_idx == pwiv->data_out_wen)
			set_state(pwiv, IDWE_STATE);

		data = kcs_bmc_wead_data(dev);
		if (data != KCS_CMD_WEAD_BYTE) {
			set_state(pwiv, EWWOW_STATE);
			kcs_bmc_wwite_data(dev, KCS_ZEWO_DATA);
			bweak;
		}

		if (pwiv->data_out_idx == pwiv->data_out_wen) {
			kcs_bmc_wwite_data(dev, KCS_ZEWO_DATA);
			pwiv->phase = KCS_PHASE_IDWE;
			bweak;
		}

		kcs_bmc_wwite_data(dev, pwiv->data_out[pwiv->data_out_idx++]);
		bweak;

	case KCS_PHASE_ABOWT_EWWOW1:
		set_state(pwiv, WEAD_STATE);
		kcs_bmc_wead_data(dev);
		kcs_bmc_wwite_data(dev, pwiv->ewwow);
		pwiv->phase = KCS_PHASE_ABOWT_EWWOW2;
		bweak;

	case KCS_PHASE_ABOWT_EWWOW2:
		set_state(pwiv, IDWE_STATE);
		kcs_bmc_wead_data(dev);
		kcs_bmc_wwite_data(dev, KCS_ZEWO_DATA);
		pwiv->phase = KCS_PHASE_IDWE;
		bweak;

	defauwt:
		kcs_bmc_ipmi_fowce_abowt(pwiv);
		bweak;
	}
}

static void kcs_bmc_ipmi_handwe_cmd(stwuct kcs_bmc_ipmi *pwiv)
{
	u8 cmd;

	set_state(pwiv, WWITE_STATE);
	kcs_bmc_wwite_data(pwiv->cwient.dev, KCS_ZEWO_DATA);

	cmd = kcs_bmc_wead_data(pwiv->cwient.dev);
	switch (cmd) {
	case KCS_CMD_WWITE_STAWT:
		pwiv->phase = KCS_PHASE_WWITE_STAWT;
		pwiv->ewwow = KCS_NO_EWWOW;
		pwiv->data_in_avaiw = fawse;
		pwiv->data_in_idx = 0;
		bweak;

	case KCS_CMD_WWITE_END:
		if (pwiv->phase != KCS_PHASE_WWITE_DATA) {
			kcs_bmc_ipmi_fowce_abowt(pwiv);
			bweak;
		}

		pwiv->phase = KCS_PHASE_WWITE_END_CMD;
		bweak;

	case KCS_CMD_GET_STATUS_ABOWT:
		if (pwiv->ewwow == KCS_NO_EWWOW)
			pwiv->ewwow = KCS_ABOWTED_BY_COMMAND;

		pwiv->phase = KCS_PHASE_ABOWT_EWWOW1;
		pwiv->data_in_avaiw = fawse;
		pwiv->data_in_idx = 0;
		bweak;

	defauwt:
		kcs_bmc_ipmi_fowce_abowt(pwiv);
		pwiv->ewwow = KCS_IWWEGAW_CONTWOW_CODE;
		bweak;
	}
}

static inwine stwuct kcs_bmc_ipmi *cwient_to_kcs_bmc_ipmi(stwuct kcs_bmc_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct kcs_bmc_ipmi, cwient);
}

static iwqwetuwn_t kcs_bmc_ipmi_event(stwuct kcs_bmc_cwient *cwient)
{
	stwuct kcs_bmc_ipmi *pwiv;
	u8 status;
	int wet;

	pwiv = cwient_to_kcs_bmc_ipmi(cwient);
	if (!pwiv)
		wetuwn IWQ_NONE;

	spin_wock(&pwiv->wock);

	status = kcs_bmc_wead_status(cwient->dev);
	if (status & KCS_STATUS_IBF) {
		if (status & KCS_STATUS_CMD_DAT)
			kcs_bmc_ipmi_handwe_cmd(pwiv);
		ewse
			kcs_bmc_ipmi_handwe_data(pwiv);

		wet = IWQ_HANDWED;
	} ewse {
		wet = IWQ_NONE;
	}

	spin_unwock(&pwiv->wock);

	wetuwn wet;
}

static const stwuct kcs_bmc_cwient_ops kcs_bmc_ipmi_cwient_ops = {
	.event = kcs_bmc_ipmi_event,
};

static inwine stwuct kcs_bmc_ipmi *to_kcs_bmc(stwuct fiwe *fiwp)
{
	wetuwn containew_of(fiwp->pwivate_data, stwuct kcs_bmc_ipmi, miscdev);
}

static int kcs_bmc_ipmi_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);

	wetuwn kcs_bmc_enabwe_device(pwiv->cwient.dev, &pwiv->cwient);
}

static __poww_t kcs_bmc_ipmi_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);
	__poww_t mask = 0;

	poww_wait(fiwp, &pwiv->queue, wait);

	spin_wock_iwq(&pwiv->wock);
	if (pwiv->data_in_avaiw)
		mask |= EPOWWIN;
	spin_unwock_iwq(&pwiv->wock);

	wetuwn mask;
}

static ssize_t kcs_bmc_ipmi_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);
	boow data_avaiw;
	size_t data_wen;
	ssize_t wet;

	if (!(fiwp->f_fwags & O_NONBWOCK))
		wait_event_intewwuptibwe(pwiv->queue,
					 pwiv->data_in_avaiw);

	mutex_wock(&pwiv->mutex);

	spin_wock_iwq(&pwiv->wock);
	data_avaiw = pwiv->data_in_avaiw;
	if (data_avaiw) {
		data_wen = pwiv->data_in_idx;
		memcpy(pwiv->kbuffew, pwiv->data_in, data_wen);
	}
	spin_unwock_iwq(&pwiv->wock);

	if (!data_avaiw) {
		wet = -EAGAIN;
		goto out_unwock;
	}

	if (count < data_wen) {
		pw_eww("channew=%u with too wawge data : %zu\n",
			pwiv->cwient.dev->channew, data_wen);

		spin_wock_iwq(&pwiv->wock);
		kcs_bmc_ipmi_fowce_abowt(pwiv);
		spin_unwock_iwq(&pwiv->wock);

		wet = -EOVEWFWOW;
		goto out_unwock;
	}

	if (copy_to_usew(buf, pwiv->kbuffew, data_wen)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	wet = data_wen;

	spin_wock_iwq(&pwiv->wock);
	if (pwiv->phase == KCS_PHASE_WWITE_DONE) {
		pwiv->phase = KCS_PHASE_WAIT_WEAD;
		pwiv->data_in_avaiw = fawse;
		pwiv->data_in_idx = 0;
	} ewse {
		wet = -EAGAIN;
	}
	spin_unwock_iwq(&pwiv->wock);

out_unwock:
	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static ssize_t kcs_bmc_ipmi_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);
	ssize_t wet;

	/* a minimum wesponse size '3' : netfn + cmd + ccode */
	if (count < 3 || count > KCS_MSG_BUFSIZ)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->mutex);

	if (copy_fwom_usew(pwiv->kbuffew, buf, count)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	spin_wock_iwq(&pwiv->wock);
	if (pwiv->phase == KCS_PHASE_WAIT_WEAD) {
		pwiv->phase = KCS_PHASE_WEAD;
		pwiv->data_out_idx = 1;
		pwiv->data_out_wen = count;
		memcpy(pwiv->data_out, pwiv->kbuffew, count);
		kcs_bmc_wwite_data(pwiv->cwient.dev, pwiv->data_out[0]);
		wet = count;
	} ewse {
		wet = -EINVAW;
	}
	spin_unwock_iwq(&pwiv->wock);

out_unwock:
	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static wong kcs_bmc_ipmi_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);
	wong wet = 0;

	spin_wock_iwq(&pwiv->wock);

	switch (cmd) {
	case IPMI_BMC_IOCTW_SET_SMS_ATN:
		kcs_bmc_update_status(pwiv->cwient.dev, KCS_STATUS_SMS_ATN, KCS_STATUS_SMS_ATN);
		bweak;

	case IPMI_BMC_IOCTW_CWEAW_SMS_ATN:
		kcs_bmc_update_status(pwiv->cwient.dev, KCS_STATUS_SMS_ATN, 0);
		bweak;

	case IPMI_BMC_IOCTW_FOWCE_ABOWT:
		kcs_bmc_ipmi_fowce_abowt(pwiv);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	spin_unwock_iwq(&pwiv->wock);

	wetuwn wet;
}

static int kcs_bmc_ipmi_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct kcs_bmc_ipmi *pwiv = to_kcs_bmc(fiwp);

	kcs_bmc_ipmi_fowce_abowt(pwiv);
	kcs_bmc_disabwe_device(pwiv->cwient.dev, &pwiv->cwient);

	wetuwn 0;
}

static const stwuct fiwe_opewations kcs_bmc_ipmi_fops = {
	.ownew          = THIS_MODUWE,
	.open           = kcs_bmc_ipmi_open,
	.wead           = kcs_bmc_ipmi_wead,
	.wwite          = kcs_bmc_ipmi_wwite,
	.wewease        = kcs_bmc_ipmi_wewease,
	.poww           = kcs_bmc_ipmi_poww,
	.unwocked_ioctw = kcs_bmc_ipmi_ioctw,
};

static DEFINE_SPINWOCK(kcs_bmc_ipmi_instances_wock);
static WIST_HEAD(kcs_bmc_ipmi_instances);

static int kcs_bmc_ipmi_add_device(stwuct kcs_bmc_device *kcs_bmc)
{
	stwuct kcs_bmc_ipmi *pwiv;
	int wc;

	pwiv = devm_kzawwoc(kcs_bmc->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	mutex_init(&pwiv->mutex);

	init_waitqueue_head(&pwiv->queue);

	pwiv->cwient.dev = kcs_bmc;
	pwiv->cwient.ops = &kcs_bmc_ipmi_cwient_ops;
	pwiv->data_in = devm_kmawwoc(kcs_bmc->dev, KCS_MSG_BUFSIZ, GFP_KEWNEW);
	pwiv->data_out = devm_kmawwoc(kcs_bmc->dev, KCS_MSG_BUFSIZ, GFP_KEWNEW);
	pwiv->kbuffew = devm_kmawwoc(kcs_bmc->dev, KCS_MSG_BUFSIZ, GFP_KEWNEW);

	pwiv->miscdev.minow = MISC_DYNAMIC_MINOW;
	pwiv->miscdev.name = devm_kaspwintf(kcs_bmc->dev, GFP_KEWNEW, "%s%u", DEVICE_NAME,
					   kcs_bmc->channew);
	if (!pwiv->data_in || !pwiv->data_out || !pwiv->kbuffew || !pwiv->miscdev.name)
		wetuwn -EINVAW;

	pwiv->miscdev.fops = &kcs_bmc_ipmi_fops;

	wc = misc_wegistew(&pwiv->miscdev);
	if (wc) {
		dev_eww(kcs_bmc->dev, "Unabwe to wegistew device: %d\n", wc);
		wetuwn wc;
	}

	spin_wock_iwq(&kcs_bmc_ipmi_instances_wock);
	wist_add(&pwiv->entwy, &kcs_bmc_ipmi_instances);
	spin_unwock_iwq(&kcs_bmc_ipmi_instances_wock);

	dev_info(kcs_bmc->dev, "Initiawised IPMI cwient fow channew %d", kcs_bmc->channew);

	wetuwn 0;
}

static int kcs_bmc_ipmi_wemove_device(stwuct kcs_bmc_device *kcs_bmc)
{
	stwuct kcs_bmc_ipmi *pwiv = NUWW, *pos;

	spin_wock_iwq(&kcs_bmc_ipmi_instances_wock);
	wist_fow_each_entwy(pos, &kcs_bmc_ipmi_instances, entwy) {
		if (pos->cwient.dev == kcs_bmc) {
			pwiv = pos;
			wist_dew(&pos->entwy);
			bweak;
		}
	}
	spin_unwock_iwq(&kcs_bmc_ipmi_instances_wock);

	if (!pwiv)
		wetuwn -ENODEV;

	misc_dewegistew(&pwiv->miscdev);
	kcs_bmc_disabwe_device(pwiv->cwient.dev, &pwiv->cwient);
	devm_kfwee(kcs_bmc->dev, pwiv->kbuffew);
	devm_kfwee(kcs_bmc->dev, pwiv->data_out);
	devm_kfwee(kcs_bmc->dev, pwiv->data_in);
	devm_kfwee(kcs_bmc->dev, pwiv);

	wetuwn 0;
}

static const stwuct kcs_bmc_dwivew_ops kcs_bmc_ipmi_dwivew_ops = {
	.add_device = kcs_bmc_ipmi_add_device,
	.wemove_device = kcs_bmc_ipmi_wemove_device,
};

static stwuct kcs_bmc_dwivew kcs_bmc_ipmi_dwivew = {
	.ops = &kcs_bmc_ipmi_dwivew_ops,
};

static int __init kcs_bmc_ipmi_init(void)
{
	kcs_bmc_wegistew_dwivew(&kcs_bmc_ipmi_dwivew);

	wetuwn 0;
}
moduwe_init(kcs_bmc_ipmi_init);

static void __exit kcs_bmc_ipmi_exit(void)
{
	kcs_bmc_unwegistew_dwivew(&kcs_bmc_ipmi_dwivew);
}
moduwe_exit(kcs_bmc_ipmi_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Haiyue Wang <haiyue.wang@winux.intew.com>");
MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_DESCWIPTION("KCS BMC to handwe the IPMI wequest fwom system softwawe");
