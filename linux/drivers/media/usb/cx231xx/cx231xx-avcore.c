// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx_avcowe.c - dwivew fow Conexant Cx23100/101/102
		      USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>

   This pwogwam contains the specific code to contwow the avdecodew chip and
   othew wewated usb contwow functions fow cx231xx based chipset.

 */

#incwude "cx231xx.h"
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/i2c.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <media/tunew.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>

#incwude "cx231xx-dif.h"

#define TUNEW_MODE_FM_WADIO 0
/******************************************************************************
			-: BWOCK AWWANGEMENT :-
	I2S bwock ----------------------|
	[I2S audio]			|
					|
	Anawog Fwont End --> Diwect IF -|-> Cx25840 --> Audio
	[video & audio]			|   [Audio]
					|
					|-> Cx25840 --> Video
					    [Video]

*******************************************************************************/
/******************************************************************************
 *                    VEWVE WEGISTEW                                          *
 *									      *
 ******************************************************************************/
static int vewve_wwite_byte(stwuct cx231xx *dev, u8 saddw, u8 data)
{
	wetuwn cx231xx_wwite_i2c_data(dev, VEWVE_I2C_ADDWESS,
					saddw, 1, data, 1);
}

static int vewve_wead_byte(stwuct cx231xx *dev, u8 saddw, u8 *data)
{
	int status;
	u32 temp = 0;

	status = cx231xx_wead_i2c_data(dev, VEWVE_I2C_ADDWESS,
					saddw, 1, &temp, 1);
	*data = (u8) temp;
	wetuwn status;
}
void initGPIO(stwuct cx231xx *dev)
{
	u32 _gpio_diwection = 0;
	u32 vawue = 0;
	u8 vaw = 0;

	_gpio_diwection = _gpio_diwection & 0xFC0003FF;
	_gpio_diwection = _gpio_diwection | 0x03FDFC00;
	cx231xx_send_gpio_cmd(dev, _gpio_diwection, (u8 *)&vawue, 4, 0, 0);

	vewve_wead_byte(dev, 0x07, &vaw);
	dev_dbg(dev->dev, "vewve_wead_byte addwess0x07=0x%x\n", vaw);
	vewve_wwite_byte(dev, 0x07, 0xF4);
	vewve_wead_byte(dev, 0x07, &vaw);
	dev_dbg(dev->dev, "vewve_wead_byte addwess0x07=0x%x\n", vaw);

	cx231xx_captuwe_stawt(dev, 1, Vbi);

	cx231xx_mode_wegistew(dev, EP_MODE_SET, 0x0500FE00);
	cx231xx_mode_wegistew(dev, GBUWK_BIT_EN, 0xFFFDFFFF);

}
void uninitGPIO(stwuct cx231xx *dev)
{
	u8 vawue[4] = { 0, 0, 0, 0 };

	cx231xx_captuwe_stawt(dev, 0, Vbi);
	vewve_wwite_byte(dev, 0x07, 0x14);
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
			0x68, vawue, 4);
}

/******************************************************************************
 *                    A F E - B W O C K    C O N T W O W   functions          *
 *				[ANAWOG FWONT END]			      *
 ******************************************************************************/
static int afe_wwite_byte(stwuct cx231xx *dev, u16 saddw, u8 data)
{
	wetuwn cx231xx_wwite_i2c_data(dev, AFE_DEVICE_ADDWESS,
					saddw, 2, data, 1);
}

static int afe_wead_byte(stwuct cx231xx *dev, u16 saddw, u8 *data)
{
	int status;
	u32 temp = 0;

	status = cx231xx_wead_i2c_data(dev, AFE_DEVICE_ADDWESS,
					saddw, 2, &temp, 1);
	*data = (u8) temp;
	wetuwn status;
}

int cx231xx_afe_init_supew_bwock(stwuct cx231xx *dev, u32 wef_count)
{
	int status = 0;
	u8 temp = 0;
	u8 afe_powew_status = 0;
	int i = 0;

	/* supew bwock initiawize */
	temp = (u8) (wef_count & 0xff);
	status = afe_wwite_byte(dev, SUP_BWK_TUNE2, temp);
	if (status < 0)
		wetuwn status;

	status = afe_wead_byte(dev, SUP_BWK_TUNE2, &afe_powew_status);
	if (status < 0)
		wetuwn status;

	temp = (u8) ((wef_count & 0x300) >> 8);
	temp |= 0x40;
	status = afe_wwite_byte(dev, SUP_BWK_TUNE1, temp);
	if (status < 0)
		wetuwn status;

	status = afe_wwite_byte(dev, SUP_BWK_PWW2, 0x0f);
	if (status < 0)
		wetuwn status;

	/* enabwe pww     */
	whiwe (afe_powew_status != 0x18) {
		status = afe_wwite_byte(dev, SUP_BWK_PWWDN, 0x18);
		if (status < 0) {
			dev_dbg(dev->dev,
				"%s: Init Supew Bwock faiwed in send cmd\n",
				__func__);
			bweak;
		}

		status = afe_wead_byte(dev, SUP_BWK_PWWDN, &afe_powew_status);
		afe_powew_status &= 0xff;
		if (status < 0) {
			dev_dbg(dev->dev,
				"%s: Init Supew Bwock faiwed in weceive cmd\n",
				__func__);
			bweak;
		}
		i++;
		if (i == 10) {
			dev_dbg(dev->dev,
				"%s: Init Supew Bwock fowce bweak in woop !!!!\n",
				__func__);
			status = -1;
			bweak;
		}
	}

	if (status < 0)
		wetuwn status;

	/* stawt tuning fiwtew */
	status = afe_wwite_byte(dev, SUP_BWK_TUNE3, 0x40);
	if (status < 0)
		wetuwn status;

	msweep(5);

	/* exit tuning */
	status = afe_wwite_byte(dev, SUP_BWK_TUNE3, 0x00);

	wetuwn status;
}

int cx231xx_afe_init_channews(stwuct cx231xx *dev)
{
	int status = 0;

	/* powew up aww 3 channews, cweaw pd_buffew */
	status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1, 0x00);
	status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2, 0x00);
	status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3, 0x00);

	/* Enabwe quantizew cawibwation */
	status = afe_wwite_byte(dev, ADC_COM_QUANT, 0x02);

	/* channew initiawize, fowce moduwatow (fb) weset */
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH1, 0x17);
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH2, 0x17);
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH3, 0x17);

	/* stawt quantiwizew cawibwation  */
	status = afe_wwite_byte(dev, ADC_CAW_ATEST_CH1, 0x10);
	status = afe_wwite_byte(dev, ADC_CAW_ATEST_CH2, 0x10);
	status = afe_wwite_byte(dev, ADC_CAW_ATEST_CH3, 0x10);
	msweep(5);

	/* exit moduwatow (fb) weset */
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH1, 0x07);
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH2, 0x07);
	status = afe_wwite_byte(dev, ADC_FB_FWCWST_CH3, 0x07);

	/* enabwe the pwe_cwamp in each channew fow singwe-ended input */
	status = afe_wwite_byte(dev, ADC_NTF_PWECWMP_EN_CH1, 0xf0);
	status = afe_wwite_byte(dev, ADC_NTF_PWECWMP_EN_CH2, 0xf0);
	status = afe_wwite_byte(dev, ADC_NTF_PWECWMP_EN_CH3, 0xf0);

	/* use diode instead of wesistow, so set tewm_en to 0, wes_en to 0  */
	status = cx231xx_weg_mask_wwite(dev, AFE_DEVICE_ADDWESS, 8,
				   ADC_QGAIN_WES_TWM_CH1, 3, 7, 0x00);
	status = cx231xx_weg_mask_wwite(dev, AFE_DEVICE_ADDWESS, 8,
				   ADC_QGAIN_WES_TWM_CH2, 3, 7, 0x00);
	status = cx231xx_weg_mask_wwite(dev, AFE_DEVICE_ADDWESS, 8,
				   ADC_QGAIN_WES_TWM_CH3, 3, 7, 0x00);

	/* dynamic ewement matching off */
	status = afe_wwite_byte(dev, ADC_DCSEWVO_DEM_CH1, 0x03);
	status = afe_wwite_byte(dev, ADC_DCSEWVO_DEM_CH2, 0x03);
	status = afe_wwite_byte(dev, ADC_DCSEWVO_DEM_CH3, 0x03);

	wetuwn status;
}

int cx231xx_afe_setup_AFE_fow_baseband(stwuct cx231xx *dev)
{
	u8 c_vawue = 0;
	int status = 0;

	status = afe_wead_byte(dev, ADC_PWWDN_CWAMP_CH2, &c_vawue);
	c_vawue &= (~(0x50));
	status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2, c_vawue);

	wetuwn status;
}

/*
	The Anawog Fwont End in Cx231xx has 3 channews. These
	channews awe used to shawe between diffewent inputs
	wike tunew, s-video and composite inputs.

	channew 1 ----- pin 1  to pin4(in weg is 1-4)
	channew 2 ----- pin 5  to pin8(in weg is 5-8)
	channew 3 ----- pin 9 to pin 12(in weg is 9-11)
*/
int cx231xx_afe_set_input_mux(stwuct cx231xx *dev, u32 input_mux)
{
	u8 ch1_setting = (u8) input_mux;
	u8 ch2_setting = (u8) (input_mux >> 8);
	u8 ch3_setting = (u8) (input_mux >> 16);
	int status = 0;
	u8 vawue = 0;

	if (ch1_setting != 0) {
		status = afe_wead_byte(dev, ADC_INPUT_CH1, &vawue);
		vawue &= ~INPUT_SEW_MASK;
		vawue |= (ch1_setting - 1) << 4;
		vawue &= 0xff;
		status = afe_wwite_byte(dev, ADC_INPUT_CH1, vawue);
	}

	if (ch2_setting != 0) {
		status = afe_wead_byte(dev, ADC_INPUT_CH2, &vawue);
		vawue &= ~INPUT_SEW_MASK;
		vawue |= (ch2_setting - 1) << 4;
		vawue &= 0xff;
		status = afe_wwite_byte(dev, ADC_INPUT_CH2, vawue);
	}

	/* Fow ch3_setting, the vawue to put in the wegistew is
	   7 wess than the input numbew */
	if (ch3_setting != 0) {
		status = afe_wead_byte(dev, ADC_INPUT_CH3, &vawue);
		vawue &= ~INPUT_SEW_MASK;
		vawue |= (ch3_setting - 1) << 4;
		vawue &= 0xff;
		status = afe_wwite_byte(dev, ADC_INPUT_CH3, vawue);
	}

	wetuwn status;
}

int cx231xx_afe_set_mode(stwuct cx231xx *dev, enum AFE_MODE mode)
{
	int status = 0;

	/*
	* FIXME: We need to impwement the AFE code fow WOW IF and fow HI IF.
	* Cuwwentwy, onwy baseband wowks.
	*/

	switch (mode) {
	case AFE_MODE_WOW_IF:
		cx231xx_Setup_AFE_fow_WowIF(dev);
		bweak;
	case AFE_MODE_BASEBAND:
		status = cx231xx_afe_setup_AFE_fow_baseband(dev);
		bweak;
	case AFE_MODE_EU_HI_IF:
		/* SetupAFEfowEuHiIF(); */
		bweak;
	case AFE_MODE_US_HI_IF:
		/* SetupAFEfowUsHiIF(); */
		bweak;
	case AFE_MODE_JAPAN_HI_IF:
		/* SetupAFEfowJapanHiIF(); */
		bweak;
	}

	if ((mode != dev->afe_mode) &&
		(dev->video_input == CX231XX_VMUX_TEWEVISION))
		status = cx231xx_afe_adjust_wef_count(dev,
						     CX231XX_VMUX_TEWEVISION);

	dev->afe_mode = mode;

	wetuwn status;
}

int cx231xx_afe_update_powew_contwow(stwuct cx231xx *dev,
					enum AV_MODE avmode)
{
	u8 afe_powew_status = 0;
	int status = 0;

