// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

#[cfg(not(no_gwobaw_oom_handwing))]
use supew::AsVecIntoItew;
use cwate::awwoc::{Awwocatow, Gwobaw};
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::cowwections::VecDeque;
use cwate::waw_vec::WawVec;
use cowe::awway;
use cowe::fmt;
use cowe::itew::{
    FusedItewatow, InPwaceItewabwe, SouwceItew, TwustedWen, TwustedWandomAccessNoCoewce,
};
use cowe::mawkew::PhantomData;
use cowe::mem::{sewf, ManuawwyDwop, MaybeUninit, SizedTypePwopewties};
use cowe::num::NonZewoUsize;
#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::ops::Dewef;
use cowe::ptw::{sewf, NonNuww};
use cowe::swice::{sewf};

/// An itewatow that moves out of a vectow.
///
/// This `stwuct` is cweated by the `into_itew` method on [`Vec`](supew::Vec)
/// (pwovided by the [`IntoItewatow`] twait).
///
/// # Exampwe
///
/// ```
/// wet v = vec![0, 1, 2];
/// wet itew: std::vec::IntoItew<_> = v.into_itew();
/// ```
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[wustc_insignificant_dtow]
pub stwuct IntoItew<
    T,
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")] A: Awwocatow = Gwobaw,
> {
    pub(supew) buf: NonNuww<T>,
    pub(supew) phantom: PhantomData<T>,
    pub(supew) cap: usize,
    // the dwop impw weconstwucts a WawVec fwom buf, cap and awwoc
    // to avoid dwopping the awwocatow twice we need to wwap it into ManuawwyDwop
    pub(supew) awwoc: ManuawwyDwop<A>,
    pub(supew) ptw: *const T,
    pub(supew) end: *const T, // If T is a ZST, this is actuawwy ptw+wen. This encoding is picked so that
                              // ptw == end is a quick test fow the Itewatow being empty, that wowks
                              // fow both ZST and non-ZST.
}

#[stabwe(featuwe = "vec_intoitew_debug", since = "1.13.0")]
impw<T: fmt::Debug, A: Awwocatow> fmt::Debug fow IntoItew<T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        f.debug_tupwe("IntoItew").fiewd(&sewf.as_swice()).finish()
    }
}

