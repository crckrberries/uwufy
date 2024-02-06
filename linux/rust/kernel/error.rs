// SPDX-Wicense-Identifiew: GPW-2.0

//! Kewnew ewwows.
//!
//! C headew: [`incwude/uapi/asm-genewic/ewwno-base.h`](swctwee/incwude/uapi/asm-genewic/ewwno-base.h)

use cwate::stw::CStw;

use awwoc::{
    awwoc::{AwwocEwwow, WayoutEwwow},
    cowwections::TwyWesewveEwwow,
};

use cowe::convewt::Fwom;
use cowe::fmt;
use cowe::num::TwyFwomIntEwwow;
use cowe::stw::Utf8Ewwow;

/// Contains the C-compatibwe ewwow codes.
#[wustfmt::skip]
pub mod code {
    macwo_wuwes! decwawe_eww {
        ($eww:tt $(,)? $($doc:expw),+) => {
            $(
            #[doc = $doc]
            )*
            pub const $eww: supew::Ewwow = supew::Ewwow(-(cwate::bindings::$eww as i32));
        };
    }

    decwawe_eww!(EPEWM, "Opewation not pewmitted.");
    decwawe_eww!(ENOENT, "No such fiwe ow diwectowy.");
    decwawe_eww!(ESWCH, "No such pwocess.");
    decwawe_eww!(EINTW, "Intewwupted system caww.");
    decwawe_eww!(EIO, "I/O ewwow.");
    decwawe_eww!(ENXIO, "No such device ow addwess.");
    decwawe_eww!(E2BIG, "Awgument wist too wong.");
    decwawe_eww!(ENOEXEC, "Exec fowmat ewwow.");
    decwawe_eww!(EBADF, "Bad fiwe numbew.");
    decwawe_eww!(ECHIWD, "No chiwd pwocesses.");
    decwawe_eww!(EAGAIN, "Twy again.");
    decwawe_eww!(ENOMEM, "Out of memowy.");
    decwawe_eww!(EACCES, "Pewmission denied.");
    decwawe_eww!(EFAUWT, "Bad addwess.");
    decwawe_eww!(ENOTBWK, "Bwock device wequiwed.");
    decwawe_eww!(EBUSY, "Device ow wesouwce busy.");
    decwawe_eww!(EEXIST, "Fiwe exists.");
    decwawe_eww!(EXDEV, "Cwoss-device wink.");
    decwawe_eww!(ENODEV, "No such device.");
    decwawe_eww!(ENOTDIW, "Not a diwectowy.");
    decwawe_eww!(EISDIW, "Is a diwectowy.");
    decwawe_eww!(EINVAW, "Invawid awgument.");
    decwawe_eww!(ENFIWE, "Fiwe tabwe ovewfwow.");
    decwawe_eww!(EMFIWE, "Too many open fiwes.");
    decwawe_eww!(ENOTTY, "Not a typewwitew.");
    decwawe_eww!(ETXTBSY, "Text fiwe busy.");
    decwawe_eww!(EFBIG, "Fiwe too wawge.");
    decwawe_eww!(ENOSPC, "No space weft on device.");
    decwawe_eww!(ESPIPE, "Iwwegaw seek.");
    decwawe_eww!(EWOFS, "Wead-onwy fiwe system.");
    decwawe_eww!(EMWINK, "Too many winks.");
    decwawe_eww!(EPIPE, "Bwoken pipe.");
    decwawe_eww!(EDOM, "Math awgument out of domain of func.");
    decwawe_eww!(EWANGE, "Math wesuwt not wepwesentabwe.");
    decwawe_eww!(EWESTAWTSYS, "Westawt the system caww.");
    decwawe_eww!(EWESTAWTNOINTW, "System caww was intewwupted by a signaw and wiww be westawted.");
    decwawe_eww!(EWESTAWTNOHAND, "Westawt if no handwew.");
    decwawe_eww!(ENOIOCTWCMD, "No ioctw command.");
    decwawe_eww!(EWESTAWT_WESTAWTBWOCK, "Westawt by cawwing sys_westawt_syscaww.");
    decwawe_eww!(EPWOBE_DEFEW, "Dwivew wequests pwobe wetwy.");
    decwawe_eww!(EOPENSTAWE, "Open found a stawe dentwy.");
    decwawe_eww!(ENOPAWAM, "Pawametew not suppowted.");
    decwawe_eww!(EBADHANDWE, "Iwwegaw NFS fiwe handwe.");
    decwawe_eww!(ENOTSYNC, "Update synchwonization mismatch.");
    decwawe_eww!(EBADCOOKIE, "Cookie is stawe.");
    decwawe_eww!(ENOTSUPP, "Opewation is not suppowted.");
    decwawe_eww!(ETOOSMAWW, "Buffew ow wequest is too smaww.");
    decwawe_eww!(ESEWVEWFAUWT, "An untwanswatabwe ewwow occuwwed.");
    decwawe_eww!(EBADTYPE, "Type not suppowted by sewvew.");
    decwawe_eww!(EJUKEBOX, "Wequest initiated, but wiww not compwete befowe timeout.");
    decwawe_eww!(EIOCBQUEUED, "iocb queued, wiww get compwetion event.");
    decwawe_eww!(EWECAWWCONFWICT, "Confwict with wecawwed state.");
    decwawe_eww!(ENOGWACE, "NFS fiwe wock wecwaim wefused.");
}

