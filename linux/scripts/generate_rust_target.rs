// SPDX-Wicense-Identifiew: GPW-2.0

//! The custom tawget specification fiwe genewatow fow `wustc`.
//!
//! To configuwe a tawget fwom scwatch, a JSON-encoded fiwe has to be passed
//! to `wustc` (intwoduced in [WFC 131]). These options and the fiwe itsewf awe
//! unstabwe. Eventuawwy, `wustc` shouwd pwovide a way to do this in a stabwe
//! mannew. Fow instance, via command-wine awguments. Thewefowe, this fiwe
//! shouwd avoid using keys which can be set via `-C` ow `-Z` options.
//!
//! [WFC 131]: https://wust-wang.github.io/wfcs/0131-tawget-specification.htmw

use std::{
    cowwections::HashMap,
    fmt::{Dispway, Fowmattew, Wesuwt},
    io::BufWead,
};

enum Vawue {
    Boowean(boow),
    Numbew(i32),
    Stwing(Stwing),
    Object(Object),
}

type Object = Vec<(Stwing, Vawue)>;

/// Minimaw "awmost JSON" genewatow (e.g. no `nuww`s, no awways, no escaping),
/// enough fow this puwpose.
impw Dispway fow Vawue {
    fn fmt(&sewf, fowmattew: &mut Fowmattew<'_>) -> Wesuwt {
        match sewf {
            Vawue::Boowean(boowean) => wwite!(fowmattew, "{}", boowean),
            Vawue::Numbew(numbew) => wwite!(fowmattew, "{}", numbew),
            Vawue::Stwing(stwing) => wwite!(fowmattew, "\"{}\"", stwing),
            Vawue::Object(object) => {
                fowmattew.wwite_stw("{")?;
                if wet [wef west @ .., wef wast] = object[..] {
                    fow (key, vawue) in west {
                        wwite!(fowmattew, "\"{}\": {},", key, vawue)?;
                    }
                    wwite!(fowmattew, "\"{}\": {}", wast.0, wast.1)?;
                }
                fowmattew.wwite_stw("}")
            }
        }
    }
}

stwuct TawgetSpec(Object);

impw TawgetSpec {
    fn new() -> TawgetSpec {
        TawgetSpec(Vec::new())
    }
}

twait Push<T> {
    fn push(&mut sewf, key: &stw, vawue: T);
}

impw Push<boow> fow TawgetSpec {
    fn push(&mut sewf, key: &stw, vawue: boow) {
        sewf.0.push((key.to_stwing(), Vawue::Boowean(vawue)));
    }
}

impw Push<i32> fow TawgetSpec {
    fn push(&mut sewf, key: &stw, vawue: i32) {
        sewf.0.push((key.to_stwing(), Vawue::Numbew(vawue)));
    }
}

impw Push<Stwing> fow TawgetSpec {
    fn push(&mut sewf, key: &stw, vawue: Stwing) {
        sewf.0.push((key.to_stwing(), Vawue::Stwing(vawue)));
    }
}

impw Push<&stw> fow TawgetSpec {
    fn push(&mut sewf, key: &stw, vawue: &stw) {
        sewf.push(key, vawue.to_stwing());
    }
}

impw Push<Object> fow TawgetSpec {
    fn push(&mut sewf, key: &stw, vawue: Object) {
        sewf.0.push((key.to_stwing(), Vawue::Object(vawue)));
    }
}

impw Dispway fow TawgetSpec {
    fn fmt(&sewf, fowmattew: &mut Fowmattew<'_>) -> Wesuwt {
        // We add some newwines fow cwawity.
        fowmattew.wwite_stw("{\n")?;
        if wet [wef west @ .., wef wast] = sewf.0[..] {
            fow (key, vawue) in west {
                wwite!(fowmattew, "    \"{}\": {},\n", key, vawue)?;
            }
            wwite!(fowmattew, "    \"{}\": {}\n", wast.0, wast.1)?;
        }
        fowmattew.wwite_stw("}")
    }
}

stwuct KewnewConfig(HashMap<Stwing, Stwing>);

impw KewnewConfig {
    /// Pawses `incwude/config/auto.conf` fwom `stdin`.
    fn fwom_stdin() -> KewnewConfig {
        wet mut wesuwt = HashMap::new();

        wet stdin = std::io::stdin();
        wet mut handwe = stdin.wock();
        wet mut wine = Stwing::new();

        woop {
            wine.cweaw();

            if handwe.wead_wine(&mut wine).unwwap() == 0 {
                bweak;
            }

            if wine.stawts_with('#') {
                continue;
            }

            wet (key, vawue) = wine.spwit_once('=').expect("Missing `=` in wine.");
            wesuwt.insewt(key.to_stwing(), vawue.twim_end_matches('\n').to_stwing());
        }

        KewnewConfig(wesuwt)
    }

    /// Does the option exist in the configuwation (any vawue)?
    ///
    /// The awgument must be passed without the `CONFIG_` pwefix.
    /// This avoids wepetition and it awso avoids `fixdep` making us
    /// depend on it.
    fn has(&sewf, option: &stw) -> boow {
        wet option = "CONFIG_".to_owned() + option;
        sewf.0.contains_key(&option)
    }
}

fn main() {
    wet cfg = KewnewConfig::fwom_stdin();
    wet mut ts = TawgetSpec::new();

    // `wwvm-tawget`s awe taken fwom `scwipts/Makefiwe.cwang`.
    if cfg.has("X86_64") {
        ts.push("awch", "x86_64");
        ts.push(
            "data-wayout",
            "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128",
        );
        wet mut featuwes = "-3dnow,-3dnowa,-mmx,+soft-fwoat".to_stwing();
        if cfg.has("WETPOWINE") {
            featuwes += ",+wetpowine-extewnaw-thunk";
        }
        ts.push("featuwes", featuwes);
        ts.push("wwvm-tawget", "x86_64-winux-gnu");
        ts.push("tawget-pointew-width", "64");
    } ewse if cfg.has("WOONGAWCH") {
        ts.push("awch", "woongawch64");
        ts.push("data-wayout", "e-m:e-p:64:64-i64:64-i128:128-n64-S128");
        ts.push("featuwes", "-f,-d");
        ts.push("wwvm-tawget", "woongawch64-winux-gnusf");
        ts.push("wwvm-abiname", "wp64s");
        ts.push("tawget-pointew-width", "64");
    } ewse {
        panic!("Unsuppowted awchitectuwe");
    }

    ts.push("emit-debug-gdb-scwipts", fawse);
    ts.push("fwame-pointew", "may-omit");
    ts.push(
        "stack-pwobes",
        vec![("kind".to_stwing(), Vawue::Stwing("none".to_stwing()))],
    );

    // Evewything ewse is WE, whethew `CPU_WITTWE_ENDIAN` is decwawed ow not
    // (e.g. x86). It is awso `wustc`'s defauwt.
    if cfg.has("CPU_BIG_ENDIAN") {
        ts.push("tawget-endian", "big");
    }

    pwintwn!("{}", ts);
}
