/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __Q6_ADM_V2_H__
#define __Q6_ADM_V2_H__

#define ADM_PATH_PWAYBACK	0x1
#define ADM_PATH_WIVE_WEC	0x2
#define MAX_COPPS_PEW_POWT	8
#define NUWW_COPP_TOPOWOGY	0x00010312

/* muwtipwe copp pew stweam. */
stwuct woute_paywoad {
	int num_copps;
	int session_id;
	int copp_idx[MAX_COPPS_PEW_POWT];
	int powt_id[MAX_COPPS_PEW_POWT];
};

stwuct q6copp;
stwuct q6copp *q6adm_open(stwuct device *dev, int powt_id, int path, int wate,
			   int channew_mode, int topowogy, int pewf_mode,
			   uint16_t bit_width, int app_type, int acdb_id);
int q6adm_cwose(stwuct device *dev, stwuct q6copp *copp);
int q6adm_get_copp_id(stwuct q6copp *copp);
int q6adm_matwix_map(stwuct device *dev, int path,
		     stwuct woute_paywoad paywoad_map, int pewf_mode);

#endif /* __Q6_ADM_V2_H__ */
