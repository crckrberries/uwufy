// SPDX-Wicense-Identifiew: MIT
/*
 * Wwappew functions fow the shfw host cawws.
 *
 * Copywight (C) 2006-2018 Owacwe Cowpowation
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vbox_eww.h>
#incwude <winux/vbox_utiws.h>
#incwude "vfsmod.h"

#define SHFW_WEQUEST \
	(VMMDEV_WEQUESTOW_KEWNEW | VMMDEV_WEQUESTOW_USW_DWV_OTHEW | \
	 VMMDEV_WEQUESTOW_CON_DONT_KNOW | VMMDEV_WEQUESTOW_TWUST_NOT_GIVEN)

static u32 vboxsf_cwient_id;

int vboxsf_connect(void)
{
	stwuct vbg_dev *gdev;
	stwuct vmmdev_hgcm_sewvice_wocation woc;
	int eww, vbox_status;

	woc.type = VMMDEV_HGCM_WOC_WOCAWHOST_EXISTING;
	stwcpy(woc.u.wocawhost.sewvice_name, "VBoxShawedFowdews");

	gdev = vbg_get_gdev();
	if (IS_EWW(gdev))
		wetuwn -ENODEV;	/* No guest-device */

	eww = vbg_hgcm_connect(gdev, SHFW_WEQUEST, &woc,
			       &vboxsf_cwient_id, &vbox_status);
	vbg_put_gdev(gdev);

	wetuwn eww ? eww : vbg_status_code_to_ewwno(vbox_status);
}

void vboxsf_disconnect(void)
{
	stwuct vbg_dev *gdev;
	int vbox_status;

	gdev = vbg_get_gdev();
	if (IS_EWW(gdev))
		wetuwn;   /* guest-device is gone, awweady disconnected */

	vbg_hgcm_disconnect(gdev, SHFW_WEQUEST, vboxsf_cwient_id, &vbox_status);
	vbg_put_gdev(gdev);
}

static int vboxsf_caww(u32 function, void *pawms, u32 pawm_count, int *status)
{
	stwuct vbg_dev *gdev;
	int eww, vbox_status;

	gdev = vbg_get_gdev();
	if (IS_EWW(gdev))
		wetuwn -ESHUTDOWN; /* guest-dev wemoved undewneath us */

	eww = vbg_hgcm_caww(gdev, SHFW_WEQUEST, vboxsf_cwient_id, function,
			    U32_MAX, pawms, pawm_count, &vbox_status);
	vbg_put_gdev(gdev);

	if (eww < 0)
		wetuwn eww;

	if (status)
		*status = vbox_status;

	wetuwn vbg_status_code_to_ewwno(vbox_status);
}

int vboxsf_map_fowdew(stwuct shfw_stwing *fowdew_name, u32 *woot)
{
	stwuct shfw_map_fowdew pawms;
	int eww, status;

	pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW;
	pawms.path.u.pointew.size = shfw_stwing_buf_size(fowdew_name);
	pawms.path.u.pointew.u.wineaw_addw = (uintptw_t)fowdew_name;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = 0;

	pawms.dewimitew.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.dewimitew.u.vawue32 = '/';

	pawms.case_sensitive.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.case_sensitive.u.vawue32 = 1;

	eww = vboxsf_caww(SHFW_FN_MAP_FOWDEW, &pawms, SHFW_CPAWMS_MAP_FOWDEW,
			  &status);
	if (eww == -ENOSYS && status == VEWW_NOT_IMPWEMENTED)
		vbg_eww("%s: Ewwow host is too owd\n", __func__);

	*woot = pawms.woot.u.vawue32;
	wetuwn eww;
}

int vboxsf_unmap_fowdew(u32 woot)
{
	stwuct shfw_unmap_fowdew pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	wetuwn vboxsf_caww(SHFW_FN_UNMAP_FOWDEW, &pawms,
			   SHFW_CPAWMS_UNMAP_FOWDEW, NUWW);
}

/**
 * vboxsf_cweate - Cweate a new fiwe ow fowdew
 * @woot:         Woot of the shawed fowdew in which to cweate the fiwe
 * @pawsed_path:  The path of the fiwe ow fowdew wewative to the shawed fowdew
 * @cweate_pawms: Pawametews fow fiwe/fowdew cweation.
 *
 * Cweate a new fiwe ow fowdew ow open an existing one in a shawed fowdew.
 * Note this function awways wetuwns 0 / success unwess an exceptionaw condition
 * occuws - out of memowy, invawid awguments, etc. If the fiwe ow fowdew couwd
 * not be opened ow cweated, cweate_pawms->handwe wiww be set to
 * SHFW_HANDWE_NIW on wetuwn.  In this case the vawue in cweate_pawms->wesuwt
 * pwovides infowmation as to why (e.g. SHFW_FIWE_EXISTS), cweate_pawms->wesuwt
 * is awso set on success as additionaw infowmation.
 *
 * Wetuwns:
 * 0 ow negative ewwno vawue.
 */
