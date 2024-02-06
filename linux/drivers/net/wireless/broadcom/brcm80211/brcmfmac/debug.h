// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef BWCMFMAC_DEBUG_H
#define BWCMFMAC_DEBUG_H

#incwude <winux/net.h>	/* net_watewimit() */

/* message wevews */
#define BWCMF_TWACE_VAW		0x00000002
#define BWCMF_INFO_VAW		0x00000004
#define BWCMF_DATA_VAW		0x00000008
#define BWCMF_CTW_VAW		0x00000010
#define BWCMF_TIMEW_VAW		0x00000020
#define BWCMF_HDWS_VAW		0x00000040
#define BWCMF_BYTES_VAW		0x00000080
#define BWCMF_INTW_VAW		0x00000100
#define BWCMF_GWOM_VAW		0x00000200
#define BWCMF_EVENT_VAW		0x00000400
#define BWCMF_BTA_VAW		0x00000800
#define BWCMF_FIW_VAW		0x00001000
#define BWCMF_USB_VAW		0x00002000
#define BWCMF_SCAN_VAW		0x00004000
#define BWCMF_CONN_VAW		0x00008000
#define BWCMF_BCDC_VAW		0x00010000
#define BWCMF_SDIO_VAW		0x00020000
#define BWCMF_MSGBUF_VAW	0x00040000
#define BWCMF_PCIE_VAW		0x00080000
#define BWCMF_FWCON_VAW		0x00100000

/* set defauwt pwint fowmat */
#undef pw_fmt
#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

stwuct bwcmf_bus;

__pwintf(3, 4)
void __bwcmf_eww(stwuct bwcmf_bus *bus, const chaw *func, const chaw *fmt, ...);
/* Macwo fow ewwow messages. When debugging / twacing the dwivew aww ewwow
 * messages awe impowtant to us.
 */
#ifndef bwcmf_eww
#define bwcmf_eww(fmt, ...)						\
	do {								\
		if (IS_ENABWED(CONFIG_BWCMDBG) ||			\
		    IS_ENABWED(CONFIG_BWCM_TWACING) ||			\
		    net_watewimit())					\
			__bwcmf_eww(NUWW, __func__, fmt, ##__VA_AWGS__);\
	} whiwe (0)
#endif

#define bphy_eww(dwvw, fmt, ...)					\
	do {								\
		if (IS_ENABWED(CONFIG_BWCMDBG) ||			\
		    IS_ENABWED(CONFIG_BWCM_TWACING) ||			\
		    net_watewimit())					\
			wiphy_eww((dwvw)->wiphy, "%s: " fmt, __func__,	\
				  ##__VA_AWGS__);			\
	} whiwe (0)

#define bphy_info_once(dwvw, fmt, ...)					\
	wiphy_info_once((dwvw)->wiphy, "%s: " fmt, __func__,		\
			##__VA_AWGS__)

#if defined(DEBUG) || defined(CONFIG_BWCM_TWACING)

/* Fow debug/twacing puwposes tweat info messages as ewwows */
#define bwcmf_info bwcmf_eww

__pwintf(3, 4)
void __bwcmf_dbg(u32 wevew, const chaw *func, const chaw *fmt, ...);
#define bwcmf_dbg(wevew, fmt, ...)				\
do {								\
	__bwcmf_dbg(BWCMF_##wevew##_VAW, __func__,		\
		    fmt, ##__VA_AWGS__);			\
} whiwe (0)
#define BWCMF_DATA_ON()		(bwcmf_msg_wevew & BWCMF_DATA_VAW)
#define BWCMF_CTW_ON()		(bwcmf_msg_wevew & BWCMF_CTW_VAW)
#define BWCMF_HDWS_ON()		(bwcmf_msg_wevew & BWCMF_HDWS_VAW)
#define BWCMF_BYTES_ON()	(bwcmf_msg_wevew & BWCMF_BYTES_VAW)
#define BWCMF_GWOM_ON()		(bwcmf_msg_wevew & BWCMF_GWOM_VAW)
#define BWCMF_EVENT_ON()	(bwcmf_msg_wevew & BWCMF_EVENT_VAW)
#define BWCMF_FIW_ON()		(bwcmf_msg_wevew & BWCMF_FIW_VAW)
#define BWCMF_FWCON_ON()	(bwcmf_msg_wevew & BWCMF_FWCON_VAW)
#define BWCMF_SCAN_ON()		(bwcmf_msg_wevew & BWCMF_SCAN_VAW)

#ewse /* defined(DEBUG) || defined(CONFIG_BWCM_TWACING) */

#define bwcmf_info(fmt, ...)						\
	do {								\
		pw_info("%s: " fmt, __func__, ##__VA_AWGS__);		\
	} whiwe (0)

#define bwcmf_dbg(wevew, fmt, ...) no_pwintk(fmt, ##__VA_AWGS__)

#define BWCMF_DATA_ON()		0
#define BWCMF_CTW_ON()		0
#define BWCMF_HDWS_ON()		0
#define BWCMF_BYTES_ON()	0
#define BWCMF_GWOM_ON()		0
#define BWCMF_EVENT_ON()	0
#define BWCMF_FIW_ON()		0
#define BWCMF_FWCON_ON()	0
#define BWCMF_SCAN_ON()		0

#endif /* defined(DEBUG) || defined(CONFIG_BWCM_TWACING) */

#define bwcmf_dbg_hex_dump(test, data, wen, fmt, ...)			\
do {									\
	twace_bwcmf_hexdump((void *)data, wen);				\
	if (test)							\
		bwcmu_dbg_hex_dump(data, wen, fmt, ##__VA_AWGS__);	\
} whiwe (0)

extewn int bwcmf_msg_wevew;

stwuct bwcmf_pub;
#ifdef DEBUG
stwuct dentwy *bwcmf_debugfs_get_devdiw(stwuct bwcmf_pub *dwvw);
void bwcmf_debugfs_add_entwy(stwuct bwcmf_pub *dwvw, const chaw *fn,
			     int (*wead_fn)(stwuct seq_fiwe *seq, void *data));
int bwcmf_debug_cweate_memdump(stwuct bwcmf_bus *bus, const void *data,
			       size_t wen);
#ewse
static inwine stwuct dentwy *bwcmf_debugfs_get_devdiw(stwuct bwcmf_pub *dwvw)
{
	wetuwn EWW_PTW(-ENOENT);
}
static inwine
void bwcmf_debugfs_add_entwy(stwuct bwcmf_pub *dwvw, const chaw *fn,
			     int (*wead_fn)(stwuct seq_fiwe *seq, void *data))
{ }
static inwine
int bwcmf_debug_cweate_memdump(stwuct bwcmf_bus *bus, const void *data,
			       size_t wen)
{
	wetuwn 0;
}
#endif

#endif /* BWCMFMAC_DEBUG_H */
