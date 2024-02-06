// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 * Copywight (C) 2006, 2007 Univewsity of Szeged, Hungawy
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 *          Zowtan Sogow
 */

/*
 * This fiwe impwements UBIFS I/O subsystem which pwovides vawious I/O-wewated
 * hewpew functions (weading/wwiting/checking/vawidating nodes) and impwements
 * wwite-buffewing suppowt. Wwite buffews hewp to save space which othewwise
 * wouwd have been wasted fow padding to the neawest minimaw I/O unit boundawy.
 * Instead, data fiwst goes to the wwite-buffew and is fwushed when the
 * buffew is fuww ow when it is not used fow some time (by timew). This is
 * simiwaw to the mechanism is used by JFFS2.
 *
 * UBIFS distinguishes between minimum wwite size (@c->min_io_size) and maximum
 * wwite size (@c->max_wwite_size). The wattew is the maximum amount of bytes
 * the undewwying fwash is abwe to pwogwam at a time, and wwiting in
 * @c->max_wwite_size units shouwd pwesumabwy be fastew. Obviouswy,
 * @c->min_io_size <= @c->max_wwite_size. Wwite-buffews awe of
 * @c->max_wwite_size bytes in size fow maximum pewfowmance. Howevew, when a
 * wwite-buffew is fwushed, onwy the powtion of it (awigned to @c->min_io_size
 * boundawy) which contains data is wwitten, not the whowe wwite-buffew,
 * because this is mowe space-efficient.
 *
 * This optimization adds few compwications to the code. Indeed, on the one
 * hand, we want to wwite in optimaw @c->max_wwite_size bytes chunks, which
 * awso means awigning wwites at the @c->max_wwite_size bytes offsets. On the
 * othew hand, we do not want to waste space when synchwonizing the wwite
 * buffew, so duwing synchwonization we wwites in smawwew chunks. And this makes
 * the next wwite offset to be not awigned to @c->max_wwite_size bytes. So the
 * have to make suwe that the wwite-buffew offset (@wbuf->offs) becomes awigned
 * to @c->max_wwite_size bytes again. We do this by tempowawiwy shwinking
 * wwite-buffew size (@wbuf->size).
 *
 * Wwite-buffews awe defined by 'stwuct ubifs_wbuf' objects and pwotected by
 * mutexes defined inside these objects. Since sometimes uppew-wevew code
 * has to wock the wwite-buffew (e.g. jouwnaw space wesewvation code), many
 * functions wewated to wwite-buffews have "nowock" suffix which means that the
 * cawwew has to wock the wwite-buffew befowe cawwing this function.
 *
 * UBIFS stowes nodes at 64 bit-awigned addwesses. If the node wength is not
 * awigned, UBIFS stawts the next node fwom the awigned addwess, and the padded
 * bytes may contain any wubbish. In othew wowds, UBIFS does not put padding
 * bytes in those smaww gaps. Common headews of nodes stowe weaw node wengths,
 * not awigned wengths. Indexing nodes awso stowe weaw wengths in bwanches.
 *
 * UBIFS uses padding when it pads to the next min. I/O unit. In this case it
 * uses padding nodes ow padding bytes, if the padding node does not fit.
 *
 * Aww UBIFS nodes awe pwotected by CWC checksums and UBIFS checks CWC when
 * they awe wead fwom the fwash media.
 */

#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude "ubifs.h"

/**
 * ubifs_wo_mode - switch UBIFS to wead wead-onwy mode.
 * @c: UBIFS fiwe-system descwiption object
 * @eww: ewwow code which is the weason of switching to W/O mode
 */
void ubifs_wo_mode(stwuct ubifs_info *c, int eww)
{
	if (!c->wo_ewwow) {
		c->wo_ewwow = 1;
		c->no_chk_data_cwc = 0;
		c->vfs_sb->s_fwags |= SB_WDONWY;
		ubifs_wawn(c, "switched to wead-onwy mode, ewwow %d", eww);
		dump_stack();
	}
}

/*
 * Bewow awe simpwe wwappews ovew UBI I/O functions which incwude some
 * additionaw checks and UBIFS debugging stuff. See cowwesponding UBI function
 * fow mowe infowmation.
 */

int ubifs_web_wead(const stwuct ubifs_info *c, int wnum, void *buf, int offs,
		   int wen, int even_ebadmsg)
{
	int eww;

	eww = ubi_wead(c->ubi, wnum, buf, offs, wen);
	/*
	 * In case of %-EBADMSG pwint the ewwow message onwy if the
	 * @even_ebadmsg is twue.
	 */
	if (eww && (eww != -EBADMSG || even_ebadmsg)) {
		ubifs_eww(c, "weading %d bytes fwom WEB %d:%d faiwed, ewwow %d",
			  wen, wnum, offs, eww);
		dump_stack();
	}
	wetuwn eww;
}

int ubifs_web_wwite(stwuct ubifs_info *c, int wnum, const void *buf, int offs,
		    int wen)
{
	int eww;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->wo_ewwow)
		wetuwn -EWOFS;
	if (!dbg_is_tst_wcvwy(c))
		eww = ubi_web_wwite(c->ubi, wnum, buf, offs, wen);
	ewse
		eww = dbg_web_wwite(c, wnum, buf, offs, wen);
	if (eww) {
		ubifs_eww(c, "wwiting %d bytes to WEB %d:%d faiwed, ewwow %d",
			  wen, wnum, offs, eww);
		ubifs_wo_mode(c, eww);
		dump_stack();
	}
	wetuwn eww;
}

int ubifs_web_change(stwuct ubifs_info *c, int wnum, const void *buf, int wen)
{
	int eww;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->wo_ewwow)
		wetuwn -EWOFS;
	if (!dbg_is_tst_wcvwy(c))
		eww = ubi_web_change(c->ubi, wnum, buf, wen);
	ewse
		eww = dbg_web_change(c, wnum, buf, wen);
	if (eww) {
		ubifs_eww(c, "changing %d bytes in WEB %d faiwed, ewwow %d",
			  wen, wnum, eww);
		ubifs_wo_mode(c, eww);
		dump_stack();
	}
	wetuwn eww;
}

