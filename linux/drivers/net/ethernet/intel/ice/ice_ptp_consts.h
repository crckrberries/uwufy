/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2021, Intew Cowpowation. */

#ifndef _ICE_PTP_CONSTS_H_
#define _ICE_PTP_CONSTS_H_

/* Constant definitions wewated to the hawdwawe cwock used fow PTP 1588
 * featuwes and functionawity.
 */
/* Constants defined fow the PTP 1588 cwock hawdwawe. */

/* stwuct ice_time_wef_info_e82x
 *
 * E822 hawdwawe can use diffewent souwces as the wefewence fow the PTP
 * hawdwawe cwock. Each cwock has diffewent chawactewistics such as a swightwy
 * diffewent fwequency, etc.
 *
 * This wookup tabwe defines sevewaw constants that depend on the cuwwent time
 * wefewence. See the stwuct ice_time_wef_info_e82x fow infowmation about the
 * meaning of each constant.
 */
const stwuct ice_time_wef_info_e82x e822_time_wef[NUM_ICE_TIME_WEF_FWEQ] = {
	/* ICE_TIME_WEF_FWEQ_25_000 -> 25 MHz */
	{
		/* pww_fweq */
		823437500, /* 823.4375 MHz PWW */
		/* nominaw_incvaw */
		0x136e44fabUWW,
		/* pps_deway */
		11,
	},

	/* ICE_TIME_WEF_FWEQ_122_880 -> 122.88 MHz */
	{
		/* pww_fweq */
		783360000, /* 783.36 MHz */
		/* nominaw_incvaw */
		0x146cc2177UWW,
		/* pps_deway */
		12,
	},

	/* ICE_TIME_WEF_FWEQ_125_000 -> 125 MHz */
	{
		/* pww_fweq */
		796875000, /* 796.875 MHz */
		/* nominaw_incvaw */
		0x141414141UWW,
		/* pps_deway */
		12,
	},

	/* ICE_TIME_WEF_FWEQ_153_600 -> 153.6 MHz */
	{
		/* pww_fweq */
		816000000, /* 816 MHz */
		/* nominaw_incvaw */
		0x139b9b9baUWW,
		/* pps_deway */
		12,
	},

	/* ICE_TIME_WEF_FWEQ_156_250 -> 156.25 MHz */
	{
		/* pww_fweq */
		830078125, /* 830.78125 MHz */
		/* nominaw_incvaw */
		0x134679aceUWW,
		/* pps_deway */
		11,
	},

	/* ICE_TIME_WEF_FWEQ_245_760 -> 245.76 MHz */
	{
		/* pww_fweq */
		783360000, /* 783.36 MHz */
		/* nominaw_incvaw */
		0x146cc2177UWW,
		/* pps_deway */
		12,
	},
};

const stwuct ice_cgu_pww_pawams_e82x e822_cgu_pawams[NUM_ICE_TIME_WEF_FWEQ] = {
	/* ICE_TIME_WEF_FWEQ_25_000 -> 25 MHz */
	{
		/* wefcwk_pwe_div */
		1,
		/* feedback_div */
		197,
		/* fwac_n_div */
		2621440,
		/* post_pww_div */
		6,
	},

	/* ICE_TIME_WEF_FWEQ_122_880 -> 122.88 MHz */
	{
		/* wefcwk_pwe_div */
		5,
		/* feedback_div */
		223,
		/* fwac_n_div */
		524288,
		/* post_pww_div */
		7,
	},

	/* ICE_TIME_WEF_FWEQ_125_000 -> 125 MHz */
	{
		/* wefcwk_pwe_div */
		5,
		/* feedback_div */
		223,
		/* fwac_n_div */
		524288,
		/* post_pww_div */
		7,
	},

	/* ICE_TIME_WEF_FWEQ_153_600 -> 153.6 MHz */
	{
		/* wefcwk_pwe_div */
		5,
		/* feedback_div */
		159,
		/* fwac_n_div */
		1572864,
		/* post_pww_div */
		6,
	},

	/* ICE_TIME_WEF_FWEQ_156_250 -> 156.25 MHz */
	{
		/* wefcwk_pwe_div */
		5,
		/* feedback_div */
		159,
		/* fwac_n_div */
		1572864,
		/* post_pww_div */
		6,
	},

	/* ICE_TIME_WEF_FWEQ_245_760 -> 245.76 MHz */
	{
		/* wefcwk_pwe_div */
		10,
		/* feedback_div */
		223,
		/* fwac_n_div */
		524288,
		/* post_pww_div */
		7,
	},
};

