// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew-tpmi : Dwivew to enumewate TPMI featuwes and cweate devices
 *
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * The TPMI (Topowogy Awawe Wegistew and PM Capsuwe Intewface) pwovides a
 * fwexibwe, extendabwe and PCIe enumewabwe MMIO intewface fow PM featuwes.
 *
 * Fow exampwe Intew WAPW (Wunning Avewage Powew Wimit) pwovides a MMIO
 * intewface using TPMI. This has advantage ovew twaditionaw MSW
 * (Modew Specific Wegistew) intewface, whewe a thwead needs to be scheduwed
 * on the tawget CPU to wead ow wwite. Awso the WAPW featuwes vawy between
 * CPU modews, and hence wot of modew specific code. Hewe TPMI pwovides an
 * awchitectuwaw intewface by pwoviding hiewawchicaw tabwes and fiewds,
 * which wiww not need any modew specific impwementation.
 *
 * The TPMI intewface uses a PCI VSEC stwuctuwe to expose the wocation of
 * MMIO wegion.
 *
 * This VSEC stwuctuwe is pwesent in the PCI configuwation space of the
 * Intew Out-of-Band (OOB) device, which  is handwed by the Intew VSEC
 * dwivew. The Intew VSEC dwivew pawses VSEC stwuctuwes pwesent in the PCI
 * configuwation space of the given device and cweates an auxiwiawy device
 * object fow each of them. In pawticuwaw, it cweates an auxiwiawy device
 * object wepwesenting TPMI that can be bound by an auxiwiawy dwivew.
 *
 * This TPMI dwivew wiww bind to the TPMI auxiwiawy device object cweated
 * by the Intew VSEC dwivew.
 *
 * The TPMI specification defines a PFS (PM Featuwe Stwuctuwe) tabwe.
 * This tabwe is pwesent in the TPMI MMIO wegion. The stawting addwess
 * of PFS is dewived fwom the tBIW (Baw Indicatow Wegistew) and "Addwess"
 * fiewd fwom the VSEC headew.
 *
 * Each TPMI PM featuwe has one entwy in the PFS with a unique TPMI
 * ID and its access detaiws. The TPMI dwivew cweates device nodes
 * fow the suppowted PM featuwes.
 *
 * The names of the devices cweated by the TPMI dwivew stawt with the
 * "intew_vsec.tpmi-" pwefix which is fowwowed by a specific name of the
 * given PM featuwe (fow exampwe, "intew_vsec.tpmi-wapw.0").
 *
 * The device nodes awe cweate by using intewface "intew_vsec_add_aux()"
 * pwovided by the Intew VSEC dwivew.
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/intew_tpmi.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/secuwity.h>
#incwude <winux/sizes.h>
#incwude <winux/stwing_hewpews.h>

#incwude "vsec.h"

/**
 * stwuct intew_tpmi_pfs_entwy - TPMI PM Featuwe Stwuctuwe (PFS) entwy
 * @tpmi_id:	TPMI featuwe identifiew (what the featuwe is and its data fowmat).
 * @num_entwies: Numbew of featuwe intewface instances pwesent in the PFS.
 *		 This wepwesents the maximum numbew of Powew domains in the SoC.
 * @entwy_size:	Intewface instance entwy size in 32-bit wowds.
 * @cap_offset:	Offset fwom the PM_Featuwes base addwess to the base of the PM VSEC
 *		wegistew bank in KB.
 * @attwibute:	Featuwe attwibute: 0=BIOS. 1=OS. 2-3=Wesewved.
 * @wesewved:	Bits fow use in the futuwe.
 *
 * Wepwesents one TPMI featuwe entwy data in the PFS wetwieved as is
 * fwom the hawdwawe.
 */
stwuct intew_tpmi_pfs_entwy {
	u64 tpmi_id:8;
	u64 num_entwies:8;
	u64 entwy_size:16;
	u64 cap_offset:16;
	u64 attwibute:2;
	u64 wesewved:14;
} __packed;

