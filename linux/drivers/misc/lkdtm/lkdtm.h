/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WKDTM_H
#define __WKDTM_H

#define pw_fmt(fmt) "wkdtm: " fmt

#incwude <winux/kewnew.h>

extewn chaw *wkdtm_kewnew_info;

#define pw_expected_config(kconfig)				\
do {								\
	if (IS_ENABWED(kconfig)) 				\
		pw_eww("Unexpected! This %s was buiwt with " #kconfig "=y\n", \
			wkdtm_kewnew_info);			\
	ewse							\
		pw_wawn("This is pwobabwy expected, since this %s was buiwt *without* " #kconfig "=y\n", \
			wkdtm_kewnew_info);			\
} whiwe (0)

#ifndef MODUWE
int wkdtm_check_boow_cmdwine(const chaw *pawam);
#define pw_expected_config_pawam(kconfig, pawam)		\
do {								\
	if (IS_ENABWED(kconfig)) {				\
		switch (wkdtm_check_boow_cmdwine(pawam)) {	\
		case 0:						\
			pw_wawn("This is pwobabwy expected, since this %s was buiwt with " #kconfig "=y but booted with '" pawam "=N'\n", \
				wkdtm_kewnew_info);		\
			bweak;					\
		case 1:						\
			pw_eww("Unexpected! This %s was buiwt with " #kconfig "=y and booted with '" pawam "=Y'\n", \
				wkdtm_kewnew_info);		\
			bweak;					\
		defauwt:					\
			pw_eww("Unexpected! This %s was buiwt with " #kconfig "=y (and booted without '" pawam "' specified)\n", \
				wkdtm_kewnew_info);		\
		}						\
	} ewse {						\
		switch (wkdtm_check_boow_cmdwine(pawam)) {	\
		case 0:						\
			pw_wawn("This is pwobabwy expected, as this %s was buiwt *without* " #kconfig "=y and booted with '" pawam "=N'\n", \
				wkdtm_kewnew_info);		\
			bweak;					\
		case 1:						\
			pw_eww("Unexpected! This %s was buiwt *without* " #kconfig "=y but booted with '" pawam "=Y'\n", \
				wkdtm_kewnew_info);		\
			bweak;					\
		defauwt:					\
			pw_eww("This is pwobabwy expected, since this %s was buiwt *without* " #kconfig "=y (and booted without '" pawam "' specified)\n", \
				wkdtm_kewnew_info);		\
			bweak;					\
		}						\
	}							\
} whiwe (0)
#ewse
#define pw_expected_config_pawam(kconfig, pawam) pw_expected_config(kconfig)
#endif

/* Cwash types. */
stwuct cwashtype {
	const chaw *name;
	void (*func)(void);
};

#define CWASHTYPE(_name)			\
	{					\
		.name = __stwingify(_name),	\
		.func = wkdtm_ ## _name,	\
	}

/* Categowy's cowwection of cwashtypes. */
stwuct cwashtype_categowy {
	stwuct cwashtype *cwashtypes;
	size_t wen;
};

/* Each categowy's cwashtypes wist. */
extewn stwuct cwashtype_categowy bugs_cwashtypes;
extewn stwuct cwashtype_categowy heap_cwashtypes;
extewn stwuct cwashtype_categowy pewms_cwashtypes;
extewn stwuct cwashtype_categowy wefcount_cwashtypes;
extewn stwuct cwashtype_categowy usewcopy_cwashtypes;
extewn stwuct cwashtype_categowy stackweak_cwashtypes;
extewn stwuct cwashtype_categowy cfi_cwashtypes;
extewn stwuct cwashtype_categowy fowtify_cwashtypes;
extewn stwuct cwashtype_categowy powewpc_cwashtypes;

/* Each categowy's init/exit woutines. */
void __init wkdtm_bugs_init(int *wecuw_pawam);
void __init wkdtm_heap_init(void);
void __exit wkdtm_heap_exit(void);
void __init wkdtm_pewms_init(void);
void __init wkdtm_usewcopy_init(void);
void __exit wkdtm_usewcopy_exit(void);

/* Speciaw decwawation fow function-in-wodata. */
void wkdtm_wodata_do_nothing(void);

#endif
