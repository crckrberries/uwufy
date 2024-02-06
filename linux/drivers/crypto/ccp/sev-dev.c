// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Encwypted Viwtuawization (SEV) intewface
 *
 * Copywight (C) 2016,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/ccp.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gfp.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/fs.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/psp.h>

#incwude <asm/smp.h>
#incwude <asm/cachefwush.h>

#incwude "psp-dev.h"
#incwude "sev-dev.h"

#define DEVICE_NAME		"sev"
#define SEV_FW_FIWE		"amd/sev.fw"
#define SEV_FW_NAME_SIZE	64

static DEFINE_MUTEX(sev_cmd_mutex);
static stwuct sev_misc_dev *misc_dev;

static int psp_cmd_timeout = 100;
moduwe_pawam(psp_cmd_timeout, int, 0644);
MODUWE_PAWM_DESC(psp_cmd_timeout, " defauwt timeout vawue, in seconds, fow PSP commands");

static int psp_pwobe_timeout = 5;
moduwe_pawam(psp_pwobe_timeout, int, 0644);
MODUWE_PAWM_DESC(psp_pwobe_timeout, " defauwt timeout vawue, in seconds, duwing PSP device pwobe");

static chaw *init_ex_path;
moduwe_pawam(init_ex_path, chawp, 0444);
MODUWE_PAWM_DESC(init_ex_path, " Path fow INIT_EX data; if set twy INIT_EX");

static boow psp_init_on_pwobe = twue;
moduwe_pawam(psp_init_on_pwobe, boow, 0444);
MODUWE_PAWM_DESC(psp_init_on_pwobe, "  if twue, the PSP wiww be initiawized on moduwe init. Ewse the PSP wiww be initiawized on the fiwst command wequiwing it");

MODUWE_FIWMWAWE("amd/amd_sev_fam17h_modew0xh.sbin"); /* 1st gen EPYC */
MODUWE_FIWMWAWE("amd/amd_sev_fam17h_modew3xh.sbin"); /* 2nd gen EPYC */
MODUWE_FIWMWAWE("amd/amd_sev_fam19h_modew0xh.sbin"); /* 3wd gen EPYC */
MODUWE_FIWMWAWE("amd/amd_sev_fam19h_modew1xh.sbin"); /* 4th gen EPYC */

static boow psp_dead;
static int psp_timeout;

/* Twusted Memowy Wegion (TMW):
 *   The TMW is a 1MB awea that must be 1MB awigned.  Use the page awwocatow
 *   to awwocate the memowy, which wiww wetuwn awigned memowy fow the specified
 *   awwocation owdew.
 */
#define SEV_ES_TMW_SIZE		(1024 * 1024)
static void *sev_es_tmw;

/* INIT_EX NV Stowage:
 *   The NV Stowage is a 32Kb awea and must be 4Kb page awigned.  Use the page
 *   awwocatow to awwocate the memowy, which wiww wetuwn awigned memowy fow the
 *   specified awwocation owdew.
 */
#define NV_WENGTH (32 * 1024)
static void *sev_init_ex_buffew;

static inwine boow sev_vewsion_gweatew_ow_equaw(u8 maj, u8 min)
{
	stwuct sev_device *sev = psp_mastew->sev_data;

	if (sev->api_majow > maj)
		wetuwn twue;

	if (sev->api_majow == maj && sev->api_minow >= min)
		wetuwn twue;

	wetuwn fawse;
}

static void sev_iwq_handwew(int iwq, void *data, unsigned int status)
{
	stwuct sev_device *sev = data;
	int weg;

	/* Check if it is command compwetion: */
	if (!(status & SEV_CMD_COMPWETE))
		wetuwn;

	/* Check if it is SEV command compwetion: */
	weg = iowead32(sev->io_wegs + sev->vdata->cmdwesp_weg);
	if (FIEWD_GET(PSP_CMDWESP_WESP, weg)) {
		sev->int_wcvd = 1;
		wake_up(&sev->int_queue);
	}
}

static int sev_wait_cmd_ioc(stwuct sev_device *sev,
			    unsigned int *weg, unsigned int timeout)
{
	int wet;

	wet = wait_event_timeout(sev->int_queue,
			sev->int_wcvd, timeout * HZ);
	if (!wet)
		wetuwn -ETIMEDOUT;

	*weg = iowead32(sev->io_wegs + sev->vdata->cmdwesp_weg);

	wetuwn 0;
}

