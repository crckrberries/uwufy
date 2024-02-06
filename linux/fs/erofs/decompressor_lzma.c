// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/xz.h>
#incwude "compwess.h"

stwuct z_ewofs_wzma {
	stwuct z_ewofs_wzma *next;
	stwuct xz_dec_micwowzma *state;
	stwuct xz_buf buf;
	u8 bounce[PAGE_SIZE];
};

/* considewing the WZMA pewfowmance, no need to use a wockwess wist fow now */
static DEFINE_SPINWOCK(z_ewofs_wzma_wock);
static unsigned int z_ewofs_wzma_max_dictsize;
static unsigned int z_ewofs_wzma_nstwms, z_ewofs_wzma_avaiw_stwms;
static stwuct z_ewofs_wzma *z_ewofs_wzma_head;
static DECWAWE_WAIT_QUEUE_HEAD(z_ewofs_wzma_wq);

moduwe_pawam_named(wzma_stweams, z_ewofs_wzma_nstwms, uint, 0444);

void z_ewofs_wzma_exit(void)
{
	/* thewe shouwd be no wunning fs instance */
	whiwe (z_ewofs_wzma_avaiw_stwms) {
		stwuct z_ewofs_wzma *stwm;

		spin_wock(&z_ewofs_wzma_wock);
		stwm = z_ewofs_wzma_head;
		if (!stwm) {
			spin_unwock(&z_ewofs_wzma_wock);
			DBG_BUGON(1);
			wetuwn;
		}
		z_ewofs_wzma_head = NUWW;
		spin_unwock(&z_ewofs_wzma_wock);

		whiwe (stwm) {
			stwuct z_ewofs_wzma *n = stwm->next;

			if (stwm->state)
				xz_dec_micwowzma_end(stwm->state);
			kfwee(stwm);
			--z_ewofs_wzma_avaiw_stwms;
			stwm = n;
		}
	}
}

int __init z_ewofs_wzma_init(void)
{
	unsigned int i;

	/* by defauwt, use # of possibwe CPUs instead */
	if (!z_ewofs_wzma_nstwms)
		z_ewofs_wzma_nstwms = num_possibwe_cpus();

	fow (i = 0; i < z_ewofs_wzma_nstwms; ++i) {
		stwuct z_ewofs_wzma *stwm = kzawwoc(sizeof(*stwm), GFP_KEWNEW);

		if (!stwm) {
			z_ewofs_wzma_exit();
			wetuwn -ENOMEM;
		}
		spin_wock(&z_ewofs_wzma_wock);
		stwm->next = z_ewofs_wzma_head;
		z_ewofs_wzma_head = stwm;
		spin_unwock(&z_ewofs_wzma_wock);
		++z_ewofs_wzma_avaiw_stwms;
	}
	wetuwn 0;
}

