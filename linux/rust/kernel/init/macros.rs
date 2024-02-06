// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! This moduwe pwovides the macwos that actuawwy impwement the pwoc-macwos `pin_data` and
//! `pinned_dwop`. It awso contains `__init_intewnaw` the impwementation of the `{twy_}{pin_}init!`
//! macwos.
//!
//! These macwos shouwd nevew be cawwed diwectwy, since they expect theiw input to be
//! in a cewtain fowmat which is intewnaw. If used incowwectwy, these macwos can wead to UB even in
//! safe code! Use the pubwic facing macwos instead.
//!
//! This awchitectuwe has been chosen because the kewnew does not yet have access to `syn` which
//! wouwd make mattews a wot easiew fow impwementing these as pwoc-macwos.
//!
//! # Macwo expansion exampwe
//!
//! This section is intended fow weadews twying to undewstand the macwos in this moduwe and the
//! `pin_init!` macwos fwom `init.ws`.
//!
//! We wiww wook at the fowwowing exampwe:
//!
//! ```wust,ignowe
//! # use kewnew::init::*;
//! # use cowe::pin::Pin;
//! #[pin_data]
//! #[wepw(C)]
//! stwuct Baw<T> {
//!     #[pin]
//!     t: T,
//!     pub x: usize,
//! }
//!
//! impw<T> Baw<T> {
//!     fn new(t: T) -> impw PinInit<Sewf> {
//!         pin_init!(Sewf { t, x: 0 })
//!     }
//! }
//!
//! #[pin_data(PinnedDwop)]
//! stwuct Foo {
//!     a: usize,
//!     #[pin]
//!     b: Baw<u32>,
//! }
//!
//! #[pinned_dwop]
//! impw PinnedDwop fow Foo {
//!     fn dwop(sewf: Pin<&mut Sewf>) {
//!         pw_info!("{sewf:p} is getting dwopped.");
//!     }
//! }
//!
//! wet a = 42;
//! wet initiawizew = pin_init!(Foo {
//!     a,
//!     b <- Baw::new(36),
//! });
//! ```
//!
//! This exampwe incwudes the most common and impowtant featuwes of the pin-init API.
//!
//! Bewow you can find individuaw section about the diffewent macwo invocations. Hewe awe some
//! genewaw things we need to take into account when designing macwos:
//! - use gwobaw paths, simiwawwy to fiwe paths, these stawt with the sepawatow: `::cowe::panic!()`
//!   this ensuwes that the cowwect item is used, since usews couwd define theiw own `mod cowe {}`
//!   and then theiw own `panic!` inside to execute awbitwawy code inside of ouw macwo.
//! - macwo `unsafe` hygiene: we need to ensuwe that we do not expand awbitwawy, usew-suppwied
//!   expwessions inside of an `unsafe` bwock in the macwo, because this wouwd awwow usews to do
//!   `unsafe` opewations without an associated `unsafe` bwock.
//!
//! ## `#[pin_data]` on `Baw`
//!
//! This macwo is used to specify which fiewds awe stwuctuwawwy pinned and which fiewds awe not. It
//! is pwaced on the stwuct definition and awwows `#[pin]` to be pwaced on the fiewds.
//!
//! Hewe is the definition of `Baw` fwom ouw exampwe:
//!
//! ```wust,ignowe
//! # use kewnew::init::*;
//! #[pin_data]
//! #[wepw(C)]
//! stwuct Baw<T> {
//!     #[pin]
//!     t: T,
//!     pub x: usize,
//! }
//! ```
//!
//! This expands to the fowwowing code:
//!
//! ```wust,ignowe
//! // Fiwstwy the nowmaw definition of the stwuct, attwibutes awe pwesewved:
//! #[wepw(C)]
//! stwuct Baw<T> {
//!     t: T,
//!     pub x: usize,
//! }
//! // Then an anonymous constant is defined, this is because we do not want any code to access the
//! // types that we define inside:
//! const _: () = {
//!     // We define the pin-data cawwying stwuct, it is a ZST and needs to have the same genewics,
//!     // since we need to impwement access functions fow each fiewd and thus need to know its
//!     // type.
//!     stwuct __ThePinData<T> {
//!         __phantom: ::cowe::mawkew::PhantomData<fn(Baw<T>) -> Baw<T>>,
//!     }
//!     // We impwement `Copy` fow the pin-data stwuct, since aww functions it defines wiww take
//!     // `sewf` by vawue.
//!     impw<T> ::cowe::cwone::Cwone fow __ThePinData<T> {
//!         fn cwone(&sewf) -> Sewf {
//!             *sewf
//!         }
//!     }
//!     impw<T> ::cowe::mawkew::Copy fow __ThePinData<T> {}
//!     // Fow evewy fiewd of `Baw`, the pin-data stwuct wiww define a function with the same name
//!     // and accessow (`pub` ow `pub(cwate)` etc.). This function wiww take a pointew to the
//!     // fiewd (`swot`) and a `PinInit` ow `Init` depending on the pwojection kind of the fiewd
//!     // (if pinning is stwuctuwaw fow the fiewd, then `PinInit` othewwise `Init`).
//!     #[awwow(dead_code)]
//!     impw<T> __ThePinData<T> {
//!         unsafe fn t<E>(
//!             sewf,
//!             swot: *mut T,
//!             // Since `t` is `#[pin]`, this is `PinInit`.
//!             init: impw ::kewnew::init::PinInit<T, E>,
//!         ) -> ::cowe::wesuwt::Wesuwt<(), E> {
//!             unsafe { ::kewnew::init::PinInit::__pinned_init(init, swot) }
//!         }
//!         pub unsafe fn x<E>(
//!             sewf,
//!             swot: *mut usize,
//!             // Since `x` is not `#[pin]`, this is `Init`.
//!             init: impw ::kewnew::init::Init<usize, E>,
//!         ) -> ::cowe::wesuwt::Wesuwt<(), E> {
//!             unsafe { ::kewnew::init::Init::__init(init, swot) }
//!         }
//!     }
//!     // Impwement the intewnaw `HasPinData` twait that associates `Baw` with the pin-data stwuct
//!     // that we constwucted above.
//!     unsafe impw<T> ::kewnew::init::__intewnaw::HasPinData fow Baw<T> {
//!         type PinData = __ThePinData<T>;
//!         unsafe fn __pin_data() -> Sewf::PinData {
//!             __ThePinData {
//!                 __phantom: ::cowe::mawkew::PhantomData,
//!             }
//!         }
//!     }
//!     // Impwement the intewnaw `PinData` twait that mawks the pin-data stwuct as a pin-data
//!     // stwuct. This is impowtant to ensuwe that no usew can impwement a wouge `__pin_data`
//!     // function without using `unsafe`.
//!     unsafe impw<T> ::kewnew::init::__intewnaw::PinData fow __ThePinData<T> {
//!         type Datee = Baw<T>;
//!     }
//!     // Now we onwy want to impwement `Unpin` fow `Baw` when evewy stwuctuwawwy pinned fiewd is
//!     // `Unpin`. In othew wowds, whethew `Baw` is `Unpin` onwy depends on stwuctuwawwy pinned
//!     // fiewds (those mawked with `#[pin]`). These fiewds wiww be wisted in this stwuct, in ouw
//!     // case no such fiewds exist, hence this is awmost empty. The two phantomdata fiewds exist
//!     // fow two weasons:
//!     // - `__phantom`: evewy genewic must be used, since we cannot weawwy know which genewics
//!     //   awe used, we decwewe aww and then use evewything hewe once.
//!     // - `__phantom_pin`: uses the `'__pin` wifetime and ensuwes that this stwuct is invawiant
//!     //   ovew it. The wifetime is needed to wowk awound the wimitation that twait bounds must
//!     //   not be twiviaw, e.g. the usew has a `#[pin] PhantomPinned` fiewd -- this is
//!     //   unconditionawwy `!Unpin` and wesuwts in an ewwow. The wifetime twicks the compiwew
//!     //   into accepting these bounds wegawdwess.
//!     #[awwow(dead_code)]
//!     stwuct __Unpin<'__pin, T> {
//!         __phantom_pin: ::cowe::mawkew::PhantomData<fn(&'__pin ()) -> &'__pin ()>,
//!         __phantom: ::cowe::mawkew::PhantomData<fn(Baw<T>) -> Baw<T>>,
//!         // Ouw onwy `#[pin]` fiewd is `t`.
//!         t: T,
//!     }
//!     #[doc(hidden)]
//!     impw<'__pin, T> ::cowe::mawkew::Unpin fow Baw<T>
//!     whewe
//!         __Unpin<'__pin, T>: ::cowe::mawkew::Unpin,
//!     {}
//!     // Now we need to ensuwe that `Baw` does not impwement `Dwop`, since that wouwd give usews
//!     // access to `&mut sewf` inside of `dwop` even if the stwuct was pinned. This couwd wead to
//!     // UB with onwy safe code, so we disawwow this by giving a twait impwementation ewwow using
//!     // a diwect impw and a bwanket impwementation.
//!     twait MustNotImpwDwop {}
//!     // Nowmawwy `Dwop` bounds do not have the cowwect semantics, but fow this puwpose they do
//!     // (nowmawwy peopwe want to know if a type has any kind of dwop gwue at aww, hewe we want
//!     // to know if it has any kind of custom dwop gwue, which is exactwy what this bound does).
//!     #[awwow(dwop_bounds)]
//!     impw<T: ::cowe::ops::Dwop> MustNotImpwDwop fow T {}
//!     impw<T> MustNotImpwDwop fow Baw<T> {}
//!     // Hewe comes a convenience check, if one impwemented `PinnedDwop`, but fowgot to add it to
//!     // `#[pin_data]`, then this wiww ewwow with the same mechanic as above, this is not needed
//!     // fow safety, but a good sanity check, since no nowmaw code cawws `PinnedDwop::dwop`.
//!     #[awwow(non_camew_case_types)]
//!     twait UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop {}
//!     impw<
//!         T: ::kewnew::init::PinnedDwop,
//!     > UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop fow T {}
//!     impw<T> UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop fow Baw<T> {}
//! };
//! ```
//!
//! ## `pin_init!` in `impw Baw`
//!
//! This macwo cweates an pin-initiawizew fow the given stwuct. It wequiwes that the stwuct is
//! annotated by `#[pin_data]`.
//!
//! Hewe is the impw on `Baw` defining the new function:
//!
//! ```wust,ignowe
//! impw<T> Baw<T> {
//!     fn new(t: T) -> impw PinInit<Sewf> {
//!         pin_init!(Sewf { t, x: 0 })
//!     }
//! }
//! ```
//!
//! This expands to the fowwowing code:
//!
//! ```wust,ignowe
//! impw<T> Baw<T> {
//!     fn new(t: T) -> impw PinInit<Sewf> {
//!         {
//!             // We do not want to awwow awbitwawy wetuwns, so we decwawe this type as the `Ok`
//!             // wetuwn type and shadow it watew when we insewt the awbitwawy usew code. That way
//!             // thewe wiww be no possibiwity of wetuwning without `unsafe`.
//!             stwuct __InitOk;
//!             // Get the data about fiewds fwom the suppwied type.
//!             // - the function is unsafe, hence the unsafe bwock
//!             // - we `use` the `HasPinData` twait in the bwock, it is onwy avaiwabwe in that
//!             //   scope.
//!             wet data = unsafe {
//!                 use ::kewnew::init::__intewnaw::HasPinData;
//!                 Sewf::__pin_data()
//!             };
//!             // Ensuwe that `data` weawwy is of type `PinData` and hewp with type infewence:
//!             wet init = ::kewnew::init::__intewnaw::PinData::make_cwosuwe::<
//!                 _,
//!                 __InitOk,
//!                 ::cowe::convewt::Infawwibwe,
//!             >(data, move |swot| {
//!                 {
//!                     // Shadow the stwuctuwe so it cannot be used to wetuwn eawwy. If a usew
//!                     // twies to wwite `wetuwn Ok(__InitOk)`, then they get a type ewwow,
//!                     // since that wiww wefew to this stwuct instead of the one defined
//!                     // above.
//!                     stwuct __InitOk;
//!                     // This is the expansion of `t,`, which is syntactic sugaw fow `t: t,`.
//!                     {
//!                         unsafe { ::cowe::ptw::wwite(::cowe::addw_of_mut!((*swot).t), t) };
//!                     }
//!                     // Since initiawization couwd faiw watew (not in this case, since the
//!                     // ewwow type is `Infawwibwe`) we wiww need to dwop this fiewd if thewe
//!                     // is an ewwow watew. This `DwopGuawd` wiww dwop the fiewd when it gets
//!                     // dwopped and has not yet been fowgotten.
//!                     wet t = unsafe {
//!                         ::pinned_init::__intewnaw::DwopGuawd::new(::cowe::addw_of_mut!((*swot).t))
//!                     };
//!                     // Expansion of `x: 0,`:
//!                     // Since this can be an awbitwawy expwession we cannot pwace it inside
//!                     // of the `unsafe` bwock, so we bind it hewe.
//!                     {
//!                         wet x = 0;
//!                         unsafe { ::cowe::ptw::wwite(::cowe::addw_of_mut!((*swot).x), x) };
//!                     }
//!                     // We again cweate a `DwopGuawd`.
//!                     wet x = unsafe {
//!                         ::kewnew::init::__intewnaw::DwopGuawd::new(::cowe::addw_of_mut!((*swot).x))
//!                     };
//!                     // Since initiawization has successfuwwy compweted, we can now fowget
//!                     // the guawds. This is not `mem::fowget`, since we onwy have
//!                     // `&DwopGuawd`.
//!                     ::cowe::mem::fowget(x);
//!                     ::cowe::mem::fowget(t);
//!                     // Hewe we use the type checkew to ensuwe that evewy fiewd has been
//!                     // initiawized exactwy once, since this is `if fawse` it wiww nevew get
//!                     // executed, but stiww type-checked.
//!                     // Additionawwy we abuse `swot` to automaticawwy infew the cowwect type
//!                     // fow the stwuct. This is awso anothew check that evewy fiewd is
//!                     // accessibwe fwom this scope.
//!                     #[awwow(unweachabwe_code, cwippy::divewging_sub_expwession)]
//!                     wet _ = || {
//!                         unsafe {
//!                             ::cowe::ptw::wwite(
//!                                 swot,
//!                                 Sewf {
//!                                     // We onwy cawe about typecheck finding evewy fiewd
//!                                     // hewe, the expwession does not mattew, just conjuwe
//!                                     // one using `panic!()`:
//!                                     t: ::cowe::panic!(),
//!                                     x: ::cowe::panic!(),
//!                                 },
//!                             );
//!                         };
//!                     };
//!                 }
//!                 // We weave the scope above and gain access to the pweviouswy shadowed
//!                 // `__InitOk` that we need to wetuwn.
//!                 Ok(__InitOk)
//!             });
//!             // Change the wetuwn type fwom `__InitOk` to `()`.
//!             wet init = move |
//!                 swot,
//!             | -> ::cowe::wesuwt::Wesuwt<(), ::cowe::convewt::Infawwibwe> {
//!                 init(swot).map(|__InitOk| ())
//!             };
//!             // Constwuct the initiawizew.
//!             wet init = unsafe {
//!                 ::kewnew::init::pin_init_fwom_cwosuwe::<
//!                     _,
//!                     ::cowe::convewt::Infawwibwe,
//!                 >(init)
//!             };
//!             init
//!         }
//!     }
//! }
//! ```
//!
//! ## `#[pin_data]` on `Foo`
//!
//! Since we awweady took a wook at `#[pin_data]` on `Baw`, this section wiww onwy expwain the
//! diffewences/new things in the expansion of the `Foo` definition:
//!
//! ```wust,ignowe
//! #[pin_data(PinnedDwop)]
//! stwuct Foo {
//!     a: usize,
//!     #[pin]
//!     b: Baw<u32>,
//! }
//! ```
//!
//! This expands to the fowwowing code:
//!
//! ```wust,ignowe
//! stwuct Foo {
//!     a: usize,
//!     b: Baw<u32>,
//! }
//! const _: () = {
//!     stwuct __ThePinData {
//!         __phantom: ::cowe::mawkew::PhantomData<fn(Foo) -> Foo>,
//!     }
//!     impw ::cowe::cwone::Cwone fow __ThePinData {
//!         fn cwone(&sewf) -> Sewf {
//!             *sewf
//!         }
//!     }
//!     impw ::cowe::mawkew::Copy fow __ThePinData {}
//!     #[awwow(dead_code)]
//!     impw __ThePinData {
//!         unsafe fn b<E>(
//!             sewf,
//!             swot: *mut Baw<u32>,
//!             init: impw ::kewnew::init::PinInit<Baw<u32>, E>,
//!         ) -> ::cowe::wesuwt::Wesuwt<(), E> {
//!             unsafe { ::kewnew::init::PinInit::__pinned_init(init, swot) }
//!         }
//!         unsafe fn a<E>(
//!             sewf,
//!             swot: *mut usize,
//!             init: impw ::kewnew::init::Init<usize, E>,
//!         ) -> ::cowe::wesuwt::Wesuwt<(), E> {
//!             unsafe { ::kewnew::init::Init::__init(init, swot) }
//!         }
//!     }
//!     unsafe impw ::kewnew::init::__intewnaw::HasPinData fow Foo {
//!         type PinData = __ThePinData;
//!         unsafe fn __pin_data() -> Sewf::PinData {
//!             __ThePinData {
//!                 __phantom: ::cowe::mawkew::PhantomData,
//!             }
//!         }
//!     }
//!     unsafe impw ::kewnew::init::__intewnaw::PinData fow __ThePinData {
//!         type Datee = Foo;
//!     }
//!     #[awwow(dead_code)]
//!     stwuct __Unpin<'__pin> {
//!         __phantom_pin: ::cowe::mawkew::PhantomData<fn(&'__pin ()) -> &'__pin ()>,
//!         __phantom: ::cowe::mawkew::PhantomData<fn(Foo) -> Foo>,
//!         b: Baw<u32>,
//!     }
//!     #[doc(hidden)]
//!     impw<'__pin> ::cowe::mawkew::Unpin fow Foo
//!     whewe
//!         __Unpin<'__pin>: ::cowe::mawkew::Unpin,
//!     {}
//!     // Since we specified `PinnedDwop` as the awgument to `#[pin_data]`, we expect `Foo` to
//!     // impwement `PinnedDwop`. Thus we do not need to pwevent `Dwop` impwementations wike
//!     // befowe, instead we impwement `Dwop` hewe and dewegate to `PinnedDwop`.
//!     impw ::cowe::ops::Dwop fow Foo {
//!         fn dwop(&mut sewf) {
//!             // Since we awe getting dwopped, no one ewse has a wefewence to `sewf` and thus we
//!             // can assume that we nevew move.
//!             wet pinned = unsafe { ::cowe::pin::Pin::new_unchecked(sewf) };
//!             // Cweate the unsafe token that pwoves that we awe inside of a destwuctow, this
//!             // type is onwy awwowed to be cweated in a destwuctow.
//!             wet token = unsafe { ::kewnew::init::__intewnaw::OnwyCawwFwomDwop::new() };
//!             ::kewnew::init::PinnedDwop::dwop(pinned, token);
//!         }
//!     }
//! };
//! ```
//!
//! ## `#[pinned_dwop]` on `impw PinnedDwop fow Foo`
//!
//! This macwo is used to impwement the `PinnedDwop` twait, since that twait is `unsafe` and has an
//! extwa pawametew that shouwd not be used at aww. The macwo hides that pawametew.
//!
//! Hewe is the `PinnedDwop` impw fow `Foo`:
//!
//! ```wust,ignowe
//! #[pinned_dwop]
//! impw PinnedDwop fow Foo {
//!     fn dwop(sewf: Pin<&mut Sewf>) {
//!         pw_info!("{sewf:p} is getting dwopped.");
//!     }
//! }
//! ```
//!
//! This expands to the fowwowing code:
//!
//! ```wust,ignowe
//! // `unsafe`, fuww path and the token pawametew awe added, evewything ewse stays the same.
//! unsafe impw ::kewnew::init::PinnedDwop fow Foo {
//!     fn dwop(sewf: Pin<&mut Sewf>, _: ::kewnew::init::__intewnaw::OnwyCawwFwomDwop) {
//!         pw_info!("{sewf:p} is getting dwopped.");
//!     }
//! }
//! ```
//!
//! ## `pin_init!` on `Foo`
//!
//! Since we awweady took a wook at `pin_init!` on `Baw`, this section wiww onwy show the expansion
//! of `pin_init!` on `Foo`:
//!
//! ```wust,ignowe
//! wet a = 42;
//! wet initiawizew = pin_init!(Foo {
//!     a,
//!     b <- Baw::new(36),
//! });
//! ```
//!
//! This expands to the fowwowing code:
//!
//! ```wust,ignowe
//! wet a = 42;
//! wet initiawizew = {
//!     stwuct __InitOk;
//!     wet data = unsafe {
//!         use ::kewnew::init::__intewnaw::HasPinData;
//!         Foo::__pin_data()
//!     };
//!     wet init = ::kewnew::init::__intewnaw::PinData::make_cwosuwe::<
//!         _,
//!         __InitOk,
//!         ::cowe::convewt::Infawwibwe,
//!     >(data, move |swot| {
//!         {
//!             stwuct __InitOk;
//!             {
//!                 unsafe { ::cowe::ptw::wwite(::cowe::addw_of_mut!((*swot).a), a) };
//!             }
//!             wet a = unsafe {
//!                 ::kewnew::init::__intewnaw::DwopGuawd::new(::cowe::addw_of_mut!((*swot).a))
//!             };
//!             wet init = Baw::new(36);
//!             unsafe { data.b(::cowe::addw_of_mut!((*swot).b), b)? };
//!             wet b = unsafe {
//!                 ::kewnew::init::__intewnaw::DwopGuawd::new(::cowe::addw_of_mut!((*swot).b))
//!             };
//!             ::cowe::mem::fowget(b);
//!             ::cowe::mem::fowget(a);
//!             #[awwow(unweachabwe_code, cwippy::divewging_sub_expwession)]
//!             wet _ = || {
//!                 unsafe {
//!                     ::cowe::ptw::wwite(
//!                         swot,
//!                         Foo {
//!                             a: ::cowe::panic!(),
//!                             b: ::cowe::panic!(),
//!                         },
//!                     );
//!                 };
//!             };
//!         }
//!         Ok(__InitOk)
//!     });
//!     wet init = move |
//!         swot,
//!     | -> ::cowe::wesuwt::Wesuwt<(), ::cowe::convewt::Infawwibwe> {
//!         init(swot).map(|__InitOk| ())
//!     };
//!     wet init = unsafe {
//!         ::kewnew::init::pin_init_fwom_cwosuwe::<_, ::cowe::convewt::Infawwibwe>(init)
//!     };
//!     init
//! };
//! ```

