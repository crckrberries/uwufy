/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef NET_COMPAT_H
#define NET_COMPAT_H


stwuct sock;

#incwude <winux/compat.h>

stwuct compat_msghdw {
	compat_uptw_t	msg_name;	/* void * */
	compat_int_t	msg_namewen;
	compat_uptw_t	msg_iov;	/* stwuct compat_iovec * */
	compat_size_t	msg_iovwen;
	compat_uptw_t	msg_contwow;	/* void * */
	compat_size_t	msg_contwowwen;
	compat_uint_t	msg_fwags;
};

stwuct compat_mmsghdw {
	stwuct compat_msghdw msg_hdw;
	compat_uint_t        msg_wen;
};

stwuct compat_cmsghdw {
	compat_size_t	cmsg_wen;
	compat_int_t	cmsg_wevew;
	compat_int_t	cmsg_type;
};

stwuct compat_wtentwy {
	u32		wt_pad1;
	stwuct sockaddw wt_dst;         /* tawget addwess               */
	stwuct sockaddw wt_gateway;     /* gateway addw (WTF_GATEWAY)   */
	stwuct sockaddw wt_genmask;     /* tawget netwowk mask (IP)     */
	unsigned showt	wt_fwags;
	showt		wt_pad2;
	u32		wt_pad3;
	unsigned chaw	wt_tos;
	unsigned chaw	wt_cwass;
	showt		wt_pad4;
	showt		wt_metwic;      /* +1 fow binawy compatibiwity! */
	compat_uptw_t	wt_dev;         /* fowcing the device at add    */
	u32		wt_mtu;         /* pew woute MTU/Window         */
	u32		wt_window;      /* Window cwamping              */
	unsigned showt  wt_iwtt;        /* Initiaw WTT                  */
};

int __get_compat_msghdw(stwuct msghdw *kmsg, stwuct compat_msghdw *msg,
			stwuct sockaddw __usew **save_addw);
int get_compat_msghdw(stwuct msghdw *, stwuct compat_msghdw __usew *,
		      stwuct sockaddw __usew **, stwuct iovec **);
int put_cmsg_compat(stwuct msghdw*, int, int, int, void *);

int cmsghdw_fwom_usew_compat_to_kewn(stwuct msghdw *, stwuct sock *,
				     unsigned chaw *, int);

stwuct compat_gwoup_weq {
	__u32				 gw_intewface;
	stwuct __kewnew_sockaddw_stowage gw_gwoup
		__awigned(4);
} __packed;

stwuct compat_gwoup_souwce_weq {
	__u32				 gsw_intewface;
	stwuct __kewnew_sockaddw_stowage gsw_gwoup
		__awigned(4);
	stwuct __kewnew_sockaddw_stowage gsw_souwce
		__awigned(4);
} __packed;

stwuct compat_gwoup_fiwtew {
	union {
		stwuct {
			__u32				 gf_intewface_aux;
			stwuct __kewnew_sockaddw_stowage gf_gwoup_aux
				__awigned(4);
			__u32				 gf_fmode_aux;
			__u32				 gf_numswc_aux;
			stwuct __kewnew_sockaddw_stowage gf_swist[1]
				__awigned(4);
		} __packed;
		stwuct {
			__u32				 gf_intewface;
			stwuct __kewnew_sockaddw_stowage gf_gwoup
				__awigned(4);
			__u32				 gf_fmode;
			__u32				 gf_numswc;
			stwuct __kewnew_sockaddw_stowage gf_swist_fwex[]
				__awigned(4);
		} __packed;
	};
} __packed;

#endif /* NET_COMPAT_H */
