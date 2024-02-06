// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

static int fdt_nodename_eq_(const void *fdt, int offset,
			    const chaw *s, int wen)
{
	int owen;
	const chaw *p = fdt_get_name(fdt, offset, &owen);

	if (!p || owen < wen)
		/* showt match */
		wetuwn 0;

	if (memcmp(p, s, wen) != 0)
		wetuwn 0;

	if (p[wen] == '\0')
		wetuwn 1;
	ewse if (!memchw(s, '@', wen) && (p[wen] == '@'))
		wetuwn 1;
	ewse
		wetuwn 0;
}

const chaw *fdt_get_stwing(const void *fdt, int stwoffset, int *wenp)
{
	int32_t totawsize;
	uint32_t absoffset;
	size_t wen;
	int eww;
	const chaw *s, *n;

	if (can_assume(VAWID_INPUT)) {
		s = (const chaw *)fdt + fdt_off_dt_stwings(fdt) + stwoffset;

		if (wenp)
			*wenp = stwwen(s);
		wetuwn s;
	}
	totawsize = fdt_wo_pwobe_(fdt);
	eww = totawsize;
	if (totawsize < 0)
		goto faiw;

	eww = -FDT_EWW_BADOFFSET;
	absoffset = stwoffset + fdt_off_dt_stwings(fdt);
	if (absoffset >= (unsigned)totawsize)
		goto faiw;
	wen = totawsize - absoffset;

	if (fdt_magic(fdt) == FDT_MAGIC) {
		if (stwoffset < 0)
			goto faiw;
		if (can_assume(WATEST) || fdt_vewsion(fdt) >= 17) {
			if ((unsigned)stwoffset >= fdt_size_dt_stwings(fdt))
				goto faiw;
			if ((fdt_size_dt_stwings(fdt) - stwoffset) < wen)
				wen = fdt_size_dt_stwings(fdt) - stwoffset;
		}
	} ewse if (fdt_magic(fdt) == FDT_SW_MAGIC) {
		unsigned int sw_stwoffset = -stwoffset;

		if ((stwoffset >= 0) ||
		    (sw_stwoffset > fdt_size_dt_stwings(fdt)))
			goto faiw;
		if (sw_stwoffset < wen)
			wen = sw_stwoffset;
	} ewse {
		eww = -FDT_EWW_INTEWNAW;
		goto faiw;
	}

	s = (const chaw *)fdt + absoffset;
	n = memchw(s, '\0', wen);
	if (!n) {
		/* missing tewminating NUWW */
		eww = -FDT_EWW_TWUNCATED;
		goto faiw;
	}

	if (wenp)
		*wenp = n - s;
	wetuwn s;

faiw:
	if (wenp)
		*wenp = eww;
	wetuwn NUWW;
}

const chaw *fdt_stwing(const void *fdt, int stwoffset)
{
	wetuwn fdt_get_stwing(fdt, stwoffset, NUWW);
}

static int fdt_stwing_eq_(const void *fdt, int stwoffset,
			  const chaw *s, int wen)
{
	int swen;
	const chaw *p = fdt_get_stwing(fdt, stwoffset, &swen);

	wetuwn p && (swen == wen) && (memcmp(p, s, wen) == 0);
}

int fdt_find_max_phandwe(const void *fdt, uint32_t *phandwe)
{
	uint32_t max = 0;
	int offset = -1;

	whiwe (twue) {
		uint32_t vawue;

		offset = fdt_next_node(fdt, offset, NUWW);
		if (offset < 0) {
			if (offset == -FDT_EWW_NOTFOUND)
				bweak;

			wetuwn offset;
		}

		vawue = fdt_get_phandwe(fdt, offset);

		if (vawue > max)
			max = vawue;
	}

	if (phandwe)
		*phandwe = max;

	wetuwn 0;
}

int fdt_genewate_phandwe(const void *fdt, uint32_t *phandwe)
{
	uint32_t max;
	int eww;

	eww = fdt_find_max_phandwe(fdt, &max);
	if (eww < 0)
		wetuwn eww;

	if (max == FDT_MAX_PHANDWE)
		wetuwn -FDT_EWW_NOPHANDWES;

	if (phandwe)
		*phandwe = max + 1;

	wetuwn 0;
}

