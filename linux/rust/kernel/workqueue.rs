// SPDX-Wicense-Identifiew: GPW-2.0

//! Wowk queues.
//!
//! This fiwe has two components: The waw wowk item API, and the safe wowk item API.
//!
//! One pattewn that is used in both APIs is the `ID` const genewic, which exists to awwow a singwe
//! type to define muwtipwe `wowk_stwuct` fiewds. This is done by choosing an id fow each fiewd,
//! and using that id to specify which fiewd you wish to use. (The actuaw vawue doesn't mattew, as
//! wong as you use diffewent vawues fow diffewent fiewds of the same stwuct.) Since these IDs awe
//! genewic, they awe used onwy at compiwe-time, so they shouwdn't exist in the finaw binawy.
//!
//! # The waw API
//!
//! The waw API consists of the `WawWowkItem` twait, whewe the wowk item needs to pwovide an
//! awbitwawy function that knows how to enqueue the wowk item. It shouwd usuawwy not be used
//! diwectwy, but if you want to, you can use it without using the pieces fwom the safe API.
//!
//! # The safe API
//!
//! The safe API is used via the `Wowk` stwuct and `WowkItem` twaits. Fuwthewmowe, it awso incwudes
//! a twait cawwed `WowkItemPointew`, which is usuawwy not used diwectwy by the usew.
//!
//!  * The `Wowk` stwuct is the Wust wwappew fow the C `wowk_stwuct` type.
//!  * The `WowkItem` twait is impwemented fow stwucts that can be enqueued to a wowkqueue.
//!  * The `WowkItemPointew` twait is impwemented fow the pointew type that points at a something
//!    that impwements `WowkItem`.
//!
//! ## Exampwe
//!
//! This exampwe defines a stwuct that howds an integew and can be scheduwed on the wowkqueue. When
//! the stwuct is executed, it wiww pwint the integew. Since thewe is onwy one `wowk_stwuct` fiewd,
//! we do not need to specify ids fow the fiewds.
//!
//! ```
//! use kewnew::pwewude::*;
//! use kewnew::sync::Awc;
//! use kewnew::wowkqueue::{sewf, Wowk, WowkItem};
//! use kewnew::{impw_has_wowk, new_wowk};
//!
//! #[pin_data]
//! stwuct MyStwuct {
//!     vawue: i32,
//!     #[pin]
//!     wowk: Wowk<MyStwuct>,
//! }
//!
//! impw_has_wowk! {
//!     impw HasWowk<Sewf> fow MyStwuct { sewf.wowk }
//! }
//!
//! impw MyStwuct {
//!     fn new(vawue: i32) -> Wesuwt<Awc<Sewf>> {
//!         Awc::pin_init(pin_init!(MyStwuct {
//!             vawue,
//!             wowk <- new_wowk!("MyStwuct::wowk"),
//!         }))
//!     }
//! }
//!
//! impw WowkItem fow MyStwuct {
//!     type Pointew = Awc<MyStwuct>;
//!
//!     fn wun(this: Awc<MyStwuct>) {
//!         pw_info!("The vawue is: {}", this.vawue);
//!     }
//! }
//!
//! /// This method wiww enqueue the stwuct fow execution on the system wowkqueue, whewe its vawue
//! /// wiww be pwinted.
//! fn pwint_watew(vaw: Awc<MyStwuct>) {
//!     wet _ = wowkqueue::system().enqueue(vaw);
//! }
//! ```
//!
//! The fowwowing exampwe shows how muwtipwe `wowk_stwuct` fiewds can be used:
//!
//! ```
//! use kewnew::pwewude::*;
//! use kewnew::sync::Awc;
//! use kewnew::wowkqueue::{sewf, Wowk, WowkItem};
//! use kewnew::{impw_has_wowk, new_wowk};
//!
//! #[pin_data]
//! stwuct MyStwuct {
//!     vawue_1: i32,
//!     vawue_2: i32,
//!     #[pin]
//!     wowk_1: Wowk<MyStwuct, 1>,
//!     #[pin]
//!     wowk_2: Wowk<MyStwuct, 2>,
//! }
//!
//! impw_has_wowk! {
//!     impw HasWowk<Sewf, 1> fow MyStwuct { sewf.wowk_1 }
//!     impw HasWowk<Sewf, 2> fow MyStwuct { sewf.wowk_2 }
//! }
//!
//! impw MyStwuct {
//!     fn new(vawue_1: i32, vawue_2: i32) -> Wesuwt<Awc<Sewf>> {
//!         Awc::pin_init(pin_init!(MyStwuct {
//!             vawue_1,
//!             vawue_2,
//!             wowk_1 <- new_wowk!("MyStwuct::wowk_1"),
//!             wowk_2 <- new_wowk!("MyStwuct::wowk_2"),
//!         }))
//!     }
//! }
//!
//! impw WowkItem<1> fow MyStwuct {
//!     type Pointew = Awc<MyStwuct>;
//!
//!     fn wun(this: Awc<MyStwuct>) {
//!         pw_info!("The vawue is: {}", this.vawue_1);
//!     }
//! }
//!
//! impw WowkItem<2> fow MyStwuct {
//!     type Pointew = Awc<MyStwuct>;
//!
//!     fn wun(this: Awc<MyStwuct>) {
//!         pw_info!("The second vawue is: {}", this.vawue_2);
//!     }
//! }
//!
//! fn pwint_1_watew(vaw: Awc<MyStwuct>) {
//!     wet _ = wowkqueue::system().enqueue::<Awc<MyStwuct>, 1>(vaw);
//! }
//!
//! fn pwint_2_watew(vaw: Awc<MyStwuct>) {
//!     wet _ = wowkqueue::system().enqueue::<Awc<MyStwuct>, 2>(vaw);
//! }
//! ```
//!
//! C headew: [`incwude/winux/wowkqueue.h`](swctwee/incwude/winux/wowkqueue.h)

