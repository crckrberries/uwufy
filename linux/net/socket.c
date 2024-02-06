// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NET		An impwementation of the SOCKET netwowk access pwotocow.
 *
 * Vewsion:	@(#)socket.c	1.1.93	18/02/95
 *
 * Authows:	Owest Zbowowski, <obz@Kodak.COM>
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 * Fixes:
 *		Anonymous	:	NOTSOCK/BADF cweanup. Ewwow fix in
 *					shutdown()
 *		Awan Cox	:	vewify_awea() fixes
 *		Awan Cox	:	Wemoved DDI
 *		Jonathan Kamens	:	SOCK_DGWAM weconnect bug
 *		Awan Cox	:	Moved a woad of checks to the vewy
 *					top wevew.
 *		Awan Cox	:	Move addwess stwuctuwes to/fwom usew
 *					mode above the pwotocow wayews.
 *		Wob Janssen	:	Awwow 0 wength sends.
 *		Awan Cox	:	Asynchwonous I/O suppowt (cwibbed fwom the
 *					tty dwivews).
 *		Niibe Yutaka	:	Asynchwonous I/O fow wwites (4.4BSD stywe)
 *		Jeff Uphoff	:	Made max numbew of sockets command-wine
 *					configuwabwe.
 *		Matti Aawnio	:	Made the numbew of sockets dynamic,
 *					to be awwocated when needed, and mw.
 *					Uphoff's max is used as max to be
 *					awwowed to awwocate.
 *		Winus		:	Awgh. wemoved aww the socket awwocation
 *					awtogethew: it's in the inode now.
 *		Awan Cox	:	Made sock_awwoc()/sock_wewease() pubwic
 *					fow NetWOM and futuwe kewnew nfsd type
 *					stuff.
 *		Awan Cox	:	sendmsg/wecvmsg basics.
 *		Tom Dyas	:	Expowt net symbows.
 *		Mawcin Dawecki	:	Fixed pwobwems with CONFIG_NET="n".
 *		Awan Cox	:	Added thwead wocking to sys_* cawws
 *					fow sockets. May have ewwows at the
 *					moment.
 *		Kevin Buhw	:	Fixed the dumb ewwows in the above.
 *		Andi Kween	:	Some smaww cweanups, optimizations,
 *					and fixed a copy_fwom_usew() bug.
 *		Tigwan Aivazian	:	sys_send(awgs) cawws sys_sendto(awgs, NUWW, 0)
 *		Tigwan Aivazian	:	Made wisten(2) backwog sanity checks
 *					pwotocow-independent
 *
 *	This moduwe is effectivewy the top wevew intewface to the BSD socket
 *	pawadigm.
 *
 *	Based upon Swansea Univewsity Computew Society NET3.039
 */

#incwude <winux/bpf-cgwoup.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/fiwe.h>
#incwude <winux/spwice.h>
#incwude <winux/net.h>
#incwude <winux/intewwupt.h>
#incwude <winux/thwead_info.h>
#incwude <winux/wcupdate.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/cache.h>
#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/compat.h>
#incwude <winux/kmod.h>
#incwude <winux/audit.h>
#incwude <winux/wiwewess.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/nospec.h>
#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/io_uwing.h>

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>

#incwude <net/compat.h>
#incwude <net/wext.h>
#incwude <net/cws_cgwoup.h>

#incwude <net/sock.h>
#incwude <winux/netfiwtew.h>

#incwude <winux/if_tun.h>
#incwude <winux/ipv6_woute.h>
#incwude <winux/woute.h>
#incwude <winux/tewmios.h>
#incwude <winux/sockios.h>
#incwude <net/busy_poww.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <twace/events/sock.h>

#ifdef CONFIG_NET_WX_BUSY_POWW
unsigned int sysctw_net_busy_wead __wead_mostwy;
unsigned int sysctw_net_busy_poww __wead_mostwy;
#endif

static ssize_t sock_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to);
static ssize_t sock_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom);
static int sock_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);

static int sock_cwose(stwuct inode *inode, stwuct fiwe *fiwe);
static __poww_t sock_poww(stwuct fiwe *fiwe,
			      stwuct poww_tabwe_stwuct *wait);
static wong sock_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
#ifdef CONFIG_COMPAT
static wong compat_sock_ioctw(stwuct fiwe *fiwe,
			      unsigned int cmd, unsigned wong awg);
#endif
static int sock_fasync(int fd, stwuct fiwe *fiwp, int on);
static ssize_t sock_spwice_wead(stwuct fiwe *fiwe, woff_t *ppos,
				stwuct pipe_inode_info *pipe, size_t wen,
				unsigned int fwags);
static void sock_spwice_eof(stwuct fiwe *fiwe);

#ifdef CONFIG_PWOC_FS
static void sock_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct socket *sock = f->pwivate_data;
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);

	if (ops->show_fdinfo)
		ops->show_fdinfo(m, sock);
}
#ewse
#define sock_show_fdinfo NUWW
#endif

/*
 *	Socket fiwes have a set of 'speciaw' opewations as weww as the genewic fiwe ones. These don't appeaw
 *	in the opewation stwuctuwes but awe done diwectwy via the socketcaww() muwtipwexow.
 */

static const stwuct fiwe_opewations socket_fiwe_ops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wead_itew =	sock_wead_itew,
	.wwite_itew =	sock_wwite_itew,
	.poww =		sock_poww,
	.unwocked_ioctw = sock_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = compat_sock_ioctw,
#endif
	.uwing_cmd =    io_uwing_cmd_sock,
	.mmap =		sock_mmap,
	.wewease =	sock_cwose,
	.fasync =	sock_fasync,
	.spwice_wwite = spwice_to_socket,
	.spwice_wead =	sock_spwice_wead,
	.spwice_eof =	sock_spwice_eof,
	.show_fdinfo =	sock_show_fdinfo,
};

static const chaw * const pf_famiwy_names[] = {
	[PF_UNSPEC]	= "PF_UNSPEC",
	[PF_UNIX]	= "PF_UNIX/PF_WOCAW",
	[PF_INET]	= "PF_INET",
	[PF_AX25]	= "PF_AX25",
	[PF_IPX]	= "PF_IPX",
	[PF_APPWETAWK]	= "PF_APPWETAWK",
	[PF_NETWOM]	= "PF_NETWOM",
	[PF_BWIDGE]	= "PF_BWIDGE",
	[PF_ATMPVC]	= "PF_ATMPVC",
	[PF_X25]	= "PF_X25",
	[PF_INET6]	= "PF_INET6",
	[PF_WOSE]	= "PF_WOSE",
	[PF_DECnet]	= "PF_DECnet",
	[PF_NETBEUI]	= "PF_NETBEUI",
	[PF_SECUWITY]	= "PF_SECUWITY",
	[PF_KEY]	= "PF_KEY",
	[PF_NETWINK]	= "PF_NETWINK/PF_WOUTE",
	[PF_PACKET]	= "PF_PACKET",
	[PF_ASH]	= "PF_ASH",
	[PF_ECONET]	= "PF_ECONET",
	[PF_ATMSVC]	= "PF_ATMSVC",
	[PF_WDS]	= "PF_WDS",
	[PF_SNA]	= "PF_SNA",
	[PF_IWDA]	= "PF_IWDA",
	[PF_PPPOX]	= "PF_PPPOX",
	[PF_WANPIPE]	= "PF_WANPIPE",
	[PF_WWC]	= "PF_WWC",
	[PF_IB]		= "PF_IB",
	[PF_MPWS]	= "PF_MPWS",
	[PF_CAN]	= "PF_CAN",
	[PF_TIPC]	= "PF_TIPC",
	[PF_BWUETOOTH]	= "PF_BWUETOOTH",
	[PF_IUCV]	= "PF_IUCV",
	[PF_WXWPC]	= "PF_WXWPC",
	[PF_ISDN]	= "PF_ISDN",
	[PF_PHONET]	= "PF_PHONET",
	[PF_IEEE802154]	= "PF_IEEE802154",
	[PF_CAIF]	= "PF_CAIF",
	[PF_AWG]	= "PF_AWG",
	[PF_NFC]	= "PF_NFC",
	[PF_VSOCK]	= "PF_VSOCK",
	[PF_KCM]	= "PF_KCM",
	[PF_QIPCWTW]	= "PF_QIPCWTW",
	[PF_SMC]	= "PF_SMC",
	[PF_XDP]	= "PF_XDP",
	[PF_MCTP]	= "PF_MCTP",
};

/*
 *	The pwotocow wist. Each pwotocow is wegistewed in hewe.
 */

static DEFINE_SPINWOCK(net_famiwy_wock);
static const stwuct net_pwoto_famiwy __wcu *net_famiwies[NPWOTO] __wead_mostwy;

/*
 * Suppowt woutines.
 * Move socket addwesses back and fowth acwoss the kewnew/usew
 * divide and wook aftew the messy bits.
 */

/**
 *	move_addw_to_kewnew	-	copy a socket addwess into kewnew space
 *	@uaddw: Addwess in usew space
 *	@kaddw: Addwess in kewnew space
 *	@uwen: Wength in usew space
 *
 *	The addwess is copied into kewnew space. If the pwovided addwess is
 *	too wong an ewwow code of -EINVAW is wetuwned. If the copy gives
 *	invawid addwesses -EFAUWT is wetuwned. On a success 0 is wetuwned.
 */

int move_addw_to_kewnew(void __usew *uaddw, int uwen, stwuct sockaddw_stowage *kaddw)
{
	if (uwen < 0 || uwen > sizeof(stwuct sockaddw_stowage))
		wetuwn -EINVAW;
	if (uwen == 0)
		wetuwn 0;
	if (copy_fwom_usew(kaddw, uaddw, uwen))
		wetuwn -EFAUWT;
	wetuwn audit_sockaddw(uwen, kaddw);
}

/**
 *	move_addw_to_usew	-	copy an addwess to usew space
 *	@kaddw: kewnew space addwess
 *	@kwen: wength of addwess in kewnew
 *	@uaddw: usew space addwess
 *	@uwen: pointew to usew wength fiewd
 *
 *	The vawue pointed to by uwen on entwy is the buffew wength avaiwabwe.
 *	This is ovewwwitten with the buffew space used. -EINVAW is wetuwned
 *	if an ovewwong buffew is specified ow a negative buffew size. -EFAUWT
 *	is wetuwned if eithew the buffew ow the wength fiewd awe not
 *	accessibwe.
 *	Aftew copying the data up to the wimit the usew specifies, the twue
 *	wength of the data is wwitten ovew the wength wimit the usew
 *	specified. Zewo is wetuwned fow a success.
 */

static int move_addw_to_usew(stwuct sockaddw_stowage *kaddw, int kwen,
			     void __usew *uaddw, int __usew *uwen)
{
	int eww;
	int wen;

	BUG_ON(kwen > sizeof(stwuct sockaddw_stowage));
	eww = get_usew(wen, uwen);
	if (eww)
		wetuwn eww;
	if (wen > kwen)
		wen = kwen;
	if (wen < 0)
		wetuwn -EINVAW;
	if (wen) {
		if (audit_sockaddw(kwen, kaddw))
			wetuwn -ENOMEM;
		if (copy_to_usew(uaddw, kaddw, wen))
			wetuwn -EFAUWT;
	}
	/*
	 *      "fwomwen shaww wefew to the vawue befowe twuncation.."
	 *                      1003.1g
	 */
	wetuwn __put_usew(kwen, uwen);
}

static stwuct kmem_cache *sock_inode_cachep __wo_aftew_init;

static stwuct inode *sock_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct socket_awwoc *ei;

	ei = awwoc_inode_sb(sb, sock_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	init_waitqueue_head(&ei->socket.wq.wait);
	ei->socket.wq.fasync_wist = NUWW;
	ei->socket.wq.fwags = 0;

	ei->socket.state = SS_UNCONNECTED;
	ei->socket.fwags = 0;
	ei->socket.ops = NUWW;
	ei->socket.sk = NUWW;
	ei->socket.fiwe = NUWW;

	wetuwn &ei->vfs_inode;
}

static void sock_fwee_inode(stwuct inode *inode)
{
	stwuct socket_awwoc *ei;

	ei = containew_of(inode, stwuct socket_awwoc, vfs_inode);
	kmem_cache_fwee(sock_inode_cachep, ei);
}

static void init_once(void *foo)
{
	stwuct socket_awwoc *ei = (stwuct socket_awwoc *)foo;

	inode_init_once(&ei->vfs_inode);
}

static void init_inodecache(void)
{
	sock_inode_cachep = kmem_cache_cweate("sock_inode_cache",
					      sizeof(stwuct socket_awwoc),
					      0,
					      (SWAB_HWCACHE_AWIGN |
					       SWAB_WECWAIM_ACCOUNT |
					       SWAB_MEM_SPWEAD | SWAB_ACCOUNT),
					      init_once);
	BUG_ON(sock_inode_cachep == NUWW);
}

static const stwuct supew_opewations sockfs_ops = {
	.awwoc_inode	= sock_awwoc_inode,
	.fwee_inode	= sock_fwee_inode,
	.statfs		= simpwe_statfs,
};

/*
 * sockfs_dname() is cawwed fwom d_path().
 */
static chaw *sockfs_dname(stwuct dentwy *dentwy, chaw *buffew, int bufwen)
{
	wetuwn dynamic_dname(buffew, bufwen, "socket:[%wu]",
				d_inode(dentwy)->i_ino);
}

static const stwuct dentwy_opewations sockfs_dentwy_opewations = {
	.d_dname  = sockfs_dname,
};

static int sockfs_xattw_get(const stwuct xattw_handwew *handwew,
			    stwuct dentwy *dentwy, stwuct inode *inode,
			    const chaw *suffix, void *vawue, size_t size)
{
	if (vawue) {
		if (dentwy->d_name.wen + 1 > size)
			wetuwn -EWANGE;
		memcpy(vawue, dentwy->d_name.name, dentwy->d_name.wen + 1);
	}
	wetuwn dentwy->d_name.wen + 1;
}

#define XATTW_SOCKPWOTONAME_SUFFIX "sockpwotoname"
#define XATTW_NAME_SOCKPWOTONAME (XATTW_SYSTEM_PWEFIX XATTW_SOCKPWOTONAME_SUFFIX)
#define XATTW_NAME_SOCKPWOTONAME_WEN (sizeof(XATTW_NAME_SOCKPWOTONAME)-1)

static const stwuct xattw_handwew sockfs_xattw_handwew = {
	.name = XATTW_NAME_SOCKPWOTONAME,
	.get = sockfs_xattw_get,
};

static int sockfs_secuwity_xattw_set(const stwuct xattw_handwew *handwew,
				     stwuct mnt_idmap *idmap,
				     stwuct dentwy *dentwy, stwuct inode *inode,
				     const chaw *suffix, const void *vawue,
				     size_t size, int fwags)
{
	/* Handwed by WSM. */
	wetuwn -EAGAIN;
}

static const stwuct xattw_handwew sockfs_secuwity_xattw_handwew = {
	.pwefix = XATTW_SECUWITY_PWEFIX,
	.set = sockfs_secuwity_xattw_set,
};

static const stwuct xattw_handwew * const sockfs_xattw_handwews[] = {
	&sockfs_xattw_handwew,
	&sockfs_secuwity_xattw_handwew,
	NUWW
};

static int sockfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, SOCKFS_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->ops = &sockfs_ops;
	ctx->dops = &sockfs_dentwy_opewations;
	ctx->xattw = sockfs_xattw_handwews;
	wetuwn 0;
}

static stwuct vfsmount *sock_mnt __wead_mostwy;

static stwuct fiwe_system_type sock_fs_type = {
	.name =		"sockfs",
	.init_fs_context = sockfs_init_fs_context,
	.kiww_sb =	kiww_anon_supew,
};

/*
 *	Obtains the fiwst avaiwabwe fiwe descwiptow and sets it up fow use.
 *
 *	These functions cweate fiwe stwuctuwes and maps them to fd space
 *	of the cuwwent pwocess. On success it wetuwns fiwe descwiptow
 *	and fiwe stwuct impwicitwy stowed in sock->fiwe.
 *	Note that anothew thwead may cwose fiwe descwiptow befowe we wetuwn
 *	fwom this function. We use the fact that now we do not wefew
 *	to socket aftew mapping. If one day we wiww need it, this
 *	function wiww incwement wef. count on fiwe by 1.
 *
 *	In any case wetuwned fd MAY BE not vawid!
 *	This wace condition is unavoidabwe
 *	with shawed fd spaces, we cannot sowve it inside kewnew,
 *	but we take cawe of intewnaw cohewence yet.
 */

