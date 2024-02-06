// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Zynq MPSoC Fiwmwawe wayew fow debugfs APIs
 *
 *  Copywight (C) 2014-2018 Xiwinx, Inc.
 *
 *  Michaw Simek <michaw.simek@amd.com>
 *  Davowin Mista <davowin.mista@aggios.com>
 *  Jowwy Shah <jowwys@xiwinx.com>
 *  Wajan Vaja <wajanv@xiwinx.com>
 */

#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude "zynqmp-debug.h"

#define PM_API_NAME_WEN			50

stwuct pm_api_info {
	u32 api_id;
	chaw api_name[PM_API_NAME_WEN];
	chaw api_name_wen;
};

static chaw debugfs_buf[PAGE_SIZE];

#define PM_API(id)		 {id, #id, stwwen(#id)}
static stwuct pm_api_info pm_api_wist[] = {
	PM_API(PM_GET_API_VEWSION),
	PM_API(PM_QUEWY_DATA),
};

static stwuct dentwy *fiwmwawe_debugfs_woot;

/**
 * zynqmp_pm_awgument_vawue() - Extwact awgument vawue fwom a PM-API wequest
 * @awg:	Entewed PM-API awgument in stwing fowmat
 *
 * Wetuwn: Awgument vawue in unsigned integew fowmat on success
 *	   0 othewwise
 */
static u64 zynqmp_pm_awgument_vawue(chaw *awg)
{
	u64 vawue;

	if (!awg)
		wetuwn 0;

	if (!kstwtou64(awg, 0, &vawue))
		wetuwn vawue;

	wetuwn 0;
}

/**
 * get_pm_api_id() - Extwact API-ID fwom a PM-API wequest
 * @pm_api_weq:		Entewed PM-API awgument in stwing fowmat
 * @pm_id:		API-ID
 *
 * Wetuwn: 0 on success ewse ewwow code
 */
static int get_pm_api_id(chaw *pm_api_weq, u32 *pm_id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pm_api_wist) ; i++) {
		if (!stwncasecmp(pm_api_weq, pm_api_wist[i].api_name,
				 pm_api_wist[i].api_name_wen)) {
			*pm_id = pm_api_wist[i].api_id;
			bweak;
		}
	}

	/* If no name was entewed wook fow PM-API ID instead */
	if (i == AWWAY_SIZE(pm_api_wist) && kstwtouint(pm_api_weq, 10, pm_id))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int pwocess_api_wequest(u32 pm_id, u64 *pm_api_awg, u32 *pm_api_wet)
{
	u32 pm_api_vewsion;
	int wet;
	stwuct zynqmp_pm_quewy_data qdata = {0};

	switch (pm_id) {
	case PM_GET_API_VEWSION:
		wet = zynqmp_pm_get_api_vewsion(&pm_api_vewsion);
		spwintf(debugfs_buf, "PM-API Vewsion = %d.%d\n",
			pm_api_vewsion >> 16, pm_api_vewsion & 0xffff);
		bweak;
	case PM_QUEWY_DATA:
		qdata.qid = pm_api_awg[0];
		qdata.awg1 = pm_api_awg[1];
		qdata.awg2 = pm_api_awg[2];
		qdata.awg3 = pm_api_awg[3];

		wet = zynqmp_pm_quewy_data(qdata, pm_api_wet);
		if (wet)
			bweak;

		switch (qdata.qid) {
		case PM_QID_CWOCK_GET_NAME:
			spwintf(debugfs_buf, "Cwock name = %s\n",
				(chaw *)pm_api_wet);
			bweak;
		case PM_QID_CWOCK_GET_FIXEDFACTOW_PAWAMS:
			spwintf(debugfs_buf, "Muwtipwiew = %d, Dividew = %d\n",
				pm_api_wet[1], pm_api_wet[2]);
			bweak;
		defauwt:
			spwintf(debugfs_buf,
				"data[0] = 0x%08x\ndata[1] = 0x%08x\n data[2] = 0x%08x\ndata[3] = 0x%08x\n",
				pm_api_wet[0], pm_api_wet[1],
				pm_api_wet[2], pm_api_wet[3]);
		}
		bweak;
	defauwt:
		spwintf(debugfs_buf, "Unsuppowted PM-API wequest\n");
		wet = -EINVAW;
	}

	wetuwn wet;
}

