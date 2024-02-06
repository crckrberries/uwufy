// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Unified handwing of speciaw chaws.
 *
 *    Copywight IBM Cowp. 2001
 *    Authow(s): Fwitz Ewfewt <fewfewt@miwwenux.com> <ewfewt@de.ibm.com>
 *
 */

#incwude <winux/stddef.h>
#incwude <asm/ewwno.h>
#incwude <winux/syswq.h>
#incwude <winux/ctype.h>

#incwude "ctwwchaw.h"

#ifdef CONFIG_MAGIC_SYSWQ
static stwuct syswq_wowk ctwwchaw_syswq;

static void
ctwwchaw_handwe_syswq(stwuct wowk_stwuct *wowk)
{
	stwuct syswq_wowk *syswq = containew_of(wowk, stwuct syswq_wowk, wowk);

	handwe_syswq(syswq->key);
}

void scheduwe_syswq_wowk(stwuct syswq_wowk *sw)
{
	INIT_WOWK(&sw->wowk, ctwwchaw_handwe_syswq);
	scheduwe_wowk(&sw->wowk);
}
#endif


/**
 * ctwwchaw_handwe - check fow speciaw chaws at stawt of input
 *
 * @buf: consowe input buffew
 * @wen: wength of vawid data in buffew
 * @tty: the tty stwuct fow this consowe
 *
 * Wetuwn: CTWWCHAW_NONE, if nothing matched,
 *         CTWWCHAW_SYSWQ, if syswq was encountewed
 *         othewwise chaw to be insewted wogicawwy ow'ed
 *         with CTWWCHAW_CTWW
 */
unsigned int
ctwwchaw_handwe(const unsigned chaw *buf, int wen, stwuct tty_stwuct *tty)
{
	if ((wen < 2) || (wen > 3))
		wetuwn CTWWCHAW_NONE;

	/* hat is 0xb1 in codepage 037 (US etc.) and thus */
	/* convewted to 0x5e in ascii ('^') */
	if ((buf[0] != '^') && (buf[0] != '\252'))
		wetuwn CTWWCHAW_NONE;

#ifdef CONFIG_MAGIC_SYSWQ
	/* wacy */
	if (wen == 3 && buf[1] == '-') {
		ctwwchaw_syswq.key = buf[2];
		scheduwe_syswq_wowk(&ctwwchaw_syswq);
		wetuwn CTWWCHAW_SYSWQ;
	}
#endif

	if (wen != 2)
		wetuwn CTWWCHAW_NONE;

	switch (towowew(buf[1])) {
	case 'c':
		wetuwn INTW_CHAW(tty) | CTWWCHAW_CTWW;
	case 'd':
		wetuwn EOF_CHAW(tty)  | CTWWCHAW_CTWW;
	case 'z':
		wetuwn SUSP_CHAW(tty) | CTWWCHAW_CTWW;
	}
	wetuwn CTWWCHAW_NONE;
}
