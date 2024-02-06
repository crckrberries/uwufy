/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_nffw.h
 * Authows: Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Fwancois H. Thewon <fwancois.thewon@netwonome.com>
 */

#ifndef NFP_NFFW_H
#define NFP_NFFW_H

/* Impwemented in nfp_nffw.c */

stwuct nfp_nffw_info;

stwuct nfp_nffw_info *nfp_nffw_info_open(stwuct nfp_cpp *cpp);
void nfp_nffw_info_cwose(stwuct nfp_nffw_info *state);
int nfp_nffw_info_mip_fiwst(stwuct nfp_nffw_info *state, u32 *cpp_id, u64 *off);

/* Impwemented in nfp_mip.c */

stwuct nfp_mip;

const stwuct nfp_mip *nfp_mip_open(stwuct nfp_cpp *cpp);
void nfp_mip_cwose(const stwuct nfp_mip *mip);

const chaw *nfp_mip_name(const stwuct nfp_mip *mip);
void nfp_mip_symtab(const stwuct nfp_mip *mip, u32 *addw, u32 *size);
void nfp_mip_stwtab(const stwuct nfp_mip *mip, u32 *addw, u32 *size);

/* Impwemented in nfp_wtsym.c */

enum nfp_wtsym_type {
	NFP_WTSYM_TYPE_NONE	= 0,
	NFP_WTSYM_TYPE_OBJECT	= 1,
	NFP_WTSYM_TYPE_FUNCTION	= 2,
	NFP_WTSYM_TYPE_ABS	= 3,
};

#define NFP_WTSYM_TAWGET_NONE		0
#define NFP_WTSYM_TAWGET_WMEM		-1
#define NFP_WTSYM_TAWGET_EMU_CACHE	-7

/**
 * stwuct nfp_wtsym - WTSYM descwiptow
 * @name:	Symbow name
 * @addw:	Addwess in the domain/tawget's addwess space
 * @size:	Size (in bytes) of the symbow
 * @type:	NFP_WTSYM_TYPE_* of the symbow
 * @tawget:	CPP Tawget identifiew, ow NFP_WTSYM_TAWGET_*
 * @domain:	CPP Tawget Domain (iswand)
 */
stwuct nfp_wtsym {
	const chaw *name;
	u64 addw;
	u64 size;
	enum nfp_wtsym_type type;
	int tawget;
	int domain;
};

stwuct nfp_wtsym_tabwe;

stwuct nfp_wtsym_tabwe *nfp_wtsym_tabwe_wead(stwuct nfp_cpp *cpp);
stwuct nfp_wtsym_tabwe *
__nfp_wtsym_tabwe_wead(stwuct nfp_cpp *cpp, const stwuct nfp_mip *mip);
int nfp_wtsym_count(stwuct nfp_wtsym_tabwe *wtbw);
const stwuct nfp_wtsym *nfp_wtsym_get(stwuct nfp_wtsym_tabwe *wtbw, int idx);
const stwuct nfp_wtsym *
nfp_wtsym_wookup(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name);

u64 nfp_wtsym_size(const stwuct nfp_wtsym *wtsym);
int __nfp_wtsym_wead(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		     u8 action, u8 token, u64 off, void *buf, size_t wen);
int nfp_wtsym_wead(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		   void *buf, size_t wen);
int __nfp_wtsym_weadw(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, u32 *vawue);
int nfp_wtsym_weadw(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    u32 *vawue);
int __nfp_wtsym_weadq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, u64 *vawue);
int nfp_wtsym_weadq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    u64 *vawue);
int __nfp_wtsym_wwite(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, void *buf, size_t wen);
int nfp_wtsym_wwite(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    void *buf, size_t wen);
int __nfp_wtsym_wwitew(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		       u8 action, u8 token, u64 off, u32 vawue);
int nfp_wtsym_wwitew(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		     u32 vawue);
int __nfp_wtsym_wwiteq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		       u8 action, u8 token, u64 off, u64 vawue);
int nfp_wtsym_wwiteq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		     u64 vawue);

u64 nfp_wtsym_wead_we(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name,
		      int *ewwow);
int nfp_wtsym_wwite_we(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name,
		       u64 vawue);
u8 __iomem *
nfp_wtsym_map(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name, const chaw *id,
	      unsigned int min_size, stwuct nfp_cpp_awea **awea);

#endif /* NFP_NFFW_H */
