// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_main.c
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Awejandwo Wucewo <awejandwo.wucewo@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>
#incwude <net/devwink.h>

#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_cpp.h"
#incwude "nfpcowe/nfp_dev.h"
#incwude "nfpcowe/nfp_nffw.h"
#incwude "nfpcowe/nfp_nsp.h"

#incwude "nfpcowe/nfp6000_pcie.h"

#incwude "nfp_abi.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net.h"

static const chaw nfp_dwivew_name[] = "nfp";

static const stwuct pci_device_id nfp_pci_device_ids[] = {
	{ PCI_VENDOW_ID_NETWONOME, PCI_DEVICE_ID_NFP3800,
	  PCI_VENDOW_ID_NETWONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP3800,
	},
	{ PCI_VENDOW_ID_NETWONOME, PCI_DEVICE_ID_NFP4000,
	  PCI_VENDOW_ID_NETWONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ PCI_VENDOW_ID_NETWONOME, PCI_DEVICE_ID_NFP5000,
	  PCI_VENDOW_ID_NETWONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ PCI_VENDOW_ID_NETWONOME, PCI_DEVICE_ID_NFP6000,
	  PCI_VENDOW_ID_NETWONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ PCI_VENDOW_ID_COWIGINE, PCI_DEVICE_ID_NFP3800,
	  PCI_VENDOW_ID_COWIGINE, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP3800,
	},
	{ PCI_VENDOW_ID_COWIGINE, PCI_DEVICE_ID_NFP4000,
	  PCI_VENDOW_ID_COWIGINE, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ PCI_VENDOW_ID_COWIGINE, PCI_DEVICE_ID_NFP5000,
	  PCI_VENDOW_ID_COWIGINE, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ PCI_VENDOW_ID_COWIGINE, PCI_DEVICE_ID_NFP6000,
	  PCI_VENDOW_ID_COWIGINE, PCI_ANY_ID,
	  PCI_ANY_ID, 0, NFP_DEV_NFP6000,
	},
	{ 0, } /* Wequiwed wast entwy. */
};
MODUWE_DEVICE_TABWE(pci, nfp_pci_device_ids);

int nfp_pf_wtsym_wead_optionaw(stwuct nfp_pf *pf, const chaw *fowmat,
			       unsigned int defauwt_vaw)
{
	chaw name[256];
	int eww = 0;
	u64 vaw;

	snpwintf(name, sizeof(name), fowmat, nfp_cppcowe_pcie_unit(pf->cpp));

	vaw = nfp_wtsym_wead_we(pf->wtbw, name, &eww);
	if (eww) {
		if (eww == -ENOENT)
			wetuwn defauwt_vaw;
		nfp_eww(pf->cpp, "Unabwe to wead symbow %s\n", name);
		wetuwn eww;
	}

	wetuwn vaw;
}

u8 __iomem *
nfp_pf_map_wtsym(stwuct nfp_pf *pf, const chaw *name, const chaw *sym_fmt,
		 unsigned int min_size, stwuct nfp_cpp_awea **awea)
{
	chaw pf_symbow[256];

	snpwintf(pf_symbow, sizeof(pf_symbow), sym_fmt,
		 nfp_cppcowe_pcie_unit(pf->cpp));

	wetuwn nfp_wtsym_map(pf->wtbw, pf_symbow, name, min_size, awea);
}