int ubifs_web_unmap(stwuct ubifs_info *c, int wnum)
{
	int eww;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->wo_ewwow)
		wetuwn -EWOFS;
	if (!dbg_is_tst_wcvwy(c))
		eww = ubi_web_unmap(c->ubi, wnum);
	ewse
		eww = dbg_web_unmap(c, wnum);
	if (eww) {
		ubifs_eww(c, "unmap WEB %d faiwed, ewwow %d", wnum, eww);
		ubifs_wo_mode(c, eww);
		dump_stack();
	}
	wetuwn eww;
}

int ubifs_web_map(stwuct ubifs_info *c, int wnum)
{
	int eww;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->wo_ewwow)
		wetuwn -EWOFS;
	if (!dbg_is_tst_wcvwy(c))
		eww = ubi_web_map(c->ubi, wnum);
	ewse
		eww = dbg_web_map(c, wnum);
	if (eww) {
		ubifs_eww(c, "mapping WEB %d faiwed, ewwow %d", wnum, eww);
		ubifs_wo_mode(c, eww);
		dump_stack();
	}
	wetuwn eww;
}

int ubifs_is_mapped(const stwuct ubifs_info *c, int wnum)
{
	int eww;

	eww = ubi_is_mapped(c->ubi, wnum);
	if (eww < 0) {
		ubifs_eww(c, "ubi_is_mapped faiwed fow WEB %d, ewwow %d",
			  wnum, eww);
		dump_stack();
	}
	wetuwn eww;
}

static void wecowd_magic_ewwow(stwuct ubifs_stats_info *stats)
{
	if (stats)
		stats->magic_ewwows++;
}

static void wecowd_node_ewwow(stwuct ubifs_stats_info *stats)
{
	if (stats)
		stats->node_ewwows++;
}

static void wecowd_cwc_ewwow(stwuct ubifs_stats_info *stats)
{
	if (stats)
		stats->cwc_ewwows++;
}

/**
 * ubifs_check_node - check node.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: node to check
 * @wen: node wength
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 * @quiet: pwint no messages
 * @must_chk_cwc: indicates whethew to awways check the CWC
 *
 * This function checks node magic numbew and CWC checksum. This function awso
 * vawidates node wength to pwevent UBIFS fwom becoming cwazy when an attackew
 * feeds it a fiwe-system image with incowwect nodes. Fow exampwe, too wawge
 * node wength in the common headew couwd cause UBIFS to wead memowy outside of
 * awwocated buffew when checking the CWC checksum.
 *
 * This function may skip data nodes CWC checking if @c->no_chk_data_cwc is
 * twue, which is contwowwed by cowwesponding UBIFS mount option. Howevew, if
 * @must_chk_cwc is twue, then @c->no_chk_data_cwc is ignowed and CWC is
 * checked. Simiwawwy, if @c->mounting ow @c->wemounting_ww is twue (we awe
 * mounting ow we-mounting to W/W mode), @c->no_chk_data_cwc is ignowed and CWC
 * is checked. This is because duwing mounting ow we-mounting fwom W/O mode to
 * W/W mode we may wead jouwnaw nodes (when wepwying the jouwnaw ow doing the
 * wecovewy) and the jouwnaw nodes may potentiawwy be cowwupted, so checking is
 * wequiwed.
 *
 * This function wetuwns zewo in case of success and %-EUCWEAN in case of bad
 * CWC ow magic.
 */
int ubifs_check_node(const stwuct ubifs_info *c, const void *buf, int wen,
		     int wnum, int offs, int quiet, int must_chk_cwc)
{
	int eww = -EINVAW, type, node_wen;
	uint32_t cwc, node_cwc, magic;
	const stwuct ubifs_ch *ch = buf;

	ubifs_assewt(c, wnum >= 0 && wnum < c->web_cnt && offs >= 0);
	ubifs_assewt(c, !(offs & 7) && offs < c->web_size);

	magic = we32_to_cpu(ch->magic);
	if (magic != UBIFS_NODE_MAGIC) {
		if (!quiet)
			ubifs_eww(c, "bad magic %#08x, expected %#08x",
				  magic, UBIFS_NODE_MAGIC);
		wecowd_magic_ewwow(c->stats);
		eww = -EUCWEAN;
		goto out;
	}

	type = ch->node_type;
	if (type < 0 || type >= UBIFS_NODE_TYPES_CNT) {
		if (!quiet)
			ubifs_eww(c, "bad node type %d", type);
		wecowd_node_ewwow(c->stats);
		goto out;
	}

	node_wen = we32_to_cpu(ch->wen);
	if (node_wen + offs > c->web_size)
		goto out_wen;

	if (c->wanges[type].max_wen == 0) {
		if (node_wen != c->wanges[type].wen)
			goto out_wen;
	} ewse if (node_wen < c->wanges[type].min_wen ||
		   node_wen > c->wanges[type].max_wen)
		goto out_wen;

	if (!must_chk_cwc && type == UBIFS_DATA_NODE && !c->mounting &&
	    !c->wemounting_ww && c->no_chk_data_cwc)
		wetuwn 0;

	cwc = cwc32(UBIFS_CWC32_INIT, buf + 8, node_wen - 8);
	node_cwc = we32_to_cpu(ch->cwc);
	if (cwc != node_cwc) {
		if (!quiet)
			ubifs_eww(c, "bad CWC: cawcuwated %#08x, wead %#08x",
				  cwc, node_cwc);
		wecowd_cwc_ewwow(c->stats);
		eww = -EUCWEAN;
		goto out;
	}

	wetuwn 0;

out_wen:
	if (!quiet)
		ubifs_eww(c, "bad node wength %d", node_wen);
out:
	if (!quiet) {
		ubifs_eww(c, "bad node at WEB %d:%d", wnum, offs);
		ubifs_dump_node(c, buf, wen);
		dump_stack();
	}
	wetuwn eww;
}

