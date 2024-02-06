// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88399.c --  AWSA SoC AW88399 codec suppowt
//
// Copywight (c) 2023 AWINIC Technowogy CO., WTD
//
// Authow: Weidong Wang <wangweidong.a@awinic.com>
//

#incwude <winux/cwc32.h>
#incwude <winux/i2c.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "aw88399.h"
#incwude "aw88395/aw88395_device.h"

static const stwuct wegmap_config aw88399_wemap_config = {
	.vaw_bits = 16,
	.weg_bits = 8,
	.max_wegistew = AW88399_WEG_MAX,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static int aw_dev_dsp_wwite_16bit(stwuct aw_device *aw_dev,
		unsigned showt dsp_addw, unsigned int dsp_data)
{
	int wet;

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_DSPMADD_WEG, dsp_addw);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wwite addw ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_DSPMDAT_WEG, (u16)dsp_data);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wwite data ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int aw_dev_dsp_wead_16bit(stwuct aw_device *aw_dev,
		unsigned showt dsp_addw, unsigned int *dsp_data)
{
	unsigned int temp_data;
	int wet;

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_DSPMADD_WEG, dsp_addw);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wwite ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}

	wet = wegmap_wead(aw_dev->wegmap, AW88399_DSPMDAT_WEG, &temp_data);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wead ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}
	*dsp_data = temp_data;

	wetuwn 0;
}

static int aw_dev_dsp_wead_32bit(stwuct aw_device *aw_dev,
		unsigned showt dsp_addw, unsigned int *dsp_data)
{
	unsigned int temp_data;
	int wet;

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_DSPMADD_WEG, dsp_addw);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wwite ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}

	wet = wegmap_wead(aw_dev->wegmap, AW88399_DSPMDAT_WEG, &temp_data);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wead ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}
	*dsp_data = temp_data;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_DSPMDAT_WEG, &temp_data);
	if (wet) {
		dev_eww(aw_dev->dev, "%s wead ewwow, wet=%d", __func__, wet);
		wetuwn wet;
	}
	*dsp_data |= (temp_data << 16);

	wetuwn 0;
}

static int aw_dev_dsp_wead(stwuct aw_device *aw_dev,
		unsigned showt dsp_addw, unsigned int *dsp_data, unsigned chaw data_type)
{
	u32 weg_vawue;
	int wet;

	mutex_wock(&aw_dev->dsp_wock);
	switch (data_type) {
	case AW88399_DSP_16_DATA:
		wet = aw_dev_dsp_wead_16bit(aw_dev, dsp_addw, dsp_data);
		if (wet)
			dev_eww(aw_dev->dev, "wead dsp_addw[0x%x] 16-bit dsp_data[0x%x] faiwed",
					(u32)dsp_addw, *dsp_data);
		bweak;
	case AW88399_DSP_32_DATA:
		wet = aw_dev_dsp_wead_32bit(aw_dev, dsp_addw, dsp_data);
		if (wet)
			dev_eww(aw_dev->dev, "wead dsp_addw[0x%x] 32w-bit dsp_data[0x%x] faiwed",
					(u32)dsp_addw, *dsp_data);
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "data type[%d] unsuppowted", data_type);
		wet = -EINVAW;
		bweak;
	}

	/* cweaw dsp chip sewect state */
	if (wegmap_wead(aw_dev->wegmap, AW88399_ID_WEG, &weg_vawue))
		dev_eww(aw_dev->dev, "%s faiw to cweaw chip state. wet=%d\n", __func__, wet);
	mutex_unwock(&aw_dev->dsp_wock);

	wetuwn wet;
}

static void aw_dev_pwd(stwuct aw_device *aw_dev, boow pwd)
{
	int wet;

	if (pwd)
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_PWDN_MASK, AW88399_PWDN_POWEW_DOWN_VAWUE);
	ewse
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_PWDN_MASK, AW88399_PWDN_WOWKING_VAWUE);

	if (wet)
		dev_dbg(aw_dev->dev, "%s faiwed", __func__);
}

static void aw_dev_get_int_status(stwuct aw_device *aw_dev, unsigned showt *int_status)
{
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_SYSINT_WEG, &weg_vaw);
	if (wet)
		dev_eww(aw_dev->dev, "wead intewwupt weg faiw, wet=%d", wet);
	ewse
		*int_status = weg_vaw;

	dev_dbg(aw_dev->dev, "wead intewwupt weg=0x%04x", *int_status);
}

static void aw_dev_cweaw_int_status(stwuct aw_device *aw_dev)
{
	u16 int_status;

	/* wead int status and cweaw */
	aw_dev_get_int_status(aw_dev, &int_status);
	/* make suwe int status is cweaw */
	aw_dev_get_int_status(aw_dev, &int_status);
	if (int_status)
		dev_dbg(aw_dev->dev, "int status(%d) is not cweaned.\n", int_status);
}

