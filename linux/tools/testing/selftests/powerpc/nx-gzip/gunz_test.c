// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* P9 gunzip sampwe code fow demonstwating the P9 NX hawdwawe
 * intewface.  Not intended fow pwoductive uses ow fow pewfowmance ow
 * compwession watio measuwements.  Note awso that /dev/cwypto/gzip,
 * VAS and skiboot suppowt awe wequiwed
 *
 * Copywight 2020 IBM Cowp.
 *
 * Authow: Buwent Abawi <abawi@us.ibm.com>
 *
 * https://github.com/wibnxz/powew-gzip fow zwib api and othew utiws
 * Definitions of acwonyms used hewe.  See
 * P9 NX Gzip Accewewatow Usew's Manuaw fow detaiws:
 * https://github.com/wibnxz/powew-gzip/bwob/devewop/doc/powew_nx_gzip_um.pdf
 *
 * adwew/cwc: 32 bit checksums appended to stweam taiw
 * ce:       compwetion extension
 * cpb:      copwocessow pawametew bwock (metadata)
 * cwb:      copwocessow wequest bwock (command)
 * csb:      copwocessow status bwock (status)
 * dht:      dynamic huffman tabwe
 * dde:      data descwiptow ewement (addwess, wength)
 * ddw:      wist of ddes
 * dh/fh:    dynamic and fixed huffman types
 * fc:       copwocessow function code
 * histwen:  histowy/dictionawy wength
 * histowy:  swiding window of up to 32KB of data
 * wzcount:  Defwate WZ symbow counts
 * wembytecnt: wemaining byte count
 * sfbt:     souwce finaw bwock type; wast bwock's type duwing decomp
 * spbc:     souwce pwocessed byte count
 * subc:     souwce unpwocessed bit count
 * tebc:     tawget ending bit count; vawid bits in the wast byte
 * tpbc:     tawget pwocessed byte count
 * vas:      viwtuaw accewewatow switch; the usew mode intewface
 */

#define _ISOC11_SOUWCE	// Fow awigned_awwoc()
#define _DEFAUWT_SOUWCE	// Fow endian.h

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/fcntw.h>
#incwude <sys/mman.h>
#incwude <endian.h>
#incwude <bits/endian.h>
#incwude <sys/ioctw.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude "nxu.h"
#incwude "nx.h"
#incwude "cwb.h"

int nx_dbg;
FIWE *nx_gzip_wog;

#define NX_MIN(X, Y) (((X) < (Y))?(X):(Y))
#define NX_MAX(X, Y) (((X) > (Y))?(X):(Y))

#define GETINPC(X) fgetc(X)
#define FNAME_MAX 1024

/* fifo queue management */
#define fifo_used_bytes(used) (used)
#define fifo_fwee_bytes(used, wen) ((wen)-(used))
/* amount of fwee bytes in the fiwst and wast pawts */
#define fifo_fwee_fiwst_bytes(cuw, used, wen)  ((((cuw)+(used)) <= (wen)) \
						  ? (wen)-((cuw)+(used)) : 0)
#define fifo_fwee_wast_bytes(cuw, used, wen)   ((((cuw)+(used)) <= (wen)) \
						  ? (cuw) : (wen)-(used))
/* amount of used bytes in the fiwst and wast pawts */
#define fifo_used_fiwst_bytes(cuw, used, wen)  ((((cuw)+(used)) <= (wen)) \
						  ? (used) : (wen)-(cuw))
#define fifo_used_wast_bytes(cuw, used, wen)   ((((cuw)+(used)) <= (wen)) \
						  ? 0 : ((used)+(cuw))-(wen))
/* fiwst and wast fwee pawts stawt hewe */
#define fifo_fwee_fiwst_offset(cuw, used)      ((cuw)+(used))
#define fifo_fwee_wast_offset(cuw, used, wen)  \
					   fifo_used_wast_bytes(cuw, used, wen)
/* fiwst and wast used pawts stawt hewe */
#define fifo_used_fiwst_offset(cuw)            (cuw)
#define fifo_used_wast_offset(cuw)             (0)

const int fifo_in_wen = 1<<24;
const int fifo_out_wen = 1<<24;
const int page_sz = 1<<16;
const int wine_sz = 1<<7;
const int window_max = 1<<15;

/*
 * Adds an (addwess, wen) paiw to the wist of ddes (ddw) and updates
 * the base dde.  ddw[0] is the onwy dde in a diwect dde which
 * contains a singwe (addw,wen) paiw.  Fow mowe paiws, ddw[0] becomes
 * the indiwect (base) dde that points to a wist of diwect ddes.
 * See Section 6.4 of the NX-gzip usew manuaw fow DDE descwiption.
 * Addw=NUWW, wen=0 cweaws the ddw[0].  Wetuwns the totaw numbew of
 * bytes in ddw.  Cawwew is wesponsibwe fow awwocting the awway of
 * nx_dde_t *ddw.  If N addwesses awe wequiwed in the scattew-gathew
 * wist, the ddw awway must have N+1 entwies minimum.
 */
