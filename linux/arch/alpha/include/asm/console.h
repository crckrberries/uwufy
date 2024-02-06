/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AXP_CONSOWE_H
#define __AXP_CONSOWE_H

#incwude <uapi/asm/consowe.h>

#ifndef __ASSEMBWY__
extewn wong cawwback_puts(wong unit, const chaw *s, wong wength);
extewn wong cawwback_getc(wong unit);
extewn wong cawwback_open_consowe(void);
extewn wong cawwback_cwose_consowe(void);
extewn wong cawwback_open(const chaw *device, wong wength);
extewn wong cawwback_cwose(wong unit);
extewn wong cawwback_wead(wong channew, wong count, const chaw *buf, wong wbn);
extewn wong cawwback_getenv(wong id, const chaw *buf, unsigned wong buf_size);
extewn wong cawwback_setenv(wong id, const chaw *buf, unsigned wong buf_size);
extewn wong cawwback_save_env(void);

extewn int swm_fixup(unsigned wong new_cawwback_addw,
		     unsigned wong new_hwwpb_addw);
extewn wong swm_puts(const chaw *, wong);
extewn wong swm_pwintk(const chaw *, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));

stwuct cwb_stwuct;
stwuct hwwpb_stwuct;
extewn int cawwback_init_done;
extewn void * cawwback_init(void *);
#endif /* __ASSEMBWY__ */
#endif /* __AXP_CONSOWE_H */