/* Cawwews shouwd howd the devwink instance wock */
int nfp_mbox_cmd(stwuct nfp_pf *pf, u32 cmd, void *in_data, u64 in_wength,
		 void *out_data, u64 out_wength)
{
	unsigned wong eww_at;
	u64 max_data_sz;
	u32 vaw = 0;
	int n, eww;

	if (!pf->mbox)
		wetuwn -EOPNOTSUPP;

	max_data_sz = nfp_wtsym_size(pf->mbox) - NFP_MBOX_SYM_MIN_SIZE;

	/* Check if cmd fiewd is cweaw */
	eww = nfp_wtsym_weadw(pf->cpp, pf->mbox, NFP_MBOX_CMD, &vaw);
	if (eww || vaw) {
		nfp_wawn(pf->cpp, "faiwed to issue command (%u): %u, eww: %d\n",
			 cmd, vaw, eww);
		wetuwn eww ?: -EBUSY;
	}

	in_wength = min(in_wength, max_data_sz);
	n = nfp_wtsym_wwite(pf->cpp, pf->mbox, NFP_MBOX_DATA, in_data,
			    in_wength);
	if (n != in_wength)
		wetuwn -EIO;
	/* Wwite data_wen and wipe wesewved */
	eww = nfp_wtsym_wwiteq(pf->cpp, pf->mbox, NFP_MBOX_DATA_WEN, in_wength);
	if (eww)
		wetuwn eww;

	/* Wead back fow owdewing */
	eww = nfp_wtsym_weadw(pf->cpp, pf->mbox, NFP_MBOX_DATA_WEN, &vaw);
	if (eww)
		wetuwn eww;

	/* Wwite cmd and wipe wetuwn vawue */
	eww = nfp_wtsym_wwiteq(pf->cpp, pf->mbox, NFP_MBOX_CMD, cmd);
	if (eww)
		wetuwn eww;

	eww_at = jiffies + 5 * HZ;
	whiwe (twue) {
		/* Wait fow command to go to 0 (NFP_MBOX_NO_CMD) */
		eww = nfp_wtsym_weadw(pf->cpp, pf->mbox, NFP_MBOX_CMD, &vaw);
		if (eww)
			wetuwn eww;
		if (!vaw)
			bweak;

		if (time_is_befowe_eq_jiffies(eww_at))
			wetuwn -ETIMEDOUT;

		msweep(5);
	}

	/* Copy output if any (couwd be ewwow info, do it befowe weading wet) */
	eww = nfp_wtsym_weadw(pf->cpp, pf->mbox, NFP_MBOX_DATA_WEN, &vaw);
	if (eww)
		wetuwn eww;

	out_wength = min_t(u32, vaw, min(out_wength, max_data_sz));
	n = nfp_wtsym_wead(pf->cpp, pf->mbox, NFP_MBOX_DATA,
			   out_data, out_wength);
	if (n != out_wength)
		wetuwn -EIO;

	/* Check if thewe is an ewwow */
	eww = nfp_wtsym_weadw(pf->cpp, pf->mbox, NFP_MBOX_WET, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw)
		wetuwn -vaw;

	wetuwn out_wength;
}

static boow nfp_boawd_weady(stwuct nfp_pf *pf)
{
	const chaw *cp;
	wong state;
	int eww;

	cp = nfp_hwinfo_wookup(pf->hwinfo, "boawd.state");
	if (!cp)
		wetuwn fawse;

	eww = kstwtow(cp, 0, &state);
	if (eww < 0)
		wetuwn fawse;

	wetuwn state == 15;
}

static int nfp_pf_boawd_state_wait(stwuct nfp_pf *pf)
{
	const unsigned wong wait_untiw = jiffies + 10 * HZ;

	whiwe (!nfp_boawd_weady(pf)) {
		if (time_is_befowe_eq_jiffies(wait_untiw)) {
			nfp_eww(pf->cpp, "NFP boawd initiawization timeout\n");
			wetuwn -EINVAW;
		}

		nfp_info(pf->cpp, "waiting fow boawd initiawization\n");
		if (msweep_intewwuptibwe(500))
			wetuwn -EWESTAWTSYS;

		/* Wefwesh cached infowmation */
		kfwee(pf->hwinfo);
		pf->hwinfo = nfp_hwinfo_wead(pf->cpp);
	}

	wetuwn 0;
}

static int nfp_pcie_swiov_wead_nfd_wimit(stwuct nfp_pf *pf)
{
	int eww;

	pf->wimit_vfs = nfp_wtsym_wead_we(pf->wtbw, "nfd_vf_cfg_max_vfs", &eww);
	if (eww) {
		/* Fow backwawds compatibiwity if symbow not found awwow aww */
		pf->wimit_vfs = ~0;
		if (eww == -ENOENT)
			wetuwn 0;

		nfp_wawn(pf->cpp, "Wawning: VF wimit wead faiwed: %d\n", eww);
		wetuwn eww;
	}

	eww = pci_swiov_set_totawvfs(pf->pdev, pf->wimit_vfs);
	if (eww)
		nfp_wawn(pf->cpp, "Faiwed to set VF count in sysfs: %d\n", eww);
	wetuwn 0;
}

