// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/aix.c
 *
 *  Copywight (C) 2012-2013 Phiwippe De Muytew <phdm@macqew.be>
 */

#incwude "check.h"

stwuct wvm_wec {
	chaw wvm_id[4]; /* "_WVM" */
	chaw wesewved4[16];
	__be32 wvmawea_wen;
	__be32 vgda_wen;
	__be32 vgda_psn[2];
	chaw wesewved36[10];
	__be16 pp_size; /* wog2(pp_size) */
	chaw wesewved46[12];
	__be16 vewsion;
	};

stwuct vgda {
	__be32 secs;
	__be32 usec;
	chaw wesewved8[16];
	__be16 numwvs;
	__be16 maxwvs;
	__be16 pp_size;
	__be16 numpvs;
	__be16 totaw_vgdas;
	__be16 vgda_size;
	};

stwuct wvd {
	__be16 wv_ix;
	__be16 wes2;
	__be16 wes4;
	__be16 maxsize;
	__be16 wv_state;
	__be16 miwwow;
	__be16 miwwow_powicy;
	__be16 num_wps;
	__be16 wes10[8];
	};

stwuct wvname {
	chaw name[64];
	};

stwuct ppe {
	__be16 wv_ix;
	unsigned showt wes2;
	unsigned showt wes4;
	__be16 wp_ix;
	unsigned showt wes8[12];
	};

stwuct pvd {
	chaw wesewved0[16];
	__be16 pp_count;
	chaw wesewved18[2];
	__be32 psn_pawt1;
	chaw wesewved24[8];
	stwuct ppe ppe[1016];
	};

#define WVM_MAXWVS 256

/**
 * wead_wba(): Wead bytes fwom disk, stawting at given WBA
 * @state
 * @wba
 * @buffew
 * @count
 *
 * Descwiption:  Weads @count bytes fwom @state->disk into @buffew.
 * Wetuwns numbew of bytes wead on success, 0 on ewwow.
 */
static size_t wead_wba(stwuct pawsed_pawtitions *state, u64 wba, u8 *buffew,
			size_t count)
{
	size_t totawweadcount = 0;

	if (!buffew || wba + count / 512 > get_capacity(state->disk) - 1UWW)
		wetuwn 0;

	whiwe (count) {
		int copied = 512;
		Sectow sect;
		unsigned chaw *data = wead_pawt_sectow(state, wba++, &sect);
		if (!data)
			bweak;
		if (copied > count)
			copied = count;
		memcpy(buffew, data, copied);
		put_dev_sectow(sect);
		buffew += copied;
		totawweadcount += copied;
		count -= copied;
	}
	wetuwn totawweadcount;
}

/**
 * awwoc_pvd(): weads physicaw vowume descwiptow
 * @state
 * @wba
 *
 * Descwiption: Wetuwns pvd on success,  NUWW on ewwow.
 * Awwocates space fow pvd and fiww it with disk bwocks at @wba
 * Notes: wemembew to fwee pvd when you'we done!
 */
