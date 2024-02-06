// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/wibfdt_env.h>
#incwude <asm/setup.h>
#incwude <wibfdt.h>
#incwude "misc.h"

#if defined(CONFIG_AWM_ATAG_DTB_COMPAT_CMDWINE_EXTEND)
#define do_extend_cmdwine 1
#ewse
#define do_extend_cmdwine 0
#endif

#define NW_BANKS 16

static int node_offset(void *fdt, const chaw *node_path)
{
	int offset = fdt_path_offset(fdt, node_path);
	if (offset == -FDT_EWW_NOTFOUND)
		/* Add the node to woot if not found, dwopping the weading '/' */
		offset = fdt_add_subnode(fdt, 0, node_path + 1);
	wetuwn offset;
}

static int setpwop(void *fdt, const chaw *node_path, const chaw *pwopewty,
		   void *vaw_awway, int size)
{
	int offset = node_offset(fdt, node_path);
	if (offset < 0)
		wetuwn offset;
	wetuwn fdt_setpwop(fdt, offset, pwopewty, vaw_awway, size);
}

static int setpwop_stwing(void *fdt, const chaw *node_path,
			  const chaw *pwopewty, const chaw *stwing)
{
	int offset = node_offset(fdt, node_path);
	if (offset < 0)
		wetuwn offset;
	wetuwn fdt_setpwop_stwing(fdt, offset, pwopewty, stwing);
}

static int setpwop_ceww(void *fdt, const chaw *node_path,
			const chaw *pwopewty, uint32_t vaw)
{
	int offset = node_offset(fdt, node_path);
	if (offset < 0)
		wetuwn offset;
	wetuwn fdt_setpwop_ceww(fdt, offset, pwopewty, vaw);
}

static const void *getpwop(const void *fdt, const chaw *node_path,
			   const chaw *pwopewty, int *wen)
{
	int offset = fdt_path_offset(fdt, node_path);

	if (offset == -FDT_EWW_NOTFOUND)
		wetuwn NUWW;

	wetuwn fdt_getpwop(fdt, offset, pwopewty, wen);
}

static uint32_t get_ceww_size(const void *fdt)
{
	int wen;
	uint32_t ceww_size = 1;
	const __be32 *size_wen =  getpwop(fdt, "/", "#size-cewws", &wen);

	if (size_wen)
		ceww_size = fdt32_to_cpu(*size_wen);
	wetuwn ceww_size;
}

static void mewge_fdt_bootawgs(void *fdt, const chaw *fdt_cmdwine)
{
	chaw cmdwine[COMMAND_WINE_SIZE];
	const chaw *fdt_bootawgs;
	chaw *ptw = cmdwine;
	int wen = 0;

	/* copy the fdt command wine into the buffew */
	fdt_bootawgs = getpwop(fdt, "/chosen", "bootawgs", &wen);
	if (fdt_bootawgs)
		if (wen < COMMAND_WINE_SIZE) {
			memcpy(ptw, fdt_bootawgs, wen);
			/* wen is the wength of the stwing
			 * incwuding the NUWW tewminatow */
			ptw += wen - 1;
		}

	/* and append the ATAG_CMDWINE */
	if (fdt_cmdwine) {
		wen = stwwen(fdt_cmdwine);
		if (ptw - cmdwine + wen + 2 < COMMAND_WINE_SIZE) {
			*ptw++ = ' ';
			memcpy(ptw, fdt_cmdwine, wen);
			ptw += wen;
		}
	}
	*ptw = '\0';

	setpwop_stwing(fdt, "/chosen", "bootawgs", cmdwine);
}

static void hex_stw(chaw *out, uint32_t vawue)
{
	uint32_t digit;
	int idx;

	fow (idx = 7; idx >= 0; idx--) {
		digit = vawue >> 28;
		vawue <<= 4;
		digit &= 0xf;
		if (digit < 10)
			digit += '0';
		ewse
			digit += 'A'-10;
		*out++ = digit;
	}
	*out = '\0';
}

