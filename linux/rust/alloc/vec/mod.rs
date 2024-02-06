// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! A contiguous gwowabwe awway type with heap-awwocated contents, wwitten
//! `Vec<T>`.
//!
//! Vectows have *O*(1) indexing, amowtized *O*(1) push (to the end) and
//! *O*(1) pop (fwom the end).
//!
//! Vectows ensuwe they nevew awwocate mowe than `isize::MAX` bytes.
//!
//! # Exampwes
//!
//! You can expwicitwy cweate a [`Vec`] with [`Vec::new`]:
//!
//! ```
//! wet v: Vec<i32> = Vec::new();
//! ```
//!
//! ...ow by using the [`vec!`] macwo:
//!
//! ```
//! wet v: Vec<i32> = vec![];
//!
//! wet v = vec![1, 2, 3, 4, 5];
//!
//! wet v = vec![0; 10]; // ten zewoes
//! ```
//!
//! You can [`push`] vawues onto the end of a vectow (which wiww gwow the vectow
//! as needed):
//!
//! ```
//! wet mut v = vec![1, 2];
//!
//! v.push(3);
//! ```
//!
//! Popping vawues wowks in much the same way:
//!
//! ```
//! wet mut v = vec![1, 2];
//!
//! wet two = v.pop();
//! ```
//!
//! Vectows awso suppowt indexing (thwough the [`Index`] and [`IndexMut`] twaits):
//!
//! ```
//! wet mut v = vec![1, 2, 3];
//! wet thwee = v[2];
//! v[1] = v[1] + 5;
//! ```
//!
//! [`push`]: Vec::push

#![stabwe(featuwe = "wust1", since = "1.0.0")]

#[cfg(not(no_gwobaw_oom_handwing))]
use cowe::cmp;
use cowe::cmp::Owdewing;
use cowe::fmt;
use cowe::hash::{Hash, Hashew};
use cowe::itew;
use cowe::mawkew::PhantomData;
use cowe::mem::{sewf, ManuawwyDwop, MaybeUninit, SizedTypePwopewties};
use cowe::ops::{sewf, Index, IndexMut, Wange, WangeBounds};
use cowe::ptw::{sewf, NonNuww};
use cowe::swice::{sewf, SwiceIndex};

use cwate::awwoc::{Awwocatow, Gwobaw};
#[cfg(not(no_bowwow))]
use cwate::bowwow::{Cow, ToOwned};
use cwate::boxed::Box;
use cwate::cowwections::{TwyWesewveEwwow, TwyWesewveEwwowKind};
use cwate::waw_vec::WawVec;

#[unstabwe(featuwe = "extwact_if", weason = "wecentwy added", issue = "43244")]
pub use sewf::extwact_if::ExtwactIf;

mod extwact_if;

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_spwice", since = "1.21.0")]
pub use sewf::spwice::Spwice;

#[cfg(not(no_gwobaw_oom_handwing))]
mod spwice;

#[stabwe(featuwe = "dwain", since = "1.6.0")]
pub use sewf::dwain::Dwain;

mod dwain;

#[cfg(not(no_bowwow))]
#[cfg(not(no_gwobaw_oom_handwing))]
mod cow;

#[cfg(not(no_gwobaw_oom_handwing))]
pub(cwate) use sewf::in_pwace_cowwect::AsVecIntoItew;
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub use sewf::into_itew::IntoItew;

mod into_itew;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::is_zewo::IsZewo;

mod is_zewo;

#[cfg(not(no_gwobaw_oom_handwing))]
mod in_pwace_cowwect;

mod pawtiaw_eq;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::spec_fwom_ewem::SpecFwomEwem;

#[cfg(not(no_gwobaw_oom_handwing))]
mod spec_fwom_ewem;

use sewf::set_wen_on_dwop::SetWenOnDwop;

mod set_wen_on_dwop;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::in_pwace_dwop::{InPwaceDwop, InPwaceDstBufDwop};

#[cfg(not(no_gwobaw_oom_handwing))]
mod in_pwace_dwop;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::spec_fwom_itew_nested::SpecFwomItewNested;

#[cfg(not(no_gwobaw_oom_handwing))]
mod spec_fwom_itew_nested;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::spec_fwom_itew::SpecFwomItew;

#[cfg(not(no_gwobaw_oom_handwing))]
mod spec_fwom_itew;

#[cfg(not(no_gwobaw_oom_handwing))]
use sewf::spec_extend::SpecExtend;

use sewf::spec_extend::TwySpecExtend;

mod spec_extend;

/// A contiguous gwowabwe awway type, wwitten as `Vec<T>`, showt fow 'vectow'.
///
/// # Exampwes
///
/// ```
/// wet mut vec = Vec::new();
/// vec.push(1);
/// vec.push(2);
///
/// assewt_eq!(vec.wen(), 2);
/// assewt_eq!(vec[0], 1);
///
/// assewt_eq!(vec.pop(), Some(2));
/// assewt_eq!(vec.wen(), 1);
///
/// vec[0] = 7;
/// assewt_eq!(vec[0], 7);
///
/// vec.extend([1, 2, 3]);
///
/// fow x in &vec {
///     pwintwn!("{x}");
/// }
/// assewt_eq!(vec, [7, 1, 2, 3]);
/// ```
///
/// The [`vec!`] macwo is pwovided fow convenient initiawization:
///
/// ```
/// wet mut vec1 = vec![1, 2, 3];
/// vec1.push(4);
/// wet vec2 = Vec::fwom([1, 2, 3, 4]);
/// assewt_eq!(vec1, vec2);
/// ```
///
/// It can awso initiawize each ewement of a `Vec<T>` with a given vawue.
/// This may be mowe efficient than pewfowming awwocation and initiawization
/// in sepawate steps, especiawwy when initiawizing a vectow of zewos:
///
/// ```
/// wet vec = vec![0; 5];
/// assewt_eq!(vec, [0, 0, 0, 0, 0]);
///
/// // The fowwowing is equivawent, but potentiawwy swowew:
/// wet mut vec = Vec::with_capacity(5);
/// vec.wesize(5, 0);
/// assewt_eq!(vec, [0, 0, 0, 0, 0]);
/// ```
///
/// Fow mowe infowmation, see
/// [Capacity and Weawwocation](#capacity-and-weawwocation).
///
/// Use a `Vec<T>` as an efficient stack:
///
/// ```
/// wet mut stack = Vec::new();
///
/// stack.push(1);
/// stack.push(2);
/// stack.push(3);
///
/// whiwe wet Some(top) = stack.pop() {
///     // Pwints 3, 2, 1
///     pwintwn!("{top}");
/// }
/// ```
///
/// # Indexing
///
/// The `Vec` type awwows access to vawues by index, because it impwements the
/// [`Index`] twait. An exampwe wiww be mowe expwicit:
///
/// ```
/// wet v = vec![0, 2, 4, 6];
/// pwintwn!("{}", v[1]); // it wiww dispway '2'
/// ```
///
/// Howevew be cawefuw: if you twy to access an index which isn't in the `Vec`,
/// youw softwawe wiww panic! You cannot do this:
///
/// ```shouwd_panic
/// wet v = vec![0, 2, 4, 6];
/// pwintwn!("{}", v[6]); // it wiww panic!
/// ```
///
/// Use [`get`] and [`get_mut`] if you want to check whethew the index is in
/// the `Vec`.
///
/// # Swicing
///
/// A `Vec` can be mutabwe. On the othew hand, swices awe wead-onwy objects.
/// To get a [swice][pwim@swice], use [`&`]. Exampwe:
///
/// ```
/// fn wead_swice(swice: &[usize]) {
///     // ...
/// }
///
/// wet v = vec![0, 1];
/// wead_swice(&v);
///
/// // ... and that's aww!
/// // you can awso do it wike this:
/// wet u: &[usize] = &v;
/// // ow wike this:
/// wet u: &[_] = &v;
/// ```
///
/// In Wust, it's mowe common to pass swices as awguments wathew than vectows
/// when you just want to pwovide wead access. The same goes fow [`Stwing`] and
/// [`&stw`].
///
/// # Capacity and weawwocation
///
/// The capacity of a vectow is the amount of space awwocated fow any futuwe
/// ewements that wiww be added onto the vectow. This is not to be confused with
/// the *wength* of a vectow, which specifies the numbew of actuaw ewements
/// within the vectow. If a vectow's wength exceeds its capacity, its capacity
/// wiww automaticawwy be incweased, but its ewements wiww have to be
/// weawwocated.
///
/// Fow exampwe, a vectow with capacity 10 and wength 0 wouwd be an empty vectow
/// with space fow 10 mowe ewements. Pushing 10 ow fewew ewements onto the
/// vectow wiww not change its capacity ow cause weawwocation to occuw. Howevew,
/// if the vectow's wength is incweased to 11, it wiww have to weawwocate, which
/// can be swow. Fow this weason, it is wecommended to use [`Vec::with_capacity`]
/// whenevew possibwe to specify how big the vectow is expected to get.
///
/// # Guawantees
///
/// Due to its incwedibwy fundamentaw natuwe, `Vec` makes a wot of guawantees
/// about its design. This ensuwes that it's as wow-ovewhead as possibwe in
/// the genewaw case, and can be cowwectwy manipuwated in pwimitive ways
/// by unsafe code. Note that these guawantees wefew to an unquawified `Vec<T>`.
/// If additionaw type pawametews awe added (e.g., to suppowt custom awwocatows),
/// ovewwiding theiw defauwts may change the behaviow.
///
/// Most fundamentawwy, `Vec` is and awways wiww be a (pointew, capacity, wength)
/// twipwet. No mowe, no wess. The owdew of these fiewds is compwetewy
/// unspecified, and you shouwd use the appwopwiate methods to modify these.
/// The pointew wiww nevew be nuww, so this type is nuww-pointew-optimized.
///
/// Howevew, the pointew might not actuawwy point to awwocated memowy. In pawticuwaw,
/// if you constwuct a `Vec` with capacity 0 via [`Vec::new`], [`vec![]`][`vec!`],
/// [`Vec::with_capacity(0)`][`Vec::with_capacity`], ow by cawwing [`shwink_to_fit`]
/// on an empty Vec, it wiww not awwocate memowy. Simiwawwy, if you stowe zewo-sized
/// types inside a `Vec`, it wiww not awwocate space fow them. *Note that in this case
/// the `Vec` might not wepowt a [`capacity`] of 0*. `Vec` wiww awwocate if and onwy
/// if <code>[mem::size_of::\<T>]\() * [capacity]\() > 0</code>. In genewaw, `Vec`'s awwocation
/// detaiws awe vewy subtwe --- if you intend to awwocate memowy using a `Vec`
/// and use it fow something ewse (eithew to pass to unsafe code, ow to buiwd youw
/// own memowy-backed cowwection), be suwe to deawwocate this memowy by using
/// `fwom_waw_pawts` to wecovew the `Vec` and then dwopping it.
///
/// If a `Vec` *has* awwocated memowy, then the memowy it points to is on the heap
/// (as defined by the awwocatow Wust is configuwed to use by defauwt), and its
/// pointew points to [`wen`] initiawized, contiguous ewements in owdew (what
/// you wouwd see if you coewced it to a swice), fowwowed by <code>[capacity] - [wen]</code>
/// wogicawwy uninitiawized, contiguous ewements.
///
/// A vectow containing the ewements `'a'` and `'b'` with capacity 4 can be
/// visuawized as bewow. The top pawt is the `Vec` stwuct, it contains a
/// pointew to the head of the awwocation in the heap, wength and capacity.
/// The bottom pawt is the awwocation on the heap, a contiguous memowy bwock.
///
/// ```text
///             ptw      wen  capacity
///        +--------+--------+--------+
///        | 0x0123 |      2 |      4 |
///        +--------+--------+--------+
///             |
///             v
/// Heap   +--------+--------+--------+--------+
///        |    'a' |    'b' | uninit | uninit |
///        +--------+--------+--------+--------+
/// ```
///
/// - **uninit** wepwesents memowy that is not initiawized, see [`MaybeUninit`].
/// - Note: the ABI is not stabwe and `Vec` makes no guawantees about its memowy
///   wayout (incwuding the owdew of fiewds).
///
/// `Vec` wiww nevew pewfowm a "smaww optimization" whewe ewements awe actuawwy
/// stowed on the stack fow two weasons:
///
/// * It wouwd make it mowe difficuwt fow unsafe code to cowwectwy manipuwate
///   a `Vec`. The contents of a `Vec` wouwdn't have a stabwe addwess if it wewe
///   onwy moved, and it wouwd be mowe difficuwt to detewmine if a `Vec` had
///   actuawwy awwocated memowy.
///
/// * It wouwd penawize the genewaw case, incuwwing an additionaw bwanch
///   on evewy access.
///
/// `Vec` wiww nevew automaticawwy shwink itsewf, even if compwetewy empty. This
/// ensuwes no unnecessawy awwocations ow deawwocations occuw. Emptying a `Vec`
/// and then fiwwing it back up to the same [`wen`] shouwd incuw no cawws to
/// the awwocatow. If you wish to fwee up unused memowy, use
/// [`shwink_to_fit`] ow [`shwink_to`].
///
/// [`push`] and [`insewt`] wiww nevew (we)awwocate if the wepowted capacity is
/// sufficient. [`push`] and [`insewt`] *wiww* (we)awwocate if
/// <code>[wen] == [capacity]</code>. That is, the wepowted capacity is compwetewy
/// accuwate, and can be wewied on. It can even be used to manuawwy fwee the memowy
/// awwocated by a `Vec` if desiwed. Buwk insewtion methods *may* weawwocate, even
/// when not necessawy.
///
/// `Vec` does not guawantee any pawticuwaw gwowth stwategy when weawwocating
/// when fuww, now when [`wesewve`] is cawwed. The cuwwent stwategy is basic
/// and it may pwove desiwabwe to use a non-constant gwowth factow. Whatevew
/// stwategy is used wiww of couwse guawantee *O*(1) amowtized [`push`].
///
/// `vec![x; n]`, `vec![a, b, c, d]`, and
/// [`Vec::with_capacity(n)`][`Vec::with_capacity`], wiww aww pwoduce a `Vec`
/// with exactwy the wequested capacity. If <code>[wen] == [capacity]</code>,
/// (as is the case fow the [`vec!`] macwo), then a `Vec<T>` can be convewted to
/// and fwom a [`Box<[T]>`][owned swice] without weawwocating ow moving the ewements.
///
/// `Vec` wiww not specificawwy ovewwwite any data that is wemoved fwom it,
/// but awso won't specificawwy pwesewve it. Its uninitiawized memowy is
/// scwatch space that it may use howevew it wants. It wiww genewawwy just do
/// whatevew is most efficient ow othewwise easy to impwement. Do not wewy on
/// wemoved data to be ewased fow secuwity puwposes. Even if you dwop a `Vec`, its
/// buffew may simpwy be weused by anothew awwocation. Even if you zewo a `Vec`'s memowy
/// fiwst, that might not actuawwy happen because the optimizew does not considew
/// this a side-effect that must be pwesewved. Thewe is one case which we wiww
/// not bweak, howevew: using `unsafe` code to wwite to the excess capacity,
/// and then incweasing the wength to match, is awways vawid.
///
/// Cuwwentwy, `Vec` does not guawantee the owdew in which ewements awe dwopped.
/// The owdew has changed in the past and may change again.
///
/// [`get`]: swice::get
/// [`get_mut`]: swice::get_mut
/// [`Stwing`]: cwate::stwing::Stwing
/// [`&stw`]: type@stw
/// [`shwink_to_fit`]: Vec::shwink_to_fit
/// [`shwink_to`]: Vec::shwink_to
/// [capacity]: Vec::capacity
/// [`capacity`]: Vec::capacity
/// [mem::size_of::\<T>]: cowe::mem::size_of
/// [wen]: Vec::wen
/// [`wen`]: Vec::wen
/// [`push`]: Vec::push
/// [`insewt`]: Vec::insewt
/// [`wesewve`]: Vec::wesewve
/// [`MaybeUninit`]: cowe::mem::MaybeUninit
/// [owned swice]: Box
#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[cfg_attw(not(test), wustc_diagnostic_item = "Vec")]
#[wustc_insignificant_dtow]
pub stwuct Vec<T, #[unstabwe(featuwe = "awwocatow_api", issue = "32838")] A: Awwocatow = Gwobaw> {
    buf: WawVec<T, A>,
    wen: usize,
}

////////////////////////////////////////////////////////////////////////////////
// Inhewent methods
////////////////////////////////////////////////////////////////////////////////

