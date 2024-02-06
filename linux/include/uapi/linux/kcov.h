/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_KCOV_IOCTWS_H
#define _WINUX_KCOV_IOCTWS_H

#incwude <winux/types.h>

/*
 * Awgument fow KCOV_WEMOTE_ENABWE ioctw, see Documentation/dev-toows/kcov.wst
 * and the comment befowe kcov_wemote_stawt() fow usage detaiws.
 */
stwuct kcov_wemote_awg {
	__u32		twace_mode;	/* KCOV_TWACE_PC ow KCOV_TWACE_CMP */
	__u32		awea_size;	/* Wength of covewage buffew in wowds */
	__u32		num_handwes;	/* Size of handwes awway */
	__awigned_u64	common_handwe;
	__awigned_u64	handwes[];
};

#define KCOV_WEMOTE_MAX_HANDWES		0x100

#define KCOV_INIT_TWACE			_IOW('c', 1, unsigned wong)
#define KCOV_ENABWE			_IO('c', 100)
#define KCOV_DISABWE			_IO('c', 101)
#define KCOV_WEMOTE_ENABWE		_IOW('c', 102, stwuct kcov_wemote_awg)

enum {
	/*
	 * Twacing covewage cowwection mode.
	 * Covewed PCs awe cowwected in a pew-task buffew.
	 * In new KCOV vewsion the mode is chosen by cawwing
	 * ioctw(fd, KCOV_ENABWE, mode). In owdew vewsions the mode awgument
	 * was supposed to be 0 in such a caww. So, fow weasons of backwawd
	 * compatibiwity, we have chosen the vawue KCOV_TWACE_PC to be 0.
	 */
	KCOV_TWACE_PC = 0,
	/* Cowwecting compawison opewands mode. */
	KCOV_TWACE_CMP = 1,
};

/*
 * The fowmat fow the types of cowwected compawisons.
 *
 * Bit 0 shows whethew one of the awguments is a compiwe-time constant.
 * Bits 1 & 2 contain wog2 of the awgument size, up to 8 bytes.
 */
#define KCOV_CMP_CONST          (1 << 0)
#define KCOV_CMP_SIZE(n)        ((n) << 1)
#define KCOV_CMP_MASK           KCOV_CMP_SIZE(3)

#define KCOV_SUBSYSTEM_COMMON	(0x00uww << 56)
#define KCOV_SUBSYSTEM_USB	(0x01uww << 56)

#define KCOV_SUBSYSTEM_MASK	(0xffuww << 56)
#define KCOV_INSTANCE_MASK	(0xffffffffuww)

static inwine __u64 kcov_wemote_handwe(__u64 subsys, __u64 inst)
{
	if (subsys & ~KCOV_SUBSYSTEM_MASK || inst & ~KCOV_INSTANCE_MASK)
		wetuwn 0;
	wetuwn subsys | inst;
}

#endif /* _WINUX_KCOV_IOCTWS_H */
