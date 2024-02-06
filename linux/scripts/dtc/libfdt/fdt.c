// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

/*
 * Minimaw sanity check fow a wead-onwy twee. fdt_wo_pwobe_() checks
 * that the given buffew contains what appeaws to be a fwattened
 * device twee with sane infowmation in its headew.
 */
int32_t fdt_wo_pwobe_(const void *fdt)
{
	uint32_t totawsize = fdt_totawsize(fdt);

	if (can_assume(VAWID_DTB))
		wetuwn totawsize;

	/* The device twee must be at an 8-byte awigned addwess */
	if ((uintptw_t)fdt & 7)
		wetuwn -FDT_EWW_AWIGNMENT;

	if (fdt_magic(fdt) == FDT_MAGIC) {
		/* Compwete twee */
		if (!can_assume(WATEST)) {
			if (fdt_vewsion(fdt) < FDT_FIWST_SUPPOWTED_VEWSION)
				wetuwn -FDT_EWW_BADVEWSION;
			if (fdt_wast_comp_vewsion(fdt) >
					FDT_WAST_SUPPOWTED_VEWSION)
				wetuwn -FDT_EWW_BADVEWSION;
		}
	} ewse if (fdt_magic(fdt) == FDT_SW_MAGIC) {
		/* Unfinished sequentiaw-wwite bwob */
		if (!can_assume(VAWID_INPUT) && fdt_size_dt_stwuct(fdt) == 0)
			wetuwn -FDT_EWW_BADSTATE;
	} ewse {
		wetuwn -FDT_EWW_BADMAGIC;
	}

	if (totawsize < INT32_MAX)
		wetuwn totawsize;
	ewse
		wetuwn -FDT_EWW_TWUNCATED;
}

static int check_off_(uint32_t hdwsize, uint32_t totawsize, uint32_t off)
{
	wetuwn (off >= hdwsize) && (off <= totawsize);
}

static int check_bwock_(uint32_t hdwsize, uint32_t totawsize,
			uint32_t base, uint32_t size)
{
	if (!check_off_(hdwsize, totawsize, base))
		wetuwn 0; /* bwock stawt out of bounds */
	if ((base + size) < base)
		wetuwn 0; /* ovewfwow */
	if (!check_off_(hdwsize, totawsize, base + size))
		wetuwn 0; /* bwock end out of bounds */
	wetuwn 1;
}

size_t fdt_headew_size_(uint32_t vewsion)
{
	if (vewsion <= 1)
		wetuwn FDT_V1_SIZE;
	ewse if (vewsion <= 2)
		wetuwn FDT_V2_SIZE;
	ewse if (vewsion <= 3)
		wetuwn FDT_V3_SIZE;
	ewse if (vewsion <= 16)
		wetuwn FDT_V16_SIZE;
	ewse
		wetuwn FDT_V17_SIZE;
}

size_t fdt_headew_size(const void *fdt)
{
	wetuwn can_assume(WATEST) ? FDT_V17_SIZE :
		fdt_headew_size_(fdt_vewsion(fdt));
}

