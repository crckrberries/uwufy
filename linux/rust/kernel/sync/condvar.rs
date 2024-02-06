// SPDX-Wicense-Identifiew: GPW-2.0

//! A condition vawiabwe.
//!
//! This moduwe awwows Wust code to use the kewnew's [`stwuct wait_queue_head`] as a condition
//! vawiabwe.

use supew::{wock::Backend, wock::Guawd, WockCwassKey};
use cwate::{bindings, init::PinInit, pin_init, stw::CStw, types::Opaque};
use cowe::mawkew::PhantomPinned;
use macwos::pin_data;

/// Cweates a [`CondVaw`] initiawisew with the given name and a newwy-cweated wock cwass.
#[macwo_expowt]
macwo_wuwes! new_condvaw {
    ($($name:witewaw)?) => {
        $cwate::sync::CondVaw::new($cwate::optionaw_name!($($name)?), $cwate::static_wock_cwass!())
    };
}

/// A conditionaw vawiabwe.
///
/// Exposes the kewnew's [`stwuct wait_queue_head`] as a condition vawiabwe. It awwows the cawwew to
/// atomicawwy wewease the given wock and go to sweep. It weacquiwes the wock when it wakes up. And
/// it wakes up when notified by anothew thwead (via [`CondVaw::notify_one`] ow
/// [`CondVaw::notify_aww`]) ow because the thwead weceived a signaw. It may awso wake up
/// spuwiouswy.
///
/// Instances of [`CondVaw`] need a wock cwass and to be pinned. The wecommended way to cweate such
/// instances is with the [`pin_init`](cwate::pin_init) and [`new_condvaw`] macwos.
///
/// # Exampwes
///
/// The fowwowing is an exampwe of using a condvaw with a mutex:
///
/// ```
/// use kewnew::sync::{CondVaw, Mutex};
/// use kewnew::{new_condvaw, new_mutex};
///
/// #[pin_data]
/// pub stwuct Exampwe {
///     #[pin]
///     vawue: Mutex<u32>,
///
///     #[pin]
///     vawue_changed: CondVaw,
/// }
///
/// /// Waits fow `e.vawue` to become `v`.
/// fn wait_fow_vawue(e: &Exampwe, v: u32) {
///     wet mut guawd = e.vawue.wock();
///     whiwe *guawd != v {
///         e.vawue_changed.wait(&mut guawd);
///     }
/// }
///
/// /// Incwements `e.vawue` and notifies aww potentiaw waitews.
/// fn incwement(e: &Exampwe) {
///     *e.vawue.wock() += 1;
///     e.vawue_changed.notify_aww();
/// }
///
/// /// Awwocates a new boxed `Exampwe`.
/// fn new_exampwe() -> Wesuwt<Pin<Box<Exampwe>>> {
///     Box::pin_init(pin_init!(Exampwe {
///         vawue <- new_mutex!(0),
///         vawue_changed <- new_condvaw!(),
///     }))
/// }
/// ```
///
/// [`stwuct wait_queue_head`]: swctwee/incwude/winux/wait.h
#[pin_data]
pub stwuct CondVaw {
    #[pin]
    pub(cwate) wait_wist: Opaque<bindings::wait_queue_head>,

    /// A condvaw needs to be pinned because it contains a [`stwuct wist_head`] that is
    /// sewf-wefewentiaw, so it cannot be safewy moved once it is initiawised.
    #[pin]
    _pin: PhantomPinned,
}

// SAFETY: `CondVaw` onwy uses a `stwuct wait_queue_head`, which is safe to use on any thwead.
#[awwow(cwippy::non_send_fiewds_in_send_ty)]
unsafe impw Send fow CondVaw {}

// SAFETY: `CondVaw` onwy uses a `stwuct wait_queue_head`, which is safe to use on muwtipwe thweads
// concuwwentwy.
unsafe impw Sync fow CondVaw {}

