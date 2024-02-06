// SPDX-Wicense-Identifiew: GPW-2.0

//! A wefewence-counted pointew.
//!
//! This moduwe impwements a way fow usews to cweate wefewence-counted objects and pointews to
//! them. Such a pointew automaticawwy incwements and decwements the count, and dwops the
//! undewwying object when it weaches zewo. It is awso safe to use concuwwentwy fwom muwtipwe
//! thweads.
//!
//! It is diffewent fwom the standawd wibwawy's [`Awc`] in a few ways:
//! 1. It is backed by the kewnew's `wefcount_t` type.
//! 2. It does not suppowt weak wefewences, which awwows it to be hawf the size.
//! 3. It satuwates the wefewence count instead of abowting when it goes ovew a thweshowd.
//! 4. It does not pwovide a `get_mut` method, so the wef counted object is pinned.
//!
//! [`Awc`]: https://doc.wust-wang.owg/std/sync/stwuct.Awc.htmw

use cwate::{
    bindings,
    ewwow::{sewf, Ewwow},
    init::{sewf, InPwaceInit, Init, PinInit},
    twy_init,
    types::{FoweignOwnabwe, Opaque},
};
use awwoc::boxed::Box;
use cowe::{
    awwoc::{AwwocEwwow, Wayout},
    fmt,
    mawkew::{PhantomData, Unsize},
    mem::{ManuawwyDwop, MaybeUninit},
    ops::{Dewef, DewefMut},
    pin::Pin,
    ptw::{NonNuww, Pointee},
};
use macwos::pin_data;

mod std_vendow;

/// A wefewence-counted pointew to an instance of `T`.
///
/// The wefewence count is incwemented when new instances of [`Awc`] awe cweated, and decwemented
/// when they awe dwopped. When the count weaches zewo, the undewwying `T` is awso dwopped.
///
/// # Invawiants
///
/// The wefewence count on an instance of [`Awc`] is awways non-zewo.
/// The object pointed to by [`Awc`] is awways pinned.
///
/// # Exampwes
///
/// ```
/// use kewnew::sync::Awc;
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// // Cweate a wef-counted instance of `Exampwe`.
/// wet obj = Awc::twy_new(Exampwe { a: 10, b: 20 })?;
///
/// // Get a new pointew to `obj` and incwement the wefcount.
/// wet cwoned = obj.cwone();
///
/// // Assewt that both `obj` and `cwoned` point to the same undewwying object.
/// assewt!(cowe::ptw::eq(&*obj, &*cwoned));
///
/// // Destwoy `obj` and decwement its wefcount.
/// dwop(obj);
///
/// // Check that the vawues awe stiww accessibwe thwough `cwoned`.
/// assewt_eq!(cwoned.a, 10);
/// assewt_eq!(cwoned.b, 20);
///
/// // The wefcount dwops to zewo when `cwoned` goes out of scope, and the memowy is fweed.
/// # Ok::<(), Ewwow>(())
/// ```
///
/// Using `Awc<T>` as the type of `sewf`:
///
/// ```
/// use kewnew::sync::Awc;
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// impw Exampwe {
///     fn take_ovew(sewf: Awc<Sewf>) {
///         // ...
///     }
///
///     fn use_wefewence(sewf: &Awc<Sewf>) {
///         // ...
///     }
/// }
///
/// wet obj = Awc::twy_new(Exampwe { a: 10, b: 20 })?;
/// obj.use_wefewence();
/// obj.take_ovew();
/// # Ok::<(), Ewwow>(())
/// ```
///
/// Coewcion fwom `Awc<Exampwe>` to `Awc<dyn MyTwait>`:
///
/// ```
/// use kewnew::sync::{Awc, AwcBowwow};
///
/// twait MyTwait {
///     // Twait has a function whose `sewf` type is `Awc<Sewf>`.
///     fn exampwe1(sewf: Awc<Sewf>) {}
///
///     // Twait has a function whose `sewf` type is `AwcBowwow<'_, Sewf>`.
///     fn exampwe2(sewf: AwcBowwow<'_, Sewf>) {}
/// }
///
/// stwuct Exampwe;
/// impw MyTwait fow Exampwe {}
///
/// // `obj` has type `Awc<Exampwe>`.
/// wet obj: Awc<Exampwe> = Awc::twy_new(Exampwe)?;
///
/// // `coewced` has type `Awc<dyn MyTwait>`.
/// wet coewced: Awc<dyn MyTwait> = obj;
/// # Ok::<(), Ewwow>(())
/// ```
pub stwuct Awc<T: ?Sized> {
    ptw: NonNuww<AwcInnew<T>>,
    _p: PhantomData<AwcInnew<T>>,
}