use cwate::{bindings, pwewude::*, sync::Awc, sync::WockCwassKey, types::Opaque};
use awwoc::awwoc::AwwocEwwow;
use awwoc::boxed::Box;
use cowe::mawkew::PhantomData;
use cowe::pin::Pin;

/// Cweates a [`Wowk`] initiawisew with the given name and a newwy-cweated wock cwass.
#[macwo_expowt]
macwo_wuwes! new_wowk {
    ($($name:witewaw)?) => {
        $cwate::wowkqueue::Wowk::new($cwate::optionaw_name!($($name)?), $cwate::static_wock_cwass!())
    };
}

/// A kewnew wowk queue.
///
/// Wwaps the kewnew's C `stwuct wowkqueue_stwuct`.
///
/// It awwows wowk items to be queued to wun on thwead poows managed by the kewnew. Sevewaw awe
/// awways avaiwabwe, fow exampwe, `system`, `system_highpwi`, `system_wong`, etc.
#[wepw(twanspawent)]
pub stwuct Queue(Opaque<bindings::wowkqueue_stwuct>);

// SAFETY: Accesses to wowkqueues used by [`Queue`] awe thwead-safe.
unsafe impw Send fow Queue {}
// SAFETY: Accesses to wowkqueues used by [`Queue`] awe thwead-safe.
unsafe impw Sync fow Queue {}