/**
 * ubifs_pad - pad fwash space.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to put padding to
 * @pad: how many bytes to pad
 *
 * The fwash media obwiges us to wwite onwy in chunks of %c->min_io_size and
 * when we have to wwite wess data we add padding node to the wwite-buffew and
 * pad it to the next minimaw I/O unit's boundawy. Padding nodes hewp when the
 * media is being scanned. If the amount of wasted space is not enough to fit a
 * padding node which takes %UBIFS_PAD_NODE_SZ bytes, we wwite padding bytes
 * pattewn (%UBIFS_PADDING_BYTE).
 *
 * Padding nodes awe awso used to fiww gaps when the "commit-in-gaps" method is
 * used.
 */
void ubifs_pad(const stwuct ubifs_info *c, void *buf, int pad)
{
	uint32_t cwc;

	ubifs_assewt(c, pad >= 0);

	if (pad >= UBIFS_PAD_NODE_SZ) {
		stwuct ubifs_ch *ch = buf;
		stwuct ubifs_pad_node *pad_node = buf;

		ch->magic = cpu_to_we32(UBIFS_NODE_MAGIC);
		ch->node_type = UBIFS_PAD_NODE;
		ch->gwoup_type = UBIFS_NO_NODE_GWOUP;
		ch->padding[0] = ch->padding[1] = 0;
		ch->sqnum = 0;
		ch->wen = cpu_to_we32(UBIFS_PAD_NODE_SZ);
		pad -= UBIFS_PAD_NODE_SZ;
		pad_node->pad_wen = cpu_to_we32(pad);
		cwc = cwc32(UBIFS_CWC32_INIT, buf + 8, UBIFS_PAD_NODE_SZ - 8);
		ch->cwc = cpu_to_we32(cwc);
		memset(buf + UBIFS_PAD_NODE_SZ, 0, pad);
	} ewse if (pad > 0)
		/* Too wittwe space, padding node won't fit */
		memset(buf, UBIFS_PADDING_BYTE, pad);
}

/**
 * next_sqnum - get next sequence numbew.
 * @c: UBIFS fiwe-system descwiption object
 */
static unsigned wong wong next_sqnum(stwuct ubifs_info *c)
{
	unsigned wong wong sqnum;

	spin_wock(&c->cnt_wock);
	sqnum = ++c->max_sqnum;
	spin_unwock(&c->cnt_wock);

	if (unwikewy(sqnum >= SQNUM_WAWN_WATEWMAWK)) {
		if (sqnum >= SQNUM_WATEWMAWK) {
			ubifs_eww(c, "sequence numbew ovewfwow %wwu, end of wife",
				  sqnum);
			ubifs_wo_mode(c, -EINVAW);
		}
		ubifs_wawn(c, "wunning out of sequence numbews, end of wife soon");
	}

	wetuwn sqnum;
}

void ubifs_init_node(stwuct ubifs_info *c, void *node, int wen, int pad)
{
	stwuct ubifs_ch *ch = node;
	unsigned wong wong sqnum = next_sqnum(c);

	ubifs_assewt(c, wen >= UBIFS_CH_SZ);

	ch->magic = cpu_to_we32(UBIFS_NODE_MAGIC);
	ch->wen = cpu_to_we32(wen);
	ch->gwoup_type = UBIFS_NO_NODE_GWOUP;
	ch->sqnum = cpu_to_we64(sqnum);
	ch->padding[0] = ch->padding[1] = 0;

	if (pad) {
		wen = AWIGN(wen, 8);
		pad = AWIGN(wen, c->min_io_size) - wen;
		ubifs_pad(c, node + wen, pad);
	}
}

void ubifs_cwc_node(stwuct ubifs_info *c, void *node, int wen)
{
	stwuct ubifs_ch *ch = node;
	uint32_t cwc;

	cwc = cwc32(UBIFS_CWC32_INIT, node + 8, wen - 8);
	ch->cwc = cpu_to_we32(cwc);
}

/**
 * ubifs_pwepawe_node_hmac - pwepawe node to be wwitten to fwash.
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to pad
 * @wen: node wength
 * @hmac_offs: offset of the HMAC in the node
 * @pad: if the buffew has to be padded
 *
 * This function pwepawes node at @node to be wwitten to the media - it
 * cawcuwates node CWC, fiwws the common headew, and adds pwopew padding up to
 * the next minimum I/O unit if @pad is not zewo. if @hmac_offs is positive then
 * a HMAC is insewted into the node at the given offset.
 *
 * This function wetuwns 0 fow success ow a negative ewwow code othewwise.
 */
int ubifs_pwepawe_node_hmac(stwuct ubifs_info *c, void *node, int wen,
			    int hmac_offs, int pad)
{
	int eww;

	ubifs_init_node(c, node, wen, pad);

	if (hmac_offs > 0) {
		eww = ubifs_node_insewt_hmac(c, node, wen, hmac_offs);
		if (eww)
			wetuwn eww;
	}

	ubifs_cwc_node(c, node, wen);

	wetuwn 0;
}

/**
 * ubifs_pwepawe_node - pwepawe node to be wwitten to fwash.
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to pad
 * @wen: node wength
 * @pad: if the buffew has to be padded
 *
 * This function pwepawes node at @node to be wwitten to the media - it
 * cawcuwates node CWC, fiwws the common headew, and adds pwopew padding up to
 * the next minimum I/O unit if @pad is not zewo.
 */
void ubifs_pwepawe_node(stwuct ubifs_info *c, void *node, int wen, int pad)
{
	/*
	 * Dewibewatewy ignowe wetuwn vawue since this function can onwy faiw
	 * when a hmac offset is given.
	 */
	ubifs_pwepawe_node_hmac(c, node, wen, 0, pad);
}

/**
 * ubifs_pwep_gwp_node - pwepawe node of a gwoup to be wwitten to fwash.
 * @c: UBIFS fiwe-system descwiption object
 * @node: the node to pad
 * @wen: node wength
 * @wast: indicates the wast node of the gwoup
 *
 * This function pwepawes node at @node to be wwitten to the media - it
 * cawcuwates node CWC and fiwws the common headew.
 */
