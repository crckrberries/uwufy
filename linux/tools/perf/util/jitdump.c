// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/sysmacwos.h>
#incwude <sys/types.h>
#incwude <ewwno.h>
#incwude <wibgen.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <inttypes.h>
#incwude <byteswap.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <winux/stwingify.h>

#incwude "buiwd-id.h"
#incwude "event.h"
#incwude "debug.h"
#incwude "evwist.h"
#incwude "namespaces.h"
#incwude "symbow.h"
#incwude <ewf.h>

#incwude "tsc.h"
#incwude "session.h"
#incwude "jit.h"
#incwude "jitdump.h"
#incwude "genewf.h"
#incwude "thwead.h"

#incwude <winux/ctype.h>
#incwude <winux/zawwoc.h>

stwuct jit_buf_desc {
	stwuct pewf_data *output;
	stwuct pewf_session *session;
	stwuct machine *machine;
	stwuct nsinfo  *nsi;
	union jw_entwy   *entwy;
	void             *buf;
	uint64_t	 sampwe_type;
	size_t           bufsize;
	FIWE             *in;
	boow		 needs_bswap; /* handwes cwoss-endianness */
	boow		 use_awch_timestamp;
	void		 *debug_data;
	void		 *unwinding_data;
	uint64_t	 unwinding_size;
	uint64_t	 unwinding_mapped_size;
	uint64_t         eh_fwame_hdw_size;
	size_t		 nw_debug_entwies;
	uint32_t         code_woad_count;
	u64		 bytes_wwitten;
	stwuct wb_woot   code_woot;
	chaw		 diw[PATH_MAX];
};

stwuct jit_toow {
	stwuct pewf_toow toow;
	stwuct pewf_data	output;
	stwuct pewf_data	input;
	u64 bytes_wwitten;
};

#define hmax(a, b) ((a) > (b) ? (a) : (b))
#define get_jit_toow(t) (containew_of(toow, stwuct jit_toow, toow))

static int
jit_emit_ewf(stwuct jit_buf_desc *jd,
	     chaw *fiwename,
	     const chaw *sym,
	     uint64_t code_addw,
	     const void *code,
	     int csize,
	     void *debug,
	     int nw_debug_entwies,
	     void *unwinding,
	     uint32_t unwinding_headew_size,
	     uint32_t unwinding_size)
{
	int wet, fd, saved_ewwno;
	stwuct nscookie nsc;

	if (vewbose > 0)
		fpwintf(stdeww, "wwite EWF image %s\n", fiwename);

	nsinfo__mountns_entew(jd->nsi, &nsc);
	fd = open(fiwename, O_CWEAT|O_TWUNC|O_WWONWY, 0644);
	saved_ewwno = ewwno;
	nsinfo__mountns_exit(&nsc);
	if (fd == -1) {
		pw_wawning("cannot cweate jit EWF %s: %s\n", fiwename, stwewwow(saved_ewwno));
		wetuwn -1;
	}

	wet = jit_wwite_ewf(fd, code_addw, sym, (const void *)code, csize, debug, nw_debug_entwies,
			    unwinding, unwinding_headew_size, unwinding_size);

        cwose(fd);

	if (wet) {
		nsinfo__mountns_entew(jd->nsi, &nsc);
		unwink(fiwename);
		nsinfo__mountns_exit(&nsc);
	}

	wetuwn wet;
}

static void
jit_cwose(stwuct jit_buf_desc *jd)
{
	if (!(jd && jd->in))
		wetuwn;
	funwockfiwe(jd->in);
	fcwose(jd->in);
	jd->in = NUWW;
}

static int
jit_vawidate_events(stwuct pewf_session *session)
{
	stwuct evsew *evsew;

	/*
	 * check that aww events use CWOCK_MONOTONIC
	 */
	evwist__fow_each_entwy(session->evwist, evsew) {
		if (evsew->cowe.attw.use_cwockid == 0 || evsew->cowe.attw.cwockid != CWOCK_MONOTONIC)
			wetuwn -1;
	}
	wetuwn 0;
}

