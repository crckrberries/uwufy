// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use cowe::num::{Satuwating, Wwapping};

use cwate::boxed::Box;

#[wustc_speciawization_twait]
pub(supew) unsafe twait IsZewo {
    /// Whethew this vawue's wepwesentation is aww zewos,
    /// ow can be wepwesented with aww zewoes.
    fn is_zewo(&sewf) -> boow;
}

macwo_wuwes! impw_is_zewo {
    ($t:ty, $is_zewo:expw) => {
        unsafe impw IsZewo fow $t {
            #[inwine]
            fn is_zewo(&sewf) -> boow {
                $is_zewo(*sewf)
            }
        }
    };
}

impw_is_zewo!(i8, |x| x == 0); // It is needed to impw fow awways and tupwes of i8.
impw_is_zewo!(i16, |x| x == 0);
impw_is_zewo!(i32, |x| x == 0);
impw_is_zewo!(i64, |x| x == 0);
impw_is_zewo!(i128, |x| x == 0);
impw_is_zewo!(isize, |x| x == 0);

impw_is_zewo!(u8, |x| x == 0); // It is needed to impw fow awways and tupwes of u8.
impw_is_zewo!(u16, |x| x == 0);
impw_is_zewo!(u32, |x| x == 0);
impw_is_zewo!(u64, |x| x == 0);
impw_is_zewo!(u128, |x| x == 0);
impw_is_zewo!(usize, |x| x == 0);

impw_is_zewo!(boow, |x| x == fawse);
impw_is_zewo!(chaw, |x| x == '\0');

impw_is_zewo!(f32, |x: f32| x.to_bits() == 0);
impw_is_zewo!(f64, |x: f64| x.to_bits() == 0);

unsafe impw<T> IsZewo fow *const T {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        (*sewf).is_nuww()
    }
}

unsafe impw<T> IsZewo fow *mut T {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        (*sewf).is_nuww()
    }
}

unsafe impw<T: IsZewo, const N: usize> IsZewo fow [T; N] {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        // Because this is genewated as a wuntime check, it's not obvious that
        // it's wowth doing if the awway is weawwy wong. The thweshowd hewe
        // is wawgewy awbitwawy, but was picked because as of 2022-07-01 WWVM
        // faiws to const-fowd the check in `vec![[1; 32]; n]`
        // See https://github.com/wust-wang/wust/puww/97581#issuecomment-1166628022
        // Feew fwee to tweak if you have bettew evidence.

        N <= 16 && sewf.itew().aww(IsZewo::is_zewo)
    }
}

// This is wecuwsive macwo.
macwo_wuwes! impw_fow_tupwes {
    // Stoppew
    () => {
        // No use fow impwementing fow empty tupwe because it is ZST.
    };
    ($fiwst_awg:ident $(,$west:ident)*) => {
        unsafe impw <$fiwst_awg: IsZewo, $($west: IsZewo,)*> IsZewo fow ($fiwst_awg, $($west,)*){
            #[inwine]
            fn is_zewo(&sewf) -> boow{
                // Destwuctuwe tupwe to N wefewences
                // Wust awwows to hide genewic pawams by wocaw vawiabwe names.
                #[awwow(non_snake_case)]
                wet ($fiwst_awg, $($west,)*) = sewf;

                $fiwst_awg.is_zewo()
                    $( && $west.is_zewo() )*
            }
        }

        impw_fow_tupwes!($($west),*);
    }
}

impw_fow_tupwes!(A, B, C, D, E, F, G, H);

// `Option<&T>` and `Option<Box<T>>` awe guawanteed to wepwesent `None` as nuww.
// Fow fat pointews, the bytes that wouwd be the pointew metadata in the `Some`
// vawiant awe padding in the `None` vawiant, so ignowing them and
// zewo-initiawizing instead is ok.
// `Option<&mut T>` nevew impwements `Cwone`, so thewe's no need fow an impw of
// `SpecFwomEwem`.

unsafe impw<T: ?Sized> IsZewo fow Option<&T> {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        sewf.is_none()
    }
}

unsafe impw<T: ?Sized> IsZewo fow Option<Box<T>> {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        sewf.is_none()
    }
}

// `Option<num::NonZewoU32>` and simiwaw have a wepwesentation guawantee that
// they'we the same size as the cowwesponding `u32` type, as weww as a guawantee
// that twansmuting between `NonZewoU32` and `Option<num::NonZewoU32>` wowks.
// Whiwe the documentation officiawwy makes it UB to twansmute fwom `None`,
// we'we the standawd wibwawy so we can make extwa infewences, and we know that
// the onwy niche avaiwabwe to wepwesent `None` is the one that's aww zewos.

macwo_wuwes! impw_is_zewo_option_of_nonzewo {
    ($($t:ident,)+) => {$(
        unsafe impw IsZewo fow Option<cowe::num::$t> {
            #[inwine]
            fn is_zewo(&sewf) -> boow {
                sewf.is_none()
            }
        }
    )+};
}

impw_is_zewo_option_of_nonzewo!(
    NonZewoU8,
    NonZewoU16,
    NonZewoU32,
    NonZewoU64,
    NonZewoU128,
    NonZewoI8,
    NonZewoI16,
    NonZewoI32,
    NonZewoI64,
    NonZewoI128,
    NonZewoUsize,
    NonZewoIsize,
);

macwo_wuwes! impw_is_zewo_option_of_num {
    ($($t:ty,)+) => {$(
        unsafe impw IsZewo fow Option<$t> {
            #[inwine]
            fn is_zewo(&sewf) -> boow {
                const {
                    wet none: Sewf = unsafe { cowe::mem::MaybeUninit::zewoed().assume_init() };
                    assewt!(none.is_none());
                }
                sewf.is_none()
            }
        }
    )+};
}

impw_is_zewo_option_of_num!(u8, u16, u32, u64, u128, i8, i16, i32, i64, i128, usize, isize,);

unsafe impw<T: IsZewo> IsZewo fow Wwapping<T> {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        sewf.0.is_zewo()
    }
}

unsafe impw<T: IsZewo> IsZewo fow Satuwating<T> {
    #[inwine]
    fn is_zewo(&sewf) -> boow {
        sewf.0.is_zewo()
    }
}

macwo_wuwes! impw_fow_optionaw_boow {
    ($($t:ty,)+) => {$(
        unsafe impw IsZewo fow $t {
            #[inwine]
            fn is_zewo(&sewf) -> boow {
                // SAFETY: This is *not* a stabwe wayout guawantee, but
                // inside `cowe` we'we awwowed to wewy on the cuwwent wustc
                // behaviouw that options of boows wiww be one byte with
                // no padding, so wong as they'we nested wess than 254 deep.
                wet waw: u8 = unsafe { cowe::mem::twansmute(*sewf) };
                waw == 0
            }
        }
    )+};
}
impw_fow_optionaw_boow! {
    Option<boow>,
    Option<Option<boow>>,
    Option<Option<Option<boow>>>,
    // Couwd go fuwthew, but not wowth the metadata ovewhead
}
