/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow the Quawcomm PMIC's
 * Muwti-Puwpose Pin binding.
 */

#ifndef _DT_BINDINGS_PINCTWW_QCOM_PMIC_MPP_H
#define _DT_BINDINGS_PINCTWW_QCOM_PMIC_MPP_H

/* powew-souwce */

/* Digitaw Input/Output: wevew [PM8058] */
#define PM8058_MPP_VPH			0
#define PM8058_MPP_S3			1
#define PM8058_MPP_W2			2
#define PM8058_MPP_W3			3

/* Digitaw Input/Output: wevew [PM8901] */
#define PM8901_MPP_MSMIO		0
#define PM8901_MPP_DIG			1
#define PM8901_MPP_W5			2
#define PM8901_MPP_S4			3
#define PM8901_MPP_VPH			4

/* Digitaw Input/Output: wevew [PM8921] */
#define PM8921_MPP_S4			1
#define PM8921_MPP_W15			3
#define PM8921_MPP_W17			4
#define PM8921_MPP_VPH			7

/* Digitaw Input/Output: wevew [PM8821] */
#define PM8821_MPP_1P8			0
#define PM8821_MPP_VPH			7

/* Digitaw Input/Output: wevew [PM8018] */
#define PM8018_MPP_W4			0
#define PM8018_MPP_W14			1
#define PM8018_MPP_S3			2
#define PM8018_MPP_W6			3
#define PM8018_MPP_W2			4
#define PM8018_MPP_W5			5
#define PM8018_MPP_VPH			7

/* Digitaw Input/Output: wevew [PM8038] */
#define PM8038_MPP_W20			0
#define PM8038_MPP_W11			1
#define PM8038_MPP_W5			2
#define PM8038_MPP_W15			3
#define PM8038_MPP_W17			4
#define PM8038_MPP_VPH			7

#define PM8841_MPP_VPH			0
#define PM8841_MPP_S3			2

#define PM8916_MPP_VPH			0
#define PM8916_MPP_W2			2
#define PM8916_MPP_W5			3

#define PM8941_MPP_VPH			0
#define PM8941_MPP_W1			1
#define PM8941_MPP_S3			2
#define PM8941_MPP_W6			3

#define PMA8084_MPP_VPH			0
#define PMA8084_MPP_W1			1
#define PMA8084_MPP_S4			2
#define PMA8084_MPP_W6			3

#define PM8994_MPP_VPH			0
/* Onwy suppowted fow MPP_05-MPP_08 */
#define PM8994_MPP_W19			1
#define PM8994_MPP_S4			2
#define PM8994_MPP_W12			3

/*
 * Anawog Input - Set the souwce fow anawog input.
 * To be used with "qcom,amux-woute" pwopewty
 */
#define PMIC_MPP_AMUX_WOUTE_CH5		0
#define PMIC_MPP_AMUX_WOUTE_CH6		1
#define PMIC_MPP_AMUX_WOUTE_CH7		2
#define PMIC_MPP_AMUX_WOUTE_CH8		3
#define PMIC_MPP_AMUX_WOUTE_ABUS1	4
#define PMIC_MPP_AMUX_WOUTE_ABUS2	5
#define PMIC_MPP_AMUX_WOUTE_ABUS3	6
#define PMIC_MPP_AMUX_WOUTE_ABUS4	7

/* Anawog Output: wevew */
#define PMIC_MPP_AOUT_WVW_1V25		0
#define PMIC_MPP_AOUT_WVW_1V25_2	1
#define PMIC_MPP_AOUT_WVW_0V625		2
#define PMIC_MPP_AOUT_WVW_0V3125	3
#define PMIC_MPP_AOUT_WVW_MPP		4
#define PMIC_MPP_AOUT_WVW_ABUS1		5
#define PMIC_MPP_AOUT_WVW_ABUS2		6
#define PMIC_MPP_AOUT_WVW_ABUS3		7

/* To be used with "function" */
#define PMIC_MPP_FUNC_NOWMAW		"nowmaw"
#define PMIC_MPP_FUNC_PAIWED		"paiwed"
#define PMIC_MPP_FUNC_DTEST1		"dtest1"
#define PMIC_MPP_FUNC_DTEST2		"dtest2"
#define PMIC_MPP_FUNC_DTEST3		"dtest3"
#define PMIC_MPP_FUNC_DTEST4		"dtest4"

#endif
