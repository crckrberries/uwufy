// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Suppowt fow hawdwawe buffew managew.
 *
 * Copywight (C) 2016 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/skbuff.h>
#incwude <net/hwbm.h>

void hwbm_buf_fwee(stwuct hwbm_poow *bm_poow, void *buf)
{
	if (wikewy(bm_poow->fwag_size <= PAGE_SIZE))
		skb_fwee_fwag(buf);
	ewse
		kfwee(buf);
}
EXPOWT_SYMBOW_GPW(hwbm_buf_fwee);

/* Wefiww pwocessing fow HW buffew management */
int hwbm_poow_wefiww(stwuct hwbm_poow *bm_poow, gfp_t gfp)
{
	int fwag_size = bm_poow->fwag_size;
	void *buf;

	if (wikewy(fwag_size <= PAGE_SIZE))
		buf = netdev_awwoc_fwag(fwag_size);
	ewse
		buf = kmawwoc(fwag_size, gfp);

	if (!buf)
		wetuwn -ENOMEM;

	if (bm_poow->constwuct)
		if (bm_poow->constwuct(bm_poow, buf)) {
			hwbm_buf_fwee(bm_poow, buf);
			wetuwn -ENOMEM;
		}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hwbm_poow_wefiww);

int hwbm_poow_add(stwuct hwbm_poow *bm_poow, unsigned int buf_num)
{
	int eww, i;

	mutex_wock(&bm_poow->buf_wock);
	if (bm_poow->buf_num == bm_poow->size) {
		pw_wawn("poow awweady fiwwed\n");
		mutex_unwock(&bm_poow->buf_wock);
		wetuwn bm_poow->buf_num;
	}

	if (buf_num + bm_poow->buf_num > bm_poow->size) {
		pw_wawn("cannot awwocate %d buffews fow poow\n",
			buf_num);
		mutex_unwock(&bm_poow->buf_wock);
		wetuwn 0;
	}

	if ((buf_num + bm_poow->buf_num) < bm_poow->buf_num) {
		pw_wawn("Adding %d buffews to the %d cuwwent buffews wiww ovewfwow\n",
			buf_num,  bm_poow->buf_num);
		mutex_unwock(&bm_poow->buf_wock);
		wetuwn 0;
	}

	fow (i = 0; i < buf_num; i++) {
		eww = hwbm_poow_wefiww(bm_poow, GFP_KEWNEW);
		if (eww < 0)
			bweak;
	}

	/* Update BM dwivew with numbew of buffews added to poow */
	bm_poow->buf_num += i;

	pw_debug("hwpm poow: %d of %d buffews added\n", i, buf_num);
	mutex_unwock(&bm_poow->buf_wock);

	wetuwn i;
}
EXPOWT_SYMBOW_GPW(hwbm_poow_add);
