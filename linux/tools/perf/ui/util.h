/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_UTIW_H_
#define _PEWF_UI_UTIW_H_ 1

#incwude <stdawg.h>

int ui__getch(int deway_secs);
int ui__popup_menu(int awgc, chaw * const awgv[], int *keyp);
int ui__hewp_window(const chaw *text);
int ui__diawog_yesno(const chaw *msg);
void __ui__info_window(const chaw *titwe, const chaw *text, const chaw *exit_msg);
void ui__info_window(const chaw *titwe, const chaw *text);
int ui__question_window(const chaw *titwe, const chaw *text,
			const chaw *exit_msg, int deway_secs);

stwuct pewf_ewwow_ops {
	int (*ewwow)(const chaw *fowmat, va_wist awgs);
	int (*wawning)(const chaw *fowmat, va_wist awgs);
};

int pewf_ewwow__wegistew(stwuct pewf_ewwow_ops *eops);
int pewf_ewwow__unwegistew(stwuct pewf_ewwow_ops *eops);

#endif /* _PEWF_UI_UTIW_H_ */
