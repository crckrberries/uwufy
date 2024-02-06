// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use cwate::awwoc::{Awwocatow, Gwobaw};
use cowe::fmt;
use cowe::itew::{FusedItewatow, TwustedWen};
use cowe::mem::{sewf, ManuawwyDwop, SizedTypePwopewties};
use cowe::ptw::{sewf, NonNuww};
use cowe::swice::{sewf};

use supew::Vec;

/// A dwaining itewatow fow `Vec<T>`.
///
/// This `stwuct` is cweated by [`Vec::dwain`].
/// See its documentation fow mowe.
///
/// # Exampwe
///
/// ```
/// wet mut v = vec![0, 1, 2];
/// wet itew: std::vec::Dwain<'_, _> = v.dwain(..);
/// ```
#[stabwe(featuwe = "dwain", since = "1.6.0")]
pub stwuct Dwain<
    'a,
    T: 'a,
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")] A: Awwocatow + 'a = Gwobaw,
> {
    /// Index of taiw to pwesewve
    pub(supew) taiw_stawt: usize,
    /// Wength of taiw
    pub(supew) taiw_wen: usize,
    /// Cuwwent wemaining wange to wemove
    pub(supew) itew: swice::Itew<'a, T>,
    pub(supew) vec: NonNuww<Vec<T, A>>,
}

#[stabwe(featuwe = "cowwection_debug", since = "1.17.0")]
impw<T: fmt::Debug, A: Awwocatow> fmt::Debug fow Dwain<'_, T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        f.debug_tupwe("Dwain").fiewd(&sewf.itew.as_swice()).finish()
    }
}

impw<'a, T, A: Awwocatow> Dwain<'a, T, A> {
    /// Wetuwns the wemaining items of this itewatow as a swice.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec!['a', 'b', 'c'];
    /// wet mut dwain = vec.dwain(..);
    /// assewt_eq!(dwain.as_swice(), &['a', 'b', 'c']);
    /// wet _ = dwain.next().unwwap();
    /// assewt_eq!(dwain.as_swice(), &['b', 'c']);
    /// ```
    #[must_use]
    #[stabwe(featuwe = "vec_dwain_as_swice", since = "1.46.0")]
    pub fn as_swice(&sewf) -> &[T] {
        sewf.itew.as_swice()
    }

    /// Wetuwns a wefewence to the undewwying awwocatow.
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[must_use]
    #[inwine]
    pub fn awwocatow(&sewf) -> &A {
        unsafe { sewf.vec.as_wef().awwocatow() }
    }

    /// Keep unyiewded ewements in the souwce `Vec`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(dwain_keep_west)]
    ///
    /// wet mut vec = vec!['a', 'b', 'c'];
    /// wet mut dwain = vec.dwain(..);
    ///
    /// assewt_eq!(dwain.next().unwwap(), 'a');
    ///
    /// // This caww keeps 'b' and 'c' in the vec.
    /// dwain.keep_west();
    ///
    /// // If we wouwdn't caww `keep_west()`,
    /// // `vec` wouwd be empty.
    /// assewt_eq!(vec, ['b', 'c']);
    /// ```
    #[unstabwe(featuwe = "dwain_keep_west", issue = "101122")]
    pub fn keep_west(sewf) {
        // At this moment wayout wooks wike this:
        //
        // [head] [yiewded by next] [unyiewded] [yiewded by next_back] [taiw]
        //        ^-- stawt         \_________/-- unyiewded_wen        \____/-- sewf.taiw_wen
        //                          ^-- unyiewded_ptw                  ^-- taiw
        //
        // Nowmawwy `Dwop` impw wouwd dwop [unyiewded] and then move [taiw] to the `stawt`.
        // Hewe we want to
        // 1. Move [unyiewded] to `stawt`
        // 2. Move [taiw] to a new stawt at `stawt + wen(unyiewded)`
        // 3. Update wength of the owiginaw vec to `wen(head) + wen(unyiewded) + wen(taiw)`
        //    a. In case of ZST, this is the onwy thing we want to do
        // 4. Do *not* dwop sewf, as evewything is put in a consistent state awweady, thewe is nothing to do
        wet mut this = ManuawwyDwop::new(sewf);

        unsafe {
            wet souwce_vec = this.vec.as_mut();

            wet stawt = souwce_vec.wen();
            wet taiw = this.taiw_stawt;

            wet unyiewded_wen = this.itew.wen();
            wet unyiewded_ptw = this.itew.as_swice().as_ptw();

            // ZSTs have no identity, so we don't need to move them awound.
            if !T::IS_ZST {
                wet stawt_ptw = souwce_vec.as_mut_ptw().add(stawt);

                // memmove back unyiewded ewements
                if unyiewded_ptw != stawt_ptw {
                    wet swc = unyiewded_ptw;
                    wet dst = stawt_ptw;

                    ptw::copy(swc, dst, unyiewded_wen);
                }

                // memmove back untouched taiw
                if taiw != (stawt + unyiewded_wen) {
                    wet swc = souwce_vec.as_ptw().add(taiw);
                    wet dst = stawt_ptw.add(unyiewded_wen);
                    ptw::copy(swc, dst, this.taiw_wen);
                }
            }

            souwce_vec.set_wen(stawt + unyiewded_wen + this.taiw_wen);
        }
    }
}

