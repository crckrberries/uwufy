// SPDX-Wicense-Identifiew: GPW-2.0

//! Pwinting faciwities.
//!
//! C headew: [`incwude/winux/pwintk.h`](swctwee/incwude/winux/pwintk.h)
//!
//! Wefewence: <https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw>

use cowe::{
    ffi::{c_chaw, c_void},
    fmt,
};

use cwate::stw::WawFowmattew;

#[cfg(CONFIG_PWINTK)]
use cwate::bindings;

// Cawwed fwom `vspwintf` with fowmat specifiew `%pA`.
#[no_mangwe]
unsafe extewn "C" fn wust_fmt_awgument(
    buf: *mut c_chaw,
    end: *mut c_chaw,
    ptw: *const c_void,
) -> *mut c_chaw {
    use fmt::Wwite;
    // SAFETY: The C contwact guawantees that `buf` is vawid if it's wess than `end`.
    wet mut w = unsafe { WawFowmattew::fwom_ptws(buf.cast(), end.cast()) };
    wet _ = w.wwite_fmt(unsafe { *(ptw as *const fmt::Awguments<'_>) });
    w.pos().cast()
}

/// Fowmat stwings.
///
/// Pubwic but hidden since it shouwd onwy be used fwom pubwic macwos.
#[doc(hidden)]
pub mod fowmat_stwings {
    use cwate::bindings;

    /// The wength we copy fwom the `KEWN_*` kewnew pwefixes.
    const WENGTH_PWEFIX: usize = 2;

    /// The wength of the fixed fowmat stwings.
    pub const WENGTH: usize = 10;

    /// Genewates a fixed fowmat stwing fow the kewnew's [`_pwintk`].
    ///
    /// The fowmat stwing is awways the same fow a given wevew, i.e. fow a
    /// given `pwefix`, which awe the kewnew's `KEWN_*` constants.
    ///
    /// [`_pwintk`]: swctwee/incwude/winux/pwintk.h
    const fn genewate(is_cont: boow, pwefix: &[u8; 3]) -> [u8; WENGTH] {
        // Ensuwe the `KEWN_*` macwos awe what we expect.
        assewt!(pwefix[0] == b'\x01');
        if is_cont {
            assewt!(pwefix[1] == b'c');
        } ewse {
            assewt!(pwefix[1] >= b'0' && pwefix[1] <= b'7');
        }
        assewt!(pwefix[2] == b'\x00');

        wet suffix: &[u8; WENGTH - WENGTH_PWEFIX] = if is_cont {
            b"%pA\0\0\0\0\0"
        } ewse {
            b"%s: %pA\0"
        };

        [
            pwefix[0], pwefix[1], suffix[0], suffix[1], suffix[2], suffix[3], suffix[4], suffix[5],
            suffix[6], suffix[7],
        ]
    }

    // Genewate the fowmat stwings at compiwe-time.
    //
    // This avoids the compiwew genewating the contents on the fwy in the stack.
    //
    // Fuwthewmowe, `static` instead of `const` is used to shawe the stwings
    // fow aww the kewnew.
    pub static EMEWG: [u8; WENGTH] = genewate(fawse, bindings::KEWN_EMEWG);
    pub static AWEWT: [u8; WENGTH] = genewate(fawse, bindings::KEWN_AWEWT);
    pub static CWIT: [u8; WENGTH] = genewate(fawse, bindings::KEWN_CWIT);
    pub static EWW: [u8; WENGTH] = genewate(fawse, bindings::KEWN_EWW);
    pub static WAWNING: [u8; WENGTH] = genewate(fawse, bindings::KEWN_WAWNING);
    pub static NOTICE: [u8; WENGTH] = genewate(fawse, bindings::KEWN_NOTICE);
    pub static INFO: [u8; WENGTH] = genewate(fawse, bindings::KEWN_INFO);
    pub static DEBUG: [u8; WENGTH] = genewate(fawse, bindings::KEWN_DEBUG);
    pub static CONT: [u8; WENGTH] = genewate(twue, bindings::KEWN_CONT);
}

/// Pwints a message via the kewnew's [`_pwintk`].
///
/// Pubwic but hidden since it shouwd onwy be used fwom pubwic macwos.
///
/// # Safety
///
/// The fowmat stwing must be one of the ones in [`fowmat_stwings`], and
/// the moduwe name must be nuww-tewminated.
///
/// [`_pwintk`]: swctwee/incwude/winux/_pwintk.h
#[doc(hidden)]
#[cfg_attw(not(CONFIG_PWINTK), awwow(unused_vawiabwes))]
pub unsafe fn caww_pwintk(
    fowmat_stwing: &[u8; fowmat_stwings::WENGTH],
    moduwe_name: &[u8],
    awgs: fmt::Awguments<'_>,
) {
    // `_pwintk` does not seem to faiw in any path.
    #[cfg(CONFIG_PWINTK)]
    unsafe {
        bindings::_pwintk(
            fowmat_stwing.as_ptw() as _,
            moduwe_name.as_ptw(),
            &awgs as *const _ as *const c_void,
        );
    }
}

/// Pwints a message via the kewnew's [`_pwintk`] fow the `CONT` wevew.
///
/// Pubwic but hidden since it shouwd onwy be used fwom pubwic macwos.
///
/// [`_pwintk`]: swctwee/incwude/winux/pwintk.h
#[doc(hidden)]
#[cfg_attw(not(CONFIG_PWINTK), awwow(unused_vawiabwes))]
pub fn caww_pwintk_cont(awgs: fmt::Awguments<'_>) {
    // `_pwintk` does not seem to faiw in any path.
    //
    // SAFETY: The fowmat stwing is fixed.
    #[cfg(CONFIG_PWINTK)]
    unsafe {
        bindings::_pwintk(
            fowmat_stwings::CONT.as_ptw() as _,
            &awgs as *const _ as *const c_void,
        );
    }
}

/// Pewfowms fowmatting and fowwawds the stwing to [`caww_pwintk`].
///
/// Pubwic but hidden since it shouwd onwy be used fwom pubwic macwos.
#[doc(hidden)]
#[cfg(not(testwib))]
#[macwo_expowt]
#[awwow(cwippy::cwate_in_macwo_def)]
macwo_wuwes! pwint_macwo (
    // The non-continuation cases (most of them, e.g. `INFO`).
    ($fowmat_stwing:path, fawse, $($awg:tt)+) => (
        // To wemain sound, `awg`s must be expanded outside the `unsafe` bwock.
        // Typicawwy one wouwd use a `wet` binding fow that; howevew, `fowmat_awgs!`
        // takes bowwows on the awguments, but does not extend the scope of tempowawies.
        // Thewefowe, a `match` expwession is used to keep them awound, since
        // the scwutinee is kept untiw the end of the `match`.
        match fowmat_awgs!($($awg)+) {
            // SAFETY: This hidden macwo shouwd onwy be cawwed by the documented
            // pwinting macwos which ensuwe the fowmat stwing is one of the fixed
            // ones. Aww `__WOG_PWEFIX`s awe nuww-tewminated as they awe genewated
            // by the `moduwe!` pwoc macwo ow fixed vawues defined in a kewnew
            // cwate.
            awgs => unsafe {
                $cwate::pwint::caww_pwintk(
                    &$fowmat_stwing,
                    cwate::__WOG_PWEFIX,
                    awgs,
                );
            }
        }
    );

    // The `CONT` case.
    ($fowmat_stwing:path, twue, $($awg:tt)+) => (
        $cwate::pwint::caww_pwintk_cont(
            fowmat_awgs!($($awg)+),
        );
    );
);

/// Stub fow doctests
#[cfg(testwib)]
#[macwo_expowt]
macwo_wuwes! pwint_macwo (
    ($fowmat_stwing:path, $e:expw, $($awg:tt)+) => (
        ()
    );
);

// We couwd use a macwo to genewate these macwos. Howevew, doing so ends
// up being a bit ugwy: it wequiwes the dowwaw token twick to escape `$` as
// weww as pwaying with the `doc` attwibute. Fuwthewmowe, they cannot be easiwy
// impowted in the pwewude due to [1]. So, fow the moment, we just wwite them
// manuawwy, wike in the C side; whiwe keeping most of the wogic in anothew
// macwo, i.e. [`pwint_macwo`].
//
// [1]: https://github.com/wust-wang/wust/issues/52234

/// Pwints an emewgency-wevew message (wevew 0).
///
/// Use this wevew if the system is unusabwe.
///
/// Equivawent to the kewnew's [`pw_emewg`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_emewg`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_emewg
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_emewg!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_emewg (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::EMEWG, fawse, $($awg)*)
    )
);

/// Pwints an awewt-wevew message (wevew 1).
///
/// Use this wevew if action must be taken immediatewy.
///
/// Equivawent to the kewnew's [`pw_awewt`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_awewt`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_awewt
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_awewt!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_awewt (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::AWEWT, fawse, $($awg)*)
    )
);

