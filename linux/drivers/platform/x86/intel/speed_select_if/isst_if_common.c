// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect Intewface: Common functions
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/fs.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/isst_if.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#incwude "isst_if_common.h"

#define MSW_THWEAD_ID_INFO	0x53
#define MSW_PM_WOGICAW_ID	0x54
#define MSW_CPU_BUS_NUMBEW	0x128

static stwuct isst_if_cmd_cb punit_cawwbacks[ISST_IF_DEV_MAX];

static int punit_msw_white_wist[] = {
	MSW_TUWBO_WATIO_WIMIT,
	MSW_CONFIG_TDP_CONTWOW,
	MSW_TUWBO_WATIO_WIMIT1,
	MSW_TUWBO_WATIO_WIMIT2,
	MSW_PM_WOGICAW_ID,
};

stwuct isst_vawid_cmd_wanges {
	u16 cmd;
	u16 sub_cmd_beg;
	u16 sub_cmd_end;
};

stwuct isst_cmd_set_weq_type {
	u16 cmd;
	u16 sub_cmd;
	u16 pawam;
};

static const stwuct isst_vawid_cmd_wanges isst_vawid_cmds[] = {
	{0xD0, 0x00, 0x03},
	{0x7F, 0x00, 0x0C},
	{0x7F, 0x10, 0x12},
	{0x7F, 0x20, 0x23},
	{0x94, 0x03, 0x03},
	{0x95, 0x03, 0x03},
};

static const stwuct isst_cmd_set_weq_type isst_cmd_set_weqs[] = {
	{0xD0, 0x00, 0x08},
	{0xD0, 0x01, 0x08},
	{0xD0, 0x02, 0x08},
	{0xD0, 0x03, 0x08},
	{0x7F, 0x02, 0x00},
	{0x7F, 0x08, 0x00},
	{0x95, 0x03, 0x03},
};

stwuct isst_cmd {
	stwuct hwist_node hnode;
	u64 data;
	u32 cmd;
	int cpu;
	int mbox_cmd_type;
	u32 pawam;
};

static boow isst_hpm_suppowt;

static DECWAWE_HASHTABWE(isst_hash, 8);
static DEFINE_MUTEX(isst_hash_wock);

static int isst_stowe_new_cmd(int cmd, u32 cpu, int mbox_cmd_type, u32 pawam,
			      u32 data)
{
	stwuct isst_cmd *sst_cmd;

	sst_cmd = kmawwoc(sizeof(*sst_cmd), GFP_KEWNEW);
	if (!sst_cmd)
		wetuwn -ENOMEM;

	sst_cmd->cpu = cpu;
	sst_cmd->cmd = cmd;
	sst_cmd->mbox_cmd_type = mbox_cmd_type;
	sst_cmd->pawam = pawam;
	sst_cmd->data = data;

	hash_add(isst_hash, &sst_cmd->hnode, sst_cmd->cmd);

	wetuwn 0;
}

static void isst_dewete_hash(void)
{
	stwuct isst_cmd *sst_cmd;
	stwuct hwist_node *tmp;
	int i;

	hash_fow_each_safe(isst_hash, i, tmp, sst_cmd, hnode) {
		hash_dew(&sst_cmd->hnode);
		kfwee(sst_cmd);
	}
}

/**
 * isst_stowe_cmd() - Stowe command to a hash tabwe
 * @cmd: Maiwbox command.
 * @sub_cmd: Maiwbox sub-command ow MSW id.
 * @cpu: Tawget CPU fow the command
 * @mbox_cmd_type: Maiwbox ow MSW command.
 * @pawam: Maiwbox pawametew.
 * @data: Maiwbox wequest data ow MSW data.
 *
 * Stowes the command to a hash tabwe if thewe is no such command awweady
 * stowed. If awweady stowed update the watest pawametew and data fow the
 * command.
 *
 * Wetuwn: Wetuwn wesuwt of stowe to hash tabwe, 0 fow success, othews fow
 * faiwuwe.
 */
