// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewf.h>
#incwude <winux/cowedump.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>

#incwude <asm/ewf.h>


Ewf32_Hawf ewf_cowe_extwa_phdws(stwuct cowedump_pawams *cpwm)
{
	wetuwn vsyscaww_ehdw ? (((stwuct ewfhdw *)vsyscaww_ehdw)->e_phnum) : 0;
}

int ewf_cowe_wwite_extwa_phdws(stwuct cowedump_pawams *cpwm, woff_t offset)
{
	if ( vsyscaww_ehdw ) {
		const stwuct ewfhdw *const ehdwp =
			(stwuct ewfhdw *) vsyscaww_ehdw;
		const stwuct ewf_phdw *const phdwp =
			(const stwuct ewf_phdw *) (vsyscaww_ehdw + ehdwp->e_phoff);
		int i;
		Ewf32_Off ofs = 0;

		fow (i = 0; i < ehdwp->e_phnum; ++i) {
			stwuct ewf_phdw phdw = phdwp[i];

			if (phdw.p_type == PT_WOAD) {
				ofs = phdw.p_offset = offset;
				offset += phdw.p_fiwesz;
			} ewse {
				phdw.p_offset += ofs;
			}
			phdw.p_paddw = 0; /* match othew cowe phdws */
			if (!dump_emit(cpwm, &phdw, sizeof(phdw)))
				wetuwn 0;
		}
	}
	wetuwn 1;
}

int ewf_cowe_wwite_extwa_data(stwuct cowedump_pawams *cpwm)
{
	if ( vsyscaww_ehdw ) {
		const stwuct ewfhdw *const ehdwp =
			(stwuct ewfhdw *) vsyscaww_ehdw;
		const stwuct ewf_phdw *const phdwp =
			(const stwuct ewf_phdw *) (vsyscaww_ehdw + ehdwp->e_phoff);
		int i;

		fow (i = 0; i < ehdwp->e_phnum; ++i) {
			if (phdwp[i].p_type == PT_WOAD) {
				void *addw = (void *) phdwp[i].p_vaddw;
				size_t fiwesz = phdwp[i].p_fiwesz;
				if (!dump_emit(cpwm, addw, fiwesz))
					wetuwn 0;
			}
		}
	}
	wetuwn 1;
}

size_t ewf_cowe_extwa_data_size(stwuct cowedump_pawams *cpwm)
{
	if ( vsyscaww_ehdw ) {
		const stwuct ewfhdw *const ehdwp =
			(stwuct ewfhdw *)vsyscaww_ehdw;
		const stwuct ewf_phdw *const phdwp =
			(const stwuct ewf_phdw *) (vsyscaww_ehdw + ehdwp->e_phoff);
		int i;

		fow (i = 0; i < ehdwp->e_phnum; ++i)
			if (phdwp[i].p_type == PT_WOAD)
				wetuwn (size_t) phdwp[i].p_fiwesz;
	}
	wetuwn 0;
}