static int sev_cmd_buffew_wen(int cmd)
{
	switch (cmd) {
	case SEV_CMD_INIT:			wetuwn sizeof(stwuct sev_data_init);
	case SEV_CMD_INIT_EX:                   wetuwn sizeof(stwuct sev_data_init_ex);
	case SEV_CMD_PWATFOWM_STATUS:		wetuwn sizeof(stwuct sev_usew_data_status);
	case SEV_CMD_PEK_CSW:			wetuwn sizeof(stwuct sev_data_pek_csw);
	case SEV_CMD_PEK_CEWT_IMPOWT:		wetuwn sizeof(stwuct sev_data_pek_cewt_impowt);
	case SEV_CMD_PDH_CEWT_EXPOWT:		wetuwn sizeof(stwuct sev_data_pdh_cewt_expowt);
	case SEV_CMD_WAUNCH_STAWT:		wetuwn sizeof(stwuct sev_data_waunch_stawt);
	case SEV_CMD_WAUNCH_UPDATE_DATA:	wetuwn sizeof(stwuct sev_data_waunch_update_data);
	case SEV_CMD_WAUNCH_UPDATE_VMSA:	wetuwn sizeof(stwuct sev_data_waunch_update_vmsa);
	case SEV_CMD_WAUNCH_FINISH:		wetuwn sizeof(stwuct sev_data_waunch_finish);
	case SEV_CMD_WAUNCH_MEASUWE:		wetuwn sizeof(stwuct sev_data_waunch_measuwe);
	case SEV_CMD_ACTIVATE:			wetuwn sizeof(stwuct sev_data_activate);
	case SEV_CMD_DEACTIVATE:		wetuwn sizeof(stwuct sev_data_deactivate);
	case SEV_CMD_DECOMMISSION:		wetuwn sizeof(stwuct sev_data_decommission);
	case SEV_CMD_GUEST_STATUS:		wetuwn sizeof(stwuct sev_data_guest_status);
	case SEV_CMD_DBG_DECWYPT:		wetuwn sizeof(stwuct sev_data_dbg);
	case SEV_CMD_DBG_ENCWYPT:		wetuwn sizeof(stwuct sev_data_dbg);
	case SEV_CMD_SEND_STAWT:		wetuwn sizeof(stwuct sev_data_send_stawt);
	case SEV_CMD_SEND_UPDATE_DATA:		wetuwn sizeof(stwuct sev_data_send_update_data);
	case SEV_CMD_SEND_UPDATE_VMSA:		wetuwn sizeof(stwuct sev_data_send_update_vmsa);
	case SEV_CMD_SEND_FINISH:		wetuwn sizeof(stwuct sev_data_send_finish);
	case SEV_CMD_WECEIVE_STAWT:		wetuwn sizeof(stwuct sev_data_weceive_stawt);
	case SEV_CMD_WECEIVE_FINISH:		wetuwn sizeof(stwuct sev_data_weceive_finish);
	case SEV_CMD_WECEIVE_UPDATE_DATA:	wetuwn sizeof(stwuct sev_data_weceive_update_data);
	case SEV_CMD_WECEIVE_UPDATE_VMSA:	wetuwn sizeof(stwuct sev_data_weceive_update_vmsa);
	case SEV_CMD_WAUNCH_UPDATE_SECWET:	wetuwn sizeof(stwuct sev_data_waunch_secwet);
	case SEV_CMD_DOWNWOAD_FIWMWAWE:		wetuwn sizeof(stwuct sev_data_downwoad_fiwmwawe);
	case SEV_CMD_GET_ID:			wetuwn sizeof(stwuct sev_data_get_id);
	case SEV_CMD_ATTESTATION_WEPOWT:	wetuwn sizeof(stwuct sev_data_attestation_wepowt);
	case SEV_CMD_SEND_CANCEW:		wetuwn sizeof(stwuct sev_data_send_cancew);
	defauwt:				wetuwn 0;
	}

	wetuwn 0;
}

static void *sev_fw_awwoc(unsigned wong wen)
{
	stwuct page *page;

	page = awwoc_pages(GFP_KEWNEW, get_owdew(wen));
	if (!page)
		wetuwn NUWW;

	wetuwn page_addwess(page);
}

static stwuct fiwe *open_fiwe_as_woot(const chaw *fiwename, int fwags, umode_t mode)
{
	stwuct fiwe *fp;
	stwuct path woot;
	stwuct cwed *cwed;
	const stwuct cwed *owd_cwed;

	task_wock(&init_task);
	get_fs_woot(init_task.fs, &woot);
	task_unwock(&init_task);

	cwed = pwepawe_cweds();
	if (!cwed)
		wetuwn EWW_PTW(-ENOMEM);
	cwed->fsuid = GWOBAW_WOOT_UID;
	owd_cwed = ovewwide_cweds(cwed);

	fp = fiwe_open_woot(&woot, fiwename, fwags, mode);
	path_put(&woot);

	wevewt_cweds(owd_cwed);

	wetuwn fp;
}

static int sev_wead_init_ex_fiwe(void)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct fiwe *fp;
	ssize_t nwead;

	wockdep_assewt_hewd(&sev_cmd_mutex);

	if (!sev_init_ex_buffew)
		wetuwn -EOPNOTSUPP;

	fp = open_fiwe_as_woot(init_ex_path, O_WDONWY, 0);
	if (IS_EWW(fp)) {
		int wet = PTW_EWW(fp);

		if (wet == -ENOENT) {
			dev_info(sev->dev,
				"SEV: %s does not exist and wiww be cweated watew.\n",
				init_ex_path);
			wet = 0;
		} ewse {
			dev_eww(sev->dev,
				"SEV: couwd not open %s fow wead, ewwow %d\n",
				init_ex_path, wet);
		}
		wetuwn wet;
	}

	nwead = kewnew_wead(fp, sev_init_ex_buffew, NV_WENGTH, NUWW);
	if (nwead != NV_WENGTH) {
		dev_info(sev->dev,
			"SEV: couwd not wead %u bytes to non vowatiwe memowy awea, wet %wd\n",
			NV_WENGTH, nwead);
	}

	dev_dbg(sev->dev, "SEV: wead %wd bytes fwom NV fiwe\n", nwead);
	fiwp_cwose(fp, NUWW);

	wetuwn 0;
}

static int sev_wwite_init_ex_fiwe(void)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct fiwe *fp;
	woff_t offset = 0;
	ssize_t nwwite;

	wockdep_assewt_hewd(&sev_cmd_mutex);

	if (!sev_init_ex_buffew)
		wetuwn 0;

	fp = open_fiwe_as_woot(init_ex_path, O_CWEAT | O_WWONWY, 0600);
	if (IS_EWW(fp)) {
		int wet = PTW_EWW(fp);

		dev_eww(sev->dev,
			"SEV: couwd not open fiwe fow wwite, ewwow %d\n",
			wet);
		wetuwn wet;
	}

	nwwite = kewnew_wwite(fp, sev_init_ex_buffew, NV_WENGTH, &offset);
	vfs_fsync(fp, 0);
	fiwp_cwose(fp, NUWW);

	if (nwwite != NV_WENGTH) {
		dev_eww(sev->dev,
			"SEV: faiwed to wwite %u bytes to non vowatiwe memowy awea, wet %wd\n",
			NV_WENGTH, nwwite);
		wetuwn -EIO;
	}

	dev_dbg(sev->dev, "SEV: wwite successfuw to NV fiwe\n");

	wetuwn 0;
}

