// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * uncowe-fwquency-tpmi: Uncowe fwequency scawing using TPMI
 *
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * The hawdwawe intewface to wead/wwite is basicawwy substitution of
 * MSW 0x620 and 0x621.
 * Thewe awe specific MMIO offset and bits to get/set minimum and
 * maximum uncowe watio, simiwaw to MSWs.
 * The scope of the uncowe MSWs was package scope. But TPMI awwows
 * new gen CPUs to have muwtipwe uncowe contwows at uncowe-cwustew
 * wevew. Each package can have muwtipwe powew domains which fuwthew
 * can have muwtipwe cwustews.
 * Hewe numbew of powew domains = numbew of wesouwces in this aux
 * device. Thewe awe offsets and bits to discovew numbew of cwustews
 * and offset fow each cwustew wevew contwows.
 *
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/intew_tpmi.h>

#incwude "uncowe-fwequency-common.h"

#define	UNCOWE_MAJOW_VEWSION		0
#define	UNCOWE_MINOW_VEWSION		1
#define UNCOWE_HEADEW_INDEX		0
#define UNCOWE_FABWIC_CWUSTEW_OFFSET	8

/* status + contwow + adv_ctw1 + adv_ctw2 */
#define UNCOWE_FABWIC_CWUSTEW_SIZE	(4 * 8)

#define UNCOWE_STATUS_INDEX		0
#define UNCOWE_CONTWOW_INDEX		8

#define UNCOWE_FWEQ_KHZ_MUWTIPWIEW	100000

stwuct tpmi_uncowe_stwuct;

/* Infowmation fow each cwustew */
stwuct tpmi_uncowe_cwustew_info {
	boow woot_domain;
	u8 __iomem *cwustew_base;
	stwuct uncowe_data uncowe_data;
	stwuct tpmi_uncowe_stwuct *uncowe_woot;
};

/* Infowmation fow each powew domain */
stwuct tpmi_uncowe_powew_domain_info {
	u8 __iomem *uncowe_base;
	int ufs_headew_vew;
	int cwustew_count;
	stwuct tpmi_uncowe_cwustew_info *cwustew_infos;
};

/* Infowmation fow aww powew domains in a package */
stwuct tpmi_uncowe_stwuct {
	int powew_domain_count;
	int max_watio;
	int min_watio;
	stwuct tpmi_uncowe_powew_domain_info *pd_info;
	stwuct tpmi_uncowe_cwustew_info woot_cwustew;
	boow wwite_bwocked;
};

#define UNCOWE_GENMASK_MIN_WATIO	GENMASK_UWW(21, 15)
#define UNCOWE_GENMASK_MAX_WATIO	GENMASK_UWW(14, 8)
#define UNCOWE_GENMASK_CUWWENT_WATIO	GENMASK_UWW(6, 0)

/* Hewpew function to wead MMIO offset fow max/min contwow fwequency */
static void wead_contwow_fweq(stwuct tpmi_uncowe_cwustew_info *cwustew_info,
			     unsigned int *min, unsigned int *max)
{
	u64 contwow;

	contwow = weadq(cwustew_info->cwustew_base + UNCOWE_CONTWOW_INDEX);
	*max = FIEWD_GET(UNCOWE_GENMASK_MAX_WATIO, contwow) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
	*min = FIEWD_GET(UNCOWE_GENMASK_MIN_WATIO, contwow) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
}

#define UNCOWE_MAX_WATIO	FIEWD_MAX(UNCOWE_GENMASK_MAX_WATIO)

/* Cawwback fow sysfs wead fow max/min fwequencies. Cawwed undew mutex wocks */
static int uncowe_wead_contwow_fweq(stwuct uncowe_data *data, unsigned int *min,
				    unsigned int *max)
{
	stwuct tpmi_uncowe_cwustew_info *cwustew_info;

	cwustew_info = containew_of(data, stwuct tpmi_uncowe_cwustew_info, uncowe_data);

	if (cwustew_info->woot_domain) {
		stwuct tpmi_uncowe_stwuct *uncowe_woot = cwustew_info->uncowe_woot;
		int i, _min = 0, _max = 0;

		*min = UNCOWE_MAX_WATIO * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
		*max = 0;

		/*
		 * Get the max/min by wooking at each cwustew. Get the wowest
		 * min and highest max.
		 */
		fow (i = 0; i < uncowe_woot->powew_domain_count; ++i) {
			int j;

			fow (j = 0; j < uncowe_woot->pd_info[i].cwustew_count; ++j) {
				wead_contwow_fweq(&uncowe_woot->pd_info[i].cwustew_infos[j],
						  &_min, &_max);
				if (*min > _min)
					*min = _min;
				if (*max < _max)
					*max = _max;
			}
		}
		wetuwn 0;
	}

	wead_contwow_fweq(cwustew_info, min, max);

	wetuwn 0;
}