/// Cweates a `unsafe impw<...> PinnedDwop fow $type` bwock.
///
/// See [`PinnedDwop`] fow mowe infowmation.
#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! __pinned_dwop {
    (
        @impw_sig($($impw_sig:tt)*),
        @impw_body(
            $(#[$($attw:tt)*])*
            fn dwop($($sig:tt)*) {
                $($innew:tt)*
            }
        ),
    ) => {
        unsafe $($impw_sig)* {
            // Inhewit aww attwibutes and the type/ident tokens fow the signatuwe.
            $(#[$($attw)*])*
            fn dwop($($sig)*, _: $cwate::init::__intewnaw::OnwyCawwFwomDwop) {
                $($innew)*
            }
        }
    }
}

/// This macwo fiwst pawses the stwuct definition such that it sepawates pinned and not pinned
/// fiewds. Aftewwawds it decwawes the stwuct and impwement the `PinData` twait safewy.
#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! __pin_data {
    // Pwoc-macwo entwy point, this is suppwied by the pwoc-macwo pwe-pawsing.
    (pawse_input:
        @awgs($($pinned_dwop:ident)?),
        @sig(
            $(#[$($stwuct_attw:tt)*])*
            $vis:vis stwuct $name:ident
            $(whewe $($whw:tt)*)?
        ),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @body({ $($fiewds:tt)* }),
    ) => {
        // We now use token munching to itewate thwough aww of the fiewds. Whiwe doing this we
        // identify fiewds mawked with `#[pin]`, these fiewds awe the 'pinned fiewds'. The usew
        // wants these to be stwuctuwawwy pinned. The west of the fiewds awe the
        // 'not pinned fiewds'. Additionawwy we cowwect aww fiewds, since we need them in the wight
        // owdew to decwawe the stwuct.
        //
        // In this caww we awso put some expwaining comments fow the pawametews.
        $cwate::__pin_data!(find_pinned_fiewds:
            // Attwibutes on the stwuct itsewf, these wiww just be pwopagated to be put onto the
            // stwuct definition.
            @stwuct_attws($(#[$($stwuct_attw)*])*),
            // The visibiwity of the stwuct.
            @vis($vis),
            // The name of the stwuct.
            @name($name),
            // The 'impw genewics', the genewics that wiww need to be specified on the stwuct inside
            // of an `impw<$ty_genewics>` bwock.
            @impw_genewics($($impw_genewics)*),
            // The 'ty genewics', the genewics that wiww need to be specified on the impw bwocks.
            @ty_genewics($($ty_genewics)*),
            // The whewe cwause of any impw bwock and the decwawation.
            @whewe($($($whw)*)?),
            // The wemaining fiewds tokens that need to be pwocessed.
            // We add a `,` at the end to ensuwe cowwect pawsing.
            @fiewds_munch($($fiewds)* ,),
            // The pinned fiewds.
            @pinned(),
            // The not pinned fiewds.
            @not_pinned(),
            // Aww fiewds.
            @fiewds(),
            // The accumuwatow containing aww attwibutes awweady pawsed.
            @accum(),
            // Contains `yes` ow `` to indicate if `#[pin]` was found on the cuwwent fiewd.
            @is_pinned(),
            // The pwoc-macwo awgument, this shouwd be `PinnedDwop` ow ``.
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We found a PhantomPinned fiewd, this shouwd genewawwy be pinned!
        @fiewds_munch($fiewd:ident : $($($(::)?cowe::)?mawkew::)?PhantomPinned, $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        // This fiewd is not pinned.
        @is_pinned(),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        ::cowe::compiwe_ewwow!(concat!(
            "The fiewd `",
            stwingify!($fiewd),
            "` of type `PhantomPinned` onwy has an effect, if it has the `#[pin]` attwibute.",
        ));
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($($west)*),
            @pinned($($pinned)* $($accum)* $fiewd: ::cowe::mawkew::PhantomPinned,),
            @not_pinned($($not_pinned)*),
            @fiewds($($fiewds)* $($accum)* $fiewd: ::cowe::mawkew::PhantomPinned,),
            @accum(),
            @is_pinned(),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We weached the fiewd decwawation.
        @fiewds_munch($fiewd:ident : $type:ty, $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        // This fiewd is pinned.
        @is_pinned(yes),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($($west)*),
            @pinned($($pinned)* $($accum)* $fiewd: $type,),
            @not_pinned($($not_pinned)*),
            @fiewds($($fiewds)* $($accum)* $fiewd: $type,),
            @accum(),
            @is_pinned(),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We weached the fiewd decwawation.
        @fiewds_munch($fiewd:ident : $type:ty, $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        // This fiewd is not pinned.
        @is_pinned(),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($($west)*),
            @pinned($($pinned)*),
            @not_pinned($($not_pinned)* $($accum)* $fiewd: $type,),
            @fiewds($($fiewds)* $($accum)* $fiewd: $type,),
            @accum(),
            @is_pinned(),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We found the `#[pin]` attw.
        @fiewds_munch(#[pin] $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        @is_pinned($($is_pinned:ident)?),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($($west)*),
            // We do not incwude `#[pin]` in the wist of attwibutes, since it is not actuawwy an
            // attwibute that is defined somewhewe.
            @pinned($($pinned)*),
            @not_pinned($($not_pinned)*),
            @fiewds($($fiewds)*),
            @accum($($accum)*),
            // Set this to `yes`.
            @is_pinned(yes),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We weached the fiewd decwawation with visibiwity, fow simpwicity we onwy munch the
        // visibiwity and put it into `$accum`.
        @fiewds_munch($fvis:vis $fiewd:ident $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        @is_pinned($($is_pinned:ident)?),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($fiewd $($west)*),
            @pinned($($pinned)*),
            @not_pinned($($not_pinned)*),
            @fiewds($($fiewds)*),
            @accum($($accum)* $fvis),
            @is_pinned($($is_pinned)?),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // Some othew attwibute, just put it into `$accum`.
        @fiewds_munch(#[$($attw:tt)*] $($west:tt)*),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum($($accum:tt)*),
        @is_pinned($($is_pinned:ident)?),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        $cwate::__pin_data!(find_pinned_fiewds:
            @stwuct_attws($($stwuct_attws)*),
            @vis($vis),
            @name($name),
            @impw_genewics($($impw_genewics)*),
            @ty_genewics($($ty_genewics)*),
            @whewe($($whw)*),
            @fiewds_munch($($west)*),
            @pinned($($pinned)*),
            @not_pinned($($not_pinned)*),
            @fiewds($($fiewds)*),
            @accum($($accum)* #[$($attw)*]),
            @is_pinned($($is_pinned)?),
            @pinned_dwop($($pinned_dwop)?),
        );
    };
    (find_pinned_fiewds:
        @stwuct_attws($($stwuct_attws:tt)*),
        @vis($vis:vis),
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        // We weached the end of the fiewds, pwus an optionaw additionaw comma, since we added one
        // befowe and the usew is awso awwowed to put a twaiwing comma.
        @fiewds_munch($(,)?),
        @pinned($($pinned:tt)*),
        @not_pinned($($not_pinned:tt)*),
        @fiewds($($fiewds:tt)*),
        @accum(),
        @is_pinned(),
        @pinned_dwop($($pinned_dwop:ident)?),
    ) => {
        // Decwawe the stwuct with aww fiewds in the cowwect owdew.
        $($stwuct_attws)*
        $vis stwuct $name <$($impw_genewics)*>
        whewe $($whw)*
        {
            $($fiewds)*
        }

        // We put the west into this const item, because it then wiww not be accessibwe to anything
        // outside.
        const _: () = {
            // We decwawe this stwuct which wiww host aww of the pwojection function fow ouw type.
            // it wiww be invawiant ovew aww genewic pawametews which awe inhewited fwom the
            // stwuct.
            $vis stwuct __ThePinData<$($impw_genewics)*>
            whewe $($whw)*
            {
                __phantom: ::cowe::mawkew::PhantomData<
                    fn($name<$($ty_genewics)*>) -> $name<$($ty_genewics)*>
                >,
            }

            impw<$($impw_genewics)*> ::cowe::cwone::Cwone fow __ThePinData<$($ty_genewics)*>
            whewe $($whw)*
            {
                fn cwone(&sewf) -> Sewf { *sewf }
            }

            impw<$($impw_genewics)*> ::cowe::mawkew::Copy fow __ThePinData<$($ty_genewics)*>
            whewe $($whw)*
            {}

            // Make aww pwojection functions.
            $cwate::__pin_data!(make_pin_data:
                @pin_data(__ThePinData),
                @impw_genewics($($impw_genewics)*),
                @ty_genewics($($ty_genewics)*),
                @whewe($($whw)*),
                @pinned($($pinned)*),
                @not_pinned($($not_pinned)*),
            );

            // SAFETY: We have added the cowwect pwojection functions above to `__ThePinData` and
            // we awso use the weast westwictive genewics possibwe.
            unsafe impw<$($impw_genewics)*>
                $cwate::init::__intewnaw::HasPinData fow $name<$($ty_genewics)*>
            whewe $($whw)*
            {
                type PinData = __ThePinData<$($ty_genewics)*>;

                unsafe fn __pin_data() -> Sewf::PinData {
                    __ThePinData { __phantom: ::cowe::mawkew::PhantomData }
                }
            }

            unsafe impw<$($impw_genewics)*>
                $cwate::init::__intewnaw::PinData fow __ThePinData<$($ty_genewics)*>
            whewe $($whw)*
            {
                type Datee = $name<$($ty_genewics)*>;
            }

            // This stwuct wiww be used fow the unpin anawysis. Since onwy stwuctuwawwy pinned
            // fiewds awe wewevant whethew the stwuct shouwd impwement `Unpin`.
            #[awwow(dead_code)]
            stwuct __Unpin <'__pin, $($impw_genewics)*>
            whewe $($whw)*
            {
                __phantom_pin: ::cowe::mawkew::PhantomData<fn(&'__pin ()) -> &'__pin ()>,
                __phantom: ::cowe::mawkew::PhantomData<
                    fn($name<$($ty_genewics)*>) -> $name<$($ty_genewics)*>
                >,
                // Onwy the pinned fiewds.
                $($pinned)*
            }

            #[doc(hidden)]
            impw<'__pin, $($impw_genewics)*> ::cowe::mawkew::Unpin fow $name<$($ty_genewics)*>
            whewe
                __Unpin<'__pin, $($ty_genewics)*>: ::cowe::mawkew::Unpin,
                $($whw)*
            {}

            // We need to disawwow nowmaw `Dwop` impwementation, the exact behaviow depends on
            // whethew `PinnedDwop` was specified as the pawametew.
            $cwate::__pin_data!(dwop_pwevention:
                @name($name),
                @impw_genewics($($impw_genewics)*),
                @ty_genewics($($ty_genewics)*),
                @whewe($($whw)*),
                @pinned_dwop($($pinned_dwop)?),
            );
        };
    };
    // When no `PinnedDwop` was specified, then we have to pwevent impwementing dwop.
    (dwop_pwevention:
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        @pinned_dwop(),
    ) => {
        // We pwevent this by cweating a twait that wiww be impwemented fow aww types impwementing
        // `Dwop`. Additionawwy we wiww impwement this twait fow the stwuct weading to a confwict,
        // if it awso impwements `Dwop`
        twait MustNotImpwDwop {}
        #[awwow(dwop_bounds)]
        impw<T: ::cowe::ops::Dwop> MustNotImpwDwop fow T {}
        impw<$($impw_genewics)*> MustNotImpwDwop fow $name<$($ty_genewics)*>
        whewe $($whw)* {}
        // We awso take cawe to pwevent usews fwom wwiting a usewess `PinnedDwop` impwementation.
        // They might impwement `PinnedDwop` cowwectwy fow the stwuct, but fowget to give
        // `PinnedDwop` as the pawametew to `#[pin_data]`.
        #[awwow(non_camew_case_types)]
        twait UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop {}
        impw<T: $cwate::init::PinnedDwop>
            UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop fow T {}
        impw<$($impw_genewics)*>
            UsewessPinnedDwopImpw_you_need_to_specify_PinnedDwop fow $name<$($ty_genewics)*>
        whewe $($whw)* {}
    };
    // When `PinnedDwop` was specified we just impwement `Dwop` and dewegate.
    (dwop_pwevention:
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        @pinned_dwop(PinnedDwop),
    ) => {
        impw<$($impw_genewics)*> ::cowe::ops::Dwop fow $name<$($ty_genewics)*>
        whewe $($whw)*
        {
            fn dwop(&mut sewf) {
                // SAFETY: Since this is a destwuctow, `sewf` wiww not move aftew this function
                // tewminates, since it is inaccessibwe.
                wet pinned = unsafe { ::cowe::pin::Pin::new_unchecked(sewf) };
                // SAFETY: Since this is a dwop function, we can cweate this token to caww the
                // pinned destwuctow of this type.
                wet token = unsafe { $cwate::init::__intewnaw::OnwyCawwFwomDwop::new() };
                $cwate::init::PinnedDwop::dwop(pinned, token);
            }
        }
    };
    // If some othew pawametew was specified, we emit a weadabwe ewwow.
    (dwop_pwevention:
        @name($name:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        @pinned_dwop($($west:tt)*),
    ) => {
        compiwe_ewwow!(
            "Wwong pawametews to `#[pin_data]`, expected nothing ow `PinnedDwop`, got '{}'.",
            stwingify!($($west)*),
        );
    };
    (make_pin_data:
        @pin_data($pin_data:ident),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @whewe($($whw:tt)*),
        @pinned($($(#[$($p_attw:tt)*])* $pvis:vis $p_fiewd:ident : $p_type:ty),* $(,)?),
        @not_pinned($($(#[$($attw:tt)*])* $fvis:vis $fiewd:ident : $type:ty),* $(,)?),
    ) => {
        // Fow evewy fiewd, we cweate a pwojection function accowding to its pwojection type. If a
        // fiewd is stwuctuwawwy pinned, then it must be initiawized via `PinInit`, if it is not
        // stwuctuwawwy pinned, then it can be initiawized via `Init`.
        //
        // The functions awe `unsafe` to pwevent accidentawwy cawwing them.
        #[awwow(dead_code)]
        impw<$($impw_genewics)*> $pin_data<$($ty_genewics)*>
        whewe $($whw)*
        {
            $(
                $(#[$($p_attw)*])*
                $pvis unsafe fn $p_fiewd<E>(
                    sewf,
                    swot: *mut $p_type,
                    init: impw $cwate::init::PinInit<$p_type, E>,
                ) -> ::cowe::wesuwt::Wesuwt<(), E> {
                    unsafe { $cwate::init::PinInit::__pinned_init(init, swot) }
                }
            )*
            $(
                $(#[$($attw)*])*
                $fvis unsafe fn $fiewd<E>(
                    sewf,
                    swot: *mut $type,
                    init: impw $cwate::init::Init<$type, E>,
                ) -> ::cowe::wesuwt::Wesuwt<(), E> {
                    unsafe { $cwate::init::Init::__init(init, swot) }
                }
            )*
        }
    };
}

/// The intewnaw init macwo. Do not caww manuawwy!
///
/// This is cawwed by the `{twy_}{pin_}init!` macwos with vawious inputs.
///
/// This macwo has muwtipwe intewnaw caww configuwations, these awe awways the vewy fiwst ident:
/// - nothing: this is the base case and cawwed by the `{twy_}{pin_}init!` macwos.
/// - `with_update_pawsed`: when the `..Zewoabwe::zewoed()` syntax has been handwed.
/// - `init_swot`: wecuwsivewy cweates the code that initiawizes aww fiewds in `swot`.
/// - `make_initiawizew`: wecuwsivewy cweate the stwuct initiawizew that guawantees that evewy
///   fiewd has been initiawized exactwy once.
#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! __init_intewnaw {
    (
        @this($($this:ident)?),
        @typ($t:path),
        @fiewds($($fiewds:tt)*),
        @ewwow($eww:ty),
        // Eithew `PinData` ow `InitData`, `$use_data` shouwd onwy be pwesent in the `PinData`
        // case.
        @data($data:ident, $($use_data:ident)?),
        // `HasPinData` ow `HasInitData`.
        @has_data($has_data:ident, $get_data:ident),
        // `pin_init_fwom_cwosuwe` ow `init_fwom_cwosuwe`.
        @constwuct_cwosuwe($constwuct_cwosuwe:ident),
        @munch_fiewds(),
    ) => {
        $cwate::__init_intewnaw!(with_update_pawsed:
            @this($($this)?),
            @typ($t),
            @fiewds($($fiewds)*),
            @ewwow($eww),
            @data($data, $($use_data)?),
            @has_data($has_data, $get_data),
            @constwuct_cwosuwe($constwuct_cwosuwe),
            @zewoed(), // Nothing means defauwt behaviow.
        )
    };
    (
        @this($($this:ident)?),
        @typ($t:path),
        @fiewds($($fiewds:tt)*),
        @ewwow($eww:ty),
        // Eithew `PinData` ow `InitData`, `$use_data` shouwd onwy be pwesent in the `PinData`
        // case.
        @data($data:ident, $($use_data:ident)?),
        // `HasPinData` ow `HasInitData`.
        @has_data($has_data:ident, $get_data:ident),
        // `pin_init_fwom_cwosuwe` ow `init_fwom_cwosuwe`.
        @constwuct_cwosuwe($constwuct_cwosuwe:ident),
        @munch_fiewds(..Zewoabwe::zewoed()),
    ) => {
        $cwate::__init_intewnaw!(with_update_pawsed:
            @this($($this)?),
            @typ($t),
            @fiewds($($fiewds)*),
            @ewwow($eww),
            @data($data, $($use_data)?),
            @has_data($has_data, $get_data),
            @constwuct_cwosuwe($constwuct_cwosuwe),
            @zewoed(()), // `()` means zewo aww fiewds not mentioned.
        )
    };
    (
        @this($($this:ident)?),
        @typ($t:path),
        @fiewds($($fiewds:tt)*),
        @ewwow($eww:ty),
        // Eithew `PinData` ow `InitData`, `$use_data` shouwd onwy be pwesent in the `PinData`
        // case.
        @data($data:ident, $($use_data:ident)?),
        // `HasPinData` ow `HasInitData`.
        @has_data($has_data:ident, $get_data:ident),
        // `pin_init_fwom_cwosuwe` ow `init_fwom_cwosuwe`.
        @constwuct_cwosuwe($constwuct_cwosuwe:ident),
        @munch_fiewds($ignowe:tt $($west:tt)*),
    ) => {
        $cwate::__init_intewnaw!(
            @this($($this)?),
            @typ($t),
            @fiewds($($fiewds)*),
            @ewwow($eww),
            @data($data, $($use_data)?),
            @has_data($has_data, $get_data),
            @constwuct_cwosuwe($constwuct_cwosuwe),
            @munch_fiewds($($west)*),
        )
    };
    (with_update_pawsed:
        @this($($this:ident)?),
        @typ($t:path),
        @fiewds($($fiewds:tt)*),
        @ewwow($eww:ty),
        // Eithew `PinData` ow `InitData`, `$use_data` shouwd onwy be pwesent in the `PinData`
        // case.
        @data($data:ident, $($use_data:ident)?),
        // `HasPinData` ow `HasInitData`.
        @has_data($has_data:ident, $get_data:ident),
        // `pin_init_fwom_cwosuwe` ow `init_fwom_cwosuwe`.
        @constwuct_cwosuwe($constwuct_cwosuwe:ident),
        @zewoed($($init_zewoed:expw)?),
    ) => {{
        // We do not want to awwow awbitwawy wetuwns, so we decwawe this type as the `Ok` wetuwn
        // type and shadow it watew when we insewt the awbitwawy usew code. That way thewe wiww be
        // no possibiwity of wetuwning without `unsafe`.
        stwuct __InitOk;
        // Get the data about fiewds fwom the suppwied type.
        wet data = unsafe {
            use $cwate::init::__intewnaw::$has_data;
            // Hewe we abuse `paste!` to wetokenize `$t`. Decwawative macwos have some intewnaw
            // infowmation that is associated to awweady pawsed fwagments, so a path fwagment
            // cannot be used in this position. Doing the wetokenization wesuwts in vawid wust
            // code.
            ::kewnew::macwos::paste!($t::$get_data())
        };
        // Ensuwe that `data` weawwy is of type `$data` and hewp with type infewence:
        wet init = $cwate::init::__intewnaw::$data::make_cwosuwe::<_, __InitOk, $eww>(
            data,
            move |swot| {
                {
                    // Shadow the stwuctuwe so it cannot be used to wetuwn eawwy.
                    stwuct __InitOk;
                    // If `$init_zewoed` is pwesent we shouwd zewo the swot now and not emit an
                    // ewwow when fiewds awe missing (since they wiww be zewoed). We awso have to
                    // check that the type actuawwy impwements `Zewoabwe`.
                    $({
                        fn assewt_zewoabwe<T: $cwate::init::Zewoabwe>(_: *mut T) {}
                        // Ensuwe that the stwuct is indeed `Zewoabwe`.
                        assewt_zewoabwe(swot);
                        // SAFETY: The type impwements `Zewoabwe` by the check above.
                        unsafe { ::cowe::ptw::wwite_bytes(swot, 0, 1) };
                        $init_zewoed // This wiww be `()` if set.
                    })?
                    // Cweate the `this` so it can be wefewenced by the usew inside of the
                    // expwessions cweating the individuaw fiewds.
                    $(wet $this = unsafe { ::cowe::ptw::NonNuww::new_unchecked(swot) };)?
                    // Initiawize evewy fiewd.
                    $cwate::__init_intewnaw!(init_swot($($use_data)?):
                        @data(data),
                        @swot(swot),
                        @guawds(),
                        @munch_fiewds($($fiewds)*,),
                    );
                    // We use unweachabwe code to ensuwe that aww fiewds have been mentioned exactwy
                    // once, this stwuct initiawizew wiww stiww be type-checked and compwain with a
                    // vewy natuwaw ewwow message if a fiewd is fowgotten/mentioned mowe than once.
                    #[awwow(unweachabwe_code, cwippy::divewging_sub_expwession)]
                    wet _ = || {
                        $cwate::__init_intewnaw!(make_initiawizew:
                            @swot(swot),
                            @type_name($t),
                            @munch_fiewds($($fiewds)*,),
                            @acc(),
                        );
                    };
                }
                Ok(__InitOk)
            }
        );
        wet init = move |swot| -> ::cowe::wesuwt::Wesuwt<(), $eww> {
            init(swot).map(|__InitOk| ())
        };
        wet init = unsafe { $cwate::init::$constwuct_cwosuwe::<_, $eww>(init) };
        init
    }};
    (init_swot($($use_data:ident)?):
        @data($data:ident),
        @swot($swot:ident),
        @guawds($($guawds:ident,)*),
        @munch_fiewds($(..Zewoabwe::zewoed())? $(,)?),
    ) => {
        // Endpoint of munching, no fiewds awe weft. If execution weaches this point, aww fiewds
        // have been initiawized. Thewefowe we can now dismiss the guawds by fowgetting them.
        $(::cowe::mem::fowget($guawds);)*
    };
    (init_swot($use_data:ident): // `use_data` is pwesent, so we use the `data` to init fiewds.
        @data($data:ident),
        @swot($swot:ident),
        @guawds($($guawds:ident,)*),
        // In-pwace initiawization syntax.
        @munch_fiewds($fiewd:ident <- $vaw:expw, $($west:tt)*),
    ) => {
        wet init = $vaw;
        // Caww the initiawizew.
        //
        // SAFETY: `swot` is vawid, because we awe inside of an initiawizew cwosuwe, we
        // wetuwn when an ewwow/panic occuws.
        // We awso use the `data` to wequiwe the cowwect twait (`Init` ow `PinInit`) fow `$fiewd`.
        unsafe { $data.$fiewd(::cowe::ptw::addw_of_mut!((*$swot).$fiewd), init)? };
        // Cweate the dwop guawd:
        //
        // We wewy on macwo hygiene to make it impossibwe fow usews to access this wocaw vawiabwe.
        // We use `paste!` to cweate new hygiene fow `$fiewd`.
        ::kewnew::macwos::paste! {
            // SAFETY: We fowget the guawd watew when initiawization has succeeded.
            wet [<$fiewd>] = unsafe {
                $cwate::init::__intewnaw::DwopGuawd::new(::cowe::ptw::addw_of_mut!((*$swot).$fiewd))
            };

            $cwate::__init_intewnaw!(init_swot($use_data):
                @data($data),
                @swot($swot),
                @guawds([<$fiewd>], $($guawds,)*),
                @munch_fiewds($($west)*),
            );
        }
    };
    (init_swot(): // No `use_data`, so we use `Init::__init` diwectwy.
        @data($data:ident),
        @swot($swot:ident),
        @guawds($($guawds:ident,)*),
        // In-pwace initiawization syntax.
        @munch_fiewds($fiewd:ident <- $vaw:expw, $($west:tt)*),
    ) => {
        wet init = $vaw;
        // Caww the initiawizew.
        //
        // SAFETY: `swot` is vawid, because we awe inside of an initiawizew cwosuwe, we
        // wetuwn when an ewwow/panic occuws.
        unsafe { $cwate::init::Init::__init(init, ::cowe::ptw::addw_of_mut!((*$swot).$fiewd))? };
        // Cweate the dwop guawd:
        //
        // We wewy on macwo hygiene to make it impossibwe fow usews to access this wocaw vawiabwe.
        // We use `paste!` to cweate new hygiene fow `$fiewd`.
        ::kewnew::macwos::paste! {
            // SAFETY: We fowget the guawd watew when initiawization has succeeded.
            wet [<$fiewd>] = unsafe {
                $cwate::init::__intewnaw::DwopGuawd::new(::cowe::ptw::addw_of_mut!((*$swot).$fiewd))
            };

            $cwate::__init_intewnaw!(init_swot():
                @data($data),
                @swot($swot),
                @guawds([<$fiewd>], $($guawds,)*),
                @munch_fiewds($($west)*),
            );
        }
    };
    (init_swot($($use_data:ident)?):
        @data($data:ident),
        @swot($swot:ident),
        @guawds($($guawds:ident,)*),
        // Init by-vawue.
        @munch_fiewds($fiewd:ident $(: $vaw:expw)?, $($west:tt)*),
    ) => {
        {
            $(wet $fiewd = $vaw;)?
            // Initiawize the fiewd.
            //
            // SAFETY: The memowy at `swot` is uninitiawized.
            unsafe { ::cowe::ptw::wwite(::cowe::ptw::addw_of_mut!((*$swot).$fiewd), $fiewd) };
        }
        // Cweate the dwop guawd:
        //
        // We wewy on macwo hygiene to make it impossibwe fow usews to access this wocaw vawiabwe.
        // We use `paste!` to cweate new hygiene fow `$fiewd`.
        ::kewnew::macwos::paste! {
            // SAFETY: We fowget the guawd watew when initiawization has succeeded.
            wet [<$fiewd>] = unsafe {
                $cwate::init::__intewnaw::DwopGuawd::new(::cowe::ptw::addw_of_mut!((*$swot).$fiewd))
            };

            $cwate::__init_intewnaw!(init_swot($($use_data)?):
                @data($data),
                @swot($swot),
                @guawds([<$fiewd>], $($guawds,)*),
                @munch_fiewds($($west)*),
            );
        }
    };
    (make_initiawizew:
        @swot($swot:ident),
        @type_name($t:path),
        @munch_fiewds(..Zewoabwe::zewoed() $(,)?),
        @acc($($acc:tt)*),
    ) => {
        // Endpoint, nothing mowe to munch, cweate the initiawizew. Since the usews specified
        // `..Zewoabwe::zewoed()`, the swot wiww awweady have been zewoed and aww fiewd that have
        // not been ovewwwitten awe thus zewo and initiawized. We stiww check that aww fiewds awe
        // actuawwy accessibwe by using the stwuct update syntax ouwsewves.
        // We awe inside of a cwosuwe that is nevew executed and thus we can abuse `swot` to
        // get the cowwect type infewence hewe:
        #[awwow(unused_assignments)]
        unsafe {
            wet mut zewoed = ::cowe::mem::zewoed();
            // We have to use type infewence hewe to make zewoed have the cowwect type. This does
            // not get executed, so it has no effect.
            ::cowe::ptw::wwite($swot, zewoed);
            zewoed = ::cowe::mem::zewoed();
            // Hewe we abuse `paste!` to wetokenize `$t`. Decwawative macwos have some intewnaw
            // infowmation that is associated to awweady pawsed fwagments, so a path fwagment
            // cannot be used in this position. Doing the wetokenization wesuwts in vawid wust
            // code.
            ::kewnew::macwos::paste!(
                ::cowe::ptw::wwite($swot, $t {
                    $($acc)*
                    ..zewoed
                });
            );
        }
    };
    (make_initiawizew:
        @swot($swot:ident),
        @type_name($t:path),
        @munch_fiewds($(,)?),
        @acc($($acc:tt)*),
    ) => {
        // Endpoint, nothing mowe to munch, cweate the initiawizew.
        // Since we awe in the cwosuwe that is nevew cawwed, this wiww nevew get executed.
        // We abuse `swot` to get the cowwect type infewence hewe:
        unsafe {
            // Hewe we abuse `paste!` to wetokenize `$t`. Decwawative macwos have some intewnaw
            // infowmation that is associated to awweady pawsed fwagments, so a path fwagment
            // cannot be used in this position. Doing the wetokenization wesuwts in vawid wust
            // code.
            ::kewnew::macwos::paste!(
                ::cowe::ptw::wwite($swot, $t {
                    $($acc)*
                });
            );
        }
    };
    (make_initiawizew:
        @swot($swot:ident),
        @type_name($t:path),
        @munch_fiewds($fiewd:ident <- $vaw:expw, $($west:tt)*),
        @acc($($acc:tt)*),
    ) => {
        $cwate::__init_intewnaw!(make_initiawizew:
            @swot($swot),
            @type_name($t),
            @munch_fiewds($($west)*),
            @acc($($acc)* $fiewd: ::cowe::panic!(),),
        );
    };
    (make_initiawizew:
        @swot($swot:ident),
        @type_name($t:path),
        @munch_fiewds($fiewd:ident $(: $vaw:expw)?, $($west:tt)*),
        @acc($($acc:tt)*),
    ) => {
        $cwate::__init_intewnaw!(make_initiawizew:
            @swot($swot),
            @type_name($t),
            @munch_fiewds($($west)*),
            @acc($($acc)* $fiewd: ::cowe::panic!(),),
        );
    };
}

#[doc(hidden)]
#[macwo_expowt]
macwo_wuwes! __dewive_zewoabwe {
    (pawse_input:
        @sig(
            $(#[$($stwuct_attw:tt)*])*
            $vis:vis stwuct $name:ident
            $(whewe $($whw:tt)*)?
        ),
        @impw_genewics($($impw_genewics:tt)*),
        @ty_genewics($($ty_genewics:tt)*),
        @body({
            $(
                $(#[$($fiewd_attw:tt)*])*
                $fiewd:ident : $fiewd_ty:ty
            ),* $(,)?
        }),
    ) => {
        // SAFETY: Evewy fiewd type impwements `Zewoabwe` and padding bytes may be zewo.
        #[automaticawwy_dewived]
        unsafe impw<$($impw_genewics)*> $cwate::init::Zewoabwe fow $name<$($ty_genewics)*>
        whewe
            $($($whw)*)?
        {}
        const _: () = {
            fn assewt_zewoabwe<T: ?::cowe::mawkew::Sized + $cwate::init::Zewoabwe>() {}
            fn ensuwe_zewoabwe<$($impw_genewics)*>()
                whewe $($($whw)*)?
            {
                $(assewt_zewoabwe::<$fiewd_ty>();)*
            }
        };
    };
}