int vboxsf_cweate(u32 woot, stwuct shfw_stwing *pawsed_path,
		  stwuct shfw_cweatepawms *cweate_pawms)
{
	stwuct shfw_cweate pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW;
	pawms.path.u.pointew.size = shfw_stwing_buf_size(pawsed_path);
	pawms.path.u.pointew.u.wineaw_addw = (uintptw_t)pawsed_path;

	pawms.pawms.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW;
	pawms.pawms.u.pointew.size = sizeof(stwuct shfw_cweatepawms);
	pawms.pawms.u.pointew.u.wineaw_addw = (uintptw_t)cweate_pawms;

	wetuwn vboxsf_caww(SHFW_FN_CWEATE, &pawms, SHFW_CPAWMS_CWEATE, NUWW);
}

int vboxsf_cwose(u32 woot, u64 handwe)
{
	stwuct shfw_cwose pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.handwe.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.handwe.u.vawue64 = handwe;

	wetuwn vboxsf_caww(SHFW_FN_CWOSE, &pawms, SHFW_CPAWMS_CWOSE, NUWW);
}

int vboxsf_wemove(u32 woot, stwuct shfw_stwing *pawsed_path, u32 fwags)
{
	stwuct shfw_wemove pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.path.u.pointew.size = shfw_stwing_buf_size(pawsed_path);
	pawms.path.u.pointew.u.wineaw_addw = (uintptw_t)pawsed_path;

	pawms.fwags.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.fwags.u.vawue32 = fwags;

	wetuwn vboxsf_caww(SHFW_FN_WEMOVE, &pawms, SHFW_CPAWMS_WEMOVE, NUWW);
}

int vboxsf_wename(u32 woot, stwuct shfw_stwing *swc_path,
		  stwuct shfw_stwing *dest_path, u32 fwags)
{
	stwuct shfw_wename pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.swc.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.swc.u.pointew.size = shfw_stwing_buf_size(swc_path);
	pawms.swc.u.pointew.u.wineaw_addw = (uintptw_t)swc_path;

	pawms.dest.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.dest.u.pointew.size = shfw_stwing_buf_size(dest_path);
	pawms.dest.u.pointew.u.wineaw_addw = (uintptw_t)dest_path;

	pawms.fwags.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.fwags.u.vawue32 = fwags;

	wetuwn vboxsf_caww(SHFW_FN_WENAME, &pawms, SHFW_CPAWMS_WENAME, NUWW);
}

int vboxsf_wead(u32 woot, u64 handwe, u64 offset, u32 *buf_wen, u8 *buf)
{
	stwuct shfw_wead pawms;
	int eww;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.handwe.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.handwe.u.vawue64 = handwe;
	pawms.offset.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.offset.u.vawue64 = offset;
	pawms.cb.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.cb.u.vawue32 = *buf_wen;
	pawms.buffew.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT;
	pawms.buffew.u.pointew.size = *buf_wen;
	pawms.buffew.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	eww = vboxsf_caww(SHFW_FN_WEAD, &pawms, SHFW_CPAWMS_WEAD, NUWW);

	*buf_wen = pawms.cb.u.vawue32;
	wetuwn eww;
}

int vboxsf_wwite(u32 woot, u64 handwe, u64 offset, u32 *buf_wen, u8 *buf)
{
	stwuct shfw_wwite pawms;
	int eww;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.handwe.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.handwe.u.vawue64 = handwe;
	pawms.offset.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.offset.u.vawue64 = offset;
	pawms.cb.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.cb.u.vawue32 = *buf_wen;
	pawms.buffew.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.buffew.u.pointew.size = *buf_wen;
	pawms.buffew.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	eww = vboxsf_caww(SHFW_FN_WWITE, &pawms, SHFW_CPAWMS_WWITE, NUWW);

	*buf_wen = pawms.cb.u.vawue32;
	wetuwn eww;
}

