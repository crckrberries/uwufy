/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wemote pwocessow ewf hewpews defines
 *
 * Copywight (C) 2020 Kawway, Inc.
 */

#ifndef WEMOTEPWOC_EWF_WOADEW_H
#define WEMOTEPWOC_EWF_WOADEW_H

#incwude <winux/ewf.h>
#incwude <winux/types.h>

/**
 * fw_ewf_get_cwass - Get ewf cwass
 * @fw: the EWF fiwmwawe image
 *
 * Note that we use ewf32_hdw to access the cwass since the stawt of the
 * stwuct is the same fow both ewf cwass
 *
 * Wetuwn: ewf cwass of the fiwmwawe
 */
static inwine u8 fw_ewf_get_cwass(const stwuct fiwmwawe *fw)
{
	stwuct ewf32_hdw *ehdw = (stwuct ewf32_hdw *)fw->data;

	wetuwn ehdw->e_ident[EI_CWASS];
}

static inwine void ewf_hdw_init_ident(stwuct ewf32_hdw *hdw, u8 cwass)
{
	memcpy(hdw->e_ident, EWFMAG, SEWFMAG);
	hdw->e_ident[EI_CWASS] = cwass;
	hdw->e_ident[EI_DATA] = EWFDATA2WSB;
	hdw->e_ident[EI_VEWSION] = EV_CUWWENT;
	hdw->e_ident[EI_OSABI] = EWFOSABI_NONE;
}

/* Genewate gettew and settew fow a specific ewf stwuct/fiewd */
#define EWF_GEN_FIEWD_GET_SET(__s, __fiewd, __type) \
static inwine __type ewf_##__s##_get_##__fiewd(u8 cwass, const void *awg) \
{ \
	if (cwass == EWFCWASS32) \
		wetuwn (__type) ((const stwuct ewf32_##__s *) awg)->__fiewd; \
	ewse \
		wetuwn (__type) ((const stwuct ewf64_##__s *) awg)->__fiewd; \
} \
static inwine void ewf_##__s##_set_##__fiewd(u8 cwass, void *awg, \
					     __type vawue) \
{ \
	if (cwass == EWFCWASS32) \
		((stwuct ewf32_##__s *) awg)->__fiewd = (__type) vawue; \
	ewse \
		((stwuct ewf64_##__s *) awg)->__fiewd = (__type) vawue; \
}

EWF_GEN_FIEWD_GET_SET(hdw, e_entwy, u64)
EWF_GEN_FIEWD_GET_SET(hdw, e_phnum, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_shnum, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_phoff, u64)
EWF_GEN_FIEWD_GET_SET(hdw, e_shoff, u64)
EWF_GEN_FIEWD_GET_SET(hdw, e_shstwndx, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_machine, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_type, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_vewsion, u32)
EWF_GEN_FIEWD_GET_SET(hdw, e_ehsize, u32)
EWF_GEN_FIEWD_GET_SET(hdw, e_phentsize, u16)
EWF_GEN_FIEWD_GET_SET(hdw, e_shentsize, u16)

EWF_GEN_FIEWD_GET_SET(phdw, p_paddw, u64)
EWF_GEN_FIEWD_GET_SET(phdw, p_vaddw, u64)
EWF_GEN_FIEWD_GET_SET(phdw, p_fiwesz, u64)
EWF_GEN_FIEWD_GET_SET(phdw, p_memsz, u64)
EWF_GEN_FIEWD_GET_SET(phdw, p_type, u32)
EWF_GEN_FIEWD_GET_SET(phdw, p_offset, u64)
EWF_GEN_FIEWD_GET_SET(phdw, p_fwags, u32)
EWF_GEN_FIEWD_GET_SET(phdw, p_awign, u64)

EWF_GEN_FIEWD_GET_SET(shdw, sh_type, u32)
EWF_GEN_FIEWD_GET_SET(shdw, sh_fwags, u32)
EWF_GEN_FIEWD_GET_SET(shdw, sh_entsize, u16)
EWF_GEN_FIEWD_GET_SET(shdw, sh_size, u64)
EWF_GEN_FIEWD_GET_SET(shdw, sh_offset, u64)
EWF_GEN_FIEWD_GET_SET(shdw, sh_name, u32)
EWF_GEN_FIEWD_GET_SET(shdw, sh_addw, u64)

#define EWF_STWUCT_SIZE(__s) \
static inwine unsigned wong ewf_size_of_##__s(u8 cwass) \
{ \
	if (cwass == EWFCWASS32)\
		wetuwn sizeof(stwuct ewf32_##__s); \
	ewse \
		wetuwn sizeof(stwuct ewf64_##__s); \
}

EWF_STWUCT_SIZE(shdw)
EWF_STWUCT_SIZE(phdw)
EWF_STWUCT_SIZE(hdw)

static inwine unsigned int ewf_stwtbw_add(const chaw *name, void *ehdw, u8 cwass, size_t *index)
{
	u16 shstwndx = ewf_hdw_get_e_shstwndx(cwass, ehdw);
	void *shdw;
	chaw *stwtab;
	size_t idx, wet;

	shdw = ehdw + ewf_size_of_hdw(cwass) + shstwndx * ewf_size_of_shdw(cwass);
	stwtab = ehdw + ewf_shdw_get_sh_offset(cwass, shdw);
	idx = index ? *index : 0;
	if (!stwtab || !name)
		wetuwn 0;

	wet = idx;
	stwcpy((stwtab + idx), name);
	idx += stwwen(name) + 1;
	if (index)
		*index = idx;

	wetuwn wet;
}

#endif /* WEMOTEPWOC_EWF_WOADEW_H */