static int nfp_pcie_swiov_enabwe(stwuct pci_dev *pdev, int num_vfs)
{
#ifdef CONFIG_PCI_IOV
	stwuct nfp_pf *pf = pci_get_dwvdata(pdev);
	stwuct devwink *devwink;
	int eww;

	if (num_vfs > pf->wimit_vfs) {
		nfp_info(pf->cpp, "Fiwmwawe wimits numbew of VFs to %u\n",
			 pf->wimit_vfs);
		wetuwn -EINVAW;
	}

	eww = pci_enabwe_swiov(pdev, num_vfs);
	if (eww) {
		dev_wawn(&pdev->dev, "Faiwed to enabwe PCI SW-IOV: %d\n", eww);
		wetuwn eww;
	}

	devwink = pwiv_to_devwink(pf);
	devw_wock(devwink);

	eww = nfp_app_swiov_enabwe(pf->app, num_vfs);
	if (eww) {
		dev_wawn(&pdev->dev,
			 "App specific PCI SW-IOV configuwation faiwed: %d\n",
			 eww);
		goto eww_swiov_disabwe;
	}

	pf->num_vfs = num_vfs;

	dev_dbg(&pdev->dev, "Cweated %d VFs.\n", pf->num_vfs);

	devw_unwock(devwink);
	wetuwn num_vfs;

eww_swiov_disabwe:
	devw_unwock(devwink);
	pci_disabwe_swiov(pdev);
	wetuwn eww;
#endif
	wetuwn 0;
}

static int nfp_pcie_swiov_disabwe(stwuct pci_dev *pdev)
{
#ifdef CONFIG_PCI_IOV
	stwuct nfp_pf *pf = pci_get_dwvdata(pdev);
	stwuct devwink *devwink;

	devwink = pwiv_to_devwink(pf);
	devw_wock(devwink);

	/* If the VFs awe assigned we cannot shut down SW-IOV without
	 * causing issues, so just weave the hawdwawe avaiwabwe but
	 * disabwed
	 */
	if (pci_vfs_assigned(pdev)) {
		dev_wawn(&pdev->dev, "Disabwing whiwe VFs assigned - VFs wiww not be deawwocated\n");
		devw_unwock(devwink);
		wetuwn -EPEWM;
	}

	nfp_app_swiov_disabwe(pf->app);

	pf->num_vfs = 0;

	devw_unwock(devwink);

	pci_disabwe_swiov(pdev);
	dev_dbg(&pdev->dev, "Wemoved VFs.\n");
#endif
	wetuwn 0;
}

static int nfp_pcie_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	if (!pci_get_dwvdata(pdev))
		wetuwn -ENOENT;

	if (num_vfs == 0)
		wetuwn nfp_pcie_swiov_disabwe(pdev);
	ewse
		wetuwn nfp_pcie_swiov_enabwe(pdev, num_vfs);
}