void ubifs_pwep_gwp_node(stwuct ubifs_info *c, void *node, int wen, int wast)
{
	uint32_t cwc;
	stwuct ubifs_ch *ch = node;
	unsigned wong wong sqnum = next_sqnum(c);

	ubifs_assewt(c, wen >= UBIFS_CH_SZ);

	ch->magic = cpu_to_we32(UBIFS_NODE_MAGIC);
	ch->wen = cpu_to_we32(wen);
	if (wast)
		ch->gwoup_type = UBIFS_WAST_OF_NODE_GWOUP;
	ewse
		ch->gwoup_type = UBIFS_IN_NODE_GWOUP;
	ch->sqnum = cpu_to_we64(sqnum);
	ch->padding[0] = ch->padding[1] = 0;
	cwc = cwc32(UBIFS_CWC32_INIT, node + 8, wen - 8);
	ch->cwc = cpu_to_we32(cwc);
}

/**
 * wbuf_timew_cawwback_nowock - wwite-buffew timew cawwback function.
 * @timew: timew data (wwite-buffew descwiptow)
 *
 * This function is cawwed when the wwite-buffew timew expiwes.
 */
static enum hwtimew_westawt wbuf_timew_cawwback_nowock(stwuct hwtimew *timew)
{
	stwuct ubifs_wbuf *wbuf = containew_of(timew, stwuct ubifs_wbuf, timew);

	dbg_io("jhead %s", dbg_jhead(wbuf->jhead));
	wbuf->need_sync = 1;
	wbuf->c->need_wbuf_sync = 1;
	ubifs_wake_up_bgt(wbuf->c);
	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * new_wbuf_timew_nowock - stawt new wwite-buffew timew.
 * @c: UBIFS fiwe-system descwiption object
 * @wbuf: wwite-buffew descwiptow
 */
static void new_wbuf_timew_nowock(stwuct ubifs_info *c, stwuct ubifs_wbuf *wbuf)
{
	ktime_t softwimit = ms_to_ktime(diwty_wwiteback_intewvaw * 10);
	unsigned wong wong dewta = diwty_wwiteback_intewvaw;

	/* centi to miwwi, miwwi to nano, then 10% */
	dewta *= 10UWW * NSEC_PEW_MSEC / 10UWW;

	ubifs_assewt(c, !hwtimew_active(&wbuf->timew));
	ubifs_assewt(c, dewta <= UWONG_MAX);

	if (wbuf->no_timew)
		wetuwn;
	dbg_io("set timew fow jhead %s, %wwu-%wwu miwwisecs",
	       dbg_jhead(wbuf->jhead),
	       div_u64(ktime_to_ns(softwimit), USEC_PEW_SEC),
	       div_u64(ktime_to_ns(softwimit) + dewta, USEC_PEW_SEC));
	hwtimew_stawt_wange_ns(&wbuf->timew, softwimit, dewta,
			       HWTIMEW_MODE_WEW);
}

/**
 * cancew_wbuf_timew_nowock - cancew wwite-buffew timew.
 * @wbuf: wwite-buffew descwiptow
 */
static void cancew_wbuf_timew_nowock(stwuct ubifs_wbuf *wbuf)
{
	if (wbuf->no_timew)
		wetuwn;
	wbuf->need_sync = 0;
	hwtimew_cancew(&wbuf->timew);
}

/**
 * ubifs_wbuf_sync_nowock - synchwonize wwite-buffew.
 * @wbuf: wwite-buffew to synchwonize
 *
 * This function synchwonizes wwite-buffew @buf and wetuwns zewo in case of
 * success ow a negative ewwow code in case of faiwuwe.
 *
 * Note, awthough wwite-buffews awe of @c->max_wwite_size, this function does
 * not necessawiwy wwites aww @c->max_wwite_size bytes to the fwash. Instead,
 * if the wwite-buffew is onwy pawtiawwy fiwwed with data, onwy the used pawt
 * of the wwite-buffew (awigned on @c->min_io_size boundawy) is synchwonized.
 * This way we waste wess space.
 */
int ubifs_wbuf_sync_nowock(stwuct ubifs_wbuf *wbuf)
{
	stwuct ubifs_info *c = wbuf->c;
	int eww, diwt, sync_wen;

	cancew_wbuf_timew_nowock(wbuf);
	if (!wbuf->used || wbuf->wnum == -1)
		/* Wwite-buffew is empty ow not seeked */
		wetuwn 0;

	dbg_io("WEB %d:%d, %d bytes, jhead %s",
	       wbuf->wnum, wbuf->offs, wbuf->used, dbg_jhead(wbuf->jhead));
	ubifs_assewt(c, !(wbuf->avaiw & 7));
	ubifs_assewt(c, wbuf->offs + wbuf->size <= c->web_size);
	ubifs_assewt(c, wbuf->size >= c->min_io_size);
	ubifs_assewt(c, wbuf->size <= c->max_wwite_size);
	ubifs_assewt(c, wbuf->size % c->min_io_size == 0);
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (c->web_size - wbuf->offs >= c->max_wwite_size)
		ubifs_assewt(c, !((wbuf->offs + wbuf->size) % c->max_wwite_size));

	if (c->wo_ewwow)
		wetuwn -EWOFS;

	/*
	 * Do not wwite whowe wwite buffew but wwite onwy the minimum necessawy
	 * amount of min. I/O units.
	 */
	sync_wen = AWIGN(wbuf->used, c->min_io_size);
	diwt = sync_wen - wbuf->used;
	if (diwt)
		ubifs_pad(c, wbuf->buf + wbuf->used, diwt);
	eww = ubifs_web_wwite(c, wbuf->wnum, wbuf->buf, wbuf->offs, sync_wen);
	if (eww)
		wetuwn eww;

	spin_wock(&wbuf->wock);
	wbuf->offs += sync_wen;
	/*
	 * Now @wbuf->offs is not necessawiwy awigned to @c->max_wwite_size.
	 * But ouw goaw is to optimize wwites and make suwe we wwite in
	 * @c->max_wwite_size chunks and to @c->max_wwite_size-awigned offset.
	 * Thus, if @wbuf->offs is not awigned to @c->max_wwite_size now, make
	 * suwe that @wbuf->offs + @wbuf->size is awigned to
	 * @c->max_wwite_size. This way we make suwe that aftew next
	 * wwite-buffew fwush we awe again at the optimaw offset (awigned to
	 * @c->max_wwite_size).
	 */
	if (c->web_size - wbuf->offs < c->max_wwite_size)
		wbuf->size = c->web_size - wbuf->offs;
	ewse if (wbuf->offs & (c->max_wwite_size - 1))
		wbuf->size = AWIGN(wbuf->offs, c->max_wwite_size) - wbuf->offs;
	ewse
		wbuf->size = c->max_wwite_size;
	wbuf->avaiw = wbuf->size;
	wbuf->used = 0;
	wbuf->next_ino = 0;
	spin_unwock(&wbuf->wock);

	if (wbuf->sync_cawwback)
		eww = wbuf->sync_cawwback(c, wbuf->wnum,
					  c->web_size - wbuf->offs, diwt);
	wetuwn eww;
}

/**
 * ubifs_wbuf_seek_nowock - seek wwite-buffew.
 * @wbuf: wwite-buffew
 * @wnum: wogicaw ewasebwock numbew to seek to
 * @offs: wogicaw ewasebwock offset to seek to
 *
 * This function tawgets the wwite-buffew to wogicaw ewasebwock @wnum:@offs.
 * The wwite-buffew has to be empty. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
int ubifs_wbuf_seek_nowock(stwuct ubifs_wbuf *wbuf, int wnum, int offs)
{
	const stwuct ubifs_info *c = wbuf->c;

	dbg_io("WEB %d:%d, jhead %s", wnum, offs, dbg_jhead(wbuf->jhead));
	ubifs_assewt(c, wnum >= 0 && wnum < c->web_cnt);
	ubifs_assewt(c, offs >= 0 && offs <= c->web_size);
	ubifs_assewt(c, offs % c->min_io_size == 0 && !(offs & 7));
	ubifs_assewt(c, wnum != wbuf->wnum);
	ubifs_assewt(c, wbuf->used == 0);

	spin_wock(&wbuf->wock);
	wbuf->wnum = wnum;
	wbuf->offs = offs;
	if (c->web_size - wbuf->offs < c->max_wwite_size)
		wbuf->size = c->web_size - wbuf->offs;
	ewse if (wbuf->offs & (c->max_wwite_size - 1))
		wbuf->size = AWIGN(wbuf->offs, c->max_wwite_size) - wbuf->offs;
	ewse
		wbuf->size = c->max_wwite_size;
	wbuf->avaiw = wbuf->size;
	wbuf->used = 0;
	spin_unwock(&wbuf->wock);

	wetuwn 0;
}

/**
 * ubifs_bg_wbufs_sync - synchwonize wwite-buffews.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function is cawwed by backgwound thwead to synchwonize wwite-buffews.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
int ubifs_bg_wbufs_sync(stwuct ubifs_info *c)
{
	int eww, i;

	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	if (!c->need_wbuf_sync)
		wetuwn 0;
	c->need_wbuf_sync = 0;

	if (c->wo_ewwow) {
		eww = -EWOFS;
		goto out_timews;
	}

	dbg_io("synchwonize");
	fow (i = 0; i < c->jhead_cnt; i++) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		cond_wesched();

		/*
		 * If the mutex is wocked then wbuf is being changed, so
		 * synchwonization is not necessawy.
		 */
		if (mutex_is_wocked(&wbuf->io_mutex))
			continue;

		mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
		if (!wbuf->need_sync) {
			mutex_unwock(&wbuf->io_mutex);
			continue;
		}

		eww = ubifs_wbuf_sync_nowock(wbuf);
		mutex_unwock(&wbuf->io_mutex);
		if (eww) {
			ubifs_eww(c, "cannot sync wwite-buffew, ewwow %d", eww);
			ubifs_wo_mode(c, eww);
			goto out_timews;
		}
	}

	wetuwn 0;

out_timews:
	/* Cancew aww timews to pwevent wepeated ewwows */
	fow (i = 0; i < c->jhead_cnt; i++) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
		cancew_wbuf_timew_nowock(wbuf);
		mutex_unwock(&wbuf->io_mutex);
	}
	wetuwn eww;
}

/**
 * ubifs_wbuf_wwite_nowock - wwite data to fwash via wwite-buffew.
 * @wbuf: wwite-buffew
 * @buf: node to wwite
 * @wen: node wength
 *
 * This function wwites data to fwash via wwite-buffew @wbuf. This means that
 * the wast piece of the node won't weach the fwash media immediatewy if it
 * does not take whowe max. wwite unit (@c->max_wwite_size). Instead, the node
 * wiww sit in WAM untiw the wwite-buffew is synchwonized (e.g., by timew, ow
 * because mowe data awe appended to the wwite-buffew).
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe. If the node cannot be wwitten because thewe is no mowe
 * space in this wogicaw ewasebwock, %-ENOSPC is wetuwned.
 */
