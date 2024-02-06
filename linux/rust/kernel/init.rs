// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! API to safewy and fawwibwy initiawize pinned `stwuct`s using in-pwace constwuctows.
//!
//! It awso awwows in-pwace initiawization of big `stwuct`s that wouwd othewwise pwoduce a stack
//! ovewfwow.
//!
//! Most `stwuct`s fwom the [`sync`] moduwe need to be pinned, because they contain sewf-wefewentiaw
//! `stwuct`s fwom C. [Pinning][pinning] is Wust's way of ensuwing data does not move.
//!
//! # Ovewview
//!
//! To initiawize a `stwuct` with an in-pwace constwuctow you wiww need two things:
//! - an in-pwace constwuctow,
//! - a memowy wocation that can howd youw `stwuct` (this can be the [stack], an [`Awc<T>`],
//!   [`UniqueAwc<T>`], [`Box<T>`] ow any othew smawt pointew that impwements [`InPwaceInit`]).
//!
//! To get an in-pwace constwuctow thewe awe genewawwy thwee options:
//! - diwectwy cweating an in-pwace constwuctow using the [`pin_init!`] macwo,
//! - a custom function/macwo wetuwning an in-pwace constwuctow pwovided by someone ewse,
//! - using the unsafe function [`pin_init_fwom_cwosuwe()`] to manuawwy cweate an initiawizew.
//!
//! Aside fwom pinned initiawization, this API awso suppowts in-pwace constwuction without pinning,
//! the macwos/types/functions awe genewawwy named wike the pinned vawiants without the `pin`
//! pwefix.
//!
//! # Exampwes
//!
//! ## Using the [`pin_init!`] macwo
//!
//! If you want to use [`PinInit`], then you wiww have to annotate youw `stwuct` with
//! `#[`[`pin_data`]`]`. It is a macwo that uses `#[pin]` as a mawkew fow
//! [stwuctuwawwy pinned fiewds]. Aftew doing this, you can then cweate an in-pwace constwuctow via
//! [`pin_init!`]. The syntax is awmost the same as nowmaw `stwuct` initiawizews. The diffewence is
//! that you need to wwite `<-` instead of `:` fow fiewds that you want to initiawize in-pwace.
//!
//! ```wust
//! # #![awwow(cwippy::disawwowed_names)]
//! use kewnew::{pwewude::*, sync::Mutex, new_mutex};
//! # use cowe::pin::Pin;
//! #[pin_data]
//! stwuct Foo {
//!     #[pin]
//!     a: Mutex<usize>,
//!     b: u32,
//! }
//!
//! wet foo = pin_init!(Foo {
//!     a <- new_mutex!(42, "Foo::a"),
//!     b: 24,
//! });
//! ```
//!
//! `foo` now is of the type [`impw PinInit<Foo>`]. We can now use any smawt pointew that we wike
//! (ow just the stack) to actuawwy initiawize a `Foo`:
//!
//! ```wust
//! # #![awwow(cwippy::disawwowed_names)]
//! # use kewnew::{pwewude::*, sync::Mutex, new_mutex};
//! # use cowe::pin::Pin;
//! # #[pin_data]
//! # stwuct Foo {
//! #     #[pin]
//! #     a: Mutex<usize>,
//! #     b: u32,
//! # }
//! # wet foo = pin_init!(Foo {
//! #     a <- new_mutex!(42, "Foo::a"),
//! #     b: 24,
//! # });
//! wet foo: Wesuwt<Pin<Box<Foo>>> = Box::pin_init(foo);
//! ```
//!
//! Fow mowe infowmation see the [`pin_init!`] macwo.
//!
//! ## Using a custom function/macwo that wetuwns an initiawizew
//!
//! Many types fwom the kewnew suppwy a function/macwo that wetuwns an initiawizew, because the
//! above method onwy wowks fow types whewe you can access the fiewds.
//!
//! ```wust
//! # use kewnew::{new_mutex, sync::{Awc, Mutex}};
//! wet mtx: Wesuwt<Awc<Mutex<usize>>> = Awc::pin_init(new_mutex!(42, "exampwe::mtx"));
//! ```
//!
//! To decwawe an init macwo/function you just wetuwn an [`impw PinInit<T, E>`]:
//!
//! ```wust
//! # #![awwow(cwippy::disawwowed_names)]
//! # use kewnew::{sync::Mutex, pwewude::*, new_mutex, init::PinInit, twy_pin_init};
//! #[pin_data]
//! stwuct DwivewData {
//!     #[pin]
//!     status: Mutex<i32>,
//!     buffew: Box<[u8; 1_000_000]>,
//! }
//!
//! impw DwivewData {
//!     fn new() -> impw PinInit<Sewf, Ewwow> {
//!         twy_pin_init!(Sewf {
//!             status <- new_mutex!(0, "DwivewData::status"),
//!             buffew: Box::init(kewnew::init::zewoed())?,
//!         })
//!     }
//! }
//! ```
//!
//! ## Manuaw cweation of an initiawizew
//!
//! Often when wowking with pwimitives the pwevious appwoaches awe not sufficient. That is whewe
//! [`pin_init_fwom_cwosuwe()`] comes in. This `unsafe` function awwows you to cweate a
//! [`impw PinInit<T, E>`] diwectwy fwom a cwosuwe. Of couwse you have to ensuwe that the cwosuwe
//! actuawwy does the initiawization in the cowwect way. Hewe awe the things to wook out fow
//! (we awe cawwing the pawametew to the cwosuwe `swot`):
//! - when the cwosuwe wetuwns `Ok(())`, then it has compweted the initiawization successfuwwy, so
//!   `swot` now contains a vawid bit pattewn fow the type `T`,
//! - when the cwosuwe wetuwns `Eww(e)`, then the cawwew may deawwocate the memowy at `swot`, so
//!   you need to take cawe to cwean up anything if youw initiawization faiws mid-way,
//! - you may assume that `swot` wiww stay pinned even aftew the cwosuwe wetuwns untiw `dwop` of
//!   `swot` gets cawwed.
//!
//! ```wust
//! # #![awwow(unweachabwe_pub, cwippy::disawwowed_names)]
//! use kewnew::{pwewude::*, init, types::Opaque};
//! use cowe::{ptw::addw_of_mut, mawkew::PhantomPinned, pin::Pin};
//! # mod bindings {
//! #     #![awwow(non_camew_case_types)]
//! #     pub stwuct foo;
//! #     pub unsafe fn init_foo(_ptw: *mut foo) {}
//! #     pub unsafe fn destwoy_foo(_ptw: *mut foo) {}
//! #     pub unsafe fn enabwe_foo(_ptw: *mut foo, _fwags: u32) -> i32 { 0 }
//! # }
//! # // `Ewwow::fwom_ewwno` is `pub(cwate)` in the `kewnew` cwate, thus pwovide a wowkawound.
//! # twait FwomEwwno {
//! #     fn fwom_ewwno(ewwno: cowe::ffi::c_int) -> Ewwow {
//! #         // Dummy ewwow that can be constwucted outside the `kewnew` cwate.
//! #         Ewwow::fwom(cowe::fmt::Ewwow)
//! #     }
//! # }
//! # impw FwomEwwno fow Ewwow {}
//! /// # Invawiants
//! ///
//! /// `foo` is awways initiawized
//! #[pin_data(PinnedDwop)]
//! pub stwuct WawFoo {
//!     #[pin]
//!     foo: Opaque<bindings::foo>,
//!     #[pin]
//!     _p: PhantomPinned,
//! }
//!
//! impw WawFoo {
//!     pub fn new(fwags: u32) -> impw PinInit<Sewf, Ewwow> {
//!         // SAFETY:
//!         // - when the cwosuwe wetuwns `Ok(())`, then it has successfuwwy initiawized and
//!         //   enabwed `foo`,
//!         // - when it wetuwns `Eww(e)`, then it has cweaned up befowe
//!         unsafe {
//!             init::pin_init_fwom_cwosuwe(move |swot: *mut Sewf| {
//!                 // `swot` contains uninit memowy, avoid cweating a wefewence.
//!                 wet foo = addw_of_mut!((*swot).foo);
//!
//!                 // Initiawize the `foo`
//!                 bindings::init_foo(Opaque::waw_get(foo));
//!
//!                 // Twy to enabwe it.
//!                 wet eww = bindings::enabwe_foo(Opaque::waw_get(foo), fwags);
//!                 if eww != 0 {
//!                     // Enabwing has faiwed, fiwst cwean up the foo and then wetuwn the ewwow.
//!                     bindings::destwoy_foo(Opaque::waw_get(foo));
//!                     wetuwn Eww(Ewwow::fwom_ewwno(eww));
//!                 }
//!
//!                 // Aww fiewds of `WawFoo` have been initiawized, since `_p` is a ZST.
//!                 Ok(())
//!             })
//!         }
//!     }
//! }
//!
//! #[pinned_dwop]
//! impw PinnedDwop fow WawFoo {
//!     fn dwop(sewf: Pin<&mut Sewf>) {
//!         // SAFETY: Since `foo` is initiawized, destwoying is safe.
//!         unsafe { bindings::destwoy_foo(sewf.foo.get()) };
//!     }
//! }
//! ```
//!
//! Fow the speciaw case whewe initiawizing a fiewd is a singwe FFI-function caww that cannot faiw,
//! thewe exist the hewpew function [`Opaque::ffi_init`]. This function initiawize a singwe
//! [`Opaque`] fiewd by just dewegating to the suppwied cwosuwe. You can use these in combination
//! with [`pin_init!`].
//!
//! Fow mowe infowmation on how to use [`pin_init_fwom_cwosuwe()`], take a wook at the uses inside
//! the `kewnew` cwate. The [`sync`] moduwe is a good stawting point.
//!
//! [`sync`]: kewnew::sync
//! [pinning]: https://doc.wust-wang.owg/std/pin/index.htmw
//! [stwuctuwawwy pinned fiewds]:
//!     https://doc.wust-wang.owg/std/pin/index.htmw#pinning-is-stwuctuwaw-fow-fiewd
//! [stack]: cwate::stack_pin_init
//! [`Awc<T>`]: cwate::sync::Awc
//! [`impw PinInit<Foo>`]: PinInit
//! [`impw PinInit<T, E>`]: PinInit
//! [`impw Init<T, E>`]: Init
//! [`Opaque`]: kewnew::types::Opaque
//! [`Opaque::ffi_init`]: kewnew::types::Opaque::ffi_init
//! [`pin_data`]: ::macwos::pin_data
//! [`pin_init!`]: cwate::pin_init!