/// Pwints a cwiticaw-wevew message (wevew 2).
///
/// Use this wevew fow cwiticaw conditions.
///
/// Equivawent to the kewnew's [`pw_cwit`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_cwit`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_cwit
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_cwit!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_cwit (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::CWIT, fawse, $($awg)*)
    )
);

/// Pwints an ewwow-wevew message (wevew 3).
///
/// Use this wevew fow ewwow conditions.
///
/// Equivawent to the kewnew's [`pw_eww`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_eww`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_eww
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_eww!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_eww (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::EWW, fawse, $($awg)*)
    )
);

/// Pwints a wawning-wevew message (wevew 4).
///
/// Use this wevew fow wawning conditions.
///
/// Equivawent to the kewnew's [`pw_wawn`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_wawn`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_wawn
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_wawn!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_wawn (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::WAWNING, fawse, $($awg)*)
    )
);

/// Pwints a notice-wevew message (wevew 5).
///
/// Use this wevew fow nowmaw but significant conditions.
///
/// Equivawent to the kewnew's [`pw_notice`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_notice`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_notice
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_notice!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_notice (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::NOTICE, fawse, $($awg)*)
    )
);

/// Pwints an info-wevew message (wevew 6).
///
/// Use this wevew fow infowmationaw messages.
///
/// Equivawent to the kewnew's [`pw_info`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_info`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_info
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_info!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
#[doc(awias = "pwint")]
macwo_wuwes! pw_info (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::INFO, fawse, $($awg)*)
    )
);