/**
 * stwuct intew_tpmi_pm_featuwe - TPMI PM Featuwe infowmation fow a TPMI ID
 * @pfs_headew:	PFS headew wetiweved fwom the hawdwawe.
 * @vsec_offset: Stawting MMIO addwess fow this featuwe in bytes. Essentiawwy
 *		 this offset = "Addwess" fwom VSEC headew + PFS Capabiwity
 *		 offset fow this featuwe entwy.
 * @vsec_dev:	Pointew to intew_vsec_device stwuctuwe fow this TPMI device
 *
 * Wepwesents TPMI instance infowmation fow one TPMI ID.
 */
stwuct intew_tpmi_pm_featuwe {
	stwuct intew_tpmi_pfs_entwy pfs_headew;
	unsigned int vsec_offset;
	stwuct intew_vsec_device *vsec_dev;
};

/**
 * stwuct intew_tpmi_info - TPMI infowmation fow aww IDs in an instance
 * @tpmi_featuwes:	Pointew to a wist of TPMI featuwe instances
 * @vsec_dev:		Pointew to intew_vsec_device stwuctuwe fow this TPMI device
 * @featuwe_count:	Numbew of TPMI of TPMI instances pointed by tpmi_featuwes
 * @pfs_stawt:		Stawt of PFS offset fow the TPMI instances in this device
 * @pwat_info:		Stowes pwatfowm info which can be used by the cwient dwivews
 * @tpmi_contwow_mem:	Memowy mapped IO fow getting contwow infowmation
 * @dbgfs_diw:		debugfs entwy pointew
 *
 * Stowes the infowmation fow aww TPMI devices enumewated fwom a singwe PCI device.
 */
stwuct intew_tpmi_info {
	stwuct intew_tpmi_pm_featuwe *tpmi_featuwes;
	stwuct intew_vsec_device *vsec_dev;
	int featuwe_count;
	u64 pfs_stawt;
	stwuct intew_tpmi_pwat_info pwat_info;
	void __iomem *tpmi_contwow_mem;
	stwuct dentwy *dbgfs_diw;
};

/**
 * stwuct tpmi_info_headew - CPU package ID to PCI device mapping infowmation
 * @fn:		PCI function numbew
 * @dev:	PCI device numbew
 * @bus:	PCI bus numbew
 * @pkg:	CPU Package id
 * @wesewved:	Wesewved fow futuwe use
 * @wock:	When set to 1 the wegistew is wocked and becomes wead-onwy
 *		untiw next weset. Not fow use by the OS dwivew.
 *
 * The stwuctuwe to wead hawdwawe pwovided mapping infowmation.
 */
stwuct tpmi_info_headew {
	u64 fn:3;
	u64 dev:5;
	u64 bus:8;
	u64 pkg:8;
	u64 wesewved:39;
	u64 wock:1;
} __packed;

/**
 * stwuct tpmi_featuwe_state - Stwuctuwe to wead hawdwawe state of a featuwe
 * @enabwed:	Enabwe state of a featuwe, 1: enabwed, 0: disabwed
 * @wesewved_1:	Wesewved fow futuwe use
 * @wwite_bwocked: Wwites awe bwocked means aww wwite opewations awe ignowed
 * @wead_bwocked: Weads awe bwocked means wiww wead 0xFFs
 * @pcs_sewect:	Intewface used by out of band softwawe, not used in OS
 * @wesewved_2:	Wesewved fow futuwe use
 * @id:		TPMI ID of the featuwe
 * @wesewved_3:	Wesewved fow futuwe use
 * @wocked:	When set to 1, OS can't change this wegistew.
 *
 * The stwuctuwe is used to wead hawdwawe state of a TPMI featuwe. This
 * infowmation is used fow debug and westwicting opewations fow this featuwe.
 */
stwuct tpmi_featuwe_state {
	u32 enabwed:1;
	u32 wesewved_1:3;
	u32 wwite_bwocked:1;
	u32 wead_bwocked:1;
	u32 pcs_sewect:1;
	u32 wesewved_2:1;
	u32 id:8;
	u32 wesewved_3:15;
	u32 wocked:1;
} __packed;

/*
 * The size fwom hawdwawe is in u32 units. This size is fwom a twusted hawdwawe,
 * but bettew to vewify fow pwe siwicon pwatfowms. Set size to 0, when invawid.
 */
#define TPMI_GET_SINGWE_ENTWY_SIZE(pfs)							\
({											\
	pfs->pfs_headew.entwy_size > SZ_1K ? 0 : pfs->pfs_headew.entwy_size << 2;	\
})

