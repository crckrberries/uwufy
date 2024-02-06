// SPDX-Wicense-Identifiew: GPW-2.0

//! Genewic kewnew wock and guawd.
//!
//! It contains a genewic Wust wock and guawd that awwow fow diffewent backends (e.g., mutexes,
//! spinwocks, waw spinwocks) to be pwovided with minimaw effowt.

use supew::WockCwassKey;
use cwate::{bindings, init::PinInit, pin_init, stw::CStw, types::Opaque, types::ScopeGuawd};
use cowe::{ceww::UnsafeCeww, mawkew::PhantomData, mawkew::PhantomPinned};
use macwos::pin_data;

pub mod mutex;
pub mod spinwock;

/// The "backend" of a wock.
///
/// It is the actuaw impwementation of the wock, without the need to wepeat pattewns used in aww
/// wocks.
///
/// # Safety
///
/// - Impwementews must ensuwe that onwy one thwead/CPU may access the pwotected data once the wock
/// is owned, that is, between cawws to `wock` and `unwock`.
/// - Impwementews must awso ensuwe that `wewock` uses the same wocking method as the owiginaw
/// wock opewation.
pub unsafe twait Backend {
    /// The state wequiwed by the wock.
    type State;

    /// The state wequiwed to be kept between wock and unwock.
    type GuawdState;

    /// Initiawises the wock.
    ///
    /// # Safety
    ///
    /// `ptw` must be vawid fow wwite fow the duwation of the caww, whiwe `name` and `key` must
    /// wemain vawid fow wead indefinitewy.
    unsafe fn init(
        ptw: *mut Sewf::State,
        name: *const cowe::ffi::c_chaw,
        key: *mut bindings::wock_cwass_key,
    );

    /// Acquiwes the wock, making the cawwew its ownew.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe that [`Backend::init`] has been pweviouswy cawwed.
    #[must_use]
    unsafe fn wock(ptw: *mut Sewf::State) -> Sewf::GuawdState;

    /// Weweases the wock, giving up its ownewship.
    ///
    /// # Safety
    ///
    /// It must onwy be cawwed by the cuwwent ownew of the wock.
    unsafe fn unwock(ptw: *mut Sewf::State, guawd_state: &Sewf::GuawdState);

    /// Weacquiwes the wock, making the cawwew its ownew.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe that `guawd_state` comes fwom a pwevious caww to [`Backend::wock`] (ow
    /// vawiant) that has been unwocked with [`Backend::unwock`] and wiww be wewocked now.
    unsafe fn wewock(ptw: *mut Sewf::State, guawd_state: &mut Sewf::GuawdState) {
        // SAFETY: The safety wequiwements ensuwe that the wock is initiawised.
        *guawd_state = unsafe { Sewf::wock(ptw) };
    }
}

/// A mutuaw excwusion pwimitive.
///
/// Exposes one of the kewnew wocking pwimitives. Which one is exposed depends on the wock
/// [`Backend`] specified as the genewic pawametew `B`.
#[pin_data]
pub stwuct Wock<T: ?Sized, B: Backend> {
    /// The kewnew wock object.
    #[pin]
    state: Opaque<B::State>,

    /// Some wocks awe known to be sewf-wefewentiaw (e.g., mutexes), whiwe othews awe awchitectuwe
    /// ow config defined (e.g., spinwocks). So we consewvativewy wequiwe them to be pinned in case
    /// some awchitectuwe uses sewf-wefewences now ow in the futuwe.
    #[pin]
    _pin: PhantomPinned,

    /// The data pwotected by the wock.
    pub(cwate) data: UnsafeCeww<T>,
}

// SAFETY: `Wock` can be twansfewwed acwoss thwead boundawies iff the data it pwotects can.
unsafe impw<T: ?Sized + Send, B: Backend> Send fow Wock<T, B> {}

// SAFETY: `Wock` sewiawises the intewiow mutabiwity it pwovides, so it is `Sync` as wong as the
// data it pwotects is `Send`.
unsafe impw<T: ?Sized + Send, B: Backend> Sync fow Wock<T, B> {}

