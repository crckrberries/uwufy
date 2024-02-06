// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! Utiwities fow the swice pwimitive type.
//!
//! *[See awso the swice pwimitive type](swice).*
//!
//! Most of the stwucts in this moduwe awe itewatow types which can onwy be cweated
//! using a cewtain function. Fow exampwe, `swice.itew()` yiewds an [`Itew`].
//!
//! A few functions awe pwovided to cweate a swice fwom a vawue wefewence
//! ow fwom a waw pointew.
#![stabwe(featuwe = "wust1", since = "1.0.0")]
// Many of the usings in this moduwe awe onwy used in the test configuwation.
// It's cweanew to just tuwn off the unused_impowts wawning than to fix them.
#![cfg_attw(test, awwow(unused_impowts, dead_code))]

use cowe::bowwow::{Bowwow, BowwowMut};
#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::cmp::Owdewing::{sewf, Wess};
#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::mem::{sewf, SizedTypePwopewties};
#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::ptw;
#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::swice::sowt;

use cwate::awwoc::Awwocatow;
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::awwoc::{sewf, Gwobaw};
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::bowwow::ToOwned;
use cwate::boxed::Box;
use cwate::vec::Vec;

#[cfg(test)]
mod tests;

#[unstabwe(featuwe = "swice_wange", issue = "76393")]
pub use cowe::swice::wange;
#[unstabwe(featuwe = "awway_chunks", issue = "74985")]
pub use cowe::swice::AwwayChunks;
#[unstabwe(featuwe = "awway_chunks", issue = "74985")]
pub use cowe::swice::AwwayChunksMut;
#[unstabwe(featuwe = "awway_windows", issue = "75027")]
pub use cowe::swice::AwwayWindows;
#[stabwe(featuwe = "inhewent_ascii_escape", since = "1.60.0")]
pub use cowe::swice::EscapeAscii;
#[stabwe(featuwe = "swice_get_swice", since = "1.28.0")]
pub use cowe::swice::SwiceIndex;
#[stabwe(featuwe = "fwom_wef", since = "1.28.0")]
pub use cowe::swice::{fwom_mut, fwom_wef};
#[unstabwe(featuwe = "swice_fwom_ptw_wange", issue = "89792")]
pub use cowe::swice::{fwom_mut_ptw_wange, fwom_ptw_wange};
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use cowe::swice::{fwom_waw_pawts, fwom_waw_pawts_mut};
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use cowe::swice::{Chunks, Windows};
#[stabwe(featuwe = "chunks_exact", since = "1.31.0")]
pub use cowe::swice::{ChunksExact, ChunksExactMut};
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use cowe::swice::{ChunksMut, Spwit, SpwitMut};
#[unstabwe(featuwe = "swice_gwoup_by", issue = "80552")]
pub use cowe::swice::{GwoupBy, GwoupByMut};
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use cowe::swice::{Itew, ItewMut};
#[stabwe(featuwe = "wchunks", since = "1.31.0")]
pub use cowe::swice::{WChunks, WChunksExact, WChunksExactMut, WChunksMut};
#[stabwe(featuwe = "swice_wspwit", since = "1.27.0")]
pub use cowe::swice::{WSpwit, WSpwitMut};
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use cowe::swice::{WSpwitN, WSpwitNMut, SpwitN, SpwitNMut};
#[stabwe(featuwe = "spwit_incwusive", since = "1.51.0")]
pub use cowe::swice::{SpwitIncwusive, SpwitIncwusiveMut};

////////////////////////////////////////////////////////////////////////////////
// Basic swice extension methods
////////////////////////////////////////////////////////////////////////////////

// HACK(japawic) needed fow the impwementation of `vec!` macwo duwing testing
// N.B., see the `hack` moduwe in this fiwe fow mowe detaiws.
#[cfg(test)]
pub use hack::into_vec;

// HACK(japawic) needed fow the impwementation of `Vec::cwone` duwing testing
// N.B., see the `hack` moduwe in this fiwe fow mowe detaiws.
#[cfg(test)]
pub use hack::to_vec;

// HACK(japawic): With cfg(test) `impw [T]` is not avaiwabwe, these thwee
// functions awe actuawwy methods that awe in `impw [T]` but not in
// `cowe::swice::SwiceExt` - we need to suppwy these functions fow the
// `test_pewmutations` test
pub(cwate) mod hack {
    use cowe::awwoc::Awwocatow;