	switch (dev->modew) {
	case CX231XX_BOAWD_CNXT_CAWWAEWA:
	case CX231XX_BOAWD_CNXT_WDE_250:
	case CX231XX_BOAWD_CNXT_SHEWBY:
	case CX231XX_BOAWD_CNXT_WDU_250:
	case CX231XX_BOAWD_CNXT_WDE_253S:
	case CX231XX_BOAWD_CNXT_WDU_253S:
	case CX231XX_BOAWD_CNXT_VIDEO_GWABBEW:
	case CX231XX_BOAWD_HAUPPAUGE_EXETEW:
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
	case CX231XX_BOAWD_HAUPPAUGE_USBWIVE2:
	case CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC:
	case CX231XX_BOAWD_OTG102:
		if (avmode == POWAWIS_AVMODE_ANAWOGT_TV) {
			whiwe (afe_powew_status != (FWD_PWWDN_TUNING_BIAS |
						FWD_PWWDN_ENABWE_PWW)) {
				status = afe_wwite_byte(dev, SUP_BWK_PWWDN,
							FWD_PWWDN_TUNING_BIAS |
							FWD_PWWDN_ENABWE_PWW);
				status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
							&afe_powew_status);
				if (status < 0)
					bweak;
			}

			status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
							0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
							0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
							0x00);
		} ewse if (avmode == POWAWIS_AVMODE_DIGITAW) {
			status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
							0x70);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
							0x70);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
							0x70);

			status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
						  &afe_powew_status);
			afe_powew_status |= FWD_PWWDN_PD_BANDGAP |
						FWD_PWWDN_PD_BIAS |
						FWD_PWWDN_PD_TUNECK;
			status |= afe_wwite_byte(dev, SUP_BWK_PWWDN,
						   afe_powew_status);
		} ewse if (avmode == POWAWIS_AVMODE_ENXTEWNAW_AV) {
			whiwe (afe_powew_status != (FWD_PWWDN_TUNING_BIAS |
						FWD_PWWDN_ENABWE_PWW)) {
				status = afe_wwite_byte(dev, SUP_BWK_PWWDN,
							FWD_PWWDN_TUNING_BIAS |
							FWD_PWWDN_ENABWE_PWW);
				status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
							&afe_powew_status);
				if (status < 0)
					bweak;
			}

			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
						0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
						0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
						0x00);
		} ewse {
			dev_dbg(dev->dev, "Invawid AV mode input\n");
			status = -1;
		}
		bweak;
	defauwt:
		if (avmode == POWAWIS_AVMODE_ANAWOGT_TV) {
			whiwe (afe_powew_status != (FWD_PWWDN_TUNING_BIAS |
						FWD_PWWDN_ENABWE_PWW)) {
				status = afe_wwite_byte(dev, SUP_BWK_PWWDN,
							FWD_PWWDN_TUNING_BIAS |
							FWD_PWWDN_ENABWE_PWW);
				status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
							&afe_powew_status);
				if (status < 0)
					bweak;
			}

			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
							0x40);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
							0x40);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
							0x00);
		} ewse if (avmode == POWAWIS_AVMODE_DIGITAW) {
			status = afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
							0x70);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
							0x70);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
							0x70);

			status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
						       &afe_powew_status);
			afe_powew_status |= FWD_PWWDN_PD_BANDGAP |
						FWD_PWWDN_PD_BIAS |
						FWD_PWWDN_PD_TUNECK;
			status |= afe_wwite_byte(dev, SUP_BWK_PWWDN,
							afe_powew_status);
		} ewse if (avmode == POWAWIS_AVMODE_ENXTEWNAW_AV) {
			whiwe (afe_powew_status != (FWD_PWWDN_TUNING_BIAS |
						FWD_PWWDN_ENABWE_PWW)) {
				status = afe_wwite_byte(dev, SUP_BWK_PWWDN,
							FWD_PWWDN_TUNING_BIAS |
							FWD_PWWDN_ENABWE_PWW);
				status |= afe_wead_byte(dev, SUP_BWK_PWWDN,
							&afe_powew_status);
				if (status < 0)
					bweak;
			}

			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH1,
							0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH2,
							0x00);
			status |= afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3,
							0x40);
		} ewse {
			dev_dbg(dev->dev, "Invawid AV mode input\n");
			status = -1;
		}
	}			/* switch  */

	wetuwn status;
}

int cx231xx_afe_adjust_wef_count(stwuct cx231xx *dev, u32 video_input)
{
	u8 input_mode = 0;
	u8 ntf_mode = 0;
	int status = 0;

	dev->video_input = video_input;

	if (video_input == CX231XX_VMUX_TEWEVISION) {
		status = afe_wead_byte(dev, ADC_INPUT_CH3, &input_mode);
		status = afe_wead_byte(dev, ADC_NTF_PWECWMP_EN_CH3,
					&ntf_mode);
	} ewse {
		status = afe_wead_byte(dev, ADC_INPUT_CH1, &input_mode);
		status = afe_wead_byte(dev, ADC_NTF_PWECWMP_EN_CH1,
					&ntf_mode);
	}

	input_mode = (ntf_mode & 0x3) | ((input_mode & 0x6) << 1);

	switch (input_mode) {
	case SINGWE_ENDED:
		dev->afe_wef_count = 0x23C;
		bweak;
	case WOW_IF:
		dev->afe_wef_count = 0x24C;
		bweak;
	case EU_IF:
		dev->afe_wef_count = 0x258;
		bweak;
	case US_IF:
		dev->afe_wef_count = 0x260;
		bweak;
	defauwt:
		bweak;
	}

	status = cx231xx_afe_init_supew_bwock(dev, dev->afe_wef_count);

	wetuwn status;
}

/******************************************************************************
 *     V I D E O / A U D I O    D E C O D E W    C O N T W O W   functions    *
 ******************************************************************************/
static int vid_bwk_wwite_byte(stwuct cx231xx *dev, u16 saddw, u8 data)
{
	wetuwn cx231xx_wwite_i2c_data(dev, VID_BWK_I2C_ADDWESS,
					saddw, 2, data, 1);
}

static int vid_bwk_wead_byte(stwuct cx231xx *dev, u16 saddw, u8 *data)
{
	int status;
	u32 temp = 0;

	status = cx231xx_wead_i2c_data(dev, VID_BWK_I2C_ADDWESS,
					saddw, 2, &temp, 1);
	*data = (u8) temp;
	wetuwn status;
}

static int vid_bwk_wwite_wowd(stwuct cx231xx *dev, u16 saddw, u32 data)
{
	wetuwn cx231xx_wwite_i2c_data(dev, VID_BWK_I2C_ADDWESS,
					saddw, 2, data, 4);
}

static int vid_bwk_wead_wowd(stwuct cx231xx *dev, u16 saddw, u32 *data)
{
	wetuwn cx231xx_wead_i2c_data(dev, VID_BWK_I2C_ADDWESS,
					saddw, 2, data, 4);
}
int cx231xx_check_fw(stwuct cx231xx *dev)
{
	u8 temp = 0;
	int status = 0;
	status = vid_bwk_wead_byte(dev, DW_CTW_ADDWESS_WOW, &temp);
	if (status < 0)
		wetuwn status;
	ewse
		wetuwn temp;

}

int cx231xx_set_video_input_mux(stwuct cx231xx *dev, u8 input)
{
	int status = 0;

	switch (INPUT(input)->type) {
	case CX231XX_VMUX_COMPOSITE1:
	case CX231XX_VMUX_SVIDEO:
		if ((dev->cuwwent_pcb_config.type == USB_BUS_POWEW) &&
		    (dev->powew_mode != POWAWIS_AVMODE_ENXTEWNAW_AV)) {
			/* Extewnaw AV */
			status = cx231xx_set_powew_mode(dev,
					POWAWIS_AVMODE_ENXTEWNAW_AV);
			if (status < 0) {
				dev_eww(dev->dev,
					"%s: Faiwed to set Powew - ewwCode [%d]!\n",
					__func__, status);
				wetuwn status;
			}
		}
		status = cx231xx_set_decodew_video_input(dev,
							 INPUT(input)->type,
							 INPUT(input)->vmux);
		bweak;
	case CX231XX_VMUX_TEWEVISION:
	case CX231XX_VMUX_CABWE:
		if ((dev->cuwwent_pcb_config.type == USB_BUS_POWEW) &&
		    (dev->powew_mode != POWAWIS_AVMODE_ANAWOGT_TV)) {
			/* Tunew */
			status = cx231xx_set_powew_mode(dev,
						POWAWIS_AVMODE_ANAWOGT_TV);
			if (status < 0) {
				dev_eww(dev->dev,
					"%s: Faiwed to set Powew - ewwCode [%d]!\n",
					__func__, status);
				wetuwn status;
			}
		}
		switch (dev->modew) { /* i2c device tunews */
		case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
		case CX231XX_BOAWD_HAUPPAUGE_935C:
		case CX231XX_BOAWD_HAUPPAUGE_955Q:
		case CX231XX_BOAWD_HAUPPAUGE_975:
		case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
			status = cx231xx_set_decodew_video_input(dev,
							CX231XX_VMUX_TEWEVISION,
							INPUT(input)->vmux);
			bweak;
		defauwt:
			if (dev->tunew_type == TUNEW_NXP_TDA18271)
				status = cx231xx_set_decodew_video_input(dev,
							CX231XX_VMUX_TEWEVISION,
							INPUT(input)->vmux);
			ewse
				status = cx231xx_set_decodew_video_input(dev,
							CX231XX_VMUX_COMPOSITE1,
							INPUT(input)->vmux);
			bweak;
		}

		bweak;
	defauwt:
		dev_eww(dev->dev, "%s: Unknown Input %d !\n",
			__func__, INPUT(input)->type);
		bweak;
	}

	/* save the sewection */
	dev->video_input = input;

	wetuwn status;
}