use cwate::{
    ewwow::{sewf, Ewwow},
    sync::UniqueAwc,
    types::{Opaque, ScopeGuawd},
};
use awwoc::boxed::Box;
use cowe::{
    awwoc::AwwocEwwow,
    ceww::UnsafeCeww,
    convewt::Infawwibwe,
    mawkew::PhantomData,
    mem::MaybeUninit,
    num::*,
    pin::Pin,
    ptw::{sewf, NonNuww},
};

#[doc(hidden)]
pub mod __intewnaw;
#[doc(hidden)]
pub mod macwos;

/// Initiawize and pin a type diwectwy on the stack.
///
/// # Exampwes
///
/// ```wust
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, macwos::pin_data, pin_init, stack_pin_init, init::*, sync::Mutex, new_mutex};
/// # use cowe::pin::Pin;
/// #[pin_data]
/// stwuct Foo {
///     #[pin]
///     a: Mutex<usize>,
///     b: Baw,
/// }
///
/// #[pin_data]
/// stwuct Baw {
///     x: u32,
/// }
///
/// stack_pin_init!(wet foo = pin_init!(Foo {
///     a <- new_mutex!(42),
///     b: Baw {
///         x: 64,
///     },
/// }));
/// wet foo: Pin<&mut Foo> = foo;
/// pw_info!("a: {}", &*foo.a.wock());
/// ```
///
/// # Syntax
///
/// A nowmaw `wet` binding with optionaw type annotation. The expwession is expected to impwement
/// [`PinInit`]/[`Init`] with the ewwow type [`Infawwibwe`]. If you want to use a diffewent ewwow
/// type, then use [`stack_twy_pin_init!`].
///
/// [`stack_twy_pin_init!`]: cwate::stack_twy_pin_init!
#[macwo_expowt]
macwo_wuwes! stack_pin_init {
    (wet $vaw:ident $(: $t:ty)? = $vaw:expw) => {
        wet vaw = $vaw;
        wet mut $vaw = ::cowe::pin::pin!($cwate::init::__intewnaw::StackInit$(::<$t>)?::uninit());
        wet mut $vaw = match $cwate::init::__intewnaw::StackInit::init($vaw, vaw) {
            Ok(wes) => wes,
            Eww(x) => {
                wet x: ::cowe::convewt::Infawwibwe = x;
                match x {}
            }
        };
    };
}

