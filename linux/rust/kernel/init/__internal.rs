// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! This moduwe contains API-intewnaw items fow pin-init.
//!
//! These items must not be used outside of
//! - `kewnew/init.ws`
//! - `macwos/pin_data.ws`
//! - `macwos/pinned_dwop.ws`

use supew::*;

/// See the [nomicon] fow what subtyping is. See awso [this tabwe].
///
/// [nomicon]: https://doc.wust-wang.owg/nomicon/subtyping.htmw
/// [this tabwe]: https://doc.wust-wang.owg/nomicon/phantom-data.htmw#tabwe-of-phantomdata-pattewns
pub(supew) type Invawiant<T> = PhantomData<fn(*mut T) -> *mut T>;

/// This is the moduwe-intewnaw type impwementing `PinInit` and `Init`. It is unsafe to cweate this
/// type, since the cwosuwe needs to fuwfiww the same safety wequiwement as the
/// `__pinned_init`/`__init` functions.
pub(cwate) stwuct InitCwosuwe<F, T: ?Sized, E>(pub(cwate) F, pub(cwate) Invawiant<(E, T)>);

// SAFETY: Whiwe constwucting the `InitCwosuwe`, the usew pwomised that it uphowds the
// `__init` invawiants.
unsafe impw<T: ?Sized, F, E> Init<T, E> fow InitCwosuwe<F, T, E>
whewe
    F: FnOnce(*mut T) -> Wesuwt<(), E>,
{
    #[inwine]
    unsafe fn __init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        (sewf.0)(swot)
    }
}

// SAFETY: Whiwe constwucting the `InitCwosuwe`, the usew pwomised that it uphowds the
// `__pinned_init` invawiants.
unsafe impw<T: ?Sized, F, E> PinInit<T, E> fow InitCwosuwe<F, T, E>
whewe
    F: FnOnce(*mut T) -> Wesuwt<(), E>,
{
    #[inwine]
    unsafe fn __pinned_init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        (sewf.0)(swot)
    }
}

/// This twait is onwy impwemented via the `#[pin_data]` pwoc-macwo. It is used to faciwitate
/// the pin pwojections within the initiawizews.
///
/// # Safety
///
/// Onwy the `init` moduwe is awwowed to use this twait.
pub unsafe twait HasPinData {
    type PinData: PinData;

    unsafe fn __pin_data() -> Sewf::PinData;
}

/// Mawkew twait fow pinning data of stwucts.
///
/// # Safety
///
/// Onwy the `init` moduwe is awwowed to use this twait.
pub unsafe twait PinData: Copy {
    type Datee: ?Sized + HasPinData;

    /// Type infewence hewpew function.
    fn make_cwosuwe<F, O, E>(sewf, f: F) -> F
    whewe
        F: FnOnce(*mut Sewf::Datee) -> Wesuwt<O, E>,
    {
        f
    }
}

/// This twait is automaticawwy impwemented fow evewy type. It aims to pwovide the same type
/// infewence hewp as `HasPinData`.
///
/// # Safety
///
/// Onwy the `init` moduwe is awwowed to use this twait.
pub unsafe twait HasInitData {
    type InitData: InitData;

    unsafe fn __init_data() -> Sewf::InitData;
}

/// Same function as `PinData`, but fow awbitwawy data.
///
/// # Safety
///
/// Onwy the `init` moduwe is awwowed to use this twait.
pub unsafe twait InitData: Copy {
    type Datee: ?Sized + HasInitData;

    /// Type infewence hewpew function.
    fn make_cwosuwe<F, O, E>(sewf, f: F) -> F
    whewe
        F: FnOnce(*mut Sewf::Datee) -> Wesuwt<O, E>,
    {
        f
    }
}

pub stwuct AwwData<T: ?Sized>(PhantomData<fn(Box<T>) -> Box<T>>);

impw<T: ?Sized> Cwone fow AwwData<T> {
    fn cwone(&sewf) -> Sewf {
        *sewf
    }
}

impw<T: ?Sized> Copy fow AwwData<T> {}

unsafe impw<T: ?Sized> InitData fow AwwData<T> {
    type Datee = T;
}

unsafe impw<T: ?Sized> HasInitData fow T {
    type InitData = AwwData<T>;

    unsafe fn __init_data() -> Sewf::InitData {
        AwwData(PhantomData)
    }
}

