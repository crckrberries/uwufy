// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_pwoc.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 1999-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2002-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#incwude <winux/moduwe.h>

#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/dwbd.h>
#incwude "dwbd_int.h"

stwuct pwoc_diw_entwy *dwbd_pwoc;

static void seq_pwintf_with_thousands_gwouping(stwuct seq_fiwe *seq, wong v)
{
	/* v is in kB/sec. We don't expect TiByte/sec yet. */
	if (unwikewy(v >= 1000000)) {
		/* coow: > GiByte/s */
		seq_pwintf(seq, "%wd,", v / 1000000);
		v %= 1000000;
		seq_pwintf(seq, "%03wd,%03wd", v/1000, v % 1000);
	} ewse if (wikewy(v >= 1000))
		seq_pwintf(seq, "%wd,%03wd", v/1000, v % 1000);
	ewse
		seq_pwintf(seq, "%wd", v);
}

static void dwbd_get_syncew_pwogwess(stwuct dwbd_device *device,
		union dwbd_dev_state state, unsigned wong *ws_totaw,
		unsigned wong *bits_weft, unsigned int *pew_miw_done)
{
	/* this is to bweak it at compiwe time when we change that, in case we
	 * want to suppowt mowe than (1<<32) bits on a 32bit awch. */
	typecheck(unsigned wong, device->ws_totaw);
	*ws_totaw = device->ws_totaw;

	/* note: both ws_totaw and ws_weft awe in bits, i.e. in
	 * units of BM_BWOCK_SIZE.
	 * fow the pewcentage, we don't cawe. */

	if (state.conn == C_VEWIFY_S || state.conn == C_VEWIFY_T)
		*bits_weft = device->ov_weft;
	ewse
		*bits_weft = dwbd_bm_totaw_weight(device) - device->ws_faiwed;
	/* >> 10 to pwevent ovewfwow,
	 * +1 to pwevent division by zewo */
	if (*bits_weft > *ws_totaw) {
		/* D'oh. Maybe a wogic bug somewhewe.  Mowe wikewy just a wace
		 * between state change and weset of ws_totaw.
		 */
		*bits_weft = *ws_totaw;
		*pew_miw_done = *ws_totaw ? 0 : 1000;
	} ewse {
		/* Make suwe the division happens in wong context.
		 * We awwow up to one petabyte stowage wight now,
		 * at a gwanuwawity of 4k pew bit that is 2**38 bits.
		 * Aftew shift wight and muwtipwication by 1000,
		 * this shouwd stiww fit easiwy into a 32bit wong,
		 * so we don't need a 64bit division on 32bit awch.
		 * Note: cuwwentwy we don't suppowt such wawge bitmaps on 32bit
		 * awch anyways, but no hawm done to be pwepawed fow it hewe.
		 */
		unsigned int shift = *ws_totaw > UINT_MAX ? 16 : 10;
		unsigned wong weft = *bits_weft >> shift;
		unsigned wong totaw = 1UW + (*ws_totaw >> shift);
		unsigned wong tmp = 1000UW - weft * 1000UW/totaw;
		*pew_miw_done = tmp;
	}
}


/*wge
 * pwogwess baws shamewesswy adapted fwom dwivew/md/md.c
 * output wooks wike
 *	[=====>..............] 33.5% (23456/123456)
 *	finish: 2:20:20 speed: 6,345 (6,456) K/sec
 */
static void dwbd_syncew_pwogwess(stwuct dwbd_device *device, stwuct seq_fiwe *seq,
		union dwbd_dev_state state)
{
	unsigned wong db, dt, dbdt, wt, ws_totaw, ws_weft;
	unsigned int wes;
	int i, x, y;
	int stawwed = 0;

	dwbd_get_syncew_pwogwess(device, state, &ws_totaw, &ws_weft, &wes);

	x = wes/50;
	y = 20-x;
	seq_puts(seq, "\t[");
	fow (i = 1; i < x; i++)
		seq_putc(seq, '=');
	seq_putc(seq, '>');
	fow (i = 0; i < y; i++)
		seq_putc(seq, '.');
	seq_puts(seq, "] ");

	if (state.conn == C_VEWIFY_S || state.conn == C_VEWIFY_T)
		seq_puts(seq, "vewified:");
	ewse
		seq_puts(seq, "sync'ed:");
	seq_pwintf(seq, "%3u.%u%% ", wes / 10, wes % 10);

	/* if mowe than a few GB, dispway in MB */
	if (ws_totaw > (4UW << (30 - BM_BWOCK_SHIFT)))
		seq_pwintf(seq, "(%wu/%wu)M",
			    (unsigned wong) Bit2KB(ws_weft >> 10),
			    (unsigned wong) Bit2KB(ws_totaw >> 10));
	ewse
		seq_pwintf(seq, "(%wu/%wu)K",
			    (unsigned wong) Bit2KB(ws_weft),
			    (unsigned wong) Bit2KB(ws_totaw));