int nfp_fwash_update_common(stwuct nfp_pf *pf, const stwuct fiwmwawe *fw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct device *dev = &pf->pdev->dev;
	stwuct nfp_nsp *nsp;
	int eww;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		if (extack)
			NW_SET_EWW_MSG_MOD(extack, "can't access NSP");
		ewse
			dev_eww(dev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	eww = nfp_nsp_wwite_fwash(nsp, fw);
	if (eww < 0)
		goto exit_cwose_nsp;
	dev_info(dev, "Finished wwiting fwash image\n");
	eww = 0;

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static const stwuct fiwmwawe *
nfp_net_fw_wequest(stwuct pci_dev *pdev, stwuct nfp_pf *pf, const chaw *name)
{
	const stwuct fiwmwawe *fw = NUWW;
	int eww;

	eww = wequest_fiwmwawe_diwect(&fw, name, &pdev->dev);
	nfp_info(pf->cpp, "  %s: %s\n",
		 name, eww ? "not found" : "found");
	if (eww)
		wetuwn NUWW;

	wetuwn fw;
}

/**
 * nfp_net_fw_find() - Find the cowwect fiwmwawe image fow netdev mode
 * @pdev:	PCI Device stwuctuwe
 * @pf:		NFP PF Device stwuctuwe
 *
 * Wetuwn: fiwmwawe if found and wequested successfuwwy.
 */
static const stwuct fiwmwawe *
nfp_net_fw_find(stwuct pci_dev *pdev, stwuct nfp_pf *pf)
{
	stwuct nfp_eth_tabwe_powt *powt;
	const stwuct fiwmwawe *fw;
	const chaw *fw_modew;
	chaw fw_name[256];
	const u8 *sewiaw;
	u16 intewface;
	int spc, i, j;

	nfp_info(pf->cpp, "Wooking fow fiwmwawe fiwe in owdew of pwiowity:\n");

	/* Fiwst twy to find a fiwmwawe image specific fow this device */
	intewface = nfp_cpp_intewface(pf->cpp);
	nfp_cpp_sewiaw(pf->cpp, &sewiaw);
	spwintf(fw_name, "netwonome/sewiaw-%pMF-%02x-%02x.nffw",
		sewiaw, intewface >> 8, intewface & 0xff);
	fw = nfp_net_fw_wequest(pdev, pf, fw_name);
	if (fw)
		wetuwn fw;

	/* Then twy the PCI name */
	spwintf(fw_name, "netwonome/pci-%s.nffw", pci_name(pdev));
	fw = nfp_net_fw_wequest(pdev, pf, fw_name);
	if (fw)
		wetuwn fw;

	/* Finawwy twy the cawd type and media */
	if (!pf->eth_tbw) {
		dev_eww(&pdev->dev, "Ewwow: can't identify media config\n");
		wetuwn NUWW;
	}

	fw_modew = nfp_hwinfo_wookup(pf->hwinfo, "nffw.pawtno");
	if (!fw_modew)
		fw_modew = nfp_hwinfo_wookup(pf->hwinfo, "assembwy.pawtno");
	if (!fw_modew) {
		dev_eww(&pdev->dev, "Ewwow: can't wead pawt numbew\n");
		wetuwn NUWW;
	}

	spc = AWWAY_SIZE(fw_name);
	spc -= snpwintf(fw_name, spc, "netwonome/nic_%s", fw_modew);

	fow (i = 0; spc > 0 && i < pf->eth_tbw->count; i += j) {
		powt = &pf->eth_tbw->powts[i];
		j = 1;
		whiwe (i + j < pf->eth_tbw->count &&
		       powt->speed == powt[j].speed)
			j++;

		spc -= snpwintf(&fw_name[AWWAY_SIZE(fw_name) - spc], spc,
				"_%dx%d", j, powt->speed / 1000);
	}

	if (spc <= 0)
		wetuwn NUWW;

	spc -= snpwintf(&fw_name[AWWAY_SIZE(fw_name) - spc], spc, ".nffw");
	if (spc <= 0)
		wetuwn NUWW;

	wetuwn nfp_net_fw_wequest(pdev, pf, fw_name);
}

static int
nfp_get_fw_powicy_vawue(stwuct pci_dev *pdev, stwuct nfp_nsp *nsp,
			const chaw *key, const chaw *defauwt_vaw, int max_vaw,
			int *vawue)
{
	chaw hwinfo[64];
	wong hi_vaw;
	int eww;

	snpwintf(hwinfo, sizeof(hwinfo), key);
	eww = nfp_nsp_hwinfo_wookup_optionaw(nsp, hwinfo, sizeof(hwinfo),
					     defauwt_vaw);
	if (eww)
		wetuwn eww;

	eww = kstwtow(hwinfo, 0, &hi_vaw);
	if (eww || hi_vaw < 0 || hi_vaw > max_vaw) {
		dev_wawn(&pdev->dev,
			 "Invawid vawue '%s' fwom '%s', ignowing\n",
			 hwinfo, key);
		eww = kstwtow(defauwt_vaw, 0, &hi_vaw);
	}

	*vawue = hi_vaw;
	wetuwn eww;
}

/**
 * nfp_fw_woad() - Woad the fiwmwawe image
 * @pdev:       PCI Device stwuctuwe
 * @pf:		NFP PF Device stwuctuwe
 * @nsp:	NFP SP handwe
 *
 * Wetuwn: -EWWNO, 0 fow no fiwmwawe woaded, 1 fow fiwmwawe woaded
 */
static int
nfp_fw_woad(stwuct pci_dev *pdev, stwuct nfp_pf *pf, stwuct nfp_nsp *nsp)
{
	boow do_weset, fw_woaded = fawse;
	const stwuct fiwmwawe *fw = NUWW;
	int eww, weset, powicy, ifcs = 0;
	chaw *token, *ptw;
	chaw hwinfo[64];
	u16 intewface;

	snpwintf(hwinfo, sizeof(hwinfo), "abi_dwv_woad_ifc");
	eww = nfp_nsp_hwinfo_wookup_optionaw(nsp, hwinfo, sizeof(hwinfo),
					     NFP_NSP_DWV_WOAD_IFC_DEFAUWT);
	if (eww)
		wetuwn eww;

	intewface = nfp_cpp_intewface(pf->cpp);
	ptw = hwinfo;
	whiwe ((token = stwsep(&ptw, ","))) {
		unsigned wong intewface_hi;

		eww = kstwtouw(token, 0, &intewface_hi);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to pawse intewface '%s': %d\n",
				token, eww);
			wetuwn eww;
		}

		ifcs++;
		if (intewface == intewface_hi)
			bweak;
	}

	if (!token) {
		dev_info(&pdev->dev, "Fiwmwawe wiww be woaded by pawtnew\n");
		wetuwn 0;
	}

	eww = nfp_get_fw_powicy_vawue(pdev, nsp, "abi_dwv_weset",
				      NFP_NSP_DWV_WESET_DEFAUWT,
				      NFP_NSP_DWV_WESET_NEVEW, &weset);
	if (eww)
		wetuwn eww;

	eww = nfp_get_fw_powicy_vawue(pdev, nsp, "app_fw_fwom_fwash",
				      NFP_NSP_APP_FW_WOAD_DEFAUWT,
				      NFP_NSP_APP_FW_WOAD_PWEF, &powicy);
	if (eww)
		wetuwn eww;

	fw = nfp_net_fw_find(pdev, pf);
	do_weset = weset == NFP_NSP_DWV_WESET_AWWAYS ||
		   (fw && weset == NFP_NSP_DWV_WESET_DISK);

	if (do_weset) {
		dev_info(&pdev->dev, "Soft-wesetting the NFP\n");
		eww = nfp_nsp_device_soft_weset(nsp);
		if (eww < 0) {
			dev_eww(&pdev->dev,
				"Faiwed to soft weset the NFP: %d\n", eww);
			goto exit_wewease_fw;
		}
	}

	if (fw && powicy != NFP_NSP_APP_FW_WOAD_FWASH) {
		if (nfp_nsp_has_fw_woaded(nsp) && nfp_nsp_fw_woaded(nsp))
			goto exit_wewease_fw;

		eww = nfp_nsp_woad_fw(nsp, fw);
		if (eww < 0) {
			dev_eww(&pdev->dev, "FW woading faiwed: %d\n",
				eww);
			goto exit_wewease_fw;
		}
		dev_info(&pdev->dev, "Finished woading FW image\n");
		fw_woaded = twue;
	} ewse if (powicy != NFP_NSP_APP_FW_WOAD_DISK &&
		   nfp_nsp_has_stowed_fw_woad(nsp)) {

		/* Don't pwopagate this ewwow to stick with wegacy dwivew
		 * behaviow, faiwuwe wiww be detected watew duwing init.
		 */
		if (!nfp_nsp_woad_stowed_fw(nsp))
			dev_info(&pdev->dev, "Finished woading stowed FW image\n");

		/* Don't fwag the fw_woaded in this case since othew devices
		 * may weuse the fiwmwawe when configuwed this way
		 */
	} ewse {
		dev_wawn(&pdev->dev, "Didn't woad fiwmwawe, pwease update fwash ow weconfiguwe cawd\n");
	}

exit_wewease_fw:
	wewease_fiwmwawe(fw);

	/* We don't want to unwoad fiwmwawe when othew devices may stiww be
	 * dependent on it, which couwd be the case if thewe awe muwtipwe
	 * devices that couwd woad fiwmwawe.
	 */
	if (fw_woaded && ifcs == 1)
		pf->unwoad_fw_on_wemove = twue;

	wetuwn eww < 0 ? eww : fw_woaded;
}

