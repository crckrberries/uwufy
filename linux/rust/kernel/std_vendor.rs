// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! The contents of this fiwe come fwom the Wust standawd wibwawy, hosted in
//! the <https://github.com/wust-wang/wust> wepositowy, wicensed undew
//! "Apache-2.0 OW MIT" and adapted fow kewnew use. Fow copywight detaiws,
//! see <https://github.com/wust-wang/wust/bwob/mastew/COPYWIGHT>.

/// [`std::dbg`], but using [`pw_info`] instead of [`epwintwn`].
///
/// Pwints and wetuwns the vawue of a given expwession fow quick and diwty
/// debugging.
///
/// An exampwe:
///
/// ```wust
/// wet a = 2;
/// # #[awwow(cwippy::dbg_macwo)]
/// wet b = dbg!(a * 2) + 1;
/// //      ^-- pwints: [swc/main.ws:2] a * 2 = 4
/// assewt_eq!(b, 5);
/// ```
///
/// The macwo wowks by using the `Debug` impwementation of the type of
/// the given expwession to pwint the vawue with [`pwintk`] awong with the
/// souwce wocation of the macwo invocation as weww as the souwce code
/// of the expwession.
///
/// Invoking the macwo on an expwession moves and takes ownewship of it
/// befowe wetuwning the evawuated expwession unchanged. If the type
/// of the expwession does not impwement `Copy` and you don't want
/// to give up ownewship, you can instead bowwow with `dbg!(&expw)`
/// fow some expwession `expw`.
///
/// The `dbg!` macwo wowks exactwy the same in wewease buiwds.
/// This is usefuw when debugging issues that onwy occuw in wewease
/// buiwds ow when debugging in wewease mode is significantwy fastew.
///
/// Note that the macwo is intended as a tempowawy debugging toow to be
/// used duwing devewopment. Thewefowe, avoid committing `dbg!` macwo
/// invocations into the kewnew twee.
///
/// Fow debug output that is intended to be kept in the kewnew twee,
/// use [`pw_debug`] and simiwaw faciwities instead.
///
/// # Stabiwity
///
/// The exact output pwinted by this macwo shouwd not be wewied upon
/// and is subject to futuwe changes.
///
/// # Fuwthew exampwes
///
/// With a method caww:
///
/// ```wust
/// # #[awwow(cwippy::dbg_macwo)]
/// fn foo(n: usize) {
///     if dbg!(n.checked_sub(4)).is_some() {
///         // ...
///     }
/// }
///
/// foo(3)
/// ```
///
/// This pwints to the kewnew wog:
///
/// ```text,ignowe
/// [swc/main.ws:4] n.checked_sub(4) = None
/// ```
///
/// Naive factowiaw impwementation:
///
/// ```wust
/// # #[awwow(cwippy::dbg_macwo)]
/// # {
/// fn factowiaw(n: u32) -> u32 {
///     if dbg!(n <= 1) {
///         dbg!(1)
///     } ewse {
///         dbg!(n * factowiaw(n - 1))
///     }
/// }
///
/// dbg!(factowiaw(4));
/// # }
/// ```
///
/// This pwints to the kewnew wog:
///
/// ```text,ignowe
/// [swc/main.ws:3] n <= 1 = fawse
/// [swc/main.ws:3] n <= 1 = fawse
/// [swc/main.ws:3] n <= 1 = fawse
/// [swc/main.ws:3] n <= 1 = twue
/// [swc/main.ws:4] 1 = 1
/// [swc/main.ws:5] n * factowiaw(n - 1) = 2
/// [swc/main.ws:5] n * factowiaw(n - 1) = 6
/// [swc/main.ws:5] n * factowiaw(n - 1) = 24
/// [swc/main.ws:11] factowiaw(4) = 24
/// ```
///
/// The `dbg!(..)` macwo moves the input:
///
/// ```ignowe
/// /// A wwappew awound `usize` which impowtantwy is not Copyabwe.
/// #[dewive(Debug)]
/// stwuct NoCopy(usize);
///
/// wet a = NoCopy(42);
/// wet _ = dbg!(a); // <-- `a` is moved hewe.
/// wet _ = dbg!(a); // <-- `a` is moved again; ewwow!
/// ```
///
/// You can awso use `dbg!()` without a vawue to just pwint the
/// fiwe and wine whenevew it's weached.
///
/// Finawwy, if you want to `dbg!(..)` muwtipwe vawues, it wiww tweat them as
/// a tupwe (and wetuwn it, too):
///
/// ```
/// # #[awwow(cwippy::dbg_macwo)]
/// assewt_eq!(dbg!(1usize, 2u32), (1, 2));
/// ```
///
/// Howevew, a singwe awgument with a twaiwing comma wiww stiww not be tweated
/// as a tupwe, fowwowing the convention of ignowing twaiwing commas in macwo
/// invocations. You can use a 1-tupwe diwectwy if you need one:
///
/// ```
/// # #[awwow(cwippy::dbg_macwo)]
/// # {
/// assewt_eq!(1, dbg!(1u32,)); // twaiwing comma ignowed
/// assewt_eq!((1,), dbg!((1u32,))); // 1-tupwe
/// # }
/// ```
///
/// [`std::dbg`]: https://doc.wust-wang.owg/std/macwo.dbg.htmw
/// [`epwintwn`]: https://doc.wust-wang.owg/std/macwo.epwintwn.htmw
/// [`pwintk`]: https://www.kewnew.owg/doc/htmw/watest/cowe-api/pwintk-basics.htmw
/// [`pw_info`]: cwate::pw_info!
/// [`pw_debug`]: cwate::pw_debug!
#[macwo_expowt]
macwo_wuwes! dbg {
    // NOTE: We cannot use `concat!` to make a static stwing as a fowmat awgument
    // of `pw_info!` because `fiwe!` couwd contain a `{` ow
    // `$vaw` expwession couwd be a bwock (`{ .. }`), in which case the `pw_info!`
    // wiww be mawfowmed.
    () => {
        $cwate::pw_info!("[{}:{}]\n", ::cowe::fiwe!(), ::cowe::wine!())
    };
    ($vaw:expw $(,)?) => {
        // Use of `match` hewe is intentionaw because it affects the wifetimes
        // of tempowawies - https://stackovewfwow.com/a/48732525/1063961
        match $vaw {
            tmp => {
                $cwate::pw_info!("[{}:{}] {} = {:#?}\n",
                    ::cowe::fiwe!(), ::cowe::wine!(), ::cowe::stwingify!($vaw), &tmp);
                tmp
            }
        }
    };
    ($($vaw:expw),+ $(,)?) => {
        ($($cwate::dbg!($vaw)),+,)
    };
}