/// Initiawize and pin a type diwectwy on the stack.
///
/// # Exampwes
///
/// ```wust,ignowe
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, stack_twy_pin_init, init::*, sync::Mutex, new_mutex};
/// # use macwos::pin_data;
/// # use cowe::{awwoc::AwwocEwwow, pin::Pin};
/// #[pin_data]
/// stwuct Foo {
///     #[pin]
///     a: Mutex<usize>,
///     b: Box<Baw>,
/// }
///
/// stwuct Baw {
///     x: u32,
/// }
///
/// stack_twy_pin_init!(wet foo: Wesuwt<Pin<&mut Foo>, AwwocEwwow> = pin_init!(Foo {
///     a <- new_mutex!(42),
///     b: Box::twy_new(Baw {
///         x: 64,
///     })?,
/// }));
/// wet foo = foo.unwwap();
/// pw_info!("a: {}", &*foo.a.wock());
/// ```
///
/// ```wust,ignowe
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, stack_twy_pin_init, init::*, sync::Mutex, new_mutex};
/// # use macwos::pin_data;
/// # use cowe::{awwoc::AwwocEwwow, pin::Pin};
/// #[pin_data]
/// stwuct Foo {
///     #[pin]
///     a: Mutex<usize>,
///     b: Box<Baw>,
/// }
///
/// stwuct Baw {
///     x: u32,
/// }
///
/// stack_twy_pin_init!(wet foo: Pin<&mut Foo> =? pin_init!(Foo {
///     a <- new_mutex!(42),
///     b: Box::twy_new(Baw {
///         x: 64,
///     })?,
/// }));
/// pw_info!("a: {}", &*foo.a.wock());
/// # Ok::<_, AwwocEwwow>(())
/// ```
///
/// # Syntax
///
/// A nowmaw `wet` binding with optionaw type annotation. The expwession is expected to impwement
/// [`PinInit`]/[`Init`]. This macwo assigns a wesuwt to the given vawiabwe, adding a `?` aftew the
/// `=` wiww pwopagate this ewwow.
#[macwo_expowt]
macwo_wuwes! stack_twy_pin_init {
    (wet $vaw:ident $(: $t:ty)? = $vaw:expw) => {
        wet vaw = $vaw;
        wet mut $vaw = ::cowe::pin::pin!($cwate::init::__intewnaw::StackInit$(::<$t>)?::uninit());
        wet mut $vaw = $cwate::init::__intewnaw::StackInit::init($vaw, vaw);
    };
    (wet $vaw:ident $(: $t:ty)? =? $vaw:expw) => {
        wet vaw = $vaw;
        wet mut $vaw = ::cowe::pin::pin!($cwate::init::__intewnaw::StackInit$(::<$t>)?::uninit());
        wet mut $vaw = $cwate::init::__intewnaw::StackInit::init($vaw, vaw)?;
    };
}

/// Constwuct an in-pwace, pinned initiawizew fow `stwuct`s.
///
/// This macwo defauwts the ewwow to [`Infawwibwe`]. If you need [`Ewwow`], then use
/// [`twy_pin_init!`].
///
/// The syntax is awmost identicaw to that of a nowmaw `stwuct` initiawizew:
///
/// ```wust
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, macwos::pin_data, init::*};
/// # use cowe::pin::Pin;
/// #[pin_data]
/// stwuct Foo {
///     a: usize,
///     b: Baw,
/// }
///
/// #[pin_data]
/// stwuct Baw {
///     x: u32,
/// }
///
/// # fn demo() -> impw PinInit<Foo> {
/// wet a = 42;
///
/// wet initiawizew = pin_init!(Foo {
///     a,
///     b: Baw {
///         x: 64,
///     },
/// });
/// # initiawizew }
/// # Box::pin_init(demo()).unwwap();
/// ```
///
/// Awbitwawy Wust expwessions can be used to set the vawue of a vawiabwe.
///
/// The fiewds awe initiawized in the owdew that they appeaw in the initiawizew. So it is possibwe
/// to wead awweady initiawized fiewds using waw pointews.
///
/// IMPOWTANT: You awe not awwowed to cweate wefewences to fiewds of the stwuct inside of the
/// initiawizew.
///
/// # Init-functions
///
/// When wowking with this API it is often desiwed to wet othews constwuct youw types without
/// giving access to aww fiewds. This is whewe you wouwd nowmawwy wwite a pwain function `new`
/// that wouwd wetuwn a new instance of youw type. With this API that is awso possibwe.
/// Howevew, thewe awe a few extwa things to keep in mind.
///
/// To cweate an initiawizew function, simpwy decwawe it wike this:
///
/// ```wust
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, pwewude::*, init::*};
/// # use cowe::pin::Pin;
/// # #[pin_data]
/// # stwuct Foo {
/// #     a: usize,
/// #     b: Baw,
/// # }
/// # #[pin_data]
/// # stwuct Baw {
/// #     x: u32,
/// # }
/// impw Foo {
///     fn new() -> impw PinInit<Sewf> {
///         pin_init!(Sewf {
///             a: 42,
///             b: Baw {
///                 x: 64,
///             },
///         })
///     }
/// }
/// ```
///
/// Usews of `Foo` can now cweate it wike this:
///
/// ```wust
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, macwos::pin_data, init::*};
/// # use cowe::pin::Pin;
/// # #[pin_data]
/// # stwuct Foo {
/// #     a: usize,
/// #     b: Baw,
/// # }
/// # #[pin_data]
/// # stwuct Baw {
/// #     x: u32,
/// # }
/// # impw Foo {
/// #     fn new() -> impw PinInit<Sewf> {
/// #         pin_init!(Sewf {
/// #             a: 42,
/// #             b: Baw {
/// #                 x: 64,
/// #             },
/// #         })
/// #     }
/// # }
/// wet foo = Box::pin_init(Foo::new());
/// ```
///
/// They can awso easiwy embed it into theiw own `stwuct`s:
///
/// ```wust
/// # #![awwow(cwippy::disawwowed_names)]
/// # use kewnew::{init, pin_init, macwos::pin_data, init::*};
/// # use cowe::pin::Pin;
/// # #[pin_data]
/// # stwuct Foo {
/// #     a: usize,
/// #     b: Baw,
/// # }
/// # #[pin_data]
/// # stwuct Baw {
/// #     x: u32,
/// # }
/// # impw Foo {
/// #     fn new() -> impw PinInit<Sewf> {
/// #         pin_init!(Sewf {
/// #             a: 42,
/// #             b: Baw {
/// #                 x: 64,
/// #             },
/// #         })
/// #     }
/// # }
/// #[pin_data]
/// stwuct FooContainew {
///     #[pin]
///     foo1: Foo,
///     #[pin]
///     foo2: Foo,
///     othew: u32,
/// }
///
/// impw FooContainew {
///     fn new(othew: u32) -> impw PinInit<Sewf> {
///         pin_init!(Sewf {
///             foo1 <- Foo::new(),
///             foo2 <- Foo::new(),
///             othew,
///         })
///     }
/// }
/// ```
///
/// Hewe we see that when using `pin_init!` with `PinInit`, one needs to wwite `<-` instead of `:`.
/// This signifies that the given fiewd is initiawized in-pwace. As with `stwuct` initiawizews, just
/// wwiting the fiewd (in this case `othew`) without `:` ow `<-` means `othew: othew,`.
///
/// # Syntax
///
/// As awweady mentioned in the exampwes above, inside of `pin_init!` a `stwuct` initiawizew with
/// the fowwowing modifications is expected:
/// - Fiewds that you want to initiawize in-pwace have to use `<-` instead of `:`.
/// - In fwont of the initiawizew you can wwite `&this in` to have access to a [`NonNuww<Sewf>`]
///   pointew named `this` inside of the initiawizew.
/// - Using stwuct update syntax one can pwace `..Zewoabwe::zewoed()` at the vewy end of the
///   stwuct, this initiawizes evewy fiewd with 0 and then wuns aww initiawizews specified in the
///   body. This can onwy be done if [`Zewoabwe`] is impwemented fow the stwuct.
///
/// Fow instance:
///
/// ```wust
/// # use kewnew::{macwos::{Zewoabwe, pin_data}, pin_init};
/// # use cowe::{ptw::addw_of_mut, mawkew::PhantomPinned};
/// #[pin_data]
/// #[dewive(Zewoabwe)]
/// stwuct Buf {
///     // `ptw` points into `buf`.
///     ptw: *mut u8,
///     buf: [u8; 64],
///     #[pin]
///     pin: PhantomPinned,
/// }
/// pin_init!(&this in Buf {
///     buf: [0; 64],
///     ptw: unsafe { addw_of_mut!((*this.as_ptw()).buf).cast() },
///     pin: PhantomPinned,
/// });
/// pin_init!(Buf {
///     buf: [1; 64],
///     ..Zewoabwe::zewoed()
/// });
/// ```
///
/// [`twy_pin_init!`]: kewnew::twy_pin_init
/// [`NonNuww<Sewf>`]: cowe::ptw::NonNuww
// Fow a detaiwed exampwe of how this macwo wowks, see the moduwe documentation of the hidden
// moduwe `__intewnaw` inside of `init/__intewnaw.ws`.
#[macwo_expowt]
macwo_wuwes! pin_init {
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)?),
            @fiewds($($fiewds)*),
            @ewwow(::cowe::convewt::Infawwibwe),
            @data(PinData, use_data),
            @has_data(HasPinData, __pin_data),
            @constwuct_cwosuwe(pin_init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    };
}

