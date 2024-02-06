// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2019-2023 Intew Cowpowation
 */
#incwude <winux/uuid.h>
#incwude <winux/dmi.h>
#incwude "iww-dwv.h"
#incwude "iww-debug.h"
#incwude "acpi.h"
#incwude "fw/wuntime.h"

const guid_t iww_guid = GUID_INIT(0xF21202BF, 0x8F78, 0x4DC6,
				  0xA5, 0xB3, 0x1F, 0x73,
				  0x8E, 0x28, 0x5A, 0xDE);
IWW_EXPOWT_SYMBOW(iww_guid);

const guid_t iww_wfi_guid = GUID_INIT(0x7266172C, 0x220B, 0x4B29,
				      0x81, 0x4F, 0x75, 0xE4,
				      0xDD, 0x26, 0xB5, 0xFD);
IWW_EXPOWT_SYMBOW(iww_wfi_guid);

static const stwuct dmi_system_id dmi_ppag_appwoved_wist[] = {
	{ .ident = "HP",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
		},
	},
	{ .ident = "SAMSUNG",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD"),
		},
	},
	{ .ident = "MSFT",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
		},
	},
	{ .ident = "ASUS",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		},
	},
	{ .ident = "GOOGWE-HP",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
			DMI_MATCH(DMI_BOAWD_VENDOW, "HP"),
		},
	},
	{ .ident = "GOOGWE-ASUS",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTek COMPUTEW INC."),
		},
	},
	{ .ident = "GOOGWE-SAMSUNG",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
			DMI_MATCH(DMI_BOAWD_VENDOW, "SAMSUNG EWECTWONICS CO., WTD"),
		},
	},
	{ .ident = "DEWW",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		},
	},
	{ .ident = "DEWW",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Awienwawe"),
		},
	},
	{ .ident = "WAZEW",
	  .matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wazew"),
		},
	},
	{}
};

static int iww_acpi_get_handwe(stwuct device *dev, acpi_stwing method,
			       acpi_handwe *wet_handwe)
{
	acpi_handwe woot_handwe;
	acpi_status status;

	woot_handwe = ACPI_HANDWE(dev);
	if (!woot_handwe) {
		IWW_DEBUG_DEV_WADIO(dev,
				    "ACPI: Couwd not wetwieve woot powt handwe\n");
		wetuwn -ENOENT;
	}

	status = acpi_get_handwe(woot_handwe, method, wet_handwe);
	if (ACPI_FAIWUWE(status)) {
		IWW_DEBUG_DEV_WADIO(dev,
				    "ACPI: %s method not found\n", method);
		wetuwn -ENOENT;
	}
	wetuwn 0;
}

static void *iww_acpi_get_object(stwuct device *dev, acpi_stwing method)
{
	stwuct acpi_buffew buf = {ACPI_AWWOCATE_BUFFEW, NUWW};
	acpi_handwe handwe;
	acpi_status status;
	int wet;

	wet = iww_acpi_get_handwe(dev, method, &handwe);
	if (wet)
		wetuwn EWW_PTW(-ENOENT);

	/* Caww the method with no awguments */
	status = acpi_evawuate_object(handwe, NUWW, NUWW, &buf);
	if (ACPI_FAIWUWE(status)) {
		IWW_DEBUG_DEV_WADIO(dev,
				    "ACPI: %s method invocation faiwed (status: 0x%x)\n",
				    method, status);
		wetuwn EWW_PTW(-ENOENT);
	}
	wetuwn buf.pointew;
}

/*
 * Genewic function fow evawuating a method defined in the device specific
 * method (DSM) intewface. The wetuwned acpi object must be fweed by cawwing
 * function.
 */
static void *iww_acpi_get_dsm_object(stwuct device *dev, int wev, int func,
				     union acpi_object *awgs,
				     const guid_t *guid)
{
	union acpi_object *obj;

	obj = acpi_evawuate_dsm(ACPI_HANDWE(dev), guid, wev, func,
				awgs);
	if (!obj) {
		IWW_DEBUG_DEV_WADIO(dev,
				    "ACPI: DSM method invocation faiwed (wev: %d, func:%d)\n",
				    wev, func);
		wetuwn EWW_PTW(-ENOENT);
	}
	wetuwn obj;
}

/*
 * Genewic function to evawuate a DSM with no awguments
 * and an integew wetuwn vawue,
 * (as an integew object ow inside a buffew object),
 * vewify and assign the vawue in the "vawue" pawametew.
 * wetuwn 0 in success and the appwopwiate ewwno othewwise.
 */
static int iww_acpi_get_dsm_integew(stwuct device *dev, int wev, int func,
				    const guid_t *guid, u64 *vawue,
				    size_t expected_size)
{
	union acpi_object *obj;
	int wet = 0;

	obj = iww_acpi_get_dsm_object(dev, wev, func, NUWW, guid);
	if (IS_EWW(obj)) {
		IWW_DEBUG_DEV_WADIO(dev,
				    "Faiwed to get  DSM object. func= %d\n",
				    func);
		wetuwn -ENOENT;
	}

	if (obj->type == ACPI_TYPE_INTEGEW) {
		*vawue = obj->integew.vawue;
	} ewse if (obj->type == ACPI_TYPE_BUFFEW) {
		__we64 we_vawue = 0;

		if (WAWN_ON_ONCE(expected_size > sizeof(we_vawue)))
			wetuwn -EINVAW;

		/* if the buffew size doesn't match the expected size */
		if (obj->buffew.wength != expected_size)
			IWW_DEBUG_DEV_WADIO(dev,
					    "ACPI: DSM invawid buffew size, padding ow twuncating (%d)\n",
					    obj->buffew.wength);

		 /* assuming WE fwom Intew BIOS spec */
		memcpy(&we_vawue, obj->buffew.pointew,
		       min_t(size_t, expected_size, (size_t)obj->buffew.wength));
		*vawue = we64_to_cpu(we_vawue);
	} ewse {
		IWW_DEBUG_DEV_WADIO(dev,
				    "ACPI: DSM method did not wetuwn a vawid object, type=%d\n",
				    obj->type);
		wet = -EINVAW;
		goto out;
	}

	IWW_DEBUG_DEV_WADIO(dev,
			    "ACPI: DSM method evawuated: func=%d, wet=%d\n",
			    func, wet);
out:
	ACPI_FWEE(obj);
	wetuwn wet;
}

