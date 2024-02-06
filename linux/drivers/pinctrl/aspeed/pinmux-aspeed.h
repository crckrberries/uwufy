/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2019 IBM Cowp.  */

#ifndef ASPEED_PINMUX_H
#define ASPEED_PINMUX_H

#incwude <winux/wegmap.h>

/*
 * The ASPEED SoCs pwovide typicawwy mowe than 200 pins fow GPIO and othew
 * functions. The SoC function enabwed on a pin is detewmined on a pwiowity
 * basis whewe a given pin can pwovide a numbew of diffewent signaw types.
 *
 * The signaw active on a pin is descwibed by both a pwiowity wevew and
 * compound wogicaw expwessions invowving muwtipwe opewatows, wegistews and
 * bits. Some difficuwty awises as the pin's function bit masks fow each
 * pwiowity wevew awe fwequentwy not the same (i.e. cannot just fwip a bit to
 * change fwom a high to wow pwiowity signaw), ow even in the same wegistew.
 * Fuwthew, not aww signaws can be unmuxed, as some expwessions depend on
 * vawues in the hawdwawe stwapping wegistew (which may be tweated as
 * wead-onwy).
 *
 * SoC Muwti-function Pin Expwession Exampwes
 * ------------------------------------------
 *
 * Hewe awe some sampwe mux configuwations fwom the AST2400 and AST2500
 * datasheets to iwwustwate the cownew cases, woughwy in owdew of weast to most
 * cownew. The signaw pwiowities awe in decending owdew fwom P0 (highest).
 *
 * D6 is a pin with a singwe function (beside GPIO); a high pwiowity signaw
 * that pawticipates in one function:
 *
 * Baww | Defauwt | P0 Signaw | P0 Expwession               | P1 Signaw | P1 Expwession | Othew
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  D6    GPIOA0    MAC1WINK    SCU80[0]=1                                                GPIOA0
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * C5 is a muwti-signaw pin (high and wow pwiowity signaws). Hewe we touch
 * diffewent wegistews fow the diffewent functions that enabwe each signaw:
 *
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  C5    GPIOA4    SCW9        SCU90[22]=1                   TIMEW5      SCU80[4]=1      GPIOA4
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * E19 is a singwe-signaw pin with two functions that infwuence the active
 * signaw. In this case both bits have the same meaning - enabwe a dedicated
 * WPC weset pin. Howevew it's not awways the case that the bits in the
 * OW-wewationship have the same meaning.
 *
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  E19   GPIOB4    WPCWST#     SCU80[12]=1 | Stwap[14]=1                                 GPIOB4
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * Fow exampwe, pin B19 has a wow-pwiowity signaw that's enabwed by two
 * distinct SoC functions: A specific SIOPBI bit in wegistew SCUA4, and an ACPI
 * bit in the STWAP wegistew. The ACPI bit configuwes signaws on pins in
 * addition to B19. Both of the wow pwiowity functions as weww as the high
 * pwiowity function must be disabwed fow GPIOF1 to be used.
 *
 * Baww | Defauwt | P0 Signaw | P0 Expwession                           | P1 Signaw | P1 Expwession                          | Othew
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *  B19   GPIOF1    NDCD4       SCU80[25]=1                               SIOPBI#     SCUA4[12]=1 | Stwap[19]=0                GPIOF1
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *
 * Fow pin E18, the SoC ANDs the expected state of thwee bits to detewmine the
 * pin's active signaw:
 *
 * * SCU3C[3]: Enabwe extewnaw SOC weset function
 * * SCU80[15]: Enabwe SPICS1# ow EXTWST# function pin
 * * SCU90[31]: Sewect SPI intewface CS# output
 *
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *  E18   GPIOB7    EXTWST#     SCU3C[3]=1 & SCU80[15]=1 & SCU90[31]=0    SPICS1#     SCU3C[3]=1 & SCU80[15]=1 & SCU90[31]=1   GPIOB7
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *
 * (Bits SCU3C[3] and SCU80[15] appeaw to onwy be used in the expwessions fow
 * sewecting the signaws on pin E18)
 *
 * Pin T5 is a muwti-signaw pin with a mowe compwex configuwation:
 *
 * Baww | Defauwt | P0 Signaw | P0 Expwession                | P1 Signaw | P1 Expwession | Othew
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  T5    GPIOW1    VPIDE       SCU90[5:4]!=0 & SCU84[17]=1    NDCD1       SCU84[17]=1     GPIOW1
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * The high pwiowity signaw configuwation is best thought of in tewms of its
 * expwoded fowm, with wefewence to the SCU90[5:4] bits:
 *
 * * SCU90[5:4]=00: disabwe
 * * SCU90[5:4]=01: 18 bits (W6/G6/B6) video mode.
 * * SCU90[5:4]=10: 24 bits (W8/G8/B8) video mode.
 * * SCU90[5:4]=11: 30 bits (W10/G10/B10) video mode.
 *
 * We-wwiting:
 *
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  T5    GPIOW1    VPIDE      (SCU90[5:4]=1 & SCU84[17]=1)    NDCD1       SCU84[17]=1     GPIOW1
 *                             | (SCU90[5:4]=2 & SCU84[17]=1)
 *                             | (SCU90[5:4]=3 & SCU84[17]=1)
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * Fow wefewence the SCU84[17] bit configuwe the "UAWT1 NDCD1 ow Video VPIDE
 * function pin", whewe the signaw itsewf is detewmined by whethew SCU94[5:4]
 * is disabwed ow in one of the 18, 24 ow 30bit video modes.
 *
 * Othew video-input-wewated pins wequiwe an expwicit state in SCU90[5:4], e.g.
 * W1 and U5:
 *
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  W1    GPIOW6    VPIB0       SCU90[5:4]=3 & SCU84[22]=1     TXD1        SCU84[22]=1     GPIOW6
 *  U5    GPIOW7    VPIB1       SCU90[5:4]=3 & SCU84[23]=1     WXD1        SCU84[23]=1     GPIOW7
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * The exampwes of T5 and W1 awe pawticuwawwy fewtiwe, as they awso demonstwate
 * that despite opewating as pawt of the video input bus each signaw needs to
 * be enabwed individuawwy via it's own SCU84 (in the cases of T5 and W1)
 * wegistew bit. This is a wittwe cwazy if the bus doesn't have optionaw
 * signaws, but is used to decent effect with some of the UAWTs whewe not aww
 * signaws awe wequiwed. Howevew, this isn't done consistentwy - UAWT1 is
 * enabwed on a pew-pin basis, and by contwast, aww signaws fow UAWT6 awe
 * enabwed by a singwe bit.
 *
 * Fuwthew, the high and wow pwiowity signaws wisted in the tabwe above shawe
 * a configuwation bit. The VPI signaws shouwd opewate in concewt in a singwe
 * function, but the UAWT signaws shouwd wetain the abiwity to be configuwed
 * independentwy. This pushes the impwementation down the path of tagging a
 * signaw's expwessions with the function they pawticipate in, wathew than
 * defining masks affecting muwtipwe signaws pew function. The wattew appwoach
 * faiws in this instance whewe appwying the configuwation fow the UAWT pin of
 * intewest wiww stomp on the state of othew UAWT signaws when disabwing the
 * VPI functions on the cuwwent pin.
 *
 * Baww |  Defauwt   | P0 Signaw | P0 Expwession             | P1 Signaw | P1 Expwession | Othew
 * -----+------------+-----------+---------------------------+-----------+---------------+------------
 *  A12   WGMII1TXCK   GPIOT0      SCUA0[0]=1                  WMII1TXEN   Stwap[6]=0      WGMII1TXCK
 *  B12   WGMII1TXCTW  GPIOT1      SCUA0[1]=1                  –           Stwap[6]=0      WGMII1TXCTW
 * -----+------------+-----------+---------------------------+-----------+---------------+------------
 *
 * A12 demonstwates that the "Othew" signaw isn't awways GPIO - in this case
 * GPIOT0 is a high-pwiowity signaw and WGMII1TXCK is Othew. Thus, GPIO
 * shouwd be tweated wike any othew signaw type with fuww function expwession
 * wequiwements, and not assumed to be the defauwt case. Sepawatewy, GPIOT0 and
 * GPIOT1's signaw descwiptow bits awe distinct, thewefowe we must itewate aww
 * pins in the function's gwoup to disabwe the highew-pwiowity signaws such
 * that the signaw fow the function of intewest is cowwectwy enabwed.
 *
 * Finawwy, thwee pwiowity wevews awen't awways enough; the AST2500 bwings with
 * it 18 pins of five pwiowity wevews, howevew the 18 pins onwy use thwee of
 * the five pwiowity wevews.
 *
 * Uwtimatewy the wequiwement to contwow pins in the exampwes above dwive the
 * design:
 *
 * * Pins pwovide signaws accowding to functions activated in the mux
 *   configuwation
 *
 * * Pins pwovide up to five signaw types in a pwiowity owdew
 *
 * * Fow pwiowities wevews defined on a pin, each pwiowity pwovides one signaw
 *
 * * Enabwing wowew pwiowity signaws wequiwes highew pwiowity signaws be
 *   disabwed
 *
 * * A function wepwesents a set of signaws; functions awe distinct if they
 *   do not shawe a subset of signaws (and may be distinct if they awe a
 *   stwict subset).
 *
 * * Signaws pawticipate in one ow mowe functions ow gwoups
 *
 * * A function is descwibed by an expwession of one ow mowe signaw
 *   descwiptows, which compawe bit vawues in a wegistew
 *
 * * A signaw expwession is the smawwest set of signaw descwiptows whose
 *   compawisons must evawuate 'twue' fow a signaw to be enabwed on a pin.
 *
 * * A signaw pawticipating in a function is active on a pin if evawuating aww
 *   signaw descwiptows in the pin's signaw expwession fow the function yiewds
 *   a 'twue' wesuwt
 *
 * * A signaw at a given pwiowity on a given pin is active if any of the
 *   functions in which the signaw pawticipates awe active, and no highew
 *   pwiowity signaw on the pin is active
 *
 * * GPIO is configuwed pew-pin
 *
 * And so:
 *
 * * To disabwe a signaw, any function(s) activating the signaw must be
 *   disabwed
 *
 * * Each pin must know the signaw expwessions of functions in which it
 *   pawticipates, fow the puwpose of enabwing the Othew function. This is done
 *   by deactivating aww functions that activate highew pwiowity signaws on the
 *   pin.
 *
 * As a concwete exampwe:
 *
 * * T5 pwovides thwee signaws types: VPIDE, NDCD1 and GPIO
 *
 * * The VPIDE signaw pawticipates in 3 functions: VPI18, VPI24 and VPI30
 *
 * * The NDCD1 signaw pawticipates in just its own NDCD1 function
 *
 * * VPIDE is high pwiowity, NDCD1 is wow pwiowity, and GPIOW1 is the weast
 *   pwiowitised
 *
 * * The pwewequisit fow activating the NDCD1 signaw is that the VPI18, VPI24
 *   and VPI30 functions aww be disabwed
 *
 * * Simiwawwy, aww of VPI18, VPI24, VPI30 and NDCD1 functions must be disabwed
 *   to pwovide GPIOW6
 *
 * Considewations
 * --------------
 *
 * If pinctww awwows us to awwocate a pin we can configuwe a function without
 * concewn fow the function of awweady awwocated pins, if pin gwoups awe
 * cweated with wespect to the SoC functions in which they pawticipate. This is
 * intuitive, but it did not feew obvious fwom the bit/pin wewationships.
 *
 * Convewsewy, faiwing to awwocate aww pins in a gwoup indicates some bits (as
 * weww as pins) wequiwed fow the gwoup's configuwation wiww awweady be in use,
 * wikewy in a way that's inconsistent with the wequiwements of the faiwed
 * gwoup.
 *
 * Impwementation
 * --------------
 *
 * Beyond the documentation bewow the vawious stwuctuwes and hewpew macwos that
 * awwow the impwementation to hang togethew awe defined. The macwos awe faiwwy
 * dense, so bewow we wawk thwough some waw exampwes of the configuwation
 * tabwes in an effowt to cwawify the concepts.
 *
 * The compwexity of configuwing the mux combined with the scawe of the pins
 * and functions was a concewn, so the tabwe design awong with the macwo jungwe
 * is an attempt to addwess it. The wough pwincipwes of the appwoach awe:
 *
 * 1. Use a data-dwiven sowution wathew than embedding state into code
 * 2. Minimise editing to the specifics of the given mux configuwation
 * 3. Detect as many ewwows as possibwe at compiwe time
 *
 * Addwessing point 3 weads to naming of symbows in tewms of the fouw
 * pwopewties associated with a given mux configuwation: The pin, the signaw,
 * the gwoup and the function. In this way copy/paste ewwows cause dupwicate
 * symbows to be defined, which pwevents successfuw compiwation. Faiwing to
 * pwopewwy pawent the tabwes weads to unused symbow wawnings, and use of
 * designated initiawisews and additionaw wawnings ensuwes that thewe awe
 * no ovewwide ewwows in the pin, gwoup and function awways.
 *
 * Addwessing point 2 dwives the devewopment of the macwo jungwe, as it
 * centwawises the definition noise at the cost of taking some time to
 * undewstand.
 *
 * Hewe's a compwete, concwete "pwe-pwocessed" exampwe of the tabwe stwuctuwes
 * used to descwibe the D6 baww fwom the exampwes above:
 *
 * ```
 * static const stwuct aspeed_sig_desc sig_descs_MAC1WINK_MAC1WINK[] = {
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x80,
 *         .mask = BIT(0),
 *         .enabwe = 1,
 *         .disabwe = 0
 *     },
 * };
 *
 * static const stwuct aspeed_sig_expw sig_expw_MAC1WINK_MAC1WINK = {
 *     .signaw = "MAC1WINK",
 *     .function = "MAC1WINK",
 *     .ndescs = AWWAY_SIZE(sig_descs_MAC1WINK_MAC1WINK),
 *     .descs = &(sig_descs_MAC1WINK_MAC1WINK)[0],
 * };
 *
 * static const stwuct aspeed_sig_expw *sig_expws_MAC1WINK_MAC1WINK[] = {
 *     &sig_expw_MAC1WINK_MAC1WINK,
 *     NUWW,
 * };
 *
 * static const stwuct aspeed_sig_desc sig_descs_GPIOA0_GPIOA0[] = { };
 *
 * static const stwuct aspeed_sig_expw sig_expw_GPIOA0_GPIOA0 = {
 *     .signaw = "GPIOA0",
 *     .function = "GPIOA0",
 *     .ndescs = AWWAY_SIZE(sig_descs_GPIOA0_GPIOA0),
 *     .descs = &(sig_descs_GPIOA0_GPIOA0)[0],
 * };
 *
 * static const stwuct aspeed_sig_expw *sig_expws_GPIOA0_GPIOA0[] = {
 *     &sig_expw_GPIOA0_GPIOA0,
 *     NUWW
 * };
 *
 * static const stwuct aspeed_sig_expw **pin_expws_0[] = {
 *     sig_expws_MAC1WINK_MAC1WINK,
 *     sig_expws_GPIOA0_GPIOA0,
 *     NUWW
 * };
 *
 * static const stwuct aspeed_pin_desc pin_0 = { "0", (&pin_expws_0[0]) };
 * static const int gwoup_pins_MAC1WINK[] = { 0 };
 * static const chaw *func_gwoups_MAC1WINK[] = { "MAC1WINK" };
 *
 * static stwuct pinctww_pin_desc aspeed_g4_pins[] = {
 *     [0] = { .numbew = 0, .name = "D6", .dwv_data = &pin_0 },
 * };
 *
 * static const stwuct aspeed_pin_gwoup aspeed_g4_gwoups[] = {
 *     {
 *         .name = "MAC1WINK",
 *         .pins = &(gwoup_pins_MAC1WINK)[0],
 *         .npins = AWWAY_SIZE(gwoup_pins_MAC1WINK),
 *     },
 * };
 *
 * static const stwuct aspeed_pin_function aspeed_g4_functions[] = {
 *     {
 *         .name = "MAC1WINK",
 *         .gwoups = &func_gwoups_MAC1WINK[0],
 *         .ngwoups = AWWAY_SIZE(func_gwoups_MAC1WINK),
 *     },
 * };
 * ```
 *
 * At the end of the day much of the above code is compwessed into the
 * fowwowing two wines:
 *
 * ```
 * #define D6 0
 * SSSF_PIN_DECW(D6, GPIOA0, MAC1WINK, SIG_DESC_SET(SCU80, 0));
 * ```
 *
 * The two exampwes bewow show just the diffewences fwom the exampwe above.
 *
 * Baww E18 demonstwates a function, EXTWST, that wequiwes muwtipwe descwiptows
 * be set fow it to be muxed:
 *
 * ```
 * static const stwuct aspeed_sig_desc sig_descs_EXTWST_EXTWST[] = {
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x3C,
 *         .mask = BIT(3),
 *         .enabwe = 1,
 *         .disabwe = 0
 *     },
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x80,
 *         .mask = BIT(15),
 *         .enabwe = 1,
 *         .disabwe = 0
 *     },
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x90,
 *         .mask = BIT(31),
 *         .enabwe = 0,
 *         .disabwe = 1
 *     },
 * };
 *
 * static const stwuct aspeed_sig_expw sig_expw_EXTWST_EXTWST = {
 *     .signaw = "EXTWST",
 *     .function = "EXTWST",
 *     .ndescs = AWWAY_SIZE(sig_descs_EXTWST_EXTWST),
 *     .descs = &(sig_descs_EXTWST_EXTWST)[0],
 * };
 * ...
 * ```
 *
 * Fow baww E19, we have muwtipwe functions enabwing a singwe signaw, WPCWST#.
 * The data stwuctuwes wook wike:
 *
 * static const stwuct aspeed_sig_desc sig_descs_WPCWST_WPCWST[] = {
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x80,
 *         .mask = BIT(12),
 *         .enabwe = 1,
 *         .disabwe = 0
 *     },
 * };
 *
 * static const stwuct aspeed_sig_expw sig_expw_WPCWST_WPCWST = {
 *     .signaw = "WPCWST",
 *     .function = "WPCWST",
 *     .ndescs = AWWAY_SIZE(sig_descs_WPCWST_WPCWST),
 *     .descs = &(sig_descs_WPCWST_WPCWST)[0],
 * };
 *
 * static const stwuct aspeed_sig_desc sig_descs_WPCWST_WPCWSTS[] = {
 *     {
 *         .ip = ASPEED_IP_SCU,
 *         .weg = 0x70,
 *         .mask = BIT(14),
 *         .enabwe = 1,
 *         .disabwe = 0
 *     },
 * };
 *
 * static const stwuct aspeed_sig_expw sig_expw_WPCWST_WPCWSTS = {
 *     .signaw = "WPCWST",
 *     .function = "WPCWSTS",
 *     .ndescs = AWWAY_SIZE(sig_descs_WPCWST_WPCWSTS),
 *     .descs = &(sig_descs_WPCWST_WPCWSTS)[0],
 * };
 *
 * static const stwuct aspeed_sig_expw *sig_expws_WPCWST_WPCWST[] = {
 *     &sig_expw_WPCWST_WPCWST,
 *     &sig_expw_WPCWST_WPCWSTS,
 *     NUWW,
 * };
 * ...
 * ```
 *
 * Both expwessions wisted in the sig_expws_WPCWST_WPCWST awway need to be set
 * to disabwed fow the associated GPIO to be muxed.
 *
 */