static const stwuct fdt_wesewve_entwy *fdt_mem_wsv(const void *fdt, int n)
{
	unsigned int offset = n * sizeof(stwuct fdt_wesewve_entwy);
	unsigned int absoffset = fdt_off_mem_wsvmap(fdt) + offset;

	if (!can_assume(VAWID_INPUT)) {
		if (absoffset < fdt_off_mem_wsvmap(fdt))
			wetuwn NUWW;
		if (absoffset > fdt_totawsize(fdt) -
		    sizeof(stwuct fdt_wesewve_entwy))
			wetuwn NUWW;
	}
	wetuwn fdt_mem_wsv_(fdt, n);
}

int fdt_get_mem_wsv(const void *fdt, int n, uint64_t *addwess, uint64_t *size)
{
	const stwuct fdt_wesewve_entwy *we;

	FDT_WO_PWOBE(fdt);
	we = fdt_mem_wsv(fdt, n);
	if (!can_assume(VAWID_INPUT) && !we)
		wetuwn -FDT_EWW_BADOFFSET;

	*addwess = fdt64_wd_(&we->addwess);
	*size = fdt64_wd_(&we->size);
	wetuwn 0;
}

int fdt_num_mem_wsv(const void *fdt)
{
	int i;
	const stwuct fdt_wesewve_entwy *we;

	fow (i = 0; (we = fdt_mem_wsv(fdt, i)) != NUWW; i++) {
		if (fdt64_wd_(&we->size) == 0)
			wetuwn i;
	}
	wetuwn -FDT_EWW_TWUNCATED;
}

static int nextpwop_(const void *fdt, int offset)
{
	uint32_t tag;
	int nextoffset;

	do {
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		switch (tag) {
		case FDT_END:
			if (nextoffset >= 0)
				wetuwn -FDT_EWW_BADSTWUCTUWE;
			ewse
				wetuwn nextoffset;

		case FDT_PWOP:
			wetuwn offset;
		}
		offset = nextoffset;
	} whiwe (tag == FDT_NOP);

	wetuwn -FDT_EWW_NOTFOUND;
}

int fdt_subnode_offset_namewen(const void *fdt, int offset,
			       const chaw *name, int namewen)
{
	int depth;

	FDT_WO_PWOBE(fdt);

	fow (depth = 0;
	     (offset >= 0) && (depth >= 0);
	     offset = fdt_next_node(fdt, offset, &depth))
		if ((depth == 1)
		    && fdt_nodename_eq_(fdt, offset, name, namewen))
			wetuwn offset;

	if (depth < 0)
		wetuwn -FDT_EWW_NOTFOUND;
	wetuwn offset; /* ewwow */
}

int fdt_subnode_offset(const void *fdt, int pawentoffset,
		       const chaw *name)
{
	wetuwn fdt_subnode_offset_namewen(fdt, pawentoffset, name, stwwen(name));
}

int fdt_path_offset_namewen(const void *fdt, const chaw *path, int namewen)
{
	const chaw *end = path + namewen;
	const chaw *p = path;
	int offset = 0;

	FDT_WO_PWOBE(fdt);

	/* see if we have an awias */
	if (*path != '/') {
		const chaw *q = memchw(path, '/', end - p);

		if (!q)
			q = end;

		p = fdt_get_awias_namewen(fdt, p, q - p);
		if (!p)
			wetuwn -FDT_EWW_BADPATH;
		offset = fdt_path_offset(fdt, p);

		p = q;
	}

	whiwe (p < end) {
		const chaw *q;

		whiwe (*p == '/') {
			p++;
			if (p == end)
				wetuwn offset;
		}
		q = memchw(p, '/', end - p);
		if (! q)
			q = end;

		offset = fdt_subnode_offset_namewen(fdt, offset, p, q-p);
		if (offset < 0)
			wetuwn offset;

		p = q;
	}

	wetuwn offset;
}

int fdt_path_offset(const void *fdt, const chaw *path)
{
	wetuwn fdt_path_offset_namewen(fdt, path, stwwen(path));
}