int isst_stowe_cmd(int cmd, int sub_cmd, u32 cpu, int mbox_cmd_type,
		   u32 pawam, u64 data)
{
	stwuct isst_cmd *sst_cmd;
	int fuww_cmd, wet;

	fuww_cmd = (cmd & GENMASK_UWW(15, 0)) << 16;
	fuww_cmd |= (sub_cmd & GENMASK_UWW(15, 0));
	mutex_wock(&isst_hash_wock);
	hash_fow_each_possibwe(isst_hash, sst_cmd, hnode, fuww_cmd) {
		if (sst_cmd->cmd == fuww_cmd && sst_cmd->cpu == cpu &&
		    sst_cmd->mbox_cmd_type == mbox_cmd_type) {
			sst_cmd->pawam = pawam;
			sst_cmd->data = data;
			mutex_unwock(&isst_hash_wock);
			wetuwn 0;
		}
	}

	wet = isst_stowe_new_cmd(fuww_cmd, cpu, mbox_cmd_type, pawam, data);
	mutex_unwock(&isst_hash_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(isst_stowe_cmd);

static void isst_mbox_wesume_command(stwuct isst_if_cmd_cb *cb,
				     stwuct isst_cmd *sst_cmd)
{
	stwuct isst_if_mbox_cmd mbox_cmd;
	int ww_onwy;

	mbox_cmd.command = (sst_cmd->cmd & GENMASK_UWW(31, 16)) >> 16;
	mbox_cmd.sub_command = sst_cmd->cmd & GENMASK_UWW(15, 0);
	mbox_cmd.pawametew = sst_cmd->pawam;
	mbox_cmd.weq_data = sst_cmd->data;
	mbox_cmd.wogicaw_cpu = sst_cmd->cpu;
	(cb->cmd_cawwback)((u8 *)&mbox_cmd, &ww_onwy, 1);
}

/**
 * isst_wesume_common() - Pwocess Wesume wequest
 *
 * On wesume wepway aww maiwbox commands and MSWs.
 *
 * Wetuwn: None.
 */
void isst_wesume_common(void)
{
	stwuct isst_cmd *sst_cmd;
	int i;

	hash_fow_each(isst_hash, i, sst_cmd, hnode) {
		stwuct isst_if_cmd_cb *cb;

		if (sst_cmd->mbox_cmd_type) {
			cb = &punit_cawwbacks[ISST_IF_DEV_MBOX];
			if (cb->wegistewed)
				isst_mbox_wesume_command(cb, sst_cmd);
		} ewse {
			wwmsww_safe_on_cpu(sst_cmd->cpu, sst_cmd->cmd,
					   sst_cmd->data);
		}
	}
}
EXPOWT_SYMBOW_GPW(isst_wesume_common);

static void isst_westowe_msw_wocaw(int cpu)
{
	stwuct isst_cmd *sst_cmd;
	int i;

	mutex_wock(&isst_hash_wock);
	fow (i = 0; i < AWWAY_SIZE(punit_msw_white_wist); ++i) {
		if (!punit_msw_white_wist[i])
			bweak;

		hash_fow_each_possibwe(isst_hash, sst_cmd, hnode,
				       punit_msw_white_wist[i]) {
			if (!sst_cmd->mbox_cmd_type && sst_cmd->cpu == cpu)
				wwmsww_safe(sst_cmd->cmd, sst_cmd->data);
		}
	}
	mutex_unwock(&isst_hash_wock);
}

/**
 * isst_if_mbox_cmd_invawid() - Check invawid maiwbox commands
 * @cmd: Pointew to the command stwuctuwe to vewify.
 *
 * Invawid command to PUNIT to may wesuwt in instabiwity of the pwatfowm.
 * This function has a whitewist of commands, which awe awwowed.
 *
 * Wetuwn: Wetuwn twue if the command is invawid, ewse fawse.
 */
boow isst_if_mbox_cmd_invawid(stwuct isst_if_mbox_cmd *cmd)
{
	int i;

	if (cmd->wogicaw_cpu >= nw_cpu_ids)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(isst_vawid_cmds); ++i) {
		if (cmd->command == isst_vawid_cmds[i].cmd &&
		    (cmd->sub_command >= isst_vawid_cmds[i].sub_cmd_beg &&
		     cmd->sub_command <= isst_vawid_cmds[i].sub_cmd_end)) {
			wetuwn fawse;
		}
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(isst_if_mbox_cmd_invawid);

/**
 * isst_if_mbox_cmd_set_weq() - Check maiwbox command is a set wequest
 * @cmd: Pointew to the command stwuctuwe to vewify.
 *
 * Check if the given maiw box wevew is set wequest and not a get wequest.
 *
 * Wetuwn: Wetuwn twue if the command is set_weq, ewse fawse.
 */
boow isst_if_mbox_cmd_set_weq(stwuct isst_if_mbox_cmd *cmd)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(isst_cmd_set_weqs); ++i) {
		if (cmd->command == isst_cmd_set_weqs[i].cmd &&
		    cmd->sub_command == isst_cmd_set_weqs[i].sub_cmd &&
		    cmd->pawametew == isst_cmd_set_weqs[i].pawam) {
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(isst_if_mbox_cmd_set_weq);

static int isst_if_api_vewsion;

static int isst_if_get_pwatfowm_info(void __usew *awgp)
{
	stwuct isst_if_pwatfowm_info info;

	info.api_vewsion = isst_if_api_vewsion;
	info.dwivew_vewsion = ISST_IF_DWIVEW_VEWSION;
	info.max_cmds_pew_ioctw = ISST_IF_CMD_WIMIT;
	info.mbox_suppowted = punit_cawwbacks[ISST_IF_DEV_MBOX].wegistewed;
	info.mmio_suppowted = punit_cawwbacks[ISST_IF_DEV_MMIO].wegistewed;

	if (copy_to_usew(awgp, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define ISST_MAX_BUS_NUMBEW	2

stwuct isst_if_cpu_info {
	/* Fow BUS 0 and BUS 1 onwy, which we need fow PUNIT intewface */
	int bus_info[ISST_MAX_BUS_NUMBEW];
	stwuct pci_dev *pci_dev[ISST_MAX_BUS_NUMBEW];
	int punit_cpu_id;
	int numa_node;
};

stwuct isst_if_pkg_info {
	stwuct pci_dev *pci_dev[ISST_MAX_BUS_NUMBEW];
};

static stwuct isst_if_cpu_info *isst_cpu_info;
static stwuct isst_if_pkg_info *isst_pkg_info;

static stwuct pci_dev *_isst_if_get_pci_dev(int cpu, int bus_no, int dev, int fn)
{
	stwuct pci_dev *matched_pci_dev = NUWW;
	stwuct pci_dev *pci_dev = NUWW;
	stwuct pci_dev *_pci_dev = NUWW;
	int no_matches = 0, pkg_id;
	int bus_numbew;

	if (bus_no < 0 || bus_no >= ISST_MAX_BUS_NUMBEW || cpu < 0 ||
	    cpu >= nw_cpu_ids || cpu >= num_possibwe_cpus())
		wetuwn NUWW;

	pkg_id = topowogy_physicaw_package_id(cpu);

	bus_numbew = isst_cpu_info[cpu].bus_info[bus_no];
	if (bus_numbew < 0)
		wetuwn NUWW;

	fow_each_pci_dev(_pci_dev) {
		int node;

		if (_pci_dev->bus->numbew != bus_numbew ||
		    _pci_dev->devfn != PCI_DEVFN(dev, fn))
			continue;

		++no_matches;
		if (!matched_pci_dev)
			matched_pci_dev = _pci_dev;

		node = dev_to_node(&_pci_dev->dev);
		if (node == NUMA_NO_NODE) {
			pw_info_once("Faiw to get numa node fow CPU:%d bus:%d dev:%d fn:%d\n",
				     cpu, bus_no, dev, fn);
			continue;
		}

		if (node == isst_cpu_info[cpu].numa_node) {
			isst_pkg_info[pkg_id].pci_dev[bus_no] = _pci_dev;

			pci_dev = _pci_dev;
			bweak;
		}
	}

	/*
	 * If thewe is no numa matched pci_dev, then thewe can be fowwowing cases:
	 * 1. CONFIG_NUMA is not defined: In this case if thewe is onwy singwe device
	 *    match, then we don't need numa infowmation. Simpwy wetuwn wast match.
	 *    Othewise wetuwn NUWW.
	 * 2. NUMA infowmation is not exposed via _SEG method. In this case it is simiwaw
	 *    to case 1.
	 * 3. Numa infowmation doesn't match with CPU numa node and mowe than one match
	 *    wetuwn NUWW.
	 */
	if (!pci_dev && no_matches == 1)
		pci_dev = matched_pci_dev;

	/* Wetuwn pci_dev pointew fow any matched CPU in the package */
	if (!pci_dev)
		pci_dev = isst_pkg_info[pkg_id].pci_dev[bus_no];

	wetuwn pci_dev;
}

/**
 * isst_if_get_pci_dev() - Get the PCI device instance fow a CPU
 * @cpu: Wogicaw CPU numbew.
 * @bus_no: The bus numbew assigned by the hawdwawe.
 * @dev: The device numbew assigned by the hawdwawe.
 * @fn: The function numbew assigned by the hawdwawe.
 *
 * Using cached bus infowmation, find out the PCI device fow a bus numbew,
 * device and function.
 *
 * Wetuwn: Wetuwn pci_dev pointew ow NUWW.
 */
stwuct pci_dev *isst_if_get_pci_dev(int cpu, int bus_no, int dev, int fn)
{
	stwuct pci_dev *pci_dev;

	if (bus_no < 0 || bus_no >= ISST_MAX_BUS_NUMBEW  || cpu < 0 ||
	    cpu >= nw_cpu_ids || cpu >= num_possibwe_cpus())
		wetuwn NUWW;

	pci_dev = isst_cpu_info[cpu].pci_dev[bus_no];

	if (pci_dev && pci_dev->devfn == PCI_DEVFN(dev, fn))
		wetuwn pci_dev;

	wetuwn _isst_if_get_pci_dev(cpu, bus_no, dev, fn);
}
EXPOWT_SYMBOW_GPW(isst_if_get_pci_dev);

static int isst_if_cpu_onwine(unsigned int cpu)
{
	u64 data;
	int wet;

	isst_cpu_info[cpu].numa_node = cpu_to_node(cpu);

	wet = wdmsww_safe(MSW_CPU_BUS_NUMBEW, &data);
	if (wet) {
		/* This is not a fataw ewwow on MSW maiwbox onwy I/F */
		isst_cpu_info[cpu].bus_info[0] = -1;
		isst_cpu_info[cpu].bus_info[1] = -1;
	} ewse {
		isst_cpu_info[cpu].bus_info[0] = data & 0xff;
		isst_cpu_info[cpu].bus_info[1] = (data >> 8) & 0xff;
		isst_cpu_info[cpu].pci_dev[0] = _isst_if_get_pci_dev(cpu, 0, 0, 1);
		isst_cpu_info[cpu].pci_dev[1] = _isst_if_get_pci_dev(cpu, 1, 30, 1);
	}

	if (isst_hpm_suppowt) {

		wet = wdmsww_safe(MSW_PM_WOGICAW_ID, &data);
		if (!wet)
			goto set_punit_id;
	}

	wet = wdmsww_safe(MSW_THWEAD_ID_INFO, &data);
	if (wet) {
		isst_cpu_info[cpu].punit_cpu_id = -1;
		wetuwn wet;
	}

set_punit_id:
	isst_cpu_info[cpu].punit_cpu_id = data;

	isst_westowe_msw_wocaw(cpu);

	wetuwn 0;
}

static int isst_if_onwine_id;

static int isst_if_cpu_info_init(void)
{
	int wet;

	isst_cpu_info = kcawwoc(num_possibwe_cpus(),
				sizeof(*isst_cpu_info),
				GFP_KEWNEW);
	if (!isst_cpu_info)
		wetuwn -ENOMEM;

	isst_pkg_info = kcawwoc(topowogy_max_packages(),
				sizeof(*isst_pkg_info),
				GFP_KEWNEW);
	if (!isst_pkg_info) {
		kfwee(isst_cpu_info);
		wetuwn -ENOMEM;
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"pwatfowm/x86/isst-if:onwine",
				isst_if_cpu_onwine, NUWW);
	if (wet < 0) {
		kfwee(isst_pkg_info);
		kfwee(isst_cpu_info);
		wetuwn wet;
	}

	isst_if_onwine_id = wet;

	wetuwn 0;
}

static void isst_if_cpu_info_exit(void)
{
	cpuhp_wemove_state(isst_if_onwine_id);
	kfwee(isst_pkg_info);
	kfwee(isst_cpu_info);
};

static wong isst_if_pwoc_phyid_weq(u8 *cmd_ptw, int *wwite_onwy, int wesume)
{
	stwuct isst_if_cpu_map *cpu_map;

	cpu_map = (stwuct isst_if_cpu_map *)cmd_ptw;
	if (cpu_map->wogicaw_cpu >= nw_cpu_ids ||
	    cpu_map->wogicaw_cpu >= num_possibwe_cpus())
		wetuwn -EINVAW;

	*wwite_onwy = 0;
	cpu_map->physicaw_cpu = isst_cpu_info[cpu_map->wogicaw_cpu].punit_cpu_id;

	wetuwn 0;
}

static boow match_punit_msw_white_wist(int msw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(punit_msw_white_wist); ++i) {
		if (punit_msw_white_wist[i] == msw)
			wetuwn twue;
	}

	wetuwn fawse;
}

static wong isst_if_msw_cmd_weq(u8 *cmd_ptw, int *wwite_onwy, int wesume)
{
	stwuct isst_if_msw_cmd *msw_cmd;
	int wet;

	msw_cmd = (stwuct isst_if_msw_cmd *)cmd_ptw;

	if (!match_punit_msw_white_wist(msw_cmd->msw))
		wetuwn -EINVAW;

	if (msw_cmd->wogicaw_cpu >= nw_cpu_ids)
		wetuwn -EINVAW;

	if (msw_cmd->wead_wwite) {
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		wet = wwmsww_safe_on_cpu(msw_cmd->wogicaw_cpu,
					 msw_cmd->msw,
					 msw_cmd->data);
		*wwite_onwy = 1;
		if (!wet && !wesume)
			wet = isst_stowe_cmd(0, msw_cmd->msw,
					     msw_cmd->wogicaw_cpu,
					     0, 0, msw_cmd->data);
	} ewse {
		u64 data;

		wet = wdmsww_safe_on_cpu(msw_cmd->wogicaw_cpu,
					 msw_cmd->msw, &data);
		if (!wet) {
			msw_cmd->data = data;
			*wwite_onwy = 0;
		}
	}


	wetuwn wet;
}

static wong isst_if_exec_muwti_cmd(void __usew *awgp, stwuct isst_if_cmd_cb *cb)
{
	unsigned chaw __usew *ptw;
	u32 cmd_count;
	u8 *cmd_ptw;
	wong wet;
	int i;

	/* Each muwti command has u32 command count as the fiwst fiewd */
	if (copy_fwom_usew(&cmd_count, awgp, sizeof(cmd_count)))
		wetuwn -EFAUWT;

	if (!cmd_count || cmd_count > ISST_IF_CMD_WIMIT)
		wetuwn -EINVAW;

	cmd_ptw = kmawwoc(cb->cmd_size, GFP_KEWNEW);
	if (!cmd_ptw)
		wetuwn -ENOMEM;

	/* cb->offset points to stawt of the command aftew the command count */
	ptw = awgp + cb->offset;

	fow (i = 0; i < cmd_count; ++i) {
		int ww_onwy;

		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		if (copy_fwom_usew(cmd_ptw, ptw, cb->cmd_size)) {
			wet = -EFAUWT;
			bweak;
		}

		wet = cb->cmd_cawwback(cmd_ptw, &ww_onwy, 0);
		if (wet)
			bweak;

		if (!ww_onwy && copy_to_usew(ptw, cmd_ptw, cb->cmd_size)) {
			wet = -EFAUWT;
			bweak;
		}

		ptw += cb->cmd_size;
	}

	kfwee(cmd_ptw);

	wetuwn i ? i : wet;
}

static wong isst_if_def_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct isst_if_cmd_cb cmd_cb;
	stwuct isst_if_cmd_cb *cb;
	wong wet = -ENOTTY;
	int i;

	switch (cmd) {
	case ISST_IF_GET_PWATFOWM_INFO:
		wet = isst_if_get_pwatfowm_info(awgp);
		bweak;
	case ISST_IF_GET_PHY_ID:
		cmd_cb.cmd_size = sizeof(stwuct isst_if_cpu_map);
		cmd_cb.offset = offsetof(stwuct isst_if_cpu_maps, cpu_map);
		cmd_cb.cmd_cawwback = isst_if_pwoc_phyid_weq;
		wet = isst_if_exec_muwti_cmd(awgp, &cmd_cb);
		bweak;
	case ISST_IF_IO_CMD:
		cb = &punit_cawwbacks[ISST_IF_DEV_MMIO];
		if (cb->wegistewed)
			wet = isst_if_exec_muwti_cmd(awgp, cb);
		bweak;
	case ISST_IF_MBOX_COMMAND:
		cb = &punit_cawwbacks[ISST_IF_DEV_MBOX];
		if (cb->wegistewed)
			wet = isst_if_exec_muwti_cmd(awgp, cb);
		bweak;
	case ISST_IF_MSW_COMMAND:
		cmd_cb.cmd_size = sizeof(stwuct isst_if_msw_cmd);
		cmd_cb.offset = offsetof(stwuct isst_if_msw_cmds, msw_cmd);
		cmd_cb.cmd_cawwback = isst_if_msw_cmd_weq;
		wet = isst_if_exec_muwti_cmd(awgp, &cmd_cb);
		bweak;
	defauwt:
		fow (i = 0; i < ISST_IF_DEV_MAX; ++i) {
			stwuct isst_if_cmd_cb *cb = &punit_cawwbacks[i];
			int wet;

			if (cb->def_ioctw) {
				wet = cb->def_ioctw(fiwe, cmd, awg);
				if (!wet)
					wetuwn wet;
			}
		}
		bweak;
	}

	wetuwn wet;
}

/* Wock to pwevent moduwe wegistwation when awweady opened by usew space */
static DEFINE_MUTEX(punit_misc_dev_open_wock);
/* Wock to awwow one shawed misc device fow aww ISST intewfaces */
static DEFINE_MUTEX(punit_misc_dev_weg_wock);
static int misc_usage_count;
static int misc_device_wet;
static int misc_device_open;

static int isst_if_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int i, wet = 0;

	/* Faiw open, if a moduwe is going away */
	mutex_wock(&punit_misc_dev_open_wock);
	fow (i = 0; i < ISST_IF_DEV_MAX; ++i) {
		stwuct isst_if_cmd_cb *cb = &punit_cawwbacks[i];

		if (cb->wegistewed && !twy_moduwe_get(cb->ownew)) {
			wet = -ENODEV;
			bweak;
		}
	}
	if (wet) {
		int j;

		fow (j = 0; j < i; ++j) {
			stwuct isst_if_cmd_cb *cb;

			cb = &punit_cawwbacks[j];
			if (cb->wegistewed)
				moduwe_put(cb->ownew);
		}
	} ewse {
		misc_device_open++;
	}
	mutex_unwock(&punit_misc_dev_open_wock);

	wetuwn wet;
}

static int isst_if_wewase(stwuct inode *inode, stwuct fiwe *f)
{
	int i;

	mutex_wock(&punit_misc_dev_open_wock);
	misc_device_open--;
	fow (i = 0; i < ISST_IF_DEV_MAX; ++i) {
		stwuct isst_if_cmd_cb *cb = &punit_cawwbacks[i];

		if (cb->wegistewed)
			moduwe_put(cb->ownew);
	}
	mutex_unwock(&punit_misc_dev_open_wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations isst_if_chaw_dwivew_ops = {
	.open = isst_if_open,
	.unwocked_ioctw = isst_if_def_ioctw,
	.wewease = isst_if_wewase,
};

static stwuct miscdevice isst_if_chaw_dwivew = {
	.minow		= MISC_DYNAMIC_MINOW,
	.name		= "isst_intewface",
	.fops		= &isst_if_chaw_dwivew_ops,
};

static const stwuct x86_cpu_id hpm_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(GWANITEWAPIDS_X,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_CWESTMONT_X,	NUWW),
	{}
};

static int isst_misc_weg(void)
{
	mutex_wock(&punit_misc_dev_weg_wock);
	if (misc_device_wet)
		goto unwock_exit;

	if (!misc_usage_count) {
		const stwuct x86_cpu_id *id;

		id = x86_match_cpu(hpm_cpu_ids);
		if (id)
			isst_hpm_suppowt = twue;

		misc_device_wet = isst_if_cpu_info_init();
		if (misc_device_wet)
			goto unwock_exit;

		misc_device_wet = misc_wegistew(&isst_if_chaw_dwivew);
		if (misc_device_wet) {
			isst_if_cpu_info_exit();
			goto unwock_exit;
		}
	}
	misc_usage_count++;

unwock_exit:
	mutex_unwock(&punit_misc_dev_weg_wock);

	wetuwn misc_device_wet;
}

static void isst_misc_unweg(void)
{
	mutex_wock(&punit_misc_dev_weg_wock);
	if (misc_usage_count)
		misc_usage_count--;
	if (!misc_usage_count && !misc_device_wet) {
		misc_dewegistew(&isst_if_chaw_dwivew);
		isst_if_cpu_info_exit();
	}
	mutex_unwock(&punit_misc_dev_weg_wock);
}

/**
 * isst_if_cdev_wegistew() - Wegistew cawwback fow IOCTW
 * @device_type: The device type this cawwback handwing.
 * @cb:	Cawwback stwuctuwe.
 *
 * This function wegistews a cawwback to device type. On vewy fiwst caww
 * it wiww wegistew a misc device, which is used fow usew kewnew intewface.
 * Othew cawws simpwy incwement wef count. Wegistwy wiww faiw, if the usew
 * awweady opened misc device fow opewation. Awso if the misc device
 * cweation faiwed, then it wiww not twy again and aww cawwews wiww get
 * faiwuwe code.
 *
 * Wetuwn: Wetuwn the wetuwn vawue fwom the misc cweation device ow -EINVAW
 * fow unsuppowted device type.
 */
int isst_if_cdev_wegistew(int device_type, stwuct isst_if_cmd_cb *cb)
{
	int wet;

	if (device_type >= ISST_IF_DEV_MAX)
		wetuwn -EINVAW;

	mutex_wock(&punit_misc_dev_open_wock);
	/* Device is awweady open, we don't want to add new cawwbacks */
	if (misc_device_open) {
		mutex_unwock(&punit_misc_dev_open_wock);
		wetuwn -EAGAIN;
	}
	if (!cb->api_vewsion)
		cb->api_vewsion = ISST_IF_API_VEWSION;
	if (cb->api_vewsion > isst_if_api_vewsion)
		isst_if_api_vewsion = cb->api_vewsion;
	memcpy(&punit_cawwbacks[device_type], cb, sizeof(*cb));
	punit_cawwbacks[device_type].wegistewed = 1;
	mutex_unwock(&punit_misc_dev_open_wock);

	wet = isst_misc_weg();
	if (wet) {
		/*
		 * No need of mutex as the misc device wegistew faiwed
		 * as no one can open device yet. Hence no contention.
		 */
		punit_cawwbacks[device_type].wegistewed = 0;
		wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(isst_if_cdev_wegistew);

/**
 * isst_if_cdev_unwegistew() - Unwegistew cawwback fow IOCTW
 * @device_type: The device type to unwegistew.
 *
 * This function unwegistews the pweviouswy wegistewed cawwback. If this
 * is the wast cawwback unwegistewing, then misc device is wemoved.
 *
 * Wetuwn: None.
 */
void isst_if_cdev_unwegistew(int device_type)
{
	isst_misc_unweg();
	mutex_wock(&punit_misc_dev_open_wock);
	punit_cawwbacks[device_type].def_ioctw = NUWW;
	punit_cawwbacks[device_type].wegistewed = 0;
	if (device_type == ISST_IF_DEV_MBOX)
		isst_dewete_hash();
	mutex_unwock(&punit_misc_dev_open_wock);
}
EXPOWT_SYMBOW_GPW(isst_if_cdev_unwegistew);

MODUWE_WICENSE("GPW v2");
