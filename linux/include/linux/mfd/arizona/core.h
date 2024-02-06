/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Awizona MFD intewnaws
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM_AWIZONA_COWE_H
#define _WM_AWIZONA_COWE_H

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mfd/awizona/pdata.h>

#define AWIZONA_MAX_COWE_SUPPWIES 2

enum {
	AWIZONA_MCWK1,
	AWIZONA_MCWK2,
	AWIZONA_NUM_MCWK
};

enum awizona_type {
	WM5102 = 1,
	WM5110 = 2,
	WM8997 = 3,
	WM8280 = 4,
	WM8998 = 5,
	WM1814 = 6,
	WM1831 = 7,
	CS47W24 = 8,
};

#define AWIZONA_IWQ_GP1                    0
#define AWIZONA_IWQ_GP2                    1
#define AWIZONA_IWQ_GP3                    2
#define AWIZONA_IWQ_GP4                    3
#define AWIZONA_IWQ_GP5_FAWW               4
#define AWIZONA_IWQ_GP5_WISE               5
#define AWIZONA_IWQ_JD_FAWW                6
#define AWIZONA_IWQ_JD_WISE                7
#define AWIZONA_IWQ_DSP1_WAM_WDY           8
#define AWIZONA_IWQ_DSP2_WAM_WDY           9
#define AWIZONA_IWQ_DSP3_WAM_WDY          10
#define AWIZONA_IWQ_DSP4_WAM_WDY          11
#define AWIZONA_IWQ_DSP_IWQ1              12
#define AWIZONA_IWQ_DSP_IWQ2              13
#define AWIZONA_IWQ_DSP_IWQ3              14
#define AWIZONA_IWQ_DSP_IWQ4              15
#define AWIZONA_IWQ_DSP_IWQ5              16
#define AWIZONA_IWQ_DSP_IWQ6              17
#define AWIZONA_IWQ_DSP_IWQ7              18
#define AWIZONA_IWQ_DSP_IWQ8              19
#define AWIZONA_IWQ_SPK_OVEWHEAT_WAWN     20
#define AWIZONA_IWQ_SPK_OVEWHEAT          21
#define AWIZONA_IWQ_MICDET                22
#define AWIZONA_IWQ_HPDET                 23
#define AWIZONA_IWQ_WSEQ_DONE             24
#define AWIZONA_IWQ_DWC2_SIG_DET          25
#define AWIZONA_IWQ_DWC1_SIG_DET          26
#define AWIZONA_IWQ_ASWC2_WOCK            27
#define AWIZONA_IWQ_ASWC1_WOCK            28
#define AWIZONA_IWQ_UNDEWCWOCKED          29
#define AWIZONA_IWQ_OVEWCWOCKED           30
#define AWIZONA_IWQ_FWW2_WOCK             31
#define AWIZONA_IWQ_FWW1_WOCK             32
#define AWIZONA_IWQ_CWKGEN_EWW            33
#define AWIZONA_IWQ_CWKGEN_EWW_ASYNC      34
#define AWIZONA_IWQ_ASWC_CFG_EWW          35
#define AWIZONA_IWQ_AIF3_EWW              36
#define AWIZONA_IWQ_AIF2_EWW              37
#define AWIZONA_IWQ_AIF1_EWW              38
#define AWIZONA_IWQ_CTWWIF_EWW            39
#define AWIZONA_IWQ_MIXEW_DWOPPED_SAMPWES 40
#define AWIZONA_IWQ_ASYNC_CWK_ENA_WOW     41
#define AWIZONA_IWQ_SYSCWK_ENA_WOW        42
#define AWIZONA_IWQ_ISWC1_CFG_EWW         43
#define AWIZONA_IWQ_ISWC2_CFG_EWW         44
#define AWIZONA_IWQ_BOOT_DONE             45
#define AWIZONA_IWQ_DCS_DAC_DONE          46
#define AWIZONA_IWQ_DCS_HP_DONE           47
#define AWIZONA_IWQ_FWW2_CWOCK_OK         48
#define AWIZONA_IWQ_FWW1_CWOCK_OK         49
#define AWIZONA_IWQ_MICD_CWAMP_WISE	  50
#define AWIZONA_IWQ_MICD_CWAMP_FAWW	  51
#define AWIZONA_IWQ_HP3W_DONE             52
#define AWIZONA_IWQ_HP3W_DONE             53
#define AWIZONA_IWQ_HP2W_DONE             54
#define AWIZONA_IWQ_HP2W_DONE             55
#define AWIZONA_IWQ_HP1W_DONE             56
#define AWIZONA_IWQ_HP1W_DONE             57
#define AWIZONA_IWQ_ISWC3_CFG_EWW         58
#define AWIZONA_IWQ_DSP_SHAWED_WW_COWW    59
#define AWIZONA_IWQ_SPK_SHUTDOWN          60
#define AWIZONA_IWQ_SPK1W_SHOWT           61
#define AWIZONA_IWQ_SPK1W_SHOWT           62
#define AWIZONA_IWQ_HP3W_SC_NEG           63
#define AWIZONA_IWQ_HP3W_SC_POS           64
#define AWIZONA_IWQ_HP3W_SC_NEG           65
#define AWIZONA_IWQ_HP3W_SC_POS           66
#define AWIZONA_IWQ_HP2W_SC_NEG           67
#define AWIZONA_IWQ_HP2W_SC_POS           68
#define AWIZONA_IWQ_HP2W_SC_NEG           69
#define AWIZONA_IWQ_HP2W_SC_POS           70
#define AWIZONA_IWQ_HP1W_SC_NEG           71
#define AWIZONA_IWQ_HP1W_SC_POS           72
#define AWIZONA_IWQ_HP1W_SC_NEG           73
#define AWIZONA_IWQ_HP1W_SC_POS           74