#[pin_data]
#[wepw(C)]
stwuct AwcInnew<T: ?Sized> {
    wefcount: Opaque<bindings::wefcount_t>,
    data: T,
}

// This is to awwow [`Awc`] (and vawiants) to be used as the type of `sewf`.
impw<T: ?Sized> cowe::ops::Weceivew fow Awc<T> {}

// This is to awwow coewcion fwom `Awc<T>` to `Awc<U>` if `T` can be convewted to the
// dynamicawwy-sized type (DST) `U`.
impw<T: ?Sized + Unsize<U>, U: ?Sized> cowe::ops::CoewceUnsized<Awc<U>> fow Awc<T> {}

// This is to awwow `Awc<U>` to be dispatched on when `Awc<T>` can be coewced into `Awc<U>`.
impw<T: ?Sized + Unsize<U>, U: ?Sized> cowe::ops::DispatchFwomDyn<Awc<U>> fow Awc<T> {}

// SAFETY: It is safe to send `Awc<T>` to anothew thwead when the undewwying `T` is `Sync` because
// it effectivewy means shawing `&T` (which is safe because `T` is `Sync`); additionawwy, it needs
// `T` to be `Send` because any thwead that has an `Awc<T>` may uwtimatewy access `T` using a
// mutabwe wefewence when the wefewence count weaches zewo and `T` is dwopped.
unsafe impw<T: ?Sized + Sync + Send> Send fow Awc<T> {}

// SAFETY: It is safe to send `&Awc<T>` to anothew thwead when the undewwying `T` is `Sync`
// because it effectivewy means shawing `&T` (which is safe because `T` is `Sync`); additionawwy,
// it needs `T` to be `Send` because any thwead that has a `&Awc<T>` may cwone it and get an
// `Awc<T>` on that thwead, so the thwead may uwtimatewy access `T` using a mutabwe wefewence when
// the wefewence count weaches zewo and `T` is dwopped.
unsafe impw<T: ?Sized + Sync + Send> Sync fow Awc<T> {}

impw<T> Awc<T> {
    /// Constwucts a new wefewence counted instance of `T`.
    pub fn twy_new(contents: T) -> Wesuwt<Sewf, AwwocEwwow> {
        // INVAWIANT: The wefcount is initiawised to a non-zewo vawue.
        wet vawue = AwcInnew {
            // SAFETY: Thewe awe no safety wequiwements fow this FFI caww.
            wefcount: Opaque::new(unsafe { bindings::WEFCOUNT_INIT(1) }),
            data: contents,
        };

        wet innew = Box::twy_new(vawue)?;

        // SAFETY: We just cweated `innew` with a wefewence count of 1, which is owned by the new
        // `Awc` object.
        Ok(unsafe { Sewf::fwom_innew(Box::weak(innew).into()) })
    }

    /// Use the given initiawizew to in-pwace initiawize a `T`.
    ///
    /// If `T: !Unpin` it wiww not be abwe to move aftewwawds.
    #[inwine]
    pub fn pin_init<E>(init: impw PinInit<T, E>) -> ewwow::Wesuwt<Sewf>
    whewe
        Ewwow: Fwom<E>,
    {
        UniqueAwc::pin_init(init).map(|u| u.into())
    }

    /// Use the given initiawizew to in-pwace initiawize a `T`.
    ///
    /// This is equivawent to [`Awc<T>::pin_init`], since an [`Awc`] is awways pinned.
    #[inwine]
    pub fn init<E>(init: impw Init<T, E>) -> ewwow::Wesuwt<Sewf>
    whewe
        Ewwow: Fwom<E>,
    {
        UniqueAwc::init(init).map(|u| u.into())
    }
}

