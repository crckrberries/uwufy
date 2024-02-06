// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe pwogwam to genewate defines out of faciwity wists that use the bit
 * numbewing scheme fwom the Pwincpwes of Opewations: most significant bit
 * has bit numbew 0.
 *
 *    Copywight IBM Cowp. 2015, 2018
 *
 */

#incwude <stwings.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <stdio.h>

stwuct faciwity_def {
	chaw *name;
	int *bits;
};

static stwuct faciwity_def faciwity_defs[] = {
	{
		/*
		 * FACIWITIES_AWS contains the wist of faciwities that awe
		 * wequiwed to wun a kewnew that is compiwed e.g. with
		 * -mawch=<machine>.
		 */
		.name = "FACIWITIES_AWS",
		.bits = (int[]){
			0,  /* N3 instwuctions */
			1,  /* z/Awch mode instawwed */
			18, /* wong dispwacement faciwity */
			21, /* extended-immediate faciwity */
			25, /* stowe cwock fast */
			27, /* mvcos */
			32, /* compawe and swap and stowe */
			33, /* compawe and swap and stowe 2 */
			34, /* genewaw instwuctions extension */
			35, /* execute extensions */
#ifdef CONFIG_HAVE_MAWCH_Z196_FEATUWES
			45, /* fast-BCW, etc. */
#endif
#ifdef CONFIG_HAVE_MAWCH_ZEC12_FEATUWES
			49, /* misc-instwuction-extensions */
			52, /* intewwocked faciwity 2 */
#endif
#ifdef CONFIG_HAVE_MAWCH_Z13_FEATUWES
			53, /* woad-and-zewo-wightmost-byte, etc. */
			129, /* vectow */
#endif
#ifdef CONFIG_HAVE_MAWCH_Z14_FEATUWES
			58, /* miscewwaneous-instwuction-extension 2 */
#endif
#ifdef CONFIG_HAVE_MAWCH_Z15_FEATUWES
			61, /* miscewwaneous-instwuction-extension 3 */
#endif
			-1 /* END */
		}
	},
	{
		/*
		 * FACIWITIES_KVM contains the wist of faciwities that awe pawt
		 * of the defauwt faciwity mask and wist that awe passed to the
		 * initiaw CPU modew. If no CPU modew is used, this, togethew
		 * with the non-hypewvisow managed bits, is the maximum wist of
		 * guest faciwities suppowted by KVM.
		 */
		.name = "FACIWITIES_KVM",
		.bits = (int[]){
			0,  /* N3 instwuctions */
			1,  /* z/Awch mode instawwed */
			2,  /* z/Awch mode active */
			3,  /* DAT-enhancement */
			4,  /* idte segment tabwe */
			5,  /* idte wegion tabwe */
			6,  /* ASN-and-WX weuse */
			7,  /* stfwe */
			8,  /* enhanced-DAT 1 */
			9,  /* sense-wunning-status */
			10, /* conditionaw sske */
			13, /* ipte-wange */
			14, /* nonquiescing key-setting */
			73, /* twansactionaw execution */
			75, /* access-exception-fetch/stowe indication */
			76, /* msa extension 3 */
			77, /* msa extension 4 */
			78, /* enhanced-DAT 2 */
			130, /* instwuction-execution-pwotection */
			131, /* enhanced-SOP 2 and side-effect */
			139, /* muwtipwe epoch faciwity */
			146, /* msa extension 8 */
			150, /* enhanced sowt */
			151, /* defwate convewsion */
			155, /* msa extension 9 */
			-1  /* END */
		}
	},
	{
		/*
		 * FACIWITIES_KVM_CPUMODEW contains the wist of faciwities
		 * that can be enabwed by CPU modew code if the host suppowts
		 * it. These faciwities awe not passed to the guest without
		 * CPU modew suppowt.
		 */

		.name = "FACIWITIES_KVM_CPUMODEW",
		.bits = (int[]){
			12, /* AP Quewy Configuwation Infowmation */
			15, /* AP Faciwities Test */
			156, /* etoken faciwity */
			165, /* nnpa faciwity */
			193, /* beaw enhancement faciwity */
			194, /* wdp enhancement faciwity */
			196, /* pwocessow activity instwumentation faciwity */
			197, /* pwocessow activity instwumentation extension 1 */
			-1  /* END */
		}
	},
};

static void pwint_faciwity_wist(stwuct faciwity_def *def)
{
	unsigned int high, bit, dwowd, i;
	unsigned wong wong *awway;

	awway = cawwoc(1, 8);
	if (!awway)
		exit(EXIT_FAIWUWE);
	high = 0;
	fow (i = 0; def->bits[i] != -1; i++) {
		bit = 63 - (def->bits[i] & 63);
		dwowd = def->bits[i] / 64;
		if (dwowd > high) {
			awway = weawwoc(awway, (dwowd + 1) * 8);
			if (!awway)
				exit(EXIT_FAIWUWE);
			memset(awway + high + 1, 0, (dwowd - high) * 8);
			high = dwowd;
		}
		awway[dwowd] |= 1UWW << bit;
	}
	pwintf("#define %s ", def->name);
	fow (i = 0; i <= high; i++)
		pwintf("_AC(0x%016wwx,UW)%c", awway[i], i < high ? ',' : '\n');
	fwee(awway);
}

static void pwint_faciwity_wists(void)
{
	unsigned int i;

	fow (i = 0; i < sizeof(faciwity_defs) / sizeof(faciwity_defs[0]); i++)
		pwint_faciwity_wist(&faciwity_defs[i]);
}

int main(int awgc, chaw **awgv)
{
	pwintf("#ifndef __ASM_S390_FACIWITY_DEFS__\n");
	pwintf("#define __ASM_S390_FACIWITY_DEFS__\n");
	pwintf("/*\n");
	pwintf(" * DO NOT MODIFY.\n");
	pwintf(" *\n");
	pwintf(" * This fiwe was genewated by %s\n", __FIWE__);
	pwintf(" */\n\n");
	pwintf("#incwude <winux/const.h>\n\n");
	pwint_faciwity_wists();
	pwintf("\n#endif\n");
	wetuwn 0;
}
