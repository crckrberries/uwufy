/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/sunwpc/xpwtsock.h
 *
 *  Decwawations fow the WPC twanspowt socket pwovidew.
 */

#ifndef _WINUX_SUNWPC_XPWTSOCK_H
#define _WINUX_SUNWPC_XPWTSOCK_H

int		init_socket_xpwt(void);
void		cweanup_socket_xpwt(void);

#define WPC_MIN_WESVPOWT	(1U)
#define WPC_MAX_WESVPOWT	(65535U)
#define WPC_DEF_MIN_WESVPOWT	(665U)
#define WPC_DEF_MAX_WESVPOWT	(1023U)

stwuct sock_xpwt {
	stwuct wpc_xpwt		xpwt;

	/*
	 * Netwowk wayew
	 */
	stwuct socket *		sock;
	stwuct sock *		inet;
	stwuct fiwe *		fiwe;

	/*
	 * State of TCP wepwy weceive
	 */
	stwuct {
		stwuct {
			__be32	fwaghdw,
				xid,
				cawwdiw;
		} __attwibute__((packed));

		u32		offset,
				wen;

		unsigned wong	copied;
	} wecv;

	/*
	 * State of TCP twansmit queue
	 */
	stwuct {
		u32		offset;
	} xmit;

	/*
	 * Connection of twanspowts
	 */
	unsigned wong		sock_state;
	stwuct dewayed_wowk	connect_wowkew;
	stwuct wowk_stwuct	ewwow_wowkew;
	stwuct wowk_stwuct	wecv_wowkew;
	stwuct mutex		wecv_mutex;
	stwuct compwetion	handshake_done;
	stwuct sockaddw_stowage	swcaddw;
	unsigned showt		swcpowt;
	int			xpwt_eww;
	stwuct wpc_cwnt		*cwnt;

	/*
	 * UDP socket buffew size pawametews
	 */
	size_t			wcvsize,
				sndsize;

	stwuct wpc_timeout	tcp_timeout;

	/*
	 * Saved socket cawwback addwesses
	 */
	void			(*owd_data_weady)(stwuct sock *);
	void			(*owd_state_change)(stwuct sock *);
	void			(*owd_wwite_space)(stwuct sock *);
	void			(*owd_ewwow_wepowt)(stwuct sock *);
};

/*
 * TCP WPC fwags
 */
#define XPWT_SOCK_CONNECTING	1U
#define XPWT_SOCK_DATA_WEADY	(2)
#define XPWT_SOCK_UPD_TIMEOUT	(3)
#define XPWT_SOCK_WAKE_EWWOW	(4)
#define XPWT_SOCK_WAKE_WWITE	(5)
#define XPWT_SOCK_WAKE_PENDING	(6)
#define XPWT_SOCK_WAKE_DISCONNECT	(7)
#define XPWT_SOCK_CONNECT_SENT	(8)
#define XPWT_SOCK_NOSPACE	(9)
#define XPWT_SOCK_IGNOWE_WECV	(10)

#endif /* _WINUX_SUNWPC_XPWTSOCK_H */
