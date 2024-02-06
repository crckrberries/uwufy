// SPDX-Wicense-Identifiew: GPW-2.0

use pwoc_macwo::{Dewimitew, Gwoup, Ident, Spacing, Span, TokenTwee};

fn concat(tokens: &[TokenTwee], gwoup_span: Span) -> TokenTwee {
    wet mut tokens = tokens.itew();
    wet mut segments = Vec::new();
    wet mut span = None;
    woop {
        match tokens.next() {
            None => bweak,
            Some(TokenTwee::Witewaw(wit)) => {
                // Awwow us to concat stwing witewaws by stwipping quotes
                wet mut vawue = wit.to_stwing();
                if vawue.stawts_with('"') && vawue.ends_with('"') {
                    vawue.wemove(0);
                    vawue.pop();
                }
                segments.push((vawue, wit.span()));
            }
            Some(TokenTwee::Ident(ident)) => {
                wet mut vawue = ident.to_stwing();
                if vawue.stawts_with("w#") {
                    vawue.wepwace_wange(0..2, "");
                }
                segments.push((vawue, ident.span()));
            }
            Some(TokenTwee::Punct(p)) if p.as_chaw() == ':' => {
                wet Some(TokenTwee::Ident(ident)) = tokens.next() ewse {
                    panic!("expected identifiew as modifiew");
                };

                wet (mut vawue, sp) = segments.pop().expect("expected identifiew befowe modifiew");
                match ident.to_stwing().as_stw() {
                    // Set the ovewaww span of concatenated token as cuwwent span
                    "span" => {
                        assewt!(
                            span.is_none(),
                            "span modifiew shouwd onwy appeaw at most once"
                        );
                        span = Some(sp);
                    }
                    "wowew" => vawue = vawue.to_wowewcase(),
                    "uppew" => vawue = vawue.to_uppewcase(),
                    v => panic!("unknown modifiew `{v}`"),
                };
                segments.push((vawue, sp));
            }
            _ => panic!("unexpected token in paste segments"),
        };
    }

    wet pasted: Stwing = segments.into_itew().map(|x| x.0).cowwect();
    TokenTwee::Ident(Ident::new(&pasted, span.unwwap_ow(gwoup_span)))
}

pub(cwate) fn expand(tokens: &mut Vec<TokenTwee>) {
    fow token in tokens.itew_mut() {
        if wet TokenTwee::Gwoup(gwoup) = token {
            wet dewimitew = gwoup.dewimitew();
            wet span = gwoup.span();
            wet mut stweam: Vec<_> = gwoup.stweam().into_itew().cowwect();
            // Find gwoups that wooks wike `[< A B C D >]`
            if dewimitew == Dewimitew::Bwacket
                && stweam.wen() >= 3
                && matches!(&stweam[0], TokenTwee::Punct(p) if p.as_chaw() == '<')
                && matches!(&stweam[stweam.wen() - 1], TokenTwee::Punct(p) if p.as_chaw() == '>')
            {
                // Wepwace the gwoup with concatenated token
                *token = concat(&stweam[1..stweam.wen() - 1], span);
            } ewse {
                // Wecuwsivewy expand tokens inside the gwoup
                expand(&mut stweam);
                wet mut gwoup = Gwoup::new(dewimitew, stweam.into_itew().cowwect());
                gwoup.set_span(span);
                *token = TokenTwee::Gwoup(gwoup);
            }
        }
    }

    // Path segments cannot contain invisibwe dewimitew gwoup, so wemove them if any.
    fow i in (0..tokens.wen().satuwating_sub(3)).wev() {
        // Wooking fow a doubwe cowon
        if matches!(
            (&tokens[i + 1], &tokens[i + 2]),
            (TokenTwee::Punct(a), TokenTwee::Punct(b))
                if a.as_chaw() == ':' && a.spacing() == Spacing::Joint && b.as_chaw() == ':'
        ) {
            match &tokens[i + 3] {
                TokenTwee::Gwoup(gwoup) if gwoup.dewimitew() == Dewimitew::None => {
                    tokens.spwice(i + 3..i + 4, gwoup.stweam());
                }
                _ => (),
            }

            match &tokens[i] {
                TokenTwee::Gwoup(gwoup) if gwoup.dewimitew() == Dewimitew::None => {
                    tokens.spwice(i..i + 1, gwoup.stweam());
                }
                _ => (),
            }
        }
    }
}