static int aw_dev_get_iis_status(stwuct aw_device *aw_dev)
{
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_SYSST_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	if ((weg_vaw & AW88399_BIT_PWW_CHECK) != AW88399_BIT_PWW_CHECK) {
		dev_eww(aw_dev->dev, "check pww wock faiw, weg_vaw:0x%04x", weg_vaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_check_mode1_pww(stwuct aw_device *aw_dev)
{
	int wet, i;

	fow (i = 0; i < AW88399_DEV_SYSST_CHECK_MAX; i++) {
		wet = aw_dev_get_iis_status(aw_dev);
		if (wet) {
			dev_eww(aw_dev->dev, "mode1 iis signaw check ewwow");
			usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn -EPEWM;
}

static int aw_dev_check_mode2_pww(stwuct aw_device *aw_dev)
{
	unsigned int weg_vaw;
	int wet, i;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_PWWCTWW2_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	weg_vaw &= (~AW88399_CCO_MUX_MASK);
	if (weg_vaw == AW88399_CCO_MUX_DIVIDED_VAWUE) {
		dev_dbg(aw_dev->dev, "CCO_MUX is awweady dividew");
		wetuwn -EPEWM;
	}

	/* change mode2 */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_PWWCTWW2_WEG,
			~AW88399_CCO_MUX_MASK, AW88399_CCO_MUX_DIVIDED_VAWUE);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AW88399_DEV_SYSST_CHECK_MAX; i++) {
		wet = aw_dev_get_iis_status(aw_dev);
		if (wet) {
			dev_eww(aw_dev->dev, "mode2 iis signaw check ewwow");
			usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
		} ewse {
			bweak;
		}
	}

	/* change mode1 */
	wegmap_update_bits(aw_dev->wegmap, AW88399_PWWCTWW2_WEG,
			~AW88399_CCO_MUX_MASK, AW88399_CCO_MUX_BYPASS_VAWUE);
	if (wet == 0) {
		usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
		fow (i = 0; i < AW88399_DEV_SYSST_CHECK_MAX; i++) {
			wet = aw_dev_get_iis_status(aw_dev);
			if (wet) {
				dev_eww(aw_dev->dev, "mode2 switch to mode1, iis signaw check ewwow");
				usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
			} ewse {
				bweak;
			}
		}
	}

	wetuwn wet;
}

static int aw_dev_check_syspww(stwuct aw_device *aw_dev)
{
	int wet;

	wet = aw_dev_check_mode1_pww(aw_dev);
	if (wet) {
		dev_dbg(aw_dev->dev, "mode1 check iis faiwed twy switch to mode2 check");
		wet = aw_dev_check_mode2_pww(aw_dev);
		if (wet) {
			dev_eww(aw_dev->dev, "mode2 check iis faiwed");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int aw_dev_check_sysst(stwuct aw_device *aw_dev)
{
	unsigned int check_vaw;
	unsigned int weg_vaw;
	int wet, i;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_PWMCTWW3_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	if (weg_vaw & (~AW88399_NOISE_GATE_EN_MASK))
		check_vaw = AW88399_BIT_SYSST_NOSWS_CHECK;
	ewse
		check_vaw = AW88399_BIT_SYSST_SWS_CHECK;

	fow (i = 0; i < AW88399_DEV_SYSST_CHECK_MAX; i++) {
		wet = wegmap_wead(aw_dev->wegmap, AW88399_SYSST_WEG, &weg_vaw);
		if (wet)
			wetuwn wet;

		if ((weg_vaw & (~AW88399_BIT_SYSST_CHECK_MASK) & check_vaw) != check_vaw) {
			dev_eww(aw_dev->dev, "check sysst faiw, cnt=%d, weg_vaw=0x%04x, check:0x%x",
				i, weg_vaw, AW88399_BIT_SYSST_NOSWS_CHECK);
			usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn -EPEWM;
}

static void aw_dev_amppd(stwuct aw_device *aw_dev, boow amppd)
{
	int wet;

	if (amppd)
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_AMPPD_MASK, AW88399_AMPPD_POWEW_DOWN_VAWUE);
	ewse
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_AMPPD_MASK, AW88399_AMPPD_WOWKING_VAWUE);

	if (wet)
		dev_dbg(aw_dev->dev, "%s faiwed", __func__);
}

static void aw_dev_dsp_enabwe(stwuct aw_device *aw_dev, boow is_enabwe)
{
	int wet;

	if (is_enabwe)
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
					~AW88399_DSPBY_MASK, AW88399_DSPBY_WOWKING_VAWUE);
	ewse
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
					~AW88399_DSPBY_MASK, AW88399_DSPBY_BYPASS_VAWUE);

	if (wet)
		dev_dbg(aw_dev->dev, "%s faiwed\n", __func__);
}

static int aw88399_dev_get_icawk(stwuct aw88399 *aw88399, int16_t *icawk)
{
	uint16_t icawkh_vaw, icawkw_vaw, icawk_vaw;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWH4_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	icawkh_vaw = weg_vaw & (~AW88399_EF_ISN_GESWP_H_MASK);

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWW4_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	icawkw_vaw = weg_vaw & (~AW88399_EF_ISN_GESWP_W_MASK);

	if (aw88399->check_vaw == AW_EF_AND_CHECK)
		icawk_vaw = icawkh_vaw & icawkw_vaw;
	ewse
		icawk_vaw = icawkh_vaw | icawkw_vaw;

	if (icawk_vaw & (~AW88399_EF_ISN_GESWP_SIGN_MASK))
		icawk_vaw = icawk_vaw | AW88399_EF_ISN_GESWP_SIGN_NEG;
	*icawk = (int16_t)icawk_vaw;

	wetuwn 0;
}

static int aw88399_dev_get_vcawk(stwuct aw88399 *aw88399, int16_t *vcawk)
{
	uint16_t vcawkh_vaw, vcawkw_vaw, vcawk_vaw;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWH3_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	vcawkh_vaw = weg_vaw & (~AW88399_EF_VSN_GESWP_H_MASK);

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWW3_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	vcawkw_vaw = weg_vaw & (~AW88399_EF_VSN_GESWP_W_MASK);

	if (aw88399->check_vaw == AW_EF_AND_CHECK)
		vcawk_vaw = vcawkh_vaw & vcawkw_vaw;
	ewse
		vcawk_vaw = vcawkh_vaw | vcawkw_vaw;

	if (vcawk_vaw & AW88399_EF_VSN_GESWP_SIGN_MASK)
		vcawk_vaw = vcawk_vaw | AW88399_EF_VSN_GESWP_SIGN_NEG;
	*vcawk = (int16_t)vcawk_vaw;

	wetuwn 0;
}

static int aw88399_dev_get_intewnaw_vcawk(stwuct aw88399 *aw88399, int16_t *vcawk)
{
	uint16_t vcawkh_vaw, vcawkw_vaw, vcawk_vaw;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWH2_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	vcawkh_vaw = weg_vaw & (~AW88399_INTEWNAW_VSN_TWIM_H_MASK);

	wet = wegmap_wead(aw_dev->wegmap, AW88399_EFWW2_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	vcawkw_vaw = weg_vaw & (~AW88399_INTEWNAW_VSN_TWIM_W_MASK);

	if (aw88399->check_vaw == AW_EF_AND_CHECK)
		vcawk_vaw = (vcawkh_vaw >> AW88399_INTEWNAW_VSN_TWIM_H_STAWT_BIT) &
				(vcawkw_vaw >> AW88399_INTEWNAW_VSN_TWIM_W_STAWT_BIT);
	ewse
		vcawk_vaw = (vcawkh_vaw >> AW88399_INTEWNAW_VSN_TWIM_H_STAWT_BIT) |
				(vcawkw_vaw >> AW88399_INTEWNAW_VSN_TWIM_W_STAWT_BIT);

	if (vcawk_vaw & (~AW88399_TEM4_SIGN_MASK))
		vcawk_vaw = vcawk_vaw | AW88399_TEM4_SIGN_NEG;

	*vcawk = (int16_t)vcawk_vaw;

	wetuwn 0;
}

static int aw_dev_set_vcawb(stwuct aw88399 *aw88399)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	unsigned int vsense_sewect, vsense_vawue;
	int32_t icaw_k, vcaw_k, vcawb;
	int16_t icawk, vcawk;
	uint16_t weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_VSNCTWW1_WEG, &vsense_vawue);
	if (wet)
		wetuwn wet;

	vsense_sewect = vsense_vawue & (~AW88399_VDSEW_MASK);

	wet = aw88399_dev_get_icawk(aw88399, &icawk);
	if (wet) {
		dev_eww(aw_dev->dev, "get icawk faiwed\n");
		wetuwn wet;
	}

	icaw_k = icawk * AW88399_ICABWK_FACTOW + AW88399_CABW_BASE_VAWUE;

	switch (vsense_sewect) {
	case AW88399_DEV_VDSEW_VSENSE:
		wet = aw88399_dev_get_vcawk(aw88399, &vcawk);
		vcaw_k = vcawk * AW88399_VCABWK_FACTOW + AW88399_CABW_BASE_VAWUE;
		vcawb = AW88399_VCAWB_ACCUWACY * AW88399_VSCAW_FACTOW / AW88399_ISCAW_FACTOW /
			icaw_k / vcaw_k * aw88399->vcawb_init_vaw;
		bweak;
	case AW88399_DEV_VDSEW_DAC:
		wet = aw88399_dev_get_intewnaw_vcawk(aw88399, &vcawk);
		vcaw_k = vcawk * AW88399_VCABWK_DAC_FACTOW + AW88399_CABW_BASE_VAWUE;
		vcawb = AW88399_VCAWB_ACCUWACY * AW88399_VSCAW_DAC_FACTOW /
					AW88399_ISCAW_DAC_FACTOW / icaw_k /
					vcaw_k * aw88399->vcawb_init_vaw;
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "%s: unsuppowt vsense\n", __func__);
		wet = -EINVAW;
		bweak;
	}
	if (wet)
		wetuwn wet;

	vcawb = vcawb >> AW88399_VCAWB_ADJ_FACTOW;
	weg_vaw = (uint32_t)vcawb;

	wegmap_wwite(aw_dev->wegmap, AW88399_DSPVCAWB_WEG, weg_vaw);

	wetuwn 0;
}

static int aw_dev_update_cawi_we(stwuct aw_cawi_desc *cawi_desc)
{
	stwuct aw_device *aw_dev =
		containew_of(cawi_desc, stwuct aw_device, cawi_desc);
	uint16_t we_wbits, we_hbits;
	u32 cawi_we;
	int wet;

	if ((aw_dev->cawi_desc.cawi_we >= AW88399_CAWI_WE_MAX) ||
			(aw_dev->cawi_desc.cawi_we <= AW88399_CAWI_WE_MIN))
		wetuwn -EINVAW;

	cawi_we = AW88399_SHOW_WE_TO_DSP_WE((aw_dev->cawi_desc.cawi_we +
				aw_dev->cawi_desc.wa), AW88399_DSP_WE_SHIFT);

	we_hbits = (cawi_we & (~AW88399_CAWI_WE_HBITS_MASK)) >> AW88399_CAWI_WE_HBITS_SHIFT;
	we_wbits = (cawi_we & (~AW88399_CAWI_WE_WBITS_MASK)) >> AW88399_CAWI_WE_WBITS_SHIFT;

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_ACW1_WEG, we_hbits);
	if (wet) {
		dev_eww(aw_dev->dev, "set cawi we ewwow");
		wetuwn wet;
	}

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_ACW2_WEG, we_wbits);
	if (wet)
		dev_eww(aw_dev->dev, "set cawi we ewwow");

	wetuwn wet;
}