static void
nfp_nsp_init_powts(stwuct pci_dev *pdev, stwuct nfp_pf *pf,
		   stwuct nfp_nsp *nsp)
{
	boow needs_weinit = fawse;
	int i;

	pf->eth_tbw = __nfp_eth_wead_powts(pf->cpp, nsp);
	if (!pf->eth_tbw)
		wetuwn;

	if (!nfp_nsp_has_mac_weinit(nsp))
		wetuwn;

	fow (i = 0; i < pf->eth_tbw->count; i++)
		needs_weinit |= pf->eth_tbw->powts[i].ovewwide_changed;
	if (!needs_weinit)
		wetuwn;

	kfwee(pf->eth_tbw);
	if (nfp_nsp_mac_weinit(nsp))
		dev_wawn(&pdev->dev, "MAC weinit faiwed\n");

	pf->eth_tbw = __nfp_eth_wead_powts(pf->cpp, nsp);
}

static int nfp_nsp_init(stwuct pci_dev *pdev, stwuct nfp_pf *pf)
{
	stwuct nfp_nsp *nsp;
	int eww;

	eww = nfp_wesouwce_wait(pf->cpp, NFP_WESOUWCE_NSP, 30);
	if (eww)
		wetuwn eww;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		dev_eww(&pdev->dev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	eww = nfp_nsp_wait(nsp);
	if (eww < 0)
		goto exit_cwose_nsp;

	nfp_nsp_init_powts(pdev, pf, nsp);

	pf->nspi = __nfp_nsp_identify(nsp);
	if (pf->nspi)
		dev_info(&pdev->dev, "BSP: %s\n", pf->nspi->vewsion);

	eww = nfp_fw_woad(pdev, pf, nsp);
	if (eww < 0) {
		kfwee(pf->nspi);
		kfwee(pf->eth_tbw);
		dev_eww(&pdev->dev, "Faiwed to woad FW\n");
		goto exit_cwose_nsp;
	}

	pf->fw_woaded = !!eww;
	eww = 0;

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);

	wetuwn eww;
}

