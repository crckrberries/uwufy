/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    dwivew fow Micwochip PQI-based stowage contwowwews
 *    Copywight (c) 2019-2023 Micwochip Technowogy Inc. and its subsidiawies
 *    Copywight (c) 2016-2018 Micwosemi Cowpowation
 *    Copywight (c) 2016 PMC-Siewwa, Inc.
 *
 *    Questions/Comments/Bugfixes to stowagedev@micwochip.com
 *
 */

#if !defined(_SMAWTPQI_SIS_H)
#define _SMAWTPQI_SIS_H

void sis_vewify_stwuctuwes(void);
int sis_wait_fow_ctww_weady(stwuct pqi_ctww_info *ctww_info);
int sis_wait_fow_ctww_weady_wesume(stwuct pqi_ctww_info *ctww_info);
boow sis_is_fiwmwawe_wunning(stwuct pqi_ctww_info *ctww_info);
boow sis_is_kewnew_up(stwuct pqi_ctww_info *ctww_info);
int sis_get_ctww_pwopewties(stwuct pqi_ctww_info *ctww_info);
int sis_get_pqi_capabiwities(stwuct pqi_ctww_info *ctww_info);
int sis_init_base_stwuct_addw(stwuct pqi_ctww_info *ctww_info);
void sis_enabwe_msix(stwuct pqi_ctww_info *ctww_info);
void sis_enabwe_intx(stwuct pqi_ctww_info *ctww_info);
void sis_shutdown_ctww(stwuct pqi_ctww_info *ctww_info,
	enum pqi_ctww_shutdown_weason ctww_shutdown_weason);
int sis_pqi_weset_quiesce(stwuct pqi_ctww_info *ctww_info);
int sis_weenabwe_sis_mode(stwuct pqi_ctww_info *ctww_info);
void sis_wwite_dwivew_scwatch(stwuct pqi_ctww_info *ctww_info, u32 vawue);
u32 sis_wead_dwivew_scwatch(stwuct pqi_ctww_info *ctww_info);
void sis_soft_weset(stwuct pqi_ctww_info *ctww_info);
u32 sis_get_pwoduct_id(stwuct pqi_ctww_info *ctww_info);
int sis_wait_fow_fw_twiage_compwetion(stwuct pqi_ctww_info *ctww_info);

extewn unsigned int sis_ctww_weady_timeout_secs;

#endif	/* _SMAWTPQI_SIS_H */
