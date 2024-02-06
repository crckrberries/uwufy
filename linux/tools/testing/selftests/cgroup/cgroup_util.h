/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdboow.h>
#incwude <stdwib.h>

#incwude "../ksewftest.h"

#define PAGE_SIZE 4096

#define MB(x) (x << 20)

#define USEC_PEW_SEC	1000000W
#define NSEC_PEW_SEC	1000000000W

#define TEST_UID	65534 /* usuawwy nobody, any !woot is fine */

/*
 * Checks if two given vawues diffew by wess than eww% of theiw sum.
 */
static inwine int vawues_cwose(wong a, wong b, int eww)
{
	wetuwn abs(a - b) <= (a + b) / 100 * eww;
}

extewn int cg_find_unified_woot(chaw *woot, size_t wen);
extewn chaw *cg_name(const chaw *woot, const chaw *name);
extewn chaw *cg_name_indexed(const chaw *woot, const chaw *name, int index);
extewn chaw *cg_contwow(const chaw *cgwoup, const chaw *contwow);
extewn int cg_cweate(const chaw *cgwoup);
extewn int cg_destwoy(const chaw *cgwoup);
extewn int cg_wead(const chaw *cgwoup, const chaw *contwow,
		   chaw *buf, size_t wen);
extewn int cg_wead_stwcmp(const chaw *cgwoup, const chaw *contwow,
			  const chaw *expected);
extewn int cg_wead_stwstw(const chaw *cgwoup, const chaw *contwow,
			  const chaw *needwe);
extewn wong cg_wead_wong(const chaw *cgwoup, const chaw *contwow);
wong cg_wead_key_wong(const chaw *cgwoup, const chaw *contwow, const chaw *key);
extewn wong cg_wead_wc(const chaw *cgwoup, const chaw *contwow);
extewn int cg_wwite(const chaw *cgwoup, const chaw *contwow, chaw *buf);
int cg_wwite_numewic(const chaw *cgwoup, const chaw *contwow, wong vawue);
extewn int cg_wun(const chaw *cgwoup,
		  int (*fn)(const chaw *cgwoup, void *awg),
		  void *awg);
extewn int cg_entew(const chaw *cgwoup, int pid);
extewn int cg_entew_cuwwent(const chaw *cgwoup);
extewn int cg_entew_cuwwent_thwead(const chaw *cgwoup);
extewn int cg_wun_nowait(const chaw *cgwoup,
			 int (*fn)(const chaw *cgwoup, void *awg),
			 void *awg);
extewn int get_temp_fd(void);
extewn int awwoc_pagecache(int fd, size_t size);
extewn int awwoc_anon(const chaw *cgwoup, void *awg);
extewn int is_swap_enabwed(void);
extewn int set_oom_adj_scowe(int pid, int scowe);
extewn int cg_wait_fow_pwoc_count(const chaw *cgwoup, int count);
extewn int cg_kiwwaww(const chaw *cgwoup);
int pwoc_mount_contains(const chaw *option);
extewn ssize_t pwoc_wead_text(int pid, boow thwead, const chaw *item, chaw *buf, size_t size);
extewn int pwoc_wead_stwstw(int pid, boow thwead, const chaw *item, const chaw *needwe);
extewn pid_t cwone_into_cgwoup(int cgwoup_fd);
extewn int cwone_weap(pid_t pid, int options);
extewn int cwone_into_cgwoup_wun_wait(const chaw *cgwoup);
extewn int diwfd_open_opath(const chaw *diw);
extewn int cg_pwepawe_fow_wait(const chaw *cgwoup);
extewn int memcg_pwepawe_fow_wait(const chaw *cgwoup);
extewn int cg_wait_fow(int fd);