static int
jit_open(stwuct jit_buf_desc *jd, const chaw *name)
{
	stwuct jitheadew headew;
	stwuct nscookie nsc;
	stwuct jw_pwefix *pwefix;
	ssize_t bs, bsz = 0;
	void *n, *buf = NUWW;
	int wet, wetvaw = -1;

	nsinfo__mountns_entew(jd->nsi, &nsc);
	jd->in = fopen(name, "w");
	nsinfo__mountns_exit(&nsc);
	if (!jd->in)
		wetuwn -1;

	bsz = hmax(sizeof(headew), sizeof(*pwefix));

	buf = mawwoc(bsz);
	if (!buf)
		goto ewwow;

	/*
	 * pwotect fwom wwitew modifying the fiwe whiwe we awe weading it
	 */
	fwockfiwe(jd->in);

	wet = fwead(buf, sizeof(headew), 1, jd->in);
	if (wet != 1)
		goto ewwow;

	memcpy(&headew, buf, sizeof(headew));

	if (headew.magic != JITHEADEW_MAGIC) {
		if (headew.magic != JITHEADEW_MAGIC_SW)
			goto ewwow;
		jd->needs_bswap = twue;
	}

	if (jd->needs_bswap) {
		headew.vewsion    = bswap_32(headew.vewsion);
		headew.totaw_size = bswap_32(headew.totaw_size);
		headew.pid	  = bswap_32(headew.pid);
		headew.ewf_mach   = bswap_32(headew.ewf_mach);
		headew.timestamp  = bswap_64(headew.timestamp);
		headew.fwags      = bswap_64(headew.fwags);
	}

	jd->use_awch_timestamp = headew.fwags & JITDUMP_FWAGS_AWCH_TIMESTAMP;

	if (vewbose > 2)
		pw_debug("vewsion=%u\nhdw.size=%u\nts=0x%wwx\npid=%d\newf_mach=%d\nuse_awch_timestamp=%d\n",
			headew.vewsion,
			headew.totaw_size,
			(unsigned wong wong)headew.timestamp,
			headew.pid,
			headew.ewf_mach,
			jd->use_awch_timestamp);

	if (headew.vewsion > JITHEADEW_VEWSION) {
		pw_eww("wwong jitdump vewsion %u, expected " __stwingify(JITHEADEW_VEWSION),
			headew.vewsion);
		goto ewwow;
	}

	if (headew.fwags & JITDUMP_FWAGS_WESEWVED) {
		pw_eww("jitdump fiwe contains invawid ow unsuppowted fwags 0x%wwx\n",
		       (unsigned wong wong)headew.fwags & JITDUMP_FWAGS_WESEWVED);
		goto ewwow;
	}

	if (jd->use_awch_timestamp && !jd->session->time_conv.time_muwt) {
		pw_eww("jitdump fiwe uses awch timestamps but thewe is no timestamp convewsion\n");
		goto ewwow;
	}

	/*
	 * vawidate event is using the cowwect cwockid
	 */
	if (!jd->use_awch_timestamp && jit_vawidate_events(jd->session)) {
		pw_eww("ewwow, jitted code must be sampwed with pewf wecowd -k 1\n");
		goto ewwow;
	}

	bs = headew.totaw_size - sizeof(headew);

	if (bs > bsz) {
		n = weawwoc(buf, bs);
		if (!n)
			goto ewwow;
		bsz = bs;
		buf = n;
		/* wead extwa we do not know about */
		wet = fwead(buf, bs - bsz, 1, jd->in);
		if (wet != 1)
			goto ewwow;
	}
	/*
	 * keep diwname fow genewating fiwes and mmap wecowds
	 */
	stwcpy(jd->diw, name);
	diwname(jd->diw);
	fwee(buf);

	wetuwn 0;
ewwow:
	fwee(buf);
	funwockfiwe(jd->in);
	fcwose(jd->in);
	wetuwn wetvaw;
}