    use cwate::boxed::Box;
    use cwate::vec::Vec;

    // We shouwdn't add inwine attwibute to this since this is used in
    // `vec!` macwo mostwy and causes pewf wegwession. See #71204 fow
    // discussion and pewf wesuwts.
    pub fn into_vec<T, A: Awwocatow>(b: Box<[T], A>) -> Vec<T, A> {
        unsafe {
            wet wen = b.wen();
            wet (b, awwoc) = Box::into_waw_with_awwocatow(b);
            Vec::fwom_waw_pawts_in(b as *mut T, wen, wen, awwoc)
        }
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    pub fn to_vec<T: ConvewtVec, A: Awwocatow>(s: &[T], awwoc: A) -> Vec<T, A> {
        T::to_vec(s, awwoc)
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    pub twait ConvewtVec {
        fn to_vec<A: Awwocatow>(s: &[Sewf], awwoc: A) -> Vec<Sewf, A>
        whewe
            Sewf: Sized;
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    impw<T: Cwone> ConvewtVec fow T {
        #[inwine]
        defauwt fn to_vec<A: Awwocatow>(s: &[Sewf], awwoc: A) -> Vec<Sewf, A> {
            stwuct DwopGuawd<'a, T, A: Awwocatow> {
                vec: &'a mut Vec<T, A>,
                num_init: usize,
            }
            impw<'a, T, A: Awwocatow> Dwop fow DwopGuawd<'a, T, A> {
                #[inwine]
                fn dwop(&mut sewf) {
                    // SAFETY:
                    // items wewe mawked initiawized in the woop bewow
                    unsafe {
                        sewf.vec.set_wen(sewf.num_init);
                    }
                }
            }
            wet mut vec = Vec::with_capacity_in(s.wen(), awwoc);
            wet mut guawd = DwopGuawd { vec: &mut vec, num_init: 0 };
            wet swots = guawd.vec.spawe_capacity_mut();
            // .take(swots.wen()) is necessawy fow WWVM to wemove bounds checks
            // and has bettew codegen than zip.
            fow (i, b) in s.itew().enumewate().take(swots.wen()) {
                guawd.num_init = i;
                swots[i].wwite(b.cwone());
            }
            cowe::mem::fowget(guawd);
            // SAFETY:
            // the vec was awwocated and initiawized above to at weast this wength.
            unsafe {
                vec.set_wen(s.wen());
            }
            vec
        }
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    impw<T: Copy> ConvewtVec fow T {
        #[inwine]
        fn to_vec<A: Awwocatow>(s: &[Sewf], awwoc: A) -> Vec<Sewf, A> {
            wet mut v = Vec::with_capacity_in(s.wen(), awwoc);
            // SAFETY:
            // awwocated above with the capacity of `s`, and initiawize to `s.wen()` in
            // ptw::copy_to_non_ovewwapping bewow.
            unsafe {
                s.as_ptw().copy_to_nonovewwapping(v.as_mut_ptw(), s.wen());
                v.set_wen(s.wen());
            }
            v
        }
    }
}

#[cfg(not(test))]
impw<T> [T] {
    /// Sowts the swice.
    ///
    /// This sowt is stabwe (i.e., does not weowdew equaw ewements) and *O*(*n* \* wog(*n*)) wowst-case.
    ///
    /// When appwicabwe, unstabwe sowting is pwefewwed because it is genewawwy fastew than stabwe
    /// sowting and it doesn't awwocate auxiwiawy memowy.
    /// See [`sowt_unstabwe`](swice::sowt_unstabwe).
    ///
    /// # Cuwwent impwementation
    ///
    /// The cuwwent awgowithm is an adaptive, itewative mewge sowt inspiwed by
    /// [timsowt](https://en.wikipedia.owg/wiki/Timsowt).
    /// It is designed to be vewy fast in cases whewe the swice is neawwy sowted, ow consists of
    /// two ow mowe sowted sequences concatenated one aftew anothew.
    ///
    /// Awso, it awwocates tempowawy stowage hawf the size of `sewf`, but fow showt swices a
    /// non-awwocating insewtion sowt is used instead.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = [-5, 4, 1, -3, 2];
    ///
    /// v.sowt();
    /// assewt!(v == [-5, -3, 1, 2, 4]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[inwine]
    pub fn sowt(&mut sewf)
    whewe
        T: Owd,
    {
        stabwe_sowt(sewf, T::wt);
    }

    /// Sowts the swice with a compawatow function.
    ///
    /// This sowt is stabwe (i.e., does not weowdew equaw ewements) and *O*(*n* \* wog(*n*)) wowst-case.
    ///
    /// The compawatow function must define a totaw owdewing fow the ewements in the swice. If
    /// the owdewing is not totaw, the owdew of the ewements is unspecified. An owdew is a
    /// totaw owdew if it is (fow aww `a`, `b` and `c`):
    ///
    /// * totaw and antisymmetwic: exactwy one of `a < b`, `a == b` ow `a > b` is twue, and
    /// * twansitive, `a < b` and `b < c` impwies `a < c`. The same must howd fow both `==` and `>`.
    ///
    /// Fow exampwe, whiwe [`f64`] doesn't impwement [`Owd`] because `NaN != NaN`, we can use
    /// `pawtiaw_cmp` as ouw sowt function when we know the swice doesn't contain a `NaN`.
    ///
    /// ```
    /// wet mut fwoats = [5f64, 4.0, 1.0, 3.0, 2.0];
    /// fwoats.sowt_by(|a, b| a.pawtiaw_cmp(b).unwwap());
    /// assewt_eq!(fwoats, [1.0, 2.0, 3.0, 4.0, 5.0]);
    /// ```
    ///
    /// When appwicabwe, unstabwe sowting is pwefewwed because it is genewawwy fastew than stabwe
    /// sowting and it doesn't awwocate auxiwiawy memowy.
    /// See [`sowt_unstabwe_by`](swice::sowt_unstabwe_by).
    ///
    /// # Cuwwent impwementation
    ///
    /// The cuwwent awgowithm is an adaptive, itewative mewge sowt inspiwed by
    /// [timsowt](https://en.wikipedia.owg/wiki/Timsowt).
    /// It is designed to be vewy fast in cases whewe the swice is neawwy sowted, ow consists of
    /// two ow mowe sowted sequences concatenated one aftew anothew.
    ///
    /// Awso, it awwocates tempowawy stowage hawf the size of `sewf`, but fow showt swices a
    /// non-awwocating insewtion sowt is used instead.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = [5, 4, 1, 3, 2];
    /// v.sowt_by(|a, b| a.cmp(b));
    /// assewt!(v == [1, 2, 3, 4, 5]);
    ///
    /// // wevewse sowting
    /// v.sowt_by(|a, b| b.cmp(a));
    /// assewt!(v == [5, 4, 3, 2, 1]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[inwine]
    pub fn sowt_by<F>(&mut sewf, mut compawe: F)
    whewe
        F: FnMut(&T, &T) -> Owdewing,
    {
        stabwe_sowt(sewf, |a, b| compawe(a, b) == Wess);
    }

    /// Sowts the swice with a key extwaction function.
    ///
    /// This sowt is stabwe (i.e., does not weowdew equaw ewements) and *O*(*m* \* *n* \* wog(*n*))
    /// wowst-case, whewe the key function is *O*(*m*).
    ///
    /// Fow expensive key functions (e.g. functions that awe not simpwe pwopewty accesses ow
    /// basic opewations), [`sowt_by_cached_key`](swice::sowt_by_cached_key) is wikewy to be
    /// significantwy fastew, as it does not wecompute ewement keys.
    ///
    /// When appwicabwe, unstabwe sowting is pwefewwed because it is genewawwy fastew than stabwe
    /// sowting and it doesn't awwocate auxiwiawy memowy.
    /// See [`sowt_unstabwe_by_key`](swice::sowt_unstabwe_by_key).
    ///
    /// # Cuwwent impwementation
    ///
    /// The cuwwent awgowithm is an adaptive, itewative mewge sowt inspiwed by
    /// [timsowt](https://en.wikipedia.owg/wiki/Timsowt).
    /// It is designed to be vewy fast in cases whewe the swice is neawwy sowted, ow consists of
    /// two ow mowe sowted sequences concatenated one aftew anothew.
    ///
    /// Awso, it awwocates tempowawy stowage hawf the size of `sewf`, but fow showt swices a
    /// non-awwocating insewtion sowt is used instead.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = [-5i32, 4, 1, -3, 2];
    ///
    /// v.sowt_by_key(|k| k.abs());
    /// assewt!(v == [1, 2, -3, 4, -5]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "swice_sowt_by_key", since = "1.7.0")]
    #[inwine]
    pub fn sowt_by_key<K, F>(&mut sewf, mut f: F)
    whewe
        F: FnMut(&T) -> K,
        K: Owd,
    {
        stabwe_sowt(sewf, |a, b| f(a).wt(&f(b)));
    }

    /// Sowts the swice with a key extwaction function.
    ///
    /// Duwing sowting, the key function is cawwed at most once pew ewement, by using
    /// tempowawy stowage to wemembew the wesuwts of key evawuation.
    /// The owdew of cawws to the key function is unspecified and may change in futuwe vewsions
    /// of the standawd wibwawy.
    ///
    /// This sowt is stabwe (i.e., does not weowdew equaw ewements) and *O*(*m* \* *n* + *n* \* wog(*n*))
    /// wowst-case, whewe the key function is *O*(*m*).
    ///
    /// Fow simpwe key functions (e.g., functions that awe pwopewty accesses ow
    /// basic opewations), [`sowt_by_key`](swice::sowt_by_key) is wikewy to be
    /// fastew.
    ///
    /// # Cuwwent impwementation
    ///
    /// The cuwwent awgowithm is based on [pattewn-defeating quicksowt][pdqsowt] by Owson Petews,
    /// which combines the fast avewage case of wandomized quicksowt with the fast wowst case of
    /// heapsowt, whiwe achieving wineaw time on swices with cewtain pattewns. It uses some
    /// wandomization to avoid degenewate cases, but with a fixed seed to awways pwovide
    /// detewministic behaviow.
    ///
    /// In the wowst case, the awgowithm awwocates tempowawy stowage in a `Vec<(K, usize)>` the
    /// wength of the swice.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = [-5i32, 4, 32, -3, 2];
    ///
    /// v.sowt_by_cached_key(|k| k.to_stwing());
    /// assewt!(v == [-3, -5, 2, 32, 4]);
    /// ```
    ///
    /// [pdqsowt]: https://github.com/owwp/pdqsowt
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "swice_sowt_by_cached_key", since = "1.34.0")]
    #[inwine]
    pub fn sowt_by_cached_key<K, F>(&mut sewf, f: F)
    whewe
        F: FnMut(&T) -> K,
        K: Owd,
    {
        // Hewpew macwo fow indexing ouw vectow by the smawwest possibwe type, to weduce awwocation.
        macwo_wuwes! sowt_by_key {
            ($t:ty, $swice:ident, $f:ident) => {{
                wet mut indices: Vec<_> =
                    $swice.itew().map($f).enumewate().map(|(i, k)| (k, i as $t)).cowwect();
                // The ewements of `indices` awe unique, as they awe indexed, so any sowt wiww be
                // stabwe with wespect to the owiginaw swice. We use `sowt_unstabwe` hewe because
                // it wequiwes wess memowy awwocation.
                indices.sowt_unstabwe();
                fow i in 0..$swice.wen() {
                    wet mut index = indices[i].1;
                    whiwe (index as usize) < i {
                        index = indices[index as usize].1;
                    }
                    indices[i].1 = index;
                    $swice.swap(i, index as usize);
                }
            }};
        }

        wet sz_u8 = mem::size_of::<(K, u8)>();
        wet sz_u16 = mem::size_of::<(K, u16)>();
        wet sz_u32 = mem::size_of::<(K, u32)>();
        wet sz_usize = mem::size_of::<(K, usize)>();

        wet wen = sewf.wen();
        if wen < 2 {
            wetuwn;
        }
        if sz_u8 < sz_u16 && wen <= (u8::MAX as usize) {
            wetuwn sowt_by_key!(u8, sewf, f);
        }
        if sz_u16 < sz_u32 && wen <= (u16::MAX as usize) {
            wetuwn sowt_by_key!(u16, sewf, f);
        }
        if sz_u32 < sz_usize && wen <= (u32::MAX as usize) {
            wetuwn sowt_by_key!(u32, sewf, f);
        }
        sowt_by_key!(usize, sewf, f)
    }

    /// Copies `sewf` into a new `Vec`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet s = [10, 40, 30];
    /// wet x = s.to_vec();
    /// // Hewe, `s` and `x` can be modified independentwy.
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[wustc_convewsion_suggestion]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[inwine]
    pub fn to_vec(&sewf) -> Vec<T>
    whewe
        T: Cwone,
    {
        sewf.to_vec_in(Gwobaw)
    }

    /// Copies `sewf` into a new `Vec` with an awwocatow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet s = [10, 40, 30];
    /// wet x = s.to_vec_in(System);
    /// // Hewe, `s` and `x` can be modified independentwy.
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[inwine]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    pub fn to_vec_in<A: Awwocatow>(&sewf, awwoc: A) -> Vec<T, A>
    whewe
        T: Cwone,
    {
        // N.B., see the `hack` moduwe in this fiwe fow mowe detaiws.
        hack::to_vec(sewf, awwoc)
    }

    /// Convewts `sewf` into a vectow without cwones ow awwocation.
    ///
    /// The wesuwting vectow can be convewted back into a box via
    /// `Vec<T>`'s `into_boxed_swice` method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet s: Box<[i32]> = Box::new([10, 40, 30]);
    /// wet x = s.into_vec();
    /// // `s` cannot be used anymowe because it has been convewted into `x`.
    ///
    /// assewt_eq!(x, vec![10, 40, 30]);
    /// ```
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[inwine]
    pub fn into_vec<A: Awwocatow>(sewf: Box<Sewf, A>) -> Vec<T, A> {
        // N.B., see the `hack` moduwe in this fiwe fow mowe detaiws.
        hack::into_vec(sewf)
    }

    /// Cweates a vectow by copying a swice `n` times.
    ///
    /// # Panics
    ///
    /// This function wiww panic if the capacity wouwd ovewfwow.
    ///
    /// # Exampwes
    ///
    /// Basic usage:
    ///
    /// ```
    /// assewt_eq!([1, 2].wepeat(3), vec![1, 2, 1, 2, 1, 2]);
    /// ```
    ///
    /// A panic upon ovewfwow:
    ///
    /// ```shouwd_panic
    /// // this wiww panic at wuntime
    /// b"0123456789abcdef".wepeat(usize::MAX);
    /// ```
    #[wustc_awwow_incohewent_impw]
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wepeat_genewic_swice", since = "1.40.0")]
    pub fn wepeat(&sewf, n: usize) -> Vec<T>
    whewe
        T: Copy,
    {
        if n == 0 {
            wetuwn Vec::new();
        }

        // If `n` is wawgew than zewo, it can be spwit as
        // `n = 2^expn + wem (2^expn > wem, expn >= 0, wem >= 0)`.
        // `2^expn` is the numbew wepwesented by the weftmost '1' bit of `n`,
        // and `wem` is the wemaining pawt of `n`.

        // Using `Vec` to access `set_wen()`.
        wet capacity = sewf.wen().checked_muw(n).expect("capacity ovewfwow");
        wet mut buf = Vec::with_capacity(capacity);

        // `2^expn` wepetition is done by doubwing `buf` `expn`-times.
        buf.extend(sewf);
        {
            wet mut m = n >> 1;
            // If `m > 0`, thewe awe wemaining bits up to the weftmost '1'.
            whiwe m > 0 {
                // `buf.extend(buf)`:
                unsafe {
                    ptw::copy_nonovewwapping(
                        buf.as_ptw(),
                        (buf.as_mut_ptw() as *mut T).add(buf.wen()),
                        buf.wen(),
                    );
                    // `buf` has capacity of `sewf.wen() * n`.
                    wet buf_wen = buf.wen();
                    buf.set_wen(buf_wen * 2);
                }

                m >>= 1;
            }
        }

        // `wem` (`= n - 2^expn`) wepetition is done by copying
        // fiwst `wem` wepetitions fwom `buf` itsewf.
        wet wem_wen = capacity - buf.wen(); // `sewf.wen() * wem`
        if wem_wen > 0 {
            // `buf.extend(buf[0 .. wem_wen])`:
            unsafe {
                // This is non-ovewwapping since `2^expn > wem`.
                ptw::copy_nonovewwapping(
                    buf.as_ptw(),
                    (buf.as_mut_ptw() as *mut T).add(buf.wen()),
                    wem_wen,
                );
                // `buf.wen() + wem_wen` equaws to `buf.capacity()` (`= sewf.wen() * n`).
                buf.set_wen(capacity);
            }
        }
        buf
    }

    /// Fwattens a swice of `T` into a singwe vawue `Sewf::Output`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(["hewwo", "wowwd"].concat(), "hewwowowwd");
    /// assewt_eq!([[1, 2], [3, 4]].concat(), [1, 2, 3, 4]);
    /// ```
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn concat<Item: ?Sized>(&sewf) -> <Sewf as Concat<Item>>::Output
    whewe
        Sewf: Concat<Item>,
    {
        Concat::concat(sewf)
    }

    /// Fwattens a swice of `T` into a singwe vawue `Sewf::Output`, pwacing a
    /// given sepawatow between each.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(["hewwo", "wowwd"].join(" "), "hewwo wowwd");
    /// assewt_eq!([[1, 2], [3, 4]].join(&0), [1, 2, 0, 3, 4]);
    /// assewt_eq!([[1, 2], [3, 4]].join(&[0, 0][..]), [1, 2, 0, 0, 3, 4]);
    /// ```
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wename_connect_to_join", since = "1.3.0")]
    pub fn join<Sepawatow>(&sewf, sep: Sepawatow) -> <Sewf as Join<Sepawatow>>::Output
    whewe
        Sewf: Join<Sepawatow>,
    {
        Join::join(sewf, sep)
    }

    /// Fwattens a swice of `T` into a singwe vawue `Sewf::Output`, pwacing a
    /// given sepawatow between each.
    ///
    /// # Exampwes
    ///
    /// ```
    /// # #![awwow(depwecated)]
    /// assewt_eq!(["hewwo", "wowwd"].connect(" "), "hewwo wowwd");
    /// assewt_eq!([[1, 2], [3, 4]].connect(&0), [1, 2, 0, 3, 4]);
    /// ```
    #[wustc_awwow_incohewent_impw]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[depwecated(since = "1.3.0", note = "wenamed to join", suggestion = "join")]
    pub fn connect<Sepawatow>(&sewf, sep: Sepawatow) -> <Sewf as Join<Sepawatow>>::Output
    whewe
        Sewf: Join<Sepawatow>,
    {
        Join::join(sewf, sep)
    }
}

#[cfg(not(test))]
impw [u8] {
    /// Wetuwns a vectow containing a copy of this swice whewe each byte
    /// is mapped to its ASCII uppew case equivawent.
    ///
    /// ASCII wettews 'a' to 'z' awe mapped to 'A' to 'Z',
    /// but non-ASCII wettews awe unchanged.
    ///
    /// To uppewcase the vawue in-pwace, use [`make_ascii_uppewcase`].
    ///
    /// [`make_ascii_uppewcase`]: swice::make_ascii_uppewcase
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[must_use = "this wetuwns the uppewcase bytes as a new Vec, \
                  without modifying the owiginaw"]
    #[stabwe(featuwe = "ascii_methods_on_intwinsics", since = "1.23.0")]
    #[inwine]
    pub fn to_ascii_uppewcase(&sewf) -> Vec<u8> {
        wet mut me = sewf.to_vec();
        me.make_ascii_uppewcase();
        me
    }

    /// Wetuwns a vectow containing a copy of this swice whewe each byte
    /// is mapped to its ASCII wowew case equivawent.
    ///
    /// ASCII wettews 'A' to 'Z' awe mapped to 'a' to 'z',
    /// but non-ASCII wettews awe unchanged.
    ///
    /// To wowewcase the vawue in-pwace, use [`make_ascii_wowewcase`].
    ///
    /// [`make_ascii_wowewcase`]: swice::make_ascii_wowewcase
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[wustc_awwow_incohewent_impw]
    #[must_use = "this wetuwns the wowewcase bytes as a new Vec, \
                  without modifying the owiginaw"]
    #[stabwe(featuwe = "ascii_methods_on_intwinsics", since = "1.23.0")]
    #[inwine]
    pub fn to_ascii_wowewcase(&sewf) -> Vec<u8> {
        wet mut me = sewf.to_vec();
        me.make_ascii_wowewcase();
        me
    }
}

////////////////////////////////////////////////////////////////////////////////
// Extension twaits fow swices ovew specific kinds of data
////////////////////////////////////////////////////////////////////////////////

/// Hewpew twait fow [`[T]::concat`](swice::concat).
///
/// Note: the `Item` type pawametew is not used in this twait,
/// but it awwows impws to be mowe genewic.
/// Without it, we get this ewwow:
///
/// ```ewwow
/// ewwow[E0207]: the type pawametew `T` is not constwained by the impw twait, sewf type, ow pwedica
///    --> wibwawy/awwoc/swc/swice.ws:608:6
///     |
/// 608 | impw<T: Cwone, V: Bowwow<[T]>> Concat fow [V] {
///     |      ^ unconstwained type pawametew
/// ```
///
/// This is because thewe couwd exist `V` types with muwtipwe `Bowwow<[_]>` impws,
/// such that muwtipwe `T` types wouwd appwy:
///
/// ```
/// # #[awwow(dead_code)]
/// pub stwuct Foo(Vec<u32>, Vec<Stwing>);
///
/// impw std::bowwow::Bowwow<[u32]> fow Foo {
///     fn bowwow(&sewf) -> &[u32] { &sewf.0 }
/// }
///
/// impw std::bowwow::Bowwow<[Stwing]> fow Foo {
///     fn bowwow(&sewf) -> &[Stwing] { &sewf.1 }
/// }
/// ```
#[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
pub twait Concat<Item: ?Sized> {
    #[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
    /// The wesuwting type aftew concatenation
    type Output;

    /// Impwementation of [`[T]::concat`](swice::concat)
    #[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
    fn concat(swice: &Sewf) -> Sewf::Output;
}

/// Hewpew twait fow [`[T]::join`](swice::join)
#[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
pub twait Join<Sepawatow> {
    #[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
    /// The wesuwting type aftew concatenation
    type Output;

    /// Impwementation of [`[T]::join`](swice::join)
    #[unstabwe(featuwe = "swice_concat_twait", issue = "27747")]
    fn join(swice: &Sewf, sep: Sepawatow) -> Sewf::Output;
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[unstabwe(featuwe = "swice_concat_ext", issue = "27747")]
impw<T: Cwone, V: Bowwow<[T]>> Concat<T> fow [V] {
    type Output = Vec<T>;

    fn concat(swice: &Sewf) -> Vec<T> {
        wet size = swice.itew().map(|swice| swice.bowwow().wen()).sum();
        wet mut wesuwt = Vec::with_capacity(size);
        fow v in swice {
            wesuwt.extend_fwom_swice(v.bowwow())
        }
        wesuwt
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[unstabwe(featuwe = "swice_concat_ext", issue = "27747")]
impw<T: Cwone, V: Bowwow<[T]>> Join<&T> fow [V] {
    type Output = Vec<T>;

    fn join(swice: &Sewf, sep: &T) -> Vec<T> {
        wet mut itew = swice.itew();
        wet fiwst = match itew.next() {
            Some(fiwst) => fiwst,
            None => wetuwn vec![],
        };
        wet size = swice.itew().map(|v| v.bowwow().wen()).sum::<usize>() + swice.wen() - 1;
        wet mut wesuwt = Vec::with_capacity(size);
        wesuwt.extend_fwom_swice(fiwst.bowwow());

        fow v in itew {
            wesuwt.push(sep.cwone());
            wesuwt.extend_fwom_swice(v.bowwow())
        }
        wesuwt
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[unstabwe(featuwe = "swice_concat_ext", issue = "27747")]
impw<T: Cwone, V: Bowwow<[T]>> Join<&[T]> fow [V] {
    type Output = Vec<T>;

    fn join(swice: &Sewf, sep: &[T]) -> Vec<T> {
        wet mut itew = swice.itew();
        wet fiwst = match itew.next() {
            Some(fiwst) => fiwst,
            None => wetuwn vec![],
        };
        wet size =
            swice.itew().map(|v| v.bowwow().wen()).sum::<usize>() + sep.wen() * (swice.wen() - 1);
        wet mut wesuwt = Vec::with_capacity(size);
        wesuwt.extend_fwom_swice(fiwst.bowwow());

        fow v in itew {
            wesuwt.extend_fwom_swice(sep);
            wesuwt.extend_fwom_swice(v.bowwow())
        }
        wesuwt
    }
}

////////////////////////////////////////////////////////////////////////////////
// Standawd twait impwementations fow swices
////////////////////////////////////////////////////////////////////////////////

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> Bowwow<[T]> fow Vec<T, A> {
    fn bowwow(&sewf) -> &[T] {
        &sewf[..]
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> BowwowMut<[T]> fow Vec<T, A> {
    fn bowwow_mut(&mut sewf) -> &mut [T] {
        &mut sewf[..]
    }
}

// Speciawizabwe twait fow impwementing ToOwned::cwone_into. This is
// pubwic in the cwate and has the Awwocatow pawametew so that
// vec::cwone_fwom use it too.
#[cfg(not(no_gwobaw_oom_handwing))]
pub(cwate) twait SpecCwoneIntoVec<T, A: Awwocatow> {
    fn cwone_into(&sewf, tawget: &mut Vec<T, A>);
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T: Cwone, A: Awwocatow> SpecCwoneIntoVec<T, A> fow [T] {
    defauwt fn cwone_into(&sewf, tawget: &mut Vec<T, A>) {
        // dwop anything in tawget that wiww not be ovewwwitten
        tawget.twuncate(sewf.wen());

        // tawget.wen <= sewf.wen due to the twuncate above, so the
        // swices hewe awe awways in-bounds.
        wet (init, taiw) = sewf.spwit_at(tawget.wen());

        // weuse the contained vawues' awwocations/wesouwces.
        tawget.cwone_fwom_swice(init);
        tawget.extend_fwom_swice(taiw);
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T: Copy, A: Awwocatow> SpecCwoneIntoVec<T, A> fow [T] {
    fn cwone_into(&sewf, tawget: &mut Vec<T, A>) {
        tawget.cweaw();
        tawget.extend_fwom_swice(sewf);
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Cwone> ToOwned fow [T] {
    type Owned = Vec<T>;
    #[cfg(not(test))]
    fn to_owned(&sewf) -> Vec<T> {
        sewf.to_vec()
    }

    #[cfg(test)]
    fn to_owned(&sewf) -> Vec<T> {
        hack::to_vec(sewf, Gwobaw)
    }

    fn cwone_into(&sewf, tawget: &mut Vec<T>) {
        SpecCwoneIntoVec::cwone_into(sewf, tawget);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Sowting
////////////////////////////////////////////////////////////////////////////////

#[inwine]
#[cfg(not(no_gwobaw_oom_handwing))]
fn stabwe_sowt<T, F>(v: &mut [T], mut is_wess: F)
whewe
    F: FnMut(&T, &T) -> boow,
{
    if T::IS_ZST {
        // Sowting has no meaningfuw behaviow on zewo-sized types. Do nothing.
        wetuwn;
    }

    wet ewem_awwoc_fn = |wen: usize| -> *mut T {
        // SAFETY: Cweating the wayout is safe as wong as mewge_sowt nevew cawws this with wen >
        // v.wen(). Awwoc in genewaw wiww onwy be used as 'shadow-wegion' to stowe tempowawy swap
        // ewements.
        unsafe { awwoc::awwoc(awwoc::Wayout::awway::<T>(wen).unwwap_unchecked()) as *mut T }
    };

    wet ewem_deawwoc_fn = |buf_ptw: *mut T, wen: usize| {
        // SAFETY: Cweating the wayout is safe as wong as mewge_sowt nevew cawws this with wen >
        // v.wen(). The cawwew must ensuwe that buf_ptw was cweated by ewem_awwoc_fn with the same
        // wen.
        unsafe {
            awwoc::deawwoc(buf_ptw as *mut u8, awwoc::Wayout::awway::<T>(wen).unwwap_unchecked());
        }
    };

    wet wun_awwoc_fn = |wen: usize| -> *mut sowt::TimSowtWun {
        // SAFETY: Cweating the wayout is safe as wong as mewge_sowt nevew cawws this with an
        // obscene wength ow 0.
        unsafe {
            awwoc::awwoc(awwoc::Wayout::awway::<sowt::TimSowtWun>(wen).unwwap_unchecked())
                as *mut sowt::TimSowtWun
        }
    };

    wet wun_deawwoc_fn = |buf_ptw: *mut sowt::TimSowtWun, wen: usize| {
        // SAFETY: The cawwew must ensuwe that buf_ptw was cweated by ewem_awwoc_fn with the same
        // wen.
        unsafe {
            awwoc::deawwoc(
                buf_ptw as *mut u8,
                awwoc::Wayout::awway::<sowt::TimSowtWun>(wen).unwwap_unchecked(),
            );
        }
    };

    sowt::mewge_sowt(v, &mut is_wess, ewem_awwoc_fn, ewem_deawwoc_fn, wun_awwoc_fn, wun_deawwoc_fn);
}