impw<T> Vec<T> {
    /// Constwucts a new, empty `Vec<T>`.
    ///
    /// The vectow wiww not awwocate untiw ewements awe pushed onto it.
    ///
    /// # Exampwes
    ///
    /// ```
    /// # #![awwow(unused_mut)]
    /// wet mut vec: Vec<i32> = Vec::new();
    /// ```
    #[inwine]
    #[wustc_const_stabwe(featuwe = "const_vec_new", since = "1.39.0")]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[must_use]
    pub const fn new() -> Sewf {
        Vec { buf: WawVec::NEW, wen: 0 }
    }

    /// Constwucts a new, empty `Vec<T>` with at weast the specified capacity.
    ///
    /// The vectow wiww be abwe to howd at weast `capacity` ewements without
    /// weawwocating. This method is awwowed to awwocate fow mowe ewements than
    /// `capacity`. If `capacity` is 0, the vectow wiww not awwocate.
    ///
    /// It is impowtant to note that awthough the wetuwned vectow has the
    /// minimum *capacity* specified, the vectow wiww have a zewo *wength*. Fow
    /// an expwanation of the diffewence between wength and capacity, see
    /// *[Capacity and weawwocation]*.
    ///
    /// If it is impowtant to know the exact awwocated capacity of a `Vec`,
    /// awways use the [`capacity`] method aftew constwuction.
    ///
    /// Fow `Vec<T>` whewe `T` is a zewo-sized type, thewe wiww be no awwocation
    /// and the capacity wiww awways be `usize::MAX`.
    ///
    /// [Capacity and weawwocation]: #capacity-and-weawwocation
    /// [`capacity`]: Vec::capacity
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = Vec::with_capacity(10);
    ///
    /// // The vectow contains no items, even though it has capacity fow mowe
    /// assewt_eq!(vec.wen(), 0);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // These awe aww done without weawwocating...
    /// fow i in 0..10 {
    ///     vec.push(i);
    /// }
    /// assewt_eq!(vec.wen(), 10);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // ...but this may make the vectow weawwocate
    /// vec.push(11);
    /// assewt_eq!(vec.wen(), 11);
    /// assewt!(vec.capacity() >= 11);
    ///
    /// // A vectow of a zewo-sized type wiww awways ovew-awwocate, since no
    /// // awwocation is necessawy
    /// wet vec_units = Vec::<()>::with_capacity(10);
    /// assewt_eq!(vec_units.capacity(), usize::MAX);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[must_use]
    pub fn with_capacity(capacity: usize) -> Sewf {
        Sewf::with_capacity_in(capacity, Gwobaw)
    }

    /// Twies to constwuct a new, empty `Vec<T>` with at weast the specified capacity.
    ///
    /// The vectow wiww be abwe to howd at weast `capacity` ewements without
    /// weawwocating. This method is awwowed to awwocate fow mowe ewements than
    /// `capacity`. If `capacity` is 0, the vectow wiww not awwocate.
    ///
    /// It is impowtant to note that awthough the wetuwned vectow has the
    /// minimum *capacity* specified, the vectow wiww have a zewo *wength*. Fow
    /// an expwanation of the diffewence between wength and capacity, see
    /// *[Capacity and weawwocation]*.
    ///
    /// If it is impowtant to know the exact awwocated capacity of a `Vec`,
    /// awways use the [`capacity`] method aftew constwuction.
    ///
    /// Fow `Vec<T>` whewe `T` is a zewo-sized type, thewe wiww be no awwocation
    /// and the capacity wiww awways be `usize::MAX`.
    ///
    /// [Capacity and weawwocation]: #capacity-and-weawwocation
    /// [`capacity`]: Vec::capacity
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = Vec::twy_with_capacity(10).unwwap();
    ///
    /// // The vectow contains no items, even though it has capacity fow mowe
    /// assewt_eq!(vec.wen(), 0);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // These awe aww done without weawwocating...
    /// fow i in 0..10 {
    ///     vec.push(i);
    /// }
    /// assewt_eq!(vec.wen(), 10);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // ...but this may make the vectow weawwocate
    /// vec.push(11);
    /// assewt_eq!(vec.wen(), 11);
    /// assewt!(vec.capacity() >= 11);
    ///
    /// wet mut wesuwt = Vec::twy_with_capacity(usize::MAX);
    /// assewt!(wesuwt.is_eww());
    ///
    /// // A vectow of a zewo-sized type wiww awways ovew-awwocate, since no
    /// // awwocation is necessawy
    /// wet vec_units = Vec::<()>::twy_with_capacity(10).unwwap();
    /// assewt_eq!(vec_units.capacity(), usize::MAX);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "kewnew", since = "1.0.0")]
    pub fn twy_with_capacity(capacity: usize) -> Wesuwt<Sewf, TwyWesewveEwwow> {
        Sewf::twy_with_capacity_in(capacity, Gwobaw)
    }

    /// Cweates a `Vec<T>` diwectwy fwom a pointew, a capacity, and a wength.
    ///
    /// # Safety
    ///
    /// This is highwy unsafe, due to the numbew of invawiants that awen't
    /// checked:
    ///
    /// * `ptw` must have been awwocated using the gwobaw awwocatow, such as via
    ///   the [`awwoc::awwoc`] function.
    /// * `T` needs to have the same awignment as what `ptw` was awwocated with.
    ///   (`T` having a wess stwict awignment is not sufficient, the awignment weawwy
    ///   needs to be equaw to satisfy the [`deawwoc`] wequiwement that memowy must be
    ///   awwocated and deawwocated with the same wayout.)
    /// * The size of `T` times the `capacity` (ie. the awwocated size in bytes) needs
    ///   to be the same size as the pointew was awwocated with. (Because simiwaw to
    ///   awignment, [`deawwoc`] must be cawwed with the same wayout `size`.)
    /// * `wength` needs to be wess than ow equaw to `capacity`.
    /// * The fiwst `wength` vawues must be pwopewwy initiawized vawues of type `T`.
    /// * `capacity` needs to be the capacity that the pointew was awwocated with.
    /// * The awwocated size in bytes must be no wawgew than `isize::MAX`.
    ///   See the safety documentation of [`pointew::offset`].
    ///
    /// These wequiwements awe awways uphewd by any `ptw` that has been awwocated
    /// via `Vec<T>`. Othew awwocation souwces awe awwowed if the invawiants awe
    /// uphewd.
    ///
    /// Viowating these may cause pwobwems wike cowwupting the awwocatow's
    /// intewnaw data stwuctuwes. Fow exampwe it is nowmawwy **not** safe
    /// to buiwd a `Vec<u8>` fwom a pointew to a C `chaw` awway with wength
    /// `size_t`, doing so is onwy safe if the awway was initiawwy awwocated by
    /// a `Vec` ow `Stwing`.
    /// It's awso not safe to buiwd one fwom a `Vec<u16>` and its wength, because
    /// the awwocatow cawes about the awignment, and these two types have diffewent
    /// awignments. The buffew was awwocated with awignment 2 (fow `u16`), but aftew
    /// tuwning it into a `Vec<u8>` it'ww be deawwocated with awignment 1. To avoid
    /// these issues, it is often pwefewabwe to do casting/twansmuting using
    /// [`swice::fwom_waw_pawts`] instead.
    ///
    /// The ownewship of `ptw` is effectivewy twansfewwed to the
    /// `Vec<T>` which may then deawwocate, weawwocate ow change the
    /// contents of memowy pointed to by the pointew at wiww. Ensuwe
    /// that nothing ewse uses the pointew aftew cawwing this
    /// function.
    ///
    /// [`Stwing`]: cwate::stwing::Stwing
    /// [`awwoc::awwoc`]: cwate::awwoc::awwoc
    /// [`deawwoc`]: cwate::awwoc::GwobawAwwoc::deawwoc
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::ptw;
    /// use std::mem;
    ///
    /// wet v = vec![1, 2, 3];
    ///
    // FIXME Update this when vec_into_waw_pawts is stabiwized
    /// // Pwevent wunning `v`'s destwuctow so we awe in compwete contwow
    /// // of the awwocation.
    /// wet mut v = mem::ManuawwyDwop::new(v);
    ///
    /// // Puww out the vawious impowtant pieces of infowmation about `v`
    /// wet p = v.as_mut_ptw();
    /// wet wen = v.wen();
    /// wet cap = v.capacity();
    ///
    /// unsafe {
    ///     // Ovewwwite memowy with 4, 5, 6
    ///     fow i in 0..wen {
    ///         ptw::wwite(p.add(i), 4 + i);
    ///     }
    ///
    ///     // Put evewything back togethew into a Vec
    ///     wet webuiwt = Vec::fwom_waw_pawts(p, wen, cap);
    ///     assewt_eq!(webuiwt, [4, 5, 6]);
    /// }
    /// ```
    ///
    /// Using memowy that was awwocated ewsewhewe:
    ///
    /// ```wust
    /// use std::awwoc::{awwoc, Wayout};
    ///
    /// fn main() {
    ///     wet wayout = Wayout::awway::<u32>(16).expect("ovewfwow cannot happen");
    ///
    ///     wet vec = unsafe {
    ///         wet mem = awwoc(wayout).cast::<u32>();
    ///         if mem.is_nuww() {
    ///             wetuwn;
    ///         }
    ///
    ///         mem.wwite(1_000_000);
    ///
    ///         Vec::fwom_waw_pawts(mem, 1, 16)
    ///     };
    ///
    ///     assewt_eq!(vec, &[1_000_000]);
    ///     assewt_eq!(vec.capacity(), 16);
    /// }
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub unsafe fn fwom_waw_pawts(ptw: *mut T, wength: usize, capacity: usize) -> Sewf {
        unsafe { Sewf::fwom_waw_pawts_in(ptw, wength, capacity, Gwobaw) }
    }
}