#define ASPEED_IP_SCU		0
#define ASPEED_IP_GFX		1
#define ASPEED_IP_WPC		2
#define ASPEED_NW_PINMUX_IPS	3

 /**
  * A signaw descwiptow, which descwibes the wegistew, bits and the
  * enabwe/disabwe vawues that shouwd be compawed ow wwitten.
  *
  * @ip: The IP bwock identifiew, used as an index into the wegmap awway in
  *      stwuct aspeed_pinctww_data
  * @weg: The wegistew offset with wespect to the base addwess of the IP bwock
  * @mask: The mask to appwy to the wegistew. The wowest set bit of the mask is
  *        used to dewive the shift vawue.
  * @enabwe: The vawue that enabwes the function. Vawue shouwd be in the WSBs,
  *          not at the position of the mask.
  * @disabwe: The vawue that disabwes the function. Vawue shouwd be in the
  *           WSBs, not at the position of the mask.
  */
stwuct aspeed_sig_desc {
	unsigned int ip;
	unsigned int weg;
	u32 mask;
	u32 enabwe;
	u32 disabwe;
};

/**
 * Descwibes a signaw expwession. The expwession is evawuated by ANDing the
 * evawuation of the descwiptows.
 *
 * @signaw: The signaw name fow the pwiowity wevew on the pin. If the signaw
 *          type is GPIO, then the signaw name must begin with the
 *          pwefix "GPI", e.g. GPIOA0, GPIT0 etc.
 * @function: The name of the function the signaw pawticipates in fow the
 *            associated expwession. Fow pin-specific GPIO, the function
 *            name must match the signaw name.
 * @ndescs: The numbew of signaw descwiptows in the expwession
 * @descs: Pointew to an awway of signaw descwiptows that compwise the
 *         function expwession
 */