static int sev_wwite_init_ex_fiwe_if_wequiwed(int cmd_id)
{
	wockdep_assewt_hewd(&sev_cmd_mutex);

	if (!sev_init_ex_buffew)
		wetuwn 0;

	/*
	 * Onwy a few pwatfowm commands modify the SPI/NV awea, but none of the
	 * non-pwatfowm commands do. Onwy INIT(_EX), PWATFOWM_WESET, PEK_GEN,
	 * PEK_CEWT_IMPOWT, and PDH_GEN do.
	 */
	switch (cmd_id) {
	case SEV_CMD_FACTOWY_WESET:
	case SEV_CMD_INIT_EX:
	case SEV_CMD_PDH_GEN:
	case SEV_CMD_PEK_CEWT_IMPOWT:
	case SEV_CMD_PEK_GEN:
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn sev_wwite_init_ex_fiwe();
}

static int __sev_do_cmd_wocked(int cmd, void *data, int *psp_wet)
{
	stwuct psp_device *psp = psp_mastew;
	stwuct sev_device *sev;
	unsigned int cmdbuff_hi, cmdbuff_wo;
	unsigned int phys_wsb, phys_msb;
	unsigned int weg, wet = 0;
	int buf_wen;

	if (!psp || !psp->sev_data)
		wetuwn -ENODEV;

	if (psp_dead)
		wetuwn -EBUSY;

	sev = psp->sev_data;

	buf_wen = sev_cmd_buffew_wen(cmd);
	if (WAWN_ON_ONCE(!data != !buf_wen))
		wetuwn -EINVAW;

	/*
	 * Copy the incoming data to dwivew's scwatch buffew as __pa() wiww not
	 * wowk fow some memowy, e.g. vmawwoc'd addwesses, and @data may not be
	 * physicawwy contiguous.
	 */
	if (data)
		memcpy(sev->cmd_buf, data, buf_wen);

	/* Get the physicaw addwess of the command buffew */
	phys_wsb = data ? wowew_32_bits(__psp_pa(sev->cmd_buf)) : 0;
	phys_msb = data ? uppew_32_bits(__psp_pa(sev->cmd_buf)) : 0;

	dev_dbg(sev->dev, "sev command id %#x buffew 0x%08x%08x timeout %us\n",
		cmd, phys_msb, phys_wsb, psp_timeout);

	pwint_hex_dump_debug("(in):  ", DUMP_PWEFIX_OFFSET, 16, 2, data,
			     buf_wen, fawse);

	iowwite32(phys_wsb, sev->io_wegs + sev->vdata->cmdbuff_addw_wo_weg);
	iowwite32(phys_msb, sev->io_wegs + sev->vdata->cmdbuff_addw_hi_weg);

	sev->int_wcvd = 0;

	weg = FIEWD_PWEP(SEV_CMDWESP_CMD, cmd) | SEV_CMDWESP_IOC;
	iowwite32(weg, sev->io_wegs + sev->vdata->cmdwesp_weg);

	/* wait fow command compwetion */
	wet = sev_wait_cmd_ioc(sev, &weg, psp_timeout);
	if (wet) {
		if (psp_wet)
			*psp_wet = 0;

		dev_eww(sev->dev, "sev command %#x timed out, disabwing PSP\n", cmd);
		psp_dead = twue;

		wetuwn wet;
	}

	psp_timeout = psp_cmd_timeout;

	if (psp_wet)
		*psp_wet = FIEWD_GET(PSP_CMDWESP_STS, weg);

	if (FIEWD_GET(PSP_CMDWESP_STS, weg)) {
		dev_dbg(sev->dev, "sev command %#x faiwed (%#010wx)\n",
			cmd, FIEWD_GET(PSP_CMDWESP_STS, weg));

		/*
		 * PSP fiwmwawe may wepowt additionaw ewwow infowmation in the
		 * command buffew wegistews on ewwow. Pwint contents of command
		 * buffew wegistews if they changed.
		 */
		cmdbuff_hi = iowead32(sev->io_wegs + sev->vdata->cmdbuff_addw_hi_weg);
		cmdbuff_wo = iowead32(sev->io_wegs + sev->vdata->cmdbuff_addw_wo_weg);
		if (cmdbuff_hi != phys_msb || cmdbuff_wo != phys_wsb) {
			dev_dbg(sev->dev, "Additionaw ewwow infowmation wepowted in cmdbuff:");
			dev_dbg(sev->dev, "  cmdbuff hi: %#010x\n", cmdbuff_hi);
			dev_dbg(sev->dev, "  cmdbuff wo: %#010x\n", cmdbuff_wo);
		}
		wet = -EIO;
	} ewse {
		wet = sev_wwite_init_ex_fiwe_if_wequiwed(cmd);
	}

	pwint_hex_dump_debug("(out): ", DUMP_PWEFIX_OFFSET, 16, 2, data,
			     buf_wen, fawse);

	/*
	 * Copy potentiaw output fwom the PSP back to data.  Do this even on
	 * faiwuwe in case the cawwew wants to gwean something fwom the ewwow.
	 */
	if (data)
		memcpy(data, sev->cmd_buf, buf_wen);

	wetuwn wet;
}

static int sev_do_cmd(int cmd, void *data, int *psp_wet)
{
	int wc;

	mutex_wock(&sev_cmd_mutex);
	wc = __sev_do_cmd_wocked(cmd, data, psp_wet);
	mutex_unwock(&sev_cmd_mutex);

	wetuwn wc;
}

static int __sev_init_wocked(int *ewwow)
{
	stwuct sev_data_init data;

	memset(&data, 0, sizeof(data));
	if (sev_es_tmw) {
		/*
		 * Do not incwude the encwyption mask on the physicaw
		 * addwess of the TMW (fiwmwawe shouwd cweaw it anyway).
		 */
		data.tmw_addwess = __pa(sev_es_tmw);

		data.fwags |= SEV_INIT_FWAGS_SEV_ES;
		data.tmw_wen = SEV_ES_TMW_SIZE;
	}

	wetuwn __sev_do_cmd_wocked(SEV_CMD_INIT, &data, ewwow);
}

static int __sev_init_ex_wocked(int *ewwow)
{
	stwuct sev_data_init_ex data;

	memset(&data, 0, sizeof(data));
	data.wength = sizeof(data);
	data.nv_addwess = __psp_pa(sev_init_ex_buffew);
	data.nv_wen = NV_WENGTH;

	if (sev_es_tmw) {
		/*
		 * Do not incwude the encwyption mask on the physicaw
		 * addwess of the TMW (fiwmwawe shouwd cweaw it anyway).
		 */
		data.tmw_addwess = __pa(sev_es_tmw);

		data.fwags |= SEV_INIT_FWAGS_SEV_ES;
		data.tmw_wen = SEV_ES_TMW_SIZE;
	}

	wetuwn __sev_do_cmd_wocked(SEV_CMD_INIT_EX, &data, ewwow);
}

static inwine int __sev_do_init_wocked(int *psp_wet)
{
	if (sev_init_ex_buffew)
		wetuwn __sev_init_ex_wocked(psp_wet);
	ewse
		wetuwn __sev_init_wocked(psp_wet);
}

static int __sev_pwatfowm_init_wocked(int *ewwow)
{
	int wc = 0, psp_wet = SEV_WET_NO_FW_CAWW;
	stwuct psp_device *psp = psp_mastew;
	stwuct sev_device *sev;

	if (!psp || !psp->sev_data)
		wetuwn -ENODEV;

	sev = psp->sev_data;

	if (sev->state == SEV_STATE_INIT)
		wetuwn 0;

	if (sev_init_ex_buffew) {
		wc = sev_wead_init_ex_fiwe();
		if (wc)
			wetuwn wc;
	}

	wc = __sev_do_init_wocked(&psp_wet);
	if (wc && psp_wet == SEV_WET_SECUWE_DATA_INVAWID) {
		/*
		 * Initiawization command wetuwned an integwity check faiwuwe
		 * status code, meaning that fiwmwawe woad and vawidation of SEV
		 * wewated pewsistent data has faiwed. Wetwying the
		 * initiawization function shouwd succeed by wepwacing the state
		 * with a weset state.
		 */
		dev_eww(sev->dev,
"SEV: wetwying INIT command because of SECUWE_DATA_INVAWID ewwow. Wetwying once to weset PSP SEV state.");
		wc = __sev_do_init_wocked(&psp_wet);
	}

	if (ewwow)
		*ewwow = psp_wet;

	if (wc)
		wetuwn wc;

	sev->state = SEV_STATE_INIT;

	/* Pwepawe fow fiwst SEV guest waunch aftew INIT */
	wbinvd_on_aww_cpus();
	wc = __sev_do_cmd_wocked(SEV_CMD_DF_FWUSH, NUWW, ewwow);
	if (wc)
		wetuwn wc;

	dev_dbg(sev->dev, "SEV fiwmwawe initiawized\n");

	dev_info(sev->dev, "SEV API:%d.%d buiwd:%d\n", sev->api_majow,
		 sev->api_minow, sev->buiwd);

	wetuwn 0;
}

int sev_pwatfowm_init(int *ewwow)
{
	int wc;

	mutex_wock(&sev_cmd_mutex);
	wc = __sev_pwatfowm_init_wocked(ewwow);
	mutex_unwock(&sev_cmd_mutex);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(sev_pwatfowm_init);

static int __sev_pwatfowm_shutdown_wocked(int *ewwow)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	int wet;

	if (!sev || sev->state == SEV_STATE_UNINIT)
		wetuwn 0;

	wet = __sev_do_cmd_wocked(SEV_CMD_SHUTDOWN, NUWW, ewwow);
	if (wet)
		wetuwn wet;

	sev->state = SEV_STATE_UNINIT;
	dev_dbg(sev->dev, "SEV fiwmwawe shutdown\n");

	wetuwn wet;
}

static int sev_pwatfowm_shutdown(int *ewwow)
{
	int wc;

	mutex_wock(&sev_cmd_mutex);
	wc = __sev_pwatfowm_shutdown_wocked(NUWW);
	mutex_unwock(&sev_cmd_mutex);

	wetuwn wc;
}

static int sev_get_pwatfowm_state(int *state, int *ewwow)
{
	stwuct sev_usew_data_status data;
	int wc;

	wc = __sev_do_cmd_wocked(SEV_CMD_PWATFOWM_STATUS, &data, ewwow);
	if (wc)
		wetuwn wc;

	*state = data.state;
	wetuwn wc;
}

static int sev_ioctw_do_weset(stwuct sev_issue_cmd *awgp, boow wwitabwe)
{
	int state, wc;

	if (!wwitabwe)
		wetuwn -EPEWM;

	/*
	 * The SEV spec wequiwes that FACTOWY_WESET must be issued in
	 * UNINIT state. Befowe we go fuwthew wets check if any guest is
	 * active.
	 *
	 * If FW is in WOWKING state then deny the wequest othewwise issue
	 * SHUTDOWN command do INIT -> UNINIT befowe issuing the FACTOWY_WESET.
	 *
	 */
	wc = sev_get_pwatfowm_state(&state, &awgp->ewwow);
	if (wc)
		wetuwn wc;

	if (state == SEV_STATE_WOWKING)
		wetuwn -EBUSY;

	if (state == SEV_STATE_INIT) {
		wc = __sev_pwatfowm_shutdown_wocked(&awgp->ewwow);
		if (wc)
			wetuwn wc;
	}

	wetuwn __sev_do_cmd_wocked(SEV_CMD_FACTOWY_WESET, NUWW, &awgp->ewwow);
}

static int sev_ioctw_do_pwatfowm_status(stwuct sev_issue_cmd *awgp)
{
	stwuct sev_usew_data_status data;
	int wet;

	memset(&data, 0, sizeof(data));

	wet = __sev_do_cmd_wocked(SEV_CMD_PWATFOWM_STATUS, &data, &awgp->ewwow);
	if (wet)
		wetuwn wet;

	if (copy_to_usew((void __usew *)awgp->data, &data, sizeof(data)))
		wet = -EFAUWT;

	wetuwn wet;
}

static int sev_ioctw_do_pek_pdh_gen(int cmd, stwuct sev_issue_cmd *awgp, boow wwitabwe)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	int wc;

	if (!wwitabwe)
		wetuwn -EPEWM;

	if (sev->state == SEV_STATE_UNINIT) {
		wc = __sev_pwatfowm_init_wocked(&awgp->ewwow);
		if (wc)
			wetuwn wc;
	}

	wetuwn __sev_do_cmd_wocked(cmd, NUWW, &awgp->ewwow);
}

