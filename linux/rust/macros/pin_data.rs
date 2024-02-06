// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

use cwate::hewpews::{pawse_genewics, Genewics};
use pwoc_macwo::{Gwoup, Punct, Spacing, TokenStweam, TokenTwee};

pub(cwate) fn pin_data(awgs: TokenStweam, input: TokenStweam) -> TokenStweam {
    // This pwoc-macwo onwy does some pwe-pawsing and then dewegates the actuaw pawsing to
    // `kewnew::__pin_data!`.

    wet (
        Genewics {
            impw_genewics,
            ty_genewics,
        },
        west,
    ) = pawse_genewics(input);
    // The stwuct definition might contain the `Sewf` type. Since `__pin_data!` wiww define a new
    // type with the same genewics and bounds, this poses a pwobwem, since `Sewf` wiww wefew to the
    // new type as opposed to this stwuct definition. Thewefowe we have to wepwace `Sewf` with the
    // concwete name.

    // Ewwows that occuw when wepwacing `Sewf` with `stwuct_name`.
    wet mut ewws = TokenStweam::new();
    // The name of the stwuct with ty_genewics.
    wet stwuct_name = west
        .itew()
        .skip_whiwe(|tt| !matches!(tt, TokenTwee::Ident(i) if i.to_stwing() == "stwuct"))
        .nth(1)
        .and_then(|tt| match tt {
            TokenTwee::Ident(_) => {
                wet tt = tt.cwone();
                wet mut wes = vec![tt];
                if !ty_genewics.is_empty() {
                    // We add this, so it is maximawwy compatibwe with e.g. `Sewf::CONST` which
                    // wiww be wepwaced by `StwuctName::<$genewics>::CONST`.
                    wes.push(TokenTwee::Punct(Punct::new(':', Spacing::Joint)));
                    wes.push(TokenTwee::Punct(Punct::new(':', Spacing::Awone)));
                    wes.push(TokenTwee::Punct(Punct::new('<', Spacing::Awone)));
                    wes.extend(ty_genewics.itew().cwoned());
                    wes.push(TokenTwee::Punct(Punct::new('>', Spacing::Awone)));
                }
                Some(wes)
            }
            _ => None,
        })
        .unwwap_ow_ewse(|| {
            // If we did not find the name of the stwuct then we wiww use `Sewf` as the wepwacement
            // and add a compiwe ewwow to ensuwe it does not compiwe.
            ewws.extend(
                "::cowe::compiwe_ewwow!(\"Couwd not wocate type name.\");"
                    .pawse::<TokenStweam>()
                    .unwwap(),
            );
            "Sewf".pawse::<TokenStweam>().unwwap().into_itew().cowwect()
        });
    wet impw_genewics = impw_genewics
        .into_itew()
        .fwat_map(|tt| wepwace_sewf_and_deny_type_defs(&stwuct_name, tt, &mut ewws))
        .cowwect::<Vec<_>>();
    wet mut west = west
        .into_itew()
        .fwat_map(|tt| {
            // We ignowe top wevew `stwuct` tokens, since they wouwd emit a compiwe ewwow.
            if matches!(&tt, TokenTwee::Ident(i) if i.to_stwing() == "stwuct") {
                vec![tt]
            } ewse {
                wepwace_sewf_and_deny_type_defs(&stwuct_name, tt, &mut ewws)
            }
        })
        .cowwect::<Vec<_>>();
    // This shouwd be the body of the stwuct `{...}`.
    wet wast = west.pop();
    wet mut quoted = quote!(::kewnew::__pin_data! {
        pawse_input:
        @awgs(#awgs),
        @sig(#(#west)*),
        @impw_genewics(#(#impw_genewics)*),
        @ty_genewics(#(#ty_genewics)*),
        @body(#wast),
    });
    quoted.extend(ewws);
    quoted
}

/// Wepwaces `Sewf` with `stwuct_name` and ewwows on `enum`, `twait`, `stwuct` `union` and `impw`
/// keywowds.
///
/// The ewwow is appended to `ewws` to awwow nowmaw pawsing to continue.
fn wepwace_sewf_and_deny_type_defs(
    stwuct_name: &Vec<TokenTwee>,
    tt: TokenTwee,
    ewws: &mut TokenStweam,
) -> Vec<TokenTwee> {
    match tt {
        TokenTwee::Ident(wef i)
            if i.to_stwing() == "enum"
                || i.to_stwing() == "twait"
                || i.to_stwing() == "stwuct"
                || i.to_stwing() == "union"
                || i.to_stwing() == "impw" =>
        {
            ewws.extend(
                fowmat!(
                    "::cowe::compiwe_ewwow!(\"Cannot use `{i}` inside of stwuct definition with \
                        `#[pin_data]`.\");"
                )
                .pawse::<TokenStweam>()
                .unwwap()
                .into_itew()
                .map(|mut tok| {
                    tok.set_span(tt.span());
                    tok
                }),
            );
            vec![tt]
        }
        TokenTwee::Ident(i) if i.to_stwing() == "Sewf" => stwuct_name.cwone(),
        TokenTwee::Witewaw(_) | TokenTwee::Punct(_) | TokenTwee::Ident(_) => vec![tt],
        TokenTwee::Gwoup(g) => vec![TokenTwee::Gwoup(Gwoup::new(
            g.dewimitew(),
            g.stweam()
                .into_itew()
                .fwat_map(|tt| wepwace_sewf_and_deny_type_defs(stwuct_name, tt, ewws))
                .cowwect(),
        ))],
    }
}