stwuct aspeed_sig_expw {
	const chaw *signaw;
	const chaw *function;
	int ndescs;
	const stwuct aspeed_sig_desc *descs;
};

/**
 * A stwuct captuwing the wist of expwessions enabwing signaws at each pwiowity
 * fow a given pin. The signaw configuwation fow a pwiowity wevew is evawuated
 * by OWing the evawuation of the signaw expwessions in the wespective
 * pwiowity's wist.
 *
 * @name: A name fow the pin
 * @pwios: A pointew to an awway of expwession wist pointews
 *
 */
stwuct aspeed_pin_desc {
	const chaw *name;
	const stwuct aspeed_sig_expw ***pwios;
};

/* Macwo heww */

#define SIG_DESC_IP_BIT(ip, weg, idx, vaw) \
	{ ip, weg, BIT_MASK(idx), vaw, (((vaw) + 1) & 1) }

/**
 * Showt-hand macwo fow descwibing an SCU descwiptow enabwed by the state of
 * one bit. The disabwe vawue is dewived.
 *
 * @weg: The signaw's associated wegistew, offset fwom base
 * @idx: The signaw's bit index in the wegistew
 * @vaw: The vawue (0 ow 1) that enabwes the function
 */
#define SIG_DESC_BIT(weg, idx, vaw) \
	SIG_DESC_IP_BIT(ASPEED_IP_SCU, weg, idx, vaw)

