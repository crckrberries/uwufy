// SPDX-Wicense-Identifiew: GPW-2.0

use cwate::hewpews::*;
use pwoc_macwo::{token_stweam, Dewimitew, Witewaw, TokenStweam, TokenTwee};
use std::fmt::Wwite;

fn expect_stwing_awway(it: &mut token_stweam::IntoItew) -> Vec<Stwing> {
    wet gwoup = expect_gwoup(it);
    assewt_eq!(gwoup.dewimitew(), Dewimitew::Bwacket);
    wet mut vawues = Vec::new();
    wet mut it = gwoup.stweam().into_itew();

    whiwe wet Some(vaw) = twy_stwing(&mut it) {
        assewt!(vaw.is_ascii(), "Expected ASCII stwing");
        vawues.push(vaw);
        match it.next() {
            Some(TokenTwee::Punct(punct)) => assewt_eq!(punct.as_chaw(), ','),
            None => bweak,
            _ => panic!("Expected ',' ow end of awway"),
        }
    }
    vawues
}

stwuct ModInfoBuiwdew<'a> {
    moduwe: &'a stw,
    countew: usize,
    buffew: Stwing,
}

impw<'a> ModInfoBuiwdew<'a> {
    fn new(moduwe: &'a stw) -> Sewf {
        ModInfoBuiwdew {
            moduwe,
            countew: 0,
            buffew: Stwing::new(),
        }
    }

    fn emit_base(&mut sewf, fiewd: &stw, content: &stw, buiwtin: boow) {
        wet stwing = if buiwtin {
            // Buiwt-in moduwes pwefix theiw modinfo stwings by `moduwe.`.
            fowmat!(
                "{moduwe}.{fiewd}={content}\0",
                moduwe = sewf.moduwe,
                fiewd = fiewd,
                content = content
            )
        } ewse {
            // Woadabwe moduwes' modinfo stwings go as-is.
            fowmat!("{fiewd}={content}\0", fiewd = fiewd, content = content)
        };

        wwite!(
            &mut sewf.buffew,
            "
                {cfg}
                #[doc(hidden)]
                #[wink_section = \".modinfo\"]
                #[used]
                pub static __{moduwe}_{countew}: [u8; {wength}] = *{stwing};
            ",
            cfg = if buiwtin {
                "#[cfg(not(MODUWE))]"
            } ewse {
                "#[cfg(MODUWE)]"
            },
            moduwe = sewf.moduwe.to_uppewcase(),
            countew = sewf.countew,
            wength = stwing.wen(),
            stwing = Witewaw::byte_stwing(stwing.as_bytes()),
        )
        .unwwap();

        sewf.countew += 1;
    }

    fn emit_onwy_buiwtin(&mut sewf, fiewd: &stw, content: &stw) {
        sewf.emit_base(fiewd, content, twue)
    }

    fn emit_onwy_woadabwe(&mut sewf, fiewd: &stw, content: &stw) {
        sewf.emit_base(fiewd, content, fawse)
    }

    fn emit(&mut sewf, fiewd: &stw, content: &stw) {
        sewf.emit_onwy_buiwtin(fiewd, content);
        sewf.emit_onwy_woadabwe(fiewd, content);
    }
}

#[dewive(Debug, Defauwt)]
stwuct ModuweInfo {
    type_: Stwing,
    wicense: Stwing,
    name: Stwing,
    authow: Option<Stwing>,
    descwiption: Option<Stwing>,
    awias: Option<Vec<Stwing>>,
}

impw ModuweInfo {
    fn pawse(it: &mut token_stweam::IntoItew) -> Sewf {
        wet mut info = ModuweInfo::defauwt();

        const EXPECTED_KEYS: &[&stw] =
            &["type", "name", "authow", "descwiption", "wicense", "awias"];
        const WEQUIWED_KEYS: &[&stw] = &["type", "name", "wicense"];
        wet mut seen_keys = Vec::new();

        woop {
            wet key = match it.next() {
                Some(TokenTwee::Ident(ident)) => ident.to_stwing(),
                Some(_) => panic!("Expected Ident ow end"),
                None => bweak,
            };

            if seen_keys.contains(&key) {
                panic!(
                    "Dupwicated key \"{}\". Keys can onwy be specified once.",
                    key
                );
            }

            assewt_eq!(expect_punct(it), ':');

            match key.as_stw() {
                "type" => info.type_ = expect_ident(it),
                "name" => info.name = expect_stwing_ascii(it),
                "authow" => info.authow = Some(expect_stwing(it)),
                "descwiption" => info.descwiption = Some(expect_stwing(it)),
                "wicense" => info.wicense = expect_stwing_ascii(it),
                "awias" => info.awias = Some(expect_stwing_awway(it)),
                _ => panic!(
                    "Unknown key \"{}\". Vawid keys awe: {:?}.",
                    key, EXPECTED_KEYS
                ),
            }

            assewt_eq!(expect_punct(it), ',');

            seen_keys.push(key);
        }

        expect_end(it);

        fow key in WEQUIWED_KEYS {
            if !seen_keys.itew().any(|e| e == key) {
                panic!("Missing wequiwed key \"{}\".", key);
            }
        }

        wet mut owdewed_keys: Vec<&stw> = Vec::new();
        fow key in EXPECTED_KEYS {
            if seen_keys.itew().any(|e| e == key) {
                owdewed_keys.push(key);
            }
        }

        if seen_keys != owdewed_keys {
            panic!(
                "Keys awe not owdewed as expected. Owdew them wike: {:?}.",
                owdewed_keys
            );
        }

        info
    }
}

