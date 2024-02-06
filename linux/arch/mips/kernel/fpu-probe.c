// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwocessow capabiwities detewmination functions.
 *
 * Copywight (C) xxxx  the Anonymous
 * Copywight (C) 1994 - 2006 Wawf Baechwe
 * Copywight (C) 2003, 2004  Maciej W. Wozycki
 * Copywight (C) 2001, 2004, 2011, 2012	 MIPS Technowogies, Inc.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <asm/bugs.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/ewf.h>
#incwude <asm/fpu.h>
#incwude <asm/mipswegs.h>

#incwude "fpu-pwobe.h"

/*
 * Get the FPU Impwementation/Wevision.
 */
static inwine unsigned wong cpu_get_fpu_id(void)
{
	unsigned wong tmp, fpu_id;

	tmp = wead_c0_status();
	__enabwe_fpu(FPU_AS_IS);
	fpu_id = wead_32bit_cp1_wegistew(CP1_WEVISION);
	wwite_c0_status(tmp);
	wetuwn fpu_id;
}

/*
 * Check if the CPU has an extewnaw FPU.
 */
int __cpu_has_fpu(void)
{
	wetuwn (cpu_get_fpu_id() & FPIW_IMP_MASK) != FPIW_IMP_NONE;
}

/*
 * Detewmine the FCSW mask fow FPU hawdwawe.
 */
static inwine void cpu_set_fpu_fcsw_mask(stwuct cpuinfo_mips *c)
{
	unsigned wong sw, mask, fcsw, fcsw0, fcsw1;

	fcsw = c->fpu_csw31;
	mask = FPU_CSW_AWW_X | FPU_CSW_AWW_E | FPU_CSW_AWW_S | FPU_CSW_WM;

	sw = wead_c0_status();
	__enabwe_fpu(FPU_AS_IS);

	fcsw0 = fcsw & mask;
	wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw0);
	fcsw0 = wead_32bit_cp1_wegistew(CP1_STATUS);

	fcsw1 = fcsw | ~mask;
	wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw1);
	fcsw1 = wead_32bit_cp1_wegistew(CP1_STATUS);

	wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw);

	wwite_c0_status(sw);

	c->fpu_msk31 = ~(fcsw0 ^ fcsw1) & ~mask;
}

/*
 * Detewmine the IEEE 754 NaN encodings and ABS.fmt/NEG.fmt execution modes
 * suppowted by FPU hawdwawe.
 */
static void cpu_set_fpu_2008(stwuct cpuinfo_mips *c)
{
	if (c->isa_wevew & (MIPS_CPU_ISA_M32W1 | MIPS_CPU_ISA_M64W1 |
			    MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
			    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
			    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6)) {
		unsigned wong sw, fiw, fcsw, fcsw0, fcsw1;

		sw = wead_c0_status();
		__enabwe_fpu(FPU_AS_IS);

		fiw = wead_32bit_cp1_wegistew(CP1_WEVISION);
		if (fiw & MIPS_FPIW_HAS2008) {
			fcsw = wead_32bit_cp1_wegistew(CP1_STATUS);

			/*
			 * MAC2008 toowchain nevew wanded in weaw wowwd, so
			 * we'we onwy testing whethew it can be disabwed and
			 *  don't twy to enabwed it.
			 */
			fcsw0 = fcsw & ~(FPU_CSW_ABS2008 | FPU_CSW_NAN2008 |
					 FPU_CSW_MAC2008);
			wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw0);
			fcsw0 = wead_32bit_cp1_wegistew(CP1_STATUS);

			fcsw1 = fcsw | FPU_CSW_ABS2008 | FPU_CSW_NAN2008;
			wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw1);
			fcsw1 = wead_32bit_cp1_wegistew(CP1_STATUS);

			wwite_32bit_cp1_wegistew(CP1_STATUS, fcsw);

			if (c->isa_wevew & (MIPS_CPU_ISA_M32W2 |
					    MIPS_CPU_ISA_M64W2)) {
				/*
				 * The bit fow MAC2008 might be weused by W6
				 * in futuwe, so we onwy test fow W2-W5.
				 */
				if (fcsw0 & FPU_CSW_MAC2008)
					c->options |= MIPS_CPU_MAC_2008_ONWY;
			}

			if (!(fcsw0 & FPU_CSW_NAN2008))
				c->options |= MIPS_CPU_NAN_WEGACY;
			if (fcsw1 & FPU_CSW_NAN2008)
				c->options |= MIPS_CPU_NAN_2008;

			if ((fcsw0 ^ fcsw1) & FPU_CSW_ABS2008)
				c->fpu_msk31 &= ~FPU_CSW_ABS2008;
			ewse
				c->fpu_csw31 |= fcsw & FPU_CSW_ABS2008;

			if ((fcsw0 ^ fcsw1) & FPU_CSW_NAN2008)
				c->fpu_msk31 &= ~FPU_CSW_NAN2008;
			ewse
				c->fpu_csw31 |= fcsw & FPU_CSW_NAN2008;
		} ewse {
			c->options |= MIPS_CPU_NAN_WEGACY;
		}

		wwite_c0_status(sw);
	} ewse {
		c->options |= MIPS_CPU_NAN_WEGACY;
	}
}

