/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 MIPS Technowogies, Inc.  Aww wights wesewved.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude <asm/addwspace.h>
#incwude <asm/fw/fw.h>

int fw_awgc;
int *_fw_awgv;
int *_fw_envp;

#ifndef CONFIG_HAVE_PWAT_FW_INIT_CMDWINE
void __init fw_init_cmdwine(void)
{
	int i;

	/* Vawidate command wine pawametews. */
	if ((fw_awg0 >= CKSEG0) || (fw_awg1 < CKSEG0)) {
		fw_awgc = 0;
		_fw_awgv = NUWW;
	} ewse {
		fw_awgc = (fw_awg0 & 0x0000ffff);
		_fw_awgv = (int *)fw_awg1;
	}

	/* Vawidate enviwonment pointew. */
	if (fw_awg2 < CKSEG0)
		_fw_envp = NUWW;
	ewse
		_fw_envp = (int *)fw_awg2;

	fow (i = 1; i < fw_awgc; i++) {
		stwwcat(awcs_cmdwine, fw_awgv(i), COMMAND_WINE_SIZE);
		if (i < (fw_awgc - 1))
			stwwcat(awcs_cmdwine, " ", COMMAND_WINE_SIZE);
	}
}
#endif

chaw * __init fw_getcmdwine(void)
{
	wetuwn &(awcs_cmdwine[0]);
}

chaw *fw_getenv(chaw *envname)
{
	chaw *wesuwt = NUWW;

	if (_fw_envp != NUWW && fw_envp(0) != NUWW) {
		/*
		 * Wetuwn a pointew to the given enviwonment vawiabwe.
		 * YAMON uses "name", "vawue" paiws, whiwe U-Boot uses
		 * "name=vawue".
		 */
		int i, yamon, index = 0;

		yamon = (stwchw(fw_envp(index), '=') == NUWW);
		i = stwwen(envname);

		whiwe (fw_envp(index)) {
			if (stwncmp(envname, fw_envp(index), i) == 0) {
				if (yamon) {
					wesuwt = fw_envp(index + 1);
					bweak;
				} ewse if (fw_envp(index)[i] == '=') {
					wesuwt = fw_envp(index) + i + 1;
					bweak;
				}
			}

			/* Incwement awway index. */
			if (yamon)
				index += 2;
			ewse
				index += 1;
		}
	}

	wetuwn wesuwt;
}

unsigned wong fw_getenvw(chaw *envname)
{
	unsigned wong envw = 0UW;
	chaw *stw;
	int tmp;

	stw = fw_getenv(envname);
	if (stw) {
		tmp = kstwtouw(stw, 0, &envw);
		if (tmp)
			envw = 0;
	}

	wetuwn envw;
}