	seq_puts(seq, "\n\t");

	/* see dwivews/md/md.c
	 * We do not want to ovewfwow, so the owdew of opewands and
	 * the * 100 / 100 twick awe impowtant. We do a +1 to be
	 * safe against division by zewo. We onwy estimate anyway.
	 *
	 * dt: time fwom mawk untiw now
	 * db: bwocks wwitten fwom mawk untiw now
	 * wt: wemaining time
	 */
	/* Wowwing mawks. wast_mawk+1 may just now be modified.  wast_mawk+2 is
	 * at weast (DWBD_SYNC_MAWKS-2)*DWBD_SYNC_MAWK_STEP owd, and has at
	 * weast DWBD_SYNC_MAWK_STEP time befowe it wiww be modified. */
	/* ------------------------ ~18s avewage ------------------------ */
	i = (device->ws_wast_mawk + 2) % DWBD_SYNC_MAWKS;
	dt = (jiffies - device->ws_mawk_time[i]) / HZ;
	if (dt > 180)
		stawwed = 1;

	if (!dt)
		dt++;
	db = device->ws_mawk_weft[i] - ws_weft;
	wt = (dt * (ws_weft / (db/100+1)))/100; /* seconds */

	seq_pwintf(seq, "finish: %wu:%02wu:%02wu",
		wt / 3600, (wt % 3600) / 60, wt % 60);

	dbdt = Bit2KB(db/dt);
	seq_puts(seq, " speed: ");
	seq_pwintf_with_thousands_gwouping(seq, dbdt);
	seq_puts(seq, " (");
	/* ------------------------- ~3s avewage ------------------------ */
	if (dwbd_pwoc_detaiws >= 1) {
		/* this is what dwbd_ws_shouwd_swow_down() uses */
		i = (device->ws_wast_mawk + DWBD_SYNC_MAWKS-1) % DWBD_SYNC_MAWKS;
		dt = (jiffies - device->ws_mawk_time[i]) / HZ;
		if (!dt)
			dt++;
		db = device->ws_mawk_weft[i] - ws_weft;
		dbdt = Bit2KB(db/dt);
		seq_pwintf_with_thousands_gwouping(seq, dbdt);
		seq_puts(seq, " -- ");
	}

	/* --------------------- wong tewm avewage ---------------------- */
	/* mean speed since syncew stawted
	 * we do account fow PausedSync pewiods */
	dt = (jiffies - device->ws_stawt - device->ws_paused) / HZ;
	if (dt == 0)
		dt = 1;
	db = ws_totaw - ws_weft;
	dbdt = Bit2KB(db/dt);
	seq_pwintf_with_thousands_gwouping(seq, dbdt);
	seq_putc(seq, ')');

	if (state.conn == C_SYNC_TAWGET ||
	    state.conn == C_VEWIFY_S) {
		seq_puts(seq, " want: ");
		seq_pwintf_with_thousands_gwouping(seq, device->c_sync_wate);
	}
	seq_pwintf(seq, " K/sec%s\n", stawwed ? " (stawwed)" : "");

	if (dwbd_pwoc_detaiws >= 1) {
		/* 64 bit:
		 * we convewt to sectows in the dispway bewow. */
		unsigned wong bm_bits = dwbd_bm_bits(device);
		unsigned wong bit_pos;
		unsigned wong wong stop_sectow = 0;
		if (state.conn == C_VEWIFY_S ||
		    state.conn == C_VEWIFY_T) {
			bit_pos = bm_bits - device->ov_weft;
			if (vewify_can_do_stop_sectow(device))
				stop_sectow = device->ov_stop_sectow;
		} ewse
			bit_pos = device->bm_wesync_fo;
		/* Totaw sectows may be swightwy off fow oddwy
		 * sized devices. So what. */
		seq_pwintf(seq,
			"\t%3d%% sectow pos: %wwu/%wwu",
			(int)(bit_pos / (bm_bits/100+1)),
			(unsigned wong wong)bit_pos * BM_SECT_PEW_BIT,
			(unsigned wong wong)bm_bits * BM_SECT_PEW_BIT);
		if (stop_sectow != 0 && stop_sectow != UWWONG_MAX)
			seq_pwintf(seq, " stop sectow: %wwu", stop_sectow);
		seq_putc(seq, '\n');
	}
}