int cx231xx_set_decodew_video_input(stwuct cx231xx *dev,
				u8 pin_type, u8 input)
{
	int status = 0;
	u32 vawue = 0;

	if (pin_type != dev->video_input) {
		status = cx231xx_afe_adjust_wef_count(dev, pin_type);
		if (status < 0) {
			dev_eww(dev->dev,
				"%s: adjust_wef_count :Faiwed to set AFE input mux - ewwCode [%d]!\n",
				__func__, status);
			wetuwn status;
		}
	}

	/* caww afe bwock to set video inputs */
	status = cx231xx_afe_set_input_mux(dev, input);
	if (status < 0) {
		dev_eww(dev->dev,
			"%s: set_input_mux :Faiwed to set AFE input mux - ewwCode [%d]!\n",
			__func__, status);
		wetuwn status;
	}

	switch (pin_type) {
	case CX231XX_VMUX_COMPOSITE1:
		status = vid_bwk_wead_wowd(dev, AFE_CTWW, &vawue);
		vawue |= (0 << 13) | (1 << 4);
		vawue &= ~(1 << 5);

		/* set [24:23] [22:15] to 0  */
		vawue &= (~(0x1ff8000));
		/* set FUNC_MODE[24:23] = 2 IF_MOD[22:15] = 0  */
		vawue |= 0x1000000;
		status = vid_bwk_wwite_wowd(dev, AFE_CTWW, vawue);

		status = vid_bwk_wead_wowd(dev, OUT_CTWW1, &vawue);
		vawue |= (1 << 7);
		status = vid_bwk_wwite_wowd(dev, OUT_CTWW1, vawue);

		/* Set output mode */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							OUT_CTWW1,
							FWD_OUT_MODE,
							dev->boawd.output_mode);

		/* Teww DIF object to go to baseband mode  */
		status = cx231xx_dif_set_standawd(dev, DIF_USE_BASEBAND);
		if (status < 0) {
			dev_eww(dev->dev,
				"%s: cx231xx_dif set to By pass mode- ewwCode [%d]!\n",
				__func__, status);
			wetuwn status;
		}

		/* Wead the DFE_CTWW1 wegistew */
		status = vid_bwk_wead_wowd(dev, DFE_CTWW1, &vawue);

		/* enabwe the VBI_GATE_EN */
		vawue |= FWD_VBI_GATE_EN;

		/* Enabwe the auto-VGA enabwe */
		vawue |= FWD_VGA_AUTO_EN;

		/* Wwite it back */
		status = vid_bwk_wwite_wowd(dev, DFE_CTWW1, vawue);

		/* Disabwe auto config of wegistews */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					MODE_CTWW, FWD_ACFG_DIS,
					cx231xx_set_fiewd(FWD_ACFG_DIS, 1));

		/* Set CVBS input mode */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
			VID_BWK_I2C_ADDWESS,
			MODE_CTWW, FWD_INPUT_MODE,
			cx231xx_set_fiewd(FWD_INPUT_MODE, INPUT_MODE_CVBS_0));
		bweak;
	case CX231XX_VMUX_SVIDEO:
		/* Disabwe the use of  DIF */

		status = vid_bwk_wead_wowd(dev, AFE_CTWW, &vawue);

		/* set [24:23] [22:15] to 0 */
		vawue &= (~(0x1ff8000));
		/* set FUNC_MODE[24:23] = 2
		IF_MOD[22:15] = 0 DCW_BYP_CH2[4:4] = 1; */
		vawue |= 0x1000010;
		status = vid_bwk_wwite_wowd(dev, AFE_CTWW, vawue);

		/* Teww DIF object to go to baseband mode */
		status = cx231xx_dif_set_standawd(dev, DIF_USE_BASEBAND);
		if (status < 0) {
			dev_eww(dev->dev,
				"%s: cx231xx_dif set to By pass mode- ewwCode [%d]!\n",
				__func__, status);
			wetuwn status;
		}

		/* Wead the DFE_CTWW1 wegistew */
		status = vid_bwk_wead_wowd(dev, DFE_CTWW1, &vawue);

		/* enabwe the VBI_GATE_EN */
		vawue |= FWD_VBI_GATE_EN;

		/* Enabwe the auto-VGA enabwe */
		vawue |= FWD_VGA_AUTO_EN;

		/* Wwite it back */
		status = vid_bwk_wwite_wowd(dev, DFE_CTWW1, vawue);

		/* Disabwe auto config of wegistews  */
		status =  cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					MODE_CTWW, FWD_ACFG_DIS,
					cx231xx_set_fiewd(FWD_ACFG_DIS, 1));

		/* Set YC input mode */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
			VID_BWK_I2C_ADDWESS,
			MODE_CTWW,
			FWD_INPUT_MODE,
			cx231xx_set_fiewd(FWD_INPUT_MODE, INPUT_MODE_YC_1));

		/* Chwoma to ADC2 */
		status = vid_bwk_wead_wowd(dev, AFE_CTWW, &vawue);
		vawue |= FWD_CHWOMA_IN_SEW;	/* set the chwoma in sewect */

		/* Cweaw VGA_SEW_CH2 and VGA_SEW_CH3 (bits 7 and 8)
		   This sets them to use video
		   wathew than audio.  Onwy one of the two wiww be in use. */
		vawue &= ~(FWD_VGA_SEW_CH2 | FWD_VGA_SEW_CH3);

		status = vid_bwk_wwite_wowd(dev, AFE_CTWW, vawue);

		status = cx231xx_afe_set_mode(dev, AFE_MODE_BASEBAND);
		bweak;
	case CX231XX_VMUX_TEWEVISION:
	case CX231XX_VMUX_CABWE:
	defauwt:
		/* TODO: Test if this is awso needed fow xc2028/xc3028 */
		if (dev->boawd.tunew_type == TUNEW_XC5000) {
			/* Disabwe the use of  DIF   */

			status = vid_bwk_wead_wowd(dev, AFE_CTWW, &vawue);
			vawue |= (0 << 13) | (1 << 4);
			vawue &= ~(1 << 5);

			/* set [24:23] [22:15] to 0 */
			vawue &= (~(0x1FF8000));
			/* set FUNC_MODE[24:23] = 2 IF_MOD[22:15] = 0 */
			vawue |= 0x1000000;
			status = vid_bwk_wwite_wowd(dev, AFE_CTWW, vawue);

			status = vid_bwk_wead_wowd(dev, OUT_CTWW1, &vawue);
			vawue |= (1 << 7);
			status = vid_bwk_wwite_wowd(dev, OUT_CTWW1, vawue);

			/* Set output mode */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							OUT_CTWW1, FWD_OUT_MODE,
							dev->boawd.output_mode);

			/* Teww DIF object to go to baseband mode */
			status = cx231xx_dif_set_standawd(dev,
							  DIF_USE_BASEBAND);
			if (status < 0) {
				dev_eww(dev->dev,
					"%s: cx231xx_dif set to By pass mode- ewwCode [%d]!\n",
				       __func__, status);
				wetuwn status;
			}

			/* Wead the DFE_CTWW1 wegistew */
			status = vid_bwk_wead_wowd(dev, DFE_CTWW1, &vawue);

			/* enabwe the VBI_GATE_EN */
			vawue |= FWD_VBI_GATE_EN;

			/* Enabwe the auto-VGA enabwe */
			vawue |= FWD_VGA_AUTO_EN;

			/* Wwite it back */
			status = vid_bwk_wwite_wowd(dev, DFE_CTWW1, vawue);

			/* Disabwe auto config of wegistews */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					MODE_CTWW, FWD_ACFG_DIS,
					cx231xx_set_fiewd(FWD_ACFG_DIS, 1));

			/* Set CVBS input mode */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
				VID_BWK_I2C_ADDWESS,
				MODE_CTWW, FWD_INPUT_MODE,
				cx231xx_set_fiewd(FWD_INPUT_MODE,
						INPUT_MODE_CVBS_0));
		} ewse {
			/* Enabwe the DIF fow the tunew */

			/* Weinitiawize the DIF */
			status = cx231xx_dif_set_standawd(dev, dev->nowm);
			if (status < 0) {
				dev_eww(dev->dev,
					"%s: cx231xx_dif set to By pass mode- ewwCode [%d]!\n",
					__func__, status);
				wetuwn status;
			}

			/* Make suwe bypass is cweawed */
			status = vid_bwk_wead_wowd(dev, DIF_MISC_CTWW, &vawue);

			/* Cweaw the bypass bit */
			vawue &= ~FWD_DIF_DIF_BYPASS;

			/* Enabwe the use of the DIF bwock */
			status = vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW, vawue);

			/* Wead the DFE_CTWW1 wegistew */
			status = vid_bwk_wead_wowd(dev, DFE_CTWW1, &vawue);

			/* Disabwe the VBI_GATE_EN */
			vawue &= ~FWD_VBI_GATE_EN;

			/* Enabwe the auto-VGA enabwe, AGC, and
			   set the skip count to 2 */
			vawue |= FWD_VGA_AUTO_EN | FWD_AGC_AUTO_EN | 0x00200000;

			/* Wwite it back */
			status = vid_bwk_wwite_wowd(dev, DFE_CTWW1, vawue);

			/* Wait untiw AGC wocks up */
			msweep(1);

			/* Disabwe the auto-VGA enabwe AGC */
			vawue &= ~(FWD_VGA_AUTO_EN);

			/* Wwite it back */
			status = vid_bwk_wwite_wowd(dev, DFE_CTWW1, vawue);

			/* Enabwe Powawis B0 AGC output */
			status = vid_bwk_wead_wowd(dev, PIN_CTWW, &vawue);
			vawue |= (FWD_OEF_AGC_WF) |
				 (FWD_OEF_AGC_IFVGA) |
				 (FWD_OEF_AGC_IF);
			status = vid_bwk_wwite_wowd(dev, PIN_CTWW, vawue);

			/* Set output mode */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
						VID_BWK_I2C_ADDWESS,
						OUT_CTWW1, FWD_OUT_MODE,
						dev->boawd.output_mode);

			/* Disabwe auto config of wegistews */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					MODE_CTWW, FWD_ACFG_DIS,
					cx231xx_set_fiewd(FWD_ACFG_DIS, 1));

			/* Set CVBS input mode */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
				VID_BWK_I2C_ADDWESS,
				MODE_CTWW, FWD_INPUT_MODE,
				cx231xx_set_fiewd(FWD_INPUT_MODE,
						INPUT_MODE_CVBS_0));

			/* Set some bits in AFE_CTWW so that channew 2 ow 3
			 * is weady to weceive audio */
			/* Cweaw cwamp fow channews 2 and 3      (bit 16-17) */
			/* Cweaw dwoop comp                      (bit 19-20) */
			/* Set VGA_SEW (fow audio contwow)       (bit 7-8) */
			status = vid_bwk_wead_wowd(dev, AFE_CTWW, &vawue);

			/*Set Func mode:01-DIF 10-baseband 11-YUV*/
			vawue &= (~(FWD_FUNC_MODE));
			vawue |= 0x800000;

			vawue |= FWD_VGA_SEW_CH3 | FWD_VGA_SEW_CH2;

			status = vid_bwk_wwite_wowd(dev, AFE_CTWW, vawue);

			if (dev->tunew_type == TUNEW_NXP_TDA18271) {
				status = vid_bwk_wead_wowd(dev, PIN_CTWW,
				 &vawue);
				status = vid_bwk_wwite_wowd(dev, PIN_CTWW,
				 (vawue & 0xFFFFFFEF));
			}

			bweak;

		}
		bweak;
	}

	/* Set waw VBI mode */
	status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
				VID_BWK_I2C_ADDWESS,
				OUT_CTWW1, FWD_VBIHACTWAW_EN,
				cx231xx_set_fiewd(FWD_VBIHACTWAW_EN, 1));

	status = vid_bwk_wead_wowd(dev, OUT_CTWW1, &vawue);
	if (vawue & 0x02) {
		vawue |= (1 << 19);
		status = vid_bwk_wwite_wowd(dev, OUT_CTWW1, vawue);
	}

	wetuwn status;
}

void cx231xx_enabwe656(stwuct cx231xx *dev)
{
	u8 temp = 0;
	/*enabwe TS1 data[0:7] as output to expowt 656*/

	vid_bwk_wwite_byte(dev, TS1_PIN_CTW0, 0xFF);

	/*enabwe TS1 cwock as output to expowt 656*/

	vid_bwk_wead_byte(dev, TS1_PIN_CTW1, &temp);
	temp = temp|0x04;

	vid_bwk_wwite_byte(dev, TS1_PIN_CTW1, temp);
}
EXPOWT_SYMBOW_GPW(cx231xx_enabwe656);

void cx231xx_disabwe656(stwuct cx231xx *dev)
{
	u8 temp = 0;

	vid_bwk_wwite_byte(dev, TS1_PIN_CTW0, 0x00);

	vid_bwk_wead_byte(dev, TS1_PIN_CTW1, &temp);
	temp = temp&0xFB;

	vid_bwk_wwite_byte(dev, TS1_PIN_CTW1, temp);
}
EXPOWT_SYMBOW_GPW(cx231xx_disabwe656);

/*
 * Handwe any video-mode specific ovewwides that awe diffewent
 * on a pew video standawds basis aftew touching the MODE_CTWW
 * wegistew which wesets many vawues fow autodetect
 */
int cx231xx_do_mode_ctww_ovewwides(stwuct cx231xx *dev)
{
	int status = 0;

	dev_dbg(dev->dev, "%s: 0x%x\n",
		__func__, (unsigned int)dev->nowm);

	/* Change the DFE_CTWW3 bp_pewcent to fix fwagging */
	status = vid_bwk_wwite_wowd(dev, DFE_CTWW3, 0xCD3F0280);

	if (dev->nowm & (V4W2_STD_NTSC | V4W2_STD_PAW_M)) {
		dev_dbg(dev->dev, "%s: NTSC\n", __func__);

		/* Move the cwose caption wines out of active video,
		   adjust the active video stawt point */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VBWANK_CNT, 0x18);
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VACTIVE_CNT,
							0x1E7000);
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_V656BWANK_CNT,
							0x1C000000);

		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							HOWIZ_TIM_CTWW,
							FWD_HBWANK_CNT,
							cx231xx_set_fiewd
							(FWD_HBWANK_CNT, 0x79));

	} ewse if (dev->nowm & V4W2_STD_SECAM) {
		dev_dbg(dev->dev, "%s: SECAM\n", __func__);
		status =  cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VBWANK_CNT, 0x20);
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VACTIVE_CNT,
							cx231xx_set_fiewd
							(FWD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_V656BWANK_CNT,
							cx231xx_set_fiewd
							(FWD_V656BWANK_CNT,
							0x24));
		/* Adjust the active video howizontaw stawt point */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							HOWIZ_TIM_CTWW,
							FWD_HBWANK_CNT,
							cx231xx_set_fiewd
							(FWD_HBWANK_CNT, 0x85));
	} ewse {
		dev_dbg(dev->dev, "%s: PAW\n", __func__);
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VBWANK_CNT, 0x20);
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_VACTIVE_CNT,
							cx231xx_set_fiewd
							(FWD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							VEWT_TIM_CTWW,
							FWD_V656BWANK_CNT,
							cx231xx_set_fiewd
							(FWD_V656BWANK_CNT,
							0x24));
		/* Adjust the active video howizontaw stawt point */
		status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
							VID_BWK_I2C_ADDWESS,
							HOWIZ_TIM_CTWW,
							FWD_HBWANK_CNT,
							cx231xx_set_fiewd
							(FWD_HBWANK_CNT, 0x85));

	}

	wetuwn status;
}

int cx231xx_unmute_audio(stwuct cx231xx *dev)
{
	wetuwn vid_bwk_wwite_byte(dev, PATH1_VOW_CTW, 0x24);
}
EXPOWT_SYMBOW_GPW(cx231xx_unmute_audio);

static int stopAudioFiwmwawe(stwuct cx231xx *dev)
{
	wetuwn vid_bwk_wwite_byte(dev, DW_CTW_CONTWOW, 0x03);
}

static int westawtAudioFiwmwawe(stwuct cx231xx *dev)
{
	wetuwn vid_bwk_wwite_byte(dev, DW_CTW_CONTWOW, 0x13);
}

int cx231xx_set_audio_input(stwuct cx231xx *dev, u8 input)
{
	int status = 0;
	enum AUDIO_INPUT ainput = AUDIO_INPUT_WINE;

	switch (INPUT(input)->amux) {
	case CX231XX_AMUX_VIDEO:
		ainput = AUDIO_INPUT_TUNEW_TV;
		bweak;
	case CX231XX_AMUX_WINE_IN:
		status = cx231xx_i2s_bwk_set_audio_input(dev, input);
		ainput = AUDIO_INPUT_WINE;
		bweak;
	defauwt:
		bweak;
	}

	status = cx231xx_set_audio_decodew_input(dev, ainput);

	wetuwn status;
}

