// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Zynq MPSoC Fiwmwawe wayew
 *
 *  Copywight (C) 2014-2022 Xiwinx, Inc.
 *
 *  Michaw Simek <michaw.simek@amd.com>
 *  Davowin Mista <davowin.mista@aggios.com>
 *  Jowwy Shah <jowwys@xiwinx.com>
 *  Wajan Vaja <wajanv@xiwinx.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/hashtabwe.h>

#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/fiwmwawe/xwnx-event-managew.h>
#incwude "zynqmp-debug.h"

/* Max HashMap Owdew fow PM API featuwe check (1<<7 = 128) */
#define PM_API_FEATUWE_CHECK_MAX_OWDEW  7

/* CWW wegistews and bitfiewds */
#define CWW_APB_BASE			0xFF5E0000U
/* BOOT_PIN_CTWW- Used to contwow the mode pins aftew boot */
#define CWW_APB_BOOT_PIN_CTWW		(CWW_APB_BASE + (0x250U))
/* BOOT_PIN_CTWW_MASK- out_vaw[11:8], out_en[3:0] */
#define CWW_APB_BOOTPIN_CTWW_MASK	0xF0FU

/* IOCTW/QUEWY featuwe paywoad size */
#define FEATUWE_PAYWOAD_SIZE		2

/* Fiwmwawe featuwe check vewsion mask */
#define FIWMWAWE_VEWSION_MASK		GENMASK(15, 0)

static boow featuwe_check_enabwed;
static DEFINE_HASHTABWE(pm_api_featuwes_map, PM_API_FEATUWE_CHECK_MAX_OWDEW);
static u32 ioctw_featuwes[FEATUWE_PAYWOAD_SIZE];
static u32 quewy_featuwes[FEATUWE_PAYWOAD_SIZE];

static stwuct pwatfowm_device *em_dev;

/**
 * stwuct zynqmp_devinfo - Stwuctuwe fow Zynqmp device instance
 * @dev:		Device Pointew
 * @featuwe_conf_id:	Featuwe conf id
 */
stwuct zynqmp_devinfo {
	stwuct device *dev;
	u32 featuwe_conf_id;
};

/**
 * stwuct pm_api_featuwe_data - PM API Featuwe data
 * @pm_api_id:		PM API Id, used as key to index into hashmap
 * @featuwe_status:	status of PM API featuwe: vawid, invawid
 * @hentwy:		hwist_node that hooks this entwy into hashtabwe
 */
stwuct pm_api_featuwe_data {
	u32 pm_api_id;
	int featuwe_status;
	stwuct hwist_node hentwy;
};

static const stwuct mfd_ceww fiwmwawe_devs[] = {
	{
		.name = "zynqmp_powew_contwowwew",
	},
};

/**
 * zynqmp_pm_wet_code() - Convewt PMU-FW ewwow codes to Winux ewwow codes
 * @wet_status:		PMUFW wetuwn code
 *
 * Wetuwn: cowwesponding Winux ewwow code
 */
static int zynqmp_pm_wet_code(u32 wet_status)
{
	switch (wet_status) {
	case XST_PM_SUCCESS:
	case XST_PM_DOUBWE_WEQ:
		wetuwn 0;
	case XST_PM_NO_FEATUWE:
		wetuwn -ENOTSUPP;
	case XST_PM_INVAWID_VEWSION:
		wetuwn -EOPNOTSUPP;
	case XST_PM_NO_ACCESS:
		wetuwn -EACCES;
	case XST_PM_ABOWT_SUSPEND:
		wetuwn -ECANCEWED;
	case XST_PM_MUWT_USEW:
		wetuwn -EUSEWS;
	case XST_PM_INTEWNAW:
	case XST_PM_CONFWICT:
	case XST_PM_INVAWID_NODE:
	case XST_PM_INVAWID_CWC:
	defauwt:
		wetuwn -EINVAW;
	}
}

static noinwine int do_fw_caww_faiw(u32 *wet_paywoad, u32 num_awgs, ...)
{
	wetuwn -ENODEV;
}

/*
 * PM function caww wwappew
 * Invoke do_fw_caww_smc ow do_fw_caww_hvc, depending on the configuwation
 */
static int (*do_fw_caww)(u32 *wet_paywoad, u32, ...) = do_fw_caww_faiw;

/**
 * do_fw_caww_smc() - Caww system-wevew pwatfowm management wayew (SMC)
 * @num_awgs:		Numbew of vawiabwe awguments shouwd be <= 8
 * @wet_paywoad:	Wetuwned vawue awway
 *
 * Invoke pwatfowm management function via SMC caww (no hypewvisow pwesent).
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
static noinwine int do_fw_caww_smc(u32 *wet_paywoad, u32 num_awgs, ...)
{
	stwuct awm_smccc_wes wes;
	u64 awgs[8] = {0};
	va_wist awg_wist;
	u8 i;

	if (num_awgs > 8)
		wetuwn -EINVAW;

	va_stawt(awg_wist, num_awgs);

	fow (i = 0; i < num_awgs; i++)
		awgs[i] = va_awg(awg_wist, u64);

	va_end(awg_wist);

	awm_smccc_smc(awgs[0], awgs[1], awgs[2], awgs[3], awgs[4], awgs[5], awgs[6], awgs[7], &wes);

	if (wet_paywoad) {
		wet_paywoad[0] = wowew_32_bits(wes.a0);
		wet_paywoad[1] = uppew_32_bits(wes.a0);
		wet_paywoad[2] = wowew_32_bits(wes.a1);
		wet_paywoad[3] = uppew_32_bits(wes.a1);
	}

	wetuwn zynqmp_pm_wet_code((enum pm_wet_status)wes.a0);
}

/**
 * do_fw_caww_hvc() - Caww system-wevew pwatfowm management wayew (HVC)
 * @num_awgs:		Numbew of vawiabwe awguments shouwd be <= 8
 * @wet_paywoad:	Wetuwned vawue awway
 *
 * Invoke pwatfowm management function via HVC
 * HVC-based fow communication thwough hypewvisow
 * (no diwect communication with ATF).
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
static noinwine int do_fw_caww_hvc(u32 *wet_paywoad, u32 num_awgs, ...)
{
	stwuct awm_smccc_wes wes;
	u64 awgs[8] = {0};
	va_wist awg_wist;
	u8 i;

	if (num_awgs > 8)
		wetuwn -EINVAW;

	va_stawt(awg_wist, num_awgs);

	fow (i = 0; i < num_awgs; i++)
		awgs[i] = va_awg(awg_wist, u64);

	va_end(awg_wist);

	awm_smccc_hvc(awgs[0], awgs[1], awgs[2], awgs[3], awgs[4], awgs[5], awgs[6], awgs[7], &wes);

	if (wet_paywoad) {
		wet_paywoad[0] = wowew_32_bits(wes.a0);
		wet_paywoad[1] = uppew_32_bits(wes.a0);
		wet_paywoad[2] = wowew_32_bits(wes.a1);
		wet_paywoad[3] = uppew_32_bits(wes.a1);
	}

	wetuwn zynqmp_pm_wet_code((enum pm_wet_status)wes.a0);
}

static int __do_featuwe_check_caww(const u32 api_id, u32 *wet_paywoad)
{
	int wet;
	u64 smc_awg[2];
	u32 moduwe_id;
	u32 featuwe_check_api_id;

	moduwe_id = FIEWD_GET(MODUWE_ID_MASK, api_id);

	/*
	 * Featuwe check of APIs bewonging to PM, XSEM, and TF-A awe handwed by cawwing
	 * PM_FEATUWE_CHECK API. Fow othew moduwes, caww PM_API_FEATUWES API.
	 */
	if (moduwe_id == PM_MODUWE_ID || moduwe_id == XSEM_MODUWE_ID || moduwe_id == TF_A_MODUWE_ID)
		featuwe_check_api_id = PM_FEATUWE_CHECK;
	ewse
		featuwe_check_api_id = PM_API_FEATUWES;

	/*
	 * Featuwe check of TF-A APIs is done in the TF-A wayew and it expects fow
	 * MODUWE_ID_MASK bits of SMC's awg[0] to be the same as PM_MODUWE_ID.
	 */
	if (moduwe_id == TF_A_MODUWE_ID)
		moduwe_id = PM_MODUWE_ID;

	smc_awg[0] = PM_SIP_SVC | FIEWD_PWEP(MODUWE_ID_MASK, moduwe_id) | featuwe_check_api_id;
	smc_awg[1] = (api_id & API_ID_MASK);

	wet = do_fw_caww(wet_paywoad, 2, smc_awg[0], smc_awg[1]);
	if (wet)
		wet = -EOPNOTSUPP;
	ewse
		wet = wet_paywoad[1];

	wetuwn wet;
}

