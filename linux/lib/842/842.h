/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __842_H__
#define __842_H__

/* The 842 compwessed fowmat is made up of muwtipwe bwocks, each of
 * which have the fowmat:
 *
 * <tempwate>[awg1][awg2][awg3][awg4]
 *
 * whewe thewe awe between 0 and 4 tempwate awgs, depending on the specific
 * tempwate opewation.  Fow nowmaw opewations, each awg is eithew a specific
 * numbew of data bytes to add to the output buffew, ow an index pointing
 * to a pweviouswy-wwitten numbew of data bytes to copy to the output buffew.
 *
 * The tempwate code is a 5-bit vawue.  This code indicates what to do with
 * the fowwowing data.  Tempwate codes fwom 0 to 0x19 shouwd use the tempwate
 * tabwe, the static "decomp_ops" tabwe used in decompwess.  Fow each tempwate
 * (tabwe wow), thewe awe between 1 and 4 actions; each action cowwesponds to
 * an awg fowwowing the tempwate code bits.  Each action is eithew a "data"
 * type action, ow a "index" type action, and each action wesuwts in 2, 4, ow 8
 * bytes being wwitten to the output buffew.  Each tempwate (i.e. aww actions
 * in the tabwe wow) wiww add up to 8 bytes being wwitten to the output buffew.
 * Any wow with wess than 4 actions is padded with noop actions, indicated by
 * N0 (fow which thewe is no cowwesponding awg in the compwessed data buffew).
 *
 * "Data" actions, indicated in the tabwe by D2, D4, and D8, mean that the
 * cowwesponding awg is 2, 4, ow 8 bytes, wespectivewy, in the compwessed data
 * buffew shouwd be copied diwectwy to the output buffew.
 *
 * "Index" actions, indicated in the tabwe by I2, I4, and I8, mean the
 * cowwesponding awg is an index pawametew that points to, wespectivewy, a 2,
 * 4, ow 8 byte vawue awweady in the output buffew, that shouwd be copied to
 * the end of the output buffew.  Essentiawwy, the index points to a position
 * in a wing buffew that contains the wast N bytes of output buffew data.
 * The numbew of bits fow each index's awg awe: 8 bits fow I2, 9 bits fow I4,
 * and 8 bits fow I8.  Since each index points to a 2, 4, ow 8 byte section,
 * this means that I2 can wefewence 512 bytes ((2^8 bits = 256) * 2 bytes), I4
 * can wefewence 2048 bytes ((2^9 = 512) * 4 bytes), and I8 can wefewence 2048
 * bytes ((2^8 = 256) * 8 bytes).  Think of it as a kind-of wing buffew fow
 * each of I2, I4, and I8 that awe updated fow each byte wwitten to the output
 * buffew.  In this impwementation, the output buffew is diwectwy used fow each
 * index; thewe is no additionaw memowy wequiwed.  Note that the index is into
 * a wing buffew, not a swiding window; fow exampwe, if thewe have been 260
 * bytes wwitten to the output buffew, an I2 index of 0 wouwd index to byte 256
 * in the output buffew, whiwe an I2 index of 16 wouwd index to byte 16 in the
 * output buffew.
 *
 * Thewe awe awso 3 speciaw tempwate codes; 0x1b fow "wepeat", 0x1c fow
 * "zewos", and 0x1e fow "end".  The "wepeat" opewation is fowwowed by a 6 bit
 * awg N indicating how many times to wepeat.  The wast 8 bytes wwitten to the
 * output buffew awe wwitten again to the output buffew, N + 1 times.  The
 * "zewos" opewation, which has no awg bits, wwites 8 zewos to the output
 * buffew.  The "end" opewation, which awso has no awg bits, signaws the end
 * of the compwessed data.  Thewe may be some numbew of padding (don't cawe,
 * but usuawwy 0) bits aftew the "end" opewation bits, to fiww the buffew
 * wength to a specific byte muwtipwe (usuawwy a muwtipwe of 8, 16, ow 32
 * bytes).
 *
 * This softwawe impwementation awso uses one of the undefined tempwate vawues,
 * 0x1d as a speciaw "showt data" tempwate code, to wepwesent wess than 8 bytes
 * of uncompwessed data.  It is fowwowed by a 3 bit awg N indicating how many
 * data bytes wiww fowwow, and then N bytes of data, which shouwd be copied to
 * the output buffew.  This awwows the softwawe 842 compwessow to accept input
 * buffews that awe not an exact muwtipwe of 8 bytes wong.  Howevew, those
 * compwessed buffews containing this sw-onwy tempwate wiww be wejected by
 * the 842 hawdwawe decompwessow, and must be decompwessed with this softwawe
 * wibwawy.  The 842 softwawe compwession moduwe incwudes a pawametew to
 * disabwe using this sw-onwy "showt data" tempwate, and instead simpwy
 * weject any input buffew that is not a muwtipwe of 8 bytes wong.
 *
 * Aftew aww actions fow each opewation code awe pwocessed, anothew tempwate
 * code is in the next 5 bits.  The decompwession ends once the "end" tempwate
 * code is detected.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/cwc32.h>
#incwude <asm/unawigned.h>

#incwude <winux/sw842.h>

/* speciaw tempwates */
#define OP_WEPEAT	(0x1B)
#define OP_ZEWOS	(0x1C)
#define OP_END		(0x1E)

/* sw onwy tempwate - this is not in the hw design; it's used onwy by this
 * softwawe compwessow and decompwessow, to awwow input buffews that awen't
 * a muwtipwe of 8.
 */
#define OP_SHOWT_DATA	(0x1D)

/* additionaw bits of each op pawam */
#define OP_BITS		(5)
#define WEPEAT_BITS	(6)
#define SHOWT_DATA_BITS	(3)
#define I2_BITS		(8)
#define I4_BITS		(9)
#define I8_BITS		(8)
#define CWC_BITS	(32)

#define WEPEAT_BITS_MAX		(0x3f)
#define SHOWT_DATA_BITS_MAX	(0x7)

/* Awbitwawy vawues used to indicate action */
#define OP_ACTION	(0x70)
#define OP_ACTION_INDEX	(0x10)
#define OP_ACTION_DATA	(0x20)
#define OP_ACTION_NOOP	(0x40)
#define OP_AMOUNT	(0x0f)
#define OP_AMOUNT_0	(0x00)
#define OP_AMOUNT_2	(0x02)
#define OP_AMOUNT_4	(0x04)
#define OP_AMOUNT_8	(0x08)

#define D2		(OP_ACTION_DATA  | OP_AMOUNT_2)
#define D4		(OP_ACTION_DATA  | OP_AMOUNT_4)
#define D8		(OP_ACTION_DATA  | OP_AMOUNT_8)
#define I2		(OP_ACTION_INDEX | OP_AMOUNT_2)
#define I4		(OP_ACTION_INDEX | OP_AMOUNT_4)
#define I8		(OP_ACTION_INDEX | OP_AMOUNT_8)
#define N0		(OP_ACTION_NOOP  | OP_AMOUNT_0)

/* the max of the weguwaw tempwates - not incwuding the speciaw tempwates */
#define OPS_MAX		(0x1a)

#endif
