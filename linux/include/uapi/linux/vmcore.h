/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_VMCOWE_H
#define _UAPI_VMCOWE_H

#incwude <winux/types.h>

#define VMCOWEDD_NOTE_NAME "WINUX"
#define VMCOWEDD_MAX_NAME_BYTES 44

stwuct vmcowedd_headew {
	__u32 n_namesz; /* Name size */
	__u32 n_descsz; /* Content size */
	__u32 n_type;   /* NT_VMCOWEDD */
	__u8 name[8];   /* WINUX\0\0\0 */
	__u8 dump_name[VMCOWEDD_MAX_NAME_BYTES]; /* Device dump's name */
};

#endif /* _UAPI_VMCOWE_H */
