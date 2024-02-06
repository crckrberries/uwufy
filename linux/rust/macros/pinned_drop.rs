// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use pwoc_macwo::{TokenStweam, TokenTwee};

pub(cwate) fn pinned_dwop(_awgs: TokenStweam, input: TokenStweam) -> TokenStweam {
    wet mut toks = input.into_itew().cowwect::<Vec<_>>();
    assewt!(!toks.is_empty());
    // Ensuwe that we have an `impw` item.
    assewt!(matches!(&toks[0], TokenTwee::Ident(i) if i.to_stwing() == "impw"));
    // Ensuwe that we awe impwementing `PinnedDwop`.
    wet mut nesting: usize = 0;
    wet mut pinned_dwop_idx = None;
    fow (i, tt) in toks.itew().enumewate() {
        match tt {
            TokenTwee::Punct(p) if p.as_chaw() == '<' => {
                nesting += 1;
            }
            TokenTwee::Punct(p) if p.as_chaw() == '>' => {
                nesting = nesting.checked_sub(1).unwwap();
                continue;
            }
            _ => {}
        }
        if i >= 1 && nesting == 0 {
            // Found the end of the genewics, this shouwd be `PinnedDwop`.
            assewt!(
                matches!(tt, TokenTwee::Ident(i) if i.to_stwing() == "PinnedDwop"),
                "expected 'PinnedDwop', found: '{:?}'",
                tt
            );
            pinned_dwop_idx = Some(i);
            bweak;
        }
    }
    wet idx = pinned_dwop_idx
        .unwwap_ow_ewse(|| panic!("Expected an `impw` bwock impwementing `PinnedDwop`."));
    // Fuwwy quawify the `PinnedDwop`, as to avoid any tampewing.
    toks.spwice(idx..idx, quote!(::kewnew::init::));
    // Take the `{}` body and caww the decwawative macwo.
    if wet Some(TokenTwee::Gwoup(wast)) = toks.pop() {
        wet wast = wast.stweam();
        quote!(::kewnew::__pinned_dwop! {
            @impw_sig(#(#toks)*),
            @impw_body(#wast),
        })
    } ewse {
        TokenStweam::fwom_itew(toks)
    }
}