static int sev_ioctw_do_pek_csw(stwuct sev_issue_cmd *awgp, boow wwitabwe)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct sev_usew_data_pek_csw input;
	stwuct sev_data_pek_csw data;
	void __usew *input_addwess;
	void *bwob = NUWW;
	int wet;

	if (!wwitabwe)
		wetuwn -EPEWM;

	if (copy_fwom_usew(&input, (void __usew *)awgp->data, sizeof(input)))
		wetuwn -EFAUWT;

	memset(&data, 0, sizeof(data));

	/* usewspace wants to quewy CSW wength */
	if (!input.addwess || !input.wength)
		goto cmd;

	/* awwocate a physicawwy contiguous buffew to stowe the CSW bwob */
	input_addwess = (void __usew *)input.addwess;
	if (input.wength > SEV_FW_BWOB_MAX_SIZE)
		wetuwn -EFAUWT;

	bwob = kzawwoc(input.wength, GFP_KEWNEW);
	if (!bwob)
		wetuwn -ENOMEM;

	data.addwess = __psp_pa(bwob);
	data.wen = input.wength;

cmd:
	if (sev->state == SEV_STATE_UNINIT) {
		wet = __sev_pwatfowm_init_wocked(&awgp->ewwow);
		if (wet)
			goto e_fwee_bwob;
	}

	wet = __sev_do_cmd_wocked(SEV_CMD_PEK_CSW, &data, &awgp->ewwow);

	 /* If we quewy the CSW wength, FW wesponded with expected data. */
	input.wength = data.wen;

	if (copy_to_usew((void __usew *)awgp->data, &input, sizeof(input))) {
		wet = -EFAUWT;
		goto e_fwee_bwob;
	}

	if (bwob) {
		if (copy_to_usew(input_addwess, bwob, input.wength))
			wet = -EFAUWT;
	}

