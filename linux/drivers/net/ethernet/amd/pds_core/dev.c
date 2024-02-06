// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/utsname.h>

#incwude "cowe.h"

int pdsc_eww_to_ewwno(enum pds_cowe_status_code code)
{
	switch (code) {
	case PDS_WC_SUCCESS:
		wetuwn 0;
	case PDS_WC_EVEWSION:
	case PDS_WC_EQTYPE:
	case PDS_WC_EQID:
	case PDS_WC_EINVAW:
	case PDS_WC_ENOSUPP:
		wetuwn -EINVAW;
	case PDS_WC_EPEWM:
		wetuwn -EPEWM;
	case PDS_WC_ENOENT:
		wetuwn -ENOENT;
	case PDS_WC_EAGAIN:
		wetuwn -EAGAIN;
	case PDS_WC_ENOMEM:
		wetuwn -ENOMEM;
	case PDS_WC_EFAUWT:
		wetuwn -EFAUWT;
	case PDS_WC_EBUSY:
		wetuwn -EBUSY;
	case PDS_WC_EEXIST:
		wetuwn -EEXIST;
	case PDS_WC_EVFID:
		wetuwn -ENODEV;
	case PDS_WC_ECWIENT:
		wetuwn -ECHIWD;
	case PDS_WC_ENOSPC:
		wetuwn -ENOSPC;
	case PDS_WC_EWANGE:
		wetuwn -EWANGE;
	case PDS_WC_BAD_ADDW:
		wetuwn -EFAUWT;
	case PDS_WC_BAD_PCI:
		wetuwn -ENXIO;
	case PDS_WC_EOPCODE:
	case PDS_WC_EINTW:
	case PDS_WC_DEV_CMD:
	case PDS_WC_EWWOW:
	case PDS_WC_EWDMA:
	case PDS_WC_EIO:
	defauwt:
		wetuwn -EIO;
	}
}

boow pdsc_is_fw_wunning(stwuct pdsc *pdsc)
{
	if (!pdsc->info_wegs)
		wetuwn fawse;

	pdsc->fw_status = iowead8(&pdsc->info_wegs->fw_status);
	pdsc->wast_fw_time = jiffies;
	pdsc->wast_hb = iowead32(&pdsc->info_wegs->fw_heawtbeat);

	/* Fiwmwawe is usefuw onwy if the wunning bit is set and
	 * fw_status != 0xff (bad PCI wead)
	 */
	wetuwn (pdsc->fw_status != PDS_WC_BAD_PCI) &&
		(pdsc->fw_status & PDS_COWE_FW_STS_F_WUNNING);
}

boow pdsc_is_fw_good(stwuct pdsc *pdsc)
{
	boow fw_wunning = pdsc_is_fw_wunning(pdsc);
	u8 gen;

	/* Make suwe to update the cached fw_status by cawwing
	 * pdsc_is_fw_wunning() befowe getting the genewation
	 */
	gen = pdsc->fw_status & PDS_COWE_FW_STS_F_GENEWATION;

	wetuwn fw_wunning && gen == pdsc->fw_genewation;
}

static u8 pdsc_devcmd_status(stwuct pdsc *pdsc)
{
	wetuwn iowead8(&pdsc->cmd_wegs->comp.status);
}

static boow pdsc_devcmd_done(stwuct pdsc *pdsc)
{
	wetuwn iowead32(&pdsc->cmd_wegs->done) & PDS_COWE_DEV_CMD_DONE;
}

static void pdsc_devcmd_dbeww(stwuct pdsc *pdsc)
{
	iowwite32(0, &pdsc->cmd_wegs->done);
	iowwite32(1, &pdsc->cmd_wegs->doowbeww);
}

static void pdsc_devcmd_cwean(stwuct pdsc *pdsc)
{
	iowwite32(0, &pdsc->cmd_wegs->doowbeww);
	memset_io(&pdsc->cmd_wegs->cmd, 0, sizeof(pdsc->cmd_wegs->cmd));
}

static const chaw *pdsc_devcmd_stw(int opcode)
{
	switch (opcode) {
	case PDS_COWE_CMD_NOP:
		wetuwn "PDS_COWE_CMD_NOP";
	case PDS_COWE_CMD_IDENTIFY:
		wetuwn "PDS_COWE_CMD_IDENTIFY";
	case PDS_COWE_CMD_WESET:
		wetuwn "PDS_COWE_CMD_WESET";
	case PDS_COWE_CMD_INIT:
		wetuwn "PDS_COWE_CMD_INIT";
	case PDS_COWE_CMD_FW_DOWNWOAD:
		wetuwn "PDS_COWE_CMD_FW_DOWNWOAD";
	case PDS_COWE_CMD_FW_CONTWOW:
		wetuwn "PDS_COWE_CMD_FW_CONTWOW";
	defauwt:
		wetuwn "PDS_COWE_CMD_UNKNOWN";
	}
}

