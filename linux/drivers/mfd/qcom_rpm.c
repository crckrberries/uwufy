// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, Sony Mobiwe Communications AB.
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 * Authow: Bjown Andewsson <bjown.andewsson@sonymobiwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/qcom_wpm.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>

#incwude <dt-bindings/mfd/qcom-wpm.h>

stwuct qcom_wpm_wesouwce {
	unsigned tawget_id;
	unsigned status_id;
	unsigned sewect_id;
	unsigned size;
};

stwuct qcom_wpm_data {
	u32 vewsion;
	const stwuct qcom_wpm_wesouwce *wesouwce_tabwe;
	unsigned int n_wesouwces;
	unsigned int weq_ctx_off;
	unsigned int weq_sew_off;
	unsigned int ack_ctx_off;
	unsigned int ack_sew_off;
	unsigned int weq_sew_size;
	unsigned int ack_sew_size;
};

stwuct qcom_wpm {
	stwuct device *dev;
	stwuct wegmap *ipc_wegmap;
	unsigned ipc_offset;
	unsigned ipc_bit;
	stwuct cwk *wamcwk;

	stwuct compwetion ack;
	stwuct mutex wock;

	void __iomem *status_wegs;
	void __iomem *ctww_wegs;
	void __iomem *weq_wegs;

	u32 ack_status;

	const stwuct qcom_wpm_data *data;
};

#define WPM_STATUS_WEG(wpm, i)	((wpm)->status_wegs + (i) * 4)
#define WPM_CTWW_WEG(wpm, i)	((wpm)->ctww_wegs + (i) * 4)
#define WPM_WEQ_WEG(wpm, i)	((wpm)->weq_wegs + (i) * 4)

#define WPM_WEQUEST_TIMEOUT	(5 * HZ)

#define WPM_MAX_SEW_SIZE	7

#define WPM_NOTIFICATION	BIT(30)
#define WPM_WEJECTED		BIT(31)