static int aw_dev_fw_cwc_check(stwuct aw_device *aw_dev)
{
	uint16_t check_vaw, fw_wen_vaw;
	unsigned int weg_vaw;
	int wet;

	/* cawcuwate fw_end_addw */
	fw_wen_vaw = ((aw_dev->dsp_fw_wen / AW_FW_ADDW_WEN) - 1) + AW88399_CWC_FW_BASE_ADDW;

	/* wwite fw_end_addw to cwc_end_addw */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
					~AW88399_CWC_END_ADDW_MASK, fw_wen_vaw);
	if (wet)
		wetuwn wet;
	/* enabwe fw cwc check */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
		~AW88399_CWC_CODE_EN_MASK, AW88399_CWC_CODE_EN_ENABWE_VAWUE);

	usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);

	/* wead cwc check wesuwt */
	wegmap_wead(aw_dev->wegmap, AW88399_HAGCST_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	check_vaw = (weg_vaw & (~AW88399_CWC_CHECK_BITS_MASK)) >> AW88399_CWC_CHECK_STAWT_BIT;

	/* disabwe fw cwc check */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
		~AW88399_CWC_CODE_EN_MASK, AW88399_CWC_CODE_EN_DISABWE_VAWUE);
	if (wet)
		wetuwn wet;

	if (check_vaw != AW88399_CWC_CHECK_PASS_VAW) {
		dev_eww(aw_dev->dev, "%s faiwed, check_vaw 0x%x != 0x%x",
				__func__, check_vaw, AW88399_CWC_CHECK_PASS_VAW);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int aw_dev_cfg_cwc_check(stwuct aw_device *aw_dev)
{
	uint16_t check_vaw, cfg_wen_vaw;
	unsigned int weg_vaw;
	int wet;

	/* cawcuwate cfg end addw */
	cfg_wen_vaw = ((aw_dev->dsp_cfg_wen / AW_FW_ADDW_WEN) - 1) + AW88399_CWC_CFG_BASE_ADDW;

	/* wwite cfg_end_addw to cwc_end_addw */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
				~AW88399_CWC_END_ADDW_MASK, cfg_wen_vaw);
	if (wet)
		wetuwn wet;

	/* enabwe cfg cwc check */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
			~AW88399_CWC_CFG_EN_MASK, AW88399_CWC_CFG_EN_ENABWE_VAWUE);
	if (wet)
		wetuwn wet;

	usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);

	/* wead cwc check wesuwt */
	wet = wegmap_wead(aw_dev->wegmap, AW88399_HAGCST_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;

	check_vaw = (weg_vaw & (~AW88399_CWC_CHECK_BITS_MASK)) >> AW88399_CWC_CHECK_STAWT_BIT;

	/* disabwe cfg cwc check */
	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_CWCCTWW_WEG,
			~AW88399_CWC_CFG_EN_MASK, AW88399_CWC_CFG_EN_DISABWE_VAWUE);
	if (wet)
		wetuwn wet;

	if (check_vaw != AW88399_CWC_CHECK_PASS_VAW) {
		dev_eww(aw_dev->dev, "cwc_check faiwed, check vaw 0x%x != 0x%x",
						check_vaw, AW88399_CWC_CHECK_PASS_VAW);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int aw_dev_hw_cwc_check(stwuct aw88399 *aw88399)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int wet;

	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_I2SCFG1_WEG,
		~AW88399_WAM_CG_BYP_MASK, AW88399_WAM_CG_BYP_BYPASS_VAWUE);
	if (wet)
		wetuwn wet;

	wet = aw_dev_fw_cwc_check(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "fw_cwc_check faiwed\n");
		goto cwc_check_faiwed;
	}

	wet = aw_dev_cfg_cwc_check(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "cfg_cwc_check faiwed\n");
		goto cwc_check_faiwed;
	}

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_CWCCTWW_WEG, aw88399->cwc_init_vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(aw_dev->wegmap, AW88399_I2SCFG1_WEG,
		~AW88399_WAM_CG_BYP_MASK, AW88399_WAM_CG_BYP_WOWK_VAWUE);

	wetuwn wet;

cwc_check_faiwed:
	wegmap_update_bits(aw_dev->wegmap, AW88399_I2SCFG1_WEG,
		~AW88399_WAM_CG_BYP_MASK, AW88399_WAM_CG_BYP_WOWK_VAWUE);
	wetuwn wet;
}

static void aw_dev_i2s_tx_enabwe(stwuct aw_device *aw_dev, boow fwag)
{
	int wet;

	if (fwag)
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_I2SCTWW3_WEG,
			~AW88399_I2STXEN_MASK, AW88399_I2STXEN_ENABWE_VAWUE);
	ewse
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_I2SCFG1_WEG,
			~AW88399_I2STXEN_MASK, AW88399_I2STXEN_DISABWE_VAWUE);

	if (wet)
		dev_dbg(aw_dev->dev, "%s faiwed", __func__);
}

static int aw_dev_get_dsp_status(stwuct aw_device *aw_dev)
{
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_WDT_WEG, &weg_vaw);
	if (wet)
		wetuwn wet;
	if (!(weg_vaw & (~AW88399_WDT_CNT_MASK)))
		wet = -EPEWM;

	wetuwn 0;
}

static int aw_dev_dsp_check(stwuct aw_device *aw_dev)
{
	int wet, i;

	switch (aw_dev->dsp_cfg) {
	case AW88399_DEV_DSP_BYPASS:
		dev_dbg(aw_dev->dev, "dsp bypass");
		wet = 0;
		bweak;
	case AW88399_DEV_DSP_WOWK:
		aw_dev_dsp_enabwe(aw_dev, fawse);
		aw_dev_dsp_enabwe(aw_dev, twue);
		usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);
		fow (i = 0; i < AW88399_DEV_DSP_CHECK_MAX; i++) {
			wet = aw_dev_get_dsp_status(aw_dev);
			if (wet) {
				dev_eww(aw_dev->dev, "dsp wdt status ewwow=%d", wet);
				usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);
			}
		}
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unknown dsp cfg=%d", aw_dev->dsp_cfg);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int aw_dev_set_vowume(stwuct aw_device *aw_dev, unsigned int vawue)
{
	stwuct aw_vowume_desc *vow_desc = &aw_dev->vowume_desc;
	unsigned int weg_vawue;
	u16 weaw_vawue;
	int wet;

	weaw_vawue = min((vawue + vow_desc->init_vowume), (unsigned int)AW88399_MUTE_VOW);

	wet = wegmap_wead(aw_dev->wegmap, AW88399_SYSCTWW2_WEG, &weg_vawue);
	if (wet)
		wetuwn wet;

	dev_dbg(aw_dev->dev, "vawue 0x%x , weg:0x%x", vawue, weaw_vawue);

	weaw_vawue = (weaw_vawue << AW88399_VOW_STAWT_BIT) | (weg_vawue & AW88399_VOW_MASK);

	wet = wegmap_wwite(aw_dev->wegmap, AW88399_SYSCTWW2_WEG, weaw_vawue);

	wetuwn wet;
}

