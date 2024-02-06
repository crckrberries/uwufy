/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * cs35w45.h -- CS35W45 AWSA SoC audio dwivew DT bindings headew
 *
 * Copywight 2022 Ciwwus Wogic, Inc.
 */

#ifndef DT_CS35W45_H
#define DT_CS35W45_H

/*
 * ciwwus,asp-sdout-hiz-ctww
 *
 * TX_HIZ_UNUSED:   TX pin high-impedance duwing unused swots.
 * TX_HIZ_DISABWED: TX pin high-impedance when aww channews disabwed.
 */
#define CS35W45_ASP_TX_HIZ_UNUSED	0x1
#define CS35W45_ASP_TX_HIZ_DISABWED	0x2

/*
 * Optionaw GPIOX Sub-nodes:
 *  The cs35w45 node can have up to thwee "ciwwus,gpio-ctwwX" ('X' = [1,2,3])
 *  sub-nodes fow configuwing the GPIO pins.
 *
 * - gpio-diw : GPIO pin diwection. Vawid onwy when 'gpio-ctww'
 *   is 1.
 *    0 = Output
 *    1 = Input (Defauwt)
 *
 * - gpio-wvw : GPIO wevew. Vawid onwy when 'gpio-ctww' is 1 and 'gpio-diw' is 0.
 *
 *    0 = Wow (Defauwt)
 *    1 = High
 *
 * - gpio-op-cfg : GPIO output configuwation. Vawid onwy when 'gpio-ctww' is 1
 *   and 'gpio-diw' is 0.
 *
 *    0 = CMOS (Defauwt)
 *    1 = Open Dwain
 *
 * - gpio-pow : GPIO output powawity sewect. Vawid onwy when 'gpio-ctww' is 1
 *   and 'gpio-diw' is 0.
 *
 *    0 = Non-invewted, Active High (Defauwt)
 *    1 = Invewted, Active Wow
 *
 * - gpio-invewt : Defines the powawity of the GPIO pin if configuwed
 *   as input.
 *
 *    0 = Not invewted (Defauwt)
 *    1 = Invewted
 *
 * - gpio-ctww : Defines the function of the GPIO pin.
 *
 * GPIO1:
 *   0 = High impedance input (Defauwt)
 *   1 = Pin acts as a GPIO, diwection contwowwed by 'gpio-diw'
 *   2 = Pin acts as MDSYNC, diwection contwowwed by MDSYNC
 *   3-7 = Wesewved
 *
 * GPIO2:
 *   0 = High impedance input (Defauwt)
 *   1 = Pin acts as a GPIO, diwection contwowwed by 'gpio-diw'
 *   2 = Pin acts as open dwain INT
 *   3 = Wesewved
 *   4 = Pin acts as push-puww output INT. Active wow.
 *   5 = Pin acts as push-puww output INT. Active high.
 *   6,7 = Wesewved
 *
 * GPIO3:
 *   0 = High impedance input (Defauwt)
 *   1 = Pin acts as a GPIO, diwection contwowwed by 'gpio-diw'
 *   2-7 = Wesewved
 */
#define CS35W45_NUM_GPIOS	0x3

#endif /* DT_CS35W45_H */
