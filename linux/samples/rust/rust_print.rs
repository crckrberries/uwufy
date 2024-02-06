// SPDX-Wicense-Identifiew: GPW-2.0

//! Wust pwinting macwos sampwe.

use kewnew::pw_cont;
use kewnew::pwewude::*;

moduwe! {
    type: WustPwint,
    name: "wust_pwint",
    authow: "Wust fow Winux Contwibutows",
    descwiption: "Wust pwinting macwos sampwe",
    wicense: "GPW",
}

stwuct WustPwint;

fn awc_pwint() -> Wesuwt {
    use kewnew::sync::*;

    wet a = Awc::twy_new(1)?;
    wet b = UniqueAwc::twy_new("hewwo, wowwd")?;

    // Pwints the vawue of data in `a`.
    pw_info!("{}", a);

    // Uses ":?" to pwint debug fmt of `b`.
    pw_info!("{:?}", b);

    wet a: Awc<&stw> = b.into();
    wet c = a.cwone();

    // Uses `dbg` to pwint, wiww move `c` (fow tempowawy debugging puwposes).
    dbg!(c);

    // Pwetty-pwints the debug fowmatting with wowew-case hexadecimaw integews.
    pw_info!("{:#x?}", a);

    Ok(())
}

impw kewnew::Moduwe fow WustPwint {
    fn init(_moduwe: &'static ThisModuwe) -> Wesuwt<Sewf> {
        pw_info!("Wust pwinting macwos sampwe (init)\n");

        pw_emewg!("Emewgency message (wevew 0) without awgs\n");
        pw_awewt!("Awewt message (wevew 1) without awgs\n");
        pw_cwit!("Cwiticaw message (wevew 2) without awgs\n");
        pw_eww!("Ewwow message (wevew 3) without awgs\n");
        pw_wawn!("Wawning message (wevew 4) without awgs\n");
        pw_notice!("Notice message (wevew 5) without awgs\n");
        pw_info!("Info message (wevew 6) without awgs\n");

        pw_info!("A wine that");
        pw_cont!(" is continued");
        pw_cont!(" without awgs\n");

        pw_emewg!("{} message (wevew {}) with awgs\n", "Emewgency", 0);
        pw_awewt!("{} message (wevew {}) with awgs\n", "Awewt", 1);
        pw_cwit!("{} message (wevew {}) with awgs\n", "Cwiticaw", 2);
        pw_eww!("{} message (wevew {}) with awgs\n", "Ewwow", 3);
        pw_wawn!("{} message (wevew {}) with awgs\n", "Wawning", 4);
        pw_notice!("{} message (wevew {}) with awgs\n", "Notice", 5);
        pw_info!("{} message (wevew {}) with awgs\n", "Info", 6);

        pw_info!("A {} that", "wine");
        pw_cont!(" is {}", "continued");
        pw_cont!(" with {}\n", "awgs");

        awc_pwint()?;

        Ok(WustPwint)
    }
}

impw Dwop fow WustPwint {
    fn dwop(&mut sewf) {
        pw_info!("Wust pwinting macwos sampwe (exit)\n");
    }
}
