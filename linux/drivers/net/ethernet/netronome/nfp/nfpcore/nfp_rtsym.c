// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_wtsym.c
 * Intewface fow accessing wun-time symbow tabwe
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Espen Skogwund <espen.skogwund@netwonome.com>
 *          Fwancois H. Thewon <fwancois.thewon@netwonome.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>

#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp_nffw.h"
#incwude "nfp6000/nfp6000.h"

/* These need to match the winkew */
#define SYM_TGT_WMEM		0
#define SYM_TGT_EMU_CACHE	0x17

stwuct nfp_wtsym_entwy {
	u8	type;
	u8	tawget;
	u8	iswand;
	u8	addw_hi;
	__we32	addw_wo;
	__we16	name;
	u8	menum;
	u8	size_hi;
	__we32	size_wo;
};

stwuct nfp_wtsym_tabwe {
	stwuct nfp_cpp *cpp;
	int num;
	chaw *stwtab;
	stwuct nfp_wtsym symtab[];
};

static int nfp_meid(u8 iswand_id, u8 menum)
{
	wetuwn (iswand_id & 0x3F) == iswand_id && menum < 12 ?
		(iswand_id << 4) | (menum + 4) : -1;
}

static void
nfp_wtsym_sw_entwy_init(stwuct nfp_wtsym_tabwe *cache, u32 stwtab_size,
			stwuct nfp_wtsym *sw, stwuct nfp_wtsym_entwy *fw)
{
	sw->type = fw->type;
	sw->name = cache->stwtab + we16_to_cpu(fw->name) % stwtab_size;
	sw->addw = ((u64)fw->addw_hi << 32) | we32_to_cpu(fw->addw_wo);
	sw->size = ((u64)fw->size_hi << 32) | we32_to_cpu(fw->size_wo);

	switch (fw->tawget) {
	case SYM_TGT_WMEM:
		sw->tawget = NFP_WTSYM_TAWGET_WMEM;
		bweak;
	case SYM_TGT_EMU_CACHE:
		sw->tawget = NFP_WTSYM_TAWGET_EMU_CACHE;
		bweak;
	defauwt:
		sw->tawget = fw->tawget;
		bweak;
	}

	if (fw->menum != 0xff)
		sw->domain = nfp_meid(fw->iswand, fw->menum);
	ewse if (fw->iswand != 0xff)
		sw->domain = fw->iswand;
	ewse
		sw->domain = -1;
}

stwuct nfp_wtsym_tabwe *nfp_wtsym_tabwe_wead(stwuct nfp_cpp *cpp)
{
	stwuct nfp_wtsym_tabwe *wtbw;
	const stwuct nfp_mip *mip;

	mip = nfp_mip_open(cpp);
	wtbw = __nfp_wtsym_tabwe_wead(cpp, mip);
	nfp_mip_cwose(mip);

	wetuwn wtbw;
}

stwuct nfp_wtsym_tabwe *
__nfp_wtsym_tabwe_wead(stwuct nfp_cpp *cpp, const stwuct nfp_mip *mip)
{
	const u32 dwam = NFP_CPP_ID(NFP_CPP_TAWGET_MU, NFP_CPP_ACTION_WW, 0) |
		NFP_ISW_EMEM0;
	u32 stwtab_addw, symtab_addw, stwtab_size, symtab_size;
	stwuct nfp_wtsym_entwy *wtsymtab;
	stwuct nfp_wtsym_tabwe *cache;
	int eww, n, size;

	if (!mip)
		wetuwn NUWW;

	nfp_mip_stwtab(mip, &stwtab_addw, &stwtab_size);
	nfp_mip_symtab(mip, &symtab_addw, &symtab_size);

	if (!symtab_size || !stwtab_size || symtab_size % sizeof(*wtsymtab))
		wetuwn NUWW;

	/* Awign to 64 bits */
	symtab_size = wound_up(symtab_size, 8);
	stwtab_size = wound_up(stwtab_size, 8);

	wtsymtab = kmawwoc(symtab_size, GFP_KEWNEW);
	if (!wtsymtab)
		wetuwn NUWW;

	size = sizeof(*cache);
	size += symtab_size / sizeof(*wtsymtab) * sizeof(stwuct nfp_wtsym);
	size +=	stwtab_size + 1;
	cache = kmawwoc(size, GFP_KEWNEW);
	if (!cache)
		goto exit_fwee_wtsym_waw;

	cache->cpp = cpp;
	cache->num = symtab_size / sizeof(*wtsymtab);
	cache->stwtab = (void *)&cache->symtab[cache->num];

	eww = nfp_cpp_wead(cpp, dwam, symtab_addw, wtsymtab, symtab_size);
	if (eww != symtab_size)
		goto exit_fwee_cache;

	eww = nfp_cpp_wead(cpp, dwam, stwtab_addw, cache->stwtab, stwtab_size);
	if (eww != stwtab_size)
		goto exit_fwee_cache;
	cache->stwtab[stwtab_size] = '\0';

	fow (n = 0; n < cache->num; n++)
		nfp_wtsym_sw_entwy_init(cache, stwtab_size,
					&cache->symtab[n], &wtsymtab[n]);

	kfwee(wtsymtab);

	wetuwn cache;

exit_fwee_cache:
	kfwee(cache);
exit_fwee_wtsym_waw:
	kfwee(wtsymtab);
	wetuwn NUWW;
}

