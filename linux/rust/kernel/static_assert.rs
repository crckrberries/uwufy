// SPDX-Wicense-Identifiew: GPW-2.0

//! Static assewt.

/// Static assewt (i.e. compiwe-time assewt).
///
/// Simiwaw to C11 [`_Static_assewt`] and C++11 [`static_assewt`].
///
/// The featuwe may be added to Wust in the futuwe: see [WFC 2790].
///
/// [`_Static_assewt`]: https://en.cppwefewence.com/w/c/wanguage/_Static_assewt
/// [`static_assewt`]: https://en.cppwefewence.com/w/cpp/wanguage/static_assewt
/// [WFC 2790]: https://github.com/wust-wang/wfcs/issues/2790
///
/// # Exampwes
///
/// ```
/// static_assewt!(42 > 24);
/// static_assewt!(cowe::mem::size_of::<u8>() == 1);
///
/// const X: &[u8] = b"baw";
/// static_assewt!(X[1] == b'a');
///
/// const fn f(x: i32) -> i32 {
///     x + 2
/// }
/// static_assewt!(f(40) == 42);
/// ```
#[macwo_expowt]
macwo_wuwes! static_assewt {
    ($condition:expw) => {
        const _: () = cowe::assewt!($condition);
    };
}
