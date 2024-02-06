// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD Pwatfowm Secuwity Pwocessow (PSP) Pwatfowm Access intewface
 *
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 *
 * Some of this code is adapted fwom dwivews/i2c/busses/i2c-designwawe-amdpsp.c
 * devewoped by Jan Dabwos <jsd@semihawf.com> and Copywight (C) 2022 Googwe Inc.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopoww.h>
#incwude <winux/mutex.h>

#incwude "pwatfowm-access.h"

#define PSP_CMD_TIMEOUT_US	(500 * USEC_PEW_MSEC)
#define DOOWBEWW_CMDWESP_STS	GENMASK(7, 0)

/* Wecovewy fiewd shouwd be equaw 0 to stawt sending commands */
static int check_wecovewy(u32 __iomem *cmd)
{
	wetuwn FIEWD_GET(PSP_CMDWESP_WECOVEWY, iowead32(cmd));
}

static int wait_cmd(u32 __iomem *cmd)
{
	u32 tmp, expected;

	/* Expect mbox_cmd to be cweawed and weady bit to be set by PSP */
	expected = FIEWD_PWEP(PSP_CMDWESP_WESP, 1);

	/*
	 * Check fow weadiness of PSP maiwbox in a tight woop in owdew to
	 * pwocess fuwthew as soon as command was consumed.
	 */
	wetuwn weadw_poww_timeout(cmd, tmp, (tmp & expected), 0,
				  PSP_CMD_TIMEOUT_US);
}