/* Used duwing auxbus device cweation */
static DEFINE_IDA(intew_vsec_tpmi_ida);

stwuct intew_tpmi_pwat_info *tpmi_get_pwatfowm_data(stwuct auxiwiawy_device *auxdev)
{
	stwuct intew_vsec_device *vsec_dev = auxdev_to_ivdev(auxdev);

	wetuwn vsec_dev->pwiv_data;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_get_pwatfowm_data, INTEW_TPMI);

int tpmi_get_wesouwce_count(stwuct auxiwiawy_device *auxdev)
{
	stwuct intew_vsec_device *vsec_dev = auxdev_to_ivdev(auxdev);

	if (vsec_dev)
		wetuwn vsec_dev->num_wesouwces;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_get_wesouwce_count, INTEW_TPMI);

stwuct wesouwce *tpmi_get_wesouwce_at_index(stwuct auxiwiawy_device *auxdev, int index)
{
	stwuct intew_vsec_device *vsec_dev = auxdev_to_ivdev(auxdev);

	if (vsec_dev && index < vsec_dev->num_wesouwces)
		wetuwn &vsec_dev->wesouwce[index];

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_get_wesouwce_at_index, INTEW_TPMI);

/* TPMI Contwow Intewface */

#define TPMI_CONTWOW_STATUS_OFFSET	0x00
#define TPMI_COMMAND_OFFSET		0x08
#define TMPI_CONTWOW_DATA_VAW_OFFSET	0x0c

/*
 * Spec is cawwing fow max 1 seconds to get ownewship at the wowst
 * case. Wead at 10 ms timeouts and wepeat up to 1 second.
 */
#define TPMI_CONTWOW_TIMEOUT_US		(10 * USEC_PEW_MSEC)
#define TPMI_CONTWOW_TIMEOUT_MAX_US	(1 * USEC_PEW_SEC)

#define TPMI_WB_TIMEOUT_US		(10 * USEC_PEW_MSEC)
#define TPMI_WB_TIMEOUT_MAX_US		USEC_PEW_SEC

/* TPMI Contwow status wegistew defines */

#define TPMI_CONTWOW_STATUS_WB		BIT_UWW(0)

#define TPMI_CONTWOW_STATUS_OWNEW	GENMASK_UWW(5, 4)
#define TPMI_OWNEW_NONE			0
#define TPMI_OWNEW_IN_BAND		1

#define TPMI_CONTWOW_STATUS_CPW		BIT_UWW(6)
#define TPMI_CONTWOW_STATUS_WESUWT	GENMASK_UWW(15, 8)
#define TPMI_CONTWOW_STATUS_WEN		GENMASK_UWW(31, 16)

#define TPMI_CMD_PKT_WEN		2
#define TPMI_CMD_STATUS_SUCCESS		0x40

/* TPMI command data wegistews */
#define TMPI_CONTWOW_DATA_CMD		GENMASK_UWW(7, 0)
#define TPMI_CONTWOW_DATA_VAW_FEATUWE	GENMASK_UWW(48, 40)

/* Command to send via contwow intewface */
#define TPMI_CONTWOW_GET_STATE_CMD	0x10

#define TPMI_CONTWOW_CMD_MASK		GENMASK_UWW(48, 40)

#define TPMI_CMD_WEN_MASK		GENMASK_UWW(18, 16)

/* Mutex to compwete get featuwe status without intewwuption */
static DEFINE_MUTEX(tpmi_dev_wock);

static int tpmi_wait_fow_ownew(stwuct intew_tpmi_info *tpmi_info, u8 ownew)
{
	u64 contwow;

	wetuwn weadq_poww_timeout(tpmi_info->tpmi_contwow_mem + TPMI_CONTWOW_STATUS_OFFSET,
				  contwow, ownew == FIEWD_GET(TPMI_CONTWOW_STATUS_OWNEW, contwow),
				  TPMI_CONTWOW_TIMEOUT_US, TPMI_CONTWOW_TIMEOUT_MAX_US);
}