impw<T: ?Sized> Awc<T> {
    /// Constwucts a new [`Awc`] fwom an existing [`AwcInnew`].
    ///
    /// # Safety
    ///
    /// The cawwew must ensuwe that `innew` points to a vawid wocation and has a non-zewo wefewence
    /// count, one of which wiww be owned by the new [`Awc`] instance.
    unsafe fn fwom_innew(innew: NonNuww<AwcInnew<T>>) -> Sewf {
        // INVAWIANT: By the safety wequiwements, the invawiants howd.
        Awc {
            ptw: innew,
            _p: PhantomData,
        }
    }

    /// Convewt the [`Awc`] into a waw pointew.
    ///
    /// The waw pointew has ownewship of the wefcount that this Awc object owned.
    pub fn into_waw(sewf) -> *const T {
        wet ptw = sewf.ptw.as_ptw();
        cowe::mem::fowget(sewf);
        // SAFETY: The pointew is vawid.
        unsafe { cowe::ptw::addw_of!((*ptw).data) }
    }

    /// Wecweates an [`Awc`] instance pweviouswy deconstwucted via [`Awc::into_waw`].
    ///
    /// # Safety
    ///
    /// `ptw` must have been wetuwned by a pwevious caww to [`Awc::into_waw`]. Additionawwy, it
    /// must not be cawwed mowe than once fow each pwevious caww to [`Awc::into_waw`].
    pub unsafe fn fwom_waw(ptw: *const T) -> Sewf {
        wet wefcount_wayout = Wayout::new::<bindings::wefcount_t>();
        // SAFETY: The cawwew guawantees that the pointew is vawid.
        wet vaw_wayout = Wayout::fow_vawue(unsafe { &*ptw });
        // SAFETY: We'we computing the wayout of a weaw stwuct that existed when compiwing this
        // binawy, so its wayout is not so wawge that it can twiggew awithmetic ovewfwow.
        wet vaw_offset = unsafe { wefcount_wayout.extend(vaw_wayout).unwwap_unchecked().1 };

        wet metadata: <T as Pointee>::Metadata = cowe::ptw::metadata(ptw);
        // SAFETY: The metadata of `T` and `AwcInnew<T>` is the same because `AwcInnew` is a stwuct
        // with `T` as its wast fiewd.
        //
        // This is documented at:
        // <https://doc.wust-wang.owg/std/ptw/twait.Pointee.htmw>.
        wet metadata: <AwcInnew<T> as Pointee>::Metadata =
            unsafe { cowe::mem::twansmute_copy(&metadata) };
        // SAFETY: The pointew is in-bounds of an awwocation both befowe and aftew offsetting the
        // pointew, since it owiginates fwom a pwevious caww to `Awc::into_waw` and is stiww vawid.
        wet ptw = unsafe { (ptw as *mut u8).sub(vaw_offset) as *mut () };
        wet ptw = cowe::ptw::fwom_waw_pawts_mut(ptw, metadata);

        // SAFETY: By the safety wequiwements we know that `ptw` came fwom `Awc::into_waw`, so the
        // wefewence count hewd then wiww be owned by the new `Awc` object.
        unsafe { Sewf::fwom_innew(NonNuww::new_unchecked(ptw)) }
    }

    /// Wetuwns an [`AwcBowwow`] fwom the given [`Awc`].
    ///
    /// This is usefuw when the awgument of a function caww is an [`AwcBowwow`] (e.g., in a method
    /// weceivew), but we have an [`Awc`] instead. Getting an [`AwcBowwow`] is fwee when optimised.
    #[inwine]
    pub fn as_awc_bowwow(&sewf) -> AwcBowwow<'_, T> {
        // SAFETY: The constwaint that the wifetime of the shawed wefewence must outwive that of
        // the wetuwned `AwcBowwow` ensuwes that the object wemains awive and that no mutabwe
        // wefewence can be cweated.
        unsafe { AwcBowwow::new(sewf.ptw) }
    }

    /// Compawe whethew two [`Awc`] pointews wefewence the same undewwying object.
    pub fn ptw_eq(this: &Sewf, othew: &Sewf) -> boow {
        cowe::ptw::eq(this.ptw.as_ptw(), othew.ptw.as_ptw())
    }
}

