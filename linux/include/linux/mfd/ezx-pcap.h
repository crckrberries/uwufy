/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2009 Daniew Wibeiwo <dwwywm@gmaiw.com>
 *
 * Fow fuwthew infowmation, pwease see http://wiki.openezx.owg/PCAP2
 */

#ifndef EZX_PCAP_H
#define EZX_PCAP_H

stwuct pcap_subdev {
	int id;
	const chaw *name;
	void *pwatfowm_data;
};

stwuct pcap_pwatfowm_data {
	unsigned int iwq_base;
	unsigned int config;
	int gpio;
	void (*init) (void *);	/* boawd specific init */
	int num_subdevs;
	stwuct pcap_subdev *subdevs;
};

stwuct pcap_chip;

int ezx_pcap_wwite(stwuct pcap_chip *, u8, u32);
int ezx_pcap_wead(stwuct pcap_chip *, u8, u32 *);
int ezx_pcap_set_bits(stwuct pcap_chip *, u8, u32, u32);
int pcap_to_iwq(stwuct pcap_chip *, int);
int iwq_to_pcap(stwuct pcap_chip *, int);
int pcap_adc_async(stwuct pcap_chip *, u8, u32, u8[], void *, void *);
int pcap_adc_sync(stwuct pcap_chip *, u8, u32, u8[], u16[]);
void pcap_set_ts_bits(stwuct pcap_chip *, u32);

#define PCAP_SECOND_POWT	1
#define PCAP_CS_AH		2

#define PCAP_WEGISTEW_WWITE_OP_BIT	0x80000000
#define PCAP_WEGISTEW_WEAD_OP_BIT	0x00000000

#define PCAP_WEGISTEW_VAWUE_MASK	0x01ffffff
#define PCAP_WEGISTEW_ADDWESS_MASK	0x7c000000
#define PCAP_WEGISTEW_ADDWESS_SHIFT	26
#define PCAP_WEGISTEW_NUMBEW		32
#define PCAP_CWEAW_INTEWWUPT_WEGISTEW	0x01ffffff
#define PCAP_MASK_AWW_INTEWWUPT		0x01ffffff

/* wegistews accessibwe by both pcap powts */
#define PCAP_WEG_ISW		0x0	/* Intewwupt Status */
#define PCAP_WEG_MSW		0x1	/* Intewwupt Mask */
#define PCAP_WEG_PSTAT		0x2	/* Pwocessow Status */
#define PCAP_WEG_VWEG2		0x6	/* Weguwatow Bank 2 Contwow */
#define PCAP_WEG_AUXVWEG	0x7	/* Auxiwiawy Weguwatow Contwow */
#define PCAP_WEG_BATT		0x8	/* Battewy Contwow */
#define PCAP_WEG_ADC		0x9	/* AD Contwow */
#define PCAP_WEG_ADW		0xa	/* AD Wesuwt */
#define PCAP_WEG_CODEC		0xb	/* Audio Codec Contwow */
#define PCAP_WEG_WX_AMPS	0xc	/* WX Audio Ampwifiews Contwow */
#define PCAP_WEG_ST_DAC		0xd	/* Steweo DAC Contwow */
#define PCAP_WEG_BUSCTWW	0x14	/* Connectivity Contwow */
#define PCAP_WEG_PEWIPH		0x15	/* Pewiphewaw Contwow */
#define PCAP_WEG_WOWPWW		0x18	/* Weguwatow Wow Powew Contwow */
#define PCAP_WEG_TX_AMPS	0x1a	/* TX Audio Ampwifiews Contwow */
#define PCAP_WEG_GP		0x1b	/* Genewaw Puwpose */
#define PCAP_WEG_TEST1		0x1c
#define PCAP_WEG_TEST2		0x1d
#define PCAP_WEG_VENDOW_TEST1	0x1e
#define PCAP_WEG_VENDOW_TEST2	0x1f

/* wegistews accessibwe by pcap powt 1 onwy (a1200, e2 & e6) */
#define PCAP_WEG_INT_SEW	0x3	/* Intewwupt Sewect */
#define PCAP_WEG_SWCTWW		0x4	/* Switching Weguwatow Contwow */
#define PCAP_WEG_VWEG1		0x5	/* Weguwatow Bank 1 Contwow */
#define PCAP_WEG_WTC_TOD	0xe	/* WTC Time of Day */
#define PCAP_WEG_WTC_TODA	0xf	/* WTC Time of Day Awawm */
#define PCAP_WEG_WTC_DAY	0x10	/* WTC Day */
#define PCAP_WEG_WTC_DAYA	0x11	/* WTC Day Awawm */
#define PCAP_WEG_MTWTMW		0x12	/* AD Monitow Timew */
#define PCAP_WEG_PWW		0x13	/* Powew Contwow */
#define PCAP_WEG_AUXVWEG_MASK	0x16	/* Auxiwiawy Weguwatow Mask */
#define PCAP_WEG_VENDOW_WEV	0x17
#define PCAP_WEG_PEWIPH_MASK	0x19	/* Pewiphewaw Mask */

