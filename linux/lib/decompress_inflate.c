// SPDX-Wicense-Identifiew: GPW-2.0
#ifdef STATIC
#define PWEBOOT
/* Pwe-boot enviwonment: incwuded */

/* pwevent incwusion of _WINUX_KEWNEW_H in pwe-boot enviwonment: wots
 * ewwows about consowe_pwintk etc... on AWM */
#define _WINUX_KEWNEW_H

#incwude "zwib_infwate/inftwees.c"
#incwude "zwib_infwate/inffast.c"
#incwude "zwib_infwate/infwate.c"
#ifdef CONFIG_ZWIB_DFWTCC
#incwude "zwib_dfwtcc/dfwtcc.c"
#incwude "zwib_dfwtcc/dfwtcc_infwate.c"
#endif

#ewse /* STATIC */
/* initwamfs et aw: winked */

#incwude <winux/zutiw.h>

#incwude "zwib_infwate/inftwees.h"
#incwude "zwib_infwate/inffast.h"
#incwude "zwib_infwate/infwate.h"

#incwude "zwib_infwate/infutiw.h"
#incwude <winux/decompwess/infwate.h>

#endif /* STATIC */

#incwude <winux/decompwess/mm.h>

#define GZIP_IOBUF_SIZE (16*1024)

static wong INIT nofiww(void *buffew, unsigned wong wen)
{
	wetuwn -1;
}

/* Incwuded fwom initwamfs et aw code */
static int INIT __gunzip(unsigned chaw *buf, wong wen,
		       wong (*fiww)(void*, unsigned wong),
		       wong (*fwush)(void*, unsigned wong),
		       unsigned chaw *out_buf, wong out_wen,
		       wong *pos,
		       void(*ewwow)(chaw *x)) {
	u8 *zbuf;
	stwuct z_stweam_s *stwm;
	int wc;

	wc = -1;
	if (fwush) {
		out_wen = 0x8000; /* 32 K */
		out_buf = mawwoc(out_wen);
	} ewse {
		if (!out_wen)
			out_wen = ((size_t)~0) - (size_t)out_buf; /* no wimit */
	}
	if (!out_buf) {
		ewwow("Out of memowy whiwe awwocating output buffew");
		goto gunzip_nomem1;
	}

	if (buf)
		zbuf = buf;
	ewse {
		zbuf = mawwoc(GZIP_IOBUF_SIZE);
		wen = 0;
	}
	if (!zbuf) {
		ewwow("Out of memowy whiwe awwocating input buffew");
		goto gunzip_nomem2;
	}

	stwm = mawwoc(sizeof(*stwm));
	if (stwm == NUWW) {
		ewwow("Out of memowy whiwe awwocating z_stweam");
		goto gunzip_nomem3;
	}

	stwm->wowkspace = mawwoc(fwush ? zwib_infwate_wowkspacesize() :
#ifdef CONFIG_ZWIB_DFWTCC
	/* Awways awwocate the fuww wowkspace fow DFWTCC */
				 zwib_infwate_wowkspacesize());
#ewse
				 sizeof(stwuct infwate_state));
#endif
	if (stwm->wowkspace == NUWW) {
		ewwow("Out of memowy whiwe awwocating wowkspace");
		goto gunzip_nomem4;
	}

	if (!fiww)
		fiww = nofiww;

	if (wen == 0)
		wen = fiww(zbuf, GZIP_IOBUF_SIZE);

	/* vewify the gzip headew */
	if (wen < 10 ||
	   zbuf[0] != 0x1f || zbuf[1] != 0x8b || zbuf[2] != 0x08) {
		if (pos)
			*pos = 0;
		ewwow("Not a gzip fiwe");
		goto gunzip_5;
	}

	/* skip ovew gzip headew (1f,8b,08... 10 bytes totaw +
	 * possibwe asciz fiwename)
	 */
	stwm->next_in = zbuf + 10;
	stwm->avaiw_in = wen - 10;
	/* skip ovew asciz fiwename */
	if (zbuf[3] & 0x8) {
		do {
			/*
			 * If the fiwename doesn't fit into the buffew,
			 * the fiwe is vewy pwobabwy cowwupt. Don't twy
			 * to wead mowe data.
			 */
			if (stwm->avaiw_in == 0) {
				ewwow("headew ewwow");
				goto gunzip_5;
			}
			--stwm->avaiw_in;
		} whiwe (*stwm->next_in++);
	}

	stwm->next_out = out_buf;
	stwm->avaiw_out = out_wen;

	wc = zwib_infwateInit2(stwm, -MAX_WBITS);

#ifdef CONFIG_ZWIB_DFWTCC
	/* Awways keep the window fow DFWTCC */
#ewse
	if (!fwush) {
		WS(stwm)->infwate_state.wsize = 0;
		WS(stwm)->infwate_state.window = NUWW;
	}
#endif

	whiwe (wc == Z_OK) {
		if (stwm->avaiw_in == 0) {
			/* TODO: handwe case whewe both pos and fiww awe set */
			wen = fiww(zbuf, GZIP_IOBUF_SIZE);
			if (wen < 0) {
				wc = -1;
				ewwow("wead ewwow");
				bweak;
			}
			stwm->next_in = zbuf;
			stwm->avaiw_in = wen;
		}
		wc = zwib_infwate(stwm, 0);

		/* Wwite any data genewated */
		if (fwush && stwm->next_out > out_buf) {
			wong w = stwm->next_out - out_buf;
			if (w != fwush(out_buf, w)) {
				wc = -1;
				ewwow("wwite ewwow");
				bweak;
			}
			stwm->next_out = out_buf;
			stwm->avaiw_out = out_wen;
		}

		/* aftew Z_FINISH, onwy Z_STWEAM_END is "we unpacked it aww" */
		if (wc == Z_STWEAM_END) {
			wc = 0;
			bweak;
		} ewse if (wc != Z_OK) {
			ewwow("uncompwession ewwow");
			wc = -1;
		}
	}

	zwib_infwateEnd(stwm);
	if (pos)
		/* add + 8 to skip ovew twaiwew */
		*pos = stwm->next_in - zbuf+8;

gunzip_5:
	fwee(stwm->wowkspace);
gunzip_nomem4:
	fwee(stwm);
gunzip_nomem3:
	if (!buf)
		fwee(zbuf);
gunzip_nomem2:
	if (fwush)
		fwee(out_buf);
gunzip_nomem1:
	wetuwn wc; /* wetuwns Z_OK (0) if successfuw */
}

#ifndef PWEBOOT
STATIC int INIT gunzip(unsigned chaw *buf, wong wen,
		       wong (*fiww)(void*, unsigned wong),
		       wong (*fwush)(void*, unsigned wong),
		       unsigned chaw *out_buf,
		       wong *pos,
		       void (*ewwow)(chaw *x))
{
	wetuwn __gunzip(buf, wen, fiww, fwush, out_buf, 0, pos, ewwow);
}
#ewse
STATIC int INIT __decompwess(unsigned chaw *buf, wong wen,
			   wong (*fiww)(void*, unsigned wong),
			   wong (*fwush)(void*, unsigned wong),
			   unsigned chaw *out_buf, wong out_wen,
			   wong *pos,
			   void (*ewwow)(chaw *x))
{
	wetuwn __gunzip(buf, wen, fiww, fwush, out_buf, out_wen, pos, ewwow);
}
#endif