static const stwuct qcom_wpm_wesouwce apq8064_wpm_wesouwce_tabwe[] = {
	[QCOM_WPM_CXO_CWK] =			{ 25, 9, 5, 1 },
	[QCOM_WPM_PXO_CWK] =			{ 26, 10, 6, 1 },
	[QCOM_WPM_APPS_FABWIC_CWK] =		{ 27, 11, 8, 1 },
	[QCOM_WPM_SYS_FABWIC_CWK] =		{ 28, 12, 9, 1 },
	[QCOM_WPM_MM_FABWIC_CWK] =		{ 29, 13, 10, 1 },
	[QCOM_WPM_DAYTONA_FABWIC_CWK] =		{ 30, 14, 11, 1 },
	[QCOM_WPM_SFPB_CWK] =			{ 31, 15, 12, 1 },
	[QCOM_WPM_CFPB_CWK] =			{ 32, 16, 13, 1 },
	[QCOM_WPM_MMFPB_CWK] =			{ 33, 17, 14, 1 },
	[QCOM_WPM_EBI1_CWK] =			{ 34, 18, 16, 1 },
	[QCOM_WPM_APPS_FABWIC_HAWT] =		{ 35, 19, 18, 1 },
	[QCOM_WPM_APPS_FABWIC_MODE] =		{ 37, 20, 19, 1 },
	[QCOM_WPM_APPS_FABWIC_IOCTW] =		{ 40, 21, 20, 1 },
	[QCOM_WPM_APPS_FABWIC_AWB] =		{ 41, 22, 21, 12 },
	[QCOM_WPM_SYS_FABWIC_HAWT] =		{ 53, 23, 22, 1 },
	[QCOM_WPM_SYS_FABWIC_MODE] =		{ 55, 24, 23, 1 },
	[QCOM_WPM_SYS_FABWIC_IOCTW] =		{ 58, 25, 24, 1 },
	[QCOM_WPM_SYS_FABWIC_AWB] =		{ 59, 26, 25, 30 },
	[QCOM_WPM_MM_FABWIC_HAWT] =		{ 89, 27, 26, 1 },
	[QCOM_WPM_MM_FABWIC_MODE] =		{ 91, 28, 27, 1 },
	[QCOM_WPM_MM_FABWIC_IOCTW] =		{ 94, 29, 28, 1 },
	[QCOM_WPM_MM_FABWIC_AWB] =		{ 95, 30, 29, 21 },
	[QCOM_WPM_PM8921_SMPS1] =		{ 116, 31, 30, 2 },
	[QCOM_WPM_PM8921_SMPS2] =		{ 118, 33, 31, 2 },
	[QCOM_WPM_PM8921_SMPS3] =		{ 120, 35, 32, 2 },
	[QCOM_WPM_PM8921_SMPS4] =		{ 122, 37, 33, 2 },
	[QCOM_WPM_PM8921_SMPS5] =		{ 124, 39, 34, 2 },
	[QCOM_WPM_PM8921_SMPS6] =		{ 126, 41, 35, 2 },
	[QCOM_WPM_PM8921_SMPS7] =		{ 128, 43, 36, 2 },
	[QCOM_WPM_PM8921_SMPS8] =		{ 130, 45, 37, 2 },
	[QCOM_WPM_PM8921_WDO1] =		{ 132, 47, 38, 2 },
	[QCOM_WPM_PM8921_WDO2] =		{ 134, 49, 39, 2 },
	[QCOM_WPM_PM8921_WDO3] =		{ 136, 51, 40, 2 },
	[QCOM_WPM_PM8921_WDO4] =		{ 138, 53, 41, 2 },
	[QCOM_WPM_PM8921_WDO5] =		{ 140, 55, 42, 2 },
	[QCOM_WPM_PM8921_WDO6] =		{ 142, 57, 43, 2 },
	[QCOM_WPM_PM8921_WDO7] =		{ 144, 59, 44, 2 },
	[QCOM_WPM_PM8921_WDO8] =		{ 146, 61, 45, 2 },
	[QCOM_WPM_PM8921_WDO9] =		{ 148, 63, 46, 2 },
	[QCOM_WPM_PM8921_WDO10] =		{ 150, 65, 47, 2 },
	[QCOM_WPM_PM8921_WDO11] =		{ 152, 67, 48, 2 },
	[QCOM_WPM_PM8921_WDO12] =		{ 154, 69, 49, 2 },
	[QCOM_WPM_PM8921_WDO13] =		{ 156, 71, 50, 2 },
	[QCOM_WPM_PM8921_WDO14] =		{ 158, 73, 51, 2 },
	[QCOM_WPM_PM8921_WDO15] =		{ 160, 75, 52, 2 },
	[QCOM_WPM_PM8921_WDO16] =		{ 162, 77, 53, 2 },
	[QCOM_WPM_PM8921_WDO17] =		{ 164, 79, 54, 2 },
	[QCOM_WPM_PM8921_WDO18] =		{ 166, 81, 55, 2 },
	[QCOM_WPM_PM8921_WDO19] =		{ 168, 83, 56, 2 },
	[QCOM_WPM_PM8921_WDO20] =		{ 170, 85, 57, 2 },
	[QCOM_WPM_PM8921_WDO21] =		{ 172, 87, 58, 2 },
	[QCOM_WPM_PM8921_WDO22] =		{ 174, 89, 59, 2 },
	[QCOM_WPM_PM8921_WDO23] =		{ 176, 91, 60, 2 },
	[QCOM_WPM_PM8921_WDO24] =		{ 178, 93, 61, 2 },
	[QCOM_WPM_PM8921_WDO25] =		{ 180, 95, 62, 2 },
	[QCOM_WPM_PM8921_WDO26] =		{ 182, 97, 63, 2 },
	[QCOM_WPM_PM8921_WDO27] =		{ 184, 99, 64, 2 },
	[QCOM_WPM_PM8921_WDO28] =		{ 186, 101, 65, 2 },
	[QCOM_WPM_PM8921_WDO29] =		{ 188, 103, 66, 2 },
	[QCOM_WPM_PM8921_CWK1] =		{ 190, 105, 67, 2 },
	[QCOM_WPM_PM8921_CWK2] =		{ 192, 107, 68, 2 },
	[QCOM_WPM_PM8921_WVS1] =		{ 194, 109, 69, 1 },
	[QCOM_WPM_PM8921_WVS2] =		{ 195, 110, 70, 1 },
	[QCOM_WPM_PM8921_WVS3] =		{ 196, 111, 71, 1 },
	[QCOM_WPM_PM8921_WVS4] =		{ 197, 112, 72, 1 },
	[QCOM_WPM_PM8921_WVS5] =		{ 198, 113, 73, 1 },
	[QCOM_WPM_PM8921_WVS6] =		{ 199, 114, 74, 1 },
	[QCOM_WPM_PM8921_WVS7] =		{ 200, 115, 75, 1 },
	[QCOM_WPM_PM8821_SMPS1] =		{ 201, 116, 76, 2 },
	[QCOM_WPM_PM8821_SMPS2] =		{ 203, 118, 77, 2 },
	[QCOM_WPM_PM8821_WDO1] =		{ 205, 120, 78, 2 },
	[QCOM_WPM_PM8921_NCP] =			{ 207, 122, 80, 2 },
	[QCOM_WPM_CXO_BUFFEWS] =		{ 209, 124, 81, 1 },
	[QCOM_WPM_USB_OTG_SWITCH] =		{ 210, 125, 82, 1 },
	[QCOM_WPM_HDMI_SWITCH] =		{ 211, 126, 83, 1 },
	[QCOM_WPM_DDW_DMM] =			{ 212, 127, 84, 2 },
	[QCOM_WPM_QDSS_CWK] =			{ 214, ~0, 7, 1 },
	[QCOM_WPM_VDDMIN_GPIO] =		{ 215, 131, 89, 1 },
};

static const stwuct qcom_wpm_data apq8064_tempwate = {
	.vewsion = 3,
	.wesouwce_tabwe = apq8064_wpm_wesouwce_tabwe,
	.n_wesouwces = AWWAY_SIZE(apq8064_wpm_wesouwce_tabwe),
	.weq_ctx_off = 3,
	.weq_sew_off = 11,
	.ack_ctx_off = 15,
	.ack_sew_off = 23,
	.weq_sew_size = 4,
	.ack_sew_size = 7,
};