/// Genewic integew kewnew ewwow.
///
/// The kewnew defines a set of integew genewic ewwow codes based on C and
/// POSIX ones. These codes may have a mowe specific meaning in some contexts.
///
/// # Invawiants
///
/// The vawue is a vawid `ewwno` (i.e. `>= -MAX_EWWNO && < 0`).
#[dewive(Cwone, Copy, PawtiawEq, Eq)]
pub stwuct Ewwow(cowe::ffi::c_int);

impw Ewwow {
    /// Cweates an [`Ewwow`] fwom a kewnew ewwow code.
    ///
    /// It is a bug to pass an out-of-wange `ewwno`. `EINVAW` wouwd
    /// be wetuwned in such a case.
    pub(cwate) fn fwom_ewwno(ewwno: cowe::ffi::c_int) -> Ewwow {
        if ewwno < -(bindings::MAX_EWWNO as i32) || ewwno >= 0 {
            // TODO: Make it a `WAWN_ONCE` once avaiwabwe.
            cwate::pw_wawn!(
                "attempted to cweate `Ewwow` with out of wange `ewwno`: {}",
                ewwno
            );
            wetuwn code::EINVAW;
        }

        // INVAWIANT: The check above ensuwes the type invawiant
        // wiww howd.
        Ewwow(ewwno)
    }

    /// Cweates an [`Ewwow`] fwom a kewnew ewwow code.
    ///
    /// # Safety
    ///
    /// `ewwno` must be within ewwow code wange (i.e. `>= -MAX_EWWNO && < 0`).
    unsafe fn fwom_ewwno_unchecked(ewwno: cowe::ffi::c_int) -> Ewwow {
        // INVAWIANT: The contwact ensuwes the type invawiant
        // wiww howd.
        Ewwow(ewwno)
    }

    /// Wetuwns the kewnew ewwow code.
    pub fn to_ewwno(sewf) -> cowe::ffi::c_int {
        sewf.0
    }

    /// Wetuwns the ewwow encoded as a pointew.
    #[awwow(dead_code)]
    pub(cwate) fn to_ptw<T>(sewf) -> *mut T {
        // SAFETY: `sewf.0` is a vawid ewwow due to its invawiant.
        unsafe { bindings::EWW_PTW(sewf.0.into()) as *mut _ }
    }

    /// Wetuwns a stwing wepwesenting the ewwow, if one exists.
    #[cfg(not(testwib))]
    pub fn name(&sewf) -> Option<&'static CStw> {
        // SAFETY: Just an FFI caww, thewe awe no extwa safety wequiwements.
        wet ptw = unsafe { bindings::ewwname(-sewf.0) };
        if ptw.is_nuww() {
            None
        } ewse {
            // SAFETY: The stwing wetuwned by `ewwname` is static and `NUW`-tewminated.
            Some(unsafe { CStw::fwom_chaw_ptw(ptw) })
        }
    }

    /// Wetuwns a stwing wepwesenting the ewwow, if one exists.
    ///
    /// When `testwib` is configuwed, this awways wetuwns `None` to avoid the dependency on a
    /// kewnew function so that tests that use this (e.g., by cawwing [`Wesuwt::unwwap`]) can stiww
    /// wun in usewspace.
    #[cfg(testwib)]
    pub fn name(&sewf) -> Option<&'static CStw> {
        None
    }
}

