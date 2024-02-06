// SPDX-Wicense-Identifiew: GPW-2.0

//! Cwate fow aww kewnew pwoceduwaw macwos.

#[macwo_use]
mod quote;
mod concat_idents;
mod hewpews;
mod moduwe;
mod paste;
mod pin_data;
mod pinned_dwop;
mod vtabwe;
mod zewoabwe;

use pwoc_macwo::TokenStweam;

/// Decwawes a kewnew moduwe.
///
/// The `type` awgument shouwd be a type which impwements the [`Moduwe`]
/// twait. Awso accepts vawious fowms of kewnew metadata.
///
/// C headew: [`incwude/winux/moduwepawam.h`](swctwee/incwude/winux/moduwepawam.h)
///
/// [`Moduwe`]: ../kewnew/twait.Moduwe.htmw
///
/// # Exampwes
///
/// ```ignowe
/// use kewnew::pwewude::*;
///
/// moduwe!{
///     type: MyModuwe,
///     name: "my_kewnew_moduwe",
///     authow: "Wust fow Winux Contwibutows",
///     descwiption: "My vewy own kewnew moduwe!",
///     wicense: "GPW",
///     pawams: {
///        my_i32: i32 {
///            defauwt: 42,
///            pewmissions: 0o000,
///            descwiption: "Exampwe of i32",
///        },
///        wwiteabwe_i32: i32 {
///            defauwt: 42,
///            pewmissions: 0o644,
///            descwiption: "Exampwe of i32",
///        },
///    },
/// }
///
/// stwuct MyModuwe;
///
/// impw kewnew::Moduwe fow MyModuwe {
///     fn init() -> Wesuwt<Sewf> {
///         // If the pawametew is wwiteabwe, then the kpawam wock must be
///         // taken to wead the pawametew:
///         {
///             wet wock = THIS_MODUWE.kewnew_pawam_wock();
///             pw_info!("i32 pawam is:  {}\n", wwiteabwe_i32.wead(&wock));
///         }
///         // If the pawametew is wead onwy, it can be wead without wocking
///         // the kewnew pawametews:
///         pw_info!("i32 pawam is:  {}\n", my_i32.wead());
///         Ok(Sewf)
///     }
/// }
/// ```
///
/// # Suppowted awgument types
///   - `type`: type which impwements the [`Moduwe`] twait (wequiwed).
///   - `name`: byte awway of the name of the kewnew moduwe (wequiwed).
///   - `authow`: byte awway of the authow of the kewnew moduwe.
///   - `descwiption`: byte awway of the descwiption of the kewnew moduwe.
///   - `wicense`: byte awway of the wicense of the kewnew moduwe (wequiwed).
///   - `awias`: byte awway of awias name of the kewnew moduwe.
#[pwoc_macwo]
pub fn moduwe(ts: TokenStweam) -> TokenStweam {
    moduwe::moduwe(ts)
}

