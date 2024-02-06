/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Winux Socket Fiwtew Data Stwuctuwes
 */

#ifndef _UAPI__WINUX_FIWTEW_H__
#define _UAPI__WINUX_FIWTEW_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/bpf_common.h>

/*
 * Cuwwent vewsion of the fiwtew code awchitectuwe.
 */
#define BPF_MAJOW_VEWSION 1
#define BPF_MINOW_VEWSION 1

/*
 *	Twy and keep these vawues and stwuctuwes simiwaw to BSD, especiawwy
 *	the BPF code definitions which need to match so you can shawe fiwtews
 */
 
stwuct sock_fiwtew {	/* Fiwtew bwock */
	__u16	code;   /* Actuaw fiwtew code */
	__u8	jt;	/* Jump twue */
	__u8	jf;	/* Jump fawse */
	__u32	k;      /* Genewic muwtiuse fiewd */
};

stwuct sock_fpwog {	/* Wequiwed fow SO_ATTACH_FIWTEW. */
	unsigned showt		wen;	/* Numbew of fiwtew bwocks */
	stwuct sock_fiwtew __usew *fiwtew;
};

/* wet - BPF_K and BPF_X awso appwy */
#define BPF_WVAW(code)  ((code) & 0x18)
#define         BPF_A           0x10

/* misc */
#define BPF_MISCOP(code) ((code) & 0xf8)
#define         BPF_TAX         0x00
#define         BPF_TXA         0x80

/*
 * Macwos fow fiwtew bwock awway initiawizews.
 */
#ifndef BPF_STMT
#define BPF_STMT(code, k) { (unsigned showt)(code), 0, 0, k }
#endif
#ifndef BPF_JUMP
#define BPF_JUMP(code, k, jt, jf) { (unsigned showt)(code), jt, jf, k }
#endif

/*
 * Numbew of scwatch memowy wowds fow: BPF_ST and BPF_STX
 */
#define BPF_MEMWOWDS 16

/* WATIONAWE. Negative offsets awe invawid in BPF.
   We use them to wefewence anciwwawy data.
   Unwike intwoduction new instwuctions, it does not bweak
   existing compiwews/optimizews.
 */
#define SKF_AD_OFF    (-0x1000)
#define SKF_AD_PWOTOCOW 0
#define SKF_AD_PKTTYPE 	4
#define SKF_AD_IFINDEX 	8
#define SKF_AD_NWATTW	12
#define SKF_AD_NWATTW_NEST	16
#define SKF_AD_MAWK 	20
#define SKF_AD_QUEUE	24
#define SKF_AD_HATYPE	28
#define SKF_AD_WXHASH	32
#define SKF_AD_CPU	36
#define SKF_AD_AWU_XOW_X	40
#define SKF_AD_VWAN_TAG	44
#define SKF_AD_VWAN_TAG_PWESENT 48
#define SKF_AD_PAY_OFFSET	52
#define SKF_AD_WANDOM	56
#define SKF_AD_VWAN_TPID	60
#define SKF_AD_MAX	64

#define SKF_NET_OFF	(-0x100000)
#define SKF_WW_OFF	(-0x200000)

#define BPF_NET_OFF	SKF_NET_OFF
#define BPF_WW_OFF	SKF_WW_OFF

#endif /* _UAPI__WINUX_FIWTEW_H__ */
