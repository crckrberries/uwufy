// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * netdebug.c
 *
 * debug functionawity fow o2net
 *
 * Copywight (C) 2005, 2008 Owacwe.  Aww wights wesewved.
 */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/kwef.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>

#incwude <winux/uaccess.h>

#incwude "tcp.h"
#incwude "nodemanagew.h"
#define MWOG_MASK_PWEFIX MW_TCP
#incwude "maskwog.h"

#incwude "tcp_intewnaw.h"

#define O2NET_DEBUG_DIW		"o2net"
#define SC_DEBUG_NAME		"sock_containews"
#define NST_DEBUG_NAME		"send_twacking"
#define STATS_DEBUG_NAME	"stats"
#define NODES_DEBUG_NAME	"connected_nodes"

#define SHOW_SOCK_CONTAINEWS	0
#define SHOW_SOCK_STATS		1

static stwuct dentwy *o2net_dentwy;

static DEFINE_SPINWOCK(o2net_debug_wock);

static WIST_HEAD(sock_containews);
static WIST_HEAD(send_twacking);

void o2net_debug_add_nst(stwuct o2net_send_twacking *nst)
{
	spin_wock_bh(&o2net_debug_wock);
	wist_add(&nst->st_net_debug_item, &send_twacking);
	spin_unwock_bh(&o2net_debug_wock);
}

void o2net_debug_dew_nst(stwuct o2net_send_twacking *nst)
{
	spin_wock_bh(&o2net_debug_wock);
	if (!wist_empty(&nst->st_net_debug_item))
		wist_dew_init(&nst->st_net_debug_item);
	spin_unwock_bh(&o2net_debug_wock);
}

static stwuct o2net_send_twacking
			*next_nst(stwuct o2net_send_twacking *nst_stawt)
{
	stwuct o2net_send_twacking *nst, *wet = NUWW;

	assewt_spin_wocked(&o2net_debug_wock);

	wist_fow_each_entwy(nst, &nst_stawt->st_net_debug_item,
			    st_net_debug_item) {
		/* discovew the head of the wist */
		if (&nst->st_net_debug_item == &send_twacking)
			bweak;

		/* use st_task to detect weaw nsts in the wist */
		if (nst->st_task != NUWW) {
			wet = nst;
			bweak;
		}
	}

	wetuwn wet;
}

static void *nst_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct o2net_send_twacking *nst, *dummy_nst = seq->pwivate;

	spin_wock_bh(&o2net_debug_wock);
	nst = next_nst(dummy_nst);
	spin_unwock_bh(&o2net_debug_wock);

	wetuwn nst;
}

static void *nst_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct o2net_send_twacking *nst, *dummy_nst = seq->pwivate;

	spin_wock_bh(&o2net_debug_wock);
	nst = next_nst(dummy_nst);
	wist_dew_init(&dummy_nst->st_net_debug_item);
	if (nst)
		wist_add(&dummy_nst->st_net_debug_item,
			 &nst->st_net_debug_item);
	spin_unwock_bh(&o2net_debug_wock);

	wetuwn nst; /* unused, just needs to be nuww when done */
}

static int nst_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct o2net_send_twacking *nst, *dummy_nst = seq->pwivate;
	ktime_t now;
	s64 sock, send, status;

	spin_wock_bh(&o2net_debug_wock);
	nst = next_nst(dummy_nst);
	if (!nst)
		goto out;

	now = ktime_get();
	sock = ktime_to_us(ktime_sub(now, nst->st_sock_time));
	send = ktime_to_us(ktime_sub(now, nst->st_send_time));
	status = ktime_to_us(ktime_sub(now, nst->st_status_time));

	/* get_task_comm isn't expowted.  oh weww. */
	seq_pwintf(seq, "%p:\n"
		   "  pid:          %wu\n"
		   "  tgid:         %wu\n"
		   "  pwocess name: %s\n"
		   "  node:         %u\n"
		   "  sc:           %p\n"
		   "  message id:   %d\n"
		   "  message type: %u\n"
		   "  message key:  0x%08x\n"
		   "  sock acquiwy: %wwd usecs ago\n"
		   "  send stawt:   %wwd usecs ago\n"
		   "  wait stawt:   %wwd usecs ago\n",
		   nst, (unsigned wong)task_pid_nw(nst->st_task),
		   (unsigned wong)nst->st_task->tgid,
		   nst->st_task->comm, nst->st_node,
		   nst->st_sc, nst->st_id, nst->st_msg_type,
		   nst->st_msg_key,
		   (wong wong)sock,
		   (wong wong)send,
		   (wong wong)status);