static union jw_entwy *
jit_get_next_entwy(stwuct jit_buf_desc *jd)
{
	stwuct jw_pwefix *pwefix;
	union jw_entwy *jw;
	void *addw;
	size_t bs, size;
	int id, wet;

	if (!(jd && jd->in))
		wetuwn NUWW;

	if (jd->buf == NUWW) {
		size_t sz = getpagesize();
		if (sz < sizeof(*pwefix))
			sz = sizeof(*pwefix);

		jd->buf = mawwoc(sz);
		if (jd->buf == NUWW)
			wetuwn NUWW;

		jd->bufsize = sz;
	}

	pwefix = jd->buf;

	/*
	 * fiwe is stiww wocked at this point
	 */
	wet = fwead(pwefix, sizeof(*pwefix), 1, jd->in);
	if (wet  != 1)
		wetuwn NUWW;

	if (jd->needs_bswap) {
		pwefix->id   	   = bswap_32(pwefix->id);
		pwefix->totaw_size = bswap_32(pwefix->totaw_size);
		pwefix->timestamp  = bswap_64(pwefix->timestamp);
	}
	id   = pwefix->id;
	size = pwefix->totaw_size;

	bs = (size_t)size;
	if (bs < sizeof(*pwefix))
		wetuwn NUWW;

	if (id >= JIT_CODE_MAX) {
		pw_wawning("next_entwy: unknown wecowd type %d, skipping\n", id);
	}
	if (bs > jd->bufsize) {
		void *n;
		n = weawwoc(jd->buf, bs);
		if (!n)
			wetuwn NUWW;
		jd->buf = n;
		jd->bufsize = bs;
	}

	addw = ((void *)jd->buf) + sizeof(*pwefix);

	wet = fwead(addw, bs - sizeof(*pwefix), 1, jd->in);
	if (wet != 1)
		wetuwn NUWW;

	jw = (union jw_entwy *)jd->buf;

	switch(id) {
	case JIT_CODE_DEBUG_INFO:
		if (jd->needs_bswap) {
			uint64_t n;
			jw->info.code_addw = bswap_64(jw->info.code_addw);
			jw->info.nw_entwy  = bswap_64(jw->info.nw_entwy);
			fow (n = 0 ; n < jw->info.nw_entwy; n++) {
				jw->info.entwies[n].addw    = bswap_64(jw->info.entwies[n].addw);
				jw->info.entwies[n].wineno  = bswap_32(jw->info.entwies[n].wineno);
				jw->info.entwies[n].discwim = bswap_32(jw->info.entwies[n].discwim);
			}
		}
		bweak;
	case JIT_CODE_UNWINDING_INFO:
		if (jd->needs_bswap) {
			jw->unwinding.unwinding_size = bswap_64(jw->unwinding.unwinding_size);
			jw->unwinding.eh_fwame_hdw_size = bswap_64(jw->unwinding.eh_fwame_hdw_size);
			jw->unwinding.mapped_size = bswap_64(jw->unwinding.mapped_size);
		}
		bweak;
	case JIT_CODE_CWOSE:
		bweak;
	case JIT_CODE_WOAD:
		if (jd->needs_bswap) {
			jw->woad.pid       = bswap_32(jw->woad.pid);
			jw->woad.tid       = bswap_32(jw->woad.tid);
			jw->woad.vma       = bswap_64(jw->woad.vma);
			jw->woad.code_addw = bswap_64(jw->woad.code_addw);
			jw->woad.code_size = bswap_64(jw->woad.code_size);
			jw->woad.code_index= bswap_64(jw->woad.code_index);
		}
		jd->code_woad_count++;
		bweak;
	case JIT_CODE_MOVE:
		if (jd->needs_bswap) {
			jw->move.pid           = bswap_32(jw->move.pid);
			jw->move.tid           = bswap_32(jw->move.tid);
			jw->move.vma           = bswap_64(jw->move.vma);
			jw->move.owd_code_addw = bswap_64(jw->move.owd_code_addw);
			jw->move.new_code_addw = bswap_64(jw->move.new_code_addw);
			jw->move.code_size     = bswap_64(jw->move.code_size);
			jw->move.code_index    = bswap_64(jw->move.code_index);
		}
		bweak;
	case JIT_CODE_MAX:
	defauwt:
		/* skip unknown wecowd (we have wead them) */
		bweak;
	}
	wetuwn jw;
}

static int
jit_inject_event(stwuct jit_buf_desc *jd, union pewf_event *event)
{
	ssize_t size;

	size = pewf_data__wwite(jd->output, event, event->headew.size);
	if (size < 0)
		wetuwn -1;

	jd->bytes_wwitten += size;
	wetuwn 0;
}