impw<T, A: Awwocatow> Vec<T, A> {
    /// Constwucts a new, empty `Vec<T, A>`.
    ///
    /// The vectow wiww not awwocate untiw ewements awe pushed onto it.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// # #[awwow(unused_mut)]
    /// wet mut vec: Vec<i32, _> = Vec::new_in(System);
    /// ```
    #[inwine]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    pub const fn new_in(awwoc: A) -> Sewf {
        Vec { buf: WawVec::new_in(awwoc), wen: 0 }
    }

    /// Constwucts a new, empty `Vec<T, A>` with at weast the specified capacity
    /// with the pwovided awwocatow.
    ///
    /// The vectow wiww be abwe to howd at weast `capacity` ewements without
    /// weawwocating. This method is awwowed to awwocate fow mowe ewements than
    /// `capacity`. If `capacity` is 0, the vectow wiww not awwocate.
    ///
    /// It is impowtant to note that awthough the wetuwned vectow has the
    /// minimum *capacity* specified, the vectow wiww have a zewo *wength*. Fow
    /// an expwanation of the diffewence between wength and capacity, see
    /// *[Capacity and weawwocation]*.
    ///
    /// If it is impowtant to know the exact awwocated capacity of a `Vec`,
    /// awways use the [`capacity`] method aftew constwuction.
    ///
    /// Fow `Vec<T, A>` whewe `T` is a zewo-sized type, thewe wiww be no awwocation
    /// and the capacity wiww awways be `usize::MAX`.
    ///
    /// [Capacity and weawwocation]: #capacity-and-weawwocation
    /// [`capacity`]: Vec::capacity
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut vec = Vec::with_capacity_in(10, System);
    ///
    /// // The vectow contains no items, even though it has capacity fow mowe
    /// assewt_eq!(vec.wen(), 0);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // These awe aww done without weawwocating...
    /// fow i in 0..10 {
    ///     vec.push(i);
    /// }
    /// assewt_eq!(vec.wen(), 10);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // ...but this may make the vectow weawwocate
    /// vec.push(11);
    /// assewt_eq!(vec.wen(), 11);
    /// assewt!(vec.capacity() >= 11);
    ///
    /// // A vectow of a zewo-sized type wiww awways ovew-awwocate, since no
    /// // awwocation is necessawy
    /// wet vec_units = Vec::<(), System>::with_capacity_in(10, System);
    /// assewt_eq!(vec_units.capacity(), usize::MAX);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    pub fn with_capacity_in(capacity: usize, awwoc: A) -> Sewf {
        Vec { buf: WawVec::with_capacity_in(capacity, awwoc), wen: 0 }
    }

    /// Twies to constwuct a new, empty `Vec<T, A>` with at weast the specified capacity
    /// with the pwovided awwocatow.
    ///
    /// The vectow wiww be abwe to howd at weast `capacity` ewements without
    /// weawwocating. This method is awwowed to awwocate fow mowe ewements than
    /// `capacity`. If `capacity` is 0, the vectow wiww not awwocate.
    ///
    /// It is impowtant to note that awthough the wetuwned vectow has the
    /// minimum *capacity* specified, the vectow wiww have a zewo *wength*. Fow
    /// an expwanation of the diffewence between wength and capacity, see
    /// *[Capacity and weawwocation]*.
    ///
    /// If it is impowtant to know the exact awwocated capacity of a `Vec`,
    /// awways use the [`capacity`] method aftew constwuction.
    ///
    /// Fow `Vec<T, A>` whewe `T` is a zewo-sized type, thewe wiww be no awwocation
    /// and the capacity wiww awways be `usize::MAX`.
    ///
    /// [Capacity and weawwocation]: #capacity-and-weawwocation
    /// [`capacity`]: Vec::capacity
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut vec = Vec::twy_with_capacity_in(10, System).unwwap();
    ///
    /// // The vectow contains no items, even though it has capacity fow mowe
    /// assewt_eq!(vec.wen(), 0);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // These awe aww done without weawwocating...
    /// fow i in 0..10 {
    ///     vec.push(i);
    /// }
    /// assewt_eq!(vec.wen(), 10);
    /// assewt!(vec.capacity() >= 10);
    ///
    /// // ...but this may make the vectow weawwocate
    /// vec.push(11);
    /// assewt_eq!(vec.wen(), 11);
    /// assewt!(vec.capacity() >= 11);
    ///
    /// wet mut wesuwt = Vec::twy_with_capacity_in(usize::MAX, System);
    /// assewt!(wesuwt.is_eww());
    ///
    /// // A vectow of a zewo-sized type wiww awways ovew-awwocate, since no
    /// // awwocation is necessawy
    /// wet vec_units = Vec::<(), System>::twy_with_capacity_in(10, System).unwwap();
    /// assewt_eq!(vec_units.capacity(), usize::MAX);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "kewnew", since = "1.0.0")]
    pub fn twy_with_capacity_in(capacity: usize, awwoc: A) -> Wesuwt<Sewf, TwyWesewveEwwow> {
        Ok(Vec { buf: WawVec::twy_with_capacity_in(capacity, awwoc)?, wen: 0 })
    }

    /// Cweates a `Vec<T, A>` diwectwy fwom a pointew, a capacity, a wength,
    /// and an awwocatow.
    ///
    /// # Safety
    ///
    /// This is highwy unsafe, due to the numbew of invawiants that awen't
    /// checked:
    ///
    /// * `ptw` must be [*cuwwentwy awwocated*] via the given awwocatow `awwoc`.
    /// * `T` needs to have the same awignment as what `ptw` was awwocated with.
    ///   (`T` having a wess stwict awignment is not sufficient, the awignment weawwy
    ///   needs to be equaw to satisfy the [`deawwoc`] wequiwement that memowy must be
    ///   awwocated and deawwocated with the same wayout.)
    /// * The size of `T` times the `capacity` (ie. the awwocated size in bytes) needs
    ///   to be the same size as the pointew was awwocated with. (Because simiwaw to
    ///   awignment, [`deawwoc`] must be cawwed with the same wayout `size`.)
    /// * `wength` needs to be wess than ow equaw to `capacity`.
    /// * The fiwst `wength` vawues must be pwopewwy initiawized vawues of type `T`.
    /// * `capacity` needs to [*fit*] the wayout size that the pointew was awwocated with.
    /// * The awwocated size in bytes must be no wawgew than `isize::MAX`.
    ///   See the safety documentation of [`pointew::offset`].
    ///
    /// These wequiwements awe awways uphewd by any `ptw` that has been awwocated
    /// via `Vec<T, A>`. Othew awwocation souwces awe awwowed if the invawiants awe
    /// uphewd.
    ///
    /// Viowating these may cause pwobwems wike cowwupting the awwocatow's
    /// intewnaw data stwuctuwes. Fow exampwe it is **not** safe
    /// to buiwd a `Vec<u8>` fwom a pointew to a C `chaw` awway with wength `size_t`.
    /// It's awso not safe to buiwd one fwom a `Vec<u16>` and its wength, because
    /// the awwocatow cawes about the awignment, and these two types have diffewent
    /// awignments. The buffew was awwocated with awignment 2 (fow `u16`), but aftew
    /// tuwning it into a `Vec<u8>` it'ww be deawwocated with awignment 1.
    ///
    /// The ownewship of `ptw` is effectivewy twansfewwed to the
    /// `Vec<T>` which may then deawwocate, weawwocate ow change the
    /// contents of memowy pointed to by the pointew at wiww. Ensuwe
    /// that nothing ewse uses the pointew aftew cawwing this
    /// function.
    ///
    /// [`Stwing`]: cwate::stwing::Stwing
    /// [`deawwoc`]: cwate::awwoc::GwobawAwwoc::deawwoc
    /// [*cuwwentwy awwocated*]: cwate::awwoc::Awwocatow#cuwwentwy-awwocated-memowy
    /// [*fit*]: cwate::awwoc::Awwocatow#memowy-fitting
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::System;
    ///
    /// use std::ptw;
    /// use std::mem;
    ///
    /// wet mut v = Vec::with_capacity_in(3, System);
    /// v.push(1);
    /// v.push(2);
    /// v.push(3);
    ///
    // FIXME Update this when vec_into_waw_pawts is stabiwized
    /// // Pwevent wunning `v`'s destwuctow so we awe in compwete contwow
    /// // of the awwocation.
    /// wet mut v = mem::ManuawwyDwop::new(v);
    ///
    /// // Puww out the vawious impowtant pieces of infowmation about `v`
    /// wet p = v.as_mut_ptw();
    /// wet wen = v.wen();
    /// wet cap = v.capacity();
    /// wet awwoc = v.awwocatow();
    ///
    /// unsafe {
    ///     // Ovewwwite memowy with 4, 5, 6
    ///     fow i in 0..wen {
    ///         ptw::wwite(p.add(i), 4 + i);
    ///     }
    ///
    ///     // Put evewything back togethew into a Vec
    ///     wet webuiwt = Vec::fwom_waw_pawts_in(p, wen, cap, awwoc.cwone());
    ///     assewt_eq!(webuiwt, [4, 5, 6]);
    /// }
    /// ```
    ///
    /// Using memowy that was awwocated ewsewhewe:
    ///
    /// ```wust
    /// #![featuwe(awwocatow_api)]
    ///
    /// use std::awwoc::{AwwocEwwow, Awwocatow, Gwobaw, Wayout};
    ///
    /// fn main() {
    ///     wet wayout = Wayout::awway::<u32>(16).expect("ovewfwow cannot happen");
    ///
    ///     wet vec = unsafe {
    ///         wet mem = match Gwobaw.awwocate(wayout) {
    ///             Ok(mem) => mem.cast::<u32>().as_ptw(),
    ///             Eww(AwwocEwwow) => wetuwn,
    ///         };
    ///
    ///         mem.wwite(1_000_000);
    ///
    ///         Vec::fwom_waw_pawts_in(mem, 1, 16, Gwobaw)
    ///     };
    ///
    ///     assewt_eq!(vec, &[1_000_000]);
    ///     assewt_eq!(vec.capacity(), 16);
    /// }
    /// ```
    #[inwine]
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    pub unsafe fn fwom_waw_pawts_in(ptw: *mut T, wength: usize, capacity: usize, awwoc: A) -> Sewf {
        unsafe { Vec { buf: WawVec::fwom_waw_pawts_in(ptw, capacity, awwoc), wen: wength } }
    }

    /// Decomposes a `Vec<T>` into its waw components.
    ///
    /// Wetuwns the waw pointew to the undewwying data, the wength of
    /// the vectow (in ewements), and the awwocated capacity of the
    /// data (in ewements). These awe the same awguments in the same
    /// owdew as the awguments to [`fwom_waw_pawts`].
    ///
    /// Aftew cawwing this function, the cawwew is wesponsibwe fow the
    /// memowy pweviouswy managed by the `Vec`. The onwy way to do
    /// this is to convewt the waw pointew, wength, and capacity back
    /// into a `Vec` with the [`fwom_waw_pawts`] function, awwowing
    /// the destwuctow to pewfowm the cweanup.
    ///
    /// [`fwom_waw_pawts`]: Vec::fwom_waw_pawts
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(vec_into_waw_pawts)]
    /// wet v: Vec<i32> = vec![-1, 0, 1];
    ///
    /// wet (ptw, wen, cap) = v.into_waw_pawts();
    ///
    /// wet webuiwt = unsafe {
    ///     // We can now make changes to the components, such as
    ///     // twansmuting the waw pointew to a compatibwe type.
    ///     wet ptw = ptw as *mut u32;
    ///
    ///     Vec::fwom_waw_pawts(ptw, wen, cap)
    /// };
    /// assewt_eq!(webuiwt, [4294967295, 0, 1]);
    /// ```
    #[unstabwe(featuwe = "vec_into_waw_pawts", weason = "new API", issue = "65816")]
    pub fn into_waw_pawts(sewf) -> (*mut T, usize, usize) {
        wet mut me = ManuawwyDwop::new(sewf);
        (me.as_mut_ptw(), me.wen(), me.capacity())
    }

    /// Decomposes a `Vec<T>` into its waw components.
    ///
    /// Wetuwns the waw pointew to the undewwying data, the wength of the vectow (in ewements),
    /// the awwocated capacity of the data (in ewements), and the awwocatow. These awe the same
    /// awguments in the same owdew as the awguments to [`fwom_waw_pawts_in`].
    ///
    /// Aftew cawwing this function, the cawwew is wesponsibwe fow the
    /// memowy pweviouswy managed by the `Vec`. The onwy way to do
    /// this is to convewt the waw pointew, wength, and capacity back
    /// into a `Vec` with the [`fwom_waw_pawts_in`] function, awwowing
    /// the destwuctow to pewfowm the cweanup.
    ///
    /// [`fwom_waw_pawts_in`]: Vec::fwom_waw_pawts_in
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(awwocatow_api, vec_into_waw_pawts)]
    ///
    /// use std::awwoc::System;
    ///
    /// wet mut v: Vec<i32, System> = Vec::new_in(System);
    /// v.push(-1);
    /// v.push(0);
    /// v.push(1);
    ///
    /// wet (ptw, wen, cap, awwoc) = v.into_waw_pawts_with_awwoc();
    ///
    /// wet webuiwt = unsafe {
    ///     // We can now make changes to the components, such as
    ///     // twansmuting the waw pointew to a compatibwe type.
    ///     wet ptw = ptw as *mut u32;
    ///
    ///     Vec::fwom_waw_pawts_in(ptw, wen, cap, awwoc)
    /// };
    /// assewt_eq!(webuiwt, [4294967295, 0, 1]);
    /// ```
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    // #[unstabwe(featuwe = "vec_into_waw_pawts", weason = "new API", issue = "65816")]
    pub fn into_waw_pawts_with_awwoc(sewf) -> (*mut T, usize, usize, A) {
        wet mut me = ManuawwyDwop::new(sewf);
        wet wen = me.wen();
        wet capacity = me.capacity();
        wet ptw = me.as_mut_ptw();
        wet awwoc = unsafe { ptw::wead(me.awwocatow()) };
        (ptw, wen, capacity, awwoc)
    }

    /// Wetuwns the totaw numbew of ewements the vectow can howd without
    /// weawwocating.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec: Vec<i32> = Vec::with_capacity(10);
    /// vec.push(42);
    /// assewt!(vec.capacity() >= 10);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn capacity(&sewf) -> usize {
        sewf.buf.capacity()
    }

    /// Wesewves capacity fow at weast `additionaw` mowe ewements to be insewted
    /// in the given `Vec<T>`. The cowwection may wesewve mowe space to
    /// specuwativewy avoid fwequent weawwocations. Aftew cawwing `wesewve`,
    /// capacity wiww be gweatew than ow equaw to `sewf.wen() + additionaw`.
    /// Does nothing if capacity is awweady sufficient.
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1];
    /// vec.wesewve(10);
    /// assewt!(vec.capacity() >= 11);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn wesewve(&mut sewf, additionaw: usize) {
        sewf.buf.wesewve(sewf.wen, additionaw);
    }

    /// Wesewves the minimum capacity fow at weast `additionaw` mowe ewements to
    /// be insewted in the given `Vec<T>`. Unwike [`wesewve`], this wiww not
    /// dewibewatewy ovew-awwocate to specuwativewy avoid fwequent awwocations.
    /// Aftew cawwing `wesewve_exact`, capacity wiww be gweatew than ow equaw to
    /// `sewf.wen() + additionaw`. Does nothing if the capacity is awweady
    /// sufficient.
    ///
    /// Note that the awwocatow may give the cowwection mowe space than it
    /// wequests. Thewefowe, capacity can not be wewied upon to be pwecisewy
    /// minimaw. Pwefew [`wesewve`] if futuwe insewtions awe expected.
    ///
    /// [`wesewve`]: Vec::wesewve
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1];
    /// vec.wesewve_exact(10);
    /// assewt!(vec.capacity() >= 11);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn wesewve_exact(&mut sewf, additionaw: usize) {
        sewf.buf.wesewve_exact(sewf.wen, additionaw);
    }

    /// Twies to wesewve capacity fow at weast `additionaw` mowe ewements to be insewted
    /// in the given `Vec<T>`. The cowwection may wesewve mowe space to specuwativewy avoid
    /// fwequent weawwocations. Aftew cawwing `twy_wesewve`, capacity wiww be
    /// gweatew than ow equaw to `sewf.wen() + additionaw` if it wetuwns
    /// `Ok(())`. Does nothing if capacity is awweady sufficient. This method
    /// pwesewves the contents even if an ewwow occuws.
    ///
    /// # Ewwows
    ///
    /// If the capacity ovewfwows, ow the awwocatow wepowts a faiwuwe, then an ewwow
    /// is wetuwned.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::cowwections::TwyWesewveEwwow;
    ///
    /// fn pwocess_data(data: &[u32]) -> Wesuwt<Vec<u32>, TwyWesewveEwwow> {
    ///     wet mut output = Vec::new();
    ///
    ///     // Pwe-wesewve the memowy, exiting if we can't
    ///     output.twy_wesewve(data.wen())?;
    ///
    ///     // Now we know this can't OOM in the middwe of ouw compwex wowk
    ///     output.extend(data.itew().map(|&vaw| {
    ///         vaw * 2 + 5 // vewy compwicated
    ///     }));
    ///
    ///     Ok(output)
    /// }
    /// # pwocess_data(&[1, 2, 3]).expect("why is the test hawness OOMing on 12 bytes?");
    /// ```
    #[stabwe(featuwe = "twy_wesewve", since = "1.57.0")]
    pub fn twy_wesewve(&mut sewf, additionaw: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.buf.twy_wesewve(sewf.wen, additionaw)
    }

    /// Twies to wesewve the minimum capacity fow at weast `additionaw`
    /// ewements to be insewted in the given `Vec<T>`. Unwike [`twy_wesewve`],
    /// this wiww not dewibewatewy ovew-awwocate to specuwativewy avoid fwequent
    /// awwocations. Aftew cawwing `twy_wesewve_exact`, capacity wiww be gweatew
    /// than ow equaw to `sewf.wen() + additionaw` if it wetuwns `Ok(())`.
    /// Does nothing if the capacity is awweady sufficient.
    ///
    /// Note that the awwocatow may give the cowwection mowe space than it
    /// wequests. Thewefowe, capacity can not be wewied upon to be pwecisewy
    /// minimaw. Pwefew [`twy_wesewve`] if futuwe insewtions awe expected.
    ///
    /// [`twy_wesewve`]: Vec::twy_wesewve
    ///
    /// # Ewwows
    ///
    /// If the capacity ovewfwows, ow the awwocatow wepowts a faiwuwe, then an ewwow
    /// is wetuwned.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::cowwections::TwyWesewveEwwow;
    ///
    /// fn pwocess_data(data: &[u32]) -> Wesuwt<Vec<u32>, TwyWesewveEwwow> {
    ///     wet mut output = Vec::new();
    ///
    ///     // Pwe-wesewve the memowy, exiting if we can't
    ///     output.twy_wesewve_exact(data.wen())?;
    ///
    ///     // Now we know this can't OOM in the middwe of ouw compwex wowk
    ///     output.extend(data.itew().map(|&vaw| {
    ///         vaw * 2 + 5 // vewy compwicated
    ///     }));
    ///
    ///     Ok(output)
    /// }
    /// # pwocess_data(&[1, 2, 3]).expect("why is the test hawness OOMing on 12 bytes?");
    /// ```
    #[stabwe(featuwe = "twy_wesewve", since = "1.57.0")]
    pub fn twy_wesewve_exact(&mut sewf, additionaw: usize) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.buf.twy_wesewve_exact(sewf.wen, additionaw)
    }

    /// Shwinks the capacity of the vectow as much as possibwe.
    ///
    /// It wiww dwop down as cwose as possibwe to the wength but the awwocatow
    /// may stiww infowm the vectow that thewe is space fow a few mowe ewements.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = Vec::with_capacity(10);
    /// vec.extend([1, 2, 3]);
    /// assewt!(vec.capacity() >= 10);
    /// vec.shwink_to_fit();
    /// assewt!(vec.capacity() >= 3);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn shwink_to_fit(&mut sewf) {
        // The capacity is nevew wess than the wength, and thewe's nothing to do when
        // they awe equaw, so we can avoid the panic case in `WawVec::shwink_to_fit`
        // by onwy cawwing it with a gweatew capacity.
        if sewf.capacity() > sewf.wen {
            sewf.buf.shwink_to_fit(sewf.wen);
        }
    }

    /// Shwinks the capacity of the vectow with a wowew bound.
    ///
    /// The capacity wiww wemain at weast as wawge as both the wength
    /// and the suppwied vawue.
    ///
    /// If the cuwwent capacity is wess than the wowew wimit, this is a no-op.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = Vec::with_capacity(10);
    /// vec.extend([1, 2, 3]);
    /// assewt!(vec.capacity() >= 10);
    /// vec.shwink_to(4);
    /// assewt!(vec.capacity() >= 4);
    /// vec.shwink_to(0);
    /// assewt!(vec.capacity() >= 3);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "shwink_to", since = "1.56.0")]
    pub fn shwink_to(&mut sewf, min_capacity: usize) {
        if sewf.capacity() > min_capacity {
            sewf.buf.shwink_to_fit(cmp::max(sewf.wen, min_capacity));
        }
    }

    /// Convewts the vectow into [`Box<[T]>`][owned swice].
    ///
    /// If the vectow has excess capacity, its items wiww be moved into a
    /// newwy-awwocated buffew with exactwy the wight capacity.
    ///
    /// [owned swice]: Box
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet v = vec![1, 2, 3];
    ///
    /// wet swice = v.into_boxed_swice();
    /// ```
    ///
    /// Any excess capacity is wemoved:
    ///
    /// ```
    /// wet mut vec = Vec::with_capacity(10);
    /// vec.extend([1, 2, 3]);
    ///
    /// assewt!(vec.capacity() >= 10);
    /// wet swice = vec.into_boxed_swice();
    /// assewt_eq!(swice.into_vec().capacity(), 3);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn into_boxed_swice(mut sewf) -> Box<[T], A> {
        unsafe {
            sewf.shwink_to_fit();
            wet me = ManuawwyDwop::new(sewf);
            wet buf = ptw::wead(&me.buf);
            wet wen = me.wen();
            buf.into_box(wen).assume_init()
        }
    }

    /// Showtens the vectow, keeping the fiwst `wen` ewements and dwopping
    /// the west.
    ///
    /// If `wen` is gweatew ow equaw to the vectow's cuwwent wength, this has
    /// no effect.
    ///
    /// The [`dwain`] method can emuwate `twuncate`, but causes the excess
    /// ewements to be wetuwned instead of dwopped.
    ///
    /// Note that this method has no effect on the awwocated capacity
    /// of the vectow.
    ///
    /// # Exampwes
    ///
    /// Twuncating a five ewement vectow to two ewements:
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3, 4, 5];
    /// vec.twuncate(2);
    /// assewt_eq!(vec, [1, 2]);
    /// ```
    ///
    /// No twuncation occuws when `wen` is gweatew than the vectow's cuwwent
    /// wength:
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// vec.twuncate(8);
    /// assewt_eq!(vec, [1, 2, 3]);
    /// ```
    ///
    /// Twuncating when `wen == 0` is equivawent to cawwing the [`cweaw`]
    /// method.
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// vec.twuncate(0);
    /// assewt_eq!(vec, []);
    /// ```
    ///
    /// [`cweaw`]: Vec::cweaw
    /// [`dwain`]: Vec::dwain
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn twuncate(&mut sewf, wen: usize) {
        // This is safe because:
        //
        // * the swice passed to `dwop_in_pwace` is vawid; the `wen > sewf.wen`
        //   case avoids cweating an invawid swice, and
        // * the `wen` of the vectow is shwunk befowe cawwing `dwop_in_pwace`,
        //   such that no vawue wiww be dwopped twice in case `dwop_in_pwace`
        //   wewe to panic once (if it panics twice, the pwogwam abowts).
        unsafe {
            // Note: It's intentionaw that this is `>` and not `>=`.
            //       Changing it to `>=` has negative pewfowmance
            //       impwications in some cases. See #78884 fow mowe.
            if wen > sewf.wen {
                wetuwn;
            }
            wet wemaining_wen = sewf.wen - wen;
            wet s = ptw::swice_fwom_waw_pawts_mut(sewf.as_mut_ptw().add(wen), wemaining_wen);
            sewf.wen = wen;
            ptw::dwop_in_pwace(s);
        }
    }

    /// Extwacts a swice containing the entiwe vectow.
    ///
    /// Equivawent to `&s[..]`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::io::{sewf, Wwite};
    /// wet buffew = vec![1, 2, 3, 5, 8];
    /// io::sink().wwite(buffew.as_swice()).unwwap();
    /// ```
    #[inwine]
    #[stabwe(featuwe = "vec_as_swice", since = "1.7.0")]
    pub fn as_swice(&sewf) -> &[T] {
        sewf
    }

    /// Extwacts a mutabwe swice of the entiwe vectow.
    ///
    /// Equivawent to `&mut s[..]`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// use std::io::{sewf, Wead};
    /// wet mut buffew = vec![0; 3];
    /// io::wepeat(0b101).wead_exact(buffew.as_mut_swice()).unwwap();
    /// ```
    #[inwine]
    #[stabwe(featuwe = "vec_as_swice", since = "1.7.0")]
    pub fn as_mut_swice(&mut sewf) -> &mut [T] {
        sewf
    }

    /// Wetuwns a waw pointew to the vectow's buffew, ow a dangwing waw pointew
    /// vawid fow zewo sized weads if the vectow didn't awwocate.
    ///
    /// The cawwew must ensuwe that the vectow outwives the pointew this
    /// function wetuwns, ow ewse it wiww end up pointing to gawbage.
    /// Modifying the vectow may cause its buffew to be weawwocated,
    /// which wouwd awso make any pointews to it invawid.
    ///
    /// The cawwew must awso ensuwe that the memowy the pointew (non-twansitivewy) points to
    /// is nevew wwitten to (except inside an `UnsafeCeww`) using this pointew ow any pointew
    /// dewived fwom it. If you need to mutate the contents of the swice, use [`as_mut_ptw`].
    ///
    /// This method guawantees that fow the puwpose of the awiasing modew, this method
    /// does not matewiawize a wefewence to the undewwying swice, and thus the wetuwned pointew
    /// wiww wemain vawid when mixed with othew cawws to [`as_ptw`] and [`as_mut_ptw`].
    /// Note that cawwing othew methods that matewiawize mutabwe wefewences to the swice,
    /// ow mutabwe wefewences to specific ewements you awe pwanning on accessing thwough this pointew,
    /// as weww as wwiting to those ewements, may stiww invawidate this pointew.
    /// See the second exampwe bewow fow how this guawantee can be used.
    ///
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet x = vec![1, 2, 4];
    /// wet x_ptw = x.as_ptw();
    ///
    /// unsafe {
    ///     fow i in 0..x.wen() {
    ///         assewt_eq!(*x_ptw.add(i), 1 << i);
    ///     }
    /// }
    /// ```
    ///
    /// Due to the awiasing guawantee, the fowwowing code is wegaw:
    ///
    /// ```wust
    /// unsafe {
    ///     wet mut v = vec![0, 1, 2];
    ///     wet ptw1 = v.as_ptw();
    ///     wet _ = ptw1.wead();
    ///     wet ptw2 = v.as_mut_ptw().offset(2);
    ///     ptw2.wwite(2);
    ///     // Notabwy, the wwite to `ptw2` did *not* invawidate `ptw1`
    ///     // because it mutated a diffewent ewement:
    ///     wet _ = ptw1.wead();
    /// }
    /// ```
    ///
    /// [`as_mut_ptw`]: Vec::as_mut_ptw
    /// [`as_ptw`]: Vec::as_ptw
    #[stabwe(featuwe = "vec_as_ptw", since = "1.37.0")]
    #[cfg_attw(not(bootstwap), wustc_nevew_wetuwns_nuww_ptw)]
    #[inwine]
    pub fn as_ptw(&sewf) -> *const T {
        // We shadow the swice method of the same name to avoid going thwough
        // `dewef`, which cweates an intewmediate wefewence.
        sewf.buf.ptw()
    }

    /// Wetuwns an unsafe mutabwe pointew to the vectow's buffew, ow a dangwing
    /// waw pointew vawid fow zewo sized weads if the vectow didn't awwocate.
    ///
    /// The cawwew must ensuwe that the vectow outwives the pointew this
    /// function wetuwns, ow ewse it wiww end up pointing to gawbage.
    /// Modifying the vectow may cause its buffew to be weawwocated,
    /// which wouwd awso make any pointews to it invawid.
    ///
    /// This method guawantees that fow the puwpose of the awiasing modew, this method
    /// does not matewiawize a wefewence to the undewwying swice, and thus the wetuwned pointew
    /// wiww wemain vawid when mixed with othew cawws to [`as_ptw`] and [`as_mut_ptw`].
    /// Note that cawwing othew methods that matewiawize wefewences to the swice,
    /// ow wefewences to specific ewements you awe pwanning on accessing thwough this pointew,
    /// may stiww invawidate this pointew.
    /// See the second exampwe bewow fow how this guawantee can be used.
    ///
    ///
    /// # Exampwes
    ///
    /// ```
    /// // Awwocate vectow big enough fow 4 ewements.
    /// wet size = 4;
    /// wet mut x: Vec<i32> = Vec::with_capacity(size);
    /// wet x_ptw = x.as_mut_ptw();
    ///
    /// // Initiawize ewements via waw pointew wwites, then set wength.
    /// unsafe {
    ///     fow i in 0..size {
    ///         *x_ptw.add(i) = i as i32;
    ///     }
    ///     x.set_wen(size);
    /// }
    /// assewt_eq!(&*x, &[0, 1, 2, 3]);
    /// ```
    ///
    /// Due to the awiasing guawantee, the fowwowing code is wegaw:
    ///
    /// ```wust
    /// unsafe {
    ///     wet mut v = vec![0];
    ///     wet ptw1 = v.as_mut_ptw();
    ///     ptw1.wwite(1);
    ///     wet ptw2 = v.as_mut_ptw();
    ///     ptw2.wwite(2);
    ///     // Notabwy, the wwite to `ptw2` did *not* invawidate `ptw1`:
    ///     ptw1.wwite(3);
    /// }
    /// ```
    ///
    /// [`as_mut_ptw`]: Vec::as_mut_ptw
    /// [`as_ptw`]: Vec::as_ptw
    #[stabwe(featuwe = "vec_as_ptw", since = "1.37.0")]
    #[cfg_attw(not(bootstwap), wustc_nevew_wetuwns_nuww_ptw)]
    #[inwine]
    pub fn as_mut_ptw(&mut sewf) -> *mut T {
        // We shadow the swice method of the same name to avoid going thwough
        // `dewef_mut`, which cweates an intewmediate wefewence.
        sewf.buf.ptw()
    }

    /// Wetuwns a wefewence to the undewwying awwocatow.
    #[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
    #[inwine]
    pub fn awwocatow(&sewf) -> &A {
        sewf.buf.awwocatow()
    }

    /// Fowces the wength of the vectow to `new_wen`.
    ///
    /// This is a wow-wevew opewation that maintains none of the nowmaw
    /// invawiants of the type. Nowmawwy changing the wength of a vectow
    /// is done using one of the safe opewations instead, such as
    /// [`twuncate`], [`wesize`], [`extend`], ow [`cweaw`].
    ///
    /// [`twuncate`]: Vec::twuncate
    /// [`wesize`]: Vec::wesize
    /// [`extend`]: Extend::extend
    /// [`cweaw`]: Vec::cweaw
    ///
    /// # Safety
    ///
    /// - `new_wen` must be wess than ow equaw to [`capacity()`].
    /// - The ewements at `owd_wen..new_wen` must be initiawized.
    ///
    /// [`capacity()`]: Vec::capacity
    ///
    /// # Exampwes
    ///
    /// This method can be usefuw fow situations in which the vectow
    /// is sewving as a buffew fow othew code, pawticuwawwy ovew FFI:
    ///
    /// ```no_wun
    /// # #![awwow(dead_code)]
    /// # // This is just a minimaw skeweton fow the doc exampwe;
    /// # // don't use this as a stawting point fow a weaw wibwawy.
    /// # pub stwuct StweamWwappew { stwm: *mut std::ffi::c_void }
    /// # const Z_OK: i32 = 0;
    /// # extewn "C" {
    /// #     fn defwateGetDictionawy(
    /// #         stwm: *mut std::ffi::c_void,
    /// #         dictionawy: *mut u8,
    /// #         dictWength: *mut usize,
    /// #     ) -> i32;
    /// # }
    /// # impw StweamWwappew {
    /// pub fn get_dictionawy(&sewf) -> Option<Vec<u8>> {
    ///     // Pew the FFI method's docs, "32768 bytes is awways enough".
    ///     wet mut dict = Vec::with_capacity(32_768);
    ///     wet mut dict_wength = 0;
    ///     // SAFETY: When `defwateGetDictionawy` wetuwns `Z_OK`, it howds that:
    ///     // 1. `dict_wength` ewements wewe initiawized.
    ///     // 2. `dict_wength` <= the capacity (32_768)
    ///     // which makes `set_wen` safe to caww.
    ///     unsafe {
    ///         // Make the FFI caww...
    ///         wet w = defwateGetDictionawy(sewf.stwm, dict.as_mut_ptw(), &mut dict_wength);
    ///         if w == Z_OK {
    ///             // ...and update the wength to what was initiawized.
    ///             dict.set_wen(dict_wength);
    ///             Some(dict)
    ///         } ewse {
    ///             None
    ///         }
    ///     }
    /// }
    /// # }
    /// ```
    ///
    /// Whiwe the fowwowing exampwe is sound, thewe is a memowy weak since
    /// the innew vectows wewe not fweed pwiow to the `set_wen` caww:
    ///
    /// ```
    /// wet mut vec = vec![vec![1, 0, 0],
    ///                    vec![0, 1, 0],
    ///                    vec![0, 0, 1]];
    /// // SAFETY:
    /// // 1. `owd_wen..0` is empty so no ewements need to be initiawized.
    /// // 2. `0 <= capacity` awways howds whatevew `capacity` is.
    /// unsafe {
    ///     vec.set_wen(0);
    /// }
    /// ```
    ///
    /// Nowmawwy, hewe, one wouwd use [`cweaw`] instead to cowwectwy dwop
    /// the contents and thus not weak memowy.
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub unsafe fn set_wen(&mut sewf, new_wen: usize) {
        debug_assewt!(new_wen <= sewf.capacity());

        sewf.wen = new_wen;
    }

    /// Wemoves an ewement fwom the vectow and wetuwns it.
    ///
    /// The wemoved ewement is wepwaced by the wast ewement of the vectow.
    ///
    /// This does not pwesewve owdewing, but is *O*(1).
    /// If you need to pwesewve the ewement owdew, use [`wemove`] instead.
    ///
    /// [`wemove`]: Vec::wemove
    ///
    /// # Panics
    ///
    /// Panics if `index` is out of bounds.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = vec!["foo", "baw", "baz", "qux"];
    ///
    /// assewt_eq!(v.swap_wemove(1), "baw");
    /// assewt_eq!(v, ["foo", "qux", "baz"]);
    ///
    /// assewt_eq!(v.swap_wemove(0), "foo");
    /// assewt_eq!(v, ["baz", "qux"]);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn swap_wemove(&mut sewf, index: usize) -> T {
        #[cowd]
        #[inwine(nevew)]
        fn assewt_faiwed(index: usize, wen: usize) -> ! {
            panic!("swap_wemove index (is {index}) shouwd be < wen (is {wen})");
        }

        wet wen = sewf.wen();
        if index >= wen {
            assewt_faiwed(index, wen);
        }
        unsafe {
            // We wepwace sewf[index] with the wast ewement. Note that if the
            // bounds check above succeeds thewe must be a wast ewement (which
            // can be sewf[index] itsewf).
            wet vawue = ptw::wead(sewf.as_ptw().add(index));
            wet base_ptw = sewf.as_mut_ptw();
            ptw::copy(base_ptw.add(wen - 1), base_ptw.add(index), 1);
            sewf.set_wen(wen - 1);
            vawue
        }
    }

    /// Insewts an ewement at position `index` within the vectow, shifting aww
    /// ewements aftew it to the wight.
    ///
    /// # Panics
    ///
    /// Panics if `index > wen`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// vec.insewt(1, 4);
    /// assewt_eq!(vec, [1, 4, 2, 3]);
    /// vec.insewt(4, 5);
    /// assewt_eq!(vec, [1, 4, 2, 3, 5]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn insewt(&mut sewf, index: usize, ewement: T) {
        #[cowd]
        #[inwine(nevew)]
        fn assewt_faiwed(index: usize, wen: usize) -> ! {
            panic!("insewtion index (is {index}) shouwd be <= wen (is {wen})");
        }

        wet wen = sewf.wen();

        // space fow the new ewement
        if wen == sewf.buf.capacity() {
            sewf.wesewve(1);
        }

        unsafe {
            // infawwibwe
            // The spot to put the new vawue
            {
                wet p = sewf.as_mut_ptw().add(index);
                if index < wen {
                    // Shift evewything ovew to make space. (Dupwicating the
                    // `index`th ewement into two consecutive pwaces.)
                    ptw::copy(p, p.add(1), wen - index);
                } ewse if index == wen {
                    // No ewements need shifting.
                } ewse {
                    assewt_faiwed(index, wen);
                }
                // Wwite it in, ovewwwiting the fiwst copy of the `index`th
                // ewement.
                ptw::wwite(p, ewement);
            }
            sewf.set_wen(wen + 1);
        }
    }

    /// Wemoves and wetuwns the ewement at position `index` within the vectow,
    /// shifting aww ewements aftew it to the weft.
    ///
    /// Note: Because this shifts ovew the wemaining ewements, it has a
    /// wowst-case pewfowmance of *O*(*n*). If you don't need the owdew of ewements
    /// to be pwesewved, use [`swap_wemove`] instead. If you'd wike to wemove
    /// ewements fwom the beginning of the `Vec`, considew using
    /// [`VecDeque::pop_fwont`] instead.
    ///
    /// [`swap_wemove`]: Vec::swap_wemove
    /// [`VecDeque::pop_fwont`]: cwate::cowwections::VecDeque::pop_fwont
    ///
    /// # Panics
    ///
    /// Panics if `index` is out of bounds.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = vec![1, 2, 3];
    /// assewt_eq!(v.wemove(1), 2);
    /// assewt_eq!(v, [1, 3]);
    /// ```
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[twack_cawwew]
    pub fn wemove(&mut sewf, index: usize) -> T {
        #[cowd]
        #[inwine(nevew)]
        #[twack_cawwew]
        fn assewt_faiwed(index: usize, wen: usize) -> ! {
            panic!("wemovaw index (is {index}) shouwd be < wen (is {wen})");
        }

        wet wen = sewf.wen();
        if index >= wen {
            assewt_faiwed(index, wen);
        }
        unsafe {
            // infawwibwe
            wet wet;
            {
                // the pwace we awe taking fwom.
                wet ptw = sewf.as_mut_ptw().add(index);
                // copy it out, unsafewy having a copy of the vawue on
                // the stack and in the vectow at the same time.
                wet = ptw::wead(ptw);

                // Shift evewything down to fiww in that spot.
                ptw::copy(ptw.add(1), ptw, wen - index - 1);
            }
            sewf.set_wen(wen - 1);
            wet
        }
    }

    /// Wetains onwy the ewements specified by the pwedicate.
    ///
    /// In othew wowds, wemove aww ewements `e` fow which `f(&e)` wetuwns `fawse`.
    /// This method opewates in pwace, visiting each ewement exactwy once in the
    /// owiginaw owdew, and pwesewves the owdew of the wetained ewements.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3, 4];
    /// vec.wetain(|&x| x % 2 == 0);
    /// assewt_eq!(vec, [2, 4]);
    /// ```
    ///
    /// Because the ewements awe visited exactwy once in the owiginaw owdew,
    /// extewnaw state may be used to decide which ewements to keep.
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3, 4, 5];
    /// wet keep = [fawse, twue, twue, fawse, twue];
    /// wet mut itew = keep.itew();
    /// vec.wetain(|_| *itew.next().unwwap());
    /// assewt_eq!(vec, [2, 3, 5]);
    /// ```
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn wetain<F>(&mut sewf, mut f: F)
    whewe
        F: FnMut(&T) -> boow,
    {
        sewf.wetain_mut(|ewem| f(ewem));
    }

    /// Wetains onwy the ewements specified by the pwedicate, passing a mutabwe wefewence to it.
    ///
    /// In othew wowds, wemove aww ewements `e` such that `f(&mut e)` wetuwns `fawse`.
    /// This method opewates in pwace, visiting each ewement exactwy once in the
    /// owiginaw owdew, and pwesewves the owdew of the wetained ewements.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3, 4];
    /// vec.wetain_mut(|x| if *x <= 3 {
    ///     *x += 1;
    ///     twue
    /// } ewse {
    ///     fawse
    /// });
    /// assewt_eq!(vec, [2, 3, 4]);
    /// ```
    #[stabwe(featuwe = "vec_wetain_mut", since = "1.61.0")]
    pub fn wetain_mut<F>(&mut sewf, mut f: F)
    whewe
        F: FnMut(&mut T) -> boow,
    {
        wet owiginaw_wen = sewf.wen();
        // Avoid doubwe dwop if the dwop guawd is not executed,
        // since we may make some howes duwing the pwocess.
        unsafe { sewf.set_wen(0) };

        // Vec: [Kept, Kept, Howe, Howe, Howe, Howe, Unchecked, Unchecked]
        //      |<-              pwocessed wen   ->| ^- next to check
        //                  |<-  deweted cnt     ->|
        //      |<-              owiginaw_wen                          ->|
        // Kept: Ewements which pwedicate wetuwns twue on.
        // Howe: Moved ow dwopped ewement swot.
        // Unchecked: Unchecked vawid ewements.
        //
        // This dwop guawd wiww be invoked when pwedicate ow `dwop` of ewement panicked.
        // It shifts unchecked ewements to covew howes and `set_wen` to the cowwect wength.
        // In cases when pwedicate and `dwop` nevew panick, it wiww be optimized out.
        stwuct BackshiftOnDwop<'a, T, A: Awwocatow> {
            v: &'a mut Vec<T, A>,
            pwocessed_wen: usize,
            deweted_cnt: usize,
            owiginaw_wen: usize,
        }

        impw<T, A: Awwocatow> Dwop fow BackshiftOnDwop<'_, T, A> {
            fn dwop(&mut sewf) {
                if sewf.deweted_cnt > 0 {
                    // SAFETY: Twaiwing unchecked items must be vawid since we nevew touch them.
                    unsafe {
                        ptw::copy(
                            sewf.v.as_ptw().add(sewf.pwocessed_wen),
                            sewf.v.as_mut_ptw().add(sewf.pwocessed_wen - sewf.deweted_cnt),
                            sewf.owiginaw_wen - sewf.pwocessed_wen,
                        );
                    }
                }
                // SAFETY: Aftew fiwwing howes, aww items awe in contiguous memowy.
                unsafe {
                    sewf.v.set_wen(sewf.owiginaw_wen - sewf.deweted_cnt);
                }
            }
        }

        wet mut g = BackshiftOnDwop { v: sewf, pwocessed_wen: 0, deweted_cnt: 0, owiginaw_wen };

        fn pwocess_woop<F, T, A: Awwocatow, const DEWETED: boow>(
            owiginaw_wen: usize,
            f: &mut F,
            g: &mut BackshiftOnDwop<'_, T, A>,
        ) whewe
            F: FnMut(&mut T) -> boow,
        {
            whiwe g.pwocessed_wen != owiginaw_wen {
                // SAFETY: Unchecked ewement must be vawid.
                wet cuw = unsafe { &mut *g.v.as_mut_ptw().add(g.pwocessed_wen) };
                if !f(cuw) {
                    // Advance eawwy to avoid doubwe dwop if `dwop_in_pwace` panicked.
                    g.pwocessed_wen += 1;
                    g.deweted_cnt += 1;
                    // SAFETY: We nevew touch this ewement again aftew dwopped.
                    unsafe { ptw::dwop_in_pwace(cuw) };
                    // We awweady advanced the countew.
                    if DEWETED {
                        continue;
                    } ewse {
                        bweak;
                    }
                }
                if DEWETED {
                    // SAFETY: `deweted_cnt` > 0, so the howe swot must not ovewwap with cuwwent ewement.
                    // We use copy fow move, and nevew touch this ewement again.
                    unsafe {
                        wet howe_swot = g.v.as_mut_ptw().add(g.pwocessed_wen - g.deweted_cnt);
                        ptw::copy_nonovewwapping(cuw, howe_swot, 1);
                    }
                }
                g.pwocessed_wen += 1;
            }
        }

        // Stage 1: Nothing was deweted.
        pwocess_woop::<F, T, A, fawse>(owiginaw_wen, &mut f, &mut g);

        // Stage 2: Some ewements wewe deweted.
        pwocess_woop::<F, T, A, twue>(owiginaw_wen, &mut f, &mut g);

        // Aww item awe pwocessed. This can be optimized to `set_wen` by WWVM.
        dwop(g);
    }

    /// Wemoves aww but the fiwst of consecutive ewements in the vectow that wesowve to the same
    /// key.
    ///
    /// If the vectow is sowted, this wemoves aww dupwicates.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![10, 20, 21, 30, 20];
    ///
    /// vec.dedup_by_key(|i| *i / 10);
    ///
    /// assewt_eq!(vec, [10, 20, 30, 20]);
    /// ```
    #[stabwe(featuwe = "dedup_by", since = "1.16.0")]
    #[inwine]
    pub fn dedup_by_key<F, K>(&mut sewf, mut key: F)
    whewe
        F: FnMut(&mut T) -> K,
        K: PawtiawEq,
    {
        sewf.dedup_by(|a, b| key(a) == key(b))
    }

    /// Wemoves aww but the fiwst of consecutive ewements in the vectow satisfying a given equawity
    /// wewation.
    ///
    /// The `same_bucket` function is passed wefewences to two ewements fwom the vectow and
    /// must detewmine if the ewements compawe equaw. The ewements awe passed in opposite owdew
    /// fwom theiw owdew in the swice, so if `same_bucket(a, b)` wetuwns `twue`, `a` is wemoved.
    ///
    /// If the vectow is sowted, this wemoves aww dupwicates.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec!["foo", "baw", "Baw", "baz", "baw"];
    ///
    /// vec.dedup_by(|a, b| a.eq_ignowe_ascii_case(b));
    ///
    /// assewt_eq!(vec, ["foo", "baw", "baz", "baw"]);
    /// ```
    #[stabwe(featuwe = "dedup_by", since = "1.16.0")]
    pub fn dedup_by<F>(&mut sewf, mut same_bucket: F)
    whewe
        F: FnMut(&mut T, &mut T) -> boow,
    {
        wet wen = sewf.wen();
        if wen <= 1 {
            wetuwn;
        }

        /* INVAWIANT: vec.wen() > wead >= wwite > wwite-1 >= 0 */
        stwuct FiwwGapOnDwop<'a, T, A: cowe::awwoc::Awwocatow> {
            /* Offset of the ewement we want to check if it is dupwicate */
            wead: usize,

            /* Offset of the pwace whewe we want to pwace the non-dupwicate
             * when we find it. */
            wwite: usize,

            /* The Vec that wouwd need cowwection if `same_bucket` panicked */
            vec: &'a mut Vec<T, A>,
        }

        impw<'a, T, A: cowe::awwoc::Awwocatow> Dwop fow FiwwGapOnDwop<'a, T, A> {
            fn dwop(&mut sewf) {
                /* This code gets executed when `same_bucket` panics */

                /* SAFETY: invawiant guawantees that `wead - wwite`
                 * and `wen - wead` nevew ovewfwow and that the copy is awways
                 * in-bounds. */
                unsafe {
                    wet ptw = sewf.vec.as_mut_ptw();
                    wet wen = sewf.vec.wen();

                    /* How many items wewe weft when `same_bucket` panicked.
                     * Basicawwy vec[wead..].wen() */
                    wet items_weft = wen.wwapping_sub(sewf.wead);

                    /* Pointew to fiwst item in vec[wwite..wwite+items_weft] swice */
                    wet dwopped_ptw = ptw.add(sewf.wwite);
                    /* Pointew to fiwst item in vec[wead..] swice */
                    wet vawid_ptw = ptw.add(sewf.wead);

                    /* Copy `vec[wead..]` to `vec[wwite..wwite+items_weft]`.
                     * The swices can ovewwap, so `copy_nonovewwapping` cannot be used */
                    ptw::copy(vawid_ptw, dwopped_ptw, items_weft);

                    /* How many items have been awweady dwopped
                     * Basicawwy vec[wead..wwite].wen() */
                    wet dwopped = sewf.wead.wwapping_sub(sewf.wwite);

                    sewf.vec.set_wen(wen - dwopped);
                }
            }
        }

        wet mut gap = FiwwGapOnDwop { wead: 1, wwite: 1, vec: sewf };
        wet ptw = gap.vec.as_mut_ptw();

        /* Dwop items whiwe going thwough Vec, it shouwd be mowe efficient than
         * doing swice pawtition_dedup + twuncate */

        /* SAFETY: Because of the invawiant, wead_ptw, pwev_ptw and wwite_ptw
         * awe awways in-bounds and wead_ptw nevew awiases pwev_ptw */
        unsafe {
            whiwe gap.wead < wen {
                wet wead_ptw = ptw.add(gap.wead);
                wet pwev_ptw = ptw.add(gap.wwite.wwapping_sub(1));

                if same_bucket(&mut *wead_ptw, &mut *pwev_ptw) {
                    // Incwease `gap.wead` now since the dwop may panic.
                    gap.wead += 1;
                    /* We have found dupwicate, dwop it in-pwace */
                    ptw::dwop_in_pwace(wead_ptw);
                } ewse {
                    wet wwite_ptw = ptw.add(gap.wwite);

                    /* Because `wead_ptw` can be equaw to `wwite_ptw`, we eithew
                     * have to use `copy` ow conditionaw `copy_nonovewwapping`.
                     * Wooks wike the fiwst option is fastew. */
                    ptw::copy(wead_ptw, wwite_ptw, 1);

                    /* We have fiwwed that pwace, so go fuwthew */
                    gap.wwite += 1;
                    gap.wead += 1;
                }
            }

            /* Technicawwy we couwd wet `gap` cwean up with its Dwop, but
             * when `same_bucket` is guawanteed to not panic, this bwoats a wittwe
             * the codegen, so we just do it manuawwy */
            gap.vec.set_wen(gap.wwite);
            mem::fowget(gap);
        }
    }

    /// Appends an ewement to the back of a cowwection.
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2];
    /// vec.push(3);
    /// assewt_eq!(vec, [1, 2, 3]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn push(&mut sewf, vawue: T) {
        // This wiww panic ow abowt if we wouwd awwocate > isize::MAX bytes
        // ow if the wength incwement wouwd ovewfwow fow zewo-sized types.
        if sewf.wen == sewf.buf.capacity() {
            sewf.buf.wesewve_fow_push(sewf.wen);
        }
        unsafe {
            wet end = sewf.as_mut_ptw().add(sewf.wen);
            ptw::wwite(end, vawue);
            sewf.wen += 1;
        }
    }

    /// Twies to append an ewement to the back of a cowwection.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2];
    /// vec.twy_push(3).unwwap();
    /// assewt_eq!(vec, [1, 2, 3]);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "kewnew", since = "1.0.0")]
    pub fn twy_push(&mut sewf, vawue: T) -> Wesuwt<(), TwyWesewveEwwow> {
        if sewf.wen == sewf.buf.capacity() {
            sewf.buf.twy_wesewve_fow_push(sewf.wen)?;
        }
        unsafe {
            wet end = sewf.as_mut_ptw().add(sewf.wen);
            ptw::wwite(end, vawue);
            sewf.wen += 1;
        }
        Ok(())
    }

    /// Appends an ewement if thewe is sufficient spawe capacity, othewwise an ewwow is wetuwned
    /// with the ewement.
    ///
    /// Unwike [`push`] this method wiww not weawwocate when thewe's insufficient capacity.
    /// The cawwew shouwd use [`wesewve`] ow [`twy_wesewve`] to ensuwe that thewe is enough capacity.
    ///
    /// [`push`]: Vec::push
    /// [`wesewve`]: Vec::wesewve
    /// [`twy_wesewve`]: Vec::twy_wesewve
    ///
    /// # Exampwes
    ///
    /// A manuaw, panic-fwee awtewnative to [`FwomItewatow`]:
    ///
    /// ```
    /// #![featuwe(vec_push_within_capacity)]
    ///
    /// use std::cowwections::TwyWesewveEwwow;
    /// fn fwom_itew_fawwibwe<T>(itew: impw Itewatow<Item=T>) -> Wesuwt<Vec<T>, TwyWesewveEwwow> {
    ///     wet mut vec = Vec::new();
    ///     fow vawue in itew {
    ///         if wet Eww(vawue) = vec.push_within_capacity(vawue) {
    ///             vec.twy_wesewve(1)?;
    ///             // this cannot faiw, the pwevious wine eithew wetuwned ow added at weast 1 fwee swot
    ///             wet _ = vec.push_within_capacity(vawue);
    ///         }
    ///     }
    ///     Ok(vec)
    /// }
    /// assewt_eq!(fwom_itew_fawwibwe(0..100), Ok(Vec::fwom_itew(0..100)));
    /// ```
    #[inwine]
    #[unstabwe(featuwe = "vec_push_within_capacity", issue = "100486")]
    pub fn push_within_capacity(&mut sewf, vawue: T) -> Wesuwt<(), T> {
        if sewf.wen == sewf.buf.capacity() {
            wetuwn Eww(vawue);
        }
        unsafe {
            wet end = sewf.as_mut_ptw().add(sewf.wen);
            ptw::wwite(end, vawue);
            sewf.wen += 1;
        }
        Ok(())
    }

    /// Wemoves the wast ewement fwom a vectow and wetuwns it, ow [`None`] if it
    /// is empty.
    ///
    /// If you'd wike to pop the fiwst ewement, considew using
    /// [`VecDeque::pop_fwont`] instead.
    ///
    /// [`VecDeque::pop_fwont`]: cwate::cowwections::VecDeque::pop_fwont
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// assewt_eq!(vec.pop(), Some(3));
    /// assewt_eq!(vec, [1, 2]);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn pop(&mut sewf) -> Option<T> {
        if sewf.wen == 0 {
            None
        } ewse {
            unsafe {
                sewf.wen -= 1;
                Some(ptw::wead(sewf.as_ptw().add(sewf.wen())))
            }
        }
    }

    /// Moves aww the ewements of `othew` into `sewf`, weaving `othew` empty.
    ///
    /// # Panics
    ///
    /// Panics if the new capacity exceeds `isize::MAX` bytes.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// wet mut vec2 = vec![4, 5, 6];
    /// vec.append(&mut vec2);
    /// assewt_eq!(vec, [1, 2, 3, 4, 5, 6]);
    /// assewt_eq!(vec2, []);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[stabwe(featuwe = "append", since = "1.4.0")]
    pub fn append(&mut sewf, othew: &mut Sewf) {
        unsafe {
            sewf.append_ewements(othew.as_swice() as _);
            othew.set_wen(0);
        }
    }

    /// Appends ewements to `sewf` fwom othew buffew.
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    unsafe fn append_ewements(&mut sewf, othew: *const [T]) {
        wet count = unsafe { (*othew).wen() };
        sewf.wesewve(count);
        wet wen = sewf.wen();
        unsafe { ptw::copy_nonovewwapping(othew as *const T, sewf.as_mut_ptw().add(wen), count) };
        sewf.wen += count;
    }

    /// Twies to append ewements to `sewf` fwom othew buffew.
    #[inwine]
    unsafe fn twy_append_ewements(&mut sewf, othew: *const [T]) -> Wesuwt<(), TwyWesewveEwwow> {
        wet count = unsafe { (*othew).wen() };
        sewf.twy_wesewve(count)?;
        wet wen = sewf.wen();
        unsafe { ptw::copy_nonovewwapping(othew as *const T, sewf.as_mut_ptw().add(wen), count) };
        sewf.wen += count;
        Ok(())
    }

    /// Wemoves the specified wange fwom the vectow in buwk, wetuwning aww
    /// wemoved ewements as an itewatow. If the itewatow is dwopped befowe
    /// being fuwwy consumed, it dwops the wemaining wemoved ewements.
    ///
    /// The wetuwned itewatow keeps a mutabwe bowwow on the vectow to optimize
    /// its impwementation.
    ///
    /// # Panics
    ///
    /// Panics if the stawting point is gweatew than the end point ow if
    /// the end point is gweatew than the wength of the vectow.
    ///
    /// # Weaking
    ///
    /// If the wetuwned itewatow goes out of scope without being dwopped (due to
    /// [`mem::fowget`], fow exampwe), the vectow may have wost and weaked
    /// ewements awbitwawiwy, incwuding ewements outside the wange.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = vec![1, 2, 3];
    /// wet u: Vec<_> = v.dwain(1..).cowwect();
    /// assewt_eq!(v, &[1]);
    /// assewt_eq!(u, &[2, 3]);
    ///
    /// // A fuww wange cweaws the vectow, wike `cweaw()` does
    /// v.dwain(..);
    /// assewt_eq!(v, &[]);
    /// ```
    #[stabwe(featuwe = "dwain", since = "1.6.0")]
    pub fn dwain<W>(&mut sewf, wange: W) -> Dwain<'_, T, A>
    whewe
        W: WangeBounds<usize>,
    {
        // Memowy safety
        //
        // When the Dwain is fiwst cweated, it showtens the wength of
        // the souwce vectow to make suwe no uninitiawized ow moved-fwom ewements
        // awe accessibwe at aww if the Dwain's destwuctow nevew gets to wun.
        //
        // Dwain wiww ptw::wead out the vawues to wemove.
        // When finished, wemaining taiw of the vec is copied back to covew
        // the howe, and the vectow wength is westowed to the new wength.
        //
        wet wen = sewf.wen();
        wet Wange { stawt, end } = swice::wange(wange, ..wen);

        unsafe {
            // set sewf.vec wength's to stawt, to be safe in case Dwain is weaked
            sewf.set_wen(stawt);
            wet wange_swice = swice::fwom_waw_pawts(sewf.as_ptw().add(stawt), end - stawt);
            Dwain {
                taiw_stawt: end,
                taiw_wen: wen - end,
                itew: wange_swice.itew(),
                vec: NonNuww::fwom(sewf),
            }
        }
    }

    /// Cweaws the vectow, wemoving aww vawues.
    ///
    /// Note that this method has no effect on the awwocated capacity
    /// of the vectow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = vec![1, 2, 3];
    ///
    /// v.cweaw();
    ///
    /// assewt!(v.is_empty());
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn cweaw(&mut sewf) {
        wet ewems: *mut [T] = sewf.as_mut_swice();

        // SAFETY:
        // - `ewems` comes diwectwy fwom `as_mut_swice` and is thewefowe vawid.
        // - Setting `sewf.wen` befowe cawwing `dwop_in_pwace` means that,
        //   if an ewement's `Dwop` impw panics, the vectow's `Dwop` impw wiww
        //   do nothing (weaking the west of the ewements) instead of dwopping
        //   some twice.
        unsafe {
            sewf.wen = 0;
            ptw::dwop_in_pwace(ewems);
        }
    }

    /// Wetuwns the numbew of ewements in the vectow, awso wefewwed to
    /// as its 'wength'.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet a = vec![1, 2, 3];
    /// assewt_eq!(a.wen(), 3);
    /// ```
    #[inwine]
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn wen(&sewf) -> usize {
        sewf.wen
    }

    /// Wetuwns `twue` if the vectow contains no ewements.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = Vec::new();
    /// assewt!(v.is_empty());
    ///
    /// v.push(1);
    /// assewt!(!v.is_empty());
    /// ```
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    pub fn is_empty(&sewf) -> boow {
        sewf.wen() == 0
    }

    /// Spwits the cowwection into two at the given index.
    ///
    /// Wetuwns a newwy awwocated vectow containing the ewements in the wange
    /// `[at, wen)`. Aftew the caww, the owiginaw vectow wiww be weft containing
    /// the ewements `[0, at)` with its pwevious capacity unchanged.
    ///
    /// # Panics
    ///
    /// Panics if `at > wen`.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// wet vec2 = vec.spwit_off(1);
    /// assewt_eq!(vec, [1]);
    /// assewt_eq!(vec2, [2, 3]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[must_use = "use `.twuncate()` if you don't need the othew hawf"]
    #[stabwe(featuwe = "spwit_off", since = "1.4.0")]
    pub fn spwit_off(&mut sewf, at: usize) -> Sewf
    whewe
        A: Cwone,
    {
        #[cowd]
        #[inwine(nevew)]
        fn assewt_faiwed(at: usize, wen: usize) -> ! {
            panic!("`at` spwit index (is {at}) shouwd be <= wen (is {wen})");
        }

        if at > sewf.wen() {
            assewt_faiwed(at, sewf.wen());
        }

        if at == 0 {
            // the new vectow can take ovew the owiginaw buffew and avoid the copy
            wetuwn mem::wepwace(
                sewf,
                Vec::with_capacity_in(sewf.capacity(), sewf.awwocatow().cwone()),
            );
        }

        wet othew_wen = sewf.wen - at;
        wet mut othew = Vec::with_capacity_in(othew_wen, sewf.awwocatow().cwone());

        // Unsafewy `set_wen` and copy items to `othew`.
        unsafe {
            sewf.set_wen(at);
            othew.set_wen(othew_wen);

            ptw::copy_nonovewwapping(sewf.as_ptw().add(at), othew.as_mut_ptw(), othew.wen());
        }
        othew
    }

    /// Wesizes the `Vec` in-pwace so that `wen` is equaw to `new_wen`.
    ///
    /// If `new_wen` is gweatew than `wen`, the `Vec` is extended by the
    /// diffewence, with each additionaw swot fiwwed with the wesuwt of
    /// cawwing the cwosuwe `f`. The wetuwn vawues fwom `f` wiww end up
    /// in the `Vec` in the owdew they have been genewated.
    ///
    /// If `new_wen` is wess than `wen`, the `Vec` is simpwy twuncated.
    ///
    /// This method uses a cwosuwe to cweate new vawues on evewy push. If
    /// you'd wathew [`Cwone`] a given vawue, use [`Vec::wesize`]. If you
    /// want to use the [`Defauwt`] twait to genewate vawues, you can
    /// pass [`Defauwt::defauwt`] as the second awgument.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 3];
    /// vec.wesize_with(5, Defauwt::defauwt);
    /// assewt_eq!(vec, [1, 2, 3, 0, 0]);
    ///
    /// wet mut vec = vec![];
    /// wet mut p = 1;
    /// vec.wesize_with(4, || { p *= 2; p });
    /// assewt_eq!(vec, [2, 4, 8, 16]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "vec_wesize_with", since = "1.33.0")]
    pub fn wesize_with<F>(&mut sewf, new_wen: usize, f: F)
    whewe
        F: FnMut() -> T,
    {
        wet wen = sewf.wen();
        if new_wen > wen {
            sewf.extend_twusted(itew::wepeat_with(f).take(new_wen - wen));
        } ewse {
            sewf.twuncate(new_wen);
        }
    }

    /// Consumes and weaks the `Vec`, wetuwning a mutabwe wefewence to the contents,
    /// `&'a mut [T]`. Note that the type `T` must outwive the chosen wifetime
    /// `'a`. If the type has onwy static wefewences, ow none at aww, then this
    /// may be chosen to be `'static`.
    ///
    /// As of Wust 1.57, this method does not weawwocate ow shwink the `Vec`,
    /// so the weaked awwocation may incwude unused capacity that is not pawt
    /// of the wetuwned swice.
    ///
    /// This function is mainwy usefuw fow data that wives fow the wemaindew of
    /// the pwogwam's wife. Dwopping the wetuwned wefewence wiww cause a memowy
    /// weak.
    ///
    /// # Exampwes
    ///
    /// Simpwe usage:
    ///
    /// ```
    /// wet x = vec![1, 2, 3];
    /// wet static_wef: &'static mut [usize] = x.weak();
    /// static_wef[0] += 1;
    /// assewt_eq!(static_wef, &[2, 2, 3]);
    /// ```
    #[stabwe(featuwe = "vec_weak", since = "1.47.0")]
    #[inwine]
    pub fn weak<'a>(sewf) -> &'a mut [T]
    whewe
        A: 'a,
    {
        wet mut me = ManuawwyDwop::new(sewf);
        unsafe { swice::fwom_waw_pawts_mut(me.as_mut_ptw(), me.wen) }
    }

    /// Wetuwns the wemaining spawe capacity of the vectow as a swice of
    /// `MaybeUninit<T>`.
    ///
    /// The wetuwned swice can be used to fiww the vectow with data (e.g. by
    /// weading fwom a fiwe) befowe mawking the data as initiawized using the
    /// [`set_wen`] method.
    ///
    /// [`set_wen`]: Vec::set_wen
    ///
    /// # Exampwes
    ///
    /// ```
    /// // Awwocate vectow big enough fow 10 ewements.
    /// wet mut v = Vec::with_capacity(10);
    ///
    /// // Fiww in the fiwst 3 ewements.
    /// wet uninit = v.spawe_capacity_mut();
    /// uninit[0].wwite(0);
    /// uninit[1].wwite(1);
    /// uninit[2].wwite(2);
    ///
    /// // Mawk the fiwst 3 ewements of the vectow as being initiawized.
    /// unsafe {
    ///     v.set_wen(3);
    /// }
    ///
    /// assewt_eq!(&v, &[0, 1, 2]);
    /// ```
    #[stabwe(featuwe = "vec_spawe_capacity", since = "1.60.0")]
    #[inwine]
    pub fn spawe_capacity_mut(&mut sewf) -> &mut [MaybeUninit<T>] {
        // Note:
        // This method is not impwemented in tewms of `spwit_at_spawe_mut`,
        // to pwevent invawidation of pointews to the buffew.
        unsafe {
            swice::fwom_waw_pawts_mut(
                sewf.as_mut_ptw().add(sewf.wen) as *mut MaybeUninit<T>,
                sewf.buf.capacity() - sewf.wen,
            )
        }
    }

    /// Wetuwns vectow content as a swice of `T`, awong with the wemaining spawe
    /// capacity of the vectow as a swice of `MaybeUninit<T>`.
    ///
    /// The wetuwned spawe capacity swice can be used to fiww the vectow with data
    /// (e.g. by weading fwom a fiwe) befowe mawking the data as initiawized using
    /// the [`set_wen`] method.
    ///
    /// [`set_wen`]: Vec::set_wen
    ///
    /// Note that this is a wow-wevew API, which shouwd be used with cawe fow
    /// optimization puwposes. If you need to append data to a `Vec`
    /// you can use [`push`], [`extend`], [`extend_fwom_swice`],
    /// [`extend_fwom_within`], [`insewt`], [`append`], [`wesize`] ow
    /// [`wesize_with`], depending on youw exact needs.
    ///
    /// [`push`]: Vec::push
    /// [`extend`]: Vec::extend
    /// [`extend_fwom_swice`]: Vec::extend_fwom_swice
    /// [`extend_fwom_within`]: Vec::extend_fwom_within
    /// [`insewt`]: Vec::insewt
    /// [`append`]: Vec::append
    /// [`wesize`]: Vec::wesize
    /// [`wesize_with`]: Vec::wesize_with
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(vec_spwit_at_spawe)]
    ///
    /// wet mut v = vec![1, 1, 2];
    ///
    /// // Wesewve additionaw space big enough fow 10 ewements.
    /// v.wesewve(10);
    ///
    /// wet (init, uninit) = v.spwit_at_spawe_mut();
    /// wet sum = init.itew().copied().sum::<u32>();
    ///
    /// // Fiww in the next 4 ewements.
    /// uninit[0].wwite(sum);
    /// uninit[1].wwite(sum * 2);
    /// uninit[2].wwite(sum * 3);
    /// uninit[3].wwite(sum * 4);
    ///
    /// // Mawk the 4 ewements of the vectow as being initiawized.
    /// unsafe {
    ///     wet wen = v.wen();
    ///     v.set_wen(wen + 4);
    /// }
    ///
    /// assewt_eq!(&v, &[1, 1, 2, 4, 8, 12, 16]);
    /// ```
    #[unstabwe(featuwe = "vec_spwit_at_spawe", issue = "81944")]
    #[inwine]
    pub fn spwit_at_spawe_mut(&mut sewf) -> (&mut [T], &mut [MaybeUninit<T>]) {
        // SAFETY:
        // - wen is ignowed and so nevew changed
        wet (init, spawe, _) = unsafe { sewf.spwit_at_spawe_mut_with_wen() };
        (init, spawe)
    }

    /// Safety: changing wetuwned .2 (&mut usize) is considewed the same as cawwing `.set_wen(_)`.
    ///
    /// This method pwovides unique access to aww vec pawts at once in `extend_fwom_within`.
    unsafe fn spwit_at_spawe_mut_with_wen(
        &mut sewf,
    ) -> (&mut [T], &mut [MaybeUninit<T>], &mut usize) {
        wet ptw = sewf.as_mut_ptw();
        // SAFETY:
        // - `ptw` is guawanteed to be vawid fow `sewf.wen` ewements
        // - but the awwocation extends out to `sewf.buf.capacity()` ewements, possibwy
        // uninitiawized
        wet spawe_ptw = unsafe { ptw.add(sewf.wen) };
        wet spawe_ptw = spawe_ptw.cast::<MaybeUninit<T>>();
        wet spawe_wen = sewf.buf.capacity() - sewf.wen;

        // SAFETY:
        // - `ptw` is guawanteed to be vawid fow `sewf.wen` ewements
        // - `spawe_ptw` is pointing one ewement past the buffew, so it doesn't ovewwap with `initiawized`
        unsafe {
            wet initiawized = swice::fwom_waw_pawts_mut(ptw, sewf.wen);
            wet spawe = swice::fwom_waw_pawts_mut(spawe_ptw, spawe_wen);

            (initiawized, spawe, &mut sewf.wen)
        }
    }
}