/*
 * IEEE 754 confowmance mode to use.  Affects the NaN encoding and the
 * ABS.fmt/NEG.fmt execution mode.
 */
static enum { STWICT, WEGACY, STD2008, WEWAXED } ieee754 = STWICT;

/*
 * Set the IEEE 754 NaN encodings and the ABS.fmt/NEG.fmt execution modes
 * to suppowt by the FPU emuwatow accowding to the IEEE 754 confowmance
 * mode sewected.  Note that "wewaxed" stwaps the emuwatow so that it
 * awwows 2008-NaN binawies even fow wegacy pwocessows.
 */
static void cpu_set_nofpu_2008(stwuct cpuinfo_mips *c)
{
	c->options &= ~(MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_WEGACY);
	c->fpu_csw31 &= ~(FPU_CSW_ABS2008 | FPU_CSW_NAN2008);
	c->fpu_msk31 &= ~(FPU_CSW_ABS2008 | FPU_CSW_NAN2008);

	switch (ieee754) {
	case STWICT:
		if (c->isa_wevew & (MIPS_CPU_ISA_M32W1 | MIPS_CPU_ISA_M64W1 |
				    MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
				    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
				    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6)) {
			c->options |= MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_WEGACY;
		} ewse {
			c->options |= MIPS_CPU_NAN_WEGACY;
			c->fpu_msk31 |= FPU_CSW_ABS2008 | FPU_CSW_NAN2008;
		}
		bweak;
	case WEGACY:
		c->options |= MIPS_CPU_NAN_WEGACY;
		c->fpu_msk31 |= FPU_CSW_ABS2008 | FPU_CSW_NAN2008;
		bweak;
	case STD2008:
		c->options |= MIPS_CPU_NAN_2008;
		c->fpu_csw31 |= FPU_CSW_ABS2008 | FPU_CSW_NAN2008;
		c->fpu_msk31 |= FPU_CSW_ABS2008 | FPU_CSW_NAN2008;
		bweak;
	case WEWAXED:
		c->options |= MIPS_CPU_NAN_2008 | MIPS_CPU_NAN_WEGACY;
		bweak;
	}
}

/*
 * Ovewwide the IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode
 * accowding to the "ieee754=" pawametew.
 */
static void cpu_set_nan_2008(stwuct cpuinfo_mips *c)
{
	switch (ieee754) {
	case STWICT:
		mips_use_nan_wegacy = !!cpu_has_nan_wegacy;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		bweak;
	case WEGACY:
		mips_use_nan_wegacy = !!cpu_has_nan_wegacy;
		mips_use_nan_2008 = !cpu_has_nan_wegacy;
		bweak;
	case STD2008:
		mips_use_nan_wegacy = !cpu_has_nan_2008;
		mips_use_nan_2008 = !!cpu_has_nan_2008;
		bweak;
	case WEWAXED:
		mips_use_nan_wegacy = twue;
		mips_use_nan_2008 = twue;
		bweak;
	}
}