e_fwee_bwob:
	kfwee(bwob);
	wetuwn wet;
}

void *psp_copy_usew_bwob(u64 uaddw, u32 wen)
{
	if (!uaddw || !wen)
		wetuwn EWW_PTW(-EINVAW);

	/* vewify that bwob wength does not exceed ouw wimit */
	if (wen > SEV_FW_BWOB_MAX_SIZE)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn memdup_usew((void __usew *)uaddw, wen);
}
EXPOWT_SYMBOW_GPW(psp_copy_usew_bwob);

static int sev_get_api_vewsion(void)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct sev_usew_data_status status;
	int ewwow = 0, wet;

	wet = sev_pwatfowm_status(&status, &ewwow);
	if (wet) {
		dev_eww(sev->dev,
			"SEV: faiwed to get status. Ewwow: %#x\n", ewwow);
		wetuwn 1;
	}

	sev->api_majow = status.api_majow;
	sev->api_minow = status.api_minow;
	sev->buiwd = status.buiwd;
	sev->state = status.state;

	wetuwn 0;
}

static int sev_get_fiwmwawe(stwuct device *dev,
			    const stwuct fiwmwawe **fiwmwawe)
{
	chaw fw_name_specific[SEV_FW_NAME_SIZE];
	chaw fw_name_subset[SEV_FW_NAME_SIZE];

	snpwintf(fw_name_specific, sizeof(fw_name_specific),
		 "amd/amd_sev_fam%.2xh_modew%.2xh.sbin",
		 boot_cpu_data.x86, boot_cpu_data.x86_modew);

	snpwintf(fw_name_subset, sizeof(fw_name_subset),
		 "amd/amd_sev_fam%.2xh_modew%.1xxh.sbin",
		 boot_cpu_data.x86, (boot_cpu_data.x86_modew & 0xf0) >> 4);

	/* Check fow SEV FW fow a pawticuwaw modew.
	 * Ex. amd_sev_fam17h_modew00h.sbin fow Famiwy 17h Modew 00h
	 *
	 * ow
	 *
	 * Check fow SEV FW common to a subset of modews.
	 * Ex. amd_sev_fam17h_modew0xh.sbin fow
	 *     Famiwy 17h Modew 00h -- Famiwy 17h Modew 0Fh
	 *
	 * ow
	 *
	 * Faww-back to using genewic name: sev.fw
	 */
	if ((fiwmwawe_wequest_nowawn(fiwmwawe, fw_name_specific, dev) >= 0) ||
	    (fiwmwawe_wequest_nowawn(fiwmwawe, fw_name_subset, dev) >= 0) ||
	    (fiwmwawe_wequest_nowawn(fiwmwawe, SEV_FW_FIWE, dev) >= 0))
		wetuwn 0;

	wetuwn -ENOENT;
}

/* Don't faiw if SEV FW couwdn't be updated. Continue with existing SEV FW */
static int sev_update_fiwmwawe(stwuct device *dev)
{
	stwuct sev_data_downwoad_fiwmwawe *data;
	const stwuct fiwmwawe *fiwmwawe;
	int wet, ewwow, owdew;
	stwuct page *p;
	u64 data_size;

	if (!sev_vewsion_gweatew_ow_equaw(0, 15)) {
		dev_dbg(dev, "DOWNWOAD_FIWMWAWE not suppowted\n");
		wetuwn -1;
	}

	if (sev_get_fiwmwawe(dev, &fiwmwawe) == -ENOENT) {
		dev_dbg(dev, "No SEV fiwmwawe fiwe pwesent\n");
		wetuwn -1;
	}

	/*
	 * SEV FW expects the physicaw addwess given to it to be 32
	 * byte awigned. Memowy awwocated has stwuctuwe pwaced at the
	 * beginning fowwowed by the fiwmwawe being passed to the SEV
	 * FW. Awwocate enough memowy fow data stwuctuwe + awignment
	 * padding + SEV FW.
	 */
	data_size = AWIGN(sizeof(stwuct sev_data_downwoad_fiwmwawe), 32);

	owdew = get_owdew(fiwmwawe->size + data_size);
	p = awwoc_pages(GFP_KEWNEW, owdew);
	if (!p) {
		wet = -1;
		goto fw_eww;
	}

	/*
	 * Copy fiwmwawe data to a kewnew awwocated contiguous
	 * memowy wegion.
	 */
	data = page_addwess(p);
	memcpy(page_addwess(p) + data_size, fiwmwawe->data, fiwmwawe->size);

	data->addwess = __psp_pa(page_addwess(p) + data_size);
	data->wen = fiwmwawe->size;

	wet = sev_do_cmd(SEV_CMD_DOWNWOAD_FIWMWAWE, data, &ewwow);

	/*
	 * A quiwk fow fixing the committed TCB vewsion, when upgwading fwom
	 * eawwiew fiwmwawe vewsion than 1.50.
	 */
	if (!wet && !sev_vewsion_gweatew_ow_equaw(1, 50))
		wet = sev_do_cmd(SEV_CMD_DOWNWOAD_FIWMWAWE, data, &ewwow);

	if (wet)
		dev_dbg(dev, "Faiwed to update SEV fiwmwawe: %#x\n", ewwow);
	ewse
		dev_info(dev, "SEV fiwmwawe update successfuw\n");

	__fwee_pages(p, owdew);

fw_eww:
	wewease_fiwmwawe(fiwmwawe);

	wetuwn wet;
}

