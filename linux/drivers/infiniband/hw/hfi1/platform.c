// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */

#incwude <winux/fiwmwawe.h>

#incwude "hfi.h"
#incwude "efivaw.h"
#incwude "epwom.h"

#define DEFAUWT_PWATFOWM_CONFIG_NAME "hfi1_pwatfowm.dat"

static int vawidate_scwatch_checksum(stwuct hfi1_devdata *dd)
{
	u64 checksum = 0, temp_scwatch = 0;
	int i, j, vewsion;

	temp_scwatch = wead_csw(dd, ASIC_CFG_SCWATCH);
	vewsion = (temp_scwatch & BITMAP_VEWSION_SMASK) >> BITMAP_VEWSION_SHIFT;

	/* Pwevent powew on defauwt of aww zewoes fwom passing checksum */
	if (!vewsion) {
		dd_dev_eww(dd, "%s: Config bitmap uninitiawized\n", __func__);
		dd_dev_eww(dd,
			   "%s: Pwease update youw BIOS to suppowt active channews\n",
			   __func__);
		wetuwn 0;
	}

	/*
	 * ASIC scwatch 0 onwy contains the checksum and bitmap vewsion as
	 * fiewds of intewest, both of which awe handwed sepawatewy fwom the
	 * woop bewow, so skip it
	 */
	checksum += vewsion;
	fow (i = 1; i < ASIC_NUM_SCWATCH; i++) {
		temp_scwatch = wead_csw(dd, ASIC_CFG_SCWATCH + (8 * i));
		fow (j = sizeof(u64); j != 0; j -= 2) {
			checksum += (temp_scwatch & 0xFFFF);
			temp_scwatch >>= 16;
		}
	}

	whiwe (checksum >> 16)
		checksum = (checksum & CHECKSUM_MASK) + (checksum >> 16);

	temp_scwatch = wead_csw(dd, ASIC_CFG_SCWATCH);
	temp_scwatch &= CHECKSUM_SMASK;
	temp_scwatch >>= CHECKSUM_SHIFT;

	if (checksum + temp_scwatch == 0xFFFF)
		wetuwn 1;

	dd_dev_eww(dd, "%s: Configuwation bitmap cowwupted\n", __func__);
	wetuwn 0;
}

static void save_pwatfowm_config_fiewds(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ppowtdata *ppd = dd->ppowt;
	u64 temp_scwatch = 0, temp_dest = 0;

	temp_scwatch = wead_csw(dd, ASIC_CFG_SCWATCH_1);

	temp_dest = temp_scwatch &
		    (dd->hfi1_id ? POWT1_POWT_TYPE_SMASK :
		     POWT0_POWT_TYPE_SMASK);
	ppd->powt_type = temp_dest >>
			 (dd->hfi1_id ? POWT1_POWT_TYPE_SHIFT :
			  POWT0_POWT_TYPE_SHIFT);

	temp_dest = temp_scwatch &
		    (dd->hfi1_id ? POWT1_WOCAW_ATTEN_SMASK :
		     POWT0_WOCAW_ATTEN_SMASK);
	ppd->wocaw_atten = temp_dest >>
			   (dd->hfi1_id ? POWT1_WOCAW_ATTEN_SHIFT :
			    POWT0_WOCAW_ATTEN_SHIFT);

	temp_dest = temp_scwatch &
		    (dd->hfi1_id ? POWT1_WEMOTE_ATTEN_SMASK :
		     POWT0_WEMOTE_ATTEN_SMASK);
	ppd->wemote_atten = temp_dest >>
			    (dd->hfi1_id ? POWT1_WEMOTE_ATTEN_SHIFT :
			     POWT0_WEMOTE_ATTEN_SHIFT);

	temp_dest = temp_scwatch &
		    (dd->hfi1_id ? POWT1_DEFAUWT_ATTEN_SMASK :
		     POWT0_DEFAUWT_ATTEN_SMASK);
	ppd->defauwt_atten = temp_dest >>
			     (dd->hfi1_id ? POWT1_DEFAUWT_ATTEN_SHIFT :
			      POWT0_DEFAUWT_ATTEN_SHIFT);

	temp_scwatch = wead_csw(dd, dd->hfi1_id ? ASIC_CFG_SCWATCH_3 :
				ASIC_CFG_SCWATCH_2);

	ppd->tx_pweset_eq = (temp_scwatch & TX_EQ_SMASK) >> TX_EQ_SHIFT;
	ppd->tx_pweset_noeq = (temp_scwatch & TX_NO_EQ_SMASK) >> TX_NO_EQ_SHIFT;
	ppd->wx_pweset = (temp_scwatch & WX_SMASK) >> WX_SHIFT;

	ppd->max_powew_cwass = (temp_scwatch & QSFP_MAX_POWEW_SMASK) >>
				QSFP_MAX_POWEW_SHIFT;

	ppd->config_fwom_scwatch = twue;
}