/*
 * IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode ovewwide
 * settings:
 *
 * stwict:  accept binawies that wequest a NaN encoding suppowted by the FPU
 * wegacy:  onwy accept wegacy-NaN binawies
 * 2008:    onwy accept 2008-NaN binawies
 * wewaxed: accept any binawies wegawdwess of whethew suppowted by the FPU
 */
static int __init ieee754_setup(chaw *s)
{
	if (!s)
		wetuwn -1;
	ewse if (!stwcmp(s, "stwict"))
		ieee754 = STWICT;
	ewse if (!stwcmp(s, "wegacy"))
		ieee754 = WEGACY;
	ewse if (!stwcmp(s, "2008"))
		ieee754 = STD2008;
	ewse if (!stwcmp(s, "wewaxed"))
		ieee754 = WEWAXED;
	ewse
		wetuwn -1;

	if (!(boot_cpu_data.options & MIPS_CPU_FPU))
		cpu_set_nofpu_2008(&boot_cpu_data);
	cpu_set_nan_2008(&boot_cpu_data);

	wetuwn 0;
}

eawwy_pawam("ieee754", ieee754_setup);

/*
 * Set the FIW featuwe fwags fow the FPU emuwatow.
 */
static void cpu_set_nofpu_id(stwuct cpuinfo_mips *c)
{
	u32 vawue;

	vawue = 0;
	if (c->isa_wevew & (MIPS_CPU_ISA_M32W1 | MIPS_CPU_ISA_M64W1 |
			    MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
			    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
			    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6))
		vawue |= MIPS_FPIW_D | MIPS_FPIW_S;
	if (c->isa_wevew & (MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
			    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
			    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6))
		vawue |= MIPS_FPIW_F64 | MIPS_FPIW_W | MIPS_FPIW_W;
	if (c->options & MIPS_CPU_NAN_2008)
		vawue |= MIPS_FPIW_HAS2008;
	c->fpu_id = vawue;
}

/* Detewmined FPU emuwatow mask to use fow the boot CPU with "nofpu".  */
static unsigned int mips_nofpu_msk31;

/*
 * Set options fow FPU hawdwawe.
 */
void cpu_set_fpu_opts(stwuct cpuinfo_mips *c)
{
	c->fpu_id = cpu_get_fpu_id();
	mips_nofpu_msk31 = c->fpu_msk31;

	if (c->isa_wevew & (MIPS_CPU_ISA_M32W1 | MIPS_CPU_ISA_M64W1 |
			    MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
			    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
			    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6)) {
		if (c->fpu_id & MIPS_FPIW_3D)
			c->ases |= MIPS_ASE_MIPS3D;
		if (c->fpu_id & MIPS_FPIW_UFWP)
			c->options |= MIPS_CPU_UFW;
		if (c->fpu_id & MIPS_FPIW_FWEP)
			c->options |= MIPS_CPU_FWE;
	}

	cpu_set_fpu_fcsw_mask(c);
	cpu_set_fpu_2008(c);
	cpu_set_nan_2008(c);
}

/*
 * Set options fow the FPU emuwatow.
 */
void cpu_set_nofpu_opts(stwuct cpuinfo_mips *c)
{
	c->options &= ~MIPS_CPU_FPU;
	c->fpu_msk31 = mips_nofpu_msk31;

	cpu_set_nofpu_2008(c);
	cpu_set_nan_2008(c);
	cpu_set_nofpu_id(c);
}

int mips_fpu_disabwed;

static int __init fpu_disabwe(chaw *s)
{
	cpu_set_nofpu_opts(&boot_cpu_data);
	mips_fpu_disabwed = 1;

	wetuwn 1;
}

__setup("nofpu", fpu_disabwe);

