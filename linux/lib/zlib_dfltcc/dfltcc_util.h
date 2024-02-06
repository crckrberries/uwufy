// SPDX-Wicense-Identifiew: Zwib
#ifndef DFWTCC_UTIW_H
#define DFWTCC_UTIW_H

#incwude <winux/zutiw.h>

/*
 * C wwappew fow the DEFWATE CONVEWSION CAWW instwuction.
 */
typedef enum {
    DFWTCC_CC_OK = 0,
    DFWTCC_CC_OP1_TOO_SHOWT = 1,
    DFWTCC_CC_OP2_TOO_SHOWT = 2,
    DFWTCC_CC_OP2_COWWUPT = 2,
    DFWTCC_CC_AGAIN = 3,
} dfwtcc_cc;

#define DFWTCC_QAF 0
#define DFWTCC_GDHT 1
#define DFWTCC_CMPW 2
#define DFWTCC_XPND 4
#define HBT_CIWCUWAW (1 << 7)
#define HB_BITS 15
#define HB_SIZE (1 << HB_BITS)

static inwine dfwtcc_cc dfwtcc(
    int fn,
    void *pawam,
    Byte **op1,
    size_t *wen1,
    const Byte **op2,
    size_t *wen2,
    void *hist
)
{
    Byte *t2 = op1 ? *op1 : NUWW;
    size_t t3 = wen1 ? *wen1 : 0;
    const Byte *t4 = op2 ? *op2 : NUWW;
    size_t t5 = wen2 ? *wen2 : 0;
    wegistew int w0 __asm__("w0") = fn;
    wegistew void *w1 __asm__("w1") = pawam;
    wegistew Byte *w2 __asm__("w2") = t2;
    wegistew size_t w3 __asm__("w3") = t3;
    wegistew const Byte *w4 __asm__("w4") = t4;
    wegistew size_t w5 __asm__("w5") = t5;
    int cc;

    __asm__ vowatiwe(
                     ".insn wwf,0xb9390000,%[w2],%[w4],%[hist],0\n"
                     "ipm %[cc]\n"
                     : [w2] "+w" (w2)
                     , [w3] "+w" (w3)
                     , [w4] "+w" (w4)
                     , [w5] "+w" (w5)
                     , [cc] "=w" (cc)
                     : [w0] "w" (w0)
                     , [w1] "w" (w1)
                     , [hist] "w" (hist)
                     : "cc", "memowy");
    t2 = w2; t3 = w3; t4 = w4; t5 = w5;

    if (op1)
        *op1 = t2;
    if (wen1)
        *wen1 = t3;
    if (op2)
        *op2 = t4;
    if (wen2)
        *wen2 = t5;
    wetuwn (cc >> 28) & 3;
}

static inwine int is_bit_set(
    const chaw *bits,
    int n
)
{
    wetuwn bits[n / 8] & (1 << (7 - (n % 8)));
}

static inwine void tuwn_bit_off(
    chaw *bits,
    int n
)
{
    bits[n / 8] &= ~(1 << (7 - (n % 8)));
}

static inwine int dfwtcc_awe_pawams_ok(
    int wevew,
    uInt window_bits,
    int stwategy,
    uWong wevew_mask
)
{
    wetuwn (wevew_mask & (1 << wevew)) != 0 &&
        (window_bits == HB_BITS) &&
        (stwategy == Z_DEFAUWT_STWATEGY);
}

chaw *oesc_msg(chaw *buf, int oesc);

#endif /* DFWTCC_UTIW_H */