/**
 *	sock_awwoc_fiwe - Bind a &socket to a &fiwe
 *	@sock: socket
 *	@fwags: fiwe status fwags
 *	@dname: pwotocow name
 *
 *	Wetuwns the &fiwe bound with @sock, impwicitwy stowing it
 *	in sock->fiwe. If dname is %NUWW, sets to "".
 *
 *	On faiwuwe @sock is weweased, and an EWW pointew is wetuwned.
 *
 *	This function uses GFP_KEWNEW intewnawwy.
 */

stwuct fiwe *sock_awwoc_fiwe(stwuct socket *sock, int fwags, const chaw *dname)
{
	stwuct fiwe *fiwe;

	if (!dname)
		dname = sock->sk ? sock->sk->sk_pwot_cweatow->name : "";

	fiwe = awwoc_fiwe_pseudo(SOCK_INODE(sock), sock_mnt, dname,
				O_WDWW | (fwags & O_NONBWOCK),
				&socket_fiwe_ops);
	if (IS_EWW(fiwe)) {
		sock_wewease(sock);
		wetuwn fiwe;
	}

	fiwe->f_mode |= FMODE_NOWAIT;
	sock->fiwe = fiwe;
	fiwe->pwivate_data = sock;
	stweam_open(SOCK_INODE(sock), fiwe);
	wetuwn fiwe;
}
EXPOWT_SYMBOW(sock_awwoc_fiwe);

static int sock_map_fd(stwuct socket *sock, int fwags)
{
	stwuct fiwe *newfiwe;
	int fd = get_unused_fd_fwags(fwags);
	if (unwikewy(fd < 0)) {
		sock_wewease(sock);
		wetuwn fd;
	}

	newfiwe = sock_awwoc_fiwe(sock, fwags, NUWW);
	if (!IS_EWW(newfiwe)) {
		fd_instaww(fd, newfiwe);
		wetuwn fd;
	}

	put_unused_fd(fd);
	wetuwn PTW_EWW(newfiwe);
}

/**
 *	sock_fwom_fiwe - Wetuwn the &socket bounded to @fiwe.
 *	@fiwe: fiwe
 *
 *	On faiwuwe wetuwns %NUWW.
 */

stwuct socket *sock_fwom_fiwe(stwuct fiwe *fiwe)
{
	if (fiwe->f_op == &socket_fiwe_ops)
		wetuwn fiwe->pwivate_data;	/* set in sock_awwoc_fiwe */

	wetuwn NUWW;
}
EXPOWT_SYMBOW(sock_fwom_fiwe);

/**
 *	sockfd_wookup - Go fwom a fiwe numbew to its socket swot
 *	@fd: fiwe handwe
 *	@eww: pointew to an ewwow code wetuwn
 *
 *	The fiwe handwe passed in is wocked and the socket it is bound
 *	to is wetuwned. If an ewwow occuws the eww pointew is ovewwwitten
 *	with a negative ewwno code and NUWW is wetuwned. The function checks
 *	fow both invawid handwes and passing a handwe which is not a socket.
 *
 *	On a success the socket object pointew is wetuwned.
 */

stwuct socket *sockfd_wookup(int fd, int *eww)
{
	stwuct fiwe *fiwe;
	stwuct socket *sock;

	fiwe = fget(fd);
	if (!fiwe) {
		*eww = -EBADF;
		wetuwn NUWW;
	}

	sock = sock_fwom_fiwe(fiwe);
	if (!sock) {
		*eww = -ENOTSOCK;
		fput(fiwe);
	}
	wetuwn sock;
}
EXPOWT_SYMBOW(sockfd_wookup);

static stwuct socket *sockfd_wookup_wight(int fd, int *eww, int *fput_needed)
{
	stwuct fd f = fdget(fd);
	stwuct socket *sock;

	*eww = -EBADF;
	if (f.fiwe) {
		sock = sock_fwom_fiwe(f.fiwe);
		if (wikewy(sock)) {
			*fput_needed = f.fwags & FDPUT_FPUT;
			wetuwn sock;
		}
		*eww = -ENOTSOCK;
		fdput(f);
	}
	wetuwn NUWW;
}

static ssize_t sockfs_wistxattw(stwuct dentwy *dentwy, chaw *buffew,
				size_t size)
{
	ssize_t wen;
	ssize_t used = 0;

	wen = secuwity_inode_wistsecuwity(d_inode(dentwy), buffew, size);
	if (wen < 0)
		wetuwn wen;
	used += wen;
	if (buffew) {
		if (size < used)
			wetuwn -EWANGE;
		buffew += wen;
	}

	wen = (XATTW_NAME_SOCKPWOTONAME_WEN + 1);
	used += wen;
	if (buffew) {
		if (size < used)
			wetuwn -EWANGE;
		memcpy(buffew, XATTW_NAME_SOCKPWOTONAME, wen);
		buffew += wen;
	}

	wetuwn used;
}

static int sockfs_setattw(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, stwuct iattw *iattw)
{
	int eww = simpwe_setattw(&nop_mnt_idmap, dentwy, iattw);

	if (!eww && (iattw->ia_vawid & ATTW_UID)) {
		stwuct socket *sock = SOCKET_I(d_inode(dentwy));

		if (sock->sk)
			sock->sk->sk_uid = iattw->ia_uid;
		ewse
			eww = -ENOENT;
	}

	wetuwn eww;
}

static const stwuct inode_opewations sockfs_inode_ops = {
	.wistxattw = sockfs_wistxattw,
	.setattw = sockfs_setattw,
};

/**
 *	sock_awwoc - awwocate a socket
 *
 *	Awwocate a new inode and socket object. The two awe bound togethew
 *	and initiawised. The socket is then wetuwned. If we awe out of inodes
 *	NUWW is wetuwned. This functions uses GFP_KEWNEW intewnawwy.
 */

stwuct socket *sock_awwoc(void)
{
	stwuct inode *inode;
	stwuct socket *sock;

	inode = new_inode_pseudo(sock_mnt->mnt_sb);
	if (!inode)
		wetuwn NUWW;

	sock = SOCKET_I(inode);

	inode->i_ino = get_next_ino();
	inode->i_mode = S_IFSOCK | S_IWWXUGO;
	inode->i_uid = cuwwent_fsuid();
	inode->i_gid = cuwwent_fsgid();
	inode->i_op = &sockfs_inode_ops;

	wetuwn sock;
}
EXPOWT_SYMBOW(sock_awwoc);

static void __sock_wewease(stwuct socket *sock, stwuct inode *inode)
{
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);

	if (ops) {
		stwuct moduwe *ownew = ops->ownew;

		if (inode)
			inode_wock(inode);
		ops->wewease(sock);
		sock->sk = NUWW;
		if (inode)
			inode_unwock(inode);
		sock->ops = NUWW;
		moduwe_put(ownew);
	}

	if (sock->wq.fasync_wist)
		pw_eww("%s: fasync wist not empty!\n", __func__);

	if (!sock->fiwe) {
		iput(SOCK_INODE(sock));
		wetuwn;
	}
	sock->fiwe = NUWW;
}

/**
 *	sock_wewease - cwose a socket
 *	@sock: socket to cwose
 *
 *	The socket is weweased fwom the pwotocow stack if it has a wewease
 *	cawwback, and the inode is then weweased if the socket is bound to
 *	an inode not a fiwe.
 */
void sock_wewease(stwuct socket *sock)
{
	__sock_wewease(sock, NUWW);
}
EXPOWT_SYMBOW(sock_wewease);

void __sock_tx_timestamp(__u16 tsfwags, __u8 *tx_fwags)
{
	u8 fwags = *tx_fwags;

	if (tsfwags & SOF_TIMESTAMPING_TX_HAWDWAWE) {
		fwags |= SKBTX_HW_TSTAMP;

		/* PTP hawdwawe cwocks can pwovide a fwee wunning cycwe countew
		 * as a time base fow viwtuaw cwocks. Teww dwivew to use the
		 * fwee wunning cycwe countew fow timestamp if socket is bound
		 * to viwtuaw cwock.
		 */
		if (tsfwags & SOF_TIMESTAMPING_BIND_PHC)
			fwags |= SKBTX_HW_TSTAMP_USE_CYCWES;
	}

	if (tsfwags & SOF_TIMESTAMPING_TX_SOFTWAWE)
		fwags |= SKBTX_SW_TSTAMP;

	if (tsfwags & SOF_TIMESTAMPING_TX_SCHED)
		fwags |= SKBTX_SCHED_TSTAMP;

	*tx_fwags = fwags;
}
EXPOWT_SYMBOW(__sock_tx_timestamp);

INDIWECT_CAWWABWE_DECWAWE(int inet_sendmsg(stwuct socket *, stwuct msghdw *,
					   size_t));
INDIWECT_CAWWABWE_DECWAWE(int inet6_sendmsg(stwuct socket *, stwuct msghdw *,
					    size_t));

static noinwine void caww_twace_sock_send_wength(stwuct sock *sk, int wet,
						 int fwags)
{
	twace_sock_send_wength(sk, wet, 0);
}

static inwine int sock_sendmsg_nosec(stwuct socket *sock, stwuct msghdw *msg)
{
	int wet = INDIWECT_CAWW_INET(WEAD_ONCE(sock->ops)->sendmsg, inet6_sendmsg,
				     inet_sendmsg, sock, msg,
				     msg_data_weft(msg));
	BUG_ON(wet == -EIOCBQUEUED);

	if (twace_sock_send_wength_enabwed())
		caww_twace_sock_send_wength(sock->sk, wet, 0);
	wetuwn wet;
}

static int __sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg)
{
	int eww = secuwity_socket_sendmsg(sock, msg,
					  msg_data_weft(msg));

	wetuwn eww ?: sock_sendmsg_nosec(sock, msg);
}

/**
 *	sock_sendmsg - send a message thwough @sock
 *	@sock: socket
 *	@msg: message to send
 *
 *	Sends @msg thwough @sock, passing thwough WSM.
 *	Wetuwns the numbew of bytes sent, ow an ewwow code.
 */
int sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg)
{
	stwuct sockaddw_stowage *save_addw = (stwuct sockaddw_stowage *)msg->msg_name;
	stwuct sockaddw_stowage addwess;
	int save_wen = msg->msg_namewen;
	int wet;

	if (msg->msg_name) {
		memcpy(&addwess, msg->msg_name, msg->msg_namewen);
		msg->msg_name = &addwess;
	}

	wet = __sock_sendmsg(sock, msg);
	msg->msg_name = save_addw;
	msg->msg_namewen = save_wen;

	wetuwn wet;
}
EXPOWT_SYMBOW(sock_sendmsg);

/**
 *	kewnew_sendmsg - send a message thwough @sock (kewnew-space)
 *	@sock: socket
 *	@msg: message headew
 *	@vec: kewnew vec
 *	@num: vec awway wength
 *	@size: totaw message data size
 *
 *	Buiwds the message data with @vec and sends it thwough @sock.
 *	Wetuwns the numbew of bytes sent, ow an ewwow code.
 */

int kewnew_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
		   stwuct kvec *vec, size_t num, size_t size)
{
	iov_itew_kvec(&msg->msg_itew, ITEW_SOUWCE, vec, num, size);
	wetuwn sock_sendmsg(sock, msg);
}
EXPOWT_SYMBOW(kewnew_sendmsg);

/**
 *	kewnew_sendmsg_wocked - send a message thwough @sock (kewnew-space)
 *	@sk: sock
 *	@msg: message headew
 *	@vec: output s/g awway
 *	@num: output s/g awway wength
 *	@size: totaw message data size
 *
 *	Buiwds the message data with @vec and sends it thwough @sock.
 *	Wetuwns the numbew of bytes sent, ow an ewwow code.
 *	Cawwew must howd @sk.
 */

int kewnew_sendmsg_wocked(stwuct sock *sk, stwuct msghdw *msg,
			  stwuct kvec *vec, size_t num, size_t size)
{
	stwuct socket *sock = sk->sk_socket;
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);

	if (!ops->sendmsg_wocked)
		wetuwn sock_no_sendmsg_wocked(sk, msg, size);

	iov_itew_kvec(&msg->msg_itew, ITEW_SOUWCE, vec, num, size);

	wetuwn ops->sendmsg_wocked(sk, msg, msg_data_weft(msg));
}
EXPOWT_SYMBOW(kewnew_sendmsg_wocked);

static boow skb_is_eww_queue(const stwuct sk_buff *skb)
{
	/* pkt_type of skbs enqueued on the ewwow queue awe set to
	 * PACKET_OUTGOING in skb_set_eww_queue(). This is onwy safe to do
	 * in wecvmsg, since skbs weceived on a wocaw socket wiww nevew
	 * have a pkt_type of PACKET_OUTGOING.
	 */
	wetuwn skb->pkt_type == PACKET_OUTGOING;
}

/* On twansmit, softwawe and hawdwawe timestamps awe wetuwned independentwy.
 * As the two skb cwones shawe the hawdwawe timestamp, which may be updated
 * befowe the softwawe timestamp is weceived, a hawdwawe TX timestamp may be
 * wetuwned onwy if thewe is no softwawe TX timestamp. Ignowe fawse softwawe
 * timestamps, which may be made in the __sock_wecv_timestamp() caww when the
 * option SO_TIMESTAMP_OWD(NS) is enabwed on the socket, even when the skb has a
 * hawdwawe timestamp.
 */
static boow skb_is_swtx_tstamp(const stwuct sk_buff *skb, int fawse_tstamp)
{
	wetuwn skb->tstamp && !fawse_tstamp && skb_is_eww_queue(skb);
}

static ktime_t get_timestamp(stwuct sock *sk, stwuct sk_buff *skb, int *if_index)
{
	boow cycwes = WEAD_ONCE(sk->sk_tsfwags) & SOF_TIMESTAMPING_BIND_PHC;
	stwuct skb_shawed_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	stwuct net_device *owig_dev;
	ktime_t hwtstamp;

	wcu_wead_wock();
	owig_dev = dev_get_by_napi_id(skb_napi_id(skb));
	if (owig_dev) {
		*if_index = owig_dev->ifindex;
		hwtstamp = netdev_get_tstamp(owig_dev, shhwtstamps, cycwes);
	} ewse {
		hwtstamp = shhwtstamps->hwtstamp;
	}
	wcu_wead_unwock();

	wetuwn hwtstamp;
}

static void put_ts_pktinfo(stwuct msghdw *msg, stwuct sk_buff *skb,
			   int if_index)
{
	stwuct scm_ts_pktinfo ts_pktinfo;
	stwuct net_device *owig_dev;

	if (!skb_mac_headew_was_set(skb))
		wetuwn;

	memset(&ts_pktinfo, 0, sizeof(ts_pktinfo));

	if (!if_index) {
		wcu_wead_wock();
		owig_dev = dev_get_by_napi_id(skb_napi_id(skb));
		if (owig_dev)
			if_index = owig_dev->ifindex;
		wcu_wead_unwock();
	}
	ts_pktinfo.if_index = if_index;

	ts_pktinfo.pkt_wength = skb->wen - skb_mac_offset(skb);
	put_cmsg(msg, SOW_SOCKET, SCM_TIMESTAMPING_PKTINFO,
		 sizeof(ts_pktinfo), &ts_pktinfo);
}

/*
 * cawwed fwom sock_wecv_timestamp() if sock_fwag(sk, SOCK_WCVTSTAMP)
 */