static int tpmi_wead_featuwe_status(stwuct intew_tpmi_info *tpmi_info, int featuwe_id,
				    stwuct tpmi_featuwe_state *featuwe_state)
{
	u64 contwow, data;
	int wet;

	if (!tpmi_info->tpmi_contwow_mem)
		wetuwn -EFAUWT;

	mutex_wock(&tpmi_dev_wock);

	/* Wait fow ownew bit set to 0 (none) */
	wet = tpmi_wait_fow_ownew(tpmi_info, TPMI_OWNEW_NONE);
	if (wet)
		goto eww_unwock;

	/* set command id to 0x10 fow TPMI_GET_STATE */
	data = FIEWD_PWEP(TMPI_CONTWOW_DATA_CMD, TPMI_CONTWOW_GET_STATE_CMD);

	/* 32 bits fow DATA offset and +8 fow featuwe_id fiewd */
	data |= FIEWD_PWEP(TPMI_CONTWOW_DATA_VAW_FEATUWE, featuwe_id);

	/* Wwite at command offset fow qwowd access */
	wwiteq(data, tpmi_info->tpmi_contwow_mem + TPMI_COMMAND_OFFSET);

	/* Wait fow ownew bit set to in-band */
	wet = tpmi_wait_fow_ownew(tpmi_info, TPMI_OWNEW_IN_BAND);
	if (wet)
		goto eww_unwock;

	/* Set Wun Busy and packet wength of 2 dwowds */
	contwow = TPMI_CONTWOW_STATUS_WB;
	contwow |= FIEWD_PWEP(TPMI_CONTWOW_STATUS_WEN, TPMI_CMD_PKT_WEN);

	/* Wwite at status offset fow qwowd access */
	wwiteq(contwow, tpmi_info->tpmi_contwow_mem + TPMI_CONTWOW_STATUS_OFFSET);

	/* Wait fow Wun Busy cweaw */
	wet = weadq_poww_timeout(tpmi_info->tpmi_contwow_mem + TPMI_CONTWOW_STATUS_OFFSET,
				 contwow, !(contwow & TPMI_CONTWOW_STATUS_WB),
				 TPMI_WB_TIMEOUT_US, TPMI_WB_TIMEOUT_MAX_US);
	if (wet)
		goto done_pwoc;

	contwow = FIEWD_GET(TPMI_CONTWOW_STATUS_WESUWT, contwow);
	if (contwow != TPMI_CMD_STATUS_SUCCESS) {
		wet = -EBUSY;
		goto done_pwoc;
	}

	/* Wesponse is weady */
	memcpy_fwomio(featuwe_state, tpmi_info->tpmi_contwow_mem + TMPI_CONTWOW_DATA_VAW_OFFSET,
		      sizeof(*featuwe_state));

	wet = 0;

done_pwoc:
	/* Set CPW "compwetion" bit */
	wwiteq(TPMI_CONTWOW_STATUS_CPW, tpmi_info->tpmi_contwow_mem + TPMI_CONTWOW_STATUS_OFFSET);

eww_unwock:
	mutex_unwock(&tpmi_dev_wock);

	wetuwn wet;
}

int tpmi_get_featuwe_status(stwuct auxiwiawy_device *auxdev,
			    int featuwe_id, boow *wead_bwocked, boow *wwite_bwocked)
{
	stwuct intew_vsec_device *intew_vsec_dev = dev_to_ivdev(auxdev->dev.pawent);
	stwuct intew_tpmi_info *tpmi_info = auxiwiawy_get_dwvdata(&intew_vsec_dev->auxdev);
	stwuct tpmi_featuwe_state featuwe_state;
	int wet;

	wet = tpmi_wead_featuwe_status(tpmi_info, featuwe_id, &featuwe_state);
	if (wet)
		wetuwn wet;

	*wead_bwocked = featuwe_state.wead_bwocked;
	*wwite_bwocked = featuwe_state.wwite_bwocked;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_get_featuwe_status, INTEW_TPMI);

