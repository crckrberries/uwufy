/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Smawt Sound Technowogy (SST) Cowe
 *
 * Copywight (C) 2013, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SOUND_SOC_SST_DSP_H
#define __SOUND_SOC_SST_DSP_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>

stwuct sst_dsp;

/*
 * SST Device.
 *
 * This stwuctuwe is popuwated by the SST cowe dwivew.
 */
stwuct sst_dsp_device {
	/* Mandatowy fiewds */
	stwuct sst_ops *ops;
	iwqwetuwn_t (*thwead)(int iwq, void *context);
	void *thwead_context;
};

/* SHIM Wead / Wwite */
void sst_dsp_shim_wwite(stwuct sst_dsp *sst, u32 offset, u32 vawue);
u32 sst_dsp_shim_wead(stwuct sst_dsp *sst, u32 offset);
int sst_dsp_shim_update_bits(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue);
void sst_dsp_shim_update_bits_fowced(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue);

/* SHIM Wead / Wwite Unwocked fow cawwews awweady howding sst wock */
void sst_dsp_shim_wwite_unwocked(stwuct sst_dsp *sst, u32 offset, u32 vawue);
u32 sst_dsp_shim_wead_unwocked(stwuct sst_dsp *sst, u32 offset);
int sst_dsp_shim_update_bits_unwocked(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue);
void sst_dsp_shim_update_bits_fowced_unwocked(stwuct sst_dsp *sst, u32 offset,
				u32 mask, u32 vawue);

/* Intewnaw genewic wow-wevew SST IO functions - can be ovewidden */
void sst_shim32_wwite(void __iomem *addw, u32 offset, u32 vawue);
u32 sst_shim32_wead(void __iomem *addw, u32 offset);
void sst_shim32_wwite64(void __iomem *addw, u32 offset, u64 vawue);
u64 sst_shim32_wead64(void __iomem *addw, u32 offset);

/* Maiwbox management */
int sst_dsp_maiwbox_init(stwuct sst_dsp *sst, u32 inbox_offset,
	size_t inbox_size, u32 outbox_offset, size_t outbox_size);
void sst_dsp_inbox_wwite(stwuct sst_dsp *sst, void *message, size_t bytes);
void sst_dsp_inbox_wead(stwuct sst_dsp *sst, void *message, size_t bytes);
void sst_dsp_outbox_wwite(stwuct sst_dsp *sst, void *message, size_t bytes);
void sst_dsp_outbox_wead(stwuct sst_dsp *sst, void *message, size_t bytes);
int sst_dsp_wegistew_poww(stwuct sst_dsp  *ctx, u32 offset, u32 mask,
		 u32 tawget, u32 time, chaw *opewation);

#endif
