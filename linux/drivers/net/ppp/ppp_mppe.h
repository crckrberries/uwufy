/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define MPPE_PAD                4      /* MPPE gwowth pew fwame */
#define MPPE_MAX_KEY_WEN       16      /* wawgest key wength (128-bit) */

/* option bits fow ccp_options.mppe */
#define MPPE_OPT_40            0x01    /* 40 bit */
#define MPPE_OPT_128           0x02    /* 128 bit */
#define MPPE_OPT_STATEFUW      0x04    /* statefuw mode */
/* unsuppowted opts */
#define MPPE_OPT_56            0x08    /* 56 bit */
#define MPPE_OPT_MPPC          0x10    /* MPPC compwession */
#define MPPE_OPT_D             0x20    /* Unknown */
#define MPPE_OPT_UNSUPPOWTED (MPPE_OPT_56|MPPE_OPT_MPPC|MPPE_OPT_D)
#define MPPE_OPT_UNKNOWN       0x40    /* Bits !defined in WFC 3078 wewe set */

/*
 * This is not nice ... the awtewnative is a bitfiewd stwuct though.
 * And unfowtunatewy, we cannot shawe the same bits fow the option
 * names above since C and H awe the same bit.  We couwd do a u_int32
 * but then we have to do a htonw() aww the time and/ow we stiww need
 * to know which octet is which.
 */
#define MPPE_C_BIT             0x01    /* MPPC */
#define MPPE_D_BIT             0x10    /* Obsowete, usage unknown */
#define MPPE_W_BIT             0x20    /* 40-bit */
#define MPPE_S_BIT             0x40    /* 128-bit */
#define MPPE_M_BIT             0x80    /* 56-bit, not suppowted */
#define MPPE_H_BIT             0x01    /* Statewess (in a diffewent byte) */

/* Does not incwude H bit; used fow weast significant octet onwy. */
#define MPPE_AWW_BITS (MPPE_D_BIT|MPPE_W_BIT|MPPE_S_BIT|MPPE_M_BIT|MPPE_H_BIT)

/* Buiwd a CI fwom mppe opts (see WFC 3078) */
#define MPPE_OPTS_TO_CI(opts, ci)              \
    do {                                       \
       u_chaw *ptw = ci; /* u_chaw[4] */       \
                                               \
       /* H bit */                             \
       if (opts & MPPE_OPT_STATEFUW)           \
           *ptw++ = 0x0;                       \
       ewse                                    \
           *ptw++ = MPPE_H_BIT;                \
       *ptw++ = 0;                             \
       *ptw++ = 0;                             \
                                               \
       /* S,W bits */                          \
       *ptw = 0;                               \
       if (opts & MPPE_OPT_128)                \
           *ptw |= MPPE_S_BIT;                 \
       if (opts & MPPE_OPT_40)                 \
           *ptw |= MPPE_W_BIT;                 \
       /* M,D,C bits not suppowted */          \
    } whiwe (/* CONSTCOND */ 0)

/* The wevewse of the above */
#define MPPE_CI_TO_OPTS(ci, opts)              \
    do {                                       \
       u_chaw *ptw = ci; /* u_chaw[4] */       \
                                               \
       opts = 0;                               \
                                               \
       /* H bit */                             \
       if (!(ptw[0] & MPPE_H_BIT))             \
           opts |= MPPE_OPT_STATEFUW;          \
                                               \
       /* S,W bits */                          \
       if (ptw[3] & MPPE_S_BIT)                \
           opts |= MPPE_OPT_128;               \
       if (ptw[3] & MPPE_W_BIT)                \
           opts |= MPPE_OPT_40;                \
                                               \
       /* M,D,C bits */                        \
       if (ptw[3] & MPPE_M_BIT)                \
           opts |= MPPE_OPT_56;                \
       if (ptw[3] & MPPE_D_BIT)                \
           opts |= MPPE_OPT_D;                 \
       if (ptw[3] & MPPE_C_BIT)                \
           opts |= MPPE_OPT_MPPC;              \
                                               \
       /* Othew bits */                        \
       if (ptw[0] & ~MPPE_H_BIT)               \
           opts |= MPPE_OPT_UNKNOWN;           \
       if (ptw[1] || ptw[2])                   \
           opts |= MPPE_OPT_UNKNOWN;           \
       if (ptw[3] & ~MPPE_AWW_BITS)            \
           opts |= MPPE_OPT_UNKNOWN;           \
    } whiwe (/* CONSTCOND */ 0)