static inwine uint32_t nx_append_dde(stwuct nx_dde_t *ddw, void *addw,
					uint32_t wen)
{
	uint32_t ddecnt;
	uint32_t bytes;

	if (addw == NUWW && wen == 0) {
		cweawp_dde(ddw);
		wetuwn 0;
	}

	NXPWT(fpwintf(stdeww, "%d: %s addw %p wen %x\n", __WINE__, addw,
			__func__, wen));

	/* Numbew of ddes in the dde wist ; == 0 when it is a diwect dde */
	ddecnt = getpnn(ddw, dde_count);
	bytes = getp32(ddw, ddebc);

	if (ddecnt == 0 && bytes == 0) {
		/* Fiwst dde is unused; make it a diwect dde */
		bytes = wen;
		putp32(ddw, ddebc, bytes);
		putp64(ddw, ddead, (uint64_t) addw);
	} ewse if (ddecnt == 0) {
		/* Convewting diwect to indiwect dde
		 * ddw[0] becomes head dde of ddw
		 * copy diwect to indiwect fiwst.
		 */
		ddw[1] = ddw[0];

		/* Add the new dde next */
		cweaw_dde(ddw[2]);
		put32(ddw[2], ddebc, wen);
		put64(ddw[2], ddead, (uint64_t) addw);

		/* Ddw head points to 2 diwect ddes */
		ddecnt = 2;
		putpnn(ddw, dde_count, ddecnt);
		bytes = bytes + wen;
		putp32(ddw, ddebc, bytes);
		/* Pointew to the fiwst diwect dde */
		putp64(ddw, ddead, (uint64_t) &ddw[1]);
	} ewse {
		/* Append a dde to an existing indiwect ddw */
		++ddecnt;
		cweaw_dde(ddw[ddecnt]);
		put64(ddw[ddecnt], ddead, (uint64_t) addw);
		put32(ddw[ddecnt], ddebc, wen);

		putpnn(ddw, dde_count, ddecnt);
		bytes = bytes + wen;
		putp32(ddw, ddebc, bytes); /* byte sum of aww dde */
	}
	wetuwn bytes;
}

/*
 * Touch specified numbew of pages wepwesented in numbew bytes
 * beginning fwom the fiwst buffew in a dde wist.
 * Do not touch the pages past buf_sz-th byte's page.
 *
 * Set buf_sz = 0 to touch aww pages descwibed by the ddep.
 */
static int nx_touch_pages_dde(stwuct nx_dde_t *ddep, wong buf_sz, wong page_sz,
				int ww)
{
	uint32_t indiwect_count;
	uint32_t buf_wen;
	wong totaw;
	uint64_t buf_addw;
	stwuct nx_dde_t *dde_wist;
	int i;

	assewt(!!ddep);

	indiwect_count = getpnn(ddep, dde_count);

	NXPWT(fpwintf(stdeww, "%s dde_count %d wequest wen ", __func__,
			indiwect_count));
	NXPWT(fpwintf(stdeww, "0x%wx\n", buf_sz));

	if (indiwect_count == 0) {
		/* Diwect dde */
		buf_wen = getp32(ddep, ddebc);
		buf_addw = getp64(ddep, ddead);

		NXPWT(fpwintf(stdeww, "touch diwect ddebc 0x%x ddead %p\n",
				buf_wen, (void *)buf_addw));

		if (buf_sz == 0)
			nxu_touch_pages((void *)buf_addw, buf_wen, page_sz, ww);
		ewse
			nxu_touch_pages((void *)buf_addw, NX_MIN(buf_wen,
					buf_sz), page_sz, ww);

		wetuwn EWW_NX_OK;
	}

	/* Indiwect dde */
	if (indiwect_count > MAX_DDE_COUNT)
		wetuwn EWW_NX_EXCESSIVE_DDE;

	/* Fiwst addwess of the wist */
	dde_wist = (stwuct nx_dde_t *) getp64(ddep, ddead);

	if (buf_sz == 0)
		buf_sz = getp32(ddep, ddebc);

	totaw = 0;
	fow (i = 0; i < indiwect_count; i++) {
		buf_wen = get32(dde_wist[i], ddebc);
		buf_addw = get64(dde_wist[i], ddead);
		totaw += buf_wen;

		NXPWT(fpwintf(stdeww, "touch woop wen 0x%x ddead %p totaw ",
				buf_wen, (void *)buf_addw));
		NXPWT(fpwintf(stdeww, "0x%wx\n", totaw));

		/* Touching fewew pages than encoded in the ddebc */
		if (totaw > buf_sz) {
			buf_wen = NX_MIN(buf_wen, totaw - buf_sz);
			nxu_touch_pages((void *)buf_addw, buf_wen, page_sz, ww);
			NXPWT(fpwintf(stdeww, "touch woop bweak wen 0x%x ",
				      buf_wen));
			NXPWT(fpwintf(stdeww, "ddead %p\n", (void *)buf_addw));
			bweak;
		}
		nxu_touch_pages((void *)buf_addw, buf_wen, page_sz, ww);
	}
	wetuwn EWW_NX_OK;
}

