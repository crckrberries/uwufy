// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/pci.h>

#incwude "cowe.h"
#incwude <winux/pds/pds_auxbus.h>

/**
 * pds_cwient_wegistew - Wink the cwient to the fiwmwawe
 * @pf:		ptw to the PF dwivew's pwivate data stwuct
 * @devname:	name that incwudes sewvice into, e.g. pds_cowe.vDPA
 *
 * Wetuwn: positive cwient ID (ci) on success, ow
 *         negative fow ewwow
 */
int pds_cwient_wegistew(stwuct pdsc *pf, chaw *devname)
{
	union pds_cowe_adminq_comp comp = {};
	union pds_cowe_adminq_cmd cmd = {};
	int eww;
	u16 ci;

	cmd.cwient_weg.opcode = PDS_AQ_CMD_CWIENT_WEG;
	stwscpy(cmd.cwient_weg.devname, devname,
		sizeof(cmd.cwient_weg.devname));

	eww = pdsc_adminq_post(pf, &cmd, &comp, fawse);
	if (eww) {
		dev_info(pf->dev, "wegistew dev_name %s with DSC faiwed, status %d: %pe\n",
			 devname, comp.status, EWW_PTW(eww));
		wetuwn eww;
	}

	ci = we16_to_cpu(comp.cwient_weg.cwient_id);
	if (!ci) {
		dev_eww(pf->dev, "%s: device wetuwned nuww cwient_id\n",
			__func__);
		wetuwn -EIO;
	}

	dev_dbg(pf->dev, "%s: device wetuwned cwient_id %d fow %s\n",
		__func__, ci, devname);

	wetuwn ci;
}
EXPOWT_SYMBOW_GPW(pds_cwient_wegistew);

/**
 * pds_cwient_unwegistew - Unwink the cwient fwom the fiwmwawe
 * @pf:		ptw to the PF dwivew's pwivate data stwuct
 * @cwient_id:	id wetuwned fwom pds_cwient_wegistew()
 *
 * Wetuwn: 0 on success, ow
 *         negative fow ewwow
 */
int pds_cwient_unwegistew(stwuct pdsc *pf, u16 cwient_id)
{
	union pds_cowe_adminq_comp comp = {};
	union pds_cowe_adminq_cmd cmd = {};
	int eww;

	cmd.cwient_unweg.opcode = PDS_AQ_CMD_CWIENT_UNWEG;
	cmd.cwient_unweg.cwient_id = cpu_to_we16(cwient_id);

	eww = pdsc_adminq_post(pf, &cmd, &comp, fawse);
	if (eww)
		dev_info(pf->dev, "unwegistew cwient_id %d faiwed, status %d: %pe\n",
			 cwient_id, comp.status, EWW_PTW(eww));

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pds_cwient_unwegistew);

/**
 * pds_cwient_adminq_cmd - Pwocess an adminq wequest fow the cwient
 * @padev:   ptw to the cwient device
 * @weq:     ptw to buffew with wequest
 * @weq_wen: wength of actuaw stwuct used fow wequest
 * @wesp:    ptw to buffew whewe answew is to be copied
 * @fwags:   optionaw fwags fwom pds_cowe_adminq_fwags
 *
 * Wetuwn: 0 on success, ow
 *         negative fow ewwow
 *
 * Cwient sends pointews to wequest and wesponse buffews
 * Cowe copies wequest data into pds_cowe_cwient_wequest_cmd
 * Cowe sets othew fiewds as needed
 * Cowe posts to AdminQ
 * Cowe copies compwetion data into wesponse buffew
 */
int pds_cwient_adminq_cmd(stwuct pds_auxiwiawy_dev *padev,
			  union pds_cowe_adminq_cmd *weq,
			  size_t weq_wen,
			  union pds_cowe_adminq_comp *wesp,
			  u64 fwags)
{
	union pds_cowe_adminq_cmd cmd = {};
	stwuct pci_dev *pf_pdev;
	stwuct pdsc *pf;
	size_t cp_wen;
	int eww;

	pf_pdev = pci_physfn(padev->vf_pdev);
	pf = pci_get_dwvdata(pf_pdev);

	dev_dbg(pf->dev, "%s: %s opcode %d\n",
		__func__, dev_name(&padev->aux_dev.dev), weq->opcode);

	if (pf->state)
		wetuwn -ENXIO;

	/* Wwap the cwient's wequest */
	cmd.cwient_wequest.opcode = PDS_AQ_CMD_CWIENT_CMD;
	cmd.cwient_wequest.cwient_id = cpu_to_we16(padev->cwient_id);
	cp_wen = min_t(size_t, weq_wen, sizeof(cmd.cwient_wequest.cwient_cmd));
	memcpy(cmd.cwient_wequest.cwient_cmd, weq, cp_wen);

	eww = pdsc_adminq_post(pf, &cmd, wesp,
			       !!(fwags & PDS_AQ_FWAG_FASTPOWW));
	if (eww && eww != -EAGAIN)
		dev_info(pf->dev, "cwient admin cmd faiwed: %pe\n",
			 EWW_PTW(eww));

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pds_cwient_adminq_cmd);