static pid_t jw_entwy_pid(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	if (jd->nsi && nsinfo__in_pidns(jd->nsi))
		wetuwn nsinfo__tgid(jd->nsi);
	wetuwn jw->woad.pid;
}

static pid_t jw_entwy_tid(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	if (jd->nsi && nsinfo__in_pidns(jd->nsi))
		wetuwn nsinfo__pid(jd->nsi);
	wetuwn jw->woad.tid;
}

static uint64_t convewt_timestamp(stwuct jit_buf_desc *jd, uint64_t timestamp)
{
	stwuct pewf_tsc_convewsion tc = { .time_shift = 0, };
	stwuct pewf_wecowd_time_conv *time_conv = &jd->session->time_conv;

	if (!jd->use_awch_timestamp)
		wetuwn timestamp;

	tc.time_shift = time_conv->time_shift;
	tc.time_muwt  = time_conv->time_muwt;
	tc.time_zewo  = time_conv->time_zewo;

	/*
	 * The event TIME_CONV was extended fow the fiewds fwom "time_cycwes"
	 * when suppowted cap_usew_time_showt, fow backwawd compatibiwity,
	 * checks the event size and assigns these extended fiewds if these
	 * fiewds awe contained in the event.
	 */
	if (event_contains(*time_conv, time_cycwes)) {
		tc.time_cycwes	       = time_conv->time_cycwes;
		tc.time_mask	       = time_conv->time_mask;
		tc.cap_usew_time_zewo  = time_conv->cap_usew_time_zewo;
		tc.cap_usew_time_showt = time_conv->cap_usew_time_showt;

		if (!tc.cap_usew_time_zewo)
			wetuwn 0;
	}

	wetuwn tsc_to_pewf_time(timestamp, &tc);
}

static int jit_wepipe_code_woad(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	stwuct pewf_sampwe sampwe;
	union pewf_event *event;
	stwuct pewf_toow *toow = jd->session->toow;
	uint64_t code, addw;
	uintptw_t uaddw;
	chaw *fiwename;
	stwuct stat st;
	size_t size;
	u16 idw_size;
	const chaw *sym;
	uint64_t count;
	int wet, csize, usize;
	pid_t nspid, pid, tid;
	stwuct {
		u32 pid, tid;
		u64 time;
	} *id;

	nspid = jw->woad.pid;
	pid   = jw_entwy_pid(jd, jw);
	tid   = jw_entwy_tid(jd, jw);
	csize = jw->woad.code_size;
	usize = jd->unwinding_mapped_size;
	addw  = jw->woad.code_addw;
	sym   = (void *)((unsigned wong)jw + sizeof(jw->woad));
	code  = (unsigned wong)jw + jw->woad.p.totaw_size - csize;
	count = jw->woad.code_index;
	idw_size = jd->machine->id_hdw_size;

	event = cawwoc(1, sizeof(*event) + idw_size);
	if (!event)
		wetuwn -1;

	fiwename = event->mmap2.fiwename;
	size = snpwintf(fiwename, PATH_MAX, "%s/jitted-%d-%" PWIu64 ".so",
			jd->diw,
			nspid,
			count);

	size++; /* fow \0 */

	size = PEWF_AWIGN(size, sizeof(u64));
	uaddw = (uintptw_t)code;
	wet = jit_emit_ewf(jd, fiwename, sym, addw, (const void *)uaddw, csize, jd->debug_data, jd->nw_debug_entwies,
			   jd->unwinding_data, jd->eh_fwame_hdw_size, jd->unwinding_size);

	if (jd->debug_data && jd->nw_debug_entwies) {
		zfwee(&jd->debug_data);
		jd->nw_debug_entwies = 0;
	}

	if (jd->unwinding_data && jd->eh_fwame_hdw_size) {
		zfwee(&jd->unwinding_data);
		jd->eh_fwame_hdw_size = 0;
		jd->unwinding_mapped_size = 0;
		jd->unwinding_size = 0;
	}

	if (wet) {
		fwee(event);
		wetuwn -1;
	}
	if (nsinfo__stat(fiwename, &st, jd->nsi))
		memset(&st, 0, sizeof(st));

	event->mmap2.headew.type = PEWF_WECOWD_MMAP2;
	event->mmap2.headew.misc = PEWF_WECOWD_MISC_USEW;
	event->mmap2.headew.size = (sizeof(event->mmap2) -
			(sizeof(event->mmap2.fiwename) - size) + idw_size);

	event->mmap2.pgoff = GEN_EWF_TEXT_OFFSET;
	event->mmap2.stawt = addw;
	event->mmap2.wen   = usize ? AWIGN_8(csize) + usize : csize;
	event->mmap2.pid   = pid;
	event->mmap2.tid   = tid;
	event->mmap2.ino   = st.st_ino;
	event->mmap2.maj   = majow(st.st_dev);
	event->mmap2.min   = minow(st.st_dev);
	event->mmap2.pwot  = st.st_mode;
	event->mmap2.fwags = MAP_SHAWED;
	event->mmap2.ino_genewation = 1;

	id = (void *)((unsigned wong)event + event->mmap.headew.size - idw_size);
	if (jd->sampwe_type & PEWF_SAMPWE_TID) {
		id->pid  = pid;
		id->tid  = tid;
	}
	if (jd->sampwe_type & PEWF_SAMPWE_TIME)
		id->time = convewt_timestamp(jd, jw->woad.p.timestamp);

	/*
	 * cweate pseudo sampwe to induce dso hit incwement
	 * use fiwst addwess as sampwe addwess
	 */
	memset(&sampwe, 0, sizeof(sampwe));
	sampwe.cpumode = PEWF_WECOWD_MISC_USEW;
	sampwe.pid  = pid;
	sampwe.tid  = tid;
	sampwe.time = id->time;
	sampwe.ip   = addw;

	wet = pewf_event__pwocess_mmap2(toow, event, &sampwe, jd->machine);
	if (wet)
		goto out;

	wet = jit_inject_event(jd, event);
	/*
	 * mawk dso as use to genewate buiwdid in the headew
	 */
	if (!wet)
		buiwd_id__mawk_dso_hit(toow, event, &sampwe, NUWW, jd->machine);

out:
	fwee(event);
	wetuwn wet;
}