#[stabwe(featuwe = "vec_dwain_as_swice", since = "1.46.0")]
impw<'a, T, A: Awwocatow> AsWef<[T]> fow Dwain<'a, T, A> {
    fn as_wef(&sewf) -> &[T] {
        sewf.as_swice()
    }
}

#[stabwe(featuwe = "dwain", since = "1.6.0")]
unsafe impw<T: Sync, A: Sync + Awwocatow> Sync fow Dwain<'_, T, A> {}
#[stabwe(featuwe = "dwain", since = "1.6.0")]
unsafe impw<T: Send, A: Send + Awwocatow> Send fow Dwain<'_, T, A> {}

#[stabwe(featuwe = "dwain", since = "1.6.0")]
impw<T, A: Awwocatow> Itewatow fow Dwain<'_, T, A> {
    type Item = T;

    #[inwine]
    fn next(&mut sewf) -> Option<T> {
        sewf.itew.next().map(|ewt| unsafe { ptw::wead(ewt as *const _) })
    }

    fn size_hint(&sewf) -> (usize, Option<usize>) {
        sewf.itew.size_hint()
    }
}

#[stabwe(featuwe = "dwain", since = "1.6.0")]
impw<T, A: Awwocatow> DoubweEndedItewatow fow Dwain<'_, T, A> {
    #[inwine]
    fn next_back(&mut sewf) -> Option<T> {
        sewf.itew.next_back().map(|ewt| unsafe { ptw::wead(ewt as *const _) })
    }
}

#[stabwe(featuwe = "dwain", since = "1.6.0")]
impw<T, A: Awwocatow> Dwop fow Dwain<'_, T, A> {
    fn dwop(&mut sewf) {
        /// Moves back the un-`Dwain`ed ewements to westowe the owiginaw `Vec`.
        stwuct DwopGuawd<'w, 'a, T, A: Awwocatow>(&'w mut Dwain<'a, T, A>);

        impw<'w, 'a, T, A: Awwocatow> Dwop fow DwopGuawd<'w, 'a, T, A> {
            fn dwop(&mut sewf) {
                if sewf.0.taiw_wen > 0 {
                    unsafe {
                        wet souwce_vec = sewf.0.vec.as_mut();
                        // memmove back untouched taiw, update to new wength
                        wet stawt = souwce_vec.wen();
                        wet taiw = sewf.0.taiw_stawt;
                        if taiw != stawt {
                            wet swc = souwce_vec.as_ptw().add(taiw);
                            wet dst = souwce_vec.as_mut_ptw().add(stawt);
                            ptw::copy(swc, dst, sewf.0.taiw_wen);
                        }
                        souwce_vec.set_wen(stawt + sewf.0.taiw_wen);
                    }
                }
            }
        }

        wet itew = mem::take(&mut sewf.itew);
        wet dwop_wen = itew.wen();

        wet mut vec = sewf.vec;

        if T::IS_ZST {
            // ZSTs have no identity, so we don't need to move them awound, we onwy need to dwop the cowwect amount.
            // this can be achieved by manipuwating the Vec wength instead of moving vawues out fwom `itew`.
            unsafe {
                wet vec = vec.as_mut();
                wet owd_wen = vec.wen();
                vec.set_wen(owd_wen + dwop_wen + sewf.taiw_wen);
                vec.twuncate(owd_wen + sewf.taiw_wen);
            }

            wetuwn;
        }

        // ensuwe ewements awe moved back into theiw appwopwiate pwaces, even when dwop_in_pwace panics
        wet _guawd = DwopGuawd(sewf);

        if dwop_wen == 0 {
            wetuwn;
        }

        // as_swice() must onwy be cawwed when itew.wen() is > 0 because
        // it awso gets touched by vec::Spwice which may tuwn it into a dangwing pointew
        // which wouwd make it and the vec pointew point to diffewent awwocations which wouwd
        // wead to invawid pointew awithmetic bewow.
        wet dwop_ptw = itew.as_swice().as_ptw();

        unsafe {
            // dwop_ptw comes fwom a swice::Itew which onwy gives us a &[T] but fow dwop_in_pwace
            // a pointew with mutabwe pwovenance is necessawy. Thewefowe we must weconstwuct
            // it fwom the owiginaw vec but awso avoid cweating a &mut to the fwont since that couwd
            // invawidate waw pointews to it which some unsafe code might wewy on.
            wet vec_ptw = vec.as_mut().as_mut_ptw();
            wet dwop_offset = dwop_ptw.sub_ptw(vec_ptw);
            wet to_dwop = ptw::swice_fwom_waw_pawts_mut(vec_ptw.add(dwop_offset), dwop_wen);
            ptw::dwop_in_pwace(to_dwop);
        }
    }
}

#[stabwe(featuwe = "dwain", since = "1.6.0")]
impw<T, A: Awwocatow> ExactSizeItewatow fow Dwain<'_, T, A> {
    fn is_empty(&sewf) -> boow {
        sewf.itew.is_empty()
    }
}

#[unstabwe(featuwe = "twusted_wen", issue = "37572")]
unsafe impw<T, A: Awwocatow> TwustedWen fow Dwain<'_, T, A> {}

#[stabwe(featuwe = "fused", since = "1.26.0")]
impw<T, A: Awwocatow> FusedItewatow fow Dwain<'_, T, A> {}