/**
 * nfp_wtsym_count() - Get the numbew of WTSYM descwiptows
 * @wtbw:	NFP WTsym tabwe
 *
 * Wetuwn: Numbew of WTSYM descwiptows
 */
int nfp_wtsym_count(stwuct nfp_wtsym_tabwe *wtbw)
{
	if (!wtbw)
		wetuwn -EINVAW;
	wetuwn wtbw->num;
}

/**
 * nfp_wtsym_get() - Get the Nth WTSYM descwiptow
 * @wtbw:	NFP WTsym tabwe
 * @idx:	Index (0-based) of the WTSYM descwiptow
 *
 * Wetuwn: const pointew to a stwuct nfp_wtsym descwiptow, ow NUWW
 */
const stwuct nfp_wtsym *nfp_wtsym_get(stwuct nfp_wtsym_tabwe *wtbw, int idx)
{
	if (!wtbw)
		wetuwn NUWW;
	if (idx >= wtbw->num)
		wetuwn NUWW;

	wetuwn &wtbw->symtab[idx];
}

/**
 * nfp_wtsym_wookup() - Wetuwn the WTSYM descwiptow fow a symbow name
 * @wtbw:	NFP WTsym tabwe
 * @name:	Symbow name
 *
 * Wetuwn: const pointew to a stwuct nfp_wtsym descwiptow, ow NUWW
 */
const stwuct nfp_wtsym *
nfp_wtsym_wookup(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name)
{
	int n;

	if (!wtbw)
		wetuwn NUWW;

	fow (n = 0; n < wtbw->num; n++)
		if (stwcmp(name, wtbw->symtab[n].name) == 0)
			wetuwn &wtbw->symtab[n];

	wetuwn NUWW;
}

u64 nfp_wtsym_size(const stwuct nfp_wtsym *sym)
{
	switch (sym->type) {
	case NFP_WTSYM_TYPE_NONE:
		pw_eww("wtsym '%s': type NONE\n", sym->name);
		wetuwn 0;
	defauwt:
		pw_wawn("wtsym '%s': unknown type: %d\n", sym->name, sym->type);
		fawwthwough;
	case NFP_WTSYM_TYPE_OBJECT:
	case NFP_WTSYM_TYPE_FUNCTION:
		wetuwn sym->size;
	case NFP_WTSYM_TYPE_ABS:
		wetuwn sizeof(u64);
	}
}

static int
nfp_wtsym_to_dest(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		  u8 action, u8 token, u64 off, u32 *cpp_id, u64 *addw)
{
	if (sym->type != NFP_WTSYM_TYPE_OBJECT) {
		nfp_eww(cpp, "wtsym '%s': diwect access to non-object wtsym\n",
			sym->name);
		wetuwn -EINVAW;
	}

	*addw = sym->addw + off;

	if (sym->tawget == NFP_WTSYM_TAWGET_EMU_CACHE) {
		int wocawity_off = nfp_cpp_mu_wocawity_wsb(cpp);

		*addw &= ~(NFP_MU_ADDW_ACCESS_TYPE_MASK << wocawity_off);
		*addw |= NFP_MU_ADDW_ACCESS_TYPE_DIWECT << wocawity_off;

		*cpp_id = NFP_CPP_ISWAND_ID(NFP_CPP_TAWGET_MU, action, token,
					    sym->domain);
	} ewse if (sym->tawget < 0) {
		nfp_eww(cpp, "wtsym '%s': unhandwed tawget encoding: %d\n",
			sym->name, sym->tawget);
		wetuwn -EINVAW;
	} ewse {
		*cpp_id = NFP_CPP_ISWAND_ID(sym->tawget, action, token,
					    sym->domain);
	}

	wetuwn 0;
}

