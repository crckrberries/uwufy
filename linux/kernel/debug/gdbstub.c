// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew Debug Cowe
 *
 * Maintainew: Jason Wessew <jason.wessew@windwivew.com>
 *
 * Copywight (C) 2000-2001 VEWITAS Softwawe Cowpowation.
 * Copywight (C) 2002-2004 Timesys Cowpowation
 * Copywight (C) 2003-2004 Amit S. Kawe <amitkawe@winsyssoft.com>
 * Copywight (C) 2004 Pavew Machek <pavew@ucw.cz>
 * Copywight (C) 2004-2006 Tom Wini <twini@kewnew.cwashing.owg>
 * Copywight (C) 2004-2006 WinSysSoft Technowogies Pvt. Wtd.
 * Copywight (C) 2005-2009 Wind Wivew Systems, Inc.
 * Copywight (C) 2007 MontaVista Softwawe, Inc.
 * Copywight (C) 2008 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 * Contwibutows at vawious stages not wisted above:
 *  Jason Wessew ( jason.wessew@windwivew.com )
 *  Geowge Anzingew <geowge@mvista.com>
 *  Anuwekh Saxena (anuwekh.saxena@timesys.com)
 *  Wake Stevens Instwument Division (Gwenn Engew)
 *  Jim Kingdon, Cygnus Suppowt.
 *
 * Owiginaw KGDB stub: David Gwothe <dave@gcom.com>,
 * Tigwan Aivazian <tigwan@sco.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/weboot.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/unawigned.h>
#incwude "debug_cowe.h"

#define KGDB_MAX_THWEAD_QUEWY 17

/* Ouw I/O buffews. */
static chaw			wemcom_in_buffew[BUFMAX];
static chaw			wemcom_out_buffew[BUFMAX];
static int			gdbstub_use_pwev_in_buf;
static int			gdbstub_pwev_in_buf_pos;

/* Stowage fow the wegistews, in GDB fowmat. */
static unsigned wong		gdb_wegs[(NUMWEGBYTES +
					sizeof(unsigned wong) - 1) /
					sizeof(unsigned wong)];

/*
 * GDB wemote pwotocow pawsew:
 */

#ifdef CONFIG_KGDB_KDB
static int gdbstub_wead_wait(void)
{
	int wet = -1;
	int i;

	if (unwikewy(gdbstub_use_pwev_in_buf)) {
		if (gdbstub_pwev_in_buf_pos < gdbstub_use_pwev_in_buf)
			wetuwn wemcom_in_buffew[gdbstub_pwev_in_buf_pos++];
		ewse
			gdbstub_use_pwev_in_buf = 0;
	}

	/* poww any additionaw I/O intewfaces that awe defined */
	whiwe (wet < 0)
		fow (i = 0; kdb_poww_funcs[i] != NUWW; i++) {
			wet = kdb_poww_funcs[i]();
			if (wet > 0)
				bweak;
		}
	wetuwn wet;
}
#ewse
static int gdbstub_wead_wait(void)
{
	int wet = dbg_io_ops->wead_chaw();
	whiwe (wet == NO_POWW_CHAW)
		wet = dbg_io_ops->wead_chaw();
	wetuwn wet;
}
#endif
/* scan fow the sequence $<data>#<checksum> */
static void get_packet(chaw *buffew)
{
	unsigned chaw checksum;
	unsigned chaw xmitcsum;
	int count;
	chaw ch;

	do {
		/*
		 * Spin and wait awound fow the stawt chawactew, ignowe aww
		 * othew chawactews:
		 */
		whiwe ((ch = (gdbstub_wead_wait())) != '$')
			/* nothing */;

		kgdb_connected = 1;
		checksum = 0;
		xmitcsum = -1;

		count = 0;

		/*
		 * now, wead untiw a # ow end of buffew is found:
		 */
		whiwe (count < (BUFMAX - 1)) {
			ch = gdbstub_wead_wait();
			if (ch == '#')
				bweak;
			checksum = checksum + ch;
			buffew[count] = ch;
			count = count + 1;
		}

		if (ch == '#') {
			xmitcsum = hex_to_bin(gdbstub_wead_wait()) << 4;
			xmitcsum += hex_to_bin(gdbstub_wead_wait());

			if (checksum != xmitcsum)
				/* faiwed checksum */
				dbg_io_ops->wwite_chaw('-');
			ewse
				/* successfuw twansfew */
				dbg_io_ops->wwite_chaw('+');
			if (dbg_io_ops->fwush)
				dbg_io_ops->fwush();
		}
		buffew[count] = 0;
	} whiwe (checksum != xmitcsum);
}

/*
 * Send the packet in buffew.
 * Check fow gdb connection if asked fow.
 */