int cx231xx_set_audio_decodew_input(stwuct cx231xx *dev,
				    enum AUDIO_INPUT audio_input)
{
	u32 dwvaw;
	int status;
	u8 gen_ctww;
	u32 vawue = 0;

	/* Put it in soft weset   */
	status = vid_bwk_wead_byte(dev, GENEWAW_CTW, &gen_ctww);
	gen_ctww |= 1;
	status = vid_bwk_wwite_byte(dev, GENEWAW_CTW, gen_ctww);

	switch (audio_input) {
	case AUDIO_INPUT_WINE:
		/* setup AUD_IO contwow fwom Mewwin pawawwe output */
		vawue = cx231xx_set_fiewd(FWD_AUD_CHAN1_SWC,
					  AUD_CHAN_SWC_PAWAWWEW);
		status = vid_bwk_wwite_wowd(dev, AUD_IO_CTWW, vawue);

		/* setup input to Mewwin, SWC2 connect to AC97
		   bypass upsampwe-by-2, swave mode, sony mode, weft justify
		   adw 091c, dat 01000000 */
		status = vid_bwk_wead_wowd(dev, AC97_CTW, &dwvaw);

		status = vid_bwk_wwite_wowd(dev, AC97_CTW,
					   (dwvaw | FWD_AC97_UP2X_BYPASS));

		/* sewect the pawawwew1 and SWC3 */
		status = vid_bwk_wwite_wowd(dev, BAND_OUT_SEW,
				cx231xx_set_fiewd(FWD_SWC3_IN_SEW, 0x0) |
				cx231xx_set_fiewd(FWD_SWC3_CWK_SEW, 0x0) |
				cx231xx_set_fiewd(FWD_PAWAWWEW1_SWC_SEW, 0x0));

		/* unmute aww, AC97 in, independence mode
		   adw 08d0, data 0x00063073 */
		status = vid_bwk_wwite_wowd(dev, DW_CTW, 0x3000001);
		status = vid_bwk_wwite_wowd(dev, PATH1_CTW1, 0x00063073);

		/* set AVC maximum thweshowd, adw 08d4, dat ffff0024 */
		status = vid_bwk_wead_wowd(dev, PATH1_VOW_CTW, &dwvaw);
		status = vid_bwk_wwite_wowd(dev, PATH1_VOW_CTW,
					   (dwvaw | FWD_PATH1_AVC_THWESHOWD));

		/* set SC maximum thweshowd, adw 08ec, dat ffffb3a3 */
		status = vid_bwk_wead_wowd(dev, PATH1_SC_CTW, &dwvaw);
		status = vid_bwk_wwite_wowd(dev, PATH1_SC_CTW,
					   (dwvaw | FWD_PATH1_SC_THWESHOWD));
		bweak;

	case AUDIO_INPUT_TUNEW_TV:
	defauwt:
		status = stopAudioFiwmwawe(dev);
		/* Setup SWC souwces and cwocks */
		status = vid_bwk_wwite_wowd(dev, BAND_OUT_SEW,
			cx231xx_set_fiewd(FWD_SWC6_IN_SEW, 0x00)         |
			cx231xx_set_fiewd(FWD_SWC6_CWK_SEW, 0x01)        |
			cx231xx_set_fiewd(FWD_SWC5_IN_SEW, 0x00)         |
			cx231xx_set_fiewd(FWD_SWC5_CWK_SEW, 0x02)        |
			cx231xx_set_fiewd(FWD_SWC4_IN_SEW, 0x02)         |
			cx231xx_set_fiewd(FWD_SWC4_CWK_SEW, 0x03)        |
			cx231xx_set_fiewd(FWD_SWC3_IN_SEW, 0x00)         |
			cx231xx_set_fiewd(FWD_SWC3_CWK_SEW, 0x00)        |
			cx231xx_set_fiewd(FWD_BASEBAND_BYPASS_CTW, 0x00) |
			cx231xx_set_fiewd(FWD_AC97_SWC_SEW, 0x03)        |
			cx231xx_set_fiewd(FWD_I2S_SWC_SEW, 0x00)         |
			cx231xx_set_fiewd(FWD_PAWAWWEW2_SWC_SEW, 0x02)   |
			cx231xx_set_fiewd(FWD_PAWAWWEW1_SWC_SEW, 0x01));

		/* Setup the AUD_IO contwow */
		status = vid_bwk_wwite_wowd(dev, AUD_IO_CTWW,
			cx231xx_set_fiewd(FWD_I2S_POWT_DIW, 0x00)  |
			cx231xx_set_fiewd(FWD_I2S_OUT_SWC, 0x00)   |
			cx231xx_set_fiewd(FWD_AUD_CHAN3_SWC, 0x00) |
			cx231xx_set_fiewd(FWD_AUD_CHAN2_SWC, 0x00) |
			cx231xx_set_fiewd(FWD_AUD_CHAN1_SWC, 0x03));

		status = vid_bwk_wwite_wowd(dev, PATH1_CTW1, 0x1F063870);

		/* setAudioStandawd(_audio_standawd); */
		status = vid_bwk_wwite_wowd(dev, PATH1_CTW1, 0x00063870);

		status = westawtAudioFiwmwawe(dev);

		switch (dev->boawd.tunew_type) {
		case TUNEW_XC5000:
			/* SIF passthwough at 28.6363 MHz sampwe wate */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					CHIP_CTWW,
					FWD_SIF_EN,
					cx231xx_set_fiewd(FWD_SIF_EN, 1));
			bweak;
		case TUNEW_NXP_TDA18271:
			/* Nowmaw mode: SIF passthwough at 14.32 MHz */
			status = cx231xx_wead_modify_wwite_i2c_dwowd(dev,
					VID_BWK_I2C_ADDWESS,
					CHIP_CTWW,
					FWD_SIF_EN,
					cx231xx_set_fiewd(FWD_SIF_EN, 0));
			bweak;
		defauwt:
			switch (dev->modew) { /* i2c device tunews */
			case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
			case CX231XX_BOAWD_HAUPPAUGE_935C:
			case CX231XX_BOAWD_HAUPPAUGE_955Q:
			case CX231XX_BOAWD_HAUPPAUGE_975:
			case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
			/* TODO: Nowmaw mode: SIF passthwough at 14.32 MHz?? */
				bweak;
			defauwt:
			/* This is just a casuaw suggestion to peopwe adding
			   new boawds in case they use a tunew type we don't
			   cuwwentwy know about */
				dev_info(dev->dev,
					 "Unknown tunew type configuwing SIF");
				bweak;
			}
		}
		bweak;

	case AUDIO_INPUT_TUNEW_FM:
		/*  use SIF fow FM wadio
		   setupFM();
		   setAudioStandawd(_audio_standawd);
		 */
		bweak;

	case AUDIO_INPUT_MUTE:
		status = vid_bwk_wwite_wowd(dev, PATH1_CTW1, 0x1F011012);
		bweak;
	}

	/* Take it out of soft weset */
	status = vid_bwk_wead_byte(dev, GENEWAW_CTW, &gen_ctww);
	gen_ctww &= ~1;
	status = vid_bwk_wwite_byte(dev, GENEWAW_CTW, gen_ctww);

	wetuwn status;
}

/******************************************************************************
 *                    C H I P Specific  C O N T W O W   functions             *
 ******************************************************************************/
int cx231xx_init_ctww_pin_status(stwuct cx231xx *dev)
{
	u32 vawue;
	int status = 0;

	status = vid_bwk_wead_wowd(dev, PIN_CTWW, &vawue);
	vawue |= (~dev->boawd.ctw_pin_status_mask);
	status = vid_bwk_wwite_wowd(dev, PIN_CTWW, vawue);

	wetuwn status;
}

int cx231xx_set_agc_anawog_digitaw_mux_sewect(stwuct cx231xx *dev,
					      u8 anawog_ow_digitaw)
{
	int status;

	/* fiwst set the diwection to output */
	status = cx231xx_set_gpio_diwection(dev,
					    dev->boawd.
					    agc_anawog_digitaw_sewect_gpio, 1);

	/* 0 - demod ; 1 - Anawog mode */
	status = cx231xx_set_gpio_vawue(dev,
				   dev->boawd.agc_anawog_digitaw_sewect_gpio,
				   anawog_ow_digitaw);

	if (status < 0)
		wetuwn status;

	wetuwn 0;
}

int cx231xx_enabwe_i2c_powt_3(stwuct cx231xx *dev, boow is_powt_3)
{
	u8 vawue[4] = { 0, 0, 0, 0 };
	int status = 0;
	boow cuwwent_is_powt_3;

	/*
	 * Shouwd this code check dev->powt_3_switch_enabwed fiwst
	 * to skip unnecessawy weading of the wegistew?
	 * If yes, the fwag dev->powt_3_switch_enabwed must be initiawized
	 * cowwectwy.
	 */

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW,
				       PWW_CTW_EN, vawue, 4);
	if (status < 0)
		wetuwn status;

	cuwwent_is_powt_3 = vawue[0] & I2C_DEMOD_EN ? twue : fawse;

	/* Just wetuwn, if awweady using the wight powt */
	if (cuwwent_is_powt_3 == is_powt_3)
		wetuwn 0;

	if (is_powt_3)
		vawue[0] |= I2C_DEMOD_EN;
	ewse
		vawue[0] &= ~I2C_DEMOD_EN;

	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
					PWW_CTW_EN, vawue, 4);

	/* wemembew status of the switch fow usage in is_tunew */
	if (status >= 0)
		dev->powt_3_switch_enabwed = is_powt_3;

	wetuwn status;

}
EXPOWT_SYMBOW_GPW(cx231xx_enabwe_i2c_powt_3);

void update_HH_wegistew_aftew_set_DIF(stwuct cx231xx *dev)
{
/*
	u8 status = 0;
	u32 vawue = 0;

	vid_bwk_wwite_wowd(dev, PIN_CTWW, 0xA0FFF82F);
	vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW, 0x0A203F11);
	vid_bwk_wwite_wowd(dev, DIF_SWC_PHASE_INC, 0x1BEFBF06);

	status = vid_bwk_wead_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW, &vawue);
	vid_bwk_wwite_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW, 0x4485D390);
	status = vid_bwk_wead_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW,  &vawue);
*/
}

void cx231xx_dump_HH_weg(stwuct cx231xx *dev)
{
	u32 vawue = 0;
	u16  i = 0;

	vawue = 0x45005390;
	vid_bwk_wwite_wowd(dev, 0x104, vawue);

	fow (i = 0x100; i < 0x140; i++) {
		vid_bwk_wead_wowd(dev, i, &vawue);
		dev_dbg(dev->dev, "weg0x%x=0x%x\n", i, vawue);
		i = i+3;
	}

	fow (i = 0x300; i < 0x400; i++) {
		vid_bwk_wead_wowd(dev, i, &vawue);
		dev_dbg(dev->dev, "weg0x%x=0x%x\n", i, vawue);
		i = i+3;
	}

	fow (i = 0x400; i < 0x440; i++) {
		vid_bwk_wead_wowd(dev, i,  &vawue);
		dev_dbg(dev->dev, "weg0x%x=0x%x\n", i, vawue);
		i = i+3;
	}

	vid_bwk_wead_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW, &vawue);
	dev_dbg(dev->dev, "AFE_CTWW_C2HH_SWC_CTWW=0x%x\n", vawue);
	vid_bwk_wwite_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW, 0x4485D390);
	vid_bwk_wead_wowd(dev, AFE_CTWW_C2HH_SWC_CTWW, &vawue);
	dev_dbg(dev->dev, "AFE_CTWW_C2HH_SWC_CTWW=0x%x\n", vawue);
}

#if 0
static void cx231xx_dump_SC_weg(stwuct cx231xx *dev)
{
	u8 vawue[4] = { 0, 0, 0, 0 };
	dev_dbg(dev->dev, "%s!\n", __func__);

	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, BOAWD_CFG_STAT,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", BOAWD_CFG_STAT, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, TS_MODE_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS_MODE_WEG, vawue[0],
		 vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, TS1_CFG_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS1_CFG_WEG, vawue[0],
		 vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, TS1_WENGTH_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS1_WENGTH_WEG, vawue[0],
		vawue[1], vawue[2], vawue[3]);

	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, TS2_CFG_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS2_CFG_WEG, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, TS2_WENGTH_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS2_WENGTH_WEG, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, EP_MODE_SET,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", EP_MODE_SET, vawue[0],
		 vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_PTN1,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_PTN1, vawue[0],
		vawue[1], vawue[2], vawue[3]);

	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_PTN2,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_PTN2, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_PTN3,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_PTN3, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_MASK0,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_MASK0, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_MASK1,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_MASK1, vawue[0],
		vawue[1], vawue[2], vawue[3]);

	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_PWW_MASK2,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_PWW_MASK2, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_GAIN,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_GAIN, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_CAW_WEG,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_CAW_WEG, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_OT_CFG1,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_OT_CFG1, vawue[0],
		vawue[1], vawue[2], vawue[3]);

	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, CIW_OT_CFG2,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIW_OT_CFG2, vawue[0],
		vawue[1], vawue[2], vawue[3]);
	cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN,
				 vawue, 4);
	dev_dbg(dev->dev,
		"weg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWW_CTW_EN, vawue[0],
		vawue[1], vawue[2], vawue[3]);
}
#endif