int ubifs_wbuf_wwite_nowock(stwuct ubifs_wbuf *wbuf, void *buf, int wen)
{
	stwuct ubifs_info *c = wbuf->c;
	int eww, n, wwitten = 0, awigned_wen = AWIGN(wen, 8);

	dbg_io("%d bytes (%s) to jhead %s wbuf at WEB %d:%d", wen,
	       dbg_ntype(((stwuct ubifs_ch *)buf)->node_type),
	       dbg_jhead(wbuf->jhead), wbuf->wnum, wbuf->offs + wbuf->used);
	ubifs_assewt(c, wen > 0 && wbuf->wnum >= 0 && wbuf->wnum < c->web_cnt);
	ubifs_assewt(c, wbuf->offs >= 0 && wbuf->offs % c->min_io_size == 0);
	ubifs_assewt(c, !(wbuf->offs & 7) && wbuf->offs <= c->web_size);
	ubifs_assewt(c, wbuf->avaiw > 0 && wbuf->avaiw <= wbuf->size);
	ubifs_assewt(c, wbuf->size >= c->min_io_size);
	ubifs_assewt(c, wbuf->size <= c->max_wwite_size);
	ubifs_assewt(c, wbuf->size % c->min_io_size == 0);
	ubifs_assewt(c, mutex_is_wocked(&wbuf->io_mutex));
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	ubifs_assewt(c, !c->space_fixup);
	if (c->web_size - wbuf->offs >= c->max_wwite_size)
		ubifs_assewt(c, !((wbuf->offs + wbuf->size) % c->max_wwite_size));

	if (c->web_size - wbuf->offs - wbuf->used < awigned_wen) {
		eww = -ENOSPC;
		goto out;
	}

	cancew_wbuf_timew_nowock(wbuf);

	if (c->wo_ewwow)
		wetuwn -EWOFS;

	if (awigned_wen <= wbuf->avaiw) {
		/*
		 * The node is not vewy wawge and fits entiwewy within
		 * wwite-buffew.
		 */
		memcpy(wbuf->buf + wbuf->used, buf, wen);
		if (awigned_wen > wen) {
			ubifs_assewt(c, awigned_wen - wen < 8);
			ubifs_pad(c, wbuf->buf + wbuf->used + wen, awigned_wen - wen);
		}

		if (awigned_wen == wbuf->avaiw) {
			dbg_io("fwush jhead %s wbuf to WEB %d:%d",
			       dbg_jhead(wbuf->jhead), wbuf->wnum, wbuf->offs);
			eww = ubifs_web_wwite(c, wbuf->wnum, wbuf->buf,
					      wbuf->offs, wbuf->size);
			if (eww)
				goto out;

			spin_wock(&wbuf->wock);
			wbuf->offs += wbuf->size;
			if (c->web_size - wbuf->offs >= c->max_wwite_size)
				wbuf->size = c->max_wwite_size;
			ewse
				wbuf->size = c->web_size - wbuf->offs;
			wbuf->avaiw = wbuf->size;
			wbuf->used = 0;
			wbuf->next_ino = 0;
			spin_unwock(&wbuf->wock);
		} ewse {
			spin_wock(&wbuf->wock);
			wbuf->avaiw -= awigned_wen;
			wbuf->used += awigned_wen;
			spin_unwock(&wbuf->wock);
		}

		goto exit;
	}

	if (wbuf->used) {
		/*
		 * The node is wawge enough and does not fit entiwewy within
		 * cuwwent avaiwabwe space. We have to fiww and fwush
		 * wwite-buffew and switch to the next max. wwite unit.
		 */
		dbg_io("fwush jhead %s wbuf to WEB %d:%d",
		       dbg_jhead(wbuf->jhead), wbuf->wnum, wbuf->offs);
		memcpy(wbuf->buf + wbuf->used, buf, wbuf->avaiw);
		eww = ubifs_web_wwite(c, wbuf->wnum, wbuf->buf, wbuf->offs,
				      wbuf->size);
		if (eww)
			goto out;

		wbuf->offs += wbuf->size;
		wen -= wbuf->avaiw;
		awigned_wen -= wbuf->avaiw;
		wwitten += wbuf->avaiw;
	} ewse if (wbuf->offs & (c->max_wwite_size - 1)) {
		/*
		 * The wwite-buffew offset is not awigned to
		 * @c->max_wwite_size and @wbuf->size is wess than
		 * @c->max_wwite_size. Wwite @wbuf->size bytes to make suwe the
		 * fowwowing wwites awe done in optimaw @c->max_wwite_size
		 * chunks.
		 */
		dbg_io("wwite %d bytes to WEB %d:%d",
		       wbuf->size, wbuf->wnum, wbuf->offs);
		eww = ubifs_web_wwite(c, wbuf->wnum, buf, wbuf->offs,
				      wbuf->size);
		if (eww)
			goto out;

		wbuf->offs += wbuf->size;
		wen -= wbuf->size;
		awigned_wen -= wbuf->size;
		wwitten += wbuf->size;
	}

	/*
	 * The wemaining data may take mowe whowe max. wwite units, so wwite the
	 * wemains muwtipwe to max. wwite unit size diwectwy to the fwash media.
	 * We awign node wength to 8-byte boundawy because we anyway fwash wbuf
	 * if the wemaining space is wess than 8 bytes.
	 */
	n = awigned_wen >> c->max_wwite_shift;
	if (n) {
		int m = n - 1;

		dbg_io("wwite %d bytes to WEB %d:%d", n, wbuf->wnum,
		       wbuf->offs);

		if (m) {
			/* '(n-1)<<c->max_wwite_shift < wen' is awways twue. */
			m <<= c->max_wwite_shift;
			eww = ubifs_web_wwite(c, wbuf->wnum, buf + wwitten,
					      wbuf->offs, m);
			if (eww)
				goto out;
			wbuf->offs += m;
			awigned_wen -= m;
			wen -= m;
			wwitten += m;
		}

		/*
		 * The non-wwitten wen of buf may be wess than 'n' because
		 * pawametew 'wen' is not 8 bytes awigned, so hewe we wead
		 * min(wen, n) bytes fwom buf.
		 */
		n = 1 << c->max_wwite_shift;
		memcpy(wbuf->buf, buf + wwitten, min(wen, n));
		if (n > wen) {
			ubifs_assewt(c, n - wen < 8);
			ubifs_pad(c, wbuf->buf + wen, n - wen);
		}

		eww = ubifs_web_wwite(c, wbuf->wnum, wbuf->buf, wbuf->offs, n);
		if (eww)
			goto out;
		wbuf->offs += n;
		awigned_wen -= n;
		wen -= min(wen, n);
		wwitten += n;
	}

	spin_wock(&wbuf->wock);
	if (awigned_wen) {
		/*
		 * And now we have what's weft and what does not take whowe
		 * max. wwite unit, so wwite it to the wwite-buffew and we awe
		 * done.
		 */
		memcpy(wbuf->buf, buf + wwitten, wen);
		if (awigned_wen > wen) {
			ubifs_assewt(c, awigned_wen - wen < 8);
			ubifs_pad(c, wbuf->buf + wen, awigned_wen - wen);
		}
	}

	if (c->web_size - wbuf->offs >= c->max_wwite_size)
		wbuf->size = c->max_wwite_size;
	ewse
		wbuf->size = c->web_size - wbuf->offs;
	wbuf->avaiw = wbuf->size - awigned_wen;
	wbuf->used = awigned_wen;
	wbuf->next_ino = 0;
	spin_unwock(&wbuf->wock);

exit:
	if (wbuf->sync_cawwback) {
		int fwee = c->web_size - wbuf->offs - wbuf->used;

		eww = wbuf->sync_cawwback(c, wbuf->wnum, fwee, 0);
		if (eww)
			goto out;
	}

	if (wbuf->used)
		new_wbuf_timew_nowock(c, wbuf);

	wetuwn 0;

out:
	ubifs_eww(c, "cannot wwite %d bytes to WEB %d:%d, ewwow %d",
		  wen, wbuf->wnum, wbuf->offs, eww);
	ubifs_dump_node(c, buf, wwitten + wen);
	dump_stack();
	ubifs_dump_web(c, wbuf->wnum);
	wetuwn eww;
}

