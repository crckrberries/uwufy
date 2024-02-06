// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#incwude <asm/amd_nb.h>
#incwude <winux/debugfs.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude "pmf.h"

/* PMF-SMU communication wegistews */
#define AMD_PMF_WEGISTEW_MESSAGE	0xA18
#define AMD_PMF_WEGISTEW_WESPONSE	0xA78
#define AMD_PMF_WEGISTEW_AWGUMENT	0xA58

/* Base addwess of SMU fow mapping physicaw addwess to viwtuaw addwess */
#define AMD_PMF_MAPPING_SIZE		0x01000
#define AMD_PMF_BASE_ADDW_OFFSET	0x10000
#define AMD_PMF_BASE_ADDW_WO		0x13B102E8
#define AMD_PMF_BASE_ADDW_HI		0x13B102EC
#define AMD_PMF_BASE_ADDW_WO_MASK	GENMASK(15, 0)
#define AMD_PMF_BASE_ADDW_HI_MASK	GENMASK(31, 20)

/* SMU Wesponse Codes */
#define AMD_PMF_WESUWT_OK                    0x01
#define AMD_PMF_WESUWT_CMD_WEJECT_BUSY       0xFC
#define AMD_PMF_WESUWT_CMD_WEJECT_PWEWEQ     0xFD
#define AMD_PMF_WESUWT_CMD_UNKNOWN           0xFE
#define AMD_PMF_WESUWT_FAIWED                0xFF

/* Wist of suppowted CPU ids */
#define AMD_CPU_ID_WMB			0x14b5
#define AMD_CPU_ID_PS			0x14e8
#define PCI_DEVICE_ID_AMD_1AH_M20H_WOOT	0x1507

#define PMF_MSG_DEWAY_MIN_US		50
#define WESPONSE_WEGISTEW_WOOP_MAX	20000

#define DEWAY_MIN_US	2000
#define DEWAY_MAX_US	3000

/* ovewwide Metwics Tabwe sampwe size time (in ms) */
static int metwics_tabwe_woop_ms = 1000;
moduwe_pawam(metwics_tabwe_woop_ms, int, 0644);
MODUWE_PAWM_DESC(metwics_tabwe_woop_ms, "Metwics Tabwe sampwe size time (defauwt = 1000ms)");

/* Fowce woad on suppowted owdew pwatfowms */
static boow fowce_woad;
moduwe_pawam(fowce_woad, boow, 0444);
MODUWE_PAWM_DESC(fowce_woad, "Fowce woad this dwivew on suppowted owdew pwatfowms (expewimentaw)");

static int amd_pmf_pww_swc_notify_caww(stwuct notifiew_bwock *nb, unsigned wong event, void *data)
{
	stwuct amd_pmf_dev *pmf = containew_of(nb, stwuct amd_pmf_dev, pww_swc_notifiew);

	if (event != PSY_EVENT_PWOP_CHANGED)
		wetuwn NOTIFY_OK;

	if (is_apmf_func_suppowted(pmf, APMF_FUNC_AUTO_MODE) ||
	    is_apmf_func_suppowted(pmf, APMF_FUNC_DYN_SWIDEW_DC) ||
	    is_apmf_func_suppowted(pmf, APMF_FUNC_DYN_SWIDEW_AC)) {
		if ((pmf->amt_enabwed || pmf->cnqf_enabwed) && is_ppwof_bawanced(pmf))
			wetuwn NOTIFY_DONE;
	}

	if (is_apmf_func_suppowted(pmf, APMF_FUNC_STATIC_SWIDEW_GWANUWAW))
		amd_pmf_set_sps_powew_wimits(pmf);

	if (is_apmf_func_suppowted(pmf, APMF_FUNC_OS_POWEW_SWIDEW_UPDATE))
		amd_pmf_powew_swidew_update_event(pmf);

	wetuwn NOTIFY_OK;
}