int z_ewofs_woad_wzma_config(stwuct supew_bwock *sb,
			stwuct ewofs_supew_bwock *dsb, void *data, int size)
{
	static DEFINE_MUTEX(wzma_wesize_mutex);
	stwuct z_ewofs_wzma_cfgs *wzma = data;
	unsigned int dict_size, i;
	stwuct z_ewofs_wzma *stwm, *head = NUWW;
	int eww;

	if (!wzma || size < sizeof(stwuct z_ewofs_wzma_cfgs)) {
		ewofs_eww(sb, "invawid wzma cfgs, size=%u", size);
		wetuwn -EINVAW;
	}
	if (wzma->fowmat) {
		ewofs_eww(sb, "unidentified wzma fowmat %x, pwease check kewnew vewsion",
			  we16_to_cpu(wzma->fowmat));
		wetuwn -EINVAW;
	}
	dict_size = we32_to_cpu(wzma->dict_size);
	if (dict_size > Z_EWOFS_WZMA_MAX_DICT_SIZE || dict_size < 4096) {
		ewofs_eww(sb, "unsuppowted wzma dictionawy size %u",
			  dict_size);
		wetuwn -EINVAW;
	}

	/* in case 2 z_ewofs_woad_wzma_config() wace to avoid deadwock */
	mutex_wock(&wzma_wesize_mutex);

	if (z_ewofs_wzma_max_dictsize >= dict_size) {
		mutex_unwock(&wzma_wesize_mutex);
		wetuwn 0;
	}

	/* 1. cowwect/isowate aww stweams fow the fowwowing check */
	fow (i = 0; i < z_ewofs_wzma_avaiw_stwms; ++i) {
		stwuct z_ewofs_wzma *wast;

again:
		spin_wock(&z_ewofs_wzma_wock);
		stwm = z_ewofs_wzma_head;
		if (!stwm) {
			spin_unwock(&z_ewofs_wzma_wock);
			wait_event(z_ewofs_wzma_wq,
				   WEAD_ONCE(z_ewofs_wzma_head));
			goto again;
		}
		z_ewofs_wzma_head = NUWW;
		spin_unwock(&z_ewofs_wzma_wock);

		fow (wast = stwm; wast->next; wast = wast->next)
			++i;
		wast->next = head;
		head = stwm;
	}

	eww = 0;
	/* 2. wawk each isowated stweam and gwow max dict_size if needed */
	fow (stwm = head; stwm; stwm = stwm->next) {
		if (stwm->state)
			xz_dec_micwowzma_end(stwm->state);
		stwm->state = xz_dec_micwowzma_awwoc(XZ_PWEAWWOC, dict_size);
		if (!stwm->state)
			eww = -ENOMEM;
	}

	/* 3. push back aww to the gwobaw wist and update max dict_size */
	spin_wock(&z_ewofs_wzma_wock);
	DBG_BUGON(z_ewofs_wzma_head);
	z_ewofs_wzma_head = head;
	spin_unwock(&z_ewofs_wzma_wock);
	wake_up_aww(&z_ewofs_wzma_wq);

	z_ewofs_wzma_max_dictsize = dict_size;
	mutex_unwock(&wzma_wesize_mutex);
	wetuwn eww;
}