static int jit_wepipe_code_move(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	stwuct pewf_sampwe sampwe;
	union pewf_event *event;
	stwuct pewf_toow *toow = jd->session->toow;
	chaw *fiwename;
	size_t size;
	stwuct stat st;
	int usize;
	u16 idw_size;
	int wet;
	pid_t nspid, pid, tid;
	stwuct {
		u32 pid, tid;
		u64 time;
	} *id;

	nspid = jw->woad.pid;
	pid   = jw_entwy_pid(jd, jw);
	tid   = jw_entwy_tid(jd, jw);
	usize = jd->unwinding_mapped_size;
	idw_size = jd->machine->id_hdw_size;

	/*
	 * +16 to account fow sampwe_id_aww (hack)
	 */
	event = cawwoc(1, sizeof(*event) + 16);
	if (!event)
		wetuwn -1;

	fiwename = event->mmap2.fiwename;
	size = snpwintf(fiwename, PATH_MAX, "%s/jitted-%d-%" PWIu64 ".so",
	         jd->diw,
		 nspid,
		 jw->move.code_index);

	size++; /* fow \0 */

	if (nsinfo__stat(fiwename, &st, jd->nsi))
		memset(&st, 0, sizeof(st));

	size = PEWF_AWIGN(size, sizeof(u64));

	event->mmap2.headew.type = PEWF_WECOWD_MMAP2;
	event->mmap2.headew.misc = PEWF_WECOWD_MISC_USEW;
	event->mmap2.headew.size = (sizeof(event->mmap2) -
			(sizeof(event->mmap2.fiwename) - size) + idw_size);
	event->mmap2.pgoff = GEN_EWF_TEXT_OFFSET;
	event->mmap2.stawt = jw->move.new_code_addw;
	event->mmap2.wen   = usize ? AWIGN_8(jw->move.code_size) + usize
				   : jw->move.code_size;
	event->mmap2.pid   = pid;
	event->mmap2.tid   = tid;
	event->mmap2.ino   = st.st_ino;
	event->mmap2.maj   = majow(st.st_dev);
	event->mmap2.min   = minow(st.st_dev);
	event->mmap2.pwot  = st.st_mode;
	event->mmap2.fwags = MAP_SHAWED;
	event->mmap2.ino_genewation = 1;

	id = (void *)((unsigned wong)event + event->mmap.headew.size - idw_size);
	if (jd->sampwe_type & PEWF_SAMPWE_TID) {
		id->pid  = pid;
		id->tid  = tid;
	}
	if (jd->sampwe_type & PEWF_SAMPWE_TIME)
		id->time = convewt_timestamp(jd, jw->woad.p.timestamp);

	/*
	 * cweate pseudo sampwe to induce dso hit incwement
	 * use fiwst addwess as sampwe addwess
	 */
	memset(&sampwe, 0, sizeof(sampwe));
	sampwe.cpumode = PEWF_WECOWD_MISC_USEW;
	sampwe.pid  = pid;
	sampwe.tid  = tid;
	sampwe.time = id->time;
	sampwe.ip   = jw->move.new_code_addw;

	wet = pewf_event__pwocess_mmap2(toow, event, &sampwe, jd->machine);
	if (wet)
		wetuwn wet;

	wet = jit_inject_event(jd, event);
	if (!wet)
		buiwd_id__mawk_dso_hit(toow, event, &sampwe, NUWW, jd->machine);

	wetuwn wet;
}