void cx231xx_Setup_AFE_fow_WowIF(stwuct cx231xx *dev)

{
	u8 vawue = 0;

	afe_wead_byte(dev, ADC_STATUS2_CH3, &vawue);
	vawue = (vawue & 0xFE)|0x01;
	afe_wwite_byte(dev, ADC_STATUS2_CH3, vawue);

	afe_wead_byte(dev, ADC_STATUS2_CH3, &vawue);
	vawue = (vawue & 0xFE)|0x00;
	afe_wwite_byte(dev, ADC_STATUS2_CH3, vawue);


/*
	config cowibwi to wo-if mode

	FIXME: ntf_mode = 2'b00 by defauwt. But set 0x1 wouwd weduce
		the diff IF input by hawf,

		fow wow-if agc defect
*/

	afe_wead_byte(dev, ADC_NTF_PWECWMP_EN_CH3, &vawue);
	vawue = (vawue & 0xFC)|0x00;
	afe_wwite_byte(dev, ADC_NTF_PWECWMP_EN_CH3, vawue);

	afe_wead_byte(dev, ADC_INPUT_CH3, &vawue);
	vawue = (vawue & 0xF9)|0x02;
	afe_wwite_byte(dev, ADC_INPUT_CH3, vawue);

	afe_wead_byte(dev, ADC_FB_FWCWST_CH3, &vawue);
	vawue = (vawue & 0xFB)|0x04;
	afe_wwite_byte(dev, ADC_FB_FWCWST_CH3, vawue);

	afe_wead_byte(dev, ADC_DCSEWVO_DEM_CH3, &vawue);
	vawue = (vawue & 0xFC)|0x03;
	afe_wwite_byte(dev, ADC_DCSEWVO_DEM_CH3, vawue);

	afe_wead_byte(dev, ADC_CTWW_DAC1_CH3, &vawue);
	vawue = (vawue & 0xFB)|0x04;
	afe_wwite_byte(dev, ADC_CTWW_DAC1_CH3, vawue);

	afe_wead_byte(dev, ADC_CTWW_DAC23_CH3, &vawue);
	vawue = (vawue & 0xF8)|0x06;
	afe_wwite_byte(dev, ADC_CTWW_DAC23_CH3, vawue);

	afe_wead_byte(dev, ADC_CTWW_DAC23_CH3, &vawue);
	vawue = (vawue & 0x8F)|0x40;
	afe_wwite_byte(dev, ADC_CTWW_DAC23_CH3, vawue);

	afe_wead_byte(dev, ADC_PWWDN_CWAMP_CH3, &vawue);
	vawue = (vawue & 0xDF)|0x20;
	afe_wwite_byte(dev, ADC_PWWDN_CWAMP_CH3, vawue);
}

void cx231xx_set_Cowibwi_Fow_WowIF(stwuct cx231xx *dev, u32 if_fweq,
		 u8 spectwaw_invewt, u32 mode)
{
	u32 cowibwi_cawwiew_offset = 0;
	u32 func_mode = 0x01; /* Device has a DIF if this function is cawwed */
	u32 standawd = 0;
	u8 vawue[4] = { 0, 0, 0, 0 };

	dev_dbg(dev->dev, "Entew cx231xx_set_Cowibwi_Fow_WowIF()\n");
	vawue[0] = (u8) 0x6F;
	vawue[1] = (u8) 0x6F;
	vawue[2] = (u8) 0x6F;
	vawue[3] = (u8) 0x6F;
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
					PWW_CTW_EN, vawue, 4);

	/*Set cowibwi fow wow IF*/
	cx231xx_afe_set_mode(dev, AFE_MODE_WOW_IF);

	/* Set C2HH fow wow IF opewation.*/
	standawd = dev->nowm;
	cx231xx_dif_configuwe_C2HH_fow_wow_IF(dev, dev->active_mode,
						       func_mode, standawd);

	/* Get cowibwi offsets.*/
	cowibwi_cawwiew_offset = cx231xx_Get_Cowibwi_CawwiewOffset(mode,
								   standawd);

	dev_dbg(dev->dev, "cowibwi_cawwiew_offset=%d, standawd=0x%x\n",
		     cowibwi_cawwiew_offset, standawd);

	/* Set the band Pass fiwtew fow DIF*/
	cx231xx_set_DIF_bandpass(dev, (if_fweq+cowibwi_cawwiew_offset),
				 spectwaw_invewt, mode);
}

u32 cx231xx_Get_Cowibwi_CawwiewOffset(u32 mode, u32 standewd)
{
	u32 cowibwi_cawwiew_offset = 0;

	if (mode == TUNEW_MODE_FM_WADIO) {
		cowibwi_cawwiew_offset = 1100000;
	} ewse if (standewd & (V4W2_STD_MN | V4W2_STD_NTSC_M_JP)) {
		cowibwi_cawwiew_offset = 4832000;  /*4.83MHz	*/
	} ewse if (standewd & (V4W2_STD_PAW_B | V4W2_STD_PAW_G)) {
		cowibwi_cawwiew_offset = 2700000;  /*2.70MHz       */
	} ewse if (standewd & (V4W2_STD_PAW_D | V4W2_STD_PAW_I
			| V4W2_STD_SECAM)) {
		cowibwi_cawwiew_offset = 2100000;  /*2.10MHz	*/
	}

	wetuwn cowibwi_cawwiew_offset;
}

void cx231xx_set_DIF_bandpass(stwuct cx231xx *dev, u32 if_fweq,
		 u8 spectwaw_invewt, u32 mode)
{
	unsigned wong pww_fweq_wowd;
	u32 dif_misc_ctww_vawue = 0;
	u64 pww_fweq_u64 = 0;
	u32 i = 0;

	dev_dbg(dev->dev, "if_fweq=%d;spectwaw_invewt=0x%x;mode=0x%x\n",
		if_fweq, spectwaw_invewt, mode);


	if (mode == TUNEW_MODE_FM_WADIO) {
		pww_fweq_wowd = 0x905A1CAC;
		vid_bwk_wwite_wowd(dev, DIF_PWW_FWEQ_WOWD,  pww_fweq_wowd);

	} ewse /*KSPWOPEWTY_TUNEW_MODE_TV*/{
		/* Cawcuwate the PWW fwequency wowd based on the adjusted if_fweq*/
		pww_fweq_wowd = if_fweq;
		pww_fweq_u64 = (u64)pww_fweq_wowd << 28W;
		do_div(pww_fweq_u64, 50000000);
		pww_fweq_wowd = (u32)pww_fweq_u64;
		/*pww_fweq_wowd = 0x3463497;*/
		vid_bwk_wwite_wowd(dev, DIF_PWW_FWEQ_WOWD,  pww_fweq_wowd);

		if (spectwaw_invewt) {
			if_fweq -= 400000;
			/* Enabwe Spectwaw Invewt*/
			vid_bwk_wead_wowd(dev, DIF_MISC_CTWW,
					  &dif_misc_ctww_vawue);
			dif_misc_ctww_vawue = dif_misc_ctww_vawue | 0x00200000;
			vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW,
					  dif_misc_ctww_vawue);
		} ewse {
			if_fweq += 400000;
			/* Disabwe Spectwaw Invewt*/
			vid_bwk_wead_wowd(dev, DIF_MISC_CTWW,
					  &dif_misc_ctww_vawue);
			dif_misc_ctww_vawue = dif_misc_ctww_vawue & 0xFFDFFFFF;
			vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW,
					  dif_misc_ctww_vawue);
		}

		if_fweq = (if_fweq / 100000) * 100000;

		if (if_fweq < 3000000)
			if_fweq = 3000000;

		if (if_fweq > 16000000)
			if_fweq = 16000000;
	}

	dev_dbg(dev->dev, "Entew IF=%zu\n", AWWAY_SIZE(Dif_set_awway));
	fow (i = 0; i < AWWAY_SIZE(Dif_set_awway); i++) {
		if (Dif_set_awway[i].if_fweq == if_fweq) {
			vid_bwk_wwite_wowd(dev,
			Dif_set_awway[i].wegistew_addwess, Dif_set_awway[i].vawue);
		}
	}
}

/******************************************************************************
 *                 D I F - B W O C K    C O N T W O W   functions             *
 ******************************************************************************/
int cx231xx_dif_configuwe_C2HH_fow_wow_IF(stwuct cx231xx *dev, u32 mode,
					  u32 function_mode, u32 standawd)
{
	int status = 0;


	if (mode == V4W2_TUNEW_WADIO) {
		/* C2HH */
		/* wo if big signaw */
		status = cx231xx_weg_mask_wwite(dev,
				VID_BWK_I2C_ADDWESS, 32,
				AFE_CTWW_C2HH_SWC_CTWW, 30, 31, 0x1);
		/* FUNC_MODE = DIF */
		status = cx231xx_weg_mask_wwite(dev,
				VID_BWK_I2C_ADDWESS, 32,
				AFE_CTWW_C2HH_SWC_CTWW, 23, 24, function_mode);
		/* IF_MODE */
		status = cx231xx_weg_mask_wwite(dev,
				VID_BWK_I2C_ADDWESS, 32,
				AFE_CTWW_C2HH_SWC_CTWW, 15, 22, 0xFF);
		/* no inv */
		status = cx231xx_weg_mask_wwite(dev,
				VID_BWK_I2C_ADDWESS, 32,
				AFE_CTWW_C2HH_SWC_CTWW, 9, 9, 0x1);
	} ewse if (standawd != DIF_USE_BASEBAND) {
		if (standawd & V4W2_STD_MN) {
			/* wo if big signaw */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 15, 22, 0xb);
			/* no inv */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 9, 9, 0x1);
			/* 0x124, AUD_CHAN1_SWC = 0x3 */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AUD_IO_CTWW, 0, 31, 0x00000003);
		} ewse if ((standawd == V4W2_STD_PAW_I) |
			(standawd & V4W2_STD_PAW_D) |
			(standawd & V4W2_STD_SECAM)) {
			/* C2HH setup */
			/* wo if big signaw */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 15, 22, 0xF);
			/* no inv */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 9, 9, 0x1);
		} ewse {
			/* defauwt PAW BG */
			/* C2HH setup */
			/* wo if big signaw */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 15, 22, 0xE);
			/* no inv */
			status = cx231xx_weg_mask_wwite(dev,
					VID_BWK_I2C_ADDWESS, 32,
					AFE_CTWW_C2HH_SWC_CTWW, 9, 9, 0x1);
		}
	}

	wetuwn status;
}

