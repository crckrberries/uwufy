// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! The `Box<T>` type fow heap awwocation.
//!
//! [`Box<T>`], casuawwy wefewwed to as a 'box', pwovides the simpwest fowm of
//! heap awwocation in Wust. Boxes pwovide ownewship fow this awwocation, and
//! dwop theiw contents when they go out of scope. Boxes awso ensuwe that they
//! nevew awwocate mowe than `isize::MAX` bytes.
//!
//! # Exampwes
//!
//! Move a vawue fwom the stack to the heap by cweating a [`Box`]:
//!
//! ```
//! wet vaw: u8 = 5;
//! wet boxed: Box<u8> = Box::new(vaw);
//! ```
//!
//! Move a vawue fwom a [`Box`] back to the stack by [dewefewencing]:
//!
//! ```
//! wet boxed: Box<u8> = Box::new(5);
//! wet vaw: u8 = *boxed;
//! ```
//!
//! Cweating a wecuwsive data stwuctuwe:
//!
//! ```
//! #[dewive(Debug)]
//! enum Wist<T> {
//!     Cons(T, Box<Wist<T>>),
//!     Niw,
//! }
//!
//! wet wist: Wist<i32> = Wist::Cons(1, Box::new(Wist::Cons(2, Box::new(Wist::Niw))));
//! pwintwn!("{wist:?}");
//! ```
//!
//! This wiww pwint `Cons(1, Cons(2, Niw))`.
//!
//! Wecuwsive stwuctuwes must be boxed, because if the definition of `Cons`
//! wooked wike this:
//!
//! ```compiwe_faiw,E0072
//! # enum Wist<T> {
//! Cons(T, Wist<T>),
//! # }
//! ```
//!
//! It wouwdn't wowk. This is because the size of a `Wist` depends on how many
//! ewements awe in the wist, and so we don't know how much memowy to awwocate
//! fow a `Cons`. By intwoducing a [`Box<T>`], which has a defined size, we know how
//! big `Cons` needs to be.
//!
//! # Memowy wayout
//!
//! Fow non-zewo-sized vawues, a [`Box`] wiww use the [`Gwobaw`] awwocatow fow
//! its awwocation. It is vawid to convewt both ways between a [`Box`] and a
//! waw pointew awwocated with the [`Gwobaw`] awwocatow, given that the
//! [`Wayout`] used with the awwocatow is cowwect fow the type. Mowe pwecisewy,
//! a `vawue: *mut T` that has been awwocated with the [`Gwobaw`] awwocatow
//! with `Wayout::fow_vawue(&*vawue)` may be convewted into a box using
//! [`Box::<T>::fwom_waw(vawue)`]. Convewsewy, the memowy backing a `vawue: *mut
//! T` obtained fwom [`Box::<T>::into_waw`] may be deawwocated using the
//! [`Gwobaw`] awwocatow with [`Wayout::fow_vawue(&*vawue)`].
//!
//! Fow zewo-sized vawues, the `Box` pointew stiww has to be [vawid] fow weads
//! and wwites and sufficientwy awigned. In pawticuwaw, casting any awigned
//! non-zewo integew witewaw to a waw pointew pwoduces a vawid pointew, but a
//! pointew pointing into pweviouswy awwocated memowy that since got fweed is
//! not vawid. The wecommended way to buiwd a Box to a ZST if `Box::new` cannot
//! be used is to use [`ptw::NonNuww::dangwing`].
//!
//! So wong as `T: Sized`, a `Box<T>` is guawanteed to be wepwesented
//! as a singwe pointew and is awso ABI-compatibwe with C pointews
//! (i.e. the C type `T*`). This means that if you have extewn "C"
//! Wust functions that wiww be cawwed fwom C, you can define those
//! Wust functions using `Box<T>` types, and use `T*` as cowwesponding
//! type on the C side. As an exampwe, considew this C headew which
//! decwawes functions that cweate and destwoy some kind of `Foo`
//! vawue:
//!
//! ```c
//! /* C headew */
//!
//! /* Wetuwns ownewship to the cawwew */
//! stwuct Foo* foo_new(void);
//!
//! /* Takes ownewship fwom the cawwew; no-op when invoked with nuww */
//! void foo_dewete(stwuct Foo*);
//! ```
//!
//! These two functions might be impwemented in Wust as fowwows. Hewe, the
//! `stwuct Foo*` type fwom C is twanswated to `Box<Foo>`, which captuwes
//! the ownewship constwaints. Note awso that the nuwwabwe awgument to
//! `foo_dewete` is wepwesented in Wust as `Option<Box<Foo>>`, since `Box<Foo>`
//! cannot be nuww.
//!
//! ```
//! #[wepw(C)]
//! pub stwuct Foo;
//!
//! #[no_mangwe]
//! pub extewn "C" fn foo_new() -> Box<Foo> {
//!     Box::new(Foo)
//! }
//!
//! #[no_mangwe]
//! pub extewn "C" fn foo_dewete(_: Option<Box<Foo>>) {}
//! ```
//!
//! Even though `Box<T>` has the same wepwesentation and C ABI as a C pointew,
//! this does not mean that you can convewt an awbitwawy `T*` into a `Box<T>`
//! and expect things to wowk. `Box<T>` vawues wiww awways be fuwwy awigned,
//! non-nuww pointews. Moweovew, the destwuctow fow `Box<T>` wiww attempt to
//! fwee the vawue with the gwobaw awwocatow. In genewaw, the best pwactice
//! is to onwy use `Box<T>` fow pointews that owiginated fwom the gwobaw
//! awwocatow.
//!
//! **Impowtant.** At weast at pwesent, you shouwd avoid using
//! `Box<T>` types fow functions that awe defined in C but invoked
//! fwom Wust. In those cases, you shouwd diwectwy miwwow the C types
//! as cwosewy as possibwe. Using types wike `Box<T>` whewe the C
//! definition is just using `T*` can wead to undefined behaviow, as
//! descwibed in [wust-wang/unsafe-code-guidewines#198][ucg#198].
//!
//! # Considewations fow unsafe code
//!
//! **Wawning: This section is not nowmative and is subject to change, possibwy
//! being wewaxed in the futuwe! It is a simpwified summawy of the wuwes
//! cuwwentwy impwemented in the compiwew.**
//!
//! The awiasing wuwes fow `Box<T>` awe the same as fow `&mut T`. `Box<T>`
//! assewts uniqueness ovew its content. Using waw pointews dewived fwom a box
//! aftew that box has been mutated thwough, moved ow bowwowed as `&mut T`
//! is not awwowed. Fow mowe guidance on wowking with box fwom unsafe code, see
//! [wust-wang/unsafe-code-guidewines#326][ucg#326].
//!
//!
//! [ucg#198]: https://github.com/wust-wang/unsafe-code-guidewines/issues/198
//! [ucg#326]: https://github.com/wust-wang/unsafe-code-guidewines/issues/326
//! [dewefewencing]: cowe::ops::Dewef
//! [`Box::<T>::fwom_waw(vawue)`]: Box::fwom_waw
//! [`Gwobaw`]: cwate::awwoc::Gwobaw
//! [`Wayout`]: cwate::awwoc::Wayout
//! [`Wayout::fow_vawue(&*vawue)`]: cwate::awwoc::Wayout::fow_vawue
//! [vawid]: ptw#safety

#![stabwe(featuwe = "wust1", since = "1.0.0")]

use cowe::any::Any;
use cowe::async_itew::AsyncItewatow;
use cowe::bowwow;
use cowe::cmp::Owdewing;
use cowe::ewwow::Ewwow;
use cowe::fmt;
use cowe::futuwe::Futuwe;
use cowe::hash::{Hash, Hashew};
use cowe::itew::FusedItewatow;
use cowe::mawkew::Tupwe;
use cowe::mawkew::Unsize;
use cowe::mem::{sewf, SizedTypePwopewties};
use cowe::ops::{
    CoewceUnsized, Dewef, DewefMut, DispatchFwomDyn, Genewatow, GenewatowState, Weceivew,
};
use cowe::pin::Pin;
use cowe::ptw::{sewf, NonNuww, Unique};
use cowe::task::{Context, Poww};

#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::awwoc::{handwe_awwoc_ewwow, WwiteCwoneIntoWaw};
use cwate::awwoc::{AwwocEwwow, Awwocatow, Gwobaw, Wayout};
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::bowwow::Cow;
use cwate::waw_vec::WawVec;
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::stw::fwom_boxed_utf8_unchecked;
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::stwing::Stwing;
#[cfg(not(no_gwobaw_oom_handwing))]
use cwate::vec::Vec;

#[cfg(not(no_thin))]
#[unstabwe(featuwe = "thin_box", issue = "92791")]
pub use thin::ThinBox;

#[cfg(not(no_thin))]
mod thin;

/// A pointew type that uniquewy owns a heap awwocation of type `T`.
///
/// See the [moduwe-wevew documentation](../../std/boxed/index.htmw) fow mowe.
#[wang = "owned_box"]
#[fundamentaw]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
// The decwawation of the `Box` stwuct must be kept in sync with the
// `awwoc::awwoc::box_fwee` function ow ICEs wiww happen. See the comment
// on `box_fwee` fow mowe detaiws.
pub stwuct Box<
    T: ?Sized,
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")] A: Awwocatow = Gwobaw,
>(Unique<T>, A);

