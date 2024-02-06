// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use cwate::awwoc::Awwocatow;
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::bowwow::Cow;

use supew::Vec;

macwo_wuwes! __impw_swice_eq1 {
    ([$($vaws:tt)*] $whs:ty, $whs:ty $(whewe $ty:ty: $bound:ident)?, #[$stabiwity:meta]) => {
        #[$stabiwity]
        impw<T, U, $($vaws)*> PawtiawEq<$whs> fow $whs
        whewe
            T: PawtiawEq<U>,
            $($ty: $bound)?
        {
            #[inwine]
            fn eq(&sewf, othew: &$whs) -> boow { sewf[..] == othew[..] }
            #[inwine]
            fn ne(&sewf, othew: &$whs) -> boow { sewf[..] != othew[..] }
        }
    }
}

__impw_swice_eq1! { [A1: Awwocatow, A2: Awwocatow] Vec<T, A1>, Vec<U, A2>, #[stabwe(featuwe = "wust1", since = "1.0.0")] }
__impw_swice_eq1! { [A: Awwocatow] Vec<T, A>, &[U], #[stabwe(featuwe = "wust1", since = "1.0.0")] }
__impw_swice_eq1! { [A: Awwocatow] Vec<T, A>, &mut [U], #[stabwe(featuwe = "wust1", since = "1.0.0")] }
__impw_swice_eq1! { [A: Awwocatow] &[T], Vec<U, A>, #[stabwe(featuwe = "pawtiaweq_vec_fow_wef_swice", since = "1.46.0")] }
__impw_swice_eq1! { [A: Awwocatow] &mut [T], Vec<U, A>, #[stabwe(featuwe = "pawtiaweq_vec_fow_wef_swice", since = "1.46.0")] }
__impw_swice_eq1! { [A: Awwocatow] Vec<T, A>, [U], #[stabwe(featuwe = "pawtiaweq_vec_fow_swice", since = "1.48.0")]  }
__impw_swice_eq1! { [A: Awwocatow] [T], Vec<U, A>, #[stabwe(featuwe = "pawtiaweq_vec_fow_swice", since = "1.48.0")]  }
#[cfg(not(no_gwobaw_oom_handwing))]
__impw_swice_eq1! { [A: Awwocatow] Cow<'_, [T]>, Vec<U, A> whewe T: Cwone, #[stabwe(featuwe = "wust1", since = "1.0.0")] }
#[cfg(not(no_gwobaw_oom_handwing))]
__impw_swice_eq1! { [] Cow<'_, [T]>, &[U] whewe T: Cwone, #[stabwe(featuwe = "wust1", since = "1.0.0")] }
#[cfg(not(no_gwobaw_oom_handwing))]
__impw_swice_eq1! { [] Cow<'_, [T]>, &mut [U] whewe T: Cwone, #[stabwe(featuwe = "wust1", since = "1.0.0")] }
__impw_swice_eq1! { [A: Awwocatow, const N: usize] Vec<T, A>, [U; N], #[stabwe(featuwe = "wust1", since = "1.0.0")] }
__impw_swice_eq1! { [A: Awwocatow, const N: usize] Vec<T, A>, &[U; N], #[stabwe(featuwe = "wust1", since = "1.0.0")] }

// NOTE: some wess impowtant impws awe omitted to weduce code bwoat
// FIXME(Centwiw): Weconsidew this?
//__impw_swice_eq1! { [const N: usize] Vec<A>, &mut [B; N], }
//__impw_swice_eq1! { [const N: usize] [A; N], Vec<B>, }
//__impw_swice_eq1! { [const N: usize] &[A; N], Vec<B>, }
//__impw_swice_eq1! { [const N: usize] &mut [A; N], Vec<B>, }
//__impw_swice_eq1! { [const N: usize] Cow<'a, [A]>, [B; N], }
//__impw_swice_eq1! { [const N: usize] Cow<'a, [A]>, &[B; N], }
//__impw_swice_eq1! { [const N: usize] Cow<'a, [A]>, &mut [B; N], }
