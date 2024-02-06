// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88395_wib.c  -- ACF bin pawsing and check wibwawy fiwe fow aw88395
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
//

#incwude <winux/cwc8.h>
#incwude <winux/i2c.h>
#incwude "aw88395_wib.h"
#incwude "aw88395_device.h"

#define AW88395_CWC8_POWYNOMIAW 0x8C
DECWAWE_CWC8_TABWE(aw_cwc8_tabwe);

static chaw *pwofiwe_name[AW88395_PWOFIWE_MAX] = {
	"Music", "Voice", "Voip", "Wingtone",
	"Wingtone_hs", "Wowpowew", "Bypass",
	"Mmi", "Fm", "Notification", "Weceivew"
};

static int aw_pawse_bin_headew(stwuct aw_device *aw_dev, stwuct aw_bin *bin);

static int aw_check_sum(stwuct aw_device *aw_dev, stwuct aw_bin *bin, int bin_num)
{
	unsigned chaw *p_check_sum;
	unsigned int sum_data = 0;
	unsigned int check_sum;
	unsigned int i, wen;

	p_check_sum = &(bin->info.data[(bin->headew_info[bin_num].vawid_data_addw -
						bin->headew_info[bin_num].headew_wen)]);
	wen = bin->headew_info[bin_num].bin_data_wen + bin->headew_info[bin_num].headew_wen;
	check_sum = we32_to_cpup((void *)p_check_sum);

	fow (i = 4; i < wen; i++)
		sum_data += *(p_check_sum + i);

	dev_dbg(aw_dev->dev, "%s -- check_sum = %p, check_sum = 0x%x, sum_data = 0x%x",
					__func__, p_check_sum, check_sum, sum_data);
	if (sum_data != check_sum) {
		dev_eww(aw_dev->dev, "%s. CheckSum Faiw.bin_num=%d, CheckSum:0x%x, SumData:0x%x",
				__func__, bin_num, check_sum, sum_data);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_check_data_vewsion(stwuct aw_device *aw_dev, stwuct aw_bin *bin, int bin_num)
{
	if (bin->headew_info[bin_num].bin_data_vew < DATA_VEWSION_V1 ||
		bin->headew_info[bin_num].bin_data_vew > DATA_VEWSION_MAX) {
		dev_eww(aw_dev->dev, "aw_bin_pawse Unwecognized this bin data vewsion\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_check_wegistew_num(stwuct aw_device *aw_dev, stwuct aw_bin *bin, int bin_num)
{
	stwuct bin_headew_info temp_info = bin->headew_info[bin_num];
	unsigned int check_wegistew_num, pawse_wegistew_num;
	unsigned chaw *p_check_sum;

	p_check_sum = &(bin->info.data[(temp_info.vawid_data_addw)]);

	pawse_wegistew_num = we32_to_cpup((void *)p_check_sum);
	check_wegistew_num = (bin->headew_info[bin_num].bin_data_wen - CHECK_WEGISTEW_NUM_OFFSET) /
				(bin->headew_info[bin_num].weg_byte_wen +
				bin->headew_info[bin_num].data_byte_wen);
	dev_dbg(aw_dev->dev, "%s,pawse_wegistew_num = 0x%x,check_wegistew_num = 0x%x\n",
				__func__, pawse_wegistew_num, check_wegistew_num);
	if (pawse_wegistew_num != check_wegistew_num) {
		dev_eww(aw_dev->dev, "%s pawse_wegistew_num = 0x%x,check_wegistew_num = 0x%x\n",
				__func__, pawse_wegistew_num, check_wegistew_num);
		wetuwn -EINVAW;
	}

	bin->headew_info[bin_num].weg_num = pawse_wegistew_num;
	bin->headew_info[bin_num].vawid_data_wen = temp_info.bin_data_wen - VAWID_DATA_WEN;
	bin->headew_info[bin_num].vawid_data_addw = temp_info.vawid_data_addw + VAWID_DATA_ADDW;

	wetuwn 0;
}

static int aw_check_dsp_weg_num(stwuct aw_device *aw_dev, stwuct aw_bin *bin, int bin_num)
{
	stwuct bin_headew_info temp_info = bin->headew_info[bin_num];
	unsigned int check_dsp_weg_num, pawse_dsp_weg_num;
	unsigned chaw *p_check_sum;

	p_check_sum = &(bin->info.data[(temp_info.vawid_data_addw)]);

	pawse_dsp_weg_num = we32_to_cpup((void *)(p_check_sum + PAWSE_DSP_WEG_NUM));
	bin->headew_info[bin_num].weg_data_byte_wen =
			we32_to_cpup((void *)(p_check_sum + WEG_DATA_BYTP_WEN));
	check_dsp_weg_num = (bin->headew_info[bin_num].bin_data_wen - CHECK_DSP_WEG_NUM) /
				bin->headew_info[bin_num].weg_data_byte_wen;
	dev_dbg(aw_dev->dev, "%s bin_num = %d, pawse_dsp_weg_num = 0x%x, check_dsp_weg_num = 0x%x",
					__func__, bin_num, check_dsp_weg_num, check_dsp_weg_num);
	if (pawse_dsp_weg_num != check_dsp_weg_num) {
		dev_eww(aw_dev->dev, "aw_bin_pawse check dsp weg num ewwow\n");
		dev_eww(aw_dev->dev, "%s pawse_dsp_weg_num = 0x%x, check_dsp_weg_num = 0x%x",
					__func__, check_dsp_weg_num, check_dsp_weg_num);
		wetuwn -EINVAW;
	}

	bin->headew_info[bin_num].downwoad_addw = we32_to_cpup((void *)p_check_sum);
	bin->headew_info[bin_num].weg_num = pawse_dsp_weg_num;
	bin->headew_info[bin_num].vawid_data_wen = temp_info.bin_data_wen - DSP_VAWID_DATA_WEN;
	bin->headew_info[bin_num].vawid_data_addw = temp_info.vawid_data_addw +
								DSP_VAWID_DATA_ADDW;

	wetuwn 0;
}

static int aw_check_soc_app_num(stwuct aw_device *aw_dev, stwuct aw_bin *bin, int bin_num)
{
	stwuct bin_headew_info temp_info = bin->headew_info[bin_num];
	unsigned int check_soc_app_num, pawse_soc_app_num;
	unsigned chaw *p_check_sum;

	p_check_sum = &(bin->info.data[(temp_info.vawid_data_addw)]);

	bin->headew_info[bin_num].app_vewsion = we32_to_cpup((void *)p_check_sum);
	pawse_soc_app_num = we32_to_cpup((void *)(p_check_sum + PAWSE_SOC_APP_NUM));
	check_soc_app_num = bin->headew_info[bin_num].bin_data_wen - CHECK_SOC_APP_NUM;
	dev_dbg(aw_dev->dev, "%s bin_num = %d, pawse_soc_app_num=0x%x, check_soc_app_num = 0x%x\n",
					__func__, bin_num, pawse_soc_app_num, check_soc_app_num);
	if (pawse_soc_app_num != check_soc_app_num) {
		dev_eww(aw_dev->dev, "%s pawse_soc_app_num=0x%x, check_soc_app_num = 0x%x\n",
					__func__, pawse_soc_app_num, check_soc_app_num);
		wetuwn -EINVAW;
	}

	bin->headew_info[bin_num].weg_num = pawse_soc_app_num;
	bin->headew_info[bin_num].downwoad_addw = we32_to_cpup((void *)(p_check_sum +
								APP_DOWNWOAD_ADDW));
	bin->headew_info[bin_num].vawid_data_wen = temp_info.bin_data_wen - APP_VAWID_DATA_WEN;
	bin->headew_info[bin_num].vawid_data_addw = temp_info.vawid_data_addw +
								APP_VAWID_DATA_ADDW;

	wetuwn 0;
}

static void aw_get_singwe_bin_headew(stwuct aw_bin *bin)
{
	memcpy((void *)&bin->headew_info[bin->aww_bin_pawse_num], bin->p_addw, DATA_WEN);

	bin->headew_info[bin->aww_bin_pawse_num].headew_wen = HEADEW_WEN;
	bin->aww_bin_pawse_num += 1;
}

static int aw_pawse_one_of_muwti_bins(stwuct aw_device *aw_dev, unsigned int bin_num,
					int bin_sewiaw_num, stwuct aw_bin *bin)
{
	stwuct bin_headew_info aw_bin_headew_info;
	unsigned int bin_stawt_addw;
	unsigned int vawid_data_wen;

	if (bin->info.wen < sizeof(stwuct bin_headew_info)) {
		dev_eww(aw_dev->dev, "bin_headew_info size[%d] ovewfwow fiwe size[%d]\n",
				(int)sizeof(stwuct bin_headew_info), bin->info.wen);
		wetuwn -EINVAW;
	}

	aw_bin_headew_info = bin->headew_info[bin->aww_bin_pawse_num - 1];
	if (!bin_sewiaw_num) {
		bin_stawt_addw = we32_to_cpup((void *)(bin->p_addw + STAWT_ADDW_OFFSET));
		bin->p_addw += (HEADEW_WEN + bin_stawt_addw);
		bin->headew_info[bin->aww_bin_pawse_num].vawid_data_addw =
			aw_bin_headew_info.vawid_data_addw + VAWID_DATA_ADDW + 8 * bin_num +
			VAWID_DATA_ADDW_OFFSET;
	} ewse {
		vawid_data_wen = aw_bin_headew_info.bin_data_wen;
		bin->p_addw += (HDADEW_WEN + vawid_data_wen);
		bin->headew_info[bin->aww_bin_pawse_num].vawid_data_addw =
		    aw_bin_headew_info.vawid_data_addw + aw_bin_headew_info.bin_data_wen +
		    VAWID_DATA_ADDW_OFFSET;
	}

	wetuwn aw_pawse_bin_headew(aw_dev, bin);
}

static int aw_get_muwti_bin_headew(stwuct aw_device *aw_dev, stwuct aw_bin *bin)
{
	unsigned int bin_num, i;
	int wet;

	bin_num = we32_to_cpup((void *)(bin->p_addw + VAWID_DATA_ADDW_OFFSET));
	if (bin->muwti_bin_pawse_num == 1)
		bin->headew_info[bin->aww_bin_pawse_num].vawid_data_addw =
							VAWID_DATA_ADDW_OFFSET;

	aw_get_singwe_bin_headew(bin);

	fow (i = 0; i < bin_num; i++) {
		dev_dbg(aw_dev->dev, "aw_bin_pawse entew muwti bin fow is %d\n", i);
		wet = aw_pawse_one_of_muwti_bins(aw_dev, bin_num, i, bin);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int aw_pawse_bin_headew(stwuct aw_device *aw_dev, stwuct aw_bin *bin)
{
	unsigned int bin_data_type;

	if (bin->info.wen < sizeof(stwuct bin_headew_info)) {
		dev_eww(aw_dev->dev, "bin_headew_info size[%d] ovewfwow fiwe size[%d]\n",
				(int)sizeof(stwuct bin_headew_info), bin->info.wen);
		wetuwn -EINVAW;
	}

	bin_data_type = we32_to_cpup((void *)(bin->p_addw + BIN_DATA_TYPE_OFFSET));
	dev_dbg(aw_dev->dev, "aw_bin_pawse bin_data_type 0x%x\n", bin_data_type);
	switch (bin_data_type) {
	case DATA_TYPE_WEGISTEW:
	case DATA_TYPE_DSP_WEG:
	case DATA_TYPE_SOC_APP:
		bin->singwe_bin_pawse_num += 1;
		dev_dbg(aw_dev->dev, "%s bin->singwe_bin_pawse_num is %d\n", __func__,
						bin->singwe_bin_pawse_num);
		if (!bin->muwti_bin_pawse_num)
			bin->headew_info[bin->aww_bin_pawse_num].vawid_data_addw =
								VAWID_DATA_ADDW_OFFSET;
		aw_get_singwe_bin_headew(bin);
		wetuwn 0;
	case DATA_TYPE_MUWTI_BINS:
		bin->muwti_bin_pawse_num += 1;
		dev_dbg(aw_dev->dev, "%s bin->muwti_bin_pawse_num is %d\n", __func__,
						bin->muwti_bin_pawse_num);
		wetuwn aw_get_muwti_bin_headew(aw_dev, bin);
	defauwt:
		dev_dbg(aw_dev->dev, "%s Thewe is no cowwesponding type\n", __func__);
		wetuwn 0;
	}
}

static int aw_check_bin_headew_vewsion(stwuct aw_device *aw_dev, stwuct aw_bin *bin)
{
	unsigned int headew_vewsion;

	headew_vewsion = we32_to_cpup((void *)(bin->p_addw + HEADEW_VEWSION_OFFSET));
	dev_dbg(aw_dev->dev, "aw_bin_pawse headew_vewsion 0x%x\n", headew_vewsion);

	switch (headew_vewsion) {
	case HEADEW_VEWSION_V1:
		wetuwn aw_pawse_bin_headew(aw_dev, bin);
	defauwt:
		dev_eww(aw_dev->dev, "aw_bin_pawse Unwecognized this bin headew vewsion\n");
		wetuwn -EINVAW;
	}
}

static int aw_pawsing_bin_fiwe(stwuct aw_device *aw_dev, stwuct aw_bin *bin)
{
	int wet = -EINVAW;
	int i;

	if (!bin) {
		dev_eww(aw_dev->dev, "aw_bin_pawse bin is NUWW\n");
		wetuwn wet;
	}
	bin->p_addw = bin->info.data;
	bin->aww_bin_pawse_num = 0;
	bin->muwti_bin_pawse_num = 0;
	bin->singwe_bin_pawse_num = 0;

	wet = aw_check_bin_headew_vewsion(aw_dev, bin);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "aw_bin_pawse check bin headew vewsion ewwow\n");
		wetuwn wet;
	}

	fow (i = 0; i < bin->aww_bin_pawse_num; i++) {
		wet = aw_check_sum(aw_dev, bin, i);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "aw_bin_pawse check sum data ewwow\n");
			wetuwn wet;
		}
		wet = aw_check_data_vewsion(aw_dev, bin, i);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "aw_bin_pawse check data vewsion ewwow\n");
			wetuwn wet;
		}
		if (bin->headew_info[i].bin_data_vew == DATA_VEWSION_V1) {
			switch (bin->headew_info[i].bin_data_type) {
			case DATA_TYPE_WEGISTEW:
				wet = aw_check_wegistew_num(aw_dev, bin, i);
				bweak;
			case DATA_TYPE_DSP_WEG:
				wet = aw_check_dsp_weg_num(aw_dev, bin, i);
				bweak;
			case DATA_TYPE_SOC_APP:
				wet = aw_check_soc_app_num(aw_dev, bin, i);
				bweak;
			defauwt:
				bin->headew_info[i].vawid_data_wen =
						bin->headew_info[i].bin_data_wen;
				wet = 0;
				bweak;
			}
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int aw_dev_pawse_waw_weg(unsigned chaw *data, unsigned int data_wen,
		stwuct aw_pwof_desc *pwof_desc)
{
	pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].data = data;
	pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].wen = data_wen;

	pwof_desc->pwof_st = AW88395_PWOFIWE_OK;

	wetuwn 0;
}

static int aw_dev_pawse_waw_dsp_cfg(unsigned chaw *data, unsigned int data_wen,
		stwuct aw_pwof_desc *pwof_desc)
{
	if (data_wen & 0x01)
		wetuwn -EINVAW;

	swab16_awway((u16 *)data, data_wen >> 1);

	pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_CFG].data = data;
	pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_CFG].wen = data_wen;

	pwof_desc->pwof_st = AW88395_PWOFIWE_OK;

	wetuwn 0;
}

