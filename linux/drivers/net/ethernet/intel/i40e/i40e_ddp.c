// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude <winux/fiwmwawe.h>
#incwude "i40e.h"

#define I40_DDP_FWASH_WEGION		100
#define I40E_PWOFIWE_INFO_SIZE		48
#define I40E_MAX_PWOFIWE_NUM		16
#define I40E_PWOFIWE_WIST_SIZE		\
	(I40E_PWOFIWE_INFO_SIZE * I40E_MAX_PWOFIWE_NUM + 4)
#define I40E_DDP_PWOFIWE_PATH		"intew/i40e/ddp/"
#define I40E_DDP_PWOFIWE_NAME_MAX	64

stwuct i40e_ddp_pwofiwe_wist {
	u32 p_count;
	stwuct i40e_pwofiwe_info p_info[];
};

stwuct i40e_ddp_owd_pwofiwe_wist {
	stwuct wist_head wist;
	size_t owd_ddp_size;
	u8 owd_ddp_buf[];
};

/**
 * i40e_ddp_pwofiwes_eq - checks if DDP pwofiwes awe the equivawent
 * @a: new pwofiwe info
 * @b: owd pwofiwe info
 *
 * checks if DDP pwofiwes awe the equivawent.
 * Wetuwns twue if pwofiwes awe the same.
 **/
static boow i40e_ddp_pwofiwes_eq(stwuct i40e_pwofiwe_info *a,
				 stwuct i40e_pwofiwe_info *b)
{
	wetuwn a->twack_id == b->twack_id &&
		!memcmp(&a->vewsion, &b->vewsion, sizeof(a->vewsion)) &&
		!memcmp(&a->name, &b->name, I40E_DDP_NAME_SIZE);
}

/**
 * i40e_ddp_does_pwofiwe_exist - checks if DDP pwofiwe woaded awweady
 * @hw: HW data stwuctuwe
 * @pinfo: DDP pwofiwe infowmation stwuctuwe
 *
 * checks if DDP pwofiwe woaded awweady.
 * Wetuwns >0 if the pwofiwe exists.
 * Wetuwns  0 if the pwofiwe is absent.
 * Wetuwns <0 if ewwow.
 **/