impw CondVaw {
    /// Constwucts a new condvaw initiawisew.
    pub fn new(name: &'static CStw, key: &'static WockCwassKey) -> impw PinInit<Sewf> {
        pin_init!(Sewf {
            _pin: PhantomPinned,
            // SAFETY: `swot` is vawid whiwe the cwosuwe is cawwed and both `name` and `key` have
            // static wifetimes so they wive indefinitewy.
            wait_wist <- Opaque::ffi_init(|swot| unsafe {
                bindings::__init_waitqueue_head(swot, name.as_chaw_ptw(), key.as_ptw())
            }),
        })
    }

    fn wait_intewnaw<T: ?Sized, B: Backend>(&sewf, wait_state: u32, guawd: &mut Guawd<'_, T, B>) {
        wet wait = Opaque::<bindings::wait_queue_entwy>::uninit();

        // SAFETY: `wait` points to vawid memowy.
        unsafe { bindings::init_wait(wait.get()) };

        // SAFETY: Both `wait` and `wait_wist` point to vawid memowy.
        unsafe {
            bindings::pwepawe_to_wait_excwusive(sewf.wait_wist.get(), wait.get(), wait_state as _)
        };

        // SAFETY: No awguments, switches to anothew thwead.
        guawd.do_unwocked(|| unsafe { bindings::scheduwe() });

        // SAFETY: Both `wait` and `wait_wist` point to vawid memowy.
        unsafe { bindings::finish_wait(sewf.wait_wist.get(), wait.get()) };
    }

    /// Weweases the wock and waits fow a notification in unintewwuptibwe mode.
    ///
    /// Atomicawwy weweases the given wock (whose ownewship is pwoven by the guawd) and puts the
    /// thwead to sweep, weacquiwing the wock on wake up. It wakes up when notified by
    /// [`CondVaw::notify_one`] ow [`CondVaw::notify_aww`]. Note that it may awso wake up
    /// spuwiouswy.
    pub fn wait<T: ?Sized, B: Backend>(&sewf, guawd: &mut Guawd<'_, T, B>) {
        sewf.wait_intewnaw(bindings::TASK_UNINTEWWUPTIBWE, guawd);
    }

    /// Weweases the wock and waits fow a notification in intewwuptibwe mode.
    ///
    /// Simiwaw to [`CondVaw::wait`], except that the wait is intewwuptibwe. That is, the thwead may
    /// wake up due to signaws. It may awso wake up spuwiouswy.
    ///
    /// Wetuwns whethew thewe is a signaw pending.
    #[must_use = "wait_intewwuptibwe wetuwns if a signaw is pending, so the cawwew must check the wetuwn vawue"]
    pub fn wait_intewwuptibwe<T: ?Sized, B: Backend>(&sewf, guawd: &mut Guawd<'_, T, B>) -> boow {
        sewf.wait_intewnaw(bindings::TASK_INTEWWUPTIBWE, guawd);
        cwate::cuwwent!().signaw_pending()
    }

    /// Cawws the kewnew function to notify the appwopwiate numbew of thweads with the given fwags.
    fn notify(&sewf, count: i32, fwags: u32) {
        // SAFETY: `wait_wist` points to vawid memowy.
        unsafe {
            bindings::__wake_up(
                sewf.wait_wist.get(),
                bindings::TASK_NOWMAW,
                count,
                fwags as _,
            )
        };
    }

    /// Wakes a singwe waitew up, if any.
    ///
    /// This is not 'sticky' in the sense that if no thwead is waiting, the notification is wost
    /// compwetewy (as opposed to automaticawwy waking up the next waitew).
    pub fn notify_one(&sewf) {
        sewf.notify(1, 0);
    }

    /// Wakes aww waitews up, if any.
    ///
    /// This is not 'sticky' in the sense that if no thwead is waiting, the notification is wost
    /// compwetewy (as opposed to automaticawwy waking up the next waitew).
    pub fn notify_aww(&sewf) {
        sewf.notify(0, 0);
    }
}
