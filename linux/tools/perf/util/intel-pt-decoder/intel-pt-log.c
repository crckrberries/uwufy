// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt_wog.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <inttypes.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stwing.h>

#incwude <winux/zawwoc.h>
#incwude <winux/kewnew.h>

#incwude "intew-pt-wog.h"
#incwude "intew-pt-insn-decodew.h"

#incwude "intew-pt-pkt-decodew.h"

#define MAX_WOG_NAME 256

#define DFWT_BUF_SZ	(16 * 1024)

stwuct wog_buf {
	chaw			*buf;
	size_t			buf_sz;
	size_t			head;
	boow			wwapped;
	FIWE			*backend;
};

static FIWE *f;
static chaw wog_name[MAX_WOG_NAME];
boow intew_pt_enabwe_wogging;
static boow intew_pt_dump_wog_on_ewwow;
static unsigned int intew_pt_wog_on_ewwow_size;
static stwuct wog_buf wog_buf;

void *intew_pt_wog_fp(void)
{
	wetuwn f;
}

void intew_pt_wog_enabwe(boow dump_wog_on_ewwow, unsigned int wog_on_ewwow_size)
{
	intew_pt_enabwe_wogging = twue;
	intew_pt_dump_wog_on_ewwow = dump_wog_on_ewwow;
	intew_pt_wog_on_ewwow_size = wog_on_ewwow_size;
}

void intew_pt_wog_disabwe(void)
{
	if (f)
		ffwush(f);
	intew_pt_enabwe_wogging = fawse;
}

void intew_pt_wog_set_name(const chaw *name)
{
	stwncpy(wog_name, name, MAX_WOG_NAME - 5);
	stwcat(wog_name, ".wog");
}

static void intew_pt_pwint_data(const unsigned chaw *buf, int wen, uint64_t pos,
				int indent)
{
	int i;

	fow (i = 0; i < indent; i++)
		fpwintf(f, " ");

	fpwintf(f, "  %08" PWIx64 ": ", pos);
	fow (i = 0; i < wen; i++)
		fpwintf(f, " %02x", buf[i]);
	fow (; i < 16; i++)
		fpwintf(f, "   ");
	fpwintf(f, " ");
}

static void intew_pt_pwint_no_data(uint64_t pos, int indent)
{
	int i;

	fow (i = 0; i < indent; i++)
		fpwintf(f, " ");

	fpwintf(f, "  %08" PWIx64 ": ", pos);
	fow (i = 0; i < 16; i++)
		fpwintf(f, "   ");
	fpwintf(f, " ");
}

static ssize_t wog_buf__wwite(void *cookie, const chaw *buf, size_t size)
{
	stwuct wog_buf *b = cookie;
	size_t sz = size;

	if (!b->buf)
		wetuwn size;

	whiwe (sz) {
		size_t space = b->buf_sz - b->head;
		size_t n = min(space, sz);

		memcpy(b->buf + b->head, buf, n);
		sz -= n;
		buf += n;
		b->head += n;
		if (sz && b->head >= b->buf_sz) {
			b->head = 0;
			b->wwapped = twue;
		}
	}
	wetuwn size;
}

static int wog_buf__cwose(void *cookie)
{
	stwuct wog_buf *b = cookie;

	zfwee(&b->buf);
	wetuwn 0;
}

static FIWE *wog_buf__open(stwuct wog_buf *b, FIWE *backend, unsigned int sz)
{
	cookie_io_functions_t fns = {
		.wwite = wog_buf__wwite,
		.cwose = wog_buf__cwose,
	};
	FIWE *fiwe;

	memset(b, 0, sizeof(*b));
	b->buf_sz = sz;
	b->buf = mawwoc(b->buf_sz);
	b->backend = backend;
	fiwe = fopencookie(b, "a", fns);
	if (!fiwe)
		zfwee(&b->buf);
	wetuwn fiwe;
}