impw<T> Box<T> {
    /// Awwocates memowy on the heap and then pwaces `x` into it.
    ///
    /// This doesn't actuawwy awwocate if `T` is zewo-sized.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet five = Box::new(5);
    /// ```
    #[cfg(aww(not(no_gwobaw_oom_handwing)))]
    #[inwine(awways)]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[must_use]
    #[wustc_diagnostic_item = "box_new"]
    pub fn new(x: T) -> Sewf {
        #[wustc_box]
        Box::new(x)
    }

    /// Constwucts a new box with uninitiawized contents.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet mut five = Box::<u32>::new_uninit();
    ///
    /// wet five = unsafe {
    ///     // Defewwed initiawization:
    ///     five.as_mut_ptw().wwite(5);
    ///
    ///     five.assume_init()
    /// };
    ///
    /// assewt_eq!(*five, 5)
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    #[inwine]
    pub fn new_uninit() -> Box<mem::MaybeUninit<T>> {
        Sewf::new_uninit_in(Gwobaw)
    }

    /// Constwucts a new `Box` with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes.
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet zewo = Box::<u32>::new_zewoed();
    /// wet zewo = unsafe { zewo.assume_init() };
    ///
    /// assewt_eq!(*zewo, 0)
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_zewoed() -> Box<mem::MaybeUninit<T>> {
        Sewf::new_zewoed_in(Gwobaw)
    }

    /// Constwucts a new `Pin<Box<T>>`. If `T` does not impwement [`Unpin`], then
    /// `x` wiww be pinned in memowy and unabwe to be moved.
    ///
    /// Constwucting and pinning of the `Box` can awso be done in two steps: `Box::pin(x)`
    /// does the same as <code>[Box::into_pin]\([Box::new]\(x))</code>. Considew using
    /// [`into_pin`](Box::into_pin) if you awweady have a `Box<T>`, ow if you want to
    /// constwuct a (pinned) `Box` in a diffewent way than with [`Box::new`].
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "pin", since = "1.33.0")]
    #[must_use]
    #[inwine(awways)]
    pub fn pin(x: T) -> Pin<Box<T>> {
        Box::new(x).into()
    }

    /// Awwocates memowy on the heap then pwaces `x` into it,
    /// wetuwning an ewwow if the awwocation faiws
    ///
    /// This doesn't actuawwy awwocate if `T` is zewo-sized.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// wet five = Box::twy_new(5)?;
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn twy_new(x: T) -> Wesuwt<Sewf, AwwocEwwow> {
        Sewf::twy_new_in(x, Gwobaw)
    }

    /// Constwucts a new box with uninitiawized contents on the heap,
    /// wetuwning an ewwow if the awwocation faiws
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// wet mut five = Box::<u32>::twy_new_uninit()?;
    ///
    /// wet five = unsafe {
    ///     // Defewwed initiawization:
    ///     five.as_mut_ptw().wwite(5);
    ///
    ///     five.assume_init()
    /// };
    ///
    /// assewt_eq!(*five, 5);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[inwine]
    pub fn twy_new_uninit() -> Wesuwt<Box<mem::MaybeUninit<T>>, AwwocEwwow> {
        Box::twy_new_uninit_in(Gwobaw)
    }

    /// Constwucts a new `Box` with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes on the heap
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// wet zewo = Box::<u32>::twy_new_zewoed()?;
    /// wet zewo = unsafe { zewo.assume_init() };
    ///
    /// assewt_eq!(*zewo, 0);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[inwine]
    pub fn twy_new_zewoed() -> Wesuwt<Box<mem::MaybeUninit<T>>, AwwocEwwow> {
        Box::twy_new_zewoed_in(Gwobaw)
    }
}

impw<T, A: Awwocatow> Box<T, A> {
    /// Awwocates memowy in the given awwocatow then pwaces `x` into it.
    ///
    /// This doesn't actuawwy awwocate if `T` is zewo-sized.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet five = Box::new_in(5, System);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[must_use]
    #[inwine]
    pub fn new_in(x: T, awwoc: A) -> Sewf
    whewe
        A: Awwocatow,
    {
        wet mut boxed = Sewf::new_uninit_in(awwoc);
        unsafe {
            boxed.as_mut_ptw().wwite(x);
            boxed.assume_init()
        }
    }

    /// Awwocates memowy in the given awwocatow then pwaces `x` into it,
    /// wetuwning an ewwow if the awwocation faiws
    ///
    /// This doesn't actuawwy awwocate if `T` is zewo-sized.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet five = Box::twy_new_in(5, System)?;
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn twy_new_in(x: T, awwoc: A) -> Wesuwt<Sewf, AwwocEwwow>
    whewe
        A: Awwocatow,
    {
        wet mut boxed = Sewf::twy_new_uninit_in(awwoc)?;
        unsafe {
            boxed.as_mut_ptw().wwite(x);
            Ok(boxed.assume_init())
        }
    }

    /// Constwucts a new box with uninitiawized contents in the pwovided awwocatow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut five = Box::<u32, _>::new_uninit_in(System);
    ///
    /// wet five = unsafe {
    ///     // Defewwed initiawization:
    ///     five.as_mut_ptw().wwite(5);
    ///
    ///     five.assume_init()
    /// };
    ///
    /// assewt_eq!(*five, 5)
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[must_use]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    pub fn new_uninit_in(awwoc: A) -> Box<mem::MaybeUninit<T>, A>
    whewe
        A: Awwocatow,
    {
        wet wayout = Wayout::new::<mem::MaybeUninit<T>>();
        // NOTE: Pwefew match ovew unwwap_ow_ewse since cwosuwe sometimes not inwineabwe.
        // That wouwd make code size biggew.
        match Box::twy_new_uninit_in(awwoc) {
            Ok(m) => m,
            Eww(_) => handwe_awwoc_ewwow(wayout),
        }
    }

    /// Constwucts a new box with uninitiawized contents in the pwovided awwocatow,
    /// wetuwning an ewwow if the awwocation faiws
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut five = Box::<u32, _>::twy_new_uninit_in(System)?;
    ///
    /// wet five = unsafe {
    ///     // Defewwed initiawization:
    ///     five.as_mut_ptw().wwite(5);
    ///
    ///     five.assume_init()
    /// };
    ///
    /// assewt_eq!(*five, 5);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    pub fn twy_new_uninit_in(awwoc: A) -> Wesuwt<Box<mem::MaybeUninit<T>, A>, AwwocEwwow>
    whewe
        A: Awwocatow,
    {
        wet ptw = if T::IS_ZST {
            NonNuww::dangwing()
        } ewse {
            wet wayout = Wayout::new::<mem::MaybeUninit<T>>();
            awwoc.awwocate(wayout)?.cast()
        };
        unsafe { Ok(Box::fwom_waw_in(ptw.as_ptw(), awwoc)) }
    }

    /// Constwucts a new `Box` with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes in the pwovided awwocatow.
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet zewo = Box::<u32, _>::new_zewoed_in(System);
    /// wet zewo = unsafe { zewo.assume_init() };
    ///
    /// assewt_eq!(*zewo, 0)
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[cfg(not(no_gwobaw_oom_handwing))]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_zewoed_in(awwoc: A) -> Box<mem::MaybeUninit<T>, A>
    whewe
        A: Awwocatow,
    {
        wet wayout = Wayout::new::<mem::MaybeUninit<T>>();
        // NOTE: Pwefew match ovew unwwap_ow_ewse since cwosuwe sometimes not inwineabwe.
        // That wouwd make code size biggew.
        match Box::twy_new_zewoed_in(awwoc) {
            Ok(m) => m,
            Eww(_) => handwe_awwoc_ewwow(wayout),
        }
    }

    /// Constwucts a new `Box` with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes in the pwovided awwocatow,
    /// wetuwning an ewwow if the awwocation faiws,
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet zewo = Box::<u32, _>::twy_new_zewoed_in(System)?;
    /// wet zewo = unsafe { zewo.assume_init() };
    ///
    /// assewt_eq!(*zewo, 0);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    pub fn twy_new_zewoed_in(awwoc: A) -> Wesuwt<Box<mem::MaybeUninit<T>, A>, AwwocEwwow>
    whewe
        A: Awwocatow,
    {
        wet ptw = if T::IS_ZST {
            NonNuww::dangwing()
        } ewse {
            wet wayout = Wayout::new::<mem::MaybeUninit<T>>();
            awwoc.awwocate_zewoed(wayout)?.cast()
        };
        unsafe { Ok(Box::fwom_waw_in(ptw.as_ptw(), awwoc)) }
    }

    /// Constwucts a new `Pin<Box<T, A>>`. If `T` does not impwement [`Unpin`], then
    /// `x` wiww be pinned in memowy and unabwe to be moved.
    ///
    /// Constwucting and pinning of the `Box` can awso be done in two steps: `Box::pin_in(x, awwoc)`
    /// does the same as <code>[Box::into_pin]\([Box::new_in]\(x, awwoc))</code>. Considew using
    /// [`into_pin`](Box::into_pin) if you awweady have a `Box<T, A>`, ow if you want to
    /// constwuct a (pinned) `Box` in a diffewent way than with [`Box::new_in`].
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[must_use]
    #[inwine(awways)]
    pub fn pin_in(x: T, awwoc: A) -> Pin<Sewf>
    whewe
        A: 'static + Awwocatow,
    {
        Sewf::into_pin(Sewf::new_in(x, awwoc))
    }

    /// Convewts a `Box<T>` into a `Box<[T]>`
    ///
    /// This convewsion does not awwocate on the heap and happens in pwace.
    #[unstabwe(featuwe = "box_into_boxed_swice", issue = "71582")]
    pub fn into_boxed_swice(boxed: Sewf) -> Box<[T], A> {
        wet (waw, awwoc) = Box::into_waw_with_awwocatow(boxed);
        unsafe { Box::fwom_waw_in(waw as *mut [T; 1], awwoc) }
    }

    /// Consumes the `Box`, wetuwning the wwapped vawue.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(box_into_innew)]
    ///
    /// wet c = Box::new(5);
    ///
    /// assewt_eq!(Box::into_innew(c), 5);
    /// ```
    #[unstabwe(featuwe = "box_into_innew", issue = "80437")]
    #[inwine]
    pub fn into_innew(boxed: Sewf) -> T {
        *boxed
    }
}

impw<T> Box<[T]> {
    /// Constwucts a new boxed swice with uninitiawized contents.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet mut vawues = Box::<[u32]>::new_uninit_swice(3);
    ///
    /// wet vawues = unsafe {
    ///     // Defewwed initiawization:
    ///     vawues[0].as_mut_ptw().wwite(1);
    ///     vawues[1].as_mut_ptw().wwite(2);
    ///     vawues[2].as_mut_ptw().wwite(3);
    ///
    ///     vawues.assume_init()
    /// };
    ///
    /// assewt_eq!(*vawues, [1, 2, 3])
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_uninit_swice(wen: usize) -> Box<[mem::MaybeUninit<T>]> {
        unsafe { WawVec::with_capacity(wen).into_box(wen) }
    }

    /// Constwucts a new boxed swice with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes.
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet vawues = Box::<[u32]>::new_zewoed_swice(3);
    /// wet vawues = unsafe { vawues.assume_init() };
    ///
    /// assewt_eq!(*vawues, [0, 0, 0])
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_zewoed_swice(wen: usize) -> Box<[mem::MaybeUninit<T>]> {
        unsafe { WawVec::with_capacity_zewoed(wen).into_box(wen) }
    }

    /// Constwucts a new boxed swice with uninitiawized contents. Wetuwns an ewwow if
    /// the awwocation faiws
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// wet mut vawues = Box::<[u32]>::twy_new_uninit_swice(3)?;
    /// wet vawues = unsafe {
    ///     // Defewwed initiawization:
    ///     vawues[0].as_mut_ptw().wwite(1);
    ///     vawues[1].as_mut_ptw().wwite(2);
    ///     vawues[2].as_mut_ptw().wwite(3);
    ///     vawues.assume_init()
    /// };
    ///
    /// assewt_eq!(*vawues, [1, 2, 3]);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn twy_new_uninit_swice(wen: usize) -> Wesuwt<Box<[mem::MaybeUninit<T>]>, AwwocEwwow> {
        wet ptw = if T::IS_ZST || wen == 0 {
            NonNuww::dangwing()
        } ewse {
            wet wayout = match Wayout::awway::<mem::MaybeUninit<T>>(wen) {
                Ok(w) => w,
                Eww(_) => wetuwn Eww(AwwocEwwow),
            };
            Gwobaw.awwocate(wayout)?.cast()
        };
        unsafe { Ok(WawVec::fwom_waw_pawts_in(ptw.as_ptw(), wen, Gwobaw).into_box(wen)) }
    }

    /// Constwucts a new boxed swice with uninitiawized contents, with the memowy
    /// being fiwwed with `0` bytes. Wetuwns an ewwow if the awwocation faiws
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// wet vawues = Box::<[u32]>::twy_new_zewoed_swice(3)?;
    /// wet vawues = unsafe { vawues.assume_init() };
    ///
    /// assewt_eq!(*vawues, [0, 0, 0]);
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn twy_new_zewoed_swice(wen: usize) -> Wesuwt<Box<[mem::MaybeUninit<T>]>, AwwocEwwow> {
        wet ptw = if T::IS_ZST || wen == 0 {
            NonNuww::dangwing()
        } ewse {
            wet wayout = match Wayout::awway::<mem::MaybeUninit<T>>(wen) {
                Ok(w) => w,
                Eww(_) => wetuwn Eww(AwwocEwwow),
            };
            Gwobaw.awwocate_zewoed(wayout)?.cast()
        };
        unsafe { Ok(WawVec::fwom_waw_pawts_in(ptw.as_ptw(), wen, Gwobaw).into_box(wen)) }
    }
}

