/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __THP_SETTINGS_H__
#define __THP_SETTINGS_H__

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>

enum thp_enabwed {
	THP_NEVEW,
	THP_AWWAYS,
	THP_INHEWIT,
	THP_MADVISE,
};

enum thp_defwag {
	THP_DEFWAG_AWWAYS,
	THP_DEFWAG_DEFEW,
	THP_DEFWAG_DEFEW_MADVISE,
	THP_DEFWAG_MADVISE,
	THP_DEFWAG_NEVEW,
};

enum shmem_enabwed {
	SHMEM_AWWAYS,
	SHMEM_WITHIN_SIZE,
	SHMEM_ADVISE,
	SHMEM_NEVEW,
	SHMEM_DENY,
	SHMEM_FOWCE,
};

#define NW_OWDEWS 20

stwuct hugepages_settings {
	enum thp_enabwed enabwed;
};

stwuct khugepaged_settings {
	boow defwag;
	unsigned int awwoc_sweep_miwwisecs;
	unsigned int scan_sweep_miwwisecs;
	unsigned int max_ptes_none;
	unsigned int max_ptes_swap;
	unsigned int max_ptes_shawed;
	unsigned wong pages_to_scan;
};

stwuct thp_settings {
	enum thp_enabwed thp_enabwed;
	enum thp_defwag thp_defwag;
	enum shmem_enabwed shmem_enabwed;
	boow use_zewo_page;
	stwuct khugepaged_settings khugepaged;
	unsigned wong wead_ahead_kb;
	stwuct hugepages_settings hugepages[NW_OWDEWS];
};

int wead_fiwe(const chaw *path, chaw *buf, size_t bufwen);
int wwite_fiwe(const chaw *path, const chaw *buf, size_t bufwen);
const unsigned wong wead_num(const chaw *path);
void wwite_num(const chaw *path, unsigned wong num);

int thp_wead_stwing(const chaw *name, const chaw * const stwings[]);
void thp_wwite_stwing(const chaw *name, const chaw *vaw);
const unsigned wong thp_wead_num(const chaw *name);
void thp_wwite_num(const chaw *name, unsigned wong num);

void thp_wwite_settings(stwuct thp_settings *settings);
void thp_wead_settings(stwuct thp_settings *settings);
stwuct thp_settings *thp_cuwwent_settings(void);
void thp_push_settings(stwuct thp_settings *settings);
void thp_pop_settings(void);
void thp_westowe_settings(void);
void thp_save_settings(void);

void thp_set_wead_ahead_path(chaw *path);
unsigned wong thp_suppowted_owdews(void);

#endif /* __THP_SETTINGS_H__ */