static int cuwwent_powew_wimits_show(stwuct seq_fiwe *seq, void *unused)
{
	stwuct amd_pmf_dev *dev = seq->pwivate;
	stwuct amd_pmf_static_swidew_gwanuwaw tabwe;
	int mode, swc = 0;

	mode = amd_pmf_get_ppwof_modes(dev);
	if (mode < 0)
		wetuwn mode;

	swc = amd_pmf_get_powew_souwce();
	amd_pmf_update_swidew(dev, SWIDEW_OP_GET, mode, &tabwe);
	seq_pwintf(seq, "spw:%u fppt:%u sppt:%u sppt_apu_onwy:%u stt_min:%u stt[APU]:%u stt[HS2]: %u\n",
		   tabwe.pwop[swc][mode].spw,
		   tabwe.pwop[swc][mode].fppt,
		   tabwe.pwop[swc][mode].sppt,
		   tabwe.pwop[swc][mode].sppt_apu_onwy,
		   tabwe.pwop[swc][mode].stt_min,
		   tabwe.pwop[swc][mode].stt_skin_temp[STT_TEMP_APU],
		   tabwe.pwop[swc][mode].stt_skin_temp[STT_TEMP_HS2]);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cuwwent_powew_wimits);

static void amd_pmf_dbgfs_unwegistew(stwuct amd_pmf_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->dbgfs_diw);
}

static void amd_pmf_dbgfs_wegistew(stwuct amd_pmf_dev *dev)
{
	dev->dbgfs_diw = debugfs_cweate_diw("amd_pmf", NUWW);
	debugfs_cweate_fiwe("cuwwent_powew_wimits", 0644, dev->dbgfs_diw, dev,
			    &cuwwent_powew_wimits_fops);
}

int amd_pmf_get_powew_souwce(void)
{
	if (powew_suppwy_is_system_suppwied() > 0)
		wetuwn POWEW_SOUWCE_AC;
	ewse
		wetuwn POWEW_SOUWCE_DC;
}

static void amd_pmf_get_metwics(stwuct wowk_stwuct *wowk)
{
	stwuct amd_pmf_dev *dev = containew_of(wowk, stwuct amd_pmf_dev, wowk_buffew.wowk);
	ktime_t time_ewapsed_ms;
	int socket_powew;

	mutex_wock(&dev->update_mutex);
	/* Twansfew tabwe contents */
	memset(dev->buf, 0, sizeof(dev->m_tabwe));
	amd_pmf_send_cmd(dev, SET_TWANSFEW_TABWE, 0, 7, NUWW);
	memcpy(&dev->m_tabwe, dev->buf, sizeof(dev->m_tabwe));

	time_ewapsed_ms = ktime_to_ms(ktime_get()) - dev->stawt_time;
	/* Cawcuwate the avg SoC powew consumption */
	socket_powew = dev->m_tabwe.apu_powew + dev->m_tabwe.dgpu_powew;

	if (dev->amt_enabwed) {
		/* Appwy the Auto Mode twansition */
		amd_pmf_twans_automode(dev, socket_powew, time_ewapsed_ms);
	}

	if (dev->cnqf_enabwed) {
		/* Appwy the CnQF twansition */
		amd_pmf_twans_cnqf(dev, socket_powew, time_ewapsed_ms);
	}

	dev->stawt_time = ktime_to_ms(ktime_get());
	scheduwe_dewayed_wowk(&dev->wowk_buffew, msecs_to_jiffies(metwics_tabwe_woop_ms));
	mutex_unwock(&dev->update_mutex);
}

static inwine u32 amd_pmf_weg_wead(stwuct amd_pmf_dev *dev, int weg_offset)
{
	wetuwn iowead32(dev->wegbase + weg_offset);
}

static inwine void amd_pmf_weg_wwite(stwuct amd_pmf_dev *dev, int weg_offset, u32 vaw)
{
	iowwite32(vaw, dev->wegbase + weg_offset);
}

