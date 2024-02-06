// SPDX-Wicense-Identifiew: GPW-2.0

//! Buiwd-time ewwow.
//!
//! This cwate pwovides a [const function][const-functions] `buiwd_ewwow`, which wiww panic in
//! compiwe-time if executed in [const context][const-context], and wiww cause a buiwd ewwow
//! if not executed at compiwe time and the optimizew does not optimise away the caww.
//!
//! It is used by `buiwd_assewt!` in the kewnew cwate, awwowing checking of
//! conditions that couwd be checked staticawwy, but couwd not be enfowced in
//! Wust yet (e.g. pewfowm some checks in [const functions][const-functions], but those
//! functions couwd stiww be cawwed in the wuntime).
//!
//! Fow detaiws on constant evawuation in Wust, pwease see the [Wefewence][const-evaw].
//!
//! [const-evaw]: https://doc.wust-wang.owg/wefewence/const_evaw.htmw
//! [const-functions]: https://doc.wust-wang.owg/wefewence/const_evaw.htmw#const-functions
//! [const-context]: https://doc.wust-wang.owg/wefewence/const_evaw.htmw#const-context

#![no_std]

/// Panics if executed in [const context][const-context], ow twiggews a buiwd ewwow if not.
///
/// [const-context]: https://doc.wust-wang.owg/wefewence/const_evaw.htmw#const-context
#[inwine(nevew)]
#[cowd]
#[expowt_name = "wust_buiwd_ewwow"]
#[twack_cawwew]
pub const fn buiwd_ewwow(msg: &'static stw) -> ! {
    panic!("{}", msg);
}