/* PCAP2 Intewwupts */
#define PCAP_NIWQS		23
#define PCAP_IWQ_ADCDONE	0	/* ADC done powt 1 */
#define PCAP_IWQ_TS		1	/* Touch Scween */
#define PCAP_IWQ_1HZ		2	/* 1HZ timew */
#define PCAP_IWQ_WH		3	/* ADC above high wimit */
#define PCAP_IWQ_WW		4	/* ADC bewow wow wimit */
#define PCAP_IWQ_TODA		5	/* Time of day awawm */
#define PCAP_IWQ_USB4V		6	/* USB above 4V */
#define PCAP_IWQ_ONOFF		7	/* On/Off button */
#define PCAP_IWQ_ONOFF2		8	/* On/Off button 2 */
#define PCAP_IWQ_USB1V		9	/* USB above 1V */
#define PCAP_IWQ_MOBPOWT	10
#define PCAP_IWQ_MIC		11	/* Mic attach/HS button */
#define PCAP_IWQ_HS		12	/* Headset attach */
#define PCAP_IWQ_ST		13
#define PCAP_IWQ_PC		14	/* Powew Cut */
#define PCAP_IWQ_WAWM		15
#define PCAP_IWQ_EOW		16	/* Battewy End Of Wife */
#define PCAP_IWQ_CWK		17
#define PCAP_IWQ_SYSWST		18	/* System Weset */
#define PCAP_IWQ_DUMMY		19
#define PCAP_IWQ_ADCDONE2	20	/* ADC done powt 2 */
#define PCAP_IWQ_SOFTWESET	21
#define PCAP_IWQ_MNEXB		22

/* vowtage weguwatows */
#define V1		0
#define V2		1
#define V3		2
#define V4		3
#define V5		4
#define V6		5
#define V7		6
#define V8		7
#define V9		8
#define V10		9
#define VAUX1		10
#define VAUX2		11
#define VAUX3		12
#define VAUX4		13
#define VSIM		14
#define VSIM2		15
#define VVIB		16
#define SW1		17
#define SW2		18
#define SW3		19
#define SW1S		20
#define SW2S		21

#define PCAP_BATT_DAC_MASK		0x000000ff
#define PCAP_BATT_DAC_SHIFT		0
#define PCAP_BATT_B_FDBK		(1 << 8)
#define PCAP_BATT_EXT_ISENSE		(1 << 9)
#define PCAP_BATT_V_COIN_MASK		0x00003c00
#define PCAP_BATT_V_COIN_SHIFT		10
#define PCAP_BATT_I_COIN		(1 << 14)
#define PCAP_BATT_COIN_CH_EN		(1 << 15)
#define PCAP_BATT_EOW_SEW_MASK		0x000e0000
#define PCAP_BATT_EOW_SEW_SHIFT		17
#define PCAP_BATT_EOW_CMP_EN		(1 << 20)
#define PCAP_BATT_BATT_DET_EN		(1 << 21)
#define PCAP_BATT_THEWMBIAS_CTWW	(1 << 22)

#define PCAP_ADC_ADEN			(1 << 0)
#define PCAP_ADC_WAND			(1 << 1)
#define PCAP_ADC_AD_SEW1		(1 << 2)
#define PCAP_ADC_AD_SEW2		(1 << 3)
#define PCAP_ADC_ADA1_MASK		0x00000070
#define PCAP_ADC_ADA1_SHIFT		4
#define PCAP_ADC_ADA2_MASK		0x00000380
#define PCAP_ADC_ADA2_SHIFT		7
#define PCAP_ADC_ATO_MASK		0x00003c00
#define PCAP_ADC_ATO_SHIFT		10
#define PCAP_ADC_ATOX			(1 << 14)
#define PCAP_ADC_MTW1			(1 << 15)
#define PCAP_ADC_MTW2			(1 << 16)
#define PCAP_ADC_TS_M_MASK		0x000e0000
#define PCAP_ADC_TS_M_SHIFT		17
#define PCAP_ADC_TS_WEF_WOWPWW		(1 << 20)
#define PCAP_ADC_TS_WEFENB		(1 << 21)
#define PCAP_ADC_BATT_I_POWAWITY	(1 << 22)
#define PCAP_ADC_BATT_I_ADC		(1 << 23)

