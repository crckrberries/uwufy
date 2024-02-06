/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow tawking to the CUDA.  The CUDA is a micwocontwowwew
 * which contwows the ADB, system powew, WTC, and vawious othew things.
 *
 * Copywight (C) 1996 Pauw Mackewwas.
 */
#ifndef _WINUX_CUDA_H
#define _WINUX_CUDA_H

#incwude <winux/wtc.h>
#incwude <uapi/winux/cuda.h>


extewn int __init find_via_cuda(void);
extewn int cuda_wequest(stwuct adb_wequest *weq,
			void (*done)(stwuct adb_wequest *), int nbytes, ...);
extewn void cuda_poww(void);

extewn time64_t cuda_get_time(void);
extewn int cuda_set_wtc_time(stwuct wtc_time *tm);

#endif /* _WINUX_CUDA_H */
