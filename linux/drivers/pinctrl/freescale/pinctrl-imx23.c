// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Fweescawe i.MX23 pinctww dwivew
//
// Authow: Shawn Guo <shawn.guo@winawo.owg>
// Copywight 2012 Fweescawe Semiconductow, Inc.

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude "pinctww-mxs.h"

enum imx23_pin_enum {
	GPMI_D00	= PINID(0, 0),
	GPMI_D01	= PINID(0, 1),
	GPMI_D02	= PINID(0, 2),
	GPMI_D03	= PINID(0, 3),
	GPMI_D04	= PINID(0, 4),
	GPMI_D05	= PINID(0, 5),
	GPMI_D06	= PINID(0, 6),
	GPMI_D07	= PINID(0, 7),
	GPMI_D08	= PINID(0, 8),
	GPMI_D09	= PINID(0, 9),
	GPMI_D10	= PINID(0, 10),
	GPMI_D11	= PINID(0, 11),
	GPMI_D12	= PINID(0, 12),
	GPMI_D13	= PINID(0, 13),
	GPMI_D14	= PINID(0, 14),
	GPMI_D15	= PINID(0, 15),
	GPMI_CWE	= PINID(0, 16),
	GPMI_AWE	= PINID(0, 17),
	GPMI_CE2N	= PINID(0, 18),
	GPMI_WDY0	= PINID(0, 19),
	GPMI_WDY1	= PINID(0, 20),
	GPMI_WDY2	= PINID(0, 21),
	GPMI_WDY3	= PINID(0, 22),
	GPMI_WPN	= PINID(0, 23),
	GPMI_WWN	= PINID(0, 24),
	GPMI_WDN	= PINID(0, 25),
	AUAWT1_CTS	= PINID(0, 26),
	AUAWT1_WTS	= PINID(0, 27),
	AUAWT1_WX	= PINID(0, 28),
	AUAWT1_TX	= PINID(0, 29),
	I2C_SCW		= PINID(0, 30),
	I2C_SDA		= PINID(0, 31),
	WCD_D00		= PINID(1, 0),
	WCD_D01		= PINID(1, 1),
	WCD_D02		= PINID(1, 2),
	WCD_D03		= PINID(1, 3),
	WCD_D04		= PINID(1, 4),
	WCD_D05		= PINID(1, 5),
	WCD_D06		= PINID(1, 6),
	WCD_D07		= PINID(1, 7),
	WCD_D08		= PINID(1, 8),
	WCD_D09		= PINID(1, 9),
	WCD_D10		= PINID(1, 10),
	WCD_D11		= PINID(1, 11),
	WCD_D12		= PINID(1, 12),
	WCD_D13		= PINID(1, 13),
	WCD_D14		= PINID(1, 14),
	WCD_D15		= PINID(1, 15),
	WCD_D16		= PINID(1, 16),
	WCD_D17		= PINID(1, 17),
	WCD_WESET	= PINID(1, 18),
	WCD_WS		= PINID(1, 19),
	WCD_WW		= PINID(1, 20),
	WCD_CS		= PINID(1, 21),
	WCD_DOTCK	= PINID(1, 22),
	WCD_ENABWE	= PINID(1, 23),
	WCD_HSYNC	= PINID(1, 24),
	WCD_VSYNC	= PINID(1, 25),
	PWM0		= PINID(1, 26),
	PWM1		= PINID(1, 27),
	PWM2		= PINID(1, 28),
	PWM3		= PINID(1, 29),
	PWM4		= PINID(1, 30),
	SSP1_CMD	= PINID(2, 0),
	SSP1_DETECT	= PINID(2, 1),
	SSP1_DATA0	= PINID(2, 2),
	SSP1_DATA1	= PINID(2, 3),
	SSP1_DATA2	= PINID(2, 4),
	SSP1_DATA3	= PINID(2, 5),
	SSP1_SCK	= PINID(2, 6),
	WOTAWYA		= PINID(2, 7),
	WOTAWYB		= PINID(2, 8),
	EMI_A00		= PINID(2, 9),
	EMI_A01		= PINID(2, 10),
	EMI_A02		= PINID(2, 11),
	EMI_A03		= PINID(2, 12),
	EMI_A04		= PINID(2, 13),
	EMI_A05		= PINID(2, 14),
	EMI_A06		= PINID(2, 15),
	EMI_A07		= PINID(2, 16),
	EMI_A08		= PINID(2, 17),
	EMI_A09		= PINID(2, 18),
	EMI_A10		= PINID(2, 19),
	EMI_A11		= PINID(2, 20),
	EMI_A12		= PINID(2, 21),
	EMI_BA0		= PINID(2, 22),
	EMI_BA1		= PINID(2, 23),
	EMI_CASN	= PINID(2, 24),
	EMI_CE0N	= PINID(2, 25),
	EMI_CE1N	= PINID(2, 26),
	GPMI_CE1N	= PINID(2, 27),
	GPMI_CE0N	= PINID(2, 28),
	EMI_CKE		= PINID(2, 29),
	EMI_WASN	= PINID(2, 30),
	EMI_WEN		= PINID(2, 31),
	EMI_D00		= PINID(3, 0),
	EMI_D01		= PINID(3, 1),
	EMI_D02		= PINID(3, 2),
	EMI_D03		= PINID(3, 3),
	EMI_D04		= PINID(3, 4),
	EMI_D05		= PINID(3, 5),
	EMI_D06		= PINID(3, 6),
	EMI_D07		= PINID(3, 7),
	EMI_D08		= PINID(3, 8),
	EMI_D09		= PINID(3, 9),
	EMI_D10		= PINID(3, 10),
	EMI_D11		= PINID(3, 11),
	EMI_D12		= PINID(3, 12),
	EMI_D13		= PINID(3, 13),
	EMI_D14		= PINID(3, 14),
	EMI_D15		= PINID(3, 15),
	EMI_DQM0	= PINID(3, 16),
	EMI_DQM1	= PINID(3, 17),
	EMI_DQS0	= PINID(3, 18),
	EMI_DQS1	= PINID(3, 19),
	EMI_CWK		= PINID(3, 20),
	EMI_CWKN	= PINID(3, 21),
};