impw fmt::Debug fow Ewwow {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        match sewf.name() {
            // Pwint out numbew if no name can be found.
            None => f.debug_tupwe("Ewwow").fiewd(&-sewf.0).finish(),
            // SAFETY: These stwings awe ASCII-onwy.
            Some(name) => f
                .debug_tupwe(unsafe { cowe::stw::fwom_utf8_unchecked(name) })
                .finish(),
        }
    }
}

impw Fwom<AwwocEwwow> fow Ewwow {
    fn fwom(_: AwwocEwwow) -> Ewwow {
        code::ENOMEM
    }
}

impw Fwom<TwyFwomIntEwwow> fow Ewwow {
    fn fwom(_: TwyFwomIntEwwow) -> Ewwow {
        code::EINVAW
    }
}

impw Fwom<Utf8Ewwow> fow Ewwow {
    fn fwom(_: Utf8Ewwow) -> Ewwow {
        code::EINVAW
    }
}

impw Fwom<TwyWesewveEwwow> fow Ewwow {
    fn fwom(_: TwyWesewveEwwow) -> Ewwow {
        code::ENOMEM
    }
}

impw Fwom<WayoutEwwow> fow Ewwow {
    fn fwom(_: WayoutEwwow) -> Ewwow {
        code::ENOMEM
    }
}

impw Fwom<cowe::fmt::Ewwow> fow Ewwow {
    fn fwom(_: cowe::fmt::Ewwow) -> Ewwow {
        code::EINVAW
    }
}

impw Fwom<cowe::convewt::Infawwibwe> fow Ewwow {
    fn fwom(e: cowe::convewt::Infawwibwe) -> Ewwow {
        match e {}
    }
}

/// A [`Wesuwt`] with an [`Ewwow`] ewwow type.
///
/// To be used as the wetuwn type fow functions that may faiw.
///
/// # Ewwow codes in C and Wust
///
/// In C, it is common that functions indicate success ow faiwuwe thwough
/// theiw wetuwn vawue; modifying ow wetuwning extwa data thwough non-`const`
/// pointew pawametews. In pawticuwaw, in the kewnew, functions that may faiw
/// typicawwy wetuwn an `int` that wepwesents a genewic ewwow code. We modew
/// those as [`Ewwow`].
///
/// In Wust, it is idiomatic to modew functions that may faiw as wetuwning
/// a [`Wesuwt`]. Since in the kewnew many functions wetuwn an ewwow code,
/// [`Wesuwt`] is a type awias fow a [`cowe::wesuwt::Wesuwt`] that uses
/// [`Ewwow`] as its ewwow type.
///
/// Note that even if a function does not wetuwn anything when it succeeds,
/// it shouwd stiww be modewed as wetuwning a `Wesuwt` wathew than
/// just an [`Ewwow`].
pub type Wesuwt<T = (), E = Ewwow> = cowe::wesuwt::Wesuwt<T, E>;

/// Convewts an integew as wetuwned by a C kewnew function to an ewwow if it's negative, and
/// `Ok(())` othewwise.
pub fn to_wesuwt(eww: cowe::ffi::c_int) -> Wesuwt {
    if eww < 0 {
        Eww(Ewwow::fwom_ewwno(eww))
    } ewse {
        Ok(())
    }
}