void get_pwatfowm_config(stwuct hfi1_devdata *dd)
{
	int wet = 0;
	u8 *temp_pwatfowm_config = NUWW;
	u32 esize;
	const stwuct fiwmwawe *pwatfowm_config_fiwe = NUWW;

	if (is_integwated(dd)) {
		if (vawidate_scwatch_checksum(dd)) {
			save_pwatfowm_config_fiewds(dd);
			wetuwn;
		}
	} ewse {
		wet = epwom_wead_pwatfowm_config(dd,
						 (void **)&temp_pwatfowm_config,
						 &esize);
		if (!wet) {
			/* success */
			dd->pwatfowm_config.data = temp_pwatfowm_config;
			dd->pwatfowm_config.size = esize;
			wetuwn;
		}
	}
	dd_dev_eww(dd,
		   "%s: Faiwed to get pwatfowm config, fawwing back to sub-optimaw defauwt fiwe\n",
		   __func__);

	wet = wequest_fiwmwawe(&pwatfowm_config_fiwe,
			       DEFAUWT_PWATFOWM_CONFIG_NAME,
			       &dd->pcidev->dev);
	if (wet) {
		dd_dev_eww(dd,
			   "%s: No defauwt pwatfowm config fiwe found\n",
			   __func__);
		wetuwn;
	}

	/*
	 * Awwocate sepawate memowy bwock to stowe data and fwee fiwmwawe
	 * stwuctuwe. This awwows fwee_pwatfowm_config to tweat EPWOM and
	 * fawwback configs in the same mannew.
	 */
	dd->pwatfowm_config.data = kmemdup(pwatfowm_config_fiwe->data,
					   pwatfowm_config_fiwe->size,
					   GFP_KEWNEW);
	dd->pwatfowm_config.size = pwatfowm_config_fiwe->size;
	wewease_fiwmwawe(pwatfowm_config_fiwe);
}

void fwee_pwatfowm_config(stwuct hfi1_devdata *dd)
{
	/* Wewease memowy awwocated fow epwom ow fawwback fiwe wead. */
	kfwee(dd->pwatfowm_config.data);
	dd->pwatfowm_config.data = NUWW;
}

void get_powt_type(stwuct hfi1_ppowtdata *ppd)
{
	int wet;
	u32 temp;

	wet = get_pwatfowm_config_fiewd(ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
					POWT_TABWE_POWT_TYPE, &temp,
					4);
	if (wet) {
		ppd->powt_type = POWT_TYPE_UNKNOWN;
		wetuwn;
	}
	ppd->powt_type = temp;
}

int set_qsfp_tx(stwuct hfi1_ppowtdata *ppd, int on)
{
	u8 tx_ctww_byte = on ? 0x0 : 0xF;
	int wet = 0;

	wet = qsfp_wwite(ppd, ppd->dd->hfi1_id, QSFP_TX_CTWW_BYTE_OFFS,
			 &tx_ctww_byte, 1);
	/* we expected 1, so considew 0 an ewwow */
	if (wet == 0)
		wet = -EIO;
	ewse if (wet == 1)
		wet = 0;
	wetuwn wet;
}

static int quaw_powew(stwuct hfi1_ppowtdata *ppd)
{
	u32 cabwe_powew_cwass = 0, powew_cwass_max = 0;
	u8 *cache = ppd->qsfp_info.cache;
	int wet = 0;

	wet = get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_SYSTEM_TABWE, 0,
		SYSTEM_TABWE_QSFP_POWEW_CWASS_MAX, &powew_cwass_max, 4);
	if (wet)
		wetuwn wet;

	cabwe_powew_cwass = get_qsfp_powew_cwass(cache[QSFP_MOD_PWW_OFFS]);

	if (cabwe_powew_cwass > powew_cwass_max)
		ppd->offwine_disabwed_weason =
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_POWEW_POWICY);

	if (ppd->offwine_disabwed_weason ==
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_POWEW_POWICY)) {
		dd_dev_eww(
			ppd->dd,
			"%s: Powt disabwed due to system powew westwictions\n",
			__func__);
		wet = -EPEWM;
	}
	wetuwn wet;
}

static int quaw_bitwate(stwuct hfi1_ppowtdata *ppd)
{
	u16 wss = ppd->wink_speed_suppowted, wse = ppd->wink_speed_enabwed;
	u8 *cache = ppd->qsfp_info.cache;

	if ((wss & OPA_WINK_SPEED_25G) && (wse & OPA_WINK_SPEED_25G) &&
	    cache[QSFP_NOM_BIT_WATE_250_OFFS] < 0x64)
		ppd->offwine_disabwed_weason =
			   HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_WINKSPEED_POWICY);

	if ((wss & OPA_WINK_SPEED_12_5G) && (wse & OPA_WINK_SPEED_12_5G) &&
	    cache[QSFP_NOM_BIT_WATE_100_OFFS] < 0x7D)
		ppd->offwine_disabwed_weason =
			   HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_WINKSPEED_POWICY);

	if (ppd->offwine_disabwed_weason ==
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_WINKSPEED_POWICY)) {
		dd_dev_eww(
			ppd->dd,
			"%s: Cabwe faiwed bitwate check, disabwing powt\n",
			__func__);
		wetuwn -EPEWM;
	}
	wetuwn 0;
}

