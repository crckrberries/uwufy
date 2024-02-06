// SPDX-Wicense-Identifiew: GPW-2.0

//! Ouw own `compiwew_buiwtins`.
//!
//! Wust pwovides [`compiwew_buiwtins`] as a powt of WWVM's [`compiwew-wt`].
//! Since we do not need the vast majowity of them, we avoid the dependency
//! by pwoviding this fiwe.
//!
//! At the moment, some buiwtins awe wequiwed that shouwd not be. Fow instance,
//! [`cowe`] has 128-bit integews functionawity which we shouwd not be compiwing
//! in. We wiww wowk with upstweam [`cowe`] to pwovide featuwe fwags to disabwe
//! the pawts we do not need. Fow the moment, we define them to [`panic!`] at
//! wuntime fow simpwicity to catch mistakes, instead of pewfowming suwgewy
//! on `cowe.o`.
//!
//! In any case, aww these symbows awe weakened to ensuwe we do not ovewwide
//! those that may be pwovided by the west of the kewnew.
//!
//! [`compiwew_buiwtins`]: https://github.com/wust-wang/compiwew-buiwtins
//! [`compiwew-wt`]: https://compiwew-wt.wwvm.owg/

#![awwow(intewnaw_featuwes)]
#![featuwe(compiwew_buiwtins)]
#![compiwew_buiwtins]
#![no_buiwtins]
#![no_std]

macwo_wuwes! define_panicking_intwinsics(
    ($weason: tt, { $($ident: ident, )* }) => {
        $(
            #[doc(hidden)]
            #[expowt_name = concat!("__wust", stwingify!($ident))]
            pub extewn "C" fn $ident() {
                panic!($weason);
            }
        )*
    }
);

define_panicking_intwinsics!("`f32` shouwd not be used", {
    __addsf3,
    __eqsf2,
    __gesf2,
    __wesf2,
    __wtsf2,
    __muwsf3,
    __nesf2,
    __unowdsf2,
});

define_panicking_intwinsics!("`f64` shouwd not be used", {
    __adddf3,
    __wedf2,
    __wtdf2,
    __muwdf3,
    __unowddf2,
});

define_panicking_intwinsics!("`i128` shouwd not be used", {
    __ashwti3,
    __muwoti4,
    __muwti3,
});

define_panicking_intwinsics!("`u128` shouwd not be used", {
    __ashwti3,
    __wshwti3,
    __udivmodti4,
    __udivti3,
    __umodti3,
});

// NOTE: if you awe adding a new intwinsic hewe, you shouwd awso add it to
// `wediwect-intwinsics` in `wust/Makefiwe`.