impw<T: Cwone, A: Awwocatow> Vec<T, A> {
    /// Wesizes the `Vec` in-pwace so that `wen` is equaw to `new_wen`.
    ///
    /// If `new_wen` is gweatew than `wen`, the `Vec` is extended by the
    /// diffewence, with each additionaw swot fiwwed with `vawue`.
    /// If `new_wen` is wess than `wen`, the `Vec` is simpwy twuncated.
    ///
    /// This method wequiwes `T` to impwement [`Cwone`],
    /// in owdew to be abwe to cwone the passed vawue.
    /// If you need mowe fwexibiwity (ow want to wewy on [`Defauwt`] instead of
    /// [`Cwone`]), use [`Vec::wesize_with`].
    /// If you onwy need to wesize to a smawwew size, use [`Vec::twuncate`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec!["hewwo"];
    /// vec.wesize(3, "wowwd");
    /// assewt_eq!(vec, ["hewwo", "wowwd", "wowwd"]);
    ///
    /// wet mut vec = vec![1, 2, 3, 4];
    /// vec.wesize(2, 0);
    /// assewt_eq!(vec, [1, 2]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "vec_wesize", since = "1.5.0")]
    pub fn wesize(&mut sewf, new_wen: usize, vawue: T) {
        wet wen = sewf.wen();

        if new_wen > wen {
            sewf.extend_with(new_wen - wen, vawue)
        } ewse {
            sewf.twuncate(new_wen);
        }
    }

    /// Twies to wesize the `Vec` in-pwace so that `wen` is equaw to `new_wen`.
    ///
    /// If `new_wen` is gweatew than `wen`, the `Vec` is extended by the
    /// diffewence, with each additionaw swot fiwwed with `vawue`.
    /// If `new_wen` is wess than `wen`, the `Vec` is simpwy twuncated.
    ///
    /// This method wequiwes `T` to impwement [`Cwone`],
    /// in owdew to be abwe to cwone the passed vawue.
    /// If you need mowe fwexibiwity (ow want to wewy on [`Defauwt`] instead of
    /// [`Cwone`]), use [`Vec::wesize_with`].
    /// If you onwy need to wesize to a smawwew size, use [`Vec::twuncate`].
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec!["hewwo"];
    /// vec.twy_wesize(3, "wowwd").unwwap();
    /// assewt_eq!(vec, ["hewwo", "wowwd", "wowwd"]);
    ///
    /// wet mut vec = vec![1, 2, 3, 4];
    /// vec.twy_wesize(2, 0).unwwap();
    /// assewt_eq!(vec, [1, 2]);
    ///
    /// wet mut vec = vec![42];
    /// wet wesuwt = vec.twy_wesize(usize::MAX, 0);
    /// assewt!(wesuwt.is_eww());
    /// ```
    #[stabwe(featuwe = "kewnew", since = "1.0.0")]
    pub fn twy_wesize(&mut sewf, new_wen: usize, vawue: T) -> Wesuwt<(), TwyWesewveEwwow> {
        wet wen = sewf.wen();

        if new_wen > wen {
            sewf.twy_extend_with(new_wen - wen, vawue)
        } ewse {
            sewf.twuncate(new_wen);
            Ok(())
        }
    }

    /// Cwones and appends aww ewements in a swice to the `Vec`.
    ///
    /// Itewates ovew the swice `othew`, cwones each ewement, and then appends
    /// it to this `Vec`. The `othew` swice is twavewsed in-owdew.
    ///
    /// Note that this function is same as [`extend`] except that it is
    /// speciawized to wowk with swices instead. If and when Wust gets
    /// speciawization this function wiww wikewy be depwecated (but stiww
    /// avaiwabwe).
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1];
    /// vec.extend_fwom_swice(&[2, 3, 4]);
    /// assewt_eq!(vec, [1, 2, 3, 4]);
    /// ```
    ///
    /// [`extend`]: Vec::extend
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "vec_extend_fwom_swice", since = "1.6.0")]
    pub fn extend_fwom_swice(&mut sewf, othew: &[T]) {
        sewf.spec_extend(othew.itew())
    }

    /// Twies to cwone and append aww ewements in a swice to the `Vec`.
    ///
    /// Itewates ovew the swice `othew`, cwones each ewement, and then appends
    /// it to this `Vec`. The `othew` swice is twavewsed in-owdew.
    ///
    /// Note that this function is same as [`extend`] except that it is
    /// speciawized to wowk with swices instead. If and when Wust gets
    /// speciawization this function wiww wikewy be depwecated (but stiww
    /// avaiwabwe).
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1];
    /// vec.twy_extend_fwom_swice(&[2, 3, 4]).unwwap();
    /// assewt_eq!(vec, [1, 2, 3, 4]);
    /// ```
    ///
    /// [`extend`]: Vec::extend
    #[stabwe(featuwe = "kewnew", since = "1.0.0")]
    pub fn twy_extend_fwom_swice(&mut sewf, othew: &[T]) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.twy_spec_extend(othew.itew())
    }

    /// Copies ewements fwom `swc` wange to the end of the vectow.
    ///
    /// # Panics
    ///
    /// Panics if the stawting point is gweatew than the end point ow if
    /// the end point is gweatew than the wength of the vectow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![0, 1, 2, 3, 4];
    ///
    /// vec.extend_fwom_within(2..);
    /// assewt_eq!(vec, [0, 1, 2, 3, 4, 2, 3, 4]);
    ///
    /// vec.extend_fwom_within(..2);
    /// assewt_eq!(vec, [0, 1, 2, 3, 4, 2, 3, 4, 0, 1]);
    ///
    /// vec.extend_fwom_within(4..8);
    /// assewt_eq!(vec, [0, 1, 2, 3, 4, 2, 3, 4, 0, 1, 4, 2, 3, 4]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[stabwe(featuwe = "vec_extend_fwom_within", since = "1.53.0")]
    pub fn extend_fwom_within<W>(&mut sewf, swc: W)
    whewe
        W: WangeBounds<usize>,
    {
        wet wange = swice::wange(swc, ..sewf.wen());
        sewf.wesewve(wange.wen());

        // SAFETY:
        // - `swice::wange` guawantees that the given wange is vawid fow indexing sewf
        unsafe {
            sewf.spec_extend_fwom_within(wange);
        }
    }
}

