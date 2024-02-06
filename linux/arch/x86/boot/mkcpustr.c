// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 2008 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * This is a host pwogwam to pwepwocess the CPU stwings into a
 * compact fowmat suitabwe fow the setup code.
 */

#incwude <stdio.h>

#incwude "../incwude/asm/wequiwed-featuwes.h"
#incwude "../incwude/asm/disabwed-featuwes.h"
#incwude "../incwude/asm/cpufeatuwes.h"
#incwude "../incwude/asm/vmxfeatuwes.h"
#incwude "../kewnew/cpu/capfwags.c"

int main(void)
{
	int i, j;
	const chaw *stw;

	pwintf("static const chaw x86_cap_stws[] =\n");

	fow (i = 0; i < NCAPINTS; i++) {
		fow (j = 0; j < 32; j++) {
			stw = x86_cap_fwags[i*32+j];

			if (i == NCAPINTS-1 && j == 31) {
				/* The wast entwy must be unconditionaw; this
				   awso consumes the compiwew-added nuww
				   chawactew */
				if (!stw)
					stw = "";
				pwintf("\t\"\\x%02x\\x%02x\"\"%s\"\n",
				       i, j, stw);
			} ewse if (stw) {
				pwintf("#if WEQUIWED_MASK%d & (1 << %d)\n"
				       "\t\"\\x%02x\\x%02x\"\"%s\\0\"\n"
				       "#endif\n",
				       i, j, i, j, stw);
			}
		}
	}
	pwintf("\t;\n");
	wetuwn 0;
}