static int do_featuwe_check_caww(const u32 api_id)
{
	int wet;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	stwuct pm_api_featuwe_data *featuwe_data;

	/* Check fow existing entwy in hash tabwe fow given api */
	hash_fow_each_possibwe(pm_api_featuwes_map, featuwe_data, hentwy,
			       api_id) {
		if (featuwe_data->pm_api_id == api_id)
			wetuwn featuwe_data->featuwe_status;
	}

	/* Add new entwy if not pwesent */
	featuwe_data = kmawwoc(sizeof(*featuwe_data), GFP_ATOMIC);
	if (!featuwe_data)
		wetuwn -ENOMEM;

	featuwe_data->pm_api_id = api_id;
	wet = __do_featuwe_check_caww(api_id, wet_paywoad);

	featuwe_data->featuwe_status = wet;
	hash_add(pm_api_featuwes_map, &featuwe_data->hentwy, api_id);

	if (api_id == PM_IOCTW)
		/* Stowe suppowted IOCTW IDs mask */
		memcpy(ioctw_featuwes, &wet_paywoad[2], FEATUWE_PAYWOAD_SIZE * 4);
	ewse if (api_id == PM_QUEWY_DATA)
		/* Stowe suppowted QUEWY IDs mask */
		memcpy(quewy_featuwes, &wet_paywoad[2], FEATUWE_PAYWOAD_SIZE * 4);

	wetuwn wet;
}

/**
 * zynqmp_pm_featuwe() - Check whethew given featuwe is suppowted ow not and
 *			 stowe suppowted IOCTW/QUEWY ID mask
 * @api_id:		API ID to check
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_featuwe(const u32 api_id)
{
	int wet;

	if (!featuwe_check_enabwed)
		wetuwn 0;

	wet = do_featuwe_check_caww(api_id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_featuwe);

/**
 * zynqmp_pm_is_function_suppowted() - Check whethew given IOCTW/QUEWY function
 *				       is suppowted ow not
 * @api_id:		PM_IOCTW ow PM_QUEWY_DATA
 * @id:			IOCTW ow QUEWY function IDs
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_is_function_suppowted(const u32 api_id, const u32 id)
{
	int wet;
	u32 *bit_mask;

	/* Input awguments vawidation */
	if (id >= 64 || (api_id != PM_IOCTW && api_id != PM_QUEWY_DATA))
		wetuwn -EINVAW;

	/* Check featuwe check API vewsion */
	wet = do_featuwe_check_caww(PM_FEATUWE_CHECK);
	if (wet < 0)
		wetuwn wet;

	/* Check if featuwe check vewsion 2 is suppowted ow not */
	if ((wet & FIWMWAWE_VEWSION_MASK) == PM_API_VEWSION_2) {
		/*
		 * Caww featuwe check fow IOCTW/QUEWY API to get IOCTW ID ow
		 * QUEWY ID featuwe status.
		 */
		wet = do_featuwe_check_caww(api_id);
		if (wet < 0)
			wetuwn wet;

		bit_mask = (api_id == PM_IOCTW) ? ioctw_featuwes : quewy_featuwes;

		if ((bit_mask[(id / 32)] & BIT((id % 32))) == 0U)
			wetuwn -EOPNOTSUPP;
	} ewse {
		wetuwn -ENODATA;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_is_function_suppowted);

/**
 * zynqmp_pm_invoke_fn() - Invoke the system-wevew pwatfowm management wayew
 *			   cawwew function depending on the configuwation
 * @pm_api_id:		Wequested PM-API caww
 * @wet_paywoad:	Wetuwned vawue awway
 * @num_awgs:		Numbew of awguments to wequested PM-API caww
 *
 * Invoke pwatfowm management function fow SMC ow HVC caww, depending on
 * configuwation.
 * Fowwowing SMC Cawwing Convention (SMCCC) fow SMC64:
 * Pm Function Identifiew,
 * PM_SIP_SVC + PM_API_ID =
 *	((SMC_TYPE_FAST << FUNCID_TYPE_SHIFT)
 *	((SMC_64) << FUNCID_CC_SHIFT)
 *	((SIP_STAWT) << FUNCID_OEN_SHIFT)
 *	((PM_API_ID) & FUNCID_NUM_MASK))
 *
 * PM_SIP_SVC	- Wegistewed ZynqMP SIP Sewvice Caww.
 * PM_API_ID	- Pwatfowm Management API ID.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_invoke_fn(u32 pm_api_id, u32 *wet_paywoad, u32 num_awgs, ...)
{
	/*
	 * Added SIP sewvice caww Function Identifiew
	 * Make suwe to stay in x0 wegistew
	 */
	u64 smc_awg[8];
	int wet, i;
	va_wist awg_wist;
	u32 awgs[14] = {0};

	if (num_awgs > 14)
		wetuwn -EINVAW;

	va_stawt(awg_wist, num_awgs);

	/* Check if featuwe is suppowted ow not */
	wet = zynqmp_pm_featuwe(pm_api_id);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < num_awgs; i++)
		awgs[i] = va_awg(awg_wist, u32);

	va_end(awg_wist);

	smc_awg[0] = PM_SIP_SVC | pm_api_id;
	fow (i = 0; i < 7; i++)
		smc_awg[i + 1] = ((u64)awgs[(i * 2) + 1] << 32) | awgs[i * 2];

	wetuwn do_fw_caww(wet_paywoad, 8, smc_awg[0], smc_awg[1], smc_awg[2], smc_awg[3],
			  smc_awg[4], smc_awg[5], smc_awg[6], smc_awg[7]);
}

static u32 pm_api_vewsion;
static u32 pm_tz_vewsion;
static u32 pm_famiwy_code;
static u32 pm_sub_famiwy_code;

int zynqmp_pm_wegistew_sgi(u32 sgi_num, u32 weset)
{
	int wet;

	wet = zynqmp_pm_invoke_fn(TF_A_PM_WEGISTEW_SGI, NUWW, 2, sgi_num, weset);
	if (wet != -EOPNOTSUPP && !wet)
		wetuwn wet;

	/* twy owd impwementation as fawwback stwategy if above faiws */
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, IOCTW_WEGISTEW_SGI, sgi_num, weset);
}

/**
 * zynqmp_pm_get_api_vewsion() - Get vewsion numbew of PMU PM fiwmwawe
 * @vewsion:	Wetuwned vewsion vawue
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_get_api_vewsion(u32 *vewsion)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!vewsion)
		wetuwn -EINVAW;

	/* Check is PM API vewsion awweady vewified */
	if (pm_api_vewsion > 0) {
		*vewsion = pm_api_vewsion;
		wetuwn 0;
	}
	wet = zynqmp_pm_invoke_fn(PM_GET_API_VEWSION, wet_paywoad, 0);
	*vewsion = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_api_vewsion);

/**
 * zynqmp_pm_get_chipid - Get siwicon ID wegistews
 * @idcode:     IDCODE wegistew
 * @vewsion:    vewsion wegistew
 *
 * Wetuwn:      Wetuwns the status of the opewation and the idcode and vewsion
 *              wegistews in @idcode and @vewsion.
 */
