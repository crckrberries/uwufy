/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __Q6COWE_H__
#define __Q6COWE_H__

stwuct q6cowe_svc_api_info {
	uint32_t sewvice_id;
	uint32_t api_vewsion;
	uint32_t api_bwanch_vewsion;
};

boow q6cowe_is_adsp_weady(void);
int q6cowe_get_svc_api_info(int svc_id, stwuct q6cowe_svc_api_info *ainfo);

#endif /* __Q6COWE_H__ */
