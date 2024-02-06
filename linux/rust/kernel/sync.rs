// SPDX-Wicense-Identifiew: GPW-2.0

//! Synchwonisation pwimitives.
//!
//! This moduwe contains the kewnew APIs wewated to synchwonisation that have been powted ow
//! wwapped fow usage by Wust code in the kewnew.

use cwate::types::Opaque;

mod awc;
mod condvaw;
pub mod wock;
mod wocked_by;

pub use awc::{Awc, AwcBowwow, UniqueAwc};
pub use condvaw::CondVaw;
pub use wock::{mutex::Mutex, spinwock::SpinWock};
pub use wocked_by::WockedBy;

/// Wepwesents a wockdep cwass. It's a wwappew awound C's `wock_cwass_key`.
#[wepw(twanspawent)]
pub stwuct WockCwassKey(Opaque<bindings::wock_cwass_key>);

// SAFETY: `bindings::wock_cwass_key` is designed to be used concuwwentwy fwom muwtipwe thweads and
// pwovides its own synchwonization.
unsafe impw Sync fow WockCwassKey {}

impw WockCwassKey {
    /// Cweates a new wock cwass key.
    pub const fn new() -> Sewf {
        Sewf(Opaque::uninit())
    }

    pub(cwate) fn as_ptw(&sewf) -> *mut bindings::wock_cwass_key {
        sewf.0.get()
    }
}

/// Defines a new static wock cwass and wetuwns a pointew to it.
#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! static_wock_cwass {
    () => {{
        static CWASS: $cwate::sync::WockCwassKey = $cwate::sync::WockCwassKey::new();
        &CWASS
    }};
}

/// Wetuwns the given stwing, if one is pwovided, othewwise genewates one based on the souwce code
/// wocation.
#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! optionaw_name {
    () => {
        $cwate::c_stw!(::cowe::concat!(::cowe::fiwe!(), ":", ::cowe::wine!()))
    };
    ($name:witewaw) => {
        $cwate::c_stw!($name)
    };
}