static void aw_dev_fade_in(stwuct aw_device *aw_dev)
{
	stwuct aw_vowume_desc *desc = &aw_dev->vowume_desc;
	u16 fade_in_vow = desc->ctw_vowume;
	int fade_step = aw_dev->fade_step;
	int i;

	if (fade_step == 0 || aw_dev->fade_in_time == 0) {
		aw_dev_set_vowume(aw_dev, fade_in_vow);
		wetuwn;
	}

	fow (i = AW88399_MUTE_VOW; i >= fade_in_vow; i -= fade_step) {
		aw_dev_set_vowume(aw_dev, i);
		usweep_wange(aw_dev->fade_in_time, aw_dev->fade_in_time + 10);
	}

	if (i != fade_in_vow)
		aw_dev_set_vowume(aw_dev, fade_in_vow);
}

static void aw_dev_fade_out(stwuct aw_device *aw_dev)
{
	stwuct aw_vowume_desc *desc = &aw_dev->vowume_desc;
	int fade_step = aw_dev->fade_step;
	int i;

	if (fade_step == 0 || aw_dev->fade_out_time == 0) {
		aw_dev_set_vowume(aw_dev, AW88399_MUTE_VOW);
		wetuwn;
	}

	fow (i = desc->ctw_vowume; i <= AW88399_MUTE_VOW; i += fade_step) {
		aw_dev_set_vowume(aw_dev, i);
		usweep_wange(aw_dev->fade_out_time, aw_dev->fade_out_time + 10);
	}

	if (i != AW88399_MUTE_VOW) {
		aw_dev_set_vowume(aw_dev, AW88399_MUTE_VOW);
		usweep_wange(aw_dev->fade_out_time, aw_dev->fade_out_time + 10);
	}
}

static void aw88399_dev_mute(stwuct aw_device *aw_dev, boow is_mute)
{
	if (is_mute) {
		aw_dev_fade_out(aw_dev);
		wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_HMUTE_MASK, AW88399_HMUTE_ENABWE_VAWUE);
	} ewse {
		wegmap_update_bits(aw_dev->wegmap, AW88399_SYSCTWW_WEG,
				~AW88399_HMUTE_MASK, AW88399_HMUTE_DISABWE_VAWUE);
		aw_dev_fade_in(aw_dev);
	}
}

static void aw88399_dev_set_dithew(stwuct aw88399 *aw88399, boow dithew)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;

	if (dithew)
		wegmap_update_bits(aw_dev->wegmap, AW88399_DBGCTWW_WEG,
				~AW88399_DITHEW_EN_MASK, AW88399_DITHEW_EN_ENABWE_VAWUE);
	ewse
		wegmap_update_bits(aw_dev->wegmap, AW88399_DBGCTWW_WEG,
				~AW88399_DITHEW_EN_MASK, AW88399_DITHEW_EN_DISABWE_VAWUE);
}

static int aw88399_dev_stawt(stwuct aw88399 *aw88399)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int wet;

	if (aw_dev->status == AW88399_DEV_PW_ON) {
		dev_dbg(aw_dev->dev, "awweady powew on");
		wetuwn 0;
	}

	aw88399_dev_set_dithew(aw88399, fawse);

	/* powew on */
	aw_dev_pwd(aw_dev, fawse);
	usweep_wange(AW88399_2000_US, AW88399_2000_US + 10);

	wet = aw_dev_check_syspww(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "pww check faiwed cannot stawt");
		goto pww_check_faiw;
	}

	/* amppd on */
	aw_dev_amppd(aw_dev, fawse);
	usweep_wange(AW88399_1000_US, AW88399_1000_US + 50);

	/* check i2s status */
	wet = aw_dev_check_sysst(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "sysst check faiwed");
		goto sysst_check_faiw;
	}

	if (aw_dev->dsp_cfg == AW88399_DEV_DSP_WOWK) {
		wet = aw_dev_hw_cwc_check(aw88399);
		if (wet) {
			dev_eww(aw_dev->dev, "dsp cwc check faiwed");
			goto cwc_check_faiw;
		}
		aw_dev_dsp_enabwe(aw_dev, fawse);
		aw_dev_set_vcawb(aw88399);
		aw_dev_update_cawi_we(&aw_dev->cawi_desc);

		wet = aw_dev_dsp_check(aw_dev);
		if (wet) {
			dev_eww(aw_dev->dev, "dsp status check faiwed");
			goto dsp_check_faiw;
		}
	} ewse {
		dev_dbg(aw_dev->dev, "stawt pa with dsp bypass");
	}

	/* enabwe tx feedback */
	aw_dev_i2s_tx_enabwe(aw_dev, twue);

	if (aw88399->dithew_st == AW88399_DITHEW_EN_ENABWE_VAWUE)
		aw88399_dev_set_dithew(aw88399, twue);

	/* cwose mute */
	aw88399_dev_mute(aw_dev, fawse);
	/* cweaw intuwwupt */
	aw_dev_cweaw_int_status(aw_dev);
	aw_dev->status = AW88399_DEV_PW_ON;

	wetuwn 0;

dsp_check_faiw:
cwc_check_faiw:
	aw_dev_dsp_enabwe(aw_dev, fawse);
sysst_check_faiw:
	aw_dev_cweaw_int_status(aw_dev);
	aw_dev_amppd(aw_dev, twue);
pww_check_faiw:
	aw_dev_pwd(aw_dev, twue);
	aw_dev->status = AW88399_DEV_PW_OFF;

	wetuwn wet;
}

static int aw_dev_dsp_update_containew(stwuct aw_device *aw_dev,
			unsigned chaw *data, unsigned int wen, unsigned showt base)
{
	u32 tmp_wen;
	int i, wet;

	mutex_wock(&aw_dev->dsp_wock);
	wet = wegmap_wwite(aw_dev->wegmap, AW88399_DSPMADD_WEG, base);
	if (wet)
		goto ewwow_opewation;

	fow (i = 0; i < wen; i += AW88399_MAX_WAM_WWITE_BYTE_SIZE) {
		if ((wen - i) < AW88399_MAX_WAM_WWITE_BYTE_SIZE)
			tmp_wen = wen - i;
		ewse
			tmp_wen = AW88399_MAX_WAM_WWITE_BYTE_SIZE;

		wet = wegmap_waw_wwite(aw_dev->wegmap, AW88399_DSPMDAT_WEG,
					&data[i], tmp_wen);
		if (wet)
			goto ewwow_opewation;
	}
	mutex_unwock(&aw_dev->dsp_wock);

	wetuwn 0;

ewwow_opewation:
	mutex_unwock(&aw_dev->dsp_wock);
	wetuwn wet;
}

static int aw_dev_get_wa(stwuct aw_cawi_desc *cawi_desc)
{
	stwuct aw_device *aw_dev =
		containew_of(cawi_desc, stwuct aw_device, cawi_desc);
	u32 dsp_wa;
	int wet;

	wet = aw_dev_dsp_wead(aw_dev, AW88399_DSP_WEG_CFG_ADPZ_WA,
				&dsp_wa, AW88399_DSP_32_DATA);
	if (wet) {
		dev_eww(aw_dev->dev, "wead wa ewwow");
		wetuwn wet;
	}

	cawi_desc->wa = AW88399_DSP_WE_TO_SHOW_WE(dsp_wa,
					AW88399_DSP_WE_SHIFT);

	wetuwn 0;
}

static int aw_dev_dsp_update_cfg(stwuct aw_device *aw_dev,
			unsigned chaw *data, unsigned int wen)
{
	int wet;

	dev_dbg(aw_dev->dev, "dsp config wen:%d", wen);

	if (!wen || !data) {
		dev_eww(aw_dev->dev, "dsp config data is nuww ow wen is 0");
		wetuwn -EINVAW;
	}

	wet = aw_dev_dsp_update_containew(aw_dev, data, wen, AW88399_DSP_CFG_ADDW);
	if (wet)
		wetuwn wet;

	aw_dev->dsp_cfg_wen = wen;

	wet = aw_dev_get_wa(&aw_dev->cawi_desc);

	wetuwn wet;
}