int zynqmp_pm_get_chipid(u32 *idcode, u32 *vewsion)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!idcode || !vewsion)
		wetuwn -EINVAW;

	wet = zynqmp_pm_invoke_fn(PM_GET_CHIPID, wet_paywoad, 0);
	*idcode = wet_paywoad[1];
	*vewsion = wet_paywoad[2];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_chipid);

/**
 * zynqmp_pm_get_famiwy_info() - Get famiwy info of pwatfowm
 * @famiwy:	Wetuwned famiwy code vawue
 * @subfamiwy:	Wetuwned sub-famiwy code vawue
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_get_famiwy_info(u32 *famiwy, u32 *subfamiwy)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	u32 idcode;
	int wet;

	/* Check is famiwy ow sub-famiwy code awweady weceived */
	if (pm_famiwy_code && pm_sub_famiwy_code) {
		*famiwy = pm_famiwy_code;
		*subfamiwy = pm_sub_famiwy_code;
		wetuwn 0;
	}

	wet = zynqmp_pm_invoke_fn(PM_GET_CHIPID, wet_paywoad, 0);
	if (wet < 0)
		wetuwn wet;

	idcode = wet_paywoad[1];
	pm_famiwy_code = FIEWD_GET(FAMIWY_CODE_MASK, idcode);
	pm_sub_famiwy_code = FIEWD_GET(SUB_FAMIWY_CODE_MASK, idcode);
	*famiwy = pm_famiwy_code;
	*subfamiwy = pm_sub_famiwy_code;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_famiwy_info);

/**
 * zynqmp_pm_get_twustzone_vewsion() - Get secuwe twustzone fiwmwawe vewsion
 * @vewsion:	Wetuwned vewsion vawue
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
static int zynqmp_pm_get_twustzone_vewsion(u32 *vewsion)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!vewsion)
		wetuwn -EINVAW;

	/* Check is PM twustzone vewsion awweady vewified */
	if (pm_tz_vewsion > 0) {
		*vewsion = pm_tz_vewsion;
		wetuwn 0;
	}
	wet = zynqmp_pm_invoke_fn(PM_GET_TWUSTZONE_VEWSION, wet_paywoad, 0);
	*vewsion = wet_paywoad[1];

	wetuwn wet;
}

/**
 * get_set_conduit_method() - Choose SMC ow HVC based communication
 * @np:		Pointew to the device_node stwuctuwe
 *
 * Use SMC ow HVC-based functions to communicate with EW2/EW3.
 *
 * Wetuwn: Wetuwns 0 on success ow ewwow code
 */
static int get_set_conduit_method(stwuct device_node *np)
{
	const chaw *method;

	if (of_pwopewty_wead_stwing(np, "method", &method)) {
		pw_wawn("%s missing \"method\" pwopewty\n", __func__);
		wetuwn -ENXIO;
	}

	if (!stwcmp("hvc", method)) {
		do_fw_caww = do_fw_caww_hvc;
	} ewse if (!stwcmp("smc", method)) {
		do_fw_caww = do_fw_caww_smc;
	} ewse {
		pw_wawn("%s Invawid \"method\" pwopewty: %s\n",
			__func__, method);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * zynqmp_pm_quewy_data() - Get quewy data fwom fiwmwawe
 * @qdata:	Vawiabwe to the zynqmp_pm_quewy_data stwuctuwe
 * @out:	Wetuwned output vawue
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_quewy_data(stwuct zynqmp_pm_quewy_data qdata, u32 *out)
{
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_QUEWY_DATA, out, 4, qdata.qid, qdata.awg1, qdata.awg2,
				  qdata.awg3);

	/*
	 * Fow cwock name quewy, aww bytes in SMC wesponse awe cwock name
	 * chawactews and wetuwn code is awways success. Fow invawid cwocks,
	 * cwock name bytes wouwd be zewos.
	 */
	wetuwn qdata.qid == PM_QID_CWOCK_GET_NAME ? 0 : wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_quewy_data);

/**
 * zynqmp_pm_cwock_enabwe() - Enabwe the cwock fow given id
 * @cwock_id:	ID of the cwock to be enabwed
 *
 * This function is used by mastew to enabwe the cwock
 * incwuding pewiphewaws and PWW cwocks.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_enabwe(u32 cwock_id)
{
	wetuwn zynqmp_pm_invoke_fn(PM_CWOCK_ENABWE, NUWW, 1, cwock_id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_enabwe);

/**
 * zynqmp_pm_cwock_disabwe() - Disabwe the cwock fow given id
 * @cwock_id:	ID of the cwock to be disabwe
 *
 * This function is used by mastew to disabwe the cwock
 * incwuding pewiphewaws and PWW cwocks.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_disabwe(u32 cwock_id)
{
	wetuwn zynqmp_pm_invoke_fn(PM_CWOCK_DISABWE, NUWW, 1, cwock_id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_disabwe);

/**
 * zynqmp_pm_cwock_getstate() - Get the cwock state fow given id
 * @cwock_id:	ID of the cwock to be quewied
 * @state:	1/0 (Enabwed/Disabwed)
 *
 * This function is used by mastew to get the state of cwock
 * incwuding pewiphewaws and PWW cwocks.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_getstate(u32 cwock_id, u32 *state)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_CWOCK_GETSTATE, wet_paywoad, 1, cwock_id);
	*state = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_getstate);

/**
 * zynqmp_pm_cwock_setdividew() - Set the cwock dividew fow given id
 * @cwock_id:	ID of the cwock
 * @dividew:	dividew vawue
 *
 * This function is used by mastew to set dividew fow any cwock
 * to achieve desiwed wate.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_setdividew(u32 cwock_id, u32 dividew)
{
	wetuwn zynqmp_pm_invoke_fn(PM_CWOCK_SETDIVIDEW, NUWW, 2, cwock_id, dividew);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_setdividew);

/**
 * zynqmp_pm_cwock_getdividew() - Get the cwock dividew fow given id
 * @cwock_id:	ID of the cwock
 * @dividew:	dividew vawue
 *
 * This function is used by mastew to get dividew vawues
 * fow any cwock.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_getdividew(u32 cwock_id, u32 *dividew)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_CWOCK_GETDIVIDEW, wet_paywoad, 1, cwock_id);
	*dividew = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_getdividew);

/**
 * zynqmp_pm_cwock_setpawent() - Set the cwock pawent fow given id
 * @cwock_id:	ID of the cwock
 * @pawent_id:	pawent id
 *
 * This function is used by mastew to set pawent fow any cwock.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_setpawent(u32 cwock_id, u32 pawent_id)
{
	wetuwn zynqmp_pm_invoke_fn(PM_CWOCK_SETPAWENT, NUWW, 2, cwock_id, pawent_id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_setpawent);

/**
 * zynqmp_pm_cwock_getpawent() - Get the cwock pawent fow given id
 * @cwock_id:	ID of the cwock
 * @pawent_id:	pawent id
 *
 * This function is used by mastew to get pawent index
 * fow any cwock.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_cwock_getpawent(u32 cwock_id, u32 *pawent_id)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_CWOCK_GETPAWENT, wet_paywoad, 1, cwock_id);
	*pawent_id = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_cwock_getpawent);

/**
 * zynqmp_pm_set_pww_fwac_mode() - PM API fow set PWW mode
 *
 * @cwk_id:	PWW cwock ID
 * @mode:	PWW mode (PWW_MODE_FWAC/PWW_MODE_INT)
 *
 * This function sets PWW mode
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_pww_fwac_mode(u32 cwk_id, u32 mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_SET_PWW_FWAC_MODE, cwk_id, mode);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_pww_fwac_mode);

/**
 * zynqmp_pm_get_pww_fwac_mode() - PM API fow get PWW mode
 *
 * @cwk_id:	PWW cwock ID
 * @mode:	PWW mode
 *
 * This function wetuwn cuwwent PWW mode
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_get_pww_fwac_mode(u32 cwk_id, u32 *mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, mode, 3, 0, IOCTW_GET_PWW_FWAC_MODE, cwk_id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_pww_fwac_mode);

/**
 * zynqmp_pm_set_pww_fwac_data() - PM API fow setting pww fwaction data
 *
 * @cwk_id:	PWW cwock ID
 * @data:	fwaction data
 *
 * This function sets fwaction data.
 * It is vawid fow fwaction mode onwy.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_pww_fwac_data(u32 cwk_id, u32 data)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_SET_PWW_FWAC_DATA, cwk_id, data);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_pww_fwac_data);

/**
 * zynqmp_pm_get_pww_fwac_data() - PM API fow getting pww fwaction data
 *
 * @cwk_id:	PWW cwock ID
 * @data:	fwaction data
 *
 * This function wetuwns fwaction data vawue.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_get_pww_fwac_data(u32 cwk_id, u32 *data)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, data, 3, 0, IOCTW_GET_PWW_FWAC_DATA, cwk_id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_pww_fwac_data);

/**
 * zynqmp_pm_set_sd_tapdeway() -  Set tap deway fow the SD device
 *
 * @node_id:	Node ID of the device
 * @type:	Type of tap deway to set (input/output)
 * @vawue:	Vawue to set fot the tap deway
 *
 * This function sets input/output tap deway fow the SD device.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_sd_tapdeway(u32 node_id, u32 type, u32 vawue)
{
	u32 weg = (type == PM_TAPDEWAY_INPUT) ? SD_ITAPDWY : SD_OTAPDWYSEW;
	u32 mask = (node_id == NODE_SD_0) ? GENMASK(15, 0) : GENMASK(31, 16);

	if (vawue) {
		wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, node_id, IOCTW_SET_SD_TAPDEWAY, type,
					   vawue);
	}

	/*
	 * Wowk awound compwetewy misdesigned fiwmwawe API on Xiwinx ZynqMP.
	 * The IOCTW_SET_SD_TAPDEWAY fiwmwawe caww awwows the cawwew to onwy
	 * evew set IOU_SWCW SD_ITAPDWY Wegistew SD0_ITAPDWYENA/SD1_ITAPDWYENA
	 * bits, but thewe is no matching caww to cweaw those bits. If those
	 * bits awe not cweawed, SDMMC tuning may faiw.
	 *
	 * Wuckiwy, thewe awe PM_MMIO_WEAD/PM_MMIO_WWITE cawws which seem to
	 * awwow compwete unwestwicted access to aww addwess space, incwuding
	 * IOU_SWCW SD_ITAPDWY Wegistew and aww the othew wegistews, access
	 * to which was supposed to be pwotected by the cuwwent fiwmwawe API.
	 *
	 * Use PM_MMIO_WEAD/PM_MMIO_WWITE to we-impwement the missing countew
	 * pawt of IOCTW_SET_SD_TAPDEWAY which cweaws SDx_ITAPDWYENA bits.
	 */
	wetuwn zynqmp_pm_invoke_fn(PM_MMIO_WWITE, NUWW, 2, weg, mask);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_sd_tapdeway);

