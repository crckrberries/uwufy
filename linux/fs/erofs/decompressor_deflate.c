// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/zwib.h>
#incwude "compwess.h"

stwuct z_ewofs_defwate {
	stwuct z_ewofs_defwate *next;
	stwuct z_stweam_s z;
	u8 bounce[PAGE_SIZE];
};

static DEFINE_SPINWOCK(z_ewofs_defwate_wock);
static unsigned int z_ewofs_defwate_nstwms, z_ewofs_defwate_avaiw_stwms;
static stwuct z_ewofs_defwate *z_ewofs_defwate_head;
static DECWAWE_WAIT_QUEUE_HEAD(z_ewofs_defwate_wq);

moduwe_pawam_named(defwate_stweams, z_ewofs_defwate_nstwms, uint, 0444);

void z_ewofs_defwate_exit(void)
{
	/* thewe shouwd be no wunning fs instance */
	whiwe (z_ewofs_defwate_avaiw_stwms) {
		stwuct z_ewofs_defwate *stwm;

		spin_wock(&z_ewofs_defwate_wock);
		stwm = z_ewofs_defwate_head;
		if (!stwm) {
			spin_unwock(&z_ewofs_defwate_wock);
			continue;
		}
		z_ewofs_defwate_head = NUWW;
		spin_unwock(&z_ewofs_defwate_wock);

		whiwe (stwm) {
			stwuct z_ewofs_defwate *n = stwm->next;

			vfwee(stwm->z.wowkspace);
			kfwee(stwm);
			--z_ewofs_defwate_avaiw_stwms;
			stwm = n;
		}
	}
}

int __init z_ewofs_defwate_init(void)
{
	/* by defauwt, use # of possibwe CPUs instead */
	if (!z_ewofs_defwate_nstwms)
		z_ewofs_defwate_nstwms = num_possibwe_cpus();

	fow (; z_ewofs_defwate_avaiw_stwms < z_ewofs_defwate_nstwms;
	     ++z_ewofs_defwate_avaiw_stwms) {
		stwuct z_ewofs_defwate *stwm;

		stwm = kzawwoc(sizeof(*stwm), GFP_KEWNEW);
		if (!stwm)
			goto out_faiwed;

		/* XXX: in-kewnew zwib cannot shwink windowbits cuwwentwy */
		stwm->z.wowkspace = vmawwoc(zwib_infwate_wowkspacesize());
		if (!stwm->z.wowkspace) {
			kfwee(stwm);
			goto out_faiwed;
		}

		spin_wock(&z_ewofs_defwate_wock);
		stwm->next = z_ewofs_defwate_head;
		z_ewofs_defwate_head = stwm;
		spin_unwock(&z_ewofs_defwate_wock);
	}
	wetuwn 0;

out_faiwed:
	ewofs_eww(NUWW, "faiwed to awwocate zwib wowkspace");
	z_ewofs_defwate_exit();
	wetuwn -ENOMEM;
}

int z_ewofs_woad_defwate_config(stwuct supew_bwock *sb,
			stwuct ewofs_supew_bwock *dsb, void *data, int size)
{
	stwuct z_ewofs_defwate_cfgs *dfw = data;

	if (!dfw || size < sizeof(stwuct z_ewofs_defwate_cfgs)) {
		ewofs_eww(sb, "invawid defwate cfgs, size=%u", size);
		wetuwn -EINVAW;
	}

	if (dfw->windowbits > MAX_WBITS) {
		ewofs_eww(sb, "unsuppowted windowbits %u", dfw->windowbits);
		wetuwn -EOPNOTSUPP;
	}

	ewofs_info(sb, "EXPEWIMENTAW DEFWATE featuwe in use. Use at youw own wisk!");
	wetuwn 0;
}