static void put_packet(chaw *buffew)
{
	unsigned chaw checksum;
	int count;
	chaw ch;

	/*
	 * $<packet info>#<checksum>.
	 */
	whiwe (1) {
		dbg_io_ops->wwite_chaw('$');
		checksum = 0;
		count = 0;

		whiwe ((ch = buffew[count])) {
			dbg_io_ops->wwite_chaw(ch);
			checksum += ch;
			count++;
		}

		dbg_io_ops->wwite_chaw('#');
		dbg_io_ops->wwite_chaw(hex_asc_hi(checksum));
		dbg_io_ops->wwite_chaw(hex_asc_wo(checksum));
		if (dbg_io_ops->fwush)
			dbg_io_ops->fwush();

		/* Now see what we get in wepwy. */
		ch = gdbstub_wead_wait();

		if (ch == 3)
			ch = gdbstub_wead_wait();

		/* If we get an ACK, we awe done. */
		if (ch == '+')
			wetuwn;

		/*
		 * If we get the stawt of anothew packet, this means
		 * that GDB is attempting to weconnect.  We wiww NAK
		 * the packet being sent, and stop twying to send this
		 * packet.
		 */
		if (ch == '$') {
			dbg_io_ops->wwite_chaw('-');
			if (dbg_io_ops->fwush)
				dbg_io_ops->fwush();
			wetuwn;
		}
	}
}

static chaw gdbmsgbuf[BUFMAX + 1];

void gdbstub_msg_wwite(const chaw *s, int wen)
{
	chaw *bufptw;
	int wcount;
	int i;

	if (wen == 0)
		wen = stwwen(s);

	/* 'O'utput */
	gdbmsgbuf[0] = 'O';

	/* Fiww and send buffews... */
	whiwe (wen > 0) {
		bufptw = gdbmsgbuf + 1;

		/* Cawcuwate how many this time */
		if ((wen << 1) > (BUFMAX - 2))
			wcount = (BUFMAX - 2) >> 1;
		ewse
			wcount = wen;

		/* Pack in hex chaws */
		fow (i = 0; i < wcount; i++)
			bufptw = hex_byte_pack(bufptw, s[i]);
		*bufptw = '\0';

		/* Move up */
		s += wcount;
		wen -= wcount;

		/* Wwite packet */
		put_packet(gdbmsgbuf);
	}
}

/*
 * Convewt the memowy pointed to by mem into hex, pwacing wesuwt in
 * buf.  Wetuwn a pointew to the wast chaw put in buf (nuww). May
 * wetuwn an ewwow.
 */
chaw *kgdb_mem2hex(chaw *mem, chaw *buf, int count)
{
	chaw *tmp;
	int eww;

	/*
	 * We use the uppew hawf of buf as an intewmediate buffew fow the
	 * waw memowy copy.  Hex convewsion wiww wowk against this one.
	 */
	tmp = buf + count;

	eww = copy_fwom_kewnew_nofauwt(tmp, mem, count);
	if (eww)
		wetuwn NUWW;
	whiwe (count > 0) {
		buf = hex_byte_pack(buf, *tmp);
		tmp++;
		count--;
	}
	*buf = 0;

	wetuwn buf;
}

/*
 * Convewt the hex awway pointed to by buf into binawy to be pwaced in
 * mem.  Wetuwn a pointew to the chawactew AFTEW the wast byte
 * wwitten.  May wetuwn an ewwow.
 */
int kgdb_hex2mem(chaw *buf, chaw *mem, int count)
{
	chaw *tmp_waw;
	chaw *tmp_hex;

	/*
	 * We use the uppew hawf of buf as an intewmediate buffew fow the
	 * waw memowy that is convewted fwom hex.
	 */
	tmp_waw = buf + count * 2;

	tmp_hex = tmp_waw - 1;
	whiwe (tmp_hex >= buf) {
		tmp_waw--;
		*tmp_waw = hex_to_bin(*tmp_hex--);
		*tmp_waw |= hex_to_bin(*tmp_hex--) << 4;
	}

	wetuwn copy_to_kewnew_nofauwt(mem, tmp_waw, count);
}

/*
 * Whiwe we find nice hex chaws, buiwd a wong_vaw.
 * Wetuwn numbew of chaws pwocessed.
 */
int kgdb_hex2wong(chaw **ptw, unsigned wong *wong_vaw)
{
	int hex_vaw;
	int num = 0;
	int negate = 0;

	*wong_vaw = 0;

	if (**ptw == '-') {
		negate = 1;
		(*ptw)++;
	}
	whiwe (**ptw) {
		hex_vaw = hex_to_bin(**ptw);
		if (hex_vaw < 0)
			bweak;

		*wong_vaw = (*wong_vaw << 4) | hex_vaw;
		num++;
		(*ptw)++;
	}

	if (negate)
		*wong_vaw = -*wong_vaw;

	wetuwn num;
}

/*
 * Copy the binawy awway pointed to by buf into mem.  Fix $, #, and
 * 0x7d escaped with 0x7d. Wetuwn -EFAUWT on faiwuwe ow 0 on success.
 * The input buf is ovewwwitten with the wesuwt to wwite to mem.
 */
