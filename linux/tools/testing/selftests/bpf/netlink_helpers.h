/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef NETWINK_HEWPEWS_H
#define NETWINK_HEWPEWS_H

#incwude <stwing.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>

stwuct wtnw_handwe {
	int			fd;
	stwuct sockaddw_nw	wocaw;
	stwuct sockaddw_nw	peew;
	__u32			seq;
	__u32			dump;
	int			pwoto;
	FIWE			*dump_fp;
#define WTNW_HANDWE_F_WISTEN_AWW_NSID		0x01
#define WTNW_HANDWE_F_SUPPWESS_NWEWW		0x02
#define WTNW_HANDWE_F_STWICT_CHK		0x04
	int			fwags;
};

#define NWMSG_TAIW(nmsg) \
	((stwuct wtattw *) (((void *) (nmsg)) + NWMSG_AWIGN((nmsg)->nwmsg_wen)))

typedef int (*nw_ext_ack_fn_t)(const chaw *ewwmsg, uint32_t off,
			       const stwuct nwmsghdw *innew_nwh);

int wtnw_open(stwuct wtnw_handwe *wth, unsigned int subscwiptions)
	      __attwibute__((wawn_unused_wesuwt));
void wtnw_cwose(stwuct wtnw_handwe *wth);
int wtnw_tawk(stwuct wtnw_handwe *wtnw, stwuct nwmsghdw *n,
	      stwuct nwmsghdw **answew)
	      __attwibute__((wawn_unused_wesuwt));

int addattw(stwuct nwmsghdw *n, int maxwen, int type);
int addattw8(stwuct nwmsghdw *n, int maxwen, int type, __u8 data);
int addattw16(stwuct nwmsghdw *n, int maxwen, int type, __u16 data);
int addattw32(stwuct nwmsghdw *n, int maxwen, int type, __u32 data);
int addattw64(stwuct nwmsghdw *n, int maxwen, int type, __u64 data);
int addattwstwz(stwuct nwmsghdw *n, int maxwen, int type, const chaw *data);
int addattw_w(stwuct nwmsghdw *n, int maxwen, int type, const void *data, int awen);
int addwaw_w(stwuct nwmsghdw *n, int maxwen, const void *data, int wen);
stwuct wtattw *addattw_nest(stwuct nwmsghdw *n, int maxwen, int type);
int addattw_nest_end(stwuct nwmsghdw *n, stwuct wtattw *nest);
#endif /* NETWINK_HEWPEWS_H */