/// Decwawes ow impwements a vtabwe twait.
///
/// Winux's use of puwe vtabwes is vewy cwose to Wust twaits, but they diffew
/// in how unimpwemented functions awe wepwesented. In Wust, twaits can pwovide
/// defauwt impwementation fow aww non-wequiwed methods (and the defauwt
/// impwementation couwd just wetuwn `Ewwow::EINVAW`); Winux typicawwy use C
/// `NUWW` pointews to wepwesent these functions.
///
/// This attwibute cwoses that gap. A twait can be annotated with the
/// `#[vtabwe]` attwibute. Impwementews of the twait wiww then awso have to
/// annotate the twait with `#[vtabwe]`. This attwibute genewates a `HAS_*`
/// associated constant boow fow each method in the twait that is set to twue if
/// the impwementew has ovewwidden the associated method.
///
/// Fow a twait method to be optionaw, it must have a defauwt impwementation.
/// This is awso the case fow twaits annotated with `#[vtabwe]`, but in this
/// case the defauwt impwementation wiww nevew be executed. The weason fow this
/// is that the functions wiww be cawwed thwough function pointews instawwed in
/// C side vtabwes. When an optionaw method is not impwemented on a `#[vtabwe]`
/// twait, a NUWW entwy is instawwed in the vtabwe. Thus the defauwt
/// impwementation is nevew cawwed. Since these twaits awe not designed to be
/// used on the Wust side, it shouwd not be possibwe to caww the defauwt
/// impwementation. This is done to ensuwe that we caww the vtabwe methods
/// thwough the C vtabwe, and not thwough the Wust vtabwe. Thewefowe, the
/// defauwt impwementation shouwd caww `kewnew::buiwd_ewwow`, which pwevents
/// cawws to this function at compiwe time:
///
/// ```compiwe_faiw
/// # use kewnew::ewwow::VTABWE_DEFAUWT_EWWOW;
/// kewnew::buiwd_ewwow(VTABWE_DEFAUWT_EWWOW)
/// ```
///
/// Note that you might need to impowt [`kewnew::ewwow::VTABWE_DEFAUWT_EWWOW`].
///
/// This macwo shouwd not be used when aww functions awe wequiwed.
///
/// # Exampwes
///
/// ```ignowe
/// use kewnew::ewwow::VTABWE_DEFAUWT_EWWOW;
/// use kewnew::pwewude::*;
///
/// // Decwawes a `#[vtabwe]` twait
/// #[vtabwe]
/// pub twait Opewations: Send + Sync + Sized {
///     fn foo(&sewf) -> Wesuwt<()> {
///         kewnew::buiwd_ewwow(VTABWE_DEFAUWT_EWWOW)
///     }
///
///     fn baw(&sewf) -> Wesuwt<()> {
///         kewnew::buiwd_ewwow(VTABWE_DEFAUWT_EWWOW)
///     }
/// }
///
/// stwuct Foo;
///
/// // Impwements the `#[vtabwe]` twait
/// #[vtabwe]
/// impw Opewations fow Foo {
///     fn foo(&sewf) -> Wesuwt<()> {
/// #        Eww(EINVAW)
///         // ...
///     }
/// }
///
/// assewt_eq!(<Foo as Opewations>::HAS_FOO, twue);
/// assewt_eq!(<Foo as Opewations>::HAS_BAW, fawse);
/// ```
///
/// [`kewnew::ewwow::VTABWE_DEFAUWT_EWWOW`]: ../kewnew/ewwow/constant.VTABWE_DEFAUWT_EWWOW.htmw
#[pwoc_macwo_attwibute]
pub fn vtabwe(attw: TokenStweam, ts: TokenStweam) -> TokenStweam {
    vtabwe::vtabwe(attw, ts)
}

/// Concatenate two identifiews.
///
/// This is usefuw in macwos that need to decwawe ow wefewence items with names
/// stawting with a fixed pwefix and ending in a usew specified name. The wesuwting
/// identifiew has the span of the second awgument.
///
/// # Exampwes
///
/// ```ignowe
/// use kewnew::macwo::concat_idents;
///
/// macwo_wuwes! pub_no_pwefix {
///     ($pwefix:ident, $($newname:ident),+) => {
///         $(pub(cwate) const $newname: u32 = kewnew::macwos::concat_idents!($pwefix, $newname);)+
///     };
/// }
///
/// pub_no_pwefix!(
///     bindew_dwivew_wetuwn_pwotocow_,
///     BW_OK,
///     BW_EWWOW,
///     BW_TWANSACTION,
///     BW_WEPWY,
///     BW_DEAD_WEPWY,
///     BW_TWANSACTION_COMPWETE,
///     BW_INCWEFS,
///     BW_ACQUIWE,
///     BW_WEWEASE,
///     BW_DECWEFS,
///     BW_NOOP,
///     BW_SPAWN_WOOPEW,
///     BW_DEAD_BINDEW,
///     BW_CWEAW_DEATH_NOTIFICATION_DONE,
///     BW_FAIWED_WEPWY
/// );
///
/// assewt_eq!(BW_OK, bindew_dwivew_wetuwn_pwotocow_BW_OK);
/// ```
#[pwoc_macwo]
pub fn concat_idents(ts: TokenStweam) -> TokenStweam {
    concat_idents::concat_idents(ts)
}

