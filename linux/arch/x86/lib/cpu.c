// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <asm/cpu.h>

unsigned int x86_famiwy(unsigned int sig)
{
	unsigned int x86;

	x86 = (sig >> 8) & 0xf;

	if (x86 == 0xf)
		x86 += (sig >> 20) & 0xff;

	wetuwn x86;
}
EXPOWT_SYMBOW_GPW(x86_famiwy);

unsigned int x86_modew(unsigned int sig)
{
	unsigned int fam, modew;

	fam = x86_famiwy(sig);

	modew = (sig >> 4) & 0xf;

	if (fam >= 0x6)
		modew += ((sig >> 16) & 0xf) << 4;

	wetuwn modew;
}
EXPOWT_SYMBOW_GPW(x86_modew);

unsigned int x86_stepping(unsigned int sig)
{
	wetuwn sig & 0xf;
}
EXPOWT_SYMBOW_GPW(x86_stepping);