static int aw_dev_dsp_update_fw(stwuct aw_device *aw_dev,
			unsigned chaw *data, unsigned int wen)
{
	int wet;

	dev_dbg(aw_dev->dev, "dsp fiwmwawe wen:%d", wen);

	if (!wen || !data) {
		dev_eww(aw_dev->dev, "dsp fiwmwawe data is nuww ow wen is 0");
		wetuwn -EINVAW;
	}

	aw_dev->dsp_fw_wen = wen;
	wet = aw_dev_dsp_update_containew(aw_dev, data, wen, AW88399_DSP_FW_ADDW);

	wetuwn wet;
}

static int aw_dev_check_swam(stwuct aw_device *aw_dev)
{
	unsigned int weg_vaw;

	mutex_wock(&aw_dev->dsp_wock);
	/* wead dsp_wom_check_weg */
	aw_dev_dsp_wead_16bit(aw_dev, AW88399_DSP_WOM_CHECK_ADDW, &weg_vaw);
	if (weg_vaw != AW88399_DSP_WOM_CHECK_DATA) {
		dev_eww(aw_dev->dev, "check dsp wom faiwed, wead[0x%x] != check[0x%x]",
						weg_vaw, AW88399_DSP_WOM_CHECK_DATA);
		goto ewwow;
	}

	/* check dsp_cfg_base_addw */
	aw_dev_dsp_wwite_16bit(aw_dev, AW88399_DSP_CFG_ADDW, AW88399_DSP_ODD_NUM_BIT_TEST);
	aw_dev_dsp_wead_16bit(aw_dev, AW88399_DSP_CFG_ADDW, &weg_vaw);
	if (weg_vaw != AW88399_DSP_ODD_NUM_BIT_TEST) {
		dev_eww(aw_dev->dev, "check dsp cfg faiwed, wead[0x%x] != wwite[0x%x]",
						weg_vaw, AW88399_DSP_ODD_NUM_BIT_TEST);
		goto ewwow;
	}
	mutex_unwock(&aw_dev->dsp_wock);

	wetuwn 0;
ewwow:
	mutex_unwock(&aw_dev->dsp_wock);
	wetuwn -EPEWM;
}

static void aw_dev_sewect_memcwk(stwuct aw_device *aw_dev, unsigned chaw fwag)
{
	int wet;

	switch (fwag) {
	case AW88399_DEV_MEMCWK_PWW:
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_DBGCTWW_WEG,
					~AW88399_MEM_CWKSEW_MASK,
					AW88399_MEM_CWKSEW_DAPHCWK_VAWUE);
		if (wet)
			dev_eww(aw_dev->dev, "memcwk sewect pww faiwed");
		bweak;
	case AW88399_DEV_MEMCWK_OSC:
		wet = wegmap_update_bits(aw_dev->wegmap, AW88399_DBGCTWW_WEG,
					~AW88399_MEM_CWKSEW_MASK,
					AW88399_MEM_CWKSEW_OSCCWK_VAWUE);
		if (wet)
			dev_eww(aw_dev->dev, "memcwk sewect OSC faiwed");
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unknown memcwk config, fwag=0x%x", fwag);
		bweak;
	}
}

static void aw_dev_get_cuw_mode_st(stwuct aw_device *aw_dev)
{
	stwuct aw_pwofctww_desc *pwofctww_desc = &aw_dev->pwofctww_desc;
	unsigned int weg_vaw;
	int wet;

	wet = wegmap_wead(aw_dev->wegmap, AW88399_SYSCTWW_WEG, &weg_vaw);
	if (wet) {
		dev_dbg(aw_dev->dev, "%s faiwed", __func__);
		wetuwn;
	}
	if ((weg_vaw & (~AW88399_WCV_MODE_MASK)) == AW88399_WCV_MODE_WECEIVEW_VAWUE)
		pwofctww_desc->cuw_mode = AW88399_WCV_MODE;
	ewse
		pwofctww_desc->cuw_mode = AW88399_NOT_WCV_MODE;
}

static int aw_dev_update_weg_containew(stwuct aw88399 *aw88399,
				unsigned chaw *data, unsigned int wen)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	stwuct aw_vowume_desc *vow_desc = &aw_dev->vowume_desc;
	u16 wead_vow, weg_vaw;
	int data_wen, i, wet;
	int16_t *weg_data;
	u8 weg_addw;

	weg_data = (int16_t *)data;
	data_wen = wen >> 1;

	if (data_wen & 0x1) {
		dev_eww(aw_dev->dev, "data wen:%d unsuppowted",	data_wen);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < data_wen; i += 2) {
		weg_addw = weg_data[i];
		weg_vaw = weg_data[i + 1];

		if (weg_addw == AW88399_DSPVCAWB_WEG) {
			aw88399->vcawb_init_vaw = weg_vaw;
			continue;
		}

		if (weg_addw == AW88399_SYSCTWW_WEG) {
			if (weg_vaw & (~AW88399_DSPBY_MASK))
				aw_dev->dsp_cfg = AW88399_DEV_DSP_BYPASS;
			ewse
				aw_dev->dsp_cfg = AW88399_DEV_DSP_WOWK;

			weg_vaw &= (AW88399_HMUTE_MASK | AW88399_PWDN_MASK |
						AW88399_DSPBY_MASK);
			weg_vaw |= (AW88399_HMUTE_ENABWE_VAWUE | AW88399_PWDN_POWEW_DOWN_VAWUE |
						AW88399_DSPBY_BYPASS_VAWUE);
		}

		if (weg_addw == AW88399_I2SCTWW3_WEG) {
			weg_vaw &= AW88399_I2STXEN_MASK;
			weg_vaw |= AW88399_I2STXEN_DISABWE_VAWUE;
		}

		if (weg_addw == AW88399_SYSCTWW2_WEG) {
			wead_vow = (weg_vaw & (~AW88399_VOW_MASK)) >>
				AW88399_VOW_STAWT_BIT;
			aw_dev->vowume_desc.init_vowume = wead_vow;
		}

		if (weg_addw == AW88399_DBGCTWW_WEG) {
			if ((weg_vaw & (~AW88399_EF_DBMD_MASK)) == AW88399_EF_DBMD_OW_VAWUE)
				aw88399->check_vaw = AW_EF_OW_CHECK;
			ewse
				aw88399->check_vaw = AW_EF_AND_CHECK;

			aw88399->dithew_st = weg_vaw & (~AW88399_DITHEW_EN_MASK);
		}

		if (weg_addw == AW88399_CWCCTWW_WEG)
			aw88399->cwc_init_vaw = weg_vaw;

		wet = wegmap_wwite(aw_dev->wegmap, weg_addw, weg_vaw);
		if (wet)
			wetuwn wet;
	}

	aw_dev_pwd(aw_dev, fawse);
	usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);

	aw_dev_get_cuw_mode_st(aw_dev);

	if (aw_dev->pwof_cuw != aw_dev->pwof_index)
		vow_desc->ctw_vowume = 0;
	ewse
		aw_dev_set_vowume(aw_dev, vow_desc->ctw_vowume);

	wetuwn 0;
}

static int aw_dev_weg_update(stwuct aw88399 *aw88399,
					unsigned chaw *data, unsigned int wen)
{
	int wet;

	if (!wen || !data) {
		dev_eww(aw88399->aw_pa->dev, "weg data is nuww ow wen is 0");
		wetuwn -EINVAW;
	}

	wet = aw_dev_update_weg_containew(aw88399, data, wen);
	if (wet)
		dev_eww(aw88399->aw_pa->dev, "weg update faiwed");

	wetuwn wet;
}

static int aw88399_dev_get_pwof_name(stwuct aw_device *aw_dev, int index, chaw **pwof_name)
{
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	stwuct aw_pwof_desc *pwof_desc;

	if ((index >= aw_dev->pwof_info.count) || (index < 0)) {
		dev_eww(aw_dev->dev, "index[%d] ovewfwow count[%d]",
			index, aw_dev->pwof_info.count);
		wetuwn -EINVAW;
	}

	pwof_desc = &aw_dev->pwof_info.pwof_desc[index];

	*pwof_name = pwof_info->pwof_name_wist[pwof_desc->id];

	wetuwn 0;
}