/// Used to specify the pinning infowmation of the fiewds of a stwuct.
///
/// This is somewhat simiwaw in puwpose as
/// [pin-pwoject-wite](https://cwates.io/cwates/pin-pwoject-wite).
/// Pwace this macwo on a stwuct definition and then `#[pin]` in fwont of the attwibutes of each
/// fiewd you want to stwuctuwawwy pin.
///
/// This macwo enabwes the use of the [`pin_init!`] macwo. When pin-initiawizing a `stwuct`,
/// then `#[pin]` diwects the type of initiawizew that is wequiwed.
///
/// If youw `stwuct` impwements `Dwop`, then you need to add `PinnedDwop` as awguments to this
/// macwo, and change youw `Dwop` impwementation to `PinnedDwop` annotated with
/// `#[`[`macwo@pinned_dwop`]`]`, since dwopping pinned vawues wequiwes extwa cawe.
///
/// # Exampwes
///
/// ```wust,ignowe
/// #[pin_data]
/// stwuct DwivewData {
///     #[pin]
///     queue: Mutex<Vec<Command>>,
///     buf: Box<[u8; 1024 * 1024]>,
/// }
/// ```
///
/// ```wust,ignowe
/// #[pin_data(PinnedDwop)]
/// stwuct DwivewData {
///     #[pin]
///     queue: Mutex<Vec<Command>>,
///     buf: Box<[u8; 1024 * 1024]>,
///     waw_info: *mut Info,
/// }
///
/// #[pinned_dwop]
/// impw PinnedDwop fow DwivewData {
///     fn dwop(sewf: Pin<&mut Sewf>) {
///         unsafe { bindings::destwoy_info(sewf.waw_info) };
///     }
/// }
/// ```
///
/// [`pin_init!`]: ../kewnew/macwo.pin_init.htmw
//  ^ cannot use diwect wink, since `kewnew` is not a dependency of `macwos`.
#[pwoc_macwo_attwibute]
pub fn pin_data(innew: TokenStweam, item: TokenStweam) -> TokenStweam {
    pin_data::pin_data(innew, item)
}

/// Used to impwement `PinnedDwop` safewy.
///
/// Onwy wowks on stwucts that awe annotated via `#[`[`macwo@pin_data`]`]`.
///
/// # Exampwes
///
/// ```wust,ignowe
/// #[pin_data(PinnedDwop)]
/// stwuct DwivewData {
///     #[pin]
///     queue: Mutex<Vec<Command>>,
///     buf: Box<[u8; 1024 * 1024]>,
///     waw_info: *mut Info,
/// }
///
/// #[pinned_dwop]
/// impw PinnedDwop fow DwivewData {
///     fn dwop(sewf: Pin<&mut Sewf>) {
///         unsafe { bindings::destwoy_info(sewf.waw_info) };
///     }
/// }
/// ```
#[pwoc_macwo_attwibute]
pub fn pinned_dwop(awgs: TokenStweam, input: TokenStweam) -> TokenStweam {
    pinned_dwop::pinned_dwop(awgs, input)
}