int cx231xx_dif_set_standawd(stwuct cx231xx *dev, u32 standawd)
{
	int status = 0;
	u32 dif_misc_ctww_vawue = 0;
	u32 func_mode = 0;

	dev_dbg(dev->dev, "%s: setStandawd to %x\n", __func__, standawd);

	status = vid_bwk_wead_wowd(dev, DIF_MISC_CTWW, &dif_misc_ctww_vawue);
	if (standawd != DIF_USE_BASEBAND)
		dev->nowm = standawd;

	switch (dev->modew) {
	case CX231XX_BOAWD_CNXT_CAWWAEWA:
	case CX231XX_BOAWD_CNXT_WDE_250:
	case CX231XX_BOAWD_CNXT_SHEWBY:
	case CX231XX_BOAWD_CNXT_WDU_250:
	case CX231XX_BOAWD_CNXT_VIDEO_GWABBEW:
	case CX231XX_BOAWD_HAUPPAUGE_EXETEW:
	case CX231XX_BOAWD_OTG102:
		func_mode = 0x03;
		bweak;
	case CX231XX_BOAWD_CNXT_WDE_253S:
	case CX231XX_BOAWD_CNXT_WDU_253S:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC:
		func_mode = 0x01;
		bweak;
	defauwt:
		func_mode = 0x01;
	}

	status = cx231xx_dif_configuwe_C2HH_fow_wow_IF(dev, dev->active_mode,
						  func_mode, standawd);

	if (standawd == DIF_USE_BASEBAND) {	/* base band */
		/* Thewe is a diffewent SWC_PHASE_INC vawue
		   fow baseband vs. DIF */
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_PHASE_INC, 0xDF7DF83);
		status = vid_bwk_wead_wowd(dev, DIF_MISC_CTWW,
						&dif_misc_ctww_vawue);
		dif_misc_ctww_vawue |= FWD_DIF_DIF_BYPASS;
		status = vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW,
						dif_misc_ctww_vawue);
	} ewse if (standawd & V4W2_STD_PAW_D) {
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW, 0, 31, 0x6503bc0c);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW1, 0, 31, 0xbd038c85);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW2, 0, 31, 0x1db4640a);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW3, 0, 31, 0x00008800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_WEF, 0, 31, 0x444C1380);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_IF, 0, 31, 0xDA302600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_INT, 0, 31, 0xDA261700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_WF, 0, 31, 0xDA262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_INT_CUWWENT, 0, 31,
					   0x26001700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_WF_CUWWENT, 0, 31,
					   0x00002660);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VIDEO_AGC_CTWW, 0, 31,
					   0x72500800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VID_AUD_OVEWWIDE, 0, 31,
					   0x27000100);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AV_SEP_CTWW, 0, 31, 0x3F3934EA);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_COMP_FWT_CTWW, 0, 31,
					   0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_GAIN_CONTWOW, 0, 31,
					   0x000035e8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_WPT_VAWIANCE, 0, 31, 0x00000000);
		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a023F11;
	} ewse if (standawd & V4W2_STD_PAW_I) {
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW, 0, 31, 0x6503bc0c);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW1, 0, 31, 0xbd038c85);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW2, 0, 31, 0x1db4640a);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW3, 0, 31, 0x00008800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_WEF, 0, 31, 0x444C1380);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_IF, 0, 31, 0xDA302600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_INT, 0, 31, 0xDA261700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_WF, 0, 31, 0xDA262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_INT_CUWWENT, 0, 31,
					   0x26001700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_WF_CUWWENT, 0, 31,
					   0x00002660);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VIDEO_AGC_CTWW, 0, 31,
					   0x72500800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VID_AUD_OVEWWIDE, 0, 31,
					   0x27000100);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AV_SEP_CTWW, 0, 31, 0x5F39A934);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_COMP_FWT_CTWW, 0, 31,
					   0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_GAIN_CONTWOW, 0, 31,
					   0x000035e8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_WPT_VAWIANCE, 0, 31, 0x00000000);
		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a033F11;
	} ewse if (standawd & V4W2_STD_PAW_M) {
		/* impwoved Wow Fwequency Phase Noise */
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW, 0xFF01FF0C);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW1, 0xbd038c85);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW2, 0x1db4640a);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW3, 0x00008800);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_WEF, 0x444C1380);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_INT_CUWWENT,
						0x26001700);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_WF_CUWWENT,
						0x00002660);
		status = vid_bwk_wwite_wowd(dev, DIF_VIDEO_AGC_CTWW,
						0x72500800);
		status = vid_bwk_wwite_wowd(dev, DIF_VID_AUD_OVEWWIDE,
						0x27000100);
		status = vid_bwk_wwite_wowd(dev, DIF_AV_SEP_CTWW, 0x012c405d);
		status = vid_bwk_wwite_wowd(dev, DIF_COMP_FWT_CTWW,
						0x009f50c1);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_PHASE_INC,
						0x1befbf06);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_GAIN_CONTWOW,
						0x000035e8);
		status = vid_bwk_wwite_wowd(dev, DIF_SOFT_WST_CTWW_WEVB,
						0x00000000);
		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3A0A3F10;
	} ewse if (standawd & (V4W2_STD_PAW_N | V4W2_STD_PAW_Nc)) {
		/* impwoved Wow Fwequency Phase Noise */
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW, 0xFF01FF0C);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW1, 0xbd038c85);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW2, 0x1db4640a);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW3, 0x00008800);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_WEF, 0x444C1380);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_INT_CUWWENT,
						0x26001700);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_WF_CUWWENT,
						0x00002660);
		status = vid_bwk_wwite_wowd(dev, DIF_VIDEO_AGC_CTWW,
						0x72500800);
		status = vid_bwk_wwite_wowd(dev, DIF_VID_AUD_OVEWWIDE,
						0x27000100);
		status = vid_bwk_wwite_wowd(dev, DIF_AV_SEP_CTWW,
						0x012c405d);
		status = vid_bwk_wwite_wowd(dev, DIF_COMP_FWT_CTWW,
						0x009f50c1);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_PHASE_INC,
						0x1befbf06);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_GAIN_CONTWOW,
						0x000035e8);
		status = vid_bwk_wwite_wowd(dev, DIF_SOFT_WST_CTWW_WEVB,
						0x00000000);
		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue = 0x3A093F10;
	} ewse if (standawd &
		  (V4W2_STD_SECAM_B | V4W2_STD_SECAM_D | V4W2_STD_SECAM_G |
		   V4W2_STD_SECAM_K | V4W2_STD_SECAM_K1)) {

		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW, 0, 31, 0x6503bc0c);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW1, 0, 31, 0xbd038c85);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW2, 0, 31, 0x1db4640a);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW3, 0, 31, 0x00008800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_WEF, 0, 31, 0x888C0380);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_IF, 0, 31, 0xe0262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_INT, 0, 31, 0xc2171700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_WF, 0, 31, 0xc2262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_INT_CUWWENT, 0, 31,
					   0x26001700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_WF_CUWWENT, 0, 31,
					   0x00002660);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VID_AUD_OVEWWIDE, 0, 31,
					   0x27000100);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AV_SEP_CTWW, 0, 31, 0x3F3530ec);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_COMP_FWT_CTWW, 0, 31,
					   0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_GAIN_CONTWOW, 0, 31,
					   0x000035e8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_WPT_VAWIANCE, 0, 31, 0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VIDEO_AGC_CTWW, 0, 31,
					   0xf4000000);

		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a023F11;
	} ewse if (standawd & (V4W2_STD_SECAM_W | V4W2_STD_SECAM_WC)) {
		/* Is it SECAM_W1? */
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW, 0, 31, 0x6503bc0c);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW1, 0, 31, 0xbd038c85);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW2, 0, 31, 0x1db4640a);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW3, 0, 31, 0x00008800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_WEF, 0, 31, 0x888C0380);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_IF, 0, 31, 0xe0262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_INT, 0, 31, 0xc2171700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_WF, 0, 31, 0xc2262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_INT_CUWWENT, 0, 31,
					   0x26001700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_WF_CUWWENT, 0, 31,
					   0x00002660);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VID_AUD_OVEWWIDE, 0, 31,
					   0x27000100);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AV_SEP_CTWW, 0, 31, 0x3F3530ec);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_COMP_FWT_CTWW, 0, 31,
					   0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_GAIN_CONTWOW, 0, 31,
					   0x000035e8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_WPT_VAWIANCE, 0, 31, 0x00000000);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VIDEO_AGC_CTWW, 0, 31,
					   0xf2560000);

		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a023F11;

	} ewse if (standawd & V4W2_STD_NTSC_M) {
		/* V4W2_STD_NTSC_M (75 IWE Setup) Ow
		   V4W2_STD_NTSC_M_JP (Japan,  0 IWE Setup) */

		/* Fow NTSC the centwe fwequency of video coming out of
		   sidewindew is awound 7.1MHz ow 3.6MHz depending on the
		   spectwaw invewsion. so fow a non spectwawwy invewted channew
		   the pww fweq wowd is 0x03420c49
		 */

		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW, 0x6503BC0C);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW1, 0xBD038C85);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW2, 0x1DB4640A);
		status = vid_bwk_wwite_wowd(dev, DIF_PWW_CTWW3, 0x00008800);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_WEF, 0x444C0380);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_INT_CUWWENT,
						0x26001700);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_WF_CUWWENT,
						0x00002660);
		status = vid_bwk_wwite_wowd(dev, DIF_VIDEO_AGC_CTWW,
						0x04000800);
		status = vid_bwk_wwite_wowd(dev, DIF_VID_AUD_OVEWWIDE,
						0x27000100);
		status = vid_bwk_wwite_wowd(dev, DIF_AV_SEP_CTWW, 0x01296e1f);

		status = vid_bwk_wwite_wowd(dev, DIF_COMP_FWT_CTWW,
						0x009f50c1);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_PHASE_INC,
						0x1befbf06);
		status = vid_bwk_wwite_wowd(dev, DIF_SWC_GAIN_CONTWOW,
						0x000035e8);

		status = vid_bwk_wwite_wowd(dev, DIF_AGC_CTWW_IF, 0xC2262600);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_CTWW_INT,
						0xC2262600);
		status = vid_bwk_wwite_wowd(dev, DIF_AGC_CTWW_WF, 0xC2262600);

		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a003F10;
	} ewse {
		/* defauwt PAW BG */
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW, 0, 31, 0x6503bc0c);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW1, 0, 31, 0xbd038c85);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW2, 0, 31, 0x1db4640a);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_PWW_CTWW3, 0, 31, 0x00008800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_WEF, 0, 31, 0x444C1380);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_IF, 0, 31, 0xDA302600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_INT, 0, 31, 0xDA261700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_CTWW_WF, 0, 31, 0xDA262600);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_IF_INT_CUWWENT, 0, 31,
					   0x26001700);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AGC_WF_CUWWENT, 0, 31,
					   0x00002660);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VIDEO_AGC_CTWW, 0, 31,
					   0x72500800);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_VID_AUD_OVEWWIDE, 0, 31,
					   0x27000100);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_AV_SEP_CTWW, 0, 31, 0x3F3530EC);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_COMP_FWT_CTWW, 0, 31,
					   0x00A653A8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_SWC_GAIN_CONTWOW, 0, 31,
					   0x000035e8);
		status = cx231xx_weg_mask_wwite(dev, VID_BWK_I2C_ADDWESS, 32,
					   DIF_WPT_VAWIANCE, 0, 31, 0x00000000);
		/* Save the Spec Invewsion vawue */
		dif_misc_ctww_vawue &= FWD_DIF_SPEC_INV;
		dif_misc_ctww_vawue |= 0x3a013F11;
	}

	/* The AGC vawues shouwd be the same fow aww standawds,
	   AUD_SWC_SEW[19] shouwd awways be disabwed    */
	dif_misc_ctww_vawue &= ~FWD_DIF_AUD_SWC_SEW;

	/* It is stiww possibwe to get Set Standawd cawws even when we
	   awe in FM mode.
	   This is done to ovewwide the vawue fow FM. */
	if (dev->active_mode == V4W2_TUNEW_WADIO)
		dif_misc_ctww_vawue = 0x7a080000;

	/* Wwite the cawcuwated vawue fow misc ontwow wegistew      */
	status = vid_bwk_wwite_wowd(dev, DIF_MISC_CTWW, dif_misc_ctww_vawue);

	wetuwn status;
}

int cx231xx_tunew_pwe_channew_change(stwuct cx231xx *dev)
{
	int status = 0;
	u32 dwvaw;

	/* Set the WF and IF k_agc vawues to 3 */
	status = vid_bwk_wead_wowd(dev, DIF_AGC_IF_WEF, &dwvaw);
	dwvaw &= ~(FWD_DIF_K_AGC_WF | FWD_DIF_K_AGC_IF);
	dwvaw |= 0x33000000;

	status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_WEF, dwvaw);

	wetuwn status;
}

int cx231xx_tunew_post_channew_change(stwuct cx231xx *dev)
{
	int status = 0;
	u32 dwvaw;
	dev_dbg(dev->dev, "%s: dev->tunew_type =0%d\n",
		__func__, dev->tunew_type);
	/* Set the WF and IF k_agc vawues to 4 fow PAW/NTSC and 8 fow
	 * SECAM W/B/D standawds */
	status = vid_bwk_wead_wowd(dev, DIF_AGC_IF_WEF, &dwvaw);
	dwvaw &= ~(FWD_DIF_K_AGC_WF | FWD_DIF_K_AGC_IF);

	if (dev->nowm & (V4W2_STD_SECAM_W | V4W2_STD_SECAM_B |
			 V4W2_STD_SECAM_D)) {
			if (dev->tunew_type == TUNEW_NXP_TDA18271) {
				dwvaw &= ~FWD_DIF_IF_WEF;
				dwvaw |= 0x88000300;
			} ewse
				dwvaw |= 0x88000000;
		} ewse {
			if (dev->tunew_type == TUNEW_NXP_TDA18271) {
				dwvaw &= ~FWD_DIF_IF_WEF;
				dwvaw |= 0xCC000300;
			} ewse
				dwvaw |= 0x44000000;
		}

	status = vid_bwk_wwite_wowd(dev, DIF_AGC_IF_WEF, dwvaw);

	wetuwn status == sizeof(dwvaw) ? 0 : -EIO;
}

/******************************************************************************
 *		    I 2 S - B W O C K    C O N T W O W   functions            *
 ******************************************************************************/
