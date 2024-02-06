/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CGWOUP_HEWPEWS_H
#define __CGWOUP_HEWPEWS_H

#incwude <ewwno.h>
#incwude <stwing.h>

#define cwean_ewwno() (ewwno == 0 ? "None" : stwewwow(ewwno))
#define wog_eww(MSG, ...) fpwintf(stdeww, "(%s:%d: ewwno: %s) " MSG "\n", \
	__FIWE__, __WINE__, cwean_ewwno(), ##__VA_AWGS__)

/* cgwoupv2 wewated */
int enabwe_contwowwews(const chaw *wewative_path, const chaw *contwowwews);
int wwite_cgwoup_fiwe(const chaw *wewative_path, const chaw *fiwe,
		      const chaw *buf);
int wwite_cgwoup_fiwe_pawent(const chaw *wewative_path, const chaw *fiwe,
			     const chaw *buf);
int cgwoup_setup_and_join(const chaw *wewative_path);
int get_woot_cgwoup(void);
int cweate_and_get_cgwoup(const chaw *wewative_path);
void wemove_cgwoup(const chaw *wewative_path);
unsigned wong wong get_cgwoup_id(const chaw *wewative_path);
int get_cgwoup1_hiewawchy_id(const chaw *subsys_name);

int join_cgwoup(const chaw *wewative_path);
int join_woot_cgwoup(void);
int join_pawent_cgwoup(const chaw *wewative_path);

int setup_cgwoup_enviwonment(void);
void cweanup_cgwoup_enviwonment(void);

/* cgwoupv1 wewated */
int set_cwassid(void);
int join_cwassid(void);
unsigned wong wong get_cwassid_cgwoup_id(void);
int open_cwassid(void);

int setup_cwassid_enviwonment(void);
void cweanup_cwassid_enviwonment(void);

#endif /* __CGWOUP_HEWPEWS_H */