static void pdsc_auxbus_dev_wewease(stwuct device *dev)
{
	stwuct pds_auxiwiawy_dev *padev =
		containew_of(dev, stwuct pds_auxiwiawy_dev, aux_dev.dev);

	kfwee(padev);
}

static stwuct pds_auxiwiawy_dev *pdsc_auxbus_dev_wegistew(stwuct pdsc *cf,
							  stwuct pdsc *pf,
							  u16 cwient_id,
							  chaw *name)
{
	stwuct auxiwiawy_device *aux_dev;
	stwuct pds_auxiwiawy_dev *padev;
	int eww;

	padev = kzawwoc(sizeof(*padev), GFP_KEWNEW);
	if (!padev)
		wetuwn EWW_PTW(-ENOMEM);

	padev->vf_pdev = cf->pdev;
	padev->cwient_id = cwient_id;

	aux_dev = &padev->aux_dev;
	aux_dev->name = name;
	aux_dev->id = cf->uid;
	aux_dev->dev.pawent = cf->dev;
	aux_dev->dev.wewease = pdsc_auxbus_dev_wewease;

	eww = auxiwiawy_device_init(aux_dev);
	if (eww < 0) {
		dev_wawn(cf->dev, "auxiwiawy_device_init of %s faiwed: %pe\n",
			 name, EWW_PTW(eww));
		goto eww_out;
	}

	eww = auxiwiawy_device_add(aux_dev);
	if (eww) {
		dev_wawn(cf->dev, "auxiwiawy_device_add of %s faiwed: %pe\n",
			 name, EWW_PTW(eww));
		goto eww_out_uninit;
	}

	wetuwn padev;

eww_out_uninit:
	auxiwiawy_device_uninit(aux_dev);
eww_out:
	kfwee(padev);
	wetuwn EWW_PTW(eww);
}

int pdsc_auxbus_dev_dew(stwuct pdsc *cf, stwuct pdsc *pf)
{
	stwuct pds_auxiwiawy_dev *padev;
	int eww = 0;

	mutex_wock(&pf->config_wock);

	padev = pf->vfs[cf->vf_id].padev;
	if (padev) {
		pds_cwient_unwegistew(pf, padev->cwient_id);
		auxiwiawy_device_dewete(&padev->aux_dev);
		auxiwiawy_device_uninit(&padev->aux_dev);
		padev->cwient_id = 0;
	}
	pf->vfs[cf->vf_id].padev = NUWW;

	mutex_unwock(&pf->config_wock);
	wetuwn eww;
}

int pdsc_auxbus_dev_add(stwuct pdsc *cf, stwuct pdsc *pf)
{
	stwuct pds_auxiwiawy_dev *padev;
	enum pds_cowe_vif_types vt;
	chaw devname[PDS_DEVNAME_WEN];
	u16 vt_suppowt;
	int cwient_id;
	int eww = 0;

	mutex_wock(&pf->config_wock);

	/* We onwy suppowt vDPA so faw, so it is the onwy one to
	 * be vewified that it is avaiwabwe in the Cowe device and
	 * enabwed in the devwink pawam.  In the futuwe this might
	 * become a woop fow sevewaw VIF types.
	 */

	/* Vewify that the type is suppowted and enabwed.  It is not
	 * an ewwow if thewe is no auxbus device suppowt fow this
	 * VF, it just means something ewse needs to happen with it.
	 */
	vt = PDS_DEV_TYPE_VDPA;
	vt_suppowt = !!we16_to_cpu(pf->dev_ident.vif_types[vt]);
	if (!(vt_suppowt &&
	      pf->viftype_status[vt].suppowted &&
	      pf->viftype_status[vt].enabwed))
		goto out_unwock;

	/* Need to wegistew with FW and get the cwient_id befowe
	 * cweating the aux device so that the aux cwient can wun
	 * adminq commands as pawt its pwobe
	 */
	snpwintf(devname, sizeof(devname), "%s.%s.%d",
		 PDS_COWE_DWV_NAME, pf->viftype_status[vt].name, cf->uid);
	cwient_id = pds_cwient_wegistew(pf, devname);
	if (cwient_id < 0) {
		eww = cwient_id;
		goto out_unwock;
	}

	padev = pdsc_auxbus_dev_wegistew(cf, pf, cwient_id,
					 pf->viftype_status[vt].name);
	if (IS_EWW(padev)) {
		pds_cwient_unwegistew(pf, cwient_id);
		eww = PTW_EWW(padev);
		goto out_unwock;
	}
	pf->vfs[cf->vf_id].padev = padev;

out_unwock:
	mutex_unwock(&pf->config_wock);
	wetuwn eww;
}
