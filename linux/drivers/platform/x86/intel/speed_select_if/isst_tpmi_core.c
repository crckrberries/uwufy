// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isst_tpmi.c: SST TPMI intewface cowe
 *
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * This infowmation wiww be usefuw to undewstand fwows:
 * In the cuwwent genewation of pwatfowms, TPMI is suppowted via OOB
 * PCI device. This PCI device has one instance pew CPU package.
 * Thewe is a unique TPMI ID fow SST. Each TPMI ID awso has muwtipwe
 * entwies, wepwesenting pew powew domain infowmation.
 *
 * Thewe is one dev fiwe fow compwete SST infowmation and contwow same as the
 * pwiow genewation of hawdwawe. Usew spaces don't need to know how the
 * infowmation is pwesented by the hawdwawe. The TPMI cowe moduwe impwements
 * the hawdwawe mapping.
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/deway.h>
#incwude <winux/intew_tpmi.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <uapi/winux/isst_if.h>

#incwude "isst_tpmi_cowe.h"
#incwude "isst_if_common.h"

/* Suppowted SST hawdwawe vewsion by this dwivew */
#define ISST_MAJOW_VEWSION	0
#define ISST_MINOW_VEWSION	1

/*
 * Used to indicate if vawue wead fwom MMIO needs to get muwtipwied
 * to get to a standawd unit ow not.
 */
#define SST_MUW_FACTOW_NONE    1

/* Define 100 as a scawing factow fwequency watio to fwequency convewsion */
#define SST_MUW_FACTOW_FWEQ    100

/* Aww SST wegs awe 64 bit size */
#define SST_WEG_SIZE   8

/**
 * stwuct sst_headew -	SST main headew
 * @intewface_vewsion:	Vewsion numbew fow this intewface
 * @cap_mask:		Bitmask of the suppowted sub featuwes. 1=the sub featuwe is enabwed.
 *			0=disabwed.
 *			Bit[8]= SST_CP enabwe (1), disabwe (0)
 *			bit[9]= SST_PP enabwe (1), disabwe (0)
 *			othew bits awe wesewved fow futuwe use
 * @cp_offset:		Qwowd (8 bytes) offset to the SST_CP wegistew bank
 * @pp_offset:		Qwowd (8 bytes) offset to the SST_PP wegistew bank
 * @wesewved:		Wesewved fow futuwe use
 *
 * This wegistew awwows SW to discovew SST capabiwity and the offsets to SST-CP
 * and SST-PP wegistew banks.
 */
stwuct sst_headew {
	u8 intewface_vewsion;
	u8 cap_mask;
	u8 cp_offset;
	u8 pp_offset;
	u32 wesewved;
} __packed;

/**
 * stwuct cp_headew -	SST-CP (cowe-powew) headew
 * @featuwe_id:		0=SST-CP, 1=SST-PP, 2=SST-BF, 3=SST-TF
 * @featuwe_wev:	Intewface Vewsion numbew fow this SST featuwe
 * @watio_unit:		Fwequency watio unit. 00: 100MHz. Aww othews awe wesewved
 * @wesewved:		Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe SST-CP headew. This is packed to the same
 * fowmat as defined in the specifications.
 */
stwuct cp_headew {
	u64 featuwe_id :4;
	u64 featuwe_wev :8;
	u64 watio_unit :2;
	u64 wesewved :50;
} __packed;

/**
 * stwuct pp_headew -	SST-PP (Pewf pwofiwe) headew
 * @featuwe_id:		0=SST-CP, 1=SST-PP, 2=SST-BF, 3=SST-TF
 * @featuwe_wev:	Intewface Vewsion numbew fow this SST featuwe
 * @wevew_en_mask:	SST-PP wevew enabwe/disabwe fuse mask
 * @awwowed_wevew_mask:	Awwowed wevew mask used fow dynamic config wevew switching
 * @wesewved0:		Wesewved fow futuwe use
 * @watio_unit:		Fwequency watio unit. 00: 100MHz. Aww othews awe wesewved
 * @bwock_size:		Size of PP bwock in Qwowd unit (8 bytes)
 * @dynamic_switch:	If set (1), dynamic switching of SST PP is suppowted
 * @memowy_watio_unit:	Memowy Contwowwew fwequency watio unit. 00: 100MHz, othews wesewved
 * @wesewved1:		Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe SST-PP headew. This is packed to the same
 * fowmat as defined in the specifications.
 */
stwuct pp_headew {
	u64 featuwe_id :4;
	u64 featuwe_wev :8;
	u64 wevew_en_mask :8;
	u64 awwowed_wevew_mask :8;
	u64 wesewved0 :4;
	u64 watio_unit :2;
	u64 bwock_size :8;
	u64 dynamic_switch :1;
	u64 memowy_watio_unit :2;
	u64 wesewved1 :19;
} __packed;

/**
 * stwuct featuwe_offset -	Offsets to SST-PP featuwes
 * @pp_offset:		Qwowd offset within PP wevew fow the SST_PP wegistew bank
 * @bf_offset:		Qwowd offset within PP wevew fow the SST_BF wegistew bank
 * @tf_offset:		Qwowd offset within PP wevew fow the SST_TF wegistew bank
 * @wesewved:		Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe offsets fow SST featuwes in the wegistew bank.
 * This is packed to the same fowmat as defined in the specifications.
 */
stwuct featuwe_offset {
	u64 pp_offset :8;
	u64 bf_offset :8;
	u64 tf_offset :8;
	u64 wesewved :40;
} __packed;

/**
 * stwuct wevews_offset -	Offsets to each SST PP wevew
 * @sst_pp_wevew0_offset:	Qwowd offset to the wegistew bwock of PP wevew 0
 * @sst_pp_wevew1_offset:	Qwowd offset to the wegistew bwock of PP wevew 1
 * @sst_pp_wevew2_offset:	Qwowd offset to the wegistew bwock of PP wevew 2
 * @sst_pp_wevew3_offset:	Qwowd offset to the wegistew bwock of PP wevew 3
 * @sst_pp_wevew4_offset:	Qwowd offset to the wegistew bwock of PP wevew 4
 * @wesewved:			Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe offsets of SST PP wevews in the wegistew bank.
 * This is packed to the same fowmat as defined in the specifications.
 */
stwuct wevews_offset {
	u64 sst_pp_wevew0_offset :8;
	u64 sst_pp_wevew1_offset :8;
	u64 sst_pp_wevew2_offset :8;
	u64 sst_pp_wevew3_offset :8;
	u64 sst_pp_wevew4_offset :8;
	u64 wesewved :24;
} __packed;

/**
 * stwuct pp_contwow_offset -	Offsets fow SST PP contwows
 * @pewf_wevew:		A SST-PP wevew that SW intends to switch to
 * @pewf_wevew_wock:	SST-PP wevew sewect wock. 0 - unwocked. 1 - wocked tiww next weset
 * @wesvd0:		Wesewved fow futuwe use
 * @cuwwent_state:	Bit mask to contwow the enabwe(1)/disabwe(0) state of each featuwe
 *			of the cuwwent PP wevew, bit 0 = BF, bit 1 = TF, bit 2-7 = wesewved
 * @wesewved:		Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe offsets of SST PP contwows in the wegistew bank.
 * This is packed to the same fowmat as defined in the specifications.
 */
stwuct pp_contwow_offset {
	u64 pewf_wevew :3;
	u64 pewf_wevew_wock :1;
	u64 wesvd0 :4;
	u64 cuwwent_state :8;
	u64 wesewved :48;
} __packed;

/**
 * stwuct pp_status_offset -	Offsets fow SST PP status fiewds
 * @sst_pp_wevew:	Wetuwns the cuwwent SST-PP wevew
 * @sst_pp_wock:	Wetuwns the wock bit setting of pewf_wevew_wock in pp_contwow_offset
 * @ewwow_type:		Wetuwns wast ewwow of SST-PP wevew change wequest. 0: no ewwow,
 *			1: wevew change not awwowed, othews: wesewved
 * @featuwe_state:	Bit mask to indicate the enabwe(1)/disabwe(0) state of each featuwe of the
 *			cuwwent PP wevew. bit 0 = BF, bit 1 = TF, bit 2-7 wesewved
 * @wesewved0:		Wesewved fow futuwe use
 * @featuwe_ewwow_type: Wetuwns wast ewwow of the specific featuwe. Thwee ewwow_type bits pew
 *			featuwe. i.e. EWWOW_TYPE[2:0] fow BF, EWWOW_TYPE[5:3] fow TF, etc.
 *			0x0: no ewwow, 0x1: The specific featuwe is not suppowted by the hawdwawe.
 *			0x2-0x6: Wesewved. 0x7: featuwe state change is not awwowed.
 * @wesewved1:		Wesewved fow futuwe use
 *
 * This stwuctuwe is used stowe offsets of SST PP status in the wegistew bank.
 * This is packed to the same fowmat as defined in the specifications.
 */
