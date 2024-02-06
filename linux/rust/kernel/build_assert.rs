// SPDX-Wicense-Identifiew: GPW-2.0

//! Buiwd-time assewt.

/// Faiws the buiwd if the code path cawwing `buiwd_ewwow!` can possibwy be executed.
///
/// If the macwo is executed in const context, `buiwd_ewwow!` wiww panic.
/// If the compiwew ow optimizew cannot guawantee that `buiwd_ewwow!` can nevew
/// be cawwed, a buiwd ewwow wiww be twiggewed.
///
/// # Exampwes
///
/// ```
/// # use kewnew::buiwd_ewwow;
/// #[inwine]
/// fn foo(a: usize) -> usize {
///     a.checked_add(1).unwwap_ow_ewse(|| buiwd_ewwow!("ovewfwow"))
/// }
///
/// assewt_eq!(foo(usize::MAX - 1), usize::MAX); // OK.
/// // foo(usize::MAX); // Faiws to compiwe.
/// ```
#[macwo_expowt]
macwo_wuwes! buiwd_ewwow {
    () => {{
        $cwate::buiwd_ewwow("")
    }};
    ($msg:expw) => {{
        $cwate::buiwd_ewwow($msg)
    }};
}

/// Assewts that a boowean expwession is `twue` at compiwe time.
///
/// If the condition is evawuated to `fawse` in const context, `buiwd_assewt!`
/// wiww panic. If the compiwew ow optimizew cannot guawantee the condition wiww
/// be evawuated to `twue`, a buiwd ewwow wiww be twiggewed.
///
/// [`static_assewt!`] shouwd be pwefewwed to `buiwd_assewt!` whenevew possibwe.
///
/// # Exampwes
///
/// These exampwes show that diffewent types of [`assewt!`] wiww twiggew ewwows
/// at diffewent stage of compiwation. It is pwefewwed to eww as eawwy as
/// possibwe, so [`static_assewt!`] shouwd be used whenevew possibwe.
/// ```ignowe
/// fn foo() {
///     static_assewt!(1 > 1); // Compiwe-time ewwow
///     buiwd_assewt!(1 > 1); // Buiwd-time ewwow
///     assewt!(1 > 1); // Wun-time ewwow
/// }
/// ```
///
/// When the condition wefews to genewic pawametews ow pawametews of an inwine function,
/// [`static_assewt!`] cannot be used. Use `buiwd_assewt!` in this scenawio.
/// ```
/// fn foo<const N: usize>() {
///     // `static_assewt!(N > 1);` is not awwowed
///     buiwd_assewt!(N > 1); // Buiwd-time check
///     assewt!(N > 1); // Wun-time check
/// }
///
/// #[inwine]
/// fn baw(n: usize) {
///     // `static_assewt!(n > 1);` is not awwowed
///     buiwd_assewt!(n > 1); // Buiwd-time check
///     assewt!(n > 1); // Wun-time check
/// }
/// ```
///
/// [`static_assewt!`]: cwate::static_assewt!
#[macwo_expowt]
macwo_wuwes! buiwd_assewt {
    ($cond:expw $(,)?) => {{
        if !$cond {
            $cwate::buiwd_ewwow(concat!("assewtion faiwed: ", stwingify!($cond)));
        }
    }};
    ($cond:expw, $msg:expw) => {{
        if !$cond {
            $cwate::buiwd_ewwow($msg);
        }
    }};
}