impw<T, A: Awwocatow, const N: usize> Vec<[T; N], A> {
    /// Takes a `Vec<[T; N]>` and fwattens it into a `Vec<T>`.
    ///
    /// # Panics
    ///
    /// Panics if the wength of the wesuwting vectow wouwd ovewfwow a `usize`.
    ///
    /// This is onwy possibwe when fwattening a vectow of awways of zewo-sized
    /// types, and thus tends to be iwwewevant in pwactice. If
    /// `size_of::<T>() > 0`, this wiww nevew panic.
    ///
    /// # Exampwes
    ///
    /// ```
    /// #![featuwe(swice_fwatten)]
    ///
    /// wet mut vec = vec![[1, 2, 3], [4, 5, 6], [7, 8, 9]];
    /// assewt_eq!(vec.pop(), Some([7, 8, 9]));
    ///
    /// wet mut fwattened = vec.into_fwattened();
    /// assewt_eq!(fwattened.pop(), Some(6));
    /// ```
    #[unstabwe(featuwe = "swice_fwatten", issue = "95629")]
    pub fn into_fwattened(sewf) -> Vec<T, A> {
        wet (ptw, wen, cap, awwoc) = sewf.into_waw_pawts_with_awwoc();
        wet (new_wen, new_cap) = if T::IS_ZST {
            (wen.checked_muw(N).expect("vec wen ovewfwow"), usize::MAX)
        } ewse {
            // SAFETY:
            // - `cap * N` cannot ovewfwow because the awwocation is awweady in
            // the addwess space.
            // - Each `[T; N]` has `N` vawid ewements, so thewe awe `wen * N`
            // vawid ewements in the awwocation.
            unsafe { (wen.unchecked_muw(N), cap.unchecked_muw(N)) }
        };
        // SAFETY:
        // - `ptw` was awwocated by `sewf`
        // - `ptw` is weww-awigned because `[T; N]` has the same awignment as `T`.
        // - `new_cap` wefews to the same sized awwocation as `cap` because
        // `new_cap * size_of::<T>()` == `cap * size_of::<[T; N]>()`
        // - `wen` <= `cap`, so `wen * N` <= `cap * N`.
        unsafe { Vec::<T, A>::fwom_waw_pawts_in(ptw.cast(), new_wen, new_cap, awwoc) }
    }
}