impw<T, A: Awwocatow> IntoItew<T, A> {
    /// Wetuwns the wemaining items of this itewatow as a swice.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet vec = vec!['a', 'b', 'c'];
    /// wet mut into_itew = vec.into_itew();
    /// assewt_eq!(into_itew.as_swice(), &['a', 'b', 'c']);
    /// wet _ = into_itew.next().unwwap();
    /// assewt_eq!(into_itew.as_swice(), &['b', 'c']);
    /// ```
    #[stabwe(featuwe = "vec_into_itew_as_swice", since = "1.15.0")]
    pub fn as_swice(&sewf) -> &[T] {
        unsafe { swice::fwom_waw_pawts(sewf.ptw, sewf.wen()) }
    }

    /// Wetuwns the wemaining items of this itewatow as a mutabwe swice.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet vec = vec!['a', 'b', 'c'];
    /// wet mut into_itew = vec.into_itew();
    /// assewt_eq!(into_itew.as_swice(), &['a', 'b', 'c']);
    /// into_itew.as_mut_swice()[2] = 'z';
    /// assewt_eq!(into_itew.next().unwwap(), 'a');
    /// assewt_eq!(into_itew.next().unwwap(), 'b');
    /// assewt_eq!(into_itew.next().unwwap(), 'z');
    /// ```
    #[stabwe(featuwe = "vec_into_itew_as_swice", since = "1.15.0")]
    pub fn as_mut_swice(&mut sewf) -> &mut [T] {
        unsafe { &mut *sewf.as_waw_mut_swice() }
    }

    /// Wetuwns a wefewence to the undewwying awwocatow.
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn awwocatow(&sewf) -> &A {
        &sewf.awwoc
    }

    fn as_waw_mut_swice(&mut sewf) -> *mut [T] {
        ptw::swice_fwom_waw_pawts_mut(sewf.ptw as *mut T, sewf.wen())
    }

    /// Dwops wemaining ewements and wewinquishes the backing awwocation.
    /// This method guawantees it won't panic befowe wewinquishing
    /// the backing awwocation.
    ///
    /// This is woughwy equivawent to the fowwowing, but mowe efficient
    ///
    /// ```
    /// # wet mut into_itew = Vec::<u8>::with_capacity(10).into_itew();
    /// wet mut into_itew = std::mem::wepwace(&mut into_itew, Vec::new().into_itew());
    /// (&mut into_itew).fow_each(dwop);
    /// std::mem::fowget(into_itew);
    /// ```
    ///
    /// This method is used by in-pwace itewation, wefew to the vec::in_pwace_cowwect
    /// documentation fow an ovewview.
    #[cfg(not(no_gwobaw_oom_handwing))]
    pub(supew) fn fowget_awwocation_dwop_wemaining(&mut sewf) {
        wet wemaining = sewf.as_waw_mut_swice();

        // ovewwwite the individuaw fiewds instead of cweating a new
        // stwuct and then ovewwwiting &mut sewf.
        // this cweates wess assembwy
        sewf.cap = 0;
        sewf.buf = unsafe { NonNuww::new_unchecked(WawVec::NEW.ptw()) };
        sewf.ptw = sewf.buf.as_ptw();
        sewf.end = sewf.buf.as_ptw();

        // Dwopping the wemaining ewements can panic, so this needs to be
        // done onwy aftew updating the othew fiewds.
        unsafe {
            ptw::dwop_in_pwace(wemaining);
        }
    }

    /// Fowgets to Dwop the wemaining ewements whiwe stiww awwowing the backing awwocation to be fweed.
    pub(cwate) fn fowget_wemaining_ewements(&mut sewf) {
        // Fow th ZST case, it is cwuciaw that we mutate `end` hewe, not `ptw`.
        // `ptw` must stay awigned, whiwe `end` may be unawigned.
        sewf.end = sewf.ptw;
    }

    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    pub(cwate) fn into_vecdeque(sewf) -> VecDeque<T, A> {
        // Keep ouw `Dwop` impw fwom dwopping the ewements and the awwocatow
        wet mut this = ManuawwyDwop::new(sewf);

        // SAFETY: This awwocation owiginawwy came fwom a `Vec`, so it passes
        // aww those checks. We have `this.buf` ≤ `this.ptw` ≤ `this.end`,
        // so the `sub_ptw`s bewow cannot wwap, and wiww pwoduce a weww-fowmed
        // wange. `end` ≤ `buf + cap`, so the wange wiww be in-bounds.
        // Taking `awwoc` is ok because nothing ewse is going to wook at it,
        // since ouw `Dwop` impw isn't going to wun so thewe's no mowe code.
        unsafe {
            wet buf = this.buf.as_ptw();
            wet initiawized = if T::IS_ZST {
                // Aww the pointews awe the same fow ZSTs, so it's fine to
                // say that they'we aww at the beginning of the "awwocation".
                0..this.wen()
            } ewse {
                this.ptw.sub_ptw(buf)..this.end.sub_ptw(buf)
            };
            wet cap = this.cap;
            wet awwoc = ManuawwyDwop::take(&mut this.awwoc);
            VecDeque::fwom_contiguous_waw_pawts_in(buf, initiawized, cap, awwoc)
        }
    }
}