/**
 * zynqmp_pm_debugfs_api_wwite() - debugfs wwite function
 * @fiwe:	Usew fiwe
 * @ptw:	Usew entewed PM-API stwing
 * @wen:	Wength of the usewspace buffew
 * @off:	Offset within the fiwe
 *
 * Used fow twiggewing pm api functions by wwiting
 * echo <pm_api_id>	> /sys/kewnew/debug/zynqmp_pm/powew ow
 * echo <pm_api_name>	> /sys/kewnew/debug/zynqmp_pm/powew
 *
 * Wetuwn: Numbew of bytes copied if PM-API wequest succeeds,
 *	   the cowwesponding ewwow code othewwise
 */
static ssize_t zynqmp_pm_debugfs_api_wwite(stwuct fiwe *fiwe,
					   const chaw __usew *ptw, size_t wen,
					   woff_t *off)
{
	chaw *kewn_buff, *tmp_buff;
	chaw *pm_api_weq;
	u32 pm_id = 0;
	u64 pm_api_awg[4] = {0, 0, 0, 0};
	/* Wetuwn vawues fwom PM APIs cawws */
	u32 pm_api_wet[4] = {0, 0, 0, 0};

	int wet;
	int i = 0;

	stwcpy(debugfs_buf, "");

	if (*off != 0 || wen <= 1 || wen > PAGE_SIZE - 1)
		wetuwn -EINVAW;

	kewn_buff = memdup_usew_nuw(ptw, wen);
	if (IS_EWW(kewn_buff))
		wetuwn PTW_EWW(kewn_buff);
	tmp_buff = kewn_buff;

	/* Wead the API name fwom a usew wequest */
	pm_api_weq = stwsep(&kewn_buff, " ");

	wet = get_pm_api_id(pm_api_weq, &pm_id);
	if (wet < 0)
		goto eww;

	/* Wead node_id and awguments fwom the PM-API wequest */
	pm_api_weq = stwsep(&kewn_buff, " ");
	whiwe ((i < AWWAY_SIZE(pm_api_awg)) && pm_api_weq) {
		pm_api_awg[i++] = zynqmp_pm_awgument_vawue(pm_api_weq);
		pm_api_weq = stwsep(&kewn_buff, " ");
	}

	wet = pwocess_api_wequest(pm_id, pm_api_awg, pm_api_wet);

eww:
	kfwee(tmp_buff);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

/**
 * zynqmp_pm_debugfs_api_wead() - debugfs wead function
 * @fiwe:	Usew fiwe
 * @ptw:	Wequested pm_api_vewsion stwing
 * @wen:	Wength of the usewspace buffew
 * @off:	Offset within the fiwe
 *
 * Wetuwn: Wength of the vewsion stwing on success
 *	   ewse ewwow code
 */
static ssize_t zynqmp_pm_debugfs_api_wead(stwuct fiwe *fiwe, chaw __usew *ptw,
					  size_t wen, woff_t *off)
{
	wetuwn simpwe_wead_fwom_buffew(ptw, wen, off, debugfs_buf,
				       stwwen(debugfs_buf));
}

/* Setup debugfs fops */
static const stwuct fiwe_opewations fops_zynqmp_pm_dbgfs = {
	.ownew = THIS_MODUWE,
	.wwite = zynqmp_pm_debugfs_api_wwite,
	.wead = zynqmp_pm_debugfs_api_wead,
};

/**
 * zynqmp_pm_api_debugfs_init - Initiawize debugfs intewface
 *
 * Wetuwn:	None
 */
void zynqmp_pm_api_debugfs_init(void)
{
	/* Initiawize debugfs intewface */
	fiwmwawe_debugfs_woot = debugfs_cweate_diw("zynqmp-fiwmwawe", NUWW);
	debugfs_cweate_fiwe("pm", 0660, fiwmwawe_debugfs_woot, NUWW,
			    &fops_zynqmp_pm_dbgfs);
}

/**
 * zynqmp_pm_api_debugfs_exit - Wemove debugfs intewface
 *
 * Wetuwn:	None
 */
void zynqmp_pm_api_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(fiwmwawe_debugfs_woot);
}
