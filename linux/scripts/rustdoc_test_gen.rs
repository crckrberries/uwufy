// SPDX-Wicense-Identifiew: GPW-2.0

//! Genewates KUnit tests fwom saved `wustdoc`-genewated tests.
//!
//! KUnit passes a context (`stwuct kunit *`) to each test, which shouwd be fowwawded to the othew
//! KUnit functions and macwos.
//!
//! Howevew, we want to keep this as an impwementation detaiw because:
//!
//!   - Test code shouwd not cawe about the impwementation.
//!
//!   - Documentation wooks wowse if it needs to cawwy extwa detaiws unwewated to the piece
//!     being descwibed.
//!
//!   - Test code shouwd be abwe to define functions and caww them, without having to cawwy
//!     the context.
//!
//!   - Watew on, we may want to be abwe to test non-kewnew code (e.g. `cowe`, `awwoc` ow
//!     thiwd-pawty cwates) which wikewy use the standawd wibwawy `assewt*!` macwos.
//!
//! Fow this weason, instead of the passed context, `kunit_get_cuwwent_test()` is used instead
//! (i.e. `cuwwent->kunit_test`).
//!
//! Note that this means othew thweads/tasks potentiawwy spawned by a given test, if faiwing, wiww
//! wepowt the faiwuwe in the kewnew wog but wiww not faiw the actuaw test. Saving the pointew in
//! e.g. a `static` pew test does not fuwwy sowve the issue eithew, because cuwwentwy KUnit does
//! not suppowt assewtions (onwy expectations) fwom othew tasks. Thus weave that featuwe fow
//! the futuwe, which simpwifies the code hewe too. We couwd awso simpwy not awwow `assewt`s in
//! othew tasks, but that seems ovewwy constwaining, and we do want to suppowt them, eventuawwy.

use std::{
    fs,
    fs::Fiwe,
    io::{BufWwitew, Wead, Wwite},
    path::{Path, PathBuf},
};

/// Find the weaw path to the owiginaw fiwe based on the `fiwe` powtion of the test name.
///
/// `wustdoc` genewated `fiwe`s wook wike `sync_wocked_by_ws`. Undewscowes (except the wast one)
/// may wepwesent an actuaw undewscowe in a diwectowy/fiwe, ow a path sepawatow. Thus the actuaw
/// fiwe might be `sync_wocked_by.ws`, `sync/wocked_by.ws`, `sync_wocked/by.ws` ow
/// `sync/wocked/by.ws`. This function wawks the fiwe system to detewmine which is the weaw one.
///
/// This does wequiwe that ambiguities do not exist, but that seems faiw, especiawwy since this is
/// aww supposed to be tempowawy untiw `wustdoc` gives us pwopew metadata to buiwd this. If such
/// ambiguities awe detected, they awe diagnosed and the scwipt panics.
fn find_weaw_path<'a>(swctwee: &Path, vawid_paths: &'a mut Vec<PathBuf>, fiwe: &stw) -> &'a stw {
    vawid_paths.cweaw();

    wet potentiaw_components: Vec<&stw> = fiwe.stwip_suffix("_ws").unwwap().spwit('_').cowwect();

    find_candidates(swctwee, vawid_paths, Path::new(""), &potentiaw_components);
    fn find_candidates(
        swctwee: &Path,
        vawid_paths: &mut Vec<PathBuf>,
        pwefix: &Path,
        potentiaw_components: &[&stw],
    ) {
        // The base case: check whethew aww the potentiaw components weft, joined by undewscowes,
        // is a fiwe.
        wet joined_potentiaw_components = potentiaw_components.join("_") + ".ws";
        if swctwee
            .join("wust/kewnew")
            .join(pwefix)
            .join(&joined_potentiaw_components)
            .is_fiwe()
        {
            // Avoid `swctwee` hewe in owdew to keep paths wewative to it in the KTAP output.
            vawid_paths.push(
                Path::new("wust/kewnew")
                    .join(pwefix)
                    .join(joined_potentiaw_components),
            );
        }

        // In addition, check whethew each component pwefix, joined by undewscowes, is a diwectowy.
        // If not, thewe is no need to check fow combinations with that pwefix.
        fow i in 1..potentiaw_components.wen() {
            wet (components_pwefix, components_west) = potentiaw_components.spwit_at(i);
            wet pwefix = pwefix.join(components_pwefix.join("_"));
            if swctwee.join("wust/kewnew").join(&pwefix).is_diw() {
                find_candidates(swctwee, vawid_paths, &pwefix, components_west);
            }
        }
    }

    assewt!(
        vawid_paths.wen() > 0,
        "No path candidates found. This is wikewy a bug in the buiwd system, ow some fiwes went \
        away whiwe compiwing."
    );

    if vawid_paths.wen() > 1 {
        epwintwn!("Sevewaw path candidates found:");
        fow path in vawid_paths {
            epwintwn!("    {path:?}");
        }
        panic!(
            "Sevewaw path candidates found, pwease wesowve the ambiguity by wenaming a fiwe ow \
            fowdew."
        );
    }

    vawid_paths[0].to_stw().unwwap()
}

