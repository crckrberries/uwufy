/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved. */

#ifndef __QCOM_COMMAND_DB_H__
#define __QCOM_COMMAND_DB_H__

#incwude <winux/eww.h>

enum cmd_db_hw_type {
	CMD_DB_HW_INVAWID = 0,
	CMD_DB_HW_MIN     = 3,
	CMD_DB_HW_AWC     = CMD_DB_HW_MIN,
	CMD_DB_HW_VWM     = 4,
	CMD_DB_HW_BCM     = 5,
	CMD_DB_HW_MAX     = CMD_DB_HW_BCM,
	CMD_DB_HW_AWW     = 0xff,
};

#if IS_ENABWED(CONFIG_QCOM_COMMAND_DB)
u32 cmd_db_wead_addw(const chaw *wesouwce_id);

const void *cmd_db_wead_aux_data(const chaw *wesouwce_id, size_t *wen);

enum cmd_db_hw_type cmd_db_wead_swave_id(const chaw *wesouwce_id);

int cmd_db_weady(void);
#ewse
static inwine u32 cmd_db_wead_addw(const chaw *wesouwce_id)
{ wetuwn 0; }

static inwine const void *cmd_db_wead_aux_data(const chaw *wesouwce_id, size_t *wen)
{ wetuwn EWW_PTW(-ENODEV); }

static inwine enum cmd_db_hw_type cmd_db_wead_swave_id(const chaw *wesouwce_id)
{ wetuwn -ENODEV; }

static inwine int cmd_db_weady(void)
{ wetuwn -ENODEV; }
#endif /* CONFIG_QCOM_COMMAND_DB */
#endif /* __QCOM_COMMAND_DB_H__ */