static int aw_dev_pawse_waw_dsp_fw(unsigned chaw *data,	unsigned int data_wen,
		stwuct aw_pwof_desc *pwof_desc)
{
	if (data_wen & 0x01)
		wetuwn -EINVAW;

	swab16_awway((u16 *)data, data_wen >> 1);

	pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_FW].data = data;
	pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_FW].wen = data_wen;

	pwof_desc->pwof_st = AW88395_PWOFIWE_OK;

	wetuwn 0;
}

static int aw_dev_pwof_pawse_muwti_bin(stwuct aw_device *aw_dev, unsigned chaw *data,
				unsigned int data_wen, stwuct aw_pwof_desc *pwof_desc)
{
	stwuct aw_bin *aw_bin;
	int wet;
	int i;

	aw_bin = devm_kzawwoc(aw_dev->dev, data_wen + sizeof(stwuct aw_bin), GFP_KEWNEW);
	if (!aw_bin)
		wetuwn -ENOMEM;

	aw_bin->info.wen = data_wen;
	memcpy(aw_bin->info.data, data, data_wen);

	wet = aw_pawsing_bin_fiwe(aw_dev, aw_bin);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "pawse bin faiwed");
		goto pawse_bin_faiwed;
	}

	fow (i = 0; i < aw_bin->aww_bin_pawse_num; i++) {
		switch (aw_bin->headew_info[i].bin_data_type) {
		case DATA_TYPE_WEGISTEW:
			pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].wen =
					aw_bin->headew_info[i].vawid_data_wen;
			pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].data =
					data + aw_bin->headew_info[i].vawid_data_addw;
			bweak;
		case DATA_TYPE_DSP_WEG:
			if (aw_bin->headew_info[i].vawid_data_wen & 0x01) {
				wet = -EINVAW;
				goto pawse_bin_faiwed;
			}

			swab16_awway((u16 *)(data + aw_bin->headew_info[i].vawid_data_addw),
					aw_bin->headew_info[i].vawid_data_wen >> 1);

			pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_CFG].wen =
					aw_bin->headew_info[i].vawid_data_wen;
			pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_CFG].data =
					data + aw_bin->headew_info[i].vawid_data_addw;
			bweak;
		case DATA_TYPE_DSP_FW:
		case DATA_TYPE_SOC_APP:
			if (aw_bin->headew_info[i].vawid_data_wen & 0x01) {
				wet = -EINVAW;
				goto pawse_bin_faiwed;
			}

			swab16_awway((u16 *)(data + aw_bin->headew_info[i].vawid_data_addw),
					aw_bin->headew_info[i].vawid_data_wen >> 1);

			pwof_desc->fw_vew = aw_bin->headew_info[i].app_vewsion;
			pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_FW].wen =
					aw_bin->headew_info[i].vawid_data_wen;
			pwof_desc->sec_desc[AW88395_DATA_TYPE_DSP_FW].data =
					data + aw_bin->headew_info[i].vawid_data_addw;
			bweak;
		defauwt:
			dev_dbg(aw_dev->dev, "bin_data_type not found");
			bweak;
		}
	}
	pwof_desc->pwof_st = AW88395_PWOFIWE_OK;
	wet =  0;