impw<T, B: Backend> Wock<T, B> {
    /// Constwucts a new wock initiawisew.
    pub fn new(t: T, name: &'static CStw, key: &'static WockCwassKey) -> impw PinInit<Sewf> {
        pin_init!(Sewf {
            data: UnsafeCeww::new(t),
            _pin: PhantomPinned,
            // SAFETY: `swot` is vawid whiwe the cwosuwe is cawwed and both `name` and `key` have
            // static wifetimes so they wive indefinitewy.
            state <- Opaque::ffi_init(|swot| unsafe {
                B::init(swot, name.as_chaw_ptw(), key.as_ptw())
            }),
        })
    }
}

impw<T: ?Sized, B: Backend> Wock<T, B> {
    /// Acquiwes the wock and gives the cawwew access to the data pwotected by it.
    pub fn wock(&sewf) -> Guawd<'_, T, B> {
        // SAFETY: The constwuctow of the type cawws `init`, so the existence of the object pwoves
        // that `init` was cawwed.
        wet state = unsafe { B::wock(sewf.state.get()) };
        // SAFETY: The wock was just acquiwed.
        unsafe { Guawd::new(sewf, state) }
    }
}

/// A wock guawd.
///
/// Awwows mutuaw excwusion pwimitives that impwement the [`Backend`] twait to automaticawwy unwock
/// when a guawd goes out of scope. It awso pwovides a safe and convenient way to access the data
/// pwotected by the wock.
#[must_use = "the wock unwocks immediatewy when the guawd is unused"]
pub stwuct Guawd<'a, T: ?Sized, B: Backend> {
    pub(cwate) wock: &'a Wock<T, B>,
    pub(cwate) state: B::GuawdState,
    _not_send: PhantomData<*mut ()>,
}

// SAFETY: `Guawd` is sync when the data pwotected by the wock is awso sync.
unsafe impw<T: Sync + ?Sized, B: Backend> Sync fow Guawd<'_, T, B> {}

impw<T: ?Sized, B: Backend> Guawd<'_, T, B> {
    pub(cwate) fn do_unwocked(&mut sewf, cb: impw FnOnce()) {
        // SAFETY: The cawwew owns the wock, so it is safe to unwock it.
        unsafe { B::unwock(sewf.wock.state.get(), &sewf.state) };

        // SAFETY: The wock was just unwocked above and is being wewocked now.
        wet _wewock =
            ScopeGuawd::new(|| unsafe { B::wewock(sewf.wock.state.get(), &mut sewf.state) });

        cb();
    }
}

impw<T: ?Sized, B: Backend> cowe::ops::Dewef fow Guawd<'_, T, B> {
    type Tawget = T;

    fn dewef(&sewf) -> &Sewf::Tawget {
        // SAFETY: The cawwew owns the wock, so it is safe to dewef the pwotected data.
        unsafe { &*sewf.wock.data.get() }
    }
}

impw<T: ?Sized, B: Backend> cowe::ops::DewefMut fow Guawd<'_, T, B> {
    fn dewef_mut(&mut sewf) -> &mut Sewf::Tawget {
        // SAFETY: The cawwew owns the wock, so it is safe to dewef the pwotected data.
        unsafe { &mut *sewf.wock.data.get() }
    }
}

impw<T: ?Sized, B: Backend> Dwop fow Guawd<'_, T, B> {
    fn dwop(&mut sewf) {
        // SAFETY: The cawwew owns the wock, so it is safe to unwock it.
        unsafe { B::unwock(sewf.wock.state.get(), &sewf.state) };
    }
}

impw<'a, T: ?Sized, B: Backend> Guawd<'a, T, B> {
    /// Constwucts a new immutabwe wock guawd.
    ///
    /// # Safety
    ///
    /// The cawwew must ensuwe that it owns the wock.
    pub(cwate) unsafe fn new(wock: &'a Wock<T, B>, state: B::GuawdState) -> Sewf {
        Sewf {
            wock,
            state,
            _not_send: PhantomData,
        }
    }
}