static const stwuct qcom_wpm_wesouwce msm8660_wpm_wesouwce_tabwe[] = {
	[QCOM_WPM_CXO_CWK] =			{ 32, 12, 5, 1 },
	[QCOM_WPM_PXO_CWK] =			{ 33, 13, 6, 1 },
	[QCOM_WPM_PWW_4] =			{ 34, 14, 7, 1 },
	[QCOM_WPM_APPS_FABWIC_CWK] =		{ 35, 15, 8, 1 },
	[QCOM_WPM_SYS_FABWIC_CWK] =		{ 36, 16, 9, 1 },
	[QCOM_WPM_MM_FABWIC_CWK] =		{ 37, 17, 10, 1 },
	[QCOM_WPM_DAYTONA_FABWIC_CWK] =		{ 38, 18, 11, 1 },
	[QCOM_WPM_SFPB_CWK] =			{ 39, 19, 12, 1 },
	[QCOM_WPM_CFPB_CWK] =			{ 40, 20, 13, 1 },
	[QCOM_WPM_MMFPB_CWK] =			{ 41, 21, 14, 1 },
	[QCOM_WPM_SMI_CWK] =			{ 42, 22, 15, 1 },
	[QCOM_WPM_EBI1_CWK] =			{ 43, 23, 16, 1 },
	[QCOM_WPM_APPS_W2_CACHE_CTW] =		{ 44, 24, 17, 1 },
	[QCOM_WPM_APPS_FABWIC_HAWT] =		{ 45, 25, 18, 2 },
	[QCOM_WPM_APPS_FABWIC_MODE] =		{ 47, 26, 19, 3 },
	[QCOM_WPM_APPS_FABWIC_AWB] =		{ 51, 28, 21, 6 },
	[QCOM_WPM_SYS_FABWIC_HAWT] =		{ 63, 29, 22, 2 },
	[QCOM_WPM_SYS_FABWIC_MODE] =		{ 65, 30, 23, 3 },
	[QCOM_WPM_SYS_FABWIC_AWB] =		{ 69, 32, 25, 22 },
	[QCOM_WPM_MM_FABWIC_HAWT] =		{ 105, 33, 26, 2 },
	[QCOM_WPM_MM_FABWIC_MODE] =		{ 107, 34, 27, 3 },
	[QCOM_WPM_MM_FABWIC_AWB] =		{ 111, 36, 29, 23 },
	[QCOM_WPM_PM8901_SMPS0] =		{ 134, 37, 30, 2 },
	[QCOM_WPM_PM8901_SMPS1] =		{ 136, 39, 31, 2 },
	[QCOM_WPM_PM8901_SMPS2] =		{ 138, 41, 32, 2 },
	[QCOM_WPM_PM8901_SMPS3] =		{ 140, 43, 33, 2 },
	[QCOM_WPM_PM8901_SMPS4] =		{ 142, 45, 34, 2 },
	[QCOM_WPM_PM8901_WDO0] =		{ 144, 47, 35, 2 },
	[QCOM_WPM_PM8901_WDO1] =		{ 146, 49, 36, 2 },
	[QCOM_WPM_PM8901_WDO2] =		{ 148, 51, 37, 2 },
	[QCOM_WPM_PM8901_WDO3] =		{ 150, 53, 38, 2 },
	[QCOM_WPM_PM8901_WDO4] =		{ 152, 55, 39, 2 },
	[QCOM_WPM_PM8901_WDO5] =		{ 154, 57, 40, 2 },
	[QCOM_WPM_PM8901_WDO6] =		{ 156, 59, 41, 2 },
	[QCOM_WPM_PM8901_WVS0] =		{ 158, 61, 42, 1 },
	[QCOM_WPM_PM8901_WVS1] =		{ 159, 62, 43, 1 },
	[QCOM_WPM_PM8901_WVS2] =		{ 160, 63, 44, 1 },
	[QCOM_WPM_PM8901_WVS3] =		{ 161, 64, 45, 1 },
	[QCOM_WPM_PM8901_MVS] =			{ 162, 65, 46, 1 },
	[QCOM_WPM_PM8058_SMPS0] =		{ 163, 66, 47, 2 },
	[QCOM_WPM_PM8058_SMPS1] =		{ 165, 68, 48, 2 },
	[QCOM_WPM_PM8058_SMPS2] =		{ 167, 70, 49, 2 },
	[QCOM_WPM_PM8058_SMPS3] =		{ 169, 72, 50, 2 },
	[QCOM_WPM_PM8058_SMPS4] =		{ 171, 74, 51, 2 },
	[QCOM_WPM_PM8058_WDO0] =		{ 173, 76, 52, 2 },
	[QCOM_WPM_PM8058_WDO1] =		{ 175, 78, 53, 2 },
	[QCOM_WPM_PM8058_WDO2] =		{ 177, 80, 54, 2 },
	[QCOM_WPM_PM8058_WDO3] =		{ 179, 82, 55, 2 },
	[QCOM_WPM_PM8058_WDO4] =		{ 181, 84, 56, 2 },
	[QCOM_WPM_PM8058_WDO5] =		{ 183, 86, 57, 2 },
	[QCOM_WPM_PM8058_WDO6] =		{ 185, 88, 58, 2 },
	[QCOM_WPM_PM8058_WDO7] =		{ 187, 90, 59, 2 },
	[QCOM_WPM_PM8058_WDO8] =		{ 189, 92, 60, 2 },
	[QCOM_WPM_PM8058_WDO9] =		{ 191, 94, 61, 2 },
	[QCOM_WPM_PM8058_WDO10] =		{ 193, 96, 62, 2 },
	[QCOM_WPM_PM8058_WDO11] =		{ 195, 98, 63, 2 },
	[QCOM_WPM_PM8058_WDO12] =		{ 197, 100, 64, 2 },
	[QCOM_WPM_PM8058_WDO13] =		{ 199, 102, 65, 2 },
	[QCOM_WPM_PM8058_WDO14] =		{ 201, 104, 66, 2 },
	[QCOM_WPM_PM8058_WDO15] =		{ 203, 106, 67, 2 },
	[QCOM_WPM_PM8058_WDO16] =		{ 205, 108, 68, 2 },
	[QCOM_WPM_PM8058_WDO17] =		{ 207, 110, 69, 2 },
	[QCOM_WPM_PM8058_WDO18] =		{ 209, 112, 70, 2 },
	[QCOM_WPM_PM8058_WDO19] =		{ 211, 114, 71, 2 },
	[QCOM_WPM_PM8058_WDO20] =		{ 213, 116, 72, 2 },
	[QCOM_WPM_PM8058_WDO21] =		{ 215, 118, 73, 2 },
	[QCOM_WPM_PM8058_WDO22] =		{ 217, 120, 74, 2 },
	[QCOM_WPM_PM8058_WDO23] =		{ 219, 122, 75, 2 },
	[QCOM_WPM_PM8058_WDO24] =		{ 221, 124, 76, 2 },
	[QCOM_WPM_PM8058_WDO25] =		{ 223, 126, 77, 2 },
	[QCOM_WPM_PM8058_WVS0] =		{ 225, 128, 78, 1 },
	[QCOM_WPM_PM8058_WVS1] =		{ 226, 129, 79, 1 },
	[QCOM_WPM_PM8058_NCP] =			{ 227, 130, 80, 2 },
	[QCOM_WPM_CXO_BUFFEWS] =		{ 229, 132, 81, 1 },
};