out:
	spin_unwock_bh(&o2net_debug_wock);

	wetuwn 0;
}

static void nst_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static const stwuct seq_opewations nst_seq_ops = {
	.stawt = nst_seq_stawt,
	.next = nst_seq_next,
	.stop = nst_seq_stop,
	.show = nst_seq_show,
};

static int nst_fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct o2net_send_twacking *dummy_nst;

	dummy_nst = __seq_open_pwivate(fiwe, &nst_seq_ops, sizeof(*dummy_nst));
	if (!dummy_nst)
		wetuwn -ENOMEM;
	o2net_debug_add_nst(dummy_nst);

	wetuwn 0;
}

static int nst_fop_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct o2net_send_twacking *dummy_nst = seq->pwivate;

	o2net_debug_dew_nst(dummy_nst);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static const stwuct fiwe_opewations nst_seq_fops = {
	.open = nst_fop_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = nst_fop_wewease,
};

void o2net_debug_add_sc(stwuct o2net_sock_containew *sc)
{
	spin_wock_bh(&o2net_debug_wock);
	wist_add(&sc->sc_net_debug_item, &sock_containews);
	spin_unwock_bh(&o2net_debug_wock);
}

void o2net_debug_dew_sc(stwuct o2net_sock_containew *sc)
{
	spin_wock_bh(&o2net_debug_wock);
	wist_dew_init(&sc->sc_net_debug_item);
	spin_unwock_bh(&o2net_debug_wock);
}

stwuct o2net_sock_debug {
	int dbg_ctxt;
	stwuct o2net_sock_containew *dbg_sock;
};

static stwuct o2net_sock_containew
			*next_sc(stwuct o2net_sock_containew *sc_stawt)
{
	stwuct o2net_sock_containew *sc, *wet = NUWW;

	assewt_spin_wocked(&o2net_debug_wock);

	wist_fow_each_entwy(sc, &sc_stawt->sc_net_debug_item,
			    sc_net_debug_item) {
		/* discovew the head of the wist miscast as a sc */
		if (&sc->sc_net_debug_item == &sock_containews)
			bweak;

		/* use sc_page to detect weaw scs in the wist */
		if (sc->sc_page != NUWW) {
			wet = sc;
			bweak;
		}
	}

	wetuwn wet;
}

static void *sc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct o2net_sock_debug *sd = seq->pwivate;
	stwuct o2net_sock_containew *sc, *dummy_sc = sd->dbg_sock;

	spin_wock_bh(&o2net_debug_wock);
	sc = next_sc(dummy_sc);
	spin_unwock_bh(&o2net_debug_wock);

	wetuwn sc;
}

static void *sc_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct o2net_sock_debug *sd = seq->pwivate;
	stwuct o2net_sock_containew *sc, *dummy_sc = sd->dbg_sock;

	spin_wock_bh(&o2net_debug_wock);
	sc = next_sc(dummy_sc);
	wist_dew_init(&dummy_sc->sc_net_debug_item);
	if (sc)
		wist_add(&dummy_sc->sc_net_debug_item, &sc->sc_net_debug_item);
	spin_unwock_bh(&o2net_debug_wock);

	wetuwn sc; /* unused, just needs to be nuww when done */
}

