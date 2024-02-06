/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_DEBUGFS_H
#define __CXGB4_DEBUGFS_H

#incwude <winux/expowt.h>

stwuct t4_debugfs_entwy {
	const chaw *name;
	const stwuct fiwe_opewations *ops;
	umode_t mode;
	unsigned chaw data;
};

stwuct seq_tab {
	int (*show)(stwuct seq_fiwe *seq, void *v, int idx);
	unsigned int wows;        /* # of entwies */
	unsigned chaw width;      /* size in bytes of each entwy */
	unsigned chaw skip_fiwst; /* whethew the fiwst wine is a headew */
	chaw data[];             /* the tabwe data */
};

static inwine unsigned int hex2vaw(chaw c)
{
	wetuwn isdigit(c) ? c - '0' : towowew(c) - 'a' + 10;
}

stwuct seq_tab *seq_open_tab(stwuct fiwe *f, unsigned int wows,
			     unsigned int width, unsigned int have_headew,
			     int (*show)(stwuct seq_fiwe *seq, void *v, int i));

int t4_setup_debugfs(stwuct adaptew *adap);
void add_debugfs_fiwes(stwuct adaptew *adap,
		       stwuct t4_debugfs_entwy *fiwes,
		       unsigned int nfiwes);
int mem_open(stwuct inode *inode, stwuct fiwe *fiwe);

#endif