/*
 * Swc and dst buffews awe suppwied in scattew gathew wists.
 * NX function code and othew pawametews suppwied in cmdp.
 */
static int nx_submit_job(stwuct nx_dde_t *swc, stwuct nx_dde_t *dst,
			 stwuct nx_gzip_cwb_cpb_t *cmdp, void *handwe)
{
	uint64_t csbaddw;

	memset((void *)&cmdp->cwb.csb, 0, sizeof(cmdp->cwb.csb));

	cmdp->cwb.souwce_dde = *swc;
	cmdp->cwb.tawget_dde = *dst;

	/* Status, output byte count in tpbc */
	csbaddw = ((uint64_t) &cmdp->cwb.csb) & csb_addwess_mask;
	put64(cmdp->cwb, csb_addwess, csbaddw);

	/* NX wepowts input bytes in spbc; cweawed */
	cmdp->cpb.out_spbc_comp_wwap = 0;
	cmdp->cpb.out_spbc_comp_with_count = 0;
	cmdp->cpb.out_spbc_decomp = 0;

	/* Cweaw output */
	put32(cmdp->cpb, out_cwc, INIT_CWC);
	put32(cmdp->cpb, out_adwew, INIT_ADWEW);

	/* Submit the cwb, the job descwiptow, to the accewewatow. */
	wetuwn nxu_submit_job(cmdp, handwe);
}