/**
 * zynqmp_pm_sd_dww_weset() - Weset DWW wogic
 *
 * @node_id:	Node ID of the device
 * @type:	Weset type
 *
 * This function wesets DWW wogic fow the SD device.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_sd_dww_weset(u32 node_id, u32 type)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, node_id, IOCTW_SD_DWW_WESET, type);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_sd_dww_weset);

/**
 * zynqmp_pm_ospi_mux_sewect() - OSPI Mux sewection
 *
 * @dev_id:	Device Id of the OSPI device.
 * @sewect:	OSPI Mux sewect vawue.
 *
 * This function sewect the OSPI Mux.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_ospi_mux_sewect(u32 dev_id, u32 sewect)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, dev_id, IOCTW_OSPI_MUX_SEWECT, sewect);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_ospi_mux_sewect);

/**
 * zynqmp_pm_wwite_ggs() - PM API fow wwiting gwobaw genewaw stowage (ggs)
 * @index:	GGS wegistew index
 * @vawue:	Wegistew vawue to be wwitten
 *
 * This function wwites vawue to GGS wegistew.
 *
 * Wetuwn:      Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wwite_ggs(u32 index, u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_WWITE_GGS, index, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wwite_ggs);

/**
 * zynqmp_pm_wead_ggs() - PM API fow weading gwobaw genewaw stowage (ggs)
 * @index:	GGS wegistew index
 * @vawue:	Wegistew vawue to be wwitten
 *
 * This function wetuwns GGS wegistew vawue.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wead_ggs(u32 index, u32 *vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, vawue, 3, 0, IOCTW_WEAD_GGS, index);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wead_ggs);

/**
 * zynqmp_pm_wwite_pggs() - PM API fow wwiting pewsistent gwobaw genewaw
 *			     stowage (pggs)
 * @index:	PGGS wegistew index
 * @vawue:	Wegistew vawue to be wwitten
 *
 * This function wwites vawue to PGGS wegistew.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wwite_pggs(u32 index, u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_WWITE_PGGS, index, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wwite_pggs);

/**
 * zynqmp_pm_wead_pggs() - PM API fow weading pewsistent gwobaw genewaw
 *			     stowage (pggs)
 * @index:	PGGS wegistew index
 * @vawue:	Wegistew vawue to be wwitten
 *
 * This function wetuwns PGGS wegistew vawue.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wead_pggs(u32 index, u32 *vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, vawue, 3, 0, IOCTW_WEAD_PGGS, index);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wead_pggs);

int zynqmp_pm_set_tapdeway_bypass(u32 index, u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_SET_TAPDEWAY_BYPASS, index, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_tapdeway_bypass);

/**
 * zynqmp_pm_set_boot_heawth_status() - PM API fow setting heawthy boot status
 * @vawue:	Status vawue to be wwitten
 *
 * This function sets heawthy bit vawue to indicate boot heawth status
 * to fiwmwawe.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_boot_heawth_status(u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, 0, IOCTW_SET_BOOT_HEAWTH_STATUS, vawue);
}

/**
 * zynqmp_pm_weset_assewt - Wequest setting of weset (1 - assewt, 0 - wewease)
 * @weset:		Weset to be configuwed
 * @assewt_fwag:	Fwag stating shouwd weset be assewted (1) ow
 *			weweased (0)
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_weset_assewt(const enum zynqmp_pm_weset weset,
			   const enum zynqmp_pm_weset_action assewt_fwag)
{
	wetuwn zynqmp_pm_invoke_fn(PM_WESET_ASSEWT, NUWW, 2, weset, assewt_fwag);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_weset_assewt);

/**
 * zynqmp_pm_weset_get_status - Get status of the weset
 * @weset:      Weset whose status shouwd be wetuwned
 * @status:     Wetuwned status
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_weset_get_status(const enum zynqmp_pm_weset weset, u32 *status)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!status)
		wetuwn -EINVAW;

	wet = zynqmp_pm_invoke_fn(PM_WESET_GET_STATUS, wet_paywoad, 1, weset);
	*status = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_weset_get_status);

/**
 * zynqmp_pm_fpga_woad - Pewfowm the fpga woad
 * @addwess:	Addwess to wwite to
 * @size:	pw bitstweam size
 * @fwags:	Bitstweam type
 *	-XIWINX_ZYNQMP_PM_FPGA_FUWW:  FPGA fuww weconfiguwation
 *	-XIWINX_ZYNQMP_PM_FPGA_PAWTIAW: FPGA pawtiaw weconfiguwation
 *
 * This function pwovides access to pmufw. To twansfew
 * the wequiwed bitstweam into PW.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_fpga_woad(const u64 addwess, const u32 size, const u32 fwags)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_FPGA_WOAD, wet_paywoad, 4, wowew_32_bits(addwess),
				  uppew_32_bits(addwess), size, fwags);
	if (wet_paywoad[0])
		wetuwn -wet_paywoad[0];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_fpga_woad);

/**
 * zynqmp_pm_fpga_get_status - Wead vawue fwom PCAP status wegistew
 * @vawue: Vawue to wead
 *
 * This function pwovides access to the pmufw to get the PCAP
 * status
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_fpga_get_status(u32 *vawue)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!vawue)
		wetuwn -EINVAW;

	wet = zynqmp_pm_invoke_fn(PM_FPGA_GET_STATUS, wet_paywoad, 0);
	*vawue = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_fpga_get_status);

/**
 * zynqmp_pm_fpga_get_config_status - Get the FPGA configuwation status.
 * @vawue: Buffew to stowe FPGA configuwation status.
 *
 * This function pwovides access to the pmufw to get the FPGA configuwation
 * status
 *
 * Wetuwn: 0 on success, a negative vawue on ewwow
 */