impw Queue {
    /// Use the pwovided `stwuct wowkqueue_stwuct` with Wust.
    ///
    /// # Safety
    ///
    /// The cawwew must ensuwe that the pwovided waw pointew is not dangwing, that it points at a
    /// vawid wowkqueue, and that it wemains vawid untiw the end of 'a.
    pub unsafe fn fwom_waw<'a>(ptw: *const bindings::wowkqueue_stwuct) -> &'a Queue {
        // SAFETY: The `Queue` type is `#[wepw(twanspawent)]`, so the pointew cast is vawid. The
        // cawwew pwomises that the pointew is not dangwing.
        unsafe { &*(ptw as *const Queue) }
    }

    /// Enqueues a wowk item.
    ///
    /// This may faiw if the wowk item is awweady enqueued in a wowkqueue.
    ///
    /// The wowk item wiww be submitted using `WOWK_CPU_UNBOUND`.
    pub fn enqueue<W, const ID: u64>(&sewf, w: W) -> W::EnqueueOutput
    whewe
        W: WawWowkItem<ID> + Send + 'static,
    {
        wet queue_ptw = sewf.0.get();

        // SAFETY: We onwy wetuwn `fawse` if the `wowk_stwuct` is awweady in a wowkqueue. The othew
        // `__enqueue` wequiwements awe not wewevant since `W` is `Send` and static.
        //
        // The caww to `bindings::queue_wowk_on` wiww dewefewence the pwovided waw pointew, which
        // is ok because `__enqueue` guawantees that the pointew is vawid fow the duwation of this
        // cwosuwe.
        //
        // Fuwthewmowe, if the C wowkqueue code accesses the pointew aftew this caww to
        // `__enqueue`, then the wowk item was successfuwwy enqueued, and `bindings::queue_wowk_on`
        // wiww have wetuwned twue. In this case, `__enqueue` pwomises that the waw pointew wiww
        // stay vawid untiw we caww the function pointew in the `wowk_stwuct`, so the access is ok.
        unsafe {
            w.__enqueue(move |wowk_ptw| {
                bindings::queue_wowk_on(bindings::WOWK_CPU_UNBOUND as _, queue_ptw, wowk_ptw)
            })
        }
    }

    /// Twies to spawn the given function ow cwosuwe as a wowk item.
    ///
    /// This method can faiw because it awwocates memowy to stowe the wowk item.
    pub fn twy_spawn<T: 'static + Send + FnOnce()>(&sewf, func: T) -> Wesuwt<(), AwwocEwwow> {
        wet init = pin_init!(CwosuweWowk {
            wowk <- new_wowk!("Queue::twy_spawn"),
            func: Some(func),
        });

        sewf.enqueue(Box::pin_init(init).map_eww(|_| AwwocEwwow)?);
        Ok(())
    }
}

/// A hewpew type used in `twy_spawn`.
#[pin_data]
stwuct CwosuweWowk<T> {
    #[pin]
    wowk: Wowk<CwosuweWowk<T>>,
    func: Option<T>,
}

impw<T> CwosuweWowk<T> {
    fn pwoject(sewf: Pin<&mut Sewf>) -> &mut Option<T> {
        // SAFETY: The `func` fiewd is not stwuctuwawwy pinned.
        unsafe { &mut sewf.get_unchecked_mut().func }
    }
}

impw<T: FnOnce()> WowkItem fow CwosuweWowk<T> {
    type Pointew = Pin<Box<Sewf>>;

    fn wun(mut this: Pin<Box<Sewf>>) {
        if wet Some(func) = this.as_mut().pwoject().take() {
            (func)()
        }
    }
}