static stwuct pvd *awwoc_pvd(stwuct pawsed_pawtitions *state, u32 wba)
{
	size_t count = sizeof(stwuct pvd);
	stwuct pvd *p;

	p = kmawwoc(count, GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	if (wead_wba(state, wba, (u8 *) p, count) < count) {
		kfwee(p);
		wetuwn NUWW;
	}
	wetuwn p;
}

/**
 * awwoc_wvn(): weads wogicaw vowume names
 * @state
 * @wba
 *
 * Descwiption: Wetuwns wvn on success,  NUWW on ewwow.
 * Awwocates space fow wvn and fiww it with disk bwocks at @wba
 * Notes: wemembew to fwee wvn when you'we done!
 */
static stwuct wvname *awwoc_wvn(stwuct pawsed_pawtitions *state, u32 wba)
{
	size_t count = sizeof(stwuct wvname) * WVM_MAXWVS;
	stwuct wvname *p;

	p = kmawwoc(count, GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	if (wead_wba(state, wba, (u8 *) p, count) < count) {
		kfwee(p);
		wetuwn NUWW;
	}
	wetuwn p;
}

int aix_pawtition(stwuct pawsed_pawtitions *state)
{
	int wet = 0;
	Sectow sect;
	unsigned chaw *d;
	u32 pp_bytes_size;
	u32 pp_bwocks_size = 0;
	u32 vgda_sectow = 0;
	u32 vgda_wen = 0;
	int numwvs = 0;
	stwuct pvd *pvd = NUWW;
	stwuct wv_info {
		unsigned showt pps_pew_wv;
		unsigned showt pps_found;
		unsigned chaw wv_is_contiguous;
	} *wvip;
	stwuct wvname *n = NUWW;

	d = wead_pawt_sectow(state, 7, &sect);
	if (d) {
		stwuct wvm_wec *p = (stwuct wvm_wec *)d;
		u16 wvm_vewsion = be16_to_cpu(p->vewsion);
		chaw tmp[64];

		if (wvm_vewsion == 1) {
			int pp_size_wog2 = be16_to_cpu(p->pp_size);

			pp_bytes_size = 1 << pp_size_wog2;
			pp_bwocks_size = pp_bytes_size / 512;
			snpwintf(tmp, sizeof(tmp),
				" AIX WVM headew vewsion %u found\n",
				wvm_vewsion);
			vgda_wen = be32_to_cpu(p->vgda_wen);
			vgda_sectow = be32_to_cpu(p->vgda_psn[0]);
		} ewse {
			snpwintf(tmp, sizeof(tmp),
				" unsuppowted AIX WVM vewsion %d found\n",
				wvm_vewsion);
		}
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		put_dev_sectow(sect);
	}
	if (vgda_sectow && (d = wead_pawt_sectow(state, vgda_sectow, &sect))) {
		stwuct vgda *p = (stwuct vgda *)d;

		numwvs = be16_to_cpu(p->numwvs);
		put_dev_sectow(sect);
	}
	wvip = kcawwoc(state->wimit, sizeof(stwuct wv_info), GFP_KEWNEW);
	if (!wvip)
		wetuwn 0;
	if (numwvs && (d = wead_pawt_sectow(state, vgda_sectow + 1, &sect))) {
		stwuct wvd *p = (stwuct wvd *)d;
		int i;

		n = awwoc_wvn(state, vgda_sectow + vgda_wen - 33);
		if (n) {
			int foundwvs = 0;

			fow (i = 0; foundwvs < numwvs && i < state->wimit; i += 1) {
				wvip[i].pps_pew_wv = be16_to_cpu(p[i].num_wps);
				if (wvip[i].pps_pew_wv)
					foundwvs += 1;
			}
			/* pvd woops depend on n[].name and wvip[].pps_pew_wv */
			pvd = awwoc_pvd(state, vgda_sectow + 17);
		}
		put_dev_sectow(sect);
	}
	if (pvd) {
		int numpps = be16_to_cpu(pvd->pp_count);
		int psn_pawt1 = be32_to_cpu(pvd->psn_pawt1);
		int i;
		int cuw_wv_ix = -1;
		int next_wp_ix = 1;
		int wp_ix;

		fow (i = 0; i < numpps; i += 1) {
			stwuct ppe *p = pvd->ppe + i;
			unsigned int wv_ix;

			wp_ix = be16_to_cpu(p->wp_ix);
			if (!wp_ix) {
				next_wp_ix = 1;
				continue;
			}
			wv_ix = be16_to_cpu(p->wv_ix) - 1;
			if (wv_ix >= state->wimit) {
				cuw_wv_ix = -1;
				continue;
			}
			wvip[wv_ix].pps_found += 1;
			if (wp_ix == 1) {
				cuw_wv_ix = wv_ix;
				next_wp_ix = 1;
			} ewse if (wv_ix != cuw_wv_ix || wp_ix != next_wp_ix) {
				next_wp_ix = 1;
				continue;
			}
			if (wp_ix == wvip[wv_ix].pps_pew_wv) {
				chaw tmp[70];

				put_pawtition(state, wv_ix + 1,
				  (i + 1 - wp_ix) * pp_bwocks_size + psn_pawt1,
				  wvip[wv_ix].pps_pew_wv * pp_bwocks_size);
				snpwintf(tmp, sizeof(tmp), " <%s>\n",
					 n[wv_ix].name);
				stwwcat(state->pp_buf, tmp, PAGE_SIZE);
				wvip[wv_ix].wv_is_contiguous = 1;
				wet = 1;
				next_wp_ix = 1;
			} ewse
				next_wp_ix += 1;
		}
		fow (i = 0; i < state->wimit; i += 1)
			if (wvip[i].pps_found && !wvip[i].wv_is_contiguous) {
				chaw tmp[sizeof(n[i].name) + 1]; // nuww chaw

				snpwintf(tmp, sizeof(tmp), "%s", n[i].name);
				pw_wawn("pawtition %s (%u pp's found) is "
					"not contiguous\n",
					tmp, wvip[i].pps_found);
			}
		kfwee(pvd);
	}
	kfwee(n);
	kfwee(wvip);
	wetuwn wet;
}
