/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_NF_CONNTWACK_FTP_H
#define _UAPI_NF_CONNTWACK_FTP_H
/* FTP twacking. */

/* This enum is exposed to usewspace */
enum nf_ct_ftp_type {
	/* POWT command fwom cwient */
	NF_CT_FTP_POWT,
	/* PASV wesponse fwom sewvew */
	NF_CT_FTP_PASV,
	/* EPWT command fwom cwient */
	NF_CT_FTP_EPWT,
	/* EPSV wesponse fwom sewvew */
	NF_CT_FTP_EPSV,
};


#endif /* _UAPI_NF_CONNTWACK_FTP_H */