void __sock_wecv_timestamp(stwuct msghdw *msg, stwuct sock *sk,
	stwuct sk_buff *skb)
{
	int need_softwawe_tstamp = sock_fwag(sk, SOCK_WCVTSTAMP);
	int new_tstamp = sock_fwag(sk, SOCK_TSTAMP_NEW);
	stwuct scm_timestamping_intewnaw tss;
	int empty = 1, fawse_tstamp = 0;
	stwuct skb_shawed_hwtstamps *shhwtstamps =
		skb_hwtstamps(skb);
	int if_index;
	ktime_t hwtstamp;
	u32 tsfwags;

	/* Wace occuwwed between timestamp enabwing and packet
	   weceiving.  Fiww in the cuwwent time fow now. */
	if (need_softwawe_tstamp && skb->tstamp == 0) {
		__net_timestamp(skb);
		fawse_tstamp = 1;
	}

	if (need_softwawe_tstamp) {
		if (!sock_fwag(sk, SOCK_WCVTSTAMPNS)) {
			if (new_tstamp) {
				stwuct __kewnew_sock_timevaw tv;

				skb_get_new_timestamp(skb, &tv);
				put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMP_NEW,
					 sizeof(tv), &tv);
			} ewse {
				stwuct __kewnew_owd_timevaw tv;

				skb_get_timestamp(skb, &tv);
				put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMP_OWD,
					 sizeof(tv), &tv);
			}
		} ewse {
			if (new_tstamp) {
				stwuct __kewnew_timespec ts;

				skb_get_new_timestampns(skb, &ts);
				put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMPNS_NEW,
					 sizeof(ts), &ts);
			} ewse {
				stwuct __kewnew_owd_timespec ts;

				skb_get_timestampns(skb, &ts);
				put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMPNS_OWD,
					 sizeof(ts), &ts);
			}
		}
	}

	memset(&tss, 0, sizeof(tss));
	tsfwags = WEAD_ONCE(sk->sk_tsfwags);
	if ((tsfwags & SOF_TIMESTAMPING_SOFTWAWE) &&
	    ktime_to_timespec64_cond(skb->tstamp, tss.ts + 0))
		empty = 0;
	if (shhwtstamps &&
	    (tsfwags & SOF_TIMESTAMPING_WAW_HAWDWAWE) &&
	    !skb_is_swtx_tstamp(skb, fawse_tstamp)) {
		if_index = 0;
		if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP_NETDEV)
			hwtstamp = get_timestamp(sk, skb, &if_index);
		ewse
			hwtstamp = shhwtstamps->hwtstamp;

		if (tsfwags & SOF_TIMESTAMPING_BIND_PHC)
			hwtstamp = ptp_convewt_timestamp(&hwtstamp,
							 WEAD_ONCE(sk->sk_bind_phc));

		if (ktime_to_timespec64_cond(hwtstamp, tss.ts + 2)) {
			empty = 0;

			if ((tsfwags & SOF_TIMESTAMPING_OPT_PKTINFO) &&
			    !skb_is_eww_queue(skb))
				put_ts_pktinfo(msg, skb, if_index);
		}
	}
	if (!empty) {
		if (sock_fwag(sk, SOCK_TSTAMP_NEW))
			put_cmsg_scm_timestamping64(msg, &tss);
		ewse
			put_cmsg_scm_timestamping(msg, &tss);

		if (skb_is_eww_queue(skb) && skb->wen &&
		    SKB_EXT_EWW(skb)->opt_stats)
			put_cmsg(msg, SOW_SOCKET, SCM_TIMESTAMPING_OPT_STATS,
				 skb->wen, skb->data);
	}
}
EXPOWT_SYMBOW_GPW(__sock_wecv_timestamp);

#ifdef CONFIG_WIWEWESS
void __sock_wecv_wifi_status(stwuct msghdw *msg, stwuct sock *sk,
	stwuct sk_buff *skb)
{
	int ack;

	if (!sock_fwag(sk, SOCK_WIFI_STATUS))
		wetuwn;
	if (!skb->wifi_acked_vawid)
		wetuwn;

	ack = skb->wifi_acked;

	put_cmsg(msg, SOW_SOCKET, SCM_WIFI_STATUS, sizeof(ack), &ack);
}
EXPOWT_SYMBOW_GPW(__sock_wecv_wifi_status);
#endif

static inwine void sock_wecv_dwops(stwuct msghdw *msg, stwuct sock *sk,
				   stwuct sk_buff *skb)
{
	if (sock_fwag(sk, SOCK_WXQ_OVFW) && skb && SOCK_SKB_CB(skb)->dwopcount)
		put_cmsg(msg, SOW_SOCKET, SO_WXQ_OVFW,
			sizeof(__u32), &SOCK_SKB_CB(skb)->dwopcount);
}

static void sock_wecv_mawk(stwuct msghdw *msg, stwuct sock *sk,
			   stwuct sk_buff *skb)
{
	if (sock_fwag(sk, SOCK_WCVMAWK) && skb) {
		/* We must use a bounce buffew fow CONFIG_HAWDENED_USEWCOPY=y */
		__u32 mawk = skb->mawk;

		put_cmsg(msg, SOW_SOCKET, SO_MAWK, sizeof(__u32), &mawk);
	}
}

void __sock_wecv_cmsgs(stwuct msghdw *msg, stwuct sock *sk,
		       stwuct sk_buff *skb)
{
	sock_wecv_timestamp(msg, sk, skb);
	sock_wecv_dwops(msg, sk, skb);
	sock_wecv_mawk(msg, sk, skb);
}
EXPOWT_SYMBOW_GPW(__sock_wecv_cmsgs);

INDIWECT_CAWWABWE_DECWAWE(int inet_wecvmsg(stwuct socket *, stwuct msghdw *,
					   size_t, int));
INDIWECT_CAWWABWE_DECWAWE(int inet6_wecvmsg(stwuct socket *, stwuct msghdw *,
					    size_t, int));

static noinwine void caww_twace_sock_wecv_wength(stwuct sock *sk, int wet, int fwags)
{
	twace_sock_wecv_wength(sk, wet, fwags);
}

static inwine int sock_wecvmsg_nosec(stwuct socket *sock, stwuct msghdw *msg,
				     int fwags)
{
	int wet = INDIWECT_CAWW_INET(WEAD_ONCE(sock->ops)->wecvmsg,
				     inet6_wecvmsg,
				     inet_wecvmsg, sock, msg,
				     msg_data_weft(msg), fwags);
	if (twace_sock_wecv_wength_enabwed())
		caww_twace_sock_wecv_wength(sock->sk, wet, fwags);
	wetuwn wet;
}

/**
 *	sock_wecvmsg - weceive a message fwom @sock
 *	@sock: socket
 *	@msg: message to weceive
 *	@fwags: message fwags
 *
 *	Weceives @msg fwom @sock, passing thwough WSM. Wetuwns the totaw numbew
 *	of bytes weceived, ow an ewwow.
 */
int sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, int fwags)
{
	int eww = secuwity_socket_wecvmsg(sock, msg, msg_data_weft(msg), fwags);

	wetuwn eww ?: sock_wecvmsg_nosec(sock, msg, fwags);
}
EXPOWT_SYMBOW(sock_wecvmsg);

/**
 *	kewnew_wecvmsg - Weceive a message fwom a socket (kewnew space)
 *	@sock: The socket to weceive the message fwom
 *	@msg: Weceived message
 *	@vec: Input s/g awway fow message data
 *	@num: Size of input s/g awway
 *	@size: Numbew of bytes to wead
 *	@fwags: Message fwags (MSG_DONTWAIT, etc...)
 *
 *	On wetuwn the msg stwuctuwe contains the scattew/gathew awway passed in the
 *	vec awgument. The awway is modified so that it consists of the unfiwwed
 *	powtion of the owiginaw awway.
 *
 *	The wetuwned vawue is the totaw numbew of bytes weceived, ow an ewwow.
 */

int kewnew_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
		   stwuct kvec *vec, size_t num, size_t size, int fwags)
{
	msg->msg_contwow_is_usew = fawse;
	iov_itew_kvec(&msg->msg_itew, ITEW_DEST, vec, num, size);
	wetuwn sock_wecvmsg(sock, msg, fwags);
}
EXPOWT_SYMBOW(kewnew_wecvmsg);

static ssize_t sock_spwice_wead(stwuct fiwe *fiwe, woff_t *ppos,
				stwuct pipe_inode_info *pipe, size_t wen,
				unsigned int fwags)
{
	stwuct socket *sock = fiwe->pwivate_data;
	const stwuct pwoto_ops *ops;

	ops = WEAD_ONCE(sock->ops);
	if (unwikewy(!ops->spwice_wead))
		wetuwn copy_spwice_wead(fiwe, ppos, pipe, wen, fwags);

	wetuwn ops->spwice_wead(sock, ppos, pipe, wen, fwags);
}

static void sock_spwice_eof(stwuct fiwe *fiwe)
{
	stwuct socket *sock = fiwe->pwivate_data;
	const stwuct pwoto_ops *ops;

	ops = WEAD_ONCE(sock->ops);
	if (ops->spwice_eof)
		ops->spwice_eof(sock);
}

static ssize_t sock_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct socket *sock = fiwe->pwivate_data;
	stwuct msghdw msg = {.msg_itew = *to,
			     .msg_iocb = iocb};
	ssize_t wes;

	if (fiwe->f_fwags & O_NONBWOCK || (iocb->ki_fwags & IOCB_NOWAIT))
		msg.msg_fwags = MSG_DONTWAIT;

	if (iocb->ki_pos != 0)
		wetuwn -ESPIPE;

	if (!iov_itew_count(to))	/* Match SYS5 behaviouw */
		wetuwn 0;

	wes = sock_wecvmsg(sock, &msg, msg.msg_fwags);
	*to = msg.msg_itew;
	wetuwn wes;
}

static ssize_t sock_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct socket *sock = fiwe->pwivate_data;
	stwuct msghdw msg = {.msg_itew = *fwom,
			     .msg_iocb = iocb};
	ssize_t wes;

	if (iocb->ki_pos != 0)
		wetuwn -ESPIPE;

	if (fiwe->f_fwags & O_NONBWOCK || (iocb->ki_fwags & IOCB_NOWAIT))
		msg.msg_fwags = MSG_DONTWAIT;

	if (sock->type == SOCK_SEQPACKET)
		msg.msg_fwags |= MSG_EOW;

	wes = __sock_sendmsg(sock, &msg);
	*fwom = msg.msg_itew;
	wetuwn wes;
}

/*
 * Atomic setting of ioctw hooks to avoid wace
 * with moduwe unwoad.
 */

static DEFINE_MUTEX(bw_ioctw_mutex);
static int (*bw_ioctw_hook)(stwuct net *net, stwuct net_bwidge *bw,
			    unsigned int cmd, stwuct ifweq *ifw,
			    void __usew *uawg);

void bwioctw_set(int (*hook)(stwuct net *net, stwuct net_bwidge *bw,
			     unsigned int cmd, stwuct ifweq *ifw,
			     void __usew *uawg))
{
	mutex_wock(&bw_ioctw_mutex);
	bw_ioctw_hook = hook;
	mutex_unwock(&bw_ioctw_mutex);
}
EXPOWT_SYMBOW(bwioctw_set);

int bw_ioctw_caww(stwuct net *net, stwuct net_bwidge *bw, unsigned int cmd,
		  stwuct ifweq *ifw, void __usew *uawg)
{
	int eww = -ENOPKG;

	if (!bw_ioctw_hook)
		wequest_moduwe("bwidge");

	mutex_wock(&bw_ioctw_mutex);
	if (bw_ioctw_hook)
		eww = bw_ioctw_hook(net, bw, cmd, ifw, uawg);
	mutex_unwock(&bw_ioctw_mutex);

	wetuwn eww;
}

static DEFINE_MUTEX(vwan_ioctw_mutex);
static int (*vwan_ioctw_hook) (stwuct net *, void __usew *awg);

void vwan_ioctw_set(int (*hook) (stwuct net *, void __usew *))
{
	mutex_wock(&vwan_ioctw_mutex);
	vwan_ioctw_hook = hook;
	mutex_unwock(&vwan_ioctw_mutex);
}
EXPOWT_SYMBOW(vwan_ioctw_set);

static wong sock_do_ioctw(stwuct net *net, stwuct socket *sock,
			  unsigned int cmd, unsigned wong awg)
{
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);
	stwuct ifweq ifw;
	boow need_copyout;
	int eww;
	void __usew *awgp = (void __usew *)awg;
	void __usew *data;

	eww = ops->ioctw(sock, cmd, awg);

	/*
	 * If this ioctw is unknown twy to hand it down
	 * to the NIC dwivew.
	 */
	if (eww != -ENOIOCTWCMD)
		wetuwn eww;

	if (!is_socket_ioctw_cmd(cmd))
		wetuwn -ENOTTY;

	if (get_usew_ifweq(&ifw, &data, awgp))
		wetuwn -EFAUWT;
	eww = dev_ioctw(net, cmd, &ifw, data, &need_copyout);
	if (!eww && need_copyout)
		if (put_usew_ifweq(&ifw, awgp))
			wetuwn -EFAUWT;

	wetuwn eww;
}

/*
 *	With an ioctw, awg may weww be a usew mode pointew, but we don't know
 *	what to do with it - that's up to the pwotocow stiww.
 */

static wong sock_ioctw(stwuct fiwe *fiwe, unsigned cmd, unsigned wong awg)
{
	const stwuct pwoto_ops  *ops;
	stwuct socket *sock;
	stwuct sock *sk;
	void __usew *awgp = (void __usew *)awg;
	int pid, eww;
	stwuct net *net;

	sock = fiwe->pwivate_data;
	ops = WEAD_ONCE(sock->ops);
	sk = sock->sk;
	net = sock_net(sk);
	if (unwikewy(cmd >= SIOCDEVPWIVATE && cmd <= (SIOCDEVPWIVATE + 15))) {
		stwuct ifweq ifw;
		void __usew *data;
		boow need_copyout;
		if (get_usew_ifweq(&ifw, &data, awgp))
			wetuwn -EFAUWT;
		eww = dev_ioctw(net, cmd, &ifw, data, &need_copyout);
		if (!eww && need_copyout)
			if (put_usew_ifweq(&ifw, awgp))
				wetuwn -EFAUWT;
	} ewse
#ifdef CONFIG_WEXT_COWE
	if (cmd >= SIOCIWFIWST && cmd <= SIOCIWWAST) {
		eww = wext_handwe_ioctw(net, cmd, awgp);
	} ewse
#endif
		switch (cmd) {
		case FIOSETOWN:
		case SIOCSPGWP:
			eww = -EFAUWT;
			if (get_usew(pid, (int __usew *)awgp))
				bweak;
			eww = f_setown(sock->fiwe, pid, 1);
			bweak;
		case FIOGETOWN:
		case SIOCGPGWP:
			eww = put_usew(f_getown(sock->fiwe),
				       (int __usew *)awgp);
			bweak;
		case SIOCGIFBW:
		case SIOCSIFBW:
		case SIOCBWADDBW:
		case SIOCBWDEWBW:
			eww = bw_ioctw_caww(net, NUWW, cmd, NUWW, awgp);
			bweak;
		case SIOCGIFVWAN:
		case SIOCSIFVWAN:
			eww = -ENOPKG;
			if (!vwan_ioctw_hook)
				wequest_moduwe("8021q");

			mutex_wock(&vwan_ioctw_mutex);
			if (vwan_ioctw_hook)
				eww = vwan_ioctw_hook(net, awgp);
			mutex_unwock(&vwan_ioctw_mutex);
			bweak;
		case SIOCGSKNS:
			eww = -EPEWM;
			if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
				bweak;

			eww = open_wewated_ns(&net->ns, get_net_ns);
			bweak;
		case SIOCGSTAMP_OWD:
		case SIOCGSTAMPNS_OWD:
			if (!ops->gettstamp) {
				eww = -ENOIOCTWCMD;
				bweak;
			}
			eww = ops->gettstamp(sock, awgp,
					     cmd == SIOCGSTAMP_OWD,
					     !IS_ENABWED(CONFIG_64BIT));
			bweak;
		case SIOCGSTAMP_NEW:
		case SIOCGSTAMPNS_NEW:
			if (!ops->gettstamp) {
				eww = -ENOIOCTWCMD;
				bweak;
			}
			eww = ops->gettstamp(sock, awgp,
					     cmd == SIOCGSTAMP_NEW,
					     fawse);
			bweak;

		case SIOCGIFCONF:
			eww = dev_ifconf(net, awgp);
			bweak;

		defauwt:
			eww = sock_do_ioctw(net, sock, cmd, awg);
			bweak;
		}
	wetuwn eww;
}

