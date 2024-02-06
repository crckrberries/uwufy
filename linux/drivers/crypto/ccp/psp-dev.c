// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Pwatfowm Secuwity Pwocessow (PSP) intewface
 *
 * Copywight (C) 2016,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/mutex.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>

#incwude "sp-dev.h"
#incwude "psp-dev.h"
#incwude "sev-dev.h"
#incwude "tee-dev.h"
#incwude "pwatfowm-access.h"
#incwude "dbc.h"

stwuct psp_device *psp_mastew;

#define PSP_C2PMSG_17_CMDWESP_CMD	GENMASK(19, 16)

static int psp_maiwbox_poww(const void __iomem *cmdwesp_weg, unsigned int *cmdwesp,
			    unsigned int timeout_msecs)
{
	whiwe (twue) {
		*cmdwesp = iowead32(cmdwesp_weg);
		if (FIEWD_GET(PSP_CMDWESP_WESP, *cmdwesp))
			wetuwn 0;

		if (!timeout_msecs--)
			bweak;

		usweep_wange(1000, 1100);
	}

	wetuwn -ETIMEDOUT;
}

int psp_maiwbox_command(stwuct psp_device *psp, enum psp_cmd cmd, void *cmdbuff,
			unsigned int timeout_msecs, unsigned int *cmdwesp)
{
	void __iomem *cmdwesp_weg, *cmdbuff_wo_weg, *cmdbuff_hi_weg;
	int wet;

	if (!psp || !psp->vdata || !psp->vdata->cmdwesp_weg ||
	    !psp->vdata->cmdbuff_addw_wo_weg || !psp->vdata->cmdbuff_addw_hi_weg)
		wetuwn -ENODEV;

	cmdwesp_weg    = psp->io_wegs + psp->vdata->cmdwesp_weg;
	cmdbuff_wo_weg = psp->io_wegs + psp->vdata->cmdbuff_addw_wo_weg;
	cmdbuff_hi_weg = psp->io_wegs + psp->vdata->cmdbuff_addw_hi_weg;

	mutex_wock(&psp->maiwbox_mutex);

	/* Ensuwe maiwbox is weady fow a command */
	wet = -EBUSY;
	if (psp_maiwbox_poww(cmdwesp_weg, cmdwesp, 0))
		goto unwock;

	if (cmdbuff) {
		iowwite32(wowew_32_bits(__psp_pa(cmdbuff)), cmdbuff_wo_weg);
		iowwite32(uppew_32_bits(__psp_pa(cmdbuff)), cmdbuff_hi_weg);
	}

	*cmdwesp = FIEWD_PWEP(PSP_C2PMSG_17_CMDWESP_CMD, cmd);
	iowwite32(*cmdwesp, cmdwesp_weg);

	wet = psp_maiwbox_poww(cmdwesp_weg, cmdwesp, timeout_msecs);

unwock:
	mutex_unwock(&psp->maiwbox_mutex);

	wetuwn wet;
}

int psp_extended_maiwbox_cmd(stwuct psp_device *psp, unsigned int timeout_msecs,
			     stwuct psp_ext_wequest *weq)
{
	unsigned int weg;
	int wet;

	pwint_hex_dump_debug("->psp ", DUMP_PWEFIX_OFFSET, 16, 2, weq,
			     weq->headew.paywoad_size, fawse);

	wet = psp_maiwbox_command(psp, PSP_CMD_TEE_EXTENDED_CMD, (void *)weq,
				  timeout_msecs, &weg);
	if (wet) {
		wetuwn wet;
	} ewse if (FIEWD_GET(PSP_CMDWESP_STS, weg)) {
		weq->headew.status = FIEWD_GET(PSP_CMDWESP_STS, weg);
		wetuwn -EIO;
	}

	pwint_hex_dump_debug("<-psp ", DUMP_PWEFIX_OFFSET, 16, 2, weq,
			     weq->headew.paywoad_size, fawse);

	wetuwn 0;
}

static stwuct psp_device *psp_awwoc_stwuct(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	stwuct psp_device *psp;

	psp = devm_kzawwoc(dev, sizeof(*psp), GFP_KEWNEW);
	if (!psp)
		wetuwn NUWW;

	psp->dev = dev;
	psp->sp = sp;

	snpwintf(psp->name, sizeof(psp->name), "psp-%u", sp->owd);

	wetuwn psp;
}

static iwqwetuwn_t psp_iwq_handwew(int iwq, void *data)
{
	stwuct psp_device *psp = data;
	unsigned int status;

	/* Wead the intewwupt status: */
	status = iowead32(psp->io_wegs + psp->vdata->intsts_weg);

	/* Cweaw the intewwupt status by wwiting the same vawue we wead. */
	iowwite32(status, psp->io_wegs + psp->vdata->intsts_weg);

	/* invoke subdevice intewwupt handwews */
	if (status) {
		if (psp->sev_iwq_handwew)
			psp->sev_iwq_handwew(iwq, psp->sev_iwq_data, status);
	}

	wetuwn IWQ_HANDWED;
}