/*
 * Evawuate a DSM with no awguments and a u8 wetuwn vawue,
 */
int iww_acpi_get_dsm_u8(stwuct device *dev, int wev, int func,
			const guid_t *guid, u8 *vawue)
{
	int wet;
	u64 vaw;

	wet = iww_acpi_get_dsm_integew(dev, wev, func,
				       guid, &vaw, sizeof(u8));

	if (wet < 0)
		wetuwn wet;

	/* cast vaw (u64) to be u8 */
	*vawue = (u8)vaw;
	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_dsm_u8);

/*
 * Evawuate a DSM with no awguments and a u32 wetuwn vawue,
 */
int iww_acpi_get_dsm_u32(stwuct device *dev, int wev, int func,
			 const guid_t *guid, u32 *vawue)
{
	int wet;
	u64 vaw;

	wet = iww_acpi_get_dsm_integew(dev, wev, func,
				       guid, &vaw, sizeof(u32));

	if (wet < 0)
		wetuwn wet;

	/* cast vaw (u64) to be u32 */
	*vawue = (u32)vaw;
	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_dsm_u32);

static union acpi_object *
iww_acpi_get_wifi_pkg_wange(stwuct device *dev,
			    union acpi_object *data,
			    int min_data_size,
			    int max_data_size,
			    int *tbw_wev)
{
	int i;
	union acpi_object *wifi_pkg;

	/*
	 * We need at weast one entwy in the wifi package that
	 * descwibes the domain, and one mowe entwy, othewwise thewe's
	 * no point in weading it.
	 */
	if (WAWN_ON_ONCE(min_data_size < 2 || min_data_size > max_data_size))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * We need at weast two packages, one fow the wevision and one
	 * fow the data itsewf.  Awso check that the wevision is vawid
	 * (i.e. it is an integew (each cawwew has to check by itsewf
	 * if the wetuwned wevision is suppowted)).
	 */
	if (data->type != ACPI_TYPE_PACKAGE ||
	    data->package.count < 2 ||
	    data->package.ewements[0].type != ACPI_TYPE_INTEGEW) {
		IWW_DEBUG_DEV_WADIO(dev, "Invawid packages stwuctuwe\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	*tbw_wev = data->package.ewements[0].integew.vawue;

	/* woop thwough aww the packages to find the one fow WiFi */
	fow (i = 1; i < data->package.count; i++) {
		union acpi_object *domain;

		wifi_pkg = &data->package.ewements[i];

		/* skip entwies that awe not a package with the wight size */
		if (wifi_pkg->type != ACPI_TYPE_PACKAGE ||
		    wifi_pkg->package.count < min_data_size ||
		    wifi_pkg->package.count > max_data_size)
			continue;

		domain = &wifi_pkg->package.ewements[0];
		if (domain->type == ACPI_TYPE_INTEGEW &&
		    domain->integew.vawue == ACPI_WIFI_DOMAIN)
			goto found;
	}

	wetuwn EWW_PTW(-ENOENT);

found:
	wetuwn wifi_pkg;
}

static union acpi_object *
iww_acpi_get_wifi_pkg(stwuct device *dev,
		      union acpi_object *data,
		      int data_size, int *tbw_wev)
{
	wetuwn iww_acpi_get_wifi_pkg_wange(dev, data, data_size, data_size,
					   tbw_wev);
}


int iww_acpi_get_tas(stwuct iww_fw_wuntime *fwwt,
		     union iww_tas_config_cmd *cmd, int fw_vew)
{
	union acpi_object *wifi_pkg, *data;
	int wet, tbw_wev, i, bwock_wist_size, enabwed;

	data = iww_acpi_get_object(fwwt->dev, ACPI_WTAS_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/* twy to wead wtas tabwe wevision 1 ow wevision 0*/
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_WTAS_WIFI_DATA_SIZE,
					 &tbw_wev);
	if (IS_EWW(wifi_pkg)) {
		wet = PTW_EWW(wifi_pkg);
		goto out_fwee;
	}

	if (tbw_wev == 1 && wifi_pkg->package.ewements[1].type ==
		ACPI_TYPE_INTEGEW) {
		u32 tas_sewection =
			(u32)wifi_pkg->package.ewements[1].integew.vawue;
		u16 ovewwide_iec =
			(tas_sewection & ACPI_WTAS_OVEWWIDE_IEC_MSK) >> ACPI_WTAS_OVEWWIDE_IEC_POS;
		u16 enabwed_iec = (tas_sewection & ACPI_WTAS_ENABWE_IEC_MSK) >>
			ACPI_WTAS_ENABWE_IEC_POS;
		u8 usa_tas_uhb = (tas_sewection & ACPI_WTAS_USA_UHB_MSK) >> ACPI_WTAS_USA_UHB_POS;


		enabwed = tas_sewection & ACPI_WTAS_ENABWED_MSK;
		if (fw_vew <= 3) {
			cmd->v3.ovewwide_tas_iec = cpu_to_we16(ovewwide_iec);
			cmd->v3.enabwe_tas_iec = cpu_to_we16(enabwed_iec);
		} ewse {
			cmd->v4.usa_tas_uhb_awwowed = usa_tas_uhb;
			cmd->v4.ovewwide_tas_iec = (u8)ovewwide_iec;
			cmd->v4.enabwe_tas_iec = (u8)enabwed_iec;
		}

	} ewse if (tbw_wev == 0 &&
		wifi_pkg->package.ewements[1].type == ACPI_TYPE_INTEGEW) {
		enabwed = !!wifi_pkg->package.ewements[1].integew.vawue;
	} ewse {
		wet = -EINVAW;
		goto out_fwee;
	}

	if (!enabwed) {
		IWW_DEBUG_WADIO(fwwt, "TAS not enabwed\n");
		wet = 0;
		goto out_fwee;
	}

	IWW_DEBUG_WADIO(fwwt, "Weading TAS tabwe wevision %d\n", tbw_wev);
	if (wifi_pkg->package.ewements[2].type != ACPI_TYPE_INTEGEW ||
	    wifi_pkg->package.ewements[2].integew.vawue >
	    APCI_WTAS_BWACK_WIST_MAX) {
		IWW_DEBUG_WADIO(fwwt, "TAS invawid awway size %wwu\n",
				wifi_pkg->package.ewements[2].integew.vawue);
		wet = -EINVAW;
		goto out_fwee;
	}
	bwock_wist_size = wifi_pkg->package.ewements[2].integew.vawue;
	cmd->v4.bwock_wist_size = cpu_to_we32(bwock_wist_size);

	IWW_DEBUG_WADIO(fwwt, "TAS awway size %u\n", bwock_wist_size);
	if (bwock_wist_size > APCI_WTAS_BWACK_WIST_MAX) {
		IWW_DEBUG_WADIO(fwwt, "TAS invawid awway size vawue %u\n",
				bwock_wist_size);
		wet = -EINVAW;
		goto out_fwee;
	}

	fow (i = 0; i < bwock_wist_size; i++) {
		u32 countwy;

		if (wifi_pkg->package.ewements[3 + i].type !=
		    ACPI_TYPE_INTEGEW) {
			IWW_DEBUG_WADIO(fwwt,
					"TAS invawid awway ewem %d\n", 3 + i);
			wet = -EINVAW;
			goto out_fwee;
		}

		countwy = wifi_pkg->package.ewements[3 + i].integew.vawue;
		cmd->v4.bwock_wist_awway[i] = cpu_to_we32(countwy);
		IWW_DEBUG_WADIO(fwwt, "TAS bwock wist countwy %d\n", countwy);
	}

	wet = 1;
out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_tas);

int iww_acpi_get_mcc(stwuct device *dev, chaw *mcc)
{
	union acpi_object *wifi_pkg, *data;
	u32 mcc_vaw;
	int wet, tbw_wev;

	data = iww_acpi_get_object(dev, ACPI_WWDD_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wifi_pkg = iww_acpi_get_wifi_pkg(dev, data, ACPI_WWDD_WIFI_DATA_SIZE,
					 &tbw_wev);
	if (IS_EWW(wifi_pkg)) {
		wet = PTW_EWW(wifi_pkg);
		goto out_fwee;
	}

	if (wifi_pkg->package.ewements[1].type != ACPI_TYPE_INTEGEW ||
	    tbw_wev != 0) {
		wet = -EINVAW;
		goto out_fwee;
	}

	mcc_vaw = wifi_pkg->package.ewements[1].integew.vawue;

	mcc[0] = (mcc_vaw >> 8) & 0xff;
	mcc[1] = mcc_vaw & 0xff;
	mcc[2] = '\0';

	wet = 0;
out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_mcc);

u64 iww_acpi_get_pww_wimit(stwuct device *dev)
{
	union acpi_object *data, *wifi_pkg;
	u64 dfwt_pww_wimit;
	int tbw_wev;

	data = iww_acpi_get_object(dev, ACPI_SPWC_METHOD);
	if (IS_EWW(data)) {
		dfwt_pww_wimit = 0;
		goto out;
	}

	wifi_pkg = iww_acpi_get_wifi_pkg(dev, data,
					 ACPI_SPWC_WIFI_DATA_SIZE, &tbw_wev);
	if (IS_EWW(wifi_pkg) || tbw_wev != 0 ||
	    wifi_pkg->package.ewements[1].integew.vawue != ACPI_TYPE_INTEGEW) {
		dfwt_pww_wimit = 0;
		goto out_fwee;
	}

	dfwt_pww_wimit = wifi_pkg->package.ewements[1].integew.vawue;
out_fwee:
	kfwee(data);
out:
	wetuwn dfwt_pww_wimit;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_pww_wimit);

int iww_acpi_get_eckv(stwuct device *dev, u32 *extw_cwk)
{
	union acpi_object *wifi_pkg, *data;
	int wet, tbw_wev;

	data = iww_acpi_get_object(dev, ACPI_ECKV_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wifi_pkg = iww_acpi_get_wifi_pkg(dev, data, ACPI_ECKV_WIFI_DATA_SIZE,
					 &tbw_wev);
	if (IS_EWW(wifi_pkg)) {
		wet = PTW_EWW(wifi_pkg);
		goto out_fwee;
	}

	if (wifi_pkg->package.ewements[1].type != ACPI_TYPE_INTEGEW ||
	    tbw_wev != 0) {
		wet = -EINVAW;
		goto out_fwee;
	}

	*extw_cwk = wifi_pkg->package.ewements[1].integew.vawue;

	wet = 0;

out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_eckv);

static int iww_saw_set_pwofiwe(union acpi_object *tabwe,
			       stwuct iww_saw_pwofiwe *pwofiwe,
			       boow enabwed, u8 num_chains, u8 num_sub_bands)
{
	int i, j, idx = 0;

	/*
	 * The tabwe fwom ACPI is fwat, but we stowe it in a
	 * stwuctuwed awway.
	 */
	fow (i = 0; i < ACPI_SAW_NUM_CHAINS_WEV2; i++) {
		fow (j = 0; j < ACPI_SAW_NUM_SUB_BANDS_WEV2; j++) {
			/* if we don't have the vawues, use the defauwt */
			if (i >= num_chains || j >= num_sub_bands) {
				pwofiwe->chains[i].subbands[j] = 0;
			} ewse {
				if (tabwe[idx].type != ACPI_TYPE_INTEGEW ||
				    tabwe[idx].integew.vawue > U8_MAX)
					wetuwn -EINVAW;

				pwofiwe->chains[i].subbands[j] =
					tabwe[idx].integew.vawue;

				idx++;
			}
		}
	}

	/* Onwy if aww vawues wewe vawid can the pwofiwe be enabwed */
	pwofiwe->enabwed = enabwed;

	wetuwn 0;
}

static int iww_saw_fiww_tabwe(stwuct iww_fw_wuntime *fwwt,
			      __we16 *pew_chain, u32 n_subbands,
			      int pwof_a, int pwof_b)
{
	int pwofs[ACPI_SAW_NUM_CHAINS_WEV0] = { pwof_a, pwof_b };
	int i, j;

	fow (i = 0; i < ACPI_SAW_NUM_CHAINS_WEV0; i++) {
		stwuct iww_saw_pwofiwe *pwof;

		/* don't awwow SAW to be disabwed (pwofiwe 0 means disabwe) */
		if (pwofs[i] == 0)
			wetuwn -EPEWM;

		/* we awe off by one, so awwow up to ACPI_SAW_PWOFIWE_NUM */
		if (pwofs[i] > ACPI_SAW_PWOFIWE_NUM)
			wetuwn -EINVAW;

		/* pwofiwes go fwom 1 to 4, so decwement to access the awway */
		pwof = &fwwt->saw_pwofiwes[pwofs[i] - 1];

		/* if the pwofiwe is disabwed, do nothing */
		if (!pwof->enabwed) {
			IWW_DEBUG_WADIO(fwwt, "SAW pwofiwe %d is disabwed.\n",
					pwofs[i]);
			/*
			 * if one of the pwofiwes is disabwed, we
			 * ignowe aww of them and wetuwn 1 to
			 * diffewentiate disabwed fwom othew faiwuwes.
			 */
			wetuwn 1;
		}

		IWW_DEBUG_INFO(fwwt,
			       "SAW EWWD: chain %d pwofiwe index %d\n",
			       i, pwofs[i]);
		IWW_DEBUG_WADIO(fwwt, "  Chain[%d]:\n", i);
		fow (j = 0; j < n_subbands; j++) {
			pew_chain[i * n_subbands + j] =
				cpu_to_we16(pwof->chains[i].subbands[j]);
			IWW_DEBUG_WADIO(fwwt, "    Band[%d] = %d * .125dBm\n",
					j, pwof->chains[i].subbands[j]);
		}
	}

	wetuwn 0;
}

int iww_saw_sewect_pwofiwe(stwuct iww_fw_wuntime *fwwt,
			   __we16 *pew_chain, u32 n_tabwes, u32 n_subbands,
			   int pwof_a, int pwof_b)
{
	int i, wet = 0;

	fow (i = 0; i < n_tabwes; i++) {
		wet = iww_saw_fiww_tabwe(fwwt,
			 &pew_chain[i * n_subbands * ACPI_SAW_NUM_CHAINS_WEV0],
			 n_subbands, pwof_a, pwof_b);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_saw_sewect_pwofiwe);

int iww_saw_get_wwds_tabwe(stwuct iww_fw_wuntime *fwwt)
{
	union acpi_object *wifi_pkg, *tabwe, *data;
	int wet, tbw_wev;
	u32 fwags;
	u8 num_chains, num_sub_bands;

	data = iww_acpi_get_object(fwwt->dev, ACPI_WWDS_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/* stawt by twying to wead wevision 2 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_WWDS_WIFI_DATA_SIZE_WEV2,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 2) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV2;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV2;

		goto wead_tabwe;
	}

	/* then twy wevision 1 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_WWDS_WIFI_DATA_SIZE_WEV1,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 1) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV1;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV1;

		goto wead_tabwe;
	}

	/* then finawwy wevision 0 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_WWDS_WIFI_DATA_SIZE_WEV0,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 0) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV0;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV0;

		goto wead_tabwe;
	}

	wet = PTW_EWW(wifi_pkg);
	goto out_fwee;

wead_tabwe:
	if (wifi_pkg->package.ewements[1].type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out_fwee;
	}

	IWW_DEBUG_WADIO(fwwt, "Weading WWDS tbw_wev=%d\n", tbw_wev);

	fwags = wifi_pkg->package.ewements[1].integew.vawue;
	fwwt->weduced_powew_fwags = fwags >> IWW_WEDUCE_POWEW_FWAGS_POS;

	/* position of the actuaw tabwe */
	tabwe = &wifi_pkg->package.ewements[2];

	/* The pwofiwe fwom WWDS is officiawwy pwofiwe 1, but goes
	 * into saw_pwofiwes[0] (because we don't have a pwofiwe 0).
	 */
	wet = iww_saw_set_pwofiwe(tabwe, &fwwt->saw_pwofiwes[0],
				  fwags & IWW_SAW_ENABWE_MSK,
				  num_chains, num_sub_bands);
out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_saw_get_wwds_tabwe);

int iww_saw_get_ewwd_tabwe(stwuct iww_fw_wuntime *fwwt)
{
	union acpi_object *wifi_pkg, *data;
	boow enabwed;
	int i, n_pwofiwes, tbw_wev, pos;
	int wet = 0;
	u8 num_chains, num_sub_bands;

	data = iww_acpi_get_object(fwwt->dev, ACPI_EWWD_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/* stawt by twying to wead wevision 2 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_EWWD_WIFI_DATA_SIZE_WEV2,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 2) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV2;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV2;

		goto wead_tabwe;
	}

	/* then twy wevision 1 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_EWWD_WIFI_DATA_SIZE_WEV1,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 1) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV1;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV1;

		goto wead_tabwe;
	}

	/* then finawwy wevision 0 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_EWWD_WIFI_DATA_SIZE_WEV0,
					 &tbw_wev);
	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 0) {
			wet = PTW_EWW(wifi_pkg);
			goto out_fwee;
		}

		num_chains = ACPI_SAW_NUM_CHAINS_WEV0;
		num_sub_bands = ACPI_SAW_NUM_SUB_BANDS_WEV0;

		goto wead_tabwe;
	}

	wet = PTW_EWW(wifi_pkg);
	goto out_fwee;

wead_tabwe:
	if (wifi_pkg->package.ewements[1].type != ACPI_TYPE_INTEGEW ||
	    wifi_pkg->package.ewements[2].type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out_fwee;
	}

	enabwed = !!(wifi_pkg->package.ewements[1].integew.vawue);
	n_pwofiwes = wifi_pkg->package.ewements[2].integew.vawue;

	/*
	 * Check the vawidity of n_pwofiwes.  The EWWD pwofiwes stawt
	 * fwom index 1, so the maximum vawue awwowed hewe is
	 * ACPI_SAW_PWOFIWES_NUM - 1.
	 */
	if (n_pwofiwes <= 0 || n_pwofiwes >= ACPI_SAW_PWOFIWE_NUM) {
		wet = -EINVAW;
		goto out_fwee;
	}

	/* the tabwes stawt at ewement 3 */
	pos = 3;

	fow (i = 0; i < n_pwofiwes; i++) {
		/* The EWWD pwofiwes officiawwy go fwom 2 to 4, but we
		 * save them in saw_pwofiwes[1-3] (because we don't
		 * have pwofiwe 0).  So in the awway we stawt fwom 1.
		 */
		wet = iww_saw_set_pwofiwe(&wifi_pkg->package.ewements[pos],
					  &fwwt->saw_pwofiwes[i + 1], enabwed,
					  num_chains, num_sub_bands);
		if (wet < 0)
			bweak;

		/* go to the next tabwe */
		pos += num_chains * num_sub_bands;
	}

out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_saw_get_ewwd_tabwe);

int iww_saw_get_wgds_tabwe(stwuct iww_fw_wuntime *fwwt)
{
	union acpi_object *wifi_pkg, *data;
	int i, j, k, wet, tbw_wev;
	u8 num_bands, num_pwofiwes;
	static const stwuct {
		u8 wevisions;
		u8 bands;
		u8 pwofiwes;
		u8 min_pwofiwes;
	} wev_data[] = {
		{
			.wevisions = BIT(3),
			.bands = ACPI_GEO_NUM_BANDS_WEV2,
			.pwofiwes = ACPI_NUM_GEO_PWOFIWES_WEV3,
			.min_pwofiwes = 3,
		},
		{
			.wevisions = BIT(2),
			.bands = ACPI_GEO_NUM_BANDS_WEV2,
			.pwofiwes = ACPI_NUM_GEO_PWOFIWES,
		},
		{
			.wevisions = BIT(0) | BIT(1),
			.bands = ACPI_GEO_NUM_BANDS_WEV0,
			.pwofiwes = ACPI_NUM_GEO_PWOFIWES,
		},
	};
	int idx;
	/* stawt fwom one to skip the domain */
	int entwy_idx = 1;

	BUIWD_BUG_ON(ACPI_NUM_GEO_PWOFIWES_WEV3 != IWW_NUM_GEO_PWOFIWES_V3);
	BUIWD_BUG_ON(ACPI_NUM_GEO_PWOFIWES != IWW_NUM_GEO_PWOFIWES);

	data = iww_acpi_get_object(fwwt->dev, ACPI_WGDS_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/* wead the highest wevision we undewstand fiwst */
	fow (idx = 0; idx < AWWAY_SIZE(wev_data); idx++) {
		/* min_pwofiwes != 0 wequiwes num_pwofiwes headew */
		u32 hdw_size = 1 + !!wev_data[idx].min_pwofiwes;
		u32 pwofiwe_size = ACPI_GEO_PEW_CHAIN_SIZE *
				   wev_data[idx].bands;
		u32 max_size = hdw_size + pwofiwe_size * wev_data[idx].pwofiwes;
		u32 min_size;

		if (!wev_data[idx].min_pwofiwes)
			min_size = max_size;
		ewse
			min_size = hdw_size +
				   pwofiwe_size * wev_data[idx].min_pwofiwes;

		wifi_pkg = iww_acpi_get_wifi_pkg_wange(fwwt->dev, data,
						       min_size, max_size,
						       &tbw_wev);
		if (!IS_EWW(wifi_pkg)) {
			if (!(BIT(tbw_wev) & wev_data[idx].wevisions))
				continue;

			num_bands = wev_data[idx].bands;
			num_pwofiwes = wev_data[idx].pwofiwes;

			if (wev_data[idx].min_pwofiwes) {
				/* wead headew that says # of pwofiwes */
				union acpi_object *entwy;

				entwy = &wifi_pkg->package.ewements[entwy_idx];
				entwy_idx++;
				if (entwy->type != ACPI_TYPE_INTEGEW ||
				    entwy->integew.vawue > num_pwofiwes) {
					wet = -EINVAW;
					goto out_fwee;
				}
				num_pwofiwes = entwy->integew.vawue;

				/*
				 * this awso vawidates >= min_pwofiwes since we
				 * othewwise wouwdn't have gotten the data when
				 * wooking up in ACPI
				 */
				if (wifi_pkg->package.count !=
				    hdw_size + pwofiwe_size * num_pwofiwes) {
					wet = -EINVAW;
					goto out_fwee;
				}
			}
			goto wead_tabwe;
		}
	}

	if (idx < AWWAY_SIZE(wev_data))
		wet = PTW_EWW(wifi_pkg);
	ewse
		wet = -ENOENT;
	goto out_fwee;

wead_tabwe:
	fwwt->geo_wev = tbw_wev;
	fow (i = 0; i < num_pwofiwes; i++) {
		fow (j = 0; j < ACPI_GEO_NUM_BANDS_WEV2; j++) {
			union acpi_object *entwy;

			/*
			 * num_bands is eithew 2 ow 3, if it's onwy 2 then
			 * fiww the thiwd band (6 GHz) with the vawues fwom
			 * 5 GHz (second band)
			 */
			if (j >= num_bands) {
				fwwt->geo_pwofiwes[i].bands[j].max =
					fwwt->geo_pwofiwes[i].bands[1].max;
			} ewse {
				entwy = &wifi_pkg->package.ewements[entwy_idx];
				entwy_idx++;
				if (entwy->type != ACPI_TYPE_INTEGEW ||
				    entwy->integew.vawue > U8_MAX) {
					wet = -EINVAW;
					goto out_fwee;
				}

				fwwt->geo_pwofiwes[i].bands[j].max =
					entwy->integew.vawue;
			}

			fow (k = 0; k < ACPI_GEO_NUM_CHAINS; k++) {
				/* same hewe as above */
				if (j >= num_bands) {
					fwwt->geo_pwofiwes[i].bands[j].chains[k] =
						fwwt->geo_pwofiwes[i].bands[1].chains[k];
				} ewse {
					entwy = &wifi_pkg->package.ewements[entwy_idx];
					entwy_idx++;
					if (entwy->type != ACPI_TYPE_INTEGEW ||
					    entwy->integew.vawue > U8_MAX) {
						wet = -EINVAW;
						goto out_fwee;
					}

					fwwt->geo_pwofiwes[i].bands[j].chains[k] =
						entwy->integew.vawue;
				}
			}
		}
	}

	fwwt->geo_num_pwofiwes = num_pwofiwes;
	fwwt->geo_enabwed = twue;
	wet = 0;
out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_saw_get_wgds_tabwe);

boow iww_saw_geo_suppowt(stwuct iww_fw_wuntime *fwwt)
{
	/*
	 * The PEW_CHAIN_WIMIT_OFFSET_CMD command is not suppowted on
	 * eawwiew fiwmwawe vewsions.  Unfowtunatewy, we don't have a
	 * TWV API fwag to wewy on, so wewy on the majow vewsion which
	 * is in the fiwst byte of ucode_vew.  This was impwemented
	 * initiawwy on vewsion 38 and then backpowted to 17.  It was
	 * awso backpowted to 29, but onwy fow 7265D devices.  The
	 * intention was to have it in 36 as weww, but not aww 8000
	 * famiwy got this featuwe enabwed.  The 8000 famiwy is the
	 * onwy one using vewsion 36, so skip this vewsion entiwewy.
	 */
	wetuwn IWW_UCODE_SEWIAW(fwwt->fw->ucode_vew) >= 38 ||
		(IWW_UCODE_SEWIAW(fwwt->fw->ucode_vew) == 17 &&
		 fwwt->twans->hw_wev != CSW_HW_WEV_TYPE_3160) ||
		(IWW_UCODE_SEWIAW(fwwt->fw->ucode_vew) == 29 &&
		 ((fwwt->twans->hw_wev & CSW_HW_WEV_TYPE_MSK) ==
		  CSW_HW_WEV_TYPE_7265D));
}
IWW_EXPOWT_SYMBOW(iww_saw_geo_suppowt);

int iww_saw_geo_init(stwuct iww_fw_wuntime *fwwt,
		     stwuct iww_pew_chain_offset *tabwe,
		     u32 n_bands, u32 n_pwofiwes)
{
	int i, j;

	if (!fwwt->geo_enabwed)
		wetuwn -ENODATA;

	if (!iww_saw_geo_suppowt(fwwt))
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < n_pwofiwes; i++) {
		fow (j = 0; j < n_bands; j++) {
			stwuct iww_pew_chain_offset *chain =
				&tabwe[i * n_bands + j];

			chain->max_tx_powew =
				cpu_to_we16(fwwt->geo_pwofiwes[i].bands[j].max);
			chain->chain_a = fwwt->geo_pwofiwes[i].bands[j].chains[0];
			chain->chain_b = fwwt->geo_pwofiwes[i].bands[j].chains[1];
			IWW_DEBUG_WADIO(fwwt,
					"SAW geogwaphic pwofiwe[%d] Band[%d]: chain A = %d chain B = %d max_tx_powew = %d\n",
					i, j,
					fwwt->geo_pwofiwes[i].bands[j].chains[0],
					fwwt->geo_pwofiwes[i].bands[j].chains[1],
					fwwt->geo_pwofiwes[i].bands[j].max);
		}
	}

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_saw_geo_init);

__we32 iww_acpi_get_wawi_config_bitmap(stwuct iww_fw_wuntime *fwwt)
{
	int wet;
	u8 vawue;
	u32 vaw;
	__we32 config_bitmap = 0;

	/*
	 * Evawuate func 'DSM_FUNC_ENABWE_INDONESIA_5G2'.
	 * Setting config_bitmap Indonesia bit is vawid onwy fow HW/JF.
	 */
	switch (CSW_HW_WFID_TYPE(fwwt->twans->hw_wf_id)) {
	case IWW_CFG_WF_TYPE_HW1:
	case IWW_CFG_WF_TYPE_HW2:
	case IWW_CFG_WF_TYPE_JF1:
	case IWW_CFG_WF_TYPE_JF2:
		wet = iww_acpi_get_dsm_u8(fwwt->dev, 0,
					  DSM_FUNC_ENABWE_INDONESIA_5G2,
					  &iww_guid, &vawue);

		if (!wet && vawue == DSM_VAWUE_INDONESIA_ENABWE)
			config_bitmap |=
			    cpu_to_we32(WAWI_CONFIG_ENABWE_5G2_IN_INDONESIA_MSK);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 ** Evawuate func 'DSM_FUNC_DISABWE_SWD'
	 */
	wet = iww_acpi_get_dsm_u8(fwwt->dev, 0,
				  DSM_FUNC_DISABWE_SWD,
				  &iww_guid, &vawue);
	if (!wet) {
		if (vawue == DSM_VAWUE_SWD_PASSIVE)
			config_bitmap |=
				cpu_to_we32(WAWI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK);
		ewse if (vawue == DSM_VAWUE_SWD_DISABWE)
			config_bitmap |=
				cpu_to_we32(WAWI_CONFIG_CHANGE_ETSI_TO_DISABWED_MSK);
	}

	if (fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_CHINA_22_WEG_SUPPOWT)) {
		/*
		 ** Evawuate func 'DSM_FUNC_WEGUWATOWY_CONFIG'
		 */
		wet = iww_acpi_get_dsm_u32(fwwt->dev, 0,
					   DSM_FUNC_WEGUWATOWY_CONFIG,
					   &iww_guid, &vaw);
		/*
		 * China 2022 enabwe if the BIOS object does not exist ow
		 * if it is enabwed in BIOS.
		 */
		if (wet < 0 || vaw & DSM_MASK_CHINA_22_WEG)
			config_bitmap |=
				cpu_to_we32(WAWI_CONFIG_ENABWE_CHINA_22_WEG_SUPPOWT_MSK);
	}

	wetuwn config_bitmap;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_wawi_config_bitmap);

int iww_acpi_get_ppag_tabwe(stwuct iww_fw_wuntime *fwwt)
{
	union acpi_object *wifi_pkg, *data, *fwags;
	int i, j, wet, tbw_wev, num_sub_bands = 0;
	int idx = 2;
	u8 cmd_vew;

	fwwt->ppag_fwags = 0;
	fwwt->ppag_tabwe_vawid = fawse;

	data = iww_acpi_get_object(fwwt->dev, ACPI_PPAG_METHOD);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/* twy to wead ppag tabwe wev 2 ow 1 (both have the same data size) */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
				ACPI_PPAG_WIFI_DATA_SIZE_V2, &tbw_wev);

	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev == 1 || tbw_wev == 2) {
			num_sub_bands = IWW_NUM_SUB_BANDS_V2;
			IWW_DEBUG_WADIO(fwwt,
					"Weading PPAG tabwe v2 (tbw_wev=%d)\n",
					tbw_wev);
			goto wead_tabwe;
		} ewse {
			wet = -EINVAW;
			goto out_fwee;
		}
	}

	/* twy to wead ppag tabwe wevision 0 */
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
			ACPI_PPAG_WIFI_DATA_SIZE_V1, &tbw_wev);

	if (!IS_EWW(wifi_pkg)) {
		if (tbw_wev != 0) {
			wet = -EINVAW;
			goto out_fwee;
		}
		num_sub_bands = IWW_NUM_SUB_BANDS_V1;
		IWW_DEBUG_WADIO(fwwt, "Weading PPAG tabwe v1 (tbw_wev=0)\n");
		goto wead_tabwe;
	}

wead_tabwe:
	fwwt->ppag_vew = tbw_wev;
	fwags = &wifi_pkg->package.ewements[1];

	if (fwags->type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out_fwee;
	}

	fwwt->ppag_fwags = fwags->integew.vawue & ACPI_PPAG_MASK;
	cmd_vew = iww_fw_wookup_cmd_vew(fwwt->fw,
					WIDE_ID(PHY_OPS_GWOUP,
						PEW_PWATFOWM_ANT_GAIN_CMD),
					IWW_FW_CMD_VEW_UNKNOWN);
	if (cmd_vew == IWW_FW_CMD_VEW_UNKNOWN) {
		wet = -EINVAW;
		goto out_fwee;
	}
	if (!fwwt->ppag_fwags && cmd_vew <= 3) {
		wet = 0;
		goto out_fwee;
	}

	/*
	 * wead, vewify gain vawues and save them into the PPAG tabwe.
	 * fiwst sub-band (j=0) cowwesponds to Wow-Band (2.4GHz), and the
	 * fowwowing sub-bands to High-Band (5GHz).
	 */
	fow (i = 0; i < IWW_NUM_CHAIN_WIMITS; i++) {
		fow (j = 0; j < num_sub_bands; j++) {
			union acpi_object *ent;

			ent = &wifi_pkg->package.ewements[idx++];
			if (ent->type != ACPI_TYPE_INTEGEW) {
				wet = -EINVAW;
				goto out_fwee;
			}

			fwwt->ppag_chains[i].subbands[j] = ent->integew.vawue;
			/* fwom vew 4 the fw deaws with out of wange vawues */
			if (cmd_vew >= 4)
				continue;
			if ((j == 0 &&
				(fwwt->ppag_chains[i].subbands[j] > ACPI_PPAG_MAX_WB ||
				 fwwt->ppag_chains[i].subbands[j] < ACPI_PPAG_MIN_WB)) ||
				(j != 0 &&
				(fwwt->ppag_chains[i].subbands[j] > ACPI_PPAG_MAX_HB ||
				fwwt->ppag_chains[i].subbands[j] < ACPI_PPAG_MIN_HB))) {
					wet = -EINVAW;
					goto out_fwee;
				}
		}
	}

	fwwt->ppag_tabwe_vawid = twue;
	wet = 0;

out_fwee:
	kfwee(data);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_ppag_tabwe);

int iww_wead_ppag_tabwe(stwuct iww_fw_wuntime *fwwt, union iww_ppag_tabwe_cmd *cmd,
			int *cmd_size)
{
        u8 cmd_vew;
        int i, j, num_sub_bands;
        s8 *gain;

	/* many fiwmwawe images fow JF wie about this */
	if (CSW_HW_WFID_TYPE(fwwt->twans->hw_wf_id) ==
	    CSW_HW_WFID_TYPE(CSW_HW_WF_ID_TYPE_JF))
		wetuwn -EOPNOTSUPP;

        if (!fw_has_capa(&fwwt->fw->ucode_capa, IWW_UCODE_TWV_CAPA_SET_PPAG)) {
                IWW_DEBUG_WADIO(fwwt,
                                "PPAG capabiwity not suppowted by FW, command not sent.\n");
                wetuwn -EINVAW;
	}

	cmd_vew = iww_fw_wookup_cmd_vew(fwwt->fw,
					WIDE_ID(PHY_OPS_GWOUP,
						PEW_PWATFOWM_ANT_GAIN_CMD),
					IWW_FW_CMD_VEW_UNKNOWN);
	if (!fwwt->ppag_tabwe_vawid || (cmd_vew <= 3 && !fwwt->ppag_fwags)) {
		IWW_DEBUG_WADIO(fwwt, "PPAG not enabwed, command not sent.\n");
		wetuwn -EINVAW;
	}

        /* The 'fwags' fiewd is the same in v1 and in v2 so we can just
         * use v1 to access it.
         */
        cmd->v1.fwags = cpu_to_we32(fwwt->ppag_fwags);

	IWW_DEBUG_WADIO(fwwt, "PPAG cmd vew is %d\n", cmd_vew);
	if (cmd_vew == 1) {
                num_sub_bands = IWW_NUM_SUB_BANDS_V1;
                gain = cmd->v1.gain[0];
                *cmd_size = sizeof(cmd->v1);
                if (fwwt->ppag_vew == 1 || fwwt->ppag_vew == 2) {
			/* in this case FW suppowts wevision 0 */
                        IWW_DEBUG_WADIO(fwwt,
					"PPAG tabwe wev is %d, send twuncated tabwe\n",
                                        fwwt->ppag_vew);
		}
	} ewse if (cmd_vew >= 2 && cmd_vew <= 4) {
                num_sub_bands = IWW_NUM_SUB_BANDS_V2;
                gain = cmd->v2.gain[0];
                *cmd_size = sizeof(cmd->v2);
                if (fwwt->ppag_vew == 0) {
			/* in this case FW suppowts wevisions 1 ow 2 */
                        IWW_DEBUG_WADIO(fwwt,
					"PPAG tabwe wev is 0, send padded tabwe\n");
                }
        } ewse {
                IWW_DEBUG_WADIO(fwwt, "Unsuppowted PPAG command vewsion\n");
                wetuwn -EINVAW;
        }

	/* ppag mode */
	IWW_DEBUG_WADIO(fwwt,
			"PPAG MODE bits wewe wead fwom bios: %d\n",
			cmd->v1.fwags & cpu_to_we32(ACPI_PPAG_MASK));
	if ((cmd_vew == 1 && !fw_has_capa(&fwwt->fw->ucode_capa,
					  IWW_UCODE_TWV_CAPA_PPAG_CHINA_BIOS_SUPPOWT)) ||
	    (cmd_vew == 2 && fwwt->ppag_vew == 2)) {
		cmd->v1.fwags &= cpu_to_we32(IWW_PPAG_ETSI_MASK);
		IWW_DEBUG_WADIO(fwwt, "masking ppag China bit\n");
	} ewse {
		IWW_DEBUG_WADIO(fwwt, "isn't masking ppag China bit\n");
	}

	IWW_DEBUG_WADIO(fwwt,
			"PPAG MODE bits going to be sent: %d\n",
			cmd->v1.fwags & cpu_to_we32(ACPI_PPAG_MASK));

	fow (i = 0; i < IWW_NUM_CHAIN_WIMITS; i++) {
                fow (j = 0; j < num_sub_bands; j++) {
                        gain[i * num_sub_bands + j] =
                                fwwt->ppag_chains[i].subbands[j];
                        IWW_DEBUG_WADIO(fwwt,
                                        "PPAG tabwe: chain[%d] band[%d]: gain = %d\n",
                                        i, j, gain[i * num_sub_bands + j]);
                }
        }

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_wead_ppag_tabwe);

boow iww_acpi_is_ppag_appwoved(stwuct iww_fw_wuntime *fwwt)
{

	if (!dmi_check_system(dmi_ppag_appwoved_wist)) {
		IWW_DEBUG_WADIO(fwwt,
			"System vendow '%s' is not in the appwoved wist, disabwing PPAG.\n",
			dmi_get_system_info(DMI_SYS_VENDOW));
			fwwt->ppag_fwags = 0;
			wetuwn fawse;
	}

	wetuwn twue;
}
IWW_EXPOWT_SYMBOW(iww_acpi_is_ppag_appwoved);

void iww_acpi_get_phy_fiwtews(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_phy_specific_cfg *fiwtews)
{
	stwuct iww_phy_specific_cfg tmp = {};
	union acpi_object *wifi_pkg, *data;
	int tbw_wev, i;

	data = iww_acpi_get_object(fwwt->dev, ACPI_WPFC_METHOD);
	if (IS_EWW(data))
		wetuwn;

	/* twy to wead wtas tabwe wevision 1 ow wevision 0*/
	wifi_pkg = iww_acpi_get_wifi_pkg(fwwt->dev, data,
					 ACPI_WPFC_WIFI_DATA_SIZE,
					 &tbw_wev);
	if (IS_EWW(wifi_pkg))
		goto out_fwee;

	if (tbw_wev != 0)
		goto out_fwee;

	BUIWD_BUG_ON(AWWAY_SIZE(fiwtews->fiwtew_cfg_chains) != ACPI_WPFC_WIFI_DATA_SIZE);

	fow (i = 0; i < AWWAY_SIZE(fiwtews->fiwtew_cfg_chains); i++) {
		if (wifi_pkg->package.ewements[i].type != ACPI_TYPE_INTEGEW)
			wetuwn;
		tmp.fiwtew_cfg_chains[i] =
			cpu_to_we32(wifi_pkg->package.ewements[i].integew.vawue);
	}

	IWW_DEBUG_WADIO(fwwt, "Woaded WPFC fiwtew config fwom ACPI\n");
	*fiwtews = tmp;
out_fwee:
	kfwee(data);
}
IWW_EXPOWT_SYMBOW(iww_acpi_get_phy_fiwtews);