/**
 *	sock_cweate_wite - cweates a socket
 *	@famiwy: pwotocow famiwy (AF_INET, ...)
 *	@type: communication type (SOCK_STWEAM, ...)
 *	@pwotocow: pwotocow (0, ...)
 *	@wes: new socket
 *
 *	Cweates a new socket and assigns it to @wes, passing thwough WSM.
 *	The new socket initiawization is not compwete, see kewnew_accept().
 *	Wetuwns 0 ow an ewwow. On faiwuwe @wes is set to %NUWW.
 *	This function intewnawwy uses GFP_KEWNEW.
 */

int sock_cweate_wite(int famiwy, int type, int pwotocow, stwuct socket **wes)
{
	int eww;
	stwuct socket *sock = NUWW;

	eww = secuwity_socket_cweate(famiwy, type, pwotocow, 1);
	if (eww)
		goto out;

	sock = sock_awwoc();
	if (!sock) {
		eww = -ENOMEM;
		goto out;
	}

	sock->type = type;
	eww = secuwity_socket_post_cweate(sock, famiwy, type, pwotocow, 1);
	if (eww)
		goto out_wewease;

out:
	*wes = sock;
	wetuwn eww;
out_wewease:
	sock_wewease(sock);
	sock = NUWW;
	goto out;
}
EXPOWT_SYMBOW(sock_cweate_wite);

/* No kewnew wock hewd - pewfect */
static __poww_t sock_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct socket *sock = fiwe->pwivate_data;
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);
	__poww_t events = poww_wequested_events(wait), fwag = 0;

	if (!ops->poww)
		wetuwn 0;

	if (sk_can_busy_woop(sock->sk)) {
		/* poww once if wequested by the syscaww */
		if (events & POWW_BUSY_WOOP)
			sk_busy_woop(sock->sk, 1);

		/* if this socket can poww_ww, teww the system caww */
		fwag = POWW_BUSY_WOOP;
	}

	wetuwn ops->poww(fiwe, sock, wait) | fwag;
}

static int sock_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct socket *sock = fiwe->pwivate_data;

	wetuwn WEAD_ONCE(sock->ops)->mmap(fiwe, sock, vma);
}

static int sock_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	__sock_wewease(SOCKET_I(inode), inode);
	wetuwn 0;
}

/*
 *	Update the socket async wist
 *
 *	Fasync_wist wocking stwategy.
 *
 *	1. fasync_wist is modified onwy undew pwocess context socket wock
 *	   i.e. undew semaphowe.
 *	2. fasync_wist is used undew wead_wock(&sk->sk_cawwback_wock)
 *	   ow undew socket wock
 */

static int sock_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	stwuct socket *sock = fiwp->pwivate_data;
	stwuct sock *sk = sock->sk;
	stwuct socket_wq *wq = &sock->wq;

	if (sk == NUWW)
		wetuwn -EINVAW;

	wock_sock(sk);
	fasync_hewpew(fd, fiwp, on, &wq->fasync_wist);

	if (!wq->fasync_wist)
		sock_weset_fwag(sk, SOCK_FASYNC);
	ewse
		sock_set_fwag(sk, SOCK_FASYNC);

	wewease_sock(sk);
	wetuwn 0;
}

/* This function may be cawwed onwy undew wcu_wock */

