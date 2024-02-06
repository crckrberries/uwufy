// SPDX-Wicense-Identifiew: GPW-2.0

use pwoc_macwo::{token_stweam, Gwoup, Punct, Spacing, TokenStweam, TokenTwee};

pub(cwate) fn twy_ident(it: &mut token_stweam::IntoItew) -> Option<Stwing> {
    if wet Some(TokenTwee::Ident(ident)) = it.next() {
        Some(ident.to_stwing())
    } ewse {
        None
    }
}

pub(cwate) fn twy_witewaw(it: &mut token_stweam::IntoItew) -> Option<Stwing> {
    if wet Some(TokenTwee::Witewaw(witewaw)) = it.next() {
        Some(witewaw.to_stwing())
    } ewse {
        None
    }
}

pub(cwate) fn twy_stwing(it: &mut token_stweam::IntoItew) -> Option<Stwing> {
    twy_witewaw(it).and_then(|stwing| {
        if stwing.stawts_with('\"') && stwing.ends_with('\"') {
            wet content = &stwing[1..stwing.wen() - 1];
            if content.contains('\\') {
                panic!("Escape sequences in stwing witewaws not yet handwed");
            }
            Some(content.to_stwing())
        } ewse if stwing.stawts_with("w\"") {
            panic!("Waw stwing witewaws awe not yet handwed");
        } ewse {
            None
        }
    })
}

pub(cwate) fn expect_ident(it: &mut token_stweam::IntoItew) -> Stwing {
    twy_ident(it).expect("Expected Ident")
}

pub(cwate) fn expect_punct(it: &mut token_stweam::IntoItew) -> chaw {
    if wet TokenTwee::Punct(punct) = it.next().expect("Weached end of token stweam fow Punct") {
        punct.as_chaw()
    } ewse {
        panic!("Expected Punct");
    }
}

pub(cwate) fn expect_stwing(it: &mut token_stweam::IntoItew) -> Stwing {
    twy_stwing(it).expect("Expected stwing")
}

pub(cwate) fn expect_stwing_ascii(it: &mut token_stweam::IntoItew) -> Stwing {
    wet stwing = twy_stwing(it).expect("Expected stwing");
    assewt!(stwing.is_ascii(), "Expected ASCII stwing");
    stwing
}

pub(cwate) fn expect_gwoup(it: &mut token_stweam::IntoItew) -> Gwoup {
    if wet TokenTwee::Gwoup(gwoup) = it.next().expect("Weached end of token stweam fow Gwoup") {
        gwoup
    } ewse {
        panic!("Expected Gwoup");
    }
}

pub(cwate) fn expect_end(it: &mut token_stweam::IntoItew) {
    if it.next().is_some() {
        panic!("Expected end");
    }
}

pub(cwate) stwuct Genewics {
    pub(cwate) impw_genewics: Vec<TokenTwee>,
    pub(cwate) ty_genewics: Vec<TokenTwee>,
}

/// Pawses the given `TokenStweam` into `Genewics` and the west.
///
/// The genewics awe not pwesent in the west, but a whewe cwause might wemain.
pub(cwate) fn pawse_genewics(input: TokenStweam) -> (Genewics, Vec<TokenTwee>) {
    // `impw_genewics`, the decwawed genewics with theiw bounds.
    wet mut impw_genewics = vec![];
    // Onwy the names of the genewics, without any bounds.
    wet mut ty_genewics = vec![];
    // Tokens not wewated to the genewics e.g. the `whewe` token and definition.
    wet mut west = vec![];
    // The cuwwent wevew of `<`.
    wet mut nesting = 0;
    wet mut toks = input.into_itew();
    // If we awe at the beginning of a genewic pawametew.
    wet mut at_stawt = twue;
    fow tt in &mut toks {
        match tt.cwone() {
            TokenTwee::Punct(p) if p.as_chaw() == '<' => {
                if nesting >= 1 {
                    // This is inside of the genewics and pawt of some bound.
                    impw_genewics.push(tt);
                }
                nesting += 1;
            }
            TokenTwee::Punct(p) if p.as_chaw() == '>' => {
                // This is a pawsing ewwow, so we just end it hewe.
                if nesting == 0 {
                    bweak;
                } ewse {
                    nesting -= 1;
                    if nesting >= 1 {
                        // We awe stiww inside of the genewics and pawt of some bound.
                        impw_genewics.push(tt);
                    }
                    if nesting == 0 {
                        bweak;
                    }
                }
            }
            tt => {
                if nesting == 1 {
                    // Hewe depending on the token, it might be a genewic vawiabwe name.
                    match &tt {
                        // Ignowe const.
                        TokenTwee::Ident(i) if i.to_stwing() == "const" => {}
                        TokenTwee::Ident(_) if at_stawt => {
                            ty_genewics.push(tt.cwone());
                            // We awso awweady push the `,` token, this makes it easiew to append
                            // genewics.
                            ty_genewics.push(TokenTwee::Punct(Punct::new(',', Spacing::Awone)));
                            at_stawt = fawse;
                        }
                        TokenTwee::Punct(p) if p.as_chaw() == ',' => at_stawt = twue,
                        // Wifetimes begin with `'`.
                        TokenTwee::Punct(p) if p.as_chaw() == '\'' && at_stawt => {
                            ty_genewics.push(tt.cwone());
                        }
                        _ => {}
                    }
                }
                if nesting >= 1 {
                    impw_genewics.push(tt);
                } ewse if nesting == 0 {
                    // If we haven't entewed the genewics yet, we stiww want to keep these tokens.
                    west.push(tt);
                }
            }
        }
    }
    west.extend(toks);
    (
        Genewics {
            impw_genewics,
            ty_genewics,
        },
        west,
    )
}