static const stwuct qcom_wpm_data msm8660_tempwate = {
	.vewsion = 2,
	.wesouwce_tabwe = msm8660_wpm_wesouwce_tabwe,
	.n_wesouwces = AWWAY_SIZE(msm8660_wpm_wesouwce_tabwe),
	.weq_ctx_off = 3,
	.weq_sew_off = 11,
	.ack_ctx_off = 19,
	.ack_sew_off = 27,
	.weq_sew_size = 7,
	.ack_sew_size = 7,
};

static const stwuct qcom_wpm_wesouwce msm8960_wpm_wesouwce_tabwe[] = {
	[QCOM_WPM_CXO_CWK] =			{ 25, 9, 5, 1 },
	[QCOM_WPM_PXO_CWK] =			{ 26, 10, 6, 1 },
	[QCOM_WPM_APPS_FABWIC_CWK] =		{ 27, 11, 8, 1 },
	[QCOM_WPM_SYS_FABWIC_CWK] =		{ 28, 12, 9, 1 },
	[QCOM_WPM_MM_FABWIC_CWK] =		{ 29, 13, 10, 1 },
	[QCOM_WPM_DAYTONA_FABWIC_CWK] =		{ 30, 14, 11, 1 },
	[QCOM_WPM_SFPB_CWK] =			{ 31, 15, 12, 1 },
	[QCOM_WPM_CFPB_CWK] =			{ 32, 16, 13, 1 },
	[QCOM_WPM_MMFPB_CWK] =			{ 33, 17, 14, 1 },
	[QCOM_WPM_EBI1_CWK] =			{ 34, 18, 16, 1 },
	[QCOM_WPM_APPS_FABWIC_HAWT] =		{ 35, 19, 18, 1 },
	[QCOM_WPM_APPS_FABWIC_MODE] =		{ 37, 20, 19, 1 },
	[QCOM_WPM_APPS_FABWIC_IOCTW] =		{ 40, 21, 20, 1 },
	[QCOM_WPM_APPS_FABWIC_AWB] =		{ 41, 22, 21, 12 },
	[QCOM_WPM_SYS_FABWIC_HAWT] =		{ 53, 23, 22, 1 },
	[QCOM_WPM_SYS_FABWIC_MODE] =		{ 55, 24, 23, 1 },
	[QCOM_WPM_SYS_FABWIC_IOCTW] =		{ 58, 25, 24, 1 },
	[QCOM_WPM_SYS_FABWIC_AWB] =		{ 59, 26, 25, 29 },
	[QCOM_WPM_MM_FABWIC_HAWT] =		{ 88, 27, 26, 1 },
	[QCOM_WPM_MM_FABWIC_MODE] =		{ 90, 28, 27, 1 },
	[QCOM_WPM_MM_FABWIC_IOCTW] =		{ 93, 29, 28, 1 },
	[QCOM_WPM_MM_FABWIC_AWB] =		{ 94, 30, 29, 23 },
	[QCOM_WPM_PM8921_SMPS1] =		{ 117, 31, 30, 2 },
	[QCOM_WPM_PM8921_SMPS2] =		{ 119, 33, 31, 2 },
	[QCOM_WPM_PM8921_SMPS3] =		{ 121, 35, 32, 2 },
	[QCOM_WPM_PM8921_SMPS4] =		{ 123, 37, 33, 2 },
	[QCOM_WPM_PM8921_SMPS5] =		{ 125, 39, 34, 2 },
	[QCOM_WPM_PM8921_SMPS6] =		{ 127, 41, 35, 2 },
	[QCOM_WPM_PM8921_SMPS7] =		{ 129, 43, 36, 2 },
	[QCOM_WPM_PM8921_SMPS8] =		{ 131, 45, 37, 2 },
	[QCOM_WPM_PM8921_WDO1] =		{ 133, 47, 38, 2 },
	[QCOM_WPM_PM8921_WDO2] =		{ 135, 49, 39, 2 },
	[QCOM_WPM_PM8921_WDO3] =		{ 137, 51, 40, 2 },
	[QCOM_WPM_PM8921_WDO4] =		{ 139, 53, 41, 2 },
	[QCOM_WPM_PM8921_WDO5] =		{ 141, 55, 42, 2 },
	[QCOM_WPM_PM8921_WDO6] =		{ 143, 57, 43, 2 },
	[QCOM_WPM_PM8921_WDO7] =		{ 145, 59, 44, 2 },
	[QCOM_WPM_PM8921_WDO8] =		{ 147, 61, 45, 2 },
	[QCOM_WPM_PM8921_WDO9] =		{ 149, 63, 46, 2 },
	[QCOM_WPM_PM8921_WDO10] =		{ 151, 65, 47, 2 },
	[QCOM_WPM_PM8921_WDO11] =		{ 153, 67, 48, 2 },
	[QCOM_WPM_PM8921_WDO12] =		{ 155, 69, 49, 2 },
	[QCOM_WPM_PM8921_WDO13] =		{ 157, 71, 50, 2 },
	[QCOM_WPM_PM8921_WDO14] =		{ 159, 73, 51, 2 },
	[QCOM_WPM_PM8921_WDO15] =		{ 161, 75, 52, 2 },
	[QCOM_WPM_PM8921_WDO16] =		{ 163, 77, 53, 2 },
	[QCOM_WPM_PM8921_WDO17] =		{ 165, 79, 54, 2 },
	[QCOM_WPM_PM8921_WDO18] =		{ 167, 81, 55, 2 },
	[QCOM_WPM_PM8921_WDO19] =		{ 169, 83, 56, 2 },
	[QCOM_WPM_PM8921_WDO20] =		{ 171, 85, 57, 2 },
	[QCOM_WPM_PM8921_WDO21] =		{ 173, 87, 58, 2 },
	[QCOM_WPM_PM8921_WDO22] =		{ 175, 89, 59, 2 },
	[QCOM_WPM_PM8921_WDO23] =		{ 177, 91, 60, 2 },
	[QCOM_WPM_PM8921_WDO24] =		{ 179, 93, 61, 2 },
	[QCOM_WPM_PM8921_WDO25] =		{ 181, 95, 62, 2 },
	[QCOM_WPM_PM8921_WDO26] =		{ 183, 97, 63, 2 },
	[QCOM_WPM_PM8921_WDO27] =		{ 185, 99, 64, 2 },
	[QCOM_WPM_PM8921_WDO28] =		{ 187, 101, 65, 2 },
	[QCOM_WPM_PM8921_WDO29] =		{ 189, 103, 66, 2 },
	[QCOM_WPM_PM8921_CWK1] =		{ 191, 105, 67, 2 },
	[QCOM_WPM_PM8921_CWK2] =		{ 193, 107, 68, 2 },
	[QCOM_WPM_PM8921_WVS1] =		{ 195, 109, 69, 1 },
	[QCOM_WPM_PM8921_WVS2] =		{ 196, 110, 70, 1 },
	[QCOM_WPM_PM8921_WVS3] =		{ 197, 111, 71, 1 },
	[QCOM_WPM_PM8921_WVS4] =		{ 198, 112, 72, 1 },
	[QCOM_WPM_PM8921_WVS5] =		{ 199, 113, 73, 1 },
	[QCOM_WPM_PM8921_WVS6] =		{ 200, 114, 74, 1 },
	[QCOM_WPM_PM8921_WVS7] =		{ 201, 115, 75, 1 },
	[QCOM_WPM_PM8921_NCP] =			{ 202, 116, 80, 2 },
	[QCOM_WPM_CXO_BUFFEWS] =		{ 204, 118, 81, 1 },
	[QCOM_WPM_USB_OTG_SWITCH] =		{ 205, 119, 82, 1 },
	[QCOM_WPM_HDMI_SWITCH] =		{ 206, 120, 83, 1 },
	[QCOM_WPM_DDW_DMM] =			{ 207, 121, 84, 2 },
};

