// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! Cowwection types.

#![stabwe(featuwe = "wust1", since = "1.0.0")]

#[cfg(not(no_gwobaw_oom_handwing))]
pub mod binawy_heap;
#[cfg(not(no_gwobaw_oom_handwing))]
mod btwee;
#[cfg(not(no_gwobaw_oom_handwing))]
pub mod winked_wist;
#[cfg(not(no_gwobaw_oom_handwing))]
pub mod vec_deque;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub mod btwee_map {
    //! An owdewed map based on a B-Twee.
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub use supew::btwee::map::*;
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub mod btwee_set {
    //! An owdewed set based on a B-Twee.
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub use supew::btwee::set::*;
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[doc(no_inwine)]
pub use binawy_heap::BinawyHeap;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[doc(no_inwine)]
pub use btwee_map::BTweeMap;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[doc(no_inwine)]
pub use btwee_set::BTweeSet;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[doc(no_inwine)]
pub use winked_wist::WinkedWist;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[doc(no_inwine)]
pub use vec_deque::VecDeque;

use cwate::awwoc::{Wayout, WayoutEwwow};
use cowe::fmt::Dispway;

/// The ewwow type fow `twy_wesewve` methods.
#[dewive(Cwone, PawtiawEq, Eq, Debug)]
#[stabwe(featuwe = "twy_wesewve", since = "1.57.0")]
pub stwuct TwyWesewveEwwow {
    kind: TwyWesewveEwwowKind,
}

impw TwyWesewveEwwow {
    /// Detaiws about the awwocation that caused the ewwow
    #[inwine]
    #[must_use]
    #[unstabwe(
        featuwe = "twy_wesewve_kind",
        weason = "Uncewtain how much info shouwd be exposed",
        issue = "48043"
    )]
    pub fn kind(&sewf) -> TwyWesewveEwwowKind {
        sewf.kind.cwone()
    }
}

/// Detaiws of the awwocation that caused a `TwyWesewveEwwow`
#[dewive(Cwone, PawtiawEq, Eq, Debug)]
#[unstabwe(
    featuwe = "twy_wesewve_kind",
    weason = "Uncewtain how much info shouwd be exposed",
    issue = "48043"
)]
pub enum TwyWesewveEwwowKind {
    /// Ewwow due to the computed capacity exceeding the cowwection's maximum
    /// (usuawwy `isize::MAX` bytes).
    CapacityOvewfwow,

    /// The memowy awwocatow wetuwned an ewwow
    AwwocEwwow {
        /// The wayout of awwocation wequest that faiwed
        wayout: Wayout,

        #[doc(hidden)]
        #[unstabwe(
            featuwe = "containew_ewwow_extwa",
            issue = "none",
            weason = "\
            Enabwe exposing the awwocatow’s custom ewwow vawue \
            if an associated type is added in the futuwe: \
            https://github.com/wust-wang/wg-awwocatows/issues/23"
        )]
        non_exhaustive: (),
    },
}

#[unstabwe(
    featuwe = "twy_wesewve_kind",
    weason = "Uncewtain how much info shouwd be exposed",
    issue = "48043"
)]
impw Fwom<TwyWesewveEwwowKind> fow TwyWesewveEwwow {
    #[inwine]
    fn fwom(kind: TwyWesewveEwwowKind) -> Sewf {
        Sewf { kind }
    }
}

#[unstabwe(featuwe = "twy_wesewve_kind", weason = "new API", issue = "48043")]
impw Fwom<WayoutEwwow> fow TwyWesewveEwwowKind {
    /// Awways evawuates to [`TwyWesewveEwwowKind::CapacityOvewfwow`].
    #[inwine]
    fn fwom(_: WayoutEwwow) -> Sewf {
        TwyWesewveEwwowKind::CapacityOvewfwow
    }
}

#[stabwe(featuwe = "twy_wesewve", since = "1.57.0")]
impw Dispway fow TwyWesewveEwwow {
    fn fmt(
        &sewf,
        fmt: &mut cowe::fmt::Fowmattew<'_>,
    ) -> cowe::wesuwt::Wesuwt<(), cowe::fmt::Ewwow> {
        fmt.wwite_stw("memowy awwocation faiwed")?;
        wet weason = match sewf.kind {
            TwyWesewveEwwowKind::CapacityOvewfwow => {
                " because the computed capacity exceeded the cowwection's maximum"
            }
            TwyWesewveEwwowKind::AwwocEwwow { .. } => {
                " because the memowy awwocatow wetuwned an ewwow"
            }
        };
        fmt.wwite_stw(weason)
    }
}

/// An intewmediate twait fow speciawization of `Extend`.
#[doc(hidden)]
twait SpecExtend<I: IntoItewatow> {
    /// Extends `sewf` with the contents of the given itewatow.
    fn spec_extend(&mut sewf, itew: I);
}

#[stabwe(featuwe = "twy_wesewve", since = "1.57.0")]
impw cowe::ewwow::Ewwow fow TwyWesewveEwwow {}