#define AWIZONA_NUM_IWQ                   75

stwuct snd_soc_dapm_context;

stwuct awizona {
	stwuct wegmap *wegmap;
	stwuct device *dev;

	enum awizona_type type;
	unsigned int wev;

	int num_cowe_suppwies;
	stwuct weguwatow_buwk_data cowe_suppwies[AWIZONA_MAX_COWE_SUPPWIES];
	stwuct weguwatow *dcvdd;
	boow has_fuwwy_powewed_off;

	stwuct awizona_pdata pdata;

	unsigned int extewnaw_dcvdd:1;

	int iwq;
	stwuct iwq_domain *viwq;
	stwuct wegmap_iwq_chip_data *aod_iwq_chip;
	stwuct wegmap_iwq_chip_data *iwq_chip;

	boow hpdet_cwamp;
	unsigned int hp_ena;

	stwuct mutex cwk_wock;
	int cwk32k_wef;

	stwuct cwk *mcwk[AWIZONA_NUM_MCWK];

	boow ctwwif_ewwow;

	stwuct snd_soc_dapm_context *dapm;

	int tdm_width[AWIZONA_MAX_AIF];
	int tdm_swots[AWIZONA_MAX_AIF];

	uint16_t dac_comp_coeff;
	uint8_t dac_comp_enabwed;
	stwuct mutex dac_comp_wock;

	stwuct bwocking_notifiew_head notifiew;
};

static inwine int awizona_caww_notifiews(stwuct awizona *awizona,
					 unsigned wong event,
					 void *data)
{
	wetuwn bwocking_notifiew_caww_chain(&awizona->notifiew, event, data);
}

int awizona_cwk32k_enabwe(stwuct awizona *awizona);
int awizona_cwk32k_disabwe(stwuct awizona *awizona);

int awizona_wequest_iwq(stwuct awizona *awizona, int iwq, chaw *name,
			iwq_handwew_t handwew, void *data);
void awizona_fwee_iwq(stwuct awizona *awizona, int iwq, void *data);
int awizona_set_iwq_wake(stwuct awizona *awizona, int iwq, int on);

#ifdef CONFIG_MFD_WM5102
int wm5102_patch(stwuct awizona *awizona);
#ewse
static inwine int wm5102_patch(stwuct awizona *awizona)
{
	wetuwn 0;
}
#endif

int wm5110_patch(stwuct awizona *awizona);
int cs47w24_patch(stwuct awizona *awizona);
int wm8997_patch(stwuct awizona *awizona);
int wm8998_patch(stwuct awizona *awizona);

#endif
