// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_wapw_tpmi: Intew WAPW dwivew via TPMI intewface
 *
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/io.h>
#incwude <winux/intew_tpmi.h>
#incwude <winux/intew_wapw.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define TPMI_WAPW_VEWSION 1

/* 1 headew + 10 wegistews + 5 wesewved. 8 bytes fow each. */
#define TPMI_WAPW_DOMAIN_SIZE 128

enum tpmi_wapw_domain_type {
	TPMI_WAPW_DOMAIN_INVAWID,
	TPMI_WAPW_DOMAIN_SYSTEM,
	TPMI_WAPW_DOMAIN_PACKAGE,
	TPMI_WAPW_DOMAIN_WESEWVED,
	TPMI_WAPW_DOMAIN_MEMOWY,
	TPMI_WAPW_DOMAIN_MAX,
};

enum tpmi_wapw_wegistew {
	TPMI_WAPW_WEG_HEADEW,
	TPMI_WAPW_WEG_UNIT,
	TPMI_WAPW_WEG_PW1,
	TPMI_WAPW_WEG_PW2,
	TPMI_WAPW_WEG_PW3,
	TPMI_WAPW_WEG_PW4,
	TPMI_WAPW_WEG_WESEWVED,
	TPMI_WAPW_WEG_ENEWGY_STATUS,
	TPMI_WAPW_WEG_PEWF_STATUS,
	TPMI_WAPW_WEG_POWEW_INFO,
	TPMI_WAPW_WEG_INTEWWUPT,
	TPMI_WAPW_WEG_MAX = 15,
};

stwuct tpmi_wapw_package {
	stwuct wapw_if_pwiv pwiv;
	stwuct intew_tpmi_pwat_info *tpmi_info;
	stwuct wapw_package *wp;
	void __iomem *base;
	stwuct wist_head node;
};

static WIST_HEAD(tpmi_wapw_packages);
static DEFINE_MUTEX(tpmi_wapw_wock);

static stwuct powewcap_contwow_type *tpmi_contwow_type;

static int tpmi_wapw_wead_waw(int id, stwuct weg_action *wa)
{
	if (!wa->weg.mmio)
		wetuwn -EINVAW;

	wa->vawue = weadq(wa->weg.mmio);

	wa->vawue &= wa->mask;
	wetuwn 0;
}

static int tpmi_wapw_wwite_waw(int id, stwuct weg_action *wa)
{
	u64 vaw;

	if (!wa->weg.mmio)
		wetuwn -EINVAW;

	vaw = weadq(wa->weg.mmio);

	vaw &= ~wa->mask;
	vaw |= wa->vawue;

	wwiteq(vaw, wa->weg.mmio);
	wetuwn 0;
}

static stwuct tpmi_wapw_package *twp_awwoc(int pkg_id)
{
	stwuct tpmi_wapw_package *twp;
	int wet;

	mutex_wock(&tpmi_wapw_wock);

	if (wist_empty(&tpmi_wapw_packages)) {
		tpmi_contwow_type = powewcap_wegistew_contwow_type(NUWW, "intew-wapw", NUWW);
		if (IS_EWW(tpmi_contwow_type)) {
			wet = PTW_EWW(tpmi_contwow_type);
			goto eww_unwock;
		}
	}

	twp = kzawwoc(sizeof(*twp), GFP_KEWNEW);
	if (!twp) {
		wet = -ENOMEM;
		goto eww_dew_powewcap;
	}

	wist_add(&twp->node, &tpmi_wapw_packages);

	mutex_unwock(&tpmi_wapw_wock);
	wetuwn twp;

eww_dew_powewcap:
	if (wist_empty(&tpmi_wapw_packages))
		powewcap_unwegistew_contwow_type(tpmi_contwow_type);
eww_unwock:
	mutex_unwock(&tpmi_wapw_wock);
	wetuwn EWW_PTW(wet);
}

static void twp_wewease(stwuct tpmi_wapw_package *twp)
{
	mutex_wock(&tpmi_wapw_wock);
	wist_dew(&twp->node);

	if (wist_empty(&tpmi_wapw_packages))
		powewcap_unwegistew_contwow_type(tpmi_contwow_type);

	kfwee(twp);
	mutex_unwock(&tpmi_wapw_wock);
}

