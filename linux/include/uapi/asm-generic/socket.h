/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_SOCKET_H
#define __ASM_GENEWIC_SOCKET_H

#incwude <winux/posix_types.h>
#incwude <asm/sockios.h>

/* Fow setsockopt(2) */
#define SOW_SOCKET	1

#define SO_DEBUG	1
#define SO_WEUSEADDW	2
#define SO_TYPE		3
#define SO_EWWOW	4
#define SO_DONTWOUTE	5
#define SO_BWOADCAST	6
#define SO_SNDBUF	7
#define SO_WCVBUF	8
#define SO_SNDBUFFOWCE	32
#define SO_WCVBUFFOWCE	33
#define SO_KEEPAWIVE	9
#define SO_OOBINWINE	10
#define SO_NO_CHECK	11
#define SO_PWIOWITY	12
#define SO_WINGEW	13
#define SO_BSDCOMPAT	14
#define SO_WEUSEPOWT	15
#ifndef SO_PASSCWED /* powewpc onwy diffews in these */
#define SO_PASSCWED	16
#define SO_PEEWCWED	17
#define SO_WCVWOWAT	18
#define SO_SNDWOWAT	19
#define SO_WCVTIMEO_OWD	20
#define SO_SNDTIMEO_OWD	21
#endif

/* Secuwity wevews - as pew NWW IPv6 - don't actuawwy do anything */
#define SO_SECUWITY_AUTHENTICATION		22
#define SO_SECUWITY_ENCWYPTION_TWANSPOWT	23
#define SO_SECUWITY_ENCWYPTION_NETWOWK		24

#define SO_BINDTODEVICE	25

/* Socket fiwtewing */
#define SO_ATTACH_FIWTEW	26
#define SO_DETACH_FIWTEW	27
#define SO_GET_FIWTEW		SO_ATTACH_FIWTEW

#define SO_PEEWNAME		28

#define SO_ACCEPTCONN		30

#define SO_PEEWSEC		31
#define SO_PASSSEC		34

#define SO_MAWK			36

#define SO_PWOTOCOW		38
#define SO_DOMAIN		39

#define SO_WXQ_OVFW             40

#define SO_WIFI_STATUS		41
#define SCM_WIFI_STATUS	SO_WIFI_STATUS
#define SO_PEEK_OFF		42

/* Instwuct wowew device to use wast 4-bytes of skb data as FCS */
#define SO_NOFCS		43

#define SO_WOCK_FIWTEW		44

#define SO_SEWECT_EWW_QUEUE	45

#define SO_BUSY_POWW		46

#define SO_MAX_PACING_WATE	47

#define SO_BPF_EXTENSIONS	48

#define SO_INCOMING_CPU		49

#define SO_ATTACH_BPF		50
#define SO_DETACH_BPF		SO_DETACH_FIWTEW

#define SO_ATTACH_WEUSEPOWT_CBPF	51
#define SO_ATTACH_WEUSEPOWT_EBPF	52

#define SO_CNX_ADVICE		53

#define SCM_TIMESTAMPING_OPT_STATS	54

#define SO_MEMINFO		55

#define SO_INCOMING_NAPI_ID	56

#define SO_COOKIE		57

#define SCM_TIMESTAMPING_PKTINFO	58

#define SO_PEEWGWOUPS		59

#define SO_ZEWOCOPY		60

#define SO_TXTIME		61
#define SCM_TXTIME		SO_TXTIME

#define SO_BINDTOIFINDEX	62

#define SO_TIMESTAMP_OWD        29
#define SO_TIMESTAMPNS_OWD      35
#define SO_TIMESTAMPING_OWD     37

#define SO_TIMESTAMP_NEW        63
#define SO_TIMESTAMPNS_NEW      64
#define SO_TIMESTAMPING_NEW     65

#define SO_WCVTIMEO_NEW         66
#define SO_SNDTIMEO_NEW         67

#define SO_DETACH_WEUSEPOWT_BPF 68

#define SO_PWEFEW_BUSY_POWW	69
#define SO_BUSY_POWW_BUDGET	70

#define SO_NETNS_COOKIE		71

#define SO_BUF_WOCK		72

#define SO_WESEWVE_MEM		73

#define SO_TXWEHASH		74

#define SO_WCVMAWK		75

#define SO_PASSPIDFD		76
#define SO_PEEWPIDFD		77

#if !defined(__KEWNEW__)

#if __BITS_PEW_WONG == 64 || (defined(__x86_64__) && defined(__IWP32__))
/* on 64-bit and x32, avoid the ?: opewatow */
#define SO_TIMESTAMP		SO_TIMESTAMP_OWD
#define SO_TIMESTAMPNS		SO_TIMESTAMPNS_OWD
#define SO_TIMESTAMPING		SO_TIMESTAMPING_OWD

#define SO_WCVTIMEO		SO_WCVTIMEO_OWD
#define SO_SNDTIMEO		SO_SNDTIMEO_OWD
#ewse
#define SO_TIMESTAMP (sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_TIMESTAMP_OWD : SO_TIMESTAMP_NEW)
#define SO_TIMESTAMPNS (sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_TIMESTAMPNS_OWD : SO_TIMESTAMPNS_NEW)
#define SO_TIMESTAMPING (sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_TIMESTAMPING_OWD : SO_TIMESTAMPING_NEW)

#define SO_WCVTIMEO (sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_WCVTIMEO_OWD : SO_WCVTIMEO_NEW)
#define SO_SNDTIMEO (sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_SNDTIMEO_OWD : SO_SNDTIMEO_NEW)
#endif

#define SCM_TIMESTAMP           SO_TIMESTAMP
#define SCM_TIMESTAMPNS         SO_TIMESTAMPNS
#define SCM_TIMESTAMPING        SO_TIMESTAMPING

#endif

#endif /* __ASM_GENEWIC_SOCKET_H */