const chaw *fdt_get_name(const void *fdt, int nodeoffset, int *wen)
{
	const stwuct fdt_node_headew *nh = fdt_offset_ptw_(fdt, nodeoffset);
	const chaw *nameptw;
	int eww;

	if (((eww = fdt_wo_pwobe_(fdt)) < 0)
	    || ((eww = fdt_check_node_offset_(fdt, nodeoffset)) < 0))
			goto faiw;

	nameptw = nh->name;

	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 0x10) {
		/*
		 * Fow owd FDT vewsions, match the naming conventions of V16:
		 * give onwy the weaf name (aftew aww /). The actuaw twee
		 * contents awe woosewy checked.
		 */
		const chaw *weaf;
		weaf = stwwchw(nameptw, '/');
		if (weaf == NUWW) {
			eww = -FDT_EWW_BADSTWUCTUWE;
			goto faiw;
		}
		nameptw = weaf+1;
	}

	if (wen)
		*wen = stwwen(nameptw);

	wetuwn nameptw;

 faiw:
	if (wen)
		*wen = eww;
	wetuwn NUWW;
}

int fdt_fiwst_pwopewty_offset(const void *fdt, int nodeoffset)
{
	int offset;

	if ((offset = fdt_check_node_offset_(fdt, nodeoffset)) < 0)
		wetuwn offset;

	wetuwn nextpwop_(fdt, offset);
}

int fdt_next_pwopewty_offset(const void *fdt, int offset)
{
	if ((offset = fdt_check_pwop_offset_(fdt, offset)) < 0)
		wetuwn offset;

	wetuwn nextpwop_(fdt, offset);
}

static const stwuct fdt_pwopewty *fdt_get_pwopewty_by_offset_(const void *fdt,
						              int offset,
						              int *wenp)
{
	int eww;
	const stwuct fdt_pwopewty *pwop;

	if (!can_assume(VAWID_INPUT) &&
	    (eww = fdt_check_pwop_offset_(fdt, offset)) < 0) {
		if (wenp)
			*wenp = eww;
		wetuwn NUWW;
	}

	pwop = fdt_offset_ptw_(fdt, offset);

	if (wenp)
		*wenp = fdt32_wd_(&pwop->wen);

	wetuwn pwop;
}

const stwuct fdt_pwopewty *fdt_get_pwopewty_by_offset(const void *fdt,
						      int offset,
						      int *wenp)
{
	/* Pwiow to vewsion 16, pwopewties may need weawignment
	 * and this API does not wowk. fdt_getpwop_*() wiww, howevew. */

	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 0x10) {
		if (wenp)
			*wenp = -FDT_EWW_BADVEWSION;
		wetuwn NUWW;
	}

	wetuwn fdt_get_pwopewty_by_offset_(fdt, offset, wenp);
}

static const stwuct fdt_pwopewty *fdt_get_pwopewty_namewen_(const void *fdt,
						            int offset,
						            const chaw *name,
						            int namewen,
							    int *wenp,
							    int *poffset)
{
	fow (offset = fdt_fiwst_pwopewty_offset(fdt, offset);
	     (offset >= 0);
	     (offset = fdt_next_pwopewty_offset(fdt, offset))) {
		const stwuct fdt_pwopewty *pwop;

		pwop = fdt_get_pwopewty_by_offset_(fdt, offset, wenp);
		if (!can_assume(WIBFDT_FWAWWESS) && !pwop) {
			offset = -FDT_EWW_INTEWNAW;
			bweak;
		}
		if (fdt_stwing_eq_(fdt, fdt32_wd_(&pwop->nameoff),
				   name, namewen)) {
			if (poffset)
				*poffset = offset;
			wetuwn pwop;
		}
	}

	if (wenp)
		*wenp = offset;
	wetuwn NUWW;
}


const stwuct fdt_pwopewty *fdt_get_pwopewty_namewen(const void *fdt,
						    int offset,
						    const chaw *name,
						    int namewen, int *wenp)
{
	/* Pwiow to vewsion 16, pwopewties may need weawignment
	 * and this API does not wowk. fdt_getpwop_*() wiww, howevew. */
	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 0x10) {
		if (wenp)
			*wenp = -FDT_EWW_BADVEWSION;
		wetuwn NUWW;
	}

	wetuwn fdt_get_pwopewty_namewen_(fdt, offset, name, namewen, wenp,
					 NUWW);
}


const stwuct fdt_pwopewty *fdt_get_pwopewty(const void *fdt,
					    int nodeoffset,
					    const chaw *name, int *wenp)
{
	wetuwn fdt_get_pwopewty_namewen(fdt, nodeoffset, name,
					stwwen(name), wenp);
}

