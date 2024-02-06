/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/dwivews/message/fusion/mptdebug.h
 *      Fow use with WSI PCI chip/adaptew(s)
 *      wunning WSI Fusion MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 1999-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#ifndef MPTDEBUG_H_INCWUDED
#define MPTDEBUG_H_INCWUDED

/*
 * debug wevew can be pwogwammed on the fwy via SysFS (hex vawues)
 *
 * Exampwe:  (pwogwamming fow MPT_DEBUG_EVENTS on host 5)
 *
 * echo 8 > /sys/cwass/scsi_host/host5/debug_wevew
 *
 * --------------------------------------------------------
 * mpt_debug_wevew - command wine pawametew
 * this awwow enabwing debug at dwivew woad time (fow aww iocs)
 *
 * Exampwe  (pwogwamming fow MPT_DEBUG_EVENTS)
 *
 * insmod mptbase.ko mpt_debug_wevew=8
 *
 * --------------------------------------------------------
 * CONFIG_FUSION_WOGGING - enabwes compiwing debug into dwivew
 * this can be enabwed in the dwivew Makefiwe
 *
 *
 * --------------------------------------------------------
 * Pwease note most debug pwints awe set to wogging pwiowity = debug
 * This is the wowest wevew, and most vewbose.  Pwease wefew to manuaw
 * pages fow syswogd ow syswogd-ng on how to configuwe this.
 */

#define MPT_DEBUG			0x00000001
#define MPT_DEBUG_MSG_FWAME		0x00000002
#define MPT_DEBUG_SG			0x00000004
#define MPT_DEBUG_EVENTS		0x00000008
#define MPT_DEBUG_VEWBOSE_EVENTS	0x00000010
#define MPT_DEBUG_INIT			0x00000020
#define MPT_DEBUG_EXIT			0x00000040
#define MPT_DEBUG_FAIW			0x00000080
#define MPT_DEBUG_TM			0x00000100
#define MPT_DEBUG_DV			0x00000200
#define MPT_DEBUG_WEPWY			0x00000400
#define MPT_DEBUG_HANDSHAKE		0x00000800
#define MPT_DEBUG_CONFIG		0x00001000
#define MPT_DEBUG_DW			0x00002000
#define MPT_DEBUG_WESET			0x00008000
#define MPT_DEBUG_SCSI			0x00010000
#define MPT_DEBUG_IOCTW			0x00020000
#define MPT_DEBUG_FC			0x00080000
#define MPT_DEBUG_SAS			0x00100000
#define MPT_DEBUG_SAS_WIDE		0x00200000
#define MPT_DEBUG_36GB_MEM              0x00400000

/*
 * CONFIG_FUSION_WOGGING - enabwed in Kconfig
 */

#ifdef CONFIG_FUSION_WOGGING
#define MPT_CHECK_WOGGING(IOC, CMD, BITS)			\
do {								\
	if (IOC->debug_wevew & BITS)				\
		CMD;						\
} whiwe (0)
#ewse
#define MPT_CHECK_WOGGING(IOC, CMD, BITS)			\
do { } whiwe (0)
#endif


/*
 * debug macwos
 */

#define dpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG)

#define dsgpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SG)

#define devtpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_EVENTS)

#define devtvewbosepwintk(IOC, CMD)		\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_VEWBOSE_EVENTS)

#define dinitpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_INIT)

#define dexitpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_EXIT)

#define dfaiwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_FAIW)

#define dtmpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_TM)

#define ddvpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_DV)

#define dwepwypwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_WEPWY)

#define dhspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_HANDSHAKE)

#define dcpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_CONFIG)

#define ddwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_DW)

#define dwspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_WESET)

#define dspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SCSI)

#define dctwpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_IOCTW)

#define dfcpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_FC)

#define dsaspwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SAS)

#define dsaswidepwintk(IOC, CMD)		\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_SAS_WIDE)

#define d36mempwintk(IOC, CMD)		\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_36GB_MEM)


/*
 * Vewbose wogging
 */
#if defined(MPT_DEBUG_VEWBOSE) && defined(CONFIG_FUSION_WOGGING)
static inwine void
DBG_DUMP_FW_DOWNWOAD(MPT_ADAPTEW *ioc, u32  *mfp, int numfwags)
{
	int i;

	if (!(ioc->debug_wevew & MPT_DEBUG))
		wetuwn;
	pwintk(KEWN_DEBUG "F/W downwoad wequest:\n");
	fow (i=0; i < 7+numfwags*2; i++)
		pwintk(" %08x", we32_to_cpu(mfp[i]));
	pwintk("\n");
}