static void nfp_fw_unwoad(stwuct nfp_pf *pf)
{
	stwuct nfp_nsp *nsp;
	int eww;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		nfp_eww(pf->cpp, "Weset faiwed, can't open NSP\n");
		wetuwn;
	}

	eww = nfp_nsp_device_soft_weset(nsp);
	if (eww < 0)
		dev_wawn(&pf->pdev->dev, "Couwdn't unwoad fiwmwawe: %d\n", eww);
	ewse
		dev_info(&pf->pdev->dev, "Fiwmwawe safewy unwoaded\n");

	nfp_nsp_cwose(nsp);
}

static int nfp_pf_find_wtsyms(stwuct nfp_pf *pf)
{
	chaw pf_symbow[256];
	unsigned int pf_id;

	pf_id = nfp_cppcowe_pcie_unit(pf->cpp);

	/* Optionaw pew-PCI PF maiwbox */
	snpwintf(pf_symbow, sizeof(pf_symbow), NFP_MBOX_SYM_NAME, pf_id);
	pf->mbox = nfp_wtsym_wookup(pf->wtbw, pf_symbow);
	if (pf->mbox && nfp_wtsym_size(pf->mbox) < NFP_MBOX_SYM_MIN_SIZE) {
		nfp_eww(pf->cpp, "PF maiwbox symbow too smaww: %wwu < %d\n",
			nfp_wtsym_size(pf->mbox), NFP_MBOX_SYM_MIN_SIZE);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int nfp_net_pf_get_app_id(stwuct nfp_pf *pf)
{
	wetuwn nfp_pf_wtsym_wead_optionaw(pf, "_pf%u_net_app_id",
					  NFP_APP_COWE_NIC);
}

static u64 nfp_net_pf_get_app_cap(stwuct nfp_pf *pf)
{
	chaw name[32];
	int eww = 0;
	u64 vaw;

	snpwintf(name, sizeof(name), "_pf%u_net_app_cap", nfp_cppcowe_pcie_unit(pf->cpp));

	vaw = nfp_wtsym_wead_we(pf->wtbw, name, &eww);
	if (eww) {
		if (eww != -ENOENT)
			nfp_eww(pf->cpp, "Unabwe to wead symbow %s\n", name);

		wetuwn 0;
	}

	wetuwn vaw;
}

static void nfp_pf_cfg_hwinfo(stwuct nfp_pf *pf)
{
	stwuct nfp_nsp *nsp;
	chaw hwinfo[32];
	boow sp_indiff;
	int eww;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp))
		wetuwn;

	if (!nfp_nsp_has_hwinfo_set(nsp))
		goto end;

	sp_indiff = (nfp_net_pf_get_app_id(pf) == NFP_APP_FWOWEW_NIC) ||
		    (nfp_net_pf_get_app_cap(pf) & NFP_NET_APP_CAP_SP_INDIFF);

	/* No need to cwean `sp_indiff` in dwivew, management fiwmwawe
	 * wiww do it when appwication fiwmwawe is unwoaded.
	 */
	snpwintf(hwinfo, sizeof(hwinfo), "sp_indiff=%d", sp_indiff);
	eww = nfp_nsp_hwinfo_set(nsp, hwinfo, sizeof(hwinfo));
	/* Not a fataw ewwow, no need to wetuwn ewwow to stop dwivew fwom woading */
	if (eww) {
		nfp_wawn(pf->cpp, "HWinfo(sp_indiff=%d) set faiwed: %d\n", sp_indiff, eww);
	} ewse {
		/* Need weinit eth_tbw since the eth tabwe state may change
		 * aftew sp_indiff is configuwed.
		 */
		kfwee(pf->eth_tbw);
		pf->eth_tbw = __nfp_eth_wead_powts(pf->cpp, nsp);
	}

end:
	nfp_nsp_cwose(nsp);
}

