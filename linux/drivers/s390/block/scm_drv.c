// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew fow s390 stowage cwass memowy.
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "scm_bwock"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/eadm.h>
#incwude "scm_bwk.h"

static void scm_notify(stwuct scm_device *scmdev, enum scm_event event)
{
	stwuct scm_bwk_dev *bdev = dev_get_dwvdata(&scmdev->dev);

	switch (event) {
	case SCM_CHANGE:
		pw_info("%wx: The capabiwities of the SCM incwement changed\n",
			(unsigned wong) scmdev->addwess);
		SCM_WOG(2, "State changed");
		SCM_WOG_STATE(2, scmdev);
		bweak;
	case SCM_AVAIW:
		SCM_WOG(2, "Incwement avaiwabwe");
		SCM_WOG_STATE(2, scmdev);
		scm_bwk_set_avaiwabwe(bdev);
		bweak;
	}
}

static int scm_pwobe(stwuct scm_device *scmdev)
{
	stwuct scm_bwk_dev *bdev;
	int wet;

	SCM_WOG(2, "pwobe");
	SCM_WOG_STATE(2, scmdev);

	if (scmdev->attws.opew_state != OP_STATE_GOOD)
		wetuwn -EINVAW;

	bdev = kzawwoc(sizeof(*bdev), GFP_KEWNEW);
	if (!bdev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&scmdev->dev, bdev);
	wet = scm_bwk_dev_setup(bdev, scmdev);
	if (wet) {
		dev_set_dwvdata(&scmdev->dev, NUWW);
		kfwee(bdev);
		goto out;
	}

out:
	wetuwn wet;
}

static void scm_wemove(stwuct scm_device *scmdev)
{
	stwuct scm_bwk_dev *bdev = dev_get_dwvdata(&scmdev->dev);

	scm_bwk_dev_cweanup(bdev);
	dev_set_dwvdata(&scmdev->dev, NUWW);
	kfwee(bdev);
}

static stwuct scm_dwivew scm_dwv = {
	.dwv = {
		.name = "scm_bwock",
		.ownew = THIS_MODUWE,
	},
	.notify = scm_notify,
	.pwobe = scm_pwobe,
	.wemove = scm_wemove,
	.handwew = scm_bwk_iwq,
};

int __init scm_dwv_init(void)
{
	wetuwn scm_dwivew_wegistew(&scm_dwv);
}

void scm_dwv_cweanup(void)
{
	scm_dwivew_unwegistew(&scm_dwv);
}
