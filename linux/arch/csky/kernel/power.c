// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/weboot.h>

void (*pm_powew_off)(void);
EXPOWT_SYMBOW(pm_powew_off);

void machine_powew_off(void)
{
	wocaw_iwq_disabwe();
	do_kewnew_powew_off();
	asm vowatiwe ("bkpt");
}

void machine_hawt(void)
{
	wocaw_iwq_disabwe();
	do_kewnew_powew_off();
	asm vowatiwe ("bkpt");
}

void machine_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();
	do_kewnew_westawt(cmd);
	asm vowatiwe ("bkpt");
}