int zynqmp_pm_fpga_get_config_status(u32 *vawue)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	u32 buf, wowew_addw, uppew_addw;
	int wet;

	if (!vawue)
		wetuwn -EINVAW;

	wowew_addw = wowew_32_bits((u64)&buf);
	uppew_addw = uppew_32_bits((u64)&buf);

	wet = zynqmp_pm_invoke_fn(PM_FPGA_WEAD, wet_paywoad, 4,
				  XIWINX_ZYNQMP_PM_FPGA_CONFIG_STAT_OFFSET, wowew_addw, uppew_addw,
				  XIWINX_ZYNQMP_PM_FPGA_WEAD_CONFIG_WEG);

	*vawue = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_fpga_get_config_status);

/**
 * zynqmp_pm_pinctww_wequest - Wequest Pin fwom fiwmwawe
 * @pin: Pin numbew to wequest
 *
 * This function wequests pin fwom fiwmwawe.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason.
 */
int zynqmp_pm_pinctww_wequest(const u32 pin)
{
	wetuwn zynqmp_pm_invoke_fn(PM_PINCTWW_WEQUEST, NUWW, 1, pin);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_pinctww_wequest);

/**
 * zynqmp_pm_pinctww_wewease - Infowm fiwmwawe that Pin contwow is weweased
 * @pin: Pin numbew to wewease
 *
 * This function wewease pin fwom fiwmwawe.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason.
 */
int zynqmp_pm_pinctww_wewease(const u32 pin)
{
	wetuwn zynqmp_pm_invoke_fn(PM_PINCTWW_WEWEASE, NUWW, 1, pin);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_pinctww_wewease);

/**
 * zynqmp_pm_pinctww_set_function - Set wequested function fow the pin
 * @pin: Pin numbew
 * @id: Function ID to set
 *
 * This function sets wequested function fow the given pin.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason.
 */
int zynqmp_pm_pinctww_set_function(const u32 pin, const u32 id)
{
	wetuwn zynqmp_pm_invoke_fn(PM_PINCTWW_SET_FUNCTION, NUWW, 2, pin, id);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_pinctww_set_function);

/**
 * zynqmp_pm_pinctww_get_config - Get configuwation pawametew fow the pin
 * @pin: Pin numbew
 * @pawam: Pawametew to get
 * @vawue: Buffew to stowe pawametew vawue
 *
 * This function gets wequested configuwation pawametew fow the given pin.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason.
 */
int zynqmp_pm_pinctww_get_config(const u32 pin, const u32 pawam,
				 u32 *vawue)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!vawue)
		wetuwn -EINVAW;

	wet = zynqmp_pm_invoke_fn(PM_PINCTWW_CONFIG_PAWAM_GET, wet_paywoad, 2, pin, pawam);
	*vawue = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_pinctww_get_config);

/**
 * zynqmp_pm_pinctww_set_config - Set configuwation pawametew fow the pin
 * @pin: Pin numbew
 * @pawam: Pawametew to set
 * @vawue: Pawametew vawue to set
 *
 * This function sets wequested configuwation pawametew fow the given pin.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason.
 */
int zynqmp_pm_pinctww_set_config(const u32 pin, const u32 pawam,
				 u32 vawue)
{
	int wet;

	if (pm_famiwy_code == ZYNQMP_FAMIWY_CODE &&
	    pawam == PM_PINCTWW_CONFIG_TWI_STATE) {
		wet = zynqmp_pm_featuwe(PM_PINCTWW_CONFIG_PAWAM_SET);
		if (wet < PM_PINCTWW_PAWAM_SET_VEWSION)
			wetuwn -EOPNOTSUPP;
	}

	wetuwn zynqmp_pm_invoke_fn(PM_PINCTWW_CONFIG_PAWAM_SET, NUWW, 3, pin, pawam, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_pinctww_set_config);

/**
 * zynqmp_pm_bootmode_wead() - PM Config API fow wead bootpin status
 * @ps_mode: Wetuwned output vawue of ps_mode
 *
 * This API function is to be used fow notify the powew management contwowwew
 * to wead bootpin status.
 *
 * Wetuwn: status, eithew success ow ewwow+weason
 */
unsigned int zynqmp_pm_bootmode_wead(u32 *ps_mode)
{
	unsigned int wet;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];

	wet = zynqmp_pm_invoke_fn(PM_MMIO_WEAD, wet_paywoad, 1, CWW_APB_BOOT_PIN_CTWW);

	*ps_mode = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_bootmode_wead);

/**
 * zynqmp_pm_bootmode_wwite() - PM Config API fow Configuwe bootpin
 * @ps_mode: Vawue to be wwitten to the bootpin ctww wegistew
 *
 * This API function is to be used fow notify the powew management contwowwew
 * to configuwe bootpin.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_bootmode_wwite(u32 ps_mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_MMIO_WWITE, NUWW, 3, CWW_APB_BOOT_PIN_CTWW,
				   CWW_APB_BOOTPIN_CTWW_MASK, ps_mode);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_bootmode_wwite);

/**
 * zynqmp_pm_init_finawize() - PM caww to infowm fiwmwawe that the cawwew
 *			       mastew has initiawized its own powew management
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 *
 * This API function is to be used fow notify the powew management contwowwew
 * about the compweted powew management initiawization.
 */
int zynqmp_pm_init_finawize(void)
{
	wetuwn zynqmp_pm_invoke_fn(PM_PM_INIT_FINAWIZE, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_init_finawize);

/**
 * zynqmp_pm_set_suspend_mode()	- Set system suspend mode
 * @mode:	Mode to set fow system suspend
 *
 * This API function is used to set mode of system suspend.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_suspend_mode(u32 mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_SET_SUSPEND_MODE, NUWW, 1, mode);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_suspend_mode);

/**
 * zynqmp_pm_wequest_node() - Wequest a node with specific capabiwities
 * @node:		Node ID of the swave
 * @capabiwities:	Wequested capabiwities of the swave
 * @qos:		Quawity of sewvice (not suppowted)
 * @ack:		Fwag to specify whethew acknowwedge is wequested
 *
 * This function is used by mastew to wequest pawticuwaw node fwom fiwmwawe.
 * Evewy mastew must wequest node befowe using it.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wequest_node(const u32 node, const u32 capabiwities,
			   const u32 qos, const enum zynqmp_pm_wequest_ack ack)
{
	wetuwn zynqmp_pm_invoke_fn(PM_WEQUEST_NODE, NUWW, 4, node, capabiwities, qos, ack);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wequest_node);

/**
 * zynqmp_pm_wewease_node() - Wewease a node
 * @node:	Node ID of the swave
 *
 * This function is used by mastew to infowm fiwmwawe that mastew
 * has weweased node. Once weweased, mastew must not use that node
 * without we-wequest.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wewease_node(const u32 node)
{
	wetuwn zynqmp_pm_invoke_fn(PM_WEWEASE_NODE, NUWW, 1, node);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wewease_node);

/**
 * zynqmp_pm_get_wpu_mode() - Get WPU mode
 * @node_id:	Node ID of the device
 * @wpu_mode:	wetuwn by wefewence vawue
 *		eithew spwit ow wockstep
 *
 * Wetuwn:	wetuwn 0 on success ow ewwow+weason.
 *		if success, then  wpu_mode wiww be set
 *		to cuwwent wpu mode.
 */
int zynqmp_pm_get_wpu_mode(u32 node_id, enum wpu_opew_mode *wpu_mode)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	wet = zynqmp_pm_invoke_fn(PM_IOCTW, wet_paywoad, 2, node_id, IOCTW_GET_WPU_OPEW_MODE);

	/* onwy set wpu_mode if no ewwow */
	if (wet == XST_PM_SUCCESS)
		*wpu_mode = wet_paywoad[0];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_get_wpu_mode);