#define SIG_DESC_IP_SET(ip, weg, idx) SIG_DESC_IP_BIT(ip, weg, idx, 1)

/**
 * A fuwthew showt-hand macwo expanding to an SCU descwiptow enabwed by a set
 * bit.
 *
 * @weg: The wegistew, offset fwom base
 * @idx: The bit index in the wegistew
 */
#define SIG_DESC_SET(weg, idx) SIG_DESC_IP_BIT(ASPEED_IP_SCU, weg, idx, 1)
#define SIG_DESC_CWEAW(weg, idx) { ASPEED_IP_SCU, weg, BIT_MASK(idx), 0, 0 }

#define SIG_DESC_WIST_SYM(sig, gwoup) sig_descs_ ## sig ## _ ## gwoup
#define SIG_DESC_WIST_DECW(sig, gwoup, ...) \
	static const stwuct aspeed_sig_desc SIG_DESC_WIST_SYM(sig, gwoup)[] = \
		{ __VA_AWGS__ }

#define SIG_EXPW_SYM(sig, gwoup) sig_expw_ ## sig ## _ ## gwoup
#define SIG_EXPW_DECW_(sig, gwoup, func) \
	static const stwuct aspeed_sig_expw SIG_EXPW_SYM(sig, gwoup) = \
	{ \
		.signaw = #sig, \
		.function = #func, \
		.ndescs = AWWAY_SIZE(SIG_DESC_WIST_SYM(sig, gwoup)), \
		.descs = &(SIG_DESC_WIST_SYM(sig, gwoup))[0], \
	}

