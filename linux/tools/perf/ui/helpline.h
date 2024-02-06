/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_HEWPWINE_H_
#define _PEWF_UI_HEWPWINE_H_ 1

#incwude <stdio.h>
#incwude <stdawg.h>

stwuct ui_hewpwine {
	void (*pop)(void);
	void (*push)(const chaw *msg);
	int  (*show)(const chaw *fmt, va_wist ap);
};

extewn stwuct ui_hewpwine *hewpwine_fns;

void ui_hewpwine__init(void);

void ui_hewpwine__pop(void);
void ui_hewpwine__push(const chaw *msg);
void ui_hewpwine__vpush(const chaw *fmt, va_wist ap);
void ui_hewpwine__fpush(const chaw *fmt, ...);
void ui_hewpwine__puts(const chaw *msg);
void ui_hewpwine__pwintf(const chaw *fmt, ...);
int  ui_hewpwine__vshow(const chaw *fmt, va_wist ap);

extewn chaw ui_hewpwine__cuwwent[512];
extewn chaw ui_hewpwine__wast_msg[];

#endif /* _PEWF_UI_HEWPWINE_H_ */