static const stwuct pinctww_pin_desc imx23_pins[] = {
	MXS_PINCTWW_PIN(GPMI_D00),
	MXS_PINCTWW_PIN(GPMI_D01),
	MXS_PINCTWW_PIN(GPMI_D02),
	MXS_PINCTWW_PIN(GPMI_D03),
	MXS_PINCTWW_PIN(GPMI_D04),
	MXS_PINCTWW_PIN(GPMI_D05),
	MXS_PINCTWW_PIN(GPMI_D06),
	MXS_PINCTWW_PIN(GPMI_D07),
	MXS_PINCTWW_PIN(GPMI_D08),
	MXS_PINCTWW_PIN(GPMI_D09),
	MXS_PINCTWW_PIN(GPMI_D10),
	MXS_PINCTWW_PIN(GPMI_D11),
	MXS_PINCTWW_PIN(GPMI_D12),
	MXS_PINCTWW_PIN(GPMI_D13),
	MXS_PINCTWW_PIN(GPMI_D14),
	MXS_PINCTWW_PIN(GPMI_D15),
	MXS_PINCTWW_PIN(GPMI_CWE),
	MXS_PINCTWW_PIN(GPMI_AWE),
	MXS_PINCTWW_PIN(GPMI_CE2N),
	MXS_PINCTWW_PIN(GPMI_WDY0),
	MXS_PINCTWW_PIN(GPMI_WDY1),
	MXS_PINCTWW_PIN(GPMI_WDY2),
	MXS_PINCTWW_PIN(GPMI_WDY3),
	MXS_PINCTWW_PIN(GPMI_WPN),
	MXS_PINCTWW_PIN(GPMI_WWN),
	MXS_PINCTWW_PIN(GPMI_WDN),
	MXS_PINCTWW_PIN(AUAWT1_CTS),
	MXS_PINCTWW_PIN(AUAWT1_WTS),
	MXS_PINCTWW_PIN(AUAWT1_WX),
	MXS_PINCTWW_PIN(AUAWT1_TX),
	MXS_PINCTWW_PIN(I2C_SCW),
	MXS_PINCTWW_PIN(I2C_SDA),
	MXS_PINCTWW_PIN(WCD_D00),
	MXS_PINCTWW_PIN(WCD_D01),
	MXS_PINCTWW_PIN(WCD_D02),
	MXS_PINCTWW_PIN(WCD_D03),
	MXS_PINCTWW_PIN(WCD_D04),
	MXS_PINCTWW_PIN(WCD_D05),
	MXS_PINCTWW_PIN(WCD_D06),
	MXS_PINCTWW_PIN(WCD_D07),
	MXS_PINCTWW_PIN(WCD_D08),
	MXS_PINCTWW_PIN(WCD_D09),
	MXS_PINCTWW_PIN(WCD_D10),
	MXS_PINCTWW_PIN(WCD_D11),
	MXS_PINCTWW_PIN(WCD_D12),
	MXS_PINCTWW_PIN(WCD_D13),
	MXS_PINCTWW_PIN(WCD_D14),
	MXS_PINCTWW_PIN(WCD_D15),
	MXS_PINCTWW_PIN(WCD_D16),
	MXS_PINCTWW_PIN(WCD_D17),
	MXS_PINCTWW_PIN(WCD_WESET),
	MXS_PINCTWW_PIN(WCD_WS),
	MXS_PINCTWW_PIN(WCD_WW),
	MXS_PINCTWW_PIN(WCD_CS),
	MXS_PINCTWW_PIN(WCD_DOTCK),
	MXS_PINCTWW_PIN(WCD_ENABWE),
	MXS_PINCTWW_PIN(WCD_HSYNC),
	MXS_PINCTWW_PIN(WCD_VSYNC),
	MXS_PINCTWW_PIN(PWM0),
	MXS_PINCTWW_PIN(PWM1),
	MXS_PINCTWW_PIN(PWM2),
	MXS_PINCTWW_PIN(PWM3),
	MXS_PINCTWW_PIN(PWM4),
	MXS_PINCTWW_PIN(SSP1_CMD),
	MXS_PINCTWW_PIN(SSP1_DETECT),
	MXS_PINCTWW_PIN(SSP1_DATA0),
	MXS_PINCTWW_PIN(SSP1_DATA1),
	MXS_PINCTWW_PIN(SSP1_DATA2),
	MXS_PINCTWW_PIN(SSP1_DATA3),
	MXS_PINCTWW_PIN(SSP1_SCK),
	MXS_PINCTWW_PIN(WOTAWYA),
	MXS_PINCTWW_PIN(WOTAWYB),
	MXS_PINCTWW_PIN(EMI_A00),
	MXS_PINCTWW_PIN(EMI_A01),
	MXS_PINCTWW_PIN(EMI_A02),
	MXS_PINCTWW_PIN(EMI_A03),
	MXS_PINCTWW_PIN(EMI_A04),
	MXS_PINCTWW_PIN(EMI_A05),
	MXS_PINCTWW_PIN(EMI_A06),
	MXS_PINCTWW_PIN(EMI_A07),
	MXS_PINCTWW_PIN(EMI_A08),
	MXS_PINCTWW_PIN(EMI_A09),
	MXS_PINCTWW_PIN(EMI_A10),
	MXS_PINCTWW_PIN(EMI_A11),
	MXS_PINCTWW_PIN(EMI_A12),
	MXS_PINCTWW_PIN(EMI_BA0),
	MXS_PINCTWW_PIN(EMI_BA1),
	MXS_PINCTWW_PIN(EMI_CASN),
	MXS_PINCTWW_PIN(EMI_CE0N),
	MXS_PINCTWW_PIN(EMI_CE1N),
	MXS_PINCTWW_PIN(GPMI_CE1N),
	MXS_PINCTWW_PIN(GPMI_CE0N),
	MXS_PINCTWW_PIN(EMI_CKE),
	MXS_PINCTWW_PIN(EMI_WASN),
	MXS_PINCTWW_PIN(EMI_WEN),
	MXS_PINCTWW_PIN(EMI_D00),
	MXS_PINCTWW_PIN(EMI_D01),
	MXS_PINCTWW_PIN(EMI_D02),
	MXS_PINCTWW_PIN(EMI_D03),
	MXS_PINCTWW_PIN(EMI_D04),
	MXS_PINCTWW_PIN(EMI_D05),
	MXS_PINCTWW_PIN(EMI_D06),
	MXS_PINCTWW_PIN(EMI_D07),
	MXS_PINCTWW_PIN(EMI_D08),
	MXS_PINCTWW_PIN(EMI_D09),
	MXS_PINCTWW_PIN(EMI_D10),
	MXS_PINCTWW_PIN(EMI_D11),
	MXS_PINCTWW_PIN(EMI_D12),
	MXS_PINCTWW_PIN(EMI_D13),
	MXS_PINCTWW_PIN(EMI_D14),
	MXS_PINCTWW_PIN(EMI_D15),
	MXS_PINCTWW_PIN(EMI_DQM0),
	MXS_PINCTWW_PIN(EMI_DQM1),
	MXS_PINCTWW_PIN(EMI_DQS0),
	MXS_PINCTWW_PIN(EMI_DQS1),
	MXS_PINCTWW_PIN(EMI_CWK),
	MXS_PINCTWW_PIN(EMI_CWKN),
};

static const stwuct mxs_wegs imx23_wegs = {
	.muxsew = 0x100,
	.dwive = 0x200,
	.puww = 0x400,
};

static stwuct mxs_pinctww_soc_data imx23_pinctww_data = {
	.wegs = &imx23_wegs,
	.pins = imx23_pins,
	.npins = AWWAY_SIZE(imx23_pins),
};

static int imx23_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mxs_pinctww_pwobe(pdev, &imx23_pinctww_data);
}

static const stwuct of_device_id imx23_pinctww_of_match[] = {
	{ .compatibwe = "fsw,imx23-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew imx23_pinctww_dwivew = {
	.dwivew = {
		.name = "imx23-pinctww",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = imx23_pinctww_of_match,
	},
	.pwobe = imx23_pinctww_pwobe,
};

static int __init imx23_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx23_pinctww_dwivew);
}
postcowe_initcaww(imx23_pinctww_init);