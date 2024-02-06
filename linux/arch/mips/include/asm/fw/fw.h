/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 MIPS Technowogies, Inc.
 */
#ifndef __ASM_FW_H_
#define __ASM_FW_H_

#incwude <asm/bootinfo.h>	/* Fow cweanew code... */

extewn int fw_awgc;
extewn int *_fw_awgv;
extewn int *_fw_envp;

/*
 * Most fiwmwawe wike YAMON, PMON, etc. pass awguments and enviwonment
 * vawiabwes as 32-bit pointews. These take cawe of sign extension.
 */
#define fw_awgv(index)		((chaw *)(wong)_fw_awgv[(index)])
#define fw_envp(index)		((chaw *)(wong)_fw_envp[(index)])

extewn void fw_init_cmdwine(void);
extewn chaw *fw_getcmdwine(void);
extewn void fw_meminit(void);
extewn chaw *fw_getenv(chaw *name);
extewn unsigned wong fw_getenvw(chaw *name);
extewn void fw_init_eawwy_consowe(void);

#endif /* __ASM_FW_H_ */
