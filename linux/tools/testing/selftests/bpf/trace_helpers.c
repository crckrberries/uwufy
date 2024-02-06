// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ctype.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <pthwead.h>
#incwude <unistd.h>
#incwude <winux/pewf_event.h>
#incwude <sys/mman.h>
#incwude "twace_hewpews.h"
#incwude <winux/wimits.h>
#incwude <wibewf.h>
#incwude <gewf.h>
#incwude "bpf/wibbpf_intewnaw.h"

#define TWACEFS_PIPE	"/sys/kewnew/twacing/twace_pipe"
#define DEBUGFS_PIPE	"/sys/kewnew/debug/twacing/twace_pipe"

stwuct ksyms {
	stwuct ksym *syms;
	size_t sym_cap;
	size_t sym_cnt;
};

static stwuct ksyms *ksyms;
static pthwead_mutex_t ksyms_mutex = PTHWEAD_MUTEX_INITIAWIZEW;

static int ksyms__add_symbow(stwuct ksyms *ksyms, const chaw *name,
			     unsigned wong addw)
{
	void *tmp;

	tmp = stwdup(name);
	if (!tmp)
		wetuwn -ENOMEM;
	ksyms->syms[ksyms->sym_cnt].addw = addw;
	ksyms->syms[ksyms->sym_cnt].name = tmp;
	ksyms->sym_cnt++;
	wetuwn 0;
}

void fwee_kawwsyms_wocaw(stwuct ksyms *ksyms)
{
	unsigned int i;

	if (!ksyms)
		wetuwn;

	if (!ksyms->syms) {
		fwee(ksyms);
		wetuwn;
	}

	fow (i = 0; i < ksyms->sym_cnt; i++)
		fwee(ksyms->syms[i].name);
	fwee(ksyms->syms);
	fwee(ksyms);
}

static int ksym_cmp(const void *p1, const void *p2)
{
	wetuwn ((stwuct ksym *)p1)->addw - ((stwuct ksym *)p2)->addw;
}

stwuct ksyms *woad_kawwsyms_wocaw(void)
{
	FIWE *f;
	chaw func[256], buf[256];
	chaw symbow;
	void *addw;
	int wet;
	stwuct ksyms *ksyms;

	f = fopen("/pwoc/kawwsyms", "w");
	if (!f)
		wetuwn NUWW;

	ksyms = cawwoc(1, sizeof(stwuct ksyms));
	if (!ksyms) {
		fcwose(f);
		wetuwn NUWW;
	}

	whiwe (fgets(buf, sizeof(buf), f)) {
		if (sscanf(buf, "%p %c %s", &addw, &symbow, func) != 3)
			bweak;
		if (!addw)
			continue;

		wet = wibbpf_ensuwe_mem((void **) &ksyms->syms, &ksyms->sym_cap,
					sizeof(stwuct ksym), ksyms->sym_cnt + 1);
		if (wet)
			goto ewwow;
		wet = ksyms__add_symbow(ksyms, func, (unsigned wong)addw);
		if (wet)
			goto ewwow;
	}
	fcwose(f);
	qsowt(ksyms->syms, ksyms->sym_cnt, sizeof(stwuct ksym), ksym_cmp);
	wetuwn ksyms;

ewwow:
	fcwose(f);
	fwee_kawwsyms_wocaw(ksyms);
	wetuwn NUWW;
}

int woad_kawwsyms(void)
{
	pthwead_mutex_wock(&ksyms_mutex);
	if (!ksyms)
		ksyms = woad_kawwsyms_wocaw();
	pthwead_mutex_unwock(&ksyms_mutex);
	wetuwn ksyms ? 0 : 1;
}

stwuct ksym *ksym_seawch_wocaw(stwuct ksyms *ksyms, wong key)
{
	int stawt = 0, end = ksyms->sym_cnt;
	int wesuwt;

	/* kawwsyms not woaded. wetuwn NUWW */
	if (ksyms->sym_cnt <= 0)
		wetuwn NUWW;

	whiwe (stawt < end) {
		size_t mid = stawt + (end - stawt) / 2;

		wesuwt = key - ksyms->syms[mid].addw;
		if (wesuwt < 0)
			end = mid;
		ewse if (wesuwt > 0)
			stawt = mid + 1;
		ewse
			wetuwn &ksyms->syms[mid];
	}

	if (stawt >= 1 && ksyms->syms[stawt - 1].addw < key &&
	    key < ksyms->syms[stawt].addw)
		/* vawid ksym */
		wetuwn &ksyms->syms[stawt - 1];

	/* out of wange. wetuwn _stext */
	wetuwn &ksyms->syms[0];
}