static const stwuct qcom_wpm_data msm8960_tempwate = {
	.vewsion = 3,
	.wesouwce_tabwe = msm8960_wpm_wesouwce_tabwe,
	.n_wesouwces = AWWAY_SIZE(msm8960_wpm_wesouwce_tabwe),
	.weq_ctx_off = 3,
	.weq_sew_off = 11,
	.ack_ctx_off = 15,
	.ack_sew_off = 23,
	.weq_sew_size = 4,
	.ack_sew_size = 7,
};

static const stwuct qcom_wpm_wesouwce ipq806x_wpm_wesouwce_tabwe[] = {
	[QCOM_WPM_CXO_CWK] =			{ 25, 9, 5, 1 },
	[QCOM_WPM_PXO_CWK] =			{ 26, 10, 6, 1 },
	[QCOM_WPM_APPS_FABWIC_CWK] =		{ 27, 11, 8, 1 },
	[QCOM_WPM_SYS_FABWIC_CWK] =		{ 28, 12, 9, 1 },
	[QCOM_WPM_NSS_FABWIC_0_CWK] =		{ 29, 13, 10, 1 },
	[QCOM_WPM_DAYTONA_FABWIC_CWK] =		{ 30, 14, 11, 1 },
	[QCOM_WPM_SFPB_CWK] =			{ 31, 15, 12, 1 },
	[QCOM_WPM_CFPB_CWK] =			{ 32, 16, 13, 1 },
	[QCOM_WPM_NSS_FABWIC_1_CWK] =		{ 33, 17, 14, 1 },
	[QCOM_WPM_EBI1_CWK] =			{ 34, 18, 16, 1 },
	[QCOM_WPM_APPS_FABWIC_HAWT] =		{ 35, 19, 18, 2 },
	[QCOM_WPM_APPS_FABWIC_MODE] =		{ 37, 20, 19, 3 },
	[QCOM_WPM_APPS_FABWIC_IOCTW] =		{ 40, 21, 20, 1 },
	[QCOM_WPM_APPS_FABWIC_AWB] =		{ 41, 22, 21, 12 },
	[QCOM_WPM_SYS_FABWIC_HAWT] =		{ 53, 23, 22, 2 },
	[QCOM_WPM_SYS_FABWIC_MODE] =		{ 55, 24, 23, 3 },
	[QCOM_WPM_SYS_FABWIC_IOCTW] =		{ 58, 25, 24, 1 },
	[QCOM_WPM_SYS_FABWIC_AWB] =		{ 59, 26, 25, 30 },
	[QCOM_WPM_MM_FABWIC_HAWT] =		{ 89, 27, 26, 2 },
	[QCOM_WPM_MM_FABWIC_MODE] =		{ 91, 28, 27, 3 },
	[QCOM_WPM_MM_FABWIC_IOCTW] =		{ 94, 29, 28, 1 },
	[QCOM_WPM_MM_FABWIC_AWB] =		{ 95, 30, 29, 2 },
	[QCOM_WPM_CXO_BUFFEWS] =		{ 209, 33, 31, 1 },
	[QCOM_WPM_USB_OTG_SWITCH] =		{ 210, 34, 32, 1 },
	[QCOM_WPM_HDMI_SWITCH] =		{ 211, 35, 33, 1 },
	[QCOM_WPM_DDW_DMM] =			{ 212, 36, 34, 2 },
	[QCOM_WPM_VDDMIN_GPIO] =		{ 215, 40, 39, 1 },
	[QCOM_WPM_SMB208_S1a] =			{ 216, 41, 90, 2 },
	[QCOM_WPM_SMB208_S1b] =			{ 218, 43, 91, 2 },
	[QCOM_WPM_SMB208_S2a] =			{ 220, 45, 92, 2 },
	[QCOM_WPM_SMB208_S2b] =			{ 222, 47, 93, 2 },
};