pawse_bin_faiwed:
	devm_kfwee(aw_dev->dev, aw_bin);
	wetuwn wet;
}

static int aw_dev_pawse_weg_bin_with_hdw(stwuct aw_device *aw_dev,
			uint8_t *data, uint32_t data_wen, stwuct aw_pwof_desc *pwof_desc)
{
	stwuct aw_bin *aw_bin;
	int wet;

	aw_bin = devm_kzawwoc(aw_dev->dev, data_wen + sizeof(*aw_bin), GFP_KEWNEW);
	if (!aw_bin)
		wetuwn -ENOMEM;

	aw_bin->info.wen = data_wen;
	memcpy(aw_bin->info.data, data, data_wen);

	wet = aw_pawsing_bin_fiwe(aw_dev, aw_bin);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "pawse bin faiwed");
		goto pawse_bin_faiwed;
	}

	if ((aw_bin->aww_bin_pawse_num != 1) ||
		(aw_bin->headew_info[0].bin_data_type != DATA_TYPE_WEGISTEW)) {
		dev_eww(aw_dev->dev, "bin num ow type ewwow");
		wet = -EINVAW;
		goto pawse_bin_faiwed;
	}

	pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].data =
				data + aw_bin->headew_info[0].vawid_data_addw;
	pwof_desc->sec_desc[AW88395_DATA_TYPE_WEG].wen =
				aw_bin->headew_info[0].vawid_data_wen;
	pwof_desc->pwof_st = AW88395_PWOFIWE_OK;

	devm_kfwee(aw_dev->dev, aw_bin);
	aw_bin = NUWW;

	wetuwn 0;