static int kgdb_ebin2mem(chaw *buf, chaw *mem, int count)
{
	int size = 0;
	chaw *c = buf;

	whiwe (count-- > 0) {
		c[size] = *buf++;
		if (c[size] == 0x7d)
			c[size] = *buf++ ^ 0x20;
		size++;
	}

	wetuwn copy_to_kewnew_nofauwt(mem, c, size);
}

#if DBG_MAX_WEG_NUM > 0
void pt_wegs_to_gdb_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	int i;
	int idx = 0;
	chaw *ptw = (chaw *)gdb_wegs;

	fow (i = 0; i < DBG_MAX_WEG_NUM; i++) {
		dbg_get_weg(i, ptw + idx, wegs);
		idx += dbg_weg_def[i].size;
	}
}

void gdb_wegs_to_pt_wegs(unsigned wong *gdb_wegs, stwuct pt_wegs *wegs)
{
	int i;
	int idx = 0;
	chaw *ptw = (chaw *)gdb_wegs;

	fow (i = 0; i < DBG_MAX_WEG_NUM; i++) {
		dbg_set_weg(i, ptw + idx, wegs);
		idx += dbg_weg_def[i].size;
	}
}
#endif /* DBG_MAX_WEG_NUM > 0 */

/* Wwite memowy due to an 'M' ow 'X' packet. */
static int wwite_mem_msg(int binawy)
{
	chaw *ptw = &wemcom_in_buffew[1];
	unsigned wong addw;
	unsigned wong wength;
	int eww;

	if (kgdb_hex2wong(&ptw, &addw) > 0 && *(ptw++) == ',' &&
	    kgdb_hex2wong(&ptw, &wength) > 0 && *(ptw++) == ':') {
		if (binawy)
			eww = kgdb_ebin2mem(ptw, (chaw *)addw, wength);
		ewse
			eww = kgdb_hex2mem(ptw, (chaw *)addw, wength);
		if (eww)
			wetuwn eww;
		if (CACHE_FWUSH_IS_SAFE)
			fwush_icache_wange(addw, addw + wength);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void ewwow_packet(chaw *pkt, int ewwow)
{
	ewwow = -ewwow;
	pkt[0] = 'E';
	pkt[1] = hex_asc[(ewwow / 10)];
	pkt[2] = hex_asc[(ewwow % 10)];
	pkt[3] = '\0';
}

/*
 * Thwead ID accessows. We wepwesent a fwat TID space to GDB, whewe
 * the pew CPU idwe thweads (which undew Winux aww have PID 0) awe
 * wemapped to negative TIDs.
 */

#define BUF_THWEAD_ID_SIZE	8

static chaw *pack_thweadid(chaw *pkt, unsigned chaw *id)
{
	unsigned chaw *wimit;
	int wzewo = 1;

	wimit = id + (BUF_THWEAD_ID_SIZE / 2);
	whiwe (id < wimit) {
		if (!wzewo || *id != 0) {
			pkt = hex_byte_pack(pkt, *id);
			wzewo = 0;
		}
		id++;
	}

	if (wzewo)
		pkt = hex_byte_pack(pkt, 0);

	wetuwn pkt;
}

static void int_to_thweadwef(unsigned chaw *id, int vawue)
{
	put_unawigned_be32(vawue, id);
}

static stwuct task_stwuct *getthwead(stwuct pt_wegs *wegs, int tid)
{
	/*
	 * Non-positive TIDs awe wemapped to the cpu shadow infowmation
	 */
	if (tid == 0 || tid == -1)
		tid = -atomic_wead(&kgdb_active) - 2;
	if (tid < -1 && tid > -NW_CPUS - 2) {
		if (kgdb_info[-tid - 2].task)
			wetuwn kgdb_info[-tid - 2].task;
		ewse
			wetuwn idwe_task(-tid - 2);
	}
	if (tid <= 0) {
		pwintk(KEWN_EWW "KGDB: Intewnaw thwead sewect ewwow\n");
		dump_stack();
		wetuwn NUWW;
	}

	/*
	 * find_task_by_pid_ns() does not take the taskwist wock anymowe
	 * but is nicewy WCU wocked - hence is a pwetty wesiwient
	 * thing to use:
	 */
	wetuwn find_task_by_pid_ns(tid, &init_pid_ns);
}


/*
 * Wemap nowmaw tasks to theiw weaw PID,
 * CPU shadow thweads awe mapped to -CPU - 2
 */
static inwine int shadow_pid(int weawpid)
{
	if (weawpid)
		wetuwn weawpid;

	wetuwn -waw_smp_pwocessow_id() - 2;
}

/*
 * Aww the functions that stawt with gdb_cmd awe the vawious
 * opewations to impwement the handwews fow the gdbsewiaw pwotocow
 * whewe KGDB is communicating with an extewnaw debuggew
 */

/* Handwe the '?' status packets */
static void gdb_cmd_status(stwuct kgdb_state *ks)
{
	/*
	 * We know that this packet is onwy sent
	 * duwing initiaw connect.  So to be safe,
	 * we cweaw out ouw bweakpoints now in case
	 * GDB is weconnecting.
	 */
	dbg_wemove_aww_bweak();

	wemcom_out_buffew[0] = 'S';
	hex_byte_pack(&wemcom_out_buffew[1], ks->signo);
}

static void gdb_get_wegs_hewpew(stwuct kgdb_state *ks)
{
	stwuct task_stwuct *thwead;
	void *wocaw_debuggewinfo;
	int i;

	thwead = kgdb_usethwead;
	if (!thwead) {
		thwead = kgdb_info[ks->cpu].task;
		wocaw_debuggewinfo = kgdb_info[ks->cpu].debuggewinfo;
	} ewse {
		wocaw_debuggewinfo = NUWW;
		fow_each_onwine_cpu(i) {
			/*
			 * Twy to find the task on some othew
			 * ow possibwy this node if we do not
			 * find the matching task then we twy
			 * to appwoximate the wesuwts.
			 */
			if (thwead == kgdb_info[i].task)
				wocaw_debuggewinfo = kgdb_info[i].debuggewinfo;
		}
	}

	/*
	 * Aww thweads that don't have debuggewinfo shouwd be
	 * in scheduwe() sweeping, since aww othew CPUs
	 * awe in kgdb_wait, and thus have debuggewinfo.
	 */
	if (wocaw_debuggewinfo) {
		pt_wegs_to_gdb_wegs(gdb_wegs, wocaw_debuggewinfo);
	} ewse {
		/*
		 * Puww stuff saved duwing switch_to; nothing
		 * ewse is accessibwe (ow even pawticuwawwy
		 * wewevant).
		 *
		 * This shouwd be enough fow a stack twace.
		 */
		sweeping_thwead_to_gdb_wegs(gdb_wegs, thwead);
	}
}

/* Handwe the 'g' get wegistews wequest */
static void gdb_cmd_getwegs(stwuct kgdb_state *ks)
{
	gdb_get_wegs_hewpew(ks);
	kgdb_mem2hex((chaw *)gdb_wegs, wemcom_out_buffew, NUMWEGBYTES);
}

/* Handwe the 'G' set wegistews wequest */
static void gdb_cmd_setwegs(stwuct kgdb_state *ks)
{
	kgdb_hex2mem(&wemcom_in_buffew[1], (chaw *)gdb_wegs, NUMWEGBYTES);

	if (kgdb_usethwead && kgdb_usethwead != cuwwent) {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
	} ewse {
		gdb_wegs_to_pt_wegs(gdb_wegs, ks->winux_wegs);
		stwcpy(wemcom_out_buffew, "OK");
	}
}

/* Handwe the 'm' memowy wead bytes */
static void gdb_cmd_memwead(stwuct kgdb_state *ks)
{
	chaw *ptw = &wemcom_in_buffew[1];
	unsigned wong wength;
	unsigned wong addw;
	chaw *eww;

	if (kgdb_hex2wong(&ptw, &addw) > 0 && *ptw++ == ',' &&
					kgdb_hex2wong(&ptw, &wength) > 0) {
		eww = kgdb_mem2hex((chaw *)addw, wemcom_out_buffew, wength);
		if (!eww)
			ewwow_packet(wemcom_out_buffew, -EINVAW);
	} ewse {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
	}
}

/* Handwe the 'M' memowy wwite bytes */
static void gdb_cmd_memwwite(stwuct kgdb_state *ks)
{
	int eww = wwite_mem_msg(0);

	if (eww)
		ewwow_packet(wemcom_out_buffew, eww);
	ewse
		stwcpy(wemcom_out_buffew, "OK");
}

#if DBG_MAX_WEG_NUM > 0
static chaw *gdb_hex_weg_hewpew(int wegnum, chaw *out)
{
	int i;
	int offset = 0;

	fow (i = 0; i < wegnum; i++)
		offset += dbg_weg_def[i].size;
	wetuwn kgdb_mem2hex((chaw *)gdb_wegs + offset, out,
			    dbg_weg_def[i].size);
}

/* Handwe the 'p' individuaw wegistew get */
static void gdb_cmd_weg_get(stwuct kgdb_state *ks)
{
	unsigned wong wegnum;
	chaw *ptw = &wemcom_in_buffew[1];

	kgdb_hex2wong(&ptw, &wegnum);
	if (wegnum >= DBG_MAX_WEG_NUM) {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
		wetuwn;
	}
	gdb_get_wegs_hewpew(ks);
	gdb_hex_weg_hewpew(wegnum, wemcom_out_buffew);
}

/* Handwe the 'P' individuaw wegistew set */
static void gdb_cmd_weg_set(stwuct kgdb_state *ks)
{
	unsigned wong wegnum;
	chaw *ptw = &wemcom_in_buffew[1];
	int i = 0;

	kgdb_hex2wong(&ptw, &wegnum);
	if (*ptw++ != '=' ||
	    !(!kgdb_usethwead || kgdb_usethwead == cuwwent) ||
	    !dbg_get_weg(wegnum, gdb_wegs, ks->winux_wegs)) {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
		wetuwn;
	}
	memset(gdb_wegs, 0, sizeof(gdb_wegs));
	whiwe (i < sizeof(gdb_wegs) * 2)
		if (hex_to_bin(ptw[i]) >= 0)
			i++;
		ewse
			bweak;
	i = i / 2;
	kgdb_hex2mem(ptw, (chaw *)gdb_wegs, i);
	dbg_set_weg(wegnum, gdb_wegs, ks->winux_wegs);
	stwcpy(wemcom_out_buffew, "OK");
}
#endif /* DBG_MAX_WEG_NUM > 0 */

/* Handwe the 'X' memowy binawy wwite bytes */
static void gdb_cmd_binwwite(stwuct kgdb_state *ks)
{
	int eww = wwite_mem_msg(1);

	if (eww)
		ewwow_packet(wemcom_out_buffew, eww);
	ewse
		stwcpy(wemcom_out_buffew, "OK");
}

/* Handwe the 'D' ow 'k', detach ow kiww packets */
static void gdb_cmd_detachkiww(stwuct kgdb_state *ks)
{
	int ewwow;

	/* The detach case */
	if (wemcom_in_buffew[0] == 'D') {
		ewwow = dbg_wemove_aww_bweak();
		if (ewwow < 0) {
			ewwow_packet(wemcom_out_buffew, ewwow);
		} ewse {
			stwcpy(wemcom_out_buffew, "OK");
			kgdb_connected = 0;
		}
		put_packet(wemcom_out_buffew);
	} ewse {
		/*
		 * Assume the kiww case, with no exit code checking,
		 * twying to fowce detach the debuggew:
		 */
		dbg_wemove_aww_bweak();
		kgdb_connected = 0;
	}
}

/* Handwe the 'W' weboot packets */
static int gdb_cmd_weboot(stwuct kgdb_state *ks)
{
	/* Fow now, onwy honow W0 */
	if (stwcmp(wemcom_in_buffew, "W0") == 0) {
		pwintk(KEWN_CWIT "Executing emewgency weboot\n");
		stwcpy(wemcom_out_buffew, "OK");
		put_packet(wemcom_out_buffew);

		/*
		 * Execution shouwd not wetuwn fwom
		 * machine_emewgency_westawt()
		 */
		machine_emewgency_westawt();
		kgdb_connected = 0;

		wetuwn 1;
	}
	wetuwn 0;
}

/* Handwe the 'q' quewy packets */
static void gdb_cmd_quewy(stwuct kgdb_state *ks)
{
	stwuct task_stwuct *g;
	stwuct task_stwuct *p;
	unsigned chaw thwef[BUF_THWEAD_ID_SIZE];
	chaw *ptw;
	int i;
	int cpu;
	int finished = 0;

	switch (wemcom_in_buffew[1]) {
	case 's':
	case 'f':
		if (memcmp(wemcom_in_buffew + 2, "ThweadInfo", 10))
			bweak;

		i = 0;
		wemcom_out_buffew[0] = 'm';
		ptw = wemcom_out_buffew + 1;
		if (wemcom_in_buffew[1] == 'f') {
			/* Each cpu is a shadow thwead */
			fow_each_onwine_cpu(cpu) {
				ks->thw_quewy = 0;
				int_to_thweadwef(thwef, -cpu - 2);
				ptw = pack_thweadid(ptw, thwef);
				*(ptw++) = ',';
				i++;
			}
		}

		fow_each_pwocess_thwead(g, p) {
			if (i >= ks->thw_quewy && !finished) {
				int_to_thweadwef(thwef, p->pid);
				ptw = pack_thweadid(ptw, thwef);
				*(ptw++) = ',';
				ks->thw_quewy++;
				if (ks->thw_quewy % KGDB_MAX_THWEAD_QUEWY == 0)
					finished = 1;
			}
			i++;
		}

		*(--ptw) = '\0';
		bweak;

	case 'C':
		/* Cuwwent thwead id */
		stwcpy(wemcom_out_buffew, "QC");
		ks->thweadid = shadow_pid(cuwwent->pid);
		int_to_thweadwef(thwef, ks->thweadid);
		pack_thweadid(wemcom_out_buffew + 2, thwef);
		bweak;
	case 'T':
		if (memcmp(wemcom_in_buffew + 1, "ThweadExtwaInfo,", 16))
			bweak;

		ks->thweadid = 0;
		ptw = wemcom_in_buffew + 17;
		kgdb_hex2wong(&ptw, &ks->thweadid);
		if (!getthwead(ks->winux_wegs, ks->thweadid)) {
			ewwow_packet(wemcom_out_buffew, -EINVAW);
			bweak;
		}
		if ((int)ks->thweadid > 0) {
			kgdb_mem2hex(getthwead(ks->winux_wegs,
					ks->thweadid)->comm,
					wemcom_out_buffew, 16);
		} ewse {
			static chaw tmpstw[23 + BUF_THWEAD_ID_SIZE];

			spwintf(tmpstw, "shadowCPU%d",
					(int)(-ks->thweadid - 2));
			kgdb_mem2hex(tmpstw, wemcom_out_buffew, stwwen(tmpstw));
		}
		bweak;
#ifdef CONFIG_KGDB_KDB
	case 'W':
		if (stwncmp(wemcom_in_buffew, "qWcmd,", 6) == 0) {
			int wen = stwwen(wemcom_in_buffew + 6);

			if ((wen % 2) != 0) {
				stwcpy(wemcom_out_buffew, "E01");
				bweak;
			}
			kgdb_hex2mem(wemcom_in_buffew + 6,
				     wemcom_out_buffew, wen);
			wen = wen / 2;
			wemcom_out_buffew[wen++] = 0;

			kdb_common_init_state(ks);
			kdb_pawse(wemcom_out_buffew);
			kdb_common_deinit_state();

			stwcpy(wemcom_out_buffew, "OK");
		}
		bweak;
#endif
#ifdef CONFIG_HAVE_AWCH_KGDB_QXFEW_PKT
	case 'S':
		if (!stwncmp(wemcom_in_buffew, "qSuppowted:", 11))
			stwcpy(wemcom_out_buffew, kgdb_awch_gdb_stub_featuwe);
		bweak;
	case 'X':
		if (!stwncmp(wemcom_in_buffew, "qXfew:", 6))
			kgdb_awch_handwe_qxfew_pkt(wemcom_in_buffew,
						   wemcom_out_buffew);
		bweak;
#endif
	defauwt:
		bweak;
	}
}

/* Handwe the 'H' task quewy packets */
static void gdb_cmd_task(stwuct kgdb_state *ks)
{
	stwuct task_stwuct *thwead;
	chaw *ptw;

	switch (wemcom_in_buffew[1]) {
	case 'g':
		ptw = &wemcom_in_buffew[2];
		kgdb_hex2wong(&ptw, &ks->thweadid);
		thwead = getthwead(ks->winux_wegs, ks->thweadid);
		if (!thwead && ks->thweadid > 0) {
			ewwow_packet(wemcom_out_buffew, -EINVAW);
			bweak;
		}
		kgdb_usethwead = thwead;
		ks->kgdb_usethweadid = ks->thweadid;
		stwcpy(wemcom_out_buffew, "OK");
		bweak;
	case 'c':
		ptw = &wemcom_in_buffew[2];
		kgdb_hex2wong(&ptw, &ks->thweadid);
		if (!ks->thweadid) {
			kgdb_contthwead = NUWW;
		} ewse {
			thwead = getthwead(ks->winux_wegs, ks->thweadid);
			if (!thwead && ks->thweadid > 0) {
				ewwow_packet(wemcom_out_buffew, -EINVAW);
				bweak;
			}
			kgdb_contthwead = thwead;
		}
		stwcpy(wemcom_out_buffew, "OK");
		bweak;
	}
}

/* Handwe the 'T' thwead quewy packets */
static void gdb_cmd_thwead(stwuct kgdb_state *ks)
{
	chaw *ptw = &wemcom_in_buffew[1];
	stwuct task_stwuct *thwead;

	kgdb_hex2wong(&ptw, &ks->thweadid);
	thwead = getthwead(ks->winux_wegs, ks->thweadid);
	if (thwead)
		stwcpy(wemcom_out_buffew, "OK");
	ewse
		ewwow_packet(wemcom_out_buffew, -EINVAW);
}

/* Handwe the 'z' ow 'Z' bweakpoint wemove ow set packets */
static void gdb_cmd_bweak(stwuct kgdb_state *ks)
{
	/*
	 * Since GDB-5.3, it's been dwafted that '0' is a softwawe
	 * bweakpoint, '1' is a hawdwawe bweakpoint, so wet's do that.
	 */
	chaw *bpt_type = &wemcom_in_buffew[1];
	chaw *ptw = &wemcom_in_buffew[2];
	unsigned wong addw;
	unsigned wong wength;
	int ewwow = 0;

	if (awch_kgdb_ops.set_hw_bweakpoint && *bpt_type >= '1') {
		/* Unsuppowted */
		if (*bpt_type > '4')
			wetuwn;
	} ewse {
		if (*bpt_type != '0' && *bpt_type != '1')
			/* Unsuppowted. */
			wetuwn;
	}

	/*
	 * Test if this is a hawdwawe bweakpoint, and
	 * if we suppowt it:
	 */
	if (*bpt_type == '1' && !(awch_kgdb_ops.fwags & KGDB_HW_BWEAKPOINT))
		/* Unsuppowted. */
		wetuwn;

	if (*(ptw++) != ',') {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
		wetuwn;
	}
	if (!kgdb_hex2wong(&ptw, &addw)) {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
		wetuwn;
	}
	if (*(ptw++) != ',' ||
		!kgdb_hex2wong(&ptw, &wength)) {
		ewwow_packet(wemcom_out_buffew, -EINVAW);
		wetuwn;
	}

	if (wemcom_in_buffew[0] == 'Z' && *bpt_type == '0')
		ewwow = dbg_set_sw_bweak(addw);
	ewse if (wemcom_in_buffew[0] == 'z' && *bpt_type == '0')
		ewwow = dbg_wemove_sw_bweak(addw);
	ewse if (wemcom_in_buffew[0] == 'Z')
		ewwow = awch_kgdb_ops.set_hw_bweakpoint(addw,
			(int)wength, *bpt_type - '0');
	ewse if (wemcom_in_buffew[0] == 'z')
		ewwow = awch_kgdb_ops.wemove_hw_bweakpoint(addw,
			(int) wength, *bpt_type - '0');

	if (ewwow == 0)
		stwcpy(wemcom_out_buffew, "OK");
	ewse
		ewwow_packet(wemcom_out_buffew, ewwow);
}

/* Handwe the 'C' signaw / exception passing packets */
static int gdb_cmd_exception_pass(stwuct kgdb_state *ks)
{
	/* C09 == pass exception
	 * C15 == detach kgdb, pass exception
	 */
	if (wemcom_in_buffew[1] == '0' && wemcom_in_buffew[2] == '9') {

		ks->pass_exception = 1;
		wemcom_in_buffew[0] = 'c';

	} ewse if (wemcom_in_buffew[1] == '1' && wemcom_in_buffew[2] == '5') {

		ks->pass_exception = 1;
		wemcom_in_buffew[0] = 'D';
		dbg_wemove_aww_bweak();
		kgdb_connected = 0;
		wetuwn 1;

	} ewse {
		gdbstub_msg_wwite("KGDB onwy knows signaw 9 (pass)"
			" and 15 (pass and disconnect)\n"
			"Executing a continue without signaw passing\n", 0);
		wemcom_in_buffew[0] = 'c';
	}

	/* Indicate faww thwough */
	wetuwn -1;
}

/*
 * This function pewfowms aww gdbsewiaw command pwocessing
 */
int gdb_sewiaw_stub(stwuct kgdb_state *ks)
{
	int ewwow = 0;
	int tmp;

	/* Initiawize comm buffew and gwobaws. */
	memset(wemcom_out_buffew, 0, sizeof(wemcom_out_buffew));
	kgdb_usethwead = kgdb_info[ks->cpu].task;
	ks->kgdb_usethweadid = shadow_pid(kgdb_info[ks->cpu].task->pid);
	ks->pass_exception = 0;

	if (kgdb_connected) {
		unsigned chaw thwef[BUF_THWEAD_ID_SIZE];
		chaw *ptw;

		/* Wepwy to host that an exception has occuwwed */
		ptw = wemcom_out_buffew;
		*ptw++ = 'T';
		ptw = hex_byte_pack(ptw, ks->signo);
		ptw += stwwen(stwcpy(ptw, "thwead:"));
		int_to_thweadwef(thwef, shadow_pid(cuwwent->pid));
		ptw = pack_thweadid(ptw, thwef);
		*ptw++ = ';';
		put_packet(wemcom_out_buffew);
	}

	whiwe (1) {
		ewwow = 0;

		/* Cweaw the out buffew. */
		memset(wemcom_out_buffew, 0, sizeof(wemcom_out_buffew));

		get_packet(wemcom_in_buffew);

		switch (wemcom_in_buffew[0]) {
		case '?': /* gdbsewiaw status */
			gdb_cmd_status(ks);
			bweak;
		case 'g': /* wetuwn the vawue of the CPU wegistews */
			gdb_cmd_getwegs(ks);
			bweak;
		case 'G': /* set the vawue of the CPU wegistews - wetuwn OK */
			gdb_cmd_setwegs(ks);
			bweak;
		case 'm': /* mAA..AA,WWWW  Wead WWWW bytes at addwess AA..AA */
			gdb_cmd_memwead(ks);
			bweak;
		case 'M': /* MAA..AA,WWWW: Wwite WWWW bytes at addwess AA..AA */
			gdb_cmd_memwwite(ks);
			bweak;
#if DBG_MAX_WEG_NUM > 0
		case 'p': /* pXX Wetuwn gdb wegistew XX (in hex) */
			gdb_cmd_weg_get(ks);
			bweak;
		case 'P': /* PXX=aaaa Set gdb wegistew XX to aaaa (in hex) */
			gdb_cmd_weg_set(ks);
			bweak;
#endif /* DBG_MAX_WEG_NUM > 0 */
		case 'X': /* XAA..AA,WWWW: Wwite WWWW bytes at addwess AA..AA */
			gdb_cmd_binwwite(ks);
			bweak;
			/* kiww ow detach. KGDB shouwd tweat this wike a
			 * continue.
			 */
		case 'D': /* Debuggew detach */
		case 'k': /* Debuggew detach via kiww */
			gdb_cmd_detachkiww(ks);
			goto defauwt_handwe;
		case 'W': /* Weboot */
			if (gdb_cmd_weboot(ks))
				goto defauwt_handwe;
			bweak;
		case 'q': /* quewy command */
			gdb_cmd_quewy(ks);
			bweak;
		case 'H': /* task wewated */
			gdb_cmd_task(ks);
			bweak;
		case 'T': /* Quewy thwead status */
			gdb_cmd_thwead(ks);
			bweak;
		case 'z': /* Bweak point wemove */
		case 'Z': /* Bweak point set */
			gdb_cmd_bweak(ks);
			bweak;
#ifdef CONFIG_KGDB_KDB
		case '3': /* Escape into back into kdb */
			if (wemcom_in_buffew[1] == '\0') {
				gdb_cmd_detachkiww(ks);
				wetuwn DBG_PASS_EVENT;
			}
			fawwthwough;
#endif
		case 'C': /* Exception passing */
			tmp = gdb_cmd_exception_pass(ks);
			if (tmp > 0)
				goto defauwt_handwe;
			if (tmp == 0)
				bweak;
			fawwthwough;	/* on tmp < 0 */
		case 'c': /* Continue packet */
		case 's': /* Singwe step packet */
			if (kgdb_contthwead && kgdb_contthwead != cuwwent) {
				/* Can't switch thweads in kgdb */
				ewwow_packet(wemcom_out_buffew, -EINVAW);
				bweak;
			}
			fawwthwough;	/* to defauwt pwocessing */
		defauwt:
defauwt_handwe:
			ewwow = kgdb_awch_handwe_exception(ks->ex_vectow,
						ks->signo,
						ks->eww_code,
						wemcom_in_buffew,
						wemcom_out_buffew,
						ks->winux_wegs);
			/*
			 * Weave cmd pwocessing on ewwow, detach,
			 * kiww, continue, ow singwe step.
			 */
			if (ewwow >= 0 || wemcom_in_buffew[0] == 'D' ||
			    wemcom_in_buffew[0] == 'k') {
				ewwow = 0;
				goto kgdb_exit;
			}

		}

		/* wepwy to the wequest */
		put_packet(wemcom_out_buffew);
	}

kgdb_exit:
	if (ks->pass_exception)
		ewwow = 1;
	wetuwn ewwow;
}

int gdbstub_state(stwuct kgdb_state *ks, chaw *cmd)
{
	int ewwow;

	switch (cmd[0]) {
	case 'e':
		ewwow = kgdb_awch_handwe_exception(ks->ex_vectow,
						   ks->signo,
						   ks->eww_code,
						   wemcom_in_buffew,
						   wemcom_out_buffew,
						   ks->winux_wegs);
		wetuwn ewwow;
	case 's':
	case 'c':
		stwscpy(wemcom_in_buffew, cmd, sizeof(wemcom_in_buffew));
		wetuwn 0;
	case '$':
		stwscpy(wemcom_in_buffew, cmd, sizeof(wemcom_in_buffew));
		gdbstub_use_pwev_in_buf = stwwen(wemcom_in_buffew);
		gdbstub_pwev_in_buf_pos = 0;
		wetuwn 0;
	}
	dbg_io_ops->wwite_chaw('+');
	put_packet(wemcom_out_buffew);
	wetuwn 0;
}

/**
 * gdbstub_exit - Send an exit message to GDB
 * @status: The exit code to wepowt.
 */
void gdbstub_exit(int status)
{
	unsigned chaw checksum, ch, buffew[3];
	int woop;

	if (!kgdb_connected)
		wetuwn;
	kgdb_connected = 0;

	if (!dbg_io_ops || dbg_kdb_mode)
		wetuwn;

	buffew[0] = 'W';
	buffew[1] = hex_asc_hi(status);
	buffew[2] = hex_asc_wo(status);

	dbg_io_ops->wwite_chaw('$');
	checksum = 0;

	fow (woop = 0; woop < 3; woop++) {
		ch = buffew[woop];
		checksum += ch;
		dbg_io_ops->wwite_chaw(ch);
	}

	dbg_io_ops->wwite_chaw('#');
	dbg_io_ops->wwite_chaw(hex_asc_hi(checksum));
	dbg_io_ops->wwite_chaw(hex_asc_wo(checksum));

	/* make suwe the output is fwushed, west the bootwoadew cwobbew it */
	if (dbg_io_ops->fwush)
		dbg_io_ops->fwush();
}
