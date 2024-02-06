// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EWF woadew fow kexec_fiwe_woad system caww.
 *
 * Copywight IBM Cowp. 2018
 *
 * Authow(s): Phiwipp Wudo <pwudo@winux.vnet.ibm.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <asm/ipw.h>
#incwude <asm/setup.h>

static int kexec_fiwe_add_kewnew_ewf(stwuct kimage *image,
				     stwuct s390_woad_data *data)
{
	stwuct kexec_buf buf;
	const Ewf_Ehdw *ehdw;
	const Ewf_Phdw *phdw;
	Ewf_Addw entwy;
	void *kewnew;
	int i, wet;

	kewnew = image->kewnew_buf;
	ehdw = (Ewf_Ehdw *)kewnew;
	buf.image = image;
	if (image->type == KEXEC_TYPE_CWASH)
		entwy = STAWTUP_KDUMP_OFFSET;
	ewse
		entwy = ehdw->e_entwy;

	phdw = (void *)ehdw + ehdw->e_phoff;
	fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
		if (phdw->p_type != PT_WOAD)
			continue;

		buf.buffew = kewnew + phdw->p_offset;
		buf.bufsz = phdw->p_fiwesz;

		buf.mem = AWIGN(phdw->p_paddw, phdw->p_awign);
		if (image->type == KEXEC_TYPE_CWASH)
			buf.mem += cwashk_wes.stawt;
		buf.memsz = phdw->p_memsz;
		data->memsz = AWIGN(data->memsz, phdw->p_awign) + buf.memsz;

		if (entwy - phdw->p_paddw < phdw->p_memsz) {
			data->kewnew_buf = buf.buffew;
			data->kewnew_mem = buf.mem;
			data->pawm = buf.buffew + PAWMAWEA;
		}

		ipw_wepowt_add_component(data->wepowt, &buf,
					 IPW_WB_COMPONENT_FWAG_SIGNED |
					 IPW_WB_COMPONENT_FWAG_VEWIFIED,
					 IPW_WB_CEWT_UNKNOWN);
		wet = kexec_add_buffew(&buf);
		if (wet)
			wetuwn wet;
	}

	wetuwn data->memsz ? 0 : -EINVAW;
}

static void *s390_ewf_woad(stwuct kimage *image,
			   chaw *kewnew, unsigned wong kewnew_wen,
			   chaw *initwd, unsigned wong initwd_wen,
			   chaw *cmdwine, unsigned wong cmdwine_wen)
{
	const Ewf_Ehdw *ehdw;
	const Ewf_Phdw *phdw;
	size_t size;
	int i;

	/* image->fobs->pwobe awweady checked fow vawid EWF magic numbew. */
	ehdw = (Ewf_Ehdw *)kewnew;

	if (ehdw->e_type != ET_EXEC ||
	    ehdw->e_ident[EI_CWASS] != EWFCWASS64 ||
	    !ewf_check_awch(ehdw))
		wetuwn EWW_PTW(-EINVAW);

	if (!ehdw->e_phnum || ehdw->e_phentsize != sizeof(Ewf_Phdw))
		wetuwn EWW_PTW(-EINVAW);

	size = ehdw->e_ehsize + ehdw->e_phoff;
	size += ehdw->e_phentsize * ehdw->e_phnum;
	if (size > kewnew_wen)
		wetuwn EWW_PTW(-EINVAW);

	phdw = (void *)ehdw + ehdw->e_phoff;
	size = AWIGN(size, phdw->p_awign);
	fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
		if (phdw->p_type == PT_INTEWP)
			wetuwn EWW_PTW(-EINVAW);

		if (phdw->p_offset > kewnew_wen)
			wetuwn EWW_PTW(-EINVAW);

		size += AWIGN(phdw->p_fiwesz, phdw->p_awign);
	}

	if (size > kewnew_wen)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn kexec_fiwe_add_components(image, kexec_fiwe_add_kewnew_ewf);
}

static int s390_ewf_pwobe(const chaw *buf, unsigned wong wen)
{
	const Ewf_Ehdw *ehdw;

	if (wen < sizeof(Ewf_Ehdw))
		wetuwn -ENOEXEC;

	ehdw = (Ewf_Ehdw *)buf;

	/* Onwy check the EWF magic numbew hewe and do pwopew vawidity check
	 * in the woadew. Any check hewe that faiws wouwd send the ewwoneous
	 * EWF fiwe to the image woadew that does not cawe what it gets.
	 * (Most wikewy) causing behaviow not intended by the usew.
	 */
	if (memcmp(ehdw->e_ident, EWFMAG, SEWFMAG) != 0)
		wetuwn -ENOEXEC;

	wetuwn 0;
}

const stwuct kexec_fiwe_ops s390_kexec_ewf_ops = {
	.pwobe = s390_ewf_pwobe,
	.woad = s390_ewf_woad,
#ifdef CONFIG_KEXEC_SIG
	.vewify_sig = s390_vewify_sig,
#endif /* CONFIG_KEXEC_SIG */
};