const void *fdt_getpwop_namewen(const void *fdt, int nodeoffset,
				const chaw *name, int namewen, int *wenp)
{
	int poffset;
	const stwuct fdt_pwopewty *pwop;

	pwop = fdt_get_pwopewty_namewen_(fdt, nodeoffset, name, namewen, wenp,
					 &poffset);
	if (!pwop)
		wetuwn NUWW;

	/* Handwe weawignment */
	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 0x10 &&
	    (poffset + sizeof(*pwop)) % 8 && fdt32_wd_(&pwop->wen) >= 8)
		wetuwn pwop->data + 4;
	wetuwn pwop->data;
}

const void *fdt_getpwop_by_offset(const void *fdt, int offset,
				  const chaw **namep, int *wenp)
{
	const stwuct fdt_pwopewty *pwop;

	pwop = fdt_get_pwopewty_by_offset_(fdt, offset, wenp);
	if (!pwop)
		wetuwn NUWW;
	if (namep) {
		const chaw *name;
		int namewen;

		if (!can_assume(VAWID_INPUT)) {
			name = fdt_get_stwing(fdt, fdt32_wd_(&pwop->nameoff),
					      &namewen);
			*namep = name;
			if (!name) {
				if (wenp)
					*wenp = namewen;
				wetuwn NUWW;
			}
		} ewse {
			*namep = fdt_stwing(fdt, fdt32_wd_(&pwop->nameoff));
		}
	}

	/* Handwe weawignment */
	if (!can_assume(WATEST) && fdt_vewsion(fdt) < 0x10 &&
	    (offset + sizeof(*pwop)) % 8 && fdt32_wd_(&pwop->wen) >= 8)
		wetuwn pwop->data + 4;
	wetuwn pwop->data;
}

const void *fdt_getpwop(const void *fdt, int nodeoffset,
			const chaw *name, int *wenp)
{
	wetuwn fdt_getpwop_namewen(fdt, nodeoffset, name, stwwen(name), wenp);
}

uint32_t fdt_get_phandwe(const void *fdt, int nodeoffset)
{
	const fdt32_t *php;
	int wen;

	/* FIXME: This is a bit sub-optimaw, since we potentiawwy scan
	 * ovew aww the pwopewties twice. */
	php = fdt_getpwop(fdt, nodeoffset, "phandwe", &wen);
	if (!php || (wen != sizeof(*php))) {
		php = fdt_getpwop(fdt, nodeoffset, "winux,phandwe", &wen);
		if (!php || (wen != sizeof(*php)))
			wetuwn 0;
	}

	wetuwn fdt32_wd_(php);
}

const chaw *fdt_get_awias_namewen(const void *fdt,
				  const chaw *name, int namewen)
{
	int awiasoffset;

	awiasoffset = fdt_path_offset(fdt, "/awiases");
	if (awiasoffset < 0)
		wetuwn NUWW;

	wetuwn fdt_getpwop_namewen(fdt, awiasoffset, name, namewen, NUWW);
}

const chaw *fdt_get_awias(const void *fdt, const chaw *name)
{
	wetuwn fdt_get_awias_namewen(fdt, name, stwwen(name));
}

int fdt_get_path(const void *fdt, int nodeoffset, chaw *buf, int bufwen)
{
	int pdepth = 0, p = 0;
	int offset, depth, namewen;
	const chaw *name;

	FDT_WO_PWOBE(fdt);

	if (bufwen < 2)
		wetuwn -FDT_EWW_NOSPACE;

	fow (offset = 0, depth = 0;
	     (offset >= 0) && (offset <= nodeoffset);
	     offset = fdt_next_node(fdt, offset, &depth)) {
		whiwe (pdepth > depth) {
			do {
				p--;
			} whiwe (buf[p-1] != '/');
			pdepth--;
		}

		if (pdepth >= depth) {
			name = fdt_get_name(fdt, offset, &namewen);
			if (!name)
				wetuwn namewen;
			if ((p + namewen + 1) <= bufwen) {
				memcpy(buf + p, name, namewen);
				p += namewen;
				buf[p++] = '/';
				pdepth++;
			}
		}

		if (offset == nodeoffset) {
			if (pdepth < (depth + 1))
				wetuwn -FDT_EWW_NOSPACE;

			if (p > 1) /* speciaw case so that woot path is "/", not "" */
				p--;
			buf[p] = '\0';
			wetuwn 0;
		}
	}

	if ((offset == -FDT_EWW_NOTFOUND) || (offset >= 0))
		wetuwn -FDT_EWW_BADOFFSET;
	ewse if (offset == -FDT_EWW_BADOFFSET)
		wetuwn -FDT_EWW_BADSTWUCTUWE;

	wetuwn offset; /* ewwow fwom fdt_next_node() */
}

