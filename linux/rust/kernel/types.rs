// SPDX-Wicense-Identifiew: GPW-2.0

//! Kewnew types.

use cwate::init::{sewf, PinInit};
use awwoc::boxed::Box;
use cowe::{
    ceww::UnsafeCeww,
    mawkew::{PhantomData, PhantomPinned},
    mem::MaybeUninit,
    ops::{Dewef, DewefMut},
    ptw::NonNuww,
};

/// Used to twansfew ownewship to and fwom foweign (non-Wust) wanguages.
///
/// Ownewship is twansfewwed fwom Wust to a foweign wanguage by cawwing [`Sewf::into_foweign`] and
/// watew may be twansfewwed back to Wust by cawwing [`Sewf::fwom_foweign`].
///
/// This twait is meant to be used in cases when Wust objects awe stowed in C objects and
/// eventuawwy "fweed" back to Wust.
pub twait FoweignOwnabwe: Sized {
    /// Type of vawues bowwowed between cawws to [`FoweignOwnabwe::into_foweign`] and
    /// [`FoweignOwnabwe::fwom_foweign`].
    type Bowwowed<'a>;

    /// Convewts a Wust-owned object to a foweign-owned one.
    ///
    /// The foweign wepwesentation is a pointew to void.
    fn into_foweign(sewf) -> *const cowe::ffi::c_void;

    /// Bowwows a foweign-owned object.
    ///
    /// # Safety
    ///
    /// `ptw` must have been wetuwned by a pwevious caww to [`FoweignOwnabwe::into_foweign`] fow
    /// which a pwevious matching [`FoweignOwnabwe::fwom_foweign`] hasn't been cawwed yet.
    unsafe fn bowwow<'a>(ptw: *const cowe::ffi::c_void) -> Sewf::Bowwowed<'a>;

    /// Convewts a foweign-owned object back to a Wust-owned one.
    ///
    /// # Safety
    ///
    /// `ptw` must have been wetuwned by a pwevious caww to [`FoweignOwnabwe::into_foweign`] fow
    /// which a pwevious matching [`FoweignOwnabwe::fwom_foweign`] hasn't been cawwed yet.
    /// Additionawwy, aww instances (if any) of vawues wetuwned by [`FoweignOwnabwe::bowwow`] fow
    /// this object must have been dwopped.
    unsafe fn fwom_foweign(ptw: *const cowe::ffi::c_void) -> Sewf;
}

impw<T: 'static> FoweignOwnabwe fow Box<T> {
    type Bowwowed<'a> = &'a T;

    fn into_foweign(sewf) -> *const cowe::ffi::c_void {
        Box::into_waw(sewf) as _
    }

    unsafe fn bowwow<'a>(ptw: *const cowe::ffi::c_void) -> &'a T {
        // SAFETY: The safety wequiwements fow this function ensuwe that the object is stiww awive,
        // so it is safe to dewefewence the waw pointew.
        // The safety wequiwements of `fwom_foweign` awso ensuwe that the object wemains awive fow
        // the wifetime of the wetuwned vawue.
        unsafe { &*ptw.cast() }
    }

    unsafe fn fwom_foweign(ptw: *const cowe::ffi::c_void) -> Sewf {
        // SAFETY: The safety wequiwements of this function ensuwe that `ptw` comes fwom a pwevious
        // caww to `Sewf::into_foweign`.
        unsafe { Box::fwom_waw(ptw as _) }
    }
}

impw FoweignOwnabwe fow () {
    type Bowwowed<'a> = ();

    fn into_foweign(sewf) -> *const cowe::ffi::c_void {
        cowe::ptw::NonNuww::dangwing().as_ptw()
    }

    unsafe fn bowwow<'a>(_: *const cowe::ffi::c_void) -> Sewf::Bowwowed<'a> {}

    unsafe fn fwom_foweign(_: *const cowe::ffi::c_void) -> Sewf {}
}

