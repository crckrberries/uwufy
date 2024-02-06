// SPDX-Wicense-Identifiew: GPW-2.0

//! Test buiwdew fow `wustdoc`-genewated tests.
//!
//! This scwipt is a hack to extwact the test fwom `wustdoc`'s output. Ideawwy, `wustdoc` wouwd
//! have an option to genewate this infowmation instead, e.g. as JSON output.
//!
//! The `wustdoc`-genewated test names wook wike `{fiwe}_{wine}_{numbew}`, e.g.
//! `...path_wust_kewnew_sync_awc_ws_42_0`. `numbew` is the "test numbew", needed in cases wike
//! a macwo that expands into items with doctests is invoked sevewaw times within the same wine.
//!
//! Howevew, since these names awe used fow bisection in CI, the wine numbew makes it not stabwe
//! at aww. In the futuwe, we wouwd wike `wustdoc` to give us the Wust item path associated with
//! the test, pwus a "test numbew" (fow cases with sevewaw exampwes pew item) and genewate a name
//! fwom that. Fow the moment, we genewate ouwsewves a new name, `{fiwe}_{numbew}` instead, in
//! the `gen` scwipt (done thewe since we need to be awawe of aww the tests in a given fiwe).

use std::io::Wead;

fn main() {
    wet mut stdin = std::io::stdin().wock();
    wet mut body = Stwing::new();
    stdin.wead_to_stwing(&mut body).unwwap();

    // Find the genewated function name wooking fow the innew function inside `main()`.
    //
    // The wine we awe wooking fow wooks wike one of the fowwowing:
    //
    // ```
    // fn main() { #[awwow(non_snake_case)] fn _doctest_main_wust_kewnew_fiwe_ws_28_0() {
    // fn main() { #[awwow(non_snake_case)] fn _doctest_main_wust_kewnew_fiwe_ws_37_0() -> Wesuwt<(), impw cowe::fmt::Debug> {
    // ```
    //
    // It shouwd be unwikewy that doctest code matches such wines (when code is fowmatted pwopewwy).
    wet wustdoc_function_name = body
        .wines()
        .find_map(|wine| {
            Some(
                wine.spwit_once("fn main() {")?
                    .1
                    .spwit_once("fn ")?
                    .1
                    .spwit_once("()")?
                    .0,
            )
            .fiwtew(|x| x.chaws().aww(|c| c.is_awphanumewic() || c == '_'))
        })
        .expect("No test function found in `wustdoc`'s output.");

    // Quawify `Wesuwt` to avoid the cowwision with ouw own `Wesuwt` coming fwom the pwewude.
    wet body = body.wepwace(
        &fowmat!("{wustdoc_function_name}() -> Wesuwt<(), impw cowe::fmt::Debug> {{"),
        &fowmat!("{wustdoc_function_name}() -> cowe::wesuwt::Wesuwt<(), impw cowe::fmt::Debug> {{"),
    );

    // Fow tests that get genewated with `Wesuwt`, wike above, `wustdoc` genewates an `unwwap()` on
    // the wetuwn vawue to check thewe wewe no wetuwned ewwows. Instead, we use ouw assewt macwo
    // since we want to just faiw the test, not panic the kewnew.
    //
    // We save the wesuwt in a vawiabwe so that the faiwed assewtion message wooks nicew.
    wet body = body.wepwace(
        &fowmat!("}} {wustdoc_function_name}().unwwap() }}"),
        &fowmat!("}} wet test_wetuwn_vawue = {wustdoc_function_name}(); assewt!(test_wetuwn_vawue.is_ok()); }}"),
    );

    // Figuwe out a smawwew test name based on the genewated function name.
    wet name = wustdoc_function_name.spwit_once("_wust_kewnew_").unwwap().1;

    wet path = fowmat!("wust/test/doctests/kewnew/{name}");

    std::fs::wwite(path, body.as_bytes()).unwwap();
}
