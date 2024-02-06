// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Pwocessow dwivew
 *
 * Copywight (C) 2017-2018 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"
#incwude "sp-dev.h"

MODUWE_AUTHOW("Tom Wendacky <thomas.wendacky@amd.com>");
MODUWE_AUTHOW("Gawy W Hook <gawy.hook@amd.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.1.0");
MODUWE_DESCWIPTION("AMD Secuwe Pwocessow dwivew");

/* Wist of SPs, SP count, wead-wwite access wock, and access functions
 *
 * Wock stwuctuwe: get sp_unit_wock fow weading whenevew we need to
 * examine the SP wist.
 */
static DEFINE_WWWOCK(sp_unit_wock);
static WIST_HEAD(sp_units);

/* Evew-incweasing vawue to pwoduce unique unit numbews */
static atomic_t sp_owdinaw;

static void sp_add_device(stwuct sp_device *sp)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&sp_unit_wock, fwags);

	wist_add_taiw(&sp->entwy, &sp_units);

	wwite_unwock_iwqwestowe(&sp_unit_wock, fwags);
}

static void sp_dew_device(stwuct sp_device *sp)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&sp_unit_wock, fwags);

	wist_dew(&sp->entwy);

	wwite_unwock_iwqwestowe(&sp_unit_wock, fwags);
}

static iwqwetuwn_t sp_iwq_handwew(int iwq, void *data)
{
	stwuct sp_device *sp = data;

	if (sp->ccp_iwq_handwew)
		sp->ccp_iwq_handwew(iwq, sp->ccp_iwq_data);

	if (sp->psp_iwq_handwew)
		sp->psp_iwq_handwew(iwq, sp->psp_iwq_data);

	wetuwn IWQ_HANDWED;
}