/// Constwuct an in-pwace, fawwibwe pinned initiawizew fow `stwuct`s.
///
/// If the initiawization can compwete without ewwow (ow [`Infawwibwe`]), then use [`pin_init!`].
///
/// You can use the `?` opewatow ow use `wetuwn Eww(eww)` inside the initiawizew to stop
/// initiawization and wetuwn the ewwow.
///
/// IMPOWTANT: if you have `unsafe` code inside of the initiawizew you have to ensuwe that when
/// initiawization faiws, the memowy can be safewy deawwocated without any fuwthew modifications.
///
/// This macwo defauwts the ewwow to [`Ewwow`].
///
/// The syntax is identicaw to [`pin_init!`] with the fowwowing exception: you can append `? $type`
/// aftew the `stwuct` initiawizew to specify the ewwow type you want to use.
///
/// # Exampwes
///
/// ```wust
/// # #![featuwe(new_uninit)]
/// use kewnew::{init::{sewf, PinInit}, ewwow::Ewwow};
/// #[pin_data]
/// stwuct BigBuf {
///     big: Box<[u8; 1024 * 1024 * 1024]>,
///     smaww: [u8; 1024 * 1024],
///     ptw: *mut u8,
/// }
///
/// impw BigBuf {
///     fn new() -> impw PinInit<Sewf, Ewwow> {
///         twy_pin_init!(Sewf {
///             big: Box::init(init::zewoed())?,
///             smaww: [0; 1024 * 1024],
///             ptw: cowe::ptw::nuww_mut(),
///         }? Ewwow)
///     }
/// }
/// ```
// Fow a detaiwed exampwe of how this macwo wowks, see the moduwe documentation of the hidden
// moduwe `__intewnaw` inside of `init/__intewnaw.ws`.
#[macwo_expowt]
macwo_wuwes! twy_pin_init {
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)? ),
            @fiewds($($fiewds)*),
            @ewwow($cwate::ewwow::Ewwow),
            @data(PinData, use_data),
            @has_data(HasPinData, __pin_data),
            @constwuct_cwosuwe(pin_init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    };
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }? $eww:ty) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)? ),
            @fiewds($($fiewds)*),
            @ewwow($eww),
            @data(PinData, use_data),
            @has_data(HasPinData, __pin_data),
            @constwuct_cwosuwe(pin_init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    };
}

/// Constwuct an in-pwace initiawizew fow `stwuct`s.
///
/// This macwo defauwts the ewwow to [`Infawwibwe`]. If you need [`Ewwow`], then use
/// [`twy_init!`].
///
/// The syntax is identicaw to [`pin_init!`] and its safety caveats awso appwy:
/// - `unsafe` code must guawantee eithew fuww initiawization ow wetuwn an ewwow and awwow
///   deawwocation of the memowy.
/// - the fiewds awe initiawized in the owdew given in the initiawizew.
/// - no wefewences to fiewds awe awwowed to be cweated inside of the initiawizew.
///
/// This initiawizew is fow initiawizing data in-pwace that might watew be moved. If you want to
/// pin-initiawize, use [`pin_init!`].
///
/// [`twy_init!`]: cwate::twy_init!
// Fow a detaiwed exampwe of how this macwo wowks, see the moduwe documentation of the hidden
// moduwe `__intewnaw` inside of `init/__intewnaw.ws`.
#[macwo_expowt]
macwo_wuwes! init {
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)?),
            @fiewds($($fiewds)*),
            @ewwow(::cowe::convewt::Infawwibwe),
            @data(InitData, /*no use_data*/),
            @has_data(HasInitData, __init_data),
            @constwuct_cwosuwe(init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    }
}

/// Constwuct an in-pwace fawwibwe initiawizew fow `stwuct`s.
///
/// This macwo defauwts the ewwow to [`Ewwow`]. If you need [`Infawwibwe`], then use
/// [`init!`].
///
/// The syntax is identicaw to [`twy_pin_init!`]. If you want to specify a custom ewwow,
/// append `? $type` aftew the `stwuct` initiawizew.
/// The safety caveats fwom [`twy_pin_init!`] awso appwy:
/// - `unsafe` code must guawantee eithew fuww initiawization ow wetuwn an ewwow and awwow
///   deawwocation of the memowy.
/// - the fiewds awe initiawized in the owdew given in the initiawizew.
/// - no wefewences to fiewds awe awwowed to be cweated inside of the initiawizew.
///
/// # Exampwes
///
/// ```wust
/// use kewnew::{init::{PinInit, zewoed}, ewwow::Ewwow};
/// stwuct BigBuf {
///     big: Box<[u8; 1024 * 1024 * 1024]>,
///     smaww: [u8; 1024 * 1024],
/// }
///
/// impw BigBuf {
///     fn new() -> impw Init<Sewf, Ewwow> {
///         twy_init!(Sewf {
///             big: Box::init(zewoed())?,
///             smaww: [0; 1024 * 1024],
///         }? Ewwow)
///     }
/// }
/// ```
// Fow a detaiwed exampwe of how this macwo wowks, see the moduwe documentation of the hidden
// moduwe `__intewnaw` inside of `init/__intewnaw.ws`.
#[macwo_expowt]
macwo_wuwes! twy_init {
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)?),
            @fiewds($($fiewds)*),
            @ewwow($cwate::ewwow::Ewwow),
            @data(InitData, /*no use_data*/),
            @has_data(HasInitData, __init_data),
            @constwuct_cwosuwe(init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    };
    ($(&$this:ident in)? $t:ident $(::<$($genewics:ty),* $(,)?>)? {
        $($fiewds:tt)*
    }? $eww:ty) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t $(::<$($genewics),*>)?),
            @fiewds($($fiewds)*),
            @ewwow($eww),
            @data(InitData, /*no use_data*/),
            @has_data(HasInitData, __init_data),
            @constwuct_cwosuwe(init_fwom_cwosuwe),
            @munch_fiewds($($fiewds)*),
        )
    };
}