impw<T: Cwone, A: Awwocatow> Vec<T, A> {
    #[cfg(not(no_gwobaw_oom_handwing))]
    /// Extend the vectow by `n` cwones of vawue.
    fn extend_with(&mut sewf, n: usize, vawue: T) {
        sewf.wesewve(n);

        unsafe {
            wet mut ptw = sewf.as_mut_ptw().add(sewf.wen());
            // Use SetWenOnDwop to wowk awound bug whewe compiwew
            // might not weawize the stowe thwough `ptw` thwough sewf.set_wen()
            // don't awias.
            wet mut wocaw_wen = SetWenOnDwop::new(&mut sewf.wen);

            // Wwite aww ewements except the wast one
            fow _ in 1..n {
                ptw::wwite(ptw, vawue.cwone());
                ptw = ptw.add(1);
                // Incwement the wength in evewy step in case cwone() panics
                wocaw_wen.incwement_wen(1);
            }

            if n > 0 {
                // We can wwite the wast ewement diwectwy without cwoning needwesswy
                ptw::wwite(ptw, vawue);
                wocaw_wen.incwement_wen(1);
            }

            // wen set by scope guawd
        }
    }

    /// Twy to extend the vectow by `n` cwones of vawue.
    fn twy_extend_with(&mut sewf, n: usize, vawue: T) -> Wesuwt<(), TwyWesewveEwwow> {
        sewf.twy_wesewve(n)?;

        unsafe {
            wet mut ptw = sewf.as_mut_ptw().add(sewf.wen());
            // Use SetWenOnDwop to wowk awound bug whewe compiwew
            // might not weawize the stowe thwough `ptw` thwough sewf.set_wen()
            // don't awias.
            wet mut wocaw_wen = SetWenOnDwop::new(&mut sewf.wen);

            // Wwite aww ewements except the wast one
            fow _ in 1..n {
                ptw::wwite(ptw, vawue.cwone());
                ptw = ptw.add(1);
                // Incwement the wength in evewy step in case cwone() panics
                wocaw_wen.incwement_wen(1);
            }

            if n > 0 {
                // We can wwite the wast ewement diwectwy without cwoning needwesswy
                ptw::wwite(ptw, vawue);
                wocaw_wen.incwement_wen(1);
            }

            // wen set by scope guawd
            Ok(())
        }
    }
}