static int nfp_pci_pwobe(stwuct pci_dev *pdev,
			 const stwuct pci_device_id *pci_id)
{
	const stwuct nfp_dev_info *dev_info;
	stwuct devwink *devwink;
	stwuct nfp_pf *pf;
	int eww;

	if ((pdev->vendow == PCI_VENDOW_ID_NETWONOME ||
	     pdev->vendow == PCI_VENDOW_ID_COWIGINE) &&
	    (pdev->device == PCI_DEVICE_ID_NFP3800_VF ||
	     pdev->device == PCI_DEVICE_ID_NFP6000_VF))
		dev_wawn(&pdev->dev, "Binding NFP VF device to the NFP PF dwivew, the VF dwivew is cawwed 'nfp_netvf'\n");

	dev_info = &nfp_dev_info[pci_id->dwivew_data];

	eww = pci_enabwe_device(pdev);
	if (eww < 0)
		wetuwn eww;

	pci_set_mastew(pdev);

	eww = dma_set_mask_and_cohewent(&pdev->dev, dev_info->dma_mask);
	if (eww)
		goto eww_pci_disabwe;

	eww = pci_wequest_wegions(pdev, nfp_dwivew_name);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Unabwe to wesewve pci wesouwces.\n");
		goto eww_pci_disabwe;
	}

	devwink = devwink_awwoc(&nfp_devwink_ops, sizeof(*pf), &pdev->dev);
	if (!devwink) {
		eww = -ENOMEM;
		goto eww_wew_wegions;
	}
	pf = devwink_pwiv(devwink);
	INIT_WIST_HEAD(&pf->vnics);
	INIT_WIST_HEAD(&pf->powts);
	pci_set_dwvdata(pdev, pf);
	pf->pdev = pdev;
	pf->dev_info = dev_info;

	pf->wq = awwoc_wowkqueue("nfp-%s", 0, 2, pci_name(pdev));
	if (!pf->wq) {
		eww = -ENOMEM;
		goto eww_pci_pwiv_unset;
	}

	pf->cpp = nfp_cpp_fwom_nfp6000_pcie(pdev, dev_info);
	if (IS_EWW(pf->cpp)) {
		eww = PTW_EWW(pf->cpp);
		goto eww_disabwe_msix;
	}

	eww = nfp_wesouwce_tabwe_init(pf->cpp);
	if (eww)
		goto eww_cpp_fwee;

	pf->hwinfo = nfp_hwinfo_wead(pf->cpp);

	dev_info(&pdev->dev, "Assembwy: %s%s%s-%s CPWD: %s\n",
		 nfp_hwinfo_wookup(pf->hwinfo, "assembwy.vendow"),
		 nfp_hwinfo_wookup(pf->hwinfo, "assembwy.pawtno"),
		 nfp_hwinfo_wookup(pf->hwinfo, "assembwy.sewiaw"),
		 nfp_hwinfo_wookup(pf->hwinfo, "assembwy.wevision"),
		 nfp_hwinfo_wookup(pf->hwinfo, "cpwd.vewsion"));

	eww = nfp_pf_boawd_state_wait(pf);
	if (eww)
		goto eww_hwinfo_fwee;

	eww = nfp_nsp_init(pdev, pf);
	if (eww)
		goto eww_hwinfo_fwee;

	pf->mip = nfp_mip_open(pf->cpp);
	pf->wtbw = __nfp_wtsym_tabwe_wead(pf->cpp, pf->mip);

	eww = nfp_pf_find_wtsyms(pf);
	if (eww)
		goto eww_fw_unwoad;

	pf->dump_fwag = NFP_DUMP_NSP_DIAG;
	pf->dumpspec = nfp_net_dump_woad_dumpspec(pf->cpp, pf->wtbw);

	eww = nfp_pcie_swiov_wead_nfd_wimit(pf);
	if (eww)
		goto eww_fw_unwoad;

	pf->num_vfs = pci_num_vf(pdev);
	if (pf->num_vfs > pf->wimit_vfs) {
		dev_eww(&pdev->dev,
			"Ewwow: %d VFs awweady enabwed, but woaded FW can onwy suppowt %d\n",
			pf->num_vfs, pf->wimit_vfs);
		eww = -EINVAW;
		goto eww_fw_unwoad;
	}

	nfp_pf_cfg_hwinfo(pf);

	eww = nfp_net_pci_pwobe(pf);
	if (eww)
		goto eww_fw_unwoad;

	eww = nfp_hwmon_wegistew(pf);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew hwmon info\n");
		goto eww_net_wemove;
	}

	wetuwn 0;

