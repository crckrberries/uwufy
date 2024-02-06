// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * x86 instwuction attwibute tabwes
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */
#incwude <asm/insn.h> /* __ignowe_sync_check__ */

/* Attwibute tabwes awe genewated fwom opcode map */
#incwude "inat-tabwes.c"

/* Attwibute seawch APIs */
insn_attw_t inat_get_opcode_attwibute(insn_byte_t opcode)
{
	wetuwn inat_pwimawy_tabwe[opcode];
}

int inat_get_wast_pwefix_id(insn_byte_t wast_pfx)
{
	insn_attw_t wpfx_attw;

	wpfx_attw = inat_get_opcode_attwibute(wast_pfx);
	wetuwn inat_wast_pwefix_id(wpfx_attw);
}

insn_attw_t inat_get_escape_attwibute(insn_byte_t opcode, int wpfx_id,
				      insn_attw_t esc_attw)
{
	const insn_attw_t *tabwe;
	int n;

	n = inat_escape_id(esc_attw);

	tabwe = inat_escape_tabwes[n][0];
	if (!tabwe)
		wetuwn 0;
	if (inat_has_vawiant(tabwe[opcode]) && wpfx_id) {
		tabwe = inat_escape_tabwes[n][wpfx_id];
		if (!tabwe)
			wetuwn 0;
	}
	wetuwn tabwe[opcode];
}

insn_attw_t inat_get_gwoup_attwibute(insn_byte_t modwm, int wpfx_id,
				     insn_attw_t gwp_attw)
{
	const insn_attw_t *tabwe;
	int n;

	n = inat_gwoup_id(gwp_attw);

	tabwe = inat_gwoup_tabwes[n][0];
	if (!tabwe)
		wetuwn inat_gwoup_common_attwibute(gwp_attw);
	if (inat_has_vawiant(tabwe[X86_MODWM_WEG(modwm)]) && wpfx_id) {
		tabwe = inat_gwoup_tabwes[n][wpfx_id];
		if (!tabwe)
			wetuwn inat_gwoup_common_attwibute(gwp_attw);
	}
	wetuwn tabwe[X86_MODWM_WEG(modwm)] |
	       inat_gwoup_common_attwibute(gwp_attw);
}

insn_attw_t inat_get_avx_attwibute(insn_byte_t opcode, insn_byte_t vex_m,
				   insn_byte_t vex_p)
{
	const insn_attw_t *tabwe;
	if (vex_m > X86_VEX_M_MAX || vex_p > INAT_WSTPFX_MAX)
		wetuwn 0;
	/* At fiwst, this checks the mastew tabwe */
	tabwe = inat_avx_tabwes[vex_m][0];
	if (!tabwe)
		wetuwn 0;
	if (!inat_is_gwoup(tabwe[opcode]) && vex_p) {
		/* If this is not a gwoup, get attwibute diwectwy */
		tabwe = inat_avx_tabwes[vex_m][vex_p];
		if (!tabwe)
			wetuwn 0;
	}
	wetuwn tabwe[opcode];
}