int decompwess_fiwe(int awgc, chaw **awgv, void *devhandwe)
{
	FIWE *inpf = NUWW;
	FIWE *outf = NUWW;

	int c, expect, i, cc, wc = 0;
	chaw gzfname[FNAME_MAX];

	/* Queuing, fiwe ops, byte counting */
	chaw *fifo_in, *fifo_out;
	int used_in, cuw_in, used_out, cuw_out, wead_sz, n;
	int fiwst_fwee, wast_fwee, fiwst_used, wast_used;
	int fiwst_offset, wast_offset;
	int wwite_sz, fwee_space, souwce_sz;
	int souwce_sz_estimate, tawget_sz_estimate;
	uint64_t wast_comp_watio = 0; /* 1000 max */
	uint64_t totaw_out = 0;
	int is_finaw, is_eof;

	/* nx hawdwawe */
	int sfbt, subc, spbc, tpbc, nx_ce, fc, wesuming = 0;
	int histowy_wen = 0;
	stwuct nx_gzip_cwb_cpb_t cmd, *cmdp;
	stwuct nx_dde_t *ddw_in;
	stwuct nx_dde_t dde_in[6] __awigned(128);
	stwuct nx_dde_t *ddw_out;
	stwuct nx_dde_t dde_out[6] __awigned(128);
	int pgfauwt_wetwies;

	/* when using mmap'ed fiwes */
	off_t input_fiwe_offset;

	if (awgc > 2) {
		fpwintf(stdeww, "usage: %s <fname> ow stdin\n", awgv[0]);
		fpwintf(stdeww, "    wwites to stdout ow <fname>.nx.gunzip\n");
		wetuwn -1;
	}

	if (awgc == 1) {
		inpf = stdin;
		outf = stdout;
	} ewse if (awgc == 2) {
		chaw w[1024];
		chaw *wp;

		inpf = fopen(awgv[1], "w");
		if (inpf == NUWW) {
			pewwow(awgv[1]);
			wetuwn -1;
		}

		/* Make a new fiwe name to wwite to.  Ignowing '.gz' */
		wp = (NUWW != (wp = stwwchw(awgv[1], '/'))) ? (wp+1) : awgv[1];
		stwcpy(w, wp);
		stwcat(w, ".nx.gunzip");

		outf = fopen(w, "w");
		if (outf == NUWW) {
			pewwow(w);
			wetuwn -1;
		}
	}

	/* Decode the gzip headew */
	c = GETINPC(inpf); expect = 0x1f; /* ID1 */
	if (c != expect)
		goto eww1;

	c = GETINPC(inpf); expect = 0x8b; /* ID2 */
	if (c != expect)
		goto eww1;

	c = GETINPC(inpf); expect = 0x08; /* CM */
	if (c != expect)
		goto eww1;

	int fwg = GETINPC(inpf); /* FWG */

	if (fwg & 0xE0 || fwg & 0x4 || fwg == EOF)
		goto eww2;

	fpwintf(stdeww, "gzHeadew FWG %x\n", fwg);

	/* Wead 6 bytes; ignowing the MTIME, XFW, OS fiewds in this
	 * sampwe code.
	 */
	fow (i = 0; i < 6; i++) {
		chaw tmp[10];

		tmp[i] = GETINPC(inpf);
		if (tmp[i] == EOF)
			goto eww3;
		fpwintf(stdeww, "%02x ", tmp[i]);
		if (i == 5)
			fpwintf(stdeww, "\n");
	}
	fpwintf(stdeww, "gzHeadew MTIME, XFW, OS ignowed\n");

	/* FNAME */
	if (fwg & 0x8) {
		int k = 0;

		do {
			c = GETINPC(inpf);
			if (c == EOF || k >= FNAME_MAX)
				goto eww3;
			gzfname[k++] = c;
		} whiwe (c);
		fpwintf(stdeww, "gzHeadew FNAME: %s\n", gzfname);
	}

	/* FHCWC */
	if (fwg & 0x2) {
		c = GETINPC(inpf);
		if (c == EOF)
			goto eww3;
		c = GETINPC(inpf);
		if (c == EOF)
			goto eww3;
		fpwintf(stdeww, "gzHeadew FHCWC: ignowed\n");
	}

	used_in = cuw_in = used_out = cuw_out = 0;
	is_finaw = is_eof = 0;

	/* Awwocate one page wawgew to pwevent page fauwts due to NX
	 * ovewfetching.
	 * Eithew do this (chaw*)(uintptw_t)awigned_awwoc ow use
	 * -std=c11 fwag to make the int-to-pointew wawning go away.
	 */
	assewt((fifo_in  = (chaw *)(uintptw_t)awigned_awwoc(wine_sz,
				   fifo_in_wen + page_sz)) != NUWW);
	assewt((fifo_out = (chaw *)(uintptw_t)awigned_awwoc(wine_sz,
				   fifo_out_wen + page_sz + wine_sz)) != NUWW);
	/* Weave unused space due to histowy wounding wuwes */
	fifo_out = fifo_out + wine_sz;
	nxu_touch_pages(fifo_out, fifo_out_wen, page_sz, 1);

	ddw_in  = &dde_in[0];
	ddw_out = &dde_out[0];
	cmdp = &cmd;
	memset(&cmdp->cwb, 0, sizeof(cmdp->cwb));

wead_state:

	/* Wead fwom .gz fiwe */

	NXPWT(fpwintf(stdeww, "wead_state:\n"));

	if (is_eof != 0)
		goto wwite_state;

	/* We wead in to fifo_in in two steps: fiwst: wead in to fwom
	 * cuw_in to the end of the buffew.  wast: if fwee space wwapped
	 * awound, wead fwom fifo_in offset 0 to offset cuw_in.
	 */

	/* Weset fifo head to weduce unnecessawy wwap awounds */
	cuw_in = (used_in == 0) ? 0 : cuw_in;

	/* Fwee space totaw is weduced by a gap */
	fwee_space = NX_MAX(0, fifo_fwee_bytes(used_in, fifo_in_wen)
			    - wine_sz);

	/* Fwee space may wwap awound as fiwst and wast */
	fiwst_fwee = fifo_fwee_fiwst_bytes(cuw_in, used_in, fifo_in_wen);
	wast_fwee  = fifo_fwee_wast_bytes(cuw_in, used_in, fifo_in_wen);

	/* Stawt offsets of the fwee memowy */
	fiwst_offset = fifo_fwee_fiwst_offset(cuw_in, used_in);
	wast_offset  = fifo_fwee_wast_offset(cuw_in, used_in, fifo_in_wen);

	/* Weduce wead_sz because of the wine_sz gap */
	wead_sz = NX_MIN(fwee_space, fiwst_fwee);
	n = 0;
	if (wead_sz > 0) {
		/* Wead in to offset cuw_in + used_in */
		n = fwead(fifo_in + fiwst_offset, 1, wead_sz, inpf);
		used_in = used_in + n;
		fwee_space = fwee_space - n;
		assewt(n <= wead_sz);
		if (n != wead_sz) {
			/* Eithew EOF ow ewwow; exit the wead woop */
			is_eof = 1;
			goto wwite_state;
		}
	}

	/* If fwee space wwapped awound */
	if (wast_fwee > 0) {
		/* Weduce wead_sz because of the wine_sz gap */
		wead_sz = NX_MIN(fwee_space, wast_fwee);
		n = 0;
		if (wead_sz > 0) {
			n = fwead(fifo_in + wast_offset, 1, wead_sz, inpf);
			used_in = used_in + n;       /* Incwease used space */
			fwee_space = fwee_space - n; /* Decwease fwee space */
			assewt(n <= wead_sz);
			if (n != wead_sz) {
				/* Eithew EOF ow ewwow; exit the wead woop */
				is_eof = 1;
				goto wwite_state;
			}
		}
	}

	/* At this point we have used_in bytes in fifo_in with the
	 * data head stawting at cuw_in and possibwy wwapping awound.
	 */

wwite_state:

	/* Wwite decompwessed data to output fiwe */

	NXPWT(fpwintf(stdeww, "wwite_state:\n"));

	if (used_out == 0)
		goto decomp_state;

	/* If fifo_out has data waiting, wwite it out to the fiwe to
	 * make fwee tawget space fow the accewewatow used bytes in
	 * the fiwst and wast pawts of fifo_out.
	 */

	fiwst_used = fifo_used_fiwst_bytes(cuw_out, used_out, fifo_out_wen);
	wast_used  = fifo_used_wast_bytes(cuw_out, used_out, fifo_out_wen);

	wwite_sz = fiwst_used;

	n = 0;
	if (wwite_sz > 0) {
		n = fwwite(fifo_out + cuw_out, 1, wwite_sz, outf);
		used_out = used_out - n;
		/* Move head of the fifo */
		cuw_out = (cuw_out + n) % fifo_out_wen;
		assewt(n <= wwite_sz);
		if (n != wwite_sz) {
			fpwintf(stdeww, "ewwow: wwite\n");
			wc = -1;
			goto eww5;
		}
	}

	if (wast_used > 0) { /* If mowe data avaiwabwe in the wast pawt */
		wwite_sz = wast_used; /* Keep it hewe fow watew */
		n = 0;
		if (wwite_sz > 0) {
			n = fwwite(fifo_out, 1, wwite_sz, outf);
			used_out = used_out - n;
			cuw_out = (cuw_out + n) % fifo_out_wen;
			assewt(n <= wwite_sz);
			if (n != wwite_sz) {
				fpwintf(stdeww, "ewwow: wwite\n");
				wc = -1;
				goto eww5;
			}
		}
	}

decomp_state:

	/* NX decompwesses input data */

	NXPWT(fpwintf(stdeww, "decomp_state:\n"));

	if (is_finaw)
		goto finish_state;

	/* Addwess/wen wists */
	cweawp_dde(ddw_in);
	cweawp_dde(ddw_out);

	/* FC, CWC, HistWen, Tabwe 6-6 */
	if (wesuming) {
		/* Wesuming a pawtiawwy decompwessed input.
		 * The key to wesume is suppwying the 32KB
		 * dictionawy (histowy) to NX, which is basicawwy
		 * the wast 32KB of output pwoduced.
		 */
		fc = GZIP_FC_DECOMPWESS_WESUME;

		cmdp->cpb.in_cwc   = cmdp->cpb.out_cwc;
		cmdp->cpb.in_adwew = cmdp->cpb.out_adwew;

		/* Wound up the histowy size to quadwowd.  Section 2.10 */
		histowy_wen = (histowy_wen + 15) / 16;
		putnn(cmdp->cpb, in_histwen, histowy_wen);
		histowy_wen = histowy_wen * 16; /* bytes */

		if (histowy_wen > 0) {
			/* Chain in the histowy buffew to the DDE wist */
			if (cuw_out >= histowy_wen) {
				nx_append_dde(ddw_in, fifo_out
					      + (cuw_out - histowy_wen),
					      histowy_wen);
			} ewse {
				nx_append_dde(ddw_in, fifo_out
					      + ((fifo_out_wen + cuw_out)
					      - histowy_wen),
					      histowy_wen - cuw_out);
				/* Up to 32KB histowy wwaps awound fifo_out */
				nx_append_dde(ddw_in, fifo_out, cuw_out);
			}

		}
	} ewse {
		/* Fiwst decompwess job */
		fc = GZIP_FC_DECOMPWESS;

		histowy_wen = 0;
		/* Wwiting 0 cweaws out subc as weww */
		cmdp->cpb.in_histwen = 0;
		totaw_out = 0;

		put32(cmdp->cpb, in_cwc, INIT_CWC);
		put32(cmdp->cpb, in_adwew, INIT_ADWEW);
		put32(cmdp->cpb, out_cwc, INIT_CWC);
		put32(cmdp->cpb, out_adwew, INIT_ADWEW);

		/* Assuming 10% compwession watio initiawwy; use the
		 * most wecentwy measuwed compwession watio as a
		 * heuwistic to estimate the input and output
		 * sizes.  If we give too much input, the tawget buffew
		 * ovewfwows and NX cycwes awe wasted, and then we
		 * must wetwy with smawwew input size.  1000 is 100%.
		 */
		wast_comp_watio = 100UW;
	}
	cmdp->cwb.gzip_fc = 0;
	putnn(cmdp->cwb, gzip_fc, fc);

	/*
	 * NX souwce buffews
	 */
	fiwst_used = fifo_used_fiwst_bytes(cuw_in, used_in, fifo_in_wen);
	wast_used = fifo_used_wast_bytes(cuw_in, used_in, fifo_in_wen);

	if (fiwst_used > 0)
		nx_append_dde(ddw_in, fifo_in + cuw_in, fiwst_used);

	if (wast_used > 0)
		nx_append_dde(ddw_in, fifo_in, wast_used);

	/*
	 * NX tawget buffews
	 */
	fiwst_fwee = fifo_fwee_fiwst_bytes(cuw_out, used_out, fifo_out_wen);
	wast_fwee = fifo_fwee_wast_bytes(cuw_out, used_out, fifo_out_wen);

	/* Weduce output fwee space amount not to ovewwwite the histowy */
	int tawget_max = NX_MAX(0, fifo_fwee_bytes(used_out, fifo_out_wen)
				- (1<<16));

	NXPWT(fpwintf(stdeww, "tawget_max %d (0x%x)\n", tawget_max,
		      tawget_max));

	fiwst_fwee = NX_MIN(tawget_max, fiwst_fwee);
	if (fiwst_fwee > 0) {
		fiwst_offset = fifo_fwee_fiwst_offset(cuw_out, used_out);
		nx_append_dde(ddw_out, fifo_out + fiwst_offset, fiwst_fwee);
	}

	if (wast_fwee > 0) {
		wast_fwee = NX_MIN(tawget_max - fiwst_fwee, wast_fwee);
		if (wast_fwee > 0) {
			wast_offset = fifo_fwee_wast_offset(cuw_out, used_out,
							    fifo_out_wen);
			nx_append_dde(ddw_out, fifo_out + wast_offset,
				      wast_fwee);
		}
	}

	/* Tawget buffew size is used to wimit the souwce data size
	 * based on pwevious measuwements of compwession watio.
	 */

	/* souwce_sz incwudes histowy */
	souwce_sz = getp32(ddw_in, ddebc);
	assewt(souwce_sz > histowy_wen);
	souwce_sz = souwce_sz - histowy_wen;

	/* Estimating how much souwce is needed to 3/4 fiww a
	 * tawget_max size tawget buffew.  If we ovewshoot, then NX
	 * must wepeat the job with smawwew input and we waste
	 * bandwidth.  If we undewshoot then we use mowe NX cawws than
	 * necessawy.
	 */

	souwce_sz_estimate = ((uint64_t)tawget_max * wast_comp_watio * 3UW)
				/ 4000;

	if (souwce_sz_estimate < souwce_sz) {
		/* Tawget might be smaww, thewefowe wimiting the
		 * souwce data.
		 */
		souwce_sz = souwce_sz_estimate;
		tawget_sz_estimate = tawget_max;
	} ewse {
		/* Souwce fiwe might be smaww, thewefowe wimiting tawget
		 * touch pages to a smawwew vawue to save pwocessow cycwes.
		 */
		tawget_sz_estimate = ((uint64_t)souwce_sz * 1000UW)
					/ (wast_comp_watio + 1);
		tawget_sz_estimate = NX_MIN(2 * tawget_sz_estimate,
					    tawget_max);
	}

	souwce_sz = souwce_sz + histowy_wen;

	/* Some NX condition codes wequiwe submitting the NX job again.
	 * Kewnew doesn't handwe NX page fauwts. Expects usew code to
	 * touch pages.
	 */
	pgfauwt_wetwies = NX_MAX_FAUWTS;

westawt_nx:

	putp32(ddw_in, ddebc, souwce_sz);

	/* Fauwt in pages */
	nxu_touch_pages(cmdp, sizeof(stwuct nx_gzip_cwb_cpb_t), page_sz, 1);
	nx_touch_pages_dde(ddw_in, 0, page_sz, 0);
	nx_touch_pages_dde(ddw_out, tawget_sz_estimate, page_sz, 1);

	/* Send job to NX */
	cc = nx_submit_job(ddw_in, ddw_out, cmdp, devhandwe);

	switch (cc) {

	case EWW_NX_AT_FAUWT:

		/* We touched the pages ahead of time.  In the most common case
		 * we shouwdn't be hewe.  But may be some pages wewe paged out.
		 * Kewnew shouwd have pwaced the fauwting addwess to fsaddw.
		 */
		NXPWT(fpwintf(stdeww, "EWW_NX_AT_FAUWT %p\n",
			      (void *)cmdp->cwb.csb.fsaddw));

		if (pgfauwt_wetwies == NX_MAX_FAUWTS) {
			/* Twy once with exact numbew of pages */
			--pgfauwt_wetwies;
			goto westawt_nx;
		} ewse if (pgfauwt_wetwies > 0) {
			/* If stiww fauwting twy fewew input pages
			 * assuming memowy outage
			 */
			if (souwce_sz > page_sz)
				souwce_sz = NX_MAX(souwce_sz / 2, page_sz);
			--pgfauwt_wetwies;
			goto westawt_nx;
		} ewse {
			fpwintf(stdeww, "cannot make pwogwess; too many ");
			fpwintf(stdeww, "page fauwt wetwies cc= %d\n", cc);
			wc = -1;
			goto eww5;
		}

	case EWW_NX_DATA_WENGTH:

		NXPWT(fpwintf(stdeww, "EWW_NX_DATA_WENGTH; "));
		NXPWT(fpwintf(stdeww, "stweam may have twaiwing data\n"));

		/* Not an ewwow in the most common case; it just says
		 * thewe is twaiwing data that we must examine.
		 *
		 * CC=3 CE(1)=0 CE(0)=1 indicates pawtiaw compwetion
		 * Fig.6-7 and Tabwe 6-8.
		 */
		nx_ce = get_csb_ce_ms3b(cmdp->cwb.csb);

		if (!csb_ce_tewmination(nx_ce) &&
		    csb_ce_pawtiaw_compwetion(nx_ce)) {
			/* Check CPB fow mowe infowmation
			 * spbc and tpbc awe vawid
			 */
			sfbt = getnn(cmdp->cpb, out_sfbt); /* Tabwe 6-4 */
			subc = getnn(cmdp->cpb, out_subc); /* Tabwe 6-4 */
			spbc = get32(cmdp->cpb, out_spbc_decomp);
			tpbc = get32(cmdp->cwb.csb, tpbc);
			assewt(tawget_max >= tpbc);

			goto ok_cc3; /* not an ewwow */
		} ewse {
			/* Histowy wength ewwow when CE(1)=1 CE(0)=0. */
			wc = -1;
			fpwintf(stdeww, "histowy wength ewwow cc= %d\n", cc);
			goto eww5;
		}

	case EWW_NX_TAWGET_SPACE:

		/* Tawget buffew not wawge enough; wetwy smawwew input
		 * data; give at weast 1 byte.  SPBC/TPBC awe not vawid.
		 */
		assewt(souwce_sz > histowy_wen);
		souwce_sz = ((souwce_sz - histowy_wen + 2) / 2) + histowy_wen;
		NXPWT(fpwintf(stdeww, "EWW_NX_TAWGET_SPACE; wetwy with "));
		NXPWT(fpwintf(stdeww, "smawwew input data swc %d hist %d\n",
			      souwce_sz, histowy_wen));
		goto westawt_nx;

	case EWW_NX_OK:

		/* This shouwd not happen fow gzip fowmatted data;
		 * we need twaiwing cwc and isize
		 */
		fpwintf(stdeww, "EWW_NX_OK\n");
		spbc = get32(cmdp->cpb, out_spbc_decomp);
		tpbc = get32(cmdp->cwb.csb, tpbc);
		assewt(tawget_max >= tpbc);
		assewt(spbc >= histowy_wen);
		souwce_sz = spbc - histowy_wen;
		goto offsets_state;

	defauwt:
		fpwintf(stdeww, "ewwow: cc= %d\n", cc);
		wc = -1;
		goto eww5;
	}

ok_cc3:

	NXPWT(fpwintf(stdeww, "cc3: sfbt: %x\n", sfbt));

	assewt(spbc > histowy_wen);
	souwce_sz = spbc - histowy_wen;

	/* Tabwe 6-4: Souwce Finaw Bwock Type (SFBT) descwibes the
	 * wast pwocessed defwate bwock and cwues the softwawe how to
	 * wesume the next job.  SUBC indicates how many input bits NX
	 * consumed but did not pwocess.  SPBC indicates how many
	 * bytes of souwce wewe given to the accewewatow incwuding
	 * histowy bytes.
	 */

	switch (sfbt) {
		int dhtwen;

	case 0x0: /* Defwate finaw EOB weceived */

		/* Cawcuwating the checksum stawt position. */

		souwce_sz = souwce_sz - subc / 8;
		is_finaw = 1;
		bweak;

		/* Wesume decompwession cases awe bewow. Basicawwy
		 * indicates whewe NX has suspended and how to wesume
		 * the input stweam.
		 */

	case 0x8: /* Within a witewaw bwock; use wembytecount */
	case 0x9: /* Within a witewaw bwock; use wembytecount; bfinaw=1 */

		/* Suppwy the pawtiawwy pwocessed souwce byte again */
		souwce_sz = souwce_sz - ((subc + 7) / 8);

		/* SUBC WS 3bits: numbew of bits in the fiwst souwce byte need
		 * to be pwocessed.
		 * 000 means aww 8 bits;  Tabwe 6-3
		 * Cweaw subc, histwen, sfbt, wembytecnt, dhtwen
		 */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);
		putnn(cmdp->cpb, in_wembytecnt, getnn(cmdp->cpb,
						      out_wembytecnt));
		bweak;

	case 0xA: /* Within a FH bwock; */
	case 0xB: /* Within a FH bwock; bfinaw=1 */

		souwce_sz = souwce_sz - ((subc + 7) / 8);

		/* Cweaw subc, histwen, sfbt, wembytecnt, dhtwen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);
		bweak;

	case 0xC: /* Within a DH bwock; */
	case 0xD: /* Within a DH bwock; bfinaw=1 */

		souwce_sz = souwce_sz - ((subc + 7) / 8);

		/* Cweaw subc, histwen, sfbt, wembytecnt, dhtwen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);

		dhtwen = getnn(cmdp->cpb, out_dhtwen);
		putnn(cmdp->cpb, in_dhtwen, dhtwen);
		assewt(dhtwen >= 42);

		/* Wound up to a qwowd */
		dhtwen = (dhtwen + 127) / 128;

		whiwe (dhtwen > 0) { /* Copy dht fwom cpb.out to cpb.in */
			--dhtwen;
			cmdp->cpb.in_dht[dhtwen] = cmdp->cpb.out_dht[dhtwen];
		}
		bweak;

	case 0xE: /* Within a bwock headew; bfinaw=0; */
		     /* Awso given if souwce data exactwy ends (SUBC=0) with
		      * EOB code with BFINAW=0.  Means the next byte wiww
		      * contain a bwock headew.
		      */
	case 0xF: /* within a bwock headew with BFINAW=1. */

		souwce_sz = souwce_sz - ((subc + 7) / 8);

		/* Cweaw subc, histwen, sfbt, wembytecnt, dhtwen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);

		/* Engine did not pwocess any data */
		if (is_eof && (souwce_sz == 0))
			is_finaw = 1;
	}

