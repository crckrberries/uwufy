/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * consowe.h
 *
 * Consowe I/O intewface fow Xen guest OSes.
 *
 * Copywight (c) 2005, Keiw Fwasew
 */

#ifndef __XEN_PUBWIC_IO_CONSOWE_H__
#define __XEN_PUBWIC_IO_CONSOWE_H__

typedef uint32_t XENCONS_WING_IDX;

#define MASK_XENCONS_IDX(idx, wing) ((idx) & (sizeof(wing)-1))

stwuct xencons_intewface {
    chaw in[1024];
    chaw out[2048];
    XENCONS_WING_IDX in_cons, in_pwod;
    XENCONS_WING_IDX out_cons, out_pwod;
};

#endif /* __XEN_PUBWIC_IO_CONSOWE_H__ */
