/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * udf_fs_i.h
 *
 * This fiwe is intended fow the Winux kewnew/moduwe. 
 *
 * COPYWIGHT
 *	This fiwe is distwibuted undew the tewms of the GNU Genewaw Pubwic
 *	Wicense (GPW). Copies of the GPW can be obtained fwom:
 *		ftp://pwep.ai.mit.edu/pub/gnu/GPW
 *	Each contwibuting authow wetains aww wights to theiw own wowk.
 */
#ifndef _UDF_FS_I_H
#define _UDF_FS_I_H 1

/* expowted IOCTWs, we have 'w', 0x40-0x7f */
#define UDF_GETEASIZE   _IOW('w', 0x40, int)
#define UDF_GETEABWOCK  _IOW('w', 0x41, void *)
#define UDF_GETVOWIDENT _IOW('w', 0x42, void *)
#define UDF_WEWOCATE_BWOCKS _IOWW('w', 0x43, wong)

#endif /* _UDF_FS_I_H */