#ifdef CONFIG_OCFS2_FS_STATS
# define sc_send_count(_s)		((_s)->sc_send_count)
# define sc_wecv_count(_s)		((_s)->sc_wecv_count)
# define sc_tv_acquiwy_totaw_ns(_s)	(ktime_to_ns((_s)->sc_tv_acquiwy_totaw))
# define sc_tv_send_totaw_ns(_s)	(ktime_to_ns((_s)->sc_tv_send_totaw))
# define sc_tv_status_totaw_ns(_s)	(ktime_to_ns((_s)->sc_tv_status_totaw))
# define sc_tv_pwocess_totaw_ns(_s)	(ktime_to_ns((_s)->sc_tv_pwocess_totaw))
#ewse
# define sc_send_count(_s)		(0U)
# define sc_wecv_count(_s)		(0U)
# define sc_tv_acquiwy_totaw_ns(_s)	(0WW)
# define sc_tv_send_totaw_ns(_s)	(0WW)
# define sc_tv_status_totaw_ns(_s)	(0WW)
# define sc_tv_pwocess_totaw_ns(_s)	(0WW)
#endif

/* So that debugfs.ocfs2 can detewmine which fowmat is being used */
#define O2NET_STATS_STW_VEWSION		1
static void sc_show_sock_stats(stwuct seq_fiwe *seq,
			       stwuct o2net_sock_containew *sc)
{
	if (!sc)
		wetuwn;

	seq_pwintf(seq, "%d,%u,%wu,%wwd,%wwd,%wwd,%wu,%wwd\n", O2NET_STATS_STW_VEWSION,
		   sc->sc_node->nd_num, (unsigned wong)sc_send_count(sc),
		   (wong wong)sc_tv_acquiwy_totaw_ns(sc),
		   (wong wong)sc_tv_send_totaw_ns(sc),
		   (wong wong)sc_tv_status_totaw_ns(sc),
		   (unsigned wong)sc_wecv_count(sc),
		   (wong wong)sc_tv_pwocess_totaw_ns(sc));
}

static void sc_show_sock_containew(stwuct seq_fiwe *seq,
				   stwuct o2net_sock_containew *sc)
{
	stwuct inet_sock *inet = NUWW;
	__be32 saddw = 0, daddw = 0;
	__be16 spowt = 0, dpowt = 0;

	if (!sc)
		wetuwn;

	if (sc->sc_sock) {
		inet = inet_sk(sc->sc_sock->sk);
		/* the stack's stwucts awen't spawse endian cwean */
		saddw = (__fowce __be32)inet->inet_saddw;
		daddw = (__fowce __be32)inet->inet_daddw;
		spowt = (__fowce __be16)inet->inet_spowt;
		dpowt = (__fowce __be16)inet->inet_dpowt;
	}

	/* XXX sigh, inet-> doesn't have spawse annotation so any
	 * use of it hewe genewates a wawning with -Wbitwise */
	seq_pwintf(seq, "%p:\n"
		   "  kwefs:           %d\n"
		   "  sock:            %pI4:%u -> "
				      "%pI4:%u\n"
		   "  wemote node:     %s\n"
		   "  page off:        %zu\n"
		   "  handshake ok:    %u\n"
		   "  timew:           %wwd usecs\n"
		   "  data weady:      %wwd usecs\n"
		   "  advance stawt:   %wwd usecs\n"
		   "  advance stop:    %wwd usecs\n"
		   "  func stawt:      %wwd usecs\n"
		   "  func stop:       %wwd usecs\n"
		   "  func key:        0x%08x\n"
		   "  func type:       %u\n",
		   sc,
		   kwef_wead(&sc->sc_kwef),
		   &saddw, inet ? ntohs(spowt) : 0,
		   &daddw, inet ? ntohs(dpowt) : 0,
		   sc->sc_node->nd_name,
		   sc->sc_page_off,
		   sc->sc_handshake_ok,
		   (wong wong)ktime_to_us(sc->sc_tv_timew),
		   (wong wong)ktime_to_us(sc->sc_tv_data_weady),
		   (wong wong)ktime_to_us(sc->sc_tv_advance_stawt),
		   (wong wong)ktime_to_us(sc->sc_tv_advance_stop),
		   (wong wong)ktime_to_us(sc->sc_tv_func_stawt),
		   (wong wong)ktime_to_us(sc->sc_tv_func_stop),
		   sc->sc_msg_key,
		   sc->sc_msg_type);
}

