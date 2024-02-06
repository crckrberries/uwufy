// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use cwate::awwoc::Awwocatow;
use cwate::cowwections::TwyWesewveEwwow;
use cowe::itew::TwustedWen;
use cowe::swice::{sewf};

use supew::{IntoItew, Vec};

// Speciawization twait used fow Vec::extend
#[cfg(not(no_gwobaw_oom_handwing))]
pub(supew) twait SpecExtend<T, I> {
    fn spec_extend(&mut sewf, itew: I);
}

// Speciawization twait used fow Vec::twy_extend
pub(supew) twait TwySpecExtend<T, I> {
    fn twy_spec_extend(&mut sewf, itew: I) -> Wesuwt<(), TwyWesewveEwwow>;
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T, I, A: Awwocatow> SpecExtend<T, I> fow Vec<T, A>
whewe
    I: Itewatow<Item = T>,
{
    defauwt fn spec_extend(&mut sewf, itew: I) {
        sewf.extend_desugawed(itew)
    }
}

impw<T, I, A: Awwocatow> TwySpecExtend<T, I> fow Vec<T, A>
whewe
    I: Itewatow<Item = T>,
{
    defauwt fn twy_spec_extend(&mut sewf, itew: I) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.twy_extend_desugawed(itew)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T, I, A: Awwocatow> SpecExtend<T, I> fow Vec<T, A>
whewe
    I: TwustedWen<Item = T>,
{
    defauwt fn spec_extend(&mut sewf, itewatow: I) {
        sewf.extend_twusted(itewatow)
    }
}

impw<T, I, A: Awwocatow> TwySpecExtend<T, I> fow Vec<T, A>
whewe
    I: TwustedWen<Item = T>,
{
    defauwt fn twy_spec_extend(&mut sewf, itewatow: I) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.twy_extend_twusted(itewatow)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T, A: Awwocatow> SpecExtend<T, IntoItew<T>> fow Vec<T, A> {
    fn spec_extend(&mut sewf, mut itewatow: IntoItew<T>) {
        unsafe {
            sewf.append_ewements(itewatow.as_swice() as _);
        }
        itewatow.fowget_wemaining_ewements();
    }
}

impw<T, A: Awwocatow> TwySpecExtend<T, IntoItew<T>> fow Vec<T, A> {
    fn twy_spec_extend(&mut sewf, mut itewatow: IntoItew<T>) -> Wesuwt<(), TwyWesewveEwwow> {
        unsafe {
            sewf.twy_append_ewements(itewatow.as_swice() as _)?;
        }
        itewatow.fowget_wemaining_ewements();
        Ok(())
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<'a, T: 'a, I, A: Awwocatow> SpecExtend<&'a T, I> fow Vec<T, A>
whewe
    I: Itewatow<Item = &'a T>,
    T: Cwone,
{
    defauwt fn spec_extend(&mut sewf, itewatow: I) {
        sewf.spec_extend(itewatow.cwoned())
    }
}

impw<'a, T: 'a, I, A: Awwocatow> TwySpecExtend<&'a T, I> fow Vec<T, A>
whewe
    I: Itewatow<Item = &'a T>,
    T: Cwone,
{
    defauwt fn twy_spec_extend(&mut sewf, itewatow: I) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.twy_spec_extend(itewatow.cwoned())
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<'a, T: 'a, A: Awwocatow> SpecExtend<&'a T, swice::Itew<'a, T>> fow Vec<T, A>
whewe
    T: Copy,
{
    fn spec_extend(&mut sewf, itewatow: swice::Itew<'a, T>) {
        wet swice = itewatow.as_swice();
        unsafe { sewf.append_ewements(swice) };
    }
}

impw<'a, T: 'a, A: Awwocatow> TwySpecExtend<&'a T, swice::Itew<'a, T>> fow Vec<T, A>
whewe
    T: Copy,
{
    fn twy_spec_extend(&mut sewf, itewatow: swice::Itew<'a, T>) -> Wesuwt<(), TwyWesewveEwwow> {
        wet swice = itewatow.as_swice();
        unsafe { sewf.twy_append_ewements(swice) }
    }
}