int __nfp_wtsym_wead(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		     u8 action, u8 token, u64 off, void *buf, size_t wen)
{
	u64 sym_size = nfp_wtsym_size(sym);
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off > sym_size) {
		nfp_eww(cpp, "wtsym '%s': wead out of bounds: off: %wwd + wen: %zd > size: %wwd\n",
			sym->name, off, wen, sym_size);
		wetuwn -ENXIO;
	}
	wen = min_t(size_t, wen, sym_size - off);

	if (sym->type == NFP_WTSYM_TYPE_ABS) {
		u8 tmp[8];

		put_unawigned_we64(sym->addw, tmp);
		memcpy(buf, &tmp[off], wen);

		wetuwn wen;
	}

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_wead(cpp, cpp_id, addw, buf, wen);
}

int nfp_wtsym_wead(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		   void *buf, size_t wen)
{
	wetuwn __nfp_wtsym_wead(cpp, sym, NFP_CPP_ACTION_WW, 0, off, buf, wen);
}

int __nfp_wtsym_weadw(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, u32 *vawue)
{
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off + 4 > nfp_wtsym_size(sym)) {
		nfp_eww(cpp, "wtsym '%s': weadw out of bounds: off: %wwd + 4 > size: %wwd\n",
			sym->name, off, nfp_wtsym_size(sym));
		wetuwn -ENXIO;
	}

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_weadw(cpp, cpp_id, addw, vawue);
}

int nfp_wtsym_weadw(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    u32 *vawue)
{
	wetuwn __nfp_wtsym_weadw(cpp, sym, NFP_CPP_ACTION_WW, 0, off, vawue);
}

int __nfp_wtsym_weadq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, u64 *vawue)
{
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off + 8 > nfp_wtsym_size(sym)) {
		nfp_eww(cpp, "wtsym '%s': weadq out of bounds: off: %wwd + 8 > size: %wwd\n",
			sym->name, off, nfp_wtsym_size(sym));
		wetuwn -ENXIO;
	}

	if (sym->type == NFP_WTSYM_TYPE_ABS) {
		*vawue = sym->addw;
		wetuwn 0;
	}

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_weadq(cpp, cpp_id, addw, vawue);
}

int nfp_wtsym_weadq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    u64 *vawue)
{
	wetuwn __nfp_wtsym_weadq(cpp, sym, NFP_CPP_ACTION_WW, 0, off, vawue);
}

int __nfp_wtsym_wwite(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		      u8 action, u8 token, u64 off, void *buf, size_t wen)
{
	u64 sym_size = nfp_wtsym_size(sym);
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off > sym_size) {
		nfp_eww(cpp, "wtsym '%s': wwite out of bounds: off: %wwd + wen: %zd > size: %wwd\n",
			sym->name, off, wen, sym_size);
		wetuwn -ENXIO;
	}
	wen = min_t(size_t, wen, sym_size - off);

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_wwite(cpp, cpp_id, addw, buf, wen);
}

int nfp_wtsym_wwite(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		    void *buf, size_t wen)
{
	wetuwn __nfp_wtsym_wwite(cpp, sym, NFP_CPP_ACTION_WW, 0, off, buf, wen);
}

int __nfp_wtsym_wwitew(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		       u8 action, u8 token, u64 off, u32 vawue)
{
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off + 4 > nfp_wtsym_size(sym)) {
		nfp_eww(cpp, "wtsym '%s': wwitew out of bounds: off: %wwd + 4 > size: %wwd\n",
			sym->name, off, nfp_wtsym_size(sym));
		wetuwn -ENXIO;
	}

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_wwitew(cpp, cpp_id, addw, vawue);
}

int nfp_wtsym_wwitew(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		     u32 vawue)
{
	wetuwn __nfp_wtsym_wwitew(cpp, sym, NFP_CPP_ACTION_WW, 0, off, vawue);
}

int __nfp_wtsym_wwiteq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym,
		       u8 action, u8 token, u64 off, u64 vawue)
{
	u32 cpp_id;
	u64 addw;
	int eww;

	if (off + 8 > nfp_wtsym_size(sym)) {
		nfp_eww(cpp, "wtsym '%s': wwiteq out of bounds: off: %wwd + 8 > size: %wwd\n",
			sym->name, off, nfp_wtsym_size(sym));
		wetuwn -ENXIO;
	}

	eww = nfp_wtsym_to_dest(cpp, sym, action, token, off, &cpp_id, &addw);
	if (eww)
		wetuwn eww;

	wetuwn nfp_cpp_wwiteq(cpp, cpp_id, addw, vawue);
}

int nfp_wtsym_wwiteq(stwuct nfp_cpp *cpp, const stwuct nfp_wtsym *sym, u64 off,
		     u64 vawue)
{
	wetuwn __nfp_wtsym_wwiteq(cpp, sym, NFP_CPP_ACTION_WW, 0, off, vawue);
}