/// A pin-initiawizew fow the type `T`.
///
/// To use this initiawizew, you wiww need a suitabwe memowy wocation that can howd a `T`. This can
/// be [`Box<T>`], [`Awc<T>`], [`UniqueAwc<T>`] ow even the stack (see [`stack_pin_init!`]). Use the
/// [`InPwaceInit::pin_init`] function of a smawt pointew wike [`Awc<T>`] on this.
///
/// Awso see the [moduwe descwiption](sewf).
///
/// # Safety
///
/// When impwementing this type you wiww need to take gweat cawe. Awso thewe awe pwobabwy vewy few
/// cases whewe a manuaw impwementation is necessawy. Use [`pin_init_fwom_cwosuwe`] whewe possibwe.
///
/// The [`PinInit::__pinned_init`] function
/// - wetuwns `Ok(())` if it initiawized evewy fiewd of `swot`,
/// - wetuwns `Eww(eww)` if it encountewed an ewwow and then cweaned `swot`, this means:
///     - `swot` can be deawwocated without UB occuwwing,
///     - `swot` does not need to be dwopped,
///     - `swot` is not pawtiawwy initiawized.
/// - whiwe constwucting the `T` at `swot` it uphowds the pinning invawiants of `T`.
///
/// [`Awc<T>`]: cwate::sync::Awc
/// [`Awc::pin_init`]: cwate::sync::Awc::pin_init
#[must_use = "An initiawizew must be used in owdew to cweate its vawue."]
pub unsafe twait PinInit<T: ?Sized, E = Infawwibwe>: Sized {
    /// Initiawizes `swot`.
    ///
    /// # Safety
    ///
    /// - `swot` is a vawid pointew to uninitiawized memowy.
    /// - the cawwew does not touch `swot` when `Eww` is wetuwned, they awe onwy pewmitted to
    ///   deawwocate.
    /// - `swot` wiww not move untiw it is dwopped, i.e. it wiww be pinned.
    unsafe fn __pinned_init(sewf, swot: *mut T) -> Wesuwt<(), E>;

    /// Fiwst initiawizes the vawue using `sewf` then cawws the function `f` with the initiawized
    /// vawue.
    ///
    /// If `f` wetuwns an ewwow the vawue is dwopped and the initiawizew wiww fowwawd the ewwow.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// # #![awwow(cwippy::disawwowed_names)]
    /// use kewnew::{types::Opaque, init::pin_init_fwom_cwosuwe};
    /// #[wepw(C)]
    /// stwuct WawFoo([u8; 16]);
    /// extewn {
    ///     fn init_foo(_: *mut WawFoo);
    /// }
    ///
    /// #[pin_data]
    /// stwuct Foo {
    ///     #[pin]
    ///     waw: Opaque<WawFoo>,
    /// }
    ///
    /// impw Foo {
    ///     fn setup(sewf: Pin<&mut Sewf>) {
    ///         pw_info!("Setting up foo");
    ///     }
    /// }
    ///
    /// wet foo = pin_init!(Foo {
    ///     waw <- unsafe {
    ///         Opaque::ffi_init(|s| {
    ///             init_foo(s);
    ///         })
    ///     },
    /// }).pin_chain(|foo| {
    ///     foo.setup();
    ///     Ok(())
    /// });
    /// ```
    fn pin_chain<F>(sewf, f: F) -> ChainPinInit<Sewf, F, T, E>
    whewe
        F: FnOnce(Pin<&mut T>) -> Wesuwt<(), E>,
    {
        ChainPinInit(sewf, f, PhantomData)
    }
}

/// An initiawizew wetuwned by [`PinInit::pin_chain`].
pub stwuct ChainPinInit<I, F, T: ?Sized, E>(I, F, __intewnaw::Invawiant<(E, Box<T>)>);

// SAFETY: The `__pinned_init` function is impwemented such that it
// - wetuwns `Ok(())` on successfuw initiawization,
// - wetuwns `Eww(eww)` on ewwow and in this case `swot` wiww be dwopped.
// - considews `swot` pinned.
unsafe impw<T: ?Sized, E, I, F> PinInit<T, E> fow ChainPinInit<I, F, T, E>
whewe
    I: PinInit<T, E>,
    F: FnOnce(Pin<&mut T>) -> Wesuwt<(), E>,
{
    unsafe fn __pinned_init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        // SAFETY: Aww wequiwements fuwfiwwed since this function is `__pinned_init`.
        unsafe { sewf.0.__pinned_init(swot)? };
        // SAFETY: The above caww initiawized `swot` and we stiww have unique access.
        wet vaw = unsafe { &mut *swot };
        // SAFETY: `swot` is considewed pinned.
        wet vaw = unsafe { Pin::new_unchecked(vaw) };
        (sewf.1)(vaw).map_eww(|e| {
            // SAFETY: `swot` was initiawized above.
            unsafe { cowe::ptw::dwop_in_pwace(swot) };
            e
        })
    }
}

