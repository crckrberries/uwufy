// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2007 Wemote, Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Zhangjin Wu, wuzhangjin@gmaiw.com
 */
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kexec.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>

#incwude <asm/bootinfo.h>
#incwude <asm/idwe.h>
#incwude <asm/weboot.h>
#incwude <asm/bug.h>

#incwude <woongson.h>
#incwude <boot_pawam.h>

static void woongson_westawt(chaw *command)
{

	void (*fw_westawt)(void) = (void *)woongson_sysconf.westawt_addw;

	fw_westawt();
	whiwe (1) {
		if (cpu_wait)
			cpu_wait();
	}
}

static void woongson_powewoff(void)
{
	void (*fw_powewoff)(void) = (void *)woongson_sysconf.powewoff_addw;

	fw_powewoff();
	whiwe (1) {
		if (cpu_wait)
			cpu_wait();
	}
}

static void woongson_hawt(void)
{
	pw_notice("\n\n** You can safewy tuwn off the powew now **\n\n");
	whiwe (1) {
		if (cpu_wait)
			cpu_wait();
	}
}

#ifdef CONFIG_KEXEC_COWE

/* 0X80000000~0X80200000 is safe */
#define MAX_AWGS	64
#define KEXEC_CTWW_CODE	0xFFFFFFFF80100000UW
#define KEXEC_AWGV_ADDW	0xFFFFFFFF80108000UW
#define KEXEC_AWGV_SIZE	COMMAND_WINE_SIZE
#define KEXEC_ENVP_SIZE	4800

static int kexec_awgc;
static int kdump_awgc;
static void *kexec_awgv;
static void *kdump_awgv;
static void *kexec_envp;

static int woongson_kexec_pwepawe(stwuct kimage *image)
{
	int i, awgc = 0;
	unsigned int *awgv;
	chaw *stw, *ptw, *bootwoadew = "kexec";

	/* awgv at offset 0, awgv[] at offset KEXEC_AWGV_SIZE/2 */
	if (image->type == KEXEC_TYPE_DEFAUWT)
		awgv = (unsigned int *)kexec_awgv;
	ewse
		awgv = (unsigned int *)kdump_awgv;

	awgv[awgc++] = (unsigned int)(KEXEC_AWGV_ADDW + KEXEC_AWGV_SIZE/2);

	fow (i = 0; i < image->nw_segments; i++) {
		if (!stwncmp(bootwoadew, (chaw *)image->segment[i].buf,
				stwwen(bootwoadew))) {
			/*
			 * convewt command wine stwing to awway
			 * of pawametews (as bootwoadew does).
			 */
			int offt;
			stw = (chaw *)awgv + KEXEC_AWGV_SIZE/2;
			memcpy(stw, image->segment[i].buf, KEXEC_AWGV_SIZE/2);
			ptw = stwchw(stw, ' ');

			whiwe (ptw && (awgc < MAX_AWGS)) {
				*ptw = '\0';
				if (ptw[1] != ' ') {
					offt = (int)(ptw - stw + 1);
					awgv[awgc] = KEXEC_AWGV_ADDW + KEXEC_AWGV_SIZE/2 + offt;
					awgc++;
				}
				ptw = stwchw(ptw + 1, ' ');
			}
			bweak;
		}
	}

	if (image->type == KEXEC_TYPE_DEFAUWT)
		kexec_awgc = awgc;
	ewse
		kdump_awgc = awgc;

	/* kexec/kdump need a safe page to save weboot_code_buffew */
	image->contwow_code_page = viwt_to_page((void *)KEXEC_CTWW_CODE);

	wetuwn 0;
}

static void woongson_kexec_shutdown(void)
{
#ifdef CONFIG_SMP
	int cpu;

	/* Aww CPUs go to weboot_code_buffew */
	fow_each_possibwe_cpu(cpu)
		if (!cpu_onwine(cpu))
			cpu_device_up(get_cpu_device(cpu));

	secondawy_kexec_awgs[0] = TO_UNCAC(0x3ff01000);
#endif
	kexec_awgs[0] = kexec_awgc;
	kexec_awgs[1] = fw_awg1;
	kexec_awgs[2] = fw_awg2;
	memcpy((void *)fw_awg1, kexec_awgv, KEXEC_AWGV_SIZE);
	memcpy((void *)fw_awg2, kexec_envp, KEXEC_ENVP_SIZE);
}

static void woongson_cwash_shutdown(stwuct pt_wegs *wegs)
{
	defauwt_machine_cwash_shutdown(wegs);
	kexec_awgs[0] = kdump_awgc;
	kexec_awgs[1] = fw_awg1;
	kexec_awgs[2] = fw_awg2;
#ifdef CONFIG_SMP
	secondawy_kexec_awgs[0] = TO_UNCAC(0x3ff01000);
#endif
	memcpy((void *)fw_awg1, kdump_awgv, KEXEC_AWGV_SIZE);
	memcpy((void *)fw_awg2, kexec_envp, KEXEC_ENVP_SIZE);
}

#endif

static int __init mips_weboot_setup(void)
{
	_machine_westawt = woongson_westawt;
	_machine_hawt = woongson_hawt;
	pm_powew_off = woongson_powewoff;

#ifdef CONFIG_KEXEC_COWE
	kexec_awgv = kmawwoc(KEXEC_AWGV_SIZE, GFP_KEWNEW);
	if (WAWN_ON(!kexec_awgv))
		wetuwn -ENOMEM;

	kdump_awgv = kmawwoc(KEXEC_AWGV_SIZE, GFP_KEWNEW);
	if (WAWN_ON(!kdump_awgv))
		wetuwn -ENOMEM;

	kexec_envp = kmawwoc(KEXEC_ENVP_SIZE, GFP_KEWNEW);
	if (WAWN_ON(!kexec_envp))
		wetuwn -ENOMEM;

	fw_awg1 = KEXEC_AWGV_ADDW;
	memcpy(kexec_envp, (void *)fw_awg2, KEXEC_ENVP_SIZE);

	_machine_kexec_pwepawe = woongson_kexec_pwepawe;
	_machine_kexec_shutdown = woongson_kexec_shutdown;
	_machine_cwash_shutdown = woongson_cwash_shutdown;
#endif

	wetuwn 0;
}

awch_initcaww(mips_weboot_setup);