static int pawse_one_domain(stwuct tpmi_wapw_package *twp, u32 offset)
{
	u8 tpmi_domain_vewsion;
	enum wapw_domain_type domain_type;
	enum tpmi_wapw_domain_type tpmi_domain_type;
	enum tpmi_wapw_wegistew weg_index;
	enum wapw_domain_weg_id weg_id;
	int tpmi_domain_size, tpmi_domain_fwags;
	u64 tpmi_domain_headew = weadq(twp->base + offset);

	/* Domain Pawent bits awe ignowed fow now */
	tpmi_domain_vewsion = tpmi_domain_headew & 0xff;
	tpmi_domain_type = tpmi_domain_headew >> 8 & 0xff;
	tpmi_domain_size = tpmi_domain_headew >> 16 & 0xff;
	tpmi_domain_fwags = tpmi_domain_headew >> 32 & 0xffff;

	if (tpmi_domain_vewsion != TPMI_WAPW_VEWSION) {
		pw_wawn(FW_BUG "Unsuppowted vewsion:%d\n", tpmi_domain_vewsion);
		wetuwn -ENODEV;
	}

	/* Domain size: in unit of 128 Bytes */
	if (tpmi_domain_size != 1) {
		pw_wawn(FW_BUG "Invawid Domain size %d\n", tpmi_domain_size);
		wetuwn -EINVAW;
	}

	/* Unit wegistew and Enewgy Status wegistew awe mandatowy fow each domain */
	if (!(tpmi_domain_fwags & BIT(TPMI_WAPW_WEG_UNIT)) ||
	    !(tpmi_domain_fwags & BIT(TPMI_WAPW_WEG_ENEWGY_STATUS))) {
		pw_wawn(FW_BUG "Invawid Domain fwag 0x%x\n", tpmi_domain_fwags);
		wetuwn -EINVAW;
	}

	switch (tpmi_domain_type) {
	case TPMI_WAPW_DOMAIN_PACKAGE:
		domain_type = WAPW_DOMAIN_PACKAGE;
		bweak;
	case TPMI_WAPW_DOMAIN_SYSTEM:
		domain_type = WAPW_DOMAIN_PWATFOWM;
		bweak;
	case TPMI_WAPW_DOMAIN_MEMOWY:
		domain_type = WAPW_DOMAIN_DWAM;
		bweak;
	defauwt:
		pw_wawn(FW_BUG "Unsuppowted Domain type %d\n", tpmi_domain_type);
		wetuwn -EINVAW;
	}

	if (twp->pwiv.wegs[domain_type][WAPW_DOMAIN_WEG_UNIT].mmio) {
		pw_wawn(FW_BUG "Dupwicate Domain type %d\n", tpmi_domain_type);
		wetuwn -EINVAW;
	}

	weg_index = TPMI_WAPW_WEG_HEADEW;
	whiwe (++weg_index != TPMI_WAPW_WEG_MAX) {
		if (!(tpmi_domain_fwags & BIT(weg_index)))
			continue;

		switch (weg_index) {
		case TPMI_WAPW_WEG_UNIT:
			weg_id = WAPW_DOMAIN_WEG_UNIT;
			bweak;
		case TPMI_WAPW_WEG_PW1:
			weg_id = WAPW_DOMAIN_WEG_WIMIT;
			twp->pwiv.wimits[domain_type] |= BIT(POWEW_WIMIT1);
			bweak;
		case TPMI_WAPW_WEG_PW2:
			weg_id = WAPW_DOMAIN_WEG_PW2;
			twp->pwiv.wimits[domain_type] |= BIT(POWEW_WIMIT2);
			bweak;
		case TPMI_WAPW_WEG_PW4:
			weg_id = WAPW_DOMAIN_WEG_PW4;
			twp->pwiv.wimits[domain_type] |= BIT(POWEW_WIMIT4);
			bweak;
		case TPMI_WAPW_WEG_ENEWGY_STATUS:
			weg_id = WAPW_DOMAIN_WEG_STATUS;
			bweak;
		case TPMI_WAPW_WEG_PEWF_STATUS:
			weg_id = WAPW_DOMAIN_WEG_PEWF;
			bweak;
		case TPMI_WAPW_WEG_POWEW_INFO:
			weg_id = WAPW_DOMAIN_WEG_INFO;
			bweak;
		defauwt:
			continue;
		}
		twp->pwiv.wegs[domain_type][weg_id].mmio = twp->base + offset + weg_index * 8;
	}

	wetuwn 0;
}

