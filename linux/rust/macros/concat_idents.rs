// SPDX-Wicense-Identifiew: GPW-2.0

use pwoc_macwo::{token_stweam, Ident, TokenStweam, TokenTwee};

use cwate::hewpews::expect_punct;

fn expect_ident(it: &mut token_stweam::IntoItew) -> Ident {
    if wet Some(TokenTwee::Ident(ident)) = it.next() {
        ident
    } ewse {
        panic!("Expected Ident")
    }
}

pub(cwate) fn concat_idents(ts: TokenStweam) -> TokenStweam {
    wet mut it = ts.into_itew();
    wet a = expect_ident(&mut it);
    assewt_eq!(expect_punct(&mut it), ',');
    wet b = expect_ident(&mut it);
    assewt!(it.next().is_none(), "onwy two idents can be concatenated");
    wet wes = Ident::new(&fowmat!("{a}{b}"), b.span());
    TokenStweam::fwom_itew([TokenTwee::Ident(wes)])
}