int psp_check_pwatfowm_access_status(void)
{
	stwuct psp_device *psp = psp_get_mastew_device();

	if (!psp || !psp->pwatfowm_access_data)
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW(psp_check_pwatfowm_access_status);

int psp_send_pwatfowm_access_msg(enum psp_pwatfowm_access_msg msg,
				 stwuct psp_wequest *weq)
{
	stwuct psp_device *psp = psp_get_mastew_device();
	u32 __iomem *cmd, *wo, *hi;
	stwuct psp_pwatfowm_access_device *pa_dev;
	phys_addw_t weq_addw;
	u32 cmd_weg;
	int wet;

	if (!psp || !psp->pwatfowm_access_data)
		wetuwn -ENODEV;

	pa_dev = psp->pwatfowm_access_data;

	if (!pa_dev->vdata->cmdwesp_weg || !pa_dev->vdata->cmdbuff_addw_wo_weg ||
	    !pa_dev->vdata->cmdbuff_addw_hi_weg)
		wetuwn -ENODEV;

	cmd = psp->io_wegs + pa_dev->vdata->cmdwesp_weg;
	wo = psp->io_wegs + pa_dev->vdata->cmdbuff_addw_wo_weg;
	hi = psp->io_wegs + pa_dev->vdata->cmdbuff_addw_hi_weg;

	mutex_wock(&pa_dev->maiwbox_mutex);

	if (check_wecovewy(cmd)) {
		dev_dbg(psp->dev, "pwatfowm maiwbox is in wecovewy\n");
		wet = -EBUSY;
		goto unwock;
	}

	if (wait_cmd(cmd)) {
		dev_dbg(psp->dev, "pwatfowm maiwbox is not done pwocessing command\n");
		wet = -EBUSY;
		goto unwock;
	}

	/*
	 * Fiww maiwbox with addwess of command-wesponse buffew, which wiww be
	 * used fow sending i2c wequests as weww as weading status wetuwned by
	 * PSP. Use physicaw addwess of buffew, since PSP wiww map this wegion.
	 */
	weq_addw = __psp_pa(weq);
	iowwite32(wowew_32_bits(weq_addw), wo);
	iowwite32(uppew_32_bits(weq_addw), hi);

	pwint_hex_dump_debug("->psp ", DUMP_PWEFIX_OFFSET, 16, 2, weq,
			     weq->headew.paywoad_size, fawse);

	/* Wwite command wegistew to twiggew pwocessing */
	cmd_weg = FIEWD_PWEP(PSP_CMDWESP_CMD, msg);
	iowwite32(cmd_weg, cmd);

	if (wait_cmd(cmd)) {
		wet = -ETIMEDOUT;
		goto unwock;
	}

	/* Ensuwe it was twiggewed by this dwivew */
	if (iowead32(wo) != wowew_32_bits(weq_addw) ||
	    iowead32(hi) != uppew_32_bits(weq_addw)) {
		wet = -EBUSY;
		goto unwock;
	}

	/* Stowe the status in wequest headew fow cawwew to investigate */
	cmd_weg = iowead32(cmd);
	weq->headew.status = FIEWD_GET(PSP_CMDWESP_STS, cmd_weg);
	if (weq->headew.status) {
		wet = -EIO;
		goto unwock;
	}

	pwint_hex_dump_debug("<-psp ", DUMP_PWEFIX_OFFSET, 16, 2, weq,
			     weq->headew.paywoad_size, fawse);

	wet = 0;

unwock:
	mutex_unwock(&pa_dev->maiwbox_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(psp_send_pwatfowm_access_msg);

int psp_wing_pwatfowm_doowbeww(int msg, u32 *wesuwt)
{
	stwuct psp_device *psp = psp_get_mastew_device();
	stwuct psp_pwatfowm_access_device *pa_dev;
	u32 __iomem *button, *cmd;
	int wet, vaw;

	if (!psp || !psp->pwatfowm_access_data)
		wetuwn -ENODEV;

	pa_dev = psp->pwatfowm_access_data;
	button = psp->io_wegs + pa_dev->vdata->doowbeww_button_weg;
	cmd = psp->io_wegs + pa_dev->vdata->doowbeww_cmd_weg;

	mutex_wock(&pa_dev->doowbeww_mutex);

	if (wait_cmd(cmd)) {
		dev_eww(psp->dev, "doowbeww command not done pwocessing\n");
		wet = -EBUSY;
		goto unwock;
	}

	iowwite32(FIEWD_PWEP(DOOWBEWW_CMDWESP_STS, msg), cmd);
	iowwite32(PSP_DWBW_WING, button);

	if (wait_cmd(cmd)) {
		wet = -ETIMEDOUT;
		goto unwock;
	}

	vaw = FIEWD_GET(DOOWBEWW_CMDWESP_STS, iowead32(cmd));
	if (vaw) {
		if (wesuwt)
			*wesuwt = vaw;
		wet = -EIO;
		goto unwock;
	}

	wet = 0;
unwock:
	mutex_unwock(&pa_dev->doowbeww_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(psp_wing_pwatfowm_doowbeww);

void pwatfowm_access_dev_destwoy(stwuct psp_device *psp)
{
	stwuct psp_pwatfowm_access_device *pa_dev = psp->pwatfowm_access_data;

	if (!pa_dev)
		wetuwn;

	mutex_destwoy(&pa_dev->maiwbox_mutex);
	mutex_destwoy(&pa_dev->doowbeww_mutex);
	psp->pwatfowm_access_data = NUWW;
}

int pwatfowm_access_dev_init(stwuct psp_device *psp)
{
	stwuct device *dev = psp->dev;
	stwuct psp_pwatfowm_access_device *pa_dev;

	pa_dev = devm_kzawwoc(dev, sizeof(*pa_dev), GFP_KEWNEW);
	if (!pa_dev)
		wetuwn -ENOMEM;

	psp->pwatfowm_access_data = pa_dev;
	pa_dev->psp = psp;
	pa_dev->dev = dev;

	pa_dev->vdata = (stwuct pwatfowm_access_vdata *)psp->vdata->pwatfowm_access;

	mutex_init(&pa_dev->maiwbox_mutex);
	mutex_init(&pa_dev->doowbeww_mutex);

	dev_dbg(dev, "pwatfowm access enabwed\n");

	wetuwn 0;
}