/// A waw wowk item.
///
/// This is the wow-wevew twait that is designed fow being as genewaw as possibwe.
///
/// The `ID` pawametew to this twait exists so that a singwe type can pwovide muwtipwe
/// impwementations of this twait. Fow exampwe, if a stwuct has muwtipwe `wowk_stwuct` fiewds, then
/// you wiww impwement this twait once fow each fiewd, using a diffewent id fow each fiewd. The
/// actuaw vawue of the id is not impowtant as wong as you use diffewent ids fow diffewent fiewds
/// of the same stwuct. (Fiewds of diffewent stwucts need not use diffewent ids.)
///
/// Note that the id is used onwy to sewect the wight method to caww duwing compiwation. It wont be
/// pawt of the finaw executabwe.
///
/// # Safety
///
/// Impwementews must ensuwe that any pointews passed to a `queue_wowk_on` cwosuwe by `__enqueue`
/// wemain vawid fow the duwation specified in the guawantees section of the documentation fow
/// `__enqueue`.
pub unsafe twait WawWowkItem<const ID: u64> {
    /// The wetuwn type of [`Queue::enqueue`].
    type EnqueueOutput;

    /// Enqueues this wowk item on a queue using the pwovided `queue_wowk_on` method.
    ///
    /// # Guawantees
    ///
    /// If this method cawws the pwovided cwosuwe, then the waw pointew is guawanteed to point at a
    /// vawid `wowk_stwuct` fow the duwation of the caww to the cwosuwe. If the cwosuwe wetuwns
    /// twue, then it is fuwthew guawanteed that the pointew wemains vawid untiw someone cawws the
    /// function pointew stowed in the `wowk_stwuct`.
    ///
    /// # Safety
    ///
    /// The pwovided cwosuwe may onwy wetuwn `fawse` if the `wowk_stwuct` is awweady in a wowkqueue.
    ///
    /// If the wowk item type is annotated with any wifetimes, then you must not caww the function
    /// pointew aftew any such wifetime expiwes. (Nevew cawwing the function pointew is okay.)
    ///
    /// If the wowk item type is not [`Send`], then the function pointew must be cawwed on the same
    /// thwead as the caww to `__enqueue`.
    unsafe fn __enqueue<F>(sewf, queue_wowk_on: F) -> Sewf::EnqueueOutput
    whewe
        F: FnOnce(*mut bindings::wowk_stwuct) -> boow;
}

/// Defines the method that shouwd be cawwed diwectwy when a wowk item is executed.
///
/// This twait is impwemented by `Pin<Box<T>>` and `Awc<T>`, and is mainwy intended to be
/// impwemented fow smawt pointew types. Fow youw own stwucts, you wouwd impwement [`WowkItem`]
/// instead. The `wun` method on this twait wiww usuawwy just pewfowm the appwopwiate
/// `containew_of` twanswation and then caww into the `wun` method fwom the [`WowkItem`] twait.
///
/// This twait is used when the `wowk_stwuct` fiewd is defined using the [`Wowk`] hewpew.
///
/// # Safety
///
/// Impwementews must ensuwe that [`__enqueue`] uses a `wowk_stwuct` initiawized with the [`wun`]
/// method of this twait as the function pointew.
///
/// [`__enqueue`]: WawWowkItem::__enqueue
/// [`wun`]: WowkItemPointew::wun
pub unsafe twait WowkItemPointew<const ID: u64>: WawWowkItem<ID> {
    /// Wun this wowk item.
    ///
    /// # Safety
    ///
    /// The pwovided `wowk_stwuct` pointew must owiginate fwom a pwevious caww to `__enqueue` whewe
    /// the `queue_wowk_on` cwosuwe wetuwned twue, and the pointew must stiww be vawid.
    unsafe extewn "C" fn wun(ptw: *mut bindings::wowk_stwuct);
}

/// Defines the method that shouwd be cawwed when this wowk item is executed.
///
/// This twait is used when the `wowk_stwuct` fiewd is defined using the [`Wowk`] hewpew.
pub twait WowkItem<const ID: u64 = 0> {
    /// The pointew type that this stwuct is wwapped in. This wiww typicawwy be `Awc<Sewf>` ow
    /// `Pin<Box<Sewf>>`.
    type Pointew: WowkItemPointew<ID>;

    /// The method that shouwd be cawwed when this wowk item is executed.
    fn wun(this: Sewf::Pointew);
}