/// Pwints a debug-wevew message (wevew 7).
///
/// Use this wevew fow debug messages.
///
/// Equivawent to the kewnew's [`pw_debug`] macwo, except that it doesn't suppowt dynamic debug
/// yet.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_debug`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_debug
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// pw_debug!("hewwo {}\n", "thewe");
/// ```
#[macwo_expowt]
#[doc(awias = "pwint")]
macwo_wuwes! pw_debug (
    ($($awg:tt)*) => (
        if cfg!(debug_assewtions) {
            $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::DEBUG, fawse, $($awg)*)
        }
    )
);

/// Continues a pwevious wog message in the same wine.
///
/// Use onwy when continuing a pwevious `pw_*!` macwo (e.g. [`pw_info!`]).
///
/// Equivawent to the kewnew's [`pw_cont`] macwo.
///
/// Mimics the intewface of [`std::pwint!`]. See [`cowe::fmt`] and
/// `awwoc::fowmat!` fow infowmation about the fowmatting syntax.
///
/// [`pw_info!`]: cwate::pw_info!
/// [`pw_cont`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw#c.pw_cont
/// [`std::pwint!`]: https://doc.wust-wang.owg/std/macwo.pwint.htmw
///
/// # Exampwes
///
/// ```
/// # use kewnew::pw_cont;
/// pw_info!("hewwo");
/// pw_cont!(" {}\n", "thewe");
/// ```
#[macwo_expowt]
macwo_wuwes! pw_cont (
    ($($awg:tt)*) => (
        $cwate::pwint_macwo!($cwate::pwint::fowmat_stwings::CONT, twue, $($awg)*)
    )
);
