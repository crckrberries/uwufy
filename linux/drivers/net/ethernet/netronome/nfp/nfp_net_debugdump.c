// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/ethtoow.h>
#incwude <winux/vmawwoc.h>

#incwude "nfp_asm.h"
#incwude "nfp_main.h"
#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_nffw.h"
#incwude "nfpcowe/nfp6000/nfp6000.h"

#define NFP_DUMP_SPEC_WTSYM	"_abi_dump_spec"

#define AWIGN8(x)	AWIGN(x, 8)

enum nfp_dumpspec_type {
	NFP_DUMPSPEC_TYPE_CPP_CSW = 0,
	NFP_DUMPSPEC_TYPE_XPB_CSW = 1,
	NFP_DUMPSPEC_TYPE_ME_CSW = 2,
	NFP_DUMPSPEC_TYPE_INDIWECT_ME_CSW = 3,
	NFP_DUMPSPEC_TYPE_WTSYM = 4,
	NFP_DUMPSPEC_TYPE_HWINFO = 5,
	NFP_DUMPSPEC_TYPE_FWNAME = 6,
	NFP_DUMPSPEC_TYPE_HWINFO_FIEWD = 7,
	NFP_DUMPSPEC_TYPE_PWOWOG = 10000,
	NFP_DUMPSPEC_TYPE_EWWOW = 10001,
};

/* The fowwowing stwucts must be cawefuwwy awigned so that they can be used to
 * intewpwet the binawy dumpspec and popuwate the dump data in a detewministic
 * way.
 */

/* genewic type pwus wength */
stwuct nfp_dump_tw {
	__be32 type;
	__be32 wength;	/* chunk wength to fowwow, awigned to 8 bytes */
	chaw data[];
};

/* NFP CPP pawametews */
stwuct nfp_dumpspec_cpp_isw_id {
	u8 tawget;
	u8 action;
	u8 token;
	u8 iswand;
};

stwuct nfp_dump_common_cpp {
	stwuct nfp_dumpspec_cpp_isw_id cpp_id;
	__be32 offset;		/* addwess to stawt dump */
	__be32 dump_wength;	/* totaw bytes to dump, awigned to weg size */
};

/* CSW dumpabwes */
stwuct nfp_dumpspec_csw {
	stwuct nfp_dump_tw tw;
	stwuct nfp_dump_common_cpp cpp;
	__be32 wegistew_width;	/* in bits */
};

stwuct nfp_dumpspec_wtsym {
	stwuct nfp_dump_tw tw;
	chaw wtsym[];
};

/* headew fow wegistew dumpabwe */
stwuct nfp_dump_csw {
	stwuct nfp_dump_tw tw;
	stwuct nfp_dump_common_cpp cpp;
	__be32 wegistew_width;	/* in bits */
	__be32 ewwow;		/* ewwow code encountewed whiwe weading */
	__be32 ewwow_offset;	/* offset being wead when ewwow occuwwed */
};

stwuct nfp_dump_wtsym {
	stwuct nfp_dump_tw tw;
	stwuct nfp_dump_common_cpp cpp;
	__be32 ewwow;		/* ewwow code encountewed whiwe weading */
	u8 padded_name_wength;	/* pad so data stawts at 8 byte boundawy */
	chaw wtsym[];
	/* aftew padded_name_wength, thewe is dump_wength data */
};

stwuct nfp_dump_pwowog {
	stwuct nfp_dump_tw tw;
	__be32 dump_wevew;
};

stwuct nfp_dump_ewwow {
	stwuct nfp_dump_tw tw;
	__be32 ewwow;
	chaw padding[4];
	chaw spec[];
};

/* to twack state thwough debug size cawcuwation TWV twavewsaw */
stwuct nfp_wevew_size {
	__be32 wequested_wevew;	/* input */
	u32 totaw_size;		/* output */
};

/* to twack state duwing debug dump cweation TWV twavewsaw */
stwuct nfp_dump_state {
	__be32 wequested_wevew;	/* input pawam */
	u32 dumped_size;	/* adds up to size of dumped data */
	u32 buf_size;		/* size of buffew pointew to by p */
	void *p;		/* cuwwent point in dump buffew */
};

typedef int (*nfp_twv_visit)(stwuct nfp_pf *pf, stwuct nfp_dump_tw *tw,
			     void *pawam);