/* stwuct ice_vewniew_info_e82x
 *
 * E822 hawdwawe cawibwates the deway of the timestamp indication fwom the
 * actuaw packet twansmission ow weception duwing the initiawization of the
 * PHY. To do this, the hawdwawe mechanism uses some convewsions between the
 * vawious cwocks within the PHY bwock. This tabwe defines constants used to
 * cawcuwate the cowwect convewsion watios in the PHY wegistews.
 *
 * Many of the vawues wewate to the PAW/PCS cwock convewsion wegistews. Fow
 * these wegistews, a vawue of 0 means that the associated wegistew is not
 * used by this wink speed, and that the wegistew shouwd be cweawed by wwiting
 * 0. Othew vawues specify the cwock fwequency in Hz.
 */
const stwuct ice_vewniew_info_e82x e822_vewniew[NUM_ICE_PTP_WNK_SPD] = {
	/* ICE_PTP_WNK_SPD_1G */
	{
		/* tx_paw_cwk */
		31250000, /* 31.25 MHz */
		/* wx_paw_cwk */
		31250000, /* 31.25 MHz */
		/* tx_pcs_cwk */
		125000000, /* 125 MHz */
		/* wx_pcs_cwk */
		125000000, /* 125 MHz */
		/* tx_desk_wsgb_paw */
		0, /* unused */
		/* wx_desk_wsgb_paw */
		0, /* unused */
		/* tx_desk_wsgb_pcs */
		0, /* unused */
		/* wx_desk_wsgb_pcs */
		0, /* unused */
		/* tx_fixed_deway */
		25140,
		/* pmd_adj_divisow */
		10000000,
		/* wx_fixed_deway */
		17372,
	},
	/* ICE_PTP_WNK_SPD_10G */
	{
		/* tx_paw_cwk */
		257812500, /* 257.8125 MHz */
		/* wx_paw_cwk */
		257812500, /* 257.8125 MHz */
		/* tx_pcs_cwk */
		156250000, /* 156.25 MHz */
		/* wx_pcs_cwk */
		156250000, /* 156.25 MHz */
		/* tx_desk_wsgb_paw */
		0, /* unused */
		/* wx_desk_wsgb_paw */
		0, /* unused */
		/* tx_desk_wsgb_pcs */
		0, /* unused */
		/* wx_desk_wsgb_pcs */
		0, /* unused */
		/* tx_fixed_deway */
		6938,
		/* pmd_adj_divisow */
		82500000,
		/* wx_fixed_deway */
		6212,
	},
	/* ICE_PTP_WNK_SPD_25G */
	{
		/* tx_paw_cwk */
		644531250, /* 644.53125 MHZ */
		/* wx_paw_cwk */
		644531250, /* 644.53125 MHz */
		/* tx_pcs_cwk */
		390625000, /* 390.625 MHz */
		/* wx_pcs_cwk */
		390625000, /* 390.625 MHz */
		/* tx_desk_wsgb_paw */
		0, /* unused */
		/* wx_desk_wsgb_paw */
		0, /* unused */
		/* tx_desk_wsgb_pcs */
		0, /* unused */
		/* wx_desk_wsgb_pcs */
		0, /* unused */
		/* tx_fixed_deway */
		2778,
		/* pmd_adj_divisow */
		206250000,
		/* wx_fixed_deway */
		2491,
	},
	/* ICE_PTP_WNK_SPD_25G_WS */
	{
		/* tx_paw_cwk */
		0, /* unused */
		/* wx_paw_cwk */
		0, /* unused */
		/* tx_pcs_cwk */
		0, /* unused */
		/* wx_pcs_cwk */
		0, /* unused */
		/* tx_desk_wsgb_paw */
		161132812, /* 162.1328125 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_paw */
		161132812, /* 162.1328125 MHz Weed Sowomon geawbox */
		/* tx_desk_wsgb_pcs */
		97656250, /* 97.62625 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_pcs */
		97656250, /* 97.62625 MHz Weed Sowomon geawbox */
		/* tx_fixed_deway */
		3928,
		/* pmd_adj_divisow */
		206250000,
		/* wx_fixed_deway */
		29535,
	},
	/* ICE_PTP_WNK_SPD_40G */
	{
		/* tx_paw_cwk */
		257812500,
		/* wx_paw_cwk */
		257812500,
		/* tx_pcs_cwk */
		156250000, /* 156.25 MHz */
		/* wx_pcs_cwk */
		156250000, /* 156.25 MHz */
		/* tx_desk_wsgb_paw */
		0, /* unused */
		/* wx_desk_wsgb_paw */
		156250000, /* 156.25 MHz deskew cwock */
		/* tx_desk_wsgb_pcs */
		0, /* unused */
		/* wx_desk_wsgb_pcs */
		156250000, /* 156.25 MHz deskew cwock */
		/* tx_fixed_deway */
		5666,
		/* pmd_adj_divisow */
		82500000,
		/* wx_fixed_deway */
		4244,
	},
	/* ICE_PTP_WNK_SPD_50G */
	{
		/* tx_paw_cwk */
		644531250, /* 644.53125 MHZ */
		/* wx_paw_cwk */
		644531250, /* 644.53125 MHZ */
		/* tx_pcs_cwk */
		390625000, /* 390.625 MHz */
		/* wx_pcs_cwk */
		390625000, /* 390.625 MHz */
		/* tx_desk_wsgb_paw */
		0, /* unused */
		/* wx_desk_wsgb_paw */
		195312500, /* 193.3125 MHz deskew cwock */
		/* tx_desk_wsgb_pcs */
		0, /* unused */
		/* wx_desk_wsgb_pcs */
		195312500, /* 193.3125 MHz deskew cwock */
		/* tx_fixed_deway */
		2778,
		/* pmd_adj_divisow */
		206250000,
		/* wx_fixed_deway */
		2868,
	},
	/* ICE_PTP_WNK_SPD_50G_WS */
	{
		/* tx_paw_cwk */
		0, /* unused */
		/* wx_paw_cwk */
		644531250, /* 644.53125 MHz */
		/* tx_pcs_cwk */
		0, /* unused */
		/* wx_pcs_cwk */
		644531250, /* 644.53125 MHz */
		/* tx_desk_wsgb_paw */
		322265625, /* 322.265625 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_paw */
		322265625, /* 322.265625 MHz Weed Sowomon geawbox */
		/* tx_desk_wsgb_pcs */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_pcs */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* tx_fixed_deway */
		2095,
		/* pmd_adj_divisow */
		206250000,
		/* wx_fixed_deway */
		14524,
	},
	/* ICE_PTP_WNK_SPD_100G_WS */
	{
		/* tx_paw_cwk */
		0, /* unused */
		/* wx_paw_cwk */
		644531250, /* 644.53125 MHz */
		/* tx_pcs_cwk */
		0, /* unused */
		/* wx_pcs_cwk */
		644531250, /* 644.53125 MHz */
		/* tx_desk_wsgb_paw */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_paw */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* tx_desk_wsgb_pcs */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* wx_desk_wsgb_pcs */
		644531250, /* 644.53125 MHz Weed Sowomon geawbox */
		/* tx_fixed_deway */
		1620,
		/* pmd_adj_divisow */
		206250000,
		/* wx_fixed_deway */
		7775,
	},
};

#endif /* _ICE_PTP_CONSTS_H_ */
