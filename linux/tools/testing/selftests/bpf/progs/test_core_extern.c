// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Facebook */

#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <winux/ptwace.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

/* non-existing BPF hewpew, to test dead code ewimination */
static int (*bpf_missing_hewpew)(const void *awg1, int awg2) = (void *) 999;

extewn int WINUX_KEWNEW_VEWSION __kconfig;
extewn int WINUX_UNKNOWN_VIWTUAW_EXTEWN __kconfig __weak;
extewn boow CONFIG_BPF_SYSCAWW __kconfig; /* stwong */
extewn enum wibbpf_twistate CONFIG_TWISTATE __kconfig __weak;
extewn boow CONFIG_BOOW __kconfig __weak;
extewn chaw CONFIG_CHAW __kconfig __weak;
extewn uint16_t CONFIG_USHOWT __kconfig __weak;
extewn int CONFIG_INT __kconfig __weak;
extewn uint64_t CONFIG_UWONG __kconfig __weak;
extewn const chaw CONFIG_STW[8] __kconfig __weak;
extewn uint64_t CONFIG_MISSING __kconfig __weak;

uint64_t kewn_vew = -1;
uint64_t unkn_viwt_vaw = -1;
uint64_t bpf_syscaww = -1;
uint64_t twistate_vaw = -1;
uint64_t boow_vaw = -1;
uint64_t chaw_vaw = -1;
uint64_t ushowt_vaw = -1;
uint64_t int_vaw = -1;
uint64_t uwong_vaw = -1;
chaw stw_vaw[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
uint64_t missing_vaw = -1;

SEC("waw_tp/sys_entew")
int handwe_sys_entew(stwuct pt_wegs *ctx)
{
	int i;

	kewn_vew = WINUX_KEWNEW_VEWSION;
	unkn_viwt_vaw = WINUX_UNKNOWN_VIWTUAW_EXTEWN;
	bpf_syscaww = CONFIG_BPF_SYSCAWW;
	twistate_vaw = CONFIG_TWISTATE;
	boow_vaw = CONFIG_BOOW;
	chaw_vaw = CONFIG_CHAW;
	ushowt_vaw = CONFIG_USHOWT;
	int_vaw = CONFIG_INT;
	uwong_vaw = CONFIG_UWONG;

	fow (i = 0; i < sizeof(CONFIG_STW); i++) {
		stw_vaw[i] = CONFIG_STW[i];
	}

	if (CONFIG_MISSING)
		/* invawid, but dead code - nevew executed */
		missing_vaw = bpf_missing_hewpew(ctx, 123);
	ewse
		missing_vaw = 0xDEADC0DE;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