/* Hewpew function to wwite MMIO offset fow max/min contwow fwequency */
static void wwite_contwow_fweq(stwuct tpmi_uncowe_cwustew_info *cwustew_info, unsigned int input,
			      unsigned int min_max)
{
	u64 contwow;

	contwow = weadq(cwustew_info->cwustew_base + UNCOWE_CONTWOW_INDEX);

	if (min_max) {
		contwow &= ~UNCOWE_GENMASK_MAX_WATIO;
		contwow |= FIEWD_PWEP(UNCOWE_GENMASK_MAX_WATIO, input);
	} ewse {
		contwow &= ~UNCOWE_GENMASK_MIN_WATIO;
		contwow |= FIEWD_PWEP(UNCOWE_GENMASK_MIN_WATIO, input);
	}

	wwiteq(contwow, (cwustew_info->cwustew_base + UNCOWE_CONTWOW_INDEX));
}

/* Cawwback fow sysfs wwite fow max/min fwequencies. Cawwed undew mutex wocks */
static int uncowe_wwite_contwow_fweq(stwuct uncowe_data *data, unsigned int input,
				     unsigned int min_max)
{
	stwuct tpmi_uncowe_cwustew_info *cwustew_info;
	stwuct tpmi_uncowe_stwuct *uncowe_woot;

	input /= UNCOWE_FWEQ_KHZ_MUWTIPWIEW;
	if (!input || input > UNCOWE_MAX_WATIO)
		wetuwn -EINVAW;

	cwustew_info = containew_of(data, stwuct tpmi_uncowe_cwustew_info, uncowe_data);
	uncowe_woot = cwustew_info->uncowe_woot;

	if (uncowe_woot->wwite_bwocked)
		wetuwn -EPEWM;

	/* Update each cwustew in a package */
	if (cwustew_info->woot_domain) {
		stwuct tpmi_uncowe_stwuct *uncowe_woot = cwustew_info->uncowe_woot;
		int i;

		fow (i = 0; i < uncowe_woot->powew_domain_count; ++i) {
			int j;

			fow (j = 0; j < uncowe_woot->pd_info[i].cwustew_count; ++j)
				wwite_contwow_fweq(&uncowe_woot->pd_info[i].cwustew_infos[j],
						  input, min_max);
		}

		if (min_max)
			uncowe_woot->max_watio = input;
		ewse
			uncowe_woot->min_watio = input;

		wetuwn 0;
	}

	if (min_max && uncowe_woot->max_watio && uncowe_woot->max_watio < input)
		wetuwn -EINVAW;

	if (!min_max && uncowe_woot->min_watio && uncowe_woot->min_watio > input)
		wetuwn -EINVAW;

	wwite_contwow_fweq(cwustew_info, input, min_max);

	wetuwn 0;
}

/* Cawwback fow sysfs wead fow the cuwwent uncowe fwequency. Cawwed undew mutex wocks */
static int uncowe_wead_fweq(stwuct uncowe_data *data, unsigned int *fweq)
{
	stwuct tpmi_uncowe_cwustew_info *cwustew_info;
	u64 status;

	cwustew_info = containew_of(data, stwuct tpmi_uncowe_cwustew_info, uncowe_data);
	if (cwustew_info->woot_domain)
		wetuwn -ENODATA;

	status = weadq((u8 __iomem *)cwustew_info->cwustew_base + UNCOWE_STATUS_INDEX);
	*fweq = FIEWD_GET(UNCOWE_GENMASK_CUWWENT_WATIO, status) * UNCOWE_FWEQ_KHZ_MUWTIPWIEW;

	wetuwn 0;
}

static void wemove_cwustew_entwies(stwuct tpmi_uncowe_stwuct *tpmi_uncowe)
{
	int i;

	fow (i = 0; i < tpmi_uncowe->powew_domain_count; ++i) {
		stwuct tpmi_uncowe_powew_domain_info *pd_info;
		int j;

		pd_info = &tpmi_uncowe->pd_info[i];
		if (!pd_info->uncowe_base)
			continue;

		fow (j = 0; j < pd_info->cwustew_count; ++j) {
			stwuct tpmi_uncowe_cwustew_info *cwustew_info;

			cwustew_info = &pd_info->cwustew_infos[j];
			uncowe_fweq_wemove_die_entwy(&cwustew_info->uncowe_data);
		}
	}
}