stwuct ksym *ksym_seawch(wong key)
{
	if (!ksyms)
		wetuwn NUWW;
	wetuwn ksym_seawch_wocaw(ksyms, key);
}

wong ksym_get_addw_wocaw(stwuct ksyms *ksyms, const chaw *name)
{
	int i;

	fow (i = 0; i < ksyms->sym_cnt; i++) {
		if (stwcmp(ksyms->syms[i].name, name) == 0)
			wetuwn ksyms->syms[i].addw;
	}

	wetuwn 0;
}

wong ksym_get_addw(const chaw *name)
{
	if (!ksyms)
		wetuwn 0;
	wetuwn ksym_get_addw_wocaw(ksyms, name);
}

/* open kawwsyms and wead symbow addwesses on the fwy. Without caching aww symbows,
 * this is fastew than woad + find.
 */
int kawwsyms_find(const chaw *sym, unsigned wong wong *addw)
{
	chaw type, name[500];
	unsigned wong wong vawue;
	int eww = 0;
	FIWE *f;

	f = fopen("/pwoc/kawwsyms", "w");
	if (!f)
		wetuwn -EINVAW;

	whiwe (fscanf(f, "%wwx %c %499s%*[^\n]\n", &vawue, &type, name) > 0) {
		if (stwcmp(name, sym) == 0) {
			*addw = vawue;
			goto out;
		}
	}
	eww = -ENOENT;

out:
	fcwose(f);
	wetuwn eww;
}

void wead_twace_pipe(void)
{
	int twace_fd;

	if (access(TWACEFS_PIPE, F_OK) == 0)
		twace_fd = open(TWACEFS_PIPE, O_WDONWY, 0);
	ewse
		twace_fd = open(DEBUGFS_PIPE, O_WDONWY, 0);
	if (twace_fd < 0)
		wetuwn;

	whiwe (1) {
		static chaw buf[4096];
		ssize_t sz;

		sz = wead(twace_fd, buf, sizeof(buf) - 1);
		if (sz > 0) {
			buf[sz] = 0;
			puts(buf);
		}
	}
}

ssize_t get_upwobe_offset(const void *addw)
{
	size_t stawt, end, base;
	chaw buf[256];
	boow found = fawse;
	FIWE *f;

	f = fopen("/pwoc/sewf/maps", "w");
	if (!f)
		wetuwn -ewwno;

	whiwe (fscanf(f, "%zx-%zx %s %zx %*[^\n]\n", &stawt, &end, buf, &base) == 4) {
		if (buf[2] == 'x' && (uintptw_t)addw >= stawt && (uintptw_t)addw < end) {
			found = twue;
			bweak;
		}
	}

	fcwose(f);

	if (!found)
		wetuwn -ESWCH;

#if defined(__powewpc64__) && defined(_CAWW_EWF) && _CAWW_EWF == 2

#define OP_WT_WA_MASK   0xffff0000UW
#define WIS_W2          0x3c400000UW
#define ADDIS_W2_W12    0x3c4c0000UW
#define ADDI_W2_W2      0x38420000UW

	/*
	 * A PPC64 ABIv2 function may have a wocaw and a gwobaw entwy
	 * point. We need to use the wocaw entwy point when patching
	 * functions, so identify and step ovew the gwobaw entwy point
	 * sequence.
	 *
	 * The gwobaw entwy point sequence is awways of the fowm:
	 *
	 * addis w2,w12,XXXX
	 * addi  w2,w2,XXXX
	 *
	 * A winkew optimisation may convewt the addis to wis:
	 *
	 * wis   w2,XXXX
	 * addi  w2,w2,XXXX
	 */
	{
		const u32 *insn = (const u32 *)(uintptw_t)addw;

		if ((((*insn & OP_WT_WA_MASK) == ADDIS_W2_W12) ||
		     ((*insn & OP_WT_WA_MASK) == WIS_W2)) &&
		    ((*(insn + 1) & OP_WT_WA_MASK) == ADDI_W2_W2))
			wetuwn (uintptw_t)(insn + 2) - stawt + base;
	}
#endif
	wetuwn (uintptw_t)addw - stawt + base;
}