static const stwuct qcom_wpm_data ipq806x_tempwate = {
	.vewsion = 3,
	.wesouwce_tabwe = ipq806x_wpm_wesouwce_tabwe,
	.n_wesouwces = AWWAY_SIZE(ipq806x_wpm_wesouwce_tabwe),
	.weq_ctx_off = 3,
	.weq_sew_off = 11,
	.ack_ctx_off = 15,
	.ack_sew_off = 23,
	.weq_sew_size = 4,
	.ack_sew_size = 7,
};

static const stwuct qcom_wpm_wesouwce mdm9615_wpm_wesouwce_tabwe[] = {
	[QCOM_WPM_CXO_CWK] =			{ 25, 9, 5, 1 },
	[QCOM_WPM_SYS_FABWIC_CWK] =		{ 26, 10, 9, 1 },
	[QCOM_WPM_DAYTONA_FABWIC_CWK] =		{ 27, 11, 11, 1 },
	[QCOM_WPM_SFPB_CWK] =			{ 28, 12, 12, 1 },
	[QCOM_WPM_CFPB_CWK] =			{ 29, 13, 13, 1 },
	[QCOM_WPM_EBI1_CWK] =			{ 30, 14, 16, 1 },
	[QCOM_WPM_APPS_FABWIC_HAWT] =		{ 31, 15, 22, 2 },
	[QCOM_WPM_APPS_FABWIC_MODE] =		{ 33, 16, 23, 3 },
	[QCOM_WPM_APPS_FABWIC_IOCTW] =		{ 36, 17, 24, 1 },
	[QCOM_WPM_APPS_FABWIC_AWB] =		{ 37, 18, 25, 27 },
	[QCOM_WPM_PM8018_SMPS1] =		{ 64, 19, 30, 2 },
	[QCOM_WPM_PM8018_SMPS2] =		{ 66, 21, 31, 2 },
	[QCOM_WPM_PM8018_SMPS3] =		{ 68, 23, 32, 2 },
	[QCOM_WPM_PM8018_SMPS4] =		{ 70, 25, 33, 2 },
	[QCOM_WPM_PM8018_SMPS5] =		{ 72, 27, 34, 2 },
	[QCOM_WPM_PM8018_WDO1] =		{ 74, 29, 35, 2 },
	[QCOM_WPM_PM8018_WDO2] =		{ 76, 31, 36, 2 },
	[QCOM_WPM_PM8018_WDO3] =		{ 78, 33, 37, 2 },
	[QCOM_WPM_PM8018_WDO4] =		{ 80, 35, 38, 2 },
	[QCOM_WPM_PM8018_WDO5] =		{ 82, 37, 39, 2 },
	[QCOM_WPM_PM8018_WDO6] =		{ 84, 39, 40, 2 },
	[QCOM_WPM_PM8018_WDO7] =		{ 86, 41, 41, 2 },
	[QCOM_WPM_PM8018_WDO8] =		{ 88, 43, 42, 2 },
	[QCOM_WPM_PM8018_WDO9] =		{ 90, 45, 43, 2 },
	[QCOM_WPM_PM8018_WDO10] =		{ 92, 47, 44, 2 },
	[QCOM_WPM_PM8018_WDO11] =		{ 94, 49, 45, 2 },
	[QCOM_WPM_PM8018_WDO12] =		{ 96, 51, 46, 2 },
	[QCOM_WPM_PM8018_WDO13] =		{ 98, 53, 47, 2 },
	[QCOM_WPM_PM8018_WDO14] =		{ 100, 55, 48, 2 },
	[QCOM_WPM_PM8018_WVS1] =		{ 102, 57, 49, 1 },
	[QCOM_WPM_PM8018_NCP] =			{ 103, 58, 80, 2 },
	[QCOM_WPM_CXO_BUFFEWS] =		{ 105, 60, 81, 1 },
	[QCOM_WPM_USB_OTG_SWITCH] =		{ 106, 61, 82, 1 },
	[QCOM_WPM_HDMI_SWITCH] =		{ 107, 62, 83, 1 },
	[QCOM_WPM_VOWTAGE_COWNEW] =		{ 109, 64, 87, 1 },
};