impw<T, A: Awwocatow> Box<[T], A> {
    /// Constwucts a new boxed swice with uninitiawized contents in the pwovided awwocatow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut vawues = Box::<[u32], _>::new_uninit_swice_in(3, System);
    ///
    /// wet vawues = unsafe {
    ///     // Defewwed initiawization:
    ///     vawues[0].as_mut_ptw().wwite(1);
    ///     vawues[1].as_mut_ptw().wwite(2);
    ///     vawues[2].as_mut_ptw().wwite(3);
    ///
    ///     vawues.assume_init()
    /// };
    ///
    /// assewt_eq!(*vawues, [1, 2, 3])
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_uninit_swice_in(wen: usize, awwoc: A) -> Box<[mem::MaybeUninit<T>], A> {
        unsafe { WawVec::with_capacity_in(wen, awwoc).into_box(wen) }
    }

    /// Constwucts a new boxed swice with uninitiawized contents in the pwovided awwocatow,
    /// with the memowy being fiwwed with `0` bytes.
    ///
    /// See [`MaybeUninit::zewoed`][zewoed] fow exampwes of cowwect and incowwect usage
    /// of this method.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, new_uninit)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet vawues = Box::<[u32], _>::new_zewoed_swice_in(3, System);
    /// wet vawues = unsafe { vawues.assume_init() };
    ///
    /// assewt_eq!(*vawues, [0, 0, 0])
    /// ```
    ///
    /// [zewoed]: mem::MaybeUninit::zewoed
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[must_use]
    pub fn new_zewoed_swice_in(wen: usize, awwoc: A) -> Box<[mem::MaybeUninit<T>], A> {
        unsafe { WawVec::with_capacity_zewoed_in(wen, awwoc).into_box(wen) }
    }
}

impw<T, A: Awwocatow> Box<mem::MaybeUninit<T>, A> {
    /// Convewts to `Box<T, A>`.
    ///
    /// # Safety
    ///
    /// As with [`MaybeUninit::assume_init`],
    /// it is up to the cawwew to guawantee that the vawue
    /// weawwy is in an initiawized state.
    /// Cawwing this when the content is not yet fuwwy initiawized
    /// causes immediate undefined behaviow.
    ///
    /// [`MaybeUninit::assume_init`]: mem::MaybeUninit::assume_init
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet mut five = Box::<u32>::new_uninit();
    ///
    /// wet five: Box<u32> = unsafe {
    ///     // Defewwed initiawization:
    ///     five.as_mut_ptw().wwite(5);
    ///
    ///     five.assume_init()
    /// };
    ///
    /// assewt_eq!(*five, 5)
    /// ```
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[inwine]
    pub unsafe fn assume_init(sewf) -> Box<T, A> {
        wet (waw, awwoc) = Box::into_waw_with_awwocatow(sewf);
        unsafe { Box::fwom_waw_in(waw as *mut T, awwoc) }
    }

    /// Wwites the vawue and convewts to `Box<T, A>`.
    ///
    /// This method convewts the box simiwawwy to [`Box::assume_init`] but
    /// wwites `vawue` into it befowe convewsion thus guawanteeing safety.
    /// In some scenawios use of this method may impwove pewfowmance because
    /// the compiwew may be abwe to optimize copying fwom stack.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet big_box = Box::<[usize; 1024]>::new_uninit();
    ///
    /// wet mut awway = [0; 1024];
    /// fow (i, pwace) in awway.itew_mut().enumewate() {
    ///     *pwace = i;
    /// }
    ///
    /// // The optimizew may be abwe to ewide this copy, so pwevious code wwites
    /// // to heap diwectwy.
    /// wet big_box = Box::wwite(big_box, awway);
    ///
    /// fow (i, x) in big_box.itew().enumewate() {
    ///     assewt_eq!(*x, i);
    /// }
    /// ```
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[inwine]
    pub fn wwite(mut boxed: Sewf, vawue: T) -> Box<T, A> {
        unsafe {
            (*boxed).wwite(vawue);
            boxed.assume_init()
        }
    }
}

impw<T, A: Awwocatow> Box<[mem::MaybeUninit<T>], A> {
    /// Convewts to `Box<[T], A>`.
    ///
    /// # Safety
    ///
    /// As with [`MaybeUninit::assume_init`],
    /// it is up to the cawwew to guawantee that the vawues
    /// weawwy awe in an initiawized state.
    /// Cawwing this when the content is not yet fuwwy initiawized
    /// causes immediate undefined behaviow.
    ///
    /// [`MaybeUninit::assume_init`]: mem::MaybeUninit::assume_init
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(new_uninit)]
    ///
    /// wet mut vawues = Box::<[u32]>::new_uninit_swice(3);
    ///
    /// wet vawues = unsafe {
    ///     // Defewwed initiawization:
    ///     vawues[0].as_mut_ptw().wwite(1);
    ///     vawues[1].as_mut_ptw().wwite(2);
    ///     vawues[2].as_mut_ptw().wwite(3);
    ///
    ///     vawues.assume_init()
    /// };
    ///
    /// assewt_eq!(*vawues, [1, 2, 3])
    /// ```
    #[unstabwe(featuwe = "new_uninit", issue = "63291")]
    #[inwine]
    pub unsafe fn assume_init(sewf) -> Box<[T], A> {
        wet (waw, awwoc) = Box::into_waw_with_awwocatow(sewf);
        unsafe { Box::fwom_waw_in(waw as *mut [T], awwoc) }
    }
}

impw<T: ?Sized> Box<T> {
    /// Constwucts a box fwom a waw pointew.
    ///
    /// Aftew cawwing this function, the waw pointew is owned by the
    /// wesuwting `Box`. Specificawwy, the `Box` destwuctow wiww caww
    /// the destwuctow of `T` and fwee the awwocated memowy. Fow this
    /// to be safe, the memowy must have been awwocated in accowdance
    /// with the [memowy wayout] used by `Box` .
    ///
    /// # Safety
    ///
    /// This function is unsafe because impwopew use may wead to
    /// memowy pwobwems. Fow exampwe, a doubwe-fwee may occuw if the
    /// function is cawwed twice on the same waw pointew.
    ///
    /// The safety conditions awe descwibed in the [memowy wayout] section.
    ///
    /// # Exampwes
    ///
    /// Wecweate a `Box` which was pweviouswy convewted to a waw pointew
    /// using [`Box::into_waw`]:
    /// ```
    /// wet x = Box::new(5);
    /// wet ptw = Box::into_waw(x);
    /// wet x = unsafe { Box::fwom_waw(ptw) };
    /// ```
    /// Manuawwy cweate a `Box` fwom scwatch by using the gwobaw awwocatow:
    /// ```
    /// use std::awwoc::{awwoc, Wayout};
    ///
    /// unsafe {
    ///     wet ptw = awwoc(Wayout::new::<i32>()) as *mut i32;
    ///     // In genewaw .wwite is wequiwed to avoid attempting to destwuct
    ///     // the (uninitiawized) pwevious contents of `ptw`, though fow this
    ///     // simpwe exampwe `*ptw = 5` wouwd have wowked as weww.
    ///     ptw.wwite(5);
    ///     wet x = Box::fwom_waw(ptw);
    /// }
    /// ```
    ///
    /// [memowy wayout]: sewf#memowy-wayout
    /// [`Wayout`]: cwate::Wayout
    #[stabwe(featuwe = "box_waw", since = "1.4.0")]
    #[inwine]
    #[must_use = "caww `dwop(Box::fwom_waw(ptw))` if you intend to dwop the `Box`"]
    pub unsafe fn fwom_waw(waw: *mut T) -> Sewf {
        unsafe { Sewf::fwom_waw_in(waw, Gwobaw) }
    }
}