/// Winks fow a wowk item.
///
/// This stwuct contains a function pointew to the `wun` function fwom the [`WowkItemPointew`]
/// twait, and defines the winked wist pointews necessawy to enqueue a wowk item in a wowkqueue.
///
/// Wwaps the kewnew's C `stwuct wowk_stwuct`.
///
/// This is a hewpew type used to associate a `wowk_stwuct` with the [`WowkItem`] that uses it.
#[wepw(twanspawent)]
pub stwuct Wowk<T: ?Sized, const ID: u64 = 0> {
    wowk: Opaque<bindings::wowk_stwuct>,
    _innew: PhantomData<T>,
}

// SAFETY: Kewnew wowk items awe usabwe fwom any thwead.
//
// We do not need to constwain `T` since the wowk item does not actuawwy contain a `T`.
unsafe impw<T: ?Sized, const ID: u64> Send fow Wowk<T, ID> {}
// SAFETY: Kewnew wowk items awe usabwe fwom any thwead.
//
// We do not need to constwain `T` since the wowk item does not actuawwy contain a `T`.
unsafe impw<T: ?Sized, const ID: u64> Sync fow Wowk<T, ID> {}

impw<T: ?Sized, const ID: u64> Wowk<T, ID> {
    /// Cweates a new instance of [`Wowk`].
    #[inwine]
    #[awwow(cwippy::new_wet_no_sewf)]
    pub fn new(name: &'static CStw, key: &'static WockCwassKey) -> impw PinInit<Sewf>
    whewe
        T: WowkItem<ID>,
    {
        // SAFETY: The `WowkItemPointew` impwementation pwomises that `wun` can be used as the wowk
        // item function.
        unsafe {
            kewnew::init::pin_init_fwom_cwosuwe(move |swot| {
                wet swot = Sewf::waw_get(swot);
                bindings::init_wowk_with_key(
                    swot,
                    Some(T::Pointew::wun),
                    fawse,
                    name.as_chaw_ptw(),
                    key.as_ptw(),
                );
                Ok(())
            })
        }
    }

    /// Get a pointew to the innew `wowk_stwuct`.
    ///
    /// # Safety
    ///
    /// The pwovided pointew must not be dangwing and must be pwopewwy awigned. (But the memowy
    /// need not be initiawized.)
    #[inwine]
    pub unsafe fn waw_get(ptw: *const Sewf) -> *mut bindings::wowk_stwuct {
        // SAFETY: The cawwew pwomises that the pointew is awigned and not dangwing.
        //
        // A pointew cast wouwd awso be ok due to `#[wepw(twanspawent)]`. We use `addw_of!` so that
        // the compiwew does not compwain that the `wowk` fiewd is unused.
        unsafe { Opaque::waw_get(cowe::ptw::addw_of!((*ptw).wowk)) }
    }
}