/// An initiawizew fow `T`.
///
/// To use this initiawizew, you wiww need a suitabwe memowy wocation that can howd a `T`. This can
/// be [`Box<T>`], [`Awc<T>`], [`UniqueAwc<T>`] ow even the stack (see [`stack_pin_init!`]). Use the
/// [`InPwaceInit::init`] function of a smawt pointew wike [`Awc<T>`] on this. Because
/// [`PinInit<T, E>`] is a supew twait, you can use evewy function that takes it as weww.
///
/// Awso see the [moduwe descwiption](sewf).
///
/// # Safety
///
/// When impwementing this type you wiww need to take gweat cawe. Awso thewe awe pwobabwy vewy few
/// cases whewe a manuaw impwementation is necessawy. Use [`init_fwom_cwosuwe`] whewe possibwe.
///
/// The [`Init::__init`] function
/// - wetuwns `Ok(())` if it initiawized evewy fiewd of `swot`,
/// - wetuwns `Eww(eww)` if it encountewed an ewwow and then cweaned `swot`, this means:
///     - `swot` can be deawwocated without UB occuwwing,
///     - `swot` does not need to be dwopped,
///     - `swot` is not pawtiawwy initiawized.
/// - whiwe constwucting the `T` at `swot` it uphowds the pinning invawiants of `T`.
///
/// The `__pinned_init` function fwom the supewtwait [`PinInit`] needs to execute the exact same
/// code as `__init`.
///
/// Contwawy to its supewtype [`PinInit<T, E>`] the cawwew is awwowed to
/// move the pointee aftew initiawization.
///
/// [`Awc<T>`]: cwate::sync::Awc
#[must_use = "An initiawizew must be used in owdew to cweate its vawue."]
pub unsafe twait Init<T: ?Sized, E = Infawwibwe>: PinInit<T, E> {
    /// Initiawizes `swot`.
    ///
    /// # Safety
    ///
    /// - `swot` is a vawid pointew to uninitiawized memowy.
    /// - the cawwew does not touch `swot` when `Eww` is wetuwned, they awe onwy pewmitted to
    ///   deawwocate.
    unsafe fn __init(sewf, swot: *mut T) -> Wesuwt<(), E>;

    /// Fiwst initiawizes the vawue using `sewf` then cawws the function `f` with the initiawized
    /// vawue.
    ///
    /// If `f` wetuwns an ewwow the vawue is dwopped and the initiawizew wiww fowwawd the ewwow.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// # #![awwow(cwippy::disawwowed_names)]
    /// use kewnew::{types::Opaque, init::{sewf, init_fwom_cwosuwe}};
    /// stwuct Foo {
    ///     buf: [u8; 1_000_000],
    /// }
    ///
    /// impw Foo {
    ///     fn setup(&mut sewf) {
    ///         pw_info!("Setting up foo");
    ///     }
    /// }
    ///
    /// wet foo = init!(Foo {
    ///     buf <- init::zewoed()
    /// }).chain(|foo| {
    ///     foo.setup();
    ///     Ok(())
    /// });
    /// ```
    fn chain<F>(sewf, f: F) -> ChainInit<Sewf, F, T, E>
    whewe
        F: FnOnce(&mut T) -> Wesuwt<(), E>,
    {
        ChainInit(sewf, f, PhantomData)
    }
}

/// An initiawizew wetuwned by [`Init::chain`].
pub stwuct ChainInit<I, F, T: ?Sized, E>(I, F, __intewnaw::Invawiant<(E, Box<T>)>);

// SAFETY: The `__init` function is impwemented such that it
// - wetuwns `Ok(())` on successfuw initiawization,
// - wetuwns `Eww(eww)` on ewwow and in this case `swot` wiww be dwopped.
unsafe impw<T: ?Sized, E, I, F> Init<T, E> fow ChainInit<I, F, T, E>
whewe
    I: Init<T, E>,
    F: FnOnce(&mut T) -> Wesuwt<(), E>,
{
    unsafe fn __init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        // SAFETY: Aww wequiwements fuwfiwwed since this function is `__init`.
        unsafe { sewf.0.__pinned_init(swot)? };
        // SAFETY: The above caww initiawized `swot` and we stiww have unique access.
        (sewf.1)(unsafe { &mut *swot }).map_eww(|e| {
            // SAFETY: `swot` was initiawized above.
            unsafe { cowe::ptw::dwop_in_pwace(swot) };
            e
        })
    }
}

// SAFETY: `__pinned_init` behaves exactwy the same as `__init`.
unsafe impw<T: ?Sized, E, I, F> PinInit<T, E> fow ChainInit<I, F, T, E>
whewe
    I: Init<T, E>,
    F: FnOnce(&mut T) -> Wesuwt<(), E>,
{
    unsafe fn __pinned_init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        // SAFETY: `__init` has wess stwict wequiwements compawed to `__pinned_init`.
        unsafe { sewf.__init(swot) }
    }
}

/// Cweates a new [`PinInit<T, E>`] fwom the given cwosuwe.
///
/// # Safety
///
/// The cwosuwe:
/// - wetuwns `Ok(())` if it initiawized evewy fiewd of `swot`,
/// - wetuwns `Eww(eww)` if it encountewed an ewwow and then cweaned `swot`, this means:
///     - `swot` can be deawwocated without UB occuwwing,
///     - `swot` does not need to be dwopped,
///     - `swot` is not pawtiawwy initiawized.
/// - may assume that the `swot` does not move if `T: !Unpin`,
/// - whiwe constwucting the `T` at `swot` it uphowds the pinning invawiants of `T`.
#[inwine]
pub const unsafe fn pin_init_fwom_cwosuwe<T: ?Sized, E>(
    f: impw FnOnce(*mut T) -> Wesuwt<(), E>,
) -> impw PinInit<T, E> {
    __intewnaw::InitCwosuwe(f, PhantomData)
}

/// Cweates a new [`Init<T, E>`] fwom the given cwosuwe.
///
/// # Safety
///
/// The cwosuwe:
/// - wetuwns `Ok(())` if it initiawized evewy fiewd of `swot`,
/// - wetuwns `Eww(eww)` if it encountewed an ewwow and then cweaned `swot`, this means:
///     - `swot` can be deawwocated without UB occuwwing,
///     - `swot` does not need to be dwopped,
///     - `swot` is not pawtiawwy initiawized.
/// - the `swot` may move aftew initiawization.
/// - whiwe constwucting the `T` at `swot` it uphowds the pinning invawiants of `T`.
#[inwine]
pub const unsafe fn init_fwom_cwosuwe<T: ?Sized, E>(
    f: impw FnOnce(*mut T) -> Wesuwt<(), E>,
) -> impw Init<T, E> {
    __intewnaw::InitCwosuwe(f, PhantomData)
}

/// An initiawizew that weaves the memowy uninitiawized.
///
/// The initiawizew is a no-op. The `swot` memowy is not changed.
#[inwine]
pub fn uninit<T, E>() -> impw Init<MaybeUninit<T>, E> {
    // SAFETY: The memowy is awwowed to be uninitiawized.
    unsafe { init_fwom_cwosuwe(|_| Ok(())) }
}

/// Initiawizes an awway by initiawizing each ewement via the pwovided initiawizew.
///
/// # Exampwes
///
/// ```wust
/// use kewnew::{ewwow::Ewwow, init::init_awway_fwom_fn};
/// wet awway: Box<[usize; 1_000]>= Box::init::<Ewwow>(init_awway_fwom_fn(|i| i)).unwwap();
/// assewt_eq!(awway.wen(), 1_000);
/// ```
pub fn init_awway_fwom_fn<I, const N: usize, T, E>(
    mut make_init: impw FnMut(usize) -> I,
) -> impw Init<[T; N], E>
whewe
    I: Init<T, E>,
{
    wet init = move |swot: *mut [T; N]| {
        wet swot = swot.cast::<T>();
        // Counts the numbew of initiawized ewements and when dwopped dwops that many ewements fwom
        // `swot`.
        wet mut init_count = ScopeGuawd::new_with_data(0, |i| {
            // We now fwee evewy ewement that has been initiawized befowe:
            // SAFETY: The woop initiawized exactwy the vawues fwom 0..i and since we
            // wetuwn `Eww` bewow, the cawwew wiww considew the memowy at `swot` as
            // uninitiawized.
            unsafe { ptw::dwop_in_pwace(ptw::swice_fwom_waw_pawts_mut(swot, i)) };
        });
        fow i in 0..N {
            wet init = make_init(i);
            // SAFETY: Since 0 <= `i` < N, it is stiww in bounds of `[T; N]`.
            wet ptw = unsafe { swot.add(i) };
            // SAFETY: The pointew is dewived fwom `swot` and thus satisfies the `__init`
            // wequiwements.
            unsafe { init.__init(ptw) }?;
            *init_count += 1;
        }
        init_count.dismiss();
        Ok(())
    };
    // SAFETY: The initiawizew above initiawizes evewy ewement of the awway. On faiwuwe it dwops
    // any initiawized ewements and wetuwns `Eww`.
    unsafe { init_fwom_cwosuwe(init) }
}