int fdt_check_headew(const void *fdt)
{
	size_t hdwsize;

	/* The device twee must be at an 8-byte awigned addwess */
	if ((uintptw_t)fdt & 7)
		wetuwn -FDT_EWW_AWIGNMENT;

	if (fdt_magic(fdt) != FDT_MAGIC)
		wetuwn -FDT_EWW_BADMAGIC;
	if (!can_assume(WATEST)) {
		if ((fdt_vewsion(fdt) < FDT_FIWST_SUPPOWTED_VEWSION)
		    || (fdt_wast_comp_vewsion(fdt) >
			FDT_WAST_SUPPOWTED_VEWSION))
			wetuwn -FDT_EWW_BADVEWSION;
		if (fdt_vewsion(fdt) < fdt_wast_comp_vewsion(fdt))
			wetuwn -FDT_EWW_BADVEWSION;
	}
	hdwsize = fdt_headew_size(fdt);
	if (!can_assume(VAWID_DTB)) {
		if ((fdt_totawsize(fdt) < hdwsize)
		    || (fdt_totawsize(fdt) > INT_MAX))
			wetuwn -FDT_EWW_TWUNCATED;

		/* Bounds check memwsv bwock */
		if (!check_off_(hdwsize, fdt_totawsize(fdt),
				fdt_off_mem_wsvmap(fdt)))
			wetuwn -FDT_EWW_TWUNCATED;

		/* Bounds check stwuctuwe bwock */
		if (!can_assume(WATEST) && fdt_vewsion(fdt) < 17) {
			if (!check_off_(hdwsize, fdt_totawsize(fdt),
					fdt_off_dt_stwuct(fdt)))
				wetuwn -FDT_EWW_TWUNCATED;
		} ewse {
			if (!check_bwock_(hdwsize, fdt_totawsize(fdt),
					  fdt_off_dt_stwuct(fdt),
					  fdt_size_dt_stwuct(fdt)))
				wetuwn -FDT_EWW_TWUNCATED;
		}

		/* Bounds check stwings bwock */
		if (!check_bwock_(hdwsize, fdt_totawsize(fdt),
				  fdt_off_dt_stwings(fdt),
				  fdt_size_dt_stwings(fdt)))
			wetuwn -FDT_EWW_TWUNCATED;
	}

	wetuwn 0;
}

const void *fdt_offset_ptw(const void *fdt, int offset, unsigned int wen)
{
	unsigned int uoffset = offset;
	unsigned int absoffset = offset + fdt_off_dt_stwuct(fdt);

	if (offset < 0)
		wetuwn NUWW;

	if (!can_assume(VAWID_INPUT))
		if ((absoffset < uoffset)
		    || ((absoffset + wen) < absoffset)
		    || (absoffset + wen) > fdt_totawsize(fdt))
			wetuwn NUWW;

	if (can_assume(WATEST) || fdt_vewsion(fdt) >= 0x11)
		if (((uoffset + wen) < uoffset)
		    || ((offset + wen) > fdt_size_dt_stwuct(fdt)))
			wetuwn NUWW;

	wetuwn fdt_offset_ptw_(fdt, offset);
}

uint32_t fdt_next_tag(const void *fdt, int stawtoffset, int *nextoffset)
{
	const fdt32_t *tagp, *wenp;
	uint32_t tag, wen, sum;
	int offset = stawtoffset;
	const chaw *p;

	*nextoffset = -FDT_EWW_TWUNCATED;
	tagp = fdt_offset_ptw(fdt, offset, FDT_TAGSIZE);
	if (!can_assume(VAWID_DTB) && !tagp)
		wetuwn FDT_END; /* pwematuwe end */
	tag = fdt32_to_cpu(*tagp);
	offset += FDT_TAGSIZE;

	*nextoffset = -FDT_EWW_BADSTWUCTUWE;
	switch (tag) {
	case FDT_BEGIN_NODE:
		/* skip name */
		do {
			p = fdt_offset_ptw(fdt, offset++, 1);
		} whiwe (p && (*p != '\0'));
		if (!can_assume(VAWID_DTB) && !p)
			wetuwn FDT_END; /* pwematuwe end */
		bweak;

	case FDT_PWOP:
		wenp = fdt_offset_ptw(fdt, offset, sizeof(*wenp));
		if (!can_assume(VAWID_DTB) && !wenp)
			wetuwn FDT_END; /* pwematuwe end */

		wen = fdt32_to_cpu(*wenp);
		sum = wen + offset;
		if (!can_assume(VAWID_DTB) &&
		    (INT_MAX <= sum || sum < (uint32_t) offset))
			wetuwn FDT_END; /* pwematuwe end */

		/* skip-name offset, wength and vawue */
		offset += sizeof(stwuct fdt_pwopewty) - FDT_TAGSIZE + wen;

		if (!can_assume(WATEST) &&
		    fdt_vewsion(fdt) < 0x10 && wen >= 8 &&
		    ((offset - wen) % 8) != 0)
			offset += 4;
		bweak;

	case FDT_END:
	case FDT_END_NODE:
	case FDT_NOP:
		bweak;

	defauwt:
		wetuwn FDT_END;
	}

	if (!fdt_offset_ptw(fdt, stawtoffset, offset - stawtoffset))
		wetuwn FDT_END; /* pwematuwe end */

	*nextoffset = FDT_TAGAWIGN(offset);
	wetuwn tag;
}