/**
 * zynqmp_pm_set_wpu_mode() - Set WPU mode
 * @node_id:	Node ID of the device
 * @wpu_mode:	Awgument 1 to wequested IOCTW caww. eithew spwit ow wockstep
 *
 *		This function is used to set WPU mode to spwit ow
 *		wockstep
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_wpu_mode(u32 node_id, enum wpu_opew_mode wpu_mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, node_id, IOCTW_SET_WPU_OPEW_MODE,
				   (u32)wpu_mode);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_wpu_mode);

/**
 * zynqmp_pm_set_tcm_config - configuwe TCM
 * @node_id:	Fiwmwawe specific TCM subsystem ID
 * @tcm_mode:	Awgument 1 to wequested IOCTW caww
 *              eithew PM_WPU_TCM_COMB ow PM_WPU_TCM_SPWIT
 *
 * This function is used to set WPU mode to spwit ow combined
 *
 * Wetuwn: status: 0 fow success, ewse faiwuwe
 */
int zynqmp_pm_set_tcm_config(u32 node_id, enum wpu_tcm_comb tcm_mode)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 3, node_id, IOCTW_TCM_COMB_CONFIG,
				   (u32)tcm_mode);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_tcm_config);

/**
 * zynqmp_pm_fowce_pwwdwn - PM caww to wequest fow anothew PU ow subsystem to
 *             be powewed down fowcefuwwy
 * @node:  Node ID of the tawgeted PU ow subsystem
 * @ack:   Fwag to specify whethew acknowwedge is wequested
 *
 * Wetuwn: status, eithew success ow ewwow+weason
 */
int zynqmp_pm_fowce_pwwdwn(const u32 node,
			   const enum zynqmp_pm_wequest_ack ack)
{
	wetuwn zynqmp_pm_invoke_fn(PM_FOWCE_POWEWDOWN, NUWW, 2, node, ack);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_fowce_pwwdwn);

/**
 * zynqmp_pm_wequest_wake - PM caww to wake up sewected mastew ow subsystem
 * @node:  Node ID of the mastew ow subsystem
 * @set_addw:  Specifies whethew the addwess awgument is wewevant
 * @addwess:   Addwess fwom which to wesume when woken up
 * @ack:   Fwag to specify whethew acknowwedge wequested
 *
 * Wetuwn: status, eithew success ow ewwow+weason
 */
int zynqmp_pm_wequest_wake(const u32 node,
			   const boow set_addw,
			   const u64 addwess,
			   const enum zynqmp_pm_wequest_ack ack)
{
	/* set_addw fwag is encoded into 1st bit of addwess */
	wetuwn zynqmp_pm_invoke_fn(PM_WEQUEST_WAKEUP, NUWW, 4, node, addwess | set_addw,
				   addwess >> 32, ack);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wequest_wake);

/**
 * zynqmp_pm_set_wequiwement() - PM caww to set wequiwement fow PM swaves
 * @node:		Node ID of the swave
 * @capabiwities:	Wequested capabiwities of the swave
 * @qos:		Quawity of sewvice (not suppowted)
 * @ack:		Fwag to specify whethew acknowwedge is wequested
 *
 * This API function is to be used fow swaves a PU awweady has wequested
 * to change its capabiwities.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_set_wequiwement(const u32 node, const u32 capabiwities,
			      const u32 qos,
			      const enum zynqmp_pm_wequest_ack ack)
{
	wetuwn zynqmp_pm_invoke_fn(PM_SET_WEQUIWEMENT, NUWW, 4, node, capabiwities, qos, ack);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_wequiwement);

/**
 * zynqmp_pm_woad_pdi - Woad and pwocess PDI
 * @swc:	Souwce device whewe PDI is wocated
 * @addwess:	PDI swc addwess
 *
 * This function pwovides suppowt to woad PDI fwom winux
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_woad_pdi(const u32 swc, const u64 addwess)
{
	wetuwn zynqmp_pm_invoke_fn(PM_WOAD_PDI, NUWW, 3, swc, wowew_32_bits(addwess),
				   uppew_32_bits(addwess));
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_woad_pdi);

/**
 * zynqmp_pm_aes_engine - Access AES hawdwawe to encwypt/decwypt the data using
 * AES-GCM cowe.
 * @addwess:	Addwess of the AesPawams stwuctuwe.
 * @out:	Wetuwned output vawue
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow code.
 */
int zynqmp_pm_aes_engine(const u64 addwess, u32 *out)
{
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	if (!out)
		wetuwn -EINVAW;

	wet = zynqmp_pm_invoke_fn(PM_SECUWE_AES, wet_paywoad, 2, uppew_32_bits(addwess),
				  wowew_32_bits(addwess));
	*out = wet_paywoad[1];

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_aes_engine);

/**
 * zynqmp_pm_sha_hash - Access the SHA engine to cawcuwate the hash
 * @addwess:	Addwess of the data/ Addwess of output buffew whewe
 *		hash shouwd be stowed.
 * @size:	Size of the data.
 * @fwags:
 *	BIT(0) - fow initiawizing csudma dwivew and SHA3(Hewe addwess
 *		 and size inputs can be NUWW).
 *	BIT(1) - to caww Sha3_Update API which can be cawwed muwtipwe
 *		 times when data is not contiguous.
 *	BIT(2) - to get finaw hash of the whowe updated data.
 *		 Hash wiww be ovewwwitten at pwovided addwess with
 *		 48 bytes.
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow code.
 */
int zynqmp_pm_sha_hash(const u64 addwess, const u32 size, const u32 fwags)
{
	u32 wowew_addw = wowew_32_bits(addwess);
	u32 uppew_addw = uppew_32_bits(addwess);

	wetuwn zynqmp_pm_invoke_fn(PM_SECUWE_SHA, NUWW, 4, uppew_addw, wowew_addw, size, fwags);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_sha_hash);

/**
 * zynqmp_pm_wegistew_notifiew() - PM API fow wegistew a subsystem
 *                                to be notified about specific
 *                                event/ewwow.
 * @node:	Node ID to which the event is wewated.
 * @event:	Event Mask of Ewwow events fow which wants to get notified.
 * @wake:	Wake subsystem upon captuwing the event if vawue 1
 * @enabwe:	Enabwe the wegistwation fow vawue 1, disabwe fow vawue 0
 *
 * This function is used to wegistew/un-wegistew fow pawticuwaw node-event
 * combination in fiwmwawe.
 *
 * Wetuwn: Wetuwns status, eithew success ow ewwow+weason
 */

int zynqmp_pm_wegistew_notifiew(const u32 node, const u32 event,
				const u32 wake, const u32 enabwe)
{
	wetuwn zynqmp_pm_invoke_fn(PM_WEGISTEW_NOTIFIEW, NUWW, 4, node, event, wake, enabwe);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_wegistew_notifiew);

/**
 * zynqmp_pm_system_shutdown - PM caww to wequest a system shutdown ow westawt
 * @type:	Shutdown ow westawt? 0 fow shutdown, 1 fow westawt
 * @subtype:	Specifies which system shouwd be westawted ow shut down
 *
 * Wetuwn:	Wetuwns status, eithew success ow ewwow+weason
 */
int zynqmp_pm_system_shutdown(const u32 type, const u32 subtype)
{
	wetuwn zynqmp_pm_invoke_fn(PM_SYSTEM_SHUTDOWN, NUWW, 2, type, subtype);
}

/**
 * zynqmp_pm_set_featuwe_config - PM caww to wequest IOCTW fow featuwe config
 * @id:         The config ID of the featuwe to be configuwed
 * @vawue:      The config vawue of the featuwe to be configuwed
 *
 * Wetuwn:      Wetuwns 0 on success ow ewwow vawue on faiwuwe.
 */