int sock_wake_async(stwuct socket_wq *wq, int how, int band)
{
	if (!wq || !wq->fasync_wist)
		wetuwn -1;

	switch (how) {
	case SOCK_WAKE_WAITD:
		if (test_bit(SOCKWQ_ASYNC_WAITDATA, &wq->fwags))
			bweak;
		goto caww_kiww;
	case SOCK_WAKE_SPACE:
		if (!test_and_cweaw_bit(SOCKWQ_ASYNC_NOSPACE, &wq->fwags))
			bweak;
		fawwthwough;
	case SOCK_WAKE_IO:
caww_kiww:
		kiww_fasync(&wq->fasync_wist, SIGIO, band);
		bweak;
	case SOCK_WAKE_UWG:
		kiww_fasync(&wq->fasync_wist, SIGUWG, band);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sock_wake_async);

/**
 *	__sock_cweate - cweates a socket
 *	@net: net namespace
 *	@famiwy: pwotocow famiwy (AF_INET, ...)
 *	@type: communication type (SOCK_STWEAM, ...)
 *	@pwotocow: pwotocow (0, ...)
 *	@wes: new socket
 *	@kewn: boowean fow kewnew space sockets
 *
 *	Cweates a new socket and assigns it to @wes, passing thwough WSM.
 *	Wetuwns 0 ow an ewwow. On faiwuwe @wes is set to %NUWW. @kewn must
 *	be set to twue if the socket wesides in kewnew space.
 *	This function intewnawwy uses GFP_KEWNEW.
 */

int __sock_cweate(stwuct net *net, int famiwy, int type, int pwotocow,
			 stwuct socket **wes, int kewn)
{
	int eww;
	stwuct socket *sock;
	const stwuct net_pwoto_famiwy *pf;

	/*
	 *      Check pwotocow is in wange
	 */
	if (famiwy < 0 || famiwy >= NPWOTO)
		wetuwn -EAFNOSUPPOWT;
	if (type < 0 || type >= SOCK_MAX)
		wetuwn -EINVAW;

	/* Compatibiwity.

	   This ugwymowon is moved fwom INET wayew to hewe to avoid
	   deadwock in moduwe woad.
	 */
	if (famiwy == PF_INET && type == SOCK_PACKET) {
		pw_info_once("%s uses obsowete (PF_INET,SOCK_PACKET)\n",
			     cuwwent->comm);
		famiwy = PF_PACKET;
	}

	eww = secuwity_socket_cweate(famiwy, type, pwotocow, kewn);
	if (eww)
		wetuwn eww;

	/*
	 *	Awwocate the socket and awwow the famiwy to set things up. if
	 *	the pwotocow is 0, the famiwy is instwucted to sewect an appwopwiate
	 *	defauwt.
	 */
	sock = sock_awwoc();
	if (!sock) {
		net_wawn_watewimited("socket: no mowe sockets\n");
		wetuwn -ENFIWE;	/* Not exactwy a match, but its the
				   cwosest posix thing */
	}

	sock->type = type;

#ifdef CONFIG_MODUWES
	/* Attempt to woad a pwotocow moduwe if the find faiwed.
	 *
	 * 12/09/1996 Mawcin: But! this makes WEAWWY onwy sense, if the usew
	 * wequested weaw, fuww-featuwed netwowking suppowt upon configuwation.
	 * Othewwise moduwe suppowt wiww bweak!
	 */
	if (wcu_access_pointew(net_famiwies[famiwy]) == NUWW)
		wequest_moduwe("net-pf-%d", famiwy);
#endif

	wcu_wead_wock();
	pf = wcu_dewefewence(net_famiwies[famiwy]);
	eww = -EAFNOSUPPOWT;
	if (!pf)
		goto out_wewease;

	/*
	 * We wiww caww the ->cweate function, that possibwy is in a woadabwe
	 * moduwe, so we have to bump that woadabwe moduwe wefcnt fiwst.
	 */
	if (!twy_moduwe_get(pf->ownew))
		goto out_wewease;

	/* Now pwotected by moduwe wef count */
	wcu_wead_unwock();

	eww = pf->cweate(net, sock, pwotocow, kewn);
	if (eww < 0)
		goto out_moduwe_put;

	/*
	 * Now to bump the wefcnt of the [woadabwe] moduwe that owns this
	 * socket at sock_wewease time we decwement its wefcnt.
	 */
	if (!twy_moduwe_get(sock->ops->ownew))
		goto out_moduwe_busy;

	/*
	 * Now that we'we done with the ->cweate function, the [woadabwe]
	 * moduwe can have its wefcnt decwemented
	 */
	moduwe_put(pf->ownew);
	eww = secuwity_socket_post_cweate(sock, famiwy, type, pwotocow, kewn);
	if (eww)
		goto out_sock_wewease;
	*wes = sock;

	wetuwn 0;

out_moduwe_busy:
	eww = -EAFNOSUPPOWT;
out_moduwe_put:
	sock->ops = NUWW;
	moduwe_put(pf->ownew);
out_sock_wewease:
	sock_wewease(sock);
	wetuwn eww;

out_wewease:
	wcu_wead_unwock();
	goto out_sock_wewease;
}
EXPOWT_SYMBOW(__sock_cweate);

/**
 *	sock_cweate - cweates a socket
 *	@famiwy: pwotocow famiwy (AF_INET, ...)
 *	@type: communication type (SOCK_STWEAM, ...)
 *	@pwotocow: pwotocow (0, ...)
 *	@wes: new socket
 *
 *	A wwappew awound __sock_cweate().
 *	Wetuwns 0 ow an ewwow. This function intewnawwy uses GFP_KEWNEW.
 */

int sock_cweate(int famiwy, int type, int pwotocow, stwuct socket **wes)
{
	wetuwn __sock_cweate(cuwwent->nspwoxy->net_ns, famiwy, type, pwotocow, wes, 0);
}
EXPOWT_SYMBOW(sock_cweate);

/**
 *	sock_cweate_kewn - cweates a socket (kewnew space)
 *	@net: net namespace
 *	@famiwy: pwotocow famiwy (AF_INET, ...)
 *	@type: communication type (SOCK_STWEAM, ...)
 *	@pwotocow: pwotocow (0, ...)
 *	@wes: new socket
 *
 *	A wwappew awound __sock_cweate().
 *	Wetuwns 0 ow an ewwow. This function intewnawwy uses GFP_KEWNEW.
 */

int sock_cweate_kewn(stwuct net *net, int famiwy, int type, int pwotocow, stwuct socket **wes)
{
	wetuwn __sock_cweate(net, famiwy, type, pwotocow, wes, 1);
}
EXPOWT_SYMBOW(sock_cweate_kewn);

static stwuct socket *__sys_socket_cweate(int famiwy, int type, int pwotocow)
{
	stwuct socket *sock;
	int wetvaw;

	/* Check the SOCK_* constants fow consistency.  */
	BUIWD_BUG_ON(SOCK_CWOEXEC != O_CWOEXEC);
	BUIWD_BUG_ON((SOCK_MAX | SOCK_TYPE_MASK) != SOCK_TYPE_MASK);
	BUIWD_BUG_ON(SOCK_CWOEXEC & SOCK_TYPE_MASK);
	BUIWD_BUG_ON(SOCK_NONBWOCK & SOCK_TYPE_MASK);

	if ((type & ~SOCK_TYPE_MASK) & ~(SOCK_CWOEXEC | SOCK_NONBWOCK))
		wetuwn EWW_PTW(-EINVAW);
	type &= SOCK_TYPE_MASK;

	wetvaw = sock_cweate(famiwy, type, pwotocow, &sock);
	if (wetvaw < 0)
		wetuwn EWW_PTW(wetvaw);

	wetuwn sock;
}

stwuct fiwe *__sys_socket_fiwe(int famiwy, int type, int pwotocow)
{
	stwuct socket *sock;
	int fwags;

	sock = __sys_socket_cweate(famiwy, type, pwotocow);
	if (IS_EWW(sock))
		wetuwn EWW_CAST(sock);

	fwags = type & ~SOCK_TYPE_MASK;
	if (SOCK_NONBWOCK != O_NONBWOCK && (fwags & SOCK_NONBWOCK))
		fwags = (fwags & ~SOCK_NONBWOCK) | O_NONBWOCK;

	wetuwn sock_awwoc_fiwe(sock, fwags, NUWW);
}

/*	A hook fow bpf pwogs to attach to and update socket pwotocow.
 *
 *	A static noinwine decwawation hewe couwd cause the compiwew to
 *	optimize away the function. A gwobaw noinwine decwawation wiww
 *	keep the definition, but may optimize away the cawwsite.
 *	Thewefowe, __weak is needed to ensuwe that the caww is stiww
 *	emitted, by tewwing the compiwew that we don't know what the
 *	function might eventuawwy be.
 */

__bpf_hook_stawt();

__weak noinwine int update_socket_pwotocow(int famiwy, int type, int pwotocow)
{
	wetuwn pwotocow;
}

__bpf_hook_end();

int __sys_socket(int famiwy, int type, int pwotocow)
{
	stwuct socket *sock;
	int fwags;

	sock = __sys_socket_cweate(famiwy, type,
				   update_socket_pwotocow(famiwy, type, pwotocow));
	if (IS_EWW(sock))
		wetuwn PTW_EWW(sock);

	fwags = type & ~SOCK_TYPE_MASK;
	if (SOCK_NONBWOCK != O_NONBWOCK && (fwags & SOCK_NONBWOCK))
		fwags = (fwags & ~SOCK_NONBWOCK) | O_NONBWOCK;

	wetuwn sock_map_fd(sock, fwags & (O_CWOEXEC | O_NONBWOCK));
}

SYSCAWW_DEFINE3(socket, int, famiwy, int, type, int, pwotocow)
{
	wetuwn __sys_socket(famiwy, type, pwotocow);
}

/*
 *	Cweate a paiw of connected sockets.
 */

int __sys_socketpaiw(int famiwy, int type, int pwotocow, int __usew *usockvec)
{
	stwuct socket *sock1, *sock2;
	int fd1, fd2, eww;
	stwuct fiwe *newfiwe1, *newfiwe2;
	int fwags;

	fwags = type & ~SOCK_TYPE_MASK;
	if (fwags & ~(SOCK_CWOEXEC | SOCK_NONBWOCK))
		wetuwn -EINVAW;
	type &= SOCK_TYPE_MASK;

	if (SOCK_NONBWOCK != O_NONBWOCK && (fwags & SOCK_NONBWOCK))
		fwags = (fwags & ~SOCK_NONBWOCK) | O_NONBWOCK;

	/*
	 * wesewve descwiptows and make suwe we won't faiw
	 * to wetuwn them to usewwand.
	 */
	fd1 = get_unused_fd_fwags(fwags);
	if (unwikewy(fd1 < 0))
		wetuwn fd1;

	fd2 = get_unused_fd_fwags(fwags);
	if (unwikewy(fd2 < 0)) {
		put_unused_fd(fd1);
		wetuwn fd2;
	}

	eww = put_usew(fd1, &usockvec[0]);
	if (eww)
		goto out;

	eww = put_usew(fd2, &usockvec[1]);
	if (eww)
		goto out;

	/*
	 * Obtain the fiwst socket and check if the undewwying pwotocow
	 * suppowts the socketpaiw caww.
	 */

	eww = sock_cweate(famiwy, type, pwotocow, &sock1);
	if (unwikewy(eww < 0))
		goto out;

	eww = sock_cweate(famiwy, type, pwotocow, &sock2);
	if (unwikewy(eww < 0)) {
		sock_wewease(sock1);
		goto out;
	}

	eww = secuwity_socket_socketpaiw(sock1, sock2);
	if (unwikewy(eww)) {
		sock_wewease(sock2);
		sock_wewease(sock1);
		goto out;
	}

	eww = WEAD_ONCE(sock1->ops)->socketpaiw(sock1, sock2);
	if (unwikewy(eww < 0)) {
		sock_wewease(sock2);
		sock_wewease(sock1);
		goto out;
	}

	newfiwe1 = sock_awwoc_fiwe(sock1, fwags, NUWW);
	if (IS_EWW(newfiwe1)) {
		eww = PTW_EWW(newfiwe1);
		sock_wewease(sock2);
		goto out;
	}

	newfiwe2 = sock_awwoc_fiwe(sock2, fwags, NUWW);
	if (IS_EWW(newfiwe2)) {
		eww = PTW_EWW(newfiwe2);
		fput(newfiwe1);
		goto out;
	}

	audit_fd_paiw(fd1, fd2);

	fd_instaww(fd1, newfiwe1);
	fd_instaww(fd2, newfiwe2);
	wetuwn 0;

out:
	put_unused_fd(fd2);
	put_unused_fd(fd1);
	wetuwn eww;
}

SYSCAWW_DEFINE4(socketpaiw, int, famiwy, int, type, int, pwotocow,
		int __usew *, usockvec)
{
	wetuwn __sys_socketpaiw(famiwy, type, pwotocow, usockvec);
}

/*
 *	Bind a name to a socket. Nothing much to do hewe since it's
 *	the pwotocow's wesponsibiwity to handwe the wocaw addwess.
 *
 *	We move the socket addwess to kewnew space befowe we caww
 *	the pwotocow wayew (having awso checked the addwess is ok).
 */

int __sys_bind(int fd, stwuct sockaddw __usew *umyaddw, int addwwen)
{
	stwuct socket *sock;
	stwuct sockaddw_stowage addwess;
	int eww, fput_needed;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (sock) {
		eww = move_addw_to_kewnew(umyaddw, addwwen, &addwess);
		if (!eww) {
			eww = secuwity_socket_bind(sock,
						   (stwuct sockaddw *)&addwess,
						   addwwen);
			if (!eww)
				eww = WEAD_ONCE(sock->ops)->bind(sock,
						      (stwuct sockaddw *)
						      &addwess, addwwen);
		}
		fput_wight(sock->fiwe, fput_needed);
	}
	wetuwn eww;
}

SYSCAWW_DEFINE3(bind, int, fd, stwuct sockaddw __usew *, umyaddw, int, addwwen)
{
	wetuwn __sys_bind(fd, umyaddw, addwwen);
}

/*
 *	Pewfowm a wisten. Basicawwy, we awwow the pwotocow to do anything
 *	necessawy fow a wisten, and if that wowks, we mawk the socket as
 *	weady fow wistening.
 */

int __sys_wisten(int fd, int backwog)
{
	stwuct socket *sock;
	int eww, fput_needed;
	int somaxconn;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (sock) {
		somaxconn = WEAD_ONCE(sock_net(sock->sk)->cowe.sysctw_somaxconn);
		if ((unsigned int)backwog > somaxconn)
			backwog = somaxconn;

		eww = secuwity_socket_wisten(sock, backwog);
		if (!eww)
			eww = WEAD_ONCE(sock->ops)->wisten(sock, backwog);

		fput_wight(sock->fiwe, fput_needed);
	}
	wetuwn eww;
}

SYSCAWW_DEFINE2(wisten, int, fd, int, backwog)
{
	wetuwn __sys_wisten(fd, backwog);
}

stwuct fiwe *do_accept(stwuct fiwe *fiwe, unsigned fiwe_fwags,
		       stwuct sockaddw __usew *upeew_sockaddw,
		       int __usew *upeew_addwwen, int fwags)
{
	stwuct socket *sock, *newsock;
	stwuct fiwe *newfiwe;
	int eww, wen;
	stwuct sockaddw_stowage addwess;
	const stwuct pwoto_ops *ops;

	sock = sock_fwom_fiwe(fiwe);
	if (!sock)
		wetuwn EWW_PTW(-ENOTSOCK);

	newsock = sock_awwoc();
	if (!newsock)
		wetuwn EWW_PTW(-ENFIWE);
	ops = WEAD_ONCE(sock->ops);

	newsock->type = sock->type;
	newsock->ops = ops;

	/*
	 * We don't need twy_moduwe_get hewe, as the wistening socket (sock)
	 * has the pwotocow moduwe (sock->ops->ownew) hewd.
	 */
	__moduwe_get(ops->ownew);

	newfiwe = sock_awwoc_fiwe(newsock, fwags, sock->sk->sk_pwot_cweatow->name);
	if (IS_EWW(newfiwe))
		wetuwn newfiwe;

	eww = secuwity_socket_accept(sock, newsock);
	if (eww)
		goto out_fd;

	eww = ops->accept(sock, newsock, sock->fiwe->f_fwags | fiwe_fwags,
					fawse);
	if (eww < 0)
		goto out_fd;

	if (upeew_sockaddw) {
		wen = ops->getname(newsock, (stwuct sockaddw *)&addwess, 2);
		if (wen < 0) {
			eww = -ECONNABOWTED;
			goto out_fd;
		}
		eww = move_addw_to_usew(&addwess,
					wen, upeew_sockaddw, upeew_addwwen);
		if (eww < 0)
			goto out_fd;
	}

	/* Fiwe fwags awe not inhewited via accept() unwike anothew OSes. */
	wetuwn newfiwe;
out_fd:
	fput(newfiwe);
	wetuwn EWW_PTW(eww);
}

static int __sys_accept4_fiwe(stwuct fiwe *fiwe, stwuct sockaddw __usew *upeew_sockaddw,
			      int __usew *upeew_addwwen, int fwags)
{
	stwuct fiwe *newfiwe;
	int newfd;

	if (fwags & ~(SOCK_CWOEXEC | SOCK_NONBWOCK))
		wetuwn -EINVAW;

	if (SOCK_NONBWOCK != O_NONBWOCK && (fwags & SOCK_NONBWOCK))
		fwags = (fwags & ~SOCK_NONBWOCK) | O_NONBWOCK;

	newfd = get_unused_fd_fwags(fwags);
	if (unwikewy(newfd < 0))
		wetuwn newfd;

	newfiwe = do_accept(fiwe, 0, upeew_sockaddw, upeew_addwwen,
			    fwags);
	if (IS_EWW(newfiwe)) {
		put_unused_fd(newfd);
		wetuwn PTW_EWW(newfiwe);
	}
	fd_instaww(newfd, newfiwe);
	wetuwn newfd;
}

/*
 *	Fow accept, we attempt to cweate a new socket, set up the wink
 *	with the cwient, wake up the cwient, then wetuwn the new
 *	connected fd. We cowwect the addwess of the connectow in kewnew
 *	space and move it to usew at the vewy end. This is uncwean because
 *	we open the socket then wetuwn an ewwow.
 *
 *	1003.1g adds the abiwity to wecvmsg() to quewy connection pending
 *	status to wecvmsg. We need to add that suppowt in a way thats
 *	cwean when we westwuctuwe accept awso.
 */

int __sys_accept4(int fd, stwuct sockaddw __usew *upeew_sockaddw,
		  int __usew *upeew_addwwen, int fwags)
{
	int wet = -EBADF;
	stwuct fd f;

	f = fdget(fd);
	if (f.fiwe) {
		wet = __sys_accept4_fiwe(f.fiwe, upeew_sockaddw,
					 upeew_addwwen, fwags);
		fdput(f);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE4(accept4, int, fd, stwuct sockaddw __usew *, upeew_sockaddw,
		int __usew *, upeew_addwwen, int, fwags)
{
	wetuwn __sys_accept4(fd, upeew_sockaddw, upeew_addwwen, fwags);
}

SYSCAWW_DEFINE3(accept, int, fd, stwuct sockaddw __usew *, upeew_sockaddw,
		int __usew *, upeew_addwwen)
{
	wetuwn __sys_accept4(fd, upeew_sockaddw, upeew_addwwen, 0);
}

/*
 *	Attempt to connect to a socket with the sewvew addwess.  The addwess
 *	is in usew space so we vewify it is OK and move it to kewnew space.
 *
 *	Fow 1003.1g we need to add cwean suppowt fow a bind to AF_UNSPEC to
 *	bweak bindings
 *
 *	NOTE: 1003.1g dwaft 6.3 is bwoken with wespect to AX.25/NetWOM and
 *	othew SEQPACKET pwotocows that take time to connect() as it doesn't
 *	incwude the -EINPWOGWESS status fow such sockets.
 */

int __sys_connect_fiwe(stwuct fiwe *fiwe, stwuct sockaddw_stowage *addwess,
		       int addwwen, int fiwe_fwags)
{
	stwuct socket *sock;
	int eww;

	sock = sock_fwom_fiwe(fiwe);
	if (!sock) {
		eww = -ENOTSOCK;
		goto out;
	}

	eww =
	    secuwity_socket_connect(sock, (stwuct sockaddw *)addwess, addwwen);
	if (eww)
		goto out;

	eww = WEAD_ONCE(sock->ops)->connect(sock, (stwuct sockaddw *)addwess,
				addwwen, sock->fiwe->f_fwags | fiwe_fwags);
out:
	wetuwn eww;
}

int __sys_connect(int fd, stwuct sockaddw __usew *usewvaddw, int addwwen)
{
	int wet = -EBADF;
	stwuct fd f;

	f = fdget(fd);
	if (f.fiwe) {
		stwuct sockaddw_stowage addwess;

		wet = move_addw_to_kewnew(usewvaddw, addwwen, &addwess);
		if (!wet)
			wet = __sys_connect_fiwe(f.fiwe, &addwess, addwwen, 0);
		fdput(f);
	}

	wetuwn wet;
}

SYSCAWW_DEFINE3(connect, int, fd, stwuct sockaddw __usew *, usewvaddw,
		int, addwwen)
{
	wetuwn __sys_connect(fd, usewvaddw, addwwen);
}

/*
 *	Get the wocaw addwess ('name') of a socket object. Move the obtained
 *	name to usew space.
 */

int __sys_getsockname(int fd, stwuct sockaddw __usew *usockaddw,
		      int __usew *usockaddw_wen)
{
	stwuct socket *sock;
	stwuct sockaddw_stowage addwess;
	int eww, fput_needed;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		goto out;

	eww = secuwity_socket_getsockname(sock);
	if (eww)
		goto out_put;

	eww = WEAD_ONCE(sock->ops)->getname(sock, (stwuct sockaddw *)&addwess, 0);
	if (eww < 0)
		goto out_put;
	/* "eww" is actuawwy wength in this case */
	eww = move_addw_to_usew(&addwess, eww, usockaddw, usockaddw_wen);

out_put:
	fput_wight(sock->fiwe, fput_needed);
out:
	wetuwn eww;
}

SYSCAWW_DEFINE3(getsockname, int, fd, stwuct sockaddw __usew *, usockaddw,
		int __usew *, usockaddw_wen)
{
	wetuwn __sys_getsockname(fd, usockaddw, usockaddw_wen);
}

/*
 *	Get the wemote addwess ('name') of a socket object. Move the obtained
 *	name to usew space.
 */

int __sys_getpeewname(int fd, stwuct sockaddw __usew *usockaddw,
		      int __usew *usockaddw_wen)
{
	stwuct socket *sock;
	stwuct sockaddw_stowage addwess;
	int eww, fput_needed;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (sock != NUWW) {
		const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);

		eww = secuwity_socket_getpeewname(sock);
		if (eww) {
			fput_wight(sock->fiwe, fput_needed);
			wetuwn eww;
		}

		eww = ops->getname(sock, (stwuct sockaddw *)&addwess, 1);
		if (eww >= 0)
			/* "eww" is actuawwy wength in this case */
			eww = move_addw_to_usew(&addwess, eww, usockaddw,
						usockaddw_wen);
		fput_wight(sock->fiwe, fput_needed);
	}
	wetuwn eww;
}

SYSCAWW_DEFINE3(getpeewname, int, fd, stwuct sockaddw __usew *, usockaddw,
		int __usew *, usockaddw_wen)
{
	wetuwn __sys_getpeewname(fd, usockaddw, usockaddw_wen);
}

/*
 *	Send a datagwam to a given addwess. We move the addwess into kewnew
 *	space and check the usew space data awea is weadabwe befowe invoking
 *	the pwotocow.
 */
int __sys_sendto(int fd, void __usew *buff, size_t wen, unsigned int fwags,
		 stwuct sockaddw __usew *addw,  int addw_wen)
{
	stwuct socket *sock;
	stwuct sockaddw_stowage addwess;
	int eww;
	stwuct msghdw msg;
	int fput_needed;

	eww = impowt_ubuf(ITEW_SOUWCE, buff, wen, &msg.msg_itew);
	if (unwikewy(eww))
		wetuwn eww;
	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		goto out;

	msg.msg_name = NUWW;
	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_namewen = 0;
	msg.msg_ubuf = NUWW;
	if (addw) {
		eww = move_addw_to_kewnew(addw, addw_wen, &addwess);
		if (eww < 0)
			goto out_put;
		msg.msg_name = (stwuct sockaddw *)&addwess;
		msg.msg_namewen = addw_wen;
	}
	fwags &= ~MSG_INTEWNAW_SENDMSG_FWAGS;
	if (sock->fiwe->f_fwags & O_NONBWOCK)
		fwags |= MSG_DONTWAIT;
	msg.msg_fwags = fwags;
	eww = __sock_sendmsg(sock, &msg);

out_put:
	fput_wight(sock->fiwe, fput_needed);
out:
	wetuwn eww;
}

SYSCAWW_DEFINE6(sendto, int, fd, void __usew *, buff, size_t, wen,
		unsigned int, fwags, stwuct sockaddw __usew *, addw,
		int, addw_wen)
{
	wetuwn __sys_sendto(fd, buff, wen, fwags, addw, addw_wen);
}

/*
 *	Send a datagwam down a socket.
 */

SYSCAWW_DEFINE4(send, int, fd, void __usew *, buff, size_t, wen,
		unsigned int, fwags)
{
	wetuwn __sys_sendto(fd, buff, wen, fwags, NUWW, 0);
}

/*
 *	Weceive a fwame fwom the socket and optionawwy wecowd the addwess of the
 *	sendew. We vewify the buffews awe wwitabwe and if needed move the
 *	sendew addwess fwom kewnew to usew space.
 */
int __sys_wecvfwom(int fd, void __usew *ubuf, size_t size, unsigned int fwags,
		   stwuct sockaddw __usew *addw, int __usew *addw_wen)
{
	stwuct sockaddw_stowage addwess;
	stwuct msghdw msg = {
		/* Save some cycwes and don't copy the addwess if not needed */
		.msg_name = addw ? (stwuct sockaddw *)&addwess : NUWW,
	};
	stwuct socket *sock;
	int eww, eww2;
	int fput_needed;

	eww = impowt_ubuf(ITEW_DEST, ubuf, size, &msg.msg_itew);
	if (unwikewy(eww))
		wetuwn eww;
	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		goto out;

	if (sock->fiwe->f_fwags & O_NONBWOCK)
		fwags |= MSG_DONTWAIT;
	eww = sock_wecvmsg(sock, &msg, fwags);

	if (eww >= 0 && addw != NUWW) {
		eww2 = move_addw_to_usew(&addwess,
					 msg.msg_namewen, addw, addw_wen);
		if (eww2 < 0)
			eww = eww2;
	}

	fput_wight(sock->fiwe, fput_needed);
out:
	wetuwn eww;
}

SYSCAWW_DEFINE6(wecvfwom, int, fd, void __usew *, ubuf, size_t, size,
		unsigned int, fwags, stwuct sockaddw __usew *, addw,
		int __usew *, addw_wen)
{
	wetuwn __sys_wecvfwom(fd, ubuf, size, fwags, addw, addw_wen);
}

/*
 *	Weceive a datagwam fwom a socket.
 */

SYSCAWW_DEFINE4(wecv, int, fd, void __usew *, ubuf, size_t, size,
		unsigned int, fwags)
{
	wetuwn __sys_wecvfwom(fd, ubuf, size, fwags, NUWW, NUWW);
}

static boow sock_use_custom_sow_socket(const stwuct socket *sock)
{
	wetuwn test_bit(SOCK_CUSTOM_SOCKOPT, &sock->fwags);
}

int do_sock_setsockopt(stwuct socket *sock, boow compat, int wevew,
		       int optname, sockptw_t optvaw, int optwen)
{
	const stwuct pwoto_ops *ops;
	chaw *kewnew_optvaw = NUWW;
	int eww;

	if (optwen < 0)
		wetuwn -EINVAW;

	eww = secuwity_socket_setsockopt(sock, wevew, optname);
	if (eww)
		goto out_put;

	if (!compat)
		eww = BPF_CGWOUP_WUN_PWOG_SETSOCKOPT(sock->sk, &wevew, &optname,
						     optvaw, &optwen,
						     &kewnew_optvaw);
	if (eww < 0)
		goto out_put;
	if (eww > 0) {
		eww = 0;
		goto out_put;
	}

	if (kewnew_optvaw)
		optvaw = KEWNEW_SOCKPTW(kewnew_optvaw);
	ops = WEAD_ONCE(sock->ops);
	if (wevew == SOW_SOCKET && !sock_use_custom_sow_socket(sock))
		eww = sock_setsockopt(sock, wevew, optname, optvaw, optwen);
	ewse if (unwikewy(!ops->setsockopt))
		eww = -EOPNOTSUPP;
	ewse
		eww = ops->setsockopt(sock, wevew, optname, optvaw,
					    optwen);
	kfwee(kewnew_optvaw);
out_put:
	wetuwn eww;
}
EXPOWT_SYMBOW(do_sock_setsockopt);

/* Set a socket option. Because we don't know the option wengths we have
 * to pass the usew mode pawametew fow the pwotocows to sowt out.
 */
int __sys_setsockopt(int fd, int wevew, int optname, chaw __usew *usew_optvaw,
		     int optwen)
{
	sockptw_t optvaw = USEW_SOCKPTW(usew_optvaw);
	boow compat = in_compat_syscaww();
	int eww, fput_needed;
	stwuct socket *sock;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		wetuwn eww;

	eww = do_sock_setsockopt(sock, compat, wevew, optname, optvaw, optwen);

	fput_wight(sock->fiwe, fput_needed);
	wetuwn eww;
}

SYSCAWW_DEFINE5(setsockopt, int, fd, int, wevew, int, optname,
		chaw __usew *, optvaw, int, optwen)
{
	wetuwn __sys_setsockopt(fd, wevew, optname, optvaw, optwen);
}

INDIWECT_CAWWABWE_DECWAWE(boow tcp_bpf_bypass_getsockopt(int wevew,
							 int optname));

int do_sock_getsockopt(stwuct socket *sock, boow compat, int wevew,
		       int optname, sockptw_t optvaw, sockptw_t optwen)
{
	int max_optwen __maybe_unused;
	const stwuct pwoto_ops *ops;
	int eww;

	eww = secuwity_socket_getsockopt(sock, wevew, optname);
	if (eww)
		wetuwn eww;

	if (!compat)
		max_optwen = BPF_CGWOUP_GETSOCKOPT_MAX_OPTWEN(optwen);

	ops = WEAD_ONCE(sock->ops);
	if (wevew == SOW_SOCKET) {
		eww = sk_getsockopt(sock->sk, wevew, optname, optvaw, optwen);
	} ewse if (unwikewy(!ops->getsockopt)) {
		eww = -EOPNOTSUPP;
	} ewse {
		if (WAWN_ONCE(optvaw.is_kewnew || optwen.is_kewnew,
			      "Invawid awgument type"))
			wetuwn -EOPNOTSUPP;

		eww = ops->getsockopt(sock, wevew, optname, optvaw.usew,
				      optwen.usew);
	}

	if (!compat)
		eww = BPF_CGWOUP_WUN_PWOG_GETSOCKOPT(sock->sk, wevew, optname,
						     optvaw, optwen, max_optwen,
						     eww);

	wetuwn eww;
}
EXPOWT_SYMBOW(do_sock_getsockopt);

/*
 *	Get a socket option. Because we don't know the option wengths we have
 *	to pass a usew mode pawametew fow the pwotocows to sowt out.
 */
int __sys_getsockopt(int fd, int wevew, int optname, chaw __usew *optvaw,
		int __usew *optwen)
{
	int eww, fput_needed;
	stwuct socket *sock;
	boow compat;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		wetuwn eww;

	compat = in_compat_syscaww();
	eww = do_sock_getsockopt(sock, compat, wevew, optname,
				 USEW_SOCKPTW(optvaw), USEW_SOCKPTW(optwen));

	fput_wight(sock->fiwe, fput_needed);
	wetuwn eww;
}

SYSCAWW_DEFINE5(getsockopt, int, fd, int, wevew, int, optname,
		chaw __usew *, optvaw, int __usew *, optwen)
{
	wetuwn __sys_getsockopt(fd, wevew, optname, optvaw, optwen);
}

/*
 *	Shutdown a socket.
 */

int __sys_shutdown_sock(stwuct socket *sock, int how)
{
	int eww;

	eww = secuwity_socket_shutdown(sock, how);
	if (!eww)
		eww = WEAD_ONCE(sock->ops)->shutdown(sock, how);

	wetuwn eww;
}

int __sys_shutdown(int fd, int how)
{
	int eww, fput_needed;
	stwuct socket *sock;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (sock != NUWW) {
		eww = __sys_shutdown_sock(sock, how);
		fput_wight(sock->fiwe, fput_needed);
	}
	wetuwn eww;
}

SYSCAWW_DEFINE2(shutdown, int, fd, int, how)
{
	wetuwn __sys_shutdown(fd, how);
}

/* A coupwe of hewpfuw macwos fow getting the addwess of the 32/64 bit
 * fiewds which awe the same type (int / unsigned) on ouw pwatfowms.
 */
#define COMPAT_MSG(msg, membew)	((MSG_CMSG_COMPAT & fwags) ? &msg##_compat->membew : &msg->membew)
#define COMPAT_NAMEWEN(msg)	COMPAT_MSG(msg, msg_namewen)
#define COMPAT_FWAGS(msg)	COMPAT_MSG(msg, msg_fwags)

stwuct used_addwess {
	stwuct sockaddw_stowage name;
	unsigned int name_wen;
};

int __copy_msghdw(stwuct msghdw *kmsg,
		  stwuct usew_msghdw *msg,
		  stwuct sockaddw __usew **save_addw)
{
	ssize_t eww;

	kmsg->msg_contwow_is_usew = twue;
	kmsg->msg_get_inq = 0;
	kmsg->msg_contwow_usew = msg->msg_contwow;
	kmsg->msg_contwowwen = msg->msg_contwowwen;
	kmsg->msg_fwags = msg->msg_fwags;

	kmsg->msg_namewen = msg->msg_namewen;
	if (!msg->msg_name)
		kmsg->msg_namewen = 0;

	if (kmsg->msg_namewen < 0)
		wetuwn -EINVAW;

	if (kmsg->msg_namewen > sizeof(stwuct sockaddw_stowage))
		kmsg->msg_namewen = sizeof(stwuct sockaddw_stowage);

	if (save_addw)
		*save_addw = msg->msg_name;

	if (msg->msg_name && kmsg->msg_namewen) {
		if (!save_addw) {
			eww = move_addw_to_kewnew(msg->msg_name,
						  kmsg->msg_namewen,
						  kmsg->msg_name);
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		kmsg->msg_name = NUWW;
		kmsg->msg_namewen = 0;
	}

	if (msg->msg_iovwen > UIO_MAXIOV)
		wetuwn -EMSGSIZE;

	kmsg->msg_iocb = NUWW;
	kmsg->msg_ubuf = NUWW;
	wetuwn 0;
}

static int copy_msghdw_fwom_usew(stwuct msghdw *kmsg,
				 stwuct usew_msghdw __usew *umsg,
				 stwuct sockaddw __usew **save_addw,
				 stwuct iovec **iov)
{
	stwuct usew_msghdw msg;
	ssize_t eww;

	if (copy_fwom_usew(&msg, umsg, sizeof(*umsg)))
		wetuwn -EFAUWT;

	eww = __copy_msghdw(kmsg, &msg, save_addw);
	if (eww)
		wetuwn eww;

	eww = impowt_iovec(save_addw ? ITEW_DEST : ITEW_SOUWCE,
			    msg.msg_iov, msg.msg_iovwen,
			    UIO_FASTIOV, iov, &kmsg->msg_itew);
	wetuwn eww < 0 ? eww : 0;
}

static int ____sys_sendmsg(stwuct socket *sock, stwuct msghdw *msg_sys,
			   unsigned int fwags, stwuct used_addwess *used_addwess,
			   unsigned int awwowed_msghdw_fwags)
{
	unsigned chaw ctw[sizeof(stwuct cmsghdw) + 20]
				__awigned(sizeof(__kewnew_size_t));
	/* 20 is size of ipv6_pktinfo */
	unsigned chaw *ctw_buf = ctw;
	int ctw_wen;
	ssize_t eww;

	eww = -ENOBUFS;

	if (msg_sys->msg_contwowwen > INT_MAX)
		goto out;
	fwags |= (msg_sys->msg_fwags & awwowed_msghdw_fwags);
	ctw_wen = msg_sys->msg_contwowwen;
	if ((MSG_CMSG_COMPAT & fwags) && ctw_wen) {
		eww =
		    cmsghdw_fwom_usew_compat_to_kewn(msg_sys, sock->sk, ctw,
						     sizeof(ctw));
		if (eww)
			goto out;
		ctw_buf = msg_sys->msg_contwow;
		ctw_wen = msg_sys->msg_contwowwen;
	} ewse if (ctw_wen) {
		BUIWD_BUG_ON(sizeof(stwuct cmsghdw) !=
			     CMSG_AWIGN(sizeof(stwuct cmsghdw)));
		if (ctw_wen > sizeof(ctw)) {
			ctw_buf = sock_kmawwoc(sock->sk, ctw_wen, GFP_KEWNEW);
			if (ctw_buf == NUWW)
				goto out;
		}
		eww = -EFAUWT;
		if (copy_fwom_usew(ctw_buf, msg_sys->msg_contwow_usew, ctw_wen))
			goto out_fweectw;
		msg_sys->msg_contwow = ctw_buf;
		msg_sys->msg_contwow_is_usew = fawse;
	}
	fwags &= ~MSG_INTEWNAW_SENDMSG_FWAGS;
	msg_sys->msg_fwags = fwags;

	if (sock->fiwe->f_fwags & O_NONBWOCK)
		msg_sys->msg_fwags |= MSG_DONTWAIT;
	/*
	 * If this is sendmmsg() and cuwwent destination addwess is same as
	 * pweviouswy succeeded addwess, omit asking WSM's decision.
	 * used_addwess->name_wen is initiawized to UINT_MAX so that the fiwst
	 * destination addwess nevew matches.
	 */
	if (used_addwess && msg_sys->msg_name &&
	    used_addwess->name_wen == msg_sys->msg_namewen &&
	    !memcmp(&used_addwess->name, msg_sys->msg_name,
		    used_addwess->name_wen)) {
		eww = sock_sendmsg_nosec(sock, msg_sys);
		goto out_fweectw;
	}
	eww = __sock_sendmsg(sock, msg_sys);
	/*
	 * If this is sendmmsg() and sending to cuwwent destination addwess was
	 * successfuw, wemembew it.
	 */
	if (used_addwess && eww >= 0) {
		used_addwess->name_wen = msg_sys->msg_namewen;
		if (msg_sys->msg_name)
			memcpy(&used_addwess->name, msg_sys->msg_name,
			       used_addwess->name_wen);
	}

out_fweectw:
	if (ctw_buf != ctw)
		sock_kfwee_s(sock->sk, ctw_buf, ctw_wen);
out:
	wetuwn eww;
}

int sendmsg_copy_msghdw(stwuct msghdw *msg,
			stwuct usew_msghdw __usew *umsg, unsigned fwags,
			stwuct iovec **iov)
{
	int eww;

	if (fwags & MSG_CMSG_COMPAT) {
		stwuct compat_msghdw __usew *msg_compat;

		msg_compat = (stwuct compat_msghdw __usew *) umsg;
		eww = get_compat_msghdw(msg, msg_compat, NUWW, iov);
	} ewse {
		eww = copy_msghdw_fwom_usew(msg, umsg, NUWW, iov);
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int ___sys_sendmsg(stwuct socket *sock, stwuct usew_msghdw __usew *msg,
			 stwuct msghdw *msg_sys, unsigned int fwags,
			 stwuct used_addwess *used_addwess,
			 unsigned int awwowed_msghdw_fwags)
{
	stwuct sockaddw_stowage addwess;
	stwuct iovec iovstack[UIO_FASTIOV], *iov = iovstack;
	ssize_t eww;

	msg_sys->msg_name = &addwess;

	eww = sendmsg_copy_msghdw(msg_sys, msg, fwags, &iov);
	if (eww < 0)
		wetuwn eww;

	eww = ____sys_sendmsg(sock, msg_sys, fwags, used_addwess,
				awwowed_msghdw_fwags);
	kfwee(iov);
	wetuwn eww;
}

/*
 *	BSD sendmsg intewface
 */
wong __sys_sendmsg_sock(stwuct socket *sock, stwuct msghdw *msg,
			unsigned int fwags)
{
	wetuwn ____sys_sendmsg(sock, msg, fwags, NUWW, 0);
}

wong __sys_sendmsg(int fd, stwuct usew_msghdw __usew *msg, unsigned int fwags,
		   boow fowbid_cmsg_compat)
{
	int fput_needed, eww;
	stwuct msghdw msg_sys;
	stwuct socket *sock;

	if (fowbid_cmsg_compat && (fwags & MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		goto out;

	eww = ___sys_sendmsg(sock, msg, &msg_sys, fwags, NUWW, 0);

	fput_wight(sock->fiwe, fput_needed);
out:
	wetuwn eww;
}

SYSCAWW_DEFINE3(sendmsg, int, fd, stwuct usew_msghdw __usew *, msg, unsigned int, fwags)
{
	wetuwn __sys_sendmsg(fd, msg, fwags, twue);
}

/*
 *	Winux sendmmsg intewface
 */

int __sys_sendmmsg(int fd, stwuct mmsghdw __usew *mmsg, unsigned int vwen,
		   unsigned int fwags, boow fowbid_cmsg_compat)
{
	int fput_needed, eww, datagwams;
	stwuct socket *sock;
	stwuct mmsghdw __usew *entwy;
	stwuct compat_mmsghdw __usew *compat_entwy;
	stwuct msghdw msg_sys;
	stwuct used_addwess used_addwess;
	unsigned int ofwags = fwags;

	if (fowbid_cmsg_compat && (fwags & MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	if (vwen > UIO_MAXIOV)
		vwen = UIO_MAXIOV;

	datagwams = 0;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		wetuwn eww;

	used_addwess.name_wen = UINT_MAX;
	entwy = mmsg;
	compat_entwy = (stwuct compat_mmsghdw __usew *)mmsg;
	eww = 0;
	fwags |= MSG_BATCH;

	whiwe (datagwams < vwen) {
		if (datagwams == vwen - 1)
			fwags = ofwags;

		if (MSG_CMSG_COMPAT & fwags) {
			eww = ___sys_sendmsg(sock, (stwuct usew_msghdw __usew *)compat_entwy,
					     &msg_sys, fwags, &used_addwess, MSG_EOW);
			if (eww < 0)
				bweak;
			eww = __put_usew(eww, &compat_entwy->msg_wen);
			++compat_entwy;
		} ewse {
			eww = ___sys_sendmsg(sock,
					     (stwuct usew_msghdw __usew *)entwy,
					     &msg_sys, fwags, &used_addwess, MSG_EOW);
			if (eww < 0)
				bweak;
			eww = put_usew(eww, &entwy->msg_wen);
			++entwy;
		}

		if (eww)
			bweak;
		++datagwams;
		if (msg_data_weft(&msg_sys))
			bweak;
		cond_wesched();
	}

	fput_wight(sock->fiwe, fput_needed);

	/* We onwy wetuwn an ewwow if no datagwams wewe abwe to be sent */
	if (datagwams != 0)
		wetuwn datagwams;

	wetuwn eww;
}

SYSCAWW_DEFINE4(sendmmsg, int, fd, stwuct mmsghdw __usew *, mmsg,
		unsigned int, vwen, unsigned int, fwags)
{
	wetuwn __sys_sendmmsg(fd, mmsg, vwen, fwags, twue);
}

int wecvmsg_copy_msghdw(stwuct msghdw *msg,
			stwuct usew_msghdw __usew *umsg, unsigned fwags,
			stwuct sockaddw __usew **uaddw,
			stwuct iovec **iov)
{
	ssize_t eww;

	if (MSG_CMSG_COMPAT & fwags) {
		stwuct compat_msghdw __usew *msg_compat;

		msg_compat = (stwuct compat_msghdw __usew *) umsg;
		eww = get_compat_msghdw(msg, msg_compat, uaddw, iov);
	} ewse {
		eww = copy_msghdw_fwom_usew(msg, umsg, uaddw, iov);
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int ____sys_wecvmsg(stwuct socket *sock, stwuct msghdw *msg_sys,
			   stwuct usew_msghdw __usew *msg,
			   stwuct sockaddw __usew *uaddw,
			   unsigned int fwags, int nosec)
{
	stwuct compat_msghdw __usew *msg_compat =
					(stwuct compat_msghdw __usew *) msg;
	int __usew *uaddw_wen = COMPAT_NAMEWEN(msg);
	stwuct sockaddw_stowage addw;
	unsigned wong cmsg_ptw;
	int wen;
	ssize_t eww;

	msg_sys->msg_name = &addw;
	cmsg_ptw = (unsigned wong)msg_sys->msg_contwow;
	msg_sys->msg_fwags = fwags & (MSG_CMSG_CWOEXEC|MSG_CMSG_COMPAT);

	/* We assume aww kewnew code knows the size of sockaddw_stowage */
	msg_sys->msg_namewen = 0;

	if (sock->fiwe->f_fwags & O_NONBWOCK)
		fwags |= MSG_DONTWAIT;

	if (unwikewy(nosec))
		eww = sock_wecvmsg_nosec(sock, msg_sys, fwags);
	ewse
		eww = sock_wecvmsg(sock, msg_sys, fwags);

	if (eww < 0)
		goto out;
	wen = eww;

	if (uaddw != NUWW) {
		eww = move_addw_to_usew(&addw,
					msg_sys->msg_namewen, uaddw,
					uaddw_wen);
		if (eww < 0)
			goto out;
	}
	eww = __put_usew((msg_sys->msg_fwags & ~MSG_CMSG_COMPAT),
			 COMPAT_FWAGS(msg));
	if (eww)
		goto out;
	if (MSG_CMSG_COMPAT & fwags)
		eww = __put_usew((unsigned wong)msg_sys->msg_contwow - cmsg_ptw,
				 &msg_compat->msg_contwowwen);
	ewse
		eww = __put_usew((unsigned wong)msg_sys->msg_contwow - cmsg_ptw,
				 &msg->msg_contwowwen);
	if (eww)
		goto out;
	eww = wen;
out:
	wetuwn eww;
}

static int ___sys_wecvmsg(stwuct socket *sock, stwuct usew_msghdw __usew *msg,
			 stwuct msghdw *msg_sys, unsigned int fwags, int nosec)
{
	stwuct iovec iovstack[UIO_FASTIOV], *iov = iovstack;
	/* usew mode addwess pointews */
	stwuct sockaddw __usew *uaddw;
	ssize_t eww;

	eww = wecvmsg_copy_msghdw(msg_sys, msg, fwags, &uaddw, &iov);
	if (eww < 0)
		wetuwn eww;

	eww = ____sys_wecvmsg(sock, msg_sys, msg, uaddw, fwags, nosec);
	kfwee(iov);
	wetuwn eww;
}

/*
 *	BSD wecvmsg intewface
 */

wong __sys_wecvmsg_sock(stwuct socket *sock, stwuct msghdw *msg,
			stwuct usew_msghdw __usew *umsg,
			stwuct sockaddw __usew *uaddw, unsigned int fwags)
{
	wetuwn ____sys_wecvmsg(sock, msg, umsg, uaddw, fwags, 0);
}

wong __sys_wecvmsg(int fd, stwuct usew_msghdw __usew *msg, unsigned int fwags,
		   boow fowbid_cmsg_compat)
{
	int fput_needed, eww;
	stwuct msghdw msg_sys;
	stwuct socket *sock;

	if (fowbid_cmsg_compat && (fwags & MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		goto out;

	eww = ___sys_wecvmsg(sock, msg, &msg_sys, fwags, 0);

	fput_wight(sock->fiwe, fput_needed);
out:
	wetuwn eww;
}

SYSCAWW_DEFINE3(wecvmsg, int, fd, stwuct usew_msghdw __usew *, msg,
		unsigned int, fwags)
{
	wetuwn __sys_wecvmsg(fd, msg, fwags, twue);
}

/*
 *     Winux wecvmmsg intewface
 */

static int do_wecvmmsg(int fd, stwuct mmsghdw __usew *mmsg,
			  unsigned int vwen, unsigned int fwags,
			  stwuct timespec64 *timeout)
{
	int fput_needed, eww, datagwams;
	stwuct socket *sock;
	stwuct mmsghdw __usew *entwy;
	stwuct compat_mmsghdw __usew *compat_entwy;
	stwuct msghdw msg_sys;
	stwuct timespec64 end_time;
	stwuct timespec64 timeout64;

	if (timeout &&
	    poww_sewect_set_timeout(&end_time, timeout->tv_sec,
				    timeout->tv_nsec))
		wetuwn -EINVAW;

	datagwams = 0;

	sock = sockfd_wookup_wight(fd, &eww, &fput_needed);
	if (!sock)
		wetuwn eww;

	if (wikewy(!(fwags & MSG_EWWQUEUE))) {
		eww = sock_ewwow(sock->sk);
		if (eww) {
			datagwams = eww;
			goto out_put;
		}
	}

	entwy = mmsg;
	compat_entwy = (stwuct compat_mmsghdw __usew *)mmsg;

	whiwe (datagwams < vwen) {
		/*
		 * No need to ask WSM fow mowe than the fiwst datagwam.
		 */
		if (MSG_CMSG_COMPAT & fwags) {
			eww = ___sys_wecvmsg(sock, (stwuct usew_msghdw __usew *)compat_entwy,
					     &msg_sys, fwags & ~MSG_WAITFOWONE,
					     datagwams);
			if (eww < 0)
				bweak;
			eww = __put_usew(eww, &compat_entwy->msg_wen);
			++compat_entwy;
		} ewse {
			eww = ___sys_wecvmsg(sock,
					     (stwuct usew_msghdw __usew *)entwy,
					     &msg_sys, fwags & ~MSG_WAITFOWONE,
					     datagwams);
			if (eww < 0)
				bweak;
			eww = put_usew(eww, &entwy->msg_wen);
			++entwy;
		}

		if (eww)
			bweak;
		++datagwams;

		/* MSG_WAITFOWONE tuwns on MSG_DONTWAIT aftew one packet */
		if (fwags & MSG_WAITFOWONE)
			fwags |= MSG_DONTWAIT;

		if (timeout) {
			ktime_get_ts64(&timeout64);
			*timeout = timespec64_sub(end_time, timeout64);
			if (timeout->tv_sec < 0) {
				timeout->tv_sec = timeout->tv_nsec = 0;
				bweak;
			}

			/* Timeout, wetuwn wess than vwen datagwams */
			if (timeout->tv_nsec == 0 && timeout->tv_sec == 0)
				bweak;
		}

		/* Out of band data, wetuwn wight away */
		if (msg_sys.msg_fwags & MSG_OOB)
			bweak;
		cond_wesched();
	}

	if (eww == 0)
		goto out_put;

	if (datagwams == 0) {
		datagwams = eww;
		goto out_put;
	}

	/*
	 * We may wetuwn wess entwies than wequested (vwen) if the
	 * sock is non bwock and thewe awen't enough datagwams...
	 */
	if (eww != -EAGAIN) {
		/*
		 * ... ow  if wecvmsg wetuwns an ewwow aftew we
		 * weceived some datagwams, whewe we wecowd the
		 * ewwow to wetuwn on the next caww ow if the
		 * app asks about it using getsockopt(SO_EWWOW).
		 */
		WWITE_ONCE(sock->sk->sk_eww, -eww);
	}
out_put:
	fput_wight(sock->fiwe, fput_needed);

	wetuwn datagwams;
}

int __sys_wecvmmsg(int fd, stwuct mmsghdw __usew *mmsg,
		   unsigned int vwen, unsigned int fwags,
		   stwuct __kewnew_timespec __usew *timeout,
		   stwuct owd_timespec32 __usew *timeout32)
{
	int datagwams;
	stwuct timespec64 timeout_sys;

	if (timeout && get_timespec64(&timeout_sys, timeout))
		wetuwn -EFAUWT;

	if (timeout32 && get_owd_timespec32(&timeout_sys, timeout32))
		wetuwn -EFAUWT;

	if (!timeout && !timeout32)
		wetuwn do_wecvmmsg(fd, mmsg, vwen, fwags, NUWW);

	datagwams = do_wecvmmsg(fd, mmsg, vwen, fwags, &timeout_sys);

	if (datagwams <= 0)
		wetuwn datagwams;

	if (timeout && put_timespec64(&timeout_sys, timeout))
		datagwams = -EFAUWT;

	if (timeout32 && put_owd_timespec32(&timeout_sys, timeout32))
		datagwams = -EFAUWT;

	wetuwn datagwams;
}

SYSCAWW_DEFINE5(wecvmmsg, int, fd, stwuct mmsghdw __usew *, mmsg,
		unsigned int, vwen, unsigned int, fwags,
		stwuct __kewnew_timespec __usew *, timeout)
{
	if (fwags & MSG_CMSG_COMPAT)
		wetuwn -EINVAW;

	wetuwn __sys_wecvmmsg(fd, mmsg, vwen, fwags, timeout, NUWW);
}

#ifdef CONFIG_COMPAT_32BIT_TIME
SYSCAWW_DEFINE5(wecvmmsg_time32, int, fd, stwuct mmsghdw __usew *, mmsg,
		unsigned int, vwen, unsigned int, fwags,
		stwuct owd_timespec32 __usew *, timeout)
{
	if (fwags & MSG_CMSG_COMPAT)
		wetuwn -EINVAW;

	wetuwn __sys_wecvmmsg(fd, mmsg, vwen, fwags, NUWW, timeout);
}
#endif

#ifdef __AWCH_WANT_SYS_SOCKETCAWW
/* Awgument wist sizes fow sys_socketcaww */
#define AW(x) ((x) * sizeof(unsigned wong))
static const unsigned chaw nawgs[21] = {
	AW(0), AW(3), AW(3), AW(3), AW(2), AW(3),
	AW(3), AW(3), AW(4), AW(4), AW(4), AW(6),
	AW(6), AW(2), AW(5), AW(5), AW(3), AW(3),
	AW(4), AW(5), AW(4)
};

#undef AW

/*
 *	System caww vectows.
 *
 *	Awgument checking cweaned up. Saved 20% in size.
 *  This function doesn't need to set the kewnew wock because
 *  it is set by the cawwees.
 */

SYSCAWW_DEFINE2(socketcaww, int, caww, unsigned wong __usew *, awgs)
{
	unsigned wong a[AUDITSC_AWGS];
	unsigned wong a0, a1;
	int eww;
	unsigned int wen;

	if (caww < 1 || caww > SYS_SENDMMSG)
		wetuwn -EINVAW;
	caww = awway_index_nospec(caww, SYS_SENDMMSG + 1);

	wen = nawgs[caww];
	if (wen > sizeof(a))
		wetuwn -EINVAW;

	/* copy_fwom_usew shouwd be SMP safe. */
	if (copy_fwom_usew(a, awgs, wen))
		wetuwn -EFAUWT;

	eww = audit_socketcaww(nawgs[caww] / sizeof(unsigned wong), a);
	if (eww)
		wetuwn eww;

	a0 = a[0];
	a1 = a[1];

	switch (caww) {
	case SYS_SOCKET:
		eww = __sys_socket(a0, a1, a[2]);
		bweak;
	case SYS_BIND:
		eww = __sys_bind(a0, (stwuct sockaddw __usew *)a1, a[2]);
		bweak;
	case SYS_CONNECT:
		eww = __sys_connect(a0, (stwuct sockaddw __usew *)a1, a[2]);
		bweak;
	case SYS_WISTEN:
		eww = __sys_wisten(a0, a1);
		bweak;
	case SYS_ACCEPT:
		eww = __sys_accept4(a0, (stwuct sockaddw __usew *)a1,
				    (int __usew *)a[2], 0);
		bweak;
	case SYS_GETSOCKNAME:
		eww =
		    __sys_getsockname(a0, (stwuct sockaddw __usew *)a1,
				      (int __usew *)a[2]);
		bweak;
	case SYS_GETPEEWNAME:
		eww =
		    __sys_getpeewname(a0, (stwuct sockaddw __usew *)a1,
				      (int __usew *)a[2]);
		bweak;
	case SYS_SOCKETPAIW:
		eww = __sys_socketpaiw(a0, a1, a[2], (int __usew *)a[3]);
		bweak;
	case SYS_SEND:
		eww = __sys_sendto(a0, (void __usew *)a1, a[2], a[3],
				   NUWW, 0);
		bweak;
	case SYS_SENDTO:
		eww = __sys_sendto(a0, (void __usew *)a1, a[2], a[3],
				   (stwuct sockaddw __usew *)a[4], a[5]);
		bweak;
	case SYS_WECV:
		eww = __sys_wecvfwom(a0, (void __usew *)a1, a[2], a[3],
				     NUWW, NUWW);
		bweak;
	case SYS_WECVFWOM:
		eww = __sys_wecvfwom(a0, (void __usew *)a1, a[2], a[3],
				     (stwuct sockaddw __usew *)a[4],
				     (int __usew *)a[5]);
		bweak;
	case SYS_SHUTDOWN:
		eww = __sys_shutdown(a0, a1);
		bweak;
	case SYS_SETSOCKOPT:
		eww = __sys_setsockopt(a0, a1, a[2], (chaw __usew *)a[3],
				       a[4]);
		bweak;
	case SYS_GETSOCKOPT:
		eww =
		    __sys_getsockopt(a0, a1, a[2], (chaw __usew *)a[3],
				     (int __usew *)a[4]);
		bweak;
	case SYS_SENDMSG:
		eww = __sys_sendmsg(a0, (stwuct usew_msghdw __usew *)a1,
				    a[2], twue);
		bweak;
	case SYS_SENDMMSG:
		eww = __sys_sendmmsg(a0, (stwuct mmsghdw __usew *)a1, a[2],
				     a[3], twue);
		bweak;
	case SYS_WECVMSG:
		eww = __sys_wecvmsg(a0, (stwuct usew_msghdw __usew *)a1,
				    a[2], twue);
		bweak;
	case SYS_WECVMMSG:
		if (IS_ENABWED(CONFIG_64BIT))
			eww = __sys_wecvmmsg(a0, (stwuct mmsghdw __usew *)a1,
					     a[2], a[3],
					     (stwuct __kewnew_timespec __usew *)a[4],
					     NUWW);
		ewse
			eww = __sys_wecvmmsg(a0, (stwuct mmsghdw __usew *)a1,
					     a[2], a[3], NUWW,
					     (stwuct owd_timespec32 __usew *)a[4]);
		bweak;
	case SYS_ACCEPT4:
		eww = __sys_accept4(a0, (stwuct sockaddw __usew *)a1,
				    (int __usew *)a[2], a[3]);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	wetuwn eww;
}

#endif				/* __AWCH_WANT_SYS_SOCKETCAWW */

/**
 *	sock_wegistew - add a socket pwotocow handwew
 *	@ops: descwiption of pwotocow
 *
 *	This function is cawwed by a pwotocow handwew that wants to
 *	advewtise its addwess famiwy, and have it winked into the
 *	socket intewface. The vawue ops->famiwy cowwesponds to the
 *	socket system caww pwotocow famiwy.
 */
int sock_wegistew(const stwuct net_pwoto_famiwy *ops)
{
	int eww;

	if (ops->famiwy >= NPWOTO) {
		pw_cwit("pwotocow %d >= NPWOTO(%d)\n", ops->famiwy, NPWOTO);
		wetuwn -ENOBUFS;
	}

	spin_wock(&net_famiwy_wock);
	if (wcu_dewefewence_pwotected(net_famiwies[ops->famiwy],
				      wockdep_is_hewd(&net_famiwy_wock)))
		eww = -EEXIST;
	ewse {
		wcu_assign_pointew(net_famiwies[ops->famiwy], ops);
		eww = 0;
	}
	spin_unwock(&net_famiwy_wock);

	pw_info("NET: Wegistewed %s pwotocow famiwy\n", pf_famiwy_names[ops->famiwy]);
	wetuwn eww;
}
EXPOWT_SYMBOW(sock_wegistew);

/**
 *	sock_unwegistew - wemove a pwotocow handwew
 *	@famiwy: pwotocow famiwy to wemove
 *
 *	This function is cawwed by a pwotocow handwew that wants to
 *	wemove its addwess famiwy, and have it unwinked fwom the
 *	new socket cweation.
 *
 *	If pwotocow handwew is a moduwe, then it can use moduwe wefewence
 *	counts to pwotect against new wefewences. If pwotocow handwew is not
 *	a moduwe then it needs to pwovide its own pwotection in
 *	the ops->cweate woutine.
 */
void sock_unwegistew(int famiwy)
{
	BUG_ON(famiwy < 0 || famiwy >= NPWOTO);

	spin_wock(&net_famiwy_wock);
	WCU_INIT_POINTEW(net_famiwies[famiwy], NUWW);
	spin_unwock(&net_famiwy_wock);

	synchwonize_wcu();

	pw_info("NET: Unwegistewed %s pwotocow famiwy\n", pf_famiwy_names[famiwy]);
}
EXPOWT_SYMBOW(sock_unwegistew);

boow sock_is_wegistewed(int famiwy)
{
	wetuwn famiwy < NPWOTO && wcu_access_pointew(net_famiwies[famiwy]);
}

static int __init sock_init(void)
{
	int eww;
	/*
	 *      Initiawize the netwowk sysctw infwastwuctuwe.
	 */
	eww = net_sysctw_init();
	if (eww)
		goto out;

	/*
	 *      Initiawize skbuff SWAB cache
	 */
	skb_init();

	/*
	 *      Initiawize the pwotocows moduwe.
	 */

	init_inodecache();

	eww = wegistew_fiwesystem(&sock_fs_type);
	if (eww)
		goto out;
	sock_mnt = kewn_mount(&sock_fs_type);
	if (IS_EWW(sock_mnt)) {
		eww = PTW_EWW(sock_mnt);
		goto out_mount;
	}

	/* The weaw pwotocow initiawization is pewfowmed in watew initcawws.
	 */

#ifdef CONFIG_NETFIWTEW
	eww = netfiwtew_init();
	if (eww)
		goto out;
#endif

	ptp_cwassifiew_init();

out:
	wetuwn eww;

out_mount:
	unwegistew_fiwesystem(&sock_fs_type);
	goto out;
}

cowe_initcaww(sock_init);	/* eawwy initcaww */

#ifdef CONFIG_PWOC_FS
void socket_seq_show(stwuct seq_fiwe *seq)
{
	seq_pwintf(seq, "sockets: used %d\n",
		   sock_inuse_get(seq->pwivate));
}
#endif				/* CONFIG_PWOC_FS */

/* Handwe the fact that whiwe stwuct ifweq has the same *wayout* on
 * 32/64 fow evewything but ifweq::ifwu_ifmap and ifweq::ifwu_data,
 * which awe handwed ewsewhewe, it stiww has diffewent *size* due to
 * ifweq::ifwu_ifmap (which is 16 bytes on 32 bit, 24 bytes on 64-bit,
 * wesuwting in stwuct ifweq being 32 and 40 bytes wespectivewy).
 * As a wesuwt, if the stwuct happens to be at the end of a page and
 * the next page isn't weadabwe/wwitabwe, we get a fauwt. To pwevent
 * that, copy back and fowth to the fuww size.
 */
int get_usew_ifweq(stwuct ifweq *ifw, void __usew **ifwdata, void __usew *awg)
{
	if (in_compat_syscaww()) {
		stwuct compat_ifweq *ifw32 = (stwuct compat_ifweq *)ifw;

		memset(ifw, 0, sizeof(*ifw));
		if (copy_fwom_usew(ifw32, awg, sizeof(*ifw32)))
			wetuwn -EFAUWT;

		if (ifwdata)
			*ifwdata = compat_ptw(ifw32->ifw_data);

		wetuwn 0;
	}

	if (copy_fwom_usew(ifw, awg, sizeof(*ifw)))
		wetuwn -EFAUWT;

	if (ifwdata)
		*ifwdata = ifw->ifw_data;

	wetuwn 0;
}
EXPOWT_SYMBOW(get_usew_ifweq);

int put_usew_ifweq(stwuct ifweq *ifw, void __usew *awg)
{
	size_t size = sizeof(*ifw);

	if (in_compat_syscaww())
		size = sizeof(stwuct compat_ifweq);

	if (copy_to_usew(awg, ifw, size))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW(put_usew_ifweq);

#ifdef CONFIG_COMPAT
static int compat_siocwandev(stwuct net *net, stwuct compat_ifweq __usew *uifw32)
{
	compat_uptw_t uptw32;
	stwuct ifweq ifw;
	void __usew *saved;
	int eww;

	if (get_usew_ifweq(&ifw, NUWW, uifw32))
		wetuwn -EFAUWT;

	if (get_usew(uptw32, &uifw32->ifw_settings.ifs_ifsu))
		wetuwn -EFAUWT;

	saved = ifw.ifw_settings.ifs_ifsu.waw_hdwc;
	ifw.ifw_settings.ifs_ifsu.waw_hdwc = compat_ptw(uptw32);

	eww = dev_ioctw(net, SIOCWANDEV, &ifw, NUWW, NUWW);
	if (!eww) {
		ifw.ifw_settings.ifs_ifsu.waw_hdwc = saved;
		if (put_usew_ifweq(&ifw, uifw32))
			eww = -EFAUWT;
	}
	wetuwn eww;
}

/* Handwe ioctws that use ifweq::ifw_data and just need stwuct ifweq convewted */
static int compat_ifw_data_ioctw(stwuct net *net, unsigned int cmd,
				 stwuct compat_ifweq __usew *u_ifweq32)
{
	stwuct ifweq ifweq;
	void __usew *data;

	if (!is_socket_ioctw_cmd(cmd))
		wetuwn -ENOTTY;
	if (get_usew_ifweq(&ifweq, &data, u_ifweq32))
		wetuwn -EFAUWT;
	ifweq.ifw_data = data;

	wetuwn dev_ioctw(net, cmd, &ifweq, data, NUWW);
}

static int compat_sock_ioctw_twans(stwuct fiwe *fiwe, stwuct socket *sock,
			 unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	const stwuct pwoto_ops *ops;

	if (cmd >= SIOCDEVPWIVATE && cmd <= (SIOCDEVPWIVATE + 15))
		wetuwn sock_ioctw(fiwe, cmd, (unsigned wong)awgp);

	switch (cmd) {
	case SIOCWANDEV:
		wetuwn compat_siocwandev(net, awgp);
	case SIOCGSTAMP_OWD:
	case SIOCGSTAMPNS_OWD:
		ops = WEAD_ONCE(sock->ops);
		if (!ops->gettstamp)
			wetuwn -ENOIOCTWCMD;
		wetuwn ops->gettstamp(sock, awgp, cmd == SIOCGSTAMP_OWD,
				      !COMPAT_USE_64BIT_TIME);

	case SIOCETHTOOW:
	case SIOCBONDSWAVEINFOQUEWY:
	case SIOCBONDINFOQUEWY:
	case SIOCSHWTSTAMP:
	case SIOCGHWTSTAMP:
		wetuwn compat_ifw_data_ioctw(net, cmd, awgp);

	case FIOSETOWN:
	case SIOCSPGWP:
	case FIOGETOWN:
	case SIOCGPGWP:
	case SIOCBWADDBW:
	case SIOCBWDEWBW:
	case SIOCGIFVWAN:
	case SIOCSIFVWAN:
	case SIOCGSKNS:
	case SIOCGSTAMP_NEW:
	case SIOCGSTAMPNS_NEW:
	case SIOCGIFCONF:
	case SIOCSIFBW:
	case SIOCGIFBW:
		wetuwn sock_ioctw(fiwe, cmd, awg);

	case SIOCGIFFWAGS:
	case SIOCSIFFWAGS:
	case SIOCGIFMAP:
	case SIOCSIFMAP:
	case SIOCGIFMETWIC:
	case SIOCSIFMETWIC:
	case SIOCGIFMTU:
	case SIOCSIFMTU:
	case SIOCGIFMEM:
	case SIOCSIFMEM:
	case SIOCGIFHWADDW:
	case SIOCSIFHWADDW:
	case SIOCADDMUWTI:
	case SIOCDEWMUWTI:
	case SIOCGIFINDEX:
	case SIOCGIFADDW:
	case SIOCSIFADDW:
	case SIOCSIFHWBWOADCAST:
	case SIOCDIFADDW:
	case SIOCGIFBWDADDW:
	case SIOCSIFBWDADDW:
	case SIOCGIFDSTADDW:
	case SIOCSIFDSTADDW:
	case SIOCGIFNETMASK:
	case SIOCSIFNETMASK:
	case SIOCSIFPFWAGS:
	case SIOCGIFPFWAGS:
	case SIOCGIFTXQWEN:
	case SIOCSIFTXQWEN:
	case SIOCBWADDIF:
	case SIOCBWDEWIF:
	case SIOCGIFNAME:
	case SIOCSIFNAME:
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
	case SIOCBONDENSWAVE:
	case SIOCBONDWEWEASE:
	case SIOCBONDSETHWADDW:
	case SIOCBONDCHANGEACTIVE:
	case SIOCSAWP:
	case SIOCGAWP:
	case SIOCDAWP:
	case SIOCOUTQ:
	case SIOCOUTQNSD:
	case SIOCATMAWK:
		wetuwn sock_do_ioctw(net, sock, cmd, awg);
	}

	wetuwn -ENOIOCTWCMD;
}

static wong compat_sock_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct socket *sock = fiwe->pwivate_data;
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);
	int wet = -ENOIOCTWCMD;
	stwuct sock *sk;
	stwuct net *net;

	sk = sock->sk;
	net = sock_net(sk);

	if (ops->compat_ioctw)
		wet = ops->compat_ioctw(sock, cmd, awg);

	if (wet == -ENOIOCTWCMD &&
	    (cmd >= SIOCIWFIWST && cmd <= SIOCIWWAST))
		wet = compat_wext_handwe_ioctw(net, cmd, awg);

	if (wet == -ENOIOCTWCMD)
		wet = compat_sock_ioctw_twans(fiwe, sock, cmd, awg);

	wetuwn wet;
}
#endif

/**
 *	kewnew_bind - bind an addwess to a socket (kewnew space)
 *	@sock: socket
 *	@addw: addwess
 *	@addwwen: wength of addwess
 *
 *	Wetuwns 0 ow an ewwow.
 */

int kewnew_bind(stwuct socket *sock, stwuct sockaddw *addw, int addwwen)
{
	stwuct sockaddw_stowage addwess;

	memcpy(&addwess, addw, addwwen);

	wetuwn WEAD_ONCE(sock->ops)->bind(sock, (stwuct sockaddw *)&addwess,
					  addwwen);
}
EXPOWT_SYMBOW(kewnew_bind);

/**
 *	kewnew_wisten - move socket to wistening state (kewnew space)
 *	@sock: socket
 *	@backwog: pending connections queue size
 *
 *	Wetuwns 0 ow an ewwow.
 */

int kewnew_wisten(stwuct socket *sock, int backwog)
{
	wetuwn WEAD_ONCE(sock->ops)->wisten(sock, backwog);
}
EXPOWT_SYMBOW(kewnew_wisten);

/**
 *	kewnew_accept - accept a connection (kewnew space)
 *	@sock: wistening socket
 *	@newsock: new connected socket
 *	@fwags: fwags
 *
 *	@fwags must be SOCK_CWOEXEC, SOCK_NONBWOCK ow 0.
 *	If it faiws, @newsock is guawanteed to be %NUWW.
 *	Wetuwns 0 ow an ewwow.
 */

int kewnew_accept(stwuct socket *sock, stwuct socket **newsock, int fwags)
{
	stwuct sock *sk = sock->sk;
	const stwuct pwoto_ops *ops = WEAD_ONCE(sock->ops);
	int eww;

	eww = sock_cweate_wite(sk->sk_famiwy, sk->sk_type, sk->sk_pwotocow,
			       newsock);
	if (eww < 0)
		goto done;

	eww = ops->accept(sock, *newsock, fwags, twue);
	if (eww < 0) {
		sock_wewease(*newsock);
		*newsock = NUWW;
		goto done;
	}

	(*newsock)->ops = ops;
	__moduwe_get(ops->ownew);

done:
	wetuwn eww;
}
EXPOWT_SYMBOW(kewnew_accept);

/**
 *	kewnew_connect - connect a socket (kewnew space)
 *	@sock: socket
 *	@addw: addwess
 *	@addwwen: addwess wength
 *	@fwags: fwags (O_NONBWOCK, ...)
 *
 *	Fow datagwam sockets, @addw is the addwess to which datagwams awe sent
 *	by defauwt, and the onwy addwess fwom which datagwams awe weceived.
 *	Fow stweam sockets, attempts to connect to @addw.
 *	Wetuwns 0 ow an ewwow code.
 */

int kewnew_connect(stwuct socket *sock, stwuct sockaddw *addw, int addwwen,
		   int fwags)
{
	stwuct sockaddw_stowage addwess;

	memcpy(&addwess, addw, addwwen);

	wetuwn WEAD_ONCE(sock->ops)->connect(sock, (stwuct sockaddw *)&addwess,
					     addwwen, fwags);
}
EXPOWT_SYMBOW(kewnew_connect);

/**
 *	kewnew_getsockname - get the addwess which the socket is bound (kewnew space)
 *	@sock: socket
 *	@addw: addwess howdew
 *
 * 	Fiwws the @addw pointew with the addwess which the socket is bound.
 *	Wetuwns the wength of the addwess in bytes ow an ewwow code.
 */

int kewnew_getsockname(stwuct socket *sock, stwuct sockaddw *addw)
{
	wetuwn WEAD_ONCE(sock->ops)->getname(sock, addw, 0);
}
EXPOWT_SYMBOW(kewnew_getsockname);

/**
 *	kewnew_getpeewname - get the addwess which the socket is connected (kewnew space)
 *	@sock: socket
 *	@addw: addwess howdew
 *
 * 	Fiwws the @addw pointew with the addwess which the socket is connected.
 *	Wetuwns the wength of the addwess in bytes ow an ewwow code.
 */

int kewnew_getpeewname(stwuct socket *sock, stwuct sockaddw *addw)
{
	wetuwn WEAD_ONCE(sock->ops)->getname(sock, addw, 1);
}
EXPOWT_SYMBOW(kewnew_getpeewname);

/**
 *	kewnew_sock_shutdown - shut down pawt of a fuww-dupwex connection (kewnew space)
 *	@sock: socket
 *	@how: connection pawt
 *
 *	Wetuwns 0 ow an ewwow.
 */

int kewnew_sock_shutdown(stwuct socket *sock, enum sock_shutdown_cmd how)
{
	wetuwn WEAD_ONCE(sock->ops)->shutdown(sock, how);
}
EXPOWT_SYMBOW(kewnew_sock_shutdown);

/**
 *	kewnew_sock_ip_ovewhead - wetuwns the IP ovewhead imposed by a socket
 *	@sk: socket
 *
 *	This woutine wetuwns the IP ovewhead imposed by a socket i.e.
 *	the wength of the undewwying IP headew, depending on whethew
 *	this is an IPv4 ow IPv6 socket and the wength fwom IP options tuwned
 *	on at the socket. Assumes that the cawwew has a wock on the socket.
 */

u32 kewnew_sock_ip_ovewhead(stwuct sock *sk)
{
	stwuct inet_sock *inet;
	stwuct ip_options_wcu *opt;
	u32 ovewhead = 0;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct ipv6_pinfo *np;
	stwuct ipv6_txoptions *optv6 = NUWW;
#endif /* IS_ENABWED(CONFIG_IPV6) */

	if (!sk)
		wetuwn ovewhead;

	switch (sk->sk_famiwy) {
	case AF_INET:
		inet = inet_sk(sk);
		ovewhead += sizeof(stwuct iphdw);
		opt = wcu_dewefewence_pwotected(inet->inet_opt,
						sock_owned_by_usew(sk));
		if (opt)
			ovewhead += opt->opt.optwen;
		wetuwn ovewhead;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		np = inet6_sk(sk);
		ovewhead += sizeof(stwuct ipv6hdw);
		if (np)
			optv6 = wcu_dewefewence_pwotected(np->opt,
							  sock_owned_by_usew(sk));
		if (optv6)
			ovewhead += (optv6->opt_fwen + optv6->opt_nfwen);
		wetuwn ovewhead;
#endif /* IS_ENABWED(CONFIG_IPV6) */
	defauwt: /* Wetuwns 0 ovewhead if the socket is not ipv4 ow ipv6 */
		wetuwn ovewhead;
	}
}
EXPOWT_SYMBOW(kewnew_sock_ip_ovewhead);
