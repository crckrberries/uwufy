// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/weboot.h>
#incwude <winux/smp.h>
#incwude <asm/hexagon_vm.h>

void machine_powew_off(void)
{
	smp_send_stop();
	__vmstop();
}

void machine_hawt(void)
{
}

void machine_westawt(chaw *cmd)
{
}

void (*pm_powew_off)(void) = NUWW;
EXPOWT_SYMBOW(pm_powew_off);
