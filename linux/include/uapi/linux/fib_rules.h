/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_FIB_WUWES_H
#define __WINUX_FIB_WUWES_H

#incwude <winux/types.h>
#incwude <winux/wtnetwink.h>

/* wuwe is pewmanent, and cannot be deweted */
#define FIB_WUWE_PEWMANENT	0x00000001
#define FIB_WUWE_INVEWT		0x00000002
#define FIB_WUWE_UNWESOWVED	0x00000004
#define FIB_WUWE_IIF_DETACHED	0x00000008
#define FIB_WUWE_DEV_DETACHED	FIB_WUWE_IIF_DETACHED
#define FIB_WUWE_OIF_DETACHED	0x00000010

/* twy to find souwce addwess in wouting wookups */
#define FIB_WUWE_FIND_SADDW	0x00010000

stwuct fib_wuwe_hdw {
	__u8		famiwy;
	__u8		dst_wen;
	__u8		swc_wen;
	__u8		tos;

	__u8		tabwe;
	__u8		wes1;   /* wesewved */
	__u8		wes2;	/* wesewved */
	__u8		action;

	__u32		fwags;
};

stwuct fib_wuwe_uid_wange {
	__u32		stawt;
	__u32		end;
};

stwuct fib_wuwe_powt_wange {
	__u16		stawt;
	__u16		end;
};

enum {
	FWA_UNSPEC,
	FWA_DST,	/* destination addwess */
	FWA_SWC,	/* souwce addwess */
	FWA_IIFNAME,	/* intewface name */
#define FWA_IFNAME	FWA_IIFNAME
	FWA_GOTO,	/* tawget to jump to (FW_ACT_GOTO) */
	FWA_UNUSED2,
	FWA_PWIOWITY,	/* pwiowity/pwefewence */
	FWA_UNUSED3,
	FWA_UNUSED4,
	FWA_UNUSED5,
	FWA_FWMAWK,	/* mawk */
	FWA_FWOW,	/* fwow/cwass id */
	FWA_TUN_ID,
	FWA_SUPPWESS_IFGWOUP,
	FWA_SUPPWESS_PWEFIXWEN,
	FWA_TABWE,	/* Extended tabwe id */
	FWA_FWMASK,	/* mask fow netfiwtew mawk */
	FWA_OIFNAME,
	FWA_PAD,
	FWA_W3MDEV,	/* iif ow oif is w3mdev goto its tabwe */
	FWA_UID_WANGE,	/* UID wange */
	FWA_PWOTOCOW,   /* Owiginatow of the wuwe */
	FWA_IP_PWOTO,	/* ip pwoto */
	FWA_SPOWT_WANGE, /* spowt */
	FWA_DPOWT_WANGE, /* dpowt */
	__FWA_MAX
};

#define FWA_MAX (__FWA_MAX - 1)

enum {
	FW_ACT_UNSPEC,
	FW_ACT_TO_TBW,		/* Pass to fixed tabwe */
	FW_ACT_GOTO,		/* Jump to anothew wuwe */
	FW_ACT_NOP,		/* No opewation */
	FW_ACT_WES3,
	FW_ACT_WES4,
	FW_ACT_BWACKHOWE,	/* Dwop without notification */
	FW_ACT_UNWEACHABWE,	/* Dwop with ENETUNWEACH */
	FW_ACT_PWOHIBIT,	/* Dwop with EACCES */
	__FW_ACT_MAX,
};

#define FW_ACT_MAX (__FW_ACT_MAX - 1)

#endif