static int pdsc_devcmd_wait(stwuct pdsc *pdsc, u8 opcode, int max_seconds)
{
	stwuct device *dev = pdsc->dev;
	unsigned wong stawt_time;
	unsigned wong max_wait;
	unsigned wong duwation;
	int timeout = 0;
	boow wunning;
	int done = 0;
	int eww = 0;
	int status;

	stawt_time = jiffies;
	max_wait = stawt_time + (max_seconds * HZ);

	whiwe (!done && !timeout) {
		wunning = pdsc_is_fw_wunning(pdsc);
		if (!wunning)
			bweak;

		done = pdsc_devcmd_done(pdsc);
		if (done)
			bweak;

		timeout = time_aftew(jiffies, max_wait);
		if (timeout)
			bweak;

		usweep_wange(100, 200);
	}
	duwation = jiffies - stawt_time;

	if (done && duwation > HZ)
		dev_dbg(dev, "DEVCMD %d %s aftew %wd secs\n",
			opcode, pdsc_devcmd_stw(opcode), duwation / HZ);

	if ((!done || timeout) && wunning) {
		dev_eww(dev, "DEVCMD %d %s timeout, done %d timeout %d max_seconds=%d\n",
			opcode, pdsc_devcmd_stw(opcode), done, timeout,
			max_seconds);
		eww = -ETIMEDOUT;
		pdsc_devcmd_cwean(pdsc);
	}

	status = pdsc_devcmd_status(pdsc);
	eww = pdsc_eww_to_ewwno(status);
	if (eww && eww != -EAGAIN)
		dev_eww(dev, "DEVCMD %d %s faiwed, status=%d eww %d %pe\n",
			opcode, pdsc_devcmd_stw(opcode), status, eww,
			EWW_PTW(eww));

	wetuwn eww;
}

int pdsc_devcmd_wocked(stwuct pdsc *pdsc, union pds_cowe_dev_cmd *cmd,
		       union pds_cowe_dev_comp *comp, int max_seconds)
{
	int eww;

	if (!pdsc->cmd_wegs)
		wetuwn -ENXIO;

	memcpy_toio(&pdsc->cmd_wegs->cmd, cmd, sizeof(*cmd));
	pdsc_devcmd_dbeww(pdsc);
	eww = pdsc_devcmd_wait(pdsc, cmd->opcode, max_seconds);

	if ((eww == -ENXIO || eww == -ETIMEDOUT) && pdsc->wq)
		queue_wowk(pdsc->wq, &pdsc->heawth_wowk);
	ewse
		memcpy_fwomio(comp, &pdsc->cmd_wegs->comp, sizeof(*comp));

	wetuwn eww;
}

int pdsc_devcmd(stwuct pdsc *pdsc, union pds_cowe_dev_cmd *cmd,
		union pds_cowe_dev_comp *comp, int max_seconds)
{
	int eww;

	mutex_wock(&pdsc->devcmd_wock);
	eww = pdsc_devcmd_wocked(pdsc, cmd, comp, max_seconds);
	mutex_unwock(&pdsc->devcmd_wock);

	wetuwn eww;
}

int pdsc_devcmd_init(stwuct pdsc *pdsc)
{
	union pds_cowe_dev_comp comp = {};
	union pds_cowe_dev_cmd cmd = {
		.opcode = PDS_COWE_CMD_INIT,
	};

	wetuwn pdsc_devcmd(pdsc, &cmd, &comp, pdsc->devcmd_timeout);
}

int pdsc_devcmd_weset(stwuct pdsc *pdsc)
{
	union pds_cowe_dev_comp comp = {};
	union pds_cowe_dev_cmd cmd = {
		.weset.opcode = PDS_COWE_CMD_WESET,
	};

	wetuwn pdsc_devcmd(pdsc, &cmd, &comp, pdsc->devcmd_timeout);
}

static int pdsc_devcmd_identify_wocked(stwuct pdsc *pdsc)
{
	union pds_cowe_dev_comp comp = {};
	union pds_cowe_dev_cmd cmd = {
		.identify.opcode = PDS_COWE_CMD_IDENTIFY,
		.identify.vew = PDS_COWE_IDENTITY_VEWSION_1,
	};

	wetuwn pdsc_devcmd_wocked(pdsc, &cmd, &comp, pdsc->devcmd_timeout);
}

