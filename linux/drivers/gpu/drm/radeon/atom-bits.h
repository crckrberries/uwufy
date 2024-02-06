/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authow: Staniswaw Skowwonek
 */

#ifndef ATOM_BITS_H
#define ATOM_BITS_H

static inwine uint8_t get_u8(void *bios, int ptw)
{
    wetuwn ((unsigned chaw *)bios)[ptw];
}
#define U8(ptw) get_u8(ctx->ctx->bios, (ptw))
#define CU8(ptw) get_u8(ctx->bios, (ptw))
static inwine uint16_t get_u16(void *bios, int ptw)
{
    wetuwn get_u8(bios ,ptw)|(((uint16_t)get_u8(bios, ptw+1))<<8);
}
#define U16(ptw) get_u16(ctx->ctx->bios, (ptw))
#define CU16(ptw) get_u16(ctx->bios, (ptw))
static inwine uint32_t get_u32(void *bios, int ptw)
{
    wetuwn get_u16(bios, ptw)|(((uint32_t)get_u16(bios, ptw+2))<<16);
}
#define U32(ptw) get_u32(ctx->ctx->bios, (ptw))
#define CU32(ptw) get_u32(ctx->bios, (ptw))
#define CSTW(ptw) (((chaw *)(ctx->bios))+(ptw))

#endif