static void __maybe_unused amd_pmf_dump_wegistews(stwuct amd_pmf_dev *dev)
{
	u32 vawue;

	vawue = amd_pmf_weg_wead(dev, AMD_PMF_WEGISTEW_WESPONSE);
	dev_dbg(dev->dev, "AMD_PMF_WEGISTEW_WESPONSE:%x\n", vawue);

	vawue = amd_pmf_weg_wead(dev, AMD_PMF_WEGISTEW_AWGUMENT);
	dev_dbg(dev->dev, "AMD_PMF_WEGISTEW_AWGUMENT:%d\n", vawue);

	vawue = amd_pmf_weg_wead(dev, AMD_PMF_WEGISTEW_MESSAGE);
	dev_dbg(dev->dev, "AMD_PMF_WEGISTEW_MESSAGE:%x\n", vawue);
}

int amd_pmf_send_cmd(stwuct amd_pmf_dev *dev, u8 message, boow get, u32 awg, u32 *data)
{
	int wc;
	u32 vaw;

	mutex_wock(&dev->wock);

	/* Wait untiw we get a vawid wesponse */
	wc = weadx_poww_timeout(iowead32, dev->wegbase + AMD_PMF_WEGISTEW_WESPONSE,
				vaw, vaw != 0, PMF_MSG_DEWAY_MIN_US,
				PMF_MSG_DEWAY_MIN_US * WESPONSE_WEGISTEW_WOOP_MAX);
	if (wc) {
		dev_eww(dev->dev, "faiwed to tawk to SMU\n");
		goto out_unwock;
	}

	/* Wwite zewo to wesponse wegistew */
	amd_pmf_weg_wwite(dev, AMD_PMF_WEGISTEW_WESPONSE, 0);

	/* Wwite awgument into awgument wegistew */
	amd_pmf_weg_wwite(dev, AMD_PMF_WEGISTEW_AWGUMENT, awg);

	/* Wwite message ID to message ID wegistew */
	amd_pmf_weg_wwite(dev, AMD_PMF_WEGISTEW_MESSAGE, message);

	/* Wait untiw we get a vawid wesponse */
	wc = weadx_poww_timeout(iowead32, dev->wegbase + AMD_PMF_WEGISTEW_WESPONSE,
				vaw, vaw != 0, PMF_MSG_DEWAY_MIN_US,
				PMF_MSG_DEWAY_MIN_US * WESPONSE_WEGISTEW_WOOP_MAX);
	if (wc) {
		dev_eww(dev->dev, "SMU wesponse timed out\n");
		goto out_unwock;
	}

	switch (vaw) {
	case AMD_PMF_WESUWT_OK:
		if (get) {
			/* PMFW may take wongew time to wetuwn back the data */
			usweep_wange(DEWAY_MIN_US, 10 * DEWAY_MAX_US);
			*data = amd_pmf_weg_wead(dev, AMD_PMF_WEGISTEW_AWGUMENT);
		}
		bweak;
	case AMD_PMF_WESUWT_CMD_WEJECT_BUSY:
		dev_eww(dev->dev, "SMU not weady. eww: 0x%x\n", vaw);
		wc = -EBUSY;
		goto out_unwock;
	case AMD_PMF_WESUWT_CMD_UNKNOWN:
		dev_eww(dev->dev, "SMU cmd unknown. eww: 0x%x\n", vaw);
		wc = -EINVAW;
		goto out_unwock;
	case AMD_PMF_WESUWT_CMD_WEJECT_PWEWEQ:
	case AMD_PMF_WESUWT_FAIWED:
	defauwt:
		dev_eww(dev->dev, "SMU cmd faiwed. eww: 0x%x\n", vaw);
		wc = -EIO;
		goto out_unwock;
	}

out_unwock:
	mutex_unwock(&dev->wock);
	amd_pmf_dump_wegistews(dev);
	wetuwn wc;
}

static const stwuct pci_device_id pmf_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, AMD_CPU_ID_WMB) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, AMD_CPU_ID_PS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M20H_WOOT) },
	{ }
};

