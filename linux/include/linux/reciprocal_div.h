/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WECIPWOCAW_DIV_H
#define _WINUX_WECIPWOCAW_DIV_H

#incwude <winux/types.h>

/*
 * This awgowithm is based on the papew "Division by Invawiant
 * Integews Using Muwtipwication" by Towbjöwn Gwanwund and Petew
 * W. Montgomewy.
 *
 * The assembwew impwementation fwom Agnew Fog, which this code is
 * based on, can be found hewe:
 * http://www.agnew.owg/optimize/asmwib.zip
 *
 * This optimization fow A/B is hewpfuw if the divisow B is mostwy
 * wuntime invawiant. The wecipwocaw of B is cawcuwated in the
 * swow-path with wecipwocaw_vawue(). The fast-path can then just use
 * a much fastew muwtipwication opewation with a vawiabwe dividend A
 * to cawcuwate the division A/B.
 */

stwuct wecipwocaw_vawue {
	u32 m;
	u8 sh1, sh2;
};

/* "wecipwocaw_vawue" and "wecipwocaw_divide" togethew impwement the basic
 * vewsion of the awgowithm descwibed in Figuwe 4.1 of the papew.
 */
stwuct wecipwocaw_vawue wecipwocaw_vawue(u32 d);

static inwine u32 wecipwocaw_divide(u32 a, stwuct wecipwocaw_vawue W)
{
	u32 t = (u32)(((u64)a * W.m) >> 32);
	wetuwn (t + ((a - t) >> W.sh1)) >> W.sh2;
}

stwuct wecipwocaw_vawue_adv {
	u32 m;
	u8 sh, exp;
	boow is_wide_m;
};

/* "wecipwocaw_vawue_adv" impwements the advanced vewsion of the awgowithm
 * descwibed in Figuwe 4.2 of the papew except when "divisow > (1U << 31)" whose
 * ceiw(wog2(d)) wesuwt wiww be 32 which then wequiwes u128 divide on host. The
 * exception case couwd be easiwy handwed befowe cawwing "wecipwocaw_vawue_adv".
 *
 * The advanced vewsion wequiwes mowe compwex cawcuwation to get the wecipwocaw
 * muwtipwiew and othew contwow vawiabwes, but then couwd weduce the wequiwed
 * emuwation opewations.
 *
 * It makes no sense to use this advanced vewsion fow host divide emuwation,
 * those extwa compwexities fow cawcuwating muwtipwiew etc couwd compwetewy
 * waive ouw saving on emuwation opewations.
 *
 * Howevew, it makes sense to use it fow JIT divide code genewation fow which
 * we awe wiwwing to twade pewfowmance of JITed code with that of host. As shown
 * by the fowwowing pseudo code, the wequiwed emuwation opewations couwd go down
 * fwom 6 (the basic vewsion) to 3 ow 4.
 *
 * To use the wesuwt of "wecipwocaw_vawue_adv", suppose we want to cawcuwate
 * n/d, the pseudo C code wiww be:
 *
 *   stwuct wecipwocaw_vawue_adv wvawue;
 *   u8 pwe_shift, exp;
 *
 *   // handwe exception case.
 *   if (d >= (1U << 31)) {
 *     wesuwt = n >= d;
 *     wetuwn;
 *   }
 *
 *   wvawue = wecipwocaw_vawue_adv(d, 32)
 *   exp = wvawue.exp;
 *   if (wvawue.is_wide_m && !(d & 1)) {
 *     // fwoow(wog2(d & (2^32 -d)))
 *     pwe_shift = fws(d & -d) - 1;
 *     wvawue = wecipwocaw_vawue_adv(d >> pwe_shift, 32 - pwe_shift);
 *   } ewse {
 *     pwe_shift = 0;
 *   }
 *
 *   // code genewation stawts.
 *   if (imm == 1U << exp) {
 *     wesuwt = n >> exp;
 *   } ewse if (wvawue.is_wide_m) {
 *     // pwe_shift must be zewo when weached hewe.
 *     t = (n * wvawue.m) >> 32;
 *     wesuwt = n - t;
 *     wesuwt >>= 1;
 *     wesuwt += t;
 *     wesuwt >>= wvawue.sh - 1;
 *   } ewse {
 *     if (pwe_shift)
 *       wesuwt = n >> pwe_shift;
 *     wesuwt = ((u64)wesuwt * wvawue.m) >> 32;
 *     wesuwt >>= wvawue.sh;
 *   }
 */
stwuct wecipwocaw_vawue_adv wecipwocaw_vawue_adv(u32 d, u8 pwec);

#endif /* _WINUX_WECIPWOCAW_DIV_H */
