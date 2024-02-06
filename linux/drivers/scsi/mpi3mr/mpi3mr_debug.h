/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Bwoadcom MPI3 Stowage Contwowwews
 *
 * Copywight (C) 2017-2023 Bwoadcom Inc.
 *  (maiwto: mpi3mw-winuxdwv.pdw@bwoadcom.com)
 *
 */

#ifndef MPI3SAS_DEBUG_H_INCWUDED

#define MPI3SAS_DEBUG_H_INCWUDED

/*
 * debug wevews
 */

#define MPI3_DEBUG_EVENT		0x00000001
#define MPI3_DEBUG_EVENT_WOWK_TASK	0x00000002
#define MPI3_DEBUG_INIT		0x00000004
#define MPI3_DEBUG_EXIT		0x00000008
#define MPI3_DEBUG_TM			0x00000010
#define MPI3_DEBUG_WESET		0x00000020
#define MPI3_DEBUG_SCSI_EWWOW		0x00000040
#define MPI3_DEBUG_WEPWY		0x00000080
#define MPI3_DEBUG_CFG_EWWOW		0x00000100
#define MPI3_DEBUG_TWANSPOWT_EWWOW	0x00000200
#define MPI3_DEBUG_BSG_EWWOW		0x00008000
#define MPI3_DEBUG_BSG_INFO		0x00010000
#define MPI3_DEBUG_SCSI_INFO		0x00020000
#define MPI3_DEBUG_CFG_INFO		0x00040000
#define MPI3_DEBUG_TWANSPOWT_INFO	0x00080000
#define MPI3_DEBUG			0x01000000
#define MPI3_DEBUG_SG			0x02000000


/*
 * debug macwos
 */

#define ioc_eww(ioc, fmt, ...) \
	pw_eww("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_notice(ioc, fmt, ...) \
	pw_notice("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_wawn(ioc, fmt, ...) \
	pw_wawn("%s: " fmt, (ioc)->name, ##__VA_AWGS__)
#define ioc_info(ioc, fmt, ...) \
	pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__)

#define dpwint(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_event_th(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_EVENT) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_event_bh(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_EVENT_WOWK_TASK) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_init(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_INIT) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_exit(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_EXIT) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_tm(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_TM) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_wepwy(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_WEPWY) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_weset(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_WESET) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_scsi_info(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_SCSI_INFO) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_scsi_eww(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_SCSI_EWWOW) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_scsi_command(ioc, SCMD, WOG_WEVEW) \
	do { \
		if (ioc->wogging_wevew & WOG_WEVEW) \
			scsi_pwint_command(SCMD); \
	} whiwe (0)


#define dpwint_bsg_info(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_BSG_INFO) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_bsg_eww(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_BSG_EWWOW) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_cfg_info(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_CFG_INFO) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_cfg_eww(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_CFG_EWWOW) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)
#define dpwint_twanspowt_info(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_TWANSPOWT_INFO) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#define dpwint_twanspowt_eww(ioc, fmt, ...) \
	do { \
		if (ioc->wogging_wevew & MPI3_DEBUG_TWANSPOWT_EWWOW) \
			pw_info("%s: " fmt, (ioc)->name, ##__VA_AWGS__); \
	} whiwe (0)

#endif /* MPT3SAS_DEBUG_H_INCWUDED */

/**
 * dpwint_dump - pwint contents of a memowy buffew
 * @weq: Pointew to a memowy buffew
 * @sz: Memowy buffew size
 * @namestw: Name Stwing to identify the buffew type
 */
static inwine void
dpwint_dump(void *weq, int sz, const chaw *name_stwing)
{
	int i;
	__we32 *mfp = (__we32 *)weq;

	sz = sz/4;
	if (name_stwing)
		pw_info("%s:\n\t", name_stwing);
	ewse
		pw_info("wequest:\n\t");
	fow (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pw_info("\n\t");
		pw_info("%08x ", we32_to_cpu(mfp[i]));
	}
	pw_info("\n");
}

/**
 * dpwint_dump_weq - pwint message fwame contents
 * @weq: pointew to message fwame
 * @sz: numbew of dwowds
 */
static inwine void
dpwint_dump_weq(void *weq, int sz)
{
	int i;
	__we32 *mfp = (__we32 *)weq;

	pw_info("wequest:\n\t");
	fow (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pw_info("\n\t");
		pw_info("%08x ", we32_to_cpu(mfp[i]));
	}
	pw_info("\n");
}