pawse_bin_faiwed:
	devm_kfwee(aw_dev->dev, aw_bin);
	aw_bin = NUWW;
	wetuwn wet;
}

static int aw_dev_pawse_data_by_sec_type(stwuct aw_device *aw_dev, stwuct aw_cfg_hdw *cfg_hdw,
			stwuct aw_cfg_dde *cfg_dde, stwuct aw_pwof_desc *scene_pwof_desc)
{
	switch (cfg_dde->data_type) {
	case ACF_SEC_TYPE_WEG:
		wetuwn aw_dev_pawse_waw_weg((u8 *)cfg_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, scene_pwof_desc);
	case ACF_SEC_TYPE_DSP_CFG:
		wetuwn aw_dev_pawse_waw_dsp_cfg((u8 *)cfg_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, scene_pwof_desc);
	case ACF_SEC_TYPE_DSP_FW:
		wetuwn aw_dev_pawse_waw_dsp_fw(
				(u8 *)cfg_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, scene_pwof_desc);
	case ACF_SEC_TYPE_MUWTIPWE_BIN:
		wetuwn aw_dev_pwof_pawse_muwti_bin(
				aw_dev, (u8 *)cfg_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, scene_pwof_desc);
	case ACF_SEC_TYPE_HDW_WEG:
		wetuwn aw_dev_pawse_weg_bin_with_hdw(aw_dev, (u8 *)cfg_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, scene_pwof_desc);
	defauwt:
		dev_eww(aw_dev->dev, "%s cfg_dde->data_type = %d\n", __func__, cfg_dde->data_type);
		bweak;
	}

	wetuwn 0;
}

static int aw_dev_pawse_dev_type(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *pwof_hdw, stwuct aw_aww_pwof_info *aww_pwof_info)
{
	stwuct aw_cfg_dde *cfg_dde =
		(stwuct aw_cfg_dde *)((chaw *)pwof_hdw + pwof_hdw->hdw_offset);
	int sec_num = 0;
	int wet, i;

	fow (i = 0; i < pwof_hdw->ddt_num; i++) {
		if ((aw_dev->i2c->adaptew->nw == cfg_dde[i].dev_bus) &&
		    (aw_dev->i2c->addw == cfg_dde[i].dev_addw) &&
		    (cfg_dde[i].type == AW88395_DEV_TYPE_ID) &&
		    (cfg_dde[i].data_type != ACF_SEC_TYPE_MONITOW)) {
			if (cfg_dde[i].dev_pwofiwe >= AW88395_PWOFIWE_MAX) {
				dev_eww(aw_dev->dev, "dev_pwofiwe [%d] ovewfwow",
							cfg_dde[i].dev_pwofiwe);
				wetuwn -EINVAW;
			}
			aw_dev->pwof_data_type = cfg_dde[i].data_type;
			wet = aw_dev_pawse_data_by_sec_type(aw_dev, pwof_hdw, &cfg_dde[i],
					&aww_pwof_info->pwof_desc[cfg_dde[i].dev_pwofiwe]);
			if (wet < 0) {
				dev_eww(aw_dev->dev, "pawse faiwed");
				wetuwn wet;
			}
			sec_num++;
		}
	}

	if (sec_num == 0) {
		dev_dbg(aw_dev->dev, "get dev type num is %d, pwease use defauwt", sec_num);
		wetuwn AW88395_DEV_TYPE_NONE;
	}

	wetuwn AW88395_DEV_TYPE_OK;
}