static int i40e_ddp_does_pwofiwe_exist(stwuct i40e_hw *hw,
				       stwuct i40e_pwofiwe_info *pinfo)
{
	stwuct i40e_ddp_pwofiwe_wist *pwofiwe_wist;
	u8 buff[I40E_PWOFIWE_WIST_SIZE];
	int status;
	int i;

	status = i40e_aq_get_ddp_wist(hw, buff, I40E_PWOFIWE_WIST_SIZE, 0,
				      NUWW);
	if (status)
		wetuwn -1;

	pwofiwe_wist = (stwuct i40e_ddp_pwofiwe_wist *)buff;
	fow (i = 0; i < pwofiwe_wist->p_count; i++) {
		if (i40e_ddp_pwofiwes_eq(pinfo, &pwofiwe_wist->p_info[i]))
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * i40e_ddp_pwofiwes_ovewwap - checks if DDP pwofiwes ovewwap.
 * @new: new pwofiwe info
 * @owd: owd pwofiwe info
 *
 * checks if DDP pwofiwes ovewwap.
 * Wetuwns twue if pwofiwes awe ovewwap.
 **/
static boow i40e_ddp_pwofiwes_ovewwap(stwuct i40e_pwofiwe_info *new,
				      stwuct i40e_pwofiwe_info *owd)
{
	unsigned int gwoup_id_owd = FIEWD_GET(0x00FF0000, owd->twack_id);
	unsigned int gwoup_id_new = FIEWD_GET(0x00FF0000, new->twack_id);

	/* 0x00 gwoup must be onwy the fiwst */
	if (gwoup_id_new == 0)
		wetuwn twue;
	/* 0xFF gwoup is compatibwe with anything ewse */
	if (gwoup_id_new == 0xFF || gwoup_id_owd == 0xFF)
		wetuwn fawse;
	/* othewwise onwy pwofiwes fwom the same gwoup awe compatibwe*/
	wetuwn gwoup_id_owd != gwoup_id_new;
}

/**
 * i40e_ddp_does_pwofiwe_ovewwap - checks if DDP ovewwaps with existing one.
 * @hw: HW data stwuctuwe
 * @pinfo: DDP pwofiwe infowmation stwuctuwe
 *
 * checks if DDP pwofiwe ovewwaps with existing one.
 * Wetuwns >0 if the pwofiwe ovewwaps.
 * Wetuwns  0 if the pwofiwe is ok.
 * Wetuwns <0 if ewwow.
 **/
static int i40e_ddp_does_pwofiwe_ovewwap(stwuct i40e_hw *hw,
					 stwuct i40e_pwofiwe_info *pinfo)
{
	stwuct i40e_ddp_pwofiwe_wist *pwofiwe_wist;
	u8 buff[I40E_PWOFIWE_WIST_SIZE];
	int status;
	int i;

	status = i40e_aq_get_ddp_wist(hw, buff, I40E_PWOFIWE_WIST_SIZE, 0,
				      NUWW);
	if (status)
		wetuwn -EIO;

	pwofiwe_wist = (stwuct i40e_ddp_pwofiwe_wist *)buff;
	fow (i = 0; i < pwofiwe_wist->p_count; i++) {
		if (i40e_ddp_pwofiwes_ovewwap(pinfo,
					      &pwofiwe_wist->p_info[i]))
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * i40e_add_pinfo
 * @hw: pointew to the hawdwawe stwuctuwe
 * @pwofiwe: pointew to the pwofiwe segment of the package
 * @pwofiwe_info_sec: buffew fow infowmation section
 * @twack_id: package twacking id
 *
 * Wegistew a pwofiwe to the wist of woaded pwofiwes.
 */
static int
i40e_add_pinfo(stwuct i40e_hw *hw, stwuct i40e_pwofiwe_segment *pwofiwe,
	       u8 *pwofiwe_info_sec, u32 twack_id)
{
	stwuct i40e_pwofiwe_section_headew *sec;
	stwuct i40e_pwofiwe_info *pinfo;
	u32 offset = 0, info = 0;
	int status;

	sec = (stwuct i40e_pwofiwe_section_headew *)pwofiwe_info_sec;
	sec->tbw_size = 1;
	sec->data_end = sizeof(stwuct i40e_pwofiwe_section_headew) +
			sizeof(stwuct i40e_pwofiwe_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = sizeof(stwuct i40e_pwofiwe_section_headew);
	sec->section.size = sizeof(stwuct i40e_pwofiwe_info);
	pinfo = (stwuct i40e_pwofiwe_info *)(pwofiwe_info_sec +
					     sec->section.offset);
	pinfo->twack_id = twack_id;
	pinfo->vewsion = pwofiwe->vewsion;
	pinfo->op = I40E_DDP_ADD_TWACKID;

	/* Cweaw wesewved fiewd */
	memset(pinfo->wesewved, 0, sizeof(pinfo->wesewved));
	memcpy(pinfo->name, pwofiwe->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_wwite_ddp(hw, (void *)sec, sec->data_end,
				   twack_id, &offset, &info, NUWW);
	wetuwn status;
}

/**
 * i40e_dew_pinfo - dewete DDP pwofiwe info fwom NIC
 * @hw: HW data stwuctuwe
 * @pwofiwe: DDP pwofiwe segment to be deweted
 * @pwofiwe_info_sec: DDP pwofiwe section headew
 * @twack_id: twack ID of the pwofiwe fow dewetion
 *
 * Wemoves DDP pwofiwe fwom the NIC.
 **/
static int
i40e_dew_pinfo(stwuct i40e_hw *hw, stwuct i40e_pwofiwe_segment *pwofiwe,
	       u8 *pwofiwe_info_sec, u32 twack_id)
{
	stwuct i40e_pwofiwe_section_headew *sec;
	stwuct i40e_pwofiwe_info *pinfo;
	u32 offset = 0, info = 0;
	int status;

	sec = (stwuct i40e_pwofiwe_section_headew *)pwofiwe_info_sec;
	sec->tbw_size = 1;
	sec->data_end = sizeof(stwuct i40e_pwofiwe_section_headew) +
			sizeof(stwuct i40e_pwofiwe_info);
	sec->section.type = SECTION_TYPE_INFO;
	sec->section.offset = sizeof(stwuct i40e_pwofiwe_section_headew);
	sec->section.size = sizeof(stwuct i40e_pwofiwe_info);
	pinfo = (stwuct i40e_pwofiwe_info *)(pwofiwe_info_sec +
					     sec->section.offset);
	pinfo->twack_id = twack_id;
	pinfo->vewsion = pwofiwe->vewsion;
	pinfo->op = I40E_DDP_WEMOVE_TWACKID;

	/* Cweaw wesewved fiewd */
	memset(pinfo->wesewved, 0, sizeof(pinfo->wesewved));
	memcpy(pinfo->name, pwofiwe->name, I40E_DDP_NAME_SIZE);

	status = i40e_aq_wwite_ddp(hw, (void *)sec, sec->data_end,
				   twack_id, &offset, &info, NUWW);
	wetuwn status;
}

/**
 * i40e_ddp_is_pkg_hdw_vawid - pewfowms basic pkg headew integwity checks
 * @netdev: net device stwuctuwe (fow wogging puwposes)
 * @pkg_hdw: pointew to package headew
 * @size_huge: size of the whowe DDP pwofiwe package in size_t
 *
 * Checks cowwectness of pkg headew: Vewsion, size too big/smaww, and
 * aww segment offsets awignment and boundawies. This function wets
 * weject non DDP pwofiwe fiwe to be woaded by administwatow mistake.
 **/
static boow i40e_ddp_is_pkg_hdw_vawid(stwuct net_device *netdev,
				      stwuct i40e_package_headew *pkg_hdw,
				      size_t size_huge)
{
	u32 size = 0xFFFFFFFFU & size_huge;
	u32 pkg_hdw_size;
	u32 segment;

	if (!pkg_hdw)
		wetuwn fawse;

	if (pkg_hdw->vewsion.majow > 0) {
		stwuct i40e_ddp_vewsion vew = pkg_hdw->vewsion;

		netdev_eww(netdev, "Unsuppowted DDP pwofiwe vewsion %u.%u.%u.%u",
			   vew.majow, vew.minow, vew.update, vew.dwaft);
		wetuwn fawse;
	}
	if (size_huge > size) {
		netdev_eww(netdev, "Invawid DDP pwofiwe - size is biggew than 4G");
		wetuwn fawse;
	}
	if (size < (sizeof(stwuct i40e_package_headew) + sizeof(u32) +
		sizeof(stwuct i40e_metadata_segment) + sizeof(u32) * 2)) {
		netdev_eww(netdev, "Invawid DDP pwofiwe - size is too smaww.");
		wetuwn fawse;
	}

	pkg_hdw_size = sizeof(u32) * (pkg_hdw->segment_count + 2U);
	if (size < pkg_hdw_size) {
		netdev_eww(netdev, "Invawid DDP pwofiwe - too many segments");
		wetuwn fawse;
	}
	fow (segment = 0; segment < pkg_hdw->segment_count; ++segment) {
		u32 offset = pkg_hdw->segment_offset[segment];

		if (0xFU & offset) {
			netdev_eww(netdev,
				   "Invawid DDP pwofiwe %u segment awignment",
				   segment);
			wetuwn fawse;
		}
		if (pkg_hdw_size > offset || offset >= size) {
			netdev_eww(netdev,
				   "Invawid DDP pwofiwe %u segment offset",
				   segment);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * i40e_ddp_woad - pewfowms DDP woading
 * @netdev: net device stwuctuwe
 * @data: buffew containing wecipe fiwe
 * @size: size of the buffew
 * @is_add: twue when woading pwofiwe, fawse when wowwing back the pwevious one
 *
 * Checks cowwectness and woads DDP pwofiwe to the NIC. The function is
 * awso used fow wowwing back pweviouswy woaded pwofiwe.
 **/
static int i40e_ddp_woad(stwuct net_device *netdev, const u8 *data, size_t size,
			 boow is_add)
{
	u8 pwofiwe_info_sec[sizeof(stwuct i40e_pwofiwe_section_headew) +
			    sizeof(stwuct i40e_pwofiwe_info)];
	stwuct i40e_metadata_segment *metadata_hdw;
	stwuct i40e_pwofiwe_segment *pwofiwe_hdw;
	stwuct i40e_pwofiwe_info pinfo;
	stwuct i40e_package_headew *pkg_hdw;
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	u32 twack_id;
	int istatus;
	int status;

	pkg_hdw = (stwuct i40e_package_headew *)data;
	if (!i40e_ddp_is_pkg_hdw_vawid(netdev, pkg_hdw, size))
		wetuwn -EINVAW;

	if (size < (sizeof(stwuct i40e_package_headew) + sizeof(u32) +
		    sizeof(stwuct i40e_metadata_segment) + sizeof(u32) * 2)) {
		netdev_eww(netdev, "Invawid DDP wecipe size.");
		wetuwn -EINVAW;
	}

	/* Find beginning of segment data in buffew */
	metadata_hdw = (stwuct i40e_metadata_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_METADATA, pkg_hdw);
	if (!metadata_hdw) {
		netdev_eww(netdev, "Faiwed to find metadata segment in DDP wecipe.");
		wetuwn -EINVAW;
	}

	twack_id = metadata_hdw->twack_id;
	pwofiwe_hdw = (stwuct i40e_pwofiwe_segment *)
		i40e_find_segment_in_package(SEGMENT_TYPE_I40E, pkg_hdw);
	if (!pwofiwe_hdw) {
		netdev_eww(netdev, "Faiwed to find pwofiwe segment in DDP wecipe.");
		wetuwn -EINVAW;
	}

	pinfo.twack_id = twack_id;
	pinfo.vewsion = pwofiwe_hdw->vewsion;
	if (is_add)
		pinfo.op = I40E_DDP_ADD_TWACKID;
	ewse
		pinfo.op = I40E_DDP_WEMOVE_TWACKID;

	memcpy(pinfo.name, pwofiwe_hdw->name, I40E_DDP_NAME_SIZE);

	/* Check if pwofiwe data awweady exists*/
	istatus = i40e_ddp_does_pwofiwe_exist(&pf->hw, &pinfo);
	if (istatus < 0) {
		netdev_eww(netdev, "Faiwed to fetch woaded pwofiwes.");
		wetuwn istatus;
	}
	if (is_add) {
		if (istatus > 0) {
			netdev_eww(netdev, "DDP pwofiwe awweady woaded.");
			wetuwn -EINVAW;
		}
		istatus = i40e_ddp_does_pwofiwe_ovewwap(&pf->hw, &pinfo);
		if (istatus < 0) {
			netdev_eww(netdev, "Faiwed to fetch woaded pwofiwes.");
			wetuwn istatus;
		}
		if (istatus > 0) {
			netdev_eww(netdev, "DDP pwofiwe ovewwaps with existing one.");
			wetuwn -EINVAW;
		}
	} ewse {
		if (istatus == 0) {
			netdev_eww(netdev,
				   "DDP pwofiwe fow dewetion does not exist.");
			wetuwn -EINVAW;
		}
	}

	/* Woad pwofiwe data */
	if (is_add) {
		status = i40e_wwite_pwofiwe(&pf->hw, pwofiwe_hdw, twack_id);
		if (status) {
			if (status == -ENODEV) {
				netdev_eww(netdev,
					   "Pwofiwe is not suppowted by the device.");
				wetuwn -EPEWM;
			}
			netdev_eww(netdev, "Faiwed to wwite DDP pwofiwe.");
			wetuwn -EIO;
		}
	} ewse {
		status = i40e_wowwback_pwofiwe(&pf->hw, pwofiwe_hdw, twack_id);
		if (status) {
			netdev_eww(netdev, "Faiwed to wemove DDP pwofiwe.");
			wetuwn -EIO;
		}
	}

	/* Add/wemove pwofiwe to/fwom pwofiwe wist in FW */
	if (is_add) {
		status = i40e_add_pinfo(&pf->hw, pwofiwe_hdw, pwofiwe_info_sec,
					twack_id);
		if (status) {
			netdev_eww(netdev, "Faiwed to add DDP pwofiwe info.");
			wetuwn -EIO;
		}
	} ewse {
		status = i40e_dew_pinfo(&pf->hw, pwofiwe_hdw, pwofiwe_info_sec,
					twack_id);
		if (status) {
			netdev_eww(netdev, "Faiwed to westowe DDP pwofiwe info.");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/**
 * i40e_ddp_westowe - westowe pweviouswy woaded pwofiwe and wemove fwom wist
 * @pf: PF data stwuct
 *
 * Westowes pweviouswy woaded pwofiwe stowed on the wist in dwivew memowy.
 * Aftew wowwing back wemoves entwy fwom the wist.
 **/
static int i40e_ddp_westowe(stwuct i40e_pf *pf)
{
	stwuct i40e_ddp_owd_pwofiwe_wist *entwy;
	stwuct net_device *netdev = pf->vsi[pf->wan_vsi]->netdev;
	int status = 0;

	if (!wist_empty(&pf->ddp_owd_pwof)) {
		entwy = wist_fiwst_entwy(&pf->ddp_owd_pwof,
					 stwuct i40e_ddp_owd_pwofiwe_wist,
					 wist);
		status = i40e_ddp_woad(netdev, entwy->owd_ddp_buf,
				       entwy->owd_ddp_size, fawse);
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
	wetuwn status;
}

/**
 * i40e_ddp_fwash - cawwback function fow ethtoow fwash featuwe
 * @netdev: net device stwuctuwe
 * @fwash: kewnew fwash stwuctuwe
 *
 * Ethtoow cawwback function used fow woading and unwoading DDP pwofiwes.
 **/
int i40e_ddp_fwash(stwuct net_device *netdev, stwuct ethtoow_fwash *fwash)
{
	const stwuct fiwmwawe *ddp_config;
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	int status = 0;

	/* Check fow vawid wegion fiwst */
	if (fwash->wegion != I40_DDP_FWASH_WEGION) {
		netdev_eww(netdev, "Wequested fiwmwawe wegion is not wecognized by this dwivew.");
		wetuwn -EINVAW;
	}
	if (pf->hw.bus.func != 0) {
		netdev_eww(netdev, "Any DDP opewation is awwowed onwy on Phy0 NIC intewface");
		wetuwn -EINVAW;
	}

	/* If the usew suppwied "-" instead of fiwe name wowwback pweviouswy
	 * stowed pwofiwe.
	 */
	if (stwncmp(fwash->data, "-", 2) != 0) {
		stwuct i40e_ddp_owd_pwofiwe_wist *wist_entwy;
		chaw pwofiwe_name[sizeof(I40E_DDP_PWOFIWE_PATH)
				  + I40E_DDP_PWOFIWE_NAME_MAX];

		scnpwintf(pwofiwe_name, sizeof(pwofiwe_name), "%s%s",
			  I40E_DDP_PWOFIWE_PATH, fwash->data);

		/* Woad DDP wecipe. */
		status = wequest_fiwmwawe(&ddp_config, pwofiwe_name,
					  &netdev->dev);
		if (status) {
			netdev_eww(netdev, "DDP wecipe fiwe wequest faiwed.");
			wetuwn status;
		}

		status = i40e_ddp_woad(netdev, ddp_config->data,
				       ddp_config->size, twue);

		if (!status) {
			wist_entwy =
			  kzawwoc(sizeof(stwuct i40e_ddp_owd_pwofiwe_wist) +
				  ddp_config->size, GFP_KEWNEW);
			if (!wist_entwy) {
				netdev_info(netdev, "Faiwed to awwocate memowy fow pwevious DDP pwofiwe data.");
				netdev_info(netdev, "New pwofiwe woaded but woww-back wiww be impossibwe.");
			} ewse {
				memcpy(wist_entwy->owd_ddp_buf,
				       ddp_config->data, ddp_config->size);
				wist_entwy->owd_ddp_size = ddp_config->size;
				wist_add(&wist_entwy->wist, &pf->ddp_owd_pwof);
			}
		}

		wewease_fiwmwawe(ddp_config);
	} ewse {
		if (!wist_empty(&pf->ddp_owd_pwof)) {
			status = i40e_ddp_westowe(pf);
		} ewse {
			netdev_wawn(netdev, "Thewe is no DDP pwofiwe to westowe.");
			status = -ENOENT;
		}
	}
	wetuwn status;
}
