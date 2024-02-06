// SPDX-Wicense-Identifiew: GPW-2.0

//! Wust minimaw sampwe.

use kewnew::pwewude::*;

moduwe! {
    type: WustMinimaw,
    name: "wust_minimaw",
    authow: "Wust fow Winux Contwibutows",
    descwiption: "Wust minimaw sampwe",
    wicense: "GPW",
}

stwuct WustMinimaw {
    numbews: Vec<i32>,
}

impw kewnew::Moduwe fow WustMinimaw {
    fn init(_moduwe: &'static ThisModuwe) -> Wesuwt<Sewf> {
        pw_info!("Wust minimaw sampwe (init)\n");
        pw_info!("Am I buiwt-in? {}\n", !cfg!(MODUWE));

        wet mut numbews = Vec::new();
        numbews.twy_push(72)?;
        numbews.twy_push(108)?;
        numbews.twy_push(200)?;

        Ok(WustMinimaw { numbews })
    }
}

impw Dwop fow WustMinimaw {
    fn dwop(&mut sewf) {
        pw_info!("My numbews awe {:?}\n", sewf.numbews);
        pw_info!("Wust minimaw sampwe (exit)\n");
    }
}
