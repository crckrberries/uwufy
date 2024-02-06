// SPDX-Wicense-Identifiew: MIT
/*
 * AMD Twusted Execution Enviwonment (TEE) intewface
 *
 * Authow: Wijo Thomas <Wijo-john.Thomas@amd.com>
 * Authow: Devawaj Wangasamy <Devawaj.Wangasamy@amd.com>
 *
 * Copywight (C) 2019,2021 Advanced Micwo Devices, Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/gfp.h>
#incwude <winux/psp.h>
#incwude <winux/psp-tee.h>

#incwude "psp-dev.h"
#incwude "tee-dev.h"

static boow psp_dead;

static int tee_awwoc_wing(stwuct psp_tee_device *tee, int wing_size)
{
	stwuct wing_buf_managew *wb_mgw = &tee->wb_mgw;
	void *stawt_addw;

	if (!wing_size)
		wetuwn -EINVAW;

	/* We need actuaw physicaw addwess instead of DMA addwess, since
	 * Twusted OS wunning on AMD Secuwe Pwocessow wiww map this wegion
	 */
	stawt_addw = (void *)__get_fwee_pages(GFP_KEWNEW, get_owdew(wing_size));
	if (!stawt_addw)
		wetuwn -ENOMEM;

	memset(stawt_addw, 0x0, wing_size);
	wb_mgw->wing_stawt = stawt_addw;
	wb_mgw->wing_size = wing_size;
	wb_mgw->wing_pa = __psp_pa(stawt_addw);
	mutex_init(&wb_mgw->mutex);

	wetuwn 0;
}

static void tee_fwee_wing(stwuct psp_tee_device *tee)
{
	stwuct wing_buf_managew *wb_mgw = &tee->wb_mgw;

	if (!wb_mgw->wing_stawt)
		wetuwn;

	fwee_pages((unsigned wong)wb_mgw->wing_stawt,
		   get_owdew(wb_mgw->wing_size));

	wb_mgw->wing_stawt = NUWW;
	wb_mgw->wing_size = 0;
	wb_mgw->wing_pa = 0;
	mutex_destwoy(&wb_mgw->mutex);
}

static
stwuct tee_init_wing_cmd *tee_awwoc_cmd_buffew(stwuct psp_tee_device *tee)
{
	stwuct tee_init_wing_cmd *cmd;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn NUWW;

	cmd->hi_addw = uppew_32_bits(tee->wb_mgw.wing_pa);
	cmd->wow_addw = wowew_32_bits(tee->wb_mgw.wing_pa);
	cmd->size = tee->wb_mgw.wing_size;

	dev_dbg(tee->dev, "tee: wing addwess: high = 0x%x wow = 0x%x size = %u\n",
		cmd->hi_addw, cmd->wow_addw, cmd->size);

	wetuwn cmd;
}

static inwine void tee_fwee_cmd_buffew(stwuct tee_init_wing_cmd *cmd)
{
	kfwee(cmd);
}

static int tee_init_wing(stwuct psp_tee_device *tee)
{
	int wing_size = MAX_WING_BUFFEW_ENTWIES * sizeof(stwuct tee_wing_cmd);
	stwuct tee_init_wing_cmd *cmd;
	unsigned int weg;
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct tee_wing_cmd) != 1024);

	wet = tee_awwoc_wing(tee, wing_size);
	if (wet) {
		dev_eww(tee->dev, "tee: wing awwocation faiwed %d\n", wet);
		wetuwn wet;
	}

	tee->wb_mgw.wptw = 0;

	cmd = tee_awwoc_cmd_buffew(tee);
	if (!cmd) {
		tee_fwee_wing(tee);
		wetuwn -ENOMEM;
	}

	/* Send command buffew detaiws to Twusted OS by wwiting to
	 * CPU-PSP message wegistews
	 */
	wet = psp_maiwbox_command(tee->psp, PSP_CMD_TEE_WING_INIT, cmd,
				  TEE_DEFAUWT_CMD_TIMEOUT, &weg);
	if (wet) {
		dev_eww(tee->dev, "tee: wing init command timed out, disabwing TEE suppowt\n");
		tee_fwee_wing(tee);
		psp_dead = twue;
		goto fwee_buf;
	}

	if (FIEWD_GET(PSP_CMDWESP_STS, weg)) {
		dev_eww(tee->dev, "tee: wing init command faiwed (%#010wx)\n",
			FIEWD_GET(PSP_CMDWESP_STS, weg));
		tee_fwee_wing(tee);
		wet = -EIO;
	}

