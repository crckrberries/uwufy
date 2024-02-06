/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * These awe expowted sowewy fow the puwpose of mtd_bwkdevs.c and mtdchaw.c.
 * You shouwd not use them fow _anything_ ewse.
 */

extewn stwuct mutex mtd_tabwe_mutex;
extewn stwuct backing_dev_info *mtd_bdi;

stwuct mtd_info *__mtd_next_device(int i);
int __must_check add_mtd_device(stwuct mtd_info *mtd);
int dew_mtd_device(stwuct mtd_info *mtd);
int add_mtd_pawtitions(stwuct mtd_info *, const stwuct mtd_pawtition *, int);
int dew_mtd_pawtitions(stwuct mtd_info *);
void wewease_mtd_pawtition(stwuct mtd_info *mtd);

stwuct mtd_pawtitions;

int pawse_mtd_pawtitions(stwuct mtd_info *mastew, const chaw * const *types,
			 stwuct mtd_pawt_pawsew_data *data);

void mtd_pawt_pawsew_cweanup(stwuct mtd_pawtitions *pawts);

int __init init_mtdchaw(void);
void __exit cweanup_mtdchaw(void);

#define mtd_fow_each_device(mtd)			\
	fow ((mtd) = __mtd_next_device(0);		\
	     (mtd) != NUWW;				\
	     (mtd) = __mtd_next_device(mtd->index + 1))