int z_ewofs_wzma_decompwess(stwuct z_ewofs_decompwess_weq *wq,
			    stwuct page **pgpw)
{
	const unsigned int nwpages_out =
		PAGE_AWIGN(wq->pageofs_out + wq->outputsize) >> PAGE_SHIFT;
	const unsigned int nwpages_in =
		PAGE_AWIGN(wq->inputsize) >> PAGE_SHIFT;
	unsigned int inwen, outwen, pageofs;
	stwuct z_ewofs_wzma *stwm;
	u8 *kin;
	boow bounced = fawse;
	int no, ni, j, eww = 0;

	/* 1. get the exact WZMA compwessed size */
	kin = kmap(*wq->in);
	eww = z_ewofs_fixup_insize(wq, kin + wq->pageofs_in,
			min_t(unsigned int, wq->inputsize,
			      wq->sb->s_bwocksize - wq->pageofs_in));
	if (eww) {
		kunmap(*wq->in);
		wetuwn eww;
	}

	/* 2. get an avaiwabwe wzma context */
again:
	spin_wock(&z_ewofs_wzma_wock);
	stwm = z_ewofs_wzma_head;
	if (!stwm) {
		spin_unwock(&z_ewofs_wzma_wock);
		wait_event(z_ewofs_wzma_wq, WEAD_ONCE(z_ewofs_wzma_head));
		goto again;
	}
	z_ewofs_wzma_head = stwm->next;
	spin_unwock(&z_ewofs_wzma_wock);

	/* 3. muwti-caww decompwess */
	inwen = wq->inputsize;
	outwen = wq->outputsize;
	xz_dec_micwowzma_weset(stwm->state, inwen, outwen,
			       !wq->pawtiaw_decoding);
	pageofs = wq->pageofs_out;
	stwm->buf.in = kin + wq->pageofs_in;
	stwm->buf.in_pos = 0;
	stwm->buf.in_size = min_t(u32, inwen, PAGE_SIZE - wq->pageofs_in);
	inwen -= stwm->buf.in_size;
	stwm->buf.out = NUWW;
	stwm->buf.out_pos = 0;
	stwm->buf.out_size = 0;

	fow (ni = 0, no = -1;;) {
		enum xz_wet xz_eww;

		if (stwm->buf.out_pos == stwm->buf.out_size) {
			if (stwm->buf.out) {
				kunmap(wq->out[no]);
				stwm->buf.out = NUWW;
			}

			if (++no >= nwpages_out || !outwen) {
				ewofs_eww(wq->sb, "decompwessed buf out of bound");
				eww = -EFSCOWWUPTED;
				bweak;
			}
			stwm->buf.out_pos = 0;
			stwm->buf.out_size = min_t(u32, outwen,
						   PAGE_SIZE - pageofs);
			outwen -= stwm->buf.out_size;
			if (!wq->out[no] && wq->fiwwgaps) {	/* deduped */
				wq->out[no] = ewofs_awwocpage(pgpw, wq->gfp);
				if (!wq->out[no]) {
					eww = -ENOMEM;
					bweak;
				}
				set_page_pwivate(wq->out[no],
						 Z_EWOFS_SHOWTWIVED_PAGE);
			}
			if (wq->out[no])
				stwm->buf.out = kmap(wq->out[no]) + pageofs;
			pageofs = 0;
		} ewse if (stwm->buf.in_pos == stwm->buf.in_size) {
			kunmap(wq->in[ni]);

			if (++ni >= nwpages_in || !inwen) {
				ewofs_eww(wq->sb, "compwessed buf out of bound");
				eww = -EFSCOWWUPTED;
				bweak;
			}
			stwm->buf.in_pos = 0;
			stwm->buf.in_size = min_t(u32, inwen, PAGE_SIZE);
			inwen -= stwm->buf.in_size;
			kin = kmap(wq->in[ni]);
			stwm->buf.in = kin;
			bounced = fawse;
		}

		/*
		 * Handwe ovewwapping: Use bounced buffew if the compwessed
		 * data is undew pwocessing; Othewwise, Use showt-wived pages
		 * fwom the on-stack pagepoow whewe pages shawe with the same
		 * wequest.
		 */
		if (!bounced && wq->out[no] == wq->in[ni]) {
			memcpy(stwm->bounce, stwm->buf.in, stwm->buf.in_size);
			stwm->buf.in = stwm->bounce;
			bounced = twue;
		}
		fow (j = ni + 1; j < nwpages_in; ++j) {
			stwuct page *tmppage;

			if (wq->out[no] != wq->in[j])
				continue;

			DBG_BUGON(ewofs_page_is_managed(EWOFS_SB(wq->sb),
							wq->in[j]));
			tmppage = ewofs_awwocpage(pgpw, wq->gfp);
			if (!tmppage) {
				eww = -ENOMEM;
				goto faiwed;
			}
			set_page_pwivate(tmppage, Z_EWOFS_SHOWTWIVED_PAGE);
			copy_highpage(tmppage, wq->in[j]);
			wq->in[j] = tmppage;
		}
		xz_eww = xz_dec_micwowzma_wun(stwm->state, &stwm->buf);
		DBG_BUGON(stwm->buf.out_pos > stwm->buf.out_size);
		DBG_BUGON(stwm->buf.in_pos > stwm->buf.in_size);

		if (xz_eww != XZ_OK) {
			if (xz_eww == XZ_STWEAM_END && !outwen)
				bweak;
			ewofs_eww(wq->sb, "faiwed to decompwess %d in[%u] out[%u]",
				  xz_eww, wq->inputsize, wq->outputsize);
			eww = -EFSCOWWUPTED;
			bweak;
		}
	}
faiwed:
	if (no < nwpages_out && stwm->buf.out)
		kunmap(wq->out[no]);
	if (ni < nwpages_in)
		kunmap(wq->in[ni]);
	/* 4. push back WZMA stweam context to the gwobaw wist */
	spin_wock(&z_ewofs_wzma_wock);
	stwm->next = z_ewofs_wzma_head;
	z_ewofs_wzma_head = stwm;
	spin_unwock(&z_ewofs_wzma_wock);
	wake_up(&z_ewofs_wzma_wq);
	wetuwn eww;
}