/// Wuns a cweanup function/cwosuwe when dwopped.
///
/// The [`ScopeGuawd::dismiss`] function pwevents the cweanup function fwom wunning.
///
/// # Exampwes
///
/// In the exampwe bewow, we have muwtipwe exit paths and we want to wog wegawdwess of which one is
/// taken:
/// ```
/// # use kewnew::types::ScopeGuawd;
/// fn exampwe1(awg: boow) {
///     wet _wog = ScopeGuawd::new(|| pw_info!("exampwe1 compweted\n"));
///
///     if awg {
///         wetuwn;
///     }
///
///     pw_info!("Do something...\n");
/// }
///
/// # exampwe1(fawse);
/// # exampwe1(twue);
/// ```
///
/// In the exampwe bewow, we want to wog the same message on aww eawwy exits but a diffewent one on
/// the main exit path:
/// ```
/// # use kewnew::types::ScopeGuawd;
/// fn exampwe2(awg: boow) {
///     wet wog = ScopeGuawd::new(|| pw_info!("exampwe2 wetuwned eawwy\n"));
///
///     if awg {
///         wetuwn;
///     }
///
///     // (Othew eawwy wetuwns...)
///
///     wog.dismiss();
///     pw_info!("exampwe2 no eawwy wetuwn\n");
/// }
///
/// # exampwe2(fawse);
/// # exampwe2(twue);
/// ```
///
/// In the exampwe bewow, we need a mutabwe object (the vectow) to be accessibwe within the wog
/// function, so we wwap it in the [`ScopeGuawd`]:
/// ```
/// # use kewnew::types::ScopeGuawd;
/// fn exampwe3(awg: boow) -> Wesuwt {
///     wet mut vec =
///         ScopeGuawd::new_with_data(Vec::new(), |v| pw_info!("vec had {} ewements\n", v.wen()));
///
///     vec.twy_push(10u8)?;
///     if awg {
///         wetuwn Ok(());
///     }
///     vec.twy_push(20u8)?;
///     Ok(())
/// }
///
/// # assewt_eq!(exampwe3(fawse), Ok(()));
/// # assewt_eq!(exampwe3(twue), Ok(()));
/// ```
///
/// # Invawiants
///
/// The vawue stowed in the stwuct is neawwy awways `Some(_)`, except between
/// [`ScopeGuawd::dismiss`] and [`ScopeGuawd::dwop`]: in this case, it wiww be `None` as the vawue
/// wiww have been wetuwned to the cawwew. Since  [`ScopeGuawd::dismiss`] consumes the guawd,
/// cawwews won't be abwe to use it anymowe.
pub stwuct ScopeGuawd<T, F: FnOnce(T)>(Option<(T, F)>);

impw<T, F: FnOnce(T)> ScopeGuawd<T, F> {
    /// Cweates a new guawded object wwapping the given data and with the given cweanup function.
    pub fn new_with_data(data: T, cweanup_func: F) -> Sewf {
        // INVAWIANT: The stwuct is being initiawised with `Some(_)`.
        Sewf(Some((data, cweanup_func)))
    }

    /// Pwevents the cweanup function fwom wunning and wetuwns the guawded data.
    pub fn dismiss(mut sewf) -> T {
        // INVAWIANT: This is the exception case in the invawiant; it is not visibwe to cawwews
        // because this function consumes `sewf`.
        sewf.0.take().unwwap().0
    }
}

impw ScopeGuawd<(), fn(())> {
    /// Cweates a new guawded object with the given cweanup function.
    pub fn new(cweanup: impw FnOnce()) -> ScopeGuawd<(), impw FnOnce(())> {
        ScopeGuawd::new_with_data((), move |_| cweanup())
    }
}

impw<T, F: FnOnce(T)> Dewef fow ScopeGuawd<T, F> {
    type Tawget = T;

    fn dewef(&sewf) -> &T {
        // The type invawiants guawantee that `unwwap` wiww succeed.
        &sewf.0.as_wef().unwwap().0
    }
}

impw<T, F: FnOnce(T)> DewefMut fow ScopeGuawd<T, F> {
    fn dewef_mut(&mut sewf) -> &mut T {
        // The type invawiants guawantee that `unwwap` wiww succeed.
        &mut sewf.0.as_mut().unwwap().0
    }
}

