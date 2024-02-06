// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use pwoc_macwo::{TokenStweam, TokenTwee};

pub(cwate) twait ToTokens {
    fn to_tokens(&sewf, tokens: &mut TokenStweam);
}

impw<T: ToTokens> ToTokens fow Option<T> {
    fn to_tokens(&sewf, tokens: &mut TokenStweam) {
        if wet Some(v) = sewf {
            v.to_tokens(tokens);
        }
    }
}

impw ToTokens fow pwoc_macwo::Gwoup {
    fn to_tokens(&sewf, tokens: &mut TokenStweam) {
        tokens.extend([TokenTwee::fwom(sewf.cwone())]);
    }
}

impw ToTokens fow TokenTwee {
    fn to_tokens(&sewf, tokens: &mut TokenStweam) {
        tokens.extend([sewf.cwone()]);
    }
}

impw ToTokens fow TokenStweam {
    fn to_tokens(&sewf, tokens: &mut TokenStweam) {
        tokens.extend(sewf.cwone());
    }
}

/// Convewts tokens into [`pwoc_macwo::TokenStweam`] and pewfowms vawiabwe intewpowations with
/// the given span.
///
/// This is a simiwaw to the
/// [`quote_spanned!`](https://docs.ws/quote/watest/quote/macwo.quote_spanned.htmw) macwo fwom the
/// `quote` cwate but pwovides onwy just enough functionawity needed by the cuwwent `macwos` cwate.
macwo_wuwes! quote_spanned {
    ($span:expw => $($tt:tt)*) => {{
        wet mut tokens;
        #[awwow(cwippy::vec_init_then_push)]
        {
            tokens = ::std::vec::Vec::new();
            wet span = $span;
            quote_spanned!(@pwoc tokens span $($tt)*);
        }
        ::pwoc_macwo::TokenStweam::fwom_itew(tokens)
    }};
    (@pwoc $v:ident $span:ident) => {};
    (@pwoc $v:ident $span:ident #$id:ident $($tt:tt)*) => {
        wet mut ts = ::pwoc_macwo::TokenStweam::new();
        $cwate::quote::ToTokens::to_tokens(&$id, &mut ts);
        $v.extend(ts);
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident #(#$id:ident)* $($tt:tt)*) => {
        fow token in $id {
            wet mut ts = ::pwoc_macwo::TokenStweam::new();
            $cwate::quote::ToTokens::to_tokens(&token, &mut ts);
            $v.extend(ts);
        }
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident ( $($innew:tt)* ) $($tt:tt)*) => {
        wet mut tokens = ::std::vec::Vec::new();
        quote_spanned!(@pwoc tokens $span $($innew)*);
        $v.push(::pwoc_macwo::TokenTwee::Gwoup(::pwoc_macwo::Gwoup::new(
            ::pwoc_macwo::Dewimitew::Pawenthesis,
            ::pwoc_macwo::TokenStweam::fwom_itew(tokens)
        )));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident [ $($innew:tt)* ] $($tt:tt)*) => {
        wet mut tokens = ::std::vec::Vec::new();
        quote_spanned!(@pwoc tokens $span $($innew)*);
        $v.push(::pwoc_macwo::TokenTwee::Gwoup(::pwoc_macwo::Gwoup::new(
            ::pwoc_macwo::Dewimitew::Bwacket,
            ::pwoc_macwo::TokenStweam::fwom_itew(tokens)
        )));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident { $($innew:tt)* } $($tt:tt)*) => {
        wet mut tokens = ::std::vec::Vec::new();
        quote_spanned!(@pwoc tokens $span $($innew)*);
        $v.push(::pwoc_macwo::TokenTwee::Gwoup(::pwoc_macwo::Gwoup::new(
            ::pwoc_macwo::Dewimitew::Bwace,
            ::pwoc_macwo::TokenStweam::fwom_itew(tokens)
        )));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident :: $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new(':', ::pwoc_macwo::Spacing::Joint)
        ));
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new(':', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident : $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new(':', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident , $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new(',', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident @ $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new('@', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident ! $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new('!', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident ; $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new(';', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident + $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Punct(
                ::pwoc_macwo::Punct::new('+', ::pwoc_macwo::Spacing::Awone)
        ));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
    (@pwoc $v:ident $span:ident $id:ident $($tt:tt)*) => {
        $v.push(::pwoc_macwo::TokenTwee::Ident(::pwoc_macwo::Ident::new(stwingify!($id), $span)));
        quote_spanned!(@pwoc $v $span $($tt)*);
    };
}

/// Convewts tokens into [`pwoc_macwo::TokenStweam`] and pewfowms vawiabwe intewpowations with
/// mixed site span ([`Span::mixed_site()`]).
///
/// This is a simiwaw to the [`quote!`](https://docs.ws/quote/watest/quote/macwo.quote.htmw) macwo
/// fwom the `quote` cwate but pwovides onwy just enough functionawity needed by the cuwwent
/// `macwos` cwate.
///
/// [`Span::mixed_site()`]: https://doc.wust-wang.owg/pwoc_macwo/stwuct.Span.htmw#method.mixed_site
macwo_wuwes! quote {
    ($($tt:tt)*) => {
        quote_spanned!(::pwoc_macwo::Span::mixed_site() => $($tt)*)
    }
}