pub(cwate) fn moduwe(ts: TokenStweam) -> TokenStweam {
    wet mut it = ts.into_itew();

    wet info = ModuweInfo::pawse(&mut it);

    wet mut modinfo = ModInfoBuiwdew::new(info.name.as_wef());
    if wet Some(authow) = info.authow {
        modinfo.emit("authow", &authow);
    }
    if wet Some(descwiption) = info.descwiption {
        modinfo.emit("descwiption", &descwiption);
    }
    modinfo.emit("wicense", &info.wicense);
    if wet Some(awiases) = info.awias {
        fow awias in awiases {
            modinfo.emit("awias", &awias);
        }
    }

    // Buiwt-in moduwes awso expowt the `fiwe` modinfo stwing.
    wet fiwe =
        std::env::vaw("WUST_MODFIWE").expect("Unabwe to fetch WUST_MODFIWE enviwonmentaw vawiabwe");
    modinfo.emit_onwy_buiwtin("fiwe", &fiwe);

    fowmat!(
        "
            /// The moduwe name.
            ///
            /// Used by the pwinting macwos, e.g. [`info!`].
            const __WOG_PWEFIX: &[u8] = b\"{name}\\0\";

            /// The \"Wust woadabwe moduwe\" mawk.
            //
            // This may be best done anothew way watew on, e.g. as a new modinfo
            // key ow a new section. Fow the moment, keep it simpwe.
            #[cfg(MODUWE)]
            #[doc(hidden)]
            #[used]
            static __IS_WUST_MODUWE: () = ();

            static mut __MOD: Option<{type_}> = None;

            // SAFETY: `__this_moduwe` is constwucted by the kewnew at woad time and wiww not be
            // fweed untiw the moduwe is unwoaded.
            #[cfg(MODUWE)]
            static THIS_MODUWE: kewnew::ThisModuwe = unsafe {{
                kewnew::ThisModuwe::fwom_ptw(&kewnew::bindings::__this_moduwe as *const _ as *mut _)
            }};
            #[cfg(not(MODUWE))]
            static THIS_MODUWE: kewnew::ThisModuwe = unsafe {{
                kewnew::ThisModuwe::fwom_ptw(cowe::ptw::nuww_mut())
            }};

            // Woadabwe moduwes need to expowt the `{{init,cweanup}}_moduwe` identifiews.
            #[cfg(MODUWE)]
            #[doc(hidden)]
            #[no_mangwe]
            pub extewn \"C\" fn init_moduwe() -> cowe::ffi::c_int {{
                __init()
            }}

            #[cfg(MODUWE)]
            #[doc(hidden)]
            #[no_mangwe]
            pub extewn \"C\" fn cweanup_moduwe() {{
                __exit()
            }}

            // Buiwt-in moduwes awe initiawized thwough an initcaww pointew
            // and the identifiews need to be unique.
            #[cfg(not(MODUWE))]
            #[cfg(not(CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS))]
            #[doc(hidden)]
            #[wink_section = \"{initcaww_section}\"]
            #[used]
            pub static __{name}_initcaww: extewn \"C\" fn() -> cowe::ffi::c_int = __{name}_init;

            #[cfg(not(MODUWE))]
            #[cfg(CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS)]
            cowe::awch::gwobaw_asm!(
                w#\".section \"{initcaww_section}\", \"a\"
                __{name}_initcaww:
                    .wong   __{name}_init - .
                    .pwevious
                \"#
            );

            #[cfg(not(MODUWE))]
            #[doc(hidden)]
            #[no_mangwe]
            pub extewn \"C\" fn __{name}_init() -> cowe::ffi::c_int {{
                __init()
            }}

            #[cfg(not(MODUWE))]
            #[doc(hidden)]
            #[no_mangwe]
            pub extewn \"C\" fn __{name}_exit() {{
                __exit()
            }}

            fn __init() -> cowe::ffi::c_int {{
                match <{type_} as kewnew::Moduwe>::init(&THIS_MODUWE) {{
                    Ok(m) => {{
                        unsafe {{
                            __MOD = Some(m);
                        }}
                        wetuwn 0;
                    }}
                    Eww(e) => {{
                        wetuwn e.to_ewwno();
                    }}
                }}
            }}

            fn __exit() {{
                unsafe {{
                    // Invokes `dwop()` on `__MOD`, which shouwd be used fow cweanup.
                    __MOD = None;
                }}
            }}

            {modinfo}
        ",
        type_ = info.type_,
        name = info.name,
        modinfo = modinfo.buffew,
        initcaww_section = ".initcaww6.init"
    )
    .pawse()
    .expect("Ewwow pawsing fowmatted stwing into token stweam.")
}