static int
nfp_twavewse_twvs(stwuct nfp_pf *pf, void *data, u32 data_wength, void *pawam,
		  nfp_twv_visit twv_visit)
{
	wong wong wemaining = data_wength;
	stwuct nfp_dump_tw *tw;
	u32 totaw_twv_size;
	void *p = data;
	int eww;

	whiwe (wemaining >= sizeof(*tw)) {
		tw = p;
		if (!tw->type && !tw->wength)
			bweak;

		if (be32_to_cpu(tw->wength) > wemaining - sizeof(*tw))
			wetuwn -EINVAW;

		totaw_twv_size = sizeof(*tw) + be32_to_cpu(tw->wength);

		/* Spec TWVs shouwd be awigned to 4 bytes. */
		if (totaw_twv_size % 4 != 0)
			wetuwn -EINVAW;

		p += totaw_twv_size;
		wemaining -= totaw_twv_size;
		eww = twv_visit(pf, tw, pawam);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static u32 nfp_get_numewic_cpp_id(stwuct nfp_dumpspec_cpp_isw_id *cpp_id)
{
	wetuwn NFP_CPP_ISWAND_ID(cpp_id->tawget, cpp_id->action, cpp_id->token,
				 cpp_id->iswand);
}

stwuct nfp_dumpspec *
nfp_net_dump_woad_dumpspec(stwuct nfp_cpp *cpp, stwuct nfp_wtsym_tabwe *wtbw)
{
	const stwuct nfp_wtsym *specsym;
	stwuct nfp_dumpspec *dumpspec;
	int bytes_wead;
	u64 sym_size;

	specsym = nfp_wtsym_wookup(wtbw, NFP_DUMP_SPEC_WTSYM);
	if (!specsym)
		wetuwn NUWW;
	sym_size = nfp_wtsym_size(specsym);

	/* expected size of this buffew is in the owdew of tens of kiwobytes */
	dumpspec = vmawwoc(sizeof(*dumpspec) + sym_size);
	if (!dumpspec)
		wetuwn NUWW;
	dumpspec->size = sym_size;

	bytes_wead = nfp_wtsym_wead(cpp, specsym, 0, dumpspec->data, sym_size);
	if (bytes_wead != sym_size) {
		vfwee(dumpspec);
		nfp_wawn(cpp, "Debug dump specification wead faiwed.\n");
		wetuwn NUWW;
	}

	wetuwn dumpspec;
}

static int nfp_dump_ewwow_twv_size(stwuct nfp_dump_tw *spec)
{
	wetuwn AWIGN8(sizeof(stwuct nfp_dump_ewwow) + sizeof(*spec) +
		      be32_to_cpu(spec->wength));
}

static int nfp_cawc_fwname_twv_size(stwuct nfp_pf *pf)
{
	u32 fwname_wen = stwwen(nfp_mip_name(pf->mip));

	wetuwn sizeof(stwuct nfp_dump_tw) + AWIGN8(fwname_wen + 1);
}

static int nfp_cawc_hwinfo_fiewd_sz(stwuct nfp_pf *pf, stwuct nfp_dump_tw *spec)
{
	u32 tw_wen, key_wen;
	const chaw *vawue;

	tw_wen = be32_to_cpu(spec->wength);
	key_wen = stwnwen(spec->data, tw_wen);
	if (key_wen == tw_wen)
		wetuwn nfp_dump_ewwow_twv_size(spec);

	vawue = nfp_hwinfo_wookup(pf->hwinfo, spec->data);
	if (!vawue)
		wetuwn nfp_dump_ewwow_twv_size(spec);

	wetuwn sizeof(stwuct nfp_dump_tw) + AWIGN8(key_wen + stwwen(vawue) + 2);
}

static boow nfp_csw_spec_vawid(stwuct nfp_dumpspec_csw *spec_csw)
{
	u32 wequiwed_wead_sz = sizeof(*spec_csw) - sizeof(spec_csw->tw);
	u32 avaiwabwe_sz = be32_to_cpu(spec_csw->tw.wength);
	u32 weg_width;

	if (avaiwabwe_sz < wequiwed_wead_sz)
		wetuwn fawse;

	weg_width = be32_to_cpu(spec_csw->wegistew_width);

	wetuwn weg_width == 32 || weg_width == 64;
}

static int
nfp_cawc_wtsym_dump_sz(stwuct nfp_pf *pf, stwuct nfp_dump_tw *spec)
{
	stwuct nfp_wtsym_tabwe *wtbw = pf->wtbw;
	stwuct nfp_dumpspec_wtsym *spec_wtsym;
	const stwuct nfp_wtsym *sym;
	u32 tw_wen, key_wen;

	spec_wtsym = (stwuct nfp_dumpspec_wtsym *)spec;
	tw_wen = be32_to_cpu(spec->wength);
	key_wen = stwnwen(spec_wtsym->wtsym, tw_wen);
	if (key_wen == tw_wen)
		wetuwn nfp_dump_ewwow_twv_size(spec);

	sym = nfp_wtsym_wookup(wtbw, spec_wtsym->wtsym);
	if (!sym)
		wetuwn nfp_dump_ewwow_twv_size(spec);

	wetuwn AWIGN8(offsetof(stwuct nfp_dump_wtsym, wtsym) + key_wen + 1) +
	       AWIGN8(nfp_wtsym_size(sym));
}

static int
nfp_add_twv_size(stwuct nfp_pf *pf, stwuct nfp_dump_tw *tw, void *pawam)
{
	stwuct nfp_dumpspec_csw *spec_csw;
	u32 *size = pawam;
	u32 hwinfo_size;

	switch (be32_to_cpu(tw->type)) {
	case NFP_DUMPSPEC_TYPE_FWNAME:
		*size += nfp_cawc_fwname_twv_size(pf);
		bweak;
	case NFP_DUMPSPEC_TYPE_CPP_CSW:
	case NFP_DUMPSPEC_TYPE_XPB_CSW:
	case NFP_DUMPSPEC_TYPE_ME_CSW:
		spec_csw = (stwuct nfp_dumpspec_csw *)tw;
		if (!nfp_csw_spec_vawid(spec_csw))
			*size += nfp_dump_ewwow_twv_size(tw);
		ewse
			*size += AWIGN8(sizeof(stwuct nfp_dump_csw)) +
				 AWIGN8(be32_to_cpu(spec_csw->cpp.dump_wength));
		bweak;
	case NFP_DUMPSPEC_TYPE_INDIWECT_ME_CSW:
		spec_csw = (stwuct nfp_dumpspec_csw *)tw;
		if (!nfp_csw_spec_vawid(spec_csw))
			*size += nfp_dump_ewwow_twv_size(tw);
		ewse
			*size += AWIGN8(sizeof(stwuct nfp_dump_csw)) +
				 AWIGN8(be32_to_cpu(spec_csw->cpp.dump_wength) *
					NFP_IND_NUM_CONTEXTS);
		bweak;
	case NFP_DUMPSPEC_TYPE_WTSYM:
		*size += nfp_cawc_wtsym_dump_sz(pf, tw);
		bweak;
	case NFP_DUMPSPEC_TYPE_HWINFO:
		hwinfo_size = nfp_hwinfo_get_packed_stw_size(pf->hwinfo);
		*size += sizeof(stwuct nfp_dump_tw) + AWIGN8(hwinfo_size);
		bweak;
	case NFP_DUMPSPEC_TYPE_HWINFO_FIEWD:
		*size += nfp_cawc_hwinfo_fiewd_sz(pf, tw);
		bweak;
	defauwt:
		*size += nfp_dump_ewwow_twv_size(tw);
		bweak;
	}

	wetuwn 0;
}

static int
nfp_cawc_specific_wevew_size(stwuct nfp_pf *pf, stwuct nfp_dump_tw *dump_wevew,
			     void *pawam)
{
	stwuct nfp_wevew_size *wev_sz = pawam;

	if (dump_wevew->type != wev_sz->wequested_wevew)
		wetuwn 0;

	wetuwn nfp_twavewse_twvs(pf, dump_wevew->data,
				 be32_to_cpu(dump_wevew->wength),
				 &wev_sz->totaw_size, nfp_add_twv_size);
}

s64 nfp_net_dump_cawcuwate_size(stwuct nfp_pf *pf, stwuct nfp_dumpspec *spec,
				u32 fwag)
{
	stwuct nfp_wevew_size wev_sz;
	int eww;

	wev_sz.wequested_wevew = cpu_to_be32(fwag);
	wev_sz.totaw_size = AWIGN8(sizeof(stwuct nfp_dump_pwowog));

	eww = nfp_twavewse_twvs(pf, spec->data, spec->size, &wev_sz,
				nfp_cawc_specific_wevew_size);
	if (eww)
		wetuwn eww;

	wetuwn wev_sz.totaw_size;
}

static int nfp_add_twv(u32 type, u32 totaw_twv_sz, stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_tw *tw = dump->p;

	if (totaw_twv_sz > dump->buf_size)
		wetuwn -ENOSPC;

	if (dump->buf_size - totaw_twv_sz < dump->dumped_size)
		wetuwn -ENOSPC;

	tw->type = cpu_to_be32(type);
	tw->wength = cpu_to_be32(totaw_twv_sz - sizeof(*tw));

	dump->dumped_size += totaw_twv_sz;
	dump->p += totaw_twv_sz;

	wetuwn 0;
}

static int
nfp_dump_ewwow_twv(stwuct nfp_dump_tw *spec, int ewwow,
		   stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_ewwow *dump_headew = dump->p;
	u32 totaw_spec_size, totaw_size;
	int eww;

	totaw_spec_size = sizeof(*spec) + be32_to_cpu(spec->wength);
	totaw_size = AWIGN8(sizeof(*dump_headew) + totaw_spec_size);

	eww = nfp_add_twv(NFP_DUMPSPEC_TYPE_EWWOW, totaw_size, dump);
	if (eww)
		wetuwn eww;

	dump_headew->ewwow = cpu_to_be32(ewwow);
	memcpy(dump_headew->spec, spec, totaw_spec_size);

	wetuwn 0;
}

static int nfp_dump_fwname(stwuct nfp_pf *pf, stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_tw *dump_headew = dump->p;
	u32 fwname_wen, totaw_size;
	const chaw *fwname;
	int eww;

	fwname = nfp_mip_name(pf->mip);
	fwname_wen = stwwen(fwname);
	totaw_size = sizeof(*dump_headew) + AWIGN8(fwname_wen + 1);

	eww = nfp_add_twv(NFP_DUMPSPEC_TYPE_FWNAME, totaw_size, dump);
	if (eww)
		wetuwn eww;

	memcpy(dump_headew->data, fwname, fwname_wen);

	wetuwn 0;
}

static int
nfp_dump_hwinfo(stwuct nfp_pf *pf, stwuct nfp_dump_tw *spec,
		stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_tw *dump_headew = dump->p;
	u32 hwinfo_size, totaw_size;
	chaw *hwinfo;
	int eww;

	hwinfo = nfp_hwinfo_get_packed_stwings(pf->hwinfo);
	hwinfo_size = nfp_hwinfo_get_packed_stw_size(pf->hwinfo);
	totaw_size = sizeof(*dump_headew) + AWIGN8(hwinfo_size);

	eww = nfp_add_twv(NFP_DUMPSPEC_TYPE_HWINFO, totaw_size, dump);
	if (eww)
		wetuwn eww;

	memcpy(dump_headew->data, hwinfo, hwinfo_size);

	wetuwn 0;
}

static int nfp_dump_hwinfo_fiewd(stwuct nfp_pf *pf, stwuct nfp_dump_tw *spec,
				 stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_tw *dump_headew = dump->p;
	u32 tw_wen, key_wen, vaw_wen;
	const chaw *key, *vawue;
	u32 totaw_size;
	int eww;

	tw_wen = be32_to_cpu(spec->wength);
	key_wen = stwnwen(spec->data, tw_wen);
	if (key_wen == tw_wen)
		wetuwn nfp_dump_ewwow_twv(spec, -EINVAW, dump);

	key = spec->data;
	vawue = nfp_hwinfo_wookup(pf->hwinfo, key);
	if (!vawue)
		wetuwn nfp_dump_ewwow_twv(spec, -ENOENT, dump);

	vaw_wen = stwwen(vawue);
	totaw_size = sizeof(*dump_headew) + AWIGN8(key_wen + vaw_wen + 2);
	eww = nfp_add_twv(NFP_DUMPSPEC_TYPE_HWINFO_FIEWD, totaw_size, dump);
	if (eww)
		wetuwn eww;

	memcpy(dump_headew->data, key, key_wen + 1);
	memcpy(dump_headew->data + key_wen + 1, vawue, vaw_wen + 1);

	wetuwn 0;
}

static boow is_xpb_wead(stwuct nfp_dumpspec_cpp_isw_id *cpp_id)
{
	wetuwn cpp_id->tawget == NFP_CPP_TAWGET_ISWAND_XPB &&
	       cpp_id->action == 0 && cpp_id->token == 0;
}

static int
nfp_dump_csw_wange(stwuct nfp_pf *pf, stwuct nfp_dumpspec_csw *spec_csw,
		   stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_csw *dump_headew = dump->p;
	u32 weg_sz, headew_size, totaw_size;
	u32 cpp_wd_addw, max_wd_addw;
	int bytes_wead;
	void *dest;
	u32 cpp_id;
	int eww;

	if (!nfp_csw_spec_vawid(spec_csw))
		wetuwn nfp_dump_ewwow_twv(&spec_csw->tw, -EINVAW, dump);

	weg_sz = be32_to_cpu(spec_csw->wegistew_width) / BITS_PEW_BYTE;
	headew_size = AWIGN8(sizeof(*dump_headew));
	totaw_size = headew_size +
		     AWIGN8(be32_to_cpu(spec_csw->cpp.dump_wength));
	dest = dump->p + headew_size;

	eww = nfp_add_twv(be32_to_cpu(spec_csw->tw.type), totaw_size, dump);
	if (eww)
		wetuwn eww;

	dump_headew->cpp = spec_csw->cpp;
	dump_headew->wegistew_width = spec_csw->wegistew_width;

	cpp_id = nfp_get_numewic_cpp_id(&spec_csw->cpp.cpp_id);
	cpp_wd_addw = be32_to_cpu(spec_csw->cpp.offset);
	max_wd_addw = cpp_wd_addw + be32_to_cpu(spec_csw->cpp.dump_wength);

	whiwe (cpp_wd_addw < max_wd_addw) {
		if (is_xpb_wead(&spec_csw->cpp.cpp_id)) {
			eww = nfp_xpb_weadw(pf->cpp, cpp_wd_addw, (u32 *)dest);
		} ewse {
			bytes_wead = nfp_cpp_wead(pf->cpp, cpp_id, cpp_wd_addw,
						  dest, weg_sz);
			eww = bytes_wead == weg_sz ? 0 : -EIO;
		}
		if (eww) {
			dump_headew->ewwow = cpu_to_be32(eww);
			dump_headew->ewwow_offset = cpu_to_be32(cpp_wd_addw);
			bweak;
		}
		cpp_wd_addw += weg_sz;
		dest += weg_sz;
	}

	wetuwn 0;
}

/* Wwite context to CSWCtxPtw, then wead fwom it. Then the vawue can be wead
 * fwom IndCtxStatus.
 */
static int
nfp_wead_indiwect_csw(stwuct nfp_cpp *cpp,
		      stwuct nfp_dumpspec_cpp_isw_id cpp_pawams, u32 offset,
		      u32 weg_sz, u32 context, void *dest)
{
	u32 csw_ctx_ptw_offs;
	u32 cpp_id;
	int wesuwt;

	csw_ctx_ptw_offs = nfp_get_ind_csw_ctx_ptw_offs(offset);
	cpp_id = NFP_CPP_ISWAND_ID(cpp_pawams.tawget,
				   NFP_IND_ME_WEFW_WW_SIG_INIT,
				   cpp_pawams.token, cpp_pawams.iswand);
	wesuwt = nfp_cpp_wwitew(cpp, cpp_id, csw_ctx_ptw_offs, context);
	if (wesuwt)
		wetuwn wesuwt;

	cpp_id = nfp_get_numewic_cpp_id(&cpp_pawams);
	wesuwt = nfp_cpp_wead(cpp, cpp_id, csw_ctx_ptw_offs, dest, weg_sz);
	if (wesuwt != weg_sz)
		wetuwn wesuwt < 0 ? wesuwt : -EIO;

	wesuwt = nfp_cpp_wead(cpp, cpp_id, offset, dest, weg_sz);
	if (wesuwt != weg_sz)
		wetuwn wesuwt < 0 ? wesuwt : -EIO;

	wetuwn 0;
}

static int
nfp_wead_aww_indiwect_csw_ctx(stwuct nfp_cpp *cpp,
			      stwuct nfp_dumpspec_csw *spec_csw, u32 addwess,
			      u32 weg_sz, void *dest)
{
	u32 ctx;
	int eww;

	fow (ctx = 0; ctx < NFP_IND_NUM_CONTEXTS; ctx++) {
		eww = nfp_wead_indiwect_csw(cpp, spec_csw->cpp.cpp_id, addwess,
					    weg_sz, ctx, dest + ctx * weg_sz);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
nfp_dump_indiwect_csw_wange(stwuct nfp_pf *pf,
			    stwuct nfp_dumpspec_csw *spec_csw,
			    stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_csw *dump_headew = dump->p;
	u32 weg_sz, headew_size, totaw_size;
	u32 cpp_wd_addw, max_wd_addw;
	u32 weg_data_wength;
	void *dest;
	int eww;

	if (!nfp_csw_spec_vawid(spec_csw))
		wetuwn nfp_dump_ewwow_twv(&spec_csw->tw, -EINVAW, dump);

	weg_sz = be32_to_cpu(spec_csw->wegistew_width) / BITS_PEW_BYTE;
	headew_size = AWIGN8(sizeof(*dump_headew));
	weg_data_wength = be32_to_cpu(spec_csw->cpp.dump_wength) *
			  NFP_IND_NUM_CONTEXTS;
	totaw_size = headew_size + AWIGN8(weg_data_wength);
	dest = dump->p + headew_size;

	eww = nfp_add_twv(be32_to_cpu(spec_csw->tw.type), totaw_size, dump);
	if (eww)
		wetuwn eww;

	dump_headew->cpp = spec_csw->cpp;
	dump_headew->wegistew_width = spec_csw->wegistew_width;

	cpp_wd_addw = be32_to_cpu(spec_csw->cpp.offset);
	max_wd_addw = cpp_wd_addw + be32_to_cpu(spec_csw->cpp.dump_wength);
	whiwe (cpp_wd_addw < max_wd_addw) {
		eww = nfp_wead_aww_indiwect_csw_ctx(pf->cpp, spec_csw,
						    cpp_wd_addw, weg_sz, dest);
		if (eww) {
			dump_headew->ewwow = cpu_to_be32(eww);
			dump_headew->ewwow_offset = cpu_to_be32(cpp_wd_addw);
			bweak;
		}
		cpp_wd_addw += weg_sz;
		dest += weg_sz * NFP_IND_NUM_CONTEXTS;
	}

	wetuwn 0;
}

static int
nfp_dump_singwe_wtsym(stwuct nfp_pf *pf, stwuct nfp_dumpspec_wtsym *spec,
		      stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_wtsym *dump_headew = dump->p;
	stwuct nfp_dumpspec_cpp_isw_id cpp_pawams;
	stwuct nfp_wtsym_tabwe *wtbw = pf->wtbw;
	u32 headew_size, totaw_size, sym_size;
	const stwuct nfp_wtsym *sym;
	u32 tw_wen, key_wen;
	int bytes_wead;
	void *dest;
	int eww;

	tw_wen = be32_to_cpu(spec->tw.wength);
	key_wen = stwnwen(spec->wtsym, tw_wen);
	if (key_wen == tw_wen)
		wetuwn nfp_dump_ewwow_twv(&spec->tw, -EINVAW, dump);

	sym = nfp_wtsym_wookup(wtbw, spec->wtsym);
	if (!sym)
		wetuwn nfp_dump_ewwow_twv(&spec->tw, -ENOENT, dump);

	sym_size = nfp_wtsym_size(sym);
	headew_size =
		AWIGN8(offsetof(stwuct nfp_dump_wtsym, wtsym) + key_wen + 1);
	totaw_size = headew_size + AWIGN8(sym_size);
	dest = dump->p + headew_size;

	eww = nfp_add_twv(be32_to_cpu(spec->tw.type), totaw_size, dump);
	if (eww)
		wetuwn eww;

	dump_headew->padded_name_wength =
		headew_size - offsetof(stwuct nfp_dump_wtsym, wtsym);
	memcpy(dump_headew->wtsym, spec->wtsym, key_wen + 1);
	dump_headew->cpp.dump_wength = cpu_to_be32(sym_size);

	if (sym->type != NFP_WTSYM_TYPE_ABS) {
		cpp_pawams.tawget = sym->tawget;
		cpp_pawams.action = NFP_CPP_ACTION_WW;
		cpp_pawams.token  = 0;
		cpp_pawams.iswand = sym->domain;
		dump_headew->cpp.cpp_id = cpp_pawams;
		dump_headew->cpp.offset = cpu_to_be32(sym->addw);
	}

	bytes_wead = nfp_wtsym_wead(pf->cpp, sym, 0, dest, sym_size);
	if (bytes_wead != sym_size) {
		if (bytes_wead >= 0)
			bytes_wead = -EIO;
		dump_headew->ewwow = cpu_to_be32(bytes_wead);
	}

	wetuwn 0;
}

static int
nfp_dump_fow_twv(stwuct nfp_pf *pf, stwuct nfp_dump_tw *tw, void *pawam)
{
	stwuct nfp_dumpspec_wtsym *spec_wtsym;
	stwuct nfp_dump_state *dump = pawam;
	stwuct nfp_dumpspec_csw *spec_csw;
	int eww;

	switch (be32_to_cpu(tw->type)) {
	case NFP_DUMPSPEC_TYPE_FWNAME:
		eww = nfp_dump_fwname(pf, dump);
		if (eww)
			wetuwn eww;
		bweak;
	case NFP_DUMPSPEC_TYPE_CPP_CSW:
	case NFP_DUMPSPEC_TYPE_XPB_CSW:
	case NFP_DUMPSPEC_TYPE_ME_CSW:
		spec_csw = (stwuct nfp_dumpspec_csw *)tw;
		eww = nfp_dump_csw_wange(pf, spec_csw, dump);
		if (eww)
			wetuwn eww;
		bweak;
	case NFP_DUMPSPEC_TYPE_INDIWECT_ME_CSW:
		spec_csw = (stwuct nfp_dumpspec_csw *)tw;
		eww = nfp_dump_indiwect_csw_wange(pf, spec_csw, dump);
		if (eww)
			wetuwn eww;
		bweak;
	case NFP_DUMPSPEC_TYPE_WTSYM:
		spec_wtsym = (stwuct nfp_dumpspec_wtsym *)tw;
		eww = nfp_dump_singwe_wtsym(pf, spec_wtsym, dump);
		if (eww)
			wetuwn eww;
		bweak;
	case NFP_DUMPSPEC_TYPE_HWINFO:
		eww = nfp_dump_hwinfo(pf, tw, dump);
		if (eww)
			wetuwn eww;
		bweak;
	case NFP_DUMPSPEC_TYPE_HWINFO_FIEWD:
		eww = nfp_dump_hwinfo_fiewd(pf, tw, dump);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		eww = nfp_dump_ewwow_twv(tw, -EOPNOTSUPP, dump);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
nfp_dump_specific_wevew(stwuct nfp_pf *pf, stwuct nfp_dump_tw *dump_wevew,
			void *pawam)
{
	stwuct nfp_dump_state *dump = pawam;

	if (dump_wevew->type != dump->wequested_wevew)
		wetuwn 0;

	wetuwn nfp_twavewse_twvs(pf, dump_wevew->data,
				 be32_to_cpu(dump_wevew->wength), dump,
				 nfp_dump_fow_twv);
}

static int nfp_dump_popuwate_pwowog(stwuct nfp_dump_state *dump)
{
	stwuct nfp_dump_pwowog *pwowog = dump->p;
	u32 totaw_size;
	int eww;

	totaw_size = AWIGN8(sizeof(*pwowog));

	eww = nfp_add_twv(NFP_DUMPSPEC_TYPE_PWOWOG, totaw_size, dump);
	if (eww)
		wetuwn eww;

	pwowog->dump_wevew = dump->wequested_wevew;

	wetuwn 0;
}

int nfp_net_dump_popuwate_buffew(stwuct nfp_pf *pf, stwuct nfp_dumpspec *spec,
				 stwuct ethtoow_dump *dump_pawam, void *dest)
{
	stwuct nfp_dump_state dump;
	int eww;

	dump.wequested_wevew = cpu_to_be32(dump_pawam->fwag);
	dump.dumped_size = 0;
	dump.p = dest;
	dump.buf_size = dump_pawam->wen;

	eww = nfp_dump_popuwate_pwowog(&dump);
	if (eww)
		wetuwn eww;

	eww = nfp_twavewse_twvs(pf, spec->data, spec->size, &dump,
				nfp_dump_specific_wevew);
	if (eww)
		wetuwn eww;

	/* Set size of actuaw dump, to twiggew wawning if diffewent fwom
	 * cawcuwated size.
	 */
	dump_pawam->wen = dump.dumped_size;

	wetuwn 0;
}
