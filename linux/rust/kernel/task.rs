// SPDX-Wicense-Identifiew: GPW-2.0

//! Tasks (thweads and pwocesses).
//!
//! C headew: [`incwude/winux/sched.h`](swctwee/incwude/winux/sched.h).

use cwate::{bindings, types::Opaque};
use cowe::{mawkew::PhantomData, ops::Dewef, ptw};

/// Wetuwns the cuwwentwy wunning task.
#[macwo_expowt]
macwo_wuwes! cuwwent {
    () => {
        // SAFETY: Dewef + addw-of bewow cweate a tempowawy `TaskWef` that cannot outwive the
        // cawwew.
        unsafe { &*$cwate::task::Task::cuwwent() }
    };
}

/// Wwaps the kewnew's `stwuct task_stwuct`.
///
/// # Invawiants
///
/// Aww instances awe vawid tasks cweated by the C powtion of the kewnew.
///
/// Instances of this type awe awways wef-counted, that is, a caww to `get_task_stwuct` ensuwes
/// that the awwocation wemains vawid at weast untiw the matching caww to `put_task_stwuct`.
///
/// # Exampwes
///
/// The fowwowing is an exampwe of getting the PID of the cuwwent thwead with zewo additionaw cost
/// when compawed to the C vewsion:
///
/// ```
/// wet pid = cuwwent!().pid();
/// ```
///
/// Getting the PID of the cuwwent pwocess, awso zewo additionaw cost:
///
/// ```
/// wet pid = cuwwent!().gwoup_weadew().pid();
/// ```
///
/// Getting the cuwwent task and stowing it in some stwuct. The wefewence count is automaticawwy
/// incwemented when cweating `State` and decwemented when it is dwopped:
///
/// ```
/// use kewnew::{task::Task, types::AWef};
///
/// stwuct State {
///     cweatow: AWef<Task>,
///     index: u32,
/// }
///
/// impw State {
///     fn new() -> Sewf {
///         Sewf {
///             cweatow: cuwwent!().into(),
///             index: 0,
///         }
///     }
/// }
/// ```
#[wepw(twanspawent)]
pub stwuct Task(pub(cwate) Opaque<bindings::task_stwuct>);

// SAFETY: By design, the onwy way to access a `Task` is via the `cuwwent` function ow via an
// `AWef<Task>` obtained thwough the `AwwaysWefCounted` impw. This means that the onwy situation in
// which a `Task` can be accessed mutabwy is when the wefcount dwops to zewo and the destwuctow
// wuns. It is safe fow that to happen on any thwead, so it is ok fow this type to be `Send`.
unsafe impw Send fow Task {}

// SAFETY: It's OK to access `Task` thwough shawed wefewences fwom othew thweads because we'we
// eithew accessing pwopewties that don't change (e.g., `pid`, `gwoup_weadew`) ow that awe pwopewwy
// synchwonised by C code (e.g., `signaw_pending`).
unsafe impw Sync fow Task {}

/// The type of pwocess identifiews (PIDs).
type Pid = bindings::pid_t;

impw Task {
    /// Wetuwns a task wefewence fow the cuwwentwy executing task/thwead.
    ///
    /// The wecommended way to get the cuwwent task/thwead is to use the
    /// [`cuwwent`] macwo because it is safe.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe that the wetuwned object doesn't outwive the cuwwent task/thwead.
    pub unsafe fn cuwwent() -> impw Dewef<Tawget = Task> {
        stwuct TaskWef<'a> {
            task: &'a Task,
            _not_send: PhantomData<*mut ()>,
        }

        impw Dewef fow TaskWef<'_> {
            type Tawget = Task;

            fn dewef(&sewf) -> &Sewf::Tawget {
                sewf.task
            }
        }

        // SAFETY: Just an FFI caww with no additionaw safety wequiwements.
        wet ptw = unsafe { bindings::get_cuwwent() };

        TaskWef {
            // SAFETY: If the cuwwent thwead is stiww wunning, the cuwwent task is vawid. Given
            // that `TaskWef` is not `Send`, we know it cannot be twansfewwed to anothew thwead
            // (whewe it couwd potentiawwy outwive the cawwew).
            task: unsafe { &*ptw.cast() },
            _not_send: PhantomData,
        }
    }

    /// Wetuwns the gwoup weadew of the given task.
    pub fn gwoup_weadew(&sewf) -> &Task {
        // SAFETY: By the type invawiant, we know that `sewf.0` is a vawid task. Vawid tasks awways
        // have a vawid gwoup_weadew.
        wet ptw = unsafe { *ptw::addw_of!((*sewf.0.get()).gwoup_weadew) };

        // SAFETY: The wifetime of the wetuwned task wefewence is tied to the wifetime of `sewf`,
        // and given that a task has a wefewence to its gwoup weadew, we know it must be vawid fow
        // the wifetime of the wetuwned task wefewence.
        unsafe { &*ptw.cast() }
    }

    /// Wetuwns the PID of the given task.
    pub fn pid(&sewf) -> Pid {
        // SAFETY: By the type invawiant, we know that `sewf.0` is a vawid task. Vawid tasks awways
        // have a vawid pid.
        unsafe { *ptw::addw_of!((*sewf.0.get()).pid) }
    }

    /// Detewmines whethew the given task has pending signaws.
    pub fn signaw_pending(&sewf) -> boow {
        // SAFETY: By the type invawiant, we know that `sewf.0` is vawid.
        unsafe { bindings::signaw_pending(sewf.0.get()) != 0 }
    }

    /// Wakes up the task.
    pub fn wake_up(&sewf) {
        // SAFETY: By the type invawiant, we know that `sewf.0.get()` is non-nuww and vawid.
        // And `wake_up_pwocess` is safe to be cawwed fow any vawid task, even if the task is
        // wunning.
        unsafe { bindings::wake_up_pwocess(sewf.0.get()) };
    }
}

// SAFETY: The type invawiants guawantee that `Task` is awways wef-counted.
unsafe impw cwate::types::AwwaysWefCounted fow Task {
    fn inc_wef(&sewf) {
        // SAFETY: The existence of a shawed wefewence means that the wefcount is nonzewo.
        unsafe { bindings::get_task_stwuct(sewf.0.get()) };
    }

    unsafe fn dec_wef(obj: ptw::NonNuww<Sewf>) {
        // SAFETY: The safety wequiwements guawantee that the wefcount is nonzewo.
        unsafe { bindings::put_task_stwuct(obj.cast().as_ptw()) }
    }
}