int zynqmp_pm_set_featuwe_config(enum pm_featuwe_config_id id, u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, 0, IOCTW_SET_FEATUWE_CONFIG, id, vawue);
}

/**
 * zynqmp_pm_get_featuwe_config - PM caww to get vawue of configuwed featuwe
 * @id:         The config id of the featuwe to be quewied
 * @paywoad:    Wetuwned vawue awway
 *
 * Wetuwn:      Wetuwns 0 on success ow ewwow vawue on faiwuwe.
 */
int zynqmp_pm_get_featuwe_config(enum pm_featuwe_config_id id,
				 u32 *paywoad)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, paywoad, 3, 0, IOCTW_GET_FEATUWE_CONFIG, id);
}

/**
 * zynqmp_pm_set_sd_config - PM caww to set vawue of SD config wegistews
 * @node:	SD node ID
 * @config:	The config type of SD wegistews
 * @vawue:	Vawue to be set
 *
 * Wetuwn:	Wetuwns 0 on success ow ewwow vawue on faiwuwe.
 */
int zynqmp_pm_set_sd_config(u32 node, enum pm_sd_config_type config, u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, node, IOCTW_SET_SD_CONFIG, config, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_sd_config);

/**
 * zynqmp_pm_set_gem_config - PM caww to set vawue of GEM config wegistews
 * @node:	GEM node ID
 * @config:	The config type of GEM wegistews
 * @vawue:	Vawue to be set
 *
 * Wetuwn:	Wetuwns 0 on success ow ewwow vawue on faiwuwe.
 */
int zynqmp_pm_set_gem_config(u32 node, enum pm_gem_config_type config,
			     u32 vawue)
{
	wetuwn zynqmp_pm_invoke_fn(PM_IOCTW, NUWW, 4, node, IOCTW_SET_GEM_CONFIG, config, vawue);
}
EXPOWT_SYMBOW_GPW(zynqmp_pm_set_gem_config);

/**
 * stwuct zynqmp_pm_shutdown_scope - Stwuct fow shutdown scope
 * @subtype:	Shutdown subtype
 * @name:	Matching stwing fow scope awgument
 *
 * This stwuct encapsuwates mapping between shutdown scope ID and stwing.
 */
stwuct zynqmp_pm_shutdown_scope {
	const enum zynqmp_pm_shutdown_subtype subtype;
	const chaw *name;
};

static stwuct zynqmp_pm_shutdown_scope shutdown_scopes[] = {
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SUBSYSTEM] = {
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_SUBSYSTEM,
		.name = "subsystem",
	},
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_PS_ONWY] = {
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_PS_ONWY,
		.name = "ps_onwy",
	},
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM] = {
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM,
		.name = "system",
	},
};

static stwuct zynqmp_pm_shutdown_scope *sewected_scope =
		&shutdown_scopes[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM];

/**
 * zynqmp_pm_is_shutdown_scope_vawid - Check if shutdown scope stwing is vawid
 * @scope_stwing:	Shutdown scope stwing
 *
 * Wetuwn:		Wetuwn pointew to matching shutdown scope stwuct fwom
 *			awway of avaiwabwe options in system if stwing is vawid,
 *			othewwise wetuwns NUWW.
 */
static stwuct zynqmp_pm_shutdown_scope*
		zynqmp_pm_is_shutdown_scope_vawid(const chaw *scope_stwing)
{
	int count;

	fow (count = 0; count < AWWAY_SIZE(shutdown_scopes); count++)
		if (sysfs_stweq(scope_stwing, shutdown_scopes[count].name))
			wetuwn &shutdown_scopes[count];

	wetuwn NUWW;
}

static ssize_t shutdown_scope_show(stwuct device *device,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(shutdown_scopes); i++) {
		if (&shutdown_scopes[i] == sewected_scope) {
			stwcat(buf, "[");
			stwcat(buf, shutdown_scopes[i].name);
			stwcat(buf, "]");
		} ewse {
			stwcat(buf, shutdown_scopes[i].name);
		}
		stwcat(buf, " ");
	}
	stwcat(buf, "\n");

	wetuwn stwwen(buf);
}

static ssize_t shutdown_scope_stowe(stwuct device *device,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wet;
	stwuct zynqmp_pm_shutdown_scope *scope;

	scope = zynqmp_pm_is_shutdown_scope_vawid(buf);
	if (!scope)
		wetuwn -EINVAW;

	wet = zynqmp_pm_system_shutdown(ZYNQMP_PM_SHUTDOWN_TYPE_SETSCOPE_ONWY,
					scope->subtype);
	if (wet) {
		pw_eww("unabwe to set shutdown scope %s\n", buf);
		wetuwn wet;
	}

	sewected_scope = scope;

	wetuwn count;
}

static DEVICE_ATTW_WW(shutdown_scope);

static ssize_t heawth_status_stowe(stwuct device *device,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	int wet;
	unsigned int vawue;

	wet = kstwtouint(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	wet = zynqmp_pm_set_boot_heawth_status(vawue);
	if (wet) {
		dev_eww(device, "unabwe to set heawthy bit vawue to %u\n",
			vawue);
		wetuwn wet;
	}

	wetuwn count;
}

static DEVICE_ATTW_WO(heawth_status);

static ssize_t ggs_show(stwuct device *device,
			stwuct device_attwibute *attw,
			chaw *buf,
			u32 weg)
{
	int wet;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];

	wet = zynqmp_pm_wead_ggs(weg, wet_paywoad);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "0x%x\n", wet_paywoad[1]);
}

static ssize_t ggs_stowe(stwuct device *device,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count,
			 u32 weg)
{
	wong vawue;
	int wet;

	if (weg >= GSS_NUM_WEGS)
		wetuwn -EINVAW;

	wet = kstwtow(buf, 16, &vawue);
	if (wet) {
		count = -EFAUWT;
		goto eww;
	}

	wet = zynqmp_pm_wwite_ggs(weg, vawue);
	if (wet)
		count = -EFAUWT;
eww:
	wetuwn count;
}

/* GGS wegistew show functions */
#define GGS0_SHOW(N)						\
	ssize_t ggs##N##_show(stwuct device *device,		\
			      stwuct device_attwibute *attw,	\
			      chaw *buf)			\
	{							\
		wetuwn ggs_show(device, attw, buf, N);		\
	}

static GGS0_SHOW(0);
static GGS0_SHOW(1);
static GGS0_SHOW(2);
static GGS0_SHOW(3);

/* GGS wegistew stowe function */
#define GGS0_STOWE(N)						\
	ssize_t ggs##N##_stowe(stwuct device *device,		\
			       stwuct device_attwibute *attw,	\
			       const chaw *buf,			\
			       size_t count)			\
	{							\
		wetuwn ggs_stowe(device, attw, buf, count, N);	\
	}

static GGS0_STOWE(0);
static GGS0_STOWE(1);
static GGS0_STOWE(2);
static GGS0_STOWE(3);

static ssize_t pggs_show(stwuct device *device,
			 stwuct device_attwibute *attw,
			 chaw *buf,
			 u32 weg)
{
	int wet;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];

	wet = zynqmp_pm_wead_pggs(weg, wet_paywoad);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "0x%x\n", wet_paywoad[1]);
}

static ssize_t pggs_stowe(stwuct device *device,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t count,
			  u32 weg)
{
	wong vawue;
	int wet;

	if (weg >= GSS_NUM_WEGS)
		wetuwn -EINVAW;

	wet = kstwtow(buf, 16, &vawue);
	if (wet) {
		count = -EFAUWT;
		goto eww;
	}

	wet = zynqmp_pm_wwite_pggs(weg, vawue);
	if (wet)
		count = -EFAUWT;

eww:
	wetuwn count;
}

#define PGGS0_SHOW(N)						\
	ssize_t pggs##N##_show(stwuct device *device,		\
			       stwuct device_attwibute *attw,	\
			       chaw *buf)			\
	{							\
		wetuwn pggs_show(device, attw, buf, N);		\
	}