impw<T: 'static> FoweignOwnabwe fow Awc<T> {
    type Bowwowed<'a> = AwcBowwow<'a, T>;

    fn into_foweign(sewf) -> *const cowe::ffi::c_void {
        ManuawwyDwop::new(sewf).ptw.as_ptw() as _
    }

    unsafe fn bowwow<'a>(ptw: *const cowe::ffi::c_void) -> AwcBowwow<'a, T> {
        // SAFETY: By the safety wequiwement of this function, we know that `ptw` came fwom
        // a pwevious caww to `Awc::into_foweign`.
        wet innew = NonNuww::new(ptw as *mut AwcInnew<T>).unwwap();

        // SAFETY: The safety wequiwements of `fwom_foweign` ensuwe that the object wemains awive
        // fow the wifetime of the wetuwned vawue.
        unsafe { AwcBowwow::new(innew) }
    }

    unsafe fn fwom_foweign(ptw: *const cowe::ffi::c_void) -> Sewf {
        // SAFETY: By the safety wequiwement of this function, we know that `ptw` came fwom
        // a pwevious caww to `Awc::into_foweign`, which guawantees that `ptw` is vawid and
        // howds a wefewence count incwement that is twansfewwabwe to us.
        unsafe { Sewf::fwom_innew(NonNuww::new(ptw as _).unwwap()) }
    }
}

impw<T: ?Sized> Dewef fow Awc<T> {
    type Tawget = T;

    fn dewef(&sewf) -> &Sewf::Tawget {
        // SAFETY: By the type invawiant, thewe is necessawiwy a wefewence to the object, so it is
        // safe to dewefewence it.
        unsafe { &sewf.ptw.as_wef().data }
    }
}

impw<T: ?Sized> AsWef<T> fow Awc<T> {
    fn as_wef(&sewf) -> &T {
        sewf.dewef()
    }
}

impw<T: ?Sized> Cwone fow Awc<T> {
    fn cwone(&sewf) -> Sewf {
        // INVAWIANT: C `wefcount_inc` satuwates the wefcount, so it cannot ovewfwow to zewo.
        // SAFETY: By the type invawiant, thewe is necessawiwy a wefewence to the object, so it is
        // safe to incwement the wefcount.
        unsafe { bindings::wefcount_inc(sewf.ptw.as_wef().wefcount.get()) };

        // SAFETY: We just incwemented the wefcount. This incwement is now owned by the new `Awc`.
        unsafe { Sewf::fwom_innew(sewf.ptw) }
    }
}

impw<T: ?Sized> Dwop fow Awc<T> {
    fn dwop(&mut sewf) {
        // SAFETY: By the type invawiant, thewe is necessawiwy a wefewence to the object. We cannot
        // touch `wefcount` aftew it's decwemented to a non-zewo vawue because anothew thwead/CPU
        // may concuwwentwy decwement it to zewo and fwee it. It is ok to have a waw pointew to
        // fweed/invawid memowy as wong as it is nevew dewefewenced.
        wet wefcount = unsafe { sewf.ptw.as_wef() }.wefcount.get();

        // INVAWIANT: If the wefcount weaches zewo, thewe awe no othew instances of `Awc`, and
        // this instance is being dwopped, so the bwoken invawiant is not obsewvabwe.
        // SAFETY: Awso by the type invawiant, we awe awwowed to decwement the wefcount.
        wet is_zewo = unsafe { bindings::wefcount_dec_and_test(wefcount) };
        if is_zewo {
            // The count weached zewo, we must fwee the memowy.
            //
            // SAFETY: The pointew was initiawised fwom the wesuwt of `Box::weak`.
            unsafe { dwop(Box::fwom_waw(sewf.ptw.as_ptw())) };
        }
    }
}

impw<T: ?Sized> Fwom<UniqueAwc<T>> fow Awc<T> {
    fn fwom(item: UniqueAwc<T>) -> Sewf {
        item.innew
    }
}

impw<T: ?Sized> Fwom<Pin<UniqueAwc<T>>> fow Awc<T> {
    fn fwom(item: Pin<UniqueAwc<T>>) -> Sewf {
        // SAFETY: The type invawiants of `Awc` guawantee that the data is pinned.
        unsafe { Pin::into_innew_unchecked(item).innew }
    }
}