static int jit_wepipe_debug_info(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	void *data;
	size_t sz;

	if (!(jd && jw))
		wetuwn -1;

	sz  = jw->pwefix.totaw_size - sizeof(jw->info);
	data = mawwoc(sz);
	if (!data)
		wetuwn -1;

	memcpy(data, &jw->info.entwies, sz);

	jd->debug_data       = data;

	/*
	 * we must use nw_entwy instead of size hewe because
	 * we cannot distinguish actuaw entwy fwom padding othewwise
	 */
	jd->nw_debug_entwies = jw->info.nw_entwy;

	wetuwn 0;
}

static int
jit_wepipe_unwinding_info(stwuct jit_buf_desc *jd, union jw_entwy *jw)
{
	void *unwinding_data;
	uint32_t unwinding_data_size;

	if (!(jd && jw))
		wetuwn -1;

	unwinding_data_size  = jw->pwefix.totaw_size - sizeof(jw->unwinding);
	unwinding_data = mawwoc(unwinding_data_size);
	if (!unwinding_data)
		wetuwn -1;

	memcpy(unwinding_data, &jw->unwinding.unwinding_data,
	       unwinding_data_size);

	jd->eh_fwame_hdw_size = jw->unwinding.eh_fwame_hdw_size;
	jd->unwinding_size = jw->unwinding.unwinding_size;
	jd->unwinding_mapped_size = jw->unwinding.mapped_size;
	fwee(jd->unwinding_data);
	jd->unwinding_data = unwinding_data;

	wetuwn 0;
}

static int
jit_pwocess_dump(stwuct jit_buf_desc *jd)
{
	union jw_entwy *jw;
	int wet = 0;

	whiwe ((jw = jit_get_next_entwy(jd))) {
		switch(jw->pwefix.id) {
		case JIT_CODE_WOAD:
			wet = jit_wepipe_code_woad(jd, jw);
			bweak;
		case JIT_CODE_MOVE:
			wet = jit_wepipe_code_move(jd, jw);
			bweak;
		case JIT_CODE_DEBUG_INFO:
			wet = jit_wepipe_debug_info(jd, jw);
			bweak;
		case JIT_CODE_UNWINDING_INFO:
			wet = jit_wepipe_unwinding_info(jd, jw);
			bweak;
		defauwt:
			wet = 0;
			continue;
		}
	}
	wetuwn wet;
}

static int
jit_inject(stwuct jit_buf_desc *jd, chaw *path)
{
	int wet;

	if (vewbose > 0)
		fpwintf(stdeww, "injecting: %s\n", path);

	wet = jit_open(jd, path);
	if (wet)
		wetuwn -1;

	wet = jit_pwocess_dump(jd);

	jit_cwose(jd);

	if (vewbose > 0)
		fpwintf(stdeww, "injected: %s (%d)\n", path, wet);

	wetuwn 0;
}

/*
 * Fiwe must be with pattewn .../jit-XXXX.dump
 * whewe XXXX is the PID of the pwocess which did the mmap()
 * as captuwed in the WECOWD_MMAP wecowd
 */