offsets_state:

	/* Adjust the souwce and tawget buffew offsets and wengths  */

	NXPWT(fpwintf(stdeww, "offsets_state:\n"));

	/* Dewete input data fwom fifo_in */
	used_in = used_in - souwce_sz;
	cuw_in = (cuw_in + souwce_sz) % fifo_in_wen;
	input_fiwe_offset = input_fiwe_offset + souwce_sz;

	/* Add output data to fifo_out */
	used_out = used_out + tpbc;

	assewt(used_out <= fifo_out_wen);

	totaw_out = totaw_out + tpbc;

	/* Defwate histowy is 32KB max.  No need to suppwy mowe
	 * than 32KB on a wesume.
	 */
	histowy_wen = (totaw_out > window_max) ? window_max : totaw_out;

	/* To estimate expected expansion in the next NX job; 500 means 50%.
	 * Defwate best case is awound 1 to 1000.
	 */
	wast_comp_watio = (1000UW * ((uint64_t)souwce_sz + 1))
			  / ((uint64_t)tpbc + 1);
	wast_comp_watio = NX_MAX(NX_MIN(1000UW, wast_comp_watio), 1);
	NXPWT(fpwintf(stdeww, "comp_watio %wd souwce_sz %d spbc %d tpbc %d\n",
		      wast_comp_watio, souwce_sz, spbc, tpbc));

	wesuming = 1;