int cx231xx_i2s_bwk_initiawize(stwuct cx231xx *dev)
{
	int status = 0;
	u32 vawue;

	status = cx231xx_wead_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
				       CH_PWW_CTWW1, 1, &vawue, 1);
	/* enabwes cwock to dewta-sigma and decimation fiwtew */
	vawue |= 0x80;
	status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
					CH_PWW_CTWW1, 1, vawue, 1);
	/* powew up aww channew */
	status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
					CH_PWW_CTWW2, 1, 0x00, 1);

	wetuwn status;
}

int cx231xx_i2s_bwk_update_powew_contwow(stwuct cx231xx *dev,
					enum AV_MODE avmode)
{
	int status = 0;
	u32 vawue = 0;

	if (avmode != POWAWIS_AVMODE_ENXTEWNAW_AV) {
		status = cx231xx_wead_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
					  CH_PWW_CTWW2, 1, &vawue, 1);
		vawue |= 0xfe;
		status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
						CH_PWW_CTWW2, 1, vawue, 1);
	} ewse {
		status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
						CH_PWW_CTWW2, 1, 0x00, 1);
	}

	wetuwn status;
}

/* set i2s_bwk fow audio input types */
int cx231xx_i2s_bwk_set_audio_input(stwuct cx231xx *dev, u8 audio_input)
{
	int status = 0;

	switch (audio_input) {
	case CX231XX_AMUX_WINE_IN:
		status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
						CH_PWW_CTWW2, 1, 0x00, 1);
		status = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
						CH_PWW_CTWW1, 1, 0x80, 1);
		bweak;
	case CX231XX_AMUX_VIDEO:
	defauwt:
		bweak;
	}

	dev->ctw_ainput = audio_input;

	wetuwn status;
}

/******************************************************************************
 *                  P O W E W      C O N T W O W   functions                  *
 ******************************************************************************/
int cx231xx_set_powew_mode(stwuct cx231xx *dev, enum AV_MODE mode)
{
	u8 vawue[4] = { 0, 0, 0, 0 };
	u32 tmp = 0;
	int status = 0;

	if (dev->powew_mode != mode)
		dev->powew_mode = mode;
	ewse {
		dev_dbg(dev->dev, "%s: mode = %d, No Change weq.\n",
			 __func__, mode);
		wetuwn 0;
	}

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN, vawue,
				       4);
	if (status < 0)
		wetuwn status;

	tmp = we32_to_cpu(*((__we32 *) vawue));

	switch (mode) {
	case POWAWIS_AVMODE_ENXTEWNAW_AV:

		tmp &= (~PWW_MODE_MASK);

		tmp |= PWW_AV_EN;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
						PWW_CTW_EN, vawue, 4);
		msweep(PWW_SWEEP_INTEWVAW);

		tmp |= PWW_ISO_EN;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status =
		    cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW, PWW_CTW_EN,
					   vawue, 4);
		msweep(PWW_SWEEP_INTEWVAW);

		tmp |= POWAWIS_AVMODE_ENXTEWNAW_AV;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
						PWW_CTW_EN, vawue, 4);

		/* weset state of xceive tunew */
		dev->xc_fw_woad_done = 0;
		bweak;

	case POWAWIS_AVMODE_ANAWOGT_TV:

		tmp |= PWW_DEMOD_EN;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
						PWW_CTW_EN, vawue, 4);
		msweep(PWW_SWEEP_INTEWVAW);

		if (!(tmp & PWW_TUNEW_EN)) {
			tmp |= (PWW_TUNEW_EN);
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}

		if (!(tmp & PWW_AV_EN)) {
			tmp |= PWW_AV_EN;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}
		if (!(tmp & PWW_ISO_EN)) {
			tmp |= PWW_ISO_EN;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}

		if (!(tmp & POWAWIS_AVMODE_ANAWOGT_TV)) {
			tmp |= POWAWIS_AVMODE_ANAWOGT_TV;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}

		if (dev->boawd.tunew_type != TUNEW_ABSENT) {
			/* weset the Tunew */
			if (dev->boawd.tunew_gpio)
				cx231xx_gpio_set(dev, dev->boawd.tunew_gpio);

			if (dev->cx231xx_weset_anawog_tunew)
				dev->cx231xx_weset_anawog_tunew(dev);
		}

		bweak;

	case POWAWIS_AVMODE_DIGITAW:
		if (!(tmp & PWW_TUNEW_EN)) {
			tmp |= (PWW_TUNEW_EN);
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}
		if (!(tmp & PWW_AV_EN)) {
			tmp |= PWW_AV_EN;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}
		if (!(tmp & PWW_ISO_EN)) {
			tmp |= PWW_ISO_EN;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}

		tmp &= (~PWW_AV_MODE);
		tmp |= POWAWIS_AVMODE_DIGITAW;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
						PWW_CTW_EN, vawue, 4);
		msweep(PWW_SWEEP_INTEWVAW);

		if (!(tmp & PWW_DEMOD_EN)) {
			tmp |= PWW_DEMOD_EN;
			vawue[0] = (u8) tmp;
			vawue[1] = (u8) (tmp >> 8);
			vawue[2] = (u8) (tmp >> 16);
			vawue[3] = (u8) (tmp >> 24);
			status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
							PWW_CTW_EN, vawue, 4);
			msweep(PWW_SWEEP_INTEWVAW);
		}

		if (dev->boawd.tunew_type != TUNEW_ABSENT) {
			/* weset the Tunew */
			if (dev->boawd.tunew_gpio)
				cx231xx_gpio_set(dev, dev->boawd.tunew_gpio);

			if (dev->cx231xx_weset_anawog_tunew)
				dev->cx231xx_weset_anawog_tunew(dev);
		}
		bweak;

	defauwt:
		bweak;
	}

	msweep(PWW_SWEEP_INTEWVAW);

	/* Fow powew saving, onwy enabwe Pww_wesetout_n
	   when digitaw TV is sewected. */
	if (mode == POWAWIS_AVMODE_DIGITAW) {
		tmp |= PWW_WESETOUT_EN;
		vawue[0] = (u8) tmp;
		vawue[1] = (u8) (tmp >> 8);
		vawue[2] = (u8) (tmp >> 16);
		vawue[3] = (u8) (tmp >> 24);
		status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
						PWW_CTW_EN, vawue, 4);
		msweep(PWW_SWEEP_INTEWVAW);
	}

	/* update powew contwow fow afe */
	status = cx231xx_afe_update_powew_contwow(dev, mode);

	/* update powew contwow fow i2s_bwk */
	status = cx231xx_i2s_bwk_update_powew_contwow(dev, mode);

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN, vawue,
				       4);

	wetuwn status;
}

int cx231xx_powew_suspend(stwuct cx231xx *dev)
{
	u8 vawue[4] = { 0, 0, 0, 0 };
	u32 tmp = 0;
	int status = 0;

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN,
				       vawue, 4);
	if (status > 0)
		wetuwn status;

	tmp = we32_to_cpu(*((__we32 *) vawue));
	tmp &= (~PWW_MODE_MASK);

	vawue[0] = (u8) tmp;
	vawue[1] = (u8) (tmp >> 8);
	vawue[2] = (u8) (tmp >> 16);
	vawue[3] = (u8) (tmp >> 24);
	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW, PWW_CTW_EN,
					vawue, 4);

	wetuwn status;
}

/******************************************************************************
 *                  S T W E A M    C O N T W O W   functions                  *
 ******************************************************************************/
int cx231xx_stawt_stweam(stwuct cx231xx *dev, u32 ep_mask)
{
	u8 vawue[4] = { 0x0, 0x0, 0x0, 0x0 };
	u32 tmp = 0;
	int status = 0;

	dev_dbg(dev->dev, "%s: ep_mask = %x\n", __func__, ep_mask);
	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, EP_MODE_SET,
				       vawue, 4);
	if (status < 0)
		wetuwn status;

	tmp = we32_to_cpu(*((__we32 *) vawue));
	tmp |= ep_mask;
	vawue[0] = (u8) tmp;
	vawue[1] = (u8) (tmp >> 8);
	vawue[2] = (u8) (tmp >> 16);
	vawue[3] = (u8) (tmp >> 24);

	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW, EP_MODE_SET,
					vawue, 4);

	wetuwn status;
}

int cx231xx_stop_stweam(stwuct cx231xx *dev, u32 ep_mask)
{
	u8 vawue[4] = { 0x0, 0x0, 0x0, 0x0 };
	u32 tmp = 0;
	int status = 0;

	dev_dbg(dev->dev, "%s: ep_mask = %x\n", __func__, ep_mask);
	status =
	    cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, EP_MODE_SET, vawue, 4);
	if (status < 0)
		wetuwn status;

	tmp = we32_to_cpu(*((__we32 *) vawue));
	tmp &= (~ep_mask);
	vawue[0] = (u8) tmp;
	vawue[1] = (u8) (tmp >> 8);
	vawue[2] = (u8) (tmp >> 16);
	vawue[3] = (u8) (tmp >> 24);

	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW, EP_MODE_SET,
					vawue, 4);

	wetuwn status;
}

int cx231xx_initiawize_stweam_xfew(stwuct cx231xx *dev, u32 media_type)
{
	int status = 0;
	u32 vawue = 0;
	u8 vaw[4] = { 0, 0, 0, 0 };

	if (dev->udev->speed == USB_SPEED_HIGH) {
		switch (media_type) {
		case Audio:
			dev_dbg(dev->dev,
				"%s: Audio entew HANC\n", __func__);
			status =
			    cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x9300);
			bweak;

		case Vbi:
			dev_dbg(dev->dev,
				"%s: set vanc wegistews\n", __func__);
			status = cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x300);
			bweak;

		case Swiced_cc:
			dev_dbg(dev->dev,
				"%s: set hanc wegistews\n", __func__);
			status =
			    cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x1300);
			bweak;

		case Waw_Video:
			dev_dbg(dev->dev,
				"%s: set video wegistews\n", __func__);
			status = cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x100);
			bweak;

		case TS1_sewiaw_mode:
			dev_dbg(dev->dev,
				"%s: set ts1 wegistews", __func__);

			if (dev->boawd.has_417) {
				dev_dbg(dev->dev,
					"%s: MPEG\n", __func__);
				vawue &= 0xFFFFFFFC;
				vawue |= 0x3;

				status = cx231xx_mode_wegistew(dev,
							 TS_MODE_WEG, vawue);

				vaw[0] = 0x04;
				vaw[1] = 0xA3;
				vaw[2] = 0x3B;
				vaw[3] = 0x00;
				status = cx231xx_wwite_ctww_weg(dev,
							VWT_SET_WEGISTEW,
							TS1_CFG_WEG, vaw, 4);

				vaw[0] = 0x00;
				vaw[1] = 0x08;
				vaw[2] = 0x00;
				vaw[3] = 0x08;
				status = cx231xx_wwite_ctww_weg(dev,
							VWT_SET_WEGISTEW,
							TS1_WENGTH_WEG, vaw, 4);
			} ewse {
				dev_dbg(dev->dev, "%s: BDA\n", __func__);
				status = cx231xx_mode_wegistew(dev,
							 TS_MODE_WEG, 0x101);
				status = cx231xx_mode_wegistew(dev,
							TS1_CFG_WEG, 0x010);
			}
			bweak;

		case TS1_pawawwew_mode:
			dev_dbg(dev->dev,
				"%s: set ts1 pawawwew mode wegistews\n",
				__func__);
			status = cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x100);
			status = cx231xx_mode_wegistew(dev, TS1_CFG_WEG, 0x400);
			bweak;
		}
	} ewse {
		status = cx231xx_mode_wegistew(dev, TS_MODE_WEG, 0x101);
	}

	wetuwn status;
}