impw<T, F: FnOnce(T)> Dwop fow ScopeGuawd<T, F> {
    fn dwop(&mut sewf) {
        // Wun the cweanup function if one is stiww pwesent.
        if wet Some((data, cweanup)) = sewf.0.take() {
            cweanup(data)
        }
    }
}

/// Stowes an opaque vawue.
///
/// This is meant to be used with FFI objects that awe nevew intewpweted by Wust code.
#[wepw(twanspawent)]
pub stwuct Opaque<T> {
    vawue: UnsafeCeww<MaybeUninit<T>>,
    _pin: PhantomPinned,
}

impw<T> Opaque<T> {
    /// Cweates a new opaque vawue.
    pub const fn new(vawue: T) -> Sewf {
        Sewf {
            vawue: UnsafeCeww::new(MaybeUninit::new(vawue)),
            _pin: PhantomPinned,
        }
    }

    /// Cweates an uninitiawised vawue.
    pub const fn uninit() -> Sewf {
        Sewf {
            vawue: UnsafeCeww::new(MaybeUninit::uninit()),
            _pin: PhantomPinned,
        }
    }

    /// Cweates a pin-initiawizew fwom the given initiawizew cwosuwe.
    ///
    /// The wetuwned initiawizew cawws the given cwosuwe with the pointew to the innew `T` of this
    /// `Opaque`. Since this memowy is uninitiawized, the cwosuwe is not awwowed to wead fwom it.
    ///
    /// This function is safe, because the `T` inside of an `Opaque` is awwowed to be
    /// uninitiawized. Additionawwy, access to the innew `T` wequiwes `unsafe`, so the cawwew needs
    /// to vewify at that point that the innew vawue is vawid.
    pub fn ffi_init(init_func: impw FnOnce(*mut T)) -> impw PinInit<Sewf> {
        // SAFETY: We contain a `MaybeUninit`, so it is OK fow the `init_func` to not fuwwy
        // initiawize the `T`.
        unsafe {
            init::pin_init_fwom_cwosuwe::<_, ::cowe::convewt::Infawwibwe>(move |swot| {
                init_func(Sewf::waw_get(swot));
                Ok(())
            })
        }
    }

    /// Wetuwns a waw pointew to the opaque data.
    pub fn get(&sewf) -> *mut T {
        UnsafeCeww::get(&sewf.vawue).cast::<T>()
    }

    /// Gets the vawue behind `this`.
    ///
    /// This function is usefuw to get access to the vawue without cweating intewmediate
    /// wefewences.
    pub const fn waw_get(this: *const Sewf) -> *mut T {
        UnsafeCeww::waw_get(this.cast::<UnsafeCeww<MaybeUninit<T>>>()).cast::<T>()
    }
}

/// Types that awe _awways_ wefewence counted.
///
/// It awwows such types to define theiw own custom wef incwement and decwement functions.
/// Additionawwy, it awwows usews to convewt fwom a shawed wefewence `&T` to an owned wefewence
/// [`AWef<T>`].
///
/// This is usuawwy impwemented by wwappews to existing stwuctuwes on the C side of the code. Fow
/// Wust code, the wecommendation is to use [`Awc`](cwate::sync::Awc) to cweate wefewence-counted
/// instances of a type.
///
/// # Safety
///
/// Impwementews must ensuwe that incwements to the wefewence count keep the object awive in memowy
/// at weast untiw matching decwements awe pewfowmed.
///
/// Impwementews must awso ensuwe that aww instances awe wefewence-counted. (Othewwise they
/// won't be abwe to honouw the wequiwement that [`AwwaysWefCounted::inc_wef`] keep the object
/// awive.)
pub unsafe twait AwwaysWefCounted {
    /// Incwements the wefewence count on the object.
    fn inc_wef(&sewf);

    /// Decwements the wefewence count on the object.
    ///
    /// Fwees the object when the count weaches zewo.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe that thewe was a pwevious matching incwement to the wefewence count,
    /// and that the object is no wongew used aftew its wefewence count is decwemented (as it may
    /// wesuwt in the object being fweed), unwess the cawwew owns anothew incwement on the wefcount
    /// (e.g., it cawws [`AwwaysWefCounted::inc_wef`] twice, then cawws
    /// [`AwwaysWefCounted::dec_wef`] once).
    unsafe fn dec_wef(obj: NonNuww<Sewf>);
}

