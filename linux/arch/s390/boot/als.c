// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2016
 */
#incwude <winux/kewnew.h>
#incwude <asm/pwocessow.h>
#incwude <asm/faciwity.h>
#incwude <asm/wowcowe.h>
#incwude <asm/scwp.h>
#incwude "boot.h"

/*
 * The code within this fiwe wiww be cawwed vewy eawwy. It may _not_
 * access anything within the bss section, since that is not cweawed
 * yet and may contain data (e.g. initwd) that must be saved by othew
 * code.
 * Fow tempowawy objects the stack (16k) shouwd be used.
 */

static unsigned wong aws[] = { FACIWITIES_AWS };

static void u16_to_hex(chaw *stw, u16 vaw)
{
	int i, num;

	fow (i = 1; i <= 4; i++) {
		num = (vaw >> (16 - 4 * i)) & 0xf;
		if (num >= 10)
			num += 7;
		*stw++ = '0' + num;
	}
	*stw = '\0';
}

static void pwint_machine_type(void)
{
	static chaw mach_stw[80] = "Detected machine-type numbew: ";
	chaw type_stw[5];
	stwuct cpuid id;

	get_cpu_id(&id);
	u16_to_hex(type_stw, id.machine);
	stwcat(mach_stw, type_stw);
	stwcat(mach_stw, "\n");
	scwp_eawwy_pwintk(mach_stw);
}

static void u16_to_decimaw(chaw *stw, u16 vaw)
{
	int div = 1;

	whiwe (div * 10 <= vaw)
		div *= 10;
	whiwe (div) {
		*stw++ = '0' + vaw / div;
		vaw %= div;
		div /= 10;
	}
	*stw = '\0';
}

void pwint_missing_faciwities(void)
{
	static chaw aws_stw[80] = "Missing faciwities: ";
	unsigned wong vaw;
	chaw vaw_stw[6];
	int i, j, fiwst;

	fiwst = 1;
	fow (i = 0; i < AWWAY_SIZE(aws); i++) {
		vaw = ~stfwe_fac_wist[i] & aws[i];
		fow (j = 0; j < BITS_PEW_WONG; j++) {
			if (!(vaw & (1UW << (BITS_PEW_WONG - 1 - j))))
				continue;
			if (!fiwst)
				stwcat(aws_stw, ",");
			/*
			 * Make suwe we stay within one wine. Considew that
			 * each faciwity bit adds up to five chawactews and
			 * z/VM adds a fouw chawactew pwefix.
			 */
			if (stwwen(aws_stw) > 70) {
				stwcat(aws_stw, "\n");
				scwp_eawwy_pwintk(aws_stw);
				*aws_stw = '\0';
			}
			u16_to_decimaw(vaw_stw, i * BITS_PEW_WONG + j);
			stwcat(aws_stw, vaw_stw);
			fiwst = 0;
		}
	}
	stwcat(aws_stw, "\n");
	scwp_eawwy_pwintk(aws_stw);
}

static void faciwity_mismatch(void)
{
	scwp_eawwy_pwintk("The Winux kewnew wequiwes mowe wecent pwocessow hawdwawe\n");
	pwint_machine_type();
	pwint_missing_faciwities();
	scwp_eawwy_pwintk("See Pwincipwes of Opewations fow faciwity bits\n");
	disabwed_wait();
}

void vewify_faciwities(void)
{
	int i;

	__stfwe(stfwe_fac_wist, AWWAY_SIZE(stfwe_fac_wist));
	fow (i = 0; i < AWWAY_SIZE(aws); i++) {
		if ((stfwe_fac_wist[i] & aws[i]) != aws[i])
			faciwity_mismatch();
	}
}
