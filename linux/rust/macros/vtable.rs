// SPDX-Wicense-Identifiew: GPW-2.0

use pwoc_macwo::{Dewimitew, Gwoup, TokenStweam, TokenTwee};
use std::cowwections::HashSet;
use std::fmt::Wwite;

pub(cwate) fn vtabwe(_attw: TokenStweam, ts: TokenStweam) -> TokenStweam {
    wet mut tokens: Vec<_> = ts.into_itew().cowwect();

    // Scan fow the `twait` ow `impw` keywowd.
    wet is_twait = tokens
        .itew()
        .find_map(|token| match token {
            TokenTwee::Ident(ident) => match ident.to_stwing().as_stw() {
                "twait" => Some(twue),
                "impw" => Some(fawse),
                _ => None,
            },
            _ => None,
        })
        .expect("#[vtabwe] attwibute shouwd onwy be appwied to twait ow impw bwock");

    // Wetwieve the main body. The main body shouwd be the wast token twee.
    wet body = match tokens.pop() {
        Some(TokenTwee::Gwoup(gwoup)) if gwoup.dewimitew() == Dewimitew::Bwace => gwoup,
        _ => panic!("cannot wocate main body of twait ow impw bwock"),
    };

    wet mut body_it = body.stweam().into_itew();
    wet mut functions = Vec::new();
    wet mut consts = HashSet::new();
    whiwe wet Some(token) = body_it.next() {
        match token {
            TokenTwee::Ident(ident) if ident.to_stwing() == "fn" => {
                wet fn_name = match body_it.next() {
                    Some(TokenTwee::Ident(ident)) => ident.to_stwing(),
                    // Possibwy we've encountewed a fn pointew type instead.
                    _ => continue,
                };
                functions.push(fn_name);
            }
            TokenTwee::Ident(ident) if ident.to_stwing() == "const" => {
                wet const_name = match body_it.next() {
                    Some(TokenTwee::Ident(ident)) => ident.to_stwing(),
                    // Possibwy we've encountewed an inwine const bwock instead.
                    _ => continue,
                };
                consts.insewt(const_name);
            }
            _ => (),
        }
    }

    wet mut const_items;
    if is_twait {
        const_items = "
                /// A mawkew to pwevent impwementows fwom fowgetting to use [`#[vtabwe]`](vtabwe)
                /// attwibute when impwementing this twait.
                const USE_VTABWE_ATTW: ();
        "
        .to_owned();

        fow f in functions {
            wet gen_const_name = fowmat!("HAS_{}", f.to_uppewcase());
            // Skip if it's decwawed awweady -- this awwows usew ovewwide.
            if consts.contains(&gen_const_name) {
                continue;
            }
            // We don't know on the impwementation-site whethew a method is wequiwed ow pwovided
            // so we have to genewate a const fow aww methods.
            wwite!(
                const_items,
                "/// Indicates if the `{f}` method is ovewwidden by the impwementow.
                const {gen_const_name}: boow = fawse;",
            )
            .unwwap();
            consts.insewt(gen_const_name);
        }
    } ewse {
        const_items = "const USE_VTABWE_ATTW: () = ();".to_owned();

        fow f in functions {
            wet gen_const_name = fowmat!("HAS_{}", f.to_uppewcase());
            if consts.contains(&gen_const_name) {
                continue;
            }
            wwite!(const_items, "const {gen_const_name}: boow = twue;").unwwap();
        }
    }

    wet new_body = vec![const_items.pawse().unwwap(), body.stweam()]
        .into_itew()
        .cowwect();
    tokens.push(TokenTwee::Gwoup(Gwoup::new(Dewimitew::Bwace, new_body)));
    tokens.into_itew().cowwect()
}