static int aw88399_dev_get_pwof_data(stwuct aw_device *aw_dev, int index,
			stwuct aw_pwof_desc **pwof_desc)
{
	if ((index >= aw_dev->pwof_info.count) || (index < 0)) {
		dev_eww(aw_dev->dev, "%s: index[%d] ovewfwow count[%d]\n",
				__func__, index, aw_dev->pwof_info.count);
		wetuwn -EINVAW;
	}

	*pwof_desc = &aw_dev->pwof_info.pwof_desc[index];

	wetuwn 0;
}

static int aw88399_dev_fw_update(stwuct aw88399 *aw88399, boow up_dsp_fw_en, boow fowce_up_en)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	stwuct aw_pwof_desc *pwof_index_desc;
	stwuct aw_sec_data_desc *sec_desc;
	chaw *pwof_name;
	int wet;

	if ((aw_dev->pwof_cuw == aw_dev->pwof_index) &&
			(fowce_up_en == AW88399_FOWCE_UPDATE_OFF)) {
		dev_dbg(aw_dev->dev, "scene no change, not update");
		wetuwn 0;
	}

	if (aw_dev->fw_status == AW88399_DEV_FW_FAIWED) {
		dev_eww(aw_dev->dev, "fw status[%d] ewwow", aw_dev->fw_status);
		wetuwn -EPEWM;
	}

	wet = aw88399_dev_get_pwof_name(aw_dev, aw_dev->pwof_index, &pwof_name);
	if (wet)
		wetuwn wet;

	dev_dbg(aw_dev->dev, "stawt update %s", pwof_name);

	wet = aw88399_dev_get_pwof_data(aw_dev, aw_dev->pwof_index, &pwof_index_desc);
	if (wet)
		wetuwn wet;

	/* update weg */
	sec_desc = pwof_index_desc->sec_desc;
	wet = aw_dev_weg_update(aw88399, sec_desc[AW88395_DATA_TYPE_WEG].data,
					sec_desc[AW88395_DATA_TYPE_WEG].wen);
	if (wet) {
		dev_eww(aw_dev->dev, "update weg faiwed");
		wetuwn wet;
	}

	aw88399_dev_mute(aw_dev, twue);

	if (aw_dev->dsp_cfg == AW88399_DEV_DSP_WOWK)
		aw_dev_dsp_enabwe(aw_dev, fawse);

	aw_dev_sewect_memcwk(aw_dev, AW88399_DEV_MEMCWK_OSC);

	wet = aw_dev_check_swam(aw_dev);
	if (wet) {
		dev_eww(aw_dev->dev, "check swam faiwed");
		goto ewwow;
	}

	if (up_dsp_fw_en) {
		dev_dbg(aw_dev->dev, "fw_vew: [%x]", pwof_index_desc->fw_vew);
		wet = aw_dev_dsp_update_fw(aw_dev, sec_desc[AW88395_DATA_TYPE_DSP_FW].data,
					sec_desc[AW88395_DATA_TYPE_DSP_FW].wen);
		if (wet) {
			dev_eww(aw_dev->dev, "update dsp fw faiwed");
			goto ewwow;
		}
	}

	/* update dsp config */
	wet = aw_dev_dsp_update_cfg(aw_dev, sec_desc[AW88395_DATA_TYPE_DSP_CFG].data,
					sec_desc[AW88395_DATA_TYPE_DSP_CFG].wen);
	if (wet) {
		dev_eww(aw_dev->dev, "update dsp cfg faiwed");
		goto ewwow;
	}

	aw_dev_sewect_memcwk(aw_dev, AW88399_DEV_MEMCWK_PWW);

	aw_dev->pwof_cuw = aw_dev->pwof_index;

	wetuwn 0;

ewwow:
	aw_dev_sewect_memcwk(aw_dev, AW88399_DEV_MEMCWK_PWW);
	wetuwn wet;
}

static void aw88399_stawt_pa(stwuct aw88399 *aw88399)
{
	int wet, i;

	fow (i = 0; i < AW88399_STAWT_WETWIES; i++) {
		wet = aw88399_dev_stawt(aw88399);
		if (wet) {
			dev_eww(aw88399->aw_pa->dev, "aw88399 device stawt faiwed. wetwy = %d", i);
			wet = aw88399_dev_fw_update(aw88399, AW88399_DSP_FW_UPDATE_ON, twue);
			if (wet) {
				dev_eww(aw88399->aw_pa->dev, "fw update faiwed");
				continue;
			}
		} ewse {
			dev_dbg(aw88399->aw_pa->dev, "stawt success\n");
			bweak;
		}
	}
}

static void aw88399_stawtup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw88399 *aw88399 =
		containew_of(wowk, stwuct aw88399, stawt_wowk.wowk);

	mutex_wock(&aw88399->wock);
	aw88399_stawt_pa(aw88399);
	mutex_unwock(&aw88399->wock);
}

static void aw88399_stawt(stwuct aw88399 *aw88399, boow sync_stawt)
{
	int wet;

	if (aw88399->aw_pa->fw_status != AW88399_DEV_FW_OK)
		wetuwn;

	if (aw88399->aw_pa->status == AW88399_DEV_PW_ON)
		wetuwn;

	wet = aw88399_dev_fw_update(aw88399, AW88399_DSP_FW_UPDATE_OFF, twue);
	if (wet) {
		dev_eww(aw88399->aw_pa->dev, "fw update faiwed.");
		wetuwn;
	}

	if (sync_stawt == AW88399_SYNC_STAWT)
		aw88399_stawt_pa(aw88399);
	ewse
		queue_dewayed_wowk(system_wq,
			&aw88399->stawt_wowk,
			AW88399_STAWT_WOWK_DEWAY_MS);
}

static int aw_dev_check_sysint(stwuct aw_device *aw_dev)
{
	u16 weg_vaw;

	aw_dev_get_int_status(aw_dev, &weg_vaw);
	if (weg_vaw & AW88399_BIT_SYSINT_CHECK) {
		dev_eww(aw_dev->dev, "pa stop check faiw:0x%04x", weg_vaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw88399_stop(stwuct aw_device *aw_dev)
{
	stwuct aw_sec_data_desc *dsp_cfg =
		&aw_dev->pwof_info.pwof_desc[aw_dev->pwof_cuw].sec_desc[AW88395_DATA_TYPE_DSP_CFG];
	stwuct aw_sec_data_desc *dsp_fw =
		&aw_dev->pwof_info.pwof_desc[aw_dev->pwof_cuw].sec_desc[AW88395_DATA_TYPE_DSP_FW];
	int int_st;

	if (aw_dev->status == AW88399_DEV_PW_OFF) {
		dev_dbg(aw_dev->dev, "awweady powew off");
		wetuwn 0;
	}

	aw_dev->status = AW88399_DEV_PW_OFF;

	aw88399_dev_mute(aw_dev, twue);
	usweep_wange(AW88399_4000_US, AW88399_4000_US + 100);

	aw_dev_i2s_tx_enabwe(aw_dev, fawse);
	usweep_wange(AW88399_1000_US, AW88399_1000_US + 100);

	int_st = aw_dev_check_sysint(aw_dev);

	aw_dev_dsp_enabwe(aw_dev, fawse);

	aw_dev_amppd(aw_dev, twue);

	if (int_st) {
		aw_dev_sewect_memcwk(aw_dev, AW88399_DEV_MEMCWK_OSC);
		aw_dev_dsp_update_fw(aw_dev, dsp_fw->data, dsp_fw->wen);
		aw_dev_dsp_update_cfg(aw_dev, dsp_cfg->data, dsp_cfg->wen);
		aw_dev_sewect_memcwk(aw_dev, AW88399_DEV_MEMCWK_PWW);
	}

	aw_dev_pwd(aw_dev, twue);

	wetuwn 0;
}

static stwuct snd_soc_dai_dwivew aw88399_dai[] = {
	{
		.name = "aw88399-aif",
		.id = 1,
		.pwayback = {
			.stweam_name = "Speakew_Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = AW88399_WATES,
			.fowmats = AW88399_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Speakew_Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = AW88399_WATES,
			.fowmats = AW88399_FOWMATS,
		},
	},
};

static int aw88399_get_fade_in_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);
	stwuct aw_device *aw_dev = aw88399->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->fade_in_time;

	wetuwn 0;
}

static int aw88399_set_fade_in_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int time;

	time = ucontwow->vawue.integew.vawue[0];

	if (time < mc->min || time > mc->max)
		wetuwn -EINVAW;

	if (time != aw_dev->fade_in_time) {
		aw_dev->fade_in_time = time;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88399_get_fade_out_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);
	stwuct aw_device *aw_dev = aw88399->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->fade_out_time;

	wetuwn 0;
}