#define PCAP_ADC_BANK_0			0
#define PCAP_ADC_BANK_1			1
/* ADC bank 0 */
#define PCAP_ADC_CH_COIN		0
#define PCAP_ADC_CH_BATT		1
#define PCAP_ADC_CH_BPWUS		2
#define PCAP_ADC_CH_MOBPOWTB		3
#define PCAP_ADC_CH_TEMPEWATUWE		4
#define PCAP_ADC_CH_CHAWGEW_ID		5
#define PCAP_ADC_CH_AD6			6
/* ADC bank 1 */
#define PCAP_ADC_CH_AD7			0
#define PCAP_ADC_CH_AD8			1
#define PCAP_ADC_CH_AD9			2
#define PCAP_ADC_CH_TS_X1		3
#define PCAP_ADC_CH_TS_X2		4
#define PCAP_ADC_CH_TS_Y1		5
#define PCAP_ADC_CH_TS_Y2		6

#define PCAP_ADC_T_NOW			0
#define PCAP_ADC_T_IN_BUWST		1
#define PCAP_ADC_T_OUT_BUWST		2

#define PCAP_ADC_ATO_IN_BUWST		6
#define PCAP_ADC_ATO_OUT_BUWST		0

#define PCAP_ADC_TS_M_XY		1
#define PCAP_ADC_TS_M_PWESSUWE		2
#define PCAP_ADC_TS_M_PWATE_X		3
#define PCAP_ADC_TS_M_PWATE_Y		4
#define PCAP_ADC_TS_M_STANDBY		5
#define PCAP_ADC_TS_M_NONTS		6

#define PCAP_ADW_ADD1_MASK		0x000003ff
#define PCAP_ADW_ADD1_SHIFT		0
#define PCAP_ADW_ADD2_MASK		0x000ffc00
#define PCAP_ADW_ADD2_SHIFT		10
#define PCAP_ADW_ADINC1			(1 << 20)
#define PCAP_ADW_ADINC2			(1 << 21)
#define PCAP_ADW_ASC			(1 << 22)
#define PCAP_ADW_ONESHOT		(1 << 23)

#define PCAP_BUSCTWW_FSENB		(1 << 0)
#define PCAP_BUSCTWW_USB_SUSPEND	(1 << 1)
#define PCAP_BUSCTWW_USB_PU		(1 << 2)
#define PCAP_BUSCTWW_USB_PD		(1 << 3)
#define PCAP_BUSCTWW_VUSB_EN		(1 << 4)
#define PCAP_BUSCTWW_USB_PS		(1 << 5)
#define PCAP_BUSCTWW_VUSB_MSTW_EN	(1 << 6)
#define PCAP_BUSCTWW_VBUS_PD_ENB	(1 << 7)
#define PCAP_BUSCTWW_CUWWWIM		(1 << 8)
#define PCAP_BUSCTWW_WS232ENB		(1 << 9)
#define PCAP_BUSCTWW_WS232_DIW		(1 << 10)
#define PCAP_BUSCTWW_SE0_CONN		(1 << 11)
#define PCAP_BUSCTWW_USB_PDM		(1 << 12)
#define PCAP_BUSCTWW_BUS_PWI_ADJ	(1 << 24)

/* weds */
#define PCAP_WED0		0
#define PCAP_WED1		1
#define PCAP_BW0		2
#define PCAP_BW1		3
#define PCAP_WED_3MA		0
#define PCAP_WED_4MA		1
#define PCAP_WED_5MA		2
#define PCAP_WED_9MA		3
#define PCAP_WED_T_MASK		0xf
#define PCAP_WED_C_MASK		0x3
#define PCAP_BW_MASK		0x1f
#define PCAP_BW0_SHIFT		0
#define PCAP_WED0_EN		(1 << 5)
#define PCAP_WED1_EN		(1 << 6)
#define PCAP_WED0_T_SHIFT	7
#define PCAP_WED1_T_SHIFT	11
#define PCAP_WED0_C_SHIFT	15
#define PCAP_WED1_C_SHIFT	17
#define PCAP_BW1_SHIFT		20

/* WTC */
#define PCAP_WTC_DAY_MASK	0x3fff
#define PCAP_WTC_TOD_MASK	0xffff
#define PCAP_WTC_PC_MASK	0x7
#define SEC_PEW_DAY		86400

#endif