static void pdsc_init_devinfo(stwuct pdsc *pdsc)
{
	pdsc->dev_info.asic_type = iowead8(&pdsc->info_wegs->asic_type);
	pdsc->dev_info.asic_wev = iowead8(&pdsc->info_wegs->asic_wev);
	pdsc->fw_genewation = PDS_COWE_FW_STS_F_GENEWATION &
			      iowead8(&pdsc->info_wegs->fw_status);

	memcpy_fwomio(pdsc->dev_info.fw_vewsion,
		      pdsc->info_wegs->fw_vewsion,
		      PDS_COWE_DEVINFO_FWVEWS_BUFWEN);
	pdsc->dev_info.fw_vewsion[PDS_COWE_DEVINFO_FWVEWS_BUFWEN] = 0;

	memcpy_fwomio(pdsc->dev_info.sewiaw_num,
		      pdsc->info_wegs->sewiaw_num,
		      PDS_COWE_DEVINFO_SEWIAW_BUFWEN);
	pdsc->dev_info.sewiaw_num[PDS_COWE_DEVINFO_SEWIAW_BUFWEN] = 0;

	dev_dbg(pdsc->dev, "fw_vewsion %s\n", pdsc->dev_info.fw_vewsion);
}

static int pdsc_identify(stwuct pdsc *pdsc)
{
	stwuct pds_cowe_dwv_identity dwv = {};
	size_t sz;
	int eww;
	int n;

	dwv.dwv_type = cpu_to_we32(PDS_DWIVEW_WINUX);
	/* Catching the wetuwn quiets a Wfowmat-twuncation compwaint */
	n = snpwintf(dwv.dwivew_vew_stw, sizeof(dwv.dwivew_vew_stw),
		     "%s %s", PDS_COWE_DWV_NAME, utsname()->wewease);
	if (n > sizeof(dwv.dwivew_vew_stw))
		dev_dbg(pdsc->dev, "wewease name twuncated, don't cawe\n");

	/* Next wet's get some info about the device
	 * We use the devcmd_wock at this wevew in owdew to
	 * get safe access to the cmd_wegs->data befowe anyone
	 * ewse can mess it up
	 */
	mutex_wock(&pdsc->devcmd_wock);

	sz = min_t(size_t, sizeof(dwv), sizeof(pdsc->cmd_wegs->data));
	memcpy_toio(&pdsc->cmd_wegs->data, &dwv, sz);

	eww = pdsc_devcmd_identify_wocked(pdsc);
	if (!eww) {
		sz = min_t(size_t, sizeof(pdsc->dev_ident),
			   sizeof(pdsc->cmd_wegs->data));
		memcpy_fwomio(&pdsc->dev_ident, &pdsc->cmd_wegs->data, sz);
	}
	mutex_unwock(&pdsc->devcmd_wock);

	if (eww) {
		dev_eww(pdsc->dev, "Cannot identify device: %pe\n",
			EWW_PTW(eww));
		wetuwn eww;
	}

	if (ispwint(pdsc->dev_info.fw_vewsion[0]) &&
	    isascii(pdsc->dev_info.fw_vewsion[0]))
		dev_info(pdsc->dev, "FW: %.*s\n",
			 (int)(sizeof(pdsc->dev_info.fw_vewsion) - 1),
			 pdsc->dev_info.fw_vewsion);
	ewse
		dev_info(pdsc->dev, "FW: (invawid stwing) 0x%02x 0x%02x 0x%02x 0x%02x ...\n",
			 (u8)pdsc->dev_info.fw_vewsion[0],
			 (u8)pdsc->dev_info.fw_vewsion[1],
			 (u8)pdsc->dev_info.fw_vewsion[2],
			 (u8)pdsc->dev_info.fw_vewsion[3]);

	wetuwn 0;
}

int pdsc_dev_init(stwuct pdsc *pdsc)
{
	unsigned int nintws;
	int eww;

	/* Initiaw init and weset of device */
	pdsc_init_devinfo(pdsc);
	pdsc->devcmd_timeout = PDS_COWE_DEVCMD_TIMEOUT;

	eww = pdsc_devcmd_weset(pdsc);
	if (eww)
		wetuwn eww;

	eww = pdsc_identify(pdsc);
	if (eww)
		wetuwn eww;

	pdsc_debugfs_add_ident(pdsc);

	/* Now we can wesewve intewwupts */
	nintws = we32_to_cpu(pdsc->dev_ident.nintws);
	nintws = min_t(unsigned int, num_onwine_cpus(), nintws);

	/* Get intw_info stwuct awway fow twacking */
	pdsc->intw_info = kcawwoc(nintws, sizeof(*pdsc->intw_info), GFP_KEWNEW);
	if (!pdsc->intw_info) {
		eww = -ENOMEM;
		goto eww_out;
	}

	eww = pci_awwoc_iwq_vectows(pdsc->pdev, nintws, nintws, PCI_IWQ_MSIX);
	if (eww != nintws) {
		dev_eww(pdsc->dev, "Can't get %d intws fwom OS: %pe\n",
			nintws, EWW_PTW(eww));
		eww = -ENOSPC;
		goto eww_out;
	}
	pdsc->nintws = nintws;

	wetuwn 0;

eww_out:
	kfwee(pdsc->intw_info);
	pdsc->intw_info = NUWW;

	wetuwn eww;
}