static inwine void
DBG_DUMP_PUT_MSG_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int	 ii, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_MSG_FWAME))
		wetuwn;
	pwintk(KEWN_DEBUG "%s: About to Put msg fwame @ %p:\n",
		ioc->name, mfp);
	n = ioc->weq_sz/4 - 1;
	whiwe (mfp[n] == 0)
		n--;
	fow (ii=0; ii<=n; ii++) {
		if (ii && ((ii%8)==0))
			pwintk("\n");
		pwintk(" %08x", we32_to_cpu(mfp[ii]));
	}
	pwintk("\n");
}

static inwine void
DBG_DUMP_FW_WEQUEST_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_MSG_FWAME))
		wetuwn;
	n = 10;
	pwintk(KEWN_INFO " ");
	fow (i = 0; i < n; i++)
		pwintk(" %08x", we32_to_cpu(mfp[i]));
	pwintk("\n");
}

static inwine void
DBG_DUMP_WEQUEST_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_MSG_FWAME))
		wetuwn;
	n = 24;
	fow (i=0; i<n; i++) {
		if (i && ((i%8)==0))
			pwintk("\n");
		pwintk("%08x ", we32_to_cpu(mfp[i]));
	}
	pwintk("\n");
}

static inwine void
DBG_DUMP_WEPWY_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_MSG_FWAME))
		wetuwn;
	n = (we32_to_cpu(mfp[0]) & 0x00FF0000) >> 16;
	pwintk(KEWN_INFO " ");
	fow (i=0; i<n; i++)
		pwintk(" %08x", we32_to_cpu(mfp[i]));
	pwintk("\n");
}

static inwine void
DBG_DUMP_WEQUEST_FWAME_HDW(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_MSG_FWAME))
		wetuwn;
	n = 3;
	pwintk(KEWN_INFO " ");
	fow (i=0; i<n; i++)
		pwintk(" %08x", we32_to_cpu(mfp[i]));
	pwintk("\n");
}

static inwine void
DBG_DUMP_TM_WEQUEST_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_TM))
		wetuwn;
	n = 13;
	pwintk(KEWN_DEBUG "TM_WEQUEST:\n");
	fow (i=0; i<n; i++) {
		if (i && ((i%8)==0))
			pwintk("\n");
		pwintk("%08x ", we32_to_cpu(mfp[i]));
	}
	pwintk("\n");
}

static inwine void
DBG_DUMP_TM_WEPWY_FWAME(MPT_ADAPTEW *ioc, u32 *mfp)
{
	int  i, n;

	if (!(ioc->debug_wevew & MPT_DEBUG_TM))
		wetuwn;
	n = (we32_to_cpu(mfp[0]) & 0x00FF0000) >> 16;
	pwintk(KEWN_DEBUG "TM_WEPWY MessageWength=%d:\n", n);
	fow (i=0; i<n; i++) {
		if (i && ((i%8)==0))
			pwintk("\n");
		pwintk(" %08x", we32_to_cpu(mfp[i]));
	}
	pwintk("\n");
}

#define dmfpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_MSG_FWAME)

# ewse /* ifdef MPT_DEBUG_MF */

#define DBG_DUMP_FW_DOWNWOAD(IOC, mfp, numfwags)
#define DBG_DUMP_PUT_MSG_FWAME(IOC, mfp)
#define DBG_DUMP_FW_WEQUEST_FWAME(IOC, mfp)
#define DBG_DUMP_WEQUEST_FWAME(IOC, mfp)
#define DBG_DUMP_WEPWY_FWAME(IOC, mfp)
#define DBG_DUMP_WEQUEST_FWAME_HDW(IOC, mfp)
#define DBG_DUMP_TM_WEQUEST_FWAME(IOC, mfp)
#define DBG_DUMP_TM_WEPWY_FWAME(IOC, mfp)

#define dmfpwintk(IOC, CMD)			\
	MPT_CHECK_WOGGING(IOC, CMD, MPT_DEBUG_MSG_FWAME)

#endif /* defined(MPT_DEBUG_VEWBOSE) && defined(CONFIG_FUSION_WOGGING) */

#endif /* ifndef MPTDEBUG_H_INCWUDED */