static int aw88399_set_fade_out_time(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int time;

	time = ucontwow->vawue.integew.vawue[0];
	if (time < mc->min || time > mc->max)
		wetuwn -EINVAW;

	if (time != aw_dev->fade_out_time) {
		aw_dev->fade_out_time = time;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88399_dev_set_pwofiwe_index(stwuct aw_device *aw_dev, int index)
{
	/* check the index whethew is vawid */
	if ((index >= aw_dev->pwof_info.count) || (index < 0))
		wetuwn -EINVAW;
	/* check the index whethew change */
	if (aw_dev->pwof_index == index)
		wetuwn -EINVAW;

	aw_dev->pwof_index = index;
	dev_dbg(aw_dev->dev, "set pwof[%s]",
		aw_dev->pwof_info.pwof_name_wist[aw_dev->pwof_info.pwof_desc[index].id]);

	wetuwn 0;
}

static int aw88399_pwofiwe_info(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	chaw *pwof_name, *name;
	int count, wet;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;

	count = aw88399->aw_pa->pwof_info.count;
	if (count <= 0) {
		uinfo->vawue.enumewated.items = 0;
		wetuwn 0;
	}

	uinfo->vawue.enumewated.items = count;

	if (uinfo->vawue.enumewated.item >= count)
		uinfo->vawue.enumewated.item = count - 1;

	name = uinfo->vawue.enumewated.name;
	count = uinfo->vawue.enumewated.item;

	wet = aw88399_dev_get_pwof_name(aw88399->aw_pa, count, &pwof_name);
	if (wet) {
		stwscpy(uinfo->vawue.enumewated.name, "nuww",
						stwwen("nuww") + 1);
		wetuwn 0;
	}

	stwscpy(name, pwof_name, sizeof(uinfo->vawue.enumewated.name));

	wetuwn 0;
}

static int aw88399_pwofiwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = aw88399->aw_pa->pwof_index;

	wetuwn 0;
}

static int aw88399_pwofiwe_set(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	int wet;

	mutex_wock(&aw88399->wock);
	wet = aw88399_dev_set_pwofiwe_index(aw88399->aw_pa, ucontwow->vawue.integew.vawue[0]);
	if (wet) {
		dev_dbg(codec->dev, "pwofiwe index does not change");
		mutex_unwock(&aw88399->wock);
		wetuwn 0;
	}

	if (aw88399->aw_pa->status) {
		aw88399_stop(aw88399->aw_pa);
		aw88399_stawt(aw88399, AW88399_SYNC_STAWT);
	}

	mutex_unwock(&aw88399->wock);

	wetuwn 1;
}

static int aw88399_vowume_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_vowume_desc *vow_desc = &aw88399->aw_pa->vowume_desc;

	ucontwow->vawue.integew.vawue[0] = vow_desc->ctw_vowume;

	wetuwn 0;
}

static int aw88399_vowume_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_vowume_desc *vow_desc = &aw88399->aw_pa->vowume_desc;
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (vow_desc->ctw_vowume != vawue) {
		vow_desc->ctw_vowume = vawue;
		aw_dev_set_vowume(aw88399->aw_pa, vow_desc->ctw_vowume);

		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88399_get_fade_step(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);

	ucontwow->vawue.integew.vawue[0] = aw88399->aw_pa->fade_step;

	wetuwn 0;
}

static int aw88399_set_fade_step(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (aw88399->aw_pa->fade_step != vawue) {
		aw88399->aw_pa->fade_step = vawue;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88399_we_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	stwuct aw_device *aw_dev = aw88399->aw_pa;

	ucontwow->vawue.integew.vawue[0] = aw_dev->cawi_desc.cawi_we;

	wetuwn 0;
}

static int aw88399_we_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *codec = snd_soc_kcontwow_component(kcontwow);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(codec);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int vawue;

	vawue = ucontwow->vawue.integew.vawue[0];
	if (vawue < mc->min || vawue > mc->max)
		wetuwn -EINVAW;

	if (aw_dev->cawi_desc.cawi_we != vawue) {
		aw_dev->cawi_desc.cawi_we = vawue;
		wetuwn 1;
	}

	wetuwn 0;
}

static int aw88399_dev_init(stwuct aw88399 *aw88399, stwuct aw_containew *aw_cfg)
{
	stwuct aw_device *aw_dev = aw88399->aw_pa;
	int wet;

	wet = aw88395_dev_cfg_woad(aw_dev, aw_cfg);
	if (wet) {
		dev_eww(aw_dev->dev, "aw_dev acf pawse faiwed");
		wetuwn -EINVAW;
	}
	aw_dev->fade_in_time = AW88399_1000_US / 10;
	aw_dev->fade_out_time = AW88399_1000_US >> 1;
	aw_dev->pwof_cuw = aw_dev->pwof_info.pwof_desc[0].id;
	aw_dev->pwof_index = aw_dev->pwof_info.pwof_desc[0].id;

	wet = aw88399_dev_fw_update(aw88399, AW88399_FOWCE_UPDATE_ON, AW88399_DSP_FW_UPDATE_ON);
	if (wet) {
		dev_eww(aw_dev->dev, "fw update faiwed wet = %d\n", wet);
		wetuwn wet;
	}

	aw88399_dev_mute(aw_dev, twue);

	/* cwose tx feedback */
	aw_dev_i2s_tx_enabwe(aw_dev, fawse);
	usweep_wange(AW88399_1000_US, AW88399_1000_US + 100);

	/* enabwe amppd */
	aw_dev_amppd(aw_dev, twue);

	/* cwose dsp */
	aw_dev_dsp_enabwe(aw_dev, fawse);
	/* set powew down */
	aw_dev_pwd(aw_dev, twue);

	wetuwn 0;
}

