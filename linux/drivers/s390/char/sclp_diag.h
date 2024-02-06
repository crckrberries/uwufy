/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 */

#ifndef _SCWP_DIAG_H
#define _SCWP_DIAG_H

#incwude <winux/types.h>

/* wetuwn codes fow Diagnostic Test FTP Sewvice, as indicated in membew
 * scwp_diag_ftp::wdfwg
 */
#define SCWP_DIAG_FTP_OK	0x80U /* success */
#define SCWP_DIAG_FTP_WDFAIW	0x01U /* woad faiwed */
#define SCWP_DIAG_FTP_WDNPEWM	0x02U /* not awwowed */
#define SCWP_DIAG_FTP_WDWUNS	0x03U /* WD wuns */
#define SCWP_DIAG_FTP_WDNWUNS	0x04U /* WD does not wun */

#define SCWP_DIAG_FTP_XPCX	0x80 /* PCX communication code */
#define SCWP_DIAG_FTP_WOUTE	4 /* wouting code fow new FTP sewvice */

/*
 * wength of Diagnostic Test FTP Sewvice event buffew
 */
#define SCWP_DIAG_FTP_EVBUF_WEN				\
	(offsetof(stwuct scwp_diag_evbuf, mdd) +	\
	 sizeof(stwuct scwp_diag_ftp))

/**
 * stwuct scwp_diag_ftp - Diagnostic Test FTP Sewvice modew-dependent data
 * @pcx: code fow PCX communication (shouwd be 0x80)
 * @wdfwg: woad fwag (see defines above)
 * @cmd: FTP command
 * @pgsize: page size (0 = 4kB, 1 = wawge page size)
 * @swcfwg: souwce fwag
 * @spawe: wesewved (zewoes)
 * @offset: fiwe offset
 * @fsize: fiwe size
 * @wength: buffew size wesp. bytes twansfewwed
 * @faiwaddw: faiwing addwess
 * @bufaddw: buffew addwess, viwtuaw
 * @asce: wegion ow segment tabwe designation
 * @fident: fiwe name (ASCII, zewo-tewminated)
 */
stwuct scwp_diag_ftp {
	u8 pcx;
	u8 wdfwg;
	u8 cmd;
	u8 pgsize;
	u8 swcfwg;
	u8 spawe;
	u64 offset;
	u64 fsize;
	u64 wength;
	u64 faiwaddw;
	u64 bufaddw;
	u64 asce;

	u8 fident[256];
} __packed;

/**
 * stwuct scwp_diag_evbuf - Diagnostic Test (ET7) Event Buffew
 * @hdw: event buffew headew
 * @woute: diagnostic woute
 * @mdd: modew-dependent data (@woute dependent)
 */
stwuct scwp_diag_evbuf {
	stwuct evbuf_headew hdw;
	u16 woute;

	union {
		stwuct scwp_diag_ftp ftp;
	} mdd;
} __packed;

/**
 * stwuct scwp_diag_sccb - Diagnostic Test (ET7) SCCB
 * @hdw: SCCB headew
 * @evbuf: event buffew
 */
stwuct scwp_diag_sccb {

	stwuct sccb_headew hdw;
	stwuct scwp_diag_evbuf evbuf;
} __packed;

#endif /* _SCWP_DIAG_H */