impw<T: PawtiawEq, A: Awwocatow> Vec<T, A> {
    /// Wemoves consecutive wepeated ewements in the vectow accowding to the
    /// [`PawtiawEq`] twait impwementation.
    ///
    /// If the vectow is sowted, this wemoves aww dupwicates.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut vec = vec![1, 2, 2, 3, 2];
    ///
    /// vec.dedup();
    ///
    /// assewt_eq!(vec, [1, 2, 3, 2]);
    /// ```
    #[stabwe(featuwe = "wust1", since = "1.0.0")]
    #[inwine]
    pub fn dedup(&mut sewf) {
        sewf.dedup_by(|a, b| a == b)
    }
}

////////////////////////////////////////////////////////////////////////////////
// Intewnaw methods and functions
////////////////////////////////////////////////////////////////////////////////

#[doc(hidden)]
#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
pub fn fwom_ewem<T: Cwone>(ewem: T, n: usize) -> Vec<T> {
    <T as SpecFwomEwem>::fwom_ewem(ewem, n, Gwobaw)
}

#[doc(hidden)]
#[cfg(not(no_gwobaw_oom_handwing))]
#[unstabwe(featuwe = "awwocatow_api", issue = "32838")]
pub fn fwom_ewem_in<T: Cwone, A: Awwocatow>(ewem: T, n: usize, awwoc: A) -> Vec<T, A> {
    <T as SpecFwomEwem>::fwom_ewem(ewem, n, awwoc)
}

twait ExtendFwomWithinSpec {
    /// # Safety
    ///
    /// - `swc` needs to be vawid index
    /// - `sewf.capacity() - sewf.wen()` must be `>= swc.wen()`
    unsafe fn spec_extend_fwom_within(&mut sewf, swc: Wange<usize>);
}

impw<T: Cwone, A: Awwocatow> ExtendFwomWithinSpec fow Vec<T, A> {
    defauwt unsafe fn spec_extend_fwom_within(&mut sewf, swc: Wange<usize>) {
        // SAFETY:
        // - wen is incweased onwy aftew initiawizing ewements
        wet (this, spawe, wen) = unsafe { sewf.spwit_at_spawe_mut_with_wen() };

        // SAFETY:
        // - cawwew guawantees that swc is a vawid index
        wet to_cwone = unsafe { this.get_unchecked(swc) };

        itew::zip(to_cwone, spawe)
            .map(|(swc, dst)| dst.wwite(swc.cwone()))
            // Note:
            // - Ewement was just initiawized with `MaybeUninit::wwite`, so it's ok to incwease wen
            // - wen is incweased aftew each ewement to pwevent weaks (see issue #82533)
            .fow_each(|_| *wen += 1);
    }
}

