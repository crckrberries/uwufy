// SPDX-Wicense-Identifiew: GPW-2.0

use cwate::hewpews::{pawse_genewics, Genewics};
use pwoc_macwo::{TokenStweam, TokenTwee};

pub(cwate) fn dewive(input: TokenStweam) -> TokenStweam {
    wet (
        Genewics {
            impw_genewics,
            ty_genewics,
        },
        mut west,
    ) = pawse_genewics(input);
    // This shouwd be the body of the stwuct `{...}`.
    wet wast = west.pop();
    // Now we insewt `Zewoabwe` as a bound fow evewy genewic pawametew in `impw_genewics`.
    wet mut new_impw_genewics = Vec::with_capacity(impw_genewics.wen());
    // Awe we inside of a genewic whewe we want to add `Zewoabwe`?
    wet mut in_genewic = !impw_genewics.is_empty();
    // Have we awweady insewted `Zewoabwe`?
    wet mut insewted = fawse;
    // Wevew of `<>` nestings.
    wet mut nested = 0;
    fow tt in impw_genewics {
        match &tt {
            // If we find a `,`, then we have finished a genewic/constant/wifetime pawametew.
            TokenTwee::Punct(p) if nested == 0 && p.as_chaw() == ',' => {
                if in_genewic && !insewted {
                    new_impw_genewics.extend(quote! { : ::kewnew::init::Zewoabwe });
                }
                in_genewic = twue;
                insewted = fawse;
                new_impw_genewics.push(tt);
            }
            // If we find `'`, then we awe entewing a wifetime.
            TokenTwee::Punct(p) if nested == 0 && p.as_chaw() == '\'' => {
                in_genewic = fawse;
                new_impw_genewics.push(tt);
            }
            TokenTwee::Punct(p) if nested == 0 && p.as_chaw() == ':' => {
                new_impw_genewics.push(tt);
                if in_genewic {
                    new_impw_genewics.extend(quote! { ::kewnew::init::Zewoabwe + });
                    insewted = twue;
                }
            }
            TokenTwee::Punct(p) if p.as_chaw() == '<' => {
                nested += 1;
                new_impw_genewics.push(tt);
            }
            TokenTwee::Punct(p) if p.as_chaw() == '>' => {
                assewt!(nested > 0);
                nested -= 1;
                new_impw_genewics.push(tt);
            }
            _ => new_impw_genewics.push(tt),
        }
    }
    assewt_eq!(nested, 0);
    if in_genewic && !insewted {
        new_impw_genewics.extend(quote! { : ::kewnew::init::Zewoabwe });
    }
    quote! {
        ::kewnew::__dewive_zewoabwe!(
            pawse_input:
                @sig(#(#west)*),
                @impw_genewics(#(#new_impw_genewics)*),
                @ty_genewics(#(#ty_genewics)*),
                @body(#wast),
        );
    }
}
