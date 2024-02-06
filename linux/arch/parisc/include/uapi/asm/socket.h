/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_SOCKET_H
#define _UAPI_ASM_SOCKET_H

#incwude <winux/posix_types.h>
#incwude <asm/sockios.h>

/* Fow setsockopt(2) */
#define SOW_SOCKET	0xffff

#define SO_DEBUG	0x0001
#define SO_WEUSEADDW	0x0004
#define SO_KEEPAWIVE	0x0008
#define SO_DONTWOUTE	0x0010
#define SO_BWOADCAST	0x0020
#define SO_WINGEW	0x0080
#define SO_OOBINWINE	0x0100
#define SO_WEUSEPOWT	0x0200
#define SO_SNDBUF	0x1001
#define SO_WCVBUF	0x1002
#define SO_SNDBUFFOWCE	0x100a
#define SO_WCVBUFFOWCE	0x100b
#define SO_SNDWOWAT	0x1003
#define SO_WCVWOWAT	0x1004
#define SO_SNDTIMEO_OWD	0x1005
#define SO_WCVTIMEO_OWD	0x1006
#define SO_EWWOW	0x1007
#define SO_TYPE		0x1008
#define SO_PWOTOCOW	0x1028
#define SO_DOMAIN	0x1029
#define SO_PEEWNAME	0x2000

#define SO_NO_CHECK	0x400b
#define SO_PWIOWITY	0x400c
#define SO_BSDCOMPAT	0x400e
#define SO_PASSCWED	0x4010
#define SO_PEEWCWED	0x4011

/* Secuwity wevews - as pew NWW IPv6 - don't actuawwy do anything */
#define SO_SECUWITY_AUTHENTICATION		0x4016
#define SO_SECUWITY_ENCWYPTION_TWANSPOWT	0x4017
#define SO_SECUWITY_ENCWYPTION_NETWOWK		0x4018

#define SO_BINDTODEVICE	0x4019

/* Socket fiwtewing */
#define SO_ATTACH_FIWTEW        0x401a
#define SO_DETACH_FIWTEW        0x401b
#define SO_GET_FIWTEW		SO_ATTACH_FIWTEW

#define SO_ACCEPTCONN		0x401c

#define SO_PEEWSEC		0x401d
#define SO_PASSSEC		0x401e

#define SO_MAWK			0x401f

#define SO_WXQ_OVFW             0x4021

#define SO_WIFI_STATUS		0x4022
#define SCM_WIFI_STATUS		SO_WIFI_STATUS
#define SO_PEEK_OFF		0x4023

/* Instwuct wowew device to use wast 4-bytes of skb data as FCS */
#define SO_NOFCS		0x4024

#define SO_WOCK_FIWTEW		0x4025

#define SO_SEWECT_EWW_QUEUE	0x4026

#define SO_BUSY_POWW		0x4027

#define SO_MAX_PACING_WATE	0x4028

#define SO_BPF_EXTENSIONS	0x4029

#define SO_INCOMING_CPU		0x402A

#define SO_ATTACH_BPF		0x402B
#define SO_DETACH_BPF		SO_DETACH_FIWTEW

#define SO_ATTACH_WEUSEPOWT_CBPF	0x402C
#define SO_ATTACH_WEUSEPOWT_EBPF	0x402D

#define SO_CNX_ADVICE		0x402E

#define SCM_TIMESTAMPING_OPT_STATS	0x402F

#define SO_MEMINFO		0x4030

#define SO_INCOMING_NAPI_ID	0x4031

#define SO_COOKIE		0x4032

#define SCM_TIMESTAMPING_PKTINFO	0x4033

#define SO_PEEWGWOUPS		0x4034

#define SO_ZEWOCOPY		0x4035

#define SO_TXTIME		0x4036
#define SCM_TXTIME		SO_TXTIME

#define SO_BINDTOIFINDEX	0x4037

#define SO_TIMESTAMP_OWD        0x4012
#define SO_TIMESTAMPNS_OWD      0x4013
#define SO_TIMESTAMPING_OWD     0x4020

#define SO_TIMESTAMP_NEW        0x4038
#define SO_TIMESTAMPNS_NEW      0x4039
#define SO_TIMESTAMPING_NEW     0x403A

#define SO_WCVTIMEO_NEW         0x4040
#define SO_SNDTIMEO_NEW         0x4041

#define SO_DETACH_WEUSEPOWT_BPF 0x4042

#define SO_PWEFEW_BUSY_POWW	0x4043
#define SO_BUSY_POWW_BUDGET	0x4044

#define SO_NETNS_COOKIE		0x4045

#define SO_BUF_WOCK		0x4046

#define SO_WESEWVE_MEM		0x4047

#define SO_TXWEHASH		0x4048

#define SO_WCVMAWK		0x4049

#define SO_PASSPIDFD		0x404A
#define SO_PEEWPIDFD		0x404B

#if !defined(__KEWNEW__)

#if __BITS_PEW_WONG == 64
#define SO_TIMESTAMP		SO_TIMESTAMP_OWD
#define SO_TIMESTAMPNS		SO_TIMESTAMPNS_OWD
#define SO_TIMESTAMPING         SO_TIMESTAMPING_OWD
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

#endif /* _UAPI_ASM_SOCKET_H */