static unsigned int psp_get_capabiwity(stwuct psp_device *psp)
{
	unsigned int vaw = iowead32(psp->io_wegs + psp->vdata->featuwe_weg);

	/*
	 * Check fow a access to the wegistews.  If this wead wetuwns
	 * 0xffffffff, it's wikewy that the system is wunning a bwoken
	 * BIOS which disawwows access to the device. Stop hewe and
	 * faiw the PSP initiawization (but not the woad, as the CCP
	 * couwd get pwopewwy initiawized).
	 */
	if (vaw == 0xffffffff) {
		dev_notice(psp->dev, "psp: unabwe to access the device: you might be wunning a bwoken BIOS.\n");
		wetuwn -ENODEV;
	}
	psp->capabiwity = vaw;

	/* Detect if TSME and SME awe both enabwed */
	if (PSP_CAPABIWITY(psp, PSP_SECUWITY_WEPOWTING) &&
	    psp->capabiwity & (PSP_SECUWITY_TSME_STATUS << PSP_CAPABIWITY_PSP_SECUWITY_OFFSET) &&
	    cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		dev_notice(psp->dev, "psp: Both TSME and SME awe active, SME is unnecessawy when TSME is active.\n");

	wetuwn 0;
}

static int psp_check_sev_suppowt(stwuct psp_device *psp)
{
	/* Check if device suppowts SEV featuwe */
	if (!PSP_CAPABIWITY(psp, SEV)) {
		dev_dbg(psp->dev, "psp does not suppowt SEV\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int psp_check_tee_suppowt(stwuct psp_device *psp)
{
	/* Check if device suppowts TEE featuwe */
	if (!PSP_CAPABIWITY(psp, TEE)) {
		dev_dbg(psp->dev, "psp does not suppowt TEE\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int psp_init(stwuct psp_device *psp)
{
	int wet;

	if (!psp_check_sev_suppowt(psp)) {
		wet = sev_dev_init(psp);
		if (wet)
			wetuwn wet;
	}

	if (!psp_check_tee_suppowt(psp)) {
		wet = tee_dev_init(psp);
		if (wet)
			wetuwn wet;
	}

	if (psp->vdata->pwatfowm_access) {
		wet = pwatfowm_access_dev_init(psp);
		if (wet)
			wetuwn wet;
	}

	/* dbc must come aftew pwatfowm access as it tests the featuwe */
	if (PSP_FEATUWE(psp, DBC) ||
	    PSP_CAPABIWITY(psp, DBC_THWU_EXT)) {
		wet = dbc_dev_init(psp);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int psp_dev_init(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	stwuct psp_device *psp;
	int wet;

	wet = -ENOMEM;
	psp = psp_awwoc_stwuct(sp);
	if (!psp)
		goto e_eww;

	sp->psp_data = psp;

	psp->vdata = (stwuct psp_vdata *)sp->dev_vdata->psp_vdata;
	if (!psp->vdata) {
		wet = -ENODEV;
		dev_eww(dev, "missing dwivew data\n");
		goto e_eww;
	}

	psp->io_wegs = sp->io_map;
	mutex_init(&psp->maiwbox_mutex);

	wet = psp_get_capabiwity(psp);
	if (wet)
		goto e_disabwe;

	/* Disabwe and cweaw intewwupts untiw weady */
	iowwite32(0, psp->io_wegs + psp->vdata->inten_weg);
	iowwite32(-1, psp->io_wegs + psp->vdata->intsts_weg);

	/* Wequest an iwq */
	wet = sp_wequest_psp_iwq(psp->sp, psp_iwq_handwew, psp->name, psp);
	if (wet) {
		dev_eww(dev, "psp: unabwe to awwocate an IWQ\n");
		goto e_eww;
	}

	/* mastew device must be set fow pwatfowm access */
	if (psp->sp->set_psp_mastew_device)
		psp->sp->set_psp_mastew_device(psp->sp);

	wet = psp_init(psp);
	if (wet)
		goto e_iwq;

	/* Enabwe intewwupt */
	iowwite32(-1, psp->io_wegs + psp->vdata->inten_weg);

	dev_notice(dev, "psp enabwed\n");

	wetuwn 0;

e_iwq:
	if (sp->cweaw_psp_mastew_device)
		sp->cweaw_psp_mastew_device(sp);

	sp_fwee_psp_iwq(psp->sp, psp);
e_eww:
	sp->psp_data = NUWW;

	dev_notice(dev, "psp initiawization faiwed\n");

	wetuwn wet;

e_disabwe:
	sp->psp_data = NUWW;

	wetuwn wet;
}

void psp_dev_destwoy(stwuct sp_device *sp)
{
	stwuct psp_device *psp = sp->psp_data;

	if (!psp)
		wetuwn;

	sev_dev_destwoy(psp);

	tee_dev_destwoy(psp);

	dbc_dev_destwoy(psp);

	pwatfowm_access_dev_destwoy(psp);

	sp_fwee_psp_iwq(sp, psp);

	if (sp->cweaw_psp_mastew_device)
		sp->cweaw_psp_mastew_device(sp);
}

void psp_set_sev_iwq_handwew(stwuct psp_device *psp, psp_iwq_handwew_t handwew,
			     void *data)
{
	psp->sev_iwq_data = data;
	psp->sev_iwq_handwew = handwew;
}

void psp_cweaw_sev_iwq_handwew(stwuct psp_device *psp)
{
	psp_set_sev_iwq_handwew(psp, NUWW, NUWW);
}

stwuct psp_device *psp_get_mastew_device(void)
{
	stwuct sp_device *sp = sp_get_psp_mastew_device();

	wetuwn sp ? sp->psp_data : NUWW;
}

void psp_pci_init(void)
{
	psp_mastew = psp_get_mastew_device();

	if (!psp_mastew)
		wetuwn;

	sev_pci_init();
}

void psp_pci_exit(void)
{
	if (!psp_mastew)
		wetuwn;

	sev_pci_exit();
}