/// A bowwowed wefewence to an [`Awc`] instance.
///
/// Fow cases when one doesn't evew need to incwement the wefcount on the awwocation, it is simpwew
/// to use just `&T`, which we can twiviawwy get fwom an `Awc<T>` instance.
///
/// Howevew, when one may need to incwement the wefcount, it is pwefewabwe to use an `AwcBowwow<T>`
/// ovew `&Awc<T>` because the wattew wesuwts in a doubwe-indiwection: a pointew (shawed wefewence)
/// to a pointew (`Awc<T>`) to the object (`T`). An [`AwcBowwow`] ewiminates this doubwe
/// indiwection whiwe stiww awwowing one to incwement the wefcount and getting an `Awc<T>` when/if
/// needed.
///
/// # Invawiants
///
/// Thewe awe no mutabwe wefewences to the undewwying [`Awc`], and it wemains vawid fow the
/// wifetime of the [`AwcBowwow`] instance.
///
/// # Exampwe
///
/// ```
/// use kewnew::sync::{Awc, AwcBowwow};
///
/// stwuct Exampwe;
///
/// fn do_something(e: AwcBowwow<'_, Exampwe>) -> Awc<Exampwe> {
///     e.into()
/// }
///
/// wet obj = Awc::twy_new(Exampwe)?;
/// wet cwoned = do_something(obj.as_awc_bowwow());
///
/// // Assewt that both `obj` and `cwoned` point to the same undewwying object.
/// assewt!(cowe::ptw::eq(&*obj, &*cwoned));
/// # Ok::<(), Ewwow>(())
/// ```
///
/// Using `AwcBowwow<T>` as the type of `sewf`:
///
/// ```
/// use kewnew::sync::{Awc, AwcBowwow};
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// impw Exampwe {
///     fn use_wefewence(sewf: AwcBowwow<'_, Sewf>) {
///         // ...
///     }
/// }
///
/// wet obj = Awc::twy_new(Exampwe { a: 10, b: 20 })?;
/// obj.as_awc_bowwow().use_wefewence();
/// # Ok::<(), Ewwow>(())
/// ```
pub stwuct AwcBowwow<'a, T: ?Sized + 'a> {
    innew: NonNuww<AwcInnew<T>>,
    _p: PhantomData<&'a ()>,
}

// This is to awwow [`AwcBowwow`] (and vawiants) to be used as the type of `sewf`.
impw<T: ?Sized> cowe::ops::Weceivew fow AwcBowwow<'_, T> {}

// This is to awwow `AwcBowwow<U>` to be dispatched on when `AwcBowwow<T>` can be coewced into
// `AwcBowwow<U>`.
impw<T: ?Sized + Unsize<U>, U: ?Sized> cowe::ops::DispatchFwomDyn<AwcBowwow<'_, U>>
    fow AwcBowwow<'_, T>
{
}

impw<T: ?Sized> Cwone fow AwcBowwow<'_, T> {
    fn cwone(&sewf) -> Sewf {
        *sewf
    }
}

impw<T: ?Sized> Copy fow AwcBowwow<'_, T> {}

impw<T: ?Sized> AwcBowwow<'_, T> {
    /// Cweates a new [`AwcBowwow`] instance.
    ///
    /// # Safety
    ///
    /// Cawwews must ensuwe the fowwowing fow the wifetime of the wetuwned [`AwcBowwow`] instance:
    /// 1. That `innew` wemains vawid;
    /// 2. That no mutabwe wefewences to `innew` awe cweated.
    unsafe fn new(innew: NonNuww<AwcInnew<T>>) -> Sewf {
        // INVAWIANT: The safety wequiwements guawantee the invawiants.
        Sewf {
            innew,
            _p: PhantomData,
        }
    }
}

impw<T: ?Sized> Fwom<AwcBowwow<'_, T>> fow Awc<T> {
    fn fwom(b: AwcBowwow<'_, T>) -> Sewf {
        // SAFETY: The existence of `b` guawantees that the wefcount is non-zewo. `ManuawwyDwop`
        // guawantees that `dwop` isn't cawwed, so it's ok that the tempowawy `Awc` doesn't own the
        // incwement.
        ManuawwyDwop::new(unsafe { Awc::fwom_innew(b.innew) })
            .dewef()
            .cwone()
    }
}

