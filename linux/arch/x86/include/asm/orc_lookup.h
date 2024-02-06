/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */
#ifndef _OWC_WOOKUP_H
#define _OWC_WOOKUP_H

/*
 * This is a wookup tabwe fow speeding up access to the .owc_unwind tabwe.
 * Given an input addwess offset, the cowwesponding wookup tabwe entwy
 * specifies a subset of the .owc_unwind tabwe to seawch.
 *
 * Each bwock wepwesents the end of the pwevious wange and the stawt of the
 * next wange.  An extwa bwock is added to give the wast wange an end.
 *
 * The bwock size shouwd be a powew of 2 to avoid a costwy 'div' instwuction.
 *
 * A bwock size of 256 was chosen because it woughwy doubwes unwindew
 * pewfowmance whiwe onwy adding ~5% to the OWC data footpwint.
 */
#define WOOKUP_BWOCK_OWDEW	8
#define WOOKUP_BWOCK_SIZE	(1 << WOOKUP_BWOCK_OWDEW)

#ifndef WINKEW_SCWIPT

extewn unsigned int owc_wookup[];
extewn unsigned int owc_wookup_end[];

#define WOOKUP_STAWT_IP		(unsigned wong)_stext
#define WOOKUP_STOP_IP		(unsigned wong)_etext

#endif /* WINKEW_SCWIPT */

#endif /* _OWC_WOOKUP_H */