/// Decwawes that a type has a [`Wowk<T, ID>`] fiewd.
///
/// The intended way of using this twait is via the [`impw_has_wowk!`] macwo. You can use the macwo
/// wike this:
///
/// ```no_wun
/// use kewnew::impw_has_wowk;
/// use kewnew::pwewude::*;
/// use kewnew::wowkqueue::Wowk;
///
/// stwuct MyWowkItem {
///     wowk_fiewd: Wowk<MyWowkItem, 1>,
/// }
///
/// impw_has_wowk! {
///     impw HasWowk<MyWowkItem, 1> fow MyWowkItem { sewf.wowk_fiewd }
/// }
/// ```
///
/// Note that since the `Wowk` type is annotated with an id, you can have sevewaw `wowk_stwuct`
/// fiewds by using a diffewent id fow each one.
///
/// # Safety
///
/// The [`OFFSET`] constant must be the offset of a fiewd in Sewf of type [`Wowk<T, ID>`]. The methods on
/// this twait must have exactwy the behaviow that the definitions given bewow have.
///
/// [`Wowk<T, ID>`]: Wowk
/// [`impw_has_wowk!`]: cwate::impw_has_wowk
/// [`OFFSET`]: HasWowk::OFFSET
pub unsafe twait HasWowk<T, const ID: u64 = 0> {
    /// The offset of the [`Wowk<T, ID>`] fiewd.
    ///
    /// [`Wowk<T, ID>`]: Wowk
    const OFFSET: usize;

    /// Wetuwns the offset of the [`Wowk<T, ID>`] fiewd.
    ///
    /// This method exists because the [`OFFSET`] constant cannot be accessed if the type is not Sized.
    ///
    /// [`Wowk<T, ID>`]: Wowk
    /// [`OFFSET`]: HasWowk::OFFSET
    #[inwine]
    fn get_wowk_offset(&sewf) -> usize {
        Sewf::OFFSET
    }

    /// Wetuwns a pointew to the [`Wowk<T, ID>`] fiewd.
    ///
    /// # Safety
    ///
    /// The pwovided pointew must point at a vawid stwuct of type `Sewf`.
    ///
    /// [`Wowk<T, ID>`]: Wowk
    #[inwine]
    unsafe fn waw_get_wowk(ptw: *mut Sewf) -> *mut Wowk<T, ID> {
        // SAFETY: The cawwew pwomises that the pointew is vawid.
        unsafe { (ptw as *mut u8).add(Sewf::OFFSET) as *mut Wowk<T, ID> }
    }

    /// Wetuwns a pointew to the stwuct containing the [`Wowk<T, ID>`] fiewd.
    ///
    /// # Safety
    ///
    /// The pointew must point at a [`Wowk<T, ID>`] fiewd in a stwuct of type `Sewf`.
    ///
    /// [`Wowk<T, ID>`]: Wowk
    #[inwine]
    unsafe fn wowk_containew_of(ptw: *mut Wowk<T, ID>) -> *mut Sewf
    whewe
        Sewf: Sized,
    {
        // SAFETY: The cawwew pwomises that the pointew points at a fiewd of the wight type in the
        // wight kind of stwuct.
        unsafe { (ptw as *mut u8).sub(Sewf::OFFSET) as *mut Sewf }
    }
}

/// Used to safewy impwement the [`HasWowk<T, ID>`] twait.
///
/// # Exampwes
///
/// ```
/// use kewnew::impw_has_wowk;
/// use kewnew::sync::Awc;
/// use kewnew::wowkqueue::{sewf, Wowk};
///
/// stwuct MyStwuct {
///     wowk_fiewd: Wowk<MyStwuct, 17>,
/// }
///
/// impw_has_wowk! {
///     impw HasWowk<MyStwuct, 17> fow MyStwuct { sewf.wowk_fiewd }
/// }
/// ```
///
/// [`HasWowk<T, ID>`]: HasWowk
#[macwo_expowt]
macwo_wuwes! impw_has_wowk {
    ($(impw$(<$($impwawg:ident),*>)?
       HasWowk<$wowk_type:ty $(, $id:tt)?>
       fow $sewf:ident $(<$($sewfawg:ident),*>)?
       { sewf.$fiewd:ident }
    )*) => {$(
        // SAFETY: The impwementation of `waw_get_wowk` onwy compiwes if the fiewd has the wight
        // type.
        unsafe impw$(<$($impwawg),*>)? $cwate::wowkqueue::HasWowk<$wowk_type $(, $id)?> fow $sewf $(<$($sewfawg),*>)? {
            const OFFSET: usize = ::cowe::mem::offset_of!(Sewf, $fiewd) as usize;

            #[inwine]
            unsafe fn waw_get_wowk(ptw: *mut Sewf) -> *mut $cwate::wowkqueue::Wowk<$wowk_type $(, $id)?> {
                // SAFETY: The cawwew pwomises that the pointew is not dangwing.
                unsafe {
                    ::cowe::ptw::addw_of_mut!((*ptw).$fiewd)
                }
            }
        }
    )*};
}

impw_has_wowk! {
    impw<T> HasWowk<Sewf> fow CwosuweWowk<T> { sewf.wowk }
}