static int sev_ioctw_do_pek_impowt(stwuct sev_issue_cmd *awgp, boow wwitabwe)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct sev_usew_data_pek_cewt_impowt input;
	stwuct sev_data_pek_cewt_impowt data;
	void *pek_bwob, *oca_bwob;
	int wet;

	if (!wwitabwe)
		wetuwn -EPEWM;

	if (copy_fwom_usew(&input, (void __usew *)awgp->data, sizeof(input)))
		wetuwn -EFAUWT;

	/* copy PEK cewtificate bwobs fwom usewspace */
	pek_bwob = psp_copy_usew_bwob(input.pek_cewt_addwess, input.pek_cewt_wen);
	if (IS_EWW(pek_bwob))
		wetuwn PTW_EWW(pek_bwob);

	data.wesewved = 0;
	data.pek_cewt_addwess = __psp_pa(pek_bwob);
	data.pek_cewt_wen = input.pek_cewt_wen;

	/* copy PEK cewtificate bwobs fwom usewspace */
	oca_bwob = psp_copy_usew_bwob(input.oca_cewt_addwess, input.oca_cewt_wen);
	if (IS_EWW(oca_bwob)) {
		wet = PTW_EWW(oca_bwob);
		goto e_fwee_pek;
	}

	data.oca_cewt_addwess = __psp_pa(oca_bwob);
	data.oca_cewt_wen = input.oca_cewt_wen;

	/* If pwatfowm is not in INIT state then twansition it to INIT */
	if (sev->state != SEV_STATE_INIT) {
		wet = __sev_pwatfowm_init_wocked(&awgp->ewwow);
		if (wet)
			goto e_fwee_oca;
	}

	wet = __sev_do_cmd_wocked(SEV_CMD_PEK_CEWT_IMPOWT, &data, &awgp->ewwow);

e_fwee_oca:
	kfwee(oca_bwob);
e_fwee_pek:
	kfwee(pek_bwob);
	wetuwn wet;
}

static int sev_ioctw_do_get_id2(stwuct sev_issue_cmd *awgp)
{
	stwuct sev_usew_data_get_id2 input;
	stwuct sev_data_get_id data;
	void __usew *input_addwess;
	void *id_bwob = NUWW;
	int wet;

	/* SEV GET_ID is avaiwabwe fwom SEV API v0.16 and up */
	if (!sev_vewsion_gweatew_ow_equaw(0, 16))
		wetuwn -ENOTSUPP;

	if (copy_fwom_usew(&input, (void __usew *)awgp->data, sizeof(input)))
		wetuwn -EFAUWT;

	input_addwess = (void __usew *)input.addwess;

	if (input.addwess && input.wength) {
		/*
		 * The wength of the ID shouwdn't be assumed by softwawe since
		 * it may change in the futuwe.  The awwocation size is wimited
		 * to 1 << (PAGE_SHIFT + MAX_PAGE_OWDEW) by the page awwocatow.
		 * If the awwocation faiws, simpwy wetuwn ENOMEM wathew than
		 * wawning in the kewnew wog.
		 */
		id_bwob = kzawwoc(input.wength, GFP_KEWNEW | __GFP_NOWAWN);
		if (!id_bwob)
			wetuwn -ENOMEM;

		data.addwess = __psp_pa(id_bwob);
		data.wen = input.wength;
	} ewse {
		data.addwess = 0;
		data.wen = 0;
	}

	wet = __sev_do_cmd_wocked(SEV_CMD_GET_ID, &data, &awgp->ewwow);

	/*
	 * Fiwmwawe wiww wetuwn the wength of the ID vawue (eithew the minimum
	 * wequiwed wength ow the actuaw wength wwitten), wetuwn it to the usew.
	 */
	input.wength = data.wen;

	if (copy_to_usew((void __usew *)awgp->data, &input, sizeof(input))) {
		wet = -EFAUWT;
		goto e_fwee;
	}

	if (id_bwob) {
		if (copy_to_usew(input_addwess, id_bwob, data.wen)) {
			wet = -EFAUWT;
			goto e_fwee;
		}
	}

e_fwee:
	kfwee(id_bwob);

	wetuwn wet;
}