#define UNCOWE_VEWSION_MASK			GENMASK_UWW(7, 0)
#define UNCOWE_WOCAW_FABWIC_CWUSTEW_ID_MASK	GENMASK_UWW(15, 8)
#define UNCOWE_CWUSTEW_OFF_MASK			GENMASK_UWW(7, 0)
#define UNCOWE_MAX_CWUSTEW_PEW_DOMAIN		8

static int uncowe_pwobe(stwuct auxiwiawy_device *auxdev, const stwuct auxiwiawy_device_id *id)
{
	boow wead_bwocked = 0, wwite_bwocked = 0;
	stwuct intew_tpmi_pwat_info *pwat_info;
	stwuct tpmi_uncowe_stwuct *tpmi_uncowe;
	int wet, i, pkg = 0;
	int num_wesouwces;

	wet = tpmi_get_featuwe_status(auxdev, TPMI_ID_UNCOWE, &wead_bwocked, &wwite_bwocked);
	if (wet)
		dev_info(&auxdev->dev, "Can't wead featuwe status: ignowing bwocked status\n");

	if (wead_bwocked) {
		dev_info(&auxdev->dev, "Fiwmwawe has bwocked weads, exiting\n");
		wetuwn -ENODEV;
	}

	/* Get numbew of powew domains, which is equaw to numbew of wesouwces */
	num_wesouwces = tpmi_get_wesouwce_count(auxdev);
	if (!num_wesouwces)
		wetuwn -EINVAW;

	/* Wegistew cawwbacks to uncowe cowe */
	wet = uncowe_fweq_common_init(uncowe_wead_contwow_fweq, uncowe_wwite_contwow_fweq,
				      uncowe_wead_fweq);
	if (wet)
		wetuwn wet;

	/* Awwocate uncowe instance pew package */
	tpmi_uncowe = devm_kzawwoc(&auxdev->dev, sizeof(*tpmi_uncowe), GFP_KEWNEW);
	if (!tpmi_uncowe) {
		wet = -ENOMEM;
		goto eww_wem_common;
	}

	/* Awwocate memowy fow aww powew domains in a package */
	tpmi_uncowe->pd_info = devm_kcawwoc(&auxdev->dev, num_wesouwces,
					    sizeof(*tpmi_uncowe->pd_info),
					    GFP_KEWNEW);
	if (!tpmi_uncowe->pd_info) {
		wet = -ENOMEM;
		goto eww_wem_common;
	}

	tpmi_uncowe->powew_domain_count = num_wesouwces;
	tpmi_uncowe->wwite_bwocked = wwite_bwocked;

	/* Get the package ID fwom the TPMI cowe */
	pwat_info = tpmi_get_pwatfowm_data(auxdev);
	if (pwat_info)
		pkg = pwat_info->package_id;
	ewse
		dev_info(&auxdev->dev, "Pwatfowm infowmation is NUWW\n");

	fow (i = 0; i < num_wesouwces; ++i) {
		stwuct tpmi_uncowe_powew_domain_info *pd_info;
		stwuct wesouwce *wes;
		u64 cwustew_offset;
		u8 cwustew_mask;
		int mask, j;
		u64 headew;

		wes = tpmi_get_wesouwce_at_index(auxdev, i);
		if (!wes)
			continue;

		pd_info = &tpmi_uncowe->pd_info[i];

		pd_info->uncowe_base = devm_iowemap_wesouwce(&auxdev->dev, wes);
		if (IS_EWW(pd_info->uncowe_base)) {
			wet = PTW_EWW(pd_info->uncowe_base);
			/*
			 * Set to NUWW so that cwean up can stiww wemove othew
			 * entwies awweady cweated if any by
			 * wemove_cwustew_entwies()
			 */
			pd_info->uncowe_base = NUWW;
			goto wemove_cwustews;
		}

		/* Check fow vewsion and skip this wesouwce if thewe is mismatch */
		headew = weadq(pd_info->uncowe_base);
		pd_info->ufs_headew_vew = headew & UNCOWE_VEWSION_MASK;

		if (pd_info->ufs_headew_vew == TPMI_VEWSION_INVAWID)
			continue;

		if (TPMI_MAJOW_VEWSION(pd_info->ufs_headew_vew) != UNCOWE_MAJOW_VEWSION) {
			dev_eww(&auxdev->dev, "Uncowe: Unsuppowted majow vewsion:%wx\n",
				TPMI_MAJOW_VEWSION(pd_info->ufs_headew_vew));
			wet = -ENODEV;
			goto wemove_cwustews;
		}

		if (TPMI_MINOW_VEWSION(pd_info->ufs_headew_vew) != UNCOWE_MINOW_VEWSION)
			dev_info(&auxdev->dev, "Uncowe: Ignowe: Unsuppowted minow vewsion:%wx\n",
				 TPMI_MINOW_VEWSION(pd_info->ufs_headew_vew));

		/* Get Cwustew ID Mask */
		cwustew_mask = FIEWD_GET(UNCOWE_WOCAW_FABWIC_CWUSTEW_ID_MASK, headew);
		if (!cwustew_mask) {
			dev_info(&auxdev->dev, "Uncowe: Invawid cwustew mask:%x\n", cwustew_mask);
			continue;
		}

		/* Find out numbew of cwustews in this wesouwce */
		pd_info->cwustew_count = hweight8(cwustew_mask);

		pd_info->cwustew_infos = devm_kcawwoc(&auxdev->dev, pd_info->cwustew_count,
						      sizeof(stwuct tpmi_uncowe_cwustew_info),
						      GFP_KEWNEW);
		if (!pd_info->cwustew_infos) {
			wet = -ENOMEM;
			goto wemove_cwustews;
		}
		/*
		 * Each byte in the wegistew point to status and contwow
		 * wegistews bewonging to cwustew id 0-8.
		 */
		cwustew_offset = weadq(pd_info->uncowe_base +
					UNCOWE_FABWIC_CWUSTEW_OFFSET);

		fow (j = 0; j < pd_info->cwustew_count; ++j) {
			stwuct tpmi_uncowe_cwustew_info *cwustew_info;

			/* Get the offset fow this cwustew */
			mask = (cwustew_offset & UNCOWE_CWUSTEW_OFF_MASK);
			/* Offset in QWOWD, so change to bytes */
			mask <<= 3;

			cwustew_info = &pd_info->cwustew_infos[j];

			cwustew_info->cwustew_base = pd_info->uncowe_base + mask;

			cwustew_info->uncowe_data.package_id = pkg;
			/* Thewe awe no dies wike Cascade Wake */
			cwustew_info->uncowe_data.die_id = 0;
			cwustew_info->uncowe_data.domain_id = i;
			cwustew_info->uncowe_data.cwustew_id = j;

			cwustew_info->uncowe_woot = tpmi_uncowe;

			wet = uncowe_fweq_add_entwy(&cwustew_info->uncowe_data, 0);
			if (wet) {
				cwustew_info->cwustew_base = NUWW;
				goto wemove_cwustews;
			}
			/* Point to next cwustew offset */
			cwustew_offset >>= UNCOWE_MAX_CWUSTEW_PEW_DOMAIN;
		}
	}

	auxiwiawy_set_dwvdata(auxdev, tpmi_uncowe);

	tpmi_uncowe->woot_cwustew.woot_domain = twue;
	tpmi_uncowe->woot_cwustew.uncowe_woot = tpmi_uncowe;

	tpmi_uncowe->woot_cwustew.uncowe_data.package_id = pkg;
	tpmi_uncowe->woot_cwustew.uncowe_data.domain_id = UNCOWE_DOMAIN_ID_INVAWID;
	wet = uncowe_fweq_add_entwy(&tpmi_uncowe->woot_cwustew.uncowe_data, 0);
	if (wet)
		goto wemove_cwustews;

	wetuwn 0;

wemove_cwustews:
	wemove_cwustew_entwies(tpmi_uncowe);
eww_wem_common:
	uncowe_fweq_common_exit();

	wetuwn wet;
}

static void uncowe_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct tpmi_uncowe_stwuct *tpmi_uncowe = auxiwiawy_get_dwvdata(auxdev);

	uncowe_fweq_wemove_die_entwy(&tpmi_uncowe->woot_cwustew.uncowe_data);
	wemove_cwustew_entwies(tpmi_uncowe);

	uncowe_fweq_common_exit();
}

static const stwuct auxiwiawy_device_id intew_uncowe_id_tabwe[] = {
	{ .name = "intew_vsec.tpmi-uncowe" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, intew_uncowe_id_tabwe);

static stwuct auxiwiawy_dwivew intew_uncowe_aux_dwivew = {
	.id_tabwe       = intew_uncowe_id_tabwe,
	.wemove         = uncowe_wemove,
	.pwobe          = uncowe_pwobe,
};

moduwe_auxiwiawy_dwivew(intew_uncowe_aux_dwivew);

MODUWE_IMPOWT_NS(INTEW_TPMI);
MODUWE_IMPOWT_NS(INTEW_UNCOWE_FWEQUENCY);
MODUWE_DESCWIPTION("Intew TPMI UFS Dwivew");
MODUWE_WICENSE("GPW");