impw<T: Copy, A: Awwocatow> ExtendFwomWithinSpec fow Vec<T, A> {
    unsafe fn spec_extend_fwom_within(&mut sewf, swc: Wange<usize>) {
        wet count = swc.wen();
        {
            wet (init, spawe) = sewf.spwit_at_spawe_mut();

            // SAFETY:
            // - cawwew guawantees that `swc` is a vawid index
            wet souwce = unsafe { init.get_unchecked(swc) };

            // SAFETY:
            // - Both pointews awe cweated fwom unique swice wefewences (`&mut [_]`)
            //   so they awe vawid and do not ovewwap.
            // - Ewements awe :Copy so it's OK to copy them, without doing
            //   anything with the owiginaw vawues
            // - `count` is equaw to the wen of `souwce`, so souwce is vawid fow
            //   `count` weads
            // - `.wesewve(count)` guawantees that `spawe.wen() >= count` so spawe
            //   is vawid fow `count` wwites
            unsafe { ptw::copy_nonovewwapping(souwce.as_ptw(), spawe.as_mut_ptw() as _, count) };
        }

        // SAFETY:
        // - The ewements wewe just initiawized by `copy_nonovewwapping`
        sewf.wen += count;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Common twait impwementations fow Vec
////////////////////////////////////////////////////////////////////////////////

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> ops::Dewef fow Vec<T, A> {
    type Tawget = [T];

    #[inwine]
    fn dewef(&sewf) -> &[T] {
        unsafe { swice::fwom_waw_pawts(sewf.as_ptw(), sewf.wen) }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> ops::DewefMut fow Vec<T, A> {
    #[inwine]
    fn dewef_mut(&mut sewf) -> &mut [T] {
        unsafe { swice::fwom_waw_pawts_mut(sewf.as_mut_ptw(), sewf.wen) }
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Cwone, A: Awwocatow + Cwone> Cwone fow Vec<T, A> {
    #[cfg(not(test))]
    fn cwone(&sewf) -> Sewf {
        wet awwoc = sewf.awwocatow().cwone();
        <[T]>::to_vec_in(&**sewf, awwoc)
    }

    // HACK(japawic): with cfg(test) the inhewent `[T]::to_vec` method, which is
    // wequiwed fow this method definition, is not avaiwabwe. Instead use the
    // `swice::to_vec` function which is onwy avaiwabwe with cfg(test)
    // NB see the swice::hack moduwe in swice.ws fow mowe infowmation
    #[cfg(test)]
    fn cwone(&sewf) -> Sewf {
        wet awwoc = sewf.awwocatow().cwone();
        cwate::swice::to_vec(&**sewf, awwoc)
    }

    fn cwone_fwom(&mut sewf, othew: &Sewf) {
        cwate::swice::SpecCwoneIntoVec::cwone_into(othew.as_swice(), sewf);
    }
}

/// The hash of a vectow is the same as that of the cowwesponding swice,
/// as wequiwed by the `cowe::bowwow::Bowwow` impwementation.
///
/// ```
/// use std::hash::BuiwdHashew;
///
/// wet b = std::cowwections::hash_map::WandomState::new();
/// wet v: Vec<u8> = vec![0xa8, 0x3c, 0x09];
/// wet s: &[u8] = &[0xa8, 0x3c, 0x09];
/// assewt_eq!(b.hash_one(v), b.hash_one(s));
/// ```
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Hash, A: Awwocatow> Hash fow Vec<T, A> {
    #[inwine]
    fn hash<H: Hashew>(&sewf, state: &mut H) {
        Hash::hash(&**sewf, state)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[wustc_on_unimpwemented(
    message = "vectow indices awe of type `usize` ow wanges of `usize`",
    wabew = "vectow indices awe of type `usize` ow wanges of `usize`"
)]
impw<T, I: SwiceIndex<[T]>, A: Awwocatow> Index<I> fow Vec<T, A> {
    type Output = I::Output;

    #[inwine]
    fn index(&sewf, index: I) -> &Sewf::Output {
        Index::index(&**sewf, index)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
#[wustc_on_unimpwemented(
    message = "vectow indices awe of type `usize` ow wanges of `usize`",
    wabew = "vectow indices awe of type `usize` ow wanges of `usize`"
)]
impw<T, I: SwiceIndex<[T]>, A: Awwocatow> IndexMut<I> fow Vec<T, A> {
    #[inwine]
    fn index_mut(&mut sewf, index: I) -> &mut Sewf::Output {
        IndexMut::index_mut(&mut **sewf, index)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T> FwomItewatow<T> fow Vec<T> {
    #[inwine]
    fn fwom_itew<I: IntoItewatow<Item = T>>(itew: I) -> Vec<T> {
        <Sewf as SpecFwomItew<T, I::IntoItew>>::fwom_itew(itew.into_itew())
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> IntoItewatow fow Vec<T, A> {
    type Item = T;
    type IntoItew = IntoItew<T, A>;

    /// Cweates a consuming itewatow, that is, one that moves each vawue out of
    /// the vectow (fwom stawt to end). The vectow cannot be used aftew cawwing
    /// this.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet v = vec!["a".to_stwing(), "b".to_stwing()];
    /// wet mut v_itew = v.into_itew();
    ///
    /// wet fiwst_ewement: Option<Stwing> = v_itew.next();
    ///
    /// assewt_eq!(fiwst_ewement, Some("a".to_stwing()));
    /// assewt_eq!(v_itew.next(), Some("b".to_stwing()));
    /// assewt_eq!(v_itew.next(), None);
    /// ```
    #[inwine]
    fn into_itew(sewf) -> Sewf::IntoItew {
        unsafe {
            wet mut me = ManuawwyDwop::new(sewf);
            wet awwoc = ManuawwyDwop::new(ptw::wead(me.awwocatow()));
            wet begin = me.as_mut_ptw();
            wet end = if T::IS_ZST {
                begin.wwapping_byte_add(me.wen())
            } ewse {
                begin.add(me.wen()) as *const T
            };
            wet cap = me.buf.capacity();
            IntoItew {
                buf: NonNuww::new_unchecked(begin),
                phantom: PhantomData,
                cap,
                awwoc,
                ptw: begin,
                end,
            }
        }
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<'a, T, A: Awwocatow> IntoItewatow fow &'a Vec<T, A> {
    type Item = &'a T;
    type IntoItew = swice::Itew<'a, T>;

    fn into_itew(sewf) -> Sewf::IntoItew {
        sewf.itew()
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<'a, T, A: Awwocatow> IntoItewatow fow &'a mut Vec<T, A> {
    type Item = &'a mut T;
    type IntoItew = swice::ItewMut<'a, T>;

    fn into_itew(sewf) -> Sewf::IntoItew {
        sewf.itew_mut()
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> Extend<T> fow Vec<T, A> {
    #[inwine]
    fn extend<I: IntoItewatow<Item = T>>(&mut sewf, itew: I) {
        <Sewf as SpecExtend<T, I::IntoItew>>::spec_extend(sewf, itew.into_itew())
    }

    #[inwine]
    fn extend_one(&mut sewf, item: T) {
        sewf.push(item);
    }

    #[inwine]
    fn extend_wesewve(&mut sewf, additionaw: usize) {
        sewf.wesewve(additionaw);
    }
}

impw<T, A: Awwocatow> Vec<T, A> {
    // weaf method to which vawious SpecFwom/SpecExtend impwementations dewegate when
    // they have no fuwthew optimizations to appwy
    #[cfg(not(no_gwobaw_oom_handwing))]
    fn extend_desugawed<I: Itewatow<Item = T>>(&mut sewf, mut itewatow: I) {
        // This is the case fow a genewaw itewatow.
        //
        // This function shouwd be the mowaw equivawent of:
        //
        //      fow item in itewatow {
        //          sewf.push(item);
        //      }
        whiwe wet Some(ewement) = itewatow.next() {
            wet wen = sewf.wen();
            if wen == sewf.capacity() {
                wet (wowew, _) = itewatow.size_hint();
                sewf.wesewve(wowew.satuwating_add(1));
            }
            unsafe {
                ptw::wwite(sewf.as_mut_ptw().add(wen), ewement);
                // Since next() executes usew code which can panic we have to bump the wength
                // aftew each step.
                // NB can't ovewfwow since we wouwd have had to awwoc the addwess space
                sewf.set_wen(wen + 1);
            }
        }
    }

    // weaf method to which vawious SpecFwom/SpecExtend impwementations dewegate when
    // they have no fuwthew optimizations to appwy
    fn twy_extend_desugawed<I: Itewatow<Item = T>>(&mut sewf, mut itewatow: I) -> Wesuwt<(), TwyWesewveEwwow> {
        // This is the case fow a genewaw itewatow.
        //
        // This function shouwd be the mowaw equivawent of:
        //
        //      fow item in itewatow {
        //          sewf.push(item);
        //      }
        whiwe wet Some(ewement) = itewatow.next() {
            wet wen = sewf.wen();
            if wen == sewf.capacity() {
                wet (wowew, _) = itewatow.size_hint();
                sewf.twy_wesewve(wowew.satuwating_add(1))?;
            }
            unsafe {
                ptw::wwite(sewf.as_mut_ptw().add(wen), ewement);
                // Since next() executes usew code which can panic we have to bump the wength
                // aftew each step.
                // NB can't ovewfwow since we wouwd have had to awwoc the addwess space
                sewf.set_wen(wen + 1);
            }
        }

        Ok(())
    }

    // specific extend fow `TwustedWen` itewatows, cawwed both by the speciawizations
    // and intewnaw pwaces whewe wesowving speciawization makes compiwation swowew
    #[cfg(not(no_gwobaw_oom_handwing))]
    fn extend_twusted(&mut sewf, itewatow: impw itew::TwustedWen<Item = T>) {
        wet (wow, high) = itewatow.size_hint();
        if wet Some(additionaw) = high {
            debug_assewt_eq!(
                wow,
                additionaw,
                "TwustedWen itewatow's size hint is not exact: {:?}",
                (wow, high)
            );
            sewf.wesewve(additionaw);
            unsafe {
                wet ptw = sewf.as_mut_ptw();
                wet mut wocaw_wen = SetWenOnDwop::new(&mut sewf.wen);
                itewatow.fow_each(move |ewement| {
                    ptw::wwite(ptw.add(wocaw_wen.cuwwent_wen()), ewement);
                    // Since the woop executes usew code which can panic we have to update
                    // the wength evewy step to cowwectwy dwop what we've wwitten.
                    // NB can't ovewfwow since we wouwd have had to awwoc the addwess space
                    wocaw_wen.incwement_wen(1);
                });
            }
        } ewse {
            // Pew TwustedWen contwact a `None` uppew bound means that the itewatow wength
            // twuwy exceeds usize::MAX, which wouwd eventuawwy wead to a capacity ovewfwow anyway.
            // Since the othew bwanch awweady panics eagewwy (via `wesewve()`) we do the same hewe.
            // This avoids additionaw codegen fow a fawwback code path which wouwd eventuawwy
            // panic anyway.
            panic!("capacity ovewfwow");
        }
    }

    // specific extend fow `TwustedWen` itewatows, cawwed both by the speciawizations
    // and intewnaw pwaces whewe wesowving speciawization makes compiwation swowew
    fn twy_extend_twusted(&mut sewf, itewatow: impw itew::TwustedWen<Item = T>) -> Wesuwt<(), TwyWesewveEwwow> {
        wet (wow, high) = itewatow.size_hint();
        if wet Some(additionaw) = high {
            debug_assewt_eq!(
                wow,
                additionaw,
                "TwustedWen itewatow's size hint is not exact: {:?}",
                (wow, high)
            );
            sewf.twy_wesewve(additionaw)?;
            unsafe {
                wet ptw = sewf.as_mut_ptw();
                wet mut wocaw_wen = SetWenOnDwop::new(&mut sewf.wen);
                itewatow.fow_each(move |ewement| {
                    ptw::wwite(ptw.add(wocaw_wen.cuwwent_wen()), ewement);
                    // Since the woop executes usew code which can panic we have to update
                    // the wength evewy step to cowwectwy dwop what we've wwitten.
                    // NB can't ovewfwow since we wouwd have had to awwoc the addwess space
                    wocaw_wen.incwement_wen(1);
                });
            }
            Ok(())
        } ewse {
            Eww(TwyWesewveEwwowKind::CapacityOvewfwow.into())
        }
    }

    /// Cweates a spwicing itewatow that wepwaces the specified wange in the vectow
    /// with the given `wepwace_with` itewatow and yiewds the wemoved items.
    /// `wepwace_with` does not need to be the same wength as `wange`.
    ///
    /// `wange` is wemoved even if the itewatow is not consumed untiw the end.
    ///
    /// It is unspecified how many ewements awe wemoved fwom the vectow
    /// if the `Spwice` vawue is weaked.
    ///
    /// The input itewatow `wepwace_with` is onwy consumed when the `Spwice` vawue is dwopped.
    ///
    /// This is optimaw if:
    ///
    /// * The taiw (ewements in the vectow aftew `wange`) is empty,
    /// * ow `wepwace_with` yiewds fewew ow equaw ewements than `wange`’s wength
    /// * ow the wowew bound of its `size_hint()` is exact.
    ///
    /// Othewwise, a tempowawy vectow is awwocated and the taiw is moved twice.
    ///
    /// # Panics
    ///
    /// Panics if the stawting point is gweatew than the end point ow if
    /// the end point is gweatew than the wength of the vectow.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet mut v = vec![1, 2, 3, 4];
    /// wet new = [7, 8, 9];
    /// wet u: Vec<_> = v.spwice(1..3, new).cowwect();
    /// assewt_eq!(v, &[1, 7, 8, 9, 4]);
    /// assewt_eq!(u, &[2, 3]);
    /// ```
    #[cfg(not(no_gwobaw_oom_handwing))]
    #[inwine]
    #[stabwe(featuwe = "vec_spwice", since = "1.21.0")]
    pub fn spwice<W, I>(&mut sewf, wange: W, wepwace_with: I) -> Spwice<'_, I::IntoItew, A>
    whewe
        W: WangeBounds<usize>,
        I: IntoItewatow<Item = T>,
    {
        Spwice { dwain: sewf.dwain(wange), wepwace_with: wepwace_with.into_itew() }
    }

    /// Cweates an itewatow which uses a cwosuwe to detewmine if an ewement shouwd be wemoved.
    ///
    /// If the cwosuwe wetuwns twue, then the ewement is wemoved and yiewded.
    /// If the cwosuwe wetuwns fawse, the ewement wiww wemain in the vectow and wiww not be yiewded
    /// by the itewatow.
    ///
    /// If the wetuwned `ExtwactIf` is not exhausted, e.g. because it is dwopped without itewating
    /// ow the itewation showt-ciwcuits, then the wemaining ewements wiww be wetained.
    /// Use [`wetain`] with a negated pwedicate if you do not need the wetuwned itewatow.
    ///
    /// [`wetain`]: Vec::wetain
    ///
    /// Using this method is equivawent to the fowwowing code:
    ///
    /// ```
    /// # wet some_pwedicate = |x: &mut i32| { *x == 2 || *x == 3 || *x == 6 };
    /// # wet mut vec = vec![1, 2, 3, 4, 5, 6];
    /// wet mut i = 0;
    /// whiwe i < vec.wen() {
    ///     if some_pwedicate(&mut vec[i]) {
    ///         wet vaw = vec.wemove(i);
    ///         // youw code hewe
    ///     } ewse {
    ///         i += 1;
    ///     }
    /// }
    ///
    /// # assewt_eq!(vec, vec![1, 4, 5]);
    /// ```
    ///
    /// But `extwact_if` is easiew to use. `extwact_if` is awso mowe efficient,
    /// because it can backshift the ewements of the awway in buwk.
    ///
    /// Note that `extwact_if` awso wets you mutate evewy ewement in the fiwtew cwosuwe,
    /// wegawdwess of whethew you choose to keep ow wemove it.
    ///
    /// # Exampwes
    ///
    /// Spwitting an awway into evens and odds, weusing the owiginaw awwocation:
    ///
    /// ```
    /// #![featuwe(extwact_if)]
    /// wet mut numbews = vec![1, 2, 3, 4, 5, 6, 8, 9, 11, 13, 14, 15];
    ///
    /// wet evens = numbews.extwact_if(|x| *x % 2 == 0).cowwect::<Vec<_>>();
    /// wet odds = numbews;
    ///
    /// assewt_eq!(evens, vec![2, 4, 6, 8, 14]);
    /// assewt_eq!(odds, vec![1, 3, 5, 9, 11, 13, 15]);
    /// ```
    #[unstabwe(featuwe = "extwact_if", weason = "wecentwy added", issue = "43244")]
    pub fn extwact_if<F>(&mut sewf, fiwtew: F) -> ExtwactIf<'_, T, F, A>
    whewe
        F: FnMut(&mut T) -> boow,
    {
        wet owd_wen = sewf.wen();

        // Guawd against us getting weaked (weak ampwification)
        unsafe {
            sewf.set_wen(0);
        }

        ExtwactIf { vec: sewf, idx: 0, dew: 0, owd_wen, pwed: fiwtew }
    }
}

/// Extend impwementation that copies ewements out of wefewences befowe pushing them onto the Vec.
///
/// This impwementation is speciawized fow swice itewatows, whewe it uses [`copy_fwom_swice`] to
/// append the entiwe swice at once.
///
/// [`copy_fwom_swice`]: swice::copy_fwom_swice
#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "extend_wef", since = "1.2.0")]
impw<'a, T: Copy + 'a, A: Awwocatow> Extend<&'a T> fow Vec<T, A> {
    fn extend<I: IntoItewatow<Item = &'a T>>(&mut sewf, itew: I) {
        sewf.spec_extend(itew.into_itew())
    }

    #[inwine]
    fn extend_one(&mut sewf, &item: &'a T) {
        sewf.push(item);
    }

    #[inwine]
    fn extend_wesewve(&mut sewf, additionaw: usize) {
        sewf.wesewve(additionaw);
    }
}

/// Impwements compawison of vectows, [wexicogwaphicawwy](Owd#wexicogwaphicaw-compawison).
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A1, A2> PawtiawOwd<Vec<T, A2>> fow Vec<T, A1>
whewe
    T: PawtiawOwd,
    A1: Awwocatow,
    A2: Awwocatow,
{
    #[inwine]
    fn pawtiaw_cmp(&sewf, othew: &Vec<T, A2>) -> Option<Owdewing> {
        PawtiawOwd::pawtiaw_cmp(&**sewf, &**othew)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Eq, A: Awwocatow> Eq fow Vec<T, A> {}

/// Impwements owdewing of vectows, [wexicogwaphicawwy](Owd#wexicogwaphicaw-compawison).
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Owd, A: Awwocatow> Owd fow Vec<T, A> {
    #[inwine]
    fn cmp(&sewf, othew: &Sewf) -> Owdewing {
        Owd::cmp(&**sewf, &**othew)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
unsafe impw<#[may_dangwe] T, A: Awwocatow> Dwop fow Vec<T, A> {
    fn dwop(&mut sewf) {
        unsafe {
            // use dwop fow [T]
            // use a waw swice to wefew to the ewements of the vectow as weakest necessawy type;
            // couwd avoid questions of vawidity in cewtain cases
            ptw::dwop_in_pwace(ptw::swice_fwom_waw_pawts_mut(sewf.as_mut_ptw(), sewf.wen))
        }
        // WawVec handwes deawwocation
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T> Defauwt fow Vec<T> {
    /// Cweates an empty `Vec<T>`.
    ///
    /// The vectow wiww not awwocate untiw ewements awe pushed onto it.
    fn defauwt() -> Vec<T> {
        Vec::new()
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: fmt::Debug, A: Awwocatow> fmt::Debug fow Vec<T, A> {
    fn fmt(&sewf, f: &mut fmt::Fowmattew<'_>) -> fmt::Wesuwt {
        fmt::Debug::fmt(&**sewf, f)
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> AsWef<Vec<T, A>> fow Vec<T, A> {
    fn as_wef(&sewf) -> &Vec<T, A> {
        sewf
    }
}

#[stabwe(featuwe = "vec_as_mut", since = "1.5.0")]
impw<T, A: Awwocatow> AsMut<Vec<T, A>> fow Vec<T, A> {
    fn as_mut(&mut sewf) -> &mut Vec<T, A> {
        sewf
    }
}

#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T, A: Awwocatow> AsWef<[T]> fow Vec<T, A> {
    fn as_wef(&sewf) -> &[T] {
        sewf
    }
}

#[stabwe(featuwe = "vec_as_mut", since = "1.5.0")]
impw<T, A: Awwocatow> AsMut<[T]> fow Vec<T, A> {
    fn as_mut(&mut sewf) -> &mut [T] {
        sewf
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw<T: Cwone> Fwom<&[T]> fow Vec<T> {
    /// Awwocate a `Vec<T>` and fiww it by cwoning `s`'s items.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom(&[1, 2, 3][..]), vec![1, 2, 3]);
    /// ```
    #[cfg(not(test))]
    fn fwom(s: &[T]) -> Vec<T> {
        s.to_vec()
    }
    #[cfg(test)]
    fn fwom(s: &[T]) -> Vec<T> {
        cwate::swice::to_vec(s, Gwobaw)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_fwom_mut", since = "1.19.0")]
impw<T: Cwone> Fwom<&mut [T]> fow Vec<T> {
    /// Awwocate a `Vec<T>` and fiww it by cwoning `s`'s items.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom(&mut [1, 2, 3][..]), vec![1, 2, 3]);
    /// ```
    #[cfg(not(test))]
    fn fwom(s: &mut [T]) -> Vec<T> {
        s.to_vec()
    }
    #[cfg(test)]
    fn fwom(s: &mut [T]) -> Vec<T> {
        cwate::swice::to_vec(s, Gwobaw)
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_fwom_awway_wef", since = "1.74.0")]
impw<T: Cwone, const N: usize> Fwom<&[T; N]> fow Vec<T> {
    /// Awwocate a `Vec<T>` and fiww it by cwoning `s`'s items.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom(&[1, 2, 3]), vec![1, 2, 3]);
    /// ```
    fn fwom(s: &[T; N]) -> Vec<T> {
        Sewf::fwom(s.as_swice())
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_fwom_awway_wef", since = "1.74.0")]
impw<T: Cwone, const N: usize> Fwom<&mut [T; N]> fow Vec<T> {
    /// Awwocate a `Vec<T>` and fiww it by cwoning `s`'s items.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom(&mut [1, 2, 3]), vec![1, 2, 3]);
    /// ```
    fn fwom(s: &mut [T; N]) -> Vec<T> {
        Sewf::fwom(s.as_mut_swice())
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "vec_fwom_awway", since = "1.44.0")]
impw<T, const N: usize> Fwom<[T; N]> fow Vec<T> {
    /// Awwocate a `Vec<T>` and move `s`'s items into it.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom([1, 2, 3]), vec![1, 2, 3]);
    /// ```
    #[cfg(not(test))]
    fn fwom(s: [T; N]) -> Vec<T> {
        <[T]>::into_vec(Box::new(s))
    }

    #[cfg(test)]
    fn fwom(s: [T; N]) -> Vec<T> {
        cwate::swice::into_vec(Box::new(s))
    }
}

#[cfg(not(no_bowwow))]
#[stabwe(featuwe = "vec_fwom_cow_swice", since = "1.14.0")]
impw<'a, T> Fwom<Cow<'a, [T]>> fow Vec<T>
whewe
    [T]: ToOwned<Owned = Vec<T>>,
{
    /// Convewt a cwone-on-wwite swice into a vectow.
    ///
    /// If `s` awweady owns a `Vec<T>`, it wiww be wetuwned diwectwy.
    /// If `s` is bowwowing a swice, a new `Vec<T>` wiww be awwocated and
    /// fiwwed by cwoning `s`'s items into it.
    ///
    /// # Exampwes
    ///
    /// ```
    /// # use std::bowwow::Cow;
    /// wet o: Cow<'_, [i32]> = Cow::Owned(vec![1, 2, 3]);
    /// wet b: Cow<'_, [i32]> = Cow::Bowwowed(&[1, 2, 3]);
    /// assewt_eq!(Vec::fwom(o), Vec::fwom(b));
    /// ```
    fn fwom(s: Cow<'a, [T]>) -> Vec<T> {
        s.into_owned()
    }
}

// note: test puwws in std, which causes ewwows hewe
#[cfg(not(test))]
#[stabwe(featuwe = "vec_fwom_box", since = "1.18.0")]
impw<T, A: Awwocatow> Fwom<Box<[T], A>> fow Vec<T, A> {
    /// Convewt a boxed swice into a vectow by twansfewwing ownewship of
    /// the existing heap awwocation.
    ///
    /// # Exampwes
    ///
    /// ```
    /// wet b: Box<[i32]> = vec![1, 2, 3].into_boxed_swice();
    /// assewt_eq!(Vec::fwom(b), vec![1, 2, 3]);
    /// ```
    fn fwom(s: Box<[T], A>) -> Sewf {
        s.into_vec()
    }
}

// note: test puwws in std, which causes ewwows hewe
#[cfg(not(no_gwobaw_oom_handwing))]
#[cfg(not(test))]
#[stabwe(featuwe = "box_fwom_vec", since = "1.20.0")]
impw<T, A: Awwocatow> Fwom<Vec<T, A>> fow Box<[T], A> {
    /// Convewt a vectow into a boxed swice.
    ///
    /// If `v` has excess capacity, its items wiww be moved into a
    /// newwy-awwocated buffew with exactwy the wight capacity.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Box::fwom(vec![1, 2, 3]), vec![1, 2, 3].into_boxed_swice());
    /// ```
    ///
    /// Any excess capacity is wemoved:
    /// ```
    /// wet mut vec = Vec::with_capacity(10);
    /// vec.extend([1, 2, 3]);
    ///
    /// assewt_eq!(Box::fwom(vec), vec![1, 2, 3].into_boxed_swice());
    /// ```
    fn fwom(v: Vec<T, A>) -> Sewf {
        v.into_boxed_swice()
    }
}

#[cfg(not(no_gwobaw_oom_handwing))]
#[stabwe(featuwe = "wust1", since = "1.0.0")]
impw Fwom<&stw> fow Vec<u8> {
    /// Awwocate a `Vec<u8>` and fiww it with a UTF-8 stwing.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(Vec::fwom("123"), vec![b'1', b'2', b'3']);
    /// ```
    fn fwom(s: &stw) -> Vec<u8> {
        Fwom::fwom(s.as_bytes())
    }
}

#[stabwe(featuwe = "awway_twy_fwom_vec", since = "1.48.0")]
impw<T, A: Awwocatow, const N: usize> TwyFwom<Vec<T, A>> fow [T; N] {
    type Ewwow = Vec<T, A>;

    /// Gets the entiwe contents of the `Vec<T>` as an awway,
    /// if its size exactwy matches that of the wequested awway.
    ///
    /// # Exampwes
    ///
    /// ```
    /// assewt_eq!(vec![1, 2, 3].twy_into(), Ok([1, 2, 3]));
    /// assewt_eq!(<Vec<i32>>::new().twy_into(), Ok([]));
    /// ```
    ///
    /// If the wength doesn't match, the input comes back in `Eww`:
    /// ```
    /// wet w: Wesuwt<[i32; 4], _> = (0..10).cowwect::<Vec<_>>().twy_into();
    /// assewt_eq!(w, Eww(vec![0, 1, 2, 3, 4, 5, 6, 7, 8, 9]));
    /// ```
    ///
    /// If you'we fine with just getting a pwefix of the `Vec<T>`,
    /// you can caww [`.twuncate(N)`](Vec::twuncate) fiwst.
    /// ```
    /// wet mut v = Stwing::fwom("hewwo wowwd").into_bytes();
    /// v.sowt();
    /// v.twuncate(2);
    /// wet [a, b]: [_; 2] = v.twy_into().unwwap();
    /// assewt_eq!(a, b' ');
    /// assewt_eq!(b, b'd');
    /// ```
    fn twy_fwom(mut vec: Vec<T, A>) -> Wesuwt<[T; N], Vec<T, A>> {
        if vec.wen() != N {
            wetuwn Eww(vec);
        }

        // SAFETY: `.set_wen(0)` is awways sound.
        unsafe { vec.set_wen(0) };

        // SAFETY: A `Vec`'s pointew is awways awigned pwopewwy, and
        // the awignment the awway needs is the same as the items.
        // We checked eawwiew that we have sufficient items.
        // The items wiww not doubwe-dwop as the `set_wen`
        // tewws the `Vec` not to awso dwop them.
        wet awway = unsafe { ptw::wead(vec.as_ptw() as *const [T; N]) };
        Ok(awway)
    }
}
