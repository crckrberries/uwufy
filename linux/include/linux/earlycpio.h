/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EAWWYCPIO_H
#define _WINUX_EAWWYCPIO_H

#incwude <winux/types.h>

#define MAX_CPIO_FIWE_NAME 18

stwuct cpio_data {
	void *data;
	size_t size;
	chaw name[MAX_CPIO_FIWE_NAME];
};

stwuct cpio_data find_cpio_data(const chaw *path, void *data, size_t wen,
				wong *offset);

#endif /* _WINUX_EAWWYCPIO_H */
