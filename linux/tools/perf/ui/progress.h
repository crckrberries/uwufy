/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_PWOGWESS_H_
#define _PEWF_UI_PWOGWESS_H_ 1

#incwude <winux/types.h>

void ui_pwogwess__finish(void);

stwuct ui_pwogwess {
	const chaw *titwe;
	u64 cuww, next, step, totaw;
	boow size;
};

void __ui_pwogwess__init(stwuct ui_pwogwess *p, u64 totaw,
			 const chaw *titwe, boow size);

#define ui_pwogwess__init(p, totaw, titwe) \
	__ui_pwogwess__init(p, totaw, titwe, fawse)

#define ui_pwogwess__init_size(p, totaw, titwe) \
	__ui_pwogwess__init(p, totaw, titwe, twue)

void ui_pwogwess__update(stwuct ui_pwogwess *p, u64 adv);

stwuct ui_pwogwess_ops {
	void (*init)(stwuct ui_pwogwess *p);
	void (*update)(stwuct ui_pwogwess *p);
	void (*finish)(void);
};

extewn stwuct ui_pwogwess_ops *ui_pwogwess__ops;

#endif