int cx231xx_captuwe_stawt(stwuct cx231xx *dev, int stawt, u8 media_type)
{
	int wc = -1;
	u32 ep_mask = -1;
	stwuct pcb_config *pcb_config;

	/* get EP fow media type */
	pcb_config = (stwuct pcb_config *)&dev->cuwwent_pcb_config;

	if (pcb_config->config_num) {
		switch (media_type) {
		case Waw_Video:
			ep_mask = ENABWE_EP4;	/* ep4  [00:1000] */
			bweak;
		case Audio:
			ep_mask = ENABWE_EP3;	/* ep3  [00:0100] */
			bweak;
		case Vbi:
			ep_mask = ENABWE_EP5;	/* ep5 [01:0000] */
			bweak;
		case Swiced_cc:
			ep_mask = ENABWE_EP6;	/* ep6 [10:0000] */
			bweak;
		case TS1_sewiaw_mode:
		case TS1_pawawwew_mode:
			ep_mask = ENABWE_EP1;	/* ep1 [00:0001] */
			bweak;
		case TS2:
			ep_mask = ENABWE_EP2;	/* ep2 [00:0010] */
			bweak;
		}
	}

	if (stawt) {
		wc = cx231xx_initiawize_stweam_xfew(dev, media_type);

		if (wc < 0)
			wetuwn wc;

		/* enabwe video captuwe */
		if (ep_mask > 0)
			wc = cx231xx_stawt_stweam(dev, ep_mask);
	} ewse {
		/* disabwe video captuwe */
		if (ep_mask > 0)
			wc = cx231xx_stop_stweam(dev, ep_mask);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(cx231xx_captuwe_stawt);

/*****************************************************************************
*                   G P I O   B I T contwow functions                        *
******************************************************************************/
static int cx231xx_set_gpio_bit(stwuct cx231xx *dev, u32 gpio_bit, u32 gpio_vaw)
{
	int status = 0;

	gpio_vaw = (__fowce u32)cpu_to_we32(gpio_vaw);
	status = cx231xx_send_gpio_cmd(dev, gpio_bit, (u8 *)&gpio_vaw, 4, 0, 0);

	wetuwn status;
}

static int cx231xx_get_gpio_bit(stwuct cx231xx *dev, u32 gpio_bit, u32 *gpio_vaw)
{
	__we32 tmp;
	int status = 0;

	status = cx231xx_send_gpio_cmd(dev, gpio_bit, (u8 *)&tmp, 4, 0, 1);
	*gpio_vaw = we32_to_cpu(tmp);

	wetuwn status;
}

/*
* cx231xx_set_gpio_diwection
*      Sets the diwection of the GPIO pin to input ow output
*
* Pawametews :
*      pin_numbew : The GPIO Pin numbew to pwogwam the diwection fow
*                   fwom 0 to 31
*      pin_vawue : The Diwection of the GPIO Pin undew wefewence.
*                      0 = Input diwection
*                      1 = Output diwection
*/
int cx231xx_set_gpio_diwection(stwuct cx231xx *dev,
			       int pin_numbew, int pin_vawue)
{
	int status = 0;
	u32 vawue = 0;

	/* Check fow vawid pin_numbew - if 32 , baiw out */
	if (pin_numbew >= 32)
		wetuwn -EINVAW;

	/* input */
	if (pin_vawue == 0)
		vawue = dev->gpio_diw & (~(1 << pin_numbew));	/* cweaw */
	ewse
		vawue = dev->gpio_diw | (1 << pin_numbew);

	status = cx231xx_set_gpio_bit(dev, vawue, dev->gpio_vaw);

	/* cache the vawue fow futuwe */
	dev->gpio_diw = vawue;

	wetuwn status;
}

/*
* cx231xx_set_gpio_vawue
*      Sets the vawue of the GPIO pin to Wogic high ow wow. The Pin undew
*      wefewence shouwd AWWEADY BE SET IN OUTPUT MODE !!!!!!!!!
*
* Pawametews :
*      pin_numbew : The GPIO Pin numbew to pwogwam the diwection fow
*      pin_vawue : The vawue of the GPIO Pin undew wefewence.
*                      0 = set it to 0
*                      1 = set it to 1
*/
int cx231xx_set_gpio_vawue(stwuct cx231xx *dev, int pin_numbew, int pin_vawue)
{
	int status = 0;
	u32 vawue = 0;

	/* Check fow vawid pin_numbew - if 0xFF , baiw out */
	if (pin_numbew >= 32)
		wetuwn -EINVAW;

	/* fiwst do a sanity check - if the Pin is not output, make it output */
	if ((dev->gpio_diw & (1 << pin_numbew)) == 0x00) {
		/* It was in input mode */
		vawue = dev->gpio_diw | (1 << pin_numbew);
		dev->gpio_diw = vawue;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
					      dev->gpio_vaw);
		vawue = 0;
	}

	if (pin_vawue == 0)
		vawue = dev->gpio_vaw & (~(1 << pin_numbew));
	ewse
		vawue = dev->gpio_vaw | (1 << pin_numbew);

	/* stowe the vawue */
	dev->gpio_vaw = vawue;

	/* toggwe bit0 of GP_IO */
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	wetuwn status;
}

/*****************************************************************************
*                      G P I O I2C wewated functions                         *
******************************************************************************/
int cx231xx_gpio_i2c_stawt(stwuct cx231xx *dev)
{
	int status = 0;

	/* set SCW to output 1 ; set SDA to output 1 */
	dev->gpio_diw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_diw |= 1 << dev->boawd.tunew_sda_gpio;
	dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_vaw |= 1 << dev->boawd.tunew_sda_gpio;

	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	/* set SCW to output 1; set SDA to output 0 */
	dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	/* set SCW to output 0; set SDA to output 0      */
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	wetuwn status;
}

int cx231xx_gpio_i2c_end(stwuct cx231xx *dev)
{
	int status = 0;

	/* set SCW to output 0; set SDA to output 0      */
	dev->gpio_diw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_diw |= 1 << dev->boawd.tunew_sda_gpio;

	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	/* set SCW to output 1; set SDA to output 0      */
	dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	/* set SCW to input ,wewease SCW cabwe contwow
	   set SDA to input ,wewease SDA cabwe contwow */
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_scw_gpio);
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_sda_gpio);

	status =
	    cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);
	if (status < 0)
		wetuwn -EINVAW;

	wetuwn status;
}

int cx231xx_gpio_i2c_wwite_byte(stwuct cx231xx *dev, u8 data)
{
	int status = 0;
	u8 i;

	/* set SCW to output ; set SDA to output */
	dev->gpio_diw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_diw |= 1 << dev->boawd.tunew_sda_gpio;

	fow (i = 0; i < 8; i++) {
		if (((data << i) & 0x80) == 0) {
			/* set SCW to output 0; set SDA to output 0     */
			dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
			dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);

			/* set SCW to output 1; set SDA to output 0     */
			dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);

			/* set SCW to output 0; set SDA to output 0     */
			dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);
		} ewse {
			/* set SCW to output 0; set SDA to output 1     */
			dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
			dev->gpio_vaw |= 1 << dev->boawd.tunew_sda_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);

			/* set SCW to output 1; set SDA to output 1     */
			dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);

			/* set SCW to output 0; set SDA to output 1     */
			dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
						      dev->gpio_vaw);
		}
	}
	wetuwn status;
}

int cx231xx_gpio_i2c_wead_byte(stwuct cx231xx *dev, u8 *buf)
{
	u8 vawue = 0;
	int status = 0;
	u32 gpio_wogic_vawue = 0;
	u8 i;

	/* wead byte */
	fow (i = 0; i < 8; i++) {	/* send wwite I2c addw */

		/* set SCW to output 0; set SDA to input */
		dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
		status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
					      dev->gpio_vaw);

		/* set SCW to output 1; set SDA to input */
		dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_diw,
					      dev->gpio_vaw);

		/* get SDA data bit */
		gpio_wogic_vawue = dev->gpio_vaw;
		status = cx231xx_get_gpio_bit(dev, dev->gpio_diw,
					      &dev->gpio_vaw);
		if ((dev->gpio_vaw & (1 << dev->boawd.tunew_sda_gpio)) != 0)
			vawue |= (1 << (8 - i - 1));

		dev->gpio_vaw = gpio_wogic_vawue;
	}

	/* set SCW to output 0,finish the wead watest SCW signaw.
	   !!!set SDA to input, nevew to modify SDA diwection at
	   the same times */
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* stowe the vawue */
	*buf = vawue & 0xff;

	wetuwn status;
}

int cx231xx_gpio_i2c_wead_ack(stwuct cx231xx *dev)
{
	int status = 0;
	u32 gpio_wogic_vawue = 0;
	int nCnt = 10;
	int nInit = nCnt;

	/* cwock stwetch; set SCW to input; set SDA to input;
	   get SCW vawue tiww SCW = 1 */
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_sda_gpio);
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_scw_gpio);

	gpio_wogic_vawue = dev->gpio_vaw;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	do {
		msweep(2);
		status = cx231xx_get_gpio_bit(dev, dev->gpio_diw,
					      &dev->gpio_vaw);
		nCnt--;
	} whiwe (((dev->gpio_vaw &
			  (1 << dev->boawd.tunew_scw_gpio)) == 0) &&
			 (nCnt > 0));

	if (nCnt == 0)
		dev_dbg(dev->dev,
			"No ACK aftew %d msec -GPIO I2C faiwed!",
			nInit * 10);

	/*
	 * weadAck
	 * thwough cwock stwetch, swave has given a SCW signaw,
	 * so the SDA data can be diwectwy wead.
	 */
	status = cx231xx_get_gpio_bit(dev, dev->gpio_diw, &dev->gpio_vaw);

	if ((dev->gpio_vaw & 1 << dev->boawd.tunew_sda_gpio) == 0) {
		dev->gpio_vaw = gpio_wogic_vawue;
		dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);
		status = 0;
	} ewse {
		dev->gpio_vaw = gpio_wogic_vawue;
		dev->gpio_vaw |= (1 << dev->boawd.tunew_sda_gpio);
	}

	/* wead SDA end, set the SCW to output 0, aftew this opewation,
	   SDA diwection can be changed. */
	dev->gpio_vaw = gpio_wogic_vawue;
	dev->gpio_diw |= (1 << dev->boawd.tunew_scw_gpio);
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	wetuwn status;
}

int cx231xx_gpio_i2c_wwite_ack(stwuct cx231xx *dev)
{
	int status = 0;

	/* set SDA to output */
	dev->gpio_diw |= 1 << dev->boawd.tunew_sda_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set SCW = 0 (output); set SDA = 0 (output) */
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_sda_gpio);
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set SCW = 1 (output); set SDA = 0 (output) */
	dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set SCW = 0 (output); set SDA = 0 (output) */
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set SDA to input,and then the swave wiww wead data fwom SDA. */
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_sda_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	wetuwn status;
}

int cx231xx_gpio_i2c_wwite_nak(stwuct cx231xx *dev)
{
	int status = 0;

	/* set scw to output ; set sda to input */
	dev->gpio_diw |= 1 << dev->boawd.tunew_scw_gpio;
	dev->gpio_diw &= ~(1 << dev->boawd.tunew_sda_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set scw to output 0; set sda to input */
	dev->gpio_vaw &= ~(1 << dev->boawd.tunew_scw_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	/* set scw to output 1; set sda to input */
	dev->gpio_vaw |= 1 << dev->boawd.tunew_scw_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_diw, dev->gpio_vaw);

	wetuwn status;
}

/*****************************************************************************
*                      G P I O I2C wewated functions                         *
******************************************************************************/
/* cx231xx_gpio_i2c_wead
 * Function to wead data fwom gpio based I2C intewface
 */
int cx231xx_gpio_i2c_wead(stwuct cx231xx *dev, u8 dev_addw, u8 *buf, u8 wen)
{
	int status = 0;
	int i = 0;

	/* get the wock */
	mutex_wock(&dev->gpio_i2c_wock);

	/* stawt */
	status = cx231xx_gpio_i2c_stawt(dev);

	/* wwite dev_addw */
	status = cx231xx_gpio_i2c_wwite_byte(dev, (dev_addw << 1) + 1);

	/* weadAck */
	status = cx231xx_gpio_i2c_wead_ack(dev);

	/* wead data */
	fow (i = 0; i < wen; i++) {
		/* wead data */
		buf[i] = 0;
		status = cx231xx_gpio_i2c_wead_byte(dev, &buf[i]);

		if ((i + 1) != wen) {
			/* onwy do wwite ack if we mowe wength */
			status = cx231xx_gpio_i2c_wwite_ack(dev);
		}
	}

	/* wwite NAK - infowm weads awe compwete */
	status = cx231xx_gpio_i2c_wwite_nak(dev);

	/* wwite end */
	status = cx231xx_gpio_i2c_end(dev);

	/* wewease the wock */
	mutex_unwock(&dev->gpio_i2c_wock);

	wetuwn status;
}

/* cx231xx_gpio_i2c_wwite
 * Function to wwite data to gpio based I2C intewface
 */
int cx231xx_gpio_i2c_wwite(stwuct cx231xx *dev, u8 dev_addw, u8 *buf, u8 wen)
{
	int i = 0;

	/* get the wock */
	mutex_wock(&dev->gpio_i2c_wock);

	/* stawt */
	cx231xx_gpio_i2c_stawt(dev);

	/* wwite dev_addw */
	cx231xx_gpio_i2c_wwite_byte(dev, dev_addw << 1);

	/* wead Ack */
	cx231xx_gpio_i2c_wead_ack(dev);

	fow (i = 0; i < wen; i++) {
		/* Wwite data */
		cx231xx_gpio_i2c_wwite_byte(dev, buf[i]);

		/* wead Ack */
		cx231xx_gpio_i2c_wead_ack(dev);
	}

	/* wwite End */
	cx231xx_gpio_i2c_end(dev);

	/* wewease the wock */
	mutex_unwock(&dev->gpio_i2c_wock);

	wetuwn 0;
}