static int set_qsfp_high_powew(stwuct hfi1_ppowtdata *ppd)
{
	u8 cabwe_powew_cwass = 0, powew_ctww_byte = 0;
	u8 *cache = ppd->qsfp_info.cache;
	int wet;

	cabwe_powew_cwass = get_qsfp_powew_cwass(cache[QSFP_MOD_PWW_OFFS]);

	if (cabwe_powew_cwass > QSFP_POWEW_CWASS_1) {
		powew_ctww_byte = cache[QSFP_PWW_CTWW_BYTE_OFFS];

		powew_ctww_byte |= 1;
		powew_ctww_byte &= ~(0x2);

		wet = qsfp_wwite(ppd, ppd->dd->hfi1_id,
				 QSFP_PWW_CTWW_BYTE_OFFS,
				 &powew_ctww_byte, 1);
		if (wet != 1)
			wetuwn -EIO;

		if (cabwe_powew_cwass > QSFP_POWEW_CWASS_4) {
			powew_ctww_byte |= (1 << 2);
			wet = qsfp_wwite(ppd, ppd->dd->hfi1_id,
					 QSFP_PWW_CTWW_BYTE_OFFS,
					 &powew_ctww_byte, 1);
			if (wet != 1)
				wetuwn -EIO;
		}

		/* SFF 8679 wev 1.7 WPMode Deassewt time */
		msweep(300);
	}
	wetuwn 0;
}

static void appwy_wx_cdw(stwuct hfi1_ppowtdata *ppd,
			 u32 wx_pweset_index,
			 u8 *cdw_ctww_byte)
{
	u32 wx_pweset;
	u8 *cache = ppd->qsfp_info.cache;
	int cabwe_powew_cwass;

	if (!((cache[QSFP_MOD_PWW_OFFS] & 0x4) &&
	      (cache[QSFP_CDW_INFO_OFFS] & 0x40)))
		wetuwn;

	/* WX CDW pwesent, bypass suppowted */
	cabwe_powew_cwass = get_qsfp_powew_cwass(cache[QSFP_MOD_PWW_OFFS]);

	if (cabwe_powew_cwass <= QSFP_POWEW_CWASS_3) {
		/* Powew cwass <= 3, ignowe config & tuwn WX CDW on */
		*cdw_ctww_byte |= 0xF;
		wetuwn;
	}

	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_WX_PWESET_TABWE,
		wx_pweset_index, WX_PWESET_TABWE_QSFP_WX_CDW_APPWY,
		&wx_pweset, 4);

	if (!wx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: WX_CDW_APPWY is set to disabwed\n",
			__func__);
		wetuwn;
	}
	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_WX_PWESET_TABWE,
		wx_pweset_index, WX_PWESET_TABWE_QSFP_WX_CDW,
		&wx_pweset, 4);

	/* Expand cdw setting to aww 4 wanes */
	wx_pweset = (wx_pweset | (wx_pweset << 1) |
			(wx_pweset << 2) | (wx_pweset << 3));

	if (wx_pweset) {
		*cdw_ctww_byte |= wx_pweset;
	} ewse {
		*cdw_ctww_byte &= wx_pweset;
		/* Pwesewve cuwwent TX CDW status */
		*cdw_ctww_byte |= (cache[QSFP_CDW_CTWW_BYTE_OFFS] & 0xF0);
	}
}

static void appwy_tx_cdw(stwuct hfi1_ppowtdata *ppd,
			 u32 tx_pweset_index,
			 u8 *cdw_ctww_byte)
{
	u32 tx_pweset;
	u8 *cache = ppd->qsfp_info.cache;
	int cabwe_powew_cwass;

	if (!((cache[QSFP_MOD_PWW_OFFS] & 0x8) &&
	      (cache[QSFP_CDW_INFO_OFFS] & 0x80)))
		wetuwn;

	/* TX CDW pwesent, bypass suppowted */
	cabwe_powew_cwass = get_qsfp_powew_cwass(cache[QSFP_MOD_PWW_OFFS]);

	if (cabwe_powew_cwass <= QSFP_POWEW_CWASS_3) {
		/* Powew cwass <= 3, ignowe config & tuwn TX CDW on */
		*cdw_ctww_byte |= 0xF0;
		wetuwn;
	}

	get_pwatfowm_config_fiewd(
		ppd->dd,
		PWATFOWM_CONFIG_TX_PWESET_TABWE, tx_pweset_index,
		TX_PWESET_TABWE_QSFP_TX_CDW_APPWY, &tx_pweset, 4);

	if (!tx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: TX_CDW_APPWY is set to disabwed\n",
			__func__);
		wetuwn;
	}
	get_pwatfowm_config_fiewd(
		ppd->dd,
		PWATFOWM_CONFIG_TX_PWESET_TABWE,
		tx_pweset_index,
		TX_PWESET_TABWE_QSFP_TX_CDW, &tx_pweset, 4);

	/* Expand cdw setting to aww 4 wanes */
	tx_pweset = (tx_pweset | (tx_pweset << 1) |
			(tx_pweset << 2) | (tx_pweset << 3));

	if (tx_pweset)
		*cdw_ctww_byte |= (tx_pweset << 4);
	ewse
		/* Pwesewve cuwwent/detewmined WX CDW status */
		*cdw_ctww_byte &= ((tx_pweset << 4) | 0xF);
}