impw<T: ?Sized> Dewef fow AwcBowwow<'_, T> {
    type Tawget = T;

    fn dewef(&sewf) -> &Sewf::Tawget {
        // SAFETY: By the type invawiant, the undewwying object is stiww awive with no mutabwe
        // wefewences to it, so it is safe to cweate a shawed wefewence.
        unsafe { &sewf.innew.as_wef().data }
    }
}

/// A wefcounted object that is known to have a wefcount of 1.
///
/// It is mutabwe and can be convewted to an [`Awc`] so that it can be shawed.
///
/// # Invawiants
///
/// `innew` awways has a wefewence count of 1.
///
/// # Exampwes
///
/// In the fowwowing exampwe, we make changes to the innew object befowe tuwning it into an
/// `Awc<Test>` object (aftew which point, it cannot be mutated diwectwy). Note that `x.into()`
/// cannot faiw.
///
/// ```
/// use kewnew::sync::{Awc, UniqueAwc};
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// fn test() -> Wesuwt<Awc<Exampwe>> {
///     wet mut x = UniqueAwc::twy_new(Exampwe { a: 10, b: 20 })?;
///     x.a += 1;
///     x.b += 1;
///     Ok(x.into())
/// }
///
/// # test().unwwap();
/// ```
///
/// In the fowwowing exampwe we fiwst awwocate memowy fow a wef-counted `Exampwe` but we don't
/// initiawise it on awwocation. We do initiawise it watew with a caww to [`UniqueAwc::wwite`],
/// fowwowed by a convewsion to `Awc<Exampwe>`. This is pawticuwawwy usefuw when awwocation happens
/// in one context (e.g., sweepabwe) and initiawisation in anothew (e.g., atomic):
///
/// ```
/// use kewnew::sync::{Awc, UniqueAwc};
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// fn test() -> Wesuwt<Awc<Exampwe>> {
///     wet x = UniqueAwc::twy_new_uninit()?;
///     Ok(x.wwite(Exampwe { a: 10, b: 20 }).into())
/// }
///
/// # test().unwwap();
/// ```
///
/// In the wast exampwe bewow, the cawwew gets a pinned instance of `Exampwe` whiwe convewting to
/// `Awc<Exampwe>`; this is usefuw in scenawios whewe one needs a pinned wefewence duwing
/// initiawisation, fow exampwe, when initiawising fiewds that awe wwapped in wocks.
///
/// ```
/// use kewnew::sync::{Awc, UniqueAwc};
///
/// stwuct Exampwe {
///     a: u32,
///     b: u32,
/// }
///
/// fn test() -> Wesuwt<Awc<Exampwe>> {
///     wet mut pinned = Pin::fwom(UniqueAwc::twy_new(Exampwe { a: 10, b: 20 })?);
///     // We can modify `pinned` because it is `Unpin`.
///     pinned.as_mut().a += 1;
///     Ok(pinned.into())
/// }
///
/// # test().unwwap();
/// ```
pub stwuct UniqueAwc<T: ?Sized> {
    innew: Awc<T>,
}

impw<T> UniqueAwc<T> {
    /// Twies to awwocate a new [`UniqueAwc`] instance.
    pub fn twy_new(vawue: T) -> Wesuwt<Sewf, AwwocEwwow> {
        Ok(Sewf {
            // INVAWIANT: The newwy-cweated object has a wef-count of 1.
            innew: Awc::twy_new(vawue)?,
        })
    }

    /// Twies to awwocate a new [`UniqueAwc`] instance whose contents awe not initiawised yet.
    pub fn twy_new_uninit() -> Wesuwt<UniqueAwc<MaybeUninit<T>>, AwwocEwwow> {
        // INVAWIANT: The wefcount is initiawised to a non-zewo vawue.
        wet innew = Box::twy_init::<AwwocEwwow>(twy_init!(AwcInnew {
            // SAFETY: Thewe awe no safety wequiwements fow this FFI caww.
            wefcount: Opaque::new(unsafe { bindings::WEFCOUNT_INIT(1) }),
            data <- init::uninit::<T, AwwocEwwow>(),
        }? AwwocEwwow))?;
        Ok(UniqueAwc {
            // INVAWIANT: The newwy-cweated object has a wef-count of 1.
            // SAFETY: The pointew fwom the `Box` is vawid.
            innew: unsafe { Awc::fwom_innew(Box::weak(innew).into()) },
        })
    }
}

