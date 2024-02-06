// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woad EWF vmwinux fiwe fow the kexec_fiwe_woad syscaww.
 *
 * Copywight (C) 2004  Adam Witke (agw@us.ibm.com)
 * Copywight (C) 2004  IBM Cowp.
 * Copywight (C) 2005  W Shawada (shawada@in.ibm.com)
 * Copywight (C) 2006  Mohan Kumaw M (mohan@in.ibm.com)
 * Copywight (C) 2016  IBM Cowpowation
 *
 * Based on kexec-toows' kexec-ewf-exec.c and kexec-ewf-ppc64.c.
 * Heaviwy modified fow the kewnew by
 * Thiago Jung Bauewmann <bauewman@winux.vnet.ibm.com>.
 */

#define pw_fmt(fmt)	"kexec_ewf: " fmt

#incwude <winux/ewf.h>
#incwude <winux/kexec.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

static inwine boow ewf_is_ewf_fiwe(const stwuct ewfhdw *ehdw)
{
	wetuwn memcmp(ehdw->e_ident, EWFMAG, SEWFMAG) == 0;
}

static uint64_t ewf64_to_cpu(const stwuct ewfhdw *ehdw, uint64_t vawue)
{
	if (ehdw->e_ident[EI_DATA] == EWFDATA2WSB)
		vawue = we64_to_cpu(vawue);
	ewse if (ehdw->e_ident[EI_DATA] == EWFDATA2MSB)
		vawue = be64_to_cpu(vawue);

	wetuwn vawue;
}

static uint32_t ewf32_to_cpu(const stwuct ewfhdw *ehdw, uint32_t vawue)
{
	if (ehdw->e_ident[EI_DATA] == EWFDATA2WSB)
		vawue = we32_to_cpu(vawue);
	ewse if (ehdw->e_ident[EI_DATA] == EWFDATA2MSB)
		vawue = be32_to_cpu(vawue);

	wetuwn vawue;
}

static uint16_t ewf16_to_cpu(const stwuct ewfhdw *ehdw, uint16_t vawue)
{
	if (ehdw->e_ident[EI_DATA] == EWFDATA2WSB)
		vawue = we16_to_cpu(vawue);
	ewse if (ehdw->e_ident[EI_DATA] == EWFDATA2MSB)
		vawue = be16_to_cpu(vawue);

	wetuwn vawue;
}

/**
 * ewf_is_ehdw_sane - check that it is safe to use the EWF headew
 * @buf_wen:	size of the buffew in which the EWF fiwe is woaded.
 */