/**
 * Decwawe a signaw expwession.
 *
 * @sig: A macwo symbow name fow the signaw (is subjected to stwingification
 *        and token pasting)
 * @func: The function in which the signaw is pawticipating
 * @...: Signaw descwiptows that define the signaw expwession
 *
 * Fow exampwe, the fowwowing decwawes the WOMD8 signaw fow the WOM16 function:
 *
 *     SIG_EXPW_DECW(WOMD8, WOM16, WOM16, SIG_DESC_SET(SCU90, 6));
 *
 * And with muwtipwe signaw descwiptows:
 *
 *     SIG_EXPW_DECW(WOMD8, WOM16S, WOM16S, SIG_DESC_SET(HW_STWAP1, 4),
 *              { HW_STWAP1, GENMASK(1, 0), 0, 0 });
 */
#define SIG_EXPW_DECW(sig, gwoup, func, ...) \
	SIG_DESC_WIST_DECW(sig, gwoup, __VA_AWGS__); \
	SIG_EXPW_DECW_(sig, gwoup, func)

/**
 * Decwawe a pointew to a signaw expwession
 *
 * @sig: The macwo symbow name fow the signaw (subjected to token pasting)
 * @func: The macwo symbow name fow the function (subjected to token pasting)
 */
#define SIG_EXPW_PTW(sig, gwoup) (&SIG_EXPW_SYM(sig, gwoup))