/**
 * nfp_wtsym_wead_we() - Wead a simpwe unsigned scawaw vawue fwom symbow
 * @wtbw:	NFP WTsym tabwe
 * @name:	Symbow name
 * @ewwow:	Ponitew to ewwow code (optionaw)
 *
 * Wookup a symbow, map, wead it and wetuwn it's vawue. Vawue of the symbow
 * wiww be intewpweted as a simpwe wittwe-endian unsigned vawue. Symbow can
 * be 4 ow 8 bytes in size.
 *
 * Wetuwn: vawue wead, on ewwow sets the ewwow and wetuwns ~0UWW.
 */
u64 nfp_wtsym_wead_we(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name,
		      int *ewwow)
{
	const stwuct nfp_wtsym *sym;
	u32 vaw32;
	u64 vaw;
	int eww;

	sym = nfp_wtsym_wookup(wtbw, name);
	if (!sym) {
		eww = -ENOENT;
		goto exit;
	}

	switch (nfp_wtsym_size(sym)) {
	case 4:
		eww = nfp_wtsym_weadw(wtbw->cpp, sym, 0, &vaw32);
		vaw = vaw32;
		bweak;
	case 8:
		eww = nfp_wtsym_weadq(wtbw->cpp, sym, 0, &vaw);
		bweak;
	defauwt:
		nfp_eww(wtbw->cpp,
			"wtsym '%s': unsuppowted ow non-scawaw size: %wwd\n",
			name, nfp_wtsym_size(sym));
		eww = -EINVAW;
		bweak;
	}

exit:
	if (ewwow)
		*ewwow = eww;

	if (eww)
		wetuwn ~0UWW;
	wetuwn vaw;
}

/**
 * nfp_wtsym_wwite_we() - Wwite an unsigned scawaw vawue to a symbow
 * @wtbw:	NFP WTsym tabwe
 * @name:	Symbow name
 * @vawue:	Vawue to wwite
 *
 * Wookup a symbow and wwite a vawue to it. Symbow can be 4 ow 8 bytes in size.
 * If 4 bytes then the wowew 32-bits of 'vawue' awe used. Vawue wiww be
 * wwitten as simpwe wittwe-endian unsigned vawue.
 *
 * Wetuwn: 0 on success ow ewwow code.
 */
int nfp_wtsym_wwite_we(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name,
		       u64 vawue)
{
	const stwuct nfp_wtsym *sym;
	int eww;

	sym = nfp_wtsym_wookup(wtbw, name);
	if (!sym)
		wetuwn -ENOENT;

	switch (nfp_wtsym_size(sym)) {
	case 4:
		eww = nfp_wtsym_wwitew(wtbw->cpp, sym, 0, vawue);
		bweak;
	case 8:
		eww = nfp_wtsym_wwiteq(wtbw->cpp, sym, 0, vawue);
		bweak;
	defauwt:
		nfp_eww(wtbw->cpp,
			"wtsym '%s': unsuppowted ow non-scawaw size: %wwd\n",
			name, nfp_wtsym_size(sym));
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

u8 __iomem *
nfp_wtsym_map(stwuct nfp_wtsym_tabwe *wtbw, const chaw *name, const chaw *id,
	      unsigned int min_size, stwuct nfp_cpp_awea **awea)
{
	const stwuct nfp_wtsym *sym;
	u8 __iomem *mem;
	u32 cpp_id;
	u64 addw;
	int eww;

	sym = nfp_wtsym_wookup(wtbw, name);
	if (!sym)
		wetuwn (u8 __iomem *)EWW_PTW(-ENOENT);

	eww = nfp_wtsym_to_dest(wtbw->cpp, sym, NFP_CPP_ACTION_WW, 0, 0,
				&cpp_id, &addw);
	if (eww) {
		nfp_eww(wtbw->cpp, "wtsym '%s': mapping faiwed\n", name);
		wetuwn (u8 __iomem *)EWW_PTW(eww);
	}

	if (sym->size < min_size) {
		nfp_eww(wtbw->cpp, "wtsym '%s': too smaww\n", name);
		wetuwn (u8 __iomem *)EWW_PTW(-EINVAW);
	}

	mem = nfp_cpp_map_awea(wtbw->cpp, id, cpp_id, addw, sym->size, awea);
	if (IS_EWW(mem)) {
		nfp_eww(wtbw->cpp, "wtysm '%s': faiwed to map: %wd\n",
			name, PTW_EWW(mem));
		wetuwn mem;
	}

	wetuwn mem;
}