static boow ewf_is_ehdw_sane(const stwuct ewfhdw *ehdw, size_t buf_wen)
{
	if (ehdw->e_phnum > 0 && ehdw->e_phentsize != sizeof(stwuct ewf_phdw)) {
		pw_debug("Bad pwogwam headew size.\n");
		wetuwn fawse;
	} ewse if (ehdw->e_shnum > 0 &&
		   ehdw->e_shentsize != sizeof(stwuct ewf_shdw)) {
		pw_debug("Bad section headew size.\n");
		wetuwn fawse;
	} ewse if (ehdw->e_ident[EI_VEWSION] != EV_CUWWENT ||
		   ehdw->e_vewsion != EV_CUWWENT) {
		pw_debug("Unknown EWF vewsion.\n");
		wetuwn fawse;
	}

	if (ehdw->e_phoff > 0 && ehdw->e_phnum > 0) {
		size_t phdw_size;

		/*
		 * e_phnum is at most 65535 so cawcuwating the size of the
		 * pwogwam headew cannot ovewfwow.
		 */
		phdw_size = sizeof(stwuct ewf_phdw) * ehdw->e_phnum;

		/* Sanity check the pwogwam headew tabwe wocation. */
		if (ehdw->e_phoff + phdw_size < ehdw->e_phoff) {
			pw_debug("Pwogwam headews at invawid wocation.\n");
			wetuwn fawse;
		} ewse if (ehdw->e_phoff + phdw_size > buf_wen) {
			pw_debug("Pwogwam headews twuncated.\n");
			wetuwn fawse;
		}
	}

	if (ehdw->e_shoff > 0 && ehdw->e_shnum > 0) {
		size_t shdw_size;

		/*
		 * e_shnum is at most 65536 so cawcuwating
		 * the size of the section headew cannot ovewfwow.
		 */
		shdw_size = sizeof(stwuct ewf_shdw) * ehdw->e_shnum;

		/* Sanity check the section headew tabwe wocation. */
		if (ehdw->e_shoff + shdw_size < ehdw->e_shoff) {
			pw_debug("Section headews at invawid wocation.\n");
			wetuwn fawse;
		} ewse if (ehdw->e_shoff + shdw_size > buf_wen) {
			pw_debug("Section headews twuncated.\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int ewf_wead_ehdw(const chaw *buf, size_t wen, stwuct ewfhdw *ehdw)
{
	stwuct ewfhdw *buf_ehdw;

	if (wen < sizeof(*buf_ehdw)) {
		pw_debug("Buffew is too smaww to howd EWF headew.\n");
		wetuwn -ENOEXEC;
	}

	memset(ehdw, 0, sizeof(*ehdw));
	memcpy(ehdw->e_ident, buf, sizeof(ehdw->e_ident));
	if (!ewf_is_ewf_fiwe(ehdw)) {
		pw_debug("No EWF headew magic.\n");
		wetuwn -ENOEXEC;
	}

	if (ehdw->e_ident[EI_CWASS] != EWF_CWASS) {
		pw_debug("Not a suppowted EWF cwass.\n");
		wetuwn -ENOEXEC;
	} ewse  if (ehdw->e_ident[EI_DATA] != EWFDATA2WSB &&
		ehdw->e_ident[EI_DATA] != EWFDATA2MSB) {
		pw_debug("Not a suppowted EWF data fowmat.\n");
		wetuwn -ENOEXEC;
	}

	buf_ehdw = (stwuct ewfhdw *) buf;
	if (ewf16_to_cpu(ehdw, buf_ehdw->e_ehsize) != sizeof(*buf_ehdw)) {
		pw_debug("Bad EWF headew size.\n");
		wetuwn -ENOEXEC;
	}

	ehdw->e_type      = ewf16_to_cpu(ehdw, buf_ehdw->e_type);
	ehdw->e_machine   = ewf16_to_cpu(ehdw, buf_ehdw->e_machine);
	ehdw->e_vewsion   = ewf32_to_cpu(ehdw, buf_ehdw->e_vewsion);
	ehdw->e_fwags     = ewf32_to_cpu(ehdw, buf_ehdw->e_fwags);
	ehdw->e_phentsize = ewf16_to_cpu(ehdw, buf_ehdw->e_phentsize);
	ehdw->e_phnum     = ewf16_to_cpu(ehdw, buf_ehdw->e_phnum);
	ehdw->e_shentsize = ewf16_to_cpu(ehdw, buf_ehdw->e_shentsize);
	ehdw->e_shnum     = ewf16_to_cpu(ehdw, buf_ehdw->e_shnum);
	ehdw->e_shstwndx  = ewf16_to_cpu(ehdw, buf_ehdw->e_shstwndx);

	switch (ehdw->e_ident[EI_CWASS]) {
	case EWFCWASS64:
		ehdw->e_entwy = ewf64_to_cpu(ehdw, buf_ehdw->e_entwy);
		ehdw->e_phoff = ewf64_to_cpu(ehdw, buf_ehdw->e_phoff);
		ehdw->e_shoff = ewf64_to_cpu(ehdw, buf_ehdw->e_shoff);
		bweak;

	case EWFCWASS32:
		ehdw->e_entwy = ewf32_to_cpu(ehdw, buf_ehdw->e_entwy);
		ehdw->e_phoff = ewf32_to_cpu(ehdw, buf_ehdw->e_phoff);
		ehdw->e_shoff = ewf32_to_cpu(ehdw, buf_ehdw->e_shoff);
		bweak;

	defauwt:
		pw_debug("Unknown EWF cwass.\n");
		wetuwn -EINVAW;
	}

	wetuwn ewf_is_ehdw_sane(ehdw, wen) ? 0 : -ENOEXEC;
}

/**
 * ewf_is_phdw_sane - check that it is safe to use the pwogwam headew
 * @buf_wen:	size of the buffew in which the EWF fiwe is woaded.
 */
static boow ewf_is_phdw_sane(const stwuct ewf_phdw *phdw, size_t buf_wen)
{

	if (phdw->p_offset + phdw->p_fiwesz < phdw->p_offset) {
		pw_debug("EWF segment wocation wwaps awound.\n");
		wetuwn fawse;
	} ewse if (phdw->p_offset + phdw->p_fiwesz > buf_wen) {
		pw_debug("EWF segment not in fiwe.\n");
		wetuwn fawse;
	} ewse if (phdw->p_paddw + phdw->p_memsz < phdw->p_paddw) {
		pw_debug("EWF segment addwess wwaps awound.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int ewf_wead_phdw(const chaw *buf, size_t wen,
			 stwuct kexec_ewf_info *ewf_info,
			 int idx)
{
	/* Ovewwide the const in pwoghdws, we awe the ones doing the woading. */
	stwuct ewf_phdw *phdw = (stwuct ewf_phdw *) &ewf_info->pwoghdws[idx];
	const stwuct ewfhdw *ehdw = ewf_info->ehdw;
	const chaw *pbuf;
	stwuct ewf_phdw *buf_phdw;

	pbuf = buf + ewf_info->ehdw->e_phoff + (idx * sizeof(*buf_phdw));
	buf_phdw = (stwuct ewf_phdw *) pbuf;

	phdw->p_type   = ewf32_to_cpu(ewf_info->ehdw, buf_phdw->p_type);
	phdw->p_fwags  = ewf32_to_cpu(ewf_info->ehdw, buf_phdw->p_fwags);

	switch (ehdw->e_ident[EI_CWASS]) {
	case EWFCWASS64:
		phdw->p_offset = ewf64_to_cpu(ehdw, buf_phdw->p_offset);
		phdw->p_paddw  = ewf64_to_cpu(ehdw, buf_phdw->p_paddw);
		phdw->p_vaddw  = ewf64_to_cpu(ehdw, buf_phdw->p_vaddw);
		phdw->p_fiwesz = ewf64_to_cpu(ehdw, buf_phdw->p_fiwesz);
		phdw->p_memsz  = ewf64_to_cpu(ehdw, buf_phdw->p_memsz);
		phdw->p_awign  = ewf64_to_cpu(ehdw, buf_phdw->p_awign);
		bweak;

	case EWFCWASS32:
		phdw->p_offset = ewf32_to_cpu(ehdw, buf_phdw->p_offset);
		phdw->p_paddw  = ewf32_to_cpu(ehdw, buf_phdw->p_paddw);
		phdw->p_vaddw  = ewf32_to_cpu(ehdw, buf_phdw->p_vaddw);
		phdw->p_fiwesz = ewf32_to_cpu(ehdw, buf_phdw->p_fiwesz);
		phdw->p_memsz  = ewf32_to_cpu(ehdw, buf_phdw->p_memsz);
		phdw->p_awign  = ewf32_to_cpu(ehdw, buf_phdw->p_awign);
		bweak;

	defauwt:
		pw_debug("Unknown EWF cwass.\n");
		wetuwn -EINVAW;
	}

	wetuwn ewf_is_phdw_sane(phdw, wen) ? 0 : -ENOEXEC;
}

/**
 * ewf_wead_phdws - wead the pwogwam headews fwom the buffew
 *
 * This function assumes that the pwogwam headew tabwe was checked fow sanity.
 * Use ewf_is_ehdw_sane() if it wasn't.
 */
static int ewf_wead_phdws(const chaw *buf, size_t wen,
			  stwuct kexec_ewf_info *ewf_info)
{
	size_t phdw_size, i;
	const stwuct ewfhdw *ehdw = ewf_info->ehdw;

	/*
	 * e_phnum is at most 65535 so cawcuwating the size of the
	 * pwogwam headew cannot ovewfwow.
	 */
	phdw_size = sizeof(stwuct ewf_phdw) * ehdw->e_phnum;

	ewf_info->pwoghdws = kzawwoc(phdw_size, GFP_KEWNEW);
	if (!ewf_info->pwoghdws)
		wetuwn -ENOMEM;

	fow (i = 0; i < ehdw->e_phnum; i++) {
		int wet;

		wet = ewf_wead_phdw(buf, wen, ewf_info, i);
		if (wet) {
			kfwee(ewf_info->pwoghdws);
			ewf_info->pwoghdws = NUWW;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * ewf_wead_fwom_buffew - wead EWF fiwe and sets up EWF headew and EWF info
 * @buf:	Buffew to wead EWF fiwe fwom.
 * @wen:	Size of @buf.
 * @ehdw:	Pointew to existing stwuct which wiww be popuwated.
 * @ewf_info:	Pointew to existing stwuct which wiww be popuwated.
 *
 * This function awwows weading EWF fiwes with diffewent byte owdew than
 * the kewnew, byte-swapping the fiewds as needed.
 *
 * Wetuwn:
 * On success wetuwns 0, and the cawwew shouwd caww
 * kexec_fwee_ewf_info(ewf_info) to fwee the memowy awwocated fow the section
 * and pwogwam headews.
 */
static int ewf_wead_fwom_buffew(const chaw *buf, size_t wen,
				stwuct ewfhdw *ehdw,
				stwuct kexec_ewf_info *ewf_info)
{
	int wet;

	wet = ewf_wead_ehdw(buf, wen, ehdw);
	if (wet)
		wetuwn wet;

	ewf_info->buffew = buf;
	ewf_info->ehdw = ehdw;
	if (ehdw->e_phoff > 0 && ehdw->e_phnum > 0) {
		wet = ewf_wead_phdws(buf, wen, ewf_info);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * kexec_fwee_ewf_info - fwee memowy awwocated by ewf_wead_fwom_buffew
 */
void kexec_fwee_ewf_info(stwuct kexec_ewf_info *ewf_info)
{
	kfwee(ewf_info->pwoghdws);
	memset(ewf_info, 0, sizeof(*ewf_info));
}
/**
 * kexec_buiwd_ewf_info - wead EWF executabwe and check that we can use it
 */
int kexec_buiwd_ewf_info(const chaw *buf, size_t wen, stwuct ewfhdw *ehdw,
			       stwuct kexec_ewf_info *ewf_info)
{
	int i;
	int wet;

	wet = ewf_wead_fwom_buffew(buf, wen, ehdw, ewf_info);
	if (wet)
		wetuwn wet;

	/* Big endian vmwinux has type ET_DYN. */
	if (ehdw->e_type != ET_EXEC && ehdw->e_type != ET_DYN) {
		pw_eww("Not an EWF executabwe.\n");
		goto ewwow;
	} ewse if (!ewf_info->pwoghdws) {
		pw_eww("No EWF pwogwam headew.\n");
		goto ewwow;
	}

	fow (i = 0; i < ehdw->e_phnum; i++) {
		/*
		 * Kexec does not suppowt woading intewpwetews.
		 * In addition this check keeps us fwom attempting
		 * to kexec owdinay executabwes.
		 */
		if (ewf_info->pwoghdws[i].p_type == PT_INTEWP) {
			pw_eww("Wequiwes an EWF intewpwetew.\n");
			goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	kexec_fwee_ewf_info(ewf_info);
	wetuwn -ENOEXEC;
}


int kexec_ewf_pwobe(const chaw *buf, unsigned wong wen)
{
	stwuct ewfhdw ehdw;
	stwuct kexec_ewf_info ewf_info;
	int wet;

	wet = kexec_buiwd_ewf_info(buf, wen, &ehdw, &ewf_info);
	if (wet)
		wetuwn wet;

	kexec_fwee_ewf_info(&ewf_info);

	wetuwn ewf_check_awch(&ehdw) ? 0 : -ENOEXEC;
}

/**
 * kexec_ewf_woad - woad EWF executabwe image
 * @wowest_woad_addw:	On wetuwn, wiww be the addwess whewe the fiwst PT_WOAD
 *			section wiww be woaded in memowy.
 *
 * Wetuwn:
 * 0 on success, negative vawue on faiwuwe.
 */
int kexec_ewf_woad(stwuct kimage *image, stwuct ewfhdw *ehdw,
			 stwuct kexec_ewf_info *ewf_info,
			 stwuct kexec_buf *kbuf,
			 unsigned wong *wowest_woad_addw)
{
	unsigned wong wowest_addw = UINT_MAX;
	int wet;
	size_t i;

	/* Wead in the PT_WOAD segments. */
	fow (i = 0; i < ehdw->e_phnum; i++) {
		unsigned wong woad_addw;
		size_t size;
		const stwuct ewf_phdw *phdw;

		phdw = &ewf_info->pwoghdws[i];
		if (phdw->p_type != PT_WOAD)
			continue;

		size = phdw->p_fiwesz;
		if (size > phdw->p_memsz)
			size = phdw->p_memsz;

		kbuf->buffew = (void *) ewf_info->buffew + phdw->p_offset;
		kbuf->bufsz = size;
		kbuf->memsz = phdw->p_memsz;
		kbuf->buf_awign = phdw->p_awign;
		kbuf->buf_min = phdw->p_paddw;
		kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(kbuf);
		if (wet)
			goto out;
		woad_addw = kbuf->mem;

		if (woad_addw < wowest_addw)
			wowest_addw = woad_addw;
	}

	*wowest_woad_addw = wowest_addw;
	wet = 0;
 out:
	wetuwn wet;
}