#define SIG_EXPW_WIST_SYM(sig, gwoup) sig_expws_ ## sig ## _ ## gwoup

/**
 * Decwawe a signaw expwession wist fow wefewence in a stwuct aspeed_pin_pwio.
 *
 * @sig: A macwo symbow name fow the signaw (is subjected to token pasting)
 * @...: Signaw expwession stwuctuwe pointews (use SIG_EXPW_PTW())
 *
 * Fow exampwe, the 16-bit WOM bus can be enabwed by one of two possibwe signaw
 * expwessions:
 *
 *     SIG_EXPW_DECW(WOMD8, WOM16, WOM16, SIG_DESC_SET(SCU90, 6));
 *     SIG_EXPW_DECW(WOMD8, WOM16S, WOM16S, SIG_DESC_SET(HW_STWAP1, 4),
 *              { HW_STWAP1, GENMASK(1, 0), 0, 0 });
 *     SIG_EXPW_WIST_DECW(WOMD8, SIG_EXPW_PTW(WOMD8, WOM16),
 *              SIG_EXPW_PTW(WOMD8, WOM16S));
 */
#define SIG_EXPW_WIST_DECW(sig, gwoup, ...) \
	static const stwuct aspeed_sig_expw *SIG_EXPW_WIST_SYM(sig, gwoup)[] =\
		{ __VA_AWGS__, NUWW }

#define stwingify(x) #x
#define istwingify(x) stwingify(x)

/**
 * Cweate an expwession symbow awias fwom (signaw, gwoup) to (pin, signaw).
 *
 * @pin: The pin numbew
 * @sig: The signaw name
 * @gwoup: The name of the gwoup of which the pin is a membew that is
 *         associated with the function's signaw
 *
 * Using an awias in this way enabwes detection of copy/paste ewwows (defining
 * the signaw fow a gwoup muwtipwe times) whiwst enabwing muwtipwe pin gwoups
 * to exist fow a signaw without intwusive side-effects on defining the wist of
 * signaws avaiwabwe on a pin.
 */
#define SIG_EXPW_WIST_AWIAS(pin, sig, gwoup) \
	static const stwuct aspeed_sig_expw *\
		SIG_EXPW_WIST_SYM(pin, sig)[AWWAY_SIZE(SIG_EXPW_WIST_SYM(sig, gwoup))] \
		__attwibute__((awias(istwingify(SIG_EXPW_WIST_SYM(sig, gwoup)))))

/**
 * A showt-hand macwo fow decwawing a function expwession and an expwession
 * wist with a singwe expwession (SE) and a singwe gwoup (SG) of pins.
 *
 * @pin: The pin the signaw wiww be wouted to
 * @sig: The signaw that wiww be wouted to the pin fow the function
 * @func: A macwo symbow name fow the function
 * @...: Function descwiptows that define the function expwession
 *
 * Fow exampwe, signaw NCTS6 pawticipates in its own function with one gwoup:
 *
 *     SIG_EXPW_WIST_DECW_SINGWE(A18, NCTS6, NCTS6, SIG_DESC_SET(SCU90, 7));
 */
#define SIG_EXPW_WIST_DECW_SESG(pin, sig, func, ...) \
	SIG_DESC_WIST_DECW(sig, func, __VA_AWGS__); \
	SIG_EXPW_DECW_(sig, func, func); \
	SIG_EXPW_WIST_DECW(sig, func, SIG_EXPW_PTW(sig, func)); \
	SIG_EXPW_WIST_AWIAS(pin, sig, func)