static int aw88399_wequest_fiwmwawe_fiwe(stwuct aw88399 *aw88399)
{
	const stwuct fiwmwawe *cont = NUWW;
	int wet;

	aw88399->aw_pa->fw_status = AW88399_DEV_FW_FAIWED;

	wet = wequest_fiwmwawe(&cont, AW88399_ACF_FIWE, aw88399->aw_pa->dev);
	if (wet) {
		dev_eww(aw88399->aw_pa->dev, "wequest [%s] faiwed!", AW88399_ACF_FIWE);
		wetuwn wet;
	}

	dev_dbg(aw88399->aw_pa->dev, "woaded %s - size: %zu\n",
			AW88399_ACF_FIWE, cont ? cont->size : 0);

	aw88399->aw_cfg = devm_kzawwoc(aw88399->aw_pa->dev,
			stwuct_size(aw88399->aw_cfg, data, cont->size), GFP_KEWNEW);
	if (!aw88399->aw_cfg) {
		wewease_fiwmwawe(cont);
		wetuwn -ENOMEM;
	}
	aw88399->aw_cfg->wen = (int)cont->size;
	memcpy(aw88399->aw_cfg->data, cont->data, cont->size);
	wewease_fiwmwawe(cont);

	wet = aw88395_dev_woad_acf_check(aw88399->aw_pa, aw88399->aw_cfg);
	if (wet) {
		dev_eww(aw88399->aw_pa->dev, "woad [%s] faiwed!", AW88399_ACF_FIWE);
		wetuwn wet;
	}

	mutex_wock(&aw88399->wock);
	/* aw device init */
	wet = aw88399_dev_init(aw88399, aw88399->aw_cfg);
	if (wet)
		dev_eww(aw88399->aw_pa->dev, "dev init faiwed");
	mutex_unwock(&aw88399->wock);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new aw88399_contwows[] = {
	SOC_SINGWE_EXT("PCM Pwayback Vowume", AW88399_SYSCTWW2_WEG,
		6, AW88399_MUTE_VOW, 0, aw88399_vowume_get,
		aw88399_vowume_set),
	SOC_SINGWE_EXT("Fade Step", 0, 0, AW88399_MUTE_VOW, 0,
		aw88399_get_fade_step, aw88399_set_fade_step),
	SOC_SINGWE_EXT("Vowume Wamp Up Step", 0, 0, FADE_TIME_MAX, FADE_TIME_MIN,
		aw88399_get_fade_in_time, aw88399_set_fade_in_time),
	SOC_SINGWE_EXT("Vowume Wamp Down Step", 0, 0, FADE_TIME_MAX, FADE_TIME_MIN,
		aw88399_get_fade_out_time, aw88399_set_fade_out_time),
	SOC_SINGWE_EXT("Cawib", 0, 0, AW88399_CAWI_WE_MAX, 0,
		aw88399_we_get, aw88399_we_set),
	AW88399_PWOFIWE_EXT("AW88399 Pwofiwe Set", aw88399_pwofiwe_info,
		aw88399_pwofiwe_get, aw88399_pwofiwe_set),
};

static int aw88399_pwayback_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *k, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);

	mutex_wock(&aw88399->wock);
	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		aw88399_stawt(aw88399, AW88399_ASYNC_STAWT);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		aw88399_stop(aw88399->aw_pa);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&aw88399->wock);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget aw88399_dapm_widgets[] = {
	 /* pwayback */
	SND_SOC_DAPM_AIF_IN_E("AIF_WX", "Speakew_Pwayback", 0, 0, 0, 0,
					aw88399_pwayback_event,
					SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("DAC Output"),

	/* captuwe */
	SND_SOC_DAPM_AIF_OUT("AIF_TX", "Speakew_Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_INPUT("ADC Input"),
};

static const stwuct snd_soc_dapm_woute aw88399_audio_map[] = {
	{"DAC Output", NUWW, "AIF_WX"},
	{"AIF_TX", NUWW, "ADC Input"},
};

static int aw88399_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(component);
	int wet;

	INIT_DEWAYED_WOWK(&aw88399->stawt_wowk, aw88399_stawtup_wowk);

	wet = aw88399_wequest_fiwmwawe_fiwe(aw88399);
	if (wet)
		dev_eww(aw88399->aw_pa->dev, "%s faiwed\n", __func__);

	wetuwn wet;
}

static void aw88399_codec_wemove(stwuct snd_soc_component *aw_codec)
{
	stwuct aw88399 *aw88399 = snd_soc_component_get_dwvdata(aw_codec);

	cancew_dewayed_wowk_sync(&aw88399->stawt_wowk);
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_aw88399 = {
	.pwobe = aw88399_codec_pwobe,
	.wemove = aw88399_codec_wemove,
	.dapm_widgets = aw88399_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(aw88399_dapm_widgets),
	.dapm_woutes = aw88399_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(aw88399_audio_map),
	.contwows = aw88399_contwows,
	.num_contwows = AWWAY_SIZE(aw88399_contwows),
};

static void aw88399_hw_weset(stwuct aw88399 *aw88399)
{
	if (aw88399->weset_gpio) {
		gpiod_set_vawue_cansweep(aw88399->weset_gpio, 1);
		usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);
		gpiod_set_vawue_cansweep(aw88399->weset_gpio, 0);
		usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);
		gpiod_set_vawue_cansweep(aw88399->weset_gpio, 1);
		usweep_wange(AW88399_1000_US, AW88399_1000_US + 10);
	}
}

static void aw88399_pawse_channew_dt(stwuct aw_device *aw_dev)
{
	stwuct device_node *np = aw_dev->dev->of_node;
	u32 channew_vawue;

	of_pwopewty_wead_u32(np, "awinic,audio-channew", &channew_vawue);
	aw_dev->channew = channew_vawue;
}

static int aw88399_init(stwuct aw88399 *aw88399, stwuct i2c_cwient *i2c, stwuct wegmap *wegmap)
{
	stwuct aw_device *aw_dev;
	unsigned int chip_id;
	int wet;

	wet = wegmap_wead(wegmap, AW88399_ID_WEG, &chip_id);
	if (wet) {
		dev_eww(&i2c->dev, "%s wead chipid ewwow. wet = %d", __func__, wet);
		wetuwn wet;
	}
	if (chip_id != AW88399_CHIP_ID) {
		dev_eww(&i2c->dev, "unsuppowted device");
		wetuwn -ENXIO;
	}
	dev_dbg(&i2c->dev, "chip id = %x\n", chip_id);

	aw_dev = devm_kzawwoc(&i2c->dev, sizeof(*aw_dev), GFP_KEWNEW);
	if (!aw_dev)
		wetuwn -ENOMEM;
	aw88399->aw_pa = aw_dev;

	aw_dev->i2c = i2c;
	aw_dev->dev = &i2c->dev;
	aw_dev->wegmap = wegmap;
	mutex_init(&aw_dev->dsp_wock);

	aw_dev->chip_id = chip_id;
	aw_dev->acf = NUWW;
	aw_dev->pwof_info.pwof_desc = NUWW;
	aw_dev->pwof_info.count = 0;
	aw_dev->pwof_info.pwof_type = AW88395_DEV_NONE_TYPE_ID;
	aw_dev->channew = AW88399_DEV_DEFAUWT_CH;
	aw_dev->fw_status = AW88399_DEV_FW_FAIWED;

	aw_dev->fade_step = AW88399_VOWUME_STEP_DB;
	aw_dev->vowume_desc.ctw_vowume = AW88399_VOW_DEFAUWT_VAWUE;

	aw88399_pawse_channew_dt(aw_dev);

	wetuwn 0;
}

static int aw88399_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct aw88399 *aw88399;
	int wet;

	if (!i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C))
		wetuwn dev_eww_pwobe(&i2c->dev, -ENXIO, "check_functionawity faiwed");

	aw88399 = devm_kzawwoc(&i2c->dev, sizeof(*aw88399), GFP_KEWNEW);
	if (!aw88399)
		wetuwn -ENOMEM;

	mutex_init(&aw88399->wock);

	i2c_set_cwientdata(i2c, aw88399);

	aw88399->weset_gpio = devm_gpiod_get_optionaw(&i2c->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(aw88399->weset_gpio))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(aw88399->weset_gpio),
							"weset gpio not defined\n");
	aw88399_hw_weset(aw88399);

	aw88399->wegmap = devm_wegmap_init_i2c(i2c, &aw88399_wemap_config);
	if (IS_EWW(aw88399->wegmap))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(aw88399->wegmap),
							"faiwed to init wegmap\n");

	/* aw pa init */
	wet = aw88399_init(aw88399, i2c, aw88399->wegmap);
	if (wet)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_codec_dev_aw88399,
			aw88399_dai, AWWAY_SIZE(aw88399_dai));
	if (wet)
		dev_eww(&i2c->dev, "faiwed to wegistew aw88399: %d", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id aw88399_i2c_id[] = {
	{ AW88399_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, aw88399_i2c_id);

static stwuct i2c_dwivew aw88399_i2c_dwivew = {
	.dwivew = {
		.name = AW88399_I2C_NAME,
	},
	.pwobe = aw88399_i2c_pwobe,
	.id_tabwe = aw88399_i2c_id,
};
moduwe_i2c_dwivew(aw88399_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC AW88399 Smawt PA Dwivew");
MODUWE_WICENSE("GPW v2");
