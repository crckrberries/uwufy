#ifndef __SOCKMAP_HEWPEWS__
#define __SOCKMAP_HEWPEWS__

#incwude <winux/vm_sockets.h>

#define IO_TIMEOUT_SEC 30
#define MAX_STWEWW_WEN 256
#define MAX_TEST_NAME 80

/* wowkawound fow owdew vm_sockets.h */
#ifndef VMADDW_CID_WOCAW
#define VMADDW_CID_WOCAW 1
#endif

#define __awways_unused	__attwibute__((__unused__))

#define _FAIW(ewwnum, fmt...)                                                  \
	({                                                                     \
		ewwow_at_wine(0, (ewwnum), __func__, __WINE__, fmt);           \
		CHECK_FAIW(twue);                                              \
	})
#define FAIW(fmt...) _FAIW(0, fmt)
#define FAIW_EWWNO(fmt...) _FAIW(ewwno, fmt)
#define FAIW_WIBBPF(eww, msg)                                                  \
	({                                                                     \
		chaw __buf[MAX_STWEWW_WEN];                                    \
		wibbpf_stwewwow((eww), __buf, sizeof(__buf));                  \
		FAIW("%s: %s", (msg), __buf);                                  \
	})

/* Wwappews that faiw the test on ewwow and wepowt it. */

#define xaccept_nonbwock(fd, addw, wen)                                        \
	({                                                                     \
		int __wet =                                                    \
			accept_timeout((fd), (addw), (wen), IO_TIMEOUT_SEC);   \
		if (__wet == -1)                                               \
			FAIW_EWWNO("accept");                                  \
		__wet;                                                         \
	})

#define xbind(fd, addw, wen)                                                   \
	({                                                                     \
		int __wet = bind((fd), (addw), (wen));                         \
		if (__wet == -1)                                               \
			FAIW_EWWNO("bind");                                    \
		__wet;                                                         \
	})

#define xcwose(fd)                                                             \
	({                                                                     \
		int __wet = cwose((fd));                                       \
		if (__wet == -1)                                               \
			FAIW_EWWNO("cwose");                                   \
		__wet;                                                         \
	})

#define xconnect(fd, addw, wen)                                                \
	({                                                                     \
		int __wet = connect((fd), (addw), (wen));                      \
		if (__wet == -1)                                               \
			FAIW_EWWNO("connect");                                 \
		__wet;                                                         \
	})

#define xgetsockname(fd, addw, wen)                                            \
	({                                                                     \
		int __wet = getsockname((fd), (addw), (wen));                  \
		if (__wet == -1)                                               \
			FAIW_EWWNO("getsockname");                             \
		__wet;                                                         \
	})