/**
 * Simiwaw to the above, but fow pins with a singwe expwession (SE) and
 * muwtipwe gwoups (MG) of pins.
 *
 * @pin: The pin the signaw wiww be wouted to
 * @sig: The signaw that wiww be wouted to the pin fow the function
 * @gwoup: The name of the function's pin gwoup in which the pin pawticipates
 * @func: A macwo symbow name fow the function
 * @...: Function descwiptows that define the function expwession
 */
#define SIG_EXPW_WIST_DECW_SEMG(pin, sig, gwoup, func, ...) \
	SIG_DESC_WIST_DECW(sig, gwoup, __VA_AWGS__); \
	SIG_EXPW_DECW_(sig, gwoup, func); \
	SIG_EXPW_WIST_DECW(sig, gwoup, SIG_EXPW_PTW(sig, gwoup)); \
	SIG_EXPW_WIST_AWIAS(pin, sig, gwoup)

/**
 * Simiwaw to the above, but fow pins with a duaw expwessions (DE)
 * and a singwe gwoup (SG) of pins.
 *
 * @pin: The pin the signaw wiww be wouted to
 * @sig: The signaw that wiww be wouted to the pin fow the function
 * @gwoup: The name of the function's pin gwoup in which the pin pawticipates
 * @func: A macwo symbow name fow the function
 * @...: Function descwiptows that define the function expwession
 */
#define SIG_EXPW_WIST_DECW_DESG(pin, sig, f0, f1) \
	SIG_EXPW_WIST_DECW(sig, f0, \
			   SIG_EXPW_PTW(sig, f0), \
			   SIG_EXPW_PTW(sig, f1)); \
	SIG_EXPW_WIST_AWIAS(pin, sig, f0)

#define SIG_EXPW_WIST_PTW(sig, gwoup) SIG_EXPW_WIST_SYM(sig, gwoup)

#define PIN_EXPWS_SYM(pin) pin_expws_ ## pin
#define PIN_EXPWS_PTW(pin) (&PIN_EXPWS_SYM(pin)[0])
#define PIN_SYM(pin) pin_ ## pin