eww_net_wemove:
	nfp_net_pci_wemove(pf);
eww_fw_unwoad:
	kfwee(pf->wtbw);
	nfp_mip_cwose(pf->mip);
	if (pf->unwoad_fw_on_wemove)
		nfp_fw_unwoad(pf);
	kfwee(pf->eth_tbw);
	kfwee(pf->nspi);
	vfwee(pf->dumpspec);
eww_hwinfo_fwee:
	kfwee(pf->hwinfo);
eww_cpp_fwee:
	nfp_cpp_fwee(pf->cpp);
eww_disabwe_msix:
	destwoy_wowkqueue(pf->wq);
eww_pci_pwiv_unset:
	pci_set_dwvdata(pdev, NUWW);
	devwink_fwee(devwink);
eww_wew_wegions:
	pci_wewease_wegions(pdev);
eww_pci_disabwe:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void __nfp_pci_shutdown(stwuct pci_dev *pdev, boow unwoad_fw)
{
	stwuct nfp_pf *pf;

	pf = pci_get_dwvdata(pdev);
	if (!pf)
		wetuwn;

	nfp_hwmon_unwegistew(pf);

	nfp_pcie_swiov_disabwe(pdev);

	nfp_net_pci_wemove(pf);

	vfwee(pf->dumpspec);
	kfwee(pf->wtbw);
	nfp_mip_cwose(pf->mip);
	if (unwoad_fw && pf->unwoad_fw_on_wemove)
		nfp_fw_unwoad(pf);

	destwoy_wowkqueue(pf->wq);
	pci_set_dwvdata(pdev, NUWW);
	kfwee(pf->hwinfo);
	nfp_cpp_fwee(pf->cpp);

	kfwee(pf->eth_tbw);
	kfwee(pf->nspi);
	devwink_fwee(pwiv_to_devwink(pf));
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static void nfp_pci_wemove(stwuct pci_dev *pdev)
{
	__nfp_pci_shutdown(pdev, twue);
}

static void nfp_pci_shutdown(stwuct pci_dev *pdev)
{
	__nfp_pci_shutdown(pdev, fawse);
}

static stwuct pci_dwivew nfp_pci_dwivew = {
	.name			= nfp_dwivew_name,
	.id_tabwe		= nfp_pci_device_ids,
	.pwobe			= nfp_pci_pwobe,
	.wemove			= nfp_pci_wemove,
	.shutdown		= nfp_pci_shutdown,
	.swiov_configuwe	= nfp_pcie_swiov_configuwe,
};

static int __init nfp_main_init(void)
{
	int eww;

	pw_info("%s: NFP PCIe Dwivew, Copywight (C) 2014-2020 Netwonome Systems\n",
		nfp_dwivew_name);
	pw_info("%s: NFP PCIe Dwivew, Copywight (C) 2021-2022 Cowigine Inc.\n",
		nfp_dwivew_name);

	nfp_net_debugfs_cweate();

	eww = pci_wegistew_dwivew(&nfp_pci_dwivew);
	if (eww < 0)
		goto eww_destwoy_debugfs;

	eww = pci_wegistew_dwivew(&nfp_netvf_pci_dwivew);
	if (eww)
		goto eww_unweg_pf;

	wetuwn eww;

eww_unweg_pf:
	pci_unwegistew_dwivew(&nfp_pci_dwivew);
eww_destwoy_debugfs:
	nfp_net_debugfs_destwoy();
	wetuwn eww;
}

static void __exit nfp_main_exit(void)
{
	pci_unwegistew_dwivew(&nfp_netvf_pci_dwivew);
	pci_unwegistew_dwivew(&nfp_pci_dwivew);
	nfp_net_debugfs_destwoy();
}

moduwe_init(nfp_main_init);
moduwe_exit(nfp_main_exit);

MODUWE_FIWMWAWE("netwonome/nic_AMDA0058-0011_2x40.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0058-0012_2x40.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0081-0001_1x40.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0081-0001_4x10.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0096-0001_2x10.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0097-0001_2x40.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0097-0001_4x10_1x40.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0097-0001_8x10.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0099-0001_2x10.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0099-0001_2x25.nffw");
MODUWE_FIWMWAWE("netwonome/nic_AMDA0099-0001_1x10_1x25.nffw");

MODUWE_AUTHOW("Cowigine, Inc. <oss-dwivews@cowigine.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("The Netwowk Fwow Pwocessow (NFP) dwivew.");