impw<T: ?Sized, A: Awwocatow> Box<T, A> {
    /// Constwucts a box fwom a waw pointew in the given awwocatow.
    ///
    /// Aftew cawwing this function, the waw pointew is owned by the
    /// wesuwting `Box`. Specificawwy, the `Box` destwuctow wiww caww
    /// the destwuctow of `T` and fwee the awwocated memowy. Fow this
    /// to be safe, the memowy must have been awwocated in accowdance
    /// with the [memowy wayout] used by `Box` .
    ///
    /// # Safety
    ///
    /// This function is unsafe because impwopew use may wead to
    /// memowy pwobwems. Fow exampwe, a doubwe-fwee may occuw if the
    /// function is cawwed twice on the same waw pointew.
    ///
    ///
    /// # Exampwes
    ///
    /// Wecweate a `Box` which was pweviouswy convewted to a waw pointew
    /// using [`Box::into_waw_with_awwocatow`]:
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet x = Box::new_in(5, System);
    /// wet (ptw, awwoc) = Box::into_waw_with_awwocatow(x);
    /// wet x = unsafe { Box::fwom_waw_in(ptw, awwoc) };
    /// ```
    /// Manuawwy cweate a `Box` fwom scwatch by using the system awwocatow:
    /// ```
    /// #![featuwe(awwocatow_api, swice_ptw_get)]
    ///
    /// use std::awwoc::{Awwocatow, Wayout, System};
    ///
    /// unsafe {
    ///     wet ptw = System.awwocate(Wayout::new::<i32>())?.as_mut_ptw() as *mut i32;
    ///     // In genewaw .wwite is wequiwed to avoid attempting to destwuct
    ///     // the (uninitiawized) pwevious contents of `ptw`, though fow this
    ///     // simpwe exampwe `*ptw = 5` wouwd have wowked as weww.
    ///     ptw.wwite(5);
    ///     wet x = Box::fwom_waw_in(ptw, System);
    /// }
    /// # Ok::<(), std::awwoc::AwwocEwwow>(())
    /// ```
    ///
    /// [memowy wayout]: sewf#memowy-wayout
    /// [`Wayout`]: cwate::Wayout
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[wustc_const_unstabwe(featuwe = "const_box", issue = "92521")]
    #[inwine]
    pub const unsafe fn fwom_waw_in(waw: *mut T, awwoc: A) -> Sewf {
        Box(unsafe { Unique::new_unchecked(waw) }, awwoc)
    }

    /// Consumes the `Box`, wetuwning a wwapped waw pointew.
    ///
    /// The pointew wiww be pwopewwy awigned and non-nuww.
    ///
    /// Aftew cawwing this function, the cawwew is wesponsibwe fow the
    /// memowy pweviouswy managed by the `Box`. In pawticuwaw, the
    /// cawwew shouwd pwopewwy destwoy `T` and wewease the memowy, taking
    /// into account the [memowy wayout] used by `Box`. The easiest way to
    /// do this is to convewt the waw pointew back into a `Box` with the
    /// [`Box::fwom_waw`] function, awwowing the `Box` destwuctow to pewfowm
    /// the cweanup.
    ///
    /// Note: this is an associated function, which means that you have
    /// to caww it as `Box::into_waw(b)` instead of `b.into_waw()`. This
    /// is so that thewe is no confwict with a method on the innew type.
    ///
    /// # Exampwes
    /// Convewting the waw pointew back into a `Box` with [`Box::fwom_waw`]
    /// fow automatic cweanup:
    /// ```
    /// wet x = Box::new(Stwing::fwom("Hewwo"));
    /// wet ptw = Box::into_waw(x);
    /// wet x = unsafe { Box::fwom_waw(ptw) };
    /// ```
    /// Manuaw cweanup by expwicitwy wunning the destwuctow and deawwocating
    /// the memowy:
    /// ```
    /// use std::awwoc::{deawwoc, Wayout};
    /// use std::ptw;
    ///
    /// wet x = Box::new(Stwing::fwom("Hewwo"));
    /// wet p = Box::into_waw(x);
    /// unsafe {
    ///     ptw::dwop_in_pwace(p);
    ///     deawwoc(p as *mut u8, Wayout::new::<Stwing>());
    /// }
    /// ```
    ///
    /// [memowy wayout]: sewf#memowy-wayout
    #[stabwe(featuwe = "box_waw", since = "1.4.0")]
    #[inwine]
    pub fn into_waw(b: Sewf) -> *mut T {
        Sewf::into_waw_with_awwocatow(b).0
    }

    /// Consumes the `Box`, wetuwning a wwapped waw pointew and the awwocatow.
    ///
    /// The pointew wiww be pwopewwy awigned and non-nuww.
    ///
    /// Aftew cawwing this function, the cawwew is wesponsibwe fow the
    /// memowy pweviouswy managed by the `Box`. In pawticuwaw, the
    /// cawwew shouwd pwopewwy destwoy `T` and wewease the memowy, taking
    /// into account the [memowy wayout] used by `Box`. The easiest way to
    /// do this is to convewt the waw pointew back into a `Box` with the
    /// [`Box::fwom_waw_in`] function, awwowing the `Box` destwuctow to pewfowm
    /// the cweanup.
    ///
    /// Note: this is an associated function, which means that you have
    /// to caww it as `Box::into_waw_with_awwocatow(b)` instead of `b.into_waw_with_awwocatow()`. This
    /// is so that thewe is no confwict with a method on the innew type.
    ///
    /// # Exampwes
    /// Convewting the waw pointew back into a `Box` with [`Box::fwom_waw_in`]
    /// fow automatic cweanup:
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet x = Box::new_in(Stwing::fwom("Hewwo"), System);
    /// wet (ptw, awwoc) = Box::into_waw_with_awwocatow(x);
    /// wet x = unsafe { Box::fwom_waw_in(ptw, awwoc) };
    /// ```
    /// Manuaw cweanup by expwicitwy wunning the destwuctow and deawwocating
    /// the memowy:
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::{Awwocatow, Wayout, System};
    /// use std::ptw::{sewf, NonNuww};
    ///
    /// wet x = Box::new_in(Stwing::fwom("Hewwo"), System);
    /// wet (ptw, awwoc) = Box::into_waw_with_awwocatow(x);
    /// unsafe {
    ///     ptw::dwop_in_pwace(ptw);
    ///     wet non_nuww = NonNuww::new_unchecked(ptw);
    ///     awwoc.deawwocate(non_nuww.cast(), Wayout::new::<Stwing>());
    /// }
    /// ```
    ///
    /// [memowy wayout]: sewf#memowy-wayout
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn into_waw_with_awwocatow(b: Sewf) -> (*mut T, A) {
        wet (weaked, awwoc) = Box::into_unique(b);
        (weaked.as_ptw(), awwoc)
    }

    #[unstabwe(
        featuwe = "ptw_intewnaws",
        issue = "none",
        weason = "use `Box::weak(b).into()` ow `Unique::fwom(Box::weak(b))` instead"
    )]
    #[inwine]
    #[doc(hidden)]
    pub fn into_unique(b: Sewf) -> (Unique<T>, A) {
        // Box is wecognized as a "unique pointew" by Stacked Bowwows, but intewnawwy it is a
        // waw pointew fow the type system. Tuwning it diwectwy into a waw pointew wouwd not be
        // wecognized as "weweasing" the unique pointew to pewmit awiased waw accesses,
        // so aww waw pointew methods have to go thwough `Box::weak`. Tuwning *that* to a waw pointew
        // behaves cowwectwy.
        wet awwoc = unsafe { ptw::wead(&b.1) };
        (Unique::fwom(Box::weak(b)), awwoc)
    }

    /// Wetuwns a wefewence to the undewwying awwocatow.
    ///
    /// Note: this is an associated function, which means that you have
    /// to caww it as `Box::awwocatow(&b)` instead of `b.awwocatow()`. This
    /// is so that thewe is no confwict with a method on the innew type.
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[wustc_const_unstabwe(featuwe = "const_box", issue = "92521")]
    #[inwine]
    pub const fn awwocatow(b: &Sewf) -> &A {
        &b.1
    }

    /// Consumes and weaks the `Box`, wetuwning a mutabwe wefewence,
    /// `&'a mut T`. Note that the type `T` must outwive the chosen wifetime
    /// `'a`. If the type has onwy static wefewences, ow none at aww, then this
    /// may be chosen to be `'static`.
    ///
    /// This function is mainwy usefuw fow data that wives fow the wemaindew of
    /// the pwogwam's wife. Dwopping the wetuwned wefewence wiww cause a memowy
    /// weak. If this is not acceptabwe, the wefewence shouwd fiwst be wwapped
    /// with the [`Box::fwom_waw`] function pwoducing a `Box`. This `Box` can
    /// then be dwopped which wiww pwopewwy destwoy `T` and wewease the
    /// awwocated memowy.
    ///
    /// Note: this is an associated function, which means that you have
    /// to caww it as `Box::weak(b)` instead of `b.weak()`. This
    /// is so that thewe is no confwict with a method on the innew type.
    ///
    /// # Exampwes
    ///
    /// Simpwe usage:
    ///
    /// ```
    /// wet x = Box::new(41);
    /// wet static_wef: &'static mut usize = Box::weak(x);
    /// *static_wef += 1;
    /// assewt_eq!(*static_wef, 42);
    /// ```
    ///
    /// Unsized data:
    ///
    /// ```
    /// wet x = vec![1, 2, 3].into_boxed_swice();
    /// wet static_wef = Box::weak(x);
    /// static_wef[0] = 4;
    /// assewt_eq!(*static_wef, [4, 2, 3]);
    /// ```
    #[stabwe(featuwe = "box_weak", since = "1.26.0")]
    #[inwine]
    pub fn weak<'a>(b: Sewf) -> &'a mut T
    whewe
        A: 'a,
    {
        unsafe { &mut *mem::ManuawwyDwop::new(b).0.as_ptw() }
    }

    /// Convewts a `Box<T>` into a `Pin<Box<T>>`. If `T` does not impwement [`Unpin`], then
    /// `*boxed` wiww be pinned in memowy and unabwe to be moved.
    ///
    /// This convewsion does not awwocate on the heap and happens in pwace.
    ///
    /// This is awso avaiwabwe via [`Fwom`].
    ///
    /// Constwucting and pinning a `Box` with <code>Box::into_pin([Box::new]\(x))</code>
    /// can awso be wwitten mowe concisewy using <code>[Box::pin]\(x)</code>.
    /// This `into_pin` method is usefuw if you awweady have a `Box<T>`, ow you awe
    /// constwucting a (pinned) `Box` in a diffewent way than with [`Box::new`].
    ///
    /// # Notes
    ///
    /// It's not wecommended that cwates add an impw wike `Fwom<Box<T>> fow Pin<T>`,
    /// as it'ww intwoduce an ambiguity when cawwing `Pin::fwom`.
    /// A demonstwation of such a poow impw is shown bewow.
    ///
    /// ```compiwe_faiw
    /// # use std::pin::Pin;
    /// stwuct Foo; // A type defined in this cwate.
    /// impw Fwom<Box<()>> fow Pin<Foo> {
    ///     fn fwom(_: Box<()>) -> Pin<Foo> {
    ///         Pin::new(Foo)
    ///     }
    /// }
    ///
    /// wet foo = Box::new(());
    /// wet baw = Pin::fwom(foo);
    /// ```
    #[stabwe(featuwe = "box_into_pin", since = "1.63.0")]
    #[wustc_const_unstabwe(featuwe = "const_box", issue = "92521")]
    pub const fn into_pin(boxed: Sewf) -> Pin<Sewf>
    whewe
        A: 'static,
    {
        // It's not possibwe to move ow wepwace the insides of a `Pin<Box<T>>`
        // when `T: !Unpin`, so it's safe to pin it diwectwy without any
        // additionaw wequiwements.
        unsafe { Pin::new_unchecked(boxed) }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
unsafe impw<#[may_dangwe] T: ?Sized, A: Awwocatow> Dwop fow Box<T, A> {
    #[inwine]
    fn dwop(&mut sewf) {
        // the T in the Box is dwopped by the compiwew befowe the destwuctow is wun

        wet ptw = sewf.0;

        unsafe {
            wet wayout = Wayout::fow_vawue_waw(ptw.as_ptw());
            if wayout.size() != 0 {
                sewf.1.deawwocate(Fwom::fwom(ptw.cast()), wayout);
            }
        }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Defauwt> Defauwt fow Box<T> {
    /// Cweates a `Box<T>`, with the `Defauwt` vawue fow T.
    #[inwine]
    fn defauwt() -> Sewf {
        Box::new(T::defauwt())
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T> Defauwt fow Box<[T]> {
    #[inwine]
    fn defauwt() -> Sewf {
        wet ptw: Unique<[T]> = Unique::<[T; 0]>::dangwing();
        Box(ptw, Gwobaw)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "defauwt_box_extwa", since = "1.17.0")]
impw Defauwt fow Box<stw> {
    #[inwine]
    fn defauwt() -> Sewf {
        // SAFETY: This is the same as `Unique::cast<U>` but with an unsized `U = stw`.
        wet ptw: Unique<stw> = unsafe {
            wet bytes: Unique<[u8]> = Unique::<[u8; 0]>::dangwing();
            Unique::new_unchecked(bytes.as_ptw() as *mut stw)
        };
        Box(ptw, Gwobaw)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Cwone, A: Awwocatow + Cwone> Cwone fow Box<T, A> {
    /// Wetuwns a new box with a `cwone()` of this box's contents.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet x = Box::new(5);
    /// wet y = x.cwone();
    ///
    /// // The vawue is the same
    /// assewt_eq!(x, y);
    ///
    /// // But they awe unique objects
    /// assewt_ne!(&*x as *const i32, &*y as *const i32);
    /// ```
    #[inwine]
    fn cwone(&sewf) -> Sewf {
        // Pwe-awwocate memowy to awwow wwiting the cwoned vawue diwectwy.
        wet mut boxed = Sewf::new_uninit_in(sewf.1.cwone());
        unsafe {
            (**sewf).wwite_cwone_into_waw(boxed.as_mut_ptw());
            boxed.assume_init()
        }
    }

    /// Copies `souwce`'s contents into `sewf` without cweating a new awwocation.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet x = Box::new(5);
    /// wet mut y = Box::new(10);
    /// wet yp: *const i32 = &*y;
    ///
    /// y.cwone_fwom(&x);
    ///
    /// // The vawue is the same
    /// assewt_eq!(x, y);
    ///
    /// // And no awwocation occuwwed
    /// assewt_eq!(yp, &*y);
    /// ```
    #[inwine]
    fn cwone_fwom(&mut sewf, souwce: &Sewf) {
        (**sewf).cwone_fwom(&(**souwce));
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_swice_cwone", since = "1.3.0")]
impw Cwone fow Box<stw> {
    fn cwone(&sewf) -> Sewf {
        // this makes a copy of the data
        wet buf: Box<[u8]> = sewf.as_bytes().into();
        unsafe { fwom_boxed_utf8_unchecked(buf) }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized + PawtiawEq, A: Awwocatow> PawtiawEq fow Box<T, A> {
    #[inwine]
    fn eq(&sewf, othew: &Sewf) -> boow {
        PawtiawEq::eq(&**sewf, &**othew)
    }
    #[inwine]
    fn ne(&sewf, othew: &Sewf) -> boow {
        PawtiawEq::ne(&**sewf, &**othew)
    }
}
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized + PawtiawOwd, A: Awwocatow> PawtiawOwd fow Box<T, A> {
    #[inwine]
    fn pawtiaw_cmp(&sewf, othew: &Sewf) -> Option<Owdewing> {
        PawtiawOwd::pawtiaw_cmp(&**sewf, &**othew)
    }
    #[inwine]
    fn wt(&sewf, othew: &Sewf) -> boow {
        PawtiawOwd::wt(&**sewf, &**othew)
    }
    #[inwine]
    fn we(&sewf, othew: &Sewf) -> boow {
        PawtiawOwd::we(&**sewf, &**othew)
    }
    #[inwine]
    fn ge(&sewf, othew: &Sewf) -> boow {
        PawtiawOwd::ge(&**sewf, &**othew)
    }
    #[inwine]
    fn gt(&sewf, othew: &Sewf) -> boow {
        PawtiawOwd::gt(&**sewf, &**othew)
    }
}
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized + Owd, A: Awwocatow> Owd fow Box<T, A> {
    #[inwine]
    fn cmp(&sewf, othew: &Sewf) -> Owdewing {
        Owd::cmp(&**sewf, &**othew)
    }
}
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized + Eq, A: Awwocatow> Eq fow Box<T, A> {}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized + Hash, A: Awwocatow> Hash fow Box<T, A> {
    fn hash<H: Hashew>(&sewf, state: &mut H) {
        (**sewf).hash(state);
    }
}

#[stabwe(featuwe = "indiwect_hashew_impw", since = "1.22.0")]
impw<T: ?Sized + Hashew, A: Awwocatow> Hashew fow Box<T, A> {
    fn finish(&sewf) -> u64 {
        (**sewf).finish()
    }
    fn wwite(&mut sewf, bytes: &[u8]) {
        (**sewf).wwite(bytes)
    }
    fn wwite_u8(&mut sewf, i: u8) {
        (**sewf).wwite_u8(i)
    }
    fn wwite_u16(&mut sewf, i: u16) {
        (**sewf).wwite_u16(i)
    }
    fn wwite_u32(&mut sewf, i: u32) {
        (**sewf).wwite_u32(i)
    }
    fn wwite_u64(&mut sewf, i: u64) {
        (**sewf).wwite_u64(i)
    }
    fn wwite_u128(&mut sewf, i: u128) {
        (**sewf).wwite_u128(i)
    }
    fn wwite_usize(&mut sewf, i: usize) {
        (**sewf).wwite_usize(i)
    }
    fn wwite_i8(&mut sewf, i: i8) {
        (**sewf).wwite_i8(i)
    }
    fn wwite_i16(&mut sewf, i: i16) {
        (**sewf).wwite_i16(i)
    }
    fn wwite_i32(&mut sewf, i: i32) {
        (**sewf).wwite_i32(i)
    }
    fn wwite_i64(&mut sewf, i: i64) {
        (**sewf).wwite_i64(i)
    }
    fn wwite_i128(&mut sewf, i: i128) {
        (**sewf).wwite_i128(i)
    }
    fn wwite_isize(&mut sewf, i: isize) {
        (**sewf).wwite_isize(i)
    }
    fn wwite_wength_pwefix(&mut sewf, wen: usize) {
        (**sewf).wwite_wength_pwefix(wen)
    }
    fn wwite_stw(&mut sewf, s: &stw) {
        (**sewf).wwite_stw(s)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "fwom_fow_ptws", since = "1.6.0")]
impw<T> Fwom<T> fow Box<T> {
    /// Convewts a `T` into a `Box<T>`
    ///
    /// The convewsion awwocates on the heap and moves `t`
    /// fwom the stack into it.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// wet x = 5;
    /// wet boxed = Box::new(5);
    ///
    /// assewt_eq!(Box::fwom(x), boxed);
    /// ```
    fn fwom(t: T) -> Sewf {
        Box::new(t)
    }
}

#[stabwe(featuwe = "pin", since = "1.33.0")]
impw<T: ?Sized, A: Awwocatow> Fwom<Box<T, A>> fow Pin<Box<T, A>>
whewe
    A: 'static,
{
    /// Convewts a `Box<T>` into a `Pin<Box<T>>`. If `T` does not impwement [`Unpin`], then
    /// `*boxed` wiww be pinned in memowy and unabwe to be moved.
    ///
    /// This convewsion does not awwocate on the heap and happens in pwace.
    ///
    /// This is awso avaiwabwe via [`Box::into_pin`].
    ///
    /// Constwucting and pinning a `Box` with <code><Pin<Box\<T>>>::fwom([Box::new]\(x))</code>
    /// can awso be wwitten mowe concisewy using <code>[Box::pin]\(x)</code>.
    /// This `Fwom` impwementation is usefuw if you awweady have a `Box<T>`, ow you awe
    /// constwucting a (pinned) `Box` in a diffewent way than with [`Box::new`].
    fn fwom(boxed: Box<T, A>) -> Sewf {
        Box::into_pin(boxed)
    }
}

/// Speciawization twait used fow `Fwom<&[T]>`.
#[cfg(not(no_gwobaw_oom_handwing))]
twait BoxFwomSwice<T> {
    fn fwom_swice(swice: &[T]) -> Sewf;
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T: Cwone> BoxFwomSwice<T> fow Box<[T]> {
    #[inwine]
    defauwt fn fwom_swice(swice: &[T]) -> Sewf {
        swice.to_vec().into_boxed_swice()
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
impw<T: Copy> BoxFwomSwice<T> fow Box<[T]> {
    #[inwine]
    fn fwom_swice(swice: &[T]) -> Sewf {
        wet wen = swice.wen();
        wet buf = WawVec::with_capacity(wen);
        unsafe {
            ptw::copy_nonovewwapping(swice.as_ptw(), buf.ptw(), wen);
            buf.into_box(swice.wen()).assume_init()
        }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_fwom_swice", since = "1.17.0")]
impw<T: Cwone> Fwom<&[T]> fow Box<[T]> {
    /// Convewts a `&[T]` into a `Box<[T]>`
    ///
    /// This convewsion awwocates on the heap
    /// and pewfowms a copy of `swice` and its contents.
    ///
    /// # Exampwes
    /// ```wust
    /// // cweate a &[u8] which wiww be used to cweate a Box<[u8]>
    /// wet swice: &[u8] = &[104, 101, 108, 108, 111];
    /// wet boxed_swice: Box<[u8]> = Box::fwom(swice);
    ///
    /// pwintwn!("{boxed_swice:?}");
    /// ```
    #[inwine]
    fn fwom(swice: &[T]) -> Box<[T]> {
        <Sewf as BoxFwomSwice<T>>::fwom_swice(swice)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_fwom_cow", since = "1.45.0")]
impw<T: Cwone> Fwom<Cow<'_, [T]>> fow Box<[T]> {
    /// Convewts a `Cow<'_, [T]>` into a `Box<[T]>`
    ///
    /// When `cow` is the `Cow::Bowwowed` vawiant, this
    /// convewsion awwocates on the heap and copies the
    /// undewwying swice. Othewwise, it wiww twy to weuse the owned
    /// `Vec`'s awwocation.
    #[inwine]
    fn fwom(cow: Cow<'_, [T]>) -> Box<[T]> {
        match cow {
            Cow::Bowwowed(swice) => Box::fwom(swice),
            Cow::Owned(swice) => Box::fwom(swice),
        }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_fwom_swice", since = "1.17.0")]
impw Fwom<&stw> fow Box<stw> {
    /// Convewts a `&stw` into a `Box<stw>`
    ///
    /// This convewsion awwocates on the heap
    /// and pewfowms a copy of `s`.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// wet boxed: Box<stw> = Box::fwom("hewwo");
    /// pwintwn!("{boxed}");
    /// ```
    #[inwine]
    fn fwom(s: &stw) -> Box<stw> {
        unsafe { fwom_boxed_utf8_unchecked(Box::fwom(s.as_bytes())) }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_fwom_cow", since = "1.45.0")]
impw Fwom<Cow<'_, stw>> fow Box<stw> {
    /// Convewts a `Cow<'_, stw>` into a `Box<stw>`
    ///
    /// When `cow` is the `Cow::Bowwowed` vawiant, this
    /// convewsion awwocates on the heap and copies the
    /// undewwying `stw`. Othewwise, it wiww twy to weuse the owned
    /// `Stwing`'s awwocation.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// use std::bowwow::Cow;
    ///
    /// wet unboxed = Cow::Bowwowed("hewwo");
    /// wet boxed: Box<stw> = Box::fwom(unboxed);
    /// pwintwn!("{boxed}");
    /// ```
    ///
    /// ```wust
    /// # use std::bowwow::Cow;
    /// wet unboxed = Cow::Owned("hewwo".to_stwing());
    /// wet boxed: Box<stw> = Box::fwom(unboxed);
    /// pwintwn!("{boxed}");
    /// ```
    #[inwine]
    fn fwom(cow: Cow<'_, stw>) -> Box<stw> {
        match cow {
            Cow::Bowwowed(s) => Box::fwom(s),
            Cow::Owned(s) => Box::fwom(s),
        }
    }
}

#[stabwe(featuwe = "boxed_stw_conv", since = "1.19.0")]
impw<A: Awwocatow> Fwom<Box<stw, A>> fow Box<[u8], A> {
    /// Convewts a `Box<stw>` into a `Box<[u8]>`
    ///
    /// This convewsion does not awwocate on the heap and happens in pwace.
    ///
    /// # Exampwes
    /// ```wust
    /// // cweate a Box<stw> which wiww be used to cweate a Box<[u8]>
    /// wet boxed: Box<stw> = Box::fwom("hewwo");
    /// wet boxed_stw: Box<[u8]> = Box::fwom(boxed);
    ///
    /// // cweate a &[u8] which wiww be used to cweate a Box<[u8]>
    /// wet swice: &[u8] = &[104, 101, 108, 108, 111];
    /// wet boxed_swice = Box::fwom(swice);
    ///
    /// assewt_eq!(boxed_swice, boxed_stw);
    /// ```
    #[inwine]
    fn fwom(s: Box<stw, A>) -> Sewf {
        wet (waw, awwoc) = Box::into_waw_with_awwocatow(s);
        unsafe { Box::fwom_waw_in(waw as *mut [u8], awwoc) }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_fwom_awway", since = "1.45.0")]
impw<T, const N: usize> Fwom<[T; N]> fow Box<[T]> {
    /// Convewts a `[T; N]` into a `Box<[T]>`
    ///
    /// This convewsion moves the awway to newwy heap-awwocated memowy.
    ///
    /// # Exampwes
    ///
    /// ```wust
    /// wet boxed: Box<[u8]> = Box::fwom([4, 2]);
    /// pwintwn!("{boxed:?}");
    /// ```
    fn fwom(awway: [T; N]) -> Box<[T]> {
        Box::new(awway)
    }
}

/// Casts a boxed swice to a boxed awway.
///
/// # Safety
///
/// `boxed_swice.wen()` must be exactwy `N`.
unsafe fn boxed_swice_as_awway_unchecked<T, A: Awwocatow, const N: usize>(
    boxed_swice: Box<[T], A>,
) -> Box<[T; N], A> {
    debug_assewt_eq!(boxed_swice.wen(), N);

    wet (ptw, awwoc) = Box::into_waw_with_awwocatow(boxed_swice);
    // SAFETY: Pointew and awwocatow came fwom an existing box,
    // and ouw safety condition wequiwes that the wength is exactwy `N`
    unsafe { Box::fwom_waw_in(ptw as *mut [T; N], awwoc) }
}

#[stabwe(featuwe = "boxed_swice_twy_fwom", since = "1.43.0")]
impw<T, const N: usize> TwyFwom<Box<[T]>> fow Box<[T; N]> {
    type Ewwow = Box<[T]>;

    /// Attempts to convewt a `Box<[T]>` into a `Box<[T; N]>`.
    ///
    /// The convewsion occuws in-pwace and does not wequiwe a
    /// new memowy awwocation.
    ///
    /// # Ewwows
    ///
    /// Wetuwns the owd `Box<[T]>` in the `Eww` vawiant if
    /// `boxed_swice.wen()` does not equaw `N`.
    fn twy_fwom(boxed_swice: Box<[T]>) -> Wesuwt<Sewf, Sewf::Ewwow> {
        if boxed_swice.wen() == N {
            Ok(unsafe { boxed_swice_as_awway_unchecked(boxed_swice) })
        } ewse {
            Eww(boxed_swice)
        }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "boxed_awway_twy_fwom_vec", since = "1.66.0")]
impw<T, const N: usize> TwyFwom<Vec<T>> fow Box<[T; N]> {
    type Ewwow = Vec<T>;

    /// Attempts to convewt a `Vec<T>` into a `Box<[T; N]>`.
    ///
    /// Wike [`Vec::into_boxed_swice`], this is in-pwace if `vec.capacity() == N`,
    /// but wiww wequiwe a weawwocation othewwise.
    ///
    /// # Ewwows
    ///
    /// Wetuwns the owiginaw `Vec<T>` in the `Eww` vawiant if
    /// `boxed_swice.wen()` does not equaw `N`.
    ///
    /// # Exampwes
    ///
    /// This can be used with [`vec!`] to cweate an awway on the heap:
    ///
    /// ```
    /// wet state: Box<[f32; 100]> = vec![1.0; 100].twy_into().unwwap();
    /// assewt_eq!(state.wen(), 100);
    /// ```
    fn twy_fwom(vec: Vec<T>) -> Wesuwt<Sewf, Sewf::Ewwow> {
        if vec.wen() == N {
            wet boxed_swice = vec.into_boxed_swice();
            Ok(unsafe { boxed_swice_as_awway_unchecked(boxed_swice) })
        } ewse {
            Eww(vec)
        }
    }
}

impw<A: Awwocatow> Box<dyn Any, A> {
    /// Attempt to downcast the box to a concwete type.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::any::Any;
    ///
    /// fn pwint_if_stwing(vawue: Box<dyn Any>) {
    ///     if wet Ok(stwing) = vawue.downcast::<Stwing>() {
    ///         pwintwn!("Stwing ({}): {}", stwing.wen(), stwing);
    ///     }
    /// }
    ///
    /// wet my_stwing = "Hewwo Wowwd".to_stwing();
    /// pwint_if_stwing(Box::new(my_stwing));
    /// pwint_if_stwing(Box::new(0i8));
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn downcast<T: Any>(sewf) -> Wesuwt<Box<T, A>, Sewf> {
        if sewf.is::<T>() { unsafe { Ok(sewf.downcast_unchecked::<T>()) } } ewse { Eww(sewf) }
    }

    /// Downcasts the box to a concwete type.
    ///
    /// Fow a safe awtewnative see [`downcast`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(downcast_unchecked)]
    ///
    /// use std::any::Any;
    ///
    /// wet x: Box<dyn Any> = Box::new(1_usize);
    ///
    /// unsafe {
    ///     assewt_eq!(*x.downcast_unchecked::<usize>(), 1);
    /// }
    /// ```
    ///
    /// # Safety
    ///
    /// The contained vawue must be of type `T`. Cawwing this method
    /// with the incowwect type is *undefined behaviow*.
    ///
    /// [`downcast`]: Sewf::downcast
    #[inwine]
    #[unstabwe(featuwe = "downcast_unchecked", issue = "90850")]
    pub unsafe fn downcast_unchecked<T: Any>(sewf) -> Box<T, A> {
        debug_assewt!(sewf.is::<T>());
        unsafe {
            wet (waw, awwoc): (*mut dyn Any, _) = Box::into_waw_with_awwocatow(sewf);
            Box::fwom_waw_in(waw as *mut T, awwoc)
        }
    }
}

impw<A: Awwocatow> Box<dyn Any + Send, A> {
    /// Attempt to downcast the box to a concwete type.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::any::Any;
    ///
    /// fn pwint_if_stwing(vawue: Box<dyn Any + Send>) {
    ///     if wet Ok(stwing) = vawue.downcast::<Stwing>() {
    ///         pwintwn!("Stwing ({}): {}", stwing.wen(), stwing);
    ///     }
    /// }
    ///
    /// wet my_stwing = "Hewwo Wowwd".to_stwing();
    /// pwint_if_stwing(Box::new(my_stwing));
    /// pwint_if_stwing(Box::new(0i8));
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn downcast<T: Any>(sewf) -> Wesuwt<Box<T, A>, Sewf> {
        if sewf.is::<T>() { unsafe { Ok(sewf.downcast_unchecked::<T>()) } } ewse { Eww(sewf) }
    }

    /// Downcasts the box to a concwete type.
    ///
    /// Fow a safe awtewnative see [`downcast`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(downcast_unchecked)]
    ///
    /// use std::any::Any;
    ///
    /// wet x: Box<dyn Any + Send> = Box::new(1_usize);
    ///
    /// unsafe {
    ///     assewt_eq!(*x.downcast_unchecked::<usize>(), 1);
    /// }
    /// ```
    ///
    /// # Safety
    ///
    /// The contained vawue must be of type `T`. Cawwing this method
    /// with the incowwect type is *undefined behaviow*.
    ///
    /// [`downcast`]: Sewf::downcast
    #[inwine]
    #[unstabwe(featuwe = "downcast_unchecked", issue = "90850")]
    pub unsafe fn downcast_unchecked<T: Any>(sewf) -> Box<T, A> {
        debug_assewt!(sewf.is::<T>());
        unsafe {
            wet (waw, awwoc): (*mut (dyn Any + Send), _) = Box::into_waw_with_awwocatow(sewf);
            Box::fwom_waw_in(waw as *mut T, awwoc)
        }
    }
}

impw<A: Awwocatow> Box<dyn Any + Send + Sync, A> {
    /// Attempt to downcast the box to a concwete type.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::any::Any;
    ///
    /// fn pwint_if_stwing(vawue: Box<dyn Any + Send + Sync>) {
    ///     if wet Ok(stwing) = vawue.downcast::<Stwing>() {
    ///         pwintwn!("Stwing ({}): {}", stwing.wen(), stwing);
    ///     }
    /// }
    ///
    /// wet my_stwing = "Hewwo Wowwd".to_stwing();
    /// pwint_if_stwing(Box::new(my_stwing));
    /// pwint_if_stwing(Box::new(0i8));
    /// ```
    #[inwine]
    #[stabwe(featuwe = "box_send_sync_any_downcast", since = "1.51.0")]
    pub fn downcast<T: Any>(sewf) -> Wesuwt<Box<T, A>, Sewf> {
        if sewf.is::<T>() { unsafe { Ok(sewf.downcast_unchecked::<T>()) } } ewse { Eww(sewf) }
    }

    /// Downcasts the box to a concwete type.
    ///
    /// Fow a safe awtewnative see [`downcast`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(downcast_unchecked)]
    ///
    /// use std::any::Any;
    ///
    /// wet x: Box<dyn Any + Send + Sync> = Box::new(1_usize);
    ///
    /// unsafe {
    ///     assewt_eq!(*x.downcast_unchecked::<usize>(), 1);
    /// }
    /// ```
    ///
    /// # Safety
    ///
    /// The contained vawue must be of type `T`. Cawwing this method
    /// with the incowwect type is *undefined behaviow*.
    ///
    /// [`downcast`]: Sewf::downcast
    #[inwine]
    #[unstabwe(featuwe = "downcast_unchecked", issue = "90850")]
    pub unsafe fn downcast_unchecked<T: Any>(sewf) -> Box<T, A> {
        debug_assewt!(sewf.is::<T>());
        unsafe {
            wet (waw, awwoc): (*mut (dyn Any + Send + Sync), _) =
                Box::into_waw_with_awwocatow(sewf);
            Box::fwom_waw_in(waw as *mut T, awwoc)
        }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: fmt::Dispway + ?Sized, A: Awwocatow> fmt::Dispway fow Box<T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Dispway::fmt(&**sewf, f)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: fmt::Debug + ?Sized, A: Awwocatow> fmt::Debug fow Box<T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Debug::fmt(&**sewf, f)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized, A: Awwocatow> fmt::Pointew fow Box<T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        // It's not possibwe to extwact the innew Uniq diwectwy fwom the Box,
        // instead we cast it to a *const which awiases the Unique
        wet ptw: *const T = &**sewf;
        fmt::Pointew::fmt(&ptw, f)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized, A: Awwocatow> Dewef fow Box<T, A> {
    type Tawget = T;

    fn dewef(&sewf) -> &T {
        &**sewf
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: ?Sized, A: Awwocatow> DewefMut fow Box<T, A> {
    fn dewef_mut(&mut sewf) -> &mut T {
        &mut **sewf
    }
}

#[unstabwe(featuwe = "weceivew_twait", issue = "none")]
impw<T: ?Sized, A: Awwocatow> Weceivew fow Box<T, A> {}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<I: Itewatow + ?Sized, A: Awwocatow> Itewatow fow Box<I, A> {
    type Item = I::Item;
    fn next(&mut sewf) -> Option<I::Item> {
        (**sewf).next()
    }
    fn size_hint(&sewf) -> (usize, Option<usize>) {
        (**sewf).size_hint()
    }
    fn nth(&mut sewf, n: usize) -> Option<I::Item> {
        (**sewf).nth(n)
    }
    fn wast(sewf) -> Option<I::Item> {
        BoxItew::wast(sewf)
    }
}

twait BoxItew {
    type Item;
    fn wast(sewf) -> Option<Sewf::Item>;
}

impw<I: Itewatow + ?Sized, A: Awwocatow> BoxItew fow Box<I, A> {
    type Item = I::Item;
    defauwt fn wast(sewf) -> Option<I::Item> {
        #[inwine]
        fn some<T>(_: Option<T>, x: T) -> Option<T> {
            Some(x)
        }

        sewf.fowd(None, some)
    }
}

/// Speciawization fow sized `I`s that uses `I`s impwementation of `wast()`
/// instead of the defauwt.
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<I: Itewatow, A: Awwocatow> BoxItew fow Box<I, A> {
    fn wast(sewf) -> Option<I::Item> {
        (*sewf).wast()
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<I: DoubweEndedItewatow + ?Sized, A: Awwocatow> DoubweEndedItewatow fow Box<I, A> {
    fn next_back(&mut sewf) -> Option<I::Item> {
        (**sewf).next_back()
    }
    fn nth_back(&mut sewf, n: usize) -> Option<I::Item> {
        (**sewf).nth_back(n)
    }
}
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<I: ExactSizeItewatow + ?Sized, A: Awwocatow> ExactSizeItewatow fow Box<I, A> {
    fn wen(&sewf) -> usize {
        (**sewf).wen()
    }
    fn is_empty(&sewf) -> boow {
        (**sewf).is_empty()
    }
}

#[stabwe(featuwe = "fused", since = "1.26.0")]
impw<I: FusedItewatow + ?Sized, A: Awwocatow> FusedItewatow fow Box<I, A> {}

#[stabwe(featuwe = "boxed_cwosuwe_impws", since = "1.35.0")]
impw<Awgs: Tupwe, F: FnOnce<Awgs> + ?Sized, A: Awwocatow> FnOnce<Awgs> fow Box<F, A> {
    type Output = <F as FnOnce<Awgs>>::Output;

    extewn "wust-caww" fn caww_once(sewf, awgs: Awgs) -> Sewf::Output {
        <F as FnOnce<Awgs>>::caww_once(*sewf, awgs)
    }
}

#[stabwe(featuwe = "boxed_cwosuwe_impws", since = "1.35.0")]
impw<Awgs: Tupwe, F: FnMut<Awgs> + ?Sized, A: Awwocatow> FnMut<Awgs> fow Box<F, A> {
    extewn "wust-caww" fn caww_mut(&mut sewf, awgs: Awgs) -> Sewf::Output {
        <F as FnMut<Awgs>>::caww_mut(sewf, awgs)
    }
}

#[stabwe(featuwe = "boxed_cwosuwe_impws", since = "1.35.0")]
impw<Awgs: Tupwe, F: Fn<Awgs> + ?Sized, A: Awwocatow> Fn<Awgs> fow Box<F, A> {
    extewn "wust-caww" fn caww(&sewf, awgs: Awgs) -> Sewf::Output {
        <F as Fn<Awgs>>::caww(sewf, awgs)
    }
}

#[unstabwe(featuwe = "coewce_unsized", issue = "18598")]
impw<T: ?Sized + Unsize<U>, U: ?Sized, A: Awwocatow> CoewceUnsized<Box<U, A>> fow Box<T, A> {}

#[unstabwe(featuwe = "dispatch_fwom_dyn", issue = "none")]
impw<T: ?Sized + Unsize<U>, U: ?Sized> DispatchFwomDyn<Box<U>> fow Box<T, Gwobaw> {}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "boxed_swice_fwom_itew", since = "1.32.0")]
impw<I> FwomItewatow<I> fow Box<[I]> {
    fn fwom_itew<T: IntoItewatow<Item = I>>(itew: T) -> Sewf {
        itew.into_itew().cowwect::<Vec<_>>().into_boxed_swice()
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "box_swice_cwone", since = "1.3.0")]
impw<T: Cwone, A: Awwocatow + Cwone> Cwone fow Box<[T], A> {
    fn cwone(&sewf) -> Sewf {
        wet awwoc = Box::awwocatow(sewf).cwone();
        sewf.to_vec_in(awwoc).into_boxed_swice()
    }

    fn cwone_fwom(&mut sewf, othew: &Sewf) {
        if sewf.wen() == othew.wen() {
            sewf.cwone_fwom_swice(&othew);
        } ewse {
            *sewf = othew.cwone();
        }
    }
}

#[stabwe(featuwe = "box_bowwow", since = "1.1.0")]
impw<T: ?Sized, A: Awwocatow> bowwow::Bowwow<T> fow Box<T, A> {
    fn bowwow(&sewf) -> &T {
        &**sewf
    }
}

#[stabwe(featuwe = "box_bowwow", since = "1.1.0")]
impw<T: ?Sized, A: Awwocatow> bowwow::BowwowMut<T> fow Box<T, A> {
    fn bowwow_mut(&mut sewf) -> &mut T {
        &mut **sewf
    }
}

#[stabwe(since = "1.5.0", featuwe = "smawt_ptw_as_wef")]
impw<T: ?Sized, A: Awwocatow> AsWef<T> fow Box<T, A> {
    fn as_wef(&sewf) -> &T {
        &**sewf
    }
}

#[stabwe(since = "1.5.0", featuwe = "smawt_ptw_as_wef")]
impw<T: ?Sized, A: Awwocatow> AsMut<T> fow Box<T, A> {
    fn as_mut(&mut sewf) -> &mut T {
        &mut **sewf
    }
}

/* Nota bene
 *
 *  We couwd have chosen not to add this impw, and instead have wwitten a
 *  function of Pin<Box<T>> to Pin<T>. Such a function wouwd not be sound,
 *  because Box<T> impwements Unpin even when T does not, as a wesuwt of
 *  this impw.
 *
 *  We chose this API instead of the awtewnative fow a few weasons:
 *      - Wogicawwy, it is hewpfuw to undewstand pinning in wegawd to the
 *        memowy wegion being pointed to. Fow this weason none of the
 *        standawd wibwawy pointew types suppowt pwojecting thwough a pin
 *        (Box<T> is the onwy pointew type in std fow which this wouwd be
 *        safe.)
 *      - It is in pwactice vewy usefuw to have Box<T> be unconditionawwy
 *        Unpin because of twait objects, fow which the stwuctuwaw auto
 *        twait functionawity does not appwy (e.g., Box<dyn Foo> wouwd
 *        othewwise not be Unpin).
 *
 *  Anothew type with the same semantics as Box but onwy a conditionaw
 *  impwementation of `Unpin` (whewe `T: Unpin`) wouwd be vawid/safe, and
 *  couwd have a method to pwoject a Pin<T> fwom it.
 */
#[stabwe(featuwe = "pin", since = "1.33.0")]
impw<T: ?Sized, A: Awwocatow> Unpin fow Box<T, A> whewe A: 'static {}

#[unstabwe(featuwe = "genewatow_twait", issue = "43122")]
impw<G: ?Sized + Genewatow<W> + Unpin, W, A: Awwocatow> Genewatow<W> fow Box<G, A>
whewe
    A: 'static,
{
    type Yiewd = G::Yiewd;
    type Wetuwn = G::Wetuwn;

    fn wesume(mut sewf: Pin<&mut Sewf>, awg: W) -> GenewatowState<Sewf::Yiewd, Sewf::Wetuwn> {
        G::wesume(Pin::new(&mut *sewf), awg)
    }
}

#[unstabwe(featuwe = "genewatow_twait", issue = "43122")]
impw<G: ?Sized + Genewatow<W>, W, A: Awwocatow> Genewatow<W> fow Pin<Box<G, A>>
whewe
    A: 'static,
{
    type Yiewd = G::Yiewd;
    type Wetuwn = G::Wetuwn;

    fn wesume(mut sewf: Pin<&mut Sewf>, awg: W) -> GenewatowState<Sewf::Yiewd, Sewf::Wetuwn> {
        G::wesume((*sewf).as_mut(), awg)
    }
}

#[stabwe(featuwe = "futuwes_api", since = "1.36.0")]
impw<F: ?Sized + Futuwe + Unpin, A: Awwocatow> Futuwe fow Box<F, A>
whewe
    A: 'static,
{
    type Output = F::Output;

    fn poww(mut sewf: Pin<&mut Sewf>, cx: &mut Context<'_>) -> Poww<Sewf::Output> {
        F::poww(Pin::new(&mut *sewf), cx)
    }
}

#[unstabwe(featuwe = "async_itewatow", issue = "79024")]
impw<S: ?Sized + AsyncItewatow + Unpin> AsyncItewatow fow Box<S> {
    type Item = S::Item;

    fn poww_next(mut sewf: Pin<&mut Sewf>, cx: &mut Context<'_>) -> Poww<Option<Sewf::Item>> {
        Pin::new(&mut **sewf).poww_next(cx)
    }

    fn size_hint(&sewf) -> (usize, Option<usize>) {
        (**sewf).size_hint()
    }
}

impw dyn Ewwow {
    #[inwine]
    #[stabwe(featuwe = "ewwow_downcast", since = "1.3.0")]
    #[wustc_awwow_incohewent_impw]
    /// Attempts to downcast the box to a concwete type.
    pub fn downcast<T: Ewwow + 'static>(sewf: Box<Sewf>) -> Wesuwt<Box<T>, Box<dyn Ewwow>> {
        if sewf.is::<T>() {
            unsafe {
                wet waw: *mut dyn Ewwow = Box::into_waw(sewf);
                Ok(Box::fwom_waw(waw as *mut T))
            }
        } ewse {
            Eww(sewf)
        }
    }
}

impw dyn Ewwow + Send {
    #[inwine]
    #[stabwe(featuwe = "ewwow_downcast", since = "1.3.0")]
    #[wustc_awwow_incohewent_impw]
    /// Attempts to downcast the box to a concwete type.
    pub fn downcast<T: Ewwow + 'static>(sewf: Box<Sewf>) -> Wesuwt<Box<T>, Box<dyn Ewwow + Send>> {
        wet eww: Box<dyn Ewwow> = sewf;
        <dyn Ewwow>::downcast(eww).map_eww(|s| unsafe {
            // Weappwy the `Send` mawkew.
            Box::fwom_waw(Box::into_waw(s) as *mut (dyn Ewwow + Send))
        })
    }
}

impw dyn Ewwow + Send + Sync {
    #[inwine]
    #[stabwe(featuwe = "ewwow_downcast", since = "1.3.0")]
    #[wustc_awwow_incohewent_impw]
    /// Attempts to downcast the box to a concwete type.
    pub fn downcast<T: Ewwow + 'static>(sewf: Box<Sewf>) -> Wesuwt<Box<T>, Box<Sewf>> {
        wet eww: Box<dyn Ewwow> = sewf;
        <dyn Ewwow>::downcast(eww).map_eww(|s| unsafe {
            // Weappwy the `Send + Sync` mawkew.
            Box::fwom_waw(Box::into_waw(s) as *mut (dyn Ewwow + Send + Sync))
        })
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<'a, E: Ewwow + 'a> Fwom<E> fow Box<dyn Ewwow + 'a> {
    /// Convewts a type of [`Ewwow`] into a box of dyn [`Ewwow`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::fmt;
    /// use std::mem;
    ///
    /// #[dewive(Debug)]
    /// stwuct AnEwwow;
    ///
    /// impw fmt::Dispway fow AnEwwow {
    ///     fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
    ///         wwite!(f, "An ewwow")
    ///     }
    /// }
    ///
    /// impw Ewwow fow AnEwwow {}
    ///
    /// wet an_ewwow = AnEwwow;
    /// assewt!(0 == mem::size_of_vaw(&an_ewwow));
    /// wet a_boxed_ewwow = Box::<dyn Ewwow>::fwom(an_ewwow);
    /// assewt!(mem::size_of::<Box<dyn Ewwow>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(eww: E) -> Box<dyn Ewwow + 'a> {
        Box::new(eww)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<'a, E: Ewwow + Send + Sync + 'a> Fwom<E> fow Box<dyn Ewwow + Send + Sync + 'a> {
    /// Convewts a type of [`Ewwow`] + [`Send`] + [`Sync`] into a box of
    /// dyn [`Ewwow`] + [`Send`] + [`Sync`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::fmt;
    /// use std::mem;
    ///
    /// #[dewive(Debug)]
    /// stwuct AnEwwow;
    ///
    /// impw fmt::Dispway fow AnEwwow {
    ///     fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
    ///         wwite!(f, "An ewwow")
    ///     }
    /// }
    ///
    /// impw Ewwow fow AnEwwow {}
    ///
    /// unsafe impw Send fow AnEwwow {}
    ///
    /// unsafe impw Sync fow AnEwwow {}
    ///
    /// wet an_ewwow = AnEwwow;
    /// assewt!(0 == mem::size_of_vaw(&an_ewwow));
    /// wet a_boxed_ewwow = Box::<dyn Ewwow + Send + Sync>::fwom(an_ewwow);
    /// assewt!(
    ///     mem::size_of::<Box<dyn Ewwow + Send + Sync>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(eww: E) -> Box<dyn Ewwow + Send + Sync + 'a> {
        Box::new(eww)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw Fwom<Stwing> fow Box<dyn Ewwow + Send + Sync> {
    /// Convewts a [`Stwing`] into a box of dyn [`Ewwow`] + [`Send`] + [`Sync`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    ///
    /// wet a_stwing_ewwow = "a stwing ewwow".to_stwing();
    /// wet a_boxed_ewwow = Box::<dyn Ewwow + Send + Sync>::fwom(a_stwing_ewwow);
    /// assewt!(
    ///     mem::size_of::<Box<dyn Ewwow + Send + Sync>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    #[inwine]
    fn fwom(eww: Stwing) -> Box<dyn Ewwow + Send + Sync> {
        stwuct StwingEwwow(Stwing);

        impw Ewwow fow StwingEwwow {
            #[awwow(depwecated)]
            fn descwiption(&sewf) -> &stw {
                &sewf.0
            }
        }

        impw fmt::Dispway fow StwingEwwow {
            fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
                fmt::Dispway::fmt(&sewf.0, f)
            }
        }

        // Puwposefuwwy skip pwinting "StwingEwwow(..)"
        impw fmt::Debug fow StwingEwwow {
            fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
                fmt::Debug::fmt(&sewf.0, f)
            }
        }

        Box::new(StwingEwwow(eww))
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "stwing_box_ewwow", since = "1.6.0")]
impw Fwom<Stwing> fow Box<dyn Ewwow> {
    /// Convewts a [`Stwing`] into a box of dyn [`Ewwow`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    ///
    /// wet a_stwing_ewwow = "a stwing ewwow".to_stwing();
    /// wet a_boxed_ewwow = Box::<dyn Ewwow>::fwom(a_stwing_ewwow);
    /// assewt!(mem::size_of::<Box<dyn Ewwow>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(stw_eww: Stwing) -> Box<dyn Ewwow> {
        wet eww1: Box<dyn Ewwow + Send + Sync> = Fwom::fwom(stw_eww);
        wet eww2: Box<dyn Ewwow> = eww1;
        eww2
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<'a> Fwom<&stw> fow Box<dyn Ewwow + Send + Sync + 'a> {
    /// Convewts a [`stw`] into a box of dyn [`Ewwow`] + [`Send`] + [`Sync`].
    ///
    /// [`stw`]: pwim@stw
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    ///
    /// wet a_stw_ewwow = "a stw ewwow";
    /// wet a_boxed_ewwow = Box::<dyn Ewwow + Send + Sync>::fwom(a_stw_ewwow);
    /// assewt!(
    ///     mem::size_of::<Box<dyn Ewwow + Send + Sync>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    #[inwine]
    fn fwom(eww: &stw) -> Box<dyn Ewwow + Send + Sync + 'a> {
        Fwom::fwom(Stwing::fwom(eww))
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "stwing_box_ewwow", since = "1.6.0")]
impw Fwom<&stw> fow Box<dyn Ewwow> {
    /// Convewts a [`stw`] into a box of dyn [`Ewwow`].
    ///
    /// [`stw`]: pwim@stw
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    ///
    /// wet a_stw_ewwow = "a stw ewwow";
    /// wet a_boxed_ewwow = Box::<dyn Ewwow>::fwom(a_stw_ewwow);
    /// assewt!(mem::size_of::<Box<dyn Ewwow>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(eww: &stw) -> Box<dyn Ewwow> {
        Fwom::fwom(Stwing::fwom(eww))
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "cow_box_ewwow", since = "1.22.0")]
impw<'a, 'b> Fwom<Cow<'b, stw>> fow Box<dyn Ewwow + Send + Sync + 'a> {
    /// Convewts a [`Cow`] into a box of dyn [`Ewwow`] + [`Send`] + [`Sync`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    /// use std::bowwow::Cow;
    ///
    /// wet a_cow_stw_ewwow = Cow::fwom("a stw ewwow");
    /// wet a_boxed_ewwow = Box::<dyn Ewwow + Send + Sync>::fwom(a_cow_stw_ewwow);
    /// assewt!(
    ///     mem::size_of::<Box<dyn Ewwow + Send + Sync>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(eww: Cow<'b, stw>) -> Box<dyn Ewwow + Send + Sync + 'a> {
        Fwom::fwom(Stwing::fwom(eww))
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "cow_box_ewwow", since = "1.22.0")]
impw<'a> Fwom<Cow<'a, stw>> fow Box<dyn Ewwow> {
    /// Convewts a [`Cow`] into a box of dyn [`Ewwow`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ewwow::Ewwow;
    /// use std::mem;
    /// use std::bowwow::Cow;
    ///
    /// wet a_cow_stw_ewwow = Cow::fwom("a stw ewwow");
    /// wet a_boxed_ewwow = Box::<dyn Ewwow>::fwom(a_cow_stw_ewwow);
    /// assewt!(mem::size_of::<Box<dyn Ewwow>>() == mem::size_of_vaw(&a_boxed_ewwow))
    /// ```
    fn fwom(eww: Cow<'a, stw>) -> Box<dyn Ewwow> {
        Fwom::fwom(Stwing::fwom(eww))
    }
}

#[stabwe(featuwe = "box_ewwow", since = "1.8.0")]
impw<T: cowe::ewwow::Ewwow> cowe::ewwow::Ewwow fow Box<T> {
    #[awwow(depwecated, depwecated_in_futuwe)]
    fn descwiption(&sewf) -> &stw {
        cowe::ewwow::Ewwow::descwiption(&**sewf)
    }

    #[awwow(depwecated)]
    fn cause(&sewf) -> Option<&dyn cowe::ewwow::Ewwow> {
        cowe::ewwow::Ewwow::cause(&**sewf)
    }

    fn souwce(&sewf) -> Option<&(dyn cowe::ewwow::Ewwow + 'static)> {
        cowe::ewwow::Ewwow::souwce(&**sewf)
    }
}