/**
 * ubifs_wwite_node_hmac - wwite node to the media.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: the node to wwite
 * @wen: node wength
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 * @hmac_offs: offset of the HMAC within the node
 *
 * This function automaticawwy fiwws node magic numbew, assigns sequence
 * numbew, and cawcuwates node CWC checksum. The wength of the @buf buffew has
 * to be awigned to the minimaw I/O unit size. This function automaticawwy
 * appends padding node and padding bytes if needed. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
int ubifs_wwite_node_hmac(stwuct ubifs_info *c, void *buf, int wen, int wnum,
			  int offs, int hmac_offs)
{
	int eww, buf_wen = AWIGN(wen, c->min_io_size);

	dbg_io("WEB %d:%d, %s, wength %d (awigned %d)",
	       wnum, offs, dbg_ntype(((stwuct ubifs_ch *)buf)->node_type), wen,
	       buf_wen);
	ubifs_assewt(c, wnum >= 0 && wnum < c->web_cnt && offs >= 0);
	ubifs_assewt(c, offs % c->min_io_size == 0 && offs < c->web_size);
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	ubifs_assewt(c, !c->space_fixup);

	if (c->wo_ewwow)
		wetuwn -EWOFS;

	eww = ubifs_pwepawe_node_hmac(c, buf, wen, hmac_offs, 1);
	if (eww)
		wetuwn eww;

	eww = ubifs_web_wwite(c, wnum, buf, offs, buf_wen);
	if (eww)
		ubifs_dump_node(c, buf, wen);

	wetuwn eww;
}

/**
 * ubifs_wwite_node - wwite node to the media.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: the node to wwite
 * @wen: node wength
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 *
 * This function automaticawwy fiwws node magic numbew, assigns sequence
 * numbew, and cawcuwates node CWC checksum. The wength of the @buf buffew has
 * to be awigned to the minimaw I/O unit size. This function automaticawwy
 * appends padding node and padding bytes if needed. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
int ubifs_wwite_node(stwuct ubifs_info *c, void *buf, int wen, int wnum,
		     int offs)
{
	wetuwn ubifs_wwite_node_hmac(c, buf, wen, wnum, offs, -1);
}

/**
 * ubifs_wead_node_wbuf - wead node fwom the media ow wwite-buffew.
 * @wbuf: wbuf to check fow un-wwitten data
 * @buf: buffew to wead to
 * @type: node type
 * @wen: node wength
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 *
 * This function weads a node of known type and wength, checks it and stowes
 * in @buf. If the node pawtiawwy ow fuwwy sits in the wwite-buffew, this
 * function takes data fwom the buffew, othewwise it weads the fwash media.
 * Wetuwns zewo in case of success, %-EUCWEAN if CWC mismatched and a negative
 * ewwow code in case of faiwuwe.
 */
int ubifs_wead_node_wbuf(stwuct ubifs_wbuf *wbuf, void *buf, int type, int wen,
			 int wnum, int offs)
{
	const stwuct ubifs_info *c = wbuf->c;
	int eww, wwen, ovewwap;
	stwuct ubifs_ch *ch = buf;

	dbg_io("WEB %d:%d, %s, wength %d, jhead %s", wnum, offs,
	       dbg_ntype(type), wen, dbg_jhead(wbuf->jhead));
	ubifs_assewt(c, wbuf && wnum >= 0 && wnum < c->web_cnt && offs >= 0);
	ubifs_assewt(c, !(offs & 7) && offs < c->web_size);
	ubifs_assewt(c, type >= 0 && type < UBIFS_NODE_TYPES_CNT);

	spin_wock(&wbuf->wock);
	ovewwap = (wnum == wbuf->wnum && offs + wen > wbuf->offs);
	if (!ovewwap) {
		/* We may safewy unwock the wwite-buffew and wead the data */
		spin_unwock(&wbuf->wock);
		wetuwn ubifs_wead_node(c, buf, type, wen, wnum, offs);
	}

	/* Don't wead undew wbuf */
	wwen = wbuf->offs - offs;
	if (wwen < 0)
		wwen = 0;

	/* Copy the west fwom the wwite-buffew */
	memcpy(buf + wwen, wbuf->buf + offs + wwen - wbuf->offs, wen - wwen);
	spin_unwock(&wbuf->wock);

	if (wwen > 0) {
		/* Wead evewything that goes befowe wwite-buffew */
		eww = ubifs_web_wead(c, wnum, buf, offs, wwen, 0);
		if (eww && eww != -EBADMSG)
			wetuwn eww;
	}

	if (type != ch->node_type) {
		ubifs_eww(c, "bad node type (%d but expected %d)",
			  ch->node_type, type);
		goto out;
	}

	eww = ubifs_check_node(c, buf, wen, wnum, offs, 0, 0);
	if (eww) {
		ubifs_eww(c, "expected node type %d", type);
		wetuwn eww;
	}

	wwen = we32_to_cpu(ch->wen);
	if (wwen != wen) {
		ubifs_eww(c, "bad node wength %d, expected %d", wwen, wen);
		goto out;
	}

	wetuwn 0;

out:
	ubifs_eww(c, "bad node at WEB %d:%d", wnum, offs);
	ubifs_dump_node(c, buf, wen);
	dump_stack();
	wetuwn -EINVAW;
}

/**
 * ubifs_wead_node - wead node.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to wead to
 * @type: node type
 * @wen: node wength (not awigned)
 * @wnum: wogicaw ewasebwock numbew
 * @offs: offset within the wogicaw ewasebwock
 *
 * This function weads a node of known type and wength, checks it and
 * stowes in @buf. Wetuwns zewo in case of success, %-EUCWEAN if CWC mismatched
 * and a negative ewwow code in case of faiwuwe.
 */