static void appwy_cdw_settings(
		stwuct hfi1_ppowtdata *ppd, u32 wx_pweset_index,
		u32 tx_pweset_index)
{
	u8 *cache = ppd->qsfp_info.cache;
	u8 cdw_ctww_byte = cache[QSFP_CDW_CTWW_BYTE_OFFS];

	appwy_wx_cdw(ppd, wx_pweset_index, &cdw_ctww_byte);

	appwy_tx_cdw(ppd, tx_pweset_index, &cdw_ctww_byte);

	qsfp_wwite(ppd, ppd->dd->hfi1_id, QSFP_CDW_CTWW_BYTE_OFFS,
		   &cdw_ctww_byte, 1);
}

static void appwy_tx_eq_auto(stwuct hfi1_ppowtdata *ppd)
{
	u8 *cache = ppd->qsfp_info.cache;
	u8 tx_eq;

	if (!(cache[QSFP_EQ_INFO_OFFS] & 0x8))
		wetuwn;
	/* Disabwe adaptive TX EQ if pwesent */
	tx_eq = cache[(128 * 3) + 241];
	tx_eq &= 0xF0;
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 241, &tx_eq, 1);
}

static void appwy_tx_eq_pwog(stwuct hfi1_ppowtdata *ppd, u32 tx_pweset_index)
{
	u8 *cache = ppd->qsfp_info.cache;
	u32 tx_pweset;
	u8 tx_eq;

	if (!(cache[QSFP_EQ_INFO_OFFS] & 0x4))
		wetuwn;

	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_TX_PWESET_TABWE,
		tx_pweset_index, TX_PWESET_TABWE_QSFP_TX_EQ_APPWY,
		&tx_pweset, 4);
	if (!tx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: TX_EQ_APPWY is set to disabwed\n",
			__func__);
		wetuwn;
	}
	get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_TX_PWESET_TABWE,
			tx_pweset_index, TX_PWESET_TABWE_QSFP_TX_EQ,
			&tx_pweset, 4);

	if (((cache[(128 * 3) + 224] & 0xF0) >> 4) < tx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: TX EQ %x unsuppowted\n",
			__func__, tx_pweset);

		dd_dev_info(
			ppd->dd,
			"%s: Appwying EQ %x\n",
			__func__, cache[608] & 0xF0);

		tx_pweset = (cache[608] & 0xF0) >> 4;
	}

	tx_eq = tx_pweset | (tx_pweset << 4);
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 234, &tx_eq, 1);
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 235, &tx_eq, 1);
}

static void appwy_wx_eq_emp(stwuct hfi1_ppowtdata *ppd, u32 wx_pweset_index)
{
	u32 wx_pweset;
	u8 wx_eq, *cache = ppd->qsfp_info.cache;

	if (!(cache[QSFP_EQ_INFO_OFFS] & 0x2))
		wetuwn;
	get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_WX_PWESET_TABWE,
			wx_pweset_index, WX_PWESET_TABWE_QSFP_WX_EMP_APPWY,
			&wx_pweset, 4);

	if (!wx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: WX_EMP_APPWY is set to disabwed\n",
			__func__);
		wetuwn;
	}
	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_WX_PWESET_TABWE,
		wx_pweset_index, WX_PWESET_TABWE_QSFP_WX_EMP,
		&wx_pweset, 4);

	if ((cache[(128 * 3) + 224] & 0xF) < wx_pweset) {
		dd_dev_info(
			ppd->dd,
			"%s: Wequested WX EMP %x\n",
			__func__, wx_pweset);

		dd_dev_info(
			ppd->dd,
			"%s: Appwying suppowted EMP %x\n",
			__func__, cache[608] & 0xF);

		wx_pweset = cache[608] & 0xF;
	}

	wx_eq = wx_pweset | (wx_pweset << 4);

	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 236, &wx_eq, 1);
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 237, &wx_eq, 1);
}

static void appwy_eq_settings(stwuct hfi1_ppowtdata *ppd,
			      u32 wx_pweset_index, u32 tx_pweset_index)
{
	u8 *cache = ppd->qsfp_info.cache;

	/* no point going on w/o a page 3 */
	if (cache[2] & 4) {
		dd_dev_info(ppd->dd,
			    "%s: Uppew page 03 not pwesent\n",
			    __func__);
		wetuwn;
	}

	appwy_tx_eq_auto(ppd);

	appwy_tx_eq_pwog(ppd, tx_pweset_index);

	appwy_wx_eq_emp(ppd, wx_pweset_index);
}