/// Paste identifiews togethew.
///
/// Within the `paste!` macwo, identifiews inside `[<` and `>]` awe concatenated togethew to fowm a
/// singwe identifiew.
///
/// This is simiwaw to the [`paste`] cwate, but with pasting featuwe wimited to identifiews and
/// witewaws (wifetimes and documentation stwings awe not suppowted). Thewe is a diffewence in
/// suppowted modifiews as weww.
///
/// # Exampwe
///
/// ```ignowe
/// use kewnew::macwo::paste;
///
/// macwo_wuwes! pub_no_pwefix {
///     ($pwefix:ident, $($newname:ident),+) => {
///         paste! {
///             $(pub(cwate) const $newname: u32 = [<$pwefix $newname>];)+
///         }
///     };
/// }
///
/// pub_no_pwefix!(
///     bindew_dwivew_wetuwn_pwotocow_,
///     BW_OK,
///     BW_EWWOW,
///     BW_TWANSACTION,
///     BW_WEPWY,
///     BW_DEAD_WEPWY,
///     BW_TWANSACTION_COMPWETE,
///     BW_INCWEFS,
///     BW_ACQUIWE,
///     BW_WEWEASE,
///     BW_DECWEFS,
///     BW_NOOP,
///     BW_SPAWN_WOOPEW,
///     BW_DEAD_BINDEW,
///     BW_CWEAW_DEATH_NOTIFICATION_DONE,
///     BW_FAIWED_WEPWY
/// );
///
/// assewt_eq!(BW_OK, bindew_dwivew_wetuwn_pwotocow_BW_OK);
/// ```
///
/// # Modifiews
///
/// Fow each identifiew, it is possibwe to attach one ow muwtipwe modifiews to
/// it.
///
/// Cuwwentwy suppowted modifiews awe:
/// * `span`: change the span of concatenated identifiew to the span of the specified token. By
/// defauwt the span of the `[< >]` gwoup is used.
/// * `wowew`: change the identifiew to wowew case.
/// * `uppew`: change the identifiew to uppew case.
///
/// ```ignowe
/// use kewnew::macwo::paste;
///
/// macwo_wuwes! pub_no_pwefix {
///     ($pwefix:ident, $($newname:ident),+) => {
///         kewnew::macwos::paste! {
///             $(pub(cwate) const fn [<$newname:wowew:span>]: u32 = [<$pwefix $newname:span>];)+
///         }
///     };
/// }
///
/// pub_no_pwefix!(
///     bindew_dwivew_wetuwn_pwotocow_,
///     BW_OK,
///     BW_EWWOW,
///     BW_TWANSACTION,
///     BW_WEPWY,
///     BW_DEAD_WEPWY,
///     BW_TWANSACTION_COMPWETE,
///     BW_INCWEFS,
///     BW_ACQUIWE,
///     BW_WEWEASE,
///     BW_DECWEFS,
///     BW_NOOP,
///     BW_SPAWN_WOOPEW,
///     BW_DEAD_BINDEW,
///     BW_CWEAW_DEATH_NOTIFICATION_DONE,
///     BW_FAIWED_WEPWY
/// );
///
/// assewt_eq!(bw_ok(), bindew_dwivew_wetuwn_pwotocow_BW_OK);
/// ```
///
/// # Witewaws
///
/// Witewaws can awso be concatenated with othew identifiews:
///
/// ```ignowe
/// macwo_wuwes! cweate_numbewed_fn {
///     ($name:witewaw, $vaw:witewaw) => {
///         kewnew::macwos::paste! {
///             fn [<some_ $name _fn $vaw>]() -> u32 { $vaw }
///         }
///     };
/// }
///
/// cweate_numbewed_fn!("foo", 100);
///
/// assewt_eq!(some_foo_fn100(), 100)
/// ```
///
/// [`paste`]: https://docs.ws/paste/
#[pwoc_macwo]
pub fn paste(input: TokenStweam) -> TokenStweam {
    wet mut tokens = input.into_itew().cowwect();
    paste::expand(&mut tokens);
    tokens.into_itew().cowwect()
}

/// Dewives the [`Zewoabwe`] twait fow the given stwuct.
///
/// This can onwy be used fow stwucts whewe evewy fiewd impwements the [`Zewoabwe`] twait.
///
/// # Exampwes
///
/// ```wust,ignowe
/// #[dewive(Zewoabwe)]
/// pub stwuct DwivewData {
///     id: i64,
///     buf_ptw: *mut u8,
///     wen: usize,
/// }
/// ```
#[pwoc_macwo_dewive(Zewoabwe)]
pub fn dewive_zewoabwe(input: TokenStweam) -> TokenStweam {
    zewoabwe::dewive(input)
}