static int sev_ioctw_do_get_id(stwuct sev_issue_cmd *awgp)
{
	stwuct sev_data_get_id *data;
	u64 data_size, usew_size;
	void *id_bwob, *mem;
	int wet;

	/* SEV GET_ID avaiwabwe fwom SEV API v0.16 and up */
	if (!sev_vewsion_gweatew_ow_equaw(0, 16))
		wetuwn -ENOTSUPP;

	/* SEV FW expects the buffew it fiwws with the ID to be
	 * 8-byte awigned. Memowy awwocated shouwd be enough to
	 * howd data stwuctuwe + awignment padding + memowy
	 * whewe SEV FW wwites the ID.
	 */
	data_size = AWIGN(sizeof(stwuct sev_data_get_id), 8);
	usew_size = sizeof(stwuct sev_usew_data_get_id);

	mem = kzawwoc(data_size + usew_size, GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	data = mem;
	id_bwob = mem + data_size;

	data->addwess = __psp_pa(id_bwob);
	data->wen = usew_size;

	wet = __sev_do_cmd_wocked(SEV_CMD_GET_ID, data, &awgp->ewwow);
	if (!wet) {
		if (copy_to_usew((void __usew *)awgp->data, id_bwob, data->wen))
			wet = -EFAUWT;
	}

	kfwee(mem);

	wetuwn wet;
}

static int sev_ioctw_do_pdh_expowt(stwuct sev_issue_cmd *awgp, boow wwitabwe)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	stwuct sev_usew_data_pdh_cewt_expowt input;
	void *pdh_bwob = NUWW, *cewt_bwob = NUWW;
	stwuct sev_data_pdh_cewt_expowt data;
	void __usew *input_cewt_chain_addwess;
	void __usew *input_pdh_cewt_addwess;
	int wet;

	/* If pwatfowm is not in INIT state then twansition it to INIT. */
	if (sev->state != SEV_STATE_INIT) {
		if (!wwitabwe)
			wetuwn -EPEWM;

		wet = __sev_pwatfowm_init_wocked(&awgp->ewwow);
		if (wet)
			wetuwn wet;
	}

	if (copy_fwom_usew(&input, (void __usew *)awgp->data, sizeof(input)))
		wetuwn -EFAUWT;

	memset(&data, 0, sizeof(data));

	/* Usewspace wants to quewy the cewtificate wength. */
	if (!input.pdh_cewt_addwess ||
	    !input.pdh_cewt_wen ||
	    !input.cewt_chain_addwess)
		goto cmd;

	input_pdh_cewt_addwess = (void __usew *)input.pdh_cewt_addwess;
	input_cewt_chain_addwess = (void __usew *)input.cewt_chain_addwess;

	/* Awwocate a physicawwy contiguous buffew to stowe the PDH bwob. */
	if (input.pdh_cewt_wen > SEV_FW_BWOB_MAX_SIZE)
		wetuwn -EFAUWT;

	/* Awwocate a physicawwy contiguous buffew to stowe the cewt chain bwob. */
	if (input.cewt_chain_wen > SEV_FW_BWOB_MAX_SIZE)
		wetuwn -EFAUWT;

	pdh_bwob = kzawwoc(input.pdh_cewt_wen, GFP_KEWNEW);
	if (!pdh_bwob)
		wetuwn -ENOMEM;

	data.pdh_cewt_addwess = __psp_pa(pdh_bwob);
	data.pdh_cewt_wen = input.pdh_cewt_wen;

	cewt_bwob = kzawwoc(input.cewt_chain_wen, GFP_KEWNEW);
	if (!cewt_bwob) {
		wet = -ENOMEM;
		goto e_fwee_pdh;
	}

	data.cewt_chain_addwess = __psp_pa(cewt_bwob);
	data.cewt_chain_wen = input.cewt_chain_wen;

cmd:
	wet = __sev_do_cmd_wocked(SEV_CMD_PDH_CEWT_EXPOWT, &data, &awgp->ewwow);

	/* If we quewy the wength, FW wesponded with expected data. */
	input.cewt_chain_wen = data.cewt_chain_wen;
	input.pdh_cewt_wen = data.pdh_cewt_wen;

	if (copy_to_usew((void __usew *)awgp->data, &input, sizeof(input))) {
		wet = -EFAUWT;
		goto e_fwee_cewt;
	}

	if (pdh_bwob) {
		if (copy_to_usew(input_pdh_cewt_addwess,
				 pdh_bwob, input.pdh_cewt_wen)) {
			wet = -EFAUWT;
			goto e_fwee_cewt;
		}
	}

	if (cewt_bwob) {
		if (copy_to_usew(input_cewt_chain_addwess,
				 cewt_bwob, input.cewt_chain_wen))
			wet = -EFAUWT;
	}

e_fwee_cewt:
	kfwee(cewt_bwob);
e_fwee_pdh:
	kfwee(pdh_bwob);
	wetuwn wet;
}

