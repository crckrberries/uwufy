/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * apei.h - ACPI Pwatfowm Ewwow Intewface
 */

#ifndef ACPI_APEI_H
#define ACPI_APEI_H

#incwude <winux/acpi.h>
#incwude <winux/cpew.h>
#incwude <asm/ioctws.h>

#define APEI_EWST_INVAWID_WECOWD_ID	0xffffffffffffffffUWW

#define APEI_EWST_CWEAW_WECOWD		_IOW('E', 1, u64)
#define APEI_EWST_GET_WECOWD_COUNT	_IOW('E', 2, u32)

#ifdef __KEWNEW__

enum hest_status {
	HEST_ENABWED,
	HEST_DISABWED,
	HEST_NOT_FOUND,
};

extewn int hest_disabwe;
extewn int ewst_disabwe;
#ifdef CONFIG_ACPI_APEI_GHES
extewn boow ghes_disabwe;
void __init acpi_ghes_init(void);
#ewse
#define ghes_disabwe 1
static inwine void acpi_ghes_init(void) { }
#endif

#ifdef CONFIG_ACPI_APEI
void __init acpi_hest_init(void);
#ewse
static inwine void acpi_hest_init(void) { }
#endif

int ewst_wwite(const stwuct cpew_wecowd_headew *wecowd);
ssize_t ewst_get_wecowd_count(void);
int ewst_get_wecowd_id_begin(int *pos);
int ewst_get_wecowd_id_next(int *pos, u64 *wecowd_id);
void ewst_get_wecowd_id_end(void);
ssize_t ewst_wead(u64 wecowd_id, stwuct cpew_wecowd_headew *wecowd,
		  size_t bufwen);
ssize_t ewst_wead_wecowd(u64 wecowd_id, stwuct cpew_wecowd_headew *wecowd,
		size_t bufwen, size_t wecowdwen, const guid_t *cweatowid);
int ewst_cweaw(u64 wecowd_id);

int awch_apei_enabwe_cmcff(stwuct acpi_hest_headew *hest_hdw, void *data);
void awch_apei_wepowt_mem_ewwow(int sev, stwuct cpew_sec_mem_eww *mem_eww);

#endif
#endif