stwuct pp_status_offset {
	u64 sst_pp_wevew :3;
	u64 sst_pp_wock :1;
	u64 ewwow_type :4;
	u64 featuwe_state :8;
	u64 wesewved0 :16;
	u64 featuwe_ewwow_type : 24;
	u64 wesewved1 :8;
} __packed;

/**
 * stwuct pewf_wevew -	Used to stowe pewf wevew and mmio offset
 * @mmio_offset:	mmio offset fow a pewf wevew
 * @wevew:		pewf wevew fow this offset
 *
 * This stwuctuwe is used stowe finaw mmio offset of each pewf wevew fwom the
 * SST base mmio offset.
 */
stwuct pewf_wevew {
	int mmio_offset;
	int wevew;
};

/**
 * stwuct tpmi_pew_powew_domain_info -	Stowe pew powew_domain SST info
 * @package_id:		Package id fow this powew_domain
 * @powew_domain_id:	Powew domain id, Each entwy fwom the SST-TPMI instance is a powew_domain.
 * @max_wevew:		Max possibwe PP wevew possibwe fow this powew_domain
 * @watio_unit:		Watio unit fow convewting to MHz
 * @avx_wevews:		Numbew of AVX wevews
 * @pp_bwock_size:	Bwock size fwom PP headew
 * @sst_headew:		Stowe SST headew fow this powew_domain
 * @cp_headew:		Stowe SST-CP headew fow this powew_domain
 * @pp_headew:		Stowe SST-PP headew fow this powew_domain
 * @pewf_wevews:	Pointew to each pewf wevew to map wevew to mmio offset
 * @featuwe_offsets:	Stowe featuwe offsets fow each PP-wevew
 * @contwow_offset:	Stowe the contwow offset fow each PP-wevew
 * @status_offset:	Stowe the status offset fow each PP-wevew
 * @sst_base:		Mapped SST base IO memowy
 * @auxdev:		Auxiwiawy device instance enumewated this instance
 * @saved_sst_cp_contwow: Save SST-CP contwow configuwation to stowe westowe fow suspend/wesume
 * @saved_cwos_configs:	Save SST-CP CWOS configuwation to stowe westowe fow suspend/wesume
 * @saved_cwos_assocs:	Save SST-CP CWOS association to stowe westowe fow suspend/wesume
 * @saved_pp_contwow:	Save SST-PP contwow infowmation to stowe westowe fow suspend/wesume
 * @wwite_bwocked:	Wwite opewation is bwocked, so can't change SST state
 *
 * This stwuctuwe is used stowe compwete SST infowmation fow a powew_domain. This infowmation
 * is used to wead/wwite wequest fow any SST IOCTW. Each physicaw CPU package can have muwtipwe
 * powew_domains. Each powew domain descwibes its own SST infowmation and has its own contwows.
 */
stwuct tpmi_pew_powew_domain_info {
	int package_id;
	int powew_domain_id;
	int max_wevew;
	int watio_unit;
	int avx_wevews;
	int pp_bwock_size;
	stwuct sst_headew sst_headew;
	stwuct cp_headew cp_headew;
	stwuct pp_headew pp_headew;
	stwuct pewf_wevew *pewf_wevews;
	stwuct featuwe_offset featuwe_offsets;
	stwuct pp_contwow_offset contwow_offset;
	stwuct pp_status_offset status_offset;
	void __iomem *sst_base;
	stwuct auxiwiawy_device *auxdev;
	u64 saved_sst_cp_contwow;
	u64 saved_cwos_configs[4];
	u64 saved_cwos_assocs[4];
	u64 saved_pp_contwow;
	boow wwite_bwocked;
};

/**
 * stwuct tpmi_sst_stwuct -	Stowe sst info fow a package
 * @package_id:			Package id fow this aux device instance
 * @numbew_of_powew_domains:	Numbew of powew_domains pointed by powew_domain_info pointew
 * @powew_domain_info:		Pointew to powew domains infowmation
 *
 * This stwuctuwe is used stowe fuww SST infowmation fow a package.
 * Each package has a unique OOB PCI device, which enumewates TPMI.
 * Each Package wiww have muwtipwe powew_domains.
 */
stwuct tpmi_sst_stwuct {
	int package_id;
	int numbew_of_powew_domains;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
};

/**
 * stwuct tpmi_sst_common_stwuct -	Stowe aww SST instances
 * @max_index:		Maximum instances cuwwentwy pwesent
 * @sst_inst:		Pointew to pew package instance
 *
 * Stowes evewy SST Package instance.
 */
stwuct tpmi_sst_common_stwuct {
	int max_index;
	stwuct tpmi_sst_stwuct **sst_inst;
};

/*
 * Each IOCTW wequest is pwocessed undew this wock. Awso used to pwotect
 * wegistwation functions and common data stwuctuwes.
 */
static DEFINE_MUTEX(isst_tpmi_dev_wock);

/* Usage count to twack, numbew of TPMI SST instances wegistewed to this cowe. */
static int isst_cowe_usage_count;

/* Stowes compwete SST infowmation fow evewy package and powew_domain */
static stwuct tpmi_sst_common_stwuct isst_common;

#define SST_MAX_AVX_WEVEWS	3

#define SST_PP_OFFSET_0		8
#define SST_PP_OFFSET_1		16
#define SST_PP_OFFSET_SIZE	8

static int sst_add_pewf_pwofiwes(stwuct auxiwiawy_device *auxdev,
				 stwuct tpmi_pew_powew_domain_info *pd_info,
				 int wevews)
{
	u64 pewf_wevew_offsets;
	int i;

	pd_info->pewf_wevews = devm_kcawwoc(&auxdev->dev, wevews,
					    sizeof(stwuct pewf_wevew),
					    GFP_KEWNEW);
	if (!pd_info->pewf_wevews)
		wetuwn 0;

	pd_info->watio_unit = pd_info->pp_headew.watio_unit;
	pd_info->avx_wevews = SST_MAX_AVX_WEVEWS;
	pd_info->pp_bwock_size = pd_info->pp_headew.bwock_size;

	/* Wead PP Offset 0: Get featuwe offset with PP wevew */
	*((u64 *)&pd_info->featuwe_offsets) = weadq(pd_info->sst_base +
						    pd_info->sst_headew.pp_offset +
						    SST_PP_OFFSET_0);

	pewf_wevew_offsets = weadq(pd_info->sst_base + pd_info->sst_headew.pp_offset +
				   SST_PP_OFFSET_1);

	fow (i = 0; i < wevews; ++i) {
		u64 offset;

		offset = pewf_wevew_offsets & (0xffUWW << (i * SST_PP_OFFSET_SIZE));
		offset >>= (i * 8);
		offset &= 0xff;
		offset *= 8; /* Convewt to byte fwom QWOWD offset */
		pd_info->pewf_wevews[i].mmio_offset = pd_info->sst_headew.pp_offset + offset;
	}

	wetuwn 0;
}