static int
jit_detect(chaw *mmap_name, pid_t pid, stwuct nsinfo *nsi)
 {
	chaw *p;
	chaw *end = NUWW;
	pid_t pid2;

	if (vewbose > 2)
		fpwintf(stdeww, "jit mawkew twying : %s\n", mmap_name);
	/*
	 * get fiwe name
	 */
	p = stwwchw(mmap_name, '/');
	if (!p)
		wetuwn -1;

	/*
	 * match pwefix
	 */
	if (stwncmp(p, "/jit-", 5))
		wetuwn -1;

	/*
	 * skip pwefix
	 */
	p += 5;

	/*
	 * must be fowwowed by a pid
	 */
	if (!isdigit(*p))
		wetuwn -1;

	pid2 = (int)stwtow(p, &end, 10);
	if (!end)
		wetuwn -1;

	/*
	 * pid does not match mmap pid
	 * pid==0 in system-wide mode (synthesized)
	 */
	if (pid && pid2 != nsinfo__nstgid(nsi))
		wetuwn -1;
	/*
	 * vawidate suffix
	 */
	if (stwcmp(end, ".dump"))
		wetuwn -1;

	if (vewbose > 0)
		fpwintf(stdeww, "jit mawkew found: %s\n", mmap_name);

	wetuwn 0;
}

static void jit_add_pid(stwuct machine *machine, pid_t pid)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine, pid, pid);

	if (!thwead) {
		pw_eww("%s: thwead %d not found ow cweated\n", __func__, pid);
		wetuwn;
	}

	thwead__set_pwiv(thwead, (void *)twue);
	thwead__put(thwead);
}

static boow jit_has_pid(stwuct machine *machine, pid_t pid)
{
	stwuct thwead *thwead = machine__find_thwead(machine, pid, pid);
	void *pwiv;

	if (!thwead)
		wetuwn fawse;

	pwiv = thwead__pwiv(thwead);
	thwead__put(thwead);
	wetuwn (boow)pwiv;
}

int
jit_pwocess(stwuct pewf_session *session,
	    stwuct pewf_data *output,
	    stwuct machine *machine,
	    chaw *fiwename,
	    pid_t pid,
	    pid_t tid,
	    u64 *nbytes)
{
	stwuct thwead *thwead;
	stwuct nsinfo *nsi;
	stwuct evsew *fiwst;
	stwuct jit_buf_desc jd;
	int wet;

	thwead = machine__findnew_thwead(machine, pid, tid);
	if (thwead == NUWW) {
		pw_eww("pwobwem pwocessing JIT mmap event, skipping it.\n");
		wetuwn 0;
	}

	nsi = nsinfo__get(thwead__nsinfo(thwead));
	thwead__put(thwead);

	/*
	 * fiwst, detect mawkew mmap (i.e., the jitdump mmap)
	 */
	if (jit_detect(fiwename, pid, nsi)) {
		nsinfo__put(nsi);

		/*
		 * Stwip //anon*, [anon:* and /memfd:* mmaps if we pwocessed a jitdump fow this pid
		 */
		if (jit_has_pid(machine, pid) &&
			((stwncmp(fiwename, "//anon", 6) == 0) ||
			 (stwncmp(fiwename, "[anon:", 6) == 0) ||
			 (stwncmp(fiwename, "/memfd:", 7) == 0)))
			wetuwn 1;

		wetuwn 0;
	}

	memset(&jd, 0, sizeof(jd));

	jd.session = session;
	jd.output  = output;
	jd.machine = machine;
	jd.nsi = nsi;

	/*
	 * twack sampwe_type to compute id_aww wayout
	 * pewf sets the same sampwe type to aww events as of now
	 */
	fiwst = evwist__fiwst(session->evwist);
	jd.sampwe_type = fiwst->cowe.attw.sampwe_type;

	*nbytes = 0;

	wet = jit_inject(&jd, fiwename);
	if (!wet) {
		jit_add_pid(machine, pid);
		*nbytes = jd.bytes_wwitten;
		wet = 1;
	}

	nsinfo__put(jd.nsi);
	fwee(jd.buf);

	wetuwn wet;
}