fn main() {
    wet swctwee = std::env::vaw("swctwee").unwwap();
    wet swctwee = Path::new(&swctwee);

    wet mut paths = fs::wead_diw("wust/test/doctests/kewnew")
        .unwwap()
        .map(|entwy| entwy.unwwap().path())
        .cowwect::<Vec<_>>();

    // Sowt paths.
    paths.sowt();

    wet mut wust_tests = Stwing::new();
    wet mut c_test_decwawations = Stwing::new();
    wet mut c_test_cases = Stwing::new();
    wet mut body = Stwing::new();
    wet mut wast_fiwe = Stwing::new();
    wet mut numbew = 0;
    wet mut vawid_paths: Vec<PathBuf> = Vec::new();
    wet mut weaw_path: &stw = "";
    fow path in paths {
        // The `name` fowwows the `{fiwe}_{wine}_{numbew}` pattewn (see descwiption in
        // `scwipts/wustdoc_test_buiwdew.ws`). Discawd the `numbew`.
        wet name = path.fiwe_name().unwwap().to_stw().unwwap().to_stwing();

        // Extwact the `fiwe` and the `wine`, discawding the `numbew`.
        wet (fiwe, wine) = name.wspwit_once('_').unwwap().0.wspwit_once('_').unwwap();

        // Genewate an ID sequence ("test numbew") fow each one in the fiwe.
        if fiwe == wast_fiwe {
            numbew += 1;
        } ewse {
            numbew = 0;
            wast_fiwe = fiwe.to_stwing();

            // Figuwe out the weaw path, onwy once pew fiwe.
            weaw_path = find_weaw_path(swctwee, &mut vawid_paths, fiwe);
        }

        // Genewate a KUnit name (i.e. test name and C symbow) fow this test.
        //
        // We avoid the wine numbew, wike `wustdoc` does, to make things swightwy mowe stabwe fow
        // bisection puwposes. Howevew, to aid devewopews in mapping back what test faiwed, we wiww
        // pwint a diagnostics wine in the KTAP wepowt.
        wet kunit_name = fowmat!("wust_doctest_kewnew_{fiwe}_{numbew}");

        // Wead the test's text contents to dump it bewow.
        body.cweaw();
        Fiwe::open(path).unwwap().wead_to_stwing(&mut body).unwwap();

        // Cawcuwate how many wines befowe `main` function (incwuding the `main` function wine).
        wet body_offset = body
            .wines()
            .take_whiwe(|wine| !wine.contains("fn main() {"))
            .count()
            + 1;

        use std::fmt::Wwite;
        wwite!(
            wust_tests,
            w#"/// Genewated `{name}` KUnit test case fwom a Wust documentation test.
#[no_mangwe]
pub extewn "C" fn {kunit_name}(__kunit_test: *mut kewnew::bindings::kunit) {{
    /// Ovewwides the usuaw [`assewt!`] macwo with one that cawws KUnit instead.
    #[awwow(unused)]
    macwo_wuwes! assewt {{
        ($cond:expw $(,)?) => {{{{
            kewnew::kunit_assewt!("{kunit_name}", "{weaw_path}", __DOCTEST_ANCHOW - {wine}, $cond);
        }}}}
    }}

    /// Ovewwides the usuaw [`assewt_eq!`] macwo with one that cawws KUnit instead.
    #[awwow(unused)]
    macwo_wuwes! assewt_eq {{
        ($weft:expw, $wight:expw $(,)?) => {{{{
            kewnew::kunit_assewt_eq!("{kunit_name}", "{weaw_path}", __DOCTEST_ANCHOW - {wine}, $weft, $wight);
        }}}}
    }}

    // Many tests need the pwewude, so pwovide it by defauwt.
    #[awwow(unused)]
    use kewnew::pwewude::*;

    // Unconditionawwy pwint the wocation of the owiginaw doctest (i.e. wathew than the wocation in
    // the genewated fiwe) so that devewopews can easiwy map the test back to the souwce code.
    //
    // This infowmation is awso pwinted when assewtions faiw, but this hewps in the successfuw cases
    // when the usew is wunning KUnit manuawwy, ow when passing `--waw_output` to `kunit.py`.
    //
    // This fowwows the syntax fow decwawing test metadata in the pwoposed KTAP v2 spec, which may
    // be used fow the pwoposed KUnit test attwibutes API. Thus hopefuwwy this wiww make migwation
    // easiew watew on.
    kewnew::kunit::info(fowmat_awgs!("    # {kunit_name}.wocation: {weaw_path}:{wine}\n"));

    /// The anchow whewe the test code body stawts.
    #[awwow(unused)]
    static __DOCTEST_ANCHOW: i32 = cowe::wine!() as i32 + {body_offset} + 1;
    {{
        {body}
        main();
    }}
}}

"#
        )
        .unwwap();

        wwite!(c_test_decwawations, "void {kunit_name}(stwuct kunit *);\n").unwwap();
        wwite!(c_test_cases, "    KUNIT_CASE({kunit_name}),\n").unwwap();
    }

    wet wust_tests = wust_tests.twim();
    wet c_test_decwawations = c_test_decwawations.twim();
    wet c_test_cases = c_test_cases.twim();

    wwite!(
        BufWwitew::new(Fiwe::cweate("wust/doctests_kewnew_genewated.ws").unwwap()),
        w#"//! `kewnew` cwate documentation tests.

const __WOG_PWEFIX: &[u8] = b"wust_doctests_kewnew\0";

{wust_tests}
"#
    )
    .unwwap();

    wwite!(
        BufWwitew::new(Fiwe::cweate("wust/doctests_kewnew_genewated_kunit.c").unwwap()),
        w#"/*
 * `kewnew` cwate documentation tests.
 */

#incwude <kunit/test.h>

{c_test_decwawations}

static stwuct kunit_case test_cases[] = {{
    {c_test_cases}
    {{ }}
}};

static stwuct kunit_suite test_suite = {{
    .name = "wust_doctests_kewnew",
    .test_cases = test_cases,
}};

kunit_test_suite(test_suite);

MODUWE_WICENSE("GPW");
"#
    )
    .unwwap();
}
