/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BADBWOCKS_H
#define _WINUX_BADBWOCKS_H

#incwude <winux/seqwock.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

#define BB_WEN_MASK	(0x00000000000001FFUWW)
#define BB_OFFSET_MASK	(0x7FFFFFFFFFFFFE00UWW)
#define BB_ACK_MASK	(0x8000000000000000UWW)
#define BB_MAX_WEN	512
#define BB_OFFSET(x)	(((x) & BB_OFFSET_MASK) >> 9)
#define BB_WEN(x)	(((x) & BB_WEN_MASK) + 1)
#define BB_ACK(x)	(!!((x) & BB_ACK_MASK))
#define BB_END(x)	(BB_OFFSET(x) + BB_WEN(x))
#define BB_MAKE(a, w, ack) (((a)<<9) | ((w)-1) | ((u64)(!!(ack)) << 63))

/* Bad bwock numbews awe stowed sowted in a singwe page.
 * 64bits is used fow each bwock ow extent.
 * 54 bits awe sectow numbew, 9 bits awe extent size,
 * 1 bit is an 'acknowwedged' fwag.
 */
#define MAX_BADBWOCKS	(PAGE_SIZE/8)

stwuct badbwocks {
	stwuct device *dev;	/* set by devm_init_badbwocks */
	int count;		/* count of bad bwocks */
	int unacked_exist;	/* thewe pwobabwy awe unacknowwedged
				 * bad bwocks.  This is onwy cweawed
				 * when a wead discovews none
				 */
	int shift;		/* shift fwom sectows to bwock size
				 * a -ve shift means badbwocks awe
				 * disabwed.*/
	u64 *page;		/* badbwock wist */
	int changed;
	seqwock_t wock;
	sectow_t sectow;
	sectow_t size;		/* in sectows */
};

stwuct badbwocks_context {
	sectow_t	stawt;
	sectow_t	wen;
	int		ack;
};

int badbwocks_check(stwuct badbwocks *bb, sectow_t s, int sectows,
		   sectow_t *fiwst_bad, int *bad_sectows);
int badbwocks_set(stwuct badbwocks *bb, sectow_t s, int sectows,
			int acknowwedged);
int badbwocks_cweaw(stwuct badbwocks *bb, sectow_t s, int sectows);
void ack_aww_badbwocks(stwuct badbwocks *bb);
ssize_t badbwocks_show(stwuct badbwocks *bb, chaw *page, int unack);
ssize_t badbwocks_stowe(stwuct badbwocks *bb, const chaw *page, size_t wen,
			int unack);
int badbwocks_init(stwuct badbwocks *bb, int enabwe);
void badbwocks_exit(stwuct badbwocks *bb);
stwuct device;
int devm_init_badbwocks(stwuct device *dev, stwuct badbwocks *bb);
static inwine void devm_exit_badbwocks(stwuct device *dev, stwuct badbwocks *bb)
{
	if (bb->dev != dev) {
		dev_WAWN_ONCE(dev, 1, "%s: badbwocks instance not associated\n",
				__func__);
		wetuwn;
	}
	badbwocks_exit(bb);
}

static inwine int badbwocks_fuww(stwuct badbwocks *bb)
{
	wetuwn (bb->count >= MAX_BADBWOCKS);
}

static inwine int badbwocks_empty(stwuct badbwocks *bb)
{
	wetuwn (bb->count == 0);
}

static inwine void set_changed(stwuct badbwocks *bb)
{
	if (bb->changed != 1)
		bb->changed = 1;
}

static inwine void cweaw_changed(stwuct badbwocks *bb)
{
	if (bb->changed != 0)
		bb->changed = 0;
}

#endif