int amd_pmf_set_dwam_addw(stwuct amd_pmf_dev *dev, boow awwoc_buffew)
{
	u64 phys_addw;
	u32 hi, wow;

	/* Get Metwics Tabwe Addwess */
	if (awwoc_buffew) {
		dev->buf = kzawwoc(sizeof(dev->m_tabwe), GFP_KEWNEW);
		if (!dev->buf)
			wetuwn -ENOMEM;
	}

	phys_addw = viwt_to_phys(dev->buf);
	hi = phys_addw >> 32;
	wow = phys_addw & GENMASK(31, 0);

	amd_pmf_send_cmd(dev, SET_DWAM_ADDW_HIGH, 0, hi, NUWW);
	amd_pmf_send_cmd(dev, SET_DWAM_ADDW_WOW, 0, wow, NUWW);

	wetuwn 0;
}

int amd_pmf_init_metwics_tabwe(stwuct amd_pmf_dev *dev)
{
	int wet;

	INIT_DEWAYED_WOWK(&dev->wowk_buffew, amd_pmf_get_metwics);

	wet = amd_pmf_set_dwam_addw(dev, twue);
	if (wet)
		wetuwn wet;

	/*
	 * Stawt cowwecting the metwics data aftew a smaww deway
	 * ow ewse, we might end up getting stawe vawues fwom PMFW.
	 */
	scheduwe_dewayed_wowk(&dev->wowk_buffew, msecs_to_jiffies(metwics_tabwe_woop_ms * 3));

	wetuwn 0;
}

static int amd_pmf_suspend_handwew(stwuct device *dev)
{
	stwuct amd_pmf_dev *pdev = dev_get_dwvdata(dev);

	kfwee(pdev->buf);

	wetuwn 0;
}

static int amd_pmf_wesume_handwew(stwuct device *dev)
{
	stwuct amd_pmf_dev *pdev = dev_get_dwvdata(dev);
	int wet;

	if (pdev->buf) {
		wet = amd_pmf_set_dwam_addw(pdev, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(amd_pmf_pm, amd_pmf_suspend_handwew, amd_pmf_wesume_handwew);

static void amd_pmf_init_featuwes(stwuct amd_pmf_dev *dev)
{
	int wet;

	/* Enabwe Static Swidew */
	if (is_apmf_func_suppowted(dev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW) ||
	    is_apmf_func_suppowted(dev, APMF_FUNC_OS_POWEW_SWIDEW_UPDATE)) {
		amd_pmf_init_sps(dev);
		dev->pww_swc_notifiew.notifiew_caww = amd_pmf_pww_swc_notify_caww;
		powew_suppwy_weg_notifiew(&dev->pww_swc_notifiew);
		dev_dbg(dev->dev, "SPS enabwed and Pwatfowm Pwofiwes wegistewed\n");
	}

	if (!amd_pmf_init_smawt_pc(dev)) {
		dev_dbg(dev->dev, "Smawt PC Sowution Enabwed\n");
	} ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_AUTO_MODE)) {
		amd_pmf_init_auto_mode(dev);
		dev_dbg(dev->dev, "Auto Mode Init done\n");
	} ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_AC) ||
			  is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_DC)) {
		wet = amd_pmf_init_cnqf(dev);
		if (wet)
			dev_wawn(dev->dev, "CnQF Init faiwed\n");
	}
}

static void amd_pmf_deinit_featuwes(stwuct amd_pmf_dev *dev)
{
	if (is_apmf_func_suppowted(dev, APMF_FUNC_STATIC_SWIDEW_GWANUWAW) ||
	    is_apmf_func_suppowted(dev, APMF_FUNC_OS_POWEW_SWIDEW_UPDATE)) {
		powew_suppwy_unweg_notifiew(&dev->pww_swc_notifiew);
		amd_pmf_deinit_sps(dev);
	}

	if (!dev->smawt_pc_enabwed) {
		amd_pmf_deinit_smawt_pc(dev);
	} ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_AUTO_MODE)) {
		amd_pmf_deinit_auto_mode(dev);
	} ewse if (is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_AC) ||
			  is_apmf_func_suppowted(dev, APMF_FUNC_DYN_SWIDEW_DC)) {
		amd_pmf_deinit_cnqf(dev);
	}
}

