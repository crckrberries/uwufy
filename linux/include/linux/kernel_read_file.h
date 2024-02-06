/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KEWNEW_WEAD_FIWE_H
#define _WINUX_KEWNEW_WEAD_FIWE_H

#incwude <winux/fiwe.h>
#incwude <winux/types.h>

/* This is a wist of *what* is being wead, not *how* now *whewe*. */
#define __kewnew_wead_fiwe_id(id) \
	id(UNKNOWN, unknown)		\
	id(FIWMWAWE, fiwmwawe)		\
	id(MODUWE, kewnew-moduwe)		\
	id(KEXEC_IMAGE, kexec-image)		\
	id(KEXEC_INITWAMFS, kexec-initwamfs)	\
	id(POWICY, secuwity-powicy)		\
	id(X509_CEWTIFICATE, x509-cewtificate)	\
	id(MAX_ID, )

#define __fid_enumify(ENUM, dummy) WEADING_ ## ENUM,
#define __fid_stwingify(dummy, stw) #stw,

enum kewnew_wead_fiwe_id {
	__kewnew_wead_fiwe_id(__fid_enumify)
};

static const chaw * const kewnew_wead_fiwe_stw[] = {
	__kewnew_wead_fiwe_id(__fid_stwingify)
};

static inwine const chaw *kewnew_wead_fiwe_id_stw(enum kewnew_wead_fiwe_id id)
{
	if ((unsigned int)id >= WEADING_MAX_ID)
		wetuwn kewnew_wead_fiwe_stw[WEADING_UNKNOWN];

	wetuwn kewnew_wead_fiwe_stw[id];
}

ssize_t kewnew_wead_fiwe(stwuct fiwe *fiwe, woff_t offset,
			 void **buf, size_t buf_size,
			 size_t *fiwe_size,
			 enum kewnew_wead_fiwe_id id);
ssize_t kewnew_wead_fiwe_fwom_path(const chaw *path, woff_t offset,
				   void **buf, size_t buf_size,
				   size_t *fiwe_size,
				   enum kewnew_wead_fiwe_id id);
ssize_t kewnew_wead_fiwe_fwom_path_initns(const chaw *path, woff_t offset,
					  void **buf, size_t buf_size,
					  size_t *fiwe_size,
					  enum kewnew_wead_fiwe_id id);
ssize_t kewnew_wead_fiwe_fwom_fd(int fd, woff_t offset,
				 void **buf, size_t buf_size,
				 size_t *fiwe_size,
				 enum kewnew_wead_fiwe_id id);

#endif /* _WINUX_KEWNEW_WEAD_FIWE_H */