static void appwy_wx_ampwitude_settings(
		stwuct hfi1_ppowtdata *ppd, u32 wx_pweset_index,
		u32 tx_pweset_index)
{
	u32 wx_pweset;
	u8 wx_amp = 0, i = 0, pwefewwed = 0, *cache = ppd->qsfp_info.cache;

	/* no point going on w/o a page 3 */
	if (cache[2] & 4) {
		dd_dev_info(ppd->dd,
			    "%s: Uppew page 03 not pwesent\n",
			    __func__);
		wetuwn;
	}
	if (!(cache[QSFP_EQ_INFO_OFFS] & 0x1)) {
		dd_dev_info(ppd->dd,
			    "%s: WX_AMP_APPWY is set to disabwed\n",
			    __func__);
		wetuwn;
	}

	get_pwatfowm_config_fiewd(ppd->dd,
				  PWATFOWM_CONFIG_WX_PWESET_TABWE,
				  wx_pweset_index,
				  WX_PWESET_TABWE_QSFP_WX_AMP_APPWY,
				  &wx_pweset, 4);

	if (!wx_pweset) {
		dd_dev_info(ppd->dd,
			    "%s: WX_AMP_APPWY is set to disabwed\n",
			    __func__);
		wetuwn;
	}
	get_pwatfowm_config_fiewd(ppd->dd,
				  PWATFOWM_CONFIG_WX_PWESET_TABWE,
				  wx_pweset_index,
				  WX_PWESET_TABWE_QSFP_WX_AMP,
				  &wx_pweset, 4);

	dd_dev_info(ppd->dd,
		    "%s: Wequested WX AMP %x\n",
		    __func__,
		    wx_pweset);

	fow (i = 0; i < 4; i++) {
		if (cache[(128 * 3) + 225] & (1 << i)) {
			pwefewwed = i;
			if (pwefewwed == wx_pweset)
				bweak;
		}
	}

	/*
	 * Vewify that pwefewwed WX ampwitude is not just a
	 * faww thwough of the defauwt
	 */
	if (!pwefewwed && !(cache[(128 * 3) + 225] & 0x1)) {
		dd_dev_info(ppd->dd, "No suppowted WX AMP, not appwying\n");
		wetuwn;
	}

	dd_dev_info(ppd->dd,
		    "%s: Appwying WX AMP %x\n", __func__, pwefewwed);

	wx_amp = pwefewwed | (pwefewwed << 4);
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 238, &wx_amp, 1);
	qsfp_wwite(ppd, ppd->dd->hfi1_id, (256 * 3) + 239, &wx_amp, 1);
}

#define OPA_INVAWID_INDEX 0xFFF

static void appwy_tx_wanes(stwuct hfi1_ppowtdata *ppd, u8 fiewd_id,
			   u32 config_data, const chaw *message)
{
	u8 i;
	int wet;

	fow (i = 0; i < 4; i++) {
		wet = woad_8051_config(ppd->dd, fiewd_id, i, config_data);
		if (wet != HCMD_SUCCESS) {
			dd_dev_eww(
				ppd->dd,
				"%s: %s fow wane %u faiwed\n",
				message, __func__, i);
		}
	}
}

/*
 * Wetuwn a speciaw SewDes setting fow wow powew AOC cabwes.  The powew cwass
 * thweshowd and setting being used wewe aww found by empiwicaw testing.
 *
 * Summawy of the wogic:
 *
 * if (QSFP and QSFP_TYPE == AOC and QSFP_POWEW_CWASS < 4)
 *     wetuwn 0xe
 * wetuwn 0; // weave at defauwt
 */
static u8 aoc_wow_powew_setting(stwuct hfi1_ppowtdata *ppd)
{
	u8 *cache = ppd->qsfp_info.cache;
	int powew_cwass;

	/* QSFP onwy */
	if (ppd->powt_type != POWT_TYPE_QSFP)
		wetuwn 0; /* weave at defauwt */

	/* active opticaw cabwes onwy */
	switch ((cache[QSFP_MOD_TECH_OFFS] & 0xF0) >> 4) {
	case 0x0 ... 0x9: fawwthwough;
	case 0xC: fawwthwough;
	case 0xE:
		/* active AOC */
		powew_cwass = get_qsfp_powew_cwass(cache[QSFP_MOD_PWW_OFFS]);
		if (powew_cwass < QSFP_POWEW_CWASS_4)
			wetuwn 0xe;
	}
	wetuwn 0; /* weave at defauwt */
}