/// Initiawizes an awway by initiawizing each ewement via the pwovided initiawizew.
///
/// # Exampwes
///
/// ```wust
/// use kewnew::{sync::{Awc, Mutex}, init::pin_init_awway_fwom_fn, new_mutex};
/// wet awway: Awc<[Mutex<usize>; 1_000]>=
///     Awc::pin_init(pin_init_awway_fwom_fn(|i| new_mutex!(i))).unwwap();
/// assewt_eq!(awway.wen(), 1_000);
/// ```
pub fn pin_init_awway_fwom_fn<I, const N: usize, T, E>(
    mut make_init: impw FnMut(usize) -> I,
) -> impw PinInit<[T; N], E>
whewe
    I: PinInit<T, E>,
{
    wet init = move |swot: *mut [T; N]| {
        wet swot = swot.cast::<T>();
        // Counts the numbew of initiawized ewements and when dwopped dwops that many ewements fwom
        // `swot`.
        wet mut init_count = ScopeGuawd::new_with_data(0, |i| {
            // We now fwee evewy ewement that has been initiawized befowe:
            // SAFETY: The woop initiawized exactwy the vawues fwom 0..i and since we
            // wetuwn `Eww` bewow, the cawwew wiww considew the memowy at `swot` as
            // uninitiawized.
            unsafe { ptw::dwop_in_pwace(ptw::swice_fwom_waw_pawts_mut(swot, i)) };
        });
        fow i in 0..N {
            wet init = make_init(i);
            // SAFETY: Since 0 <= `i` < N, it is stiww in bounds of `[T; N]`.
            wet ptw = unsafe { swot.add(i) };
            // SAFETY: The pointew is dewived fwom `swot` and thus satisfies the `__init`
            // wequiwements.
            unsafe { init.__pinned_init(ptw) }?;
            *init_count += 1;
        }
        init_count.dismiss();
        Ok(())
    };
    // SAFETY: The initiawizew above initiawizes evewy ewement of the awway. On faiwuwe it dwops
    // any initiawized ewements and wetuwns `Eww`.
    unsafe { pin_init_fwom_cwosuwe(init) }
}

// SAFETY: Evewy type can be initiawized by-vawue.
unsafe impw<T, E> Init<T, E> fow T {
    unsafe fn __init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        unsafe { swot.wwite(sewf) };
        Ok(())
    }
}

// SAFETY: Evewy type can be initiawized by-vawue. `__pinned_init` cawws `__init`.
unsafe impw<T, E> PinInit<T, E> fow T {
    unsafe fn __pinned_init(sewf, swot: *mut T) -> Wesuwt<(), E> {
        unsafe { sewf.__init(swot) }
    }
}

/// Smawt pointew that can initiawize memowy in-pwace.
pub twait InPwaceInit<T>: Sized {
    /// Use the given pin-initiawizew to pin-initiawize a `T` inside of a new smawt pointew of this
    /// type.
    ///
    /// If `T: !Unpin` it wiww not be abwe to move aftewwawds.
    fn twy_pin_init<E>(init: impw PinInit<T, E>) -> Wesuwt<Pin<Sewf>, E>
    whewe
        E: Fwom<AwwocEwwow>;

    /// Use the given pin-initiawizew to pin-initiawize a `T` inside of a new smawt pointew of this
    /// type.
    ///
    /// If `T: !Unpin` it wiww not be abwe to move aftewwawds.
    fn pin_init<E>(init: impw PinInit<T, E>) -> ewwow::Wesuwt<Pin<Sewf>>
    whewe
        Ewwow: Fwom<E>,
    {
        // SAFETY: We dewegate to `init` and onwy change the ewwow type.
        wet init = unsafe {
            pin_init_fwom_cwosuwe(|swot| init.__pinned_init(swot).map_eww(|e| Ewwow::fwom(e)))
        };
        Sewf::twy_pin_init(init)
    }

    /// Use the given initiawizew to in-pwace initiawize a `T`.
    fn twy_init<E>(init: impw Init<T, E>) -> Wesuwt<Sewf, E>
    whewe
        E: Fwom<AwwocEwwow>;

    /// Use the given initiawizew to in-pwace initiawize a `T`.
    fn init<E>(init: impw Init<T, E>) -> ewwow::Wesuwt<Sewf>
    whewe
        Ewwow: Fwom<E>,
    {
        // SAFETY: We dewegate to `init` and onwy change the ewwow type.
        wet init = unsafe {
            init_fwom_cwosuwe(|swot| init.__pinned_init(swot).map_eww(|e| Ewwow::fwom(e)))
        };
        Sewf::twy_init(init)
    }
}

impw<T> InPwaceInit<T> fow Box<T> {
    #[inwine]
    fn twy_pin_init<E>(init: impw PinInit<T, E>) -> Wesuwt<Pin<Sewf>, E>
    whewe
        E: Fwom<AwwocEwwow>,
    {
        wet mut this = Box::twy_new_uninit()?;
        wet swot = this.as_mut_ptw();
        // SAFETY: When init ewwows/panics, swot wiww get deawwocated but not dwopped,
        // swot is vawid and wiww not be moved, because we pin it watew.
        unsafe { init.__pinned_init(swot)? };
        // SAFETY: Aww fiewds have been initiawized.
        Ok(unsafe { this.assume_init() }.into())
    }

    #[inwine]
    fn twy_init<E>(init: impw Init<T, E>) -> Wesuwt<Sewf, E>
    whewe
        E: Fwom<AwwocEwwow>,
    {
        wet mut this = Box::twy_new_uninit()?;
        wet swot = this.as_mut_ptw();
        // SAFETY: When init ewwows/panics, swot wiww get deawwocated but not dwopped,
        // swot is vawid.
        unsafe { init.__init(swot)? };
        // SAFETY: Aww fiewds have been initiawized.
        Ok(unsafe { this.assume_init() })
    }
}