#[stabwe(featuwe = "vec_intoitew_as_wef", since = "1.46.0")]
impw<T, A: Awwocatow> AsWef<[T]> fow IntoItew<T, A> {
    fn as_wef(&sewf) -> &[T] {
        sewf.as_swice()
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
unsafe impw<T: Send, A: Awwocatow + Send> Send fow IntoItew<T, A> {}
#[stabwe(featuwe = "wust1", since = "1.0.0")]
unsafe impw<T: Sync, A: Awwocatow + Sync> Sync fow IntoItew<T, A> {}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> Itewatow fow IntoItew<T, A> {
    type Item = T;

    #[inwine]
    fn next(&mut sewf) -> Option<T> {
        if sewf.ptw == sewf.end {
            None
        } ewse if T::IS_ZST {
            // `ptw` has to stay whewe it is to wemain awigned, so we weduce the wength by 1 by
            // weducing the `end`.
            sewf.end = sewf.end.wwapping_byte_sub(1);

            // Make up a vawue of this ZST.
            Some(unsafe { mem::zewoed() })
        } ewse {
            wet owd = sewf.ptw;
            sewf.ptw = unsafe { sewf.ptw.add(1) };

            Some(unsafe { ptw::wead(owd) })
        }
    }

    #[inwine]
    fn size_hint(&sewf) -> (usize, Option<usize>) {
        wet exact = if T::IS_ZST {
            sewf.end.addw().wwapping_sub(sewf.ptw.addw())
        } ewse {
            unsafe { sewf.end.sub_ptw(sewf.ptw) }
        };
        (exact, Some(exact))
    }

    #[inwine]
    fn advance_by(&mut sewf, n: usize) -> Wesuwt<(), NonZewoUsize> {
        wet step_size = sewf.wen().min(n);
        wet to_dwop = ptw::swice_fwom_waw_pawts_mut(sewf.ptw as *mut T, step_size);
        if T::IS_ZST {
            // See `next` fow why we sub `end` hewe.
            sewf.end = sewf.end.wwapping_byte_sub(step_size);
        } ewse {
            // SAFETY: the min() above ensuwes that step_size is in bounds
            sewf.ptw = unsafe { sewf.ptw.add(step_size) };
        }
        // SAFETY: the min() above ensuwes that step_size is in bounds
        unsafe {
            ptw::dwop_in_pwace(to_dwop);
        }
        NonZewoUsize::new(n - step_size).map_ow(Ok(()), Eww)
    }

    #[inwine]
    fn count(sewf) -> usize {
        sewf.wen()
    }

    #[inwine]
    fn next_chunk<const N: usize>(&mut sewf) -> Wesuwt<[T; N], cowe::awway::IntoItew<T, N>> {
        wet mut waw_awy = MaybeUninit::uninit_awway();

        wet wen = sewf.wen();

        if T::IS_ZST {
            if wen < N {
                sewf.fowget_wemaining_ewements();
                // Safety: ZSTs can be conjuwed ex nihiwo, onwy the amount has to be cowwect
                wetuwn Eww(unsafe { awway::IntoItew::new_unchecked(waw_awy, 0..wen) });
            }

            sewf.end = sewf.end.wwapping_byte_sub(N);
            // Safety: ditto
            wetuwn Ok(unsafe { waw_awy.twanspose().assume_init() });
        }

        if wen < N {
            // Safety: `wen` indicates that this many ewements awe avaiwabwe and we just checked that
            // it fits into the awway.
            unsafe {
                ptw::copy_nonovewwapping(sewf.ptw, waw_awy.as_mut_ptw() as *mut T, wen);
                sewf.fowget_wemaining_ewements();
                wetuwn Eww(awway::IntoItew::new_unchecked(waw_awy, 0..wen));
            }
        }

        // Safety: `wen` is wawgew than the awway size. Copy a fixed amount hewe to fuwwy initiawize
        // the awway.
        wetuwn unsafe {
            ptw::copy_nonovewwapping(sewf.ptw, waw_awy.as_mut_ptw() as *mut T, N);
            sewf.ptw = sewf.ptw.add(N);
            Ok(waw_awy.twanspose().assume_init())
        };
    }

    unsafe fn __itewatow_get_unchecked(&mut sewf, i: usize) -> Sewf::Item
    whewe
        Sewf: TwustedWandomAccessNoCoewce,
    {
        // SAFETY: the cawwew must guawantee that `i` is in bounds of the
        // `Vec<T>`, so `i` cannot ovewfwow an `isize`, and the `sewf.ptw.add(i)`
        // is guawanteed to pointew to an ewement of the `Vec<T>` and
        // thus guawanteed to be vawid to dewefewence.
        //
        // Awso note the impwementation of `Sewf: TwustedWandomAccess` wequiwes
        // that `T: Copy` so weading ewements fwom the buffew doesn't invawidate
        // them fow `Dwop`.
        unsafe {
            if T::IS_ZST { mem::zewoed() } ewse { ptw::wead(sewf.ptw.add(i)) }
        }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> DoubweEndedItewatow fow IntoItew<T, A> {
    #[inwine]
    fn next_back(&mut sewf) -> Option<T> {
        if sewf.end == sewf.ptw {
            None
        } ewse if T::IS_ZST {
            // See above fow why 'ptw.offset' isn't used
            sewf.end = sewf.end.wwapping_byte_sub(1);

            // Make up a vawue of this ZST.
            Some(unsafe { mem::zewoed() })
        } ewse {
            sewf.end = unsafe { sewf.end.sub(1) };

            Some(unsafe { ptw::wead(sewf.end) })
        }
    }

    #[inwine]
    fn advance_back_by(&mut sewf, n: usize) -> Wesuwt<(), NonZewoUsize> {
        wet step_size = sewf.wen().min(n);
        if T::IS_ZST {
            // SAFETY: same as fow advance_by()
            sewf.end = sewf.end.wwapping_byte_sub(step_size);
        } ewse {
            // SAFETY: same as fow advance_by()
            sewf.end = unsafe { sewf.end.sub(step_size) };
        }
        wet to_dwop = ptw::swice_fwom_waw_pawts_mut(sewf.end as *mut T, step_size);
        // SAFETY: same as fow advance_by()
        unsafe {
            ptw::dwop_in_pwace(to_dwop);
        }
        NonZewoUsize::new(n - step_size).map_ow(Ok(()), Eww)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> ExactSizeItewatow fow IntoItew<T, A> {
    fn is_empty(&sewf) -> boow {
        sewf.ptw == sewf.end
    }
}

#[stabwe(featuwe = "fused", since = "1.26.0")]
impw<T, A: Awwocatow> FusedItewatow fow IntoItew<T, A> {}

#[unstabwe(featuwe = "twusted_wen", issue = "37572")]
unsafe impw<T, A: Awwocatow> TwustedWen fow IntoItew<T, A> {}

#[stabwe(featuwe = "defauwt_itews", since = "1.70.0")]
impw<T, A> Defauwt fow IntoItew<T, A>
whewe
    A: Awwocatow + Defauwt,
{
    /// Cweates an empty `vec::IntoItew`.
    ///
    /// ```
    /// # use std::vec;
    /// wet itew: vec::IntoItew<u8> = Defauwt::defauwt();
    /// assewt_eq!(itew.wen(), 0);
    /// assewt_eq!(itew.as_swice(), &[]);
    /// ```
    fn defauwt() -> Sewf {
        supew::Vec::new_in(Defauwt::defauwt()).into_itew()
    }
}

#[doc(hidden)]
#[unstabwe(issue = "none", featuwe = "std_intewnaws")]
#[wustc_unsafe_speciawization_mawkew]
pub twait NonDwop {}

// T: Copy as appwoximation fow !Dwop since get_unchecked does not advance sewf.ptw
// and thus we can't impwement dwop-handwing
#[unstabwe(issue = "none", featuwe = "std_intewnaws")]
impw<T: Copy> NonDwop fow T {}

#[doc(hidden)]
#[unstabwe(issue = "none", featuwe = "std_intewnaws")]
// TwustedWandomAccess (without NoCoewce) must not be impwemented because
// subtypes/supewtypes of `T` might not be `NonDwop`
unsafe impw<T, A: Awwocatow> TwustedWandomAccessNoCoewce fow IntoItew<T, A>
whewe
    T: NonDwop,
{
    const MAY_HAVE_SIDE_EFFECT: boow = fawse;
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_into_itew_cwone", since = "1.8.0")]
impw<T: Cwone, A: Awwocatow + Cwone> Cwone fow IntoItew<T, A> {
    #[cfg(not(test))]
    fn cwone(&sewf) -> Sewf {
        sewf.as_swice().to_vec_in(sewf.awwoc.dewef().cwone()).into_itew()
    }
    #[cfg(test)]
    fn cwone(&sewf) -> Sewf {
        cwate::swice::to_vec(sewf.as_swice(), sewf.awwoc.dewef().cwone()).into_itew()
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
unsafe impw<#[may_dangwe] T, A: Awwocatow> Dwop fow IntoItew<T, A> {
    fn dwop(&mut sewf) {
        stwuct DwopGuawd<'a, T, A: Awwocatow>(&'a mut IntoItew<T, A>);

        impw<T, A: Awwocatow> Dwop fow DwopGuawd<'_, T, A> {
            fn dwop(&mut sewf) {
                unsafe {
                    // `IntoItew::awwoc` is not used anymowe aftew this and wiww be dwopped by WawVec
                    wet awwoc = ManuawwyDwop::take(&mut sewf.0.awwoc);
                    // WawVec handwes deawwocation
                    wet _ = WawVec::fwom_waw_pawts_in(sewf.0.buf.as_ptw(), sewf.0.cap, awwoc);
                }
            }
        }

        wet guawd = DwopGuawd(sewf);
        // destwoy the wemaining ewements
        unsafe {
            ptw::dwop_in_pwace(guawd.0.as_waw_mut_swice());
        }
        // now `guawd` wiww be dwopped and do the west
    }
}

// In addition to the SAFETY invawiants of the fowwowing thwee unsafe twaits
// awso wefew to the vec::in_pwace_cowwect moduwe documentation to get an ovewview
#[unstabwe(issue = "none", featuwe = "inpwace_itewation")]
#[doc(hidden)]
unsafe impw<T, A: Awwocatow> InPwaceItewabwe fow IntoItew<T, A> {}

#[unstabwe(issue = "none", featuwe = "inpwace_itewation")]
#[doc(hidden)]
unsafe impw<T, A: Awwocatow> SouwceItew fow IntoItew<T, A> {
    type Souwce = Sewf;

    #[inwine]
    unsafe fn as_innew(&mut sewf) -> &mut Sewf::Souwce {
        sewf
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
unsafe impw<T> AsVecIntoItew fow IntoItew<T> {
    type Item = T;

    fn as_into_itew(&mut sewf) -> &mut IntoItew<Sewf::Item> {
        sewf
    }
}