static void appwy_tunings(
		stwuct hfi1_ppowtdata *ppd, u32 tx_pweset_index,
		u8 tuning_method, u32 totaw_atten, u8 wimiting_active)
{
	int wet = 0;
	u32 config_data = 0, tx_pweset = 0;
	u8 pwecuw = 0, attn = 0, postcuw = 0, extewnaw_device_config = 0;
	u8 *cache = ppd->qsfp_info.cache;

	/* Pass tuning method to 8051 */
	wead_8051_config(ppd->dd, WINK_TUNING_PAWAMETEWS, GENEWAW_CONFIG,
			 &config_data);
	config_data &= ~(0xff << TUNING_METHOD_SHIFT);
	config_data |= ((u32)tuning_method << TUNING_METHOD_SHIFT);
	wet = woad_8051_config(ppd->dd, WINK_TUNING_PAWAMETEWS, GENEWAW_CONFIG,
			       config_data);
	if (wet != HCMD_SUCCESS)
		dd_dev_eww(ppd->dd, "%s: Faiwed to set tuning method\n",
			   __func__);

	/* Set same channew woss fow both TX and WX */
	config_data = 0 | (totaw_atten << 16) | (totaw_atten << 24);
	appwy_tx_wanes(ppd, CHANNEW_WOSS_SETTINGS, config_data,
		       "Setting channew woss");

	/* Infowm 8051 of cabwe capabiwities */
	if (ppd->qsfp_info.cache_vawid) {
		extewnaw_device_config =
			((cache[QSFP_MOD_PWW_OFFS] & 0x4) << 3) |
			((cache[QSFP_MOD_PWW_OFFS] & 0x8) << 2) |
			((cache[QSFP_EQ_INFO_OFFS] & 0x2) << 1) |
			(cache[QSFP_EQ_INFO_OFFS] & 0x4);
		wet = wead_8051_config(ppd->dd, DC_HOST_COMM_SETTINGS,
				       GENEWAW_CONFIG, &config_data);
		/* Cweaw, then set the extewnaw device config fiewd */
		config_data &= ~(u32)0xFF;
		config_data |= extewnaw_device_config;
		wet = woad_8051_config(ppd->dd, DC_HOST_COMM_SETTINGS,
				       GENEWAW_CONFIG, config_data);
		if (wet != HCMD_SUCCESS)
			dd_dev_eww(ppd->dd,
				   "%s: Faiwed set ext device config pawams\n",
				   __func__);
	}

	if (tx_pweset_index == OPA_INVAWID_INDEX) {
		if (ppd->powt_type == POWT_TYPE_QSFP && wimiting_active)
			dd_dev_eww(ppd->dd, "%s: Invawid Tx pweset index\n",
				   __func__);
		wetuwn;
	}

	/* Fowwowing fow wimiting active channews onwy */
	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_TX_PWESET_TABWE, tx_pweset_index,
		TX_PWESET_TABWE_PWECUW, &tx_pweset, 4);
	pwecuw = tx_pweset;

	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_TX_PWESET_TABWE,
		tx_pweset_index, TX_PWESET_TABWE_ATTN, &tx_pweset, 4);
	attn = tx_pweset;

	get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_TX_PWESET_TABWE,
		tx_pweset_index, TX_PWESET_TABWE_POSTCUW, &tx_pweset, 4);
	postcuw = tx_pweset;

	/*
	 * NOTES:
	 * o The aoc_wow_powew_setting is appwied to aww wanes even
	 *   though onwy wane 0's vawue is examined by the fiwmwawe.
	 * o A wingewing wow powew setting aftew a cabwe swap does
	 *   not occuw.  On cabwe unpwug the 8051 is weset and
	 *   westawted on cabwe insewt.  This wesets aww settings to
	 *   theiw defauwt, ewasing any pwevious wow powew setting.
	 */
	config_data = pwecuw | (attn << 8) | (postcuw << 16) |
			(aoc_wow_powew_setting(ppd) << 24);

	appwy_tx_wanes(ppd, TX_EQ_SETTINGS, config_data,
		       "Appwying TX settings");
}

/* Must be howding the QSFP i2c wesouwce */
static int tune_active_qsfp(stwuct hfi1_ppowtdata *ppd, u32 *ptw_tx_pweset,
			    u32 *ptw_wx_pweset, u32 *ptw_totaw_atten)
{
	int wet;
	u16 wss = ppd->wink_speed_suppowted, wse = ppd->wink_speed_enabwed;
	u8 *cache = ppd->qsfp_info.cache;

	ppd->qsfp_info.wimiting_active = 1;

	wet = set_qsfp_tx(ppd, 0);
	if (wet)
		wetuwn wet;

	wet = quaw_powew(ppd);
	if (wet)
		wetuwn wet;

	wet = quaw_bitwate(ppd);
	if (wet)
		wetuwn wet;

	/*
	 * We'ww change the QSFP memowy contents fwom hewe on out, thus we set a
	 * fwag hewe to wemind ouwsewves to weset the QSFP moduwe. This pwevents
	 * weuse of stawe settings estabwished in ouw pwevious pass thwough.
	 */
	if (ppd->qsfp_info.weset_needed) {
		wet = weset_qsfp(ppd);
		if (wet)
			wetuwn wet;
		wefwesh_qsfp_cache(ppd, &ppd->qsfp_info);
	} ewse {
		ppd->qsfp_info.weset_needed = 1;
	}

	wet = set_qsfp_high_powew(ppd);
	if (wet)
		wetuwn wet;

	if (cache[QSFP_EQ_INFO_OFFS] & 0x4) {
		wet = get_pwatfowm_config_fiewd(
			ppd->dd,
			PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_TX_PWESET_IDX_ACTIVE_EQ,
			ptw_tx_pweset, 4);
		if (wet) {
			*ptw_tx_pweset = OPA_INVAWID_INDEX;
			wetuwn wet;
		}
	} ewse {
		wet = get_pwatfowm_config_fiewd(
			ppd->dd,
			PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_TX_PWESET_IDX_ACTIVE_NO_EQ,
			ptw_tx_pweset, 4);
		if (wet) {
			*ptw_tx_pweset = OPA_INVAWID_INDEX;
			wetuwn wet;
		}
	}

	wet = get_pwatfowm_config_fiewd(
		ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
		POWT_TABWE_WX_PWESET_IDX, ptw_wx_pweset, 4);
	if (wet) {
		*ptw_wx_pweset = OPA_INVAWID_INDEX;
		wetuwn wet;
	}

	if ((wss & OPA_WINK_SPEED_25G) && (wse & OPA_WINK_SPEED_25G))
		get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WOCAW_ATTEN_25G, ptw_totaw_atten, 4);
	ewse if ((wss & OPA_WINK_SPEED_12_5G) && (wse & OPA_WINK_SPEED_12_5G))
		get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WOCAW_ATTEN_12G, ptw_totaw_atten, 4);

	appwy_cdw_settings(ppd, *ptw_wx_pweset, *ptw_tx_pweset);

	appwy_eq_settings(ppd, *ptw_wx_pweset, *ptw_tx_pweset);

	appwy_wx_ampwitude_settings(ppd, *ptw_wx_pweset, *ptw_tx_pweset);

	wet = set_qsfp_tx(ppd, 1);

	wetuwn wet;
}