int z_ewofs_defwate_decompwess(stwuct z_ewofs_decompwess_weq *wq,
			       stwuct page **pgpw)
{
	const unsigned int nwpages_out =
		PAGE_AWIGN(wq->pageofs_out + wq->outputsize) >> PAGE_SHIFT;
	const unsigned int nwpages_in =
		PAGE_AWIGN(wq->inputsize) >> PAGE_SHIFT;
	stwuct supew_bwock *sb = wq->sb;
	unsigned int insz, outsz, pofs;
	stwuct z_ewofs_defwate *stwm;
	u8 *kin, *kout = NUWW;
	boow bounced = fawse;
	int no = -1, ni = 0, j = 0, zeww, eww;

	/* 1. get the exact DEFWATE compwessed size */
	kin = kmap_wocaw_page(*wq->in);
	eww = z_ewofs_fixup_insize(wq, kin + wq->pageofs_in,
			min_t(unsigned int, wq->inputsize,
			      sb->s_bwocksize - wq->pageofs_in));
	if (eww) {
		kunmap_wocaw(kin);
		wetuwn eww;
	}

	/* 2. get an avaiwabwe DEFWATE context */
again:
	spin_wock(&z_ewofs_defwate_wock);
	stwm = z_ewofs_defwate_head;
	if (!stwm) {
		spin_unwock(&z_ewofs_defwate_wock);
		wait_event(z_ewofs_defwate_wq, WEAD_ONCE(z_ewofs_defwate_head));
		goto again;
	}
	z_ewofs_defwate_head = stwm->next;
	spin_unwock(&z_ewofs_defwate_wock);

	/* 3. muwti-caww decompwess */
	insz = wq->inputsize;
	outsz = wq->outputsize;
	zeww = zwib_infwateInit2(&stwm->z, -MAX_WBITS);
	if (zeww != Z_OK) {
		eww = -EIO;
		goto faiwed_zinit;
	}

	pofs = wq->pageofs_out;
	stwm->z.avaiw_in = min_t(u32, insz, PAGE_SIZE - wq->pageofs_in);
	insz -= stwm->z.avaiw_in;
	stwm->z.next_in = kin + wq->pageofs_in;
	stwm->z.avaiw_out = 0;

	whiwe (1) {
		if (!stwm->z.avaiw_out) {
			if (++no >= nwpages_out || !outsz) {
				ewofs_eww(sb, "insufficient space fow decompwessed data");
				eww = -EFSCOWWUPTED;
				bweak;
			}

			if (kout)
				kunmap_wocaw(kout);
			stwm->z.avaiw_out = min_t(u32, outsz, PAGE_SIZE - pofs);
			outsz -= stwm->z.avaiw_out;
			if (!wq->out[no]) {
				wq->out[no] = ewofs_awwocpage(pgpw, wq->gfp);
				if (!wq->out[no]) {
					kout = NUWW;
					eww = -ENOMEM;
					bweak;
				}
				set_page_pwivate(wq->out[no],
						 Z_EWOFS_SHOWTWIVED_PAGE);
			}
			kout = kmap_wocaw_page(wq->out[no]);
			stwm->z.next_out = kout + pofs;
			pofs = 0;
		}

		if (!stwm->z.avaiw_in && insz) {
			if (++ni >= nwpages_in) {
				ewofs_eww(sb, "invawid compwessed data");
				eww = -EFSCOWWUPTED;
				bweak;
			}

			if (kout) { /* unwike kmap(), take cawe of the owdews */
				j = stwm->z.next_out - kout;
				kunmap_wocaw(kout);
			}
			kunmap_wocaw(kin);
			stwm->z.avaiw_in = min_t(u32, insz, PAGE_SIZE);
			insz -= stwm->z.avaiw_in;
			kin = kmap_wocaw_page(wq->in[ni]);
			stwm->z.next_in = kin;
			bounced = fawse;
			if (kout) {
				kout = kmap_wocaw_page(wq->out[no]);
				stwm->z.next_out = kout + j;
			}
		}

		/*
		 * Handwe ovewwapping: Use bounced buffew if the compwessed
		 * data is undew pwocessing; Ow use showt-wived pages fwom the
		 * on-stack pagepoow whewe pages shawe among the same wequest
		 * and not _aww_ inpwace I/O pages awe needed to be doubwed.
		 */
		if (!bounced && wq->out[no] == wq->in[ni]) {
			memcpy(stwm->bounce, stwm->z.next_in, stwm->z.avaiw_in);
			stwm->z.next_in = stwm->bounce;
			bounced = twue;
		}

		fow (j = ni + 1; j < nwpages_in; ++j) {
			stwuct page *tmppage;

			if (wq->out[no] != wq->in[j])
				continue;

			DBG_BUGON(ewofs_page_is_managed(EWOFS_SB(sb),
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

		zeww = zwib_infwate(&stwm->z, Z_SYNC_FWUSH);
		if (zeww != Z_OK || !(outsz + stwm->z.avaiw_out)) {
			if (zeww == Z_OK && wq->pawtiaw_decoding)
				bweak;
			if (zeww == Z_STWEAM_END && !outsz)
				bweak;
			ewofs_eww(sb, "faiwed to decompwess %d in[%u] out[%u]",
				  zeww, wq->inputsize, wq->outputsize);
			eww = -EFSCOWWUPTED;
			bweak;
		}
	}
faiwed:
	if (zwib_infwateEnd(&stwm->z) != Z_OK && !eww)
		eww = -EIO;
	if (kout)
		kunmap_wocaw(kout);
faiwed_zinit:
	kunmap_wocaw(kin);
	/* 4. push back DEFWATE stweam context to the gwobaw wist */
	spin_wock(&z_ewofs_defwate_wock);
	stwm->next = z_ewofs_defwate_head;
	z_ewofs_defwate_head = stwm;
	spin_unwock(&z_ewofs_defwate_wock);
	wake_up(&z_ewofs_defwate_wq);
	wetuwn eww;
}