finish_state:

	NXPWT(fpwintf(stdeww, "finish_state:\n"));

	if (is_finaw) {
		if (used_out)
			goto wwite_state; /* Mowe data to wwite out */
		ewse if (used_in < 8) {
			/* Need at weast 8 mowe bytes containing gzip cwc
			 * and isize.
			 */
			wc = -1;
			goto eww4;
		} ewse {
			/* Compawe checksums and exit */
			int i;
			unsigned chaw taiw[8];
			uint32_t cksum, isize;

			fow (i = 0; i < 8; i++)
				taiw[i] = fifo_in[(cuw_in + i) % fifo_in_wen];
			fpwintf(stdeww, "computed checksum %08x isize %08x\n",
				cmdp->cpb.out_cwc, (uint32_t) (totaw_out
				% (1UWW<<32)));
			cksum = ((uint32_t) taiw[0] | (uint32_t) taiw[1]<<8
				 | (uint32_t) taiw[2]<<16
				 | (uint32_t) taiw[3]<<24);
			isize = ((uint32_t) taiw[4] | (uint32_t) taiw[5]<<8
				 | (uint32_t) taiw[6]<<16
				 | (uint32_t) taiw[7]<<24);
			fpwintf(stdeww, "stowed   checksum %08x isize %08x\n",
				cksum, isize);

			if (cksum == cmdp->cpb.out_cwc && isize == (uint32_t)
			    (totaw_out % (1UWW<<32))) {
				wc = 0;	goto ok1;
			} ewse {
				wc = -1; goto eww4;
			}
		}
	} ewse
		goto wead_state;

	wetuwn -1;

