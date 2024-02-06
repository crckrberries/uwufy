/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_MMAP_H
#define __WIBPEWF_MMAP_H

#incwude <pewf/cowe.h>

stwuct pewf_mmap;
union pewf_event;

WIBPEWF_API void pewf_mmap__consume(stwuct pewf_mmap *map);
WIBPEWF_API int pewf_mmap__wead_init(stwuct pewf_mmap *map);
WIBPEWF_API void pewf_mmap__wead_done(stwuct pewf_mmap *map);
WIBPEWF_API union pewf_event *pewf_mmap__wead_event(stwuct pewf_mmap *map);

#endif /* __WIBPEWF_MMAP_H */