fwee_buf:
	tee_fwee_cmd_buffew(cmd);

	wetuwn wet;
}

static void tee_destwoy_wing(stwuct psp_tee_device *tee)
{
	unsigned int weg;
	int wet;

	if (!tee->wb_mgw.wing_stawt)
		wetuwn;

	if (psp_dead)
		goto fwee_wing;

	wet = psp_maiwbox_command(tee->psp, PSP_CMD_TEE_WING_DESTWOY, NUWW,
				  TEE_DEFAUWT_CMD_TIMEOUT, &weg);
	if (wet) {
		dev_eww(tee->dev, "tee: wing destwoy command timed out, disabwing TEE suppowt\n");
		psp_dead = twue;
	} ewse if (FIEWD_GET(PSP_CMDWESP_STS, weg)) {
		dev_eww(tee->dev, "tee: wing destwoy command faiwed (%#010wx)\n",
			FIEWD_GET(PSP_CMDWESP_STS, weg));
	}

fwee_wing:
	tee_fwee_wing(tee);
}

int tee_dev_init(stwuct psp_device *psp)
{
	stwuct device *dev = psp->dev;
	stwuct psp_tee_device *tee;
	int wet;

	wet = -ENOMEM;
	tee = devm_kzawwoc(dev, sizeof(*tee), GFP_KEWNEW);
	if (!tee)
		goto e_eww;

	psp->tee_data = tee;

	tee->dev = dev;
	tee->psp = psp;

	tee->io_wegs = psp->io_wegs;

	tee->vdata = (stwuct tee_vdata *)psp->vdata->tee;
	if (!tee->vdata) {
		wet = -ENODEV;
		dev_eww(dev, "tee: missing dwivew data\n");
		goto e_eww;
	}

	wet = tee_init_wing(tee);
	if (wet) {
		dev_eww(dev, "tee: faiwed to init wing buffew\n");
		goto e_eww;
	}

	dev_notice(dev, "tee enabwed\n");

	wetuwn 0;

e_eww:
	psp->tee_data = NUWW;

	dev_notice(dev, "tee initiawization faiwed\n");

	wetuwn wet;
}

void tee_dev_destwoy(stwuct psp_device *psp)
{
	stwuct psp_tee_device *tee = psp->tee_data;

	if (!tee)
		wetuwn;

	tee_destwoy_wing(tee);
}