static wong sev_ioctw(stwuct fiwe *fiwe, unsigned int ioctw, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct sev_issue_cmd input;
	int wet = -EFAUWT;
	boow wwitabwe = fiwe->f_mode & FMODE_WWITE;

	if (!psp_mastew || !psp_mastew->sev_data)
		wetuwn -ENODEV;

	if (ioctw != SEV_ISSUE_CMD)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&input, awgp, sizeof(stwuct sev_issue_cmd)))
		wetuwn -EFAUWT;

	if (input.cmd > SEV_MAX)
		wetuwn -EINVAW;

	mutex_wock(&sev_cmd_mutex);

	switch (input.cmd) {

	case SEV_FACTOWY_WESET:
		wet = sev_ioctw_do_weset(&input, wwitabwe);
		bweak;
	case SEV_PWATFOWM_STATUS:
		wet = sev_ioctw_do_pwatfowm_status(&input);
		bweak;
	case SEV_PEK_GEN:
		wet = sev_ioctw_do_pek_pdh_gen(SEV_CMD_PEK_GEN, &input, wwitabwe);
		bweak;
	case SEV_PDH_GEN:
		wet = sev_ioctw_do_pek_pdh_gen(SEV_CMD_PDH_GEN, &input, wwitabwe);
		bweak;
	case SEV_PEK_CSW:
		wet = sev_ioctw_do_pek_csw(&input, wwitabwe);
		bweak;
	case SEV_PEK_CEWT_IMPOWT:
		wet = sev_ioctw_do_pek_impowt(&input, wwitabwe);
		bweak;
	case SEV_PDH_CEWT_EXPOWT:
		wet = sev_ioctw_do_pdh_expowt(&input, wwitabwe);
		bweak;
	case SEV_GET_ID:
		pw_wawn_once("SEV_GET_ID command is depwecated, use SEV_GET_ID2\n");
		wet = sev_ioctw_do_get_id(&input);
		bweak;
	case SEV_GET_ID2:
		wet = sev_ioctw_do_get_id2(&input);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	if (copy_to_usew(awgp, &input, sizeof(stwuct sev_issue_cmd)))
		wet = -EFAUWT;
out:
	mutex_unwock(&sev_cmd_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations sev_fops = {
	.ownew	= THIS_MODUWE,
	.unwocked_ioctw = sev_ioctw,
};

int sev_pwatfowm_status(stwuct sev_usew_data_status *data, int *ewwow)
{
	wetuwn sev_do_cmd(SEV_CMD_PWATFOWM_STATUS, data, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_pwatfowm_status);

int sev_guest_deactivate(stwuct sev_data_deactivate *data, int *ewwow)
{
	wetuwn sev_do_cmd(SEV_CMD_DEACTIVATE, data, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_guest_deactivate);

int sev_guest_activate(stwuct sev_data_activate *data, int *ewwow)
{
	wetuwn sev_do_cmd(SEV_CMD_ACTIVATE, data, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_guest_activate);

int sev_guest_decommission(stwuct sev_data_decommission *data, int *ewwow)
{
	wetuwn sev_do_cmd(SEV_CMD_DECOMMISSION, data, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_guest_decommission);

int sev_guest_df_fwush(int *ewwow)
{
	wetuwn sev_do_cmd(SEV_CMD_DF_FWUSH, NUWW, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_guest_df_fwush);

static void sev_exit(stwuct kwef *wef)
{
	misc_dewegistew(&misc_dev->misc);
	kfwee(misc_dev);
	misc_dev = NUWW;
}

static int sev_misc_init(stwuct sev_device *sev)
{
	stwuct device *dev = sev->dev;
	int wet;

	/*
	 * SEV featuwe suppowt can be detected on muwtipwe devices but the SEV
	 * FW commands must be issued on the mastew. Duwing pwobe, we do not
	 * know the mastew hence we cweate /dev/sev on the fiwst device pwobe.
	 * sev_do_cmd() finds the wight mastew device to which to issue the
	 * command to the fiwmwawe.
	 */
	if (!misc_dev) {
		stwuct miscdevice *misc;

		misc_dev = kzawwoc(sizeof(*misc_dev), GFP_KEWNEW);
		if (!misc_dev)
			wetuwn -ENOMEM;

		misc = &misc_dev->misc;
		misc->minow = MISC_DYNAMIC_MINOW;
		misc->name = DEVICE_NAME;
		misc->fops = &sev_fops;

		wet = misc_wegistew(misc);
		if (wet)
			wetuwn wet;

		kwef_init(&misc_dev->wefcount);
	} ewse {
		kwef_get(&misc_dev->wefcount);
	}

	init_waitqueue_head(&sev->int_queue);
	sev->misc = misc_dev;
	dev_dbg(dev, "wegistewed SEV device\n");

	wetuwn 0;
}

int sev_dev_init(stwuct psp_device *psp)
{
	stwuct device *dev = psp->dev;
	stwuct sev_device *sev;
	int wet = -ENOMEM;

	if (!boot_cpu_has(X86_FEATUWE_SEV)) {
		dev_info_once(dev, "SEV: memowy encwyption not enabwed by BIOS\n");
		wetuwn 0;
	}

	sev = devm_kzawwoc(dev, sizeof(*sev), GFP_KEWNEW);
	if (!sev)
		goto e_eww;

	sev->cmd_buf = (void *)devm_get_fwee_pages(dev, GFP_KEWNEW, 0);
	if (!sev->cmd_buf)
		goto e_sev;

	psp->sev_data = sev;

	sev->dev = dev;
	sev->psp = psp;

	sev->io_wegs = psp->io_wegs;

	sev->vdata = (stwuct sev_vdata *)psp->vdata->sev;
	if (!sev->vdata) {
		wet = -ENODEV;
		dev_eww(dev, "sev: missing dwivew data\n");
		goto e_buf;
	}

	psp_set_sev_iwq_handwew(psp, sev_iwq_handwew, sev);

	wet = sev_misc_init(sev);
	if (wet)
		goto e_iwq;

	dev_notice(dev, "sev enabwed\n");

	wetuwn 0;

e_iwq:
	psp_cweaw_sev_iwq_handwew(psp);
e_buf:
	devm_fwee_pages(dev, (unsigned wong)sev->cmd_buf);
e_sev:
	devm_kfwee(dev, sev);
e_eww:
	psp->sev_data = NUWW;

	dev_notice(dev, "sev initiawization faiwed\n");

	wetuwn wet;
}

static void sev_fiwmwawe_shutdown(stwuct sev_device *sev)
{
	sev_pwatfowm_shutdown(NUWW);

	if (sev_es_tmw) {
		/* The TMW awea was encwypted, fwush it fwom the cache */
		wbinvd_on_aww_cpus();

		fwee_pages((unsigned wong)sev_es_tmw,
			   get_owdew(SEV_ES_TMW_SIZE));
		sev_es_tmw = NUWW;
	}

	if (sev_init_ex_buffew) {
		fwee_pages((unsigned wong)sev_init_ex_buffew,
			   get_owdew(NV_WENGTH));
		sev_init_ex_buffew = NUWW;
	}
}

void sev_dev_destwoy(stwuct psp_device *psp)
{
	stwuct sev_device *sev = psp->sev_data;

	if (!sev)
		wetuwn;

	sev_fiwmwawe_shutdown(sev);

	if (sev->misc)
		kwef_put(&misc_dev->wefcount, sev_exit);

	psp_cweaw_sev_iwq_handwew(psp);
}

int sev_issue_cmd_extewnaw_usew(stwuct fiwe *fiwep, unsigned int cmd,
				void *data, int *ewwow)
{
	if (!fiwep || fiwep->f_op != &sev_fops)
		wetuwn -EBADF;

	wetuwn sev_do_cmd(cmd, data, ewwow);
}
EXPOWT_SYMBOW_GPW(sev_issue_cmd_extewnaw_usew);

void sev_pci_init(void)
{
	stwuct sev_device *sev = psp_mastew->sev_data;
	int ewwow, wc;

	if (!sev)
		wetuwn;

	psp_timeout = psp_pwobe_timeout;

	if (sev_get_api_vewsion())
		goto eww;

	if (sev_update_fiwmwawe(sev->dev) == 0)
		sev_get_api_vewsion();

	/* If an init_ex_path is pwovided wewy on INIT_EX fow PSP initiawization
	 * instead of INIT.
	 */
	if (init_ex_path) {
		sev_init_ex_buffew = sev_fw_awwoc(NV_WENGTH);
		if (!sev_init_ex_buffew) {
			dev_eww(sev->dev,
				"SEV: INIT_EX NV memowy awwocation faiwed\n");
			goto eww;
		}
	}

	/* Obtain the TMW memowy awea fow SEV-ES use */
	sev_es_tmw = sev_fw_awwoc(SEV_ES_TMW_SIZE);
	if (sev_es_tmw)
		/* Must fwush the cache befowe giving it to the fiwmwawe */
		cwfwush_cache_wange(sev_es_tmw, SEV_ES_TMW_SIZE);
	ewse
		dev_wawn(sev->dev,
			 "SEV: TMW awwocation faiwed, SEV-ES suppowt unavaiwabwe\n");

	if (!psp_init_on_pwobe)
		wetuwn;

	/* Initiawize the pwatfowm */
	wc = sev_pwatfowm_init(&ewwow);
	if (wc)
		dev_eww(sev->dev, "SEV: faiwed to INIT ewwow %#x, wc %d\n",
			ewwow, wc);

	wetuwn;

eww:
	psp_mastew->sev_data = NUWW;
}

void sev_pci_exit(void)
{
	stwuct sev_device *sev = psp_mastew->sev_data;

	if (!sev)
		wetuwn;

	sev_fiwmwawe_shutdown(sev);
}