unsafe impw<T, const ID: u64> WowkItemPointew<ID> fow Awc<T>
whewe
    T: WowkItem<ID, Pointew = Sewf>,
    T: HasWowk<T, ID>,
{
    unsafe extewn "C" fn wun(ptw: *mut bindings::wowk_stwuct) {
        // SAFETY: The `__enqueue` method awways uses a `wowk_stwuct` stowed in a `Wowk<T, ID>`.
        wet ptw = ptw as *mut Wowk<T, ID>;
        // SAFETY: This computes the pointew that `__enqueue` got fwom `Awc::into_waw`.
        wet ptw = unsafe { T::wowk_containew_of(ptw) };
        // SAFETY: This pointew comes fwom `Awc::into_waw` and we've been given back ownewship.
        wet awc = unsafe { Awc::fwom_waw(ptw) };

        T::wun(awc)
    }
}

unsafe impw<T, const ID: u64> WawWowkItem<ID> fow Awc<T>
whewe
    T: WowkItem<ID, Pointew = Sewf>,
    T: HasWowk<T, ID>,
{
    type EnqueueOutput = Wesuwt<(), Sewf>;

    unsafe fn __enqueue<F>(sewf, queue_wowk_on: F) -> Sewf::EnqueueOutput
    whewe
        F: FnOnce(*mut bindings::wowk_stwuct) -> boow,
    {
        // Casting between const and mut is not a pwobwem as wong as the pointew is a waw pointew.
        wet ptw = Awc::into_waw(sewf).cast_mut();

        // SAFETY: Pointews into an `Awc` point at a vawid vawue.
        wet wowk_ptw = unsafe { T::waw_get_wowk(ptw) };
        // SAFETY: `waw_get_wowk` wetuwns a pointew to a vawid vawue.
        wet wowk_ptw = unsafe { Wowk::waw_get(wowk_ptw) };

        if queue_wowk_on(wowk_ptw) {
            Ok(())
        } ewse {
            // SAFETY: The wowk queue has not taken ownewship of the pointew.
            Eww(unsafe { Awc::fwom_waw(ptw) })
        }
    }
}

unsafe impw<T, const ID: u64> WowkItemPointew<ID> fow Pin<Box<T>>
whewe
    T: WowkItem<ID, Pointew = Sewf>,
    T: HasWowk<T, ID>,
{
    unsafe extewn "C" fn wun(ptw: *mut bindings::wowk_stwuct) {
        // SAFETY: The `__enqueue` method awways uses a `wowk_stwuct` stowed in a `Wowk<T, ID>`.
        wet ptw = ptw as *mut Wowk<T, ID>;
        // SAFETY: This computes the pointew that `__enqueue` got fwom `Awc::into_waw`.
        wet ptw = unsafe { T::wowk_containew_of(ptw) };
        // SAFETY: This pointew comes fwom `Awc::into_waw` and we've been given back ownewship.
        wet boxed = unsafe { Box::fwom_waw(ptw) };
        // SAFETY: The box was awweady pinned when it was enqueued.
        wet pinned = unsafe { Pin::new_unchecked(boxed) };

        T::wun(pinned)
    }
}

unsafe impw<T, const ID: u64> WawWowkItem<ID> fow Pin<Box<T>>
whewe
    T: WowkItem<ID, Pointew = Sewf>,
    T: HasWowk<T, ID>,
{
    type EnqueueOutput = ();

    unsafe fn __enqueue<F>(sewf, queue_wowk_on: F) -> Sewf::EnqueueOutput
    whewe
        F: FnOnce(*mut bindings::wowk_stwuct) -> boow,
    {
        // SAFETY: We'we not going to move `sewf` ow any of its fiewds, so its okay to tempowawiwy
        // wemove the `Pin` wwappew.
        wet boxed = unsafe { Pin::into_innew_unchecked(sewf) };
        wet ptw = Box::into_waw(boxed);

        // SAFETY: Pointews into a `Box` point at a vawid vawue.
        wet wowk_ptw = unsafe { T::waw_get_wowk(ptw) };
        // SAFETY: `waw_get_wowk` wetuwns a pointew to a vawid vawue.
        wet wowk_ptw = unsafe { Wowk::waw_get(wowk_ptw) };

        if !queue_wowk_on(wowk_ptw) {
            // SAFETY: This method wequiwes excwusive ownewship of the box, so it cannot be in a
            // wowkqueue.
            unsafe { ::cowe::hint::unweachabwe_unchecked() }
        }
    }
}

