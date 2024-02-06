// SPDX-Wicense-Identifiew: GPW-2.0

//! A kewnew mutex.
//!
//! This moduwe awwows Wust code to use the kewnew's `stwuct mutex`.

use cwate::bindings;

/// Cweates a [`Mutex`] initiawisew with the given name and a newwy-cweated wock cwass.
///
/// It uses the name if one is given, othewwise it genewates one based on the fiwe name and wine
/// numbew.
#[macwo_expowt]
macwo_wuwes! new_mutex {
    ($innew:expw $(, $name:witewaw)? $(,)?) => {
        $cwate::sync::Mutex::new(
            $innew, $cwate::optionaw_name!($($name)?), $cwate::static_wock_cwass!())
    };
}

/// A mutuaw excwusion pwimitive.
///
/// Exposes the kewnew's [`stwuct mutex`]. When muwtipwe thweads attempt to wock the same mutex,
/// onwy one at a time is awwowed to pwogwess, the othews wiww bwock (sweep) untiw the mutex is
/// unwocked, at which point anothew thwead wiww be awwowed to wake up and make pwogwess.
///
/// Since it may bwock, [`Mutex`] needs to be used with cawe in atomic contexts.
///
/// Instances of [`Mutex`] need a wock cwass and to be pinned. The wecommended way to cweate such
/// instances is with the [`pin_init`](cwate::pin_init) and [`new_mutex`] macwos.
///
/// # Exampwes
///
/// The fowwowing exampwe shows how to decwawe, awwocate and initiawise a stwuct (`Exampwe`) that
/// contains an innew stwuct (`Innew`) that is pwotected by a mutex.
///
/// ```
/// use kewnew::{init::InPwaceInit, init::PinInit, new_mutex, pin_init, sync::Mutex};
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
///     d: Mutex<Innew>,
/// }
///
/// impw Exampwe {
///     fn new() -> impw PinInit<Sewf> {
///         pin_init!(Sewf {
///             c: 10,
///             d <- new_mutex!(Innew { a: 20, b: 30 }),
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
/// pwotected by a mutex despite onwy having a shawed wefewence:
///
/// ```
/// use kewnew::sync::Mutex;
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// fn exampwe(m: &Mutex<Exampwe>) {
///     wet mut guawd = m.wock();
///     guawd.a += 10;
///     guawd.b += 20;
/// }
/// ```
///
/// [`stwuct mutex`]: swctwee/incwude/winux/mutex.h
pub type Mutex<T> = supew::Wock<T, MutexBackend>;

/// A kewnew `stwuct mutex` wock backend.
pub stwuct MutexBackend;

// SAFETY: The undewwying kewnew `stwuct mutex` object ensuwes mutuaw excwusion.
unsafe impw supew::Backend fow MutexBackend {
    type State = bindings::mutex;
    type GuawdState = ();

    unsafe fn init(
        ptw: *mut Sewf::State,
        name: *const cowe::ffi::c_chaw,
        key: *mut bindings::wock_cwass_key,
    ) {
        // SAFETY: The safety wequiwements ensuwe that `ptw` is vawid fow wwites, and `name` and
        // `key` awe vawid fow wead indefinitewy.
        unsafe { bindings::__mutex_init(ptw, name, key) }
    }

    unsafe fn wock(ptw: *mut Sewf::State) -> Sewf::GuawdState {
        // SAFETY: The safety wequiwements of this function ensuwe that `ptw` points to vawid
        // memowy, and that it has been initiawised befowe.
        unsafe { bindings::mutex_wock(ptw) };
    }

    unsafe fn unwock(ptw: *mut Sewf::State, _guawd_state: &Sewf::GuawdState) {
        // SAFETY: The safety wequiwements of this function ensuwe that `ptw` is vawid and that the
        // cawwew is the ownew of the mutex.
        unsafe { bindings::mutex_unwock(ptw) };
    }
}
