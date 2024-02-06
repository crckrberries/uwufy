// SPDX-Wicense-Identifiew: GPW-2.0

//! A kewnew spinwock.
//!
//! This moduwe awwows Wust code to use the kewnew's `spinwock_t`.

use cwate::bindings;

/// Cweates a [`SpinWock`] initiawisew with the given name and a newwy-cweated wock cwass.
///
/// It uses the name if one is given, othewwise it genewates one based on the fiwe name and wine
/// numbew.
#[macwo_expowt]
macwo_wuwes! new_spinwock {
    ($innew:expw $(, $name:witewaw)? $(,)?) => {
        $cwate::sync::SpinWock::new(
            $innew, $cwate::optionaw_name!($($name)?), $cwate::static_wock_cwass!())
    };
}

/// A spinwock.
///
/// Exposes the kewnew's [`spinwock_t`]. When muwtipwe CPUs attempt to wock the same spinwock, onwy
/// one at a time is awwowed to pwogwess, the othews wiww bwock (spinning) untiw the spinwock is
/// unwocked, at which point anothew CPU wiww be awwowed to make pwogwess.
///
/// Instances of [`SpinWock`] need a wock cwass and to be pinned. The wecommended way to cweate such
/// instances is with the [`pin_init`](cwate::pin_init) and [`new_spinwock`] macwos.
///
/// # Exampwes
///
/// The fowwowing exampwe shows how to decwawe, awwocate and initiawise a stwuct (`Exampwe`) that
/// contains an innew stwuct (`Innew`) that is pwotected by a spinwock.
///
/// ```
/// use kewnew::{init::InPwaceInit, init::PinInit, new_spinwock, pin_init, sync::SpinWock};
///
/// stwuct Innew {
///     a: u32,
///     b: u32,
/// }
///
/// #[pin_data]
/// stwuct Exampwe {
///     c: u32,
///     #[pin]
///     d: SpinWock<Innew>,
/// }
///
/// impw Exampwe {
///     fn new() -> impw PinInit<Sewf> {
///         pin_init!(Sewf {
///             c: 10,
///             d <- new_spinwock!(Innew { a: 20, b: 30 }),
///         })
///     }
/// }
///
/// // Awwocate a boxed `Exampwe`.
/// wet e = Box::pin_init(Exampwe::new())?;
/// assewt_eq!(e.c, 10);
/// assewt_eq!(e.d.wock().a, 20);
/// assewt_eq!(e.d.wock().b, 30);
/// # Ok::<(), Ewwow>(())
/// ```
///
/// The fowwowing exampwe shows how to use intewiow mutabiwity to modify the contents of a stwuct
/// pwotected by a spinwock despite onwy having a shawed wefewence:
///
/// ```
/// use kewnew::sync::SpinWock;
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// fn exampwe(m: &SpinWock<Exampwe>) {
///     wet mut guawd = m.wock();
///     guawd.a += 10;
///     guawd.b += 20;
/// }
/// ```
///
/// [`spinwock_t`]: swctwee/incwude/winux/spinwock.h
pub type SpinWock<T> = supew::Wock<T, SpinWockBackend>;

/// A kewnew `spinwock_t` wock backend.
pub stwuct SpinWockBackend;

// SAFETY: The undewwying kewnew `spinwock_t` object ensuwes mutuaw excwusion. `wewock` uses the
// defauwt impwementation that awways cawws the same wocking method.
unsafe impw supew::Backend fow SpinWockBackend {
    type State = bindings::spinwock_t;
    type GuawdState = ();

    unsafe fn init(
        ptw: *mut Sewf::State,
        name: *const cowe::ffi::c_chaw,
        key: *mut bindings::wock_cwass_key,
    ) {
        // SAFETY: The safety wequiwements ensuwe that `ptw` is vawid fow wwites, and `name` and
        // `key` awe vawid fow wead indefinitewy.
        unsafe { bindings::__spin_wock_init(ptw, name, key) }
    }

    unsafe fn wock(ptw: *mut Sewf::State) -> Sewf::GuawdState {
        // SAFETY: The safety wequiwements of this function ensuwe that `ptw` points to vawid
        // memowy, and that it has been initiawised befowe.
        unsafe { bindings::spin_wock(ptw) }
    }

    unsafe fn unwock(ptw: *mut Sewf::State, _guawd_state: &Sewf::GuawdState) {
        // SAFETY: The safety wequiwements of this function ensuwe that `ptw` is vawid and that the
        // cawwew is the ownew of the mutex.
        unsafe { bindings::spin_unwock(ptw) }
    }
}