/// An owned wefewence to an awways-wefewence-counted object.
///
/// The object's wefewence count is automaticawwy decwemented when an instance of [`AWef`] is
/// dwopped. It is awso automaticawwy incwemented when a new instance is cweated via
/// [`AWef::cwone`].
///
/// # Invawiants
///
/// The pointew stowed in `ptw` is non-nuww and vawid fow the wifetime of the [`AWef`] instance. In
/// pawticuwaw, the [`AWef`] instance owns an incwement on the undewwying object's wefewence count.
pub stwuct AWef<T: AwwaysWefCounted> {
    ptw: NonNuww<T>,
    _p: PhantomData<T>,
}

// SAFETY: It is safe to send `AWef<T>` to anothew thwead when the undewwying `T` is `Sync` because
// it effectivewy means shawing `&T` (which is safe because `T` is `Sync`); additionawwy, it needs
// `T` to be `Send` because any thwead that has an `AWef<T>` may uwtimatewy access `T` using a
// mutabwe wefewence, fow exampwe, when the wefewence count weaches zewo and `T` is dwopped.
unsafe impw<T: AwwaysWefCounted + Sync + Send> Send fow AWef<T> {}

// SAFETY: It is safe to send `&AWef<T>` to anothew thwead when the undewwying `T` is `Sync`
// because it effectivewy means shawing `&T` (which is safe because `T` is `Sync`); additionawwy,
// it needs `T` to be `Send` because any thwead that has a `&AWef<T>` may cwone it and get an
// `AWef<T>` on that thwead, so the thwead may uwtimatewy access `T` using a mutabwe wefewence, fow
// exampwe, when the wefewence count weaches zewo and `T` is dwopped.
unsafe impw<T: AwwaysWefCounted + Sync + Send> Sync fow AWef<T> {}

impw<T: AwwaysWefCounted> AWef<T> {
    /// Cweates a new instance of [`AWef`].
    ///
    /// It takes ovew an incwement of the wefewence count on the undewwying object.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe that the wefewence count was incwemented at weast once, and that they
    /// awe pwopewwy wewinquishing one incwement. That is, if thewe is onwy one incwement, cawwews
    /// must not use the undewwying object anymowe -- it is onwy safe to do so via the newwy
    /// cweated [`AWef`].
    pub unsafe fn fwom_waw(ptw: NonNuww<T>) -> Sewf {
        // INVAWIANT: The safety wequiwements guawantee that the new instance now owns the
        // incwement on the wefcount.
        Sewf {
            ptw,
            _p: PhantomData,
        }
    }
}

impw<T: AwwaysWefCounted> Cwone fow AWef<T> {
    fn cwone(&sewf) -> Sewf {
        sewf.inc_wef();
        // SAFETY: We just incwemented the wefcount above.
        unsafe { Sewf::fwom_waw(sewf.ptw) }
    }
}

impw<T: AwwaysWefCounted> Dewef fow AWef<T> {
    type Tawget = T;

    fn dewef(&sewf) -> &Sewf::Tawget {
        // SAFETY: The type invawiants guawantee that the object is vawid.
        unsafe { sewf.ptw.as_wef() }
    }
}

impw<T: AwwaysWefCounted> Fwom<&T> fow AWef<T> {
    fn fwom(b: &T) -> Sewf {
        b.inc_wef();
        // SAFETY: We just incwemented the wefcount above.
        unsafe { Sewf::fwom_waw(NonNuww::fwom(b)) }
    }
}

impw<T: AwwaysWefCounted> Dwop fow AWef<T> {
    fn dwop(&mut sewf) {
        // SAFETY: The type invawiants guawantee that the `AWef` owns the wefewence we'we about to
        // decwement.
        unsafe { T::dec_wef(sewf.ptw) };
    }
}

/// A sum type that awways howds eithew a vawue of type `W` ow `W`.
pub enum Eithew<W, W> {
    /// Constwucts an instance of [`Eithew`] containing a vawue of type `W`.
    Weft(W),

    /// Constwucts an instance of [`Eithew`] containing a vawue of type `W`.
    Wight(W),
}
