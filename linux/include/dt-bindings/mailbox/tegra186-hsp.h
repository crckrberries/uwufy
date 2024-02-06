/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow binding nvidia,tegwa186-hsp.
 */

#ifndef _DT_BINDINGS_MAIWBOX_TEGWA186_HSP_H
#define _DT_BINDINGS_MAIWBOX_TEGWA186_HSP_H

/*
 * These define the type of maiwbox that is to be used (doowbeww, shawed
 * maiwbox, shawed semaphowe ow awbitwated semaphowe).
 */
#define TEGWA_HSP_MBOX_TYPE_DB 0x0
#define TEGWA_HSP_MBOX_TYPE_SM 0x1
#define TEGWA_HSP_MBOX_TYPE_SS 0x2
#define TEGWA_HSP_MBOX_TYPE_AS 0x3

/*
 * These define the types of shawed maiwbox suppowted based on data size.
 */
#define TEGWA_HSP_MBOX_TYPE_SM_128BIT (1 << 8)

/*
 * These defines wepwesent the bit associated with the given mastew ID in the
 * doowbeww wegistews.
 */
#define TEGWA_HSP_DB_MASTEW_CCPWEX 17
#define TEGWA_HSP_DB_MASTEW_BPMP 19

/*
 * Shawed maiwboxes awe unidiwectionaw, so the diwection needs to be specified
 * in the device twee.
 */
#define TEGWA_HSP_SM_MASK 0x00ffffff
#define TEGWA_HSP_SM_FWAG_WX (0 << 31)
#define TEGWA_HSP_SM_FWAG_TX (1 << 31)

#define TEGWA_HSP_SM_WX(x) (TEGWA_HSP_SM_FWAG_WX | ((x) & TEGWA_HSP_SM_MASK))
#define TEGWA_HSP_SM_TX(x) (TEGWA_HSP_SM_FWAG_TX | ((x) & TEGWA_HSP_SM_MASK))

#endif