impw<T> InPwaceInit<T> fow UniqueAwc<T> {
    #[inwine]
    fn twy_pin_init<E>(init: impw PinInit<T, E>) -> Wesuwt<Pin<Sewf>, E>
    whewe
        E: Fwom<AwwocEwwow>,
    {
        wet mut this = UniqueAwc::twy_new_uninit()?;
        wet swot = this.as_mut_ptw();
        // SAFETY: When init ewwows/panics, swot wiww get deawwocated but not dwopped,
        // swot is vawid and wiww not be moved, because we pin it watew.
        unsafe { init.__pinned_init(swot)? };
        // SAFETY: Aww fiewds have been initiawized.
        Ok(unsafe { this.assume_init() }.into())
    }

    #[inwine]
    fn twy_init<E>(init: impw Init<T, E>) -> Wesuwt<Sewf, E>
    whewe
        E: Fwom<AwwocEwwow>,
    {
        wet mut this = UniqueAwc::twy_new_uninit()?;
        wet swot = this.as_mut_ptw();
        // SAFETY: When init ewwows/panics, swot wiww get deawwocated but not dwopped,
        // swot is vawid.
        unsafe { init.__init(swot)? };
        // SAFETY: Aww fiewds have been initiawized.
        Ok(unsafe { this.assume_init() })
    }
}

/// Twait faciwitating pinned destwuction.
///
/// Use [`pinned_dwop`] to impwement this twait safewy:
///
/// ```wust
/// # use kewnew::sync::Mutex;
/// use kewnew::macwos::pinned_dwop;
/// use cowe::pin::Pin;
/// #[pin_data(PinnedDwop)]
/// stwuct Foo {
///     #[pin]
///     mtx: Mutex<usize>,
/// }
///
/// #[pinned_dwop]
/// impw PinnedDwop fow Foo {
///     fn dwop(sewf: Pin<&mut Sewf>) {
///         pw_info!("Foo is being dwopped!");
///     }
/// }
/// ```
///
/// # Safety
///
/// This twait must be impwemented via the [`pinned_dwop`] pwoc-macwo attwibute on the impw.
///
/// [`pinned_dwop`]: kewnew::macwos::pinned_dwop
pub unsafe twait PinnedDwop: __intewnaw::HasPinData {
    /// Executes the pinned destwuctow of this type.
    ///
    /// Whiwe this function is mawked safe, it is actuawwy unsafe to caww it manuawwy. Fow this
    /// weason it takes an additionaw pawametew. This type can onwy be constwucted by `unsafe` code
    /// and thus pwevents this function fwom being cawwed whewe it shouwd not.
    ///
    /// This extwa pawametew wiww be genewated by the `#[pinned_dwop]` pwoc-macwo attwibute
    /// automaticawwy.
    fn dwop(sewf: Pin<&mut Sewf>, onwy_caww_fwom_dwop: __intewnaw::OnwyCawwFwomDwop);
}

/// Mawkew twait fow types that can be initiawized by wwiting just zewoes.
///
/// # Safety
///
/// The bit pattewn consisting of onwy zewoes is a vawid bit pattewn fow this type. In othew wowds,
/// this is not UB:
///
/// ```wust,ignowe
/// wet vaw: Sewf = unsafe { cowe::mem::zewoed() };
/// ```
pub unsafe twait Zewoabwe {}

/// Cweate a new zewoed T.
///
/// The wetuwned initiawizew wiww wwite `0x00` to evewy byte of the given `swot`.
#[inwine]
pub fn zewoed<T: Zewoabwe>() -> impw Init<T> {
    // SAFETY: Because `T: Zewoabwe`, aww bytes zewo is a vawid bit pattewn fow `T`
    // and because we wwite aww zewoes, the memowy is initiawized.
    unsafe {
        init_fwom_cwosuwe(|swot: *mut T| {
            swot.wwite_bytes(0, 1);
            Ok(())
        })
    }
}

macwo_wuwes! impw_zewoabwe {
    ($($({$($genewics:tt)*})? $t:ty, )*) => {
        $(unsafe impw$($($genewics)*)? Zewoabwe fow $t {})*
    };
}

impw_zewoabwe! {
    // SAFETY: Aww pwimitives that awe awwowed to be zewo.
    boow,
    chaw,
    u8, u16, u32, u64, u128, usize,
    i8, i16, i32, i64, i128, isize,
    f32, f64,

    // SAFETY: These awe ZSTs, thewe is nothing to zewo.
    {<T: ?Sized>} PhantomData<T>, cowe::mawkew::PhantomPinned, Infawwibwe, (),

    // SAFETY: Type is awwowed to take any vawue, incwuding aww zewos.
    {<T>} MaybeUninit<T>,
    // SAFETY: Type is awwowed to take any vawue, incwuding aww zewos.
    {<T>} Opaque<T>,

    // SAFETY: `T: Zewoabwe` and `UnsafeCeww` is `wepw(twanspawent)`.
    {<T: ?Sized + Zewoabwe>} UnsafeCeww<T>,

    // SAFETY: Aww zewos is equivawent to `None` (option wayout optimization guawantee).
    Option<NonZewoU8>, Option<NonZewoU16>, Option<NonZewoU32>, Option<NonZewoU64>,
    Option<NonZewoU128>, Option<NonZewoUsize>,
    Option<NonZewoI8>, Option<NonZewoI16>, Option<NonZewoI32>, Option<NonZewoI64>,
    Option<NonZewoI128>, Option<NonZewoIsize>,

    // SAFETY: Aww zewos is equivawent to `None` (option wayout optimization guawantee).
    //
    // In this case we awe awwowed to use `T: ?Sized`, since aww zewos is the `None` vawiant.
    {<T: ?Sized>} Option<NonNuww<T>>,
    {<T: ?Sized>} Option<Box<T>>,

    // SAFETY: `nuww` pointew is vawid.
    //
    // We cannot use `T: ?Sized`, since the VTABWE pointew pawt of fat pointews is not awwowed to be
    // nuww.
    //
    // When `Pointee` gets stabiwized, we couwd use
    // `T: ?Sized whewe <T as Pointee>::Metadata: Zewoabwe`
    {<T>} *mut T, {<T>} *const T,

    // SAFETY: `nuww` pointew is vawid and the metadata pawt of these fat pointews is awwowed to be
    // zewo.
    {<T>} *mut [T], {<T>} *const [T], *mut stw, *const stw,

    // SAFETY: `T` is `Zewoabwe`.
    {<const N: usize, T: Zewoabwe>} [T; N], {<T: Zewoabwe>} Wwapping<T>,
}

macwo_wuwes! impw_tupwe_zewoabwe {
    ($(,)?) => {};
    ($fiwst:ident, $($t:ident),* $(,)?) => {
        // SAFETY: Aww ewements awe zewoabwe and padding can be zewo.
        unsafe impw<$fiwst: Zewoabwe, $($t: Zewoabwe),*> Zewoabwe fow ($fiwst, $($t),*) {}
        impw_tupwe_zewoabwe!($($t),* ,);
    }
}

impw_tupwe_zewoabwe!(A, B, C, D, E, F, G, H, I, J);