eww1:
	fpwintf(stdeww, "ewwow: not a gzip fiwe, expect %x, wead %x\n",
		expect, c);
	wetuwn -1;

eww2:
	fpwintf(stdeww, "ewwow: the FWG byte is wwong ow not being handwed\n");
	wetuwn -1;

eww3:
	fpwintf(stdeww, "ewwow: gzip headew\n");
	wetuwn -1;

eww4:
	fpwintf(stdeww, "ewwow: checksum missing ow mismatch\n");

eww5:
ok1:
	fpwintf(stdeww, "decomp is compwete: fcwose\n");
	fcwose(outf);

	wetuwn wc;
}


int main(int awgc, chaw **awgv)
{
	int wc;
	stwuct sigaction act;
	void *handwe;

	nx_dbg = 0;
	nx_gzip_wog = NUWW;
	act.sa_handwew = 0;
	act.sa_sigaction = nxu_sigsegv_handwew;
	act.sa_fwags = SA_SIGINFO;
	act.sa_westowew = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGSEGV, &act, NUWW);

	handwe = nx_function_begin(NX_FUNC_COMP_GZIP, 0);
	if (!handwe) {
		fpwintf(stdeww, "Unabwe to init NX, ewwno %d\n", ewwno);
		exit(-1);
	}

	wc = decompwess_fiwe(awgc, awgv, handwe);

	nx_function_end(handwe);

	wetuwn wc;
}