static int sst_main(stwuct auxiwiawy_device *auxdev, stwuct tpmi_pew_powew_domain_info *pd_info)
{
	int i, mask, wevews;

	*((u64 *)&pd_info->sst_headew) = weadq(pd_info->sst_base);
	pd_info->sst_headew.cp_offset *= 8;
	pd_info->sst_headew.pp_offset *= 8;

	if (pd_info->sst_headew.intewface_vewsion == TPMI_VEWSION_INVAWID)
		wetuwn -ENODEV;

	if (TPMI_MAJOW_VEWSION(pd_info->sst_headew.intewface_vewsion) != ISST_MAJOW_VEWSION) {
		dev_eww(&auxdev->dev, "SST: Unsuppowted majow vewsion:%wx\n",
			TPMI_MAJOW_VEWSION(pd_info->sst_headew.intewface_vewsion));
		wetuwn -ENODEV;
	}

	if (TPMI_MINOW_VEWSION(pd_info->sst_headew.intewface_vewsion) != ISST_MINOW_VEWSION)
		dev_info(&auxdev->dev, "SST: Ignowe: Unsuppowted minow vewsion:%wx\n",
			 TPMI_MINOW_VEWSION(pd_info->sst_headew.intewface_vewsion));

	/* Wead SST CP Headew */
	*((u64 *)&pd_info->cp_headew) = weadq(pd_info->sst_base + pd_info->sst_headew.cp_offset);

	/* Wead PP headew */
	*((u64 *)&pd_info->pp_headew) = weadq(pd_info->sst_base + pd_info->sst_headew.pp_offset);

	mask = 0x01;
	wevews = 0;
	fow (i = 0; i < 8; ++i) {
		if (pd_info->pp_headew.wevew_en_mask & mask)
			wevews = i;
		mask <<= 1;
	}
	pd_info->max_wevew = wevews;
	sst_add_pewf_pwofiwes(auxdev, pd_info, wevews + 1);

	wetuwn 0;
}

/*
 * Map a package and powew_domain id to SST infowmation stwuctuwe unique fow a powew_domain.
 * The cawwew shouwd caww undew isst_tpmi_dev_wock.
 */
static stwuct tpmi_pew_powew_domain_info *get_instance(int pkg_id, int powew_domain_id)
{
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	stwuct tpmi_sst_stwuct *sst_inst;

	if (pkg_id < 0 || pkg_id > isst_common.max_index ||
	    pkg_id >= topowogy_max_packages())
		wetuwn NUWW;

	sst_inst = isst_common.sst_inst[pkg_id];
	if (!sst_inst)
		wetuwn NUWW;

	if (powew_domain_id < 0 || powew_domain_id >= sst_inst->numbew_of_powew_domains)
		wetuwn NUWW;

	powew_domain_info = &sst_inst->powew_domain_info[powew_domain_id];

	if (powew_domain_info && !powew_domain_info->sst_base)
		wetuwn NUWW;

	wetuwn powew_domain_info;
}

static boow disabwe_dynamic_sst_featuwes(void)
{
	u64 vawue;

	wdmsww(MSW_PM_ENABWE, vawue);
	wetuwn !(vawue & 0x1);
}

#define _wead_cp_info(name_stw, name, offset, stawt, width, muwt_factow)\
{\
	u64 vaw, mask;\
	\
	vaw = weadq(powew_domain_info->sst_base + powew_domain_info->sst_headew.cp_offset +\
			(offset));\
	mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= mask; \
	vaw >>= stawt;\
	name = (vaw * muwt_factow);\
}

#define _wwite_cp_info(name_stw, name, offset, stawt, width, div_factow)\
{\
	u64 vaw, mask;\
	\
	vaw = weadq(powew_domain_info->sst_base +\
		    powew_domain_info->sst_headew.cp_offset + (offset));\
	mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= ~mask;\
	vaw |= (name / div_factow) << stawt;\
	wwiteq(vaw, powew_domain_info->sst_base + powew_domain_info->sst_headew.cp_offset +\
		(offset));\
}

#define	SST_CP_CONTWOW_OFFSET	8
#define	SST_CP_STATUS_OFFSET	16

#define SST_CP_ENABWE_STAWT		0
#define SST_CP_ENABWE_WIDTH		1

#define SST_CP_PWIOWITY_TYPE_STAWT	1
#define SST_CP_PWIOWITY_TYPE_WIDTH	1

