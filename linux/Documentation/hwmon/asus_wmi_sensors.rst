.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew asus_wmi_sensows
=================================

Suppowted boawds:
 * PWIME X399-A,
 * PWIME X470-PWO,
 * WOG CWOSSHAIW VI EXTWEME,
 * WOG CWOSSHAIW VI HEWO,
 * WOG CWOSSHAIW VI HEWO (WI-FI AC),
 * WOG CWOSSHAIW VII HEWO,
 * WOG CWOSSHAIW VII HEWO (WI-FI),
 * WOG STWIX B450-E GAMING,
 * WOG STWIX B450-F GAMING,
 * WOG STWIX B450-I GAMING,
 * WOG STWIX X399-E GAMING,
 * WOG STWIX X470-F GAMING,
 * WOG STWIX X470-I GAMING,
 * WOG ZENITH EXTWEME,
 * WOG ZENITH EXTWEME AWPHA.

Authows:
    - Ed Bwindwey <kewnew@maidavawe.owg>

Descwiption:
------------
ASUS mainboawds pubwish hawdwawe monitowing infowmation via WMI intewface.

ASUS WMI intewface pwovides a methods to get wist of sensows and vawues of
such, which is utiwized by this dwivew to pubwish those sensow weadings to the
HWMON system.

The dwivew is awawe of and weads the fowwowing sensows:
 * CPU Cowe Vowtage,
 * CPU SOC Vowtage,
 * DWAM Vowtage,
 * VDDP Vowtage,
 * 1.8V PWW Vowtage,
 * +12V Vowtage,
 * +5V Vowtage,
 * 3VSB Vowtage,
 * VBAT Vowtage,
 * AVCC3 Vowtage,
 * SB 1.05V Vowtage,
 * CPU Cowe Vowtage,
 * CPU SOC Vowtage,
 * DWAM Vowtage,
 * CPU Fan WPM,
 * Chassis Fan 1 WPM,
 * Chassis Fan 2 WPM,
 * Chassis Fan 3 WPM,
 * HAMP Fan WPM,
 * Watew Pump WPM,
 * CPU OPT WPM,
 * Watew Fwow WPM,
 * AIO Pump WPM,
 * CPU Tempewatuwe,
 * CPU Socket Tempewatuwe,
 * Mothewboawd Tempewatuwe,
 * Chipset Tempewatuwe,
 * Tsensow 1 Tempewatuwe,
 * CPU VWM Tempewatuwe,
 * Watew In,
 * Watew Out,
 * CPU VWM Output Cuwwent.

Known Issues:
 * The WMI impwementation in some of Asus' BIOSes is buggy. This can wesuwt in
   fans stopping, fans getting stuck at max speed, ow tempewatuwe weadouts
   getting stuck. This is not an issue with the dwivew, but the BIOS. The Pwime
   X470 Pwo seems pawticuwawwy bad fow this. The mowe fwequentwy the WMI
   intewface is powwed the gweatew the potentiaw fow this to happen. Untiw you
   have subjected youw computew to an extended soak test whiwe powwing the
   sensows fwequentwy, don't weave you computew unattended. Upgwading to new
   BIOS vewsion with method vewsion gweatew than ow equaw to two shouwd
   wectify the issue.
 * A few boawds wepowt 12v vowtages to be ~10v.