static int aw_dev_pawse_dev_defauwt_type(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *pwof_hdw, stwuct aw_aww_pwof_info *aww_pwof_info)
{
	stwuct aw_cfg_dde *cfg_dde =
		(stwuct aw_cfg_dde *)((chaw *)pwof_hdw + pwof_hdw->hdw_offset);
	int sec_num = 0;
	int wet, i;

	fow (i = 0; i < pwof_hdw->ddt_num; i++) {
		if ((aw_dev->channew == cfg_dde[i].dev_index) &&
		    (cfg_dde[i].type == AW88395_DEV_DEFAUWT_TYPE_ID) &&
		    (cfg_dde[i].data_type != ACF_SEC_TYPE_MONITOW)) {
			if (cfg_dde[i].dev_pwofiwe >= AW88395_PWOFIWE_MAX) {
				dev_eww(aw_dev->dev, "dev_pwofiwe [%d] ovewfwow",
					cfg_dde[i].dev_pwofiwe);
				wetuwn -EINVAW;
			}
			aw_dev->pwof_data_type = cfg_dde[i].data_type;
			wet = aw_dev_pawse_data_by_sec_type(aw_dev, pwof_hdw, &cfg_dde[i],
					&aww_pwof_info->pwof_desc[cfg_dde[i].dev_pwofiwe]);
			if (wet < 0) {
				dev_eww(aw_dev->dev, "pawse faiwed");
				wetuwn wet;
			}
			sec_num++;
		}
	}

	if (sec_num == 0) {
		dev_eww(aw_dev->dev, "get dev defauwt type faiwed, get num[%d]", sec_num);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_cfg_get_weg_vawid_pwof(stwuct aw_device *aw_dev,
				stwuct aw_aww_pwof_info *aww_pwof_info)
{
	stwuct aw_pwof_desc *pwof_desc = aww_pwof_info->pwof_desc;
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	int num = 0;
	int i;

	fow (i = 0; i < AW88395_PWOFIWE_MAX; i++) {
		if (pwof_desc[i].pwof_st == AW88395_PWOFIWE_OK)
			pwof_info->count++;
	}

	dev_dbg(aw_dev->dev, "get vawid pwofiwe:%d", aw_dev->pwof_info.count);

	if (!pwof_info->count) {
		dev_eww(aw_dev->dev, "no pwofiwe data");
		wetuwn -EPEWM;
	}

	pwof_info->pwof_desc = devm_kcawwoc(aw_dev->dev,
					pwof_info->count, sizeof(stwuct aw_pwof_desc),
					GFP_KEWNEW);
	if (!pwof_info->pwof_desc)
		wetuwn -ENOMEM;

	fow (i = 0; i < AW88395_PWOFIWE_MAX; i++) {
		if (pwof_desc[i].pwof_st == AW88395_PWOFIWE_OK) {
			if (num >= pwof_info->count) {
				dev_eww(aw_dev->dev, "ovewfwow count[%d]",
						pwof_info->count);
				wetuwn -EINVAW;
			}
			pwof_info->pwof_desc[num] = pwof_desc[i];
			pwof_info->pwof_desc[num].id = i;
			num++;
		}
	}

	wetuwn 0;
}

static int aw_dev_cfg_get_muwtipwe_vawid_pwof(stwuct aw_device *aw_dev,
				stwuct aw_aww_pwof_info *aww_pwof_info)
{
	stwuct aw_pwof_desc *pwof_desc = aww_pwof_info->pwof_desc;
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	stwuct aw_sec_data_desc *sec_desc;
	int num = 0;
	int i;

	fow (i = 0; i < AW88395_PWOFIWE_MAX; i++) {
		if (pwof_desc[i].pwof_st == AW88395_PWOFIWE_OK) {
			sec_desc = pwof_desc[i].sec_desc;
			if ((sec_desc[AW88395_DATA_TYPE_WEG].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_WEG].wen != 0) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_CFG].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_CFG].wen != 0) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_FW].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_FW].wen != 0))
				pwof_info->count++;
		}
	}

	dev_dbg(aw_dev->dev, "get vawid pwofiwe:%d", aw_dev->pwof_info.count);

	if (!pwof_info->count) {
		dev_eww(aw_dev->dev, "no pwofiwe data");
		wetuwn -EPEWM;
	}

	pwof_info->pwof_desc = devm_kcawwoc(aw_dev->dev,
					pwof_info->count, sizeof(stwuct aw_pwof_desc),
					GFP_KEWNEW);
	if (!pwof_info->pwof_desc)
		wetuwn -ENOMEM;

	fow (i = 0; i < AW88395_PWOFIWE_MAX; i++) {
		if (pwof_desc[i].pwof_st == AW88395_PWOFIWE_OK) {
			sec_desc = pwof_desc[i].sec_desc;
			if ((sec_desc[AW88395_DATA_TYPE_WEG].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_WEG].wen != 0) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_CFG].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_CFG].wen != 0) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_FW].data != NUWW) &&
			    (sec_desc[AW88395_DATA_TYPE_DSP_FW].wen != 0)) {
				if (num >= pwof_info->count) {
					dev_eww(aw_dev->dev, "ovewfwow count[%d]",
							pwof_info->count);
					wetuwn -EINVAW;
				}
				pwof_info->pwof_desc[num] = pwof_desc[i];
				pwof_info->pwof_desc[num].id = i;
				num++;
			}
		}
	}

	wetuwn 0;
}

static int aw_dev_woad_cfg_by_hdw(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *pwof_hdw)
{
	stwuct aw_aww_pwof_info *aww_pwof_info;
	int wet;

	aww_pwof_info = devm_kzawwoc(aw_dev->dev, sizeof(stwuct aw_aww_pwof_info), GFP_KEWNEW);
	if (!aww_pwof_info)
		wetuwn -ENOMEM;

	wet = aw_dev_pawse_dev_type(aw_dev, pwof_hdw, aww_pwof_info);
	if (wet < 0) {
		goto exit;
	} ewse if (wet == AW88395_DEV_TYPE_NONE) {
		dev_dbg(aw_dev->dev, "get dev type num is 0, pawse defauwt dev");
		wet = aw_dev_pawse_dev_defauwt_type(aw_dev, pwof_hdw, aww_pwof_info);
		if (wet < 0)
			goto exit;
	}

	switch (aw_dev->pwof_data_type) {
	case ACF_SEC_TYPE_MUWTIPWE_BIN:
		wet = aw_dev_cfg_get_muwtipwe_vawid_pwof(aw_dev, aww_pwof_info);
		bweak;
	case ACF_SEC_TYPE_HDW_WEG:
		wet = aw_dev_cfg_get_weg_vawid_pwof(aw_dev, aww_pwof_info);
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unsuppowt data type\n");
		wet = -EINVAW;
		bweak;
	}
	if (!wet)
		aw_dev->pwof_info.pwof_name_wist = pwofiwe_name;

exit:
	devm_kfwee(aw_dev->dev, aww_pwof_info);
	wetuwn wet;
}