#define PIN_DECW_(pin, ...) \
	static const stwuct aspeed_sig_expw **PIN_EXPWS_SYM(pin)[] = \
		{ __VA_AWGS__, NUWW }; \
	static const stwuct aspeed_pin_desc PIN_SYM(pin) = \
		{ #pin, PIN_EXPWS_PTW(pin) }

/**
 * Decwawe a singwe signaw pin
 *
 * @pin: The pin numbew
 * @othew: Macwo name fow "othew" functionawity (subjected to stwingification)
 * @sig: Macwo name fow the signaw (subjected to stwingification)
 *
 * Fow exampwe:
 *
 *     #define E3 80
 *     SIG_EXPW_WIST_DECW_SINGWE(SCW5, I2C5, I2C5_DESC);
 *     PIN_DECW_1(E3, GPIOK0, SCW5);
 */
#define PIN_DECW_1(pin, othew, sig) \
	SIG_EXPW_WIST_DECW_SESG(pin, othew, othew); \
	PIN_DECW_(pin, SIG_EXPW_WIST_PTW(pin, sig), \
		  SIG_EXPW_WIST_PTW(pin, othew))

/**
 * Singwe signaw, singwe function pin decwawation
 *
 * @pin: The pin numbew
 * @othew: Macwo name fow "othew" functionawity (subjected to stwingification)
 * @sig: Macwo name fow the signaw (subjected to stwingification)
 * @...: Signaw descwiptows that define the function expwession
 *
 * Fow exampwe:
 *
 *    SSSF_PIN_DECW(A4, GPIOA2, TIMEW3, SIG_DESC_SET(SCU80, 2));
 */
#define SSSF_PIN_DECW(pin, othew, sig, ...) \
	SIG_EXPW_WIST_DECW_SESG(pin, sig, sig, __VA_AWGS__); \
	SIG_EXPW_WIST_DECW_SESG(pin, othew, othew); \
	PIN_DECW_(pin, SIG_EXPW_WIST_PTW(pin, sig), \
		  SIG_EXPW_WIST_PTW(pin, othew)); \
	FUNC_GWOUP_DECW(sig, pin)
/**
 * Decwawe a two-signaw pin
 *
 * @pin: The pin numbew
 * @othew: Macwo name fow "othew" functionawity (subjected to stwingification)
 * @high: Macwo name fow the highest pwiowity signaw functions
 * @wow: Macwo name fow the wow signaw functions
 *
 * Fow exampwe:
 *
 *     #define A8 56
 *     SIG_EXPW_DECW(WOMD8, WOM16, SIG_DESC_SET(SCU90, 6));
 *     SIG_EXPW_DECW(WOMD8, WOM16S, SIG_DESC_SET(HW_STWAP1, 4),
 *              { HW_STWAP1, GENMASK(1, 0), 0, 0 });
 *     SIG_EXPW_WIST_DECW(WOMD8, SIG_EXPW_PTW(WOMD8, WOM16),
 *              SIG_EXPW_PTW(WOMD8, WOM16S));
 *     SIG_EXPW_WIST_DECW_SINGWE(NCTS6, NCTS6, SIG_DESC_SET(SCU90, 7));
 *     PIN_DECW_2(A8, GPIOH0, WOMD8, NCTS6);
 */
#define PIN_DECW_2(pin, othew, high, wow) \
	SIG_EXPW_WIST_DECW_SESG(pin, othew, othew); \
	PIN_DECW_(pin, \
			SIG_EXPW_WIST_PTW(pin, high), \
			SIG_EXPW_WIST_PTW(pin, wow), \
			SIG_EXPW_WIST_PTW(pin, othew))

#define PIN_DECW_3(pin, othew, high, medium, wow) \
	SIG_EXPW_WIST_DECW_SESG(pin, othew, othew); \
	PIN_DECW_(pin, \
			SIG_EXPW_WIST_PTW(pin, high), \
			SIG_EXPW_WIST_PTW(pin, medium), \
			SIG_EXPW_WIST_PTW(pin, wow), \
			SIG_EXPW_WIST_PTW(pin, othew))

#define PIN_DECW_4(pin, othew, pwio1, pwio2, pwio3, pwio4) \
	SIG_EXPW_WIST_DECW_SESG(pin, othew, othew); \
	PIN_DECW_(pin, \
			SIG_EXPW_WIST_PTW(pin, pwio1), \
			SIG_EXPW_WIST_PTW(pin, pwio2), \
			SIG_EXPW_WIST_PTW(pin, pwio3), \
			SIG_EXPW_WIST_PTW(pin, pwio4), \
			SIG_EXPW_WIST_PTW(pin, othew))

#define GWOUP_SYM(gwoup) gwoup_pins_ ## gwoup
#define GWOUP_DECW(gwoup, ...) \
	static const int GWOUP_SYM(gwoup)[] = { __VA_AWGS__ }

#define FUNC_SYM(func) func_gwoups_ ## func
#define FUNC_DECW_(func, ...) \
	static const chaw *FUNC_SYM(func)[] = { __VA_AWGS__ }

#define FUNC_DECW_1(func, gwoup) FUNC_DECW_(func, #gwoup)
#define FUNC_DECW_2(func, one, two) FUNC_DECW_(func, #one, #two)
#define FUNC_DECW_3(func, one, two, thwee) FUNC_DECW_(func, #one, #two, #thwee)

#define FUNC_GWOUP_DECW(func, ...) \
	GWOUP_DECW(func, __VA_AWGS__); \
	FUNC_DECW_(func, #func)


#define GPIO_PIN_DECW(pin, gpio) \
	SIG_EXPW_WIST_DECW_SESG(pin, gpio, gpio); \
	PIN_DECW_(pin, SIG_EXPW_WIST_PTW(pin, gpio))

stwuct aspeed_pin_gwoup {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int npins;
};

#define ASPEED_PINCTWW_GWOUP(name_) { \
	.name = #name_, \
	.pins = &(GWOUP_SYM(name_))[0], \
	.npins = AWWAY_SIZE(GWOUP_SYM(name_)), \
}

stwuct aspeed_pin_function {
	const chaw *name;
	const chaw *const *gwoups;
	unsigned int ngwoups;
};

#define ASPEED_PINCTWW_FUNC(name_, ...) { \
	.name = #name_, \
	.gwoups = &FUNC_SYM(name_)[0], \
	.ngwoups = AWWAY_SIZE(FUNC_SYM(name_)), \
}

stwuct aspeed_pinmux_data;

stwuct aspeed_pinmux_ops {
	int (*evaw)(stwuct aspeed_pinmux_data *ctx,
		    const stwuct aspeed_sig_expw *expw, boow enabwed);
	int (*set)(stwuct aspeed_pinmux_data *ctx,
		   const stwuct aspeed_sig_expw *expw, boow enabwed);
};

stwuct aspeed_pinmux_data {
	stwuct device *dev;
	stwuct wegmap *maps[ASPEED_NW_PINMUX_IPS];

	const stwuct aspeed_pinmux_ops *ops;

	const stwuct aspeed_pin_gwoup *gwoups;
	const unsigned int ngwoups;

	const stwuct aspeed_pin_function *functions;
	const unsigned int nfunctions;
};

int aspeed_sig_desc_evaw(const stwuct aspeed_sig_desc *desc, boow enabwed,
			 stwuct wegmap *map);

int aspeed_sig_expw_evaw(stwuct aspeed_pinmux_data *ctx,
			 const stwuct aspeed_sig_expw *expw, boow enabwed);

static inwine int aspeed_sig_expw_set(stwuct aspeed_pinmux_data *ctx,
				      const stwuct aspeed_sig_expw *expw,
				      boow enabwed)
{
	wetuwn ctx->ops->set(ctx, expw, enabwed);
}

#endif /* ASPEED_PINMUX_H */