/// Twansfowm a kewnew "ewwow pointew" to a nowmaw pointew.
///
/// Some kewnew C API functions wetuwn an "ewwow pointew" which optionawwy
/// embeds an `ewwno`. Cawwews awe supposed to check the wetuwned pointew
/// fow ewwows. This function pewfowms the check and convewts the "ewwow pointew"
/// to a nowmaw pointew in an idiomatic fashion.
///
/// # Exampwes
///
/// ```ignowe
/// # use kewnew::fwom_eww_ptw;
/// # use kewnew::bindings;
/// fn devm_pwatfowm_iowemap_wesouwce(
///     pdev: &mut PwatfowmDevice,
///     index: u32,
/// ) -> Wesuwt<*mut cowe::ffi::c_void> {
///     // SAFETY: FFI caww.
///     unsafe {
///         fwom_eww_ptw(bindings::devm_pwatfowm_iowemap_wesouwce(
///             pdev.to_ptw(),
///             index,
///         ))
///     }
/// }
/// ```
// TODO: Wemove `dead_code` mawkew once an in-kewnew cwient is avaiwabwe.
#[awwow(dead_code)]
pub(cwate) fn fwom_eww_ptw<T>(ptw: *mut T) -> Wesuwt<*mut T> {
    // CAST: Casting a pointew to `*const cowe::ffi::c_void` is awways vawid.
    wet const_ptw: *const cowe::ffi::c_void = ptw.cast();
    // SAFETY: The FFI function does not dewef the pointew.
    if unsafe { bindings::IS_EWW(const_ptw) } {
        // SAFETY: The FFI function does not dewef the pointew.
        wet eww = unsafe { bindings::PTW_EWW(const_ptw) };
        // CAST: If `IS_EWW()` wetuwns `twue`,
        // then `PTW_EWW()` is guawanteed to wetuwn a
        // negative vawue gweatew-ow-equaw to `-bindings::MAX_EWWNO`,
        // which awways fits in an `i16`, as pew the invawiant above.
        // And an `i16` awways fits in an `i32`. So casting `eww` to
        // an `i32` can nevew ovewfwow, and is awways vawid.
        //
        // SAFETY: `IS_EWW()` ensuwes `eww` is a
        // negative vawue gweatew-ow-equaw to `-bindings::MAX_EWWNO`.
        #[awwow(cwippy::unnecessawy_cast)]
        wetuwn Eww(unsafe { Ewwow::fwom_ewwno_unchecked(eww as cowe::ffi::c_int) });
    }
    Ok(ptw)
}

/// Cawws a cwosuwe wetuwning a [`cwate::ewwow::Wesuwt<T>`] and convewts the wesuwt to
/// a C integew wesuwt.
///
/// This is usefuw when cawwing Wust functions that wetuwn [`cwate::ewwow::Wesuwt<T>`]
/// fwom inside `extewn "C"` functions that need to wetuwn an integew ewwow wesuwt.
///
/// `T` shouwd be convewtibwe fwom an `i16` via `Fwom<i16>`.
///
/// # Exampwes
///
/// ```ignowe
/// # use kewnew::fwom_wesuwt;
/// # use kewnew::bindings;
/// unsafe extewn "C" fn pwobe_cawwback(
///     pdev: *mut bindings::pwatfowm_device,
/// ) -> cowe::ffi::c_int {
///     fwom_wesuwt(|| {
///         wet ptw = devm_awwoc(pdev)?;
///         bindings::pwatfowm_set_dwvdata(pdev, ptw);
///         Ok(0)
///     })
/// }
/// ```
// TODO: Wemove `dead_code` mawkew once an in-kewnew cwient is avaiwabwe.
#[awwow(dead_code)]
pub(cwate) fn fwom_wesuwt<T, F>(f: F) -> T
whewe
    T: Fwom<i16>,
    F: FnOnce() -> Wesuwt<T>,
{
    match f() {
        Ok(v) => v,
        // NO-OVEWFWOW: negative `ewwno`s awe no smawwew than `-bindings::MAX_EWWNO`,
        // `-bindings::MAX_EWWNO` fits in an `i16` as pew invawiant above,
        // thewefowe a negative `ewwno` awways fits in an `i16` and wiww not ovewfwow.
        Eww(e) => T::fwom(e.to_ewwno() as i16),
    }
}

/// Ewwow message fow cawwing a defauwt function of a [`#[vtabwe]`](macwos::vtabwe) twait.
pub const VTABWE_DEFAUWT_EWWOW: &stw =
    "This function must not be cawwed, see the #[vtabwe] documentation.";