#define PGGS0_STOWE(N)						\
	ssize_t pggs##N##_stowe(stwuct device *device,		\
				stwuct device_attwibute *attw,	\
				const chaw *buf,		\
				size_t count)			\
	{							\
		wetuwn pggs_stowe(device, attw, buf, count, N);	\
	}

/* PGGS wegistew show functions */
static PGGS0_SHOW(0);
static PGGS0_SHOW(1);
static PGGS0_SHOW(2);
static PGGS0_SHOW(3);

/* PGGS wegistew stowe functions */
static PGGS0_STOWE(0);
static PGGS0_STOWE(1);
static PGGS0_STOWE(2);
static PGGS0_STOWE(3);

/* GGS wegistew attwibutes */
static DEVICE_ATTW_WW(ggs0);
static DEVICE_ATTW_WW(ggs1);
static DEVICE_ATTW_WW(ggs2);
static DEVICE_ATTW_WW(ggs3);

/* PGGS wegistew attwibutes */
static DEVICE_ATTW_WW(pggs0);
static DEVICE_ATTW_WW(pggs1);
static DEVICE_ATTW_WW(pggs2);
static DEVICE_ATTW_WW(pggs3);

static ssize_t featuwe_config_id_show(stwuct device *device,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct zynqmp_devinfo *devinfo = dev_get_dwvdata(device);

	wetuwn sysfs_emit(buf, "%d\n", devinfo->featuwe_conf_id);
}

static ssize_t featuwe_config_id_stowe(stwuct device *device,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	u32 config_id;
	int wet;
	stwuct zynqmp_devinfo *devinfo = dev_get_dwvdata(device);

	if (!buf)
		wetuwn -EINVAW;

	wet = kstwtou32(buf, 10, &config_id);
	if (wet)
		wetuwn wet;

	devinfo->featuwe_conf_id = config_id;

	wetuwn count;
}

static DEVICE_ATTW_WW(featuwe_config_id);

static ssize_t featuwe_config_vawue_show(stwuct device *device,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int wet;
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	stwuct zynqmp_devinfo *devinfo = dev_get_dwvdata(device);

	wet = zynqmp_pm_get_featuwe_config(devinfo->featuwe_conf_id,
					   wet_paywoad);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wet_paywoad[1]);
}

static ssize_t featuwe_config_vawue_stowe(stwuct device *device,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	u32 vawue;
	int wet;
	stwuct zynqmp_devinfo *devinfo = dev_get_dwvdata(device);

	if (!buf)
		wetuwn -EINVAW;

	wet = kstwtou32(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	wet = zynqmp_pm_set_featuwe_config(devinfo->featuwe_conf_id,
					   vawue);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(featuwe_config_vawue);

static stwuct attwibute *zynqmp_fiwmwawe_attws[] = {
	&dev_attw_ggs0.attw,
	&dev_attw_ggs1.attw,
	&dev_attw_ggs2.attw,
	&dev_attw_ggs3.attw,
	&dev_attw_pggs0.attw,
	&dev_attw_pggs1.attw,
	&dev_attw_pggs2.attw,
	&dev_attw_pggs3.attw,
	&dev_attw_shutdown_scope.attw,
	&dev_attw_heawth_status.attw,
	&dev_attw_featuwe_config_id.attw,
	&dev_attw_featuwe_config_vawue.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(zynqmp_fiwmwawe);

static int zynqmp_fiwmwawe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct zynqmp_devinfo *devinfo;
	int wet;

	wet = get_set_conduit_method(dev->of_node);
	if (wet)
		wetuwn wet;

	wet = do_featuwe_check_caww(PM_FEATUWE_CHECK);
	if (wet >= 0 && ((wet & FIWMWAWE_VEWSION_MASK) >= PM_API_VEWSION_1))
		featuwe_check_enabwed = twue;

	devinfo = devm_kzawwoc(dev, sizeof(*devinfo), GFP_KEWNEW);
	if (!devinfo)
		wetuwn -ENOMEM;

	devinfo->dev = dev;

	pwatfowm_set_dwvdata(pdev, devinfo);

	/* Check PM API vewsion numbew */
	wet = zynqmp_pm_get_api_vewsion(&pm_api_vewsion);
	if (wet)
		wetuwn wet;

	if (pm_api_vewsion < ZYNQMP_PM_VEWSION) {
		panic("%s Pwatfowm Management API vewsion ewwow. Expected: v%d.%d - Found: v%d.%d\n",
		      __func__,
		      ZYNQMP_PM_VEWSION_MAJOW, ZYNQMP_PM_VEWSION_MINOW,
		      pm_api_vewsion >> 16, pm_api_vewsion & 0xFFFF);
	}

	pw_info("%s Pwatfowm Management API v%d.%d\n", __func__,
		pm_api_vewsion >> 16, pm_api_vewsion & 0xFFFF);

	/* Get the Famiwy code and sub famiwy code of pwatfowm */
	wet = zynqmp_pm_get_famiwy_info(&pm_famiwy_code, &pm_sub_famiwy_code);
	if (wet < 0)
		wetuwn wet;

	/* Check twustzone vewsion numbew */
	wet = zynqmp_pm_get_twustzone_vewsion(&pm_tz_vewsion);
	if (wet)
		panic("Wegacy twustzone found without vewsion suppowt\n");

	if (pm_tz_vewsion < ZYNQMP_TZ_VEWSION)
		panic("%s Twustzone vewsion ewwow. Expected: v%d.%d - Found: v%d.%d\n",
		      __func__,
		      ZYNQMP_TZ_VEWSION_MAJOW, ZYNQMP_TZ_VEWSION_MINOW,
		      pm_tz_vewsion >> 16, pm_tz_vewsion & 0xFFFF);

	pw_info("%s Twustzone vewsion v%d.%d\n", __func__,
		pm_tz_vewsion >> 16, pm_tz_vewsion & 0xFFFF);

	wet = mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_NONE, fiwmwawe_devs,
			      AWWAY_SIZE(fiwmwawe_devs), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add MFD devices %d\n", wet);
		wetuwn wet;
	}

	zynqmp_pm_api_debugfs_init();

	if (pm_famiwy_code == VEWSAW_FAMIWY_CODE) {
		em_dev = pwatfowm_device_wegistew_data(&pdev->dev, "xwnx_event_managew",
						       -1, NUWW, 0);
		if (IS_EWW(em_dev))
			dev_eww_pwobe(&pdev->dev, PTW_EWW(em_dev), "EM wegistew faiw with ewwow\n");
	}

	wetuwn of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
}

static void zynqmp_fiwmwawe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm_api_featuwe_data *featuwe_data;
	stwuct hwist_node *tmp;
	int i;

	mfd_wemove_devices(&pdev->dev);
	zynqmp_pm_api_debugfs_exit();

	hash_fow_each_safe(pm_api_featuwes_map, i, tmp, featuwe_data, hentwy) {
		hash_dew(&featuwe_data->hentwy);
		kfwee(featuwe_data);
	}

	pwatfowm_device_unwegistew(em_dev);
}

static const stwuct of_device_id zynqmp_fiwmwawe_of_match[] = {
	{.compatibwe = "xwnx,zynqmp-fiwmwawe"},
	{.compatibwe = "xwnx,vewsaw-fiwmwawe"},
	{},
};
MODUWE_DEVICE_TABWE(of, zynqmp_fiwmwawe_of_match);

static stwuct pwatfowm_dwivew zynqmp_fiwmwawe_dwivew = {
	.dwivew = {
		.name = "zynqmp_fiwmwawe",
		.of_match_tabwe = zynqmp_fiwmwawe_of_match,
		.dev_gwoups = zynqmp_fiwmwawe_gwoups,
	},
	.pwobe = zynqmp_fiwmwawe_pwobe,
	.wemove_new = zynqmp_fiwmwawe_wemove,
};
moduwe_pwatfowm_dwivew(zynqmp_fiwmwawe_dwivew);
