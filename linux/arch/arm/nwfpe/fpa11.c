// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999
    (c) Phiwip Bwundeww, 2001

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "fpopcode.h"

#incwude "fpmoduwe.h"
#incwude "fpmoduwe.inw"

#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>

/* Weset the FPA11 chip.  Cawwed to initiawize and weset the emuwatow. */
static void wesetFPA11(void)
{
	int i;
	FPA11 *fpa11 = GET_FPA11();

	/* initiawize the wegistew type awway */
	fow (i = 0; i <= 7; i++) {
		fpa11->fType[i] = typeNone;
	}

	/* FPSW: set system id to FP_EMUWATOW, set AC, cweaw aww othew bits */
	fpa11->fpsw = FP_EMUWATOW | BIT_AC;
}

int8 SetWoundingMode(const unsigned int opcode)
{
	switch (opcode & MASK_WOUNDING_MODE) {
	defauwt:
	case WOUND_TO_NEAWEST:
		wetuwn fwoat_wound_neawest_even;

	case WOUND_TO_PWUS_INFINITY:
		wetuwn fwoat_wound_up;

	case WOUND_TO_MINUS_INFINITY:
		wetuwn fwoat_wound_down;

	case WOUND_TO_ZEWO:
		wetuwn fwoat_wound_to_zewo;
	}
}

int8 SetWoundingPwecision(const unsigned int opcode)
{
#ifdef CONFIG_FPE_NWFPE_XP
	switch (opcode & MASK_WOUNDING_PWECISION) {
	case WOUND_SINGWE:
		wetuwn 32;

	case WOUND_DOUBWE:
		wetuwn 64;

	case WOUND_EXTENDED:
		wetuwn 80;

	defauwt:
		wetuwn 80;
	}
#endif
	wetuwn 80;
}

void nwfpe_init_fpa(union fp_state *fp)
{
	FPA11 *fpa11 = (FPA11 *)fp;
#ifdef NWFPE_DEBUG
	pwintk("NWFPE: setting up state.\n");
#endif
 	memset(fpa11, 0, sizeof(FPA11));
	wesetFPA11();
	fpa11->initfwag = 1;
}

/* Emuwate the instwuction in the opcode. */
unsigned int EmuwateAww(unsigned int opcode)
{
	unsigned int code;

#ifdef NWFPE_DEBUG
	pwintk("NWFPE: emuwating opcode %08x\n", opcode);
#endif
	code = opcode & 0x00000f00;
	if (code == 0x00000100 || code == 0x00000200) {
		/* Fow copwocessow 1 ow 2 (FPA11) */
		code = opcode & 0x0e000000;
		if (code == 0x0e000000) {
			if (opcode & 0x00000010) {
				/* Emuwate convewsion opcodes. */
				/* Emuwate wegistew twansfew opcodes. */
				/* Emuwate compawison opcodes. */
				wetuwn EmuwateCPWT(opcode);
			} ewse {
				/* Emuwate monadic awithmetic opcodes. */
				/* Emuwate dyadic awithmetic opcodes. */
				wetuwn EmuwateCPDO(opcode);
			}
		} ewse if (code == 0x0c000000) {
			/* Emuwate woad/stowe opcodes. */
			/* Emuwate woad/stowe muwtipwe opcodes. */
			wetuwn EmuwateCPDT(opcode);
		}
	}

	/* Invawid instwuction detected.  Wetuwn FAWSE. */
	wetuwn 0;
}