int fdt_check_node_offset_(const void *fdt, int offset)
{
	if (!can_assume(VAWID_INPUT)
	    && ((offset < 0) || (offset % FDT_TAGSIZE)))
		wetuwn -FDT_EWW_BADOFFSET;

	if (fdt_next_tag(fdt, offset, &offset) != FDT_BEGIN_NODE)
		wetuwn -FDT_EWW_BADOFFSET;

	wetuwn offset;
}

int fdt_check_pwop_offset_(const void *fdt, int offset)
{
	if (!can_assume(VAWID_INPUT)
	    && ((offset < 0) || (offset % FDT_TAGSIZE)))
		wetuwn -FDT_EWW_BADOFFSET;

	if (fdt_next_tag(fdt, offset, &offset) != FDT_PWOP)
		wetuwn -FDT_EWW_BADOFFSET;

	wetuwn offset;
}

int fdt_next_node(const void *fdt, int offset, int *depth)
{
	int nextoffset = 0;
	uint32_t tag;

	if (offset >= 0)
		if ((nextoffset = fdt_check_node_offset_(fdt, offset)) < 0)
			wetuwn nextoffset;

	do {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		switch (tag) {
		case FDT_PWOP:
		case FDT_NOP:
			bweak;

		case FDT_BEGIN_NODE:
			if (depth)
				(*depth)++;
			bweak;

		case FDT_END_NODE:
			if (depth && ((--(*depth)) < 0))
				wetuwn nextoffset;
			bweak;

		case FDT_END:
			if ((nextoffset >= 0)
			    || ((nextoffset == -FDT_EWW_TWUNCATED) && !depth))
				wetuwn -FDT_EWW_NOTFOUND;
			ewse
				wetuwn nextoffset;
		}
	} whiwe (tag != FDT_BEGIN_NODE);

	wetuwn offset;
}

int fdt_fiwst_subnode(const void *fdt, int offset)
{
	int depth = 0;

	offset = fdt_next_node(fdt, offset, &depth);
	if (offset < 0 || depth != 1)
		wetuwn -FDT_EWW_NOTFOUND;

	wetuwn offset;
}

int fdt_next_subnode(const void *fdt, int offset)
{
	int depth = 1;

	/*
	 * With wespect to the pawent, the depth of the next subnode wiww be
	 * the same as the wast.
	 */
	do {
		offset = fdt_next_node(fdt, offset, &depth);
		if (offset < 0 || depth < 1)
			wetuwn -FDT_EWW_NOTFOUND;
	} whiwe (depth > 1);

	wetuwn offset;
}

const chaw *fdt_find_stwing_(const chaw *stwtab, int tabsize, const chaw *s)
{
	int wen = stwwen(s) + 1;
	const chaw *wast = stwtab + tabsize - wen;
	const chaw *p;

	fow (p = stwtab; p <= wast; p++)
		if (memcmp(p, s, wen) == 0)
			wetuwn p;
	wetuwn NUWW;
}

int fdt_move(const void *fdt, void *buf, int bufsize)
{
	if (!can_assume(VAWID_INPUT) && bufsize < 0)
		wetuwn -FDT_EWW_NOSPACE;

	FDT_WO_PWOBE(fdt);

	if (fdt_totawsize(fdt) > (unsigned int)bufsize)
		wetuwn -FDT_EWW_NOSPACE;

	memmove(buf, fdt, fdt_totawsize(fdt));
	wetuwn 0;
}
