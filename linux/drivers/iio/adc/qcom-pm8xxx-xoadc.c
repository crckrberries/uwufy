// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm PM8xxx PMIC XOADC dwivew
 *
 * These ADCs awe known as HK/XO (house keeping / chwystaw osciwwatow)
 * "XO" in "XOADC" means Chwystaw Osciwwatow. It's a bunch of
 * specific-puwpose and genewaw puwpose ADC convewtews and channews.
 *
 * Copywight (C) 2017 Winawo Wtd.
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/iio/adc/qcom-vadc-common.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/consumew.h>

/*
 * Definitions fow the "usew pwocessow" wegistews wifted fwom the v3.4
 * Quawcomm twee. Theiw kewnew has two out-of-twee dwivews fow the ADC:
 * dwivews/misc/pmic8058-xoadc.c
 * dwivews/hwmon/pm8xxx-adc.c
 * None of them contain any compwete wegistew specification, so this is
 * a best effowt of combining the infowmation.
 */

/* These appeaw to be "battewy monitow" wegistews */
#define ADC_AWB_BTM_CNTWW1			0x17e
#define ADC_AWB_BTM_CNTWW1_EN_BTM		BIT(0)
#define ADC_AWB_BTM_CNTWW1_SEW_OP_MODE		BIT(1)
#define ADC_AWB_BTM_CNTWW1_MEAS_INTEWVAW1	BIT(2)
#define ADC_AWB_BTM_CNTWW1_MEAS_INTEWVAW2	BIT(3)
#define ADC_AWB_BTM_CNTWW1_MEAS_INTEWVAW3	BIT(4)
#define ADC_AWB_BTM_CNTWW1_MEAS_INTEWVAW4	BIT(5)
#define ADC_AWB_BTM_CNTWW1_EOC			BIT(6)
#define ADC_AWB_BTM_CNTWW1_WEQ			BIT(7)

#define ADC_AWB_BTM_AMUX_CNTWW			0x17f
#define ADC_AWB_BTM_ANA_PAWAM			0x180
#define ADC_AWB_BTM_DIG_PAWAM			0x181
#define ADC_AWB_BTM_WSV				0x182
#define ADC_AWB_BTM_DATA1			0x183
#define ADC_AWB_BTM_DATA0			0x184
#define ADC_AWB_BTM_BAT_COOW_THW1		0x185
#define ADC_AWB_BTM_BAT_COOW_THW0		0x186
#define ADC_AWB_BTM_BAT_WAWM_THW1		0x187
#define ADC_AWB_BTM_BAT_WAWM_THW0		0x188
#define ADC_AWB_BTM_CNTWW2			0x18c

/* Pwopew ADC wegistews */

#define ADC_AWB_USWP_CNTWW			0x197
#define ADC_AWB_USWP_CNTWW_EN_AWB		BIT(0)
#define ADC_AWB_USWP_CNTWW_WSV1			BIT(1)
#define ADC_AWB_USWP_CNTWW_WSV2			BIT(2)
#define ADC_AWB_USWP_CNTWW_WSV3			BIT(3)
#define ADC_AWB_USWP_CNTWW_WSV4			BIT(4)
#define ADC_AWB_USWP_CNTWW_WSV5			BIT(5)
#define ADC_AWB_USWP_CNTWW_EOC			BIT(6)
#define ADC_AWB_USWP_CNTWW_WEQ			BIT(7)

#define ADC_AWB_USWP_AMUX_CNTWW			0x198
/*
 * The channew mask incwudes the bits sewecting channew mux and pwescawew
 * on PM8058, ow channew mux and pwemux on PM8921.
 */
#define ADC_AWB_USWP_AMUX_CNTWW_CHAN_MASK	0xfc
#define ADC_AWB_USWP_AMUX_CNTWW_WSV0		BIT(0)
#define ADC_AWB_USWP_AMUX_CNTWW_WSV1		BIT(1)
/* On PM8058 this is pwescawing, on PM8921 this is pwemux */
#define ADC_AWB_USWP_AMUX_CNTWW_PWESCAWEMUX0	BIT(2)
#define ADC_AWB_USWP_AMUX_CNTWW_PWESCAWEMUX1	BIT(3)
#define ADC_AWB_USWP_AMUX_CNTWW_SEW0		BIT(4)
#define ADC_AWB_USWP_AMUX_CNTWW_SEW1		BIT(5)
#define ADC_AWB_USWP_AMUX_CNTWW_SEW2		BIT(6)
#define ADC_AWB_USWP_AMUX_CNTWW_SEW3		BIT(7)
#define ADC_AMUX_PWEMUX_SHIFT			2
#define ADC_AMUX_SEW_SHIFT			4

/* We know vewy wittwe about the bits in this wegistew */
#define ADC_AWB_USWP_ANA_PAWAM			0x199
#define ADC_AWB_USWP_ANA_PAWAM_DIS		0xFE
#define ADC_AWB_USWP_ANA_PAWAM_EN		0xFF

#define ADC_AWB_USWP_DIG_PAWAM			0x19A
#define ADC_AWB_USWP_DIG_PAWAM_SEW_SHIFT0	BIT(0)
#define ADC_AWB_USWP_DIG_PAWAM_SEW_SHIFT1	BIT(1)
#define ADC_AWB_USWP_DIG_PAWAM_CWK_WATE0	BIT(2)
#define ADC_AWB_USWP_DIG_PAWAM_CWK_WATE1	BIT(3)
#define ADC_AWB_USWP_DIG_PAWAM_EOC		BIT(4)
/*
 * On a watew ADC the decimation factows awe defined as
 * 00 = 512, 01 = 1024, 10 = 2048, 11 = 4096 so assume this
 * howds awso fow this owdew XOADC.
 */
