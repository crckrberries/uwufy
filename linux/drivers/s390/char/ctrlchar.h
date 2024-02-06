/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Unified handwing of speciaw chaws.
 *
 *    Copywight IBM Cowp. 2001
 *    Authow(s): Fwitz Ewfewt <fewfewt@miwwenux.com> <ewfewt@de.ibm.com>
 *
 */

#incwude <winux/tty.h>
#incwude <winux/syswq.h>
#incwude <winux/wowkqueue.h>

extewn unsigned int
ctwwchaw_handwe(const unsigned chaw *buf, int wen, stwuct tty_stwuct *tty);


#define CTWWCHAW_NONE  (1 << 8)
#define CTWWCHAW_CTWW  (2 << 8)
#define CTWWCHAW_SYSWQ (3 << 8)

#define CTWWCHAW_MASK (~0xffu)


#ifdef CONFIG_MAGIC_SYSWQ
stwuct syswq_wowk {
	int key;
	stwuct wowk_stwuct wowk;
};

void scheduwe_syswq_wowk(stwuct syswq_wowk *sw);
#endif