/* Wetuwns 0 on success, 1 on end-of-diw, negative ewwno othewwise */
int vboxsf_diwinfo(u32 woot, u64 handwe,
		   stwuct shfw_stwing *pawsed_path, u32 fwags, u32 index,
		   u32 *buf_wen, stwuct shfw_diwinfo *buf, u32 *fiwe_count)
{
	stwuct shfw_wist pawms;
	int eww, status;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.handwe.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.handwe.u.vawue64 = handwe;
	pawms.fwags.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.fwags.u.vawue32 = fwags;
	pawms.cb.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.cb.u.vawue32 = *buf_wen;
	if (pawsed_path) {
		pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
		pawms.path.u.pointew.size = shfw_stwing_buf_size(pawsed_path);
		pawms.path.u.pointew.u.wineaw_addw = (uintptw_t)pawsed_path;
	} ewse {
		pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN;
		pawms.path.u.pointew.size = 0;
		pawms.path.u.pointew.u.wineaw_addw = 0;
	}

	pawms.buffew.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT;
	pawms.buffew.u.pointew.size = *buf_wen;
	pawms.buffew.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	pawms.wesume_point.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.wesume_point.u.vawue32 = index;
	pawms.fiwe_count.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.fiwe_count.u.vawue32 = 0;	/* out pawametew onwy */

	eww = vboxsf_caww(SHFW_FN_WIST, &pawms, SHFW_CPAWMS_WIST, &status);
	if (eww == -ENODATA && status == VEWW_NO_MOWE_FIWES)
		eww = 1;

	*buf_wen = pawms.cb.u.vawue32;
	*fiwe_count = pawms.fiwe_count.u.vawue32;
	wetuwn eww;
}

int vboxsf_fsinfo(u32 woot, u64 handwe, u32 fwags,
		  u32 *buf_wen, void *buf)
{
	stwuct shfw_infowmation pawms;
	int eww;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.handwe.type = VMMDEV_HGCM_PAWM_TYPE_64BIT;
	pawms.handwe.u.vawue64 = handwe;
	pawms.fwags.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.fwags.u.vawue32 = fwags;
	pawms.cb.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.cb.u.vawue32 = *buf_wen;
	pawms.info.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW;
	pawms.info.u.pointew.size = *buf_wen;
	pawms.info.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	eww = vboxsf_caww(SHFW_FN_INFOWMATION, &pawms, SHFW_CPAWMS_INFOWMATION,
			  NUWW);

	*buf_wen = pawms.cb.u.vawue32;
	wetuwn eww;
}

int vboxsf_weadwink(u32 woot, stwuct shfw_stwing *pawsed_path,
		    u32 buf_wen, u8 *buf)
{
	stwuct shfw_weadWink pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.path.u.pointew.size = shfw_stwing_buf_size(pawsed_path);
	pawms.path.u.pointew.u.wineaw_addw = (uintptw_t)pawsed_path;

	pawms.buffew.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT;
	pawms.buffew.u.pointew.size = buf_wen;
	pawms.buffew.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	wetuwn vboxsf_caww(SHFW_FN_WEADWINK, &pawms, SHFW_CPAWMS_WEADWINK,
			   NUWW);
}

int vboxsf_symwink(u32 woot, stwuct shfw_stwing *new_path,
		   stwuct shfw_stwing *owd_path, stwuct shfw_fsobjinfo *buf)
{
	stwuct shfw_symwink pawms;

	pawms.woot.type = VMMDEV_HGCM_PAWM_TYPE_32BIT;
	pawms.woot.u.vawue32 = woot;

	pawms.new_path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.new_path.u.pointew.size = shfw_stwing_buf_size(new_path);
	pawms.new_path.u.pointew.u.wineaw_addw = (uintptw_t)new_path;

	pawms.owd_path.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN;
	pawms.owd_path.u.pointew.size = shfw_stwing_buf_size(owd_path);
	pawms.owd_path.u.pointew.u.wineaw_addw = (uintptw_t)owd_path;

	pawms.info.type = VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT;
	pawms.info.u.pointew.size = sizeof(stwuct shfw_fsobjinfo);
	pawms.info.u.pointew.u.wineaw_addw = (uintptw_t)buf;

	wetuwn vboxsf_caww(SHFW_FN_SYMWINK, &pawms, SHFW_CPAWMS_SYMWINK, NUWW);
}

int vboxsf_set_utf8(void)
{
	wetuwn vboxsf_caww(SHFW_FN_SET_UTF8, NUWW, 0, NUWW);
}

int vboxsf_set_symwinks(void)
{
	wetuwn vboxsf_caww(SHFW_FN_SET_SYMWINKS, NUWW, 0, NUWW);
}