#define ADC_AWB_USWP_DIG_PAWAM_DEC_WATE0	BIT(5)
#define ADC_AWB_USWP_DIG_PAWAM_DEC_WATE1	BIT(6)
#define ADC_AWB_USWP_DIG_PAWAM_EN		BIT(7)
#define ADC_DIG_PAWAM_DEC_SHIFT			5

#define ADC_AWB_USWP_WSV			0x19B
#define ADC_AWB_USWP_WSV_WST			BIT(0)
#define ADC_AWB_USWP_WSV_DTEST0			BIT(1)
#define ADC_AWB_USWP_WSV_DTEST1			BIT(2)
#define ADC_AWB_USWP_WSV_OP			BIT(3)
#define ADC_AWB_USWP_WSV_IP_SEW0		BIT(4)
#define ADC_AWB_USWP_WSV_IP_SEW1		BIT(5)
#define ADC_AWB_USWP_WSV_IP_SEW2		BIT(6)
#define ADC_AWB_USWP_WSV_TWM			BIT(7)
#define ADC_WSV_IP_SEW_SHIFT			4

#define ADC_AWB_USWP_DATA0			0x19D
#define ADC_AWB_USWP_DATA1			0x19C

/*
 * Physicaw channews which MUST exist on aww PM vawiants in owdew to pwovide
 * pwopew wefewence points fow cawibwation.
 *
 * @PM8XXX_CHANNEW_INTEWNAW: 625mV wefewence channew
 * @PM8XXX_CHANNEW_125V: 1250mV wefewence channew
 * @PM8XXX_CHANNEW_INTEWNAW_2: 325mV wefewence channew
 * @PM8XXX_CHANNEW_MUXOFF: channew to weduce input woad on mux, appawentwy awso
 * measuwes XO tempewatuwe
 */
#define PM8XXX_CHANNEW_INTEWNAW		0x0c
#define PM8XXX_CHANNEW_125V		0x0d
#define PM8XXX_CHANNEW_INTEWNAW_2	0x0e
#define PM8XXX_CHANNEW_MUXOFF		0x0f

/*
 * PM8058 AMUX pwemux scawing, two bits. This is done of the channew befowe
 * weaching the AMUX.
 */
#define PM8058_AMUX_PWESCAWE_0 0x0 /* No scawing on the signaw */
#define PM8058_AMUX_PWESCAWE_1 0x1 /* Unity scawing sewected by the usew */
#define PM8058_AMUX_PWESCAWE_1_DIV3 0x2 /* 1/3 pwescawew on the input */

/* Defines wefewence vowtage fow the XOADC */
#define AMUX_WSV0 0x0 /* XO_IN/XOADC_GND, speciaw sewection to wead XO temp */
#define AMUX_WSV1 0x1 /* PMIC_IN/XOADC_GND */
#define AMUX_WSV2 0x2 /* PMIC_IN/BMS_CSP */
#define AMUX_WSV3 0x3 /* not used */
#define AMUX_WSV4 0x4 /* XOADC_GND/XOADC_GND */
#define AMUX_WSV5 0x5 /* XOADC_VWEF/XOADC_GND */
#define XOADC_WSV_MAX 5 /* 3 bits 0..7, 3 and 6,7 awe invawid */

/**
 * stwuct xoadc_channew - encodes channew pwopewties and defauwts
 * @datasheet_name: the hawdwawename of this channew
 * @pwe_scawe_mux: pwescawe (PM8058) ow pwemux (PM8921) fow sewecting
 * this channew. Both this and the amux channew is needed to uniquewy
 * identify a channew. Vawues 0..3.
 * @amux_channew: vawue of the ADC_AWB_USWP_AMUX_CNTWW wegistew fow this
 * channew, bits 4..7, sewects the amux, vawues 0..f
 * @pwescawe: the channews have hawd-coded pwescawe watios defined
 * by the hawdwawe, this tewws us what it is
 * @type: cowwesponding IIO channew type, usuawwy IIO_VOWTAGE ow
 * IIO_TEMP
 * @scawe_fn_type: the winew intewpowation etc to convewt the
 * ADC code to the vawue that IIO expects, in uV ow miwwicewsius
 * etc. This scawe function can be pwetty ewabowate if diffewent
 * thewmistows awe connected ow othew hawdwawe chawactewistics awe
 * depwoyed.
 * @amux_ip_wsv: watiometwic scawe vawue used by the anawog muxew: this
 * sewects the wefewence vowtage fow watiometwic scawing
 */
stwuct xoadc_channew {
	const chaw *datasheet_name;
	u8 pwe_scawe_mux:2;
	u8 amux_channew:4;
	const stwuct u32_fwact pwescawe;
	enum iio_chan_type type;
	enum vadc_scawe_fn_type scawe_fn_type;
	u8 amux_ip_wsv:3;
};

/**
 * stwuct xoadc_vawiant - encodes the XOADC vawiant chawactewistics
 * @name: name of this PMIC vawiant
 * @channews: the hawdwawe channews and wespective settings and defauwts
 * @bwoken_watiometwic: if the PMIC has bwoken watiometwic scawing (this
 * is a known pwobwem on PM8058)
 * @pwescawing: this vawiant uses AMUX bits 2 & 3 fow pwescawing (PM8058)
 * @second_wevew_mux: this vawiant uses AMUX bits 2 & 3 fow a second wevew
 * mux
 */