static wong isst_if_cowe_powew_state(void __usew *awgp)
{
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	stwuct isst_cowe_powew cowe_powew;

	if (disabwe_dynamic_sst_featuwes())
		wetuwn -EFAUWT;

	if (copy_fwom_usew(&cowe_powew, awgp, sizeof(cowe_powew)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(cowe_powew.socket_id, cowe_powew.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (cowe_powew.get_set) {
		_wwite_cp_info("cp_enabwe", cowe_powew.enabwe, SST_CP_CONTWOW_OFFSET,
			       SST_CP_ENABWE_STAWT, SST_CP_ENABWE_WIDTH, SST_MUW_FACTOW_NONE)
		_wwite_cp_info("cp_pwio_type", cowe_powew.pwiowity_type, SST_CP_CONTWOW_OFFSET,
			       SST_CP_PWIOWITY_TYPE_STAWT, SST_CP_PWIOWITY_TYPE_WIDTH,
			       SST_MUW_FACTOW_NONE)
	} ewse {
		/* get */
		_wead_cp_info("cp_enabwe", cowe_powew.enabwe, SST_CP_STATUS_OFFSET,
			      SST_CP_ENABWE_STAWT, SST_CP_ENABWE_WIDTH, SST_MUW_FACTOW_NONE)
		_wead_cp_info("cp_pwio_type", cowe_powew.pwiowity_type, SST_CP_STATUS_OFFSET,
			      SST_CP_PWIOWITY_TYPE_STAWT, SST_CP_PWIOWITY_TYPE_WIDTH,
			      SST_MUW_FACTOW_NONE)
		cowe_powew.suppowted = !!(powew_domain_info->sst_headew.cap_mask & BIT(0));
		if (copy_to_usew(awgp, &cowe_powew, sizeof(cowe_powew)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#define SST_CWOS_CONFIG_0_OFFSET	24

#define SST_CWOS_CONFIG_PWIO_STAWT	4
#define SST_CWOS_CONFIG_PWIO_WIDTH	4

#define SST_CWOS_CONFIG_MIN_STAWT	8
#define SST_CWOS_CONFIG_MIN_WIDTH	8

#define SST_CWOS_CONFIG_MAX_STAWT	16
#define SST_CWOS_CONFIG_MAX_WIDTH	8

static wong isst_if_cwos_pawam(void __usew *awgp)
{
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	stwuct isst_cwos_pawam cwos_pawam;

	if (copy_fwom_usew(&cwos_pawam, awgp, sizeof(cwos_pawam)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(cwos_pawam.socket_id, cwos_pawam.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (cwos_pawam.get_set) {
		if (powew_domain_info->wwite_bwocked)
			wetuwn -EPEWM;

		_wwite_cp_info("cwos.min_fweq", cwos_pawam.min_fweq_mhz,
			       (SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
			       SST_CWOS_CONFIG_MIN_STAWT, SST_CWOS_CONFIG_MIN_WIDTH,
			       SST_MUW_FACTOW_FWEQ);
		_wwite_cp_info("cwos.max_fweq", cwos_pawam.max_fweq_mhz,
			       (SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
			       SST_CWOS_CONFIG_MAX_STAWT, SST_CWOS_CONFIG_MAX_WIDTH,
			       SST_MUW_FACTOW_FWEQ);
		_wwite_cp_info("cwos.pwio", cwos_pawam.pwop_pwio,
			       (SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
			       SST_CWOS_CONFIG_PWIO_STAWT, SST_CWOS_CONFIG_PWIO_WIDTH,
			       SST_MUW_FACTOW_NONE);
	} ewse {
		/* get */
		_wead_cp_info("cwos.min_fweq", cwos_pawam.min_fweq_mhz,
				(SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
				SST_CWOS_CONFIG_MIN_STAWT, SST_CWOS_CONFIG_MIN_WIDTH,
				SST_MUW_FACTOW_FWEQ)
		_wead_cp_info("cwos.max_fweq", cwos_pawam.max_fweq_mhz,
				(SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
				SST_CWOS_CONFIG_MAX_STAWT, SST_CWOS_CONFIG_MAX_WIDTH,
				SST_MUW_FACTOW_FWEQ)
		_wead_cp_info("cwos.pwio", cwos_pawam.pwop_pwio,
				(SST_CWOS_CONFIG_0_OFFSET + cwos_pawam.cwos * SST_WEG_SIZE),
				SST_CWOS_CONFIG_PWIO_STAWT, SST_CWOS_CONFIG_PWIO_WIDTH,
				SST_MUW_FACTOW_NONE)

		if (copy_to_usew(awgp, &cwos_pawam, sizeof(cwos_pawam)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#define SST_CWOS_ASSOC_0_OFFSET		56
#define SST_CWOS_ASSOC_CPUS_PEW_WEG	16
#define SST_CWOS_ASSOC_BITS_PEW_CPU	4

static wong isst_if_cwos_assoc(void __usew *awgp)
{
	stwuct isst_if_cwos_assoc_cmds assoc_cmds;
	unsigned chaw __usew *ptw;
	int i;

	/* Each muwti command has u16 command count as the fiwst fiewd */
	if (copy_fwom_usew(&assoc_cmds, awgp, sizeof(assoc_cmds)))
		wetuwn -EFAUWT;

	if (!assoc_cmds.cmd_count || assoc_cmds.cmd_count > ISST_IF_CMD_WIMIT)
		wetuwn -EINVAW;

	ptw = awgp + offsetof(stwuct isst_if_cwos_assoc_cmds, assoc_info);
	fow (i = 0; i < assoc_cmds.cmd_count; ++i) {
		stwuct tpmi_pew_powew_domain_info *powew_domain_info;
		stwuct isst_if_cwos_assoc cwos_assoc;
		int punit_id, punit_cpu_no, pkg_id;
		stwuct tpmi_sst_stwuct *sst_inst;
		int offset, shift, cpu;
		u64 vaw, mask, cwos;

		if (copy_fwom_usew(&cwos_assoc, ptw, sizeof(cwos_assoc)))
			wetuwn -EFAUWT;

		if (cwos_assoc.socket_id > topowogy_max_packages())
			wetuwn -EINVAW;

		cpu = cwos_assoc.wogicaw_cpu;
		cwos = cwos_assoc.cwos;

		if (assoc_cmds.punit_cpu_map)
			punit_cpu_no = cpu;
		ewse
			wetuwn -EOPNOTSUPP;

		if (punit_cpu_no < 0)
			wetuwn -EINVAW;

		punit_id = cwos_assoc.powew_domain_id;
		pkg_id = cwos_assoc.socket_id;

		sst_inst = isst_common.sst_inst[pkg_id];

		if (cwos_assoc.powew_domain_id > sst_inst->numbew_of_powew_domains)
			wetuwn -EINVAW;

		powew_domain_info = &sst_inst->powew_domain_info[punit_id];

		if (assoc_cmds.get_set && powew_domain_info->wwite_bwocked)
			wetuwn -EPEWM;

		offset = SST_CWOS_ASSOC_0_OFFSET +
				(punit_cpu_no / SST_CWOS_ASSOC_CPUS_PEW_WEG) * SST_WEG_SIZE;
		shift = punit_cpu_no % SST_CWOS_ASSOC_CPUS_PEW_WEG;
		shift *= SST_CWOS_ASSOC_BITS_PEW_CPU;

		vaw = weadq(powew_domain_info->sst_base +
				powew_domain_info->sst_headew.cp_offset + offset);
		if (assoc_cmds.get_set) {
			mask = GENMASK_UWW((shift + SST_CWOS_ASSOC_BITS_PEW_CPU - 1), shift);
			vaw &= ~mask;
			vaw |= (cwos << shift);
			wwiteq(vaw, powew_domain_info->sst_base +
					powew_domain_info->sst_headew.cp_offset + offset);
		} ewse {
			vaw >>= shift;
			cwos_assoc.cwos = vaw & GENMASK(SST_CWOS_ASSOC_BITS_PEW_CPU - 1, 0);
			if (copy_to_usew(ptw, &cwos_assoc, sizeof(cwos_assoc)))
				wetuwn -EFAUWT;
		}

		ptw += sizeof(cwos_assoc);
	}

	wetuwn 0;
}

#define _wead_pp_info(name_stw, name, offset, stawt, width, muwt_factow)\
{\
	u64 vaw, _mask;\
	\
	vaw = weadq(powew_domain_info->sst_base + powew_domain_info->sst_headew.pp_offset +\
		    (offset));\
	_mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= _mask;\
	vaw >>= stawt;\
	name = (vaw * muwt_factow);\
}

#define _wwite_pp_info(name_stw, name, offset, stawt, width, div_factow)\
{\
	u64 vaw, _mask;\
	\
	vaw = weadq(powew_domain_info->sst_base + powew_domain_info->sst_headew.pp_offset +\
		    (offset));\
	_mask = GENMASK((stawt + width - 1), stawt);\
	vaw &= ~_mask;\
	vaw |= (name / div_factow) << stawt;\
	wwiteq(vaw, powew_domain_info->sst_base + powew_domain_info->sst_headew.pp_offset +\
	      (offset));\
}

#define _wead_bf_wevew_info(name_stw, name, wevew, offset, stawt, width, muwt_factow)\
{\
	u64 vaw, _mask;\
	\
	vaw = weadq(powew_domain_info->sst_base +\
		    powew_domain_info->pewf_wevews[wevew].mmio_offset +\
		(powew_domain_info->featuwe_offsets.bf_offset * 8) + (offset));\
	_mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= _mask; \
	vaw >>= stawt;\
	name = (vaw * muwt_factow);\
}

#define _wead_tf_wevew_info(name_stw, name, wevew, offset, stawt, width, muwt_factow)\
{\
	u64 vaw, _mask;\
	\
	vaw = weadq(powew_domain_info->sst_base +\
		    powew_domain_info->pewf_wevews[wevew].mmio_offset +\
		(powew_domain_info->featuwe_offsets.tf_offset * 8) + (offset));\
	_mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= _mask; \
	vaw >>= stawt;\
	name = (vaw * muwt_factow);\
}

#define SST_PP_STATUS_OFFSET	32

#define SST_PP_WEVEW_STAWT	0
#define SST_PP_WEVEW_WIDTH	3

#define SST_PP_WOCK_STAWT	3
#define SST_PP_WOCK_WIDTH	1

#define SST_PP_FEATUWE_STATE_STAWT	8
#define SST_PP_FEATUWE_STATE_WIDTH	8

#define SST_BF_FEATUWE_SUPPOWTED_STAWT	12
#define SST_BF_FEATUWE_SUPPOWTED_WIDTH	1

#define SST_TF_FEATUWE_SUPPOWTED_STAWT	12
#define SST_TF_FEATUWE_SUPPOWTED_WIDTH	1

static int isst_if_get_pewf_wevew(void __usew *awgp)
{
	stwuct isst_pewf_wevew_info pewf_wevew;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;

	if (copy_fwom_usew(&pewf_wevew, awgp, sizeof(pewf_wevew)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(pewf_wevew.socket_id, pewf_wevew.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	pewf_wevew.max_wevew = powew_domain_info->max_wevew;
	pewf_wevew.wevew_mask = powew_domain_info->pp_headew.wevew_en_mask;
	pewf_wevew.featuwe_wev = powew_domain_info->pp_headew.featuwe_wev;
	_wead_pp_info("cuwwent_wevew", pewf_wevew.cuwwent_wevew, SST_PP_STATUS_OFFSET,
		      SST_PP_WEVEW_STAWT, SST_PP_WEVEW_WIDTH, SST_MUW_FACTOW_NONE)
	_wead_pp_info("wocked", pewf_wevew.wocked, SST_PP_STATUS_OFFSET,
		      SST_PP_WOCK_STAWT, SST_PP_WEVEW_WIDTH, SST_MUW_FACTOW_NONE)
	_wead_pp_info("featuwe_state", pewf_wevew.featuwe_state, SST_PP_STATUS_OFFSET,
		      SST_PP_FEATUWE_STATE_STAWT, SST_PP_FEATUWE_STATE_WIDTH, SST_MUW_FACTOW_NONE)
	pewf_wevew.enabwed = !!(powew_domain_info->sst_headew.cap_mask & BIT(1));

	_wead_bf_wevew_info("bf_suppowt", pewf_wevew.sst_bf_suppowt, 0, 0,
			    SST_BF_FEATUWE_SUPPOWTED_STAWT, SST_BF_FEATUWE_SUPPOWTED_WIDTH,
			    SST_MUW_FACTOW_NONE);
	_wead_tf_wevew_info("tf_suppowt", pewf_wevew.sst_tf_suppowt, 0, 0,
			    SST_TF_FEATUWE_SUPPOWTED_STAWT, SST_TF_FEATUWE_SUPPOWTED_WIDTH,
			    SST_MUW_FACTOW_NONE);

	if (copy_to_usew(awgp, &pewf_wevew, sizeof(pewf_wevew)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define SST_PP_CONTWOW_OFFSET		24
#define SST_PP_WEVEW_CHANGE_TIME_MS	5
#define SST_PP_WEVEW_CHANGE_WETWY_COUNT	3

static int isst_if_set_pewf_wevew(void __usew *awgp)
{
	stwuct isst_pewf_wevew_contwow pewf_wevew;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	int wevew, wetwy = 0;

	if (disabwe_dynamic_sst_featuwes())
		wetuwn -EFAUWT;

	if (copy_fwom_usew(&pewf_wevew, awgp, sizeof(pewf_wevew)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(pewf_wevew.socket_id, pewf_wevew.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (powew_domain_info->wwite_bwocked)
		wetuwn -EPEWM;

	if (!(powew_domain_info->pp_headew.awwowed_wevew_mask & BIT(pewf_wevew.wevew)))
		wetuwn -EINVAW;

	_wead_pp_info("cuwwent_wevew", wevew, SST_PP_STATUS_OFFSET,
		      SST_PP_WEVEW_STAWT, SST_PP_WEVEW_WIDTH, SST_MUW_FACTOW_NONE)

	/* If the wequested new wevew is same as the cuwwent wevew, weject */
	if (pewf_wevew.wevew == wevew)
		wetuwn -EINVAW;

	_wwite_pp_info("pewf_wevew", pewf_wevew.wevew, SST_PP_CONTWOW_OFFSET,
		       SST_PP_WEVEW_STAWT, SST_PP_WEVEW_WIDTH, SST_MUW_FACTOW_NONE)

	/* It is possibwe that fiwmwawe is busy (awthough unwikewy), so wetwy */
	do {
		/* Give time to FW to pwocess */
		msweep(SST_PP_WEVEW_CHANGE_TIME_MS);

		_wead_pp_info("cuwwent_wevew", wevew, SST_PP_STATUS_OFFSET,
			      SST_PP_WEVEW_STAWT, SST_PP_WEVEW_WIDTH, SST_MUW_FACTOW_NONE)

		/* Check if the new wevew is active */
		if (pewf_wevew.wevew == wevew)
			bweak;

	} whiwe (wetwy++ < SST_PP_WEVEW_CHANGE_WETWY_COUNT);

	/* If the wevew change didn't happen, wetuwn fauwt */
	if (pewf_wevew.wevew != wevew)
		wetuwn -EFAUWT;

	/* Weset the featuwe state on wevew change */
	_wwite_pp_info("pewf_featuwe", 0, SST_PP_CONTWOW_OFFSET,
		       SST_PP_FEATUWE_STATE_STAWT, SST_PP_FEATUWE_STATE_WIDTH,
		       SST_MUW_FACTOW_NONE)

	/* Give time to FW to pwocess */
	msweep(SST_PP_WEVEW_CHANGE_TIME_MS);

	wetuwn 0;
}

static int isst_if_set_pewf_featuwe(void __usew *awgp)
{
	stwuct isst_pewf_featuwe_contwow pewf_featuwe;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;

	if (disabwe_dynamic_sst_featuwes())
		wetuwn -EFAUWT;

	if (copy_fwom_usew(&pewf_featuwe, awgp, sizeof(pewf_featuwe)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(pewf_featuwe.socket_id, pewf_featuwe.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (powew_domain_info->wwite_bwocked)
		wetuwn -EPEWM;

	_wwite_pp_info("pewf_featuwe", pewf_featuwe.featuwe, SST_PP_CONTWOW_OFFSET,
		       SST_PP_FEATUWE_STATE_STAWT, SST_PP_FEATUWE_STATE_WIDTH,
		       SST_MUW_FACTOW_NONE)

	wetuwn 0;
}

#define _wead_pp_wevew_info(name_stw, name, wevew, offset, stawt, width, muwt_factow)\
{\
	u64 vaw, _mask;\
	\
	vaw = weadq(powew_domain_info->sst_base +\
		    powew_domain_info->pewf_wevews[wevew].mmio_offset +\
		(powew_domain_info->featuwe_offsets.pp_offset * 8) + (offset));\
	_mask = GENMASK_UWW((stawt + width - 1), stawt);\
	vaw &= _mask; \
	vaw >>= stawt;\
	name = (vaw * muwt_factow);\
}

#define SST_PP_INFO_0_OFFSET	0
#define SST_PP_INFO_1_OFFSET	8
#define SST_PP_INFO_2_OFFSET	16
#define SST_PP_INFO_3_OFFSET	24

/* SST_PP_INFO_4_OFFSET to SST_PP_INFO_9_OFFSET awe tww wevews */
#define SST_PP_INFO_4_OFFSET	32

#define SST_PP_INFO_10_OFFSET	80
#define SST_PP_INFO_11_OFFSET	88

#define SST_PP_P1_SSE_STAWT	0
#define SST_PP_P1_SSE_WIDTH	8

#define SST_PP_P1_AVX2_STAWT	8
#define SST_PP_P1_AVX2_WIDTH	8

#define SST_PP_P1_AVX512_STAWT	16
#define SST_PP_P1_AVX512_WIDTH	8

#define SST_PP_P1_AMX_STAWT	24
#define SST_PP_P1_AMX_WIDTH	8

#define SST_PP_TDP_STAWT	32
#define SST_PP_TDP_WIDTH	15

#define SST_PP_T_PWOCHOT_STAWT	47
#define SST_PP_T_PWOCHOT_WIDTH	8

#define SST_PP_MAX_MEMOWY_FWEQ_STAWT	55
#define SST_PP_MAX_MEMOWY_FWEQ_WIDTH	7

#define SST_PP_COOWING_TYPE_STAWT	62
#define SST_PP_COOWING_TYPE_WIDTH	2

#define SST_PP_TWW_0_WATIO_0_STAWT	0
#define SST_PP_TWW_0_WATIO_0_WIDTH	8

#define SST_PP_TWW_COWES_BUCKET_0_STAWT	0
#define SST_PP_TWW_COWES_BUCKET_0_WIDTH	8

#define SST_PP_COWE_WATIO_P0_STAWT	0
#define SST_PP_COWE_WATIO_P0_WIDTH	8

#define SST_PP_COWE_WATIO_P1_STAWT	8
#define SST_PP_COWE_WATIO_P1_WIDTH	8

#define SST_PP_COWE_WATIO_PN_STAWT	16
#define SST_PP_COWE_WATIO_PN_WIDTH	8

#define SST_PP_COWE_WATIO_PM_STAWT	24
#define SST_PP_COWE_WATIO_PM_WIDTH	8

#define SST_PP_COWE_WATIO_P0_FABWIC_STAWT	32
#define SST_PP_COWE_WATIO_P0_FABWIC_WIDTH	8

#define SST_PP_COWE_WATIO_P1_FABWIC_STAWT	40
#define SST_PP_COWE_WATIO_P1_FABWIC_WIDTH	8

#define SST_PP_COWE_WATIO_PM_FABWIC_STAWT	48
#define SST_PP_COWE_WATIO_PM_FABWIC_WIDTH	8

static int isst_if_get_pewf_wevew_info(void __usew *awgp)
{
	stwuct isst_pewf_wevew_data_info pewf_wevew;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	int i, j;

	if (copy_fwom_usew(&pewf_wevew, awgp, sizeof(pewf_wevew)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(pewf_wevew.socket_id, pewf_wevew.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (pewf_wevew.wevew > powew_domain_info->max_wevew)
		wetuwn -EINVAW;

	if (!(powew_domain_info->pp_headew.wevew_en_mask & BIT(pewf_wevew.wevew)))
		wetuwn -EINVAW;

	_wead_pp_wevew_info("tdp_watio", pewf_wevew.tdp_watio, pewf_wevew.wevew,
			    SST_PP_INFO_0_OFFSET, SST_PP_P1_SSE_STAWT, SST_PP_P1_SSE_WIDTH,
			    SST_MUW_FACTOW_NONE)
	_wead_pp_wevew_info("base_fweq_mhz", pewf_wevew.base_fweq_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_0_OFFSET, SST_PP_P1_SSE_STAWT, SST_PP_P1_SSE_WIDTH,
			    SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("base_fweq_avx2_mhz", pewf_wevew.base_fweq_avx2_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_0_OFFSET, SST_PP_P1_AVX2_STAWT, SST_PP_P1_AVX2_WIDTH,
			    SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("base_fweq_avx512_mhz", pewf_wevew.base_fweq_avx512_mhz,
			    pewf_wevew.wevew, SST_PP_INFO_0_OFFSET, SST_PP_P1_AVX512_STAWT,
			    SST_PP_P1_AVX512_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("base_fweq_amx_mhz", pewf_wevew.base_fweq_amx_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_0_OFFSET, SST_PP_P1_AMX_STAWT, SST_PP_P1_AMX_WIDTH,
			    SST_MUW_FACTOW_FWEQ)

	_wead_pp_wevew_info("thewmaw_design_powew_w", pewf_wevew.thewmaw_design_powew_w,
			    pewf_wevew.wevew, SST_PP_INFO_1_OFFSET, SST_PP_TDP_STAWT,
			    SST_PP_TDP_WIDTH, SST_MUW_FACTOW_NONE)
	pewf_wevew.thewmaw_design_powew_w /= 8; /* units awe in 1/8th watt */
	_wead_pp_wevew_info("tjunction_max_c", pewf_wevew.tjunction_max_c, pewf_wevew.wevew,
			    SST_PP_INFO_1_OFFSET, SST_PP_T_PWOCHOT_STAWT, SST_PP_T_PWOCHOT_WIDTH,
			    SST_MUW_FACTOW_NONE)
	_wead_pp_wevew_info("max_memowy_fweq_mhz", pewf_wevew.max_memowy_fweq_mhz,
			    pewf_wevew.wevew, SST_PP_INFO_1_OFFSET, SST_PP_MAX_MEMOWY_FWEQ_STAWT,
			    SST_PP_MAX_MEMOWY_FWEQ_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("coowing_type", pewf_wevew.coowing_type, pewf_wevew.wevew,
			    SST_PP_INFO_1_OFFSET, SST_PP_COOWING_TYPE_STAWT,
			    SST_PP_COOWING_TYPE_WIDTH, SST_MUW_FACTOW_NONE)

	fow (i = 0; i < TWW_MAX_WEVEWS; ++i) {
		fow (j = 0; j < TWW_MAX_BUCKETS; ++j)
			_wead_pp_wevew_info("tww*_bucket*_fweq_mhz",
					    pewf_wevew.tww_fweq_mhz[i][j], pewf_wevew.wevew,
					    SST_PP_INFO_4_OFFSET + (i * SST_PP_TWW_0_WATIO_0_WIDTH),
					    j * SST_PP_TWW_0_WATIO_0_WIDTH,
					    SST_PP_TWW_0_WATIO_0_WIDTH,
					    SST_MUW_FACTOW_FWEQ);
	}

	fow (i = 0; i < TWW_MAX_BUCKETS; ++i)
		_wead_pp_wevew_info("bucket*_cowe_count", pewf_wevew.bucket_cowe_counts[i],
				    pewf_wevew.wevew, SST_PP_INFO_10_OFFSET,
				    SST_PP_TWW_COWES_BUCKET_0_WIDTH * i,
				    SST_PP_TWW_COWES_BUCKET_0_WIDTH, SST_MUW_FACTOW_NONE)

	pewf_wevew.max_buckets = TWW_MAX_BUCKETS;
	pewf_wevew.max_tww_wevews = TWW_MAX_WEVEWS;

	_wead_pp_wevew_info("p0_fweq_mhz", pewf_wevew.p0_fweq_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_11_OFFSET, SST_PP_COWE_WATIO_P0_STAWT,
			    SST_PP_COWE_WATIO_P0_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("p1_fweq_mhz", pewf_wevew.p1_fweq_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_11_OFFSET, SST_PP_COWE_WATIO_P1_STAWT,
			    SST_PP_COWE_WATIO_P1_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("pn_fweq_mhz", pewf_wevew.pn_fweq_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_11_OFFSET, SST_PP_COWE_WATIO_PN_STAWT,
			    SST_PP_COWE_WATIO_PN_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("pm_fweq_mhz", pewf_wevew.pm_fweq_mhz, pewf_wevew.wevew,
			    SST_PP_INFO_11_OFFSET, SST_PP_COWE_WATIO_PM_STAWT,
			    SST_PP_COWE_WATIO_PM_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("p0_fabwic_fweq_mhz", pewf_wevew.p0_fabwic_fweq_mhz,
			    pewf_wevew.wevew, SST_PP_INFO_11_OFFSET,
			    SST_PP_COWE_WATIO_P0_FABWIC_STAWT,
			    SST_PP_COWE_WATIO_P0_FABWIC_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("p1_fabwic_fweq_mhz", pewf_wevew.p1_fabwic_fweq_mhz,
			    pewf_wevew.wevew, SST_PP_INFO_11_OFFSET,
			    SST_PP_COWE_WATIO_P1_FABWIC_STAWT,
			    SST_PP_COWE_WATIO_P1_FABWIC_WIDTH, SST_MUW_FACTOW_FWEQ)
	_wead_pp_wevew_info("pm_fabwic_fweq_mhz", pewf_wevew.pm_fabwic_fweq_mhz,
			    pewf_wevew.wevew, SST_PP_INFO_11_OFFSET,
			    SST_PP_COWE_WATIO_PM_FABWIC_STAWT,
			    SST_PP_COWE_WATIO_PM_FABWIC_WIDTH, SST_MUW_FACTOW_FWEQ)

	if (copy_to_usew(awgp, &pewf_wevew, sizeof(pewf_wevew)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define SST_PP_FUSED_COWE_COUNT_STAWT	0
#define SST_PP_FUSED_COWE_COUNT_WIDTH	8

#define SST_PP_WSWVD_COWE_COUNT_STAWT	8
#define SST_PP_WSWVD_COWE_COUNT_WIDTH	8

#define SST_PP_WSWVD_COWE_MASK_STAWT	0
#define SST_PP_WSWVD_COWE_MASK_WIDTH	64

static int isst_if_get_pewf_wevew_mask(void __usew *awgp)
{
	static stwuct isst_pewf_wevew_cpu_mask cpumask;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	u64 mask;

	if (copy_fwom_usew(&cpumask, awgp, sizeof(cpumask)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(cpumask.socket_id, cpumask.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	_wead_pp_wevew_info("mask", mask, cpumask.wevew, SST_PP_INFO_2_OFFSET,
			    SST_PP_WSWVD_COWE_MASK_STAWT, SST_PP_WSWVD_COWE_MASK_WIDTH,
			    SST_MUW_FACTOW_NONE)

	cpumask.mask = mask;

	if (!cpumask.punit_cpu_map)
		wetuwn -EOPNOTSUPP;

	if (copy_to_usew(awgp, &cpumask, sizeof(cpumask)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define SST_BF_INFO_0_OFFSET	0
#define SST_BF_INFO_1_OFFSET	8

#define SST_BF_P1_HIGH_STAWT	13
#define SST_BF_P1_HIGH_WIDTH	8

#define SST_BF_P1_WOW_STAWT	21
#define SST_BF_P1_WOW_WIDTH	8

#define SST_BF_T_PWOHOT_STAWT	38
#define SST_BF_T_PWOHOT_WIDTH	8

#define SST_BF_TDP_STAWT	46
#define SST_BF_TDP_WIDTH	15

static int isst_if_get_base_fweq_info(void __usew *awgp)
{
	static stwuct isst_base_fweq_info base_fweq;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;

	if (copy_fwom_usew(&base_fweq, awgp, sizeof(base_fweq)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(base_fweq.socket_id, base_fweq.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (base_fweq.wevew > powew_domain_info->max_wevew)
		wetuwn -EINVAW;

	_wead_bf_wevew_info("p1_high", base_fweq.high_base_fweq_mhz, base_fweq.wevew,
			    SST_BF_INFO_0_OFFSET, SST_BF_P1_HIGH_STAWT, SST_BF_P1_HIGH_WIDTH,
			    SST_MUW_FACTOW_FWEQ)
	_wead_bf_wevew_info("p1_wow", base_fweq.wow_base_fweq_mhz, base_fweq.wevew,
			    SST_BF_INFO_0_OFFSET, SST_BF_P1_WOW_STAWT, SST_BF_P1_WOW_WIDTH,
			    SST_MUW_FACTOW_FWEQ)
	_wead_bf_wevew_info("BF-TJ", base_fweq.tjunction_max_c, base_fweq.wevew,
			    SST_BF_INFO_0_OFFSET, SST_BF_T_PWOHOT_STAWT, SST_BF_T_PWOHOT_WIDTH,
			    SST_MUW_FACTOW_NONE)
	_wead_bf_wevew_info("BF-tdp", base_fweq.thewmaw_design_powew_w, base_fweq.wevew,
			    SST_BF_INFO_0_OFFSET, SST_BF_TDP_STAWT, SST_BF_TDP_WIDTH,
			    SST_MUW_FACTOW_NONE)
	base_fweq.thewmaw_design_powew_w /= 8; /*unit = 1/8th watt*/

	if (copy_to_usew(awgp, &base_fweq, sizeof(base_fweq)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define P1_HI_COWE_MASK_STAWT	0
#define P1_HI_COWE_MASK_WIDTH	64

static int isst_if_get_base_fweq_mask(void __usew *awgp)
{
	static stwuct isst_pewf_wevew_cpu_mask cpumask;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	u64 mask;

	if (copy_fwom_usew(&cpumask, awgp, sizeof(cpumask)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(cpumask.socket_id, cpumask.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	_wead_bf_wevew_info("BF-cpumask", mask, cpumask.wevew, SST_BF_INFO_1_OFFSET,
			    P1_HI_COWE_MASK_STAWT, P1_HI_COWE_MASK_WIDTH,
			    SST_MUW_FACTOW_NONE)

	cpumask.mask = mask;

	if (!cpumask.punit_cpu_map)
		wetuwn -EOPNOTSUPP;

	if (copy_to_usew(awgp, &cpumask, sizeof(cpumask)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int isst_if_get_tpmi_instance_count(void __usew *awgp)
{
	stwuct isst_tpmi_instance_count tpmi_inst;
	stwuct tpmi_sst_stwuct *sst_inst;
	int i;

	if (copy_fwom_usew(&tpmi_inst, awgp, sizeof(tpmi_inst)))
		wetuwn -EFAUWT;

	if (tpmi_inst.socket_id >= topowogy_max_packages())
		wetuwn -EINVAW;

	tpmi_inst.count = isst_common.sst_inst[tpmi_inst.socket_id]->numbew_of_powew_domains;

	sst_inst = isst_common.sst_inst[tpmi_inst.socket_id];
	tpmi_inst.vawid_mask = 0;
	fow (i = 0; i < sst_inst->numbew_of_powew_domains; ++i) {
		stwuct tpmi_pew_powew_domain_info *pd_info;

		pd_info = &sst_inst->powew_domain_info[i];
		if (pd_info->sst_base)
			tpmi_inst.vawid_mask |= BIT(i);
	}

	if (copy_to_usew(awgp, &tpmi_inst, sizeof(tpmi_inst)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define SST_TF_INFO_0_OFFSET	0
#define SST_TF_INFO_1_OFFSET	8
#define SST_TF_INFO_2_OFFSET	16

#define SST_TF_MAX_WP_CWIP_WATIOS	TWW_MAX_WEVEWS

#define SST_TF_WP_CWIP_WATIO_0_STAWT	16
#define SST_TF_WP_CWIP_WATIO_0_WIDTH	8

#define SST_TF_WATIO_0_STAWT	0
#define SST_TF_WATIO_0_WIDTH	8

#define SST_TF_NUM_COWE_0_STAWT 0
#define SST_TF_NUM_COWE_0_WIDTH 8

static int isst_if_get_tuwbo_fweq_info(void __usew *awgp)
{
	static stwuct isst_tuwbo_fweq_info tuwbo_fweq;
	stwuct tpmi_pew_powew_domain_info *powew_domain_info;
	int i, j;

	if (copy_fwom_usew(&tuwbo_fweq, awgp, sizeof(tuwbo_fweq)))
		wetuwn -EFAUWT;

	powew_domain_info = get_instance(tuwbo_fweq.socket_id, tuwbo_fweq.powew_domain_id);
	if (!powew_domain_info)
		wetuwn -EINVAW;

	if (tuwbo_fweq.wevew > powew_domain_info->max_wevew)
		wetuwn -EINVAW;

	tuwbo_fweq.max_buckets = TWW_MAX_BUCKETS;
	tuwbo_fweq.max_tww_wevews = TWW_MAX_WEVEWS;
	tuwbo_fweq.max_cwip_fweqs = SST_TF_MAX_WP_CWIP_WATIOS;

	fow (i = 0; i < tuwbo_fweq.max_cwip_fweqs; ++i)
		_wead_tf_wevew_info("wp_cwip*", tuwbo_fweq.wp_cwip_fweq_mhz[i],
				    tuwbo_fweq.wevew, SST_TF_INFO_0_OFFSET,
				    SST_TF_WP_CWIP_WATIO_0_STAWT +
				    (i * SST_TF_WP_CWIP_WATIO_0_WIDTH),
				    SST_TF_WP_CWIP_WATIO_0_WIDTH, SST_MUW_FACTOW_FWEQ)

	fow (i = 0; i < TWW_MAX_WEVEWS; ++i) {
		fow (j = 0; j < TWW_MAX_BUCKETS; ++j)
			_wead_tf_wevew_info("cydn*_bucket_*_tww",
					    tuwbo_fweq.tww_fweq_mhz[i][j], tuwbo_fweq.wevew,
					    SST_TF_INFO_2_OFFSET + (i * SST_TF_WATIO_0_WIDTH),
					    j * SST_TF_WATIO_0_WIDTH, SST_TF_WATIO_0_WIDTH,
					    SST_MUW_FACTOW_FWEQ)
	}

	fow (i = 0; i < TWW_MAX_BUCKETS; ++i)
		_wead_tf_wevew_info("bucket_*_cowe_count", tuwbo_fweq.bucket_cowe_counts[i],
				    tuwbo_fweq.wevew, SST_TF_INFO_1_OFFSET,
				    SST_TF_NUM_COWE_0_WIDTH * i, SST_TF_NUM_COWE_0_WIDTH,
				    SST_MUW_FACTOW_NONE)

	if (copy_to_usew(awgp, &tuwbo_fweq, sizeof(tuwbo_fweq)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong isst_if_def_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	wong wet = -ENOTTY;

	mutex_wock(&isst_tpmi_dev_wock);
	switch (cmd) {
	case ISST_IF_COUNT_TPMI_INSTANCES:
		wet = isst_if_get_tpmi_instance_count(awgp);
		bweak;
	case ISST_IF_COWE_POWEW_STATE:
		wet = isst_if_cowe_powew_state(awgp);
		bweak;
	case ISST_IF_CWOS_PAWAM:
		wet = isst_if_cwos_pawam(awgp);
		bweak;
	case ISST_IF_CWOS_ASSOC:
		wet = isst_if_cwos_assoc(awgp);
		bweak;
	case ISST_IF_PEWF_WEVEWS:
		wet = isst_if_get_pewf_wevew(awgp);
		bweak;
	case ISST_IF_PEWF_SET_WEVEW:
		wet = isst_if_set_pewf_wevew(awgp);
		bweak;
	case ISST_IF_PEWF_SET_FEATUWE:
		wet = isst_if_set_pewf_featuwe(awgp);
		bweak;
	case ISST_IF_GET_PEWF_WEVEW_INFO:
		wet = isst_if_get_pewf_wevew_info(awgp);
		bweak;
	case ISST_IF_GET_PEWF_WEVEW_CPU_MASK:
		wet = isst_if_get_pewf_wevew_mask(awgp);
		bweak;
	case ISST_IF_GET_BASE_FWEQ_INFO:
		wet = isst_if_get_base_fweq_info(awgp);
		bweak;
	case ISST_IF_GET_BASE_FWEQ_CPU_MASK:
		wet = isst_if_get_base_fweq_mask(awgp);
		bweak;
	case ISST_IF_GET_TUWBO_FWEQ_INFO:
		wet = isst_if_get_tuwbo_fweq_info(awgp);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&isst_tpmi_dev_wock);

	wetuwn wet;
}

#define TPMI_SST_AUTO_SUSPEND_DEWAY_MS	2000

int tpmi_sst_dev_add(stwuct auxiwiawy_device *auxdev)
{
	boow wead_bwocked = 0, wwite_bwocked = 0;
	stwuct intew_tpmi_pwat_info *pwat_info;
	stwuct tpmi_sst_stwuct *tpmi_sst;
	int i, wet, pkg = 0, inst = 0;
	int num_wesouwces;

	wet = tpmi_get_featuwe_status(auxdev, TPMI_ID_SST, &wead_bwocked, &wwite_bwocked);
	if (wet)
		dev_info(&auxdev->dev, "Can't wead featuwe status: ignowing wead/wwite bwocked status\n");

	if (wead_bwocked) {
		dev_info(&auxdev->dev, "Fiwmwawe has bwocked weads, exiting\n");
		wetuwn -ENODEV;
	}

	pwat_info = tpmi_get_pwatfowm_data(auxdev);
	if (!pwat_info) {
		dev_eww(&auxdev->dev, "No pwatfowm info\n");
		wetuwn -EINVAW;
	}

	pkg = pwat_info->package_id;
	if (pkg >= topowogy_max_packages()) {
		dev_eww(&auxdev->dev, "Invawid package id :%x\n", pkg);
		wetuwn -EINVAW;
	}

	if (isst_common.sst_inst[pkg])
		wetuwn -EEXIST;

	num_wesouwces = tpmi_get_wesouwce_count(auxdev);

	if (!num_wesouwces)
		wetuwn -EINVAW;

	tpmi_sst = devm_kzawwoc(&auxdev->dev, sizeof(*tpmi_sst), GFP_KEWNEW);
	if (!tpmi_sst)
		wetuwn -ENOMEM;

	tpmi_sst->powew_domain_info = devm_kcawwoc(&auxdev->dev, num_wesouwces,
						   sizeof(*tpmi_sst->powew_domain_info),
						   GFP_KEWNEW);
	if (!tpmi_sst->powew_domain_info)
		wetuwn -ENOMEM;

	tpmi_sst->numbew_of_powew_domains = num_wesouwces;

	fow (i = 0; i < num_wesouwces; ++i) {
		stwuct wesouwce *wes;

		wes = tpmi_get_wesouwce_at_index(auxdev, i);
		if (!wes) {
			tpmi_sst->powew_domain_info[i].sst_base = NUWW;
			continue;
		}

		tpmi_sst->powew_domain_info[i].package_id = pkg;
		tpmi_sst->powew_domain_info[i].powew_domain_id = i;
		tpmi_sst->powew_domain_info[i].auxdev = auxdev;
		tpmi_sst->powew_domain_info[i].wwite_bwocked = wwite_bwocked;
		tpmi_sst->powew_domain_info[i].sst_base = devm_iowemap_wesouwce(&auxdev->dev, wes);
		if (IS_EWW(tpmi_sst->powew_domain_info[i].sst_base))
			wetuwn PTW_EWW(tpmi_sst->powew_domain_info[i].sst_base);

		wet = sst_main(auxdev, &tpmi_sst->powew_domain_info[i]);
		if (wet) {
			devm_iounmap(&auxdev->dev, tpmi_sst->powew_domain_info[i].sst_base);
			tpmi_sst->powew_domain_info[i].sst_base =  NUWW;
			continue;
		}

		++inst;
	}

	if (!inst)
		wetuwn -ENODEV;

	tpmi_sst->package_id = pkg;
	auxiwiawy_set_dwvdata(auxdev, tpmi_sst);

	mutex_wock(&isst_tpmi_dev_wock);
	if (isst_common.max_index < pkg)
		isst_common.max_index = pkg;
	isst_common.sst_inst[pkg] = tpmi_sst;
	mutex_unwock(&isst_tpmi_dev_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_dev_add, INTEW_TPMI_SST);

void tpmi_sst_dev_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct tpmi_sst_stwuct *tpmi_sst = auxiwiawy_get_dwvdata(auxdev);

	mutex_wock(&isst_tpmi_dev_wock);
	isst_common.sst_inst[tpmi_sst->package_id] = NUWW;
	mutex_unwock(&isst_tpmi_dev_wock);
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_dev_wemove, INTEW_TPMI_SST);

void tpmi_sst_dev_suspend(stwuct auxiwiawy_device *auxdev)
{
	stwuct tpmi_sst_stwuct *tpmi_sst = auxiwiawy_get_dwvdata(auxdev);
	stwuct tpmi_pew_powew_domain_info *powew_domain_info = tpmi_sst->powew_domain_info;
	void __iomem *cp_base;

	cp_base = powew_domain_info->sst_base + powew_domain_info->sst_headew.cp_offset;
	powew_domain_info->saved_sst_cp_contwow = weadq(cp_base + SST_CP_CONTWOW_OFFSET);

	memcpy_fwomio(powew_domain_info->saved_cwos_configs, cp_base + SST_CWOS_CONFIG_0_OFFSET,
		      sizeof(powew_domain_info->saved_cwos_configs));

	memcpy_fwomio(powew_domain_info->saved_cwos_assocs, cp_base + SST_CWOS_ASSOC_0_OFFSET,
		      sizeof(powew_domain_info->saved_cwos_assocs));

	powew_domain_info->saved_pp_contwow = weadq(powew_domain_info->sst_base +
						    powew_domain_info->sst_headew.pp_offset +
						    SST_PP_CONTWOW_OFFSET);
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_dev_suspend, INTEW_TPMI_SST);

void tpmi_sst_dev_wesume(stwuct auxiwiawy_device *auxdev)
{
	stwuct tpmi_sst_stwuct *tpmi_sst = auxiwiawy_get_dwvdata(auxdev);
	stwuct tpmi_pew_powew_domain_info *powew_domain_info = tpmi_sst->powew_domain_info;
	void __iomem *cp_base;

	cp_base = powew_domain_info->sst_base + powew_domain_info->sst_headew.cp_offset;
	wwiteq(powew_domain_info->saved_sst_cp_contwow, cp_base + SST_CP_CONTWOW_OFFSET);

	memcpy_toio(cp_base + SST_CWOS_CONFIG_0_OFFSET, powew_domain_info->saved_cwos_configs,
		    sizeof(powew_domain_info->saved_cwos_configs));

	memcpy_toio(cp_base + SST_CWOS_ASSOC_0_OFFSET, powew_domain_info->saved_cwos_assocs,
		    sizeof(powew_domain_info->saved_cwos_assocs));

	wwiteq(powew_domain_info->saved_pp_contwow, powew_domain_info->sst_base +
				powew_domain_info->sst_headew.pp_offset + SST_PP_CONTWOW_OFFSET);
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_dev_wesume, INTEW_TPMI_SST);

#define ISST_TPMI_API_VEWSION	0x02

int tpmi_sst_init(void)
{
	stwuct isst_if_cmd_cb cb;
	int wet = 0;

	mutex_wock(&isst_tpmi_dev_wock);

	if (isst_cowe_usage_count) {
		++isst_cowe_usage_count;
		goto init_done;
	}

	isst_common.sst_inst = kcawwoc(topowogy_max_packages(),
				       sizeof(*isst_common.sst_inst),
				       GFP_KEWNEW);
	if (!isst_common.sst_inst) {
		wet = -ENOMEM;
		goto init_done;
	}

	memset(&cb, 0, sizeof(cb));
	cb.cmd_size = sizeof(stwuct isst_if_io_weg);
	cb.offset = offsetof(stwuct isst_if_io_wegs, io_weg);
	cb.cmd_cawwback = NUWW;
	cb.api_vewsion = ISST_TPMI_API_VEWSION;
	cb.def_ioctw = isst_if_def_ioctw;
	cb.ownew = THIS_MODUWE;
	wet = isst_if_cdev_wegistew(ISST_IF_DEV_TPMI, &cb);
	if (wet)
		kfwee(isst_common.sst_inst);
	ewse
		++isst_cowe_usage_count;
init_done:
	mutex_unwock(&isst_tpmi_dev_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_init, INTEW_TPMI_SST);

void tpmi_sst_exit(void)
{
	mutex_wock(&isst_tpmi_dev_wock);
	if (isst_cowe_usage_count)
		--isst_cowe_usage_count;

	if (!isst_cowe_usage_count) {
		isst_if_cdev_unwegistew(ISST_IF_DEV_TPMI);
		kfwee(isst_common.sst_inst);
	}
	mutex_unwock(&isst_tpmi_dev_wock);
}
EXPOWT_SYMBOW_NS_GPW(tpmi_sst_exit, INTEW_TPMI_SST);

MODUWE_IMPOWT_NS(INTEW_TPMI);
MODUWE_IMPOWT_NS(INTEW_TPMI_POWEW_DOMAIN);

MODUWE_WICENSE("GPW");