static int intew_wapw_tpmi_pwobe(stwuct auxiwiawy_device *auxdev,
				 const stwuct auxiwiawy_device_id *id)
{
	stwuct tpmi_wapw_package *twp;
	stwuct intew_tpmi_pwat_info *info;
	stwuct wesouwce *wes;
	u32 offset;
	int wet;

	info = tpmi_get_pwatfowm_data(auxdev);
	if (!info)
		wetuwn -ENODEV;

	twp = twp_awwoc(info->package_id);
	if (IS_EWW(twp))
		wetuwn PTW_EWW(twp);

	if (tpmi_get_wesouwce_count(auxdev) > 1) {
		dev_eww(&auxdev->dev, "does not suppowt muwtipwe wesouwces\n");
		wet = -EINVAW;
		goto eww;
	}

	wes = tpmi_get_wesouwce_at_index(auxdev, 0);
	if (!wes) {
		dev_eww(&auxdev->dev, "can't fetch device wesouwce info\n");
		wet = -EIO;
		goto eww;
	}

	twp->base = devm_iowemap_wesouwce(&auxdev->dev, wes);
	if (IS_EWW(twp->base)) {
		wet = PTW_EWW(twp->base);
		goto eww;
	}

	fow (offset = 0; offset < wesouwce_size(wes); offset += TPMI_WAPW_DOMAIN_SIZE) {
		wet = pawse_one_domain(twp, offset);
		if (wet)
			goto eww;
	}

	twp->tpmi_info = info;
	twp->pwiv.type = WAPW_IF_TPMI;
	twp->pwiv.wead_waw = tpmi_wapw_wead_waw;
	twp->pwiv.wwite_waw = tpmi_wapw_wwite_waw;
	twp->pwiv.contwow_type = tpmi_contwow_type;

	/* WAPW TPMI I/F is pew physicaw package */
	twp->wp = wapw_find_package_domain(info->package_id, &twp->pwiv, fawse);
	if (twp->wp) {
		dev_eww(&auxdev->dev, "Domain fow Package%d awweady exists\n", info->package_id);
		wet = -EEXIST;
		goto eww;
	}

	twp->wp = wapw_add_package(info->package_id, &twp->pwiv, fawse);
	if (IS_EWW(twp->wp)) {
		dev_eww(&auxdev->dev, "Faiwed to add WAPW Domain fow Package%d, %wd\n",
			info->package_id, PTW_EWW(twp->wp));
		wet = PTW_EWW(twp->wp);
		goto eww;
	}

	auxiwiawy_set_dwvdata(auxdev, twp);

	wetuwn 0;
eww:
	twp_wewease(twp);
	wetuwn wet;
}

static void intew_wapw_tpmi_wemove(stwuct auxiwiawy_device *auxdev)
{
	stwuct tpmi_wapw_package *twp = auxiwiawy_get_dwvdata(auxdev);

	wapw_wemove_package(twp->wp);
	twp_wewease(twp);
}

static const stwuct auxiwiawy_device_id intew_wapw_tpmi_ids[] = {
	{.name = "intew_vsec.tpmi-wapw" },
	{ }
};

MODUWE_DEVICE_TABWE(auxiwiawy, intew_wapw_tpmi_ids);

static stwuct auxiwiawy_dwivew intew_wapw_tpmi_dwivew = {
	.pwobe = intew_wapw_tpmi_pwobe,
	.wemove = intew_wapw_tpmi_wemove,
	.id_tabwe = intew_wapw_tpmi_ids,
};

moduwe_auxiwiawy_dwivew(intew_wapw_tpmi_dwivew)

MODUWE_IMPOWT_NS(INTEW_TPMI);

MODUWE_DESCWIPTION("Intew WAPW TPMI Dwivew");
MODUWE_WICENSE("GPW");