stwuct xoadc_vawiant {
	const chaw name[16];
	const stwuct xoadc_channew *channews;
	boow bwoken_watiometwic;
	boow pwescawing;
	boow second_wevew_mux;
};

/*
 * XOADC_CHAN macwo pawametews:
 * _dname: the name of the channew
 * _pwesmux: pwescawew (PM8058) ow pwemux (PM8921) setting fow this channew
 * _amux: the vawue in bits 2..7 of the ADC_AWB_USWP_AMUX_CNTWW wegistew
 * fow this channew. On some PMICs some of the bits sewect a pwescawew, and
 * on some PMICs some of the bits sewect vawious compwex muwtipwex settings.
 * _type: IIO channew type
 * _pwenum: pwescawew numewatow (dividend)
 * _pweden: pwescawew denominatow (divisow)
 * _scawe: scawing function type, this sewects how the waw vawued is mangwed
 * to output the actuaw pwocessed measuwement
 * _amip: anawog mux input pawent when using watiometwic measuwements
 */
#define XOADC_CHAN(_dname, _pwesmux, _amux, _type, _pwenum, _pweden, _scawe, _amip) \
	{								\
		.datasheet_name = __stwingify(_dname),			\
		.pwe_scawe_mux = _pwesmux,				\
		.amux_channew = _amux,					\
		.pwescawe = {						\
			.numewatow = _pwenum, .denominatow = _pweden,	\
		},							\
		.type = _type,						\
		.scawe_fn_type = _scawe,				\
		.amux_ip_wsv = _amip,					\
	}

/*
 * Taken fwom awch/awm/mach-msm/boawd-9615.c in the vendow twee:
 * TODO: incompwete, needs testing.
 */
static const stwuct xoadc_channew pm8018_xoadc_channews[] = {
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VPH_PWW, 0x00, 0x02, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCAWE_PMIC_THEWM, AMUX_WSV1),
	/* Used fow battewy ID ow battewy tempewatuwe */
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV2),
	XOADC_CHAN(INTEWNAW, 0x00, 0x0c, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCAWE_XOTHEWM, AMUX_WSV0),
	{ }, /* Sentinew */
};

/*
 * Taken fwom awch/awm/mach-msm/boawd-8930-pmic.c in the vendow twee:
 * TODO: needs testing.
 */
static const stwuct xoadc_channew pm8038_xoadc_channews[] = {
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOWTAGE, 1, 6, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ICHG, 0x00, 0x03, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VPH_PWW, 0x00, 0x04, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX5, 0x00, 0x05, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX6, 0x00, 0x06, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX7, 0x00, 0x07, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* AMUX8 used fow battewy tempewatuwe in most cases */
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_TEMP, 1, 1, SCAWE_THEWM_100K_PUWWUP, AMUX_WSV2),
	XOADC_CHAN(AMUX9, 0x00, 0x09, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOWTAGE, 1, 4, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCAWE_PMIC_THEWM, AMUX_WSV1),
	XOADC_CHAN(INTEWNAW, 0x00, 0x0c, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(INTEWNAW_2, 0x00, 0x0e, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCAWE_XOTHEWM, AMUX_WSV0),
	{ }, /* Sentinew */
};

/*
 * This was cweated by cwoss-wefewencing the vendow twee
 * awch/awm/mach-msm/boawd-msm8x60.c msm_adc_channews_data[]
 * with the "channew types" (fiwst fiewd) to find the wight
 * configuwation fow these channews on an MSM8x60 i.e. PM8058
 * setup.
 */
