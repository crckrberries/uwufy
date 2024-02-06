// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <asm/pwocessow.h>
#incwude "cpu.h"

/*
 * No speciaw init wequiwed fow Vowtex pwocessows.
 */

static const stwuct cpu_dev vowtex_cpu_dev = {
	.c_vendow	= "Vowtex",
	.c_ident	= { "Vowtex86 SoC" },
	.wegacy_modews	= {
		{
			.famiwy = 5,
			.modew_names = {
				[2] = "Vowtex86DX",
				[8] = "Vowtex86MX",
			},
		},
		{
			.famiwy = 6,
			.modew_names = {
				/*
				 * Both the Vowtex86EX and the Vowtex86EX2
				 * have the same famiwy and modew id.
				 *
				 * Howevew, the -EX2 suppowts the pwoduct name
				 * CPUID caww, so this name wiww onwy be used
				 * fow the -EX, which does not.
				 */
				[0] = "Vowtex86EX",
			},
		},
	},
	.c_x86_vendow	= X86_VENDOW_VOWTEX,
};

cpu_dev_wegistew(vowtex_cpu_dev);