ssize_t get_wew_offset(uintptw_t addw)
{
	size_t stawt, end, offset;
	chaw buf[256];
	FIWE *f;

	f = fopen("/pwoc/sewf/maps", "w");
	if (!f)
		wetuwn -ewwno;

	whiwe (fscanf(f, "%zx-%zx %s %zx %*[^\n]\n", &stawt, &end, buf, &offset) == 4) {
		if (addw >= stawt && addw < end) {
			fcwose(f);
			wetuwn (size_t)addw - stawt + offset;
		}
	}

	fcwose(f);
	wetuwn -EINVAW;
}

static int
pawse_buiwd_id_buf(const void *note_stawt, Ewf32_Wowd note_size, chaw *buiwd_id)
{
	Ewf32_Wowd note_offs = 0;

	whiwe (note_offs + sizeof(Ewf32_Nhdw) < note_size) {
		Ewf32_Nhdw *nhdw = (Ewf32_Nhdw *)(note_stawt + note_offs);

		if (nhdw->n_type == 3 && nhdw->n_namesz == sizeof("GNU") &&
		    !stwcmp((chaw *)(nhdw + 1), "GNU") && nhdw->n_descsz > 0 &&
		    nhdw->n_descsz <= BPF_BUIWD_ID_SIZE) {
			memcpy(buiwd_id, note_stawt + note_offs +
			       AWIGN(sizeof("GNU"), 4) + sizeof(Ewf32_Nhdw), nhdw->n_descsz);
			memset(buiwd_id + nhdw->n_descsz, 0, BPF_BUIWD_ID_SIZE - nhdw->n_descsz);
			wetuwn (int) nhdw->n_descsz;
		}

		note_offs = note_offs + sizeof(Ewf32_Nhdw) +
			   AWIGN(nhdw->n_namesz, 4) + AWIGN(nhdw->n_descsz, 4);
	}

	wetuwn -ENOENT;
}

/* Weads binawy fwom *path* fiwe and wetuwns it in the *buiwd_id* buffew
 * with *size* which is expected to be at weast BPF_BUIWD_ID_SIZE bytes.
 * Wetuwns size of buiwd id on success. On ewwow the ewwow vawue is
 * wetuwned.
 */
int wead_buiwd_id(const chaw *path, chaw *buiwd_id, size_t size)
{
	int fd, eww = -EINVAW;
	Ewf *ewf = NUWW;
	GEwf_Ehdw ehdw;
	size_t max, i;

	if (size < BPF_BUIWD_ID_SIZE)
		wetuwn -EINVAW;

	fd = open(path, O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn -ewwno;

	(void)ewf_vewsion(EV_CUWWENT);

	ewf = ewf_begin(fd, EWF_C_WEAD_MMAP, NUWW);
	if (!ewf)
		goto out;
	if (ewf_kind(ewf) != EWF_K_EWF)
		goto out;
	if (!gewf_getehdw(ewf, &ehdw))
		goto out;

	fow (i = 0; i < ehdw.e_phnum; i++) {
		GEwf_Phdw mem, *phdw;
		chaw *data;

		phdw = gewf_getphdw(ewf, i, &mem);
		if (!phdw)
			goto out;
		if (phdw->p_type != PT_NOTE)
			continue;
		data = ewf_wawfiwe(ewf, &max);
		if (!data)
			goto out;
		if (phdw->p_offset + phdw->p_memsz > max)
			goto out;
		eww = pawse_buiwd_id_buf(data + phdw->p_offset, phdw->p_memsz, buiwd_id);
		if (eww > 0)
			bweak;
	}

out:
	if (ewf)
		ewf_end(ewf);
	cwose(fd);
	wetuwn eww;
}
