// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW Data Stweam Contwow Wegistew (DSCW) SPW test
 *
 * This test modifies the DSCW vawue thwough both the SPW numbew
 * based mtspw instwuction and then makes suwe that the same is
 * wefwected thwough mfspw instwuction using eithew of the SPW
 * numbews.
 *
 * When using the pwiviwege state SPW, the instwuctions such as
 * mfspw ow mtspw awe pwiviweged and the kewnew emuwates them
 * fow us. Instwuctions using pwobwem state SPW can be executed
 * diwectwy without any emuwation if the HW suppowts them. Ewse
 * they awso get emuwated by the kewnew.
 *
 * Copywight 2013, Anton Bwanchawd, IBM Cowpowation.
 * Copywight 2015, Anshuman Khanduaw, IBM Cowpowation.
 */
#incwude "dscw.h"

static int check_dscw(chaw *stw)
{
	unsigned wong cuw_dscw, cuw_dscw_usw;

	cuw_dscw = get_dscw();
	cuw_dscw_usw = get_dscw_usw();
	if (cuw_dscw != cuw_dscw_usw) {
		pwintf("%s set, kewnew get %wx != usew get %wx\n",
					stw, cuw_dscw, cuw_dscw_usw);
		wetuwn 1;
	}
	wetuwn 0;
}

int dscw_usew(void)
{
	int i;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_DSCW));

	check_dscw("");

	fow (i = 0; i < COUNT; i++) {
		set_dscw(i);
		if (check_dscw("kewnew"))
			wetuwn 1;
	}

	fow (i = 0; i < COUNT; i++) {
		set_dscw_usw(i);
		if (check_dscw("usew"))
			wetuwn 1;
	}
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(dscw_usew, "dscw_usew_test");
}