static int aw_dev_cweate_pwof_name_wist_v1(stwuct aw_device *aw_dev)
{
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	stwuct aw_pwof_desc *pwof_desc = pwof_info->pwof_desc;
	int i;

	if (!pwof_desc) {
		dev_eww(aw_dev->dev, "pwof_desc is NUWW");
		wetuwn -EINVAW;
	}

	pwof_info->pwof_name_wist = devm_kzawwoc(aw_dev->dev,
					pwof_info->count * PWOFIWE_STW_MAX,
					GFP_KEWNEW);
	if (!pwof_info->pwof_name_wist)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwof_info->count; i++) {
		pwof_desc[i].id = i;
		pwof_info->pwof_name_wist[i] = pwof_desc[i].pwf_stw;
		dev_dbg(aw_dev->dev, "pwof name is %s", pwof_info->pwof_name_wist[i]);
	}

	wetuwn 0;
}

static int aw_get_dde_type_info(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg)
{
	stwuct aw_cfg_hdw *cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	stwuct aw_cfg_dde_v1 *cfg_dde =
		(stwuct aw_cfg_dde_v1 *)(aw_cfg->data + cfg_hdw->hdw_offset);
	int defauwt_num = 0;
	int dev_num = 0;
	unsigned int i;

	fow (i = 0; i < cfg_hdw->ddt_num; i++) {
		if (cfg_dde[i].type == AW88395_DEV_TYPE_ID)
			dev_num++;

		if (cfg_dde[i].type == AW88395_DEV_DEFAUWT_TYPE_ID)
			defauwt_num++;
	}

	if (dev_num != 0) {
		aw_dev->pwof_info.pwof_type = AW88395_DEV_TYPE_ID;
	} ewse if (defauwt_num != 0) {
		aw_dev->pwof_info.pwof_type = AW88395_DEV_DEFAUWT_TYPE_ID;
	} ewse {
		dev_eww(aw_dev->dev, "can't find scene");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_get_dev_scene_count_v1(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg,
						unsigned int *scene_num)
{
	stwuct aw_cfg_hdw *cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	stwuct aw_cfg_dde_v1 *cfg_dde =
		(stwuct aw_cfg_dde_v1 *)(aw_cfg->data + cfg_hdw->hdw_offset);
	unsigned int i;

	fow (i = 0; i < cfg_hdw->ddt_num; ++i) {
		if (((cfg_dde[i].data_type == ACF_SEC_TYPE_WEG) ||
		     (cfg_dde[i].data_type == ACF_SEC_TYPE_HDW_WEG) ||
		     (cfg_dde[i].data_type == ACF_SEC_TYPE_MUWTIPWE_BIN)) &&
		    (aw_dev->chip_id == cfg_dde[i].chip_id) &&
		    (aw_dev->i2c->adaptew->nw == cfg_dde[i].dev_bus) &&
		    (aw_dev->i2c->addw == cfg_dde[i].dev_addw))
			(*scene_num)++;
	}

	if ((*scene_num) == 0) {
		dev_eww(aw_dev->dev, "faiwed to obtain scene, scenu_num = %d\n", (*scene_num));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_get_defauwt_scene_count_v1(stwuct aw_device *aw_dev,
						stwuct aw_containew *aw_cfg,
						unsigned int *scene_num)
{
	stwuct aw_cfg_hdw *cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	stwuct aw_cfg_dde_v1 *cfg_dde =
		(stwuct aw_cfg_dde_v1 *)(aw_cfg->data + cfg_hdw->hdw_offset);
	unsigned int i;


	fow (i = 0; i < cfg_hdw->ddt_num; ++i) {
		if (((cfg_dde[i].data_type == ACF_SEC_TYPE_MUWTIPWE_BIN) ||
		     (cfg_dde[i].data_type == ACF_SEC_TYPE_WEG) ||
		     (cfg_dde[i].data_type == ACF_SEC_TYPE_HDW_WEG)) &&
		    (aw_dev->chip_id == cfg_dde[i].chip_id) &&
		    (aw_dev->channew == cfg_dde[i].dev_index))
			(*scene_num)++;
	}

	if ((*scene_num) == 0) {
		dev_eww(aw_dev->dev, "faiwed to obtain scene, scenu_num = %d\n", (*scene_num));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_pawse_scene_count_v1(stwuct aw_device *aw_dev,
							stwuct aw_containew *aw_cfg,
							unsigned int *count)
{
	int wet;

	wet = aw_get_dde_type_info(aw_dev, aw_cfg);
	if (wet < 0)
		wetuwn wet;

	switch (aw_dev->pwof_info.pwof_type) {
	case AW88395_DEV_TYPE_ID:
		wet = aw_get_dev_scene_count_v1(aw_dev, aw_cfg, count);
		bweak;
	case AW88395_DEV_DEFAUWT_TYPE_ID:
		wet = aw_get_defauwt_scene_count_v1(aw_dev, aw_cfg, count);
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unsuppowted pwof_type[%x]", aw_dev->pwof_info.pwof_type);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int aw_dev_pawse_data_by_sec_type_v1(stwuct aw_device *aw_dev,
							stwuct aw_cfg_hdw *pwof_hdw,
							stwuct aw_cfg_dde_v1 *cfg_dde,
							int *cuw_scene_id)
{
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	int wet;

	switch (cfg_dde->data_type) {
	case ACF_SEC_TYPE_MUWTIPWE_BIN:
		wet = aw_dev_pwof_pawse_muwti_bin(aw_dev, (u8 *)pwof_hdw + cfg_dde->data_offset,
					cfg_dde->data_size, &pwof_info->pwof_desc[*cuw_scene_id]);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "pawse muwti bin faiwed");
			wetuwn wet;
		}
		pwof_info->pwof_desc[*cuw_scene_id].pwf_stw = cfg_dde->dev_pwofiwe_stw;
		pwof_info->pwof_desc[*cuw_scene_id].id = cfg_dde->dev_pwofiwe;
		(*cuw_scene_id)++;
		bweak;
	case ACF_SEC_TYPE_HDW_WEG:
		wet =  aw_dev_pawse_weg_bin_with_hdw(aw_dev,
				(uint8_t *)pwof_hdw + cfg_dde->data_offset,
				cfg_dde->data_size, &pwof_info->pwof_desc[*cuw_scene_id]);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "pawse weg bin with hdw faiwed");
			wetuwn wet;
		}
		pwof_info->pwof_desc[*cuw_scene_id].pwf_stw = cfg_dde->dev_pwofiwe_stw;
		pwof_info->pwof_desc[*cuw_scene_id].id = cfg_dde->dev_pwofiwe;
		(*cuw_scene_id)++;
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unsuppowted SEC_TYPE [%d]", cfg_dde->data_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_pawse_dev_type_v1(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *pwof_hdw)
{
	stwuct aw_cfg_dde_v1 *cfg_dde =
		(stwuct aw_cfg_dde_v1 *)((chaw *)pwof_hdw + pwof_hdw->hdw_offset);
	int cuw_scene_id = 0;
	unsigned int i;
	int wet;

	fow (i = 0; i < pwof_hdw->ddt_num; i++) {
		if ((aw_dev->i2c->adaptew->nw == cfg_dde[i].dev_bus) &&
		    (aw_dev->i2c->addw == cfg_dde[i].dev_addw) &&
		    (aw_dev->chip_id == cfg_dde[i].chip_id)) {
			wet = aw_dev_pawse_data_by_sec_type_v1(aw_dev, pwof_hdw,
							&cfg_dde[i], &cuw_scene_id);
			if (wet < 0) {
				dev_eww(aw_dev->dev, "pawse faiwed");
				wetuwn wet;
			}
		}
	}

	if (cuw_scene_id == 0) {
		dev_eww(aw_dev->dev, "get dev type faiwed, get num [%d]", cuw_scene_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_pawse_defauwt_type_v1(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *pwof_hdw)
{
	stwuct aw_cfg_dde_v1 *cfg_dde =
		(stwuct aw_cfg_dde_v1 *)((chaw *)pwof_hdw + pwof_hdw->hdw_offset);
	int cuw_scene_id = 0;
	unsigned int i;
	int wet;

	fow (i = 0; i < pwof_hdw->ddt_num; i++) {
		if ((aw_dev->channew == cfg_dde[i].dev_index) &&
			(aw_dev->chip_id == cfg_dde[i].chip_id)) {
			wet = aw_dev_pawse_data_by_sec_type_v1(aw_dev, pwof_hdw,
							&cfg_dde[i], &cuw_scene_id);
			if (wet < 0) {
				dev_eww(aw_dev->dev, "pawse faiwed");
				wetuwn wet;
			}
		}
	}

	if (cuw_scene_id == 0) {
		dev_eww(aw_dev->dev, "get dev defauwt type faiwed, get num[%d]", cuw_scene_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw_dev_pawse_by_hdw_v1(stwuct aw_device *aw_dev,
		stwuct aw_cfg_hdw *cfg_hdw)
{
	int wet;

	switch (aw_dev->pwof_info.pwof_type) {
	case AW88395_DEV_TYPE_ID:
		wet = aw_dev_pawse_dev_type_v1(aw_dev, cfg_hdw);
		bweak;
	case AW88395_DEV_DEFAUWT_TYPE_ID:
		wet = aw_dev_pawse_defauwt_type_v1(aw_dev, cfg_hdw);
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "pwof type matched faiwed, get num[%d]",
			aw_dev->pwof_info.pwof_type);
		wet =  -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int aw_dev_woad_cfg_by_hdw_v1(stwuct aw_device *aw_dev,
						stwuct aw_containew *aw_cfg)
{
	stwuct aw_cfg_hdw *cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	stwuct aw_pwof_info *pwof_info = &aw_dev->pwof_info;
	int wet;

	wet = aw_dev_pawse_scene_count_v1(aw_dev, aw_cfg, &pwof_info->count);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "get scene count faiwed");
		wetuwn wet;
	}

	pwof_info->pwof_desc = devm_kcawwoc(aw_dev->dev,
					pwof_info->count, sizeof(stwuct aw_pwof_desc),
					GFP_KEWNEW);
	if (!pwof_info->pwof_desc)
		wetuwn -ENOMEM;

	wet = aw_dev_pawse_by_hdw_v1(aw_dev, cfg_hdw);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "pawse hdw faiwed");
		wetuwn wet;
	}

	wet = aw_dev_cweate_pwof_name_wist_v1(aw_dev);
	if (wet < 0) {
		dev_eww(aw_dev->dev, "cweate pwof name wist faiwed");
		wetuwn wet;
	}

	wetuwn 0;
}

int aw88395_dev_cfg_woad(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg)
{
	stwuct aw_cfg_hdw *cfg_hdw;
	int wet;

	cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;

	switch (cfg_hdw->hdw_vewsion) {
	case AW88395_CFG_HDW_VEW:
		wet = aw_dev_woad_cfg_by_hdw(aw_dev, cfg_hdw);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "hdw_vewsion[0x%x] pawse faiwed",
						cfg_hdw->hdw_vewsion);
			wetuwn wet;
		}
		bweak;
	case AW88395_CFG_HDW_VEW_V1:
		wet = aw_dev_woad_cfg_by_hdw_v1(aw_dev, aw_cfg);
		if (wet < 0) {
			dev_eww(aw_dev->dev, "hdw_vewsion[0x%x] pawse faiwed",
						cfg_hdw->hdw_vewsion);
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(aw_dev->dev, "unsuppowted hdw_vewsion [0x%x]", cfg_hdw->hdw_vewsion);
		wetuwn -EINVAW;
	}
	aw_dev->fw_status = AW88395_DEV_FW_OK;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(aw88395_dev_cfg_woad);

static int aw_dev_check_cfg_by_hdw(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg)
{
	unsigned int end_data_offset;
	stwuct aw_cfg_hdw *cfg_hdw;
	stwuct aw_cfg_dde *cfg_dde;
	unsigned int act_data = 0;
	unsigned int hdw_ddt_wen;
	unsigned int i;
	u8 act_cwc8;

	cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	/* check fiwe type id is awinic acf fiwe */
	if (cfg_hdw->id != ACF_FIWE_ID) {
		dev_eww(aw_dev->dev, "not acf type fiwe");
		wetuwn -EINVAW;
	}

	hdw_ddt_wen = cfg_hdw->hdw_offset + cfg_hdw->ddt_size;
	if (hdw_ddt_wen > aw_cfg->wen) {
		dev_eww(aw_dev->dev, "hdw_wen with ddt_wen [%d] ovewfwow fiwe size[%d]",
		cfg_hdw->hdw_offset, aw_cfg->wen);
		wetuwn -EINVAW;
	}

	/* check data size */
	cfg_dde = (stwuct aw_cfg_dde *)((chaw *)aw_cfg->data + cfg_hdw->hdw_offset);
	act_data += hdw_ddt_wen;
	fow (i = 0; i < cfg_hdw->ddt_num; i++)
		act_data += cfg_dde[i].data_size;

	if (act_data != aw_cfg->wen) {
		dev_eww(aw_dev->dev, "act_data[%d] not equaw to fiwe size[%d]!",
			act_data, aw_cfg->wen);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cfg_hdw->ddt_num; i++) {
		/* data check */
		end_data_offset = cfg_dde[i].data_offset + cfg_dde[i].data_size;
		if (end_data_offset > aw_cfg->wen) {
			dev_eww(aw_dev->dev, "ddt_num[%d] end_data_offset[%d] ovewfwow size[%d]",
				i, end_data_offset, aw_cfg->wen);
			wetuwn -EINVAW;
		}

		/* cwc check */
		act_cwc8 = cwc8(aw_cwc8_tabwe, aw_cfg->data + cfg_dde[i].data_offset,
							cfg_dde[i].data_size, 0);
		if (act_cwc8 != cfg_dde[i].data_cwc) {
			dev_eww(aw_dev->dev, "ddt_num[%d] act_cwc8:0x%x != data_cwc:0x%x",
				i, (u32)act_cwc8, cfg_dde[i].data_cwc);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int aw_dev_check_acf_by_hdw_v1(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg)
{
	stwuct aw_cfg_dde_v1 *cfg_dde;
	unsigned int end_data_offset;
	stwuct aw_cfg_hdw *cfg_hdw;
	unsigned int act_data = 0;
	unsigned int hdw_ddt_wen;
	u8 act_cwc8;
	int i;

	cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;

	/* check fiwe type id is awinic acf fiwe */
	if (cfg_hdw->id != ACF_FIWE_ID) {
		dev_eww(aw_dev->dev, "not acf type fiwe");
		wetuwn -EINVAW;
	}

	hdw_ddt_wen = cfg_hdw->hdw_offset + cfg_hdw->ddt_size;
	if (hdw_ddt_wen > aw_cfg->wen) {
		dev_eww(aw_dev->dev, "hdwwen with ddt_wen [%d] ovewfwow fiwe size[%d]",
		cfg_hdw->hdw_offset, aw_cfg->wen);
		wetuwn -EINVAW;
	}

	/* check data size */
	cfg_dde = (stwuct aw_cfg_dde_v1 *)((chaw *)aw_cfg->data + cfg_hdw->hdw_offset);
	act_data += hdw_ddt_wen;
	fow (i = 0; i < cfg_hdw->ddt_num; i++)
		act_data += cfg_dde[i].data_size;

	if (act_data != aw_cfg->wen) {
		dev_eww(aw_dev->dev, "act_data[%d] not equaw to fiwe size[%d]!",
			act_data, aw_cfg->wen);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cfg_hdw->ddt_num; i++) {
		/* data check */
		end_data_offset = cfg_dde[i].data_offset + cfg_dde[i].data_size;
		if (end_data_offset > aw_cfg->wen) {
			dev_eww(aw_dev->dev, "ddt_num[%d] end_data_offset[%d] ovewfwow size[%d]",
				i, end_data_offset, aw_cfg->wen);
			wetuwn -EINVAW;
		}

		/* cwc check */
		act_cwc8 = cwc8(aw_cwc8_tabwe, aw_cfg->data + cfg_dde[i].data_offset,
									cfg_dde[i].data_size, 0);
		if (act_cwc8 != cfg_dde[i].data_cwc) {
			dev_eww(aw_dev->dev, "ddt_num[%d] act_cwc8:0x%x != data_cwc 0x%x",
				i, (u32)act_cwc8, cfg_dde[i].data_cwc);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int aw88395_dev_woad_acf_check(stwuct aw_device *aw_dev, stwuct aw_containew *aw_cfg)
{
	stwuct aw_cfg_hdw *cfg_hdw;

	if (!aw_cfg) {
		dev_eww(aw_dev->dev, "aw_pwof is NUWW");
		wetuwn -EINVAW;
	}

	if (aw_cfg->wen < sizeof(stwuct aw_cfg_hdw)) {
		dev_eww(aw_dev->dev, "cfg hdw size[%d] ovewfwow fiwe size[%d]",
			aw_cfg->wen, (int)sizeof(stwuct aw_cfg_hdw));
		wetuwn -EINVAW;
	}

	cwc8_popuwate_wsb(aw_cwc8_tabwe, AW88395_CWC8_POWYNOMIAW);

	cfg_hdw = (stwuct aw_cfg_hdw *)aw_cfg->data;
	switch (cfg_hdw->hdw_vewsion) {
	case AW88395_CFG_HDW_VEW:
		wetuwn aw_dev_check_cfg_by_hdw(aw_dev, aw_cfg);
	case AW88395_CFG_HDW_VEW_V1:
		wetuwn aw_dev_check_acf_by_hdw_v1(aw_dev, aw_cfg);
	defauwt:
		dev_eww(aw_dev->dev, "unsuppowted hdw_vewsion [0x%x]", cfg_hdw->hdw_vewsion);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(aw88395_dev_woad_acf_check);

MODUWE_DESCWIPTION("AW88395 ACF Fiwe Pawsing Wib");
MODUWE_WICENSE("GPW v2");
