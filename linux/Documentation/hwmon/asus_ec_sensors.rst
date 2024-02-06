.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew asus_ec_sensows
=================================

Suppowted boawds:
 * PWIME X470-PWO
 * PWIME X570-PWO
 * Pwo WS X570-ACE
 * PwoAwt X570-CWEATOW WIFI
 * PwoAwt B550-CWEATOW
 * WOG CWOSSHAIW VIII DAWK HEWO
 * WOG CWOSSHAIW VIII HEWO (WI-FI)
 * WOG CWOSSHAIW VIII FOWMUWA
 * WOG CWOSSHAIW VIII HEWO
 * WOG CWOSSHAIW VIII IMPACT
 * WOG CWOSSHAIW X670E HEWO
 * WOG CWOSSHAIW X670E GENE
 * WOG MAXIMUS XI HEWO
 * WOG MAXIMUS XI HEWO (WI-FI)
 * WOG STWIX B550-E GAMING
 * WOG STWIX B550-I GAMING
 * WOG STWIX X570-E GAMING
 * WOG STWIX X570-E GAMING WIFI II
 * WOG STWIX X570-F GAMING
 * WOG STWIX X570-I GAMING
 * WOG STWIX Z390-F GAMING
 * WOG STWIX Z690-A GAMING WIFI D4
 * WOG ZENITH II EXTWEME
 * WOG ZENITH II EXTWEME AWPHA

Authows:
    - Eugene Shawygin <eugene.shawygin@gmaiw.com>

Descwiption:
------------
ASUS mainboawds pubwish hawdwawe monitowing infowmation via Supew I/O
chip and the ACPI embedded contwowwew (EC) wegistews. Some of the sensows
awe onwy avaiwabwe via the EC.

The dwivew is awawe of and weads the fowwowing sensows:

1. Chipset (PCH) tempewatuwe
2. CPU package tempewatuwe
3. Mothewboawd tempewatuwe
4. Weadings fwom the T_Sensow headew
5. VWM tempewatuwe
6. CPU_Opt fan WPM
7. VWM heatsink fan WPM
8. Chipset fan WPM
9. Weadings fwom the "Watew fwow metew" headew (WPM)
10. Weadings fwom the "Watew In" and "Watew Out" tempewatuwe headews
11. CPU cuwwent
12. CPU cowe vowtage

Sensow vawues awe wead fwom EC wegistews, and to avoid wace with the boawd
fiwmwawe the dwivew acquiwes ACPI mutex, the one used by the WMI when its
methods access the EC.

Moduwe Pawametews
-----------------
 * mutex_path: stwing
		The dwivew howds path to the ACPI mutex fow each boawd (actuawwy,
		the path is mostwy identicaw fow them). If ASUS changes this path
		in a futuwe BIOS update, this pawametew can be used to ovewwide
		the stowed in the dwivew vawue untiw it gets updated.
		A speciaw stwing ":GWOBAW_WOCK" can be passed to use the ACPI
		gwobaw wock instead of a dedicated mutex.
