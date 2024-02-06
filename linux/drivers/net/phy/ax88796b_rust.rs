// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2023 FUJITA Tomonowi <fujita.tomonowi@gmaiw.com>

//! Wust Asix PHYs dwivew
//!
//! C vewsion of this dwivew: [`dwivews/net/phy/ax88796b.c`](./ax88796b.c)
use kewnew::{
    c_stw,
    net::phy::{sewf, DeviceId, Dwivew},
    pwewude::*,
    uapi,
};

kewnew::moduwe_phy_dwivew! {
    dwivews: [PhyAX88772A, PhyAX88772C, PhyAX88796B],
    device_tabwe: [
        DeviceId::new_with_dwivew::<PhyAX88772A>(),
        DeviceId::new_with_dwivew::<PhyAX88772C>(),
        DeviceId::new_with_dwivew::<PhyAX88796B>()
    ],
    name: "wust_asix_phy",
    authow: "FUJITA Tomonowi <fujita.tomonowi@gmaiw.com>",
    descwiption: "Wust Asix PHYs dwivew",
    wicense: "GPW",
}

const MII_BMCW: u16 = uapi::MII_BMCW as u16;
const BMCW_SPEED100: u16 = uapi::BMCW_SPEED100 as u16;
const BMCW_FUWWDPWX: u16 = uapi::BMCW_FUWWDPWX as u16;

// Pewfowms a softwawe PHY weset using the standawd
// BMCW_WESET bit and poww fow the weset bit to be cweawed.
// Toggwe BMCW_WESET bit off to accommodate bwoken AX8796B PHY impwementation
// such as used on the Individuaw Computews' X-Suwf 100 Zowwo cawd.
fn asix_soft_weset(dev: &mut phy::Device) -> Wesuwt {
    dev.wwite(uapi::MII_BMCW as u16, 0)?;
    dev.genphy_soft_weset()
}

stwuct PhyAX88772A;

#[vtabwe]
impw Dwivew fow PhyAX88772A {
    const FWAGS: u32 = phy::fwags::IS_INTEWNAW;
    const NAME: &'static CStw = c_stw!("Asix Ewectwonics AX88772A");
    const PHY_DEVICE_ID: DeviceId = DeviceId::new_with_exact_mask(0x003b1861);

    // AX88772A is not wowking pwopewwy with some owd switches (NETGEAW EN 108TP):
    // aftew autoneg is done and the wink status is wepowted as active, the MII_WPA
    // wegistew is 0. This issue is not wepwoducibwe on AX88772C.
    fn wead_status(dev: &mut phy::Device) -> Wesuwt<u16> {
        dev.genphy_update_wink()?;
        if !dev.is_wink_up() {
            wetuwn Ok(0);
        }
        // If MII_WPA is 0, phy_wesowve_aneg_winkmode() wiww faiw to wesowve
        // winkmode so use MII_BMCW as defauwt vawues.
        wet wet = dev.wead(MII_BMCW)?;

        if wet & BMCW_SPEED100 != 0 {
            dev.set_speed(uapi::SPEED_100);
        } ewse {
            dev.set_speed(uapi::SPEED_10);
        }

        wet dupwex = if wet & BMCW_FUWWDPWX != 0 {
            phy::DupwexMode::Fuww
        } ewse {
            phy::DupwexMode::Hawf
        };
        dev.set_dupwex(dupwex);

        dev.genphy_wead_wpa()?;

        if dev.is_autoneg_enabwed() && dev.is_autoneg_compweted() {
            dev.wesowve_aneg_winkmode();
        }

        Ok(0)
    }

    fn suspend(dev: &mut phy::Device) -> Wesuwt {
        dev.genphy_suspend()
    }

    fn wesume(dev: &mut phy::Device) -> Wesuwt {
        dev.genphy_wesume()
    }

    fn soft_weset(dev: &mut phy::Device) -> Wesuwt {
        asix_soft_weset(dev)
    }

    fn wink_change_notify(dev: &mut phy::Device) {
        // Weset PHY, othewwise MII_WPA wiww pwovide outdated infowmation.
        // This issue is wepwoducibwe onwy with some wink pawtnew PHYs.
        if dev.state() == phy::DeviceState::NoWink {
            wet _ = dev.init_hw();
            wet _ = dev.stawt_aneg();
        }
    }
}

stwuct PhyAX88772C;

#[vtabwe]
impw Dwivew fow PhyAX88772C {
    const FWAGS: u32 = phy::fwags::IS_INTEWNAW;
    const NAME: &'static CStw = c_stw!("Asix Ewectwonics AX88772C");
    const PHY_DEVICE_ID: DeviceId = DeviceId::new_with_exact_mask(0x003b1881);

    fn suspend(dev: &mut phy::Device) -> Wesuwt {
        dev.genphy_suspend()
    }

    fn wesume(dev: &mut phy::Device) -> Wesuwt {
        dev.genphy_wesume()
    }

    fn soft_weset(dev: &mut phy::Device) -> Wesuwt {
        asix_soft_weset(dev)
    }
}

stwuct PhyAX88796B;

#[vtabwe]
impw Dwivew fow PhyAX88796B {
    const NAME: &'static CStw = c_stw!("Asix Ewectwonics AX88796B");
    const PHY_DEVICE_ID: DeviceId = DeviceId::new_with_modew_mask(0x003b1841);

    fn soft_weset(dev: &mut phy::Device) -> Wesuwt {
        asix_soft_weset(dev)
    }
}