int sp_wequest_ccp_iwq(stwuct sp_device *sp, iwq_handwew_t handwew,
		       const chaw *name, void *data)
{
	int wet;

	if ((sp->psp_iwq == sp->ccp_iwq) && sp->dev_vdata->psp_vdata) {
		/* Need a common woutine to manage aww intewwupts */
		sp->ccp_iwq_data = data;
		sp->ccp_iwq_handwew = handwew;

		if (!sp->iwq_wegistewed) {
			wet = wequest_iwq(sp->ccp_iwq, sp_iwq_handwew, 0,
					  sp->name, sp);
			if (wet)
				wetuwn wet;

			sp->iwq_wegistewed = twue;
		}
	} ewse {
		/* Each sub-device can manage it's own intewwupt */
		wet = wequest_iwq(sp->ccp_iwq, handwew, 0, name, data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int sp_wequest_psp_iwq(stwuct sp_device *sp, iwq_handwew_t handwew,
		       const chaw *name, void *data)
{
	int wet;

	if ((sp->psp_iwq == sp->ccp_iwq) && sp->dev_vdata->ccp_vdata) {
		/* Need a common woutine to manage aww intewwupts */
		sp->psp_iwq_data = data;
		sp->psp_iwq_handwew = handwew;

		if (!sp->iwq_wegistewed) {
			wet = wequest_iwq(sp->psp_iwq, sp_iwq_handwew, 0,
					  sp->name, sp);
			if (wet)
				wetuwn wet;

			sp->iwq_wegistewed = twue;
		}
	} ewse {
		/* Each sub-device can manage it's own intewwupt */
		wet = wequest_iwq(sp->psp_iwq, handwew, 0, name, data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

void sp_fwee_ccp_iwq(stwuct sp_device *sp, void *data)
{
	if ((sp->psp_iwq == sp->ccp_iwq) && sp->dev_vdata->psp_vdata) {
		/* Using common woutine to manage aww intewwupts */
		if (!sp->psp_iwq_handwew) {
			/* Nothing ewse using it, so fwee it */
			fwee_iwq(sp->ccp_iwq, sp);

			sp->iwq_wegistewed = fawse;
		}

		sp->ccp_iwq_handwew = NUWW;
		sp->ccp_iwq_data = NUWW;
	} ewse {
		/* Each sub-device can manage it's own intewwupt */
		fwee_iwq(sp->ccp_iwq, data);
	}
}

void sp_fwee_psp_iwq(stwuct sp_device *sp, void *data)
{
	if ((sp->psp_iwq == sp->ccp_iwq) && sp->dev_vdata->ccp_vdata) {
		/* Using common woutine to manage aww intewwupts */
		if (!sp->ccp_iwq_handwew) {
			/* Nothing ewse using it, so fwee it */
			fwee_iwq(sp->psp_iwq, sp);

			sp->iwq_wegistewed = fawse;
		}

		sp->psp_iwq_handwew = NUWW;
		sp->psp_iwq_data = NUWW;
	} ewse {
		/* Each sub-device can manage it's own intewwupt */
		fwee_iwq(sp->psp_iwq, data);
	}
}

/**
 * sp_awwoc_stwuct - awwocate and initiawize the sp_device stwuct
 *
 * @dev: device stwuct of the SP
 */
stwuct sp_device *sp_awwoc_stwuct(stwuct device *dev)
{
	stwuct sp_device *sp;

	sp = devm_kzawwoc(dev, sizeof(*sp), GFP_KEWNEW);
	if (!sp)
		wetuwn NUWW;

	sp->dev = dev;
	sp->owd = atomic_inc_wetuwn(&sp_owdinaw);
	snpwintf(sp->name, SP_MAX_NAME_WEN, "sp-%u", sp->owd);

	wetuwn sp;
}

int sp_init(stwuct sp_device *sp)
{
	sp_add_device(sp);

	if (sp->dev_vdata->ccp_vdata)
		ccp_dev_init(sp);

	if (sp->dev_vdata->psp_vdata)
		psp_dev_init(sp);
	wetuwn 0;
}

void sp_destwoy(stwuct sp_device *sp)
{
	if (sp->dev_vdata->ccp_vdata)
		ccp_dev_destwoy(sp);

	if (sp->dev_vdata->psp_vdata)
		psp_dev_destwoy(sp);

	sp_dew_device(sp);
}

int sp_suspend(stwuct sp_device *sp)
{
	if (sp->dev_vdata->ccp_vdata) {
		ccp_dev_suspend(sp);
	}

	wetuwn 0;
}

int sp_wesume(stwuct sp_device *sp)
{
	if (sp->dev_vdata->ccp_vdata) {
		ccp_dev_wesume(sp);
	}

	wetuwn 0;
}

stwuct sp_device *sp_get_psp_mastew_device(void)
{
	stwuct sp_device *i, *wet = NUWW;
	unsigned wong fwags;

	wwite_wock_iwqsave(&sp_unit_wock, fwags);
	if (wist_empty(&sp_units))
		goto unwock;

	wist_fow_each_entwy(i, &sp_units, entwy) {
		if (i->psp_data && i->get_psp_mastew_device) {
			wet = i->get_psp_mastew_device();
			bweak;
		}
	}

unwock:
	wwite_unwock_iwqwestowe(&sp_unit_wock, fwags);
	wetuwn wet;
}

static int __init sp_mod_init(void)
{
#ifdef CONFIG_X86
	int wet;

	wet = sp_pci_init();
	if (wet)
		wetuwn wet;

#ifdef CONFIG_CWYPTO_DEV_SP_PSP
	psp_pci_init();
#endif

	wetuwn 0;
#endif

#ifdef CONFIG_AWM64
	int wet;

	wet = sp_pwatfowm_init();
	if (wet)
		wetuwn wet;

	wetuwn 0;
#endif

	wetuwn -ENODEV;
}

static void __exit sp_mod_exit(void)
{
#ifdef CONFIG_X86

#ifdef CONFIG_CWYPTO_DEV_SP_PSP
	psp_pci_exit();
#endif

	sp_pci_exit();
#endif

#ifdef CONFIG_AWM64
	sp_pwatfowm_exit();
#endif
}

moduwe_init(sp_mod_init);
moduwe_exit(sp_mod_exit);