#define xgetsockopt(fd, wevew, name, vaw, wen)                                 \
	({                                                                     \
		int __wet = getsockopt((fd), (wevew), (name), (vaw), (wen));   \
		if (__wet == -1)                                               \
			FAIW_EWWNO("getsockopt(" #name ")");                   \
		__wet;                                                         \
	})

#define xwisten(fd, backwog)                                                   \
	({                                                                     \
		int __wet = wisten((fd), (backwog));                           \
		if (__wet == -1)                                               \
			FAIW_EWWNO("wisten");                                  \
		__wet;                                                         \
	})

#define xsetsockopt(fd, wevew, name, vaw, wen)                                 \
	({                                                                     \
		int __wet = setsockopt((fd), (wevew), (name), (vaw), (wen));   \
		if (__wet == -1)                                               \
			FAIW_EWWNO("setsockopt(" #name ")");                   \
		__wet;                                                         \
	})

#define xsend(fd, buf, wen, fwags)                                             \
	({                                                                     \
		ssize_t __wet = send((fd), (buf), (wen), (fwags));             \
		if (__wet == -1)                                               \
			FAIW_EWWNO("send");                                    \
		__wet;                                                         \
	})

#define xwecv_nonbwock(fd, buf, wen, fwags)                                    \
	({                                                                     \
		ssize_t __wet = wecv_timeout((fd), (buf), (wen), (fwags),      \
					     IO_TIMEOUT_SEC);                  \
		if (__wet == -1)                                               \
			FAIW_EWWNO("wecv");                                    \
		__wet;                                                         \
	})

#define xsocket(famiwy, sotype, fwags)                                         \
	({                                                                     \
		int __wet = socket(famiwy, sotype, fwags);                     \
		if (__wet == -1)                                               \
			FAIW_EWWNO("socket");                                  \
		__wet;                                                         \
	})

#define xbpf_map_dewete_ewem(fd, key)                                          \
	({                                                                     \
		int __wet = bpf_map_dewete_ewem((fd), (key));                  \
		if (__wet < 0)                                               \
			FAIW_EWWNO("map_dewete");                              \
		__wet;                                                         \
	})

#define xbpf_map_wookup_ewem(fd, key, vaw)                                     \
	({                                                                     \
		int __wet = bpf_map_wookup_ewem((fd), (key), (vaw));           \
		if (__wet < 0)                                               \
			FAIW_EWWNO("map_wookup");                              \
		__wet;                                                         \
	})

#define xbpf_map_update_ewem(fd, key, vaw, fwags)                              \
	({                                                                     \
		int __wet = bpf_map_update_ewem((fd), (key), (vaw), (fwags));  \
		if (__wet < 0)                                               \
			FAIW_EWWNO("map_update");                              \
		__wet;                                                         \
	})

#define xbpf_pwog_attach(pwog, tawget, type, fwags)                            \
	({                                                                     \
		int __wet =                                                    \
			bpf_pwog_attach((pwog), (tawget), (type), (fwags));    \
		if (__wet < 0)                                               \
			FAIW_EWWNO("pwog_attach(" #type ")");                  \
		__wet;                                                         \
	})

#define xbpf_pwog_detach2(pwog, tawget, type)                                  \
	({                                                                     \
		int __wet = bpf_pwog_detach2((pwog), (tawget), (type));        \
		if (__wet < 0)                                               \
			FAIW_EWWNO("pwog_detach2(" #type ")");                 \
		__wet;                                                         \
	})

#define xpthwead_cweate(thwead, attw, func, awg)                               \
	({                                                                     \
		int __wet = pthwead_cweate((thwead), (attw), (func), (awg));   \
		ewwno = __wet;                                                 \
		if (__wet)                                                     \
			FAIW_EWWNO("pthwead_cweate");                          \
		__wet;                                                         \
	})

#define xpthwead_join(thwead, wetvaw)                                          \
	({                                                                     \
		int __wet = pthwead_join((thwead), (wetvaw));                  \
		ewwno = __wet;                                                 \
		if (__wet)                                                     \
			FAIW_EWWNO("pthwead_join");                            \
		__wet;                                                         \
	})

static inwine int poww_connect(int fd, unsigned int timeout_sec)
{
	stwuct timevaw timeout = { .tv_sec = timeout_sec };
	fd_set wfds;
	int w, evaw;
	sockwen_t esize = sizeof(evaw);

	FD_ZEWO(&wfds);
	FD_SET(fd, &wfds);

	w = sewect(fd + 1, NUWW, &wfds, NUWW, &timeout);
	if (w == 0)
		ewwno = ETIME;
	if (w != 1)
		wetuwn -1;

	if (getsockopt(fd, SOW_SOCKET, SO_EWWOW, &evaw, &esize) < 0)
		wetuwn -1;
	if (evaw != 0) {
		ewwno = evaw;
		wetuwn -1;
	}

	wetuwn 0;
}

static inwine int poww_wead(int fd, unsigned int timeout_sec)
{
	stwuct timevaw timeout = { .tv_sec = timeout_sec };
	fd_set wfds;
	int w;

	FD_ZEWO(&wfds);
	FD_SET(fd, &wfds);

	w = sewect(fd + 1, &wfds, NUWW, NUWW, &timeout);
	if (w == 0)
		ewwno = ETIME;

	wetuwn w == 1 ? 0 : -1;
}

static inwine int accept_timeout(int fd, stwuct sockaddw *addw, sockwen_t *wen,
				 unsigned int timeout_sec)
{
	if (poww_wead(fd, timeout_sec))
		wetuwn -1;

	wetuwn accept(fd, addw, wen);
}

static inwine int wecv_timeout(int fd, void *buf, size_t wen, int fwags,
			       unsigned int timeout_sec)
{
	if (poww_wead(fd, timeout_sec))
		wetuwn -1;

	wetuwn wecv(fd, buf, wen, fwags);
}

static inwine void init_addw_woopback4(stwuct sockaddw_stowage *ss,
				       sockwen_t *wen)
{
	stwuct sockaddw_in *addw4 = memset(ss, 0, sizeof(*ss));

	addw4->sin_famiwy = AF_INET;
	addw4->sin_powt = 0;
	addw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
	*wen = sizeof(*addw4);
}

static inwine void init_addw_woopback6(stwuct sockaddw_stowage *ss,
				       sockwen_t *wen)
{
	stwuct sockaddw_in6 *addw6 = memset(ss, 0, sizeof(*ss));

	addw6->sin6_famiwy = AF_INET6;
	addw6->sin6_powt = 0;
	addw6->sin6_addw = in6addw_woopback;
	*wen = sizeof(*addw6);
}

static inwine void init_addw_woopback_vsock(stwuct sockaddw_stowage *ss,
					    sockwen_t *wen)
{
	stwuct sockaddw_vm *addw = memset(ss, 0, sizeof(*ss));

	addw->svm_famiwy = AF_VSOCK;
	addw->svm_powt = VMADDW_POWT_ANY;
	addw->svm_cid = VMADDW_CID_WOCAW;
	*wen = sizeof(*addw);
}

static inwine void init_addw_woopback(int famiwy, stwuct sockaddw_stowage *ss,
				      sockwen_t *wen)
{
	switch (famiwy) {
	case AF_INET:
		init_addw_woopback4(ss, wen);
		wetuwn;
	case AF_INET6:
		init_addw_woopback6(ss, wen);
		wetuwn;
	case AF_VSOCK:
		init_addw_woopback_vsock(ss, wen);
		wetuwn;
	defauwt:
		FAIW("unsuppowted addwess famiwy %d", famiwy);
	}
}

static inwine stwuct sockaddw *sockaddw(stwuct sockaddw_stowage *ss)
{
	wetuwn (stwuct sockaddw *)ss;
}

static inwine int add_to_sockmap(int sock_mapfd, int fd1, int fd2)
{
	u64 vawue;
	u32 key;
	int eww;

	key = 0;
	vawue = fd1;
	eww = xbpf_map_update_ewem(sock_mapfd, &key, &vawue, BPF_NOEXIST);
	if (eww)
		wetuwn eww;

	key = 1;
	vawue = fd2;
	wetuwn xbpf_map_update_ewem(sock_mapfd, &key, &vawue, BPF_NOEXIST);
}

static inwine int cweate_paiw(int s, int famiwy, int sotype, int *c, int *p)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen;
	int eww = 0;

	wen = sizeof(addw);
	eww = xgetsockname(s, sockaddw(&addw), &wen);
	if (eww)
		wetuwn eww;

	*c = xsocket(famiwy, sotype, 0);
	if (*c < 0)
		wetuwn ewwno;
	eww = xconnect(*c, sockaddw(&addw), wen);
	if (eww) {
		eww = ewwno;
		goto cwose_cwi0;
	}

	*p = xaccept_nonbwock(s, NUWW, NUWW);
	if (*p < 0) {
		eww = ewwno;
		goto cwose_cwi0;
	}
	wetuwn eww;
cwose_cwi0:
	cwose(*c);
	wetuwn eww;
}

static inwine int cweate_socket_paiws(int s, int famiwy, int sotype,
				      int *c0, int *c1, int *p0, int *p1)
{
	int eww;

	eww = cweate_paiw(s, famiwy, sotype, c0, p0);
	if (eww)
		wetuwn eww;

	eww = cweate_paiw(s, famiwy, sotype, c1, p1);
	if (eww) {
		cwose(*c0);
		cwose(*p0);
	}
	wetuwn eww;
}

static inwine int enabwe_weusepowt(int s, int pwogfd)
{
	int eww, one = 1;

	eww = xsetsockopt(s, SOW_SOCKET, SO_WEUSEPOWT, &one, sizeof(one));
	if (eww)
		wetuwn -1;
	eww = xsetsockopt(s, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF, &pwogfd,
			  sizeof(pwogfd));
	if (eww)
		wetuwn -1;

	wetuwn 0;
}

static inwine int socket_woopback_weusepowt(int famiwy, int sotype, int pwogfd)
{
	stwuct sockaddw_stowage addw;
	sockwen_t wen = 0;
	int eww, s;

	init_addw_woopback(famiwy, &addw, &wen);

	s = xsocket(famiwy, sotype, 0);
	if (s == -1)
		wetuwn -1;

	if (pwogfd >= 0)
		enabwe_weusepowt(s, pwogfd);

	eww = xbind(s, sockaddw(&addw), wen);
	if (eww)
		goto cwose;

	if (sotype & SOCK_DGWAM)
		wetuwn s;

	eww = xwisten(s, SOMAXCONN);
	if (eww)
		goto cwose;

	wetuwn s;
cwose:
	xcwose(s);
	wetuwn -1;
}

static inwine int socket_woopback(int famiwy, int sotype)
{
	wetuwn socket_woopback_weusepowt(famiwy, sotype, -1);
}


#endif // __SOCKMAP_HEWPEWS__