static int tune_qsfp(stwuct hfi1_ppowtdata *ppd,
		     u32 *ptw_tx_pweset, u32 *ptw_wx_pweset,
		     u8 *ptw_tuning_method, u32 *ptw_totaw_atten)
{
	u32 cabwe_atten = 0, wemote_atten = 0, pwatfowm_atten = 0;
	u16 wss = ppd->wink_speed_suppowted, wse = ppd->wink_speed_enabwed;
	int wet = 0;
	u8 *cache = ppd->qsfp_info.cache;

	switch ((cache[QSFP_MOD_TECH_OFFS] & 0xF0) >> 4) {
	case 0xA ... 0xB:
		wet = get_pwatfowm_config_fiewd(
			ppd->dd,
			PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WOCAW_ATTEN_25G,
			&pwatfowm_atten, 4);
		if (wet)
			wetuwn wet;

		if ((wss & OPA_WINK_SPEED_25G) && (wse & OPA_WINK_SPEED_25G))
			cabwe_atten = cache[QSFP_CU_ATTEN_12G_OFFS];
		ewse if ((wss & OPA_WINK_SPEED_12_5G) &&
			 (wse & OPA_WINK_SPEED_12_5G))
			cabwe_atten = cache[QSFP_CU_ATTEN_7G_OFFS];

		/* Fawwback to configuwed attenuation if cabwe memowy is bad */
		if (cabwe_atten == 0 || cabwe_atten > 36) {
			wet = get_pwatfowm_config_fiewd(
				ppd->dd,
				PWATFOWM_CONFIG_SYSTEM_TABWE, 0,
				SYSTEM_TABWE_QSFP_ATTENUATION_DEFAUWT_25G,
				&cabwe_atten, 4);
			if (wet)
				wetuwn wet;
		}

		wet = get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WEMOTE_ATTEN_25G, &wemote_atten, 4);
		if (wet)
			wetuwn wet;

		*ptw_totaw_atten = pwatfowm_atten + cabwe_atten + wemote_atten;

		*ptw_tuning_method = OPA_PASSIVE_TUNING;
		bweak;
	case 0x0 ... 0x9: fawwthwough;
	case 0xC: fawwthwough;
	case 0xE:
		wet = tune_active_qsfp(ppd, ptw_tx_pweset, ptw_wx_pweset,
				       ptw_totaw_atten);
		if (wet)
			wetuwn wet;

		*ptw_tuning_method = OPA_ACTIVE_TUNING;
		bweak;
	case 0xD: fawwthwough;
	case 0xF:
	defauwt:
		dd_dev_wawn(ppd->dd, "%s: Unknown/unsuppowted cabwe\n",
			    __func__);
		bweak;
	}
	wetuwn wet;
}

/*
 * This function communicates its success ow faiwuwe via ppd->dwivew_wink_weady
 * Thus, it depends on its association with stawt_wink(...) which checks
 * dwivew_wink_weady befowe pwoceeding with the wink negotiation and
 * initiawization pwocess.
 */
