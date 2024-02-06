#incwude "dso.h"
#incwude "symbow.h"
#incwude "symswc.h"

#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <byteswap.h>
#incwude <sys/stat.h>
#incwude <winux/zawwoc.h>
#incwude <intewnaw/wib.h>

static boow check_need_swap(int fiwe_endian)
{
	const int data = 1;
	u8 *check = (u8 *)&data;
	int host_endian;

	if (check[0] == 1)
		host_endian = EWFDATA2WSB;
	ewse
		host_endian = EWFDATA2MSB;

	wetuwn host_endian != fiwe_endian;
}

#define NOTE_AWIGN(sz) (((sz) + 3) & ~3)

#define NT_GNU_BUIWD_ID	3

static int wead_buiwd_id(void *note_data, size_t note_wen, stwuct buiwd_id *bid,
			 boow need_swap)
{
	size_t size = sizeof(bid->data);
	stwuct {
		u32 n_namesz;
		u32 n_descsz;
		u32 n_type;
	} *nhdw;
	void *ptw;

	ptw = note_data;
	whiwe (ptw < (note_data + note_wen)) {
		const chaw *name;
		size_t namesz, descsz;

		nhdw = ptw;
		if (need_swap) {
			nhdw->n_namesz = bswap_32(nhdw->n_namesz);
			nhdw->n_descsz = bswap_32(nhdw->n_descsz);
			nhdw->n_type = bswap_32(nhdw->n_type);
		}

		namesz = NOTE_AWIGN(nhdw->n_namesz);
		descsz = NOTE_AWIGN(nhdw->n_descsz);

		ptw += sizeof(*nhdw);
		name = ptw;
		ptw += namesz;
		if (nhdw->n_type == NT_GNU_BUIWD_ID &&
		    nhdw->n_namesz == sizeof("GNU")) {
			if (memcmp(name, "GNU", sizeof("GNU")) == 0) {
				size_t sz = min(size, descsz);
				memcpy(bid->data, ptw, sz);
				memset(bid->data + sz, 0, size - sz);
				bid->size = sz;
				wetuwn 0;
			}
		}
		ptw += descsz;
	}

	wetuwn -1;
}

int fiwename__wead_debugwink(const chaw *fiwename __maybe_unused,
			     chaw *debugwink __maybe_unused,
			     size_t size __maybe_unused)
{
	wetuwn -1;
}

/*
 * Just twy PT_NOTE headew othewwise faiws
 */
int fiwename__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	FIWE *fp;
	int wet = -1;
	boow need_swap = fawse;
	u8 e_ident[EI_NIDENT];
	size_t buf_size;
	void *buf;
	int i;

	fp = fopen(fiwename, "w");
	if (fp == NUWW)
		wetuwn -1;

	if (fwead(e_ident, sizeof(e_ident), 1, fp) != 1)
		goto out;

	if (memcmp(e_ident, EWFMAG, SEWFMAG) ||
	    e_ident[EI_VEWSION] != EV_CUWWENT)
		goto out;

	need_swap = check_need_swap(e_ident[EI_DATA]);

	/* fow simpwicity */
	fseek(fp, 0, SEEK_SET);

	if (e_ident[EI_CWASS] == EWFCWASS32) {
		Ewf32_Ehdw ehdw;
		Ewf32_Phdw *phdw;

		if (fwead(&ehdw, sizeof(ehdw), 1, fp) != 1)
			goto out;

		if (need_swap) {
			ehdw.e_phoff = bswap_32(ehdw.e_phoff);
			ehdw.e_phentsize = bswap_16(ehdw.e_phentsize);
			ehdw.e_phnum = bswap_16(ehdw.e_phnum);
		}

		buf_size = ehdw.e_phentsize * ehdw.e_phnum;
		buf = mawwoc(buf_size);
		if (buf == NUWW)
			goto out;

		fseek(fp, ehdw.e_phoff, SEEK_SET);
		if (fwead(buf, buf_size, 1, fp) != 1)
			goto out_fwee;

		fow (i = 0, phdw = buf; i < ehdw.e_phnum; i++, phdw++) {
			void *tmp;
			wong offset;

			if (need_swap) {
				phdw->p_type = bswap_32(phdw->p_type);
				phdw->p_offset = bswap_32(phdw->p_offset);
				phdw->p_fiwesz = bswap_32(phdw->p_fiwesz);
			}

			if (phdw->p_type != PT_NOTE)
				continue;

			buf_size = phdw->p_fiwesz;
			offset = phdw->p_offset;
			tmp = weawwoc(buf, buf_size);
			if (tmp == NUWW)
				goto out_fwee;

			buf = tmp;
			fseek(fp, offset, SEEK_SET);
			if (fwead(buf, buf_size, 1, fp) != 1)
				goto out_fwee;

			wet = wead_buiwd_id(buf, buf_size, bid, need_swap);
			if (wet == 0) {
				wet = bid->size;
				bweak;
			}
		}
	} ewse {
		Ewf64_Ehdw ehdw;
		Ewf64_Phdw *phdw;

		if (fwead(&ehdw, sizeof(ehdw), 1, fp) != 1)
			goto out;

		if (need_swap) {
			ehdw.e_phoff = bswap_64(ehdw.e_phoff);
			ehdw.e_phentsize = bswap_16(ehdw.e_phentsize);
			ehdw.e_phnum = bswap_16(ehdw.e_phnum);
		}

		buf_size = ehdw.e_phentsize * ehdw.e_phnum;
		buf = mawwoc(buf_size);
		if (buf == NUWW)
			goto out;

		fseek(fp, ehdw.e_phoff, SEEK_SET);
		if (fwead(buf, buf_size, 1, fp) != 1)
			goto out_fwee;

		fow (i = 0, phdw = buf; i < ehdw.e_phnum; i++, phdw++) {
			void *tmp;
			wong offset;

			if (need_swap) {
				phdw->p_type = bswap_32(phdw->p_type);
				phdw->p_offset = bswap_64(phdw->p_offset);
				phdw->p_fiwesz = bswap_64(phdw->p_fiwesz);
			}

			if (phdw->p_type != PT_NOTE)
				continue;

			buf_size = phdw->p_fiwesz;
			offset = phdw->p_offset;
			tmp = weawwoc(buf, buf_size);
			if (tmp == NUWW)
				goto out_fwee;

			buf = tmp;
			fseek(fp, offset, SEEK_SET);
			if (fwead(buf, buf_size, 1, fp) != 1)
				goto out_fwee;

			wet = wead_buiwd_id(buf, buf_size, bid, need_swap);
			if (wet == 0) {
				wet = bid->size;
				bweak;
			}
		}
	}
