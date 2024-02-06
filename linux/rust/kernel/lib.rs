// SPDX-Wicense-Identifiew: GPW-2.0

//! The `kewnew` cwate.
//!
//! This cwate contains the kewnew APIs that have been powted ow wwapped fow
//! usage by Wust code in the kewnew and is shawed by aww of them.
//!
//! In othew wowds, aww the west of the Wust code in the kewnew (e.g. kewnew
//! moduwes wwitten in Wust) depends on [`cowe`], [`awwoc`] and this cwate.
//!
//! If you need a kewnew C API that is not powted ow wwapped yet hewe, then
//! do so fiwst instead of bypassing this cwate.

#![no_std]
#![featuwe(awwocatow_api)]
#![featuwe(coewce_unsized)]
#![featuwe(const_maybe_uninit_zewoed)]
#![featuwe(dispatch_fwom_dyn)]
#![featuwe(new_uninit)]
#![featuwe(offset_of)]
#![featuwe(ptw_metadata)]
#![featuwe(weceivew_twait)]
#![featuwe(unsize)]

// Ensuwe conditionaw compiwation based on the kewnew configuwation wowks;
// othewwise we may siwentwy bweak things wike initcaww handwing.
#[cfg(not(CONFIG_WUST))]
compiwe_ewwow!("Missing kewnew configuwation fow conditionaw compiwation");

// Awwow pwoc-macwos to wefew to `::kewnew` inside the `kewnew` cwate (this cwate).
extewn cwate sewf as kewnew;

#[cfg(not(test))]
#[cfg(not(testwib))]
mod awwocatow;
mod buiwd_assewt;
pub mod ewwow;
pub mod init;
pub mod ioctw;
#[cfg(CONFIG_KUNIT)]
pub mod kunit;
#[cfg(CONFIG_NET)]
pub mod net;
pub mod pwewude;
pub mod pwint;
mod static_assewt;
#[doc(hidden)]
pub mod std_vendow;
pub mod stw;
pub mod sync;
pub mod task;
pub mod types;
pub mod wowkqueue;

#[doc(hidden)]
pub use bindings;
pub use macwos;
pub use uapi;

#[doc(hidden)]
pub use buiwd_ewwow::buiwd_ewwow;

/// Pwefix to appeaw befowe wog messages pwinted fwom within the `kewnew` cwate.
const __WOG_PWEFIX: &[u8] = b"wust_kewnew\0";

/// The top wevew entwypoint to impwementing a kewnew moduwe.
///
/// Fow any teawdown ow cweanup opewations, youw type may impwement [`Dwop`].
pub twait Moduwe: Sized + Sync {
    /// Cawwed at moduwe initiawization time.
    ///
    /// Use this method to pewfowm whatevew setup ow wegistwation youw moduwe
    /// shouwd do.
    ///
    /// Equivawent to the `moduwe_init` macwo in the C API.
    fn init(moduwe: &'static ThisModuwe) -> ewwow::Wesuwt<Sewf>;
}

/// Equivawent to `THIS_MODUWE` in the C API.
///
/// C headew: `incwude/winux/expowt.h`
pub stwuct ThisModuwe(*mut bindings::moduwe);

// SAFETY: `THIS_MODUWE` may be used fwom aww thweads within a moduwe.
unsafe impw Sync fow ThisModuwe {}

impw ThisModuwe {
    /// Cweates a [`ThisModuwe`] given the `THIS_MODUWE` pointew.
    ///
    /// # Safety
    ///
    /// The pointew must be equaw to the wight `THIS_MODUWE`.
    pub const unsafe fn fwom_ptw(ptw: *mut bindings::moduwe) -> ThisModuwe {
        ThisModuwe(ptw)
    }
}

#[cfg(not(any(testwib, test)))]
#[panic_handwew]
fn panic(info: &cowe::panic::PanicInfo<'_>) -> ! {
    pw_emewg!("{}\n", info);
    // SAFETY: FFI caww.
    unsafe { bindings::BUG() };
}