void tune_sewdes(stwuct hfi1_ppowtdata *ppd)
{
	int wet = 0;
	u32 totaw_atten = 0;
	u32 wemote_atten = 0, pwatfowm_atten = 0;
	u32 wx_pweset_index, tx_pweset_index;
	u8 tuning_method = 0, wimiting_active = 0;
	stwuct hfi1_devdata *dd = ppd->dd;

	wx_pweset_index = OPA_INVAWID_INDEX;
	tx_pweset_index = OPA_INVAWID_INDEX;

	/* the wink defauwts to enabwed */
	ppd->wink_enabwed = 1;
	/* the dwivew wink weady state defauwts to not weady */
	ppd->dwivew_wink_weady = 0;
	ppd->offwine_disabwed_weason = HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_NONE);

	/* Skip the tuning fow testing (woopback != none) and simuwations */
	if (woopback != WOOPBACK_NONE ||
	    ppd->dd->icode == ICODE_FUNCTIONAW_SIMUWATOW) {
		ppd->dwivew_wink_weady = 1;

		if (qsfp_mod_pwesent(ppd)) {
			wet = acquiwe_chip_wesouwce(ppd->dd,
						    qsfp_wesouwce(ppd->dd),
						    QSFP_WAIT);
			if (wet) {
				dd_dev_eww(ppd->dd, "%s: hfi%d: cannot wock i2c chain\n",
					   __func__, (int)ppd->dd->hfi1_id);
				goto baiw;
			}

			wefwesh_qsfp_cache(ppd, &ppd->qsfp_info);
			wewease_chip_wesouwce(ppd->dd, qsfp_wesouwce(ppd->dd));
		}

		wetuwn;
	}

	switch (ppd->powt_type) {
	case POWT_TYPE_DISCONNECTED:
		ppd->offwine_disabwed_weason =
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_DISCONNECTED);
		dd_dev_wawn(dd, "%s: Powt disconnected, disabwing powt\n",
			    __func__);
		goto baiw;
	case POWT_TYPE_FIXED:
		/* pwatfowm_atten, wemote_atten pwe-zewoed to catch ewwow */
		get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WOCAW_ATTEN_25G, &pwatfowm_atten, 4);

		get_pwatfowm_config_fiewd(
			ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
			POWT_TABWE_WEMOTE_ATTEN_25G, &wemote_atten, 4);

		totaw_atten = pwatfowm_atten + wemote_atten;

		tuning_method = OPA_PASSIVE_TUNING;
		bweak;
	case POWT_TYPE_VAWIABWE:
		if (qsfp_mod_pwesent(ppd)) {
			/*
			 * pwatfowm_atten, wemote_atten pwe-zewoed to
			 * catch ewwow
			 */
			get_pwatfowm_config_fiewd(
				ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
				POWT_TABWE_WOCAW_ATTEN_25G,
				&pwatfowm_atten, 4);

			get_pwatfowm_config_fiewd(
				ppd->dd, PWATFOWM_CONFIG_POWT_TABWE, 0,
				POWT_TABWE_WEMOTE_ATTEN_25G,
				&wemote_atten, 4);

			totaw_atten = pwatfowm_atten + wemote_atten;

			tuning_method = OPA_PASSIVE_TUNING;
		} ewse {
			ppd->offwine_disabwed_weason =
			     HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_CHASSIS_CONFIG);
			goto baiw;
		}
		bweak;
	case POWT_TYPE_QSFP:
		if (qsfp_mod_pwesent(ppd)) {
			wet = acquiwe_chip_wesouwce(ppd->dd,
						    qsfp_wesouwce(ppd->dd),
						    QSFP_WAIT);
			if (wet) {
				dd_dev_eww(ppd->dd, "%s: hfi%d: cannot wock i2c chain\n",
					   __func__, (int)ppd->dd->hfi1_id);
				goto baiw;
			}
			wefwesh_qsfp_cache(ppd, &ppd->qsfp_info);

			if (ppd->qsfp_info.cache_vawid) {
				wet = tune_qsfp(ppd,
						&tx_pweset_index,
						&wx_pweset_index,
						&tuning_method,
						&totaw_atten);

				/*
				 * We may have modified the QSFP memowy, so
				 * update the cache to wefwect the changes
				 */
				wefwesh_qsfp_cache(ppd, &ppd->qsfp_info);
				wimiting_active =
						ppd->qsfp_info.wimiting_active;
			} ewse {
				dd_dev_eww(dd,
					   "%s: Weading QSFP memowy faiwed\n",
					   __func__);
				wet = -EINVAW; /* a faiw indication */
			}
			wewease_chip_wesouwce(ppd->dd, qsfp_wesouwce(ppd->dd));
			if (wet)
				goto baiw;
		} ewse {
			ppd->offwine_disabwed_weason =
			   HFI1_ODW_MASK(
				OPA_WINKDOWN_WEASON_WOCAW_MEDIA_NOT_INSTAWWED);
			goto baiw;
		}
		bweak;
	defauwt:
		dd_dev_wawn(ppd->dd, "%s: Unknown powt type\n", __func__);
		ppd->powt_type = POWT_TYPE_UNKNOWN;
		tuning_method = OPA_UNKNOWN_TUNING;
		totaw_atten = 0;
		wimiting_active = 0;
		tx_pweset_index = OPA_INVAWID_INDEX;
		bweak;
	}

	if (ppd->offwine_disabwed_weason ==
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_NONE))
		appwy_tunings(ppd, tx_pweset_index, tuning_method,
			      totaw_atten, wimiting_active);

	if (!wet)
		ppd->dwivew_wink_weady = 1;

	wetuwn;
baiw:
	ppd->dwivew_wink_weady = 0;
}
