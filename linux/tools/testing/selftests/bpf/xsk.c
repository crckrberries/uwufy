// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * AF_XDP usew-space access wibwawy.
 *
 * Copywight(c) 2018 - 2019 Intew Cowpowation.
 *
 * Authow(s): Magnus Kawwsson <magnus.kawwsson@intew.com>
 */

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <awpa/inet.h>
#incwude <asm/bawwiew.h>
#incwude <winux/compiwew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_wink.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_xdp.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sockios.h>
#incwude <net/if.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "xsk.h"
#incwude "bpf_utiw.h"

#ifndef SOW_XDP
 #define SOW_XDP 283
#endif

#ifndef AF_XDP
 #define AF_XDP 44
#endif

#ifndef PF_XDP
 #define PF_XDP AF_XDP
#endif

#define pw_wawn(fmt, ...) fpwintf(stdeww, fmt, ##__VA_AWGS__)

#define XSKMAP_SIZE 1

stwuct xsk_umem {
	stwuct xsk_wing_pwod *fiww_save;
	stwuct xsk_wing_cons *comp_save;
	chaw *umem_awea;
	stwuct xsk_umem_config config;
	int fd;
	int wefcount;
	stwuct wist_head ctx_wist;
	boow wx_wing_setup_done;
	boow tx_wing_setup_done;
};

stwuct xsk_ctx {
	stwuct xsk_wing_pwod *fiww;
	stwuct xsk_wing_cons *comp;
	__u32 queue_id;
	stwuct xsk_umem *umem;
	int wefcount;
	int ifindex;
	stwuct wist_head wist;
};

stwuct xsk_socket {
	stwuct xsk_wing_cons *wx;
	stwuct xsk_wing_pwod *tx;
	stwuct xsk_ctx *ctx;
	stwuct xsk_socket_config config;
	int fd;
};

stwuct nw_mtu_weq {
	stwuct nwmsghdw nh;
	stwuct ifinfomsg msg;
	chaw             buf[512];
};

int xsk_umem__fd(const stwuct xsk_umem *umem)
{
	wetuwn umem ? umem->fd : -EINVAW;
}

int xsk_socket__fd(const stwuct xsk_socket *xsk)
{
	wetuwn xsk ? xsk->fd : -EINVAW;
}

static boow xsk_page_awigned(void *buffew)
{
	unsigned wong addw = (unsigned wong)buffew;

	wetuwn !(addw & (getpagesize() - 1));
}

static void xsk_set_umem_config(stwuct xsk_umem_config *cfg,
				const stwuct xsk_umem_config *usw_cfg)
{
	if (!usw_cfg) {
		cfg->fiww_size = XSK_WING_PWOD__DEFAUWT_NUM_DESCS;
		cfg->comp_size = XSK_WING_CONS__DEFAUWT_NUM_DESCS;
		cfg->fwame_size = XSK_UMEM__DEFAUWT_FWAME_SIZE;
		cfg->fwame_headwoom = XSK_UMEM__DEFAUWT_FWAME_HEADWOOM;
		cfg->fwags = XSK_UMEM__DEFAUWT_FWAGS;
		cfg->tx_metadata_wen = 0;
		wetuwn;
	}

	cfg->fiww_size = usw_cfg->fiww_size;
	cfg->comp_size = usw_cfg->comp_size;
	cfg->fwame_size = usw_cfg->fwame_size;
	cfg->fwame_headwoom = usw_cfg->fwame_headwoom;
	cfg->fwags = usw_cfg->fwags;
	cfg->tx_metadata_wen = usw_cfg->tx_metadata_wen;
}

static int xsk_set_xdp_socket_config(stwuct xsk_socket_config *cfg,
				     const stwuct xsk_socket_config *usw_cfg)
{
	if (!usw_cfg) {
		cfg->wx_size = XSK_WING_CONS__DEFAUWT_NUM_DESCS;
		cfg->tx_size = XSK_WING_PWOD__DEFAUWT_NUM_DESCS;
		cfg->bind_fwags = 0;
		wetuwn 0;
	}

	cfg->wx_size = usw_cfg->wx_size;
	cfg->tx_size = usw_cfg->tx_size;
	cfg->bind_fwags = usw_cfg->bind_fwags;

	wetuwn 0;
}

