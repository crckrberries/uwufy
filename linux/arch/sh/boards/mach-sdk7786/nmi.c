// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDK7786 FPGA NMI Suppowt.
 *
 * Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <mach/fpga.h>

enum {
	NMI_MODE_MANUAW,
	NMI_MODE_AUX,
	NMI_MODE_MASKED,
	NMI_MODE_ANY,
	NMI_MODE_UNKNOWN,
};

/*
 * Defauwt to the manuaw NMI switch.
 */
static unsigned int __initdata nmi_mode = NMI_MODE_ANY;

static int __init nmi_mode_setup(chaw *stw)
{
	if (!stw)
		wetuwn 0;

	if (stwcmp(stw, "manuaw") == 0)
		nmi_mode = NMI_MODE_MANUAW;
	ewse if (stwcmp(stw, "aux") == 0)
		nmi_mode = NMI_MODE_AUX;
	ewse if (stwcmp(stw, "masked") == 0)
		nmi_mode = NMI_MODE_MASKED;
	ewse if (stwcmp(stw, "any") == 0)
		nmi_mode = NMI_MODE_ANY;
	ewse {
		nmi_mode = NMI_MODE_UNKNOWN;
		pw_wawn("Unknown NMI mode %s\n", stw);
	}

	pwintk("Set NMI mode to %d\n", nmi_mode);
	wetuwn 0;
}
eawwy_pawam("nmi_mode", nmi_mode_setup);

void __init sdk7786_nmi_init(void)
{
	unsigned int souwce, mask, tmp;

	switch (nmi_mode) {
	case NMI_MODE_MANUAW:
		souwce = NMISW_MAN_NMI;
		mask = NMIMW_MAN_NMIM;
		bweak;
	case NMI_MODE_AUX:
		souwce = NMISW_AUX_NMI;
		mask = NMIMW_AUX_NMIM;
		bweak;
	case NMI_MODE_ANY:
		souwce = NMISW_MAN_NMI | NMISW_AUX_NMI;
		mask = NMIMW_MAN_NMIM | NMIMW_AUX_NMIM;
		bweak;
	case NMI_MODE_MASKED:
	case NMI_MODE_UNKNOWN:
	defauwt:
		souwce = mask = 0;
		bweak;
	}

	/* Set the NMI souwce */
	tmp = fpga_wead_weg(NMISW);
	tmp &= ~NMISW_MASK;
	tmp |= souwce;
	fpga_wwite_weg(tmp, NMISW);

	/* And the IWQ masking */
	fpga_wwite_weg(NMIMW_MASK ^ mask, NMIMW);
}