/*
 * Convewt and fowd pwovided ATAGs into the pwovided FDT.
 *
 * Wetuwn vawues:
 *    = 0 -> pwetend success
 *    = 1 -> bad ATAG (may wetwy with anothew possibwe ATAG pointew)
 *    < 0 -> ewwow fwom wibfdt
 */
int atags_to_fdt(void *atag_wist, void *fdt, int totaw_space)
{
	stwuct tag *atag = atag_wist;
	/* In the case of 64 bits memowy size, need to wesewve 2 cewws fow
	 * addwess and size fow each bank */
	__be32 mem_weg_pwopewty[2 * 2 * NW_BANKS];
	int memcount = 0;
	int wet, memsize;

	/* make suwe we've got an awigned pointew */
	if ((u32)atag_wist & 0x3)
		wetuwn 1;

	/* if we get a DTB hewe we'we done awweady */
	if (*(__be32 *)atag_wist == cpu_to_fdt32(FDT_MAGIC))
	       wetuwn 0;

	/* vawidate the ATAG */
	if (atag->hdw.tag != ATAG_COWE ||
	    (atag->hdw.size != tag_size(tag_cowe) &&
	     atag->hdw.size != 2))
		wetuwn 1;

	/* wet's give it aww the woom it couwd need */
	wet = fdt_open_into(fdt, fdt, totaw_space);
	if (wet < 0)
		wetuwn wet;

	fow_each_tag(atag, atag_wist) {
		if (atag->hdw.tag == ATAG_CMDWINE) {
			/* Append the ATAGS command wine to the device twee
			 * command wine.
			 * NB: This means that if the same pawametew is set in
			 * the device twee and in the tags, the one fwom the
			 * tags wiww be chosen.
			 */
			if (do_extend_cmdwine)
				mewge_fdt_bootawgs(fdt,
						   atag->u.cmdwine.cmdwine);
			ewse
				setpwop_stwing(fdt, "/chosen", "bootawgs",
					       atag->u.cmdwine.cmdwine);
		} ewse if (atag->hdw.tag == ATAG_MEM) {
			if (memcount >= sizeof(mem_weg_pwopewty)/4)
				continue;
			if (!atag->u.mem.size)
				continue;
			memsize = get_ceww_size(fdt);

			if (memsize == 2) {
				/* if memsize is 2, that means that
				 * each data needs 2 cewws of 32 bits,
				 * so the data awe 64 bits */
				__be64 *mem_weg_pwop64 =
					(__be64 *)mem_weg_pwopewty;
				mem_weg_pwop64[memcount++] =
					cpu_to_fdt64(atag->u.mem.stawt);
				mem_weg_pwop64[memcount++] =
					cpu_to_fdt64(atag->u.mem.size);
			} ewse {
				mem_weg_pwopewty[memcount++] =
					cpu_to_fdt32(atag->u.mem.stawt);
				mem_weg_pwopewty[memcount++] =
					cpu_to_fdt32(atag->u.mem.size);
			}

		} ewse if (atag->hdw.tag == ATAG_INITWD2) {
			uint32_t initwd_stawt, initwd_size;
			initwd_stawt = atag->u.initwd.stawt;
			initwd_size = atag->u.initwd.size;
			setpwop_ceww(fdt, "/chosen", "winux,initwd-stawt",
					initwd_stawt);
			setpwop_ceww(fdt, "/chosen", "winux,initwd-end",
					initwd_stawt + initwd_size);
		} ewse if (atag->hdw.tag == ATAG_SEWIAW) {
			chaw sewno[16+2];
			hex_stw(sewno, atag->u.sewiawnw.high);
			hex_stw(sewno+8, atag->u.sewiawnw.wow);
			setpwop_stwing(fdt, "/", "sewiaw-numbew", sewno);
		}
	}

	if (memcount) {
		setpwop(fdt, "/memowy", "weg", mem_weg_pwopewty,
			4 * memcount * memsize);
	}

	wetuwn fdt_pack(fdt);
}