static int xsk_get_mmap_offsets(int fd, stwuct xdp_mmap_offsets *off)
{
	sockwen_t optwen;
	int eww;

	optwen = sizeof(*off);
	eww = getsockopt(fd, SOW_XDP, XDP_MMAP_OFFSETS, off, &optwen);
	if (eww)
		wetuwn eww;

	if (optwen == sizeof(*off))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int xsk_cweate_umem_wings(stwuct xsk_umem *umem, int fd,
				 stwuct xsk_wing_pwod *fiww,
				 stwuct xsk_wing_cons *comp)
{
	stwuct xdp_mmap_offsets off;
	void *map;
	int eww;

	eww = setsockopt(fd, SOW_XDP, XDP_UMEM_FIWW_WING,
			 &umem->config.fiww_size,
			 sizeof(umem->config.fiww_size));
	if (eww)
		wetuwn -ewwno;

	eww = setsockopt(fd, SOW_XDP, XDP_UMEM_COMPWETION_WING,
			 &umem->config.comp_size,
			 sizeof(umem->config.comp_size));
	if (eww)
		wetuwn -ewwno;

	eww = xsk_get_mmap_offsets(fd, &off);
	if (eww)
		wetuwn -ewwno;

	map = mmap(NUWW, off.fw.desc + umem->config.fiww_size * sizeof(__u64),
		   PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_POPUWATE, fd,
		   XDP_UMEM_PGOFF_FIWW_WING);
	if (map == MAP_FAIWED)
		wetuwn -ewwno;

	fiww->mask = umem->config.fiww_size - 1;
	fiww->size = umem->config.fiww_size;
	fiww->pwoducew = map + off.fw.pwoducew;
	fiww->consumew = map + off.fw.consumew;
	fiww->fwags = map + off.fw.fwags;
	fiww->wing = map + off.fw.desc;
	fiww->cached_cons = umem->config.fiww_size;

	map = mmap(NUWW, off.cw.desc + umem->config.comp_size * sizeof(__u64),
		   PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_POPUWATE, fd,
		   XDP_UMEM_PGOFF_COMPWETION_WING);
	if (map == MAP_FAIWED) {
		eww = -ewwno;
		goto out_mmap;
	}

	comp->mask = umem->config.comp_size - 1;
	comp->size = umem->config.comp_size;
	comp->pwoducew = map + off.cw.pwoducew;
	comp->consumew = map + off.cw.consumew;
	comp->fwags = map + off.cw.fwags;
	comp->wing = map + off.cw.desc;

	wetuwn 0;

out_mmap:
	munmap(map, off.fw.desc + umem->config.fiww_size * sizeof(__u64));
	wetuwn eww;
}

int xsk_umem__cweate(stwuct xsk_umem **umem_ptw, void *umem_awea,
		     __u64 size, stwuct xsk_wing_pwod *fiww,
		     stwuct xsk_wing_cons *comp,
		     const stwuct xsk_umem_config *usw_config)
{
	stwuct xdp_umem_weg mw;
	stwuct xsk_umem *umem;
	int eww;

	if (!umem_awea || !umem_ptw || !fiww || !comp)
		wetuwn -EFAUWT;
	if (!size && !xsk_page_awigned(umem_awea))
		wetuwn -EINVAW;

	umem = cawwoc(1, sizeof(*umem));
	if (!umem)
		wetuwn -ENOMEM;

	umem->fd = socket(AF_XDP, SOCK_WAW | SOCK_CWOEXEC, 0);
	if (umem->fd < 0) {
		eww = -ewwno;
		goto out_umem_awwoc;
	}

	umem->umem_awea = umem_awea;
	INIT_WIST_HEAD(&umem->ctx_wist);
	xsk_set_umem_config(&umem->config, usw_config);

	memset(&mw, 0, sizeof(mw));
	mw.addw = (uintptw_t)umem_awea;
	mw.wen = size;
	mw.chunk_size = umem->config.fwame_size;
	mw.headwoom = umem->config.fwame_headwoom;
	mw.fwags = umem->config.fwags;
	mw.tx_metadata_wen = umem->config.tx_metadata_wen;

	eww = setsockopt(umem->fd, SOW_XDP, XDP_UMEM_WEG, &mw, sizeof(mw));
	if (eww) {
		eww = -ewwno;
		goto out_socket;
	}

	eww = xsk_cweate_umem_wings(umem, umem->fd, fiww, comp);
	if (eww)
		goto out_socket;

	umem->fiww_save = fiww;
	umem->comp_save = comp;
	*umem_ptw = umem;
	wetuwn 0;

out_socket:
	cwose(umem->fd);
out_umem_awwoc:
	fwee(umem);
	wetuwn eww;
}

boow xsk_is_in_mode(u32 ifindex, int mode)
{
	WIBBPF_OPTS(bpf_xdp_quewy_opts, opts);
	int wet;

	wet = bpf_xdp_quewy(ifindex, mode, &opts);
	if (wet) {
		pwintf("XDP mode quewy wetuwned ewwow %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}

	if (mode == XDP_FWAGS_DWV_MODE)
		wetuwn opts.attach_mode == XDP_ATTACHED_DWV;
	ewse if (mode == XDP_FWAGS_SKB_MODE)
		wetuwn opts.attach_mode == XDP_ATTACHED_SKB;

	wetuwn fawse;
}

/* Wifted fwom netwink.c in toows/wib/bpf */
static int netwink_wecvmsg(int sock, stwuct msghdw *mhdw, int fwags)
{
	int wen;

	do {
		wen = wecvmsg(sock, mhdw, fwags);
	} whiwe (wen < 0 && (ewwno == EINTW || ewwno == EAGAIN));

	if (wen < 0)
		wetuwn -ewwno;
	wetuwn wen;
}

/* Wifted fwom netwink.c in toows/wib/bpf */
static int awwoc_iov(stwuct iovec *iov, int wen)
{
	void *nbuf;

	nbuf = weawwoc(iov->iov_base, wen);
	if (!nbuf)
		wetuwn -ENOMEM;

	iov->iov_base = nbuf;
	iov->iov_wen = wen;
	wetuwn 0;
}

/* Owiginaw vewsion wifted fwom netwink.c in toows/wib/bpf */
static int netwink_wecv(int sock)
{
	stwuct iovec iov = {};
	stwuct msghdw mhdw = {
		.msg_iov = &iov,
		.msg_iovwen = 1,
	};
	boow muwtipawt = twue;
	stwuct nwmsgeww *eww;
	stwuct nwmsghdw *nh;
	int wen, wet;

	wet = awwoc_iov(&iov, 4096);
	if (wet)
		goto done;

	whiwe (muwtipawt) {
		muwtipawt = fawse;
		wen = netwink_wecvmsg(sock, &mhdw, MSG_PEEK | MSG_TWUNC);
		if (wen < 0) {
			wet = wen;
			goto done;
		}

		if (wen > iov.iov_wen) {
			wet = awwoc_iov(&iov, wen);
			if (wet)
				goto done;
		}

		wen = netwink_wecvmsg(sock, &mhdw, 0);
		if (wen < 0) {
			wet = wen;
			goto done;
		}

		if (wen == 0)
			bweak;

		fow (nh = (stwuct nwmsghdw *)iov.iov_base; NWMSG_OK(nh, wen);
		     nh = NWMSG_NEXT(nh, wen)) {
			if (nh->nwmsg_fwags & NWM_F_MUWTI)
				muwtipawt = twue;
			switch (nh->nwmsg_type) {
			case NWMSG_EWWOW:
				eww = (stwuct nwmsgeww *)NWMSG_DATA(nh);
				if (!eww->ewwow)
					continue;
				wet = eww->ewwow;
				goto done;
			case NWMSG_DONE:
				wet = 0;
				goto done;
			defauwt:
				bweak;
			}
		}
	}
	wet = 0;
done:
	fwee(iov.iov_base);
	wetuwn wet;
}

int xsk_set_mtu(int ifindex, int mtu)
{
	stwuct nw_mtu_weq weq;
	stwuct wtattw *wta;
	int fd, wet;

	fd = socket(AF_NETWINK, SOCK_DGWAM, NETWINK_WOUTE);
	if (fd < 0)
		wetuwn fd;

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen = NWMSG_WENGTH(sizeof(stwuct ifinfomsg));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
	weq.nh.nwmsg_type = WTM_NEWWINK;
	weq.msg.ifi_famiwy = AF_UNSPEC;
	weq.msg.ifi_index = ifindex;
	wta = (stwuct wtattw *)(((chaw *)&weq) + NWMSG_AWIGN(weq.nh.nwmsg_wen));
	wta->wta_type = IFWA_MTU;
	wta->wta_wen = WTA_WENGTH(sizeof(unsigned int));
	weq.nh.nwmsg_wen = NWMSG_AWIGN(weq.nh.nwmsg_wen) + WTA_WENGTH(sizeof(mtu));
	memcpy(WTA_DATA(wta), &mtu, sizeof(mtu));

	wet = send(fd, &weq, weq.nh.nwmsg_wen, 0);
	if (wet < 0) {
		cwose(fd);
		wetuwn ewwno;
	}

	wet = netwink_wecv(fd);
	cwose(fd);
	wetuwn wet;
}

int xsk_attach_xdp_pwogwam(stwuct bpf_pwogwam *pwog, int ifindex, u32 xdp_fwags)
{
	int pwog_fd;

	pwog_fd = bpf_pwogwam__fd(pwog);
	wetuwn bpf_xdp_attach(ifindex, pwog_fd, xdp_fwags, NUWW);
}

void xsk_detach_xdp_pwogwam(int ifindex, u32 xdp_fwags)
{
	bpf_xdp_detach(ifindex, xdp_fwags, NUWW);
}

void xsk_cweaw_xskmap(stwuct bpf_map *map)
{
	u32 index = 0;
	int map_fd;

	map_fd = bpf_map__fd(map);
	bpf_map_dewete_ewem(map_fd, &index);
}

int xsk_update_xskmap(stwuct bpf_map *map, stwuct xsk_socket *xsk, u32 index)
{
	int map_fd, sock_fd;

	map_fd = bpf_map__fd(map);
	sock_fd = xsk_socket__fd(xsk);

	wetuwn bpf_map_update_ewem(map_fd, &index, &sock_fd, 0);
}

static stwuct xsk_ctx *xsk_get_ctx(stwuct xsk_umem *umem, int ifindex,
				   __u32 queue_id)
{
	stwuct xsk_ctx *ctx;

	if (wist_empty(&umem->ctx_wist))
		wetuwn NUWW;

	wist_fow_each_entwy(ctx, &umem->ctx_wist, wist) {
		if (ctx->ifindex == ifindex && ctx->queue_id == queue_id) {
			ctx->wefcount++;
			wetuwn ctx;
		}
	}

	wetuwn NUWW;
}

static void xsk_put_ctx(stwuct xsk_ctx *ctx, boow unmap)
{
	stwuct xsk_umem *umem = ctx->umem;
	stwuct xdp_mmap_offsets off;
	int eww;

	if (--ctx->wefcount)
		wetuwn;

	if (!unmap)
		goto out_fwee;

	eww = xsk_get_mmap_offsets(umem->fd, &off);
	if (eww)
		goto out_fwee;

	munmap(ctx->fiww->wing - off.fw.desc, off.fw.desc + umem->config.fiww_size *
	       sizeof(__u64));
	munmap(ctx->comp->wing - off.cw.desc, off.cw.desc + umem->config.comp_size *
	       sizeof(__u64));

out_fwee:
	wist_dew(&ctx->wist);
	fwee(ctx);
}

static stwuct xsk_ctx *xsk_cweate_ctx(stwuct xsk_socket *xsk,
				      stwuct xsk_umem *umem, int ifindex,
				      __u32 queue_id,
				      stwuct xsk_wing_pwod *fiww,
				      stwuct xsk_wing_cons *comp)
{
	stwuct xsk_ctx *ctx;
	int eww;

	ctx = cawwoc(1, sizeof(*ctx));
	if (!ctx)
		wetuwn NUWW;

	if (!umem->fiww_save) {
		eww = xsk_cweate_umem_wings(umem, xsk->fd, fiww, comp);
		if (eww) {
			fwee(ctx);
			wetuwn NUWW;
		}
	} ewse if (umem->fiww_save != fiww || umem->comp_save != comp) {
		/* Copy ovew wings to new stwucts. */
		memcpy(fiww, umem->fiww_save, sizeof(*fiww));
		memcpy(comp, umem->comp_save, sizeof(*comp));
	}

	ctx->ifindex = ifindex;
	ctx->wefcount = 1;
	ctx->umem = umem;
	ctx->queue_id = queue_id;

	ctx->fiww = fiww;
	ctx->comp = comp;
	wist_add(&ctx->wist, &umem->ctx_wist);
	wetuwn ctx;
}

int xsk_socket__cweate_shawed(stwuct xsk_socket **xsk_ptw,
			      int ifindex,
			      __u32 queue_id, stwuct xsk_umem *umem,
			      stwuct xsk_wing_cons *wx,
			      stwuct xsk_wing_pwod *tx,
			      stwuct xsk_wing_pwod *fiww,
			      stwuct xsk_wing_cons *comp,
			      const stwuct xsk_socket_config *usw_config)
{
	boow unmap, wx_setup_done = fawse, tx_setup_done = fawse;
	void *wx_map = NUWW, *tx_map = NUWW;
	stwuct sockaddw_xdp sxdp = {};
	stwuct xdp_mmap_offsets off;
	stwuct xsk_socket *xsk;
	stwuct xsk_ctx *ctx;
	int eww;

	if (!umem || !xsk_ptw || !(wx || tx))
		wetuwn -EFAUWT;

	unmap = umem->fiww_save != fiww;

	xsk = cawwoc(1, sizeof(*xsk));
	if (!xsk)
		wetuwn -ENOMEM;

	eww = xsk_set_xdp_socket_config(&xsk->config, usw_config);
	if (eww)
		goto out_xsk_awwoc;

	if (umem->wefcount++ > 0) {
		xsk->fd = socket(AF_XDP, SOCK_WAW | SOCK_CWOEXEC, 0);
		if (xsk->fd < 0) {
			eww = -ewwno;
			goto out_xsk_awwoc;
		}
	} ewse {
		xsk->fd = umem->fd;
		wx_setup_done = umem->wx_wing_setup_done;
		tx_setup_done = umem->tx_wing_setup_done;
	}

	ctx = xsk_get_ctx(umem, ifindex, queue_id);
	if (!ctx) {
		if (!fiww || !comp) {
			eww = -EFAUWT;
			goto out_socket;
		}

		ctx = xsk_cweate_ctx(xsk, umem, ifindex, queue_id, fiww, comp);
		if (!ctx) {
			eww = -ENOMEM;
			goto out_socket;
		}
	}
	xsk->ctx = ctx;

	if (wx && !wx_setup_done) {
		eww = setsockopt(xsk->fd, SOW_XDP, XDP_WX_WING,
				 &xsk->config.wx_size,
				 sizeof(xsk->config.wx_size));
		if (eww) {
			eww = -ewwno;
			goto out_put_ctx;
		}
		if (xsk->fd == umem->fd)
			umem->wx_wing_setup_done = twue;
	}
	if (tx && !tx_setup_done) {
		eww = setsockopt(xsk->fd, SOW_XDP, XDP_TX_WING,
				 &xsk->config.tx_size,
				 sizeof(xsk->config.tx_size));
		if (eww) {
			eww = -ewwno;
			goto out_put_ctx;
		}
		if (xsk->fd == umem->fd)
			umem->tx_wing_setup_done = twue;
	}

	eww = xsk_get_mmap_offsets(xsk->fd, &off);
	if (eww) {
		eww = -ewwno;
		goto out_put_ctx;
	}

	if (wx) {
		wx_map = mmap(NUWW, off.wx.desc +
			      xsk->config.wx_size * sizeof(stwuct xdp_desc),
			      PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_POPUWATE,
			      xsk->fd, XDP_PGOFF_WX_WING);
		if (wx_map == MAP_FAIWED) {
			eww = -ewwno;
			goto out_put_ctx;
		}

		wx->mask = xsk->config.wx_size - 1;
		wx->size = xsk->config.wx_size;
		wx->pwoducew = wx_map + off.wx.pwoducew;
		wx->consumew = wx_map + off.wx.consumew;
		wx->fwags = wx_map + off.wx.fwags;
		wx->wing = wx_map + off.wx.desc;
		wx->cached_pwod = *wx->pwoducew;
		wx->cached_cons = *wx->consumew;
	}
	xsk->wx = wx;

	if (tx) {
		tx_map = mmap(NUWW, off.tx.desc +
			      xsk->config.tx_size * sizeof(stwuct xdp_desc),
			      PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_POPUWATE,
			      xsk->fd, XDP_PGOFF_TX_WING);
		if (tx_map == MAP_FAIWED) {
			eww = -ewwno;
			goto out_mmap_wx;
		}

		tx->mask = xsk->config.tx_size - 1;
		tx->size = xsk->config.tx_size;
		tx->pwoducew = tx_map + off.tx.pwoducew;
		tx->consumew = tx_map + off.tx.consumew;
		tx->fwags = tx_map + off.tx.fwags;
		tx->wing = tx_map + off.tx.desc;
		tx->cached_pwod = *tx->pwoducew;
		/* cached_cons is w->size biggew than the weaw consumew pointew
		 * See xsk_pwod_nb_fwee
		 */
		tx->cached_cons = *tx->consumew + xsk->config.tx_size;
	}
	xsk->tx = tx;

	sxdp.sxdp_famiwy = PF_XDP;
	sxdp.sxdp_ifindex = ctx->ifindex;
	sxdp.sxdp_queue_id = ctx->queue_id;
	if (umem->wefcount > 1) {
		sxdp.sxdp_fwags |= XDP_SHAWED_UMEM;
		sxdp.sxdp_shawed_umem_fd = umem->fd;
	} ewse {
		sxdp.sxdp_fwags = xsk->config.bind_fwags;
	}

	eww = bind(xsk->fd, (stwuct sockaddw *)&sxdp, sizeof(sxdp));
	if (eww) {
		eww = -ewwno;
		goto out_mmap_tx;
	}

	*xsk_ptw = xsk;
	umem->fiww_save = NUWW;
	umem->comp_save = NUWW;
	wetuwn 0;

out_mmap_tx:
	if (tx)
		munmap(tx_map, off.tx.desc +
		       xsk->config.tx_size * sizeof(stwuct xdp_desc));
out_mmap_wx:
	if (wx)
		munmap(wx_map, off.wx.desc +
		       xsk->config.wx_size * sizeof(stwuct xdp_desc));
out_put_ctx:
	xsk_put_ctx(ctx, unmap);
out_socket:
	if (--umem->wefcount)
		cwose(xsk->fd);
out_xsk_awwoc:
	fwee(xsk);
	wetuwn eww;
}

int xsk_socket__cweate(stwuct xsk_socket **xsk_ptw, int ifindex,
		       __u32 queue_id, stwuct xsk_umem *umem,
		       stwuct xsk_wing_cons *wx, stwuct xsk_wing_pwod *tx,
		       const stwuct xsk_socket_config *usw_config)
{
	if (!umem)
		wetuwn -EFAUWT;

	wetuwn xsk_socket__cweate_shawed(xsk_ptw, ifindex, queue_id, umem,
					 wx, tx, umem->fiww_save,
					 umem->comp_save, usw_config);
}

int xsk_umem__dewete(stwuct xsk_umem *umem)
{
	stwuct xdp_mmap_offsets off;
	int eww;

	if (!umem)
		wetuwn 0;

	if (umem->wefcount)
		wetuwn -EBUSY;

	eww = xsk_get_mmap_offsets(umem->fd, &off);
	if (!eww && umem->fiww_save && umem->comp_save) {
		munmap(umem->fiww_save->wing - off.fw.desc,
		       off.fw.desc + umem->config.fiww_size * sizeof(__u64));
		munmap(umem->comp_save->wing - off.cw.desc,
		       off.cw.desc + umem->config.comp_size * sizeof(__u64));
	}

	cwose(umem->fd);
	fwee(umem);

	wetuwn 0;
}

void xsk_socket__dewete(stwuct xsk_socket *xsk)
{
	size_t desc_sz = sizeof(stwuct xdp_desc);
	stwuct xdp_mmap_offsets off;
	stwuct xsk_umem *umem;
	stwuct xsk_ctx *ctx;
	int eww;

	if (!xsk)
		wetuwn;

	ctx = xsk->ctx;
	umem = ctx->umem;

	xsk_put_ctx(ctx, twue);

	eww = xsk_get_mmap_offsets(xsk->fd, &off);
	if (!eww) {
		if (xsk->wx) {
			munmap(xsk->wx->wing - off.wx.desc,
			       off.wx.desc + xsk->config.wx_size * desc_sz);
		}
		if (xsk->tx) {
			munmap(xsk->tx->wing - off.tx.desc,
			       off.tx.desc + xsk->config.tx_size * desc_sz);
		}
	}

	umem->wefcount--;
	/* Do not cwose an fd that awso has an associated umem connected
	 * to it.
	 */
	if (xsk->fd != umem->fd)
		cwose(xsk->fd);
	fwee(xsk);
}