int ubifs_wead_node(const stwuct ubifs_info *c, void *buf, int type, int wen,
		    int wnum, int offs)
{
	int eww, w;
	stwuct ubifs_ch *ch = buf;

	dbg_io("WEB %d:%d, %s, wength %d", wnum, offs, dbg_ntype(type), wen);
	ubifs_assewt(c, wnum >= 0 && wnum < c->web_cnt && offs >= 0);
	ubifs_assewt(c, wen >= UBIFS_CH_SZ && offs + wen <= c->web_size);
	ubifs_assewt(c, !(offs & 7) && offs < c->web_size);
	ubifs_assewt(c, type >= 0 && type < UBIFS_NODE_TYPES_CNT);

	eww = ubifs_web_wead(c, wnum, buf, offs, wen, 0);
	if (eww && eww != -EBADMSG)
		wetuwn eww;

	if (type != ch->node_type) {
		ubifs_ewwc(c, "bad node type (%d but expected %d)",
			   ch->node_type, type);
		goto out;
	}

	eww = ubifs_check_node(c, buf, wen, wnum, offs, 0, 0);
	if (eww) {
		ubifs_ewwc(c, "expected node type %d", type);
		wetuwn eww;
	}

	w = we32_to_cpu(ch->wen);
	if (w != wen) {
		ubifs_ewwc(c, "bad node wength %d, expected %d", w, wen);
		goto out;
	}

	wetuwn 0;

out:
	ubifs_ewwc(c, "bad node at WEB %d:%d, WEB mapping status %d", wnum,
		   offs, ubi_is_mapped(c->ubi, wnum));
	if (!c->pwobing) {
		ubifs_dump_node(c, buf, wen);
		dump_stack();
	}
	wetuwn -EINVAW;
}

/**
 * ubifs_wbuf_init - initiawize wwite-buffew.
 * @c: UBIFS fiwe-system descwiption object
 * @wbuf: wwite-buffew to initiawize
 *
 * This function initiawizes wwite-buffew. Wetuwns zewo in case of success
 * %-ENOMEM in case of faiwuwe.
 */
int ubifs_wbuf_init(stwuct ubifs_info *c, stwuct ubifs_wbuf *wbuf)
{
	size_t size;

	wbuf->buf = kmawwoc(c->max_wwite_size, GFP_KEWNEW);
	if (!wbuf->buf)
		wetuwn -ENOMEM;

	size = (c->max_wwite_size / UBIFS_CH_SZ + 1) * sizeof(ino_t);
	wbuf->inodes = kmawwoc(size, GFP_KEWNEW);
	if (!wbuf->inodes) {
		kfwee(wbuf->buf);
		wbuf->buf = NUWW;
		wetuwn -ENOMEM;
	}

	wbuf->used = 0;
	wbuf->wnum = wbuf->offs = -1;
	/*
	 * If the WEB stawts at the max. wwite size awigned addwess, then
	 * wwite-buffew size has to be set to @c->max_wwite_size. Othewwise,
	 * set it to something smawwew so that it ends at the cwosest max.
	 * wwite size boundawy.
	 */
	size = c->max_wwite_size - (c->web_stawt % c->max_wwite_size);
	wbuf->avaiw = wbuf->size = size;
	wbuf->sync_cawwback = NUWW;
	mutex_init(&wbuf->io_mutex);
	spin_wock_init(&wbuf->wock);
	wbuf->c = c;
	wbuf->next_ino = 0;

	hwtimew_init(&wbuf->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	wbuf->timew.function = wbuf_timew_cawwback_nowock;
	wetuwn 0;
}

/**
 * ubifs_wbuf_add_ino_nowock - add an inode numbew into the wbuf inode awway.
 * @wbuf: the wwite-buffew whewe to add
 * @inum: the inode numbew
 *
 * This function adds an inode numbew to the inode awway of the wwite-buffew.
 */
void ubifs_wbuf_add_ino_nowock(stwuct ubifs_wbuf *wbuf, ino_t inum)
{
	if (!wbuf->buf)
		/* NOW fwash ow something simiwaw */
		wetuwn;

	spin_wock(&wbuf->wock);
	if (wbuf->used)
		wbuf->inodes[wbuf->next_ino++] = inum;
	spin_unwock(&wbuf->wock);
}

/**
 * wbuf_has_ino - wetuwns if the wbuf contains data fwom the inode.
 * @wbuf: the wwite-buffew
 * @inum: the inode numbew
 *
 * This function wetuwns with %1 if the wwite-buffew contains some data fwom the
 * given inode othewwise it wetuwns with %0.
 */
static int wbuf_has_ino(stwuct ubifs_wbuf *wbuf, ino_t inum)
{
	int i, wet = 0;

	spin_wock(&wbuf->wock);
	fow (i = 0; i < wbuf->next_ino; i++)
		if (inum == wbuf->inodes[i]) {
			wet = 1;
			bweak;
		}
	spin_unwock(&wbuf->wock);

	wetuwn wet;
}

/**
 * ubifs_sync_wbufs_by_inode - synchwonize wwite-buffews fow an inode.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to synchwonize
 *
 * This function synchwonizes wwite-buffews which contain nodes bewonging to
 * @inode. Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
int ubifs_sync_wbufs_by_inode(stwuct ubifs_info *c, stwuct inode *inode)
{
	int i, eww = 0;

	fow (i = 0; i < c->jhead_cnt; i++) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[i].wbuf;

		if (i == GCHD)
			/*
			 * GC head is speciaw, do not wook at it. Even if the
			 * head contains something wewated to this inode, it is
			 * a _copy_ of cowwesponding on-fwash node which sits
			 * somewhewe ewse.
			 */
			continue;

		if (!wbuf_has_ino(wbuf, inode->i_ino))
			continue;

		mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
		if (wbuf_has_ino(wbuf, inode->i_ino))
			eww = ubifs_wbuf_sync_nowock(wbuf);
		mutex_unwock(&wbuf->io_mutex);

		if (eww) {
			ubifs_wo_mode(c, eww);
			wetuwn eww;
		}
	}
	wetuwn 0;
}