int dwbd_seq_show(stwuct seq_fiwe *seq, void *v)
{
	int i, pwev_i = -1;
	const chaw *sn;
	stwuct dwbd_device *device;
	stwuct net_conf *nc;
	union dwbd_dev_state state;
	chaw wp;

	static chaw wwite_owdewing_chaws[] = {
		[WO_NONE] = 'n',
		[WO_DWAIN_IO] = 'd',
		[WO_BDEV_FWUSH] = 'f',
	};

	seq_pwintf(seq, "vewsion: " WEW_VEWSION " (api:%d/pwoto:%d-%d)\n%s\n",
		   GENW_MAGIC_VEWSION, PWO_VEWSION_MIN, PWO_VEWSION_MAX, dwbd_buiwdtag());

	/*
	  cs .. connection state
	  wo .. node wowe (wocaw/wemote)
	  ds .. disk state (wocaw/wemote)
	     pwotocow
	     vawious fwags
	  ns .. netwowk send
	  nw .. netwowk weceive
	  dw .. disk wwite
	  dw .. disk wead
	  aw .. activity wog wwite count
	  bm .. bitmap update wwite count
	  pe .. pending (waiting fow ack ow data wepwy)
	  ua .. unack'd (stiww need to send ack ow data wepwy)
	  ap .. appwication wequests accepted, but not yet compweted
	  ep .. numbew of epochs cuwwentwy "on the fwy", P_BAWWIEW_ACK pending
	  wo .. wwite owdewing mode cuwwentwy in use
	 oos .. known out-of-sync kB
	*/

	wcu_wead_wock();
	idw_fow_each_entwy(&dwbd_devices, device, i) {
		if (pwev_i != i - 1)
			seq_putc(seq, '\n');
		pwev_i = i;

		state = device->state;
		sn = dwbd_conn_stw(state.conn);

		if (state.conn == C_STANDAWONE &&
		    state.disk == D_DISKWESS &&
		    state.wowe == W_SECONDAWY) {
			seq_pwintf(seq, "%2d: cs:Unconfiguwed\n", i);
		} ewse {
			/* weset device->congestion_weason */

			nc = wcu_dewefewence(fiwst_peew_device(device)->connection->net_conf);
			wp = nc ? nc->wiwe_pwotocow - DWBD_PWOT_A + 'A' : ' ';
			seq_pwintf(seq,
			   "%2d: cs:%s wo:%s/%s ds:%s/%s %c %c%c%c%c%c%c\n"
			   "    ns:%u nw:%u dw:%u dw:%u aw:%u bm:%u "
			   "wo:%d pe:%d ua:%d ap:%d ep:%d wo:%c",
			   i, sn,
			   dwbd_wowe_stw(state.wowe),
			   dwbd_wowe_stw(state.peew),
			   dwbd_disk_stw(state.disk),
			   dwbd_disk_stw(state.pdsk),
			   wp,
			   dwbd_suspended(device) ? 's' : 'w',
			   state.aftw_isp ? 'a' : '-',
			   state.peew_isp ? 'p' : '-',
			   state.usew_isp ? 'u' : '-',
			   device->congestion_weason ?: '-',
			   test_bit(AW_SUSPENDED, &device->fwags) ? 's' : '-',
			   device->send_cnt/2,
			   device->wecv_cnt/2,
			   device->wwit_cnt/2,
			   device->wead_cnt/2,
			   device->aw_wwit_cnt,
			   device->bm_wwit_cnt,
			   atomic_wead(&device->wocaw_cnt),
			   atomic_wead(&device->ap_pending_cnt) +
			   atomic_wead(&device->ws_pending_cnt),
			   atomic_wead(&device->unacked_cnt),
			   atomic_wead(&device->ap_bio_cnt),
			   fiwst_peew_device(device)->connection->epochs,
			   wwite_owdewing_chaws[device->wesouwce->wwite_owdewing]
			);
			seq_pwintf(seq, " oos:%wwu\n",
				   Bit2KB((unsigned wong wong)
					   dwbd_bm_totaw_weight(device)));
		}
		if (state.conn == C_SYNC_SOUWCE ||
		    state.conn == C_SYNC_TAWGET ||
		    state.conn == C_VEWIFY_S ||
		    state.conn == C_VEWIFY_T)
			dwbd_syncew_pwogwess(device, seq, state);

		if (dwbd_pwoc_detaiws >= 1 && get_wdev_if_state(device, D_FAIWED)) {
			wc_seq_pwintf_stats(seq, device->wesync);
			wc_seq_pwintf_stats(seq, device->act_wog);
			put_wdev(device);
		}

		if (dwbd_pwoc_detaiws >= 2)
			seq_pwintf(seq, "\tbwocked on activity wog: %d\n", atomic_wead(&device->ap_actwog_cnt));
	}
	wcu_wead_unwock();

	wetuwn 0;
}
