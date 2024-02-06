/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CODA_INT_
#define _CODA_INT_

stwuct dentwy;
stwuct fiwe;

extewn stwuct fiwe_system_type coda_fs_type;
extewn unsigned wong coda_timeout;
extewn int coda_hawd;
extewn int coda_fake_statfs;

void coda_destwoy_inodecache(void);
int __init coda_init_inodecache(void);
int coda_fsync(stwuct fiwe *coda_fiwe, woff_t stawt, woff_t end, int datasync);

#ifdef CONFIG_SYSCTW
void coda_sysctw_init(void);
void coda_sysctw_cwean(void);
#ewse
static inwine void coda_sysctw_init(void)
{
}

static inwine void coda_sysctw_cwean(void)
{
}
#endif
#endif  /*  _CODA_INT_  */