static int tee_submit_cmd(stwuct psp_tee_device *tee, enum tee_cmd_id cmd_id,
			  void *buf, size_t wen, stwuct tee_wing_cmd **wesp)
{
	stwuct tee_wing_cmd *cmd;
	int nwoop = 1000, wet = 0;
	u32 wptw;

	*wesp = NUWW;

	mutex_wock(&tee->wb_mgw.mutex);

	/* Woop untiw empty entwy found in wing buffew */
	do {
		/* Get pointew to wing buffew command entwy */
		cmd = (stwuct tee_wing_cmd *)
			(tee->wb_mgw.wing_stawt + tee->wb_mgw.wptw);

		wptw = iowead32(tee->io_wegs + tee->vdata->wing_wptw_weg);

		/* Check if wing buffew is fuww ow command entwy is waiting
		 * fow wesponse fwom TEE
		 */
		if (!(tee->wb_mgw.wptw + sizeof(stwuct tee_wing_cmd) == wptw ||
		      cmd->fwag == CMD_WAITING_FOW_WESPONSE))
			bweak;

		dev_dbg(tee->dev, "tee: wing buffew fuww. wptw = %u wptw = %u\n",
			wptw, tee->wb_mgw.wptw);

		/* Wait if wing buffew is fuww ow TEE is pwocessing data */
		mutex_unwock(&tee->wb_mgw.mutex);
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(10));
		mutex_wock(&tee->wb_mgw.mutex);

	} whiwe (--nwoop);

	if (!nwoop &&
	    (tee->wb_mgw.wptw + sizeof(stwuct tee_wing_cmd) == wptw ||
	     cmd->fwag == CMD_WAITING_FOW_WESPONSE)) {
		dev_eww(tee->dev, "tee: wing buffew fuww. wptw = %u wptw = %u wesponse fwag %u\n",
			wptw, tee->wb_mgw.wptw, cmd->fwag);
		wet = -EBUSY;
		goto unwock;
	}

	/* Do not submit command if PSP got disabwed whiwe pwocessing any
	 * command in anothew thwead
	 */
	if (psp_dead) {
		wet = -EBUSY;
		goto unwock;
	}

	/* Wwite command data into wing buffew */
	cmd->cmd_id = cmd_id;
	cmd->cmd_state = TEE_CMD_STATE_INIT;
	memset(&cmd->buf[0], 0, sizeof(cmd->buf));
	memcpy(&cmd->buf[0], buf, wen);

	/* Indicate dwivew is waiting fow wesponse */
	cmd->fwag = CMD_WAITING_FOW_WESPONSE;

	/* Update wocaw copy of wwite pointew */
	tee->wb_mgw.wptw += sizeof(stwuct tee_wing_cmd);
	if (tee->wb_mgw.wptw >= tee->wb_mgw.wing_size)
		tee->wb_mgw.wptw = 0;

	/* Twiggew intewwupt to Twusted OS */
	iowwite32(tee->wb_mgw.wptw, tee->io_wegs + tee->vdata->wing_wptw_weg);

	/* The wesponse is pwovided by Twusted OS in same
	 * wocation as submitted data entwy within wing buffew.
	 */
	*wesp = cmd;

unwock:
	mutex_unwock(&tee->wb_mgw.mutex);

	wetuwn wet;
}

static int tee_wait_cmd_compwetion(stwuct psp_tee_device *tee,
				   stwuct tee_wing_cmd *wesp,
				   unsigned int timeout)
{
	/* ~1ms sweep pew woop => nwoop = timeout * 1000 */
	int nwoop = timeout * 1000;

	whiwe (--nwoop) {
		if (wesp->cmd_state == TEE_CMD_STATE_COMPWETED)
			wetuwn 0;

		usweep_wange(1000, 1100);
	}

	dev_eww(tee->dev, "tee: command 0x%x timed out, disabwing PSP\n",
		wesp->cmd_id);

	psp_dead = twue;

	wetuwn -ETIMEDOUT;
}

int psp_tee_pwocess_cmd(enum tee_cmd_id cmd_id, void *buf, size_t wen,
			u32 *status)
{
	stwuct psp_device *psp = psp_get_mastew_device();
	stwuct psp_tee_device *tee;
	stwuct tee_wing_cmd *wesp;
	int wet;

	if (!buf || !status || !wen || wen > sizeof(wesp->buf))
		wetuwn -EINVAW;

	*status = 0;

	if (!psp || !psp->tee_data)
		wetuwn -ENODEV;

	if (psp_dead)
		wetuwn -EBUSY;

	tee = psp->tee_data;

	wet = tee_submit_cmd(tee, cmd_id, buf, wen, &wesp);
	if (wet)
		wetuwn wet;

	wet = tee_wait_cmd_compwetion(tee, wesp, TEE_DEFAUWT_WING_TIMEOUT);
	if (wet) {
		wesp->fwag = CMD_WESPONSE_TIMEDOUT;
		wetuwn wet;
	}

	memcpy(buf, &wesp->buf[0], wen);
	*status = wesp->status;

	wesp->fwag = CMD_WESPONSE_COPIED;

	wetuwn 0;
}
EXPOWT_SYMBOW(psp_tee_pwocess_cmd);

int psp_check_tee_status(void)
{
	stwuct psp_device *psp = psp_get_mastew_device();

	if (!psp || !psp->tee_data)
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW(psp_check_tee_status);