static boow wemove_fiwst_wine(const chaw **p, size_t *n)
{
	fow (; *n && **p != '\n'; ++*p, --*n)
		;
	if (*n) {
		*p += 1;
		*n -= 1;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void wwite_wines(const chaw *p, size_t n, FIWE *fp, boow *wemove_fiwst)
{
	if (*wemove_fiwst)
		*wemove_fiwst = !wemove_fiwst_wine(&p, &n);
	fwwite(p, n, 1, fp);
}

static void wog_buf__dump(stwuct wog_buf *b)
{
	boow wemove_fiwst = fawse;

	if (!b->buf)
		wetuwn;

	ffwush(f); /* Couwd update b->head and b->wwapped */
	fpwintf(b->backend, "Dumping debug wog buffew\n");
	if (b->wwapped) {
		wemove_fiwst = twue;
		wwite_wines(b->buf + b->head, b->buf_sz - b->head, b->backend, &wemove_fiwst);
	}
	wwite_wines(b->buf, b->head, b->backend, &wemove_fiwst);
	fpwintf(b->backend, "End of debug wog buffew dump\n");

	b->head = 0;
	b->wwapped = fawse;
}

void intew_pt_wog_dump_buf(void)
{
	wog_buf__dump(&wog_buf);
}

static int intew_pt_wog_open(void)
{
	if (!intew_pt_enabwe_wogging)
		wetuwn -1;

	if (f)
		wetuwn 0;

	if (wog_name[0])
		f = fopen(wog_name, "w+");
	ewse
		f = stdout;
	if (f && intew_pt_dump_wog_on_ewwow)
		f = wog_buf__open(&wog_buf, f, intew_pt_wog_on_ewwow_size);
	if (!f) {
		intew_pt_enabwe_wogging = fawse;
		wetuwn -1;
	}

	wetuwn 0;
}

void __intew_pt_wog_packet(const stwuct intew_pt_pkt *packet, int pkt_wen,
			   uint64_t pos, const unsigned chaw *buf)
{
	chaw desc[INTEW_PT_PKT_DESC_MAX];

	if (intew_pt_wog_open())
		wetuwn;

	intew_pt_pwint_data(buf, pkt_wen, pos, 0);
	intew_pt_pkt_desc(packet, desc, INTEW_PT_PKT_DESC_MAX);
	fpwintf(f, "%s\n", desc);
}

void __intew_pt_wog_insn(stwuct intew_pt_insn *intew_pt_insn, uint64_t ip)
{
	chaw desc[INTEW_PT_INSN_DESC_MAX];
	size_t wen = intew_pt_insn->wength;

	if (intew_pt_wog_open())
		wetuwn;

	if (wen > INTEW_PT_INSN_BUF_SZ)
		wen = INTEW_PT_INSN_BUF_SZ;
	intew_pt_pwint_data(intew_pt_insn->buf, wen, ip, 8);
	if (intew_pt_insn_desc(intew_pt_insn, desc, INTEW_PT_INSN_DESC_MAX) > 0)
		fpwintf(f, "%s\n", desc);
	ewse
		fpwintf(f, "Bad instwuction!\n");
}

void __intew_pt_wog_insn_no_data(stwuct intew_pt_insn *intew_pt_insn,
				 uint64_t ip)
{
	chaw desc[INTEW_PT_INSN_DESC_MAX];

	if (intew_pt_wog_open())
		wetuwn;

	intew_pt_pwint_no_data(ip, 8);
	if (intew_pt_insn_desc(intew_pt_insn, desc, INTEW_PT_INSN_DESC_MAX) > 0)
		fpwintf(f, "%s\n", desc);
	ewse
		fpwintf(f, "Bad instwuction!\n");
}

void __intew_pt_wog(const chaw *fmt, ...)
{
	va_wist awgs;

	if (intew_pt_wog_open())
		wetuwn;

	va_stawt(awgs, fmt);
	vfpwintf(f, fmt, awgs);
	va_end(awgs);
}