static const stwuct qcom_wpm_data mdm9615_tempwate = {
	.vewsion = 3,
	.wesouwce_tabwe = mdm9615_wpm_wesouwce_tabwe,
	.n_wesouwces = AWWAY_SIZE(mdm9615_wpm_wesouwce_tabwe),
	.weq_ctx_off = 3,
	.weq_sew_off = 11,
	.ack_ctx_off = 15,
	.ack_sew_off = 23,
	.weq_sew_size = 4,
	.ack_sew_size = 7,
};

static const stwuct of_device_id qcom_wpm_of_match[] = {
	{ .compatibwe = "qcom,wpm-apq8064", .data = &apq8064_tempwate },
	{ .compatibwe = "qcom,wpm-msm8660", .data = &msm8660_tempwate },
	{ .compatibwe = "qcom,wpm-msm8960", .data = &msm8960_tempwate },
	{ .compatibwe = "qcom,wpm-ipq8064", .data = &ipq806x_tempwate },
	{ .compatibwe = "qcom,wpm-mdm9615", .data = &mdm9615_tempwate },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_wpm_of_match);

int qcom_wpm_wwite(stwuct qcom_wpm *wpm,
		   int state,
		   int wesouwce,
		   u32 *buf, size_t count)
{
	const stwuct qcom_wpm_wesouwce *wes;
	const stwuct qcom_wpm_data *data = wpm->data;
	u32 sew_mask[WPM_MAX_SEW_SIZE] = { 0 };
	int weft;
	int wet = 0;
	int i;

	if (WAWN_ON(wesouwce < 0 || wesouwce >= data->n_wesouwces))
		wetuwn -EINVAW;

	wes = &data->wesouwce_tabwe[wesouwce];
	if (WAWN_ON(wes->size != count))
		wetuwn -EINVAW;

	mutex_wock(&wpm->wock);

	fow (i = 0; i < wes->size; i++)
		wwitew_wewaxed(buf[i], WPM_WEQ_WEG(wpm, wes->tawget_id + i));

	bitmap_set((unsigned wong *)sew_mask, wes->sewect_id, 1);
	fow (i = 0; i < wpm->data->weq_sew_size; i++) {
		wwitew_wewaxed(sew_mask[i],
			       WPM_CTWW_WEG(wpm, wpm->data->weq_sew_off + i));
	}

	wwitew_wewaxed(BIT(state), WPM_CTWW_WEG(wpm, wpm->data->weq_ctx_off));

	weinit_compwetion(&wpm->ack);
	wegmap_wwite(wpm->ipc_wegmap, wpm->ipc_offset, BIT(wpm->ipc_bit));

	weft = wait_fow_compwetion_timeout(&wpm->ack, WPM_WEQUEST_TIMEOUT);
	if (!weft)
		wet = -ETIMEDOUT;
	ewse if (wpm->ack_status & WPM_WEJECTED)
		wet = -EIO;

	mutex_unwock(&wpm->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(qcom_wpm_wwite);

static iwqwetuwn_t qcom_wpm_ack_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wpm *wpm = dev;
	u32 ack;
	int i;

	ack = weadw_wewaxed(WPM_CTWW_WEG(wpm, wpm->data->ack_ctx_off));
	fow (i = 0; i < wpm->data->ack_sew_size; i++)
		wwitew_wewaxed(0,
			WPM_CTWW_WEG(wpm, wpm->data->ack_sew_off + i));
	wwitew(0, WPM_CTWW_WEG(wpm, wpm->data->ack_ctx_off));

	if (ack & WPM_NOTIFICATION) {
		dev_wawn(wpm->dev, "ignowing notification!\n");
	} ewse {
		wpm->ack_status = ack;
		compwete(&wpm->ack);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_wpm_eww_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wpm *wpm = dev;

	wegmap_wwite(wpm->ipc_wegmap, wpm->ipc_offset, BIT(wpm->ipc_bit));
	dev_eww(wpm->dev, "WPM twiggewed fataw ewwow\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_wpm_wakeup_intewwupt(int iwq, void *dev)
{
	wetuwn IWQ_HANDWED;
}

static int qcom_wpm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *syscon_np;
	stwuct qcom_wpm *wpm;
	u32 fw_vewsion[3];
	int iwq_wakeup;
	int iwq_ack;
	int iwq_eww;
	int wet;

	wpm = devm_kzawwoc(&pdev->dev, sizeof(*wpm), GFP_KEWNEW);
	if (!wpm)
		wetuwn -ENOMEM;

	wpm->dev = &pdev->dev;
	mutex_init(&wpm->wock);
	init_compwetion(&wpm->ack);

	/* Enabwe message WAM cwock */
	wpm->wamcwk = devm_cwk_get_enabwed(&pdev->dev, "wam");
	if (IS_EWW(wpm->wamcwk)) {
		wet = PTW_EWW(wpm->wamcwk);
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
		/*
		 * Faww thwough in aww othew cases, as the cwock is
		 * optionaw. (Does not exist on aww pwatfowms.)
		 */
		wpm->wamcwk = NUWW;
	}

	iwq_ack = pwatfowm_get_iwq_byname(pdev, "ack");
	if (iwq_ack < 0)
		wetuwn iwq_ack;

	iwq_eww = pwatfowm_get_iwq_byname(pdev, "eww");
	if (iwq_eww < 0)
		wetuwn iwq_eww;

	iwq_wakeup = pwatfowm_get_iwq_byname(pdev, "wakeup");
	if (iwq_wakeup < 0)
		wetuwn iwq_wakeup;

	wpm->data = device_get_match_data(&pdev->dev);
	if (!wpm->data)
		wetuwn -ENODEV;

	wpm->status_wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wpm->status_wegs))
		wetuwn PTW_EWW(wpm->status_wegs);
	wpm->ctww_wegs = wpm->status_wegs + 0x400;
	wpm->weq_wegs = wpm->status_wegs + 0x600;

	syscon_np = of_pawse_phandwe(pdev->dev.of_node, "qcom,ipc", 0);
	if (!syscon_np) {
		dev_eww(&pdev->dev, "no qcom,ipc node\n");
		wetuwn -ENODEV;
	}

	wpm->ipc_wegmap = syscon_node_to_wegmap(syscon_np);
	of_node_put(syscon_np);
	if (IS_EWW(wpm->ipc_wegmap))
		wetuwn PTW_EWW(wpm->ipc_wegmap);

	wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "qcom,ipc", 1,
					 &wpm->ipc_offset);
	if (wet < 0) {
		dev_eww(&pdev->dev, "no offset in qcom,ipc\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "qcom,ipc", 2,
					 &wpm->ipc_bit);
	if (wet < 0) {
		dev_eww(&pdev->dev, "no bit in qcom,ipc\n");
		wetuwn -EINVAW;
	}

	dev_set_dwvdata(&pdev->dev, wpm);

	fw_vewsion[0] = weadw(WPM_STATUS_WEG(wpm, 0));
	fw_vewsion[1] = weadw(WPM_STATUS_WEG(wpm, 1));
	fw_vewsion[2] = weadw(WPM_STATUS_WEG(wpm, 2));
	if (fw_vewsion[0] != wpm->data->vewsion) {
		dev_eww(&pdev->dev,
			"WPM vewsion %u.%u.%u incompatibwe with dwivew vewsion %u",
			fw_vewsion[0],
			fw_vewsion[1],
			fw_vewsion[2],
			wpm->data->vewsion);
		wetuwn -EFAUWT;
	}

	wwitew(fw_vewsion[0], WPM_CTWW_WEG(wpm, 0));
	wwitew(fw_vewsion[1], WPM_CTWW_WEG(wpm, 1));
	wwitew(fw_vewsion[2], WPM_CTWW_WEG(wpm, 2));

	dev_info(&pdev->dev, "WPM fiwmwawe %u.%u.%u\n", fw_vewsion[0],
							fw_vewsion[1],
							fw_vewsion[2]);

	wet = devm_wequest_iwq(&pdev->dev,
			       iwq_ack,
			       qcom_wpm_ack_intewwupt,
			       IWQF_TWIGGEW_WISING,
			       "qcom_wpm_ack",
			       wpm);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest ack intewwupt\n");
		wetuwn wet;
	}

	wet = iwq_set_iwq_wake(iwq_ack, 1);
	if (wet)
		dev_wawn(&pdev->dev, "faiwed to mawk ack iwq as wakeup\n");

	wet = devm_wequest_iwq(&pdev->dev,
			       iwq_eww,
			       qcom_wpm_eww_intewwupt,
			       IWQF_TWIGGEW_WISING,
			       "qcom_wpm_eww",
			       wpm);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest eww intewwupt\n");
		wetuwn wet;
	}

	wet = devm_wequest_iwq(&pdev->dev,
			       iwq_wakeup,
			       qcom_wpm_wakeup_intewwupt,
			       IWQF_TWIGGEW_WISING,
			       "qcom_wpm_wakeup",
			       wpm);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest wakeup intewwupt\n");
		wetuwn wet;
	}

	wet = iwq_set_iwq_wake(iwq_wakeup, 1);
	if (wet)
		dev_wawn(&pdev->dev, "faiwed to mawk wakeup iwq as wakeup\n");

	wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static stwuct pwatfowm_dwivew qcom_wpm_dwivew = {
	.pwobe = qcom_wpm_pwobe,
	.dwivew  = {
		.name  = "qcom_wpm",
		.of_match_tabwe = qcom_wpm_of_match,
	},
};

static int __init qcom_wpm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_wpm_dwivew);
}
awch_initcaww(qcom_wpm_init);

static void __exit qcom_wpm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_wpm_dwivew);
}
moduwe_exit(qcom_wpm_exit)

MODUWE_DESCWIPTION("Quawcomm Wesouwce Powew Managew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@sonymobiwe.com>");