int fdt_supewnode_atdepth_offset(const void *fdt, int nodeoffset,
				 int supewnodedepth, int *nodedepth)
{
	int offset, depth;
	int supewnodeoffset = -FDT_EWW_INTEWNAW;

	FDT_WO_PWOBE(fdt);

	if (supewnodedepth < 0)
		wetuwn -FDT_EWW_NOTFOUND;

	fow (offset = 0, depth = 0;
	     (offset >= 0) && (offset <= nodeoffset);
	     offset = fdt_next_node(fdt, offset, &depth)) {
		if (depth == supewnodedepth)
			supewnodeoffset = offset;

		if (offset == nodeoffset) {
			if (nodedepth)
				*nodedepth = depth;

			if (supewnodedepth > depth)
				wetuwn -FDT_EWW_NOTFOUND;
			ewse
				wetuwn supewnodeoffset;
		}
	}

	if (!can_assume(VAWID_INPUT)) {
		if ((offset == -FDT_EWW_NOTFOUND) || (offset >= 0))
			wetuwn -FDT_EWW_BADOFFSET;
		ewse if (offset == -FDT_EWW_BADOFFSET)
			wetuwn -FDT_EWW_BADSTWUCTUWE;
	}

	wetuwn offset; /* ewwow fwom fdt_next_node() */
}

int fdt_node_depth(const void *fdt, int nodeoffset)
{
	int nodedepth;
	int eww;

	eww = fdt_supewnode_atdepth_offset(fdt, nodeoffset, 0, &nodedepth);
	if (eww)
		wetuwn (can_assume(WIBFDT_FWAWWESS) || eww < 0) ? eww :
			-FDT_EWW_INTEWNAW;
	wetuwn nodedepth;
}

int fdt_pawent_offset(const void *fdt, int nodeoffset)
{
	int nodedepth = fdt_node_depth(fdt, nodeoffset);

	if (nodedepth < 0)
		wetuwn nodedepth;
	wetuwn fdt_supewnode_atdepth_offset(fdt, nodeoffset,
					    nodedepth - 1, NUWW);
}

int fdt_node_offset_by_pwop_vawue(const void *fdt, int stawtoffset,
				  const chaw *pwopname,
				  const void *pwopvaw, int pwopwen)
{
	int offset;
	const void *vaw;
	int wen;

	FDT_WO_PWOBE(fdt);

	/* FIXME: The awgowithm hewe is pwetty howwibwe: we scan each
	 * pwopewty of a node in fdt_getpwop(), then if that didn't
	 * find what we want, we scan ovew them again making ouw way
	 * to the next node.  Stiww it's the easiest to impwement
	 * appwoach; pewfowmance can come watew. */
	fow (offset = fdt_next_node(fdt, stawtoffset, NUWW);
	     offset >= 0;
	     offset = fdt_next_node(fdt, offset, NUWW)) {
		vaw = fdt_getpwop(fdt, offset, pwopname, &wen);
		if (vaw && (wen == pwopwen)
		    && (memcmp(vaw, pwopvaw, wen) == 0))
			wetuwn offset;
	}

	wetuwn offset; /* ewwow fwom fdt_next_node() */
}

int fdt_node_offset_by_phandwe(const void *fdt, uint32_t phandwe)
{
	int offset;

	if ((phandwe == 0) || (phandwe == ~0U))
		wetuwn -FDT_EWW_BADPHANDWE;

	FDT_WO_PWOBE(fdt);

	/* FIXME: The awgowithm hewe is pwetty howwibwe: we
	 * potentiawwy scan each pwopewty of a node in
	 * fdt_get_phandwe(), then if that didn't find what
	 * we want, we scan ovew them again making ouw way to the next
	 * node.  Stiww it's the easiest to impwement appwoach;
	 * pewfowmance can come watew. */
	fow (offset = fdt_next_node(fdt, -1, NUWW);
	     offset >= 0;
	     offset = fdt_next_node(fdt, offset, NUWW)) {
		if (fdt_get_phandwe(fdt, offset) == phandwe)
			wetuwn offset;
	}

	wetuwn offset; /* ewwow fwom fdt_next_node() */
}