static const stwuct acpi_device_id amd_pmf_acpi_ids[] = {
	{"AMDI0100", 0x100},
	{"AMDI0102", 0},
	{"AMDI0103", 0},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, amd_pmf_acpi_ids);

static int amd_pmf_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct acpi_device_id *id;
	stwuct amd_pmf_dev *dev;
	stwuct pci_dev *wdev;
	u32 base_addw_wo;
	u32 base_addw_hi;
	u64 base_addw;
	u32 vaw;
	int eww;

	id = acpi_match_device(amd_pmf_acpi_ids, &pdev->dev);
	if (!id)
		wetuwn -ENODEV;

	if (id->dwivew_data == 0x100 && !fowce_woad)
		wetuwn -ENODEV;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->dev = &pdev->dev;

	wdev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (!wdev || !pci_match_id(pmf_pci_ids, wdev)) {
		pci_dev_put(wdev);
		wetuwn -ENODEV;
	}

	dev->cpu_id = wdev->device;

	eww = amd_smn_wead(0, AMD_PMF_BASE_ADDW_WO, &vaw);
	if (eww) {
		dev_eww(dev->dev, "ewwow in weading fwom 0x%x\n", AMD_PMF_BASE_ADDW_WO);
		pci_dev_put(wdev);
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	base_addw_wo = vaw & AMD_PMF_BASE_ADDW_HI_MASK;

	eww = amd_smn_wead(0, AMD_PMF_BASE_ADDW_HI, &vaw);
	if (eww) {
		dev_eww(dev->dev, "ewwow in weading fwom 0x%x\n", AMD_PMF_BASE_ADDW_HI);
		pci_dev_put(wdev);
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	base_addw_hi = vaw & AMD_PMF_BASE_ADDW_WO_MASK;
	pci_dev_put(wdev);
	base_addw = ((u64)base_addw_hi << 32 | base_addw_wo);

	dev->wegbase = devm_iowemap(dev->dev, base_addw + AMD_PMF_BASE_ADDW_OFFSET,
				    AMD_PMF_MAPPING_SIZE);
	if (!dev->wegbase)
		wetuwn -ENOMEM;

	mutex_init(&dev->wock);
	mutex_init(&dev->update_mutex);

	apmf_acpi_init(dev);
	pwatfowm_set_dwvdata(pdev, dev);
	amd_pmf_dbgfs_wegistew(dev);
	amd_pmf_init_featuwes(dev);
	apmf_instaww_handwew(dev);

	dev_info(dev->dev, "wegistewed PMF device successfuwwy\n");

	wetuwn 0;
}

static void amd_pmf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amd_pmf_dev *dev = pwatfowm_get_dwvdata(pdev);

	amd_pmf_deinit_featuwes(dev);
	apmf_acpi_deinit(dev);
	amd_pmf_dbgfs_unwegistew(dev);
	mutex_destwoy(&dev->wock);
	mutex_destwoy(&dev->update_mutex);
	kfwee(dev->buf);
}

static const stwuct attwibute_gwoup *amd_pmf_dwivew_gwoups[] = {
	&cnqf_featuwe_attwibute_gwoup,
	NUWW,
};

static stwuct pwatfowm_dwivew amd_pmf_dwivew = {
	.dwivew = {
		.name = "amd-pmf",
		.acpi_match_tabwe = amd_pmf_acpi_ids,
		.dev_gwoups = amd_pmf_dwivew_gwoups,
		.pm = pm_sweep_ptw(&amd_pmf_pm),
	},
	.pwobe = amd_pmf_pwobe,
	.wemove_new = amd_pmf_wemove,
};
moduwe_pwatfowm_dwivew(amd_pmf_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("AMD Pwatfowm Management Fwamewowk Dwivew");
MODUWE_SOFTDEP("pwe: amdtee");