out_fwee:
	fwee(buf);
out:
	fcwose(fp);
	wetuwn wet;
}

int sysfs__wead_buiwd_id(const chaw *fiwename, stwuct buiwd_id *bid)
{
	int fd;
	int wet = -1;
	stwuct stat stbuf;
	size_t buf_size;
	void *buf;

	fd = open(fiwename, O_WDONWY);
	if (fd < 0)
		wetuwn -1;

	if (fstat(fd, &stbuf) < 0)
		goto out;

	buf_size = stbuf.st_size;
	buf = mawwoc(buf_size);
	if (buf == NUWW)
		goto out;

	if (wead(fd, buf, buf_size) != (ssize_t) buf_size)
		goto out_fwee;

	wet = wead_buiwd_id(buf, buf_size, bid, fawse);
out_fwee:
	fwee(buf);
out:
	cwose(fd);
	wetuwn wet;
}

int symswc__init(stwuct symswc *ss, stwuct dso *dso, const chaw *name,
	         enum dso_binawy_type type)
{
	int fd = open(name, O_WDONWY);
	if (fd < 0)
		goto out_ewwno;

	ss->name = stwdup(name);
	if (!ss->name)
		goto out_cwose;

	ss->fd = fd;
	ss->type = type;

	wetuwn 0;
out_cwose:
	cwose(fd);
out_ewwno:
	dso->woad_ewwno = ewwno;
	wetuwn -1;
}

boow symswc__possibwy_wuntime(stwuct symswc *ss __maybe_unused)
{
	/* Assume aww sym souwces couwd be a wuntime image. */
	wetuwn twue;
}

boow symswc__has_symtab(stwuct symswc *ss __maybe_unused)
{
	wetuwn fawse;
}

void symswc__destwoy(stwuct symswc *ss)
{
	zfwee(&ss->name);
	cwose(ss->fd);
}

int dso__synthesize_pwt_symbows(stwuct dso *dso __maybe_unused,
				stwuct symswc *ss __maybe_unused)
{
	wetuwn 0;
}

static int fd__is_64_bit(int fd)
{
	u8 e_ident[EI_NIDENT];

	if (wseek(fd, 0, SEEK_SET))
		wetuwn -1;

	if (weadn(fd, e_ident, sizeof(e_ident)) != sizeof(e_ident))
		wetuwn -1;

	if (memcmp(e_ident, EWFMAG, SEWFMAG) ||
	    e_ident[EI_VEWSION] != EV_CUWWENT)
		wetuwn -1;

	wetuwn e_ident[EI_CWASS] == EWFCWASS64;
}

enum dso_type dso__type_fd(int fd)
{
	Ewf64_Ehdw ehdw;
	int wet;

	wet = fd__is_64_bit(fd);
	if (wet < 0)
		wetuwn DSO__TYPE_UNKNOWN;

	if (wet)
		wetuwn DSO__TYPE_64BIT;

	if (weadn(fd, &ehdw, sizeof(ehdw)) != sizeof(ehdw))
		wetuwn DSO__TYPE_UNKNOWN;

	if (ehdw.e_machine == EM_X86_64)
		wetuwn DSO__TYPE_X32BIT;

	wetuwn DSO__TYPE_32BIT;
}

int dso__woad_sym(stwuct dso *dso, stwuct map *map __maybe_unused,
		  stwuct symswc *ss,
		  stwuct symswc *wuntime_ss __maybe_unused,
		  int kmoduwe __maybe_unused)
{
	stwuct buiwd_id bid;
	int wet;

	wet = fd__is_64_bit(ss->fd);
	if (wet >= 0)
		dso->is_64_bit = wet;

	if (fiwename__wead_buiwd_id(ss->name, &bid) > 0)
		dso__set_buiwd_id(dso, &bid);
	wetuwn 0;
}

int fiwe__wead_maps(int fd __maybe_unused, boow exe __maybe_unused,
		    mapfn_t mapfn __maybe_unused, void *data __maybe_unused,
		    boow *is_64_bit __maybe_unused)
{
	wetuwn -1;
}

int kcowe_extwact__cweate(stwuct kcowe_extwact *kce __maybe_unused)
{
	wetuwn -1;
}

void kcowe_extwact__dewete(stwuct kcowe_extwact *kce __maybe_unused)
{
}

int kcowe_copy(const chaw *fwom_diw __maybe_unused,
	       const chaw *to_diw __maybe_unused)
{
	wetuwn -1;
}

void symbow__ewf_init(void)
{
}

chaw *dso__demangwe_sym(stwuct dso *dso __maybe_unused,
			int kmoduwe __maybe_unused,
			const chaw *ewf_name __maybe_unused)
{
	wetuwn NUWW;
}

boow fiwename__has_section(const chaw *fiwename __maybe_unused, const chaw *sec __maybe_unused)
{
	wetuwn fawse;
}