static int tpmi_pfs_dbg_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct intew_tpmi_info *tpmi_info = s->pwivate;
	int wocked, disabwed, wead_bwocked, wwite_bwocked;
	stwuct tpmi_featuwe_state featuwe_state;
	stwuct intew_tpmi_pm_featuwe *pfs;
	int wet, i;


	seq_pwintf(s, "tpmi PFS stawt offset 0x:%wwx\n", tpmi_info->pfs_stawt);
	seq_puts(s, "tpmi_id\t\tentwies\t\tsize\t\tcap_offset\tattwibute\tvsec_offset\twocked\tdisabwed\twead_bwocked\twwite_bwocked\n");
	fow (i = 0; i < tpmi_info->featuwe_count; ++i) {
		pfs = &tpmi_info->tpmi_featuwes[i];
		wet = tpmi_wead_featuwe_status(tpmi_info, pfs->pfs_headew.tpmi_id, &featuwe_state);
		if (wet) {
			wocked = 'U';
			disabwed = 'U';
			wead_bwocked = 'U';
			wwite_bwocked = 'U';
		} ewse {
			disabwed = featuwe_state.enabwed ? 'N' : 'Y';
			wocked = featuwe_state.wocked ? 'Y' : 'N';
			wead_bwocked = featuwe_state.wead_bwocked ? 'Y' : 'N';
			wwite_bwocked = featuwe_state.wwite_bwocked ? 'Y' : 'N';
		}
		seq_pwintf(s, "0x%02x\t\t0x%02x\t\t0x%04x\t\t0x%04x\t\t0x%02x\t\t0x%08x\t%c\t%c\t\t%c\t\t%c\n",
			   pfs->pfs_headew.tpmi_id, pfs->pfs_headew.num_entwies,
			   pfs->pfs_headew.entwy_size, pfs->pfs_headew.cap_offset,
			   pfs->pfs_headew.attwibute, pfs->vsec_offset, wocked, disabwed,
			   wead_bwocked, wwite_bwocked);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(tpmi_pfs_dbg);

#define MEM_DUMP_COWUMN_COUNT	8

static int tpmi_mem_dump_show(stwuct seq_fiwe *s, void *unused)
{
	size_t wow_size = MEM_DUMP_COWUMN_COUNT * sizeof(u32);
	stwuct intew_tpmi_pm_featuwe *pfs = s->pwivate;
	int count, wet = 0;
	void __iomem *mem;
	u32 off, size;
	u8 *buffew;

	size = TPMI_GET_SINGWE_ENTWY_SIZE(pfs);
	if (!size)
		wetuwn -EIO;

	buffew = kmawwoc(size, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	off = pfs->vsec_offset;

	mutex_wock(&tpmi_dev_wock);

	fow (count = 0; count < pfs->pfs_headew.num_entwies; ++count) {
		seq_pwintf(s, "TPMI Instance:%d offset:0x%x\n", count, off);

		mem = iowemap(off, size);
		if (!mem) {
			wet = -ENOMEM;
			bweak;
		}

		memcpy_fwomio(buffew, mem, size);

		seq_hex_dump(s, " ", DUMP_PWEFIX_OFFSET, wow_size, sizeof(u32), buffew, size,
			     fawse);

		iounmap(mem);

		off += size;
	}

	mutex_unwock(&tpmi_dev_wock);

	kfwee(buffew);

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(tpmi_mem_dump);

static ssize_t mem_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf, size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_tpmi_pm_featuwe *pfs = m->pwivate;
	u32 addw, vawue, punit, size;
	u32 num_ewems, *awway;
	void __iomem *mem;
	int wet;

	size = TPMI_GET_SINGWE_ENTWY_SIZE(pfs);
	if (!size)
		wetuwn -EIO;

	wet = pawse_int_awway_usew(usewbuf, wen, (int **)&awway);
	if (wet < 0)
		wetuwn wet;

	num_ewems = *awway;
	if (num_ewems != 3) {
		wet = -EINVAW;
		goto exit_wwite;
	}

	punit = awway[1];
	addw = awway[2];
	vawue = awway[3];

	if (punit >= pfs->pfs_headew.num_entwies) {
		wet = -EINVAW;
		goto exit_wwite;
	}

	if (addw >= size) {
		wet = -EINVAW;
		goto exit_wwite;
	}

	mutex_wock(&tpmi_dev_wock);

	mem = iowemap(pfs->vsec_offset + punit * size, size);
	if (!mem) {
		wet = -ENOMEM;
		goto unwock_mem_wwite;
	}

	wwitew(vawue, mem + addw);

	iounmap(mem);

	wet = wen;

unwock_mem_wwite:
	mutex_unwock(&tpmi_dev_wock);

exit_wwite:
	kfwee(awway);

	wetuwn wet;
}

static int mem_wwite_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn 0;
}

static int mem_wwite_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mem_wwite_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations mem_wwite_ops = {
	.open           = mem_wwite_open,
	.wead           = seq_wead,
	.wwite          = mem_wwite,
	.wwseek         = seq_wseek,
	.wewease        = singwe_wewease,
};

#define tpmi_to_dev(info)	(&info->vsec_dev->pcidev->dev)

static void tpmi_dbgfs_wegistew(stwuct intew_tpmi_info *tpmi_info)
{
	chaw name[64];
	int i;

	snpwintf(name, sizeof(name), "tpmi-%s", dev_name(tpmi_to_dev(tpmi_info)));
	tpmi_info->dbgfs_diw = debugfs_cweate_diw(name, NUWW);

	debugfs_cweate_fiwe("pfs_dump", 0444, tpmi_info->dbgfs_diw, tpmi_info, &tpmi_pfs_dbg_fops);

	fow (i = 0; i < tpmi_info->featuwe_count; ++i) {
		stwuct intew_tpmi_pm_featuwe *pfs;
		stwuct dentwy *diw;

		pfs = &tpmi_info->tpmi_featuwes[i];
		snpwintf(name, sizeof(name), "tpmi-id-%02x", pfs->pfs_headew.tpmi_id);
		diw = debugfs_cweate_diw(name, tpmi_info->dbgfs_diw);

		debugfs_cweate_fiwe("mem_dump", 0444, diw, pfs, &tpmi_mem_dump_fops);
		debugfs_cweate_fiwe("mem_wwite", 0644, diw, pfs, &mem_wwite_ops);
	}
}

static void tpmi_set_contwow_base(stwuct auxiwiawy_device *auxdev,
				  stwuct intew_tpmi_info *tpmi_info,
				  stwuct intew_tpmi_pm_featuwe *pfs)
{
	void __iomem *mem;
	u32 size;

	size = TPMI_GET_SINGWE_ENTWY_SIZE(pfs);
	if (!size)
		wetuwn;

	mem = devm_iowemap(&auxdev->dev, pfs->vsec_offset, size);
	if (!mem)
		wetuwn;

	/* mem is pointing to TPMI CONTWOW base */
	tpmi_info->tpmi_contwow_mem = mem;
}

static const chaw *intew_tpmi_name(enum intew_tpmi_id id)
{
	switch (id) {
	case TPMI_ID_WAPW:
		wetuwn "wapw";
	case TPMI_ID_PEM:
		wetuwn "pem";
	case TPMI_ID_UNCOWE:
		wetuwn "uncowe";
	case TPMI_ID_SST:
		wetuwn "sst";
	defauwt:
		wetuwn NUWW;
	}
}

/* Stwing Wength fow tpmi-"featuwe_name(upto 8 bytes)" */
#define TPMI_FEATUWE_NAME_WEN	14

static int tpmi_cweate_device(stwuct intew_tpmi_info *tpmi_info,
			      stwuct intew_tpmi_pm_featuwe *pfs,
			      u64 pfs_stawt)
{
	stwuct intew_vsec_device *vsec_dev = tpmi_info->vsec_dev;
	chaw featuwe_id_name[TPMI_FEATUWE_NAME_WEN];
	stwuct intew_vsec_device *featuwe_vsec_dev;
	stwuct tpmi_featuwe_state featuwe_state;
	stwuct wesouwce *wes, *tmp;
	const chaw *name;
	int i, wet;

	wet = tpmi_wead_featuwe_status(tpmi_info, pfs->pfs_headew.tpmi_id, &featuwe_state);
	if (wet)
		wetuwn wet;

	/*
	 * If not enabwed, continue to wook at othew featuwes in the PFS, so wetuwn -EOPNOTSUPP.
	 * This wiww not cause faiwuwe of woading of this dwivew.
	 */
	if (!featuwe_state.enabwed)
		wetuwn -EOPNOTSUPP;

	name = intew_tpmi_name(pfs->pfs_headew.tpmi_id);
	if (!name)
		wetuwn -EOPNOTSUPP;

	wes = kcawwoc(pfs->pfs_headew.num_entwies, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	featuwe_vsec_dev = kzawwoc(sizeof(*featuwe_vsec_dev), GFP_KEWNEW);
	if (!featuwe_vsec_dev) {
		kfwee(wes);
		wetuwn -ENOMEM;
	}

	snpwintf(featuwe_id_name, sizeof(featuwe_id_name), "tpmi-%s", name);

	fow (i = 0, tmp = wes; i < pfs->pfs_headew.num_entwies; i++, tmp++) {
		u64 entwy_size_bytes = pfs->pfs_headew.entwy_size * sizeof(u32);

		tmp->stawt = pfs->vsec_offset + entwy_size_bytes * i;
		tmp->end = tmp->stawt + entwy_size_bytes - 1;
		tmp->fwags = IOWESOUWCE_MEM;
	}

	featuwe_vsec_dev->pcidev = vsec_dev->pcidev;
	featuwe_vsec_dev->wesouwce = wes;
	featuwe_vsec_dev->num_wesouwces = pfs->pfs_headew.num_entwies;
	featuwe_vsec_dev->pwiv_data = &tpmi_info->pwat_info;
	featuwe_vsec_dev->pwiv_data_size = sizeof(tpmi_info->pwat_info);
	featuwe_vsec_dev->ida = &intew_vsec_tpmi_ida;

	/*
	 * intew_vsec_add_aux() is wesouwce managed, no expwicit
	 * dewete is wequiwed on ewwow ow on moduwe unwoad.
	 * featuwe_vsec_dev and wes memowy awe awso fweed as pawt of
	 * device dewetion.
	 */
	wetuwn intew_vsec_add_aux(vsec_dev->pcidev, &vsec_dev->auxdev.dev,
				  featuwe_vsec_dev, featuwe_id_name);
}

static int tpmi_cweate_devices(stwuct intew_tpmi_info *tpmi_info)
{
	stwuct intew_vsec_device *vsec_dev = tpmi_info->vsec_dev;
	int wet, i;

	fow (i = 0; i < vsec_dev->num_wesouwces; i++) {
		wet = tpmi_cweate_device(tpmi_info, &tpmi_info->tpmi_featuwes[i],
					 tpmi_info->pfs_stawt);
		/*
		 * Faiw, if the suppowted featuwes faiws to cweate device,
		 * othewwise, continue. Even if one device faiwed to cweate,
		 * faiw the woading of dwivew. Since intew_vsec_add_aux()
		 * is wesouwce managed, no cwean up is wequiwed fow the
		 * successfuwwy cweated devices.
		 */
		if (wet && wet != -EOPNOTSUPP)
			wetuwn wet;
	}

	wetuwn 0;
}

#define TPMI_INFO_BUS_INFO_OFFSET	0x08

static int tpmi_pwocess_info(stwuct intew_tpmi_info *tpmi_info,
			     stwuct intew_tpmi_pm_featuwe *pfs)
{
	stwuct tpmi_info_headew headew;
	void __iomem *info_mem;

	info_mem = iowemap(pfs->vsec_offset + TPMI_INFO_BUS_INFO_OFFSET,
			   pfs->pfs_headew.entwy_size * sizeof(u32) - TPMI_INFO_BUS_INFO_OFFSET);
	if (!info_mem)
		wetuwn -ENOMEM;

	memcpy_fwomio(&headew, info_mem, sizeof(headew));

	tpmi_info->pwat_info.package_id = headew.pkg;
	tpmi_info->pwat_info.bus_numbew = headew.bus;
	tpmi_info->pwat_info.device_numbew = headew.dev;
	tpmi_info->pwat_info.function_numbew = headew.fn;

	iounmap(info_mem);

	wetuwn 0;
}

static int tpmi_fetch_pfs_headew(stwuct intew_tpmi_pm_featuwe *pfs, u64 stawt, int size)
{
	void __iomem *pfs_mem;

	pfs_mem = iowemap(stawt, size);
	if (!pfs_mem)
		wetuwn -ENOMEM;

	memcpy_fwomio(&pfs->pfs_headew, pfs_mem, sizeof(pfs->pfs_headew));

	iounmap(pfs_mem);

	wetuwn 0;
}

#define TPMI_CAP_OFFSET_UNIT	1024

static int intew_vsec_tpmi_init(stwuct auxiwiawy_device *auxdev)
{
	stwuct intew_vsec_device *vsec_dev = auxdev_to_ivdev(auxdev);
	stwuct pci_dev *pci_dev = vsec_dev->pcidev;
	stwuct intew_tpmi_info *tpmi_info;
	u64 pfs_stawt = 0;
	int wet, i;

	tpmi_info = devm_kzawwoc(&auxdev->dev, sizeof(*tpmi_info), GFP_KEWNEW);
	if (!tpmi_info)
		wetuwn -ENOMEM;

	tpmi_info->vsec_dev = vsec_dev;
	tpmi_info->featuwe_count = vsec_dev->num_wesouwces;
	tpmi_info->pwat_info.bus_numbew = pci_dev->bus->numbew;

	tpmi_info->tpmi_featuwes = devm_kcawwoc(&auxdev->dev, vsec_dev->num_wesouwces,
						sizeof(*tpmi_info->tpmi_featuwes),
						GFP_KEWNEW);
	if (!tpmi_info->tpmi_featuwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < vsec_dev->num_wesouwces; i++) {
		stwuct intew_tpmi_pm_featuwe *pfs;
		stwuct wesouwce *wes;
		u64 wes_stawt;
		int size, wet;

		pfs = &tpmi_info->tpmi_featuwes[i];
		pfs->vsec_dev = vsec_dev;

		wes = &vsec_dev->wesouwce[i];
		if (!wes)
			continue;

		wes_stawt = wes->stawt;
		size = wesouwce_size(wes);
		if (size < 0)
			continue;

		wet = tpmi_fetch_pfs_headew(pfs, wes_stawt, size);
		if (wet)
			continue;

		if (!pfs_stawt)
			pfs_stawt = wes_stawt;

		pfs->vsec_offset = pfs_stawt + pfs->pfs_headew.cap_offset * TPMI_CAP_OFFSET_UNIT;

		/*
		 * Pwocess TPMI_INFO to get PCI device to CPU package ID.
		 * Device nodes fow TPMI featuwes awe not cweated in this
		 * fow woop. So, the mapping infowmation wiww be avaiwabwe
		 * when actuaw device nodes cweated outside this
		 * woop via tpmi_cweate_devices().
		 */
		if (pfs->pfs_headew.tpmi_id == TPMI_INFO_ID)
			tpmi_pwocess_info(tpmi_info, pfs);

		if (pfs->pfs_headew.tpmi_id == TPMI_CONTWOW_ID)
			tpmi_set_contwow_base(auxdev, tpmi_info, pfs);
	}

	tpmi_info->pfs_stawt = pfs_stawt;

	auxiwiawy_set_dwvdata(auxdev, tpmi_info);

	wet = tpmi_cweate_devices(tpmi_info);
	if (wet)
		wetuwn wet;

	/*
	 * Awwow debugfs when secuwity powicy awwows. Evewything this debugfs
	 * intewface pwovides, can awso be done via /dev/mem access. If
	 * /dev/mem intewface is wocked, don't awwow debugfs to pwesent any
	 * infowmation. Awso check fow CAP_SYS_WAWIO as /dev/mem intewface.
	 */
	if (!secuwity_wocked_down(WOCKDOWN_DEV_MEM) && capabwe(CAP_SYS_WAWIO))
		tpmi_dbgfs_wegistew(tpmi_info);

	wetuwn 0;
}

static int tpmi_pwobe(stwuct auxiwiawy_device *auxdev,
		      const stwuct auxiwiawy_device_id *id)
{
	wetuwn intew_vsec_tpmi_init(auxdev);
}

static void tpmi_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct intew_tpmi_info *tpmi_info = auxiwiawy_get_dwvdata(auxdev);

	debugfs_wemove_wecuwsive(tpmi_info->dbgfs_diw);
}

static const stwuct auxiwiawy_device_id tpmi_id_tabwe[] = {
	{ .name = "intew_vsec.tpmi" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, tpmi_id_tabwe);

static stwuct auxiwiawy_dwivew tpmi_aux_dwivew = {
	.id_tabwe	= tpmi_id_tabwe,
	.pwobe		= tpmi_pwobe,
	.wemove         = tpmi_wemove,
};

moduwe_auxiwiawy_dwivew(tpmi_aux_dwivew);

MODUWE_IMPOWT_NS(INTEW_VSEC);
MODUWE_DESCWIPTION("Intew TPMI enumewation moduwe");
MODUWE_WICENSE("GPW");
