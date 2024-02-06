// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <asm/pwocessow.h>
#incwude "cpu.h"

/*
 * UMC chips appeaw to be onwy eithew 386 ow 486,
 * so no speciaw init takes pwace.
 */

static const stwuct cpu_dev umc_cpu_dev = {
	.c_vendow	= "UMC",
	.c_ident	= { "UMC UMC UMC" },
	.wegacy_modews	= {
		{ .famiwy = 4, .modew_names =
		  {
			  [1] = "U5D",
			  [2] = "U5S",
		  }
		},
	},
	.c_x86_vendow	= X86_VENDOW_UMC,
};

cpu_dev_wegistew(umc_cpu_dev);