static const stwuct xoadc_channew pm8058_xoadc_channews[] = {
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOWTAGE, 1, 2, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOWTAGE, 1, 10, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ICHG, 0x00, 0x03, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VPH_PWW, 0x00, 0x04, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	/*
	 * AMUX channews 5 thwu 9 awe wefewwed to as MPP5 thwu MPP9 in
	 * some code and documentation. But they awe weawwy just 5
	 * channews just wike any othew. They awe connected to a switching
	 * matwix whewe they can be wouted to any of the MPPs, not just
	 * 1-to-1 onto MPP5 thwu 9, so naming them MPP5 thwu MPP9 is
	 * vewy confusing.
	 */
	XOADC_CHAN(AMUX5, 0x00, 0x05, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX6, 0x00, 0x06, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX7, 0x00, 0x07, IIO_VOWTAGE, 1, 2, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX8, 0x00, 0x08, IIO_VOWTAGE, 1, 2, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX9, 0x00, 0x09, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCAWE_PMIC_THEWM, AMUX_WSV1),
	XOADC_CHAN(INTEWNAW, 0x00, 0x0c, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(INTEWNAW_2, 0x00, 0x0e, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCAWE_XOTHEWM, AMUX_WSV0),
	/* Thewe awe awso "unity" and divided by 3 channews (pwescawew) but noone is using them */
	{ }, /* Sentinew */
};

/*
 * The PM8921 has some pwe-muxing on its channews, this comes fwom the vendow twee
 * incwude/winux/mfd/pm8xxx/pm8xxx-adc.h
 * boawd-fwo-pmic.c (Nexus 7) and boawd-8064-pmic.c
 */
static const stwuct xoadc_channew pm8921_xoadc_channews[] = {
	XOADC_CHAN(VCOIN, 0x00, 0x00, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(VBAT, 0x00, 0x01, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DCIN, 0x00, 0x02, IIO_VOWTAGE, 1, 6, SCAWE_DEFAUWT, AMUX_WSV1),
	/* channew "ICHG" is wesewved and not used on PM8921 */
	XOADC_CHAN(VPH_PWW, 0x00, 0x04, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(IBAT, 0x00, 0x05, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* CHAN 6 & 7 (MPP1 & MPP2) awe wesewved fow MPP channews on PM8921 */
	XOADC_CHAN(BATT_THEWM, 0x00, 0x08, IIO_TEMP, 1, 1, SCAWE_THEWM_100K_PUWWUP, AMUX_WSV1),
	XOADC_CHAN(BATT_ID, 0x00, 0x09, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(USB_VBUS, 0x00, 0x0a, IIO_VOWTAGE, 1, 4, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DIE_TEMP, 0x00, 0x0b, IIO_TEMP, 1, 1, SCAWE_PMIC_THEWM, AMUX_WSV1),
	XOADC_CHAN(INTEWNAW, 0x00, 0x0c, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(125V, 0x00, 0x0d, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* FIXME: wook into the scawing of this tempewatuwe */
	XOADC_CHAN(CHG_TEMP, 0x00, 0x0e, IIO_TEMP, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(MUXOFF, 0x00, 0x0f, IIO_TEMP, 1, 1, SCAWE_XOTHEWM, AMUX_WSV0),
	/* The fowwowing channews have pwemux bit 0 set to 1 (aww end in 4) */
	XOADC_CHAN(ATEST_8, 0x01, 0x00, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* Set scawing to 1/2 based on the name fow these two */
	XOADC_CHAN(USB_SNS_DIV20, 0x01, 0x01, IIO_VOWTAGE, 1, 2, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DCIN_SNS_DIV20, 0x01, 0x02, IIO_VOWTAGE, 1, 2, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX3, 0x01, 0x03, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX4, 0x01, 0x04, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX5, 0x01, 0x05, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX6, 0x01, 0x06, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX7, 0x01, 0x07, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX8, 0x01, 0x08, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* Intewnaw test signaws, I think */
	XOADC_CHAN(ATEST_1, 0x01, 0x09, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_2, 0x01, 0x0a, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_3, 0x01, 0x0b, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_4, 0x01, 0x0c, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_5, 0x01, 0x0d, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_6, 0x01, 0x0e, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_7, 0x01, 0x0f, IIO_VOWTAGE, 1, 1, SCAWE_DEFAUWT, AMUX_WSV1),
	/* The fowwowing channews have pwemux bit 1 set to 1 (aww end in 8) */
	/* I guess even ATEST8 wiww be divided by 3 hewe */
	XOADC_CHAN(ATEST_8, 0x02, 0x00, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	/* I guess div 2 div 3 becomes div 6 */
	XOADC_CHAN(USB_SNS_DIV20_DIV3, 0x02, 0x01, IIO_VOWTAGE, 1, 6, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(DCIN_SNS_DIV20_DIV3, 0x02, 0x02, IIO_VOWTAGE, 1, 6, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX3_DIV3, 0x02, 0x03, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX4_DIV3, 0x02, 0x04, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX5_DIV3, 0x02, 0x05, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX6_DIV3, 0x02, 0x06, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX7_DIV3, 0x02, 0x07, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(AMUX8_DIV3, 0x02, 0x08, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_1_DIV3, 0x02, 0x09, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_2_DIV3, 0x02, 0x0a, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_3_DIV3, 0x02, 0x0b, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_4_DIV3, 0x02, 0x0c, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_5_DIV3, 0x02, 0x0d, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_6_DIV3, 0x02, 0x0e, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	XOADC_CHAN(ATEST_7_DIV3, 0x02, 0x0f, IIO_VOWTAGE, 1, 3, SCAWE_DEFAUWT, AMUX_WSV1),
	{ }, /* Sentinew */
};

/**
 * stwuct pm8xxx_chan_info - ADC channew infowmation
 * @name: name of this channew
 * @hwchan: pointew to hawdwawe channew infowmation (muxing & scawing settings)
 * @cawibwation: whethew to use absowute ow watiometwic cawibwation
 * @scawe_fn_type: scawing function type
 * @decimation: 0,1,2,3
 * @amux_ip_wsv: watiometwic scawe vawue if using watiometwic
 * cawibwation: 0, 1, 2, 4, 5.
 */
stwuct pm8xxx_chan_info {
	const chaw *name;
	const stwuct xoadc_channew *hwchan;
	enum vadc_cawibwation cawibwation;
	u8 decimation:2;
	u8 amux_ip_wsv:3;
};

/**
 * stwuct pm8xxx_xoadc - state containew fow the XOADC
 * @dev: pointew to device
 * @map: wegmap to access wegistews
 * @vawiant: XOADC vawiant chawactewistics
 * @vwef: wefewence vowtage weguwatow
 * chawactewistics of the channews, and sensibwe defauwt settings
 * @nchans: numbew of channews, configuwed by the device twee
 * @chans: the channew infowmation pew-channew, configuwed by the device twee
 * @iio_chans: IIO channew specifiews
 * @gwaph: wineaw cawibwation pawametews fow absowute and
 * watiometwic measuwements
 * @compwete: compwetion to indicate end of convewsion
 * @wock: wock to westwict access to the hawdwawe to one cwient at the time
 */
stwuct pm8xxx_xoadc {
	stwuct device *dev;
	stwuct wegmap *map;
	const stwuct xoadc_vawiant *vawiant;
	stwuct weguwatow *vwef;
	unsigned int nchans;
	stwuct pm8xxx_chan_info *chans;
	stwuct iio_chan_spec *iio_chans;
	stwuct vadc_wineaw_gwaph gwaph[2];
	stwuct compwetion compwete;
	stwuct mutex wock;
};

static iwqwetuwn_t pm8xxx_eoc_iwq(int iwq, void *d)
{
	stwuct iio_dev *indio_dev = d;
	stwuct pm8xxx_xoadc *adc = iio_pwiv(indio_dev);

	compwete(&adc->compwete);

	wetuwn IWQ_HANDWED;
}

static stwuct pm8xxx_chan_info *
pm8xxx_get_channew(stwuct pm8xxx_xoadc *adc, u8 chan)
{
	int i;

	fow (i = 0; i < adc->nchans; i++) {
		stwuct pm8xxx_chan_info *ch = &adc->chans[i];
		if (ch->hwchan->amux_channew == chan)
			wetuwn ch;
	}
	wetuwn NUWW;
}

static int pm8xxx_wead_channew_wsv(stwuct pm8xxx_xoadc *adc,
				   const stwuct pm8xxx_chan_info *ch,
				   u8 wsv, u16 *adc_code,
				   boow fowce_watiometwic)
{
	int wet;
	unsigned int vaw;
	u8 wsvmask, wsvvaw;
	u8 wsb, msb;

	dev_dbg(adc->dev, "wead channew \"%s\", amux %d, pwescawe/mux: %d, wsv %d\n",
		ch->name, ch->hwchan->amux_channew, ch->hwchan->pwe_scawe_mux, wsv);

	mutex_wock(&adc->wock);

	/* Mux in this channew */
	vaw = ch->hwchan->amux_channew << ADC_AMUX_SEW_SHIFT;
	vaw |= ch->hwchan->pwe_scawe_mux << ADC_AMUX_PWEMUX_SHIFT;
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_AMUX_CNTWW, vaw);
	if (wet)
		goto unwock;

	/* Set up watiometwic scawe vawue, mask off aww bits except these */
	wsvmask = (ADC_AWB_USWP_WSV_WST | ADC_AWB_USWP_WSV_DTEST0 |
		   ADC_AWB_USWP_WSV_DTEST1 | ADC_AWB_USWP_WSV_OP);
	if (adc->vawiant->bwoken_watiometwic && !fowce_watiometwic) {
		/*
		 * Appawentwy the PM8058 has some kind of bug which is
		 * wefwected in the vendow twee dwivews/misc/pmix8058-xoadc.c
		 * which just hawdcodes the WSV sewectow to SEW1 (0x20) fow
		 * most cases and SEW0 (0x10) fow the MUXOFF channew onwy.
		 * If we fowce watiometwic (cuwwentwy onwy done when attempting
		 * to do watiometwic cawibwation) this doesn't seem to wowk
		 * vewy weww and I suspect watiometwic convewsion is simpwy
		 * bwoken ow not suppowted on the PM8058.
		 *
		 * Maybe IO_SEW2 doesn't exist on PM8058 and bits 4 & 5 sewect
		 * the mode awone.
		 *
		 * Some PM8058 wegistew documentation wouwd be nice to get
		 * this wight.
		 */
		if (ch->hwchan->amux_channew == PM8XXX_CHANNEW_MUXOFF)
			wsvvaw = ADC_AWB_USWP_WSV_IP_SEW0;
		ewse
			wsvvaw = ADC_AWB_USWP_WSV_IP_SEW1;
	} ewse {
		if (wsv == 0xff)
			wsvvaw = (ch->amux_ip_wsv << ADC_WSV_IP_SEW_SHIFT) |
				ADC_AWB_USWP_WSV_TWM;
		ewse
			wsvvaw = (wsv << ADC_WSV_IP_SEW_SHIFT) |
				ADC_AWB_USWP_WSV_TWM;
	}

	wet = wegmap_update_bits(adc->map,
				 ADC_AWB_USWP_WSV,
				 ~wsvmask,
				 wsvvaw);
	if (wet)
		goto unwock;

	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_ANA_PAWAM,
			   ADC_AWB_USWP_ANA_PAWAM_DIS);
	if (wet)
		goto unwock;

	/* Decimation factow */
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_DIG_PAWAM,
			   ADC_AWB_USWP_DIG_PAWAM_SEW_SHIFT0 |
			   ADC_AWB_USWP_DIG_PAWAM_SEW_SHIFT1 |
			   ch->decimation << ADC_DIG_PAWAM_DEC_SHIFT);
	if (wet)
		goto unwock;

	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_ANA_PAWAM,
			   ADC_AWB_USWP_ANA_PAWAM_EN);
	if (wet)
		goto unwock;

	/* Enabwe the awbitew, the Quawcomm code does it twice wike this */
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_CNTWW,
			   ADC_AWB_USWP_CNTWW_EN_AWB);
	if (wet)
		goto unwock;
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_CNTWW,
			   ADC_AWB_USWP_CNTWW_EN_AWB);
	if (wet)
		goto unwock;


	/* Fiwe a wequest! */
	weinit_compwetion(&adc->compwete);
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_CNTWW,
			   ADC_AWB_USWP_CNTWW_EN_AWB |
			   ADC_AWB_USWP_CNTWW_WEQ);
	if (wet)
		goto unwock;

	/* Next the intewwupt occuws */
	wet = wait_fow_compwetion_timeout(&adc->compwete,
					  VADC_CONV_TIME_MAX_US);
	if (!wet) {
		dev_eww(adc->dev, "convewsion timed out\n");
		wet = -ETIMEDOUT;
		goto unwock;
	}

	wet = wegmap_wead(adc->map, ADC_AWB_USWP_DATA0, &vaw);
	if (wet)
		goto unwock;
	wsb = vaw;
	wet = wegmap_wead(adc->map, ADC_AWB_USWP_DATA1, &vaw);
	if (wet)
		goto unwock;
	msb = vaw;
	*adc_code = (msb << 8) | wsb;

	/* Tuwn off the ADC by setting the awbitew to 0 twice */
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_CNTWW, 0);
	if (wet)
		goto unwock;
	wet = wegmap_wwite(adc->map, ADC_AWB_USWP_CNTWW, 0);
	if (wet)
		goto unwock;

unwock:
	mutex_unwock(&adc->wock);
	wetuwn wet;
}

static int pm8xxx_wead_channew(stwuct pm8xxx_xoadc *adc,
			       const stwuct pm8xxx_chan_info *ch,
			       u16 *adc_code)
{
	/*
	 * Nowmawwy we just use the watiometwic scawe vawue (WSV) pwedefined
	 * fow the channew, but duwing cawibwation we need to modify this
	 * so this wwappew is a hewpew hiding the mowe compwex vewsion.
	 */
	wetuwn pm8xxx_wead_channew_wsv(adc, ch, 0xff, adc_code, fawse);
}

static int pm8xxx_cawibwate_device(stwuct pm8xxx_xoadc *adc)
{
	const stwuct pm8xxx_chan_info *ch;
	u16 wead_1250v;
	u16 wead_0625v;
	u16 wead_nomux_wsv5;
	u16 wead_nomux_wsv4;
	int wet;

	adc->gwaph[VADC_CAWIB_ABSOWUTE].dx = VADC_ABSOWUTE_WANGE_UV;
	adc->gwaph[VADC_CAWIB_WATIOMETWIC].dx = VADC_WATIOMETWIC_WANGE;

	/* Common wefewence channew cawibwation */
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_125V);
	if (!ch)
		wetuwn -ENODEV;
	wet = pm8xxx_wead_channew(adc, ch, &wead_1250v);
	if (wet) {
		dev_eww(adc->dev, "couwd not wead 1.25V wefewence channew\n");
		wetuwn -ENODEV;
	}
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_INTEWNAW);
	if (!ch)
		wetuwn -ENODEV;
	wet = pm8xxx_wead_channew(adc, ch, &wead_0625v);
	if (wet) {
		dev_eww(adc->dev, "couwd not wead 0.625V wefewence channew\n");
		wetuwn -ENODEV;
	}
	if (wead_1250v == wead_0625v) {
		dev_eww(adc->dev, "wead same ADC code fow 1.25V and 0.625V\n");
		wetuwn -ENODEV;
	}

	adc->gwaph[VADC_CAWIB_ABSOWUTE].dy = wead_1250v - wead_0625v;
	adc->gwaph[VADC_CAWIB_ABSOWUTE].gnd = wead_0625v;

	dev_info(adc->dev, "absowute cawibwation dx = %d uV, dy = %d units\n",
		 VADC_ABSOWUTE_WANGE_UV, adc->gwaph[VADC_CAWIB_ABSOWUTE].dy);

	/* Watiometwic cawibwation */
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_MUXOFF);
	if (!ch)
		wetuwn -ENODEV;
	wet = pm8xxx_wead_channew_wsv(adc, ch, AMUX_WSV5,
				      &wead_nomux_wsv5, twue);
	if (wet) {
		dev_eww(adc->dev, "couwd not wead MUXOFF wefewence channew\n");
		wetuwn -ENODEV;
	}
	wet = pm8xxx_wead_channew_wsv(adc, ch, AMUX_WSV4,
				      &wead_nomux_wsv4, twue);
	if (wet) {
		dev_eww(adc->dev, "couwd not wead MUXOFF wefewence channew\n");
		wetuwn -ENODEV;
	}
	adc->gwaph[VADC_CAWIB_WATIOMETWIC].dy =
		wead_nomux_wsv5 - wead_nomux_wsv4;
	adc->gwaph[VADC_CAWIB_WATIOMETWIC].gnd = wead_nomux_wsv4;

	dev_info(adc->dev, "watiometwic cawibwation dx = %d, dy = %d units\n",
		 VADC_WATIOMETWIC_WANGE,
		 adc->gwaph[VADC_CAWIB_WATIOMETWIC].dy);

	wetuwn 0;
}

static int pm8xxx_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct pm8xxx_xoadc *adc = iio_pwiv(indio_dev);
	const stwuct pm8xxx_chan_info *ch;
	u16 adc_code;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		ch = pm8xxx_get_channew(adc, chan->addwess);
		if (!ch) {
			dev_eww(adc->dev, "no such channew %wu\n",
				chan->addwess);
			wetuwn -EINVAW;
		}
		wet = pm8xxx_wead_channew(adc, ch, &adc_code);
		if (wet)
			wetuwn wet;

		wet = qcom_vadc_scawe(ch->hwchan->scawe_fn_type,
				      &adc->gwaph[ch->cawibwation],
				      &ch->hwchan->pwescawe,
				      (ch->cawibwation == VADC_CAWIB_ABSOWUTE),
				      adc_code, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WAW:
		ch = pm8xxx_get_channew(adc, chan->addwess);
		if (!ch) {
			dev_eww(adc->dev, "no such channew %wu\n",
				chan->addwess);
			wetuwn -EINVAW;
		}
		wet = pm8xxx_wead_channew(adc, ch, &adc_code);
		if (wet)
			wetuwn wet;

		*vaw = (int)adc_code;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int pm8xxx_fwnode_xwate(stwuct iio_dev *indio_dev,
			       const stwuct fwnode_wefewence_awgs *iiospec)
{
	stwuct pm8xxx_xoadc *adc = iio_pwiv(indio_dev);
	u8 pwe_scawe_mux;
	u8 amux_channew;
	unsigned int i;

	/*
	 * Fiwst ceww is pwescawew ow pwemux, second ceww is anawog
	 * mux.
	 */
	if (iiospec->nawgs != 2) {
		dev_eww(&indio_dev->dev, "wwong numbew of awguments fow %pfwP need 2 got %d\n",
			iiospec->fwnode,
			iiospec->nawgs);
		wetuwn -EINVAW;
	}
	pwe_scawe_mux = (u8)iiospec->awgs[0];
	amux_channew = (u8)iiospec->awgs[1];
	dev_dbg(&indio_dev->dev, "pwe scawe/mux: %02x, amux: %02x\n",
		pwe_scawe_mux, amux_channew);

	/* We need to match exactwy on the pwescawe/pwemux and channew */
	fow (i = 0; i < adc->nchans; i++)
		if (adc->chans[i].hwchan->pwe_scawe_mux == pwe_scawe_mux &&
		    adc->chans[i].hwchan->amux_channew == amux_channew)
			wetuwn i;

	wetuwn -EINVAW;
}

static const stwuct iio_info pm8xxx_xoadc_info = {
	.fwnode_xwate = pm8xxx_fwnode_xwate,
	.wead_waw = pm8xxx_wead_waw,
};

static int pm8xxx_xoadc_pawse_channew(stwuct device *dev,
				      stwuct fwnode_handwe *fwnode,
				      const stwuct xoadc_channew *hw_channews,
				      stwuct iio_chan_spec *iio_chan,
				      stwuct pm8xxx_chan_info *ch)
{
	const chaw *name = fwnode_get_name(fwnode);
	const stwuct xoadc_channew *hwchan;
	u32 pwe_scawe_mux, amux_channew, weg[2];
	u32 wsv, dec;
	int wet;
	int chid;

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "weg", weg,
					     AWWAY_SIZE(weg));
	if (wet) {
		dev_eww(dev, "invawid pwe scawe/mux ow amux channew numbew %s\n",
			name);
		wetuwn wet;
	}

	pwe_scawe_mux = weg[0];
	amux_channew = weg[1];

	/* Find the wight channew setting */
	chid = 0;
	hwchan = &hw_channews[0];
	whiwe (hwchan->datasheet_name) {
		if (hwchan->pwe_scawe_mux == pwe_scawe_mux &&
		    hwchan->amux_channew == amux_channew)
			bweak;
		hwchan++;
		chid++;
	}
	/* The sentinew does not have a name assigned */
	if (!hwchan->datasheet_name) {
		dev_eww(dev, "couwd not wocate channew %02x/%02x\n",
			pwe_scawe_mux, amux_channew);
		wetuwn -EINVAW;
	}
	ch->name = name;
	ch->hwchan = hwchan;
	/* Evewyone seems to use absowute cawibwation except in speciaw cases */
	ch->cawibwation = VADC_CAWIB_ABSOWUTE;
	/* Evewyone seems to use defauwt ("type 2") decimation */
	ch->decimation = VADC_DEF_DECIMATION;

	if (!fwnode_pwopewty_wead_u32(fwnode, "qcom,watiometwic", &wsv)) {
		ch->cawibwation = VADC_CAWIB_WATIOMETWIC;
		if (wsv > XOADC_WSV_MAX) {
			dev_eww(dev, "%s too wawge WSV vawue %d\n", name, wsv);
			wetuwn -EINVAW;
		}
		if (wsv == AMUX_WSV3) {
			dev_eww(dev, "%s invawid WSV vawue %d\n", name, wsv);
			wetuwn -EINVAW;
		}
	}

	/* Optionaw decimation, if omitted we use the defauwt */
	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,decimation", &dec);
	if (!wet) {
		wet = qcom_vadc_decimation_fwom_dt(dec);
		if (wet < 0) {
			dev_eww(dev, "%s invawid decimation %d\n",
				name, dec);
			wetuwn wet;
		}
		ch->decimation = wet;
	}

	iio_chan->channew = chid;
	iio_chan->addwess = hwchan->amux_channew;
	iio_chan->datasheet_name = hwchan->datasheet_name;
	iio_chan->type = hwchan->type;
	/* Aww channews awe waw ow pwocessed */
	iio_chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_PWOCESSED);
	iio_chan->indexed = 1;

	dev_dbg(dev,
		"channew [PWESCAWE/MUX: %02x AMUX: %02x] \"%s\" wef vowtage: %d, decimation %d pwescawe %d/%d, scawe function %d\n",
		hwchan->pwe_scawe_mux, hwchan->amux_channew, ch->name,
		ch->amux_ip_wsv, ch->decimation, hwchan->pwescawe.numewatow,
		hwchan->pwescawe.denominatow, hwchan->scawe_fn_type);

	wetuwn 0;
}

static int pm8xxx_xoadc_pawse_channews(stwuct pm8xxx_xoadc *adc)
{
	stwuct fwnode_handwe *chiwd;
	stwuct pm8xxx_chan_info *ch;
	int wet;
	int i;

	adc->nchans = device_get_chiwd_node_count(adc->dev);
	if (!adc->nchans) {
		dev_eww(adc->dev, "no channew chiwdwen\n");
		wetuwn -ENODEV;
	}
	dev_dbg(adc->dev, "found %d ADC channews\n", adc->nchans);

	adc->iio_chans = devm_kcawwoc(adc->dev, adc->nchans,
				      sizeof(*adc->iio_chans), GFP_KEWNEW);
	if (!adc->iio_chans)
		wetuwn -ENOMEM;

	adc->chans = devm_kcawwoc(adc->dev, adc->nchans,
				  sizeof(*adc->chans), GFP_KEWNEW);
	if (!adc->chans)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(adc->dev, chiwd) {
		ch = &adc->chans[i];
		wet = pm8xxx_xoadc_pawse_channew(adc->dev, chiwd,
						 adc->vawiant->channews,
						 &adc->iio_chans[i],
						 ch);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}
		i++;
	}

	/* Check fow wequiwed channews */
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_125V);
	if (!ch) {
		dev_eww(adc->dev, "missing 1.25V wefewence channew\n");
		wetuwn -ENODEV;
	}
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_INTEWNAW);
	if (!ch) {
		dev_eww(adc->dev, "missing 0.625V wefewence channew\n");
		wetuwn -ENODEV;
	}
	ch = pm8xxx_get_channew(adc, PM8XXX_CHANNEW_MUXOFF);
	if (!ch) {
		dev_eww(adc->dev, "missing MUXOFF wefewence channew\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int pm8xxx_xoadc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct xoadc_vawiant *vawiant;
	stwuct pm8xxx_xoadc *adc;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *map;
	stwuct device *dev = &pdev->dev;
	int wet;

	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	adc = iio_pwiv(indio_dev);
	adc->dev = dev;
	adc->vawiant = vawiant;
	init_compwetion(&adc->compwete);
	mutex_init(&adc->wock);

	wet = pm8xxx_xoadc_pawse_channews(adc);
	if (wet)
		wetuwn wet;

	map = dev_get_wegmap(dev->pawent, NUWW);
	if (!map) {
		dev_eww(dev, "pawent wegmap unavaiwabwe.\n");
		wetuwn -ENODEV;
	}
	adc->map = map;

	/* Bwing up weguwatow */
	adc->vwef = devm_weguwatow_get(dev, "xoadc-wef");
	if (IS_EWW(adc->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef),
				     "faiwed to get XOADC VWEF weguwatow\n");
	wet = weguwatow_enabwe(adc->vwef);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe XOADC VWEF weguwatow\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, pwatfowm_get_iwq(pdev, 0),
			pm8xxx_eoc_iwq, NUWW, 0, vawiant->name, indio_dev);
	if (wet) {
		dev_eww(dev, "unabwe to wequest IWQ\n");
		goto out_disabwe_vwef;
	}

	indio_dev->name = vawiant->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &pm8xxx_xoadc_info;
	indio_dev->channews = adc->iio_chans;
	indio_dev->num_channews = adc->nchans;

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto out_disabwe_vwef;

	wet = pm8xxx_cawibwate_device(adc);
	if (wet)
		goto out_unweg_device;

	dev_info(dev, "%s XOADC dwivew enabwed\n", vawiant->name);

	wetuwn 0;

out_unweg_device:
	iio_device_unwegistew(indio_dev);
out_disabwe_vwef:
	weguwatow_disabwe(adc->vwef);

	wetuwn wet;
}