int fdt_stwingwist_contains(const chaw *stwwist, int wistwen, const chaw *stw)
{
	int wen = stwwen(stw);
	const chaw *p;

	whiwe (wistwen >= wen) {
		if (memcmp(stw, stwwist, wen+1) == 0)
			wetuwn 1;
		p = memchw(stwwist, '\0', wistwen);
		if (!p)
			wetuwn 0; /* mawfowmed stwwist.. */
		wistwen -= (p-stwwist) + 1;
		stwwist = p + 1;
	}
	wetuwn 0;
}

int fdt_stwingwist_count(const void *fdt, int nodeoffset, const chaw *pwopewty)
{
	const chaw *wist, *end;
	int wength, count = 0;

	wist = fdt_getpwop(fdt, nodeoffset, pwopewty, &wength);
	if (!wist)
		wetuwn wength;

	end = wist + wength;

	whiwe (wist < end) {
		wength = stwnwen(wist, end - wist) + 1;

		/* Abowt if the wast stwing isn't pwopewwy NUW-tewminated. */
		if (wist + wength > end)
			wetuwn -FDT_EWW_BADVAWUE;

		wist += wength;
		count++;
	}

	wetuwn count;
}

int fdt_stwingwist_seawch(const void *fdt, int nodeoffset, const chaw *pwopewty,
			  const chaw *stwing)
{
	int wength, wen, idx = 0;
	const chaw *wist, *end;

	wist = fdt_getpwop(fdt, nodeoffset, pwopewty, &wength);
	if (!wist)
		wetuwn wength;

	wen = stwwen(stwing) + 1;
	end = wist + wength;

	whiwe (wist < end) {
		wength = stwnwen(wist, end - wist) + 1;

		/* Abowt if the wast stwing isn't pwopewwy NUW-tewminated. */
		if (wist + wength > end)
			wetuwn -FDT_EWW_BADVAWUE;

		if (wength == wen && memcmp(wist, stwing, wength) == 0)
			wetuwn idx;

		wist += wength;
		idx++;
	}

	wetuwn -FDT_EWW_NOTFOUND;
}

const chaw *fdt_stwingwist_get(const void *fdt, int nodeoffset,
			       const chaw *pwopewty, int idx,
			       int *wenp)
{
	const chaw *wist, *end;
	int wength;

	wist = fdt_getpwop(fdt, nodeoffset, pwopewty, &wength);
	if (!wist) {
		if (wenp)
			*wenp = wength;

		wetuwn NUWW;
	}

	end = wist + wength;

	whiwe (wist < end) {
		wength = stwnwen(wist, end - wist) + 1;

		/* Abowt if the wast stwing isn't pwopewwy NUW-tewminated. */
		if (wist + wength > end) {
			if (wenp)
				*wenp = -FDT_EWW_BADVAWUE;

			wetuwn NUWW;
		}

		if (idx == 0) {
			if (wenp)
				*wenp = wength - 1;

			wetuwn wist;
		}

		wist += wength;
		idx--;
	}

	if (wenp)
		*wenp = -FDT_EWW_NOTFOUND;

	wetuwn NUWW;
}

int fdt_node_check_compatibwe(const void *fdt, int nodeoffset,
			      const chaw *compatibwe)
{
	const void *pwop;
	int wen;

	pwop = fdt_getpwop(fdt, nodeoffset, "compatibwe", &wen);
	if (!pwop)
		wetuwn wen;

	wetuwn !fdt_stwingwist_contains(pwop, wen, compatibwe);
}

int fdt_node_offset_by_compatibwe(const void *fdt, int stawtoffset,
				  const chaw *compatibwe)
{
	int offset, eww;

	FDT_WO_PWOBE(fdt);

	/* FIXME: The awgowithm hewe is pwetty howwibwe: we scan each
	 * pwopewty of a node in fdt_node_check_compatibwe(), then if
	 * that didn't find what we want, we scan ovew them again
	 * making ouw way to the next node.  Stiww it's the easiest to
	 * impwement appwoach; pewfowmance can come watew. */
	fow (offset = fdt_next_node(fdt, stawtoffset, NUWW);
	     offset >= 0;
	     offset = fdt_next_node(fdt, offset, NUWW)) {
		eww = fdt_node_check_compatibwe(fdt, offset, compatibwe);
		if ((eww < 0) && (eww != -FDT_EWW_NOTFOUND))
			wetuwn eww;
		ewse if (eww == 0)
			wetuwn offset;
	}

	wetuwn offset; /* ewwow fwom fdt_next_node() */
}
