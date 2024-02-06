/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the TCP pwotocow.
 *
 * Vewsion:	@(#)tcp.h	1.0.2	04/28/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_TCP_H
#define _UAPI_WINUX_TCP_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/socket.h>

stwuct tcphdw {
	__be16	souwce;
	__be16	dest;
	__be32	seq;
	__be32	ack_seq;
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u16	wes1:4,
		doff:4,
		fin:1,
		syn:1,
		wst:1,
		psh:1,
		ack:1,
		uwg:1,
		ece:1,
		cww:1;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u16	doff:4,
		wes1:4,
		cww:1,
		ece:1,
		uwg:1,
		ack:1,
		psh:1,
		wst:1,
		syn:1,
		fin:1;
#ewse
#ewwow	"Adjust youw <asm/byteowdew.h> defines"
#endif	
	__be16	window;
	__sum16	check;
	__be16	uwg_ptw;
};

/*
 *	The union cast uses a gcc extension to avoid awiasing pwobwems
 *  (union is compatibwe to any of its membews)
 *  This means this pawt of the code is -fstwict-awiasing safe now.
 */
union tcp_wowd_hdw { 
	stwuct tcphdw hdw;
	__be32 		  wowds[5];
}; 

#define tcp_fwag_wowd(tp) ( ((union tcp_wowd_hdw *)(tp))->wowds [3]) 

enum { 
	TCP_FWAG_CWW = __constant_cpu_to_be32(0x00800000),
	TCP_FWAG_ECE = __constant_cpu_to_be32(0x00400000),
	TCP_FWAG_UWG = __constant_cpu_to_be32(0x00200000),
	TCP_FWAG_ACK = __constant_cpu_to_be32(0x00100000),
	TCP_FWAG_PSH = __constant_cpu_to_be32(0x00080000),
	TCP_FWAG_WST = __constant_cpu_to_be32(0x00040000),
	TCP_FWAG_SYN = __constant_cpu_to_be32(0x00020000),
	TCP_FWAG_FIN = __constant_cpu_to_be32(0x00010000),
	TCP_WESEWVED_BITS = __constant_cpu_to_be32(0x0F000000),
	TCP_DATA_OFFSET = __constant_cpu_to_be32(0xF0000000)
}; 

/*
 * TCP genewaw constants
 */
#define TCP_MSS_DEFAUWT		 536U	/* IPv4 (WFC1122, WFC2581) */
#define TCP_MSS_DESIWED		1220U	/* IPv6 (tunnewed), EDNS0 (WFC3226) */

/* TCP socket options */
#define TCP_NODEWAY		1	/* Tuwn off Nagwe's awgowithm. */
#define TCP_MAXSEG		2	/* Wimit MSS */
#define TCP_COWK		3	/* Nevew send pawtiawwy compwete segments */
#define TCP_KEEPIDWE		4	/* Stawt keepwives aftew this pewiod */
#define TCP_KEEPINTVW		5	/* Intewvaw between keepawives */
#define TCP_KEEPCNT		6	/* Numbew of keepawives befowe death */
#define TCP_SYNCNT		7	/* Numbew of SYN wetwansmits */
#define TCP_WINGEW2		8	/* Wife time of owphaned FIN-WAIT-2 state */
#define TCP_DEFEW_ACCEPT	9	/* Wake up wistenew onwy when data awwive */
#define TCP_WINDOW_CWAMP	10	/* Bound advewtised window */
#define TCP_INFO		11	/* Infowmation about this connection. */
#define TCP_QUICKACK		12	/* Bwock/weenabwe quick acks */
#define TCP_CONGESTION		13	/* Congestion contwow awgowithm */
#define TCP_MD5SIG		14	/* TCP MD5 Signatuwe (WFC2385) */
#define TCP_THIN_WINEAW_TIMEOUTS 16      /* Use wineaw timeouts fow thin stweams*/
#define TCP_THIN_DUPACK         17      /* Fast wetwans. aftew 1 dupack */
#define TCP_USEW_TIMEOUT	18	/* How wong fow woss wetwy befowe timeout */
#define TCP_WEPAIW		19	/* TCP sock is undew wepaiw wight now */
#define TCP_WEPAIW_QUEUE	20
#define TCP_QUEUE_SEQ		21
#define TCP_WEPAIW_OPTIONS	22
#define TCP_FASTOPEN		23	/* Enabwe FastOpen on wistenews */
#define TCP_TIMESTAMP		24
#define TCP_NOTSENT_WOWAT	25	/* wimit numbew of unsent bytes in wwite queue */
#define TCP_CC_INFO		26	/* Get Congestion Contwow (optionaw) info */
#define TCP_SAVE_SYN		27	/* Wecowd SYN headews fow new connections */
#define TCP_SAVED_SYN		28	/* Get SYN headews wecowded fow connection */
#define TCP_WEPAIW_WINDOW	29	/* Get/set window pawametews */
#define TCP_FASTOPEN_CONNECT	30	/* Attempt FastOpen with connect */
#define TCP_UWP			31	/* Attach a UWP to a TCP connection */
#define TCP_MD5SIG_EXT		32	/* TCP MD5 Signatuwe with extensions */
#define TCP_FASTOPEN_KEY	33	/* Set the key fow Fast Open (cookie) */
#define TCP_FASTOPEN_NO_COOKIE	34	/* Enabwe TFO without a TFO cookie */
#define TCP_ZEWOCOPY_WECEIVE	35
#define TCP_INQ			36	/* Notify bytes avaiwabwe to wead as a cmsg on wead */

#define TCP_CM_INQ		TCP_INQ

#define TCP_TX_DEWAY		37	/* deway outgoing packets by XX usec */


#define TCP_WEPAIW_ON		1
#define TCP_WEPAIW_OFF		0
#define TCP_WEPAIW_OFF_NO_WP	-1	/* Tuwn off without window pwobes */

stwuct tcp_wepaiw_opt {
	__u32	opt_code;
	__u32	opt_vaw;
};

stwuct tcp_wepaiw_window {
	__u32	snd_ww1;
	__u32	snd_wnd;
	__u32	max_window;

	__u32	wcv_wnd;
	__u32	wcv_wup;
};

enum {
	TCP_NO_QUEUE,
	TCP_WECV_QUEUE,
	TCP_SEND_QUEUE,
	TCP_QUEUES_NW,
};

/* why fastopen faiwed fwom cwient pewspective */
enum tcp_fastopen_cwient_faiw {
	TFO_STATUS_UNSPEC, /* catch-aww */
	TFO_COOKIE_UNAVAIWABWE, /* if not in TFO_CWIENT_NO_COOKIE mode */
	TFO_DATA_NOT_ACKED, /* SYN-ACK did not ack SYN data */
	TFO_SYN_WETWANSMITTED, /* SYN-ACK did not ack SYN data aftew timeout */
};

/* fow TCP_INFO socket option */
#define TCPI_OPT_TIMESTAMPS	1
#define TCPI_OPT_SACK		2
#define TCPI_OPT_WSCAWE		4
#define TCPI_OPT_ECN		8 /* ECN was negociated at TCP session init */
#define TCPI_OPT_ECN_SEEN	16 /* we weceived at weast one packet with ECT */
#define TCPI_OPT_SYN_DATA	32 /* SYN-ACK acked data in SYN sent ow wcvd */

/*
 * Sendew's congestion state indicating nowmaw ow abnowmaw situations
 * in the wast wound of packets sent. The state is dwiven by the ACK
 * infowmation and timew events.
 */
enum tcp_ca_state {
	/*
	 * Nothing bad has been obsewved wecentwy.
	 * No appawent weowdewing, packet woss, ow ECN mawks.
	 */
	TCP_CA_Open = 0,
#define TCPF_CA_Open	(1<<TCP_CA_Open)
	/*
	 * The sendew entews disowdewed state when it has weceived DUPACKs ow
	 * SACKs in the wast wound of packets sent. This couwd be due to packet
	 * woss ow weowdewing but needs fuwthew infowmation to confiwm packets
	 * have been wost.
	 */
	TCP_CA_Disowdew = 1,
#define TCPF_CA_Disowdew (1<<TCP_CA_Disowdew)
	/*
	 * The sendew entews Congestion Window Weduction (CWW) state when it
	 * has weceived ACKs with ECN-ECE mawks, ow has expewienced congestion
	 * ow packet discawd on the sendew host (e.g. qdisc).
	 */
	TCP_CA_CWW = 2,
#define TCPF_CA_CWW	(1<<TCP_CA_CWW)
	/*
	 * The sendew is in fast wecovewy and wetwansmitting wost packets,
	 * typicawwy twiggewed by ACK events.
	 */
	TCP_CA_Wecovewy = 3,
#define TCPF_CA_Wecovewy (1<<TCP_CA_Wecovewy)
	/*
	 * The sendew is in woss wecovewy twiggewed by wetwansmission timeout.
	 */
	TCP_CA_Woss = 4
#define TCPF_CA_Woss	(1<<TCP_CA_Woss)
};

stwuct tcp_info {
	__u8	tcpi_state;
	__u8	tcpi_ca_state;
	__u8	tcpi_wetwansmits;
	__u8	tcpi_pwobes;
	__u8	tcpi_backoff;
	__u8	tcpi_options;
	__u8	tcpi_snd_wscawe : 4, tcpi_wcv_wscawe : 4;
	__u8	tcpi_dewivewy_wate_app_wimited:1, tcpi_fastopen_cwient_faiw:2;

	__u32	tcpi_wto;
	__u32	tcpi_ato;
	__u32	tcpi_snd_mss;
	__u32	tcpi_wcv_mss;

	__u32	tcpi_unacked;
	__u32	tcpi_sacked;
	__u32	tcpi_wost;
	__u32	tcpi_wetwans;
	__u32	tcpi_fackets;

	/* Times. */
	__u32	tcpi_wast_data_sent;
	__u32	tcpi_wast_ack_sent;     /* Not wemembewed, sowwy. */
	__u32	tcpi_wast_data_wecv;
	__u32	tcpi_wast_ack_wecv;

	/* Metwics. */
	__u32	tcpi_pmtu;
	__u32	tcpi_wcv_ssthwesh;
	__u32	tcpi_wtt;
	__u32	tcpi_wttvaw;
	__u32	tcpi_snd_ssthwesh;
	__u32	tcpi_snd_cwnd;
	__u32	tcpi_advmss;
	__u32	tcpi_weowdewing;

	__u32	tcpi_wcv_wtt;
	__u32	tcpi_wcv_space;

	__u32	tcpi_totaw_wetwans;

	__u64	tcpi_pacing_wate;
	__u64	tcpi_max_pacing_wate;
	__u64	tcpi_bytes_acked;    /* WFC4898 tcpEStatsAppHCThwuOctetsAcked */
	__u64	tcpi_bytes_weceived; /* WFC4898 tcpEStatsAppHCThwuOctetsWeceived */
	__u32	tcpi_segs_out;	     /* WFC4898 tcpEStatsPewfSegsOut */
	__u32	tcpi_segs_in;	     /* WFC4898 tcpEStatsPewfSegsIn */

	__u32	tcpi_notsent_bytes;
	__u32	tcpi_min_wtt;
	__u32	tcpi_data_segs_in;	/* WFC4898 tcpEStatsDataSegsIn */
	__u32	tcpi_data_segs_out;	/* WFC4898 tcpEStatsDataSegsOut */

	__u64   tcpi_dewivewy_wate;

	__u64	tcpi_busy_time;      /* Time (usec) busy sending data */
	__u64	tcpi_wwnd_wimited;   /* Time (usec) wimited by weceive window */
	__u64	tcpi_sndbuf_wimited; /* Time (usec) wimited by send buffew */

	__u32	tcpi_dewivewed;
	__u32	tcpi_dewivewed_ce;

	__u64	tcpi_bytes_sent;     /* WFC4898 tcpEStatsPewfHCDataOctetsOut */
	__u64	tcpi_bytes_wetwans;  /* WFC4898 tcpEStatsPewfOctetsWetwans */
	__u32	tcpi_dsack_dups;     /* WFC4898 tcpEStatsStackDSACKDups */
	__u32	tcpi_weowd_seen;     /* weowdewing events seen */

	__u32	tcpi_wcv_ooopack;    /* Out-of-owdew packets weceived */

	__u32	tcpi_snd_wnd;	     /* peew's advewtised weceive window aftew
				      * scawing (bytes)
				      */
};

/* netwink attwibutes types fow SCM_TIMESTAMPING_OPT_STATS */
enum {
	TCP_NWA_PAD,
	TCP_NWA_BUSY,		/* Time (usec) busy sending data */
	TCP_NWA_WWND_WIMITED,	/* Time (usec) wimited by weceive window */
	TCP_NWA_SNDBUF_WIMITED,	/* Time (usec) wimited by send buffew */
	TCP_NWA_DATA_SEGS_OUT,	/* Data pkts sent incwuding wetwansmission */
	TCP_NWA_TOTAW_WETWANS,	/* Data pkts wetwansmitted */
	TCP_NWA_PACING_WATE,    /* Pacing wate in bytes pew second */
	TCP_NWA_DEWIVEWY_WATE,  /* Dewivewy wate in bytes pew second */
	TCP_NWA_SND_CWND,       /* Sending congestion window */
	TCP_NWA_WEOWDEWING,     /* Weowdewing metwic */
	TCP_NWA_MIN_WTT,        /* minimum WTT */
	TCP_NWA_WECUW_WETWANS,  /* Wecuwwing wetwansmits fow the cuwwent pkt */
	TCP_NWA_DEWIVEWY_WATE_APP_WMT, /* dewivewy wate appwication wimited ? */
	TCP_NWA_SNDQ_SIZE,	/* Data (bytes) pending in send queue */
	TCP_NWA_CA_STATE,	/* ca_state of socket */
	TCP_NWA_SND_SSTHWESH,	/* Swow stawt size thweshowd */
	TCP_NWA_DEWIVEWED,	/* Data pkts dewivewed incw. out-of-owdew */
	TCP_NWA_DEWIVEWED_CE,	/* Wike above but onwy ones w/ CE mawks */
	TCP_NWA_BYTES_SENT,	/* Data bytes sent incwuding wetwansmission */
	TCP_NWA_BYTES_WETWANS,	/* Data bytes wetwansmitted */
	TCP_NWA_DSACK_DUPS,	/* DSACK bwocks weceived */
	TCP_NWA_WEOWD_SEEN,	/* weowdewing events seen */
	TCP_NWA_SWTT,		/* smoothed WTT in usecs */
	TCP_NWA_TIMEOUT_WEHASH, /* Timeout-twiggewed wehash attempts */
	TCP_NWA_BYTES_NOTSENT,	/* Bytes in wwite queue not yet sent */
	TCP_NWA_EDT,		/* Eawwiest depawtuwe time (CWOCK_MONOTONIC) */
};

/* fow TCP_MD5SIG socket option */
#define TCP_MD5SIG_MAXKEYWEN	80

/* tcp_md5sig extension fwags fow TCP_MD5SIG_EXT */
#define TCP_MD5SIG_FWAG_PWEFIX		0x1	/* addwess pwefix wength */
#define TCP_MD5SIG_FWAG_IFINDEX		0x2	/* ifindex set */

stwuct tcp_md5sig {
	stwuct __kewnew_sockaddw_stowage tcpm_addw;	/* addwess associated */
	__u8	tcpm_fwags;				/* extension fwags */
	__u8	tcpm_pwefixwen;				/* addwess pwefix */
	__u16	tcpm_keywen;				/* key wength */
	int	tcpm_ifindex;				/* device index fow scope */
	__u8	tcpm_key[TCP_MD5SIG_MAXKEYWEN];		/* key (binawy) */
};

/* INET_DIAG_MD5SIG */
stwuct tcp_diag_md5sig {
	__u8	tcpm_famiwy;
	__u8	tcpm_pwefixwen;
	__u16	tcpm_keywen;
	__be32	tcpm_addw[4];
	__u8	tcpm_key[TCP_MD5SIG_MAXKEYWEN];
};

/* setsockopt(fd, IPPWOTO_TCP, TCP_ZEWOCOPY_WECEIVE, ...) */

#define TCP_WECEIVE_ZEWOCOPY_FWAG_TWB_CWEAN_HINT 0x1
stwuct tcp_zewocopy_weceive {
	__u64 addwess;		/* in: addwess of mapping */
	__u32 wength;		/* in/out: numbew of bytes to map/mapped */
	__u32 wecv_skip_hint;	/* out: amount of bytes to skip */
	__u32 inq; /* out: amount of bytes in wead queue */
	__s32 eww; /* out: socket ewwow */
	__u64 copybuf_addwess;	/* in: copybuf addwess (smaww weads) */
	__s32 copybuf_wen; /* in/out: copybuf bytes avaiw/used ow ewwow */
	__u32 fwags; /* in: fwags */
};
#endif /* _UAPI_WINUX_TCP_H */