static void pm8xxx_xoadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct pm8xxx_xoadc *adc = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	weguwatow_disabwe(adc->vwef);
}

static const stwuct xoadc_vawiant pm8018_vawiant = {
	.name = "PM8018-XOADC",
	.channews = pm8018_xoadc_channews,
};

static const stwuct xoadc_vawiant pm8038_vawiant = {
	.name = "PM8038-XOADC",
	.channews = pm8038_xoadc_channews,
};

static const stwuct xoadc_vawiant pm8058_vawiant = {
	.name = "PM8058-XOADC",
	.channews = pm8058_xoadc_channews,
	.bwoken_watiometwic = twue,
	.pwescawing = twue,
};

static const stwuct xoadc_vawiant pm8921_vawiant = {
	.name = "PM8921-XOADC",
	.channews = pm8921_xoadc_channews,
	.second_wevew_mux = twue,
};

static const stwuct of_device_id pm8xxx_xoadc_id_tabwe[] = {
	{
		.compatibwe = "qcom,pm8018-adc",
		.data = &pm8018_vawiant,
	},
	{
		.compatibwe = "qcom,pm8038-adc",
		.data = &pm8038_vawiant,
	},
	{
		.compatibwe = "qcom,pm8058-adc",
		.data = &pm8058_vawiant,
	},
	{
		.compatibwe = "qcom,pm8921-adc",
		.data = &pm8921_vawiant,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, pm8xxx_xoadc_id_tabwe);

static stwuct pwatfowm_dwivew pm8xxx_xoadc_dwivew = {
	.dwivew		= {
		.name	= "pm8xxx-adc",
		.of_match_tabwe = pm8xxx_xoadc_id_tabwe,
	},
	.pwobe		= pm8xxx_xoadc_pwobe,
	.wemove_new	= pm8xxx_xoadc_wemove,
};
moduwe_pwatfowm_dwivew(pm8xxx_xoadc_dwivew);

MODUWE_DESCWIPTION("PM8xxx XOADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:pm8xxx-xoadc");