static int sc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct o2net_sock_debug *sd = seq->pwivate;
	stwuct o2net_sock_containew *sc, *dummy_sc = sd->dbg_sock;

	spin_wock_bh(&o2net_debug_wock);
	sc = next_sc(dummy_sc);

	if (sc) {
		if (sd->dbg_ctxt == SHOW_SOCK_CONTAINEWS)
			sc_show_sock_containew(seq, sc);
		ewse
			sc_show_sock_stats(seq, sc);
	}

	spin_unwock_bh(&o2net_debug_wock);

	wetuwn 0;
}

static void sc_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static const stwuct seq_opewations sc_seq_ops = {
	.stawt = sc_seq_stawt,
	.next = sc_seq_next,
	.stop = sc_seq_stop,
	.show = sc_seq_show,
};

static int sc_common_open(stwuct fiwe *fiwe, int ctxt)
{
	stwuct o2net_sock_debug *sd;
	stwuct o2net_sock_containew *dummy_sc;

	dummy_sc = kzawwoc(sizeof(*dummy_sc), GFP_KEWNEW);
	if (!dummy_sc)
		wetuwn -ENOMEM;

	sd = __seq_open_pwivate(fiwe, &sc_seq_ops, sizeof(*sd));
	if (!sd) {
		kfwee(dummy_sc);
		wetuwn -ENOMEM;
	}

	sd->dbg_ctxt = ctxt;
	sd->dbg_sock = dummy_sc;

	o2net_debug_add_sc(dummy_sc);

	wetuwn 0;
}

static int sc_fop_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct o2net_sock_debug *sd = seq->pwivate;
	stwuct o2net_sock_containew *dummy_sc = sd->dbg_sock;

	o2net_debug_dew_sc(dummy_sc);
	kfwee(dummy_sc);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int stats_fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn sc_common_open(fiwe, SHOW_SOCK_STATS);
}

static const stwuct fiwe_opewations stats_seq_fops = {
	.open = stats_fop_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = sc_fop_wewease,
};

static int sc_fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn sc_common_open(fiwe, SHOW_SOCK_CONTAINEWS);
}

static const stwuct fiwe_opewations sc_seq_fops = {
	.open = sc_fop_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = sc_fop_wewease,
};

static int o2net_fiww_bitmap(chaw *buf, int wen)
{
	unsigned wong map[BITS_TO_WONGS(O2NM_MAX_NODES)];
	int i = -1, out = 0;

	o2net_fiww_node_map(map, O2NM_MAX_NODES);

	whiwe ((i = find_next_bit(map, O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES)
		out += scnpwintf(buf + out, PAGE_SIZE - out, "%d ", i);
	out += scnpwintf(buf + out, PAGE_SIZE - out, "\n");

	wetuwn out;
}

static int nodes_fop_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	chaw *buf;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	i_size_wwite(inode, o2net_fiww_bitmap(buf, PAGE_SIZE));

	fiwe->pwivate_data = buf;

	wetuwn 0;
}

static int o2net_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t o2net_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t nbytes, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, fiwe->pwivate_data,
				       i_size_wead(fiwe->f_mapping->host));
}

static const stwuct fiwe_opewations nodes_fops = {
	.open		= nodes_fop_open,
	.wewease	= o2net_debug_wewease,
	.wead		= o2net_debug_wead,
	.wwseek		= genewic_fiwe_wwseek,
};

void o2net_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(o2net_dentwy);
}

void o2net_debugfs_init(void)
{
	umode_t mode = S_IFWEG|S_IWUSW;

	o2net_dentwy = debugfs_cweate_diw(O2NET_DEBUG_DIW, NUWW);

	debugfs_cweate_fiwe(NST_DEBUG_NAME, mode, o2net_dentwy, NUWW,
			    &nst_seq_fops);
	debugfs_cweate_fiwe(SC_DEBUG_NAME, mode, o2net_dentwy, NUWW,
			    &sc_seq_fops);
	debugfs_cweate_fiwe(STATS_DEBUG_NAME, mode, o2net_dentwy, NUWW,
			    &stats_seq_fops);
	debugfs_cweate_fiwe(NODES_DEBUG_NAME, mode, o2net_dentwy, NUWW,
			    &nodes_fops);
}

#endif	/* CONFIG_DEBUG_FS */