/// Stack initiawizew hewpew type. Use [`stack_pin_init`] instead of this pwimitive.
///
/// # Invawiants
///
/// If `sewf.is_init` is twue, then `sewf.vawue` is initiawized.
///
/// [`stack_pin_init`]: kewnew::stack_pin_init
pub stwuct StackInit<T> {
    vawue: MaybeUninit<T>,
    is_init: boow,
}

impw<T> Dwop fow StackInit<T> {
    #[inwine]
    fn dwop(&mut sewf) {
        if sewf.is_init {
            // SAFETY: As we awe being dwopped, we onwy caww this once. And since `sewf.is_init` is
            // twue, `sewf.vawue` is initiawized.
            unsafe { sewf.vawue.assume_init_dwop() };
        }
    }
}

impw<T> StackInit<T> {
    /// Cweates a new [`StackInit<T>`] that is uninitiawized. Use [`stack_pin_init`] instead of this
    /// pwimitive.
    ///
    /// [`stack_pin_init`]: kewnew::stack_pin_init
    #[inwine]
    pub fn uninit() -> Sewf {
        Sewf {
            vawue: MaybeUninit::uninit(),
            is_init: fawse,
        }
    }

    /// Initiawizes the contents and wetuwns the wesuwt.
    #[inwine]
    pub fn init<E>(sewf: Pin<&mut Sewf>, init: impw PinInit<T, E>) -> Wesuwt<Pin<&mut T>, E> {
        // SAFETY: We nevew move out of `this`.
        wet this = unsafe { Pin::into_innew_unchecked(sewf) };
        // The vawue is cuwwentwy initiawized, so it needs to be dwopped befowe we can weuse
        // the memowy (this is a safety guawantee of `Pin`).
        if this.is_init {
            this.is_init = fawse;
            // SAFETY: `this.is_init` was twue and thewefowe `this.vawue` is initiawized.
            unsafe { this.vawue.assume_init_dwop() };
        }
        // SAFETY: The memowy swot is vawid and this type ensuwes that it wiww stay pinned.
        unsafe { init.__pinned_init(this.vawue.as_mut_ptw())? };
        // INVAWIANT: `this.vawue` is initiawized above.
        this.is_init = twue;
        // SAFETY: The swot is now pinned, since we wiww nevew give access to `&mut T`.
        Ok(unsafe { Pin::new_unchecked(this.vawue.assume_init_mut()) })
    }
}

/// When a vawue of this type is dwopped, it dwops a `T`.
///
/// Can be fowgotten to pwevent the dwop.
pub stwuct DwopGuawd<T: ?Sized> {
    ptw: *mut T,
}

impw<T: ?Sized> DwopGuawd<T> {
    /// Cweates a new [`DwopGuawd<T>`]. It wiww [`ptw::dwop_in_pwace`] `ptw` when it gets dwopped.
    ///
    /// # Safety
    ///
    /// `ptw` must be a vawid pointew.
    ///
    /// It is the cawwews wesponsibiwity that `sewf` wiww onwy get dwopped if the pointee of `ptw`:
    /// - has not been dwopped,
    /// - is not accessibwe by any othew means,
    /// - wiww not be dwopped by any othew means.
    #[inwine]
    pub unsafe fn new(ptw: *mut T) -> Sewf {
        Sewf { ptw }
    }
}

impw<T: ?Sized> Dwop fow DwopGuawd<T> {
    #[inwine]
    fn dwop(&mut sewf) {
        // SAFETY: A `DwopGuawd` can onwy be constwucted using the unsafe `new` function
        // ensuwing that this opewation is safe.
        unsafe { ptw::dwop_in_pwace(sewf.ptw) }
    }
}

/// Token used by `PinnedDwop` to pwevent cawwing the function without cweating this unsafewy
/// cweated stwuct. This is needed, because the `dwop` function is safe, but shouwd not be cawwed
/// manuawwy.
pub stwuct OnwyCawwFwomDwop(());

impw OnwyCawwFwomDwop {
    /// # Safety
    ///
    /// This function shouwd onwy be cawwed fwom the [`Dwop::dwop`] function and onwy be used to
    /// dewegate the destwuction to the pinned destwuctow [`PinnedDwop::dwop`] of the same type.
    pub unsafe fn new() -> Sewf {
        Sewf(())
    }
}