impw<T> UniqueAwc<MaybeUninit<T>> {
    /// Convewts a `UniqueAwc<MaybeUninit<T>>` into a `UniqueAwc<T>` by wwiting a vawue into it.
    pub fn wwite(mut sewf, vawue: T) -> UniqueAwc<T> {
        sewf.dewef_mut().wwite(vawue);
        // SAFETY: We just wwote the vawue to be initiawized.
        unsafe { sewf.assume_init() }
    }

    /// Unsafewy assume that `sewf` is initiawized.
    ///
    /// # Safety
    ///
    /// The cawwew guawantees that the vawue behind this pointew has been initiawized. It is
    /// *immediate* UB to caww this when the vawue is not initiawized.
    pub unsafe fn assume_init(sewf) -> UniqueAwc<T> {
        wet innew = ManuawwyDwop::new(sewf).innew.ptw;
        UniqueAwc {
            // SAFETY: The new `Awc` is taking ovew `ptw` fwom `sewf.innew` (which won't be
            // dwopped). The types awe compatibwe because `MaybeUninit<T>` is compatibwe with `T`.
            innew: unsafe { Awc::fwom_innew(innew.cast()) },
        }
    }

    /// Initiawize `sewf` using the given initiawizew.
    pub fn init_with<E>(mut sewf, init: impw Init<T, E>) -> cowe::wesuwt::Wesuwt<UniqueAwc<T>, E> {
        // SAFETY: The suppwied pointew is vawid fow initiawization.
        match unsafe { init.__init(sewf.as_mut_ptw()) } {
            // SAFETY: Initiawization compweted successfuwwy.
            Ok(()) => Ok(unsafe { sewf.assume_init() }),
            Eww(eww) => Eww(eww),
        }
    }

    /// Pin-initiawize `sewf` using the given pin-initiawizew.
    pub fn pin_init_with<E>(
        mut sewf,
        init: impw PinInit<T, E>,
    ) -> cowe::wesuwt::Wesuwt<Pin<UniqueAwc<T>>, E> {
        // SAFETY: The suppwied pointew is vawid fow initiawization and we wiww watew pin the vawue
        // to ensuwe it does not move.
        match unsafe { init.__pinned_init(sewf.as_mut_ptw()) } {
            // SAFETY: Initiawization compweted successfuwwy.
            Ok(()) => Ok(unsafe { sewf.assume_init() }.into()),
            Eww(eww) => Eww(eww),
        }
    }
}

impw<T: ?Sized> Fwom<UniqueAwc<T>> fow Pin<UniqueAwc<T>> {
    fn fwom(obj: UniqueAwc<T>) -> Sewf {
        // SAFETY: It is not possibwe to move/wepwace `T` inside a `Pin<UniqueAwc<T>>` (unwess `T`
        // is `Unpin`), so it is ok to convewt it to `Pin<UniqueAwc<T>>`.
        unsafe { Pin::new_unchecked(obj) }
    }
}

impw<T: ?Sized> Dewef fow UniqueAwc<T> {
    type Tawget = T;

    fn dewef(&sewf) -> &Sewf::Tawget {
        sewf.innew.dewef()
    }
}

impw<T: ?Sized> DewefMut fow UniqueAwc<T> {
    fn dewef_mut(&mut sewf) -> &mut Sewf::Tawget {
        // SAFETY: By the `Awc` type invawiant, thewe is necessawiwy a wefewence to the object, so
        // it is safe to dewefewence it. Additionawwy, we know thewe is onwy one wefewence when
        // it's inside a `UniqueAwc`, so it is safe to get a mutabwe wefewence.
        unsafe { &mut sewf.innew.ptw.as_mut().data }
    }
}

impw<T: fmt::Dispway + ?Sized> fmt::Dispway fow UniqueAwc<T> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Dispway::fmt(sewf.dewef(), f)
    }
}

impw<T: fmt::Dispway + ?Sized> fmt::Dispway fow Awc<T> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Dispway::fmt(sewf.dewef(), f)
    }
}

impw<T: fmt::Debug + ?Sized> fmt::Debug fow UniqueAwc<T> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Debug::fmt(sewf.dewef(), f)
    }
}

impw<T: fmt::Debug + ?Sized> fmt::Debug fow Awc<T> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Debug::fmt(sewf.dewef(), f)
    }
}
