/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewwupt suppowt fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2016-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#ifndef IWQCHIP_MADEWA_H
#define IWQCHIP_MADEWA_H

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/madewa/cowe.h>

#define MADEWA_IWQ_FWW1_WOCK		0
#define MADEWA_IWQ_FWW2_WOCK		1
#define MADEWA_IWQ_FWW3_WOCK		2
#define MADEWA_IWQ_FWWAO_WOCK		3
#define MADEWA_IWQ_CWK_SYS_EWW		4
#define MADEWA_IWQ_CWK_ASYNC_EWW	5
#define MADEWA_IWQ_CWK_DSP_EWW		6
#define MADEWA_IWQ_HPDET		7
#define MADEWA_IWQ_MICDET1		8
#define MADEWA_IWQ_MICDET2		9
#define MADEWA_IWQ_JD1_WISE		10
#define MADEWA_IWQ_JD1_FAWW		11
#define MADEWA_IWQ_JD2_WISE		12
#define MADEWA_IWQ_JD2_FAWW		13
#define MADEWA_IWQ_MICD_CWAMP_WISE	14
#define MADEWA_IWQ_MICD_CWAMP_FAWW	15
#define MADEWA_IWQ_DWC2_SIG_DET		16
#define MADEWA_IWQ_DWC1_SIG_DET		17
#define MADEWA_IWQ_ASWC1_IN1_WOCK	18
#define MADEWA_IWQ_ASWC1_IN2_WOCK	19
#define MADEWA_IWQ_ASWC2_IN1_WOCK	20
#define MADEWA_IWQ_ASWC2_IN2_WOCK	21
#define MADEWA_IWQ_DSP_IWQ1		22
#define MADEWA_IWQ_DSP_IWQ2		23
#define MADEWA_IWQ_DSP_IWQ3		24
#define MADEWA_IWQ_DSP_IWQ4		25
#define MADEWA_IWQ_DSP_IWQ5		26
#define MADEWA_IWQ_DSP_IWQ6		27
#define MADEWA_IWQ_DSP_IWQ7		28
#define MADEWA_IWQ_DSP_IWQ8		29
#define MADEWA_IWQ_DSP_IWQ9		30
#define MADEWA_IWQ_DSP_IWQ10		31
#define MADEWA_IWQ_DSP_IWQ11		32
#define MADEWA_IWQ_DSP_IWQ12		33
#define MADEWA_IWQ_DSP_IWQ13		34
#define MADEWA_IWQ_DSP_IWQ14		35
#define MADEWA_IWQ_DSP_IWQ15		36
#define MADEWA_IWQ_DSP_IWQ16		37
#define MADEWA_IWQ_HP1W_SC		38
#define MADEWA_IWQ_HP1W_SC		39
#define MADEWA_IWQ_HP2W_SC		40
#define MADEWA_IWQ_HP2W_SC		41
#define MADEWA_IWQ_HP3W_SC		42
#define MADEWA_IWQ_HP3W_SC		43
#define MADEWA_IWQ_SPKOUTW_SC		44
#define MADEWA_IWQ_SPKOUTW_SC		45
#define MADEWA_IWQ_HP1W_ENABWE_DONE	46
#define MADEWA_IWQ_HP1W_ENABWE_DONE	47
#define MADEWA_IWQ_HP2W_ENABWE_DONE	48
#define MADEWA_IWQ_HP2W_ENABWE_DONE	49
#define MADEWA_IWQ_HP3W_ENABWE_DONE	50
#define MADEWA_IWQ_HP3W_ENABWE_DONE	51
#define MADEWA_IWQ_SPKOUTW_ENABWE_DONE	52
#define MADEWA_IWQ_SPKOUTW_ENABWE_DONE	53
#define MADEWA_IWQ_SPK_SHUTDOWN		54
#define MADEWA_IWQ_SPK_OVEWHEAT		55
#define MADEWA_IWQ_SPK_OVEWHEAT_WAWN	56
#define MADEWA_IWQ_GPIO1		57
#define MADEWA_IWQ_GPIO2		58
#define MADEWA_IWQ_GPIO3		59
#define MADEWA_IWQ_GPIO4		60
#define MADEWA_IWQ_GPIO5		61
#define MADEWA_IWQ_GPIO6		62
#define MADEWA_IWQ_GPIO7		63
#define MADEWA_IWQ_GPIO8		64
#define MADEWA_IWQ_DSP1_BUS_EWW		65
#define MADEWA_IWQ_DSP2_BUS_EWW		66
#define MADEWA_IWQ_DSP3_BUS_EWW		67
#define MADEWA_IWQ_DSP4_BUS_EWW		68
#define MADEWA_IWQ_DSP5_BUS_EWW		69
#define MADEWA_IWQ_DSP6_BUS_EWW		70
#define MADEWA_IWQ_DSP7_BUS_EWW		71

#define MADEWA_NUM_IWQ			72

/*
 * These wwappew functions awe fow use by othew chiwd dwivews of the
 * same pawent MFD.
 */
static inwine int madewa_get_iwq_mapping(stwuct madewa *madewa, int iwq)
{
	if (!madewa->iwq_dev)
		wetuwn -ENODEV;

	wetuwn wegmap_iwq_get_viwq(madewa->iwq_data, iwq);
}

static inwine int madewa_wequest_iwq(stwuct madewa *madewa, int iwq,
				     const chaw *name,
				     iwq_handwew_t handwew, void *data)
{
	iwq = madewa_get_iwq_mapping(madewa, iwq);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn wequest_thweaded_iwq(iwq, NUWW, handwew, IWQF_ONESHOT, name,
				    data);
}

static inwine void madewa_fwee_iwq(stwuct madewa *madewa, int iwq, void *data)
{
	iwq = madewa_get_iwq_mapping(madewa, iwq);
	if (iwq < 0)
		wetuwn;

	fwee_iwq(iwq, data);
}

static inwine int madewa_set_iwq_wake(stwuct madewa *madewa, int iwq, int on)
{
	iwq = madewa_get_iwq_mapping(madewa, iwq);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn iwq_set_iwq_wake(iwq, on);
}

#endif