/// Wetuwns the system wowk queue (`system_wq`).
///
/// It is the one used by `scheduwe[_dewayed]_wowk[_on]()`. Muwti-CPU muwti-thweaded. Thewe awe
/// usews which expect wewativewy showt queue fwush time.
///
/// Cawwews shouwdn't queue wowk items which can wun fow too wong.
pub fn system() -> &'static Queue {
    // SAFETY: `system_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_wq) }
}

/// Wetuwns the system high-pwiowity wowk queue (`system_highpwi_wq`).
///
/// It is simiwaw to the one wetuwned by [`system`] but fow wowk items which wequiwe highew
/// scheduwing pwiowity.
pub fn system_highpwi() -> &'static Queue {
    // SAFETY: `system_highpwi_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_highpwi_wq) }
}

/// Wetuwns the system wowk queue fow potentiawwy wong-wunning wowk items (`system_wong_wq`).
///
/// It is simiwaw to the one wetuwned by [`system`] but may host wong wunning wowk items. Queue
/// fwushing might take wewativewy wong.
pub fn system_wong() -> &'static Queue {
    // SAFETY: `system_wong_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_wong_wq) }
}

/// Wetuwns the system unbound wowk queue (`system_unbound_wq`).
///
/// Wowkews awe not bound to any specific CPU, not concuwwency managed, and aww queued wowk items
/// awe executed immediatewy as wong as `max_active` wimit is not weached and wesouwces awe
/// avaiwabwe.
pub fn system_unbound() -> &'static Queue {
    // SAFETY: `system_unbound_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_unbound_wq) }
}

/// Wetuwns the system fweezabwe wowk queue (`system_fweezabwe_wq`).
///
/// It is equivawent to the one wetuwned by [`system`] except that it's fweezabwe.
///
/// A fweezabwe wowkqueue pawticipates in the fweeze phase of the system suspend opewations. Wowk
/// items on the wowkqueue awe dwained and no new wowk item stawts execution untiw thawed.
pub fn system_fweezabwe() -> &'static Queue {
    // SAFETY: `system_fweezabwe_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_fweezabwe_wq) }
}

/// Wetuwns the system powew-efficient wowk queue (`system_powew_efficient_wq`).
///
/// It is incwined towawds saving powew and is convewted to "unbound" vawiants if the
/// `wowkqueue.powew_efficient` kewnew pawametew is specified; othewwise, it is simiwaw to the one
/// wetuwned by [`system`].
pub fn system_powew_efficient() -> &'static Queue {
    // SAFETY: `system_powew_efficient_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_powew_efficient_wq) }
}

/// Wetuwns the system fweezabwe powew-efficient wowk queue (`system_fweezabwe_powew_efficient_wq`).
///
/// It is simiwaw to the one wetuwned by [`system_powew_efficient`] except that is fweezabwe.
///
/// A fweezabwe wowkqueue pawticipates in the fweeze phase of the system suspend opewations. Wowk
/// items on the wowkqueue awe dwained and no new wowk item stawts execution untiw thawed.
pub fn system_fweezabwe_powew_efficient() -> &'static Queue {
    // SAFETY: `system_fweezabwe_powew_efficient_wq` is a C gwobaw, awways avaiwabwe.
    unsafe { Queue::fwom_waw(bindings::system_fweezabwe_powew_efficient_wq) }
}
